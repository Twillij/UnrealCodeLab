// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterAttributeSet.h"
#include "CharacterBase.generated.h"

UCLASS()
class UNREALCODELAB_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCharacterAttributeSet* CharacterAttributeSet;

	// Base attribute variables are used for initializing attributes from the editor
	// The base attributes can be set by calling the InitBaseAttributes funtion
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Attributes")
	float Health = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Attributes")
	float MaxHealth = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Attributes")
	float Mana = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Attributes")
	float MaxMana = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Attributes")
	float Attack = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Attributes")
	float Defense = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// override the purely virtual function in the interface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	void InitBaseAttributes();

	UFUNCTION(BlueprintCallable)
	void GainAbility(TSubclassOf<UGameplayAbility> Ability);
};
