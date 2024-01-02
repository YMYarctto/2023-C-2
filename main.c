#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define storeTxt "store.sav"

struct Goods goods[20];
struct node *buyList;
int N = 0;

int main() {
	printf("*********************************************************\n");
	printf("             欢迎进入购物车————超市信息管理系统\n");
	printf("*********************************************************\n");

	mainStore();
}

void mainStore() {
	while (1) {
		switch (mainStoreMenu()) {
			case 1:
				addStore();
				break;

			case 2:
				showStore();
				break;

			case 3:
				addBuy();
				break;

			case 4:
				//TODO About
				break;

			case 5:
				system("cls");
				printf("感谢您的使用，再见！\n");
				Sleep(2000);
				exit(0);
		}
	}
}

void  mainBuy() {
	while (1) {
		switch (mainBuyMenu()) {
			case 1:
				showBuy();
				break;
			case 2:
				addBuy();
				break;
			case 3:
				calculate();
				break;
			case 4:
				return ;
		}
	}
}

void addStore() {
	char choice;
	printf("请依次输入货物信息：\n");
	printf("--------------------------------------------\n");
	while (N < 20) {
		//向文件中写入信息
		printf("输入添加的商品信息：\n");
		printf("货号：");
		fflush(stdin);
		gets(goods[N].ID);

		printf("品名：");
		fflush(stdin);
		gets(goods[N].brand);

		printf("进价: ");
		fflush(stdin);
		scanf("%lf", &goods[N].inprice);

		printf("售价：");
		fflush(stdin);
		scanf("%lf", &goods[N].outprice);

		printf("数量：");
		fflush(stdin);
		scanf("%d", &goods[N].storage);
		printf("\n");
		N += 1;

		printf("输入y/Y以继续添加\n");
		fflush(stdin);
		scanf("%s", &choice);
		if (choice != 'y' && choice != 'Y') {
			printf("已返回菜单\n");
			break;
		}
	}
	save();
}

void save() {
	FILE *fp;
	for (int i = 0; i < N; i++) {
		if ((fp = fopen(storeTxt, "w")) == NULL) {
			printf("Error:创建文件失败。\n");
			return ;
		}
		fprintf(fp, "%-11s%-15s%-10.2f%-10.2f%-7d\n", goods[i].ID, goods[i].brand, goods[i].inprice, goods[i].outprice,
		        goods[i].storage);
	}
	fclose(fp);
	printf("信息导入成功\n");
}


void showStore() {
	//显示库存信息函数
	FILE *fp;//定义文件指针
	if ((fp = fopen(storeTxt, "r")) == NULL) {
		//判断是否打开了文件
		printf("Error:打开文件失败\n");
		return ;
	}

	for (int i = 0; i < N; i++) {
		//输出物品信息
		//读取文件信息
		fscanf(fp, "%s%s%lf%lf%d", goods[i].ID, goods[i].brand, &goods[i].inprice, &goods[i].outprice, &goods[i].storage);
		printf("--------------------------------------------\n");
		//输出文件信息
		printf("货号       品名           单价    库存量\n");
		printf("%-11s%-15s%-10.2f%-7d\n", goods[i].ID, goods[i].brand, goods[i].outprice, goods[i].storage);
	}
	fclose(fp);//关闭文件
}

void showBuy() {
	struct node *p = buyList;
	if (p == NULL) {
		//购物车为空
		printf("目前购物车为空：");
		return ;
	}
	//购物车不为空
	while (p != NULL) {
		//把购物车物品不断减一，直到为空
		printf("--------------------------------------------\n");
		printf("货号       品名           单价    数量\n");
		printf("%-11s%-15s%-10.2f%-7d\n", p->buy.ID, p->buy.brand, p->buy.outprice, p->number); //输出物品信息
		p = p->next;
	}
}


void addBuy() {
	//在购物车里添加商品
	FILE *fp;
	struct node *p1, *p;//p为新节点，p1为buyList节点
	int i, n;
	char name[20];
	char choice;
	if ((fp = fopen(storeTxt, "r")) == NULL) {
		printf("打开文件失败\n");
		return;
	}


	while (1) {
		printf("输入所需物品的名称或货号：\n");
		fflush(stdin);
		gets(name);
		for (i = 0; i < N; i++) {
			//循环N次
			fscanf(fp, "%s%s%*lf%lf%d", goods[i].ID, goods[i].brand, &goods[i].outprice, &goods[i].storage); //读

			if ((strcmp(goods[i].ID, name) == 0 || strcmp(goods[i].brand, name) == 0) && goods[i].storage > 0) { //if找到商品
				printf("已找到所需商品：\n");
				printf("--------------------------------------------\n");
				printf("货号       品名           单价    数量\n");
				printf("%-11s%-15s%-10.2f%-7d\n", goods[i].ID, goods[i].brand, goods[i].outprice, goods[i].storage);

				printf("请输入所需商品数量: ");
				scanf("%d", &n);
				if (n > goods[i].storage) {
					printf("该商品库存不足\n");
					break;
				}
				printf("\n输入y/Y以购买此商品\n");
				fflush(stdin);
				scanf("%s", choice);
				if (choice == 'y' || choice == 'Y') { //if购买
					p = (node *)malloc(sizeof(node));
					if (p == NULL) {
						printf("内存申请失败！\n");
						exit(1);
					}
					p->number = n; //商品数量
					p->buy = goods[i]; //货物信息
					p->next = NULL;
					goods[i].storage -= n;
					if (buyList == NULL) //头结点为空
						buyList = p; //把节点赋值给头结点
					else {
						p1 = buyList;
						while (p1->next != NULL) {
							p1 = p1->next;
						}
						p1->next = p; //把新节点p挂在链表尾部
					}
				} else {
					printf("取消购买\n");
				}
				break;//找到商品结束循环
			}
		}
		if (i >= N) {
			printf("未找到所需物品\n");
		}


		save();
		printf("输入y/Y以继续购买\n");
		fflush(stdin);//清空输入流
		scanf("%s", &choice); //输入选项
		if (choice != 'y' && choice != 'Y') {
			printf("已返回菜单\n");
			break;
		}
	}
	fclose(fp);
}

void calculate() {
	struct node *p = buyList;
	float sum = 0, pay;
	FILE *fp;
	printf("以下是购物清单：\n");
	showBuy();
	while (p != NULL) {
		sum = sum + p->buy.outprice * p->number;
		p = p->next;
	}

	printf("总计：%-10.2f\n", sum);
	printf("输入实付金额：");
	scanf("%f", &pay);
	printf("实付：  %-10.2f    找零:    %10.2f\n", pay, pay - sum);
}

