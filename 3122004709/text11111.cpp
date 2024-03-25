#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 10000 // 假设最大长度为10000字符    

// 函数声明
// 规范化字符串函数
void easy(char *str);
// 计算重复率函数
float compare(const char *original, const char *plagiarized);
// 写入函数声明
void write(float overlap, const char *ans);

int main(int argc, char *argv[]) {

	// 原文文件路径
	const char *fp1 = argv[1];
	// 抄袭文文件路径
	const char *fp2 = argv[2];
	// 答案文件路径
	const char *ans = argv[3];

	FILE *origFile = fopen(fp1, "r");  // 打开原文文件
	if (origFile == NULL) {
		perror("Error opening original file");  // 打开文件失败
		return 1;
	}

	FILE *plagFile = fopen(fp2, "r");  // 打开抄袭文文件
	if (plagFile == NULL) {
		perror("Error opening plagiarized file");  // 打开文件失败
		return 1;
	}

	char orig[MAX_LENGTH] = {0};  // 原文内容
	char plag[MAX_LENGTH] = {0};  // 抄袭文内容

	if (fgets(orig, MAX_LENGTH, origFile) == NULL) {
		perror("Error reading original file");  // 读取原文文件失败，输出错误信息
		fclose(origFile);  // 关闭已打开的文件
		return 1;
	}

	if (fgets(plag, MAX_LENGTH, plagFile) == NULL) {
		perror("Error reading plagiarized file");  // 读取抄袭文文件失败，输出错误信息
		fclose(plagFile);  // 关闭已打开的文件
		return 1;
	}

	fclose(origFile);  // 关闭原文文件
	fclose(plagFile);  // 关闭抄袭文文件

	easy(orig);  // 规范化原文内容
	easy(plag);  // 规范化抄袭文内容

	float overlap = compare(orig, plag);  // 计算重复率
	write(overlap, ans);  // 写入答案到答案文件

	return 0;  // 程序正常退出
}

void easy(char *str) {
	int a = 0, b = 0, i = 0;
	for (i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);  // 将字符转换为小写
		if (!isalnum(str[i])) {  // 如果不是字母或数字
			str[i] = ' ';  // 则替换为空格
		}
	}
}


void write(float overlap, const char *ans) {
	FILE *ansFile = fopen(ans, "w");
	if (ansFile == NULL) {
		perror("Error opening answer file");
		exit(EXIT_FAILURE);
	}

	// 将重复率格式化为两位小数的字符串
	char in[10];
	snprintf(in, sizeof(in), "%.2f", overlap);

	// 写入答案文件
	fprintf(ansFile, "%s%%\n", in);

	// 关闭文件
	fclose(ansFile);
}

float compare(const char *orig, const char *plag) {
	int origLength = strlen(orig);
	int plagLength = strlen(plag);
	int number = 0;

	for (int i = 0; i < plagLength; i++) {
		for (int j = 0; j <= origLength - plagLength + i; j++) {
			int temp = 1;
			for (int k = 0; k < plagLength - i; k++) {
				if (orig[j + k] != plag[i + k]) {
					temp = 0;
					break;
				}
			}
			if (temp) {
				number = plagLength - i;
				break;
			}
		}
	}

	return (float)number / plagLength * 1000.0;
}