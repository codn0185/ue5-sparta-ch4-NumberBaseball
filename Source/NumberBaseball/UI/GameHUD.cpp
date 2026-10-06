#include "UI/GameHUD.h"

#include "UI/NBChatWidget.h"

void UGameHUD::NativeConstruct()
{
	// 이벤트 바인딩 추가
	ChatWidget->OnTextCommitted.BindUObject(this, &ThisClass::OnChatInputTextCommitted);
}

void UGameHUD::AddChat(const FNBChatData& ChatData)
{
	ChatWidget->Add(ChatData);
}

void UGameHUD::ClearChat()
{
	ChatWidget->Clear();
}

void UGameHUD::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	// 브로드캐스트 송출
	OnTextCommitted.ExecuteIfBound(Text, CommitMethod);
}
