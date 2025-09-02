# 2-Coloring

## 题目描述

There is a grid with $ n $ rows and $ m $ columns. Every cell of the grid should be colored either blue or yellow.

A coloring of the grid is called stupid if every row has exactly one segment of blue cells and every column has exactly one segment of yellow cells.

In other words, every row must have at least one blue cell, and all blue cells in a row must be consecutive. Similarly, every column must have at least one yellow cell, and all yellow cells in a column must be consecutive.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1503E/f3562aaf6fab4721f0bb458f1d8dd50d6d917a2d.png) An example of a stupid coloring.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1503E/de3679de796822ab7c00a24a2e2a1dd2e13093bc.png) Examples of clever colorings. The first coloring is missing a blue cell in the second row, and the second coloring has two yellow segments in the second column. How many stupid colorings of the grid are there? Two colorings are considered different if there is some cell that is colored differently.

## 说明/提示

In the first test case, these are the only two stupid $ 2\times 2 $ colorings.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1503E/f66a34ec71497a45956a4e5d1e13d8d8d13ba2bf.png)

## 样例 #1

### 输入

```
2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3```

### 输出

```
294```

## 样例 #3

### 输入

```
2020 2021```

### 输出

```
50657649```

# 题解

## 作者：tzc_wk (赞：40)

[Codeforces 题目传送门](https://codeforces.com/contest/1503/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1503E)

考虑什么样的 2-染色方式是符合题目要求的，首先蓝、黄颜色所形成的连通块个数必须 $\le 2$，否则一定不合法，而显然如果两种颜色连通块个数都为 $1$ 也不合法，以蓝色连通块个数为 $1$，黄色连通块个数为 $2$ 为例，稍微画个图即可发现合法的染色方式都如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/sxx8jksf.png)

也就是说存在一个分割点 $i$，使得第一个连通块全部在第 $i$ 列左侧，第二个连通块全部在第 $i$ 列右侧，那么显然两个连通块与第 $i$ 列的交点分别是一段不相交区间 $(l_1,r_1),(l_2,r_2)$，我们假设第一个连通块的区间在第二个连通块的区间的上方，也就是如图所示的情况，那么我们假设 $j=r_1,k=l_2$（当然如果 $j=k$ 蓝色连通块会被一分为二，也就是蓝色、黄色连通块个数都为 $2$ 的情况），那么显然第一个连通块与直线 $x=i$ 的交中最下方的点的坐标就是 $(j,i)$（即图中的点 A），第二个连通块与直线 $x=i$ 的交中最上方的点就是 $(k,i)$（即图中的点 B）。接下来考虑怎样计算方案数，隔板法是肯定没问题的，不过这里有一种更简便的理解方式，以计算 $A$ 左上角的方案数为例，它等价于从最左上角的点走到 $A$ 的方案数，但由于 $A$ 是这段区间中最下方的点，因此最后一步必须是向下走的，因此左上角的方案数就是从最左上角的点走到 $A$ 上方的点的方案数，另外四块也同理，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/d61cxhkf.png)

暴力枚举是 $n^2m$ 的，通过前缀和优化可以做到 $nm$。对于 $(l_1,r_1)$ 在 $(l_2,r_2)$ 下方的情况只需乘个 $2$ 即可，因为所有 $(l_1,r_1)$ 在 $(l_2,r_2)$ 上方的情况把它上下翻转都能够得到 $(l_1,r_1)$ 在 $(l_2,r_2)$ 下方的情况，因此它们构成了一个双射。对于蓝色连通块个数为 $2$，黄色连通块个数为 $1$ 的情况其实很 simple，只需做整个网络关于 $y=x$ 对称的图形即可，但是这样蓝色、黄色连通块个数都是 $2$ 的情况会被算重，因此第二次计算的时候需要强制令 $k-j\ge 1$。

时间复杂度 $\mathcal O(nm)$

```cpp
const int MAXN=1<<12;
const int MOD=998244353;
int n,m,fac[MAXN+5],ifac[MAXN+5],ans=0;
void init_fac(int n){
	for(int i=(fac[0]=ifac[0]=ifac[1]=1)+1;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i-1]*ifac[i]%MOD;
}
int ways(int x,int y){return 1ll*fac[x+y]*ifac[x]%MOD*ifac[y]%MOD;}
int main(){
	scanf("%d%d",&n,&m);init_fac(MAXN);
	for(int i=1;i<=m-1;i++){
		int sum=0;
		for(int j=1;j<=n-1;j++){
			sum=(sum+1ll*ways(i,j-1)*ways(i-1,n-j))%MOD;
			ans=(ans+1ll*sum*ways(m-i-1,j)%MOD*ways(m-i,n-j-1))%MOD;
		}
	} n^=m^=n^=m;
	for(int i=1;i<=m-1;i++){
		int sum=0;
		for(int j=1;j<=n-1;j++){
			ans=(ans+1ll*sum*ways(m-i-1,j)%MOD*ways(m-i,n-j-1))%MOD;
			sum=(sum+1ll*ways(i,j-1)*ways(i-1,n-j))%MOD;
		}
	} printf("%d\n",(ans<<1)%MOD);
	return 0;
}
```



---

## 作者：zhoukangyang (赞：34)

[更好的阅读体验](https://www.cnblogs.com/zkyJuruo/p/14616877.html)

感觉这题是一道细节比较多但是不难的题，配不上这个 ``*3100`` 的标签，连萌新都能独立做出来......

## 题面

给定一个 $n \times m$ 的矩阵，要你把矩阵的每一个格子染成蓝的或黄的，要求每一行的蓝色格子段数（连通块数）恰好有一个，每一列的黄格子段数恰好有一个。求染色方案数，答案对 $998244353$ 取模。

数据范围：$1 \le n, m \le 2000$。

## 题解

这里的 $n, m$ 可能是反的，但是不影响答案（

观察蓝色的线段。

经过手膜大致可以发现可以分成两类情况讨论

### 第一类

蓝色的分成两个部分，上面一个下面一个。

这两个部分都是 "单峰" 的。

![](https://cdn.luogu.com.cn/upload/image_hosting/ltg9ofs0.png)

要求两个部分的 "高度" 之和恰好为 $m$。

考虑美剧第一个的高度和两个峰值的位置（枚举最左边的或最右边的即可）

$$2 \sum\limits_{z = 1}^{m - 1} \sum\limits_{i = 1}^{n - 1} \sum\limits_{j = i + 1}^{n} \binom{i + z - 1}{z} \binom{n - i + z - 1}{z - 1} \binom{j + m - z - 2}{m - z - 1} \binom{n - j + m - z}{m - z}$$

### 第二类

蓝色的分成两个部分，上面一个下面一个。

![](https://cdn.luogu.com.cn/upload/image_hosting/w8uz5dem.png)

要求两个部分的 "高度" 之和 $> m$。

枚举高度，然后枚举这个交的部分（黑线）的 $x$ 坐标即可。

$$2 \sum\limits_{p = 1}^{n} \sum\limits_{i = 1}^{m - 1} \sum\limits_{j = m - i + 1}^{m - 1} \binom{p + i - 1}{i} \binom{n - p + m - j - 1}{m - j - 1} \binom{p + m - i - 1}{m - i - 1} \binom{n - p + j - 1}{j}$$


现在的复杂度是 $\Theta(n^3)$ 的（$n, m$ 同阶）

但是这两个柿子是可以前缀和优化的，做到 $\Theta(n^2)$。

----------------

上面这些柿子是哪里来的？

考虑一个长为 $x$ 的不严格单调下降序列，要求第一个值 $\le y$。

这个是经典的插板法，先化成严格的，然后再插板，一个板代表这个序列的一个元素。那么答案就是 $\binom{x+y}{x}$。

那里要乘以 $2$ 是因为我们钦定了上面和下面的左右关系。

**你有没有感觉这两个柿子是一模一样的？**

嗯是的，其实这两种情况只是 $n. m$ 交换了一下，本质是差不多的（


## 代码

```cpp
#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j, i##E = k; i <= i##E; i++)
#define R(i, j, k) for(int i = j, i##E = k; i >= i##E; i--)
#define ll long long
#define pii pair<int, int>
#define db double
#define x first
#define y second
#define ull unsigned long long
#define sz(a) ((int) (a).size())
#define vi vector<int>
using namespace std;
const int N = 4e5 + 7, mod = 998244353;
int ns, n, m;
int fac[N], inv[N], ifac[N];
void init(int x) {
	fac[0] = ifac[0] = inv[1] = 1;
	L(i, 2, x) inv[i] = (ll) inv[mod % i] * (mod - mod / i) % mod;
	L(i, 1, x) fac[i] = (ll) fac[i - 1] * i % mod, ifac[i] = (ll) ifac[i - 1] * inv[i] % mod;
}
int C(int x, int y) {
	return x < y || y < 0 ? 0 : (ll) fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
int main() {
	cin >> n >> m, init(max(n, m) * 4);
	L(z, 1, m - 1) {
		int now = 0;
		R(r1, n - 1, 1) {
			(now += (ll) C(r1 + m - z - 1, m - z - 1) * C(n - r1 + m - z - 1, m - z) % mod) %= mod;
			(ns += (ll) C(r1 + z - 1, z) * C(n - r1 + z - 1, z - 1) % mod * now % mod) %= mod;
		}
	}
	L(p, 1, n) {
		int now = 0;
		L(z1, 1, m - 1) {
			(now += (ll) C(n - p + z1 - 2, z1 - 2) * C(n - p + m - z1, m - z1 + 1) % mod) %= mod; 
			(ns += (ll) C(p + z1 - 1, z1) * C(p + m - z1 - 1, m - z1 - 1) % mod * now % mod) %= mod;	
		}
	}
	ns = (ll) ns * 2 % mod;
	cout << ns << "\n";
	return 0;
} 
```

**祝大家学习愉快！**

---

## 作者：Rainbow_qwq (赞：20)

- [CF1503E 2-Coloring](https://www.luogu.com.cn/problem/CF1503E)

---

看到这种条件计数题，可以思考一下什么样的图形符合条件。

画一画图发现，不可能有 $\le 3$ 个黄色的分开部分，否则就会有一行多个蓝色块。

并且不可能黄色全连通并且蓝色也全连通。

---


假设现在统计黄色的两个部分分开的方案数。

这时候就需要多画图，找出符合条件的情况。不要被题面图限制了思维而少数了一些情况（

情况如下，这是左边黄色块在右边黄色块下面的情况。也可以在上面，只要把答案乘上 2 。

![](https://cdn.luogu.com.cn/upload/image_hosting/g0fcildn.png)

如何计算个数？

考虑枚举中间那条虚线的位置，再枚举 2 个红点的位置，计算符合条件的黄色块边界数量。

这个可以通过 4 个角到某几个点的路线方案数乘起来计算，路径方案数显然是组合数。

见下图：（注意细节，由于枚举的是右上角，左下角，所以最后一步的方向是确定的。）

![](https://cdn.luogu.com.cn/upload/image_hosting/4pzpdaa6.png)

这样枚举是 $O(n^3)$ 的，前缀和优化就是 $O(n^2)$ 了。

还要计算蓝色两块分开的方案数，直接交换 $n,m$ 算就行了。

然后就会发现算重了，蓝色、黄色都分开的重复算了。

其实很好处理，在算蓝色的时候强制让两个红点相差 $\ge 1$ 即可。

有一点点细节，画画图就会了。

[代码](https://www.luogu.com.cn/paste/7fzkp1yk)

画图不易，求赞qwq（

---

## 作者：too_later (赞：8)

[link](https://www.luogu.com.cn/problem/CF1503E)

### 大致题意：

求满足以下条件的 $n\times m$ 的矩阵的个数：

- 一行既不能没有 $1$ ，也不能出现两个不相邻的 $1$。

- 一列既不能全为 $1$ ，也不能有两个不相邻的 $1$ 。

$1\le n,m\le 2021$。

### Sol.

#### 前置知识：插板法。

如果第 $0$ 个位置为 $v$，那么长度为 $n$ 的不上升序列个数为 $\dbinom{v+n}{v}$。

证明：问题等价于有 $v$ 个球，每次减少插板插掉一个球。从组合意义来说，第一个板有 $v+1$ 种插法，第二个板有 $v+2$ 种插法……第 $n$ 个板有 $v+n$ 个插法。但是板子排列是重的，因此还要除以 $n!$，得到 $\binom{v+n}v$。

#### 正解：

我们发现题目只有两种形式：一种是上下两个山峰，在某处相遇。一种是左右两个山峰，在某线相逢。

很简单，因为如果 $(i,j)$ 是 $1$，那么必定有 $\forall k<j,(i,k)=1$ 或者 $\forall k>j,(i,k)=1$。而且不存在 $(i+1,j-1)=0$ 且 $(i+1,j+1)=0$，不然就是横着的 $101$ 是不合法的。因此，不存在下凹，一定只有一条单调上升&单调下降。单调上升和单调下降汇集在一个点形成山峰。

也可以理解为，下降了就不能上升，因为会出现凹槽，就有 $101$ 了，因此是山峰。

这两个山峰峰顶一定不能相交，不然就出现一列全都为 $1$ 了。

那么我们枚举 $i$ 表示相会的 $y$ 坐标，$j$ 为左山峰的峰顶（就是最大值）右端点，$k$ 为右山峰的左端点，那么有：

$$\sum\limits_{i=1}^n \sum\limits_{j=1}^m \sum\limits_{k=j+1}^m \dbinom{i+j-1}{i} \dbinom{i+m-j-1}{i-1}\dbinom{k+n-i-2}{n-i-1}\dbinom{m-k+n-i}{n-i}$$

为什么会有 $i$ 和 $i-1$ 的区别呢，因为左山峰右端点右边一定不能为 $i$ 不然就和假设矛盾了，因此他等价于 $i-1$ 开始。其余手推不(hai)难(hao)。

然后就是左右的山峰配对了，其实你把纸逆时针旋转 90° 就会发现这不是 $swap(n,m)$ 吗？但是要注意，在相会处如果 $k=j+1$ 的话（y 轴相会，x 轴也相会），那么会导致他既被认为是上下又被认为是左右，因此减掉就好了（让 $y=\alpha$ 不相会）。

然后你发现这个式子可以这么处理：

$$\sum\limits_{i=1}^n (\sum\limits_{j=1}^m \dbinom{i+j-1}{i} \dbinom{i+m-j-1}{i-1})(\sum\limits_{k=j+1}^m \dbinom{k+n-i-2}{n-i-1}\dbinom{m-k+n-i}{n-i})$$

然后就做完了。

时间复杂度 $O(nm)$。

### Code:

```cpp
#include<bits/stdc++.h>
#define I inline
#define RI register int
#define rep(i,a,b) for(RI i=a;i<=b;++i)
#define dow(i,a,b) for(RI i=a;i>=b;--i)
using namespace std;
const int N=2025,mo=998244353;
int n,m,ans,C[N<<1][N<<1],sum[N][N];
I int add(int a,int b){ return a+b>=mo?a+b-mo:a+b; }
I int sub(int a,int b){ return a-b<0?a-b+mo:a-b; }
I int mul(int a,int b){ return 1ll*a*b%mo; }
int main(){
	scanf("%d%d",&n,&m),C[0][0]=1;
	rep(i,1,(N<<1)-1) rep(j,0,(N<<1)-1) C[i][j]=add(C[i-1][j-1],C[i-1][j]);
	rep(i,1,n) rep(j,1,m) sum[i][j]=add(sum[i][j-1],mul(C[j+n-i-2][n-i-1],C[m-j+n-i][n-i]));
	rep(i,1,n) rep(j,1,m) ans=add(ans,mul(C[i+j-1][i],mul(C[m-j+i-1][i-1],sub(sum[i][m],sum[i][j]))));
	swap(n,m);
	rep(i,1,n) rep(j,1,m) sum[i][j]=add(sum[i][j-1],mul(C[j+n-i-2][n-i-1],C[m-j+n-i][n-i]));
	rep(i,1,n) rep(j,1,m-1) ans=add(ans,mul(C[i+j-1][i],mul(C[m-j+i-1][i-1],sub(sum[i][m],sum[i][j+1]))));
	return printf("%d\n",add(ans,ans)),0;
}
```

resound. 永远可爱！

---

## 作者：Exber (赞：7)

> 输入正整数 $n,m$，要求把一个 $n \times m$ 的棋盘染成蓝色和黄色，且每行恰好有一段蓝色的格子，每列恰好有一段黄色的格子。输出总方案数对 $998244353$ 取模的结果。
>
> $n,m\le2021$。

CF *3100 虚高。

显然合法的棋盘是长这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/wgw1hlox.png)

抽象一点：

![](https://cdn.luogu.com.cn/upload/image_hosting/4s7lf7ab.png)

大概就是上面一个山坡下面一个山坡，并且两个山坡没有接触。

先考虑怎么数山坡的方案数，显然可以把山坡劈成单调不降的两段，设 $dp_{i,j}$ 表示 $i$ 根柱子，最高的柱子（第 $i$ 根）高 $j$ 的方案数，显然有 $dp_{0,0}=1$，转移为：
$$
dp_{i,j}=\sum\limits_{k=0}^{j}dp_{i-1,k}
$$
接下来考虑拼接形成山坡，由于上面的山坡和下面的山坡不能有接触，但是每一行都必须有某一个山坡经过，所以两个山坡最高的柱子之间只有两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/7meh2o3a.png)

（最高的柱子交错）

和：

![](https://cdn.luogu.com.cn/upload/image_hosting/jhet1ic5.png)

（最高的柱子高度和为 $n$）

交错的情况很简单，显然两根最高的柱子一定是相邻的，那么把网格劈成两半，算出 $dp2_{i,j}$ 表示上下都有 $i$ 根柱子，下面最高的那根柱子长度为 $j$，上面最高的那根柱子长度 $\le n-j-1$ 的方案数，显然有 $dp2_{i,j}=dp_{i,j}\times\sum\limits_{k=0}^{n-j-1}dp_{i,k}$。然后枚举左边的那一半有多长和上面最高的柱子的高度，和右边拼起来即可：
$$
ans1=\sum\limits_{i=1}^{m-1}\sum\limits_{j=2}^{n-1}dp2_{i,j}\times\sum\limits_{k=n-j+1}^{n-1}dp2_{m-i,k}
$$
高度和为 $n$ 的情况有点麻烦，不难发现上面的最高柱子区间和下面的最高柱子区间一定不相交，那么仍旧把网格劈成两半，求出 $dp3_{i,j}$ 表示一共有 $i$ 个柱子可以是最高的，最高的柱子高度为 $j$ 时山坡的方案，显然有 $dp3_{i,j}=dp_{i,j}\times\sum\limits_{k=0}^{j-1}dp_{m-i,k}$。然后强制让上面最高柱子的区间右端点为 $i$，枚举下面最高柱子的区间左端点 $j$ 即可：
$$
ans2=\sum\limits_{i=1}^{m-1}\sum\limits_{j=1}^{n-1}dp3_{i,j}\times\sum\limits_{k=i+1}^{m}dp3_{m-i+1,n-j}
$$
答案即为 $ans=2(ans1+ans2)$ 因为上下可以反过来。

不难发现所有式子都可以用前缀和优化到 $O(nm)$，那么就做完了。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int S=3005,p=998244353;

int n,m;
int dp[S][S],sm[S][S];
int sm2[S][S];

inline void add(int &x,int y)
{
	x+=y;
	if(x>=p) x-=p;
}

int main()
{
	scanf("%d%d",&n,&m);
	dp[0][0]=1;
	for(int i=0;i<=n;i++) sm[0][i]=1;
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<=n;j++) dp[i][j]=sm[i-1][j];
		for(int j=0;j<=n;j++)
		{
			if(j>0) sm[i][j]=sm[i][j-1];
			add(sm[i][j],dp[i][j]);
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=n-1;j>=0;j--)
		{
			sm2[i][j]=sm2[i][j+1];
			add(sm2[i][j],1ll*dp[i][j]*sm[i][n-j-1]%p);
		}
	}
	int ans=0;
	for(int i=1;i<=m-1;i++)
	{
		for(int j=2;j<=n-1;j++)
		{
			int pre=1ll*dp[i][j]*sm[i][n-j-1]%p*sm2[m-i][n-j+1]%p;
			add(ans,pre);
		}
	}
	memset(sm2,0,sizeof(sm2));
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n-1;j++)
		{
			int pre=1ll*dp[i][j]*sm[m-i][j-1]%p;
			sm2[i][j]=sm2[i-1][j];
			add(sm2[i][j],pre);
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n-1;j++)
		{
			int pre=1ll*dp[i][j]*sm[m-i][j-1]%p*sm2[m-i][n-j]%p;
			add(ans,pre);
		}
	}
	ans=2ll*ans%p;
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：gary2005 (赞：6)

# CF1503E 2-Coloring 题解

首先什么每列只有一段发现是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/x9kmu8yh.png)

但是有一种情况是这样的：
![](https://cdn.luogu.com.cn/upload/image_hosting/obz1hcjm.png)

但是冷静一下，就会发现这本质上是一种情况，一个是上下连接了起来，一个是左右连接了起来，所以我们可以考虑上下连接的情况，左右同理。

假设我们知道了u,d,l:

![](https://cdn.luogu.com.cn/upload/image_hosting/tf19wyjf.png)

则方案数为${d+l-1\choose {l-1} }\cdot {u+l-1\choose l-1}$

其实我们只需要枚举下面这张图中的两部分的分界点$u,d$，左边的长度$l$就行了。

然后简单推一波式子：

$$
sum(d,k)=\sum _{i=0}^d {i+k-1\choose i}
$$
$$
g(d,l)=sum(d-1,l)\times {n-d+l-1\choose n-d}
$$
$$
ans=\sum_{l=1}^{m-1} \sum_{i+j\leq n} g(i,l)\times g(j,m-l)
$$

就行了。

时间复杂度为$O(N^2)$。

[Submission #112205378 - Codeforces](https://codeforces.com/contest/1503/submission/112205378)

---

## 作者：pyiming (赞：2)

# 题意简述

给定一个 $n$ 行 $m$ 列的网格，每个格子可以涂成蓝色或黄色。一个“愚蠢的”涂色方案要求：

- 每一行至少包含一个连续的蓝色单元格段，且该行中所有的蓝色单元格都必须连续。
- 每一列至少包含一个连续的黄色单元格段，且该列中所有的黄色单元格都必须连续。

题目要求计算有多少种不同的“愚蠢的”涂色方案，并输出这个数量对 $998244353$ 取模的结果。

输入格式：输入包含一行，有两个整数 $n$ 和 $m$ ($1 \le n, m \le 2021$)，分别表示网格的行数和列数。

输出格式：输出一个整数，表示“愚蠢的”涂色方案的数量（对 $998244353$ 取模）。

# 解题思路

将蓝色单元格视为 $1$，黄色单元格视为 $0$。

逐行考虑，同时维护每列的情况，鉴于每列情况形如

```
1
1
0
0
0
1
1
```

不妨把第二次出现的 $1$ 视为 $2$，列的情况变为

```
1
1
0
0
0
2
2
```

考虑每行的情况，应形如

```
00112200
```

显然，$1$ 和 $2$ 必须连续，若出现 $1$ 和 $2$ 不连续，则必然不合法。

若同时出现 $1$ 和 $2$，不太好想，考虑只出现 $1$ 或者 $2$ 的情况，若只出现 $1$（$2$ 同理），显然可以通过插板法插出该 $1$ 序列的左右端点做到 $O(1)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/91ea8lc8.png)

接下来只需要考虑同时含有 $1$ 和 $2$ 的情况，钦定 $x$ 表示最下面的只含有 $1$ 的行，$y$ 表示最上面的只含有 $2$ 的行。

显然，有两种情况：

1. $x$ 和 $y$ 相邻，此时只需保证 $1$ 和 $2$ 不相交。
2. $x$ 和 $y$ 不相邻，则 $1$ 的左端点必须和 $2$ 的右端点相邻（反之亦然）。

![](https://cdn.luogu.com.cn/upload/image_hosting/5sthcfs3.png)

先考虑第 $2$ 种情况，只需要插板法插出 $x$ 和 $y$ 行之间的序列左右端点就可以了。但显然，这样的复杂度不优。

考虑枚举 $1$ 的左端点和 $2$ 的右端点之间的位置（反之亦然）。那么我们所插的板形如下图，不难发现，我们根本无需确定 $1$ 的右端点必须和 $2$ 的左端点，做插板法时已经把所有情况考虑进去了。如果我们枚举 $x$ 和 $y$，显然可以在 $O(n^2m)$ 的时间复杂度内解决此问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/cih5lj6s.png)

考虑优化，对 $x$ 有贡献的的 $y$ 显然满足 $x \le y$，从下往上枚举 $x$，再用前缀和优化，就可以做到 $O(nm)$ 了。

考虑第 $1$ 种情况，显然我们得不到类似于以下这样优秀的性质。

> $1$ 的左端点和 $2$ 的右端点相邻

但是不难发现，若我们将整个矩形旋转 $90°$，则情况 $1$ 就变为了情况 $2$，不妨旋转以后再统计一下答案。

注意到会算重，对于同时满足以下两条性质的答案，我们在第二遍时直接不统计就可以了。

1. $x$ 和 $y$ 相邻
2. $1$ 的左端点和 $2$ 的右端点相邻

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
void read(T &x){
    char c; bool f = 0;
    while(((c = getchar()) < '0' || c > '9') && c != '-');
    if(c == '-'){f = 1; c = getchar();}
    x = c - '0';
    while((c = getchar()) >= '0' && c <= '9')x = x * 10 + c - '0';
    if(f) x = -x;
}
template <typename T>
void write(T x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9)write(x / 10);
    putchar(x % 10 + '0');
}
const int N=2021,mod=998244353;
struct fastmod {
    // typedef unsigned long long u64;
    // typedef __int128 u128;
    ll m;
    // u64 b;
    fastmod(int m) : m(m){}
    int reduce(ll a) {
       return a%m;
    }
}z(mod);
ll pow(ll a,ll b,ll p){
    ll ans=1;
    while(b){
        if(b&1) ans=z.reduce(ans*a);
        a=z.reduce(a*a);
        b>>=1;
    }
    return ans;
}
ll v[2*N+2],inv[2*N+1];
ll s[N+2][N+2];
ll C(int n,int m){
    if(n<m||n<0||m<0){
        return 0;
    }
    return z.reduce(z.reduce(v[n]*inv[m])*inv[n-m]);
}
void prework(){
    v[0]=1;
    for(int i=1;i<=2*N;i++){
        v[i]=z.reduce(v[i-1]*i);
    }
    inv[2*N]=pow(v[2*N],mod-2,mod);
    for(int i=2*N-1;i>=0;i--){
        inv[i]=z.reduce(inv[i+1]*(i+1));
    }
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            s[i][j]=C(i+j,j);
            // a[i][j]=a[i-1][j]+s[i][j];
        }
    }
}
ll t1[N+2],t2[N+2],t3[N+2],t4[N+2];
int main(){
    prework();
    // cout<<C(1,0)<<endl;
    int n,m;
    read(n);
    read(m);
    ll ans=0;
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            t1[j]=z.reduce(s[i][j-1]*s[i-1][m-j]);
            t2[j]=z.reduce(s[i-1][j-1]*s[i][m-j]);
            t3[j]=z.reduce(s[n-i][j-1]*s[n-i-1][m-j]);
            t4[j]=z.reduce(s[n-i-1][j-1]*s[n-i][m-j]);
            // cout<<t1[j]<<" "<<t2[j]<<" "<<t3[j]<<" "<<t4[j]<<endl;
        }
        ll temp=0;
        for(int j=m;j>=1;j--){
            ans=z.reduce(ans+z.reduce(temp*t1[j]));
            temp=z.reduce(temp+t4[j]);
        }
        temp=0;
        for(int j=1;j<=m;j++){
            ans=z.reduce(ans+z.reduce(temp*t2[j]));
            temp=z.reduce(temp+t3[j]);
        }
    }
    swap(n,m);
    memset(t1,0,sizeof t1);
    memset(t2,0,sizeof t2);
    memset(t3,0,sizeof t3);
    memset(t4,0,sizeof t4);
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            t1[j]=z.reduce(s[i][j-1]*s[i-1][m-j]);
            t2[j]=z.reduce(s[i-1][j-1]*s[i][m-j]);
            t3[j]=z.reduce(s[n-i][j-1]*s[n-i-1][m-j]);
            t4[j]=z.reduce(s[n-i-1][j-1]*s[n-i][m-j]);
            // cout<<t1[j]<<" "<<t2[j]<<" "<<t3[j]<<" "<<t4[j]<<endl;
        }
        ll temp=0;
        for(int j=m;j>=1;j--){
            ans=z.reduce(ans+z.reduce(temp*t1[j]));
            temp=z.reduce(temp+t4[j+1]);
        }
        temp=0;
        for(int j=1;j<=m;j++){
            ans=z.reduce(ans+z.reduce(temp*t2[j]));
            temp=z.reduce(temp+t3[j-1]);
        }
    }
    write(ans);
    putchar('\n');
    return 0;
}
```

---

## 作者：KAxdd (赞：1)

## 题意
给定一个 $n\times m$ 的矩阵，要你把矩阵的每一个格子染成蓝的或黄的，要求每一行的蓝色格子段数（连通块数）恰好有一个，每一列的黄格子段数恰好有一个。求染色方案数，答案对 $998244353$ 取模。

## 题解
首先可以发现，直接去做这道题并不好做，因为我们的连通块并不能直接计算，我们考虑发现一些性质。

首先连通块的位置不好考虑，考虑连通块数量。我们惊奇的发现，连通块数量至多为 $2$。因为假设我们只考虑黄色（两种颜色没有区别）我们发现在多个连通块中间不连通，要么就有可能有一行没有，要么就有可能一行有多个。

这样子考虑的话我们只需要枚举连通块的分界点就可以了。但很明显，连通块枚举是 $O(n^3)$ 的，还需要继续优化。

![](https://cdn.luogu.com.cn/upload/image_hosting/zfyjrt4w.png)
我们发现假设我们固定一个连通块的上半部分，下半部分方案数实际上是可以直接利用的（就相当于平移方案），理论上来说复杂度就已经优化到了 $O(n^2)$。

现在只需要考虑计数了。我们假设把一个分成两个部分，因为要选就要选一整行，所以我们只需要考虑最外围的轮廓线的方案数就可以了，我们可以把他看作每次可以向下和向左移动，这样子方案数就是好求的。假设我们可以往左移动 $n$ 步,往下移动 $m$ 步，那么方案数就是 $\begin{pmatrix}n+m\\n\end{pmatrix}$。剩下的部分是简单的，只需要注意只有一个连通块方案会算重的方案就行了。

## ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,N=5005;
int n,m;
int fx[N],fy[N],fac[N],inv[N],sum[N][N],g[N][N],pre[N];
int ksm(int x,int y) {
    int ans=1;
    while(y) {
        if(y&1) ans=(1ll*ans*x)%mod;
        x=(1ll*x*x)%mod;
        y>>=1;
    }
    return ans;
}
void init() {
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=(1ll*fac[i-1]*i)%mod;
    inv[N-1]=ksm(fac[N-1],mod-2);
    for(int i=N-2;i>=0;i--) inv[i]=(1ll*inv[i+1]*(i+1))%mod;
}
int C(int x,int y) {
    return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int sol(int x,int y,int fl) {
    for(int i=1;i<=x;i++) {
        for(int j=1;j<=y;j++) {
            g[i][j]=(1ll*sum[i-1][j]*C(x-i+j-1,x-i))%mod;
        }
    }
    int res=0;
    for(int i=1;i<=y-1;i++) {
        for(int j=1;j<=x;j++) pre[j]=(1ll*pre[j-1]+g[j][y-i])%mod;
        for(int j=1;j<=x-1-fl;j++) {
            res=(1ll*res+2ll*g[j][i]%mod*1ll*pre[x-j-fl]%mod)%mod;
        }
    }
    return res;
}
signed main() {
#ifndef ONLINE_JUDGE  
#ifndef KAxdd
    freopen("2-Coloring.in","r",stdin);
    freopen("2-Coloring.out","w",stdout);
#endif 
#endif  
    init();
    scanf("%d %d",&n,&m);
    for(int i=1;i<=max(n,m);i++) {
        sum[0][i]=1;
        for(int j=1;j<=max(n,m);j++) {
            sum[j][i]=(1ll*sum[j-1][i]+C(i+j-1,j)%mod)%mod;
        }
    }
    for(int i=1;i<=max(n,m);i++) {
        for(int j=1;j<=max(n,m);j++) {
            g[i][j]=(1ll*sum[i-1][j]*C(n-i+j-1,n-i)%mod)%mod;
        }
    }
    printf("%lld\n",(1ll*sol(n,m,0)+sol(m,n,1)%mod)%mod);
    return 0;   
}
```

---

## 作者：Federico2903 (赞：1)

## 思路

~~集中注意力~~可以发现，合法染色方案的结果一定是黄色和蓝色各自形成 $\le 2$ 个连通块，并且两种连通块都只有一个的情况也不合法（每一列必须有一段黄色/每一行必须有一段蓝色）。

根据上述情况，原图存在一条直线 $x = l$ 使得左右两边的连通块的右/左边界和该直线交于两个不交的区间。

左右两边的计算方法是一样的，我们先只单独查看一侧。这里以左侧为例。

![](https://s2.loli.net/2024/03/04/8q7ZN2f1Qch6WLX.png)

单独取出上半部分来看，相当于从左上角走到 $(l, a)$ 的方案数量，但是由于最后一格是最下方的格子，我们需要钦定最后一步必须向下，也就是相当于走到其上方的格子。

那么我们可以直接枚举 $a, b, l$，式子是显然的。暴力枚举的时间复杂度为 $O(n^2m)$。

但是不难发现，这个式子可以使用前缀和优化。

记录一个 $sum(i, j) = \sum\limits^{i}_{k = 0} {k + j - 1\choose k}$。

每次计算一个部分的答案时可以使用 $sum(i - 1, j)$ 来帮助递推答案。

最终时间复杂度 $O(nm)$，可以通过此题。

[My Submission](https://codeforces.com/contest/1503/submission/249530913)

---

## 作者：daduoli (赞：0)

首先看到这个题目，考虑怎样的图形是合法的，容易发现因为我们要求每行恰有一个蓝色块，所以我们每行一定是从最左边往右延伸若干个黄色块，从最右边往左延伸若干个黄色块，且不存在全黄色段。

![](https://cdn.luogu.com.cn/upload/image_hosting/pokglab5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

接下来考虑列的限制，因为恰有一个黄色连续段，所以对于每一列而言，他出现黄色的部分一定是连续的。

我们记第 $i$ 行从最左边往右延伸的长度为 $l_i$，那么容易发现 $l$ 是一个存在 $mid$ 满足 $l_1\le l_{2}\le \dots\le l_{mid}\ge \cdots\ge l_{n-1}\ge l_n$ 的序列。

对于 $r_i$ 同理。

那么我们可以将我们的答案分成两种情况：

- $\max l_i<m-\max r_i+1$。
- $\max l_i\ge m-\max r_i+1$。

先考虑计算第一种答案。

---

由于是因为 $\max l_i<m-\max r_i+1$，所以容易知道 $\max l_i+1=m-\max r_i+1$。

考虑枚举 $\max l_i$ 的位置，由于可能存在相同的位置，我们在所有 $\max l_i$ 中枚举最上面的位置。

这时候我们钦定 $\max r_i$ 在 $\max l_i$ 的右上角，具体是长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/s5ylguhy.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们先枚举 $\max l_i=y$，然后从后往前枚举第 $x$ 行。

每次钦定第 $x$ 行为所有 $l_i=y$ 中最大的 $x$ 添加进我们的答案算贡献。

$$res_x=\sum\limits_{i=n}^x{y-1+n-x\choose n-x}$$

具体地 $y-1$ 是因为我们钦定了当前行为 $l_i=y$ 中 $x$ 最大的行，所以下一行一定至少减 $1$，后面的而组合数是显然的。

然后因为 $1\sim x-1$ 行的贡献也还没有算，计算完之后是这样的：

$$res_x\times {y-1+i-1\choose i-1}$$

这样第 $x$ 行的左边部分贡献就算好了，进一步对于右边部分的贡献我们也可以类似于左边的算，然后用一个前缀和即可。

因为我们是钦定了右边的最大值在左边最大值的上面，只需要再乘一个 $2$ 就是我们这部分的总贡献，这样可以得到右边最大值在左边最大值下面的情况。

这一部分的时间复杂度不难做到 $O(nm)$。

---

接下来我们考虑第二部分的答案。

我们记右边最大值最下面的位置为 $q$，左边最大值最上面的位置为 $p$，那么有 $q+1=p$,差不多长下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/2g4o9yhm.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这时候有一个很暴力的做法，考虑枚举 $\max l_i,\max r_i$，然后再枚举第几行算贡献，这样会获得一个 $O(nm^2)$ 的做法，无法通过，考虑优化。

先把我们原本的贡献的式子写出来先。

$$\sum\limits_{i=1}^{m-1}\sum\limits_{j=m-i+1}^{m-1}\sum\limits_{q=2}^{n}{m-j-1+q-1\choose q-1}{i+n-q\choose n-q}{j+q-2\choose q-2}{m-i-1+n-q+1\choose n-q+1}$$

我们现在需要把这个东西优化到 $O(nm)$。

$$
\begin{aligned}
&\sum\limits_{i=1}^{m-1}\sum\limits_{j=m-i+1}^{m-1}\sum\limits_{q=2}^{n}{m-j-1+q-1\choose q-1}{i+n-q\choose n-q}{j+q-2\choose q-2}{m-i-1+n-q+1\choose n-q+1}
\\
&=\sum\limits_{q=2}^{n}\sum\limits_{i=1}^{m-1}{i+n-q\choose n-q}{m-i-1+n-q+1\choose n-q+1}\sum\limits_{j=m-i+1}^{m-1}{m-j-1+q-1\choose q-1}{j+q-2\choose q-2}
\end{aligned}
$$

容易发现后面的那一坨求和式只与 $q,j$ 有关，所以可以将那个东西预处理出来，然后因为每次随着 $i$ 的变化至多改变一项，这是可以维护的。

这题就做完了，当然最后也要乘一个 $2$，时间复杂度 $O(nm)$。

代码就不放了，很好写的，没啥细节。

---

## 作者：binbin_200811 (赞：0)

# [CF1503E 2-Coloring](https://www.luogu.com.cn/problem/CF1503E)

cjx 组合强。

## 思路

观察一下题目，不难发现只有当黄色形成如下的单峰时才合法。

（~~染错色了，将就一下~~）

![](https://cdn.luogu.com.cn/upload/image_hosting/73lsvbkz.png)

其中两座峰的峰顶高度相加等于 $m$，为了方便统计，我们钦定右边的峰一定在左峰下方的行出现，最后答案乘以二就是最终方案。

发现对于每一边是两个最长不下降子序列拼在一起。

设 $f[i][j]$ 为长度为 $i$ 的最长不下降子序列，最高点高度为 $j$ 的方案数。

再设 $f'[i][j]$ 为长度为 $i$ 的最长不下降子序列，仅有一个最高点为 $j$ 的方案数。

答案就是
$$
2\times \sum_{i=1}^n\sum_{j=i+1}^{n}\sum_{k=1}^{m-1} (f[i][k]\times f'[n-i+1][k])\times (f'[j][m-k]\times f[n-j+1][m-k])
$$
相当于枚举第一个峰在行 $i$，第二个峰在行 $j$，第一个峰高度为 $k$。

变幻一下：
$$
2\times \sum_{i=1}^n\sum_{k=1}^{m-1}(f[i][k]\times f'[n-i+1][k])\times \sum_{j=i+1}^{n} (f'[j][m-k]\times f[n-j+1][m-k])
$$
这样给后一个和式做一个后缀和优化，即可把复杂度优化到 $O(n^2)$ 级别。

当然有例外是这个样子。

![](https://cdn.luogu.com.cn/upload/image_hosting/2o5gae94.png)

两峰交在一起（必须保证在连续的行且峰顶高度相加大于 $m$），也是一种方案。
$$
2\times \sum_{i=1}^n\sum_{x=1}^{m-1}\sum_{y=1}^{m-1} (f[i][x]\times \sum_{k=1}^{y-1} f[n-i][k])\times (f[n-i][y]\times\sum_{k=1}^{x-1}f[i][k])
$$
相当于枚举左边的峰顶在行 $i$，左峰高度为 $x$，右峰高度为 $y$，同时求和了峰过后的一段不下降子序列的方案。
$$
2\times \sum_{i=1}^n\sum_{x=1}^{m-1} (f[i][x]\times\sum_{k=1}^{x-1}f[i][k] )\sum_{y=1}^{m-1} (f[n-i][y]\times\sum_{k=1}^{y-1} f[n-i][k])
$$
对于 $\sum_{k=1}^{x-1}f[i][k]$ 和 $\sum_{k=1}^{y-1} f[n-i][k]$ 前缀和优化。

然后预处理出所有的
$$
f[n-i][y]\times\sum_{k=1}^{y-1} f[n-i][k]
$$
再次前缀和。

即可在 $O(n^2)$ 的时间内求出上述和式。

对于 $f$ 和 $f'$ 的转移是容易的。
$$
f[i][j]=\sum_{k=1}^j f[i-1][k]
$$

$$
f'[i][j]=\sum_{k=1}^{j-1} f[i-1][k]
$$

初始值 $f[0][0]=1$。

其实你看到这里，已经可以使用 dp 做出本题了，但是如果你想进一步了解组合，请移步。

不难发现，我们每次的转移都相当于求一次前缀和，而 $f[0][0]=1$。

所以有可以构造这样的生成函数：
$$
f[0]=1
$$
观察 $\sum_{i=0} x^i$ 的优雅性质，你会发现 $1\times \sum_{i=0} x^i$ 相当于求一次前缀和。

而 $(\sum_{i=0} x^i)^2$ 相当于求两次前缀和（$x^i$ 的系数是第 $i$ 项的求前缀和后的值）。

由 $f[0]$ 转移到 $f[1]$ 的过程相当于乘以 $\sum_{i=0} x^i$（一次前缀和），所以有：
$$
f[1][j]=[x^j](\sum_{k=0} x^k)^1
$$
推广一下，每次 $f[i]$ 向 $f[i+1]$ 的转移都是乘以 $\sum_{i=0} x^i$（每转移一次求一次前缀和），所以有：
$$
f[i][j]=[x^j](\sum_{k=0}x^k)^i
$$
对于 $\sum_{i=0} x^i$，的封闭形式为 $(1-x)^{-1}$ 有很多种方法求，这里不再赘述。

所以有：
$$
f[i][j]=[x^j](1-x)^{-i}
$$
使用广义二项式展开 $(1+(-x))^{-i}$，即可得到第 $j$ 项的系数为：
$$
\binom{-i}{j}=(-1)^j\binom{i+j-1}{j}
$$
关于牛顿二项式系数，已经有完备的公式，本处直接套公式即可，故不再展开讨论。

把系数乘上 $(-x)^j$，有
$$
f[i][j]=\binom{i+j-1}{j}
$$
从比较简单的组合意义考虑，有 $j$ 个球，有 $i-1$ 个挡板，可以为空，两个挡板之间的球数相当于相邻两项的差。

那么有：
$$
f[i][j]=\binom{i+j-1}{i-1}=\binom{i+j-1}{j}
$$
在观察一下 $f'$ 求值的式子，你会发现 $f'[i][j]=f[i][j-1]$。

所以其实你也求出 $f'$ 的组合意义了。

相当于有 $j$ 个球，$i-1$ 个挡板，最后一个挡板至少挡一个球，那么就可以投入 $j-1$ 个球供所有挡板挡。
$$
f'[i][j]=\binom{i+j-2}{j-1}
$$
如果考虑生成函数的话，$f'[i][j]$ 相当于较 $f[i][j]$ 向后平移了一个位置，那么可以写成：
$$
f'[i][j]=[x^{j-1}](1-x)^{-i}
$$
或
$$
f'[i][j]=[x^j](1-x)^{-i}x
$$
于是你就可以 ~~愉快~~ 的 AC 本题了。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define N 5000
#define mod 998244353

const int maxn=5e3+5;

ll n,m,ans;
ll fac[maxn],inv[maxn],f[maxn];

inline ll ksm(ll x,ll y)
{
    ll sum=1;
    for(;y;y/=2,x=x*x%mod) if(y&1) sum=sum*x%mod;
    return sum;
}
inline ll C(int n,int m)
{
    if(n<m||m<0) return 0;
    return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int main()
{
    freopen("magic.in","r",stdin);
    freopen("magic.out","w",stdout);
    for(int i=fac[0]=1;i<=N;i++) fac[i]=fac[i-1]*i%mod;
    inv[N]=ksm(fac[N],mod-2);
    for(int i=N-1;~i;i--) inv[i]=inv[i+1]*(i+1)%mod;
    scanf("%lld%lld",&n,&m);
    for(int h=1;h<n;h++)
    {
        for(int j=m;j>=2;j--)
        {
            f[j]=(1LL*f[j+1]+1LL*C(j+n-h-2,n-h-1)*C(m-j+n-h,n-h)%mod)%mod;
        }
        for(int i=m-1;i>=1;i--)
        {
            ans = (1LL*ans+1LL*C(i+h-1,h)*C(m-i+1+h-2,h-1)%mod*f[i+1]%mod)%mod;
        }
    }
    memset(f,0,sizeof(f));
    for(int x=1;x<=m;x++)
    {
        for(int j=n-1;j>=1;j--)
        {
            f[j]=(1LL*f[j+1]+1LL*C(m-x+n-j-1,n-j-1)*C(m-x+j-1,j)%mod)%mod;
        }
        for(int i=1;i<n;i++)
        {
            ans=(1LL*ans+1LL*C(x+i-1,i)*C(x+n-i-1,n-i-1)%mod*f[n-i+1]%mod)%mod;
        }
    }
    printf("%lld\n",ans*2%mod);
}
```

---

