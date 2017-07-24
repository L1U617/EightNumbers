#pragma once
#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

class ASTAR
{
public:
	typedef struct NODE {
		int info[3][3];//�ڵ���Ϣ
		NODE *parent;//���ڵ�
		NODE *next;
		NODE *pre;
		int f,g,h;//f=g+h�����ڽڵ���gֵ��Ϊ+1
	}node;
	node *temp;

public:
	int Algorithm(int start[][3], int target[][3]);//�㷨
	void Extend(int a[][3], int t1[][3], int t2[][3], int t3[][3], int t4[][3]);//��չ����
	int h(int a[][3], int b[][3]);//���㵱ǰ״̬��Ŀ��״̬�ľ���
	bool ifClosed(int a[][3], node *cls);//�жϵ�ǰ�ڵ��Ƿ���Closed����
	bool ifOpen(node *a, node *opn,int num);//�жϵ�ǰ�ڵ��Ƿ���Open����
	node *findNode(node *opn);//��open�����ҵ�fֵ���ŵĽڵ�
	node *showResult();//���չʾ
};