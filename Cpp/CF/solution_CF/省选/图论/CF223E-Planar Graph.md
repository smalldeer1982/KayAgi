# Planar Graph

## 题目描述

A graph is called planar, if it can be drawn in such a way that its edges intersect only at their vertexes.

An articulation point is such a vertex of an undirected graph, that when removed increases the number of connected components of the graph.

A bridge is such an edge of an undirected graph, that when removed increases the number of connected components of the graph.

You've got a connected undirected planar graph consisting of $ n $ vertexes, numbered from $ 1 $ to $ n $ , drawn on the plane. The graph has no bridges, articulation points, loops and multiple edges. You are also given $ q $ queries. Each query is a cycle in the graph. The query response is the number of graph vertexes, which (if you draw a graph and the cycle on the plane) are located either inside the cycle, or on it. Write a program that, given the graph and the queries, will answer each query.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
0 0
1 0
0 1
1
3 1 2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 8
1 2
2 3
3 4
4 1
1 5
2 5
3 5
4 5
0 0
2 0
2 2
0 2
1 1
1
4 1 2 3 4
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4 5
1 2
2 3
3 4
4 1
2 4
0 0
1 0
1 1
0 1
3
3 1 2 4
3 4 2 3
4 1 2 3 4
```

### 输出

```
3
3
4
```

# 题解

## 作者：KaisuoShutong (赞：4)

CF223E Planar Graph 题解。

简单提一下官方题解的 tricky 做法。

首先拿到题目的第一反应肯定是平面图欧拉定理。然后考虑求出 $F$、$E$ 就可以得到 $V$。@滑大稽 搞出了一个基于 [HNOI2016] 矿区 的做法，可以膜她。这里是不是应该用感叹号。

上述做法是基于平面图对偶的。但由于此题询问的良好性质，所以并不需要对偶。

具体地，每一次询问都是一个环状结构。这使得需要被统计的点（环内点）必须经过环上点才能够到达环外。考虑利用这个性质计数。

构造一个流模型：以某个点作为汇点，为每个点赋予 $1$ 的额外流量，让所有点都向着汇点流去。每次询问，计数 流出环 和 流入环 的流数量之差，即为所求。

正确性证明，考虑环内点流出必须经过环，环外点若有流经环内，则必定会流出环。

如何统计这样的流的数量呢？首先图上统计显然是劣的，考虑构建一颗原图的生成树。若此时我们将流网络的汇点设为一个极值点（比如图的最左侧、最右侧点或新建一个极远点），并将汇点作为生成树的根，那么所有环边界上点的邻边中产生环内流向的必定会形成一段倾斜角连续的区间，可以对每个点的出边做极角排序并处理前缀和，这样每次询问就可以快速统计答案。

做法基本就这样，但有几个小的实现细节。

1. 注意到贡献有正有负，可以在生成树上将父边贡献设为负权，子边贡献设为正权，这样可以一起统计。
2. 因为需要取的是极角排序后的一段连续区间，所以环上点必须固定顺/逆时针。题给点并未保证顺逆，但可以通过叉积求面积后的正负性来判断，从而保证顺序。

---

## 作者：滑大稽 (赞：3)

这里介绍一种平面图欧拉定理的做法，官方题解过于思维。感觉这种思路会好想一些？

首先我们考虑，这题是询问一个平面图的一个环内有多少点。那么点数我们不好求，但是环去割平面图，得到的子图一定是联通的。并且面数我们也很好求。那么考虑求出边数，就可以得到点数了。

边数我们直接累加每个环内部面的相邻的边数量。那么发现我们需要的边中，除了边界的边只被计数了一次，其它都被计数了两次。通过这个我们容易算出正确的边数。

至于如何找到我们需要的面，可以使用矿区那题的做法。注意一定是要外部面作为根，否则统计不对。找外部面还是需要算算面积。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#define ll long long
using namespace std;
namespace shik{
	const int N=2e5+5;
	struct infor{
		int x,rev,bel,id;
	};
	vector<infor>g[N];
	struct vec{
		int x,y;
		vec operator-(const vec b)const{return (vec){x-b.x,y-b.y};}
		ll operator*(const vec b)const{return 1ll*x*b.y-1ll*y*b.x;}
	}p[N],p0;
	struct edge{
		int x,y,z;
	}e[N];
	int k[N],val[N],fa[N],si[N],a[N];
	int tot=0,su=0,root,cnt,E,tot2=0;
	bool usd[N];
	inline char gc()
	{
		static char buf[1<<16],*S,*T;
		if(S==T)
		{
			T=(S=buf)+fread(buf,1,1<<16,stdin);
			if(S==T)return EOF;
		}
		return *(S++);
	}
	#define getchar gc
	inline ll read()
	{
		char h=getchar();
		ll y=0;int q=1;
		while(h<'0'||h>'9'){if(h=='-')q=-1;h=getchar();}
		while(h>='0'&&h<='9')y=y*10+h-'0',h=getchar();
		return y*q;
	}
	bool cmp(infor x,infor y)
	{
		vec a=p[x.x]-p0,b=p[y.x]-p0;
		if((a.y>=0)!=(b.y>=0))return a.y>=0;
		if(a.y==0&&b.y==0)return a.x>b.x;
		return a*b>0;
	}
	inline void work(int st,infor &v)
	{
		v.bel=++tot;val[tot]++;
		int x=v.x,res;ll s=0;infor *la=&v;
		while(x!=st)
		{
			la=&g[x][(la->rev==g[x].size()-1)?0:la->rev+1];
			res=x,x=la->x;la->bel=tot;val[tot]++;s+=(p[x]-p[st])*(p[res]-p[st]);
		}
		if(s<0)root=tot;
	}
	inline void add(int a,int b,int c){e[++su]=(edge){k[a],b,c};k[a]=su;}
	void dfs(int x)
	{
		si[x]=1;
		for(int i=k[x];i;i=e[i].x)if(!si[e[i].y])fa[e[i].y]=x,dfs(e[i].y),val[x]+=val[e[i].y],si[x]+=si[e[i].y],usd[e[i].z]=1;
	}
	inline void calc(int x,int y)
	{
		p0=p[x];
		infor res=g[x][lower_bound(g[x].begin(),g[x].end(),(infor){y},cmp)-g[x].begin()],res2=g[y][res.rev];
		if(!usd[res.id]&&!usd[res2.id])return;
		int a=res.bel,b=res2.bel;
		if(a==fa[b])cnt+=si[b],E+=val[b];
		else cnt-=si[a],E-=val[a];
	}
	int main()
	{
		int n=read(),m=read();
		for(int a,b,i=1;i<=m;i++)a=read(),b=read(),g[a].push_back((infor){b}),g[b].push_back((infor){a});
		for(int i=1;i<=n;i++)p[i].x=read(),p[i].y=read();
		for(int i=1;i<=n;i++)p0=p[i],sort(g[i].begin(),g[i].end(),cmp);
		for(int i=1;i<=n;i++)
		for(int res,j=0;j<g[i].size();j++)res=g[i][j].x,p0=p[res],g[i][j].rev=lower_bound(g[res].begin(),g[res].end(),(infor){i},cmp)-g[res].begin();
		for(int i=1;i<=n;i++)
		for(int j=0;j<g[i].size();j++)if(!g[i][j].bel)work(i,g[i][j]);
		for(int i=1;i<=n;i++)
		for(int j=0;j<g[i].size();j++)add(g[i][j].bel,g[g[i][j].x][g[i][j].rev].bel,(g[i][j].id=++tot2));
		dfs(root);
		int t=read();
		while(t--)
		{
			int s=read();cnt=E=0;
			for(int i=1;i<=s;i++)a[i]=read();
			for(int i=1;i<s;i++)calc(a[i],a[i+1]);
			calc(a[s],a[1]);
			if(cnt<0)cnt=-cnt,E=-E;
			E+=s;E>>=1;
			cout<<(E-cnt+1)<<"\n"; 
		}
		return 0;
	}
}
int main(){return shik::main();}
```

---

