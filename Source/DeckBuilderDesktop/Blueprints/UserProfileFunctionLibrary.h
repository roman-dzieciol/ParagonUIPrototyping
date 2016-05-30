// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UserProfileFunctionLibrary.generated.h"

class UUserProfileModel;

/**
 * 
 */
UCLASS()
class DECKBUILDERDESKTOP_API UUserProfileFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = "User Profile Function Library")
		static UUserProfileModel* ConstructSampleUserProfile();

	
};
