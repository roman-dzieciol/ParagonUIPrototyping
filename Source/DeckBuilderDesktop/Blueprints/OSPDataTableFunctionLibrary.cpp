// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "OSPDataTableFunctionLibrary.h"
#include "Models/GameTypeListModel.h"
#include "Models/StoreProductModel.h"

UGameTypeListModel* UOSPDataTableFunctionLibrary::ConstructGameTypeListFromDataTable(UDataTable* GameTypeDataTable)
{
	return UGameTypeListModel::ConstructFromGameTypeDataTable(GameTypeDataTable);
}

UStoreProductModel* UOSPDataTableFunctionLibrary::ConstructStoreProductFromData(const FStoreProductData& StoreProductData)
{
	return UStoreProductModel::ConstructFromStoreProductData(StoreProductData);
}

