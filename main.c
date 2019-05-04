#include "Init.h"
#include "Debugging.h"
#include "Render.h"
#include "Update.h"
#include "Global.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc();

	ConsoleInit();
	srand((unsigned int)time(0)); // 씨앗

	// 플레이어
	PLAYER tPlayer;
	// 캐슬
	PECASTLE pECastles[TOTAL_ECASTLE_NUM];
	// 배틀맵
	PBATTLEMAP pBattleMaps[TOTAL_BATTLEMAP_NUM];

	int nMenu;
	nMenu = MainMenuScene();

	// New
	if (nMenu == MT_NEW)
	{
		if (!Init(&tPlayer, pECastles, pBattleMaps))
		{
			puts("ERROR) 초기화 실패");
			return 0;
		}
	}

	// Load
	else if (nMenu == MT_LOAD)
	{
		if (!LoadPlayer(&tPlayer))
		{
			puts("로드에 실패했습니다.");
			return 0;
		}
		if (!LoadWorld())
		{
			puts("로드에 실패했습니다");
			return 0;
		}
		if (!LoadECastles(pECastles))
		{
			puts("로드에 실패했습니다");
			return 0;
		}
		if (!LoadBattleMaps(pBattleMaps))
		{
			puts("로드에 실패했습니다.");
			return 0;
		}
	}

	// Exit
	else if (nMenu == MT_EXIT)
		return 0;

	BasicInit(&tPlayer);

	// 배틀맵 종료 플래그
	int nBattleEnd = 0;
	// 한번 맵 렌더링 해주기
	g_moveFlag = 1;

	// PLAY
	while (!g_gameOver)
	{
		// 델타타임 계산
		CalcDeltaTime();

		// 월드맵
		if (g_gameMode == MM_WORLDMAP)
		{
			DrawAll(&tPlayer);

			// Update
			Update(&tPlayer, &pECastles, pBattleMaps);

			// 그리기
			RenderWorldMap(&tPlayer);

			// 세금 징수
			// CollectionTaxFromCastle(&tPlayer);
		}

		// 성(미로)
		else if (g_gameMode == MM_CASTLEMAP)
		{
			DrawECastle(&tPlayer, pECastles[g_nEnableStage]);

			// Update
			UpdateInCastle(&tPlayer, pECastles[g_nEnableStage]);

			// 그리기
			RenderECastleMap(&tPlayer, pECastles[g_nEnableStage]);
		}

		// 배틀맵
		else if (g_gameMode == MM_BATTLEMAP)
		{
			DrawBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// 사용자의 턴
			if (pBattleMaps[g_battleMapIndex]->m_nCurTurn == TT_PLAYER)
				UpdateInBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// 적 턴인 경우 AI
			else if (pBattleMaps[g_battleMapIndex]->m_nCurTurn == TT_ENEMY)
				BattleMapEnemyAI(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// 그리기
			RenderBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// 배틀이 끝난 경우
			if ((nBattleEnd = CheckEndBattleGame(&tPlayer, pBattleMaps[g_battleMapIndex])))
				ChangeBattleMapToWorld(&tPlayer, pBattleMaps[g_battleMapIndex], nBattleEnd);
		}
	}
	
	SavePlayer(&tPlayer);
	SaveWorldMap();
	SaveECastleMap(pECastles);
	SaveBattleMaps(pBattleMaps);

#pragma region FREE
	// 캐슬 free
	for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
	{
		PAREA pArea = pECastles[i]->m_tAreaPosList->m_pBegin->m_pNext;
		while (pArea != pECastles[i]->m_tAreaPosList->m_pEnd)
		{
			PAREA pNext = pArea->m_pNext;
			SAFE_DELETE(pArea)
			pArea = pNext;
		}
		SAFE_DELETE(pECastles[i]->m_tAreaPosList->m_pBegin)
		SAFE_DELETE(pECastles[i]->m_tAreaPosList->m_pEnd)
		SAFE_DELETE(pECastles[i]->m_tAreaPosList)

		PDOOR pDoor = pECastles[i]->m_tDoorPosList->m_pBegin->m_pNext;
		while (pDoor != pECastles[i]->m_tDoorPosList->m_pEnd)
		{
			PDOOR pNext = pDoor->m_pNext;
			SAFE_DELETE(pDoor)
			pDoor = pNext;
		}

		SAFE_DELETE(pECastles[i]->m_tDoorPosList->m_pBegin)
		SAFE_DELETE(pECastles[i]->m_tDoorPosList->m_pEnd)
		SAFE_DELETE(pECastles[i]->m_tDoorPosList)

		SAFE_DELETE(pECastles[i])
	}
	
	// 배틀맵 free
	for (int i = 0; i < TOTAL_BATTLEMAP_NUM; ++i)
		SAFE_DELETE(pBattleMaps[i])

	// 플레이어 인벤토리 free
	PITEM pItem = tPlayer.m_tInventory.m_pBegin->m_pNext;
	while (pItem != tPlayer.m_tInventory.m_pEnd)
	{
		PITEM pNext = pItem->m_pNext;
		SAFE_DELETE(pItem)
		pItem = pNext;
	}
	SAFE_DELETE(tPlayer.m_tInventory.m_pBegin)
	SAFE_DELETE(tPlayer.m_tInventory.m_pEnd)
#pragma endregion

	_CrtDumpMemoryLeaks();
	return 0;
}