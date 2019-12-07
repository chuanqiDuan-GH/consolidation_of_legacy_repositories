/*******************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:5-mergeSort.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-01-02 22:16
 *   Describe:
 ********************************************************/
#include <stdio.h>
#include <stdlib.h>   

typedef int RecType;//要排序元素类型  

void Merge(RecType *R, int low, int m, int high)  
{  
    //将两个有序的子文件R[low..m)和R[m+1..high]归并成一个有序的子文件R[low..high]  
    int i = low;
    int j = m+1;
    int p = 0;                //置初始值  
    RecType *R1;                        //R1是局部向量  
    R1 = (RecType *)malloc((high-low+1)*sizeof(RecType));  

    if(!R1)  
	return;                         //申请空间失败  

    while(i<=m && j<=high)                //两子文件非空时取其小者输出到R1[p]上  
	R1[p++] = (R[i]<=R[j]) ? R[i++] : R[j++];  

    while(i <= m)                         //若第1个子文件非空，则复制剩余记录到R1中  
	R1[p++] = R[i++];  

    while(j <= high)                      //若第2个子文件非空，则复制剩余记录到R1中  
	R1[p++] = R[j++];  

    for(p=0,i=low; i<=high; p++,i++)  
	R[i] = R1[p];                     //归并完成后将结果复制回R[low..high]  
}  

void MergeSort(RecType R[], int low, int high)  
{     
    //用分治法对R[low..high]进行二路归并排序  
    int mid;  
    if(low < high)  
    {   //区间长度大于1   
	mid = (low+high) / 2;               //分解  
	MergeSort(R, low, mid);           //递归地对R[low..mid]排序  
	MergeSort(R, mid+1, high);        //递归地对R[mid+1..high]排序  
	Merge(R, low, mid, high);          //组合，将两个有序区归并为一个有序区  
    }  
}  

void main()  
{  
    int a[] = {9, 10, 20, 0, 3};
    int low = 0;
    int high = 4;                   //初始化low和high的值  
    int i;

    printf("Before merge sort: ");  
    for(i=low; i<=high; i++)  
    {  
	printf("%d ", a[i]);             //输出测试  
    }  
    printf("\n");  

    MergeSort(a, low, high);  

    printf("After merge sort: ");  
    for(i=low; i<=high; i++)  
    {  
	printf("%d ", a[i]);             //输出测试  
    }  
    printf("\n");  
}
