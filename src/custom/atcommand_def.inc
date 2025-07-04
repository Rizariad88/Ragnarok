// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the definition of custom atcommands in this file.
 * Format:
 *	ACMD_DEF(command_name),
 **/

//ACMD_DEF(newcommand),

// Stormbreaker
ACMD_DEF(questadd),
ACMD_DEF(questcomplete),
ACMD_DEF(questremove),
ACMD_DEF(questupdate),

#ifdef STORM_ITEM_DURABILITY
ACMD_DEF(durability),
#endif

#ifdef STORM_BAZAAR
ACMD_DEF(resetbazaar),
#endif

ACMD_DEFR(battlestats, ATCMD_NOCONSOLE|ATCMD_NOAUTOTRADE),
ACMD_DEFR(enemystats, ATCMD_NOCONSOLE|ATCMD_NOAUTOTRADE),
