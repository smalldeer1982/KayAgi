# [PA 2016] 任务排序 /  Szeregowanie zadań

## 题目背景


译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R5 Szeregowanie zadań [B] (SZE)。

## 题目描述


有 $n$ 个任务，编号 $1\sim n$。任务 $i$ 有三个参数 $p_i,c_i,k_i$，含义为：
- 这个任务必须在时刻 $p_i$（或者 $p_i$ 之后）开始执行；
- 这个任务需要 $c_i$ 单位时间；（意思是，它需要在处理器上运行的总时间为 $c_i$）
- 这个任务必须在时刻 $k_i$（或者 $k_i$ 之前）完成。

有 $m$ 个处理器用来执行任务。

一个处理器同一时间只能处理一个任务，一个任务同一时间只能在一个处理器上被处理。每个任务可以在处理时被中断任意次，可以在任意时刻（不一定是整数时刻）被中断，在中断后可以分配给另一个处理器处理。

是否存在一种策略可以满足所有要求？

## 说明/提示


- $1\le n,m\le 100$；
- $0\le p_i\lt k_i\le 10^6$；
- $1\le c_i\le k_i-p_i$。

## 样例 #1

### 输入

```
3 2
3 8 3
2 5 2
3 7 3```

### 输出

```
TAK```

## 样例 #2

### 输入

```
2 1
0 1 1
0 1 1```

### 输出

```
NIE```

# 题解

## 作者：MornStar (赞：3)

## P11614 [PA 2016] 任务排序 /  Szeregowanie zadań 题解
简单网络流，场切了。

### solution

发现这道题严格弱于[P2570 [ZJOI2010] 贪吃的老鼠](https://www.luogu.com.cn/problem/P2570)，所以去掉那道题的二分即可 AC。

这里说一下更简单的建边方式：

首先将所有 $p_i$ 和 $k_i$ 离散化，将整个时间划分为 $O(n)$ 个区间，那么一个任务必然可以用若干个时间区间拼接出来。

然后设 $m$ 个处理器对应点 $1\sim m$，$n$ 个任务对应点 $m+1 \sim m+n$。

源点向每个处理器连 INF 边，第 $i$ 个任务向汇点连容量为 $c_i$ 的边。

然后考虑如何处理处理器与任务之间的边，我们可以对第 $i$ 个时间段建一个点 $n+m+i$，同时可以计算这个时间段经过的时间 $t_i$，每个处理器向这个点连一条容量为 $t_i$ 的边，代表处理器可以处理的时间，这个点对于每一个包含这个时间段的任务也连一条容量为 $t_i$ 的边，代表这个时间段最多被处理器处理多久。

可以发现，在题目的条件下，跑出的流一定可以对应一个分配处理器的合法方案，即满足题目中**一个处理器同一时间只能处理一个任务，一个任务同一时间只能在一个处理器上被处理**的限制。

于是跑完最大流后检查一下是否满流就可以了。

时间复杂度 $O(n^3(n+m))$，实际远远跑不满。

### code
代码中的变量定义与题目中略有不同。

```cpp
// by MornStar
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll N=405,M=100505,INF=0x3f3f3f3f3f3f3f3f;
//N: max of node num
//M: max of edge num
//T: the type of max_flow
//INF: max of max_flow
//eps: is used to check the val is 0 or not
template<int N,int M,typename T,const T INF=0x3f3f3f3f,const T eps=0>
struct Dinic{
	const int inf=0x3f3f3f3f;
	int vnum,s,t;
	struct edge{int to,pre;T w;}e[M<<1];
	int head[N],now[N],cnt=1;
	//use opt=1 to add undirected edge
	void add_edge(int u,int v,T w=INF,int opt=0){
		e[++cnt]={v,head[u],w};head[u]=cnt;
		e[++cnt]={u,head[v],w*opt};head[v]=cnt;
	}
	int dis[N];
	queue<int>q;
	void set_information(int num,int _s,int _t){vnum=num,s=_s,t=_t;}
	void set_dis(){for(int i=1;i<=vnum;i++)	dis[i]=inf;}
	void clear(){cnt=1,clear_head(),set_information(0,0,0);}
	void clear_head(){for(int i=1;i<N;i++)	head[i]=0;}
	void clear_q(){while(!q.empty())	q.pop();}
	bool bfs(){
		clear_q(),set_dis();
		dis[s]=0,now[s]=head[s];q.push(s);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int i=head[x];i;i=e[i].pre){
				edge &it=e[i];
				if(it.w>eps&&dis[it.to]==inf){
					dis[it.to]=dis[x]+1;
					q.push(it.to),now[it.to]=head[it.to];
					if(it.to==t)	return 1;
				}
			}
		}
		return 0;
	}
	T dinic(int x,T flow){
		if(x==t)	return flow;
		T ret=0;
		for(int i=now[x];i&&(flow>eps);i=e[i].pre){
			now[x]=i;
			edge &it=e[i],&rev=e[i^1];
			if(it.w>eps&&(dis[it.to]==dis[x]+1)){
				T k=dinic(it.to,min(flow,it.w));
				if(!k)	dis[it.to]=inf;
				it.w-=k,rev.w+=k,flow-=k,ret+=k;
			}
		}
		return ret;
	}
	T max_flow(){
		T ret=0;
		while(bfs())	ret+=dinic(s,INF);
		return ret;
	}
	T min_cut(){return max_flow();}
	//upper and lower bound flow
	bool check_full(){
		for(int i=head[s];i;i=e[i].pre){
			if(e[i].w>eps)	return 0;
		}
		return 1;
	}
	void debug(){
		for(int i=2;i<=cnt;i+=2)	cerr<<e[i^1].to<<' '<<e[i].to<<" "<<e[i].w<<"\n";
	}
};
Dinic<N,M,ll,INF>dc;
int n,m,l[N],r[N],t[N],b[N<<1],tb,num;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>l[i]>>r[i]>>t[i],num+=t[i],b[++tb]=l[i],b[++tb]=r[i];
	sort(b+1,b+tb+1);
	tb=unique(b+1,b+tb+1)-b-1;
	dc.set_information(N-1,N-2,N-1);
	for(int i=1;i<=m;i++)	dc.add_edge(dc.s,i,INF);
	for(int i=1;i<=n;i++)	dc.add_edge(m+i,dc.t,t[i]);
	for(int i=1;i<tb;i++){
		for(int j=1;j<=m;j++)	dc.add_edge(j,n+m+i,b[i+1]-b[i]);
		for(int j=1;j<=n;j++){
			if(l[j]<=b[i]&&b[i+1]<=r[j])	dc.add_edge(n+m+i,m+j,b[i+1]-b[i]);
		}
	}
//	dc.debug();
	int ans=dc.max_flow();
	if(ans==num)	cout<<"TAK\n";
	else	cout<<"NIE\n";
}
```

---

