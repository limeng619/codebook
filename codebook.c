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
	printf("*                     欢迎使用密码本!                        *\n");
	printf("*                   请输入需要执行的操作:                    *\n");
	printf("*                        1 增加数据                          *\n");
	printf("*                        2 删除数据                          *\n");
	printf("*                        3 修改数据                          *\n");
	printf("*                        4 查找数据                          *\n");
	printf("*                        5 所有数据                          *\n");
	printf("*                        0 退出                              *\n");
	printf("**************************************************************\n");
	
	int choice = 1;
	scanf("%d", &choice);
	while(choice < 0 || choice > 5) {
		printf("输入无效，请重输:");
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
	
	printf("请输入需要存储的 站点:");
	scanf("%s", recd->website, LEN);
	printf("请输入需要存储的 账号:");
	scanf("%s", recd->username, LEN);
	printf("请输入需要存储的 密码:");
	scanf("%s", recd->password, LEN);
	printf("请输入需要存储的 备注:");
	scanf("%s", recd->remark, LEN);
	
	records[count++] = recd;
	printf("存储成功!\n");
	printf("**************************************************************\n");
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
		printf("输入无效，请重新输入:");
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
	int num;
	int i;
	printf("请输入删除第几条数据？：");
	scanf("%d", &num);
	while(num < 1 || num > count) {
		printf("输入错误，请重输：");
		scanf("%d", &num);
	}
	free(records[num-1]);
	for(i=num-1;i<count-1;i++) {
		records[num-1] = records[num];
	}
	count--;
	printf("删除成功！\n");
}

void modifyInfo() {
	int num;
	printf("请输入修改第几条数据？：");
	scanf("%d", &num);
	printf("第 %d 条数据信息如下:\n", num);
	printf("站点：%s\n", records[num-1]->website);
	printf("账号：%s\n", records[num-1]->username);
	printf("密码：%s\n", records[num-1]->password);
	printf("备注：%s\n", records[num-1]->remark);
	printf("请输入新的信息:\n");
	printf("新的 站点:");
	scanf("%s", records[num-1]->website, LEN);
	printf("新的 账号:");
	scanf("%s", records[num-1]->username, LEN);
	printf("新的 密码:");
	scanf("%s", records[num-1]->password, LEN);
	printf("新的 备注:");
	scanf("%s", records[num-1]->remark, LEN);
	printf("修改成功！\n");
}
void searchInfo() {
	int num;
	printf("请输入查找第几条数据？：!");
	scanf("%d", &num);
	printf("第 %d 条数据信息如下:\n", num);
	printf("站点：%s\n", records[num-1]->website);
	printf("账号：%s\n", records[num-1]->username);
	printf("密码：%s\n", records[num-1]->password);
	printf("备注：%s\n", records[num-1]->remark);

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
void quit() {
	FILE *fp = fopen(FILE_NAME, "w");
	int i;
	for(i=0;i<count;i++) {
		fprintf(fp, "%s %s %s %s\n", records[i]->website, records[i]->username, records[i]->password, records[i]->remark);
	}

	fclose(fp);
	printf("谢谢使用!\n");
	printf("再见!\n");
}
void error() {
	printf("输入错误，请重新输入:");
}
