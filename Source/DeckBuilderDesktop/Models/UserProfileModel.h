// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "UserProfileModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UUserProfileModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		FString Nick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 Reputation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 Coins;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 BoostExperienceAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 BoostExperienceWins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		FDateTime BoostExperienceTime;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 BoostReputationAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 BoostReputationWins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		FDateTime BoostReputationTime;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		FTimespan TimePlayed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 TotalGames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 TotalWins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 TowerTakedowns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 InhibitorTakedowns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 CoreTakedowns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 HeroKills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 HeroAssists;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 HarvestersPlaced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Profile")
		int32 HarvestersDestroyed;
	
};
