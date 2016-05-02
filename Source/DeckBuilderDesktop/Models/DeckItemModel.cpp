// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "DeckItemModel.h"


UDeckItemModel* UDeckItemModel::ConstructDeckItemModel(UCardModel* ForCardModel)
{
	UDeckItemModel* Model = NewObject<UDeckItemModel>(GetTransientPackage(), NAME_None);
	Model->CardModel = ForCardModel;
	return Model;
}

