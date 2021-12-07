#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest.generated.h"

class UQuestObjective;

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
	Available,
	Started,
	Completed,
	Abandoned
};

UCLASS(Blueprintable)
class UNREALCODELAB_API UQuest : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Display Name")
	FText QuestDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Description")
	FText QuestDescription;

	UPROPERTY(EditAnywhere, DisplayName = "Objectives")
	TArray<TSubclassOf<UQuestObjective>> InitialQuestObjectiveClasses;

private:
	EQuestStatus QuestStatus;
	TArray<UQuestObjective*> QuestObjectives;

public:
	void Init();
	
	UFUNCTION(BlueprintCallable)
	const FName& GetQuestID();

	UFUNCTION(BlueprintCallable)
	EQuestStatus GetQuestStatus();

	UFUNCTION(BlueprintCallable)
	const TArray<UQuestObjective*>& GetObjectives();

	UFUNCTION(BlueprintCallable)
	void SetQuestStatus(EQuestStatus NewStatus);

	UFUNCTION(BlueprintCallable)
	void SetObjectiveStatusByIndex(int ArrayIndex, bool bIsComplete);

	UFUNCTION(BlueprintCallable)
	void SetObjectiveStatusByID(const FName& ObjectiveID, bool bIsComplete);

	UFUNCTION(BlueprintCallable)
	void AddObjective(UQuestObjective* Objective);

	UFUNCTION(BlueprintCallable)
	bool CompareQuestID(UQuest* OtherQuest);

	UFUNCTION(BlueprintImplementableEvent)
	void OnQuestStatusChanged(EQuestStatus NewStatus);
};
