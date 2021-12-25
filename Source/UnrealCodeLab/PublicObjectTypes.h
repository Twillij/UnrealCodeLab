#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PublicObjectTypes.generated.h"

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
	Locked,
	Unlocked,
	Accepted,
	Abandoned,
	Failed,
	Completed,
};

USTRUCT(BlueprintType)
struct FQuestRewards
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Exp;
};