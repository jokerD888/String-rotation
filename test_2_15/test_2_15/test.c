#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>

//1.字符串旋转

//内容较为冗杂，[]内容较多，逻辑较为复杂
void left_move1(char arr[10], int n)//此处10，为任意大于字符长度的数
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

//逻辑较为清晰，易于理解
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

//最优解，三步翻转法,若字符串较长，此法效率较高
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
	assert(k <= len);//防止选择字数大于总字符串字数
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


//2.判断旋转字符串

//穷举，效率低下
int is_left_move1(char* s1, char* s2)
{
	int len = strlen(s1);
	int i;
	for (i = 0; i < len; i++)
	{
		left_move(s1, 1);//此函数会改变原数组内容，加1即可检验所有选择可能
		int ret = strcmp(s1, s2);
		if (ret == 0)
			return 1;
	}
	return 0;
}

//效率较高，但局限于无重复元素字符串
//如"abcdde"和"deabcd"则不能正确判断
int is_left_move2(char* s1, char* s2)
{
	int n = 0;
	char* ss = s1;
	while (*ss != *s2)//找第s1中第几项跟s2首元素相同
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
	//可以直接在s1后追加本身，也可新创数组，但自身追加不可用strcat函数，会无限套娃，程序奔溃。若要自身追加，可用strncat
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
	//1.追加自身
	strncat(s1, s1, len1);
	//2.判断s2是否是s1的字串
	//可用strstr函数，若找到返回字串首元素地址，若找不到，返回空指针
	char* ret = strstr(s1, s2);
	if (ret == NULL)
		return 0;
	else
		return 1;
}

int main(void)
{
	char arr1[30] = "abcdef";//若用法4，arr1的空间最少得是原字符串的2倍
	char arr2[] = "cdefab";
	int ret = is_left_move4(arr1, arr2);
	if (ret == 1)
		printf("Yes!\n");
	else
		printf("No!\n");
	return 0;
}