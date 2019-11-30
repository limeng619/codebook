#include <stdio.h>
#include <string.h>
void addInfo();
void deleteInfo();
void modifyInfo();
void searchInfo();
void getAllInfo();
void quit();
void error();
void deleteAll();
void deleteOne();

char website[100][20];
char username[100][20];
char password[100][20];
char info[100][20];

int count = 0;

int main(void) {

	int choice = 1;

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

	scanf("%d", &choice);//�˴����������ʱ��bug
	//printf("%d \n", choice);
	while(choice) {
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

void addInfo() {
	printf("��������Ҫ�洢�� վ��:");
	scanf("%s", website[count], 20);
	printf("��������Ҫ�洢�� �˺�:");
	scanf("%s", username[count], 20);
	printf("��������Ҫ�洢�� ����:");
	scanf("%s", password[count], 20);
	printf("��������Ҫ�洢�� ��ע:");
	scanf("%s", info[count], 20);
	
	printf("���洢��������Ϣ:\n");
	printf("վ�㣺%s\n", website[count]);
	printf("�˺ţ�%s\n", username[count]);
	printf("���룺%s\n", password[count]);
	printf("��ע��%s\n", info[count]);
	count++;
	printf("�洢�ɹ�!\n");
	printf("**************************************************************\n");
}

void deleteInfo() {
	int del;
	printf("��ѡ��ɾ��ѡ�\n1 ɾ����������\n2 ɾ��ĳ��վ������\n");
	scanf("%d", &del);
	if(del == 1) {
		deleteAll();
	} else if(del == 2) {
		deleteOne();
	} else {
		printf("������Ч������������:\n");
		deleteInfo();
	}
}

void deleteAll() {
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
	for(i=num-1;i<count-1;i++) {
		strcpy(website[i], website[i+1]);
		strcpy(username[i], username[i+1]);
		strcpy(password[i], password[i+1]);
		strcpy(info[i], info[i+1]);
	}
	count--;
	printf("ɾ���ɹ���\n");
}

void modifyInfo() {
	int num;
	printf("�������޸ĵڼ������ݣ���");
	scanf("%d", &num);
	printf("�� %d ��������Ϣ����:\n", num);
	printf("վ�㣺%s\n", website[num-1]);
	printf("�˺ţ�%s\n", username[num-1]);
	printf("���룺%s\n", password[num-1]);
	printf("��ע��%s\n", info[num-1]);
	printf("�������µ���Ϣ:\n");
	printf("�µ� վ��:");
	scanf("%s", website[num-1], 20);
	printf("�µ� �˺�:");
	scanf("%s", username[num-1], 20);
	printf("�µ� ����:");
	scanf("%s", password[num-1], 20);
	printf("�µ� ��ע:");
	scanf("%s", info[num-1], 20);
	printf("�޸ĳɹ���\n");
}
void searchInfo() {
	int num;
	printf("��������ҵڼ������ݣ���!");
	scanf("%d", &num);
	printf("�� %d ��������Ϣ����:\n", num);
	printf("վ�㣺%s\n", website[num-1]);
	printf("�˺ţ�%s\n", username[num-1]);
	printf("���룺%s\n", password[num-1]);
	printf("��ע��%s\n", info[num-1]);
}
void getAllInfo() {
	int i;
	printf("��ǰ���洢�� %d �����ݣ�\n", count);
	printf("**************************************************************\n");
	for(i=0;i<count;i++) {
		printf("�� %d ��������Ϣ���£�\n", i+1);
		printf("վ�㣺%s\n", website[i]);
		printf("�˺ţ�%s\n", username[i]);
		printf("���룺%s\n", password[i]);
		printf("��ע��%s\n", info[i]);
		printf("**************************************************************\n");
	}
}
void quit() {
	printf("ллʹ��!\n");
	printf("�ټ�!\n");
}
void error() {
	printf("�����������������!\n");
}
