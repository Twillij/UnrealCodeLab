#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestObjective.generated.h"

class UQuest;

UENUM(BlueprintType)
enum class EQuestObjectiveType : uint8
{
	None,
	Travel,
	Interact,
	Collect,
	Slay
};

UCLASS(Blueprintable)
class UNREALCODELAB_API UQuestObjective : public UObject
{
	GENERATED_BODY()

public:
	UQuest* OwningQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Objective ID")
	FName ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Type")
	EQuestObjectiveType ObjectiveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Description")
	FText ObjectiveDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLocked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsCompleted;

public:
	UFUNCTION(BlueprintCallable)
	UQuest* GetOwningQuest();

	UFUNCTION(BlueprintCallable)
	void SetObjectiveStatus(bool bIsComplete);
};
