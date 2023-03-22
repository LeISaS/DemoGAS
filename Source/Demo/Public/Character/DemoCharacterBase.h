// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Demo/Demo.h"
#include "GameplayTagContainer.h"
#include "Character/Abilities/CharacterGameplayAbility.h"
#include "DemoCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate,ADemoCharacterBase*, Character);

UCLASS()
class DEMO_API ADemoCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemoCharacterBase(const class FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(BlueprintAssignable, Category = "Demo|Character")
	FCharacterDiedDelegate OnCharacterDied;
	
	UFUNCTION(BlueprintCallable, Category = "Demo|Character")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character")
	virtual int32 GetAbilityLevel(DemoAbilityID AbilityID) const;

	virtual void RemoveCharacterAbilities();

	virtual void Die();
	
	UFUNCTION(BlueprintCallable,Category = "Demo|Character")
	virtual void FinishDying();

	UFUNCTION(BlueprintCallable, Category= "Demo|Character|Attributes")
	float GetCharacterLevel() const;

	
	UFUNCTION(BlueprintCallable, Category= "Demo|Character|Attributes")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category= "Demo|Character|Attributes")
	float GetMaxHealth() const;
	
	UFUNCTION(BlueprintCallable, Category= "Demo|Character|Attributes")
	float GetMana() const;
	
	UFUNCTION(BlueprintCallable, Category= "Demo|Character|Attributes")
	float GetMaxMana() const;	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UCharacterAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UCharacterAttributeSetBase> AttributeSetBase;

	//규칙 만들어 상태제어
	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;	// 죽은뒤 효과

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Demo|Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Demo|Character")
	UAnimMontage* DeathMontage;

	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Demo|Character")
	TArray<TSubclassOf<class UCharacterGameplayAbility>> CharacterAbilities;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Demo|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Demo|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();
	
	virtual void InitializeAttributes();
	
	virtual void AddStartupEffects();
	
	virtual void SetHealth(float Health);
	
	virtual void SetMana(float Mana);
	
public:	

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
