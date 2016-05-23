// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardDeckExporterJSON.h"
#include "Json.h"
#include "CardDeckModel.h"
#include "HeroModel.h"

UCardDeckExporterJSON::UCardDeckExporterJSON(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCardDeckExporterJSON::ExportDeckModel(UCardDeckModel* DeckModel, FString& OutExportText)
{
	TSharedRef< TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR> > > JsonWriter = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR> >::Create(&OutExportText);

	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue(TEXT("DeckName"), DeckModel->DeckName);
	JsonWriter->WriteValue(TEXT("HeroName"), DeckModel->HeroModel->HeroName);
	JsonWriter->WriteArrayStart(TEXT("Cards"));

	for (auto& DeckItemModel : DeckModel->DeckItems)
	{
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue(TEXT("CardName"), DeckItemModel->CardModel->CardName.ToString());
		if (DeckItemModel->LinkedDeckItems.Num() > 0)
		{
			JsonWriter->WriteArrayStart(TEXT("LinkedCards"));
			for (auto& LinkedDeckItemModel : DeckItemModel->LinkedDeckItems)
			{
				JsonWriter->WriteValue(LinkedDeckItemModel->CardModel->CardName.ToString());
			}
			JsonWriter->WriteArrayEnd();
		}
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteArrayEnd(); // Cards
	JsonWriter->WriteObjectEnd(); // Deck
	JsonWriter->Close();
	return true;
}


