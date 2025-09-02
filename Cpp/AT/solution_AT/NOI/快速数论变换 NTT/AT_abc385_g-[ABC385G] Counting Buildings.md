# [ABC385G] Counting Buildings

## 题目描述

对于一个 $(1,2,\dots,N)$ 的排列 $P=(P_1,P_2,\dots,P_N)$，定义整数 $L(P)$ 和 $R(P)$：

-   考虑 $N$ 栋从左到右的建筑，其中第 $i$ 栋建筑的高度为 $P_i$。然后 $L(P)$ 表示从最左边能看到的建筑的数量，$R(P)$ 表示从最右边能看到的建筑的数量。  
    更正式的说，$L(P)$ 为满足对于所有 $j<i$ 都有 $P_j<P_i$ 的 $i$ 的个数，$R(P)$ 为满足对于所有 $j>i$ 都有 $P_i>P_j$ 的 $i$ 的个数。

给定你整数 $N$ 和 $K$。找出满足 $L(P)-R(P)=K$ 的 $(1,2,\dots,N)$ 的排列 $P$ 的数量对 $998244353$ 取模后的值。

## 说明/提示

- $1\le N\le 2\times 10^5$
- $\mid K\mid\le N-1$
- 所有输入都为整数。

## 样例 #1

### 输入

```
3 -1```

### 输出

```
1```

## 样例 #2

### 输入

```
1 0```

### 输出

```
1```

## 样例 #3

### 输入

```
2024 385```

### 输出

```
576300012```

# 题解

## 作者：Register_int (赞：14)

省流：P4609+P5408 即可，时间复杂度 $O(n\log n)$，爆标。

---

具体地，先来考虑对于一对确定的 $L(p)$ 与 $R(p)$ 怎么做。首先你会发现前后缀最大值数组大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/oteim142.png)

也就是以 $n$ 为峰后两边就互不影响了，所以先把 $n$ 放进去，只考虑一边。不妨先看前缀最大值，我们可以分成这么多段：

![](https://cdn.luogu.com.cn/upload/image_hosting/3mn3uehc.png)

首先内层可以随便排，只要保证最大值在最左侧就好了。内层确定后外层也随之确定，因为我们只能按内层最大值从小到大的顺序去排列。因此方案数是将这些数分成 $L(p)-1$ 个圆排列的方案数。

后缀是同理的，可以先把所有 $L(p)+R(p)-2$ 个圆排列分出来，再将其中的 $L(p)-1$ 个分到 $n$ 左侧。方案数为：

$$\left[\begin{matrix}n-1\\L(p)+R(p)-2\end{matrix}\right]\dbinom{L(p)+R(p)-2}{L(p)-1}$$

那么压力就给到了求一行的一类斯特林数。这个也是好办的，我们有：

$$x^{\overline{n}}=\sum_i\left[\begin{matrix}n\\i\end{matrix}\right]x^i$$

所以我们的目标就是将 $x^{\overline{n}}$ 转普通幂多项式。你考虑到我们有：

$$x^{\overline{2n}}=x^{\overline{n}}(x+n)^{\overline{n}}$$

所以你可以倍增，每次对多项式做一个平移后和自己乘起来就好了。时间复杂度 $T(n)=T(n/2)+O(n\log n)=O(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

namespace polynomial {
	// By Ri.
}

using namespace polynomial;

const int MAXN = 2e5 + 10;

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll c(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}


inline 
poly<ll> offset(poly<ll> f, int n, ll c) {
	poly<ll> a(n), b(n);
	b[0] = 1;
	for (int i = 0; i < n; i++) a[n - i - 1] = f[i] * fac[i] % mod;
	for (int i = 1; i < n; i++) b[i] = b[i - 1] * c % mod;
	for (int i = 0; i < n; i++) b[i] = b[i] * ifac[i] % mod;
	a *= b;
	for (int i = 0; i < n; i++) b[i] = a[n - i - 1] * ifac[i] % mod;
	return b;
}

inline 
poly<ll> solve(int n) {
	poly<ll> f;
	if (!n) return f.push_back(1), f;
	int m = n >> 1;
	f = solve(m);
	poly<ll> g = f; f = offset(f, m + 1, m);
	f.resize(n + 1), g.resize(n + 1);
	f *= g;
	if (n & 1) {
		for (int i = 0; i <= n; i++) g[i] = ((i ? f[i - 1] : 0) + (n - 1) * f[i]) % mod;
	} else g = f;
	return g;
}

int n, m; poly<ll> f; ll ans;

int main() {
	scanf("%d%d", &n, &m), m = abs(m), init(n), f = solve(n - 1);
	for (int i = m + 1, j = 1; i <= n && i + j - 2 < n; i++, j++) {
		ans = (ans + f[i + j - 2] * c(i + j - 2, i - 1)) % mod;
	}
	printf("%lld", ans);
}
```

---

## 作者：emmoy (赞：9)

## 题目大意

对于一个排列 $p$，定义 $L(p)$ 为 $p$ 中有多少个 $i$，满足 $\forall j<i,h_j<h_i$，$R(p)$ 为 $p$ 中有多少个 $i$，满足 $\forall j>i,h_j<h_i$，问有多少个排列 $p$，满足 $L(p)-R(p)=k$。

## 做法

### $\mathcal{O}(n^2)$ 做法

考虑差值 dp，设 $f_{i,j}$ 表示我们将从 $n-i+1$ 至 $n$ 的数放入序列后，$L(\text{当前序列})-R(当前序列)=j$ 的方案数。

考虑从 $i-1$ 转移到 $i$。

首先，现在有 $i$ 个位置可以插入（有 $i-1$ 个点，包括首尾），那么如果插入队头，那么 $L$ 会加 $1$，$R$ 不变，于是 $f_{i-1,j-1}\Rightarrow f_{i,j}$，插入队尾同理，于是 $f_{i-1,j+1}\Rightarrow f_{i,j}$，剩下的 $i-2$ 个位置都在中间，因为以前插入的所有点都比当前点高，所以 $L,R$ 都不变，所以 $f_{i-1,j}\times (i-2)\Rightarrow f_{i,j}$。

整合一下:

$$
f_{i,j}=f_{i-1,j-1}+f_{i-1,j+1}+f_{i-1,j}\times(i-2)
$$

边界 $f_{1,0}=1$。

给出代码(滚动数组)
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=998244353;
int n,k;
int f[200010],g[200010];
signed main(){
	cin>>n>>k;
	k=100000-k;
	g[100000]=1;
	for(int i=2;i<=n;i++){
		for(int j=100000-i+1;j<=100000+i-1;j++){
			f[j+1]=(f[j+1]+g[j])%p;
			f[j-1]=(f[j-1]+g[j])%p;
			f[j]=(f[j]+g[j]*(i-2)%p)%p;
		}
		for(int j=100000-i;j<=100000+i;j++){
			g[j]=f[j],f[j]=0;
		}
	}
	cout<<g[k];
	return 0;
}
```
然而只过了样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/xkm32wef.png)
### $\mathcal{O}(n\log^2n)$ 做法

我们考虑优化上面的 dp，我们发现 $f_{i-1,j-1}\Rightarrow f_{i,j}$ 相当于整体右移了一位，$f_{i-1,j+1}\Rightarrow f_{i,j}$ 相当于整体左移了一位，所以我们可以将其看成一个多项式。

$$
f_1=1\times x^0=1\\
f_i=xf_{i-1}+x^{-1}f_{i-1}+(i-2)f_{i-1}=f_{i-1}[x+x^{-1}+(i-2)]
$$

递推有些难看，于是转化成

$$
f_n=f_1\times\prod^{n}_{i=2}[x+x^{-1}+(i-2)]
$$

$i-2$ 还是难看，于是变成

$$
f_n=f_1\times\prod^{n-2}_{i=0}(x+x^{-1}+i)
$$

又因为 $f_1=1$，所以答案为 $\prod^{n-2}_{i=0}(x+x^{-1}+i)$ 的 $x^{k}$ 项的系数。

但是 $x^{-1}$ 还是不好搞，于是乘上 $n-1$ 个 $x$ 再除回去，于是变成

$$
\prod^{n-2}_{i=0}(x^2+ix+1)\over x^{n-1}
$$

相当于求出 $\prod^{n-2}_{i=0}(x^2+ix+1)$ 的 $x^{k+n-1}$ 项的系数。

考虑如何快速求。

我们可以每次将两个次数最小的多项式先乘起来，这样复杂度可以优化至 $\mathcal{O}(n\log^2n)$。

~~和玩2048一样~~
### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353,y=3,ny=332748118;
const int N=1e6+10;
int n,k;
int ksm(int a,int b=mod-2){
	int ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
int a[N],r[N];
int limit,l;
void NTT(int *f,int type){//NTT板子
	for(int i=0;i<limit;i++) if(i<r[i]) swap(f[i],f[r[i]]);
	for(int mid=1;mid<limit;mid<<=1){
		int Wn=ksm((type?y:ny),(mod-1)/(mid<<1));
		for(int j=0,R=mid<<1;j<limit;j+=R){
			int w(1);
			for(int k=0;k<mid;k++,w=w*Wn%mod){
				int x=f[j+k],y=f[j+k+mid]*w%mod;
				f[j+k]=(x+y)%mod;
				f[j+k+mid]=(x+mod-y)%mod;
			}
		}
	}
	if(type) return;
	int h=ksm(limit);
	for(int i=0;i<limit;i++) f[i]=f[i]*h%mod;
}
int lg[N];//多项式长度
void mul(int *f,int *g,int l1,int l2){
	int re=lg[l1]+lg[l2]-1;
	for(limit=1,l=0;limit<re;limit<<=1,l++);
	for(int i=1;i<limit;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	NTT(f,1),NTT(g,1);
	for(int i=0;i<limit;i++) f[i]=f[i]*g[i]%mod,g[i]=0;
	NTT(f,0);
	lg[l1]=re;
}
int g[40][N],rp;
//因为长度不同的多项式最多不会超过log n个，所以开40就够了
signed main(){
	cin>>n>>k;
	if(n==1){//特判n=1的情况
		if(k==0) cout<<1;
		else cout<<0;
		return 0;
	}
	k+=n-1;
	for(int i=0;i<=n-2;i++){
		rp++;
		lg[rp]=3,g[rp][0]=1,g[rp][1]=i,g[rp][2]=1;
		while(rp>1&&lg[rp]==lg[rp-1]){//合并相同长度的
			mul(g[rp-1],g[rp],rp-1,rp);
			rp--;
		}
	}
	while(rp>1){//合并剩余的
		mul(g[rp-1],g[rp],rp-1,rp);
		rp--;
	}
	cout<<g[1][k];
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：6)

观察：从 $n$ 将排列分成前后两部分，前缀 $\max$ 都会在左边，后缀 $\max$ 都会在右边。

考虑一个一个插入元素，从小到大插入会推平掉一段区间，这是不好处理的。不妨从大到小插入元素，新元素造成贡献当且仅当它在两边。

具体的，设 $f_{i,j}$ 表示长度为 $i$ 的排列 $[n-i+1,n-i+2,\ldots,n]$ 里前缀 $\max$ 数量与后缀 $\max$ 数量差为 $j$ 的排列数，考虑插入一个新的最小值 $x$ 后的状态：

- 将 $x$ 插入到开头，使得前缀 $\max$ 增加 $1$，转移到 $f_{i+1,j+1}$。
- 将 $x$ 插入到末尾，使得后缀 $\max$ 增加 $1$，转移到 $f_{i+1,j-1}$。
- 将 $x$ 插入到中间，前后缀 $\max$ 都没有变化，转移到 $f_{i+1,j}$，系数为 $i-1$。

最终答案即为 $f_{n,k}$。

直接 DP 时间复杂度是 $\mathcal O(n^2)$ 的，不能通过。但是这个 DP 有很好的性质：$j$ 改变的时候系数都是 $1$。考虑枚举 $j \gets j+1$ 发生了 $x$ 次，那么 $j \gets j - 1$ 应当发生 $x-k$ 次。不妨枚举所有大小为 $2x-k$ 的 $\{1,2,\ldots,n-1\}$ 的子集 $S$，表示 $\forall i \in S$，$i \gets i +1$ 的时候 $j$ 发生了变化，则首先应当乘上 $\dbinom{2x-k}{x}$ 的系数，然后乘上所有不在 $S$ 中的 $(i-1)$ 的乘积。

不难发现我们只需要求所有大小为 $n-1-(2x-k)$ 的子集的乘积的和，这是背包问题。考虑分治，合并两个区间的答案是一个卷积，NTT 即可。复杂度 $\mathcal O(n \log^2 n)$。

[Code](https://atcoder.jp/contests/abc385/submissions/60956417)。

---

## 作者：SpadeA261 (赞：5)

显然 $K$ 与 $|K|$ 的答案相等。

考虑 $n\rightarrow n+1$ 的过程，可以看作是先整体加一，再把 $1$ 插到里面。设 $S=L(P)-R(P)$，把 $1$ 插到开头 $S$ 会变为 $S+1$，插到结尾 $S$ 会变为 $S-1$，插到其余的 $n-1$ 个位置则还是 $S$。可以写成转移式：

$$f_{1,0}=1,f_{n,k}=f_{n-1,k-1}+f_{n-1,k+1}+(n-2)f_{n-1,k}$$

考虑用多项式刻画，则有：

$$F_1=1,F_n=\left(x+x^{-1}+n-2\right)F_{n-1}$$

平移将 $x^{-1}$ 消掉：

$$F_1=1,F_n=\left(x^2+(n-2)x+1\right)F_{n-1}$$

分治 NTT 即可，答案为 $[x^{N+|K|-1}]F_N$。

```cpp
int n,k;
vector<mint> calc(int l,int r)
{
    if(l==r) return {1,l-2,1};
    int mid=(l+r)>>1;
    return convolution(calc(l,mid),calc(mid+1,r));
}
void solve()
{
    cin>>n>>k;
    if(n==1){cout<<1<<endl;return;}
    vector<mint> F=calc(2,n);
    cout<<F[n+abs(k)-1].val()<<endl;
    return;
}
```

---

## 作者：Felix72 (赞：2)

比较有代表性的数学方法优化 DP。

考虑到最高建筑两边都有建筑，同时维护会显得难以计算，因此不妨钦定最高建筑在右边，那么能看见的其他建筑（设数量为 $m$）全部在左边。我们把其中 $c$ 个建筑翻转过去，可以得到左右都有建筑的状态，那么这时它的贡献是 $m \choose c$。

设 $f_{i, j}$ 表示从左到右有 $i$ 个建筑，能看见 $j$ 个的方案数，转移是 $f_{i, j} = f_{i - 1, j - 1} + f_{i - 1, j} \times (i - 1)$。这和 $n \brack m$ 的定义一致。

综上，确定左右各能看见多少建筑后，贡献为一个斯特林数乘上一个组合数。

套用求一行第一类斯特林数的方法，对 $x^{\bar n}$ 倍增就可以了。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 1200010, mod = 998244353, g = 3, gi = (mod + 1) / g;
int rev[N]; long long fac[N], inv[N];
inline long long C(int n, int m)
{
	if(n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
inline long long qpow(long long a, long long b)
{
	long long res = 1;
	while(b)
	{
		if(b & 1) res = res * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return res;
}
inline void exgcd(long long a, long long b, long long &x, long long &y)
{
	if(b == 0) {x = 1, y = 0; return ;}
	exgcd(b, a % b, y, x); y -= a / b * x;
}
inline long long Inv(long long num)
{
	long long x, y; exgcd(num, mod, x, y);
	x = (x % mod + mod) % mod; return x;
}
inline void init()
{
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= 1200000; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[1200000] = Inv(fac[1200000]);
	for(int i = 1199999; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}

struct Poly
{
	int n; vector < long long > f;
	inline void NTT(int opt, int len)
	{
		f.resize(len);
		for(int i = n + 1; i < len; ++i) f[i] = 0;
		for(int i = 0; i < len; ++i) rev[i] = (rev[i / 2] / 2) + ((i & 1) ? (len / 2) : 0);
		for(int i = 0; i < len; ++i) if(i > rev[i]) swap(f[i], f[rev[i]]);
		for(int i = 1; (1 << i) <= len; ++i)
		{
			long long wn = ((opt == 1) ? qpow(g, (mod - 1) >> i) : qpow(gi, (mod - 1) >> i));
			for(int j = 0; j < len; j += (1 << i))
			{
				long long w = 1;
				for(int k = j; k < j + (1 << (i - 1)); ++k, w = w * wn % mod)
				{
					long long n1 = f[k], n2 = f[k + (1 << (i - 1))] * w % mod;
					f[k] = (n1 + n2) % mod, f[k + (1 << (i - 1))] = (n1 - n2 + mod) % mod;
				}
			}
		}
		if(opt == -1)
		{
			long long iv = Inv(len);
			for(int i = 0; i < len; ++i) f[i] = f[i] * iv % mod;
		}
	}
	inline void output() {for(int i = 0; i <= n; ++i) cout << f[i] << " "; cout << '\n';}
};
Poly operator * (Poly A, Poly B)
{
	int len = 1;
	Poly C; C.n = 0;
	while(len < A.n + B.n + 1) len *= 2;
	C.f.resize(len);
	A.NTT(1, len), B.NTT(1, len);
	for(int i = 0; i < len; ++i) C.f[i] = 0;
	for(int i = 0; i < len; ++i) C.f[i] = A.f[i] * B.f[i] % mod;
	C.n = len - 1;
	C.NTT(-1, len); C.n = A.n + B.n;
	return C;
}

int n, k; Poly stir;
inline void transform(int op)
{
	if(op == 1)
	{
		Poly mul; mul.n = 1; mul.f.resize(2);
		mul.f[0] = stir.n, mul.f[1] = 1;
		stir = stir * mul;
	}
	else
	{
		Poly A, B, C; A.n = B.n = stir.n;
		A.f.resize(stir.n + 1), B.f.resize(stir.n + 1);
		for(int i = 0; i <= stir.n; ++i) A.f[i] = fac[i] * stir.f[i] % mod;
		for(int i = 0; i <= stir.n; ++i) B.f[i] = qpow(stir.n, stir.n - i) * inv[stir.n - i] % mod;
		C = A * B;
		for(int i = 0; i <= stir.n; ++i) A.f[i] = C.f[i + stir.n] * inv[i] % mod;
		B = stir;
		stir = A * B;
	}
}
inline void solve(int m)
{
	if(m == 0) return ;
	solve(m / 2); transform(2);
	if(m & 1) transform(1);
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.err", "w", stderr);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	init();
	cin >> n >> k;
	stir.n = 0, stir.f.resize(1); stir.f[0] = 1;
	solve(n - 1);
	long long res = 0;
	for(int ln = 0; ln <= n; ++ln)
	{
		int rn = ln - k;
		if(rn >= 0 && ln + rn <= n + 1 && (ln - 1) + (rn - 1) >= 0)
			res = (res + stir.f[(ln - 1) + (rn - 1)] * C((ln - 1) + (rn - 1), ln - 1) % mod) % mod;
	}
	cout << res << '\n';
	return 0;
}
/*

*/
```

---

## 作者：WorldMachine (赞：2)

题意：求有多少个长度为 $n$ 的排列 $P$，使得其从左往右的单调栈长度 $L(P)$ 和从右往左的单调栈长度 $R(P)$ 之差为 $k$。

设 $f_{i,j}$ 表示插入了 $[n-i,n]$ 中的数，且 $L(P)-R(P)=k$ 的方案数，初始值为 $f_{0,0}=1$。

考虑插入 $n-i-1$ 带来的影响：

- 放在最左边，$L(P)$ 会增加 $1$，$R(P)$ 不变；
- 放在最右边，$R(P)$ 会增加 $1$，$L(P)$ 不变；
- 插在中间，那么 $L(P)$ 和 $R(P)$ 都不变。

故转移方程为：
$$
f_{i,j}=f_{i-1,j-1}+(i-1)f_{i-1,j}+f_{i-1,j+1}
$$
最终答案为 $f_{n-1,k}$。

这是 $\mathcal O(n^2)$ 的，压缩状态是不太现实的，只能考虑类似整体 dp 的转移。

把 $f_i$ 作为一个多项式（当然这里会有 $x^{-1}$ 这样的项，所以要整体乘上一个 $x^n$），有 $[x^j]f_i=f_{i,j}$。那么有：
$$
f_i=(x^{-1}+i-1+x)f_{i-1}
$$
则 $f_n$ 为：
$$
\prod_{i=0}^{n-2}(x^{-1}+i+x)
$$
直接分治做乘法即可，时间复杂度为 $\mathcal O(n\log^2n)$。

代码使用了 atcoder library 中的多项式乘法。
```cpp
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef modint998244353 mint;
typedef vector<mint> poly;
#define mul convolution
vector<mint> solve(int l, int r) {
	if (l > r) return {1};
	if (l == r) return {1, l - 1, 1};
	int mid = (l + r) >> 1;
	return mul(solve(l, mid), solve(mid + 1, r));
}
int main() {
	int n, k;
	cin >> n >> k;
	vector<mint> f = solve(1, n - 1);
	cout << f[k + n - 1].val();
}
```

---

## 作者：YYZ1208 (赞：1)

# abc385g做题笔记

## 题目描述

给定 $n$ 与 $k$，求贡献为 $k$ 的排列个数模 $998244353$ 的结果。

此处排列的贡献定义为：

$n$ 个数中大于其左边的数的个数减去大于其右边的数的个数。

$n\le 2\times10^5,|k|<n$。

## 做题思路

看到这个范围，不是结论就是 dp。

考虑朴素 dp。

发现对于 $x$，小于 $x$ 的数对他没有影响，考虑从大到小加数。

令 $f_{i,j}$ 表示从大到小加完了前 $i$ 个数，贡献为 $j$ 的方案数（ $-i< j < i$ ）。

初始化为 $f_{1,0}=1$ 考虑转移：

我们假设已经把 $n,n-1...n-i+1$ 都插入了。

考虑把 $x=n-i$ 插入到序列中。

​	1、放在最左侧，则一定大于其左边的数，所以贡献会加一，即：$f_{i+1,j+1}=f_{i+1,j+1}+f_{i,j} $。

​	2、放在最右侧也是同理，即：$f_{i+1,j-1}=f_{i+1,j-1}+f_{i,j} $。

​	3、放在中间的 $i-2$ 个位置时对贡献没影响，即：$f_{i+1,j}=f_{i+1,j}+f_{i,j}\times(i-2) $。

最后答案就是 $f_{n,k}$。

但是这样是 $O(n^2)$ 的，放 at 那甚至只能过掉样例~~那这跟打表有什么区别~~。

别急，我们考虑优化一下这个 dp。

发现转移十分的单一，考虑把 $f_i$ 看成一个多项式 $\sum_{j=-i}^{i} f_{i,j}x^j$。

考虑如何从 $f_i$ 转移到 $f_{i+1}$：

发现第一种转移相当于整体右移一位，即 $f_i\times x$。

第二种同理：$f_i\times x^{-1} $。

第三种明显就是：$f_i\times(i-2)$。

所以转移式子可以写成：$f_{i+1}=f_i\times(x+x^{-1}+i-2)$。

考虑直接用 $f_1$ 表示 $f_n$：

$f_n\\=f_1\times\prod_{i=2}^n(x+x^{-1}+i-2)\\=\prod_{i=0}^{n-2}(x+x^{-1}+i)\\=\prod_{i=0}^{n-2}(x^2+x+ix)\div x^{n-1}$ 

所以求 $f_n$ 的 $x^k$ 的系数相当于求 $\prod_{i=0}^{n-2}(x^2+x+ix)$ 的 $x^{k+n-1}$ 的系数。

现在考虑求 $\prod_{i=0}^{n-2}(x^2+x+ix)$，也就是这 $n-2$ 个多项式的乘积。

~~一眼 ntt~~。

发现直接 ntt 是会达到恐怖的 $O(n^2\log n)$ 还不如暴力。

这里提供一种优化的方法：

先把二次多项式都合并成四次多项式，

先把四次多项式都合并成八次多项式……

这样的话只要合并 $\log n$ 次，

第 $i$ 次的复杂度为 $n/2^i\times(2^{i+1}\times(i+1))=2n(i+1) $。

所以总的复杂度就为 $O(\sum_{i=0}^{\log n} 2n(i+1))=O(n\log^2 n) $。

然后最后还会剩下不超过 $\log n$ 个多项式，暴力合并即可，复杂度也是 $O(n\log^2 n)$。

**实现方法**

发现如果直接存的话空间很大。

发现它每次就是选择两个长度相同且最小的合并。

所以可以维护一个栈，里面从大到小存现在没合并的多项式，每次加入一个多项式就不断往前合并。

这样的话因为最多只会剩下 $O(\log n)$ 个多项式，所以空间是 $O(n\log n)$ 的，可以过。



## Code
https://atcoder.jp/contests/abc385/submissions/61024326

---

## 作者：ddxrS_loves_zxr (赞：1)

### 题目翻译

对于一个 $(1,2,\dots,N)$ 的排列 $P=(P_1,P_2,\dots,P_N)$，定义整数 $L(P)$ 和 $R(P)$：

-   考虑 $N$ 栋从左到右的建筑，其中第 $i$ 栋建筑的高度为 $P_i$。然后 $L(P)$ 表示从最左边能看到的建筑的数量，$R(P)$ 表示从最右边能看到的建筑的数量。  
    更正式的说，$L(P)$ 为满足对于所有 $j<i$ 都有 $P_j<P_i$ 的 $i$ 的个数，$R(P)$ 为满足对于所有 $j>i$ 都有 $P_i>P_j$ 的 $i$ 的个数。

给定你整数 $N$ 和 $K$。找出满足 $L(P)-R(P)=K$ 的 $(1,2,\dots,N)$ 的排列 $P$ 的数量对 $998244353$ 取模后的值。

### 思路

首先，高度为 $N$ 的建筑会对 $L(P)$ 和 $R(P)$ 造成贡献。在 $N$ 左边的建筑只可能会对 $L(P)$ 造成贡献，在 $N$ 右边的建筑只可能会对 $R(P)$ 造成贡献。

接下来考虑 $L(P)-R(P)=K$ 的限制，可以枚举 $L(P)$，那么 $R(P)$ 也知道了。记对 $L(P)$ 或 $R(P)$ 造成贡献的建筑有 $d$ 个，那么我们就需要求出剩下 $N-d$ 栋建筑完全没造成贡献且只考虑这些建筑的方案数。

来考虑这样一种生成这 $N$ 栋建筑的方案，将建筑按照高度从大到小插入，那么第 $i$ 次插入（即高度为 $N-i+1$ 的建筑）：

- 若 $i=1$，对 $L(P)$ 和 $R(P)$ 都造成贡献。
- 若 $i=2$，放在 $N$ 的左边或右边，分别对 $L(P)$ 或 $R(P)$ 造成贡献。
- 若 $i>2$，放在最左边或最右边或者直接插到中间，分别对 $L(P)$ 或 $R(P)$ 造成贡献或者不造成贡献，其中插到中间的方案数为 $i-2$。

接下来我们就可以计算出方案了，定义 $f_{i,j}$ 表示当前是第 $i+2$ 次插入，其中 $j$ 栋建筑没造成贡献且只考虑这些建筑的方案数，那么有：

$$
f_{i,j}=f_{i-1,j}+f_{i-1,j-1}\times i
$$

我们需要的就是 $f_{n-2}$。

那么对于 $L(P)+R(P)-1=d$ 的方案数就是 $C_{d-1}^{R(P)-1}\times f_{n-2,N-d}$。

我们就可以在 $O(N^2)$ 的复杂度内解决这个问题，时间瓶颈在求解 $f$ 上。

但是，你可以发现，要求的就是第一类斯特林数行，直接套上来就行了。

时间复杂度 $O(N\log N)$。

---

## 作者：CarroT1212 (赞：0)

正好满脑子都是多项式，结果刚好来这么个 G，这下对口了。

排列问题考虑从插入元素考虑。尝试 DP。其实这里 DP 有很多种，但是未必都能优化。

> 应该有不少人试过 $dp_{i,j}$ 表示长度为 $i$ 的排列里出现过 $j$ 个前缀最大值的方案数，然后合并前后缀答案之类的。但是你不管怎么优化都需要用到几乎所有的 DP 值求答案，并且这似乎不是能把计算答案的过程分散到转移里的东西。所以这个 DP 完全没有优化空间。只能重开，至少要用来算答案的东西不能满地都是。

在序列位置上考虑值域行不通的话就在值域上考虑序列位置吧！设 $dp_{i,j}$ 为长度为 $i$ 的排列的 $L-R=j$ 时的答案。每次看成往排列里插入一个比前面 $i$ 个数都要小的数，有 $dp_{i,j}=dp_{i-1,j}(i-2)+dp_{i-1,j+1}+dp_{i-1,j-1}$。即放中间，左边和右边的情况。

为了避免负数下标可以令 $j\gets j+i-1$，现在就是 $dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-1}(i-2)+dp_{i-1,j-2}$。这么设还是 $O(n^2)$ 的，但是 $dp_{n,k+n-1}$ 就直接是答案了。

然后熟悉 OGF 的选手会发现可以设 $dp_i$ 的生成函数为 $F(i)$，$G(i)=x^2+(i-2)x+1\ (i\ge 2)$，于是转移式变成 $F(i)=F(i-1)\cdot G(i)$。那么答案就是 $\prod\limits_{i=2}^n G(i)$ 的 $k+n-1$ 次项系数。

这能做啊，直接分治乘 $G(i)$，再来个 NTT 复杂度就是 $O(n\log^2 n)$ 的了。

```cpp
ll n,k;
fps f[N<<2];
void dac(ll p,ll l,ll r) {
	if (l==r) return f[p]=l==1?fps{1}:fps{1,l-2,1},void();
	ll mid=l+r>>1;
	dac(p<<1,l,mid),dac(p<<1|1,mid+1,r);
	f[p]=f[p<<1]*f[p<<1|1];
}
void mian() {
	scanf("%lld%lld",&n,&k);
	dac(1,1,n);
	cout<<f[1][k+n-1];
}
```

---

