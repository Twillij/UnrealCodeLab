#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PublicObjectTypes.h"
#include "CustomGameplayAbility.generated.h"

UCLASS()
class UNREALCODELAB_API UCustomGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityInputID AbilityInputID = EAbilityInputID::None;
};
