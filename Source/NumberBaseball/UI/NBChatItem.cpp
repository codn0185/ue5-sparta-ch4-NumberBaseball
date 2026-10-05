#include "UI/NBChatItem.h"

#include "Components/TextBlock.h"
#include "UI/Data/NBChatItemData.h"

void UNBChatItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UNBChatItemData* ChatItemData = Cast<UNBChatItemData>(ListItemObject);
	if (!IsValid(ChatItemData))
	{
		return;
	}

	TextBlock_Name->SetText(FText::Format(FText::FromString(TEXT("[{0}]")), ChatItemData->NameText));
	TextBlock_Name->SetColorAndOpacity(ChatItemData->NameColor);

	TextBlock_Message->SetText(ChatItemData->MessageText);
	TextBlock_Message->SetColorAndOpacity(ChatItemData->MessageColor);
}
