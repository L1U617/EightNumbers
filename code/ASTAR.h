#pragma once
#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

class ASTAR
{
public:
	typedef struct NODE {
		int info[3][3];//节点信息
		NODE *parent;//父节点
		NODE *next;
		NODE *pre;
		int f,g,h;//f=g+h，相邻节点间的g值均为+1
	}node;
	node *temp;

public:
	int Algorithm(int start[][3], int target[][3]);//算法
	void Extend(int a[][3], int t1[][3], int t2[][3], int t3[][3], int t4[][3]);//扩展函数
	int h(int a[][3], int b[][3]);//计算当前状态到目标状态的距离
	bool ifClosed(int a[][3], node *cls);//判断当前节点是否在Closed表中
	bool ifOpen(node *a, node *opn,int num);//判断当前节点是否在Open表中
	node *findNode(node *opn);//在open表中找到f值最优的节点
	node *showResult();//结果展示
};