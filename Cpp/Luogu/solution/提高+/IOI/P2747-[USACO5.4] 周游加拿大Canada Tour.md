# [USACO5.4] 周游加拿大Canada Tour

## 题目描述

你赢得了一场航空公司举办的比赛，奖品是一张加拿大环游机票。旅行在这家航空公司开放的最西边的城市开始，然后一直自西向东旅行，直到你到达最东边的城市，再由东向西返回，直到你回到开始的城市。除了旅行开始的城市之外，每个城市只能访问一次，因为开始的城市必定要被访问两次（在旅行的开始和结束）。

当然不允许使用其他公司的航线或者用其他的交通工具。

给出这个航空公司开放的城市的列表，和两两城市之间的直达航线列表。找出能够访问尽可能多的城市的路线，这条路线必须满足上述条件，也就是从列表中的第一个城市开始旅行，访问到列表中最后一个城市之后再返回第一个城市。


## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 5.4


## 样例 #1

### 输入

```
8 9
Vancouver
Yellowknife
Edmonton
Calgary
Winnipeg
Toronto
Montreal
Halifax
Vancouver Edmonton
Vancouver Calgary
Calgary Winnipeg
Winnipeg Toronto
Toronto Halifax
Montreal Halifax
Edmonton Montreal
Edmonton Yellowknife
Edmonton Calgary```

### 输出

```
7```

# 题解

## 作者：远航之曲 (赞：25)

一道基础的dp


把返回的路线反向，那么整条路线就变成了两条不相交的从起点到终点的路线。这样我们可以用DP解决。

状态设定

f[i,j] 为假定的甲乙两人，甲走到第i个城市，乙走到第j个城市时，两人走过的城市数目的和。

初始状态

f[1,1]=1

状态转移方程

f[j,i]=f[i,j]=max{f[i,k]+1}(k到j存在飞机航线，以及f[i,k]>0，就是说存在f[i,k]的走法，1<=k<j，i<j<=n

交换甲乙，则肯定有f[j,i]=f[i,j]。

目标结果

由于题中告知必须走到终点才能返回，输出结果一定是max{f[i,N]}(i到N存在飞机航线)。 如果没有经过城市数目大于1的可行目标状态，则无法完成这次环游，输出1。


```cpp
#include <cstdio>
#include <string>
#include <map>
#include <iostream>
#include <cstring>
using namespace std;
string s,s1,s2;
int n,m,f[110][110],a[110][110];
map <string,int> ma;
main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {
        cin>>s;
        ma[s]=i;
    }
    for (int i=1;i<=m;i++)
    {
        cin>>s1>>s2;
        a[ma[s1]][ma[s2]]=1;
        a[ma[s2]][ma[s1]]=1;
        //printf("%d %d\n",ma[s1],ma[s2]);
    }
    //memset(f,-1,sizeof f);
    f[1][1]=1;
    for (int i=1;i<n;i++)
        for (int j=i+1;j<=n;j++)
        {
            for (int k=1;k<j;k++)
                if (a[j][k]&&f[i][k]) 
                    f[i][j]=max(f[i][j],f[i][k]+1);
            f[j][i]=f[i][j];
        }
    int ans=1;
    for (int i=1;i<=n;i++)
        if(a[i][n])
            ans=max(ans,f[i][n]);
    printf("%d",ans);
}
```

---

## 作者：Celebrate (赞：16)

这一道题其实是一道floyd最大环，也可以说是dp

按照dp来说

就是两个人甲乙，分别从1走到n和n走到1，两个路径不能重复

定义一个f数组，f[i][j]表示甲从1走到i，乙从n走到j的最大值

一开始是f[1][1]=1，题目说无法找出一条满足条件的路线，输

出1，所以就这样开始了

公式：f[i][j]=f[j][i]=max(f[i][j],f[j][k]+1）

为了保证不重复，就要保证1<=k<j，i<j<=n

然后就是floyd3重循环

代码如下：

![代码](https://cdn.luogu.com.cn/upload/pic/20902.png)

防止直接抄袭（至少要手打一遍）

---

## 作者：songyuchen (赞：11)

全都在用动态规划，这里来一个**网络流**的解法

首先和动态规划的套路一样，都是把从起点->终点->起点的环变成**两条不相交的从起点到终点的路径**

首先因为强制只能从西边往东边走，所以直连从小编号到大编号的边。

由于每一个城市只能经过一次（注意这里要除去第一个城市和最后一个城市），所以考虑拆点限制经过一个点的流量最多为1

又因为要求得经过的城市最大，所以可以考虑采用费用流的办法，把每一条边的费用设为1，那么求最大费用最大流即可。

至于字符串处理嘛，可以采用字符串哈希，也可以map

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=105*2;
const int maxM=maxN*maxN*4;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow,w;
};

class Mystring//string太慢了，这里写一个自己的string（反正只是map中要用到）
{
public:
    char name[20];
};

bool operator < (Mystring A,Mystring B)
{
    return strcmp(A.name,B.name)>0;
}

int n,m,S,T;//S-源点，T-汇点
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
map<Mystring,int> Map;
Mystring Name[maxN];
int Dist[maxN],Queue[maxM],Path[maxN],Flow[maxN];
bool vis[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool Spfa();

int main()
{
    mem(Head,-1);
    scanf("%d%d",&n,&m);
    S=1,T=n+n;
    Mystring In1,In2;
    for (int i=1;i<=n;i++)
    {
    scanf("%s",Name[i].name);
    Map[Name[i]]=i;
    }
    for (int i=1;i<=m;i++)
    {
    scanf("%s %s",In1.name,In2.name);
    int id1=Map[In1],id2=Map[In2];
    if (id1>id2) swap(id1,id2);//注意要强制从西边往东边走
    Add_Edge(id1+n,id2,1,1);Add_Edge(id2,id1+n,0,-1);
    }
    Add_Edge(1,1+n,2,0);Add_Edge(n+1,1,0,0);Add_Edge(n,n+n,2,0);Add_Edge(n+n,n,0,0);//特殊处理最西边和最东边的点，因为它们相当于可以经过两次
    for (int i=2;i<n;i++)//其它点都只能经过一次咯
        Add_Edge(i,i+n,1,0),Add_Edge(i+n,i,0,0);
    int Ans=0,flowsum=0;
    while (Spfa())//spfa费用流
    {
    int now=T;
    while (now!=S)
    {
        E[Path[now]].flow-=Flow[T];
        E[Path[now]^1].flow+=Flow[T];
        now=E[Path[now]].u;
    }
    Ans+=Flow[T]*Dist[T];
    flowsum+=Flow[T];
    }
    if (flowsum<2) printf("1\n");//当不满两条路径时要输出无解
    else printf("%d\n",Ans);
    return 0;
}

void Add_Edge(int u,int v,int flow,int w)
{
    edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
    E[edgecnt]=((Edge){u,v,flow,w});
    return;
}

bool Spfa()
{
    mem(Dist,-1);mem(vis,0);
    int h=1,t=0;Queue[1]=S;Dist[S]=0;vis[S]=0;Flow[S]=inf;
    do
    {
    int u=Queue[++t];vis[u]=0;
    for (int i=Head[u];i!=-1;i=Next[i])
    {
        int v=E[i].v;
        if ((E[i].flow>0)&&((Dist[v]==-1)||(Dist[v]<Dist[u]+E[i].w)))
        {
        Dist[v]=Dist[u]+E[i].w;Path[v]=i;Flow[v]=min(Flow[u],E[i].flow);
        if (vis[v]==0) vis[Queue[++h]=v]=1;
        }
    }
    }
    while (t!=h);
    if (Dist[T]==-1) return 0;
    return 1;
}
```
嗯，如果想输出方案的话可以做一做[这道题](https://www.luogu.org/problemnew/show/2770 "这道题")


---

## 作者：yybyyb (赞：7)

动态规划套路题？？？？

首先题目的要求是从$1-n$找一条路线

再返回来找一条不相交的路线

这样很不好搞对不对？

我们反过来想，把第二条找回来的路线反过来看

题目就变成了

从$1$出发，找两条不相交的路径到达$n$，求路径之和最大

那么这样就好搞多了

设$f[i][j]$表示一条线路搞到了$i$，另一条搞到了$j$

强制$j>i$这样的话方便转移

那就是枚举一个$k$

其中$k∈[1,j)$

$f[i][j]=max(f[i][k]+1)$

直接大力搞就行了

值得注意的是最后的答案

为$max(f[i][n]),i∈[1,n]$

但是对于所有的$i$，要有$i$与$n$联通才能更新答案

别问我字符串啥的怎么搞。~~STL大法好~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define MAX 200
map<string,int> M;
int n,m;
bool g[MAX][MAX];
string Pla[MAX],s1,s2;
int f[MAX][MAX],ans=1;
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;++i)
    {
        cin>>Pla[i];
        M[Pla[i]]=i;
    }
    for(int i=1;i<=m;++i)
    {
        cin>>s1>>s2;
        g[M[s1]][M[s2]]=g[M[s2]][M[s1]]=1;
    }
    memset(f,-63,sizeof(f));
    f[1][1]=1;
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j)
        {
            if(i==j)continue;
            for(int k=1;k<j;++k)
                if(g[j][k])
                    f[i][j]=f[j][i]=max(f[i][j],f[i][k]+1);
        }
    for(int i=1;i<=n;++i)
        if(g[i][n])
            ans=max(ans,f[i][n]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：keepwatcher_kensap (赞：3)

## Part 1 前言

在写本题的时候原本是用暴搜的，但感觉太慢了过不去。于是就开始想别的做法，但依旧没想到。试着用动态规划的时候也被绕晕了。在题解区看到 [Edwin_liannan](https://www.luogu.com.cn/user/511042) 的做法后便学了 Floyd 最大环，成功 AC 此题。

如果你不会 Floyd 最大环，或是想用比较快且简单的办法 AC 本题，便可以看看此题解。

## Part 2 题意

你将开始一场 Canada 之旅，有 $n$ 个城市，$m$ 条无向道路相连通。城市按照输入顺序分别位于 Canada 的从西到东。

抽象化理解后，我们可以将来回理解为两条路线 $a,b$，且 $a_{begin}=b_{begin}=1$，$a_{end}$ 与 $b_{end}$ 其中一个为 $n$。又 $a_{end}$ 和 $b_{end}$ 有直接道路相连。除起点和终点外 $a,b$ 路线没有经过相同的地方。求 $a,b$ 中最多出现的城市数量。

## Part 3 引入

传统情况下，我们用 Floyd 求节点不多的最短路问题，令 $n$ 为节点数，$f_{i,j}$ 表示点 $i,j$ 间的最短路长度。初始的时候 $f_{x.x}(1 \leq x \leq n)$,。通过枚举起点 $i$，终点 $j$，断点 $k$ 来求得 $f_{i,j}$，基本状态转移方程为：

- $f_{i,j}=\min(f_{i,j},f_{i,k}+f_{k,j})$。

而在本题中要求最长的，所以基本思想就是将 $\min$ 改为 $\max$。

## Part 4 思路

为了方便做题，我们将题目中的城市名称以 map 映射的方式转化为数组：

```
map<string,int> name;

for (int i=1;i<=n;i++)
{
	string str;
	cin>>str;
	name[str]=i;
}
```

在环游的过程中必然只能在两座有道路的城市之间穿梭，因此我们可以用一个 bool 数组 $g$，$g_{i,j}$ 表示城市 $i,j$ 之间是否有联通:

```
bool g[105];

for (int i=1;i<=m;i++)
{
	string str1,str2;
	cin>>str1>>str2;
	g[name[str1]][name[str2]]=g[name[str2]][name[str1]]=true;
}
```
在 Part 2 中提到可以将其抽象化为 $a,b$ 路径，而我们假设 $a$ 路径走到了 $i$ 城市，$b$ 路径走到了 $j$ 城市，两者除起点外没有重合的城市，且 $i$ 城市与 $j$ 城市直接相连的情况下，最多经过的城市数量为 $f_{i,j}$。

为了方便，我们假设 $b$ 是走到了 $n$ 城市的路线，而 $a$ 的终点与 $n$ 城市直接相连。则有 $i<j$。

我们确保了 $i,j$ 城市直接相连，枚举与 $j$ 直接相连的城市 $k(k<j)$，不难发现，当 $i,k$ 城市直接或间接相连的情况下。可以得到状态转移方程：

- $f_{i,j}=\max(f_{i,j},f_{i,k}+1)$。

```
int f[105][105]

f[1][1]=1;
for (int i=1;i<=n-1;i++)
{
	for (int j=i+1;j<=n;j++)
	{
		for (int k=1;k<=j-1;k++)
		{
			if (!g[j][k] || f[i][k]==0) continue;
			f[i][j]=max(f[i][j],f[i][k]+1);
		}
		f[j][i]=f[i][j];
	}
}
```

至于最后的答案，令 $Z$ 是所有与 $n$ 直接相连的点，则有 $result=\max(f_{Z,n})$。

```
int result=1;
for (int i=1;i<=n;i++) if (g[i][n]) result=max(result,f[i][n]);
cout<<result<<endl;
```

## Part 5 代码

```
#include <bits/stdc++.h>
using namespace std;
bool g[105][105];
int n,m,f[105][105];
map<string,int> name;
int main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		string str;cin>>str;name[str]=i;
	}
	for (int i=1;i<=m;i++)
	{
		string str1,str2;cin>>str1>>str2;
		g[name[str1]][name[str2]]=g[name[str2]][name[str1]]=true;
	}
	f[1][1]=1;
	for (int i=1;i<=n-1;i++)
	{
		for (int j=i+1;j<=n;j++)
		{
			for (int k=1;k<=j-1;k++)
			{
				if (!g[j][k] || f[i][k]==0) continue;
				f[i][j]=max(f[i][j],f[i][k]+1);
			}
			f[j][i]=f[i][j];
		}
	}
	int result=1;
	for (int i=1;i<=n;i++) if (g[i][n]) result=max(result,f[i][n]);
	cout<<result<<endl;
	return 0;
}
```

## Part 6 后记

本题的状态表示本身就很难想到，加上极其复杂的状态转移条件，导致这种比其他题解要简洁不少的做法却很少被使用。希望大家可以认真学习 Floyd 算法的扩展思维，试着自己写一遍出来。

---

## 作者：云岁月书 (赞：3)

~~IOI 1993 的原题，疑似 DP 起源。~~

### 费用流：

先不讲 DP，讲一下这题费用流的做法。~~毕竟这种做法不用太多脑子。~~

首先，要看出一点，这题目所要求的其实与方向无关，可以看作两个人同时从 1 出发走到 n，中间两人不能经过同一个点。

其次，走的路径和经过的点权都要考虑，所以单纯的网络流很难满足，考虑费用流。

最后，因为在走的路径不能重叠的限制，显然是把走的路径当做流量，把经过的点的点权作为费用比较好做。

综上，再辅以一定的尝试，我们可以建出本题网络流模型：

将 1 点设为源点，拆点，中间连流量为 2，费用为 1 的边。

将 n 点设为汇点，拆点，中间连流量为 2，费用为 1 的边。

对于其余的点，拆点，中间连一条流量为 1，费用也为 1 的边(这样就限制了每个点只能经历一次)。

其余的边流量为 1，费用为 0。

这样直接跑最大费用最大流就可以了。

对于烦人的读入，直接用 STL 就可以了。

#### Code 1:
~~~
# include <map>
# include <cstdio>
# include <string>
# include <cstdlib>
# include <cstring>
# include <iostream>
# include <algorithm>
# define N 10000
# define M 100000
# define reg register
using std::map;
using std::cin;
using std::cout;
using std::string;

class Queue
{
    static const int MAX_QUEUE_SIZE = 2e5;
    private:
            int Q_U_E_E[MAX_QUEUE_SIZE],rear_,front_;
    public:
            Queue(){rear_=-1;front_=0;}
            ~Queue(){}

            inline void Push(const int Val){Q_U_E_E[++rear_] = Val;}
            inline int Size(){return rear_-front_+1;}
            inline void reset(){rear_=-1;front_=0;}
            inline bool Empty(){return rear_ < front_;}
            inline int Get(){return Q_U_E_E[front_++];}
            inline int Front(){return Q_U_E_E[front_];}
            inline void Pop(){++front_;}
} q;

struct edge
{
    int Next,to,Wi,Flow;
    edge(const int Next_=0,const int to_=0,const int Wi_=0,const int Flow_=0):Next(Next_),to(to_),Wi(Wi_),Flow(Flow_){}
} e[M+5];

int n,m,edge_tot = 1,S,T,head[N+5],ans;

inline void add_edge(const int u,const int v,const int wi,const int Flow)
{
    e[++edge_tot] = edge(head[u],v,wi,Flow);
    head[u] = edge_tot;
}

string s1,s2;
bool inq[N+5];
map<string,int> mp;
int dis[N+5],flow[N+5],Pre[N+5];

void Input()
{
    cin>>n>>m;

    for(reg int i = 1; i <= n ; ++i)
    {
        cin>>s1;
        mp[s1] = i;
    }
}

void Build_Graph()
{
    Input();
    S = 1;T = n;
    add_edge(S,S+n,0,2);add_edge(S+n,1,0,0);
    add_edge(T,T+n,0,2);add_edge(T+n,T,0,0);

    for(reg int i = 2; i < n ; ++i){add_edge(i,i+n,0,1);add_edge(i+n,i,0,0);}

    for(reg int i = 1,x,y; i <= m ; ++i)
    {
        cin>>s1>>s2;
        x = mp[s1];y = mp[s2];
        if(y < x) x ^= y ^= x ^= y;
        add_edge(x+n,y,1,1);
        add_edge(y,x+n,-1,0);
    }
}

bool SPFA()
{
    memset(inq,0,sizeof(inq));
    memset(dis,-1,sizeof(dis));
    memset(flow,0x3f,sizeof(flow));
    q.reset();q.Push(S);inq[S] = 1;dis[S] = 0;
    
    while(q.Size())
    {
        int u = q.Get();inq[u] = 0;
        
        for(reg int i = head[u]; i ; i = e[i].Next)
            if(e[i].Flow > 0 && (dis[e[i].to] < dis[u] + e[i].Wi))
            {
                dis[e[i].to] = dis[u] + e[i].Wi;
                Pre[e[i].to] = i;
                flow[e[i].to] = flow[u] > e[i].Flow ? e[i].Flow : flow[u];
                if(!inq[e[i].to]){q.Push(e[i].to);inq[e[i].to] = 1;}
            }
    }

    return dis[T] != -1;
}

inline bool MCMF()
{
    int Max_Flow = 0;

    while(SPFA())
    {
        Max_Flow += flow[T];
        ans += flow[T] * dis[T];
        reg int u = T;
        
		while (u != S)
        {
            e[Pre[u]].Flow -= flow[T];
            
			e[Pre[u]^1].Flow += flow[T];
		
            u = e[Pre[u]^1].to;
        }
    }

    return Max_Flow == 2;
}

int main()
{
    Build_Graph();

    if(MCMF()) printf("%d",ans);
    else printf("1");

    return 0;
}
~~~

其实虽然本题的费用流模型很裸，但是对代码能力要求较高，Debug 时间可能较长(~~主要原因是我已经 N 年没写过网络流费用流相关题目~~)。

### 想办法降低码量，考虑 DP：

**题目求的其实与方向无关，可以看作两个人同时从 1 出发走到 n，中间两人不能经过同一个点。**

回到这个关键点，其实这里抽象化一下相当于在原图中求一个包含 1，n 两点的最大环。

设计状态 $dp[i][j]$ 表示从起点分别走到 $i,j$ 的不重复最长路径。

首先最基础的一点，他本身是有对称性，也就是 $dp[i][j] = dp[j][i]$,因为两人交换路径不会影响答案。

难点在于如何确定每个点只经历一次，这一点我看其他题解也没讲清楚(~~可能是太显然了~~)。

其实这一点也不难，因为我们采用了邻接矩阵存图，所以天然的没有重边，
而在枚举路径的时候，其实我们是通过每条边只会被用一次来维持 $dp$ 数组的每一次转移路径不重叠。

综上所述，便有了状态转移方程：

$$dp(j,i) = dp(i,j) = Max(dp(i,k)+1)\ \ i \in[1,n],j \in(i,n],k\in[1,j)$$

最后初始化时 $dp[1][1] = 1$。 

答案为所有与 1 有边连接的点的最大值。

极限压缩码量以后能做到整个代码 527B 的码量(与上面的网络流形成鲜明对比)。

#### Code 2：
~~~c++
#include<map>
#include<string>
#include<iostream>
#define F(k,l,r) for(int k=l;k<=r;++k)
using namespace std;
int n,m,G[105][105],f[105][105],ans=1;
string s1,s2;
map<string,int> p;
int main()
{
    cin>>n>>m;
    F(i,1,n){cin>>s1;p[s1]=i;}
    F(i,1,m){cin>>s1>>s2;G[p[s1]][p[s2]]=G[p[s2]][p[s1]]=1;}
    f[1][1]=1;\\压缩版
    F(i,1,n)F(j,i+1,n)F(k,1,j-1)if(G[j][k]&&f[i][k])f[i][j]=f[j][i]=((f[i][j]<=f[i][k])?f[i][k]+1:f[i][j]);
    F(i,1,n)if(G[i][n])ans=(ans<f[i][n]?f[i][n]:ans);
    cout<<ans;
    return 0;
}

void DP()\\不压缩码量的 DP。
{
    f[1][1] = 1;
    for(reg int i = 1; i <= n ; ++i)
        for(reg int j = i+1; j <= n ; ++j)
            for(reg int k = 1; k < j ; ++k)
                if(G[j][k] && f[i][k])
                    f[i][j] = f[j][i] = ((f[i][j] <= f[i][k]) ? f[i][k]+1 : f[i][j]);
    int ans = 1;
    for(reg int i = 1; i <= n ; ++i)
        if(G[i][n]) ans = ((ans < f[i][n]) ? f[i][n] : ans);
    printf("%d\n",ans);
}
~~~



---

## 作者：船酱魔王 (赞：2)

# P2747 [USACO5.4] 周游加拿大Canada Tour 题解

## 题意回顾

在无向图上找到一个先由 $ 1 $ 到 $ n $ 点号递增，再由 $ n $ 到 $ 1 $ 点号递减的简单环，使环长最大。

$ 1 \le n \le 100 $。

## 分析

单纯的无向图最大简单环问题似乎不太好做，考虑本问题的特殊性质：环的点号先增大再减小。

因为是无向图，我们不妨拆环，把问题转化为由 $ 1 $ 到 $ n $ 走两次，要求两条路线点号递增，每个中间点只能用一次，求出最多的经历点的个数。

我们可以参考『传纸条』一题的思路，同时维护两条路线的当前所到结点。因为转移是在图上进行的，故使用主动转移。

两条路线没有相对顺序，但我们可以认为两个路线是轮流扩展的，点号靠前的路线为了避免重合点必须扩展到另一条路线当前位置之后，靠后的路线扩展到本身后面的点即可。

可以理解成，将两个路线的中间点排序，把每种路线在序列上的的一个极长连续段连续扩展（对应较大点号路向前走），再连接下一个段和上一个段（对应较小点号路跨越到较大点号路之后）。

$ dp_{i,j} $ 表示两条路线分别已经到达 $ i,j $ 的最多点数，因为 $ i,j $ 顺序对状态无影响，此处我们只说明 $ i<j $ 的情况（$ i>j $ 时状态转移方法同理）。

* 对于 $ i,v $ 存在边且 $ j<v $，$ dp_{v,j}\leftarrow dp_{i,j}+1 $。

* 对于 $ j,v $ 存在边且 $ j<v $，$ dp_{i,v}\leftarrow dp_{i,j}+1 $。

注意特殊处理 $ i=j=1 $ 和 $ i=j=n $ 两个情况。

时间复杂度 $ O(nm) $，边数 $ m=n^2 $ 时运行次数上限约为 $ n^3=10^6 $ 量级，可过。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;
const int N = 105;
const int inf = 1e9 + 5;
int n, m;
map<string, int> mp;
vector<int> g[N];
int dp[N][N];
int main() {
    cin >> n >> m;
    string u, v;
    for(int i = 1; i <= n; i++) {
        cin >> u;
        mp[u] = i;
    }
    int u1, v1;
    for(int i = 1; i <= m; i++) {
        cin >> u >> v;
        u1 = mp[u];v1 = mp[v];
        if(u1 > v1) swap(u1, v1);
        g[u1].push_back(v1);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            dp[i][j] = -inf;
        }
    }
    dp[1][1] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i < j || i + j == 2) {
                for(int k = 0; k < g[i].size(); k++) {
                    int v = g[i][k];
                    if(v <= j && v + j != 2 * n) continue;
                    dp[v][j] = max(dp[v][j], dp[i][j] + 1);
                }
                for(int k = 0; k < g[j].size(); k++) {
                    int v = g[j][k];
                    dp[i][v] = max(dp[i][v], dp[i][j] + 1);
                }
            } else {
                for(int k = 0; k < g[j].size(); k++) {
                    int v = g[j][k];
                    if(v <= i && i + v != 2 * n) continue;
                    dp[i][v] = max(dp[i][v], dp[i][j] + 1);
                }
                for(int k = 0; k < g[i].size(); k++) {
                    int v = g[i][k];
                    dp[v][j] = max(dp[v][j], dp[i][j] + 1);
                }
            }
        }
    }
    if(dp[n][n] < 0) dp[n][n] = 1;
    printf("%d\n", dp[n][n]);
    return 0;
}

```

---

## 作者：Coros_Trusds (赞：1)

小清新 $\rm dp$。

# 题目大意

有 $n$ 个城市，$m$ 条线路。

小 $\rm A$ 从城市 $1$ 走到城市 $n$，小 $\rm B$ 从城市 $n$ 走到城市 $1$，两人的路径不能相交，求他们能够经过的最大城市数量之和。

# 题目分析

令 $dp_{i,j}$ 表示小 $\rm A$ 走到城市 $i$，小 $\rm B$ 走到城市 $i$ 经过的最大城市数量之和。（当然要保证路径不相交）

显然 $dp_{1,1}=1$。

状态方程也很好推，就是从上一个城市转移来，数据范围较小，所以直接枚举即可，但是如果数据范围更大我们可以采用邻接链表存图来快速转移。

状态转移方程为 $dp_{i,j}=\max\{dp_{i,k}+1\}$，城市 $k$ 与城市 $j$ 有边。值得注意的是，每次转移过后需要 $dp_{j,i}=dp_{i,j}$，因为路径对称。

# 代码

```cpp
//2022/3/5
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <string>
#include <map>
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int ma = 105;
int dp[ma][ma];//dp[i][j]:A 走到 i,B 走到 j 两人走过的城市数量之和
bool G[ma][ma];
map<string,int>mp;
int n,m;
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	cin >> n >> m;
	for (register int i = 1;i <= n; ++ i) {
		string str;
		cin >> str;
		mp[str] = i;
	}
	for (register int i = 1;i <= m; ++ i) {
		string s1,s2;
		cin >> s1 >> s2;
		G[mp[s1]][mp[s2]] = G[mp[s2]][mp[s1]] = true;
	}
	mst(dp,-1);
	dp[1][1] = 1;
	for (register int i = 1;i < n; ++ i) {
		for (register int j = i + 1;j <= n; ++ j) {
			for (register int k = 1;k < j; ++ k) {
				if (G[j][k] == true && dp[i][k] != -1) {
					dp[i][j] = dp[j][i] = max(dp[i][j],dp[i][k] + 1);
				}
			}
		}
	}
	int ans = 1;
	for (register int i = 1;i <= n; ++ i) {
		if (G[i][n]) {
			ans = max(ans,dp[i][n]);
		}
	}
	printf("%d\n",ans);

	return 0;
}
```

---

## 作者：ttq012 (赞：1)

**费用流**

首先，可以将 $1$ 点设为源点，然后拆点，中间连流量为 $2$，费用为 $1$ 的边。然后将 $n$ 点设为汇点，然后拆点，中间连流量为 $2$，费用为 $1$ 的边，其余的点拆点后中间连流量为 $1$，费用为 $1$ 的边，其余边流量为 $1$，费用为 $0$。

建完网络流之后，直接跑一遍最大流就可以了。

**双向动态规划**

我们设 $dp[i][j]$ 表示左边的人到i号城市时和右边的人到j号城市时所走过的总城市数目。
因为有对称性，所以显然有 $dp[i][j] = dp[j][i]$。

初始条件：$dp[1][1] = 1$。

在枚举路径的时候，由于每条边只会被用一次，所以有转移方程：
$dp[i][j] = dp[j][i] = \max(dp[i][k] + 1)$。



---

## 作者：Edwin_liannan (赞：1)

# Thinking
## 类似Floyd最大环，最多黄题
可以看成两个人，一个从起点出发，一个从终点出发。
用 `Floyd` 最大环(即把求最短路的 `min` 改成 `max` )。


# Productiveness
效率即为求 `Floyd` 的过程： $ O(n^3) $ 。

# Code
### Talk is cheap, show me the code.
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[105][105],n,v,ans=1;
map<string,int> mp;
bool g[105][105];
string s,s2;
#define f(i,a,b) for(int i=a;i<=b;i++)
int main(){
	cin>>n>>v;
	f(i,1,n) cin>>s,mp[s]=i;
	f(i,1,v) cin>>s>>s2,g[mp[s]][mp[s2]]=g[mp[s2]][mp[s]]=1;
	f[1][1]=1;
	f(i,1,n-1)
		f(j,i+1,n){
			f(k,1,j-1) if(g[j][k]&&f[i][k]) f[i][j]=max(f[i][j],f[i][k]+1);
			f[j][i]=f[i][j];
		}	
	f(i,1,n) if(g[i][n]) ans=max(ans,f[i][n]);
	cout<<ans;
}
```

---

## 作者：SNiFe (赞：1)

题意可以理解为为一个人先自西向东，再自西向东，且不经过相同的城市，并且航线是双向的，由此可以把问题转换为，有两个人分别从 1 号城市出发，同时向东旅行，且不经过相同城市，并且乙到达 n 城市后，甲在与 n 城有航线的城市。

用 f[i][j] 表示甲走到 i 城市，乙走到 j 城市时所经过的总城市数，边界条件 f[1][1]=1，转移方程为


###f[i][j]=max{f[i][k]+1}+1（k,j 有航线且 1<=k<j 且 f[i][k]>0）


因为对于甲乙两个人来说，是甲走到 i 乙走到 j 还是甲走到 j 乙走到 i 是一样的，所以方程为


f[i][j]=f[j][i]=max{f[i][k]+1}+1 k,j 有航线且 1<=k<j 且 f[i][k]>0


如此一来，最优解就得到了

ans=max{f[i][n]} 1<=i<n

对于输入的是城市名的问题，只需用 map<char,int> 就可以啦，把名字映射到输入的序号上。

上代码（有详细批注）：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<iostream>
#include<cmath>
using namespace std;
const int N=205;
char s[N],t[N];
map<string,int>orz;
int n,m,mp[N][N],dp[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);
        orz[s]=i;
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%s %s",s,t);
        mp[orz[s]][orz[t]]=1;
        mp[orz[t]][orz[s]]=1;
    }
    int ans=1;
    dp[1][1]=1;
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            for(int k=1;k<j;k++)//类似floyd
            if(mp[j][k]&&dp[i][k]&&dp[i][k]+1>dp[i][j])
            dp[i][j]=dp[j][i]=dp[i][k]+1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(mp[i][n])//这个判断很重要，我没加之前只有45分
        ans=max(ans,dp[i][n]);
    }
    printf("%d",ans);
}
```

---

## 作者：Chronomaly_Atlandis (赞：0)

**思路**

把返回的路线反向，那么这次旅行就变成了两条从起点到终点的路线。

题目就变成了：从起点出发，找两条不相交的路径到达终点，求最大的路径和。

这样就可以用动态规划解决了。

**设置状态：**

设有两人 A 和 B，那么 $\mathit{dp}_{i,j}$ 表示 A 走到第 $i$ 个城市，B 走到第 $j$ 个城市时，两人走过的城市数量的总和。

**转移方程：**

$$\mathit{dp}_{i,j}=\operatorname{max}(\mathit{dp}_{i,j},\mathit{dp}_{i,k}+1)$$

让 $j>i$，方便转移。

注意：这里的 $k∈[1,j)$。

**初始化：**

$$\mathit{dp}_{1,1}=1$$

最后的答案为：

$$\operatorname{max}(\mathit{dp}_{i,n})$$

其中，$i∈[1,n]$。

但是 $i$ 要与 $n$ 联通才能更新答案。

关于存储字符串，这里用 `map` 比较方便。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=150;
int n,m,dp[maxn][maxn],x[maxn][maxn];
map<string,int>mp;
main(){
	cin.tie(NULL);
    cin >> n >> m;
    for (int i=1;i<=n;i++){
    	string s;
        cin >> s;
        mp[s]=i;
    }
    for (int i=1;i<=m;i++){
    	string tmp,temp;
        cin >> tmp >> temp;
        x[mp[tmp]][mp[temp]]=1,x[mp[temp]][mp[tmp]]=1;
    }
    dp[1][1]=1;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=1;k<j;k++)if(x[j][k]&&dp[i][k])dp[i][j]=max(dp[i][j],dp[i][k]+1);
            dp[j][i]=dp[i][j];
        }
    }
    int ans=1;
    for (int i=1;i<=n;i++)if(x[i][n])ans=max(ans,dp[i][n]);
    cout << ans;
    return 0;
}
```

---

## 作者：chenzhangpei (赞：0)

### 前言

这是我第一道 USACO 的蓝题，收获蛮大的，写篇题解纪念一下。

### 思路

标签是 `动态规划，DP` ，那好,我们就来试试 DP。

因为：
 
旅行在这家航空公司开放的最西边的城市开始，然后一直自西向东旅行，直到你到达最东边的城市，再由东向西返回，直到你回到开始的城市。除了旅行开始的城市之外，每个城市只能访问一次，因为开始的城市必定要被访问两次（在旅行的开始和结束）。

所以，我们把返回的过程倒放 ,你会发现这就是除了过去的路径的第二条满足条件的从起点到终点的路线。

那么我们可以让“我”分身，变成甲,乙两人。

这就可以用动态规划来解决了。

既然确定了是动态规划，来，上动态规划“四件套”。

**1. 状态设定** 

$dp[i,j]$ 为假定的甲，乙两人，甲走到了第 $i$ 个城市，乙走到了第 $j$ 个城市时，两人走过的城市数目的和。

**2. 初始状态**

既然是初始状态，那么就是起点,即 $dp[1,1] = 1$。

**3. 状态转移方程**

$dp[i,j] = \max(dp[i,j],dp[i,k] + 1)$

$k$ 到 $j$ 存在飞机航线，以及 $f[i,k] > 0$，就是说存在 $f[i,k]$ 的走法。

范围：$1 \le k < j $，$i < j \le n$ 。

这用个三重循环就可以写出来。

但是仔细想想，会发现把甲，乙两个数倒过来和还是一样，所以就有$dp[i,j] = dp[j,i]$。

**4. 目标状态**

既然确定了状态设定初始状态和状态转移方程，那么就差该求什么了。

题目说先得走到终点，然后再返回。那么结果肯定是 $\max(dp[1,n],ans)$。

$Q$：
那么 $i$ 到 $j$ 之间有航线，怎么标记呢？

$A$：
使用 `map` 映射来标记即可。

[不会用 `map` 的同学看这里](https://blog.csdn.net/qq_41700151/article/details/81231688)

### 代码

**核心 DP 代码**

```
dp[1][1]=1;//初始化
for(int i=1; i<n; i++) {
	for(int j=i+1; j<=n; j++) {
		for(int k=1; k<j; k++) {
			if(a[j][k]==1 && f[i][k]>0) {
				dp[i][j]=max(dp[i][j],dp[i][k]+1);//状态转移方程
			}
		}
		dp[j][i]=dp[i][j];//对应
	}
}
```

**完整代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,s1,s2;
int n,m,dp[105][105];
bool a[105][105];
map<string,int> ma;
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		cin>>s;
		ma[s]=i;
	}
	for(int i=1; i<=m; i++) {
		cin>>s1>>s2;
		a[ma[s1]][ma[s2]]=1;
		a[ma[s2]][ma[s1]]=1;//映射
	}
	dp[1][1]=1;
	for(int i=1; i<n; i++) {
		for(int j=i+1; j<=n; j++) {
			for(int k=1; k<j; k++) {
				if(a[j][k]==1 && dp[i][k]>0) {
					dp[i][j]=max(dp[i][j],dp[i][k]+1);
				}
			}
			dp[j][i]=dp[i][j];
		}
	}

	int ans=1;//要注意：如果无法找到路线，输出 1。
	for(int i=1; i<=n; i++) {
		if(a[i][n]) {
			ans=max(ans,dp[i][n]);//更新答案
		}
	}

	cout<<ans;
	return 0;
}
```

---

## 作者：BrokenSword (赞：0)

嗯，我们的%ni赛又出原题了。

当时考场是这么想的：

# 暴力出奇迹 #
其实是想正着建一张图再反着建一张图，跑两边dfs取最大答案。

这个思路不用想绝壁会T飞起来。

于是就有了如下蛇皮剪枝：

**①**对两张图各跑一遍Floyd，如果当前答案+不考虑重点的最大答案<=ans就return.

**②**记录到不了的点的个数，如果当前答案==总点数-记录点数则直接输出答案走人。

**③**如果1到不了n直接puts("1");return 0;。

然后发现在过去和回来必须经过同一点的情况可能会输出0，特判了一下。

结果 期望得分30~60 实际得分80.TLE*2.

# ∴暴力还是出了奇迹。

代码如下：（主要是我现在还没想出一种能把↓剪到A的办法，就放弃了。）
```cpp
#include<bits/stdc++.h>
#define IN inline
#define RE register 
#define res register int 
//#define int long long
IN int read(){
	res f=1,x=0;
	RE char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=0;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f?x:-x;
}
#define For(q,w) for(res i=q;i<=w;i++)
#define fOr(q,w) for(res j=q;j<=w;j++)
#define foR(q,w) for(res k=q;k<=w;k++)
#define FOR for(res i=d[now];i;i=b[i].next)
#define FOr for(res i=e[now];i;i=c[i].next)
#define max(a,b) (((a)>(b))?(a):(b))
#define ljc 10000007
#define qwer 510
using std::swap;
using std::map;
using std::string;
string s;
int n,m,d[qwer],e[qwer],cnt,q,w,ans,dis[qwer],eis[qwer],f[qwer][qwer],g[qwer][qwer],xxx;
map<string,int>qwq;
bool is[qwer];
struct star{
	int to,next;
}b[qwer<<2],c[qwer<<2];
IN void psh(const int &from,const int &to){
	b[++cnt].to=to;
	c[cnt].to=from;
	b[cnt].next=d[from];
	c[cnt].next=e[to];
	d[from]=e[to]=cnt;
}
IN void dfs2(int now,int x){
	if(now==1){
		ans=max(ans,x);
		if(ans==n-xxx){
			printf("%d\n",ans);
			exit(0);
		}
		return ;
	}
	if(ans>=x+g[now][1])return;
	is[now]=1;
	FOr{
		if(is[c[i].to])continue;
		dfs2(c[i].to,x+1);
	}
	is[now]=0;
}
IN void dfs1(int now,int x){
	if(now==n){
		dfs2(n,x);
		return ;
	}
	if(ans>=x+f[now][n]+g[n][1])return;
	is[now]=1;
	FOR{
		if(is[b[i].to])continue;
		dfs1(b[i].to,x+1);
	}
	is[now]=0;
}
signed main(){
	freopen("tour.in","r",stdin);
	freopen("tour.out","w",stdout);
	n=read();
	m=read();
	For(1,n){
		std::cin>>s;
		qwq[s]=i;
	}
	memset(f,0xff,sizeof(f));
	memset(g,0xff,sizeof(g));
	For(1,m){
		std::cin>>s;
		q=qwq[s];
		std::cin>>s;
		w=qwq[s];
		if(q>w)swap(q,w);
		psh(q,w);
		f[q][w]=1;
		g[w][q]=1;
	}
	For(1,n)f[i][i]=g[i][i]=0;
	For(1,n)
	fOr(1,i-1)
	if(f[j][i]>=0)foR(i+1,n){
		if(f[i][k]>=0 && f[j][i]+f[i][k]>f[j][k])f[j][k]=f[j][i]+f[i][k];
	}
	For(1,n)fOr(i+1,n)
	if(g[j][i]>=0)foR(1,i-1){
		if(g[i][k]>=0 && g[j][i]+g[i][k]>g[j][k])g[j][k]=g[j][i]+g[i][k];
	}
	if(f[1][n]==-1){
		puts("1");
		return 0;
	}
	For(2,n)if(f[1][i]==-1)xxx++;
	for(res i=d[1];i;i=b[i].next)dfs1(b[i].to,1);
	if(ans==0)ans=1;
	printf("%d\n",ans);
	return 0;
}
```
然后嘛，正解可以dp。

$f[i][j]$=从$j$走到$1$再从$1$走到$i$的最大不重复点数。

转移方程:如果i到k有边，则$f[i][k]=max(f[i][k],f[i][j]+1)$

如果j到k有边，则$f[k][j]=max(f[k][j],f[i][j]+1)$.

$($$k>i$ $&&$ $k>j$$)$

答案即为$f[n][n]-1$.

代码懒得放了。

~~对了，有兴趣加入[颓废教派](https://www.luogu.org/team/show?teamid=21582)吗？~~

---

## 作者：蒟蒻初音ミク (赞：0)

# 广告

[蒟蒻的blog](https://www.luogu.com.cn/blog/111990/)

# 正文

这个题有一个加强版（即转化成二维平面）：[NOIP提高组2018 传纸条](https://www.luogu.org/problem/P1006)

再说这道题，如果用**网络流**，那么这两道题其实~~就是码农题~~思路都是一样的。

把找一个环变为找两条不相交的路径，要求这两个路径经过的点的数量最多。

也就是**每一个点的权值为$1$，同时每一个点只能走一遍，要求路径的权值最大**。

只能走一遍？权值为$1$？想到了什么？**拆点**啊！！！

对于每一个点$x$，拆成两个点，一个入点$x$，一个出点$x+n$，两点之间连一条由入点连向出点的边，流量为$1$（表示这个点只能经过一次），费用为$1$（表示这个点的权值为$1$）。

但是，**特殊的，起点的流量为$2$，终点的流量为$2$**（因为两条路径都要经过他们，即要经过他们两次），**最后答案的费用$-2$**。

然后对于每一个边$(u,v)$，就变成了$(u+n,v)$

![](https://cdn.luogu.com.cn/upload/image_hosting/voszh3hg.png)

最后建立一个超级源点，向起点连一条流量为$2$，权值为$0$的边

再跑一遍最大费用最大流，输出费用$-2$就行了。

对于无解的情况，就判断流量是否达到$2$，如果没有就输出$1$。

# code：

```cpp
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define re register
#define ll long long
#define bool char
#define N 1000
#define M 10000
#define inf 0x3f3f3f3f

inline int read()
{
	char ch=getchar();
	int x=0,f=1;
	for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+ch-'0';
	return x*f;
}

struct ed{
	int to,next,f,w;
}edge[M+10];int tot=1,head[N+10];

inline void adde_double(int u,int v,int f,int w)
{
	edge[++tot].to=v;
	edge[tot].next=head[u];
	edge[tot].f=f;
	edge[tot].w=w;
	head[u]=tot;

	edge[++tot].to=u;
	edge[tot].next=head[v];
	edge[tot].f=0;
	edge[tot].w=-w;
	head[v]=tot;
}

queue<int>q;
int dis[N+10],cur[N+10],s,t;
bool vis[N+10];

inline bool spfa()
{
//	puts("spfa::");
	for(re int i=s;i<=t;++i)dis[i]=-inf;
	while(!q.empty())q.pop();
	memset(vis,0,sizeof(vis));
	for(re int i=s;i<=t;++i)cur[i]=head[i];
	dis[s]=0;q.push(s);
	int u,v;
	while(!q.empty())
	{
		u=q.front();q.pop();vis[u]=0;
//		printf("u==%d dis[u]==%d\n",u,dis[u]);system("pause");
		for(re int i=head[u];i;i=edge[i].next)
		{
			v=edge[i].to;
			if(edge[i].f&&dis[v]<dis[u]+edge[i].w)
			{
				dis[v]=dis[u]+edge[i].w;
				if(!vis[v])q.push(v),vis[v]=1;
			}
		}
	}
	return dis[t]>-inf;
}

int feiyong,maxflow;

inline int dfs(int now,int limit)
{
	if(!limit||now==t)
	{
		feiyong+=dis[now]*limit;
		return limit;
	}
	vis[now]=1;
	int flow=0,v,f;
	for(re int &i=cur[now];i;i=edge[i].next)
	{
		v=edge[i].to;
		if(edge[i].f&&dis[v]==dis[now]+edge[i].w&&!vis[v])
		{
			f=dfs(v,min(limit,edge[i].f));
			edge[i].f-=f;
			edge[i^1].f+=f;
			flow+=f;
			limit-=f;
			if(!limit)break;
		}
	}
	return flow;
}

inline void dinic()
{
	while(spfa())maxflow+=dfs(s,inf);
}

char pa[20];
int n,m;
map<string,int>mp;

inline void In(string &s)
{
	scanf(" %s",pa);
	int len=strlen(pa);
	s.clear();
	for(re int i=0;i<len;++i)s+=pa[i];
}

int main()
{
	n=read(),m=read();
	string S;
	for(re int i=1;i<=n;++i)
	{
		In(S);
		mp[S]=i;
		if(i==1)adde_double(i,i+n,2,1);
		else if(i==n)adde_double(i,i+n,2,1);
		else adde_double(i,i+n,1,1);
	}
	s=0,t=n*2+1;
	adde_double(s,1,2,0);
	adde_double(n+n,t,2,0);
	string s1,s2;
	for(re int i=1;i<=m;++i)
	{
		In(s1);In(s2);
		int u=mp[s1],v=mp[s2];
		if(u>v)swap(u,v);
		adde_double(u+n,v,inf,0);
	}
	dinic();
	if(maxflow<2)puts("1");
	else printf("%d\n",feiyong-2);//在费用流计算过程中，起点走两次，终点走两次，所以要-2 
	return 0;
}
```
还不懂的话可以私信我哦~~~

---

## 作者：姚文涛 (赞：0)

```cpp
//动态规划 
//把返回的路线反向，那么整条路线就变成了两条不相交的从起点到终点的路线。这样我们可以用DP解决。 
//状态设定：f[i，j] 为假定的甲乙两人，甲走到第i个城市，乙走到第j个城市时，两人走过的城市数目的和。 
//初始状态：f[1，1]=1。 
//状态转移方程：f[j，i]=f[i，j]=max{f[i，k]+1}(k到j存在飞机航线，以及f[i，k]>0，就是说存在f[i，k]的走法，1<=k
var n,m,i,j,ans,k:longint;
    c:char;
    s:string;
    city:array[1..100] of string;
    e:array[1..100,1..100] of boolean;
    f:array[1..100,1..100] of longint;
procedure getdata;
var i,j,x,y:longint;
begin
readln(n,m);
for i:=1 to n do readln(city[i]);
for i:=1 to m do
    begin
    s:='';
    read(c);
    while c<>' ' do
        begin
        s:=s+c;
        read(c);
        end;
    for j:=1 to n do
        if city[j]=s then begin x:=j;break;end;
    readln(s);
    for j:=1 to n do
        if city[j]=s then begin y:=j;break;end;
    e[x,y]:=true;
    e[y,x]:=true;
    end;
end;
begin
getdata;
f[1,1]:=1;
for i:=1 to n-1 do
    for j:=i+1 to n do
        begin
        for k:=1 to j-1 do
            if e[k,j] and (f[i,k]>0) and (f[i,k]+1>f[i,j]) then f[i,j]:=f[i,k]+1;
        f[j,i]:=f[i,j];
        end;
ans:=1;
for i:=1 to n-1 do
    if (e[i,n]) and (f[i,n]>ans) then ans:=f[i,n];
writeln(ans);
end.
```

---

