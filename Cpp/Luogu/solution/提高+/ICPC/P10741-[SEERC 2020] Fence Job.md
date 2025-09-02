# [SEERC 2020] Fence Job

## 题目描述

Fred 有一个长度为 $n$ 的排列 $h$，每次操作他可以选择一段区间 $[l,r]$，令 $h_i = \min_{j=l}^{r}h_j\ (i \in [l,r])$。

问进行若干次操作（可以为 $0$ 次）后不同的数组数量，对 $10^9 + 7$ 取模。

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
4```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
42```

## 样例 #3

### 输入

```
7
1 4 2 5 3 6 7```

### 输出

```
124```

# 题解

## 作者：ZHR100102 (赞：4)

不错的观察类 dp 题！

# 观察

首先不难发现，假设某一段数字 $a_l\sim a_r$ 最后全变成了 $x$，那么 $x$ 的位置 $pos_x$ 一定满足：
- $l \le pos_x \le r$。
- $\forall l \le i \le r,a_i \ge x$。

那么，我们就可以 $O(n^2)$ 求出每个数最大能覆盖的区间 $a_l\sim a_r$。

并且不难发现，我们最后的答案一定是由这些连续段拼接起来的。

# dp 设计

因为有了这个连续段性质，所以我们就比较容易 dp 了。

本人一开始用的是 $dp_{i,j}$ 表示考虑到第 $i$ 位，第 $i$ 位是原数列里第 $j$ 个数的方案数。这种状态定义下利用前缀和优化 dp 其实是可以 $O(n^2)$ 得到答案的，但是转移方程细节有点多，这里不再赘述。

但是实际上这题有更简单的一个状态定义，同样是 $dp_{i,j}$，但是表示的却是考虑到第 $j$ 位，这 $j$ 个位的数字所处的**下标**全都在 $1 \sim i$ 之间的方案数是多少（这里的 $i,j$ 和前一个状态定义颠倒了一下，但是无伤大雅）。

这两种 dp 的状态定义的唯一区别就在于一个是限制了这一位必须是 $j$，一个限制了这一位只要小于等于 $j$ 即可。这种通过**把固定某个元素转化为固定某个前缀**的状态优化是一种常见的优化转移方式，无论是计数 dp 还是最优化 dp 都可以用到，并且还方便统计答案。

那么预处理每个数能够拓展到的左右端点后直接转移即可：

- 当 $l \le j \le r,dp_{i,j}\gets dp_{i-1,j}+dp_{i,j-1}$，即对应着接着上一个连续段的方案。
- 否则 $dp_{i,j}\gets dp_{i-1,j}$，即对应着一个元素单独成一个连续段的情况。

最后输出 $dp_{n,n}$ 即可。

同时这个显然是可以用类似背包优化一下空间的，时间复杂度是 $O(n^2)$。不优化空间其实也能过。

# 代码

## 不优化版本

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const ll mod=1e9+7;
const int N=5005;
int n,h[N];
ll dp[N][N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>h[i];
    for(int i=1;i<=n;i++)dp[i][0]=1;
    for(int i=1;i<=n;i++)
    {
        int l=i,r=i;
        while(l-1>=1&&h[l-1]>=h[i])l--;
        while(r+1<=n&&h[r+1]>=h[i])r++;
        for(int j=1;j<=n;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(l<=j&&j<=r)dp[i][j]=(dp[i][j]+dp[i][j-1])%mod;
        }
    }
    cout<<dp[n][n];
    return 0;
}
```

## 优化版本

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const ll mod=1e9+7;
const int N=5005;
int n,h[N];
ll dp[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>h[i];
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        int l=i,r=i;
        while(l-1>=1&&h[l-1]>=h[i])l--;
        while(r+1<=n&&h[r+1]>=h[i])r++;
        for(int j=l;j<=r;j++)dp[j]=(dp[j]+dp[j-1])%mod;
    }
    cout<<dp[n];
    return 0;
}
```

---

## 作者：Super_Cube (赞：4)

# Solution

称操作一段区间为染色。定义 $dp_{i,j}$ 表示对 $1\sim i$ 染色后，$1\sim j$ 的颜色已定的方案数。

对于第 $i$ 个数，如果不能定下自己的颜色就是 $dp_{i-1,j}$，否则找到一个极大区间 $[l,r]$ 使得 $a_{l\sim r}\ge a_i$，那么对于 $l\sim r$ 所有数都可以被 $i$ 确定，即为 $dp_{i,j-1}$。所以转移为 $dp_{i,j}=dp_{i-1,j}+[l_i\le j\le r_i]dp_{i,j-1}$。

答案为 $dp_{n,n}$，时间复杂度 $O(n^2)$。

# Code

注意到每次转移只与当前行与上一行相关，打了滚动。

```cpp
#include<bits/stdc++.h>
const int mod=1e9+7;
int dp[3005];
int a[3005];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;scanf("%d",&a[i++]));
	dp[0]=1;
	for(int i=1,l,r;i<=n;++i){
		for(l=i;a[l-1]>=a[i];--l);
		for(r=i;a[r+1]>=a[i];++r);
		for(int j=l;j<=r;++j)
			if((dp[j]+=dp[j-1])>=mod)dp[j]-=mod;
	}
	printf("%d",dp[n]);
	return 0;
}
```

---

## 作者：lmq308270 (赞：3)

# 线性动态规划 + 滚动数组
容易想到动态规划，不妨定义 $dp[i][j]$ 表示使用前 $i$ 个数字，填前 $j$ 个的位置的方案数。

那么可以先求出第 $i$ 个数字的拓展区间，即两边比其大的数都可拓展。

那么：

如果 $j$ 在 $i$ 的填充区间之外，那么考虑继承 即 $dp[i][j]=dp[i-1][j]$。

如果 $j$ 在 $i$ 的填充区间之内，那么考虑继承 + 转移， 即 $dp[i][j]=dp[i-1][j]+dp[i][j-1]$。

发现状态转移方程只与上一层有关，那么就可以用滚动数组优化即可。

时间复杂度： $O(n^2)$。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3+5;
const int mod=1e9+7;
int n,m,a[N],dp[N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	dp[0]=1;
	for(int i=1,l,r;i<=n;i++){
		for(l=i;a[l-1]>a[i];l--);
		for(r=i;a[r+1]>a[i];r++);
		for(int j=l;j<=r;j++){
			dp[j]+=dp[j-1];
			dp[j]%=mod;
		}
	}
	cout<<dp[n];
	return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 思路

下面我们将题面中的区间赋最小值操作称之为染色。

dp，设 $f(i,j)$ 表示已经染了 $[1,i]$ 的元素，决定了 $[1,j]$ 的元素的颜色（即，这些颜色不会改变了）。这样子我们转移的时候可以考虑到所有情况。

转移的话：第一种转移就是 $f(i,j)=f(i-1,j)$，也就是对 $i$ 号元素染色后不能决定 $i$ 的值。

另一种就是染过了之后决定了 $i$ 的值，这些值一定在一个区间中。我们可以求出这个区间。

在这个区间内的元素 $i$，需要进行额外转移 $f(i,j)=f(i,j-1)+f(i,j)$ 表示这个位置的值已经确定，因此需要看前缀 $[1,i]$ 方才知道。

时间复杂度 $O(n^2)$。

[双倍经验](https://www.luogu.com.cn/problem/AT_agc058_b)

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

const int N = 3005, mod = 1e9 + 7;
int f[N][N], a[N], n;

int Add(int x, int y){ return (x + y) > mod ? (x + y - mod) : (x + y); }

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) f[i][0] = 1;
    for(int i=1;i<=n;i++){
        int L, R;
        for(L=i;a[L - 1]>=a[i];L--);
        for(R=i;a[R + 1]>=a[i];R++);
        for(int j=1;j<=n;j++){
            // First: 不决定
            f[i][j] = f[i - 1][j];
            // Second: 决定
            if(L <= j && j <= R) f[i][j]  = Add(f[i][j], f[i][j - 1]);
        }
    }
    cout << f[n][n] << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Dazlin7 (赞：2)

### 题意

给定一个长度为 $n$ 的排列 $h$，每次操作可以选择一段区间 $[l,r]$，令 $h_i = \min_{j=l}^{r}h_j\ (i \in [l,r])$。

问进行若干次操作（可以不操作）后结果序列的方案数，对 $10^9 + 7$ 取模。
### 思路

比较容易想到 DP， 我们定义 $ f(i, j) $ 为使用前 $ i $ 个元素 $ h_1 $ 到 $ h_i $，构造一个长度为 $ j $ 的结果序列的方案数。

考虑如何从 $ f(i, \cdot) $ 转移到 $ f(i+1, \cdot) $。设 $[l, r]$ 为包含索引 $i$ 的极大区间，并且满足该区间的最小值为 $h_i$。对于所有 $ j \in [l, r] $，有以下转移方程：

$$
f(i+1, j) = \sum_{k=l-1}^{j} f(i, k) 
$$


### 优化

由于每次计算只依赖于前一层的结果，可以将 DP 数组的第一维滚动以节省空间。

利用前缀和来优化上述转移方程。通过计算前缀和数组，可以在 $O(1)$ 时间内计算出区间和，从而使时间复杂度降到 $O(n^2)$。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = (int)3005;
const ll mod = (ll)1e9 + 7;
ll dp[N][N];
ll l[N], r[N];
ll prefix[N];
ll h[N];
int main() {
  ios::sync_with_stdio(!cin.tie(0));
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> h[i];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i - 1; ; --j) {
      if (h[j] < h[i]) {
        l[i] = j;
        break;
      }
    }
    for (int j = i + 1; ; ++j) {
      if (h[j] < h[i]) {
        r[i] = j;
        break;
      }
    }
  }
  for (int j = 1; j <= n; ++j) {
    if (l[j] < 1) {
      dp[1][j] = 1;
    }
    prefix[j] = prefix[j - 1] + dp[1][j];
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (l[j] < i && i < r[j]) {
        dp[i][j] += prefix[j];
        dp[i][j] %= mod;
      }
      prefix[j] = (prefix[j - 1] + dp[i][j]) % mod;
    }
  }
  cout << accumulate(dp[n] + 1, dp[n] + n + 1, 0ll) % mod << endl;
  return 0;
}

```

---

## 作者：Walrus (赞：1)

胡的一个做法居然对了很有实力啊。

## Solution

不知道是否可用最值分治，如果有可以交流。

考虑点 $i$ 会影响哪些区间，显然，假设其最初影响的区间是 $[i,i]$，如果要向左右拓展，假设要从 $[i,i]$ 拓展到 $[i,i+1]$，那么其必须满足 $a_i< a_{i+1}$，否则此覆盖是无意义的（因为如果继续向右的话最小值将不再是 $a_i$），所以这个区间可以考虑用单调栈预处理。

根据此性质，考虑怎么定义 dp，通过观察得知一定会有一维 $dp_i$ 表示已经算了前 $i$ 个数的贡献，但是发现转移困难，考虑再加上一维 $j$ 表示 $1\sim j$ 可以被确定，则最后的状态为 $dp_{i,j}$ 表示用了前 $i$ 个数确定了前 $j$ 个数。

那么转移比较自然是 

$$dp_{i,j}=dp_{i-1,j}+\sum\limits_{l_i\leq j \leq r_i}dp_{i,j-1}$$

然后做完了，调试删了即可。

```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pre(i, j, k) for(int i = j; i >= k; --i)
#define int long long
#define inf 0x3fffffff
#define pb push_back
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;

const int N = 3e3 + 5;
const int V = 3e3;
const int mod = 1e9 + 7;

int n, a[N], dp[N][N];
int st[N], top, l[N], r[N];

signed main() {
    FASTIO;
#ifdef Xdik
	cerr << "I love gm";
#else

#endif

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) {
		while(top && a[i] <= a[st[top]]) --top;
		l[i] = st[top], st[++top] = i;
	}
	top = 0;
	pre(i, n, 1) {
		while(top && a[i] <= a[st[top]]) --top;
		r[i] = st[top], st[++top] = i;
	}
	rep(i, 1, n) if(l[i]) ++l[i];
	rep(i, 1, n) if(r[i]) --r[i];
	rep(i, 1, n) if(!l[i]) l[i] = 1;
	rep(i, 1, n) if(!r[i]) r[i] = n;
	rep(i, 1, n) cout << l[i] << ' ' << r[i] << '\n';
	
	rep(i, 0, n) dp[i][0] = 1;
	
	rep(i, 1, n) {
		rep(j, 1, n) {
			dp[i][j] = dp[i - 1][j];
			if(l[i] <= j && j <= r[i]) dp[i][j] += dp[i][j - 1], dp[i][j] %= mod;
		}
	}

	cout << dp[n][n] % mod;
    return 0;
}

```

---

