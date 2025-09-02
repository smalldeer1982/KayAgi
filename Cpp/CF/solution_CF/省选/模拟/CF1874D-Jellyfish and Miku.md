# Jellyfish and Miku

## 题目描述

There are $ n + 1 $ cities with numbers from $ 0 $ to $ n $ , connected by $ n $ roads. The $ i $ -th $ (1 \leq i \leq n) $ road connects city $ i-1 $ and city $ i $ bi-directionally. After Jellyfish flew back to city $ 0 $ , she found out that she had left her Miku fufu in city $ n $ .

Each road has a positive integer level of beauty. Denote the beauty of the $ i $ -th road as $ a_i $ .

Jellyfish is trying to find her fufu. Because of her poor sense of direction, she doesn't know which way to go. Every day, she randomly chooses a road connected to the city she currently is in and traverses it. Let $ s $ be the sum of the beauty of the roads connected to the current city. For each road connected to the current city, Jellyfish will traverse the road with a probability of $ \frac x s $ , where $ x $ is the beauty of the road, reaching the city on the other side of the road.

Jellyfish will start at city $ 0 $ , and she will get only her fufu back when she reaches city $ n $ .

You want to choose the beauty of the roads such that the expected number of days Jellyfish takes to find her fufu will be the minimum possible. However, due to limited funding, the sum of beauties of all roads must be less than or equal to $ m $ .

Find the minimum expected number of days Jellyfish needs to get her fufu back if the beauty of the roads is chosen optimally.

## 说明/提示

In the first example, the optimal assignment of beauty is $ a=[1, 2, 5] $ . The expected number of days Jellyfish needs to get her fufu back is $ 5.2 $ .

## 样例 #1

### 输入

```
3 8```

### 输出

```
5.200000000000```

## 样例 #2

### 输入

```
10 98```

### 输出

```
37.721155173329```

# 题解

## 作者：mod998244353 (赞：14)

设 $f_i$ 表示从 $i$ 走到 $n$ 需要的期望步数，则有：

$$\begin{cases}f_{0}=1+f_{1}\\f_{i}=1+\dfrac{a_i}{a_i+a_{i+1}}f_{i-1}+\dfrac{a_{i+1}}{a_i+a_{i+1}}f_{i+1}\quad(1\leq i<n)\\f_n=0\end{cases}$$

将第二条式子化简后得到：

$$a_{i+1}(f_{i}-f_{i+1})=a_i(f_{i-1}-f_{i})+a_i+a_{i+1}$$

设 $g_{i}=f_{i-1}-f_{i}$，则有：

$$\begin{cases}g_{1}=1\\a_{i+1}g_{i+1}=a_ig_i+a_i+a_{i+1}\end{cases}$$

可以计算得到：

$$g_{i}=2\times\frac{\sum\limits_{j<i}a_j}{a_i}+1$$

我们要求的答案就是 $f_0$：

$$\begin{aligned}f_0 & = \sum\limits_{i=1}^n (f_{i-1}-f_{i}) \\ & = \sum\limits_{i=1}^n g_{i} \\ & = \sum\limits_{i=1}^n (2\times\frac{\sum\limits_{j<i}a_j}{a_i}+1) \\ & = 2\times\sum\limits_{i=1}^n \dfrac{1}{a_i}(\sum\limits_{j=1}^{i-1}a_j)+n\end{aligned}$$

因此我们只需要最小化 $\sum\limits_{i=1}^n \dfrac{1}{a_i}(\sum\limits_{j=1}^{i-1}a_j)$。

设 $dp_{i,s}$ 表示确定了 $a_1,a_2,\cdots,a_i$ 的值， $\sum\limits_{j=1}^{i}a_j=s$ 时，$\sum\limits_{k=1}^i \dfrac{1}{a_k}(\sum\limits_{j=1}^{k-1}a_j)$ 的最小值。

有 $dp_{i+1,s+k}\leftarrow dp_{i,s}\times \dfrac{s}{k}$

这样的做法是 $O(nm^2)$ 的。

我们发现，$a$ 序列一定是不下降的。

> 证明:若存在 $a_{i}>a_{i+1}$，则交换 $a_{i},a_{i+1}$ 后答案一定更优

所以我们得到上述转移方程的一个限制： $s+k(n-i)\leq m$。（后面至少能放下 $n-i$ 个 $k$）

时间复杂度就变成了 $O(m^2\log n)$：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=3005;
int n,m;
double f[MAXN][MAXN];
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		for(int j=0; j<=m; ++j)
			f[i][j]=1e9;
	for(int j=0; j<n; ++j)
		for(int k=0; k<=m; ++k)
			for(int i=1; k+i*(n-j)<=m; ++i)
				f[j+1][k+i]=min(f[j+1][k+i],f[j][k]+k/(double)i);
	printf("%.15lf\n",f[n][m]*2+n);
	return 0;
}
```

---

## 作者：stntn (赞：6)

设 $E_u$ 表示从 $u$ 走到 $u+1$ 的期望步数。根据期望线性性，总期望步数 $Ans=\sum_u E_{u}$

设 $a_i$ 为 $i \to i+1$ 的边权，易得方程 
$$
E_u=\frac{a_{u-1}}{a_{u}+a_{u-1}}(E_{u-1}+E_u+1)+\frac{a_{u}}{a_{u}+a_{u-1}}
$$

整理得：

$$
E_u=\frac{a_{u-1}}{a_{u}}(E_{u-1}+1)+1
$$

手玩一下前几项发现：

$$
E_1=1
$$
$$
E_2=\frac{a_1}{a_2}(E_1+1)+1=\frac{2a_1}{a_2}+1
$$
$$
E_3=\frac{a_2}{a_3}\left( \frac{a_1}{a_2} (E_1+1)+2 \right ) +1=\frac{2a_1}{a_3}+\frac{2a_2}{a_3}+1
$$
$$
E_4=\frac{a_3}{a_4}\left(\frac{a_1}{a_3}(E_1+1)+\frac{2a_2}{a_3}+2\right)+1=\frac{2a_1}{a_4}+\frac{2a_2}{a_4}+\frac{2a_3}{a_4}+1
$$
$$
E_n=1+\frac{2}{a_n}\sum_{i<n} a_i
$$
$$
Ans=\sum_{i=1}^n \left(1+ \frac{2}{a_i}\sum_{j=1}^{i-1} a_j\right)=n+2\sum_{i=1}^n \frac{1}{a_i} \sum_{j=1}^{i-1} a_j
$$

于是可以 DP，设 $f_{i,j}$ 表示前 $i$ 个点，边权和为 $j$ 的最小期望步数。方程是显然的：

$$
f_{i,j}=\min_{k<i}\{f_{i-1,k}+w(k,j)\},w(k,j)=\frac{k}{j-k}
$$

暴力做是 $O(n^3)$ 的，但是我们发现 $w(i,j)$ 满足四边形不等式，证明过程暴力通分简单无脑。

考虑 $l_1\le l_2 < r_1 \le r_2$，假设四边形不等式成立，有：

$$
\frac{l_1}{r_1-l_1}+\frac{l_2}{r_2-l_2} \ge \frac{l_1}{r_2-l_1}+\frac{l_2}{r_1-l_2}
$$

$$
l_2(r_1-r_2) \le l_1(r_1-r_2)
$$

不等式成立故得证。

于是可以分治决策点，复杂度为 $O(nm\log m)$。

---

## 作者：WilliamFranklin (赞：5)

### 主要思路

这里将每一条边的权值设为 $w_i$。

首先设 $f_i$ 表示以 $i$ 为起点，以 $i + 1$ 为终点的期望步数，则：

$$f_i = 1 + \frac{w_i}{w_i + w_{i + 1}}(f_{i - 1} + f_i)$$

两边同时乘 $w_i + w_{i + 1}$，再移个项，得到：

$$w_{i + 1} \cdot f_i = w_i + w_{i + 1} + w_i \cdot f_{i - 1}$$

然后设 $h_i = w_{i + 1} \cdot f_i$，得到：

$$h_i = w_i + w_{i + 1} + h_{i - 1}$$

像递推一样考虑，发现可以得到：

$$h_i = w_{i + 1} + 2\sum_{j = 1}^{i}w_j$$

将 $h_i$ 换成 $w_{i + 1} \cdot f_i$ 得到：

$$w_{i + 1} \cdot f_i = w_{i + 1} + 2\sum_{j = 1}^{i}w_j$$

再将左边 $w_{i + 1}$ 除过去，得到：

$$f_i = 1 + \frac{2}{w_{i + 1}}\sum_{j = 1}^i w_j$$

根据期望的线性性质，从 $0$ 走到 $n$ 的期望，就是 $\sum_{i = 0}^{n - 1} f_i$，即：

$$\sum_{i = 0}^{n - 1}f_i = n + 2\sum_{i = 1}^n \frac{1}{w_i}\sum_{j = 1}^{i - 1} w_j$$

然后就可以用 DP 来放松一下了，设 $dp_{i, j}$ 表示已经确定了 $w_{1\dots i}$，且 $\sum w_{1\dots i} = j$ 时 $\sum_{x = 1}^i \frac{1}{w_x} \sum_{y = 1}^{x - 1} w_y$ 的最小值，但是会发现这样会超时。

考虑优化，发现最优解中，$w_{1\dots n}$ 必须时非严格递增的，所以 $w_i \le \frac{m}{n - i + 1}$，利用这个条件，降下时间复杂度，即可通过此题。

下面看下简短的代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 3005;
long double f[N][N + N];
int n, m;
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	For(i, 0, N - 1) For(j, 0, N + N - 1) f[i][j] = 1e18;
	f[0][0] = 0;
	For(i, 1, n) {
		For(j, 1, m / (n - i + 1)) {
			For(k, 0, m) {
				f[i][k + j] = min(f[i - 1][k] + k * 1.0000000000 / j, f[i][k + j]);
			}
		}
	}
	long double minn = 1e18;
	For(i, 1, m) minn = min(minn, f[n][i]);
	printf("%.10Lf", n + 2 * minn); 
	return 0;
} 
```

---

## 作者：MatrixGroup (赞：5)

## 题意

给定 $n,m$，你需要在所有的长度为 $n$，和为 $m$ 的正整数序列 $a$ 中最小化如下值：

> 从 $0$ 开始随机游走。如果到 $n$ 就结束。如果当前在 $0$ 就走到 $1$。否则设当前在 $i$。以 $\dfrac{a_i}{a_i+a_{i+1}}$ 的概率走到 $i-1$，剩下概率走到 $i+1$。该值为期望步数。

求最小的该值。

$1\le n\le m\le 3000$。

## 题解

考虑求出期望步数的表达式。设 $f_i$ 为 $i$ 到 $n$ 的期望步数。有：

$$
\begin{cases}
f_0=f_1+1\\
f_i=\dfrac{a_i}{a_i+a_{i+1}}f_{i-1}+\dfrac{a_{i+1}}{a_i+a_{i+1}}f_{i+1}+1&1\le i<n\\
f_n=0
\end{cases}
$$

考虑设 $f_i=k_if_0+b_i$，则 $f_0=-\dfrac{b_n}{k_n}$。

有：

$$
\begin{cases}
k_0=1,b_0=0,k_1=1,b_1=-1\\
k_{i+1}-k_i=\dfrac{a_i}{a_{i+1}}(k_i-k_{i-1})&1\le i<n\\
b_{i+1}-b_i=\dfrac{a_i}{a_{i+1}}(b_i-b_{i-1})-1-\dfrac{a_i}{a_{i+1}}&1\le i<n\\
\end{cases}
$$

根据第一个式子不难得出 $k_i\equiv k_1=1$（这在任何随机游走题中都是成立的，因为你不会走丢了）。那么答案就是 $-b_n$。令 $c_i=-b_i$，有

$$
\begin{cases}
c_0=0,c_1=1\\
c_{i+1}-c_i=\dfrac{a_i}{a_{i+1}}(c_i-c_{i-1})+1+\dfrac{a_i}{a_{i+1}}&1\le i<n\\
\end{cases}
$$

那么 $c_{i+1}-c_i=1+\dfrac{a_i}{a_{i+1}}+\dfrac{a_i}{a_{i+1}}(1+\dfrac{a_{i-1}}{a_i}+\dfrac{a_{i-1}}{a_i}(1+\cdots))=1+2\sum_{j=1}^i\dfrac{a_j}{a_{i+1}}$。进行前缀和，可得 $c_{n}=n+2\sum_{1\le j<i\le n}\dfrac{a_j}{a_i}$。

这样 $dp_{i,j}$ 表示前 $i$ 个和为 $j$ 的最小当前 $\sum_{1\le j<i\le n}\dfrac{a_j}{a_i}$ 就可以 $O(m^3)$ 了（假设 $n=O(m)$）。

考虑优化。$dp_{i,j}\overset{+\frac{j}{k}}{\rightarrow}dp_{i+1,j+k}$，注意到四边形不等式：若 $j_1<j_2<j_3<j_4$，则有 $\dfrac{j_1}{j_3-j_1}+\dfrac{j_2}{j_4-j_2}<\dfrac{j_1}{j_4-j_1}+\dfrac{j_2}{j_3-j_2}$。证明考虑这等价于$
\dfrac{j_1(j_4-j_3)}{(j_3-j_1)(j_4-j_1)}<\dfrac{j_2(j_4-j_3)}{(j_3-j_2)(j_4-j_2)}$，即 $\dfrac{(j_3-j_1)(j_4-j_1)}{j_1}>\dfrac{(j_3-j_2)(j_4-j_2)}{j_2}$，也就是 $\dfrac{j_3j_4}{j_1}+j_1>\dfrac{j_3j_4}{j_2}+j_2$。根据题设我们有 $j_1,j_2<\sqrt{j_3j_4}$，于是就证完了。因此用决策单调性分治优化 dp 就可以做到 $O(m^2\log m)$ 的复杂度。

---

## 作者：Purslane (赞：3)

# Solution

但凡这题写的快一点，昨晚就能上 GrandMaster 了 /ll

首先考虑给定了 $a_i$，你能否求出期望步数。然后再想怎么最优化。

很容易列出方程：

$$dp_i=\frac{a_i}{a_i+a_{i+1}}dp_{i-1}+\frac{a_{i+1}}{a_i+a_{i+1}}dp_{i+1}+1$$

特别地，$a_0=0$，$dp_{-1}=0$，$dp_n=0$。

正常做是带状矩阵的高斯消元，然而我们希望写成 $a$ 的表达式。

考虑手动模拟。你现在知道了 $dp_0=dp_1+1$。

然后根据这个方程你可以写出 $dp_1 = \frac{a_1}{a_1+a_2} dp_0+\frac{a_2}{a_1+a_2} dp_2+1$。把上面这个式子给带进来得到 $\frac{a_2}{a_1+a_2}dp_1 = \frac{a_2}{a_1+a_2}dp_2+\frac{2a_1+a_2}{a_1+a_2}$，也就是 $dp_1=dp_2+\frac{2a_1+a_2}{a_2}$。然后你继续这样操作。

最终你发现你可以统一出一个式子：$dp_k=dp_{k+1}+\frac{2\sum_{i=1}^{k}a_i+a_{k+1}}{a_{k+1}}$ . 最终得到

$$dp_0 = n + 2\sum_{i=1}^n \frac{S_{i-1}}{a_i}$$

其中 $S_k = \sum_{i=1}^k a_i$。因此你要最大化这个东西。

考虑使用动态规划。设 $dp_{i,j}$ 表示 $S_{i}=j$ 的最大答案（我们只算 $\sum_{i=1}^n \frac{S_{i-1}}{a_i}$）。那么可以写出转移：

$$dp_{i,j}=\min_{1 \le k < j} \{dp_{i-1,k}+\frac{k}{j-k}\}$$

一时间感觉只能 $O(nm^2)$。然后你敏锐地察觉到大概有决策单调性，不过还需要严谨证明。

考虑 $f(x) = \frac{k}{x-k}$，导之有 $f'(x)=-\frac{k}{(x-k)^2}$。可以发现，当 $x$ 一定，小于 $x$ 的 $k$ 越大，这个值越小。因此如果对于 $j$，决策点 $k_1 < k_2$ 且 $k_2$ 优于 $k_1$，那么当 $j$ 增加时，$k_2$ 的增量更小，也就是说 $k_2$ 依旧更优，那么具有决策单调性。可以使用二分栈或者分治来写。

代码；

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10;
int n,m; long double dp[MAXN][MAXN];
void solve(int dep,int l,int r,int L,int R) {
	if(l>r) return ;
	if(L==R) {
		ffor(i,l,r) dp[dep][i]=dp[dep-1][L]+(long double)(L*1.0/(i-L));
		return ;
	}
	int mid=l+r>>1,pos=0; long double ans=1000000000;
	ffor(i,L,min(R,mid-1)) if(dp[dep-1][i]+(long double)(i*1.0/(mid-i))<ans) ans=min(ans,dp[dep-1][i]+(long double)(i*1.0/(mid-i))),pos=i;
	dp[dep][mid]=ans;
	solve(dep,l,mid-1,L,pos);
	solve(dep,mid+1,r,pos,R);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,0,n) ffor(j,0,m) dp[i][j]=1000000000;
	dp[0][0]=0;
	ffor(i,1,n) solve(i,i,m,0,m);	
	long double ans=1000000000;
	ffor(i,n,m) ans=min(ans,dp[n][i]);
	cout<<fixed<<setprecision(12)<<n+ans*2;
	return 0;
}
```

---

## 作者：Liuxizai (赞：2)

[My Blog](https://liuxizai.ac.cn/archives/solution-codeforces-round-901.html)

从 $0$ 到 $n$ 的期望步数可以拆成从 $i$ 到 $i+1$，也即通过每条道路所需的期望步数之和。

我们考虑若相邻两条道路的美丽值分别为 $a,b$，设通过前一条道路期望需要 $x$ 步，通过后一条道路期望需要 $E$ 步，则有方程：
$$
E=1+\frac{a}{a+b}(x+E)
$$
解得 $E=\frac ab (x+1)+1$。

于是，若我们设 $i-1\to i$ 的道路美丽值为 $a_i$，通过 $i-1\to i$ 的的期望步数为 $f_i$，令 $a_0=0,f_0=0$，则有转移 $f_i=\frac{a_{i-1}}{a_i}(f_{i-1}+1)+1$。

为了让转移方程更加简洁，我们现在令 $f_i$ 表示原来的 $f_i+1$，则转移变为 $f_i=\frac{a_{i-1}}{a_i}f_{i-1}+2$。

观察 $\frac{a_{i-1}}{a_i}$ 这个分式，我们发现连续的这种分式乘起来有相当好的性质，于是考虑将转移方程中的 $f$ 不断带入。
$$
\begin{aligned}
f_i&=\frac{a_{i-1}}{a_i}f_{i-1}+2\\
f_i&=\frac{a_{i-1}}{a_i}\left(\frac{a_{i-2}}{a_{i-1}}f_{i-2}+2\right)+2\\
f_i&=\frac{a_{i-2}}{a_i}f_{i-2}+\frac{2a_{i-1}}{a_i}+2\\
f_i&=\frac{a_{i-3}}{a_i}f_{i-3}+\frac{2(a_{i-2}+a_{i-1})}{a_i}+2\\
&\dots
\end{aligned}
$$
直到递归进行到 $f_0$ 时，此时第一项形如 $\frac{a_0}{a_i}f_0$，其值为 $0$，于是 $f_i$ 可以写成更加漂亮的形式：
$$
f_i=\frac{2\sum_{j<i}a_j}{a_i}+2
$$
现在问题转化为最小化 $\sum_i\frac 1{a_i}\sum_{j<i}a_j$。我们设 $dp_{i,j}$ 表示考虑了前 $i$ 条道路，已经分配了 $j$ 的美丽值时前述式子的最小值。有转移：
$$
dp_{i,j}=\min\left\{dp_{i-1,k}+\frac{k}{j-k}\right\}
$$
可以证明，转移时的代价满足四边形不等式，从而这一 dp 有决策单调性。

由于分层转移，我们可以使用分治优化 dp，复杂度为 $O(nm\log m)$；也可以直接运用序列分割 dp 中的结论，也即设 $dp_{i,j}$ 的最优转移点为 $opt_{i,j}$，我们有 $opt_{i,j-1}\le opt_{i,j}\le opt_{i+1,j}$，复杂度为 $O(nm)$。我实现了后者。

注意代码里交换了 dp 的两维。

[Submission #232937205](https://codeforces.com/contest/1874/submission/232937205)

---

## 作者：xzz_cat6 (赞：1)

# CF1874D Jellyfish and Miku
难得有一道可以自己做出来的题，本文的做法非常暴力，但是非常易懂。
## Solution
直接做显然不太好做，考虑 $a_i$ 确定的情况，设 $f_i$ 为从 $i$ 点走到 $n$ 点的期望步数，容易得到下式：
$$
\begin{cases}
ans=f_0=f_1+1\\
f_i=f_{i-1}\times\frac{a_i}{a_i+a_{i+1}}+f_{i+1}\times\frac{a_{i+1}}{a_i+a_{i+1}}+1\\
f_n=0
\end{cases}
$$
此时对第二条式子化简：
$$
f_i=f_{i-1}\times\frac{a_i}{a_i+a_{i+1}}+f_{i+1}\times\frac{a_{i+1}}{a_i+a_{i+1}}+1\\
f_{i+1}\times\frac{a_{i+1}}{a_i+a_{i+1}}=f_i-f_{i-1}\times\frac{a_i}{a_i+a_{i+1}}-1\\
f_{i+1}=f_i\times\frac{a_i+a_{i+1}}{a_{i+1}}-f_{i-1}\times\frac{a_i}{a_{i+1}}-\frac{a_i+a_{i+1}}{a_{i+1}}\\
f_{i+1}=(f_i-f_{i-1}-1)\times\frac{a_i}{a_{i+1}}+f_i-1\\
$$
此时就有了关于 $f$ 的递推式，将 $f_0$ 代入 $ans$，并依次递推出 $f_i$，有下式：
$$
\begin{cases}
f_0=ans\\
f_1=ans-1\\
f_2=(f_1-f_0-1)\times\frac{a_1}{a_2}+f_1-1\\
~~~~~=ans-2-\frac{2\cdot a_1}{a_2}\\
f_3=ans-3-\frac{2\cdot a_1}{a_2}-\frac{2\cdot  a_1}{a_3}-\frac{2\cdot a_2}{a_3}\\
\dots\\
f_n=ans-n-2\cdot \sum_{i=1}^{n}\frac{1}{a_i}\cdot \sum_{j=1}^{i-1}a_j
\end{cases}
$$
又因为 $f_n=0$，所以有：
$$
ans-n-2\cdot \sum_{i=1}^{n}\frac{1}{a_i}\cdot \sum_{j=1}^{i-1}a_j=0\\
ans=n+2\cdot \sum_{i=1}^{n}\frac{1}{a_i}\cdot \sum_{j=1}^{i-1}a_j
$$
于是目标变为使 $\sum_{i=1}^{n}\frac{1}{a_i}\cdot \sum_{j=1}^{i-1}a_j$ 最大，容易列出 dp 转移方程：
$$
dp_{i,j}=\min_{k=0}^{j-1} dp_{i-1,k}+\frac{k}{j-k}
$$
直接转移的复杂度是 $O(nm^2)$ 的，难以通过，注意到这是经典的决策单调性优化 dp，证明只需设 $w(x,y)=\frac{x}{y-x}$，之后打表发现其满足四边形不等式，即可以决策单调性优化，时空复杂度 $O(nm)$。
## Code
```cpp
#include<bits/stdc++.h>
#define N 3005
#define inf 1e9
using namespace std;
double calc(int a,int b){return a*1.0/(b-a);}
int n,m,q[N],hd,tl;
long double dp[N][N],ans=inf;
int solve(int now,int x,int y){
	if(dp[now][x]+calc(x,m)<dp[now][y]+calc(y,m))	return m+1;
	int l=y+1,r=m,res=y;
	while(l<=r){
		int m=(l+r)>>1;
		if(calc(y,m)+dp[now][y]<=calc(x,m)+dp[now][x])	r=m-1,res=m;
		else	l=m+1;
	}
	return res;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)	dp[0][i]=inf;
	for(int i=1;i<=n;i++){
		q[tl=hd=1]=i-1;
		for(int j=i;j<=m;j++){
			while(hd<tl&&solve(i-1,q[hd],q[hd+1])<=j)	hd++;
			dp[i][j]=dp[i-1][q[hd]]+calc(q[hd],j);
			while(hd<tl&&solve(i-1,q[tl-1],q[tl])>=solve(i-1,q[tl],j))	tl--;
			q[++tl]=j;
		}
	}
	for(int i=n;i<=m;i++)	ans=min(ans,dp[n][i]);
	cout<<fixed<<setprecision(12)<<ans*2+n;
	return 0;
} 
```

---

## 作者：Leasier (赞：1)

考虑在已知 $a_i$ 的情况下如何计算期望用时。

设 $f_i$ 表示到达 $n$ 的期望用时，有：

- $f_0 = f_1 + 1$。
- $\forall i \in [1, n)$，$f_i = \dfrac{a_i f_{i - 1} + a_{i + 1} f_{i + 1}}{a_i + a_{i + 1}} + 1$。
- $f_n = 0$。

套路地，化简得 $a_{i + 1} (f_i - f_{i + 1}) - a_i (f_{i - 1} - f_i) = a_i + a_{i + 1}$。

令 $g_i = f_{i - 1} - f_i$，有：

- $g_1 = 1$。
- $\forall i \in [2, n]$，$g_i = \dfrac{a_i}{a_i{i + 1}} (g_{i - 1} + 1) + 1$。

不难归纳出 $g_i = \dfrac{2 \displaystyle\sum_{j = 1}^{i - 1} a_j}{a_i} + 1$。

于是我们所求即为 $f_0 = \displaystyle\sum_{i = 1}^n g_i = 2 \sum_{i = 1}^n \dfrac{\displaystyle\sum_{j = 1}^{i - 1} a_j}{a_i} + n$，则目标为最小化 $\displaystyle\sum_{i = 1}^n \dfrac{\displaystyle\sum_{j = 1}^{i - 1} a_j}{a_i}$。

一个暴力的想法是直接背包，但时间复杂度为 $O(nm^2)$，无法通过。

注意到 $a_i > a_{i + 1}$ 一定不优，则 $\displaystyle\sum_{j = 1}^{i - 1} a_j + a_i (n - i + 1) \leq m$，适当限制背包上界即可做到 $O(nm \log n)$，可以通过。

代码：
```cpp
#include <stdio.h>

double dp[3007][3007];

inline double min(double a, double b){
	return a < b ? a : b;
}

int main(){
	int n, m;
	double ans = 1e9;
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= n; i++){
		for (int j = i; j <= m; j++){
			dp[i][j] = 1e9;
		}
	}
	dp[0][0] = 0.0;
	for (int i = 0; i < n; i++){
		int up = m / (n - i);
		for (int j = i; j < m; j++){
			for (int k = 1; k <= up && j + k <= m; k++){
				dp[i + 1][j + k] = min(dp[i + 1][j + k], dp[i][j] + 1.0 * j / k);
			}
		}
	}
	for (int i = n; i <= m; i++){
		ans = min(ans, dp[n][i]);
	}
	printf("%.12lf", ans * 2 + n);
	return 0;
}
```

---

## 作者：Register_int (赞：1)

先考虑 $a_i$ 固定怎么做。设 $dp_i$ 表示从 $i-1$ 到 $i$ 的期望步数，有转移：

$$
dp_i=
\begin{cases}
1&i=1\\
\dfrac{a_{i-1}}{a_{i-1}+a_i}(dp_{i-1}+dp_i)+1&i>1
\end{cases}
$$

第二个式子化简为 $dp_i=\frac{a_{i-1}}{a_i}(dp_{i-1}+1)+1$，得到 $dp_i=1+\frac2{a_i}\sum^{i-1}_{j=1}a_j$。所以答案为 $\sum dp_i=n+2\sum^n_{i=1}\frac1{a_i}\sum^{i-1}_{j=1}a_j$。

我们需要最小化 $\sum^n_{i=1}\frac1{a_i}\sum^{i-1}_{j=1}a_j$。设 $f_{i,j}$ 为当前算了前 $i$ 个，$a_i$ 总和为 $j$ 时的最小值，有 $f_{i+1,j+k}\leftarrow f_{i,j}+\dfrac jk$，时间复杂度 $O(nm^2)$。

考虑优化。容易发现 $a_i$ 必定单调不减，否则交换两项一定不劣。时间复杂度降为 $O(m^2\ln n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int MAXN = 3e3 + 10;

int n, m; double dp[MAXN][MAXN];

int main() {
	scanf("%d%d", &n, &m), memset(dp, 0x44, sizeof dp);
	for (int i = 0; i <= m; i++) dp[0][i] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			for (int k = 1; (m - j) / k >= n - i; k++) {
				dp[i + 1][j + k] = min(dp[i + 1][j + k], dp[i][j] + (db)j / k);
			}
		}
	}
	printf("%.12lf", n + 2 * dp[n][m]);
}
```

---

## 作者：UKE_Automation (赞：0)

### CF1873D Jellyfish and Miku

[$\text{Link}$](https://codeforces.com/contest/1874/problem/D)

首先直接做不太可行，我们先考虑给定 $a_i$ 之后的情况。令 $f_i$ 表示 $i\to n$ 的期望步数，那么显然有：
$$
f_i=f_{i+1}\times \frac{a_{i+1}}{a_i+a_{i+1}}+f_{i-1}\times \frac{a_i}{a_i+a_{i+1}}+1
$$
化简一下可以得到：
$$
f_{i-1}=f_i\times \frac{a_i+a_{i+1}}{a_i}-f_{i+1}\times \frac{a_{i+1}}{a_i}-\dfrac{a_i+a_{i+1}}{a_i}
$$
这个形式不是很直观，此时发现我们可以构造出差分形式，于是有：
$$
f_{i-1}-f_i=(f_i -f_{i+1})\times \frac{a_{i+1}}{a_{i}}-\dfrac{a_i+a_{i+1}}{a_i}
$$
令 $g_i=f_{i-1}-f_i$，则有：
$$
a_{i+1}g_{i+1}=a_ig_i+a_i+a_{i+1}
$$
那么此时可以得到：
$$
g_i=2\times \dfrac{\sum\limits_{j=1}^{i-1}a_j}{a_i}+1
$$
而我们要求的 $f_0$ 就是 $\sum g_i$，这个时候我们就可以很容易的设出 dp 状态：设 $dp(i,j)$ 表示当前考虑到 $i$，前 $i$ 个 $a$ 的和是 $j$ 时的最小期望步数。那么容易写出转移：
$$
dp(i+1,j+k)\gets dp(i,j)+ \frac{j}{k}
$$
直接转移显然是 $O(nm^2)$ 的。这个时候需要再发现一个性质：最优解一定保证 $a_i$ 单调不降。这个可以用调整法简单证明。那么转移的时候必须要满足 $j+k(n-i)<m$，此时合法的 $k$ 的个数就会减少了，最后复杂度是 $O(m^2\log m)$ 的。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 3e3 + 5;
const int Inf = 2e9;
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, m; 
double dp[Maxn][Maxn];

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	IOS();
	cin >> n >> m;
	for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) dp[i][j] = Inf;
	dp[0][0] = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= m; j++) {
			for(int k = 1; j + (n - i) * k <= m; k++) {
				chkmin(dp[i + 1][j + k], dp[i][j] + 1.0 * j / k);
			}
		}
	}
	double ans = Inf;
	for(int i = 0; i <= m; i++) chkmin(ans, dp[n][i]);
	cout << fixed << setprecision(13) << 2 * ans + n << '\n';
    Usd();
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1874D)

**题目大意**

> 给定长度为 $n$ 的链，给每条边赋一个权重 $a_i$，每个点会按权重随机一条边移动，要求 $\sum a_i\le m$，最小化 $0\to n$ 的期望移动步数。
>
> 数据范围：$n,m\le 3000$。

**思路分析**

根据期望线性性，计算 $i\to i+1$ 的期望步数 $f_i$：
$$
f_i=1+\dfrac{a_i}{a_{i}+a_{i+1}}(f_{i-1}+f_i)=\dfrac{a_{i}}{a_{i+1}}(1+f_{i-1})+1=1+2\sum_{j\le i}\dfrac{a_j}{a_{i+1}}
$$
因此直接 dp，$f_{i,s}$ 表示 $a[1,i]$ 前缀和为 $s$ 的方案数，枚举 $a_i=x$，暴力 dp 复杂度 $\mathcal O(nm^2)$。

但根据贪心思想，不难证明 $a$ 单调递减，否则交换邻项更优，那么 $(n-i)x\le m-s$，此时枚举量降到 $\mathcal O(m^2\log n)$ 级别。

时间复杂度 $\mathcal O(m^2\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ld long double
using namespace std;
const int MAXN=3005;
const ld inf=1e18;
ld f[MAXN],g[MAXN];
signed main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for(int j=0;j<=m;++j) f[j]=g[j]=inf;
	f[0]=0;
	for(int i=1;i<=n;++i) {
		for(int s=0;s<=m;++s) {
			for(int j=1;s+j<=m&&s+(n-i)*j<=m;++j) {
				g[s+j]=min(g[s+j],f[s]+(ld)s/j);
			}
		}
		for(int j=0;j<=m;++j) f[j]=g[j],g[j]=inf;
	}
	ld ans=inf;
	for(int j=0;j<=m;++j) ans=min(ans,f[j]);
	printf("%.20Lf\n",ans*2+n);
	return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

# Solution

先考虑如果每条道路的美丽度固定，怎么快速计算期望时间。

令 $E_i$ 表示 $i-1\to i$ 的期望时间。

根据期望的线性性，可得 $ans=\sum\limits_{i=1}^n E_i$。

$$
\begin{aligned}
E_i&=1+\dfrac{a_{i-1}}{a_{i-1}+a_i}(E_{i-1}+E_i)\\
a_iE_i&=a_{i-1}+a_i+a_{i-1}E_{i-1}\\
\end{aligned}
$$


再令 $t_i=a_iE_i$，$t_i=a_{i-1}+a_i+t_{i-1}$。

根据通过道路概率的定义，可以得到 $a_0=0$，那么 $t_0=0$。

$$
\begin{aligned}
ans&=\sum_{i=1}^n\dfrac{t_i}{a_i}\\
&=\sum_{i=1}^n\dfrac{2\sum\limits_{j=1}^ia_j}{a_i}-1\\
&=2(\sum_{i=1}^n\sum_{j=1}^i\dfrac{a_j}{a_i})-n
\end{aligned}
$$

那么最小化答案，就要最小化 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n\dfrac{a_j}{a_i}$ 的值。

设 $f_{i,j}$ 表示考虑前 $i$ 个数，当前和为 $j$ 这个式子的最小值。

状态转移方程就为 $f_{i,j}=\min_{k=1}^j f_{i-1,j-k}+\dfrac jk$。

但是直接枚举决策的时间复杂度为 $O(nm^2)$，考虑优化。

有一个重要的性质：**最优方案的美丽值单调不降**。

## 证明

反证法，如果最优方案存在相邻两项 $i$ 和 $i+1$，使得 $a_i>a_{i+1}$，那么交换 $a_i$ 和 $a_{i+1}$ 后，第一个求和的第 $i$ 项和第 $i+1$ 项的和就由 $\sum\limits_{j=1}^i\dfrac{a_j}{a_i}+\sum\limits_{j=1}^{i+1}\dfrac{a_j}{a_{i+1}}$ 变为了 $\sum\limits_{j=1}^{i-1}\dfrac{a_j}{a_{i+1}}+1+\sum\limits_{j=1}^{i+1}\dfrac{a_j}{a_i}$。

把求和里的上界都改为 $i-1$，第一个式子就变为了 $\sum\limits_{j=1}^{i-1}\dfrac{a_j}{a_i}+\sum\limits_{j=1}^{i-1}\dfrac{a_j}{a_{i+1}}+2+\dfrac{a_i}{a_{i+1}}$，第二个式子变为了 $\sum\limits_{j=1}^{i-1}\dfrac{a_j}{a_{i+1}}+\sum\limits_{j=1}^{i-1}\dfrac{a_j}{a_i}+2+\dfrac{a_{i+1}}{a_i}$。

两个式子把前三项抵消掉后，第一个式子就为 $\dfrac{a_i}{a_{i+1}}$，第二个式子为 $\dfrac{a_{i+1}}{a_i}$。

由于 $a_i>a_{i+1}$，第一个式子大于 $1$，第二个式子小于 $1$，第一个式子就大于第二个式子。

那么交换 $a_i$ 和 $a_{i+1}$ 后，期望时间一定更少，与交换前为最优方案矛盾，证毕。

___



得到这个性质后，可以发现：每次的最优决策一定都小于等于 $\dfrac m{n-i+1}$，因为如果 $a_i$ 大于这个值，后面即使都填 $a_i$ 总和也大于 $m$。

再分析一下时间复杂度：
$$
\begin{aligned}
&\sum_{i=1}^n\sum_{j=1}^m\dfrac m{n-i+1}\\
=&\sum_{i=1}^n\sum_{j=1}^m\dfrac mi\\
=&\sum_{j=1}^m\sum_{i=1}^n\dfrac mi\\
=&\sum_{j=1}^mO(m\ln n)\\
=&O(m^2\ln n)
\end{aligned}
$$


时间复杂度就为 $O(m^2\ln n)$，可以通过。

答案就为 $2(\min_{i=1}^mf_{n,i})-n$。

# Code

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=3001;
double f[N][N];
int n,m;

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;i++)
		for (int j=0;j<=m;j++)
			f[i][j]=1e9;
	
	f[0][0]=0;
	for (int i=1;i<=n;i++)
		for (int j=i;j<=m;j++)
			for (int k=j/i;j+(n-i)*k<=m&&k<=j;k++)
				f[i][j]=min(f[i][j],f[i-1][j-k]+1.0*j/k);
	
	double ans=1e9;
	for (int i=n;i<=m;i++) ans=min(ans,f[n][i]);
	return !printf("%.9lf",2*ans-n);
}
```

---

## 作者：狂风之息 (赞：0)

很久没写题解了，写这篇题解的原因是乱搞过了。

推柿子：

设 $g_i$ 表示从第 $i$ 条路左侧走到右侧的期望花费。

则有 

$$\begin{aligned}
  g_i		&= \frac{a_i+a_{i-1}(g_{i-1}+g_i)}{a_{i-1}+a_i}+1 \\
  a_i g_i	&= a_{i-1}g_{i-1}+a_{i-1}+a_i \\
  a_i g_i	&= S_i-S_{i-1} \\
  g_i		&= \frac{S_i+S_{i-1}}{S_i-S_{i-1}}
\end{aligned}$$

其中 $S$ 表示 $a$ 的前缀和序列。

所以可以设计状态 $f_{i,j}$ 表示前 $i$ 条路 $S_i$ 为 $j$ 的最优方案。

转移为

$$f_{i,j}=\min_{k=i-1}^{j-1}\{f_{i-1,k}+\frac{j+k}{j-k}\}$$

这个时候大胆猜测 $i$ 相等时 $j$ 越小对应的最佳的 $k$ 也越小，但是是错的。

怎么办呢，乱搞呗，注意到在 $n$ 较小 $m$ 极大时容易出错，反而是在 $n,m$ 都相当大的时候正确性不错。

因此取一个数 $D=\frac{K}{nm}$，其中 $K$ 是一个适当的大数。每一次在上一次转移的基础上，在 $k'\in[k-D,k+D]$ 的范围内寻找新的最优解。

时间复杂度 $O(K)$。

---

