/*
 * Copyright (c) 2014-2020 AscEmu Team <http://www.ascemu.org>
 * Copyright (c) 2007-2015 Moon++ Team <http://www.moonplusplus.info>
 * Copyright (C) 2008-2011 ArcEmu Team <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Setup.h"
#include "Objects/Faction.h"
#include "Spell/SpellAuras.h"
#include "Server/Script/ScriptMgr.h"
#include "Spell/Definitions/ProcFlags.h"

bool Penance(uint8_t /*effectIndex*/, Spell* pSpell)
{
    if (!pSpell->getPlayerCaster() || !pSpell->getPlayerCaster()->isAlive() ||
        !pSpell->GetUnitTarget() || !pSpell->GetUnitTarget()->isAlive())
        return true;

    Unit* target = pSpell->GetUnitTarget();
    Player* player = pSpell->getPlayerCaster();

    // index 0 contains the spell for the first tick, index 1 is the peroidic cast spell.
    uint32_t hostileSpell[] = { 0, 0 };
    uint32_t friendlySpell[] = { 0, 0 };

    switch (pSpell->getSpellInfo()->getId())
    {
        case 47540: //Rank 1
            hostileSpell[0] = 47666;
            hostileSpell[1] = 47758;

            friendlySpell[0] = 47750;
            friendlySpell[1] = 47757;
            break;
        case 53005:
            hostileSpell[0] = 52998;
            hostileSpell[1] = 53001;

            friendlySpell[0] = 52983;
            friendlySpell[1] = 52986;
            break;
        case 53006:
            hostileSpell[0] = 52999;
            hostileSpell[1] = 53002;

            friendlySpell[0] = 52984;
            friendlySpell[1] = 52987;
            break;
        case 53007:
            hostileSpell[0] = 53000;
            hostileSpell[1] = 53003;

            friendlySpell[0] = 52985;
            friendlySpell[1] = 52988;
            break;
    }

    if (isAttackable(player, target))   // Do holy damage
    {
        // First tick is instant.
        player->castSpell(target, hostileSpell[0], true);
        player->castSpell(target, hostileSpell[1], false);
    }
    else // Heal
    {
        player->castSpell(target, friendlySpell[0], true);
        player->castSpell(target, friendlySpell[1], false);
    }
    return true;
}

bool DivineAegis(uint8_t /*effectIndex*/, Aura* pAura, bool apply)
{
    Unit* target = pAura->getOwner();

    if (apply)
        target->AddProcTriggerSpell(47753, pAura->getSpellId(), pAura->getCasterGuid(), pAura->getSpellInfo()->getProcChance(), PROC_ON_SPELL_CRIT_HIT, 0, NULL, NULL);
    else
        target->RemoveProcTriggerSpell(47753, pAura->getCasterGuid());

    return true;
}

bool ImprovedDevouringPlague(uint8_t /*effectIndex*/, Aura* pAura, bool apply)
{
    Unit* target = pAura->getOwner();

    if (apply)
    {
        static uint32_t classMask[3] = { 0x2000000, 0, 0 };
        target->AddProcTriggerSpell(63675, pAura->getSpellInfo()->getId(), pAura->getCasterGuid(), pAura->getSpellInfo()->getProcChance(), PROC_ON_CAST_SPELL, 0, NULL, classMask);
    }
    else
        target->RemoveProcTriggerSpell(63675, pAura->getCasterGuid());

    return true;
}

bool VampiricEmbrace(uint8_t /*effectIndex*/, Aura* pAura, bool apply)
{
    Unit* target = pAura->getOwner();

    if (apply)
        target->AddProcTriggerSpell(15290, pAura->getSpellId(), pAura->getCasterGuid(), pAura->getSpellInfo()->getProcChance(), PROC_ON_ANY_HOSTILE_ACTION | PROC_TARGET_SELF, 0, NULL, NULL);
    else
        target->RemoveProcTriggerSpell(15290, pAura->getCasterGuid());

    return true;
}

bool VampiricTouch(uint8_t effectIndex, Aura* pAura, bool apply)
{
    Unit* target = pAura->getOwner();

    switch (effectIndex)
    {
        case 0:
            if (apply)
                target->AddProcTriggerSpell(64085, pAura->getSpellId(), pAura->getCasterGuid(), pAura->getSpellInfo()->getProcChance(), PROC_ON_PRE_DISPELL_AURA_VICTIM | PROC_TARGET_SELF, 0, NULL, NULL);
            else
                target->RemoveProcTriggerSpell(64085, pAura->getCasterGuid());
            break;

        case 2:
            if (apply)
                target->AddProcTriggerSpell(34919, pAura->getSpellId(), pAura->getCasterGuid(), pAura->getSpellInfo()->getProcChance(), PROC_ON_SPELL_HIT_VICTIM, 0, NULL, NULL);
            else
                target->RemoveProcTriggerSpell(34919, pAura->getCasterGuid());
            break;
    }

    return true;
}

bool EmpoweredRenew(uint8_t /*effectIndex*/, Aura* pAura, bool apply)
{
    Unit* target = pAura->getOwner();

    if (apply)
    {
        static uint32_t classMask[3] = { 0x40, 0, 0 };
        target->AddProcTriggerSpell(63544, pAura->getSpellId(), pAura->getCasterGuid(), pAura->getSpellInfo()->getProcChance(), PROC_ON_CAST_SPELL, 0, NULL, classMask);
    }
    else
        target->RemoveProcTriggerSpell(63544, pAura->getCasterGuid());

    return true;
}

bool ImprovedMindBlast(uint8_t /*effectIndex*/, Aura* pAura, bool apply)
{
    Unit* target = pAura->getOwner();

    if (apply)
    {
        static uint32_t classMask[3] = { 0x2000, 0, 0 };
        target->AddProcTriggerSpell(48301, pAura->getSpellId(), pAura->getCasterGuid(), pAura->getSpellInfo()->getProcChance(), PROC_ON_SPELL_HIT, 0, NULL, classMask);
    }
    else
        target->RemoveProcTriggerSpell(48301, pAura->getCasterGuid());

    return true;
}

bool PainAndSufferingAura(uint8_t /*effectIndex*/, Aura* pAura, bool apply)
{
    Unit* target = pAura->getOwner();

    if (apply)
    {
        static uint32_t classMask[3] = { 0, 0, 0x40 };
        target->AddProcTriggerSpell(47948, pAura->getSpellId(), pAura->getCasterGuid(), pAura->getSpellInfo()->getProcChance(), PROC_ON_CAST_SPELL, 0, NULL, classMask);
    }
    else
        target->RemoveProcTriggerSpell(47948, pAura->getCasterGuid());

    return true;
}

bool PainAndSufferingProc(uint8_t /*effectIndex*/, Spell* pSpell)
{
    Player* caster = pSpell->getPlayerCaster();
    if (caster == NULL)
        return true;

    Unit* target = pSpell->GetUnitTarget();
    if (target == NULL)
        return true;

    uint32_t shadowWordPain[] =
    {
        //SPELL_HASH_SHADOW_WORD__PAIN
        589,
        594,
        970,
        992,
        2767,
        10892,
        10893,
        10894,
        11639,
        14032,
        15654,
        17146,
        19776,
        23268,
        23952,
        24212,
        25367,
        25368,
        27605,
        30854,
        30898,
        34441,
        34941,
        34942,
        37275,
        41355,
        46560,
        48124,
        48125,
        57778,
        59864,
        60005,
        60446,
        65541,
        68088,
        68089,
        68090,
        72318,
        72319,
        0
    };
    Aura* aura = target->getAuraWithIdForGuid(shadowWordPain, caster->getGuid());
    if (aura == nullptr)
        return true;

    // Set new aura's duration, reset event timer and set client visual aura
    aura->refresh(true);

    return true;
}

bool BodyAndSoul(uint8_t effectIndex, Aura* pAura, bool apply)
{
    Unit* target = pAura->getOwner();

    if (apply)
    {
        static uint32_t classMask[3] = { 0, 1, 0 };
        target->AddProcTriggerSpell(64134, pAura->getSpellId(), pAura->getCasterGuid(), pAura->getEffectDamage(effectIndex), PROC_ON_CAST_SPELL | PROC_TARGET_SELF, 0, NULL, classMask);
    }
    else
        target->RemoveProcTriggerSpell(64134, pAura->getCasterGuid());

    return true;
}

bool PrayerOfMendingAura(uint8_t /*effectIndex*/, Aura* pAura, bool apply)
{
    Unit* target = pAura->getOwner();

    if (apply)
        target->AddProcTriggerSpell(pAura->getSpellInfo(), pAura->getSpellInfo(), pAura->getCasterGuid(), pAura->getSpellInfo()->getProcChance(), PROC_ON_ANY_DAMAGE_VICTIM, pAura->getSpellInfo()->getProcCharges(), NULL, NULL);
    else
    {
        int32_t count = target->GetAuraStackCount(pAura->getSpellId());
        if (count == 1)
            target->RemoveProcTriggerSpell(pAura->getSpellId(), pAura->getCasterGuid());
    }

    return true;
}

void SetupLegacyPriestSpells(ScriptMgr* mgr)
{
    uint32_t PenanceIds[] =
    {
        47540, // Rank 1
        53005, // Rank 2
        53006, // Rank 3
        53007, // Rank 4
        0,
    };
    mgr->register_dummy_spell(PenanceIds, &Penance);

    uint32_t DivineAegisIds[] = { 47509, 47511, 47515, 0 };
    mgr->register_dummy_aura(DivineAegisIds, &DivineAegis);

    uint32_t ImprovedDevouringPlagueIds[] = { 63625, 63626, 63627, 0 };
    mgr->register_dummy_aura(ImprovedDevouringPlagueIds, &ImprovedDevouringPlague);

    mgr->register_dummy_aura(15286, &VampiricEmbrace);

    uint32_t VampiricTouchIds[] = { 34914, 34916, 34917, 48159, 48160, 0 };
    mgr->register_dummy_aura(VampiricTouchIds, &VampiricTouch);

    uint32_t EmpoweredRenewIds[] = { 63534, 63542, 63543, 0 };
    mgr->register_dummy_aura(EmpoweredRenewIds, &EmpoweredRenew);

    uint32_t ImprovedMindBlastIds[] = { 15273, 15312, 15313, 15314, 15316, 0 };
    mgr->register_dummy_aura(ImprovedMindBlastIds, &ImprovedMindBlast);

    uint32_t PainAndSufferingAuraIds[] = { 47580, 47581, 47582, 0 };
    mgr->register_dummy_aura(PainAndSufferingAuraIds, &PainAndSufferingAura);

    mgr->register_script_effect(47948, &PainAndSufferingProc);

    mgr->register_dummy_aura(64127, &BodyAndSoul);
    mgr->register_dummy_aura(64129, &BodyAndSoul);

    uint32_t PrayerOfMendingAuraIds[] = { 41635, 48110, 48111, 0 };
    mgr->register_dummy_aura(PrayerOfMendingAuraIds, &PrayerOfMendingAura);
}
