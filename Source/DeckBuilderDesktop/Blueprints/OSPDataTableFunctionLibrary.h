// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataTables/FStoreProductData.h"
#include "OSPDataTableFunctionLibrary.generated.h"

class UGameTypeListModel;
class UStoreProductModel;

/**
 * 
 */
UCLASS()
class DECKBUILDERDESKTOP_API UOSPDataTableFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = "DataTable Function Library")
		static UGameTypeListModel* ConstructGameTypeListFromDataTable(UDataTable* GameTypeDataTable);

	UFUNCTION(BlueprintCallable, Category = "DataTable Function Library")
		static UStoreProductModel* ConstructStoreProductFromData(const FStoreProductData& StoreProductData);
};
