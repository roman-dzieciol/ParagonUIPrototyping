// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "DeckItemModel.h"


UDeckItemModel* UDeckItemModel::ConstructDeckItemModel(UCardModel* ForCardModel)
{
	UDeckItemModel* Model = NewObject<UDeckItemModel>(GetTransientPackage(), NAME_None);
	Model->CardModel = ForCardModel;
	return Model;
}


void UDeckItemModel::LinkWithCard(UCardModel* CardModelToLink)
{
	UDeckItemModel* LinkedDeckItem = UDeckItemModel::ConstructDeckItemModel(CardModelToLink);
	LinkedDeckItems.Add(LinkedDeckItem);
	CardModelToLink->IncrementInUseCount();
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

