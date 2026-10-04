#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"

#include "NBGameModeBase.generated.h"

class ANBPlayerController;

// 숫자야구 판정 결과 구조체
USTRUCT()
struct FResult
{
	GENERATED_BODY()

  public:
	bool bIsCorrect = false; // 정답인지 여부
	int32 StrikeCount = 0;   // 숫자+자리 맞춘 개수
	int32 BallCount = 0;     // 숫자만 맞춘 개수

  public:
	FString ToString() const;
};

UCLASS()
class NUMBERBASEBALL_API ANBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

  protected:
	// 숫자 길이 (1 ~ 9)
	int32 NumberLength;

  public:
	ANBGameModeBase();

  protected:
	virtual void OnPostLogin(AController* NewPlayer) override;

  public:
	// 정답 숫자 생성 (중복되지 않는 숫자로 이루어짐)
	FString GenerateSecretNumber();
	// 유효한 추측 숫자인지 여부 (중복되지 않았는지, 개수가 다르지 않는지 등 확인)
	bool IsGuessNumberString(const FString& InNumberString) const;
	// 정답 판정
	FResult JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);
};
