// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoPlayerState.h"

#include "Character/Abilities/CharacterAbilitySystemComponent.h"

ADemoPlayerState::ADemoPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* ADemoPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCharacterAttributeSetBase* ADemoPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool ADemoPlayerState::IsAlive() const
{
	return false;
}

void ADemoPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	//TODO HUD
}

float ADemoPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float ADemoPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float ADemoPlayerState::GetMana() const
{
	return AttributeSetBase->GetMana();
}

float ADemoPlayerState::GetMaxMana() const
{
	return AttributeSetBase->GetMaxMana();
}

int32 ADemoPlayerState::GetCharacterLevel() const
{
	return AttributeSetBase->GetLevel();
}

void ADemoPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, & ThisClass::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, & ThisClass::MaxHealthChanged);
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, & ThisClass::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, & ThisClass::MaxManaChanged);
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, & ThisClass::CharacterLevelChanged);
		
		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")),EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::StunTagChanged);
	}
}

void ADemoPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("Health Changed!"));
}

void ADemoPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("MaxHealthChanged Changed!"));
}

void ADemoPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("ManaChanged Changed!"));
}

void ADemoPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("MaxManaChanged Changed!"));
}

void ADemoPlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("CharacterLevelChanged Changed!"));
}

void ADemoPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if(NewCount >0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag((FName("Ability"))));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag((FName("Ability.NotCanceledByStun"))));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel,&AbilityTagsToIgnore);
		
	}
}

