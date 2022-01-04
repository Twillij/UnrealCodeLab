#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PublicObjectTypes.h"
#include "QuestObjectiveComponent.generated.h"

class UQuest;
class UQuestObjective;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCODELAB_API UQuestObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestObjectiveComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<FQuestObjectiveInfo> RelatedObjectivesInfo;

public:
	virtual void BeginPlay() override;

	void InitRelatedObjectives();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuestObjective* GetObjectiveByClass(TSubclassOf<UQuestObjective> ObjectiveClass);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuestObjective* GetObjectiveByID(FName ObjectiveID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<UQuestObjective*> GetObjectivesByStatus(EProgressStatus ObjectiveStatus);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetObjectivesByQuest(UQuest* NewQuest);
};
