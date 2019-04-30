#pragma once
#include "Render.h"
#include "Global.h"

void TextColor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void MoveCursorTo(const int x, const int y)
{
	const COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void DrawToBackBuffer(const int x, const int y, char image)
{
	aBackBuffer[x][y] = image;
}

void DrawAll(PPLAYER pPlayer)
{
	int nLeft = 0, nTop = 0, nRight = 0, nBottom = 0;

	if (g_sightMode)
	{
		int sightRange = 2;
		nLeft = pPlayer->m_tWorldPos.y - sightRange > 0 ? pPlayer->m_tWorldPos.y - sightRange : 0;
		nTop = pPlayer->m_tWorldPos.x - sightRange > 0 ? pPlayer->m_tWorldPos.x - sightRange : 0;
		nRight = pPlayer->m_tWorldPos.y + sightRange < MAP_WIDTH_MAX ? pPlayer->m_tWorldPos.y + sightRange : MAP_WIDTH_MAX - 1;
		nBottom = pPlayer->m_tWorldPos.x + sightRange < MAP_WIDTH_MAX ? pPlayer->m_tWorldPos.x + sightRange : MAP_HEIGHT_MAX - 1;
	}

	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			if (!g_sightMode)
			{
				aBackBuffer[i][j] = aWorldMap[i][j];
			}
			else
			{
				if (nLeft <= j && j <= nRight && nTop <= i && i <= nBottom)
					aBackBuffer[i][j] = aWorldMap[i][j];
				else
					aBackBuffer[i][j] = '\0';
			}
		}
	}
}

void RenderECastleMap(PPLAYER pPlayer, PECASTLE pECastle)
{
	// Draw
	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		int nTmp = 0;

		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			int nForeColor = aCastleTileColor[0][pECastle->m_aECastleMap[i][j] - '0'];
			int nBackColor = aCastleTileColor[1][pECastle->m_aECastleMap[i][j] - '0'];

			if (aBackBuffer[i][j] != aFrontBuffer[i][j] || g_moveFlag)
			{
				MoveCursorTo(nTmp, i);

				// 플레이어인 경우
				if (i == pPlayer->m_tPos.x && j == pPlayer->m_tPos.y)
				{
					MoveCursorTo(nTmp, i);
					TextColor(pPlayer->m_nColor, nBackColor);
					printf(pPlayer->m_cShape);
				}
				// 땅
				else if (aBackBuffer[i][j] == MCT_GROUND)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// 벽
				else if (aBackBuffer[i][j] == MCT_WALL)
				{
					TextColor(nForeColor, nBackColor);
					printf("▦");
				}
				// 물
				else if (aBackBuffer[i][j] == MCT_WATER)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// 문
				else if (aBackBuffer[i][j] == MCT_DOOR)
				{
					TextColor(nForeColor, nBackColor);
					printf("Ω");
				}
				// 키
				else if (aBackBuffer[i][j] == MCT_KEY)
				{
					TextColor(nForeColor, BLACK);
					printf("♀");
				}
				// 목적지
				else if (pECastle->m_tDestPos.x == i && pECastle->m_tDestPos.y == j)
				{
					if (aBackBuffer[i][j] == '\0')
						TextColor(GREEN, BLACK);
					else
						TextColor(GREEN, BLACK);
					printf("◈");
				}
				// 장애물
				else if (aBackBuffer[i][j] == MCT_OBSTACLE)
				{
					TextColor(nForeColor, nBackColor);
					printf("￥");
				}
				else if (aBackBuffer[i][j] == '\0')
				{
					TextColor(BLACK, BLACK);
					printf("  ");
				}
			}
			nTmp += 2;
		}
	}

	// Move 플래그 제거
	g_moveFlag = 0;
	// 색상 본래대로
	TextColor(LIGHTGRAY, BLACK);


	// 프론트 버퍼 업데이트
	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			aFrontBuffer[i][j] = aBackBuffer[i][j];
			aBackBuffer[i][j] = '\0';
		}
	}
}

void RenderWorldMap(PPLAYER pPlayer)
{
	// Draw
	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		int nTmp = 0;

		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			int nForeColor = aMapTileColor[0][aWorldMap[i][j] - '0'];
			int nBackColor = aMapTileColor[1][aWorldMap[i][j] - '0'];

			if (aBackBuffer[i][j] != aFrontBuffer[i][j] || g_moveFlag)
			{
				MoveCursorTo(nTmp, i);

				// 플레이어인 경우
				if (i == pPlayer->m_tWorldPos.x && j == pPlayer->m_tWorldPos.y)
				{
					MoveCursorTo(nTmp, i);
					TextColor(pPlayer->m_nColor, nBackColor);
					printf(pPlayer->m_cShape);
				}
				// 땅
				else if (aBackBuffer[i][j] == MWT_GROUND)
				{
					TextColor(nForeColor, nBackColor);
					printf("□");
				}
				// 벽
				else if (aBackBuffer[i][j] == MWT_WALL)
				{
					TextColor(nForeColor, nBackColor);
					printf("▦");
				}
				// 물
				else if (aBackBuffer[i][j] == MWT_WATER)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// 플레이어 성
				else if (aBackBuffer[i][j] == MWT_PCASTLE)
				{
					TextColor(nForeColor, nBackColor);
					printf("♣");
				}
				// 플레이어 영역
				else if (aBackBuffer[i][j] == MWT_PCASTLEAREA)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// 적 성
				else if (aBackBuffer[i][j] == MWT_ECASTLE)
				{
					TextColor(nForeColor, nBackColor);
					printf("♣");
				}
				// 적 성 영역
				else if (aBackBuffer[i][j] == MWT_ECASTLEAREA)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// 상점
				else if (aBackBuffer[i][j] == MWT_SHOP)
				{
					TextColor(RED, BROWN);
					printf("♨");
				}
				else if (aBackBuffer[i][j] == '\0')
				{
					TextColor(BLACK, BLACK);
					printf("  ");
				}
			}
			nTmp += 2;
		}
	}

	// Move 플래그 제거
	g_moveFlag = 0;
	// 색상 본래대로
	TextColor(LIGHTGRAY, BLACK);


	// 프론트 버퍼 업데이트
	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			aFrontBuffer[i][j] = aBackBuffer[i][j];
			aBackBuffer[i][j] = '\0';
		}
	}
}

void StatusWindow()
{
	MoveCursorTo(STATUS_WINDOW_HEIGHT, 0);
	TextColor(BLACK, WHITE);
	printf("%s\n", aStatusWindow);
	TextColor(LIGHTGRAY, BLACK);
	printf("계속 하려면 아무 키나 누르세요..");
	_getch();
}

void DrawECastle(PPLAYER pPlayer, PECASTLE pECastle)
{
	int nLeft = 0, nTop = 0, nRight = 0, nBottom = 0;

	if (g_sightMode)
	{
		int sightRange = 3;
		nLeft = pPlayer->m_tPos.y - sightRange > 0 ? pPlayer->m_tPos.y - sightRange : 0;
		nTop = pPlayer->m_tPos.x - sightRange > 0 ? pPlayer->m_tPos.x - sightRange : 0;
		nRight = pPlayer->m_tPos.y + sightRange < CASTLE_WIDTH_MAX ? pPlayer->m_tPos.y + sightRange : CASTLE_WIDTH_MAX - 1;
		nBottom = pPlayer->m_tPos.x + sightRange < CASTLE_HEIGHT_MAX ? pPlayer->m_tPos.x + sightRange : CASTLE_HEIGHT_MAX - 1;
	}

	for (int i = 0; i < CASTLE_HEIGHT_MAX; ++i)
	{
		for (int j = 0; j < CASTLE_WIDTH_MAX; ++j)
		{
			if (!g_sightMode)
			{
				aBackBuffer[i][j] = pECastle->m_aECastleMap[i][j];
			}
			else
			{
				if (nLeft <= j && j <= nRight && nTop <= i && i <= nBottom || pECastle->m_aECastleMap[i][j] == MCT_DEST)
					aBackBuffer[i][j] = pECastle->m_aECastleMap[i][j];
				else
					aBackBuffer[i][j] = '\0';
			}
		}
	}
}
