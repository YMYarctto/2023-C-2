#ifndef INC_2023_C_2_MAIN_H
#define INC_2023_C_2_MAIN_H

void mainStore();//打印主菜单函数
int mainStoreMenu();
void mainBuy();//对购物车进行操作
int mainBuyMenu();
void addStore();//文件建立库存信息
void showStore();//显示库存信息函数
void addBuy();//在购物车里添加商品
void showBuy();//显示购物列表
void calculate();//计算所购商品价格并修改保存
void save();//保存数据到文件

typedef struct node node;
struct Goods {
	char ID[10];//货号
	char brand[20];//商品名
	float inprice;//进价
	float outprice;//售价
	int storage;//存储量
};

struct node {
	struct Goods buy;
	int number;
	struct node *next;
};

#endif