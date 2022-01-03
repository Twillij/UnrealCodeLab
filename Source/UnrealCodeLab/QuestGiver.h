#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestGiver.generated.h"

class UQuest;

UINTERFACE(MinimalAPI)
class UQuestGiver : public UInterface
{
	GENERATED_BODY()
};

class UNREALCODELAB_API IQuestGiver
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitAssignedQuests();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<UQuest*> GetAssignedQuests();
};
