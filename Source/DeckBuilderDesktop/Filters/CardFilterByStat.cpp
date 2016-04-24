// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardFilterByStat.h"


UCardFilterByStat::UCardFilterByStat(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	static FName FNAME_CardFilterByStat_Generic(TEXT("Stat"));
	FilterName = FNAME_CardFilterByStat_Generic;
}

bool UCardFilterByStat::IsMatching(UCardModel* CardModel) const
{
	if (CardModel)
	{
		auto StatModel = CardModel->GetStatByName(StatName);
		if (StatModel != nullptr)
		{
			if (bEqualValue)
			{
				return StatModel->Value.ToString().Equals(StatContains);
			}
			else
			{
				return StatContains.IsEmpty() || StatModel->Value.ToString().Contains(StatContains);
			}
		}
	}
	return false;
}


FText UCardFilterByStat::GetDisplayName() const
{
	if (!LocalizedName.IsEmpty())
	{
		return LocalizedName;
	}

	if (!StatContains.IsEmpty())
	{
		return FText::FromString(StatName);
	}
	else
	{
		return FText::FromName(FilterName);
	}
}

FText UCardFilterByStat::GetDisplayValue() const
{
	if (!LocalizedValue.IsEmpty())
	{
		return LocalizedValue;
	}

	if (!StatContains.IsEmpty())
	{
		return FText::FromString(StatContains);
	} 
	else
	{
		return FText::FromString(StatName);
	}
}

TArray<UCardFilter*> UCardFilterByStat::FindFiltersMatching(FName FilterName, FText DisplayName, FText DisplayValue) const
{
	TArray<UCardFilter*> Result;
	if ((FilterName == NAME_None || this->FilterName.IsEqual(FilterName)) &&
		(DisplayName.IsEmpty() || LocalizedName.EqualTo(DisplayName)) &&
		(DisplayValue.IsEmpty() || LocalizedValue.EqualTo(DisplayValue)))
	{
		Result.Add(const_cast<UCardFilterByStat*>(this));
	}
	return Result;
}


UCardFilterByStat* UCardFilterByStat::ConstructCardFilterByStat(FName InFilterType, FString InStatName, FString InStatValue, bool InIsEqualValue)
{
	UCardFilterByStat* Filter = NewObject<UCardFilterByStat>(GetTransientPackage(), NAME_None);
	Filter->FilterName = InFilterType;
	Filter->LocalizedName = FText::FromString(InStatName);
	Filter->LocalizedValue = FText::FromString(InStatValue);
	Filter->StatName = InStatName;
	Filter->StatContains = InStatValue;
	Filter->bEqualValue = InIsEqualValue;
	return Filter;
}


