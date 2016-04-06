
#include "DeckBuilderDesktop.h"
#include "CardsFunctionLibrary.h"

TArray<UCardStatModel*> UCardsFunctionLibrary::ConstructExistingCardStatModelsFromTableData(const FCardData& CardData)
{
	TArray<UCardStatModel*> StatModels;

	for (TFieldIterator<UProperty> PropIt(CardData.StaticStruct()); PropIt; ++PropIt)
	{
		auto Property = *PropIt;

		// Check basic property types for non-default values
		// TODO: Generic UStruct compare to default/empty?

		// Check numeric properties
		if (Property->IsA(UNumericProperty::StaticClass()))
		{
			auto NumericProperty = CastChecked<UNumericProperty>(Property);
			if (NumericProperty->IsFloatingPoint())
			{
				auto Value = NumericProperty->GetFloatingPointPropertyValue(Property->ContainerPtrToValuePtr<float>(&CardData));
				if (Value != 0.0)
				{
					auto StatModel = NewObject<UCardStatModel>(GetTransientPackage(), Property->GetFName());
					StatModel->Type = FText::FromName(Property->GetFName());
					StatModel->Value = FText::FromString(FString::Printf(TEXT("%f"), Value));
					StatModel->Icon = nullptr;
					StatModels.Add(StatModel);
				}
			}
			else if (NumericProperty->IsInteger())
			{
				auto Value = NumericProperty->GetUnsignedIntPropertyValue(Property->ContainerPtrToValuePtr<float>(&CardData));
				if (Value != 0)
				{
					auto StatModel = NewObject<UCardStatModel>(GetTransientPackage(), Property->GetFName());
					StatModel->Type = FText::FromName(Property->GetFName());
					StatModel->Value = FText::FromString(FString::Printf(TEXT("%d"), Value));
					StatModel->Icon = nullptr;
					StatModels.Add(StatModel);
				}
			}
		}

		// Check string property
		else if (Property->IsA(UStrProperty::StaticClass()))
		{
			UStrProperty* StrProperty = CastChecked<UStrProperty>(Property);
			auto Value = StrProperty->GetPropertyValue_InContainer(&CardData);
			if (Value.Len() > 0)
			{
				auto StatModel = NewObject<UCardStatModel>(GetTransientPackage(), Property->GetFName());
				StatModel->Type = FText::FromName(Property->GetFName());
				StatModel->Value = FText::FromString(Value);
				StatModel->Icon = nullptr;
				StatModels.Add(StatModel);
			}
		}

		// Check name property
		else if (Property->IsA(UNameProperty::StaticClass()))
		{
			UNameProperty* NameProperty = CastChecked<UNameProperty>(Property);
			auto Value = NameProperty->GetPropertyValue_InContainer(&CardData);
			if (Value != NAME_None)
			{
				auto StatModel = NewObject<UCardStatModel>(GetTransientPackage(), Property->GetFName());
				StatModel->Type = FText::FromName(Property->GetFName());
				StatModel->Value = FText::FromString(Value.ToString());
				StatModel->Icon = nullptr;
				StatModels.Add(StatModel);
			}
		}

		// Check text property
		else if (Property->IsA(UTextProperty::StaticClass()))
		{
			UTextProperty* TextProperty = CastChecked<UTextProperty>(Property);
			auto Value = TextProperty->GetPropertyValue_InContainer(&CardData);
			if (!Value.IsEmpty())
			{
				auto StatModel = NewObject<UCardStatModel>(GetTransientPackage(), Property->GetFName());
				StatModel->Type = FText::FromName(Property->GetFName());
				StatModel->Value = FText::FromString(Value.ToString());
				StatModel->Icon = nullptr;
				StatModels.Add(StatModel);
			}
		}
	}
	return StatModels;
}

UCardModel* UCardsFunctionLibrary::ConstructCardModelFromTableData(const FCardData& CardData)
{
	auto CardModel = NewObject<UCardModel>(GetTransientPackage(), CardData.StaticStruct()->GetFName());
	CardModel->CardName = FText::FromString(CardData.CardName);
	CardModel->Cost = CardData.Cost;
	CardModel->Type = FText::FromString(CardData.Type);
	CardModel->Affinity = FText::FromString(CardData.Affinity);
	CardModel->Rarity = FText::FromString(CardData.Rarity);
	CardModel->Stats = UCardsFunctionLibrary::ConstructExistingCardStatModelsFromTableData(CardData);
	return CardModel;
}
