#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PublicObjectTypes.h"
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
	TArray<FQuestObjectiveInfo> RelatedObjectivesInfo;

public:
	virtual void BeginPlay() override;

	void InitRelatedObjectives();

	UFUNCTION(BlueprintCallable)
	void SetObjectiveByQuest(UQuest* NewQuest);
};
