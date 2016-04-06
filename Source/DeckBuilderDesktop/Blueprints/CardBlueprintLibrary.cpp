// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardBlueprintLibrary.h"


TArray<FCardStat> UCardBlueprintLibrary::GetValidCardStats(FCardData CardData)
{
	TArray<FCardStat> validStats;

	for (TFieldIterator<UProperty> PropIt(CardData.StaticStruct()); PropIt; ++PropIt)
	{
		UProperty* Property = *PropIt;
		// Do something with the property
		if (Property->IsA(UFloatProperty::StaticClass()))
		{
			UFloatProperty *NumericProp = CastChecked<UFloatProperty>(Property);
			float value = NumericProp->GetPropertyValue_InContainer(&CardData);
			if (value != 0.0)
			{
				FCardStat stat;
				stat.Type = NumericProp->GetFName();
				stat.Value = FString::Printf(TEXT("%f"), value);
				validStats.Add(stat);
			}
		}
		else if (Property->IsA(UStrProperty::StaticClass()))
		{
			UStrProperty *StrProp = CastChecked<UStrProperty>(Property);
			FString Value = StrProp->GetPropertyValue_InContainer(&CardData);
			if (Value.Len() > 0) 
			{
				FCardStat stat;
				stat.Type = StrProp->GetFName();
				stat.Value = Value;
				validStats.Add(stat);
			}
		}
	}

	return validStats;
}

TArray<FCardData> UCardBlueprintLibrary::CardsDataContainingProperty(TArray<FCardData> CardsData, FName PropertyName)
{
	return CardsData.FilterByPredicate([=](const FCardData& CardData) {
		 UProperty* Property = CardData.StaticStruct()->FindPropertyByName(PropertyName);
		 if (Property) 
		 {
			 if (Property->IsA(UFloatProperty::StaticClass()))
			 {
				 UFloatProperty *NumericProp = CastChecked<UFloatProperty>(Property);
				 float value = NumericProp->GetPropertyValue_InContainer(&CardData);
				 if (value != -0.0 && value != 0.0)
				 {
					 return true;
				 }
			 }
			 else if (Property->IsA(UStrProperty::StaticClass()))
			 {
				 UStrProperty *StrProp = CastChecked<UStrProperty>(Property);
				 FString Value = StrProp->GetPropertyValue_InContainer(&CardData);
				 if (Value.Len() > 0)
				 {
					 return true;
				 }
			 }
		 }
		 return false;
	});
}


TArray<FCardData> UCardBlueprintLibrary::CardsDataContainingPropertyValue(TArray<FCardData> CardsData, FName PropertyName, FString PropertyValue)
{
	return CardsData.FilterByPredicate([=](const FCardData& CardData) {
		UProperty* Property = CardData.StaticStruct()->FindPropertyByName(PropertyName);
		if (Property)
		{
			if (Property->IsA(UFloatProperty::StaticClass()))
			{
				UFloatProperty *NumericProp = CastChecked<UFloatProperty>(Property);
				float value = NumericProp->GetPropertyValue_InContainer(&CardData);
				if (value != -0.0 && value != 0.0)
				{
					return PropertyValue.Equals(FString::Printf(TEXT("%f"), value));
				}
			}
			else if (Property->IsA(UStrProperty::StaticClass()))
			{
				UStrProperty *StrProp = CastChecked<UStrProperty>(Property);
				FString Value = StrProp->GetPropertyValue_InContainer(&CardData);
				if (Value.Len() > 0)
				{
					return PropertyValue.Equals(Value);
				}
			}
		}
		return false;
	});
}

TArray<FCardData> UCardBlueprintLibrary::CardsDataWithCardType(TArray<FCardData> CardsData, FString CardType)
{
	if (CardType.Len() > 0)
	{
		return CardsData.FilterByPredicate([=](const FCardData& CardData)
		{
			return CardData.Type == CardType;
		});
	}
	else
	{
		return CardsData;
	}
}

TArray<FCardData> UCardBlueprintLibrary::CardsDataWithCardNameSubstring(TArray<FCardData> CardsData, FString Substring)
{
	if (Substring.Len() > 0)
	{
		return CardsData.FilterByPredicate([=](const FCardData& CardData)
		{
			return CardData.CardName.Contains(Substring);
		});
	}
	else
	{
		return CardsData;
	}
}

TArray<FStatData> UCardBlueprintLibrary::FilterableStatsData(TArray<FStatData> StatsData)
{
	TArray<FStatData> FilterableStats = StatsData.FilterByPredicate([=](const FStatData& StatData) {
		return !StatData.FilterGroup.IsEmpty();
	});


	FilterableStats.StableSort([=](const FStatData& LHS, const FStatData& RHS) {
		return LHS.FilterGroupIndex < RHS.FilterGroupIndex;
	});

	FilterableStats.StableSort([=](const FStatData& LHS, const FStatData& RHS) {
		return LHS.FilterGroup.Compare(RHS.FilterGroup) < 0;
	});

	return FilterableStats;
}

FName UCardBlueprintLibrary::MakeValidTableRowName(const FString& InString)
{
	return DataTableUtils::MakeValidName(InString);
}

UTexture2D* UCardBlueprintLibrary::LoadCardTextureNamed(const FString& CardName)
{
	FString TexturePath = FString::Printf(TEXT("/Game/Art/Cards/T_%s.T_%s"), *CardName, *CardName);
	return LoadObject<UTexture2D>(NULL, *TexturePath, NULL, LOAD_None, NULL);
}
