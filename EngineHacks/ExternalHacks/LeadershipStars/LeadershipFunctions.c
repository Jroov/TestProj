#include "include\gbafe.h"

// Leadership Stars FE8. Hack by Zeta/Gilgamesh
// Requires FE-CLIB
// Free to use/modify

#define MAX_BLUE_UNITS 20
#define MAX_GREEN_UNITS 20
#define MAX_RED_UNITS 50

extern struct Unit gUnitArrayRed[]; //! FE8U = 0x202CFBC
extern struct Unit gUnitArrayGreen[]; //! FE8U = 0x202DDCC
extern uint8_t gLeadershipUnitListOut[];

static int LeadershipTest(Unit* unit, Unit* other, int param);


struct Leadership
{
	u8 UnitID;
	u8 LeadershipStars;
};

extern struct Leadership LeadershipTable[];

extern u8 AllyStarHitBonus;
extern u8 AllyStarAvoidBonus;

extern u8 EnemyStarHitBonus;
extern u8 EnemyStarAvoidBonus;

extern u8 NPCStarHitBonus;
extern u8 NPCStarAvoidBonus;

extern u8 CancelOutOpposingLeadership;

signed char GetFactionLeadershipCount(u8 faction)
{
	signed char total = 0;
	Unit *unitArray = gUnitArrayBlue;
	int maxUnits = MAX_BLUE_UNITS;
	
	if (faction == FACTION_RED)
	{
		unitArray = gUnitArrayRed;
		maxUnits = MAX_RED_UNITS;
	}
	if (faction == FACTION_GREEN)
	{
		unitArray = gUnitArrayGreen;
		maxUnits = MAX_GREEN_UNITS;		
	}
	
	// go through the unit array for the appropriate faction
	for (int x = 0; x < maxUnits; x++)
	{
		// make sure the unit is alive
		if (unitArray[x].pCharacterData != NULL && !(unitArray[x].state & US_UNAVAILABLE))
		{
			// now check through the leadership table to see if they're on it
			for (int y = 0; LeadershipTable[y].UnitID != 0; y++)
			{
				if (LeadershipTable[y].UnitID == unitArray[x].pCharacterData->number)
				{
					total += LeadershipTable[y].LeadershipStars;
					break; // no need to go through the rest of the leadership table
				}
			}
		}
	}
	
	return total;
}

/*
signed char GetFactionLeadershipCount(u8 faction)
{
	signed char total = 0;
	for (int x = 0; LeadershipTable[x].UnitID != 0; x++)
	{
		Unit *potentialLeader = GetUnitByCharId(LeadershipTable[x].UnitID);
		if (potentialLeader != NULL && !(potentialLeader->state & US_UNAVAILABLE) && faction == UNIT_FACTION(potentialLeader)) // make sure they exist, are on the field and are on the same faction
		{
			total += LeadershipTable[x].LeadershipStars;
		}
	}
	
	return total;
}
*/

void CalculateHitAvoidBonus(BattleUnit* bunit, signed char leadership)
{
	if (UNIT_FACTION(&bunit->unit) == FACTION_BLUE)
	{
		bunit->battleHitRate += leadership * AllyStarHitBonus;
		bunit->battleAvoidRate += leadership * AllyStarAvoidBonus;
	}
		else if (UNIT_FACTION(&bunit->unit) == FACTION_RED)
		{
			bunit->battleHitRate += leadership * EnemyStarHitBonus;
			bunit->battleAvoidRate += leadership * NPCStarAvoidBonus;
		}
	else
	{
		bunit->battleHitRate += leadership * NPCStarHitBonus;
		bunit->battleAvoidRate += leadership * NPCStarAvoidBonus;
	}
}

//This function is fine
uint8_t LeadershipRangeCheck(Unit* unit, int param) {
	int count = 0;
	
	//checking every unit and adding them to the list of units to be buffed
	for (int i = 0; i < 0x100; ++i) {
		Unit* other = gUnitLookup[i];
		
		if (!other)
			continue;

		if (unit->index == i)
			continue;

		if (!other->pCharacterData)
			continue;

		if (other->state & (US_RESCUED | US_NOT_DEPLOYED | US_DEAD | 0x00010000))
			continue;
		
		int distance = absolute(other->xPos - unit->xPos)
		             + absolute(other->yPos - unit->yPos);
		
		if ((distance <= 3) && LeadershipTest(unit, other, param))
			gLeaderhsipUnitListOut[count++] = i;
	}

	//terminating the list
	gAuraUnitListOut[count] = 0;

	return gLeadershipUnitListOut;
}

//Testing skill on one of the two units?? idk
int LeadershipTest(Unit* unit, Unit* other, int param) {
	//checking allegiance function
	const int(*pAllegianceChecker)(int, int) = ((param & 1) ? AreUnitsAllied : IsSameAllegience);

	if (param == 4)
		return LeadershipTester(other);
	
	if (param > 4)
		return 0;

	//checking allegiance using the previously defined function
	int check = pAllegianceChecker(unit->index, other->index);

	if (param & 2)
		check = !check;

	return check && LeadershipTester(other);
}

bool LeadershipTester(Unit* unit) {
	if(GetLeadershipStarCount(unit) !- 0xFF){
		return TRUE;
	}
	return FALSE;
}

void ApplyLeadershipBonus(BattleUnit *bunitOne, BattleUnit *bunitTwo)
{
	signed char unitOneLeadership = GetLeadershipStarCount(&bunitOne->unit);
	uint8_t LeadershipList = LeadershipRangeCheck(&bunitOne->unit, UNIT_FACTION(&bunitOne->unit))
	if (unitOneLeadership != 0xFF){
		for(int i = 0; LeadershipList[i] != 0; i++){
			CalculateHitAvoidBonus(LeadershipList[i], unitOneLeadership)
		}
	}

	//unused but I don't want to change that much in the rest of how this works, just going to turn off canceloutopposingleadership
	signed char unitTwoLeadership = GetFactionLeadershipCount(UNIT_FACTION(&bunitTwo->unit));
	
	if (CancelOutOpposingLeadership)
		unitOneLeadership -= unitTwoLeadership;
	//end of unused
	
}

// gets the leadership star count for a single unit
u8 GetLeadershipStarCount(Unit *unit)
{
	for (int x = 0; LeadershipTable[x].UnitID != 0; x++)
	{
		if (unit->pCharacterData->number == LeadershipTable[x].UnitID)
			return LeadershipTable[x].LeadershipStars;
	}
	
	return 0xFF;
}