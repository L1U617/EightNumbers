#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "ASTAR.h"
#include "math.h"
#include <string>

/*----------A*算法----------*/
int ASTAR::h(int a[][3], int b[][3])
{
	/*每个放错的数字移动到目标位置所需步数之和*/
	int count=0;
	int i, j;
	int m, n;
	int flag=0;
	for(i=0;i<3;i++)
		for (j = 0; j < 3; j++){
			if (a[i][j] != b[i][j])
			{
				for (m = 0; m < 3; m++) {
					for (n = 0; n < 3; n++) {
						if (a[i][j] == b[m][n]) {
							count += abs(m - i);
							count += abs(n - j);
							flag = 1;
							break;
						}						
					}
					if (flag == 1)  break;
				}
					
			}
		}
	return count;
}

void ASTAR::Extend(int a[][3], int t1[][3], int t2[][3], int t3[][3], int t4[][3])
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

bool ASTAR::ifClosed(int a[][3], node *cls)
{
	node *p;
	p = cls->next;
	while (p != NULL) {
		if (!memcmp(p->info, a, 36)) {
			return true;
		}
		else p = p->next;
	}
	return false;
}

bool ASTAR::ifOpen(node *a, node *opn,int num)
{
	node *p;
	p = opn->next;
	while (p != NULL){
		if (!memcmp(p->info, a->info, 36)) {
			if (p->g > a->g) {
				p->parent = a->parent;
				p->g = a->parent->g + 1;
				p->f = p->h + p->g;
				return true;
			}
			else return true;
		}
		else
			p=p->next;
	}
	return false;
}

ASTAR::node *ASTAR::findNode(node *opn)
{
	node *p, *min;
	p = opn->next;
	min = p;

	while (p != NULL)
	{
		if (p->f < min->f) min = p;
		p = p->next;
	}
	return min;
}

int ASTAR::Algorithm(int start[][3], int target[][3])
{
	int t1[3][3], t2[3][3], t3[3][3], t4[3][3];//存储4个扩展状态
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
	p->h = h(p->info, target);
	p->g = 0;
	p->f = p->g + p->h;

	p->parent = NULL;
	p->next = NULL;
	open = p;
	openlist->next = open;
	open->pre = openlist;

	close = q;
	closedlist = close;
	close->next = NULL;

	while (num < 10000) {
	
		if (openlist->next == NULL)
			return -1;
		else {
			p = findNode(openlist);

			q = (node *)malloc(sizeof(node));
			memcpy(q->info, p->info, 36);
			q->parent = p->parent;
			q->next = close->next;
			close->next = q;

			Extend(p->info, t1, t2, t3, t4);//扩展当前节点

			/*判断当前扩展节点是否在closed表中，若是就跳过，
			否则判断是否在open表中，若在则判断两者g值大小，取小者*/

			if (t1[0][0] != -1) {
				if (!ifClosed(t1, closedlist)) {
					r = (node *)malloc(sizeof(node));
					memcpy(r->info, t1, 36);
					r->h = h(t1, target);
					r->g = p->g + 1;
					r->f = r->g + r->h;
					r->parent = p;
					if (!ifOpen(r, openlist,num)) {
						open->next = r;
						r->pre = open;
						
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
			}
			if (t2[0][0] != -1) {
				if (!ifClosed(t2, closedlist)) {
					r = (node *)malloc(sizeof(node));
					memcpy(r->info, t2, 36);
					r->h = h(t2, target);
					r->g = p->g + 1;
					r->f = r->g + r->h;
					r->parent = p;
					if (!ifOpen(r, openlist,num)) {
						open->next = r;
						r->pre = open;
						
						open = r;
						open->next = NULL;
						num++;

						if (!(memcmp(target, t2, 36)))
						{
							temp = r;
							return num;
						}
					}
				}
			}
			if (t3[0][0] != -1) {
				if (!ifClosed(t3, closedlist)) {
					r = (node *)malloc(sizeof(node));
					memcpy(r->info, t3, 36);
					r->h = h(t3, target);
					r->g = p->g + 1;
					r->f = r->g + r->h;
					r->parent = p;
					if (!ifOpen(r, openlist,num)) {
						open->next = r;
						r->pre = open;
						
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
			}
			if (t4[0][0] != -1) {
				if (!ifClosed(t4, closedlist)) {
					r = (node *)malloc(sizeof(node));
					memcpy(r->info, t4, 36);
					r->h = h(t4, target);
					r->g = p->g + 1;
					r->f = r->g + r->h;
					r->parent = p;
					if (!ifOpen(r, openlist,num)) {
						open->next = r;
						r->pre = open;
						
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
				p->next->pre = p->pre;
			p->pre->next = p->next;

		}
	}
	
	return -1;

}


ASTAR::node *ASTAR::showResult()
{
	/*获取解决路径*/
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