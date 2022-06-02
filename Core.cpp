#include "Core.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "Player.h"

CCore* CCore::m_pInst = NULL;

// cpp 파일에는 클래스의 구현부분이 있다.
CCore::CCore()
{
	srand((unsigned)time(0));
}

CCore::~CCore()
{
	CMapManager::DestroyInst();
	CObjectManager::DestroyInst();
}

CCore* CCore::GetInst()
{
	if (!m_pInst)
		m_pInst = new CCore;
	
	return m_pInst;
}

void CCore::DestroyInst()
{
	SAFE_DELETE(m_pInst);
}

bool CCore::Init()
{
	// 맵 관리자를 초기화한다. 실패시 false를 리턴한다.
	if (!CMapManager::GetInst()->Init())
		return false;

	// 오브젝트 관리자 초기화
	if (!CObjectManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run()
{
	//CMapManager::GetInst()->Render();

	while (true)
	{
		int iStage = OutputMenu();

		if (iStage == 4)
			break;

		else if (iStage == 0)
			continue;

		CMapManager::GetInst()->Run(iStage-1);
	}

}

int CCore::OutputMenu()
{
	system("cls");
	cout << "1. Stage1" << endl;
	cout << "2. Stage2" << endl;
	cout << "3. Stage3" << endl;
	cout << "4. Exit" << endl;
	cout << "Input Stage : ";
	int iInput = InputInt();

	if (iInput < 1 || iInput > 4)
		return 0;

	return iInput;
}
