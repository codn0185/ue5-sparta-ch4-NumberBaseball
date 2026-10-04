#include "Player/NBPlayerState.h"

#include "Net/UnrealNetwork.h"

ANBPlayerState::ANBPlayerState()
{
	bReplicates = true;
}

void ANBPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerNameString);
}
