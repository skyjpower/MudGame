#include "Init.h"
#include "Debugging.h"
#include "Render.h"
#include "Update.h"

int main()
{
	// 플레이어
	PLAYER tPlayer;
	// 캐슬
	PECASTLE pECastles[TOTAL_ECASTLE_NUM];

	if (!Init(&tPlayer, pECastles))
	{
		puts("ERROR) 초기화 실패");
		return 0;
	}

	if(DEBUG_MODE)
		DebugSoliderList(&tPlayer);

	// PLAY
	while (1)
	{
		// 일반
		if (g_gameMode == MM_WORLDMAP)
		{
			DrawAll(&tPlayer);
			Update(&tPlayer, pECastles[0]);
			RenderWorldMap(&tPlayer);
		}
		// 성(미로)
		else if (g_gameMode == MM_CASTLEMAP)
		{
			DrawECastle(&tPlayer, pECastles[0]);
			Update(&tPlayer, pECastles[0]);
			RenderECastleMap(&tPlayer, pECastles[0]);
		}
		// 배틀
		else if (g_gameMode == MM_BATTLEMAP)
		{
			;
		}
		
		Sleep(33);
	}
	
	return 0;
}