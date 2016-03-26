// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardsDeck.h"


void UCardsDeck::AddCard(FCardData CardData)
{
	Cards.Add(CardData);
}

void UCardsDeck::RemoveCard(FCardData CardData)
{
	Cards.RemoveSingle(CardData);
}

void UCardsDeck::RemoveAllCards()
{
	Cards.Empty();
}

void UCardsDeck::RemoveAllCardsOfType(FString CardType)
{
	Cards.RemoveAll([=](const FCardData& CardData) { return CardData.Type == CardType; });
}

TArray<FCardData> UCardsDeck::GetAllCardsOfType(FString CardType)
{
	return Cards.FilterByPredicate([=](const FCardData& CardData) { return CardData.Type == CardType; });
}

int32 UCardsDeck::CountOfCardsNamed(FString CardName)
{
	auto AllCardsNamed = Cards.FilterByPredicate([=](const FCardData& CardData) { return CardData.CardName == CardName; });
	return AllCardsNamed.Num();
}



