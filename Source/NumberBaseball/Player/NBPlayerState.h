#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"

#include "NBPlayerState.generated.h"

UCLASS()
class NUMBERBASEBALL_API ANBPlayerState : public APlayerState
{
	GENERATED_BODY()

  public:
	ANBPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

  public:
	// 플레이어 이름
	UPROPERTY(Replicated)
	FString PlayerNameString;
};
