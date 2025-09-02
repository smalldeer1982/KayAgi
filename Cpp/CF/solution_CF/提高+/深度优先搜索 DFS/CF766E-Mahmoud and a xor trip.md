# Mahmoud and a xor trip

## 题目描述

Mahmoud and Ehab live in a country with $ n $ cities numbered from $ 1 $ to $ n $ and connected by $ n-1 $ undirected roads. It's guaranteed that you can reach any city from any other using these roads. Each city has a number $ a_{i} $ attached to it.

We define the distance from city $ x $ to city $ y $ as the xor of numbers attached to the cities on the path from $ x $ to $ y $ (including both $ x $ and $ y $ ). In other words if values attached to the cities on the path from $ x $ to $ y $ form an array $ p $ of length $ l $ then the distance between them is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF766E/e28c1b7e227a128d11b738e0dd966321ffdd5e65.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF766E/4298d47c0191af3c0a3103f431751061bc7e2362.png) is bitwise xor operation.

Mahmoud and Ehab want to choose two cities and make a journey from one to another. The index of the start city is always less than or equal to the index of the finish city (they may start and finish in the same city and in this case the distance equals the number attached to that city). They can't determine the two cities so they try every city as a start and every city with greater index as a finish. They want to know the total distance between all pairs of cities.

## 说明/提示

A bitwise xor takes two bit integers of equal length and performs the logical xor operation on each pair of corresponding bits. The result in each position is $ 1 $ if only the first bit is $ 1 $ or only the second bit is $ 1 $ , but will be $ 0 $ if both are $ 0 $ or both are $ 1 $ . You can read more about bitwise xor operation here: [https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

In the first sample the available paths are:

- city $ 1 $ to itself with a distance of $ 1 $ ,
- city $ 2 $ to itself with a distance of $ 2 $ ,
- city $ 3 $ to itself with a distance of $ 3 $ ,
- city $ 1 $ to city $ 2 $ with a distance of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF766E/1f43581f72fc5ce3c0b862a8034cb76a29952125.png),
- city $ 1 $ to city $ 3 $ with a distance of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF766E/2d25f1b13f8bc3e6a3f63c847df4adbf20b39c7c.png),
- city $ 2 $ to city $ 3 $ with a distance of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF766E/360a9ab048a3005f1d532cfb7c78e96ffd10455b.png).

 The total distance between all pairs of cities equals $ 1+2+3+3+0+1=10 $ .

## 样例 #1

### 输入

```
3
1 2 3
1 2
2 3
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1 2
2 3
3 4
3 5
```

### 输出

```
52
```

## 样例 #3

### 输入

```
5
10 9 8 7 6
1 2
2 3
3 4
3 5
```

### 输出

```
131
```

# 题解

## 作者：GIFBMP (赞：7)

考虑树形DP。

按位统计，设 $f_{i,x}$ 表示根为 $i$，当前二进制位为 $x$ 时的**方案数**。

易得递推式：

$$f_{i,1}=\sum f_{son,a_i\ \text{xor}\ 1}$$

$$f_{i,0}=\sum f_{son,a_i}$$

初值很明显，即：

$$f_{i,a_i}=1,f_{i,a_i\ \text{xor}\ 1}=0$$

然后转移每棵子树前累加贡献，乘上位权相加即可，即：

$$ans=ans+f_{i,0}\times f_{son,1}\times 2^k+f_{i,1}\times f_{son,0}\times 2^k$$

记得考虑节点数为 $1$ 的链的贡献。

Code:

```cpp
#include <cstdio>
#include <vector>
using namespace std ;
const int MAXN = 1e5 + 10 ;
typedef long long ll ;
ll n , a[MAXN] , f[MAXN][2] , ans , bit ;
vector <int> G[MAXN] ;
void dfs (int x , int fa , int b) {
	int now = (a[x] >> b) & 1 ;
	f[x][now] = 1 ; f[x][now ^ 1] = 0 ;
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i] ;
		if (v == fa) continue ;
		dfs (v , x , b) ;
		ans += f[v][1] * bit * f[x][0] ;
		ans += f[v][0] * bit * f[x][1] ;
		if (!now) {
			f[x][now] += f[v][now] ;
			f[x][now ^ 1] += f[v][now ^ 1] ; 
		}
		else  {
			f[x][now] += f[v][now ^ 1] ;
			f[x][now ^ 1] += f[v][now] ;
		}
	}
}
int main () {
	scanf ("%lld" , &n) ;
	for (int i = 1 ; i <= n ; i++)
		scanf ("%lld" , &a[i]) , ans += a[i] ;
	for (int i = 1 ; i < n ; i++) {
		int u , v ;
		scanf ("%d%d" , &u , &v) ;
		G[u].push_back (v) ;
		G[v].push_back (u) ;  
	}
	for (int i = 0 ; i <= 20 ; i++) {
		bit = 1 << i ;
		dfs (1 , 0 , i) ;
	}
	printf ("%lld" , ans) ;
	return 0 ;
}
```

---

## 作者：o51gHaboTei1 (赞：2)

考虑枚举每一位，用树 dp 算所有使该二进制位为 $1$ 的路径条数。

记 $dp_{x,0/1}$ 表示多少子树内的点与 $x$ 的路径按位异或后二进制为 $0\text{/}1$。

这个显然是可以直接更新的，统计答案时由子树内的贡献互相乘即可。具体地，设 $a_x$ 表示当前 $x$ 本身的值在枚举第 $ps$ 位时是否为 $1$：

- $ans \leftarrow ans + dp_{x,0} \times dp_{son_x,a_x \bigoplus 1} + dp_{x,1} \times dp_{son_x,a_x \bigoplus 0}$

时间复杂度 $O(n \log V)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
#define ll long long 
ll ans,res;
int n,m,dp[Len][2],a[Len],b[Len],head[Len],cnt;
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void DP(int x,int f)
{
	dp[x][0] = dp[x][1] = 0;
	dp[x][b[x]] ++;
	res += b[x];
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		DP(to , x);
		res += 1ll * dp[to][0] * dp[x][1];
		res += 1ll * dp[to][1] * dp[x][0];
		dp[x][0] += dp[to][0 ^ b[x]];
		dp[x][1] += dp[to][1 ^ b[x]];
	}
}
int mxa;
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d",&a[i]);
		mxa = max(mxa , a[i]);
	}
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);
	}
	for(int i = 0 ; (1 << i) <= mxa ; i ++) 
	{
		for(int j = 1 ; j <= n ; j ++) b[j] = (a[j] >> i) & 1;
		DP(1 , 0);
		ans += 1ll * res * (1 << i);
		res = 0;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：CWzwz (赞：1)

[CF766E Mahmoud and a xor trip](https://www.luogu.com.cn/problem/CF766E) 题解

[CodeForces](https://codeforces.com/problemset/problem/766/E)

[cnblogs](https://www.cnblogs.com/C01et10n/p/17959515)

------------

提供一种有点复杂但是好想的换根 dp 思路，好像没什么人写。

给定一棵树，带点权，设 $I(i, j)$ 表示 $i$ 到 $j$ 的路径**按位异或和**，求：

$$\sum_{i=1}^{n}\sum_{j=i}^{n} I(i, j)$$

### 拆位 & 状态

按位异或，先拆个位，每位单独考虑。（以下所写皆为只考虑其中一位时的做法。）

状态就是换根 dp 经典的两个数组：

- $s_{u,0/1}$ 表示，有多少 $v \in \text{sub}_u$ 满足 $I(u, v) = 0/1$。（只考虑子树内的 $v$。）

- $f_{u,0/1}$ 表示，有多少 $v$ 满足 $I(u, v) = 0/1$。（考虑所有 $v \in [1,n]$。）

### $s$ 转移

平凡的，其中 $b\in\{0,1\}$：

$$s_{u, b} = \sum_{v \in \text{son}_u} s_{v, b\operatorname{xor}a_u} + [a_u = b]$$

（最后那个 $[a_u = b]$ 就是 $I(u, u) = b$ 的情况，我们由子树转移来的时候没有统计到。）

### $f$ 转移

至于 $f$ 的转移，我是胡了个大分讨，有无大佬优化下qwq：（$v\in\operatorname{son}_u$）

- $a_u = 0$，$a_v = 0$：

珂以画图看一下，对于所有节点 $x$，$I(x, u) = I(x, v)$，因此 $f_{v, 0} = f_{u, 0}$，$f_{v, 1} = f_{u, 1}$。

- $a_u = 1$，$a_v = 1$：

与上面相反，对于节点 $x$，$I(x, u) = \neg\ I(x, v)$，因此 $f_{v, 0} = f_{u, 1}$，$f_{v, 1} = f_{u, 0}$。

- $a_u = 1$，$a_v = 0$：

对于 $v$ **子树外**的节点 $x$，$I(x, u) = I(x, v)$。

而对于 $v$ **子树内**的节点 $x$，$I(x, u) = \neg\ I(x, v)$。

（第一个括号是子树外，第二个括号是子树内）

$f_{v, 0} = (f_{u, 0} - s_{v, 1}) + (s_{v, 0})$

$f_{v, 1} = (f_{u, 1} - s_{v, 0}) + (s_{v, 1})$

- $a_u = 0$，$a_v = 1$：

与上面相反。

对于 $v$ **子树外**的节点 $x$，$I(x, u) = \neg\ I(x, v)$。

而对于 $v$ **子树内**的节点 $x$，$I(x, u) = I(x, v)$。

$f_{v, 0} = (f_{u, 1} - s_{v, 1}) + (s_{v, 0})$

$f_{v, 1} = (f_{u, 0} - s_{v, 0}) + (s_{v, 1})$

### 统计答案

$lg$ 是当前考虑第几位，从 $0$ 开始。$V$ 是值域。

对于每个点，求出所有**以它为端点的**路径答案之和。这样每条路径会算两次，因此最后除以 $2$。

但是，仅包含一个点的路径只会被算一次！！！所以把它们**再加一遍**，保证除以 $2$ 的时候不出错。

$$\text{ans} = (\ \sum_{lg=0}^{\log V} \sum_{i=1}^n\ f_{i, 1} + \lfloor\frac{a_i}{2^{lg}}\rfloor) \div 2$$

做完了。这个做法确实挺麻烦，但是感觉比较直观。跑得还算比较快，在第一页末尾。

代码里把两维反过来开了，貌似快一点？

[Submission](https://codeforces.com/contest/766/submission/241158958)

---

## 作者：康立扬 (赞：1)

考虑树形 dp。

不妨设 $1$ 为根，记录 $dis_i$ 为从 $1$ 到 $i$ 路径上的点权异或和，则易知 $f(u,v)=dis_u \oplus dis_v \oplus a_{\operatorname{lca}(u,v)}$。

因此可以二进制拆位，维护 $c_{i,0/1}$ 表示 $\operatorname{lca}(u,v)≠u, (dis_v \oplus a_{\operatorname{lca}(u,v)})$ 的第 $i$ 位为 $0/1$ 的个数，然后每一位分别求贡献即可。

具体细节见代码。

[提交记录](https://codeforces.com/contest/766/submission/226285752)

---

## 作者：chlchl (赞：1)

提供一个思维不是最简单代码也不是最好写但是重在独特的思路（doge）。

个人认为这个做法对于处理树上双重和式的许多题目都很有启发意义。

## Solution
明显这个题就是个树形 DP。

这个双重和式很明显不能直接算，我们只能设 $f_u$ 为 $u$ 子树内的答案。

然后你你发现根本就没办法计算答案。注意到题目要求的是所有路径的异或和之和，所以考虑拆二进制位计算。

设 $f_{u,k}$ 为 $u$ 的子树内所有路径权值中，第 $k$ 位为 $1$ 的路径条数。最后答案就是 $\sum_{i=1}^{20}f_{rt,i}\times 2^i$。

首先我们把 $u$ 子树内的路径拆成三种：
1. 两个端点都在 $u$ 的一个儿子 $v$ 的子树内；
2. $u$ 子树的某个点到 $u$；
3. 路径的两个端点来自 $u$ 的两个不同儿子 $v$ 的子树（显然路径会经过 $u$）。

这样我们只需要分别计算这三种的答案就可以得到 $f_u$ 的转移。

对于第一种，非常简单，就是 $f_v$，所以先有 $f_{u,k}=\sum\limits_{v\in son_u}f_{v,k}$。

对于第二种，我们可以预处理一个 $sum_{u,k}$ 表示 $u$ 的子树内有多少个点到 $u$ 的路径权值的第 $k$ 位是 $1$，这样 $f_{u,k}\leftarrow sum_{u,k}+f_{u,k}$。

对于最后一种，我们遍历 $u$ 的每个儿子 $v$，算 $v$ 的子树对 $u$ 的其他子树的贡献即可。

显然一条这样的路径一定会经过 $u$。设起点是 $s$，终点是 $t$。 

- 若 $a_u$ 的第 $k$ 位是 $0$，贡献为 $sum_{v,k}\times\big(sz_u-sz_v-\sum\limits_{x\in son_u,x\ne v}sum_{x,k}\big)+(sz_v-sum_{v,k})\times\sum\limits_{x\in son_u,x\ne v}sum_{x,k}$。其实就是到 $v$ 路径为 $0$ 的数量乘上到 $x$ 路径为 $1$ 的，和到 $v$ 路径为 $1$ 的数量乘上到 $x$ 路径为 $0$ 的，因为 $u$ 第 $k$ 位是 $0$，所以 $s\rightarrow v$ 和 $x\rightarrow t$ 异或起来之后再异或 $a_u$ 之后第 $k$ 位仍然为 $1$；
- $a_u$ 第 $k$ 位为 $1$，类似地，贡献为 $sum_{v,k}\times\sum\limits_{x\in son_u,x\ne v}sum_{x,k}+(sz_v-sum_{v,k})\times\big(sz_u-sz_v-\sum\limits_{x\in son_u,x\ne v}sum_{x,k}\big)$。

然后 $f_u$ 就转移完啦！然后再跑一次 dfs 预处理 $sum_{u,k}$ 即可。

这个就比较简单，可以直接看代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e5 + 10;
int n, a[N], sz[N];
int id, head[N << 1], to[N << 1], nxt[N << 1];
ll ans, sum[N][22], f[N][22];
//sum[u][k] 表示 u 子树内有多少个点到 u 的距离的第 k 位是 1
//f[u][k] 表示 u 子树内的答案中有多少个的第 k 位是 1 

void add(int u, int v){
	to[++id] = v;
	nxt[id] = head[u], head[u] = id;
}

void pre_dfs(int u, int fa){
	sz[u] = 1;
	for(int i=head[u];i;i=nxt[i]){
		int v = to[i];
		if(v == fa)
			continue;
		pre_dfs(v, u);
		sz[u] += sz[v];
		for(int k=0;k<=20;k++){
			if(((a[u] >> k) & 1))
				sum[u][k] += 1ll * sz[v] - sum[v][k];
			else
				sum[u][k] += sum[v][k];//sum 的递推不难
		}
	}
	for(int i=0;i<=20;i++){
		sum[u][i] += ((a[u] >> i) & 1);
		f[u][i] += sum[u][i];//第三种情况
	}
}

void dfs(int u, int fa){
	int s[22][2] = {0}, tot = 0;
	for(int i=head[u];i;i=nxt[i]){
		int v = to[i];
		if(v == fa)
			continue;
		++tot;
		dfs(v, u);
		for(int k=0;k<=20;k++){
			f[u][k] += f[v][k];//第一种情况
			s[k][1] += sum[v][k];//先把所有子树的方案加起来，方便后续转移
			s[k][0] += sz[v] - sum[v][k];
		}
	}
	for(int i=head[u];i;i=nxt[i]){
		int v = to[i];
		if(v == fa)
			continue;
		for(int k=0;k<=20;k++){
			if((a[u] >> k) & 1){
				s[k][1] -= sum[v][k], s[k][0] -= (sz[v] - sum[v][k]);
				f[u][k] += sum[v][k] * s[k][1] + (sz[v] - sum[v][k]) * s[k][0];
			}
			else{
				s[k][1] -= sum[v][k], s[k][0] -= (sz[v] - sum[v][k]);
				f[u][k] += sum[v][k] * s[k][0] + (sz[v] - sum[v][k]) * s[k][1];
			}
		}//算子树对子树的贡献 
	}
}

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++)
		scanf("%d", &a[i]);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	pre_dfs(1, 1);
	dfs(1, 1);
	ll ans = 0;
	for(int i=0;i<=20;i++)
		ans += f[1][i] * (1ll << i);//最后算答案，别忘了 long long
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：wcyQwQ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF766E)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/12/28/CF766E%20Mahmoud%20and%20a%20xor%20trip/)

## 前言

题解里面怎么都是树形 DP，显然不适合我这种没有脑子的选手，于是讲一下思维难度低，但是复杂度稍高的点分治做法。

### 前置芝士

点分治

## 分析

考虑统计经过当前分治中心 $u$ 的答案，记 $d_v$ 为 $u \rightarrow v$ 上不包括点 $u$ 的所有点的异或和。当处理完 $u$ 的一棵子树后，我们可以对二进制下的每一位分别统计答案，用 $cnt_{0/1, i}$ 来表示第 $i$ 位为 $0/1$ 的距离数量，因为我们的 $d_v$ 并不包含 $a_u$，所以我们算贡献时要计算 $d_v \oplus a_u$ 的贡献，不难发现 $d_v \oplus a_u$ 的第 $i$ 位就是桶里面它异或 $1$ 的数量再乘个 $2^i$，我们直接统计即可。注意不要忘记统计路径短点在分治中心的路径和起终点一致的路径。时间复杂度 $O(n\log n\log a)$。

## 代码

```c++
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int N = 1e5 + 10;
int a[N];
int h[N], e[N << 1], ne[N << 1], idx;
bool vis[N];
int cnt[2][30];
int d[N], tot;
ll res;

inline int read()
{
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

inline int get_size(int u, int p)
{
    if (vis[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int v = e[i];
        if (v == p) continue;
        res += get_size(v, u);
    }
    return res;
}

inline int get_root(int u, int p, int all, int &root)
{
    if (vis[u]) return 0;
    int sum = 1, now = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int v = e[i];
        if (v == p) continue;
        int k = get_root(v, u, all, root);
        now = max(now, k);
        sum += k;
    }
    now = max(now, all - sum);
    if (now <= all / 2) root = u;
    return sum;
}

inline void get_dist(int u, int p, int dist)
{
    if (vis[u]) return;
    d[++tot] = dist;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int v = e[i];
        if (v == p) continue;
        get_dist(v, u, dist ^ a[v]);
    }
}

inline void calc(int u)
{
    for (int i = h[u]; ~i; i = ne[i])
    {
        int v = e[i];
        if (vis[v]) continue;
        tot = 0;
        get_dist(v, u, a[v]);
        for (int j = 1; j <= tot; j++)
        {
            int tmp = d[j] ^ a[u];
            res += tmp;
            for (int k = 0; k <= 29; k++)
                res += (ll)cnt[(tmp >> k & 1) ^ 1][k] * (1 << k);
        }
        for (int j = 1; j <= tot; j++)
            for (int k = 0; k <= 29; k++)
                cnt[d[j] >> k & 1][k]++;
    }
    for (int i = 0; i <= 29; i++)
        cnt[0][i] = cnt[1][i] = 0; 
}

inline void dfs(int u)
{
    if (vis[u]) return;
    get_root(u, -1, get_size(u, -1), u);
    vis[u] = 1;
    calc(u);
    for (int i = h[u]; ~i; i = ne[i]) dfs(e[i]);
}

int main()
{
    memset(h, -1, sizeof h);
    int n = read();
    for (int i = 1; i <= n; i++) a[i] = read(), res += a[i];
    for (int i = 1; i <= n - 1; i++)
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }
    dfs(1);
    printf("%lld\n", res);
    return 0;
}
```







---

## 作者：Nylch (赞：1)

首先按照套路，我们按位考虑，那么就变成统计 $0$ 和 $1$ 两种情况的组合的数目，最后乘2的某次幂。

那么记 $dp_{i,j,0/1}$ 表示经过以 $i$ 为根的子树的每一个节点，在第 $j$ 位上产生了多少个 $0$ 或 $1$，然后 dfs 一遍，用儿子的答案更新父亲的答案，最后累加就好了。注意要考虑长度为 $0$ 的路径。

```cpp
#include <bits/stdc++.h>
#define reg register
#define ll long long
#define int long long
#define ull unsigned long long
#define db double
#define pi pair<int, int>
#define pl pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vpi vector<pi>
#define vpl vector<pl>
#define pb push_back
#define er erase
#define SZ(x) (int) x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mkp make_pair
#define ms(data_name) memset(data_name, 0, sizeof(data_name))
#define msn(data_name, num) memset(data_name, num, sizeof(data_name))
#define For(i, j) for(reg int (i) = 1; (i) <= (j); ++(i))
#define For0(i, j) for(reg int (i) = 0; (i) < (j); ++(i))
#define Forx(i, j, k) for(reg int (i) = (j); (i) <= (k); ++(i))
#define Forstep(i , j, k, st) for(reg int (i) = (j); (i) <= (k); (i) += (st))
#define fOR(i, j) for(reg int (i) = (j); (i) >= 1; (i)--)
#define fOR0(i, j) for(reg int (i) = (j) - 1; (i) >= 0; (i)--)
#define fORx(i, j, k) for(reg int (i) = (k); (i) >= (j); (i)--)
#define tour(i, u) for(reg int (i) = head[(u)]; (i) != -1; (i) = nxt[(i)])
using namespace std;
char ch, B[1 << 20], *S = B, *T = B;
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 20, stdin), S == T) ? 0 : *S++)
#define isd(c) (c >= '0' && c <= '9')
int rdint() {
  int aa, bb;
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
ll rdll() {
  ll aa, bb;
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
const int mod = 998244353;
// const int mod = 1e9 + 7;
struct mod_t {
  static int norm(int x) {
    return x + (x >> 31 & mod);
  }
  int x;
  mod_t() {  }
  mod_t(int v) : x(v) {  }
  // mod_t(ll v) : x(v) {  }
  mod_t(char v) : x(v) {  }
  mod_t operator +(const mod_t &rhs) const {
    return norm(x + rhs.x - mod);
  }
  mod_t operator -(const mod_t &rhs) const {
    return norm(x - rhs.x);
  }
  mod_t operator *(const mod_t &rhs) const {
    return (ll) x * rhs.x % mod;
  }
};
const int MAXN = 2e5 + 10;
int n, a[MAXN], dp[MAXN][20][2];
ll ans = 0;
int E, head[MAXN], nxt[MAXN << 1], pnt[MAXN << 1];
inline void clear() {
  E = 0;
  msn(head, -1);
}
inline void addedge(int x, int y) {
  nxt[E] = head[x];
  pnt[E] = y;
  head[x] = E++;
}
inline void dfs(int u, int f) {
  For0(i, 20)
    if(a[u] & (1 << i))
      dp[u][i][1] = 1;
    else
      dp[u][i][0] = 1;
  tour(i, u) {
    int v = pnt[i];
    if(v != f) {
      dfs(v, u);
      For0(j, 20) {
        int tmp = (a[u] >> j) & 1;
        ans += (dp[u][j][1] * dp[v][j][0] + dp[u][j][0] * dp[v][j][1]) << j;
        dp[u][j][tmp ^ 0] += dp[v][j][0];
        dp[u][j][tmp ^ 1] += dp[v][j][1];
      }
    }
  }
}
inline void work() {
  n = rdint();
  For(i, n) {
    a[i] = rdint();
    ans += a[i];
  }
  clear();
  Forx(i, 2, n) {
    int u = rdint(), v = rdint();
    addedge(u, v);
    addedge(v, u);
  }
  dfs(1, -1);
  printf("%lld\n", ans);
}
signed main() {
  // freopen("input.txt", "r", stdin);
  work();
  return 0;
}
```

---

## 作者：TanX_1e18 (赞：0)

看到没有 dsu 的题解，水一发题解。

首先，路径上点权异或和可以差分计算，设 $s_i$ 为 $i$ 号点到根节点路径上的点权异或和，则 $f(u,v)=s_u$ XOR $s_v$ XOR $s_{lca}$ XOR $s_{fa_{lca}}=s_u$ XOR $s_v$ XOR $a_{lca}$。

显然可以 dsu on tree。

详细见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+9;
struct bian
{
    int to,lt;
}b[N<<1];
int head[N],top;
void mkb(int l,int r)
{
    b[++top]={r,head[l]};
    head[l]=top;
}
int val[N],v[N],num[40][2],ans,son[N],siz[N],dfn[N],cnt,mp[N],L[N],R[N];
void dfs(int x,int fa)
{
    v[x]=v[fa]^val[x];
    siz[x]=1;
    dfn[x]=++cnt;
    mp[cnt]=x;
    L[x]=cnt;
    for(int t=head[x];t;t=b[t].lt)
    {
        int y=b[t].to;
        if(y==fa)
        continue;
        dfs(y,x);
        siz[x]+=siz[y];
        if(siz[y]>siz[son[x]])
        son[x]=y;
    }
    R[x]=cnt;
}
void dsu(int x,int fa,bool kp)
{
    for(int t=head[x];t;t=b[t].lt)
    {
        int y=b[t].to;
        if(y==fa||y==son[x])
        continue;
        dsu(y,x,false);
    }
    if(son[x])
    {
        dsu(son[x],x,true);
    }
    for(int t=head[x];t;t=b[t].lt)
    {
        int y=b[t].to;
        if(y==fa||y==son[x])
        continue;
        for(int i=L[y];i<=R[y];i++)
        {
            for(int k=0;k<=21;k++)
            {
                int c=((v[mp[i]]>>k)&1);
                ans+=(1<<k)*(num[k][c^1^((val[x]>>k)&1)]);
            }
        }
        for(int i=L[y];i<=R[y];i++)
        {
            for(int k=0;k<=21;k++)
            {
                int c=((v[mp[i]]>>k)&1);
                num[k][c]++;
            }
        }
    }
    for(int k=0;k<=21;k++)
    {
        int c=((v[x]>>k)&1);
        ans+=(1<<k)*(num[k][c^1^((val[x]>>k)&1)]);
    }
    for(int k=0;k<=21;k++)
    {
        int c=((v[x]>>k)&1);
        num[k][c]++;
    }
    if(!kp)
    {
        memset(num,0,sizeof(num));
    }
}
int n;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>val[i];
        ans+=val[i];
    }
    for(int i=1;i<n;i++)
    {
        int l,r;
        cin>>l>>r;
        mkb(l,r);
        mkb(r,l);
    }
    dfs(1,0);
    dsu(1,0,0);
    cout<<ans;
    return 0;
}
//设v[i]表示i到根的路径上的异或值
//f(i,j)=v[i]^v[j]^val[lca];
```


---

## 作者：Lagerent (赞：0)

本文以 $\oplus$ 表示异或。

记 $w_u$ 表示节点 $u$ 的权值，$s_u$ 表示从根到当前节点的路径异或和。

考虑两点 $u, v$ 间路径的异或和可以表示为

$$s_u \oplus s_v \oplus w_{lca}.$$

$\oplus$ 运算各二进制位之间独立，考虑拆位算贡献。

设 $f_{u, 0/1}$ 表示以 $u$ 为根的子树，从子树中节点到 $u$ 的路径异或和二进制位为 $0$ 或 $1$，这样的**节点个数**。

转移方程是显然的，设 $v$ 是 $u$ 的儿子：

$$f_{u, 0} = \sum f_{v, 0}, f_{u, 1} = \sum f_{v, 1}.$$

考虑如何统计答案。当路径异或和在当前二进制位上为 $1$ 时会对最终答案产生贡献。发现我们并不关心路径的起点和终点具体是啥，我们只关心路径异或和为 $1$ 的点对有多少个，而 $s$ 我们又可以处理出来，所以在合并两棵子树时，对于答案的贡献就是：

$$(f_{u, 0} \times f_{v, 0} + f_{u, 1} \times f_{v, 1}) \times 2^{bit}, w_u \text{ 在第 } bit \text{ 位上是 }1,$$

$$(f_{u, 0} \times f_{v, 1} + f_{u, 1} \times f_{v, 0}) \times 2^{bit}, w_u \text{ 在第 } bit \text{ 位上是 } 0.$$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
#define gc getchar
#define rep(a, b, c) for(int (a) = (b); (a) <= (c); ++ (a))
#define per(a, b, c)for(int (a) = (b); (a) >= (c); -- (a))
using namespace std;

inline int rd() {
    int x = 0,f = 1; char ch = gc();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = gc();}
    while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
    return x * f;
}

const int N = 100010, M = 25;

int n, w[N], ans, col[N], now = 1;
int hd[N], to[N << 1], nt[N << 1], idx;
int f[N][2];

void add(int u, int v) {
    to[idx] = v, nt[idx] = hd[u], hd[u] = idx ++ ;
}

void dfs(int u, int fa, int s) {
    f[u][s] = 1, f[u][s ^ 1] = 0;
    for(int i = hd[u]; ~i; i = nt[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u, s ^ col[v]);
    	if(col[u]) ans += (f[u][0] * f[v][0] + f[u][1] * f[v][1]) * now;
    	else ans += (f[u][1] * f[v][0] + f[u][0] * f[v][1]) * now;
    	f[u][0] += f[v][0];
    	f[u][1] += f[v][1];
    }
}

signed main() {
    memset(hd, -1, sizeof hd);
    n = rd();
    rep(i, 1, n) w[i] = rd(), ans += w[i];
    rep(i, 1, n - 1) {
        int u = rd(), v = rd();
        add(u, v), add(v, u);
    }
    rep(i, 0, 21) {
    	rep(j, 1, n) {
    		col[j] = w[j] & 1;
    		w[j] >>= 1;
		}
		dfs(1, 0, col[1]);
		now <<= 1;
	}
    printf("%lld\n", ans);
    return 0;
}
```

---

