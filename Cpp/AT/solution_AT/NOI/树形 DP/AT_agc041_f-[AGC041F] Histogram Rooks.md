# [AGC041F] Histogram Rooks

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc041/tasks/agc041_f

$ N $ 行 $ N $ 列のマスからなる盤面を考えます。アーボックはこの盤面の一部を切り離し、$ i\ =\ 1,\ 2,\ \ldots,\ N $ のそれぞれについて、左から $ i $ 列目は最も下の $ h_i $ マスのみが残されています。 そして、残されたマスのうち何マスかにルークを置こうとしています。

ルークはチェスの駒の一種で、$ 1 $ マスを占めます。$ 1 $ 回の移動では、何も置かれていないマスの上を縦か横の一方向に何マスでも動けます。 切り離されたマスの上は通れません。

あるマスについて、そのマスにルークが置かれているか、そのマスに $ 1 $ 回の移動で到達できるルークがあるとき、そのマスは支配下にあるといいます。

残された全マスが支配下に入るように残されたマスのうち何マスかにルークを置く方法の数を $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 400 $
- $ 1\ \leq\ h_i\ \leq\ N $
- 入力中のすべての値は整数である。

### Sample Explanation 1

$ 2 $ 個以上のルークをどのように置いても条件が満たされ、そのような置き方は $ 11 $ 通りです。

### Sample Explanation 2

条件を満たす置き方は次の $ 17 $ 通りです (`R` がルーク、`\*` が空のマスに対応)。 ``` R \* \* R \* \* R R R R R R \*\*R R\*\* R\*R R\*\* \*R\* \*\*R R \* R \* \* R \* R \* \* R R R\*R \*RR RR\* R\*R RRR RR\* R R R R R \* \* R R R R\*R \*RR RRR RRR RRR ```

## 样例 #1

### 输入

```
2
2 2```

### 输出

```
11```

## 样例 #2

### 输入

```
3
2 1 2```

### 输出

```
17```

## 样例 #3

### 输入

```
4
1 2 4 1```

### 输出

```
201```

## 样例 #4

### 输入

```
10
4 7 4 8 4 6 8 2 3 6```

### 输出

```
263244071```

# 题解

## 作者：command_block (赞：33)

**题意** ：有一个 $n$ **行**的棋盘，第 $i$ 行的长度为 $h_i$ ，左侧对齐。

该棋盘上放置“車”棋子，若一个格子和某个“車”同行或同列，且之间都是棋盘，则称该格子被覆盖。

求将该棋盘完全覆盖的放置方案数。

答案对 $998244353$ 取模。

$h\leq n\leq 400$ ，时限$\texttt{4s}$。

------------

AT 题目总是让人一看就很想知道答案，但是想半分钟就会发现根本不可做。

市面上的题解都比较意识流，看了半天才看懂，这里整理一个详细一点的……

考虑容斥，选（钦定） $k$ 个格子没有被覆盖，容斥系数为 $(-1)^k$。

此时对于某个还能放置車的格子，方案数就是 $2$。

这个做法虽然很直观易懂，但是还没有利用题目的任何性质。考虑对“不可放置”这一条件进行化简。

不难发现，由于行总是连续的，若某一行选了一个格子，则这一整行都不能放置車。

枚举不能放置車的行集合 $S$（不是钦定）。这样，就只需要再考虑列的约束，行列能独立了。

所以，对于每个独立的部分，即**列**上的一个极长连续段，计算出贡献，然后乘起来即可。

若列连续段长度为 $len$ 且有 $p$ 个格子在 $S$ 中，贡献有如下两种 ：

- ① 没有格子被选，则所有不在 $S$ 中的格子都能放置，方案数为 $2^{len-p}$。

- ② 枚举选格子的个数，贡献为 $\sum\limits_{i=1}^p\binom{p}{i}(-1)^i=-[p>0]$。

但这个做法是错误的，因为不能保证 $S$ 中的每行都至少有一个点被选。

那就……再容斥！

钦定不能选格子的行集合 $T\subseteq S$，容斥系数是 $(-1)^{|T|}$。

若列连续段中有 $q$ 个格子在 $S$ 中，则还能选的格子个数只剩下 $p-q$ ，二类贡献变为 $-[p-q>0]=-[p>q]$。

现在正确性有保证了，然而枚举 $S,T$ 的复杂度太高，所以接下来寻找反射。

不难发现，一个列连续段最终的贡献只与 $p,[p=q]$ 有关。（$q$ 要么 $=p$ 要么 $<p$）

前面的做法指出了映射 “ $(S,T)\rightarrow $ 各个连续段 $p,[p=q]$ ” ，现在我们反过来，对某个贡献已经确定的局面，寻找所有可能的 $(S,T)$ 的 $(-1)^{|T|}$ 的和。

坏消息是，在统计 $(S,T)$ 时，列连续段之间不再是独立的。也就是说，该连续段计数的不同的 $(S,T)$ 对其他连续段有不同的影响，所以不能简单地乘法原理了事。

具体地，影响的方式如下 ：

观察棋盘的形状，将其剖分成笛卡尔树的形式，如图 ：（图是蒯 @Itst 神的）

![stO Itst Orz](https://cdn.luogu.com.cn/upload/image_hosting/2xxvstz5.png)

好在，我们只关心 $p,[p=q]$ 。

在某个确定的 $(S,T)$ 局面中，有如下显然事实 ： 

红色部分的某一列在 $S$ 中的行的数量 $=$ 绿色部分在 $S$ 中的行的数量 $+$ 蓝色部分在 $S$ 中的行的数量 $+$ 第四行是否在 $S$ 内。

红色部分的某一列的 $[p=q]=($ 绿色部分的 $[p=q]\ ){\ \rm and\ }($ 蓝色部分的 $[p=q]\ ){\ \rm and\ }($ 第四行的 $[p=q]\ )$

这启发我们在笛卡尔树上做树形 $\rm DP$。

设 $f\big[u,p,[0=q]\big]$ 为 ： 对笛卡尔树的节点 $u$ ，其 $p,q$ 为给定情况，所有 $(S,T)$ 的 $(-1)^{|T|}$ 且**乘上儿子所有贡献**的和。

转移时，$p$ 那一维是背包，而 $[p=q]$ 那一维是 $\rm and$。具体可见代码。

对于右侧没东西的行，可以看作特殊的儿子。

复杂度为树上背包的复杂度，即 $O(n^2)$。

求出 $f\big[u,p,[0=q]\big]$ 后，计算出自己一列的贡献，再 `pow` 一下列数，就能得到自己的贡献。

若每次都 `pow` ，复杂度可以达到 $O(n^2\log n)$。但不难发现本质不同的贡献只有 $n$ 种， $O(n^2)$ 预处理幂即可。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define pb push_back
#define ll long long
#define MaxN 405
using namespace std;
const int mod=998244353;
ll powM(ll a,int t=mod-2){
  ll ret=1;
  while(t){
    if (t&1)ret=ret*a%mod;
    a=a*a%mod;t>>=1;
  }return ret;
}
ll c[MaxN][MaxN][2];
void Init(int n)
{
  ll buf=1;
  for (int i=0;i<=n;i++){
    c[i][0][0]=c[i][0][1]=1;
    for (int j=1;j<=n;j++){
      c[i][j][1]=c[i][j-1][1]*buf%mod;
      c[i][j][0]=c[i][j-1][0]*(buf-1)%mod;
    }buf=buf*2%mod;
  }
}
vector<int> g[MaxN];
int siz[MaxN],len[MaxN];
ll f[MaxN][MaxN][2];
void dfs(int u)
{
  if (!u)return ;
  f[u][0][1]=1;
  for (int i=0,v;i<g[u].size();i++){
    dfs(v=g[u][i]);
    siz[u]+=siz[v];
    for (int k=siz[u];k>=0;k--){
      ll sav0=0,sav1=0;
      for (int j=0;j<=min(siz[v],k);j++){
        ll buf=(f[v][j][0]+f[v][j][1])*(f[u][k-j][0]+f[u][k-j][1])%mod,
           buf2=f[v][j][1]*f[u][k-j][1]%mod;
        sav0+=buf-buf2;sav1+=buf2;
      }f[u][k][0]=sav0%mod;
      f[u][k][1]=sav1%mod;
    }
  }for (int p=0;p<=siz[u];p++){
    f[u][p][0]=f[u][p][0]*c[siz[u]-p][len[u]][0]%mod;
    f[u][p][1]=f[u][p][1]*c[siz[u]-p][len[u]][1]%mod;
  }
}
int n,h[MaxN],tn;
int build(int l,int r,int pre)
{
  int mx=*min_element(h+l,h+r+1),
      u=++tn,p=l;
  len[u]=mx-pre;
  for (int i=l;i<=r;i++)
    if (h[i]==mx){
      g[u].pb(0);
      if (p<i)g[u].pb(build(p,i-1,mx));
      p=i+1;
    }
  if (p<=r)g[u].pb(build(p,r,mx));
  return u;
}
int main()
{
  scanf("%d",&n);Init(n);
  for (int i=1;i<=n;i++)
    scanf("%d",&h[i]);
  siz[0]=1;f[0][1][1]=mod-1;f[0][0][1]=f[0][1][0]=1;
  //0节点代表空行 
  int rt=build(1,n,0);
  dfs(rt);
  ll ans=0;
  for (int p=0;p<=n;p++)
    ans+=f[rt][p][0]+f[rt][p][1];
  printf("%lld",(ans%mod+mod)%mod);
  return 0;
}
```

---

## 作者：lsj2009 (赞：23)

## Preface

非常 Educational 的题！

虽然感觉独立做出了大半，但还是感觉这个题很深刻。

## Description

给定一个直方图，其中第 $i$ 列高度为 $a_i$，可以往上面放若干个車，每个車会占领其 **所在列上的所有格子** 和 **向左、向右延申直到碰到边界的所有格子**。

求有多少种放車的方案使得每个位置都会被 **至少一个** 車占领。

$1\le a_i\le n\le 400$。

**Bonus：**$1\le n\le 3000$，$1\le a_i\le 10^9$。

## Solution

### Part 1

事实上相当于每个位置上有一个限制，刻画为：所在行的连续段和所在列至少有一个車。

则答案就是对于满足每个限制的方案集合 **交集**，也就是得满足所有限制。

比较套路地，钦定 $i$ 个限制 **违反**，其于限制 **不进行强制要求**，只需要将此情况的方案数乘上 $(-1)^i$ 再求和即可。

容斥系数推导较为经典，这里不赘述。

若枚举所有 **钦定违反限制的格子集合** $S$，是容易快速计算出此情况下的方案数的，即可做到 $\widetilde{\mathcal{O}}(2^{\sum a_i})$ 复杂度。

### Part 2

一个关键观察是：**列是连续的**。

所以考虑 **枚举**（注意不是钦定！！这会在全文的最后有解释）哪几列 **存在我们钦定违反限制的格子**。记我们枚举的列集合为 $S$。

这里 **枚举** 的含义是：任意 $x\in S$ 的列均存在钦定违反限制格子，任意 $x\notin S$ 的列均不存在钦定违反限制的格子。

则每一行，会分成若干连续段 $[l_1,r_1],[l_2,r_2],\cdots,[l_k,r_k]$，对于每一个连续段考虑其是否存在不合法格子。
- 不存在：则任意 $x\notin S$ 的列均可以放車，对答案贡献即为 $2^{|[l_i,r_i]|-|[l_i,r_i]\cap S|}$。
- 存在：则该连续段内不可以放車，且需在 $[l_i,r_i]\cap S$ 内选择一 **非空** 子集 $T$ 钦定 $T$ 中所有格子违反限制，即对答案贡献为 $\sum\limits_{\emptyset\ne T\subseteq \left([l_i,r_i]\cap S\right)} (-1)^{|T|}=\left(\sum\limits_{i\ge 0} \binom{|[l_i,r_i]\cap S|}{i}(-1)^i\right)-1=-[[l_i,r_i]\cap S\ne\emptyset]$。

记 $t=|[l_i,r_i]\cap S|$，则该连续段对答案贡献为 $2^{|[l_i,r_i]|-x}-[x\ne 0]$。这里的贡献为 **乘法**。

然而你注意到这样子其实不太对：
- 任意 $x\in S$ 的列 **均存在** 钦定违反限制格子。
- 任意 $x\notin S$ 的列 **均不存在** 钦定违反限制的格子。

我们并没有保证前者的每一列都存在违反限制的格子。

但这仔细看这句话：**任意** $x\in S$ 的列 **均存在** 钦定违反限制格子。

这其实对于每个 $x\in S$ 都是一个限制，我们求的就是对于每个满足限制的方案集合 **交集** 的大小。

这其实和我们最开始的问题形式上一模一样！！！

同样考虑容斥，钦定一个列集合 $T\subseteq S$，令任意 $x\in T$ 的列 $x$ 违反限制，也就是其中 **没有** 违反限制的格子（但仍然 **不能放車**，否则这和我们枚举集合 $S$ 的根本冲突了！）。同样，带 $(-1)^{|T|}$ 的容斥系数即可。

则原来的贡献改写成如下形式：
- 不存在：则任意 $x\notin S$ 的列均可以放車，对答案贡献即为 $2^{|[l_i,r_i]|-|[l_i,r_i]\cap S|}$。
- 存在：则该连续段内不可以放車，且需在 $[l_i,r_i]\cap (S\setminus T)$ 内选择一 **非空** 子集 $T'$ 钦定 $T'$ 中所有格子违反限制，即对答案贡献为 $=-[[l_i,r_i]\cap (S\setminus T)\ne\emptyset]$。

这样子暴力做我们也就获得了一个 $\widetilde{\mathcal{O}}(3^n)$ 的做法。

### Part 3

进一步优化：我们考虑将整个直方图 **剖分**。

![](https://s21.ax1x.com/2024/12/30/pAzPojS.png)

这也就是我们上面说的每一行的连续段，当然我们有把这种“比较厚”的连续段缩在了一大块。

如何比较好的刻画这个东西？**广义笛卡尔树**（这个东西在网上好像没有什么 blog，但确实是有听过这样子的一个名字的）。

普通的笛卡尔树是一个二叉树，且仅在对 **排列** 建树时有比较好的定义，否则如果当前 **存在多个最值**，取谁为根是要打一个问号的。

广义笛卡尔树给出了比较好的解决方法。广义笛卡尔树上分 **方点** 和 **圆点**，前者刻画为一个 **区间**，后者为一个 **单独的点**。

下面给出一个例子可能可以比较好的解释：
- 求序列 $1,1,4,5,1,4$ 的广义笛卡尔树。

![](https://s21.ax1x.com/2024/12/30/pAzikNR.png)

这应该就很清晰了。

注意到对于一个行段算贡献的时候我们其实只关心 $|S\cap[l_i,r_i]|$ 的值和 $[(S\setminus T)\cap[l_i,r_i]=\emptyset]$ 的值。

考虑在 $a$ 序列的广义笛卡尔树上 dp。更清晰的，对于一个广义笛卡尔树上的方点（这对应一个连续段）的区间 $[l_i,r_i]$ 我们 **暂且先仅保留 $S$ 在 $[l_i,r_i]$ 中的部分**，记录 $|S|$，以及当前是否有 $S\setminus T=\emptyset\Rightarrow S=T$。

合并两个儿子时对于 $|S|$ 做加法，$[S=T]$ 取与即可。

即：

$$
f_{u,i,p_1}\times f_{v,j,p_2} \to f'_{u,i+j,p_1\operatorname{and}p_2}
$$

进行完子树内的合并后考虑 **连续段内产生的贡献**：

$$
f_{u,i,p}\times\left(2^{|[l_u,r_u]|-i}-(1-p)\right)^{b_u}\to f_{u,i,p}
$$

其中 $b_u$ 为该方点和其父亲节点 $a$ 值之差，也就是该连续段的 **厚度**。

核心在于：对于一个节点 $u$ 的两个儿子，**其对应区间无交**。

圆点有何用？初始化 $(-1)^{|T|}$ 的系数。

$$
\begin{aligned}
& f_{u,0,1}=f_{u,1,0}=1\\
& f_{u,1,1}=-1
\end{aligned}
$$

由于转移需要快速幂，所以复杂度即为 $\mathcal{O}(n^2\log{V})$。

## Code

[Submission Link](https://atcoder.jp/contests/agc041/submissions/60911882)。

## Others

这时候再来回头看看为啥 $S$ 是 **枚举**。

**钦定** 表示为强制令 $S$ 中的每一列均存在违反限制的格子，而不在 $S$ 中的列是不进行约束的（这样就导致了 **钦定** 往往带有额外的容斥系数）。

但其实注意到 **不进行约束** 的方案数是很难计算的，因为你无法很好地计算 **既可以有违反格子也可以无违反格子** 的方案数。

所以我们强制钦定不在 $S$ 中的列均不能有违反的格子，这样子也就能快速算方案数了。

---

## 作者：Log_x (赞：15)

## Solution

每次取出区间中 $h$ 的最小值建出笛卡尔树，令每个结点表示一个区间，从叶子结点往上 DP。

考虑容斥，即钦定若干个方格没有被 `車` 覆盖，求出此时的方案数，设选中的方格个数为 $t$，容斥系数为 $(-1)^{t}$。

注意到如果一个方格被钦定，方格所在的列一定没有 `車`。

于是我们在状态中记录钦定没有 `車` 的列的数量，设 $f_{s,i}$ 表示在结点 $s$ 共有 $i$ 列钦定没有 `車` 的容斥系数乘上方案数的和。

两个子区间的合并只需要考虑中间新增的那一列是否被钦定即可。

对于填结点 $s$ 所包含的每个行连续段的情况，我们进行一些讨论，设区间长度为 $len$，共有 $i$ 列钦定没有 `車`：

1. 若连续段中没有选择任何一个方格钦定没有被 `車` 覆盖，方案数为 $2^{len - i}$；
2. 若连续段中选择了一些方格钦定没有被 `車` 覆盖，连续段中不能再填 `車`，容斥系数和为 $\sum \limits_{k = 1}^{i}(-1)^kC_{i}^{k} = -[i \neq 0]$。

因此转移前的系数和为 $2^{len - i} - [i \neq 0]$。

但这样做是有一些问题的，因为我们无法保证钦定的列中都有方格被选。

考虑再次容斥，我们钦定有 $j$ 列在第一次钦定后没有方格被选，容斥系数为 $(-1)^j$。

那么只有第二种情况的系数和变为了 $\sum \limits_{k = 1}^{i - j}(-1)^kC_{i}^{k} = -[i \neq j]$，总的系数和为 $2^{len - i} - [i \neq j]$。

因此我们并不关心 $j$ 的取值，只需要在状态中额外记录一维表示 $i$ 是否等于 $j$ 即可。

时间复杂度 $\mathcal O(N^2)$。

## Code
```cpp
#include <bits/stdc++.h>

const int N = 1e4 + 5;
const int mod = 998244353;
int len[N], ex[N], f[N][N], g[N][N], h[N];
int n, T, rt;

inline int quick_pow(int x, int k)
{
	int res = 1;
	while (k)
	{
		if (k & 1)
			res = 1ll * res * x % mod;
		x = 1ll * x * x % mod;
		k >>= 1;
	}
	return res;
}

inline void add(int &x, int y)
{
	x += y;
	x >= mod ? x -= mod : 0;
}

inline void dec(int &x, int y)
{
	x -= y;
	x < 0 ? x += mod : 0;
}

inline int solve(int l, int r, int lst)
{
	if (l > r)
		return 0;
	
	int mid = l, now = ++T;
	for (int i = l + 1; i <= r; ++i)
		if (h[i] < h[mid])
			mid = i;

	int lc = solve(l, mid - 1, h[mid]),
		rc = solve(mid + 1, r, h[mid]);
	for (int i = 0; i <= len[lc]; ++i)
		for (int j = 0; j <= len[rc]; ++j)
		{
			int t = i + j;
			int a = 1ll * f[lc][i] * f[rc][j] % mod,
				b = (1ll * g[lc][i] * (f[rc][j] + g[rc][j]) + 1ll * f[lc][i] * g[rc][j]) % mod;
			add(f[now][t], a);
			add(g[now][t], b);
			dec(f[now][t + 1], a);
			add(g[now][t + 1], a);
		}
	len[now] = len[lc] + len[rc] + 1;
	for (int j = 0; j <= len[now]; ++j)
	{
		f[now][j] = 1ll * f[now][j] * quick_pow(ex[len[now] - j], h[mid] - lst) % mod;
		g[now][j] = 1ll * g[now][j] * quick_pow(ex[len[now] - j] - 1, h[mid] - lst) % mod;
	}
	return now;
}

int main()
{
	f[0][0] = 1;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &h[i]);

	ex[0] = 1;
	for (int i = 1; i <= n; ++i)
		add(ex[i] = ex[i - 1], ex[i - 1]);
	rt = solve(1, n, 0);

	int ans = 0;
	for (int i = 0; i <= n; ++i)
	{
		add(ans, f[rt][i]);
		add(ans, g[rt][i]);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：whileAK (赞：12)

### 题意：
>有一个 $n$ 行的棋盘，第 $i$ 行长度为 $h_i$ ，左对齐。
>
>一个格子可以放一个“車”，一个格子若和一个“車”同一行或同列，且中间都是棋盘，则称该格子被覆盖。求所有格子都被覆盖的方案数。
>
>$n$ 可以开到 $5000$ 。

其它题解都比较抽象，看了半天才懂QAQ。来一发更加详细的，当作自己做这题的总结。

我们称没被覆盖的格子为空格子，“車”称为棋子。

要求的是没有空格子的方案数。你发现直接求是非常困难的——那就迂回地求，考虑容斥。我们枚举所有格子集合 $U$ ，求出使这些格子集合中所有格子为空的方案数，再乘上容斥系数 $(-1)^{|U|}$ ，再求和就是答案。我们发现，如果一行内有至少一个空格子，这行的任意位置都不能有棋子。这就启发我们枚举 $U$ 所在的行的集合 $S$ ，即 $S$ 中的行都至少有一个空格子且 $U$ 中所有空格子都在 $S$ 中的 $U$ 的贡献之和。因此，答案应该为：
$$ans=\sum_SV(S)$$
其中 $V(S)$ 为所有 $S$ 中的行都至少有一个空格子且 $U$ 中所有空格子都在 $S$ 中的 $U$ 贡献之和。这样刚好覆盖了所有 $U$ 恰好一次。

进一步，我们发现若一个列上的**极长连续段**有空格子，这个连续段也不能放棋子，同时每个段是独立的。因此，为了求 $v(S)$ ，我们需要把每个极长连续段拎出来计算。对于一个长 $len$ 的连续段，若有 $p$ 行属于 $S$ ，则这段（记为段 $l$ ）的贡献为：
$$
v(l)=2^{len-p}+\sum_{i=1}^p(-1)^iC_p^i=2^{len-p}-[p>0]
$$
然后所有段的贡献相乘，即为 $V(S)$。

上式第一项表示若这一列没有空格子，则只要不在那 $p$ 行上放棋子，剩下的随便，就有 $2^{len-p}$ 。若放空格子，枚举空格子个数 $i$ ,有 $C_p^i$ 种方法放空格子，这部分容斥系数为 $(-1)^i$ ，相加等于 $-[p>0]$ 。为什么可以单独计算一段求和再全部相乘呢？因为每段之间是独立的且刚好覆盖了所有格子，如果把乘法拆开，每一项就是对应了每一个 $U$ 的贡献。

但这样求出来的 $V(S)$ 不是正确的。因为 $S$ 要求所有 $S$ 中的行都至少有一个空格子，而上述式子只能保证钦定的行没有棋子，可能每列都有棋子，刚好覆盖整行。于是，我们再容斥，枚举 $T\subset S$ 表示钦定所有 $T$ 中的行都一定**没有空格子**的方案数，容斥系数为 $(-1)^{|T|}$ ，则
$$
V(S)=\sum_{T\subset S}(-1)^{|T|}V(S,T)
$$
$$
V(S,T)=\prod v(l)
$$
若 $T$ 中有 $q$ 行在 $l$ 中：
$$
v(l)=2^{len-p}+\sum_{i=1}^{p-q}(-1)^iC_{p-q}^i=2^{len-p}-[p-q>0]=2^{len-p}-[p\ne q]
$$
所以最终答案为
$$
ans=\sum_T\sum_{T\subset S}(-1)^{|T|}\prod_l(2^{len-p}-[p-q>0])
$$
枚举 $S,T$ 即可做到 $O(3^n nm)$

~~搞了半天复杂度好像还是很劣~~

那我们考虑如何优化。我们发现 $v(l)$ 只和 $p,q$ 有关，如果一个极长连续段 $l$ 的 $p,q$ 确定了，我们可以把 $v(l)$ 提出来，算其它段的贡献和，最后乘上 $v(l)$ 。这就启发我们 $dp$ 。

怎么 $dp$ 呢？我们可以建笛卡尔树，每个节点对应一组连续的极长连续段，如图：

![图片](https://cdn.luogu.com.cn/upload/image_hosting/2xxvstz5.png)

图片来自蒯 @Itst 神。

计 $f[u][p][op]$ 表示对于点 $u$ 的子树，有 $p$ 条 $S$ 的行，$q$ 是否等于 $p$ ，该子树的贡献。计左右儿子为 $ls,rs$ ，容易发现 

$p_u=p_{ls}+p_{rs}+[中间那行是否属于S]$ 

$op_u=op_{ls}\&op_{rs}\&[中间那行是否属于T]$ 

据此分类即可转移。

这其实就是树上背包，复杂度为 $O(n^2)$ 。若在背包过程中算快速幂的话总复杂度是 $O(n^2\log n)$ ,但发现只有 $O(n)$ 种底和幂，所以可以 $O(n^2)$ 计算次幂，总复杂度为 $O(n^2)$ 。难绷的是， $O(n^2)$ 的跑得还没 $O(n^2\log n)$ 快， $O(n^2\log n)$ 的甚至成了最优解，可能是因为原题数据太小了。
### Code
$O(n^2\log n)$
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void rd(int &p){
	p=0;char z=getchar();int f(0);
	while(z>'9'||z<'0'){if(z=='-')f^=1;z=getchar();}
	while(z<='9'&&z>='0')p=(p<<1)+(p<<3)+z-'0',z=getchar();
	if(f)p=-p;
}
void rdl(ll &p){
	p=0;char z=getchar();int f(0);
	while(z>'9'||z<'0'){if(z=='-')f^=1;z=getchar();}
	while(z<='9'&&z>='0')p=(p<<1)+(p<<3)+z-'0',z=getchar();
	if(f)p=-p;
}
const int N=5050;
const ll mod=998244353;
int n,a[N];
int ls[N],rs[N],st[N],tp(0),rt(0);
ll f[N][N][2],pw[N];
ll qp(ll x,int y){
    ll ans(1);
    for(;y;y>>=1){
        if(y&1)ans=ans*x%mod;
        x=x*x%mod;
    }return ans;
}
void sl(int p,int l,int r,int d){
    if(!p)return;
    sl(ls[p],l,p-1,a[ls[p]]-a[p]);
    sl(rs[p],p+1,r,a[rs[p]]-a[p]);
    int len=r-l+1;
    ll bs1,bs2;
    for(int i(0);i<=p-l;++i){
        for(int j(0);j<=r-p;++j){
            bs1=(f[ls[p]][i][0]+f[ls[p]][i][1])*(f[rs[p]][j][0]+f[rs[p]][j][1])%mod;
            bs2=f[ls[p]][i][1]*f[rs[p]][j][1]%mod;
            f[p][i+j][0]+=bs1-bs2+mod;
            f[p][i+j][1]+=bs2;
            f[p][i+j+1][0]+=bs2;
            f[p][i+j+1][1]+=mod-bs2;
        }
    }
    for(int i(0);i<=len;++i){
        f[p][i][0]%=mod;f[p][i][1]%=mod;
        f[p][i][0]=f[p][i][0]*qp(pw[len-i]-1,d)%mod;
        f[p][i][1]=f[p][i][1]*qp(pw[len-i],d)%mod;
    }
}
int main(){
    rd(n);pw[0]=1;f[0][0][1]=1;
    for(int i(1);i<=n;++i)rd(a[i]);
    for(int i(1);i<=n;++i){
        while(tp&&a[st[tp]]>a[i])--tp;
        if(tp){
            ls[i]=rs[st[tp]];rs[st[tp]]=i;
        }
        else{
            ls[i]=rt;rt=i;
        }pw[i]=pw[i-1]*2%mod;st[++tp]=i;
    }sl(rt,1,n,a[rt]);
    ll ans(0);
    for(int i(0);i<=n;++i){
        ans+=f[rt][i][0]+f[rt][i][1];
    }ans%=mod;
    printf("%lld",ans);
	return 0;
}
```
$O(n^2)$
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void rd(int &p){
	p=0;char z=getchar();int f(0);
	while(z>'9'||z<'0'){if(z=='-')f^=1;z=getchar();}
	while(z<='9'&&z>='0')p=(p<<1)+(p<<3)+z-'0',z=getchar();
	if(f)p=-p;
}
void rdl(ll &p){
	p=0;char z=getchar();int f(0);
	while(z>'9'||z<'0'){if(z=='-')f^=1;z=getchar();}
	while(z<='9'&&z>='0')p=(p<<1)+(p<<3)+z-'0',z=getchar();
	if(f)p=-p;
}
const int N=5050;
const ll mod=998244353;
int n,a[N];
int ls[N],rs[N],st[N],tp(0),rt(0);
ll f[N][N][2],pw[N],s1[N][N],s2[N][N];
void sl(int p,int l,int r,int d){
    if(!p)return;
    sl(ls[p],l,p-1,a[ls[p]]-a[p]);
    sl(rs[p],p+1,r,a[rs[p]]-a[p]);
    int len=r-l+1;
    ll bs1,bs2;
    for(int i(0);i<=p-l;++i){
        for(int j(0);j<=r-p;++j){
            bs1=(f[ls[p]][i][0]+f[ls[p]][i][1])*(f[rs[p]][j][0]+f[rs[p]][j][1])%mod;
            bs2=f[ls[p]][i][1]*f[rs[p]][j][1]%mod;
            f[p][i+j][0]+=bs1-bs2+mod;
            f[p][i+j][1]+=bs2;
            f[p][i+j+1][0]+=bs2;
            f[p][i+j+1][1]+=mod-bs2;
        }
    }
    for(int i(0);i<=len;++i){
        f[p][i][0]%=mod;f[p][i][1]%=mod;
        f[p][i][0]=f[p][i][0]*s2[len-i][d]%mod;
        f[p][i][1]=f[p][i][1]*s1[len-i][d]%mod;
    }
}
int main(){
    rd(n);pw[0]=1;f[0][0][1]=1;
    for(int i(1);i<=n;++i)rd(a[i]);
    for(int i(1);i<=n;++i){
        while(tp&&a[st[tp]]>a[i])--tp;
        if(tp){
            ls[i]=rs[st[tp]];rs[st[tp]]=i;
        }
        else{
            ls[i]=rt;rt=i;
        }pw[i]=pw[i-1]*2%mod;st[++tp]=i;
    }
    for(int i(0);i<=n;++i){
        s1[i][0]=s2[i][0]=1;
        for(int j(1);j<=n;++j){
            s1[i][j]=s1[i][j-1]*pw[i]%mod;
            s2[i][j]=s2[i][j-1]*(pw[i]-1)%mod;
        }
    }sl(rt,1,n,a[rt]);
    ll ans(0);
    for(int i(0);i<=n;++i){
        ans+=f[rt][i][0]+f[rt][i][1];
    }ans%=mod;
    printf("%lld",ans);
	return 0;
}
```

---

## 作者：whiteqwq (赞：7)

[AT5697 [AGC041F] Histogram Rooks](https://www.luogu.com.cn/problem/AT5697)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1786477)

## 题意
给定一个$n$列的棋盘，每一列高度为$h_i$，可以放置若干个車（不用考虑車之间会不会影响），需要把整个棋盘覆盖，求方案数。（$1\leqslant n\leqslant 400$）

## 分析
容斥毒瘤题，代码$10$分钟，思维$10$小时。

首先看到这一种棋盘的模型（可见[P6453 [COCI2008-2009#4] F](https://www.luogu.com.cn/problem/P6453)）果断建出笛卡尔树，然后考虑在上面dp（就是按照最小值分治，把棋盘分成类似下面这样）。

![](https://fp1.fghrsh.net/2021/03/30/26b815d61705423cad859615915bb73b.png)

看到这个覆盖满很容易想到容斥，那么很容易第一时间定义$f_{i,j}$为笛卡尔树上结点$i$有至少$k$个格子没有被覆盖（下文称这些点为关键点）的方案数乘上容斥系数$(-1)^k$。

但是这个状态定义的就是$O(n^3)$，空间会炸，因此我们改变定义：$f_{i,j}$为笛卡尔树上结点$i$一共有$j$列不能放車（注意，这里是不能放車，这些列有可能是没有关键点的）的方案数乘上容斥系数$(-1)^j$，那么我们只需要关注每一个极长行连续段上是否有关键点。

我们设不能放車的列集合为$S_0$，不难发现$S_0$是无法约束关键点的，因此再次容斥，设关键点所在的列集合$S_1(S_1\subseteq S_0)$，容斥系数为$(-1)^{|S_1|}$，通过容斥简化问题后，我们讨论当前节点的决策：

设当前节点为$x$，区间长度（列数）为$len_x$，$|S_0|=k$，那么：

- 如果$|S_1|=0$，方案数为$2^{len_x-k}$。
- 如果$|S_1|>0$，我们枚举$|S_1|$的大小为$t$，然后枚举$S_0$除了$S_1$的部分有多少列真正被覆盖了，那么可知道算上容斥系数后贡献之和为$\sum_{i=1}^{k-t}(-1)^k{k\choose i}$，这个东西可以化简成$-[k\ne t]$。

那么可以发现我们并不关心$t$，而是只关心$t$是否等于$k$了，直接开一维枚举$t$是否等于$k$。

具体操作就是类似树形背包，合并左右儿子的信息并进行当前结点的决策：枚举左儿子有$i$列不能放車，右儿子有$j$列不能放車，那么当前结点有$i+j$或$i+j+1$列不能放車。设$a$为左子树和右子树均没有贡献满的方案数，$b$为左子树和右子树至少有一个贡献满的方案数，那么经过讨论不难发现：

$$a\rightarrow f_{x,k,0},b\rightarrow f_{x,k,1},-a\rightarrow f_{x,k+1,0},a\rightarrow f_{x,k+1,1}$$

```cpp
int p=lc[x],q=rc[x];
for(int i=0;i<=size[p];i++)
	for(int j=0;j<=size[q];j++){
		int k=i+j;
		int a=1ll*f[p][i][0]*f[q][j][0]%mod;
		int b=(1ll*f[p][i][0]*f[q][j][1]%mod+1ll*f[p][i][1]*f[q][j][0]%mod+1ll*f[p][i][1]*f[q][j][1]%mod)%mod;
		f[x][k][0]=(f[x][k][0]+a)%mod,f[x][k][1]=(f[x][k][1]+b)%mod;
		f[x][k+1][0]=(f[x][k+1][0]-a)%mod,f[x][k+1][1]=(f[x][k+1][1]+a)%mod;
	}
```

记得dp完乘上没有讨论的所有点贡献的$2$的次幂，当然求幂的地方可以直接预处理代替快速幂优化掉$\log$。

复杂度：$O(n^2)$。

## 代码
```cpp
#include<stdio.h>
const int maxn=405,mod=998244353;
int n,rt,top,ans;
int a[maxn],stk[maxn],lc[maxn],rc[maxn],f[maxn][maxn][2],bin[maxn],size[maxn],mul[maxn][maxn][2];
void dfs(int x,int last){
	if(x==0)
		return ;
	int p=lc[x],q=rc[x];
	dfs(p,a[x]),dfs(q,a[x]);
	for(int i=0;i<=size[p];i++)
		for(int j=0;j<=size[q];j++){
			int k=i+j,a=1ll*f[p][i][0]*f[q][j][0]%mod,b=(1ll*f[p][i][0]*f[q][j][1]%mod+1ll*f[p][i][1]*f[q][j][0]%mod+1ll*f[i][i][1]*f[q][j][1]%mod)%mod;
			f[x][k][0]=(f[x][k][0]+a)%mod,f[x][k][1]=(f[x][k][1]+b)%mod;
			f[x][k+1][0]=(f[x][k+1][0]-a)%mod,f[x][k+1][1]=(f[x][k+1][1]+a)%mod;
		}
	size[x]=size[p]+size[q]+1;
	for(int i=0;i<=size[x];i++){
		f[x][i][0]=1ll*f[x][i][0]*mul[size[x]-i][a[x]-last][0]%mod;
		f[x][i][1]=1ll*f[x][i][1]*mul[size[x]-i][a[x]-last][1]%mod;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	bin[0]=1;
	for(int i=1;i<=n;i++)
		bin[i]=(bin[i-1]<<1)%mod;
	for(int i=0;i<=n;i++){
		mul[i][0][0]=mul[i][0][1]=1;
		for(int j=1;j<=n;j++){
			mul[i][j][0]=1ll*mul[i][j-1][0]*bin[i]%mod;
			mul[i][j][1]=1ll*mul[i][j-1][1]*(bin[i]-1)%mod;
		}
	}
	for(int i=1;i<=n;i++){
		int k=top;
		while(k>0&&a[stk[k]]>a[i])
			k--;
		if(k>0)
			rc[stk[k]]=i;
		if(k<top)
			lc[i]=stk[k+1];
		stk[++k]=i,top=k;
	}
	rt=stk[1],f[0][0][0]=1,dfs(rt,0);
	for(int i=0;i<=n;i++)
		ans=(ans+(f[rt][i][0]+f[rt][i][1])%mod)%mod;
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：6)

神题！！！！！！！！！/bx

全部格子都被覆盖不好处理，考虑钦定 $k$ 个格子不被覆盖，容斥系数就是 $(-1)^k$。

发现网格的行不一定连续，但是列是连续的。如果一列有格子被钦定，那么这一列就不能放棋子。

由此想到枚举不能放棋子的列（至少有一个棋子被钦定的列）集合 $S$，把每个行连续段的贡献相乘。

设行连续段有 $len$ 个格子，其中 $p$ 个格子所在列属于 $S$，那么如果这个行连续段没有格子被钦定，每个所在列不属于 $S$ 的格子都能放棋子，贡献是 $2^{len - p}$；如果至少一个格子被钦定，枚举钦定了几个格子，得贡献为 $\sum\limits_{i = 1}^p \binom{p}{i} (-1)^i = -[p > 0]$。

但是很容易看出来一个问题，就是 $S$ 中的列不一定至少有一个棋子被钦定。

仍然考虑容斥，钦定 $T \subseteq S$ 为没有格子被钦定的列集合，容斥系数为 $(-1)^{|T|}$；设行连续段中有 $q$ 个格子所在列属于 $T$，那么如果这个行连续段没有格子被钦定，贡献仍然是 $2^{len - p}$；如果至少一个格子被钦定，贡献为 $\sum\limits_{i = 1}^{p - q} \binom{p - q}{i} (-1)^i = -[p - q > 0] = -[p > q]$。计算答案就把每个行连续段这样的贡献相乘即可。

枚举 $S, T$ 复杂度显然过高，考虑简化。

首先我们发现只有连续段中 $|S| = p, [|S| > |T|] = [p > q]$ 在计算贡献时有用。

然后考虑把网格按 $h_i$ 的笛卡尔树剖分成若干个行连续段的贡献相同的形式，像这样（图来自 [Verdandi](https://www.luogu.com.cn/blog/xiaoziyaoxzy/solution-at5697)）：

![](https://fp1.fghrsh.net/2021/03/30/26b815d61705423cad859615915bb73b.png)

建出笛卡尔树，发现相邻的色块（父亲与儿子）相互依赖。比如上图，绿色块的 $p$ 等于第 $1, 3, 5$ 列是否被 $S$ 包含加上橙色块的 $p$ 加上黄色块的 $p$ 加上粉色块的 $p$，同理，$[p > q]$ 是所有子结点的 $[p > q]$ 的或（或者可以维护 $[p = q]$，就是所有子结点的 $[p = q]$ 的与）。

考虑一个树形 dp，$f_{u, i, 0/1}$ 表示 $u$ 结点目前 $p = i$，$[p = q] = 0/1$ 的容斥系数 $(-1)^{|T|}$ 乘贡献之和。我们首先考虑空行，也就是 $f_{u, 0, 1} = f_{u, 1, 0} = 1, f_{u, 1, 1} = -1$（对于 $h_i$ 相同的子结点强制钦定一个父子顺序）。然后树形背包合并上来子结点。最后乘上若干行（设为 $b_u$）连续段的贡献，也就是 $(2^{sz_u - p} - [p > q])^{b_u}$。

快速幂计算贡献是 $O(n^2 \log n)$，容易通过预处理这个贡献做到 $O(n^2)$。

[code](https://atcoder.jp/contests/agc041/submissions/45309974)

---

## 作者：pufanyi (赞：5)

首先考虑到这样一件事情，就是如果用 $\left<l,r,h\right>$ 表示的是 $[l,r]$ 区间内，纵坐标大于 $h$ 的格子，我们定义一个这样的三元组为一个状态。

然后我们考虑对于每个状态，它里面的格子，如果要合法的话，每一列一定是下面三种中的其中一种：
1. 这一列中至少有一个车。这时候的话，这一列中的每个格子就一定合法。
2. 这一列没有车，但是这些格子都被一个车覆盖到了，也就是说这个二元组所包含的格子中没有。
3. 这一列没有车，而且部分格子并没有被车覆盖到，这时候，就这一列只能在 $h$ 下面有车才能合法。

现在我们考虑 `dp`，$f_{t,i,j}$ 表示状态为 $t$ 的时候，现在有 $i$ 个 $2$ 类点，$j$ 个 $3$ 类点，那么显然 $1$ 类点就是 $r-l+1-i-j$ 个。

然后我们考虑转移，我们考虑 $t$ 所表示的方格是否完全被分成了两块，也就是 $h$ 是否跟 $[l,r]$ 中最小的 $a$ 相等。如果是的话，那么我们就将其分成两半进行 `dp`，记左边那个状态为 $l(t)$，右边为 $r(t)$，那么我们可以得到转移 $f_{t,i,j+1}=\sum_{a,b}f_{l(t),a,b}\cdot f_{r(t),i-a,j-b}$，因为两块是不相干的。

然后我们如果没有，也就是说我们要从 $\left<l,r,h+1\right>$ 向 $\left<l,r,h\right>$ 转移。我们令$u=\left<l,r,h+1\right>$，$k,i,j$ 分别表示三类列的数量。这个转移需要分 $2$ 中情况讨论：
1. 如果这一行不放车：$f_{t,0,i+j}\leftarrow f_{u,i,j}$。
2. 如果这一行的车只放在一类列上：$f_{t,i,j}\leftarrow f_{u,i,j}\cdot (2^{k_1}-1)$。
3. 如果 $x$ 个车放在 $2$ 类列，$y$ 个车放在 $3$ 类列：$f_{t,i-x,j-y}\leftarrow f_{u,i,j}\cdot\binom{i}{x}\binom{j}{y}\cdot2^{k}$。

我们考虑优化这个 `dp`。

我们发现对于一个状态 $t$，有两种形式：
1. 每一行都至少有一辆车。
2. 有一行没有车。

为什么要把这两种分开来讨论呢？

我们考虑这两种有什么不一样。第一种形式，都有一个车，那么就没有第 $3$ 类列了，否则如果是第二种形式，那就最终就没有第 $2$ 类列了。这样子，其实我们就相当于分两种情况，把 $2$ 类列和 $3$ 类列看成是一个东西一起转移了，可以把她们放在同一维里，然后加一维 $0/1$ 即可。

这样第二种转移的时候，我们也只要枚举一维 $x$ 表示 $2,3$ 类列总的放车个数，考虑到复杂度为 $\sum \ell^2$，$\ell$ 表示的是每个有用状态的长度，不难发现复杂度为 $\mathcal{O}(n^3)$。

---

## 作者：DaiRuiChen007 (赞：4)

# AGC041F 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_agc041_f)

**题目大意**

> 考虑一个 $n$ 行的棋盘，第 $i$ 行宽度为 $[1,h_i]$，请问有多少种在棋盘中放棋子的方案，使得每个格子所在的行、列连续段中至少有一个棋子。
>
> 数据范围：$n\le 400$。

**思路分析**

朴素的想法就是容斥每个不能被覆盖的点（称为关键点），然后算剩下的位置的数量。

我们可以考虑枚举所有关键点所在的行集合 $S$。

然后对于每个列的连续段计算方案数：设连续段长度为 $len$，其中有 $s$ 行在 $S$ 中：

- 如果 $s$ 个点中没有点被设为关键点，那么方案数为 $2^{len-s}$。
- 如果有至少一个点被设为关键点，那么枚举关键点数 $i$，容斥系数就是 $(-1)^i$，贡献为 $\sum_{i=1}^s\binom si(-1)^i=-[s>0]$。

因此对于这样的一个组，其方案数为 $2^{len-s}-[s>0]$。

但是这样枚举的 $S$ 不能保证每行至少有一个关键点，因此我们枚举 $T\subseteq S$ 表示钦定没有关键点的行集合，容斥系数为 $(-1)^T$。

不妨设一个列连续段里有 $t$ 个行在 $T$ 中，那么这个列连续段的贡献就是 $(-1)^t(2^{len-s}-[s>t])$。

对于这种棋盘问题，一个很自然的想法就是建小根笛卡尔树，然后在树上 dp。

注意到我们只需要记录 $s,[s>t]$ 两个状态，那么我们可以记录 $f_{u,s},g_{u,s}$ 表示 $[s=t]$ 和 $[s>t]$ 两种状态的方案的总贡献。

转移类似树形背包，最后给每个 $f_{u,s},g_{u,s}$ 乘以一个列连续段的 $h_u-h_{fa}$ 次方即可。

时间复杂度 $\mathcal O(n^2\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=405,MOD=998244353;
ll f[MAXN][MAXN],g[MAXN][MAXN]; //f:[p=q], g:[p>q]
ll pw[MAXN],tf[MAXN],tg[MAXN];
int n,h[MAXN],siz[MAXN];
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
int solve(int l,int r,int fa) {
	int u=l;
	for(int i=l+1;i<=r;++i) if(h[u]>h[i]) u=i;
	f[u][0]=1,g[u][1]=1,f[u][1]=MOD-1,siz[u]=1;
	if(l<u) {
		int v=solve(l,u-1,h[u]);
		memset(tf,0,sizeof(tf)),memset(tg,0,sizeof(tg));
		for(int i=0;i<=siz[u];++i) for(int j=0;j<=siz[v];++j) {
			tf[i+j]=(tf[i+j]+f[u][i]*f[v][j])%MOD;
			tg[i+j]=(tg[i+j]+g[u][i]*g[v][j]+f[u][i]*g[v][j]+g[u][i]*f[v][j])%MOD;
		}
		swap(tf,f[u]),swap(tg,g[u]),siz[u]+=siz[v];
	}
	if(u<r) {
		int v=solve(u+1,r,h[u]);
		memset(tf,0,sizeof(tf)),memset(tg,0,sizeof(tg));
		for(int i=0;i<=siz[u];++i) for(int j=0;j<=siz[v];++j) {
			tf[i+j]=(tf[i+j]+f[u][i]*f[v][j])%MOD;
			tg[i+j]=(tg[i+j]+g[u][i]*g[v][j]+f[u][i]*g[v][j]+g[u][i]*f[v][j])%MOD;
		}
		swap(tf,f[u]),swap(tg,g[u]),siz[u]+=siz[v];
	}
	for(int i=0;i<=siz[u];++i) {
		f[u][i]=f[u][i]*ksm(pw[r-l+1-i],h[u]-fa)%MOD;
		g[u][i]=g[u][i]*ksm(pw[r-l+1-i]-1,h[u]-fa)%MOD;
	}
	return u;
}
signed main() {
	scanf("%d",&n);
	for(int i=pw[0]=1;i<=n;++i) pw[i]=pw[i-1]*2%MOD;
	for(int i=1;i<=n;++i) scanf("%d",&h[i]);
	int rt=solve(1,n,0); ll ans=0;
	for(int i=0;i<=n;++i) ans=(ans+f[rt][i]+g[rt][i])%MOD;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Komomo (赞：1)

如果直接对这个笛卡尔树决策，发现大部分都是高复杂度的 $\mathcal O(\text{poly}(n))$ 做法。但是题目给出的这个条件转化一下，就是每个格子必须被一个车覆盖到，满足所有条件反过来容斥。钦定 $i$ 个格子不能被覆盖（以下称为白格子），系数就是 $(-1)^i$，时间复杂度 $\mathcal O(2^{n^2}\text{poly}(n))$。

正常观察到一列如果放了一个白格子，那么整列都填不了，大量减少了信息量。转而枚举含有白格子的列集合 $S$（注意这里要求 $U\backslash S$ 必须没有白格子），列已经枚举完，考虑行。对于每个长度为 $len$ 的行连续段，如果有 $p$ 个格子在 $\in S$ 的列中：

- 连续段没有白格子，那么剩下 $len-p$ 个可以随便填，方案数为 $2^{len-p}$。
- 如果有白格子，方案数为 $\sum\limits_{i=1}^p(-1)^i\dbinom{p}{i}=-[p\not=0]$。

但是这样算不能保证 $S$ 的每一列都有白格子，再容斥一层，钦定 $T\subseteq S$ 不能有白格子，那么如果 $|T|=q$，第二个条件的贡献就变成了 $-[p\not= q]$，时间复杂度 $\mathcal O(3^n\text{poly}(n))$。

发现贡献只和 $p,[p\not=q]$ 有关，而且两个是容易合并的。现在就可以对这个笛卡尔树决策了，令 $f_{u,i,j}$ 表示在节点 $u$，$i=p,j=[p\not=q]$，合并是树上背包复杂度，套个快速幂，预处理一下可以做到 $\mathcal O(n^2)$。

---

## 作者：JCY_ (赞：1)

[更好的阅读体验](https://www.cnblogs.com/JCY-std/p/18160639)

考察一个合法的棋盘，有一些列上有车，其他的列没有车。

有车的列所有格子都被覆盖，没有车的列上的每个格子都需要被同一行的车覆盖。

即考察所有极长的行连续段，如果这个连续段涉及的列里包含没有车的列，那么这个行连续段里必须有车。

考虑枚举有车的列的集合 $S$，对于每个行连续段，记它涉及的列集合与 $S$ 的交集大小为 $c$，如果它包含没有车的列则方案数为 $2^c - 1$，否则方案数为 $2^c$。

容易发现这么计数不能保证 $S$ 里的列都有车，再枚举 $T \subseteq S$ 表示钦定 $T$ 里的列没有车，容斥系数为 $(-1)^T$，把上一段里与 $S$ 的交集改为与 $S - T$ 的交集即可。

一个自然的分治过程是找到当前最低的列 $i$ 然后把最底下的 $h_i$ 行删掉，这样棋盘就被分成了不相关的两个部分。根据这个分治过程进行 dp 相当于建出笛卡尔树然后自底向上进行 dp。

设 $dp_{u, i, 0/1}$ 表示考察 $u$ 的子树，共有 $i$ 个列属于 $S - T$，是否有不属于 $S$（即没有车）的列。

合并两个儿子是树形背包，然后枚举当前的最低列属于三个部分的哪一个进行转移，再对每个在分治过程中删掉的行连续段乘上 $2^c$ 或 $2^c - 1$ 的系数即可。

注意乘上系数的快速幂复杂度可以摊到每个格子上，因此时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using i128 = __int128;
using u128 = unsigned __int128;
template <typename T>
void chkmax(T &x, const T &y) {
  if (x < y) x = y;
}
template <typename T>
void chkmin(T &x, const T &y) {
  if (y < x) x = y;
}
constexpr int MOD = 998244353;
void inc(int &x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
}
int add(int x, int y) {
  x += y;
  return x >= MOD ? x - MOD : x;
}
int neg(int x) { return x ? MOD - x : 0; }
void upd(int &x, ll y) { x = (x + y) % MOD; }
int qpow(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1, x = (ll)x * x % MOD)
    if (y & 1) ret = (ll)ret * x % MOD;
  return ret;
}
constexpr int MAXN = 405;
int n, h[MAXN], stk[MAXN], tp, ls[MAXN], rs[MAXN];
int dp[MAXN][MAXN][2], pw2[MAXN];
void dfs(int u, int pre, int l, int r) {
  if (!u) return;
  dfs(ls[u], u, l, u - 1);
  dfs(rs[u], u, u + 1, r);
  for (int i = 0; i <= u - l; ++i) {
    for (int x = 0; x < 2; ++x) {
      if (!dp[ls[u]][i][x]) continue;
      for (int j = 0; j <= r - u; ++j) {
        for (int y = 0; y < 2; ++y) {
          if (!dp[rs[u]][j][y]) continue;
          upd(dp[u][i + j][x || y], (ll)dp[ls[u]][i][x] * dp[rs[u]][j][y]);
        }
      }
    }
  }
  for (int i = r - l; i >= 0; --i) {
    inc(dp[u][i + 1][0], dp[u][i][0]);
    inc(dp[u][i + 1][1], dp[u][i][1]);
    dp[u][i][1] = dp[u][i][0];
    dp[u][i][0] = neg(dp[u][i][0]);
  }
  for (int i = 0; i <= r - l + 1; ++i) {
    dp[u][i][0] = (ll)dp[u][i][0] * qpow(pw2[i], h[u] - h[pre]) % MOD;
    dp[u][i][1] = (ll)dp[u][i][1] * qpow(pw2[i] - 1, h[u] - h[pre]) % MOD;
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> h[i];
  for (int i = 1; i <= n; ++i) {
    while (tp && h[i] < h[stk[tp]]) ls[i] = stk[tp--];
    if (tp) rs[stk[tp]] = i;
    stk[++tp] = i;
  }
  for (int i = 1; i < tp; ++i) rs[stk[i]] = stk[i + 1];
  pw2[0] = 1;
  for (int i = 1; i <= n; ++i) pw2[i] = add(pw2[i - 1], pw2[i - 1]);
  dp[0][0][0] = 1;
  dfs(stk[1], 0, 1, n);
  int ans = 0;
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j < 2; ++j) inc(ans, dp[stk[1]][i][j]);
  cout << ans << "\n";
  return 0;
}
/*
g++ F.cpp -o F -std=c++14 -O2 -Wall -Wextra -Wshadow -g
-fsanitize=address,undefined
*/
```

---

## 作者：qiuzx (赞：1)

## 题意

有一个 $n\times n$ 的棋盘，每一列最上面若干个格子被挖掉了，只保留了最下面 $h_i$ 个。问有多少种在棋盘上放車的方案，使得每个位置都能被攻击到。車不能跨过被挖掉的格子。$n\le 400$。

## 思路

我们从下往上逐行考虑，直到某一行没有任何一个位置被选择。此时为了让这一行合法，必须要将每一列都选上。所以就做完了，要么每一行都有一个，要么每一列都有一个被选择。但是这样显然是不对的，因为这个实际上是矩形图上的做法，但在原来这个图上，如果一个比较靠上的行没有被选择，它只会要求所有涉及到它的列被选择，所以我们需要一些更好的定义来解决这个问题。

还是逐行考虑，这次我们只考虑 $h_i$ 的最小值下面的这些行。如果有至少一行没有任何一个棋子，则所有列都必须被选择。否则这些行都已经合法了，那么最小值会把序列剖成两段，这两段在上面是完全独立的，所以可以记 $f_{l,r}$ 表示区间 $[l,r]$ 的答案。然而问题是虽然在上面是独立的，但是在下面这部分每一行并不是在两侧都必须有棋子。而与下面填棋子的方案数有关的信息是上面还有几列在下面必须被选择（出现这些列的原因是在某一次一行没有被选择的时候一些列必须被选择，而这些列在上面还暂时没有被选）。所以修改一下 dp 状态，记 $f_{l,r,k}$ 表示考虑区间 $[l,r]$，还有 $k$ 列下面必须选择的方案数。考虑一下怎么转移。

对于一个区间 $[l,r]$ 而言，取出其最小值位置 $x$，先做 $[l,x-1]$ 和 $[x+1,r]$ 的 dp，其实就是笛卡尔树对应区间的两个儿子做一次 dp。下面分两种情况讨论。第一种是 $[l,r]$ 中每一行都选了。此时先把左右两个区间合并起来，然后依次考虑每一行。假设当前一共 $k$ 列需要被选择，枚举一个 $j$ 表示选择了这 $k$ 列中的几列，剩余可以随便选，组合数算一下贡献即可。需要注意由于此时要求每一行都被选择，所以不能什么都不选，要把这种转移去掉。第二种是 $[l,r]$ 中至少一列没有选。此时不使用两侧的 dp 值了，因为这里必须要求 $[l,r]$ 中每一列都要被选择，和更上面的东西无关。如果不管这几行是否要求被选，只是要对于每个 $k$ 求有 $k$ 列不选择的答案，显然每一列选择的方案数为 $2^{a_i}-1$，不选择的方案数为 $1$，可以背包计算。然而这样会算重每一行都选择的答案，不过这个可以看作是先填上面的，使用这个背包对于每个 $k$ 计算答案，再按照第一种情况中的方法依次考虑每一行进行进一步的转移。将这种的贡献减去即可。只有笛卡尔树对应的区间有用，总复杂度是 $O(n^3)$。

[代码](https://atcoder.jp/contests/agc041/submissions/49203346)

---

## 作者：AzusaCat (赞：1)

掉估值了，补一发题解。

给定 $n\times n$ 的棋盘，现在第 $i$ 列只有最底下 $h_i$ 个位置没被扣掉，现在往棋盘上未被扣掉的格子上放若干个车，使得每个没被扣掉的格子要不被某个车占领，要不可以被某个车攻击到（车不能跨过被扣掉的格子），求方案数。$n\leqslant 400$（可以改为 $3000$）。

我们称题目中的条件为“被覆盖”。考虑容斥，钦定某些位置一定未被覆盖，并计算每个行连续段的贡献，假设钦定 $k$ 个位置未被覆盖，则容斥系数为 $(-1)^k$。

我们注意到每一列都是连续的，所以我们考虑钦定某些列中存在未被覆盖的格子。设某个行连续段的长度为 $len$，这个行连续段有 $p$ 列被钦定未被覆盖。我们考虑这 $p$ 列中在这一行的格子是否被钦定，若一个都没有被钦定，则剩下 $p-len$ 个格子随便填，方案数为 $2^{len-p}$；若至少有一个格子被钦定，则剩下格子都不能填，方案数为 $1$，枚举钦定的格子数，带上容斥系数，这部分的总贡献是 $\sum\limits_{i=1}^p(-1)^i\dbinom{p}{i}=-[p \not= 0]$，所以这个行连续段的贡献为 $2^{len-p}-[p>0]$。

其实我们刚才那个容斥是假的，因为我们并没有保证存在钦定未被覆盖的格子的列真的存在了未被覆盖的格子（这句话有点绕，就是说对每个包含这列的行连续段我们都没钦定到这个列的格子，这样就算多了），为此我们再套一层容斥：设 $S$ 表示我们上面钦定的列的集合，$T$ 表示 $S$ 中一定不存在被钦定未被覆盖的格子的列的集合，那么这一层的容斥系数为 $(-1)^{|T|}$。

现在假设某行的连续段的长度为 $len$，这个行连续段有 $p$ 列在 $S$ 中，$q$ 列在 $T$ 中，那么现在这个行连续段的贡献变为了 $2^{len-p}+\sum\limits_{i=1}^{p-q}(-1)^i\dbinom{p+q}{i}=2^{len-p}-[p\not=q]$。注意到我们并不关心 $q$ 具体的值，我们只在乎 $p$ 是否等于 $q$，关于 $q$ 的容斥系数我们只需要在向 $T$ 中添加元素时同时加上即可。

现在考虑如何加速这个过程，考虑分治，如果我们每次取当前列的区间内的最小值，发现最小值到底端的行连续段都一致可以一起计算，就可以把区间分为两个子问题再合并，合并时只需要考虑当前列是否加入 $S$ 和 $T$（其实就是笛卡尔树）。

所以只需要设状态 $f(i,j,0/1)$ 表示当前 dp 到了矩形 $i$，$|S|=j$，$T$ 是否等于 $S$。 

由于我们只会访问 $O(n)$ 个连续的行连续段，所以总复杂度 $O(n^2\log n)$，如果预处理转移系数可以达到 $O(n^2)$。

---

## 作者：Purslane (赞：0)

# Solution

我觉得这道题挺简单的啊，至少我能切。 /yun

鉴于他是银牌黑题，我需要把题解写的复杂一点，但是基本思路非常简单——尝试多项式复杂度暴力，发现关键性质后进行容斥省掉一个维度。

显然这种结构需要类似笛卡尔树的东西：每次找到 $h_{\min}$ 并将其砍掉，然后递归处理子结构。

我们不急着做任何容斥，先想想直接暴力怎么做。（有 $O(n^3 \log n)$ 的暴力多项式做法，下文我们将提及一些基本思想而不做完整分析）

发现列的关系是可以继承的。假设我们考虑了水平线 $h=H$ 上的矩形，每一列只有三种状态：

1. $R$ 状态，表示这列已经放了一个車。
2. $S$ 状态，表示这列没有放車，但是这一列每个格子同行都有一个可到达的車。
3. $T$ 状态，表示这列没有放車，且这一列有至少一个格子同行没有可到达的車。

如下图所示：

![](https://s21.ax1x.com/2025/02/17/pEMQ5VJ.png)

$T$ 状态和 $S$ 状态不同的点在于，**之后这一列上必须放至少一个車**。

所以我们记录当前处理的矩形上放的所有列中，有多少个处于 $S$ 状态，多少个处于 $T$ 状态（$R$ 状态可以由列的状态减去它们两个得出）。记为 $dp_{u,s,t}$ 表示考虑了矩形 $u$ 以上的结构（矩形显然形成了树形结构。可以参考 lsj 题解中的“广义笛卡尔树”的图。）

特别的，如果这一列是当前最矮的，我们认为他当前是 $S$ 状态。

暴力的第一步，是利用树形背包将所有的列合并。这一步直接做是 $O(n^4)$ 的，但是如果你会二维卷积可以直接做到 $O(n^3 \log n)$。

第二步，考虑下面这个大的矩形。如果能找到一行没有任何車，我们将**所有的 $S$ 状态转化为 $T$ 状态**。而 $ST$ 状态的每一列只要放了一个車，就会变为 $R$ 状态。

因此我们容易求出 $s_{h,l,q}$ 表示，对于一个 $h \times l$ 的矩形，有多少种方案使得钦定的 $q$ 列都至少放了一个車，且每一行都至少一个車。（直接容斥得出，发现可以 $O(n^3)$ 将其递推）

分有没有空行讨论，依然容易用多项式手段做二维差卷积得到 $O(n^3 \log n)$。

直接实现也许能过。

-------

本题最重要的观察是，我们最终对 $dp_{rt,s,0}$ 求和，所以我们要求 $t$ 最终是 $0$ 即可。而 $[t=0]$ 型容斥是大家都熟悉的：$\sum_{i=0}^t (-1)^i \dbinom{t}{i} = [t=0]$。所以，只需要钦定一些列，让他们最终是 $T$ 状态，并且乘上 $(-1)^{cnt}$（每选一个数就取相反数），**其他列的状态就不用考虑了，他们最终是 $S$ 还是 $T$ 还是 $R$ 一点关系都没有**（容斥最精妙的部分）。

而怎么让一列是 $T$ 状态呢？

1. 始终不能放車。这个并不难，在 DP 的过程中我们把这一列剔除了就行。
2. 每一列最开始加入都是 $S$，必须出现**下方某个矩形一整列都没有放車才会转化为 $T$**，且在此后只要满足条件 $1$，他就一直是 $T$ 状态。

因此我们在 DP 状态中记录：

1. 有多少列不是 $T$（这样方便实现），记为 $t$。
2. 是否要在之后的矩形中，将一列留空来将一些 $S$ 转化为 $T$，记为 $0/1$。

仍然考虑树形 DP。

第一步，先钦定**新加的列有哪些被钦定是 $T$ 状态**。假设新加了 $ad$ 列。方案数（带上了容斥）为：

1. 如果钦定了 $k \ge 1$ 列，则为 $(-1)^k \dbinom{ad}{k}$，并且第二维是 $1$。
2. 如果钦定 $k=0$ 列，则为 $1$ 且第二维是 $0$。

然后树形背包合并，形如：

$$
f_{u,i+j,o_1 \text{or } o_2} \leftarrow f_{u,i+j,o_1 \text{or } o_2} + f_{u,i,o_1}f_{v,j,o_2}
$$

接着考虑矩形的情况。从 $f_{u,i,0}$ 出发，这 $h \times i$ 的矩形每个格子都可以自由决策是否放車，所以乘上 $2^{hi}$ 并且转移到自身（赋值）。$f_{u,i,1}$ 的矩形，如果所有行非空，方案为 $(2^i-1)^h$，转移到自身（赋值）；如果有行为空，方案为 $2^{hi} - (2^i-1)^h$，转移到 $f_{u,i,0}$。

那么本题就做完了，复杂度 $O(n^2)$（预处理 $(2^a-1)^b$ 的值）。

![](https://ts1.cn.mm.bing.net/th/id/R-C.d5af3734a4dfb36b22de1fd26965bf3f?rik=3HgjIWteWv8Y6g&riu=http%3a%2f%2fimg.wxcha.com%2fm00%2fd6%2fb0%2fc5b85aaea54129a375d13fc1f2b23555.gif&ehk=%2f0gH9p9So%2boxRv%2fMCmknukHtlHYSaHhdAvvhHGwGAz8%3d&risl=&pid=ImgRaw&r=0)

这是我的代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=400+10,MOD=998244353;
int n,rt,tot,h[MAXN],C[MAXN][MAXN],sze[MAXN],dp[MAXN][MAXN][2],p2[MAXN*MAXN],pw[MAXN][MAXN],tmp[MAXN][2];
#define gv(x) (((x)%2==0)?1:-1)
int solve(int l,int r,int lsth) {
	int u=++tot,mn=n+1,ot=0;
	ffor(i,l,r) mn=min(mn,h[i]);
	int lst=l-1;
	ffor(i,l,r) if(h[i]==mn) ot++;
	ffor(i,1,ot) dp[u][ot-i][1]=gv(i)*C[ot][i];
	dp[u][ot][0]=1,sze[u]=ot;
	ffor(i,l,r+1) if(h[i]==mn||i==r+1) {
		if(lst+1<=i-1) {
			int id=solve(lst+1,i-1,mn);
			ffor(x,0,sze[u]+sze[id]) tmp[x][0]=tmp[x][1]=0;
			ffor(x,0,sze[u]) ffor(y,0,sze[id]) ffor(o1,0,1) ffor(o2,0,1) tmp[x+y][o1|o2]=(tmp[x+y][o1|o2]+dp[u][x][o1]*dp[id][y][o2])%MOD;
			sze[u]+=sze[id];
			ffor(x,0,sze[u]) dp[u][x][0]=tmp[x][0],dp[u][x][1]=tmp[x][1];
		}
		lst=i;
	}
	ffor(i,0,sze[u]) {
		dp[u][i][0]=dp[u][i][0]*p2[i*(mn-lsth)]%MOD;
		dp[u][i][0]=(dp[u][i][0]+(p2[i*(mn-lsth)]-pw[i][mn-lsth])%MOD*dp[u][i][1])%MOD;
		dp[u][i][1]=dp[u][i][1]*pw[i][mn-lsth]%MOD;
	}
	return u;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n,p2[0]=1;
	ffor(i,0,n) {C[i][0]=1;ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;}
	ffor(i,1,n*n) p2[i]=p2[i-1]*2%MOD;
	ffor(i,1,n) {
		pw[i][0]=1,pw[i][1]=p2[i]-1;
		ffor(j,2,n) pw[i][j]=pw[i][j-1]*pw[i][1]%MOD;	
	}
	ffor(i,1,n) cin>>h[i];
	rt=solve(1,n,0);
	int ans=0;
	ffor(i,0,n) ans=(ans+dp[rt][i][0])%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：dAniel_lele (赞：0)

首先从高往低扫。对于每个高度找到所有使得不存在前一个格子且存在该格子的地方记录接下来一个连续段的情况。

考虑 $dp_{i,j,k}$ 表示高度 $i$，$j$ 位置，所记录的列中有 $k$ 列有车。设总共记录的列为 $j$。

首先从上一行类似树上依赖背包合并所有上面的段。

如果 $k=siz$，那么这一行不需要车了；否则需要。可以枚举有多少个新列有车。

这样就可以 $O(n^3)$ 了。

当然本题还可以优化，考虑容斥，将状态含义改为钦定 $k$ 列可以有车。剩下的列一定没有车。

对于没有车的列，有两种情况，一个是这列没有空格子，一个是在之前的 dp 中有空格子，需要带上 $(-1)^k$ 的容斥系数。

添加一维 $0/1$ 表示目前这一行是否还需要新的车（即，有空格子的列我们不管）。

总复杂度 $O(n^2)$，具体转移见代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int dp[405][405][2],pw[405];
int siz[405],h[405];
signed main(){
	pw[0]=1;
	for(int i=1;i<=400;i++) pw[i]=pw[i-1]*2%mod;
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>h[i];
	for(int i=n;i>=1;i--){
		for(int j=1;j<=n;j++){
			if(h[j]>=i){
				int k=j;
				while(h[k+1]>=i){
					k++;
				}
				if(siz[j]==k-j+1){
					for(int l=0;l<=siz[j];l++){
						(dp[j][l][1]*=(pw[l]-1))%=mod;
						(dp[j][l][0]*=pw[l])%=mod;
					} 
				}
				else{
					int nsiz=0;
					int ndp[505][2]; memset(ndp,0,sizeof(ndp));
					ndp[0][0]=1;
					for(int l=j;l<=k;l++){
						if(siz[l]){
							int tmp[505][2]; memset(tmp,0,sizeof(tmp));
							for(int p=0;p<=nsiz;p++){
								for(int q=0;q<=siz[l];q++){
									(tmp[p+q][0]+=ndp[p][0]*dp[l][q][0])%=mod;
									(tmp[p+q][1]+=ndp[p][0]*dp[l][q][1]+ndp[p][1]*dp[l][q][0]+ndp[p][1]*dp[l][q][1])%=mod;
								}
							}
							nsiz+=siz[l];
							for(int p=0;p<=nsiz;p++) ndp[p][0]=tmp[p][0],ndp[p][1]=tmp[p][1];
							l+=siz[l]-1;
							siz[l]=0;
						}
						else{
							int tmp[505][2]; memset(tmp,0,sizeof(tmp));
							for(int p=0;p<=nsiz;p++){
								for(int j=0;j<=1;j++){
									(tmp[p+1][j]+=ndp[p][j])%=mod;
									(tmp[p][j|1]+=ndp[p][j])%=mod;
									(tmp[p][j]+=ndp[p][j]*(mod-1))%=mod;
								}
							}
							nsiz++;
							for(int p=0;p<=nsiz;p++) ndp[p][0]=tmp[p][0],ndp[p][1]=tmp[p][1];
						}
					}
					siz[j]=nsiz;
					for(int l=0;l<=siz[j];l++){
						dp[j][l][1]=ndp[l][1]*(pw[l]-1)%mod;
						dp[j][l][0]=ndp[l][0]*pw[l]%mod;
					}
				}
				j=k;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		(ans+=dp[1][i][0]+dp[1][i][1])%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

