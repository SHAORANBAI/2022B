#include<stdio.h>

int main(void)
{
	/*int age = 12;
	printf("%d\n", age);
	age = 13;
	printf("%d\n", age);

	return 0;*/


	//const int YEAR = 2000;//����� �ν��ϰ� �Ѵ�.
	//printf("�¾ �⵵ : %d\n", YEAR);

	//return 0;

	//int add = 3 + 7;
	//printf("3 + 7 = %d\n", add);
	//printf("%d + %d = %d\n", 3, 7, 3 + 7);

	//scanf : Ű���� �Է��� �޾Ƽ� ����

	//int input;
	//printf("���� �Է��ϼ���. : ");
	//scanf_s("%d", &input);
	//printf("�Է°� : %d\n", input);

	//int one, two, three;
	//printf("3���� ������ �Է��ϼ���. : ");
	//scanf_s("%d %d %d", &one &two &three);
	//printf("ù��°�� : %d\n", one);
	//printf("�ι�°�� : %d\n", two);
	//printf("����°�� : %d\n", three);

	//������Ʈ
	// �������� �������� ������ �Լ�(���� �ۼ�)
	// �̸�, ����, ������, Ű, ���˸�

	char name[256];
	printf("�̸��� ������?");
	scanf_s("%d", &name);

	float weight;
	printf("�����Դ� �� kg �̿���?");
	scanf_s("%f", &weight);

	double height;
	pirntf("Ű�� �� cm �̿���?");
	scanf_s("%lf", &height);

	char what[256];
	printf("���� ���˸� ���������?");
	scanf_s("�̸�         : %s\n", name);
	scanf_s("������       : %d\n", weight);
	scanf_s("Ű           : %.2lf\n", height);
	scanf_s("����         : %s\n", what);




	return 0;

}