#include <stdio.h>
#include <time.h>

int main() {

	srand(time(NULL));
	int i = rand() % 3;
	if (i == 0) {
		printf("가위\n");
	}
	else if (i == 1) {
		printf("바위\n");
	}
	else { printf("몰라요\n") };



	//for (int i = 1; i <= 30; i++)
	//{	
	//	/*if (i >= 6) {
	//		printf("나머지 학생은 집에 가세요\n");
	//		break;
	//	}
	//	printf("%d번 학생은 조별 발표를 하세요.\n", i);*/
	//}

}