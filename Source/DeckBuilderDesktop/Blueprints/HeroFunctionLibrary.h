// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "HeroFunctionLibrary.generated.h"

class UHeroListModel;
class UDataTable;

/**
 * 
 */
UCLASS()
class DECKBUILDERDESKTOP_API UHeroFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Hero Function Library")
	static UHeroListModel* ConstructHeroListFromHeroDataTable(UDataTable* HeroDataTable, UDataTable* HeroAbilityTable);

	UFUNCTION(BlueprintCallable, Category = "Hero Function Library")
	static UTexture2D* LoadKeyTextureNamed(const FString& KeyName);
};
