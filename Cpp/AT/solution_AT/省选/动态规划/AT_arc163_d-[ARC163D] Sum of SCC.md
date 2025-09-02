# [ARC163D] Sum of SCC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc163/tasks/arc163_d

以下の条件を全て満たす頂点に $ 1 $ から $ N $ までの番号がついた $ N $ 頂点の有向グラフ $ G $ を考えます。

- $ G $ はトーナメントである。すなわち、$ G $ に多重辺や自己ループはなく、$ G $ のどの $ 2 $ 頂点 $ u,v $ に対しても、$ u\ \rightarrow\ v $ 辺または $ v\ \rightarrow\ u $ 辺のうちちょうど片方が存在する。
- $ G $ の辺のうち、頂点番号が小さい方から大きい方へ向けられた辺はちょうど $ M $ 本存在する。
 
そのような有向グラフ $ G $ 全てに対する強連結成分の個数の総和を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 30 $
- $ 0\ \le\ M\ \le\ \frac{N(N-1)}{2} $
 
### Sample Explanation 1

条件を満たす有向グラフ $ G $ は以下の $ 3 $ 個です。それぞれ強連結成分の個数は $ 3,1,3 $ であるため答えは $ 7 $ です。 ![](https://img.atcoder.jp/arc163/ee8acabc2a7d48164b3cc568e88f0840.png)

## 样例 #1

### 输入

```
3 1```

### 输出

```
7```

## 样例 #2

### 输入

```
6 2```

### 输出

```
300```

## 样例 #3

### 输入

```
25 156```

### 输出

```
902739687```

# 题解

## 作者：vegetable_king (赞：20)

[可能更佳的阅读体验](https://yjh965.github.io/post/arc163d-sum-of-scc-ti-jie)

nb 题，我想不到的。

首先，SCC 个数显然是一个很强的东西，看起来就显得很不可维护，至少不能高效的表示进状态里。

然后我们考虑把 SCC 个数转化下：

> 有结论：一个竞赛图的 SCC 个数等于将其点集划分为两个集合 $A, B$（可为空集）并满足以下限制的方案数 $-1$：
>
> - 对于每条满足 $u \in A, v \in b$ 的边 $(u, v)$，都满足其方向为 $u \to v$。

证明这个结论也很简单，考虑将这个图缩点，然后它仍然是一个竞赛图，并且是一个 DAG。考虑它的拓扑序 $p_1, p_2, p_3, \dots, p_k$（因为它是竞赛图，所以拓扑序唯一），并找到一个分界点 $i(0 \le i \le k)$，将 $p_1, p_2, \dots, p_i$ 所对应的 SCC 划入 $A$，将 $p_{i + 1}, p_{i + 2}, \dots, p_k$ 所对应的 SCC 划入 $B$。

可以发现一定只有这样划分才是合法的方案，因为把一个 SCC 分到两个集合，一个集合内拓扑序不连续的情况都是不合法的。而每个 $i$ 就对应了一种合法的方案，且 $i$ 的取值共有 $k + 1$ 种，$-1$ 则变为 $k$，即 SCC 个数。

现在我们的目标就变为对上述划分方案计数，而这个计数是简单的，直接 dp 即可：设 $f_{i, j, k}$ 为加入了 $1 \sim i + j$ 号点，且满足 $|A| = i, |B| = j$，有 $k$ 条满足要求的边的方案数。

考虑将 $i + j + 1$ 号点加入到 $A$ 或 $B$，转移如下：
$$
f_{i + 1, j, k + x} \gets \binom ixf_{i, j, k} (0 \le x \le i)\\
f_{i, j + 1, k + i + x} \gets \binom jxf_{i, j, k} (0 \le x \le j)\\
$$
对第一个转移的解释：在 $A$ 内加入最大点 $u$，$u$ 向 $B$ 内的连边都是逆向的，向 $A$ 内的连边任意。钦定 $x$ 条为正向的，则系数为 $\binom ix$。

对第二个转移的解释：在 $B$ 内加入最大点 $u$，$u$ 向 $A$ 内的连边都是正向的，向 $B$ 内的连边任意。钦定 $x$ 条为正向的，则系数为 $\binom jx$。

时间复杂度为 $O(n^3m)$，其中状态数为 $O(n^2m)$，转移为 $O(n)$。

[code](https://atcoder.jp/contests/arc163/submissions/43219948)

---

## 作者：zac2010 (赞：6)

## 思路

有向图 $G(V,E)$ 中的强连通分量数量等于以下值：

* 将 $G$ 的顶点集 $V$ 分成两个顶点集 $A$ 和 $B$ 的方案数，满足以下条件：$A$ 中的顶点与 $B$ 中的顶点之间的每条边都是从 $A$ 指向 $B$，且 $B$ 非空。

证明：设 $s_1,s_2 ,…,s_k$ 是 $G$ 的强连通分量（编号小的强连通分量连出边指向编号大的），那么满足条件的恰好 $k$ 对 $A={s_1,s_2,…,s_i},B={s_{i+1},s_{i+2},…,s_k}$ 有 $0\leq i < k$。

转化后的问题利用动态规划求解。
$dp_{i,j,k}(i \leq N,j \leq i, k \leq \min(M,\frac{i\times(i-1)}{2}))$：对于一个 $i$ 个顶点的锦标赛图 $G$ 和顶点集 $A,B$，满足 $|A|=i$，且有 $j$ 条边从较小编号的顶点指向较大编号的顶点的对数。

这里采用刷表法转移，方法如下：

* $i+1$ 加入 $A$ 集合。

	* $i+1$ 与 $A$ 之间的边方向任意。
  	* $i+1$ 指向所有 $B$ 中的点。
   * 枚举变量 $t(t \leq j)$ 表示 $A$ 中指向 $i+1$ 的边数。转移方程：$dp_{i+1,j+1,k+t}$ 加上 $dp_{i,j,k}\times\tbinom{j}{t}$。
* $i+1$ 加入 $B$ 集合。

  	* $A$ 中所有节点指向 $i+1$。
  	* $i+1$ 与 $B$ 之间的边方向任意。
	* 枚举 $B$ 中指向 $i+1$ 的边数 $t(t \leq i - j)$。转移方程：$dp_{i+1,j,k+t+j}$ 加上 $dp_{i,j,k}\times\tbinom{i-j}{t}$。

时间复杂度：$O(N^3M)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i++)
using namespace std;
const int N = 32, M = 440, mod = 998244353;
int n, m, ans, C[N][N], dp[N][N][M];
int main(){
    scanf("%d%d", &n, &m), C[0][0] = 1;
    L(i, 1, n){
        C[i][0] = 1;
        L(j, 1, i) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    dp[0][0][0] = 1;
    L(i, 0, n - 1) L(j, 0, i) L(k, 0, min(m, i * (i - 1) / 2)){
		L(t, 0, min(j, m - k)) (dp[i + 1][j + 1][k + t] += 1ll * dp[i][j][k] * C[j][t] % mod) %= mod;
	    L(t, 0, min(i - j, m - k - j)) (dp[i + 1][j][k + t + j] += 1ll * dp[i][j][k] * C[i - j][t] % mod) %= mod; 
	}
    L(i, 0, n - 1) (ans += dp[n][i][m]) %= mod;
    printf("%d", ans);
    return 0;
}
```


---

## 作者：Pengzt (赞：6)

[ARC163D](https://www.luogu.com.cn/problem/AT_arc163_d)

发现这个竞赛图一定能被分为两个集合 $A$，$B$。满足 $\forall u\in A,v\in B$，均有 $u\to v\in E$。答案就是划分这两个集合的方案数。

证明：

首先，竞赛图缩完点后一定是一条链，对强连通分量进行标号，满足编号小的强连通分量指向编号大的强连通分量。不妨令竞赛图 $G$ 缩完点后的强连通分量编号分别为 $a_1,a_2\dots a_k$。则这个图 $G$ 存在 $k$ 个 $i$ 能分出两个满足条件的集合，即 $\{a_1\dots a_i\}$ 和 $\{a_{i+1}\dots a_k\},i\in[1,k]$。而分出的 $k$ 种集合 $A$，$B$ 是与其形成双射关系的，故可转化。

这时就很好用动态规划求解了，定义 $f_{i,j,k}$ 表示 $i$ 个点的竞赛图中，$A$ 集合有 $j$ 个点，有 $k$ 条边满足 $u<v$ 的方案数。

采用刷表法，考虑转移。

若第 $i+1$ 个点在 $A$ 中，内部有 $c$ 条边连向 $i+1(c\le j)$，则对 $f_{i+1,j+1,k+c}$ 产生贡献。

若第 $i+1$ 个点在 $B$ 中，内部有 $c$ 条边连向 $i+1(c\le i-j)$，则对 $f_{i+1,j,k+j+c}$ 产生贡献。

可得到方程：

$f_{i+1,j+1,k+c}\leftarrow f_{i+1,j+1,k+c}+f_{i,j,k}\times\dbinom{j}{c}$

$f_{i+1,j,k+j+c}\leftarrow f_{i+1,j+1,k+j+c}+f_{i,j,k}\times\dbinom{i-j}{c}$

答案容易得到：$\sum\limits_{i=0}^{n-1} f_{n,i,m}$。

时间复杂度：$\mathcal{O}(n^5)$。

空间复杂度：$\mathcal{O}(n^4)$。

[评测记录](https://atcoder.jp/contests/arc163/submissions/45693802)

---

## 作者：绝顶我为峰 (赞：5)

关于竞赛图强联通分量的一个很典的结论是你把竞赛图缩点会得到一条链，链上前面的点到后面的每个点都有边。

然后你考虑没有边数量的限制怎么做，这个就是非常经典的推半在线卷积或者求逆的那一套，$f_i$ 表示强联通的数量，$g_i$ 表示没有限制的数量，然后枚举 $i$ 所在的连通快大小得到一个 $O(n^2)$ 的递推式，大概是 $f_i=g_i-\sum\limits_{j=1}^{i-1}\dbinom{i-1}{j-1}f_jg_{i-j}$ 这样。然后你再对 $f$ 做一遍背包就能得到答案。

现在加入了边的限制，如法炮制设 $f_{i,j}$ 表示强联通且有 $j$ 条边从小到大的方案数，$g_{i,j}$ 表示没有限制且有 $j$ 条边从小到大的方案数，显然有 $g_{i,j}=\dbinom{\frac{i(i-1)}2}j$。

考虑得到一个类似的递推式，但是问题在于无法快速处理出来 $i$ 所在联通块和其他部分之间的连边的贡献，但是注意到这个贡献系数只和总点数和选出的点数有关，我们设 $h_{i,j,k}$ 表示有 $i$ 个点，连通块有 $i-j$ 个点，连通块内外有 $k$ 条边从小到大的方案数，那么有递推式 $f_{i,j}=g_{i,j}-\sum\limits_{k=1}^{i-1}\sum\limits_{x=0}^j\sum\limits_{y=0}^{j-x}f_{k,x}g_{i-k,y}h_{i,i-k,j-x-y}$。

$h_{i,j,k}$ 是可以在 $O(n^4)$ 的时间内求出的，具体来说从小到大加入点，转移的时候枚举这个点放在哪个集合即可，增加的边数是容易计算的。

但是直接递推 $f$ 的复杂度依然高达 $O(n^8)$，考虑优化。

注意到递推式中 $g,h$ 的部分是一个标准的卷积，于是可以直接预处理出来 $g,h$ 卷积的结果记作 $G_{i,j,k}$，那么递推式就是 $f_{i,j}=g_{i,j}-\sum\limits_{k=1}^{i-1}\sum\limits_{p=0}^jf_{k,p}G_{i,i-k,j-p}$。

预处理 $G$ 和递推 $f$ 的时间复杂度都是 $O(n^6)$，于是可以在 $O(n^6)$ 的时间内求出 $f$。

有了 $f$ 之后还是考虑做背包求出答案，发现合并背包的时候还是需要处理连通块之间的连边，写出式子发现背包的过程中 $f,h$ 之间是直接卷起来，预处理这个卷积就可以做到 $O(n^6)$ 完成这个背包，和上面递推 $f$ 的部分是类似的，这里不做赘述。

综上我们在 $O(n^6)$ 的时间内解决了这个问题。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int mod=998244353;
int n,m,lim,c[1001][1001],f[31][1001],g[31][31][1001],h[31][31][1001],cnt[31][1001],sum[31][1001];
inline void init()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}
inline int read()
{
    int x;
    cin>>x;
    return x;
}
inline int Mod(int x)
{
    return x>=mod? x-mod:x;
}
int main()
{
    init();
    n=read(),m=read();
    lim=n*(n-1)/2;
    for(int i=0;i<=lim;++i)
    {
        c[i][0]=1;
        for(int j=1;j<=i;++j)
            c[i][j]=Mod(c[i-1][j]+c[i-1][j-1]);
    }
    h[0][0][0]=1;
    for(int i=1;i<=n;++i)
        for(int j=0;j<i;++j)
            for(int k=0;k<=(i-1)*(i-2)/2;++k)
                if(h[i-1][j][k])
                {
                    h[i][j][k]=Mod(h[i][j][k]+h[i-1][j][k]);
                    h[i][j+1][k+(i-j-1)]=Mod(h[i][j+1][k+(i-j-1)]+h[i-1][j][k]);
                }
    for(int i=1;i<=n;++i)
        for(int x=1;x<i;++x)
            for(int y=0;y<=x*(x-1)/2;++y)
                for(int z=0;z<=x*(i-x);++z)
                    g[i][x][y+z]=Mod(g[i][x][y+z]+1ll*c[x*(x-1)/2][y]*h[i][x][z]%mod);
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=i*(i-1)/2;++j)
        {
            f[i][j]=c[i*(i-1)/2][j];
            for(int k=1;k<=i;++k)
                for(int p=0;p<=j;++p)
                    f[i][j]=Mod(f[i][j]-1ll*f[k][p]*g[i][i-k][j-p]%mod+mod);
        }
    }
    memset(g,0,sizeof g);
    for(int i=1;i<=n;++i)
        for(int x=1;x<=i;++x)
            for(int y=0;y<=x*(x-1)/2;++y)
                for(int z=0;z<=x*(i-x);++z)
                    g[i][x][y+z]=Mod(g[i][x][y+z]+1ll*f[x][y]*h[i][x][z]%mod);
    cnt[0][0]=1;
    for(int i=1;i<=n;++i)
        for(int j=0;j<=i*(i-1)/2;++j)
            for(int x=1;x<=i;++x)
                for(int y=0;y<=j;++y)
                {
                    cnt[i][j]=Mod(cnt[i][j]+1ll*cnt[i-x][j-y]*g[i][x][y]%mod);
                    sum[i][j]=Mod(sum[i][j]+Mod(1ll*cnt[i-x][j-y]*g[i][x][y]%mod+1ll*sum[i-x][j-y]*g[i][x][y]%mod));
                }
    cout<<sum[n][m]<<'\n';
    cout.flush();
    return 0;
}
```

---

## 作者：Arghariza (赞：3)

### Description

给定 $N,M$，求对于所有 $N$ 个点的，满足恰有 $M$ 条从小连向大的边，即 $\sum\limits_{(u,v)\in E}[u<v]=M$ 的**竞赛图**，求其**强连通分量的个数**之和。

$N\le 30,0\le M\le \frac{N(N-1)}{2}$

### Solution

首先有一个经典结论：

> 给竞赛图每个 SCC （强连通分量）缩点后，剩下的是由一条**极长**的链与某些前向边组成的图。

于是 SCC 的数量能够转换为链上边数 $+1$，也就是在链上切一刀分成左右 $2$ 个集合的方案数 $+1$。

如果我们在链的开头前/结尾后也能切的话，那就变成了切一刀分成左右 $2$ 个集合 $A,B$ 的方案数 $-1$，因为边的方向始终从左到右，那么 $A,B$ 满足 $\forall u\in A,v\in B$，存在 $u\to v$ 的边。

于是我们现在考虑统计把 $\{1,2,\cdots, n\}$ 分成两个集合 $A,B$（允许出现空集），使得 $A$ 中的点始终连向 $B$ 中的点的方案数。再减去 $N$ 个点 $M$ 条从小连向大的边的竞赛图个数就是答案。

设 $f_{i,j,k}$ 表示 $i$ 个点的竞赛图，上述 $A$ 集合满足 $|A|=j$，一共有 $k$ 条从小连向大的边的方案数。考虑添加 $i+1$ 号点，讨论加入 $A/B$ 中，对 $k$ 产生的贡献：

- $i+1$ 加入 $A$ 集合，由于 $A$ 始终向 $B$ 连边，所以 $B$ 中没有贡献；于是只要在 $A$ 中任选 $l$ 个点 $u$ 满足 $u\to i+1$ 即可贡献 $l$，那么 $f_{i,j,k}\cdot \dbinom{j}{l}\to f_{i+1,j+1,k+l}$。
- $i+1$ 加入 $B$ 集合，$A$ 中所有点向 $i+1$ 连边有 $j$ 的贡献，在 $B$ 中任选 $l$ 个点满足 $u\to i+1$ 贡献 $l$，那么 $f_{i,j,k}\cdot\dbinom{i-j}{l}\to f_{i+1,j,k+l+j}$。

现在还剩最后一步：如何统计再减去 $N$ 个点有 $M$ 条从小连向大的边的竞赛图个数。其实不难发现这就是 $f_{n,0,m}$ 或者 $f_{n,n,m}$，因为去掉 $A$ 向 $B$ 连边的限制即可。

所以答案为：

$$\sum\limits_{i=1}^nf_{n,i,m}$$

复杂度 $O(n^5)$。

```cpp
const int N = 35;
const int P = 998244353;
int n, m, f[N][N][N * N], C[N][N];

signed main() {
	n = rd(), m = rd();
	C[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
	}
	f[0][0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			for (int k = 0; k <= i * (i - 1) / 2; k++) {
				for (int l = 0; l <= j; l++) (f[i + 1][j + 1][l + k] += 1ll * f[i][j][k] * C[j][l] % P) %= P;
				for (int l = 0; l <= i - j; l++) (f[i + 1][j][l + k + j] += 1ll * f[i][j][k] * C[i - j][l] % P) %= P;
			}
		}
	} 
	int res = 0;
	for (int i = 1; i <= n; i++) 
		(res += f[n][i][m]) %= P;
	wr(res);
	return 0;
}

```

---

## 作者：5ab_juruo (赞：3)

SCC 个数等于如下方案数之和：将 $n$ 个点分成两个集合 $S,T$，使得 $S$ 和 $T$ 之间只有 $S\to T$ 的边的方案数。其中 $1\le |S|\le n$。

设 $dp_{i,j,k}$ 为：前 $i$ 个点中，有 $j$ 个属于 $S$，已经加入了 $k$ 条正向的边。转移考虑每个点属于 $S$ 还是 $T$，更新 $j$ 和 $k$ 即可。

最后的答案即为：

$$
\sum _{i=1}^n\sum_{j=0}^m\binom{\binom{i}{2}+\binom{n-i}{2}}{m-j}dp_{n,i,j}
$$

复杂度 $\mathcal{O}(n^2m)$。

```cpp
const int max_n = 30, max_m = max_n * (max_n - 1) / 2, mod = 998244353;
using mint = mod_int<mod>;

mint fac[max_m + 1], ifac[max_m + 1], dp[max_n + 1][max_n + 1][max_m + 1];

void initfac(int lim)
{
	fac[0] = 1;
	for (int i = 0; i < lim; i++)
		fac[i + 1] = fac[i] * (i + 1);
	ifac[lim] = fac[lim].inv();
	for (int i = lim; i > 0; i--)
		ifac[i - 1] = ifac[i] * i;
}
inline mint C(int n, int m) { return fac[n] * ifac[m] * ifac[n - m]; }

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;
	
	cin >> n >> m;
	initfac(n * (n - 1) / 2);
	
	dp[0][0][0] = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= i + 1; j++)
			for (int k = 0; k <= m; k++)
			{
				if (j) dp[i + 1][j][k] += dp[i][j - 1][k];
				if (k >= j) dp[i + 1][j][k] += dp[i][j][k - j];
			}
	
	mint ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= m; j++)
			ans += dp[n][i][j] * C(i * (i - 1) / 2 + (n - i) * (n - i - 1) / 2, m - j);
	cout << ans << endl;
	
	return 0;
}
// started coding at: 07-03 08:12:27
```

---

## 作者：Leasier (赞：1)

~~关于我昨晚把 tournament 当成了无重边自环的任意有向图这回事。~~

**重点：tournament 是竞赛图。**

考虑竞赛图缩点后所得结果：

- 一堆 BCC，设编号为 $1 \sim m$。
- $\forall 1 \leq i < j \leq m$，编号为 $i$ 的 BCC 中所有点的出边指向编号为 $j$ 的 BCC 中的所有点。

考虑在这样一个链上的某个 $1 \leq i \leq m$ 的位置讨论贡献，即：

- 选择一个大小为 $j$ 的点集 $S_1$ 表示编号在 $[1, i]$ 中的 BCC 中的点，剩下的大小为 $n - j$ 的点集 $S_2$ 表示编号在 $(i, n]$ 中的 BCC 中的点。
- 这两个点集内部可以随便连边，从 $S_1$ 中的点出发的边指向 $S_2$ 中的点。

考虑对点集间的情况 dp。设 $dp_{i, j, k}$ 表示前 $i$ 个点中有 $j$ 个在 $S_1$ 中、剩的点在 $S_2$ 中、从 $S_1$ 到 $S_2$ 且从小指向大的边数为 $k$ 的方案数。转移略去。

统计答案时枚举上面的 $j$、$p$ 表示 $S_1$ 内部从小指向大的边数、$q$ 表示 $S_2$ 内部小指向大的边数，则方案数为 $C_{C_j^2}^p C_{C_{n - j}^2}^q dp_{n, j, m - p - q}$。

暴力实现即可。时间复杂度为 $O(n^5)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 998244353;
int c[437][437], dp[37][37][437];

inline void init(int n){
	c[0][0] = 1;
	for (int i = 1; i <= n; i++){
		c[i][0] = 1;
		for (int j = 1; j <= i; j++){
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
}

inline int comb_2(int n){
	return n * (n - 1) / 2;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int min(int a, int b){
	return a < b ? a : b;
}

int main(){
	int n, m;
	ll ans = 0;
	scanf("%d %d", &n, &m);
	init(max(n, comb_2(n)));
	dp[0][0][0] = 1;
	for (int i = 0; i < n; i++){
		for (int j = 0; j <= i; j++){
			int up = min(j * (i - j), m);
			for (int k = 0; k <= up; k++){
				dp[i + 1][j][k + j] = (dp[i + 1][j][k + j] + dp[i][j][k]) % mod;
				dp[i + 1][j + 1][k] = (dp[i + 1][j + 1][k] + dp[i][j][k]) % mod;
			}
		}
	}
	for (int i = 1; i <= n; i++){
		int up1 = min(c[i][2], m), t = n - i;
		for (int j = 0; j <= up1; j++){
			int up2 = min(c[t][2], m - j);
			for (int k = 0; k <= up2; k++){
				ans = (ans + (ll)c[c[i][2]][j] * c[c[t][2]][k] % mod * dp[n][i][m - j - k] % mod) % mod;
			}
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：云浅知处 (赞：1)

考虑这样计数一张竞赛图的 SCC：计数点集的划分 $(S,T)$，使得对任意 $u\in S,v\in T$，这两个点之间的边的方向都是 $u\to v$。如果 $S,T$ 中有空集也合法。那么 SCC 个数就是这样的划分的个数 $-1$。

按照编号从小到大 DP，设 $f(i,j,k)$ 表示前 $i$ 个点，$S$ 里面有 $j$ 个，目前有 $k$ 条从小指向大的边的方案数。转移考虑 $i+1$ 放在哪边，如果放在 $S$ 里面就是
$$
f(i,j,k)\times \binom{j}{l}\to f(i+1,j+1,k+l)
$$
放在 $T$ 里面就是
$$
f(i,j,k)\times \binom{i-j}{l}\to f(i+1,j,k+j+l)
$$
最后还需要减去这样的图的个数，即 $\binom{\frac{N(N-1)}{2}}{M}$。复杂度 $O(n^5)$。

<https://atcoder.jp/contests/arc163/submissions/43248049>

---

## 作者：xuanxuan001 (赞：0)

做法不太一样，所以发篇题解。

# upd

2023.7.3 改正了最后复杂度上的笔误，感谢 @yinzijia 的提醒。

会发现如果有多个 SCC，那么这些 SCC 之间一定有一个顺序，使得每条边的方向都是从两个端点所在 SCC 中靠前的连向靠后的。

那么设 $dp_{i,j}$ 表示当 $n = i$，$m = j$ 时的答案。转移就考虑枚举最后一个 SCC 的点数以及从小连到大的边数，然后再枚举这个 SCC 与其他点间的边中从小到大的边数。那么在这么转移之前需要先预处理以下两个数组：

首先要预处理 $F_{i,j,k}$ 表示 $i$ 个点连向 $j$ 个点的 $ij$ 条边且方向定为 $i$ 个点的块连向 $j$ 个点的块，其中有 $k$ 条边是从小连到大的点的排列方案数，也就是说 $\sum\limits_{k=0}^{ij}F_{i,j,k} = C_{i+j}^i$。

那么这个的转移就是考虑最后一个是 $i$ 个的块的还是 $j$ 个的块的，那么就是 $F_{i,j,k} = F_{i-1,j,k} + F_{i,j-1,k-i}$。

然后是 $G_{i,j}$ 表示一个 $i$ 个点的有 $j$ 条边是从小连到大的 SCC 的方案数，那么转移就是枚举如果不是一个 SCC 就枚举最靠后的 SCC，所以就是

$$
G_{i,j} = C_{C_i^2}^j - \sum\limits_{x=1}^{i-1}\sum\limits_{y=0}^j\sum\limits_{z=0}^y C_{C_x^2}^{j-y} G_{i-x,z} F_{x,i-x,y-z}
$$

大致意思就是枚举最后一个 SCC 有 $i - x$ 个点，内部有 $z$ 条从小到大的边，有 $y-z$ 条这个 SCC 与其他点之间的从小到大的边。

处理出这两个之后就可以得出 $dp$ 的转移：

$$
dp_{i,j} = \sum\limits_{x=1}^{i}\sum\limits_{y=0}^j\sum\limits_{z=0}^y dp_{x,j-y} G_{i-x,z} F_{x,i-x,y-z}
$$

但是要注意 $dp$ 需要记录方案数和 SCC 数量和两个值，每次转移时再给 SCC 数量和加上方案数。

然后就可以得出正确答案了。

但是会发现如果认为 $m = n^2$ 的话，那么 $G$ 和 $dp$ 的转移都是 $O(n^8)$ 的，虽然常数极小，但依然无法通过。

那么考虑优化，观察两个转移式子，发现都有下面这个东西：

$$
\sum\limits_{z=0}^y G_{i-x,z} F_{x,i-x,y-z}
$$

那么可以预处理一个 $tot_{i,x,y} = \sum\limits_{z=0}^y G_{i-x,z} F_{x,i-x,y-z}$

这样省掉了一个 $m$ 的复杂度，变成了 $O(n^6)$，常数也非常小，所以就过了。

代码：

```
#include<cstdio>
#define TY ll
#define MAXN 32
#define MAXM 1002
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
#define EDG(i,u) for(TY i=hed[u];i;i=nxt[i])
using namespace std;
typedef long long ll;
const TY M=998244353;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
inline void updmx(TY &x,TY y){if(x<y)x=y;}
inline void updmn(TY &x,TY y){if(x>y)x=y;}
inline void add(TY &x,TY y){if((x+=y)>=M)x-=M;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(1&b)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a){if(a>9)qw(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY n,m,F[MAXN][MAXN][MAXM],C[MAXM][MAXM],G[MAXN][MAXM],tot[MAXN][MAXN][MAXM],vl;
struct node{TY nm,sm;}dp[MAXN][MAXM],tmp;
node operator*(node a,TY b){a.nm=a.nm*b%M;a.sm=a.sm*b%M;return a;}
void operator+=(node &a,node &b){add(a.nm,b.nm);add(a.sm,b.sm);}
int main(){
	n=qr();m=qr();
	fOR(i,0,MAXM)C[i][0]=1;
	fOR(i,1,MAXM)FOR(j,1,i){
		C[i][j]=C[i-1][j-1];
		add(C[i][j],C[i-1][j]);
	}FOR(i,1,n)F[i][0][0]=F[0][i][0]=1;
	FOR(i,1,n)FOR(j,1,n)ROF(k,i*j,0){
		if(k>=i)F[i][j][k]=F[i][j-1][k-i];
		add(F[i][j][k],F[i-1][j][k]);
	}FOR(i,1,n){
		FOR(x,1,i)FOR(y,0,m)FOR(z,0,y)
			add(tot[i][x][y],G[i-x][z]*F[i-x][x][y-z]%M);
		FOR(j,0,m){
			fOR(x,1,i)FOR(y,0,j)add(G[i][j],tot[i][x][y]*C[x*(x-1)>>1][j-y]%M);
			G[i][j]=M-G[i][j];add(G[i][j],C[i*(i-1)>>1][j]);
		}FOR(y,0,m)FOR(z,0,y)add(tot[i][0][y],G[i][z]*F[i][0][y-z]%M);
	}FOR(i,dp[0][0].nm=1,n)FOR(j,0,m)fOR(x,0,i)FOR(y,0,j){
		tmp=dp[x][j-y]*tot[i][x][y];
		add(tmp.sm,tmp.nm);dp[i][j]+=tmp;
	}qw(dp[n][m].sm);return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

首先有一个关于竞赛图的 SCC 的重要结论：

- 竞赛图强连通缩点后的 DAG 呈链状，前面的所有点向后面的所有点连边。

证明其实也很简单，利用归纳法逐一加入每个 SCC 即可。

然后利用这点我们就可以把统计 SCC 数目转化为另一个问题了。

设将图的点集 $V$ 划分为 $A,B$ 两个集合，且满足 $A$ 中的所有点与 $B$ 中的所有点的边的方向均为 $A \to B$，则这种点集划分的方案数即为图的 SCC 个数加 $1$。

证明的话就考虑上面的结论，我们将缩点后的 DAG 链记为 $s_1,s_2,\cdots,s_k$，当 $i<j$ 时，边的方向均为 $s_i \to s_j$。

则对于 $t\in[0,k]$，$A=\{s_1,s_2,\cdots,s_t\}$ 和 $B=\{s_{t+1},s_{t+2},\cdots,s_k\}$ 均为满足上述要求的划分方案，且不存在在这之外的方案了。

因此我们只要统计上面的问题的答案即可，这个很容易通过 DP 算出。

设 $f_{i,j,k}$ 表示以及处理了前 $i$ 个点，其中有 $j$ 条边的方向是从小到大的，且集合 $A$ 的大小为 $k$ 的方案数。

转移的话就考虑 $i+1$ 号点放在集合 $A$ 还是集合 $B$ 即可：

- 若放在集合 $A$，枚举原来 $A$ 集合中的边有 $t\in[0,k]$ 条方向为从小到大，则 $f_{i,j,k}\times C_{t}^{k} \rightarrow f_{i+1,j+t,k+1}$。
- 若放在集合 $B$，枚举原来 $B$ 集合中的边有 $t\in[0,i-k]$ 条方向为从小到大，则 $f_{i,j,k}\times C_{t}^{i-k} \rightarrow f_{i+1,j+k+t,k}$。

最后答案就是 $(\sum_{i=0}^{n} f_{n,m,i}) - C_{\frac{(n-1)}{2}}^{m}$。

### 完整代码：

```cpp
#include<cstdio>
#include<iostream>
#define RI register int
#define CI const int&
using namespace std;
const int N=35,mod=998244353;
int n,m,C[N][N],f[N][N*N][N],ans;
inline int sum(CI x,CI y)
{
	return x+y>=mod?x+y-mod:x+y;
}
inline void inc(int& x,CI y)
{
	if ((x+=y)>=mod) x-=mod;
}
inline int quick_pow(int x,int p=mod-2,int mul=1)
{
	for (;p;p>>=1,x=1LL*x*x%mod) if (p&1) mul=1LL*mul*x%mod; return mul;
}
int main()
{
	//freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
	RI i,j,k,t; for (scanf("%d%d",&n,&m),i=0;i<=n;++i)
	for (C[i][0]=j=1;j<=i;++j) C[i][j]=sum(C[i-1][j],C[i-1][j-1]);
	for (f[0][0][0]=1,i=0;i<n;++i) for (j=0;j<=m;++j)
	for (k=0;k<=i;++k) if (f[i][j][k])
	{
		for (t=0;t<=k;++t) inc(f[i+1][j+t][k+1],1LL*f[i][j][k]*C[k][t]%mod);
		for (t=0;t<=i-k;++t) inc(f[i+1][j+k+t][k],1LL*f[i][j][k]*C[i-k][t]%mod);
	}
	for (ans=1,i=m+1;i<=n*(n-1)/2;++i) ans=1LL*ans*i%mod*quick_pow(i-m)%mod;
	for (ans=(mod-ans)%mod,i=0;i<=n;++i) inc(ans,f[n][m][i]);
	return printf("%d",ans),0;
}

```


---

## 作者：Raisetsu41 (赞：0)

先放一个竞赛图性质**将一个竞赛图缩点之后形成的 DAG 是一条单链**，证明方式考虑依次加点进图即可。  
难点在于去计算所有强连通块个数的和。考虑换一种方式去描述强连通块个数？  
结合到性质，发现对于一张固定的图，对它缩点，劈开这条单链使其成为两个非空集合的方案数等于强连通个数减一。  
更具体地来说，如果缩点后图变成 $scc_1 \to scc_2 \to scc_3 \to \dots \to scc_n$，将其划分成 $A,B$ 两个集合，满足 $A \cup B = scc, A \cap B = \varnothing, \forall u \in A, v \in B, \exists e = u \to v$。  
于是达到了切换主体的目的，定义 $dp_{i, j, k}$ 表示考虑了前 $i$ 个点，$\mid A \mid = j$，有 $k$ 条小连大的边，$\Theta(n^4)$ 转移即可。  

```cpp
dp[0][0][0] = 1;
for (int i = 0; i < n; i++) {
  for (int j = 0; j <= i; j++) {
    for (int k = 0; k <= m; k++) {
      if (!dp[i][j][k]) continue;
      for (int l = 0; l <= j; l++) dp[i + 1][j + 1][k + l] = (dp[i + 1][j + 1][k + l] + (dp[i][j][k] * binom(j, l) % Mod)) % Mod;
      for (int l = 0; l <= (i - j); l++) dp[i + 1][j][k + j + l] = (dp[i + 1][j][k + j + l] + (dp[i][j][k] * binom(i - j, l) % Mod)) % Mod;
    }
  }
}
```

---

