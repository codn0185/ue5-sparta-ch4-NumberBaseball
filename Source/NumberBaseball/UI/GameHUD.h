#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "GameHUD.generated.h"

class UNBChatWidget;
class UNBNotificationWidget;

struct FNBChatData;

UCLASS()
class NUMBERBASEBALL_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

  public:
	FOnTextCommitted OnTextCommitted;

  protected:
	// 채팅 위젯
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UNBChatWidget> ChatWidget;

	// 공지 위젯
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UNBNotificationWidget> NotificationWidget;

  protected:
	virtual void NativeConstruct() override;

  public:
	// 채팅 추가
	void AddChat(const FNBChatData& ChatData);
	// 채팅 클리어
	void ClearChat();

	// 공지 설정
	void ShowNotification(const FText& NotifiactionText, const float Lifetime = 0.f);

  protected:
	// 채팅 입력 이벤트
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
