#include<stdio.h>

int main(void)
{
	//int subway_1 = 30;
	//int subway_2 = 40;
	//int subway_3 = 50;

	//printf("지하철 1호차에 %d 명이 탑승해 있습니다.\n", subway_1);
	//printf("지하철 2호차에 %d 명이 탑승해 있습니다.\n", subway_2);
	//printf("지하철 3호차에 %d 명이 탑승해 있습니다.\n", subway_3);
	int subway_array[3];
	subway_array[0] = 30;
	subway_array[1] = 40;
	subway_array[2] = 50;

	/*for (int i = 0; i < 3; i++)
	{
		printf("지하철 %d호차에 %명이 타고 있습니다.\n", i + 1, subway_array[i]);


	}*/
	/*int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}*/
	//int arr[10] = { 1,2 };

	//for (int i = 0; i < 10; i++)
	//{
	//	printf("%d\n", arr[i]);
	//}
	//3번째 값부터는 자동으로 '0'으로 초기화 됨.

	//int arr[] = { 1,2 };

	//char c = 'A';
	//printf("%c\n", c);

	//char str[7] = "coding";
	//printf("%s\n", str);
	//문자열 끝에는 끝을 의미하는 NULL 문자 '0'이 포함되어야 함
	
	
	/*char str[] = "coding";
	printf("%s\n", str);
	printf("%d\n", sizeof(str));*/

	// sizeof 문자열의 사이즈를 측정하는 것인데 마지막에 널이 들어가 있어 7

	/*for (int i = 0; i < sizeof(str); i++)
	{
		print("%c\n", str[i]);

	}*/

	char kor[] = "나도코딩";
	printf("%s\n", kor);
	printf("%d\n", sizeof(kor));

	//영어 : 1 바이트
	//한글 : 2 바이트


	return 0;
}