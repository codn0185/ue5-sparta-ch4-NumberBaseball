#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"

#include "NBPlayerState.generated.h"

UCLASS()
class NUMBERBASEBALL_API ANBPlayerState : public APlayerState
{
	GENERATED_BODY()

  public:
	// 플레이어 이름
	UPROPERTY(Replicated)
	FString PlayerNameString;

	// 최대 추측 횟수
	UPROPERTY(Replicated)
	int32 MaxGuessCount;

	// 현재 추측 횟수
	UPROPERTY(Replicated)
	int32 CurrentGuessCount;

  public:
	ANBPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
