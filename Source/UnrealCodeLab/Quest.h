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

	UPROPERTY(EditAnywhere, DisplayName = "Objectives")
	TArray<TSubclassOf<UQuestObjective>> QuestObjectiveClasses;

private:
	EQuestStatus QuestStatus;
	TArray<UQuestObjective*> QuestObjectives;

public:
	void Init();

	void OnQuestStatusChanged(EQuestStatus NewStatus);

	UFUNCTION(BlueprintCallable)
	EQuestStatus GetQuestStatus();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuestObjective* GetObjectiveByID(FName ObjectiveID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuestObjective*>& GetObjectives();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetQuestStatus(EQuestStatus NewStatus, bool bIgnoreLock = false);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool CheckQuestComplete(bool bSetCompleted = false);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if the compared ID is the same, false otherwise.
	bool CompareQuestID(UQuest* OtherQuest);

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
