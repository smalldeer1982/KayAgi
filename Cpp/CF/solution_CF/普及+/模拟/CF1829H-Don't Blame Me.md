# Don't Blame Me

## 题目描述

Sadly, the problem setter couldn't think of an interesting story, thus he just asks you to solve the following problem.

Given an array $ a $ consisting of $ n $ positive integers, count the number of non-empty subsequences for which the bitwise $ \mathsf{AND} $ of the elements in the subsequence has exactly $ k $ set bits in its binary representation. The answer may be large, so output it modulo $ 10^9+7 $ .

Recall that the subsequence of an array $ a $ is a sequence that can be obtained from $ a $ by removing some (possibly, zero) elements. For example, $ [1, 2, 3] $ , $ [3] $ , $ [1, 3] $ are subsequences of $ [1, 2, 3] $ , but $ [3, 2] $ and $ [4, 5, 6] $ are not.

Note that $ \mathsf{AND} $ represents the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

## 样例 #1

### 输入

```
6
5 1
1 1 1 1 1
4 0
0 1 2 3
5 1
5 5 7 4 2
1 2
3
12 0
0 2 0 2 0 2 0 2 0 2 0 2
10 6
63 0 63 5 5 63 63 4 12 13```

### 输出

```
31
10
10
1
4032
15```

# 题解

## 作者：SunnyYuan (赞：16)

### 题意：

给定一个长度为 $n$ 的数组，选择它的一个子序列（不一定要连续的），问有多少种选法使得它们 AND 的值的二进制表示法中有 $k$ 个 $1$。

### 思路：

这个题就是一个简单的 DP，

设 $f_{i,j}$ 表示选择到了第 $i$ 个数字（但不一定是把前 $i$ 个数字都选择了），所有被选择的数字的 AND 值等于 $j$ 的方案数。

那么我可以不选择这个数字：$f_{i,j} = f_{i,j} + f_{i-1,j}$，即与选择 $i - 1$ 个数字，数字的 AND 的值为 $j$ 的方案数一样。

那么我们也可以选择这个数字：$f_{i,j\& a_i} = f_{i,j\& a_i} + f_{i - 1,j}$，即从前 $i - 1$ 个数得到的 $j$ 与上一个 $a_i$ 就有前 $i$ 个数字得到的 $j\&a_i$。

当然，我们为什么一定要让第 $i$ 个数字受到前面的数字的影响呢？我们可以另起炉灶！即 $f_{i, a_i}=1$。

这就讨论完了所有情况。

归纳总结起来就是

$$
\begin{cases}
 f_{i,j} = f_{i,j} + f_{i-1,j} \\
 f_{i,j\& a_i} = f_{i,j\& a_i} + f_{i - 1,j} \\
 f_{i, a_i}=1 \\
\end{cases}
$$


### 代码：

```
#include <bits/stdc++.h>

using namespace std;

const int N = 200010, mod = 1e9 + 7;

int f[N][64];
int n, k;
int a[N];

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) memset(f[i], 0, sizeof(f[i]));
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        f[i][a[i]] = 1;
        for (int j = 0; j < 64; j++) {
            f[i][j] = (1ll * f[i][j] + f[i - 1][j]) % mod;
            f[i][j & a[i]] = (1ll * f[i][j & a[i]] + f[i - 1][j]) % mod;
        }
    }
    int res = 0;
    for (int i = 0; i < 64; i++) {
        int cnt = 0;
        for (int j = 0; j < 6; j++) {
            if (i >> j & 1) cnt++;
        }
        if (cnt == k) res = (1ll * res + f[n][i]) % mod;
    }
    cout << res << '\n';
}

int main() {
    #ifdef DEBUG
    freopen("Test.in", "r", stdin);
    cout << "===================START===================" << endl;
    #endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    #ifdef DEBUG
    cout << "====================END====================" << endl;
    #endif
    return 0;
}
```

---

## 作者：YipChip (赞：9)

这是一个 SOSDP 的板子题，时间复杂度 $O(k2^k +n)$，但在微弱的数据范围前并不能体现出 SOSDP 的优越性。

### 形式化题意

给定序列 $a_1,a_2,...,a_n$，求出 $\sum\limits_{a_i \& a_j \& ... = t}1$（其中 $t$ 的二进制中恰好有 $m$ 个 $1$）。

### 题解

我们用集合的方式来表示一个二进制数，如此，如果 $a_i$ 是 $a_j$ 的子集，我们的与运算可以表示为 $a_i \& a_j = a_i$，而我们要的状态转移便是利用了这个性质。

我们设 $a_i$ 表示集合 $i$ 的个数（**注意：我们认为 $i$ 的二进制中 $1$ 的位置为元素**），如果 $i \& j = i$，那么此时 $i ∈ j$，$a_j$ 显然要加上 $a_i$ ，为了加的时候不重复，我们要首先指定一个元素不被存在，转移到该元素存在的集合中，学过高位前缀和的同学可以列出如下转移式：

```cpp
if (i & 1 << j) a[i] += a[i ^ 1 << j];
```

而题目要求我们的元素实际上不是 $1$ 的位置，而是 $0$ 的位置，因此将条件取反即可。

`k` 是集合元素个数，`(1<<k)-1` 表示全集。

```cpp
for (int j = 0; j < k; j ++ )
	for (int i = 0; i < 1 << k; i ++ )
		if (!(i & 1 << j))
			a[i] += a[i ^ 1 << j];
```

此时我们发现每一个 $i$ 的子集个数恰好不重复的加入了我们的 $a_i$ 中，这样得到的 $a_i$ 代表了集合 $i$ 的所有子集的总个数。

我们再设置一个 $p_i$ 数组表示 $2$ 的 $i$ 次幂，$dp_i$ 表示集合 $i$ 的子集任意匹配，总共有 $2^{a_i}$ 个匹配数，原因是我们可以把 $dp$ 数组看成一个大集合，大集合中有 $a_i$ 个小集合，求大集合的子集个数，即选出的小集合子序列，也可以称为原题目中要求的与子序列的个数。

我们发现 $dp_i$ 的匹配在子集 $j$ 中计算过了，即（$j ∈ i$），而同样 $k ∈ j$ 中又有 $dp_j$ 的计算，因此我们做反向运算（即高维差分，也可以理解为容斥）求回真正不重复的匹配数。

```cpp
for (int j = 0; j < k; j ++ )
	for (int i = 0; i < 1 << k; i ++ )
		if (!(i & 1 << j))
			dp[i] -= dp[i ^ 1 << j];
```

如此，我们的答案就是 $\sum\limits_{\text{i 的二进制中恰好有 m 个 1}}dp_i$。

而为全集时，即 $m = k$ 时，我们会发现 $\emptyset$ 也被考虑成一个单独的子序列了，因此我们减去 $1$。

由于多测数据记得清空 $a$ 数组，~~昨晚上被这个坑惨了(~~

参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const ll mod = 1e9 + 7;
int n, m;
ll a[1 << 6], p[N], dp[1 << 6];
int main()
{
	int T;
	scanf("%d", &T);
	p[0] = 1;
	for (int i = 1; i < N; i ++ ) p[i] = (p[i - 1] << 1) % mod;
	while (T -- )
	{
		memset(a, 0, sizeof a);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i ++ )
		{
			int x;
			scanf("%d", &x);
			a[x] ++ ;
		}
		for (int j = 0; j < 6; j ++ )
			for (int i = 0; i < 1 << 6; i ++ )
				if (!(i & 1 << j))
					a[i] += a[i ^ 1 << j];
		for (int i = 0; i < 1 << 6; i ++ ) dp[i] = p[a[i]];
		for (int j = 0; j < 6; j ++ )
			for (int i = 0; i < 1 << 6; i ++ )
				if (!(i & 1 << j))
					dp[i] = (dp[i] - dp[i ^ 1 << j] + mod) % mod;
		ll ans = 0;
		for (int i = 0; i < 1 << 6; i ++ )
			if (__builtin_popcountll(i) == m)
				ans = (ans + dp[i]) % mod;
		if (m == 6) ans = (ans - 1 + mod) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：SkyLines (赞：3)

## Solution

$dp_{i,j}$ 表示前 $i$ 个数的子序列，按位与为 $j$ 的方案数。

很明显有：

$dp_{i,j}=dp_{i,j}+dp_{i-1,j}$（不选第 $i$ 个）

$dp_{i,a_i\&j}=dp_{i,a_i\&j}+dp_{i,j}$（选第 $i$ 个）

最后统计 $\text{popcount}(i)=k$ 的 $dp$ 总和即可。

## Code

```cpp
scanf("%lld", &t);
	for(int kk = 1; kk <= t; kk++){
		now = 1;
		ans = 0;
		scanf("%lld %lld", &n, &k);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i <= n; i++){
			for(int j = 0; j < 75; j++) dp[now][j] = 0;
			dp[now][a[i]]++;
			for(int j = 0; j < 64; j++){
				dp[now][j] = (dp[now][j] + dp[now ^ 1][j]) % mod;
				dp[now][j & a[i]] = (dp[now][j & a[i]] + dp[now ^ 1][j]) % mod;
			}
			now ^= 1;
		}
		for(int i = 0; i < 64; i++) if(__popcount(i) == k) ans = (ans + dp[now ^ 1][i]) % mod;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 75; j++){
				dp[i][j] = 0;
			}
		}
		printf("%lld\n", ans);
	}
```

---

## 作者：andyli (赞：2)

设 $f_x$ 表示当前按位与结果为 $x$ 的子序列数，则可以从之前的状态转移：
```cpp
g[a[i] & x] += f[x];
```
对于每个 $x$，将 $f_x$ 添加到 $f_{a_i \operatorname{and} x}$ 中，表示考虑当前数 $a_i$ 时，可以从之前的状态 $x$ 转移到 $a_i \operatorname{and} x$。  
以及考虑子序列仅包含当前数的情况：
```cpp
g[a[i]]++;
```
表示考虑子序列仅包含当前数 $a_i$ 的情况。  
最后统计 $\operatorname{popcount}$ 结果为 $k$ 的 $x$ 对应的值 $f_x$。

```cpp
int main() {
    multipleTests([&] {
        dR(int, n, k);
        dRV(int, a, n);
        Vec<Z> f(64);
        _for (i, n) {
            auto g = f;
            _for (x, 64)
                g[a[i] & x] += f[x];
            g[a[i]]++;
            f = std::move(g);
        }
        Z ans;
        _for (x, 64U)
            if (std::popcount(x) == k)
                ans += f[x];
        writeln(ans);
    });
    return 0;
}
```

---

## 作者：theb0t (赞：2)

update on 2024.8.29：根据[最新规则](https://help.luogu.com.cn/rules/academic/solution-standard#%E5%9B%BE%E7%89%87%E4%B8%8E%E4%BB%A3%E7%A0%81)，去掉了防抄袭内容。

***

动态规划好题。

对于此题解，不懂的问题可以私信笔者。

[前置知识](https://oi-wiki.org/math/bit/)

# 解题方法

用 $dp_{i,j}$ 表示前 $i$ 个数选择了若干个数按位与之后为 $j$ 的子序列个数。

**接下来思考转移。**

想到这里，你会发现按位与没有逆运算，一次我们要正推，例如 $f_{i+2}=f_{i}+f_{i+1}$。

那么转移方程不就来了嘛：

第 $i+1$ 个数按位与 $j$ 等于 原来的加上 $dp_{i,j}$。

$$dp_{i+1,j \& a_{i+1}}=
dp_{i+1,j \& a_{i+1}}+dp_{i,j}$$

还有就是不将第 $i$ 个数加入此序列。

$$dp_{i+1,j}=dp_{i+1,j}+dp_{i,j}$$

其中 $\&$ 是按位与。

# 边界

计数题一定要有边界，否则算了等于白算（只有 $0$）。

$dp_{0,63}=1$，但是要特判。

特判：$dp_{0,63}=1$ 相当于是空序列，是“借”的，因此当 $k=6$ 时答案要减 $1$（因为此时 $63$ 刚好有 $6$ 个 $1$（二进制下））。

# code

`__builtin_popcount(i)` 表示计算 $i$ 的二进制中有多少个 $1$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
#define mod 1000000007
int a[200005];
ll dp[200005][70];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n,k;
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=0;i<=n;i++){
			for(int j=0;j<=63;j++){
				dp[i][j]=0;
			}
		}
		dp[0][63]=1;
		for(int i=0;i<n;i++){
			for(int j=0;j<=63;j++){
				dp[i+1][j&a[i+1]]=(dp[i+1][j&a[i+1]]+dp[i][j])%mod;
				dp[i+1][j]=(dp[i+1][j]+dp[i][j])%mod;
			}
		}
		ll ans=0;
		for(int i=0;i<=63;i++){
			if(__builtin_popcount(i)==k) ans=(ans+dp[n][i])%mod;
		}
		if(k==6) ans=((ans-1)+mod)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：ZBH_123 (赞：1)

## 题目分析
本题是一道 DP 的题目。既然是 DP 的题目，那么就有设计状态、推导状态转移方程、输出答案三个步骤。
### 1.设计状态
对于本题，我们可以设 $dp_{i,j}$ 为选到第 $i$ 个数（不一定要选第 $i$ 个数），且按位与结果为 $j$ 的方案数。
### 2.推导状态转移方程
既然状态设计的是选到第 $i$ 个数，但不一定要选第 $i$ 个数的方案数，那我们就把选不选第 $i$ 个数作为分类的标准来分类讨论。如果不选第 $i$ 个数，那么选到第 $i$ 个数的方案数就可以加上选到第 $i-1$ 个数的方案数，即 $dp_{i,j}=dp_{i,j}+dp_{i-1,j}$。如果要选第 $i$ 个数，那么按位与的结果就要与上第 $i$ 个数，即 $dp_{i,j \operatorname{and} a_i}=dp_{i,j \operatorname{and} a_i}+dp_{i-1,j}$。
### 3.输出答案
由于题目给出的 $k$ 表示二进制位有 $k$ 个 $1$，那我们就要在 $0 \sim 63$ 中找到所有二进制位中有 $k$ 个 $1$ 的数，并将方案数累加。这里我推荐的找二进制中有多少个 $1$ 的方法是不停的与比当前数少 $1$ 的数进行按位与，这样当目前的数变成 $0$ 时，二进制位 $1$ 的个数也就统计出来了。
### 4.code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5,mod=1e9+7;
int t,n,m,a[maxn+5];
long long dp[maxn+5][65];
int countbit(int x){
	int cnt=0;
	while(x!=0){
		cnt++,x&=x-1;
	}
	return cnt;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			for(int j=0;j<64;j++){
				dp[i][j]=0;
			}
			dp[i][a[i]]=1;
		}
		for(int i=1;i<=n;i++){
			for(int j=0;j<64;j++){
				dp[i][j]=(dp[i][j]+dp[i-1][j])%mod,dp[i][j&a[i]]=(dp[i][j&a[i]]+dp[i-1][j])%mod;
			}
		}
		long long ans=0;
		for(int i=0;i<64;i++){
			if(countbit(i)==m){
				ans=(ans+dp[n][i])%mod;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：igAC (赞：1)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1829H)

[CFlink](https://codeforces.com/problemset/problem/1829/H)

简要题意：

问有多少个子序列的按位与的结果在二进制下有 $k$ 个 $1$。

# $\text{Solution}$

膜拜一下题解区的各位大佬，这里给出一份记忆化搜索的题解。

设 $f_{i,j}$ 表示当前是第 $i$ 位，选择前按位与的结果是 $j$。

那么 $f_{i,j}$ 可以转移到 $f_{i+1,j}$ 和 $f_{i+1,j\&a_i}$。

到达边界判断即可。

最后的答案是 $\sum_{i=1}^{n} f_{i+1,a_i}$（每个 $i$ 都可以作为起点）。

提醒一句 Codeforces 的清空不能用 memset，作者 T 的很惨。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define N 200005
#define M 64
#define Mod 1000000007
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int T,n,k,f[N][M],a[N],ans;
int dfs(int x,int sum){
	if(x==n+1) return __builtin_popcount(sum)==k;
	if(~f[x][sum]) return f[x][sum];
	int res=0;
	res=(dfs(x+1,sum)%Mod+dfs(x+1,sum&a[x])%Mod)%Mod;
	return f[x][sum]=res%Mod;
}
void solve(){
	n=read(),k=read(),ans=0;
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n+1;++i) for(int j=0;j<M;++j) f[i][j]=-1;
	for(int i=1;i<=n;++i) ans=(ans+dfs(i+1,a[i]))%Mod;
	printf("%d\n",ans);
}
int main(){
	T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：Mooncrying (赞：1)

考试的时候写挂了，过来补篇题解。

这是一道**状压 dp** 的题目。

这里是[题目传送门](https://www.luogu.com.cn/problem/CF1829H)。

### 题目大意

- 给定序列 $a (a_{i} \in [0,63],i \in [1, n])$ 和一个数 $k$，求出该序列中子序列的与运算和在二进制下有 $k$ 个 $1$ 的子序列数。

- 有 $t$ 组测试，规定 $1 \le t \le 10 ^ 4$，$sum_{n} \le 2 \times 10 ^ 5$，$0 \le k \le 6$。

### 题意分析

- 有点类似背包的思想和状态设计。

- 我们设 $f_{i, j}$ 表示选择到 $a_i$，所选数的与运算和为 $j$ 的方案数。

- 如果没有选择 $a_{i}$，则直接从选 $a_{i - 1}$ 与运算和为 $j$ 的状态转移过来，有转移方程：

	> $f_{i, j} = f_{i, j} + f_{i - 1, j}.$
    
	 如果选择了 $a_{i}$，就对状态 $f_{i,j \& a_{i}}$ 产生了影响，我们得到转移方程：

	> $f_{i,j \& a_{i}} = f_{i,j \& a_{i}} + f_{i - 1, j}.$
    
	如果再把 $f_{i, j}$ 放在转移方程左边，我们会发现转移极其困难，因此采取了正着转移的写法。
    
- 注意初始化：$f_{i, a_{i}} = 1$。

- 最后枚举所有 $j$，若 $j_i$ 在二进制下 $1$ 的个数恰好为 $k$，就把 $f_{n, j_{i}}$ 加入答案。

- 多测，注意清空。

- 别忘了取模，别爆 int。

- 本题结束，时间复杂度为 $O(n \cdot 2 ^ 6)$。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
const int N = 2e5 + 10;
int f[N][70], ans, T, n, k, a[N];
template <typename T> void read(T &x)
{
	T f = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
	x *= f;
}
int num1(int x)
{
	int cnt = 0;
	while(x) { if(x & 1) cnt++; x >>= 1; }
	return cnt;
}// 求二进制下 1 的个数
int main()
{
	read(T);
	while(T--)
	{
		read(n); read(k); ans = 0;
		for(int i = 1; i <= n; ++i) memset(f[i], 0, sizeof(f[i])); 
		for(int i = 1; i <= n; ++i) read(a[i]), f[i][a[i]] = 1;
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j < 64; ++j)
				f[i][j] = (1ll * f[i][j] + f[i - 1][j]) % mod, 
				f[i][j & a[i]] = (1ll * f[i][j & a[i]] + f[i - 1][j]) % mod;
		for(int i = 0; i < 64; ++i)
			if(num1(i) == k) ans = (1ll * ans + f[n][i]) % mod;
		printf("%d\n", ans);
	}
}
```


---

## 作者：ncwzdlsd (赞：0)

DP。

设计状态 $f(i,j)$ 表示以 $i$ 为结尾的子序列，与运算和为 $j$ 的方案数。

状态转移考虑选 / 不选 $a_i$ 的方案数：

$$
\begin{aligned}
f(i,j)&=f(i,j)+f(i-1,j)\\
f(i,j\&a_i)&=f(i,j\&a_i)+f(i-1,j)
\end{aligned}
$$

对于 $a_i$，它自己可以成为一个与运算和为 $a_i$ 的子序列。

找到每一个满足 $\text{popcount}(i)=k$ 的 $i$，答案即为：$\sum f(n,i)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7,maxn=2e5+5;
int a[maxn],f[maxn][65];

int popcount(int x)
{
    int cnt=0;
    while(x) x&=(x-1),cnt++;
    return cnt;
}

void solve()
{
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) memset(f[i],0,sizeof f[i]),f[i][a[i]]=1;
    for(int i=1;i<=n;i++) 
        for(int j=0;j<64;j++) f[i][j]=(f[i-1][j]+f[i][j])%mod,f[i][j&a[i]]=(f[i-1][j]+f[i][j&a[i]])%mod;
    int ans=0;
    for(int i=0;i<64;i++) if(popcount(i)==k) ans=(ans+f[n][i])%mod;
    cout<<ans<<endl;
}

signed main()
{
    int t;cin>>t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：technopolis_2085 (赞：0)

题意：

给你一个长 $n$ 的数组，让你求有多少个子序列，使得子序列中的数的按位与结果的二进制有 $k$ 个 $1$。

$n ≤ 2 × 10^5$，$k ≤ 6$。

$a_i ≤ 63$。

分析：

很明显是一个 dp。

设 $dp_i,_j$ 表示考虑到第 $i$ 个元素，子序列中按位与的结果为 $j$ 的方案个数。

设 $x$ 为 $j$ 与 $a_i$ 按位与运算的结果。

那么 $dp_i,_x$ 可以从每一个满足 $dp_k,_j$ 转移过来，其中 $k ≤ i$。

这样转移的复杂度是 $O(n^2V)$ 的，会超时。

考虑优化。

我们发现我们并不需要枚举每一个 $k$，而可以开一个 $sum_j$ 数组，表示子序列中按位与的结果为 $j$ 的总数。

这样，$dp_i,_x$ 可以从 $sum_j$ 转移过来。

转移后，还要更新 $sum$ 数组，此时 $sum_j$ 要加上 $dp_i,_j$。

答案为所有满足二进制中 $1$ 的个数的 $j$ 的 $sum_j$ 加和。

这样就做完了，时间复杂度为 $O(nV)$，$V$ 代表 $a_i$ 的值域。

注意：要开 long long，记得清空数组。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7;
const int maxn=2e5+10;
int a[maxn];
int dp[maxn][66];
int sum[66];

bool check(int x,int aim){
	int ans=0;
	while (x>0){
		if (x%2==1) ans++;
		x/=2;
	}
	return ans==aim;
}

signed main(){
	int T;
	scanf("%lld",&T);
	
	while (T--){
		int n,k;
		scanf("%lld%lld",&n,&k);
		
		for (int i=1;i<=n;i++){
			for (int j=0;j<=63;j++) dp[i][j]=0;
		}
		for (int i=0;i<=63;i++) sum[i]=0;
		
		for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
		
		for (int i=1;i<=n;i++){
			dp[i][a[i]]=1;
			
			for (int j=0;j<=63;j++){
				dp[i][j&a[i]]=(dp[i][j&a[i]]+sum[j])%mod;
			}
			
			for (int j=0;j<=63;j++){
				sum[j]=(sum[j]+dp[i][j])%mod;
			}
		}
		
		int ans=0;
		for (int j=0;j<=63;j++){
			if (check(j,k)) ans=(ans+sum[j])%mod;
		} 
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Iniaugoty (赞：0)

## problem

每组数据中，给出一个长度为 $n$ 的**非负整数**列 $a_1\sim a_n$，和一个**非负整数** $k$，求出 $a$ 有多少个**非空**子序列，使得子序列的元素的按位与结果在二进制下恰好有 $k$ 个 $1$，答案对 $10^9+7$ 取模。

## solution

观察数据范围，发现 $a_i$ 最大只有 $2^6-1=63$，这说明可以用一些指数级的暴力算法。

爆搜显然是不行的，那就只剩状压 dp 了。

状压 dp 详见 [OI Wiki](https://oi-wiki.org/dp/state/)。

设 $dp_{i,j}$ 表示，$[1,i]$ 的子序列中，子序列元素的按位与和为 $j$ 的子序列数量。

初始化：如果子序列只有 $a_i$ 的话，按位与和为 $a_i$，即 $dp_{i,a_i}=1$。

状态转移：可以直接延续 $[1,i-1]$ 的子序列，即 $dp_{i,j}\gets dp_{i,j}+dp_{i-1,j}$；也可以将 $[1,i-1]$ 的子序列后面的添上 $a_i$，即 $dp_{i,j\operatorname{and}a_i}\gets dp_{i,j\operatorname{and}a_i}+dp_{i-1,j}$。

答案：如果 $i$ 的二进制中有 $k$ 个 $1$，则令 $ans\gets ans+dp_{n,i}$（$ans$ 表示答案）。

## code

```cpp
#include<bits/stdc++.h>
#define int long long//不开 long long 见祖宗
#define N 200005//数组开小见祖宗
#define mod 1000000007//忘记取模见祖宗
using namespace std;
int T,n,k,a[N],dp[N][64],ans;//变量含义同文字描述
signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		//多测不清空见祖宗
		//注意，如果直接 memset 的话，会超时
		for(int i=1;i<=n;i++)
			for(int j=0;j<64;j++)
				dp[i][j]=0;
		cin>>n>>k,ans=0;
		for(int i=1;i<=n;i++)//输入和初始化
			cin>>a[i],dp[i][a[i]]=1;
		for(int i=1;i<=n;i++)//状态转移
        	for(int j=0;j<64;j++){
        	    dp[i][j]=(dp[i][j]+dp[i-1][j])%mod;
        	    dp[i][j&a[i]]=(dp[i][j&a[i]]+dp[i-1][j])%mod;
        	}
		for(int i=0,j=0;i<64;i++,j=i){求答案
    		int cnt=0;
			while(j) cnt+=j&1,j>>=1;//求 1 的个数
        	if(cnt==k) ans=(ans+dp[n][i])%mod;
    	}
		cout<<ans<<"\n";
	}
	return 0;
}
```

全文完。

---

## 作者：ダ月 (赞：0)

### 题目分析：

既然是子序列的计数问题，我们可以套用模型形如 $f_{i,k}=\sum f_{j,p}$，满足 $j<i$ 且 $p\oplus a_i=k$，其中 $\oplus$ 是一种操作。其中 $f_{i,k}$ 表示选到第 $i$ 个数，当前的数为 $p$ 的方案数。

回到本题，我们可以得到 $f_{i,k}=\sum f_{j,p}$ 转移方程式，满足 $j<i$ 并且 $p\operatorname{AND}a_i=k$。

边界条件就是 $f_{0,(111111)_2}=1$。最后就是统计对于所有 $p\in[1,n]$，$i$ 在二进制下有 $k$ 个 $1$ 的所有 $f_{p,i}$ 的和。

我们暴力转移，我们可以得到 $O(n^2w^2)$，其中，$w$ 表示值域，在本题 $w=64$。显然会超时。

我们考虑优化，若当前已经处理到第 $i$ 个数，记 $\begin{aligned}g_{j}=\sum_{p=1}^{i-1}f_{p,i}\end{aligned}$，显然 $f_{i,k}=\sum g_p$，其中满足 $p\operatorname{AND}a_i=k$，每次转移完就用 $f$ 来更新 $g$ 即可。这样的话边界条件为 $g_{(111111)_2}=1$。最后统计答案的话，就是对所有满足 $i$ 在二进制下有 $k$ 个 $1$ 的 $g_i$ 的和。这样时间复杂度为 $O(nw^2)$。

不过这里要注意，如果 $k=6$ 的话，我们答案要减去 $1$，因为边界 $g_{(111111)_2}=1$ 默认了 $k=6$ 的情况下，空集也算答案。我们要减去这个空集。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pd push_back
#define all(x) x.begin(),x.end()
#define Clear(x,n) for(int i=0;i<=n;i++)x[i]=0;
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}
	void write(int x){if(!x)return;write(x/10);putchar(x%10+'0');}
	void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
}
namespace Debug{
	void DeVec(vector<int> c){for(auto y:c)printf("%d ",y);puts("");}
	void DeNum(int x){printf("%d\n",x);}
}
//==============================================================================
const int N=2e5+10;
ll g[64];
int T;
int n,m;
ll f[64];
int a[N];
const int mod=1e9+7;
int pop_count(int x){
	int ans=0;
	for(;x;x>>=1)
		ans+=(x&1);
	return ans;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    scanf("%d",&T);
    while(T--){
    	scanf("%d%d",&n,&m);
    	g[63]=1;
    	for(int i=1;i<=n;i++)
    		scanf("%d",&a[i]);
    	for(int i=1;i<=n;i++){
    		memset(f,0,sizeof(f));
    		for(int j=0;j<=63;j++){
    			for(int k=0;k<=63;k++)
    				if((k&a[i])==j)
    					f[j]=(f[j]+g[k])%mod;
			}for(int j=0;j<=63;j++)
				g[j]=(f[j]+g[j])%mod;
		}ll ans=0;
		for(int i=0;i<=63;i++)
			if(pop_count(i)==m)
				ans=(ans+g[i])%mod;
		printf("%lld\n",((ans-(pop_count(63)==m))%mod+mod)%mod);
		for(int i=0;i<=63;i++)
			g[i]=0;
	}return 0;
}


```


---

## 作者：沉石鱼惊旋 (赞：0)

[更好的阅读体验](http://blog.cyx2009.top/archives/169/)

# H.[Don&#39;t Blame Me](https://codeforces.com/contest/1829/problem/H)

## 题目翻译

> 你有一个长度为 $n$ 的数组 $a$，问有多少子序列使得选中数字按位与结果中含有 $k$ 个 $1$，答案对 $10^9+7$ 取模。
> 
> $1\leq n\leq 2\times 10^5,0\leq k\leq 6,0\leq a_i\leq 63$。
> 
> $t$ 组数据，$1\leq t\leq 10^4$。

## 题目思路

这题非常像背包，但是背包的转移是 `f[j]=max(f[j],f[j+w[i]]+value[i]);`，这题只不过是把所谓体积的转移从加法改成按位与。

这题 dp 的初值也很有意思，赛时因为最开始的初值赋错导致痛失 AK。

初值应该写成 `f[63]=1`，假设先放上一个 $(111111)_2$ 去做按位与。因为 $0$ 按位与答案一定是 $0$，后面就没意义了。

但是这样有个问题，当 $k=6$ 因为加了一个额外的 $(111111)_2$，所以会选择空集。$k=6$ 我们最后答案减一即可。

## 完整代码



```cpp
#include<bits/stdc++.h>
using namespace std;
const int p=1000000007;
void solve()
{
    int n,m;
    long long ANS=0;
    cin>>n>>m;
    int a[n+1];
    long long f[64]={},ans[64]={};
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    ans[63]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<64;j++)
        {
            f[a[i]&j]=(f[a[i]&j]+ans[j])%p;
        }
        for(int j=0;j<64;j++)
        {
            ans[j]+=f[j];
            f[j]=0;
        }
    }    
    for(int i=0;i<64;i++)
    {
        if(__builtin_popcount(i)==m)
        {
            ANS=(ANS+ans[i])%p;
        }
    }
    cout<<ANS-(m==6)<<endl;
}
int main()
{
    int t;cin>>t;while(t--)
    solve();
    return 0;
}
```



---

## 作者：未来姚班zyl (赞：0)

## 题目大意

给定序列 $a$，求按位与和的二进制下 $1$ 的个数为 $k$ 的子序列个数。

## 题目分析

难度虚高。只需要记录 $dp_{i,j}$ 表示前 $i$ 个数内按位与结果为 $j$ 的答案。暴力枚举转移即可，复杂度 $O(nV)$，$V$ 表示值域，甚至 $O(nV^2)$ 都能轻松通过。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L xd[x].l
#define R xd[x].r
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=5e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=1e9+7;
using namespace std;
int T=read(),n,k,a[N];
int dp[N][64];
int get(int x){
	int ans=0;
	while(x)ans++,x-=x&-x;
	return ans;
}
signed main(){
	while(T--){
		n=read(),k=read();
		rep(i,1,n)a[i]=read(); 
		rep(i,0,n)rep(j,0,63)dp[i][j]=0;
		dp[0][63]=1;
		rep(i,1,n)rep(j,0,63){
			dp[i][j]=dp[i-1][j];
			rep(k,0,63)if((k&a[i])==j)(dp[i][j]+=dp[i-1][k])%=mod;
		}int ans=0;
		rep(i,0,63)if(get(i)==k)(ans+=dp[n][i])%=mod;
		if(k==6)ans=(ans-1+mod)%mod;
		cout <<ans<<endl;
	}
	return 0;
}
```


---

