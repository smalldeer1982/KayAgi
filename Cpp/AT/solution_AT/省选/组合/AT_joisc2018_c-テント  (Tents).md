# テント  (Tents)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2018/tasks/joisc2018_c



# 题解

## 作者：DaiRuiChen007 (赞：3)

# JOISC2018C 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2018_c)

**题目大意**

> $n\times m$ 的网格上选若干个（至少一个）格子染色并指定上下左右，满足任意两个同行或同列的格子的朝向必须相对。
>
> 数据范围：$n,m\le 3000$。

**思路分析**

设 $dp_{i,j}$ 表示 $i\times j$ 网格上的答案，考虑第 $i$ 行的情况：

- 第 $i$ 行无黑格：从  $dp_{i-1,j}$ 转移。
- 第 $i$ 行有一个黑格，设在第 $x$ 列：
  - 若第 $x$ 列只有一个黑格：那么第 $i$ 行的黑格有 $j$ 种位置和 $4$ 种朝向，从 $4\times j\times dp_{i-1,j-1}$ 转移。
  - 若第 $x$ 列有两个黑格：显然两个黑格相对，那么选定两个黑格的位置后不能选朝向，且同行不能选其他黑格，从 $(i-1)\times j\times dp_{i-2,j}$ 转移。
- 若第 $i$ 行有两个黑格：显然对应两列不能放其他黑格，从 $\dfrac{j(j-1)}2\times dp_{i-1,j-2}$ 转移。

因此得到状态转移方程：
$$
dp_{i,j}=dp_{i-1,j}+4\times j\times dp_{i-1,j-1}+(i-1)\times j\times dp_{i-2,j}+\binom j2\times dp_{i-1,j-2}
$$
时间复杂度 $\mathcal O(nm)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=3001,MOD=1e9+7;
int dp[MAXN][MAXN];
signed main() {
	int n,m;
	scanf("%lld%lld",&n,&m);
	for(int i=0;i<=max(n,m);++i) dp[0][i]=dp[i][0]=1;
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) {
		dp[i][j]=(dp[i-1][j]+4*j*dp[i-1][j-1])%MOD;
		if(i>1) dp[i][j]=(dp[i][j]+(i-1)*j%MOD*dp[i-2][j-1]%MOD)%MOD;
		if(j>1) dp[i][j]=(dp[i][j]+j*(j-1)/2%MOD*dp[i-1][j-2]%MOD)%MOD;
	}
	printf("%lld\n",(dp[n][m]+MOD-1)%MOD);
	return 0;
}
```



---

## 作者：cosf (赞：0)

考虑大力 dp。

如果某一个点和其他所有的点都不共行或者共列，则这个点有 $4$ 种情况。

除了这些点，若两个点共行或共列，则它们的内容是定好的了，就不需要考虑它们的内容的种类了。

我们令 $f_{i, j}$ 表示在 $i \times j$ 的表格上不含单点地填数，则答案为 $\sum_{k = 0}^{\min\{n, m\}}4^k \times\frac{1}{k}\times A_n^k\times A_m^k \times f_{n - k, m - k}$。

接下来考虑如何转移。

首先，$f_{i, j}$ 必然包含 $f_{i - 1, j}$ 和 $f_{i, j - 1}$ 的情况，由容斥原理，所有的 $f_{i, j}$ 初始值为 $f_{i - 1, j} + f_{i, j - 1} - f_{i - 1, j - 1}$。特别地，若 $i = 0$ 或 $j = 0$，则 $f_{i, j} = 1$。

接下来考虑其他情况。

第一种。

![](https://cdn.luogu.com.cn/upload/image_hosting/yr2t5m6m.png)

如图，如果右下角有棋子，那么蓝色底下或者绿色的右边必然有棋子，否则红棋就是单点。

如果是蓝色的，那么有

$$
f_{i, j} \overset{+}{\gets} (j - 1)f_{i - 1, j - 2}
$$

绿色的则是

$$
f_{i, j} \overset{+}{\gets}(i-1)f_{i - 2, j - 1}
$$

第二种。

如图，右下角没有棋子，则底下的那一行和右边的那一行都必然有棋子，否则会被前面的包含。

![](https://cdn.luogu.com.cn/upload/image_hosting/gpqkmkej.png)

一种方案是选两列和两行，这样有 $5$ 组。对应的方程：

$$
f_{i, j} \overset{+}{\gets} \binom{i - 1}{2}\binom{j - 1}{2} \times 5f_{i - 3, j - 3}
$$

![](https://cdn.luogu.com.cn/upload/image_hosting/150ryci5.png)

另一种方案是选三行（列）和一列（行），这样有三种。对应的方程：

$$
f_{i, j} \overset{+}{\gets} \binom{i - 1}{3}(j - 1) \times 3f_{i - 4, j - 2}\\
f_{i, j} \overset{+}{\gets} \binom{j - 1}{3}(i - 1) \times 3f_{i - 2, j - 4}
$$

大致想想应该是没别的情况了，毕竟过了。

复杂度 $O(nm)$。

```cpp
#include <iostream>
using namespace std;

#define MAXN 3005
#define MOD 1000000007ll

using ll = long long;

ll pow(ll b, ll p, ll m)
{
    ll r = 1;
    while (p)
    {
        if (p & 1)
        {
            r = r * b % m;
        }
        b = b * b % m;
        p >>= 1;
    }
    return r;
}

ll fac[MAXN], inf[MAXN];

ll C(int n, int m)
{
    return fac[n] * inf[m] % MOD * inf[n - m] % MOD;
}

ll f[MAXN][MAXN];

int n, m;

ll k;

int main()
{
    cin >> n >> m ;
    k = 4;
    fac[0] = inf[0] = 1;
    for (int i = 1; i <= max(n, m); i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
        inf[i] = pow(fac[i], MOD - 2, MOD);
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i][0] = 1;
    }
    for (int j = 1; j <= m; j++)
    {
        f[0][j] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            f[i][j] = (f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + MOD) % MOD;
            if (i >= 2)
            {
                f[i][j] = (f[i][j] + f[i - 2][j - 1] * (i - 1) % MOD) % MOD;
            }
            if (j >= 2)
            {
                f[i][j] = (f[i][j] + f[i - 1][j - 2] * (j - 1) % MOD) % MOD;
            }
            if (i >= 3 && j >= 3)
            {
                f[i][j] = (f[i][j] + f[i - 3][j - 3] * C(i - 1, 2) % MOD * C(j - 1, 2) % MOD * 5 % MOD) % MOD;
            }
            if (i >= 4 && j >= 2)
            {
                f[i][j] = (f[i][j] + f[i - 4][j - 2] * C(i - 1, 3) % MOD * 3 % MOD * (j - 1) % MOD) % MOD;
            }
            if (i >= 2 && j >= 4)
            {
                f[i][j] = (f[i][j] + f[i - 2][j - 4] * C(j - 1, 3) % MOD * 3 % MOD * (i - 1) % MOD) % MOD;
            }
        }
    }
    ll res = MOD - 1, p = 1;
    for (int i = 0; i <= min(n, m); i++)
    {
        res = (res + C(n, i) * C(m, i) % MOD * fac[i] % MOD * p % MOD * f[n - i][m - i] % MOD) % MOD;
        p = p * k % MOD;
    }
    cout << res << endl;
    return 0;
}

```

---

## 作者：_maze (赞：0)

> 给你 $H\times W$ 的网格图，你可以在上面放小人并指定方向。但是当一行或者一列有两个小人，他们会把方向转向对方开始中门对狙。求至少放一个小人，且每个小人最多有一个方向限制的方案数。两种方案不同，当且仅当最终图上存在一个位置状态（即是否有小人或小人朝向）不同。

观察到同一行，同一列最多都只能有两个元素，两个元素按照题目要求方向固定。

于是可以考虑以行为一层进行动态规划。设计状态 $f_{i,j}$ 表示第 $i$ 行，状态为 $j$ 的答案。其中 $j$ 实际上是一个 $01$ 串，表示每一列选还是不选，

这样时空双炸，但是我们发现好像方案跟具体是哪些列没有关系，我们只关心列的数量。于是可以设计状态 $f_{i,j,k}$，表示到了第 $i$ 行，有 $j$ 列已经有两个元素，有 $k$ 列拥有一个元素。

发现还是不好跑进时限。考虑最终我们不需要 $k$ 这维状态，我们只需要知道哪些元素是单独享有一行一列的即可。于是设计状态 $f_{i,j}$ 表示当前处于第 $i$ 行，当前还有 $j$ 列空余。现在考虑转移：

1. 在一行放置一个元素，且这个元素最终独自一行一列：$f_{i,j-1}\leftarrow f_{i-1, j}\times j$。
2. 在一行放置两个元素：$f_{i,j-2}\leftarrow f_{i-1, j}\times \tbinom{j}{2}$。
3. 在当前行放置一个元素，且在 $i-1$ 行中选择一行放置同一列上的元素：$f_{i,j-1}\leftarrow f_{i-2, j}\times j\times (i-1)$。
4. 在这一行不放任何元素，直接继承上一层的状态。

然后直接转移即可。时间复杂度 $O(HW)$。

```cpp
  dp[0][w] = 1;
  for (int i = 1; i <= h; ++i) {
    for (int j = 0; j <= w; ++j) {
      dp[i][j] = dp[i][j] + dp[i - 1][j];
      if (j >= 1) {
        dp[i][j - 1] = dp[i][j - 1] + (dp[i - 1][j] * mint(j) * mint(4));
        if (i > 1) dp[i][j - 1] = dp[i][j - 1] + (dp[i - 2][j] * mint(j) * mint(i - 1));
      }
      if (j >= 2) dp[i][j - 2] = dp[i][j - 2] + (dp[i - 1][j] * mint(j) * mint (j - 1) * inv2);
    }
  }
  mint sum = 0;
  for (int i = 0; i < w; ++i) sum = sum + dp[h][i];
  cout << sum() << endl;
```


---

