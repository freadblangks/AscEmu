/*
Copyright (c) 2014-2020 AscEmu Team <http://www.ascemu.org>
This file is released under the MIT license. See README-MIT for more information.
*/

#include "SpellAuras.h"

#include "Definitions/SpellFamily.h"
#include "Definitions/SpellIsFlags.h"
#include "Definitions/SpellTypes.h"
#include "SpellHelpers.h"
#include "SpellMgr.h"

#include "Objects/ObjectMgr.h"

using AscEmu::World::Spell::Helpers::spellModFlatFloatValue;
using AscEmu::World::Spell::Helpers::spellModFlatIntValue;
using AscEmu::World::Spell::Helpers::spellModPercentageFloatValue;
using AscEmu::World::Spell::Helpers::spellModPercentageIntValue;

pSpellAura SpellAuraHandler[TOTAL_SPELL_AURAS] =
{
    &Aura::spellAuraEffectNotImplemented,                                   //   0 SPELL_AURA_NONE
    &Aura::SpellAuraBindSight,                                              //   1 SPELL_AURA_BIND_SIGHT
    &Aura::SpellAuraModPossess,                                             //   2 SPELL_AURA_MOD_POSSESS
    &Aura::spellAuraEffectPeriodicDamage,                                   //   3 SPELL_AURA_PERIODIC_DAMAGE
    &Aura::SpellAuraDummy,                                                  //   4 SPELL_AURA_DUMMY
    &Aura::SpellAuraModConfuse,                                             //   5 SPELL_AURA_MOD_CONFUSE
    &Aura::SpellAuraModCharm,                                               //   6 SPELL_AURA_MOD_CHARM
    &Aura::SpellAuraModFear,                                                //   7 SPELL_AURA_MOD_FEAR
    &Aura::spellAuraEffectPeriodicHeal,                                     //   8 SPELL_AURA_PERIODIC_HEAL
    &Aura::SpellAuraModAttackSpeed,                                         //   9 SPELL_AURA_MOD_ATTACK_SPEED
    &Aura::SpellAuraModThreatGenerated,                                     //  10 SPELL_AURA_MOD_THREAT_GENERATED
    &Aura::SpellAuraModTaunt,                                               //  11 SPELL_AURA_MOD_TAUNT
    &Aura::SpellAuraModStun,                                                //  12 SPELL_AURA_MOD_STUN
    &Aura::SpellAuraModDamageDone,                                          //  13 SPELL_AURA_MOD_DAMAGE_DONE
    &Aura::SpellAuraModDamageTaken,                                         //  14 SPELL_AURA_MOD_DAMAGE_TAKEN
    &Aura::SpellAuraDamageShield,                                           //  15 SPELL_AURA_DAMAGE_SHIELD
    &Aura::SpellAuraModStealth,                                             //  16 SPELL_AURA_MOD_STEALTH
    &Aura::SpellAuraModStealthDetection,                                    //  17 SPELL_AURA_MOD_STEALTH_DETECTION
    &Aura::SpellAuraModInvisibility,                                        //  18 SPELL_AURA_MOD_INVISIBILITY
    &Aura::SpellAuraModInvisibilityDetection,                               //  19 SPELL_AURA_MOD_INVISIBILITY_DETECTION
    &Aura::spellAuraEffectPeriodicHealPct,                                  //  20 SPELL_AURA_PERIODIC_HEAL_PCT
    &Aura::spellAuraEffectPeriodicPowerPct,                                 //  21 SPELL_AURA_PERIODIC_POWER_PCT
    &Aura::SpellAuraModResistance,                                          //  22 SPELL_AURA_MOD_RESISTANCE
    &Aura::spellAuraEffectPeriodicTriggerSpell,                             //  23 SPELL_AURA_PERIODIC_TRIGGER_SPELL
    &Aura::spellAuraEffectPeriodicEnergize,                                 //  24 SPELL_AURA_PERIODIC_ENERGIZE
    &Aura::SpellAuraModPacify,                                              //  25 SPELL_AURA_MOD_PACIFY
    &Aura::SpellAuraModRoot,                                                //  26 SPELL_AURA_MOD_ROOT
    &Aura::SpellAuraModSilence,                                             //  27 SPELL_AURA_MOD_SILENCE
    &Aura::SpellAuraReflectSpells,                                          //  28 SPELL_AURA_REFLECT_SPELLS
    &Aura::SpellAuraModStat,                                                //  29 SPELL_AURA_MOD_STAT
    &Aura::SpellAuraModSkill,                                               //  30 SPELL_AURA_MOD_SKILL
    &Aura::SpellAuraModIncreaseSpeed,                                       //  31 SPELL_AURA_MOD_INCREASE_SPEED
    &Aura::SpellAuraModIncreaseMountedSpeed,                                //  32 SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED
    &Aura::SpellAuraModDecreaseSpeed,                                       //  33 SPELL_AURA_MOD_DECREASE_SPEED
    &Aura::SpellAuraModIncreaseHealth,                                      //  34 SPELL_AURA_MOD_INCREASE_HEALTH
    &Aura::SpellAuraModIncreaseEnergy,                                      //  35 SPELL_AURA_MOD_INCREASE_ENERGY
    &Aura::SpellAuraModShapeshift,                                          //  36 SPELL_AURA_MOD_SHAPESHIFT
    &Aura::SpellAuraModEffectImmunity,                                      //  37 SPELL_AURA_MOD_EFFECT_IMMUNITY
    &Aura::SpellAuraModStateImmunity,                                       //  38 SPELL_AURA_MOD_STATE_IMMUNITY
    &Aura::SpellAuraModSchoolImmunity,                                      //  39 SPELL_AURA_MOD_SCHOOL_IMMUNITY
    &Aura::SpellAuraModDmgImmunity,                                         //  40 SPELL_AURA_MOD_DMG_IMMUNITY
    &Aura::SpellAuraModDispelImmunity,                                      //  41 SPELL_AURA_MOD_DISPEL_IMMUNITY
    &Aura::SpellAuraProcTriggerSpell,                                       //  42 SPELL_AURA_PROC_TRIGGER_SPELL
    &Aura::SpellAuraProcTriggerDamage,                                      //  43 SPELL_AURA_PROC_TRIGGER_DAMAGE
    &Aura::SpellAuraTrackCreatures,                                         //  44 SPELL_AURA_TRACK_CREATURES
    &Aura::SpellAuraTrackResources,                                         //  45 SPELL_AURA_TRACK_RESOURCES
    &Aura::spellAuraEffectNotImplemented,                                   //  46 SPELL_AURA_46
    &Aura::SpellAuraModParryPerc,                                           //  47 SPELL_AURA_MOD_PARRY_PERC
    &Aura::spellAuraEffectNotImplemented,                                   //  48 SPELL_AURA_48
    &Aura::SpellAuraModDodgePerc,                                           //  49 SPELL_AURA_MOD_DODGE_PERC
    &Aura::spellAuraEffectNotImplemented,                                   //  50 SPELL_AURA_50
    &Aura::SpellAuraModBlockPerc,                                           //  51 SPELL_AURA_MOD_BLOCK_PERC
    &Aura::SpellAuraModCritPerc,                                            //  52 SPELL_AURA_MOD_CRIT_PERC
    &Aura::spellAuraEffectPeriodicLeech,                                    //  53 SPELL_AURA_PERIODIC_LEECH
    &Aura::SpellAuraModHitChance,                                           //  54 SPELL_AURA_MOD_HIT_CHANCE
    &Aura::SpellAuraModSpellHitChance,                                      //  55 SPELL_AURA_MOD_SPELL_HIT_CHANCE
    &Aura::SpellAuraTransform,                                              //  56 SPELL_AURA_TRANSFORM
    &Aura::SpellAuraModSpellCritChance,                                     //  57 SPELL_AURA_MOD_SPELL_CRIT_CHANCE
    &Aura::SpellAuraIncreaseSwimSpeed,                                      //  58 SPELL_AURA_INCREASE_SWIM_SPEED
    &Aura::SpellAuraModCratureDmgDone,                                      //  59 SPELL_AURA_MOD_CRATURE_DMG_DONE
    &Aura::SpellAuraPacifySilence,                                          //  60 SPELL_AURA_PACIFY_SILENCE
    &Aura::SpellAuraModScale,                                               //  61 SPELL_AURA_MOD_SCALE
    &Aura::spellAuraEffectPeriodicHealthFunnel,                             //  62 SPELL_AURA_PERIODIC_HEALTH_FUNNEL
    &Aura::spellAuraEffectNotImplemented,                                   //  63 SPELL_AURA_63
    &Aura::spellAuraEffectPeriodicManaLeech,                                //  64 SPELL_AURA_PERIODIC_MANALEECH
    &Aura::SpellAuraModCastingSpeed,                                        //  65 SPELL_AURA_MOD_CASTING_SPEED
    &Aura::SpellAuraFeignDeath,                                             //  66 SPELL_AURA_FEIGN_DEATH
    &Aura::SpellAuraModDisarm,                                              //  67 SPELL_AURA_MOD_DISARM
    &Aura::SpellAuraModStalked,                                             //  68 SPELL_AURA_MOD_STALKED
    &Aura::spellAuraEffectSchoolAbsorb,                                     //  69 SPELL_AURA_SCHOOL_ABSORB
    &Aura::spellAuraEffectNotImplemented,                                   //  70 SPELL_AURA_70
    &Aura::SpellAuraModSpellCritChanceSchool,                               //  71 SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL
    &Aura::SpellAuraModPowerCost,                                           //  72 SPELL_AURA_MOD_POWER_COST
    &Aura::SpellAuraModPowerCostSchool,                                     //  73 SPELL_AURA_MOD_POWER_COST_SCHOOL
    &Aura::SpellAuraReflectSpellsSchool,                                    //  74 SPELL_AURA_REFLECT_SPELLS_SCHOOL
    &Aura::SpellAuraModLanguage,                                            //  75 SPELL_AURA_MOD_LANGUAGE
    &Aura::SpellAuraAddFarSight,                                            //  76 SPELL_AURA_ADD_FAR_SIGHT
    &Aura::SpellAuraMechanicImmunity,                                       //  77 SPELL_AURA_MECHANIC_IMMUNITY
    &Aura::SpellAuraMounted,                                                //  78 SPELL_AURA_MOUNTED
    &Aura::SpellAuraModDamagePercDone,                                      //  79 SPELL_AURA_MOD_DAMAGE_PERC_DONE
    &Aura::SpellAuraModPercStat,                                            //  80 SPELL_AURA_MOD_PERC_STAT
    &Aura::SpellAuraSplitDamage,                                            //  81 SPELL_AURA_SPLIT_DAMAGE
    &Aura::SpellAuraWaterBreathing,                                         //  82 SPELL_AURA_WATER_BREATHING
    &Aura::SpellAuraModBaseResistance,                                      //  83 SPELL_AURA_MOD_BASE_RESISTANCE
    &Aura::SpellAuraModRegen,                                               //  84 SPELL_AURA_MOD_REGEN
    &Aura::SpellAuraModPowerRegen,                                          //  85 SPELL_AURA_MOD_POWER_REGEN
    &Aura::SpellAuraChannelDeathItem,                                       //  86 SPELL_AURA_CHANNEL_DEATH_ITEM
    &Aura::SpellAuraModDamagePercTaken,                                     //  87 SPELL_AURA_MOD_DAMAGE_PERC_TAKEN
    &Aura::SpellAuraModRegenPercent,                                        //  88 SPELL_AURA_MOD_REGEN_PERCENT
    &Aura::spellAuraEffectPeriodicDamagePercent,                            //  89 SPELL_AURA_PERIODIC_DAMAGE_PERCENT
    &Aura::SpellAuraModResistChance,                                        //  90 SPELL_AURA_MOD_RESIST_CHANCE
    &Aura::SpellAuraModDetectRange,                                         //  91 SPELL_AURA_MOD_DETECT_RANGE
    &Aura::SpellAuraPreventsFleeing,                                        //  92 SPELL_AURA_PREVENTS_FLEEING
    &Aura::SpellAuraModUnattackable,                                        //  93 SPELL_AURA_MOD_UNATTACKABLE
    &Aura::SpellAuraInterruptRegen,                                         //  94 SPELL_AURA_INTERRUPT_REGEN
    &Aura::SpellAuraGhost,                                                  //  95 SPELL_AURA_GHOST
    &Aura::SpellAuraMagnet,                                                 //  96 SPELL_AURA_MAGNET
    &Aura::SpellAuraManaShield,                                             //  97 SPELL_AURA_MANA_SHIELD
    &Aura::SpellAuraSkillTalent,                                            //  98 SPELL_AURA_SKILL_TALENT
    &Aura::SpellAuraModAttackPower,                                         //  99 SPELL_AURA_MOD_ATTACK_POWER
    &Aura::SpellAuraVisible,                                                // 100 SPELL_AURA_VISIBLE
    &Aura::SpellAuraModResistancePCT,                                       // 101 SPELL_AURA_MOD_RESISTANCE_PCT
    &Aura::SpellAuraModCreatureAttackPower,                                 // 102 SPELL_AURA_MOD_CREATURE_ATTACK_POWER
    &Aura::SpellAuraModTotalThreat,                                         // 103 SPELL_AURA_MOD_TOTAL_THREAT
    &Aura::SpellAuraWaterWalk,                                              // 104 SPELL_AURA_WATER_WALK
    &Aura::SpellAuraFeatherFall,                                            // 105 SPELL_AURA_FEATHER_FALL
    &Aura::SpellAuraHover,                                                  // 106 SPELL_AURA_HOVER
    &Aura::SpellAuraAddFlatModifier,                                        // 107 SPELL_AURA_ADD_FLAT_MODIFIER
    &Aura::SpellAuraAddPctMod,                                              // 108 SPELL_AURA_ADD_PCT_MOD
    &Aura::SpellAuraAddClassTargetTrigger,                                  // 109 SPELL_AURA_ADD_CLASS_TARGET_TRIGGER
    &Aura::SpellAuraModPowerRegPerc,                                        // 110 SPELL_AURA_MOD_POWER_REG_PERC
    &Aura::spellAuraEffectNotImplemented,                                   // 111 SPELL_AURA_111
    &Aura::SpellAuraOverrideClassScripts,                                   // 112 SPELL_AURA_OVERRIDE_CLASS_SCRIPTS
    &Aura::SpellAuraModRangedDamageTaken,                                   // 113 SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN
    &Aura::spellAuraEffectNotImplemented,                                   // 114 SPELL_AURA_114
    &Aura::SpellAuraModHealing,                                             // 115 SPELL_AURA_MOD_HEALING
    &Aura::SpellAuraIgnoreRegenInterrupt,                                   // 116 SPELL_AURA_IGNORE_REGEN_INTERRUPT
    &Aura::SpellAuraModMechanicResistance,                                  // 117 SPELL_AURA_MOD_MECHANIC_RESISTANCE
    &Aura::SpellAuraModHealingPCT,                                          // 118 SPELL_AURA_MOD_HEALING_PCT
    &Aura::spellAuraEffectNotImplemented,                                   // 119 SPELL_AURA_119
    &Aura::SpellAuraUntrackable,                                            // 120 SPELL_AURA_UNTRACKABLE
    &Aura::SpellAuraEmphaty,                                                // 121 SPELL_AURA_EMPHATY
    &Aura::SpellAuraModOffhandDamagePCT,                                    // 122 SPELL_AURA_MOD_OFFHANDDAMAGE_PCT
    &Aura::SpellAuraModPenetration,                                         // 123 SPELL_AURA_MOD_PENETRATION
    &Aura::SpellAuraModRangedAttackPower,                                   // 124 SPELL_AURA_MOD_RANGED_ATTACK_POWER
    &Aura::SpellAuraModMeleeDamageTaken,                                    // 125 SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN
    &Aura::SpellAuraModMeleeDamageTakenPct,                                 // 126 SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT
    &Aura::SpellAuraRAPAttackerBonus,                                       // 127 SPELL_AURA_RAP_ATTACKER_BONUS
    &Aura::SpellAuraModPossessPet,                                          // 128 SPELL_AURA_MOD_POSSESS_PET
    &Aura::SpellAuraModIncreaseSpeedAlways,                                 // 129 SPELL_AURA_MOD_INCREASE_SPEED_ALWAYS
    &Aura::SpellAuraModIncreaseMountedSpeed,                                // 130 SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED
    &Aura::SpellAuraModCreatureRangedAttackPower,                           // 131 SPELL_AURA_MOD_CREATURE_RANGED_ATTACK_POWER
    &Aura::SpellAuraModIncreaseEnergyPerc,                                  // 132 SPELL_AURA_MOD_INCREASE_ENERGY_PERC
    &Aura::SpellAuraModIncreaseHealthPerc,                                  // 133 SPELL_AURA_MOD_INCREASE_HEALTH_PERC
    &Aura::SpellAuraModManaRegInterrupt,                                    // 134 SPELL_AURA_MOD_MANA_REG_INTERRUPT
    &Aura::SpellAuraModHealingDone,                                         // 135 SPELL_AURA_MOD_HEALING_DONE
    &Aura::SpellAuraModHealingDonePct,                                      // 136 SPELL_AURA_MOD_HEALING_DONE_PCT
    &Aura::SpellAuraModTotalStatPerc,                                       // 137 SPELL_AURA_MOD_TOTAL_STAT_PERC
    &Aura::SpellAuraModHaste,                                               // 138 SPELL_AURA_MOD_HASTE
    &Aura::SpellAuraForceReaction,                                          // 139 SPELL_AURA_FORCE_REACTION
    &Aura::SpellAuraModRangedHaste,                                         // 140 SPELL_AURA_MOD_RANGED_HASTE
    &Aura::SpellAuraModRangedAmmoHaste,                                     // 141 SPELL_AURA_MOD_RANGED_AMMO_HASTE
    &Aura::SpellAuraModBaseResistancePerc,                                  // 142 SPELL_AURA_MOD_BASE_RESISTANCE_PERC
    &Aura::SpellAuraModResistanceExclusive,                                 // 143 SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE
    &Aura::SpellAuraSafeFall,                                               // 144 SPELL_AURA_SAFE_FALL
    &Aura::spellAuraEffectNotImplemented,                                   // 145 SPELL_AURA_145
    &Aura::spellAuraEffectNotImplemented,                                   // 146 SPELL_AURA_146
    &Aura::spellAuraEffectNotImplemented,                                   // 147 SPELL_AURA_147
    &Aura::SpellAuraRetainComboPoints,                                      // 148 SPELL_AURA_RETAIN_COMBO_POINTS
    &Aura::SpellAuraResistPushback,                                         // 149 SPELL_AURA_RESIST_PUSHBACK
    &Aura::SpellAuraModShieldBlockPCT,                                      // 150 SPELL_AURA_MOD_SHIELD_BLOCK_PCT
    &Aura::SpellAuraTrackStealthed,                                         // 151 SPELL_AURA_TRACK_STEALTHED
    &Aura::SpellAuraModDetectedRange,                                       // 152 SPELL_AURA_MOD_DETECTED_RANGE
    &Aura::SpellAuraSplitDamageFlat,                                        // 153 SPELL_AURA_SPLIT_DAMAGE_FLAT
    &Aura::SpellAuraModStealthLevel,                                        // 154 SPELL_AURA_MOD_STEALTH_LEVEL
    &Aura::SpellAuraModUnderwaterBreathing,                                 // 155 SPELL_AURA_MOD_UNDERWATER_BREATHING
    &Aura::SpellAuraModReputationAdjust,                                    // 156 SPELL_AURA_MOD_REPUTATION_ADJUST
    &Aura::spellAuraEffectNotImplemented,                                   // 157 SPELL_AURA_157
    &Aura::SpellAuraModBlockValue,                                          // 158 SPELL_AURA_MOD_BLOCK_VALUE
    &Aura::SpellAuraNoPVPCredit,                                            // 159 SPELL_AURA_NO_PVP_CREDIT
    &Aura::spellAuraEffectNotImplemented,                                   // 160 SPELL_AURA_160
    &Aura::SpellAuraModHealthRegInCombat,                                   // 161 SPELL_AURA_MOD_HEALTH_REG_IN_COMBAT
    &Aura::spellAuraEffectPeriodicPowerBurn,                                // 162 SPELL_AURA_PERIODIC_POWER_BURN
    &Aura::SpellAuraModCritDmgPhysical,                                     // 163 SPELL_AURA_MOD_CRIT_DMG_PHYSICAL
    &Aura::spellAuraEffectNotImplemented,                                   // 164 SPELL_AURA_164
    &Aura::SpellAuraAPAttackerBonus,                                        // 165 SPELL_AURA_AP_ATTACKER_BONUS
    &Aura::SpellAuraModPAttackPower,                                        // 166 SPELL_AURA_MOD_P_ATTACK_POWER
    &Aura::SpellAuraModRangedAttackPowerPct,                                // 167 SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT
    &Aura::SpellAuraIncreaseDamageTypePCT,                                  // 168 SPELL_AURA_INCREASE_DAMAGE_TYPE_PCT
    &Aura::SpellAuraIncreaseCricticalTypePCT,                               // 169 SPELL_AURA_INCREASE_CRICTICAL_TYPE_PCT
    &Aura::spellAuraEffectNotImplemented,                                   // 170 SPELL_AURA_170
    &Aura::SpellAuraIncreasePartySpeed,                                     // 171 SPELL_AURA_INCREASE_PARTY_SPEED
    &Aura::SpellAuraIncreaseMovementAndMountedSpeed,                        // 172 SPELL_AURA_INCREASE_MOVEMENT_AND_MOUNTED_SPEED
    &Aura::spellAuraEffectNotImplemented,                                   // 173 SPELL_AURA_173
    &Aura::SpellAuraIncreaseSpellDamageByAttribute,                         // 174 SPELL_AURA_INCREASE_SPELL_DAMAGE_BY_ATTRIBUTE
    &Aura::SpellAuraIncreaseHealingByAttribute,                             // 175 SPELL_AURA_INCREASE_HEALING_BY_ATTRIBUTE
    &Aura::SpellAuraSpiritOfRedemption,                                     // 176 SPELL_AURA_SPIRIT_OF_REDEMPTION
    &Aura::spellAuraEffectNotImplemented,                                   // 177 SPELL_AURA_177
    &Aura::spellAuraEffectNotImplemented,                                   // 178 SPELL_AURA_178
    &Aura::SpellAuraIncreaseAttackerSpellCrit,                              // 179 SPELL_AURA_INCREASE_ATTACKER_SPELL_CRIT
    &Aura::spellAuraEffectNotImplemented,                                   // 180 SPELL_AURA_180
    &Aura::spellAuraEffectNotImplemented,                                   // 181 SPELL_AURA_181
    &Aura::SpellAuraIncreaseArmorByPctInt,                                  // 182 SPELL_AURA_INCREASE_ARMOR_BY_PCT_INT
    &Aura::spellAuraEffectNotImplemented,                                   // 183 SPELL_AURA_183
    &Aura::SpellAuraReduceAttackerMHitChance,                               // 184 SPELL_AURA_REDUCE_ATTACKER_M_HIT_CHANCE
    &Aura::SpellAuraReduceAttackerRHitChance,                               // 185 SPELL_AURA_REDUCE_ATTACKER_R_HIT_CHANCE
    &Aura::SpellAuraReduceAttackerSHitChance,                               // 186 SPELL_AURA_REDUCE_ATTACKER_S_HIT_CHANCE
    &Aura::SpellAuraReduceEnemyMCritChance,                                 // 187 SPELL_AURA_REDUCE_ENEMY_M_CRIT_CHANCE
    &Aura::SpellAuraReduceEnemyRCritChance,                                 // 188 SPELL_AURA_REDUCE_ENEMY_R_CRIT_CHANCE
    &Aura::SpellAuraIncreaseRating,                                         // 189 SPELL_AURA_INCREASE_RATING
    &Aura::SpellAuraIncreaseRepGainPct,                                     // 190 SPELL_AURA_INCREASE_REP_GAIN_PCT
    &Aura::SpellAuraLimitSpeed,                                             // 191 SPELL_AURA_LIMIT_SPEED
    &Aura::SpellAuraMeleeHaste,                                             // 192 SPELL_AURA_MELEE_HASTE
    &Aura::SpellAuraIncreaseTimeBetweenAttacksPCT,                          // 193 SPELL_AURA_INCREASE_TIME_BETWEEN_ATTACKS_PCT
    &Aura::spellAuraEffectNotImplemented,                                   // 194 SPELL_AURA_194
    &Aura::spellAuraEffectNotImplemented,                                   // 195 SPELL_AURA_195
    &Aura::spellAuraEffectNotImplemented,                                   // 196 SPELL_AURA_196
    &Aura::SpellAuraModAttackerCritChance,                                  // 197 SPELL_AURA_MOD_ATTACKER_CRIT_CHANCE
    &Aura::SpellAuraIncreaseAllWeaponSkill,                                 // 198 SPELL_AURA_INCREASE_ALL_WEAPON_SKILL 
    &Aura::SpellAuraIncreaseHitRate,                                        // 199 SPELL_AURA_INCREASE_HIT_RATE
    &Aura::spellAuraEffectNotImplemented,                                   // 200 SPELL_AURA_200
    &Aura::SpellAuraAllowFlight,                                            // 201 SPELL_AURA_ALLOW_FLIGHT
    &Aura::SpellAuraFinishingMovesCannotBeDodged,                           // 202 SPELL_AURA_FINISHING_MOVES_CANNOT_BE_DODGED
    &Aura::SpellAuraReduceCritMeleeAttackDmg,                               // 203 SPELL_AURA_REDUCE_CRIT_MELEE_ATTACK_DMG
    &Aura::SpellAuraReduceCritRangedAttackDmg,                              // 204 SPELL_AURA_REDUCE_CRIT_RANGED_ATTACK_DMG
    &Aura::spellAuraEffectNotImplemented,                                   // 205 SPELL_AURA_205
    &Aura::SpellAuraEnableFlight,                                           // 206 SPELL_AURA_ENABLE_FLIGHT
    &Aura::SpellAuraEnableFlight,                                           // 207 SPELL_AURA_ENABLE_FLIGHT
    &Aura::SpellAuraEnableFlightWithUnmountedSpeed,                         // 208 SPELL_AURA_ENABLE_FLIGHT_WITH_UNMOUNTED_SPEED
    &Aura::spellAuraEffectNotImplemented,                                   // 209 SPELL_AURA_209
    &Aura::spellAuraEffectNotImplemented,                                   // 210 SPELL_AURA_210
    &Aura::SpellAuraIncreaseFlightSpeed,                                    // 211 SPELL_AURA_INCREASE_FLIGHT_SPEED
    &Aura::SpellAuraIncreaseRAPbyStatPct,                                   // 212 SPELL_AURA_INCREASE_RAP_BY_STAT_PCT
    &Aura::SpellAuraIncreaseRageFromDamageDealtPCT,                         // 213 SPELL_AURA_INCREASE_RAGE_FROM_DAMAGE_DEALT_PCT
    &Aura::spellAuraEffectNotImplemented,                                   // 214 SPELL_AURA_214
    &Aura::SpellAuraRemoveReagentCost,                                      // 215 SPELL_AURA_REMOVE_REAGENT_COST
    &Aura::SpellAuraModCastingSpeed,                                        // 216 SPELL_AURA_MOD_CASTING_SPEED
    &Aura::spellAuraEffectNotImplemented,                                   // 217 SPELL_AURA_217
    &Aura::spellAuraEffectNotImplemented,                                   // 218 SPELL_AURA_218
    &Aura::SpellAuraRegenManaStatPCT,                                       // 219 SPELL_AURA_REGEN_MANA_STAT_PCT
    &Aura::SpellAuraSpellHealingStatPCT,                                    // 220 SPELL_AURA_SPELL_HEALING_STAT_PCT
    &Aura::spellAuraEffectNotImplemented,                                   // 221 SPELL_AURA_221
    &Aura::spellAuraEffectNotImplemented,                                   // 222 SPELL_AURA_222
    &Aura::spellAuraEffectNotImplemented,                                   // 223 SPELL_AURA_223
    &Aura::spellAuraEffectNotImplemented,                                   // 224 SPELL_AURA_224
    &Aura::spellAuraEffectNotImplemented,                                   // 225 SPELL_AURA_225
    &Aura::spellAuraEffectPeriodicTriggerDummy,                             // 226 SPELL_AURA_PERIODIC_TRIGGER_DUMMY
    &Aura::spellAuraEffectPeriodicTriggerSpellWithValue,                    // 227 SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE
    &Aura::spellAuraEffectNotImplemented,                                   // 228 SPELL_AURA_228
    &Aura::SpellAuraReduceAOEDamageTaken,                                   // 229 SPELL_AURA_REDUCE_AOE_DAMAGE_TAKEN
    &Aura::SpellAuraIncreaseMaxHealth,                                      // 230 SPELL_AURA_INCREASE_MAX_HEALTH
    &Aura::SpellAuraProcTriggerSpell,                                       // 231 SPELL_AURA_PROC_TRIGGER_SPELL
    &Aura::SpellAuraReduceEffectDuration,                                   // 232 SPELL_AURA_REDUCE_EFFECT_DURATION
    &Aura::spellAuraEffectNotImplemented,                                   // 233 SPELL_AURA_233
    &Aura::SpellAuraReduceEffectDuration,                                   // 234 SPELL_AURA_REDUCE_EFFECT_DURATION
    &Aura::spellAuraEffectNotImplemented,                                   // 235 SPELL_AURA_235
    &Aura::HandleAuraControlVehicle,                                        // 236 HANDLE_AURA_CONTROL_VEHICLE
    &Aura::SpellAuraModHealingByAP,                                         // 237 SPELL_AURA_MOD_HEALING_BY_AP
    &Aura::SpellAuraModSpellDamageByAP,                                     // 238 SPELL_AURA_MOD_SPELL_DAMAGE_BY_AP
    &Aura::SpellAuraModScale,                                               // 239 SPELL_AURA_MOD_SCALE
    &Aura::SpellAuraExpertise,                                              // 240 SPELL_AURA_EXPERTISE
    &Aura::SpellAuraForceMoveForward,                                       // 241 SPELL_AURA_FORCE_MOVE_FORWARD
    &Aura::spellAuraEffectNotImplemented,                                   // 242 SPELL_AURA_242
    &Aura::spellAuraEffectNotImplemented,                                   // 243 SPELL_AURA_243
    &Aura::SpellAuraComprehendLang,                                         // 244 SPELL_AURA_COMPREHEND_LANG
    &Aura::spellAuraEffectNotImplemented,                                   // 245 SPELL_AURA_245
    &Aura::spellAuraEffectNotImplemented,                                   // 246 SPELL_AURA_246
    &Aura::SpellAuraMirrorImage,                                            // 247 SPELL_AURA_MIRROR_IMAGE
    &Aura::SpellAuraModCombatResultChance,                                  // 248 SPELL_AURA_MOD_COMBAT_RESULT_CHANCE
    &Aura::SpellAuraConvertRune,                                            // 249 SPELL_AURA_CONVERT_RUNE
    &Aura::SpellAuraAddHealth,                                              // 250 SPELL_AURA_ADD_HEALTH
    &Aura::spellAuraEffectNotImplemented,                                   // 251 SPELL_AURA_251
    &Aura::spellAuraEffectNotImplemented,                                   // 252 SPELL_AURA_252
    &Aura::SpellAuraBlockMultipleDamage,                                    // 253 SPELL_AURA_BLOCK_MULTIPLE_DAMAGE
    &Aura::SpellAuraModDisarm,                                              // 254 SPELL_AURA_MOD_DISARM
    &Aura::SpellAuraModMechanicDmgTakenPct,                                 // 255 SPELL_AURA_MOD_MECHANIC_DMG_TAKEN_PCT
    &Aura::SpellAuraRemoveReagentCost,                                      // 256 SPELL_AURA_REMOVE_REAGENT_COST
    &Aura::spellAuraEffectNotImplemented,                                   // 257 SPELL_AURA_257
    &Aura::spellAuraEffectNotImplemented,                                   // 258 SPELL_AURA_258
    &Aura::spellAuraEffectNotImplemented,                                   // 259 SPELL_AURA_259
    &Aura::spellAuraEffectNotImplemented,                                   // 260 SPELL_AURA_260
    &Aura::SpellAuraPhase,                                                  // 261 SPELL_AURA_PHASE
    &Aura::spellAuraEffectNotImplemented,                                   // 262 SPELL_AURA_262
    &Aura::SpellAuraAllowOnlyAbility,                                       // 263 SPELL_AURA_ALLOW_ONLY_ABILITY
    &Aura::spellAuraEffectNotImplemented,                                   // 264 SPELL_AURA_264
    &Aura::spellAuraEffectNotImplemented,                                   // 265 SPELL_AURA_265
    &Aura::spellAuraEffectNotImplemented,                                   // 266 SPELL_AURA_266
    &Aura::spellAuraEffectNotImplemented,                                   // 267 SPELL_AURA_267
    &Aura::SpellAuraIncreaseAPbyStatPct,                                    // 268 SPELL_AURA_INCREASE_AP_BY_STAT_PCT
    &Aura::spellAuraEffectNotImplemented,                                   // 269 SPELL_AURA_269
    &Aura::spellAuraEffectNotImplemented,                                   // 270 SPELL_AURA_270
    &Aura::SpellAuraModSpellDamageDOTPct,                                   // 271 SPELL_AURA_MOD_SPELL_DAMAGE_DOT_PCT
    &Aura::spellAuraEffectNotImplemented,                                   // 272 SPELL_AURA_272
    &Aura::spellAuraEffectNotImplemented,                                   // 273 SPELL_AURA_273
    &Aura::SpellAuraConsumeNoAmmo,                                          // 274 SPELL_AURA_CONSUME_NO_AMMO
    &Aura::spellAuraEffectNotImplemented,                                   // 275 SPELL_AURA_275
    &Aura::spellAuraEffectNotImplemented,                                   // 276 SPELL_AURA_276
    &Aura::spellAuraEffectNotImplemented,                                   // 277 SPELL_AURA_277
    &Aura::SpellAuraModDisarm,                                              // 278 SPELL_AURA_MOD_DISARM
    &Aura::SpellAuraMirrorImage2,                                           // 279 SPELL_AURA_MIRROR_IMAGE2
    &Aura::SpellAuraModIgnoreArmorPct,                                      // 280 SPELL_AURA_MOD_IGNORE_ARMOR_PCT
    &Aura::spellAuraEffectNotImplemented,                                   // 281 SPELL_AURA_281
    &Aura::SpellAuraModBaseHealth,                                          // 282 SPELL_AURA_MOD_BASE_HEALTH
    &Aura::SpellAuraModHealingPCT,                                          // 283 SPELL_AURA_MOD_HEALING_PCT
    &Aura::spellAuraEffectNotImplemented,                                   // 284 SPELL_AURA_284
    &Aura::SpellAuraModAttackPowerOfArmor,                                  // 285 SPELL_AURA_MOD_ATTACK_POWER_OF_ARMOR
    &Aura::spellAuraEffectNotImplemented,                                   // 286 SPELL_AURA_286
    &Aura::SpellAuraDeflectSpells,                                          // 287 SPELL_AURA_DEFLECT_SPELLS
    &Aura::spellAuraEffectNotImplemented,                                   // 288 SPELL_AURA_288
    &Aura::spellAuraEffectNotImplemented,                                   // 289 SPELL_AURA_289
    &Aura::spellAuraEffectNotImplemented,                                   // 290 SPELL_AURA_290
    &Aura::spellAuraEffectNotImplemented,                                   // 291 SPELL_AURA_291
    &Aura::SpellAuraCallStabledPet,                                         // 292 SPELL_AURA_CALL_STABLED_PET
    &Aura::spellAuraEffectNotImplemented,                                   // 293 SPELL_AURA_293
    &Aura::spellAuraEffectNotImplemented,                                   // 294 SPELL_AURA_294
    &Aura::spellAuraEffectNotImplemented,                                   // 295 SPELL_AURA_295
    &Aura::spellAuraEffectNotImplemented,                                   // 296 SPELL_AURA_296
    &Aura::spellAuraEffectNotImplemented,                                   // 297 SPELL_AURA_297
    &Aura::spellAuraEffectNotImplemented,                                   // 298 SPELL_AURA_298
    &Aura::spellAuraEffectNotImplemented,                                   // 299 SPELL_AURA_299
    &Aura::spellAuraEffectNotImplemented,                                   // 300 SPELL_AURA_300
    &Aura::spellAuraEffectNotImplemented,                                   // 301 SPELL_AURA_301
    &Aura::spellAuraEffectNotImplemented,                                   // 302 SPELL_AURA_302
    &Aura::spellAuraEffectNotImplemented,                                   // 303 SPELL_AURA_303
    &Aura::spellAuraEffectNotImplemented,                                   // 304 SPELL_AURA_304
    &Aura::spellAuraEffectNotImplemented,                                   // 305 SPELL_AURA_305
    &Aura::spellAuraEffectNotImplemented,                                   // 306 SPELL_AURA_306
    &Aura::spellAuraEffectNotImplemented,                                   // 307 SPELL_AURA_307
    &Aura::spellAuraEffectNotImplemented,                                   // 308 SPELL_AURA_308
    &Aura::spellAuraEffectNotImplemented,                                   // 309 SPELL_AURA_309
    &Aura::spellAuraEffectNotImplemented,                                   // 310 SPELL_AURA_310
    &Aura::spellAuraEffectNotImplemented,                                   // 311 SPELL_AURA_311
    &Aura::spellAuraEffectNotImplemented,                                   // 312 SPELL_AURA_312
    &Aura::spellAuraEffectNotImplemented,                                   // 313 SPELL_AURA_313
    &Aura::spellAuraEffectNotImplemented,                                   // 314 SPELL_AURA_314
    &Aura::spellAuraEffectNotImplemented,                                   // 315 SPELL_AURA_315
    &Aura::spellAuraEffectNotImplemented,                                   // 316 SPELL_AURA_ALLOW_HASTE_AFFECT_DURATION
    &Aura::spellAuraEffectNotImplemented,                                   // 317 SPELL_AURA_317
    &Aura::spellAuraEffectNotImplemented,                                   // 318 SPELL_AURA_318
    &Aura::spellAuraEffectNotImplemented,                                   // 319 SPELL_AURA_319
    &Aura::spellAuraEffectNotImplemented,                                   // 320 SPELL_AURA_320
    &Aura::spellAuraEffectNotImplemented,                                   // 321 SPELL_AURA_321
    &Aura::spellAuraEffectNotImplemented,                                   // 322 SPELL_AURA_322
    &Aura::spellAuraEffectNotImplemented,                                   // 323 SPELL_AURA_323
    &Aura::spellAuraEffectNotImplemented,                                   // 324 SPELL_AURA_324
    &Aura::spellAuraEffectNotImplemented,                                   // 325 SPELL_AURA_325
    &Aura::spellAuraEffectNotImplemented,                                   // 326 SPELL_AURA_326
    &Aura::spellAuraEffectNotImplemented,                                   // 327 SPELL_AURA_327
    &Aura::spellAuraEffectNotImplemented,                                   // 328 SPELL_AURA_328
    &Aura::spellAuraEffectNotImplemented,                                   // 329 SPELL_AURA_329
    &Aura::spellAuraEffectNotImplemented,                                   // 330 SPELL_AURA_330
    &Aura::spellAuraEffectNotImplemented,                                   // 331 SPELL_AURA_331
    &Aura::spellAuraEffectNotImplemented,                                   // 332 SPELL_AURA_332
    &Aura::spellAuraEffectNotImplemented,                                   // 333 SPELL_AURA_333
    &Aura::spellAuraEffectNotImplemented,                                   // 334 SPELL_AURA_334
    &Aura::spellAuraEffectNotImplemented,                                   // 335 SPELL_AURA_335
    &Aura::spellAuraEffectNotImplemented,                                   // 336 SPELL_AURA_336
    &Aura::spellAuraEffectNotImplemented,                                   // 337 SPELL_AURA_337
    &Aura::spellAuraEffectNotImplemented,                                   // 338 SPELL_AURA_338
    &Aura::spellAuraEffectNotImplemented,                                   // 339 SPELL_AURA_339
    &Aura::spellAuraEffectNotImplemented,                                   // 340 SPELL_AURA_340
    &Aura::spellAuraEffectNotImplemented,                                   // 341 SPELL_AURA_341
    &Aura::spellAuraEffectNotImplemented,                                   // 342 SPELL_AURA_342
    &Aura::spellAuraEffectNotImplemented,                                   // 343 SPELL_AURA_343
    &Aura::spellAuraEffectNotImplemented,                                   // 344 SPELL_AURA_344
    &Aura::spellAuraEffectNotImplemented,                                   // 345 SPELL_AURA_345
    &Aura::spellAuraEffectNotImplemented,                                   // 346 SPELL_AURA_346
    &Aura::spellAuraEffectNotImplemented,                                   // 347 SPELL_AURA_347
    &Aura::spellAuraEffectNotImplemented,                                   // 348 SPELL_AURA_348
    &Aura::spellAuraEffectNotImplemented,                                   // 349 SPELL_AURA_349
    &Aura::spellAuraEffectNotImplemented,                                   // 350 SPELL_AURA_350
    &Aura::spellAuraEffectNotImplemented,                                   // 351 SPELL_AURA_351
    &Aura::spellAuraEffectNotImplemented,                                   // 352 SPELL_AURA_352
    &Aura::spellAuraEffectNotImplemented,                                   // 353 SPELL_AURA_353
    &Aura::spellAuraEffectNotImplemented,                                   // 354 SPELL_AURA_354
    &Aura::spellAuraEffectNotImplemented,                                   // 355 SPELL_AURA_355
    &Aura::spellAuraEffectNotImplemented,                                   // 356 SPELL_AURA_356
    &Aura::spellAuraEffectNotImplemented,                                   // 357 SPELL_AURA_357
    &Aura::spellAuraEffectNotImplemented,                                   // 358 SPELL_AURA_358
    &Aura::spellAuraEffectNotImplemented,                                   // 359 SPELL_AURA_359
    &Aura::spellAuraEffectNotImplemented,                                   // 360 SPELL_AURA_360
    &Aura::spellAuraEffectNotImplemented,                                   // 361 SPELL_AURA_361
    &Aura::spellAuraEffectNotImplemented,                                   // 362 SPELL_AURA_362
    &Aura::spellAuraEffectNotImplemented,                                   // 363 SPELL_AURA_363
    &Aura::spellAuraEffectNotImplemented,                                   // 364 SPELL_AURA_364
    &Aura::spellAuraEffectNotImplemented,                                   // 365 SPELL_AURA_365
    &Aura::spellAuraEffectNotImplemented,                                   // 366 SPELL_AURA_366
    &Aura::spellAuraEffectNotImplemented,                                   // 367 SPELL_AURA_367
    &Aura::spellAuraEffectNotImplemented,                                   // 368 SPELL_AURA_368
    &Aura::spellAuraEffectNotImplemented,                                   // 369 SPELL_AURA_369
    &Aura::spellAuraEffectNotImplemented                                    // 370 SPELL_AURA_370
};

const char* SpellAuraNames[TOTAL_SPELL_AURAS] =
{
    "SPELL_AURA_NONE",                                                      //   0 None
    "SPELL_AURA_BIND_SIGHT",                                                //   1 Bind Sight
    "SPELL_AURA_MOD_POSSESS",                                               //   2 Mod Possess
    "SPELL_AURA_PERIODIC_DAMAGE",                                           //   3 Periodic Damage
    "SPELL_AURA_DUMMY",                                                     //   4 Script Aura
    "SPELL_AURA_MOD_CONFUSE",                                               //   5 Mod Confuse
    "SPELL_AURA_MOD_CHARM",                                                 //   6 Mod Charm
    "SPELL_AURA_MOD_FEAR",                                                  //   7 Mod Fear
    "SPELL_AURA_PERIODIC_HEAL",                                             //   8 Periodic Heal
    "SPELL_AURA_MOD_ATTACK_SPEED",                                          //   9 Mod Attack Speed
    "SPELL_AURA_MOD_THREAT_GENERATED",                                      //  10 Mod Threat
    "SPELL_AURA_MOD_TAUNT",                                                 //  11 Taunt
    "SPELL_AURA_MOD_STUN",                                                  //  12 Stun
    "SPELL_AURA_MOD_DAMAGE_DONE",                                           //  13 Mod Damage Done
    "SPELL_AURA_MOD_DAMAGE_TAKEN",                                          //  14 Mod Damage Taken
    "SPELL_AURA_DAMAGE_SHIELD",                                             //  15 Damage Shield
    "SPELL_AURA_MOD_STEALTH",                                               //  16 Mod Stealth
    "SPELL_AURA_MOD_STEALTH_DETECTION",                                     //  17 Mod Detect
    "SPELL_AURA_MOD_INVISIBILITY",                                          //  18 Mod Invisibility
    "SPELL_AURA_MOD_INVISIBILITY_DETECTION",                                //  19 Mod Invisibility Detection
    "SPELL_AURA_PERIODIC_HEAL_PCT",                                         //  20
    "SPELL_AURA_PERIODIC_POWER_PCT",                                        //  21
    "SPELL_AURA_MOD_RESISTANCE",                                            //  22 Mod Resistance
    "SPELL_AURA_PERIODIC_TRIGGER_SPELL",                                    //  23 Periodic Trigger
    "SPELL_AURA_PERIODIC_ENERGIZE",                                         //  24 Periodic Energize
    "SPELL_AURA_MOD_PACIFY",                                                //  25 Pacify
    "SPELL_AURA_MOD_ROOT",                                                  //  26 Root
    "SPELL_AURA_MOD_SILENCE",                                               //  27 Silence
    "SPELL_AURA_REFLECT_SPELLS",                                            //  28 Reflect Spells %
    "SPELL_AURA_MOD_STAT",                                                  //  29 Mod Stat
    "SPELL_AURA_MOD_SKILL",                                                 //  30 Mod Skill
    "SPELL_AURA_MOD_INCREASE_SPEED",                                        //  31 Mod Speed
    "SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED",                                //  32 Mod Speed Mounted
    "SPELL_AURA_MOD_DECREASE_SPEED",                                        //  33 Mod Speed Slow
    "SPELL_AURA_MOD_INCREASE_HEALTH",                                       //  34 Mod Increase Health
    "SPELL_AURA_MOD_INCREASE_ENERGY",                                       //  35 Mod Increase Energy
    "SPELL_AURA_MOD_SHAPESHIFT",                                            //  36 Shapeshift
    "SPELL_AURA_MOD_EFFECT_IMMUNITY",                                       //  37 Immune Effect
    "SPELL_AURA_MOD_STATE_IMMUNITY",                                        //  38 Immune State
    "SPELL_AURA_MOD_SCHOOL_IMMUNITY",                                       //  39 Immune School
    "SPELL_AURA_MOD_DMG_IMMUNITY",                                          //  40 Immune Damage
    "SPELL_AURA_MOD_DISPEL_IMMUNITY",                                       //  41 Immune Dispel Type
    "SPELL_AURA_PROC_TRIGGER_SPELL",                                        //  42 Proc Trigger Spell
    "SPELL_AURA_PROC_TRIGGER_DAMAGE",                                       //  43 Proc Trigger Damage
    "SPELL_AURA_TRACK_CREATURES",                                           //  44 Track Creatures
    "SPELL_AURA_TRACK_RESOURCES",                                           //  45 Track Resources
    "SPELL_AURA_46",                                                        //  46 Mod Parry Skill
    "SPELL_AURA_MOD_PARRY_PERC",                                            //  47 Mod Parry Percent
    "SPELL_AURA_48",                                                        //  48 Mod Dodge Skill
    "SPELL_AURA_MOD_DODGE_PERC",                                            //  49 Mod Dodge Percent
    "SPELL_AURA_50",                                                        //  50 Mod Block Skill
    "SPELL_AURA_MOD_BLOCK_PERC",                                            //  51 Mod Block Percent
    "SPELL_AURA_MOD_CRIT_PERC",                                             //  52 Mod Crit Percent
    "SPELL_AURA_PERIODIC_LEECH",                                            //  53 Periodic Leech
    "SPELL_AURA_MOD_HIT_CHANCE",                                            //  54 Mod Hit Chance
    "SPELL_AURA_MOD_SPELL_HIT_CHANCE",                                      //  55 Mod Spell Hit Chance
    "SPELL_AURA_TRANSFORM",                                                 //  56 Transform
    "SPELL_AURA_MOD_SPELL_CRIT_CHANCE",                                     //  57 Mod Spell Crit Chance
    "SPELL_AURA_INCREASE_SWIM_SPEED",                                       //  58 Mod Speed Swim
    "SPELL_AURA_MOD_CRATURE_DMG_DONE",                                      //  59 Mod Creature Dmg Done
    "SPELL_AURA_PACIFY_SILENCE",                                            //  60 Pacify & Silence
    "SPELL_AURA_MOD_SCALE",                                                 //  61 Mod Scale
    "SPELL_AURA_PERIODIC_HEALTH_FUNNEL",                                    //  62 Periodic Health Funnel
    "SPELL_AURA_63",                                                        //  63 Periodic Mana Funnel
    "SPELL_AURA_PERIODIC_MANALEECH",                                        //  64 Periodic Mana Leech
    "SPELL_AURA_MOD_CASTING_SPEED",                                         //  65 Haste - Spells
    "SPELL_AURA_FEIGN_DEATH",                                               //  66 Feign Death
    "SPELL_AURA_MOD_DISARM",                                                //  67 Disarm
    "SPELL_AURA_MOD_STALKED",                                               //  68 Mod Stalked
    "SPELL_AURA_SCHOOL_ABSORB",                                             //  69 School Absorb
    "SPELL_AURA_70",                                                        //  70 Extra Attacks
    "SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL",                              //  71 Mod School Spell Crit Chance
    "SPELL_AURA_MOD_POWER_COST",                                            //  72 Mod Power Cost
    "SPELL_AURA_MOD_POWER_COST_SCHOOL",                                     //  73 Mod School Power Cost
    "SPELL_AURA_REFLECT_SPELLS_SCHOOL",                                     //  74 Reflect School Spells %
    "SPELL_AURA_MOD_LANGUAGE",                                              //  75 Mod Language
    "SPELL_AURA_ADD_FAR_SIGHT",                                             //  76 Far Sight
    "SPELL_AURA_MECHANIC_IMMUNITY",                                         //  77 Immune Mechanic
    "SPELL_AURA_MOUNTED",                                                   //  78 Mounted
    "SPELL_AURA_MOD_DAMAGE_PERC_DONE",                                      //  79 Mod Dmg %
    "SPELL_AURA_MOD_PERC_STAT",                                             //  80 Mod Stat %
    "SPELL_AURA_SPLIT_DAMAGE",                                              //  81 Split Damage
    "SPELL_AURA_WATER_BREATHING",                                           //  82 Water Breathing
    "SPELL_AURA_MOD_BASE_RESISTANCE",                                       //  83 Mod Base Resistance
    "SPELL_AURA_MOD_REGEN",                                                 //  84 Mod Health Regen
    "SPELL_AURA_MOD_POWER_REGEN",                                           //  85 Mod Power Regen
    "SPELL_AURA_CHANNEL_DEATH_ITEM",                                        //  86 Create Death Item
    "SPELL_AURA_MOD_DAMAGE_PERC_TAKEN",                                     //  87 Mod Dmg % Taken
    "SPELL_AURA_MOD_REGEN_PERCENT",                                         //  88 Mod Health Regen Percent
    "SPELL_AURA_PERIODIC_DAMAGE_PERCENT",                                   //  89 Periodic Damage Percent
    "SPELL_AURA_MOD_RESIST_CHANCE",                                         //  90 Mod Resist Chance
    "SPELL_AURA_MOD_DETECT_RANGE",                                          //  91 Mod Detect Range
    "SPELL_AURA_PREVENTS_FLEEING",                                          //  92 Prevent Fleeing
    "SPELL_AURA_MOD_UNATTACKABLE",                                          //  93 Mod Uninteractible
    "SPELL_AURA_INTERRUPT_REGEN",                                           //  94 Interrupt Regen
    "SPELL_AURA_GHOST",                                                     //  95 Ghost
    "SPELL_AURA_MAGNET",                                                    //  96 Spell Magnet
    "SPELL_AURA_MANA_SHIELD",                                               //  97 Mana Shield
    "SPELL_AURA_SKILL_TALENT",                                              //  98 Mod Skill Talent
    "SPELL_AURA_MOD_ATTACK_POWER",                                          //  99 Mod Attack Power
    "SPELL_AURA_VISIBLE",                                                   // 100 Auras Visible
    "SPELL_AURA_MOD_RESISTANCE_PCT",                                        // 101 Mod Resistance %
    "SPELL_AURA_MOD_CREATURE_ATTACK_POWER",                                 // 102 Mod Creature Attack Power
    "SPELL_AURA_MOD_TOTAL_THREAT",                                          // 103 Mod Total Threat (Fade)
    "SPELL_AURA_WATER_WALK",                                                // 104 Water Walk
    "SPELL_AURA_FEATHER_FALL",                                              // 105 Feather Fall
    "SPELL_AURA_HOVER",                                                     // 106 Hover
    "SPELL_AURA_ADD_FLAT_MODIFIER",                                         // 107 Add Flat Modifier
    "SPELL_AURA_ADD_PCT_MOD",                                               // 108 Add % Modifier
    "SPELL_AURA_ADD_CLASS_TARGET_TRIGGER",                                  // 109 Add Class Target Trigger
    "SPELL_AURA_MOD_POWER_REG_PERC",                                        // 110 Mod Power Regen %
    "SPELL_AURA_111",                                                       // 111 Add Class Caster Hit Trigger
    "SPELL_AURA_OVERRIDE_CLASS_SCRIPTS",                                    // 112 Override Class Scripts
    "SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN",                                   // 113 Mod Ranged Dmg Taken
    "SPELL_AURA_114",                                                       // 114 Mod Ranged % Dmg Taken
    "SPELL_AURA_MOD_HEALING",                                               // 115 Mod Healing
    "SPELL_AURA_IGNORE_REGEN_INTERRUPT",                                    // 116 Regen During Combat
    "SPELL_AURA_MOD_MECHANIC_RESISTANCE",                                   // 117 Mod Mechanic Resistance
    "SPELL_AURA_MOD_HEALING_PCT",                                           // 118 Mod Healing %
    "SPELL_AURA_119",                                                       // 119 Share Pet Tracking
    "SPELL_AURA_UNTRACKABLE",                                               // 120 Untrackable
    "SPELL_AURA_EMPHATY",                                                   // 121 Empathy (Lore, whatever)
    "SPELL_AURA_MOD_OFFHANDDAMAGE_PCT",                                     // 122 Mod Offhand Dmg %
    "SPELL_AURA_MOD_PENETRATION",                                           // 123 Mod Power Cost % (armor penetration & spell penetration. NOT power cost!)
    "SPELL_AURA_MOD_RANGED_ATTACK_POWER",                                   // 124 Mod Ranged Attack Power
    "SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN",                                    // 125 Mod Melee Dmg Taken
    "SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT",                                // 126 Mod Melee % Dmg Taken
    "SPELL_AURA_RAP_ATTACKER_BONUS",                                        // 127 Rngd Atk Pwr Attckr Bonus
    "SPELL_AURA_MOD_POSSESS_PET",                                           // 128 Mod Possess Pet
    "SPELL_AURA_MOD_INCREASE_SPEED_ALWAYS",                                 // 129 Mod Speed Always
    "SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED",                                // 130 Mod Mounted Speed Always
    "SPELL_AURA_MOD_CREATURE_RANGED_ATTACK_POWER",                          // 131 Mod Creature Ranged Attack Power
    "SPELL_AURA_MOD_INCREASE_ENERGY_PERC",                                  // 132 Mod Increase Energy %
    "SPELL_AURA_MOD_INCREASE_HEALTH_PERC",                                  // 133 Mod Max Health %
    "SPELL_AURA_MOD_MANA_REG_INTERRUPT",                                    // 134 Mod Interrupted Mana Regen
    "SPELL_AURA_MOD_HEALING_DONE",                                          // 135 Mod Healing Done
    "SPELL_AURA_MOD_HEALING_DONE_PCT",                                      // 136 Mod Healing Done %
    "SPELL_AURA_MOD_TOTAL_STAT_PERC",                                       // 137 Mod Total Stat %
    "SPELL_AURA_MOD_HASTE",                                                 // 138 Haste - Melee
    "SPELL_AURA_FORCE_REACTION",                                            // 139 Force Reaction
    "SPELL_AURA_MOD_RANGED_HASTE",                                          // 140 Haste - Ranged
    "SPELL_AURA_MOD_RANGED_AMMO_HASTE",                                     // 141 Haste - Ranged (Ammo Only)
    "SPELL_AURA_MOD_BASE_RESISTANCE_PERC",                                  // 142 Mod Base Resistance %
    "SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE",                                  // 143 Mod Resistance Exclusive
    "SPELL_AURA_SAFE_FALL",                                                 // 144 Safe Fall
    "SPELL_AURA_145",                                                       // 145 Charisma
    "SPELL_AURA_146",                                                       // 146 Persuaded
    "SPELL_AURA_147",                                                       // 147 Add Creature Immunity // https://www.wowhead.com/spell=36798/
    "SPELL_AURA_RETAIN_COMBO_POINTS",                                       // 148 Retain Combo Points
    "SPELL_AURA_RESIST_PUSHBACK",                                           // 149 Resist Pushback // Simply resist spell casting delay
    "SPELL_AURA_MOD_SHIELD_BLOCK_PCT",                                      // 150 Mod Shield Block %
    "SPELL_AURA_TRACK_STEALTHED",                                           // 151 Track Stealthed
    "SPELL_AURA_MOD_DETECTED_RANGE",                                        // 152 Mod Detected Range
    "SPELL_AURA_SPLIT_DAMAGE_FLAT",                                         // 153 Split Damage Flat
    "SPELL_AURA_MOD_STEALTH_LEVEL",                                         // 154 Stealth Level Modifier
    "SPELL_AURA_MOD_UNDERWATER_BREATHING",                                  // 155 Mod Water Breathing
    "SPELL_AURA_MOD_REPUTATION_ADJUST",                                     // 156 Mod Reputation Gain
    "SPELL_AURA_157",                                                       // 157 Mod Pet Damage
    "SPELL_AURA_MOD_BLOCK_VALUE",                                           // 158 used Apply Aura: Mod Shield Block // https://classic.wowhead.com/spell=25036/
    "SPELL_AURA_NO_PVP_CREDIT",                                             // 159 used Apply Aura: No PVP Credit // https://classic.wowhead.com/spell=2479/
    "SPELL_AURA_160",                                                       // 160 used Apply Aura: Mod Side/Rear PBAE Damage Taken % // https://classic.wowhead.com/spell=23198
    "SPELL_AURA_MOD_HEALTH_REG_IN_COMBAT",                                  // 161 Mod Health Regen In Combat
    "SPELL_AURA_PERIODIC_POWER_BURN",                                       // 162 Power Burn
    "SPELL_AURA_MOD_CRIT_DMG_PHYSICAL",                                     // 163 missing Apply Aura: Mod Critical Damage Bonus (Physical)
    "SPELL_AURA_164",                                                       // 164 missing used // test spell
    "SPELL_AURA_AP_ATTACKER_BONUS",                                         // 165 Melee AP Attacker Bonus
    "SPELL_AURA_MOD_P_ATTACK_POWER",                                        // 166 missing used Apply Aura: Mod Attack Power % // https://classic.wowhead.com/spell=30803/
    "SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT",                               // 167 Mod Ranged Attack Power % // missing // http://www.thottbot.com/s34485
    "SPELL_AURA_INCREASE_DAMAGE_TYPE_PCT",                                  // 168 missing used // Apply Aura: Increase Damage % *type* // https://classic.wowhead.com/spell=24991
    "SPELL_AURA_INCREASE_CRICTICAL_TYPE_PCT",                               // 169 missing used // Apply Aura: Increase Critical % *type* // https://classic.wowhead.com/spell=24293
    "SPELL_AURA_170",                                                       // 170 Detect Amore // Apply Aura: Detect Amore // https://classic.wowhead.com/spell=26802
    "SPELL_AURA_INCREASE_PARTY_SPEED",                                      // 171
    "SPELL_AURA_INCREASE_MOVEMENT_AND_MOUNTED_SPEED",                       // 172 // used // Apply Aura: Increase Movement and Mounted Speed (Non-Stacking) // https://classic.wowhead.com/spell=26022 2e effect
    "SPELL_AURA_173",                                                       // 173 // Apply Aura: Allow Champion Spells
    "SPELL_AURA_INCREASE_SPELL_DAMAGE_BY_ATTRIBUTE",                        // 174 // used // Apply Aura: Increase Spell Damage by % Spirit (Spells) // https://classic.wowhead.com/spell=15031
    "SPELL_AURA_INCREASE_HEALING_BY_ATTRIBUTE",                             // 175 // used // Apply Aura: Increase Spell Healing by % Spirit // https://classic.wowhead.com/spell=15031
    "SPELL_AURA_SPIRIT_OF_REDEMPTION",                                      // 176 // used // Apply Aura: Spirit of Redemption
    "SPELL_AURA_177",                                                       // 177 // used // Apply Aura: Area Charm // https://classic.wowhead.com/spell=26740
    "SPELL_AURA_178",                                                       // 178 missing // Apply Aura: Increase Debuff Resistance 
    "SPELL_AURA_INCREASE_ATTACKER_SPELL_CRIT",                              // 179 Apply Aura: Increase Attacker Spell Crit % *type* // https://classic.wowhead.com/spell=12579
    "SPELL_AURA_180",                                                       // 180 // Apply Aura: Increase Spell Damage *type* // https://classic.wowhead.com/spell=29113
    "SPELL_AURA_181",                                                       // 181 missing
    "SPELL_AURA_INCREASE_ARMOR_BY_PCT_INT",                                 // 182 missing // Apply Aura: Increase Armor by % of Intellect // https://classic.wowhead.com/spell=28574
    "SPELL_AURA_183",                                                       // 183 // used // Apply Aura: Decrease Critical Threat by % (Spells) // https://classic.wowhead.com/spell=28746/ (SPELL_AURA_MOD_CRITICAL_THREAT)
    "SPELL_AURA_REDUCE_ATTACKER_M_HIT_CHANCE",                              // 184 // Apply Aura: Reduces Attacker Chance to Hit with Melee // http://www.thottbot.com/s31678
    "SPELL_AURA_REDUCE_ATTACKER_R_HIT_CHANCE",                              // 185 // Apply Aura: Reduces Attacker Chance to Hit with Ranged // https://classic.wowhead.com/spell=30895
    "SPELL_AURA_REDUCE_ATTACKER_S_HIT_CHANCE",                              // 186 // Apply Aura: Reduces Attacker Chance to Hit with Spells (Spells) // https://classic.wowhead.com/spell=30895
    "SPELL_AURA_REDUCE_ENEMY_M_CRIT_CHANCE",                                // 187 missing // used // Apply Aura: Reduces Attacker Chance to Crit with Melee (Ranged?)
    "SPELL_AURA_REDUCE_ENEMY_R_CRIT_CHANCE",                                // 188 missing // used // Apply Aura: Reduces Attacker Chance to Crit with Ranged (Melee?)
    "SPELL_AURA_INCREASE_RATING",                                           // 189 missing // Apply Aura: Increases Rating
    "SPELL_AURA_INCREASE_REP_GAIN_PCT",                                     // 190 // used // Apply Aura: Increases Reputation Gained by % // https://classic.wowhead.com/spell=30754/ (SPELL_AURA_MOD_FACTION_REPUTATION_GAIN)
    "SPELL_AURA_LIMIT_SPEED",                                               // 191 speed limit // https://classic.wowhead.com/spell=29894/
    "SPELL_AURA_MELEE_HASTE",                                               // 192 Apply Aura: Melee Slow %
    "SPELL_AURA_INCREASE_TIME_BETWEEN_ATTACKS_PCT",                         // 193 Apply Aura: Increase Time Between Attacks (Melee, Ranged and Spell) by %
    "SPELL_AURA_194",                                                       // 194 NOT USED ANYMORE - 174 used instead // Apply Aura: Increase Spell Damage by % of Intellect (All)
    "SPELL_AURA_195",                                                       // 195 NOT USED ANYMORE - 175 used instead // Apply Aura: Increase Healing by % of Intellect
    "SPELL_AURA_196",                                                       // 196 Apply Aura: Mod All Weapon Skills (6)
    "SPELL_AURA_MOD_ATTACKER_CRIT_CHANCE",                                  // 197 Apply Aura: Reduce Attacker Critical Hit Chance by %
    "SPELL_AURA_INCREASE_ALL_WEAPON_SKILL",                                 // 198
    "SPELL_AURA_INCREASE_HIT_RATE",                                         // 199 Apply Aura: Increases Spell % To Hit (Fire, Nature, Frost)
    "SPELL_AURA_200",                                                       // 200 Increases experience earned by $s1%. Lasts $d.
    "SPELL_AURA_ALLOW_FLIGHT",                                              // 201 isn't it same like 206 and 207?
    "SPELL_AURA_FINISHING_MOVES_CANNOT_BE_DODGED",                          // 202 Finishing moves cannot be dodged - 32601, 44452
    "SPELL_AURA_REDUCE_CRIT_MELEE_ATTACK_DMG",                              // 203 Apply Aura: Reduces Attacker Critical Hit Damage with Melee by %
    "SPELL_AURA_REDUCE_CRIT_RANGED_ATTACK_DMG",                             // 204 Apply Aura: Reduces Attacker Critical Hit Damage with Ranged by %
    "SPELL_AURA_205",                                                       // 205 "School" Vulnerability
    "SPELL_AURA_ENABLE_FLIGHT",                                             // 206 Take flight on a worn old carpet. - Spell 43343
    "SPELL_AURA_ENABLE_FLIGHT",                                             // 207 set fly mod flight speed?
    "SPELL_AURA_ENABLE_FLIGHT_WITH_UNMOUNTED_SPEED",                        // 208 mod flight speed?
    "SPELL_AURA_209",                                                       // 209 mod flight speed?
    "SPELL_AURA_210",                                                       // 210 commentator's command - spell 42009
    "SPELL_AURA_INCREASE_FLIGHT_SPEED",                                     // 211 Apply Aura: Increase Ranged Atk Power by % of stat
    "SPELL_AURA_INCREASE_RAP_BY_STAT_PCT",                                  // 212 Apply Aura: Increase Rage from Damage Dealt by %
    "SPELL_AURA_INCREASE_RAGE_FROM_DAMAGE_DEALT_PCT",                       // 213 // Tamed Pet Passive (DND)
    "SPELL_AURA_214",                                                       // 214 // arena preparation buff - cancel soul shard requirement?
    "SPELL_AURA_REMOVE_REAGENT_COST",                                       // 215 Increases casting time %, reuse existing handler...
    "SPELL_AURA_MOD_CASTING_SPEED",                                         // 216 // not used
    "SPELL_AURA_217",                                                       // 217 // increases time between ranged attacks
    "SPELL_AURA_218",                                                       // 218 Regenerate mana equal to $s1% of your Intellect every 5 sec, even while casting
    "SPELL_AURA_REGEN_MANA_STAT_PCT",                                       // 219 Increases your healing spells  by up to $s1% of your Strength // increases your critical strike rating by 35% of your spirit // Molten Armor only?
    "SPELL_AURA_SPELL_HEALING_STAT_PCT",                                    // 220 Detaunt "Ignores an enemy, forcing the caster to not attack it unless there is no other target nearby. When the effect wears off, the creature will attack the most threatening target."
    "SPELL_AURA_221",                                                       // 221 // not used
    "SPELL_AURA_222",                                                       // 222 // used in one spell, cold stare 43593
    "SPELL_AURA_223",                                                       // 223 // not used
    "SPELL_AURA_224",                                                       // 224
    "SPELL_AURA_225",                                                       // 225 // Prayer of Mending "Places a spell on the target that heals them for $s1 the next time they take damage.  When the heal occurs, Prayer of Mending jumps to a raid member within $a1 yards.  Jumps up to $n times and lasts $d after each jump.  This spell can only be placed on one target at a time."
    "SPELL_AURA_PERIODIC_TRIGGER_DUMMY",                                    // 226 // used in brewfest spells, headless horseman, Aspect of the Viper
    "SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE",                         // 227 // Used by Mind Flay, Siege Turrets 'Machine gun' and a few other spells.
    "SPELL_AURA_228",                                                       // 228 Stealth Detection. https://www.wowhead.com/spell=34709 // handled in Unit::canSee
    "SPELL_AURA_REDUCE_AOE_DAMAGE_TAKEN",                                   // 229  Apply Aura:Reduces the damage your pet takes from area of effect attacks // http://www.thottbot.com/s35694
    "SPELL_AURA_INCREASE_MAX_HEALTH",                                       // 230 Used by Increase Max Health (commanding shout);
    "SPELL_AURA_PROC_TRIGGER_SPELL",                                        // 231 curse a target https://www.wowhead.com/spell=40303
    "SPELL_AURA_REDUCE_EFFECT_DURATION",                                    // 232 // Reduces duration of Magic effects by $s2%.
    "SPELL_AURA_233",                                                       // 233 // Beer Goggles
    "SPELL_AURA_REDUCE_EFFECT_DURATION",                                    // 234 Apply Aura: Reduces Silence or Interrupt effects, Item spell magic https://www.wowhead.com/spell=42184
    "SPELL_AURA_235",                                                       // 235 // 33206 Instantly reduces a friendly target's threat by $44416s1%, reduces all damage taken by $s1% and increases resistance to Dispel mechanics by $s2% for $d.
    "HANDLE_AURA_CONTROL_VEHICLE",                                          // 236
    "SPELL_AURA_MOD_HEALING_BY_AP",                                         // 237 // increase spell healing by X pct from attack power
    "SPELL_AURA_MOD_SPELL_DAMAGE_BY_AP",                                    // 238 // increase spell dmg by X pct from attack power
    "SPELL_AURA_MOD_SCALE",                                                 // 239
    "SPELL_AURA_EXPERTISE",                                                 // 240
    "SPELL_AURA_FORCE_MOVE_FORWARD",                                        // 241 makes target to run forward
    "SPELL_AURA_242",                                                       // 242
    "SPELL_AURA_243",                                                       // 243
    "SPELL_AURA_COMPREHEND_LANG",                                           // 244 allows target to understand itself while talking in different language
    "SPELL_AURA_245",                                                       // 245
    "SPELL_AURA_246",                                                       // 246
    "SPELL_AURA_MIRROR_IMAGE",                                              // 247
    "SPELL_AURA_MOD_COMBAT_RESULT_CHANCE",                                  // 248
    "SPELL_AURA_CONVERT_RUNE",                                              // 249 Convert rune
    "SPELL_AURA_ADD_HEALTH",                                                // 250
    "SPELL_AURA_251",                                                       // 251 Mod Enemy Dodge
    "SPELL_AURA_252",                                                       // 252 Reduces the target's ranged, melee attack, and casting speed by X pct for Y sec.
    "SPELL_AURA_BLOCK_MULTIPLE_DAMAGE",                                     // 253
    "SPELL_AURA_MOD_DISARM",                                                // 254
    "SPELL_AURA_MOD_MECHANIC_DMG_TAKEN_PCT",                                // 255
    "SPELL_AURA_REMOVE_REAGENT_COST",                                       // 256 Remove reagent cost
    "SPELL_AURA_257",                                                       // 257 Mod Target Resist By Spell Class (does damage in the form of X damage, ignoring all resistances, absorption, and immunity mechanics. - http://thottbot.com/s47271)
    "SPELL_AURA_258",                                                       // 258 Mod Spell Visual
    "SPELL_AURA_259",                                                       // 259 Mod Periodic Damage Taken Pct - Periodic Shadow damage taken increased by 3% // http://thottbot.com/s60448
    "SPELL_AURA_260",                                                       // 260 Screen Effect
    "SPELL_AURA_PHASE",                                                     // 261
    "SPELL_AURA_262",                                                       // 262
    "SPELL_AURA_ALLOW_ONLY_ABILITY",                                        // 263
    "SPELL_AURA_264",                                                       // 264
    "SPELL_AURA_265",                                                       // 265
    "SPELL_AURA_266",                                                       // 266
    "SPELL_AURA_267",                                                       // 267 Prevent the application of harmful magical effects. used only by Dk's Anti Magic Shell
    "SPELL_AURA_INCREASE_AP_BY_STAT_PCT",                                   // 268 Mental Dexterity (increases ap by x% of intellect)
    "SPELL_AURA_269",                                                       // 269 Damage reduction effects ignored. (?) - http://thottbot.com/s57318
    "SPELL_AURA_270",                                                       // 270 Ignore target resist
    "SPELL_AURA_MOD_SPELL_DAMAGE_DOT_PCT",                                  // 271
    "SPELL_AURA_272",                                                       // 272
    "SPELL_AURA_273",                                                       // 273 Some sort of dummy aura? https://www.wowhead.com/spell=54844 + https://classic.wowhead.com/spell=26659
    "SPELL_AURA_CONSUME_NO_AMMO",                                           // 274 Consumes no ammo
    "SPELL_AURA_275",                                                       // 275 Ignores form/shapeshift requirements
    "SPELL_AURA_276",                                                       // 276 Mod Damage % Mechanic
    "SPELL_AURA_277",                                                       // 277
    "SPELL_AURA_MOD_DISARM",                                                // 278
    "SPELL_AURA_MIRROR_IMAGE2",                                             // 279 Modify models(?)
    "SPELL_AURA_MOD_IGNORE_ARMOR_PCT",                                      // 280
    "SPELL_AURA_281",                                                       // 281 Mod Honor gain increased by X pct. Final Reward Honor increased by X pct for Y Rank and above. https://www.wowhead.com/spell=58560 && https://www.wowhead.com/spell=58557/
    "SPELL_AURA_MOD_BASE_HEALTH",                                           // 282
    "SPELL_AURA_MOD_HEALING_PCT",                                           // 283 Increases all healing received by X pct
    "SPELL_AURA_284",                                                       // 284 not used by any spells (3.08a)
    "SPELL_AURA_MOD_ATTACK_POWER_OF_ARMOR",                                 // 285
    "SPELL_AURA_286",                                                       // 286
    "SPELL_AURA_DEFLECT_SPELLS",                                            // 287
    "SPELL_AURA_288",                                                       // 288 not used by any spells (3.09) except 1 test spell.
    "SPELL_AURA_289",                                                       // 289
    "SPELL_AURA_290",                                                       // 290
    "SPELL_AURA_291",                                                       // 291
    "SPELL_AURA_CALL_STABLED_PET",                                          // 292 call stabled pet
    "SPELL_AURA_293",                                                       // 293 2 test spells
    "SPELL_AURA_294",                                                       // 294 2 spells, possible prevent mana regen
    "SPELL_AURA_295",                                                       // 295
    "SPELL_AURA_296",                                                       // 296
    "SPELL_AURA_297",                                                       // 297
    "SPELL_AURA_298",                                                       // 298
    "SPELL_AURA_299",                                                       // 299
    "SPELL_AURA_300",                                                       // 300
    "SPELL_AURA_301",                                                       // 301
    "SPELL_AURA_302",                                                       // 302
    "SPELL_AURA_303",                                                       // 303
    "SPELL_AURA_304",                                                       // 304
    "SPELL_AURA_305",                                                       // 305
    "SPELL_AURA_306",                                                       // 306
    "SPELL_AURA_307",                                                       // 307
    "SPELL_AURA_308",                                                       // 308
    "SPELL_AURA_309",                                                       // 309
    "SPELL_AURA_310",                                                       // 310
    "SPELL_AURA_311",                                                       // 311
    "SPELL_AURA_312",                                                       // 312
    "SPELL_AURA_313",                                                       // 313
    "SPELL_AURA_314",                                                       // 314
    "SPELL_AURA_315",                                                       // 315
    "SPELL_AURA_ALLOW_HASTE_AFFECT_DURATION",                               // 316
    "SPELL_AURA_317",                                                       // 317
    "SPELL_AURA_318",                                                       // 318
    "SPELL_AURA_319",                                                       // 319
    "SPELL_AURA_320",                                                       // 320
    "SPELL_AURA_321",                                                       // 321
    "SPELL_AURA_322",                                                       // 322
    "SPELL_AURA_323",                                                       // 323
    "SPELL_AURA_324",                                                       // 324
    "SPELL_AURA_325",                                                       // 325
    "SPELL_AURA_326",                                                       // 326
    "SPELL_AURA_327",                                                       // 327
    "SPELL_AURA_328",                                                       // 328
    "SPELL_AURA_329",                                                       // 329
    "SPELL_AURA_330",                                                       // 330
    "SPELL_AURA_331",                                                       // 331
    "SPELL_AURA_332",                                                       // 332
    "SPELL_AURA_333",                                                       // 333
    "SPELL_AURA_334",                                                       // 334
    "SPELL_AURA_335",                                                       // 335
    "SPELL_AURA_336",                                                       // 336
    "SPELL_AURA_337",                                                       // 337
    "SPELL_AURA_338",                                                       // 338
    "SPELL_AURA_339",                                                       // 339
    "SPELL_AURA_340",                                                       // 340
    "SPELL_AURA_341",                                                       // 341
    "SPELL_AURA_342",                                                       // 342
    "SPELL_AURA_343",                                                       // 343
    "SPELL_AURA_344",                                                       // 344
    "SPELL_AURA_345",                                                       // 345
    "SPELL_AURA_346",                                                       // 346
    "SPELL_AURA_347",                                                       // 347
    "SPELL_AURA_348",                                                       // 348
    "SPELL_AURA_349",                                                       // 349
    "SPELL_AURA_350",                                                       // 350
    "SPELL_AURA_351",                                                       // 351
    "SPELL_AURA_352",                                                       // 352
    "SPELL_AURA_353",                                                       // 353
    "SPELL_AURA_354",                                                       // 354
    "SPELL_AURA_355",                                                       // 355
    "SPELL_AURA_356",                                                       // 356
    "SPELL_AURA_357",                                                       // 357
    "SPELL_AURA_358",                                                       // 358
    "SPELL_AURA_359",                                                       // 359
    "SPELL_AURA_360",                                                       // 360
    "SPELL_AURA_361",                                                       // 361
    "SPELL_AURA_362",                                                       // 362
    "SPELL_AURA_363",                                                       // 363
    "SPELL_AURA_364",                                                       // 364
    "SPELL_AURA_365",                                                       // 365
    "SPELL_AURA_366",                                                       // 366
    "SPELL_AURA_367",                                                       // 367
    "SPELL_AURA_368",                                                       // 368
    "SPELL_AURA_369",                                                       // 369
    "SPELL_AURA_370",                                                       // 370
};

void Aura::spellAuraEffectNotImplemented(AuraEffectModifier* aurEff, bool /*apply*/)
{
    LogDebugFlag(LF_AURA, "Aura::applyModifiers : Unknown aura id %u for spell id %u", aurEff->mAuraEffect, getSpellId());
}

void Aura::spellAuraEffectNotUsed(AuraEffectModifier* /*aurEff*/, bool /*apply*/)
{
    // Handled elsewhere or not used, so do nothing
}

void Aura::spellAuraEffectPeriodicDamage(AuraEffectModifier* aurEff, bool apply)
{
    if (apply)
    {
        // Hackfixes from legacy aura effect
        // Move these to spellscript
        switch (getSpellInfo()->getId())
        {
            //mage talent ignite
            case 12654:
            {
                if (!pSpellId) //we need a parent spell and should always have one since it procs on it
                    break;
                SpellInfo const* parentsp = sSpellMgr.getSpellInfo(pSpellId);
                if (!parentsp)
                    return;
                auto c = GetUnitCaster();
                if (c != nullptr && c->isPlayer())
                {
                    aurEff->mDamage = float2int32(static_cast< Player* >(c)->m_casted_amount[SCHOOL_FIRE] * parentsp->getEffectBasePoints(0) / 100.0f);
                }
                else if (c != nullptr)
                {
                    if (!aurEff->mDamage)
                        return;

                    Spell* spell = sSpellMgr.newSpell(c, parentsp, false, nullptr);
                    SpellCastTargets castTargets(m_target->getGuid());

                    //this is so not good, maybe parent spell has more then dmg effect and we use it to calc our new dmg :(
                    aurEff->mDamage = 0;
                    for (uint8 i = 0; i < 3; ++i)
                    {
                        aurEff->mDamage += spell->CalculateEffect(i, m_target) * parentsp->getEffectBasePoints(0) / 100;
                    }
                    delete spell;
                    spell = nullptr;
                }

            }
            // Warrior deep wounds
            case 12162:
            case 12721:
            {
                auto c = GetUnitCaster();
                if (!c->isPlayer())
                    break;

                uint32 multiplyer = 0;
                if (pSpellId == 12834)
                    multiplyer = 16; //level 1 of the talent should apply 16 of average melee weapon dmg
                else if (pSpellId == 12849)
                    multiplyer = 32;
                else if (pSpellId == 12867)
                    multiplyer = 48;

                if (multiplyer)
                {
                    Player* pr = static_cast<Player*>(c);
                    Item* it;
                    it = pr->getItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
                    if (it)
                    {
                        aurEff->mDamage = 0;
                        for (uint8 i = 0; i < MAX_ITEM_PROTO_DAMAGES; ++i)
                            if (it->getItemProperties()->Damage[i].Type == SCHOOL_NORMAL)
                                aurEff->mDamage += int32((it->getItemProperties()->Damage[i].Min + it->getItemProperties()->Damage[i].Max) / 2);
                        aurEff->mDamage = multiplyer * aurEff->mDamage / 100;
                    }
                }
            }
        }

        // Hackfixes end

        const auto casterUnit = GetUnitCaster();

        // Apply damage over time modifiers
        if (casterUnit != nullptr)
        {
            spellModFlatIntValue(casterUnit->SM_FDOT, &aurEff->mDamage, getSpellInfo()->getSpellFamilyFlags());
            spellModPercentageIntValue(casterUnit->SM_PDOT, &aurEff->mDamage, getSpellInfo()->getSpellFamilyFlags());
        }

        if (aurEff->mDamage <= 0)
            return;

        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;

        // Hackfixes from legacy aura effect
        if (getSpellInfo()->custom_BGR_one_buff_on_target & SPELL_TYPE_WARLOCK_IMMOLATE)
            m_target->addAuraStateAndAuras(AURASTATE_FLAG_CONFLAGRATE);
        //maybe poison aurastate should get triggered on other spells too ?
        else if (getSpellInfo()->custom_c_is_flags & SPELL_FLAG_IS_POISON)  //deadly poison
            m_target->addAuraStateAndAuras(AURASTATE_FLAG_ENVENOM);
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif

        if (m_spellInfo->custom_BGR_one_buff_on_target & SPELL_TYPE_WARLOCK_IMMOLATE)
            m_target->removeAuraStateAndAuras(AURASTATE_FLAG_CONFLAGRATE);
        //maybe poison aurastate should get triggered on other spells too ?
        else if (m_spellInfo->custom_c_is_flags & SPELL_FLAG_IS_POISON)  //deadly poison
            m_target->removeAuraStateAndAuras(AURASTATE_FLAG_ENVENOM);
    }
}

void Aura::spellAuraEffectPeriodicHeal(AuraEffectModifier* aurEff, bool apply)
{
    if (apply)
    {
        auto value = aurEff->mDamage;

        // Apply modifiers
        const auto casterUnit = GetUnitCaster();
        if (casterUnit != nullptr)
        {
            spellModFlatIntValue(casterUnit->SM_FDOT, &aurEff->mDamage, getSpellInfo()->getSpellFamilyFlags());
            spellModPercentageIntValue(casterUnit->SM_PDOT, &aurEff->mDamage, getSpellInfo()->getSpellFamilyFlags());

            //\ todo: these are already applied in Spell::CalculateEffect
            spellModFlatIntValue(casterUnit->SM_FMiscEffect, &value, getSpellInfo()->getSpellFamilyFlags());
            spellModPercentageIntValue(casterUnit->SM_PMiscEffect, &value, getSpellInfo()->getSpellFamilyFlags());
        }

        if (value <= 0)
            return;

        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;

        // Hackfix for aura state
        if (getSpellInfo()->getSpellFamilyName() == SPELLFAMILY_DRUID &&
            (getSpellInfo()->getSpellFamilyFlags(0) == 0x10 || getSpellInfo()->getSpellFamilyFlags(0) == 0x40))
        {
            getOwner()->addAuraStateAndAuras(AURASTATE_FLAG_SWIFTMEND);
            if (!sEventMgr.HasEvent(m_target, EVENT_REJUVENATION_FLAG_EXPIRE))
                sEventMgr.AddEvent(m_target, &Unit::removeAuraStateAndAuras, AURASTATE_FLAG_SWIFTMEND, EVENT_REJUVENATION_FLAG_EXPIRE, getTimeLeft(), 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
            else
                sEventMgr.ModifyEventTimeLeft(m_target, EVENT_REJUVENATION_FLAG_EXPIRE, getTimeLeft(), 0);
        }
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectPeriodicHealPct(AuraEffectModifier* aurEff, bool apply)
{
    if (apply)
    {
        aurEff->mDamage = static_cast<int32_t>(std::ceil(getOwner()->getMaxHealth() * (aurEff->mBaseDamage / 100.0f))) * getStackCount();

        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectPeriodicPowerPct(AuraEffectModifier* aurEff, bool apply)
{
    if (aurEff->miscValue < POWER_TYPE_MANA || aurEff->miscValue >= TOTAL_PLAYER_POWER_TYPES)
        return;

    if (apply)
    {
        const auto powerType = static_cast<PowerType>(aurEff->miscValue);
        aurEff->mDamage = static_cast<int32_t>(std::ceil(getOwner()->getMaxPower(powerType) * (aurEff->mBaseDamage / 100.0f))) * getStackCount();

        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectPeriodicTriggerSpell(AuraEffectModifier* aurEff, bool apply)
{
    // Hackfixes from legacy methods
    switch (m_spellInfo->getId())
    {
        case 23493:
        case 24379:
        {
            Unit* caster = m_target;
            if (caster != nullptr)
            {
                ///\ todo: fix this
                //sEventMgr.AddEvent(this, &Aura::EventPeriodicHealPct, 10.0f , EVENT_AURA_PERIODIC_HEALPERC, 1000, 10, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

                if (caster->getMaxPower(POWER_TYPE_MANA))
                {
                    //sEventMgr.AddEvent(this, &Aura::EventPeriodicManaPct, 10.0f, EVENT_AURA_PERIOCIC_MANA, 1000, 10, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
                }
            }
            return;
        }
        case 57550: //Tirion Aggro
        {
            //Zyres: prevent server crash by invalid caster spells/amplitude
            return;
        }
    }

    const auto triggerSpellId = getSpellInfo()->getEffectTriggerSpell(aurEff->effIndex);
    if (triggerSpellId == 0 || sSpellMgr.getSpellInfo(triggerSpellId) == nullptr)
        return;

    if (apply)
    {
        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectPeriodicEnergize(AuraEffectModifier* aurEff, bool apply)
{
    if (aurEff->miscValue < POWER_TYPE_MANA || aurEff->miscValue >= TOTAL_PLAYER_POWER_TYPES)
        return;

    if (apply)
    {
        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectPeriodicLeech(AuraEffectModifier* aurEff, bool apply)
{
    if (apply)
    {
        const auto casterUnit = GetUnitCaster();

        // Apply modifiers
        if (casterUnit != nullptr)
        {
            spellModFlatIntValue(casterUnit->SM_FDOT, &aurEff->mDamage, getSpellInfo()->getSpellFamilyFlags());
            spellModPercentageIntValue(casterUnit->SM_PDOT, &aurEff->mDamage, getSpellInfo()->getSpellFamilyFlags());

            // Hackfix from legacy method
            // Apply bonus from [Warlock] Soul Siphon
            if (casterUnit->m_soulSiphon.amt)
            {
                // Use std::map to prevent counting duplicate auras (stacked ones, from the same unit)
                std::map<uint64_t, std::set<uint32_t> *> auras;
                std::map<uint64_t, std::set<uint32_t> *>::iterator itx, itx2;
                int32_t pct;
                int32_t count = 0;

                auras.clear();
                for (auto i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
                {
                    Aura* aura = m_target->m_auras[i];
                    if (aura == nullptr)
                        continue;

                    if (aura->getSpellInfo()->getSpellFamilyName() != 5)
                        continue;

                    auto skill_line_ability = sObjectMgr.GetSpellSkill(aura->getSpellId());
                    if (skill_line_ability == nullptr || skill_line_ability->skilline != SKILL_AFFLICTION)
                        continue;

                    itx = auras.find(aura->getCasterGuid());
                    if (itx == auras.end())
                    {
                        std::set<uint32_t> *ids = new std::set<uint32_t>;
                        auras.insert(make_pair(aura->getCasterGuid(), ids));
                        itx = auras.find(aura->getCasterGuid());
                    }

                    std::set<uint32> *ids = itx->second;
                    if (ids->find(aura->getSpellId()) == ids->end())
                    {
                        ids->insert(aura->getSpellId());
                    }
                }

                if (auras.size())
                {
                    itx = auras.begin();
                    while (itx != auras.end())
                    {
                        itx2 = itx++;
                        count += (int32_t)itx2->second->size();
                        delete itx2->second;
                    }
                }

                pct = count * casterUnit->m_soulSiphon.amt;
                if (pct > casterUnit->m_soulSiphon.max)
                    pct = casterUnit->m_soulSiphon.max;
                aurEff->mDamage += aurEff->mDamage * pct / 100;
            }
        }

        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectPeriodicHealthFunnel(AuraEffectModifier* aurEff, bool apply)
{
    if (apply)
    {
        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectPeriodicManaLeech(AuraEffectModifier* aurEff, bool apply)
{
    if (apply)
    {
        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectSchoolAbsorb(AuraEffectModifier* /*aurEff*/, bool /*apply*/)
{
    // See AbsorbAura::spellAuraEffectSchoolAbsorb
}

void Aura::spellAuraEffectPeriodicDamagePercent(AuraEffectModifier* aurEff, bool apply)
{
    if (apply)
    {
        aurEff->mDamage = static_cast<int32_t>(std::ceil(aurEff->mBaseDamage / 100.0f * getOwner()->getMaxHealth())) * getStackCount();

        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectPeriodicPowerBurn(AuraEffectModifier* aurEff, bool apply)
{
    if (aurEff->miscValue < POWER_TYPE_MANA || aurEff->miscValue >= TOTAL_PLAYER_POWER_TYPES)
        return;

    const auto powerType = static_cast<PowerType>(aurEff->miscValue);
    if (getOwner()->getMaxPower(powerType) == 0)
        return;

    if (apply)
    {
        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectPeriodicTriggerDummy(AuraEffectModifier* aurEff, bool apply)
{
    if (apply)
    {
        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
        if (!sScriptMgr.CallScriptedDummyAura(getSpellId(), aurEff->effIndex, this, false))
            LogDebugFlag(LF_AURA, "Spell aura %u has a periodic trigger dummy effect but no handler for it", getSpellId());

#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}

void Aura::spellAuraEffectPeriodicTriggerSpellWithValue(AuraEffectModifier* aurEff, bool apply)
{
    if (apply)
    {
        const auto triggeredInfo = sSpellMgr.getSpellInfo(getSpellInfo()->getEffectTriggerSpell(aurEff->effIndex));
        if (triggeredInfo == nullptr)
            return;

        // Set periodic timer only if timer was resetted
        if (m_periodicTimer[aurEff->effIndex] == 0)
            m_periodicTimer[aurEff->effIndex] = aurEff->mAmplitude;
    }
    else
    {
#if VERSION_STRING < Cata
        // Prior to cata periodic timer was resetted on refresh
        m_periodicTimer[aurEff->effIndex] = 0;
#endif
    }
}
