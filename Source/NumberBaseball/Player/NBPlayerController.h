#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "NBPlayerController.generated.h"

class UUserWidget;
class UNBChatInput;

UCLASS()
class NUMBERBASEBALL_API ANBPlayerController : public APlayerController
{
	GENERATED_BODY()

  protected:
	// 알림 텍스트 위젯
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> NotificationTextWidgetInstance;

	// 채팅 입력 위젯
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNBChatInput> ChatInputWidgetClass;
	UPROPERTY()
	TObjectPtr<UNBChatInput> ChatInputWidgetInstance;

	// 채팅 메시지 캐시
	FString ChatMessageString;

  public:
	// 알림 텍스트
	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;

  protected:
	// 알림 텍스트 제거 타이머 핸들
	FTimerHandle NotificationTimerHandle;

  public:
	ANBPlayerController();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

  protected:
	virtual void BeginPlay() override;

  public:
	// 알림 텍스트 설정
	void SetNotificationText(const FText& InNotificationText, const float LifeTime = 0.f);

  public:
	// 채팅 메시지 캐시 설정
	void SetChatMessageString(const FString& InChatMessageString);

	// 채팅 메시지 출력
	void PrintChatMessageString(const FString& InChatMessageString);

  protected:
	// 채팅 텍스트 커밋 시 콜백
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

  public:
	// 채팅 메시지 출략 (클라이언트 실행 RPC)
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	// 채팅 메시지 출략 (서버 실행 RPC)
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);
};
