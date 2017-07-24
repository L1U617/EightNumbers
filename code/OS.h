#pragma once
#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
class OS
{
public:
	typedef struct NODE {
		int info[3][3];//节点信息
		NODE *parent;//父节点
		NODE *pre;
		NODE *next;
		int promise;//估计值
	}node;

	node *temp;//存储目标节点，以获取目标路径

public:
	void Extend(int a[][3], int t1[][3], int t2[][3], int t3[][3], int t4[][3]);//扩展函数
	bool Compare(int a[][3], node *open, node *close);//判断当前节点是否在open表或closed表中
	int Algorithm(int start[][3], int target[][3]);//算法
	int f(int a[][3],int b[][3]);//估计函数
	node *findNode(node *opn);//找到open表中估计值最小的节点
	node *showResult();
}; 

