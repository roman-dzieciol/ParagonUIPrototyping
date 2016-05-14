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

bool UDeckItemModel::CanLinkItem(UDeckItemModel* DeckItem) const
{
	return LinkedDeckItems.Num() < LinkedCardsLimit;
}

bool UDeckItemModel::LinkWithItem(UDeckItemModel* DeckItem)
{
	if (CanLinkItem(DeckItem))
	{
		LinkedDeckItems.Add(DeckItem);
		DeckItem->LinkingDeckItem = this;
		return true;
	}
	return false;
}

void UDeckItemModel::UnlinkWithItem(UDeckItemModel* DeckItem)
{
	DeckItem->LinkingDeckItem = nullptr;
	LinkedDeckItems.Remove(DeckItem);
}

void UDeckItemModel::UnlinkAllItems()
{
	for (auto LinkedDeckItem : LinkedDeckItems)
	{
		LinkedDeckItem->LinkingDeckItem = nullptr;
	}
	LinkedDeckItems.Empty();
}

int32 UDeckItemModel::GetItemCount() const
{
	return 1 + LinkedDeckItems.Num();
}

void UDeckItemModel::OnRemove()
{
	if (LinkingDeckItem)
	{
		LinkingDeckItem->UnlinkWithItem(this);
	}
	else 
	{
		UnlinkAllItems();
	}
}
