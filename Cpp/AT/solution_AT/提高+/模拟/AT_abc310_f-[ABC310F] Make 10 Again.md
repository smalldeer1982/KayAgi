# [ABC310F] Make 10 Again

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc310/tasks/abc310_f

$ N $ 個のサイコロがあります。 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 番目のサイコロを振ると $ 1 $ 以上 $ A_i $ 以下の整数の出目がそれぞれ等確率でランダムにでます。

$ N $ 個のサイコロすべてを同時に振るとき、その結果が下記の条件を満たす確率を $ \text{mod\ }\ 998244353 $ で求めてください。

> $ N $ 個のサイコロの中からいくつか（ $ N $ 個全部でも良い）を選ぶ方法であって、選んだサイコロの出目の和がちょうど $ 10 $ であるようなものが存在する。

  確率 $ \text{mod\ }\ 998244353 $ の定義この問題で求める確率は必ず有理数になることが証明できます。 また、この問題の制約下では、求める確率を既約分数 $ \frac{y}{x} $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。

このとき $ xz\ \equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の整数 $ z $ が一意に定まります。この $ z $ を答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ A_i\ \leq\ 10^6 $
- 入力はすべて整数
 
### Sample Explanation 1

例えば、$ 1,\ 2,\ 3,\ 4 $ 個目のサイコロの出目が順に $ 1,\ 3,\ 2,\ 7 $ だった場合、この結果は問題文中の条件を満たします。 実際、$ 2,\ 4 $ 番目のサイコロを選択すると、選んだサイコロの出目の和が $ 3\ +\ 7\ =\ 10 $ になります。 また、$ 1,\ 3,\ 4 $ 番目のサイコロを選択しても、選んだサイコロの出目の和が $ 1\ +\ 2\ +\ 7\ =\ 10 $ になります。 一方、$ 1,\ 2,\ 3,\ 4 $ 個目のサイコロの出目が順に $ 1,\ 6,\ 1,\ 5 $ だった場合、 どのようにサイコロを選んでも選んだサイコロの出目の和が $ 10 $ にならないため、この結果は問題文中の条件を満たしません。 この入力例では、$ N $ 個のサイコロを振った結果が問題文中の条件を満たす確率は $ \frac{11}{18} $ です。 よって、その $ \text{mod\ }\ 998244353 $ における値である $ 942786334 $ を出力します。

## 样例 #1

### 输入

```
4
1 7 2 9```

### 输出

```
942786334```

## 样例 #2

### 输入

```
7
1 10 100 1000 10000 100000 1000000```

### 输出

```
996117877```

# 题解

## 作者：Coffee_zzz (赞：8)

### 分析

看到求概率，想到概率 dp。

为了方便，我们令以下运算都在模 $998244353$ 的意义下进行，同时令二进制数的最低位为第 $0$ 位。

我们先求这个概率的分母。第 $i$ 个骰子正面朝上的可能是 $1\sim a_i$，共有 $a_i$ 中可能，所以这个概率的分母为 $a_1 \times a_2 \times a_3 \times \cdots \times a_N$，即 $\prod\limits_{i=1}^N a_i$。我们令其等于 $den$。

接下来我们求这个概率的分子。我们可以把“是否可以凑出 $0,1,2\cdots,10$” 都压进状态里，进行状压 dp。其中，对于状态 $S$，如果它在二进制表示下第 $i$ 位为 $0$ 则表示不能凑出 $i$，反之则表示可以凑出 $i$。容易发现有 $0 \sim 2^{11}-1$ 共 $2^{11}$ 种状态。为了方便表示，我们令 $K=2^{11}$。

- 状态定义：定义 dp 数组 $dp_{i,S}$ 表示枚举到了第 $i$ 个骰子且此时的状态为 $S$ 的方案数。

- 初始状态：当什么还没有枚举时，骰子正面朝上的数的和就为 $0$，能够凑出的只有 $0$，所以它的状态在二进制表示下只有第 $0$ 位为 $1$，可以得到状态为 $1$。所以 $dp_{0,1}=1$。

- 状态转移：

  - 我们从 $1$ 到 $N$ 枚举骰子 $i$，然后从 $1$ 到 $a_i$ 枚举点数 $j$，再从 $0$ 到 $K-1$ 枚举每一个转移来的状态 $k$，计算转移后的状态 $s$。
  
  - 如果 $k$ 在二进制表示下第 $p$ 位为 $1$，则根据状态定义可以知道，$s$ 在二进制表示下的第 $p$ 位和第 $p+j$ 位需要为 $1$。由于我们只需要记录状态在二进制表示下的前 $11$ 位，所以我们要将 $s$ 对 $K$ 取模。此时的 $s$ 即转移后的状态。
  
  - 我们将 $dp_{i,s}$ 增加 $dp_{i-1,k}$。这样做的总复杂度是 $O(N\times a_i \times K \times D)$，其中 $D=11$，无法接受，考虑优化。
  
  - 注意到我们只需要记录 $s$ 的前 $11$ 位，所以当 $j$ 大于 $10$ 时，无论什么状态，转移后的状态一定和转移前相同，所以可以一起处理。现在的复杂度为 $O(N \times K \times D^2)$，其中 $D=11$，可以接受。

- 最终答案：如果骰子的点数可以凑出 $10$，即状态在二进制表示下的第 $10$ 位为 $1$，就都需要计入分子中，设分子为 $num$，则 $num=dp_{N,K/2}+dp_{N,K/2+1}+\cdots+dp_{N,K-1}$，即 $\sum\limits^{K-1}_{S=K/2} dp_{N,S}$。

输出 $num\times den^{-1}$ 即可。

### 代码 

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353,N=105,P=12,K=2048;
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int dp[N][1<<P],n,a[N],pro=1;
signed main(){
	int s;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],pro=pro*a[i]%mod;
	dp[0][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=min(11ll,a[i]);j++){
			for(int k=0;k<K;k++){
				s=k;
				for(int p=0;p<=10;p++) if(k>>p&1) s=s|1<<(j+p);
				s=s%K;
				dp[i][s]=(dp[i][s]+dp[i-1][k])%mod;
			}
		}
		if(a[i]>10) for(int k=0;k<K;k++) dp[i][k]=(dp[i][k]+dp[i-1][k]*(a[i]-11))%mod;
	}
	int ans=0;
	for(int k=K/2;k<K;k++){
		ans=ans+dp[n][k];
		ans%=mod;
	}
	cout<<(ans*ksm(pro,mod-2))%mod;
	return 0;
}
```

---

## 作者：escapist404 (赞：6)

# AT_abc310_f Make 10 Again Solution

## Statement

你有 $N$ 个骰子和一个序列 $A_i$，第 $i$ 个骰子能等概率掷出 $1 \sim A_i$ 的点数。

在同时掷出 $N$ 个骰子后，求下面所述的条件被满足的概率模 $998,244,353$ 的值：

> 能够选出这些骰子的一个子集，使得子集内的骰子掷出的点数和为 $10$。

保证 $1 \le N \le 100$，$1 \le A_i \le {10}^6$。

## Solution

发现要求掷出的点数为 $10$，所以 $A_i$ 中比 $10$ 大的数都没有贡献。

当我们投掷一些骰子，选出它们的所有子集，对每个子集中骰子的掷出点数和取并，可以得到这些骰子可能的*贡献集合*。根据前文，贡献集合中大于 $10$ 的元素没有意义，因此我们只考虑元素 $0 \sim 10$ 是否存在于贡献集合中。这启发我们状态压缩表示这个集合。

设计 DP 状态 $f_{i, T}$ 表示：投掷前 $i$ 个骰子，使得这些骰子的贡献集合为 $T$ 的概率。

考虑转移。如果前 $i-1$ 个骰子的贡献集合中存在 $x$，掷第 $i$ 个骰子得到点数 $j$ 后，意味着前 $i$ 个骰子的贡献集合必然存在 $x+j$（$x$ 对应的子集选中骰子 $i$） 和 $x$（$x$ 对应的子集不选骰子 $x$）。即：

$$T = \mathrm{trans}( T', j) = (\{x+j|x\in T'\} \cup T') \cap \{0,1,\cdots,10\}$$

对第 $i$ 个骰子而言，掷出某个点数的概率都是 $\frac{1}{A_i}$。

对于掷第 $i$ 个骰子得到 $j \ge 10$ 时，发现新的贡献集合等于原来的（前 $i-1$ 个骰子）贡献集合，不妨认为 $j \ge 10$ 是同一个事件，其概率为 $\frac{A_i-10}{A_i}$。

对初始情况，掷了 $0$ 个骰子的贡献集合显然为 $\{0\}$，其概率为 $1$。

据此，我们得到状态转移方程

$$
f_{0, T} = \begin{cases}
0, &\textrm{when T } = \{0\}\\
1, &\textrm{otherwise}
\end{cases}
$$

$$
\begin{cases}
f_{i, \mathrm{trans}( T, j )} \gets f_{i-1, T} \times \frac{1}{A_i}, j \in \{1,2,\cdots,10\}, &\textrm{for all } A_i\\
f_{i, T} \gets f_{i-1, T} \times \frac{A_i-10}{A_i}, &\textrm{when }A_i > 10
\end{cases}
$$

其中

$$
\mathrm{trans}( T, j) = (\{x+j|x\in T\} \cup T) \cap \{0,1,\cdots,10\}
$$

答案就是掷前 $N$ 个骰子，贡献集合包含 $10$ 的概率，即 $\sum_{10 \in T} f_{N, T}$。

转移时枚举 $i, j, T$，时间复杂度 $\mathcal{O}( N \cdot 2^{w} \cdot w)$，空间复杂度 $\mathcal{O}( N \cdot 2^{w})$，这里 $w = 11$。

空间复杂度可以用滚动数组优化至 $\mathcal{O}( 2^{w})$。具体见代码实现。

## Code

```cpp
#include <array>
#include <iostream>
#include <vector>

typedef long long LL;

const LL p = 998244353;
const int mask = (1 << 11) - 1;

LL qpow(LL a, LL b) {
	return b ? (b & 1 ? a * qpow(a, b - 1) % p : qpow(a * a % p, b / 2) % p) : 1ll;
}

int main() {
	int n;
	std::cin >> n;

	std::vector<std::array<LL, (1 << 11)>> f(2);

	f[0][1] = 1;
	bool last = 0, now = 1;

	for (int i = 1; i <= n; ++i) {
		int x;
		std::cin >> x;
		LL inv = qpow(x, p - 2);
		f[now].fill(0);

		for (int j = 1; j <= std::min(x, 10); ++j) {
			for (LL k = 0; k <= mask; ++k) {
				LL trans = (((k << j) | k) & mask);
				(f[now][trans] += f[last][k] * inv) %= p;
			}
		}
		for (LL k = 0; k <= mask; ++k) {
			(f[now][k] += f[last][k] * inv % p * std::max(x - 10, 0)) %= p;
		}

		std::swap(now, last);
	}

	LL ans = 0;
	for (int i = 0; i < (1 << 10); ++i) {
		(ans += f[last][i | (1 << 10)]) %= p;
	}

	std::cout << ans << '\n';
	return 0;
}

```


---

## 作者：shinkuu (赞：4)

打过最漂亮的一场 ABC，写个 F 题解纪念一下。

考虑概率 dp，容易发现，“选若干个数，和为 $10$”这样的表述就很像背包。但是要考虑到一个问题：如果一种方案有两种及以上的方式凑出 $10$，他们对答案是没有贡献的。所以不能常规地线性 dp。

观察题目，发现如果选到 $10$ 以上的数对答案是不可能有贡献的。那么我们就可以直接状压，第 $i$ 位为 $1$ 表示当前已经可以凑出 $i+1$。所以，我们可以设计一个状态：$dp_{i,S}$ 表示只考虑前 $i$ 个数，能凑出的集合为 $S$ 的概率。

转移的时候，枚举当前位置变成的数 $j$。如果 $j\leq 10$，则加入 $j$ 后，$S$ 会变成 $S|(1<<(j-1))|((k<< j)\&(2^{10}-1))$。否则 $S$ 没有变化，所有 $j$ 的贡献可以一起算。

然后快乐转移。

统计答案的时候枚举所有能凑出 $10$，即第 $9$ 位为 $1$ 的集合统计即可。

时间复杂度 $\Theta(2^{10}\times 10n)$，相当优秀。但是懒得预处理逆元了，所以下面实现还多了个 $\log V$，$V$ 为值域。

然后 15min 切 ABC F 了。

code：

```cpp
int n,m,e[N],dp[N][M];
inline int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
void solve(){
	scanf("%d",&n);
	dp[0][0]=1;
	const int mx=1<<10;
	for(int i=1;i<=n;i++){
		scanf("%d",&e[i]);
		for(int j=1;j<=min(e[i],10);j++){
			for(int k=0;k<mx;k++){
				int val=k|(1<<(j-1))|((k<<j)&(mx-1));
				dp[i][val]=(dp[i][val]+1ll*dp[i-1][k]*qpow(e[i],mod-2)%mod)%mod;
			}
		}
		if(e[i]>10){
			for(int j=0;j<mx;j++)
				dp[i][j]=(dp[i][j]+1ll*(e[i]-10)*qpow(e[i],mod-2)%mod*dp[i-1][j]%mod)%mod;
		}
	}
	int ans=0;
	for(int i=0;i<mx;i++){
		if(i&(1<<9))
			ans=(ans+dp[n][i])%mod;
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

话说这场写最久的竟然是 D。

---

## 作者：Judgelight (赞：3)

赛时切，挺好的。

# 题意

给你 $n$ 个数，每个数 $A_i$ 表示第 $i$ 次从 $1\sim A_i$ 中等概率抽取一个数，问最后的这 $n$ 个数能选出一些加起来为 10 的概率。

# 题解

概率转为方案数除总方案数。发现 10 特别小，然后再想一想其实只有 $1\sim \min(A_i,10)$ 是有用的。所以设 $f_{i,S}$ 表示取了前 $i$ 轮，能选出数加和得到的关于值域 $[1,10]$ 的情况为 $S$ 的方案数。其中若能得到 $i$ 则 $S$ 的二进制表示中 $2^{i}$ 为 1。注意如果 $A_i>10$ 则只计算 $[1,10]$，然后相当于有 $A_i-10$ 种情况为选了没选，则 $f_{i,S}+=(A_i-1)f_{i-1,S}$。

时间复杂度为 $O(2^{v}vn)$，$v$ 是值域，在这里是 10。

# 代码

```cpp
#include<bits/stdc++.h>
#define N 109
#define K 100009
#define int long long
using namespace std;
const int mod=998244353;
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int n,f[N][K],mul=1;
signed main(){
	cin>>n;
	f[0][1]=1;
	for(int i=1;i<=n;i++){
		int sum;
		cin>>sum;
		mul*=sum,mul%=mod;
		for(int p=(1<<11)-1;p>=1;p--){
			if(!(p&1))continue;
			for(int x=1;x<=min(sum,10ll);x++){
				int q=((p<<x)|p)&((1<<11)-1);
				f[i][q]+=f[i-1][p];
				if(f[i][q]>=mod)f[i][q]-=mod;
			}
		}
		if(sum>10){
			for(int p=(1<<11)-1;p>=1;p--){
				f[i][p]+=f[i-1][p]*(sum-10)%mod;
				if(f[i][p]>=mod)f[i][p]-=mod;
			}
		}
	}
	int ans=0;
	for(int i=0;i<(1<<11);i++){
		if(i&(1<<10)){
			ans+=f[n][i];
		}
		if(ans>=mod)ans-=mod;
	}
	cout<<ans*ksm(mul,mod-2)%mod;
	return 0;
}
```

---

## 作者：ケロシ (赞：1)

# 题意
有 $n$ 个骰子，第 $i$ 个骰子能等概率投掷 $1$ 到 $a_i$ 的数。   
现在随机投掷骰子，求投出的骰子能选出一些骰子，它们和为 $10$ 的概率。  
$1 \le n\le100$。
# 解题思路
首先想到状压 dp 解决此题。  
设置状态 $f_{i,j}$ 其中 $j$ 为二进制状压表示可以选到和的状态，总体表示前 $i$ 个骰子在 $j$ 状态的概率。  
随后考虑转移，每个骰子投出一个数的概率为 $\frac{1}{a_i}$，那么枚举筛子投掷出的数，随后像背包一样转移能选到和的状态。   
最后在能投出 $10$ 的状态里求和即可。
# 代码
这里放核心代码，完整代码在[这里](https://atcoder.jp/contests/abc310/submissions/43657899)。
```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    REP(i, n) cin >> a[i];
    vector<mint> f(1 << 10);
    f[0] = 1;    
    REP(i, n) {
        vector<mint> g(1 << 10);
        mint val = mint(1) / a[i];
        int m = min(a[i], 10);
        REP(j, 1 << 10) {
            FOR(k, 1, m) {
                g[(j | j << k | 1 << (k - 1)) & ((1 << 10) - 1)] += f[j] * val;
            }
            g[j] += f[j] * (a[i] - m) * val;
        }
        f = g;
    }
    mint ans = 0;
    FOR(i, 1 << 9, (1 << 10) - 1) {
        ans += f[i];
    }
    cout << ans << endl;
}
```

---

## 作者：D2T1 (赞：1)

$n$ 比较小，考虑 dp。

设 $f_{i,p}$ 表示考虑到第 $i$ 个数，$[0,10]$ 的数是否可以通过若干数之和得到的状态 $p$。

考虑转移：

- 首先是随机到 $[1,10]$ 的数，这样的数会对状态 $p$ 产生贡献，出现概率为 $\dfrac 1{a_i}$。

$$f_{i-1,k}\to f_{i,k|((k<<j)\&(2^{11}-1)}$$

- 再是随机到除了 $[1,10]$ 以外的数，根据 $a_i$ 与 $10$ 的大小分讨求得出现次数 $x$，概率为 $\dfrac x{a_i}$，这样的数不会对状态 $p$ 产生贡献。

$$f_{i-1,k}\to f_{i,k}$$

```cpp
//AT_abc310_f
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 110;
int n, a[N];
ll f[N][4097];
const ll P = 998244353;

ll qp(ll a, ll b){
	ll ans = 1;
	while(b){
		if(b&1){
			ans = ans * a % P; 
		}
		a = a * a % P;
		b >>= 1;
	}
	return ans;
}

void solve(){
	scanf("%d", &n);
	f[0][1] = 1;
	for(int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
		for(int j = 1; j <= min(a[i], 10); ++ j){
			for(int k = 0; k < (1 << 11); ++ k){
				(f[i][k|((k<<j)&((1<<11)-1))] += f[i-1][k] * qp(a[i], P-2) % P) %= P;
			}
		}
		int p = (a[i] <= 10) ? 0 : a[i] - 10;
		ll pp = qp(a[i], P-2) * p % P;
		for(int k = 0; k < (1 << 11); ++ k){
			(f[i][k] += f[i-1][k] * pp) %= P;
		}
	}
	ll ans = 0;
	for(int k = 0; k < (1 << 11); ++ k){
		if((k >> 10) & 1){
			(ans += f[n][k]) %= P;
		}
	}
	printf("%lld\n", ans);
}

int main(){
	solve();
	return 0;
}
```

---

## 作者：解方橙 (赞：0)

来一个极为暴力的做法。

首先注意到大于 $10$ 的数都没用。于是

设 $dp_{i,a_1,a_2,a_3,a_4,a_5,a_6,a_7,a_8,a_9,a_{10}}$ 表示到第 $i$ 个数，$1$ 有 $a_1$ 个，$2$ 有 $a_2$ 个，……，$10$ 有 $a_{10}$ 个的概率。由于我们要凑 $10$ ，因此对我们有用的状态满足 $a_1\leq 10,a_2\leq 5,a_3 \leq 3,a_4,a_5\leq 2,a_6,a_7,a_8,a_9,a_{10}\leq 1$ ，因此时间和空间都绰绰有余。对于每次扔骰子操作，直接暴力枚举扔出来的哪个数（如果扔出来的数 $\ge 11$ 可以一起计算），转移即可。最后直接枚举所有状态暴力 $\operatorname{check}$ 更新答案。时间复杂度 $\mathcal{O}(n)$ ，常数在 $8\times 10^5$ 左右，在 AT 的少爷姬上绰绰有余。

高能代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=110;
const int mod=998244353;
int qpow(int x,int b){
    int res=1;
    while(b){
        if(b&1) res=res*x%mod;
        x=x*x%mod;
        b>>=1;
    }
    return res;
}
int n,a[N];
int inv(int x){return qpow(x,mod-2);}
void to(int& x,int y){x=(x+y)%mod;}
int dp[N][11][6][4][3][3][2][2][2][2][2];
bool check(int _1,int _2,int _3,int _4,int _5,int _6,int _7,int _8,int _9,int _0){
    return _0||(_9&&_1)||(_8&&(_2||_1>=2))||(_7&&(_3||_2&&_1||_1>=3))||(_6&&(_4||_3&&_1||_2>=2||_2&&_1>=2||_1>=4))
    ||(_5&&(_5>=2||_4&&_1||_3&&_2||_3&&_1>=2||_2>=2&&_1||_2&&_1>=3||_1>=5))||(_4&&(_4>=2&&_2||_4>=2&&_1>=2||_3>=2||_3&&_2&&_1
    ||_3&&_1>=3||_2>=3||_2>=2&&_1>=2||_2&&_1>=4||_1>=6))||(_3&&(_3>=3&&_1||_3>=2&&_2>=2||_3>=2&&_2&&_1>=2||_3>=2&&
    _1>=4||_2>=3&&_1||_2>=2&&_1>=3||_2&&_1>=5||_1>=7))||(_2&&(_2>=5||_2>=4&&_1>=2||_2>=3&&_1>=4||_2>=2&&_1>=6||_1>=8))
    ||_1>=10;
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    dp[0][0][0][0][0][0][0][0][0][0][0]=1;
    for(int i=0;i<n;i++){
      for(int _1=0;_1<=10;_1++){
        for(int _2=0;_2<=5;_2++){
          for(int _3=0;_3<=3;_3++){
            for(int _4=0;_4<=2;_4++){
              for(int _5=0;_5<=2;_5++){
                for(int _6=0;_6<=1;_6++){
                  for(int _7=0;_7<=1;_7++){
                    for(int _8=0;_8<=1;_8++){
                      for(int _9=0;_9<=1;_9++){
                        for(int _0=0;_0<=1;_0++){
                          int cur=dp[i][_1][_2][_3][_4][_5][_6][_7][_8][_9][_0];
                          int invi=inv(a[i+1]);
                          if(a[i+1]>=11) to(dp[i+1][_1][_2][_3][_4][_5][_6][_7][_8][_9][_0],cur*invi%mod*(a[i+1]-10)%mod);
                          if(a[i+1]>=1) to(dp[i+1][min(_1+1,10ll)][_2][_3][_4][_5][_6][_7][_8][_9][_0],cur*invi%mod);
                          if(a[i+1]>=2) to(dp[i+1][_1][min(_2+1,5ll)][_3][_4][_5][_6][_7][_8][_9][_0],cur*invi%mod);
                          if(a[i+1]>=3) to(dp[i+1][_1][_2][min(_3+1,3ll)][_4][_5][_6][_7][_8][_9][_0],cur*invi%mod);
                          if(a[i+1]>=4) to(dp[i+1][_1][_2][_3][min(_4+1,2ll)][_5][_6][_7][_8][_9][_0],cur*invi%mod);
                          if(a[i+1]>=5) to(dp[i+1][_1][_2][_3][_4][min(_5+1,2ll)][_6][_7][_8][_9][_0],cur*invi%mod);
                          if(a[i+1]>=6) to(dp[i+1][_1][_2][_3][_4][_5][min(_6+1,1ll)][_7][_8][_9][_0],cur*invi%mod);
                          if(a[i+1]>=7) to(dp[i+1][_1][_2][_3][_4][_5][_6][min(_7+1,1ll)][_8][_9][_0],cur*invi%mod);
                          if(a[i+1]>=8) to(dp[i+1][_1][_2][_3][_4][_5][_6][_7][min(_8+1,1ll)][_9][_0],cur*invi%mod);
                          if(a[i+1]>=9) to(dp[i+1][_1][_2][_3][_4][_5][_6][_7][_8][min(_9+1,1ll)][_0],cur*invi%mod);
                          if(a[i+1]>=10) to(dp[i+1][_1][_2][_3][_4][_5][_6][_7][_8][_9][min(_0+1,1ll)],cur*invi%mod);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    int ans=0;
      for(int _1=0;_1<=10;_1++){
        for(int _2=0;_2<=5;_2++){
          for(int _3=0;_3<=3;_3++){
            for(int _4=0;_4<=2;_4++){
              for(int _5=0;_5<=2;_5++){
                for(int _6=0;_6<=1;_6++){
                  for(int _7=0;_7<=1;_7++){
                    for(int _8=0;_8<=1;_8++){
                      for(int _9=0;_9<=1;_9++){
                        for(int _0=0;_0<=1;_0++){
                          int cur=dp[n][_1][_2][_3][_4][_5][_6][_7][_8][_9][_0];
                          if(check(_1,_2,_3,_4,_5,_6,_7,_8,_9,_0)) //cerr<<"! "<<_1<<" "<<_2<<" "<<_3<<" "<<_4<<" "<<_5<<" "<<_6<<" "<<_7<<" "<<_8<<" "<<_9<<" "<<_0<<" "<<cur<<endl,
                          to(ans,cur);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    printf("%lld\n",ans);
}

```

---

## 作者：DengDuck (赞：0)

今天模拟赛的题打过，就这道之前没做，切了之后发现非常有意思啊！

于是写个题解。


首先转换一下，概率什么的真是太愚蠢了，直接转换成可行方案数 $cnt$ 除于总方案数 $prd$。

显然：
$$
prd=\prod_{i=1}^N A_i\pmod{998244353}
$$
接下来考虑求 $cnt$。

显然要 DP，考虑到我们的状态转移类似于背包，需要保存是否可以选出 $i\in[1,10]$，所以可以状压，后面的状态其实没用，我们最后只关心选出 $10$。

我们设 $f_{i,j}$ 表示前 $i$ 个骰子的结果可以拼出的数字集合 为$j$ 的方案数，考虑转移,这里用我为人人的刷表法思想比较简单。

我们设当前骰子投出的是 $t\in[1,A_i]$，则新的集合可以利用位运算快速算出，其实就是一个背包转移的思想，看我代码，不多赘述，设新集合为 $k$。 
$$
f_{i-1,j}\to f_{i,k}
$$
我们注意到对于 $t>10$ 的情况其实新集合 $k$ 就是原来的集合 $j$，因为你只保存了 $[1,10]$，而你大于了 $10$ 新的可以选出的值都是大于 $10$ 的。

所以对于 $t>10$ 的情况，值的贡献都是一样的，可以直接全部算出。

时间复杂度由此降至 $O(2^{T}N)$，其中 $T$ 为状态要保存的位数，或者说保存的最大集合的大小，为 $10$。

## 代码实现

``` cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL mod=998244353;
const LL N=105;
const LL M=(1<<11);
LL n,a[N],f[N][M+5],prd=1,ans;
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		prd=prd*a[i]%mod;
	}
	f[0][1]=1;
	for(int i=1;i<=n;i++)
	{
		for(LL k=0;k<M;k++)
		{
			for(LL j=1;j<=min(a[i],10ll);j++)
			{
				LL t=k|(k<<j);
				t&=(1<<11)-1;
				f[i][t]=(f[i][t]+f[i-1][k])%mod;
			}
			if(a[i]>10)
			{
				f[i][k]=(f[i][k]+f[i-1][k]*(a[i]-10)%mod)%mod;
			}
		}
	}
	for(int k=1<<10;k<M;k++)
	{
		ans=(ans+f[n][k])%mod;
	}
	ans=ans*ksm(prd,mod-2)%mod;
	printf("%lld",ans);
	
}
```



---

## 作者：yemuzhe (赞：0)

### 题目大意

- 有 $N$ 个骰子，每个骰子有 $A _ i$ 面，上面分别是 $1 \sim A _ i$。
- 现在同时掷这些骰子，问可以从中取出若干个骰子使得它们向上的面的数字之和正好为 $10$ 的概率。概率对 $998244353$ 取模。
- $1 \le N \le 100$，$1 \le A _ i \le 10 ^ 6$。

### 解题思路

对于一个骰子的值 $k$（指的是骰子向上的面的数字，下同），如果它大于 $10$ 那么就是没用的。

我们考虑 dp，我们只需记录之前若干骰子的值之和是否能组成 $x$（$0 \le x \le 10$），不用关心大于 $10$ 的 $x$（因为 $k > 0$）。

注意到 $10$ 很小，可以用状压 dp。设 $f _ {i, j}$ 表示用前 $i$ 个骰子能表示出 $j$ 状态的概率。

其中 $j$ 是一个 $11$ 位二进制数，从右往左第 $t$ 位为 $0$ / $1$ 表示不能 / 能用前 $i$ 个骰子中若干个的值之和组成 $t$。

如前 $i$ 个骰子的值分别为 $1, 2, 5$，那么可以组成 $0$、$1$、$2$、$3$、$5$、$6$、$7$、$8$，此时 $j = 00111101111$。

显然初始状态 $f _ {0, 1} = 1$（即只能表示出 $0$），目标状态为 $\max \limits _ {2 ^ {10} \le i < 2 ^ {11}} \{f _ {N, i}\}$（即必须表示出 $10$）。

考虑主动转移，对于 $k \le 10$，$j$ 状态再加入当前骰子的值 $val$ 后状态变成 `j | j << k`，即不选 $val$ 和选 $k$ 的并集，概率为 $1 \over A _ i$。转移方程如下：

$$f _ {i +1, j | j << k} \leftarrow f _ {i, j} \times {1 \over A _ i}$$

对于 $k > 10$，$j$ 状态不受影响，概率为 $A _ i - 10 \over A _ i$，转移方程如下：

$$f _ {i + 1, j} \leftarrow f _ {i, j} \times {A _ i - 10 \over A _ i}$$

时间复杂度为 $O (2 ^ K N K \log P)$，其中 $K = 11$，$P = 998244353$。

### AC Code

```cpp
#include <cstdio>
#define MOD 998244353
#define N 105
#define M 2050
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;

int n, x, ans, f[N][M];

int qpow (long long a, int b) // 快速幂
{
    long long res = 1;
    for (; b; b >>= 1)
    {
        if (b & 1)
        {
            res = res * a % MOD;
        }
        a = a * a % MOD;
    }
    return res;
}

int val (int a, int b) // 分数取模
{
    return (long long) a * qpow (b, MOD - 2) % MOD;
}

void add (int &x, int y)
{
    x = x + y >= MOD ? x + y - MOD : x + y;
    return ;
}

int main ()
{
    scanf ("%d", &n), f[0][1] = 1;
    for (int i = 0; i < n; i ++) // dp
    {
        scanf ("%d", &x);
        for (int j = 1; j < 1 << 11; j ++)
        {
            if (!f[i][j])
            {
                continue;
            }
            for (int k = 1, tmp; k <= min (x, 10); k ++)
            {
                tmp = (long long) f[i][j] * val (1, x) % MOD;
                add (f[i + 1][(j | j << k) & ((1 << 11) - 1)], tmp);
            }
            if (x > 10)
            {
                add (f[i + 1][j], (long long) f[i][j] * val (x - 10, x) % MOD);
            }
        }
    }
    for (int i = 1 << 10; i < 1 << 11; i ++) // 统计答案
    {
        ans = (ans + f[n][i]) % MOD;
    }
    printf ("%d", ans);
    return 0;
}
```

---

## 作者：rainygame (赞：0)

将题目转化为求方案数，设 $f_{i,a_1\sim a_{10}}$，表示在 $A_1\sim A_i$ 中，$1\sim10$ 的出现次数分别为 $a_1\sim a_{10}$ 的方案数，那么转移只需要枚举 $A_i$ 取多少，然后 dfs 即可。

计算答案时只需要 dfs 求出 $10$ 的所有整数拆分（共 $42$ 个），再 dfs 统计所有包含它的状态，注意不要重复计算一个状态的贡献。

设 $k=10\times5\times3\times2\times2$ 表示每次转移的状态数，$g=42$，那么时间复杂度为 $O((n+g)k)$，可以通过。

给一个 hack 数据：

```
3
5 5 5
```

```
782623573
```

注意 $\{5, 5, 5\}$ 也是合法的答案。

[code](https://atcoder.jp/contests/abc310/submissions/57411955)

---

