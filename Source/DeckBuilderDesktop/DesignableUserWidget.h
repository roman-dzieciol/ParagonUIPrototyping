// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "DesignableUserWidget.generated.h"

/**
 * UserWidget that can update itself when its default property is changed in the editor.
 */
UCLASS(BlueprintType, Blueprintable)
class DECKBUILDERDESKTOP_API UDesignableUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * This is called after a widget is constructed and properties are synchronized.
	 * It can also be called by the editor to update modified state.
	 * Override this event in blueprint to update the widget after a default property is modified.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "User Interface")
		void OnSynchronizeProperties();

	/**
	* Gets current time cursor position for a playing animation
	*
	* @param Animation The animation currently being played
	* @return Current time cursor position for a playing animation
	*/
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")
		bool GetAnimationTimeCursorPosition(const UWidgetAnimation* Animation, float& OutTimeCursorPosition) const;

	/**
	* Gets time cursor position for continuing playing animation from current state (i.e. reverse on hover animation)
	*
	* @param Animation The animation currently being played
	* @param DefaultStartTime The time cursor position to return if animation isn't playing currently
	* @param PlayMode The play mode to calculate start time for.
	* @return Time cursor position for continuing playing animation from current state
	*/
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface|Animation")
		float GetAnimationCurrentStartTimeForPlayMode(const UWidgetAnimation* Animation, float DefaultStartTime, EUMGSequencePlayMode::Type PlayMode) const;

public:
	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface
};
