
#include "Core.h"
ㅎ
/*
170728 숙제 : 1. 점프
2. 코인먹기
3. 떨어지기
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
