#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PublicObjectTypes.h"
#include "QuestObjective.generated.h"

class AQuest;

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
	UPROPERTY(BlueprintReadOnly)
	AQuest* OwningQuest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Description")
	FText ObjectiveDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Type")
	EQuestObjectiveType ObjectiveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHidden;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLocked;
	
	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeLastStarted;

	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeLastUpdated;

	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeLastCompleted;

private:
	EProgressStatus ObjectiveStatus;

public:
	bool IsObjectiveStatusBlocked(const FProgressStatusBlockFlags& Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	EProgressStatus GetObjectiveStatus();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if objective is able to be locked, false otherwise.
	bool LockObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be unlocked, false otherwise.
	bool UnlockObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be started, false otherwise.
	bool StartObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be abandoned, false otherwise.
	bool AbandonObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be failed, false otherwise.
	bool FailObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be completed, false otherwise.
	bool CompleteObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintNativeEvent)
	void OnObjectiveUpdated();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveLocked();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveUnlocked();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveStarted();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveAbandoned();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveFailed();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveCompleted();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetProgress();
};
