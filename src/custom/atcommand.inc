// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//ACMD_FUNC(newcommand)
//{
//	clif_displaymessage(fd, "It works!");
//	clif_specialeffect(&sd->bl, EF_HEARTCASTING, AREA);
//	return 0;
//}


#define ACMD_MESSAGE(num, ...) \
	snprintf(atcmd_output, sizeof(atcmd_output), msg_txt(sd, num), ##__VA_ARGS__); \
	clif_displaymessage(fd, atcmd_output);

/**
 * @questadd <id>
 */
ACMD_FUNC(questadd)
{
	int id;

	nullpo_retr(-1, sd);
	memset(atcmd_output, '\0', sizeof(atcmd_output));

	if (!message || !*message || sscanf(message, "%11d", &id) == 0) {
		ACMD_MESSAGE(1525, "questadd");
		return -1;
	}

	std::shared_ptr<s_quest_db> quest = quest_search(id);

	if (quest == nullptr) {
		ACMD_MESSAGE(1526, id);
		return -1;
	}

	if (quest_check(sd, id, HAVEQUEST) >= 0) {
		ACMD_MESSAGE(1527, id);
		return -1;
	}

	quest_add(sd, id);
	ACMD_MESSAGE(1528, id);

	return 0;
}

/**
 * @questcomplete <id>
 */
ACMD_FUNC(questcomplete)
{
	int id, state;

	nullpo_retr(-1, sd);
	memset(atcmd_output, '\0', sizeof(atcmd_output));

	if (!message || !*message || sscanf(message, "%11d", &id) == 0) {
		ACMD_MESSAGE(1525, "questcomplete");
		return -1;
	}
	
	std::shared_ptr<s_quest_db> quest = quest_search(id);

	if (quest == nullptr) {
		ACMD_MESSAGE(1526, id);
		return -1;
	}
	
	state = quest_check(sd, id, HAVEQUEST);

	if (state < 0) {
		ACMD_MESSAGE(1529, id);
		return -1;
	}

	if (state == Q_COMPLETE) {
		ACMD_MESSAGE(1532, id);
		return -1;
	}

	quest_update_status(sd, id, Q_COMPLETE);
	ACMD_MESSAGE(1528, id);

	return 0;
}

/**
 * @questremove <id>
 */
ACMD_FUNC(questremove)
{
	int id;
	
	nullpo_retr(-1, sd);
	memset(atcmd_output, '\0', sizeof(atcmd_output));

	if (!message || !*message || sscanf(message, "%11d", &id) == 0) {
		ACMD_MESSAGE(1525, "questremove");
		return -1;
	}

	
	std::shared_ptr<s_quest_db> quest = quest_search(id);

	if (quest == nullptr) {
		ACMD_MESSAGE(1526, id);
		return -1;
	}

	if (quest_check(sd, id, HAVEQUEST) < 0) {
		ACMD_MESSAGE(1529, id);
		return -1;
	}

	quest_delete(sd, id);
	ACMD_MESSAGE(1530, id);

	return 0;
}

/**
 * @questupdate <id> <mob id> {<count>}
 */
ACMD_FUNC(questupdate)
{
	int id, mob, count = 0;
	int state;
	
	nullpo_retr(-1, sd);
	memset(atcmd_output, '\0', sizeof(atcmd_output));

	if (!message || !*message || sscanf(message, "%11d %11d %11d", &id, &mob, &count) < 2) {
		ACMD_MESSAGE(1531);
		return -1;
	}

	if (count <= 0)
		count = 1;
		
	std::shared_ptr<s_quest_db> quest = quest_search(id);

	if (quest == nullptr) {
		ACMD_MESSAGE(1526, id);
		return -1;
	}

	if (!mobdb_checkid(mob)) {
		ACMD_MESSAGE(1533, mob);
		return -1;
	}

	state = quest_check(sd, id, HAVEQUEST);

	if (state < 0) {
		ACMD_MESSAGE(1529, id);
		return -1;
	}

	if (state == Q_COMPLETE) {
		ACMD_MESSAGE(1532, id);
		return -1;
	}

	struct mob_data * md = map_id2md(id);
	if(!md){
		ACMD_MESSAGE(1533, mob);
		return -1;
	}

	while (count-- > 0)
		quest_update_objective(sd, md);

	ACMD_MESSAGE(1534, id, mob);

	return 0;
}

#ifdef STORM_ITEM_DURABILITY

/**
 * @durability
 */
ACMD_FUNC(durability)
{
	int i, count = 0;

	nullpo_retr(-1, sd);
	memset(atcmd_output, '\0', sizeof(atcmd_output));

	for (i = 0; i < EQI_MAX; i++)
	{
		int index = sd->equip_index[i];
		struct item* it;
		struct item_data* id;

		if (index < 0)
			continue;
		if (i == EQI_AMMO)
			continue;
		if (pc_is_same_equip_index((enum equip_index)i, sd->equip_index, index))
			continue;
		if (!(id = sd->inventory_data[index]))
			continue;

		it = &sd->inventory.u.items_inventory[index];
		ACMD_MESSAGE(1523, it->refine, id->ename.c_str(), id->slots, it->durability / 10000.);
		count++;
	}

	if (!count)
		ACMD_MESSAGE(1522);

	return 0;
}

#endif

#ifdef STORM_BAZAAR

/**
 * @resetbazaar {<id>}
 */
ACMD_FUNC(resetbazaar)
{
	int id;

	nullpo_retr(-1, sd);

	if (!message || !*message || sscanf(message, "%11d", &id) == 0)
	{
		memset(sd->status.bazaar_unlocked, 0, sizeof(sd->status.bazaar_unlocked));
		memset(sd->status.bazaar_sold, 0, sizeof(sd->status.bazaar_sold));
	}
	else
	{
		int i;

		for (i = 0; i < MAX_BAZAAR_ITEMS; i++)
		{
			if (sd->status.bazaar_unlocked[i].bazaarid == id)
				memset(&sd->status.bazaar_unlocked[i], 0, sizeof(bazaarunlocked));
		}
	}

	ACMD_MESSAGE(1521);
	return 0;
}
#endif

#undef ACMD_MESSAGE

void atcommand_battlestats_sub(int fd, map_session_data *sd) {
	status_data *status = status_get_status_data(&sd->bl);
	char output[CHAT_SIZE_MAX];

#define battlestats_msg(__msg__) (__msg__); clif_displaymessage(fd, output)

	battlestats_msg(sprintf(output, "Battle Status: %s", sd->status.name));

	clif_displaymessage(fd, "|--- Basic Info ---|");
	battlestats_msg(sprintf(output, "   -> ATK: %d + %d", pc_leftside_atk(sd), pc_rightside_atk(sd)));
	battlestats_msg(sprintf(output, "   -> MATK: %d + %d", pc_leftside_matk(sd), pc_rightside_matk(sd)));
	battlestats_msg(sprintf(output, "   -> HIT: %d", status->hit));
	battlestats_msg(sprintf(output, "   -> CRIT: %d", status->cri / 10));
	battlestats_msg(sprintf(output, "   -> DEF: %d + %d", pc_leftside_def(sd), pc_rightside_def(sd)));
	battlestats_msg(sprintf(output, "   -> MDEF: %d + %d", pc_leftside_mdef(sd), pc_rightside_mdef(sd)));
	battlestats_msg(sprintf(output, "   -> FLEE: %d + %d", status->flee, status->flee2 / 10));
	battlestats_msg(sprintf(output, "   -> ASPD: %d", (2000 - status->amotion) / 10));
	battlestats_msg(sprintf(output, "   -> ACD: %d%%", sd->bonus.delayrate));
	battlestats_msg(sprintf(output, "   -> Var Cast: -%d%%", sd->bonus.varcastrate));
	battlestats_msg(sprintf(output, "   -> FCT Reduction: %d%% + %d s", sd->bonus.fixcastrate, sd->bonus.add_fixcast/100));

	clif_displaymessage(fd, "|--- Bonus Physical Damages ---|");
	if (sd->right_weapon.addsize[SZ_SMALL] + sd->left_weapon.addsize[SZ_SMALL]) {
		battlestats_msg(sprintf(output, "   -> Small Size: %d%%", sd->right_weapon.addsize[SZ_SMALL] + sd->left_weapon.addsize[SZ_SMALL] + sd->right_weapon.addsize[SZ_ALL] + sd->left_weapon.addsize[SZ_ALL]));
	}
	if (sd->right_weapon.addsize[SZ_MEDIUM] + sd->left_weapon.addsize[SZ_MEDIUM]) {
		battlestats_msg(sprintf(output, "   -> Medium Size: %d%%", sd->right_weapon.addsize[SZ_MEDIUM] + sd->left_weapon.addsize[SZ_MEDIUM] + sd->right_weapon.addsize[SZ_ALL] + sd->left_weapon.addsize[SZ_ALL]));
	}
	if (sd->right_weapon.addsize[SZ_BIG] + sd->left_weapon.addsize[SZ_BIG]) {
		battlestats_msg(sprintf(output, "   -> Large Size: %d%%", sd->right_weapon.addsize[SZ_BIG] + sd->left_weapon.addsize[SZ_BIG] + sd->right_weapon.addsize[SZ_ALL] + sd->left_weapon.addsize[SZ_ALL]));
	}
	if (sd->right_weapon.addrace[RC_PLAYER_HUMAN] + sd->left_weapon.addrace[RC_PLAYER_HUMAN]) {
		battlestats_msg(sprintf(output, "   -> Player Human: %d%%", sd->right_weapon.addrace[RC_PLAYER_HUMAN] + sd->left_weapon.addrace[RC_PLAYER_HUMAN] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}
	if (sd->right_weapon.addrace[RC_PLAYER_DORAM] + sd->left_weapon.addrace[RC_PLAYER_DORAM]) {
		battlestats_msg(sprintf(output, "   -> Player Doram: %d%%", sd->right_weapon.addrace[RC_PLAYER_DORAM] + sd->left_weapon.addrace[RC_PLAYER_DORAM] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}
	if (sd->right_weapon.addrace[RC_ANGEL] + sd->left_weapon.addrace[RC_ANGEL]) {
		battlestats_msg(sprintf(output, "   -> Angel: %d%%", sd->right_weapon.addrace[RC_ANGEL] + sd->left_weapon.addrace[RC_ANGEL] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}
	if (sd->right_weapon.addrace[RC_BRUTE] + sd->left_weapon.addrace[RC_BRUTE]) {
		battlestats_msg(sprintf(output, "   -> Brute: %d%%", sd->right_weapon.addrace[RC_BRUTE] + sd->left_weapon.addrace[RC_BRUTE] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}
	if (sd->right_weapon.addrace[RC_DEMIHUMAN] + sd->left_weapon.addrace[RC_DEMIHUMAN]) {
		battlestats_msg(sprintf(output, "   -> Demihuman: %d%%", sd->right_weapon.addrace[RC_DEMIHUMAN] + sd->left_weapon.addrace[RC_DEMIHUMAN] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}
	if (sd->right_weapon.addrace[RC_DRAGON] + sd->left_weapon.addrace[RC_DRAGON]) {
		battlestats_msg(sprintf(output, "   -> Dragon: %d%%", sd->right_weapon.addrace[RC_DRAGON] + sd->left_weapon.addrace[RC_DRAGON] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}
	if (sd->right_weapon.addrace[RC_FISH] + sd->left_weapon.addrace[RC_FISH]) {
		battlestats_msg(sprintf(output, "   -> Fish: %d%%", sd->right_weapon.addrace[RC_FISH] + sd->left_weapon.addrace[RC_FISH] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}
	if (sd->right_weapon.addrace[RC_FORMLESS] + sd->left_weapon.addrace[RC_FORMLESS]) {
		battlestats_msg(sprintf(output, "   -> Formless: %d%%", sd->right_weapon.addrace[RC_FORMLESS] + sd->left_weapon.addrace[RC_FORMLESS] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}
	if (sd->right_weapon.addrace[RC_INSECT] + sd->left_weapon.addrace[RC_INSECT]) {
		battlestats_msg(sprintf(output, "   -> Insect: %d%%", sd->right_weapon.addrace[RC_INSECT] + sd->left_weapon.addrace[RC_INSECT] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}
	if (sd->right_weapon.addrace[RC_PLANT] + sd->left_weapon.addrace[RC_PLANT]) {
		battlestats_msg(sprintf(output, "   -> Plant: %d%%", sd->right_weapon.addrace[RC_PLANT] + sd->left_weapon.addrace[RC_PLANT] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}
	if (sd->right_weapon.addrace[RC_UNDEAD] + sd->left_weapon.addrace[RC_UNDEAD]) {
		battlestats_msg(sprintf(output, "   -> Undead: %d%%", sd->right_weapon.addrace[RC_UNDEAD] + sd->left_weapon.addrace[RC_UNDEAD] + sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
	}


	if (sd->right_weapon.addclass[CLASS_NORMAL] + sd->left_weapon.addclass[CLASS_NORMAL]) {
		battlestats_msg(sprintf(output, "   -> Normal Class: %d%%", sd->right_weapon.addclass[CLASS_NORMAL] + sd->left_weapon.addclass[CLASS_NORMAL] + sd->right_weapon.addclass[CLASS_ALL] + sd->left_weapon.addclass[CLASS_ALL]));
	}
	if (sd->right_weapon.addclass[CLASS_BOSS] + sd->left_weapon.addclass[CLASS_BOSS]) {
		battlestats_msg(sprintf(output, "   -> Boss Class: %d%%", sd->right_weapon.addclass[CLASS_BOSS] + sd->left_weapon.addclass[CLASS_BOSS] + sd->right_weapon.addclass[CLASS_ALL] + sd->left_weapon.addclass[CLASS_ALL]));
	}

	clif_displaymessage(fd, "|--- Bonus Magic Damages ---|");
	if (sd->indexed_bonus.magic_addsize[SZ_SMALL]) {
		battlestats_msg(sprintf(output, "   -> Small Size: %d%%", sd->indexed_bonus.magic_addsize[SZ_SMALL] + sd->indexed_bonus.magic_addsize[SZ_ALL]));
	}
	if (sd->indexed_bonus.magic_addsize[SZ_MEDIUM]) {
		battlestats_msg(sprintf(output, "   -> Medium Size: %d%%", sd->indexed_bonus.magic_addsize[SZ_MEDIUM] + sd->indexed_bonus.magic_addsize[SZ_ALL]));
	}
	if (sd->indexed_bonus.magic_addsize[SZ_BIG]) {
		battlestats_msg(sprintf(output, "   -> Large Size: %d%%", sd->indexed_bonus.magic_addsize[SZ_BIG] + sd->indexed_bonus.magic_addsize[SZ_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_PLAYER_HUMAN]) {
		battlestats_msg(sprintf(output, "   -> Player Human: %d%%", sd->indexed_bonus.magic_addrace[RC_PLAYER_HUMAN] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_PLAYER_DORAM]) {
		battlestats_msg(sprintf(output, "   -> Player Doram: %d%%", sd->indexed_bonus.magic_addrace[RC_PLAYER_DORAM] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_ANGEL]) {
		battlestats_msg(sprintf(output, "   -> Angel: %d%%", sd->indexed_bonus.magic_addrace[RC_ANGEL] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_BRUTE]) {
		battlestats_msg(sprintf(output, "   -> Brute: %d%%", sd->indexed_bonus.magic_addrace[RC_BRUTE] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_DEMIHUMAN]) {
		battlestats_msg(sprintf(output, "   -> Demihuman: %d%%", sd->indexed_bonus.magic_addrace[RC_DEMIHUMAN] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_DRAGON]) {
		battlestats_msg(sprintf(output, "   -> Dragon: %d%%", sd->indexed_bonus.magic_addrace[RC_DRAGON] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_FISH]) {
		battlestats_msg(sprintf(output, "   -> Fish: %d%%", sd->indexed_bonus.magic_addrace[RC_FISH] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_FORMLESS]) {
		battlestats_msg(sprintf(output, "   -> Formless: %d%%", sd->indexed_bonus.magic_addrace[RC_FORMLESS] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_INSECT]) {
		battlestats_msg(sprintf(output, "   -> Insect: %d%%", sd->indexed_bonus.magic_addrace[RC_INSECT] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_PLANT]) {
		battlestats_msg(sprintf(output, "   -> Plant: %d%%", sd->indexed_bonus.magic_addrace[RC_PLANT] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addrace[RC_UNDEAD]) {
		battlestats_msg(sprintf(output, "   -> Undead: %d%%", sd->indexed_bonus.magic_addrace[RC_UNDEAD] + sd->indexed_bonus.magic_addrace[RC_ALL]));
	}
	if (sd->indexed_bonus.magic_addclass[CLASS_NORMAL]) {
		battlestats_msg(sprintf(output, "   -> Normal Class: %d%%", sd->indexed_bonus.magic_addclass[CLASS_NORMAL] + sd->indexed_bonus.magic_addclass[CLASS_ALL]));
	}

	clif_displaymessage(fd, "|--- General Defense ---|");
	battlestats_msg(sprintf(output, "   -> Melee: %d%%", sd->bonus.near_attack_def_rate));
	battlestats_msg(sprintf(output, "   -> Long Range: %d%%", sd->bonus.long_attack_def_rate));
	battlestats_msg(sprintf(output, "   -> Magic: %d%%", sd->bonus.magic_def_rate));
	battlestats_msg(sprintf(output, "   -> Critical: %d%%", sd->bonus.critical_def));

	clif_displaymessage(fd, "|--- Elemental Resistance ---|");
	struct {
		const char *format;
		int value;
	} ele_resist_info[] = {
		{ "   -> Neutral: %d%%", sd->indexed_bonus.subele_script[ELE_NEUTRAL] + sd->indexed_bonus.subele_script[ELE_ALL]},
		{ "   -> Water: %d%%", sd->indexed_bonus.subele_script[ELE_WATER] + sd->indexed_bonus.subele_script[ELE_ALL]},
		{ "   -> Earth: %d%%", sd->indexed_bonus.subele_script[ELE_EARTH] + sd->indexed_bonus.subele_script[ELE_ALL]},
		{ "   -> Fire: %d%%", sd->indexed_bonus.subele_script[ELE_FIRE] + sd->indexed_bonus.subele_script[ELE_ALL]},
		{ "   -> Wind: %d%%", sd->indexed_bonus.subele_script[ELE_WIND] + sd->indexed_bonus.subele_script[ELE_ALL]},
		{ "   -> Poison: %d%%", sd->indexed_bonus.subele_script[ELE_POISON] + sd->indexed_bonus.subele_script[ELE_ALL]},
		{ "   -> Holy: %d%%", sd->indexed_bonus.subele_script[ELE_HOLY] + sd->indexed_bonus.subele_script[ELE_ALL]},
		{ "   -> Dark: %d%%", sd->indexed_bonus.subele_script[ELE_DARK] + sd->indexed_bonus.subele_script[ELE_ALL]},
		{ "   -> Ghost: %d%%", sd->indexed_bonus.subele_script[ELE_GHOST] + sd->indexed_bonus.subele_script[ELE_ALL]},
		{ "   -> Undead: %d%%", sd->indexed_bonus.subele_script[ELE_UNDEAD] + sd->indexed_bonus.subele_script[ELE_ALL]},
	};
	for (int i = 0; i < ARRAYLENGTH(ele_resist_info); i++) {
		if (ele_resist_info[i].value == 0)
			continue;
		battlestats_msg(sprintf(output, ele_resist_info[i].format, ele_resist_info[i].value));
	}

	clif_displaymessage(fd, "|--- General Resistance ---|");
	struct {
		const char *format;
		int value;
	} race_resist_info[] = {
		{ "   -> Formless: %d%%", sd->indexed_bonus.subrace[RC_FORMLESS] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Undead: %d%%", sd->indexed_bonus.subrace[RC_UNDEAD] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Beast: %d%%", sd->indexed_bonus.subrace[RC_BRUTE] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Plant: %d%%", sd->indexed_bonus.subrace[RC_PLANT] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Insect: %d%%", sd->indexed_bonus.subrace[RC_INSECT] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Fish: %d%%", sd->indexed_bonus.subrace[RC_FISH] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Demon: %d%%", sd->indexed_bonus.subrace[RC_DEMON] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> DemiHuman: %d%%", sd->indexed_bonus.subrace[RC_DEMIHUMAN] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Angel: %d%%", sd->indexed_bonus.subrace[RC_ANGEL] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Dragon: %d%%", sd->indexed_bonus.subrace[RC_DRAGON] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Player Human: %d%%", sd->indexed_bonus.subrace[RC_PLAYER_HUMAN] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Player Doram: %d%%", sd->indexed_bonus.subrace[RC_PLAYER_DORAM] + sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Normal Class: %d%%", sd->indexed_bonus.subclass[CLASS_NORMAL] + sd->indexed_bonus.subclass[CLASS_ALL] },
		{ "   -> Boss Class: %d%%", sd->indexed_bonus.subclass[CLASS_BOSS] + sd->indexed_bonus.subclass[CLASS_ALL] },
	};
	for (int i = 0; i < ARRAYLENGTH(race_resist_info); i++) {
		if (race_resist_info[i].value == 0)
			continue;
		battlestats_msg(sprintf(output, race_resist_info[i].format, race_resist_info[i].value));
	}

#undef battlestats_msg
}

ACMD_FUNC(battlestats) {
	nullpo_retr(-1, sd);
	atcommand_battlestats_sub(fd, sd);
	return 0;
}

ACMD_FUNC(enemystats) {
	map_session_data *pl_sd;

	nullpo_retr(-1, sd);

	memset(atcmd_player_name, '\0', sizeof atcmd_player_name);

	if (!message || !*message || sscanf(message, "%23[^\n]", atcmd_player_name) < 1) {
		clif_displaymessage(fd, "Please enter a player name (usage: @enemystats <char name>)");
		return -1;
	}

	pl_sd = map_nick2sd(atcmd_player_name, true);
	if (pl_sd == NULL ||
		strncmp(pl_sd->status.name, atcmd_player_name, NAME_LENGTH) != 0 ||
		(pc_has_permission(pl_sd, PC_PERM_HIDE_SESSION) && pc_get_group_level(pl_sd) > pc_get_group_level(sd))
		) {
		clif_displaymessage(fd, msg_txt(sd, 3)); // Character not found.
		return -1;
	}

	atcommand_battlestats_sub(fd, pl_sd);
	return 0;
}
