# 『DABOI Round 1』Develop a Tree

## 题目背景

小 Z 看不惯树，所以他总想在树上随机添加一些边。他认为二分图是很和谐的，所以他想知道将一棵树变为二分图的方案数。你能否回答他的询问？

## 题目描述

对于一颗无向有根树，定义 $f(i,k)$ 表示在以 $i$ 为根的子树中，在其内部连 $k$ 条边，使得这颗子树变为一个二分图的方案数。请注意，加边时允许与原树边重边，但任意两条新加的边都不能重合。

给定一棵 $n$ 个点的无向有根树，根节点为 $1$ 号点。对于每个 $i\in [1,n]$，求 $f(i,k)$ 对 $p_i$ 取模的值。

## 说明/提示

**【样例 1 解释】**

在这棵树上，连接 $(u,v)\in\{(1,3),(1,5),(1,6),(2,3),(2,5),(2,6),(3,4),(4,5),(4,6)\}$ 即可使树变为二分图。

---

**【数据范围】**

**本题开启捆绑测试**。

对于 $100\%$ 的数据，$1\le n\le5\times10^5$，$1\le k\le 20$，$1\le u_i,v_i\le n$，$2\le p_i\le2\times10^9$，$p_i$ 为素数。最多有 $99$ 个大小不同的 $p_i$。保证 $p_i>k$。

| $\text{Subtask}$ | $n\le$ | $\text{Special}$ | $\text{Score}$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $5\times10^5$ | $\text{A}$ | $10$ |
| $2$ | $10^3$ | $\text{No}$ | $15$ |
| $3$ | $5\times10^5$ | $\text{B}$ | $15$ |
| $4$ | $5\times10^5$ | $\text{No}$ | $60$ |

- $\text{Special A}$：保证 $k=1$；
- $\text{Special B}$：保证 $v_i=u_i+1$。

---

**【提示】**

本题 IO 量较大，请使用较快速的 IO 方式。

## 样例 #1

### 输入

```
6 1
1 3
1 5
1 6
2 5
3 4
998244353 998244353 998244353 998244353 998244353 998244353```

### 输出

```
9 0 1 0 1 0```

# 题解

## 作者：Cute_M (赞：7)

更新：修缮了[该帖子](https://www.luogu.com.cn/discuss/923678)中提到的明显错误。

~~观察比赛名称可以发现，因为 D 在第一位，所以 D 最简单（大雾）。~~

同学开场切 D，太强了。

仔细阅读题目要求：

> 请注意，加边时允许与原树边重边，但任意两条新加的边都不能重合。

即：若存在一种方案来划分原树使得其可以满足所有已知的边不会连在同一个部点内，则设左部点个数为 $l$，右部点个数为 $r$，答案即为 $C^k_{l\times r}$。

问题转化为怎样在 $O(n)$ 的时间复杂度内求出每个子树中的方案。

容易发现，对于一个点，其只可能与与其深度差为 $1$ 的点连边，则将奇数深度点化为左部点，偶数深度点划分为右部点即可。

注意组合数求解过程中 $C^k_{l\times r}=\frac{A^k_{l\times r}}{A^k_k}$，其中除法需要用乘法逆元完成。这里保证了 $p_i$ 均为质数，就用费马小定理做了。

复杂度 $O(n(k+\log p_i))$。

---

## 作者：zgy_123 (赞：3)

![](https://cdn.luogu.com.cn/upload/image_hosting/zxxf3qro.png)

~~感觉太板了~~。

## subtask 1

考虑二分图的性质：

> 二分图不存在长度为奇数的环。

由于加边后树变为基环树，有且只有一个环。易得对答案有贡献的点，距离只能为奇数，这样才可以保证产生的环长为偶数。

记 $d(X,Y)$ 为 $X$ 和 $Y$ 之间的距离，$R$ 为根节点，$L$ 当前两个节点的 LCA。

根据 LCA，两个点的距离为：

$$d(X,Y)=d(x,R)+d(y,R)-2d(L,R)$$

然而本题中仅需要求路径长度的奇偶性，所以有：

$$d(X,Y)\equiv(x,R)+d(y,R)(\operatorname{mod} 2)$$

得出结论：

> 两个点距离为奇数，当且仅当其到根节点距离和为奇数。

又根据小学数学，只有奇数加偶数为奇数，即：

> 两个点距离为奇数，当且仅当其中一个点到根节点距离为偶数，而另一个节点到根节点距离为奇数。

所以这个题实际上是求：在 $i$ 的子树中到 $i$ 距离为偶数（奇数）的点的数量，乘积即为 $f(i,1)$。

考虑 dfs 的同时维护一个 dp 数组，其中 $dp_{i,x}$ 表示 $i$ 的子树中到 $i$ 的距离模 $2$ 为 $x$ 的点的个数。

有转移式（令 $v$ 为 $u$ 的儿子）：

$$dp_{u,0}=\sum dp_{v,1}+1$$

$$dp_{u,1}=\sum dp_{v,0}$$

输出 $f(i,1)=dp_{i,0}\times dp_{i,1}$ 即可。复杂度 $O(n)$。

## subtask 2

可以直接枚举每个点对，计算距离。但是问题在于 $k>1$。

不难发现添加 $k$ 条边等价于在可添加的边里选 $k$ 条。所以 $f(i,k)=C_{f(i,1)}^{k}$。

由于模数是质数，可以直接 $O(k)$ 求组合数。

## subtask 3,4

将 subtask1 和 subtask2 的做法结合起来即可，时间复杂度 $O(\sum k\log_2p_i)=O(nk\log p)$，TLE。

所以考虑优化掉 $\log$，显然可以开个桶预处理逆元，于是就做完了。

std by caosheng_zzz：

```cpp
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <map>
#include <set>
typedef int intt ;
#define prt printf
#define ll long long
#define int __int128
#define spc prt(" ")
#define ent prt("\n")
#define pr_ prt("---")
#define prx prt("***")
using namespace std;

int read(){
	int f = 1 , k = 0;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') f = -1;
		c = getchar() ;
	}
	while(c >= '0' && c <= '9'){
		k = (k << 3) + (k << 1) + (c ^ 48);
		c = getchar() ;
	}
	return (f == 1 ? k : -k);
}

void output(int now){
	if(now < 0){
		putchar('-');
		output(- now);
	}
	else{
		if(now > 9) output(now / 10);
		putchar((now % 10) ^ 48);
	}
}

const intt maxn = 5e5 + 1;
const ll Mod[] = {0 , 999998003 , 999998017 , 999998023 , 999998059 , 999998081 , 999998107 , 999998119 , 999998137 , 999998141 , 999998143 , 999998147 , 999998173 , 999998183 , 999998203 , 999998243 , 999998261 , 999998269 , 999998309 , 999998339 , 999998369 , 999998423 , 999998459 , 999998501 , 999998507 , 999998509 , 999998533 , 999998537 , 999998563 , 999998609 , 999998617 , 999998621 , 999998627 , 999998639 , 999998641 , 999998653 , 999998663 , 999998683 , 999998687 , 999998689 , 999998693 , 999998777 , 999998789 , 999998801 , 999998843 , 999998863 , 999998869 , 999998903 , 999998917 , 999998921 , 999998929 , 999998957 , 999998959 , 999998971 , 999998981 , 999999001 , 999999017 , 999999029 , 999999043 , 999999059 , 999999067 , 999999103 , 999999107 , 999999113 , 999999131 , 999999137 , 999999151 , 999999163 , 999999181 , 999999191 , 999999193 , 999999197 , 999999223 , 999999229 , 999999323 , 999999337 , 999999353 , 999999391 , 999999433 , 999999487 , 999999491 , 999999503 , 999999527 , 999999541 , 999999587 , 999999599 , 999999607 , 999999613 , 999999667 , 999999677 , 999999733 , 999999739 , 999999751 , 999999757 , 999999761 , 999999797 , 999999883 , 999999893 , 999999929 , 999999937};
intt cnt = 0 , h[maxn] ;
intt f[maxn][2];
struct Edge{
	intt next , to;
}edge[maxn << 1];
map<ll , intt> G ;
ll g[100][21] , mul[100][21];
intt cour = 0 ;

void add(intt u , intt v){
	edge[++ cnt] = {h[u] , v};
	h[u] = cnt;
}

void dfs(intt u , intt fa , intt deep){
	f[u][deep % 2] ++ ;
//	output(u) , spc , output(fa) , spc , output(deep) , ent;
	for(intt i=h[u] ; i ; i=edge[i].next){
		intt v = edge[i].to ;
//		output(u) , spc , output(v) , ent;
		if(v == fa) continue ;
		dfs(v , u , deep + 1) ;
		f[u][0] += f[v][0] , f[u][1] += f[v][1];
	}
	return ;
}	

int power(int base , ll s , ll p){
	int res = 1;
	while(s){
		if(s & 1) res = res * base % p;
		base = base * base % p;
		s >>= 1;
	}
	return res;
}

ll C(intt a , int b , ll p){
	int res = 1 ; intt num = G[p];
	if(b == 0 || a == 0) return 0 ;
	if(a > b) return 0 ;
	if(a == 1) return b % p ;
	if(a >= p) return 0 ;
	for(int i=1 ; i<=a ; i++){
		res = res * (b - i + 1) % p * mul[num][i]  % p;
	}
	return res;
}

signed main(){
//	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n = read() , k = read() ;
	for(int i=1 ; i<=100 ; i++) { G[Mod[i]] = i ; for(int j=1 ; j<=k ; j++) mul[i][j] = power(j , Mod[i] - 2 , Mod[i]) ;}
	for(int i=1 ; i<n ; i++){
		intt u , v ;
		cin >> u >> v ;
		add(u , v) , add(v,  u);
	}
	dfs(1 , 0 , 1);
	for(int i=1 ; i<=n ; i++) { output(C(k , (__int128)f[i][0] * f[i][1] , read())) , i == n ? ent : spc ;}
	return 0;
}
```

- 这个题所有人都认为不应该放 T4，但是最后还是放了。
- 题太水请见谅。
- 感谢阅读！

---

## 作者：awapwq233 (赞：2)

## P11032 Develop a Tree 题解

[题意](https://www.luogu.com.cn/problem/P11032)：一个以 1 为根节点的树，分别求出以 $i=1,2,\cdots, n$ 为根的子树中，加入 k 条边构成二分图对 $p_i$ 取模的方案数。

先考虑 $i=1$ 的情况。首先我们要知道，**树就是二分图**，且染色方案是唯一的：将节点深度为奇数的节点染黑，节点深度为偶数的节点染白，这样就保证了两个颜色之间不相连。

而题目让你加边且可以重复，也就是在这两种颜色（个数分别为 a 和 b）之间加边，方案数为 $C_{a\times b} ^ k$。

注意到在子树中，深度的奇偶性不变或者交换，也就是对 $i=1$ 的情况的划分依然是成立的，于是我们可以直接 dfs 预处理出每个节点为根的子树的黑白两色的个数，扔组合数板子就行。

因为 $k\leq 20$，所以组合数是好求的。

Code

```cpp
int sum[500005][2];
void dfs(int u, int fa, bool color)
{
    sum[u][color] = 1;
    for(int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if(v == fa)
            continue;
        dfs(v, u, !color);
        sum[u][0] += sum[v][0];
        sum[u][1] += sum[v][1];
    }
}
ll C(ll n, ll m, ll p)
{
    if(m > n)
        return 0;
    ll ans = 1;
    UF(i, n, n - m + 1)
        ans = ans * i % p;
    ll inv = 1;
    F(i, 2, m)
        inv = inv * i % p;
    return ans * fastpow(inv, p - 2, p) % p;
}
ll lucas(ll n, ll m, ll p)
{
    if (n < p && m < p) return C(n, m, p);
    return 1ll * C(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}

signed main()
{
    read(n, k);
    F(i, 1, n - 1)
    {
        int u, v; read(u, v);
        addedge(u, v); addedge(v, u);
    }
    dfs(1, 0, 0);
    F(i, 1, n)
        write(' ', lucas(1ll * sum[i][0] * sum[i][1], k, readll()));
    return 0;
}
```

---

## 作者：chenxi2009 (赞：2)

[专栏沉浸式阅读](https://www.luogu.com.cn/article/ynz7reik)
# 题目描述

对于一颗无向有根树，定义 $f(i,k)$ 表示在以 $i$ 为根的子树中，在其内部连 $k$ 条边，使得这颗子树变为一个二分图的方案数。请注意，加边时允许与原树边重边，但任意两条新加的边都不能重合。

给定一棵 $n$ 个点的无向有根树，根节点为 $1$ 号点。对于每个 $i\in [1,n]$，求 $f(i,k)$ 对 $p_i$ 取模的值。

# 提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le n\le5\times10^5$，$1\le k\le 20$，$1\le u_i,v_i\le n$，$2\le p_i\le2\times10^9$，$p_i$ 为素数。最多有 $99$ 个大小不同的 $p_i$。保证 $p_i>k$。

**题解前的话**

前置知识：二分图的概念，树的概念，一点动态规划思想，一点点组合数学（或许有）。

# 思路

对于一个二分图 $G$，其左部点有 $n1$ 个，右部点有 $n2$ 个，容易想到在其中连 $k$ 条不重的边的方案数为 $C_{n1\times n2}^{k}$。求它的复杂度为 $O(k)$，这里不再赘述，如果不懂请参考代码。

我们发现对于一颗树，它就是一个**二分图式**的结构。什么意思呢？我们可以将其中深度为奇数的点归为左部点，深度为偶数的点归为右部点，它就成为了一个二分图。可以发现有且只有这一种转换方式。换种说法说，**到根节点距离为奇数的点是左部点，反之为右部点。**

我们又可以发现：对于一个子树，按上述方法分割，它的左部点数就是**以它的子节点为根的子树的右部点个数之和**，右部点个数就是**以它的子节点为根的子树的左部点个数之和加一**（因为还有这个点本身）。

形式化地去描述，以点 $i$ 为根的子树左部点数为 $f_i$，右部点数为 $g_i$，则有

$$
f_i=\sum_{j\in son_i}g_j
$$

$$
g_i=\sum_{j\in son_i}f_j+1
$$

其方案数则为

$$
C_{f_i\times g_i}^{k}
$$

到这里，这个问题已经得到了基本解决。

但是 ——

嗯？？怎么超时了？？

原来由于我们对组合数的取模操作中，组合数的分母项求逆元的复杂度是 $O(\log p_i)$，这样程序的总时间复杂度就变成了 $O(nk\log p)$。在本题中有着 $3\times 10^8$ 的运算量。

接下来的优化可以从两个方面入手：

1. 分母阶乘运算完后再取模，复杂度降为 $O(n(k+\log p))$。

2. 由于数据范围中“最多有 $99$ 个大小不同的 $p_i$”，可以预处理出 $k!$ 在各个 $p_i$ 下的乘法逆元。复杂度为 $O(nk+100k \log p)$。达到了本题的最佳复杂度。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
vector<int>lp;
set<int>ep;
map<int,int>m;
int n,k,u,v,js[500001],os[500001],c,head[500001],nxt[1000001],des[1000001],cnt;
int ans[500001],p[500001];
int qp(int a,int b,int MOD){//乘法逆元所需的快速幂 
	if(!b){
		return 1;
	}
	if(b == 1){
		return a;
	}
	int c = qp(a,b >> 1,MOD);
	c = c * c % MOD;
	if(b & 1){
		return c * a % MOD;
	}
	return c; 
}
void sch(int fa,int u){
	for(int i = head[u];i;i = nxt[i]){
		int v = des[i];
		if(v == fa){
			continue;
		}
		sch(u,v);
		js[u] += os[v];
		os[u] += js[v];
	}
	os[u] ++;
	int C = js[u] * os[u];
	if(C < k){
		ans[u] = 0;
		return;
	}
	int MOD = p[u];
	c = C % MOD;
	for(int i = 2;i <= k;i ++){
		c *= (C - i + 1) % MOD;
		c %= p[u];
	}
	c *= m[p[u]];
	c %= MOD;
	ans[u] = c;
	return;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i = 1;i < n;i ++){
		scanf("%lld%lld",&u,&v);
		nxt[++ cnt] = head[u],head[u] = cnt,des[cnt] = v;
		nxt[++ cnt] = head[v],head[v] = cnt,des[cnt] = u;
	}
	for(int i = 1;i <= n;i ++){
		scanf("%lld",&p[i]);
		if(!ep.count(p[i])){
			ep.insert(p[i]);
			lp.push_back(p[i]); 
		}
	}//统计不同的 p[i] 
	for(int i = 0;i < lp.size();i ++){
		int x = 1;
		for(int j = 2;j <= k;j ++){
			x = x * qp(j,lp[i] - 2,lp[i]) % lp[i];
		}
		m[lp[i]] = x;
	}//预处理 k! 的乘法逆元 
	sch(0,1);//树形动态规划 
	for(int i = 1;i <= n;i ++){
		printf("%lld ",ans[i]);
	}
	return 0;
}
```

总结：一道适合练习树形 dp 的题目，需要一些组合数学与取模运算的知识来写出正解。

---

## 作者：DFM_O (赞：1)

## [P11032 题目](https://www.luogu.com.cn/problem/P11032)

### 解题思路
众所周知，一个图为二分图的充要条件为：图中所有回路的长度均为偶数。所以我们可以在 $i$ 与 $j$ 之间连边当且仅当树上 $i$ 与 $j$ 的距离为奇数。

定义树上 $i$ 与 $j$ 的距离为 $\operatorname{dis}(i,j)$，易知 $\operatorname{dis}(i,j)=\operatorname{dis}(i,\operatorname{LCA}(i,j))+\operatorname{dis}(\operatorname{LCA}(i,j),j)$。

定义 $dp_i$ 为以 $i$ 为根节点的子树中有多少组点对 $(u,v)$ 满足 $1\le u<v\le n$ 且 $\operatorname{dis}(u,v)$ 为奇数，$dp2_i$ 为以 $i$ 为根节点的子树中有个点 $u$ 满足 $\operatorname{dis}(u,i)$ 为奇数，$s_i$ 表示节点 $i$ 的儿子序列，$son_i$ 表示其儿子个数，$siz_i$ 表示以 $i$ 为根节点的子树大小。

$dp2$ 的转移方程很容易想到，若 $u$ 为 $v$ 的父亲，那么对于任意一个在 $u$ 的子树点 $i$ 都有 $\operatorname{dis}(i,v)+1=\operatorname{dis}(i,u)$，即 $\operatorname{dis}(i,v)$ 与 $\operatorname{dis}(i,u)$ 奇偶性不同，所以可得：
$$dp2_u=\sum_{i=1}^{son_u} siz_{s_{u,i}}-dp2_{s_{u,i}}$$

然后再考虑 $dp$ 的转移方程，容易想到 $dp_u=\sum_{i=1}^{son_u}dp_{s_{u,i}}+dp2_i$ 再加上 $\operatorname{dis}(i,j)$ 为奇数的个数（这里的 $i,j$ 需满足 $i$ 在 $s_{u,x}$ 的子树内，$j$ 在 $s_{u,y}$ 的子树内，且 $x<y$）。

前面两个部分都很好求，那么 $\operatorname{dis}(i,j)$ 的部分该怎么求呢？前面我们提到 $\operatorname{dis}(i,j)=\operatorname{dis}(i,\operatorname{LCA}(i,j))+\operatorname{dis}(\operatorname{LCA}(i,j),j)$，显然，在这里 $\operatorname{LCA}(i,j)=u$，那么$\operatorname{dis}(i,j)=\operatorname{dis}(i,u)+\operatorname{dis}(u,j)$，考虑枚举 $i$ 和 $j$ 在哪个子树内和 $\operatorname{dis}(i,u)$ 的奇偶性：

$$\begin{aligned} dp_u&=\sum_{i=1}^{son_u}dp_{s_{u,i}}+dp2_i+\sum_{i=1}^{son_u}\sum_{j=i+1}^{son_u}(dp2_{s_{u,i}}\times(siz_{s_{u,j}}-dp2_{s_{u,j}})+(siz_{s_{u,i}}-dp2_{s_{u,i}})\times dp2_{s_{u,j}})\\&=\sum_{i=1}^{son_u}dp_{s_{u,i}}+dp2_i+\sum_{i=1}^{son_u}(dp2_{s_{u,i}}\times\sum_{j=i+1}^{son_u}(siz_{s_{u,j}}-dp2_{s_{u,j}})+(siz_{s_{u,i}}-dp2_{s_{u,i}})\times\sum_{j=i+1}^{son_u}dp2_{s_{u,j}})\\&=\sum_{i=1}^{son_u}dp_{s_{u,i}}+dp2_i+\frac{\sum_{i=1}^{son_u}(dp2_{s_{u,i}}\times(dp2_{s_u}-(siz_{s_{u,i}}-dp2_{s_{u,i}}))+(siz_{s_{u,i}}-dp2_{s_{u,i}})\times (siz_u-1-dp2_u-dp2_{s_{u,i}}))}{2}\end{aligned}$$

但每次添加边后，图就会不一样，我们还能不能按照原图的方式进行处理呢？

答案是可以的，即不可能出现类似于在 $a$ 与 $b$，$b$ 与 $c$ 之间添加边后，$a$ 与 $c$ 之间仍能添加边的情况。

证明：首先，我们易知 
$\operatorname{dis}(a,b)=\operatorname{dis}(a,\operatorname{LCA}(a,b))+\operatorname{dis}(\operatorname{LCA}(a,b),b)$ 与 $\operatorname{dis}(a,\operatorname{LCA}(a,b,c))+\operatorname{dis}(\operatorname{LCA}(a,b,c),b)$ 的奇偶性相同，均为奇，因为要么 $\operatorname{LCA}(a,b,c)=\operatorname{LCA}(a,b)$，要么 $\operatorname{LCA}(a,b,c)$ 为 $\operatorname{LCA}(a,b)$ 的父亲，$\operatorname{dis}(b,c)$ 和 $\operatorname{dis}(a,c)$ 同理。

所以 $\operatorname{dis}(a,c)$ 与 $\operatorname{dis}(a,\operatorname{LCA}(a,b,c))+\operatorname{dis}(\operatorname{LCA}(a,b,c),c)=\operatorname{dis}(a,\operatorname{LCA}(a,b,c))+\operatorname{dis}(\operatorname{LCA}(a,b,c),b)+\operatorname{dis}(b,\operatorname{LCA}(a,b,c))+\operatorname{dis}(\operatorname{LCA}(a,b,c),c)-2\times\operatorname{dis}(\operatorname{LCA}(a,b,c),b)=\operatorname{dis}(a,b)+\operatorname{dis}(b,c)-2\times\operatorname{dis}(\operatorname{LCA}(a,b,c),b)$ 的奇偶性相等，$\operatorname{dis}(a,b)$ 为奇，$\operatorname{dis}(b,c)$ 也为奇，而 $2\times\operatorname{dis}(\operatorname{LCA}(a,b,c),b)$ 为偶，所以 $\operatorname{dis}(a,c)$ 为偶，即 $a$ 与 $c$ 之间不能连边，得证。

这样就大功告成了，最后的答案 $ans_i$ 就为 $C_{dp_i}^k$。

注意：因为 $dp_i$ 和 $dp2_i$ 的值不可能超过 $10^{18}$，所以在计算 $dp_i$ 和 $dp2_i$ 的值的过程中不要取模，在最后计算组合数时取模即可。

~~所以至多有 $99$ 个不同的 $p_i$ 有啥用。~~

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int> g[500001];
int io[500001],p[500001],dp[500001],dp2[500001],siz[500001];
inline long long poww(long long a,long long b,long long mod)
{
    long long ss=1;
    while(b)
    {
        if(b&1)
            ss=ss*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ss;
}
inline int ny(int a,int b,int mod)
{
	int s=poww(b,mod-2,mod)*a%mod;
	return s;
}
inline int reC(int n,int m,int mod)
{
	int a=1;
	for(int i=m;i>=m-n+1;i--)
		a=a*i%mod;
	int ch=1;
	for(int i=2;i<=n;i++)
		ch=ch*i%mod;
	a=ny(a,ch,mod);
	return a;
}
inline int C(int n,int m,int mod)
{
	int a=n,b=m,s=1;
	while(a>=mod||b>=mod)
	{
		int nown=a%mod,nowm=b%mod;
		s=s*reC(nown,nowm,mod)%mod;
		a/=mod,b/=mod;
	}
	s=s*reC(a,b,mod)%mod;
	return s;
}
inline void dfs(int x,int fa)
{
	siz[x]=1;
	for(auto u:g[x])
	{
		if(u!=fa)
		{
			dfs(u,x);
			siz[x]+=siz[u],dp2[x]+=siz[u]-dp2[u];
		}
	}
	for(auto u:g[x])
	{
		if(u!=fa)
		{
			dp[x]+=(siz[u]-dp2[u])*(siz[x]-1-dp2[x]-dp2[u]);
			dp[x]+=dp2[u]*(dp2[x]-(siz[u]-dp2[u]));
		}
	}
	dp[x]/=2;
	for(auto u:g[x])
	{
		if(u!=fa)
			dp[x]+=dp[u];
	}
	dp[x]+=dp2[x];
}
signed main()
{
	ios::sync_with_stdio(false);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		g[u].push_back(v),g[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
		cin>>p[i];
  dfs(1,0);
  for(int i=1;i<=n;i++)
  {
    dp[i]=C(k,dp[i],p[i]);
    cout<<dp[i]<<' ';
  }
	return 0;
}
```

---

## 作者：CRZ_AK_DZG (赞：0)

# 题解 P11032 Develop a Tree 
~~第一次在模拟赛解决绿题，以此纪念。~~   
##### 二分图，看似很高级，实则就是将图中所有点分成两部分，并且每部分之间没有连边，而题目一开始给的是一棵树，因此我们只需要用 dfs 对树进行染色，并且途中维护一个 dp 数组，即可快速求解。
需注意，本题目由于需要求模，所以需要快速幂求解乘法逆元，不会的请跳转[P3811 【模板】模意义下的乘法逆元](https://www.luogu.com.cn/problem/P3811)。
##### （细节见代码）
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10;
int qpow(int a, int b, int p);
void dfs(int u, int fa);
struct node {
	int w, b; //white black
} dp[N]; //dp[i].b: 以i节点为根节点的子树中黑点的个数（w同理） 
int n, m, ans, tmp, k, p, f[N]; //f[i] : i节点的父节点
vector <int> g[N];
bool flag[N];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> k;
	int u, v;
	for(int i=1;i<n;i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	for(int i=1;i<=n;i++) {
		cin >> p;
		ans = 1, tmp = 1, m = dp[i].w % p * (dp[i].b % p) % p;
		if(k == 1) {
			cout << m % p << ' ';
			continue;
		} 
		for(int i=m;i>=m-k+1;i--) ans = i % p * ans % p;
		for(int i=1;i<=k;i++) {
			tmp = i % p * tmp % p;
		}
		ans = ans * qpow(tmp, p-2, p) % p;
		cout << ans << ' ';
	}
	return 0;
}
//dfs维护dp
void dfs(int u, int fa) {
	f[u] = fa, flag[u] = !flag[fa];
	for(auto v : g[u]) {
		if(v == fa) continue;
		dfs(v, u);
	}
	if(flag[u]) dp[u].b++;
	else dp[u].w++;
	dp[fa].b += dp[u].b;
	dp[fa].w += dp[u].w;
	return ;
}
//快速幂求解乘法逆元
int qpow(int a, int b, int p) {
	int res = 1;
	while(b) {
		if(b & 1) res = res * a % p;
		b >>= 1, a = a * a % p;
	}
	return res; 
} 

```
~~绫地宁宁天下第一可爱！~~

---

## 作者：CaoSheng_zzz (赞：0)

### 思路
我们首先需要了解什么是二分图。

假设我们有两个集合 $S , T$，在这两个集合里面的点互相没有连边，但是 $S$ 集合的点**可以**与 $T$ 集合的点有连边。

那很显然这道题目我们就有思路了，我们假设当前点为 $u$，我们定义 $son_{u,0}$ 为 $u$，$son_{u,1}$ 为 $u$ 的儿子，$son_{u,2}$ 为 $u$ 儿子的儿子，$son_{u,3}$ 为 $\dots$。那么我们就可以找出两个集合具体有哪些点了，对于 $son_{u,i}$ 当 $i$ 为 $2$ 的倍数时 $son_{u,i} \in S$ 否则 $son_{u,i} \in T$。

假设 $S$ 集合有 $s$ 个点，集合 $T$ 有 $t$ 个点，那么我们总共可以连 $s \times t$ 条边，题目需要连 $k$ 条边就先当与在 $s \times t$ 条边中选 $k$ 条边那么总方案数就为 $C_{s \times t}^{k}$。

如果你想到这里我们思路就完结撒花了，但是代码实现却有很多不同的细节。

### 程序细节与优化

对于答案的统计我们只需要知道对于每个点 $u$，以 $u$ 为根节点 $S , T$ 集合中点的个数，所以我们可以优化即定义一个数组 $f_{u,0/1}$，$f_{u,0}$ 表示 $S$ 集合的点的个数，$f_{u,1}$ 表示 $S$ 集合的点的个数，那么对于每个点 $u$ 答案就为 $C_{f_{u,0} \times f_{u,1}}^{k}$。

由于每个点答案的统计模数都不同所以我们总时间复杂度为遍历一遍数 $\Omicron({n})$ 加上算组合数 $C$ 的时间复杂度 $\Omicron({nk \log p})$，$\log p$ 求逆元的时间复杂度。所以总时间复杂度是 $\Omicron({n + nk \log q})$。但是显然这个时间复杂度是不行的。

考虑到只有 $100$ 个不同的 $p$ 所以考虑记忆化去掉 $\log p$ 所以总时间复杂度为 $\Omicron(nk)$。

考虑到每个人代码能力不同所以特此放一下 [Link](https://www.luogu.com.cn/paste/5c9l1qxx)。

### 推荐另一篇[题解](https://www.luogu.com.cn/article/xyi0srz5) [by zgy123](https://www.luogu.com.cn/user/577628)

---

