# 「MCOI-02」Glass 玻璃

## 题目背景

小 S 进入了一个服务器，这个服务器有一个游戏叫“树上的玻璃”。

## 题目描述

首先给定一棵树，每个点上有 $V_i$ 个玻璃，每条边上有权值 $W_i$。

每次操作小 S 可以选择两个节点 $u,v(u\ne v)$，从节点 $u$ 到节点 $v$ 的唯一路径上，**边和** 为路径上所有边的权值和，即 $\sum W_i$，**点和** 为路径上所有点（包括 $u,v$）的玻璃数和，即 $\sum V_i$。小 S 将可以获得 **边和** 和 **点和** 的乘积的分数，即 $\sum W_i\times\sum V_i$。

任意两次操作不能完全相同，$(u,v)$ 和 $(v,u)$ 被看作是两种操作。

但是有时候这颗树太过庞大，小 S 需要你的帮助。他需要你告诉他，经过 $N(N-1)$ 次操作后，总共能得到多少分。结果可能很大，你只需要输出答案对 $998244353$ 取模的结果。

## 说明/提示

#### 样例说明

对于样例 $1$，树的形态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/4yfdr3b6.png)

#### 数据规模与约定

**本题采用捆绑测试。**

|子任务编号  | $N$ | $V_i,W_i$ | 特殊性质 | 分值 |时限|
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $\le200$ | $\lt 2^3$ |  | $3$ |$\rm 1s$|
| 2 | $\le10^3$ | $\lt2^3$ |  | $6$ |$\rm 1s$|
| 3 | $\le6\times10^3$ | $\lt2^8$ |  | $11$ |$\rm 1s$|
| 4 | $\le2\times 10^5$ | $\lt 2^8$ | 存在度数为 $N-1$ 的节点 | $12$ |$\rm 1s$|
| 5 | $\le2\times10^5$ |  | 树的形态为一条链 | $13$ |$\rm 1s$|
| 6 | $\le2\times10^5$ |  |  | $21$ |$\rm 1s$|
| 7 | $\le2\times10^6$ |  |  | $34$ |$\rm 2s$|

对于 $100\%$ 的数据，$0\le V_i,W_i\lt2^
{16}$，$1 \le N\le2\times10^6$。

#### 说明

Minecraft OI Round 2 D

- Maker：Inf_Voltage
- Tester：tarjin


## 样例 #1

### 输入

```
5
1 2 1 2 1
1 5 1
1 2 2
2 3 1
2 4 2```

### 输出

```
256```

# 题解

## 作者：loveJY (赞：3)

暴力推式子!

第一篇题解虽然详细但是细节还是要补充的....

钦定一个根后:

首先考虑一条路径,

$$\sum_{i}^nV_i\sum_{j}^mW_j$$

然后我们分离一条边

$$\sum_{i}^nV_i * W_j$$

然后我们裂开西格玛

设1~l表示了这个边所在的下面子树的路径的点

l+1~n就表示这个边所管子树外的路径上的点

$$\sum_{j=1}^l V_j \sum_{i=l+1}^n V_i * W_k$$

嗯,再看看所有路径一起,设S为一条路径

$\sum_S *(\sum_{j=1}^l V_j \sum_{i=l+1}^n V_i * W_k[i,j \in S])$

设这条边管束的点为u,即u到fa的边是这条边

这个式子的左半部分表示子树内所有点到点u的路径点权和,可以用dp处理

$dp_{u}=\sum_{v}dp_v + siz[u]*a[u]$

右半部分表示子树外所有点到点u的路径点权和,换根DP

转移时考虑除去这个子树的贡献,并且加上其他点到到点u的贡献

$$		f[v] = dp[u] - dp[v]  - siz[v] * a[u] + f[u] +(n - siz[u]) * a[u];
$$

前三项是u其他子树到v的贡献,剩下是算上u被统计几次

再考虑统计答案

你会发现直接相乘f,dp数组是不行的,因为我们是带权的....

但是冷静一下会发现我们相当于把每条路径拆成两半算

那么我们可以考虑这一半被算的次数

那么$dp_u*(n-siz[u])*w_i$就表示子树内一半的贡献

$f_u*siz[u]*w_i$表示另一半

这样我们算好了一个边的贡献

又由于乘法分配律,我们不难看出所有边这样算的贡献和就是答案了

时间复杂度$O(n)$

code:

```cpp


#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 2e6 + 7;
const int MAXM = 4e6 + 7;
const int P = 998244353;
int n, home[MAXN], nxt[MAXM], to[MAXM], w[MAXM], ccnt, a[MAXN], siz[MAXN];
ll dp[MAXN], f[MAXN], ans;

namespace fastIO {
#define BUF_SIZE (1<<21)
	static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = BUF_SIZE + buf;
	inline char nc() {
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
		}
		return *p1++;
	}
	inline int read() {
		char s = nc();
		int x = 0;
		for(; !isdigit(s); s = nc());
		for(; isdigit(s); s = nc())x = (x << 1) + (x << 3) + s - '0';
		return x;
	}
}
using namespace fastIO;

inline void ct(int x, int y, int z) {
	ccnt++;
	nxt[ccnt] = home[x];
	home[x] = ccnt;
	to[ccnt] = y;
	w[ccnt] = z;
}

inline void add(ll &x, ll y) {
	x += y;
	if(x >= P)x -= P;
}

inline void dfs1(int u, int F) {
	siz[u] = 1;
	for(int i = home[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v == F)continue;
		dfs1(v, u);
		add(dp[u], dp[v]);
		siz[u] += siz[v];
	}
	add(dp[u], 1ll * siz[u] * a[u] % P);
	return ;
}

inline void dfs2(int u, int F) {
	for(int i = home[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v == F)continue;
		f[v] = ((dp[u] - dp[v]  - 1ll * siz[v] * a[u] % P + P) % P + f[u] + 1ll * (n - siz[u]) * a[u] % P) % P;
		add(f[v], P);
		add(ans, ((1ll * f[v] * siz[v] % P * w[i] % P + 1ll * w[i] * dp[v] % P * (n - siz[v]) % P) % P + P) % P);
		dfs2(v, u);
	}
	return ;
}


int main() {
	n = read();
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
	}
	for(int i = 1, x, y, z; i < n; ++i) {
		x = read();
		y = read();
		z = read();
		ct(x, y, z);
		ct(y, x, z);
	}
	dfs1(1, 0);//第一遍dfs考虑做出所有点子树内到他的路径点权和
	dfs2(1, 0);//第二遍dfs考虑做出所有点子树外到他的路径点权和并计算答案
	printf("%d\n", 1ll * ans * 2 % P);
	return 0;
}



```

---

## 作者：一只书虫仔 (赞：3)

已获得出题人授权。

---------------

$\large\texttt{Subtask1:\ 3\ pts}$

读题分，枚举所有的 $(u,v)$，然后花费 $O(N)$ 的时间计算 $u,v$ 之间链上的点权和和边权和，统计答案即可。

时间复杂度 $O(N^3)$。


--------------

$\large\texttt{Subtask2:\ 6\ pts}$

我们延续上面的思路，枚举所有的 $(u,v)$，然后统计答案。

但是统计答案可以优化到 $O(\log N)$。我们算出每个节点到根节点路径上的边权和和点权和，即树上前缀和，一遍 DFS 即可。对于两个点 $u,v$，我们求出它们的 LCA，然后用前缀和求出 $u,v$ 两点路径上的边权和与点权和。

时间复杂度 $O(N^2\log N)$。

----------------------

$\large\texttt{Subtask3:\ 11\ pts}$

拿到这个 Subtask 有两种方式。

1. 考虑优化 Subtask 2 的方法，什么倍增树剖 LCA 太慢了，我们用 tarjan 算法可以优化到线性。不过 tarjan 算法常数偏大，轻微卡常。
2. 换一种思路，我们枚举一个端点，然后以它为根节点进行 DFS。DFS 到的每个节点的树上边权前缀和和点权前缀和的乘积统计到答案中。代码简单，常数优秀。

时间复杂度 $O(N^2)$。

-------------------------

$\large\texttt{Subtask4:\ 12\ pts}$

菊花图。

考虑链的形态就两种情况。长度为 $1$ 的链和长度为 $2$ 的链。长度为 $1$ 的链就是一条边，直接枚举边统计。长度为 $2$ 的链肯定经过中心点，枚举一个端点对另一个端点算贡献即可。

时间复杂度 $O(N)$。

-----------------------

$\large\texttt{Subtask5:\ 13\ pts}$

链。

不失一般性，我们假设链的形态是 $1-2-3-\dots-N$。


考虑对每条边算贡献。对于一条边，端点为 $i,i+1$。左边在 $[1,i]$ 右边在 $[i+1,N]$ 的操作会经过该边。这条边一共会被算 $i\times(N-i)$ 次。对于点权，我们看成点 $i$ 要算 $V_i$ 次即可

时间复杂度 $O(N)$。

---------------------

$\large\texttt{Subtask6:\ 25\ pts}$

我们要统计所有路径的贡献，点分治是个不错的选择。

考虑将两条半链 $A,B$ 拼起来。完整的链的贡献为 
$$\left(\sum W_A+\sum W_B\right)\times \left(\sum V_A+\sum V_B\right)$$
乘一下得到

$$\sum W_A\times  \sum V_A+\sum W_A\times \sum V_B+ \sum W_B\times \sum V_A+\sum W_B\times \sum V_B$$
开几个变量分别记录 $\sum W$ 和 $\sum V$ 的前缀和即可。

时间复杂度 $O(N \log N)$。

----------------------

$\large\texttt{Subtask7:\ 35\ pts}$

你认为结束了？并没有，因为我们有更优秀的做法。

延续链的思路，我们对每条边算贡献。我们称一条边两侧为左右两侧。

以边两个端点为根分别 DFS，不经过当前正在统计的边。记 $Val_i$ 为节点 $i$ 的子树大小和点权的乘积。则这条边的贡献为左侧所有点的 $Val$ 的和与右侧子树大小的乘积加右侧所有点的 $Val$ 的和与左侧子树大小的乘积。别忘了还要乘以自身的边权。

但是每次都要 DFS 不是沦为和暴力老哥同分吗。没错，这里我们需要换根 DP。两次 DFS，在第二次 DFS 的时候同时统计所有边的答案。

时间复杂度 $O(N)$。

---

