// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "ParagonSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DECKBUILDERDESKTOP_API UParagonSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FString> DecksAsJSON;
	
};
