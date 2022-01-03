#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SomeActorComponent.generated.h"

class UQuest;
class UQuestObjective;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCODELAB_API USomeActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USomeActorComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TMap<TSubclassOf<UQuest>, TSubclassOf<UQuestObjective>> RelatedQuestObjectiveClasses;

	UPROPERTY(BlueprintReadOnly)
	TArray<UQuestObjective*> RelatedObjectives;

public:
	virtual void BeginPlay() override;

	void InitRelatedObjectives();

	void AddRelatedObjective(UQuestObjective* ObjectivePtr);
};
