#include "CharacterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		OnHealthChange.Broadcast(GetHealth(), GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
		OnManaChange.Broadcast(GetMana(), GetMaxMana());
	}
}

void UCharacterAttributeSet::InitBaseAttributes()
{
	InitHealth(BaseHealth);
	InitMaxHealth(BaseMaxHealth);
	InitMana(BaseMana);
	InitMaxMana(BaseMaxMana);
	InitAttack(BaseAttack);
	InitDefense(BaseDefense);
}
