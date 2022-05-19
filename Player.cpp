#include "Player.h"
#include "MapManager.h"
#include "Stage.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	m_tPos.x = 0;
	m_tPos.y = 8;

	m_bJump = false;
	m_iJumpDir = JD_STOP;
	m_iJumpState = 0;

	return true;
}

void CPlayer::Update()
{
	CStage* pStage = CMapManager::GetInst()->GetStage();

	// 키 입력을 받는다.
	// GetAsyncKeyState 함수는 Win32 API 에서 제공되는 키 입력 함수이다.
	// W키를 눌렀을때 바로 반응하게 하기 위해서 0x8000 과 &연산을 하여
	// 눌렀을 경우 true가 나오게 된다.
	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (pStage->GetBlock(m_tPos.x - 1, m_tPos.y) != SBT_WALL)
		{
			--m_tPos.x;

			if (m_tPos.x < 0)
				m_tPos.x = 0;
		}
	}
	
	if (GetAsyncKeyState('D') & 0x8000)
	{
		if (pStage->GetBlock(m_tPos.x + 1, m_tPos.y) != SBT_WALL)
		{
			++m_tPos.x;
			if (m_tPos.x >= 50)
				m_tPos.x = 49;
		}
	}
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !m_bJump)
	{
		m_bJump = true;
		m_iJumpDir = JD_UP;
		m_iJumpState = 0;
	}

	if (m_bJump)
	{
		CStage* pStage = CMapManager::GetInst()->GetStage();

		switch (m_iJumpDir)
		{
		case JD_UP:
			++m_iJumpState;

			if (m_iJumpState > JUMP_BLOCK_MAX)
			{
				m_iJumpState = JUMP_BLOCK_MAX;
				m_iJumpDir = JD_DOWN;
			}

			else if (pStage->GetBlock(m_tPos.x, m_tPos.y - 1) == SBT_WALL)
			{
				--m_iJumpState;
				m_iJumpDir = JD_DOWN;
			}

			else
			{
				--m_tPos.y;
			}
			break;
		case JD_DOWN:
			if (m_tPos.y >= BLOCK_Y)
			{
				cout << "플레이어 사망" << endl;
				system("pause");
				--m_tPos.y = BLOCK_Y - 1;
			}

			if (pStage->GetBlock(m_tPos.x, m_tPos.y + 1) == SBT_WALL)
			{
				m_iJumpDir = JD_STOP;
				m_bJump = false;
			}

			else
			{
				++m_tPos.y;
			}
			break;
		}
	}
}
