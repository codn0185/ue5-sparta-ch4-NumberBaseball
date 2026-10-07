#include "UI/NBGuessResultItem.h"

#include "Components/TextBlock.h"
#include "UI/Data/NBGuessResultItemData.h"

void UNBGuessResultItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UNBGuessResultItemData* GuessResultItemData = Cast<UNBGuessResultItemData>(ListItemObject);
	if (!IsValid(GuessResultItemData))
	{
		return;
	}

	FNBGuessResultData GuessResultData = GuessResultItemData->GuessResultData;

	TextBlock_CurrentTryCount->SetText(FText::AsNumber(GuessResultData.CurrentTryCount));
	TextBlock_MaxTryCount->SetText(FText::AsNumber(GuessResultData.MaxTryCount));

	TextBlock_GuessNumber->SetText(FText::FromString(GuessResultData.GuessNumberString));

	TextBlock_StrikeCount->SetText(FText::AsNumber(GuessResultData.StrikeCount));
	TextBlock_BallCount->SetText(FText::AsNumber(GuessResultData.BallCount));
}
