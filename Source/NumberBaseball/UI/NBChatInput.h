#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NBChatInput.generated.h"

class UEditableTextBox;

UCLASS()
class NUMBERBASEBALL_API UNBChatInput : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox_ChatInput;

  protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

  protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
