// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardFilterFactory.h"
#include "Filters/CardFilterByStat.h"


UCardFilter* UCardFilterFactory::ConstructFilterByCostValue(int32 CostValue)
{
	return UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Cost")), TEXT("Cost"), FString::FromInt(CostValue), true);
}
