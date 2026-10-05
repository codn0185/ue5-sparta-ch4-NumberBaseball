#include "Game/NBGameModeBase.h"

#include "Algo/RandomShuffle.h"
#include "Game/NBGameStateBase.h"
#include "Player/NBPlayerController.h"
#include "Player/NBPlayerState.h"

FString FResult::ToString() const
{
	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

ANBGameModeBase::ANBGameModeBase()
{
	NumberLength = 3;
}

void ANBGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateSecretNumber();
	UE_LOG(LogTemp, Error, TEXT("%s"), *SecretNumberString);
}

void ANBGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	// ANBPlayerController 확인
	ANBPlayerController* NBPlayerController = Cast<ANBPlayerController>(NewPlayer);
	if (IsValid(NBPlayerController))
	{
		// 플레이어 추가
		AllPlayerControllers.Add(NBPlayerController);

		// 알림 텍스트 설정
		// NBPlayerController->NotificationText = FText::FromString(TEXT("Connected to the game server."));
		NBPlayerController->SetNotificationText(FText::FromString(TEXT("Connected to the game server.")), 3.f);

		// PlayerState 확인
		ANBPlayerState* NBPlayerState = NBPlayerController->GetPlayerState<ANBPlayerState>();
		if (IsValid(NBPlayerState))
		{
			// 플레이어 이름 설정
			NBPlayerState->PlayerNameString = TEXT("Player") + FString::FromInt(AllPlayerControllers.Num());
		}

		// GameState 확인
		ANBGameStateBase* NBGameState = GetGameState<ANBGameStateBase>();
		if (IsValid(NBGameState))
		{
			// 플레이어 입장 메시지 출력
			NBGameState->MulticastRPCBroadcastLoginMessage(NBPlayerState->PlayerNameString);
		}
	}
}

FString ANBGameModeBase::GenerateSecretNumber()
{
	// 1~9까지의 숫자 배열
	TArray<int32> Numbers;
	for (int32 Number = 1; Number <= 9; ++Number)
	{
		Numbers.Add(Number);
	}

	// 랜덤 섞기
	Algo::RandomShuffle(Numbers);

	// 개수 설정
	Numbers.SetNum(NumberLength);

	// 문자열 전환
	FString SecretNumber;
	for (const int32 Number : Numbers)
	{
		SecretNumber.AppendInt(Number);
	}

	return SecretNumber;
}

bool ANBGameModeBase::IsGuessNumberString(const FString& InNumberString) const
{
	// 개수 확인
	if (InNumberString.Len() != NumberLength)
	{
		return false;
	}

	// 숫자가 아닌 것 포함 or 중복된 숫자 포함
	TSet<TCHAR> UniqueNumbers;
	for (const TCHAR C : InNumberString)
	{
		// 숫자가 아님
		if (!FChar::IsDigit(C) || C == '0')
		{
			return false;
		}

		// 중복 여부 판단
		bool bIsAlreadyInSet = false;
		UniqueNumbers.Add(C, &bIsAlreadyInSet);

		// 중복된 숫자가 포함됨
		if (bIsAlreadyInSet)
		{
			return false;
		}
	}

	return true;
}

FResult ANBGameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	// 결과 구조체
	FResult Result;

	for (int32 Index = 0; Index < NumberLength; ++Index)
	{
		// 스트라이크 판별 - 숫자와 자리 모두 같음
		if (InSecretNumberString[Index] == InGuessNumberString[Index])
		{
			Result.StrikeCount++;
		}
		// 볼 판별 - 숫자만 같고 자리는 다음
		else if (InSecretNumberString.Contains(FString(1, &InGuessNumberString[Index])))
		{
			Result.BallCount++;
		}
	}

	// 정답 여부 판별
	Result.bIsCorrect = Result.StrikeCount == NumberLength;

	return Result;
}

void ANBGameModeBase::PrintChatMessageString(ANBPlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	// PlayerController 유효성 검증
	if (!IsValid(InChattingPlayerController))
	{
		return;
	}

	// PlayerState 유효성 검증
	ANBPlayerState* NBPlayerState = InChattingPlayerController->GetPlayerState<ANBPlayerState>();
	if (!IsValid(NBPlayerState))
	{
		return;
	}

	// 정답 유추 채팅
	if (IsGuessNumberString(InChatMessageString))
	{
		// 유추 횟수 증가
		IncreaseGuessCount(InChattingPlayerController);
		const FString PrefixMessageString = NBPlayerState->GetPlayerInfoString() + TEXT(": ");

		// 모든 플레이어에 유추 결과 메시지 출력
		FResult Result = JudgeResult(SecretNumberString, InChatMessageString);
		FString JudgeResultString = Result.ToString();
		for (TObjectPtr<ANBPlayerController> NBPlayerController : AllPlayerControllers)
		{
			if (IsValid(NBPlayerController) == true)
			{
				const FString CombinedMessageString = PrefixMessageString + InChatMessageString + TEXT(" -> ") + JudgeResultString;
				NBPlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);
			}
		}
	}
	// 일반 채팅
	else
	{
		// 모든 플레이어에 일반 채팅 메시지 출력
		const FString PrefixMessageString = NBPlayerState->GetPlayerInfoString() + TEXT(": ");
		for (TObjectPtr<ANBPlayerController> NBPlayerController : AllPlayerControllers)
		{
			if (IsValid(NBPlayerController))
			{
				const FString CombinedMessageString = PrefixMessageString + InChatMessageString;
				NBPlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);
			}
		}
	}
}

bool ANBGameModeBase::IsGuessChat(const FString& InChatMessageString, FString& OutGuessNumberString) const
{
	int Index = InChatMessageString.Len() - NumberLength;
	FString GuessNumberString = InChatMessageString.RightChop(Index);

	if (IsGuessNumberString(GuessNumberString))
	{
		OutGuessNumberString = GuessNumberString;
		return true;
	}

	return false;
}

void ANBGameModeBase::IncreaseGuessCount(ANBPlayerController* InChattingPlayerController)
{
	// InChattingPlayerController 유효성 검증
	if (!IsValid(InChattingPlayerController))
	{
		return;
	}

	// PlayerState 확인
	ANBPlayerState* NBPlayerState = InChattingPlayerController->GetPlayerState<ANBPlayerState>();
	if (!IsValid(NBPlayerState))
	{
		return;
	}

	NBPlayerState->CurrentGuessCount++;
}

void ANBGameModeBase::ResetGame()
{
	// 새로운 숫자 생성
	SecretNumberString = GenerateSecretNumber();
	UE_LOG(LogTemp, Error, TEXT("%s"), *SecretNumberString);

	// 모든 플레이어의 추측 횟수 초기화
	for (const auto& NBPlayerController : AllPlayerControllers)
	{
		ANBPlayerState* NBPlayerState = Cast<ANBPlayerState>(NBPlayerController);
		if (IsValid(NBPlayerState))
		{
			NBPlayerState->CurrentGuessCount = 0;
		}
	}
}
