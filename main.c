#include "Init.h"
#include "Debugging.h"
#include "Render.h"
#include "Update.h"

int main()
{
	// �÷��̾�
	PLAYER tPlayer;
	// ĳ��
	PECASTLE pECastles[TOTAL_ECASTLE_NUM];

	if (!Init(&tPlayer, pECastles))
	{
		puts("ERROR) �ʱ�ȭ ����");
		return 0;
	}

	if(DEBUG_MODE)
		DebugSoliderList(&tPlayer);

	// PLAY
	while (1)
	{
		// �Ϲ�
		if (g_gameMode == MM_WORLDMAP)
		{
			DrawAll(&tPlayer);
			Update(&tPlayer, pECastles[0]);
			RenderWorldMap(&tPlayer);
		}
		// ��(�̷�)
		else if (g_gameMode == MM_CASTLEMAP)
		{
			DrawECastle(&tPlayer, pECastles[0]);
			Update(&tPlayer, pECastles[0]);
			RenderECastleMap(&tPlayer, pECastles[0]);
		}
		// ��Ʋ
		else if (g_gameMode == MM_BATTLEMAP)
		{
			;
		}
		
		Sleep(33);
	}
	
	return 0;
}