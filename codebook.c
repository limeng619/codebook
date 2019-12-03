#include <stdio.h>
#include <string.h>

#define LEN 255
#define MAX_COUNT 255
#define FILE_NAME "codebook.txt"

void addInfo();
void deleteInfo();
void modifyInfo();
void searchInfo();
void getAllInfo();
void quit();
void error();
void deleteAll();
void deleteOne();

typedef struct {
	char website[LEN];
	char username[LEN];
	char password[LEN];
	char remark[LEN];
} Record;

Record* records[MAX_COUNT];
int count = 0;

int main() {

	init();
	

	printf("**************************************************************\n");
	printf("*                     ��ӭʹ�����뱾!                        *\n");
	printf("*                   ��������Ҫִ�еĲ���:                    *\n");
	printf("*                        1 ��������                          *\n");
	printf("*                        2 ɾ������                          *\n");
	printf("*                        3 �޸�����                          *\n");
	printf("*                        4 ��������                          *\n");
	printf("*                        5 ��������                          *\n");
	printf("*                        0 �˳�                              *\n");
	printf("**************************************************************\n");
	
	int choice = 1;
	scanf("%d", &choice);
	while(choice < 0 || choice > 5) {
		printf("������Ч��������:");
		scanf("%d", &choice);
	} 
	while(choice != 0) {
		switch(choice) {
			case 1:
				addInfo();
				break;
			case 2:
				deleteInfo();
				break;
			case 3:
				modifyInfo();
				break;
			case 4:
				searchInfo();
				break;
			case 5:
				getAllInfo();
				break;
			default:
				error();
				break;
		}
		printf("1 �����洢��2 ɾ�����ݣ�3 �޸�����\n");
		printf("4 �������ݣ�5 �������ݣ�0 �˳�\n");
		scanf("%d", &choice);
	}
	quit();
	
	return 0;
}

void init() {
	FILE *fp = fopen(FILE_NAME, "r");
	
	if(fp == NULL) {
		return;
	}
	
	Record* recd;
	recd = malloc(sizeof(Record));
	int res = fscanf(fp, "%s%s%s%s", recd->website, recd->username, recd->password, recd->remark);
	while(res != EOF) {
		records[count] = recd;
		count++;
		recd = malloc(sizeof(Record));
		res = fscanf(fp, "%s%s%s%s", recd->website, recd->username, recd->password, recd->remark);
	}
	free(recd);

	fclose(fp);
}

void addInfo() {
	
	Record* recd;
	recd = malloc(sizeof(Record));
	
	printf("��������Ҫ�洢�� վ��:");
	scanf("%s", recd->website, LEN);
	printf("��������Ҫ�洢�� �˺�:");
	scanf("%s", recd->username, LEN);
	printf("��������Ҫ�洢�� ����:");
	scanf("%s", recd->password, LEN);
	printf("��������Ҫ�洢�� ��ע:");
	scanf("%s", recd->remark, LEN);
	
	records[count++] = recd;
	printf("�洢�ɹ�!\n");
	printf("**************************************************************\n");
}

void deleteInfo() {
	int del;
	printf("��ѡ��ɾ��ѡ�1 ɾ����������; 2 ɾ��ĳ��վ������\n");
	scanf("%d", &del);
	if(del == 1) {
		deleteAll();
	} else if(del == 2) {
		deleteOne();
	} else {
		printf("������Ч������������:");
		deleteInfo();
	}
}

void deleteAll() {
	int i;
	for(i=0;i<count;i++) {
		free(records[i]);
	}
	count = 0;
	printf("����ɾ���ɹ���\n");
}

void deleteOne() {
	int num;
	int i;
	printf("������ɾ���ڼ������ݣ���");
	scanf("%d", &num);
	while(num < 1 || num > count) {
		printf("������������䣺");
		scanf("%d", &num);
	}
	free(records[num-1]);
	for(i=num-1;i<count-1;i++) {
		records[num-1] = records[num];
	}
	count--;
	printf("ɾ���ɹ���\n");
}

void modifyInfo() {
	int num;
	printf("�������޸ĵڼ������ݣ���");
	scanf("%d", &num);
	printf("�� %d ��������Ϣ����:\n", num);
	printf("վ�㣺%s\n", records[num-1]->website);
	printf("�˺ţ�%s\n", records[num-1]->username);
	printf("���룺%s\n", records[num-1]->password);
	printf("��ע��%s\n", records[num-1]->remark);
	printf("�������µ���Ϣ:\n");
	printf("�µ� վ��:");
	scanf("%s", records[num-1]->website, LEN);
	printf("�µ� �˺�:");
	scanf("%s", records[num-1]->username, LEN);
	printf("�µ� ����:");
	scanf("%s", records[num-1]->password, LEN);
	printf("�µ� ��ע:");
	scanf("%s", records[num-1]->remark, LEN);
	printf("�޸ĳɹ���\n");
}
void searchInfo() {
	int num;
	printf("��������ҵڼ������ݣ���!");
	scanf("%d", &num);
	printf("�� %d ��������Ϣ����:\n", num);
	printf("վ�㣺%s\n", records[num-1]->website);
	printf("�˺ţ�%s\n", records[num-1]->username);
	printf("���룺%s\n", records[num-1]->password);
	printf("��ע��%s\n", records[num-1]->remark);

}
void getAllInfo() {
	
	int i;
	printf("��ǰ���洢�� %d �����ݣ�\n", count);
	printf("**************************************************************\n");
	for(i=0;i<count;i++) {
		printf("�� %d ��������Ϣ���£�\n", i+1);
		printf("վ�㣺%s\n", records[i]->website);
		printf("�˺ţ�%s\n", records[i]->username);
		printf("���룺%s\n", records[i]->password);
		printf("��ע��%s\n", records[i]->remark);
		printf("**************************************************************\n");
	}
	
}
void quit() {
	FILE *fp = fopen(FILE_NAME, "w");
	int i;
	for(i=0;i<count;i++) {
		fprintf(fp, "%s %s %s %s\n", records[i]->website, records[i]->username, records[i]->password, records[i]->remark);
	}

	fclose(fp);
	printf("ллʹ��!\n");
	printf("�ټ�!\n");
}
void error() {
	printf("�����������������:");
}
