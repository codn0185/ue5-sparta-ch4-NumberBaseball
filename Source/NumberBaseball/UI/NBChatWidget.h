#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NBChatWidget.generated.h"

struct FNBChatData;

UCLASS()
class NUMBERBASEBALL_API UNBChatWidget : public UUserWidget
{
	GENERATED_BODY()

  public:
	FOnTextCommitted OnTextCommitted;

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UNBChatList> ChatList;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UNBChatInput> ChatInput;

  protected:
	virtual void NativeConstruct() override;

  public:
	// 채팅 추가
	void Add(const FNBChatData& ChatData);

	// 채팅 클리어
	void Clear();

  protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
