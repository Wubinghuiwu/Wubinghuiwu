#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 10000 // ������󳤶�Ϊ10000�ַ�    

// ��������
// �淶���ַ�������
void easy(char *str);
// �����ظ��ʺ���
float compare(const char *original, const char *plagiarized);
// д�뺯������
void write(float overlap, const char *ans);

int main(int argc, char *argv[]) {

	// ԭ���ļ�·��
	const char *fp1 = argv[1];
	// ��Ϯ���ļ�·��
	const char *fp2 = argv[2];
	// ���ļ�·��
	const char *ans = argv[3];

	FILE *origFile = fopen(fp1, "r");  // ��ԭ���ļ�
	if (origFile == NULL) {
		perror("Error opening original file");  // ���ļ�ʧ��
		return 1;
	}

	FILE *plagFile = fopen(fp2, "r");  // �򿪳�Ϯ���ļ�
	if (plagFile == NULL) {
		perror("Error opening plagiarized file");  // ���ļ�ʧ��
		return 1;
	}

	char orig[MAX_LENGTH] = {0};  // ԭ������
	char plag[MAX_LENGTH] = {0};  // ��Ϯ������

	if (fgets(orig, MAX_LENGTH, origFile) == NULL) {
		perror("Error reading original file");  // ��ȡԭ���ļ�ʧ�ܣ����������Ϣ
		fclose(origFile);  // �ر��Ѵ򿪵��ļ�
		return 1;
	}

	if (fgets(plag, MAX_LENGTH, plagFile) == NULL) {
		perror("Error reading plagiarized file");  // ��ȡ��Ϯ���ļ�ʧ�ܣ����������Ϣ
		fclose(plagFile);  // �ر��Ѵ򿪵��ļ�
		return 1;
	}

	fclose(origFile);  // �ر�ԭ���ļ�
	fclose(plagFile);  // �رճ�Ϯ���ļ�

	easy(orig);  // �淶��ԭ������
	easy(plag);  // �淶����Ϯ������

	float overlap = compare(orig, plag);  // �����ظ���
	write(overlap, ans);  // д��𰸵����ļ�

	return 0;  // ���������˳�
}

void easy(char *str) {
	int a = 0, b = 0, i = 0;
	for (i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);  // ���ַ�ת��ΪСд
		if (!isalnum(str[i])) {  // ���������ĸ������
			str[i] = ' ';  // ���滻Ϊ�ո�
		}
	}
}


void write(float overlap, const char *ans) {
	FILE *ansFile = fopen(ans, "w");
	if (ansFile == NULL) {
		perror("Error opening answer file");
		exit(EXIT_FAILURE);
	}

	// ���ظ��ʸ�ʽ��Ϊ��λС�����ַ���
	char in[10];
	snprintf(in, sizeof(in), "%.2f", overlap);

	// д����ļ�
	fprintf(ansFile, "%s%%\n", in);

	// �ر��ļ�
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