/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef TRINITY_DBCSTORES_H
#define TRINITY_DBCSTORES_H

#include "Common.h"
#include "DBCStore.h"
#include "DBCStructure.h"

#include <list>

typedef std::list<uint32> SimpleFactionsList;
AC_GAME_API SimpleFactionsList const* GetFactionTeamList(uint32 faction);

AC_GAME_API char* GetPetName(uint32 petfamily, uint32 dbclang);
AC_GAME_API uint32 GetTalentSpellCost(uint32 spellId);
AC_GAME_API TalentSpellPos const* GetTalentSpellPos(uint32 spellId);

AC_GAME_API WMOAreaTableEntry const* GetWMOAreaTableEntryByTripple(int32 rootid, int32 adtid, int32 groupid);

AC_GAME_API uint32 GetVirtualMapForMapAndZone(uint32 mapid, uint32 zoneId);

enum ContentLevels
{
    CONTENT_1_60 = 0,
    CONTENT_61_70,
    CONTENT_71_80
};

AC_GAME_API ContentLevels GetContentLevelsForMapAndZone(uint32 mapid, uint32 zoneId);

AC_GAME_API void Zone2MapCoordinates(float &x, float &y, uint32 zone);
AC_GAME_API void Map2ZoneCoordinates(float &x, float &y, uint32 zone);

typedef std::map<uint32/*pair32(map, diff)*/, MapDifficulty> MapDifficultyMap;
AC_GAME_API MapDifficulty const* GetMapDifficultyData(uint32 mapId, Difficulty difficulty);
AC_GAME_API MapDifficulty const* GetDownscaledMapDifficultyData(uint32 mapId, Difficulty &difficulty);

AC_GAME_API bool IsSharedDifficultyMap(uint32 mapid);

AC_GAME_API uint32 GetLiquidFlags(uint32 liquidType);

AC_GAME_API PvPDifficultyEntry const* GetBattlegroundBracketByLevel(uint32 mapid, uint32 level);
AC_GAME_API PvPDifficultyEntry const* GetBattlegroundBracketById(uint32 mapid, BattlegroundBracketId id);

AC_GAME_API CharStartOutfitEntry const* GetCharStartOutfitEntry(uint8 race, uint8 class_, uint8 gender);

AC_GAME_API LFGDungeonEntry const* GetLFGDungeon(uint32 mapId, Difficulty difficulty);
AC_GAME_API uint32 GetDefaultMapLight(uint32 mapId);

AC_GAME_API extern DBCStorage <AchievementEntry>             sAchievementStore;
AC_GAME_API extern DBCStorage <AchievementCriteriaEntry>     sAchievementCriteriaStore;
AC_GAME_API extern DBCStorage <AchievementCategoryEntry>     sAchievementCategoryStore;
AC_GAME_API extern DBCStorage <AreaTableEntry>               sAreaTableStore;
AC_GAME_API extern DBCStorage <AreaGroupEntry>               sAreaGroupStore;
AC_GAME_API extern DBCStorage <AreaPOIEntry>                 sAreaPOIStore;
AC_GAME_API extern DBCStorage <AuctionHouseEntry>            sAuctionHouseStore;
AC_GAME_API extern DBCStorage <BankBagSlotPricesEntry>       sBankBagSlotPricesStore;
AC_GAME_API extern DBCStorage <BarberShopStyleEntry>         sBarberShopStyleStore;
AC_GAME_API extern DBCStorage <BattlemasterListEntry>        sBattlemasterListStore;
AC_GAME_API extern DBCStorage <ChatChannelsEntry>            sChatChannelsStore;
AC_GAME_API extern DBCStorage <CharStartOutfitEntry>         sCharStartOutfitStore;
AC_GAME_API extern DBCStorage <CharTitlesEntry>              sCharTitlesStore;
AC_GAME_API extern DBCStorage <ChrClassesEntry>              sChrClassesStore;
AC_GAME_API extern DBCStorage <ChrRacesEntry>                sChrRacesStore;
AC_GAME_API extern DBCStorage <CinematicSequencesEntry>      sCinematicSequencesStore;
AC_GAME_API extern DBCStorage <CreatureDisplayInfoEntry>     sCreatureDisplayInfoStore;
AC_GAME_API extern DBCStorage <CreatureFamilyEntry>          sCreatureFamilyStore;
AC_GAME_API extern DBCStorage <CreatureModelDataEntry>       sCreatureModelDataStore;
AC_GAME_API extern DBCStorage <CreatureSpellDataEntry>       sCreatureSpellDataStore;
AC_GAME_API extern DBCStorage <CreatureTypeEntry>            sCreatureTypeStore;
AC_GAME_API extern DBCStorage <CurrencyTypesEntry>           sCurrencyTypesStore;
AC_GAME_API extern DBCStorage <DestructibleModelDataEntry>   sDestructibleModelDataStore;
AC_GAME_API extern DBCStorage <DungeonEncounterEntry>        sDungeonEncounterStore;
AC_GAME_API extern DBCStorage <DurabilityCostsEntry>         sDurabilityCostsStore;
AC_GAME_API extern DBCStorage <DurabilityQualityEntry>       sDurabilityQualityStore;
AC_GAME_API extern DBCStorage <EmotesEntry>                  sEmotesStore;
AC_GAME_API extern DBCStorage <EmotesTextEntry>              sEmotesTextStore;
AC_GAME_API extern DBCStorage <FactionEntry>                 sFactionStore;
AC_GAME_API extern DBCStorage <FactionTemplateEntry>         sFactionTemplateStore;
AC_GAME_API extern DBCStorage <GameObjectDisplayInfoEntry>   sGameObjectDisplayInfoStore;
AC_GAME_API extern DBCStorage <GemPropertiesEntry>           sGemPropertiesStore;
AC_GAME_API extern DBCStorage <GlyphPropertiesEntry>         sGlyphPropertiesStore;
AC_GAME_API extern DBCStorage <GlyphSlotEntry>               sGlyphSlotStore;

AC_GAME_API extern DBCStorage <GtBarberShopCostBaseEntry>    sGtBarberShopCostBaseStore;
AC_GAME_API extern DBCStorage <GtCombatRatingsEntry>         sGtCombatRatingsStore;
AC_GAME_API extern DBCStorage <GtChanceToMeleeCritBaseEntry> sGtChanceToMeleeCritBaseStore;
AC_GAME_API extern DBCStorage <GtChanceToMeleeCritEntry>     sGtChanceToMeleeCritStore;
AC_GAME_API extern DBCStorage <GtChanceToSpellCritBaseEntry> sGtChanceToSpellCritBaseStore;
AC_GAME_API extern DBCStorage <GtChanceToSpellCritEntry>     sGtChanceToSpellCritStore;
AC_GAME_API extern DBCStorage <GtNPCManaCostScalerEntry>     sGtNPCManaCostScalerStore;
AC_GAME_API extern DBCStorage <GtOCTClassCombatRatingScalarEntry> sGtOCTClassCombatRatingScalarStore;
AC_GAME_API extern DBCStorage <GtOCTRegenHPEntry>            sGtOCTRegenHPStore;
//AC_GAME_API extern DBCStorage <GtOCTRegenMPEntry>            sGtOCTRegenMPStore; -- not used currently
AC_GAME_API extern DBCStorage <GtRegenHPPerSptEntry>         sGtRegenHPPerSptStore;
AC_GAME_API extern DBCStorage <GtRegenMPPerSptEntry>         sGtRegenMPPerSptStore;
AC_GAME_API extern DBCStorage <HolidaysEntry>                sHolidaysStore;
AC_GAME_API extern DBCStorage <ItemBagFamilyEntry>           sItemBagFamilyStore;
AC_GAME_API extern DBCStorage <ItemDisplayInfoEntry>         sItemDisplayInfoStore;
AC_GAME_API extern DBCStorage <ItemExtendedCostEntry>        sItemExtendedCostStore;
AC_GAME_API extern DBCStorage <ItemLimitCategoryEntry>       sItemLimitCategoryStore;
AC_GAME_API extern DBCStorage <ItemRandomPropertiesEntry>    sItemRandomPropertiesStore;
AC_GAME_API extern DBCStorage <ItemRandomSuffixEntry>        sItemRandomSuffixStore;
AC_GAME_API extern DBCStorage <ItemSetEntry>                 sItemSetStore;
AC_GAME_API extern DBCStorage <LFGDungeonEntry>           sLFGDungeonStore;
AC_GAME_API extern DBCStorage <LiquidTypeEntry>              sLiquidTypeStore;
AC_GAME_API extern DBCStorage <LockEntry>                    sLockStore;
AC_GAME_API extern DBCStorage <MailTemplateEntry>            sMailTemplateStore;
AC_GAME_API extern DBCStorage <MapEntry>                     sMapStore;
//extern DBCStorage <MapDifficultyEntry>           sMapDifficultyStore; -- use GetMapDifficultyData insteed
AC_GAME_API extern MapDifficultyMap                          sMapDifficultyMap;
AC_GAME_API extern DBCStorage <MovieEntry>                   sMovieStore;
AC_GAME_API extern DBCStorage <OverrideSpellDataEntry>       sOverrideSpellDataStore;
AC_GAME_API extern DBCStorage <PowerDisplayEntry>            sPowerDisplayStore;
AC_GAME_API extern DBCStorage <QuestSortEntry>               sQuestSortStore;
AC_GAME_API extern DBCStorage <QuestXPEntry>                 sQuestXPStore;
AC_GAME_API extern DBCStorage <QuestFactionRewEntry>         sQuestFactionRewardStore;
AC_GAME_API extern DBCStorage <RandomPropertiesPointsEntry>  sRandomPropertiesPointsStore;
AC_GAME_API extern DBCStorage <ScalingStatDistributionEntry> sScalingStatDistributionStore;
AC_GAME_API extern DBCStorage <ScalingStatValuesEntry>       sScalingStatValuesStore;
AC_GAME_API extern DBCStorage <SkillLineEntry>               sSkillLineStore;
AC_GAME_API extern DBCStorage <SkillLineAbilityEntry>        sSkillLineAbilityStore;
AC_GAME_API extern DBCStorage <SoundEntriesEntry>            sSoundEntriesStore;
AC_GAME_API extern DBCStorage <SpellCastTimesEntry>          sSpellCastTimesStore;
AC_GAME_API extern DBCStorage <SpellCategoryEntry>           sSpellCategoryStore;
AC_GAME_API extern DBCStorage <SpellDifficultyEntry>         sSpellDifficultyStore;
AC_GAME_API extern DBCStorage <SpellDurationEntry>           sSpellDurationStore;
AC_GAME_API extern DBCStorage <SpellFocusObjectEntry>        sSpellFocusObjectStore;
AC_GAME_API extern DBCStorage <SpellItemEnchantmentEntry>    sSpellItemEnchantmentStore;
AC_GAME_API extern DBCStorage <SpellItemEnchantmentConditionEntry> sSpellItemEnchantmentConditionStore;
AC_GAME_API extern SpellCategoryStore                        sSpellsByCategoryStore;
AC_GAME_API extern PetFamilySpellsStore                      sPetFamilySpellsStore;
AC_GAME_API extern DBCStorage <SpellRadiusEntry>             sSpellRadiusStore;
AC_GAME_API extern DBCStorage <SpellRangeEntry>              sSpellRangeStore;
AC_GAME_API extern DBCStorage <SpellRuneCostEntry>           sSpellRuneCostStore;
AC_GAME_API extern DBCStorage <SpellShapeshiftEntry>         sSpellShapeshiftStore;
AC_GAME_API extern DBCStorage <SpellEntry>                   sSpellStore;
AC_GAME_API extern DBCStorage <StableSlotPricesEntry>        sStableSlotPricesStore;
AC_GAME_API extern DBCStorage <SummonPropertiesEntry>        sSummonPropertiesStore;
AC_GAME_API extern DBCStorage <TalentEntry>                  sTalentStore;
AC_GAME_API extern DBCStorage <TalentTabEntry>               sTalentTabStore;
AC_GAME_API extern DBCStorage <TaxiNodesEntry>               sTaxiNodesStore;
AC_GAME_API extern DBCStorage <TaxiPathEntry>                sTaxiPathStore;
AC_GAME_API extern TaxiMask                                  sTaxiNodesMask;
AC_GAME_API extern TaxiMask                                  sOldContinentsNodesMask;
AC_GAME_API extern TaxiMask                                  sHordeTaxiNodesMask;
AC_GAME_API extern TaxiMask                                  sAllianceTaxiNodesMask;
AC_GAME_API extern TaxiMask                                  sDeathKnightTaxiNodesMask;
AC_GAME_API extern TaxiPathSetBySource                       sTaxiPathSetBySource;
AC_GAME_API extern TaxiPathNodesByPath                       sTaxiPathNodesByPath;
AC_GAME_API extern DBCStorage <TeamContributionPointsEntry>  sTeamContributionPointsStore;
AC_GAME_API extern DBCStorage <TotemCategoryEntry>           sTotemCategoryStore;
AC_GAME_API extern DBCStorage <VehicleEntry>                 sVehicleStore;
AC_GAME_API extern DBCStorage <VehicleSeatEntry>             sVehicleSeatStore;
AC_GAME_API extern DBCStorage <WMOAreaTableEntry>            sWMOAreaTableStore;
//extern DBCStorage <WorldMapAreaEntry>           sWorldMapAreaStore; -- use Zone2MapCoordinates and Map2ZoneCoordinates
AC_GAME_API extern DBCStorage <WorldMapOverlayEntry>         sWorldMapOverlayStore;

AC_GAME_API void LoadDBCStores(const std::string& dataPath);

#endif
