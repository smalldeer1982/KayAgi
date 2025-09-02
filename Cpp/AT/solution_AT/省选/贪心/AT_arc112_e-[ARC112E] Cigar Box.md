# [ARC112E] Cigar Box

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc112/tasks/arc112_e

数列 $ (1,2,\dots,n) $ に対して、以下の操作をちょうど $ m $ 回繰り返したところ、$ (a_1,\dots\ ,a_n) $ になりました。

- 項を $ 1 $ つ選んで消す。その後、消した項を数列の先頭か末尾に付け加える。

$ m $ 回の操作列としてありうるものの数を $ 998244353 $ で割ったあまりを求めてください。

ただし、$ 2 $ つの操作列が同じであるとは、「どの操作についても、選んだ項と付け加えた位置がどちらも等しいこと」とします。

## 说明/提示

### 制約

- $ 2\le\ n\ \le\ 3000 $
- $ 1\le\ m\ \le\ 3000 $
- $ a_1,\dots\ ,a_n $ は $ 1,\dots,n $ の順列

### Sample Explanation 1

以下の $ 5 $ 通りの操作列がありえます。 - $ 1 $ を消して先頭に付け加える。数列は $ (1,2,3,4,5) $ となる。その後、$ 3 $ を消して末尾に付け加える。数列は $ (1,2,4,5,3) $ となる。 - $ 3 $ を消して先頭に付け加える。数列は $ (3,1,2,4,5) $ となる。その後、$ 3 $ を消して末尾に付け加える。数列は $ (1,2,4,5,3) $ となる。 - $ 3 $ を消して末尾に付け加える。数列は $ (1,2,4,5,3) $ となる。その後、$ 1 $ を消して先頭に付け加える。数列は $ (1,2,4,5,3) $ となる。 - $ 3 $ を消して末尾に付け加える。数列は $ (1,2,4,5,3) $ となる。その後、$ 3 $ を消して末尾に付け加える。数列は $ (1,2,4,5,3) $ となる。 - $ 5 $ を消して末尾に付け加える。数列は $ (1,2,3,4,5) $ となる。その後、$ 3 $ を消して末尾に付け加える。数列は $ (1,2,4,5,3) $ となる。

### Sample Explanation 2

$ 4 $ 種類の操作のうち、$ 2 $ 種類では数列が全く変わらず、もう $ 2 $ 種類では $ 2 $ 項が入れ替わります。 このことから、全ての操作列のうち半分である $ 4^m/2\ =\ 2^{31}\ =\ 2147483648 $ が求める操作列の数であることが示せます。 よって、$ 2147483648 $ を $ 998244353 $ で割ったあまりである $ 150994942 $ が答えです。

## 样例 #1

### 输入

```
5 2
1 2 4 5 3```

### 输出

```
5```

## 样例 #2

### 输入

```
2 16
1 2```

### 输出

```
150994942```

## 样例 #3

### 输入

```
10 3000
3 7 10 1 9 5 4 8 6 2```

### 输出

```
129989699```

# 题解

## 作者：天命之路 (赞：14)

### ARC112E

是一道对题目性质分析比较透彻的 dp 题。

一个数的位置，至于其最后一次操作有关，所以我们把研究对象从操作转到了数，这样才能进一步分析。

我们称每个数的最后一次操作为“有效操作”。

那么假设有 $L$ 个有效操作把数放在开头，有 $R$ 个有效操作把数放在结尾，那么 $a_{L+1},\dots,a_{n-R}$ 这一段的相对位置是一直没有改变的，因为它们没有进行过任何操作，所以，$a_{L+1},\dots,a_{n-R}$ 必须是递增的。



接下来我们要针对操作计数。

如果有了上面这个观察，就可以设出状态 $dp[i][l][r]$ 表示进行了 $i$ 次操作（有效+无效），$l,r$ 意义同上。转移如下：

```cpp
dp[i + 1][l][r] += dp[i][l][r] * 2 * (l + r) // 无效操作，放在任意一次有效操作的前面。
dp[i + 1][l + 1][r] += dp[i][l][r] //有效操作
dp[i + 1][l][r + 1] += dp[i][l][r] //有效操作
```

这个 dp 在时间线上是反向的，即从后向前填充操作序列，可见**倒流**的思想不仅能应用于数据结构，还能用于 dp。



我们发现 dp 转移过程中只用到了 $l + r$，所以有个想法是直接记录 $dp[i][l + r]$，最后再来分配这 $l  + r$ 次有效操作。

于是可以写出 $dp2[i][j]$ ，其中 $j = l + r$。

而原来的 $dp[i][l][r]$ 则是现在的 $dp2[i][l + r] \times \binom{l + r}{l}$，我们用组合数规定这 $l + r$ 次有效操作的顺序。

然后对于满足条件的 $l,r$ 统计即可。



本题的关键在于观察到“有效操作”的特殊性，以及根据有效操作的特点设计倒流式的 dp，这种“有效操作”其实跟普通的赋值具有很相近的特点，故思想也是相似的。最后一步的优化也非常好，是对转移方程的观察与思考。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e3 + 5,P = 998244353;
int fac[N],ifac[N];
int dp[N][N],n,m,a[N];
inline void init(int n)
{
	fac[0] = 1;
	for(int i = 1;i <= n;i++) fac[i] = 1ll * fac[i - 1] * i % P;
	ifac[1] = 1;
	for(int i = 2;i <= n;i++) ifac[i] = 1ll * (P - P / i) * ifac[P % i] % P;
	ifac[0] = 1;
	for(int i = 1;i <= n;i++) ifac[i] = 1ll * ifac[i - 1] * ifac[i] % P;
}
inline int C(int n,int m) { return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P;}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	dp[0][0] = 1;
	for(int i = 0;i < m;i++)
		for(int j = 0;j <= n;j++)
			(dp[i + 1][j] += 2ll * dp[i][j] * j % P) %= P,
			(dp[i + 1][j + 1] += dp[i][j]) %= P;
	init(n);
	int ans = 0;
	for(int l = 0;l <= n;l++)
		for(int r = n - l;r >= 0;r--)
			if (n - l - r >= 2 && a[n - r - 1] > a[n - r])
       			 break;
       		else (ans += 1ll * C(l + r,l) * dp[m][l + r] % P) %= P;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：xcyyyyyy (赞：6)

个人觉得这才是漂亮的做法。

考虑每一种颜色的最后一次操作，显然前面有关这个颜色的其他任何操作都没有用。

接着我们考虑，假设最后向左的有 $L$ 个，最后向右的有 $R$ 个，那么中间的一定是一个升序。

那么题目给的 $a_i$ 的作用就到此为止了，我们考虑快速计算这个方案数从而达到 $O(n^2)$ 的时间复杂度。

首先有 $m$ 个不同的操作，将他们所对应的操作归类，一共有 $L+R$ 个类（此时只是分类，没有确定具体的颜色和左右)，那么方案数是 $m \brace L+R$，然后有 $m-L-R$ 个颜色是无效操作，方案数是 $2^{m-L-R}$，最后考虑具体是哪个颜色，方案数是 $\binom{L+R}{L}$。

```cpp
#include<cstdio>
using namespace std;
#define N 3005
#define p 998244353
#define ll long long
int n,m;
int a[N],ok[N][N];
ll S[N][N],C[N][N],mi[N];
int main(){
    S[0][0]=C[0][0]=mi[0]=1;
    for(int i=1;i<=3000;i++){
        C[i][0]=1;
        mi[i]=(mi[i-1]+mi[i-1])%p;
        for(int j=1;j<=i;j++)
            S[i][j]=(S[i-1][j-1]+j*S[i-1][j]%p)%p,
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
    }
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    ll ans=0;
    for(int l=1;l<=n+1;l++){
        for(int r=l-1;r<=n&&(r<=l||a[r]>a[r-1]);r++){
            int L=l-1,R=n-r;
            if(L+R<=m){
                ans=(ans+S[m][L+R]*C[L+R][L]%p*mi[m-L-R]%p)%p;
            }
        }
    }printf("%lld",ans);
}

```

---

## 作者：demonlover923 (赞：5)

注意到只有最后一个操作是有用的, 同时注意到, 最终的序列一定是这样的形式, 可以分成三部分, 左边一部分放是最终操作移动到左边的数, 右边一部分是最终操作移动到右边的数, 中间是从来没有被移动过的数, 并且中间部分是单调递增的.

这时我们可以 $\mathcal{O}(n^2)$ 的枚举左边和右边的个数 $L$ , $R$ , 并且期望快速计算这种情况下移动的方案数.

这相当于我们给 $m$ 个元素上颜色, 颜色为 $1\sim L+R$ , 并且每种颜色都要有, 相当于我们把 $m$ 个球放进 $L+R$ 个无标号的盒子中, 并令盒子的编号为盒子中的序号最大的球的序号, 并给盒子排序, 这样即可一一对应一种移动方案, 同时我们需要钦定这 $L+R$ 个颜色哪些左移哪些右移, 并且我们只需要最后一个操作是我们钦定的方向即可, 之前的颜色相同的可以任意方向, 所以一个局面的移动方案即为
$$
\begin{Bmatrix}m\\L+R\end{Bmatrix}\binom{L+R}{L}2^{m-L-R}
$$

时间复杂度 $\mathcal{O}(n^2)$ .

```cpp
/************************************************
*Author        :  demonlover
*Created Time  :  2022.09.25.21:15
*Problem       :  ARC112E
************************************************/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair <int,int> pii;
template <typename T>
inline bool read(T &x) {
	int f = 1,c = getchar();x = 0;
	while (!isdigit(c)) {if (c == 45)f = -1;c = getchar();}
	while (isdigit(c))x = (x<<3)+(x<<1)+(c^48),c = getchar();
	return x *= f,true;
}
template <typename T,typename... Args>
inline bool read(T &x,Args &...args) {
	return read(x) && read(args...);
}

namespace run {
	const int maxn = 3e3+10;
	const int mod = 998244353;
	int a[maxn],s[maxn][maxn],c[maxn][maxn],bin[maxn];
	int n,m,ans;
	inline bool main() {
		read(n,m);
		for (int i = 1;i <= n;++i)read(a[i]);
		for (int i = 0;i <= m;++i) {
			c[i][0] = 1;s[i][0] = (i == 0);
			for (int j = 1;j <= i;++j)c[i][j] = (c[i-1][j]+c[i-1][j-1])%mod,s[i][j] = (s[i-1][j-1]+1ll*j*s[i-1][j]%mod)%mod;
		}
		for (int i = (bin[0] = 1);i <= m;++i)bin[i] = 1ll*bin[i-1]*2%mod;
		for (int l = 1;l <= n+1;++l)
			for (int r = l-1;r <= n;++r) {
				if (r > l && a[r] < a[r-1])break;
				int L = l-1,R = n-r;
				if (m >= L+R)ans = (ans+1ll*s[m][L+R]*c[L+R][L]%mod*bin[m-(L+R)]%mod)%mod;
			}
		printf("%d\n",ans);
		return 0;
	}
}

int main() {
#ifdef demonlover
	freopen("ARC112E.in","r",stdin);
	freopen("ARC112E.out","w",stdout);
#endif
	return run :: main();
}

```

---

## 作者：max67 (赞：4)

## 前言

~~一看到没有题解贺就浑身难受。~~

## 正解

（下面说的数 $i$ 一般指的是值为 $i$ 的数）

首先，凭直觉知道，一般这种求方案数的题目都是和 dp 有关。

然后，若直接 dp，没有目的地乱选，也就是说在操作一些数后，我们无法有效记录当前的状态——因为我们不知道序列的形状，我们觉得整个序列都有必要记录。因此肯定是按照一定规律进行移动。

经过手摸之后，我们发现对于一个值为 $i$ 的数，固定他最后一次操作的时间和位置（放在开头或者结尾）后，所有在这个时间之前的对这个数的操作都不会影响这个数的最终位置。因为对于在这个时间之前的所有操作，都不会改变其他数的相对位置和操作，只有最后一个操作会影响这个数的位置。

因此对于一个数，我们只关心他的最后一次操作的时间以及移动到开头还是结尾。依此，我们把所有数分成两类：被操作过和未被操作过。

我们先考虑未被操作过的数。发现若在序列上 $(1,2\dots n)$ 上固定了两个未被操作过的数（设为 $l$ 和 $r$），那么对于子区间 $[l,r]$ ，每次操作只可能会从这个区间中取一个数往外放，已经放在外面的数不可能再放进来。即：若假设这两个数在序列 $(a_1\dots a_n)$ 中的位置为 $p_l$ 和 $p_r$，那么 $\forall i\in [p_l,p_r]$，$a_i \in [l,r]$ 并且一定不会被操作。因为 $l$ 和 $r$ 已经固定，不可能往里填数，因此若 $a_i$ 一开始不在 $[l,r]$ 内就无法再移进来。若在 $[l,r]$ 内则一操作就会移动出去，不能移动。

然后大力不断归纳可以看出，未被操作的数在 $(a_1\dots a_n)$ 上的位置是一段连续的区间，并且满足值随着位置增加而增加。因此我们先考虑暴力 $O(n^2)$ 枚举这个区间 （设为 $[l,r]$）。

做完这个后，我们再来考虑已经被操作过的数。我们先只考虑有效操作，因为每个数只有一次有效操作，那么对于 $(a_1\dots a_{l-1})$，我们肯定是先放 $a_{l-1}$，再放 $a_{l-2}\dots $ 依此类推。也就是说我们对于放在开头的有效操作来说，放数的相对顺序是固定的。又因为他可以任意选择一个数放，因此对于我们重要的状态只有：

* 操作了几次

* 在开头已经有几次有效操作，在结尾已经有几次有效操作。

注意我们正着做无法判断当前的操作是不是有效操作，因此我们考虑按照操作顺序倒着做。

我们设 $dp[i][l][r]$ 表示后 $i$ 次操作中，开头有 $l$ 次有效操作，结尾有 $r$ 次有效操作的方案数。转移为：

* 当前这个操作是有效操作，可以选择放到开头或者结尾：$dp[i][l][r] \longrightarrow dp[i+1][l+1][r],dp[i+1][l][r+1] $ 

* 当前这个操作是无效操作，必须选择已经操作过有效操作的数，每次可以选择放到开头或者结尾：$dp[i][j][k] \stackrel{2\times (j+k)}\longrightarrow dp[i+1][j][k]$

然而这样 $dp$ 时间复杂度是 $O(n^3)$ 的，考虑优化。

我们发现 $dp$ 的转移系数为 $1$ 或者 $j+k$ ——与单独 $j$ 或 $k$ 的取值无关。这样启示我们把 $j,k$ 两维缩成一维。但怎么缩呢？

我们考虑我们为什么能压缩：按照通用套路，我们把 $dp$ 转移建成拓扑图：对每个状态 $dp[i][j][k]$ 建一个点 $(i,j,k)$。若两个点之间有转移，那么连一条有向边，边权为转移系数。我们定义一条路径的贡献为这条路径上的边权积。那么 $dp[i][j][k]$ 就为：从点 $(0,0,0)$ 到点 $(i,j,k)$ 的所有路径的贡献和。

三维的 $dp$ 转移就是把所有到 $(i,j,k)$ 点的路径缩成一个状态进行转移。因为有很多不同的边的边权相同，我们换一个角度：考虑有多少条路径依次经过的每条边权相
同，我们把它缩成一条路径考虑。

我们新创建一个拓扑图，对于每个状态 $(i,sum)$，我们创建一个点。然后我们对 $(i,sum)$ 向 $(i,sum+1)$ 连一条权值为 $1$ 的边，再对 $(i,sum)$  向 $(i+1,sum)$ 连一条权值为 $sum$ 的边。容易发现原图中的每条路径都可以映射在这个新图的一条路径上。

那么对于一个原图状态 $dp[i][j][k]$，与新图状态 $(i,j+k)$ 中的每条路径的贡献乘上相同的路径数量的和相等。分别对于每个路径考虑在原图中相等的路径数量。我们考虑对于新图的一条路径对应到原图，能够对应多少条合法的路径。

对于这条路径的每条边，我们把它拆分成往左走（$(i,j) \rightarrow (i+1,j)$） 和向上走（$(i,j) \rightarrow (i,j+1)$ ）。对于往左走的边，由于只改变了 $i$ 的取值，与我们缩的两维无关，因此并不会影响到路径的数量。对于向上走的边，在原图中每次能使 $j$ 或者 $k$ 自增 $1$。而显然在 $dp[i][j][k]$ 中 $j,k$ 的取值是固定的。也就是合法的路径数量为：我们对于每一条向上走的边，我们能使 $j$ 或 $k$ 自增 $1$，最终使得 $j$ 和 $k$ 为某一固定值的方案数。这显然是一个轻松的组合数问题。若最终状态为 $j=a,k=b$，那么方案数为 $C_{a+b}^{a}$。

而对于新图中的每条路径，由于向上走的边数相同，因此方案数也相同。那么可以把这个看做系数提出来。

那么对于新图中的状态 $(j,k)$ ，设 $f[j][k]$ 为从 $(0,0)$ 到 $(j,k)$ 的路径权值和。那么有： $dp[i][j][k]=C_{j+k}^{k}f[j][k]$。

~~好像说复杂了。。。~~

然后 $f$ 数组的转移是 $O(n^2)$ 的：

* $f[i][j] \rightarrow f[i][j+1]$

* $f[i][j] \stackrel{2\times j}\rightarrow f[i+1][j]$

那么总的复杂度就是：$O(n^2)$

## 代码


~~不会吧，不会吧，不会真的有人连只有 $30$ 行的代码都要贺吧。咦？是我，那没事了。~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3010,mod=998244353;
int n,m;
int a[N];
int f[N][N<<1],c[N][N];
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=0;i<=m;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}
	f[0][0]=1;
	for(int i=1;i<=m;i++)
		for(int j=0;j<=n;j++)
		{
			if(j)f[i][j]=f[i-1][j-1];
			f[i][j]=(f[i][j]+f[i-1][j]*2*j)%mod;
		}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)	
		{
			ans=(ans+f[m][i-1+n-j]*c[i-1+n-j][i-1])%mod;
			if(a[j]>a[j+1])break;
		}
	for(int i=0;i<=n;i++)ans=(ans+f[m][n]*c[n][i])%mod;
	printf("%lld\n",ans);
	return 0;
}
```

## 后记

整个题目缩点最妙的还是把三维缩成两维。考场上能感性猜一个系数，但赛后还是这样~~可能应该也许~~理解为自然一点。

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc112_e)

**题目大意**

> 给定序列 $x_1\sim x_n$，初始 $x_i=i$，每次操作可以把其中一个元素放到开头或末尾，求有多少种长度为 $m$ 的操作序列能够使得最终 $x_i=a_i$。
>
> 数据范围：$n,m\le 3000$。

**思路分析**

显然一个数如果被操作多次，只有最后一次有用。

那么每个元素有三种情况：最后一次在放在开头，最后一次放到末尾，未操作过。

前两种操作对应 $a$ 的前缀后缀，中间剩余的元素必须是升序的。

假设前缀有 $x$ 个元素，后缀有 $y$ 个元素，计数时先给每个操作划分到元素中，非最后一次的操作可以选方向，前缀操作和后缀操作内部有序，总的方案数就是：
$$
2^{m-x-y}\binom{x+y}x\begin{Bmatrix}m\\x+y\end{Bmatrix}
$$
预处理后直接 $\mathcal O(1)$ 计算。

时间复杂度 $\mathcal O(n^2+m^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3005,MOD=998244353;
int n,a[MAXN],m;
ll S[MAXN][MAXN],C[MAXN][MAXN],pw[MAXN],ans=0;
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	S[0][0]=1;
	for(int i=1;i<=m;++i) for(int j=1;j<=i;++j) S[i][j]=(S[i-1][j]*j+S[i-1][j-1])%MOD;
	for(int i=0;i<=m;++i) for(int j=C[i][0]=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
	for(int i=pw[0]=1;i<=m;++i) pw[i]=pw[i-1]*2%MOD;
	for(int i=0;i<=n;++i) {
		for(int j=i+1;j<=n+1;++j) {
			if(j-i-1>=2&&a[j-2]>a[j-1]) break;
			int l=i,r=n+1-j;
			if(l+r<=m) ans=(ans+S[m][l+r]*pw[m-l-r]%MOD*C[l+r][l])%MOD;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：hexu2010 (赞：2)

# AT_arc112_e E - Cigar Box 题解

## 题目大意

给定 $1\sim n$ 的排列 $P$，并给定 $m$，要求在 $m$ 次操作以内将排列 $P$ 还原为 $1\sim n$ 的升序排列（即 $1,2,\cdots,n$）。

一次操作是指：将排列中的任意一个数移到第一个或移到最后一个。

+ $2\leqslant n\leqslant 3000$
+ $1\leqslant m\leqslant 3000$

## 分析

动态规划。

首先有一条性质，就是说对于一个数 $x$ 的所有操作中，只有最后一个操作才是有效的，其他操作对于还原都是无效的。显然，任意一个数有且仅有一个与它对应的有效操作。

假设操作序列 $M$ 能使得题目给定的排列还原，就可以设 $f_{i,j}$ 表示满足序列的**后** $i$ 项中有 $j$ 个有效操作的序列数。假设$[$操作 $M_i$ 是有效的$]^{(1)}$，那么方案数就是 $f_{i-1,j-1}$；如果操作 $M_i$ 是无效的，那么方案数是 $f_{i-1,j}$，但又因为还要考虑这个操作和哪一个操作冲突了（后面哪一个操作移动了这个数），所以还要乘 $(i-1)$。所以，可以得出转移方程 $f_{i,j}=f_{i-1,j-1}+(i-1)f_{i-1,j}$。

最后，统计答案。注意这个转移方程的前提。显然的，在大多数状态下会有一些数没有被操作过。这些数没被操作过到最后依然能够形成 $1\sim n$ 的排列，说明这些数是连续的区间，并且单调递增。可以枚举区间 $[l,r]$，只要区间 $[l,r]$ 满足 $a_l\sim a_r$ 递增就可以将 $f_{l,r}$ 累加到答案中。累加的时候还需考虑操作是移到最前面还是移到最后面。可以用组合数 $C_{i-1+n-j}^{i-1}$ 解决。当然，还要考虑$[$没有递增序列但依然合法的情况$]^{(2)}$。这种情况说明所有操作都有效，那么只需要看操作是移到前面还是移到后面，$[$共 $2^n$ 种情况$]^{(3)}$。

## 注记

这里的注记是给看不懂此题解的同学们看的。

+ $(1)$：“操作有效”的含义就是说这个操作移动的数在后面没有被移动过。由于设计的状态 $f_{i,j}$ 与后 $i$ 项相关，所以 $M_{i+1}\sim M_{m}$ 中没有操作所移动的数跟 $M_i$ 移动的数相等。
+ $(2)$：也就是说所有的数都被移动过了，所以没有递增序列。
+ $(3)$：每个数对应的有效操作有可能是将某个数移至最前面，也有可能是移至最后面，共 $n$ 个数，所以有 $2^n$ 种方法。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	for(; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
	for(; ch >= '0' && ch <= '9'; s = 10 * s + ch - '0', ch = getchar());
	return s * w;
}
const int MAXN = 3005;
const int MOD = 998244353;
int n, m, a[MAXN], f[MAXN][MAXN], C[MAXN][MAXN << 1];
signed main(){
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++){
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; j++){
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
	}
	f[0][0] = 1;
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++){
			f[i][j] = (f[i - 1][j - 1] + f[i - 1][j] * 2 * j % MOD) % MOD;
		}
	}
	int res = 0;
	for(int i = 1; i <= n; i++){
		bool flag = false;
		for(int j = i; j <= n; j++){
			if(j > i && a[j] < a[j - 1]) flag = true;
			if(flag) break;
			res = (res + f[m][i - 1 + n - j] * C[i - 1 + n - j][i - 1]) % MOD;
		}
	}
	for(int i = 0; i <= n; i++){
		res = (res + f[m][n] * C[n][i] % MOD) % MOD;
	}
	cout << res << endl;
	return 0;
}
```

---

## 作者：freoepn (赞：1)

可以发现序列的最终状态之和对每个数进行的最后一个操作有关，所以可以把序列分成三个部分，最后一次操作提到开头的部分，最后一次操作提到末尾的，没有做过操作的，提到开头的在最后序列中一定是一段前缀，提到末尾的一定是一段后缀，没做过操作的在这两端之间，且一定单调递增。可以在最终序列中枚举前缀后缀，设前缀有 $l$ 个元素，后缀有 $r$ 个元素，只要满足中间部分单调递增且 $l + r \leq m$ 就一定合法。考虑确定前缀后缀后怎么计算方案，把 $m$ 次操作打包成 $l+r$ 份，且每一份都不能为空，这是一个第二类斯特林数（不会的可以点[这里](https://oi-wiki.org/math/combinatorics/stirling/)），也就是 $m \brace l+r$,打包后分配每个包中最后的操作是往前还是往后，一定正好 $l$ 个向前 $r$ 个向后，因为确定了往前往后的包后每个包都会按最后操作的向后固定被分配，所以不用考虑包的分配，方案数就是 $l+r\choose l$，不是每个包最后的操作可以随便分前后，有 $2^{m-l-r}$ 种方案，所以方案数就是 $m \brace {l+r} $ $l+r\choose l$ $2^{m-l-r}$，枚举所有可能的前缀后缀计算总和即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int kMaxN = 3005, mod = 998244353;
int n, m;
int a[kMaxN], fac[kMaxN], ifac[kMaxN], fpow[kMaxN];
int f[kMaxN][kMaxN];
int qpow(int x, int y) {
  int ans = 1, p = x;
  while (y) {
    if (y& 1) {
      ans = (ans * p) % mod;
    }
    p = (p * p) % mod;
    y >>= 1;
  }
  return ans;
}
int C(int x, int y) {
  return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  fac[0] = fpow[0]= ifac[0] = 1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  a[0] = 1e9;
  for (int i = 1; i < kMaxN; i++) {
    fac[i] = (i * fac[i - 1]) % mod;
    ifac[i] = qpow(fac[i], mod - 2);
    fpow[i] = (2 * fpow[i - 1]) % mod;
  }
  f[0][0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    for (int j = 1; j <= i; j++) {
      f[i][j] = (f[i - 1][j] * j + f[i - 1][j - 1]) % mod;
    }
  }
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    for (int j = i + 1, p = 0; j <= n + 1 && p < a[j - 1]; p = (j - 1 != i ? a[j - 1] : 0),j++ ) {
      if (m >= i + (n - j + 1)) {
        ans = (ans + fpow[m - i - (n - j + 1)] * C(i + (n - j + 1), i) % mod * f[m][i + (n - j + 1)])%mod;
        }
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：Cx114514 (赞：1)

### 题目链接：[[ARC112E] Cigar Box ](https://www.luogu.com.cn/problem/AT_arc112_e)   

非常有思维难度的一道题。

考虑在操作时，被修改位置的数字一定会换到整个序列的最前面或最后面。那么，在若干次操作后，整个序列一定形如：**一段被放到前面的数字** $+$ **一段没有修改过的数字** $+$ **一段被放到后面的数字**。对于中间一段没有修改过的数字，一定是单调递增的。

当一个数字被修改位置若干次时，只有最后一次会对最终序列造成影响，之前怎么放都是无所谓的。

我们不妨设 $f_{i,l,r}$ 表示在进行了 $i$ 次操作后，放到前面的数字有 $l$ 个，放到后面的数字有 $r$ 个的方案数。

考虑倒序dp，我们对一个数进行操作。当此次操作对最终序列造成影响时，受给出的目标序列限制，该数是唯一的。若此次操作对最终序列不造成影响，则该数可以是在它之后进行操作中的任意一个数，故转移为：

$f_{i,l,r} = f_{i-1,l-1,r}+f_{i-1,l,r-1}+2 \times \left ( l+r \right ) \times f_{i-1,l,r}$

此时的复杂度为 $O\left ( n^{2}m\right )$, 无法通过此题，考虑进行优化。

对于每个状态，设 $k=l+r$。不难发现，每个和为 $k$ 的状态都由和为 $k$ 与 $k-1$ 的状态转移得来。

不妨设 $dp_{i,j}$ 表示在进行了 $i$ 次操作后，放到前面和放到后面的数字和为 $j$ 个的方案数，有转移如下：

$dp_{i,j}=dp_{i-1,j-1}+2\times j \times dp_{i-1,j}$

对于一种情况，放在前面的数的个数为 $l$，放在后面的数的个数为 $r$，其最终答案为 $dp_{m,l+r} \times  \binom{l+r}{l} $，其中组合数为它们操作的顺序个数。

枚举所有可能作为中间没有修改过的连续段的情况，计算它们的答案之和，即为最终答案，时间复杂度 $O\left ( nm\right )$，可以通过本题。

下面是代码部分：

```cpp
//该代码并未预处理组合数，时间复杂度为O(nmlogn)。预处理复杂度可以做到O(nm)。
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;

int n, m, ans, a[3005], f[3005][3005], fac[3005];

int Qpow(int t, int p)
{
	int Ans = 1;
	while (p)
	{
		if (p & 1) Ans = (Ans * t) % mod;
		t = (t * t) % mod;
		p /= 2;
	}
	return Ans;
}

int C(int x, int y)
{
	return (fac[y] * Qpow(fac[y - x], mod - 2) % mod) * Qpow(fac[x], mod - 2) % mod;
}

signed main()
{
	cin >> n >> m;
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = (fac[i - 1] * i) % mod;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	f[0][0] = 1;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			f[i][j] = (f[i - 1][j - 1] + f[i - 1][j] * j * 2) % mod;
	for (int i = 1; i <= n; i++)
	{
		ans = (ans + f[m][n - 1] * C(i - 1, n - 1)) % mod;
		for (int j = i + 1; j <= n; j++)
			if (a[j] < a[j - 1]) break;
			else ans = (ans + f[m][i + n - j - 1] * C(i - 1, i + n - j - 1)) % mod;
	}
	for (int i = 0; i <= n; i++)
		ans = (ans + f[m][n] * C(i, n)) % mod;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

考虑我们做的最后一次操作是什么。

显然必须是把**左端点的数放到正确的位置上或者右端点的数放到正确的位置上**，不妨设是左端点。

那么我们可以将问题转化为**只考虑 $a_{2,3,\cdots,n}$ 这些数的相对位置关系**，因为 $a_1$ 在哪并不重要，它可以随便移动，只要最后一次归位即可。

因此设 $dp_{l,r,k}$ 表示用 $k$ 次操作，将 $a_{l,l+1,\cdots,r}$ 从递增顺序变为 $a$ 的方案数。

这样容易得到 $O(n^2 m)$ 的做法，考虑优化。

最终必定是在某个 $dp_{l,r,0}$ 处产生有效贡献，这等价于 $a_l < a_{l+1} < a_{l+2} < \cdots < a_r$。

假设我们选定的区间是 $(l,r)$，则我们要在 $m$ 次操作中扔掉 $l-1+n-r$ 个数。假设固定了他们扔掉的顺序，我们很容易用 $f_{n,m}$ 记录其方案数。而扔掉的顺序有 $\dbinom{n-1+l-r}{l-1}$ 种，所以可以直接计算。

复杂度 $O(n^2+nm)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10,MOD=998244353; 
int n,m,a[MAXN],C[MAXN][MAXN],dp[MAXN][MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>a[i];
	ffor(i,0,n) {C[i][0]=1;ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;}
	dp[0][0]=1;
	ffor(i,1,m) ffor(j,1,n) dp[i][j]=(dp[i-1][j]*j*2+dp[i-1][j-1])%MOD;
	int ans=0;
	ffor(i,0,n) ans=(ans+dp[m][n]*C[n][i])%MOD;
	ffor(l,1,n) {
		ffor(r,l,n) {
			if(r!=l&&a[r]<a[r-1]) break ;
			ans=(ans+dp[m][n-(r-l+1)]*C[n-(r-l+1)][l-1])%MOD;
		}	
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：happybob (赞：0)

题意：

有一个长度为 $n$ 的排列，初始有 $p_i=i$。给定 $m$ 和另一个排列 $h_1,h_2,\cdots,h_n$。你要进行恰好 $m$ 次操作，每次操作选择 $i$，然后将 $p_i$ 移动到排列左侧或右侧。最终你需要使得 $p=h$。你要求这样的操作方案数，对 $998244353$ 取模。

$2 \leq n \leq 3000$，$1 \leq m \leq 3000$。

解法：

操作不容易刻画，考虑每个元素最终的结果。

容易发现每个数要么没操作过，要么只和其最后一次操作的位置与方向有关。

所以整个原排列可以被分为三部分，分别是最后一次操作放到前面与后面，以及没有被操作过的。

容易发现最后一次操作放到前面的那些数在 $a$ 中对应一个前缀，放到后面的对应一个后缀，没被操作的按照原顺序插入前缀和后缀之间。

故枚举前缀 $[1,i]$ 与后缀 $[j,n]$，考虑此时的贡献。对于 $m$ 次操作按照操作的数分类，有 $m \brace i+j$ 种方式，然后考虑 $i+j$ 种中选 $i$ 种作为前缀，有 $\dbinom{i+j}{i}$，最后乘以 $2^{m-x-y}$ 表示不是最后一次操作的方向任意。对所有 $i,j$ 求和即可。

[Submission Link.](https://atcoder.jp/contests/arc112/submissions/60493667)

---

## 作者：shinkuu (赞：0)

唐龙题不知道为什么有 2600。此处应有[对称唐龙.gif]。

首先，把 $a_i=i$ 的序列 $a$ 变成给定序列显然是难做的，考虑将目标序列进行某种映射，转化成将 $a$ 变成 $a_i=i$。

然后发现，对于每个数字，只有对其的最后一次操作是有用的，并且进行放到开头的操作的数字一定是某个 $[1,i]$ 内的所有数，并且依次进行 $i,i-1,i-2,\cdots,1$ 的操作。放到末尾的同理。

于是考虑倒推每次操作，就变成了依次对 $1,2,\cdots,x$ 操作。并且对 $i$ 进行操作后，以后可以任意对 $i$ 操作。

则可以进行 dp：设 $dp_{i,j,k}$ 表示当前到第 $i$ 次操作，已经进行过放到第一的操作的为 $[1,j]$，进行过放到末尾的为 $[k,n]$ 的方案数。则转移为：$dp_{i,j,k}=dp_{i-1,j-1,k}+dp_{i-1,j,k+1}+(j+n-k+1)dp_{i-1,j,k}$。而对于没有进行过操作的数，它们之间的相对位置不变，则检查它们的相对位置是否符合条件即可。

这是 $O(n^3)$ 的。考虑优化状态。发现 $j$ 和 $k$ 无关，于是考虑记录 $[1,j]$ 和 $[k,n]$ 这些一共选了多少个，最后在乘上 $\binom{j+n-k+1}{j}$。状态为 $dp_{i,j}$ 表示前 $i$ 次操作，已经进行过操作的位置有 $j$ 个，则有转移：$dp_{i,j}=dp_{i-1,j-1}+2jdp_{i-1,j}$。

最后枚举 $j,k$，判断 $[j+1,k-1]$ 是否符合条件，再乘上上述组合数，全部情况相加即可。时间复杂度 $O(n^2)$。

code：

```cpp
int n,m,a[N],p[N],dp[N][N],C[N][N];
bool pd[N][N];
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
void Yorushika(){
	read(n,m);
	rep(i,1,n){
		read(p[i]);
		a[p[i]]=i;
	}
	dp[0][0]=1;
	rep(i,1,m){
		rep(j,1,n){
			dp[i][j]=Mod(dp[i-1][j-1],2ll*dp[i-1][j]*j%mod);
		}
	}
	pd[1][0]=1;
	rep(i,1,n){
		pd[i][i]=pd[i+1][i]=1;
		rep(j,i+1,n){
			if(p[j]<p[j-1]){
				break;
			}
			pd[i][j]=1;
		}
	}
	C[0][0]=1;
	rep(i,1,n){
		C[i][0]=C[i][i]=1;
		rep(j,1,i-1){
			C[i][j]=Mod(C[i-1][j],C[i-1][j-1]);
		}
	}
	int ans=0;
	rep(i,0,n){
		rep(j,i+1,n+1){
			if(!pd[i+1][j-1]){
				continue;
			}
			ans=Mod(ans,1ll*dp[m][i+n-j+1]*C[i+n-j+1][i]%mod);
		}
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：cqbzlzm (赞：0)

### Description

一个 1 到 $n$ 的数列，进行恰好 $m$ 次操作，每次操作可以将一个数移动到开头或结尾。最后得到了数列 $a$。问有多少种操作方案。

**数据范围：**$1\leq n,m\leq 3000$。

### Solution

首先，我们发现对于一个数而言，只要搞清楚它最后一次操作的时间和类型就能判断出它最终的位置。我们设这样的所谓**最后一次操作**为**有效操作**。

我们假设有 $L$ 个移向开头的有效操作，有 $R$ 个移向结尾的有效操作。那么，在最后的序列 $a$ 中，$a$ 的 $L+1$ 到 $n-R$ 没有被操作过，即保持了原来的相对顺序。我们称这样的 $(L,R)$ 是合法的。

我们又发现对于每一个合法的 $(L,R)$，因为 $a$ 是固定的，所以它所进行的所有的**有效操作**中，每个 $L$ 操作的**相对顺序**固定，每个 $R$ 操作的**相对顺序**也固定。

所以我们才可以大胆地使用动态规划（此动态规划和 $a$ 数组无关），并设 $dp_{i,j,k}$ 是**后** $i$ 个操作中，有 $j$ 个**有效的** $L$ 操作，有 $k$ 个**有效的** $R$ 操作的数量。

至于为什么是**后** $i$ 个操作，因为**有效操作**保证越后面的一定有效，只有这样才能方便转移。

转移也相当简单：
$$
dp_{i+1,j,k} \leftarrow  dp_{i,j,k}\times 2\times (j+k)\\
dp_{i+1,j,k+1} \leftarrow dp_{i,j,k}\\
dp_{i+1,j+1,k} \leftarrow dp_{i,j,k}\\
$$


那么怎么优化呢？

我们再梳理一遍，发现 $dp$ 解决的问题是下面两个：

1. **有效操作**和**无效操作**如何排列。
2. 每个**有效操作**是 $L$ 还是 $R$。

这里，第一个问题很有必要，但是对于第二个问题，因为 $L$ 与 $R$ 操作的顺序不会影响答案，所以我们干脆舍掉这个问题。那么事实上，我们只要知道 $L+R$ 就好了，于是 $dp_{i,j,k}$ 可以优化为 $dp1_{i,p=j+k}$，其实 $dp1_{i,p=j+k}=dp_{i,j,k}\times \binom{i+j}{i}$。我们统计答案处乘上贡献即可。

而且，这个转移更简单：
$$
dp1_{i+1,j}\leftarrow dp1_{i,j}\times 2\times j\\
dp1_{i+1,j+1}\leftarrow dp1_{i,j}
$$

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3000, mod = 998244353;
int n, m;
int a[MAXN + 5];
int dp[MAXN + 5][MAXN + 5];
int qpow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b &1ll) ans = ans * a % mod;
		a = a * a % mod;
		b = b / 2;
	}
	return ans;
}
int fac[MAXN + 5], inv[MAXN + 5];
int C(int n, int m) {
	if (n < m ) return 0;
	return fac[n] *inv[m]%mod*inv[n-m]%mod;
}
signed main() {
    fac[0] = inv[0] = 1;
	for (int i = 1; i <= MAXN; i ++) fac[i] = fac[i - 1] * i % mod, inv[i] = qpow(fac[i], mod - 2);
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
    dp[0][0] = 1;
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j <= i; j ++) {
            (dp[i + 1][j] += dp[i][j] * 2 * j % mod) %= mod;
            (dp[i + 1][j + 1] += dp[i][j] ) %= mod;
        }
    }
    int ans = 0;
    for (int l = 0; l <= n; l ++) {
        for (int r = n - l; r >= 0; r --) {
            if (n - l - r >= 2 && a[n - r - 1] > a[n - r]) break;
            (ans += C(l + r,l) * dp[m][l + r] % mod) %= mod;
        }
    }
    cout<<ans;
    return 0;
}
```

---

