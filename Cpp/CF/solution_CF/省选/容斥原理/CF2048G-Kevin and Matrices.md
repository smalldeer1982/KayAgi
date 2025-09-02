# Kevin and Matrices

## 题目描述

Kevin has been transported to Sacred Heart Hospital, which contains all the $  n \times m  $ matrices with integer values in the range $  [1,v]  $ .

Now, Kevin wants to befriend some matrices, but he is willing to befriend a matrix $  a  $ if and only if the following condition is satisfied:

 $ $$$ \min_{1\le i\le n}\left(\max_{1\le j\le m}a_{i,j}\right)\le\max_{1\le j\le m}\left(\min_{1\le i\le n}a_{i,j}\right).  $ $ </p><p>Please count how many matrices in Sacred Heart Hospital can be friends with Kevin.</p><p>Since Kevin is very friendly, there could be many matrices that meet this condition. Therefore, you only need to output the result modulo  $ 998\\,244\\,353$$$.

## 说明/提示

In the first test case, besides the matrices $  a=\begin{bmatrix}1&2\\2&1\end{bmatrix}  $ and $  a=\begin{bmatrix}2&1\\1&2\end{bmatrix}  $ , which do not satisfy the condition, the remaining $  2^{2 \cdot 2} - 2 = 14  $ matrices can all be friends with Kevin.

## 样例 #1

### 输入

```
3
2 2 2
2 3 4
11 45 14```

### 输出

```
14
2824
883799966```

# 题解

## 作者：251Sec (赞：8)

没打这场，赛后做了下 EFG，E 用时 1h，F 用时 5min（仅口胡），G 用时 2h，怎么回事呢？

---

对题面进行翻译，发现一个矩阵合法当且仅当 **存在至少一个位置，既是所在行最大值又是所在列最小值**，称这样的位置是好的。

注意到如果存在两个好的位置 $(x_1,y_1),(x_2,y_2)$，我们可以得到 $(x_1,y_2)$ 和 $(x_2,y_1)$ 也是好的，且所有好的位置相等。证明只需要注意到 $(x_1,y_1) \le (x_1,y_2) \le (x_2,y_2) \le (x_1,y_2) \le (x_1,y_1)$。

那么这说明我们可以使用两个集合 $S$ 和 $T$ 描述所有好的位置为 $\{(x,y)|x \in S \land y \in T\}$，枚举 $S$ 和 $T$ 的大小，钦定里面的元素好，不保证外面的元素不好，作容斥，得到：

$$
\sum_{x=1}^n \sum_{y=1}^m\sum_{c=1}^V (-1)^{x+y}\binom{n}{x}\binom{m}{y}c^{x(m-y)}(V-c+1)^{y(n-x)}V^{(n-x)(m-y)}
$$

直接计算倒闭了，但是我们把 $y$ 那层循环移到最里面之后可以二项式定理处理，所以复杂度就是 $O(nV \log)$，可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P = 998244353, N = 1e6;
ll fac[1000005], ifac[1000005];
ll C(int n, int m) {
	return fac[n] * ifac[m] % P * ifac[n - m] % P;
}
ll QPow(ll a, ll b) {
	ll res = 1;
	for (; b; b >>= 1, a = a * a % P) if (b & 1) res = res * a % P;
	return res;
}
int T, n, m, V;
int main() {
	scanf("%d", &T);
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % P;
	ifac[N] = QPow(fac[N], P - 2);
	for (int i = N; i; i--) ifac[i - 1] = ifac[i] * i % P;
	while (T--) {
		scanf("%d%d%d", &n, &m, &V);
		ll ans = 0;
		for (int x = 1; x <= n; x++) {
			for (int c = 1; c <= V; c++) {
				ll t = 1ll * ((x & 1) ? P - 1 : 1) * C(n, x) % P * QPow(QPow(c, x), m) % P * QPow(QPow(V, n - x), m) % P;
				ll w = QPow(c, 1ll * x * (P - 2)) * (P - 1) % P * QPow(V - c + 1, n - x) % P * QPow(V, 1ll * (n - x) * (P - 2)) % P;
				ans += t * QPow(w + 1, m) % P;
				ans -= t;
			}
		}
		printf("%lld\n", (ans % P + P) % P);
	}
	return 0;
}
```

---

## 作者：MatrixGroup (赞：7)

来点不需要二项式定理的做法。

正难则反，考虑如何计算左边大于右边的方案数。设 $f(a,b)$ 表示左边 $\ge a$，右边 $\le b$ 的方案数，则答案为

$$
v^{nm}-\sum_{i=1}^{v-1}f(i+1,i)+\sum_{i=1}^{v-2}f(i+2,i)
$$

考虑如何计算 $f$。对行容斥，钦定 $i$ 行的 $\max<a$（换言之全部小于 $a$），则每一列是独立的。一列的方案数就是所有方案数（$v^{n-i}(a-1)^i$）减去每个都大于 $b$ 的方案数（$(v-b)^{n-i}(a-b-1)^i$），因此有。

$$
f(a,b)=\sum_{j=0}^n(-1)^j\dbinom nj\left(v^{n-i}(a-1)^i-(v-b)^{n-i}(a-b-1)^i\right)^m
$$

直接计算即可。时间复杂度 $O(nv\log(nm))$。

---

## 作者：Rosabel (赞：6)

作为勤劳的题解自动姬来写这篇题解四周目。

观察 $nv\le 10^6$，那么复杂度多半与这俩有关。

好心的小妹妹把式子重新搬一遍：
$$
\min_{1\le i\le n}(\max_{1\le j\le m} a_{i,j})\le\max_{1\le j\le m}(\min_{1\le i\le n} a_{i,j})
$$
设 $x=\min_{1\le i\le n}(\max_{1\le j\le m} a_{i,j})$。为了使式子成立，那么至少存在一列使得每个元素都 $\ge x$。不取等当且仅当存在一列每个元素都 $\gt x$。不妨设这列的最小值为 $y$。但从行的角度考虑会使得 $\min_{1\le i\le n}(\max_{1\le j\le m} a_{i,j})=y\gt x$。所以不可能不取等。也可以同步证明：
$$
\min_{1\le i\le n}(\max_{1\le j\le m} a_{i,j})\ge\max_{1\le j\le m}(\min_{1\le i\le n} a_{i,j})
$$
那么问题变成求取等的方案数。发现此时若直接计数会使一些条件互相干扰。所以钦定 $\max= x$ 的行。我们发现要存在至少一列满足每个元素都 $\ge x$ 且最小值恰为 $x$，设这些列为 **第二条件关键列**（名字很土，见谅）。对于钦定 $\max=x$ 的行，第二条件关键列值恰为 $x$，其他列满足 $\le x$ 即可；对于没有钦定 $\max=x$ 的行，第二条件关键列值 $\ge x$，其他随意。

我们考虑去枚举 $x$。

由于钦定的这些行所构成的集合元素位置随意，所以对于同大小的集合只需要计算一次乘上组合数即可。设 $f_p(i)$ 为钦定 $x=p$，$\max=x$ 的行恰有 $i$ 行的方案数。但是发现恰好的方案不太方便计算，只能计算至少。设 $g_p(i)$ 为钦定 $x=p$，$\max=x$ 的行至少 $i$ 行的方案数。有如下关系式：
$$
g_p(i)=\sum_{i\le j\le n}{n-i\choose j-i}f_p(j)
$$
反演得：
$$
f_p(i)=\sum_{i\le j\le n}(-1)^{j-i}{n-i\choose j-i}g_p(j)
$$
我们此时需要求的是：
$$
\sum_{1\le i\le n}{n\choose i}f_p(i)=\sum_{1\le i\le n}{n\choose i}\sum_{i\le j\le n}(-1)^{j-i}{n-i\choose j-i}g_p(j)
$$
将 $j$ 提到前面：
$$
=\sum_{1\le j\le n}(-1)^jg_p(j)\sum_{1\le i\le j}(-1)^{i}{n\choose i}{n-i\choose j-i}
$$
由二项式推论得：
$$
=\sum_{1\le j\le n}(-1)^jg_p(j)\sum_{1\le i\le j}(-1)^i{n\choose j}{j\choose i}
$$
将 $j$ 相关项移到前面：
$$
=\sum_{1\le j\le n}(-1)^j{n\choose j}g_p(j)\sum_{1\le i\le j}(-1)^i{j\choose i}
$$
由二项式推论得：
$$
=\sum_{1\le j\le n}(-1)^j{n\choose j}g_p(j)
$$


接下来的问题是如何求出 $g_p(j)$。至少存在一列满足 $j$ 列恰好取 $p$，$n-j$ 列取 $\ge p$，其他一般列满足 $j$ 列取 $\le p$，$n-j$ 列随便取。这是一个很经典的容斥，将总方案数减去全取一般列的方案数即可：
$$
g_p(j)=(x^jv^{n-j})^m-((x^jv^{n-j})-(v-x+1)^{n-x})^m
$$
很容易做到 $\Theta(\log(nm))$ 求出。总时间复杂度 $\Theta(nv\log(nm))$。常数很大但过得去。

[code](https://codeforces.com/contest/2048/submission/297342328)

upd：2024.12.24 修正了一些排版上的问题。

---

## 作者：喵仔牛奶 (赞：4)

## Solution

考虑 $\text{LHS}<\text{RHS}$，此时存在 $x$ 使得一行每个数都 $<x$，存在一列每个数都 $\ge x$，显然行列相交的地方不能取值，所以不存在这种情况。

考虑 $\text{LHS}=\text{RHS}$ 的条件，枚举 $x=\text{LHS}$：
- 存在一行 $\max=x$，所有行存在 $\ge x$ 的数。
- 存在一列 $\min=x$，所有列存在 $\le x$ 的数。

设 $f(x,y)$ 表示行存在 $\ge x$ 的数、列存在 $\le y$ 的数的方案数。$\max=x$ 的方案数等于 $\max\ge x$ 和 $\max\ge x+1$ 的方案数相减，同理取消掉 $\min=x$ 的限制，答案可以表示为
$$(f(x,x)-f(x,x-1))-(f(x+1,x)-f(x+1,x-1))$$

考虑如何求出 $f(x,y)$：
- 枚举 $i\in[0,n]$，钦定 $i$ 行不存在 $\ge x$ 的数。
- 考虑一列的填数方案，对于这 $i$ 行，要 $<x$，所以方案数为 $v^{n-i}(x-1)^i$。
- 要减去不存在 $\le y$ 的数的方案，即减去 $(v-y)^{n-i}\max(x-y-1,0)^i$。
- 记上两式之差为 $t$，贡献为 $(-1)^i\binom{n}{i}t^m$。

综上：
$$f(x,y)=\sum_{i=0}^{n}(-1)^i\binom{n}{i}\left(v^{n-i}(x-1)^i-(v-y)^{n-i}\max(x-y-1,0)^i\right)^m$$

时间复杂度 $\mathcal{O}(\sum nv\log nm)$。

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace math { ... }
namespace Milkcat {
	using namespace math;
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5, mod = 998244353;
	typedef mint<mod> MI;
	int n, m, v; MI rs; Comb<MI> C;
	MI calc(int p, int q) {
		MI rs = 0; 
		REP(i, 0, n) {
			MI t = qpow((MI)v, n - i) * qpow((MI)p - 1, i);
			t -= qpow((MI)v - q, n - i) * qpow((MI)max(p - q - 1, 0), i);
			rs += C(n, i) * qpow(t, m) * (i & 1 ? -1 : 1);
		}
		return rs;
	}
	int main() {
		cin >> n >> m >> v, C.init(n), rs = 0;
		REP(i, 1, v) {
			rs += calc(i, i) - calc(i, i - 1);
			rs -= calc(i + 1, i) - calc(i + 1, i - 1);
		}
		cout << rs << '\n';
		return 0;
	}
}
```

---

## 作者：qczrz6v4nhp6u (赞：3)

比较有趣的题，但是赛时没时间做了。/ll

### Solution

观察一下 $\min\limits_{1\le i\le n}\max\limits_{1\le j\le m}a_{i,j}\le \max\limits_{1\le j\le m}\min\limits_{1\le i\le n}a_{i,j}$ 这一条件。设左边在 $(u,v)$ 处取到最值，右边在 $(p,q)$ 处取到最值，那么有：

$$a_{u,v}\ge a_{u,q}\ge a_{p,q}$$

所以说上面的条件一定满足左边一定大于等于右边，成立当且仅当 $a_{u,v}=a_{p,q}$。

设这个最值为 $t$，考虑所有取到最值的位置的集合。因为对于每个取到最值的位置都满足它是所在行的 $\max$，所以这一行的数都要 $\le t$；同理，对于每个取到最值的位置，所在列的数都满足 $\ge t$。所以说限制其实就相当于指定了若干行 $\le t$ 与若干列 $\ge t$，行和列的交点处即为取到最值的位置。

现在考虑计数。枚举 $t$，这显然不会算重；因为每种合法矩阵只能算一次，我们考虑对限制的行和列容斥。那么答案即为：

$$\sum_{t=1}^v\sum_{i=1}^n\sum_{j=1}^m(-1)^{i+j}{n\choose i}{m\choose j}t^{i(m-j)}(v-t+1)^{j(n-i)}v^{(n-i)(m-j)}$$

现在我们有了个 $O(nmv)$ 的做法。考虑优化掉一个 $m$：

$$\begin{aligned}
&\sum_{t=1}^v\sum_{i=1}^n\sum_{j=1}^m(-1)^{i+j}{n\choose i}{m\choose j}t^{i(m-j)}(v-t+1)^{j(n-i)}v^{(n-i)(m-j)}\\
=&\sum_{t=1}^v\sum_{i=1}^n(-1)^i{n\choose i}\sum_{j=1}^m(-1)^j{m\choose j}\Big(t^i\Big)^{m-j}\Big((v-t+1)^{n-i}\Big)^j\Big(v^{n-i}\Big)^{m-j}
\end{aligned}$$

设 $A=-(v-t+1)^{n-i}$，$B=t^iv^{n-i}$，原式即为

$$\begin{aligned}
&\sum_{t=1}^v\sum_{i=1}^n(-1)^i{n\choose i}\sum_{j=1}^m{m\choose j}A^jB^{m-j}\\
=&\sum_{t=1}^v\sum_{i=1}^n(-1)^i{n\choose i}\Big((A+B)^m-B^m\Big)
\end{aligned}$$

复杂度为 $O(nv\log m)$，可以通过。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=1e6+5,mod=998244353;
int n,m,v;
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
ll fac[N],ifac[N];
void init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i%mod;
}
inline ll C(int n,int m){return fac[n]*ifac[m]%mod*ifac[n-m]%mod;}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	init(1e6);
	int _Test;cin>>_Test;
	while(_Test--){
		cin>>n>>m>>v;
		ll ans=0;
		for(int t=1;t<=v;t++)
			for(int i=1;i<=n;i++){
				ll A=mod-qpow(v-t+1,n-i),B=qpow(t,i)*qpow(v,n-i)%mod;
				ans=(ans+(i&1?mod-1:1)*C(n,i)%mod*(qpow(A+B,m)-qpow(B,m)+mod))%mod;
			}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Komomo (赞：1)

容易发现 LHS 必定 $\ge$ RHS，因为对于任意第 $i$ 行和第 $j$ 列，一定有第 $i$ 行的 $\max \ge a_{i,j}\ge$ 第 $j$ 列的 $\min$。于是我们只要算出相等的方案数就好了，这个非常傻逼，直接容斥，每次钦定 $i$ 行 $j$ 列，枚举这个相等的值 $x$，答案就是：

$$\sum\limits_{x=1}^V\sum\limits_{i=1}^n\sum\limits_{j=1}^m(-1)^{i+j}\dbinom{n}{i}\dbinom{m}{j}x^{i(m-j)}(V-x+1)^{j(n-i)}V^{(n-i)(m-j)}$$

已经可以 $\mathcal O(n^2V)$ 计算了，把 $i$ 的系数提出来：

$$\sum\limits_{x=1}^V\sum\limits_{i=1}^n(-1)^i\dbinom{n}{i}\sum\limits_{j=1}^m\dbinom{m}{j}(-1)^jx^{i(m-j)}(V-x+1)^{j(n-i)}V^{(n-i)(m-j)}$$

后面那坨很像二项式定理，合并一下：

$$\sum\limits_{x=1}^V\sum\limits_{i=1}^n(-1)^i\dbinom{n}{i}\sum\limits_{j=1}^m\dbinom{m}{j}[-(V-x+1)^{(n-i)}]^j[x^iV^{(n-i)}]^{m-j}$$

$$\sum\limits_{x=1}^V\sum\limits_{i=1}^n(-1)^i\dbinom{n}{i}[x^iV^{(n-i)}-(V-x+1)^{(n-i)}]^m-\Delta$$

后面那个 $\Delta$ 就是为了凑二项式定理要把 $j=0$ 的算进去，然后最后减掉的东西，时间复杂度 $\mathcal O(nV\log V)$。

---

## 作者：Purslane (赞：0)

# Solution

我的做法挺意识流的。

转化为对

$$ \min_{1\le i\le n}\left(\max_{1\le j\le m}a_{i,j}\right)>\max_{1\le j\le m}\left(\min_{1\le i\le n}a_{i,j}\right)$$

的矩阵计数。

考虑按照数值大小从 $v$ 到 $1$，不断往 $a$ 中填数。称时刻 $i$ 填了所有值为 $i$ 的数。

矩阵满足上面的条件，等价于存在某个时刻 $t$，满足**所有行非空，所有列非满**。为了计数方便，如果存在我们找到最大的这个 $t$。

我们先求出：在时刻 $i$ 满足**所有行非空，所有列非满**的矩阵个数。考虑使用容斥。发现反面情况“存在有行为空”和“存在有列为满”是互相独立的，可以分开算。

给出计算式：

$$
\sum_{j=0}^n (-1)^j \dbinom{n}{j} (i-1)^{jm} v^{(n-j)m} = [v^m-(i-1)^m]^n (*) \\
\sum_{j=0}^m (-1)^j \dbinom{m}{j} (v-i+1)^{nj} v^{n(m-j)} = [v^n-(v-i+1)^n]^m (**)
$$

则 $(*)+(**) - v^{nm}$ 就是答案（很容易验证，反面情况在 $(*)+(**)$ 中算了一次，正面情况算了两次，直接减掉全局即可）。

不过还有一个问题：我们需要保证某一行**所有填的数都是 $i$**。设最终有 $k$ 行**填了 $>i$ 的数**，则我们需要再上面算的基础上再减去 $k=n$ 的情况。

而 $k=n$ 咋容斥呢？就是枚举超集，并且赋予 $(-1)^{n-k}$ 的贡献。所以我们钦定 $k$ 行**可以填 $>i$ 的数**。

还是模仿上面的容斥，得到两个计算式：一个是对**所有行非空**加限制，就是（注意这些东西最后都要乘上 $(-1)^{n-k} \dbinom{n}{k}$）

$$
\sum_{s=0}^n \sum_{x \le k, y \le n-k,x+y=s} (-1)^{s} \binom{k}{x} \binom{n-k}{y} (i-1)^{ms}(v^m)^{k-x}(i^m)^{n-k-y}
$$

稍微解释一下含义：我们钦定了 $x+y=s$ 行为空，其中 $x$ 行是我们之前钦定过的 $k$ 行中的一部分，$y$ 行是没被我们钦定的一部分（因为是否在钦定的 $k$ 行中会直接决定决策）。

断言：我们可以直接令 $x=y=0$。我们可以换一个角度去理解——先钦定了 $s$ 行全满，剩下的 $n-s$ 假设已经钦定好了。那么 $s$ 行内部每个数钦定是否在 $k$ 行中是独立的，每个都会带上 $(-1)+1=0$ 的贡献（非常类似 NOIP2024 T3 容斥做法中的一步），所以只要 $s \neq 0$ 一定最终贡献为 $0$。

另一个计算式是对于**所有列非空加限制**。发现没啥大的改动：

$$\sum_{j=0}^m \dbinom{m}{j} [-(v-i+1)^k]^{j} (v^ki^{n-k})^{m-j}= [v^ki^{n-k}-(v-i+1)^k]^m$$

而总体的局面就是 $i^{(n-k)m}v^{km}$。

直接实现上述过程就可以做到 $O(\sum nk \log V)$，足以通过本题。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10,MOD=998244353;
int T,n,m,v,inv[MAXN],frac[MAXN];
int qpow(int base,int p) {
	base%=MOD;
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int C(int u,int d) {return frac[d]*inv[u]%MOD*inv[d-u]%MOD;}
int solve(int n,int m,int v) {
	int ans=0;
	ffor(i,1,v) {
		ans=(ans+qpow(qpow(v,n)-qpow(v-i+1,n),m))%MOD;
		ans=(ans+qpow(qpow(v,m)-qpow(i-1,m),n))%MOD;
		ans=(ans-qpow(v,n*m))%MOD;
	}
	ffor(k,0,n) {
		int mul=C(k,n)*(1-2*((n-k)%2));
		ffor(i,1,v) {
			ans=(ans-mul*qpow(v,m*k)%MOD*qpow(i,m*(n-k)))%MOD;
			ans=(ans-mul*qpow(qpow(v,k)*qpow(i,n-k)%MOD-qpow(v-i+1,k),m))%MOD;
			ans=(ans+mul*qpow(i,(n-k)*m)%MOD*qpow(v,k*m))%MOD;
		}
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	int t=1000000;
	frac[0]=1; ffor(i,1,t) frac[i]=frac[i-1]*i%MOD;
	inv[t]=qpow(frac[t],MOD-2); roff(i,t-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	while(T--) {
		cin>>n>>m>>v;	
		cout<<((qpow(v,n*m)-solve(n,m,v))%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```

---

## 作者：wrkwrkwrk (赞：0)

从式子的特征入手。
令 $\min_{1\le i\le n}\left(\max_{1\le j\le m}a_{i,j}\right)=b$，$\max_{1\le j\le m}\left(\min_{1\le i\le n}a_{i,j}\right)=c$，根据题面有 $b \leq c$。

则 $\exists i \left(\max_{1\le j\le m}a_{i,j}\right)=b,\exists j\left(\min_{1\le i\le n}a_{i,j}\right)=c$。

考虑将其中的一个第 $i$ 行和第 $j$ 列提出，则这行的所有数都 $\leq b$，这列的所有数都 $\geq c$。

考虑交点，则 $c \leq a_{i,j}\leq b \leq c$。于是 $c= a_{i,j}= b$。

注意到 $\forall x\neq i,a_{x,j} \geq b$，则 $\forall x,\max_{1\le j\le m}a_{x,j} \geq b$，列上同理。故在其他数任意时，所有限制已经被满足。

考虑对每个 $b$ 计数。我们希望找到一行一列满足条件，钦定一行一列的方案数为：

$$
nmb^{m-1}(v+1-b)^{n-1}v^{(m-1)(n-1)}
$$

显然这会记重。考虑重复的方案来自哪里：同时存在多个行或多个列满足条件。于是考虑容斥。钦定 $c$ 行 $d$ 列的方案数为：

$$
\binom n c \binom m d b^{(m-d)c}(v+1-b)^{(n-c)d}v^{(m-d)(n-c)}
$$

考虑容斥系数：首先对行容斥 $(-1)^c$，然后对列容斥 $(-1)^d$，故总答案为：

$$
\sum _{b=1}^{v}\sum _{c=1}^n \sum_{d=1}^m (-1)^{c+d}\binom n c \binom m d b^{(m-d)c}(v+1-b)^{(n-c)d}v^{(m-d)(n-c)}
$$

这个式子的时间复杂度是 $O(mnv)$。考虑优化。
先提取公因子：

$$
\sum _{b=1}^{v}\sum _{c=1}^n (-1)^c\binom n c b^{mc}v^{m(n-c)}\sum_{d=1}^m \binom m d b^{-cd}(v+1-b)^{(n-c)d}v^{-(n-c)d}
$$

考虑有关 $d$ 的式子，其所有指数均有因子 $d$，令所有底数的乘积为 $t$，则其为 $\sum_{d=1}^n \binom n d t^d$，发现其符合二项式定理的形式。其为 $(t+1)^n-1$。直接计算即可。

时间复杂度 $O(nv\log m)$。

```cpp

#define mod 998244353
#define mint modint<mod>
Math<mint,1000006>math;
const mint f1=mod-1;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n,m,v;
		cin>>n>>m>>v;
		mint ans=0;
		for(int i=1;i<=v;i++){
			for(int h=1;h<=n;h++){
				mint xs=f1.fpof(h)*math.binom(n,h)*mint(i).fpof(h*m)*((mint(v).fpof((n-h)*m))); 
				mint t=f1*(mint(i).fpof(h).inv())*mint(v-i+1).fpof(n-h)*((mint(v)).fpof(n-h).inv());
				ans+=xs*mint((t+mint(1)).fpof(m)-mint(1));
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

[AC ](https://codeforces.com/contest/2048/submission/297407430)记录

---

## 作者：_lmh_ (赞：0)

让最小值小于一个最大值是不好做的，考虑容斥，让最小值大于最大值。

令 $F(x,y)$ 为 $\min_{1\le i\le n}(\max_{1\le j\le m}a_{i,j})\ge x>y\ge\max_{1\le j\le m}(\min_{1\le i\le n}a_{i,j})$ 的矩阵个数，也就是说，$\forall i\in [1,n],\max_{1\le j\le m}a_{i,j}\ge x$ 且 $\forall j\in [1,m],\min_{1\le i\le n}a_{i,j}\le y$。

计算答案时枚举 $\min_{1\le i\le n}(\max_{1\le j\le m}a_{i,j})$，容斥 $\max_{1\le j\le m}(\min_{1\le i\le n}a_{i,j})$，可以得到 $v^{nm}-\sum_{i=2}^vF(i,i-1)+\sum_{i=3}^vF(i,i-2)$。

现在我们发现又出现了最大值大于等于某个数的形式，这个是不好做的，再来一次容斥，考虑钦定一些行不满足限制。也就是说：

> 对于其中的 $i$ 行，所有元素 $<x$。
> 
> 其余元素没有任何限制。

所有的列互不影响，可以考虑只算一列的答案然后快速幂。

这个时候我们遇到了最小值小于等于某个数的形式，那只好再请出容斥了，考虑让所有数都 $>y$，方案数是好算的。再用所有方案去减，就可以得出单列的答案 $v^{n-i}(x-1)^i-(v-y)^{n-i}(x-y-1)^i$。

现在套上前面的容斥，最终得出 $F(x,y)=\sum_{i=0}^{n}(-1)^iC_n^i(v^{n-i}(x-1)^i-(v-y)^{n-i}(x-y-1)^i)^m$，可以 $O(n\log nm)$ 计算。

因此最后我们可以在 $O(nv\log nm)$ 的复杂度内解决，怎么实现都是能过的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll MOD=998244353;
ll qpow(ll x,ll k){
	ll sum=1;
	while(k){
		if (k&1) (sum*=x)%=MOD;
		(x*=x)%=MOD;k>>=1;
	}
	return sum;
}
ll T,n,m,v,ans;
ll F(ll x,ll y){
	ll sum=0,C=1;
	for (int i=0;i<=n;++i){
		(sum+=((i&1)?MOD-1:1)*C%MOD*qpow((qpow(v,n-i)*qpow(x-1,i)+MOD-qpow(v-y,n-i)*qpow(x-y-1,i)%MOD)%MOD,m))%=MOD;
		C=C*(n-i)%MOD*qpow(i+1,MOD-2)%MOD;
	}
	return sum;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m>>v;ans=qpow(v,n*m);
		for (int i=1;i<v;++i) (ans+=(MOD-1)*F(i+1,i))%=MOD;
		for (int i=2;i<v;++i) (ans+=F(i+1,i-1))%=MOD;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF2048G)

**题目大意**

> 给定 $n\times m$ 矩阵，填入 $[1,v]$ 使得每行最大值的最小值小于等于每列最小值的最大值。
>
> 数据范围：$nv\le 10^6,m\le 10^9$。

**思路分析**

可以反面考虑，统计有多少矩阵每行最大值 $r_i$ 都大于每列最小值 $c_j$。

然后接着容斥，钦定若干格子 $(i,j)$ 满足 $r_i\le c_j$，由于 $a_{i,j}\le r_i\le c_j\le a_{i,j}$，因此 $a_{i,j}=r_i=c_j$。

因此当我们钦定的格子包含 $x$ 行 $y$ 列，则这个 $x\times y$ 矩阵内的元素相等，枚举其取值，方案数为 $\sum v^{(n-x)(m-y)}k^{x(m-y)}(v-k+1)^{(n-x)y}$。

直接枚举 $(x,y)$，求对应的容斥系数，即 $x\times y$ 矩阵每行每列至少钦定一个格子的容斥系数，容斥每行是否非空得到系数为 $(-1)^{x+y+1}$。

此时答案为：
$$
\sum_{x,y,k}(-1)^{x+y}\binom nx\binom myv^{(n-x)(m-y)}k^{x(m-y)}(v-k+1)^{(n-x)y}
$$
把 $y$ 一维提出来，用二项式定理化简得到：
$$
\sum_{x,k}(-1)^x\binom nx(v^{n-x}k^x-(v-k+1)^{n-x})^m
$$
直接计算即可。

时间复杂度 $\mathcal O(nv\log P)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e6+5,MOD=998244353;
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
ll inv[MAXN];
void solve() {
	ll n,m,v;
	scanf("%lld%lld%lld",&n,&m,&v);
	ll c=1,s=0;
	for(int i=1;i<=n;++i) {
		c=c*(n-i+1)%MOD*inv[i]%MOD;
		for(int k=1;k<=v;++k) {
			ll b=(ksm(k,i)*ksm(v,n-i)+MOD-ksm(v-k+1,n-i))%MOD;
			b=(ksm(b,m)-ksm(k,i*m)*ksm(v,(n-i)*m))%MOD;
			s=(s+(i&1?MOD-c:c)*(b+MOD))%MOD;
		}
	}
	printf("%lld\n",s);
}
signed main() {
	inv[1]=1;
	for(int i=2;i<MAXN;++i) inv[i]=inv[MOD%i]*(MOD-MOD/i)%MOD;
	int _;
	scanf("%d",&_);
	while(_--) solve();
	return 0;
}
```

---

