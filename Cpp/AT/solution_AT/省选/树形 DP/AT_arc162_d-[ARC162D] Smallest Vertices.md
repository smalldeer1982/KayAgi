# [ARC162D] Smallest Vertices

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc162/tasks/arc162_d

この問題では、根付き有向木と言った際には全ての辺が根から葉の方向に向き付けられた根付き木を指すものとします。

総和が $ N-1 $ であるような非負整数列 $ d=(d_1,d_2,\ldots,d_N) $ が与えられます。

頂点に $ 1 $ から $ N $ の番号がついた、頂点 $ 1 $ を根とする $ N $ 頂点の根付き有向木のうち、以下の条件を満たすものを**良い木**と呼びます。

- 頂点 $ i\ (1\leq\ i\ \leq\ N) $ の出次数は $ d_i $
 
さらに、良い木の頂点 $ v $ に対して、 $ f(v) $ を「頂点 $ v $ の部分木に含まれる頂点（$ v $ 含む）の頂点番号の最小値」と定め、$ f(v)=v $ を満たす頂点を**良い頂点**と呼びます。

良い木全てに対する良い頂点の個数の総和を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 500 $
- $ 0\ \leq\ d_i\ \leq\ N-1 $
- $ d_1\ \geq\ 1 $
- $ \sum_{i=1}^N\ d_i\ =\ N-1 $
- 入力される数値は全て整数
 
### Sample Explanation 1

良い木は以下の $ 2 $ 通りあります。青く塗られた頂点は良い頂点です。 !\[\](https://img.atcoder.jp/arc162/D-sample1-zFXKLnmt.png) それぞれについて良い頂点は $ 4 $ 個、 $ 3 $ 個なので答えは $ 7 $ です。

## 样例 #1

### 输入

```
4
2 0 1 0```

### 输出

```
7```

## 样例 #2

### 输入

```
10
3 1 0 0 2 0 1 2 0 0```

### 输出

```
37542```

# 题解

## 作者：EuphoricStar (赞：7)

注意到，如果给定每个点的度数 $d_i$，那么根据 Prufer 序可得，合法本质不同无根树数量为 $\frac{(n - 2)!}{\prod\limits_{i = 1}^n (d_i - 1)!}$。

考虑拆贡献，钦定一个点是好点，在这样的基础上求本质不同无根树数量。

设钦定 $u$ 为好点。那么 $u$ 子树内所有点都在 $[u, n]$ 内。注意到求无根树的式子只关心树的大小和 $(d_i - 1)!$ 的乘积，并且合法当且仅当 $\sum (d_i - 1) = n - 2$，于是考虑背包，设 $f_{i, j, k}$ 为 $[i, n]$ 中，被选的点度数和为 $j$，数量为 $k$ 的方案数。

考虑完 $u$ 子树后，把这些点全部删掉，$u$ 作为叶子再参与接下来整棵树方案数的计算即可。

时间复杂度 $O(n^3)$。

[code](https://atcoder.jp/contests/arc162/submissions/42727920)

---

## 作者：PNNNN (赞：6)

### 思路：

#### 1.
首先，这道题输入的 $d_i$ 表示的是出度，而点 $i \in [2,n]$ 在双向边的情况下的度数 $deg_i=d_i+1$，但要注意 $deg_1=d_1$。

#### 2.
如果直接通过每个点的度数构造一个 Prufer 序列，也就相当于构造一棵树，并在上面寻找好顶点不算容易，所以我们考虑每个点能有多少种满足度数要求的树能使其成为好顶点。

#### 3.
可以发现，根节点 $1$ 与 $d_i=0$ 的点(也就是叶子结点)，无论在任何满足度数要求的树上，都是好顶点。因为 $1$ 是最小的编号，而叶子结点的子树只有它自己。而它们对答案的贡献就为满足度数要求的树的数量，也就是 $\frac{(n-2)!}{\prod_{i=1}^n(deg_i-1)!}$，化简得 $\frac{d_1\times(n-2)!}{\prod_{i=1}^nd_i!}$。

### 4.
那么其余的点呢？设当前的点为 $x$，若 $x$ 要为好顶点，则它子树内的点的编号要 $\in [x+1,n]$，所以我们想到将 $x$ 子树内的部分和子树外的部分分开考虑。

先看 $x$ 子树内的部分。注意此时我们要把 $x$ 当作一个根节点，所以现在 $deg_x=d_x$。我们枚举 $k=1,2,\dots, n-x+1$，表示 $x$ 的子树内有 $k$ 个点，则这些点的 $d_i$ 的和要等于 $k-1$。那这样有多少种选择方案呢？
我们可以提前通过dp来求解。设 $dp_{i,j,k}$ 表示选择了 $j$ 个编号 $\in [i,n]$ 点，且这些点 $d_i$ 的和为 $k$ 的方案数，则可以写出这样的代码：

```cpp
dp[n+1][0][0]=1;//记得初始化 
for(int i=n;i>=1;i--){//因为状态设计，所以是倒序枚举
	for(int j=0;j<=n-i+1;j++){
		for(int k=0;k<n;k++){//d[i]的和一定会小于点数 
			dp[i][j][k]=dp[i+1][j][k]/*加上不选当前点的方案数*/;
			if(j>0&&k>=d[i])dp[i][j][k]+=dp[i+1][j-1][k-d[i]]/*加上选当前点的方案数*/;
			dp[i][j][k]%=mod;//记得取模！！！ 
		}
	}
}
```

时间复杂度为 $O(n^3)$

注意， $x$ 的子树有 $k$ 个结点的方案数是 ```dp[x+1][k-1][k-1-d[x]]``` 而不是 ```dp[x][k][k-1]```，因为这样可能会出现没有选择 $x$ 这个结点的情况。假设当前选择了 $x$ 和 $t_1,t_2,\dots,t_k-1$ 这 $k$ 个点，则 $x$ 的子树有 $k$ 个结点的方案数为 $\frac{(k-2)!}{(deg_x-2)! \prod_{i=1}^{k-1}(deg_{t_i}-1)!}\times dp_{x+1,k-1,k-1-d_x}$，化简得 $\frac{d_x(k-2)!}{d_x! \prod_{i=1}^{k-1}d_{t_i}!}\times dp_{x+1,k-1,k-1-d_x}$。
 
此时再看 $x$ 子树外的部分。注意，我们也要把 $x$ 当作一个叶子结点加入 $x$ 子树外的部分中。可以发现，此部分的方案数为 $\frac{(n-k-2+1)!}{\prod_{i\notin t}deg_{i}!}$，化简得 $\frac{d_1(n-k-1)!}{\prod_{i\notin t}d_{i}!}$。

此时，将两部分的方案数乘起来便是$x$ 的子树有 $k$ 个结点对答案的贡献了，化简可得 $\frac{d_1(n-k-1)!d_x(k-2)!}{\prod_{i=1}^nd_{i}!}\times dp_{x+1,k-1,k-1-d_x}$。发现，$\prod_{i=1}^nd_{i}!$ 可以提前预处理出来，而且这个式子只与 $x$ 与 $k$ 有关，所以只要枚举 $x$ 和 $k$ 即可，时间复杂度 $O(n^2)$。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int mod=998244353;

int n,d[505],dp[505][505][505],fac[505]={1},mul=1,ans;

inline int ksm(int base,int t){
	int res=1;
	while(t>0){
		if(t&1)res=res*base%mod;
		t>>=1,base=base*base%mod;
	}return res;
}

inline int inv(int x){return ksm(x,mod-2);}

inline int read(){
	register int x(0),t(0);
	static char ch=getchar();
	while(!isdigit(ch)){t|=(ch=='-'),ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48),ch=getchar();}
	return t?-x:x;
}

signed main(){
	for(int i=1;i<=500;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	n=read();
	for(int i=1;i<=n;i++){
		d[i]=read(),mul=mul*fac[d[i]]%mod;
	}
	dp[n+1][0][0]=1;//记得初始化 
	for(int i=n;i>=1;i--){//因为状态设计，所以是倒序枚举
		for(int j=0;j<=n-i+1;j++){
			for(int k=0;k<n;k++){//d[i]的和一定会小于点数 
				dp[i][j][k]=dp[i+1][j][k]/*加上不选当前点的方案数*/;
				if(j>0&&k>=d[i])dp[i][j][k]+=dp[i+1][j-1][k-d[i]]/*加上选当前点的方案数*/;
				dp[i][j][k]%=mod;//记得取模！！！ 
			}
		}
	}
	for(int x=1;x<=n;x++){
		if(x==1||!d[x]){
			(ans+=(fac[n-2]*d[1]%mod)*inv(mul)%mod)%=mod;
		}else{
			for(int k=1;k<=n-x+1;k++){
				(ans+=(fac[n-k-1]*fac[k-2]%mod*d[1]*d[x]%mod)*inv(mul)%mod*dp[x+1][k-1][k-1-d[x]]%mod)%=mod;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

完结撒花！有问题可以私信我

---

## 作者：HHH6666666666 (赞：2)

前置知识：[prufer 序列](https://oi-wiki.org/graph/prufer/)。

根据 prufer 序列，任意一个长为 $n-2$，元素值域为 $[1,n]$ 的整数序列均可与一棵无根树一一对应，同时这棵树中每个点的度数为其在序列中的出现次数 $+1$。因为对于根节点（任意指定），显然出现次数为儿子个数减 $1$。剩余节点的出现次数为儿子的个数，其度数则还要加上父边。

因此，满足题中度数限制的树有 $\binom{n-2}{d_1-1,d_2,d_3,...,d_n}$ 棵，即长为 $n-2$ 的序列中每个数分别出现了 $d$ 次（根节点为 $d-1$）。

直接看整棵树显然不方便计数，拆贡献统计每个点在多少棵树中为好点。

点的贡献有两种情况：

1. 该点为根节点 $1$ 或叶节点，则任何情况下都是好点。

2. 该点非根非叶，则为好点当且仅当子树内所有点编号均大于它。

假如对于点 $x$，我们选取了一个若干个点 $y_1,y_2,...y_{m-1}$ 满足 $\forall y_i > x$ 且 $\sum d_{y_i}+d_{x_i}=m-1$，则 $x$ 与这些点共可以组成 $\binom{m-2}{d_{y_1},...,d_{y_{m-1},d_x-1}}$ 棵子树。注意 $x$ 的度数要减 $1$，因为将其看作子树内的根节点时其度数会从整棵树来看的 $d_x+1$ 变成 $d_x$（去掉了父边）。

还要考虑 $x$ 以外的部分。由于已经确定了 $x$ 的子树，我们将子树内节点去掉，把 $x$ 视作叶节点拼到原树上即可。令子树外的点为 $o_1,o_2,...o_{n-m}$，这部分贡献就是 $\binom{n-m-1}{d_{o_1},...,d_{o_m}}$，$x$ 为叶子节点故 $d=0$（注意式子中未考虑根节点度数减 $1$，为表达方便先忽略这个问题）。

两式相乘：

$$

\begin{aligned}

&\binom{m-2}{d_{y_1},...,d_{y_{m-1},d_x-1}} \times \binom{n-m-1}{d_{o_1},...,d_{o_m}}

\\=&\frac{(m-2)!}{\prod d_{y_i}! \times (d_x-1)!} \times \frac{(n-m-1)!}{\prod d_{o_i}!}

\\=&\frac{(m-2)! \times (n-m-1)!}{\prod\limits_{i=1}^{n}d_i! \times \frac{(d_x-1)!}{d_x!}}

\end{aligned}

$$

对于每个点求出只选编号比它大的点的所有子树大小（也就是每个 $m$）的方案数即可。设计三位状态分别记录扫到了哪个点、选了几个点以及当前度数和，状态数 $O(n^3)$，转移 $O(1)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define i1 __int128
#define pii pair<int, int>
#define pll pair<ll, ll>
#define mp make_pair
#define fi first
#define se second
#define ep emplace
#define eb emplace_back
#define all(v) v.begin(), v.end()

using namespace std;

const int MAXN = 510;
const int MOD = 998244353;

int n;
int d[MAXN];
ll f[MAXN][MAXN], g[MAXN][MAXN];
ll fac[MAXN];

#define bet(x, y, z) (((x) <= (y)) && ((y) <= (z)))
#define add(x, y) x += (y) % MOD, x %= MOD

ll qpow(ll x, int y) {
    ll res = 1; x %= MOD;
    while (y) {
        if (y & 1) res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}
ll inv(ll x) { return qpow(x, MOD - 2); }
ll calc(ll x) {
    return fac[x - 2] * fac[n - x - 1] % MOD;
}
signed main() {
	ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    fac[0] = 1;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> d[i], fac[i] = fac[i - 1] * i % MOD;
    --d[1];
    ll prod = 1;
    for (int i = 1; i <= n; ++i) prod *= fac[d[i]], prod %= MOD;
    f[0][0] = 1;
    ll ans = 0;
    for (int i = n; i; --i) {
        ll res = 0;
        memset(g, 0, sizeof g);
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= n; ++k) {
                if (!f[j][k]) continue;
                int jj = j + 1, kk = k + d[i];
                add(g[j][k], f[j][k]);
                add(g[jj][kk], f[j][k]);
                if (d[i] && i > 1) 
                    if (jj - kk == 1 && jj < n) add(res, calc(jj) * f[j][k] % MOD);
            }
        }
        swap(f, g);
        if (d[i]) add(ans, res * inv(prod) % MOD * fac[d[i]] % MOD * inv(fac[d[i] - 1]) % MOD);
    }
    ll t = fac[n - 2] * inv(prod) % MOD;
    for (int i = 2; i <= n; ++i)
        if (!d[i]) add(ans, t);
    add(ans, t);
    cout << ans << endl;
    return 0;
}

```

---

## 作者：TernaryTree (赞：2)

学不会计数。/ng

---

一个结论：对于一棵 $n$ 点的无根树，钦定每个结点度数为 $d_i$，则这样的树个数为

$$\dfrac{(n-2)!}{\prod\limits_{i=1}^n (d_i-1)!}$$

证明：Prufer 序列。

---

首先把答案拆到结点算贡献。

对于叶子结点和根，一定满足条件。此时根据结论，该点的答案为全局树的个数。又非根结点一定有且仅有一条入边，所以全局树数为

$$\dfrac{(n-2)!}{(d_1-1)!\prod\limits_{i=2}^nd_i!}$$

对于非叶子结点 $u$，我们在 $[u+1,n]$ 中选取若干个结点再并上 $u$ 构成集合 $S$，表示 $u$ 及其子树内的结点。显然 $S$ 内的结点要构成一棵完整的子树，所以要求满足

$$\sum_{i\in S}d_i=|S|-1$$

此时，$u$ 子树内的方案数为

$$\dfrac{(|S|-2)!}{(d_u-1)!\prod\limits_{i\in S,i\neq u}d_i!}$$

我们还要考虑 $u$ 子树外的贡献，这里要把 $u$ 看做一个叶子结点，所以分母中 $u$ 的度数不会计入，而分子中结点个数会多 $1$。

$$\dfrac{(n-|S|+1-2)!}{(d_1-1)!\prod\limits_{i\not\in S,i\neq 1} d_i!}$$

将上面两个式子相乘，再把 $\dfrac{1}{(d_1-1)!(d_u-1)!}$ 化成 $\dfrac{d_1d_u}{d_1!d_u!}$，得到

$$\dfrac{(|S|-2)!(n-|S|-1)!d_1d_u}{\prod\limits_{i=1}^n d_i}$$

这样这个式子里面的变量只有 $|S|,u$。

设计一个 dp 计算方案数：$f_{i,j,k}$ 表示在 $[i,n]$ 中选了 $j$ 个点，这些点的 $d_i$ 之和为 $k$ 的方案数。可以简单 $\Theta(1)$ 转移，复杂度 $\Theta(n^3)$。

然后枚举 $u$ 和 $|S|$，再通过 $f$ 计算出 $S$ 的方案数，与上面那个式子相乘即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 5e2 + 10;
const int mod = 998244353;

int n, tot = 1, inv = 1, ans;
int d[maxn];
int f[maxn][maxn][maxn];
int fac[maxn], ifac[maxn];

int power(int a, int b) {
	int t = 1;
	while (b) {
		if (b & 1) t = t * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return t;
}

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> d[i];
	fac[0] = 1;
	for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[maxn - 1] = power(fac[maxn - 1], mod - 2);
	for (int i = maxn - 2; ~i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
	tot = fac[n - 2];
	for (int i = 1; i <= n; i++) tot = tot * ifac[i == 1 ? d[i] - 1 : d[i]] % mod;
	f[n + 1][0][0] = 1;
	for (int i = n; i; i--) {
		for (int j = 0; j <= n - i + 1; j++) {
			for (int k = 0; k < n; k++) {
				f[i][j][k] = (f[i + 1][j][k] + (j && k >= d[i] ? f[i + 1][j - 1][k - d[i]] : 0)) % mod;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (i == 1 || !d[i]) {
			ans = (ans + tot) % mod;
			continue;
		}
		for (int j = d[i] + 1; j <= n - i + 1; j++) (ans += d[i] * fac[j - 2] % mod * fac[n - j - 1] % mod * tot % mod * ifac[n - 2] % mod * f[i + 1][j - 1][j - d[i] - 1] % mod) %= mod;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：0)

为了这个题才会的 Prufer，没救了……

先考虑求出好树的个数，如果你会 Prufer 就不难发现为 ${n-2\choose d_1-1,d_2,d_3\dots d_n}=\frac{d_1(n-2)!}{\prod\limits_{i=1}^n{d_i!}}$。

根和叶子始终是好的，直接加上，现在对于每一个节点求其贡献。

假设我们要求节点 $u$ 的贡献，先想想给定其子树的点集 $T$ 时怎么做。

方案自然是 $\frac {d_u(|T|-2)!}{\prod\limits_{x\in T}d_x!}$，然后还要算子树外的节点，此时我们直接把 $d_u$ 子树当成一个点算 Prufer，可以得到是 $\frac {d_1(n-|T|-1)!}{\prod\limits_{x\not\in T}d_x!}$。

把两部分乘起来，变成了 $\frac{d_1d_u(|T|-2)!(n-|T|-1)!}{\prod\limits_{i=1}^nd_i!}$，只与 $|T|$ 和 $u$ 有关。

直接 DP 就行了，记得要从后往前 DP，因为子树内只能放编号大于当前点的。

注意 $|T|-1=\sum\limits_{x\in T} d_x$ 的条件，不然你无法构成一棵树。

代码中将序列反转了。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=510;
const int mod=998244353;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint operator-() const { return modint(norm(-val)); }
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
	friend std::ostream& operator<<(std::ostream& os, const modint a) { return os << a.val; }
}dp[N][N],w,frac[N],tmp,res,T;
int n,d[N];

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	dp[0][0]=1;cin>>n;for(int i=n;i;--i,w=d[n]) cin>>d[i];
	frac[0]=1;for(int i=1;i<=n;++i) frac[i]=frac[i-1]*i;
	tmp=w*frac[n-2];T=1;for(int i=1;i<=n;++i) T*=frac[d[i]].inv();
	for(int i=1;i<=n;++i) if(!d[i]||i==n) res+=tmp*T;
	for(int i=1;i<n;++i){
		for(int j=d[i];j<i;++j){
			int x=j+1,y=j-d[i];
			res+=frac[x-2]*frac[n-x-1]*T*d[i]*w*dp[j][y];
		}
		for(int j=i-1;~j;--j){
			for(int k=0;k<=n;++k){
				if(!dp[j][k].val) continue;
				dp[j+1][k+d[i]]+=dp[j][k];
			}
		}
	}
	cout<<res<<endl;
	return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

根据 prufer 序列，满足 $i$ 的度数为 $d_i$ 的无根树的个数为 $\begin{pmatrix}
 n-2\\
d_1-1,...,d_n-1
\end{pmatrix}$，带入问题，得到 $\begin{pmatrix}
 n-2\\
d_1-1,d_2,...,d_n
\end{pmatrix} = \dfrac{d_1(n-2)!}{\prod d_i !}$。

考虑把贡献拆到节点上面，那么，钦定 $u$ 为好节点，那么 $u$ 的后代节点必须是比它标号大的节点。

我们设从比它标号大的节点选出了 $S$ 作为 $u$ 的子树。

那么 $|S| = \sum\limits_{u \in S} d_u + 1$，子树内的方案数就是 $\dfrac{d_u(|S|-2)!}{\prod\limits_{v \in S} d_v}$。

其余部分的方案数就是 $\dfrac{d_1(n-|S|-1)!}{\prod\limits_{v \notin S} d_v}$。

相乘得到点 $u$ 的方案数为 $\dfrac{d_1d_u(n-|S|-1)!(|S|-2)!}{\prod d_v}$。

考虑枚举 $|S|$，$u$，考虑 dp 出 $S$ 的方案数，设 $f_{i,j,k}$ 代表从 $[i,n]$ 中选出 $j$ 个并且 $\sum d_i = k$ 的方案数。

时间 $O(n^3)$。

---

## 作者：冷却心 (赞：0)

计数好题。参考了 zlt 和三叉树的题解。

先考虑一个 naive 的问题，根据给定的 $d_i$ 求出好树个数。根据 Prufer 序列可以简单做出，个数为：

$$\binom{n-2}{d_1-1,d_2,d_3,\cdots,d_n}=\frac{d_1(n-2)!}{\prod d_i!}.$$

这里要注意 $d_i$ 并非点 $i$ 的度数，当 $i\neq1$ 的是度数减一。

对于一颗好树，显然根结点和叶子结点必定好结点，直接加上总方案数。然后其他情况考虑拆贡献，枚举点 $u$，我们钦定 $u$ 是好结点，那么 $u$ 只能从比他大的结点中选择子树。我们设选出了子树 $T$。显然这个子树需要满足 $\sum_{i\in T} d_i= |T| -1$。那么子树内的方案数根据我们上面的讨论一共是：

$$\frac{d_u(|T| - 2)!}{\prod_{i\in T} d_i!}.$$

其他结点的方案数就正常算，但是去掉子树 $T$，只保留 $u$ 作为一个叶子，方案有：

$$\frac{d_1(n-|T|+1-2)!}{\prod_{i\notin T}d_i}=\frac{d_1(n-|T|-1)!}{\prod_{i\notin T}d_i}.$$

把这两个式子相乘得到总方案数：

$$\frac{d_1d_u(n-|T|-1)!(|T|-2)!}{\prod d_i}.$$

我们发现这个式子很清新，只和 $u$ 以及 $|T|$ 有关。于是我们枚举 $u$ 和 $|T|$，然后求出满足 $\sum d_i=|T|-1$ 的 $T$ 个数然后乘一乘加一加就做完了。

然后考虑怎么求出满足条件的 $T$ 的个数，这个就是一个背包，我们定义 $f_{i,j,k}$ 表示从 $[i,n]$ 中选出了 $j$ 个点 $d$ 之和为 $k$ 的方案数，然后随便 dp 一下就好了。做完了。

时间复杂度 $O(n^3)$，瓶颈在于 dp。

[https://atcoder.jp/contests/arc162/submissions/62950881](https://atcoder.jp/contests/arc162/submissions/62950881)。

---

## 作者：伊地知虹夏 (赞：0)


由 Prufer 序列的性质结合可重集全排列公式知好树的方案数为：

$$T = d_1 (n-2)! \times(\prod_{i = 1}^{n} (d_i) !)^{-1}$$

考虑计算贡献。

首先注意到 $1$ 和叶子节点都是好点，则方案数为 $T$。

我们钦定非根非叶子节点 $x$ 为好点，计算能使 $x$ 为好点的树方案数。

先定下子树的形态，从 $[x+1,n]$ 中选出 $k - 1$ 个节点，由于子树也可使用 Prufer 序列的性质，则方案数为：

$$T_1 = d_x (k-2)! \times(\prod_{j = 1}^{k} (d_{p(j)}) !)^{-1}$$

其中 $p(i)$ 为选出的第 $i$ 个点的编号，规定 $p(k) = x$。

再考虑子树外的节点的形态，如果将子树缩成一个点，则子树外同样使用公式知方案数为：

$$T_2 = d_1 (n-k+1-2)! \times(\prod_{j \neq p(i)}^{n} (d_j) !)^{-1}$$

我们发现，最后的方案 $T_1 \times T_2$ 和 $p$ 的具体选取方案没有关系，只和方案数 $f_x$，子树大小 $k$ 有关。

考虑设计状态 $f_{i,j,k}$ 表示在 $[i,n]$ 中选取 $j$ 个点，其 $d$ 之和为 $k$ 的方案数，转移是 $\Theta(1)$ 的，时间复杂度 $\Theta(n^3)$。

最后枚举 $x$ 和 $k$ 按公式求答案即可，[代码](https://www.luogu.com.cn/paste/nr7ltp1x)。

---

