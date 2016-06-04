// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "GameTypeListModel.h"
#include "GameTypeModel.h"


UGameTypeListModel::UGameTypeListModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UGameTypeListModel* UGameTypeListModel::ConstructFromGameTypeDataTable(UDataTable* GameTypeDataTable)
{
	check(GameTypeDataTable != nullptr);

	auto GameTypeListModel = NewObject<UGameTypeListModel>(GetTransientPackage(), NAME_None);
	for (auto RowName : GameTypeDataTable->GetRowNames())
	{
		FGameTypeData* Row = GameTypeDataTable->FindRow<FGameTypeData>(RowName, TEXT(" UGameTypeListModel::ConstructFromGameTypeDataTable"));
		if (Row != nullptr)
		{
			UGameTypeModel* GameTypeModel = UGameTypeModel::ConstructFromGameTypeData(*Row);
			if (GameTypeModel != nullptr)
			{
				GameTypeListModel->GameTypeModels.Add(GameTypeModel);
			}
		}
	}
	return GameTypeListModel;
}
