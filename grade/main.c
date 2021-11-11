#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#define CNT 15//�л��� �ִ� 15
#define YEAR 2021//���� �⵵ �й� ����ó�� �Ҷ� ���

int subjectcon(int subject);//�����ڵ�->�������� ��ȯ ex)105->3
int gradecon(char grade);//����->������ ��ȯ ex)A->4
void sort(char department[][16], double a[], char name[][10], int n);//�̸����� �������� ����
void swapdouble(double* x, double* y);//������ �ڸ��� �ٲ���
void swapstr(char* x, char* y);//���ڿ��� �ڸ��� �ٲ���
void printArray(char department[][16], double arr[], char na[][10], int n);//���

int main() {
	int i, j;
	int count; //�л��� ����
	int student[CNT];//�Է¹迭 �й�
	int subject[2][CNT];//����1�ڵ� ����2�ڵ� 
	char grade[2][CNT];//����1���� ����2����
	char name[CNT][10];//�Է¹迭 �̸�
	int dm[CNT]; //�й����� �а��� ����
	int found;//�Է½� Ʋ�� Ƚ�� ����
	char department[CNT][16]; //�а� ���ڿ� ����
	int cnt[4] = { 0, }; //�а��� �ο�
	double sum[4] = { 0, }, avg[4] = { 0, }; //�а��� ��������, ���
	int check;//��ȸ�ϰ����ϴ� �а� �ڵ�
	double score[CNT];//��¹迭 ����


	do
	{
		printf("�л� ���� �Է��Ͻÿ�:");
		scanf("%d", &count);
		if (count > CNT || count < 1)
		{
			printf("�߸��Է��߽��ϴ�.\n");
		}
	} while (count > CNT || count < 1);

	//�й� ����1�ڵ� ����1���� ����2�ڵ� ����2���� �̸� �Է� �й����� �а� ����
	for (i = 0; i < count; i++)
	{
		found = 0;
		printf("�й� �̸� ����1�ڵ� ���� ����2�ڵ� ���� �Է��Ͻÿ�:");
		scanf("%d %s %d %c %d %c", &student[i], name[i], &subject[0][i], &grade[0][i], &subject[1][i], &grade[1][i]);
		dm[i] = ((student[i] / 1000) % 1000);

		for (j = i - 1; j >= 0; j--)
		{
			if (student[i] == student[j])
			{
				printf("�й�(�ߺ�) ");
				found++;
			}
		}
		if (((student[i] / 1000000) % 10000) < 1970 || ((student[i] / 1000000) % 10000) > YEAR)
		{
			printf("�й�(���г⵵) ");
			found++;
		}
		if (dm[i] != 7 && dm[i] != 12 && dm[i] != 81 && dm[i] != 91)
		{
			printf("�й�(�а��ڵ�) ");
			found++;
		}

		for (j = 0; j < 2; j++)
		{
			if (subject[j][i] != 101 && subject[j][i] != 102 && subject[j][i] != 103 && subject[j][i] != 105 && subject[j][i] != 201)
			{
				printf("�����ڵ� ");
				found++;
			}
		}
		if (subject[0][i] == subject[1][i])
		{
			printf("�����ڵ�(�ߺ�) ");
			found++;
		}

		for (j = 0; j < 2; j++)
		{
			if (grade[j][i] != 'A' && grade[j][i] != 'B' && grade[j][i] != 'C' && grade[j][i] != 'a' && grade[j][i] != 'b' && grade[j][i] != 'c')
			{
				printf("���� ");
				found++;
			}
		}

		if (found != 0)
		{
			printf("(��)�� �߸��Է��߽��ϴ�.\n");
			i--;
		}
	}

	//�������
	for (i = 0; i < count; i++)
	{
		score[i] = (double)(subjectcon(subject[0][i]) * gradecon(grade[0][i]) + subjectcon(subject[1][i]) * gradecon(grade[1][i])) / (subjectcon(subject[0][i]) + subjectcon(subject[1][i]));
	}

	//�а��� ���� ��� �� �а� ���ڿ� ����
	for (i = 0; i < count; i++)
	{
		switch (dm[i])
		{
		case 7: strcpy(department[i], "���ڰ��а�"); sum[0] += score[i]; cnt[0]++; break;
		case 12: strcpy(department[i], "��ȸü����"); sum[1] += score[i]; cnt[1]++; break;
		case 81: strcpy(department[i], "��ǻ�Ͱ��а�"); sum[2] += score[i]; cnt[2]++; break;
		case 91: strcpy(department[i], "������Ű�"); sum[3] += score[i]; cnt[3]++; break;
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

	//���� �� �а� �̸� ���� ���
	sort(department, score, name, count);
	printArray(department, score, name, count);

	printf("��ȸ�ϰ��� �ϴ� �а��ڵ带 �Է��Ͻÿ� :");
	while (scanf("%d", &check) == 1)
	{
		switch (check)
		{
		case 7: printf("���ڰ��а� ������ %.2lf�Դϴ�.", avg[0]); break;
		case 12: printf("��ȸü���� ������ %.2lf�Դϴ�.", avg[1]); break;
		case 81: printf("��ǻ�Ͱ��а� ������ %.2lf�Դϴ�.", avg[2]); break;
		case 91: printf("������Ű� ������ %.2lf�Դϴ�.", avg[3]); break;
		default: printf("�߸��Է��ϼ̽��ϴ�."); break;
		}

		printf("\n��ȸ�ϰ��� �ϴ� �а��ڵ带 �Է��Ͻÿ� (��ȸ�� �׸��Ͻ÷��� xŰ�� ��������.):");
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
	char temp[16];//�а��̸� ���
	strcpy(temp, x);
	strcpy(x, y);
	strcpy(y, temp);
}

void printArray(char department[][16], double arr[], char na[][10], int n)
{
	int i;
	printf("\n\t�а�\t�̸�\t����\t\n-------------------------------\n");
	for (i = 0; i < n; i++)
		printf("%s\t%s\t%.1lf\n", department[i], na[i], arr[i]);
	printf("\n");
}