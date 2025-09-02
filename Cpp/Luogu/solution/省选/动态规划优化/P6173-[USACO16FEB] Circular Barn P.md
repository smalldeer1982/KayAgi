# [USACO16FEB] Circular Barn P

## 题目描述

作为当代建筑的爱好者，Farmer John 建造了一个圆形新谷仓，谷仓内部 $n$ 个房间排成环形（$3 \leq n \leq 1000$），按顺时针顺序编号为 $1\ldots n$，每个房间都有通往与其相邻的左右房间的门，还有一扇门通往外面。

FJ 准备让第 $i$ 个房间里恰好有 $r_i$ 头奶牛（$1 \le r_i \le {10}^6$）。为了有序地让奶牛进入谷仓，他打算解锁 $k$ 个从外界进入谷仓的门（$1 \le k \le 7$）。然后，每头奶牛**顺时针**走动，直到到达目的地。FJ 的目标是让所有奶牛走动的距离和最小（奶牛从哪个门进入可以随意安排，这里走动的距离只包含进入谷仓后走动的距离），现在请你求出这个最小距离。

## 说明/提示

FJ 打开 $2,5$ 两个门。$11$ 头奶牛从 $2$ 号门进入，前往 $2,3,4$ 号房间，总距离 $8$。$10$ 头奶牛从 $5$ 号门进入，前往 $5,6,1$ 号房间，总距离 $6$。

## 样例 #1

### 输入

```
6 2
2
5
4
2
6
2```

### 输出

```
14```

# 题解

## 作者：Usada_Pekora (赞：5)

我用的是官方题解中提到的利用分治优化 $O(n^3 k)$ 的暴力程序的做法。优化后复杂度为 $O(n^2k \log n)$ 。

设 $f[i][j]$ 表示到了 $j-1$ 位置一共开了 $i$ 扇门。 $f[0][n]$ 初始化为 $0$ 。（有一维起点隐藏掉了） 。

$f[i][j] = \min { \{ f[i-1][k] + sum_{k,j}\} }$ ，其中 $k$ 是开门的位置。

直接跑显然是不行的，枚举起点、开门数、终点、开门点需要 $O(n^3 k)$ 的复杂度。

如果计算第 $i$ 个门在 $f[i][n/2]$ 中的位置，那么对于 $j<n/2$ 的 $f[i][j]$ 必须在其左侧，对于 $j>n/2$ 的 $f[i][j]$ 必须在其右侧。通过这种方式，我们可以在递归的每个级别平均将搜索空间减半。这样就将复杂度降了一个级别。也就是 $O(n^2k \log n)$ 。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1005, K = 10;
#define INF 0x3fffffffffffffff
int t, n, k;
long long a[N], f[K][N], s[N][N];
inline int pos(int x, int y) {
  return x+y>=n?x+y-n:x+y;
}
inline long long calc(int a, int b) {
  return s[pos(a, t)][pos(b, n - a)];
}
inline void dfs(int k, int x1, int x2, int y1, int y2) {
	if (x1 == x2) return;
	int midx = (x1 + x2) >> 1;
	int midy = -1;
	f[k][midx] = INF;
	for (int j = max(midx + 1, y1); j < y2; j++) {
		long long v = f[k - 1][j] + calc(midx, j);
		if (v < f[k][midx]) {
			midy = j;
			f[k][midx] = v;
		}
	}
	dfs(k, x1, midx, y1, midy + 1);
	dfs(k, midx + 1, x2, midy, y2);
	return;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> k;
	for (int i = n - 1; ~i; i--)  cin >> a[i];
	for (int i = 0; i < n; i++) {
    	long long sum = 0;
		for (int j = 1; j <= n; j++) {
			s[i][j] = s[i][j - 1] + sum;
			sum += a[pos(i, j - 1)];
		}
	}
	memset(f, 63, sizeof(f));
	long long ans = INF;
	f[0][n] = 0;
	for (t = 0; t < n; t++) {
		for (int i = 1; i <= k; i++) dfs(i, 0, n, 1, n + 1);
		ans = min(ans, f[k][0]);
	}
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：Zjl37 (赞：5)

题面传送：[P6173 [USACO16FEB]Circular Barn P](https://www.luogu.com.cn/problem/P6173)，[P3140 [USACO16FEB]Circular Barn Revisited G](https://www.luogu.com.cn/problem/P3140)（弱化版，n 只有 100）

[图解样例](https://cdn.luogu.com.cn/upload/image_hosting/4e33o4kg.png)

有空了，写一篇详细一点的题解。

### DP启示

环上的问题不好考虑，我们可以先想想**一个直线型谷仓的问题**怎么做。

因为奶牛只会顺时针（延正方向）走，所以如果一个房间没有门（下文中的门，都指通往谷仓外面的门），它里面的牛一定是从一个逆时针（反）方向离它最近的门走过来的。所以第一个房间一定要开门。

每开一扇门，就计算到下一扇门之前的位置上所有牛走的路程。可以看出，当前位置的 dp 值与后面的位置有关，所以从后往前 dp. 为了转移方便，如果没有“下一扇门”，就假设“下一扇门”位置是 $ n+1$.

设 $ f(j,l) $ 表示到了 j 位置一共开了 l 扇门，并且 j 位置也开门的最小距离。那么初始值 $ f(n+1,0)=0 $，其余为 $+\infty $. 从下一扇门 p 位置转移过来，新的 dp 值
$$
\begin{aligned}
val = & f(p,l-1)+\sum_{q=j}^{p-j} r_q(q-j) \\
= & f(p,l-1)+\sum_{q=j}^{p-j} (r_q\cdot q) -j\sum_{q=j}^{p-j}r_q \\
= & f(p,l-1)+\sum_{q=j-1}^{p-j+1} (r_q\cdot q) -j\sum_{q=j-1}^{p-j+1}r_q
\qquad\sf\text{(j 位置牛没有路程)}
\end{aligned}
$$
设 $ sr $ 数组为 $ \lbrace r_i \rbrace $ 的前缀和，$ sri $ 数组为 $ \lbrace r_i\cdot i\rbrace $ 的前缀和（可以预处理），那么上式
$$
=f(p,l-1)+sri(p-1)-sri(j)-j\times(sr(p-1)-sr(j))
$$
得到转移方程
$$ f(j,l)=\min_{p=j+1}^{n-j+1} \lbrace f(p,l-1)+sri(p-1)-sri(j)-j\cdot sr(p-1)+j\cdot sr(j)\rbrace\qquad (l=1,2,\cdots,k)$$
最终 $ f(1,k) $ 即为答案。

再来看**原问题**：在原问题的众多可行情况中，对任一一种开门方案，都可以对应**以其中一扇门为起点，破环成链的**一个直线型问题。枚举 n 扇房间作为起点，其直线型问题的的解一定能涵盖原问题的所有情况。

于是给 f 数组加第一维 i 表示起点。在每一个子问题里，谷仓的房间编号就是 $ i,\cdots,n+i-1 $. 解决每个子问题，取其答案的最小值。（也可以每次重用二维数组 f 计算新的子问题——节省空间，但每次 memset 较慢）

该方法的时间复杂度为为 $ O(n^3k) $，只能通过[弱化版 P3140](https://www.luogu.com.cn/problem/P3140)。

### 参考程序1

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int N=101;
const lld inf=0x3f3f3f3f3f3f3f3f;
int n,k,r[2*N];
lld sri[2*N],sr[2*N],f[N][2*N][8],ans=inf;
// 变量名注解：所有变量名（不分大小写）与题面和本题解中含义相同

int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++)
		scanf("%d",&r[i]), r[i+n]=r[i];
	// 破环成链的处理。尤其注意相应数组要开两倍大
	for(int i=1; i<=2*n; i++)
		sr[i]=sr[i-1]+r[i], sri[i]=sri[i-1]+(lld)r[i]*i;
	// 预处理前缀和数组
	memset(f,0x3f,sizeof f);
	// 将数组f中的每个数初始化为inf
	for(int i=1; i<=n; i++) { // 枚举起点
		f[i][n+i][0]=0;
		for(int l=1; l<=k; l++) { // 枚举已开门数
			for(int j=n+i-1; j>=i; j--) // 枚举当前开门位置
				for(int p=j+1; p<=n+i; p++) if(f[i][p][l-1]<inf) {
					// 枚举下一扇门位置
					lld val=f[i][p][l-1]+sri[p-1]-sri[j]-j*(sr[p-1]-sr[j]);
					if(val<f[i][j][l]) f[i][j][l]=val;
				}
			ans=min(ans,f[i][i][l]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

### DP优化

观察转移方程式，在 i、j、l已经确定的情况下，其中有与 j、p 都有关的项 $ -j\cdot sr(p-1) $，有只与 p 有关的项 $ f(i,p,l-1)+sri(p-1) $，剩下的 $ j\cdot sr(j)-sri(j) $ 只与 j 有关。这提示我们可以**斜率优化**。

下面介绍一种斜率优化的方法。

设 $ k=-sr(p-1) $，$ b=f(i,p,l-1)+sri(p-1) $，$y=f(i,j,l)+sri(j)-j\cdot sr(j)$。   
每一条转移方程可以化成 $ y=k\cdot j+b $。我们选择将 j 看做自变量，y 看做关于 j 的函数。那么对每个不同的 p，函数解析式表示一条不同的直线。   
我们要求的 dp 值就是在已知所有的 p（所有的直线）中，找到自变量 j 对应的最小函数值。

注意到：①自变量 j 递减，而 $ j<p\le n+i $。j 每减一，可行的 p 就多一个，对应可行的直线就要加入一条。②随着 p 递减，直线斜率 k 递增。|| 我们可以利用这些性质**将直线存放在单调队列中**，将时间复杂度优化到 $ O(n^2k) $.

- 加入一条直线

![](https://cdn.luogu.com.cn/upload/image_hosting/2h3yco7a.png)

用 head、tail 表示队头、队尾。如图，现在已存在直线 $ \color{#E06E6E}l_{tail-1}$、$ \color {#E6915B}l_{tail} $，即将加入一条$\sf\color{#948AE0}\text{新的直线}$。由于我们要求的是最小函数值，加入$\sf\color{#948AE0}\text{新的直线}$后，不可能再从$ \color {#E6915B}\sf\text{队尾直线} $中取到最小值。做出这个判断等价于$\sf\color{#948AE0}\text{新直线}$与 $ \color {#E6915B}l_{tail} $ 的交点在$\sf\color{#948AE0}\text{新直线}$与$\color{#E06E6E}l_{tail-1}$右侧，（交点横坐标可以联立方程组求）即：
$$ \frac{\color{#948AE0}b-\color {#E6915B}b_{tail}}{\color {#E6915B}k_{tail}\color{#948AE0}-k}\ge\frac{\color{#948AE0}b\color{#E06E6E}-b_{tail-1}}{\color{#E06E6E}k_{tail-1}\color{#948AE0}-k} $$
用 while 循环从**队尾**不断删除“无用”的直线，再加入当前新的直线。

- 求最小函数值

![](https://cdn.luogu.com.cn/upload/image_hosting/a336tmq3.png)

如图，假如现在已存在直线 $ \color{#57975B}l_{head} $，$ \color{#33ADFF}l_{head+1} $，它们的交点在当前 $\color{#818181} x=j $ 的右侧。因为 j 是递减的，最小值不可能再从$\color{#57975B}\sf\text{队头直线}$中取到。这个判断等同于将当前 $\color{#818181} x=j $ 代入 $ \color{#57975B}l_{head} $ 的函数值已经比代入 $ \color{#33ADFF}l_{head+1} $ 大了。   
用 while 循环从**队头**不断删除“无用”的直线，剩下的队头直线将 j 代入一定能得到最小函数值。该函数值加上“只与 j 有关的”那部分就是 dp 值。

上面只讨论了删除**队尾**直线的**可行性**，没有讨论**必要性**。可以结合下图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/ep7xb5io.png)

### 参考程序2

部分代码如下：

```cpp
int qh,qt;
struct line {
	lld k,b;
	line() {}
	line(lld kk, lld bb): k(kk), b(bb) {}
} ln[N];
// 变量名注解：qh、qt为直线队列 ln 的队头、队尾
// 其余变量名（不分大小写）与题面和本题解中含义相同
```

```cpp
for(int l=1; l<=k; l++) { // 枚举已开门数
	qh=1, qt=0; // 清空队列
	for(int j=n+i-1; j>=i; j--) { // 枚举当前开门位置
		lld ki=-sr[j], bi=f[i][j+1][l-1]+sri[j];
		// 加入直线的考量：每次j减少1，可行的p就比原来多一个p=j+1
		while(qh<qt&&(bi-ln[qt].b)*(ln[qt-1].k-ki)>=(bi-ln[qt-1].b)*(ln[qt].k-ki))
			--qt;
		ln[++qt]=line(ki,bi);
		// 从队尾不断删除“无用”的直线，再加入当前新的直线。
		while(qh<qt&&ln[qh].k*j+ln[qh].b>=ln[qh+1].k*j+ln[qh+1].b)
			++qh;
		f[i][j][l]=ln[qh].k*j+ln[qh].b+j*sr[j]-sri[j];
		// 从队头不断删除“无用”的直线，将j代入剩下的队头直线得到最小函数值。
	}
	ans=min(ans,f[i][i][l]);
}
/*
注意：
①作删除判断时，队列中至少要有两条直线。(qh<qt)
②line(ki,bi)调用了line的构造函数。该句等同于
	ln[++qt].k=ki, ln[qt].b=bi;
③与平时做的斜率优化不同，这题自变量是从大到小变化的（表现在图像上，从右到左）。自己实现时，有些方向要尤其注意。
*/
```






---

## 作者：acniu (赞：3)

设

$$
w(l,r)=\sum_{i=l}^r r_i(i-l)
$$

即一段牛从入口 $l$ 进入谷仓的代价。

发现 $w$ 满足四边形不等式：

$$
\begin{aligned}
&w(a,d)+w(b,c)-w(a,c)-w(b,d)\\
=&\sum_{i=a}^d r_i(i-a)+\sum_{i=b}^cr_i(i-b)-\sum_{i=a}^c r_i(i-a)-\sum_{i=b}^dr_i(i-b)\\
=&\sum_{i=c+1}^dr_i(i-a)-\sum_{i=c+1}^dr_i(i-b)\\
=&\sum_{i=c+1}^dr_i(b-a) \ge 0
\end{aligned}
$$

所以直接四边形不等式优化即可，复杂度 $O(n^2k)$。

代码：
```cpp
#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#define freopen(...) 0
#endif
using namespace std;

using ll = long long;
using l3 = __int128_t;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l, ll r) { return rng() % (r - l + 1) + l; }
#define fi first
#define se second
#define eb emplace_back
#define V vector
#define F(i, a, b) for (int i = (a), iee = (b); i <= iee; i++)
#define FO(i, a, b) F(i, a, (b) - 1)
#define R(i, a, b) for (int i = (b), iee = (a); i >= iee; i--)

const ll inf = 0x3f3f3f3f3f3f3f3f;
const int N = 2100;
int n, k, r[N], pos[N][N];
ll f[N][N], w[N][N];

int main() {
	freopen("P6173.in", "r", stdin),
	freopen("P6173.out", "w", stdout),
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> k;
	int m = n * 2;
	F(i, 1, n) cin >> r[i], r[i + n] = r[i];
	F(i, 1, m) F(j, i, m)
		f[i][j] = w[i][j] = w[i][j - 1] + 1ll * (j - i) * r[j];
	F(i, 1, m) pos[0][i] = 1, pos[i][m + 1] = m;
	F(t, 2, k) {
		R(L, 1, m) F(j, L, m) {
			int i = j - L + 1;
			f[i][j] = inf;
			F(k, max(i, pos[i - 1][j]), min(j - 1, pos[i][j + 1])) {
				ll tmp = w[i][k] + f[k + 1][j];
				if (f[i][j] > tmp)
					f[i][j] = tmp, pos[i][j] = k;
			}
		}
	}
	ll ans = inf;
	F(i, 1, n) ans = min(ans, f[i][n + i - 1]);
	cout << ans << "\n";
}
```

---

## 作者：kouylan (赞：2)

遇到环的问题，我们先考虑直线的情况怎么做。

在直线上，定义 $f(i,j)$ 表示到了第 $i$ 间谷仓开了 $j$ 扇门的最小距离。转移时我们只要枚举下一扇开着的门即可。

$f(i,j)=\min\limits_{i+1\leq k\leq n}\{f(k,j)+(k-i)\sum\limits_{i\leq l<k} r_l\}$

把 $r$ 序列反转一下，再设 $s1(i)$ 为 $r_i$ 的前缀和，$s2(i)$ 为 $i\times r_i$ 的前缀和，转移方程就变成了

$f(i,j)=\min\limits_{1\leq k<i}\{f(k,i)+i(s1(i)-s1(k))-(s2(i)-s2(k))\}$

这个式子可以斜率优化。

$f(i,j)=f(k,i)+s2(k)-i\times s1(k)+i\times s1(i)-s2(i)$

我们设 $Y(k)=f(k,i)+s2(k),X(k)=s1(k)$，若 $k_1<k_2$ 且 $k_2$ 优于 $k_1$，则

$Y(k_2)-iX(k_2)\leq Y(k_1)-iX(k_1)$

$\frac{Y(k_2)-Y(k_1)}{X(k_2)-X(k_1)}\leq i$

这是一个下凸包，又因为 $X(k)$ 是前缀和单调递增，所以直接用单调队列维护就行。

一条链上做一次 dp，复杂度是 $nm$ 的。

然后原题是一个环，我们只要枚举起点，每次做 dp 就好，总复杂度 $O(n^2m)$。

下面是 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = (1ll<<61)-1;

int n,m,ans=INF,a[2005],r[2005];
int s1[2005],s2[2005];
int f[2005],g[2005],hd=1,tl=0,dq[2005];

int X(int k)
{
	return s1[k];
}

int Y(int k)
{
	return g[k]+s2[k];
}

double K(int k1,int k2)
{
	return 1.0*(Y(k2)-Y(k1))/(X(k2)-X(k1));
}

signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;cin>>r[i++]);
	reverse(r+1,r+1+n);
	for(int i=1;i<=n;i++)
		r[i+n] = r[i];
	for(int st=1;st<=n;st++)
	{
		for(int i=1;i<=n;i++)
			f[i] = INF;
		for(int i=1;i<=n;i++)
			a[i] = r[st+i-1];
		for(int i=1;i<=n;i++)
			s1[i] = s1[i-1]+a[i], s2[i] = s2[i-1]+i*a[i];
		f[0] = 0;
		for(int j=1;j<=m;j++)
		{
			for(int i=1;i<=n;i++)
				g[i] = f[i];
			hd = 1, tl = 0, memset(dq,0,sizeof(dq));
			dq[++tl] = 0;
			for(int i=1;i<=n;i++)
			{
				while(hd<tl && K(dq[hd],dq[hd+1])<=1.0*i)
					hd++;
				int k=dq[hd];
				f[i] = g[k]+i*(s1[i]-s1[k])-(s2[i]-s2[k]);
				while(hd<tl && K(dq[tl],i)<=K(dq[tl-1],dq[tl]))
					tl--;
				dq[++tl] = i;
			}
		}
		ans = min(ans,f[n]);
	}
	cout<<ans<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：OneLeft (赞：0)

## 题意
有顺时针编号的 $n$ 个房间，房间 $i$ 有 $r_i$ 头奶牛，你需要在这些房间中开 $k$ 扇门，每个奶牛会从某个门进入，然后顺时针行走到自己的谷仓，求奶牛行走距离总和的最小值。
## 思路
在一个环上比较难考虑，因此我们断环为链，这里需要 $O(n)$ 的时间复杂度。

设 $dp_{i,j}$ 为前 $i$ 个房间开 $j$ 扇门时奶牛行走距离的总和，则有转移方程如下：
$$
dp_{i,j}=\min_{k=0}^{i-1}dp_{k,j-1}+w(k+1,i)
$$
其中 $w(i,j)$ 为在房间 $i$ 开门，房间编号为 $i\sim j$ 的奶牛的行走距离总和，可以 $O(n^2)$ 预处理出来。

这个做法是 $O(n^3k)$ 的，无法通过此题，但是可以通过此题的[弱化版](https://www.luogu.com.cn/problem/P3140)。

通过打表可以发现对于 $a\le b\le c\le d$ 有 $w(a,c)+w(b,d)\le w(a,d)+w(b,c)$，证明如下：
$$
w(a,c)=r_{a+1}+2r_{a+2}+\dots+(c-a)a_c\\
w(a,d)=r_{a+1}+2r_{a+2}+\dots+(d-a)a_d\\
w(a,d)-w(a,c)=(c+1-a)a_{c+1}+(c+2-a)a_{c+2}+\dots+(d-a)a_d\\
w(b,d)=r_{b+1}+2r_{b+2}+\dots+(d-b)a_d\\
w(b,c)=r_{b+1}+2r_{b+2}+\dots+(c-b)a_c\\
w(b,c)-w(b,d)=-(c+1-b)a_{c+1}-(c+2-b)a_{c+2}-\dots-(d-b)a_d\\
w(a,d)+w(b,c)-w(a,c)-w(b,d)=(b-a)a_{c+1}+(b-a)a_{c+2}+\dots+(b-a)a_d\\
w(a,d)+w(b,c)-w(a,c)-w(b,d)\ge0\\
w(a,c)+w(b,d)\le w(a,d)+w(b,c)
$$
满足四边形不等式，故满足决策单调性，考虑使用分治优化，最终时间复杂度为 $O(n^2k\log n)$，可以通过此题。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5,M=15,inf=(int)4e18+5;
int a[N<<1],w[N<<1][N<<1],dp[N][M];
void solve(int bgn,int id,int l,int r,int lpt,int rpt)
{
	if(l>r)return;
	int mid=l+r>>1,opt;
	for(int i=lpt;i<=min(mid,rpt);i++)
	{
		int val=dp[i][id-1]+w[i+bgn][mid+bgn-1];
		if(dp[mid][id]>val)dp[mid][id]=val,opt=i;
	}
	solve(bgn,id,l,mid-1,lpt,opt),solve(bgn,id,mid+1,r,opt,rpt);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],a[i+n]=a[i];
	for(int i=1;i<=(n<<1);i++)
	for(int j=i+1;j<=(n<<1);j++)
		w[i][j]=w[i][j-1]+a[j]*(j-i);
	int ans=inf;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<N;j++)
		for(int k=0;k<M;k++)
			dp[j][k]=inf;
		for(int j=1;j<=m;j++)solve(i,j,0,n,0,n);
		ans=min(ans,dp[n][m]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Jadonyzx (赞：0)

典中典模型，考虑**破环成链**。

经过神秘转换，考虑让奶牛们从谷仓**~往返自然~出来**然后就是[P8632 [蓝桥杯 2015 国 B] 居民集会](https://www.luogu.com.cn/problem/P8632)了。

设 $dp_{i,j}$ 表示设了 $j$ 个出口，考虑到第 $i$ 个位置的最小总移动。

设 $pre_i$ 表示前 $i$ 个格子奶牛移动距离前缀和。

设 $cnt_i$ 表示前 $i$ 个格子奶牛数量的前缀和。

有转移方程：

$dp_{i,j}=\min_{x\lt i}dp_{x,k-1}+pre_i-pre_x-cnt_x\times (i-x)$。

斜率优化即可。

最外层循环枚举初始开口。

code：


```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define maxn 1005
using namespace std;
int L,d[maxn],t[maxn],pre[maxn],cnt[maxn];
int head,tail,q[maxn],dp[maxn][10],ans=1e18;
inline double Y(int i,int k){return dp[i][k]-pre[i]+d[i]*cnt[i];}
inline double X(int i){return cnt[i];}
inline double K(int i,int j,int k){return (Y(i,k)-Y(j,k))/(X(i)-X(j)==0?1e-9:X(i)-X(j));}
int n,Kop,r[maxn];
inline void CZS_AK_NOI2085(){
    int noi2085=r[1];
    for(int i=1;i<n;++i)r[i]=r[i+1];r[n]=noi2085;
    return;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>Kop;for(int i=1;i<=n;++i)cin>>r[i];
    for(int i=1;i<=n;++i)d[i]=i-1;reverse(r+1,r+1+n);
    for(int CZS_AK_IOI2085=1;CZS_AK_IOI2085<=n;++CZS_AK_IOI2085){
        cnt[0]=pre[0]=dp[0][1]=0;
        for(int i=1;i<=n;++i){
            cnt[i]=cnt[i-1]+r[i];
            pre[i]=pre[i-1]+cnt[i-1];
            dp[i][1]=dp[i-1][1]+cnt[i-1];
        }
        for(int k=2;k<=Kop;++k){
            head=1;tail=0;
            for(int i=0;i<=n;++i)q[i]=0;
            for(int i=0;i<=n;++i)dp[i][k]=1e18;
            for(int i=1;i<=n;++i){
                while(head<tail&&K(q[tail-1],q[tail],k-1)>=K(q[tail],i-1,k-1))tail--;
                q[++tail]=i-1;
                while(head<tail&&K(q[head],q[head+1],k-1)<=d[i])head++;
                int j=q[head];dp[i][k]=dp[j][k-1]+pre[i]-pre[j]-cnt[j]*(d[i]-d[j]);
            }
        }
        ans=min(ans,dp[n][Kop]);
        CZS_AK_NOI2085();
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：huhangqi (赞：0)

由于环非常难处理，但是这个数据范围又很小，所以很容易想到枚举一个谷仓的位置，然后以这个地点为起始点使用动态规划。

为了使转移方便，我这里选择了逆时针处理这样计算这一段奶牛的路程。

我们定义 $dp_{i,j}$ 表示已经选择了 $i$ 个谷仓，目前最后一个选择的谷仓为 $j$ 时的最少路程。

我们再处理出前缀和以及从第一个点开始奶牛走的总路程，方便我们转移。

最后就可以得到转移方程：

$$$
dp_{i,j}=\min(dp_{i-1,k}+j\times (pre_j-pre_k)-s_j+s_k)
$$$

这样就可以完成暴力部分代码了。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, r[1005], pre[1005], s[1005], ans = 1e16, dp[1005][1005], p[1005], head, tail, x[1005], y[1005];
void solve() {
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + r[i];
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + r[i] * i;
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i - 1][k] + j * (pre[j] - pre[k]) - s[j] + s[k]);
            }
        }
    }
    ans = min(ans, dp[m][n]);
}
signed main() {
    cin >> n >> m;
    for (int i = n; i >= 1; i--) cin >> r[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) r[j] = r[j + 1];
        r[n] = r[0];
        solve();
    }
    cout << ans;
    return 0;
}
``````

考虑如何优化。

首先在原式子中之中 $i$ 这一状态对决策不产生影响，不进行考虑。

此时我们发现可以使用斜率优化。

我们将确定两个变量 $dp_{k}+s_k$ 以及 $pre_k$。

直接维护一个下凸包即可。

代码：

```cpp
/*
dp[j]=min(dp[k]+j*(pre[j]-pre[k])-s[j]+s[k])
x<y,y优
dp[x]-i*pre[x]+s[x]>dp[y]-i*pre[y]+s[y]
dp[x]-dp[y]+s[x]-s[y]>(pre[x]-pre[y])*i
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, r[1005], pre[1005], s[1005], ans = 1e16, dp[1005], p[1005], head, tail, x[1005], y[1005];
bool check(int i, int j, int k) { return (y[i] - y[j]) * (x[j] - x[k]) <= (y[j] - y[k]) * (x[i] - x[j]); }
void solve() {
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + r[i];
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + r[i] * i;
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= m; i++) {
        head = 1, tail = 0;
        p[++tail] = 0;
        for (int j = 1; j <= n; j++) y[j] = dp[j] + s[j], x[j] = pre[j];
        for (int j = 1; j <= n; j++) {
            while (head < tail && y[p[head]] - y[p[head + 1]] > j * (x[p[head]] - x[p[head + 1]])) head++;
            dp[j] = y[p[head]] - x[p[head]] * j + j * pre[j] - s[j];
            while (head < tail && check(j, p[tail], p[tail - 1])) tail--;
            p[++tail] = j;
        }
    }
    ans = min(ans, dp[n]);
}
signed main() {
    cin >> n >> m;
    for (int i = n; i >= 1; i--) cin >> r[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) r[j] = r[j + 1];
        r[n] = r[0];
        solve();
    }
    cout << ans;
    return 0;
}
``````

---

## 作者：qwer6 (赞：0)

首先，看到环，我们第一时间想到拆环成链，看到数据范围中的 $n\le1000$ 就知道这就是为了预留出拆环成链的时间。

那现在的问题就转换成了如何快速求出一个序列的最小值。

这一眼动态规划。

我们定义状态 $dp_{ij,}$ 表示前 $i$ 个谷仓开 $j$ 个门，并且第 $i$ 个谷仓必须开门的最小花费，那么状态转移方程十分容易写出。
$$
dp_{i,k}=\min(dp_{j,k-1}+\sum_{p=j+1}^{i-1}[r_p\times (p-j)])
$$
但是这样的转移显然是 $O(n)$ 的，总时间复杂度为 $O(n^3k)$ 这显然是无法接受的，所以我们考虑优化。

我们把方程拆开。
$$
dp_{i,k}=\min(dp_{j,k-1}-j\times\sum_{p=j+1}^{i-1}r_p+\sum_{p=j+1}^{i-1}p\times r_p)
$$
然后令 $pre_{1,i}=\sum_{p=1}^i r_i\times i$，$pre_{2,i}=\sum_{p=1}^i r_i$，那么式子就写为：
$$
dp_{i,k}=\min(dp_{j,k-1}-(j\times pre_{2,i-1}-j\times pre_{2,j})+pre_{1,i-1}-pre_{1,j})
$$
我们把 $\min$ 符号去掉，然后整理一下式子。
$$
dp_{j,k-1}-pre_{1,j}+j\times pre_{2,j}=dp_{i,k}-pre_{1,i-1}+j\times pre_{2,i-1}
$$
这很显然已经满足斜率优化的模式了，所以我们维护一个下凸包，每个决策点设为 $(j,dp_{j,k-1}-pre_{1,j}+j\times pre_{2,j})$，每次转移求斜率为 $pre_{2,i-1}$ 的切线即可，时间复杂度为 $O(n^2k)$。

```c++
#include<bits/stdc++.h>
#define int long long
#define Nxt puts("")
#define Spa putchar(32)
#define Pline puts("------------------------------")
namespace FastIO{
	inline int read(int &a){
		char c=getchar();
		int f=1;
		a=0;
		while(!isdigit(c)){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(isdigit(c)){
			a=(a<<1)+(a<<3)+(c^48);
			c=getchar();
		}
		return a=a*f;
	}
	inline int read(){
		char c=getchar();
		int f=1,a=0;
		while(!isdigit(c)){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(isdigit(c)){
			a=(a<<1)+(a<<3)+(c^48);
			c=getchar();
		}
		return a*f;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		std::stack<int>st;
		do{
		   st.push(x%10);
		   x/=10;
		}while(x);
		while(!st.empty())putchar(st.top()+'0'),st.pop();
		return ;
	}
	inline void tomax(int &a,int b){
		if(a<b)a=b;
		return ;
	}
	inline void tomin(int &a,int b){
		if(a>b)a=b;
		return ;
	}
}
using namespace FastIO;
using namespace std;
const int N=1005,inf=1e18;
int n,k,tail,head,ans=inf;
int r[N],dp[15][N],pre1[N],pre2[N],x[N],y[N],q[N];
bool check(int s,int mid,int t){
	return (y[mid]-y[s])*(x[t]-x[mid])>=(y[t]-y[mid])*(x[mid]-x[s]);
}
int cal(int i,int j){
	return y[j]-pre2[i-1]*x[j]+pre1[i-1];
}
void DP(bool opt=0){
	memset(dp,0x3f,sizeof(dp));
	dp[1][1]=0;
	for(int t=2;t<=k+1;t++){
		tail=0,head=1;
		for(int i=t;i<=n+1;i++){
			x[i-1]=i-1,y[i-1]=dp[t-1][i-1]-pre1[i-1]+(i-1)*pre2[i-1];
			while(head<tail&&check(q[tail-1],q[tail],i-1))tail--;
			q[++tail]=i-1;
			while(head<tail&&cal(i,q[head])>cal(i,q[head+1]))head++;
			dp[t][i]=cal(i,q[head]);
		}
	}
	tomin(ans,dp[k+1][n+1]);
}
void move(){
	for(int i=n;i>=1;i--)swap(r[i+1],r[i]);
	r[1]=r[n+1];
	for(int i=1;i<=n;i++){
		pre1[i]=pre1[i-1]+r[i]*i;
		pre2[i]=pre2[i-1]+r[i];
	}
}
signed main(){
	read(n),read(k);
	for(int i=1;i<=n;i++)read(r[i]);
	for(int i=1;i<=n;i++){
		move();
		DP();
	}
	write(ans);
}
```

---

