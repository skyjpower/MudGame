#pragma once
#include "Game.h"

// 콘솔 색상 조정
void TextColor(int foreground, int background);
// 커서 이동
void MoveCursorTo(const int x, const int y);
// 백버퍼에 그리기
void DrawToBackBuffer(const int x, const int y, char image);
// 월드맵 backbuffer 기록
void DrawAll(PPLAYER pPlayer);
// 월드맵 그리기
void RenderWorldMap(PPLAYER pPlayer);
// 적 성 backbuffer 기록
void DrawECastle(PPLAYER pPlayer, PECASTLE pECastle);
// 적 성 그리기
void RenderECastleMap(PPLAYER pPlayer, PECASTLE pECastle);
// 배틀 맵 backbuffer 기록
void DrawBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// 배틀 맵 그리기
void RenderBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// 상태 창 그리기
void CreateStatusWindow();
// 이벤트 창 메세지
void EventWindowRenewal();
// 아군 땅 체크
int CheckPlayerArea(int x, int y);
