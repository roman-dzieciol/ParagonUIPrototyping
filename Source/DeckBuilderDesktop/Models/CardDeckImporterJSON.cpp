// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardDeckImporterJSON.h"
#include "CardDeckModel.h"
#include "CardListModel.h"


UCardDeckImporterJSON::UCardDeckImporterJSON(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UCardDeckModel* UCardDeckImporterJSON::ImportDeckModel(const FString& InJSONData, UCardListModel* CardListModel, TArray<FString>& OutErrors)
{
	if (InJSONData.IsEmpty())
	{
		return nullptr;
	}

	auto CardDeckModel = NewObject<UCardDeckModel>(GetTransientPackage(), NAME_None);

	const TSharedRef< TJsonReader<TCHAR> > JsonReader = TJsonReaderFactory<TCHAR>::Create(InJSONData);
	TSharedPtr<FJsonObject> DeckObject;
	if (!FJsonSerializer::Deserialize(JsonReader, DeckObject))
	{
		OutErrors.Add(FString::Printf(TEXT("Failed to parse the JSON data. Error: %s"), *JsonReader->GetErrorMessage()));
		return nullptr;
	}

	FString DeckName;
	if (!DeckObject->TryGetStringField(TEXT("DeckName"), DeckName))
	{
		OutErrors.Add(FString::Printf(TEXT("DeckName not present")));
		return nullptr;
	}
	CardDeckModel->DeckName = DeckName;

	const TArray< TSharedPtr<FJsonValue> >* Cards = nullptr;
	if (!DeckObject->TryGetArrayField(TEXT("Cards"), Cards))
	{
		OutErrors.Add(FString::Printf(TEXT("Cards array not present")));
		return nullptr;
	}

	TMap<UDeckItemModel*, TArray<FString>> CardLinks;

	for (TSharedPtr<FJsonValue> JsonValue : *Cards)
	{
		const TSharedPtr<FJsonObject>* JsonObject = nullptr;
		if (!JsonValue->TryGetObject(JsonObject))
		{
			OutErrors.Add(FString::Printf(TEXT("Failed to parse card item")));
			return nullptr;
		}

		FString CardName;
		if (!(*JsonObject)->TryGetStringField(TEXT("CardName"), CardName))
		{
			OutErrors.Add(FString::Printf(TEXT("Failed to parse card item name")));
			return nullptr;
		}

		UCardModel* CardModel = CardListModel->GetCardModelNamed(CardName);
		if (!CardModel)
		{
			OutErrors.Add(FString::Printf(TEXT("Unknown card: %s"), *CardName));
			return nullptr;
		}

		UDeckItemModel* DeckItemModel = UDeckItemModel::ConstructDeckItemModel(CardModel);
		if (!DeckItemModel)
		{
			OutErrors.Add(FString::Printf(TEXT("Failed to create deck item for: %s"), *CardName));
			return nullptr;
		}

		if (!CardDeckModel->AddDeckItem(DeckItemModel))
		{
			OutErrors.Add(FString::Printf(TEXT("Failed to add card to deck: %s"), *CardName));
			return nullptr;
		}
	
		TArray<FString> LinkedCardNames;
		if ((*JsonObject)->TryGetStringArrayField(TEXT("LinkedCards"), LinkedCardNames))
		{
			UE_LOG(Deck, Verbose, TEXT("linked: %s"), *FString::Join(LinkedCardNames, TEXT(", ")));
			CardLinks.Add(DeckItemModel, LinkedCardNames);
		}
	}

	// 2nd pass: link cards
	for (auto& Item : CardLinks)
	{
		auto DeckItemModel = Item.Key;
		for (auto& LinkedCardName : Item.Value)
		{
			UCardModel* LinkedCardModel = CardListModel->GetCardModelNamed(LinkedCardName);
			if (!LinkedCardModel)
			{
				OutErrors.Add(FString::Printf(TEXT("Unknown card: %s"), *LinkedCardName));
				return nullptr;
			}

			TArray<UDeckItemModel*> UnlinkedDeckItemModels = CardDeckModel->GetUnlinkedDeckItemsForCardModel(LinkedCardModel);
			UDeckItemModel* UnlinkedDeckItemModel = UnlinkedDeckItemModels.Num() > 0 ? UnlinkedDeckItemModels[0] : nullptr;
			if (!UnlinkedDeckItemModel)
			{
				OutErrors.Add(FString::Printf(TEXT("Not enough unlinked cards: %s"), *LinkedCardName));
				return nullptr;
			}

			if (!CardDeckModel->LinkDeckItemWith(UnlinkedDeckItemModel, DeckItemModel))
			{
				OutErrors.Add(FString::Printf(TEXT("Failed to add card to deck: %s and link with: %s"), *LinkedCardName, *DeckItemModel->CardModel->CardName.ToString()));
				return nullptr;
			}
		}
	}

	return CardDeckModel;
}

