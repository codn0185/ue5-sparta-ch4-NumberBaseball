#include "UI/GameHUD.h"

#include "UI/NBChatWidget.h"
#include "UI/NBNotificationWidget.h"

void UGameHUD::NativeConstruct()
{
	// 이벤트 바인딩 추가
	ChatWidget->OnTextCommitted.BindUObject(this, &ThisClass::OnChatInputTextCommitted);
}

void UGameHUD::AddChat(const FNBChatData& ChatData)
{
	if (IsValid(ChatWidget))
	{
		ChatWidget->Add(ChatData);
	}
}

void UGameHUD::ClearChat()
{
	if (IsValid(ChatWidget))
	{
		ChatWidget->Clear();
	}
}

void UGameHUD::ShowNotification(const FText& NotifiactionText, const float Lifetime)
{
	if (IsValid(NotificationWidget))
	{
		NotificationWidget->SetNotificationText(NotifiactionText, Lifetime);
	}
}

void UGameHUD::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	// 채팅 입력 델리게이트 송출
	OnTextCommitted.ExecuteIfBound(Text, CommitMethod);
}
