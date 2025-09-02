# [ABC217G] Groups

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc217/tasks/abc217_g

正の整数 $ N,M $ が与えられます。$ k=1,\ldots,N $ のそれぞれについて、次の問題を解いてください。

- 問題：$ 1 $ から $ N $ の番号がついた $ N $ 人を、空でない $ k $ 個のグループに分けます。 ただし、番号を $ M $ で割ったあまりが等しい人は同じグループになることができません。  
   そのようなグループ分けの方法は何通りありますか？  
   答えは非常に大きくなる可能性があるので $ 998244353 $ で割ったあまりを求めてください。

ここで、グループ分けが異なるとは、一方では人 $ x,y $ が同じグループであり、他方では異なるグループであるような $ (x,y) $ が存在することを指すものとします。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5000 $
- $ 2\ \leq\ M\ \leq\ N $
- 入力は全て整数である

### Sample Explanation 1

番号を $ 2 $ で割ったあまりが等しい人、すなわち、人 $ 1 $ と $ 3 $、人 $ 2 $ と $ 4 $ を同じグループにすることはできません。 - $ 1 $ 個のグループにすることはできません。 - $ 2 $ 個のグループにする方法は $ \{\{1,2\},\{3,4\}\},\{\{1,4\},\{2,3\}\} $ の $ 2 $ 通りです。 - $ 3 $ 個のグループにする方法は $ \{\{1,2\},\{3\},\{4\}\},\{\{1,4\},\{2\},\{3\}\},\{\{1\},\{2,3\},\{4\}\},\{\{1\},\{2\},\{3,4\}\} $ の $ 4 $ 通りです。 - $ 4 $ 個のグループにする方法は $ \{\{1\},\{2\},\{3\},\{4\}\} $ の $ 1 $ 通りです。

### Sample Explanation 2

自由にグループ分けすることができます。

### Sample Explanation 3

答えを $ 998244353 $ で割ったあまりを求めてください。

## 样例 #1

### 输入

```
4 2```

### 输出

```
0
2
4
1```

## 样例 #2

### 输入

```
6 6```

### 输出

```
1
31
90
65
15
1```

## 样例 #3

### 输入

```
20 5```

### 输出

```
0
0
0
331776
207028224
204931064
814022582
544352515
755619435
401403040
323173195
538468102
309259764
722947327
162115584
10228144
423360
10960
160
1```

# 题解

## 作者：NaCly_Fish (赞：7)

感觉机械化做法还是比较好用的，这类问题大都能使用 [求解迭代列的一些手法](https://www.luogu.com.cn/article/v82plvq2) 来处理。   
由于 $m=1$ 的情况比较特殊又很简单，**下文默认 $m \geq 2$。**   

****
DP 式子很简单就不解释了，设 $f_{i,j}$ 表示将前 $i$ 个数分成 $j$ 组的方案数，则有

$$f_{i,j}=f_{i-1,j-1}+\left( j- \left\lfloor \frac{i-1}{m} \right\rfloor\right)f_{i-1,j}$$
经典起手，按行设生成函数 $F_i(x)=\sum_j f_{i,j}x^j$：
$$F_i(x)=xF_{i-1}(x) + xF_{i-1}'(x)- \left\lfloor  \frac{i-1}{m}\right\rfloor F_{i-1}(x)$$
使用**附加因子法**，添加一个 $t_i$，设 $F_i=G_it_i$：
$$G_it_i=\left( x-\left\lfloor  \frac{i-1}{m}\right\rfloor \right)G_{i-1}t_{i-1}+x(G_{i-1}'t_{i-1}+G_{i-1}t_{i-1}')$$
我们希望 $t_i$ 满足一定的性质，使得右式中只含有带 $G_{i-1}'$ 的项，而不含有 $G_{i-1}$，这就需要解微分方程

$$\left( x-\left\lfloor  \frac{i-1}{m}\right\rfloor \right)t_{i-1}+xt_{i-1}'=0$$
容易得到一个合适的特解为
$$t_{i-1}= \text e^{-x} x^{\lfloor (i-1)/m \rfloor}$$
这样关于 $G_i$ 的递推就能写为
$$G_i x^{\lfloor i/m \rfloor}= x G_{i-1}'  x^{\lfloor (i-1)/m \rfloor}$$
稍等，我们知道 $F_1=x$，所以 $G_1= x\text e^x$，也就能反推出 $G_0 = \text e^x$。

然后再来看这个递推，在 $\lfloor i/m \rfloor = \lfloor (i-1)/m\rfloor$，即 $i\in[km,(k+1)m-1]$ 时就会变为 $G_i=x G_{i-1}'$，否则变为 $G_i = G_{i-1}'$。所以我们可以写出：

$$G_{m-1}=\sum_{i=0}^\infty \frac{x^i}{i!} i^{m-1}$$
$$G_m=\sum_{i=1}^\infty  \frac{x^{i-1}}{i!}i^m$$

$$G_{2m}=\sum_{i=2}^\infty \frac{x^{i-2}}{i!}i^m(i-1)^{m}$$
你应该也发现了规律（$0\leq b < m$）：
$$G_{am+b}=\sum_{i=a}^\infty \frac{x^{i-a}}{i!} \left( i^{\underline a}\right)^m (i-a)^b$$
利用数学归纳法证明此式是容易的，这里就不展开写了。现在回到 $F$ 上去：
$$F_{am+b}=\text e^{-x}\sum_{i=a}^\infty \frac{x^i}{i!}\left( i^{\underline a}\right)^m (i-a)^b$$
使用 FFT 直接计算其前 $n$ 项系数即可，时间复杂度 $\Theta(n \log n)$。

[参考代码](https://atcoder.jp/contests/abc217/submissions/60596729)
****

能否进一步优化呢？显然，在 $n=m$ 时这个问题就变为求一行**第二类 Stirling 数**，这个问题目前还没有很好的解决方法，只能用 FFT 计算。对于弱化问题尚且如此，在原问题上就更加困难了。

另外我推完这个式子才发现似乎是有组合解释的，好像做麻烦了，呜呜。

---

## 作者：mojoege (赞：3)

## 题意

对于 $\forall k \in [1,n]$，求出把 $[1,n]$ 中的 $n$ 个整数分为非空的 $k$ 组, 每组任意两个数模 $m$ 不同余的方案数。

## 分析

前置知识：斯特林数。

先来考虑简单情况，把 $n$ 个数分成 $m$ 组有多少种情况？

可以定义 $dp_{i,j}$ 表示第 $i$ 个数之前分了 $j$ 组有多少种情况。basecase 为 $dp_{0,0}=1$。

转移分两种讨论：

- $i$ 单独开一组新的：$dp_{i,j}=dp_{i-1,j-1}$。

- 把 $i$ 放到前面的几组中：$dp_{i,j}=dp_{i-1,j} \times j$。乘上 $j$ 表示可以放到前 $j$ 组，每组 $dp_{i-1,j}$ 种情况。

回到原题，因为有了模数的限制，问题肯定出在放到前 $j$ 组的地方，那么要乘上多少呢？就是除了放了模数相同的数的组里。而我们已经知道前 $i-1$ 个数中与 $i$ 同余的数肯定不在一个格子内，而有  $\lfloor \frac{i-1}{m}\rfloor$ 个与 $i$ 同余的数，所以有 $j-\lfloor \frac{i-1}{m}\rfloor$ 组是合法的，可得最后式子为：
$$
dp_{i,j}=dp_{i-1,j-1}+dp_{i-1,j} \times (j-\lfloor \frac{i-1}{m}\rfloor)
$$
还有一点，在转移的时候记得将合法组数和 $0$ 取一个 $\max$，~~肯定不能取负的组数~~

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
int n, m;
int dp[5005][5005];

signed main(){
    cin >> n >> m;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= i; j++){
            dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
            dp[i][j] = (dp[i][j] + dp[i - 1][j] * max((j - (i - 1) / m), 0ll)) % mod;
        }
    }
    for (int i = 1; i <= n; i++) cout << dp[n][i] << endl;
    return 0;
}
```

---

## 作者：luogu_gza (赞：1)

考虑 dp。

记 $f_{i,j}$ 表示前 $i$ 个分成 $j$ 组的方案数。

转移我们考虑分为两种情况，新开一个组和并入之前的组，有意思的是因为同余的都是不同组的，所以可以直接计算出有多少种放置方案，由此可得方程 $f_{i,j}=f_{i-1,j-1}+(j-\lfloor \frac{i-1}{m} \rfloor)f_{i-1,j}$。

直接转移即可，不需要优化，时间复杂度 $O(n^2)$。

---

## 作者：WaterSun (赞：1)

# 思路

定义 $dp_{i,j}$ 表示将前 $i$ 个数，正好分为 $j$ 组的方案数。

那么，我们对 $i$ 号元素进行分类讨论：

1. 将 $i$ 放入原本就存在的组中，因为在同一个组中不能存在两个数 $x,y$，使得 $x \bmod m = y \bmod m$。所以对于 $i$，如果它是 $m$ 的倍数，则在 $1 \sim i - 1$ 中，与其模 $m$ 的值相同的有 $\frac{i}{m} - 1$ 个；否则，有 $\lfloor \frac{i}{m} \rfloor$ 个，并将此数记为 $x$。即，在剩下 $j - x$ 组中选出 $1$ 组来加入。由此，得到状态转移方程 $dp_{i,j} = dp_{i - 1,j} \times (j - x)$。

2. 将 $i$ 单独新开作一组，则与其它的元素无关，得状态转移方程 $dp_{i,j} = dp_{i - 1,j - 1}$。

综上，得状态转移方程：

$$
dp_{i,j} = dp_{i - 1,j} \times (j - x) + dp_{i - 1,j - 1}
$$

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 5010,mod = 998244353;
int n,m;
int dp[N][N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	dp[0][0] = 1;
	n = read();
	m = read();
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= i;j++){
			if (i % m != 0) dp[i][j] = dp[i - 1][j] * (j - i / m) % mod;
			else dp[i][j] = dp[i - 1][j] * (j - i / m + 1) % mod;
			dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
		}
	}
	for (re int i = 1;i <= n;i++) printf("%lld\n",dp[n][i]);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

不妨钦定组之间的顺序是最小值越小的组越靠前，这样可以给每个组按顺序编号。

设 $f_{i,j}$ 为考虑了模 $m$ 后 $< i$ 的数，目前有 $j$ 个非空组的方案数。

转移就是枚举模 $m = i - 1$ 的数新开了 $k$ 个组，设 $\le n$ 的数中模 $m = i - 1$ 的数有 $t$ 个，有转移：

$$f_{i,j} \gets f_{i-1,j-k} \times \binom{t}{k} \times \binom{j-k}{t-k} \times (t-k)!$$

意思就是从这 $t$ 个数中选出 $k$ 个数分到编号 $j - k + 1 \sim j$ 的组，在已有的 $j-k$ 个组中选 $t-k$ 个组给剩下不用新开一组的数放进去，顺序任意。

答案为 $f_{m,i}$。

时间复杂度 $O(n^2)$。

[code](https://atcoder.jp/contests/abc217/submissions/41271647)

---

## 作者：CQ_Bab (赞：1)

# 前言
有个同学说大家怎么都在写题解，乍一看发现他在 florr。
# 思路
一眼 Dp，那么我们先定义 $f_{i,j}$ 表示前 $i$ 个数分在 $j$ 组的方案数，然后我们可以进行分类讨论。

- 当 $i$ 自己开一组时 $f_{i,j}=f_{i-1,j-1}$。
- 当 $i$ 加入其他组时，因为在前面与他相同的有 $(i-1)\div m$ 个然后一共有 $j$ 组那么还剩下 $j-(i-1)\div m$ 组可以进入，所以 $f_{i,j}=(f_{i,j}+f_{i-1,\max(0,j-(i-1)\div m)}$。

最后答案即为所有的 $f_{n,i}$ 相加。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
const int N=5e3+10;
int f[N][N],n,m;
const int mod=998244353;
fire main() {
	cin>>n>>m;
	f[0][0]=1;
	rep(i,1,n) {
		rep(j,1,i) {
			f[i][j]=(f[i][j]+f[i-1][j-1])%mod; //分类讨论
			f[i][j]=(f[i][j]+f[i-1][j]*max((j-(i-1)/m),0ll))%mod;
		}
	}
	rep(i,1,n) cout<<f[n][i]<<endl;
	return false;
}

```

---

## 作者：封禁用户 (赞：1)

## 分析

定义状态函数 $\mathit{f}_{i,j}$ 表示将 $1$ 到 $i$ 分成 $j$ 组的满足条件的方案数。那么，对于一个数字 $i$，我们将有 $2$ 种分组情况：

1. 分到前面已经非空组里。
2. 分到一个新的空组里。

对于情况 $1$，由于我们不能将 $i$ 分到存在与 $i \bmod m$ 相同的数字所在的组里。所以我们在已经分好的 $j$ 组中，可以分到的组的数量为：$j-\lfloor \frac{i-1}{m} \rfloor$。因为每 $m$ 个数字必有一个与 $i$ 同余。情况一的转移方程即为：$\mathit{f}_{i,j}=\mathit{f}_{i,j}+(j-\lfloor \frac{i-1}{m} \rfloor)\times\mathit{f}_{i-1,j}$。

对于情况 $2$，我们直接给 $i$ 新开一组就行。但是要注意，新开的那一组是包含在 $j$ 组之中的，故转移方程为：$\mathit{f}_{i,j}=\mathit{f}_{i,j}+\mathit{f}_{i-1,j-1}$。

最后，对于分成 $k$ 组的答案，就是 $\mathit{f}_{n,k}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005,p=998244353;
int n,m;
long long f[N][N];//前i个数分j组的方案数
void solve(){
	scanf("%d%d",&n,&m),f[0][0]=1;
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=i;++j)
			f[i][j]=(f[i][j]+(j-(i-1)/m)*(f[i-1][j]))%p,
			f[i][j]=(f[i][j]+f[i-1][j-1])%p;
	for(register int i=1;i<=n;++i) printf("%lld\n",f[n][i]);
	return ;
}
int main(){
	return solve(),0;
}
```


---

## 作者：Mr_Gengar (赞：0)

#### Description
对于 $\forall k \in [1,n]$，求出把 $[1,n]$ 中的 $n$ 个整数分为非空的 $k$ 组，每组任意两个数模 $m$ 不同余的方案数。

两个方案不同，当且仅当存在两个数，一种方案中它们在同一组，但在另一种方案中，它们不同组。

对 $998244353$ 取模。

#### Solution
考虑进行 `dp`。

设 $f(i, j)$ 表示将前 $i$ 个数分为 $j$ 组，使每组中任意两个数均不同余的方案数。

我们分两种情况进行分类讨论。

第一种情况是将第 $i$ 个数单独作为新的一组，此时方案数为 $f(i-1, j-1)$。

第二种情况则是将第 $i$ 个数加入已存在的组中，此时组数不变，共有 $j$ 个组，但不能加入有同余数的组。考虑求出有同余数的组数。容易得到在前 $i-1$ 个数中有 $\lfloor \frac{i-1}{m} \rfloor$ 个数与 $i$ 同余，而我们又知道这些数一定被分在不同组中，所以最终就有 $j - \lfloor \frac{i-1}{m} \rfloor$ 个组可以被加入。在这种情况下，每个可以选择加入的组都会产生 $f(i-1,j)$ 的方案数。

最终可以得到状态转移方程为 $f(i,j)=f(i-1,j-1) + (j - \lfloor \frac{i-1}{m} \rfloor) \times f(i-1,j)$。

时间复杂度为 $O(n^2)$。

#### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int kMaxN = 5e3 + 1, kM = 998244353;

LL n, m, f[kMaxN][kMaxN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      f[i][j] = (f[i - 1][j - 1] + (j - (i - 1) / m) * f[i - 1][j] % kM) % kM;
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << f[n][i] << "\n";
  }
  return 0;
}
```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/AT_abc217_g)

## 思路

考虑 `dp`。

令 $dp_{i,j}$ 为前 $i$ 个数分为 $j$ 组的方案数。

则转移方程为：

$$dp_{i,j}=dp_{i-1,j-1}+dp_{i-1,j} \times (j-\lfloor \frac{i-1}{m}\rfloor)$$

下面来解释每项：

- $dp_{i-1,j-1}$：第 $i$ 个数自成一组，则方案数就是 $i-1$ 个数分 $j-1$ 个组。

- $dp_{i-1,j}$：第 $i$ 个数分进之前的组中去。

- $\lfloor \frac{i-1}{m}\rfloor$：之前 $i-1$ 个数中有多少个和 $i$ 同余。

- $j-\lfloor \frac{i-1}{m}\rfloor$：前 $j$ 个组中有多少个组中没有与 $i$ 同余的数。

根据转移方程递推即可。

时间复杂度 $O(n^2)$。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int kMaxN = 5e3 + 5;
const LL kP = 998244353;

int n, m;
LL dp[kMaxN][kMaxN];

int main() {
  cin >> n >> m, dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      dp[i][j] = (dp[i - 1][j - 1] + ((dp[i - 1][j] * (j - (i - 1) / m)) % kP)) % kP;
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << dp[n][i] << '\n';
  }
  return 0;
}
```

---

## 作者：apiad (赞：0)

这道题的 Dp 转移基于一个叫做斯特林数的东西。$dp_{i,j}$ 代表的是前 $i$ 个数，分成了 $j$ 组。对于两种情况：新加入一个组，那么是 $dp_{i,j} = dp_{i-1,j-1}$。不加入：$dp_{i,j}$ 加上贡献 $dp_{i-1,j} \times (j- \tfrac{i-1}{m})$。$j- \tfrac{i-1}{m}$ 代表的是他可以放的组别的个数。比较容易理解，按照这样转移即可。[link](https://atcoder.jp/contests/abc217/submissions/50746731)。

---

## 作者：Phobia (赞：0)

考虑二项式反演，设 $cnt_i$ 表示模 $m$ 结果为 $i$ 的数的个数，$f_{i}$ 表示分成**恰好** $i$ 组的方案数，$g_i$ 表示分成**至多** $i$ 组的方案数。

于是有 $g_i=\prod\limits_{j=0}^{m-1}A_i^{cnt_j}=\sum\limits_{j=1}^i\tbinom{i}{j}f_j$，由二项式反演可得 $f_i=\sum\limits_{j=1}^i\tbinom{i}{j}(-1)^{i-j}g_j$，注意这里求出来的 $f_i$ 是有标号的，所以答案还得除以 $i!$。

然后就做完了，当然也可以进一步优化，注意到本质不同的 $cnt$ 至多只有 $O(\sqrt{n})$，而后面求 $f$ 的部分可以 NTT 加速，可以做到 $O(n^\frac{3}{2})$，不过没有必要。

时间复杂度 $O\left(n^2+nm\right)$，空间复杂度 $O\left(n+m\right)$。

~~~cpp#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int maxn = 5005;
const int p = 998244353;

int n, m, fac[maxn], ifac[maxn], cnt[maxn], g[maxn];

int read()
{
	int res = 0, ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		;
	for (; isdigit(ch); ch = getchar())
		res = (res << 3) + (res << 1) + (ch & 15);
	return res;
}

int qpow(int x, int y)
{
	int res = 1;
	while (y)
	{
		if (y & 1)
			res = (i64)res * x % p;
		x = (i64)x * x % p;
		y >>= 1;
	}
	return res;
}

void init()
{
	fac[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = (i64)fac[i - 1] * i % p;
	ifac[n] = qpow(fac[n], p - 2);
	for (int i = n; i >= 1; --i)
		ifac[i - 1] = (i64)ifac[i] * i % p;
}

int A(int n, int m)
{
	if (n < m)
		return 0;
	return (i64)fac[n] * ifac[n - m] % p;
} 

int C(int n, int m)
{
	if (n < m)
		return 0;
	return (i64)fac[n] * ifac[m] % p * ifac[n - m] % p;
}

int main()
{
	n = read(), m = read();
	init();
	for (int i = 1; i <= n; ++i)
		g[i] = 1, ++cnt[i % m];
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j < m; ++j)
			g[i] = (i64)g[i] * A(i, cnt[j]) % p;
	}
	for (int i = 1; i <= n; ++i)
	{
		int ans = 0;
		for (int j = 1; j <= n; ++j)
			ans = (ans + (i64)((i - j & 1) ? -1 : 1) * C(i, j) * g[j]) % p;
		printf("%lld\n", (i64)(ans + p) * ifac[i] % p); 
	}
	return 0;
}
~~~

---

## 作者：gdf_yhm (赞：0)

[abc217g](https://www.luogu.com.cn/problem/AT_abc217_g)

### 思路

dp 题。

设 $f_{i,j}$ 表示前 $i$ 个数分到 $j$ 组的情况数。

两种转移：

- 新开一组。$f_{i,j}=f_{i-1,j-1}$。

- 加入之前的组。在 $i$ 之前与 $i$ 模 $m$ 余数相同的有 $\frac{i-1}{m}$ 个，剩下 $j-\frac{i-1}{m}$ 组可以加入。$f_{i,j}=f_{i-1,j}\times (j-\frac{i-1}{m})$。

最后答案为 $f_{n,i}$。

这也是斯特林数。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int maxn=5010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int f[maxn][maxn];

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();m=read();
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=f[i-1][j-1];
			if(j>=(i+1)/m)f[i][j]+=f[i-1][j]*(j-(i-1)/m);
			f[i][j]%=mod;
//			cout<<f[i][j]<<" ";
		}
//		cout<<"\n";
	}
	for(int i=1;i<=n;i++)printf("%lld\n",f[n][i]);
}
```


---

## 作者：_Flame_ (赞：0)

## 思路

很套路的一道 `DP`。

设 $dp_{i,j}$ 表示推到第 $i$ 个数时分成 $j$ 段。

对于每一个数，可以选择两种方案：

- 不加入前面的任何一个子集，自己新开一个子集，这时 $ dp_{i,j}=dp_{i-1,j-1} $。

- 加入已有的某个子集，这时设前面选过 $cnt$ 个模 $m$ 与 $i$ 同余的数，容易证明每个合法子集只能有一个模 $m$ 与 $i$ 同余的数，所以 $cnt$ 即为 $i$ 不能加入的子集数量，转移方程为 $dp_{i,j}=dp_{i-1,j}\times (j-cnt)$。

两种情况求和即为最终的情况总数。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=5010;
const int maxm=110;
const int mod=998244353;
const int inf=1e18;

int dp[maxn][maxn];

int cnt[maxn];

int n,m;

void init(){
	dp[0][0]=1;
}

void solve(){
	n=read(),m=read();
	init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dp[i][j]=dp[i-1][j-1];
			dp[i][j]=(dp[i][j]+(dp[i-1][j]*((j-cnt[i%m]+mod)%mod)%mod))%mod;
		}
		cnt[i%m]++;
	}
	for(int i=1;i<=n;i++){
		write(dp[n][i]%mod);
		puts("");
	}
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}

```

---

## 作者：luqyou (赞：0)

# ABC217G

## 题意

给出正整数 $n,m$，对于所有 $1 \le k \le n$，解决以下问题：

- 将 $n$ 个数放入 $k$ 个集合中，但是在 $\mod m$ 意义下相同的数不能放入同一个集合。问总方案数 $\mod 998244353$。

## 思路

令 $dp_{i,j}$ 为前 $i$ 个数放入 $j$ 组的方案数。

如果不考虑限制条件，那么显然转移方程就是 $dp_{i,j}=dp_{i-1,j-1} \times j$。

显然限制条件是会影响后面乘上的 $j$ 的。

那么我们在转移的时候记录一下放了多少个该数，记为 $cnt_i$，然后在转移的时候将转移的 $j$ 减掉 $cnt_{i \mod m}$ 就可以了。

时间复杂度 $O(n^2)$。

---

## 作者：Fracture_Dream (赞：0)

#### G - Groups

还是一道 `dp` 呢。

我们定义 $f(i, j)$ 表示分完前 $i$ 个数且当前分了 $j$ 个组。

考虑当前数的两种决策。

第一种，新开一个组，即方案数为 $f(i - 1, j - 1)$。

第二种，不开新的组而是丢进已存在的组，不难发现当前数可以丢入的组共有 $j - g(i, i \bmod m)$ 个，其中 $g(x, y) = \sum_{i = 1}^{x} [i \bmod m = y]$。

故可得，$f(i, j) = f(i - 1, j - 1) + f(i - 1, j) \times (j - g(i, i \bmod m))$。

初始状态为 $f(0, 0) = 1$。其他的比如 $g(x, y)$ 的转移啦、答案状态啦就很简单了嘛，时间复杂度 $O(n^2)$。


```cpp
#include <cstdio>

typedef long long LL;
LL Max(LL x, LL y) { return x > y ? x : y; }
LL Min(LL x, LL y) { return x < y ? x : y; }
LL Abs(LL x) { return x < 0 ? -x : x; }

int read() {
    int k = 1, x = 0;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar();
    }
    while (s >= '0' && s <= '9') {
        x = (x << 3) + (x << 1) + s - '0';
        s = getchar();
    }
    return x * k;
}

LL read_LL() {
    int k = 1;
	LL x = 0;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar();
    }
    while (s >= '0' && s <= '9') {
        x = (x << 3) + (x << 1) + s - '0';
        s = getchar();
    }
    return x * k;
}

void write(LL x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void print(LL x, char s) {
    write(x);
    putchar(s);
}

const int MAXN = 5e3 + 5;
const int mod = 998244353; 

int t[MAXN];
LL dp[MAXN][MAXN];

int main() {
	int n = read(), m = read();
	dp[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) 
			dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] * ((j - t[i % m] + mod) % mod) % mod) % mod;	
		t[i % m]++;	
	}
	for(int i = 1; i <= n; i++)
		print(dp[n][i], '\n');
	return 0;
}
```

---

## 作者：Acheron_RBM (赞：0)

很明显的动态规划。

设 $dp_{i,j}$ 为前 $i$ 个数分在第 $j$ 组的方案数，分类动规即可。

第一种状态转移方程很简单就是 $dp_{i,j}$ 等于 $dp_{i-1,j-1}$。

第二种会复杂一些是 $dp_{i,j}$ 等于 $dp_{i,j}+dp_{i-1,\max(0,\max(j-(i-1\div m)}$


```cpp
int main() 
{
	int n,m;
	cin>>n>>m;
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			dp[i][j]=(dp[i][j]+dp[i-1][j-1])%998244353;//i自己为一组时的状态转移方程 
			dp[i][j]=(dp[i][j]+dp[i-1][j]*max((j-(i-1)/m)*1ll,0ll))%998244353;//i要加入其他组时的状态转移方程 
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<dp[n][i]<<"\n";
	}
}
```

---

