// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "DesignableUserWidget.h"

void UDesignableUserWidget::OnSynchronizeProperties_Implementation() 
{
}

void UDesignableUserWidget::SynchronizeProperties() {
	Super::SynchronizeProperties();
	OnSynchronizeProperties();
}