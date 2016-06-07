// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "TextWidgetTypes.h"
#include "OSPRichTextBlock.generated.h"

/**
 * The rich text block
 *
 * * Fancy Text
 * * No Children
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UOSPRichTextBlock : public UTextLayoutWidget
{
	GENERATED_BODY()

public:
	UOSPRichTextBlock(const FObjectInitializer& ObjectInitializer);
	
	// UWidget interface
	virtual void SynchronizeProperties() override;
	// End of UWidget interface

	// UVisual interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UVisual interface

#if WITH_EDITOR
	// UWidget interface
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface
#endif

	/** The text to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Content, meta=( MultiLine="true" ))
	FText Text;

	/** A bindable delegate to allow logic to drive the text of the widget */
	UPROPERTY()
	FGetText TextDelegate;

	/** The default font for the text. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	FSlateFontInfo Font;

	/** The default color for the text. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	FLinearColor Color;

	UPROPERTY(EditAnywhere, Instanced, Category=Decorators)
	TArray<class URichTextBlockDecorator*> Decorators;

	/**
	* Gets the widget text
	* @return The widget text
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget", meta = (DisplayName = "GetText (RichText)"))
		FText GetText() const;

	/**
	* Directly sets the widget text.
	* Warning: This will wipe any binding created for the Text property!
	* @param InText The text to assign to the widget
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget", meta = (DisplayName = "SetText (RichText)"))
		void SetText(FText InText);

protected:
	FTextBlockStyle DefaultStyle;

	/** Native Slate Widget */
	TSharedPtr<SRichTextBlock> MyRichTextBlock;

	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface
};
