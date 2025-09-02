# Puzzles

## 题目描述

Barney lives in country USC (United States of Charzeh). USC has $ n $ cities numbered from $ 1 $ through $ n $ and $ n-1 $ roads between them. Cities and roads of USC form a rooted tree (Barney's not sure why it is rooted). Root of the tree is the city number $ 1 $ . Thus if one will start his journey from city $ 1 $ , he can visit any city he wants by following roads.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696B/ba3e1e6f719802c9fe4b318c8d8513024bc088eb.png)Some girl has stolen Barney's heart, and Barney wants to find her. He starts looking for in the root of the tree and (since he is Barney Stinson not a random guy), he uses a random DFS to search in the cities. A pseudo code of this algorithm is as follows:

```plain
let starting_time be an array of length n
current_time = 0
dfs(v):
	current_time = current_time + 1
	starting_time[v] = current_time
	shuffle children[v] randomly (each permutation with equal possibility)
	// children[v] is vector of children cities of city v
	for u in children[v]:
		dfs(u)
```

As told before, Barney will start his journey in the root of the tree (equivalent to call dfs(1)).

Now Barney needs to pack a backpack and so he wants to know more about his upcoming journey: for every city $ i $ , Barney wants to know the expected value of starting\_time\[i\]. He's a friend of Jon Snow and knows nothing, that's why he asked for your help.

## 样例 #1

### 输入

```
7
1 2 1 1 4 4
```

### 输出

```
1.0 4.0 5.0 3.5 4.5 5.0 5.0 
```

## 样例 #2

### 输入

```
12
1 1 2 2 4 4 3 3 1 10 8
```

### 输出

```
1.0 5.0 5.5 6.5 7.5 8.0 8.0 7.0 7.5 6.5 7.5 8.0 
```

# 题解

## 作者：Terac (赞：6)

[$\texttt{Link}$](https://www.luogu.com.cn/problem/CF696B)    

## 题意  

给定一棵 $n$ 个节点的树，对它进行 DFS，每次 DFS 随机排列当前节点的所有儿子，求每个点的期望时间戳。  

数据范围： $1\le n\le10^5$  

## 做法  
以下用 $f_x$ 表示点 $x$ 时间戳的期望值，$siz_x$ 表示点 $x$ 的子树大小。

对于节点 $u$，显然他会继承其父节点 $fa$ 的时间戳为基础，再加上兄弟节点的贡献。  

对于点 $u$ 的兄弟节点 $v$，先被搜概率是相等的，这个结论很显然，因为将 DFS 顺序反转后两种时间戳大小关系是一一对应的，所以点 $v$ 对点 $u$ 的贡献即为 $\frac{siz_v}{2}$。又因为 $\sum\limits_{v\in son(fa)}siz_v=siz_{fa}-siz_u-1$，所以对于点 $u$， $f_u=f_{fa}+\frac{siz_{fa}-siz_u-1}{2}+1$。  

然后树形 DP  即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, siz[N];
double f[N];
struct edge {
	int to, nxt;
} e[N];
int head[N], cnt;
void add(int u, int v) {
	e[++cnt] = (edge){v, head[u]};
	head[u] = cnt;
}
void dfs1(int u) {
	siz[u] = 1;
	for(int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].to;
		dfs1(v);
		siz[u] += siz[v];
	}
}
void dfs2(int u, int fa) {
	if(fa) f[u] = f[fa] + (siz[fa] - siz[u] - 1) * 0.5 + 1;
	for(int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].to;
		dfs2(v, u);
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 2, u; i <= n; i++)
		scanf("%d", &u), add(u, i);
	dfs1(1);
	f[1] = 1.;
	dfs2(1, 0);
	for(int i = 1; i <= n; i++) printf("%.1lf ", f[i]);
	return 0;
}
```


---

## 作者：_xxxxx_ (赞：2)

### 题面

给你一段关于 `dfs` 求时间戳的代码，遍历节点的顺序是随机的，问每个点的时间戳期望值。

### 分析

树形 dp 求期望。

定义节点 $u$ 的期望为 $dp_u$。

我们对于一个节点 $u$，向上看他的时间戳是在他的父亲节点下的，因此 $dp_u$ 会加上 $dp_{fa_u}$。

接下来考虑兄弟，因为随机，所以每个更深的点对 $u$ 的贡献为 $\frac{1}{2}$。我们可以存下每个节点的子树节点个数 $siz$，那除 $u$ 之外的兄弟子侄的贡献则为 $siz_{fa_u}-siz_u-1$，父亲子树减去子树 $u$ 即为剩下的节点，减一是因为父亲本身。

最后不要忘了加上 $u$ 自己贡献的 $1$。

### 代码

```cpp
#include <iostream>
#include <cmath>
#include <string.h>
#include <queue>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n;
int head[N], ne[N], to[N], id;
void add(int x, int y)
{
	to[++id] = y;
	ne[id] = head[x];
	head[x] = id;
}
double dp[N];
int siz[N];
void dfs1(int u, int fa)
{
	siz[u] = 1;
	for(int i = head[u]; i; i = ne[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs1(v, u);
		siz[u] += siz[v];
	}
}
void dfs2(int u, int fa)
{
	if(fa)
	{
		dp[u] = dp[fa] + 0.5 * (siz[fa] - siz[u] - 1) + 1;
	}
	for(int i = head[u]; i; i = ne[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs2(v, u);
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
//	cout.tie(0);
	cin >> n;
	for(int i = 2; i <= n; i++)
	{
		int x;
		cin >> x;
		add(i, x);
		add(x, i); 
	}
	dfs1(1, 0);
	dp[1] = 1.0;
	dfs2(1, 0);
	for(int i = 1; i <= n; i++)
	{
		printf("%.1lf ", dp[i]);
	}
	return 0;
}
```

---

## 作者：daiarineko (赞：2)

# 题解 - 10445 Puzzles

## Link - 链接

[Luogu RMJ CF696B](https://www.luogu.com.cn/problem/CF696B)  
[CF 696B](http://codeforces.com/problemset/problem/696/B)

## Description - 题目简述

现有如下算法：

```plain
let starting_time be an array of length n
current_time = 0
dfs(v):
    current_time = current_time + 1
    starting_time[v] = current_time
    shuffle children[v] randomly (each permutation with equal possibility)
    // children[v] is vector of children cities of city v
    for u in children[v]:
        dfs(u)
dfs(1)
```

即，从根节点开始，对于每个节点按随机顺序搜索子节点，请输出每个节点 u 的时间戳（`starting_time[u]`）的期望值。

## Solution - 题解

首先，设节点 u 的期望时间戳为 $dp_u$。

一个节点的期望时间戳可以按如下方式计算：

$dp_u = dp_{\text{fa}_u} + 1 + \text{something}$

$dp_{\text{fa}_u}$ 是来自于父亲节点的贡献，$1$ 是来自于 $u$ 本身的贡献，$\text{something}$ 即来自于兄弟节点和子节点的贡献，是需要重点探讨的。

可证，对于 $fa$ 的子节点 $u,v$，$u$ 先于 $v$ 被搜索的概率即为 $\frac{1}{2}$，反之亦成立。

那么，对于 $fa$ 除 $u$ 以外所有子节点 $v$，以上说法都成立，即 $v$ 对 $u$ 的贡献是 $\text{size}_v \times \frac{1}{2} + 0 = \frac{\text{size}_v}{2}$。

继而，$\text{something}$ 即为 $\sum\limits_{v\in \text{sons}_{fa}, v\neq u}\frac{\text{size}_v}{2}$。

这样的形式不太好看，不方便进一步化简。

$$
\begin{aligned}
& \sum\limits_{v\in \text{sons}_{fa}, v\neq u}\frac{\text{size}_v}{2}\\
= & \frac{\sum\limits_{v\in \text{sons}_{fa}, v\neq u}\text{size}_v}{2}\\
= & \frac{\text{size}_{fa} - \text{size}_u - 1}{2}\\
\end{aligned}
$$

注意第二次化简。为什么可以这样化简呢？

注意到，我们需要统计的是 $u$ 所有兄弟节点的子树大小之和。这恰好是 $fa$ 子树大小 - $u$ 子树大小 - $fa$ 本身（$1$）。

**那么，整个 dp 方程则为 $dp_u = dp_{\text{fa}_u} + 1 + \frac{\text{size}_{fa} - \text{size}_u - 1}{2}$。**

两次 dfs，第一次预处理 $\text{size}$，第二次 DP 即可。

### 示例代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 102400;
struct Edge
{
    int v, next;
} e[maxn << 1];
int head[maxn], cnt;
int n, m;
void add(int u, int v)
{
    e[++cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
int siz[maxn];
double dp[maxn];
void pre(int u, int fa)
{
    siz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if (v == fa)
            continue;
        pre(v, u);
        siz[u] += siz[v];
    }
    return;
}
void solve(int u, int fa)
{
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if (v == fa)
            continue;
        dp[v] = dp[u] + 1.0 + (siz[u] - siz[v] - 1) * 0.5;
        solve(v, u);
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i)
    {
        scanf("%d", &m);
        add(i, m);
        add(m, i);
    }
    pre(1, 0);
    dp[1] = 1;
    solve(1, 0);
    for (int i = 1; i <= n; ++i)
        printf("%.8lf ", dp[i]);
    printf("\n");
    return 0;
}
```


---

## 作者：shiroi (赞：2)

### Description

给出一棵树，按一定算法DFS整棵树，求出每个节点期望的时间戳。

### Solution

一道很好的概率期望dp题目。

设每个点的期望时间戳为ans，观察题目可以发现由于是随机进行DFS，每个节点的ans只和其父亲的ans和它兄弟的子树大小有关。对于父节点的处理相似，我们可以先只考虑兄弟节点之间的情况。

考虑设节点父亲的儿子个数为t（包括节点本身），如果其在当前所有兄弟的dfs序中排名为 i，那么总的贡献就是 $\frac{i-1}{t-1}$ 。对其求和之后可得出转移方程为

$$
ans[x]=\frac{size[fa]-size[x]-1}{2}+ans[fa]+1
$$

两遍dfs即可得出解。


```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0,f=1,c=getchar();
	while(c<48) c=='-'&&(f=-1),c=getchar();
	while(c>47) x=x*10+c-'0',c=getchar();
	return x*f;
}

const int MAXN = 100005;
std::vector<int> G[MAXN];
int size[MAXN],sum[MAXN];
double ans[MAXN];
int n;

inline void addedge(int u,int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

void dfs(int x,int fa)
{
	size[x]=1;
	for(int &y : G[x])
		if(y^fa) dfs(y,x),size[x]+=size[y];
	for(int &y : G[x])
		if(y^fa) sum[y]=size[x]-size[y]-1;
}

inline void dp(int x,int fa)
{
	for(int &y : G[x])
		if(y^fa) ans[y]=ans[x]+1+0.5*sum[y],dp(y,x);
}

int main(int argc, char const *argv[])
{
	n=read();
	for(int i=1; i<n; ++i)
		addedge(read(),i+1);
	ans[1]=1; dfs(1,1); dp(1,1);
	for(int i=1; i<=n; ++i)
		printf("%.1lf%c", ans[i]," \n"[i==n]);
	return 0;
}
```



---

## 作者：Strelitzia (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF696B)

---

其实上手这道题感觉还是不是非常难，定义 $dp_i$ 为到第 $i$ 个点的期望。

所以就可以知道，一个节点的期望肯定与它的爸爸有关，

所以我们可得出要先算当前节点的期望，再搜子树的规律。

设爸爸是 $u$ ,它的一个儿子是 $v$ 其他儿子是 $v'$ ,其他儿子对 $v$ 的贡献是$\dfrac{size_{v'}}{2}$，就可推出:

$\ \ \ \ \ \ \ \ \ \ \ $ $dp_v = dp_x + (sz_x - sz_v - 1) / 2 + 1$

$sz_x - sz_v - 1$ 是其他的子树大小的和。

```cpp
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int n,sz[100005];
double dp[100005];
vector<int> g[100005];

void dfs1(int x,int fa) {
	sz[x] = 1;
	for (int i = 0 ; i < g[x].size() ; ++ i) {
		int v = g[x][i];
		dfs1(v,x);
		sz[x] += sz[v];
	}
}

void dfs(int x,int fa) {
	for (int i = 0 ; i < g[x].size() ; ++ i) {
		int v = g[x][i];
		dp[v] = dp[x] + (sz[x] - sz[v] - 1.0) * 1.0 / 2 + 1;
		dfs(v,x);
	}
}

int main () {
	read(n);
	int x;
	for (int i = 2 ; i <= n ; ++ i) {
		read(x);
		g[x].push_back(i);
	}
	dp[1] = 1;
	dfs1(1,0);
	dfs(1,0);
	for (int i = 1 ; i <= n ; ++ i) {
		printf("%.1lf ",dp[i]);
	}
	return 0;
}
```

---

## 作者：白鲟 (赞：1)

## 前言
若是显示有问题就来蒟蒻的[博客](https://www.luogu.com.cn/blog/bzlz-zdx/solution-cf696b)看看吧！~~没有问题也可以看看咯！~~

## 题意简述
从根结点开始，按照每次随机进入一个未进入过的儿子的策略，深度优先遍历一棵树，求访问每个结点的期望时间。

## 题目分析
首先容易发现，对于任意结点，访问它的期望时间与其父结点的期望访问时间和在它之前访问的兄弟结点的期望访问时间有关。其父结点的期望访问时间和这个问题是一个同样结构的问题。因此，我们需要解决的就是在它之前访问的兄弟结点的期望访问时间。  

究竟有哪些兄弟结点在这个结点之前访问呢？~~这是个好问题。~~ 对于期望的问题，问题的思考应该转为另一个方向。设以结点 $x$ 为根结点的子树大小为 $\operatorname{size}(x)$，容易知道，如果结点 $x$ 的兄弟结点 $i$ 比其先访问，那么它会使得结点 $x$ 的期望访问时间增加 $\operatorname{size}(i)$。设结点 $x$ 的期望访问时间为 $\operatorname{E}(x)$，父结点为$\operatorname{father}(x)$，其每个兄弟结点在它之前访问到的概率为 $\operatorname{P}(i)$，可以得到以下公式：
$$
\operatorname{E}(x)=\operatorname{E}(\operatorname{father}(x))+\sum \operatorname{P}(i)\operatorname{size}(i)+1
$$
那么 $\operatorname{P}(i)$ 到底是多少呢？由于每个兄弟结点 $i$ 与 $x$ 的关系只有两种可能：在其之前与在其之后，故所有 $\operatorname{P}(i)$ 均等于 $\dfrac{1}{2}$。  

这时我们可以化简式子如下：
$$
\operatorname{E}(x)=\operatorname{E}(\operatorname{father}(x))+\dfrac{\sum\operatorname{size}(i)}{2}+1
$$
对于 $\sum\operatorname{size}(i)$ 的快速计算，可以得到以下式子：
$$
\sum\operatorname{size}(i)=\operatorname{size}(\operatorname{father}(x))-\operatorname{size}(x)-1
$$
故可以一遍 dfs 预处理 $\operatorname{size}(x)$，然后再一遍统计答案。
## 代码
注意边界：$\operatorname{E}(1)=1$。
```cpp
#include<cstdio>
using namespace std;
int n,tot,father[100001],size[100001],head[100001],go[100001],suc[100001];
double f[100001];
void dfs1(int x)
{
	size[x]=1;
	for(int i=head[x];i;i=suc[i])
	{
		dfs1(go[i]);
		size[x]+=size[go[i]];
	}
	return;	
}
void dfs2(int x)
{
	f[x]=f[father[x]]+(size[father[x]]-size[x]-1)/2.0+1;
	for(int i=head[x];i;i=suc[i])
		dfs2(go[i]);
	return;
}
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;++i)
	{
		scanf("%d",&father[i]);
		go[++tot]=i;
		suc[tot]=head[father[i]];
		head[father[i]]=tot;
		++size[head[i]];
	}
	dfs1(1);
	size[0]=size[1]+1;//使得f[1]满足边界
	dfs2(1);
	for(int i=1;i<=n;++i)
		printf("%.1lf ",f[i]);
	return 0;
}
```

---

## 作者：porse114514 (赞：1)

# [CF696B Puzzles](https://www.luogu.com.cn/problem/CF696B) 题解
这是一道有点水的树形 dp 题。

对于根节点为 $u$ 的一个儿子 $now$，其他的每个儿子都有一半的概率排在他前面，一半的概率排在他后面，所以我们可以得到方程：
$$dfn_{now}=dfn_u+1+\frac{size_u-1-size_{now}}{2}$$
其中，$dfn$ 是要求的答案，$size$ 是子树大小，右边的 $\large\frac{size_u-1-size_{now}}{2}$ 就是兄弟节点的数量。

所以我们只需要写两个 DFS，一个求出 $size$，一个求出 $dfn$ 即可。

时间复杂度只有 $O(n)$，$10^{5}$ 的数据完全够用了。

## Code（第一篇为邻接表，第二篇为链式前向星）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 100010;
int n,fa,sz[maxn];//变量名千万不要用size，虽然洛谷上没事，但如果写到OI比赛中，就会爆0 
double dfn[maxn];
vector<int> G[maxn];//邻接表（大佬好象都用链式前向星） 
void getsz(int u)
{
	sz[u] = 1;//不要忘了这一句 
	for(int i = 0;i < G[u].size();i++)
	{
		int now = G[u][i];
		getsz(now);
		sz[u] += sz[now];
		//要先递归再修改，要不然会寄 
	}
	return ; 
}
void getdfn(int u)
{
	for(int i = 0;i < G[u].size();i++)
	{
		int now = G[u][i];
		dfn[now] = dfn[u] + 1 + ((sz[u] - 1 - sz[now]) / 2.0);//注意这里一定是2.0而不是2，我当时就因为这里卡了好久 
		getdfn(now); 
		//要先递归再修改，要不然也会寄 
	}
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);//输入输出优化 
	cin >> n;
	for(int i = 2;i <= n;i++)
	{
		cin >> fa;
		G[fa].push_back(i);//单向边就够了，而且dfs还不用判边界 
	}
	getsz(1);
	dfn[1] = 1;//初始化 
	getdfn(1); 
	for(int i = 1;i <= n;i++)
	{
		printf("%.1lf ",dfn[i]);//看清楚题，保留一位小数，不要弄多了 
	}
	return 0;//养成return好习惯 
}
```
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 100010;
int n,fa,sz[maxn];//变量名千万不要用size，虽然洛谷上没事，但如果写到OI比赛中，就会爆0 
double dfn[maxn];
struct edge{ 
	int to,nxt;
}e[maxn];//链式前向星
int head[maxn],cnt = 0;
void add(int u, int v)//加边 
{
	e[++cnt] = {v,head[u]};
	head[u] = cnt;
}
void getsz(int u)
{
	sz[u] = 1;//不要忘了这一句 
	for(int i = head[u];i;i = e[i].nxt)
	{
		int now = e[i].to;
		getsz(now);
		sz[u] += sz[now];
		//要先递归再修改，要不然会寄 
	}
	return ; 
}
void getdfn(int u)
{
	for(int i = head[u];i;i = e[i].nxt)
	{
		int now = e[i].to;
		dfn[now] = dfn[u] + 1 + ((sz[u] - 1 - sz[now]) / 2.0);//注意这里一定是2.0而不是2，我当时就因为这里卡了好久 
		getdfn(now); 
		//要先递归再修改，要不然也会寄 
	}
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);//输入输出优化 
	cin >> n;
	for(int i = 2;i <= n;i++)
	{
		cin >> fa;
		add(fa,i);//单向边就够了，而且dfs还不用判边界 
	}
	getsz(1);
	dfn[1] = 1;//初始化 
	getdfn(1); 
	for(int i = 1;i <= n;i++)
	{
		printf("%.1lf ",dfn[i]);//看清楚题，保留一位小数，不要弄多了 
	}
	return 0;//养成return好习惯 
}
```

---

## 作者：ivyjiao (赞：0)

直接考虑 $dp_u$，当搜完 $fa_u$ 时，对于每一个 $v(v~\text{is a son of}~u,v\neq u)$，搜 $v$ 和 $u$ 的概率各为 $\dfrac 1 2$，若搜到的不是 $u$，再把每一个 $w(w~\text{is a son of}~v,w\neq v)$ 入队，对于队中每个点，搜到 $u$ 的概率仍为 $\dfrac 1 2$……以此类推可得：对于兄弟节点子树内每个节点，对于 $dp_u$ 的贡献都是 $\dfrac 1 2$，$u$ 对 $u$ 的贡献为 $1$。

$$dp_u=dp_{fa}+\dfrac{sz_{fa}-sz_u-1}{2}+1$$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int n,u,v,sz[N];
double dp[N];
vector<int>G[N];
void dfs(int u,int fa){
    sz[u]=1;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(v==fa) continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
}
void dfs1(int u,int fa){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(v==fa) continue;
        dp[v]=dp[u]+(sz[u]-sz[v]-1)*0.5+1;
        dfs1(v,u);
    }
}
int main(){
    cin>>n;
    for(int i=2;i<=n;i++){
        cin>>u;
        G[i].push_back(u);
        G[u].push_back(i);
    }
    dp[1]=1;
    dfs(1,0);
    dfs1(1,0);
    for(int i=1;i<=n;i++) printf("%.1f ",dp[i]);
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF696B)

# 前置知识

[树的遍历](https://oi-wiki.org/graph/tree-basic/#%E6%A0%91%E7%9A%84%E9%81%8D%E5%8E%86)

# 解法

目前在 $fa$ 节点时，搜到子节点 $x$ 和其他子节点的概率是相等的（因为不需要管具体是哪个节点），均为 $\frac{1}{2}$。

设 $f_{x}$ 表示 $x$ 时间戳的期望值，状态转移方程为 $f_{x}=1+f_{fa}+\frac{siz_{fa}-1-siz_{x}}{2}$，边界为 $f_{1}=1$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct node
{
    int nxt,to;
}e[100010];
int head[100010],siz[100010],cnt=0;
double f[100010];
void add(int u,int v)
{
    cnt++;
    e[cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
void dfs(int x)
{
    siz[x]=1;
    for(int i=head[x];i!=0;i=e[i].nxt)
    {
        dfs(e[i].to);
        siz[x]+=siz[e[i].to];
    }
}
void reroot(int x)
{
    for(int i=head[x];i!=0;i=e[i].nxt)
    {
        f[e[i].to]=1+f[x]+(siz[x]-1-siz[e[i].to])/2.0;
        reroot(e[i].to);
    }
}
int main()
{
    int n,u,v,i;
    cin>>n;
    for(i=2;i<=n;i++)
    {
        cin>>u;
        v=i;
        add(u,v);
    }
    dfs(1);
    f[1]=1;
    reroot(1);
    for(i=1;i<=n;i++)
    {
        printf("%.6lf ",f[i]);
    }
    return 0;
}
```

---

## 作者：pldzy (赞：0)

[传送门： 洛谷 CF696B Puzzles](https://www.luogu.com.cn/problem/CF696B) 

首先在此感谢 @[OneZzz6174](https://www.luogu.com.cn/user/368107) 大佬提供的学术支持。

## 思路

对于一个节点 $i$ 的期望时间戳，我们记为 $f_i$。

与其他题解所述相似，我们根据 $i$ 的父亲节点和它的兄弟节点可以得到 $f_i$。

具体地，它的兄弟节点对它的贡献（也是从它的父亲走到它这个节点的概率）是 $\dfrac{siz_{fa}-siz_u-1}{2}$。

然后就可以得到 $f_i=f_{fa} + \dfrac{siz_{fa}-siz_u-1}{2} + 1$。

其他挺多题解大致都说到这里。

所以我不妨来说说最后那个加一是怎么来的。

上面得到 $f_i$ 的式子中，中间那一项，无疑是父亲走到节点 $i$ 的概率，但是要注意此题求的是每个节点的期望**时间戳**，所以在走到节点 $i$ 的时候，时间戳要加一，这就是最后一个加一的缘由。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(register int i = a; i <= b; ++i)
#define per(i, a, b) for(register int i = a; i >= b; --i)
#define go(u) for(int i = hd[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
#define add(u, v) (e[++cnt].to = v, e[cnt].nxt = hd[u], hd[u] = cnt)
#define Add(u, v) (add(u, v), add(v, u))
typedef long long ll ;
inline int rd(){
	int x = 1, s = 0; char ch = getchar();
	while(ch < '0' or ch > '9'){if(ch == '-') x = -1; ch = getchar();}
	while(ch >= '0' and ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return x * s;
}
inline void wr(int x){
	if(x < 0) putchar('-'), x *= -1;
	if(x > 9) wr(x / 10);
	putchar(x % 10 + '0');
}
//----------------------------------//
const int maxn = 1e5 + 5;
int cnt, hd[maxn];
struct edge{
	int to, nxt;
}e[maxn << 1];
int n, siz[maxn];
double f[maxn];

inline void dfs1(int u, int fa){
	siz[u] = 1;
	go(u) if(v ^ fa)
		dfs1(v, u), siz[u] += siz[v];
}

inline void dfs2(int u, int fa){
	if(fa) f[u] = f[fa] + (siz[fa] - siz[u] - 1.0) / 2.0 + 1.0;
	go(u) if(v ^ fa) dfs2(v, u);
}

int main(){
	n = rd(); int x;
	rep(i, 2, n) x = rd(), Add(x, i);
	f[1] = 1.0, dfs1(1, 0), dfs2(1, 0);
	rep(i, 1, n) printf("%.1lf ", f[i]);
	return 0;
}
```


------------
感谢阅读。

辛苦管理员审核，如有问题烦请指出。

---

## 作者：Azazеl (赞：0)

### CF696B Puzzles  

---

#### 题意  

>$\ \ \ \ $ 给出一个打时间戳的 dfs,每次将所有儿子等概率重新排列后再遍历，求每个节点的期望时间戳。

---

#### 题解  

$~~~~$ 乍一看随机化无从下手，但考虑对于一个节点 $u$ ,若有一个子节点 $v$ ，考虑其他子节点 $v'(v' \not = v)$ 对它的贡献。若 $v'$ 在重排的序列中在它前面，对它的贡献就是 $\operatorname{siz(v')}$ ，其中 $\operatorname{siz(u)}$ 表示以 $u$ 为根的子树大小。  

$~~~~$ 再来考虑每个 $v'$ 在 $v$ 前面的概率，不难想到当有一种情况 $v'$ 在 $v$ 前面时，直接将序列翻转可以得到与之对应的 $v'$ 在 $v$ 后面的概率。因此 $v'$ 等概率在 $v$ 的前后，因此 $v'$ 对 $v$ 的时间戳的期望的贡献为 $\dfrac{\operatorname{siz(v')}}{2}$ 。总的贡献为所有 $u$ 的子节点中所有不是 $v$ 的子树大小和的一半，转换一下就是 $\dfrac{\operatorname{siz(u)-siz(v)-1}}{2}$.因此 $dp$ 转移即可

$~~~~$ 设：$dp_{u}$ 表示 $u$ 节点的期望时间戳，若 $u$ 的父节点为 $fa$ 则有：  

$$
dp_{u}=dp_{fa}+1+\dfrac{\operatorname{siz(u)-siz(v)-1}}{2}
$$

---

#### 代码  

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
vector <int> G[100005];
int sz[100005];
double dp[100005];
void dfs(int u,int fa)
{
	sz[u]=1;
	for(int i=0;i<G[u].size();i++) 
	{
		int v=G[u][i];
		if(v==fa) continue;
		dfs(v,u);
		sz[u]+=sz[v];
	}
}
void DP(int u,int fa)
{
	if(fa!=0) dp[u]=dp[fa]+1+(sz[fa]-sz[u]-1)*1.0/2;
	for(int i=0;i<G[u].size();i++)
	{
		int v=G[u][i];
		if(v==fa) continue;
		DP(v,u);
	}
}
int main() {
	int n;
	scanf("%d",&n);
	for(int i=2,f;i<=n;i++)
	{
		scanf("%d",&f);
		G[f].push_back(i);
		G[i].push_back(f);
	}
	dfs(1,0);
	dp[1]=1;
	DP(1,0);
	for(int i=1;i<=n;i++) printf("%.1f ",dp[i]);
	return 0;
}

```



---

## 作者：ouuan (赞：0)

用 $f[u]$ 表示访问节点 $u$ 的期望时间，$siz[u]$ 表示子树 $u$ 的大小。

令 $v$ 为 $u$ 的一个儿子，那么 $f[v]=f[u]+1+\frac{siz[u]-siz[v]-1}2$ 。

因为 $u$ 除了 $v$ 以外的其它儿子，每个儿子都有 $\frac 1 2$ 的概率在 $v$ 之前被访问、$\frac 1 2$ 的概率在 $v$ 之后被访问，一个儿子 $v'$ 对 $f[v]$ 的贡献就是 $\frac{siz[v']}2$ 。

参考代码：

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N=100010;

void add(int u,int v);
void dfs1(int u);
void dfs2(int u);

int head[N],nxt[N],to[N],cnt;
int n,p[N],siz[N];
double f[N];

int main()
{
	int i;
	
	scanf("%d",&n);
	
	for (i=2;i<=n;++i)
	{
		scanf("%d",p+i);
		add(p[i],i);
	}
	
	dfs1(1);
	f[1]=1;
	dfs2(1);
	
	for (i=1;i<=n;++i)
	{
		printf("%.6lf ",f[i]);
	}
	
	return 0;
}

void add(int u,int v)
{
	nxt[++cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
}

void dfs1(int u)
{
	int i,v;
	siz[u]=1;
	for (i=head[u];i;i=nxt[i])
	{
		v=to[i];
		dfs1(v);
		siz[u]+=siz[v];
	}
}

void dfs2(int u)
{
	int i,v;
	for (i=head[u];i;i=nxt[i])
	{
		v=to[i];
		f[v]=f[u]+1+(siz[u]-1-siz[v])/2.0;
		dfs2(v);
	}
}
```

---

## 作者：pomelo_nene (赞：0)

不会吧不会吧这道题 CF 评分 $1700$ 不会真的是紫题吧。

看到随机化就害怕。问题让我们求期望，我们当然要用一个方法去解决这个问题。

定义一个节点 $u$ 的答案为 $dp_u$，答案显然，初始状态即为 $dp_1 \gets 1$。如何转移？

考虑一个节点的答案（即时间戳的期望），从它的父亲和它的父亲的其他子节点入手。节点 $v$ 必须继承父亲 $u$ 的期望 $dp_u$，还要加上一个 $1$。计算它的父亲的其他子节点的影响。感性理解，对于任意一个 $v$ 父亲 $u$ 的子节点 $v'(v' \neq v)$，其时间戳只有两种情况：比 $v$ 早，比 $v$ 晚。因此令 $\operatorname{size}({v'})$ 为以 $v'$ 为根的子树大小，$v'$ 的贡献实际上是 $\dfrac{\operatorname{size}(v')}{2}$。于是每个 $v'$ 都会类似的给 $v$ 这样的贡献。可是这样做是 $O(n^2)$ 的。于是我们求出每一个 $\operatorname{size}(v)$，就可以做到 $O(n)$ 求解。注意计算贡献的时候求贡献量要排除掉 $u$ 这个节点的贡献。

转移方程：

$$dp_v=dp_u+1+\dfrac{\operatorname{size}(u)-\operatorname{size}(v)-1}{2}$$

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> G[100005];
int n,sizen[100005];
double dp[100005];
void dfs1(int now)
{
	sizen[now]=1;
	for(unsigned int i=0;i<G[now].size();++i)
	{
		int to=G[now][i];
		dfs1(to);
		sizen[now]+=sizen[to];
	}
}
void dfs2(int now)
{
	for(unsigned int i=0;i<G[now].size();++i)
	{
		int to=G[now][i];
		dp[to]=dp[now]+1+(double)((double)sizen[now]-(double)sizen[to]-1)/(double)2;
		dfs2(to);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;++i)
	{
		int fa;
		scanf("%d",&fa);
		G[fa].push_back(i);
	}
	dfs1(1);
	dp[1]=1;
	dfs2(1);
	for(int i=1;i<=n;++i)	printf("%.1f ",dp[i]);
	return 0;
}
```

---

