# [ARC104D] Multiset Mean

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc104/tasks/arc104_d

正の整数 $ N,\ K,\ M $ が与えられるので、$ 1 $ 以上 $ N $ 以下の全ての整数 $ x $ について、次の問題を解いてください。

- $ 1,\ 2,\ 3\ \cdots,\ N $ の各整数をそれぞれ $ 0 $ 個以上 $ K $ 個以下含むような空でない多重集合であって、平均が $ x $ であるものの個数を $ M $ で割った余りを求めよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ K\ \leq\ 100 $
- $ 10^8\ \leq\ M\ \leq\ 10^9\ +\ 9 $
- $ M $ は素数である
- 入力は全て整数である

### Sample Explanation 1

$ 1 $ 以上 $ 3 $ 以下の整数をそれぞれ $ 0 $ 個以上 $ 1 $ 個以下含むような空でない多重集合を考えます。 - 平均が $ x\ =\ 1 $ である多重集合は、$ \{1\} $ の $ 1 $ 個です。 - 平均が $ x\ =\ 2 $ である多重集合は、$ \{2\},\ \{1,\ 3\},\ \{1,\ 2,\ 3\} $ の $ 3 $ 個です。 - 平均が $ x\ =\ 3 $ である多重集合は、$ \{3\} $ の $ 1 $ 個です。

### Sample Explanation 2

$ 1 $ 以上 $ 1 $ 以下の整数をそれぞれ $ 0 $ 個以上 $ 2 $ 個以下含むような空でない多重集合を考えます。 - 平均が $ x\ =\ 1 $ である多重集合は、$ \{1\},\ \{1,\ 1\} $ の $ 2 $ 個です。

## 样例 #1

### 输入

```
3 1 998244353```

### 输出

```
1
3
1```

## 样例 #2

### 输入

```
1 2 1000000007```

### 输出

```
2```

## 样例 #3

### 输入

```
10 8 861271909```

### 输出

```
8
602
81827
4054238
41331779
41331779
4054238
81827
602
8```

# 题解

## 作者：K8He (赞：12)

# [[ARC104D] Multiset Mean](https://www.luogu.com.cn/problem/AT_arc104_d)

感觉翻译的歧义好大，那先把题面翻译成人话：

------------

> 给定 $n,k$ 和 $m$。对于每个大小在 $[1, n]$ 中的 $x$，求每个元素大小在 $[1, n]$ 中，平均数为 $x$ 且相同元素不超过 $k$ 个的可重集的数量，对 $m$ 取模。
> 
> $1\le n, k\le100$，$m$ 为质数。

------------

题意有个很厉害的转化：整体减去 $x$。也就是说原来我们可以选的数是 $1\sim n$，现在选的是 $1 - x\sim n - x$。

这个时候可选的部分变为了 $[1 - x, -1], 0$ 和 $[1, n - x]$ 三个部分。$0$ 随便选，有 $k + 1$ 种方案。然后要求在 $[1 - x, -1]$ 中和在 $[1, n - x]$ 中选的元素之和相加为零，考虑背包预处理。注意减去空集情况。

$f_{i, j}$ 表示选 $1\sim i$ 的数，和为 $j$ 的方案数。

答案就是：

$$
(k + 1)\sum_{j = 0}^{\frac{n(n + 1)k}{2}}f_{i - 1, j}f_{n - i, j} - 1
$$

~~前天模拟赛刚好学到前缀和优化多重背包，可以优化到 $O(n^2k)$。~~

Update on 2023/10/18：

错了，这个上限是 $O(n^2k)$ 级别的，总复杂度应该是 $O(n^3k)$，感谢 @[369Pai](https://www.luogu.com.cn/user/290023) 指出。

我不知道谁贺的谁的，题解区全说时间复杂度是 $O(n^2k)$。

Code:

```cpp
const ll N = 110;
namespace SOLVE {
	ll n, k, P, f[N][N * N * N], ans[N];
	inline ll rnt () {
		ll x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}
	inline void In () {
		n = rnt (), k = rnt (), P = rnt ();
		return;
	}
	inline void Solve () {
		f[0][0] = 1;
		ll sum = 0, l = 0;
		_for (i, 1, n) {
			sum += i * k, l += k + 1;
			_for (j, 0, i - 1) f[i][j] = f[i - 1][j];
			_for (j, i, sum) f[i][j] = (f[i - 1][j] + f[i][j - i]) % P;
			for_ (j, sum, l) f[i][j] = (f[i][j] - f[i][j - l] + P) % P;
		}
		_for (i, 1, n) {
			ans[i] = 0;
			_for (j, 0, sum) ans[i] = (ans[i] + f[i - 1][j] * f[n - i][j] % P) % P;
			ans[i] = (ans[i] * (k + 1) % P - 1 + P) % P;
		}
		return;
	}
	inline void Out () {
		_for (i, 1, n) printf ("%lld\n", ans[i]);
		return;
	}
}
```

---

## 作者：wjh2011 (赞：5)

## 题意：

对于每个在区间 $[1, n]$ 中的 $x$，求平均数为 $x$，取值在 $[1, n]$ 中且重复元素个数不超过 $k$ 的非空集合的个数，答案对 $m$ 取模。

## 思路：

如果平均数为 $x$，则这些数的和为 $x*cnt$，其中 $cnt$ 为集合元素的个数。

由于 $cnt$ 无法确定，所以我们可以让 $x=0$，于是问题变成了在 $[1 - x, n - x]$ 中选出一些数，这些数和为 $0$ 且重复元素个数不超过 $k$。

要让和为 $0$，$0$ 可以选 $0$ 个到 $k$ 个，前 $x-1$ 个数的绝对值的和等于后 $n-x$ 个数的绝对值的和。

我们可以用 $dp_{i, j}$ 表示前 $i$ 个数和为 $j$ 的方案数，可以用前缀和优化的多重背包求出 $dp_{i, j}$，时间复杂度 $O(n^{2}k)$。

答案为
$$(k+1) * \sum_{j = 0}^{\frac {n*k*(n+1)} {2}} dp_{i - 1, j} * dp_{n - i, j} - 1$$

减一是因为答案不能为空集。

## 代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k, mod, sum, ans, dp[105][1000005];
signed main()
{
    cin >> n >> k >> mod;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= sum; j++)
            dp[i][j] = dp[i - 1][j];
        sum += i * k;
        for (int j = i; j <= sum; j++)
            dp[i][j] = (dp[i][j] + dp[i][j - i]) % mod;
        int cnt = i * (k + 1);
        for (int j = sum; j >= cnt; j--)
            dp[i][j] = ((dp[i][j] - dp[i][j - cnt]) % mod + mod) % mod;
    }
    for (int i = 1; i <= n; i++)
    {
        ans = 0;
        for (int j = 0; j <= sum; j++)
            ans = (ans + (k + 1) * dp[i - 1][j] % mod * dp[n - i][j] % mod) % mod;
        cout << (ans - 1 + mod) % mod << "\n";
    }
    return 0;
}
```

---

## 作者：WeWantToRun (赞：4)

讲个笑话：我看完所有题解加上网上搜索硬是没学会前缀和优化多重背包计数。

于是我想了一个小时才会。

显然平均数左右一正一负本质相同，于是问题转化成 $1\sim i$ 每个数 $k$ 个，总和等于 $j$ 的方案数计数，最后答案就是 $(k+1)\sum _j f_{x-1,j}f_{n-x,j}-1$。

然后大力求这个 $f_{i,j}$ 显然是 $O(n^5)$ 带一个几十分之一的常数，运气好就过去了。然后考虑转移是 $f_{i,j}=\sum _{t\le k}f_{i-1,j-ti}$，所以考虑把 f 当成 $i$ 个数组，每个数组分别做前缀和，然后就可以 $O(1)$ 转移，时间复杂度 $O(n^4)$。

---

## 作者：DaiRuiChen007 (赞：3)

# ARC104D 题解



## 思路分析

看到平均数 $=x$ 立刻想到让可选元素集从 $\{1,2,\cdots n\}$ 变成 $\{1-x,2-x,\cdots ,n-x\}$，然后求和 $=0$ 的方案数。

把可选元素看成 $-1\sim -(x-1),0,1\sim n-x$ 三个部分，枚举正数部分的权值和 $i$，那么负数部分的权值和就是 $-i$，而 $0$ 可以选择 $0\sim k$ 次。

因此，我们先用 dp 预处理出 $dp_{i,j}$ 表示用 $1\sim i$ 凑出 $j$ 的和的方案数，那么答案为：
$$
(k+1)\times \sum_{i=0}^\infty dp_{n,x-1}\times dp_{n,n-x}-1
$$
最终答案 $-1$ 是因为减去全为 $0$ 的集合。

而 $dp_{i,j}$ 可以用前缀和优化多重背包的做法，把时间复杂度从 $\Theta(n^3k)$ 降到 $\Theta(n^2k)$。

时间复杂度 $\Theta(n^2k)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=101,MAXS=1e6+1;
int dp[MAXN][MAXS];
signed main() {
	int n,k,mod;
	scanf("%lld%lld%lld",&n,&k,&mod);
	int sum=0;
	dp[0][0]=1;
	for(int i=1;i<=n;++i) {
		sum+=i*k;
		memcpy(dp[i],dp[i-1],sizeof(dp[i]));
		for(int j=i;j<=sum;++j) dp[i][j]=(dp[i][j]+dp[i][j-i])%mod;
		int tmp=(k+1)*i;
		for(int j=sum;j>=tmp;--j) dp[i][j]=(dp[i][j]+mod-dp[i][j-tmp])%mod;
	}
	for(int x=1;x<=n;++x) {
		int ans=0;
		for(int i=0;i<=sum;++i) ans=(ans+dp[x-1][i]*dp[n-x][i]%mod)%mod;
		ans=(ans*(k+1)%mod+mod-1)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：Minecraft万岁 (赞：3)

首先，我们考虑如何判断一个集合的平均数 $=x$ ，如果将所有数全部减去 $x$ ，那么只要所有元素的和 $=0$ ，那么平均数 $=x$。  

假设当前算到的答案为 $x$，那么 $1$ 到 $n$ 减去 $x$ 后变为   
$$-x+1,-x+2,....,-1,0,1,2,...n-x$$
我们设 $f_{i,j}$ 表示由 $1$ 到 $i$ 构成和为 $j$ 方案，由此我们可以得出
$$ ans_x= \sum\limits_{j=0}^{maxsum}{f_{x-1,j} \times f_{n-x,j}} \times (k+1) - 1 $$

即让前后的正负相互抵消，而 $x$ 选多少个都无所谓，但是不能一个都不选，故最后应该 $-1$ 。  

发现 $f_{i,j}$ 是经典的多重背包计数，如果用前缀和优化，复杂度是 $O(n^3)$ 的，可以通过本题。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=105;
int n,k,mod;
int f[105][505005],ans;
int sum[505005],tot;
inline void read(int &x) 
{
	int f=1;char c;
	for(x=0,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48); x*=f;
} 
inline int mn(int _x,int _y){return _x<_y?_x:_y;}
inline int mx(int _x,int _y){return _x>_y?_x:_y;}
inline int ab(int _x){return _x<0?-_x:_x;}
inline void add(int &x,int y){x=(x+y>=mod?x+y-mod:x+y);}

int main()
{
	read(n);read(k);read(mod);
	f[0][0]=1;tot=0;
	/*这里使用了前缀和优化 对 -i -2i -3i ... -ki 做前缀和*/
	for(int i=1;i<=n;i++){
		tot+=i*k;
		for(int j=0;j<=tot;j++){
			sum[j]=f[i-1][j];
			if(j-i>=0) sum[j]=(sum[j]+sum[j-i])%mod;
			f[i][j]=sum[j];
			if(j-i*(k+1)>=0) f[i][j]=(f[i][j]-sum[j-i*(k+1)]+mod)%mod; 
		}
	}
    
    /*计算答案*/
	for(int i=1;i<=n;i++){
		ans=0;
		for(int j=0;j<=tot;j++)
			ans=(ans+1ll*f[i-1][j]*f[n-i][j]%mod)%mod;
		ans=1ll*ans*(k+1ll)%mod;
		ans=(ans-1+mod)%mod;
		printf("%d\n",ans);
	}
	return 0;	
}  

```


---

## 作者：Isharmla (赞：2)

题目相当于让你在 $[1,n]$ 种选 $cnt$ 个数，且每一个数的数量不超过 $k$ 的情况下，平均数为 $x$ 的方案数。本质上就是使得这些数和为 $x \times cnt$。这并不好搞，我们不妨对每一个数都减去 $x$。此时，就相当于在求 $(x-x) \times cnt$ 也就是这些数和为 $0$ 了，这是一个很好搞的东西，我们相当于是在 $[1-x,-1]$ 和 $0$ 和 $[1,n-x]$ 三个区间拿东西。我们用 $f_{i,j}$ 表示前 $i$ 个数和为 $j$ 的方案数很自然就可以推出方程。
$$(k+1) \times \sum_{j=1}^{Maxsum} f_{i-1,j}\times f_{n-i,j}-1$$
其中 $Maxsum$ 表示我们可以的到的最大和，减一是为了防止空集。复杂度 $O(n^3k)$。

---

## 作者：Super_Cube (赞：1)

# Solution

要求可重集平均数为 $x$，那么将可重集中每个数都减去 $x$，依然符合要求的条件为所有元素之和为 $0$。原来是在 $[1,n]$ 中选数，现在就是在 $[1-x,n-x]$ 中选数使得和为 $0$。由于 $0$ 不影响和，可转化为在 $[1,x-1]$ 与 $[1,n-x]$ 这两部分中选数使得两边的和相等。

设 $dp_{i,j}$ 表示在 $[1,i]$ 中选了一些数使得和为 $j$ 的方案数。初始化 $dp_{0,0}=1$。枚举选 $i$ 的个数为 $c$，有转移：$dp_{i,j}=\displaystyle\sum_{c=0}^kdp_{i-1,j-ci}$。答案为 $-1+(k+1)\sum dp_{x-1,i}\cdot dp_{n-x,i}$，因为可以选 $0\sim k$ 个 $0$，此外还要减去全部不选即可重集为空的这种情况。

时间复杂度：$O(n^3k^2)$，但是严重跑不满。

---

## 作者：rainygame (赞：1)

以下设 $f(x)=\dfrac{x(x+1)}{2}$。

观察样例可以发现，只需要求出 $x \le \lceil\dfrac{n}{2}\rceil$ 的答案就可以了，剩下的对称一下即可。

注意到若将每个数改为它减去 $x$ 的绝对值，那么原序列变为 $b=\{\dots,2,1,0,1,2,\dots\}$。设选出小于 $x$ 的数在 $b$ 里的和为 $S_1$，大于 $x$ 的数为 $S_2$，那么必然有 $S_1=S_2$。

对于这类和固定的选数问题，考虑背包。考虑维护 $x$ 左右两边的背包，但是删除右边背包的一个数感觉很难做。

再次注意到两边的背包本质是相同的——它们都维护了 $k$ 个在 $[1,t]$ 的数，考虑直接预处理出来。设 $f_{i,j}$ 表示只考虑 $[1,i]$ 之间的数，且和恰好为 $j$ 的方案数。显然 $f_{i,j}$ 相当于 $f_{i-1,j}$ 再加入 $k$ 个 $i$，注意转移细节。

时间复杂度理论上为 $O(n^3k^2)$，注意到求 $f_i$ 只需要转移不超过 $kf(\lceil \dfrac{n}{2}\rceil)$ 的背包。具体地，对于 $i<\lceil \dfrac{n}{2}\rceil$ 只需要转移 $kf(i)$ 的背包，对于 $i \ge \lceil\dfrac{n}{2}\rceil$ 只需要转移 $kf(n-i-1)$ 的背包（因为 $x$ 左边的不可能凑出超过 $kf(n-i-1)$ 的和），所以实际计算量非常小。

还可以发现每次转移时都取模太浪费了，不若开 `long long` 之后把取模放到最后统一执行。

然后就可以过了。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100
#define MAXM 130001
#define ct(x) (((x)+1)*(x)/2)

int n, np, k, p;
int ans[MAXN];
long long f[MAXN][MAXM];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> k >> p; np = (n-1)/2+1; f[0][0] = 1;
	for (int i(1); i<n; ++i){
		memcpy(f[i], f[i-1], sizeof(f[i]));
		int ft((i<np?ct(i):ct(n-i-1))*k);
		for (int j(1); j<=k; ++j){
			for (int l(ft), ed(i*j); l>=ed; --l) f[i][l] += f[i-1][l-ed];
		}
		for (int j(0); j<=ft; ++j) f[i][j] %= p;
	}

	for (int i(1); i<=np; ++i){
		long long res(0);
		for (int j(0); j<=ct(i-1)*k; ++j){
			(res += f[i-1][j]*f[n-i][j]) %= p;
		}
		res = (res*(k+1)-1+p)%p;
		cout << (ans[i]=res) << '\n';
	}
	if (n % 2 == 0) cout << ans[np] << '\n';
	for (int i(np-1); i; --i) cout << ans[i] << '\n';

	return 0;
}
```

这份代码跑得很优秀，貌似很多复杂度比它优的题解都比它慢很多。

---

## 作者：User_Authorized (赞：0)

# 题意

给定 $N,K$ 和 $M$。对于每个大小在 $[1,N]$ 中的 $x$，求每个元素大小在 $[1,N]$ 中，平均数为 $x$ 且相同元素不超过 $K$ 个的可重集的数量，对 $M$ 取模。

$1 \le N,K \le 100$，$M$ 为质数。

## 题解

发现对于 $x$，若存在一个合法的集合 $S$，那么有

$$\sum\limits_{y \in S} (x - y) \left[y < x\right] = \sum\limits_{y \in S} (y - x) \left[y > x\right]$$

成立，设 $sum = \sum\limits_{y \in S} (x - y) \left[y < x\right]$，那么可以通过枚举 $sum$ 的值实现计算答案。

现在问题转化为了求使用 $[1, i]$ 中的数构成和为 $sum$ 的集合的数量，这个问题可以通过背包 $\tt{DP}$ 解决。

设 $f_{i, j}$ 表示使用 $[1, i]$ 中的数构成和为 $j$ 的集合的数量，那么有

$$f_{i, j} = \sum\limits_{x = 0}^{K} f_{i - 1, j - i \times x}$$

直接暴力做的话复杂度为 $\mathcal{O}(N^4K)$，写得好的话是可以通过的。

但是我们可以通过使用前缀和优化来通过，这样的话复杂度为 $\mathcal{O}(N^3K)$，可以通过。

## Code

$\mathcal{O}(N^4K)$

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

valueType MOD;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, K;

    std::cin >> N >> K >> MOD;

    valueType const S = K * N / 2 * (N / 2 + 1) / 2;

    ValueMatrix F(N + 1, ValueVector(S + 1, 0));

    F[0][0] = 1;

    for (valueType i = 1; i <= N; ++i) {
        F[i] = F[i - 1];

        for (valueType k = 1; k <= K; ++k)
            for (valueType j = std::min(i * k + K * (i - 1) * i / 2, S); j >= i * k; --j)
                Inc(F[i][j], F[i - 1][j - i * k]);
    }

    for (valueType i = 1; i <= N; ++i) {
        valueType ans = 0;

        for (valueType j = 1; j <= S; ++j) {
            if (F[i - 1][j] == 0 || F[N - i][j] == 0)
                break;
            else
                Inc(ans, mul(F[i - 1][j], F[N - i][j]));
        }

        Mul(ans, K + 1);
        Inc(ans, K);

        std::cout << ans << std::endl;
    }

    return 0;
}
```

---

$\mathcal{O}(N^3K)$

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

valueType MOD;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, K;

    std::cin >> N >> K >> MOD;

    valueType const S = K * N / 2 * (N / 2 + 1) / 2;

    ValueMatrix F(N + 1, ValueVector(S + 1, 0));

    F[0][0] = 1;

    for (valueType i = 1; i <= N; ++i) {
        F[i] = F[i - 1];

        for (valueType j = i; j <= S; ++j)
            Inc(F[i].at(j), F[i][j - i]);

        for (valueType j = S; j >= i * (K + 1); --j)
            Dec(F[i][j], F[i][j - i * (K + 1)]);
    }

    for (valueType i = 1; i <= N; ++i) {
        valueType ans = 0;

        for (valueType j = 1; j <= S; ++j) {
            if (F[i - 1][j] == 0 || F[N - i][j] == 0)
                break;
            else
                Inc(ans, mul(F[i - 1][j], F[N - i][j]));
        }

        Mul(ans, K + 1);
        Inc(ans, K);

        std::cout << ans << std::endl;
    }

    return 0;
}
```

---

