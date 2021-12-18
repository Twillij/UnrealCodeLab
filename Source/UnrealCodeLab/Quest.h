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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLocked;

	UPROPERTY(EditAnywhere, DisplayName = "Objectives")
	TArray<TSubclassOf<UQuestObjective>> QuestObjectiveClasses;

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

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetQuestStatus(EQuestStatus NewStatus);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetObjectiveStatusByIndex(int ArrayIndex, bool bIsComplete);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetObjectiveStatusByID(FName ObjectiveID, bool bIsComplete);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if the compared ID is the same, false otherwise.
	bool CompareQuestID(UQuest* OtherQuest);
};
