#include "Player/NBPlayerController.h"

#include "EngineUtils.h"
#include "NumberBaseball.h"

#include "Game/NBGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Player/NBPlayerState.h"
#include "UI/NBChatWidget.h"
#include "UI/NBNotificationWidget.h"

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

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	// 채팅 위젯 인스턴스 생성
	if (IsValid(ChatWidgetClass))
	{
		ChatWidgetInstance = CreateWidget<UNBChatWidget>(this, ChatWidgetClass);

		if (IsValid(ChatWidgetInstance))
		{
			ChatWidgetInstance->AddToViewport(1);

			// 델리게이트 바인딩
			ChatWidgetInstance->OnTextCommitted.BindUObject(this, &ThisClass::OnTextCommitted);
		}
	}

	// 알림 위젯 인스턴스 생성
	if (IsValid(UNBNotificationWidgetClass))
	{
		UNBNotificationWidgetInstance = CreateWidget<UNBNotificationWidget>(this, UNBNotificationWidgetClass);
		if (IsValid(UNBNotificationWidgetInstance))
		{
			UNBNotificationWidgetInstance->AddToViewport(0);
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

void ANBPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	NBFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ANBPlayerController::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	SetChatMessageString(Text.ToString());
}

void ANBPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ANBPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	if (IsValid(GameMode))
	{
		ANBGameModeBase* NBGameMode = Cast<ANBGameModeBase>(GameMode);
		if (IsValid(NBGameMode))
		{
			NBGameMode->PrintChatMessageString(this, InChatMessageString);
		}
	}
}

void ANBPlayerController::ClientRPCReceiveChat_Implementation(const FNBChatData& ChatData)
{
	if (IsValid(ChatWidgetInstance))
	{
		ChatWidgetInstance->Add(ChatData);
	}
}

void ANBPlayerController::ClientRPCClearChat_Implementation()
{
	if (IsValid(ChatWidgetInstance))
	{
		ChatWidgetInstance->Clear();
	}
}

void ANBPlayerController::ClientRPCShowNotification_Implementation(const FText& NotificationText, const float Lifetime)
{
	if (IsValid(UNBNotificationWidgetInstance))
	{
		UNBNotificationWidgetInstance->SetNotificationText(NotificationText, Lifetime);
	}
}
