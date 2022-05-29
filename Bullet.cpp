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
	// ���������� ���´�.
	CStage* pStage = CMapManager::GetInst()->GetStage();

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
