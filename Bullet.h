#pragma once

#include "value.h"

class CBullet
{
public:
	CBullet();
	~CBullet();

private:
	POINT	m_tPos;
	int		m_iDist;

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

	bool GetEnable()
	{
		// 0이 아닌 경우는 아직 총알이 더 나아갈 수 있는 상태이기 때문에
		// true를 리턴하고 0일 경우는 총알이 나갈 수 있는 사정거리까지
		// 모두 나갔기 때문에 false를 리턴하여 총알을 삭제해준다.
		return m_iDist != 0;
	}

public:
	bool Init();
	void Update();
};

