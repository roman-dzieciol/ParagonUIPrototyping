// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DeckBuilderDesktop.h"

#include "RichTextBlockDecorator.h"
#include "OSPRichTextBlock.h"

#define LOCTEXT_NAMESPACE "OSP"

/////////////////////////////////////////////////////
// URichTextBlock

UOSPRichTextBlock::UOSPRichTextBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		Font = FSlateFontInfo(RobotoFontObj.Object, 12, FName("Regular"));
	}
	Color = FLinearColor::White;

	Decorators.Add(ObjectInitializer.CreateOptionalDefaultSubobject<URichTextBlockDecorator>(this, FName("DefaultDecorator")));
}

void UOSPRichTextBlock::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyRichTextBlock.Reset();
}

TSharedRef<SWidget> UOSPRichTextBlock::RebuildWidget()
{
	//+ OnHyperlinkClicked = FSlateHyperlinkRun::FOnClick::CreateStatic(&RichTextHelper::OnBrowserLinkClicked, AsShared());
	//+ FHyperlinkDecorator::Create(TEXT("browser"), OnHyperlinkClicked))
	//+MakeShareable(new FDefaultRichTextDecorator(Font, Color));

	DefaultStyle.SetFont(Font);
	DefaultStyle.SetColorAndOpacity(Color);

	TArray< TSharedRef< class ITextDecorator > > CreatedDecorators;

	for ( URichTextBlockDecorator* Decorator : Decorators )
	{
		if ( Decorator )
		{
			CreatedDecorators.Add(Decorator->CreateDecorator(Font, Color));
		}
	}

	MyRichTextBlock =
		SNew(SRichTextBlock)
		.TextStyle(&DefaultStyle)
		.Decorators(CreatedDecorators);
	
	return MyRichTextBlock.ToSharedRef();
}

void UOSPRichTextBlock::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	TAttribute<FText> TextBinding = OPTIONAL_BINDING(FText, Text);

	MyRichTextBlock->SetText(TextBinding);

	Super::SynchronizeTextLayoutProperties( *MyRichTextBlock );
}


FText UOSPRichTextBlock::GetText() const
{
	if (MyRichTextBlock.IsValid())
	{
		return MyRichTextBlock->GetText();
	}

	return Text;
}

void UOSPRichTextBlock::SetText(FText InText)
{
	Text = InText;
	if (MyRichTextBlock.IsValid())
	{
		MyRichTextBlock->SetText(Text);
	}
	Super::SynchronizeTextLayoutProperties(*MyRichTextBlock);
}

#if WITH_EDITOR

const FText UOSPRichTextBlock::GetPaletteCategory()
{
	return LOCTEXT("Common", "Common");
}

#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
