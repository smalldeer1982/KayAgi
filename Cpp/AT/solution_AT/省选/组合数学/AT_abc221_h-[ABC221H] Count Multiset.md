# [ABC221H] Count Multiset

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc221/tasks/abc221_h

正の整数 $ N $, $ M $ が与えられます。

$ k=1,2,\ldots,N $ について以下の値を求め、$ 998244353 $ で割ったあまりをそれぞれ出力してください。

- $ k $ 個の正整数からなる多重集合 $ A $ のうち、以下の $ 2 $ つの条件をすべて満たすものの個数
  - $ A $ に含まれる要素の総和は $ N $
  - 任意の正整数 $ x $ について、$ A $ は $ x $ を高々 $ M $ 個しか含まない

## 说明/提示

### 制約

- $ 1\ \leq\ M\ \leq\ N\ \leq\ 5000 $
- 入力はすべて整数

### Sample Explanation 1

\- $ k=1 $ のとき、問題文中の条件を満たすような多重集合 $ A $ は $ \{4\} $ の $ 1 $ 通りです。 - $ k=2 $ のとき、問題文中の条件を満たすような多重集合 $ A $ は $ \{1,3\} $ と $ \{2,2\} $ の $ 2 $ 通りです。 - $ k=3 $ のとき、問題文中の条件を満たすような多重集合 $ A $ は $ \{1,1,2\} $ の $ 1 $ 通りです。 - $ k=4 $ のとき、問題文中の条件を満たすような多重集合 $ A $ は $ 1 $ つも存在しません。

## 样例 #1

### 输入

```
4 2```

### 输出

```
1
2
1
0```

## 样例 #2

### 输入

```
7 7```

### 输出

```
1
3
4
3
2
1
1```

# 题解

## 作者：K8He (赞：45)

校内学长搬的模拟赛题，赛时爆标了，来写一发。

首先为了方便，先不考虑相同元素出现次数的限制。

我们设 $f_{i, j}$ 表示当前填了 $i$ 个数，总和为 $j$ 的方案数。

考虑一种奇妙的转移方式：

- 向当前序列里加上一个 $0$，即从 $f_{i - 1, j}$ 转移过来。
- 将当前序列全部加 $1$，即从 $f_{i, j - i}$ 转移过来。

第一种操作的例子是序列 `2 2 3` 加上一个 `0` 得到 `0 2 2 3`，由 $f_{3, 7}$ 转移到 $f_{4, 7}$；第二种操作的例子是 `0 0 1 2` 整体加 $1$ 变为 `1 1 2 3`，由 $f_{4, 3}$ 转移到 $f_{4, 7}$。

接下来开始考虑相同元素出现次数的限制。

既然有限制就不能随意加零，那么第一种操作贡献就应该是 $\sum_{k = 1}^{m}f_{i - k, j}$，但是我们不知道之前的 $f_{i - k, j}$ 有几个零，这样就不能直接转移。

考虑设一个辅助的 $g_{i, j}$ 表示当前填了 $i$ 个数，总和为 $j$ 且 **序列里不含有 $0$** 的方案数。

$g_{i, j}$ 很好转移，就是整体加一的情况，从 $f_{i, j - i}$ 转移过来。

用这个可以很方便地转移 $f_{i, j}$ 的第一种操作，即 $\sum_{k = 1}^{m}g_{i - k, j}$。

总结一下转移方程：

$$
\begin{aligned}
f_{i, j} &= f_{i, j - i} + \sum_{k = 1}^{m}g_{i - k, j}\\
g_{i, j} &= f_{i, j - i}
\end{aligned}
$$

考虑前缀和优化，$O(n^2)$ 解决。

一份实现：

```cpp
const ll N = 5010, P = 998244353;
namespace SOLVE {
	ll n, m, f[N][N], g[N][N], sum[N][N];
	inline ll rnt () {
		ll x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}
	inline void In () {
		n = rnt (), m = rnt ();
		return;
	}
	inline void Solve () {
		_for (i, 1, n) {
			if (i <= m) f[i][0] = 1;
			_for (j, 1, n) {
				if (j >= i) g[i][j] = f[i][j] = f[i][j - i];
				sum[i][j] = (sum[i - 1][j] + g[i][j]) % P;
				f[i][j] = (f[i][j] + sum[i - 1][j] - sum[std::max (0ll, i - m - 1)][j] + P) % P;
			}
		}
		return;
	}
	inline void Out () {
		_for (i, 1, n) printf ("%lld\n", g[i][n]);
		return;
	}
}
```


---

## 作者：yllcm (赞：9)

分拆数做法。

考虑形式化描述问题，计数长度在 $k\in[1,n]$ 的数列 $y$，满足：

* $y_i\leq y_{i+1}$。
* $\sum y_i=n$。
* 每个数的个数不能超过 $m$ 个。

没有第三个条件就是分拆数，有第三个条件的话，只需要在每次转移的时候容斥掉开头**恰好**有 $m+1$ 个 $1$ 的情况即可。转移方程式：

$$f_{i,j}=f_{i-1,j-1}+f_{i-j,j}-f_{i-j,j-(m+1)}$$

解释一下，前面两项就是普通分拆数，最后一项的意思是，如果最开始有 $m+1$ 个 $1$，那么全局 $-1$ 之后的效果就是删去最开始的 $m+1$ 个数。时间复杂度 $\mathcal{O}(n^2)$。

PS：可以在[这里](https://www.cnblogs.com/yllcm/p/17035565.html)看博主的完整思考过程，比较有趣。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define FR first
#define SE second
using namespace std;
inline int read() {
    int x = 0; bool op = 0;
    char c = getchar();
    while(!isdigit(c))op |= (c == '-'), c = getchar();
    while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return op ? -x : x;
}
const int N = 5010;
const int P = 998244353;
void add(int &a, int b) {a = (a + b) % P;}
void sub(int &a, int b) {a = (a - b + P) % P;}
int n, m;
int f[N][N], g[N][N];
int main() { 
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    n = read(); m = read();
    f[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            add(f[i][j], f[i - 1][j - 1]);
            add(f[i][j], f[i - j][j]);
            if(j >= m + 1)sub(f[i][j], f[i - j][j - (m + 1)]);
        }
    }
    for(int i = 1; i <= n; i++)printf("%d\n", f[n][i]);
    return 0;
}
```


---

## 作者：FrozenDream (赞：7)

## 思路:
题目要求我们求出可能的可重集个数，我们可以先将这个大小为 $k$ 的可重集转化为长度为 $k$ 的不降序
列，满足第一个数大于 0，不存在 $m$ 个相同且连续的数。这个可以暴力 $\operatorname{dp}$ 做。记 $f[i][j][k][h]$ 表示确定了可重集中的前 $i$ 个数，当前数的和为 $j$，第 $i$ 个位置的数是 $g$，$g$ 这个数已经连续出现 $h$ 次，暴力转移是 $O(n^5)$ 的。

发现上面的 $\operatorname{dp}$ 不好优化，考虑优化 $\operatorname{dp}$ 状态设计。有一个套路，对于不降序列，我们可以差分，从而将不降序列转化为任意序列。我们令原来的序列为 $A$，新序列为 $B$，且 $B_1$ 和 $A_1$相等，$B_i$ 和 $A_{i+1}-A_i$ 相等，即 $B$ 为 $A$ 的差分数组，因为差分数组和原不降序列一一对应，所以问题转化为，对于一个大小为 $k$ 的序列，计算满足 $\sum_{i = 1}^k (k-i+1)B_i=n,B_1>0$ 且不存在连续的 $m$ 个 0 的可能的序列个数。

这样也不好做，考虑将差分数组倒过来与原不降序列也是一一对应的，转化为计算满足 $\sum_{i = 1}^k iB_i=b,b_k>0$ 且不存在连续的 $m$ 个 0 的序列的个数。

这个显然比较好做了，记 $f[i][j]$ 表示确定了倒过来的差分数组中的前 $i$ 个数，前 $i$ 个数加权求和的和为 $j$ 且 $B_i>0$ 的方案数，转移的话，枚举上一个不为 0 的位置 $k$，然后枚举 $B_i$ 的值，直接转移的复杂度是 $O(n^2log(n))$ 的。
## Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define M 998244353
using namespace std;
int n,m,dp[5005][5005],sum[5005][5005];
signed main(){
	cin>>n>>m;
	dp[0][0]=sum[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int g=1;g<=(j/i);g++){
				dp[i][j]=(dp[i][j]+sum[i-1][j-g*i])%M;
				if(i>m) dp[i][j]=(dp[i][j]-sum[i-m-1][j-g*i]+M)%M;
			}
			sum[i][j]=(sum[i-1][j]+dp[i][j])%M;
		}
		sum[i][0]=1;
	}
	for(int i=1;i<=n;i++) cout<<dp[i][n]<<"\n";
	return 0;
}
```




---

## 作者：小木虫 (赞：6)

### Preface  
一道比较容易的前缀和优化 dp 题目。  
### Problem  
输入两个正整数 $n,m$，并存在一个集合，问你一个长度为 $k$ 的合法集合存在多少个。你需要回答 $k$ 的值为 $1$ 到 $n$ 的每种情况。  
一个合法的集合定义指长度为 $k$，元素和为 $n$，每一个数字在集合中出现的次数都小于等于 $m$ 的集合。
### Solution  
首先，经典套路，集合转不下降序列。  
不下降序列转差分。  
设 $l_1....l_k$ 为差分数组，则其需要满足：  
$$l_i\geq0,\sum_ {i=x}^{i\leq x+m}l_i >0\space \space (1\leq x \leq k-m)$$  
并且，由于对元素和的性质，根据差分得到：  
$$(\space \sum _{i=1}^{i\leq k}l_i\times (k-i+1)\space ) \space =n$$  

由于这个限制内带 $k$，我们需要回答若干个 $k$，并且我们并没有对差分数组的先后顺序做任何的限制，我们将差分数组倒转过来，限制是一样的，这样就消去了 $k$ 的限制，即：  

$$(\space \sum _{i=1}^{i\leq k}l_i\times i\space ) \space =n$$ 

现在这个限制就非常的好，可以开始进行 dp 了。  
容易设状态为 $f_{p,j}$，意义为选了 $p$ 个数，他们的差分满足 $(\space \sum _{i=1}^{i\leq p}l_i\times i\space ) \space =j$。  

容易列出状态转移方程：  
$$f_{p,j}=\sum_{i=1}^{i \times p\leq j} \sum_{k=p-m}^{k<p} f_{k,j-p\times i}$$  
其中，$k$ 为上一个非 0 位置，$i$ 为选择的差分数。  
显然，第二个 $\sum$ 是可以滚动前缀和的，而第一个 $\sum$ 是调和级数的。  
总复杂度为 $O(n^2 \ln n)$：  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5010;
const int mod=998244353;
int n,m,f[N][N],sum[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	f[0][0]=1;sum[0]=1;
	for(int p=1;p<=n;p++){
		for(int j=1;j<=n;j++){
			for(int i=1;i*p<=j;i++){
				f[p][j]+=sum[j-p*i];
				f[p][j]%=mod;
			}
		}
		for(int j=0;j<=n;j++){
			if(p-m>=0)sum[j]=(sum[j]-f[p-m][j]+mod)%mod;
			sum[j]=(sum[j]+f[p][j])%mod;
		}
	}
	for(int i=1;i<=n;i++)
		cout<<f[i][n]<<"\n";
	return 0;
}
```


---

## 作者：ケロシ (赞：0)

非常好计数，使我乱写一发就过

首先考虑没有出现次数的限制怎么做，这是经典问题，设 $f_{n,k}$ 为现在集合有 $k$ 个数，总合为 $n$ 的方案数，那么每次有两种操作：

1. 往集合后面塞一个 $1$。
2. 集合里所有的数都加 $1$。

转移也很简单：

1. $f_{n,k}\to f_{n+1,k+1}$
2. $f_{n,k}\to f_{n+k,k}$

接下来考虑有出现次数的限制怎么做。

不难发现这个等价于操作 $1$ 不能连续做超过 $m$ 次。

那么很自然就想到容斥，因为在进行一次操作 $2$ 后再进行超过 $m$ 次操作 $1$ 就不合法，那么直接在做一次操作 $2$ 后做 $m+1$ 次操作 $1$ 的地方减掉对应方案数即可，即：

$$
f_{n,k} \overset{-}{\to} f_{n+k+m+1,k+m+1}
$$

时间复杂度 $O(n^2)$。

```cpp
const int N = 5e3 + 5;
const int P = 998244353;
inline int add(int x, int y) { return (x + y < P ? x + y : x + y - P); }
inline void Add(int & x, int y) { x = (x + y < P ? x + y : x + y - P); }
inline int sub(int x, int y) { return (x < y ? x - y + P : x - y); }
inline void Sub(int & x, int y) { x = (x < y ? x - y + P : x - y); }
int n, m;
int dp[N][N];
void solve() {
	cin >> n >> m;
	dp[0][0] = 1;
	dp[m + 1][m + 1] = P - 1;
	REP(i, n) FOR(j, 0, i) {
		Add(dp[i + 1][j + 1], dp[i][j]);
		if(j && i + j <= n) {
			Add(dp[i + j][j], dp[i][j]);
			if(i + j + m + 1 <= n) 
				Sub(dp[i + j + m + 1][j + m + 1], dp[i][j]);
		}
	}
	FOR(i, 1, n) cout << dp[n][i] << endl;
}
```

---

