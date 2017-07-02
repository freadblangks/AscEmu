/*
 * AscEmu Framework based on ArcEmu MMORPG Server
 * Copyright (C) 2014-2017 AscEmu Team <http://www.ascemu.org>
 * Copyright (C) 2008-2012 ArcEmu Team <http://www.ArcEmu.org/>
 * Copyright (C) 2005-2007 Ascent Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef GUILD_H
#define GUILD_H

#include "WorldConf.h"

#if VERSION_STRING != Cata

class PlayerInfo;

enum
{
    MAX_GUILD_RANKS     = 10,
    MAX_GUILD_MEMBERS   = 500
};

enum PETITION_TURNIN_ERRORS
{
    ERR_PETITION_OK,
    ERR_PETITION_ALREADY_SIGNED,
    ERR_PETITION_IN_GUILD,
    ERR_PETITION_CREATOR,
    ERR_PETITION_NOT_ENOUGH_SIGNATURES,

    //ERR_PET_SPELL_DEAD
    //ERR_PETITION_DECLINED_S
    //ERR_PETITION_SIGNED_S
    //ERR_PETITION_SIGNED
    //ERR_PETITION_OFFERED
};

enum GUILDEMBLEM_ERRORS
{
    ERR_GUILDEMBLEM_SUCCESS,
    ERR_GUILDEMBLEM_INVALID_TABARD_COLORS,
    ERR_GUILDEMBLEM_NOGUILD,
    ERR_GUILDEMBLEM_NOTGUILDMASTER,
    ERR_GUILDEMBLEM_NOTENOUGHMONEY,
    ERR_GUILDEMBLEM_INVALIDVENDOR
};

enum GuildMessageTypes
{
    G_MSGTYPE_ALL,
    G_MSGTYPE_ALLBUTONE,
    G_MSGTYPE_PUBLICCHAT,
    G_MSGTYPE_OFFICERCHAT
};

enum MONEY
{
    MONEY_ONE_COPPER        = 1,
    MONEY_ONE_SILVER        = MONEY_ONE_COPPER * 100,
    MONEY_ONE_GOLD          = MONEY_ONE_SILVER * 100
};

//enum GuildCommandError
//{
//    GC_ERROR_SUCCESS = 0,
//    GC_ERROR_INTERNAL = 1,
//    GC_ERROR_ALREADY_IN_GUILD = 2,
//    GC_ERROR_ALREADY_IN_GUILD_S = 3,
//    GC_ERROR_INVITED_TO_GUILD = 4,
//    GC_ERROR_ALREADY_INVITED_TO_GUILD = 5,
//    GC_ERROR_NAME_INVALID = 6,
//    GC_ERROR_NAME_EXISTS_S = 7,
//    GC_ERROR_LEADER_LEAVE = 8,
//    GC_ERROR_PERMISSIONS = 8,
//    GC_ERROR_PLAYER_NOT_IN_GUILD = 9,
//    GC_ERROR_PLAYER_NOT_IN_GUILD_S = 10,
//    GC_ERROR_PLAYER_NOT_FOUND_S = 11,
//    GC_ERROR_NOT_ALLIED = 12,
//    GC_ERROR_RANK_TOO_HIGH_S = 13,
//    GC_ERROR_RANK_TOO_LOW_S = 14,
//    GC_ERROR_RANKS_LOCKED = 17,
//    GC_ERROR_RANK_IN_USE = 18,
//    GC_ERROR_IGNORING_YOU_S = 19,
//    GC_ERROR_UNK1 = 20,
//    GC_ERROR_WITHDRAW_LIMIT = 25,
//    GC_ERROR_NOT_ENOUGH_MONEY = 26,
//    GC_ERROR_BANK_FULL = 28,
//    GC_ERROR_ITEM_NOT_FOUND = 29,
//    GC_ERROR_TOO_MUCH_MONEY = 31,
//    GC_ERROR_BANK_WRONG_TAB = 32,
//    GC_ERROR_REQUIRES_AUTHENTICATOR = 34,
//    GC_ERROR_BANK_VOUCHER_FAILED = 35,
//    GC_ERROR_TRIAL_ACCOUNT = 36,
//    GC_ERROR_UNDELETABLE_DUE_TO_LEVEL = 37,
//    GC_ERROR_MOVE_STARTING = 38,
//    GC_ERROR_REP_TOO_LOW = 39
//};
enum GuildCommandError
{
    GC_ERROR_SUCCESS          = 0x00,
    GC_ERROR_INTERNAL                = 0x01,
    GC_ERROR_ALREADY_IN_GUILD        = 0x02,
    GC_ERROR_ALREADY_IN_GUILD_S              = 0x03,
    GC_ERROR_INVITED_TO_GUILD              = 0x04,
    GC_ERROR_ALREADY_INVITED_TO_GUILD      = 0x05,
    GC_ERROR_NAME_INVALID            = 0x06,
    GC_ERROR_NAME_EXISTS_S             = 0x07,
    GC_ERROR_LEADER_LEAVE            = 0x08,
    GC_ERROR_PERMISSIONS             = 0x08,
    GC_ERROR_PLAYER_NOT_IN_GUILD     = 0x09,
    GC_ERROR_PLAYER_NOT_IN_GUILD_S   = 0x0A,
    GC_ERROR_PLAYER_NOT_FOUND_S        = 0x0B,
    GC_ERROR_NOT_ALLIED              = 0x0C
};

//for uint32(0)<<name<<code
enum GUILD_COMMAND_RESULTS
{
    C_R_CREATED                             = 1,
    C_R_ALREADY_IN_GUILD                    = 2,
    C_R_TARGET_ALREADY_IN_GUILD             = 3,
    C_R_ALREADY_INVITED_TO_GUILD            = 4,
    C_R_TARGET_ALREADY_INVITED_TO_GUILD     = 5,
    C_R_GUILDNAME_HAS_INVALID_CHARACTERS    = 6,
    C_R_GUILD_NAME_EXISTS                   = 7,
    C_R_DONT_HAVE_PERMISSION                = 8,
    C_R_NOT_IN_GUILD                        = 9,
    C_R_TARGET_IS_NOT_IN_YOUR_GUILD         = 10,
    C_R_NAME_NOT_FOUND                      = 11,
    C_R_CANT_INVITE_PLYRS_FROM_OPP_ALLIANCE = 12,
    C_R_NAME_RANK_TOO_HIGH                  = 13,
    C_R_NAME_RANK_AT_LOWEST_RANK            = 14
    /*
    ERR_NO_GUILD_CHARTER

    ERR_GUILD_NAME_NAME_CONSECUTIVE_SPACES
    ERR_GUILD_NAME_INVALID_SPACE
    ERR_GUILD_NAME_RESERVED
    ERR_GUILD_NAME_PROFANE
    ERR_GUILD_NAME_MIXED_LANGUAGES
    ERR_GUILD_NAME_TOO_SHORT

    ERR_GUILD_ENTER_NAME

    ERR_GUILD_NAME_EXISTS_S
    ERR_GUILD_NAME_INVALID

    ERR_GUILD_RANK_TOO_LOW_S
    ERR_GUILD_RANK_TOO_HIGH_S
    ERR_GUILD_RANK_IN_USE
    ERR_GUILD_RANKS_LOCKED
    ERR_GUILD_LEADER_LEAVE
    ERR_GUILD_NOT_ALLIED
    ERR_GUILD_DISBANDED
    ERR_GUILD_LEADER_CHANGED_SS
    ERR_GUILD_LEADER_IS_S
    ERR_GUILD_INTERNAL
    ERR_GUILD_NOT_IN_A_GUILD
    ERR_GUILD_CANT_DEMOTE_S
    ERR_GUILD_CANT_PROMOTE_S
    ERR_GUILD_PLAYER_NOT_IN_GUILD
    ERR_GUILD_PLAYER_NOT_IN_GUILD_S
    ERR_GUILD_PLAYER_NOT_FOUND_S
    ERR_GUILD_LEADER_SELF
    ERR_GUILD_LEADER_S
    ERR_GUILD_DISBAND_SELF
    ERR_GUILD_DISBAND_S
    ERR_GUILD_REMOVE_SELF
    ERR_GUILD_REMOVE_SS
    ERR_GUILD_LEAVE_S
    ERR_GUILD_QUIT_S
    ERR_GUILD_DEMOTE_SSS
    ERR_GUILD_PROMOTE_SSS
    ERR_GUILD_FOUNDER_S
    ERR_GUILD_JOIN_S
    ERR_GUILD_PERMISSIONS
    ERR_GUILD_DECLINE_S
    ERR_GUILD_ACCEPT
    ERR_ALREADY_IN_GUILD
    ERR_INVITED_TO_GUILD
    ERR_ALREADY_INVITED_TO_GUILD_S
    ERR_ALREADY_IN_GUILD_S
    ERR_INVITED_TO_GUILD_SS
    ERR_GUILD_INVITE_S
    ERR_GUILD_CREATE_S
    */
};

//enum GuildCommandType
//{
//    GC_TYPE_CREATE = 0,
//    GC_TYPE_INVITE = 1,
//    GC_TYPE_QUIT = 3,
//    GC_TYPE_ROSTER = 5,
//    GC_TYPE_PROMOTE = 6,
//    GC_TYPE_DEMOTE = 7,
//    GC_TYPE_REMOVE = 8,
//    GC_TYPE_CHANGE_LEADER = 10,
//    GC_TYPE_EDIT_MOTD = 11,
//    GC_TYPE_GUILD_CHAT = 13,
//    GC_TYPE_FOUNDER = 14,
//    GC_TYPE_CHANGE_RANK = 16,
//    GC_TYPE_PUBLIC_NOTE = 19,
//    GC_TYPE_VIEW_TAB = 21,
//    GC_TYPE_MOVE_ITEM = 22,
//    GC_TYPE_REPAIR = 25
//};
enum GuildCommandType
{
    GC_TYPE_CREATE                  = 0x00,
    GC_TYPE_INVITE                  = 0x01,
    GC_TYPE_QUIT                    = 0x02,
    GC_TYPE_PROMOTE                 = 0x03,
    GC_TYPE_FOUNDER                 = 0x0C,
    GC_TYPE_GUILD_CHAT                  = 0x0D,
    GC_TYPE_PUBLIC_NOTE     = 0x13,
    GC_TYPE_CHANGE_RANK    = 0x14

};

enum GuildRankRights
{
    GR_RIGHT_EMPTY                     = 0x00040,
    GR_RIGHT_GCHATLISTEN               = 0x00001,
    GR_RIGHT_GCHATSPEAK                = 0x00002,
    GR_RIGHT_OFFCHATLISTEN             = 0x00004,
    GR_RIGHT_OFFCHATSPEAK              = 0x00008,
    GR_RIGHT_INVITE                    = 0x00010,
    GR_RIGHT_REMOVE                    = 0x00020,
    // unknown 0x00040
    GR_RIGHT_PROMOTE                   = 0x00080,
    GR_RIGHT_DEMOTE                    = 0x00100,
    // unknown 0x00200
    // unknown 0x00400
    // unknown 0x00800
    GR_RIGHT_SETMOTD                   = 0x01000,
    GR_RIGHT_EPNOTE                    = 0x02000,
    GR_RIGHT_VIEWOFFNOTE               = 0x04000,
    GR_RIGHT_EOFFNOTE                  = 0x08000,
    GR_RIGHT_EGUILDINFO                = 0x10000,
    GR_RIGHT_GUILD_BANK_REPAIR         = 0x40000,
    GR_RIGHT_GUILD_BANK_WITHDRAW_MONEY = 0x80000,
    GR_RIGHT_ALL                       = 0xDF1FF,
    GR_RIGHT_DEFAULT                   = GR_RIGHT_GCHATLISTEN | GR_RIGHT_GCHATSPEAK | GR_RIGHT_EMPTY,
    GR_RIGHT_GUILD_BANK_VIEW_TAB       = 0x01,
    GR_RIGHT_GUILD_BANK_DEPOSIT_ITEMS  = 0x02,
    GR_RIGHT_GUILD_BANK_CHANGE_TABTXT  = 0x04,
    GR_RIGHT_GUILD_BANK_ALL            = GR_RIGHT_GUILD_BANK_VIEW_TAB | GR_RIGHT_GUILD_BANK_DEPOSIT_ITEMS | GR_RIGHT_GUILD_BANK_CHANGE_TABTXT
};

enum GuildEvent
{
    GUILD_EVENT_PROMOTION          = 0x0,
    GUILD_EVENT_DEMOTION           = 0x1,
    GUILD_EVENT_MOTD               = 0x2,
    GUILD_EVENT_JOINED             = 0x3,
    GUILD_EVENT_LEFT               = 0x4,
    GUILD_EVENT_REMOVED            = 0x5,
    GUILD_EVENT_LEADER_IS          = 0x6,
    GUILD_EVENT_LEADER_CHANGED     = 0x7,
    GUILD_EVENT_DISBANDED          = 0x8,
    GUILD_EVENT_TABARDCHANGE       = 0x9,
    GUILD_EVENT_UNK1               = 0xA,
    GUILD_EVENT_UNK2               = 0xB,
    GUILD_EVENT_HASCOMEONLINE      = 0xC,
    GUILD_EVENT_HASGONEOFFLINE     = 0xD,
    GUILD_EVENT_BANKTABBOUGHT      = 0xF,
    GUILD_EVENT_SETNEWBALANCE      = 0x11,
    GUILD_EVENT_TABINFO            = 0x13
};
enum GuildLogEventE
{
    GUILD_LOG_EVENT_INVITE       = 1,
    GUILD_LOG_EVENT_JOIN         = 2,
    GUILD_LOG_EVENT_PROMOTION    = 3,
    GUILD_LOG_EVENT_DEMOTION     = 4,
    GUILD_LOG_EVENT_REMOVAL      = 5,
    GUILD_LOG_EVENT_LEFT         = 6
};

enum GuildBankLogEvents
{
    GUILD_BANK_LOG_EVENT_DEPOSIT_ITEM   = 1,
    GUILD_BANK_LOG_EVENT_WITHDRAW_ITEM  = 2,
    GUILD_BANK_LOG_EVENT_DEPOSIT_MONEY  = 4,
    GUILD_BANK_LOG_EVENT_WITHDRAW_MONEY = 5,
    GUILD_BANK_LOG_EVENT_REPAIR         = 6
};

#define ITEM_ENTRY_GUILD_CHARTER 5863

#define ARENA_TEAM_CHARTER_2v2 23560
#define ARENA_TEAM_CHARTER_2v2_COST 800000  // 80 G

#define ARENA_TEAM_CHARTER_3v3 23561
#define ARENA_TEAM_CHARTER_3v3_COST 1200000 // 120 G

#define ARENA_TEAM_CHARTER_5v5 23562
#define ARENA_TEAM_CHARTER_5v5_COST 2000000 // 200 G

#define MAX_GUILD_BANK_SLOTS 98
#define MAX_GUILD_BANK_TABS 6

struct SERVER_DECL GuildRankTabPermissions
{
    uint32 iFlags;
    int32 iStacksPerDay;
};

struct SERVER_DECL GuildRank
{
    uint32 iId;
    uint32 iRights;
    int32 iGoldLimitPerDay;
    GuildRankTabPermissions iTabPermissions[MAX_GUILD_BANK_TABS];
    char* szRankName;
    bool CanPerformCommand(uint32 t);
    bool CanPerformBankCommand(uint32 t, uint32 tab);
};

struct SERVER_DECL GuildMember
{
    PlayerInfo* pPlayer;
    const char* szPublicNote;
    const char* szOfficerNote;
    GuildRank* pRank;
    uint32 uLastWithdrawReset;
    uint32 uWithdrawlsSinceLastReset;
    uint32 uLastItemWithdrawReset[MAX_GUILD_BANK_TABS];
    uint32 uItemWithdrawlsSinceLastReset[MAX_GUILD_BANK_TABS];

    uint32 CalculateAllowedItemWithdraws(uint32 tab);
    void OnItemWithdraw(uint32 tabid);

    uint32 CalculateAvailableAmount();
    bool RepairItem(uint32 cost);
    void OnMoneyWithdraw(uint32 amt);
};

struct SERVER_DECL GuildLogEvent
{
    uint32 iLogId;
    uint8 iEvent;
    uint32 iTimeStamp;
    uint32 iEventData[3];
};

struct SERVER_DECL GuildBankEvent
{
    uint32 iLogId;
    uint8 iAction;
    uint32 uPlayer;
    uint32 uEntry;
    uint8 iStack;
    uint32 uTimeStamp;
};

struct SERVER_DECL GuildBankTab
{
    uint8 iTabId;
    char* szTabName;
    char* szTabIcon;
    char* szTabInfo;
    Item* pSlots[MAX_GUILD_BANK_SLOTS];
    std::list<GuildBankEvent*> lLog;
};

class Charter;

typedef std::map<PlayerInfo*, GuildMember*> GuildMemberMap;

class SERVER_DECL Guild
{
    public:

        Guild();
        ~Guild();

        static Guild* Create();
        bool LoadFromDB(Field* f);


    protected:

        // Log entry processing
        uint32 m_hiLogId;

    public:

        uint32 GenerateGuildLogEventId();

        // guild bank logging calls
        void LogGuildBankActionMoney(uint8 iAction, uint32 uGuid, uint32 uAmount);
        void LogGuildBankAction(uint8 iAction, uint32 uGuid, uint32 uEntry, uint8 iStack, GuildBankTab* pTab);
        static void ClearOutOfDateLogEntries();

        // only call at first create/save 
        void CreateInDB();

        void SetMOTD(const char* szNewMotd, WorldSession* pClient);

        inline const char* getMOTD() const { return (m_motd ? m_motd : ""); }

        void SetGuildInformation(const char* szGuildInformation, WorldSession* pClient);

        inline const char* GetGuildInformation() const { return m_guildInfo; }

        void SendGuildRoster(WorldSession* pClient);

        void SendGuildQuery(WorldSession* pClient);

        void AddGuildMember(PlayerInfo* pMember, WorldSession* pClient, int32 ForcedRank = -1);

        // If this member is the guild master, the guild will be automatically handed down to the next highest member.
        void RemoveGuildMember(PlayerInfo* pMember, WorldSession* pClient);

        // Do not use for changing guild master.Use ChangeGuildMaster() for that instead.
        void PromoteGuildMember(PlayerInfo* pMember, WorldSession* pClient);

        // Do not use for changing guild master. Use ChangeGuildMaster() for that instead.
        void DemoteGuildMember(PlayerInfo* pMember, WorldSession* pClient);

        void ChangeGuildMaster(PlayerInfo* pNewMaster, WorldSession* pClient);

        static void sendCommandResult(WorldSession* pClient, GuildCommandType iCmd, GuildCommandError iType, const char* szMsg = NULL);

        static void SendTurnInPetitionResult(WorldSession* pClient, uint32 result);

        void LogGuildEvent(uint8 iEvent, uint8 iStringCount, ...);

        void AddGuildLogEntry(uint8 iEvent, uint8 iParamCount, ...);

        void CreateFromCharter(Charter* pCharter, WorldSession* pTurnIn);

        void sendPacket(WorldPacket* data);

        // Sends a guild chat message.
        void GuildChat(const char* szMessage, WorldSession* pClient, uint32 iType);

        // Sends an officer chat message.
        void OfficerChat(const char* szMessage, WorldSession* pClient, uint32 iType);

        void SendGuildLog(WorldSession* pClient);
        void SendGuildBankLog(WorldSession* pClient, uint8 iSlot);

        void SetPublicNote(PlayerInfo* pMember, const char* szNewNote, WorldSession* pClient);

        void SetOfficerNote(PlayerInfo* pMember, const char* szNewNote, WorldSession* pClient);

        void disband();

        // creation time stuff
        uint32 creationDay;
        uint32 creationMonth;
        uint32 creationYear;

        // Getters :P
        inline const char* getGuildName() const { return m_guildName; }
        inline const uint32 GetGuildLeader() const { return m_guildLeader; }
        inline const uint32 getGuildId() const { return m_guildId; }
        inline const uint8  GetBankTabCount() const { return (uint8) m_bankTabs.size(); }
        inline const uint64 GetBankBalance() const { return m_bankBalance; }
        inline const size_t GetNumMembers() const { return m_members.size(); }

        // Creates a guild rank with the specified permissions.
        GuildRank* CreateGuildRank(const char* szRankName, uint32 iPermissions, bool bFullGuildBankPermissions);

        // "Pops" or removes the bottom guild rank.
        void RemoveGuildRank(WorldSession* pClient);

        // Buys a new guild bank tab, usable only by guild master
        void BuyBankTab(WorldSession* pClient);

        // Deposits money into the guild bank, usable by any member.
        void DepositMoney(WorldSession* pClient, uint32 uAmount);

        // Withdraws money from the guild bank, usable by members with that permission.
        void WithdrawMoney(WorldSession* pClient, uint32 uAmount);

        // Decrease the guild balance of uAmount
        void SpendMoney(uint32 uAmount);

        // Retrieves a guild rank for editing
        inline GuildRank* GetGuildRank(uint32 Id)
        {
            if (Id >= MAX_GUILD_RANKS)
                return NULL;

            return m_ranks[Id];
        }

        // Gets a guild bank tab for editing/viewing
        inline GuildBankTab* GetBankTab(uint8 Id)
        {
            if (Id >= GetBankTabCount())
                return NULL;

            return m_bankTabs[Id];
        }

        // Gets a guild member struct
        inline GuildMember* GetGuildMember(PlayerInfo* pInfo)
        {
            GuildMemberMap::iterator itr;
            GuildMember* ret;
            m_lock.Acquire();
            itr = m_members.find(pInfo);
            ret = (itr != m_members.end()) ? itr->second : NULL;
            m_lock.Release();
            return ret;
        }

        // Get iterators
        inline GuildMemberMap::iterator GetGuildMembersBegin() { return m_members.begin(); }
        inline GuildMemberMap::iterator GetGuildMembersEnd() { return m_members.end(); }

        // Get, Lock, Unlock Mutex
        inline Mutex & getLock() { return m_lock; }
        inline void Lock() { m_lock.Acquire(); }
        inline void Unlock() { return m_lock.Release(); }

        // Sends the guild bank to this client.
        void SendGuildBank(WorldSession* pClient, GuildBankTab* pTab, int8 updated_slot1 = -1, int8 updated_slot2 = -1);
        void SendGuildBankInfo(WorldSession* pClient);

        // Changes the tabard info.
        void SetTabardInfo(uint32 EmblemStyle, uint32 EmblemColor, uint32 BorderStyle, uint32 BorderColor, uint32 BackgroundColor);

        // Sends the guild information packet to the specified client.
        void SendGuildInfo(WorldSession* pClient);

    protected:

        // Enables/disables command logging.
        // Use when performing mass events such as guild creation or destruction.
        bool m_commandLogging;

        // Internal variables
        uint32 m_guildId;
        uint32 m_emblemStyle;
        uint32 m_emblemColor;
        uint32 m_borderStyle;
        uint32 m_borderColor;
        uint32 m_backgroundColor;
        uint32 m_guildLeader;
        uint32 m_creationTimeStamp;
        uint64 m_bankBalance; //use a 64 bit int so we can store more gold in the gbank

        typedef std::vector<GuildBankTab*> GuildBankTabVector;
        GuildBankTabVector m_bankTabs;

        char* m_guildName;
        char* m_guildInfo;
        char* m_motd;

        // Guild Member Map.
        //typedef map<PlayerInfo*, GuildMember*> GuildMemberMap;
        GuildMemberMap m_members;

        // Guild Rank Information.
        GuildRank* m_ranks[MAX_GUILD_RANKS];

        // Guild log. Ordered in first event -> last event.
        typedef std::list<GuildLogEvent*> GuildLogList;
        GuildLogList m_log;
        std::list<GuildBankEvent*> m_moneyLog;

        // Guild lock.
        Mutex m_lock;

        // finds the lowest rank
        GuildRank* FindLowestRank();
        GuildRank* FindHighestRank();
};


#endif // GUILD_H
#endif
