#include<stdio.h>

int main(void)
{
	//int subway_1 = 30;
	//int subway_2 = 40;
	//int subway_3 = 50;

	//printf("����ö 1ȣ���� %d ���� ž���� �ֽ��ϴ�.\n", subway_1);
	//printf("����ö 2ȣ���� %d ���� ž���� �ֽ��ϴ�.\n", subway_2);
	//printf("����ö 3ȣ���� %d ���� ž���� �ֽ��ϴ�.\n", subway_3);
	int subway_array[3];
	subway_array[0] = 30;
	subway_array[1] = 40;
	subway_array[2] = 50;

	/*for (int i = 0; i < 3; i++)
	{
		printf("����ö %dȣ���� %���� Ÿ�� �ֽ��ϴ�.\n", i + 1, subway_array[i]);


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
	//3��° �����ʹ� �ڵ����� '0'���� �ʱ�ȭ ��.

	//int arr[] = { 1,2 };

	//char c = 'A';
	//printf("%c\n", c);

	//char str[7] = "coding";
	//printf("%s\n", str);
	//���ڿ� ������ ���� �ǹ��ϴ� NULL ���� '0'�� ���ԵǾ�� ��
	
	
	/*char str[] = "coding";
	printf("%s\n", str);
	printf("%d\n", sizeof(str));*/

	// sizeof ���ڿ��� ����� �����ϴ� ���ε� �������� ���� �� �־� 7

	/*for (int i = 0; i < sizeof(str); i++)
	{
		print("%c\n", str[i]);

	}*/

	char kor[] = "�����ڵ�";
	printf("%s\n", kor);
	printf("%d\n", sizeof(kor));

	//���� : 1 ����Ʈ
	//�ѱ� : 2 ����Ʈ


	return 0;
}