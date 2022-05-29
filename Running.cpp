
#include "Core.h"

/*
170728 숙제 : 커져라 아이템을 획득하면 플레이어가 1칸이던게 위로 하나가
늘어나서 세로로 2칸이 되게 한다. 플레이어가 움직일때 지금은 한칸만
벽이 있는지 체크하는데 2칸 모두 벽이 있는지 체크해본다.
*/

int main()
{
	// 게임을 초기화한다.
	if (!CCore::GetInst()->Init())
	{
		cout << "게임 초기화 실패!!" << endl;
		CCore::DestroyInst();

		return 0;
	}

	// 초기화에 성공했다면 게임을 구동시킨다.
	CCore::GetInst()->Run();

	// 동작이 끝나면 CCore 객체를 메모리에서 해제시킨다.
	CCore::DestroyInst();

	return 0;
}
