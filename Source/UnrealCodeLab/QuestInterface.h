#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestInterface.generated.h"

class AQuestManager;

UINTERFACE(MinimalAPI, BlueprintType)
class UQuestInterface : public UInterface
{
	GENERATED_BODY()
};

class UNREALCODELAB_API IQuestInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest")
	AQuestManager* GetQuestManager();
};
