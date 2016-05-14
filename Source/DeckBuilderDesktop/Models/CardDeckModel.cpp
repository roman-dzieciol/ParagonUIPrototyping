// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardDeckModel.h"

UCardDeckModel::UCardDeckModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxCardCount = 40;
}

void UCardDeckModel::IncrementInUseCount(UDeckItemModel* DeckItem)
{
	DeckItemsByCardModel.Emplace(DeckItem->CardModel, DeckItem);
}

void UCardDeckModel::DecrementInUseCount(UDeckItemModel* DeckItem)
{
	DeckItemsByCardModel.Remove(DeckItem->CardModel, DeckItem);
}

bool UCardDeckModel::AddCard(UCardModel* CardModel)
{
	auto DeckItem = UDeckItemModel::ConstructDeckItemModel(CardModel);
	return AddDeckItem(DeckItem);
}

bool UCardDeckModel::CanAddDeckItem(UDeckItemModel* DeckItem) const
{
	return GetCountOfAllCards() < MaxCardCount && !DeckItems.Contains(DeckItem);
}

bool UCardDeckModel::InternalAddDeckItem(UDeckItemModel* DeckItem)
{
	if (!CanAddDeckItem(DeckItem))
	{
		return false;
	}

	IncrementInUseCount(DeckItem);
	DeckItems.Add(DeckItem);
	return true;
}

bool UCardDeckModel::AddDeckItem(UDeckItemModel* DeckItem)
{
	if (!InternalAddDeckItem(DeckItem))
	{
		return false;
	}

	OnCardDeckUpdated.Broadcast();
	return true;
}

bool UCardDeckModel::AddDeckItemAndLinkWith(UDeckItemModel* DeckItem, UDeckItemModel* LinkingItem)
{
	if (!InternalAddDeckItem(DeckItem))
	{
		return false;
	}

	if (!LinkingItem->LinkWithItem(DeckItem))
	{
		InternalRemoveDeckItem(DeckItem);
		return false;
	}

	OnCardDeckUpdated.Broadcast();
	return true;
}

void UCardDeckModel::InternalRemoveDeckItem(UDeckItemModel* DeckItem)
{
	DecrementInUseCount(DeckItem);
	DeckItem->OnRemove();

	for (auto LinkedDeckItem : DeckItem->LinkedDeckItems)
	{
		RemoveDeckItem(LinkedDeckItem);
	}
	DeckItems.Remove(DeckItem);
}

void UCardDeckModel::RemoveDeckItem(UDeckItemModel* DeckItem)
{
	InternalRemoveDeckItem(DeckItem);
	OnCardDeckUpdated.Broadcast();
}

void UCardDeckModel::RemoveAllCards()
{
	DeckItemsByCardModel.Empty();
	DeckItems.Empty();
	OnCardDeckUpdated.Broadcast();
}

void UCardDeckModel::RemoveAllCardsOfType(FString CardType)
{
	auto ItemsToRemove = GetAllCardsOfType(CardType);
	for (auto ItemToRemove : ItemsToRemove)
	{
		InternalRemoveDeckItem(ItemToRemove);
	}
	OnCardDeckUpdated.Broadcast();
}

TArray<UDeckItemModel*> UCardDeckModel::GetAllCardsOfType(FString CardType) const
{
	return DeckItems.FilterByPredicate([=](UDeckItemModel* DeckItem) 
	{ 
		if (DeckItem->CardModel != nullptr)
		{
			return DeckItem->CardModel->Type.ToString().Equals(CardType);
		}
		return false;
	});
}

int32 UCardDeckModel::GetCountOfCard(UCardModel* CardModel) const
{
	TArray<UDeckItemModel*> RelatedDeckItems;
	DeckItemsByCardModel.MultiFind(CardModel, RelatedDeckItems);
	return RelatedDeckItems.Num();
}

int32 UCardDeckModel::GetCountOfAllCards() const
{
	return DeckItems.Num();
}

bool UCardDeckModel::CanAddCard() const
{
	return GetCountOfAllCards() < MaxCardCount;
}
