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

	// ��� ���ʹ� �����ʿ� �������־���. �׷��Ƿ� �������� ����
	// �����̵��� ���ش�.
	m_iDir = -1;

	return true;
}

void CMonster::Update()
{
	// ������ ����ĭ �Ʒ���(��, ������ ĭ�� �߹�) �������� ���̶��
	// ������ �ٲ��ش�.
	CStage* pStage = CMapManager::GetInst()->GetStage();

	if (pStage->GetBlock(m_tPos.x + m_iDir, m_tPos.y + 1) != SBT_WALL)
	{
		// ������ �ݴ�������� �ٲ��ֵ��� �Ѵ�.
		m_iDir *= -1;
	}

	else if (pStage->GetBlock(m_tPos.x + m_iDir, m_tPos.y) == SBT_WALL)
		m_iDir *= -1;

	m_tPos.x += m_iDir;
}
