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
struct FQuestStatusBlockFlags
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// Set to true to ignore all the other flags and allow functions to handle the checks instead.
	bool bUseDefaultFlags = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockUnlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockAccepted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockAbandoned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockFailed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockCompleted;
};
