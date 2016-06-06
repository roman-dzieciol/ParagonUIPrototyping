// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DataTables/FHeroAbilityData.h"
#include "HeroAbilityModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UHeroAbilityModel : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability")
		FString AbilityName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability")
		TArray<float> ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability")
		TArray<float> Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability")
		UTexture2D* IconTexture;
	
public:

	static UHeroAbilityModel* ConstructFromHeroAbilityData(const FHeroAbilityData& HeroAbilityData);
	
};
