#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PublicObjectTypes.h"
#include "Quest.generated.h"

class UQuestObjective;
class UQuestRewards;

UCLASS(Blueprintable)
class UNREALCODELAB_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Display Name")
	FText QuestDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Description")
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRepeatable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAllowRetryAbandoned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAllowedFails;

	UPROPERTY(EditAnywhere, DisplayName = "Objectives")
	TArray<TSubclassOf<UQuestObjective>> QuestObjectiveClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UQuestRewards* QuestRewards;

	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeLastStarted;

	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeLastUpdated;

	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeLastCompleted;

private:
	EProgressStatus QuestStatus;
	TArray<UQuestObjective*> QuestObjectives;

public:
	// Returns true if the current quest status is being flagged to ignore.
	bool IsQuestStatusBlocked(const FProgressStatusBlockFlags& Flags);

	UFUNCTION(BlueprintCallable)
	EProgressStatus GetQuestStatus();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuestObjective* GetObjectiveByID(FName ObjectiveID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuestObjective*>& GetObjectives();

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

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if the compared ID is the same, false otherwise.
	bool CompareQuestID(AQuest* OtherQuest);

	UFUNCTION(BlueprintNativeEvent, Category = "Quest")
	// Returns true if completion conditions are met.
	bool CheckCompletionConditions();

	UFUNCTION(BlueprintNativeEvent, Category = "Quest")
	void OnQuestUpdated();

	UFUNCTION(BlueprintNativeEvent, Category = "Quest")
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

protected:
	virtual void BeginPlay() override;
};
