#include <stdio.h>
#include <stdlib.h>

int scanNum(int num) {
	char s[5];
	int n;
	while (1) {
		while (getchar() != '\n');
		gets(s);//����һ���ַ���
		n = atoi(s); //�ַ���ת��Ϊ����

		if (n < 1 || n > num)
			printf("����������������룺\n");
		else
			break;
	}
	return n;
}

int mainStoreMenu() {
	//��ӡ���˵�����
	printf("\n\n��ѡ����������ֽ��в�����\n");
	printf("--------------------------------------------\n");
	printf("1. ��ӿ��\n");
	printf("2. �鿴���\n");
	printf("3. ����\n");
	printf("4. ����\n");
	printf("5. �˳�\n");
	printf("--------------------------------------------\n");
	printf(">>>");


	return scanNum(5);
}

int mainBuyMenu() {
	//��ӡ���ﳵ�˵�
	printf("\n\n��ѡ�������\n");
	printf("--------------------------------------------\n");
	printf("1. ��ʾ��ǰ���Թ����б�\n");
	printf("2. �ڹ��ﳵ�������Ʒ\n");
	printf("3. ����\n");
	printf("4. ����\n");
	printf("--------------------------------------------\n");
	printf(">>>");

	return scanNum(4);
}

