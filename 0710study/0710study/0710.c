#include<stdio.h>
//void swap(int, int);
//int main() {
//	int a[5] = { 1,4,2,3,6 };
//	int i, j;
//	for (i = 0; i < 5; i++)
//		printf("%d", a[i]);
//	for (i = 0; i < 5; i++) {
//		for (j = i; j < 5; j++) {
//			if (a[i] > a[j])
//				swap(a[i], a[j]);
//		}
//	}
//	printf("\n");
//	for (i = 0; i < 5; i++)
//		printf("%d", a[i]);
//	return 0;
//}
//void swap(int n1, int n2) {
//	int temp;
//	temp = n1;
//	n1 = n2;
//	n2 = temp;
//}

//#define SIZE 6
//void SelectionSort(int a[], int);
//int main() {
//	int lise[SIZE] = { 0 };
//	int i;
//	printf("enter element SIZE = %d\n", SIZE);
//	for (i = 0; i < SIZE; i++) {
//		scanf("%d", list + i);
//	}
//	SelectionSort(list, SIZE);
//	return 0;
//}
//void SelectionSort(int a[], int size) {
//	int i, j, min;
//	int temp;
//	printf("\n list : ");
//	for (t = 0; t < size; t++) {
//		min = i;
//		for (j = i + i; j < size; j++) {
//			if (a[j] < a[min])
//				min = j;
//		}
//		temp = a[i];
//		a[i] = a[min];
//		a[min] = temp;
//		printf("\n step %d :", i + 1);
//		for (t = 0; t < size; t++) printf("%3d", a[t]);
//	}
//}
int main() {
	int i, j;
	char op;
	printf("¿¬»ê½Ä : ");
	scanf("%d%c%d", &i, &op, &j);
	if (op == '+')
		printf("%d+%d=%d\n", i, j, i + j);
	else if (op == '-')
		printf("%d+%d=%d\n", i, j, i - j);
	else
		printf("wrong\n")
	return 0;
}