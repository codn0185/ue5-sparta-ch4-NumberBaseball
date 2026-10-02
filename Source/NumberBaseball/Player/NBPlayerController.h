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

	// 채팅 메시지 캐시
	FString ChatMessageString;

  protected:
	virtual void BeginPlay() override;

  public:
	// 채팅 메시지 캐시 설정
	void SetChatMessageString(const FString& InChatMessageString);

	// 채팅 메시지 출력
	void PrintChatMessageString(const FString& InChatMessageString);
};
