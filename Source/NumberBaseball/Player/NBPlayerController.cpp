#include "Player/NBPlayerController.h"

#include "NumberBaseball.h"

#include "Kismet/KismetSystemLibrary.h"
#include "UI/NBChatInput.h"

void ANBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass))
	{
		ChatInputWidgetInstance = CreateWidget<UNBChatInput>(this, ChatInputWidgetClass);

		if (IsValid(ChatInputWidgetInstance))
		{
			ChatInputWidgetInstance->AddToViewport();

			// 델리게이트 바인딩
			ChatInputWidgetInstance->OnTextCommitted.BindUObject(this, &ThisClass::OnTextCommitted);
		}
	}
}

void ANBPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	PrintChatMessageString(ChatMessageString);
}

void ANBPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	NBFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ANBPlayerController::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	SetChatMessageString(Text.ToString());
}
