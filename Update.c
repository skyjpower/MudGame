#pragma once
#include "Update.h"
#include "Global.h"
#include "Render.h"
#include "Init.h"

int CheckCanMoveInWorld(int nShip, int x, int y)
{
	if (x < 0 || y < 0 || x >= MAP_HEIGHT_MAX || y >= MAP_WIDTH_MAX) return 0;

	if (aWorldMap[x][y] == MWT_WALL) return 0;
	if (!nShip && aWorldMap[x][y] == MWT_WATER) return 0;
	if (aWorldMap[x][y] == MWT_SHOP) return 0;

	return 1;
}

int CheckCanMoveInECastle(int x, int y, PECASTLE pECastle)
{
	if (x < 0 || y < 0 || x >= CASTLE_HEIGHT_MAX || y >= CASTLE_WIDTH_MAX) return 0;

	if (pECastle->m_aECastleMap[x][y] == MCT_WALL ||
		pECastle->m_aECastleMap[x][y] == MCT_WATER ||
		pECastle->m_aECastleMap[x][y] == MCT_DOOR)
		return 0;

	return 1;
}

void Update(PPLAYER pPlayer, PECASTLE* ppECastle, PBATTLEMAP* ppBattleMaps)
{
	if (GetAsyncKeyState('W') & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x - 1, pPlayer->m_tWorldPos.y))
		{
			pPlayer->m_tWorldPos.x--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x, pPlayer->m_tWorldPos.y - 1))
		{
			pPlayer->m_tWorldPos.y--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x + 1, pPlayer->m_tWorldPos.y))
		{
			pPlayer->m_tWorldPos.x++;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x, pPlayer->m_tWorldPos.y + 1))
		{
			pPlayer->m_tWorldPos.y++;
			g_moveFlag = 1;
		}
	}

	// 관리자
	if (MANAGE_MODE)
	{
		// 바다 건너기
		if (GetAsyncKeyState('C') & 0x8000)
		{
			pPlayer->m_nHaveShip = !pPlayer->m_nHaveShip;
		}

		// 아군 영역으로 만들기
		if (GetAsyncKeyState('B') & 0x8000)
		{
			if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_ECASTLEAREA)
				aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_PCASTLEAREA;
			else if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_PCASTLEAREA)
				aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_ECASTLEAREA;
		}

		// 시야각
		if (GetAsyncKeyState('N') & 0x8000)
		{
			g_sightMode = !g_sightMode;
			Sleep(100);
		}

		if (GetAsyncKeyState('L') & 0x8000)
		{
			g_gameOver = 1;
		}
	}


	// 적 성인 경우
	if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_ECASTLE)
	{
		// 캐슬 맵 변화
		for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
		{
			if (ppECastle[i]->m_tWorldPos.x == pPlayer->m_tWorldPos.x
				&& ppECastle[i]->m_tWorldPos.y == pPlayer->m_tWorldPos.y)
			{
				g_nEnableStage = i;
				pPlayer->m_tPos.x = ppECastle[i]->m_tStartPos.x;
				pPlayer->m_tPos.y = ppECastle[i]->m_tStartPos.y;
				break;
			}
		}
		EventWindowRenewal("공성전 시작 !!");
		ChangeWorldToCastle(pPlayer, ppECastle[g_nEnableStage]);
	}
	// 적 영토인 경우
	else if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_ECASTLEAREA)
	{
		ChangeWorldToBattleMap(pPlayer, ppBattleMaps[g_battleMapIndex]);

		EventWindowRenewal("적과 조우하였습니다. 전투 시작.");
	}
}

void UpdateInCastle(PPLAYER pPlayer, PECASTLE pECastle)
{
	int nLoseFlag = 0;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x - 1, pPlayer->m_tPos.y, pECastle))
		{
			pPlayer->m_tPos.x--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x, pPlayer->m_tPos.y - 1, pECastle))
		{
			pPlayer->m_tPos.y--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x + 1, pPlayer->m_tPos.y, pECastle))
		{
			pPlayer->m_tPos.x++;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x, pPlayer->m_tPos.y + 1, pECastle))
		{
			pPlayer->m_tPos.y++;
			g_moveFlag = 1;
		}
	}

	// 관리자
	if (MANAGE_MODE)
	{
		// 시야각
		if (GetAsyncKeyState('N') & 0x8000)
		{
			g_sightMode = !g_sightMode;
			Sleep(100);
		}

		// 캐슬 바로 깨기
		if (GetAsyncKeyState('F') & 0x8000)
		{
			pPlayer->m_tPos.x = 1;
			pPlayer->m_tPos.y = 27;
		}
	}


	// 플레이어 위치
	int nPlayerX = pPlayer->m_tPos.x;
	int nPlayerY = pPlayer->m_tPos.y;

	// 장애물 밟음
	if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_OBSTACLE)
	{
		nLoseFlag = 1;
	}
	// 키 획득
	else if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_KEY)
	{
		PDOOR pDoor = pECastle->m_tDoorPosList->m_pBegin->m_pNext;
		PDOOR pEnd = pECastle->m_tDoorPosList->m_pEnd;

		// 문 열기
		while (pDoor != pEnd)
		{
			pECastle->m_aECastleMap[pDoor->m_tPos.x][pDoor->m_tPos.y] = MCT_GROUND;
			pECastle->m_aECastleMap[pECastle->m_tKeyPos.x][pECastle->m_tKeyPos.y] = MCT_GROUND;
			pDoor->m_nClosed = 0;
			pDoor = pDoor->m_pNext;
		}
		EventWindowRenewal("키 획득 ! 성문이 열렸습니다.");
	}
	// 목적지에 다다른 경우 ( 클리어 )
	else if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_DEST)
	{
		// 성지 아군화
		aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_PCASTLE;
		// 영토 아군화
		PAREA pArea = pECastle->m_tAreaPosList->m_pBegin->m_pNext;
		while (pArea != pECastle->m_tAreaPosList->m_pEnd)
		{
			PAREA pNext = pArea->m_pNext;
			aWorldMap[pArea->m_tPos.x][pArea->m_tPos.y] = MWT_PCASTLEAREA;
			free(pArea);
			pArea = pNext;
		}

		// 보상 획득
		pPlayer->m_nMoney += pECastle->m_nReward;

		EventWindowRenewal("공성전 클리어 !");
		// 월드맵으로 이동
		ChangeCastleToWorld(pPlayer, CASTLE_WIN);
	}

	// 패배 판정 시
	if (nLoseFlag)
	{
		// 시작 지점으로 되돌리기
		pPlayer->m_tWorldPos.x = tStartPos.x;
		pPlayer->m_tWorldPos.y = tStartPos.y;

		// 적 영토 회복
		PAREA pArea = pECastle->m_tAreaPosList->m_pBegin->m_pNext;
		while (pArea != pECastle->m_tAreaPosList->m_pEnd)
		{
			pArea->m_beOccupied = 0;
			aWorldMap[pArea->m_tPos.x][pArea->m_tPos.y] = MWT_ECASTLEAREA;
			pArea = pArea->m_pNext;
		}

		// 성에서 쫓아내기 및 적 영토 회복
		ChangeCastleToWorld(pPlayer, CASTLE_LOSE);
		EventWindowRenewal("패배하였습니다....");
	}
}

void ChangeWorldToCastle(PPLAYER pPlayer, PECASTLE pECastle)
{
	// 위치 조정
	pPlayer->m_tPos.x = pECastle->m_tStartPos.x;
	pPlayer->m_tPos.y = pECastle->m_tStartPos.y;

	// 모드 조정
	g_gameMode = MM_CASTLEMAP;
	memset(aBackBuffer, 0, sizeof(aBackBuffer));

	g_moveFlag = 1;
}

void ChangeCastleToWorld(PPLAYER pPlayer, int nWin)
{
	g_gameMode = MM_WORLDMAP;
	memset(aBackBuffer, 0, sizeof(aBackBuffer));
	g_moveFlag = 1;
}

void ChangeWorldToBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	g_battleMapIndex = rand() % TOTAL_BATTLEMAP_NUM;
	g_gameMode = MM_BATTLEMAP;
	memset(aBackBuffer, 0, sizeof(aBackBuffer));

	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		pPlayer->m_pSoldiers[i]->m_tPos.x = pBattleMap->m_tPlayerStartPos[i].x;
		pPlayer->m_pSoldiers[i]->m_tPos.y = pBattleMap->m_tPlayerStartPos[i].y;
	}

	g_moveFlag = 1;
}

void CalcSoldierMoveRange(PSOLDIER pSoldier, PBATTLEMAP pBattleMap)
{
	if (pSoldier == NULL)
	{
		memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
	}
	else
	{
		memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
		POINT queue[QUEUE_MAX_SIZE] = { 0 };
		int front = 0, rear = 1;
		int nPath = 0;

		POINT curPos = { pSoldier->m_tPos.x, pSoldier->m_tPos.y };
		queue[front] = curPos;
		aBattleMapRange[curPos.x][curPos.y] = 1;

		while (front != rear)
		{
			int qSize = rear - front;
			for (int i = 0; i < qSize; ++i)
			{
				int cur_x = queue[front].x;
				int cur_y = queue[front].y;
				front = (front + 1) % QUEUE_MAX_SIZE;

				for (int j = 0; j < 4; ++j)
				{
					int next_x = cur_x + xDir[j];
					int next_y = cur_y + yDir[j];

					if (aBattleMapRange[next_x][next_y]) continue;
					if (pBattleMap->m_aBattleMap[next_x][next_y] == MBT_WATER ||
						pBattleMap->m_aBattleMap[next_x][next_y] == MBT_WALL)
						continue;

					POINT tmp = { next_x, next_y };
					queue[rear++] = tmp;
					aBattleMapRange[next_x][next_y] = 1;
				}
			}
			if (++nPath >= pSoldier->m_nMoveRange) return;
		}
	}
}

void SetMousePos(PPLAYER pPlayer)
{
	pPlayer->m_nMouseOn = !pPlayer->m_nMouseOn;
	if (pPlayer->m_nMouseOn)
	{
		pPlayer->m_tMouse.x = pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.x;
		pPlayer->m_tMouse.y = pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.y;
	}
	g_moveFlag = 1;
}

void PlayerSoldierMove(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	// 움직임 가능
	if (pPlayer->m_nMouseOn == ON)
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x - 1][pPlayer->m_tMouse.y])
			{
				pPlayer->m_tMouse.x--;
				g_moveFlag = 1;
			}

		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y - 1])
			{
				pPlayer->m_tMouse.y--;
				g_moveFlag = 1;
			}
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x + 1][pPlayer->m_tMouse.y])
			{
				pPlayer->m_tMouse.x++;
				g_moveFlag = 1;
			}
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y + 1])
			{
				pPlayer->m_tMouse.y++;
				g_moveFlag = 1;
			}
		}

		if (GetAsyncKeyState('K') & 0x8000)
		{
			if (pPlayer->m_tMouse.x != pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.x ||
				pPlayer->m_tMouse.y != pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.y)
			{
				pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.x = pPlayer->m_tMouse.x;
				pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.y = pPlayer->m_tMouse.y;

				// 턴을 사용함을 알림
				pPlayer->m_nSoldierTurn[pPlayer->m_nSelectSoldier] = 1;

				// 턴을 쓰지 않은 병사가 있는 지 확인
				pPlayer->m_nSelectSoldier = -1;
				for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
				{
					if (!pPlayer->m_nSoldierTurn[i])
					{
						// 선택하지 않은 경우
						pPlayer->m_nSelectSoldier = i;
						pPlayer->m_tMouse.x = pPlayer->m_pSoldiers[i]->m_tPos.x;
						pPlayer->m_tMouse.y = pPlayer->m_pSoldiers[i]->m_tPos.y;
						CalcSoldierMoveRange(pPlayer->m_pSoldiers[i], pBattleMap);
						break;
					}
				}

				// 턴을 모두 소진한 경우
				if (pPlayer->m_nSelectSoldier == -1)
				{
					// 상대 턴
					pPlayer->m_nMouseOn = OFF;
					pBattleMap->m_nCurTurn = TT_ENEMY;
					CalcSoldierMoveRange(NULL, pBattleMap);
					EventWindowRenewal("상대방 턴 입니다.");
				}

				g_moveFlag = 1;
			}
		}
	}
}

void UpdateInBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	// 기사 선택
	if (GetAsyncKeyState('1') & 0x8000)
	{
		if (!pPlayer->m_nSoldierTurn[SC_KNIGHT])
		{
			pPlayer->m_nSelectSoldier = SC_KNIGHT;
			sprintf(aEventTmpMessage, "[플레이어] %s", pPlayer->m_pSoldiers[SC_KNIGHT]->m_strName);
			EventWindowRenewal(aEventTmpMessage);
			memset(aEventTmpMessage, 0, sizeof(aEventMessage));

			// 범위 계산
			CalcSoldierMoveRange(pPlayer->m_pSoldiers[SC_KNIGHT], pBattleMap);
			g_moveFlag = 1;
		}
		else
			EventWindowRenewal("이미 턴을 마친 병사입니다.");
	}
	// 기병 선택
	if (GetAsyncKeyState('2') & 0x8000)
	{
		if (!pPlayer->m_nSoldierTurn[SC_CAVALRY])
		{
			pPlayer->m_nSelectSoldier = SC_CAVALRY;
			sprintf(aEventTmpMessage, "[플레이어] %s", pPlayer->m_pSoldiers[SC_CAVALRY]->m_strName);
			EventWindowRenewal(aEventTmpMessage);
			memset(aEventTmpMessage, 0, sizeof(aEventMessage));

			// 범위 계산
			CalcSoldierMoveRange(pPlayer->m_pSoldiers[SC_CAVALRY], pBattleMap);
			g_moveFlag = 1;
		}

		else
			EventWindowRenewal("이미 턴을 마친 병사입니다.");
	}
	// 궁수 선택
	if (GetAsyncKeyState('3') & 0x8000)
	{
		if (!pPlayer->m_nSoldierTurn[SC_ARCHER])
		{
			pPlayer->m_nSelectSoldier = SC_ARCHER;
			sprintf(aEventTmpMessage, "[플레이어] %s", pPlayer->m_pSoldiers[SC_ARCHER]->m_strName);
			EventWindowRenewal(aEventTmpMessage);
			memset(aEventTmpMessage, 0, sizeof(aEventMessage));

			// 범위 계산
			CalcSoldierMoveRange(pPlayer->m_pSoldiers[SC_ARCHER], pBattleMap);
			g_moveFlag = 1;
		}

		else
			EventWindowRenewal("이미 턴을 마친 병사입니다.");
	}

	// 캐릭터 선택
	if (!pPlayer->m_nSoldierTurn[pPlayer->m_nSelectSoldier] && 
		pPlayer->m_nSelectSoldier >= 0 && 
		pPlayer->m_nSelectSoldier < TOTAL_SOLDIER_NUM && 
		GetAsyncKeyState('T') & 0x8000)
	{
		SetMousePos(pPlayer);
	}

	// 병사 Move
	PlayerSoldierMove(pPlayer, pBattleMap);
}

int CheckEndBattleGame(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	return 0;
}
