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
	printf("             ��ӭ���빺�ﳵ��������������Ϣ����ϵͳ\n");
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
				printf("��л����ʹ�ã��ټ���\n");
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
	printf("���������������Ϣ��\n");
	printf("--------------------------------------------\n");
	while (N < 20) {
		//���ļ���д����Ϣ
		printf("������ӵ���Ʒ��Ϣ��\n");
		printf("���ţ�");
		fflush(stdin);
		gets(goods[N].ID);

		printf("Ʒ����");
		fflush(stdin);
		gets(goods[N].brand);

		printf("����: ");
		fflush(stdin);
		scanf("%lf", &goods[N].inprice);

		printf("�ۼۣ�");
		fflush(stdin);
		scanf("%lf", &goods[N].outprice);

		printf("������");
		fflush(stdin);
		scanf("%d", &goods[N].storage);
		printf("\n");
		N += 1;

		printf("����y/Y�Լ������\n");
		fflush(stdin);
		scanf("%s", &choice);
		if (choice != 'y' && choice != 'Y') {
			printf("�ѷ��ز˵�\n");
			break;
		}
	}
	save();
}

void save() {
	FILE *fp;
	for (int i = 0; i < N; i++) {
		if ((fp = fopen(storeTxt, "w")) == NULL) {
			printf("Error:�����ļ�ʧ�ܡ�\n");
			return ;
		}
		fprintf(fp, "%-11s%-15s%-10.2f%-10.2f%-7d\n", goods[i].ID, goods[i].brand, goods[i].inprice, goods[i].outprice,
		        goods[i].storage);
	}
	fclose(fp);
	printf("��Ϣ����ɹ�\n");
}


void showStore() {
	//��ʾ�����Ϣ����
	FILE *fp;//�����ļ�ָ��
	if ((fp = fopen(storeTxt, "r")) == NULL) {
		//�ж��Ƿ�����ļ�
		printf("Error:���ļ�ʧ��\n");
		return ;
	}

	for (int i = 0; i < N; i++) {
		//�����Ʒ��Ϣ
		//��ȡ�ļ���Ϣ
		fscanf(fp, "%s%s%lf%lf%d", goods[i].ID, goods[i].brand, &goods[i].inprice, &goods[i].outprice, &goods[i].storage);
		printf("--------------------------------------------\n");
		//����ļ���Ϣ
		printf("����       Ʒ��           ����    �����\n");
		printf("%-11s%-15s%-10.2f%-7d\n", goods[i].ID, goods[i].brand, goods[i].outprice, goods[i].storage);
	}
	fclose(fp);//�ر��ļ�
}

void showBuy() {
	struct node *p = buyList;
	if (p == NULL) {
		//���ﳵΪ��
		printf("Ŀǰ���ﳵΪ�գ�");
		return ;
	}
	//���ﳵ��Ϊ��
	while (p != NULL) {
		//�ѹ��ﳵ��Ʒ���ϼ�һ��ֱ��Ϊ��
		printf("--------------------------------------------\n");
		printf("����       Ʒ��           ����    ����\n");
		printf("%-11s%-15s%-10.2f%-7d\n", p->buy.ID, p->buy.brand, p->buy.outprice, p->number); //�����Ʒ��Ϣ
		p = p->next;
	}
}


void addBuy() {
	//�ڹ��ﳵ�������Ʒ
	FILE *fp;
	struct node *p1, *p;//pΪ�½ڵ㣬p1ΪbuyList�ڵ�
	int i, n;
	char name[20];
	char choice;
	if ((fp = fopen(storeTxt, "r")) == NULL) {
		printf("���ļ�ʧ��\n");
		return;
	}


	while (1) {
		printf("����������Ʒ�����ƻ���ţ�\n");
		fflush(stdin);
		gets(name);
		for (i = 0; i < N; i++) {
			//ѭ��N��
			fscanf(fp, "%s%s%*lf%lf%d", goods[i].ID, goods[i].brand, &goods[i].outprice, &goods[i].storage); //��

			if ((strcmp(goods[i].ID, name) == 0 || strcmp(goods[i].brand, name) == 0) && goods[i].storage > 0) { //if�ҵ���Ʒ
				printf("���ҵ�������Ʒ��\n");
				printf("--------------------------------------------\n");
				printf("����       Ʒ��           ����    ����\n");
				printf("%-11s%-15s%-10.2f%-7d\n", goods[i].ID, goods[i].brand, goods[i].outprice, goods[i].storage);

				printf("������������Ʒ����: ");
				scanf("%d", &n);
				if (n > goods[i].storage) {
					printf("����Ʒ��治��\n");
					break;
				}
				printf("\n����y/Y�Թ������Ʒ\n");
				fflush(stdin);
				scanf("%s", choice);
				if (choice == 'y' || choice == 'Y') { //if����
					p = (node *)malloc(sizeof(node));
					if (p == NULL) {
						printf("�ڴ�����ʧ�ܣ�\n");
						exit(1);
					}
					p->number = n; //��Ʒ����
					p->buy = goods[i]; //������Ϣ
					p->next = NULL;
					goods[i].storage -= n;
					if (buyList == NULL) //ͷ���Ϊ��
						buyList = p; //�ѽڵ㸳ֵ��ͷ���
					else {
						p1 = buyList;
						while (p1->next != NULL) {
							p1 = p1->next;
						}
						p1->next = p; //���½ڵ�p��������β��
					}
				} else {
					printf("ȡ������\n");
				}
				break;//�ҵ���Ʒ����ѭ��
			}
		}
		if (i >= N) {
			printf("δ�ҵ�������Ʒ\n");
		}


		save();
		printf("����y/Y�Լ�������\n");
		fflush(stdin);//���������
		scanf("%s", &choice); //����ѡ��
		if (choice != 'y' && choice != 'Y') {
			printf("�ѷ��ز˵�\n");
			break;
		}
	}
	fclose(fp);
}

void calculate() {
	struct node *p = buyList;
	float sum = 0, pay;
	FILE *fp;
	printf("�����ǹ����嵥��\n");
	showBuy();
	while (p != NULL) {
		sum = sum + p->buy.outprice * p->number;
		p = p->next;
	}

	printf("�ܼƣ�%-10.2f\n", sum);
	printf("����ʵ����");
	scanf("%f", &pay);
	printf("ʵ����  %-10.2f    ����:    %10.2f\n", pay, pay - sum);
}

