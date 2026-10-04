#include "Game/NBGameModeBase.h"

#include "Algo/RandomShuffle.h"
#include "Game/NBGameStateBase.h"

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

void ANBGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	ANBGameStateBase* NBGameStateBase = GetGameState<ANBGameStateBase>();
	if (IsValid(NBGameStateBase))
	{
		NBGameStateBase->MulticastRPCBroadcastLoginMessage(GetNameSafe(NewPlayer));
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

bool ANBGameModeBase::IsGuessNumberString(const FString& InNumberString)
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

	return false;
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
