# Expected Destruction

## 题目描述

You have a set $ S $ of $ n $ distinct integers between $ 1 $ and $ m $ .

Each second you do the following steps:

1. Pick an element $ x $ in $ S $ uniformly at random.
2. Remove $ x $ from $ S $ .
3. If $ x+1 \leq m $ and $ x+1 $ is not in $ S $ , add $ x+1 $ to $ S $ .

What is the expected number of seconds until $ S $ is empty?

Output the answer modulo $ 1\,000\,000\,007 $ .

Formally, let $ P = 1\,000\,000\,007 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{a}{b} $ , where $ a $ and $ b $ are integers and $ b \not \equiv 0 \pmod{P} $ . Output the integer equal to $ a \cdot b^{-1} \bmod P $ . In other words, output an integer $ z $ such that $ 0 \le z < P $ and $ z \cdot b \equiv a \pmod{P} $ .

## 说明/提示

For test 1, here is a list of all the possible scenarios and their probabilities:

1. $ [1, 3] $ (50% chance) $ \to $ $ [1] $ $ \to $ $ [2] $ $ \to $ $ [3] $ $ \to $ $ [] $
2. $ [1, 3] $ (50% chance) $ \to $ $ [2, 3] $ (50% chance) $ \to $ $ [2] $ $ \to $ $ [3] $ $ \to $ $ [] $
3. $ [1, 3] $ (50% chance) $ \to $ $ [2, 3] $ (50% chance) $ \to $ $ [3] $ $ \to $ $ [] $

Adding them up, we get $ \frac{1}{2}\cdot 4 + \frac{1}{4} \cdot 4 + \frac{1}{4} \cdot 3 = \frac{15}{4} $ . We see that $ 750000009 \cdot 4 \equiv 15 \pmod{1\,000\,000\,007} $ .

## 样例 #1

### 输入

```
2 3
1 3```

### 输出

```
750000009```

## 样例 #2

### 输入

```
5 10
1 2 3 4 5```

### 输出

```
300277731```

## 样例 #3

### 输入

```
5 10
2 3 6 8 9```

### 输出

```
695648216```

## 样例 #4

### 输入

```
1 100
1```

### 输出

```
100```

# 题解

## 作者：Alex_Wei (赞：27)

### [CF1854C Expected Destruction](https://www.luogu.com.cn/problem/CF1854C)

挺不错的题目。

若 $S$ 是可重集，则每次操作会令 $\sum S$ 恰好增加 $1$，因此答案为 $\sum m + 1 - S_i$。先用这个估计答案，再减去多算的部分。

考虑什么情况下会多算：考虑相邻两个元素的差。每次操作会将至多一个差值变为 $0$。如果变为 $0$ 的差值对应的相邻两个元素为 $t$，则答案减少 $m + 1 - t$。

根据期望的线性性，将答案摊到每相邻两个元素上。枚举 $S_{i + 1}\leq t \leq m$，求出过程中 $S_i$ 第一次等于 $S_{i + 1}$ 是 $S_i = t$ 的概率，则答案减去 $P\times (m + 1 - t)$。这等价于求出 $S_i = S_{i + 1} = t$ 的概率 $P$，并将答案减去 $P$。

设 $f_{x, y}$ 表示 $S_i = x$ 且 $S_j = y$ 的概率。初始化 $f_{S_i, S_{i + 1}} = 1$。对于 $x < y$，以 $\frac 1 2$ 为系数分别转移到 $f_{x + 1, y}$ 和 $f_{x, y + 1}$（我们不关心其它元素被选中，因此 $x$ 或 $y$ 先被选中的概率均为 $\frac 1 2$）。对于 $x = y$，将答案减去 $f_{x, x}(m + 1 - x)$。

再根据线性性，可以将所有 $(S_i, S_{i + 1})$ 放在一起 DP。

时间复杂度 $\mathcal{O}(m ^ 2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rnd(1064);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int Z = 1e6 + 5;
int fc[Z], ifc[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
}

// ---------- templates above ----------

constexpr int N = 500 + 5;

int n, m, S[N], f[N][N];
void mian() {
  cin >> n >> m;
  int ans = 0;
  for(int i = 1; i <= n; i++) cin >> S[i], ans += m + 1 - S[i];
  for(int i = 1; i < n; i++) f[S[i]][S[i + 1]] = 1;
  for(int i = 1; i <= m; i++) {
    addt(ans, mod - 1ll * (m + 1 - i) * f[i][i] % mod);
    for(int j = i + 1; j <= m; j++) {
      int c = 1ll * f[i][j] * (mod + 1 >> 1) % mod;
      addt(f[i][j + 1], c);
      addt(f[i + 1][j], c);
    }
  }
  cout << ans << "\n";
}

bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  while(T--) mian();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：BreakPlus (赞：11)

+ 观察这一过程，相当于 $n$ 个木块向右运动，两个木块相撞仅保留一个。

+ 如果没有相撞过程，那么答案是固定的。

+ 假设两个木块在距离终点 $x$ 处相撞，那么这种情况下，答案就会减少 $x$。

+ 一次相撞一定是原先相邻的木块相撞。否则，夹在中间的木块去哪里了呢？

+ 对于两个木块 $u,v$，把所有关于 $u,v$ 的操作拿出来，我们发现，不管其他木块怎么变化，$u$ 或 $v$ 有没有和其他木块相撞，由于题中给我们的随机性，这两个木块被抽中的概率是相等的。在所有拿出来的操作中，这两个木块被抽中的概率都是 $\dfrac{1}{2}$。

+ 那么我们很容易针对两个木块设计一个 DP 来解决这个问题。设 $f(i,j)$ 表示第一个木块走了 $i$ 步，第二个木块走了 $j$ 步的概率，当 $i$ 与 $j$ 的差值刚好是两个木块的距离时不再走下一步。

+ 时间复杂度 $\mathcal{O}(nm^2)$。很容易优化，但是这个做法更加直白。


```cpp
inline void add(ll &a,ll b){
	a+=b;
	if(a>=mod) a-=mod;
}
inline void Minus(ll &a,ll b){
	a-=b;
	if(a<0) a+=mod;
}
ll n,m,a[505],f[505][505];
void solve(){
	n=read(), m=read();
	ll ans = 0;
	for(ll i=1;i<=n;i++){
		a[i]=read();
		ans = (ans + m + 1 - a[i]) % mod;
	}
	ll inv2 = qpow(2, mod-2);
	for(ll i=1;i<n;i++){
		ll Dec = a[i+1] - a[i];
		memset(f,0,sizeof(f));
		f[0][0]=1; ll all = (2*m+2-a[i]-a[i+1]);
		for(ll sum=0;sum<=all;sum++){
			for(ll j=0;j<=sum && j<=m+1-a[i];j++){
				ll k = sum - j;
				if(k<=m+1-a[i+1]){
					if(j-k==Dec){
						Minus(ans , 1ll * (m+1-a[i]-j) * f[j][k] % mod);
					}else{
						ll x = 1ll * f[j][k] * inv2 % mod;
						add(f[j][k+1], x);
						add(f[j+1][k], x);
					}
				}
			}
		}
	} 
	printf("%d\n", ans);
}
```

---

## 作者：jasonliujiahua (赞：9)

# CF1854C

[题目传送门](https://www.luogu.com.cn/problem/CF1854C)
## 题意简述：
给定大小为 $n$ 的正整数集合 $S$，$S$ 中的每个数在 $1 \sim m$ 之间。每一秒进行如下操作：
- 从 $S$ 中等概率随机选择一个数 $x$。
- 将 $x$ 从 $S$ 中删去。
- 若 $x + 1\leq m$ 且 $x + 1\notin S$，则将 $x+1$ 加入 $S$。

求 $S$ 变成空集的期望时间，对 $10^9+7$ 取模。
$1\leq n\leq m \leq 500$，
$1\le S_1 < S_2 < \cdots < S_n \le m$。
## 题目分析：
### Step 1：转化题意
根据
$$E_{x+y}=E_x+E_y$$
可以把题目中要求的将 $S$ 变成空集转变成：**将所有的 $S_i$ 都删去的期望步数的和**。

### Step 2：DP
可以知道 $S_i$ 的期望步数只与 $S_{i+1}$ 有关。这是因为若 $S_{i+1}$ 右移的过程中碰到了 $S_{i+2}$ 那就会消掉一个，相当于还是 $S_{i+1}$。因此考虑一个 $O(m^2)$ 的 $dp$。

设 $dp_{i,j}$ 表示第一个数值在 $i$，第二个数值在 $j$ 时，$i$ 追到 $j$（相当于用 $j$ 消去 $i$）$i$ 所用的期望步数。这里为什么是 $S_i$ 的期望步数而不是 $S_i,S_{i+1}$ 的期望步数呢？这是因为 $S_{i+1}$ 对答案的贡献会在 $dp_{S_{i+1},S_{i+2}}$ 中计算，因此刚好不重不漏地统计了所有 $S_i$ 对答案的贡献。显然有转移方程：
$$dp_{i,j}=\frac{1}{2}(dp_{i+1,j}+1)+\frac{1}{2}dp_{i,j+1}$$
这里的 $\frac{1}{2}$ 是因为我们不关心除了 $i,j$ 之外的数（因为总会轮到它的）。最终的答案就是
$$ans=\left ( \sum_{i=1}^{n-1} dp_{S_i,S_{i+1}}\right )+(m+1-S_n)$$
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=510;
const int p=1e9+7;
const int inv2=500000004;
int n,m,ans,a[maxn],dp[maxn][maxn];
void init()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
}
void DP()
{
    for(int i=1;i<=m;i++) dp[i][m+1]=m+1-i;
    for(int i=m;i;i--)
        for(int j=m;j>i;j--)
            dp[i][j]=(inv2*(dp[i+1][j]+1+dp[i][j+1]))%p;
}
void output()
{
    for(int i=1;i<n;i++) ans=(ans+dp[a[i]][a[i+1]])%p;
    cout<<(ans+m+1-a[n])%p;
}
signed main()
{
    init();
    DP();
    output();
    return 0;
}
```

---

## 作者：睿智的憨憨 (赞：5)

# CF1854C Expected Destruction 解题报告

此题要用到期望的线性性，不知道可以[戳这里](https://oi-wiki.org/math/probability/exp-var/)。

自认为详细地讲了转移方程中的 $\frac{1}{2}$ 是怎么来的。

## 解法分析

### 题意转化

题意可以等价看成有 $n+1$ 个块，第 $i$ 个块的坐标为 $S_i$（$S_i$ 单调递增），第 $n+1$ 个块的坐标是给定的 $m+1$。每次操作从 $1 \sim n$ 中随机选一个块将其往正方向挪一个单位长度，若撞到了其他块就把自己的灵魂（？）交给这个块，然后消失（显然自己有自己的灵魂）。求 $1 \sim n$ 块都被消掉的操作次数的期望。

### 思路

考虑全局情况非常麻烦，但期望的线性性可以将处理的问题从全局变成局部。

根据期望的线性性，将所有块消掉的期望等于将每个块消掉的期望和，具体地，$\operatorname E(S_1,S_2,\dots,S_n)=\operatorname E(S_1)+\operatorname E(S_2)+\dots+\operatorname E(S_n)$，其中 $\operatorname E()$ 表示将括号内的坐标上的块消掉的期望操作次数。

不难知道第 $i$ 个块只能与有第 $i+1$ 个块的灵魂的块相撞，所以我们在研究 第 $i$ 个块的答案时可以盯着块 $i$ 与块 $i+1$ 的灵魂看。

假设研究块 $p$ 和块 $p+1$。可以用 dp 解决这个问题：$f_{i,j}$ 表示块 $p$ 坐标为 $i$，块 $p+1$ 的灵魂在 $j$ 时 $p$ 撞上 $p+1$ 的灵魂 $p$ 的期望移动次数。

转移方程很简单，先放出来：

$$f_{i,j} = \frac{1}{2}(f_{i+1,j}+1) + \frac{1}{2}f_{i,j+1}$$

其中的 $\frac{1}{2}$ 是关键，说一下是怎么来的：设目前共 $p$ 个块，取到每个块的概率均为 $\frac{1}{p}$，由于不取 $i,j$ 对答案无影响，所以转移式为：

$$f_{i,j} = \frac{p-2}{p}f_{i,j} + \frac{1}{p}(f_{i+1,j}+1) + \frac{1}{p}f_{i,j+1}$$

移项即可转换成带 $\frac{1}{2}$ 的式子。

默认 $S_{n+1}=m+1$，则最后的答案就是 $\sum\limits_{i=1}^{n}f_{S_i,S_{i+1}}$。

## 代码

```
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define lowbit(x) (x&(-x))
using namespace std;
const int N = 510, mod = 1e9 + 7;
const ll inv2 = 5e8 + 4;

int n, m, a[N];
ll f[N][N], ans;

int main(){
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	a[n + 1] = m + 1;
	for (int i = m; i >= 1; i--){
		for (int j = m + 1; j > i; j--){
			if (j == m + 1)
				f[i][j] = (f[i + 1][j] + 1) % mod;
			else
				f[i][j] = inv2 * (f[i + 1][j] + 1 + f[i][j + 1]) % mod;
		}
	}
	for (int i = 1; i <= n; i++)
		ans += f[a[i]][a[i + 1]];
	printf("%lld\n", ans % mod);
	return 0;
}
```

---

## 作者：littlebug (赞：3)

原来还可以这么玩。

期望的线性可加！这使我们可以忽略很多东西来分别计算！

## Solution

先单步容斥，若 $s$ 为可重集，那么答案为 $\sum m+1-s_i$。考虑如何计算两个元素重合的期望。若两个元素在位置 $x$ 重合，那么期望从答案里减去的操作数即为 $(m+1-x) \times p$，$p$ 为这两个元素在位置 $x$ 重合的概率。

但这样似乎还是没法做，因为哪两个元素相遇似乎很难处理，还要考虑中间有其他元素的情况，但是我们可以发现，两个元素相遇可以视作合并成了一个元素每次一起移动，也就是两个元素的相遇对另两个元素的相遇是没有影响的！于是我们便可以根据期望的线性可加性，分别计算相邻两个元素在每个位置重合的概率即可。

这一部分是简单的，dp 一下就可以，设 $f_{i,j}$ 为第一个元素在位置 $i$，第二个元素在位置 $j~(j>i)$ 的概率，因为只需要考虑这两个元素的移动，不考虑其它元素移动的情况，所以 $f_{i,j} = \frac 1 2 (f_{i-1,j} + f_{i,j-1})$。复杂度 $O(m^2)$，再加上枚举每一对元素，总共时间复杂度 $O(nm^2)$。

但是很显然，还是由于期望的线性可加，只接把所有元素放到一起 dp 也可以，复杂度 $O(m^2)$。

## Code

```cpp
const int MAXN=500+5;
int n,m,a[MAXN],f[MAXN][MAXN];

signed main()
{
    read(n,m),_::r(a,n);

    int ans=0;
    rep(i,1,n) ans+=m+1-a[i]; ans%=mod;

    rep(i,1,n-1) f[a[i]][a[i+1]]=1;
    rep(i,1,m) rep(j,i+1,m) f[i+1][j]+=f[i][j]*(mod+1>>1)%mod,f[i][j+1]+=f[i][j]*(mod+1>>1)%mod;

    rep(i,1,m) ans-=(m+1-i)*f[i][i]%mod;
    write((ans%mod+mod)%mod,'\n');

    return ot(),0;
}
```

---

## 作者：shs2007 (赞：2)

### CF1854C Expected Destruction

考虑对每个点 $s_i$ 计算贡献，发现每个点只与后面的点 $s_{i+1}$ 有关，即与 $s_{i+1}$ 相撞后就没了。

考虑 $dp$，$dp_{i,j}$ 表示两点 ${a,b}$ 与 $m+1$ 距离分别为 $i$，$j$ 对 $a$ 点计算期望步数。对于选择的其他点均对 ${a,b}$ 无影响，因此只与对 ${a,b}$ 的操作有关，每次等概率选择，概率即为 ${1/2}$。

考虑初始化：$dp_{i,0} = i,dp_{i,i} = 0$。

考虑转移：$dp_{i,j} = inv2 \times (dp_{i-1,j} + dp_{i,j-1} + 1)$。

最后对每个点计算答案即可，时间复杂度 $O(m^2)$。

[AC记录](https://codeforces.com/contest/1854/submission/223056124)

---

## 作者：huazai676 (赞：1)

[题目](https://www.luogu.com.cn/problem/CF1854C)

每个 $S_i$ 被删除前走的期望步数只与 $S_i$ 和 $S_{i+1}$ 有关，因为若 $S_{i+1}$ 被删除，也只会被删除 $S_{i+1}$ 的那个数替代。

所以若 $f_{i,j}(1\leq i\leq j\leq m)$ 表示从开始到 $i$ 被删除时 $i$ 的期望步数，只需求 $\sum\limits_{i=1}^n f_{S_i,S_{i+1}}(S_{n+1}=m+1)$。

为了能够转移，设 $f_{i,j,k}$ 为步数为 $k$ 的概率，则 $f_{i,j,k}=\frac{f_{i+1,j,k-1}+f_{i,j+1,k}}{2}$。

把 $k$ 这一维滚动掉就能卡进空间了。时间复杂度 $O(m^3)$。

[代码](https://codeforces.com/contest/1854/submission/221652581)

---

## 作者：Helenty (赞：0)

考虑差分出相邻的距离，考虑一个操作会使相邻两个距离左边 $+1$ 右边 $-1$，当一个数第一次变成 $0$ 的时候我们要减掉其代表的两个东西剩余路程。

注意到一个数只有两个操作涉及他一个是 $+1$ 一个是 $-1$，根据期望的线性性我们可以单独算这个数变成 $0$ 的贡献，而这两个操作在这个问题内分别就是 $\dfrac{1}{2}$ 的概率，那么我们每个分别 DP 就可以做到 $O(nm^2)$。

但是根据线性性我们可以全部丢一起 DP 做到 $O(m^2)$。

---

## 作者：MiRaciss (赞：0)

把数轴上初始存在的数看作关键点，首先根据期望的线性，我们将问题转换成每一个点被删去的期望步数。然后我们把一个点追逐上另一个点之后的过程看作**删去追逐另一个点的那个点**，也就是两点中靠前的那个点。

定义 $dp[i][j]$ 表示追逐的点初始位置在 $i$，被追逐的点初始位置在 $j$ 时删去追逐的点的期望步数。这样定义的好处是我们不用考虑数轴上 $i$ 之前的点发生了什么。

只考虑这一对点，每个点都有一半的概率被选中。那么 $dp[i][j] = \frac{1}{2}(dp[i+1][j] +1) + \frac{1}{2} dp[i][j+1]$。

最终的答案是 $m-s_n+1 + \sum\limits_{i=1}^{n-1} dp[s_i][s_{i+1}]$ 。

```cpp
// LUOGU_RID: 132844420
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=1e9+7;

ll inv;
ll Pow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1) ans*=a,ans%=Mod;
		a*=a,a%=Mod,b>>=1;
	}
	return ans;
}

int n,m;
ll dp[505][505];
int a[505];

int main(){
	inv=Pow(2,Mod-2);
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) dp[i][m+1]=m-i+1;
	for(int i=m;i>=1;i--) for(int j=m;j>=i+1;j--) dp[i][j]=inv*(dp[i+1][j]+dp[i][j+1]+1)%Mod;
	ll ans=0;
	for(int i=1;i<n;i++) ans+=dp[a[i]][a[i+1]],ans%=Mod; 
	ans+=(m-a[n]+1),ans=(ans%Mod+Mod)%Mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：zzafanti (赞：0)


[传送门](https://codeforces.com/problemset/problem/1854/C)

## description

给定正整数 $n,m$ 和集合 $S$，满足 $S$ 中元素互不相同且都是小于等于 $m$ 的正整数。每次进行如下操作

1. 从集合 $S$ 中随机选取一个数记作 $x$

2. 从 $S$ 中删去 $x$

3. 如果 $x+1\leq m$ 且 $x+1$ 不在 $S$ 中，把 $x+1$ 放入 $S$

求把集合清空的期望次数。

- $n,m,|S|\leq 500$

## solution

~~数据范围诈骗。~~

可以发现，一个数对答案的贡献不受比它小的数的影响，只需要考虑每个数合并到第一个比它大的数的期望步数（或者最后一个数合并到 $m+1$），依据期望的线性性把每个数的期望步数加起来即为答案。

于是问题转化成这样独立的模型：

已知两数分别为 $x,y(x\leq y)$，

- 若 $y\neq m+1$，随机把 $x$ 或 $y$ 加 1。

- 若 $y=m+1$，把 $x$ 加 1。

求 $f_{x,y}$ 表示使得初始的 $x,y$ 相等 **$x$ 的**期望增加步数。

显然有转移：

- $f_{i,i}=0$

- $f_{i,j}=\dfrac{(f_{i+1,j}+1)+f_{i,j+1}}{2}$

- $f_{i,m+1}=f_{i+1,m+1}+1$

时间复杂度 $O(m^2)$

## code

代码里的状态 $x,y$ 分别表示第一个数和第二个数到 $m+1$ 的距离。

[Submission #230364270 - Codeforces](https://codeforces.com/problemset/submission/1854/230364270)

## P.S.

[CF1540B 一个类似的方法算期望的题](https://www.luogu.com.cn/problem/CF1540B)


---

