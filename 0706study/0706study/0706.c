#include <stdio.h>
#include <time.h>

int main() {

	srand(time(NULL));
	int i = rand() % 3;
	if (i == 0) {
		printf("����\n");
	}
	else if (i == 1) {
		printf("����\n");
	}
	else { printf("�����\n") };



	//for (int i = 1; i <= 30; i++)
	//{	
	//	/*if (i >= 6) {
	//		printf("������ �л��� ���� ������\n");
	//		break;
	//	}
	//	printf("%d�� �л��� ���� ��ǥ�� �ϼ���.\n", i);*/
	//}

}