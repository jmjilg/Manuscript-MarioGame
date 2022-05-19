#pragma once

#include "value.h"

enum JUMP_DIR
{
	JD_STOP,
	JD_UP,
	JD_DOWN
};

#define JUMP_BLOCK_MAX	2

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

private:
	POINT	m_tPos;
	bool	m_bJump;
	int		m_iJumpDir;
	int		m_iJumpState;

public:
	int GetX()
	{
		return m_tPos.x;
	}

	int GetY()
	{
		return m_tPos.y;
	}

public:
	void SetPos(int x, int y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

public:
	bool Init();
	void Update();
};

