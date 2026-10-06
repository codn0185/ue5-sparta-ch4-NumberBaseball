#include "UI/NBChatWidget.h"

#include "UI/Data/NBChatItemData.h"
#include "UI/NBChatInput.h"
#include "UI/NBChatList.h"

void UNBChatWidget::NativeConstruct()
{
	// 이벤트 바인딩 추가
	ChatInput->OnTextCommitted.BindUObject(this, &ThisClass::OnChatInputTextCommitted);
}

void UNBChatWidget::Add(const FNBChatData& ChatData)
{
	UNBChatItemData* ChatItemData = NewObject<UNBChatItemData>(this);
	ChatItemData->ChatData = ChatData;

	ChatList->Add(ChatItemData);
}

void UNBChatWidget::Clear()
{
	ChatList->Clear();
}

void UNBChatWidget::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	// 브로드캐스트 송출
	OnTextCommitted.ExecuteIfBound(Text, CommitMethod);
}
