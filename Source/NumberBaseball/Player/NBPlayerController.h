#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "NBPlayerController.generated.h"

class UNBGameHUD;

struct FNBChatData;
struct FNBGuessResultData;

UCLASS()
class NUMBERBASEBALL_API ANBPlayerController : public APlayerController
{
	GENERATED_BODY()

  protected:
	// GameHUD 위젯
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNBGameHUD> GameHUDClass;
	UPROPERTY()
	TObjectPtr<UNBGameHUD> GameHUDInstance;

	// 채팅 메시지 캐시
	FString ChatMessageString;

  public:
	ANBPlayerController();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

  protected:
	virtual void BeginPlay() override;

  public:
	// 채팅 메시지 캐시 설정
	void SetChatMessageString(const FString& InChatMessageString);

	// 채팅 메시지 출력
	void CheckChatMessageString(const FString& InChatMessageString);

  protected:
	// 채팅 텍스트 커밋 시 콜백
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

  public:
	// 게임 리셋 (클라이언트 실행 RPC)
	UFUNCTION(Client, Reliable)
	void ClientRPCResetUI();

	// 채팅 메시지 출력 (클라이언트 실행 RPC)
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	// 채팅 메시지 출력 (서버 실행 RPC)
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);

	// 채팅 메시지 받기 (클라이언트 실행 RPC)
	UFUNCTION(Client, Reliable)
	void ClientRPCReceiveChat(const FNBChatData& ChatData);

	// 채팅 메시지 클리어 (클라이언트 실행 RPC)
	UFUNCTION(Client, Reliable)
	void ClientRPCClearChat();

	// 공지 알림 (클라이언트 실행 RPC)
	UFUNCTION(Client, Reliable)
	void ClientRPCShowNotification(const FText& NotificationText, const float Lifetime = 0.f);

	// 유추 결과 받기 (클라이언트 실행 RPC)
	UFUNCTION(Client, Reliable)
	void ClientRPCReceiveGuessResult(const FNBGuessResultData& GuessResultData);

	// 유추 결과 클리어(클라이언트 실행 RPC)
	UFUNCTION(Client, Reliable)
	void ClientRPCClearGuessResult(const FNBGuessResultData& GuessResultData);
};
