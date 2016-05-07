
#include "DeckBuilderDesktop.h"
#include "Blueprints/CardsFunctionLibrary.h"
#include "CardStatModel.h"
#include "DataTables/FStatData.h"

UCardStatModel::UCardStatModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool operator == (const UCardStatModel& LHS, const UCardStatModel& RHS)
{
	return LHS.Type.EqualTo(RHS.Type)
		&& LHS.Value.EqualTo(RHS.Value)
		&& LHS.Icon == RHS.Icon;
}

UCardStatModel* UCardStatModel::ConstructWithName(const FName& StatName, const FText& StatValue, const FStatData& StatData)
{
	auto StatModel = NewObject<UCardStatModel>(GetTransientPackage(), NAME_None);
	StatModel->Type = FText::FromName(StatName);
	StatModel->Value = StatValue;
	StatModel->BonusType = FText::FromString(StatData.BonusType);
	StatModel->Icon = StatData.Icon;
	return StatModel;
}

UCardStatModel* UCardStatModel::ConstructFromProperty(UProperty* Property, void const * Container, const FStatData& StatData)
{
	if (Property == nullptr || Container == nullptr)
	{
		return nullptr;
	}
	
	// Check basic property types for non-default values
	// TODO: Generic UStruct compare to default/empty?

	// Check numeric properties
	if (Property->IsA(UNumericProperty::StaticClass()))
	{
		auto NumericProperty = CastChecked<UNumericProperty>(Property);
		if (NumericProperty->IsFloatingPoint())
		{
			auto Value = NumericProperty->GetFloatingPointPropertyValue(Property->ContainerPtrToValuePtr<float>(Container));
			if (Value != 0.0)
			{
				return UCardStatModel::ConstructWithName(Property->GetFName(), FText::FromString(FString::Printf(TEXT("%f"), Value)), StatData);
			}
		}
		else if (NumericProperty->IsInteger())
		{
			auto Value = NumericProperty->GetUnsignedIntPropertyValue(Property->ContainerPtrToValuePtr<int32>(Container));
			if (Value != 0)
			{
				return UCardStatModel::ConstructWithName(Property->GetFName(), FText::FromString(FString::Printf(TEXT("%d"), Value)), StatData);
			}
		}
	}

	// Check string property
	else if (Property->IsA(UStrProperty::StaticClass()))
	{
		UStrProperty* StrProperty = CastChecked<UStrProperty>(Property);
		auto Value = StrProperty->GetPropertyValue_InContainer(Container);
		if (Value.Len() > 0)
		{
			return UCardStatModel::ConstructWithName(Property->GetFName(), FText::FromString(Value), StatData);
		}
	}

	// Check name property
	else if (Property->IsA(UNameProperty::StaticClass()))
	{
		UNameProperty* NameProperty = CastChecked<UNameProperty>(Property);
		auto Value = NameProperty->GetPropertyValue_InContainer(Container);
		if (Value != NAME_None)
		{
			return UCardStatModel::ConstructWithName(Property->GetFName(), FText::FromString(Value.ToString()), StatData);
		}
	}

	// Check text property
	else if (Property->IsA(UTextProperty::StaticClass()))
	{
		UTextProperty* TextProperty = CastChecked<UTextProperty>(Property);
		auto Value = TextProperty->GetPropertyValue_InContainer(Container);
		if (!Value.IsEmpty())
		{
			return UCardStatModel::ConstructWithName(Property->GetFName(), FText::FromString(Value.ToString()), StatData);
		}
	}

	return nullptr;
}

TArray<UCardStatModel*> UCardStatModel::ConstructModelsFromCardData(const FCardData& CardData, const FString& BonusType, UDataTable* StatDataTable)
{
	TArray<UCardStatModel*> StatModels;
	for (TFieldIterator<UProperty> PropIt(CardData.StaticStruct()); PropIt; ++PropIt)
	{
		auto Property = *PropIt;
		auto StatData = StatDataTable->FindRow<FStatData>(Property->GetFName(), TEXT("UCardsFunctionLibrary::ConstructExistingCardStatModelsFromTableData"), true);
		if (StatData != nullptr && (BonusType.IsEmpty() || BonusType == StatData->BonusType))
		{
			const FCardData LocalCardData = CardData;
			auto StatModel = UCardStatModel::ConstructFromProperty(Property, &LocalCardData, *StatData);
			if (StatModel != nullptr)
			{
				StatModels.Add(StatModel);
			}
		}
	}
	return StatModels;
}

