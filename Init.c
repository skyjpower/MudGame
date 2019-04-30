#pragma once
#include "Init.h"
#include "Global.h"

int Init(PPLAYER pPlayer, PECASTLE* ppECastle)
{

	// 커서 깜빡임 없애주는 코드
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
	{
		ppECastle[i] = (PECASTLE)malloc(sizeof(ECASTLE));
		ppECastle[i]->m_nReward = 0;
		ppECastle[i]->m_tStartPos.x = 0;
		ppECastle[i]->m_tStartPos.y = 0;
		ppECastle[i]->m_tDestPos.x = 0;
		ppECastle[i]->m_tDestPos.y = 0;
		ppECastle[i]->m_tKeyPos.x = 0;
		ppECastle[i]->m_tKeyPos.y = 0;

		// 문 리스트 초기화
		ppECastle[i]->m_tDoorPosList = (PDLIST)malloc(sizeof(DLIST));
		ppECastle[i]->m_tDoorPosList->m_pBegin = (PDOOR)malloc(sizeof(DOOR));
		ppECastle[i]->m_tDoorPosList->m_pEnd = (PDOOR)malloc(sizeof(DOOR));
		ppECastle[i]->m_tDoorPosList->m_pBegin->m_pNext = ppECastle[i]->m_tDoorPosList->m_pEnd;
		ppECastle[i]->m_tDoorPosList->m_pEnd->m_pPrev = ppECastle[i]->m_tDoorPosList->m_pBegin;
		ppECastle[i]->m_tDoorPosList->m_nSize = 0;
		ppECastle[i]->m_tDoorPosList->m_pBegin->m_pPrev = NULL;
		ppECastle[i]->m_tDoorPosList->m_pEnd->m_pNext = NULL;

		// 지역 리스트 초기화
		ppECastle[i]->m_tAreaPosList = (PALIST)malloc(sizeof(ALIST));
		ppECastle[i]->m_tAreaPosList->m_pBegin = (PAREA)malloc(sizeof(AREA));
		ppECastle[i]->m_tAreaPosList->m_pEnd = (PAREA)malloc(sizeof(AREA));
		ppECastle[i]->m_tAreaPosList->m_pBegin->m_pNext = ppECastle[i]->m_tAreaPosList->m_pEnd;
		ppECastle[i]->m_tAreaPosList->m_pEnd->m_pPrev = ppECastle[i]->m_tAreaPosList->m_pBegin;
		ppECastle[i]->m_tDoorPosList->m_nSize = 0;
		ppECastle[i]->m_tAreaPosList->m_pBegin->m_pPrev = NULL;
		ppECastle[i]->m_tAreaPosList->m_pEnd->m_pNext = NULL;

		memset(ppECastle[i]->m_aECastleMap, 0, sizeof(ppECastle[i]->m_aECastleMap));
	}

	// 맵 불러오기
	if (!LoadWorldMap(ppECastle))
	{
		puts("맵을 불러오는 데 실패했습니다.");
		return 0;
	}

	// 플레이어 초기화
	pPlayer->m_tWorldPos.x = tStartPos.x;
	pPlayer->m_tWorldPos.y = tStartPos.y;
	pPlayer->m_tPos.x = 0;
	pPlayer->m_tPos.y = 0;
	pPlayer->m_nHaveShip = 0;
	pPlayer->m_nMoney = 100;
	pPlayer->m_nColor = YELLOW;
	strcpy(pPlayer->m_cShape, "●");

	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
		pPlayer->pSoldiers[i] = NULL;

	if (!CreatePlayerSoldier(pPlayer))
	{
		puts("플레이어의 병사들을 초기화 중 오류가 났습니다.");
		return 0;
	}

	// 각 적 성의 영토를 리스트에 저장
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
		CheckEnemyCastleArea(ppECastle[i]);

	// 배틀 맵 초기화


	return 1;
}

void CheckEnemyCastleArea(PECASTLE pECastle)
{
	int xDir[4] = { 1, -1, 0, 0 };
	int yDir[4] = { 0, 0, 1, -1 };
	int visit[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };

	POINT queue[QUEUE_MAX_SIZE] = { 0 };
	int nFront = 0, nRear = 1;
	POINT tStart = { pECastle->m_tWorldPos.x, pECastle->m_tWorldPos.y };
	visit[pECastle->m_tWorldPos.x][pECastle->m_tWorldPos.y] = 1;

	queue[nFront] = tStart;

	while (nFront != nRear)
	{
		int qSize = nRear - nFront;
		for (int i = 0; i < qSize; ++i)
		{
			int cur_x = queue[nFront].x;
			int cur_y = queue[nFront].y;
			// pop
			nFront = (nFront + 1) % QUEUE_MAX_SIZE;
			for (int j = 0; j < 4; ++j)
			{
				int next_x = cur_x + xDir[j];
				int next_y = cur_y + yDir[j];

				if (next_x < 0 || next_y < 0 || next_x >= MAP_HEIGHT_MAX || next_y >= MAP_WIDTH_MAX) continue;
				if (aWorldMap[next_x][next_y] != MWT_ECASTLEAREA) continue;
				if (visit[next_x][next_y]) continue;

				POINT tmp = { next_x, next_y };
				visit[next_x][next_y] = 1;
				queue[nRear++] = tmp;

				PAREA pArea = (PAREA)malloc(sizeof(AREA));
				pArea->m_tPos.x = next_x;
				pArea->m_tPos.y = next_y;
				pArea->m_beOccupied = 0;
				
				// 첫 노드인 경우
				if (pECastle->m_tAreaPosList->m_pEnd->m_pPrev == pECastle->m_tAreaPosList->m_pBegin)
				{
					pECastle->m_tAreaPosList->m_pBegin->m_pNext = pArea;
					pArea->m_pPrev = pECastle->m_tAreaPosList->m_pBegin;

					pECastle->m_tAreaPosList->m_pEnd->m_pPrev = pArea;
					pArea->m_pNext = pECastle->m_tAreaPosList->m_pEnd;
				}
				// 노드가 한 개라도 있는 경우
				else
				{
					PAREA pPrev = pECastle->m_tAreaPosList->m_pEnd->m_pPrev;

					pPrev->m_pNext = pArea;
					pArea->m_pPrev = pPrev;

					pArea->m_pNext = pECastle->m_tAreaPosList->m_pEnd;
					pECastle->m_tAreaPosList->m_pEnd->m_pPrev = pArea;
				}
			}
		}
	}
}

int CreatePlayerSoldier(PPLAYER pPlayer)
{
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
		if ((pPlayer->pSoldiers[i] = CreateSoldier(i, TT_PLAYER, 0)) == NULL)
			return 0;

	return 1;
}

PSOLDIER CreateSoldier(int nType, int nTeam, int nUpgrade)
{
	PSOLDIER pSoldier = (PSOLDIER)malloc(sizeof(SOLDIER));

	pSoldier->m_nType = nType;
	pSoldier->m_nTeam = nTeam;
	pSoldier->m_nCurUpgrade = 0;

	pSoldier->m_nMoveRange = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][MOVE];

	pSoldier->m_nAttackMin = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][ATMIN];
	pSoldier->m_nAttackMax = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][ATMAX];
	pSoldier->m_nAttackRange = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][RANGE];

	pSoldier->m_nArmorMin = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][ARMIN];
	pSoldier->m_nArmorMax = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][ARMAX];

	pSoldier->m_nHp = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][HP];
	pSoldier->m_nCurHp = pSoldier->m_nHp;

	pSoldier->m_nUpgradeMax = 3;

	strcpy(pSoldier->m_strName, LevelCharacterNameTable[nType][pSoldier->m_nCurUpgrade]);
	strcpy(pSoldier->m_cShape, LevelCharacterShapeTable[nType][pSoldier->m_nCurUpgrade]);
	strcpy(pSoldier->m_strClass, CharacterClassName[nType]);

	if (pSoldier->m_nTeam == TT_PLAYER)
		pSoldier->m_nColor = BLUE;
	else if (pSoldier->m_nTeam == TT_ALLY)
		pSoldier->m_nColor = GREEN;
	else if (pSoldier->m_nTeam == TT_ENEMY)
		pSoldier->m_nColor = RED;

	return pSoldier;
}

int LoadWorldMap(PECASTLE* ppECastle)
{
	int nECastleIndex = 0;

	FILE* fp = NULL;

	fp = fopen("NationWide.txt", "rt");
	if (fp == NULL)
	{
		puts("파일 오픈에 실패하였습니다.");
		return 0;
	}

	int nX = 0;
	int nY = 0;

	while (!feof(fp))
	{
		char cTmp = fgetc(fp);
		if (cTmp == '\n') continue;
		else if (cTmp == MWT_PLAYERPOS)
		{
			tStartPos.x = nX;
			tStartPos.y = nY;
			cTmp = MWT_PCASTLEAREA;
		}
		else if (cTmp == MWT_ECASTLE)
		{
			ppECastle[nECastleIndex]->m_tWorldPos.x = nX;
			ppECastle[nECastleIndex]->m_tWorldPos.y = nY;
		
			if (!LoadECastleMap(ppECastle[nECastleIndex], FileName[nECastleIndex]))
			{
				puts("캐슬 맵 불러오기 실패!!");
				return 0;
			}
			nECastleIndex++;
		}

		aWorldMap[nX][nY++] = cTmp;

		if (nY >= MAP_WIDTH_MAX)
		{
			nX++;
			nY = 0;
		}
	}

	fclose(fp);

	return 1;
}

int LoadECastleMap(PECASTLE pECastle, const char* FileName)
{
	FILE* fp = NULL;

	fp = fopen(FileName, "rt");
	if (fp == NULL)
	{
		puts("파일 오픈에 실패하였습니다.");
		return 0;
	}

	int nX = 0;
	int nY = 0;

	while (!feof(fp))
	{
		char cTmp = fgetc(fp);
		if (cTmp == '\n') continue;
		// 출발지
		else if (cTmp == MCT_START)
		{
			pECastle->m_tStartPos.x = nX;
			pECastle->m_tStartPos.y = nY;
			cTmp = MCT_GROUND;
		}
		// 목적지
		else if (cTmp == MCT_DEST)
		{
			pECastle->m_tDestPos.x = nX;
			pECastle->m_tDestPos.y = nY;
		}
		else if (cTmp == MCT_KEY)
		{
			pECastle->m_tKeyPos.x = nX;
			pECastle->m_tKeyPos.y = nY;
		}
		else if (cTmp == MCT_DOOR)
		{
			PDOOR pDoor = (PDOOR)malloc(sizeof(DOOR));
			pDoor->m_tPos.x = nX;
			pDoor->m_tPos.y = nY;
			pDoor->m_nClosed = 1;
			pECastle->m_tDoorPosList->m_nSize++;

			// 문 추가
			if (pECastle->m_tDoorPosList->m_pBegin->m_pNext == pECastle->m_tDoorPosList->m_pEnd)
			{
				pECastle->m_tDoorPosList->m_pBegin->m_pNext = pDoor;
				pDoor->m_pPrev = pECastle->m_tDoorPosList->m_pBegin;

				pECastle->m_tDoorPosList->m_pEnd->m_pPrev = pDoor;
				pDoor->m_pNext = pECastle->m_tDoorPosList->m_pEnd;
			}
			else
			{
				PDOOR pPrev = pECastle->m_tDoorPosList->m_pEnd->m_pPrev;
				pDoor->m_pPrev = pPrev;
				pPrev->m_pNext = pDoor;

				pDoor->m_pNext = pECastle->m_tDoorPosList->m_pEnd;
				pECastle->m_tDoorPosList->m_pEnd->m_pPrev = pDoor;
			}
		}

		pECastle->m_aECastleMap[nX][nY++] = cTmp;

		if (nY >= CASTLE_WIDTH_MAX)
		{
			nX++;
			nY = 0;
		}
	}

	fclose(fp);

	return 1;
}


