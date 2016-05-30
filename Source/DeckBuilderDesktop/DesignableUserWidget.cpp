// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "DesignableUserWidget.h"
#include "UMGSequencePlayer.h"
#include "WidgetAnimation.h"

void UDesignableUserWidget::OnSynchronizeProperties_Implementation() 
{
}

void UDesignableUserWidget::SynchronizeProperties() {
	Super::SynchronizeProperties();
	OnSynchronizeProperties();
}


bool UDesignableUserWidget::GetAnimationTimeCursorPosition(const UWidgetAnimation* Animation, float& OutTimeCursorPosition) const
{
	if (Animation)
	{
		UUMGSequencePlayer* const* FoundPlayer = ActiveSequencePlayers.FindByPredicate(
			[&](const UUMGSequencePlayer* Player)
		{
			return Player->GetAnimation() == Animation;
		});

		if (FoundPlayer)
		{
			OutTimeCursorPosition = (*FoundPlayer)->GetTimeCursorPosition();
			return true;
		}
	}
	return false;
}

float UDesignableUserWidget::GetAnimationCurrentStartTimeForPlayMode(const UWidgetAnimation* Animation, float DefaultStartTime, EUMGSequencePlayMode::Type PlayMode) const
{
	float TimeCursorPosition = DefaultStartTime;
	if (Animation && GetAnimationTimeCursorPosition(Animation, TimeCursorPosition))
	{
		if (EUMGSequencePlayMode::Reverse == PlayMode)
		{
			TimeCursorPosition = (Animation->GetEndTime() - Animation->GetStartTime()) - TimeCursorPosition;
		}
	}
	return TimeCursorPosition;
}