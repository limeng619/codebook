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
	printf("*                     欢迎使用密码本!                        *\n");
	printf("*                   请输入需要执行的操作:                    *\n");
	printf("*                        1 增加数据                          *\n");
	printf("*                        2 删除数据                          *\n");
	printf("*                        3 修改数据                          *\n");
	printf("*                        4 查找数据                          *\n");
	printf("*                        5 所有数据                          *\n");
	printf("*                        0 退出                              *\n");
	printf("**************************************************************\n");

	scanf("%d", &choice);//此处输入非数字时有bug
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
		printf("1 继续存储；2 删除数据；3 修改数据\n");
		printf("4 查找数据；5 所有数据；0 退出\n");
		scanf("%d", &choice);
	}
	quit();
	
	return 0;
}

void addInfo() {
	printf("请输入需要存储的 站点:");
	scanf("%s", website[count], 20);
	printf("请输入需要存储的 账号:");
	scanf("%s", username[count], 20);
	printf("请输入需要存储的 密码:");
	scanf("%s", password[count], 20);
	printf("请输入需要存储的 备注:");
	scanf("%s", info[count], 20);
	
	printf("将存储以下下信息:\n");
	printf("站点：%s\n", website[count]);
	printf("账号：%s\n", username[count]);
	printf("密码：%s\n", password[count]);
	printf("备注：%s\n", info[count]);
	count++;
	printf("存储成功!\n");
	printf("**************************************************************\n");
}

void deleteInfo() {
	int del;
	printf("请选择删除选项：\n1 删除所有数据\n2 删除某个站点数据\n");
	scanf("%d", &del);
	if(del == 1) {
		deleteAll();
	} else if(del == 2) {
		deleteOne();
	} else {
		printf("输入无效，请重新输入:\n");
		deleteInfo();
	}
}

void deleteAll() {
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
	for(i=num-1;i<count-1;i++) {
		strcpy(website[i], website[i+1]);
		strcpy(username[i], username[i+1]);
		strcpy(password[i], password[i+1]);
		strcpy(info[i], info[i+1]);
	}
	count--;
	printf("删除成功！\n");
}

void modifyInfo() {
	int num;
	printf("请输入修改第几条数据？：");
	scanf("%d", &num);
	printf("第 %d 条数据信息如下:\n", num);
	printf("站点：%s\n", website[num-1]);
	printf("账号：%s\n", username[num-1]);
	printf("密码：%s\n", password[num-1]);
	printf("备注：%s\n", info[num-1]);
	printf("请输入新的信息:\n");
	printf("新的 站点:");
	scanf("%s", website[num-1], 20);
	printf("新的 账号:");
	scanf("%s", username[num-1], 20);
	printf("新的 密码:");
	scanf("%s", password[num-1], 20);
	printf("新的 备注:");
	scanf("%s", info[num-1], 20);
	printf("修改成功！\n");
}
void searchInfo() {
	int num;
	printf("请输入查找第几条数据？：!");
	scanf("%d", &num);
	printf("第 %d 条数据信息如下:\n", num);
	printf("站点：%s\n", website[num-1]);
	printf("账号：%s\n", username[num-1]);
	printf("密码：%s\n", password[num-1]);
	printf("备注：%s\n", info[num-1]);
}
void getAllInfo() {
	int i;
	printf("当前共存储有 %d 条数据：\n", count);
	printf("**************************************************************\n");
	for(i=0;i<count;i++) {
		printf("第 %d 条数据信息如下：\n", i+1);
		printf("站点：%s\n", website[i]);
		printf("账号：%s\n", username[i]);
		printf("密码：%s\n", password[i]);
		printf("备注：%s\n", info[i]);
		printf("**************************************************************\n");
	}
}
void quit() {
	printf("谢谢使用!\n");
	printf("再见!\n");
}
void error() {
	printf("输入错误，请重新输入!\n");
}
