// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Engine/DataTable.h"
#include "DataTables/FHeroData.h"
#include "HeroModel.generated.h"

class UHeroAbilityModel;
class UHeroSkinModel;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UHeroModel : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		FString HeroID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		FString HeroName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		UTexture2D* AvatarTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		TArray<FString> Affinities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		TArray<FString> RecommendedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		TArray<FString> NotRecommendedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		TArray<UHeroAbilityModel*> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		TArray<UHeroSkinModel*> Skins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		FString Difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		int32 BasicAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		int32 AbilityPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		int32 Durability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		int32 Mobility;
	
public:
	static UHeroModel* ConstructFromHeroData(const FHeroData& HeroData, UDataTable* HeroAbilityTable, UDataTable* HeroSkinTable);
	
};
