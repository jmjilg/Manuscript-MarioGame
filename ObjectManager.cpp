#include "ObjectManager.h"
#include "Player.h"
#include "Bullet.h"

CObjectManager* CObjectManager::m_pInst = NULL;

CObjectManager::CObjectManager()	:
	m_pPlayer(NULL)
{
}

CObjectManager::~CObjectManager()
{
	SAFE_DELETE(m_pPlayer);

	for (int i = 0; i < m_iCurBulletCount; ++i)
	{
		SAFE_DELETE(m_pBullet[i]);
	}
}

bool CObjectManager::Init()
{
	m_pPlayer = new CPlayer;

	m_pPlayer->Init();

	// 1번 인자에 값을 세팅할 메모리 주소를 넣어준다.
	// 3번 인자는 값을 세팅할 메모리 크기를 넣어준다.
	// 이렇게 해주면 1번에 넣어준 주소부터 3번에 넣어준 메모리 크기만큼
	// 2번인자에 들어간 값으로 메모리를 초기화해준다.
	memset(m_pBullet, 0, sizeof(CBullet*) * BULLET_COUNT_MAX);
	m_iCurBulletCount = 0;

	return true;
}

void CObjectManager::Update()
{
	m_pPlayer->Update();

	for (int i = 0; i < m_iCurBulletCount; ++i)
	{
		m_pBullet[i]->Update();
	}

	for (int i = 0; i < m_iCurBulletCount;)
	{
		// 총알이 삭제되어야 할 경우
		if (m_pBullet[i]->GetEnable())
		{
			delete	m_pBullet[i];

			for (int j = i; j < m_iCurBulletCount - 1; ++j)
			{
				m_pBullet[j] = m_pBullet[j + 1];
			}

			// 가장 마지막 인덱스를 NULL로 초기화한다.
			m_pBullet[m_iCurBulletCount - 1] = NULL;

			--m_iCurBulletCount;
		}

		// 총알이 삭제되지 않을 경우 i를 증가시킨다.
		else
			++i;
	}
}

bool CObjectManager::CreateBullet(POINT tPos)
{
	// 총알 생성시 생성된 총알이 이미 최대치라면 더이상 생성하지 않는다.
	if (m_iCurBulletCount == BULLET_COUNT_MAX)
		return false;

	// 총알을 생성한다.
	CBullet* pBullet = new CBullet;

	// 총알을 초기화한다. 총알 초기화 실패시 생성한 총알을 지우고
	// false를 반환한다.
	if (!pBullet->Init())
	{
		SAFE_DELETE(pBullet);
		return false;
	}

	// 인자로 들어온 위치로 총알의 위치를 설정한다.
	pBullet->SetPos(tPos.x, tPos.y);

	m_pBullet[m_iCurBulletCount] = pBullet;
	++m_iCurBulletCount;

	return true;
}

// 이 함수는 해당 위치에 총알이 있는지를 총알목록에서 검사해준다.
// 있을 경우 true, 없을 경우 false를 반환하게 하여 해당 위치에 총알이 있
// 는지를 판단한다.
bool CObjectManager::CheckBullet(int x, int y)
{
	// 실제 총알이 추가된 수만큼 반복하며 각 총알들의 위치를 체크한다.
	for (int i = 0; i < m_iCurBulletCount; ++i)
	{
		// 총알의 위치와 인자로 들어온 위치가 같다면 총알이므로 true를 
		// 리턴한다.
		if (m_pBullet[i]->GetPos().x == x && m_pBullet[i]->GetPos().y == y)
			return true;
	}

	return false;
}
