#include "Player/NBPlayerController.h"

#include "EngineUtils.h"
#include "NumberBaseball.h"

#include "Game/NBGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Player/NBPlayerState.h"
#include "UI/NBGameHUD.h"

ANBPlayerController::ANBPlayerController()
{
	// 레플리케이션 활성화
	bReplicates = true;
}

void ANBPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ANBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
	{
		return;
	}

	// UI 입력 모드
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	// 마우스 커서 보이기
	bShowMouseCursor = true;

	// GameHUD 위젯 생성
	if (IsValid(GameHUDClass))
	{
		GameHUDInstance = CreateWidget<UNBGameHUD>(this, GameHUDClass);
		if (IsValid(GameHUDInstance))
		{
			GameHUDInstance->AddToViewport();

			// 델리게이트 바인딩
			GameHUDInstance->OnTextCommitted.BindUObject(this, &ThisClass::OnTextCommitted);
		}
	}
}

void ANBPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController())
	{
		ANBPlayerState* NBPlayerState = GetPlayerState<ANBPlayerState>();
		if (IsValid(NBPlayerState))
		{
			// 서버에 입력한 채팅 메시지 전달
			ServerRPCPrintChatMessageString(InChatMessageString);
		}
	}
}

void ANBPlayerController::CheckChatMessageString(const FString& InChatMessageString)
{
	NBFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ANBPlayerController::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	SetChatMessageString(Text.ToString());
}

void ANBPlayerController::ClientRPCResetUI_Implementation()
{
	// UI 초기화
	if (IsValid(GameHUDInstance))
	{
		GameHUDInstance->ClearChat();
		GameHUDInstance->ClearGuessResult();
	}
}

void ANBPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	CheckChatMessageString(InChatMessageString);
}

void ANBPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	if (IsValid(GameMode))
	{
		ANBGameModeBase* NBGameMode = Cast<ANBGameModeBase>(GameMode);
		if (IsValid(NBGameMode))
		{
			NBGameMode->CheckChatMessageString(this, InChatMessageString);
		}
	}
}

void ANBPlayerController::ClientRPCReceiveChat_Implementation(const FNBChatData& ChatData)
{
	if (IsValid(GameHUDInstance))
	{
		GameHUDInstance->AddChat(ChatData);
	}
}

void ANBPlayerController::ClientRPCClearChat_Implementation()
{
	if (IsValid(GameHUDInstance))
	{
		GameHUDInstance->ClearChat();
	}
}

void ANBPlayerController::ClientRPCShowNotification_Implementation(const FText& NotificationText, const float Lifetime)
{
	if (IsValid(GameHUDInstance))
	{
		GameHUDInstance->ShowNotification(NotificationText, Lifetime);
	}
}

void ANBPlayerController::ClientRPCReceiveGuessResult_Implementation(const FNBGuessResultData& GuessResultData)
{
	if (IsValid(GameHUDInstance))
	{
		GameHUDInstance->AddGuessResult(GuessResultData);
	}
}

void ANBPlayerController::ClientRPCClearGuessResult_Implementation(const FNBGuessResultData& GuessResultData)
{
	if (IsValid(GameHUDInstance))
	{
		GameHUDInstance->ClearGuessResult();
	}
}
