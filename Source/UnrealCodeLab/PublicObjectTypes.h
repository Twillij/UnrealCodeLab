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
	// Set to true to ignore all the other flags and allow functions to handle the checks instead.
	bool bUseDefaultFlags = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseDefaultFlags"))
	bool bBlockLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseDefaultFlags"))
	bool bBlockUnlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseDefaultFlags"))
	bool bBlockStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseDefaultFlags"))
	bool bBlockAbandoned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseDefaultFlags"))
	bool bBlockFailed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bUseDefaultFlags"))
	bool bBlockCompleted;
};
