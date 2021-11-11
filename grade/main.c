#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#define CNT 15//학생수 최대 15
#define YEAR 2021//올해 년도 학번 예외처리 할때 사용

int subjectcon(int subject);//과목코드->학점으로 변환 ex)105->3
int gradecon(char grade);//성적->점수로 변환 ex)A->4
void sort(char department[][16], double a[], char name[][10], int n);//이름기준 오름차순 정렬
void swapdouble(double* x, double* y);//더블형 자리를 바꿔줌
void swapstr(char* x, char* y);//문자열의 자리를 바꿔줌
void printArray(char department[][16], double arr[], char na[][10], int n);//출력

int main() {
	int i, j;
	int count; //학생수 저장
	int student[CNT];//입력배열 학번
	int subject[2][CNT];//과목1코드 과목2코드 
	char grade[2][CNT];//과목1학점 과목2학점
	char name[CNT][10];//입력배열 이름
	int dm[CNT]; //학번에서 학과만 저장
	int found;//입력시 틀린 횟수 저장
	char department[CNT][16]; //학과 문자열 저장
	int cnt[4] = { 0, }; //학과별 인원
	double sum[4] = { 0, }, avg[4] = { 0, }; //학과별 총합점수, 평균
	int check;//조회하고자하는 학과 코드
	double score[CNT];//출력배열 성적


	do
	{
		printf("학생 수를 입력하시오:");
		scanf("%d", &count);
		if (count > CNT || count < 1)
		{
			printf("잘못입력했습니다.\n");
		}
	} while (count > CNT || count < 1);

	//학번 과목1코드 과목1학점 과목2코드 과목2학점 이름 입력 학번에서 학과 추출
	for (i = 0; i < count; i++)
	{
		found = 0;
		printf("학번 이름 과목1코드 학점 과목2코드 학점 입력하시오:");
		scanf("%d %s %d %c %d %c", &student[i], name[i], &subject[0][i], &grade[0][i], &subject[1][i], &grade[1][i]);
		dm[i] = ((student[i] / 1000) % 1000);

		for (j = i - 1; j >= 0; j--)
		{
			if (student[i] == student[j])
			{
				printf("학번(중복) ");
				found++;
			}
		}
		if (((student[i] / 1000000) % 10000) < 1970 || ((student[i] / 1000000) % 10000) > YEAR)
		{
			printf("학번(입학년도) ");
			found++;
		}
		if (dm[i] != 7 && dm[i] != 12 && dm[i] != 81 && dm[i] != 91)
		{
			printf("학번(학과코드) ");
			found++;
		}

		for (j = 0; j < 2; j++)
		{
			if (subject[j][i] != 101 && subject[j][i] != 102 && subject[j][i] != 103 && subject[j][i] != 105 && subject[j][i] != 201)
			{
				printf("과목코드 ");
				found++;
			}
		}
		if (subject[0][i] == subject[1][i])
		{
			printf("과목코드(중복) ");
			found++;
		}

		for (j = 0; j < 2; j++)
		{
			if (grade[j][i] != 'A' && grade[j][i] != 'B' && grade[j][i] != 'C' && grade[j][i] != 'a' && grade[j][i] != 'b' && grade[j][i] != 'c')
			{
				printf("학점 ");
				found++;
			}
		}

		if (found != 0)
		{
			printf("(을)를 잘못입력했습니다.\n");
			i--;
		}
	}

	//평점계산
	for (i = 0; i < count; i++)
	{
		score[i] = (double)(subjectcon(subject[0][i]) * gradecon(grade[0][i]) + subjectcon(subject[1][i]) * gradecon(grade[1][i])) / (subjectcon(subject[0][i]) + subjectcon(subject[1][i]));
	}

	//학과별 평점 계산 및 학과 문자열 저장
	for (i = 0; i < count; i++)
	{
		switch (dm[i])
		{
		case 7: strcpy(department[i], "전자공학과"); sum[0] += score[i]; cnt[0]++; break;
		case 12: strcpy(department[i], "사회체육과"); sum[1] += score[i]; cnt[1]++; break;
		case 81: strcpy(department[i], "컴퓨터공학과"); sum[2] += score[i]; cnt[2]++; break;
		case 91: strcpy(department[i], "정보통신과"); sum[3] += score[i]; cnt[3]++; break;
		default:
			break;
		}
	}
	for (i = 0; i < 4; i++)
	{
		if (cnt[i] == 0)
		{
			avg[i] = 0;
		}
		else
		{
			avg[i] = sum[i] / cnt[i];
		}
	}

	//정렬 후 학과 이름 평점 출력
	sort(department, score, name, count);
	printArray(department, score, name, count);

	printf("조회하고자 하는 학과코드를 입력하시요 :");
	while (scanf("%d", &check) == 1)
	{
		switch (check)
		{
		case 7: printf("전자공학과 평점은 %.2lf입니다.", avg[0]); break;
		case 12: printf("사회체육과 평점은 %.2lf입니다.", avg[1]); break;
		case 81: printf("컴퓨터공학과 평점은 %.2lf입니다.", avg[2]); break;
		case 91: printf("정보통신과 평점은 %.2lf입니다.", avg[3]); break;
		default: printf("잘못입력하셨습니다."); break;
		}

		printf("\n조회하고자 하는 학과코드를 입력하시요 (조회를 그만하시려면 x키를 누르세요.):");
	}

	return 0;
}

int subjectcon(int subject) {
	int ans = 0;
	switch (subject)
	{
	case 101: ans = 3; break;
	case 102: ans = 2; break;
	case 103: ans = 1; break;
	case 105: ans = 2; break;
	case 201: ans = 3; break;
	default:
		break;
	}

	return ans;
}

int gradecon(char grade) {
	int ans = 0;
	switch (grade)
	{
	case 'A':;
	case 'a': ans = 4; break;
	case 'B':;
	case 'b': ans = 3; break;
	case 'C':;
	case 'c': ans = 2; break;
	default: break;
	}

	return ans;
}

void sort(char department[][16], double a[], char name[][10], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
			if (strcmp(name[i], name[j]) > 0) {
				swapdouble(&a[i], &a[j]);
				swapstr(name[i], name[j]);
				swapstr(department[i], department[j]);
			}
}

void swapdouble(double* x, double* y)
{
	double temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void swapstr(char* x, char* y)
{
	char temp[16];//학과이름 고려
	strcpy(temp, x);
	strcpy(x, y);
	strcpy(y, temp);
}

void printArray(char department[][16], double arr[], char na[][10], int n)
{
	int i;
	printf("\n\t학과\t이름\t평점\t\n-------------------------------\n");
	for (i = 0; i < n; i++)
		printf("%s\t%s\t%.1lf\n", department[i], na[i], arr[i]);
	printf("\n");
}