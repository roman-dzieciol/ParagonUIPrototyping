// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardFilterByStatContains.h"


UCardFilterByStatContains::UCardFilterByStatContains(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	static FName FNAME_CardFilterByStatContains_Generic(TEXT("StatContains"));
	FilterName = FNAME_CardFilterByStatContains_Generic;
}

bool UCardFilterByStatContains::IsMatching(UCardModel* CardModel) const
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


FText UCardFilterByStatContains::GetDisplayName() const
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

FText UCardFilterByStatContains::GetDisplayValue() const
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




