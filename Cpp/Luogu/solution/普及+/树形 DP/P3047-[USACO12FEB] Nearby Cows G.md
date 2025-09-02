# [USACO12FEB] Nearby Cows G

## 题目描述

Farmer John has noticed that his cows often move between nearby fields. Taking this into account, he wants to plant enough grass in each of his fields not only for the cows situated initially in that field, but also for cows visiting from nearby fields.

Specifically, FJ's farm consists of N fields (1 <= N <= 100,000), where some pairs of fields are connected with bi-directional trails (N-1 of them in total).  FJ has designed the farm so that between any two fields i and j, there is a unique path made up of trails connecting between i and j. Field i is home to C(i) cows, although cows sometimes move to a different field by crossing up to K trails (1 <= K <= 20).

FJ wants to plant enough grass in each field i to feed the maximum number of cows, M(i), that could possibly end up in that field -- that is, the number of cows that can potentially reach field i by following at most K trails.  Given the structure of FJ's farm and the value of C(i) for each field i, please help FJ compute M(i) for every field i.

给你一棵 $n$ 个点的树，点带权，对于每个节点求出距离它不超过 $k$ 的所有节点权值和 $m_i$。

## 说明/提示

There are 6 fields, with trails connecting (5,1), (3,6), (2,4), (2,1), and (3,2).  Field i has C(i) = i cows.


Field 1 has M(1) = 15 cows within a distance of 2 trails, etc.

【数据范围】  
对于 $100\%$ 的数据：$1 \le n \le 10^5$，$1 \le k \le 20$，$0 \le c_i \le 1000$

## 样例 #1

### 输入

```
6 2 
5 1 
3 6 
2 4 
2 1 
3 2 
1 
2 
3 
4 
5 
6 
```

### 输出

```
15 
21 
16 
10 
8 
11 
```

# 题解

## 作者：asuldb (赞：79)

我记得我调这道题时中耳炎，发烧，于是在学长的指导下过了也没有发题解

发现我自己的思路蛮鬼畜的

常规操作：$f[i][j]$ 表示到$i$的距离为$j$的奶牛有多少只，但注意这只是在第二遍dfs之后

在我的第一遍dfs中(就是下面那个叫build的函数）,$f[i][j]$的含义是在i这课子树中到$i$的距离为$j$的奶牛有多少只，所以在第一遍dfs的时候，$f[i][j]$的状态只会来自它的儿子们

于是在第一遍dfs就有一个异常简单的方程

$$f[i][j]=\sum_{}f[k][j-1]$$

其中$k$是 $i$的儿子

如果我们钦定以1为根建树的话，那么1的子树就是整棵树，于是这个时候的$f[1]$就是全树意义下的答案了

而这个时候第二遍dfs就要登场了，第二遍dfs的意义就是利用父亲去更新儿子，于是我们就又有一个简单的方程了

$$f[k][j]=\sum_{}f[i][j-1]$$

其中$k$是 $i$的儿子

这样的话肯定会有重复的，因为到$i$的距离为2的点包含到$k$距离为1的k的儿子们,而这些点位于$k$的子树中的点已经在第一遍dfs的时候被加上了，于是我们在这里简单容斥就好了

于是就是代码了
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
#define maxn 100001
using namespace std;
struct node
{
    int v,nxt;
}e[maxn<<1];
int f[maxn][21],s[maxn],head[maxn],deep[maxn];
int n,num,k;
inline int read()
{
    char c=getchar();
    int x=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
      x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x;
}
inline void add(int x,int y)
{
    e[++num].v=y;
    e[num].nxt=head[x];
    head[x]=num;
}
inline void build(int r)
{
    for(re int i=head[r];i;i=e[i].nxt)
    if(!deep[e[i].v])
    {
        deep[e[i].v]=deep[r]+1;
        build(e[i].v);
        for(re int j=1;j<=k;j++)
        f[r][j]+=f[e[i].v][j-1];
    }
}
inline void dfs(int r)
{
    for(re int i=head[r];i;i=e[i].nxt)
    if(deep[e[i].v]>deep[r])
    {
        for(re int j=k;j>=2;j--)
            f[e[i].v][j]-=f[e[i].v][j-2];//简单的容斥原理了
          //这里的循环一定要倒序
        for(re int j=1;j<=k;j++)
            f[e[i].v][j]+=f[r][j-1];
        dfs(e[i].v);
    }
}
int main()
{
    n=read();
    k=read();
    int x,y;
    for(re int i=1;i<n;i++)
    {
        x=read();
        y=read();
        add(x,y);
        add(y,x);
    }
    for(re int i=1;i<=n;i++)
        s[i]=read(),f[i][0]=s[i];
    deep[1]=1;
    build(1);
    dfs(1);
    for(re int j=1;j<=n;j++)
    {
        int ans=0;
        for(re int i=0;i<=k;i++)
        ans+=f[j][i];
        printf("%d\n",ans);
    }
}
```

---

## 作者：Yuyuanqi (赞：64)

# 题解 P3047 [USACO12FEB]附近的牛Nearby Cows

[题目链接](https://www.luogu.org/problem/P3047)

题目大意是给你一颗树，对于每一个节点i，求出范围k之内的点权之和

看数据范围就知道暴力肯定是会t飞的，所以我们要考虑如何dp（代码习惯写dfs）

仔细思考一下我们发现点i走k步能到达的点分为以下两种

**1.在i的子树中（由i点往下）**

**2.经过i的父亲（由i点往上）**

这样的问题一般可以用**两次dfs**解决

我们定义状态f[i][j]表示i点往下j步范围内的点权之和，d[i][j]表示i点往上和往下走j步范围内点权之和。

第一次dfs我们求出所有的f[n][k]，这个比较简单，对于节点u和其儿子v,f[u][k] += f[v][j - 1]就行了。（第一次dfs已知叶子节点推父亲节点）

第二次dfs我们通过已经求出的f数组推d数组，对于u和u的儿子v, d[v][k] += (d[u][k - 1] - f[v][k - 2]), 注意数组下表不要越界。d[i][j]的初始值应该赋为f[i][j]，因为根节点的d[i][j]就是f[i][j]。（第二次dfs已知父亲节点推儿子节点）

~~思路说得可能有点罗嗦~~看代码吧：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long
#define N 100005
using namespace std;
inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

ll f[N][25], d[N][25];
//f数组和d数组前面已经说了
int val[N];
int n, k, tot, head[N];

struct edge
{
	int to, next;
	edge() {}
	edge(int x, int y) { to = x; next = y; }
}a[N * 2];
//邻接表存图
void add(int from, int to)
{
	a[++tot] = edge(to, head[from]);
	head[from] = tot;
}

void dfs(int x, int fa)
{
	for (int i = 0; i <= k; i++) f[x][i] = val[x];
	for (int i = head[x]; i; i = a[i].next)
	{
		int u = a[i].to;
		if (u != fa)
		{
			dfs(u, x);//先dfs到叶子节点，然后推父亲节点
			for (int i = 1; i <= k; i++)
				f[x][i] += f[u][i - 1];
		}
	}
}
//第一次dfs
void dfs2(int x, int fa)
{
	for (int i = head[x]; i; i = a[i].next)
	{
		int u = a[i].to;
		if (u != fa)
		{
			d[u][1] += f[x][0];
			for (int i = 2; i <= k; i++)
				d[u][i] += d[x][i - 1] - f[u][i - 2];
			dfs2(u, x);//先dfs父亲节点，更新完儿子后dfs儿子
		}
	}
}
//第二次dfs
int main()
{
	n = read(), k = read();
	for (int i = 1; i < n; i++)
	{
		int a1 = read(), a2 = read();
		add(a1, a2);
		add(a2, a1);
	}
	for (int i = 1; i <= n; i++)
		val[i] = read();
	dfs(1, 1);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= k; j++)
			d[i][j] = f[i][j];//把f赋给d
	dfs2(1, 1);
	for (int i = 1; i <= n; i++)
		cout << d[i][k] << endl;//输出答案
	return 0;
}
```
总之有一类树上dp的题，每个节点的答案与这个节点的父亲和儿子都有关，这时候我们可以分两次dfs求出答案，一般这两次dfs便利顺序不同。这要求大家对树的遍历有非常深的理解和实现能力，但是思路其实并没有那么难。

---

## 作者：DQYdqy (赞：33)

## Solution:

首先看看数据范围，$n\le1e5,k\le20$，那我们可以尝试设$f[n][k]$

设$d[i][j]$表示从i点开始向下k的范围内有多少头牛，$f[i][j]$代表从i点开始j范围内有多少头牛

$d[i][j]$可以很容易算出来，对于一个点$u$,$d[u][j]=C_u+\sum_{v\in son_u}d[v][j-1]$

而$f[i][j]$也可以得出，$f[v][j]=f[fa[v]][j-1]-d[v][j-2]+d[v][j]$

最后输出$f[i][k]$就行了

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int n,k,cnt,head[N];
int a[N],d[N][21],f[N][21];
struct Edge{int nxt,to;}edge[N<<1];
void ins(int x,int y){
	edge[++cnt].nxt=head[x];
	edge[cnt].to=y;head[x]=cnt;
}
void dfs(int x,int fa,int u){
	d[x][u]+=a[x];
	for(int i=head[x];i;i=edge[i].nxt){
		int y=edge[i].to;
		if(y==fa) continue;
		d[x][u]+=d[y][u-1];
		dfs(y,x,u);
	}
}
void calc(int x,int fa,int u){
	int w=u-2>=0?d[x][u-2]:0;
	f[x][u]=f[fa][u-1]-w+d[x][u];
	for(int i=head[x];i;i=edge[i].nxt)
		if(edge[i].to!=fa) calc(edge[i].to,x,u);
}
void work(int u){
	for(int i=head[1];i;i=edge[i].nxt)
		calc(edge[i].to,1,u);
}
int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main(){
	n=read(),k=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		ins(x,y),ins(y,x);
	}
	for(int i=1;i<=n;i++)
		a[i]=read(),d[i][0]=a[i];
	if(!k){
		for(int i=1;i<=n;i++)
			printf("%d\n",a[i]);
		return 0;
	}
	for(int i=1;i<=k;i++) dfs(1,0,i),f[1][i]=d[1][i];
	for(int i=1;i<=n;i++) f[i][0]=a[i];
	for(int i=1;i<=k;i++) work(i);
	for(int i=1;i<=n;i++) printf("%d\n",f[i][k]);
	return 0;
}
```


---

## 作者：juruo_zjc (赞：31)

# 路过的靓仔看过来！
走过路过，千万不要蒟蒻！

这道题狠友男赌，尻（考）的不仅仅是码力，毒题能力，更是叔上问题功底的检测，无论各位现在是在普及组还是提高组，都十分值得来刷一下这道经典题目。

（~~抄袭了一下我上一篇题解的开头~~）

------------
不扯其他的了，直切主题

题目就是求每个结点在k步内能到达当前结点的奶牛数目。


因为不仅可以向上搜，还能向下搜，只说步数为k，没说只能往树下面搜，不能往上搜，所以要做两次大法师（滑稽


------------
## 第一次dfs

Dp[u][j]表示从下往上，走j步能到达u点的奶牛数。

很明显这不是正确答案，我们来手动构一张图。

![](https://cdn.luogu.com.cn/upload/pic/73544.png)

在这张其丑无比的图中，我们
看3号结点，它dp[3][j]记录了从
上往下k步到达3的点，但是它忽略了1到达它
情况，于是第二遍大法师就是要处理上方的结点。


------------
## 熔池，融吃，容斥！！！
解决这个问题的办法就是↑ ↑ ↑ ↑

第二遍dfs我们要用父亲状态更新儿子。

方程显而易见：
f[i的儿子][j]+=∑​f[i][j−1]

## 这个方程对吗

------------
## 我信你个鬼！！！！（滑稽
这方程鬼都看得出有许多重复！

在k>2的时候肯定会有重复！

那么重复了什么呢？还是用这张奇丑无比的图

![](https://cdn.luogu.com.cn/upload/pic/73545.png)

K=3

我在图上标的数字表示

Dp[1][3~0]（这是第一次dfs时的dp数组

好，我们来看2号结点。

假如我们要求最终的dp[2][3]
如果用上面的公式的话，

![](https://cdn.luogu.com.cn/upload/pic/73547.png)

我们就要加上这些结点，

然而，4号结点离2号结点的距离明明是1啊，但他
离1的距离的确是2。所以，我们要减去像4号结点一样的结点，那么这些结点有什么特点呢？很明显，它离2距离为1，也就是3-2


------------
所以公式就是

所以公式就是：

f[i的儿子][j]+=∑​f[i][j−1]

f[i的儿子][j]-=∑​f[i][j-2]


------------
那么很明显，第一次dfs是从叶子节点更新根结点，而第二次是父亲更新儿子，所以第一次操作要在搜索后做，第二次要在搜索前。
```cpp
void dfs1(int u,int fa)
{
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==fa)continue;
		dfs1(v,u);
		for(int j=1;j<=k;++j)
		dp[u][j]+=dp[v][j-1];
	}
}
void dfs2(int u,int fa)
{
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==fa)continue;
		for(int j=k;j>=2;--j)
			dp[v][j]-=dp[v][j-2];
		for(int j=1;j<=k;++j)
			dp[v][j]+=dp[u][j-1];
		dfs2(v,u);
	}

```

##### 最后把dp[i][1~k]累加起来即可其实这题还是有些难度的，主要是容斥原理的应用！

# QWQ


---

## 作者：whyl (赞：28)

发布一篇换根的题解

发现大家的做法基本上是容斥做的

填一篇换根的题解

换根的题目的大体思虑是先指定一个根

做出预处理

然后我们换根就只需要考虑父亲节点和儿子节点之间维护的信息

然后我们考虑一下贡献就可以了

定义状态为f[i][j]表示在i节点属于子树距离为j的节点

转移显然f[i][j]=sigma(f[son[x][j-1]])

cut表示抛去原来的贡献

link表示加上贡献

回溯时把根换回来就好了

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
	int x=0,f=1;
	char p=getchar();
	while(!isdigit(p)){
		if(p=='-') f=-1;
		p=getchar();
	}
	while(isdigit(p)) x=(x<<3)+(x<<1)+(p^48),p=getchar();
	return x*f;
}

const int maxn=1e5+5;

int n,k,dp[maxn][23],head[maxn],ver[maxn<<1],nxt[maxn<<1],cnt,ans[maxn];

inline void add(int x,int y){
	nxt[++cnt]=head[x];
	head[x]=cnt;
	ver[cnt]=y;
}

inline void dfs_pre(int x,int fa){
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(y==fa) continue;
		dfs_pre(y,x);
		for(int j=1;j<=k;j++) dp[x][j]+=dp[y][j-1];
	}
}

inline void cut(int root1,int root2){
	for(int i=1;i<=k;i++) dp[root1][i]-=dp[root2][i-1];
} 

inline void link(int root1,int root2){
	for(int i=1;i<=k;i++) dp[root1][i]+=dp[root2][i-1];
}

inline void change_root(int x,int y){
	cut(x,y);
	link(y,x);
}

inline void dfs(int x,int fa){
	for(int i=0;i<=k;i++) ans[x]+=dp[x][i];
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(y==fa) continue;
		change_root(x,y);
		dfs(y,x);
		change_root(y,x);
	}
}

int main(){
	n=read();k=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	for(int i=1;i<=n;i++) dp[i][0]=read();
	dfs_pre(1,0);
//	for(int i=1;i<=n;i++){
//		for(int j=0;j<=k;j++){
//			cout<<dp[i][j]<<" ";
//		}
//		cout<<endl;
//	}
//	cout<<endl;	
	dfs(1,0);
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}

```














---

## 作者：Goldia (赞：16)

ps：蒟蒻我不太明白其他题解的换根思路，感觉每个人写的都是容斥，所以这题为什么要容斥呢？直接换根统计不好吗？

下面开始正题：

- 为什么这道题能换根？因为dp方程只有加操作，他的逆操作就是减，知道一个点的答案后，可以轻易的算出来其他点的答案。
- 首先设一个数组$f[i][j]$,表示有多少个点离$i$这个点的距离为$j$;
- 其次考虑第一次统计，显然$ $f[i][j]=$  \sum_{j=1}^k \ $f[v][j-1]$ $ (v是与i相邻的点),因为第一次统计时只是从下到上转移，所以dp没有后效性。
- 之后我们考虑换根，在讨论这之前，我们先定义两种操作 link和 cut(不是lct) link(now,pre)表示把pre的贡献加到now上，cut(now,pre)表示把now中属于pre的贡献删掉，这样换根就相当于 cut(now,v),link(v,now) 十分的方便。
- 最后只要统计答案就行了$ ans[i]= $ $ \sum_{j=0}^k \ $f[i][j]$ $。

## code:
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
using namespace std;
#define LL long long 
const int N=1e5+5;
int head[N],tot,n,m;
LL f[N][25],a[N];
struct ccf
{
	int to,nxt;
}e[N*2];
void add(int a,int b)
{
	tot++;
	e[tot].to=b;
	e[tot].nxt=head[a];
	head[a]=tot;
}
void init(int now,int fa)
{
	f[now][0]=a[now];
	for(int i=head[now];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa)continue;
		init(v,now);
		for(int j=1;j<=m;j++)
			f[now][j]+=f[v][j-1];
	}
}
void cut(int now,int pre)
{
	for(int i=1;i<=m;i++)
		f[now][i]-=f[pre][i-1];
}
void link(int now,int pre)
{
	for(int i=1;i<=m;i++)
		f[now][i]+=f[pre][i-1];
}
LL ans[N];
void dfs(int now,int fa)
{
	for(int i=0;i<=m;i++)
		ans[now]+=f[now][i];
	for(int i=head[now];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa)continue;
		cut(now,v);link(v,now);
		dfs(v,now);
		cut(v,now);link(now,v);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	init(1,0);
	dfs(1,0);
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
}
```


---

## 作者：Demoe (赞：11)

### [题目传送门](https://www.luogu.com.cn/problem/P3047)

## 前置知识

树形DP、容斥（可以不要）。

## 题意简述

- 给定一棵树，每个点有点权。

- 问在离每个节点距离不超过某定值的点权和。

# 树形DP

首先，$n$ 个点 $n-1$ 条边的连通图是**树**。

我们以1号节点为根（方便）。

定义 $f_{i,j}$ 为离 $i$ 节点 $j$ 距离的点权和。

我们很容易处理他子树内的情况，只需递归迭代即可。

```cpp
void dfs(ll x){
	vst[x]=1;
    for(ll i=hd[x];i;i=es[i].nxt)
        if(!vst[es[i].t]){
        	dfs(es[i].t);
        	for(ll j=1;j<=k;j++) f[x][j]+=f[es[i].t][j-1];
		}
}
```

而我们还要处理不在他子树内的情况。

我们从根往叶子开始。

首先根不需要处理。

对每个它的儿子，我们加上他父亲距离减一的点权和。

但我们会发现，子树内的节点也在里面。

所以我们**先**通过容斥把子树内的减掉。

也就是每个距离减掉他距离-2的。

```cpp
void dfs2(ll x){
	vis[x]=1;
	for(ll i=hd[x];i;i=es[i].nxt)
		if(!vis[es[i].t]){
			for(ll j=k;j>=2;--j) f[es[i].t][j]-=f[es[i].t][j-2];
			for(ll j=1;j<=k;++j) f[es[i].t][j]+=f[x][j-1];
			dfs2(es[i].t);
	}
}
```

时间复杂度 $O(nk)$，每次递归或递推经过 $n$ 个节点，每次更新操作 $k$ 次。

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+5;
ll n,k,tot,hd[N],vst[N],cnt,f[N][25],ans,rt,vis[N];
struct edge{ll t,nxt;}es[N<<2];
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
void add(ll u,ll v){
    es[++tot]=(edge){v,hd[u]},hd[u]=tot;
}
void dfs(ll x){
	vst[x]=1;
    for(ll i=hd[x];i;i=es[i].nxt)
        if(!vst[es[i].t]){
        	dfs(es[i].t);
        	for(ll j=1;j<=k;j++) f[x][j]+=f[es[i].t][j-1];
		}
}
void dfs2(ll x){
	vis[x]=1;
	for(ll i=hd[x];i;i=es[i].nxt)
		if(!vis[es[i].t]){
			for(ll j=k;j>=2;--j) f[es[i].t][j]-=f[es[i].t][j-2];
			for(ll j=1;j<=k;++j) f[es[i].t][j]+=f[x][j-1];
			dfs2(es[i].t);
	}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);rd(k);rt=1;
	for(ll i=1,u,v;i<n;i++){
		rd(u);rd(v);
		add(u,v);
		add(v,u);
	}
	for(ll i=1;i<=n;i++) rd(f[i][0]);
	dfs(rt);
	dfs2(rt);
	for(ll i=1;i<=n;i++){
		ll sum=0;
		for(ll j=0;j<=k;j++) sum+=f[i][j];
		wr(sum);puts("");
	}
	return 0;
}
```



---

## 作者：panda_eater (赞：9)

挺不错的一道树形dp

由于既要统计每个节点的子树还要统计父亲来更新答案，所以需要特殊的算法

用dp[i][j][0]表示结点i的子树中与i距离<=j的结点权值之和（包括i结点权值）

用dp[i][j][1]表示对于该点父节点，不管该节点只管其它子节点时距离<=j-1的牛的个数

稍微用一点容斥来解决状态转移： dp[v][k][1]=dp[u][k-1][0]-dp[v][k-2][0]; (v是u的子节点)

最后对于每个节点，循环不断找父亲，统计牛的数量



 
```cpp
//2591 [Usaco 2012 Feb]Nearby Cows
#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define ll long long
#define fo(i,j,k) for(int i=j;i<=k;i++)
using namespace std;
const int mxn=100005;
int ans[mxn],head[mxn],father[mxn];
int dp[mxn][22][2];  //0表示只管子树，1表示该点父节点中，不管该节点时只管其它子节点时附近牛的个数 
int n,m,cnt;
struct edge {int to,next;} f[mxn<<1];
inline void add(int u,int v)
{
    f[++cnt].to=v;f[cnt].next=head[u];head[u]=cnt;
}
inline void dfs(int u,int fa)
{
    int i,j,k,sum=0;
    father[u]=fa;
    fo(k,1,m) dp[u][k][0]=dp[u][0][0];
    for(i=head[u];i;i=f[i].next)
    {
        int v=f[i].to;
        if(v==fa) continue;
        dfs(v,u);
        fo(k,1,m) dp[u][k][0]+=dp[v][k-1][0];
    }
    for(i=head[u];i;i=f[i].next)
    {
        int v=f[i].to;
        if(v==fa) continue;
        dp[v][1][1]=dp[u][0][0]; 
        fo(k,2,m) dp[v][k][1]=dp[u][k-1][0]-dp[v][k-2][0];
    }
}
int main()
{
    int u,v;
    scanf("%d%d",&n,&m);
    fo(i,2,n)
    {
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    fo(i,1,n) scanf("%d",&dp[i][0][0]);
    dfs(1,0);
    fo(i,1,n)  //枚举试点 
    {
        ans[i]=dp[i][m][0];
        int u=i,v;
        fo(j,1,m)
        {
            ans[i]+=dp[u][m-j+1][1];
            u=father[u];
            if(!u) break;
        }
    } 
    fo(i,1,n) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：元夕 (赞：8)

### 树形dp题。。



**考虑两遍dfs，一次从统计从父亲出去的点权， 一次从孩子出去的点权。**

1. 状态量。

设由题问， $f[i][j]$表示距离$i$为$j$的点权之和,  $d[i][j]$表示距离$i$为$j$ 且$j \in Son_i$的点权之和。

2. dfs1

易知，
$$f[i][j] = d[i][j] = \sum_{k \in Son_i}f[k][j - 1] $$
容易理解，不多赘述。

3. dfs2

对于节点$i$与其$cnt$辈祖先$t$以及$cnt - 1$辈祖先$s$, 需要的是如图部分:(意会即可)
![](https://cdn.luogu.com.cn/upload/image_hosting/wai0xrum.png)
所以我们求时，就加上(例如)$d[1][j - cnt] - d[2][j - cnt - 1]$, 就可轻松求出所需内容

4. cpp

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5 + 5;
const int maxk = 20 + 5; 
int n, k, f[maxn][maxk], d[maxn][maxk], fa[maxn];
vector <int> e[maxn];
void dfs1(int x, int father) {
	for(int i = 0, y;i < e[x].size();i ++) {
		y = e[x][i];
		if(y ^ father) {
			dfs1(y, x); fa[y] = x;
 			for(int j = 1;j <= k;j ++) { 
				f[x][j] += f[y][j - 1];
			}
		}
	}
}
void dfs2(int x, int father) {
	for(int i = 0;i < e[x].size();i ++) {
		if(e[x][i] ^ father) dfs2(e[x][i], x);
	}
	for(int j = 1;j <= k;j ++) {
		int cnt = 0, t = x, s;	
		while(cnt < j && fa[t]) {
			cnt ++, s = t, t = fa[t];
			f[x][j] += (d[t][j - cnt] - d[s][j - cnt - 1]);
		} 
	}
} 
signed main() {
	cin >> n >> k; 
	for(int i = 1, x, y;i < n;i ++) {
		scanf("%lld%lld", &x, &y);
		e[x].push_back(y);
		e[y].push_back(x);			
	}
	for(int i = 1;i <= n;i ++) {
		scanf("%lld", &f[i][0]);
	}
	dfs1 (1, 0); fa[1] = 0;
	for(int i = 1;i <= n;i ++) {
		for(int j = 0;j <= k;j ++) {
			d[i][j] = f[i][j];
		}
	}
	dfs2 (1, 0);
	for(int i = 1;i <= n;i ++) {
		int res = 0;
		for(int j = 0;j <= k;j ++) {
			res += f[i][j];
		}
		printf("%lld\n", res);
	}
	return 0;
}

```

---

## 作者：szr666 (赞：8)

我这里推荐一下[我的博客](https://www.luogu.org/blog/szr666--blog/)

在博客里观看更美观哦~

[题目](https://www.luogu.org/problemnew/show/P3047)
------------


------------

华丽的分割线
# 解析
说一下本蒟蒻的做法

### 搜索

对于树形$dp$,当然要搜索,则先设以$1$为根

对于每第$i$点求出$dp[i][j]$,表示以$i$为根且深度不超过$j$的子树和,

则$dp[i][j]=dp[i][0]+\sum\limits_{u\in son}dp[u][j-1]$,$son$为子节点集合

顺便把各节点的父节点$fa$求出来,则$dp[1][k]$为$1$的答案

### 转移

对于第$i$个点来说,$dp$数组只记录了它下面距离为$k$的和

可以向上走到某一个祖宗,再从祖宗走到另一棵子树,且满足条件

若某个祖宗距离第$i$个点$j$步,如图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/z9oi67z4.png)

$ans[i]$先等于$dp[i][k]$,还需加上距离为$j($小于等于$k)$
的

祖先的其它子树,这里我说的其它子树指不包含点$i$的子树

先枚举$j$,设祖先为$f$,则$ans[i]+=dp[f][k-j]$

因为这里算了包含$i$及其某些在$f$下面祖先的子树,应减去

设距离$i$为$j-1$的祖先为$f'$,则$ans[i]-=dp[f'][k-j-1]$

因为不减会把$f'$的其它子树再加一遍,但在枚举$j-1$时已加完

同时也会把$f'$到$i$链上的某些点加进来,先都减去

最后再把其祖先与$i$链上的值加一下,把之前的补回来

因为已经处理过$fa$数组,所以直接枚举$j$,不断求$f'$和$f$即可

# 代码

```cpp
#include<cstdio>
using namespace std;
void read(int &x)
{
	x=0;
	int f;
	f=1;
	char c;
	c=getchar();
	while((c<'0'||c>'9')&&c!='-')
	{
		c=getchar();
	}
	if(c=='-')
	{
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	x=x*f;
}
const int N=110000;
struct node
{
	int to;
	int next;
};
node e[N*2];
int head[N],etot;
void add(int x,int y)
{
	etot++;
	e[etot].to=y;
	e[etot].next=head[x];
	head[x]=etot;
}
int dp[N][30];
int fa[N];
int ans[N];
void dfs(int x,int ffa)
{
	int i,j;
	for(j=1;j<=20;j++)
	{
		dp[x][j]=dp[x][0];
	}
	for(i=head[x];i!=0;i=e[i].next)
	{
		if(e[i].to!=ffa)
		{
			dfs(e[i].to,x);
			fa[e[i].to]=x;
			for(j=1;j<=20;j++)
			{
				dp[x][j]+=dp[e[i].to][j-1];
			}
		}
	}
}
int main()
{
	int n,i,x,y,k,j;
	read(n);
	read(k);
	for(i=1;i<=n-1;i++)
	{
		read(x);
		read(y);
		add(x,y);
		add(y,x);
	}
	for(i=1;i<=n;i++)
	{
		read(dp[i][0]);
	}
	dfs(1,0);
	for(i=1;i<=n;i++)
	{
		ans[i]=dp[i][k];
		x=i;
		for(j=1;j<=k-1&&x!=1;j++)
		{
			y=fa[x];
			ans[i]+=dp[y][k-j]-dp[x][k-j-1];
			x=y;
		}
		if(x!=1)
		{
			ans[i]+=dp[fa[x]][0];
		}
	}	
	for(i=1;i<=n;i++)
	{
		printf("%d\n",ans[i]);
	}
}
```


---

## 作者：caidzh (赞：7)

一道好题！可能本人太菜了，因此想不到一次$dfs$的方法，写了两次$dfs$的

对于树形$dp$，我们最擅长的就是合并子树内的答案，可是这题的答案并不是全从子树里来的，因此我们必须另辟蹊径。

考虑先统计子树里的答案（即从儿子推到父亲），然后再进行一次从父亲推到儿子的递推

### $Step.1:$从儿子推到父亲

我们考虑用$dp[i][j]$表示以$i$为根的子树中，与$i$距离为$j$的点有几个，那么显而易见的，我们应该先处理最底下的叶子结点，然后合并到根

转移方程如下：

$$dp[i][j]=\sum_{k\in_{son[i]}}dp[k][j-1]$$

这次的转移非常简单，可以用一次$dfs$来完成

### $Step.2:$从父亲推到儿子

接下来我们考虑从父亲到儿子的递推

你会发现这东西很麻烦，因为在父亲的状态中存在它的儿子的一部分，因此我们容斥一波，把儿子中的状态减掉即可

**注意接下来的等号右边的所有值都是在第一次中求出来的，并没有被第二次的求值覆盖，写代码的时候注意细节**

$$dp[i][j]=dp[i][j]+dp[fa[i]][j-1]-dp[i][j-2]$$

解释一下：对于$i$来说，在它的子树中距离它$j$的点已经求出，接下来还要加上经它的父亲中转的其他子树的节点，因为多出了$fa[i]->i$这样一条边，所以要加上$dp[fa[i]][j-1]$，然后因为这个值里包含了$dp[i][j]$中的一部分，因此要减掉$dp[i][j-2]$

这也可以用一次$dfs$求出

最后统计答案的时候对于$i$，输出：

$$\sum_{j=0}^kdp[i][j]$$

代码如下：
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define INF 2147483647
#define LLINF 9223372036854775807
#define LL long long
#define xyx AKIOI
#define Dilute AKIOI
#define Chtholly_Tree AKIOI
#define time_interspace AKIOI
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
int n,k;
struct Edge{int nxt,to;}edge[200010];
int head[100010],cnt,dp[100010][21],val[100010];
void add_edge(int x,int y){
	edge[++cnt].nxt=head[x];edge[cnt].to=y;head[x]=cnt;
}
void dfs(int x,int fa){
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(v==fa)continue;
		dfs(v,x);for(int j=0;j<k;j++)dp[x][j+1]+=dp[v][j];
	}
}
void dfs1(int x,int fa){
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(v==fa)continue;
		for(int j=k;j>=1;j--)if(j!=1)dp[v][j]+=dp[x][j-1]-dp[v][j-2];else dp[v][j]+=dp[x][j-1];
		dfs1(v,x);
	}
}
int main()
{
	n=read();k=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();add_edge(u,v);add_edge(v,u);
	}for(int i=1;i<=n;i++)dp[i][0]=read();
	dfs(1,0);dfs1(1,0);
	for(int i=1;i<=n;i++){
		int sum=0;
	    for(int j=0;j<=k;j++)sum+=dp[i][j];
	    cout<<sum<<endl;
	}
	return 0;
}
```

---

## 作者：Minclxc (赞：7)

不用dfs，不用后向星，200ms-

记录每个点走k步可以到的点权和，每条单向边方向走k-1步可以到的点权和

分别是C[n][k]和E[n<<1].P[k]

然后就是dp方程了:C[u][c]+=E[e].P[c]=C[v][c-1]-E[e^1].P[c-1];E[e]表示u到v，E[e^1]表示v到u,C[u][0]初值为点权

发现每次C、E.P和本次的并无关系，所以可以直接循环边，而且只和上一次的有关系，所以可以循环压缩，省空间，因为循环边，所以连后向星也不用了

算上读入优化共26行

```cpp
#include<cstdio>
using namespace std;
#define fo(a,b,c) for(int a=b;a<=c;a++)
int read(){
    int a=0,f=0;char c=getchar();
    for(;c<'0'||c>'9';c=getchar())if(c=='-')f=1;
    for(;c>='0'&&c<='9';c=getchar())a=a*10+c-'0';
    return f?-a:a;
}
const int maxn=100001;
struct edge{int u,v,P[2][2];}E[maxn];
int A[maxn],C[maxn][2];
int main(){
    int n=read(),k=read();
    fo(i,2,n)E[i]=(edge){read(),read()};
    fo(i,1,n)A[i]=C[i][0]=read();//以上读入
    fo(i,1,k){//循环步数
        fo(j,1,n)C[j][i&1]=A[j];
        fo(j,2,n){//循环边
            C[E[j].u][i&1]+=E[j].P[0][i&1]=C[E[j].v][i&1^1]-E[j].P[1][i&1^1];
            C[E[j].v][i&1]+=E[j].P[1][i&1]=C[E[j].u][i&1^1]-E[j].P[0][i&1^1];
        }//dp
    }
    fo(i,1,n)printf("%d\n",C[i][k&1]);
    return 0;
}
```

---

## 作者：AxDea (赞：7)

[题面](https://www.luogu.com.cn/problem/P3047)

题意简述：

给一个节点数为 $n$ 且有 $n-1$ 条边的连通图，给出每个点的点权 $c_i$ ，对于每一个点，求出与其距离不大于 $m$ 条路径的点的权值和

首先它是一棵树 ~~(废话)~~

这题拿上手，不能正经搜索，考虑DP

设计状态 $f_{i,j}$ 表示第 $i$ 个点距离不大于 $j$ 的点权和

那么 $f_{i,0}$ 即为点权 $c_i$ (初始化)

$k$ 为点 $i$ 经过一条边所到之处， $num_i$ 表示 $k$ 的个数，则转移方程为：
$$f_{i,j} = \sum f_{k,j-1} - (num_i-1) \times f_{i,j-2}$$

说明一下减去的部分，因为 $\sum f_{k,j-1}$ 肯定会重复算 $num_i$ 次 $f_{i,j-2}$

为什么，因为这个状态的定义就是相互的，我们只需要每次加上后一层的点权的总和，将前面的减去即可

大家可以画张图理解一下，其实就是简单的容斥原理。

特殊的，对于 $j = 1$ 的情况，有转移方程：
$$f_{i,j} = \sum f_{k,j-1} + f_{i,j-1}$$

代码供出
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5+7;
struct node {                  // 链式前向星存图
	int nxt,dir;
}Edge[maxn<<1];
int head[maxn],num[maxn],cnt;
inline void Add(int u,int v) {
	Edge[++cnt].dir = v,Edge[cnt].nxt = head[u],head[u] = cnt;
	Edge[++cnt].dir = u,Edge[cnt].nxt = head[v],head[v] = cnt;
	num[u]++,num[v]++;
}
int n,m,f[maxn][23]; 		// f[i][j] 表示第i个节点走j步时的总权值 
int main() {
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=1;i<n;++i) {
		scanf("%d%d",&u,&v);
		Add(u,v);
	}
	for(int i=1;i<=n;++i) scanf("%d",&f[i][0]);    // 初始化
	for(int i=1;i<=m;++i)                          // 进行DP
		for(int j=1;j<=n;++j) {
			for(int k=head[j];k;k=Edge[k].nxt) 
				f[j][i] += f[Edge[k].dir][i-1];
			if(i>1) f[j][i] -= (num[j]-1) * f[j][i-2];
			else f[j][i] += f[j][i-1];
		}
	for(int i=1;i<=n;++i) printf("%d\n",f[i][m]);
	return 0;
}
```

---

## 作者：Forever_Lin (赞：6)

    首先这是一道很明显的树形dp，读完题思考一下就可以知道大致的思路了，但我在这一题上还是卡了很长时间。

------------
1. 将每个点分两步来看 考虑：

   对于第i个点，在其k步范围内的点，要么在其子树内，要么在它的父亲及以上。

   **dp[i][j]** 表示对于第i个点，距离它距离为j的点上的牛的总数
  
2. 第一步，对于其子树范围内的点（由子节点v转移到父节点u）
   
   显然 通过深搜简单dp一下就好了，见代码中的dfs
   
   **$dp[u][j]+=dp[v][j-1]$**
 
3. 第二步，对于其上方的点（用父节点u转移到子节点v）
   
   难道就是简单地 $dp[v][j]+=dp[u][j-1]$？错了！
   
   那该怎么办呢？我想了很久，~~想到了一个方案~~，要记录路径，但也仅仅是20分
   
   于是，我尝试在错误的状态转移上稍加修改，只要删除上面两个状态转移方程中重复的部分就好啦，而对于$dp[v][j]$，其重复的部分就是$dp[v][j-2]$(多画几个图理解一下)
   
4. 贴代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int d[100010][30],k,head[100010],sum[100010],tot,n,c[100010],x,y;
struct node
{
    int v,nex;
}e[200020];
inline void add(int u,int v)
{
    tot++;
    e[tot].v=v;
    e[tot].nex=head[u];
    head[u]=tot;
}
inline void dfs(int u,int fa)
{
    d[u][0]+=c[u];
    for (int i=head[u];i;i=e[i].nex)
    {
        int v=e[i].v;
        if (v==fa) continue;
        dfs(v,u);
        for (int j=0;j<k;j++)
          d[u][j+1]+=d[v][j];
    }
}
inline void dfs2(int u,int fa)
{
    for (int i=head[u];i;i=e[i].nex)
    {
        int v=e[i].v;
        if (v==fa) continue;
        
        for (int j=k;j>=2;j--)
            d[v][j]-=d[v][j-2];
        for (int j=1;j<=k;j++) 
            d[v][j]+=d[u][j-1];
        
        dfs2(v,u);
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for (int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        add(x,y);add(y,x);
    }
    for (int i=1;i<=n;i++) scanf("%d",&c[i]);
    dfs(1,0);
    dfs2(1,0);
    for (int i=1;i<=n;i++)
      for (int j=0;j<=k;j++) 
      sum[i]+=d[i][j];
    for (int i=1;i<=n;i++) printf("%d\n",sum[i]);
    return 0;
}
```
   
   
   
   
   

---

## 作者：zhyh (赞：6)

我发现我的做法和各位都不一样诶，不过觉得大家的做法都挺漂亮的qwq  
我用了一个辅助数组（应该不算是什么结构qwq），用途后面再说

首先用$sum[i][j]$表示以节点$i$为根的子树中，与$i$相距为$j$的节点权值总和；  
处理完后我们重新从根节点$u$跑一遍dfs，我们知道，根节点$u$的答案就是$\sum^{K}_{j=0}sum[u][j]$

当往下走一层时，对于当前节点$v$而言，它的答案由两部分组成，分别是$\sum^{K}_{j=0}sum[v][j]$和**根节点$u$中减去$v$子树贡献后的$\sum^{K-1}_{j=0}sum'[u][j]$**

关键就在这里，为了维护$sum'$，我用了一个辅助数组$stk$，且遍历时每个节点$x$在该数组上都对应有一个位置$p_x$，$p_x=K+deep_x$；其有**$stk[p_x-j]$的值为$x$非子树部分距$x$为$j$的贡献**

具体维护操作如下：dfs到某节点$u$时首先统计答案：
$$ans[u]=\sum^{K}_{j=0}sum[u][j]+\sum^{K}_{j=0}stk[p_x-j]$$
接着从$u$开始向下遍历，对于当前$u$的子节点$v$，我们在对应的位置加上$v$非子树部分的贡献（遍历完$v$后再将其减去），即：
$$stk[p-j]=stk[p-j]+sum[u][j]-sum[v][j-1]$$
处理完后再跑到$v$，注意有$p_v=p_u+1$。各位模拟一下就会发现它的有趣之处啦。另外，$p_{root}=K+1$（其实只要大于$K$就可以了）。

我觉得这种思维挺漂亮的，不知有什么其它应用qwq

代码如下：
```cpp
#include <cstdio>
using namespace std;
const int MAXN = 100005;

struct edge {
	int v, pre;
} e[MAXN<<1];
int N, T, C[MAXN], fst[MAXN], vis[MAXN];
int sum[MAXN][21], ans[MAXN], stk[MAXN+50];

inline int read()
{
	register int o = 0;
	register char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >='0' && c <='9') o = (o<<3)+(o<<1)+(c&15), c = getchar();
	return o;
}
inline void adde(int a, int b, int k)
{
	e[k] = (edge){b, fst[a]}, fst[a] = k;
}
void dfs(int k)
{
	vis[k] = 1, sum[k][0] = C[k];
	for (register int o=fst[k], vv; o; o=e[o].pre) if (!vis[e[o].v]) {
		vv = e[o].v, dfs(vv);
		for (register int i=1; i<=T; i++) sum[k][i] += sum[vv][i-1];
	}
}
void dp(int k, int p)
{
	vis[k] = 0;
	for (register int i=0; i<=T; i++) ans[k] += sum[k][i] + stk[p-i];
	for (register int o=fst[k], vv; o; o=e[o].pre) if (vis[e[o].v]) {
		vv = e[o].v, stk[p] += sum[k][0];
		for (register int i=1; i<=T; i++) stk[p-i] += sum[k][i] - sum[vv][i-1];
		dp(vv, p+1), stk[p] -= sum[k][0];
		for (register int i=1; i<=T; i++) stk[p-i] -= sum[k][i] - sum[vv][i-1];
	}
}
int main()
{
	N = read(), T = read();
	for (register int i=1, a, b; i<N; i++) {
		a = read(), b = read();
		adde(a, b, i), adde(b, a, i+N);
	}
	for (register int i=1; i<=N; i++) C[i] = read();
	
	dfs(1);
	dp(1, T+1);
	
	for (register int i=1; i<=N; i++) printf("%d\n", ans[i]);
}
```

---

## 作者：天国的逗比 (赞：5)

分享一种奇妙的解法；（也不清楚有没有人写过emm）
首先，对于树上的任意一个点x，它k步以内能够到达的点分为3种情况：

1：当前节点正下方的点，如它的儿子和它儿子的儿子；

我们将x恰好j步所能到达的此类节点的权值和记作f1[x][j];

2：当前节点正上方的点，如它的父亲和它父亲的父亲；

我们将x恰好j步所能到达的此类节点的权值和记作f2[x][j];

3：当前节点的旁系血亲,如我父亲的另一个儿子，我祖先的另一个后代等；

我们将x恰好j步所能到达的此类节点的权值和也记在f2[x][j]里;（理由等下再做讨论）

显然，第一种和第二种情况可以DFS和BFS直接求；

那么，现在问题就变成了如何求它的旁系血亲，即同x不在一条链上的对答案有贡献的点；

我们发现，如当前节点能通过它的正上方的节点，也就是它的直系祖先（我们先记作fa[x]），到达它的旁系血亲；fa[x]也必然能够到达这位旁系血亲；那我们就可以在进行对tip2的求解时顺路传递下来了；（这就是我们将tip2与tip3统一用f2记录的原因）；

既然这样，那么我们就只要求x父亲的其它子树中满足条件的节点了，即x的兄弟节点。

我们用y表示另一位兄弟节点，因为x要先到x，y的父亲fa[x]，再走到y，这里要消耗2步的距离，那状态转移方程就顺理成章的出来了：
f2[x][j]+=f2[y][j-2];

如此这般，在最后输出答案时，我们只需要计算

$sum_{i}=\sum_{j=0,j\le k}f1[i][j]+f2[i][j]$

然后sum还需要-=f1[i][0];因为我们给f1[i][0],f2[i][0]都赋值为c[i];在这里被计算了两次，需要去重；
把每一个i的sum依次输出就行了；

值得注意的一点是某些毒瘤数据，直接算会被卡爆，我们可以加入一些优化；我的做法是处理出一个maxdep;
如果$2maxdep-1<=k$此时每个点必然能到达所以的点因为你从一个深度最大点到根再到另一个深度最大点需要的距离（2maxdqp-1）都在k的范围以内，那么所以的点显然可以互相到达；

以下是AC代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100001
using namespace std;
inline void read(int &x){
	int datta=0;char chchc=getchar();bool okoko=0;
	while(chchc<'0'||chchc>'9'){if(chchc=='-')okoko=1;chchc=getchar();}
	while(chchc>='0'&&chchc<='9'){datta=datta*10+chchc-'0';chchc=getchar();}
	x=okoko?-datta:datta;
}
int n,k,a,b,cnt,head[N],nxt[N<<1],to[N<<1];
int root=1,f1[N][21],f2[N][21],fa[N],nn[N];
int mmx,ssum,dep[N];
void link(int a,int b){
	to[++cnt]=b,nxt[cnt]=head[a],head[a]=cnt;nn[a]++;
}
void get_ans1(int x,int last){
	dep[x]=dep[last]+1;
	if(dep[x]>mmx)mmx=dep[x];
	for(int i=head[x];i;i=nxt[i]){
		if(to[i]!=last){
			get_ans1(to[i],x);
			for(int j=1;j<=k;j++)
				f1[x][j]+=f1[to[i]][j-1];
		}
	}
}
void get_ans2(int x,int last){
	int p[nn[x]];int tot=0;
	for(int i=head[x];i;i=nxt[i]){
		if(to[i]!=last){
			p[++tot]=to[i];
			get_ans2(to[i],x);
		}
	}
	for(int i=1;i<=tot;i++){
		for(int j=1;j<=tot;j++){
			if(i!=j){
				for(int l=2;l<=k;l++)
					f2[p[i]][l]+=f1[p[j]][l-2];
			}
		}
	}
}
void get_ans3(int x,int last){
	for(int i=head[x];i;i=nxt[i]){
		if(to[i]!=last){
			for(int j=1;j<=k;j++)
				f2[to[i]][j]+=f2[x][j-1];
			get_ans3(to[i],x);
		}
	}
}

int main(){
	read(n),read(k);
	for(int i=1;i<n;i++){
		read(a),read(b);
		link(a,b),link(b,a);
	}
	for(int i=1;i<=n;i++){
		read(f1[i][0]);
		f2[i][0]=f1[i][0];
		ssum+=f1[i][0];
	} 
	get_ans1(root,0);
	if((mmx<<1)-1<=k){
		for(int i=1;i<=n;i++){
			printf("%d\n",ssum);
			
		}return 0;
	}
	get_ans2(root,0);
	get_ans3(root,0);
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=0;j<=k;j++)
			sum+=f1[i][j]+f2[i][j];
		sum-=f1[i][0];
		printf("%d\n",sum);
	}
	return 0;
}
```

---

## 作者：nofind (赞：4)

发现很多题解没解释这为什么是对的,这其实是换根法.
------------

参考:https://www.cnblogs.com/wsmrxc/p/9818331.html

题意：

给你一棵树,求从每个点x出发,最多走k条路能到达的点的权值之和。

解析：

暴力就是从每个点dfs,深度为k就返回即可。

期望得分：70,原因：TLE

code(一开始只会暴力,就写了试试)：

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
struct edge
{
    int to,nxt;
}e[maxn<<1];
int n,k,cnt;
int head[maxn],c[maxn],f[maxn];
inline void add(int u,int v)
{
    e[++cnt].nxt=head[u];
    head[u]=cnt;
    e[cnt].to=v;
}
int dfs(int x,int fa,int dep)
{
    if(dep==k) return c[x];
    int ans=0;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(y==fa) continue;
        ans+=dfs(y,x,dep+1);
    }
    return ans+c[x];
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }	
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=1;i<=n;i++) f[i]=dfs(i,0,0);
    for(int i=1;i<=n;i++) printf("%d\n",f[i]);
    return 0;
}
```
正解：

发现似乎无法用树形DP解决,因为父亲可以更新儿子,这就具有后效性。

又注意到根节点不用考虑父亲节点的那一条路,因此可以用一次树形DP求出根节点的答案。

状态:f[i][j]表示从i经过j条路到达的点的权值和。

如果以x为根,方程f[x][j]+=singma(f[y][j-1])(1=<j<=k),y是x的儿子。

这样可以求出x的答案。

但是这样对每个点跑一次DP，复杂度与暴力无异。

发现这好像可以用换根法解决。

假设以x为根的答案已经求出,那么y的答案就少了经过x的路径的点,加上就好了。

也就是说对于y，以它为根的答案可以由x求出。

f[y][j]=sigma(f[x][j-1])(1=<j<=k)

但是这样的话会重复计算：f[x][j-1]中包含了f[y][j-2],即x走y这条路径到达的点,减去即可,注意倒序。

### 好题~

code(代码参考了题解,毕竟一开始真的不会~)：

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
const int maxk=30;
struct edge
{
	int to,nxt;
}e[maxn<<1];
int n,k,cnt;
int head[maxn],c[maxn];
int f[maxn][maxk];
bool vis[maxn];
inline void add(int u,int v)
{
	e[++cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}
void dfs1(int x)
{
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(vis[y]) continue;
		dfs1(y);
		for(int j=1;j<=k;j++) f[x][j]+=f[y][j-1];
	}
}
void dfs2(int x)
{
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(vis[y]) continue;
		for(int j=k;j>=2;j--) f[y][j]-=f[y][j-2];//这里要倒序,用正确的状态更新. 
		for(int j=1;j<=k;j++) f[y][j]+=f[x][j-1];
		dfs2(y);
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++) scanf("%d",&c[i]),f[i][0]=c[i];
	dfs1(1);memset(vis,0,sizeof(vis));dfs2(1);
	for(int i=1;i<=n;i++)
	{
		int ans=0;
		for(int j=0;j<=k;j++) ans+=f[i][j];
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Isonan (赞：4)

原题传送门[>Here<](https://www.luogu.org/problemnew/show/P3047)

如果只查询一个点，我们可以把这个点看成根，要求的也就是所有深度$\le k$的点的权值和。

现在考虑每个点都要询问怎么办。

这里有一种做树形DP很重要的思想，我也不知道叫什么，就姑且叫做‘换根思想’吧。

考虑一个点的父亲是根节点，现在如何快速转移到该点。

（设son(r)表示以r为根的子树集合）

对于一个点x，假设另外一个点y与fa[x]的距离为s（也就是当fa[x]为根时深度为s），那么

当$y \in son(x)$该点对于x来说深度为s-1；

否则为s+1。

这样转移就可以了。

代码：

```cpp
#include <cstdio>
#define int long long

int head[100001],nxt[200001],b[200001],val[100001],dep[100001][23],k,m[100001],n,K;
void push(int s,int t){
    nxt[++K]=head[s];
    head[s]=K;
    b[K]=t;
}
void build(int x,int f){
    dep[x][0]=val[x];
    for(int i=head[x];i;i=nxt[i]){
        if(b[i]==f)continue;
        build(b[i],x);
        for(int j=1;j<=k;j++)dep[x][j]+=dep[b[i]][j-1];
    }
}
void check(int x,int f){
    if(x!=1)for(int i=k;i;i--)dep[x][i]+=dep[f][i-1]-dep[x][i-2];
    for(int i=0;i<=k;i++)m[x]+=dep[x][i];
    for(int i=head[x];i;i=nxt[i])if(b[i]!=f)check(b[i],x);
}
#undef int
int main(){
#define int long long
    scanf("%lld%lld",&n,&k);
    for(int i=1,s,t;i<n;i++)scanf("%lld%lld",&s,&t),push(s,t),push(t,s);
    for(int i=1;i<=n;i++)scanf("%lld",val+i);
    build(1,0);
    check(1,0);
    for(int i=1;i<=n;i++)printf("%lld\n",m[i]);
}
```

---

## 作者：Panthera_AFO (赞：4)

神题
让我搞清了大部分树形dp思路
第一遍dfs求出子树内的信息
第二遍搞出非子树信息（一般会对子树内的产生影响，需要容斥）
$f[i][j]$表示经过最多j步到i点的奶牛数
详见代码
```
#include<iostream>
#include<cstdio>
#include<queue>
int const maxn=100110,maxm=24,inf=0x1f1f1f1f;
struct E
{
    int to,next;
    E(int to=0,int next=0):
        to(to),next(next){}
}e[maxn<<1];
int head[maxn],cnt;
inline void add(int u,int v)
{
    e[++cnt]=(E){v,head[u]};
    head[u]=cnt;
}
int n,k,w[maxn];
int f[maxn][maxm],ff[maxn][maxm],fff[maxn][maxm],size[maxn];
void pre_dfs(int u,int fa)
{
    fff[u][0]=f[u][0]=w[u];
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa)
            continue;
        pre_dfs(v,u);
        for(int j=1;j<=k;j++)
            f[u][j]+=f[v][j-1];
    }
    for(int j=1;j<=k;j++)
        fff[u][j]=f[u][j]+fff[u][j-1];
        //新开一个数组，要不会对向上回溯产生影响
}
void r_c_dfs(int u,int fa)
{
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa)
            continue;
        ff[v][0]=w[v];
        ff[v][1]=fff[v][1]+fff[u][0];
        //单独处理0、1步的情况
        for(int j=2;j<=k;j++)
            ff[v][j]=fff[v][j]+ff[u][j-1]-fff[v][j-2];
            //细节，对于u要用更新后的值，也就是ff数组
            //这个容斥请务必自己思考或手模
        r_c_dfs(v,u);
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int u,v,i=1;i<n;i++)
        scanf("%d%d",&u,&v),add(u,v),add(v,u);
    for(int i=1;i<=n;i++)
        scanf("%d",w+i);
    pre_dfs(1,0);
    for(int j=0;j<=k;j++)
        ff[1][j]=fff[1][j];
       	//别忘了对1初始化
    r_c_dfs(1,0);
    for(int i=1;i<=n;i++)
        printf("%d\n",ff[i][k]);
    return 0;
}
```

---

## 作者：tyno夏 (赞：3)

这题应该算是比较巧妙的换根dp（当然也可能是我的做法有点假）

最主要的是我发现这题的k值非常小，完全可以维护一个k倍的额外空间。

所以往这方面考虑，任意一个点距离k以内的点，可以拆分为该点子树上的点和该点父亲节点方向的点，那么是否可以利用父亲节点呢？当然是可以的，因为子节点和父亲节点的差必然是1，那么可以利用父亲节点距离k-1以内的点，再加上该点子树上**距离为**k-1，和距离为k的点即可（以为这些点距离父亲节点的距离大于k-1）。

这样就可以得到转移方程：

## **dp[i][j]=dp[fa[i]][j-1]+son[i][j]+son[i][j-1]**

i为当前节点，fa[i]为父亲节点，j表示距离j以内的点的权值和，son表示i的子树上距离i为j的点的权值和。

我们可以可以用第一个dfs来维护fa数组和son数组，只需要每次往上遍历k个父亲节点即可

```cpp
son[x][0]=inp[x];
int now=fa[x];
for(int i=1;i<=k;i++)
{
	son[now][i]+=inp[x];
	now=fa[now];
}
```
由于k的值很小，这完全是可以接受的。

接下来在dfs2中利用换根dp的思想，充分利用父亲节点以及被算出来的值和之前维护的son数组，就可以得到结果。

时间复杂度O(kn)，当然也可以把k理解成常数，复杂度实际上就是O(n)。

完整代码如下
```cpp
#include<iostream>
#include<vector>
#include<stdio.h>
using namespace std;
#define ll long long
#define N 100005
vector<int>edge[N];
int fa[N],inp[N];
int son[N][25],dp[N][25];
int n,k;
void dfs1(int x)
{
	son[x][0]=inp[x];
	int now=fa[x];
	for(int i=1;i<=k;i++)
	{
		son[now][i]+=inp[x];
		now=fa[now];
	}
	for(int i=0;i<edge[x].size();i++)
	{
		int to=edge[x][i];
		if(to==fa[x])
			continue;
		fa[to]=x;
		dfs1(to);
	}
}
void dfs2(int x)
{
	for(int i=0;i<edge[x].size();i++)
	{
		int to=edge[x][i];
		if(to==fa[x])
			continue;
		dp[to][0]=inp[to];
		for(int j=1;j<=k;j++)
			dp[to][j]=dp[x][j-1]+son[to][j]+son[to][j-1];
		dfs2(to);
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&inp[i]);
	dfs1(1);
	dp[1][0]=inp[1];
	for(int i=1;i<=k;i++)
		dp[1][i]=son[1][i]+dp[1][i-1];
	dfs2(1);
	for(int i=1;i<=n;i++)
		printf("%d\n",dp[i][k]);
}
```


---

## 作者：jins3599 (赞：3)

树形dp + 容斥

首先我们可以想到设计方程$f(i,j)$代表结点$i$周围$j$步（是$j$步而不是$j$步内）的所有儿子和。

于是转移方程显然：$f(i,j)=\sum f(v,j-1)$，其中$v$为$j$的相邻结点。

不过显然是有重复记录的，而且不好枚举，我们可以考虑一下容斥原理。

首先我们从下往上转移，用所有的儿子来转移父亲，

然后再从上往下转移，用所有的父亲来转移儿子。

然后显然其中是有重复的部分的，重复在哪里?

我们考虑我们在转移结点$v$的时候，他的子节点是先转移过一遍的，也就是以他为根的子树中$k$步内的结点已经转移好了，然后再让他继承他父亲的状态$f(fa,k-1)$时，我们发现他当前父亲的状态是包括了$f(v,k-2)$的，于是在转移之前减掉就好了。

代码就比较好实现了。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int f[N][25];
int n , k;
int cnt , head[N], a[N] , ans;
struct Edge {
	int to , nxt;
}e[N << 1];
void add(int u , int v) {
	e[++ cnt].to = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

void dfs1(int now , int fa) {
	for(int i = head[now] ; i ; i = e[i].nxt) {
		int v = e[i].to;
		if(v == fa) continue;
		dfs1(v , now);
		for(int j = 1 ; j <= k ; j ++)
			f[now][j] += f[v][j - 1]; 
	}
}

void dfs2(int now , int fa) {
	for(int i = head[now] ; i ; i = e[i].nxt) {
		int v = e[i].to;
		if(v == fa) continue;
		for(int j = k ; j >= 2 ; j --)
			f[v][j] -= f[v][j - 2];
		for(int j = 1 ; j <= k ; j ++)	
			f[v][j] += f[now][j - 1];
		dfs2(v , now);	
	}
}

int main () {
	scanf("%d %d" , &n , &k);
	for(int i = 1 ; i <= n - 1 ; i ++) {
		int u , v; scanf("%d %d" , &u, &v);
		add(u , v); add(v , u);
	}
	for(int i = 1 ; i <= n ; i ++) scanf("%d" , a + i) , f[i][0] = a[i];
	dfs1(1 , 1);
	dfs2(1 , 1);
	for(int i = 1 ; i <= n ; i ++) {
		ans = 0;
		for(int j = 0 ; j <= k ; j ++) ans += f[i][j];
		printf("%d\n" , ans);
	}
	return 0;
} 
```

---

## 作者：ljc20020730 (赞：3)

题目简述：给出一棵n个点的树，每个点上有Ci头牛，问每个点k步范围内各有多少头牛。

显然朴素的算法是要超时的，那么我们考虑是否存在重复计算的情况，

显然是有前缀情况的出现，我们考虑树形dp
- 状态：f[u][j]表示节点u像外恰好延生j步能覆盖的牛的数目

首先两个状态转移比较容易想到，题解中也有人阐述了
- f[u][j]=singma{f[v][j-1]} |1<=j<=w(w表示最远的长度,v为u的子节点) 

- f[v][j]=singma{f[u][j-1]} |1<=j<=w(w表示最远的长度,v为u的子节点)

如果你真的是按照上述思路写一个dp，你会发现，有重复，
你的输出是这样的
```
15
23
19
14
13
17
```
你去对照标准输出，发现只有第一个是对的，其他都多了。

好了知道有重复了，但是重复在哪里？

我们分析下：

- 第一遍dfs你算出f[i][j]从i点向下j步及以内的权值和

- 第二遍dfs你算出f[i][j]从i点向儿子走0-j步，像父亲走j步的权值和

- 那么重复算的那一部分就是节点u向儿子走0到j-2步的权值和，

究其原因就是这个点和j步以上的那个父亲节点是不计算在步数j中的，所以要减去。

```
# include <bits/stdc++.h>
using namespace std;
const int root=1,MAXN=100001;
struct rec{
	int pre,to;
}a[2*MAXN];
int head[MAXN],f[MAXN][21],w,n,tot=0,c[MAXN];
bool vis[MAXN];
void adde(int u,int v)
{
	a[++tot].pre=head[u];
	a[tot].to=v;
	head[u]=tot;
}
void dfs1(int u)
{
	vis[u]=true;
	for (int i=head[u];i!=0;i=a[i].pre)
	{
		int v=a[i].to; if (vis[v]) continue;
		dfs1(v);
		for (int j=1;j<=w;j++) f[u][j]+=f[v][j-1];
	}
}
void dfs2(int u)
{
	vis[u]=true;
	for (int i=head[u];i!=0;i=a[i].pre)
	{
		int v=a[i].to;if (vis[v]) continue;
		//节点u向儿子走 0-j 步，u向 父亲走0-j
		//重复算一次：向儿子 j-2步及以内（减掉）
		for (int j=w;j>=2;j--) f[v][j]-=f[v][j-2];
		for (int j=1;j<=w;j++) f[v][j]+=f[u][j-1];
		dfs2(v);
	}
}
int main()
{
	scanf("%d%d",&n,&w);
	int u,v;
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d",&u,&v);
		adde(u,v); adde(v,u);
	}
	memset(f,0,sizeof(f));
	for (int i=1;i<=n;i++) {
		scanf("%d",&c[i]);
		f[i][0]=c[i];
	}
	memset(vis,false,sizeof(vis));
	dfs1(root);
	memset(vis,false,sizeof(vis));
	dfs2(root);
	for (int i=1;i<=n;i++) {
		int ans=0;
		for(int j=0;j<=w;j++) ans+=f[i][j];
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：GoAway (赞：3)

```cpp
\documentclass[UTF8]{ctexart}
\title{[USACO12FEB]Nearby Cows solution}
\author{GoAway}
\usepackage{color}
\usepackage{xcolor}
\definecolor{keywordcolor}{rgb}{0.8,0.1,0.5}
\usepackage{listings}
\lstset{breaklines}
\lstset{extendedchars=false}
\lstset{language=C++,
    keywordstyle=\color{keywordcolor} \bfseries, 
    identifierstyle=,
    basicstyle=\ttfamily, 
    commentstyle=\color{blue} \textit,
    stringstyle=\ttfamily, 
    showstringspaces=false,
    frame=shadowbox
    captionpos=b
}
\begin{document}
\maketitle{}
```
这道题分两步处理
\section{第一步}

    \paragraph{}先转化成有根树，然后再计算出以每个点为根的子树中 \textbf{往下}走j步得到的牛的总数。

树形DP完成，弱智公式

$$
f[x][j] = \sum\_{u \in \\{son\_x\\} } f[u][j-1]  + f[x][0]

$$
\paragraph{}时间复杂度$ O( n \times k ) $




```cpp
\section{第二步}
    \paragraph{} 每个点往下的已经算好了，接下来就算往上以及拐来拐去的。反正 $ k $ 不大，暴力往上跳 $ k $ 步就行了，跳的时候统计。
    \paragraph{}如何统计呢？
    \paragraph{}假设现在跳了 $ j $ 步到达点 $ u $，那么再加上 $ f[u][k-j] $，有一部分被重复加了，再减掉，就是 $ f[ son_u ][k-j-1] $，其中 $ son_u $代表在往上跳的过程中经过的$u$的儿子，不难发现是唯一的。
    \paragraph{}时间复杂度$ O( n \times k ) $
\section{代码}
\begin{lstlisting}
#include <bits/stdc++.h>
using namespace std ;
void Read ( int &x, char c = getchar() ) {
    for ( x = 0 ; !isdigit(c) ; c = getchar() ) ;
    for ( ; isdigit(c) ; c = getchar() ) x = 10*x + c - '0' ;
}
const int maxn = 1e5+5, maxm = 25 ;
int n, m, f[maxn][maxm] ;
int e, be[maxn], nxt[maxn<<1], to[maxn<<1], fa[maxn] ;
void add ( int x, int y ) {
    to[++e] = y ;
    nxt[e] = be[x] ;
    be[x] = e ;
}
void dfs ( int x ) {
    int i, u, j ;
    for ( i = be[x] ; i ; i = nxt[i] ) {
        u = to[i] ;
        if ( u == fa[x] ) continue ;
        fa[u] = x ;
        dfs(u) ;
    }
    for ( j = 1 ; j <= m ; j ++ ) {
        f[x][j] = f[x][0] ;
        for ( i = be[x] ; i ; i = nxt[i] )
            if ( to[i] != fa[x] ) f[x][j] += f[to[i]][j-1] ;
    }
}
int calc ( int x ) {
    int i, u, v = 0, stp = m ;
    v = f[x][m] ;
    for ( u = fa[x] ; fa[x] && stp>=0 ; x = u, u = fa[x], stp-- ) {
        v += f[u][stp-1]-f[x][stp-2] ;
    }
    return v ;
}
int main() {
    int i, j, k, x, y ;
    Read(n) ; Read(m) ;
    for ( i = 1 ; i < n ; i ++ ) {
        Read(x) ; Read(y) ;
        add ( x, y ) ;
        add ( y, x ) ;
    }
    for ( i = 1 ; i <= n ; i ++ ) Read(f[i][0]) ;
    dfs(1) ;
    for ( i = 1 ; i <= n ; i ++ ) printf ( "%d\n", calc(i) ) ;
    return 0 ;
}
\end{lstlisting}
\end{document}
```

---

## 作者：xzyxzy (赞：3)

这道题我花了很久才做出来，自己一开始也没想清楚，求助了大佬们

###这道题有两种思路

一种在大佬的博客上，我算是明白了，干脆贴上博客吧，我将也讲不清**笑哭**


http://blog.csdn.net/oi\_konnyaku/article/details/75449966

另一种呢，是比较容易想到的，但也很容易出错的

用到了链式前向星和容斥原理

首先链式前向星呢，是个高级的东西，百度上第一个候选的博客挺好的

实际上也就是记录边的信息，记录该边同起点异终点的边的存储位置和该边的权值以及指向的终点

这个不太好理解，模拟也需要一定的耐心，但是搞懂了真的很好用

这是我第一道用链式前向星做的题，比较简单的例题大家可以去做一下##二叉苹果数


容斥原理呢，我也不太清楚，百度上是这么说的

 ![](https://cdn.luogu.com.cn/upload/pic/6532.png) 

然后来了一大堆看不懂的sigma等等，看得懂的只有这个

 ![](https://cdn.luogu.com.cn/upload/pic/6533.png) 

所以大概明白了

递推（DP）公式就能够理解了

具体的吧，建议首次用链式前向星可以照着代码敲

我的注释也是比较详尽的啦~\(≧▽≦)/~（因为第一遍自己也没搞清楚）



```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int read()//读入优化
{
    char ch=getchar();
    while(ch>'9'||ch<'0') ch=getchar();
    int h=0;
    while(ch>='0'&&ch<='9')
    {
        h=h*10+ch-'0';
        ch=getchar();
    }
    return h;
}
int f[100001][21];//f[i][j]表示距离第i块地(正好)j步的牛的头数 
int w[100001];//存储结点的牛的头数 
struct qxx{
    int to;
    int next;//链式前向星 
}a[200002];
int head[100001];
int cnt=0;//计数 
int fa[100001]; 
int n,k; 
void add(int x,int y)
{
    a[++cnt].to=y;
    a[cnt].next=head[x];
    head[x]=cnt;
}
void dfs(int x,int y)//实际上这个函数默认1为根，进行树形深搜 
{
    fa[x]=y;
    f[x][0]=w[x];//当前结点走0步
    for(int i=head[x];i!=-1;i=a[i].next)//枚举同起点异终点的边 
```
{//申明此时变量：x表示当前结点，fa表示x的父结点
//i表示枚举以x为起点的边的编号，a[i].to表示第i条边的终点(x的子结点)


```cpp
     //a[i].next前向星指向下一条以x为起点的边 
        if(a[i].to!=y)
        {
            dfs(a[i].to,x);//深搜子结点 
            for(int j=1;j<=k;j++)
            {
                f[x][j]+=f[a[i].to][j-1];//先加上子树上的牛 
            }
        }
    } 
}
int main()
{
//    freopen("a.in","r",stdin);
//    freopen("a.out","w",stdout);
    n=read();k=read();
    for(int i=0;i<=100000;i++) head[i]=-1; 
    for(int i=1;i<=n-1;i++)
    {
        int x,y;
        x=read();
        y=read();
        add(x,y);
        add(y,x);//双向存储链式前向星 
    }
    for(int i=1;i<=n;i++) w[i]=read();//读取每个结点的牛的数量
    dfs(1,0); 
//    for(int i=1;i<=n;i++) for(int w=0;w<=k;w++) cout<<"f["<<i<<"]["<<w<<"]="<<f[i][w]<<endl; 
    for(int i=1;i<=n;i++)
        for(int w=1;w<=k;w++)
            f[i][w]+=f[i][w-1];//计算前缀和，改变f的意义
//    for(int i=1;i<=n;i++) for(int w=0;w<=k;w++) cout<<"f["<<i<<"]["<<w<<"]="<<f[i][w]<<endl;//这两句用来调试的
    //现在f[i][j]表示在i结点的子树上距离为j的牛数
    for(int i=1;i<=n;i++)//顺序枚举田地 
    {
        int ans=f[i][k];//初值赋为从1开始，子树上距离为k以内的牛数 
        int j=k;//
        int x=i;//
        //实际上一整句话的意思是
        //运用容斥原理，从x结点开始，ans为向父结点走0~k步再加上父结点向下走k~0步的和，再减去重复算的(重复算的是子树上走j-2步的地方)
        //比如说按样例，当i为2时，x=2，ans首先为3+4+6+2=15，keep on，ans+=f[fa[2](1)][j-1(1)],ans+=1+2+5=8,ans-=f[2][0](2),算得ans=21
        //实际上就是通过找父结点拓展出兄弟结点的情况，由于父结点的状态包括了该子树的状态，故要减 
        while(x!=1&&j!=0)
        {
            ans+=f[fa[x]][j-1];
            if(j>=2) ans-=f[x][j-2];
            x=fa[x];
            j--;
        }
        printf("%d\n",ans); 
    } 
    return 0;
}
```

---

## 作者：durex_com (赞：2)

一看就知道是一道**~~树形dp~~**

用伪容斥原理

$dp[v][i][1]=dp[u][i-1][0]-dp[v][i-2][0]$

$dp[i][j][0]$表示$i$在$j$的距离内的结点权值和。

$dp[i][j][1]$表示对于$i$的兄弟姐妹节点距离为$<=j-1$的权值数；

最后统计答案。

```cpp
#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int maxn=100001;
int sum[maxn],head[maxn],father[maxn],dp[maxn][21][2];  
int n,m,cnt=0;
struct zk
{ 
   int u,v,next;
}e[maxn*2];
void add(int u,int v)
{
	e[cnt].u=u;
    e[cnt].v=v;
	e[cnt].next=head[u];
	head[u]=cnt++;
}
void dfs(int u,int fa)
{
    int i,j,k,sum=0;
    father[u]=fa;
    for(int k=1;k<=m;k++) 
	dp[u][k][0]=dp[u][0][0];
    for(i=head[u];i!=-1;i=e[i].next)
    {
        int v=e[i].v;
        if(v==fa) continue;
        dfs(v,u);
        for(int k=1;k<=m;k++) 
		dp[u][k][0]+=dp[v][k-1][0];
    }
    for(i=head[u];i!=-1;i=e[i].next)
    {
        int v=e[i].v;
        if(v==fa) continue;
        dp[v][1][1]=dp[u][0][0]; 
        for(int k=2;k<=m;k++)
		dp[v][k][1]=dp[u][k-1][0]-dp[v][k-2][0];
    }
}
int main()
{
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v);
		add(v,u);
    }
    for(int i=1;i<=n;i++) 
	scanf("%d",&dp[i][0][0]);
    dfs(1,0);
    for(int i=1;i<=n;i++)  
    {
        sum[i]=dp[i][m][0];
        int u=i,v;
        for(int j=1;j<=m;j++)
        {
            sum[i]+=dp[u][m-j+1][1];
            u=father[u];
            if(father[u]==0) break;
        }
    } 
    for(int i=1;i<=n;i++) 
	printf("%d\n",sum[i]);
    return 0;
}
```

---

## 作者：巨型方块 (赞：2)

首先感谢楼下大神提供思路，现在我压缩一下楼下的；

我们只弄一个f[i][j]表示第i点时，向子节点走0~j步所有可以到达的点的值的和；

那么显然f[i][0]=w[i];

这个数组怎么更新，自己想吧，也可以看我代码，我是分两步去搞f数组的；

那么对于一个点x；

显然的f[x][k]时答案的一部分

但是这样仅仅算了x向下走；

如果向上走一步再向下走

f[fa[x]][k-1]-f[x][k-2];

向上走两步亦是如此，我们可以用while来搞

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#define Ll long long
using namespace std;
struct cs{
    int to,next;
}a[200001];
int head[100001],w[100001],fa[100001],f[100001][25];//w[i]表示i节点的值，fa[i]是i的父节点, 
int m,n,x,y,z,ll;
void init(int x,int y){
    ll++;
    a[ll].to=y;
    a[ll].next=head[x];
    head[x]=ll;
}
void dfs(int x,int y){//当前是x点，其父节点是y 
    fa[x]=y;
    f[x][0]=w[x];
    for(int k=head[x];k;k=a[k].next)
    if(a[k].to!=y){
        dfs(a[k].to,x);
        for(int j=1;j<=m;j++)
        f[x][j]+=f[a[k].to][j-1];
    }    
}
void cfb(int x){
    int ans=0,k=m;
    ans=f[x][m];
    while(x!=1&&k){
        ans+=f[fa[x]][--k];
        if(k)ans-=f[x][k-1];
        x=fa[x];
    }
    printf("%d\n",ans);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;i++)scanf("%d%d",&x,&y),init(x,y),init(y,x);
    for(int i=1;i<=n;i++)scanf("%d",&w[i]);
    dfs(1,-1);//1的父节点是-1好了 
    for(int i=1;i<=n;i++)//dfs时f[i][j]是第i点刚好走j步，现在求前缀和 
    for(int j=1;j<=m;j++)f[i][j]+=f[i][j-1];
    for(int i=1;i<=n;i++)cfb(i);
}

```

---

