// Fill out your copyright notice in the Description page of Project Settings.

#define LOCTEXT_NAMESPACE "NS" 

#include "DeckBuilderDesktop.h"
#include "SMainWindow.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainWindow::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SNew(STextBlock)
		.Text(LOCTEXT("BlockingVolumeMenu", "Create Blocking Volume"))
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE