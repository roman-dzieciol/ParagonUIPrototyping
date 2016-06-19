// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "RewardModel.h"
#include "DataTables/FHeroRewardData.h"
#include "HeroRewardModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UHeroRewardModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Reward")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Reward")
		URewardModel* Reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Reward")
		float MatchXPBoost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Reward")
		float MatchTeamXPBoost;

public:
	static UHeroRewardModel* ConstructFromHeroRewardData(const FHeroRewardData& HeroRewardData, FString HeroName, UDataTable* RewardTable, UDataTable* HeroSkinTable, UDataTable* HeroEmoteTable);
	
	
};
