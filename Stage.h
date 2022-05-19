#pragma once

#include "value.h"

enum STAGE_BLOCK_TYPE
{
	SBT_WALL = '0',
	SBT_ROAD = '1',
	SBT_START = '2',
	SBT_END = '3',
	SBT_COIN = '4'
};

class CStage
{
public:
	CStage();
	~CStage();

private:
	char	m_cStage[BLOCK_Y][BLOCK_X];
	POINT	m_tStart;
	POINT	m_tEnd;

public:
	POINT GetStart()
	{
		return m_tStart;
	}

	POINT GetEnd()
	{
		return m_tEnd;
	}

	char GetBlock(int x, int y)
	{
		return m_cStage[y][x];
	}

public:
	// 이 함수는 그냥 초기화할 목적의 함수이다.
	bool Init();

	// 이 함수는 파일에서 정보를 읽어와서 설정할 목적의 함수이다.
	bool Init(char* pFileName);
	void Render();
};

