# Hamiltonian Spanning Tree

## 题目描述

n 个城市之间形成了一个有n*(n-1)/2条边的完全无向图。走每条边需要y秒。  

给定该图的一个n-1条边的生成树，走树上的每一条边只需要x秒（不过注意x不一定小于y）。

你希望从任意一个点开始，经过每个点恰好一次，在任意一个点结束的路径的长度所花时间最少。求最少时间。

## 样例 #1

### 输入

```
5 2 3
1 2
1 3
3 4
5 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5 3 2
1 2
1 3
3 4
5 3
```

### 输出

```
8
```

# 题解

## 作者：Durancer (赞：4)

### 前言

我不会DP，但我会运用人类本质。

### 题目

> 给定一个 n 个点的完全图，边权相同为 y ，在完全图中标定一颗生成树，树上边权变为 x，求不重复遍历所有节点的最短路径长度。

### 思路

既然题目中非常鲜明地指出了 `不过注意x不一定小于y` 那么肯定是让我们来进行分类讨论的。

一、完全图的边权更小。

大家肯定知道这个情况一定会选择更小的，也就是使选择的完全图的边更多一些。

那么现在讨论两种情况：

1、菊花图。

生成树为菊花图说明必须要选择一条树边 $e$，那么其他的路径一定可以在完全图的边上遍历完成，所以其他的选择完全图上的边即可。答案为 $\text{x+(n-2)y}$。

判断是否为菊花图，只需要判断一个点的出度是否为 $\text{n-1}$ 即可。

2、非菊花图。

这个时候连接一个点的边一定有一条是完全图边，那么肯定有一条路径是不会经过任何的树边的，可以手模几组样例尝试尝试。

此时的答案就是 $(\text{n-1}) y$ 。

二、边权相同。

那肯定随便选就行了，答案为 $(\text{n-1})y$。

三、树边的边权更小。

根据贪心思想，一定会尽可能多得选择树边去走，但是这个并没有一些很固定的规律，那么就可以利用**人类本质**了，可以发现，路径中一个点的度最大为 $2$，也就是
$$a-x-b$$

一条进，一条出。

那么我们就会贪心地想，尽量使选择的树边最多，那么就可以用深搜判断是否可以选择即可。

最后答案就是 $cnt_e y+(n-cnt_e-1) x$

### 代码实现

```cpp
/*

	分类讨论:
	
	生成树边x > 完全图边y : 1、非菊花图，通过手模发现，只要生成树不是菊花图，那么一定可以找到一条路径不会经过树边，也就是
									ans=y*(n-1)
							2、菊花图，一定会经过一条树边，其他的边都可以经过完全图边， ans=x+y*(n-2)
							(判断菊花图找度为 n-1 的即可)
	x=y ans=x*(n-1)
	
	生成树边x < 完全图边y : 1、尽可能地找生成树的边，另有一条性质，度最多为2，那么直接贪心计算就可以了！只要一条合法的树边没有被选，贪心选上即可。 
									ans=stick*x+(n-stick-1)*y

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<algorithm>
#include<vector>
#define int long long
#define ZPL return
#define AK 0
#define IOI ;
using namespace std;
const int N=2e5+9;
struct node{
	int last;
	int to;
	int dis;
}e[N<<1];
int head[N];
int cnt;
int f[N][3];
int ans;
int ind[N];
int stick;//选择的树边 
int n,x,y;//x生成树，y完全图上 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
void add(int from,int to,int dis)
{
	e[++cnt].last=head[from];
	e[cnt].to=to;
	e[cnt].dis=dis;
	head[from]=cnt;
}
bool dfs(int u,int fa)
{
	int du=2;//度最多为2
	for(int i=head[u];i;i=e[i].last)
	{
		int v=e[i].to;
		if(v==fa) continue;
		if(dfs(v,u)&&du)//可以使用树边！ 
		{
			du--;
			stick++;
		}
	}
	if(du>0) return true;
	else return false; 
}
void work()
{
	dfs(1,0);
	cout<<stick*x+(n-stick-1)*y<<endl;
	return;
}
signed main()
{
	n=read();
	x=read();//生成树边 
	y=read();//完全图边 
	bool flag=false;
	for(int i=1;i<n;i++)
	{
		int u=read();
		int v=read();
		add(u,v,x);
		add(v,u,x);
		ind[v]++;
		ind[u]++;
		if(ind[v]==n-1||ind[u]==n-1)
			flag=true;	
	}
	if(flag&&x>y)
	{
		cout<<x+(n-2)*y<<endl;
		return 0;
	}
	if(x>y)
	{
		cout<<(n-1)*y<<endl;
		return 0;
	}
	if(x==y)
	{
		cout<<(n-1)*y<<endl;
		return 0;
	}
	work();
	ZPL AK IOI 
}
```

---

## 作者：Accelerator_X (赞：3)

# 贪心 + 树上最小路径覆盖

## 0x00 何为路径覆盖：

**路径覆盖**是指将点集划分为若干点 _不相交_ 的路径的方案

## 0x01 怎样求最小路径覆盖

这里我们仅探讨**树上**最小路径覆盖

### 考虑树形DP

记$dp_u$表示要覆盖以$u$为根节点及其子树，最少需要的点集个数

显然最终答案为$dp_{root}$

我们还需记一个$f_u\in\ \{0, 1\}$表示$u$是否可以成为一条路径的端点

直观来说就是它能不能成为它父节点的“接口”

#### 接下来考虑如何转移

首先，如果$u$的所有子树都没有可以与它相“接上”的“端口”，那么最小路径覆盖的集合数就要$+1$，同是它也成了新的集合的“接口”，故$f_u=1$

如果$u$的子树中有一个“接口”，考虑到如果接上这个“接口”，则$u$还可以继续接到上一级，一定不差。故贪心地把$u$接上这颗子树上，$f_u=1$

如果$u$的子树中存在多个“接口”，由于路径不可交叉，$u$最多与两“接口”相接。这里继续使用贪心的思想考虑，如果$u$只接一个“接口”，则会舍弃让集合数$-1$的代价（子树中两个独立集合并），来换取$u$可以接到其父节点而可能达到的$-1$的回报，显然不划算！故要让$u$接两个子树“接口”，那么最小路径覆盖的集合数就要$-1$，同时$f_u=0$

综上，可以写出如下DP转移方程：

$$
dp_u = \sum_{}{dp_v}+
\left\{ 
\begin{matrix}
+1,\quad\sum_{}{f_v}=0 \\
0,\quad\sum_{}{f_v}=1 \\
-1,\quad\sum_{}{f_v}>=2 \\
\end{matrix}
\right.
$$

$$
f_u =
\left\{ 
\begin{matrix}
1,\quad\sum_{}{f_v}=0 \\
1,\quad\sum_{}{f_v}=1 \\
0,\quad\sum_{}{f_v}>=2 \\
\end{matrix}
\right.
$$

两者同时转移

至此，即可求出树上最小路径覆盖的集合数

## 0x02 本题运用

本题中是给出了一张图和图上的一颗生成树，在图上跑的边需要花费$y$，在树上跑的边需要花费$x$

若$y<x$，显然在图上跑反而更优，但需要注意这种情况：

若此树是菊花图，即所有点都连向根节点，则必须要跑一条树边，其他的跑$n-2$图边

其余情况，不难发现皆可跑$n-1$条图边完成

若$y>=x$，可以发现能跑树边尽量跑树边更优，即需要让图边尽量少。而我们发现图边数就是连接每段“独立路径块”的边数。因此，我们只需求出最小路径覆盖数$k$，那么跑$k-1$条图边和$n-k$条树边即是最有解

## 0x03 附上AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0; bool f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int MAXN = 2e5 + 6;
int n, x, y, cnte, hd[MAXN];
int in[MAXN], dp[MAXN], f[MAXN];
struct tEdge { int to, nxt; } e[MAXN << 1];
inline void link(int u, int v) {
	e[++cnte] = {v, hd[u]};
	hd[u] = cnte;
}
void misaka(int u, int p) {
	if (!hd[u]) {
		dp[u] = f[u] = 1;
		return;
	}
	int sumf = 0;
	for (int i = hd[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == p) continue;
		misaka(v, u);
		dp[u] += dp[v];
		sumf += f[v];
	}
	if (sumf == 0) ++dp[u], f[u] = 1;
	if (sumf == 1) f[u] = 1;
	if (sumf >= 2) --dp[u], f[u] = 0;
}
int main() {
	n = read(), x = read(), y = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		link(u, v); link(v, u);
		++in[u]; ++in[v];
	}
	if (y < x) {
		bool f = 0;
		for (int i = 1; i <= n; ++i)
			if (in[i] == n - 1) f = 1;
		if (f) printf("%lld\n", (n - 2ll) * y + x);
		else printf("%lld\n", (n - 1ll) * y);
	} else {
		misaka(1, 0);
		printf("%lld\n", (dp[1] - 1ll) * y + (n - dp[1] * 1ll) * x);
	}
	return 0;
}
```


---

## 作者：Hoks (赞：1)

## 前言
duel 到的题，降智了卡了 $10$ min+，整体思路还是比较连贯的。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
很自然的想到贪心。

如果对于 $x\ge y$ 的情况，显然是选更多的图边更好。

这个时候就要人类智慧分类讨论了：
1. 是菊花图：无法避免的会选择一条树边，因为找不到任何点不和菊花的重心不相连，答案即为 $x+(n-2)\times y$。
2. 不是菊花图，则肯定能选出一条路径不经过任何一条树边，答案即为 $(n-1)\times y$。

接着来考虑 $x<y$ 的情况，显然是选择越多的树边越好。

然后我卡在这了，仔细一看才发现**经过每个点恰好一次**被我忘了。

既然一个点恰好经过一次，那么能选择的与他相连的树边最多只有两条。

考虑用 dfs 实现，对于一个点 $u$ 为 $v$ 的父亲，先考虑 $v$ 点尝试能否找到两条边，若没找满，则再考虑 $u\rightarrow v$ 这条边。

设找到了 $cnt$ 条边，答案即为 $cnt\times x+(n-cnt-1)\times y$。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,mod=998244353,INF=0x3f3f3f3f3f3f3f3f,lim=20;
int n,x,y,cnt,in[N];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='A'&&c<='Z'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline bool dfs(int u,int ff)
{
    int s=2;
    for(auto v:e[u])
    {
        if(v==ff) continue;
        if(dfs(v,u)&&s) s--,cnt++;
    }
    return s>0;
}
signed main()
{
    n=read(),x=read(),y=read();int f=0;
    for(int i=1,u,v;i<n;i++) u=read(),v=read(),e[u].emplace_back(v),e[v].emplace_back(u),in[u]++,in[v]++;
    for(int i=1;i<=n;i++) if(in[i]==n-1) f=1;
    if(y<=x){print(f?(n-2)*y+x:(n-1)*y);goto genshin;}
    dfs(1,0);print(cnt*x+(n-cnt-1)*y);
    genshin:;flush();return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

分三类讨论。

+ $x=y$：随便走。答案为 $(n-1)\times x$。
+ $x>y$：尽量不走树上的边。如果某一个点的全部 $n-1$ 条出边均为树边则答案为 $x+(n-2)\times y$，否则为 $(n-1)\times y$。
+ $x<y$：尽量走树上的边，直接贪心的搜索找出树上链长的和的最大值即可。

时间复杂度为 $O(n)$。

---

