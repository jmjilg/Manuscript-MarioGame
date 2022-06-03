#include "Bullet.h"
#include "Stage.h"
#include "MapManager.h"
#include "Monster.h"

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

	// 총알이 이동할 위치를 구해준다.
	POINT	tNextPos = m_tPos;
	tNextPos.x++;

	// 현재 살아있는 몬스터를 얻어와서 위치가 같은지 체크한다.
	for (int i = 0; i < pStage->GetMonsterCount(); ++i)
	{
		CMonster* pMonster = pStage->GetMonster(i);

		POINT	tMonsterPos = pMonster->GetPos();
		if (tMonsterPos.x == m_tPos.x && tMonsterPos.y == m_tPos.y ||
			tMonsterPos.x == tNextPos.x && tMonsterPos.y == tNextPos.y)
		{
			// 몬스터를 목록에서 삭제한다.
			pStage->DeleteMonster(i);

			// 총알의 남은 거리를 0으로 만들어서 삭제되도록 한다.
			m_iDist = 0;
			return;
		}
	}

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
