// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "StoreProductModel.h"
#include "DataTables/FStoreProductData.h"

UStoreProductModel::UStoreProductModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UStoreProductModel* UStoreProductModel::ConstructFromStoreProductData(const FStoreProductData& StoreProductData)
{
	auto StoreProductModel = NewObject<UStoreProductModel>(GetTransientPackage(), NAME_None);
	StoreProductModel->ID = StoreProductData.ID;
	StoreProductModel->Title = StoreProductData.Title;
	StoreProductModel->Description = StoreProductData.Description;
	StoreProductModel->Tooltip = StoreProductData.Tooltip;
	StoreProductModel->Price = StoreProductData.Price;
	StoreProductModel->Currency = StoreProductData.Currency;
	StoreProductModel->Icon = StoreProductData.Icon;
	return StoreProductModel;
}

