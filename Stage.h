#pragma once

#include "value.h"

enum STAGE_BLOCK_TYPE
{
	SBT_WALL = '0',
	SBT_ROAD = '1',
	SBT_START = '2',
	SBT_END = '3',
	SBT_COIN = '4',
	SBT_ITEM_BULLET = '5',
	SBT_ITEM_BIG = '6',
	SBT_MONSTER = '7'
};

class CStage
{
public:
	CStage();
	~CStage();

private:
	char	m_cOriginStage[BLOCK_Y][BLOCK_X];
	char	m_cStage[BLOCK_Y][BLOCK_X];
	POINT	m_tStart;
	POINT	m_tEnd;
	// ������ �����迭�� ����� ���ؼ� �����Ѵ�.
	// �� ������ �����Ҵ��� ���� �ּҸ� ��Ƴ��� ���ؼ��̴�.
	class CMonster**	m_pMonsterArray;
	int					m_iMonsterCount; // ���Ͱ� ��� �����Ǿ����� üũ
	int					m_iMonsterArrayCount; // ���� �迭 ũ��

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

	void ChangeBlock(int x, int y, STAGE_BLOCK_TYPE eBlock)
	{
		m_cStage[y][x] = eBlock;
	}

	int GetMonsterCount()
	{
		return m_iMonsterCount;
	}

	class CMonster* GetMonster(int idx)
	{
		return m_pMonsterArray[idx];
	}

	void DeleteMonster(int idx)
	{
		delete	m_pMonsterArray[idx];

		for (int i = idx; i < m_iMonsterCount - 1; ++i)
		{
			m_pMonsterArray[i] = m_pMonsterArray[i + 1];
		}

		m_pMonsterArray[m_iMonsterCount - 1] = NULL;

		--m_iMonsterCount;
	}

public:
	// �� �Լ��� �׳� �ʱ�ȭ�� ������ �Լ��̴�.
	bool Init();

	// �� �Լ��� ���Ͽ��� ������ �о�ͼ� ������ ������ �Լ��̴�.
	bool Init(char* pFileName);
	void Update();
	void Render();
	void ResetStage();
	class CMonster* CreateMonster(int x, int y);
	bool CheckMonster(int x, int y);
};

