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
	uint32& Count = Cards.FindOrAdd(CardModel);
	++Count;
}

void UCardDeckModel::RemoveCard(UCardModel* CardModel)
{
	uint32* Count = Cards.Find(CardModel);
	if (Count)
	{
		--(*Count);
		if (*Count == 0)
		{
			Cards.Remove(CardModel);
		}
	}
}

void UCardDeckModel::RemoveAllCards()
{
	Cards.Empty();
}

void UCardDeckModel::RemoveAllCardsOfType(FString CardType)
{
	auto CardsOfType = GetAllCardsOfType(CardType);
	for (auto CardModel : CardsOfType)
	{
		Cards.Remove(CardModel);
	}
}

TArray<UCardModel*> UCardDeckModel::GetAllCardsOfType(FString CardType)
{
	TArray<UCardModel*> CardModels;
	Cards.GetKeys(CardModels);
	return CardModels.FilterByPredicate([=](UCardModel* CardModel) { return CardModel->Type.ToString().Equals(CardType); });
}

int32 UCardDeckModel::CountOfCard(UCardModel* CardModel)
{
	uint32* Count = Cards.Find(CardModel);
	return Count ? *Count : 0;
}

int32 UCardDeckModel::CountOfAllCards()
{
	int32 Count = 0;
	for (const auto& Entry : Cards)
	{
		Count += Entry.Value;
	}
	return Count;
}
