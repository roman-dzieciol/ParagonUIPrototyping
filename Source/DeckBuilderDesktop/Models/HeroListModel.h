// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "HeroListModel.generated.h"

class UHeroModel;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UHeroListModel : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero List")
		TArray<UHeroModel*> HeroModels;

	UPROPERTY()
		TMap<FString, UHeroModel*> HeroModelsByName;

public:
	UFUNCTION(BlueprintCallable, Category = "Hero List")
	UHeroModel* GetHeroModelNamed(FString HeroName) const;

public:
	static UHeroListModel* ConstructFromHeroDataTable(UDataTable* HeroDataTable, UDataTable* HeroAbilityTable, UDataTable* HeroSkinTable);
};
