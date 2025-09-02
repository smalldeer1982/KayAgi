# [BalticOI 2007] Escape

## 题目描述

战犯们企图逃离监狱，他们详细地计划了如何逃出监狱本身，逃出监狱之后他们希望在附近的一个村子里找到掩护。

村子（下图中的 B）和监狱（图中的 A）中间有一个峡谷，这个峡谷也是有士兵守卫的。守卫峡谷的士兵们坐在岗哨上很少走动，每个士兵的观察范围是 $100$ 米。士兵所处位置决定了战犯们能否安全通过峡谷，安全通过的条件就是在任何时刻战犯们距离最近的士兵大于 $100$ 米。

给定峡谷的长、宽和每个士兵在峡谷中的坐标，假定士兵的位置一直保持不变，请你写一个程序计算战犯们能否不被士兵发现，顺利通过峡谷。

如果不能，那么战犯们最少需要消灭几个士兵才能安全通过峡谷（无论士兵是否被另一个士兵看到，他都可以被消灭）。 

![](https://cdn.luogu.com.cn/upload/image_hosting/59rrua2p.png)

## 说明/提示

对于 $100\%$ 的数据，满足：$1 \leq w \leq 5\cdot 10^4$，$1\leq l \leq 5\cdot 10^4$，$1\leq n \leq 250$，$0 \leq x_i \leq l$，$0 \leq y_i \leq w$。

## 样例 #1

### 输入

```
130 340 5
10 50
130 130
70 170
0 180
60 260```

### 输出

```
1```

# 题解

## 作者：FQ04gty (赞：3)

##### [原题链接](https://www.luogu.com.cn/problem/P6077)

---

考虑何时必须消灭士兵才能通过。

可以发现，在最优方案中，要消灭士兵当且仅当若干个士兵的观察范围将峡谷的上边界和下边界连通，我们才消灭其中一个士兵。

明显的最小割模型——割掉最小数量的士兵，使得上边界和下边界不连通，那么就找到了一条通路。

##### 实现细节

峡谷下边界为 $s$，上边界为 $t$。

对于每一个圆心 $(x_i,y_i)$。

若 $y_i\leq 100$，从 $s$ 向 $i$ 加一条流量为 $1$ 的边。

若 $y_i\geq w-100$，从 $i$ 向 $t$ 加一条流量为 $1$ 的边。

对于点 $(x_j,y_j)$ 使得 $y_j\geq y_i$ 且 $dis(i,j)\leq 200$，由 $i$ 向 $j$ 加一条流量为 $\inf$ 的边。

在该图上得到的最大流即为答案。

算距离时最好不要用 `double`。

### Code
```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#define pow(x) ((x)*(x))
#define mset(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
typedef pair<int,int>pii;
const int SIZE=1010,EXTRA=5e5+10,s=SIZE-2,t=SIZE-1,inf=0x3f3f3f3f;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x*10)+(ch^48),ch=getchar();
    return x;
}
queue<int>q;
int l,w,n,dpth[SIZE],head[SIZE],sizee;
struct edge{int u,v,w,nxt;}e[EXTRA];
inline void add(int u,int v,int w){e[sizee]={u,v,w,head[u]},head[u]=sizee++;}
inline void add_edge(int u,int v,int w){add(u,v,w),add(v,u,0);}
pii p[SIZE];
inline bool bfs()
{
    mset(dpth,0),dpth[s]=1,q.push(s);
    while(!q.empty())
    {
        int thisp=q.front();q.pop();
        for(int i=head[thisp];~i;i=e[i].nxt)if(!dpth[e[i].v]&&e[i].w)dpth[e[i].v]=dpth[thisp]+1,q.push(e[i].v);
    }
    return dpth[t];
}
int dfs(int thisp,int rate)
{
    if(thisp==t)return rate;
    int out=0;
    for(int i=head[thisp],_rate;~i;i=e[i].nxt)if(e[i].w&&dpth[e[i].v]==dpth[thisp]+1)
    {
        _rate=dfs(e[i].v,min(rate,e[i].w));
        rate-=_rate,out+=_rate,e[i].w-=_rate,e[i^1].w+=_rate;
        if(!rate)break;
    }
    if(!out)dpth[thisp]=0;
    return out;
}
inline int dinic(){int res=0;while(bfs())res+=dfs(s,inf);return res;}
inline bool cmp(pii x,pii y){return x.second==y.second?x.first<y.first:x.second<y.second;}
inline int dis(pii x,pii y){return pow(x.first-y.first)+pow(x.second-y.second);}
int main()
{
    mset(head,-1);
    l=read(),w=read(),n=read();
    for(int i=1;i<=n;i++)p[i].first=read(),p[i].second=read();
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        if(p[i].second<=100)add_edge(s,i,1);
        if(p[i].second>=w-100)add_edge(i,t,1);
        for(int j=i+1;j<=n;j++)
        {
            if(dis(p[i],p[j])<=40000)add_edge(i,j,inf);
        }
    }
    printf("%d",dinic());
    return 0;
}
```

---

## 作者：Nazq (赞：0)

可以转化为消灭最少士兵后上下界不连通。

进一步地，转化为至多选择多少条从下界到上界的互不相交（无公共点）路径。

>**Proof**
>
>如果两条路径有交点，则相当于消灭交点处士兵。
>不存在一条路径上，与其他路径有多于 $1$ 个不同交点。若有不同，则有至少有 $2$ 条不交路径。
>![](https://cdn.luogu.com.cn/upload/image_hosting/kq3wz7n1.png)
>如图，如果选红色路径答案优于选黑色路径。
>![](https://cdn.luogu.com.cn/upload/image_hosting/tqza5mqu.png)

考虑网络流。

下界为 $S$，上界为 $T$。

由于路径不交，$i$ 拆点为 $u_i,v_i$，连边 $u_i\to v_i$，容量为 $1$。

对于相交的两个点 $i, j(y_i\lt y_j)$，连边 $v_i\to u_j$，容量为 $1$。



>
>
>考虑现有题解里的最小割做法，是可以被 hack 的。
>```
>500 250
>5
>100 0
>400 0
>250 125
>100 250
>400 250
>```
>![](https://cdn.luogu.com.cn/upload/image_hosting/72jqhkns.png)

>一个拆点的例子。之前一直以为可以 hack 拆点的方法，直到 Acerkaio 大佬提醒才发现这个例子拆点是对的。
>![](https://cdn.luogu.com.cn/upload/image_hosting/21w6zjbx.png)
>$2$ 与 $6$ 相离（虽然图上看起来是连通的，但是之间有极小空隙），路径交点为 $3$。
>
>构造的思路：若没有 $4$，拆点则两条路径因交点答案为 $1$，确实是对的。但是如果我通过某种方法就算你消灭 $3$，你想通过还必须再消灭士兵，导致拆点方法给出错误答案 $1$。那于是添加 $4$，以阻止只消灭 $3$ 就可以通过。
>
>但是，你要覆盖 $3$，就势必要连接 $1, 5$，不论用多少个圆。
>
>于是路径应当为 $(1, 4, 5), (2, 3, 6)$。拆点仍然会给出答案 $2$。

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6077)

# 前置知识

[最小割](https://oi-wiki.org/graph/flow/min-cut/)

# 解法

如果在能相互看到的士兵间连一条边后合法条件就转化为消灭最少的士兵使得上下边界不连通，考虑最小割。

设 $S$ 表示和 $(0,ys)$ 距离 $\le 100$ 的点组成的集合，$T$ 表示和 $(w,ys)$ 距离 $\le 100$ 的点组成的集合。对于 $u \in S,v \in T$ 的有向边 $(u,v)$ 自然是无法删掉的，其容量为 $\infty$；否则容量为 $1$。

为保证转移的有向性，需要先按照纵坐标排序。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const int inf=0x3f3f3f3f;
pair<int,int>a[260];
struct MinCut
{
	struct node
	{
		int nxt,to,cap,flow;
	}e[140010];
	int head[260],vis[260],dis[260],cur[260],cnt=1;
	void add(int u,int v,int w)
	{
		cnt++;  e[cnt]=(node){head[u],v,w,0};  head[u]=cnt;
		cnt++;  e[cnt]=(node){head[v],u,0,0};  head[v]=cnt;
	}
	bool bfs(int s,int t)
	{
		memset(vis,0,sizeof(vis));
		queue<int>q;
		dis[s]=1;  cur[s]=head[s];
		q.push(s);  vis[s]=1;
		while(q.empty()==0)
		{
			int x=q.front();  q.pop();
			for(int i=head[x];i!=0;i=e[i].nxt)
			{
				if(vis[e[i].to]==0&&e[i].cap>e[i].flow)
				{
					dis[e[i].to]=dis[x]+1;  cur[e[i].to]=head[e[i].to];
					q.push(e[i].to);  vis[e[i].to]=1;
					if(e[i].to==t)  return true;
				}
			}
		}
		return false;
	}
	int dfs(int x,int t,int flow)
	{
		if(x==t)  return flow;
		int sum=0,tmp;
		for(int i=cur[x];i!=0&&sum<flow;i=e[i].nxt)
		{
			cur[x]=i;
			if(dis[e[i].to]==dis[x]+1&&e[i].cap>e[i].flow)
			{
				tmp=dfs(e[i].to,t,min(e[i].cap-e[i].flow,flow-sum));
				if(tmp==0)  dis[e[i].to]=0;
				sum+=tmp;
				e[i].flow+=tmp;  e[i^1].flow-=tmp;
			}
		}
		return sum;
	}
	int Dinic(int s,int t)
	{
		int flow=0;
		while(bfs(s,t)==true)  flow+=dfs(s,t,inf);
		return flow;
	}
}C;
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int h,w,n,s,t,i,j;
	cin>>h>>w>>n;  s=n+1;  t=n+2;
	for(i=1;i<=n;i++)  cin>>a[i].second>>a[i].first;
	sort(a+1,a+1+n);
	for(i=1;i<=n;i++)
	{
		if(a[i].first<=100)  C.add(s,i,1);
		if(a[i].first>=w-100)  C.add(i,t,1);
		for(j=i+1;j<=n;j++)
			if(1ll*(a[i].second-a[j].second)*(a[i].second-a[j].second)+1ll*(a[i].first-a[j].first)*(a[i].first-a[j].first)<=40000)  C.add(i,j,inf);
	}
	cout<<C.Dinic(s,t)<<endl;
	return 0;
}	
```

---

