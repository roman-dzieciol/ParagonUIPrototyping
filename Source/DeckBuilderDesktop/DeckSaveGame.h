// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "DeckSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DECKBUILDERDESKTOP_API UDeckSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString JSONData;
};
