/*
Copyright (c) 2014-2017 AscEmu Team <http://www.ascemu.org/>
This file is released under the MIT license. See README-MIT for more information.
*/

#include "Setup.h"
#include "TheStockade.h"


class TheStockade : public InstanceScript
{
public:

    TheStockade(MapMgr* pMapMgr) : InstanceScript(pMapMgr)
    {
        generateBossDataState();
    }

    static InstanceScript* Create(MapMgr* pMapMgr) { return new TheStockade(pMapMgr); }

    void OnCreatureDeath(Creature* pCreature, Unit* pUnit)
    {
        setData(pCreature->GetEntry(), Finished);
    }
};


void TheStockadeScripts(ScriptMgr* scriptMgr)
{
    scriptMgr->register_instance_script(34, &TheStockade::Create);
}
