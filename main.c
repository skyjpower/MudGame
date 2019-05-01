#include "Init.h"
#include "Debugging.h"
#include "Render.h"
#include "Update.h"
#include "Global.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc();
	
	srand((unsigned int)time(0)); // 씨앗

	// 플레이어
	PLAYER tPlayer;
	// 캐슬
	PECASTLE pECastles[TOTAL_ECASTLE_NUM];
	// 배틀맵
	PBATTLEMAP pBattleMaps[TOTAL_BATTLEMAP_NUM];

	if (!Init(&tPlayer, pECastles, pBattleMaps))
	{
		puts("ERROR) 초기화 실패");
		return 0;
	}

	if(DEBUG_MODE)
		DebugSoliderList(&tPlayer);

	// PLAY
	while (!g_gameOver)
	{
		// 일반
		if (g_gameMode == MM_WORLDMAP)
		{
			DrawAll(&tPlayer);
			Update(&tPlayer, &pECastles, pBattleMaps);
			RenderWorldMap(&tPlayer);
		}
		// 성(미로)
		else if (g_gameMode == MM_CASTLEMAP)
		{
			DrawECastle(&tPlayer, pECastles[g_nEnableStage]);
			UpdateInCastle(&tPlayer, pECastles[g_nEnableStage]);
			RenderECastleMap(&tPlayer, pECastles[g_nEnableStage]);
		}
		// 배틀
		else if (g_gameMode == MM_BATTLEMAP)
		{
			DrawBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// 사용자의 턴에만 실행
			if (pBattleMaps[g_battleMapIndex]->m_nCurTurn == TT_PLAYER)
				UpdateInBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);
			//else if (pBattleMaps[g_battleMapIndex]->m_nCurTurn == TT_ENEMY)
				// 적 AI 실행;
			RenderBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// 배틀이 끝난 경우
			if (CheckEndBattleGame(&tPlayer, pBattleMaps[g_battleMapIndex]))
			{

			}
		}
		
		Sleep(33);
	}
	
	// 캐슬 free
	for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
	{
		PAREA pArea = pECastles[i]->m_tAreaPosList->m_pBegin->m_pNext;
		while (pArea != pECastles[i]->m_tAreaPosList->m_pEnd)
		{
			PAREA pNext = pArea->m_pNext;
			free(pArea);
			pArea = pNext;
		}
		free(pECastles[i]->m_tAreaPosList->m_pBegin);
		free(pECastles[i]->m_tAreaPosList->m_pEnd);
		free(pECastles[i]->m_tAreaPosList);

		PDOOR pDoor = pECastles[i]->m_tDoorPosList->m_pBegin->m_pNext;
		while (pDoor != pECastles[i]->m_tDoorPosList->m_pEnd)
		{
			PDOOR pNext = pDoor->m_pNext;
			free(pDoor);
			pDoor = pNext;
		}

		free(pECastles[i]->m_tDoorPosList->m_pBegin);
		free(pECastles[i]->m_tDoorPosList->m_pEnd);
		free(pECastles[i]->m_tDoorPosList);

		free(pECastles[i]);
	}
	// 병사 free
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		free(tPlayer.m_pSoldiers[i]);
	}

	_CrtDumpMemoryLeaks();
	return 0;
}