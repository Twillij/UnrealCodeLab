#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PublicObjectTypes.generated.h"

UENUM(BlueprintType)
enum class EProgressStatus : uint8
{
	Locked,
	Unlocked,
	Started,
	Abandoned,
	Failed,
	Completed,
};

USTRUCT(BlueprintType)
struct FProgressStatusBlockFlags
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockUnlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockAbandoned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockFailed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockCompleted;
};
