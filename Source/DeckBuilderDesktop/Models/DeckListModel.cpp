// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "DeckListModel.h"
#include "CardDeckModel.h"
#include "Models/CardListModel.h"
#include "Models/CardDeckModel.h"
#include "Models/CardDeckExporterJSON.h"
#include "Models/CardDeckImporterJSON.h"
#include "ParagonSaveGame.h"
#include "Kismet/GameplayStatics.h"

UDeckListModel::UDeckListModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	DeckSlotsCount = 28;
	DeckSlots.AddZeroed(DeckSlotsCount);
}

UCardDeckModel* UDeckListModel::CreateNewDeck()
{
	for (size_t i = 0; i < DeckSlots.Num(); i++)
	{
		if (DeckSlots[i] == nullptr)
		{
			auto CardDeckModel = NewObject<UCardDeckModel>(GetTransientPackage(), NAME_None);
			DeckSlots[i] = CardDeckModel;
			return CardDeckModel;
		}
	}
	return nullptr;
}

bool UDeckListModel::SaveDecks()
{
	auto Exporter = NewObject<UCardDeckExporterJSON>(GetTransientPackage(), NAME_None);
	TArray<FString> DecksAsJSON;

	for (auto CardDeckModel : DeckSlots)
	{
		if (CardDeckModel)
		{
			FString JSONData;
			if (!Exporter->ExportDeckModel(CardDeckModel, JSONData))
			{
				return false;
			}
			DecksAsJSON.Add(JSONData);
		}
		else
		{
			DecksAsJSON.Add(FString());
		}
	}

	UParagonSaveGame* SaveGame = Cast<UParagonSaveGame>(UGameplayStatics::CreateSaveGameObject(UParagonSaveGame::StaticClass()));
	SaveGame->DecksAsJSON = DecksAsJSON;
	return UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("DefaultSaveGameSlot"), 0);
}

bool UDeckListModel::LoadDecks(UCardListModel* CardListModel)
{
	TArray<UCardDeckModel*> Result;
	UParagonSaveGame* LoadedSaveGame = Cast<UParagonSaveGame>(UGameplayStatics::CreateSaveGameObject(UParagonSaveGame::StaticClass()));
	LoadedSaveGame = Cast<UParagonSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("DefaultSaveGameSlot"), 0));
	if (!LoadedSaveGame)
	{
		return false;
	}

	auto Importer = NewObject<UCardDeckImporterJSON>(GetTransientPackage(), NAME_None);

	for (auto& DeckAsJSON : LoadedSaveGame->DecksAsJSON)
	{
		if (DeckAsJSON.IsEmpty())
		{
			Result.Add(nullptr);
		}
		else
		{
			TArray<FString> ImportErrors;
			UCardDeckModel* CardDeckModel = Importer->ImportDeckModel(DeckAsJSON, CardListModel, ImportErrors);
			if (!CardDeckModel)
			{
				return false;
			}
			Result.Add(CardDeckModel);
		}
	}

	DeckSlots = Result;
	return true;
}
