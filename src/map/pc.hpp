// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef PC_HPP
#define PC_HPP

#include <bitset>
#include <memory>
#include <vector>

#include "../common/cbasetypes.hpp"
#include "../common/database.hpp"
#include "../common/mmo.hpp" // JOB_*, MAX_FAME_LIST, struct fame_list, struct mmo_charstatus
#include "../common/strlib.hpp"// StringBuf
#include "../common/timer.hpp"

#include "autoattack.hpp"
#include "battleground.hpp"
#include "buyingstore.hpp" // struct s_buyingstore
#include "clif.hpp" //e_wip_block
#include "itemdb.hpp" // MAX_ITEMGROUP
#include "map.hpp" // RC_ALL
#include "mob.hpp" //e_size
#include "pc_groups.hpp" // s_player_group
#include "script.hpp" // struct script_reg, struct script_regstr
#include "searchstore.hpp"  // struct s_search_store_info
#include "status.hpp" // unit_data
#include "stormbreaker.hpp"
#include "unit.hpp" // unit_data
#include "vending.hpp" // struct s_vending

enum AtCommandType : uint8;
enum e_instance_mode : uint8;
//enum e_log_chat_type : uint8;
enum e_log_pick_type : uint32;
enum sc_type : int16;

#define MAX_PC_BONUS 50 /// Max bonus, usually used by item bonus
#define MAX_PC_FEELHATE 3 /// Max feel hate info
#define DAMAGELOG_SIZE_PC 100	/// Damage log
#define MAX_SPIRITBALL 15 /// Max spirit balls
#define MAX_DEVOTION 5 /// Max Devotion slots
#define MAX_SPIRITCHARM 10 /// Max spirit charms
#define MAX_SOUL_BALL 20 /// Max soul ball
#define MAX_STELLAR_MARKS 5 /// Max stellar marks
#define MAX_UNITED_SOULS 12 /// Max united souls
#define MAX_SERVANTBALL 5 /// Max servant weapons
#define MAX_SERVANT_SIGN 5 /// Max servant signs
#define MAX_ABYSSBALL 5 /// Max abyss spheres

#define LANGTYPE_VAR "#langtype"
#define CASHPOINT_VAR "#CASHPOINTS"
#define KAFRAPOINT_VAR "#KAFRAPOINTS"
#define BANK_VAULT_VAR "#BANKVAULT"
#define ROULETTE_BRONZE_VAR "RouletteBronze"
#define ROULETTE_SILVER_VAR "RouletteSilver"
#define ROULETTE_GOLD_VAR "RouletteGold"
#define COOKMASTERY_VAR "COOK_MASTERY"
#define PCDIECOUNTER_VAR "PC_DIE_COUNTER"
#define JOBCHANGE2ND_VAR "jobchange_level"
#define JOBCHANGE3RD_VAR "jobchange_level_3rd"
#define JOBCHANGE4TH_VAR "jobchange_level_4th"
#define TKMISSIONID_VAR "TK_MISSION_ID"
#define TKMISSIONCOUNT_VAR "TK_MISSION_COUNT"
#define ATTENDANCE_DATE_VAR "#AttendanceDate"
#define ATTENDANCE_COUNT_VAR "#AttendanceCounter"
#define ACHIEVEMENTLEVEL "AchievementLevel"
#ifndef GOLDPC_POINT_VAR
	#define GOLDPC_POINT_VAR "Goldpc_Points"
#endif
#ifndef GOLDPC_SECONDS_VAR
	#define GOLDPC_SECONDS_VAR "Goldpc_Seconds"
#endif

//Total number of classes (for data storage)
#define CLASS_COUNT (JOB_MAX - JOB_NOVICE_HIGH + JOB_MAX_BASIC)


enum weapon_type : uint8 {
	W_FIST,	//Bare hands
	W_DAGGER,	//1
	W_1HSWORD,	//2
	W_2HSWORD,	//3
	W_1HSPEAR,	//4
	W_2HSPEAR,	//5
	W_1HAXE,	//6
	W_2HAXE,	//7
	W_MACE,	//8
	W_2HMACE,	//9 (unused)
	W_STAFF,	//10
	W_BOW,	//11
	W_KNUCKLE,	//12
	W_MUSICAL,	//13
	W_WHIP,	//14
	W_BOOK,	//15
	W_KATAR,	//16
	W_REVOLVER,	//17
	W_RIFLE,	//18
	W_GATLING,	//19
	W_SHOTGUN,	//20
	W_GRENADE,	//21
	W_HUUMA,	//22
	W_2HSTAFF,	//23
	MAX_WEAPON_TYPE,
	// dual-wield constants
	W_DOUBLE_DD, // 2 daggers
	W_DOUBLE_SS, // 2 swords
	W_DOUBLE_AA, // 2 axes
	W_DOUBLE_DS, // dagger + sword
	W_DOUBLE_DA, // dagger + axe
	W_DOUBLE_SA, // sword + axe
	MAX_WEAPON_TYPE_ALL,
	W_SHIELD = MAX_WEAPON_TYPE,
};

#define WEAPON_TYPE_ALL ((1<<MAX_WEAPON_TYPE)-1)

//Equip indexes constants. (eg: sd->equip_index[EQI_AMMO] returns the index
//where the arrows are equipped)
enum equip_index {
	EQI_COMPOUND_ON = -1,
	EQI_ACC_L = 0,
	EQI_ACC_R,
	EQI_SHOES,
	EQI_GARMENT,
	EQI_HEAD_LOW,
	EQI_HEAD_MID,
	EQI_HEAD_TOP,
	EQI_ARMOR,
	EQI_HAND_L,
	EQI_HAND_R,
	EQI_COSTUME_HEAD_TOP,
	EQI_COSTUME_HEAD_MID,
	EQI_COSTUME_HEAD_LOW,
	EQI_COSTUME_GARMENT,
	EQI_AMMO,
	EQI_SHADOW_ARMOR,
	EQI_SHADOW_WEAPON,
	EQI_SHADOW_SHIELD,
	EQI_SHADOW_SHOES,
	EQI_SHADOW_ACC_R,
	EQI_SHADOW_ACC_L,
	EQI_MAX
};

enum job_bonus_type {
	JST_ALL = 0,
	JST_JOB = 1,
	JST_ACCOUNT = 2,
	JST_CHAR = 3
};

enum prevent_logout_trigger {
	PLT_NONE = 0,
	PLT_LOGIN = 1,
	PLT_ATTACK = 2,
	PLT_SKILL = 4,
	PLT_DAMAGE = 8
};

enum e_chkitem_result : uint8 {
	CHKADDITEM_EXIST,
	CHKADDITEM_NEW,
	CHKADDITEM_OVERAMOUNT
};

enum e_additem_result : uint8 {
	ADDITEM_SUCCESS,
	ADDITEM_INVALID,
	ADDITEM_OVERWEIGHT,
	ADDITEM_ITEM,
	ADDITEM_OVERITEM,
	ADDITEM_OVERAMOUNT,
	ADDITEM_REFUSED_TIME,
	ADDITEM_STACKLIMIT
};

#ifndef CAPTCHA_ANSWER_SIZE
	#define CAPTCHA_ANSWER_SIZE 16
#endif
#ifndef CAPTCHA_BMP_SIZE
	#define CAPTCHA_BMP_SIZE (2 + 52 + (3 * 220 * 90)) // sizeof("BM") + sizeof(BITMAPV2INFOHEADER) + 24bits 220x90 BMP
#endif
#ifndef MAX_CAPTCHA_CHUNK_SIZE
	#define MAX_CAPTCHA_CHUNK_SIZE 1024
#endif

struct s_captcha_data {
	uint16 index;
	uint16 image_size;
	char image_data[CAPTCHA_BMP_SIZE];
	char captcha_answer[CAPTCHA_ANSWER_SIZE];
	script_code *bonus_script;

	~s_captcha_data() {
		if (this->bonus_script)
			script_free_code(this->bonus_script);
	}
};

struct s_macro_detect {
	std::shared_ptr<s_captcha_data> cd;
	int32 reporter_aid;
	int32 retry;
	int32 timer;
};

enum e_macro_detect_status : uint8 {
	MCD_TIMEOUT = 0,
	MCD_INCORRECT = 1,
	MCD_GOOD = 2,
};

enum e_macro_report_status : uint8 {
	MCR_MONITORING = 0,
	MCR_NO_DATA = 1,
	MCR_INPROGRESS = 2,
};

class CaptchaDatabase : public TypesafeYamlDatabase<int16, s_captcha_data> {
public:
	CaptchaDatabase() : TypesafeYamlDatabase("CAPTCHA_DB", 1) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef &node) override;
};

extern CaptchaDatabase captcha_db;

struct skill_cooldown_entry {
	unsigned short skill_id;
	int timer;
};

#ifdef VIP_ENABLE
struct vip_info {
	unsigned int enabled : 1;
	time_t time;
	bool disableshowrate; //State to disable clif_display_pinfo(). [Cydh]
};
#endif

enum npc_timeout_type {
	NPCT_INPUT = 0,
	NPCT_MENU  = 1,
	NPCT_WAIT  = 2,
};

/// Enum of Player's Parameter
enum e_params {
	PARAM_STR = 0,
	PARAM_AGI,
	PARAM_VIT,
	PARAM_INT,
	PARAM_DEX,
	PARAM_LUK,
	PARAM_POW,
	PARAM_STA,
	PARAM_WIS,
	PARAM_SPL,
	PARAM_CON,
	PARAM_CRT,
	PARAM_MAX
};

static const char* parameter_names[PARAM_MAX] = {
	"Str",
	"Agi",
	"Vit",
	"Int",
	"Dex",
	"Luk",
	"Pow",
	"Sta",
	"Wis",
	"Spl",
	"Con",
	"Crt"
};

extern unsigned int equip_bitmask[EQI_MAX];

#define equip_index_check(i) ( (i) >= EQI_ACC_L && (i) < EQI_MAX )

/// Miscellaneous item bonus struct
struct s_item_bonus {
	uint16 id;
	int val;
};

/// AddEle bonus struct
struct s_addele2 {
	short flag, rate;
	unsigned char ele;
};

/// AddRace bonus struct
struct s_addrace2 {
	short flag, rate;
	unsigned char race;
};

struct weapon_data {
	int atkmods[SZ_ALL];
	// all the variables except atkmods get zero'ed in each call of status_calc_pc
	// NOTE: if you want to add a non-zeroed variable, you need to update the memset call
	//  in status_calc_pc as well! All the following are automatically zero'ed. [Skotlex]
	int overrefine;
	int star;
	int ignore_def_ele;
	int ignore_def_race;
	int ignore_def_class;
	int def_ratio_atk_ele;
	int def_ratio_atk_race;
	int def_ratio_atk_class;
	int addele[ELE_MAX];
	int addrace[RC_MAX];
	int addclass[CLASS_MAX];
	int addrace2[RC2_MAX];
	int addsize[SZ_MAX];
	short hp_drain_race[RC_MAX];
	short sp_drain_race[RC_MAX];
	short hp_drain_class[CLASS_MAX];
	short sp_drain_class[CLASS_MAX];

	// Stormbreaker
	int mdef_ratio_atk_ele;
	int mdef_ratio_atk_race;
	short hp_attack_ratio[RC_MAX];
	short sp_attack_ratio[RC_MAX];

	struct drain_data {
		short rate; ///< Success rate 10000 = 100%
		short per;  ///< Drain value/rate per attack
	} hp_drain_rate, sp_drain_rate, hp_drain_rate_race[RC_MAX], sp_drain_rate_race[RC_MAX];

	std::vector<s_item_bonus> add_dmg;
	std::vector<s_addele2> addele2;
	std::vector<s_addrace2> addrace3;
};

/// Bonus expansion pack bonus struct
struct s_bonusvalue {
	int value;
};

/// Bonus expansion pack bonus2 struct
struct s_bonusvalue2 {
	int value1;
	int value2; // rate
};

/// Bonus expansion pack bonus3 struct
struct s_bonusvalue3 {
	int value1;
	int value2;
	int value3; // rate
};

/// Bonus expansion pack bonus4 struct
struct s_bonusvalue4 {
	int value1;
	int value2;
	int value3;
	int value4; // rate
};

/// Status bonus entry struct
struct s_statusbonus_entry {
	char* script;
	bool active;
};

/// Status bonus struct
struct s_statusbonus {
	sc_type type;
	std::vector<s_statusbonus_entry> entries;
};

enum e_autospell_flags{
	AUTOSPELL_FORCE_SELF = 0x0,
	AUTOSPELL_FORCE_TARGET = 0x1,
	AUTOSPELL_FORCE_RANDOM_LEVEL = 0x2,
	AUTOSPELL_FORCE_ALL = 0x3
};

/// AutoSpell bonus struct
struct s_autospell {
	uint16 id, lv, trigger_skill;
	short rate, battle_flag;
	t_itemid card_id;
	uint8 flag;
	bool lock;  // bAutoSpellOnSkill: blocks autospell from triggering again, while being executed
};

/// AddEff and AddEff2 bonus struct
struct s_addeffect {
	enum sc_type sc; /// SC type/effect
	int rate; /// Rate
	short arrow_rate; /// Arrow rate
	unsigned char flag; /// Flag
	unsigned int duration; /// Duration the effect applied
};

/// AddEffOnSkill bonus struct
struct s_addeffectonskill {
	enum sc_type sc; /// SC type/effect
	int rate; /// Rate
	short skill_id; /// Skill ID
	unsigned char target; /// Target
	unsigned int duration; /// Duration the effect applied
};

///Struct of add drop item/group rate
struct s_add_drop {
	t_itemid nameid; ///Item ID
	unsigned short group; ///Group ID
	int rate; ///Rate, 1 ~ 10000, -1 ~ -100000
	short race; ///Target Race, bitwise value of 1<<x. if < 0 means Monster ID
	unsigned short class_; ///Target Class, bitwise value of 1<<x
};

struct s_vanish_bonus {
	int16 rate; // 1000 = 100%
	int16 per; // 100 = 100%
	int flag;
};

/// AutoBonus bonus struct
struct s_autobonus {
	short rate;
	uint16 atk_type;
	unsigned int duration;
	char *bonus_script, *other_script;
	int active;
	unsigned int pos;

	~s_autobonus();
};

/// Timed bonus 'bonus_script' struct [Cydh]
struct s_bonus_script_entry {
	struct script_code *script;
	StringBuf *script_buf; //Used for comparing and storing on table
	t_tick tick;
	uint16 flag;
	enum efst_type icon;
	uint8 type; //0 - Ignore; 1 - Buff; 2 - Debuff
	int tid;
};

/// HP/SP bonus struct
struct s_regen {
	short value;
	int rate;
	int tick;
};

/// Item combo struct
struct s_combos {
	script_code *bonus;
	uint32 id;
	uint32 pos;
};

struct s_qi_display {
	bool is_active;
	e_questinfo_types icon;
	e_questinfo_markcolor color;
};

class map_session_data {
public:
	struct block_list bl;
	struct unit_data ud;
	struct view_data vd;
	struct status_data base_status, battle_status;
	struct status_change sc;
	struct regen_data regen;
	struct regen_data_sub sregen, ssregen;
	struct s_autoattack aa;
	//NOTE: When deciding to add a flag to state or special_state, take into consideration that state is preserved in
	//status_calc_pc, while special_state is recalculated in each call. [Skotlex]
	struct s_state {
		unsigned int autoattack : 1;
		unsigned int active : 1; //Marks active player (not active is logging in/out, or changing map servers)
		unsigned int menu_or_input : 1;// if a script is waiting for feedback from the player
		unsigned int dead_sit : 2;
		unsigned int lr_flag : 3;//1: left h. weapon; 2: arrow; 3: shield
		unsigned int connect_new : 1;
		unsigned int arrow_atk : 1;
		unsigned int gangsterparadise : 1;
		unsigned int rest : 1;
		unsigned int storage_flag : 3; //0: closed, 1: Normal Storage open, 2: guild storage open [Skotlex], 3: Premium Storage
		unsigned int snovice_dead_flag : 1; //Explosion spirits on death: 0 off, 1 used.
		unsigned int abra_flag : 2; // Abracadabra bugfix by Aru
		unsigned int autocast : 1; // Autospell flag [Inkfish]
		unsigned int autotrade : 3;	//By Fantik. &2 Requested by vending autotrade; &4 Requested by buyingstore autotrade
		unsigned int showdelay :1;
		unsigned int showexp :1;
		unsigned int showzeny :1;
		unsigned short ltp :1;
		unsigned int noask :1; // [LuzZza]
		unsigned int trading :1; //[Skotlex] is 1 only after a trade has started.
		unsigned int deal_locked :2; //1: Clicked on OK. 2: Clicked on TRADE
		unsigned int size :2; // for tiny/large types
		unsigned int night :1; //Holds whether or not the player currently has the SI_NIGHT effect on. [Skotlex]
		unsigned int using_fake_npc :1;
		unsigned int rewarp :1; //Signals that a player should warp as soon as he is done loading a map. [Skotlex]
		unsigned int killer : 1;
		unsigned int killable : 1;
		unsigned int doridori : 1;
		unsigned int ignoreAll : 1;
		unsigned int debug_remove_map : 1; // temporary state to track double remove_map's [FlavioJS]
		unsigned int buyingstore : 1;
		unsigned int lesseffect : 1;
		unsigned int vending : 1;
		unsigned int noks : 3; // [Zeph Kill Steal Protection]
		unsigned int changemap : 1;
		unsigned int callshop : 1; // flag to indicate that a script used callshop; on a shop
		short pmap; // Previous map on Map Change
		unsigned short autoloot;
		t_itemid autolootid[AUTOLOOTITEM_SIZE]; // [Zephyrus]
		unsigned short autoloottype;
		unsigned int autolooting : 1; //performance-saver, autolooting state for @alootid
		unsigned int gmaster_flag : 1;
		unsigned int prevend : 1;//used to flag wheather you've spent 40sp to open the vending or not.
		unsigned int warping : 1;//states whether you're in the middle of a warp processing
		unsigned int permanent_speed : 1; // When 1, speed cannot be changed through status_calc_pc().
		bool hold_recalc;
		unsigned int banking : 1; //1 when we using the banking system 0 when closed
		unsigned int hpmeter_visible : 1;
		unsigned disable_atcommand_on_npc : 1; //Prevent to use atcommand while talking with NPC [Kichi]
		uint8 isBoundTrading; // Player is currently add bound item to trade list [Cydh]
		bool ignoretimeout; // Prevent the SECURE_NPCTIMEOUT function from closing current script.
		unsigned int workinprogress : 2; // See clif.hpp::e_workinprogress
		bool pc_loaded; // Ensure inventory data and status data is loaded before we calculate player stats
		bool keepshop; // Whether shop data should be removed when the player disconnects
		bool mail_writing; // Whether the player is currently writing a mail in RODEX or not
		bool cashshop_open;
		bool sale_open;
		bool stylist_open;
		bool barter_open;
		bool barter_extended_open;
		bool enchantgrade_open; // Whether the enchantgrade window is open or not
		unsigned int block_action : 10;

		// Stormbreaker
		bool inventory_select; // Whether the player has the inventory select screen open
		bool skill_select; // Whether the player has the skill select screen open

		bool refineui_open;
		t_itemid inventory_expansion_confirmation;
		uint16 inventory_expansion_amount;
		t_itemid laphine_synthesis;
		t_itemid laphine_upgrade;
		bool roulette_open;
		t_itemid item_reform;
		uint64 item_enchant_index;
	} state;
	struct {
		unsigned char no_weapon_damage, no_magic_damage, no_misc_damage;
		unsigned int restart_full_recover : 1;
		unsigned int no_castcancel : 1;
		unsigned int no_castcancel2 : 1;
		unsigned int no_sizefix : 1;
		unsigned int no_gemstone : 2;
		unsigned int intravision : 1; // Maya Purple Card effect [DracoRPG]
		unsigned int perfect_hiding : 1; // [Valaris]
		unsigned int no_knockback : 1;
		unsigned int bonus_coma : 1;
		unsigned int no_mado_fuel : 1; // Disable Magic_Gear_Fuel consumption [Secret]
		unsigned int no_walk_delay : 1;

		// <Epoque>
		unsigned int keep_buffs : 1;
		unsigned int no_chat : 1;
		unsigned int snap : 1;
		unsigned int zeny_attack;
		unsigned int skill_hp : 1;
		unsigned int no_item : 1;
		unsigned int no_skill : 1;
		unsigned int no_walk : 1;
		unsigned int undetectable : 1;
		unsigned int item_hptosp : 1;
		unsigned int item_sptohp : 1;
		unsigned int zeny_cost : 1;
		unsigned int hp_cost : 1;
	} special_state;
	uint32 login_id1, login_id2;
	uint64 class_;	//This is the internal job ID used by the map server to simplify comparisons/queries/etc. [Skotlex]
	int group_id;
	std::shared_ptr<s_player_group> group;
	std::bitset<PC_PERM_MAX> permissions; // group permissions have to be copied, because they might be adjusted by atcommand addperm
	int count_rewarp; //count how many time we being rewarped

	int langtype;
	struct mmo_charstatus status;

	// Item Storages
	struct s_storage storage, premiumStorage;
	struct s_storage inventory;
	struct s_storage cart;

	struct item_data* inventory_data[MAX_INVENTORY]; // direct pointers to itemdb entries (faster than doing item_id lookups)
	short equip_index[EQI_MAX];
	short equip_switch_index[EQI_MAX];
	unsigned int weight,max_weight,add_max_weight;
	int cart_weight,cart_num,cart_weight_max;
	int fd;
	unsigned short mapindex;
	unsigned char head_dir; //0: Look forward. 1: Look right, 2: Look left.
	t_tick client_tick;
	int npc_id,npc_shopid; //for script follow scriptoid;   ,npcid
	std::vector<int> npc_id_dynamic;
	std::vector<int> areanpc, npc_ontouch_;	///< Array of OnTouch and OnTouch_ NPC ID
	int npc_item_flag; //Marks the npc_id with which you can use items during interactions with said npc (see script command enable_itemuse)
	int npc_menu; // internal variable, used in npc menu handling
	int npc_amount;
	struct script_state *st;
	char npc_str[CHATBOX_SIZE]; // for passing npc input box text to script engine
	int npc_timer_id; //For player attached npc timers. [Skotlex]
	unsigned int chatID;
	time_t idletime;
	time_t idletime_hom;
	time_t idletime_mer;

	struct s_progressbar {
		int npc_id;
		t_tick timeout;
	} progressbar; //Progress Bar [Inkfish]

	struct s_ignore {
		char name[NAME_LENGTH];
	} ignore[MAX_IGNORE_LIST];

	int followtimer; // [MouseJstr]
	int followtarget;

	time_t emotionlasttime; // to limit flood with emotion packets

	short skillitem,skillitemlv;
	bool skillitem_keep_requirement;
	uint16 skill_id_old,skill_lv_old;
	uint16 skill_id_dance,skill_lv_dance;
	uint16 skill_id_song, skill_lv_song;
	short cook_mastery; // range: [0,1999] [Inkfish]
	struct skill_cooldown_entry * scd[MAX_SKILLCOOLDOWN]; // Skill Cooldown
	uint16 cloneskill_idx, ///Stores index of copied skill by Intimidate/Plagiarism
		reproduceskill_idx; ///Stores index of copied skill by Reproduce
	int menuskill_id, menuskill_val, menuskill_val2;

	int invincible_timer;
	t_tick canlog_tick;
	t_tick canuseitem_tick;	// [Skotlex]
	t_tick canusecashfood_tick;
	t_tick canequip_tick;	// [Inkfish]
	t_tick cantalk_tick;
	t_tick canskill_tick; // used to prevent abuse from no-delay ACT files
	t_tick cansendmail_tick; // [Mail System Flood Protection]
	t_tick ks_floodprotect_tick; // [Kill Steal Protection]
	t_tick equipswitch_tick; // Equip switch

//=========================================================================================
// [keitenai] Spam Hack Protection
//=========================================================================================
		unsigned int k_tick_c = 0;
		t_tick kdelay = 0;
		t_tick spamtick_DEFAULT = 0;
		t_tick spamtick_MO_RELOCDELAY = 0;
		t_tick spamtick_SM_BASH = 0;
		t_tick spamtick_SM_MAGNUM = 0;
		t_tick spamtick_MG_NAPALMBEAT = 0;
		t_tick spamtick_MG_SOULSTRIKE = 0;
		t_tick spamtick_MG_COLDBOLT = 0;
		t_tick spamtick_MG_FROSTDIVER = 0;
		t_tick spamtick_MG_STONECURSE = 0;
		t_tick spamtick_MG_FIREBALL = 0;
		t_tick spamtick_MG_FIREWALL = 0;
		t_tick spamtick_MG_FIREBOLT = 0;
		t_tick spamtick_MG_LIGHTNINGBOLT = 0;
		t_tick spamtick_MG_THUNDERSTORM = 0;
		t_tick spamtick_AL_HEAL = 0;
		t_tick spamtick_AL_DECAGI = 0;
		t_tick spamtick_AL_CRUCIS = 0;
		t_tick spamtick_MC_MAMMONITE = 0;
		t_tick spamtick_AC_DOUBLE = 0;
		t_tick spamtick_AC_SHOWER = 0;
		t_tick spamtick_TF_POISON = 0;
		t_tick spamtick_KN_PIERCE = 0;
		t_tick spamtick_KN_BRANDISHSPEAR = 0;
		t_tick spamtick_KN_SPEARSTAB = 0;
		t_tick spamtick_KN_SPEARBOOMERANG = 0;
		t_tick spamtick_KN_BOWLINGBASH = 0;
		t_tick spamtick_PR_LEXDIVINA = 0;
		t_tick spamtick_PR_TURNUNDEAD = 0;
		t_tick spamtick_PR_LEXAETERNA = 0;
		t_tick spamtick_PR_MAGNUS = 0;
		t_tick spamtick_WZ_FIREPILLAR = 0;
		t_tick spamtick_WZ_SIGHTRASHER = 0;
		t_tick spamtick_WZ_FIREIVY = 0;
		t_tick spamtick_WZ_METEOR = 0;
		t_tick spamtick_WZ_JUPITEL = 0;
		t_tick spamtick_WZ_VERMILION = 0;
		t_tick spamtick_WZ_WATERBALL = 0;
		t_tick spamtick_WZ_ICEWALL = 0;
		t_tick spamtick_WZ_FROSTNOVA = 0;
		t_tick spamtick_WZ_STORMGUST = 0;
		t_tick spamtick_WZ_EARTHSPIKE = 0;
		t_tick spamtick_WZ_HEAVENDRIVE = 0;
		t_tick spamtick_WZ_QUAGMIRE = 0;
		t_tick spamtick_WZ_ESTIMATION = 0;
		t_tick spamtick_BS_HAMMERFALL = 0;
		t_tick spamtick_HT_BLITZBEAT = 0;
		t_tick spamtick_AS_SONICBLOW = 0;
		t_tick spamtick_AS_GRIMTOOTH = 0;
		t_tick spamtick_AC_CHARGEARROW = 0;
		t_tick spamtick_TF_BACKSLIDING = 0;
		t_tick spamtick_MC_CARTREVOLUTION = 0;
		t_tick spamtick_AL_HOLYLIGHT = 0;
		t_tick spamtick_RG_BACKSTAP = 0;
		t_tick spamtick_RG_RAID = 0;
		t_tick spamtick_RG_GRAFFITI = 0;
		t_tick spamtick_RG_FLAGGRAFFITI = 0;
		t_tick spamtick_RG_COMPULSION = 0;
		t_tick spamtick_RG_PLAGIARISM = 0;
		t_tick spamtick_AM_DEMONSTRATION = 0;
		t_tick spamtick_AM_ACIDTERROR = 0;
		t_tick spamtick_AM_POTIONPITCHER = 0;
		t_tick spamtick_AM_CANNIBALIZE = 0;
		t_tick spamtick_AM_SPHEREMINE = 0;
		t_tick spamtick_AM_FLAMECONTROL = 0;
		t_tick spamtick_AM_DRILLMASTER = 0;
		t_tick spamtick_CR_SHIELDBOOMERANG = 0;
		t_tick spamtick_CR_HOLYCROSS = 0;
		t_tick spamtick_CR_GRANDCROSS = 0;
		t_tick spamtick_MO_CALLSPIRITS = 0;
		t_tick spamtick_MO_ABSORBSPIRITS = 0;
		t_tick spamtick_MO_BODYRELOCATION = 0;
		t_tick spamtick_MO_INVESTIGATE = 0;
		t_tick spamtick_MO_FINGEROFFENSIVE = 0;
		t_tick spamtick_MO_EXPLOSIONSPIRITS = 0;
		t_tick spamtick_MO_EXTREMITYFIST = 0;
		t_tick spamtick_MO_CHAINCOMBO = 0;
		t_tick spamtick_MO_COMBOFINISH = 0;
		t_tick spamtick_SA_CASTCANCEL = 0;
		t_tick spamtick_SA_SPELLBREAKER = 0;
		t_tick spamtick_SA_DISPELL = 0;
		t_tick spamtick_SA_ABRACADABRA = 0;
		t_tick spamtick_SA_MONOCELL = 0;
		t_tick spamtick_SA_CLASSCHANGE = 0;
		t_tick spamtick_SA_SUMMONMONSTER = 0;
		t_tick spamtick_SA_REVERSEORCISH = 0;
		t_tick spamtick_SA_DEATH = 0;
		t_tick spamtick_SA_FORTUNE = 0;
		t_tick spamtick_SA_TAMINGMONSTER = 0;
		t_tick spamtick_SA_QUESTION = 0;
		t_tick spamtick_SA_GRAVITY = 0;
		t_tick spamtick_SA_LEVELUP = 0;
		t_tick spamtick_SA_INSTANTDEATH = 0;
		t_tick spamtick_SA_FULLRECOVERY = 0;
		t_tick spamtick_SA_COMA = 0;
		t_tick spamtick_BD_ADAPTATION = 0;
		t_tick spamtick_BD_ENCORE = 0;
		t_tick spamtick_BD_LULLABY = 0;
		t_tick spamtick_BD_RICHMANKIM = 0;
		t_tick spamtick_BA_MUSICALSTRIKE = 0;
		t_tick spamtick_BA_DISSONANCE = 0;
		t_tick spamtick_BA_FROSTJOKER = 0;
		t_tick spamtick_BA_WHISTLE = 0;
		t_tick spamtick_BA_ASSASSINCROSS = 0;
		t_tick spamtick_BA_POEMBRAGI = 0;
		t_tick spamtick_BA_APPLEIDUN = 0;
		t_tick spamtick_DC_THROWARROW = 0;
		t_tick spamtick_DC_UGLYDANCE = 0;
		t_tick spamtick_DC_SCREAM = 0;
		t_tick spamtick_DC_HUMMING = 0;
		t_tick spamtick_DC_DONTFORGETME = 0;
		t_tick spamtick_DC_FORTUNEKISS = 0;
		t_tick spamtick_DC_SERVICEFORYOU = 0;
		t_tick spamtick_LK_FURY = 0;
		t_tick spamtick_HW_MAGICCRASHER = 0;
		t_tick spamtick_PA_PRESSURE = 0;
		t_tick spamtick_CH_PALMSTRIKE = 0;
		t_tick spamtick_CH_TIGERFIST = 0;
		t_tick spamtick_CH_CHAINCRUSH = 0;
		t_tick spamtick_PF_SOULCHANGE = 0;
		t_tick spamtick_PF_SOULBURN = 0;
		t_tick spamtick_ASC_BREAKER = 0;
		t_tick spamtick_SN_FALCONASSAULT = 0;
		t_tick spamtick_SN_SHARPSHOOTING = 0;
		t_tick spamtick_CR_ALCHEMY = 0;
		t_tick spamtick_CR_SYNTHESISPOTION = 0;
		t_tick spamtick_CG_ARROWVULCAN = 0;
		t_tick spamtick_CG_MOONLIT = 0;
		t_tick spamtick_CG_MARIONETTE = 0;
		t_tick spamtick_LK_SPIRALPIERCE = 0;
		t_tick spamtick_LK_HEADCRUSH = 0;
		t_tick spamtick_LK_JOINTBEAT = 0;
		t_tick spamtick_HW_NAPALMVULCAN = 0;
		t_tick spamtick_CH_SOULCOLLECT = 0;
		t_tick spamtick_PF_MINDBREAKER = 0;
		t_tick spamtick_PF_SPIDERWEB = 0;
		t_tick spamtick_ASC_METEORASSAULT = 0;
		t_tick spamtick_TK_STORMKICK = 0;
		t_tick spamtick_TK_DOWNKICK = 0;
		t_tick spamtick_TK_TURNKICK = 0;
		t_tick spamtick_TK_JUMPKICK = 0;
		t_tick spamtick_TK_POWER = 0;
		t_tick spamtick_TK_HIGHJUMP = 0;
		t_tick spamtick_SL_KAIZEL = 0;
		t_tick spamtick_SL_KAAHI = 0;
		t_tick spamtick_SL_KAUPE = 0;
		t_tick spamtick_SL_KAITE = 0;
		t_tick spamtick_SL_KAINA = 0;
		t_tick spamtick_SL_STIN = 0;
		t_tick spamtick_SL_STUN = 0;
		t_tick spamtick_SL_SMA = 0;
		t_tick spamtick_SL_SWOO = 0;
		t_tick spamtick_SL_SKE = 0;
		t_tick spamtick_SL_SKA = 0;
		t_tick spamtick_ST_FULLSTRIP = 0;
		t_tick spamtick_WS_WEAPONREFINE = 0;
		t_tick spamtick_CR_SLIMPITCHER = 0;
		t_tick spamtick_CR_FULLPROTECTION = 0;
		t_tick spamtick_PA_SHIELDCHAIN = 0;
		t_tick spamtick_HP_MANARECHARGE = 0;
		t_tick spamtick_PF_DOUBLECASTING = 0;
		t_tick spamtick_HW_GANBANTEIN = 0;
		t_tick spamtick_HW_GRAVITATION = 0;
		t_tick spamtick_WS_CARTTERMINATION = 0;
		t_tick spamtick_CG_HERMODE = 0;
		t_tick spamtick_CG_TAROTCARD = 0;
		t_tick spamtick_CR_ACIDDEMONSTRATION = 0;
		t_tick spamtick_SL_HIGH = 0;
		t_tick spamtick_GS_TRIPLEACTION = 0;
		t_tick spamtick_GS_BULLSEYE = 0;
		t_tick spamtick_GS_MADNESSCANCEL = 0;
		t_tick spamtick_GS_INCREASING = 0;
		t_tick spamtick_GS_MAGICALBULLET = 0;
		t_tick spamtick_GS_CRACKER = 0;
		t_tick spamtick_GS_SINGLEACTION = 0;
		t_tick spamtick_GS_CHAINACTION = 0;
		t_tick spamtick_GS_TRACKING = 0;
		t_tick spamtick_GS_DISARM = 0;
		t_tick spamtick_GS_PIERCINGSHOT = 0;
		t_tick spamtick_GS_RAPIDSHOWER = 0;
		t_tick spamtick_GS_DESPERADO = 0;
		t_tick spamtick_GS_GATLINGFEVER = 0;
		t_tick spamtick_GS_DUST = 0;
		t_tick spamtick_GS_FULLBUSTER = 0;
		t_tick spamtick_GS_SPREADATTACK = 0;
		t_tick spamtick_GS_GROUNDDRIFT = 0;
		t_tick spamtick_NJ_TOBIDOUGU = 0;
		t_tick spamtick_NJ_SYURIKEN = 0;
		t_tick spamtick_NJ_KUNAI = 0;
		t_tick spamtick_NJ_HUUMA = 0;
		t_tick spamtick_NJ_ZENYNAGE = 0;
		t_tick spamtick_NJ_TATAMIGAESHI = 0;
		t_tick spamtick_NJ_KASUMIKIRI = 0;
		t_tick spamtick_NJ_SHADOWJUMP = 0;
		t_tick spamtick_NJ_KIRIKAGE = 0;
		t_tick spamtick_NJ_UTSUSEMI = 0;
		t_tick spamtick_NJ_BUNSINJYUTSU = 0;
		t_tick spamtick_NJ_NINPOU = 0;
		t_tick spamtick_NJ_KOUENKA = 0;
		t_tick spamtick_NJ_KAENSIN = 0;
		t_tick spamtick_NJ_BAKUENRYU = 0;
		t_tick spamtick_NJ_HYOUSENSOU = 0;
		t_tick spamtick_NJ_SUITON = 0;
		t_tick spamtick_NJ_HYOUSYOURAKU = 0;
		t_tick spamtick_NJ_HUUJIN = 0;
		t_tick spamtick_NJ_RAIGEKISAI = 0;
		t_tick spamtick_NJ_KAMAITACHI = 0;
		t_tick spamtick_NJ_NEN = 0;
		t_tick spamtick_NJ_ISSEN = 0;
		t_tick spamtick_KN_CHARGEATK = 0;
		t_tick spamtick_AS_VENOMKNIFE = 0;
		t_tick spamtick_RG_CLOSECONFINE = 0;
		t_tick spamtick_WZ_SIGHTBLASTER = 0;
		t_tick spamtick_HT_PHANTASMIC = 0;
		t_tick spamtick_BA_PANGVOICE = 0;
		t_tick spamtick_DC_WINKCHARM = 0;
		t_tick spamtick_PR_REDEMPTIO = 0;
		t_tick spamtick_MO_KITRANSLATION = 0;
		t_tick spamtick_MO_BALKYOUNG = 0;
		t_tick spamtick_RK_SONICWAVE = 0;
		t_tick spamtick_RK_DEATHBOUND = 0;
		t_tick spamtick_RK_HUNDREDSPEAR = 0;
		t_tick spamtick_RK_WINDCUTTER = 0;
		t_tick spamtick_RK_IGNITIONBREAK = 0;
		t_tick spamtick_RK_DRAGONBREATH = 0;
		t_tick spamtick_RK_CRUSHSTRIKE = 0;
		t_tick spamtick_RK_STORMBLAST = 0;
		t_tick spamtick_RK_PHANTOMTHRUST = 0;
		t_tick spamtick_GC_CROSSIMPACT = 0;
		t_tick spamtick_GC_WEAPONCRUSH = 0;
		t_tick spamtick_GC_ROLLINGCUTTER = 0;
		t_tick spamtick_GC_CROSSRIPPERSLASHER = 0;
		t_tick spamtick_AB_JUDEX = 0;
		t_tick spamtick_AB_ADORAMUS = 0;
		t_tick spamtick_AB_CHEAL = 0;
		t_tick spamtick_AB_EPICLESIS = 0;
		t_tick spamtick_AB_PRAEFATIO = 0;
		t_tick spamtick_AB_EUCHARISTICA = 0;
		t_tick spamtick_AB_RENOVATIO = 0;
		t_tick spamtick_AB_HIGHNESSHEAL = 0;
		t_tick spamtick_AB_CLEARANCE = 0;
		t_tick spamtick_AB_EXPIATIO = 0;
		t_tick spamtick_AB_DUPLELIGHT = 0;
		t_tick spamtick_AB_DUPLELIGHT_MELEE = 0;
		t_tick spamtick_AB_DUPLELIGHT_MAGIC = 0;
		t_tick spamtick_AB_SILENTIUM = 0;
		t_tick spamtick_WL_WHITEIMPRISON = 0;
		t_tick spamtick_WL_SOULEXPANSION = 0;
		t_tick spamtick_WL_FROSTMISTY = 0;
		t_tick spamtick_WL_JACKFROST = 0;
		t_tick spamtick_WL_MARSHOFABYSS = 0;
		t_tick spamtick_WL_RADIUS = 0;
		t_tick spamtick_WL_STASIS = 0;
		t_tick spamtick_WL_DRAINLIFE = 0;
		t_tick spamtick_WL_CRIMSONROCK = 0;
		t_tick spamtick_WL_HELLINFERNO = 0;
		t_tick spamtick_WL_COMET = 0;
		t_tick spamtick_WL_CHAINLIGHTNING = 0;
		t_tick spamtick_WL_CHAINLIGHTNING_ATK = 0;
		t_tick spamtick_WL_EARTHSTRAIN = 0;
		t_tick spamtick_WL_TETRAVORTEX = 0;
		t_tick spamtick_WL_TETRAVORTEX_FIRE = 0;
		t_tick spamtick_WL_TETRAVORTEX_WATER = 0;
		t_tick spamtick_WL_TETRAVORTEX_WIND = 0;
		t_tick spamtick_WL_TETRAVORTEX_GROUND = 0;
		t_tick spamtick_WL_RELEASE = 0;
		t_tick spamtick_WL_READING_SB = 0;
		t_tick spamtick_WL_FREEZE_SP = 0;
		t_tick spamtick_RA_ARROWSTORM = 0;
		t_tick spamtick_RA_AIMEDBOLT = 0;
		t_tick spamtick_RA_WUGSTRIKE = 0;
		t_tick spamtick_RA_WUGBITE = 0;
		t_tick spamtick_NC_BOOSTKNUCKLE = 0;
		t_tick spamtick_NC_PILEBUNKER = 0;
		t_tick spamtick_NC_VULCANARM = 0;
		t_tick spamtick_NC_FLAMELAUNCHER = 0;
		t_tick spamtick_NC_COLDSLOWER = 0;
		t_tick spamtick_NC_ARMSCANNON = 0;
		t_tick spamtick_NC_ACCELERATION = 0;
		t_tick spamtick_NC_F_SIDESLIDE = 0;
		t_tick spamtick_NC_B_SIDESLIDE = 0;
		t_tick spamtick_NC_MAINFRAME = 0;
		t_tick spamtick_NC_SHAPESHIFT = 0;
		t_tick spamtick_NC_INFRAREDSCAN = 0;
		t_tick spamtick_NC_ANALYZE = 0;
		t_tick spamtick_NC_MAGNETICFIELD = 0;
		t_tick spamtick_NC_NEUTRALBARRIER = 0;
		t_tick spamtick_NC_STEALTHFIELD = 0;
		t_tick spamtick_NC_AXEBOOMERANG = 0;
		t_tick spamtick_NC_POWERSWING = 0;
		t_tick spamtick_NC_AXETORNADO = 0;
		t_tick spamtick_NC_SILVERSNIPER = 0;
		t_tick spamtick_NC_MAGICDECOY = 0;
		t_tick spamtick_NC_DISJOINT = 0;
		t_tick spamtick_SC_FATALMENACE = 0;
		t_tick spamtick_SC_TRIANGLESHOT = 0;
		t_tick spamtick_SC_INVISIBILITY = 0;
		t_tick spamtick_SC_ENERVATION = 0;
		t_tick spamtick_SC_GROOMY = 0;
		t_tick spamtick_SC_IGNORANCE = 0;
		t_tick spamtick_SC_LAZINESS = 0;
		t_tick spamtick_SC_UNLUCKY = 0;
		t_tick spamtick_SC_WEAKNESS = 0;
		t_tick spamtick_SC_STRIPACCESSARY = 0;
		t_tick spamtick_SC_MANHOLE = 0;
		t_tick spamtick_SC_DIMENSIONDOOR = 0;
		t_tick spamtick_SC_CHAOSPANIC = 0;
		t_tick spamtick_SC_MAELSTROM = 0;
		t_tick spamtick_SC_BLOODYLUST = 0;
		t_tick spamtick_SC_FEINTBOMB = 0;
		t_tick spamtick_LG_CANNONSPEAR = 0;
		t_tick spamtick_LG_BANISHINGPOINT = 0;
		t_tick spamtick_LG_TRAMPLE = 0;
		t_tick spamtick_LG_PINPOINTATTACK = 0;
		t_tick spamtick_LG_RAGEBURST = 0;
		t_tick spamtick_LG_EXEEDBREAK = 0;
		t_tick spamtick_LG_OVERBRAND = 0;
		t_tick spamtick_LG_BANDING = 0;
		t_tick spamtick_LG_MOONSLASHER = 0;
		t_tick spamtick_LG_RAYOFGENESIS = 0;
		t_tick spamtick_LG_PIETY = 0;
		t_tick spamtick_LG_EARTHDRIVE = 0;
		t_tick spamtick_LG_HESPERUSLIT = 0;
		t_tick spamtick_SR_DRAGONCOMBO = 0;
		t_tick spamtick_SR_SKYNETBLOW = 0;
		t_tick spamtick_SR_EARTHSHAKER = 0;
		t_tick spamtick_SR_FALLENEMPIRE = 0;
		t_tick spamtick_SR_TIGERCANNON = 0;
		t_tick spamtick_SR_HELLGATE = 0;
		t_tick spamtick_SR_RAMPAGEBLASTER = 0;
		t_tick spamtick_SR_CRESCENTELBOW = 0;
		t_tick spamtick_SR_CURSEDCIRCLE = 0;
		t_tick spamtick_SR_LIGHTNINGWALK = 0;
		t_tick spamtick_SR_KNUCKLEARROW = 0;
		t_tick spamtick_SR_WINDMILL = 0;
		t_tick spamtick_SR_RAISINGDRAGON = 0;
		t_tick spamtick_SR_GENTLETOUCH = 0;
		t_tick spamtick_SR_ASSIMILATEPOWER = 0;
		t_tick spamtick_SR_POWERVELOCITY = 0;
		t_tick spamtick_SR_CRESCENTELBOW_AUTOSPELL = 0;
		t_tick spamtick_SR_GATEOFHELL = 0;
		t_tick spamtick_SR_GENTLETOUCH_QUIET = 0;
		t_tick spamtick_SR_GENTLETOUCH_CURE = 0;
		t_tick spamtick_SR_GENTLETOUCH_ENERGYGAIN = 0;
		t_tick spamtick_SR_GENTLETOUCH_CHANGE = 0;
		t_tick spamtick_SR_GENTLETOUCH_REVITALIZE = 0;
		t_tick spamtick_WA_SWING_DANCE = 0;
		t_tick spamtick_WA_SYMPHONY_OF_LOVER = 0;
		t_tick spamtick_WA_MOONLIT_SERENADE = 0;
		t_tick spamtick_MI_RUSH_WINDMILL = 0;
		t_tick spamtick_MI_ECHOSONG = 0;
		t_tick spamtick_MI_HARMONIZE = 0;
		t_tick spamtick_WM_LESSON = 0;
		t_tick spamtick_WM_METALICSOUND = 0;
		t_tick spamtick_WM_REVERBERATION = 0;
		t_tick spamtick_WM_REVERBERATION_MELEE = 0;
		t_tick spamtick_WM_REVERBERATION_MAGIC = 0;
		t_tick spamtick_WM_DOMINION_IMPULSE = 0;
		t_tick spamtick_WM_SEVERE_RAINSTORM = 0;
		t_tick spamtick_WM_SEVERE_RAINSTORM_MELEE = 0;
		t_tick spamtick_WM_POEMOFNETHERWORLD = 0;
		t_tick spamtick_WM_VOICEOFSIREN = 0;
		t_tick spamtick_WM_DEADHILLHERE = 0;
		t_tick spamtick_WM_LULLABY_DEEPSLEEP = 0;
		t_tick spamtick_WM_SIRCLEOFNATURE = 0;
		t_tick spamtick_WM_RANDOMIZESPELL = 0;
		t_tick spamtick_WM_GLOOMYDAY = 0;
		t_tick spamtick_WM_GREAT_ECHO = 0;
		t_tick spamtick_WM_SONG_OF_MANA = 0;
		t_tick spamtick_WM_DANCE_WITH_WUG = 0;
		t_tick spamtick_WM_SOUND_OF_DESTRUCTION = 0;
		t_tick spamtick_WM_SATURDAY_NIGHT_FEVER = 0;
		t_tick spamtick_WM_LERADS_DEW = 0;
		t_tick spamtick_WM_MELODYOFSINK = 0;
		t_tick spamtick_WM_BEYOND_OF_WARCRY = 0;
		t_tick spamtick_WM_UNLIMITED_HUMMING_VOICE = 0;
		t_tick spamtick_SO_FIREWALK = 0;
		t_tick spamtick_SO_ELECTRICWALK = 0;
		t_tick spamtick_SO_SPELLFIST = 0;
		t_tick spamtick_SO_EARTHGRAVE = 0;
		t_tick spamtick_SO_DIAMONDDUST = 0;
		t_tick spamtick_SO_POISON_BUSTER = 0;
		t_tick spamtick_SO_PSYCHIC_WAVE = 0;
		t_tick spamtick_SO_CLOUD_KILL = 0;
		t_tick spamtick_SO_STRIKING = 0;
		t_tick spamtick_SO_WARMER = 0;
		t_tick spamtick_SO_VACUUM_EXTREME = 0;
		t_tick spamtick_SO_VARETYR_SPEAR = 0;
		t_tick spamtick_SO_ARRULLO = 0;
		t_tick spamtick_SO_EL_CONTROL = 0;
		t_tick spamtick_SO_EL_ACTION = 0;
		t_tick spamtick_SO_EL_ANALYSIS = 0;
		t_tick spamtick_SO_EL_SYMPATHY = 0;
		t_tick spamtick_SO_EL_CURE = 0;
		t_tick spamtick_GN_CART_TORNADO = 0;
		t_tick spamtick_GN_CARTCANNON = 0;
		t_tick spamtick_GN_THORNS_TRAP = 0;
		t_tick spamtick_GN_BLOOD_SUCKER = 0;
		t_tick spamtick_GN_SPORE_EXPLOSION = 0;
		t_tick spamtick_GN_WALLOFTHORN = 0;
		t_tick spamtick_GN_CRAZYWEED = 0;
		t_tick spamtick_GN_CRAZYWEED_ATK = 0;
		t_tick spamtick_GN_DEMONIC_FIRE = 0;
		t_tick spamtick_GN_FIRE_EXPANSION = 0;
		t_tick spamtick_GN_FIRE_EXPANSION_SMOKE_POWDER = 0;
		t_tick spamtick_GN_FIRE_EXPANSION_TEAR_GAS = 0;
		t_tick spamtick_GN_FIRE_EXPANSION_ACID = 0;
		t_tick spamtick_GN_HELLS_PLANT = 0;
		t_tick spamtick_GN_HELLS_PLANT_ATK = 0;
		t_tick spamtick_GN_MANDRAGORA = 0;
		t_tick spamtick_GN_SLINGITEM = 0;
		t_tick spamtick_GN_SLINGITEM_RANGEMELEEATK = 0;
		t_tick spamtick_GN_CHANGEMATERIAL = 0;
		t_tick spamtick_AB_SECRAMENT = 0;
		t_tick spamtick_SR_HOWLINGOFLION = 0;
		t_tick spamtick_SR_RIDEINLIGHTNING = 0;
		t_tick spamtick_LG_OVERBRAND_BRANDISH = 0;
		t_tick spamtick_LG_OVERBRAND_PLUSATK = 0;
		t_tick spamtick_RL_GLITTERING_GREED = 0;
		t_tick spamtick_RL_RICHS_COIN = 0;
		t_tick spamtick_RL_MASS_SPIRAL = 0;
		t_tick spamtick_RL_BANISHING_BUSTER = 0;
		t_tick spamtick_RL_B_TRAP = 0;
		t_tick spamtick_RL_S_STORM = 0;
		t_tick spamtick_RL_E_CHAIN = 0;
		t_tick spamtick_RL_QD_SHOT = 0;
		t_tick spamtick_RL_C_MARKER = 0;
		t_tick spamtick_RL_FIREDANCE = 0;
		t_tick spamtick_RL_H_MINE = 0;
		t_tick spamtick_RL_P_ALTER = 0;
		t_tick spamtick_RL_FALLEN_ANGEL = 0;
		t_tick spamtick_RL_R_TRIP = 0;
		t_tick spamtick_RL_D_TAIL = 0;
		t_tick spamtick_RL_FIRE_RAIN = 0;
		t_tick spamtick_RL_HEAT_BARREL = 0;
		t_tick spamtick_RL_AM_BLAST = 0;
		t_tick spamtick_RL_SLUGSHOT = 0;
		t_tick spamtick_RL_HAMMER_OF_GOD = 0;
		t_tick spamtick_RL_R_TRIP_PLUSATK = 0;
		t_tick spamtick_RL_B_FLICKER_ATK = 0;
		t_tick spamtick_KO_YAMIKUMO = 0;
		t_tick spamtick_KO_JYUMONJIKIRI = 0;
		t_tick spamtick_KO_SETSUDAN = 0;
		t_tick spamtick_KO_BAKURETSU = 0;
		t_tick spamtick_KO_HAPPOKUNAI = 0;
		t_tick spamtick_KO_MUCHANAGE = 0;
		t_tick spamtick_KO_HUUMARANKA = 0;
		t_tick spamtick_KO_MAKIBISHI = 0;
		t_tick spamtick_KO_MEIKYOUSISUI = 0;
		t_tick spamtick_KO_ZANZOU = 0;
		t_tick spamtick_KO_KYOUGAKU = 0;
		t_tick spamtick_KO_JYUSATSU = 0;
		t_tick spamtick_KO_KAHU_ENTEN = 0;
		t_tick spamtick_KO_HYOUHU_HUBUKI = 0;
		t_tick spamtick_KO_KAZEHU_SEIRAN = 0;
		t_tick spamtick_KO_DOHU_KOUKAI = 0;
		t_tick spamtick_KO_KAIHOU = 0;
		t_tick spamtick_KO_ZENKAI = 0;
		t_tick spamtick_KO_GENWAKU = 0;
		t_tick spamtick_KO_IZAYOI = 0;
		t_tick spamtick_KG_KAGEHUMI = 0;
		t_tick spamtick_KG_KYOMU = 0;
		t_tick spamtick_KG_KAGEMUSYA = 0;
		t_tick spamtick_OB_ZANGETSU = 0;
		t_tick spamtick_OB_OBOROGENSOU = 0;
		t_tick spamtick_OB_OBOROGENSOU_TRANSITION_ATK = 0;
		t_tick spamtick_OB_AKAITSUKI = 0;
		t_tick spamtick_GC_DARKCROW = 0;
		t_tick spamtick_RA_UNLIMIT = 0;
		t_tick spamtick_GN_ILLUSIONDOPING = 0;
		t_tick spamtick_RK_DRAGONBREATH_WATER = 0;
		t_tick spamtick_RK_LUXANIMA = 0;
		t_tick spamtick_NC_MAGMA_ERUPTION = 0;
		t_tick spamtick_WM_FRIGG_SONG = 0;
		t_tick spamtick_SO_ELEMENTAL_SHIELD = 0;
		t_tick spamtick_SR_FLASHCOMBO = 0;
		t_tick spamtick_SC_ESCAPE = 0;
		t_tick spamtick_AB_OFFERTORIUM = 0;
		t_tick spamtick_WL_TELEKINESIS_INTENSE = 0;
		t_tick spamtick_ALL_FULL_THROTTLE = 0;
		t_tick spamtick_SU_BITE = 0;
		t_tick spamtick_SU_SCRATCH = 0;
		t_tick spamtick_SU_STOOP = 0;
		t_tick spamtick_SU_LOPE = 0;
		t_tick spamtick_SU_SPRITEMABLE = 0;
		t_tick spamtick_SU_POWEROFLAND = 0;
		t_tick spamtick_SU_SV_STEMSPEAR = 0;
		t_tick spamtick_SU_CN_POWDERING = 0;
		t_tick spamtick_SU_CN_METEOR = 0;
		t_tick spamtick_SU_SV_ROOTTWIST = 0;
		t_tick spamtick_SU_SV_ROOTTWIST_ATK = 0;
		t_tick spamtick_SU_POWEROFLIFE = 0;
		t_tick spamtick_SU_SCAROFTAROU = 0;
		t_tick spamtick_SU_PICKYPECK = 0;
		t_tick spamtick_SU_PICKYPECK_DOUBLE_ATK = 0;
		t_tick spamtick_SU_ARCLOUSEDASH = 0;
		t_tick spamtick_SU_LUNATICCARROTBEAT = 0;
		t_tick spamtick_SU_POWEROFSEA = 0;
		t_tick spamtick_SU_TUNABELLY = 0;
		t_tick spamtick_SU_TUNAPARTY = 0;
		t_tick spamtick_SU_BUNCHOFSHRIMP = 0;
		t_tick spamtick_SU_FRESHSHRIMP = 0;
		t_tick spamtick_SU_CN_METEOR2 = 0;
		t_tick spamtick_SU_LUNATICCARROTBEAT2 = 0;
		t_tick spamtick_SU_SOULATTACK = 0;
		t_tick spamtick_SU_POWEROFFLOCK = 0;
		t_tick spamtick_SU_SVG_SPIRIT = 0;
		t_tick spamtick_SU_HISS = 0;
		t_tick spamtick_SU_NYANGGRASS = 0;
		t_tick spamtick_SU_GROOMING = 0;
		t_tick spamtick_SU_PURRING = 0;
		t_tick spamtick_SU_SHRIMPARTY = 0;
		t_tick spamtick_SU_SPIRITOFLIFE = 0;
		t_tick spamtick_SU_MEOWMEOW = 0;
		t_tick spamtick_SU_SPIRITOFLAND = 0;
		t_tick spamtick_SU_CHATTERING = 0;
		t_tick spamtick_SU_SPIRITOFSEA = 0;
		t_tick spamtick_CG_SPECIALSINGER = 0;
		t_tick spamtick_AB_VITUPERATUM = 0;
		t_tick spamtick_AB_CONVENIO = 0;
		t_tick spamtick_DK_SERVANTWEAPON = 0;
		t_tick spamtick_DK_SERVANT_W_SIGN = 0;
		t_tick spamtick_DK_SERVANT_W_PHANTOM = 0;
		t_tick spamtick_DK_SERVANT_W_DEMOL = 0;
		t_tick spamtick_DK_CHARGINGPIERCE = 0;
		t_tick spamtick_DK_HACKANDSLASHER = 0;
		t_tick spamtick_DK_DRAGONIC_AURA = 0;
		t_tick spamtick_DK_MADNESS_CRUSHER = 0;
		t_tick spamtick_DK_VIGOR = 0;
		t_tick spamtick_DK_STORMSLASH = 0;
		t_tick spamtick_AG_DEADLY_PROJECTION = 0;
		t_tick spamtick_AG_DESTRUCTIVE_HURRICANE = 0;
		t_tick spamtick_AG_RAIN_OF_CRYSTAL = 0;
		t_tick spamtick_AG_MYSTERY_ILLUSION = 0;
		t_tick spamtick_AG_VIOLENT_QUAKE = 0;
		t_tick spamtick_AG_SOUL_VC_STRIKE = 0;
		t_tick spamtick_AG_STRANTUM_TREMOR = 0;
		t_tick spamtick_AG_ALL_BLOOM = 0;
		t_tick spamtick_AG_CRYSTAL_IMPACT = 0;
		t_tick spamtick_AG_TORNADO_STORM = 0;
		t_tick spamtick_AG_FLORAL_FLARE_ROAD = 0;
		t_tick spamtick_AG_ASTRAL_STRIKE = 0;
		t_tick spamtick_AG_CLIMAX = 0;
		t_tick spamtick_AG_ROCK_DOWN = 0;
		t_tick spamtick_AG_STORM_CANNON = 0;
		t_tick spamtick_AG_CRIMSON_ARROW = 0;
		t_tick spamtick_AG_FROZEN_SLASH = 0;
		t_tick spamtick_IQ_POWERFUL_FAITH = 0;
		t_tick spamtick_IQ_FIRM_FAITH = 0;
		t_tick spamtick_IQ_WILL_OF_FAITH = 0;
		t_tick spamtick_IQ_OLEUM_SANCTUM = 0;
		t_tick spamtick_IQ_SINCERE_FAITH = 0;
		t_tick spamtick_IQ_MASSIVE_F_BLASTER = 0;
		t_tick spamtick_IQ_EXPOSION_BLASTER = 0;
		t_tick spamtick_IQ_FIRST_BRAND = 0;
		t_tick spamtick_IQ_FIRST_FAITH_POWER = 0;
		t_tick spamtick_IQ_JUDGE = 0;
		t_tick spamtick_IQ_SECOND_FLAME = 0;
		t_tick spamtick_IQ_SECOND_FAITH = 0;
		t_tick spamtick_IQ_SECOND_JUDGEMENT = 0;
		t_tick spamtick_IQ_THIRD_PUNISH = 0;
		t_tick spamtick_IQ_THIRD_FLAME_BOMB = 0;
		t_tick spamtick_IQ_THIRD_CONSECRATION = 0;
		t_tick spamtick_IQ_THIRD_EXOR_FLAME = 0;
		t_tick spamtick_IG_GUARD_STANCE = 0;
		t_tick spamtick_IG_GUARDIAN_SHIELD = 0;
		t_tick spamtick_IG_REBOUND_SHIELD = 0;
		t_tick spamtick_IG_ATTACK_STANCE = 0;
		t_tick spamtick_IG_ULTIMATE_SACRIFICE = 0;
		t_tick spamtick_IG_HOLY_SHIELD = 0;
		t_tick spamtick_IG_GRAND_JUDGEMENT = 0;
		t_tick spamtick_IG_JUDGEMENT_CROSS = 0;
		t_tick spamtick_IG_SHIELD_SHOOTING = 0;
		t_tick spamtick_IG_OVERSLASH = 0;
		t_tick spamtick_IG_CROSS_RAIN = 0;
		t_tick spamtick_CD_REPARATIO = 0;
		t_tick spamtick_CD_MEDIALE_VOTUM = 0;
		t_tick spamtick_CD_ARGUTUS_VITA = 0;
		t_tick spamtick_CD_ARGUTUS_TELUM = 0;
		t_tick spamtick_CD_ARBITRIUM = 0;
		t_tick spamtick_CD_PRESENS_ACIES = 0;
		t_tick spamtick_CD_EFFLIGO = 0;
		t_tick spamtick_CD_COMPETENTIA = 0;
		t_tick spamtick_CD_PNEUMATICUS_PROCELLA = 0;
		t_tick spamtick_CD_DILECTIO_HEAL = 0;
		t_tick spamtick_CD_RELIGIO = 0;
		t_tick spamtick_CD_BENEDICTUM = 0;
		t_tick spamtick_CD_PETITIO = 0;
		t_tick spamtick_CD_FRAMEN = 0;
		t_tick spamtick_SHC_SHADOW_EXCEED = 0;
		t_tick spamtick_SHC_DANCING_KNIFE = 0;
		t_tick spamtick_SHC_SAVAGE_IMPACT = 0;
		t_tick spamtick_SHC_ETERNAL_SLASH = 0;
		t_tick spamtick_SHC_POTENT_VENOM = 0;
		t_tick spamtick_SHC_SHADOW_STAB = 0;
		t_tick spamtick_SHC_IMPACT_CRATER = 0;
		t_tick spamtick_SHC_ENCHANTING_SHADOW = 0;
		t_tick spamtick_SHC_FATAL_SHADOW_CROW = 0;
		t_tick spamtick_MT_AXE_STOMP = 0;
		t_tick spamtick_MT_RUSH_QUAKE = 0;
		t_tick spamtick_MT_M_MACHINE = 0;
		t_tick spamtick_MT_A_MACHINE = 0;
		t_tick spamtick_MT_D_MACHINE = 0;
		t_tick spamtick_MT_TWOAXEDEF = 0;
		t_tick spamtick_MT_ABR_M = 0;
		t_tick spamtick_MT_SUMMON_ABR_BATTLE_WARIOR = 0;
		t_tick spamtick_MT_SUMMON_ABR_DUAL_CANNON = 0;
		t_tick spamtick_MT_SUMMON_ABR_MOTHER_NET = 0;
		t_tick spamtick_MT_SUMMON_ABR_INFINITY = 0;
		t_tick spamtick_AG_DESTRUCTIVE_HURRICANE_CLIMAX = 0;
		t_tick spamtick_ABC_STRIP_SHADOW = 0;
		t_tick spamtick_ABC_ABYSS_DAGGER = 0;
		t_tick spamtick_ABC_UNLUCKY_RUSH = 0;
		t_tick spamtick_ABC_CHAIN_REACTION_SHOT = 0;
		t_tick spamtick_ABC_FROM_THE_ABYSS = 0;
		t_tick spamtick_ABC_ABYSS_SLAYER = 0;
		t_tick spamtick_ABC_ABYSS_STRIKE = 0;
		t_tick spamtick_ABC_DEFT_STAB = 0;
		t_tick spamtick_ABC_ABYSS_SQUARE = 0;
		t_tick spamtick_ABC_FRENZY_SHOT = 0;
		t_tick spamtick_WH_NATUREFRIENDLY = 0;
		t_tick spamtick_WH_HAWKRUSH = 0;
		t_tick spamtick_WH_HAWKBOOMERANG = 0;
		t_tick spamtick_WH_GALESTORM = 0;
		t_tick spamtick_WH_DEEPBLINDTRAP = 0;
		t_tick spamtick_WH_SOLIDTRAP = 0;
		t_tick spamtick_WH_SWIFTTRAP = 0;
		t_tick spamtick_WH_CRESCIVE_BOLT = 0;
		t_tick spamtick_WH_FLAMETRAP = 0;
		t_tick spamtick_BO_ACIDIFIED_ZONE_WATER = 0;
		t_tick spamtick_BO_ACIDIFIED_ZONE_GROUND = 0;
		t_tick spamtick_BO_ACIDIFIED_ZONE_WIND = 0;
		t_tick spamtick_BO_ACIDIFIED_ZONE_FIRE = 0;
		t_tick spamtick_TR_STAGE_MANNER = 0;
		t_tick spamtick_TR_ROSEBLOSSOM = 0;
		t_tick spamtick_TR_RHYTHMSHOOTING = 0;
		t_tick spamtick_TR_METALIC_FURY = 0;
		t_tick spamtick_EM_DIAMOND_STORM = 0;
		t_tick spamtick_EM_LIGHTNING_LAND = 0;
		t_tick spamtick_EM_VENOM_SWAMP = 0;
		t_tick spamtick_EM_CONFLAGRATION = 0;
		t_tick spamtick_EM_TERRA_DRIVE = 0;
		t_tick spamtick_EM_ELEMENTAL_BUSTER = 0;
		t_tick spamtick_BO_WOODEN_THROWROCK = 0;
		t_tick spamtick_BO_WOODEN_ATTACK = 0;
		t_tick spamtick_BO_HELL_HOWLING = 0;
		t_tick spamtick_BO_HELL_DUSTY = 0;
		t_tick spamtick_BO_FAIRY_DUSTY = 0;
		t_tick spamtick_EM_ELEMENTAL_BUSTER_FIRE = 0;
		t_tick spamtick_EM_ELEMENTAL_BUSTER_WATER = 0;
		t_tick spamtick_EM_ELEMENTAL_BUSTER_WIND = 0;
		t_tick spamtick_EM_ELEMENTAL_BUSTER_GROUND = 0;
		t_tick spamtick_EM_ELEMENTAL_BUSTER_POISON = 0;

		unsigned int spamcount_DEFAULT = 0;
		unsigned int spamcount_MO_RELOCDELAY = 0;
		unsigned int spamcount_SM_BASH = 0;
		unsigned int spamcount_SM_MAGNUM = 0;
		unsigned int spamcount_MG_NAPALMBEAT = 0;
		unsigned int spamcount_MG_SOULSTRIKE = 0;
		unsigned int spamcount_MG_COLDBOLT = 0;
		unsigned int spamcount_MG_FROSTDIVER = 0;
		unsigned int spamcount_MG_STONECURSE = 0;
		unsigned int spamcount_MG_FIREBALL = 0;
		unsigned int spamcount_MG_FIREWALL = 0;
		unsigned int spamcount_MG_FIREBOLT = 0;
		unsigned int spamcount_MG_LIGHTNINGBOLT = 0;
		unsigned int spamcount_MG_THUNDERSTORM = 0;
		unsigned int spamcount_AL_HEAL = 0;
		unsigned int spamcount_AL_DECAGI = 0;
		unsigned int spamcount_AL_CRUCIS = 0;
		unsigned int spamcount_MC_MAMMONITE = 0;
		unsigned int spamcount_AC_DOUBLE = 0;
		unsigned int spamcount_AC_SHOWER = 0;
		unsigned int spamcount_TF_POISON = 0;
		unsigned int spamcount_KN_PIERCE = 0;
		unsigned int spamcount_KN_BRANDISHSPEAR = 0;
		unsigned int spamcount_KN_SPEARSTAB = 0;
		unsigned int spamcount_KN_SPEARBOOMERANG = 0;
		unsigned int spamcount_KN_BOWLINGBASH = 0;
		unsigned int spamcount_PR_LEXDIVINA = 0;
		unsigned int spamcount_PR_TURNUNDEAD = 0;
		unsigned int spamcount_PR_LEXAETERNA = 0;
		unsigned int spamcount_PR_MAGNUS = 0;
		unsigned int spamcount_WZ_FIREPILLAR = 0;
		unsigned int spamcount_WZ_SIGHTRASHER = 0;
		unsigned int spamcount_WZ_FIREIVY = 0;
		unsigned int spamcount_WZ_METEOR = 0;
		unsigned int spamcount_WZ_JUPITEL = 0;
		unsigned int spamcount_WZ_VERMILION = 0;
		unsigned int spamcount_WZ_WATERBALL = 0;
		unsigned int spamcount_WZ_ICEWALL = 0;
		unsigned int spamcount_WZ_FROSTNOVA = 0;
		unsigned int spamcount_WZ_STORMGUST = 0;
		unsigned int spamcount_WZ_EARTHSPIKE = 0;
		unsigned int spamcount_WZ_HEAVENDRIVE = 0;
		unsigned int spamcount_WZ_QUAGMIRE = 0;
		unsigned int spamcount_WZ_ESTIMATION = 0;
		unsigned int spamcount_BS_HAMMERFALL = 0;
		unsigned int spamcount_HT_BLITZBEAT = 0;
		unsigned int spamcount_AS_SONICBLOW = 0;
		unsigned int spamcount_AS_GRIMTOOTH = 0;
		unsigned int spamcount_AC_CHARGEARROW = 0;
		unsigned int spamcount_TF_BACKSLIDING = 0;
		unsigned int spamcount_MC_CARTREVOLUTION = 0;
		unsigned int spamcount_AL_HOLYLIGHT = 0;
		unsigned int spamcount_RG_BACKSTAP = 0;
		unsigned int spamcount_RG_RAID = 0;
		unsigned int spamcount_RG_GRAFFITI = 0;
		unsigned int spamcount_RG_FLAGGRAFFITI = 0;
		unsigned int spamcount_RG_COMPULSION = 0;
		unsigned int spamcount_RG_PLAGIARISM = 0;
		unsigned int spamcount_AM_DEMONSTRATION = 0;
		unsigned int spamcount_AM_ACIDTERROR = 0;
		unsigned int spamcount_AM_POTIONPITCHER = 0;
		unsigned int spamcount_AM_CANNIBALIZE = 0;
		unsigned int spamcount_AM_SPHEREMINE = 0;
		unsigned int spamcount_AM_FLAMECONTROL = 0;
		unsigned int spamcount_AM_DRILLMASTER = 0;
		unsigned int spamcount_CR_SHIELDBOOMERANG = 0;
		unsigned int spamcount_CR_HOLYCROSS = 0;
		unsigned int spamcount_CR_GRANDCROSS = 0;
		unsigned int spamcount_MO_CALLSPIRITS = 0;
		unsigned int spamcount_MO_ABSORBSPIRITS = 0;
		unsigned int spamcount_MO_BODYRELOCATION = 0;
		unsigned int spamcount_MO_INVESTIGATE = 0;
		unsigned int spamcount_MO_FINGEROFFENSIVE = 0;
		unsigned int spamcount_MO_EXPLOSIONSPIRITS = 0;
		unsigned int spamcount_MO_EXTREMITYFIST = 0;
		unsigned int spamcount_MO_CHAINCOMBO = 0;
		unsigned int spamcount_MO_COMBOFINISH = 0;
		unsigned int spamcount_SA_CASTCANCEL = 0;
		unsigned int spamcount_SA_SPELLBREAKER = 0;
		unsigned int spamcount_SA_DISPELL = 0;
		unsigned int spamcount_SA_ABRACADABRA = 0;
		unsigned int spamcount_SA_MONOCELL = 0;
		unsigned int spamcount_SA_CLASSCHANGE = 0;
		unsigned int spamcount_SA_SUMMONMONSTER = 0;
		unsigned int spamcount_SA_REVERSEORCISH = 0;
		unsigned int spamcount_SA_DEATH = 0;
		unsigned int spamcount_SA_FORTUNE = 0;
		unsigned int spamcount_SA_TAMINGMONSTER = 0;
		unsigned int spamcount_SA_QUESTION = 0;
		unsigned int spamcount_SA_GRAVITY = 0;
		unsigned int spamcount_SA_LEVELUP = 0;
		unsigned int spamcount_SA_INSTANTDEATH = 0;
		unsigned int spamcount_SA_FULLRECOVERY = 0;
		unsigned int spamcount_SA_COMA = 0;
		unsigned int spamcount_BD_ADAPTATION = 0;
		unsigned int spamcount_BD_ENCORE = 0;
		unsigned int spamcount_BD_LULLABY = 0;
		unsigned int spamcount_BD_RICHMANKIM = 0;
		unsigned int spamcount_BA_MUSICALSTRIKE = 0;
		unsigned int spamcount_BA_DISSONANCE = 0;
		unsigned int spamcount_BA_FROSTJOKER = 0;
		unsigned int spamcount_BA_WHISTLE = 0;
		unsigned int spamcount_BA_ASSASSINCROSS = 0;
		unsigned int spamcount_BA_POEMBRAGI = 0;
		unsigned int spamcount_BA_APPLEIDUN = 0;
		unsigned int spamcount_DC_THROWARROW = 0;
		unsigned int spamcount_DC_UGLYDANCE = 0;
		unsigned int spamcount_DC_SCREAM = 0;
		unsigned int spamcount_DC_HUMMING = 0;
		unsigned int spamcount_DC_DONTFORGETME = 0;
		unsigned int spamcount_DC_FORTUNEKISS = 0;
		unsigned int spamcount_DC_SERVICEFORYOU = 0;
		unsigned int spamcount_LK_FURY = 0;
		unsigned int spamcount_HW_MAGICCRASHER = 0;
		unsigned int spamcount_PA_PRESSURE = 0;
		unsigned int spamcount_CH_PALMSTRIKE = 0;
		unsigned int spamcount_CH_TIGERFIST = 0;
		unsigned int spamcount_CH_CHAINCRUSH = 0;
		unsigned int spamcount_PF_SOULCHANGE = 0;
		unsigned int spamcount_PF_SOULBURN = 0;
		unsigned int spamcount_ASC_BREAKER = 0;
		unsigned int spamcount_SN_FALCONASSAULT = 0;
		unsigned int spamcount_SN_SHARPSHOOTING = 0;
		unsigned int spamcount_CR_ALCHEMY = 0;
		unsigned int spamcount_CR_SYNTHESISPOTION = 0;
		unsigned int spamcount_CG_ARROWVULCAN = 0;
		unsigned int spamcount_CG_MOONLIT = 0;
		unsigned int spamcount_CG_MARIONETTE = 0;
		unsigned int spamcount_LK_SPIRALPIERCE = 0;
		unsigned int spamcount_LK_HEADCRUSH = 0;
		unsigned int spamcount_LK_JOINTBEAT = 0;
		unsigned int spamcount_HW_NAPALMVULCAN = 0;
		unsigned int spamcount_CH_SOULCOLLECT = 0;
		unsigned int spamcount_PF_MINDBREAKER = 0;
		unsigned int spamcount_PF_SPIDERWEB = 0;
		unsigned int spamcount_ASC_METEORASSAULT = 0;
		unsigned int spamcount_TK_STORMKICK = 0;
		unsigned int spamcount_TK_DOWNKICK = 0;
		unsigned int spamcount_TK_TURNKICK = 0;
		unsigned int spamcount_TK_JUMPKICK = 0;
		unsigned int spamcount_TK_POWER = 0;
		unsigned int spamcount_TK_HIGHJUMP = 0;
		unsigned int spamcount_SL_KAIZEL = 0;
		unsigned int spamcount_SL_KAAHI = 0;
		unsigned int spamcount_SL_KAUPE = 0;
		unsigned int spamcount_SL_KAITE = 0;
		unsigned int spamcount_SL_KAINA = 0;
		unsigned int spamcount_SL_STIN = 0;
		unsigned int spamcount_SL_STUN = 0;
		unsigned int spamcount_SL_SMA = 0;
		unsigned int spamcount_SL_SWOO = 0;
		unsigned int spamcount_SL_SKE = 0;
		unsigned int spamcount_SL_SKA = 0;
		unsigned int spamcount_ST_FULLSTRIP = 0;
		unsigned int spamcount_CR_SLIMPITCHER = 0;
		unsigned int spamcount_CR_FULLPROTECTION = 0;
		unsigned int spamcount_PA_SHIELDCHAIN = 0;
		unsigned int spamcount_HP_MANARECHARGE = 0;
		unsigned int spamcount_PF_DOUBLECASTING = 0;
		unsigned int spamcount_HW_GANBANTEIN = 0;
		unsigned int spamcount_HW_GRAVITATION = 0;
		unsigned int spamcount_WS_CARTTERMINATION = 0;
		unsigned int spamcount_CG_HERMODE = 0;
		unsigned int spamcount_CG_TAROTCARD = 0;
		unsigned int spamcount_CR_ACIDDEMONSTRATION = 0;
		unsigned int spamcount_SL_HIGH = 0;
		unsigned int spamcount_GS_TRIPLEACTION = 0;
		unsigned int spamcount_GS_BULLSEYE = 0;
		unsigned int spamcount_GS_MADNESSCANCEL = 0;
		unsigned int spamcount_GS_INCREASING = 0;
		unsigned int spamcount_GS_MAGICALBULLET = 0;
		unsigned int spamcount_GS_CRACKER = 0;
		unsigned int spamcount_GS_SINGLEACTION = 0;
		unsigned int spamcount_GS_CHAINACTION = 0;
		unsigned int spamcount_GS_TRACKING = 0;
		unsigned int spamcount_GS_DISARM = 0;
		unsigned int spamcount_GS_PIERCINGSHOT = 0;
		unsigned int spamcount_GS_RAPIDSHOWER = 0;
		unsigned int spamcount_GS_DESPERADO = 0;
		unsigned int spamcount_GS_GATLINGFEVER = 0;
		unsigned int spamcount_GS_DUST = 0;
		unsigned int spamcount_GS_FULLBUSTER = 0;
		unsigned int spamcount_GS_SPREADATTACK = 0;
		unsigned int spamcount_GS_GROUNDDRIFT = 0;
		unsigned int spamcount_NJ_TOBIDOUGU = 0;
		unsigned int spamcount_NJ_SYURIKEN = 0;
		unsigned int spamcount_NJ_KUNAI = 0;
		unsigned int spamcount_NJ_HUUMA = 0;
		unsigned int spamcount_NJ_ZENYNAGE = 0;
		unsigned int spamcount_NJ_TATAMIGAESHI = 0;
		unsigned int spamcount_NJ_KASUMIKIRI = 0;
		unsigned int spamcount_NJ_SHADOWJUMP = 0;
		unsigned int spamcount_NJ_KIRIKAGE = 0;
		unsigned int spamcount_NJ_UTSUSEMI = 0;
		unsigned int spamcount_NJ_BUNSINJYUTSU = 0;
		unsigned int spamcount_NJ_NINPOU = 0;
		unsigned int spamcount_NJ_KOUENKA = 0;
		unsigned int spamcount_NJ_KAENSIN = 0;
		unsigned int spamcount_NJ_BAKUENRYU = 0;
		unsigned int spamcount_NJ_HYOUSENSOU = 0;
		unsigned int spamcount_NJ_SUITON = 0;
		unsigned int spamcount_NJ_HYOUSYOURAKU = 0;
		unsigned int spamcount_NJ_HUUJIN = 0;
		unsigned int spamcount_NJ_RAIGEKISAI = 0;
		unsigned int spamcount_NJ_KAMAITACHI = 0;
		unsigned int spamcount_NJ_NEN = 0;
		unsigned int spamcount_NJ_ISSEN = 0;
		unsigned int spamcount_KN_CHARGEATK = 0;
		unsigned int spamcount_AS_VENOMKNIFE = 0;
		unsigned int spamcount_RG_CLOSECONFINE = 0;
		unsigned int spamcount_WZ_SIGHTBLASTER = 0;
		unsigned int spamcount_HT_PHANTASMIC = 0;
		unsigned int spamcount_BA_PANGVOICE = 0;
		unsigned int spamcount_DC_WINKCHARM = 0;
		unsigned int spamcount_PR_REDEMPTIO = 0;
		unsigned int spamcount_MO_KITRANSLATION = 0;
		unsigned int spamcount_MO_BALKYOUNG = 0;
		unsigned int spamcount_RK_SONICWAVE = 0;
		unsigned int spamcount_RK_DEATHBOUND = 0;
		unsigned int spamcount_RK_HUNDREDSPEAR = 0;
		unsigned int spamcount_RK_WINDCUTTER = 0;
		unsigned int spamcount_RK_IGNITIONBREAK = 0;
		unsigned int spamcount_RK_DRAGONBREATH = 0;
		unsigned int spamcount_RK_CRUSHSTRIKE = 0;
		unsigned int spamcount_RK_STORMBLAST = 0;
		unsigned int spamcount_RK_PHANTOMTHRUST = 0;
		unsigned int spamcount_GC_CROSSIMPACT = 0;
		unsigned int spamcount_GC_WEAPONCRUSH = 0;
		unsigned int spamcount_GC_ROLLINGCUTTER = 0;
		unsigned int spamcount_GC_CROSSRIPPERSLASHER = 0;
		unsigned int spamcount_AB_JUDEX = 0;
		unsigned int spamcount_AB_ADORAMUS = 0;
		unsigned int spamcount_AB_CHEAL = 0;
		unsigned int spamcount_AB_EPICLESIS = 0;
		unsigned int spamcount_AB_PRAEFATIO = 0;
		unsigned int spamcount_AB_EUCHARISTICA = 0;
		unsigned int spamcount_AB_RENOVATIO = 0;
		unsigned int spamcount_AB_HIGHNESSHEAL = 0;
		unsigned int spamcount_AB_CLEARANCE = 0;
		unsigned int spamcount_AB_EXPIATIO = 0;
		unsigned int spamcount_AB_DUPLELIGHT = 0;
		unsigned int spamcount_AB_DUPLELIGHT_MELEE = 0;
		unsigned int spamcount_AB_DUPLELIGHT_MAGIC = 0;
		unsigned int spamcount_AB_SILENTIUM = 0;
		unsigned int spamcount_WL_WHITEIMPRISON = 0;
		unsigned int spamcount_WL_SOULEXPANSION = 0;
		unsigned int spamcount_WL_FROSTMISTY = 0;
		unsigned int spamcount_WL_JACKFROST = 0;
		unsigned int spamcount_WL_MARSHOFABYSS = 0;
		unsigned int spamcount_WL_RADIUS = 0;
		unsigned int spamcount_WL_STASIS = 0;
		unsigned int spamcount_WL_DRAINLIFE = 0;
		unsigned int spamcount_WL_CRIMSONROCK = 0;
		unsigned int spamcount_WL_HELLINFERNO = 0;
		unsigned int spamcount_WL_COMET = 0;
		unsigned int spamcount_WL_CHAINLIGHTNING = 0;
		unsigned int spamcount_WL_EARTHSTRAIN = 0;
		unsigned int spamcount_WL_TETRAVORTEX = 0;
		unsigned int spamcount_WL_RELEASE = 0;
		unsigned int spamcount_WL_READING_SB = 0;
		unsigned int spamcount_WL_FREEZE_SP = 0;
		unsigned int spamcount_RA_ARROWSTORM = 0;
		unsigned int spamcount_RA_AIMEDBOLT = 0;
		unsigned int spamcount_RA_WUGSTRIKE = 0;
		unsigned int spamcount_RA_WUGBITE = 0;
		unsigned int spamcount_NC_BOOSTKNUCKLE = 0;
		unsigned int spamcount_NC_PILEBUNKER = 0;
		unsigned int spamcount_NC_VULCANARM = 0;
		unsigned int spamcount_NC_FLAMELAUNCHER = 0;
		unsigned int spamcount_NC_COLDSLOWER = 0;
		unsigned int spamcount_NC_ARMSCANNON = 0;
		unsigned int spamcount_NC_ACCELERATION = 0;
		unsigned int spamcount_NC_F_SIDESLIDE = 0;
		unsigned int spamcount_NC_B_SIDESLIDE = 0;
		unsigned int spamcount_NC_MAINFRAME = 0;
		unsigned int spamcount_NC_SHAPESHIFT = 0;
		unsigned int spamcount_NC_INFRAREDSCAN = 0;
		unsigned int spamcount_NC_ANALYZE = 0;
		unsigned int spamcount_NC_MAGNETICFIELD = 0;
		unsigned int spamcount_NC_NEUTRALBARRIER = 0;
		unsigned int spamcount_NC_STEALTHFIELD = 0;
		unsigned int spamcount_NC_AXEBOOMERANG = 0;
		unsigned int spamcount_NC_POWERSWING = 0;
		unsigned int spamcount_NC_AXETORNADO = 0;
		unsigned int spamcount_NC_SILVERSNIPER = 0;
		unsigned int spamcount_NC_MAGICDECOY = 0;
		unsigned int spamcount_NC_DISJOINT = 0;
		unsigned int spamcount_SC_FATALMENACE = 0;
		unsigned int spamcount_SC_AUTOSHADOWSPELL = 0;
		unsigned int spamcount_SC_TRIANGLESHOT = 0;
		unsigned int spamcount_SC_INVISIBILITY = 0;
		unsigned int spamcount_SC_ENERVATION = 0;
		unsigned int spamcount_SC_GROOMY = 0;
		unsigned int spamcount_SC_IGNORANCE = 0;
		unsigned int spamcount_SC_LAZINESS = 0;
		unsigned int spamcount_SC_UNLUCKY = 0;
		unsigned int spamcount_SC_WEAKNESS = 0;
		unsigned int spamcount_SC_STRIPACCESSARY = 0;
		unsigned int spamcount_SC_MANHOLE = 0;
		unsigned int spamcount_SC_DIMENSIONDOOR = 0;
		unsigned int spamcount_SC_CHAOSPANIC = 0;
		unsigned int spamcount_SC_MAELSTROM = 0;
		unsigned int spamcount_SC_BLOODYLUST = 0;
		unsigned int spamcount_SC_FEINTBOMB = 0;
		unsigned int spamcount_LG_CANNONSPEAR = 0;
		unsigned int spamcount_LG_BANISHINGPOINT = 0;
		unsigned int spamcount_LG_TRAMPLE = 0;
		unsigned int spamcount_LG_PINPOINTATTACK = 0;
		unsigned int spamcount_LG_RAGEBURST = 0;
		unsigned int spamcount_LG_EXEEDBREAK = 0;
		unsigned int spamcount_LG_OVERBRAND = 0;
		unsigned int spamcount_LG_BANDING = 0;
		unsigned int spamcount_LG_MOONSLASHER = 0;
		unsigned int spamcount_LG_RAYOFGENESIS = 0;
		unsigned int spamcount_LG_PIETY = 0;
		unsigned int spamcount_LG_EARTHDRIVE = 0;
		unsigned int spamcount_LG_HESPERUSLIT = 0;
		unsigned int spamcount_SR_DRAGONCOMBO = 0;
		unsigned int spamcount_SR_SKYNETBLOW = 0;
		unsigned int spamcount_SR_EARTHSHAKER = 0;
		unsigned int spamcount_SR_FALLENEMPIRE = 0;
		unsigned int spamcount_SR_TIGERCANNON = 0;
		unsigned int spamcount_SR_HELLGATE = 0;
		unsigned int spamcount_SR_RAMPAGEBLASTER = 0;
		unsigned int spamcount_SR_CRESCENTELBOW = 0;
		unsigned int spamcount_SR_CURSEDCIRCLE = 0;
		unsigned int spamcount_SR_LIGHTNINGWALK = 0;
		unsigned int spamcount_SR_KNUCKLEARROW = 0;
		unsigned int spamcount_SR_WINDMILL = 0;
		unsigned int spamcount_SR_RAISINGDRAGON = 0;
		unsigned int spamcount_SR_GENTLETOUCH = 0;
		unsigned int spamcount_SR_ASSIMILATEPOWER = 0;
		unsigned int spamcount_SR_POWERVELOCITY = 0;
		unsigned int spamcount_SR_CRESCENTELBOW_AUTOSPELL = 0;
		unsigned int spamcount_SR_GATEOFHELL = 0;
		unsigned int spamcount_SR_GENTLETOUCH_QUIET = 0;
		unsigned int spamcount_SR_GENTLETOUCH_CURE = 0;
		unsigned int spamcount_SR_GENTLETOUCH_ENERGYGAIN = 0;
		unsigned int spamcount_SR_GENTLETOUCH_CHANGE = 0;
		unsigned int spamcount_SR_GENTLETOUCH_REVITALIZE = 0;
		unsigned int spamcount_WA_SWING_DANCE = 0;
		unsigned int spamcount_WA_SYMPHONY_OF_LOVER = 0;
		unsigned int spamcount_WA_MOONLIT_SERENADE = 0;
		unsigned int spamcount_MI_RUSH_WINDMILL = 0;
		unsigned int spamcount_MI_ECHOSONG = 0;
		unsigned int spamcount_MI_HARMONIZE = 0;
		unsigned int spamcount_WM_LESSON = 0;
		unsigned int spamcount_WM_METALICSOUND = 0;
		unsigned int spamcount_WM_REVERBERATION = 0;
		unsigned int spamcount_WM_REVERBERATION_MELEE = 0;
		unsigned int spamcount_WM_REVERBERATION_MAGIC = 0;
		unsigned int spamcount_WM_DOMINION_IMPULSE = 0;
		unsigned int spamcount_WM_SEVERE_RAINSTORM = 0;
		unsigned int spamcount_WM_SEVERE_RAINSTORM_MELEE = 0;
		unsigned int spamcount_WM_POEMOFNETHERWORLD = 0;
		unsigned int spamcount_WM_VOICEOFSIREN = 0;
		unsigned int spamcount_WM_DEADHILLHERE = 0;
		unsigned int spamcount_WM_LULLABY_DEEPSLEEP = 0;
		unsigned int spamcount_WM_SIRCLEOFNATURE = 0;
		unsigned int spamcount_WM_RANDOMIZESPELL = 0;
		unsigned int spamcount_WM_GLOOMYDAY = 0;
		unsigned int spamcount_WM_GREAT_ECHO = 0;
		unsigned int spamcount_WM_SONG_OF_MANA = 0;
		unsigned int spamcount_WM_DANCE_WITH_WUG = 0;
		unsigned int spamcount_WM_SOUND_OF_DESTRUCTION = 0;
		unsigned int spamcount_WM_SATURDAY_NIGHT_FEVER = 0;
		unsigned int spamcount_WM_LERADS_DEW = 0;
		unsigned int spamcount_WM_MELODYOFSINK = 0;
		unsigned int spamcount_WM_BEYOND_OF_WARCRY = 0;
		unsigned int spamcount_WM_UNLIMITED_HUMMING_VOICE = 0;
		unsigned int spamcount_SO_FIREWALK = 0;
		unsigned int spamcount_SO_ELECTRICWALK = 0;
		unsigned int spamcount_SO_SPELLFIST = 0;
		unsigned int spamcount_SO_EARTHGRAVE = 0;
		unsigned int spamcount_SO_DIAMONDDUST = 0;
		unsigned int spamcount_SO_POISON_BUSTER = 0;
		unsigned int spamcount_SO_PSYCHIC_WAVE = 0;
		unsigned int spamcount_SO_CLOUD_KILL = 0;
		unsigned int spamcount_SO_STRIKING = 0;
		unsigned int spamcount_SO_WARMER = 0;
		unsigned int spamcount_SO_VACUUM_EXTREME = 0;
		unsigned int spamcount_SO_VARETYR_SPEAR = 0;
		unsigned int spamcount_SO_ARRULLO = 0;
		unsigned int spamcount_SO_EL_CONTROL = 0;
		unsigned int spamcount_SO_EL_ACTION = 0;
		unsigned int spamcount_SO_EL_ANALYSIS = 0;
		unsigned int spamcount_SO_EL_SYMPATHY = 0;
		unsigned int spamcount_SO_EL_CURE = 0;
		unsigned int spamcount_GN_CART_TORNADO = 0;
		unsigned int spamcount_GN_CARTCANNON = 0;
		unsigned int spamcount_GN_THORNS_TRAP = 0;
		unsigned int spamcount_GN_BLOOD_SUCKER = 0;
		unsigned int spamcount_GN_SPORE_EXPLOSION = 0;
		unsigned int spamcount_GN_WALLOFTHORN = 0;
		unsigned int spamcount_GN_CRAZYWEED = 0;
		unsigned int spamcount_GN_DEMONIC_FIRE = 0;
		unsigned int spamcount_GN_FIRE_EXPANSION = 0;
		unsigned int spamcount_GN_HELLS_PLANT = 0;
		unsigned int spamcount_GN_MANDRAGORA = 0;
		unsigned int spamcount_GN_SLINGITEM = 0;
		unsigned int spamcount_GN_CHANGEMATERIAL = 0;
		unsigned int spamcount_AB_SECRAMENT = 0;
		unsigned int spamcount_SR_HOWLINGOFLION = 0;
		unsigned int spamcount_SR_RIDEINLIGHTNING = 0;
		unsigned int spamcount_LG_OVERBRAND_BRANDISH = 0;
		unsigned int spamcount_RL_GLITTERING_GREED = 0;
		unsigned int spamcount_RL_RICHS_COIN = 0;
		unsigned int spamcount_RL_MASS_SPIRAL = 0;
		unsigned int spamcount_RL_BANISHING_BUSTER = 0;
		unsigned int spamcount_RL_B_TRAP = 0;
		unsigned int spamcount_RL_S_STORM = 0;
		unsigned int spamcount_RL_E_CHAIN = 0;
		unsigned int spamcount_RL_QD_SHOT = 0;
		unsigned int spamcount_RL_C_MARKER = 0;
		unsigned int spamcount_RL_FIREDANCE = 0;
		unsigned int spamcount_RL_H_MINE = 0;
		unsigned int spamcount_RL_P_ALTER = 0;
		unsigned int spamcount_RL_FALLEN_ANGEL = 0;
		unsigned int spamcount_RL_R_TRIP = 0;
		unsigned int spamcount_RL_D_TAIL = 0;
		unsigned int spamcount_RL_FIRE_RAIN = 0;
		unsigned int spamcount_RL_HEAT_BARREL = 0;
		unsigned int spamcount_RL_AM_BLAST = 0;
		unsigned int spamcount_RL_SLUGSHOT = 0;
		unsigned int spamcount_RL_HAMMER_OF_GOD = 0;
		unsigned int spamcount_KO_YAMIKUMO = 0;
		unsigned int spamcount_KO_JYUMONJIKIRI = 0;
		unsigned int spamcount_KO_SETSUDAN = 0;
		unsigned int spamcount_KO_BAKURETSU = 0;
		unsigned int spamcount_KO_HAPPOKUNAI = 0;
		unsigned int spamcount_KO_MUCHANAGE = 0;
		unsigned int spamcount_KO_HUUMARANKA = 0;
		unsigned int spamcount_KO_MAKIBISHI = 0;
		unsigned int spamcount_KO_MEIKYOUSISUI = 0;
		unsigned int spamcount_KO_ZANZOU = 0;
		unsigned int spamcount_KO_KYOUGAKU = 0;
		unsigned int spamcount_KO_JYUSATSU = 0;
		unsigned int spamcount_KO_KAHU_ENTEN = 0;
		unsigned int spamcount_KO_HYOUHU_HUBUKI = 0;
		unsigned int spamcount_KO_KAZEHU_SEIRAN = 0;
		unsigned int spamcount_KO_DOHU_KOUKAI = 0;
		unsigned int spamcount_KO_KAIHOU = 0;
		unsigned int spamcount_KO_ZENKAI = 0;
		unsigned int spamcount_KO_GENWAKU = 0;
		unsigned int spamcount_KO_IZAYOI = 0;
		unsigned int spamcount_KG_KAGEHUMI = 0;
		unsigned int spamcount_KG_KYOMU = 0;
		unsigned int spamcount_KG_KAGEMUSYA = 0;
		unsigned int spamcount_OB_ZANGETSU = 0;
		unsigned int spamcount_OB_OBOROGENSOU = 0;
		unsigned int spamcount_OB_AKAITSUKI = 0;
		unsigned int spamcount_GC_DARKCROW = 0;
		unsigned int spamcount_RA_UNLIMIT = 0;
		unsigned int spamcount_GN_ILLUSIONDOPING = 0;
		unsigned int spamcount_RK_DRAGONBREATH_WATER = 0;
		unsigned int spamcount_RK_LUXANIMA = 0;
		unsigned int spamcount_NC_MAGMA_ERUPTION = 0;
		unsigned int spamcount_WM_FRIGG_SONG = 0;
		unsigned int spamcount_SO_ELEMENTAL_SHIELD = 0;
		unsigned int spamcount_SR_FLASHCOMBO = 0;
		unsigned int spamcount_SC_ESCAPE = 0;
		unsigned int spamcount_AB_OFFERTORIUM = 0;
		unsigned int spamcount_WL_TELEKINESIS_INTENSE = 0;
		unsigned int spamcount_ALL_FULL_THROTTLE = 0;
		unsigned int spamcount_SU_BITE = 0;
		unsigned int spamcount_SU_SCRATCH = 0;
		unsigned int spamcount_SU_STOOP = 0;
		unsigned int spamcount_SU_LOPE = 0;
		unsigned int spamcount_SU_SPRITEMABLE = 0;
		unsigned int spamcount_SU_POWEROFLAND = 0;
		unsigned int spamcount_SU_SV_STEMSPEAR = 0;
		unsigned int spamcount_SU_CN_POWDERING = 0;
		unsigned int spamcount_SU_CN_METEOR = 0;
		unsigned int spamcount_SU_SV_ROOTTWIST = 0;
		unsigned int spamcount_SU_POWEROFLIFE = 0;
		unsigned int spamcount_SU_SCAROFTAROU = 0;
		unsigned int spamcount_SU_PICKYPECK = 0;
		unsigned int spamcount_SU_ARCLOUSEDASH = 0;
		unsigned int spamcount_SU_LUNATICCARROTBEAT = 0;
		unsigned int spamcount_SU_POWEROFSEA = 0;
		unsigned int spamcount_SU_TUNABELLY = 0;
		unsigned int spamcount_SU_TUNAPARTY = 0;
		unsigned int spamcount_SU_BUNCHOFSHRIMP = 0;
		unsigned int spamcount_SU_FRESHSHRIMP = 0;
		unsigned int spamcount_SU_CN_METEOR2 = 0;
		unsigned int spamcount_SU_LUNATICCARROTBEAT2 = 0;
		unsigned int spamcount_SU_SOULATTACK = 0;
		unsigned int spamcount_SU_POWEROFFLOCK = 0;
		unsigned int spamcount_SU_SVG_SPIRIT = 0;
		unsigned int spamcount_SU_HISS = 0;
		unsigned int spamcount_SU_NYANGGRASS = 0;
		unsigned int spamcount_SU_GROOMING = 0;
		unsigned int spamcount_SU_PURRING = 0;
		unsigned int spamcount_SU_SHRIMPARTY = 0;
		unsigned int spamcount_SU_SPIRITOFLIFE = 0;
		unsigned int spamcount_SU_MEOWMEOW = 0;
		unsigned int spamcount_SU_SPIRITOFLAND = 0;
		unsigned int spamcount_SU_CHATTERING = 0;
		unsigned int spamcount_SU_SPIRITOFSEA = 0;
		unsigned int spamcount_CG_SPECIALSINGER = 0;
		unsigned int spamcount_AB_VITUPERATUM = 0;
		unsigned int spamcount_AB_CONVENIO = 0;
//=========================================================================================

	struct s_item_delay {
		t_itemid nameid;
		t_tick tick;
	} item_delay[MAX_ITEMDELAYS]; // [Paradox924X]

	short weapontype1,weapontype2;
	short disguise; // [Valaris]

	struct weapon_data right_weapon, left_weapon;

	// here start arrays to be globally zeroed at the beginning of status_calc_pc()
	struct s_indexed_bonus {
		int param_bonus[PARAM_MAX], param_equip[PARAM_MAX]; //Stores card/equipment bonuses.
		int subele[ELE_MAX];
		int subele_script[ELE_MAX];
		int subdefele[ELE_MAX];
		int subrace[RC_MAX];
		int subclass[CLASS_MAX];
		int subrace2[RC2_MAX];
		int subsize[SZ_MAX];
		short coma_class[CLASS_MAX];
		short coma_race[RC_MAX];
		short weapon_coma_ele[ELE_MAX];
		short weapon_coma_race[RC_MAX];
		short weapon_coma_class[CLASS_MAX];
		int weapon_atk[16];
		int weapon_damage_rate[16];
		int arrow_addele[ELE_MAX];
		int arrow_addrace[RC_MAX];
		int arrow_addclass[CLASS_MAX];
		int arrow_addsize[SZ_MAX];
		int magic_addele[ELE_MAX];
		int magic_addele_script[ELE_MAX];
		int magic_addrace[RC_MAX];
		int magic_addclass[CLASS_MAX];
		int magic_addsize[SZ_MAX];
		int magic_atk_ele[ELE_MAX];
		int weapon_subsize[SZ_MAX];
		int magic_subsize[SZ_MAX];
		int critaddrace[RC_MAX];
		int expaddrace[RC_MAX];
		int expaddclass[CLASS_MAX];
		int ignore_mdef_by_race[RC_MAX];
		int ignore_mdef_by_class[CLASS_MAX];
		int ignore_def_by_race[RC_MAX];
		int ignore_def_by_class[CLASS_MAX];
		short sp_gain_race[RC_MAX];
		int magic_addrace2[RC2_MAX];
		int ignore_mdef_by_race2[RC2_MAX];
		int dropaddrace[RC_MAX];
		int dropaddclass[CLASS_MAX];
		int magic_subdefele[ELE_MAX];

		// <Epoque>
		short breakequip[EQI_MAX];
		unsigned char noequip[EQI_MAX];
		short weapondef[static_cast<int>(MAX_WEAPON_TYPE)];
		short durabilitydef[EQI_MAX];
	} indexed_bonus;
	// zeroed arrays end here.

	std::vector<s_autospell> autospell, autospell2, autospell3;
	std::vector<s_addeffect> addeff, addeff_atked;
	std::vector<s_addeffectonskill> addeff_onskill;
	std::vector<s_item_bonus> skillatk, skillusesprate, skillusesp, skillheal, skillheal2, skillblown, skillcastrate, skillfixcastrate, subskill, skillcooldown, skillfixcast,
		skillvarcast, skilldelay, itemhealrate, add_def, add_mdef, add_mdmg, reseff, itemgrouphealrate, itemsphealrate, itemgroupsphealrate;
	std::vector<s_add_drop> add_drop;
	std::vector<s_addele2> subele2;
	std::vector<s_vanish_bonus> sp_vanish, hp_vanish;
	std::vector<s_addrace2> subrace3;
	std::vector<std::shared_ptr<s_autobonus>> autobonus, autobonus2, autobonus3; //Auto script on attack, when attacked, on skill usage

	// Stormbreaker
	std::vector<s_bonusvalue2> criticaldodge;
	std::vector<s_bonusvalue3> areaskill;
	std::vector<s_bonusvalue3> skillgainsp;
	std::vector<s_bonusvalue2> statusdamage;
	std::vector<s_bonusvalue2> statusresist;
	std::vector<s_bonusvalue3> statusswitch;
	std::vector<s_bonusvalue3> attackemotion;
	std::vector<s_bonusvalue2> statusrate;
	std::vector<s_bonusvalue3> ignoredefele;
	std::vector<s_bonusvalue3> ignoredefrace;
	std::vector<s_bonusvalue4> areastatus;
	std::vector<s_bonusvalue4> areastatusonhit;
	std::vector<s_bonusvalue2> skillchain;
	std::vector<s_bonusvalue2> skillbounce;
	std::vector<s_bonusvalue2> subjob;
	std::vector<s_bonusvalue2> addjob;
	std::vector<s_bonusvalue2> mobdropitem;
	std::vector<s_bonusvalue2> mobdropitemgroup;
	std::vector<s_bonusvalue3> mobracedropitem;
	std::vector<s_bonusvalue3> mobclassdropitem;
	std::vector<s_bonusvalue2> selfdropitem;
	std::vector<s_bonusvalue2> selfdropitemgroup;
	std::vector<s_bonusvalue3> statusinflict;
	std::vector<s_bonusvalue2> multidrop;
	std::vector<s_bonusvalue2> doublecast;
	std::vector<s_bonusvalue2> gravity;
	std::vector<s_bonusvalue> itemattack;
	std::vector<s_bonusvalue2> atkratechance;
	std::vector<s_bonusvalue2> matkratechance;
	std::vector<s_bonusvalue> skillhpcost;
	std::vector<s_bonusvalue2> skillitemcost;
	std::vector<s_bonusvalue3> autohpuse;
	std::vector<s_bonusvalue3> autospuse;
	std::vector<s_bonusvalue3> autostatususe;
	std::vector<s_bonusvalue2> skillrequirementcost;
	std::vector<s_statusbonus> statusbonus;

	// zeroed structures start here
	struct s_regen {
		short value;
		int rate;
		t_tick tick;
	} hp_loss, sp_loss, hp_regen, sp_regen, percent_hp_regen, percent_sp_regen;
	struct {
		short value;
		int rate, tick;
	} def_set_race[RC_MAX], mdef_set_race[RC_MAX], norecover_state_race[RC_MAX];
	struct s_bonus_vanish_gain {
		short rate,	///< Success rate 0 - 1000 (100%)
			per;	///< % HP/SP vanished/gained
	} hp_vanish_race[RC_MAX], sp_vanish_race[RC_MAX];
	// zeroed structures end here

	// zeroed vars start here.
	struct s_bonus {
		int hp, sp, ap;
		int atk_rate;
		int arrow_atk,arrow_ele,arrow_cri,arrow_hit;
		int nsshealhp,nsshealsp;
		int critical_def,double_rate;
		int short_attack_atk_rate; // Short range atk rate, not weapon based.
		int long_attack_atk_rate; //Long range atk rate, not weapon based. [Skotlex]
		int near_attack_def_rate,long_attack_def_rate,magic_def_rate,misc_def_rate;
		int ignore_mdef_ele;
		int ignore_mdef_race;
		int ignore_mdef_class;
		int perfect_hit;
		int perfect_hit_add;
		int get_zeny_rate;
		int get_zeny_num; //Added Get Zeny Rate [Skotlex]
		int double_add_rate;
		int short_weapon_damage_return,long_weapon_damage_return,reduce_damage_return;
		int magic_damage_return; // AppleGirl Was Here
		int break_weapon_rate,break_armor_rate;
		int crit_atk_rate;
		int crit_def_rate;
		int classchange; // [Valaris]
		int speed_rate, speed_add_rate, aspd_add;
		int itemhealrate2; // [Epoque] Increase heal rate of all healing items.
		int itemsphealrate2;
		int shieldmdef;//royal guard's
		unsigned int setitem_hash, setitem_hash2; //Split in 2 because shift operations only work on int ranges. [Skotlex]

		short splash_range, splash_add_range;
		short add_steal_rate;
		int add_heal_rate, add_heal2_rate;
		int sp_gain_value, hp_gain_value, magic_sp_gain_value, magic_hp_gain_value, long_sp_gain_value, long_hp_gain_value;
		unsigned short unbreakable;	// chance to prevent ANY equipment breaking [celest]
		unsigned short unbreakable_equip; //100% break resistance on certain equipment
		unsigned short unstripable_equip;
		int fixcastrate, varcastrate, delayrate; // n/100
		int add_fixcast, add_varcast; // in milliseconds
		int ematk; // matk bonus from equipment
		int eatk; // atk bonus from equipment
		uint8 absorb_dmg_maxhp; // [Cydh]
		uint8 absorb_dmg_maxhp2;
		short critical_rangeatk;
		short weapon_atk_rate, weapon_matk_rate;

		// <Epoque>
		short homintimacy;
		short skillmove;
		short evadetrap;
		short magicareadefrate;
		short magicsingledefrate;
		short evadecritical;
		s_bonusvalue2 ignoregtb;
		short healattack;
		short statusrate;
		short switchplace;
		short skillchain;
		short skillbounce;
		short petintimacy;
		short interrupt;
		short invert;
		short doublecast;
		short ignoreflee;
		short death;
		short wateratkrate;
		short watermatkrate;
		short noconsume;
		short noammo;
		short autolife;
		unsigned int damagelimit;
		unsigned int hplimit;
		unsigned int splimit;
		short durabilitydef;
		short skillrequirementcost;
	} bonus;
	// zeroed vars end here.

	int castrate,hprate,sprate,aprate,dsprate;
	int hprecov_rate,sprecov_rate;
	int matk_rate;
	int critical_rate,hit_rate,flee_rate,flee2_rate,def_rate,def2_rate,mdef_rate,mdef2_rate;
	int patk_rate,smatk_rate,res_rate,mres_rate,hplus_rate,crate_rate;

	t_itemid itemid;
	short itemindex;	//Used item's index in sd->inventory [Skotlex]

	uint16 catch_target_class; // pet catching, stores a pet class to catch [zzo]

	int8 spiritball, spiritball_old;
	int spirit_timer[MAX_SPIRITBALL];
	short spiritcharm; //No. of spirit
	int spiritcharm_type; //Spirit type
	int spiritcharm_timer[MAX_SPIRITCHARM];
	int8 soulball, soulball_old;
	int8 servantball, servantball_old;
	int8 abyssball, abyssball_old;

	unsigned char potion_success_counter; //Potion successes in row counter
	unsigned char mission_count; //Stores the bounty kill count for TK_MISSION
	short mission_mobid; //Stores the target mob_id for TK_MISSION
	int die_counter; //Total number of times you've died
	int devotion[MAX_DEVOTION]; //Stores the account IDs of chars devoted to.
	int stellar_mark[MAX_STELLAR_MARKS]; // Stores the account ID's of character's with a stellar mark.
	int united_soul[MAX_UNITED_SOULS]; // Stores the account ID's of character's who's soul is united.
	int servant_sign[MAX_SERVANT_SIGN]; // Stores the account ID's of character's with a servant sign.

	int trade_partner;
	struct s_deal {
		struct s_item {
			short index, amount;
		} item[10];
		int zeny, weight;
	} deal;

	bool party_creating; // whether the char is requesting party creation
	bool party_joining; // whether the char is accepting party invitation
	int party_invite, party_invite_account; // for handling party invitation (holds party id and account id)
	int adopt_invite; // Adoption

	struct guild *guild; // [Ind] speed everything up
	int guild_invite,guild_invite_account;
	int guild_emblem_id,guild_alliance,guild_alliance_account;
	short guild_x,guild_y; // For guildmate position display. [Skotlex] should be short [zzo]
	int guildspy; // [Syrus22]
	int partyspy; // [Syrus22]
	int clanspy;

	struct clan *clan;

	short ltp_x,ltp_y; // For last tp position display

	int vended_id;
	int vender_id;
	int vend_num;
	uint16 vend_skill_lv;
	char message[MESSAGE_SIZE];
	struct s_vending vending[MAX_VENDING];

	unsigned int buyer_id;  // uid of open buying store
	struct s_buyingstore buyingstore;

	struct s_search_store_info searchstore;

	// Stormbreaker
	openshoplist* openshop;
#ifdef STORM_BAZAAR
	int bazaar_shop_id;
	int bazaar_timer_id;
#endif

	struct pet_data *pd;
	struct homun_data *hd;	// [blackhole89]
	s_mercenary_data *md;
	s_elemental_data *ed;

	struct s_hate_mob {
		int  m; //-1 - none, other: map index corresponding to map name.
		unsigned short index; //map index
	} feel_map[3];// 0 - Sun; 1 - Moon; 2 - Stars
	short hate_mob[3];

	int pvp_timer;
	short pvp_point;
	unsigned short pvp_rank, pvp_lastusers;
	unsigned short pvp_won, pvp_lost;

	char eventqueue[MAX_EVENTQUEUE][EVENT_NAME_LENGTH];
	int eventtimer[MAX_EVENTTIMER];
	unsigned short eventcount; // [celest]

	uint16 change_level_2nd; // job level when changing from 1st to 2nd class [jobchange_level in global_reg_value]
	uint16 change_level_3rd; // job level when changing from 2nd to 3rd class [jobchange_level_3rd in global_reg_value]
	uint16 change_level_4th; // job level when changing from 3rd to 4th class [jobchange_level_4rd in global_reg_value]

	char fakename[NAME_LENGTH]; // fake names [Valaris]

	size_t duel_group; // duel vars [LuzZza]
	size_t duel_invite;

	int killerrid, killedrid, killedgid;

	int cashPoints, kafraPoints;
	int rental_timer;

	// Auction System [Zephyrus]
	struct s_auction{
		int index, amount;
	} auction;

	// Mail System [Zephyrus]
	struct s_mail {
		struct {
			t_itemid nameid;
			int index, amount;
		} item[MAIL_MAX_ITEM];
		int zeny;
		struct mail_data inbox;
		bool changed; // if true, should sync with charserver on next mailbox request
		uint32 pending_weight;
		uint32 pending_zeny;
		uint16 pending_slots;
	} mail;

	//Quest log system
	int num_quests;          ///< Number of entries in quest_log
	int avail_quests;        ///< Number of Q_ACTIVE and Q_INACTIVE entries in quest log (index of the first Q_COMPLETE entry)
	struct quest *quest_log; ///< Quest log entries (note: Q_COMPLETE quests follow the first <avail_quests>th enties
	bool save_quest;         ///< Whether the quest_log entries were modified and are waitin to be saved

	// Achievement log system
	struct s_achievement_data {
		int total_score;                  ///< Total achievement points
		int level;                        ///< Achievement level
		bool save;                        ///< Flag to know if achievements need to be saved
		uint16 count;                     ///< Total achievements in log
		uint16 incompleteCount;           ///< Total incomplete achievements in log
		struct achievement *achievements; ///< Achievement log entries
	} achievement_data;

	// Title system
	std::vector<int> titles;

	std::vector<int> cloaked_npc;

	/* ShowEvent Data Cache flags from map */
	std::vector<s_qi_display> qi_display;

	// temporary debug [flaviojs]
	const char* debug_file;
	int debug_line;
	const char* debug_func;

	// Battlegrounds queue system [MasterOfMuppets]
	int bg_id, bg_queue_id;
	int tid_queue_active; ///< Timer ID associated with players joining an active BG

#ifdef SECURE_NPCTIMEOUT
	/**
	 * ID of the timer
	 * @info
	 * - value is -1 (INVALID_TIMER constant) when not being used
	 * - timer is cancelled upon closure of the current npc's instance
	 **/
	int npc_idle_timer;
	/**
	 * Tick on the last recorded NPC iteration (next/menu/whatever)
	 * @info
	 * - It is updated on every NPC iteration as mentioned above
	 **/
	t_tick npc_idle_tick;
	/* */
	enum npc_timeout_type npc_idle_type;
#endif

	std::vector<std::shared_ptr<s_combos>> combos;

	/**
	 * Guarantees your friend request is legit (for bugreport:4629)
	 **/
	int friend_req;

	int shadowform_id;

	/* Channel System [Ind] */
	struct Channel **channels;
	unsigned char channel_count;
	struct Channel *gcbind;
	bool stealth;
	unsigned char fontcolor;
	t_tick *channel_tick;

	/* [Ind] */
	struct sc_display_entry **sc_display;
	unsigned char sc_display_count;

	unsigned char delayed_damage; //[Ind]

	/**
	 * Account/Char variables & array control of those variables
	 **/
	struct reg_db regs;
	unsigned char vars_received; // char loading is only complete when you get it all.
	bool vars_ok;
	bool vars_dirty;

	uint16 dmglog[DAMAGELOG_SIZE_PC]; ///target ids

	int c_marker[MAX_SKILL_CRIMSON_MARKER]; /// Store target that marked by Crimson Marker [Cydh]
	bool flicker; /// Check RL_FLICKER usage status [Cydh]

#ifdef VIP_ENABLE
	struct vip_info vip;
#endif

	/// Bonus Script [Cydh]
	struct s_bonus_script_list {
		struct linkdb_node *head; ///< Bonus script head node. data: struct s_bonus_script_entry *entry, key: (intptr_t)entry
		uint16 count;
	} bonus_script;

	/* Expiration Timer ID */
	int expiration_tid;
	time_t expiration_time;

	short last_addeditem_index; /// Index of latest item added
	int autotrade_tid;
	int respawn_tid;
	int bank_vault; ///< Bank Vault

#ifdef PACKET_OBFUSCATION
	unsigned int cryptKey; ///< Packet obfuscation key to be used for the next received packet
#endif

	struct {
		int bronze, silver, gold; ///< Roulette Coin
	} roulette_point;

	struct {
		short stage;
		int8 prizeIdx;
		short prizeStage;
		bool claimPrize;
		t_tick tick;
	} roulette;

	int instance_id;
	e_instance_mode instance_mode; ///< Mode of instance player last leaves from (used for instance destruction button)

	short setlook_head_top, setlook_head_mid, setlook_head_bottom, setlook_robe; ///< Stores 'setlook' script command values.

#if PACKETVER_MAIN_NUM >= 20150507 || PACKETVER_RE_NUM >= 20150429 || defined(PACKETVER_ZERO)
	std::vector<int16> hatEffects;
#endif

	struct{
		int tid;
		uint16 skill_id;
		uint16 level;
		int target;
	} skill_keep_using;

	struct {
		std::shared_ptr<s_captcha_data> cd;
		uint16 upload_size;
	} captcha_upload;

	s_macro_detect macro_detect;

	int goldpc_tid;

	///Extended Vending system [Lilith]
	unsigned short vend_loot;
	int vend_lvl;
};

extern struct eri *pc_sc_display_ers; /// Player's SC display table

/**
 * ERS for the bulk of pc vars
 **/
extern struct eri *num_reg_ers;
extern struct eri *str_reg_ers;

/* Global Expiration Timer ID */
extern int pc_expiration_tid;

enum e_ammo_type : uint8 {
	AMMO_NONE = 0,
	AMMO_ARROW,
	AMMO_DAGGER,
	AMMO_BULLET,
	AMMO_SHELL,
	AMMO_GRENADE,
	AMMO_SHURIKEN,
	AMMO_KUNAI,
	AMMO_CANNONBALL,
	AMMO_THROWWEAPON,
	MAX_AMMO_TYPE
};

enum e_card_type : uint8 {
	CARD_NORMAL = 0,
	CARD_ENCHANT,
	MAX_CARD_TYPE
};

enum idletime_option {
	IDLE_WALK          = 0x0001,
	IDLE_USESKILLTOID  = 0x0002,
	IDLE_USESKILLTOPOS = 0x0004,
	IDLE_USEITEM       = 0x0008,
	IDLE_ATTACK        = 0x0010,
	IDLE_CHAT          = 0x0020,
	IDLE_SIT           = 0x0040,
	IDLE_EMOTION       = 0x0080,
	IDLE_DROPITEM      = 0x0100,
	IDLE_ATCOMMAND     = 0x0200,
	IDLE_NPC_CLOSE     = 0x0400,
	IDLE_NPC_INPUT     = 0x0800,
	IDLE_NPC_MENU      = 0x1000,
	IDLE_NPC_NEXT      = 0x2000,
	IDLE_NPC_PROGRESS  = 0x4000,
};

enum adopt_responses {
	ADOPT_ALLOWED = 0,
	ADOPT_ALREADY_ADOPTED,
	ADOPT_MARRIED_AND_PARTY,
	ADOPT_EQUIP_RINGS,
	ADOPT_NOT_NOVICE,
	ADOPT_CHARACTER_NOT_FOUND,
	ADOPT_MORE_CHILDREN,
	ADOPT_LEVEL_70,
	ADOPT_MARRIED,
};

enum item_check {
	ITMCHK_NONE      = 0x0,
	ITMCHK_INVENTORY = 0x1,
	ITMCHK_CART      = 0x2,
	ITMCHK_STORAGE   = 0x4,
	ITMCHK_ALL       = ITMCHK_INVENTORY|ITMCHK_CART|ITMCHK_STORAGE,
};

enum e_penalty_type : uint16{
	PENALTY_NONE,
	PENALTY_EXP,
	PENALTY_DROP,
	PENALTY_MVP_EXP,
	PENALTY_MVP_DROP,
	PENALTY_MAX
};

struct s_penalty{
	e_penalty_type type;
	uint16 rate[MAX_LEVEL * 2 - 1];
};

class PenaltyDatabase : public TypesafeYamlDatabase<uint16, s_penalty> {
public:
	PenaltyDatabase() : TypesafeYamlDatabase( "PENALTY_DB", 1 ){

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
	void loadingFinished() override;
};

struct s_job_info {
	std::vector<uint32> base_hp, base_sp, base_ap; //Storage for the first calculation with hp/sp/ap factor and multiplicator
	uint32 hp_factor, hp_increase, sp_increase, max_weight_base;
	std::vector<std::array<uint16,PARAM_MAX>> job_bonus;
	std::vector<int16> aspd_base;
	t_exp base_exp[MAX_LEVEL], job_exp[MAX_LEVEL];
	uint16 max_base_level, max_job_level;
	uint16 max_param[PARAM_MAX];
	struct s_job_noenter_map {
		uint32 zone;
		uint8 group_lv;
	} noenter_map;
};

class JobDatabase : public TypesafeCachedYamlDatabase<uint16, s_job_info> {
public:
	JobDatabase() : TypesafeCachedYamlDatabase("JOB_STATS", 2) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
	void loadingFinished() override;

	// Additional
	uint32 get_maxBaseLv(uint16 job_id);
	uint32 get_maxJobLv(uint16 job_id);
	t_exp get_baseExp(uint16 job_id, uint32 level);
	t_exp get_jobExp(uint16 job_id, uint32 level);
	int32 get_maxWeight(uint16 job_id);
};

extern JobDatabase job_db;

struct s_job_bonus_db {
	struct script_code *script;
	job_bonus_type type;
	uint32 id, account_id, char_id, jobidx;

	~s_job_bonus_db() {
		if (this->script){
			script_free_code(this->script);
			this->script = nullptr;
		}
	}
};

class JobBonusDatabase : public TypesafeYamlDatabase<uint32, s_job_bonus_db> {
public:
	JobBonusDatabase() : TypesafeYamlDatabase("JOB_BONUS", 1) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef &node) override;
};

extern JobBonusDatabase job_bonus_db;


#define EQP_WEAPON EQP_HAND_R
#define EQP_SHIELD EQP_HAND_L
#define EQP_ARMS (EQP_HAND_R|EQP_HAND_L)
#define EQP_HELM (EQP_HEAD_LOW|EQP_HEAD_MID|EQP_HEAD_TOP)
#define EQP_ACC (EQP_ACC_L|EQP_ACC_R)
#define EQP_COSTUME (EQP_COSTUME_HEAD_TOP|EQP_COSTUME_HEAD_MID|EQP_COSTUME_HEAD_LOW|EQP_COSTUME_GARMENT)
#define EQP_COSTUME_HELM (EQP_COSTUME_HEAD_TOP|EQP_COSTUME_HEAD_MID|EQP_COSTUME_HEAD_LOW)
#define EQP_SHADOW_GEAR (EQP_SHADOW_ARMOR|EQP_SHADOW_WEAPON|EQP_SHADOW_SHIELD|EQP_SHADOW_SHOES|EQP_SHADOW_ACC_R|EQP_SHADOW_ACC_L)
#define EQP_SHADOW_ACC (EQP_SHADOW_ACC_R|EQP_SHADOW_ACC_L)
#define EQP_SHADOW_ARMS (EQP_SHADOW_WEAPON|EQP_SHADOW_SHIELD)

/// Equip positions that use a visible sprite
#if PACKETVER < 20110111
	#define EQP_VISIBLE EQP_HELM
#else
	#define EQP_VISIBLE (EQP_HELM|EQP_GARMENT|EQP_COSTUME)
#endif

#define pc_setdead(sd)        ( (sd)->state.dead_sit = (sd)->vd.dead_sit = 1 )
#define pc_setsit(sd)         { pc_stop_walking((sd), 1|4); pc_stop_attack((sd)); (sd)->state.dead_sit = (sd)->vd.dead_sit = 2; }
#define pc_isdead(sd)         ( (sd)->state.dead_sit == 1 )
#define pc_issit(sd)          ( (sd)->vd.dead_sit == 2 )
#define pc_isidle_party(sd)   ( (sd)->chatID || (sd)->state.vending || (sd)->state.buyingstore || DIFF_TICK(last_tick, (sd)->idletime) >= battle_config.idle_no_share )
#define pc_isidle_hom(sd)     ( (sd)->hd && ( (sd)->chatID || (sd)->state.vending || (sd)->state.buyingstore || DIFF_TICK(last_tick, (sd)->idletime_hom) >= battle_config.hom_idle_no_share ) )
#define pc_isidle_mer(sd)     ( (sd)->md && ( (sd)->chatID || (sd)->state.vending || (sd)->state.buyingstore || DIFF_TICK(last_tick, (sd)->idletime_mer) >= battle_config.mer_idle_no_share ) )
#define pc_istrading(sd)      ( (sd)->npc_id || (sd)->state.vending || (sd)->state.buyingstore || (sd)->state.trading )
static bool pc_cant_act2( map_session_data* sd ){
	return sd->state.vending || sd->state.buyingstore || (sd->sc.opt1 && sd->sc.opt1 != OPT1_BURNING)
		|| sd->state.trading || sd->state.storage_flag || sd->state.prevend || sd->state.refineui_open
		|| sd->state.stylist_open || sd->state.inventory_expansion_confirmation || sd->npc_shopid
		|| sd->state.barter_open || sd->state.barter_extended_open
		|| sd->state.laphine_synthesis || sd->state.laphine_upgrade
		|| sd->state.roulette_open || sd->state.enchantgrade_open
		|| sd->state.item_reform || sd->state.item_enchant_index;
}
// equals pc_cant_act2 and additionally checks for chat rooms and npcs
static bool pc_cant_act( map_session_data* sd ){
	return sd->npc_id || sd->chatID || pc_cant_act2( sd );
}

#define pc_setdir(sd,b,h)     ( (sd)->ud.dir = (b) ,(sd)->head_dir = (h) )
#define pc_setchatid(sd,n)    ( (sd)->chatID = n )
#define pc_ishiding(sd)       ( (sd)->sc.option&(OPTION_HIDE|OPTION_CLOAK|OPTION_CHASEWALK) )
#define pc_iscloaking(sd)     ( !((sd)->sc.option&OPTION_CHASEWALK) && ((sd)->sc.option&OPTION_CLOAK) )
#define pc_ischasewalk(sd)    ( (sd)->sc.option&OPTION_CHASEWALK )
#ifdef VIP_ENABLE
	#define pc_isvip(sd)      ( (sd)->vip.enabled ? true : false )
#else
	#define pc_isvip(sd)      ( false )
#endif
#ifdef NEW_CARTS
	#define pc_iscarton(sd)       ( (sd)->sc.data[SC_PUSH_CART] )
#else
	#define pc_iscarton(sd)       ( (sd)->sc.option&OPTION_CART )
#endif

#define pc_isfalcon(sd)       ( (sd)->sc.option&OPTION_FALCON )
#define pc_isriding(sd)       ( (sd)->sc.option&OPTION_RIDING )
#define pc_isinvisible(sd)    ( (sd)->sc.option&OPTION_INVISIBLE )
#define pc_is50overweight(sd) ( (sd)->weight * 100 >= (sd)->max_weight * battle_config.natural_heal_weight_rate )
#define pc_is70overweight(sd) ( (sd)->weight * 100 >= (sd)->max_weight * battle_config.natural_heal_weight_rate_renewal )
#define pc_is90overweight(sd) ( (sd)->weight * 10 >= (sd)->max_weight * 9 )

static inline bool pc_hasprogress(map_session_data *sd, enum e_wip_block progress) {
	return sd == NULL || (sd->state.workinprogress&progress) == progress;
}

uint16 pc_maxparameter(map_session_data *sd, e_params param);
short pc_maxaspd(map_session_data *sd);

/**
 * Ranger
 **/
#define pc_iswug(sd)       ( (sd)->sc.option&OPTION_WUG )
#define pc_isridingwug(sd) ( (sd)->sc.option&OPTION_WUGRIDER )
// Mechanic Magic Gear
enum e_mado_type : uint16 {
	MADO_ROBOT = 0x00,
	MADO_UNUSED,
	MADO_SUIT,
	MADO_MAX
};

#define pc_ismadogear(sd) ( (sd)->sc.option&OPTION_MADOGEAR )
// Rune Knight Dragon
#define pc_isridingdragon(sd) ( (sd)->sc.option&OPTION_DRAGON )

#define pc_stop_walking(sd, type) unit_stop_walking(&(sd)->bl, type)
#define pc_stop_attack(sd) unit_stop_attack(&(sd)->bl)

//Weapon check considering dual wielding.
#define pc_check_weapontype(sd, type) ((type)&((sd)->status.weapon < MAX_WEAPON_TYPE? \
	1<<(sd)->status.weapon:(1<<(sd)->weapontype1)|(1<<(sd)->weapontype2)|(1<<(sd)->status.weapon)))
//Checks if the given class value corresponds to a player class. [Skotlex]
//JOB_NOVICE isn't checked for class_ is supposed to be unsigned
#define pcdb_checkid_sub(class_) ( \
	( (class_) < JOB_MAX_BASIC ) || \
	( (class_) >= JOB_NOVICE_HIGH			&& (class_) <= JOB_DARK_COLLECTOR ) || \
	( (class_) >= JOB_RUNE_KNIGHT			&& (class_) <= JOB_MECHANIC_T2    ) || \
	( (class_) >= JOB_BABY_RUNE_KNIGHT		&& (class_) <= JOB_BABY_MECHANIC2 ) || \
	( (class_) >= JOB_SUPER_NOVICE_E		&& (class_) <= JOB_SUPER_BABY_E   ) || \
	( (class_) >= JOB_KAGEROU				&& (class_) <= JOB_OBORO          ) || \
	  (class_) == JOB_REBELLION				|| (class_) == JOB_SUMMONER         || \
	  (class_) == JOB_BABY_SUMMONER			|| \
	( (class_) >= JOB_BABY_NINJA			&& (class_) <= JOB_BABY_REBELLION ) || \
	( (class_) >= JOB_BABY_STAR_GLADIATOR2	&& (class_) <= JOB_BABY_STAR_EMPEROR2 ) || \
	( (class_) >= JOB_DRAGON_KNIGHT			&& (class_) <= JOB_TROUVERE       ) || \
	( (class_) >= JOB_WINDHAWK2				&& (class_) <= JOB_IMPERIAL_GUARD2 ) || \
	( (class_) >= JOB_SKY_EMPEROR			&& (class_) <= JOB_SPIRIT_HANDLER ) || \
	  (class_) == JOB_SKY_EMPEROR2 \
)
#define pcdb_checkid(class_) pcdb_checkid_sub((unsigned int)class_)

// clientside display macros (values to the left/right of the "+")
#ifdef RENEWAL
	#define pc_leftside_atk(sd) ((sd)->battle_status.batk)
	#define pc_rightside_atk(sd) ((sd)->battle_status.watk + (sd)->battle_status.watk2 + (sd)->battle_status.eatk)
	#define pc_leftside_def(sd) ((sd)->battle_status.def2)
	#define pc_rightside_def(sd) ((sd)->battle_status.def)
	#define pc_leftside_mdef(sd) ((sd)->battle_status.mdef2)
	#define pc_rightside_mdef(sd) ((sd)->battle_status.mdef)
	#define pc_leftside_matk(sd) (status_base_matk_min(&(sd)->bl, status_get_status_data(&(sd)->bl), (sd)->status.base_level))
	#define pc_rightside_matk(sd) ((sd)->battle_status.rhw.matk+(sd)->battle_status.lhw.matk+(sd)->bonus.ematk)
#else
	#define pc_leftside_atk(sd) ((sd)->battle_status.batk + (sd)->battle_status.rhw.atk + (sd)->battle_status.lhw.atk)
	#define pc_rightside_atk(sd) ((sd)->battle_status.rhw.atk2 + (sd)->battle_status.lhw.atk2)
	#define pc_leftside_def(sd) ((sd)->battle_status.def)
	#define pc_rightside_def(sd) ((sd)->battle_status.def2)
	#define pc_leftside_mdef(sd) ((sd)->battle_status.mdef)
	#define pc_rightside_mdef(sd) ( (sd)->battle_status.mdef2 - ((sd)->battle_status.vit>>1) )
#define pc_leftside_matk(sd) \
    (\
    ((sd)->sc.data[SC_MAGICPOWER] && (sd)->sc.data[SC_MAGICPOWER]->val4) \
		?((sd)->battle_status.matk_min * 100 + 50) / ((sd)->sc.data[SC_MAGICPOWER]->val3+100) \
        :(sd)->battle_status.matk_min \
    )
#define pc_rightside_matk(sd) \
    (\
    ((sd)->sc.data[SC_MAGICPOWER] && (sd)->sc.data[SC_MAGICPOWER]->val4) \
		?((sd)->battle_status.matk_max * 100 + 50) / ((sd)->sc.data[SC_MAGICPOWER]->val3+100) \
        :(sd)->battle_status.matk_max \
    )
#endif

struct s_attendance_reward {
	t_itemid item_id;
	uint16 amount;
};

struct s_attendance_period {
	uint32 start;
	uint32 end;
	std::map<uint32, std::shared_ptr<struct s_attendance_reward>> rewards;
};

class AttendanceDatabase : public TypesafeYamlDatabase<uint32, s_attendance_period> {
public:
	AttendanceDatabase() : TypesafeYamlDatabase("ATTENDANCE_DB", 1) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
};

extern AttendanceDatabase attendance_db;

struct s_reputation{
	int64 id;
	std::string name;
	std::string variable;
	int64 minimum;
	int64 maximum;
#ifdef MAP_GENERATOR
	enum e_visibility {ALWAYS, NEVER, EXIST} visibility;
#endif
};

class ReputationDatabase : public TypesafeYamlDatabase<int64, s_reputation>{
public:
	ReputationDatabase() : TypesafeYamlDatabase( "REPUTATION_DB", 1 ){
#ifdef MAP_GENERATOR
	setGenerator(true);
#endif
	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode( const ryml::NodeRef& node ) override;
};

extern ReputationDatabase reputation_db;

struct s_reputationgroup {
	int64 id;
	std::string script_name;
	std::string name;
	std::vector<int64> reputations;
};

class ReputationGroupDatabase : public TypesafeYamlDatabase<int64, s_reputationgroup> {
public:
	ReputationGroupDatabase() : TypesafeYamlDatabase("REPUTATION_GROUP_DB", 1) {
#ifdef MAP_GENERATOR
	setGenerator(true);
#endif
	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
};

extern ReputationGroupDatabase reputationgroup_db;

struct s_statpoint_entry{
	uint16 level;
	uint32 statpoints;
	uint32 traitpoints;
};

class PlayerStatPointDatabase : public TypesafeCachedYamlDatabase<uint16, s_statpoint_entry>{
public:
	PlayerStatPointDatabase() : TypesafeCachedYamlDatabase("STATPOINT_DB", 2, 1) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
	void loadingFinished() override;

	// Additional
	uint32 pc_gets_status_point(uint16 level);
	uint32 get_table_point(uint16 level);
	uint32 pc_gets_trait_point(uint16 level);
	uint32 get_trait_table_point(uint16 level);
};

extern PlayerStatPointDatabase statpoint_db;

/// Enum of Summoner Power of 
enum e_summoner_power_type {
	SUMMONER_POWER_LAND = 0,
	SUMMONER_POWER_LIFE,
	SUMMONER_POWER_SEA,
};

void pc_set_reg_load(bool val);
int pc_class2idx(int class_);
int pc_get_group_level(map_session_data *sd);
int pc_get_group_id(map_session_data *sd);
bool pc_can_sell_item(map_session_data* sd, struct item * item, enum npc_subtype shoptype);
bool pc_can_give_items(map_session_data *sd);
bool pc_can_give_bounded_items(map_session_data *sd);
bool pc_can_trade_item(map_session_data *sd, int index);

bool pc_can_use_command(map_session_data *sd, const char *command, AtCommandType type);
bool pc_has_permission( map_session_data* sd, e_pc_permission permission );
bool pc_should_log_commands(map_session_data *sd);

void pc_setrestartvalue(map_session_data *sd, char type);
void pc_makesavestatus(map_session_data *sd);
void pc_respawn(map_session_data* sd, clr_type clrtype);
void pc_setnewpc(map_session_data *sd, uint32 account_id, uint32 char_id, int login_id1, t_tick client_tick, int sex, int fd);
bool pc_authok(map_session_data *sd, uint32 login_id2, time_t expiration_time, int group_id, struct mmo_charstatus *st, bool changing_mapservers);
void pc_authfail(map_session_data *sd);
void pc_reg_received(map_session_data *sd);
void pc_close_npc(map_session_data *sd,int flag);
TIMER_FUNC(pc_close_npc_timer);

void pc_setequipindex(map_session_data *sd);
uint8 pc_isequip(map_session_data *sd,int n);
int pc_equippoint(map_session_data *sd,int n);
int pc_equippoint_sub(map_session_data *sd, struct item_data* id);
void pc_setinventorydata(map_session_data *sd);

int pc_get_skillcooldown(map_session_data *sd, uint16 skill_id, uint16 skill_lv);
uint8 pc_checkskill(map_session_data *sd,uint16 skill_id);
e_skill_flag pc_checkskill_flag(map_session_data &sd, uint16 skill_id);
uint8 pc_checkskill_summoner(map_session_data *sd, e_summoner_power_type type);
uint8 pc_checkskill_imperial_guard(map_session_data *sd, short flag);
short pc_checkequip(map_session_data *sd,int pos,bool checkall=false);
bool pc_checkequip2(map_session_data *sd, t_itemid nameid, int min, int max);

void pc_scdata_received(map_session_data *sd);
void pc_check_expiration(map_session_data *sd);
TIMER_FUNC(pc_expiration_timer);
TIMER_FUNC(pc_global_expiration_timer);
void pc_expire_check(map_session_data *sd);

void pc_calc_skilltree(map_session_data *sd);
uint64 pc_calc_skilltree_normalize_job(map_session_data *sd);
void pc_clean_skilltree(map_session_data *sd);

#define pc_checkoverhp(sd) ((sd)->battle_status.hp == (sd)->battle_status.max_hp)
#define pc_checkoversp(sd) ((sd)->battle_status.sp == (sd)->battle_status.max_sp)

enum e_setpos{
	SETPOS_OK = 0,
	SETPOS_MAPINDEX = 1,
	SETPOS_NO_MAPSERVER = 2,
	SETPOS_AUTOTRADE = 3
};

enum e_setpos pc_setpos(map_session_data* sd, unsigned short mapindex, int x, int y, clr_type clrtype);
void pc_setsavepoint(map_session_data *sd, short mapindex,int x,int y);
char pc_randomwarp(map_session_data *sd,clr_type type,bool ignore_mapflag = false);
bool pc_memo(map_session_data* sd, int pos);

char pc_checkadditem(map_session_data *sd, t_itemid nameid, int amount);
uint8 pc_inventoryblank(map_session_data *sd);
short pc_search_inventory(map_session_data *sd, t_itemid nameid);
char pc_payzeny(map_session_data *sd, int zeny, enum e_log_pick_type type, map_session_data *tsd);
enum e_additem_result pc_additem(map_session_data *sd, struct item *item, int amount, e_log_pick_type log_type);
char pc_getzeny(map_session_data *sd, int zeny, enum e_log_pick_type type, map_session_data *tsd);
char pc_delitem(map_session_data *sd, int n, int amount, int type, short reason, e_log_pick_type log_type);

uint64 pc_generate_unique_id(map_session_data *sd);

//Bound items
int pc_bound_chk(TBL_PC *sd,enum bound_type type,int *idxlist);

// Special Shop System
int pc_paycash( map_session_data *sd, int price, int points, e_log_pick_type type );
int pc_getcash( map_session_data *sd, int cash, int points, e_log_pick_type type );

enum e_additem_result pc_cart_additem(map_session_data *sd,struct item *item_data,int amount,e_log_pick_type log_type);
void pc_cart_delitem(map_session_data *sd,int n,int amount,int type,e_log_pick_type log_type);
void pc_putitemtocart(map_session_data *sd,int idx,int amount);
void pc_getitemfromcart(map_session_data *sd,int idx,int amount);
int pc_cartitem_amount(map_session_data *sd,int idx,int amount);

bool pc_takeitem(map_session_data *sd,struct flooritem_data *fitem);
bool pc_dropitem(map_session_data *sd,int n,int amount);

bool pc_isequipped(map_session_data *sd, t_itemid nameid);
enum adopt_responses pc_try_adopt(map_session_data *p1_sd, map_session_data *p2_sd, map_session_data *b_sd);
bool pc_adoption(map_session_data *p1_sd, map_session_data *p2_sd, map_session_data *b_sd);

void pc_updateweightstatus(map_session_data *sd);

bool pc_addautobonus(std::vector<std::shared_ptr<s_autobonus>> &bonus, const char *script, short rate, unsigned int dur, uint16 atk_type, const char *o_script, unsigned int pos, bool onskill);
void pc_exeautobonus(map_session_data &sd, std::vector<std::shared_ptr<s_autobonus>> *bonus, std::shared_ptr<s_autobonus> autobonus);
TIMER_FUNC(pc_endautobonus);
void pc_delautobonus(map_session_data &sd, std::vector<std::shared_ptr<s_autobonus>> &bonus, bool restore);

void pc_bonus(map_session_data *sd, int type, int val);
void pc_bonus2(map_session_data *sd, int type, int type2, int val);
void pc_bonus3(map_session_data *sd, int type, int type2, int type3, int val);
void pc_bonus4(map_session_data *sd, int type, int type2, int type3, int type4, int val);
void pc_bonus5(map_session_data *sd, int type, int type2, int type3, int type4, int type5, int val);

enum e_addskill_type {
	ADDSKILL_PERMANENT			= 0,	///< Permanent skill. Remove the skill if level is 0
	ADDSKILL_TEMP				= 1,	///< Temporary skill. If player learned the skill and the given level is higher, level will be replaced and learned level will be palced in skill flag. `flag = learned + SKILL_FLAG_REPLACED_LV_0; learned_level = level;`
	ADDSKILL_TEMP_ADDLEVEL		= 2,	///< Like PCSKILL_TEMP, except the level will be stacked. `learned_level += level`. The flag is used to store original learned level
	ADDSKILL_PERMANENT_GRANTED	= 3,	///< Grant permanent skill, ignore skill tree and learned level
};

bool pc_skill(map_session_data *sd, uint16 skill_id, int level, enum e_addskill_type type);
bool pc_skill_plagiarism(map_session_data &sd, uint16 skill_id, uint16 skill_lv);
bool pc_skill_plagiarism_reset(map_session_data &sd, uint8 type);

int pc_insert_card(map_session_data *sd,int idx_card,int idx_equip);

int pc_identifyall(map_session_data *sd, bool identify_item);

bool pc_steal_item(map_session_data *sd,struct block_list *bl, uint16 skill_lv);
int pc_steal_coin(map_session_data *sd,struct block_list *bl);

int pc_modifybuyvalue(map_session_data*,int);
int pc_modifysellvalue(map_session_data*,int);

int pc_follow(map_session_data*, int); // [MouseJstr]
int pc_stop_following(map_session_data*);

unsigned int pc_maxbaselv(map_session_data *sd);
unsigned int pc_maxjoblv(map_session_data *sd);
bool pc_is_maxbaselv(map_session_data *sd);
bool pc_is_maxjoblv(map_session_data *sd);
int pc_checkbaselevelup(map_session_data *sd);
int pc_checkjoblevelup(map_session_data *sd);
void pc_gainexp(map_session_data *sd, struct block_list *src, t_exp base_exp, t_exp job_exp, uint8 exp_flag);
void pc_gainexp_disp(map_session_data *sd, t_exp base_exp, t_exp next_base_exp, t_exp job_exp, t_exp next_job_exp, bool lost);
void pc_lostexp(map_session_data *sd, t_exp base_exp, t_exp job_exp);
t_exp pc_nextbaseexp(map_session_data *sd);
t_exp pc_nextjobexp(map_session_data *sd);
int pc_need_status_point(map_session_data *,int,int);
int pc_maxparameterincrease(map_session_data*,int);
bool pc_statusup(map_session_data*,int,int);
int pc_statusup2(map_session_data*,int,int);
int pc_getstat(map_session_data *sd, int type);
int pc_setstat(map_session_data* sd, int type, int val);
int pc_need_trait_point(map_session_data *, int, int);
int pc_maxtraitparameterincrease(map_session_data*, int);
bool pc_traitstatusup(map_session_data*, int, int);
int pc_traitstatusup2(map_session_data*, int, int);
void pc_skillup(map_session_data*,uint16 skill_id);
int pc_allskillup(map_session_data*);
int pc_resetlvl(map_session_data*,int type);
int pc_resetstate(map_session_data*);
int pc_resetskill(map_session_data*, int);
int pc_resetfeel(map_session_data*);
int pc_resethate(map_session_data*);
bool pc_equipitem(map_session_data *sd, short n, int req_pos, bool equipswitch=false);
bool pc_unequipitem(map_session_data*,int,int);
int pc_equipswitch( map_session_data* sd, int index );
void pc_equipswitch_remove( map_session_data* sd, int index );
void pc_checkitem(map_session_data*);
void pc_check_available_item(map_session_data *sd, uint8 type);
int pc_useitem(map_session_data*,int);

int pc_skillatk_bonus(map_session_data *sd, uint16 skill_id);
int pc_sub_skillatk_bonus(map_session_data *sd, uint16 skill_id);
int pc_skillheal_bonus(map_session_data *sd, uint16 skill_id);
int pc_skillheal2_bonus(map_session_data *sd, uint16 skill_id);

void pc_damage(map_session_data *sd,struct block_list *src,unsigned int hp, unsigned int sp, unsigned int ap);
int pc_dead(map_session_data *sd,struct block_list *src);
void pc_revive(map_session_data *sd,unsigned int hp, unsigned int sp, unsigned int ap = 0);
bool pc_revive_item(map_session_data *sd);
void pc_heal(map_session_data *sd,unsigned int hp,unsigned int sp, unsigned int ap, int type);
int pc_itemheal(map_session_data *sd, t_itemid itemid, int hp,int sp);
int pc_percentheal(map_session_data *sd,int,int);
bool pc_jobchange(map_session_data *sd, int job, char upper);
void pc_setoption(map_session_data *,int type, int subtype = 0);
bool pc_setcart(map_session_data* sd, int type);
void pc_setfalcon(map_session_data* sd, int flag);
void pc_setriding(map_session_data* sd, int flag);
void pc_setmadogear(map_session_data* sd, bool flag, e_mado_type type = MADO_ROBOT);
void pc_changelook(map_session_data *,int,int);
void pc_equiplookall(map_session_data *sd);
void pc_set_costume_view(map_session_data *sd);

int64 pc_readparam(map_session_data *sd, int64 type);
bool pc_setparam(map_session_data *sd, int64 type, int64 val);
int64 pc_readreg(map_session_data *sd, int64 reg);
bool pc_setreg(map_session_data *sd, int64 reg, int64 val);
char *pc_readregstr(map_session_data *sd, int64 reg);
bool pc_setregstr(map_session_data *sd, int64 reg, const char *str);
int64 pc_readregistry(map_session_data *sd, int64 reg);
bool pc_setregistry(map_session_data *sd, int64 reg, int64 val);
char *pc_readregistry_str(map_session_data *sd, int64 reg);
bool pc_setregistry_str(map_session_data *sd, int64 reg, const char *val);

#define pc_readglobalreg(sd,reg) pc_readregistry(sd,reg)
#define pc_setglobalreg(sd,reg,val) pc_setregistry(sd,reg,val)
#define pc_readglobalreg_str(sd,reg) pc_readregistry_str(sd,reg)
#define pc_setglobalreg_str(sd,reg,val) pc_setregistry_str(sd,reg,val)
#define pc_readaccountreg(sd,reg) pc_readregistry(sd,reg)
#define pc_setaccountreg(sd,reg,val) pc_setregistry(sd,reg,val)
#define pc_readaccountregstr(sd,reg) pc_readregistry_str(sd,reg)
#define pc_setaccountregstr(sd,reg,val) pc_setregistry_str(sd,reg,val)
#define pc_readaccountreg2(sd,reg) pc_readregistry(sd,reg)
#define pc_setaccountreg2(sd,reg,val) pc_setregistry(sd,reg,val)
#define pc_readaccountreg2str(sd,reg) pc_readregistry_str(sd,reg)
#define pc_setaccountreg2str(sd,reg,val) pc_setregistry_str(sd,reg,val)

bool pc_setreg2(map_session_data *sd, const char *reg, int64 val);
int64 pc_readreg2(map_session_data *sd, const char *reg);

bool pc_addeventtimer(map_session_data *sd,int tick,const char *name);
bool pc_deleventtimer(map_session_data *sd,const char *name);
void pc_cleareventtimer(map_session_data *sd);
void pc_addeventtimercount(map_session_data *sd,const char *name,int tick);

int pc_calc_pvprank(map_session_data *sd);
TIMER_FUNC(pc_calc_pvprank_timer);

int pc_ismarried(map_session_data *sd);
bool pc_marriage(map_session_data *sd,map_session_data *dstsd);
bool pc_divorce(map_session_data *sd);
map_session_data *pc_get_partner(map_session_data *sd);
map_session_data *pc_get_father(map_session_data *sd);
map_session_data *pc_get_mother(map_session_data *sd);
map_session_data *pc_get_child(map_session_data *sd);

void pc_bleeding (map_session_data *sd, t_tick diff_tick);
void pc_regen (map_session_data *sd, t_tick diff_tick);

bool pc_setstand(map_session_data *sd, bool force);
bool pc_candrop(map_session_data *sd,struct item *item);

uint64 pc_jobid2mapid(unsigned short b_class);	// Skotlex
int pc_mapid2jobid(uint64 class_, int sex);	// Skotlex

const char * job_name(int class_);

struct s_skill_tree_entry {
	uint16 skill_id, max_lv;
	uint32 baselv, joblv;
	std::unordered_map<uint16, uint16> need;	/// skill_id, skill_lv
	bool exclude_inherit;	// exclude the skill from inherit when loading the table
};

struct s_skill_tree {
	std::vector<uint16> inherit_job;
	std::unordered_map<uint16, std::shared_ptr<s_skill_tree_entry>> skills;	/// skill_id, entry
};

class SkillTreeDatabase : public TypesafeYamlDatabase<uint16, s_skill_tree> {
public:
	SkillTreeDatabase() : TypesafeYamlDatabase("SKILL_TREE_DB", 1) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
	void loadingFinished() override;

	// Additional
	std::shared_ptr<s_skill_tree_entry> get_skill_data(int class_, uint16 skill_id);
};

extern SkillTreeDatabase skill_tree_db;

struct sg_data {
	short anger_id;
	short bless_id;
	short comfort_id;
	char feel_var[NAME_LENGTH];
	char hate_var[NAME_LENGTH];
	bool (*day_func)(void);
};
extern const struct sg_data sg_info[MAX_PC_FEELHATE];

void pc_set_bg_queue_timer(map_session_data *sd);
void pc_delete_bg_queue_timer(map_session_data *sd);

void pc_setinvincibletimer(map_session_data* sd, int val);
void pc_delinvincibletimer(map_session_data* sd);

void pc_addspiritball(map_session_data *sd,int interval,int max);
void pc_delspiritball(map_session_data *sd,int count,int type);
int pc_addsoulball(map_session_data *sd, int max);
int pc_delsoulball(map_session_data *sd, int count, bool type);
void pc_addservantball( map_session_data& sd, int count = 1 );
void pc_delservantball( map_session_data& sd, int count = 1 );
void pc_addabyssball( map_session_data& sd, int count = 1 );
void pc_delabyssball( map_session_data& sd, int count = 1 );

bool pc_addfame(map_session_data &sd, int count);
unsigned char pc_famerank(uint32 char_id, int job);
bool pc_set_hate_mob(map_session_data *sd, int pos, struct block_list *bl);

extern struct fame_list smith_fame_list[MAX_FAME_LIST];
extern struct fame_list chemist_fame_list[MAX_FAME_LIST];
extern struct fame_list taekwon_fame_list[MAX_FAME_LIST];

void pc_readdb(void);
void do_init_pc(void);
void do_final_pc(void);

// timer for night.day
extern int day_timer_tid;
extern int night_timer_tid;
TIMER_FUNC(map_day_timer); // by [yor]
TIMER_FUNC(map_night_timer); // by [yor]

// Rental System
void pc_inventory_rentals(map_session_data *sd);
void pc_inventory_rental_clear(map_session_data *sd);
void pc_inventory_rental_add(map_session_data *sd, unsigned int seconds);

int pc_read_motd(void); // [Valaris]
int pc_disguise(map_session_data *sd, int class_);
bool pc_isautolooting(map_session_data *sd, t_itemid nameid);

void pc_overheat(map_session_data &sd, int16 heat);

void pc_itemcd_do(map_session_data *sd, bool load);
uint8 pc_itemcd_add(map_session_data *sd, struct item_data *id, t_tick tick, unsigned short n);
uint8 pc_itemcd_check(map_session_data *sd, struct item_data *id, t_tick tick, unsigned short n);

int pc_load_combo(map_session_data *sd);

void pc_addspiritcharm(map_session_data *sd, int interval, int max, int type);
void pc_delspiritcharm(map_session_data *sd, int count, int type);

void pc_baselevelchanged(map_session_data *sd);

void pc_damage_log_add(map_session_data *sd, int id);
void pc_damage_log_clear(map_session_data *sd, int id);

enum e_BANKING_DEPOSIT_ACK : uint8;
enum e_BANKING_WITHDRAW_ACK : uint8;
enum e_BANKING_DEPOSIT_ACK pc_bank_deposit(map_session_data *sd, int money);
enum e_BANKING_WITHDRAW_ACK pc_bank_withdraw(map_session_data *sd, int money);

void pc_crimson_marker_clear(map_session_data *sd);

void pc_show_version(map_session_data *sd);

TIMER_FUNC(pc_bonus_script_timer);
void pc_bonus_script(map_session_data *sd);
struct s_bonus_script_entry *pc_bonus_script_add(map_session_data *sd, const char *script_str, t_tick dur, enum efst_type icon, uint16 flag, uint8 type);
void pc_bonus_script_clear(map_session_data *sd, uint32 flag);

void pc_cell_basilica(map_session_data *sd);

short pc_get_itemgroup_bonus(map_session_data* sd, t_itemid nameid, std::vector<s_item_bonus>& bonuses);
short pc_get_itemgroup_bonus_group(map_session_data* sd, uint16 group_id, std::vector<s_item_bonus>& bonuses);

bool pc_is_same_equip_index(enum equip_index eqi, short *equip_index, short index);
/// Check if player is Taekwon Ranker and the level is >= 90 (battle_config.taekwon_ranker_min_lv)
#define pc_is_taekwon_ranker(sd) (((sd)->class_&MAPID_UPPERMASK) == MAPID_TAEKWON && (sd)->status.base_level >= battle_config.taekwon_ranker_min_lv && pc_famerank((sd)->status.char_id,MAPID_TAEKWON))

TIMER_FUNC(pc_autotrade_timer);

void pc_validate_skill(map_session_data *sd);

void pc_show_questinfo(map_session_data *sd);
void pc_show_questinfo_reinit(map_session_data *sd);

bool pc_job_can_entermap(enum e_job jobid, int m, int group_lv);

void pc_job_bonus(map_session_data *sd);

#if defined(RENEWAL_DROP) || defined(RENEWAL_EXP)
uint16 pc_level_penalty_mod( map_session_data* sd, e_penalty_type type, std::shared_ptr<s_mob_db> mob, mob_data* md = nullptr );
#endif

bool pc_attendance_enabled();
int32 pc_attendance_counter( map_session_data* sd );
void pc_attendance_claim_reward( map_session_data* sd );

void pc_jail(map_session_data &sd, int32 duration = INT_MAX);

// Captcha Register
void pc_macro_captcha_register(map_session_data &sd, uint16 image_size, char captcha_answer[CAPTCHA_ANSWER_SIZE]);
void pc_macro_captcha_register_upload(map_session_data & sd, uint16 upload_size, char *upload_data);

// Macro Detector
TIMER_FUNC(pc_macro_detector_timeout);
void pc_macro_detector_process_answer(map_session_data &sd, char captcha_answer[CAPTCHA_ANSWER_SIZE]);
void pc_macro_detector_disconnect(map_session_data &sd);

// Macro Reporter
void pc_macro_reporter_area_select(map_session_data &sd, const int16 x, const int16 y, const int8 radius);
void pc_macro_reporter_process(map_session_data &sd, int32 reporter_account_id = -1);

#ifdef MAP_GENERATOR
void pc_reputation_generate();
#endif

TIMER_FUNC(pc_goldpc_update);

#endif /* PC_HPP */
