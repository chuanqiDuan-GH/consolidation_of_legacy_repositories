//矩阵乘法必须要符合a[m][n] b[n][p]这种形式
//最终得出的矩阵为c[m][p],m可以和p相同，也可以不同，但是n是同一个
//矩阵乘法：先以a的一行为开始对应乘以b的第一列，一共有n个乘积，相加后为c的第一个元素
#include<stdio.h>
#define MAIN
#define M 2
#define N 3
#define P 4

//void multiplication(int matrix1[M][N], int matrix2[N][P]);

int main()
{
    int a[2][3] = {{1, 2, 3}, {1, 2, 3}};
    int b[3][4] = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};
    int *c[2];
    int *d[3];
#ifdef MAIN 
//normal operation
    int i, j, k;   
    int temp = 0;
    int matrix[2][4];

    for(i=0; i<2; i++)
    {
	for(j=0; j<4; j++)
	{
	    for(k=0; k<3; k++)
	    {
		temp += a[i][k] * b[k][j];
	    }
	   matrix[i][j] = temp;
	   printf("%d\t", temp);
	}
	printf("\n");
    }
#endif

    //multiplication(c, d);
    return 0;
}

#if 0
//矩阵乘法的单独函数传参未调试好,以下程序error
void multiplication(int matrix1[M][N], int matrix2[N][P])
{
    int i, j, k;   
    int temp;
    int matrix[M][P];
    for(i=0; i<M; i++)
    {
	for(j=0; j<P; j++)
	{
	    for(k=0; k<N; k++)
	    {
		temp += matrix1[M][N] * matrix2[N][P];
	    }
	   matrix[M][P] = temp;
	   printf("%d\t", temp);
	}
	printf("\n");
    }
}
#endif
