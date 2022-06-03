#pragma once

#include "value.h"

class CMonster
{
public:
	CMonster();
	~CMonster();

private:
	POINT	m_tPos;
	int		m_iDir; // 움직일 방향이다.

public:
	void SetPos(int x, int y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

public:
	POINT GetPos()
	{
		return m_tPos;
	}

public:
	bool Init();
	void Update();
};

