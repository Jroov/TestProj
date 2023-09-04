#include "global.h"

#include "constants/items.h"
#include "constants/classes.h"
#include "constants/characters.h"
#include "constants/terrains.h"

#include "bmitem.h"
#include "bmunit.h"
#include "bmmap.h"
#include "bmidoten.h"
#include "bmbattle.h"
#include "bmreliance.h"
#include "bmtrick.h"
#include "monstergen.h"
#include "prepscreen.h"
#include "uiselecttarget.h"
#include "bmdifficulty.h"
#include "cp_utility.h"
#include "bmudisp.h"
#include "bmsave.h"
#include "bmtarget.h"

void ForEachAdjacentUnit(int x, int y, void(*func)(struct Unit* unit));

extern u8 HighGroundTerrains[];
extern u8 ObscuredTerrains[];
bool TerrainIsHighGround(u8 terrainID);

int GetUnitFogViewRange(struct Unit* unit) {
    int result = gPlaySt.chapterVisionRange;

    if (UNIT_CATTRIBUTES(unit) & CA_THIEF)
        result += 2;
		
	if (TerrainIsHighGround(gBmMapTerrain[unit->yPos][unit->xPos])) 
		result += 4;

    return result + unit->torchDuration;
}

bool TerrainIsHighGround(u8 terrainID) {
	int i = 0;
	while (HighGroundTerrains[i] != 0xFF) {
		if (HighGroundTerrains[i] == terrainID) return true;
		i++;
	}
	return false;
}

bool TerrainIsObscured(u8 terrainID) {
	int i = 0;
	while (ObscuredTerrains[i] != 0xFF) {
		if (ObscuredTerrains[i] == terrainID) return true;
		i++;
	}
	return false;
}


void ClearObscuredTerrainFromFogMap() {
	//for each position on the terrain map within map size,
	//if the value is not 0, compare the terrain type to the obscured terrain list
	//if present, check if there are blue units on or adjacent to that position
	//if not, set the value to 0
	/* 
	 */
	
	
	//may be less work to do this in 2 passes
	//rather than checking for adjacent units for every hidden tile, check for adjacent hidden tiles for every unit
	
	//so first, if the spot is visible but the terrain is obscured, obscure vision on the tile, for each tile on the map
	
	
	int curX = 0;
	int curY = 0;
	
	while (curY < gBmMapSize.y) {
		curX = 0;
		while (curX < gBmMapSize.x) {
			if ( gBmMapFog[curY][curX] != 0 && TerrainIsObscured(gBmMapTerrain[curY][curX])) gBmMapFog[curY][curX] = 0;
			curX++;
		}
	curY++;
	}
	
	//next, for each player unit on the unit map(? deployed?) make obscured terrain they're on or adjacent to visible again
	
	int i = -1;
	while (i < 63) { //unit cap failsafe exit
		i++;
		struct Unit* curUnit = GetUnit(i);
		if (curUnit->pCharacterData == 0) break; //exit when we run out of filled units
		if (curUnit->state & US_NOT_DEPLOYED != 0) continue; //skip unit if undeployed
		
		if (gBmMapFog[curUnit->yPos][curUnit->xPos] == 0 && TerrainIsObscured(gBmMapTerrain[curUnit->yPos][curUnit->xPos])) gBmMapFog[curUnit->yPos][curUnit->xPos] = 2;
		if (curUnit->yPos-1 >= 0) {
			if (gBmMapFog[curUnit->yPos-1][curUnit->xPos] == 0 && TerrainIsObscured(gBmMapTerrain[curUnit->yPos-1][curUnit->xPos])) gBmMapFog[curUnit->yPos-1][curUnit->xPos] = 1;
		}
		if (curUnit->xPos-1 >= 0) {
			if (gBmMapFog[curUnit->yPos][curUnit->xPos-1] == 0 && TerrainIsObscured(gBmMapTerrain[curUnit->yPos][curUnit->xPos-1])) gBmMapFog[curUnit->yPos][curUnit->xPos-1] = 1;
		}
		if (curUnit->yPos+1 < gBmMapSize.y) {
			if (gBmMapFog[curUnit->yPos+1][curUnit->xPos] == 0 && TerrainIsObscured(gBmMapTerrain[curUnit->yPos+1][curUnit->xPos])) gBmMapFog[curUnit->yPos+1][curUnit->xPos] = 1;
		}
		if (curUnit->xPos+1 < gBmMapSize.x) {
			if (gBmMapFog[curUnit->yPos][curUnit->xPos+1] == 0 && TerrainIsObscured(gBmMapTerrain[curUnit->yPos][curUnit->xPos+1])) gBmMapFog[curUnit->yPos][curUnit->xPos+1] = 1;
		}
	}	
}
	