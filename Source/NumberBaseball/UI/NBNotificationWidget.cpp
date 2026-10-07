#include "UI/NBNotificationWidget.h"

#include "Components/TextBlock.h"

void UNBNotificationWidget::NativeConstruct()
{
	// 빈 텍스트 설정
	TextBlock_Notification->SetText(FText());
}

void UNBNotificationWidget::SetNotificationText(const FText& NotifiactionText, const float Lifetime)
{
	// 기존 타이머 제거
	GetWorld()->GetTimerManager().ClearTimer(NotificationTimerHandle);

	// 텍스트 설정
	TextBlock_Notification->SetText(NotifiactionText);

	// 수명 설정
	if (Lifetime > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(
			NotificationTimerHandle,
			this,
			&UNBNotificationWidget::Clear,
			Lifetime,
			false);
	}
}

void UNBNotificationWidget::Clear()
{
	// 기존 타이머 제거
	GetWorld()->GetTimerManager().ClearTimer(NotificationTimerHandle);

	// 텍스트 제거
	TextBlock_Notification->SetText(FText());
}
