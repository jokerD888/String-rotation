#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>

//1.�ַ�����ת

//���ݽ�Ϊ���ӣ�[]���ݽ϶࣬�߼���Ϊ����
void left_move1(char arr[10], int n)//�˴�10��Ϊ��������ַ����ȵ���
{
	int i,j;
	int sz = strlen(arr);
	for (i = 0; i < n; i++)
	{
		char temp = arr[i];
		arr[i] = arr[sz-n+i];
		arr[sz-n+i] = temp;
	}
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < sz - 2 * n; i++)
		{
			char temp = arr[n - j + i-1];
			arr[n - j + i-1] = arr[n-j+i];
			arr[n-j+i] = temp;
		}
	}
}

//�߼���Ϊ�������������
void left_move2(char *arr, int k)
{
	assert(arr);
	int len = strlen(arr);
	int i,j;
	for (i = 0; i < k; i++)
	{
		char temp = *arr;

		for (j = 0; j < len - 1 ; j++)
		{
			*(arr + j) = *(arr + j + 1);
		}
		*(arr + len - 1) = temp;
	}
}

//���Ž⣬������ת��,���ַ����ϳ����˷�Ч�ʽϸ�
void reverse(char* left, char* right)
{
	assert(left);
	assert(right);
	while (left < right)
	{
		char temp = *left;
		*left = *right;
		*right = temp;
		left++;
		right--;
	}
}
void left_move(char* arr, int k)
{
	assert(arr);
	int len = strlen(arr);
	assert(k <= len);//��ֹѡ�������������ַ�������
	reverse(arr, arr + k - 1);
	reverse(arr + k, arr + len - 1);
	reverse(arr, arr + len - 1);
}

//int main(void)
//{
//	char arr[] = "abcdef";
//
//	left_move(arr, 2);
//	printf( "%s\n",arr );
//	return 0;
//}


//2.�ж���ת�ַ���

//��٣�Ч�ʵ���
int is_left_move1(char* s1, char* s2)
{
	int len = strlen(s1);
	int i;
	for (i = 0; i < len; i++)
	{
		left_move(s1, 1);//�˺�����ı�ԭ�������ݣ���1���ɼ�������ѡ�����
		int ret = strcmp(s1, s2);
		if (ret == 0)
			return 1;
	}
	return 0;
}

//Ч�ʽϸߣ������������ظ�Ԫ���ַ���
//��"abcdde"��"deabcd"������ȷ�ж�
int is_left_move2(char* s1, char* s2)
{
	int n = 0;
	char* ss = s1;
	while (*ss != *s2)//�ҵ�s1�еڼ����s2��Ԫ����ͬ
	{
		n++;
		ss++;
	}
	left_move(s1, n);
	int num = strcmp(s1, s2);
	if (num == 0)
		return 1;
	return 0;

}

int is_left_move3(char* s1, char* s2)
{
	char arr[20] = {0};
	//����ֱ����s1��׷�ӱ���Ҳ���´����飬������׷�Ӳ�����strcat���������������ޣ�����������Ҫ����׷�ӣ�����strncat
	strcpy(arr, s1);
	strcat(arr, s1);
	int len = strlen(s1);
	int i = 0;
	for (i = 0; i <len; i++)
	{
		int j;
		for (j = 0; j < len; j++)
		{
			int ret=strncmp(arr + i, s2, len);
			if (ret == 0)
				return 1;
		}
	}
	return 0;

}

int is_left_move4(char* s1, char* s2)
{
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	//1.׷������
	strncat(s1, s1, len1);
	//2.�ж�s2�Ƿ���s1���ִ�
	//����strstr���������ҵ������ִ���Ԫ�ص�ַ�����Ҳ��������ؿ�ָ��
	char* ret = strstr(s1, s2);
	if (ret == NULL)
		return 0;
	else
		return 1;
}

int main(void)
{
	char arr1[30] = "abcdef";//���÷�4��arr1�Ŀռ����ٵ���ԭ�ַ�����2��
	char arr2[] = "cdefab";
	int ret = is_left_move4(arr1, arr2);
	if (ret == 1)
		printf("Yes!\n");
	else
		printf("No!\n");
	return 0;
}