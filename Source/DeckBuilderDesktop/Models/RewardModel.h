// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DataTables/FRewardData.h"
#include "RewardModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API URewardModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
		FString RewardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
		FString RewardType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
		int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
		UTexture2D* Icon;
};
