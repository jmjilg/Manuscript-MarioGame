
#include "Core.h"
��
/*
170728 ���� : 1. ����
2. ���θԱ�
3. ��������
*/

int main()
{
	// ������ �ʱ�ȭ�Ѵ�.
	if (!CCore::GetInst()->Init())
	{
		cout << "���� �ʱ�ȭ ����!!" << endl;
		CCore::DestroyInst();

		return 0;
	}

	// �ʱ�ȭ�� �����ߴٸ� ������ ������Ų��.
	CCore::GetInst()->Run();

	// ������ ������ CCore ��ü�� �޸𸮿��� ������Ų��.
	CCore::DestroyInst();

	return 0;
}
