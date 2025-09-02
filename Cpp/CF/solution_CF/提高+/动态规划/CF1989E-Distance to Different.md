# Distance to Different

## 题目描述

Consider an array $ a $ of $ n $ integers, where every element is from $ 1 $ to $ k $ , and every integer from $ 1 $ to $ k $ appears at least once.

Let the array $ b $ be constructed as follows: for the $ i $ -th element of $ a $ , $ b_i $ is the distance to the closest element in $ a $ which is not equal to $ a_i $ . In other words, $ b_i = \min \limits_{j \in [1, n], a_j \ne a_i} |i - j| $ .

For example, if $ a = [1, 1, 2, 3, 3, 3, 3, 1] $ , then $ b = [2, 1, 1, 1, 2, 2, 1, 1] $ .

Calculate the number of different arrays $ b $ you can obtain if you consider all possible arrays $ a $ , and print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
2 2```

### 输出

```
1```

## 样例 #2

### 输入

```
4 3```

### 输出

```
3```

## 样例 #3

### 输入

```
6 2```

### 输出

```
20```

## 样例 #4

### 输入

```
6 5```

### 输出

```
3```

## 样例 #5

### 输入

```
133 7```

### 输出

```
336975971```

# 题解

## 作者：TTpandaS (赞：16)

以题目给出的实例为例，当 $a=[\color{red}1,1,\color{green}2,\color{blue}3,3,3,3,\color{grey}1]$ 时，$b=[\color{red}2,1,\color{green}1,\color{blue}1,2,2,1,\color{grey}1]$。

更普遍的，若 $a=[1,\color{red}2,2,2,2,2,2,2,\color{black}1]$，则 $b=[1,\color{red}1,2,3,4,3,2,1,\color{black}1]$。

具体的，如果 $a$ 中存在长度为 $n$ 的相同段，那么 $b$ 中对应位置一定是 $1,2,3,...,\dfrac{n}{2},\dfrac{n}{2}-1,..,1$。可以发现，如果确定了一段的起始，那么在 $b$ 中整段就已经是确定的了。

所以问题转化成了将 $n$ 个数分成至少 $k$ 个段，求方案数。

设 $dp_{i,j}$ 表示将前 $i$ 个数分成 $j$ 段的方案数，则 $dp_{i,j+1}=\sum_{p=1}^{i-1}dp_{p,j}$。但是考虑当 $i>2 \wedge i \not= n $ 时，如果 $b_{i-1}=1 \wedge b_i=1$，则不能确定它是被分成 $1,\color{red}1$ 还是 $\color{blue}1,1$，所以需要减去 $dp_{i-2}{j}$。

另外，由于答案是求将 $n$ 个数分成至少 $k$ 个段的方案数，所以每次将 $dp_{i,k+1}$ 加在 $dp_{i,k}$ 上即可，这样分成大于 $k$ 个段的答案全部记录在了 $dp_{i,k}$ 上。

最后答案就是 $dp_{n,k}$。

---

## 作者：聪明的乖宝宝 (赞：14)

# 题目大意
数组 $ a $ 的长度为 $ n $ 且 $ 1,2,\dots,k $ 在 $ a $ 中均出现过。

数组 $ b $ 由数组 $ a $ 求得，元素 $ b_i $ 表示与 $ a_i $ 最近的与 $ a_i $ 不相等的数的距离。

现给两个整数 $ n $ 和 $ k $ 问能构造出多少种 $ b $ 。
# 思路
通过观察题目中给的例子，可以发现，若我们把 $ a $ 数组按照元素分为若干段，例如：

$$
1,1,1,4,4,4,3,2,2,1,1,1
$$

可以分为

$$
1,1,1
$$

$$
4,4,4
$$

$$
3
$$

$$
2,2
$$

$$
1,1,1
$$

这五段，我们把每一段的长度去除构成一个 $ c $ 序列，如上例为

$$
3,3,1,2,3
$$ 

我们可以发现，对应的数组 $ b $ 为：

$$
3,2,1,1,2,1,1,1,1,1,2,3
$$

更直观地，我们写成

$$
3,2,1\\ 1,2,1\\1\\1,1\\1,2,3
$$

我们可以发现，数组 $ b $ 只与数组 $ c $ 有关，而与数组 $ a $ 中具体的元素无关。

但是，通过观察，我们发现数组 $ b $ 与数组 $ c $ 并不是一一对应的，因为如果数组 $ c $ 出现了 $ 2 $ 如果这个 $ 2 $ 不是数组的第一个元素或者最后一个元素，那么它与 $ c $ 中连续出现两个 $ 1 $ 是等价的，在数组 $ b $ 中均会被转化成 $ 1,1 $ 。

故，问题就转化成了，将一个长度为 $ n $ 的区间化分成不少于 $ k $ 段，其中仅有区间的两端可以出现长度为 $ 2 $ 的段，有多少种这样的划分方案。

这样，由于 $ k $ 的值非常小，故可以采用时间复杂度为 $ O(nk) $ 的递推。
# 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=200010;
int n,k;
long long p=998244353;
long long f[N][12],sum[N][12];
int main()
{
    cin>>n>>k;
    f[0][0]=sum[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        sum[i][0]=1;
        for(int j=1;j<=k;j++)
        {
            f[i][j]=sum[i-1][j-1];
            if(i>2&&i!=n)f[i][j]-=f[i-2][j-1];
            f[i][j]+=p;
            f[i][j]%=p;
            sum[i][j]=sum[i-1][j]+f[i][j];
            sum[i][j]%=p;
        }
        f[i][k+1]=sum[i-1][k]+sum[i-1][k+1];
        if(i>2&&i!=n)f[i][k+1]-=(f[i-2][k]+f[i-2][k+1]);
        f[i][k+1]+=p;
        f[i][k+1]%=p;
        sum[i][k+1]=sum[i-1][k+1]+f[i][k+1];
        sum[i][k+1]%=p;
    }
    cout<<(f[n][k]+f[n][k+1])%p;
}

```

---

## 作者：2huk (赞：6)

> 称长度为 $n$ 的正整数序列 $a$ 是合法的，当且仅当 $1 \le a_i \le k$ 且 $1 \sim k$ 在 $a$ 中都有出现。
>
> 令 $b_i = \min_{a_j \ne a_i} |j-i|$。求所有合法 $a$ 对应的 $b$ 有多少种。
>
> $n \le 2 \times 10^5$，$k \le 10$。

~~这个 $k$ 的范围很诈骗啊。~~

考虑对于一个确定的 $a$，它的 $b$ 长什么样子。比如：

$$
a = \{\color{red}1,1,1,\color{blue}2,2,2,\color{green}3,\color{orange}4,\color{purple}5,5,5,5,5,\color{grey}6,6 \color{black}\} \\
b = \{\color{red}3,2,1,\color{blue}1,2,1,\color{green}1,\color{orange}1,\color{purple}1,2,3,2,1,\color{grey}1,2\}
$$

可以发现，除开头结尾外，每一个 $a$ 中长 $k$ 的极长连续段，在 $b$ 中都形如 $1,2,\dots,k/2,\dots,2,1$。而开头是 $k,k-1,\dots,1$，结尾是 $1,2,\dots,k$。

也就是说 $b$ 的形态只和 $a$ 中每个极长连续段的长度有关。

这里有一个小细节：如果 $a$ 中有长 $2$ 的极长连续段，那么对应到 $b$ 中是 $1,1$，这和**两个长 $1$ 的极长连续段**在效果上是相同的。而我们只需要计 $b$ 的形态数，所以我们在后续处理中，默认 **$a$ 中不存在长 $2$ 的极长连续段**。

别忘了还有一个限制是 $a$ 中 $1 \sim k$ 都出现过至少一次。不难发现，只要 $a$ 中的极长连续段**数量** $\ge k$ 就能满足这个条件。

于是可以愉快的 DP 啦！设 $f(i, j)$ 表示考虑前 $i$ 个位置，且 $i$ 是第 $j$ 个极长连续段的结尾。转移枚举上一个连续段的结尾的位置 $k$。注意**如果这一段不是第一段且不是最后一段**需要满足 $i-k \ne 2$。

答案为 $\sum_{j=k}^n f(n, j)$。因为段数要 $\ge k$。

转移可以前缀和优化成 $\mathcal O(1)$。但是状态数是 $\mathcal O(n^2)$ 的。考虑优化。

别忘了 $k$ 很小！所以求段数 $\ge k$ 复杂度不能接受，但是可以求段数 $<k$ 的方案数。用全集减一下就行。

这里的全集指 $\sum_{j=2}^n f(n,j)$。$j$ 从 $2$ 开始是因为**如果 $a$ 全部相同则 $b$ 无法定义**。

考虑怎么求全集。很简单，再做一遍上面的 DP，并直接把第二维去掉即可。

复杂度 $\mathcal O(nk)$。

- 前缀和优化前：<https://codeforces.com/contest/1989/submission/291168277>
- AC：<https://codeforces.com/contest/1989/submission/291168850>

---

## 作者：vme50xiex2 (赞：6)

令 $c_i = [a_i \neq a_{i-1}]$，特殊的，令 $c_1 = 0$。

显然对于两个 $a$，$c$ 不同是 $b$ 不同的必要条件。因为 $c$ 已经能够表达出每个 $i$ 离它最近的不同的 $j$ 在哪了。

而这个是不是冲要的呢，打表或者观察可以发现，如果 $a$ 在中间出现了某个长为 $2$ 的连续段，那么这和出现两个不同的数是本质相同的。也就是在 $c$ 中 $[1,0,1]$ 和 $[1,1,1]$ 是本质相同的。那么只要钦定 $c$ 中不出现 $[1,0,1]$，再保证 $c$ 中 $1$ 至少出现了 $k-1$ 次（$c_1 = 0$ 没有统计），这样 $b$ 和 $c$ 就形成双射了。

设 $f(i,x,y,j)$ 表示前 $i$ 位，第 $i$ 位和第 $i-1$ 位分别为 $x$ 和 $y$，出现了 $j$ 个 $1$（对 $k-1$ 取 $\min$），直接转移即可。时间复杂度 $\mathcal{O}(nk)$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
const int MOD = 998244353;
int n, k;
ll f[N][2][2][15];
int main() {
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	cin >> n >> k;
	f[1][0][0][1] = 1;
	for(int i = 2; i <= n; ++i)
		for(int x : {0, 1}) for(int y : {0, 1}) 
			for(int j = 1; j <= k; ++j) if(f[i - 1][x][y][j]) 
			for(int z : {0, 1}) {
				if(x && !y && z) continue;
				int nj = min(k, j + z);
				(f[i][y][z][nj] += f[i - 1][x][y][j]) %= MOD;
			}
	ll ans = 0;
	for(int x : {0, 1})
		for(int y : {0, 1}) ans += f[n][x][y][k];
	printf("%lld\n", ans % MOD);
	return 0;
}
```

---

## 作者：Moeebius (赞：6)

注意到合法的 $b$ 一定形如：

$$
\red{p, p-1,\cdots,1},\blue{1,\cdots,(q-1),q,(q-1),\cdots,1},\orange{1,\cdots ,o,o,\cdots,1},1,\cdots,w
$$

并且按照如上标准应该要能划分成至少 $k$ 段。

记 $f_{i,j}$ 表示前 $i$ 位分 $j$ 段的方案数（$j$ 对 $k+1$ chkmin）。转移是显然的，使用前缀和优化。

一些细节：
- 如果 $i\neq 2 \land i \neq n$，那么最后一段长度 **不能** 为 $2$，因为 $\orange{1, 1}$ 和 $\red{1}, \blue{1}$ 不可区分。
- 但是如果 $i = 2 \lor i = n$ 是可以的，因为此时 $b$ 会变成 $2, 1$ 或者 $1, 2$。

---

## 作者：DE_aemmprty (赞：3)

## $\textup{Part 1. }$观察范围，经典转化

首先，我们容易注意到 $k \leq 10$。因此，我们可以初步判断此题的时间复杂度为 $\mathcal{O}(nk)$ 左右。这个复杂度一般是 DP，而且这道题让我们对一个排列计数，显然更有可能是 DP 了。当然，不排除普通的组合计数或者进一步的转化。

然后，老样子，我们可以先手玩一下样例，也就是对于一个数组 $a$，它是怎么生成 $b$ 的。

拿题面的例子，如果 $a=[1,1,2,3,3,3,3,1]$，那么有 $b=[2,1,1,1,2,2,1,1]$。我们发现，由于 $b_i$ 是 $a$ 数组中离 $a_i$ 最近的，与 $a_i$ 不同的数的距离，所以 $b_i$ 在 $a$ 的相同数的联通块中十分有规律。显然，这个规律是形如 $1, 2, 3, \cdots, p - 1, p, p - 1, \cdots, 3, 2, 1$ 或者 $1, 2, 3, \cdots, p - 1, p, p, p - 1, \cdots, 3, 2, 1$ 状物的东西。（但是要注意开始和结束两个联通块，这时不太一样）所以，这个 dp 肯定与联通块有很大的关系。我们肯定要在 dp 中，枚举最后一段联通块的大小。这样，我们对这道题有了一个初步认知。

**进展 1：这道题应该是 $\mathcal{O}(nk)$ 的二维 DP，且与联通块有关。**

## $\textup{Part 2. }$考虑题目限制，设计 DP 状态

这么一看，我们发现这道题好像与 $k$ 没有太大的关系，因为 $b$ 的生成应该只与联通块有关。而 $k = 2$ 的情况已经可以囊括所有联通块的分布情况。

但是我们仔细看题，发现题目有一个要求：$a$ 数组中必须出现 $1$ 到 $k$ 的所有数。考虑怎么处理，我们容易发现，这种情况其实只是相当于限制了联通块的个数必须 $\geq k$，本质上和 $k = 2$ 确实没有差别。

于是考虑 $dp$，设 $dp_{i, j}$ 表示对于前 $i$ 个数，有 $j$ 个联通块，$b$ 的数量有多少。转移是显然的，我们暴力枚举最后一个联通块的大小即可。前缀和优化可以做到 $\mathcal{O}(nk)$。

**进展 2：我们设计了 DP 状态，且疑似完成了此题。**

## $\textup{Part 3. }$注意细节，DP 去重

但，其实还没有结束，我们其实还有一个问题一直没有考虑：$b$ 序列和 $a$ 的联通块生成方式真的是一一对应的吗？考虑反证这一点。

我们先考虑在中间的联通块。我们发现，对于这些联通块，它们对应的 $b$ 数组一定是以 $1$ 开头，以 $1$ 结尾的。这样的话，如果有两个生成情况对应一种 $b$，且生成情况恰好在中间的联通块时不同，由于 $\text{len} > 2$ 的联通块一定有非 $1$ 的数，也就是说，一定会有一个联通块对应的 $b$，它的开头不是 $1$ 或者结尾不是 $1$。但是，$\text{len} = 2$ 时，这个联通块显然能拆分成两个大小为 $1$ 的联通块。这个去重很好解决，直接不让枚举的联通块大小为 $2$ 就行。

再来考虑两边的联通块。这时候，类似的，$\text{len} > 1$ 的联通块一定有非 $1$ 的数，而 $\text{len} = 1$ 的联通块又不可能被拆分，因此开头和结尾确实是不会有问题的。

因此，我们还要在 DP 的转移过程中，注意大小为 $2$ 的联通块的处理以及首尾即可。

```cpp
/*******************************
| Author:  DE_aemmprty
| Problem: Distance to Different
| Contest: Luogu
| URL:     https://www.luogu.com.cn/problem/CF1989E
| When:    2025-01-17 09:07:19
| 
| Memory:  500 MB
| Time:    2000 ms
*******************************/
#include <bits/stdc++.h>
using namespace std;

long long read() {
    char c = getchar();
    long long x = 0, p = 1;
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') p = -1, c = getchar();
    while (c >= '0' && c <= '9')
        x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return x * p;
}

const int N = 2e5 + 7;
const long long mod = 998244353;

int n, k;
long long dp[N][13], f[N][13];

void solve() {
    n = read(), k = read();
    dp[0][0] = 1;
    f[0][0] = 1;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= k + 1; j ++) {
            dp[i][j] = dp[i - 1][j - 1];
            if ((i == 2 || i == n) && i >= 2)
                (dp[i][j] += dp[i - 2][j - 1]) %= mod;
            if (i >= 3)
                (dp[i][j] += f[i - 3][j - 1]) %= mod;
            if (j == k + 1) {
                (dp[i][j] += dp[i - 1][j]) %= mod;
                if ((i == 2 || i == n) && i >= 2)
                    (dp[i][j] += dp[i - 2][j]) %= mod;
                if (i >= 3)
                    (dp[i][j] += f[i - 3][j]) %= mod;
            }
            f[i][j] = (f[i - 1][j] + dp[i][j]) % mod;
        }
        f[i][0] = 1;
    }
    cout << (dp[n][k] + dp[n][k + 1]) % mod << '\n';
}

signed main() {
    int t = 1;
    while (t --) solve();
    return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

对于一个长度为 $n$ 的序列 $a$，定义 $a$ 的生成序列 $b$ 为一个长度为 $n$ 的序列，且满足：

$$
b_i = \min_{j\in[1,n], a_i\neq a_j} |i-j|
$$

我们称一个序列是好的，当且仅当值域**恰好**为 $[1,k]$。你需要求所有长度为 $n$ 的好的序列的生成序列数量。相同的序列仅计算一次。

$2\leq n\leq 2\times 10^5,2\leq k\leq\min(n,10)$。

## 思路

先来考虑长度为 $n$ 的序列的生成序列数量，由于 $b_i$ 的意义其实是 $a_i$ 到最近的与 $a_i$ 不同的 $a_j$ 的距离，所以对于一个长度为 $L$ 的颜色段，$b_i$ 应当形如 $1,\cdots,\lfloor\frac{L}{2}\rfloor,\lceil\frac{L}{2}\rceil,\cdots,1$。特别地，若颜色段位于开头或结尾，则为 $L,L-1,\cdots,1$ 以及 $1,2,\cdots,L$。这启示我们将 $b$ 划分为若干段，则每一段对应 $a$ 的颜色段，且 $b$ 中该段的填数只和 $L$ 和是否位于开头结尾有关。

dp，设 $F(i)$ 表示长度为 $i$ 的序列的生成序列数量，不难有转移：

$$
F(i)=\sum_{k=0}^{i-1} F(k)
$$

这样会算重，原因是对于不为首尾的长度为 $2$ 的段，则形如 $1,1$，和两个长度为 $1$ 的段一致，所以需要排除这种情况：

$$
F(i)=\sum_{k=0}^{i-1}[i=1\lor i=n\lor k-i\neq 2] F(k)
$$

用前缀和优化转移，时间复杂度 $O(n)$。

然后考虑值域的限制，只需要将序列分成至少 $k$ 段即可，只需要在 $F$ 的基础上加一维表示划分的段数即可。

时间复杂度 $O(n^2)$，考虑优化，改为用全集减去分成少于 $k$ 段的方案即可做到 $O(nk)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

const int N = 2e5 + 5;
int n, k, dp[N], f[N][15], g[N][15], sumt[N];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> k;
    dp[0] = sumt[0] = 1;
    for(int i=1;i<=n;i++){
        dp[i] = sumt[i - 1];
        if(i >= 2 && i != 2 && i != n) dp[i] = Sub(dp[i], dp[i - 2]);
        sumt[i] = Add(sumt[i - 1], dp[i]);
    }
    f[0][0] = g[0][0] = 1;
    for(int i=1;i<=n;i++){
        g[i][0] = g[i - 1][0];
        for(int j=1;j<=min(k-1,i);j++){
            f[i][j] = g[i - 1][j - 1];
            if(i >= 2 && i != 2 && i != n) f[i][j] = Sub(f[i][j], f[i - 2][j - 1]);
            g[i][j] = Add(g[i - 1][j], f[i][j]);
        }
    }
    int ans = 0;
    for(int i=1;i<k;i++) ans = Add(ans, f[n][i]);
    cout << Sub(dp[n], ans) << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：lfxxx (赞：1)

先考虑如何区分不同的 $b$ 再判断能否构造合法 $a$。

对于一个 $a$ 我们可以提取其中所有极长颜色连续段，那么一个长度为 $len$ 的极长段在 $b$ 数组中一定形如从 $1$ 开始先依次递增再依次递减的一段，我们发现，除了中间的两个长度为 $1$ 的段会与一个长度为 $2$ 的段混淆外，其余情况均可以区分，再来判断是否合法，不难发现，只要段数大于等于 $k$ 一定合法，也就是放两个 $1$ 比放一个 $2$ 更容易合法，考虑钦定中间不能放一个 $2$，容斥减去其贡献即可做到 $O(n \times k)$。


```cpp
 #include<bits/stdc++.h>
 #define int long long
 using namespace std;
 const int mod = 998244353;
const int maxn = 2e5+114;
int n,k;
int cnt[20],dp[20][maxn];
signed main(){
    cin>>n>>k;
    cnt[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=min(i,k);j++){
            dp[j][i]=(j!=k?cnt[j-1]:(cnt[j-1]+cnt[j])%mod)%mod;
            if(i>=2){
                dp[j][i]=(dp[j][i]+mod-(j!=k?dp[j-1][i-2]:(dp[j-1][i-2]+dp[j][i-2])%mod))%mod;
            }
            if(i==n){
                dp[j][i]=(dp[j][i]+(j!=k?dp[j-1][i-2]:(dp[j-1][i-2]+dp[j][i-2])%mod))%mod;
            }
        }
        for(int j=1;j<=k;j++) cnt[j]=(cnt[j]+dp[j][i])%mod;
    }
    cout<<dp[k][n]<<'\n';
    return 0;
}

```

---

## 作者：newwzl (赞：1)

一个时间复杂度稍高并且有点神金的方法。

# 思路

可以轻易想到，要想使 $b$ 不重复且合法，我们要求 $a$ 满足下述条件：

- 除了开头结尾的，连续且相同的数字个数不可以为 $2$ 个。

- 至少有 $k$ 个连续且相同的数字段。

先不考虑第二个条件，并且只考虑除了 $a$ 中开头和结尾的连续段的其余部分，我们可以定义 $f_i$ 表示长度为 $i$ 的序列中，结尾连续且相同的数字个数 $\geq 3$ 的序列有多少种。特别的，$f_0$ 为 $1$。再定义一个前缀和 $sum$。然后转移如下：

$$f_i=f_{i-1}+sum_{i-3}$$

因为不考虑第二个条件，此时答案为 $\sum_{i=2}^n (i-1)\times s_{n-i}$，$i$ 枚举的是 $a$ 数组开头结尾连续且相同的数字个数之和。

答案只需要减去连续且相同的数字段数小于 $k$ 的情况即可。

此时，需要枚举 $a$ 数组开头结尾连续且相同的数字个数之和、除去开头结尾相同数字段数、除去开头结尾相同数字长度为一的段数。需要用点基本的组合数，具体看代码。

时间复杂度 $O(NK^2)$。

# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,mod=998244353;
int n,k;
int f[N],s[N];
int ans;
int fac[N]={1},inv[N]={1};
int power(int a,int b){int ret=1,num=a%mod;while(b){if(b&1)ret=ret*num%mod;num=num*num%mod;b>>=1;}return ret;}
int C(int down,int up){if(up<0||up>down||down<0)return 0;return fac[down]*inv[up]%mod*inv[down-up]%mod;}
signed main(){
	for(int i=1;i<=2e5+8;i++){fac[i]=fac[i-1]*i%mod;inv[i]=power(fac[i],mod-2);}
	cin>>n>>k;f[0]=1;s[0]=1;
	for(int i=1;i<=n;i++){
		if(i>=3){
			f[i]=(f[i-1]+s[i-3])%mod;
		}
		s[i]=(s[i-1]+f[i])%mod;
	}
	for(int i=2;i<=n;i++){
		ans=(ans+(i-1)*s[n-i])%mod;
	}
	for(int i=2;i<n;i++){//首尾段总长度
		int len=n-i;
		for(int j=1;j+2<k&&j<=len;j++){//中间段数
			for(int one=0;one<=j;one++){//长度为1的段数
				if(one==j){
					if(j==len){
						ans=(ans-(i-1))%mod;
					}
					continue;
				}
				ans=(ans-C(len-one-2*(j-one)-1,j-one-1)*C(j,one)%mod*(i-1))%mod; //第一个组合数表示去除所有长度为1的段后每个段长度至少为3时有多少种情况，第二个是算长度为1的段的位置有多少种
			}
		}
	}
	if(k>=3)ans=(ans-n+1)%mod;
	ans=(ans+mod)%mod;
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：w9095 (赞：1)

[CF1989E Distance to Different](https://www.luogu.com.cn/problem/CF1989E)

好题。题目要求 $b$ 数组的数量，但 $b$ 数组难以直接计算，而 $b$ 数组和 $a$ 数组的映射关系并不明显。考虑分析 $b$ 的性质，并映射到其他数组。

我们发现，$b$ 数组与 $a$ 数组中元素的具体数值无关，只与 $a$ 数组中元素的不等关系有关。因此，我们考虑把 $b$ 数组映射到一个反映 $a$ 数组中元素的不等关系的数组。

记 $c_i=[a_i\ne a_{i-1}]$，特别的，不难发现 $c_1=0$。考虑将 $b$ 数组映射到 $c$ 数组。题目中要求 $k$ 个元素至少出现一次，所以至少有 $k-1$ 个 $c_i$ 等于 $1$。若至少有 $k-1$ 个 $c_i$ 等于 $1$，则一定可以构造出一个 $a$ 数组满足条件，每次不同时换新的元素即可。因此，这个 $c$ 数组是可行的，对应的 $b$ 数组也是可行的。

但是，$b$ 数组和 $c$ 数组并不是严格的双射关系。$c=[1,0,1]$ 和 $c=[1,1,1]$ 时，$b$ 数组均为 $[1,1,1]$。因此，我们需要强制舍去其中一种情况以保证双射。由于至少有 $k$ 个 $c_i$ 等于 $1$，显然应该舍去 $[1,0,1]$，这样可以获得更多的 $c_i=1$，否则可能无法满足条件。

最后，我们使用动态规划计算满足条件的 $c$ 数组数量。设状态 $f[i][j][k][l]$ 表示第 $i$ 个位置，前 $1$ 位为 $j$，这一位为 $k$，一共出现 $l$ 个 $c_i=1$ 的情况，显然有如下转移方程：

$$f[i][j][0][l]=f[i][j][0][l]+f[i-1][p][j][l]$$

$$f[i][j][1][l]=f[i][j][1][l]+f[i-1][p][j][l-1](p\ne1\lor j\ne0)$$

初始 $f[1][0][0][0]=1$，目标 $\sum_{i=0}^{1}\sum_{j=0}^{1}f[n][i][j][k-1]$。

时间复杂度 $O(nk)$，代码中采用了另一种转移方式。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long k,n,f[200001][2][2][11],ans=0;
const long long mod=998244353;
int main()
{
    scanf("%lld%lld",&n,&k);
    f[1][0][0][0]=1;
    for(int i=2;i<=n;i++)
        for(int j=0;j<=1;j++)
            for(int l=0;l<=1;l++)
                for(int p=0;p<=k-1;p++)
                    for(int q=0;q<=1;q++)
                        {
                        if(j==1&&l==0&&q==1)continue;
                        if(p+q>=k)f[i][l][q][k-1]+=f[i-1][j][l][p],f[i][l][q][k-1]%=mod;
                        else f[i][l][q][p+q]+=f[i-1][j][l][p],f[i][l][q][p+q]%=mod;
                        }
    for(int i=0;i<=1;i++)
        for(int j=0;j<=1;j++)
            ans+=f[n][i][j][k-1],ans%=mod;
    printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：nxd_oxm (赞：0)

注意到我们可以将 $a$ 分成若干极长子段，每段元素相同。举个例子，当 $a=[1,2,3,3,4,2,2]$ 时，可以将 $a$ 分成 $[1],[2],[3,3],[4],[2,2]$。

容易推出，不管每段元素是什么，只需要知道划分方式就可以推出唯一的 $b$。如下。


$$a=[[2],[2],[2]],b=[2,1,1,1,1,2]$$

$$a=[[2],[1],[1],[2]],b=[2,1,1,1,1,2]$$

其中 $[x]$ 表示一个长度为 $x$ 的极长子段。

唯一的特殊情况是当划分成长度为 $2$ 的字段时对应的 $b$ 是 `1 1`，就有可能是两个长度为 $1$ 的子段贡献出来的答案。所以我们不能统计形如 $[2]$ 的子段，用两个 $[1]$ 段统计答案就正好不重不漏。但是我们发现 $[2]$ 段在序列的最前或最后时，答案是不会被算重的，需要加上特判。

于是我们可以列出 dp：设 $dp_{i,j}$ 表示前 $i$ 个数分成 $j$ 个极长子段的方案数。显然，这样的状态数是 $\mathcal{O}(n^2)$ 的，需要优化。

题目说 $a$ 中需要 $1\sim k$ 的数都出现，显然至少需要 $k$ 段极长子段。而我们并不关心极长子段的个数在 $k$ 以上时到底有多少段，可以将 $\sum_{j=k}^{n}dp_{i,j} $ 中的数合并到 $dp_{i,k}$ 中去统一转移。

初始化：

$$dp_{i,1}=1$$

转移：

$$sum_{i,j}=sum_{i-1,j}+dp_{i,j}$$

$$dp_{i,j}=dp_{i-1,j-1}+sum_{i-3,j-1}$$

特别的，

$$dp_{i,k}=dp_{i-1,k-1}+sum_{i-3,k-1}+dp_{i-1,k}+sum_{i-3,k}$$

以及，

$$dp_{n,j}=sum_{n-1,j-1}$$

$$dp_{n,k}=sum_{n-1,k-1}+sum_{n-1,k}$$

时间复杂度 $\mathcal{O}(nk)$。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(long long i=j;i<=n;i++)
#define updmax(a,b) a=max(a,b)
#define updmin(a,b) a=min(a,b)
#define updsum(a,b) a=((a+b)%mod+mod)%mod
#define pb push_back
using namespace std;
const int N=2e5+10;
const int mod=998244353;
int n,k,dp[N][20],sum[N][20];
void gs(){
	cin>>n>>k;
	dp[0][0]=1;
	sum[0][0]=1;
	f(i,1,n){
		dp[i][1]=1;
		f(j,2,k){
			updsum(dp[i][j],dp[i-1][j-1]);
			if(i!=n&&i-3>=0)updsum(dp[i][j],sum[i-3][j-1]);
			else if(i==n&&i-2>=0)updsum(dp[i][j],sum[i-2][j-1]);
			if(j==k){
				updsum(dp[i][j],dp[i-1][j]);
				if(i!=n&&i-3>=0)updsum(dp[i][j],sum[i-3][j]);
				else if(i==n&&i-2>=0)updsum(dp[i][j],sum[i-2][j]);
			}
		}
		f(j,0,k){
			sum[i][j]=(sum[i-1][j]+dp[i][j])%mod;
		}
	}
	cout<<dp[n][k]<<endl;
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	gs();
	return 0;
}
```

---

