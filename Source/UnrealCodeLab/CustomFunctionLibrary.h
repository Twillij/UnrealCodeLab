#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomFunctionLibrary.generated.h"

class AQuestManager;

UCLASS()
class UNREALCODELAB_API UCustomFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static AQuestManager* GetQuestManager(const UObject* WorldContextObject);
};
