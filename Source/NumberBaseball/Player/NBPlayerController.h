#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "NBPlayerController.generated.h"

class UNBChatInput;

UCLASS()
class NUMBERBASEBALL_API ANBPlayerController : public APlayerController
{
	GENERATED_BODY()

  protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNBChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UNBChatInput> ChatInputWidgetInstance;

  protected:
	virtual void BeginPlay() override;
};
