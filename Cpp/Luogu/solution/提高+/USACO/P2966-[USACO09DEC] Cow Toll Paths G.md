# [USACO09DEC] Cow Toll Paths G

## 题目描述

Like everyone else, FJ is always thinking up ways to increase his revenue. To this end, he has set up a series of tolls that the cows will pay when they traverse the cowpaths throughout the farm.

The cows move from any of the $N (1 \leq N \leq 250)$ pastures conveniently numbered $1...N$ to any other pasture over a set of $M (1 \leq M \leq 10,000) $bidirectional cowpaths that connect pairs of different pastures $A_j$ and $B_j (1 \leq A_j \leq N; 1 \leq B_j \leq N)$. FJ has assigned a toll $L_j (1 \leq L_j \leq 100,000)$ to the path connecting pastures $A_j$ and $B_j$.

While there may be multiple cowpaths connecting the same pair of pastures, a cowpath will never connect a pasture to itself. Best of all, a cow can always move from any one pasture to any other pasture by following some sequence of cowpaths.

In an act that can only be described as greedy, FJ has also assigned a toll $C_i (1 \leq C_i \leq 100,000)$ to every pasture. The cost of moving from one pasture to some different pasture is the sum of the tolls for each of the cowpaths that were traversed plus a **single additional toll** that is the maximum of all the pasture tolls encountered along the way, including the initial and destination pastures.

The patient cows wish to investigate their options. They want you to write a program that accepts $K (1 \leq K \leq 10,000)$ queries and outputs the minimum cost of trip specified by each query. Query $i$ is a pair of numbers $s_i$ and $t_i (1 \leq s_i \leq N; 1 \leq t_i \leq N; s_i \neq t_i)$ specifying a starting and ending pasture.

Consider this example diagram with five pastures:

The 'edge toll' for the path from pasture $1$ to pasture $2$ is $3$. Pasture $2$'s 'node toll' is $5$.

To travel from pasture $1$ to pasture $4$, traverse pastures $1$ to $3$ to $5$ to $4$. This incurs an edge toll of $2+1+1=4$ and a node toll of $4$ (since pasture $5$'s toll is greatest), for a total cost of $4+4=8$.

The best way to travel from pasture $2$ to pasture $3$ is to traverse pastures $2$ to $5$ to $3$. This incurs an edge toll of $3+1=4$ and a node toll of $5$, for a total cost of $4+5=9$.

给定一个 $n$ 点 $m$ 边的双向图，第 $i$ 条道路连接了 $u_i$ 与 $v_i$，边权为 $w_i$，第 $i$ 个点的点权为 $c_i$。

给定 $q$ 组询问，第 $i$ 组询问求从 $s_i$ 到 $t_i$ 的路径的边权之和与点权的最大值的和的最小值。

**可能有重边，但保证无自环。**

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 250$，$1 \le m \le 10^4$，$1 \le q \le 10^4$。

## 样例 #1

### 输入

```
5 7 2 
2 
5 
3 
3 
4 
1 2 3 
1 3 2 
2 5 3 
5 3 1 
5 4 1 
2 4 3 
3 4 4 
1 4 
2 3 
```

### 输出

```
8 
9 
```

# 题解

## 作者：一只书虫仔 (赞：41)

#### Description

> [P2966](https://www.luogu.com.cn/problem/P2966)     
> 给定一张图，求 $q$ 组询问，$s_i$ 到 $t_i$ 的边权之和与点权的最大值的和的最小值。

#### Solution

Floyd。

首先是对点权进行排序（记得要记原来的顺序，以便之后跑 floyd）。

然后邻接表存边，floyd 的经典操作。

然后就三重循环跑 floyd 即可，注意 $dist$ 是跑边权，$ans$ 是边权与点权。

我们用上 floyd 的转移公式：

$$dist_{i,j}=\min\{dist_{i,j},dist_{i,k}+dist_{k,j}\}$$

注意，这时候不能直接用 $i,j,k$，因为点权是排过序的，所以都要转变成 $c_i.dis$，$c_j.dis$，$c_k.dis$。

最后 $ans$ 的转移公式就很简单了，按照题目所说的：

$$ans_{i,j}=\min\{ans_{i,j},dist_{i,j}+\max\{c_i.val,c_j.val,c_k.val\}\}$$

跟上面 $dist$ 的转移公式一样，$i,j,k$ 还是要转变为 $c_i.dis$，$c_j.dis$，$c_k.dis$。

最后输出 $ans_{a,b}$ 即可。

注意：上面的 $dis$ 和 $val$ 代表的具体内容可以看下方的代码。

#### Code 1

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, q;
int ans[1005][1005], dist[1005][1005]; 
const int inf = 0x3f3f3f3f;

struct node {
	int val, dis;
} c[1005];

bool cmp (node x, node y) {
	return x.val < y.val;
}

int main () {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c[i].val);
		c[i].dis = i;
	}
	sort(c + 1, c + n + 1, cmp);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) 
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = inf;
	memset(ans, 0x3f, sizeof(ans));
	for (int i = 1, u, v, w; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		dist[u][v] = w;
		dist[v][u] = w;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				dist[c[i].dis][c[j].dis] = min(dist[c[i].dis][c[j].dis], dist[c[i].dis][c[k].dis] + dist[c[k].dis][c[j].dis]);
				ans[c[i].dis][c[j].dis] = min(ans[c[i].dis][c[j].dis], dist[c[i].dis][c[j].dis] + max(c[i].val, max(c[j].val, c[k].val)));
			}
	while (q--) {
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", ans[a][b]);
	}
	return 0;
}

```

预测得分：$50$ 分    
为什么只有 $50$ 分呢 …… 因为题目中说了可能要有重边   
所以我们要处理一下重边

#### Code 2

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, q;
int ans[1005][1005], dist[1005][1005]; 
const int inf = 0x3f3f3f3f;

struct node {
	int val, dis;
} c[1005];

bool cmp (node x, node y) {
	return x.val < y.val;
}

int main () {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c[i].val);
		c[i].dis = i;
	}
	sort(c + 1, c + n + 1, cmp);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) 
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = inf;
	memset(ans, 0x3f, sizeof(ans));
	for (int i = 1, u, v, w; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		dist[u][v] = min(dist[u][v], w);
		dist[v][u] = min(dist[v][u], w);
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				dist[c[i].dis][c[j].dis] = min(dist[c[i].dis][c[j].dis], dist[c[i].dis][c[k].dis] + dist[c[k].dis][c[j].dis]);
				ans[c[i].dis][c[j].dis] = min(ans[c[i].dis][c[j].dis], dist[c[i].dis][c[j].dis] + max(c[i].val, max(c[j].val, c[k].val)));
			}
	while (q--) {
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", ans[a][b]);
	}
	return 0;
}

```

预测得分：$100$ 分    
[AC Link!](https://www.luogu.com.cn/record/35264285)

By Shuchong    
2020.7.17

---

## 作者：Jouna_Kasa_Hasinele (赞：34)

首先，楼上几位讲的好像确实很玄学。。还有多跑几遍这种做法。。（一般好像是用来骗分的）

为了不使这个题变得很玄学，首先我们应当按点权排序。

之后当然是跑floyd，不过可以用两个数组计，d数组计不计点权的，dist数组计带点权的。（混在一块很难处理）

按点权从小到大的顺序枚举中转点，但两端不能只枚举到k，否则最短路会错。

由于k是从小到大枚举的，所以可以去最后的k作为i->j的路径上除i,j外点权的最大值，

但由于i,j从1到n枚举，所以再和i,j取max就是路径上最大的点权。

对于dist数组，加上点权取最大就好了，目测只要一趟floyd跑完。

下面贴上代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=255,INF=0x3f3f3f3f;
int n,m,q,u,v,w,s,t;
int rank[N],dist[N][N],d[N][N];
struct node
{
    int d;
    int id;
}nm[N];
bool cmp(node a,node b)
{
    if(a.d==b.d)
        return a.id<b.id;
    return a.d<b.d;
}
inline void get(int &a)//快读
{
    char c=getchar();
    a=0;
    for(;c<'0'||c>'9';c=getchar());
    a=c-'0';
    for(c=getchar();c>='0'&&c<='9';c=getchar())
        a=a*10+c-'0';
}
int main()
{
    get(n);get(m);get(q);
    for(int i=1;i<=n;i++)
    {
        get(nm[i].d);
        nm[i].id=i;
    }
    sort(nm+1,nm+1+n,cmp);//按点权排序
    for(int i=1;i<=n;i++)
        rank[nm[i].id]=i;//因为询问是用原始编号，这里存一下
    memset(d,0x3f,sizeof(d));
    for(int i=1;i<=n;i++)
        d[i][i]=0;
    for(int i=1;i<=m;i++)
    {
        get(u);get(v);get(w);
        d[rank[v]][rank[u]]=d[rank[u]][rank[v]]=min(d[rank[u]][rank[v]],w);
    }
    memset(dist,0x3f,sizeof(dist));
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(i==j)
                    continue;
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
                dist[i][j]=min(dist[i][j],d[i][j]+max(nm[k].d,max(nm[i].d,nm[j].d)));
            }
    while(q--)
    {
        get(s);get(t);
        printf("%d\n",dist[rank[s]][rank[t]]);
    }
    return 0;
}
```

---

## 作者：asuldb (赞：19)

很妙的一道题，我之前一直是用一个非常暴力的做法

就是枚举点权跑堆优化dijkstra

但是询问次数太多了

于是一直只有50分

今天终于~~抄~~做了这道题，不贴代码了，只说一下对这道题的理解

首先点权和边权不能混在一起，这是公认的，毕竟这个样子完全没有办法处理

那我们为什么要排序呢，发现其余几篇题解好像也没讲清楚

~~说得好像我能讲清楚一样~~

我们对于所有点按点权进行了一个排序，这一点很令人玩味，这是为什么呢

首先我们的floyd的枚举是长这个样子的

```cpp
for(re int k=1;k<=n;k++)
for(re int i=1;i<=n;i++)
for(re int j=1;j<=n;j++)
```

最外层枚举的$k$是枚举的什么

中转点啊

那我们排序完了之后说明什么

说明我们中转点加入的顺序是从小到大的

于是我们在找$i$,$j$之间的最短路的时候，我们的中转点如果只是枚举到了$k1$

那么这又说明了什么

这说明了我们当前的$i$,$j$之间的最短路中并没有点权超过$k1$的点

于是当前这条最短路上除去起点和终点点权最大的也就是$k1$了

那么我们就可以这样更新了

```cpp
dist[i][j]=min(dist[i][j],d[i][j]+max(nm[k].d,max(nm[i].d,nm[j].d)))
```

这是从楼下的那位大佬代码里抄来的

怎么说呢

我们当前的k越大，说明我们的最短路中可能的中转点越多，最短路也就越短（尽管可能随着$k$增大最短路并不会变短，而是不变），但是同时我们加入的中转点的点权也越来越大

也就是说我们每次新加入一个中转点，可能最短路是变短了，但是我们的点权最大值也增加了，这个时候就要与前面的dist值取一个最小了

于是代码就不贴了

---

## 作者：于丰林 (赞：12)

 [USACO09DEC]牛收费路径Cow Toll Paths

题目大意：给定一个无向图，求出一条路径，使得边权和加上点权和最小，多组询问

n<=250 m<=10000

多组询问，数据范围这么小，很显然就是floyd了，但是这个点权着实让人讨厌哇。。。

我们重新回想一遍floyd算法的原理：i到j有两种可能：直接到和借助中间接口k，所以取一个min就行了

我们再往下细细的想一下，k代表的是中间的接口，而且k的枚举顺序是任意的？

显然是任意的！突破口就在这：我们可以肆意的修改k的枚举顺序！

所以，这道题就解决了，我们只要从小到大枚举k，跑flyod，点权最大值利用min(c[i],c[j],c[k])来维护就行了！

正确性？

当我们枚举到一个k的时候，就代表路径中除了i，j以外没有任何数可能比k大，所以我们在三个中取一个min就行了

时间复杂度:O(n^3)

注意处理细节：例如枚举后顺序改变等

最后，附上本题代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<iostream>
using namespace std;
//Debug Yufenglin
#define dej printf("Running\n");
#define dep1(x) cout<<#x<<"="<<x<<endl;
#define dep2(x,y) cout<<#x<<"="<<x<<' '<<#y<<"="<<y<<endl;
#define dep3(x,y,z) cout<<#x<<"="<<x<<' '<<#y<<"="<<y<<' '<<#z<<"="<<z<<endl;

//Standfor Yufenglin
#define LL long long
#define LB long double
#define reg register
#define il inline
#define inf 1000000000
#define maxn 250
#define maxm 1005

struct pot
{
    int v,id;
};
int n,m,q;
pot c[maxn+5];
int dis[maxn+5][maxn+5],f[maxn+5][maxn+5],pre[maxn+5];

bool cmp(pot x,pot y)
{
    if(x.v==y.v) return x.id<y.id;
    return x.v<y.v;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&c[i].v);
        c[i].id=i;
    }
    sort(c+1,c+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        pre[c[i].id]=i;
    }
    memset(dis,0x1f,sizeof(dis));
    memset(f,0x1f,sizeof(f));
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        dis[pre[x]][pre[y]]=dis[pre[y]][pre[x]]=min(dis[pre[x]][pre[y]],z);
    }
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(i==j) continue;
                dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
                f[i][j]=min(f[i][j],dis[i][j]+max(c[i].v,max(c[j].v,c[k].v)));
            }
        }
    }
    for(int i=1;i<=q;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",f[pre[x]][pre[y]]);
    }
    return 0;
}
```


---

## 作者：ywy_c_asm (赞：11)

这里提供另一种空间复杂度$O(n^3)$的$Floyd$思路。

看到这题我们可以有一个思路，就是如果我们钦定最短路上点权最大的点，那么我们只需要考虑最短路即可，然后我们很自然的就可以想到$Floyd$，我们知道$Floyd$实质上是一个使用滚动数组的$dp$，即$dp[i][j][k]$为经过$[1,k]$的中转点（注意不一定包括$i,j$）的$i->j$的最短路，那么我们可以把这个中转点从小到大排序，不让这个$dp$数组滚动，就达到了钦定最大的中转点的效果，我们只需把最短路加上$a_k$即可——吗？这里要注意的是中转点是不包括$i,j$的，所以应该加上$max(a_i,a_j,a_k)$。

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int get() {//我的垃圾快读 
	int n=0;
	char c;
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')break;
		if(c=='-')goto s;
	}
	n=c-'0';
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
	}
s:
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')n=n*10-c+'0';
		else return(n);
	}
}
void print(int num) {
	if(num>=10)print(num/10);
	putchar(num%10+'0');
}
int G[251][251][251];//不滚动的dp数组 
typedef struct _n {//用于排序的结构体 
	int pt;
	int v;
	friend bool operator <(const _n &a,const _n &b) {
		return(a.v<b.v);
	}
} node;
node memchi[251];
int ref[251];
int main() {
	memset(G,0x3f,sizeof(G));
	int n=get(),m=get(),q=get();
	for(register int i=1; i<=n; i++) {
		memchi[i].pt=i;
		memchi[i].v=get();
		G[i][i][0]=0;
	}
	sort(memchi+1,memchi+1+n);
	for(register int i=1; i<=n; i++)ref[memchi[i].pt]=i;
	for(register int i=1; i<=m; i++) {
		int s=ref[get()],t=ref[get()],l=get();
		G[s][t][0]=min(G[s][t][0],l);
		G[t][s][0]=G[s][t][0];
	}
	for(register int k=1; k<=n; k++) {//Floyd 
		for(register int i=1; i<=n; i++) {
			for(register int j=1; j<=n; j++) {
				G[i][j][k]=min(G[i][j][k],G[i][k][k-1]+G[k][j][k-1]);
				G[i][j][k]=min(G[i][j][k],G[i][j][k-1]);
			}
		}
	}
	while(q) {
		q--;
		int s=ref[get()],t=ref[get()];
		int minn=0x7f7f7f7f;
		for(register int i=1; i<=n; i++) {//枚举最大中转点 
			minn=min(minn,G[s][t][i]+max(max(memchi[s].v,memchi[t].v),memchi[i].v));
		}
		print(minn);
		putchar('\n');
	}
	return(0);
}
```

---

## 作者：Zjl37 (赞：10)

[题面传送门](https://www.luogu.com.cn/problem/P2966)   
我的第一篇题解，有不对的地方请指正。
### 本篇题解的目的
- 这题使我陷入了多个误区，花了很久的时间，值得用我的第一篇题解来纪念。同时练习 Markdown 与 Latex 。
- 不像其他题解所说的，“点权和边权不能混在一起”，其实是有办法处理的。
- “为什么要对中转点按点权从小到大排序”其他题解讲的似乎不是很清楚。 ~~说得好像我能讲清楚一样~~   

### 思路
注意到数据范围：$ N \leq 250 $，$K \leq 10000 $。点数较小，询问数较多，可以使用 Floyd 算法将每对草地间的距离算出来。   
设路径 i -> j 的费用（同题意）为 $ f(i,j) $，那么每次询问回答的答案就是 $ f(s,t) $。由于路径中包含一个最大的草地过路费（点权），我们还需要记费用最少的 i -> j 路径上，最大的点权为 $ pm(i,j) $（包括 i, j ）。   
考虑路径 i -> h -> j，怎么通过中转点 h 更新 $ f(i,j) $ 呢？可以知道路径上最大的点权为 $ \max(pm(i,h),pm(h,j)) $。先在两边路径的费用中减去最大的点权并求和，然后加上连起来路径上最大点权，得到新路径   
$ l=f(i,h)+f(h,j)-pm(i,h)-pm(h,j)+\max(pm(i,h),pm(h,j)) $
如果 l 比 $ f(i,j) $ 小，则更新 f 和 pm。   
初始化：如果存在一条道路 (a, b) 过路费为 l，那么路径 a -> b 上的最大点权为 $ \max(c_a,c_b) $，费用为 l 加上最大点权。
### 代码（WA，30分）

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,k,c[251],a,b,l,s,t,f[251][251],pm[251][251];
// 变量的含义与题目或题解中的相同

int main() {
	scanf("%d%d%d",&n,&m,&k);
	memset(f,0x3f,sizeof f);
	// 将 f 数组所有值初始化为0x3f3f3f3f，使得它近似无穷大，而两个这样大的数相加后又不会超过 int 范围 
	// 读入所有点权
	for(int i=1; i<=n; i++)
		scanf("%d",&c[i]);
	// 读入所有道路及其过路费（边权）并初始化
	for(int i=1; i<=m; i++) {
		scanf("%d%d%d",&a,&b,&l);
		pm[b][a]=pm[a][b]=max(c[a],c[b]);
		f[b][a]=f[a][b]=min(f[a][b],l+pm[a][b]);
		// 注意会有重边。我在这里卡了很久，也是看了其他题解才改过来的。有重边时要取边权最小的边。
	}
	// 下面是 Floyd 算法
	for(int h=1; h<=n; h++) // 枚举中转点
		for(int j=1; j<=n; j++)
			if(j!=h) for(int i=1; i<=n; i++) {
				if(i==j||i==h) continue;
				l=f[j][h] + f[h][i] - pm[j][h] - pm[h][i] + max(pm[j][h],pm[h][i]);
				if(l<=f[j][i])
					f[j][i]=l,
					pm[j][i]=max(pm[j][h],pm[h][i]);
			}
	// 读入每个询问并回答 
	for(int i=1; i<=k; i++) {
		scanf("%d%d",&s,&t);
		printf("%d\n",f[s][t]);
	}
	return 0;
}
```

### 改进
然而会发现这样的代码只有30分。  
参考其他大佬的题解，发现需要对中转点 _按点权_ **从小到大**排序。  
由于我 ~~懒，~~ 希望改动最少，于是   
- 用优先队列来确定中转点的顺序。在 main 函数前面加入如下代码：
```cpp
typedef pair<int,int> node; // first: c, second: i
// STL之pair真好用。使用时建议将first，second代表的意义记录在旁边以免忘记。
priority_queue<node,vector<node>,greater<node> > q;
```
- 读入每点点权时顺便将其加入优先队列。
```
		q.push(node(c[i],i));
```
- 将枚举中转点的循环改为如下while循环，并将接下来枚举 j 的循环放入```*|*```处

```cpp
	while(!q.empty()) {
		int h=q.top().second; q.pop();
		*|*
	}

```

### 疑问
为什么要对中转点 _按点权_ **从小到大**排序？为了帮助理解这个问题，我设法画出了这幅图：
[![](https://cdn.luogu.com.cn/upload/image_hosting/3w7tlhjx.png)](https://www.luogu.com.cn/paste/kpeywhum)   
转折点按点权从小到大遍历：   
通过h=3（点权为3），$ f(1,2)=7+8=15,\;f(1,4)=14+6=20 $   
通过h=2（点权为8），$ f(1,4)=f(1,2)+11-8-8+8=18 $   
转折点从1到n：   
通过h=2，$ l=8+4=12>11=3+8=f(3,4) $ 于是不通过 2；   
通过h=3，$ f(1,4)=f(1,3)-6+f(3,4)-3+6=20 $   
30分代码：？？？   

---
其他题解有的说玄学，多跑几遍就过了；有的解释了方便性（这样就能知道一条路径的最大点权是三个点的max）。目前我也不能严谨地说清楚它的正确性，于是去看了[USACO官网的Analysis](https://contest.usaco.org/TESTDATA/DEC09.toll.htm)。大意是，因为总费用分为边权和和最大点权，不妨先限定点权为某一特定值，求经过所有点的点权不超过一特定值的最优路径的费用。对于所有N个顶点，可以每次用 $O(n^3)$ 的算法求经过所有的点不超过该顶点权值的最优路径，然后取得到的N个费用的最小值作为答案。   
然而这样的算法时间复杂度为 $O(n^4)$，可以在 Floyd 的基础上优化。因为 Floyd 的是基于中转点的松弛操作的，算法算到中途时，每对点的费用就是只通过那些已枚举过的中转点的路径的最小费用。因此将中转的顺序按点权排序后，与上面的算法效果等同：第i次循环算出了每对点只经过那些点权不超过 _点权第i小的点_ 的点的路径的最小费用。（以上为翻译）   
值得注意的是，Floyd 算法是基于动态规划的思想的，数组 $ f(i,j) $ 隐藏了中转点（动规阶段）那一维，变为了滚动数组。如果不排序，那么这一维度是否还有意义？违背了动态规划的哪条适用条件？使30分代码不通过的某些图的共同性质能否用一些不等式关系描述？可以试着从这些角度否定30分的代码。然而我太菜了，想了一整天也想不出怎样严谨地说明这个的正确性，那个的错误。If someone could give me better explanations, I would appreciate it very much.

---

## 作者：逃课小姐MS (赞：6)

居然发现没有人写dijkstra的算法过这个题

那我这个水过的蒟蒻就来讲讲dijkstra怎么做

如果不会dijkstra 请先进[这个题](https://www.luogu.org/problemnew/show/P3371)进行学习qwq

这个思路比较清奇

首先 我们这个题目中有个坑点 就是说 每一次要加上走过路径之中点权最大的点

其实很好想的就是每一次处理的时候存一下最大点权 然后就发现 不是TLE即MLE

------------


然后 我们就有了这个思路：

1 一重循环k 表示当前我们这条路上的最大点权 即所有可经过点的点权≤点k的权值

2 在循环k里面做dijkstra 注意经过的点只能是点权≤k点的 不然就错了

3 在更新完dist后 计算答案 计算式要加上k点的点权

这样一分析 时间复杂度Θ（$n^3$)   **美妙**~~卡过~~

------------


最后来上一发代码（~~要抄~~也得先**理解思路**）
```cpp
//这里写一笔 我的标程没有写链式前向星 用的是邻接矩阵
#include<bits/stdc++.h>
using namespace std;
// n,m,query 就是n,m,k
// p代表点的权值 maze是邻接矩阵 dist是处理出来的某个点到所有点的最小值(dijkstra) vis标记 ans不必多说 储存答案 
int n,m,query;
int p[260],maze[260][260],dist[260],ans[260][260],vis[260]; 
void dijkstra(int k){
//当然 数组不清空 交题见祖宗 
    memset(vis,0,sizeof(vis));
    memset(dist,0x3f,sizeof(dist));
    //以下是disjktra正常操作 
    dist[k]=0; 
    for(int i=1;i<=n;i++){
        int v=-1;
        /*看到这里你可能会奇怪 (p[u]<=p[k]) 什么鬼
	其实很好理解的 我把我每一次做dijkstra的点拉出来 做为当前的最大点权 那当然不可以进入比最大点权权值还要大的点了 */ 
        for(int u=1;u<=n;u++) if(((dist[u]<dist[v])||(v==-1))&&(p[u]<=p[k])&&(!vis[u])) v=u;
        if(v==-1) break;
        vis[v]=true;
        //其实这里(p[u]>p[k])跟上面那个一样的 然后就dijkstra正常走一波 
        for(int u=1;u<=n;u++){
            if(p[u]>p[k]) continue;
            dist[u]=min(dist[u],dist[v]+maze[v][u]);
        }
    }
}
int main(){
	//清空赋值读入 这里就不多讲了
    memset(ans,0x3f,sizeof(ans));
    memset(maze,0x3f,sizeof(maze));
    cin>>n>>m>>query;
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        maze[a][b]=maze[b][a]=min(maze[a][b],c);
    }
    //这里的k代表的是当前我选中的点 这个点代表了当前的最大点权 即在本次我dijkstra中选出可用的点的点权不可以有大于它的 
    for(int k=1;k<=n;k++){
        dijkstra(k);//进函数
		//下面是计算ans 这里计算ans是由选出的最大点权的点到任意两个点的距离 别忘了加上最大点权 
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                ans[i][j]=min(ans[i][j],dist[i]+dist[j]+p[k]);
    }
    //对于每一次询问 我们处理出它的答案:) 
    for(int i=1;i<=query;i++){
        int a,b;
        cin>>a>>b;
        cout<<ans[a][b]<<endl;
    }
    return 0;
}
```

---

## 作者：Space_Gold_Trash (赞：4)

用floyed跑几遍的做法很玄学，我的思路和那个一样

为了让它变得不再玄学,我便附上了自己的想法：为什么多跑几遍就对了

AC代码:
```
#include<bits/stdc++.h>
using namespace std;
const int INF=20040915;
int n,m,Q;
int d[250][250],w[250][250];
int main(){
	scanf("%d%d%d",&n,&m,&Q);
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			d[i][j]=d[j][i]=w[i][j]=w[j][i]=INF;
		}
		d[i][i]=0;
	}
	for(register int i=1;i<=n;i++) scanf("%d",&w[i][i]);
	for(register int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		d[x][y]=d[y][x]=min(d[x][y],z);
		w[x][y]=w[y][x]=max(w[x][x],w[y][y]);
	}
	bool op=1;
	while(op){
		op=0;
		for(register int k=1;k<=n;k++){
			for(register int i=1;i<=n;i++){
				for(register int j=1;j<=n;j++){
					if(d[i][j]+w[i][j]>d[i][k]+d[k][j]+max(w[i][k],w[k][j])){
						d[j][i]=d[i][j]=d[i][k]+d[k][j];
						w[i][j]=w[j][i]=max(w[i][k],w[k][j]);
						op=1;
					}
				}
			}
		}
	}
	while(Q--){
		int s,t;
		scanf("%d%d",&s,&t);
		printf("%d\n",d[s][t]+w[s][t]);
	}
	return 0;
}
```
这就是AC代码，如果进行了松弛操作，那么就继续跑floyed

否则就退出了

那么证明一次loyed是不一定能找到它的最优解的

那么为什么呢？

原因肯定在这点权上面

而至于找到具体什么使floyed无法一次找到它的最优解，就等下一位大佬来吧



---

## 作者：attack (赞：3)

给大家介绍一种不用排序就能AC的方法

（排序的方法请看这位大神的博客：http://www.cnblogs.com/peter-le/p/6014643.html）


我们可以分别记录下从点x到点y 的最短路径的长度和在最短路上的花费

然后就是套Floyd的模板。

但是注意，因为你的长度和花费是分开记录的

所以一遍Floyd跑出来的不一定是最小值

我们可以多跑几遍试试

    
            
    


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN=251;
const int maxn=0x7ffffff;
void read(int & n)
{
    char c='+';int x=0;    
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')
    {
        x=x*10+c-48;
        c=getchar();
    }
    n=x;
}
int a[MAXN][MAXN];
int spend[MAXN][MAXN];
int b[MAXN];
int n,m,q;
void floyd()
{
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                int p=a[i][k]+a[k][j]+max(spend[i][k],spend[k][j]);
                if((p<a[i][j]+spend[i][j])&&a[i][k]<maxn&&a[k][j]<maxn)
                {
                    //a[i][j]=a[i][j]-max(spend[i],spend[j]);
                    a[i][j]=a[i][k]+a[k][j];
                    spend[i][j]=max(spend[i][k],spend[k][j]);
                }            
            }
}
int main()
{
    read(n);read(m);read(q);
    for(int i=1;i<=n;i++)
        read(b[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==j)
            a[i][j]=0;
            else
            a[i][j]=maxn;
        }
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        read(x);read(y);read(z);
        if(a[x][y]>z)
        {
            a[x][y]=z;
            a[y][x]=z;
            spend[x][y]=max(b[x],b[y]);
            spend[y][x]=max(b[x],b[y]);
        }
    }
    floyd();
    floyd();
    floyd();            
    for(int i=1;i<=q;i++)
    {
        int x,y;
        read(x);read(y);
        printf("%d\n",a[x][y]+spend[x][y]);
    }
    return 0;
}

```

---

## 作者：Provicy (赞：2)

一道适合初学者的图论题

题目意思就是求一条路径上的边权和$+$点权最大值 的最小值。看到$n$的范围并不大，其实我们可以考虑用$Floyd$来做。

因为我们最终求的是最小值，所以我们考虑将点权进行排序，这样可以保证最终答案一定是最小值。

 故我们一边跑最短路，一边在最短路上加上当前$i,j,k$三个点中点权最大的，每次更新在$dis[i][j]$中即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=510;
ll n,m,Q,dis[N][N],cro[N],to[N][N];
struct Edge{ll c,id;}pro[N];
inline ll read()
{
    ll s=0,w=1;char ch;ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
bool cp(Edge a,Edge b){return a.c==b.c?a.id<b.id:a.c<b.c;}
int main()
{
    scanf("%lld%lld%lld",&n,&m,&Q);
    for(ll i=1;i<=n;i++) scanf("%lld",&pro[i].c),pro[i].id=i; 
    sort(pro+1,pro+1+n,cp);
    for(ll i=1;i<=n;i++) cro[pro[i].id]=i;
    for(ll i=1;i<=n;i++) for(ll j=1;j<=n;j++) dis[i][j]=to[i][j]=1e11;
    for(ll i=1;i<=n;i++) to[i][i]=0;
    for(ll i=1,x,y,z;i<=m;i++) 
    {
        scanf("%lld%lld%lld",&x,&y,&z);
        x=cro[x];y=cro[y];
        to[x][y]=min(to[x][y],z);to[y][x]=to[x][y];
    }
    for(ll k=1;k<=n;k++) 
        for(ll i=1;i<=n;i++) 
            for(ll j=1;j<=n;j++) 
            {
                to[i][j]=min(to[i][j],to[i][k]+to[k][j]);
                dis[i][j]=min(to[i][j]+max(pro[i].c,max(pro[j].c,pro[k].c)),dis[i][j]);
            }
    for(ll i=1,ax,ay;i<=Q;i++) 
    {
        scanf("%lld%lld",&ax,&ay);
        ax=cro[ax];ay=cro[ay];
        printf("%lld\n",dis[ax][ay]);
    }
    return 0;
}
```


---

## 作者：僚机 (赞：2)

玄学。。。

每个a[i][j]存的是i到 j所需路径最大花费数 加上最大点的花费

然后不知道为什么要多跑几次floyd。。

注意！！！一直卡在五十分！！！

他会有重边。。。。判一下



        
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int INF=10086110;
int w[255];
int a[255][255];
int maxn[255][255];
int n,m,k;
int readin(){
    int yi=0;
    char c=getchar();
    while(!isdigit(c)){
        c=getchar();
    }
    for(;isdigit(c);c=getchar()){
        yi=yi*10+c-'0';
    }
    return yi;
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        w[i]=readin();
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            a[i][j]=INF;
        }
    }
    for(int i=1;i<=m;i++){
        int xi=readin(),yi=readin(),zi=readin();
        if(a[xi][yi]>zi+max(w[xi],w[yi])){
            a[xi][yi]=zi+max(w[xi],w[yi]);
            a[yi][xi]=zi+max(w[xi],w[yi]);
            maxn[xi][yi]=max(w[xi],w[yi]);
            maxn[yi][xi]=max(w[xi],w[yi]);
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j||j==k||i==k) continue;
                if(a[i][j]>a[i][k]+a[k][j]-min(maxn[i][k],maxn[k][j])){
                    a[i][j]=a[i][k]+a[k][j]-min(maxn[i][k],maxn[k][j]);
                    maxn[i][j]=max(maxn[i][k],maxn[k][j]);
                }
            }
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j||j==k||i==k) continue;
                if(a[i][j]>a[i][k]+a[k][j]-min(maxn[i][k],maxn[k][j])){
                    a[i][j]=a[i][k]+a[k][j]-min(maxn[i][k],maxn[k][j]);
                    maxn[i][j]=max(maxn[i][k],maxn[k][j]);
                }
            }
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j||j==k||i==k) continue;
                if(a[i][j]>a[i][k]+a[k][j]-min(maxn[i][k],maxn[k][j])){
                    a[i][j]=a[i][k]+a[k][j]-min(maxn[i][k],maxn[k][j]);
                    maxn[i][j]=max(maxn[i][k],maxn[k][j]);
                }
            }
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j||j==k||i==k) continue;
                if(a[i][j]>a[i][k]+a[k][j]-min(maxn[i][k],maxn[k][j])){
                    a[i][j]=a[i][k]+a[k][j]-min(maxn[i][k],maxn[k][j]);
                    maxn[i][j]=max(maxn[i][k],maxn[k][j]);
                }
            }
        }
    }
    for(int i=1;i<=k;i++){
        int ai=readin();
        int bi=readin();
        printf("%d\n",a[ai][bi]);
    }
    return 0;
}
```

---

