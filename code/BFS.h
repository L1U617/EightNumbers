#pragma once
#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
class BFS
{
public:
	typedef struct NODE {
		int info[3][3];//节点信息
		NODE *parent;//父节点
		NODE *next;
	}node;

	node *temp;

public:
	void Extend(int a[][3],int t1[][3],int t2[][3],int t3[][3],int t4[][3]);//扩展函数
	bool Compare(int a[][3], node *open, node *close);//判断当前节点是否已经在open表和closed表中
	int Algorithm(int start[][3], int target[][3]);//算法
	node *showResult();//计算路径
};