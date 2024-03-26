#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

//除法中分数的化简部分
void fenshu(int &a1, int &a2) {
	//a1为分子，a2为分母
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

//除法
void chufa(int str1, int str2,int str3, float &sum, int a[]) {
	int c = 0;
	sum = str1 * str3 / str2;
	c = str1 * str3 / str2;//c为带分数的整数部分
	int r = str1 * str3 % str2;//r为分子
	//'?'作为检查位置，前两种情况检测到问号则停止打印
	if (r == 0) {
		//整除
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



//生成运算
//生成n条，r以内的运算
//规定:n应该大于0,小于100，r不能小于10
void randmath(int n, int r, int answer[100], int qu[100][11]) {
	if (n < 1 || r < 10 ) {
		printf("规定:n应该大于0,r不能小于10");
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
				//双加
				k1 = 0;
				k2 = 0;
				sum = num1 + num2 + num3;
				a[0] = sum;
				a[1] = '?';
				break;
			case 1:
				//一加一减
				k1 = 0;
				k2 = 1;
				sum = num1 + num2 - num3 ;
				a[0] = sum;
				a[1] = '?';
				break;
			case 2:
				//一加一乘
				k1 = 0;
				k2 = 2;
				sum = num1 + num2 * num3;
				a[0] = sum;
				a[1] = '?';
				break;
			case 3:
				//双减
				k1=1;
				k2=1;
				sum = num1 - num2 - num3 ;
				a[0] = sum;
				a[1] = '?';

				break;
			case 4:
				//一减一加
				k1=1;
				k2=0;
				sum = num1 - num2 + num3 ;
				a[0] = sum;
				a[1] = '?';

				break;

			case 5:
				//一减一乘
				k1=1;
				k2=2;
				sum = num1 - num2 * num3 ;
				a[0] = sum;
				a[1] = '?';

				break;

			case 6:
				//一乘一加
				k1=2;
				k2=0;
				sum = num1 * num2 + num3 ;
				a[0] = sum;
				a[1] = '?';

				break;

			case 7:
				//一乘一减
				k1=2;
				k2=1;
				sum = num1 * num2 - num3 ;
				a[0] = sum;
				a[1] = '?';

				break;

			case 8:
				//双乘
				k1=2;
				k2=2;
				sum = num1 * num2 * num3;
				a[0] = sum;
				a[1] = '?';

				break;
			case 9:
				//除法
				k1=3;
				k2=3;
				chufa(num1, num2,num3, sum, a);
			default:
				break;
		}

		//把答案和题目填入数组
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



// 将题目写入文件
void write_qu(int n, int qu[100][11], FILE *file) {
	for (int i = 0; i < n; i++) {
		fprintf(file, "%d, %d%c%d%c%d%c?\n", i+1,qu[i][0],qu[i][1],qu[i][2],qu[i][3],qu[i][4],qu[i][5]);
	}
}

// 将答案写入文件
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
	printf("请输入生成题目数\n");
	scanf("%d", &n);
	printf("请输入题目范围\n");
	scanf("%d", &r);

	// 打开 Exercises.txt 文件进行写入
	FILE *exercisesFile = fopen("D:\\Exercises.txt", "w");
	if (exercisesFile == NULL) {
		printf("无法打开 Exercises.txt 文件进行写入。\n");
		return -1;
	}

	// 生成题目并写入 Exercises.txt 文件
	randmath(n, r, answer, qu);
	write_qu(n, qu, exercisesFile);
	fclose(exercisesFile); // 关闭文件

	// 打开 Answers.txt 文件进行写入
	FILE *answersFile = fopen("D:\\Answers.txt", "w");
	if (answersFile == NULL) {
		printf("无法打开 Answers.txt 文件进行写入。\n");
		return -1;
	}

	// 将答案写入 Answers.txt 文件
	write_answer(n, qu, answersFile);
	fclose(answersFile); // 关闭文件

	printf("题目和答案已生成并存入文件中。\n");

	return 0;
}
