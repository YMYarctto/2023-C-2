#include <stdio.h>
#include <stdlib.h>

int scanNum(int num) {
	char s[5];
	int n;
	while (1) {
		while (getchar() != '\n');
		gets(s);//输入一串字符串
		n = atoi(s); //字符串转化为整数

		if (n < 1 || n > num)
			printf("输入错误，请重新输入：\n");
		else
			break;
	}
	return n;
}

int mainStoreMenu() {
	//打印主菜单函数
	printf("\n\n请选择下面的数字进行操作：\n");
	printf("--------------------------------------------\n");
	printf("1. 添加库存\n");
	printf("2. 查看库存\n");
	printf("3. 购买\n");
	printf("4. 关于\n");
	printf("5. 退出\n");
	printf("--------------------------------------------\n");
	printf(">>>");


	return scanNum(5);
}

int mainBuyMenu() {
	//打印购物车菜单
	printf("\n\n请选择操作：\n");
	printf("--------------------------------------------\n");
	printf("1. 显示当前可以购物列表\n");
	printf("2. 在购物车里添加商品\n");
	printf("3. 结算\n");
	printf("4. 返回\n");
	printf("--------------------------------------------\n");
	printf(">>>");

	return scanNum(4);
}

