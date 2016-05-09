// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardDeckModel.h"

UCardDeckModel::UCardDeckModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxCardCount = 40;
}

void UCardDeckModel::AddCard(UCardModel* CardModel)
{
	auto DeckItem = UDeckItemModel::ConstructDeckItemModel(CardModel);
	AddDeckItem(DeckItem);
}

void UCardDeckModel::AddDeckItem(UDeckItemModel* DeckItem)
{
	if (!DeckItems.Contains(DeckItem))
	{
		DeckItem->CardModel->IncrementInUseCount();
		DeckItems.Add(DeckItem);
	}
}

void UCardDeckModel::RemoveDeckItem(UDeckItemModel* DeckItem)
{
	DeckItem->CardModel->DecrementInUseCount();
	DeckItem->UnlinkAllCards();
	DeckItems.Remove(DeckItem);
}

void UCardDeckModel::RemoveAllCards()
{
	for (auto DeckItem : DeckItems)
	{
		DeckItem->CardModel->DecrementInUseCount();
		DeckItem->UnlinkAllCards();
	}
	DeckItems.Empty();
}

void UCardDeckModel::RemoveAllCardsOfType(FString CardType)
{
	auto ItemsToRemove = GetAllCardsOfType(CardType);
	for (auto ItemToRemove : ItemsToRemove)
	{
		RemoveDeckItem(ItemToRemove);
	}
}

TArray<UDeckItemModel*> UCardDeckModel::GetAllCardsOfType(FString CardType)
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

int32 UCardDeckModel::CountOfCard(UCardModel* CardModel)
{
	// TODO: Use map or event driven updates
	int32 Count = 0;
	for (const auto DeckItem : DeckItems)
	{
		if (DeckItem->CardModel == CardModel)
		{
			++Count;
		}
		for (const auto LinkedDeckItem : DeckItem->LinkedDeckItems)
		{
			if (LinkedDeckItem->CardModel == CardModel)
			{
				++Count;
			}
		}
	}
	return Count;
}

int32 UCardDeckModel::CountOfAllCards()
{
	auto Count = DeckItems.Num();
	for (const auto DeckItem : DeckItems)
	{
		Count += DeckItem->LinkedDeckItems.Num();
	}
	return Count;
}
