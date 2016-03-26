

#include "DeckBuilderDesktop.h"
#include "FCardData.h"

bool operator == (const FCardData& LHS, const FCardData& RHS)
{
	return LHS.CardName == RHS.CardName
		&& LHS.Cost == RHS.Cost
		&& LHS.Type == RHS.Type
		&& LHS.Affinity == RHS.Affinity
		&& LHS.Rarity == RHS.Rarity
		&& LHS.EnergyDamage == RHS.EnergyDamage
		&& LHS.ManaRegen == RHS.ManaRegen
		&& LHS.MaxHealth == RHS.MaxHealth
		&& LHS.PhysicalDamage == RHS.PhysicalDamage
		&& LHS.HealthRegen == RHS.HealthRegen
		&& LHS.MaxMana == RHS.MaxMana
		&& LHS.EnergyPen == RHS.EnergyPen
		&& LHS.PhysicalArmor == RHS.PhysicalArmor
		&& LHS.CooldownReduction == RHS.CooldownReduction
		&& LHS.PhysicalPen == RHS.PhysicalPen
		&& LHS.EnergyArmor == RHS.EnergyArmor
		&& LHS.CritChance == RHS.CritChance
		&& LHS.Lifesteal == RHS.Lifesteal
		&& LHS.CritBonus == RHS.CritBonus
		&& LHS.AttackSpeed == RHS.AttackSpeed
		&& LHS.HarvesterPlacementTime == RHS.HarvesterPlacementTime
		&& LHS.MaxMovementSpeed == RHS.MaxMovementSpeed
		&& LHS.DamageBonus == RHS.DamageBonus
		&& LHS.MaxedEnergyDamage == RHS.MaxedEnergyDamage
		&& LHS.MaxedManaRegen == RHS.MaxedManaRegen
		&& LHS.MaxedMaxHealth == RHS.MaxedMaxHealth
		&& LHS.MaxedPhysicalDamage == RHS.MaxedPhysicalDamage
		&& LHS.MaxedHealthRegen == RHS.MaxedHealthRegen
		&& LHS.MaxedMaxMana == RHS.MaxedMaxMana
		&& LHS.MaxedEnergyPen == RHS.MaxedEnergyPen
		&& LHS.MaxedPhysicalArmor == RHS.MaxedPhysicalArmor
		&& LHS.MaxedCooldownReduction == RHS.MaxedCooldownReduction
		&& LHS.MaxedPhysicalPen == RHS.MaxedPhysicalPen
		&& LHS.MaxedEnergyArmor == RHS.MaxedEnergyArmor
		&& LHS.MaxedCritChance == RHS.MaxedCritChance
		&& LHS.MaxedLifesteal == RHS.MaxedLifesteal
		&& LHS.MaxedCritBonus == RHS.MaxedCritBonus
		&& LHS.MaxedAttackSpeed == RHS.MaxedAttackSpeed
		&& LHS.MaxedHarvesterPlacementTime == RHS.MaxedHarvesterPlacementTime
		&& LHS.MaxedMaxMovementSpeed == RHS.MaxedMaxMovementSpeed
		&& LHS.MaxedDamageBonus == RHS.MaxedDamageBonus
		&& LHS.Special0 == RHS.Special0
		&& LHS.Special1 == RHS.Special1
		&& LHS.Special2 == RHS.Special2
		&& LHS.MaxedSpecial0 == RHS.MaxedSpecial0
		&& LHS.MaxedSpecial1 == RHS.MaxedSpecial1
		&& LHS.MaxedSpecial2 == RHS.MaxedSpecial2
		&& LHS.Unknown == RHS.Unknown;
}
