#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NBChatWidget.generated.h"

UCLASS()
class NUMBERBASEBALL_API UNBChatWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UNBChatList> ChatList;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UNBChatInput> ChatInput;
};
