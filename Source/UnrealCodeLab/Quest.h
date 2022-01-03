#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PublicObjectTypes.h"
#include "Quest.generated.h"

class UQuestObjective;
class UQuestRewards;

UCLASS(Blueprintable)
class UNREALCODELAB_API UQuest : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Display Name", Category = "Quest")
	FText QuestDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Description", Category = "Quest")
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bIsHidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bIsRepeatable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bAllowRetryAbandoned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	int MaxAllowedFails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	int MinReqLevel;

	UPROPERTY(EditAnywhere, DisplayName = "Objectives", Category = "Quest")
	TArray<TSubclassOf<UQuestObjective>> QuestObjectiveClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	UQuestRewards* QuestRewards;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	int ActiveObjectiveGroupIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	FDateTime TimeLastStarted;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	FDateTime TimeLastUpdated;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	FDateTime TimeLastCompleted;

private:
	EProgressStatus QuestStatus;
	TArray<UQuestObjective*> Objectives;
	TArray<UQuestObjective*> ActiveObjectiveGroup;

public:
	void Init();

	// Returns true if the current quest status is being flagged to ignore.
	bool IsQuestStatusBlocked(const FProgressStatusBlockFlags& Flags);

	UFUNCTION(BlueprintCallable)
	EProgressStatus GetQuestStatus();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuestObjective* GetObjectiveByID(FName ObjectiveID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuestObjective*>& GetObjectives();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuestObjective*>& GetActiveObjectiveGroup();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns an array of objectives with the passed group index if bEqualsIndex is true.
	// * bEqualsIndex = If set to false, function returns all objectives with different group index. Default value is true.
	TArray<UQuestObjective*> GetObjectivesByGroupIndex(int Index, bool bEqualsIndex = true);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Sets the active objective group if there is at least one objective of the passed group index.
	// * bHideInactiveGroup = Sets all other objectives as hidden if set to true. Default value is true.
	void SetActiveObjectiveGroup(int GroupIndex, bool bHideInactiveGroups = true);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Convenience function that calls the appropriate status changing function depending on the NewStatus passed.
	// Preliminarily returns false if NewStatus is the same as current quest status.
	bool SetQuestStatus(EProgressStatus NewStatus, FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be locked, false otherwise.
	bool LockQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be unlocked, false otherwise.
	bool UnlockQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be started, false otherwise.
	bool StartQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be abandoned, false otherwise.
	bool AbandonQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be failed, false otherwise.
	bool FailQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be completed, false otherwise.
	bool CompleteQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest")
	// Returns true if completion conditions are met.
	bool CheckCompletionConditions();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest")
	void OnQuestUpdated();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest")
	void ResetProgress();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestLocked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestUnlocked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestStarted();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestAbandoned();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestFailed();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestCompleted();
};
