#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100010;//点数的最大值
const int MAXM = 400010;//边数的最大值
const int oo = 0x3f3f3f3f;
struct Edge
{
	int to,next,cap,flow;
}edge[MAXM];//注意是MAXM
int tol;
int head[MAXN];
int gap[MAXN],dep[MAXN],cur[MAXN];
void init()
{
	tol = 0;
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w,int rw = 0)
{
	edge[tol].to = v; edge[tol].cap = w; edge[tol].flow = 0;
	edge[tol].next = head[u]; head[u] = tol++;
	edge[tol].to = u; edge[tol].cap = rw; edge[tol].flow = 0;
	edge[tol].next = head[v]; head[v] = tol++;
}
int Q[MAXN];
void BFS(int ss,int tt)
{
	memset(dep,-1,sizeof(dep));
	memset(gap,0,sizeof(gap));
	gap[0] = 1;
	int front = 0, rear = 0;
	dep[tt] = 0;
	Q[rear++] = tt;
	while(front != rear)
	{
		int u = Q[front++];
		for(int i = head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].to;
			if(dep[v] != -1)continue;
			Q[rear++] = v;
			dep[v] = dep[u] + 1;
			gap[dep[v]]++;
		}
	}
}
int S[MAXN];
int sap(int ss,int tt,int N)
{
	BFS(ss,tt);
	memcpy(cur,head,sizeof(head));
	int top = 0;
	int u = ss;
	int ans = 0;
	while(dep[ss] < N)
	{
		if(u == tt)
		{
			int mi = oo;
			int inser;
			for(int i = 0;i < top;i++)
				if(mi > edge[S[i]].cap - edge[S[i]].flow)
				{
					mi = edge[S[i]].cap - edge[S[i]].flow;
					inser = i;
				}
			for(int i = 0;i < top;i++)
			{
				edge[S[i]].flow += mi;
				edge[S[i]^1].flow -= mi;
			}
			ans += mi;
			top = inser;
			u = edge[S[top]^1].to;
			continue;
		}
		bool flag = false;
		int v;
		for(int i = cur[u]; i != -1; i = edge[i].next)
		{
			v = edge[i].to;
			if(edge[i].cap - edge[i].flow && dep[v]+1 == dep[u])
			{
				flag = true;
				cur[u] = i;
				break;
			}
		}
		if(flag)
		{
			S[top++] = cur[u];
			u = v;
			continue;
		}
		int mi = N;
		for(int i = head[u]; i != -1; i = edge[i].next)
			if(edge[i].cap - edge[i].flow && dep[edge[i].to] < mi)
			{
				mi = dep[edge[i].to];
				cur[u] = i;
			}
		gap[dep[u]]--;
		if(!gap[dep[u]])return ans;
		dep[u] = mi + 1;
		gap[dep[u]]++;
		if(u != ss)u = edge[S[--top]^1].to;
	}
	return ans;
}
