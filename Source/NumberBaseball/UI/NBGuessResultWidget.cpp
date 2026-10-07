#include "UI/NBGuessResultWidget.h"

#include "Components/ListView.h"
#include "UI/Data/NBGuessResultItemData.h"

void UNBGuessResultWidget::Add(const FString GuessNumberString, const int32 StrikeCount, const int32 BallCount)
{
	UNBGuessResultItemData* GuessResultItemData = NewObject<UNBGuessResultItemData>(this);

	ListView_GuessResult->AddItem(GuessResultItemData);
}

void UNBGuessResultWidget::Clear()
{
	ListView_GuessResult->ClearListItems();
}
