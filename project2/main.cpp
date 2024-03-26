#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

//�����з����Ļ��򲿷�
void fenshu(int &a1, int &a2) {
	//a1Ϊ���ӣ�a2Ϊ��ĸ
	int i = a2 - 1;
	while (i > 0) {
		if (a2 % i == 0)
			if (a1 % i == 0) {
				a2 = a2 / i;
				a1 = a1 / i;
			}
		i--;
	}
}

//����
void chufa(int str1, int str2,int str3, float &sum, int a[]) {
	int c = 0;
	sum = str1 * str3 / str2;
	c = str1 * str3 / str2;//cΪ����������������
	int r = str1 * str3 % str2;//rΪ����
	//'?'��Ϊ���λ�ã�ǰ���������⵽�ʺ���ֹͣ��ӡ
	if (r == 0) {
		//����
		a[0] = c;
		a[1] = '?';
	} else if (c == 0) {
		fenshu(r, str2);
		a[0] = r;
		a[1] = '/';
		a[2] = str2;
		a[3] = '?';
	} else {
		fenshu(r, str2);
		a[0] = c;
		a[1] = '\'';
		a[2] = r;
		a[3] = '/';
		a[4] = str2;
	}


}



//��������
//����n����r���ڵ�����
//�涨:nӦ�ô���0,С��100��r����С��10
void randmath(int n, int r, int answer[100], int qu[100][11]) {
	if (n < 1 || r < 10 ) {
		printf("�涨:nӦ�ô���0,r����С��10");
		return;
	}

	int i = 0,k1,k2;
	float sum = 0;
	for (; i < n; i++) {
		int num1 = rand() % r;
		int num2 = rand() % r;
		int num3 = rand() % r;
		int fuhao[4] = { '+', '-', '*', '/' };
		int f = rand() % 10;
		int a[5] = { 0, 0, 0, 0, 0 };
		switch (f) {

			case 0:
				//˫��
				k1 = 0;
				k2 = 0;
				sum = num1 + num2 + num3;
				a[0] = sum;
				a[1] = '?';
				break;
			case 1:
				//һ��һ��
				k1 = 0;
				k2 = 1;
				sum = num1 + num2 - num3 ;
				a[0] = sum;
				a[1] = '?';
				break;
			case 2:
				//һ��һ��
				k1 = 0;
				k2 = 2;
				sum = num1 + num2 * num3;
				a[0] = sum;
				a[1] = '?';
				break;
			case 3:
				//˫��
				k1=1;
				k2=1;
				sum = num1 - num2 - num3 ;
				a[0] = sum;
				a[1] = '?';

				break;
			case 4:
				//һ��һ��
				k1=1;
				k2=0;
				sum = num1 - num2 + num3 ;
				a[0] = sum;
				a[1] = '?';

				break;

			case 5:
				//һ��һ��
				k1=1;
				k2=2;
				sum = num1 - num2 * num3 ;
				a[0] = sum;
				a[1] = '?';

				break;

			case 6:
				//һ��һ��
				k1=2;
				k2=0;
				sum = num1 * num2 + num3 ;
				a[0] = sum;
				a[1] = '?';

				break;

			case 7:
				//һ��һ��
				k1=2;
				k2=1;
				sum = num1 * num2 - num3 ;
				a[0] = sum;
				a[1] = '?';

				break;

			case 8:
				//˫��
				k1=2;
				k2=2;
				sum = num1 * num2 * num3;
				a[0] = sum;
				a[1] = '?';

				break;
			case 9:
				//����
				k1=3;
				k2=3;
				chufa(num1, num2,num3, sum, a);
			default:
				break;
		}

		//�Ѵ𰸺���Ŀ��������
		answer[i] = (int)sum;
		qu[i][0] = num1;
		qu[i][1] = fuhao[k1];
		qu[i][2] = num2;
        qu[i][3] = fuhao[k2];
        qu[i][4] = num3;
		qu[i][5] = '=';
		qu[i][6] = a[0];
		qu[i][7] = a[1];
		if (a[1] != '?') {
			qu[i][8] = a[2];
			qu[i][9] = a[3];
			if (a[3] != '?') {
				qu[i][10] = a[4];
				qu[i][11] = '?';
			}
		}
		int temp = 0 ;
		if(a[0]<0){
			temp = 1;
		}
		if (temp == 1)
			i--;
	}
}



// ����Ŀд���ļ�
void write_qu(int n, int qu[100][11], FILE *file) {
	for (int i = 0; i < n; i++) {
		fprintf(file, "%d, %d%c%d%c%d%c?\n", i+1,qu[i][0],qu[i][1],qu[i][2],qu[i][3],qu[i][4],qu[i][5]);
	}
}

// ����д���ļ�
void write_answer(int n, int qu[100][11], FILE *file) {
	for (int i = 0; i < n; i++) {
		fprintf(file, "%d, %d",i+1, qu[i][6]);
		if (qu[i][7] != '?') {
			fprintf(file, "%c%d", qu[i][8], qu[i][9]);
			if (qu[i][9] != '?') {
				fprintf(file, "%c%d", qu[i][10], qu[i][11]);
			}
		}
		fprintf(file, "\n");
	}
}



int main() {
	int answer[100] = { 0 };
	int qu[100][11] = { 0 };
	int n = 0;
	int r = 0;
	printf("������������Ŀ��\n");
	scanf("%d", &n);
	printf("��������Ŀ��Χ\n");
	scanf("%d", &r);

	// �� Exercises.txt �ļ�����д��
	FILE *exercisesFile = fopen("D:\\Exercises.txt", "w");
	if (exercisesFile == NULL) {
		printf("�޷��� Exercises.txt �ļ�����д�롣\n");
		return -1;
	}

	// ������Ŀ��д�� Exercises.txt �ļ�
	randmath(n, r, answer, qu);
	write_qu(n, qu, exercisesFile);
	fclose(exercisesFile); // �ر��ļ�

	// �� Answers.txt �ļ�����д��
	FILE *answersFile = fopen("D:\\Answers.txt", "w");
	if (answersFile == NULL) {
		printf("�޷��� Answers.txt �ļ�����д�롣\n");
		return -1;
	}

	// ����д�� Answers.txt �ļ�
	write_answer(n, qu, answersFile);
	fclose(answersFile); // �ر��ļ�

	printf("��Ŀ�ʹ������ɲ������ļ��С�\n");

	return 0;
}
