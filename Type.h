#pragma once

enum SOLDIER_CLASS
{
	SC_KNIGHT,
	SC_CAVALRY,
	SC_ARCHER,
	SC_END
};

enum TEAM_TYPE
{
	TT_NONE,
	TT_PLAYER,
	TT_ALLY,
	TT_ENEMY,
	TT_END
};

enum MAP_WORLD_TILE
{
	MWT_GROUND ='0',
	MWT_WALL = '1',
	MWT_WATER = '2',
	MWT_PCASTLE = '3',
	MWT_PCASTLEAREA = '4',
	MWT_ECASTLE = '5',
	MWT_ECASTLEAREA = '6',
	MWT_SHOP = '7',
	MWT_PLAYERPOS = '9',
	MWT_END
};

enum MAP_BATTLE_TILE
{
	MBT_GROUND = '0',
	MBT_WALL = '1',
	MBT_WATER = '2',
	MBT_MOUNTAIN = '3',
	MBT_ESOLDIER_K = '4', // 기사
	MBT_ESOLDIER_C = '5', // 기병
	MBT_ESOLDIER_A = '6', // 궁병
	MBT_END
};

enum MAP_CASTLE_TILE
{
	MCT_GROUND = '0',
	MCT_WALL = '1',
	MCT_WATER = '2',
	MCT_DOOR = '3',
	MCT_KEY = '4',
	MCT_OBSTACLE = '5',
	MCT_DEST = '8',
	MCT_START = '9',
	MCT_END
};

enum Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};



enum MAP_MODE
{
	MM_WORLDMAP,
	MM_CASTLEMAP,
	MM_BATTLEMAP
};

// fore, back color
int aMapTileColor[2][7] = 
{
	{ BROWN, WHITE, BLUE, GREEN, LIGHTGREEN, RED, RED },
	{ BROWN, BLACK, BLUE, LIGHTGRAY, LIGHTGREEN, LIGHTGRAY, LIGHTRED }
};

// fore, back color
int aCastleTileColor[2][6] =
{
	{ BROWN, WHITE, BLUE, YELLOW, MAGENTA, RED },
	{ BROWN, BROWN, BLUE, BLACK, BROWN, BROWN }
};

// 캐슬 스테이지 이름
const char* FileName[3] = { "CastleStage1.txt", "CastleStage1.txt", "CastleStage1.txt" };