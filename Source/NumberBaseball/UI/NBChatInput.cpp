#include "UI/NBChatInput.h"

#include "Components/EditableTextBox.h"

void UNBChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	// 이벤트 바인딩 추가
	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UNBChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	// 이벤트 바인딩 제거
	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UNBChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	// Enter 키 입력
	if (CommitMethod == ETextCommit::OnEnter)
	{
		OnTextCommitted.ExecuteIfBound(Text, CommitMethod);

		EditableTextBox_ChatInput->SetText(FText::GetEmpty());

		GetWorld()->GetTimerManager().SetTimerForNextTick(
			FTimerDelegate::CreateLambda(
				[this]()
				{
					EditableTextBox_ChatInput->SetKeyboardFocus();
				}));
	}
}
