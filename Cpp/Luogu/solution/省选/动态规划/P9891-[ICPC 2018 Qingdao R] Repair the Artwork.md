# [ICPC 2018 Qingdao R] Repair the Artwork

## 题目描述

DreamGrid 有一条纸带，上面有 $n$ 个格子排成一行，他在一些格子上画了一些美丽的图案。不幸的是，他淘气的室友 BaoBao 在他不在家的时候在其他一些格子上画了一些其他图案。现在 DreamGrid 需要在不破坏自己图案的情况下擦除 BaoBao 的图案。

我们将格子从左到右编号为 1 到 $n$。每个格子要么包含 DreamGrid 的图案，要么包含 BaoBao 的图案，要么是空的。

每次，DreamGrid 可以选择两个整数 $l$ 和 $r$（每次选择可以不同），使得

- $1 \le l \le r \le n$，并且
- 对于所有 $l \le i \le r$，第 $i$ 个格子要么包含 BaoBao 的图案，要么是空的，

然后将所有 $l \le i \le r$ 的第 $i$ 个格子变为空格子。

DreamGrid 有多少种方法可以通过执行上述操作恰好 $m$ 次将所有包含 BaoBao 图案的格子变为空格子？由于答案可能很大，请输出答案对 $10^9 + 7$ 取模的结果。

设 $\{(a_1, b_1), (a_2, b_2), \dots (a_m, b_m)\}$ 是一个有效的擦除序列（$1 \le a_i \le b_i \le n$），其中 $(a_i, b_i)$ 表示 DreamGrid 在第 $i$ 次操作中选择整数 $a_i$ 和 $b_i$。设 $\{(c_1, d_1), (c_2, d_2), \dots, (c_m, d_m)\}$ 是另一个有效的擦除序列（$1 \le c_i \le d_i \le n$），其中 $(c_i, d_i)$ 表示 DreamGrid 在第 $i$ 次操作中选择整数 $c_i$ 和 $d_i$。如果存在一个整数 $k$（$1 \le k \le m$）使得 $a_k 
e c_k$ 或 $b_k 
e d_k$，则这两个序列被认为是不同的。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
2 2
2 0
3 2
2 1 0
3 1
2 1 0```

### 输出

```
8
3
1```

# 题解

## 作者：immortal_immortals (赞：3)

## 思路
1. 从左往右递推，$dp_{i,j}$ 表示第 $i$ 个数可选区间数量为 $j$ 的方案数。
1. 考虑只包含 $0$ 和 $1$ 的情况，每碰到一个 $1$。此 $1$ 的位置为 $i$，前面的 $1$ 的位置为 $k$，则可选区间数要加上：
$$C_{i-k-1}^{2}=\frac{(i-k-1)\times(i-k)}{2}$$
3. 考虑包含2的情况，对于每个 $2$，可选区间数（可选可不选的方案数）减去（必选的方案数）。
1. 利用容斥的思想， 可把 $2$ 拆成 $0$ 和 $1$，对答案的贡献即为 $0$ 的贡献减去 $1$ 的贡献。

时间复杂度 $O(n^4)$。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
const int mod=1000000007;
long long ans;
int t,ll,n,m,dp[105][5565],f[105][5565],a[105];
int js(int a,int b)
{
    int sum=1;
    for(;b;b/=2,a=(long long)a*a%mod)
	{
		if(b%2!=0)
		{
			sum=(long long)sum*a%mod;
		}
	}
    return sum;
}
void work(int i,int j,int x)
{
    if(f[i][j]!=ll)
	{
		f[i][j]=ll;
		dp[i][j]=0;
	}
    dp[i][j]=(dp[i][j]+x)%mod;
}
int main()
{
    t=read();
    for(ll=1;ll<=t;ll++)
	{
        n=read();
		m=read();
        for(int i=1;i<=n;i++)
		{
			a[i]=read();
		}
        a[n+1]=1;
		work(0,0,1);
        for(int i=0;i<=n;i++)
        {
        	for(int j=0;j<=i*(i+1)/2;j++)
			{
				if(f[i][j]==ll&&dp[i][j])
				{
					for(int k=i+1;k<=n+1;k++)
					{
                        if(a[k]==1)
						{
							work(k,j+(k-i)*(k-i-1)/2,dp[i][j]);
							break;
						}
                        else if(a[k]==2)
						{
							work(k,j+(k-i)*(k-i-1)/2,-dp[i][j]);
						}
                    }
				}     
			}
		}
        ans=0;
        for(int i=0;i<=n*(n+1)/2;i++)
		{
			if(f[n+1][i]==ll)
			{
				ans=(ans+(long long)dp[n+1][i]*js(i,m))%mod;
			}
		}
        ans=(ans+mod)%mod;
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：Sampson_YW (赞：2)

设一个集合 $A$ 表示所有为 2 的下标集合。我们要求的就是：所有操作中恰好包含了 $A$ 的方案数。

恰好不好算，可以容斥成至多。枚举一个集合 $S$，表示这个集合里的位置**可以**被包含，这个集合之外的位置**不能**被包含，容斥系数为 $(-1)^{|A|-|S|}$。容易发现这两种状态是和题目中 0,1 的状态是一样的。那么就将 $S$ 中的数看成 0，$S$ 之外的数看成 1。容斥系数的指数就是有多少个 2 被看成了 1。

于是现在变成了对一个 01 序列求答案。这是容易计算的，所有不包含任意一个 1 的区间都可以选，方案数就是这些区间数量的 $m$ 次方。考虑区间数量如何计算：设 $X$ 为 1 的下标序列（为了方便计算，设第 $0$ 位和 $n+1$ 位上的数是 1），那么区间数量就是 $\sum \binom{X_i-X_{i-1}}{2}$。

因此区间数量只与这个下标序列有关，考虑 DP。设 $f_{i,k}$ 表示 $i$ 在下标序列中，$i$ 之前的区间数量为 $k$。转移枚举下一个在下标序列中的数 $j$，要满足 $[i+1,j-1]$ 中没有 1。令 $w=\binom{j-i}{2}$。

如果 $j$ 是 1，那么 $f_{i,k}$ 转移到 $f_{j,k+w}$。

如果 $j$ 是 2，那么转移时要乘上一个容斥系数 $-1$，即 $-f_{i,k}$ 转移到 $f_{j,k+w}$。

答案为 $\sum k^mf_{n+1,k}$。[code](https://www.luogu.com.cn/paste/3mjri8yd)

---

## 作者：modfisher (赞：0)

## 思路
考虑不存在 $a_i=2$ 的情况。这时是非常简单的，设序列中不包含 $1$ 的子区间数为 $cnt$，则答案为 $cnt^m$。

那 $a_i=2$ 的情况呢？考虑容斥。把一个 $2$ 改成 $1$ 会贡献 $-1$ 的容斥系数，于是可以 $O(n2^n)$ 暴力计算。

考虑优化。发现 $cnt$ 的范围只有 $O(n^2)$，于是设 $dp_{i,j}$ 表示：在所有容斥状态中，最后一个改成 $1$ 的 $2$ 下标为 $i$，$cnt=j$ 的状态的容斥系数之和。容易得出转移式：

$$dp_{i,j}=-\sum_{a_k=2}dp_{k,j-c(k+1,i-1)}$$

其中，$c(x,y)$ 表示将 $[x,y]$ 中的所有 $2$ 改成 $0$ 后，该区间中不包含 $1$ 的子区间数。

初始 $dp_{0,0}=1$，不妨令 $a_0=2$。

最后只需统计：

$$\sum_{a_i=2}\sum_{j=1}^{\frac{i(i+1)}{2}}dp_{i,j}\times (j+c(i+1,n))^m$$

复杂度 $O(n^4)$，常数不大就能过。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 105, p = 1e9 + 7;

int a[maxn], suf[maxn];
ll dp[maxn][maxn * maxn], pn[maxn * maxn];

ll qpow(ll a, ll x){
	ll res = 1;
	while(x){
		if(x & 1) res = res * a % p;
		a = a * a % p;
		x >>= 1;
	}
	return res;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n, m;
		scanf("%d %d", &n, &m);
		dp[0][0] = 1, a[0] = 2;
		for(int i = 1; i <= n; i ++){
			scanf("%d", &a[i]);
			if(a[i] == 2){
				int pre = 0, res = 0;
				for(int k = i - 1; k >= 0; k --){
					if(a[k] == 0) pre ++, res += pre;
					else if(a[k] == 1) pre = 0;
					else{
						for(int j = res; j <= i * (i + 1) / 2; j ++) dp[i][j] = (dp[i][j] + p - dp[k][j - res]) % p;
						pre ++, res += pre;
					}
				}
			}
		}
		suf[n + 1] = 0;
		int pre = 0;
		for(int i = n; i >= 1; i --){
			if(a[i] == 1) pre = 0;
			else pre ++;
			suf[i] = suf[i + 1] + pre;
		}
		for(int i = 0; i <= n * (n + 1) / 2; i ++) pn[i] = qpow(i, m);
		ll ans = 0;
		for(int i = 0; i <= n; i ++) if(a[i] == 2) for(int j = 0; j <= i * (i + 1) / 2; j ++) ans = (ans + dp[i][j] * pn[j + suf[i + 1]] % p) % p, dp[i][j] = 0;
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：bluewindde (赞：0)

所求即为选择的区间恰好包含所有 $a_i = 2$ 的位置的方案数。

设所有 $a_i = 2$ 的位置 $i$ 组成集合 $S$，考虑容斥被选中的位置是 $S$ 的子集的方案数 $g(S)$。

设 $T$ 为 $S$ 的子集，$T$ 的贡献 $f(T)$ 为：选中的位置都在 $T$ 的子集中的方案数乘容斥系数 $(-1)^{|S| - |T|}$。

将所有 $i \in T$ 视为 $a_i = 0$（可选可不选）；将所有 $i \in U - T$ 视为 $a_i = 1$（必须不选）。$f(T)$ 可重新表述为不包含 $1$ 的区间的数量的 $m$ 次方（一个区间允许多次选，方案有序）。

只需求满足条件的区间数量，设所有被视为 $a_i = 1$ 的位置 $i$ 依次组成长为 $m$ 的数列 $b_1, b_2, \cdots b_m$，则满足条件的区间数量为

$$\sum\limits_{i = 2}^m \frac 1 2 (b_i - b_{i - 1}) (b_i - b_{i - 1} - 1)$$

考虑 DP，发现答案只与 $b$ 的上一项有关，设 $dp_{i, j}$ 表示 $i$ 被视为 $a_i = 1$，区间数量为 $j$ 的方案数。（为了方便初始化和统计答案，规定 $a_0 = a_{n + 1} = 1$）

**转移**

$$dp_{k, j + w} = \sum\limits_{i = 0}^{k - 1} c_i \cdot dp_{i, j}$$

其中 $c_i$ 是容斥系数，$w$ 是权值。

发现容斥系数的指数实际上是有多少个 $a_i = 2$ 被视为 $a_i = 1$，所以

$$c_i = \begin{cases} 1, &a_i = 1, \\ -1, &a_i = 2, \\ 0, &\text{otherwise}. \end{cases}$$

该式中 $a_i$ 是原数列中的 $a_i$。

$$w = \frac 1 2 (k - i) (k - i - 1)$$

**边界**

$$dp_{0, 0} = 1$$

**答案**

$$\sum\limits_{x = 1}^{\frac 1 2 n (n + 1)} dp_{n + 1, x} \cdot x^m$$

```cpp
#include <iostream>

#define int long long

using namespace std;

const int mod = 1e9 + 7;

static inline int qpow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1)
            ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}

int n, m;
int a[105];
int dp[105][10005];

static inline void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 0; i <= n + 1; ++i) {
        int mx = n * (n + 1) / 2;
        for (int j = 0; j <= mx; ++j)
            dp[i][j] = 0;
    }
    a[n + 1] = 1;
    dp[0][0] = 1;
    for (int i = 0; i <= n; ++i) {
        int mx = i * (i + 1) / 2;
        for (int j = 0; j <= mx; ++j) {
            for (int k = i + 1; k <= n + 1; ++k) {
                int w = (k - i) * (k - i - 1) / 2;
                if (a[k] == 1) {
                    dp[k][j + w] = (dp[k][j + w] + dp[i][j]) % mod;
                    break;
                } else if (a[k] == 2) {
                    dp[k][j + w] = (dp[k][j + w] - dp[i][j] + mod) % mod;
                }
            }
        }
    }
    int mx = n * (n + 1) / 2;
    int ans = 0;
    for (int i = 0; i <= mx; ++i)
        ans = (ans + dp[n + 1][i] * qpow(i, m) % mod) % mod;
    cout << ans << endl;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("P9891.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```

---

