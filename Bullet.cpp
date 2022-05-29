#include "Bullet.h"
#include "Stage.h"
#include "MapManager.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	m_tPos.x = 0;
	m_tPos.y = 0;

	m_iDist = 8;

	return true;
}

void CBullet::Update()
{
	// 스테이지를 얻어온다.
	CStage* pStage = CMapManager::GetInst()->GetStage();

	// 총알이 한칸 앞으로 나아가기 전에 현재 총알 위치의 다음칸 즉 총알이
	// 나아가야 할 위치에 만약 벽이 있다면 더이상 나가지 못하고 총알을
	// 삭제하게 한다.
	if (pStage->GetBlock(m_tPos.x + 1, m_tPos.y) != SBT_WALL)
	{
		// 매번 총알을 오른쪽으로 한칸 이동시킨다.
		m_tPos.x++;

		--m_iDist;
	}

	// 벽일 경우
	else
	{
		m_iDist = 0;
	}
}
