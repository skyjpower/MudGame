#pragma once
#include "Game.h"

// �ܼ� ���� ����
void TextColor(int foreground, int background);
// Ŀ�� �̵�
void MoveCursorTo(const int x, const int y);
// ����ۿ� �׸���
void DrawToBackBuffer(const int x, const int y, char image);
// ����� backbuffer ���
void DrawAll(PPLAYER pPlayer);
// ����� �׸���
void RenderWorldMap(PPLAYER pPlayer);
// �� �� backbuffer ���
void DrawECastle(PPLAYER pPlayer, PECASTLE pECastle);
// �� �� �׸���
void RenderECastleMap(PPLAYER pPlayer, PECASTLE pECastle);
// ��Ʋ �� backbuffer ���
void DrawBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// ��Ʋ �� �׸���
void RenderBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// ���� â �׸���
void CreateStatusWindow();
// �̺�Ʈ â �޼���
void EventWindowRenewal();
// �Ʊ� �� üũ
int CheckPlayerArea(int x, int y);
