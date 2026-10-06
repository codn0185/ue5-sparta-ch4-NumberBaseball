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

	FNBChatData ChatData = ChatItemData->ChatData;

	TextBlock_Name->SetText(FText::Format(FText::FromString(TEXT("[{0}]")), ChatData.NameText));
	TextBlock_Name->SetColorAndOpacity(ChatData.NameColor);

	TextBlock_Message->SetText(ChatData.MessageText);
	TextBlock_Message->SetColorAndOpacity(ChatData.MessageColor);

	UE_LOG(LogTemp, Warning, TEXT("채팅 아이템 추가 - [%s] %s"), *ChatData.NameText.ToString(), *ChatData.MessageText.ToString());
}
