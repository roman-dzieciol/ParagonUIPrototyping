// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "UserProfileFunctionLibrary.h"
#include "Models/UserProfileModel.h"

UUserProfileModel* UUserProfileFunctionLibrary::ConstructSampleUserProfile()
{
	UUserProfileModel* UserProfileModel = NewObject<UUserProfileModel>(GetTransientPackage(), NAME_None);
	UserProfileModel->Nick = TEXT("Neai01");
	UserProfileModel->Level = 27;
	UserProfileModel->Coins = 100;
	UserProfileModel->Reputation = 10500;
	UserProfileModel->BoostExperienceAmount = 100;
	UserProfileModel->BoostExperienceWins = 3;
	UserProfileModel->BoostExperienceTime = FDateTime::Now() + FTimespan(24, 0, 0);
	return UserProfileModel;
}


