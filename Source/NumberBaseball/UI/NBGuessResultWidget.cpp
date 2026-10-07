#include "UI/NBGuessResultWidget.h"

#include "Components/ListView.h"
#include "UI/Data/NBGuessResultItemData.h"

void UNBGuessResultWidget::Add(const FNBGuessResultData& GuessResultData)
{
	UNBGuessResultItemData* GuessResultItemData = NewObject<UNBGuessResultItemData>(this);
	GuessResultItemData->GuessResultData = GuessResultData;

	ListView_GuessResult->AddItem(GuessResultItemData);
}

void UNBGuessResultWidget::Clear()
{
	ListView_GuessResult->ClearListItems();
}
