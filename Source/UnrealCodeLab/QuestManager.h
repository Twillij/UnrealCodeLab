#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PublicObjectTypes.h"
#include "QuestManager.generated.h"

class UQuest;
class UQuestObjective;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, UQuest*, Quest);
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
	TArray<UQuest*> Quests;
	TArray<UQuest*> FilteredQuests;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& GetAllQuests();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& GetQuestsByStatus(EProgressStatus Status);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuest* GetQuestByID(FName QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Adds a new quest to the manager's quest list, and performs any necessary initialisation.
	// * bOverwriteDuplicateID = Whether the function overwrites any existing quest with the same ID.
	void AddNewQuest(UQuest* NewQuest, bool bOverwriteDuplicateID = false);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByDisplayName();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByID();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestByStatus();
};
