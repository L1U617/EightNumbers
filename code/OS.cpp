#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "OS.h"
#include <string>

/*-------有序搜索-------*/

int OS::f(int a[][3],int b[][3])//估计函数，放错的数字个数
{
	int num=0;//计数
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (a[i][j] != b[i][j]) num++;
	return num;
}

bool OS::Compare(int a[][3], node *open, node *close)
{
	node *p, *q;
	p = open->next;
	q = close->next;
	while (p != NULL)
	{
		if (!(memcmp(p->info, a, 36))) return false;
		else p = p->next;
	}
	while (q != NULL)
	{
		if (!(memcmp(q->info, a, 36))) return false;
		else q = q->next;
	}
	return true;
}

void OS::Extend(int a[][3], int t1[][3], int t2[][3], int t3[][3], int t4[][3])
{
	int i, j, k;
	int temp[4];
	int flag = 0;
	for (k = 0; k < 4; k++)
		temp[k] = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (a[i][j] == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}

	if (i + 1 < 3)
		temp[0] = 1;
	if (i - 1 >= 0)
		temp[1] = 1;
	if (j + 1 < 3)
		temp[2] = 1;
	if (j - 1 >= 0)
		temp[3] = 1;

	for (k = 0; k < 4; k++)
	{
		switch (k)
		{
		case 0:
			if (temp[0] == 1) {
				memcpy(t1, a, 36);
				t1[i][j] = a[i + 1][j];
				t1[i + 1][j] = a[i][j];
			}
			break;
		case 1:
			if (temp[1] == 1) {
				memcpy(t2, a, 36);
				t2[i][j] = a[i - 1][j];
				t2[i - 1][j] = a[i][j];
			}
			break;
		case 2:
			if (temp[2] == 1)
			{
				memcpy(t3, a, 36);
				t3[i][j] = a[i][j + 1];
				t3[i][j + 1] = a[i][j];
			}
			break;
		case 3:
			if (temp[3] == 1)
			{
				memcpy(t4, a, 36);
				t4[i][j] = a[i][j - 1];
				t4[i][j - 1] = a[i][j];
			}
			break;
		}
	}
}

OS::node * OS::findNode(node *opn)
{
	node *p,*min;
	p = opn->next;
	min = p;

	while (p != NULL)
	{
		if (p->promise < min->promise) min = p;
		p = p->next;
	}

	return min;
}

int OS::Algorithm(int start[][3], int target[][3])
{
	int t1[3][3], t2[3][3], t3[3][3], t4[3][3];//存储可能扩展的4个状态
	node *openlist, *p, *r, *open;
	node *closedlist, *q, *close;
	int num = 1;
	for (int i = 0; i<3; i++)
		for (int j = 0; j < 3; j++)
		{
			t1[i][j] = -1;
			t2[i][j] = -1;
			t3[i][j] = -1;
			t4[i][j] = -1;
		}

	/*建立open表和closed表*/
	p = (node *)malloc(sizeof(node));
	q = (node *)malloc(sizeof(node));
	openlist = (node *)malloc(sizeof(node));
	close = (node *)malloc(sizeof(node));
	memcpy(p->info, start, 36);
	p->promise = f(p->info, target);

	p->parent = NULL;
	p->next = NULL;
	open = p;
	openlist->next = open;
	open->pre = openlist;

	close = q;
	closedlist = close;
	close->next = NULL;

	while (num<10000) {
		if (openlist->next == NULL)
			return -1;
		else {
			p = findNode(openlist);

			q = (node *)malloc(sizeof(node));
			memcpy(q->info, p->info, 36);
			q->parent = p->parent;
			q->next = close->next;
			close->next = q;

			Extend(p->info, t1, t2, t3, t4);

			/*判断当前扩展节点是否在closed表和open表中，若是就跳过，
			否则将该节点加入open表*/
			if (t1[0][0] != -1)
			{
				if (Compare(t1, openlist, closedlist)) {
					r = (node *)malloc(sizeof(node));
					memcpy(r->info, t1, 36);
					r->promise = f(t1,target);
					open->next = r;
					r->pre = open;
					r->parent = p;
					open = r;
					open->next = NULL;
					num++;
					if (!(memcmp(target, t1, 36)))
					{
						temp = r;
						return num;
					}
				}

			}
			if (t2[0][0] != -1)
			{
				if (Compare(t2, openlist, closedlist)) {
					r = (node *)malloc(sizeof(node));
					memcpy(r->info, t2, 36);
					r->promise = f(t2, target);
					open->next = r;
					r->pre = open;
					r->parent = p;
					open = r;
					open->next = NULL;
					num++;
					if (!(memcmp(target, t2, 36)))
					{
						temp = r;
						return true;
					}
				}

			}
			if (t3[0][0] != -1)
			{
				if (Compare(t3, openlist, closedlist)) {
					r = (node *)malloc(sizeof(node));
					memcpy(r->info, t3, 36);
					r->promise = f(t3, target);
					open->next = r;
					r->pre = open;
					r->parent = p;
					open = r;
					open->next = NULL;
					num++;
					if (!(memcmp(target, t3, 36)))
					{
						temp = r;
						return num;
					}
				}
			}
			if (t4[0][0] != -1)
			{
				if (Compare(t4, openlist, closedlist)) {
					r = (node *)malloc(sizeof(node));
					memcpy(r->info, t4, 36);
					r->promise = f(t4, target);
					open->next = r;
					r->pre = open;
					r->parent = p;
					open = r;
					open->next = NULL;
					num++;
					if (!(memcmp(target, t4, 36)))
					{
						temp = r;
						return num;
					}
				}
			}
			for (int i = 0; i<3; i++)
				for (int j = 0; j < 3; j++)
				{
					t1[i][j] = -1;
					t2[i][j] = -1;
					t3[i][j] = -1;
					t4[i][j] = -1;
				}
			if (p->next != NULL) 
				p->next->pre=p->pre;
			p->pre->next = p->next;
		}

	}
	return -1;
}

OS::node *OS::showResult()
{
	node *display, *p, *r;
	p = (node *)malloc(sizeof(node));
	display = (node *)malloc(sizeof(node));
	display = p;
	p->next = NULL;
	while (temp != NULL)
	{
		r = (node *)malloc(sizeof(node));
		r = temp;
		r->next = p->next;
		p->next = r;
		temp = temp->parent;
	}
	return display->next;
}