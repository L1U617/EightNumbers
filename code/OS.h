#pragma once
#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
class OS
{
public:
	typedef struct NODE {
		int info[3][3];//�ڵ���Ϣ
		NODE *parent;//���ڵ�
		NODE *pre;
		NODE *next;
		int promise;//����ֵ
	}node;

	node *temp;//�洢Ŀ��ڵ㣬�Ի�ȡĿ��·��

public:
	void Extend(int a[][3], int t1[][3], int t2[][3], int t3[][3], int t4[][3]);//��չ����
	bool Compare(int a[][3], node *open, node *close);//�жϵ�ǰ�ڵ��Ƿ���open���closed����
	int Algorithm(int start[][3], int target[][3]);//�㷨
	int f(int a[][3],int b[][3]);//���ƺ���
	node *findNode(node *opn);//�ҵ�open���й���ֵ��С�Ľڵ�
	node *showResult();
}; 

