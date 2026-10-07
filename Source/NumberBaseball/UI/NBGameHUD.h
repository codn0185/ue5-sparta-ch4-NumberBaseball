#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NBGameHUD.generated.h"

class UNBChatWidget;
class UNBNotificationWidget;
class UNBGuessResultWidget;

struct FNBChatData;
struct FNBGuessResultData;

UCLASS()
class NUMBERBASEBALL_API UNBGameHUD : public UUserWidget
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

	// 유추 결과 위젯
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UNBGuessResultWidget> GuessResultWidget;

  protected:
	virtual void NativeConstruct() override;

  public:
	// 채팅 추가
	void AddChat(const FNBChatData& ChatData);
	// 채팅 클리어
	void ClearChat();

	// 공지 설정
	void ShowNotification(const FText& NotifiactionText, const float Lifetime = 0.f);

	// 유추 결과 추가
	void AddGuessResult(const FNBGuessResultData& GuessResultData);
	// 유추 결과 클리어
	void ClearGuessResult();

  protected:
	// 채팅 입력 이벤트
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
