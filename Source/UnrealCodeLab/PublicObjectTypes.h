#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PublicObjectTypes.generated.h"

class UQuest;
class UQuestObjective;

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel
};

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

USTRUCT(BlueprintType)
struct FQuestObjectiveInfo
{
	GENERATED_BODY()

public:
	FQuestObjectiveInfo() {}
	FQuestObjectiveInfo(UQuestObjective* ObjectivePtr);

	UPROPERTY(BlueprintReadOnly)
	UQuest* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UQuest> QuestClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestID;

	UPROPERTY(BlueprintReadOnly)
	UQuestObjective* Objective;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UQuestObjective> ObjectiveClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ObjectiveID;
};
