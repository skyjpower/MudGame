#pragma once
#include "Game.h"

// �ܼ� ���� ����
void TextColor(int foreground, int background);
// Ŀ�� �̵�
void MoveCursorTo(const int x, const int y);
// ����ۿ� �׸���
void DrawToBackBuffer(const int x, const int y, char image);
// ����� �׸���
void DrawAll(PPLAYER pPlayer);
// �� �� �׸���
void RenderECastleMap(PPLAYER pPlayer, PECASTLE pECastle);
// ����� �׸���
void RenderWorldMap(PPLAYER pPlayer);
// ����â
void StatusWindow();
// �� �� �׸���
void DrawECastle(PPLAYER pPlayer, PECASTLE pECastle);