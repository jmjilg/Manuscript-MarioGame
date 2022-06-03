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
	// ���������� ���´�.
	CStage* pStage = CMapManager::GetInst()->GetStage();

	// �Ѿ��� �̵��� ��ġ�� �����ش�.
	POINT	tNextPos = m_tPos;
	tNextPos.x++;

	// ���� ����ִ� ���͸� ���ͼ� ��ġ�� ������ üũ�Ѵ�.
	for (int i = 0; i < pStage->GetMonsterCount(); ++i)
	{
		CMonster* pMonster = pStage->GetMonster(i);

		POINT	tMonsterPos = pMonster->GetPos();
		if (tMonsterPos.x == m_tPos.x && tMonsterPos.y == m_tPos.y ||
			tMonsterPos.x == tNextPos.x && tMonsterPos.y == tNextPos.y)
		{
			// ���͸� ��Ͽ��� �����Ѵ�.
			pStage->DeleteMonster(i);

			// �Ѿ��� ���� �Ÿ��� 0���� ���� �����ǵ��� �Ѵ�.
			m_iDist = 0;
			return;
		}
	}

	// �Ѿ��� ��ĭ ������ ���ư��� ���� ���� �Ѿ� ��ġ�� ����ĭ �� �Ѿ���
	// ���ư��� �� ��ġ�� ���� ���� �ִٸ� ���̻� ������ ���ϰ� �Ѿ���
	// �����ϰ� �Ѵ�.
	if (pStage->GetBlock(m_tPos.x + 1, m_tPos.y) != SBT_WALL)
	{
		// �Ź� �Ѿ��� ���������� ��ĭ �̵���Ų��.
		m_tPos.x++;

		--m_iDist;
	}

	// ���� ���
	else
	{
		m_iDist = 0;
	}
}
