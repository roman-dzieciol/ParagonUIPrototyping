#pragma once

#include "Engine/DataTable.h"
#include "FCardStat.h"
#include "FCardData.generated.h"

/** Structure that defines a level up table entry */
USTRUCT(BlueprintType)
struct FCardData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FCardData()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Affinity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float EnergyDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float ManaRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float PhysicalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float HealthRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float EnergyPen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float PhysicalArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float CooldownReduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float PhysicalPen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float EnergyArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float CritChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float Lifesteal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float CritBonus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float HarvesterPlacementTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float DamageBonus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedEnergyDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedManaRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedPhysicalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedHealthRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedMaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedEnergyPen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedPhysicalArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedCooldownReduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedPhysicalPen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedEnergyArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedCritChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedLifesteal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedCritBonus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedAttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedHarvesterPlacementTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedMaxMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float MaxedDamageBonus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Special0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Special1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Special2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString MaxedSpecial0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString MaxedSpecial1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString MaxedSpecial2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Unknown;

	friend bool operator==(const FCardData& LHS, const FCardData& RHS);
};

