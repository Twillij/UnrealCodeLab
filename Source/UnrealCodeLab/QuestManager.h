#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PublicObjectTypes.h"
#include "QuestManager.generated.h"

class AQuest;
class UQuestObjective;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, AQuest*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveUpdated, UQuestObjective*, Objective);

UCLASS()
class UNREALCODELAB_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuestManager();

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
	TArray<AQuest*> Quests;
	TArray<AQuest*> FilteredQuests;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<AQuest*>& GetAllQuests();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<AQuest*>& GetQuestsByStatus(EProgressStatus Status);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	AQuest* GetQuestByID(FName QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Adds a new quest to the manager's quest list, and performs any necessary initialisation.
	// * bOverwriteDuplicateID = Whether the function overwrites any existing quest with the same ID.
	void AddNewQuest(AQuest* NewQuest, bool bOverwriteDuplicateID = false);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<AQuest*>& SortQuestsByDisplayName();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<AQuest*>& SortQuestsByID();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<AQuest*>& SortQuestByStatus();
};
