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

bool CObjectManager::CreateBullet()
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

	m_pBullet[m_iCurBulletCount] = pBullet;
	++m_iCurBulletCount;

	return true;
}
