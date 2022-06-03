#include "Monster.h"
#include "Stage.h"
#include "MapManager.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	m_tPos.x = 0;
	m_tPos.y = 0;
	m_iFrameCount = 0;

	// 모든 몬스터는 오른쪽에 생성해주었다. 그러므로 왼쪽으로 먼저
	// 움직이도록 해준다.
	m_iDir = -1;
	m_iSpeed = 3;

	return true;
}

void CMonster::Update()
{
	++m_iFrameCount;
	if (m_iFrameCount == m_iSpeed)
	{
		m_iFrameCount = 0;
		// 움직일 다음칸 아래가(즉, 움직인 칸의 발밑) 떨어지는 곳이라면
		// 방향을 바꿔준다.
		CStage* pStage = CMapManager::GetInst()->GetStage();

		if (pStage->GetBlock(m_tPos.x + m_iDir, m_tPos.y + 1) != SBT_WALL)
		{
			// 방향을 반대방향으로 바꿔주도록 한다.
			m_iDir *= -1;
		}

		else if (pStage->GetBlock(m_tPos.x + m_iDir, m_tPos.y) == SBT_WALL)
			m_iDir *= -1;

		m_tPos.x += m_iDir;
	}
}
