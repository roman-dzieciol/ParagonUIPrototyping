// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DataTables/FHeroSkinData.h"
#include "HeroSkinModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UHeroSkinModel : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin")
		FString SkinName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin")
		UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin")
		TAssetPtr<class UTexture2D> PreviewTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin")
		int32 Cost;
	
public:

	static UHeroSkinModel* ConstructFromHeroSkinData(const FHeroSkinData& HeroSkinData);
	
};
