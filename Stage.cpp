#include "Stage.h"
#include "FileStream.h"
#include "Player.h"
#include "ObjectManager.h"

CStage::CStage()
{
}

CStage::~CStage()
{
}

bool CStage::Init()
{
	return true;
}

bool CStage::Init(char* pFileName)
{
	CFileStream file;

	if (!file.Open(pFileName, "rt"))
		return false;

	for (int i = 0; i < 10; ++i)
	{
		int iSize = 0;
		file.ReadLine(m_cOriginStage[i], iSize);

		for (int j = 0; j < 50; ++j)
		{
			m_cStage[i][j] = m_cOriginStage[i][j];

			if (m_cOriginStage[i][j] == SBT_START)
			{
				m_tStart.x = j;
				m_tStart.y = i;
			}

			else if (m_cOriginStage[i][j] == SBT_END)
			{
				m_tEnd.x = j;
				m_tEnd.y = i;
			}
		}
	}

	return true;
}

void CStage::Render()
{
	/*
	 맵은 스크롤 처리를 해야한다. 그렇기 때문에 현재 플레이어가
	 이동한 위치로부터 맵을 출력해주어야 한다. 출력 크기는 세로4칸
	 가로 10칸으로 해준다. 지금은 플레이어가 처음에 있다 라고 가정하고
	 처음 4 x 10 출력을 해준다.
	 0 : 벽	  1 : 길	2 : 시작점	3 : 도착점	4 : 코인
	 */

	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

	// 플레이어의 x, y 좌표를 얻어온다.
	int iX = pPlayer->GetX();
	int iY = pPlayer->GetY();

	// 맵의 출력은 플레이어의 위치를 중심으로 출력한다.
	// 세로는 플레이어 2칸 위부터 한칸 아래까지 출력한다.
	// 총 5줄이 출력되는 것이다.
	// 가로는 플레이어 위치부터 오른쪽 10칸까지 출력한다.
	// 출력될 블럭수를 2로 나누어주어서 출력될 가장 아래쪽 인덱스를
	// 구해준다. 플레이어 위치보다 2칸 아래까지 출력해야 하기 때문이다.
	int iYCount = iY + (RENDER_BLOCK_Y / 2);

	// 만약 출력될 아래 2칸이 맵의 가장 아래쪽 개수보다 크거나 같다면
	// 출력될 아래 인덱스를 가장 마지막 인덱스로 제한한다.
	if (iYCount >= BLOCK_Y)
		iYCount = BLOCK_Y - 1;

	// 출력해야 할 최소 인덱스를 구해준다.
	// 출력해야 할 가장 아래쪽 인덱스에서 출력해야할 개수 -1개를 빼주게 되면
	// 출력해야할 가장 인덱스가 9이고 5개 출력시 9-4 가 되므로
	// 5 ~ 9까지 반복이 돌 수 있도록 최소값을 잡아준다.
	int iYMin = iYCount - (RENDER_BLOCK_Y - 1);

	// 만약 최소값이 0보다 작다면 인덱스가 없으므로 0으로 제한해준다.
	if (iYMin < 0)
		iYMin = 0;

	// 가로줄 최대 출력수는 현재 플레이어 위치 + 출력해야할 가로개수 이다.
	int iXCount = iX + RENDER_BLOCK_X;

	// 출력해야 할 가로 인덱스 최대치가 전체 블럭 수보다 크다면
	// 잘못된 인덱스이므로 최대 블럭수로 제한해준다.
	// 아래 for문에서 구해준 이 값보다 작을때까지만 돌리기 때문이다.
	if (iXCount > BLOCK_X)
		iXCount = BLOCK_X;

	// X의 최소 인덱스는 플레이어의 위치이다.
	int iXMin = iX;

	// 가장 마지막길 10칸은 모두 보여주기 위해서 반복문의 최소값을
	// 블럭 전체길이 - 출력될 블럭으로 처리해준다.
	if (iXMin > BLOCK_X - RENDER_BLOCK_X)
		iXMin = BLOCK_X - RENDER_BLOCK_X;

	for (int i = iYMin; i <= iYCount; ++i)
	{
		for (int j = iXMin; j < iXCount; ++j)
		{
			if (i == iY && j == iX)
				cout << "§";

			else if (m_cStage[i][j] == SBT_WALL)
				cout << "■";

			else if (m_cStage[i][j] == SBT_ROAD)
				cout << "  ";

			else if (m_cStage[i][j] == SBT_START)
				cout << "◑";

			else if (m_cStage[i][j] == SBT_END)
				cout << "◐";

			else if (m_cStage[i][j] == SBT_COIN)
				cout << "＠";
		}

		cout << endl;
	}
}

void CStage::ResetStage()
{
	for (int i = 0; i < BLOCK_Y; ++i)
	{
		for (int j = 0; j < BLOCK_X; ++j)
		{
			m_cStage[i][j] = m_cOriginStage[i][j];
		}
	}
}
