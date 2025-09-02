# [USACO08NOV] Cheering up the Cow G

## 题目描述

Farmer John has grown so lazy that he no longer wants to continue maintaining the cow paths that currently provide a way to visit each of his N (5 <= N <= 10,000) pastures (conveniently numbered 1..N). Each and every pasture is home to one cow. FJ plans to remove as many of the P (N-1 <= P <= 100,000) paths as possible while keeping the pastures connected. You must determine which N-1 paths to keep.

Bidirectional path j connects pastures S\_j and E\_j (1 <= S\_j <= N; 1 <= E\_j <= N; S\_j != E\_j) and requires L\_j (0 <= L\_j <= 1,000) time to traverse. No pair of pastures is directly connected by more than one path.

The cows are sad that their transportation system is being reduced. You must visit each cow at least once every day to cheer her up. Every time you visit pasture i (even if you're just traveling

through), you must talk to the cow for time C\_i (1 <= C\_i <= 1,000).

You will spend each night in the same pasture (which you will choose) until the cows have recovered from their sadness. You will end up talking to the cow in the sleeping pasture at least in the morning when you wake up and in the evening after you have returned to sleep.

Assuming that Farmer John follows your suggestions of which paths to keep and you pick the optimal pasture to sleep in, determine the minimal amount of time it will take you to visit each cow at least once in a day.

For your first 10 submissions, you will be provided with the results of running your program on a part of the actual test data.

POINTS: 300

约翰有N个牧场，编号依次为1到N。每个牧场里住着一头奶牛。连接这些牧场的有P条道路，每条道路都是双向的。第j条道路连接的是牧场Sj和Ej，通行需要Lj的时间。两牧场之间最多只有一条道路。约翰打算在保持各牧场连通的情况下去掉尽量多的道路。 

约翰知道，在道路被强拆后，奶牛会非常伤心，所以他计划拆除道路之后就去忽悠她们。约翰可以选择从任意一个牧场出发开始他维稳工作。当他走访完所有的奶牛之后，还要回到他的出发地。每次路过牧场i的时候，他必须花Ci的时间和奶牛交谈，即使之前已经做过工作了，也要留下来再谈一次。注意约翰在出发和回去的时候，都要和出发地的奶牛谈一次话。请你计算一下，约翰要拆除哪些道路，才能让忽悠奶牛的时间变得最少？


## 说明/提示

```cpp
   +-(15)-+ 
  /        \ 
 /          \ 
1-(5)-2-(5)-3-(6)--5 
   \   /(17)  / 
(12)\ /      /(12) 
     4------+ 

Keep these paths: 
1-(5)-2-(5)-3      5 
       \          / 
    (12)\        /(12) 
        *4------+ 
```
Wake up in pasture 4 and visit pastures in the order 4, 5, 4, 2, 3, 2, 1, 2, 4 yielding a total time of 176 before going back to sleep.


## 样例 #1

### 输入

```
5 7 
10 
10 
20 
6 
30 
1 2 5 
2 3 5 
2 4 12 
3 4 17 
2 5 15 
3 5 6 
4 5 12 
```

### 输出

```
176 
```

# 题解

## 作者：qwqKanade (赞：35)

此题明显是最小生成树的模板题...

kruskal算法...

值得注意的一点是：与奶牛谈话也需要时间，而且每条路都需要来回走两遍。

所以每条边的权值为：起点权值+终点权值+路的长度\*2.

然后就能直接跑最小生成树了......

PS：别忘了加上权值最小的点哦


下面粘上蒟蒻的丑陋代码...


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10001];
struct edge
{
    int l,r,v;
}
e[100001];
int f[10001];
bool cmp(edge a,edge b)
{
    return a.v<b.v;
}
int n,ans;
int find(int n)
{
    if(f[n]==n)
    {
        return n;
    }
    f[n]=find(f[n]);
    return f[n];
}
void bing(int m,int n)
{
    int x,y;
    x=find(m);
    y=find(n);
    f[x]=y;
}
int main()
{
    int p,num=0,road=0,s=0x7fffffff;
    scanf("%d%d",&n,&p);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s=min(s,a[i]);
    }
    for(int i=1;i<=p;i++)
    {
        num++;
        scanf("%d%d%d",&e[num].l,&e[num].r,&e[num].v);
        e[num].v=e[num].v*2+a[e[num].l]+a[e[num].r];   //改变边权
    }
    sort(e+1,e+num+1,cmp);
    for(int i=1;i<=n;i++)
    {
        f[i]=i;
    }
    for(int i=1;road<n-1;i++)    //最小生成树
    {
        if(find(e[i].l)!=find(e[i].r))
        {
            ans+=e[i].v;
            bing(e[i].l,e[i].r);
            road++;
        }
    }
    printf("%d",ans+s);
    return 0;
}
```

---

## 作者：nao_nao (赞：13)

[这道题](https://www.luogu.com.cn/problem/P2916)解法：最小生成树，也就是使用 Kruskal 算法。

### 题意：
题目会给出一张连通图，首先需要我们生成一棵树，然后选取一个点作为出发点，设计一条路径遍历所有的点，并按要求计算最小的可能答案。

### 分析：
我们发现题目并没有告诉我们生成树的规则，全部枚举显然也不现实，因此我们可以从答案统计方法上来入手。

答案中包括了点权与边权，每一个点对于答案的贡献并不能很显然的确定，因为可能会经过一个点多次。我们可以从边入手，路线可以看成一个**首尾相接的环**，通过把玩样例可以发现生成树上的每一条边都被经过了恰好两次,并且发现起始点的选择并不会影响路径，因此我们可以把答案分为两部分，即为 **起始点点权** 与 **路径环上的点权边权和** 。 _（注意 : 这里所说的“路径环上的点权边权”并不是单纯的相加）_

经过进一步的观察与思考，我们发现**一个点被重复经过的次数恰好与它在生成树中的度数相等**。我们考虑， Kruskal 算法是通过对边权的排序来求取最小生成树，此题要求最小的答案，也可以通过某种手段将它也转化成最小生成树来求解，因此，我们需要找到某种方法来将点权来转化到边权上。

根据：“**一个点被重复经过的次数恰好与它在生成树中的度数相等**”，我们可以将点权安排到与之相邻的边上。

现在来整理一下要求的内容。“**起始点点权**最小”，我们可以贪心选点权最小的点作为起始点。“**路径环上的点权边权和**最小”，我们可以将边权赋值为原边权的二倍与两个端点点权的和，然后跑一遍 Kruskal 求出最小值。

code：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=2e5+7;
int n,m,arr[N];
struct node{
	int u,v,dis;
	friend bool operator < (node a,node b)
	{
		return a.dis < b.dis;
	}
}edge[N];
int fa[N];
int find(int s)//并查集 
{
	if(fa[s] == s) return s;
	return fa[s] = find(fa[s]);
}
int main()
{
	int mini = 2147483647;
	scanf("%d %d",&n,&m);
	for(int i = 1;i <= n;i ++){
		scanf("%d",&arr[i]);
		mini = min(mini,arr[i]);//读入时顺便选一下起始点 
	}
	for(int i = 1;i <= m;i ++){
		scanf("%d %d %d",&edge[i].u,&edge[i].v,&edge[i].dis);
		//处理边权 
		edge[i].dis += edge[i].dis + arr[edge[i].u] + arr[edge[i].v];
	}
	sort(edge+1,edge+1+m);
	int sum = n-1,ans = 0;
	for(int i = 1;i <= n;i ++) fa[i] = i;
	
	//Kruskal
	for(int i = 1;i <= m&&sum;i ++){
		if(find(edge[i].u) != find(edge[i].v)){
			sum --;
			fa[find(edge[i].u)] = find(edge[i].v);
			ans += edge[i].dis;
		//	printf("connect %d and %d,it cost %d\n",edge[i].u,edge[i].v,edge[i].dis);
		}
	}
	printf("%d",ans + mini);
	return 0;
}
```


---

## 作者：x_miracle (赞：11)

**核心算法：Kruskal**

题目中说：“删去尽可能多的边”。就是指保留一棵最小生成树。

------------

 **构图**：

我们取一小段来分析一下：

（可以把这个理解为**单位元**）

![a8CtXQ.png](https://s1.ax1x.com/2020/08/01/a8CtXQ.png)

按照题目中的意思，走过该图的花费为：

C[1] + L + C[2] + L + C[1]

即：C[1] + C[1] + 2L + C[2]

![a89RFP.png](https://s1.ax1x.com/2020/08/01/a89RFP.png)

走过该图的花费为：

C[1] + L(1,2) + C[2] + L(2,3) + C[3] + L(2,3) + C[2] + L(1,2) + C[1]

即：C[1] + （C[1] + 2L(1,2) + C[2]） + （C[2] + 2L(2,3) + C[3]）

所以，我们可以推出：新的边的权值，为这条边  **起点权值+终点权值+两倍边权**

 **而最后的结果，还要加上一开始起点权值。** （即取点权中的最小值，因为题目中要求最小）

代码如下（细节见注释）：
```cpp
#include <bits/stdc++.h>
#define MAXN 1000000
#define INF 0x3f3f3f3f
int fat[MAXN],siz[MAXN];
int c[MAXN],n,m,ans=0;
struct EDGE{int from,to,val;}	e[MAXN];
//邻接矩阵 
bool cmp(EDGE x,EDGE y){return x.val<y.val;}
//比较器  按照边的权值排序 
int Find(int x)	{return (fat[x]==x) ? x :fat[x]=Find(fat[x]);}
void unionn (int x,int y)
{
	x=Find(x); y=Find(y);
	if(siz[x]>siz[y]) std::swap(x,y);
	fat[x]=y;	siz[y]+=siz[x];
}
//并查集模板 
bool kruskal()
{
	int k=0;
	std::sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;++i)
	{
		if(k==n-1)	break;
		if(Find(e[i].to)!=Find(e[i].from))
		{
			unionn(e[i].to,e[i].from);
			++k;	ans+=e[i].val;
		}
	}
	return (k==n-1);
}
// kruskal模板 
int main()
{
	int minn=INF;
	std::scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)	{fat[i]=i;	siz[i]=1;}
	//并查集初始化  
	for(int i=1;i<=n;++i)
	{
		std::scanf("%d",&c[i]);
		minn=std::min(minn,c[i]);
		//点权值中取最小值 
	}
	for(int i=1;i<=m;++i)
	{
		std::scanf("%d%d%d",&e[i].from,&e[i].to,&e[i].val);
		e[i].val=e[i].val*2+c[e[i].from]+c[e[i].to];
		//重新定义权值 
	}
	if(kruskal()) std::printf("%d",ans+minn);
	return 0;
}
```

---

## 作者：Hiraeth (赞：7)

解题报告：

求经过所有节点所花费的最小代价.

考虑最小生成树求解.

来看一下题目：

1.当他走访完所有的奶牛之后，还要回到他的出发地.

2.注意约翰在出发和回去的时候，都要和出发地的奶牛谈一次话.

先看一下这一句：

### 注意约翰在出发和回去的时候，都要和出发地的奶牛谈一次话.

那么是不是就是每条边都是被遍历两次呢 并且每一次计算的时候都要加上起点的权值

举个例子说明一下：

有一条边 a->b 那么假定我们从a点出发再回到a点 先从a点出发 加上a点权值和边权 在从b回到a 加上b点权值和边权 那么对于每一条边 他的边权是不是就等于边权$*2$+起点的终点的边权呢？

那么我们就把每一条边的边权更新一下

```cpp
	a[i].z=z*2+t[x]+t[y]; 
```

再来注意一下另外一句话：

### 当他走访完所有的奶牛之后，还要回到他的出发地.

代表着我们还要加上出发点的权值 对于一个给定的图 它的最小生成树的是一定的 那么我们只要加上最小的出发点即可

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,z,ans=0x3f,px,py,f[100005],t[100005];
struct p{
	int x,y,z;
}a[200005];
bool cmp(p a,p b){
	return a.z<b.z;
} 
int find(int x){
	if (x==f[x]) return x;
	return f[x]=find(f[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) f[i]=i;
	for (int i=1;i<=n;i++) {
		scanf("%d",&t[i]);
		ans=min(ans,t[i]);
	}
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		a[i].x=x;
		a[i].y=y;
		a[i].z=z*2+t[x]+t[y]; 
	}
	sort(a+1,a+m+1,cmp);
	for (int i=1;i<=m;i++){
		px=find(a[i].x);
		py=find(a[i].y);
		if (px==py) continue;
		f[px]=py;
		ans+=a[i].z;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Plozia (赞：3)

[博客阅读效果更佳](https://blog.csdn.net/BWzhuzehao/article/details/104741744)

前置知识：最小生成树算法（Kruskal/Prim）

[例题](https://www.luogu.com.cn/problem/P3366)

**算法分析：**

这一道题中给出一个无向图，求从任意一点开始经过每一点的最短路径。

既然要经过每一个点，还要求最短路径，算法就是最小生成树了。

我用的是 Kruskal 算法。

有一点需要注意：每条路的长度需要如何计算？

约翰需要经过每一条道路两次，并且每走一次，就需要安慰这条路后的奶牛，所以路径长度=道路长度*2+安慰两头奶牛时间

**代码如下：（因为几乎是 Kruskal 模板，所以没有注释）**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
struct node
{
	LL x,y,dis;
}a[100000+10];
LL n,p,c[10000+10],fa[10000+10],t,ans;
bool cmp(node fir,node sec)
{
	return fir.dis<sec.dis;
}
LL gf(LL x)
{
	if(fa[x]==x) return x;
	return fa[x]=gf(fa[x]);
}
int main()
{
	scanf("%lld%lld",&n,&p);
	for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
	for(int i=1;i<=p;i++)
	{
		scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].dis);
		a[i].dis=a[i].dis*2+c[a[i].x]+c[a[i].y];
	}
	for(int i=1;i<=n;i++) fa[i]=i;
	sort(a+1,a+p+1,cmp);
	for(int i=1;t<n-1;i++)
	{
		int fx=gf(a[i].x);
		int fy=gf(a[i].y);
		if(fx!=fy)
		{
			fa[fx]=fy;
			ans+=a[i].dis;
			t++;
		}
	}
	sort(c+1,c+n+1);
	printf("%lld\n",ans+c[1]);
	return 0;
}
```

---

## 作者：wancong (赞：2)

## 最小生成树

这题写起来很简单，就是需要思考

我们首先看题目要求，需要在保证连通的情况下去除最多的边，说明需要留下一棵生成树。

另外要求谈话时间最短。我们来看谈话时间怎么算。每个农场都要遍历一次，从起点出发到终点再回到起点的过程就相当于dfs的过程。但这里并不需要我们写dfs，我们可以用拓扑学的规律来探究。对于生成树来说，一定不存在环，所以从起点出发遍历一次，回到起点的路径，必然是这样的路径：对于任意一个顶点V，假设其度数为d(V)，则每个路径中间的顶点经过d(V)次，起点经过d(V)+1次，每条边经过2次。具体的证明方法，自己思考，提示：用数学归纳法。

这样，就可以把每条边的权值乘2，再加上它的两个邻接点的权值，构成一个新的图，对这个图求最小生成树。这个最小生成树的权值之和加上这些点的权值最小者即得答案。

所以一下就变成了kruskal算法+并查集的~~模板~~题！

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

int father[10001];

int root(int n) {
    while (father[n] >= 0) n = father[n];
    return n;
}

bool merge(int a, int b) {
    int r1 = root(a), r2 = root(b);
    if (r1 == r2) return false;
    if (father[r1] < father[r2]) {
        father[r1] += father[r2];
        father[r2] = r1;
    } else {
        father[r2] += father[r1];
        father[r1] = r2;
    }
    return true;
}

typedef struct {
    int v1;
    int v2;
    int l;
} edge;
edge arr[100000];
int c[10001];

bool cmp(const edge& a, const edge& b) {
    return a.l < b.l;
}

int main() {
    int n, p, i, v1, v2, l, m = 19260817;
    scanf("%d %d", &n, &p);
    for (i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
        if (m > c[i]) m = c[i];
    }
    for (i = 0; i < p; i++) {
        scanf("%d %d %d", &v1, &v2, &l);
        arr[i].v1 = v1;
        arr[i].v2 = v2;
        arr[i].l = (l << 1) + c[v1] + c[v2];
    }
    sort(arr, arr + p, cmp);
    memset(father, -1, sizeof(father));
    for (i = 0; i < p; i++) {
        if (merge(arr[i].v1, arr[i].v2)) m += arr[i].l;
    }
    printf("%d", m);
    return 0;
}

```

---

## 作者：soy_un_perro (赞：2)

最小生成树之Kruskal——$O(m \log m )$。注意思路转化。

边权转化为边权*2（来回，跑两遍）+两边点权，即

$ L_j=L_j\times2+C_{S_j}+C_{E_j} $  。

最后按照贪心思想，选择点权最小的点开始遍历，即

$ ans+=\min(C_i)$  。

不知道要开long long吗？反正本蒟蒻开了。。。

```cpp
//省略头文件及typedef
const int Maxn=10005,Enum=10;
int n,p;ll c[Maxn],ans=0ll,minpt=1<<25;//minpt存最小点权
struct Edge
{
	int s,e;ll l;
}a[Maxn*Enum];
bool cmp(Edge x,Edge y)
{
	return x.l<y.l;
}
namespace bcj //并查集操作：fa数组，初始化，查询
{
	int fa[Maxn];
	void init()
	{
		for(int i=1;i<=n;i++) fa[i]=i;
	}
	int fd(int x)
	{
		if (x==fa[x]) return x;
		return fa[x]=fd(fa[x]);
	}
}
using namespace bcj;
void prework()
{
	//省略n,p及点权读入
	for(int i=1;i<=p;i++)
	{
		scanf("%d%d%lld",&a[i].s,&a[i].e,&a[i].l);
		a[i].l=(a[i].l<<1)+c[a[i].s]+c[a[i].e];//处理边权
	}
	sort(a+1,a+1+p,cmp);//排序
	init();//并查集预处理
}
void kruskal()
{
	int i=0,sum=0,f1=0,f2=0;
	while(sum<n-1)//找齐n-1条边
	{
		i++;
		f1=fd(a[i].s),f2=fd(a[i].e);
		if (f1==f2) continue;//已连通的两点之间的边不选，否则成环
		sum++;
		fa[f1]=f2;
		ans+=a[i].l;
	}
}
int main()
{
	prework();
	kruskal();
	printf("%lld",ans+minpt);//别漏了最小点权
	return 0;//愉快结束
}
```

---

## 作者：jbc392 (赞：1)

此题考最小生成树

首先想到的是Kruskal

Kruskal就不多讲了

先看样例

![](https://cdn.luogu.com.cn/upload/image_hosting/4dxbx2fg.png)

勾代表需要忽悠的次数,红色的边代表最小生成树

从图中可看出每个点的忽悠次数为此点连接的红色的边的条数

不难看出每条红色的边都要走两遍

在4这个点上我标了一个红色的勾

不难看出点权最小的是出发位置所以4为出发点

那么把上面说的总结在一起

就是每条边的权值是此边 * 2 + 此边连接的两个点的点权

下面是我T了2个点的代码

```
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 10000 + 10 ,MAXP = 100000 + 10;

int n ,p ,c[MAXN];
int fa[MAXN] ,ans ,road;

inline int read()
{
    int x = 0 ,y = 1;
    char c = getchar();
    while(c > '9' || c < '0')
    {
        if(c == '-')y = -1;
        c = getchar();
    }
    while(c <= '9' && c >= '0')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * y;
}

struct node
{
	int x ,y ,l;
}t[MAXP];

int cmp(node x ,node y)
{
	return x.l < y.l;
}

int find(int x)
{
	if(fa[x] == x)return x;
	else find(fa[x]);
}

void Union(int x ,int y)
{
	fa[find(x)] = find(y);
}

void kruskal()
{
	sort(t + 1 ,t + 1 + p ,cmp);
	for(register int i = 1;i <= n;i++)fa[i] = i;
	for(register int i = 1;road < n - 1;i++)
	{
		if(find(t[i].x) != find(t[i].y))
		{
			ans += t[i].l;
			Union(t[i].x ,t[i].y);
			road++;
		}
	}
}

int main()
{
	n = read(); p = read();
	for(register int i = 1;i <= n;i++) c[i] = read();
	for(register int i = 1;i <= p;i++)
	{
		t[i].x = read(); t[i].y = read(); t[i].l = read();
		t[i].l *= 2;
		t[i].l += c[t[i].x] + c[t[i].y];
	}

	kruskal();
	sort(c + 1 ,c + 1 + n);
	cout << ans + c[1];

	return 0;
}
```


---

## 作者：扬皓2006 (赞：1)

思路:存边权为边权2倍加上两个顶点的权值

输出为最小生成树权值总和加上最先点权

如果还不会求最小生成树的请左转[这里](https://www.luogu.org/problem/P3366)

好了，开始我们的正题，此题用的是Kruskal算法，它是一种基于贪心和并查集的算法（就是把边权排序，然后按照边权从小到大搜，如果形成环就跳过继续搜，直到生成树的边数为总边数即可）

代码如下:
```
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[10001],a[10001],tot=0,smalest=0x3f,p,ans=0;
struct Edge{
	int from,to,dis;
}edge[100001];
bool operator <(Edge a,Edge b)
{
	return a.dis<b.dis;
}//定义小于号
int get(int x)
{
	if(fa[x]==x)  return x;
	return fa[x]=get(fa[x]);
}//并查集查询操作
int main()
{
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		smalest=min(a[i],smalest);//存最小点权
	}
	for(int i=1;i<=p;i++)
	{
		tot++;
	scanf("%d%d%d",&edge[i].from,&edge[i].to,&edge[i].dis);
		edge[i].dis=edge[i].dis*2+a[edge[i].from]+a[edge[i].to];
	}
	sort(edge+1,edge+tot+1);//排序
	for(int i=1;i<=n;i++)  fa[i]=i;//初始把每个点视为一个集合
	for(int i=1;i<=p;i++)
	{
		int x=get(edge[i].from);
		int y=get(edge[i].to);
		if(x==y)  continue;
		fa[x]=y;
		ans+=edge[i].dis;
	}
	printf("%d",ans+smalest);//最小生成树权和加上最小点权
	return 0;
}

最后，希望各位同学都能够学会Kruskal，也希望管理大大能够通过此篇题解！
```


---

## 作者：C20212724杨京朝 (赞：1)

今天刚学了最小生成树，写篇题解纪念一下，然而不会Prim，就只能写Kruscal了。

------------
思路：只要根据流程走一遍就行，这个题中就只有边权处理稍微麻烦一点，要把两边的点权加上，即劝（hu you）奶牛的时间；边权 * 2，因为要返回；还要找出最小的点权，因为最后还要再劝（hu you）出发点的奶牛。

代码实现：难道我们每次连边时都要把点权加一遍，其实不然，输入的时候把边权重新赋值即可，dis = ；其次，Kruscal的处理要用到并查集（废话），这里我的find函数是用路径压缩写的。
   
------------
最后贴一下代码：
```cpp
#include <cstdio>
#include <algorithm>
int f[100005],ans,a[100005];
struct node {
	int from,to,dis;
}edge[100005];
void makeSet(int n) {
	for(int i = 1;i <= n;i ++) f[i] = i;
}//初始化
int findSet(int x) {
	if(x != f[x]) f[x] = findSet(f[x]);
	return f[x];
}//找祖宗
void unionSet(int a,int b) {
	int u = findSet(a),v = findSet(b);
	f[u] = v;
}//合并
bool cmp(node x,node y) {
	return x.dis < y.dis;
}//排序函数，按边权排序，也是Kruscal中贪心思想的体现
int main() {
	int n,p,Min = 1e9;
	scanf("%d %d",&n,&p);
	for(int i = 1;i <= n;i ++) scanf("%d",&a[i]),Min = std::min(a[i],Min);//找最小点权
	for(int i = 1;i <= p;i ++) {
		scanf("%d %d %d",&edge[i].from,&edge[i].to,&edge[i].dis);
		edge[i].dis = a[edge[i].from] + edge[i].dis * 2 + a[edge[i].to];//重新赋值，见上文
	}
	makeSet(n);
	std::sort(edge + 1,edge + p + 1,cmp);//排序
	int k = 0;
	for(int i = 1;i <= p;i ++) {//Kruscal的板子
		if(k == n - 1) break;//不形成回路，就只有n-1条边
		if(findSet(edge[i].from) != findSet(edge[i].to)) {
			ans += edge[i].dis;
			unionSet(edge[i].from,edge[i].to);
			k ++;
		}
	}
	printf("%d",ans + Min);//输出，点权和边权的处理上文提到的
	return 0;
}
```


---

## 作者：ws_fuweidong (赞：1)

题意：可以理解为给你一个图，让你建一个树，然后从某根开始走，每走一条边就要消耗两边点权+边的边权。最后再加上一个根的点权，问最少花多少代价。

题解：改变边权然后做最小生成树。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<algorithm>
#include<cstdio>
#define maxn 10001
#define maxm 100001
#define inf 99999999
using namespace std;
struct edge{
    int x,y,z;
}e[maxm];
int fa[maxn],a[maxn];
bool vis[maxn];
int n,m;
int gf(int k){
    return k==fa[k]?k:fa[k]=gf(fa[k]);
}
bool cmp(edge l,edge m)
{
    return l.z<m.z;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    fa[i]=i;
    int ans=inf;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        ans=min(ans,a[i]);
    }
    for (int i=1;i<=m;i++)
    {
        int z;
        scanf("%d%d%d",&e[i].x,&e[i].y,&z);
        e[i].z=a[e[i].x]+a[e[i].y]+z*2;
    }
    sort(e+1,e+1+m,cmp);
    for (int i=1;i<=m;i++)
    {
        int f1=gf(e[i].x);
        int f2=gf(e[i].y);
        if (f1!=f2)
        {
            fa[f1]=f2;
            ans+=e[i].z;
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：ShineEternal (赞：0)

[$My\ blog$](https://blog.csdn.net/kkkksc03/article/details/102688779)


前来补充一篇题解，，

## description：

求一个既有点权又有边权的无向图中的最小生成树。

## solution：

这道题因为一句话：

> 约翰打算在保持各牧场连通的情况下去掉尽量多的道路。

显然就可以看出是用最小生成树。

仔细读读题，发现唯一的瓶颈就是在处理权值上。

- 如何将点权和边权都处理呢？

- 首先，这条路要被来回走两遍（因为是树），所以在总权值里要有它$\times2$

- 其次，每头奶牛会被安慰两次，这样可以想到要加入2倍的点权，但是再更新下一条时就又会被重复计算，所以只需要算一次就行。


**这样中间节点都是两次，两端是1次，但是题目的特殊要求要起点算2次，所以先在读入点权时就找到最小的数最后加入即可**

## code:

```cpp
#include<cstdio>
#include<algorithm> 
using namespace std;
struct ben
{
	int s,e,l;
}a[100005];
int fa[10005];
int cmp(const ben &a,const ben &b)
{
	return a.l<b.l;
}
int c[10005];
int find(int x)
{
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int main()
{
	int n,p;
	scanf("%d%d",&n,&p);
	int Min=100000000;
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		scanf("%d",&c[i]);
		Min=min(Min,c[i]);
	}
	for(int i=1;i<=p;i++)
	{
		scanf("%d%d%d",&a[i].s,&a[i].e,&a[i].l);
		a[i].l=a[i].l*2+c[a[i].s]+c[a[i].e];
	}
	sort(a+1,a+p+1,cmp);
	int k=0,ans=0;
	for(int i=1;i<=p;i++)
	{
		int x=find(a[i].s);
		int y=find(a[i].e);
		if(x!=y)
		{
			ans+=a[i].l;
			k++;
			fa[y]=x;
		}
		if(k==n-1)break;
	}
	printf("%d\n",ans+Min);
	return 0;
}
```

---

## 作者：星之海 (赞：0)

第一次写最小生成树的题解，不喜勿喷——

本题我用的Kruskal

只是改了一下路径的权值

而我过了11次才AC

直接上代码

```cpp
#include<stdio.h>
struct mon
{
    int x;
    int y;
    int v;
};
int father[100001];
int find(int x)//查
{
    if(father[x]!=x)
    father[x]=find(father[x]);
    return father[x];
}
```
P.S.  “并” 放在主函数的循环里了
void qsort(struct mon a[],int l,int r)//对各个路径的权值快排

```cpp
{
    int i,j,mid;
    struct mon p;
    i=l;
    j=r;
    mid=a[(l+r)/2].v;
    while(i<=j)
{
    while(a[i].v<mid)
    i++;
    while(a[j].v>mid)
    j--;
    if(i<=j)
{
    p=a[i];
    a[i]=a[j];
    a[j]=p;
    i++;
    j--;
}
}
    if(l<j)
    qsort(a,l,j);
    if(i<r)
    qsort(a,i,r);
}
int min(int a,int b)//返回较小值
{
    return a<b?a:b;
}
int main()
{
    struct mon a[100001];
    int c[100001],n,p,i,ans=999999;
    scanf("%d%d",&n,&p);
    for(i=1;i<=n;i++)
    father[i]=i;//初始化
    for(i=1;i<=n;i++)
{
    scanf("%d",&c[i]);
    ans=min(ans,c[i]);//和奶牛谈心的最短时间
}
    for(i=1;i<=p;i++)
{
    scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].v);
    a[i].v=a[i].v*2+c[a[i].x]+c[a[i].y];//这个就是对权值的一个修改
}
    qsort(a,1,p);//快排
    for(i=1;i<=p;i++)
{
    int r1,r2;
    r1=find(a[i].x);
    r2=find(a[i].y);
    if(r1!=r2)//不是一个祖宗
{
    ans+=a[i].v;//累加权值
    father[r2]=r1;//并
}       
}
    printf("%d\n",ans);//输出结果
    return 0;
}
```

---

