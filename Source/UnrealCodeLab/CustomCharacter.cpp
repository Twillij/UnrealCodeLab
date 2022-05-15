#include "CustomCharacter.h"

// Sets default values
ACustomCharacter::ACustomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>("CharacterAttributeSet");
}

// Called when the game starts or when spawned
void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ACustomCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACustomCharacter::OnHealthChanged(float Health, float MaxHealth)
{
	BP_OnHealthChanged(Health, MaxHealth);
}

void ACustomCharacter::OnManaChanged(float Mana, float MaxMana)
{
	BP_OnManaChanged(Mana, MaxMana);
}

void ACustomCharacter::GainAbility(TSubclassOf<UGameplayAbility> Ability)
{
	if (AbilitySystemComponent)
	{
		if (Ability && HasAuthority())
		{
			//AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
		}

		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
