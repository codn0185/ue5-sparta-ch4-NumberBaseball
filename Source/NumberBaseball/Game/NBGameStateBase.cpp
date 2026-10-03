#include "Game/NBGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/NBPlayerController.h"

void ANBGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (!HasAuthority())
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); // 0번(로컬) 플레이어 컨트롤러
		if (IsValid(PlayerController))
		{
			ANBPlayerController* NBPlayerController = Cast<ANBPlayerController>(PlayerController);
			if (IsValid(NBPlayerController))
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				NBPlayerController->PrintChatMessageString(NotificationString);
			}
		}
	}
}
