//#include<stdio.h>
//
//int main() {
//	int score[2][3];
//	int i, j, sum[2] = { 0 }, avg[2] = { 0 };
//	for (i = 0; i < 2; i++); {
//		for (j = 0; j < 3; j++) {
//			printf("%d�� �л��� %d��° ���� �Է� :", i + 1, j + 1);
//			scanf_s("%d", &score[i][j]);
//			sum[i] = sum[i] + score[i][j];
//		}
//		avg[i] = sum[i] / 3.0;
//	}
//	for (i = 0; i < 2; i++) {
//		printf("%d��° �л��� ����: %d, ���:%d\n", i + 1, sum[i], avg[i]);
//	}
//	return 0;
//}

#include<stdio.h>

//int main() {
//	int gugu[9][9], i, j;
//	int n;
//	printf("�� �ܱ��� ����ұ��?");
//	scanf_s("%d", &n);
//	for (i = 0; i < n - 1; i++) {
//		printf("%d��\n", i + 2);
//		for (j = 0; j < 9; j++) {
//			gugu[i][j] = (i + 2)* (j + 1);
//			printf("%d*%d = %d\t", i + 2, j + 1, gugu[i][j]);
//		}
//		printf("\n");
//	}
//	return 0;
//}

//#include<stdio.h>
//#define N 2
//#define S 3
//int main(){
//	int num[N][S] = {0};
//	int sum[N] = { 0 };
//	int i, j;
//	for (i = 0; i < N; i++) {
//		for (j = 0; j < S; j++) {
//			printf("%d���� %d��° ���� = ", i + 1, j + 1);
//			scanf_s("%d", &num[i][j]);
//			sum[i] += num[i][j];
//		}
//	}
//	for (i = 0; i < N; i++) {
//		printf("%d���� ������ �� = %d ��� = %f\n", i + 1, sum[i], sum[i] / (float)S);
//	}
//	return 0;
//}

int main() {
	int arr[5] = { 1,2,3,4,5 };
	int* arptr;
	arptr = arr;
	int i;
	printf("\n\n");
	for (i = 0; i < 5; i++) {
		printf("arr[%d]=%d\n", i, *(arr + i));
	}
}