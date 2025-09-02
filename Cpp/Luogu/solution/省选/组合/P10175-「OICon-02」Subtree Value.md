# 「OICon-02」Subtree Value

## 题目描述

给出一棵 $n$ 个节点的树，每个点有点权 $a_v$。定义一棵树的一个子连通块为一个树中点的**非空集合**，满足这些点在树上形成一个连通块。定义子连通块 $S$ 的权值为 $\prod_{v\in S}(a_v+|S|)$。求所有子连通块的权值之和对 $U^V$ 取模。

## 说明/提示

### 样例解释

对于样例 $1$，以下子连通块的权值分别是：

* $\{1\}$：$(1+1)=2$；
* $\{2\}$：$(2+1)=3$；
* $\{3\}$：$(3+1)=4$；
* $\{1,2\}$：$(1+2)\times(2+2)=12$；
* $\{1,3\}$：$(1+2)\times(3+2)=15$；
* $\{1,2,3\}$：$(1+3)\times(2+3)\times(3+3)=120$。

总和为 $2+3+4+12+15+120=156$，对 $10^6$ 取模后为 $156$。

### 数据范围

**本题采用捆绑测试。**

| $\text{Subtask}$ | 特殊性质 | $\text{Score}$ |
|:--:|:--:|:--:|
| $1$ | $n\leq10$ | $5$ |
| $2$ | $n\leq150$ | $8$ |
| $3$ | $n\leq500$ | $11$ |
| $4$ | $U=2,V=1$ | $7$ |
| $5$ | $V=1$ | $23$ |
| $6$ | $U\mid a_i$ | $23$ |
| $7$ | 无特殊限制 | $23$ |

对于 $100\%$ 的数据：$1\leq n\leq2000$，$1\leq f_i<i$，$2\leq U\leq10$，$1\leq V\leq6$，$0\leq a_i< U^V$。

## 样例 #1

### 输入

```
3 10 6
1 1
1 2 3```

### 输出

```
156```

## 样例 #2

### 输入

```
11 4 6
1 1 2 3 4 4 4 5 6 7
325 190 400 325 380 165 334 400 80 171 340```

### 输出

```
678```

# 题解

## 作者：zhouyuhang (赞：13)

记 $U^V$ 标准分解为 $\prod_{i=1}^k p_i^{\alpha_i}$，那我们只需对每个 $i$ 求出答案模 $p_i^{\alpha_i}$ 的值，最后做一遍 CRT 合并就行了。

将每个连通块 $S$ 的权值看作一个多项式 $F_S(x)=\prod_{v\in S}(a_v+x)$，则答案为 $\sum_{i=1}^n\sum_{|S|=i}F_S(i)$。接下来我们注意到这样一个结论：对整系数多项式 $F(x)$ 而言，$F(x)\equiv F(x)\bmod x^{\underline {pk}}\pmod {p^k}$。这就意味着 $F(S)$ 对 $p^k$ 取模后变成了一个至多 $pk-1$ 次的多项式。那么我们直接将 $1\sim pk$ 代入 $x$ 做 $O(n^2)$ dp，最后拉插回来即可。

总复杂度 $O(n^2\sum_{i=1}^kp_i\alpha_i)$，理论上比标算优秀一些。

---

## 作者：BreakPlus (赞：4)

验题人题解。

+ $\mathcal{O}(n^3)$ 做法（24 分）：

枚举 $|S|$，然后我们知道了每一个 $a_i+|S|$，暴力跑一遍 $\mathcal{O}(n^2)$ 的树上背包即可。设 $f_{i,j}$ 为以 $i$ 为根的子树选取了大小为 $j$ 的连通块，每种方案 $\prod(a_i+|S|)$ 的总和，易转移。

+ $\mathcal{O}(n^2UV^2)$ 做法（100 分）：

发现每次枚举 $|S|$ 其实制造了浪费，又有模数为 $U^V$ 的性质没有使用。

$\prod(a_i+|S|)$ 是一个乘积的形式，而 $U^V$ 也是 $V$ 个 $U$ 乘起来的形式。若有 $V$ 个 $(a_i+|S|)$ 都含有因子 $U$，则这个式子模 $U^V$ 就是 $0$。

好像只寄希望于它变成 $0$ 并没有什么用。

继续尝试，为了让每个式子里出现 $U$，同时联想到分配律展开的 trick，我们可以将乘积中的每个数写成除以 $U$ 的带余除法形式：令 $a_i+|S| = Ux+y \ (0 \le y < U)$。

我们惊喜地发现，一堆 $(Ux+y)$ 的乘积看成每个括号中选取一项乘起来再加和（分配律）的形式后，若 $Ux$ 的选取个数不少于 $V$ 个，那么整个这一项模 $U^V$ 就变成 $0$ 了。

为了方便实现，由于 $a_i$ 已经确定，我们不必去拆 $a_i$，而只把 $|S|$ 写成 $Ux+y$ 的形式，则 $\prod (a_i+|S|) = \prod (Ux + (y+a_i))$。

$y$ 的取值范围是很小的，启发我们直接枚举 $y$，然后 DP 时记录选取 $Ux$ 的次数（最多 $V-1$ 次）。而 $Ux$ 具体是多少，我们可以最后再计算，它对整个 DP 过程是不影响的！

此时我们就不需要 24 分做法中的枚举 $|S|$，而是枚举 $|S| \mod U$ 再 DP。
设 $f_{i,j,y,k}$ 表示以 $i$ 为根，选取 $j$ 个点的连通块，枚举的 $|S| \mod U = y$，选取 $Ux$ 的个数为 $k(k<V)$，树上背包转移它。

DP 完后再枚举 $|S|$ 具体的值，此时 $|S| = Ux+y$ 中 $x,y$ 的具体值已经确定，直接访问 $f$ 数组加和计算即可。

```cpp
vector<ll>E[2005];
ll n,U,V,Mod,a[2005],p[2005],sz[2005],I; ll f[2001][2001][7], tmp[2001][7];
void dfs(ll x){
	f[x][1][0] = (a[x] + I) % Mod;
	f[x][1][1] = 1;
	sz[x]=1;
	for(auto y: E[x]){
		dfs(y); 
		memset(tmp,0,sizeof(tmp));
		for(ll j=0;j<V;j++){
			for(ll k=1;k<=sz[x];k++){
				for(ll l=0;j+l<V;l++){
					for(ll k2=0; k2<=sz[y]; k2++)
					tmp[k+k2][j+l] += f[x][k][j] * f[y][k2][l];
				}
			}
		}
		sz[x] += sz[y];
		for(ll k=1;k<=sz[x];k++) 
			for(ll j=0;j<V;j++) f[x][k][j] = tmp[k][j] % Mod;
		 
	}
	f[x][0][0] = 1;
}
void solve(){
	n=read(), U=read(),V=read(), Mod=1;
	for(ll i=1;i<=V;i++) Mod*=U;
	for(ll i=2;i<=n;i++) p[i]=read(), E[p[i]].emplace_back(i);
	for(ll i=1;i<=n;i++) a[i]=read();
	ll ans = 0;
	for(I=0;I<U;I++){
		memset(f,0,sizeof(f));
		dfs(1);
		for(ll x=1;x<=n;x++){
			for(ll i=I+((I==0)?U:0);i<=sz[x];i+=U){
				ll p=i/U*U, w=1;
				for(ll j=0;j<V;j++){
					ans = (ans + f[x][i][j] * w);
					w = w * p % Mod;
				}
			}
			ans %= Mod;
		}
	}
	printf("%lld\n", ans);
}
```

---

## 作者：thomaswmy (赞：2)

<https://www.luogu.com.cn/problem/P10175>

有人赛时会 6 个 Subtask，但是怎么也不会正解，怎么回事呢？

出题人认为这是套路题。

题意：

给出一棵树，求 $\sum_{S|S\text{为树中的连通块}} \prod_{a_i\in S}(a_i+|S|) \bmod U^V$。

首先考虑一个三次方的 dp，设 $dp_{i,j,k}$ 表示在 $i$ 的子树内，强制钦定连通块大小为 $j$，当前填了 $k$ 个数的乘积。注意到 $k\leq |subtree_i|$，所以可以使用树上背包技巧，复杂度三次方。

第六个 Subtask 对正解有启发价值。当 $U|a_i$ 时，将 $\prod(a_i+|S|)$ 展开，即对于联通块里的每一个 $i$，选 $a_i$ 与 $|S|$ 之一的乘积之和。又因为 $a_i$ 可以表示为 $U\times r_i$。所以只能取最多 $V-1$ 项 $a_i$，否则乘积为 $U^V$ 的倍数。还是设 $dp_{i,j,k}$ 表示在 $i$ 的子树内，当前联通块大小为 $j$，取了 $k$ 个 $a_i$ 的乘积之和。转移相似，答案为 $\sum_{i,j,k}dp_{i,j,k}\times j^{j-k}$。复杂度 $O(n^2V^2)$。

正解肯定是把式子拆开，但我场上一直在想把 $a_i$ 拆开/fn

设 $|S|=KU+r$，则所求为 $\prod(a_i+KU+r)=\prod((a_i+r)+KU)$。所以枚举 $r$，相似地，设 $dp_{i,j,k}$ 表示在 $i$ 的子树内，当前联通块大小为 $j$，取了 $k$ 个 $KU$ 的乘积之和。转移及求答案都相似，复杂度 $O(n^2UV^2)$。

实现时注意合并时可以一起取模，否则应该会被卡常，加上会快 10 倍。

---

## 作者：Nelofus (赞：1)

首先我们有两个树形 DP 做法，让每个点权值为 $a_u+x$，子连通块的权值是点权值的乘积，令 $F_{u,k}$ 为以 $u$ 为根的大小为 $k$ 的子连通块权值之和

$$
F_{u,k}\leftarrow \sum_{i+j=k}F_{u,i}F_{v,j}
$$

查询答案的时候查询 $\sum_{u=1}^{n}\sum_{k=1}^{n}F_{u,k}(k)$ 即可。不知道复杂度是 $\mathcal O(n^4)$ 还是 $\mathcal O(n^3)$。

然后是第二个做法，枚举 $s=1,2,3,\cdots, n$，令每个点权值为 $a_u+j$，子连通块的权值是点权值的乘积，令 $f_{u,k}$ 为以 $u$ 为根的大小为 $k$ 的子连通块权值之和。

$$
f_{u,k}\leftarrow \sum_{i+j=k}f_{u,i}f_{v,j}
$$

每次可以令答案加上 $\sum_{u=1}^{n}f_{u,s}$。显然这是 $\mathcal O(n^3)$ 的。

考虑利用上模数为 $U^V$ 的性质，这就是说，子连通块大小 $\operatorname{siz}(u)$ 是 $U$ 的倍数，那么没有必要维护次数 $>V$ 的项。

对于一般的 $x$，我们将其写成 $x=kU+s$，不难注意到本质不同的 $s$ 只有 $U$ 种。

我们把第一个做法和第二个做法拼起来，对每个 $s=0,1,\cdots, U-1$ 做一次，令每个点权值是 $a_u+s+x$，这样询问 $F(kU)$ 的时候就相当于询问了原先的 $F(kU+s)$。我们的询问总是 $U$ 的倍数，所以只用保留次数 $<V$ 的项。

剩下的部分还是一样，令 $F_{u,k}$ 为以 $u$ 为根的大小为 $k$ 的子连通块权值之和

$$
F_{u,k}\leftarrow \sum_{i+j=k}F_{u,i}F_{v,j}
$$

询问 $\sum_{u=1}^{n}\sum_{k,kU\le n}F_{u,kU+s}(kU)$ 即可。

时间复杂度 $\mathcal O(n^2UV^2)$。

```cpp
// 哇，还要卡常
// Code by Heratino & Nelofus
#include <bits/stdc++.h>
using i64 = long long;

//{{{
template<typename T>
inline void chkmin(T &a, const T &b) {if (a > b)	a = b;}
template<typename T>
inline void chkmax(T &a, const T &b) {if (a < b)	a = b;}
//}}}

int mod;
inline int fpow(int x, int k) {
	int res = 1;
	for (; k; k >>= 1, x = 1ll * x * x)
		if (k & 1)
			res = 1ll * res * x;
	return res;
}
inline int Add(const int &x, const int &y) {return x + y >= mod ? x + y - mod : x + y;}
inline int Mul(const int &x, const int &y) {return 1ll * x * y % mod;}
inline void AddTo(int &x, const int &y) {x = Add(x, y);}
inline void MulTo(int &x, const int &y) {x = Mul(x, y);}
template<typename... Ts>
inline int Add(Ts... args) {
	int __len = sizeof...(args);
	int b[__len] = {args...};
	int ans = 0;
	for (int i = 0; i < __len; i++)	AddTo(ans, b[i]);
	return ans;
}
template<typename... Ts>
inline int Mul(Ts... args) {
	int __len = sizeof...(args);
	int b[__len] = {args...};
	int ans = 1;
	for (int i = 0; i < __len; i++)	MulTo(ans, b[i]);
	return ans;
}

constexpr int N = 2e3 + 10;
constexpr int M = 6;
int n, U, V;
int f[N], a[N];
int siz[N];
int F[N][N][M];
__int128 G[N][M];
i64 tm[M];
int main() {
#ifdef HeratinoNelofus
	freopen("input.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> U >> V;
	mod = fpow(U, V);
	for (int i = 2; i <= n; i++)
		std::cin >> f[i];
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	for (int i = 1; i <= n; i++)
		a[i] %= mod;

	int ans = 0;
	for (int s = 0; s < U; s++) {
		memset(F, 0, sizeof(F));

		for (int i = 1; i <= n; i++)
			siz[i] = 1, F[i][0][0] = 1, F[i][1][0] = Add(a[i], s), F[i][1][1] = 1;

		for (int v = n; v >= 2; v--) {
			int u = f[v];
			for (int i = 0; i <= siz[u] + siz[v]; i++)
				for (int j = 0; j < V; j++)
					G[i][j] = 0;
			// 卷积
			// u 至少要选一个点，不要把下面的继承了
			for (int i = 1; i <= siz[u]; i++)
				for (int j = 0; j <= siz[v]; j++) {
					memset(tm, 0, sizeof(tm));
					for (int k1 = 0; k1 < V; k1++)
						for (int k2 = 0; k1 + k2 < V; k2++)
							tm[k1 + k2] += 1ll * F[u][i][k1] * F[v][j][k2];
					for (int k = 0; k < V; k++)
						G[i + j][k] += tm[k];
				}
			for (int i = 1; i <= siz[u] + siz[v]; i++)
				for (int k = 0; k < V; k++)
					F[u][i][k] = G[i][k] % mod;
			siz[u] += siz[v];
		}
		for (int k = 0; k * U + s <= n; k++) {
			if (s == 0 && k == 0)
				continue;
			__int128 tmp = 0;
			for (int p = 1; p <= n; p++) {
				__int128 t = 1;
				for (int j = 0; j < V; j++) {
					tmp += F[p][k * U + s][j] * t;
					t *= k * U;
				}
			}
			AddTo(ans, tmp % mod);
		}
	}
	std::cout << ans << '\n';
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

考虑 $f(x,S) = \prod_{u \in S} (x+a_u)$，它是一个关于 $x$ 的 $|S|$ 次多项式。

我们试图对于所有 $|S|=k$ 的连通块，求出 $g(x)$ 为对应 $f(x,S)$ 的和，这样带入计算 $g(|S|)$ 即可。

注意模数很小，将 $|S|$ 写成 $kU+r$ 的形式，则 $f(x,S) = \prod_{u \in S} (kU+r+a_u) = h(kU,S)$，其中 $h(x,S) = \prod_{u \in S} (x+r+a_u)$。

注意我们只需要知道 $h$ 的 $0$ 到 $V-1$ 次项的系数即可。$r$ 只有 $U$ 种取值，所以可以记录所有 $U$ 种多项式。

因此设计树形背包 $dp_{u,k,r}$ 表示以 $u$ 为根的大小为 $k$ 的连通块，以 $r$ 为偏移量的多项式的和。

考虑复杂度。注意偏移量这一维是独立的，可以最后乘上 $U$；单次多项式合并是 $O(V^2)$ 的，所以总复杂度为 $O(n^2UV^2)$。

模拟赛时候写了一个泰勒展开的方法，和它差不多，但是难理解一些。

这玩意是会被卡常的，要把取模放到循环的外面，这样常数小。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+20;
int n,U,V,MOD,a[MAXN],sze[MAXN],fa;
struct POLY {
	ll f[6];
	ll g(ll x) {
		ll ans=0;
		roff(i,V-1,0) ans=(ans*x+f[i])%MOD;
		return ans;
	}
};
ll dp[MAXN][MAXN][6];
vector<int> G[MAXN];
POLY sum[MAXN];
void dfs(int u,int r) {
	ffor(i,1,sze[u]) ffor(j,0,V-1) dp[u][i][j]=0;
	sze[u]=1;
	dp[u][0][0]=1,dp[u][1][0]=r+a[u],dp[u][1][1]=1;
	for(auto v:G[u]) {
		dfs(v,r);
		roff(i,sze[u]+sze[v],1) {
			ffor(j,1,min(i-1,sze[v])) 
				ffor(t,0,V-1) ffor(p,0,V-1-t) dp[u][i][t+p]=(dp[u][i][t+p]+dp[u][i-j][t]*dp[v][j][p]);	
			ffor(t,0,V-1) dp[u][i][t]%=MOD;
		}
		sze[u]+=sze[v];
	}
	ffor(i,1,n) if(i%U==r) ffor(j,0,V-1) sum[i].f[j]=(sum[i].f[j]+dp[u][i][j])%MOD;
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>U>>V,MOD=pow(U,V);
	ffor(i,2,n) {
		cin>>fa;
		G[fa].push_back(i);
	}
	ffor(i,1,n) cin>>a[i];
	ffor(r,0,U-1) dfs(1,r);
	int ans=0;
	ffor(i,1,n) ans=(ans+sum[i].g(i-i%U))%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

