#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomDataObject.generated.h"

UCLASS()
class UNREALCODELAB_API UCustomDataObject : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual UWorld* GetWorld() const override;
};
