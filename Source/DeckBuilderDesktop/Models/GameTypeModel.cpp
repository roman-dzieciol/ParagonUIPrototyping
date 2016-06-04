// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "GameTypeModel.h"

UGameTypeModel::UGameTypeModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UGameTypeModel* UGameTypeModel::ConstructFromGameTypeData(const FGameTypeData& GameTypeData)
{
	auto GameTypeModel = NewObject<UGameTypeModel>(GetTransientPackage(), NAME_None);
	GameTypeModel->GameTypeName = GameTypeData.GameTypeName;
	GameTypeModel->Title = GameTypeData.Title;
	GameTypeModel->Description = GameTypeData.Description;
	return GameTypeModel;
}
