// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DataTables/FHeroData.h"
#include "HeroModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UHeroModel : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		FString HeroName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		UTexture2D* AvatarTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
		TArray<FString> Affinities;
	
public:

	static UHeroModel* ConstructFromHeroData(const FHeroData& HeroData);
	
};
