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
	printf("*                     欢迎使用密码本!                        *\n");
	printf("*                   请输入需要执行的操作:                    *\n");
	printf("*                        1 增加数据                          *\n");
	printf("*                        2 删除数据                          *\n");
	printf("*                        3 修改数据                          *\n");
	printf("*                        4 查找数据                          *\n");
	printf("*                        5 所有数据                          *\n");
	printf("*                        0 退出                              *\n");
	printf("**************************************************************\n");
	
	int choice = -1;
	scanf("%d", &choice);
	char tempc;
	int errTime = 0; 
	while(choice < 0 || choice > 5) {
		setbuf(stdin, NULL);//清空上一次的输入缓冲区。如未清空，当上次输入为非数字时，这次会scanf会直接使用上次的输入 
		errTime++;
		if(errTime > 2) {
			printf("错误3次将退出程序，程序结束\n");
			return; 
		}
		printf("输入无效，输入必须为有效数字，错误3次将退出程序，请重输:\n");
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
		printf("1 继续存储；2 删除数据；3 修改数据\n");
		printf("4 查找数据；5 所有数据；0 退出\n");
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
		printf("容量已满，存储失败！");
		return ERROR;
	}
	
	Record* recd;
	recd = malloc(sizeof(Record));
	
	printf("请输入需要存储的 站点:");
	scanf("%s", recd->website, LEN);
	int i;
	for(i=0;i<count;i++) {
		if(strcmp(records[i]->website, recd->website) == 0) {
				printf("站点信息已存在，添加失败！\n");
				free(recd);
				return ERROR;
		}
	}
	printf("请输入需要存储的 账号:");
	scanf("%s", recd->username, LEN);
	printf("请输入需要存储的 密码:");
	scanf("%s", recd->password, LEN);
	printf("请输入需要存储的 备注:");
	scanf("%s", recd->remark, LEN);
	
	records[count++] = recd;
	printf("存储成功!\n");
	printf("**************************************************************\n");
	return OK;
}

void deleteInfo() {
	int del;
	printf("请选择删除选项：1 删除所有数据; 2 删除某个站点数据\n");
	scanf("%d", &del);
	if(del == 1) {
		deleteAll();
	} else if(del == 2) {
		deleteOne();
	} else {
		printf("输入无效，请重新输入:\n");
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
	printf("数据删除成功！\n");
}

void deleteOne() {
	char website[LEN];
	printf("请输入需要删除的站点：");
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
	printf("删除成功！\n");
	printf("**************************************************************\n");
}

void modifyInfo() {
	char website[LEN];
	printf("请输入需要修改的站点：");
	scanf("%s", website);
	int i;
	for(i=0;i<count;i++) {
		if(strcmp(records[i]->website, website) == 0) {
				break;
		}
	}
	if(i == count) {
		printf("未存储该站点信息");
		return;	
	}
	printf("该站点原信息如下:\n");
	printf("站点：%s\n", records[i]->website);
	printf("账号：%s\n", records[i]->username);
	printf("密码：%s\n", records[i]->password);
	printf("备注：%s\n", records[i]->remark);
	printf("请输入新的信息:\n");
	printf("新的 站点:");
	scanf("%s", records[i]->website, LEN);
	printf("新的 账号:");
	scanf("%s", records[i]->username, LEN);
	printf("新的 密码:");
	scanf("%s", records[i]->password, LEN);
	printf("新的 备注:");
	scanf("%s", records[i]->remark, LEN);
	printf("修改成功！\n");
	printf("**************************************************************\n");
}
void searchInfo() {
	char website[LEN];
	int i;
	int temp = 0;
	printf("请输入需要查找的站点：");
	scanf("%s", website);
	printf("站点 %s 存储信息如下:\n", website);
	for(i=0;i<count;i++) {
		if(strcmp(records[i]->website, website) == 0) {
				temp++;
				printf("站点：%s\n", records[i]->website);
				printf("账号：%s\n", records[i]->username);
				printf("密码：%s\n", records[i]->password);
				printf("备注：%s\n", records[i]->remark);
		}
	}
	printf("以上，共查询到 %d 条站点 %s 的信息\n", temp, website);
	printf("**************************************************************\n");
}
void getAllInfo() {
	
	int i;
	printf("当前共存储有 %d 条数据：\n", count);
	printf("**************************************************************\n");
	for(i=0;i<count;i++) {
		printf("第 %d 条数据信息如下：\n", i+1);
		printf("站点：%s\n", records[i]->website);
		printf("账号：%s\n", records[i]->username);
		printf("密码：%s\n", records[i]->password);
		printf("备注：%s\n", records[i]->remark);
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
	printf("谢谢使用!\n");
	printf("再见!\n");
}
void error() {
	printf("输入错误，请重新输入:");
}
