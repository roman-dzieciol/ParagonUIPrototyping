// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TableViewBase.h"
#include "CardListTileView.generated.h"

/**
 * Duplicated from UTileView, removed the Experimental tag.
 */
UCLASS()
class DECKBUILDERDESKTOP_API UCardListTileView : public UTableViewBase
{
	GENERATED_UCLASS_BODY()

public:

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		float ItemWidth;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		float ItemHeight;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
		TArray<UObject*> Items;

	/**  */
	UPROPERTY(EditAnywhere, Category = Content)
		TEnumAsByte<ESelectionMode::Type> SelectionMode;

	/**  */
	UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
		FOnGenerateRowUObject OnGenerateTileEvent;

public:

	/** Set item width */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetItemWidth(float Width);

	/** Set item height */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetItemHeight(float Height);

	/** Refreshes the list */
	UFUNCTION(BlueprintCallable, Category = "Behavior")
	void RequestListRefresh();

	/** Set the scroll offset of this view (in items) */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetScrollOffset(const float InScrollOffset);

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void SetSelection(UObject* SoleSelectedItem, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);

	// UVisual interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UVisual interface

#if WITH_EDITOR
	virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;
#endif
public:
	// Delegate for selection notification
	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSelectionChangedUObject, UObject*, Item);

	UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
	FOnSelectionChangedUObject OnSelectionChangedEvent;

protected:
	TSharedRef<ITableRow> HandleOnGenerateTile(UObject* Item, const TSharedRef< STableViewBase >& OwnerTable) const;
	void HandleOnSelectionChanged(UObject* Item, ESelectInfo::Type SelectInfo) const;


	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

protected:
	TSharedPtr< STileView< UObject* > > MyTileView;
};
