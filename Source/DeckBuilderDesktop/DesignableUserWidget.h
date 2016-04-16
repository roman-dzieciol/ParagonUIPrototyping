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

public:
	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface
};
