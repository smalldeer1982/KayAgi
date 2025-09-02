# Chips on a Line

## 题目描述

你有 $n$ 个芯片，并且要将它们放置在 $x$ 个点上，这些点编号为 $1$ 到 $x$ 。每个点可以放置多个芯片。

在放置芯片后，你可以执行以下四种操作（顺序任意，次数不限）：

- 选择在点 $i \geq 3$ 的一个芯片，将其移除，并在 $i - 1$ 和 $i - 2$ 各放置一个芯片；
- 选择在相邻点 $i$ 和 $i + 1$ 的两个芯片，将它们移除，并在 $i + 2$ 放置一个新芯片；
- 选择在点 $1$ 的一个芯片，并将其移到点 $2$；
- 选择在点 $2$ 的一个芯片，并将其移到点 $1$。

注意，放置操作中芯片的位置不能小于 $1$，但可以大于 $x$ 。

定义芯片放置的成本为：经过以上操作后剩余的最少芯片数。

例如，将两个芯片放在点 $3$ 和一个芯片放在点 $5$ 的成本为 $2$，因为可以通过以下步骤将芯片数减少到 $2$：

- 选择点 $3$ 的一个芯片，移除它，并在点 $1$ 和点 $2$ 各放置一个芯片；
- 选择点 $2$ 和点 $3$ 的芯片，移除它们，并在点 $4$ 放置一个芯片；
- 选择点 $4$ 和点 $5$ 的芯片，移除它们，并在点 $6$ 放置一个芯片。

给定三个整数 $n$、$x$ 和 $m$，计算在点 $1$ 到 $x$ 放置恰好 $n$ 个芯片且成本等于 $m$ 的放置方案数，并输出其模 $998244353$ 的结果。如果两个放置方案在某点的芯片数不同，则认为它们是不同的放置方案。

## 样例 #1

### 输入

```
2 3 1```

### 输出

```
5```

## 样例 #2

### 输入

```
42 10 5```

### 输出

```
902673363```

## 样例 #3

### 输入

```
1000 10 8```

### 输出

```
187821763```

# 题解

## 作者：wrkwrkwrk (赞：12)

观察发现如下事实：
- 所有操作可逆。
- 可以将所有棋子全部变成若干个 $1$ 号棋子。

因此，所有棋子的花费与提供都是若干个 $1$ 号棋子。由操作性质和积累可知，棋子 $i$ 花费为斐波那契数 $f_i$。

由于 $f_{10}=55$，至多 $55000$ 个 $1$ 号棋子，查表或打表可知用到的位置不会超过 $24$。

预处理出用 $0\sim 55000$ 个 $1$ 号棋子可以得到的最少棋子个数。

之后统计出恰好 $i$ 个棋子的方案数目，具体的，定义 $dp_{i,j,k}$ 表示到第 $i$ 个位置为止，用了 $j$ 个棋子，产生 $k$ 个 $1$ 号棋子的方案数。可以优化掉 $i$ 这一维度，之后直接转移得到结果。

最后根据 $1$ 号棋子个数是否满足条件直接累加即可。

预处理运算量为 $24 \times 55000$，剩下的复杂度为 $\Theta(xn^2)$

为了节省篇幅，代码中 mint 表示取模整数。完整代码在[这里](https://codeforces.com/contest/1997/submission/273644507)。
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace _wrk{;
#define int long long
#define mod 998244353
#define mint modint<mod>
Math<mint,1000006>math;
int a[2323];
int n,m,x;
int c[60000];
mint p[1003][60003];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	a[1]=a[2]=1;
	for(int i=3;i<=24;i++){
		a[i]=a[i-1]+a[i-2];
	}
	memset(c,0x3f,sizeof(c));
	c[0]=0;
	for(int k=1;k<=24;k++){
		for(int i=a[k];i<=a[10]*1000;i++){
			c[i]=min(c[i],c[i-a[k]]+1);
		}
	}
	int n,m,x;
	cin>>n>>x>>m;
	p[0][0]=1;
	for(int i=1;i<=x;i++){
		for(int f=1;f<=n;f++){
			for(int j=a[i];j<=55*n;j++){
				p[f][j]+=p[f-1][j-a[i]];
			}
		}
	}
	mint ans=0;
	for(int i=1;i<=a[10]*1000;i++){
		if(c[i]==m)ans+=p[n][i];
	}
	cout<<ans;

	return 0;
}
}
signed main(){
	   return _wrk::main();
}




```

---

## 作者：Iniaugoty (赞：2)

### [CF1997F	Chips on a Line](https://www.luogu.com.cn/problem/CF1997F)

好题！

很难不发现，前两个和后两个操作是分别互逆的，也就是现在进行的操作可以在将来被撤销掉。

同时不难发现，所有物品都能经过某种操作放到 $1$ 上（证明归纳即可）。

设 $i$ 上的一个物品经过操作会变成 $1$ 上的 $f _ i$ 个物品。显然 $f _ 1 = f _ 2 = 1$。由于 1 操作是将 $i$ 上的物品放到 $i - 1$ 和 $i - 2$ 上，故 $f _ i = f _ {i - 1} + f _ {i - 2}$。这是一个斐波那契数列（不过似乎把它换成别的数列这题照样可做）。

再设 $g _ i$ 表示转化到 $1$ 上有 $i$ 个物品的“成本”。容易发现，最终结果，一个位置上最多只有一个物品（证明考虑调整法）。那么可以用一个 01 背包求出 $g$。$i$ 的上界为 $\max \{ n f _ x \} = 5.5 \times 10 ^ 4$，打表发现只用枚举到 $f _ {24}$。

这一部分运算量约为 $1320000$。

再设 $h _ {i, j, k}$ 表示初始用了 $k$ 个物品，物品最大放在 $i$，转化到 $1$ 上有 $j$ 个物品的方案数。可以做一个类似完全背包进行转移，同时 $i$ 这一维可以优化掉。

这一部分时间复杂度 $O (n ^ 2 f _ x x)$。

答案为 $\sum _ {i = 0} ^ {n f _ x} h _ {x, i, n} [g _ i = m]$。

[code](https://codeforces.com/contest/1997/submission/273972822)。

---

## 作者：红黑树 (赞：2)

[可能更好的阅读体验](https://rbtr.ee/CF1997F)

## [题目](https://codeforces.com/contest/1997/problem/F)

## 题解
定义 $N$ 的 Fibonacci 表示 $a_i$：

$$N = \sum a_if_i$$

其中 $f_i$ 为 Fibonacci 数，$f_1 = f_2 = 1$。注意 Fibonacci 表示可能不唯一。

有两个性质：所有操作可撤销 和 所有操作不改变 Fibonacci 表示下的和（$\sum a_if_i$）。

首先想想一个放置方案的 cost 是多少。找到 $\sum a_i$ 最小的 Fibonacci 表示，cost 就是 $\sum a_i$。这个表示显然可以从大到小枚举 Fibonacci 数贪心求解，且是唯一的。这个最小表示名为 Zeckendorf 表示。

那现在知道 cost 怎么算之后，我们可以判定出哪些数是需要统计进答案的了。

对于一个数来说，我们想计算有多少种不同的 Fibonacci 表示。设 $f_{i, j, k}$ 表示如果只用前 $i$ 个位，$\sum a_i = j$ 且 $\sum a_if_i = k$ 的方案数。

然后空间会卡，把第一维滚掉。

时间复杂度 $O\left(x \cdot n^2 \cdot f_x\right)$。

## 代码
```cpp
/* C++17 is required!
 * By Koicy (https://koicy.ly)
 * Email n@rbtr.ee
 * I've reached the end of my fantasy.

         __    __                             __         _
   _____/ /_  / /_________  ___              / /______  (_)______  __
  / ___/ __ \/ __/ ___/ _ \/ _ \   ______   / //_/ __ \/ / ___/ / / /
 / /  / /_/ / /_/ /  /  __/  __/  /_____/  / ,< / /_/ / / /__/ /_/ /
/_/  /_.___/\__/_/   \___/\___/           /_/|_|\____/_/\___/\__, /
                               SIGN                         /___*/
#ifndef XCODE
constexpr bool _CONSOLE = false;
#else
constexpr bool _CONSOLE = true;
#endif
#define __NO_MAIN__ false
#define __ENABLE_RBLIB__ true
constexpr bool _MTS = false, SPC_MTS = false;
constexpr char EFILE[] = "";
#define FULL(arg) arg.begin(), arg.end()

// :/

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  constexpr tp mod = 998244353;
  tp n, x, m; bin >> n >> x >> m;
  vetp fib { 0, 1, 1 };
  for (tp i = 3; i <= 100; ++i) fib.push_back(fib[i - 1] + fib[i - 2]);
  auto Zeckendorf = [&](tp n) -> tp {
    tp ret = 0;
    for (tp i = 100; i >= 1; --i) {
      ret += n / fib[i];
      n %= fib[i];
    }
    return ret;
  };
  vector<vetp> f(n + 1, vetp(fib[x] * n + 1));
  f[0][0] = 1;
  auto mad = [](tp a, tp b) { return a + b >= mod ? a + b - mod : a + b; };
  for (tp i = 1; i <= x; ++i) {
    for (tp j = 1; j <= n; ++j) {
      for (tp k = fib[i]; k < f[j].size(); ++k) {
        f[j][k] = mad(f[j][k], f[j - 1][k - fib[i]]);
      }
    }
  }
  tp tar = 0;
  for (tp j = 1; j < f[n].size(); ++j) {
    if (Zeckendorf(j) == m) tar = mad(tar, f[n][j]);
  }
  bin << tar << '\n';
  return 0;
}

void MIST() {
}

// :\ */
```

---

## 作者：DerrickLo (赞：1)

考虑给每个位置赋一个权值 $f_i$，使得两个状态 $\{a_1,\ldots a_n\}$ 和 $\{b_1,\ldots b_n\}$ 可以转化当且仅当 $\displaystyle\sum_{i=1}^{n}a_if_i=\sum_{i=1}^{n}b_if_i$。我们看看这个权值要满足什么条件：

- $f_i=f_{i-1}+f_{i-2}$
- $f_1=f_2$

不难发现 $f_i=Fib_i$ 就是满足条件的。然后我们就可以直接 dp，记 $g_{i,j}$ 表示选了 $i$ 个数，和为 $j$ 的方案数。转移是简单的，若记 $F(x)$ 表示 $x$ 分解成最少个斐波那契数的和的个数，那么答案就是 $\displaystyle\sum_{i=1}^{nf_x}[F(i)=m]g_{n,i}$，预处理 $F(i)$ 即可。

时间复杂度 $\mathcal O(n^2xf_x)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int n,x,m,f[35],g[1005][55005],a[55005],ans;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>x>>m,f[1]=f[2]=1;
	for(int i=3;i<=25;i++)f[i]=f[i-1]+f[i-2]; g[0][0]=1;
	for(int i=1;i<=x;i++){
		for(int j=1;j<=n;j++){
			for(int k=f[i];k<=j*f[x];k++){
				(g[j][k]+=g[j-1][k-f[i]])%=mod;
			}
		}
	}
	for(int i=1;i<=n*f[x];i++){
		int now=i;
		for(int j=25;j;j--)if(now>=f[j])now-=f[j],a[i]++;
	}
	for(int i=1;i<=n*f[x];i++)if(a[i]==m)(ans+=g[n][i])%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

板子题。

观察到操作可逆，于是可以全都转化成 $1$，再转化回来。发现这实际上就代表一个状态的权值为所有对应位置的斐波那契数列对应项之和，而最少 chip 个数实际上就是最少用几个斐波那契数凑出这个和。

于是直接背包 DP 即可，时间复杂度 $\mathcal O(fib_XXn^2)$。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline","unroll-loops")
#include<bits/stdc++.h>
typedef int ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll Mod=998244353;
ll n,m,X,dp[1009][55009],w[55009],f[35];
void Upd(ll&x,ll y){
    x+=y;
    if(x>=Mod)x-=Mod;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),X=read(),m=read();
    f[1]=f[2]=1;
    rep(i,3,30)f[i]=f[i-2]+f[i-1];
    rep(i,1,55000){
        w[i]=i;
        rep(j,1,30){
            if(i>=f[j])w[i]=min(w[i],w[i-f[j]]+1);
            else break;
        }
    }
    dp[0][0]=1;
    rep(i,1,X){
        rep(j,1,n){
            rep(k,max(j,f[i]),f[i]*n)Upd(dp[j][k],dp[j-1][k-f[i]]);
        }
    }
    ll ans=0;
    rep(j,n,f[X]*n){
        if(w[j]==m)Upd(ans,dp[n][j]);
    }
    write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：gyyyyx (赞：1)

容易发现所有位置筹码都能通过操作一到达点 $1,2$，而点 $2$ 的筹码又能通过操作四到达点 $1$。

而点 $1$ 上的筹码又能通过操作二、三到达任意点。

设一个点 $i$ 上的筹码到达点 $1$ 后的筹码数量会变成 $f_i$，则根据操作一可得 $f_i=f_{i-1}+f_{i-2}$。

因此 $f$ 为斐波那契数列。

我们可以通过 dp 求出点 $1$ 上筹码数量为 $i$ 时的直线上的筹码最小值，记为 $g_i$。

点 $1$ 上最多有 $nf_x$ 个筹码，也就是最多 $55000$ 个，查一下斐波那契数列表可知最多只能放到点 $24$。

设每个点上的筹码数量为 $c_i$，可列出不定方程：$\sum c_i=n,\sum f_ic_i=t$ 其中 $t$ 满足 $g_t=m$。

再次通过 dp 求出满足条件的 $c$ 的数量，记为 $k_t$。

$t$ 的范围是 $n\sim nf_x$，直接枚举 $t$，答案累加上满足 $g_t=m$，发 $k_t$ 即可。

时间复杂度 $O(n^2xf_n)$，瓶颈在求 $k_t$。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define mod 998244353
using namespace std;
int n,m,x,f[25],g[55005];
LL k[1005][55005];
LL ans;
int main(){
	scanf("%d%d%d",&n,&x,&m);
	f[1]=f[2]=1;for(int i(3);i<=24;++i) f[i]=f[i-1]+f[i-2];
	memset(g,0x3f3f3f3f,sizeof(g));g[0]=0;
	for(int i(1);i<=24;++i)
		for(int j(f[i]);j<=f[x]*n;++j)
			g[j]=min(g[j],g[j-f[i]]+1);
	k[0][0]=1;
	for(int t(1);t<=x;++t)
		for(int i(1);i<=n;++i)
			for(int j(f[t]);j<=f[x]*n;++j)
				(k[i][j]+=k[i-1][j-f[t]])%=mod;
	for(int t(n);t<=f[x]*n;++t)
		if(g[t]==m) (ans+=k[n][t])%=mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

我们发现这个筹码总数变来变去的很难搞。

考虑给不同位置上的筹码加上不同的权值使得筹码总权值之和不变，不难发现权值需要满足 $F_{i-1} + F_{i-2} = F_i$，且 $F_1 = F_2$，我们发现这就是斐波那契数列，然后我们发现对于所有权值之和相同的摆放筹码情况一定可以通过操作得到。

由于初始状态总权值之和至多是 $\text{Fib}_x \times n = 5.5 \times 10^4$，所以我们考虑以权值之和做两次背包，第一次算每种权值被凑出来的最小代价，第二次算每种权值被凑出来的方案数，注意到第二个背包是一个多重背包，但是没有取物品的数量限制，直接记录余数优化即可做到 $O(x \times \text{Fib}_x \times n^2)$。

[代码](https://codeforces.com/contest/1997/submission/273653674)

其实不需要余数优化，没有限制的话从前往后更新，允许一个状态被多次更新即可。

---

## 作者：MhxMa (赞：1)

### 题意
有 $n$ 个筹码，需要将它们放置在从 $1$ 到 $x$ 的点上，可以进行四种操作来减少筹码的数量，目标是找到一种放置方式，使得通过一系列操作后，筹码的数量最少。需要计算出所有满足特定成本 $m$ 的放置方式的数量。

### 分析
考虑 $dp$ 和组合数学。

### 思路
我们需要了解如何通过一系列操作将筹码数量减少到最小。那么可以构建一个数组用来维护 $1 \sim x$ 的斐波那契数列的子序列，因为每次操作都可以看作是将筹码从更远的点移动到更近的点。

用一个二维 $dp$ 数组，```dp[j][i]``` 用来维护有 $j$ 个筹码，成本为 $i$ 的放置方式的数量。则可得动态规划表达式：```dp[j][k] += dp[j - 1][k - weight[i]]```。

将所有满足成本为 $m$ 的放置方式的数量加起来输出即可。


### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
int n, x, m;
int ans;
vector<int> weight = {1, 1}; // 该数组包含从 1 到 x 的斐波那契数列的子序列
vector<int> fibs = {1, 1};

int main() {
	scanf("%d%d%d", &n, &x, &m);

	while (weight.size() < x) {
		int l = weight.size();
		weight.emplace_back(weight[l - 1] + weight[l - 2]);
	}

	int up = weight.back() * n;
	while (fibs.back() <= up) {
		int l = fibs.size();
		fibs.emplace_back(fibs[l - 1] + fibs[l - 2]);
	}

    vector<int> cost(up + 1, 0); // 用于记录每个筹码数量对应的成本
	for (int i = 1; i <= up; i++) {
		for (int j = fibs.size() - 1; j >= 0; j--) {
			if (i >= fibs[j]) {
				cost[i] = cost[i - fibs[j]] + 1;
				break;
			}
		}
	}

	vector<vector<int>> dp(n + 1, vector<int>(up + 1));


	dp[0][0] = 1;	// 0筹码的情况
	for (int i = weight.size() - 1; i >= 0; i--) {
		for (int j = 1; j <= n; j++) {
			for (int k = weight[i]; k <= up; k++) {
				dp[j][k] += dp[j - 1][k - weight[i]];
				// dp[j][k] 用来维护有 j 个筹码，成本为 k 的放置方式的数量。
				dp[j][k] %= mod;
			}
		}
	}

	// 遍历cost数组，累加所有成本等于 m 的放置方式数量
	for (int i = 0; i <= up; i++) {
		if (cost[i] == m) {
			ans += dp[n][i];
			if (ans >= mod) {
				ans -= mod;
			}
		}
	}

	cout << ans;
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

提供一个不需要 [Zeckendorf's Theorem](https://proofwiki.org/wiki/Zeckendorf%27s_Theorem) 的做法。

## 简要题意

有一个游戏在数轴的区间 $[1,\infty)$ 上进行，每个整点上可能有一些筹码。你可以进行以下操作任意次：

- 选定一个 $i\in[1,\infty)$，移去 $i+1,i+2$ 两点上各一个筹码，然后在点 $i$ 放置一个筹码。
- 选定一个 $i\in[1,\infty)$，移去点 $i$ 上的各一个筹码，然后在点 $i+1,i+2$ 上各放置一个筹码。
- 将点 $1$ 上的一个筹码移动至点 $2$。
- 将点 $2$ 上的一个筹码移动至点 $1$。

你的得分是最终区间 $[1,\infty)$ 上的筹码总数。

现在总共有 $n$ 个筹码，你需要将其任意分配给 $[1,x]$ 中的任意个整点，使得你的得分最小值恰好为 $m$，求方案数，答案对 $998,244,353$ 取模。

$1\leq m\leq n\leq 10^3,2\leq x\leq 10$。

## 思路

看到题目后，可以发现两个事实：

- 操作是可逆的。
- 经过任意次操作，可以将所有筹码移动到点 $1$。

所以我们可以想到先将所有筹码移动到点 $1$，假设此时点 $1$ 上有 $a$ 个筹码。然后还原到某一个筹码数最少的状态，要求这个状态可以通过操作，使得所有的 $a$ 个筹码均在点 $1$。

因此，我们需要解决两个子问题：

1. 对于一个状态，将所有筹码移动到点 $1$ 后，点 $1$ 上有多少个筹码。
2. 可以通过操作，使得所有的 $a$ 个筹码均在点 $1$ 的状态中，筹码最少的状态是什么。

对于第一个问题，我们发现每个筹码是独立的，不妨设 $f(i)$ 表示位于点 $i$ 的筹码移动到点 $1$ 后变为多少个筹码。容易列出转移方程 $f(i)=f(i-1)+f(i-2)$，边界 $f(1)=f(2)=1$。这个 $f(n)$ 其实就是 Fibonacci 数列。于是假设所有筹码分别位于点 $a_1,a_2,\cdots,a_n$，则操作后点 $1$ 就有 $f(a_1)+f(a_2)+\cdots+f(a_n)$ 个筹码。

对于第二个问题，我们可以 dp，设 $\mathrm{vis}(i,j,k)$ 表示考虑到第 $i$ 个位置，放置了 $j$ 个筹码，当前状态下，将所有筹码移动到点 $1$ 后，点 $1$ 上有 $k$ 筹码，这种状态是否存在。转移就是一个完全背包状物。

至于 $i$ 的上界，由于 $f(25)>10^3\cdot f(10)$，所以取 $i\leq 24$ 即可。时间复杂度 $O(24f^2(n)n)$。

于是筹码数量的最小值就是最小的 $x$ 满足 $\mathrm{vis}(24,x,a)$。

然后考虑解决原问题，设 $f(i,j,k)$ 表示考虑到第 $i$ 个位置，放置了 $j$ 个筹码，当前状态下，将所有筹码移动到点 $1$ 后，点 $1$ 上有 $k$ 筹码的状态数。转移是类似的。，不过此时 $i$ 的上界是 $x$，最后简单统计一下即可。

时间复杂度 $O(24f^2(n)n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

const int N = 1e3 + 5;
int n, x, m, fib[25], cnt[N * 55], f[N][55 * N];
bool vis[N][55 * N];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> x >> m;
    fib[1] = 1;
    for(int i=2;i<=24;i++) fib[i] = Add(fib[i - 1], fib[i - 2]);
    f[0][0] = 1;
    for(int i=1;i<=x;i++){
        for(int j=1;j<=n;j++){
            for(int k=fib[i];k<=fib[x]*n;k++) f[j][k] = Add(f[j][k], f[j - 1][k - fib[i]]);
        }
    }
    vis[0][0] = 1;
    for(int i=1;i<=24;i++){
        for(int j=1;j<=n;j++){
            for(int k=fib[i];k<=fib[x]*n;k++) vis[j][k] |= vis[j - 1][k - fib[i]];
        }
    }
    for(int i=1;i<=fib[x]*n;i++){
        for(int k=1;k<=n;k++){
            if(vis[k][i]){
                cnt[i] = k;
                break;
            }
        }
    }
    int ans = 0;
    for(int i=1;i<=fib[x]*n;i++){
        if(cnt[i] == m) ans = Add(ans, f[n][i]);
    }
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：OI_AKed_me (赞：0)

操作是可逆的。第 $i$ 位放一个等价于第一位放 $f_i$ 个，$f_i$ 表示斐波那契数列第 $i$ 项。

故一种放置方法可表示为 $\sum a_if_i$，$a_i$ 表示第 $i$ 位放置个数。

对于一种表示为 $v$ 的放置方法，其成本为 $\min\{|S|\}$，其中 $v=\sum\limits_{i\in S} f_i$。

背包即可求出每种放置方法的成本。

再进行一次背包，记 $dp_{i,j,k}$ 表示枚举到第 $i$ 为，用了 $j$ 个芯片，表示为 $k$ 的方案数。需要滚掉第一维。

时间复杂度 $O(n^2xf_x)$。[submission](https://codeforces.com/contest/1997/submission/302202322)

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1997F)

**题目大意**

> 给定 $n$ 个棋子放在 $1\sim x$ 上，每次操作可以：
>
> - 把一个 $i+1$ 上的棋子替换成两个分别在 $i,i-1$ 上的棋子，或执行逆操作。
> - 把 $1/2$ 上的棋子移动到 $2/1$ 上。
>
> 求有多少种放棋子的方案使得经过上述操作，能得到的棋子数量最小值是 $m$。
>
> 数据范围：$n,m\le 1000,x\le 10$。

**思路分析**

容易发现最优策略一定是把棋子都放在 $1$ 上再推平。

一个位置 $i$ 上的棋子对应 $Fib_i$ 个 $1$ 上的棋子。

假设最终在 $1$ 上有 $w$ 个棋子，那么得到的最小棋子数量就是 $Fib$ 进制下 $w$ 的 $\mathrm{popcount}$。

因此我们只关心最终 $1$ 上有多少棋子。

$f_{u,i,j}$ 表示考虑位置 $[1,u]$，填了 $i$ 个棋子，对应最终 $1$ 上的 $j$ 个棋子。

统计答案的时候判断 $\mathrm{popcount}(j)=m$ 是否成立。

时间复杂度：$\mathcal O(n^2xFib_x)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1005,MAXV=65005,MOD=998244353;
inline void add(int &x,const int &y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
int f[MAXV][MAXN],fib[50];
int pcnt(int x) {
	int s=0;
	for(int k=30;k>=1;--k) if(x>=fib[k]) x-=fib[k],++s;
	return s;
}
signed main() {
	fib[1]=fib[2]=1;
	for(int i=3;i<=30;++i) fib[i]=fib[i-1]+fib[i-2];
	int n,q,m;
	scanf("%d%d%d",&n,&q,&m);
	int up=n*fib[q];
	f[0][0]=1;
	for(int i=q;i;--i) {
		int z=fib[i];
		for(int j=0;j+z<=up;++j) for(int k=0;k<n&&k*z<=j;++k) {
			add(f[j+z][k+1],f[j][k]);
		}
	}
	int ans=0;
	for(int j=1;j<=up;++j) if(pcnt(j)==m) add(ans,f[j][n]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：phil071128 (赞：0)

好题，将计数和最优化背包结合，同时又考察了找上界的能力。

## CF1997F

> 有 $x\le 10$ 个格子，你总共可以放 $n\le 1000$ 个物品，定义一个放置物品方案的价值为，经过以下四种操作得到的最小物品数量：
>
> - 将 $i,i+1$ 格子上的物品数量减一，$i+2$ 上的物品数量加一。
> - 将 $i,i+1$ 格子上的物品数量加一，$i+2$ 上的物品数量减一。
> - 将格子 $2$ 的物品移动到格子 $1$。
> - 将格子 $1$ 的物品移动到格子 $2$。
>
> 求价值为 $m\le 1000$ 的方案数量。
>
> 注意：初始时只允许 $x$ 个格子放物品，但是操作结束时任意正整数位置的格子都可以放。


显然，操作是可逆的，而且因为有三四操作的存在，使得 $1,2$ 位置的格子尤为特殊。

我们思考如何才能尽可能减少物品数量，我们不能一直进行操作一的原因是，初始情况下 $a_i$ 并不连续，如果任意两个位置都可以交换的话则可以不断除以二。

既然操作可逆，那么我们自然地想到可以先将全部物品移动到位置 $1$ 上，容易发现，一种初始方案对应了唯一一种只在位置 $1$ 有物品的方案。此时整个问题分为两部分：

- 有多少种初始方案，使得将其聚在位置一的个数为 $t$。
- 有多少种只在位置一放 $t$ 个物品的方案，使得将其分开后最小物品数量为 $m$。

问题一是好解决的，我们从右往左不断进行操作 $2$，不难发现 $t=\sum c_i f_i$，其中 $c_i$ 表示初始在 $i$ 位置上物品个数，$f_i$ 表示斐波那契数列。因此相当于解决一个多重背包计数问题：有 $x$ 种物品，第 $i$ 种的重量是 $f_i$，总共可以买 $n$ 个，问填满大小为 $t$ 的背包方案数。

对于问题二，我们正难则反，**考虑有多少最终方案可以最优化中间方案**，即解决一个多重背包最大价值问题：有 $x'$ 种物品，第 $i$ 种的重量是 $f_i$，价值为 $1$，求填满大小为 $t$ 的背包最小价值是多少。

注意到 $x\le 10,f_{10}=55$，因此可以得到 $t$ 的上界为 $55\times 1000$，又由于最终方案可能会向右延伸很远（越往右越优），但 $f_{25}=75\times 1000$，所以 $x'$ 有上界 $f_{25}$。总复杂度为 $O(x\times f_x\times n)$。


```cpp
const int N=1010,V=100*N;
int f[N],g[V],t[N][V];
const int mod=998244353;
int main(){
//	fil();
	int n=read(),x=read(),m=read();
	f[1]=f[2]=1;
	for(int i=3;i<=25;i++) f[i]=f[i-1]+f[i-2];
	memset(g,0x3f,sizeof g);
	g[0]=0;
	for(int i=1;i<=25;i++) {
		for(int j=1;j<=f[25];j++) {
			if(j>=f[i]) g[j]=min(g[j],g[j-f[i]]+1);
		}
	}
	t[0][0]=1;
	for(int i=1;i<=x;i++) {
		for(int j=1;j<=n;j++) {
			for(int k=0;k<=f[25];k++) {
				if(k>=f[i]) t[j][k]=(1ll*t[j][k]+t[j-1][k-f[i]])%mod;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=f[25];i++) {
		if(g[i]==m) {
			ans=(1ll*ans+1ll*t[n][i])%mod;
		}
	}
	cout<<ans<<endl; 
	return 0;
}
```

---

## 作者：yshpdyt (赞：0)

## 题意
初始时总共有 $n$ 个物品要放在格子 $[1,x]$ 当中，你可以进行任意次以下操作：

- 将 $i$，$i+1$ 格子上的物品数量减一，$i+2$ 上的物品数量加一。
- 将 $i$，$i+1$ 格子上的物品数量加一，$i+2$ 上的物品数量减一。
- 将格子 $2$ 的物品移动到格子 $1$。
 
- 将格子 $1$ 的物品移动到格子 $2$。

操作时物品放置位置可以跨过 $x$。

令一个种放置方式的代价为任意次操作后的最小物品数量，求对于给定的 $n,x,m$，初始 $n$ 个物品放在格子 $[1,x]$ 中，代价为 $m$ 的方案数量。

## Sol
注意到操作一二，操作三四互相可逆，这启示我们可以从一个相对简单的初始局面出发，统计其可以经过若干操作变成的合法局面数量。

如果我们每次对最右边的有物品的格子进行操作一，这样所有的物品将会堆积到格子 $1,2$，再通过操作三即可全部堆到格子 $1$。

注意到堆积到格子 $1$ 后物品数量多了很多，考虑记 $f_i$ 表示格子 $i$ 上的 $1$ 个物品，经过操作后变成了格子 $1$ 上的 $f_i$ 个物品，有转移方程：

$$f_i=f_{i-1}+f_{i-2}$$

同时 $f_1=f_2=1$，这其实就是这个斐波那契数列。

于是现在的问题就变成了两部分：
- 有多少种初始放置方式，使得操作后格子 $1$ 有 $c$ 个物品。
- 在格子 $1$ 放 $c$ 个物品可以使代价为 $m$ 的所有 $c$。 

### 问题一
记 $h(i,j,k)$ 表示考虑到了前 $i$ 个格子，在初始局面放了 $j$ 个物品后，对于格子 $1$ 相当于放了 $k$ 个物品的方案数，有转移：

$$h(i,j,k)=h(i-1,j,k)+h(i,j-1,k-f_i)$$

然后把第一维滚掉就可以在 $O(xn^2f_x)$ 的复杂度内求解。

### 问题二
求出格子 $1$ 放了 $i$ 个物品的代价为 $g_i$，就只需要对 $g_k=m$ 的 $h(x,n,k)$ 求和便可以得到答案。 

考虑最小化物品数量后的放置情况，即每个格子最多一个物品，且不存在两个相邻格子均含有物品，这样一定是不可再操作的，最小的物品数量方案，可以考虑用 $01$ 背包求解。 

估计 $1$ 格子放的物品最多为 $nf_x\le55000<75025=f_{25}$，所以只需要枚举前 $24$ 个格子是否放物品即可：

$$g_j=\min(g_j,g_{j-f_i}+1)$$

最终的答案为
$$res=\sum\limits_{i=1}^{nf_x} h(x,n,i)\times  [g_i=m]$$

---

## 作者：RoamingDuck (赞：0)

### 题目传送门
[link](http://codeforces.com/problemset/problem/1997/F)

### 思路
第一眼看到"方案数"这个词，肯定第一时间想到的是使用动态规划做这道题。

我们发现：$f_i=f_{i-1}+f_{i-2}$ 并且 $f_1=f_2=1$，这便是 Fibonacci 数列；又因为 $2 \le x\le 10$，所以我们计算得出 $f_{10}=55$，即 $1$ 号棋子至多有 $55000$ 个。

我们定义状态： $f_{i,j,k}$ 表示到 第 $i$ 个位置用了 $j$ 颗棋子，得到 $k$ 个棋子的方案数量。另外我们发现 $i$ 这一维度可以优化掉，节约了空间复杂度。

我们预处理 Fibonacci 数列数组的第 $1$~$24$ 项，并得出状态转移方程：$p_{i,j}=p_{i,j}+p_{j-1,k-a_i}$，最后累加满足条件的方案数即可。

如果想要有理有据作对一道题，首先写思路，然后根据思路写代码。这里我提供思路，代码看你们的了，加油！

---

## 作者：zifanwang (赞：0)

注意到操作是可逆的，可以先把所有筹码移动到位置 $1$，再进行若干次操作使筹码数量最小化。

那么我们只需要对每一个 $i$ 知道有多少种情况把筹码全移动到位置 $1$ 后恰好有 $i$ 个筹码，和这类情况的最少筹码数。

记 $f_i$ 表示斐波那契数列的第 $i$ 项，显然一个位置 $i$ 的筹码移动到位置 $1$ 后会变成 $f_i$ 个筹码。于是可以做一个 dp，记 ${dp}_{i,j,k}$ 表示前 $i$ 个位置放 $j$ 个筹码，全部移动到位置 $1$ 后有 $k$ 个筹码的方案数。需要滚动数组，每次直接 $\mathcal O(1)$ 转移。

接下来考虑怎么算最少筹码数。因为操作是可逆的，所以每次可以将 $f_i$ 个位置 $1$ 的筹码替换成一个位置 $i$ 的筹码。考虑贪心，从一个较大的 $f_i$ 开始枚举，每次选择尽量多的位置 $1$ 的筹码替换该位置的筹码，显然是最优的。

最后只需要把最少筹码数等于 $m$ 的方案数加起来就做完了，时间复杂度 $\mathcal O(xf_xn^2)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define mxn 200003
#define md 998244353
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int n,x,m,ans,f[30],dp[2][1002][55002];
bool fl;
inline void add(int &x,int y){
	x+=y;if(x>=md)x-=md;
}
signed main(){
	cin>>n>>x>>m;
	f[1]=f[2]=1;
	rep(i,3,25)f[i]=f[i-1]+f[i-2];
	dp[0][0][0]=1;
	rep(i,1,x){
		fl^=1;
		rep(j,0,n)rep(k,0,f[i]*j){
			dp[fl][j][k]=dp[fl^1][j][k];
			if(j&&k>=f[i])add(dp[fl][j][k],dp[fl][j-1][k-f[i]]);
		}
	}
	rep(i,0,n*f[x]){
		int s=0,x=i;
		drep(j,25,2){
			s+=x/f[j];
			x%=f[j];
		}
		if(s==m)add(ans,dp[fl][n][i]);
	}
	cout<<ans;
	return 0;
}
```

---

