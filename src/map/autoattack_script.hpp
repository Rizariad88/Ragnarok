#ifndef AUTOATTACK_SCRIPT_H
#define AUTOATTACK_SCRIPT_H

#define MIN_MOB_DB 1000
#define MAX_MOB_DB 3999
#define MIN_MOB_DB2 20020
#define MAX_MOB_DB2 31999

#include "autoattack.hpp"
#include "pc.hpp"

#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "../common/db.hpp"
#include "../common/database.hpp"
#include "../common/utilities.hpp"
#include "../common/utils.hpp"

//Get string script
void handle_autoattack_heal(std::ostringstream& os_buf, int index, int extra_index, script_state* st, map_session_data* sd);
void handle_autoattack_potions(std::ostringstream& os_buf, int index, script_state* st, map_session_data* sd);
void handle_autoattack_attack(std::ostringstream& os_buf, int index, int extra_index, script_state* st, map_session_data* sd);
void handle_autoattack_buff(std::ostringstream& os_buf, int index, int extra_index, script_state* st, map_session_data* sd);
void handle_autoattack_items(std::ostringstream& os_buf, int index, script_state* st, map_session_data* sd);
void handle_potions(std::ostringstream& os_buf, map_session_data* sd);
void handle_token_of_siegfried(std::ostringstream& os_buf, map_session_data* sd);
void handle_return_to_savepoint(std::ostringstream& os_buf, map_session_data* sd);
void handle_party_request(std::ostringstream& os_buf, map_session_data* sd);
void handle_priorize_loot_fight(std::ostringstream& os_buf, map_session_data* sd);
void handle_autoattack_sitrest(std::ostringstream& os_buf, int index, script_state* st, map_session_data* sd);
void handle_autoattack_teleport(std::ostringstream& os_buf, int index, script_state* st, map_session_data* sd);
void handle_autoattack_monsterselection(std::ostringstream& os_buf, int index, int extra_index, script_state* st, map_session_data* sd);
void handle_autoattack_itempickup(std::ostringstream& os_buf, int index, int extra_index, script_state* st, map_session_data* sd);

//Start the aa
bool handleAutoattack_fromitem(map_session_data* sd, t_itemid item_id, t_tick max_duration);

//Set script
void handleAutoHeal(const std::vector<std::string>& result, map_session_data* sd);
void handleAutoPotion(const std::vector<std::string>& result, map_session_data* sd);
void handleAutoAttackSkills(const std::vector<std::string>& result, map_session_data* sd);
void handleAutoBuffSkills(const std::vector<std::string>& result, map_session_data* sd);
void handleAutoAttackItems(const std::vector<std::string>& result, map_session_data* sd);
void handleAutoAttackPotionState(const std::vector<std::string>& result, map_session_data* sd);
void handleReturnToSavepoint(const std::vector<std::string>& result, map_session_data* sd);
void handleResetAutoAttackConfig(map_session_data* sd);
void handleTokenOfSiegfried(const std::vector<std::string>& result, map_session_data* sd);
void handlePriorizeLootFight(const std::vector<std::string>& result, map_session_data* sd);
void handleAcceptPartyRequest(const std::vector<std::string>& result, map_session_data* sd);
void handleMeleeAttack(const std::vector<std::string>& result, map_session_data* sd);
void handleTeleportFlywing(const std::vector<std::string>& result, map_session_data* sd);
void handleTeleportSkill(const std::vector<std::string>& result, map_session_data* sd);
void handleSitRestHp(const std::vector<std::string>& result, map_session_data* sd);
void handleSitRestSp(const std::vector<std::string>& result, map_session_data* sd);
void handleTeleportMinHp(const std::vector<std::string>& result, map_session_data* sd);
void handleTeleportNoMobMeet(const std::vector<std::string>& result, map_session_data* sd);
void handleIgnoreAggressiveMonster(const std::vector<std::string>& result, map_session_data* sd);
void handleMonsterSelection(const std::vector<std::string>& result, map_session_data* sd);
void handleItemPickupConfiguration(const std::vector<std::string>& result, map_session_data* sd);
void handleItemPickupSelection(const std::vector<std::string>& result, map_session_data* sd);
void handleActionOnEnd(const std::vector<std::string>& result, map_session_data* sd);
void handleMonsterSurround(const std::vector<std::string>& result, map_session_data* sd);

int handleGetautoattackint(map_session_data* sd, const int value);

#endif // AUTOATTACK_SCRIPT_H
