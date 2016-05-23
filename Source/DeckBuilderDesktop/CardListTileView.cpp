// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardListTileView.h"
#include "UMGStyle.h"

#define LOCTEXT_NAMESPACE "UMG"

/////////////////////////////////////////////////////
// UCardListTileView

UCardListTileView::UCardListTileView(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = true;

	ItemWidth = 128.0f;
	ItemHeight = 128.0f;
	SelectionMode = ESelectionMode::Single;
}

TSharedRef<SWidget> UCardListTileView::RebuildWidget()
{
	MyTileView = SNew(STileView< UObject* >)
		.SelectionMode(SelectionMode)
		.ListItemsSource(&Items)
		.ItemWidth(ItemWidth)
		.ItemHeight(ItemHeight)
		.OnGenerateTile(BIND_UOBJECT_DELEGATE(STileView< UObject* >::FOnGenerateRow, HandleOnGenerateTile))
		.OnSelectionChanged(BIND_UOBJECT_DELEGATE(STileView< UObject* >::FOnSelectionChanged, HandleOnSelectionChanged))
		//.OnSelectionChanged(this, &SSocketManager::SocketSelectionChanged_Execute)
		//.OnContextMenuOpening(this, &SSocketManager::OnContextMenuOpening)
		//.OnItemScrolledIntoView(this, &SSocketManager::OnItemScrolledIntoView)
		//	.HeaderRow
		//	(
		//		SNew(SHeaderRow)
		//		.Visibility(EVisibility::Collapsed)
		//		+ SHeaderRow::Column(TEXT("Socket"))
		//	);
		;

	return BuildDesignTimeWidget(MyTileView.ToSharedRef());
}

TSharedRef<ITableRow> UCardListTileView::HandleOnGenerateTile(UObject* Item, const TSharedRef< STableViewBase >& OwnerTable) const
{
	// Call the user's delegate to see if they want to generate a custom widget bound to the data source.
	if (OnGenerateTileEvent.IsBound())
	{
		UWidget* Widget = OnGenerateTileEvent.Execute(Item);
		if (Widget != NULL)
		{
			return SNew(STableRow< UObject* >, OwnerTable)
				[
					Widget->TakeWidget()
				];
		}
	}

	// If a row wasn't generated just create the default one, a simple text block of the item's name.
	return SNew(STableRow< UObject* >, OwnerTable)
		[
			SNew(STextBlock).Text(Item ? FText::FromString(Item->GetName()) : LOCTEXT("null", "null"))
		];
}

void UCardListTileView::HandleOnSelectionChanged(UObject* Item, ESelectInfo::Type SelectInfo) const
{
	if (OnSelectionChangedEvent.IsBound())
	{
		OnSelectionChangedEvent.Execute(Item);
	}
}

void UCardListTileView::SetItemWidth(float Width)
{
	MyTileView->SetItemWidth(Width);
}

void UCardListTileView::SetItemHeight(float Height)
{
	MyTileView->SetItemHeight(Height);
}

void UCardListTileView::RequestListRefresh()
{
	MyTileView->RequestListRefresh();
}

void UCardListTileView::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyTileView.Reset();
}

#if WITH_EDITOR

const FSlateBrush* UCardListTileView::GetEditorIcon()
{
	return FUMGStyle::Get().GetBrush("Widget.TileView");
}

const FText UCardListTileView::GetPaletteCategory()
{
	return LOCTEXT("Misc", "Misc");
}

#endif


void UCardListTileView::SetScrollOffset(const float InScrollOffset)
{
	MyTileView->SetScrollOffset(InScrollOffset);
}

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE

