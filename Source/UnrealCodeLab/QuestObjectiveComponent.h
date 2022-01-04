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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FQuestObjectiveInfo> RelatedObjectivesInfo;

public:
	virtual void BeginPlay() override;

	void InitRelatedObjectives();

	UFUNCTION(BlueprintCallable)
	void SetObjectivesByQuest(UQuest* NewQuest);
};
