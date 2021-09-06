#include "CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>("CharacterAttributeSet");
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterBase::InitBaseAttributes()
{
	CharacterAttributeSet->InitHealth(Health);
	CharacterAttributeSet->InitMaxHealth(MaxHealth);
	CharacterAttributeSet->InitMana(Mana);
	CharacterAttributeSet->InitMaxMana(MaxMana);
	CharacterAttributeSet->InitAttack(Attack);
	CharacterAttributeSet->InitDefense(Defense);
}

void ACharacterBase::GainAbility(TSubclassOf<UGameplayAbility> Ability)
{
	if (AbilitySystemComponent)
	{
		if (Ability && HasAuthority())
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability));
		}

		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
