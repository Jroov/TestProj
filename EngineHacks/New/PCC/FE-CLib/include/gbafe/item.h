#ifndef GBAFE_ITEM_H
#define GBAFE_ITEM_H

// bmitem.c

typedef struct Item Item;

struct Item
{
	u8 number;
	u8 durability;
};

typedef struct ItemData ItemData;

typedef struct ItemStatBonuses ItemStatBonuses;

struct ItemStatBonuses
{
	s8 hpBonus;
	s8 powBonus;
	s8 sklBonus;
	s8 spdBonus;
	s8 defBonus;
	s8 resBonus;
	s8 lckBonus;
	s8 movBonus;
	s8 conBonus;
	s8 magBonus;
	s8 hpGrowthBonus;
	s8 powGrowthBonus;
	s8 sklGrowthBonus;
	s8 spdGrowthBonus;
	s8 defGrowthBonus;
	s8 resGrowthBonus;
	s8 lckGrowthBonus;
	s8 magGrowthBonus;
	s8 movGrowthBonus;
	s8 conGrowthBonus;

};

struct ItemData
{
	/* 00 */ u16 nameTextId;
	/* 02 */ u16 descTextId;
	/* 04 */ u16 useDescTextId;

	/* 06 */ u8  number;
	/* 07 */ u8  weaponType;

	/* 08 */ u32 attributes;

	/* 0C */ const struct ItemStatBonuses* pStatBonuses;
	/* 10 */ const u8* pEffectiveness;

	/* 14 */ u8  maxUses;

	/* 15 */ u8  might;
	/* 16 */ u8  hit;
	/* 17 */ u8  weight;
	/* 18 */ u8  crit;

	/* 19 */ u8 encodedRange;

	/* 1A */ u16 costPerUse;
	/* 1C */ u8  weaponRank;
	/* 1D */ u8  iconId;
	/* 1E */ u8  useEffectId;
	/* 1F */ u8  weaponEffectId;
	/* 20 */ u8  weaponExp;
	/* 21 */ u8  debuff;
	/* 22 */ u8  IERExtraByte;
	/* 23 */ u8  skill;
};

enum
{
	// Item attributes

	IA_NONE		   = 0,

	IA_WEAPON         = (1 << 0),
	IA_MAGIC          = (1 << 1),
	IA_STAFF          = (1 << 2),
	IA_UNBREAKABLE    = (1 << 3),
	IA_UNSELLABLE     = (1 << 4),
	IA_BRAVE          = (1 << 5),
	IA_MAGICDAMAGE    = (1 << 6),
	IA_UNCOUNTERABLE  = (1 << 7),
	IA_REVERTTRIANGLE = (1 << 8),
	IA_HAMMERNE       = (1 << 9), // Defined as Hammerne effect in FE6 Nightmare module, but as ??? in FE7 & FE8.
	IA_LOCK_3         = (1 << 10), // Dragons or Monster depending of game
	IA_LOCK_1         = (1 << 11),
	IA_LOCK_2         = (1 << 12),
	IA_LOCK_0         = (1 << 13), // King in FE6
	IA_NEGATE_FLYING  = (1 << 14),
	IA_NEGATE_CRIT    = (1 << 15),
	IA_UNUSABLE       = (1 << 16),
	IA_NEGATE_DEFENSE = (1 << 17),
	IA_LOCK_4         = (1 << 18),
	IA_LOCK_5         = (1 << 19),
	IA_LOCK_6         = (1 << 20),
	IA_LOCK_7         = (1 << 21),

	// Helpers
	IA_REQUIRES_WEXP = (IA_WEAPON | IA_STAFF),
	IA_LOCK_ANY = (IA_LOCK_0 | IA_LOCK_1 | IA_LOCK_2 | IA_LOCK_3 | IA_LOCK_4 | IA_LOCK_5 | IA_LOCK_6 | IA_LOCK_7 | IA_UNUSABLE)
};

enum
{
	ITYPE_SWORD = 0,
	ITYPE_LANCE = 1,
	ITYPE_AXE   = 2,
	ITYPE_BOW   = 3,
	ITYPE_STAFF = 4,
	ITYPE_ANIMA = 5,
	ITYPE_LIGHT = 6,
	ITYPE_DARK  = 7,
	ITYPE_BLLST = 8,
	ITYPE_ITEM  = 9,
	ITYPE_DRAGN = 10,

	ITYPE_12	= 12,
};

enum
{
	WPN_EFFECT_NONE	= 0,
	WPN_EFFECT_POISON  = 1,
	WPN_EFFECT_HPDRAIN = 2,
	WPN_EFFECT_HPHALVE = 3,
	WPN_EFFECT_DEVIL   = 4,
	WPN_EFFECT_PETRIFY = 5,
	WPN_EFFECT_CANNOTDOUBLE = 0xC,
};

enum
{
	// Unit ranges are a (sometimes) weirdly hardcoded.
	// A flagset value is used to represent the combined ranges of a unit's usable items
	// That's what those "reaches" bits are for.

	REACH_NONE   = 0,

	REACH_RANGE1 = (1 << 0),
	REACH_RANGE2 = (1 << 1),
	REACH_RANGE3 = (1 << 2),
	REACH_TO10   = (1 << 3),
	REACH_TO15   = (1 << 4),
	REACH_MAGBY2 = (1 << 5),
};

enum
{
	// Weapon level identifiers

	WPN_LEVEL_0 = 0,
	WPN_LEVEL_E = 1,
	WPN_LEVEL_D = 2,
	WPN_LEVEL_C = 3,
	WPN_LEVEL_B = 4,
	WPN_LEVEL_A = 5,
	WPN_LEVEL_S = 6,
};

enum
{
	// Weapon exp needed to have a given weapon level

	WPN_EXP_0 = 0,
	WPN_EXP_E = 1,
	WPN_EXP_D = 51,
	WPN_EXP_C = 101,
	WPN_EXP_B = 151,
	WPN_EXP_A = 201,
	WPN_EXP_S = 251,
};

#define ITEM_SLOT_NONE (-1)
#define ITEM_SLOT_COUNT (5)

extern const ItemData gItemData[];

char* GetItemNameWithArticle(int item, int capitalized); //! FE8U = (0x0801618C+1)

int GetItemHpBonus(int item); //! FE8U = (0x080163F0+1)
int GetItemPowBonus(int item); //! FE8U = (0x08016420+1)
int GetItemSklBonus(int item); //! FE8U = (0x08016450+1)
int GetItemSpdBonus(int item); //! FE8U = (0x08016480+1)
int GetItemDefBonus(int item); //! FE8U = (0x080164B0+1)
int GetItemResBonus(int item); //! FE8U = (0x080164E0+1)
int GetItemLckBonus(int item); //! FE8U = (0x08016510+1)

int MakeNewItem(u8 id); //! FE8U = (0x08016540+1)



void DrawItemMenuLine(struct TextHandle* text, int item, s8 isGrayed, u16* mapOut);
void DrawItemMenuLineLong(struct TextHandle* text, int item, s8 isGrayed, u16* mapOut);
void DrawItemMenuLineNoColor(struct TextHandle* text, int item, u16* mapOut);
void DrawItemStatScreenLine(struct TextHandle* text, int item, int nameColor, u16* mapOut);

Item GetItemAfterUse(int item); //! FE8U = (0x08016AEC+1)



int IsItemCoveringRange(int item, int range); //! FE8U = (0x08016B8C+1)



char* GetItemDisplayRangeString(int item); //! FE8U = (0x08016CC0+1)
int GetWeaponLevelFromExp(int rank); //! FE8U = (0x08016D5C+1)
char* GetItemDisplayRankString(int item); //! FE8U = (0x08016D94+1)

char* GetWeaponTypeDisplayString(int wtype); //! FE8U = (0x08016E20+1)

void GetWeaponExpProgressState(int wrank, int* valOut, int* maxOut); //! FE8U = (0x08016E50+1)

int IsItemDanceRing(int item); //! FE8U = (0x08016EC8+1)


int IsItemStealable(int item); //! FE8U = 0x8017055
int IsItemHammernable(int item); //! FE8U = 0x8017081

u32 GetItemReachBits(int item); //! FE8U = 0x80170D5


int GetConvoyItemCostSum(void); //! FE8U = 0x801737D

void SetItemUnsealedForCharacter(int item, u8 charId);


u8 GetItemIndex(int item); //! FE8U = 0x80174ED
char* GetItemName(int item); //! FE8U = 0x80174F5
int GetItemDescId(int item); //! FE8U = 0x8017519
int GetItemUseDescId(int item); //! FE8U = 0x8017531
int GetItemType(int item); //! FE8U = 0x8017549
u32 GetItemAttributes(int item); //! FE8U = 0x801756D
int GetItemUses(int item); //! FE8U = 0x8017585
int GetItemMaxUses(int item); //! FE8U = 0x80175B1
int GetItemMight(int item); //! FE8U = 0x80175DD
int GetItemHit(int item); //! FE8U = 0x80175F5
int GetItemWeight(int item); //! FE8U = 0x801760D
int GetItemCrit(int item); //! FE8U = 0x8017625
int GetItemCost(int item); //! FE8U = 0x801763D
int GetItemMinRange(int item); //! FE8U = 0x801766D
int GetItemMaxRange(int item); //! FE8U = 0x8017685
int GetItemEncodedRange(int item); //! FE8U = 0x80176A1
int GetItemRequiredExp(int item); //! FE8U = 0x80176B9
u8* GetItemEffectiveness(int item); //! FE8U = 0x80176D1
struct ItemStatBonuses* GetItemStatBonuses(int item); //! FE8U = 0x80176E9
int GetItemIconId(int item); //! FE8U = 0x8017701
int GetItemWeaponEffect(int item); //! FE8U = 0x8017725
int GetItemUseEffect(int item); //! FE8U = 0x801773D
int GetItemCostPerUse(int item); //! FE8U = 0x8017755
int GetItemMaxCost(int item); //! FE8U = 0x801776D
int GetItemAwardedExp(int item); //! FE8U = 0x8017799

const ItemData* GetItemData(int itemId); //! FE8U = 0x80177B1

// TODO: move elsewhere?
Item* GetConvoyItemArray(void);

enum { CONVOY_ITEM_COUNT = 100 };

#endif // GBAFE_ITEM_H
