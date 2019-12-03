#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN 255
#define MAX_COUNT 255
#define FILE_NAME "codebook.txt"
#define ERROR 1
#define OK 0

int addInfo();
void deleteInfo();
void modifyInfo();
void searchInfo();
void getAllInfo();
void quit();
void error();
void deleteAll();
void deleteOne();
void encode(char *s);


typedef struct {
	char website[LEN];
	char username[LEN];
	char password[LEN];
	char remark[LEN];
} Record;
void encodeRecord(Record* r);
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
	
	int choice = -1;
	scanf("%d", &choice);
	char tempc;
	int errTime = 0; 
	while(choice < 0 || choice > 5) {
		setbuf(stdin, NULL);//�����һ�ε����뻺��������δ��գ����ϴ�����Ϊ������ʱ����λ�scanf��ֱ��ʹ���ϴε����� 
		errTime++;
		if(errTime > 2) {
			printf("����3�ν��˳����򣬳������\n");
			return; 
		}
		printf("������Ч���������Ϊ��Ч���֣�����3�ν��˳�����������:\n");
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
	while(res != EOF && count < MAX_COUNT) {
		encodeRecord(recd);
		records[count] = recd;
		count++;
		recd = malloc(sizeof(Record));
		res = fscanf(fp, "%s%s%s%s", recd->website, recd->username, recd->password, recd->remark);
	}
	free(recd);

	fclose(fp);
}

int addInfo() {
	
	if(count >= MAX_COUNT) {
		printf("�����������洢ʧ�ܣ�");
		return ERROR;
	}
	
	Record* recd;
	recd = malloc(sizeof(Record));
	
	printf("��������Ҫ�洢�� վ��:");
	scanf("%s", recd->website, LEN);
	int i;
	for(i=0;i<count;i++) {
		if(strcmp(records[i]->website, recd->website) == 0) {
				printf("վ����Ϣ�Ѵ��ڣ����ʧ�ܣ�\n");
				free(recd);
				return ERROR;
		}
	}
	printf("��������Ҫ�洢�� �˺�:");
	scanf("%s", recd->username, LEN);
	printf("��������Ҫ�洢�� ����:");
	scanf("%s", recd->password, LEN);
	printf("��������Ҫ�洢�� ��ע:");
	scanf("%s", recd->remark, LEN);
	
	records[count++] = recd;
	printf("�洢�ɹ�!\n");
	printf("**************************************************************\n");
	return OK;
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
		printf("������Ч������������:\n");
		setbuf(stdin, NULL);
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
	char website[LEN];
	printf("��������Ҫɾ����վ�㣺");
	scanf("%s", website);
	int i;
	for(i=0;i<count;i++) {
		if(strcmp(records[i]->website, website) == 0) {
			free(records[i]); 
			int j;
			for(j=i;j<count-1;j++) {
				records[j] = records[j+1];
			}
			count--;
		}
	}
	printf("ɾ���ɹ���\n");
	printf("**************************************************************\n");
}

void modifyInfo() {
	char website[LEN];
	printf("��������Ҫ�޸ĵ�վ�㣺");
	scanf("%s", website);
	int i;
	for(i=0;i<count;i++) {
		if(strcmp(records[i]->website, website) == 0) {
				break;
		}
	}
	if(i == count) {
		printf("δ�洢��վ����Ϣ");
		return;	
	}
	printf("��վ��ԭ��Ϣ����:\n");
	printf("վ�㣺%s\n", records[i]->website);
	printf("�˺ţ�%s\n", records[i]->username);
	printf("���룺%s\n", records[i]->password);
	printf("��ע��%s\n", records[i]->remark);
	printf("�������µ���Ϣ:\n");
	printf("�µ� վ��:");
	scanf("%s", records[i]->website, LEN);
	printf("�µ� �˺�:");
	scanf("%s", records[i]->username, LEN);
	printf("�µ� ����:");
	scanf("%s", records[i]->password, LEN);
	printf("�µ� ��ע:");
	scanf("%s", records[i]->remark, LEN);
	printf("�޸ĳɹ���\n");
	printf("**************************************************************\n");
}
void searchInfo() {
	char website[LEN];
	int i;
	int temp = 0;
	printf("��������Ҫ���ҵ�վ�㣺");
	scanf("%s", website);
	printf("վ�� %s �洢��Ϣ����:\n", website);
	for(i=0;i<count;i++) {
		if(strcmp(records[i]->website, website) == 0) {
				temp++;
				printf("վ�㣺%s\n", records[i]->website);
				printf("�˺ţ�%s\n", records[i]->username);
				printf("���룺%s\n", records[i]->password);
				printf("��ע��%s\n", records[i]->remark);
		}
	}
	printf("���ϣ�����ѯ�� %d ��վ�� %s ����Ϣ\n", temp, website);
	printf("**************************************************************\n");
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

void encodeRecord(Record* r) {
	encode(r->website);
	encode(r->username);
	encode(r->password);
	encode(r->remark);
}

void encode(char *s) {
	while(*s != '\0') {
		*s = *s ^ 9;
		s++;
	}
}
void quit() {
	FILE *fp = fopen(FILE_NAME, "w");
	int i;
	for(i=0;i<count;i++) {
		encodeRecord(records[i]);
		fprintf(fp, "%s %s %s %s\n", records[i]->website, records[i]->username, records[i]->password, records[i]->remark);
	}

	fclose(fp);
	printf("ллʹ��!\n");
	printf("�ټ�!\n");
}
void error() {
	printf("�����������������:");
}
