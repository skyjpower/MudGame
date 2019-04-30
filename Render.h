#pragma once
#include "Game.h"

// 콘솔 색상 조정
void TextColor(int foreground, int background);
// 커서 이동
void MoveCursorTo(const int x, const int y);
// 백버퍼에 그리기
void DrawToBackBuffer(const int x, const int y, char image);
// 월드맵 그리기
void DrawAll(PPLAYER pPlayer);
// 적 성 그리기
void RenderECastleMap(PPLAYER pPlayer, PECASTLE pECastle);
// 월드맵 그리기
void RenderWorldMap(PPLAYER pPlayer);
// 상태창
void StatusWindow();
// 적 성 그리기
void DrawECastle(PPLAYER pPlayer, PECASTLE pECastle);