#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PublicObjectTypes.h"
#include "Quest.generated.h"

class UQuestObjective;

UCLASS(Blueprintable)
class UNREALCODELAB_API UQuest : public UObject
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

	UPROPERTY(EditAnywhere, DisplayName = "Objectives")
	TArray<TSubclassOf<UQuestObjective>> QuestObjectiveClasses;

private:
	EQuestStatus QuestStatus;
	TArray<UQuestObjective*> QuestObjectives;

public:
	void Init();

	void OnQuestStatusChanged(EQuestStatus NewStatus);

	// Returns true if the current quest status is being flagged to ignore.
	bool IsStatusBlocked(const FQuestStatusBlockFlags& Flags);

	UFUNCTION(BlueprintCallable)
	EQuestStatus GetQuestStatus();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuestObjective* GetObjectiveByID(FName ObjectiveID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuestObjective*>& GetObjectives();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetQuestStatus(EQuestStatus NewStatus, bool bIgnoreLock = false);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool LockQuest(FQuestStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool UnlockQuest(FQuestStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool AcceptQuest(FQuestStatusBlockFlags Flags);

	//UFUNCTION(BlueprintCallable, Category = "Quest")
	//bool AbandonQuest(FQuestStatusBlockFlags Flags);

	//UFUNCTION(BlueprintCallable, Category = "Quest")
	//bool FailQuest(FQuestStatusBlockFlags Flags);

	//UFUNCTION(BlueprintCallable, Category = "Quest")
	//bool CompleteQuest(FQuestStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if the compared ID is the same, false otherwise.
	bool CompareQuestID(UQuest* OtherQuest);

	UFUNCTION(BlueprintNativeEvent, Category = "Quest")
	// Returns true if unlock conditions are met.
	bool CheckUnlockConditions();

	UFUNCTION(BlueprintNativeEvent, Category = "Quest")
	// Returns true if completion conditions are met.
	bool CheckCompletionConditions();

	UFUNCTION(BlueprintNativeEvent, Category = "Quest")
	void ResetProgress();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestLocked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestUnlocked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestAccepted();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestAbandoned();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestFailed();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestCompleted();
};
