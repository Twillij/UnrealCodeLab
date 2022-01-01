#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomFunctionLibrary.generated.h"

class UQuestManager;

UCLASS()
class UNREALCODELAB_API UCustomFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UQuestManager* GetQuestManager(const UObject* WorldContextObject);
};
