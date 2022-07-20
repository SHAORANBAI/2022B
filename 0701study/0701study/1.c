#include<stdio.h>

int main(void)
{
	/*int age = 12;
	printf("%d\n", age);
	age = 13;
	printf("%d\n", age);

	return 0;*/


	//const int YEAR = 2000;//상수로 인식하게 한다.
	//printf("태어난 년도 : %d\n", YEAR);

	//return 0;

	//int add = 3 + 7;
	//printf("3 + 7 = %d\n", add);
	//printf("%d + %d = %d\n", 3, 7, 3 + 7);

	//scanf : 키보드 입력을 받아서 저장

	//int input;
	//printf("값을 입력하세요. : ");
	//scanf_s("%d", &input);
	//printf("입력값 : %d\n", input);

	//int one, two, three;
	//printf("3개의 정수를 입력하세요. : ");
	//scanf_s("%d %d %d", &one &two &three);
	//printf("첫번째값 : %d\n", one);
	//printf("두번째값 : %d\n", two);
	//printf("세번째값 : %d\n", three);

	//프로젝트
	// 경찰관이 범죄자의 정보를 입수(조서 작성)
	// 이름, 나이, 몸무게, 키, 범죄명

	char name[256];
	printf("이름이 뭐예요?");
	scanf_s("%d", &name);

	float weight;
	printf("몸무게는 몇 kg 이예요?");
	scanf_s("%f", &weight);

	double height;
	pirntf("키는 몇 cm 이예요?");
	scanf_s("%lf", &height);

	char what[256];
	printf("무슨 범죄를 저질렀어요?");
	scanf_s("이름         : %s\n", name);
	scanf_s("몸무게       : %d\n", weight);
	scanf_s("키           : %.2lf\n", height);
	scanf_s("범죄         : %s\n", what);




	return 0;

}