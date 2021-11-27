#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestObjective.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Type")
	EQuestObjectiveType ObjectiveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Description")
	FText ObjectiveDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsCompleted;

public:

	UFUNCTION(BlueprintCallable)
	void SetObjectiveStatus(bool bIsComplete);

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveComplete();
};
