// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterAttributeSet.h"
#include "CustomCharacter.generated.h"

UCLASS()
class UNREALCODELAB_API ACustomCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomCharacter();

	// Component required for the gameplay ability system
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent;

	// Attribute set containing all the character gameplay variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCharacterAttributeSet* CharacterAttributeSet;

	// Identifies a character's team and their behaviour towards other teams
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TeamID = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Override function for the purely virtual function in the interface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Called when certain gameplay attributes are changed
	// Also calls the corresponding blueprint implementable events
	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth);
	UFUNCTION()
	void OnManaChanged(float Mana, float MaxMana);

	// Grants the ability system component an ability
	UFUNCTION(BlueprintCallable)
	void GainAbility(TSubclassOf<UCustomGameplayAbility> Ability);

	// Blueprint implementable events that are called when certain gameplay attributes are changed
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnManaChanged"))
	void BP_OnManaChanged(float Mana, float MaxMana);
};
