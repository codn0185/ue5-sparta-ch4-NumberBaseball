#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "GameHUD.generated.h"

class UNBChatWidget;

struct FNBChatData;

UCLASS()
class NUMBERBASEBALL_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

  public:
	FOnTextCommitted OnTextCommitted;

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UNBChatWidget> ChatWidget;

  protected:
	virtual void NativeConstruct() override;

  public:
	// 채팅 추가
	void AddChat(const FNBChatData& ChatData);

	// 채팅 클리어
	void ClearChat();

  protected:
	// 채팅 입력 이벤트
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
