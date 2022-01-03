#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PublicObjectTypes.h"
#include "QuestManager.generated.h"

class UQuest;
class UQuestObjective;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, UQuest*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveUpdated, UQuestObjective*, Objective);

UCLASS()
class UNREALCODELAB_API UQuestManager : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	int MaxTrackedQuests = 1;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestLocked;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestUnlocked;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestStarted;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestAbandoned;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestFailed;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestCompleted;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveLocked;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveUnlocked;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveStarted;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveAbandoned;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveFailed;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveCompleted;

private:
	TArray<UQuest*> Quests;
	TArray<UQuest*> TrackedQuests;

public:
	void Init();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& GetAllQuests();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& GetTrackedQuests();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<UQuest*> GetQuestsByStatus(EProgressStatus Status);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuest* GetQuestByClass(TSubclassOf<UQuest> QuestClass);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuest* GetQuestByID(FName QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest ID exist in the quest list.
	bool DoesQuestIDExist(FName QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Adds a new quest to the manager's quest list, and performs any necessary initialisation.
	// * bOverwriteDuplicateID = Whether the function overwrites any existing quest with the same ID.
	void AddNewQuest(UQuest* NewQuest, bool bOverwriteDuplicateID = false);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void TrackQuest(UQuest* Quest, bool bReplaceOldest = false);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByDisplayName();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByID();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestByStatus();
};
