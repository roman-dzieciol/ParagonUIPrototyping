// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "DeckItemModel.h"

UDeckItemModel::UDeckItemModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	LinkedCardsLimit = 6;
}


UDeckItemModel* UDeckItemModel::ConstructDeckItemModel(UCardModel* ForCardModel)
{
	UDeckItemModel* Model = NewObject<UDeckItemModel>(GetTransientPackage(), NAME_None);
	Model->CardModel = ForCardModel;
	return Model;
}


bool UDeckItemModel::LinkWithCard(UCardModel* CardModelToLink)
{
	if (LinkedDeckItems.Num() < LinkedCardsLimit)
	{
		UDeckItemModel* LinkedDeckItem = UDeckItemModel::ConstructDeckItemModel(CardModelToLink);
		LinkedDeckItems.Add(LinkedDeckItem);
		CardModelToLink->IncrementInUseCount();
		return true;
	}
	return false;
}

void UDeckItemModel::UnlinkWithDeckItem(UDeckItemModel* DeckItem)
{
	DeckItem->CardModel->DecrementInUseCount();
	LinkedDeckItems.Remove(DeckItem);
}

void UDeckItemModel::UnlinkAllCards()
{
	for (auto LinkedDeckItem : LinkedDeckItems)
	{
		LinkedDeckItem->CardModel->DecrementInUseCount();
	}
	LinkedDeckItems.Empty();
}

