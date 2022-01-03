#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestObjectiveEntity.generated.h"

class UQuestObjective;

UINTERFACE(MinimalAPI, BlueprintType)
class UQuestObjectiveEntity : public UInterface
{
	GENERATED_BODY()
};

class UNREALCODELAB_API IQuestObjectiveEntity
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<UQuestObjective*> GetRelatedQuestObjectives();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsEntityActive();
};
