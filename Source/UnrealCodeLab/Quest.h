#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest.generated.h"

class UQuestObjective;

UCLASS(Blueprintable)
class UNREALCODELAB_API UQuest : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "Quest ID")
	FName QuestId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Display Name")
	FString QuestDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Description")
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Objectives")
	TArray<UQuestObjective*> QuestObjectives;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsCompleted;

public:
	
	UFUNCTION(BlueprintCallable)
	void SetQuestStatus(bool bIsComplete);

	UFUNCTION(BlueprintImplementableEvent)
	void OnQuestComplete();
};
