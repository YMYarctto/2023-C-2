#ifndef INC_2023_C_2_MAIN_H
#define INC_2023_C_2_MAIN_H

void mainStore();//��ӡ���˵�����
int mainStoreMenu();
void mainBuy();//�Թ��ﳵ���в���
int mainBuyMenu();
void addStore();//�ļ����������Ϣ
void showStore();//��ʾ�����Ϣ����
void addBuy();//�ڹ��ﳵ�������Ʒ
void showBuy();//��ʾ�����б�
void calculate();//����������Ʒ�۸��޸ı���
void save();//�������ݵ��ļ�

typedef struct node node;
struct Goods {
	char ID[10];//����
	char brand[20];//��Ʒ��
	float inprice;//����
	float outprice;//�ۼ�
	int storage;//�洢��
};

struct node {
	struct Goods buy;
	int number;
	struct node *next;
};

#endif