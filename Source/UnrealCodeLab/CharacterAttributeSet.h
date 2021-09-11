#pragma once

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float, Health, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangeDelegate, float, Mana, float, MaxMana);

UCLASS()
class UNREALCODELAB_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	// Can be used to initialize attributes
	UCharacterAttributeSet() {}

	FOnHealthChangeDelegate OnHealthChange;
	FOnManaChangeDelegate OnManaChange;

	// Base attributes are used for initialising attributes from the editor
	// The base attributes can be set by calling the InitBaseAttributes funtion
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes")
	float BaseHealth = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes")
	float BaseMaxHealth = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes")
	float BaseMana = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes")
	float BaseMaxMana = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes")
	float BaseAttack = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes")
	float BaseDefense = 0;

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Mana);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Attack);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Defense);

public:
	// Called after a gameplay effect is executed successfully
	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// Initialises the gameplay attributes in the attribute set using the base attribute variables
	UFUNCTION(BlueprintCallable)
	void InitBaseAttributes();
};
