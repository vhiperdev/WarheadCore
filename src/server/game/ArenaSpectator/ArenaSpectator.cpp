/*
 * This file is part of the WarheadCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ArenaSpectator.h"
#include "BattlegroundMgr.h"

namespace ArenaSpectator
{
    bool HandleSpectatorSpectateCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        std::list<std::string> errors;

        if (!*args)
        {
            handler->SendSysMessage("Missing player name.");
            return true;
        }

        if (player->IsSpectator())
        {
            if (player->FindMap() && player->FindMap()->IsBattleArena())
            {
                HandleSpectatorWatchCommand(handler, args);
                return true;
            }
            handler->PSendSysMessage("You are already spectacting arena.");
            return true;
        }

        if (player->getClass() == CLASS_DEATH_KNIGHT && player->GetMapId() == 609)
        {
            handler->PSendSysMessage("Death Knights can't spectate before finishing questline.");
            return true;
        }

        std::string name = std::string(args);
        Player* spectate = ObjectAccessor::FindPlayerByName(name);
        if (!spectate)
        {
            handler->SendSysMessage("Requested player not found.");
            return true;
        }

        if (spectate->IsSpectator())
        {
            handler->SendSysMessage("Requested player is a spectator.");
            return true;
        }

        if (!spectate->FindMap() || !spectate->FindMap()->IsBattleArena())
        {
            handler->SendSysMessage("Requested player is not in arena.");
            return true;
        }

        BattlegroundMap* bgmap = ((BattlegroundMap*)spectate->FindMap());
        if (!bgmap->GetBG() || bgmap->GetBG()->GetStatus() == STATUS_WAIT_LEAVE)
        {
            handler->SendSysMessage("This arena battle has finished.");
            return true;
        }

        if (player->IsBeingTeleported() || !player->IsInWorld())
            errors.push_back("Can't use while being teleported.");

        if (!player->FindMap() || player->FindMap()->Instanceable())
            errors.push_back("Can't use while in instance, bg or arena.");

        if (player->GetVehicle())
            errors.push_back("Can't be on a vehicle.");

        if (player->IsInCombat())
            errors.push_back("Can't be in combat.");

        if (player->isUsingLfg())
            errors.push_back("Can't spectate while using LFG system.");

        if (player->InBattlegroundQueue())
            errors.push_back("Can't be queued for arena or bg.");

        if (player->GetGroup())
            errors.push_back("Can't be in a group.");

        if (player->HasUnitState(UNIT_STATE_ISOLATED))
            errors.push_back("Can't be isolated.");

        if (player->m_mover != player)
            errors.push_back("You must control yourself.");

        if (player->IsInFlight())
            errors.push_back("Can't be in flight.");

        if (player->IsMounted())
            errors.push_back("Dismount before spectating.");

        if (!player->IsAlive())
            errors.push_back("Must be alive.");

        if (!player->m_Controlled.empty())
            errors.push_back("Can't be controlling creatures.");

        const Unit::VisibleAuraMap* va = player->GetVisibleAuras();        
        for (auto itr = va->begin(); itr != va->end(); ++itr)
            if (Aura* aura = itr->second->GetBase())
                if (!itr->second->IsPositive() && !aura->IsPermanent() && aura->GetDuration() < HOUR * IN_MILLISECONDS)
                {
                    switch (aura->GetSpellInfo()->Id)
                    {
                    case lfg::LFG_SPELL_DUNGEON_DESERTER:
                    case lfg::LFG_SPELL_DUNGEON_COOLDOWN:
                    case 26013: // bg deserter
                    case 57724: // sated
                    case 57723: // exhaustion
                    case 25771: // forbearance
                    case 15007: // resurrection sickness
                    case 24755: // Tricked or Treated (z eventu)
                        continue;
                    }

                    errors.push_back("Can't have negative auras.");
                    break;
                }

        if (uint32 inviteInstanceId = player->GetPendingSpectatorInviteInstanceId())
        {
            if (Battleground* tbg = sBattlegroundMgr->GetBattleground(inviteInstanceId))
                tbg->RemoveToBeTeleported(player->GetGUID());
            player->SetPendingSpectatorInviteInstanceId(0);
        }

        bool bgPreparation = false;
        if ((!handler->GetSession()->GetSecurity() && bgmap->GetBG()->GetStatus() != STATUS_IN_PROGRESS) ||
            (handler->GetSession()->GetSecurity() && bgmap->GetBG()->GetStatus() != STATUS_WAIT_JOIN && bgmap->GetBG()->GetStatus() != STATUS_IN_PROGRESS))
        {
            bgPreparation = true;
            handler->SendSysMessage("Arena is not in progress yet. You will be invited as soon as it starts.");
            bgmap->GetBG()->AddToBeTeleported(player->GetGUID(), spectate->GetGUID());
            player->SetPendingSpectatorInviteInstanceId(spectate->GetBattlegroundId());
        }

        if (!errors.empty())
        {
            handler->PSendSysMessage("To spectate, please fix the following:");
            for (std::list<std::string>::const_iterator itr = errors.begin(); itr != errors.end(); ++itr)
                handler->PSendSysMessage("- %s", (*itr).c_str());

            return true;
        }

        if (bgPreparation)
            return true;

        float z = spectate->GetMapId() == 618 ? std::max(28.27f, spectate->GetPositionZ() + 0.25f) : spectate->GetPositionZ() + 0.25f;

        player->SetPendingSpectatorForBG(spectate->GetBattlegroundId());
        player->SetBattlegroundId(spectate->GetBattlegroundId(), spectate->GetBattlegroundTypeId(), PLAYER_MAX_BATTLEGROUND_QUEUES, false, false, TEAM_NEUTRAL);
        player->SetEntryPoint();        
        player->TeleportTo(spectate->GetMapId(), spectate->GetPositionX(), spectate->GetPositionY(), z, spectate->GetOrientation(), TELE_TO_GM_MODE);

        return true;
    }

    bool HandleSpectatorWatchCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return true;

        Player* player = handler->GetSession()->GetPlayer();
        if (!player->IsSpectator())
            return true;

        if (!player->FindMap() || !player->FindMap()->IsBattleArena())
            return true;

        Battleground* bg = ((BattlegroundMap*)player->FindMap())->GetBG();
        if (!bg || bg->GetStatus() != STATUS_IN_PROGRESS)
            return true;

        std::string name = std::string(args);
        Player* spectate = ObjectAccessor::FindPlayerByName(name);
        if (!spectate || !spectate->IsAlive() || spectate->IsSpectator() || spectate->GetGUID() == player->GetGUID() || !spectate->IsInWorld() || !spectate->FindMap() || spectate->IsBeingTeleported() || spectate->FindMap() != player->FindMap() || !bg->IsPlayerInBattleground(spectate->GetGUID()))
            return true;

        if (WorldObject* o = player->GetViewpoint())
            if (Unit* u = o->ToUnit())
            {
                u->RemoveAurasByType(SPELL_AURA_BIND_SIGHT, player->GetGUID());
                player->RemoveAurasDueToSpell(SPECTATOR_SPELL_BINDSIGHT, player->GetGUID(), (1 << EFFECT_1));

                if (u->GetGUID() == spectate->GetGUID())
                    return true;
            }

        if (player->GetUInt64Value(PLAYER_FARSIGHT) || player->m_seer != player) // pussywizard: below this point we must not have a viewpoint!
            return true;

        if (player->HaveAtClient(spectate))
            player->CastSpell(spectate, SPECTATOR_SPELL_BINDSIGHT, true);

        return true;
    }

}
