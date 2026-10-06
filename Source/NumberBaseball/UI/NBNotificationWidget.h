#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NBNotificationWidget.generated.h"

class UTextBlock;

UCLASS()
class NUMBERBASEBALL_API UNBNotificationWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Notification;

	// 수명 관리 타이머 핸들
	FTimerHandle NotificationTimerHandle;

  public:
	void SetNotificationText(const FText& NotifiactionText, const float Lifetime = 0.f);

	void Clear();
};
