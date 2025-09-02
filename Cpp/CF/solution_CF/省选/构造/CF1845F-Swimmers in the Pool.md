# Swimmers in the Pool

## 题目描述

有 $n$ 个游泳者在长度为 $l$ 的水池中游泳。每个游泳者从时刻 $0$ 出发且互不干涉。

每个游泳者遵循以下路线：第 $i$ 个游泳者从位置 $0$ 开始游泳，以恒定的速度 $v_i$（每个单位时刻移动 $v_i$ 个单位长度）游到位置 $l$，到达后立即以相同的速度返回到位置 $0$。回到位置 $0$ 之后，立即重复以上过程。

当水池中（可为 $0,l$ 或任意其他水池中的位置）至少有 $2$ 个游泳者在相同位置时，我们把该时刻称为“相遇时刻”。

水池会开放 $t$ 时刻。求在 $t$ 时刻内相遇时刻的数量。输出答案对 $10^9+7$ 取模的结果。

## 样例 #1

### 输入

```
9 18
2
1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
12 13
3
4 2 6```

### 输出

```
10```

## 样例 #3

### 输入

```
1 1000000000
3
100000 150000 200000```

### 输出

```
997200007```

# 题解

## 作者：honglan0301 (赞：6)

## 题目分析

我们首先考虑任两个人什么时候会相遇。这是一个小学数学问题，设两个人 $i,j$ 走的路程分别为 $s_i,s_j$，则当且仅当 $s_i+s_j=2kl$ 或 $|s_i-s_j|=2kl$ 时才会跑到同一个位置去。

因为我们更关心相遇时的时间而非路程，所以再把 $s$ 分解成 $v\cdot t$，注意到 $v$ 的值域很小，故我们试图求出所有的 $v$，于是想到 $\text{GF}$，直接先搞出来 $A(x)=\sum x^{v_i}$ 和 $B(x)=\sum x^{-v_i}$，那么:

* $A(x)^2$ 中所有系数不为 $0$ 的项就构成了 $\{v_i+v_j\}$（记得把所有的 $v_i+v_i$ 去掉，因为自己不能跟自己相遇）。

* $A(x)\times B(x)$ 中所有系数不为 $0$ 的地方就构成了 $\{v_i-v_j\}$（为了方便处理，我们可以先给 $B(x)$ 乘上一个 $x^{\max v_i}$）

记 $V=\{v_i+v_j\}\cup\{|v_i-v_j|\}$，接下来我们只需处理一个极简化版的问题：求有多少个 $\in[0,t]$ 的实数 $x$ 满足存在 $y\in V,k\in N^+$ 使得 $xy=2kl$。

注意到 $2l$ 是常数，所以再转化成求有多少个 $\in[0,\frac{t}{2l}]$ 的实数 $x$ 满足存在 $y\in V,k\in N^+$ 使得 $x=\frac{k}{y}$。

这个问题就非常好处理了，我们对每个 $y$ 分别考虑，用 $\text{dp}$ 的方式，令 $f_i$ 表示当 $y=i$ 时有多少个满足 $\gcd(k,y)=1$ 的 $k$ 符合要求。转移是：

$$f_i=\lfloor \frac{ti}{2l} \rfloor-\sum\limits_{j\mid i} f_j$$

最终的答案就是 $ans=\sum\limits_{\exists j\in V,i\mid j} f_i$（于是注意要先求出集合 $V$ 中数的约数），此处时间复杂度由调和级数求和知为 $O(n\log n)$，故总时间复杂度也是 $O(n\log n)$，另一个瓶颈在于前面的 $\text{NTT}$。

## 代码

```cpp
//NTT板子

signed main()
{
	cin>>l>>t>>n; for(int i=1;i<=n;i++) cin>>v[i],a[v[i]]++,b[200000-v[i]]++;
	for(int i=0;i<lim;i++) rv[i]=(rv[i>>1]>>1)+(i&1)*(1<<L-1);
	NTT(a,1); NTT(b,1);
	for(int i=0;i<lim;i++) b[i]=b[i]*a[i]%mod,a[i]=a[i]*a[i]%mod;
	NTT(a,-1); NTT(b,-1);
	for(int i=1;i<=n;i++) a[v[i]*2]--;
	for(int i=1;i<=400000;i++) if(a[i]) zt[i]=1;
	for(int i=1;i<=200000;i++) if(b[i+200000]) zt[i]=1;
	for(int i=1;i<=400000;i++) for(int j=2*i;j<=400000;j+=i) zt[i]|=zt[j];
	int ans=0;
	for(int i=1;i<=400000;i++)
	{
		dp[i]+=(t*i)/(2*l); dp[i]%=P; if(zt[i]) ans=(ans+dp[i])%P;
		for(int j=2*i;j<=400000;j+=i) dp[j]=(dp[j]-dp[i]+P)%P;
	}
	cout<<ans<<endl;
}
```


---

## 作者：InQueue (赞：1)

首先把 $(l,t)$ 变成 $(\dfrac12,\dfrac t{2l})$，可以证明答案不变。

此时，速度为 $a,b$（$a\neq b$）的两人在 $t_0$ 时刻相遇，当且仅当 $t_0(a+b)\in \mathbb{Z}$ 或 $t_0(a-b)\in \mathbb{Z}$。

令集合 $S := \left\{ x\mid \exists1\le i<j\le n,v_i+v_j=x\text{ or }\left|v_i-v_j\right|=x \right\}$。可以用 FFT / NTT 求出 $S$。

我们枚举互质的 $(i,j)$ 表示时间 $t_0=\dfrac ji$：

$$\begin{aligned}

ANS &= \sum_{i:\exists x\in S,i|x}\sum_{j\perp i,0<\frac ji\le t}1

\\ &= \sum_{i:\exists x\in S,i|x}\sum_{1\le j\le ti}[j\perp i]

\\ &= \sum_{i:\exists x\in S,i|x}\sum_{1\le j\le ti}\sum_{d|i,d|j}\mu(d)

\\ &= \sum_{i:\exists x\in S,i|x}\sum_{d|i}\mu(d)\sum_{1\le j\le ti,d|j}1

\\ &= \sum_{i:\exists x\in S,i|x}\sum_{d|i}\mu(d)\left \lfloor \dfrac{ti}d \right \rfloor 

\end{aligned}$$

这样直接按着式子枚举即可，总时间复杂度 $O(V\log V)$。

[CF 提交记录](https://codeforces.com/contest/1845/submission/312281046)。

---

## 作者：Little09 (赞：1)

小学学过的相遇问题和追及问题让我们得到，如果当前时间 $t$ 和两个人的速度 $v_a,v_b$ 满足 $t(v_a+v_b)=2kl$ 或 $t(v_a-v_b)=2kl$（$k$ 为正整数），那么此时这个时间 $t$ 就是一个“相遇时刻”。

首先我们可以用 FFT 求出所有符合的 $v_a+v_b$ 和 $v_a-v_b$，这样可行的 $v_a+v_b$ 或 $v_a-v_b$ 我们称做 $v$。然后考虑怎么不重不漏地计算出所有 $t=\frac{2kl}{v}$。首先如果一个 $v$ 可行我们可以把它的所有因子也加入集合中，这会方便我们操作。接下来考虑每个 $t=\frac{2kl}{v}$ 仅在一个地方计算贡献，也就是如果存在 $v$ 的一个因子也满足上式，那么就不在原先的 $v$ 处计算这个 $t$。所以我们从小到大枚举 $v$，然后用容斥减掉每个因子的贡献就行。

复杂度 $O(v\log v)$。

```cpp
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> l >> t >> n;
	rep(i,1,n)
	{
		int x;
		cin >> x;
		a[x]++,b[x]++;
	}
	mul(M,M,a,b,c);
	rep(i,0,M*2) d[i]=c[i];
	rep(i,0,M) d[i*2]-=a[i];
	reverse(b,b+M+1);
	mul(M,M,a,b,c);
	rep(i,1,M) d[i]+=c[i+M];
	// rep(i,1,M*2) if (d[i]>0) cout << i << " ";
	// cout << endl;
	l*=2;
	ll ans=0;
	per(i,M*2,1) for (int j=2;i*j<=2*M;j++) d[i]=max(d[i],d[i*j]);
	rep(i,1,M*2)
	{
		(dp[i]+=1ll*t*i/l)%=mod;
		for (int j=2;i*j<=M*2;j++) (dp[i*j]+=mod-dp[i])%=mod;
		if (d[i]>0) (ans+=dp[i])%=mod;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：win114514 (赞：0)

### 思路

考虑两个人什么时候会相遇。

根据小学的相遇追及问题，两人会相遇的条件为：

$$2\times k\times l=t\times (v1+v2)$$
$$2\times k\times l=t\times (v1-v2)$$

那么对于一个速度 $v$。

它可一相遇的次数即为：

$$\frac{t\times v}{2\times l}$$

当然，这样有可能会算重，也就是在相同的时间算了多次答案。

注意到若两个 $v$ 有倍数关系，那么就会算重答案。

所以可以更改一下式子：

$$f_v=\frac{t\times v}{2\times l}-\sum_{i=1}^{i<v}[i|v] f_i$$

可以直接枚举倍数计算。

至于如何求出所有的 $v$ 是否等于 $v1+v2$ 或者 $v1-v2$。

可以看作两个多项式：

$$f=x^{v_1}+x^{v_2}+x^{v_3}+x^{v_4}\cdots $$

$$g=x^{-v_1}+x^{-v_2}+x^{-v_3}+x^{-v_4}\cdots $$

算出 $f$ 与 $f$ 和 $f$ 与 $g$ 的卷积即可，可以使用 ntt 加速。

时间复杂度：$O(v\ln v+v\log v)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
// #define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for(int i = (x); i <= (y); i++)
#define pre(i, x, y) for(int i = (x); i >= (y); i--)
inline void JYFILE19();

typedef long long i64;
typedef pair<int, int> PII;

bool ST;
const int N = 2e6 + 10;
const int M = 2e5;
const int mod = 998244353;
const int Mod = 1e9 + 7;

int l, t, n, ans, v[N], f[N], g[N], h[N], dp[N];

inline i64 power(i64 x, i64 y) {
  i64 res = 1;
  while(y) {
    if(y & 1) res = res * x % mod;
    x = x * x % mod, y /= 2;
  }
  return res;
}

struct ntt {
  int m, tp, b[N], w[N];
  int g = 3, ig = power(3, mod - 2);
  #define Add(x, y) ((x + y >= mod) ? x + y - mod : x + y)
  #define Sub(x, y) ((x - y >= 0) ? x - y : x - y + mod)
  inline void init(int n) {
    if(m == (1<<__lg(n)+1)) return; m = (1<<__lg(n)+1);
    fro(i, 0, m - 1) b[i] = (b[i>>1]>>1)|((i&1)?m>>1:0);
  }
  inline void NTT(int *f, int n) {
    init(n), w[0] = 1; int iv = (tp?power(m,mod-2):1);
    fro(i, 1, m) if(i < b[i]) swap(f[i], f[b[i]]);
    for(int p = 1; p < m; p <<= 1) {
      int s = p<<1, b = power(tp?ig:g,(mod-1)/s);
      for(int i = p - 2; i >= 0; i -= 2)
        w[i | 1] = 1ll * b * (w[i] = w[i>>1]) % mod;
      for(int i = 0; i < m; i += s) fro(j, 0, p - 1) {
        int x = f[i + j], y = 1ll * f[i + j + p] * w[j] % mod;
        f[i + j] = Add(x, y), f[i + j + p] = Sub(x, y);
      }
    }
    if(tp) fro(i, 0, m - 1) f[i] = 1ll * f[i] * iv % mod;
  }
  inline void times(int *f, int *g, int n) {
    tp = 0, NTT(f, n), NTT(g, n);
    fro(i, 0, m - 1) f[i] = 1ll * f[i] * g[i] % mod;
    tp = 1, NTT(f, n);
    fill(g, g + m, 0);
    fill(f + n + 1, f + m, 0);
  }
} sol;

signed main() {
  JYFILE19();
  cin >> l >> t >> n;
  fro(i, 1, n) cin >> v[i];
  fro(i, 1, n) f[M + v[i]] = 1;
  fro(i, 1, n) g[M + v[i]] = 1;
  sol.times(f, g, M * 4);
  fro(i, 0, M * 2) dp[i] = max(f[i + M * 2], dp[i]);
  fro(i, 1, n) dp[v[i] * 2]--;
  memset(f, 0, sizeof f);
  memset(g, 0, sizeof g);
  fro(i, 1, n) f[M + v[i]] = 1;
  fro(i, 1, n) g[M - v[i]] = 1;
  sol.times(f, g, M * 4);
  fro(i, 0, M * 2) dp[i] = max(f[i + M * 2], dp[i]);
  fro(i, 1, M * 2) {
    for(int j = 1; j * i <= M * 2; j++) {
      dp[i] = max(dp[i], dp[j * i]);
    }
  }
  fro(i, 1, M * 2) {
    (h[i] += (1ll * i * t / (l * 2)) % Mod) %= Mod;
    for(int j = 2; j * i <= M * 2; j++)
      (h[i * j] += Mod - h[i]) %= Mod;
    if(dp[i] > 0) (ans += h[i]) %= Mod;
  }
  cout << ans << "\n";
  return 0;
}

bool ED;
inline void JYFILE19() {
  // freopen("", "r", stdin);
  // freopen("", "w", stdout);
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED-&ST)/1048576.), LIM = 512;
  cerr << "MEMORY: " << MIB << endl, assert(MIB<=LIM);
}
```

---

## 作者：Mars_Dingdang (赞：0)

刚学习生成函数和多项式，真的很菜捏。

## 题目大意
有 $n$ 个游泳者在长度为 $l$ 的水池中游泳。每个游泳者从时刻 $0$ 出发且互不干涉。

每个游泳者遵循以下路线：第 $i$ 个游泳者从位置 $0$ 开始游泳，以恒定的速度 $v_i$（每个单位时刻移动 $v_i$ 个单位长度）游到位置 $l$，到达后立即以相同的速度返回到位置 $0$。回到位置 $0$ 之后，立即重复以上过程。

当水池中（可为 $0,l$ 或任意其他水池中的位置）至少有 $2$ 个游泳者在相同位置时，我们把该时刻称为“相遇时刻”。

水池会开放 $t$ 时刻。求在 $t$ 时刻内相遇时刻的数量。输出答案对 $10^9+7$ 取模的结果。

$n,v\le 2\times 10^5, l,t\le 10^9$。

## 大体思路
对于相遇和追及问题，小学奥数告诉我们其路程必定相差两个全程的若干倍，即 $(v_i+v_j)t=2kl$ 或 $(v_i-v_j)t=2kl$。显然这里的绝对值并不重要。

然后，由于 $v$ 很小，我们可以得到 $V=\{v_i+v_j\}\cup \{|v_i-v_j|\}$。暴力枚举是 $O(n^2)$ 的，但是我们可以得到普通型生成函数 
$$F(x)=\sum_{i=1}^n x^{v_i}, G(x)=\sum_{i=1}^n x^{-v_i}$$

这样 $[x^v]F(x)^2$ 和 $[x^v]F(x)G(x)$ 是否不为 $0$ 就表示 $v$ 是否在集合 $V$ 中。当然有一些边界，比如负指数要整体平移，再比如去掉 $i=j$ 的情况等。

然后相当于对于 $v\in V$，需要有时刻 $x$ 满足 $vx=2kl$，即 $\exists x\in [0,\dfrac{t}{2l}]$ 使得 $x=\dfrac k v$。

记 $f_v$ 表示有多少个 $k$ 满足 $(k,v)=1$ 且 $\dfrac k v\in [0,\dfrac{t}{2l}]$。这里强制 $(k,v)=1$ 是为了除去重复的时刻。比如存在 $4\in V,8\in V$，那么 $\dfrac 8 4=\dfrac {16} 8=2$ 都对应时刻 $2$。当然这样可能导致 $v\in V$ 被错误地约分（如上述例子中 $4,8$ 都没有被考虑），因此统计答案时可以枚举 $v$ 的约数，即 
$$ans=\sum_{\exists v\in V, d|v}f_d$$

$f$ 的转移是显然的。由于 $\dfrac k v\in [0,\dfrac{t}{2l}]$，因此 $1\le k\le \dfrac{tv}{2l}$。再枚举 $v$ 的约数减去与之互素的合法的 $k$ 的数量即可。

$$f_v=\left\lfloor\dfrac{tv}{2l}\right\rfloor-\sum_{d|v}f_d$$

时间复杂度 $O(n\ln n+V\log V)$，前者是 DP 时级数求和，后者来自 NTT。

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 4e5 + 5, MAX = 4e5;
const int mod = 1e9 + 7;
template <typename T>
inline void chkmax(T &x, T y) {x = (x > y ? x : y);}
template <typename T>
inline void chkmin(T &x, T y) {x = (x < y ? x : y);}
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;

ll l, t, n, f[maxn], ans;
bool vis[maxn];
int main () {
	read(l); read(t); read(n);
	vector <int> v(n + 1), a(MAX), b(MAX);
	rep(i, 1, n) read(v[i]), a[v[i]] ++, b[200000 - v[i]] ++;
	PolyS A(a), B(b);
	PolyS AP = A * A, AM = A * B;
	rep(i, 1, n) AP[v[i] * 2] --;
	rep(i, 1, MAX) if(AP[i]) vis[i] = 1;
	rep(i, 1, 200000) if(AM[i + 200000]) vis[i] = 1;
	rep(i, 1, MAX) for(int j = 2 * i; j <= MAX; j += i) vis[i] |= vis[j];
	rep(i, 1, MAX) {
		(f[i] += (t * i) / (2 * l)) %= mod;
		if(vis[i]) (ans += f[i]) %= mod;
		for(int j = 2 * i; j <= MAX; j += i) (f[j] -= f[i]) %= mod;
	}
	writeln((ans + mod) % mod);
	
	return 0;
}
```
省略了封装好的[多项式全家桶](https://www.luogu.com.cn/paste/4he1knid)。

## 后记
现在是 2023 年 12 月 31 日 22 点 25 分，希望在新的一年里多项式水平能够有所提高，OI 之路能够顺利。

最后一年了！

---

