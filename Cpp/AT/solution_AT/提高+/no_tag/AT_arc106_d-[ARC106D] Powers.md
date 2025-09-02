# [ARC106D] Powers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc106/tasks/arc106_d

長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \cdots,\ A_N) $ と整数 $ K $ が与えられます。

$ 1\ \le\ X\ \le\ K $ を満たす整数 $ X $ それぞれについて、以下の値を求めてください。

$ \left(\displaystyle\ \sum_{L=1}^{N-1}\ \sum_{R=L+1}^{N}\ (A_L+A_R)^X\right)\ \bmod\ 998244353 $

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ K\ \le\ 300 $
- $ 1\ \le\ A_i\ \le\ 10^8 $

### Sample Explanation 1

$ 1 $ 行目には、$ (1+2)^1\ +\ (1+3)^1\ +\ (2+3)^1\ =\ 3\ +\ 4\ +\ 5\ =\ 12 $ を出力します。 $ 2 $ 行目には、$ (1+2)^2\ +\ (1+3)^2\ +\ (2+3)^2\ =\ 9\ +\ 16\ +\ 25\ =\ 50 $ を出力します。 $ 3 $ 行目には、$ (1+2)^3\ +\ (1+3)^3\ +\ (2+3)^3\ =\ 27\ +\ 64\ +\ 125\ =\ 216 $ を出力します。

### Sample Explanation 3

$ \bmod\ 998244353 $ での値を出力してください。

## 样例 #1

### 输入

```
3 3
1 2 3```

### 输出

```
12
50
216```

## 样例 #2

### 输入

```
10 10
1 1 1 1 1 1 1 1 1 1```

### 输出

```
90
180
360
720
1440
2880
5760
11520
23040
46080```

## 样例 #3

### 输入

```
2 5
1234 5678```

### 输出

```
6912
47775744
805306038
64822328
838460992```

# 题解

## 作者：K8He (赞：5)

# [「解题报告」[ARC106D] Powers](https://www.luogu.com.cn/problem/AT_arc106_d)

考虑容斥。

$$
\begin{aligned}
\sum_{l = 1}^{n - 1}\sum_{r = l + 1}^{n}(a_l + a_r)^x
&=\frac{\sum_{l = 1}^{n}\sum_{r = 1}^{n}(a_l + a_r)^x - \sum_{l = 1}^{n}(2a_i)^x}{2}\\
\end{aligned}
$$

后边预处理出来，考虑使用二项式定理化简一下前边的。

$$
\begin{aligned}
\sum_{l = 1}^{n}\sum_{r = 1}^{n}(a_l + a_r)^x
&=\sum_{l = 1}^{n}\sum_{r = 1}^{n}\sum_{k = 0}^{x}\dbinom{x}{k}a_l^{k}a_r^{x - k}\\
&=\sum_{k = 0}^{x}\dbinom{x}{k}(\sum_{l = 1}^{n}a_l^{k})(\sum_{r = 1}^{n}a_r^{x - k})\\
\end{aligned}
$$

那么对于所有的 $x$ 预处理出来 $\sum_{i = 1}^{n}a_i^x$ 即可。

时间复杂度 $O(nk)$。

```cpp
const ll N = 2e5 + 10, K = 310, P = 998244353;
namespace SOLVE {
	ll n, k, a[N], b[2][K], c[K][K], ans[K];
	inline ll rnt () {
		ll x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}
	inline ll FastPow (ll a, ll b) {
		ll ans = 1;
		while (b) {
			if (b & 1) ans = ans * a % P;
			a = a * a % P, b >>= 1;
		}
		return ans;
	}
	inline void In () {
		n = rnt (), k = rnt ();
		_for (i, 1, n) a[i] = rnt ();
		return;
	}
	inline void Solve () {
		c[0][0] = 1, b[0][0] = b[1][0] = n;
		_for (j, 1, k) {
			_for (i, 1, n) {
				b[0][j] = (b[0][j] + FastPow (a[i], j)) % P;
				b[1][j] = (b[1][j] + FastPow (a[i] << 1, j)) % P;
			}
		}
		_for (i, 1, k) {
			c[i][0] = 1, ans[i] = b[0][0] * b[0][i] % P;
			_for (j, 1, i) {
				c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % P;
				ans[i] = (ans[i] + c[i][j] * b[0][j] % P * b[0][i - j] % P) % P;
			}
			ans[i] = (ans[i] - b[1][i] + P) % P * 499122177 % P;
		}
		return;
	}
	inline void Out () {
		_for (i, 1, k) printf ("%lld\n", ans[i]);
		return;
	}
}
```


---

## 作者：_Flame_ (赞：3)

### $\text{solution}$

容斥一下柿子：

$$\sum\limits_{l=1}^{n-1}\sum\limits_{r=l+1}^{n}(a_l+a_r)^x=\frac{\sum\limits_{l=1}^{n}\sum\limits_{r=1}^{n}(a_l+a_r)^x-\sum\limits_{i=1}^{n}(2\times a_i)^x}{2}$$

化简一下 $\sum\limits_{l=1}^{n}\sum\limits_{r=1}^{n}(a_l+a_r)^x$，根据二项式定理，有：

$$(a_l+a_r)^x=\sum\limits_{i=0}^{x}(\binom{x}{i}\times {a_l}^i\times {a_r}^{x-i})$$

$$\sum\limits_{l=1}^{n}\sum\limits_{r=1}^{n}(a_l+a_r)^x=\sum\limits_{l=1}^{n}\sum\limits_{r=1}^{n}\sum\limits_{i=0}^{x}(\binom{x}{i}\times {a_l}^i\times {a_r}^{x-i})$$

预处理 $\sum\limits_{i=1}^{n}{a_i}^x$，就能过了。

### $\text{code}$

```cpp
int fac[maxn],inv[maxn];
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}

void init(int maxn){
	fac[0]=1;
	for(int i=1;i<=maxn;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[maxn]=ksm(fac[maxn],mod-2);
	for(int i=maxn-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}

int C(int m,int n){
	if(n<0||m<0||m<n){
		return 0ll;
	}
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}

int n,x;

int a[maxn],sum[maxn];

void solve(){
	n=read(),x=read();
	init(x);
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=0;i<=x;i++){
		for(int j=1;j<=n;j++){
			sum[i]=(sum[i]+ksm(a[j],i))%mod;
		}
	}
	for(int i=1;i<=x;i++){
		int ans=0;
		for(int j=0;j<=i;j++){
			ans=(ans+C(i,j)*sum[j]%mod*sum[i-j]%mod)%mod;
		}
		ans=((ans-ksm(2,i)*sum[i]%mod+mod)%mod*ksm(2,mod-2)%mod)%mod;
		write(ans);
		puts("");
	}
	return ;
}

```

---

## 作者：gdf_yhm (赞：3)

[ARC106D](https://www.luogu.com.cn/problem/AT_arc106_d)

[Powers](https://atcoder.jp/contests/arc106/tasks/arc106_d)


### 思路

左边到右边不好，改为任意一个到另一个。

$$ans_x=\frac{1}{2}(\sum_i^n\sum_j^n (a_i+a_j)^x-\sum_i^n (2\times a_i)^x)$$

拆开 $k$ 次方。

$$(a_i+a_j)^x=\sum_{k=0}^x (\binom{x}{k}\times {a_i}^k\times {a_j}^{x-k})$$

$$ans_x=\frac{1}{2}(\sum_{k=0}^x(\sum_i^n {a_i}^k\times \sum_j^n {a_j}^{x-k})-\sum_i^n (2\times a_i)^x)$$

预处理 $sum_k=\sum_i {a_i}^k$。

$$ans_x=\frac{1}{2}(\sum_{k=0}^x(sum_k\times sum_{x-k})-2^x\times sum_x)$$

复杂度 $O(nk+k^2)$。 

### code

```cpp
int n,x,a[maxn];
inline int ksm(int a,int b=mod-2,int p=mod){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
int ans,ni;
int fac[maxn],inv[maxn];
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int sum[maxm],mul[maxn];
void work(){
	n=read();x=read();
	for(int i=1;i<=n;i++)a[i]=read(),mul[i]=1;
	for(int k=0;k<=x;k++){
		for(int i=1;i<=n;i++)sum[k]+=mul[i],sum[k]%=mod;
		for(int i=1;i<=n;i++)mul[i]=mul[i]*a[i]%mod;
//		cout<<sum[k]<<" ";
	}
//	cout<<"\n";
	fac[0]=1;for(int i=1;i<=x;i++)fac[i]=fac[i-1]*i%mod;
	inv[x]=ksm(fac[x]);
	for(int i=x-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	ni=ksm(2);
	for(int i=1;i<=x;i++){
		ans=0;
		for(int k=0;k<=i;k++)ans+=C(i,k)*sum[k]%mod*sum[i-k]%mod,ans%=mod;
		ans+=mod-ksm(2,i)*sum[i]%mod,ans%=mod;
		ans*=ni,ans%=mod;
		printf("%lld\n",ans);
	}
}
```

---

## 作者：luchenxi2012 (赞：2)

题目传送门：[[ARC106D] Powers](https://www.luogu.com.cn/problem/AT_arc106_d)

推式子题。

先看数据范围，好像是 $O(nk)$ 的做法，但是发现不能只枚举 $n$ 就能推出两两之间和的 $x$ 次方，于是先考虑把 $(a_l+a_r)^x$ 拆开。于是得到

$$(a_l+a_r)^x=\frac12((a_l^x+a_r^x)+x(a_l^{x-1}a_r+a_la_r^{x-1})+\frac{x(x-1)}{2}(a_l^{x-2}a_r^2+a_l^2a_r^{x-2})+\ldots+(a_r^x+a_l^x))$$

将 $l$ 和 $r$ 从 $1$ 到 $n$ 扫一遍，于是得到

$$\begin{aligned}
{} & \sum_{l=1}^{n}\sum_{r=l+1}^{n}(a_l+a_r)^x & 
\\
= &\ \frac12((\sum_{l=1}^{n}\sum_{r=l+1}^{n}(a_l^x+a_r^x))+(\sum_{l=1}^{n}\sum_{r=l+1}^{n}x(a_l^{x-1}a_r+a_la_r^{x-1}))+\ldots+(\sum_{l=1}^{n}\sum_{r=l+1}^{n}(a_r^x+a_l^x))) \\
= &\ \frac12(\frac12(\sum_{l=1}^{n}\sum_{r=1}^{n}(a_l^x+a_r^x)-\sum_{i=1}^{n}a_i^x)+\frac12(\sum_{l=1}^{n}\sum_{r=1}^{n}x(a_l^{x-1}a_r+a_la_r^{x-1})-\sum_{i=1}^{n}xa_i^x)+\ldots+\frac12(\sum_{l=1}^{n}\sum_{r=1}^{n}(a_r^x+a_l^x)-\sum_{i=1}^{n}a_i^x)) \\
= &\ \frac12(\sum_{l=1}^n\sum_{r=1}^na_l^x-\sum_{i=1}^na_i^x)+\frac12x(\sum_{l=1}^n\sum_{r=1}^na_l^{x-1}a_r-\sum_{i=1}^na_i^x)+\ldots+\frac12(\sum_{l=1}^n\sum_{r=1}^na_r^x-\sum_{i=1}^na_i^x) \\
= &\ \frac12(\sum_{l=1}^na_l^x\sum_{r=1}^n1-\sum_{i=1}^na_i^x)+\frac12x(\sum_{l=1}^na_l^{x-1}\sum_{r=1}^na_r-\sum_{i=1}^na_i^x)+\ldots+\frac12(\sum_{l=1}^n1\sum_{r=1}^na_r^x-\sum_{i=1}^na_i^x) \\
= &\ \frac12\sum_{i=0}^xC_{x}^{i}(s_is_{x-i}-s_x)
\end{aligned}$$

其中

$$s_i=\sum_{p=1}^na_p^i$$

这下就清爽多了吧。现在，我们只需要求出 $s_i$ 即可。显然，这是可以预处理的。具体实现看代码吧，没有什么复杂的点。最后时间复杂度瓶颈在于求 $s$ 数组，复杂度为 $O(nk)$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int p[200001][301], s[301]; // p[i][j] 表示 p[i] 的 j 次方
int fac[301], inv[301]; // 组合数必备
int qpow(int x, int y, int res = 1) {
	while (y) {
		if (y & 1) (res *= x) %= mod;
		(x *= x) %= mod; y >>= 1;
	}
	return res;
}
int C(int n, int m) {return fac[n] * inv[m] % mod * inv[n - m] % mod;}
signed main() {
	int n, k;
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &p[i][1]),
		(s[1] += p[i][1]) %= mod,
		p[i][0] = 1, s[0] = n; // 注意 0 也要初始化
	for (int i = 2; i <= k; i++)
		for (int j = 1; j <= n; j++)
			p[j][i] = p[j][i - 1] * p[j][1] % mod,
			(s[i] += p[j][i]) %= mod;
	fac[0] = 1;
	for (int i = 1; i <= k; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[k] = qpow(fac[k], mod - 2);
	for (int i = k; i; i--)
		inv[i - 1] = inv[i] * i % mod; // 求逆元
	for (int x = 1; x <= k; x++) {
		// (\sum a[l]^i * \sum a[r]^(x-i) - \sum a[l]^x) * C(x, i)
		int ans = 0;
		for (int i = 0; i <= x; i++)
			(ans += C(x, i) * (s[i] * s[x - i] % mod - s[x] + mod) % mod) %= mod;
		printf("%lld\n", ans * (mod + 1) / 2 % mod); // 注意要除以 2（即乘以 2 模模数的逆元）
	}
	return 0;
}
```

---

## 作者：Xy_top (赞：2)

简单题，不会二项式定理，只会杨辉三角。

考虑 $(a_i+a_j)^k$ 拆开的样子，即考虑 ${a_i}^x \times {a_j}^{k-x}$，然后把这个算出来后再乘上它出现的次数即可。

这个出现次数其实就是杨辉三角，对于每个 $\leq k$ 的数 $x$，预处理出所有数 $x$ 次方的和，算答案的时候乘法分配律即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, k;
int a[200005];
int sum[301];
int yh[302][302];
const int mod = 998244353;
void init () {
	yh[1][1] = 1;
	For (i, 2, 301) {
		For (j, 1, i) {
			yh[i][j] = yh[i - 1][j] + yh[i - 1][j - 1];
			if (yh[i][j] >= mod) yh[i][j] -= mod;
		}
	}
}
void solve () {
	init ();
	cin >> n >> k;
	For (i, 1, n) cin >> a[i];
	For (i, 1, n) {
		int tmp = 1;
		For (j, 0, k) {
			sum[j] += tmp;
			if (sum[j] >= mod) sum[j] -= mod;
			tmp = tmp * a[i] % mod;
		}
	}
	For (i, 1, k) {
		int ans = 0;
		For (x, 0, i) {
			ans += sum[x] * sum[i - x] % mod * yh[i + 1][x + 1] % mod;
			ans -= (sum[i] * yh[i + 1][x + 1]) % mod;//每个数^x * 每个数^(i-x)
			if (ans >= mod) ans -= mod;
			if (ans < 0) ans += mod;
		}
		ans = ans * 499122177 % mod;
		cout << ans << '\n';
	}
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：yzq_yzq (赞：1)

考虑算 $\sum (a_i+a_j)^x-\sum(a_i+a_i)^x$ 然后答案除以二。

后半部分是简单的，考虑先预处理好 $a_i^x,x\in[1,k]$ ，这是 $O(nk)$ 的。

然后前边的直接展开，命 $s_x=\sum a_i^x$，那么答案是 $\sum_{j=0}^xs_j\times s_{x-j}\times C_{x}^j$ 。

总复杂度 $O(nk)$ 。

```cpp
#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = x; i <= y; ++i)
#define drep(i, x, y) for (int i = x; i >= y; --i)
#define ll long long
#define pb push_back
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 200020, M = 305, mod = 998244353;
int n, k, a[N], C[M][M], v[N][M], s[M], pw[N];
inline ll qp(ll a, ll b = mod - 2) {
	ll res = 1;
	for(; b; b >>= 1, a = a * a % mod)
		if(b & 1) res = res * a % mod;
	return res;
}
// a[i] ^ y \times a[j] ^ x - y \times C(x, y)
int main() {
	IOS; cin >> n >> k, C[0][0] = 1, pw[0] = 1;
	rep(i, 1, N - 1) pw[i] = (pw[i - 1] << 1) % mod;
	rep(i, 1, M - 1) rep(j, 0, i) C[i][j] = (C[i - 1][j] + (j ? C[i - 1][j - 1] : 0)) % mod;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) {
		v[i][0] = 1;
		rep(j, 1, k + 1) v[i][j] = 1ll * v[i][j - 1] * a[i] % mod;
		rep(j, 0, k + 1) {
			s[j] += v[i][j];
			if(s[j] >= mod) s[j] -= mod;
		}
	}
	rep(i, 1, k) {
		ll res = 0;
		rep(j, 0, i) res += 1ll * s[j] * s[i - j] % mod * C[i][j] % mod;
		rep(j, 1, n) res -= (ll)v[j][i] * pw[i] % mod;
		cout << ((res % mod + mod) % mod) * qp(2) % mod << '\n';
	}
	return 0;
}
```

---

## 作者：FreedomKing (赞：1)

### 思路

原式不好硬求，考虑对式子容斥：

$$\sum_{l=1}^{n-1}\sum_{r=l+1}^n(a_i+a_j)^x=\frac{\sum_{l=1}^{n}\sum_{r=1}^n(a_i+a_j)^x-\sum_{i=1}^n(2a_i)^x}{2}$$

$\frac{\sum_{i=1}^n(2a_i)^x}{2}$ 可以通过直接预处理出来 $\sum_{i=1}^na_i^x$，然后发现 $\sum_{l=1}^{n}\sum_{r=1}^n(a_i+a_j)^x$ 可以使用二项式定理化一下得到：

$$\sum_{l=1}^{n-1}\sum_{r=l+1}^n(a_i+a_j)^x=\sum_{l=1}^{n-1}\sum_{r=l+1}^n\sum_{i=0}^x(\binom{x}{i}\times a_l^i\times a_r^{x-i})$$

前式转化为了关于组合数和 $\sum_{i=1}^na_i^x$ 的问题，分别预处理即可。

最终得到对于每个 $x$ 答案为：

$$\sum_{l=1}^{n-1}\sum_{r=l+1}^n(a_i+a_j)^x=\frac{\sum_{l=1}^{n-1}\sum_{r=l+1}^n\sum_{i=0}^x(\binom{x}{i}\times a_l^i\times a_r^{x-i})-\sum_{i=1}^n(2a_i)^x}{2}$$

### AC Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
bool M1;
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<" MB\n"
#define look_time cerr<<(clock()-Time)*1.0/CLOCKS_PER_SEC<<'\n'
#define File(_) freopen(_".in","r",stdin);freopen(_".out","w",stdout)
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=1e6+5,mN=3e4+5,mod=998244353;
namespace FreedomKing_qwq{
#define Time 0
#define lowbit(_) (_&-_) 
	struct Tree{
		int tree[N];
		inline void add(int x,int j){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=j;
			return;
		}
		inline int query(int x){
			int ans=0;
			for(int i=x;i>1;i-=lowbit(i)) ans+=tree[i];
			return ans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[x]=y;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,vis=getchar(),t=1;
		while(vis<'0'||vis>'9'){
			t^=(vis=='-');
			vis=getchar();
		}
		while(vis>='0'&&vis<='9'){
			x=(x<<3)+(x<<1)+vis-'0';
			vis=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
#define pf(_) ((_)*(_))
}
const int inv2=(mod+1)>>1;
int a[N],f[N],sum[N],fct[N],infct[N];
inline void init(int n){
	fct[0]=1;
	for(int i=1;i<=n;i++) fct[i]=(fct[i-1]*i)%mod;
	infct[n]=qpow(fct[n],mod-2,mod);
	for(int i=n-1;i>=0;i--) infct[i]=infct[i+1]*(i+1)%mod;
	return;
}
inline int C(int n,int m){return ((fct[m]*infct[n])%mod*infct[m-n])%mod;}
bool M2;signed main(){
	int n=qr,k=qr;
	init(k);
	for(int i=1;i<=n;i++){
		a[i]=qr;
		f[i]=1;
	}
	for(int i=0;i<=k;i++) for(int j=1;j<=n;j++) (sum[i]+=qpow(a[j],i,mod))%=mod;
	for(int x=1;x<=k;x++){
		int ans=0;
		for(int i=0;i<=x;i++) (ans+=(((C(i,x)*sum[i])%mod)*sum[x-i])%mod)%=mod;
		ans=((ans-qpow(2,x,mod)*sum[x]%mod+mod)%mod*inv2%mod)%mod;
		qwe(ans);
	}
	return 0;
}
```

代码常数很低劣，还有不少可以优化的地方。

---

## 作者：lsj2009 (赞：1)

简单推一下柿子：

$$
\begin{aligned}
 & \sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n (a_i+a_j)^x\\
 & =\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n \sum\limits_{k=0}^x {x\choose k}a_i^ka_j^{x-k}\\
 & =\sum\limits_{k=0}^x {x\choose k}\sum\limits_{i=1}^{n-1} a_i^k \sum\limits_{j=i+1}^n a_j^{x-k}\\
 & =\sum\limits_{k=0}^x {x\choose k}\frac{(\sum\limits_{i=1}^{n} a_i^k \sum\limits_{j=1}^n a_j^{x-k})-\sum\limits_{i=1}^n a_i^x}{2}\\
\end{aligned}
$$

设 $s_k=\sum\limits_{i=1}^n a_i^k$。得到：

$$\sum\limits_{k=0}^x {x\choose k}\frac{s_k\cdot s_{x-k}-s_x}{2}$$

然后 $\Theta(nk)$ 预处理一下 $s_i$，再 $\Theta(k)$ 枚举一下 $x$，在 $\Theta(k)$ 直接用上面那个柿子算就好了，复杂度 $\Theta(nk+k^2)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e5+5,M=3e2+5,MOD=998244353,inv2=(MOD+1)/2;
int a[N],b[N],sum[M],jc[M],inv_jc[M],n,k;
int qpow(int a,int b) {
    int res=1,base=a;
    while(b) {
        if(b&1)
            res=res*base%MOD;
        base=base*base%MOD; b>>=1;
    }
    return res;
}
void init() {
    jc[0]=1;
    rep(i,1,k)
        jc[i]=jc[i-1]*i%MOD;
    inv_jc[k]=qpow(jc[k],MOD-2);
    per(i,k-1,0)
        inv_jc[i]=inv_jc[i+1]*(i+1)%MOD;
}
int C(int n,int m) {
    return jc[m]*inv_jc[n]%MOD*inv_jc[m-n]%MOD;
}
signed main() {
    scanf("%lld%lld",&n,&k);
	init();
    rep(i,1,n)
        scanf("%lld",&a[i]),b[i]=1;
    sum[0]=n;
    rep(i,1,k) {
        rep(j,1,n) {
            b[j]=b[j]*a[j]%MOD;
            sum[i]=(sum[i]+b[j])%MOD;
        }
        int res=0;
        rep(j,0,i)
            res=(res+C(j,i)*(sum[j]*sum[i-j]%MOD-sum[i]+MOD)%MOD*inv2%MOD)%MOD;
        printf("%lld\n",res);
    }
    return 0;
}
```

---

## 作者：0xyz (赞：1)

直接推式子。

对于 $1\le x\le k$，我们有

$$\begin{aligned}ans_x&=\sum\limits_{1\le l<r\le n}(a_l+a_r)^x\\&=\frac{1}{2}\sum\limits_{1\le l\ne r\le n}(a_l+a_r)^x\\&=\frac{1}{2}\Big(\sum\limits_{1\le l,r\le n}(a_l+a_r)^x-\sum\limits_{1\le i\le n}(2a_i)^x\Big)\\&=\frac{1}{2}\Big(\sum\limits_{1\le l,r\le n}\sum\limits_{0\le y\le x}C_{x}^{y}a_l^ya_r^{x-y}-\sum\limits_{1\le i\le n}2^xa_i^x\Big)\\&=\frac{1}{2}\Big(\sum\limits_{1\le l,r\le n}\sum\limits_{0\le y\le x}\frac{x!}{y!(x-y)!}a_l^ya_r^{x-y}-\sum\limits_{1\le i\le n}2^xa_i^x\Big)\\&=\frac{1}{2}\Big(x!\sum\limits_{1\le l,r\le n}\sum\limits_{0\le y\le x}\frac{a_l^y}{y!}\frac{a_r^{x-y}}{(x-y)!}-\sum\limits_{1\le i\le n}2^xa_i^x\Big)\end{aligned}$$

我们令 $b_{l,x}=\frac{a_l^x}{x!},c_{x}=\sum\limits_{1\le i\le n}b_{i,x},d_{x}=\sum\limits_{1\le i\le n}2^xa_i^x$，这些东西可以 $O(nk)$ 预处理，那么

$$\begin{aligned}ans_x&=\frac{1}{2}\Big(x!\sum\limits_{1\le l,r\le n}\sum\limits_{0\le y\le x}b_{l,y}b_{r,x-y}-d_x\Big)\\&=\frac{1}{2}\Big(x!\sum\limits_{1\le l\le n}\sum\limits_{1\le r\le n}\sum\limits_{0\le y\le x}b_{l,y}b_{r,x-y}-d_x\Big)\\&=\frac{1}{2}\Big(x!\sum\limits_{0\le y\le x}\sum\limits_{1\le l\le n}b_{l,y}\sum\limits_{1\le r\le n}b_{r,x-y}-d_x\Big)\\&=\frac{1}{2}\Big(x!\sum\limits_{0\le y\le x}\sum\limits_{1\le l\le n}b_{l,y}c_{x-y}-d_x\Big)\\&=\frac{1}{2}\Big(x!\sum\limits_{0\le y\le x}c_{x-y}\sum\limits_{1\le l\le n}b_{l,y}-d_x\Big)\\&=\frac{1}{2}\Big(x!\sum\limits_{0\le y\le x}c_{x-y}c_y-d_x\Big)\end{aligned}$$

这个东西可以 $O(k^2)$ 暴力卷积。也可以用 FFT 优化到 $O(k\log k)$，但是意义不大。

总时间复杂度 $O(nk+k^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353,_=200010;
ll n,k,p[_],q[_],a[_],c[_],d[_],w[_];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;p[0]=q[k]=1;
	for(ll i=1;i<=n;i++)cin>>a[i];
	for(ll i=1;i<=k;i++)p[i]=p[i-1]*i%mod;
	for(ll y=mod-2,x=p[k];y;y>>=1,x=x*x%mod)
		if(y&1)q[k]=q[k]*x%mod;
	for(ll i=k-1;~i;i--)q[i]=q[i+1]*(i+1)%mod;
	for(ll i=1;i<=n;i++)
		for(ll j=0,s=1,t=1;j<=k;j++,s=s*a[i]%mod,t=t*2*a[i]%mod){
			c[j]=(c[j]+s*q[j])%mod;
			d[j]=(d[j]+t)%mod;
		}
	for(ll i=0;i<=k;i++)
		for(ll j=0;j<=k-i;j++)w[i+j]=(w[i+j]+c[i]*c[j])%mod;
	for(ll i=1;i<=k;i++)cout<<(p[i]*w[i]%mod-d[i]+mod)*(mod+1>>1)%mod<<'\n';
	return 0;
}
```

---

## 作者：henrytb (赞：1)

首先，

$$
\sum_{l = 1}^{n - 1}\sum_{r = l + 1}^{n}(a_l + a_r)^x = \frac{\sum\limits_{l = 1}^{n}\sum\limits_{r = 1}^{n}(a_l + a_r)^x - \sum\limits_{i = 1}^{n}(2a_i)^x}{2}
$$

然后对于 $\sum\limits_{i = 1}^{n}\sum\limits_{j = 1}^{n}(a_l + a_r)^x$，可以二项式定理展开。

$$
\begin{aligned}
\sum\limits_{l = 1}^{n}\sum\limits_{r = 1}^{n}(a_l + a_r)^x &= \sum_{l = 1}^{n}\sum_{r = 1}^{n}\sum_{i + j = x}\binom{x}{i}a_l^i a_r^j \\
&= \sum_{i + j = x}\binom{x}{i}\left(\sum_{l = 1}^{n}a_l^i\right)\left(\sum_{r = 1}^{n}a_r^j\right) \\
\end{aligned}
$$

暴力预处理 $b_x = \sum\limits_{i = 1}^{n}a_i^x$，即可快速算出所有答案。

---

## 作者：joke3579 (赞：1)

## $\text{Statement}$

给定长度为 $n$ 的序列 $a$，以及一个整数 $k$。

对于每个 $1\le x \le k$，求出如下式子的值：
$$\sum_{l=1}^{n-1}\sum_{r=l+1}^n \left(a_l + a_r\right)^ x$$

答案对 $998244353$ 取模。

$2\le n \le 2\times 10^5,\ 1 \le k \le 300, \ 1\le a_i \le 10^8$。

## $\text{Solution}$

不难发现，
$$\sum_{l=1}^{n}\sum_{r=1}^n \left(a_l + a_r\right)^x = 2\sum_{l=1}^{n-1}\sum_{r=l+1}^n \left(a_l + a_r\right)^x  +\sum_{l=1}^{n}\left(a_l + a_l\right)^x $$

于是可以计算
$$\sum_{l=1}^{n}\sum_{r=1}^n \left(a_l + a_r\right)^x$$
减去
$$\sum_{l=1}^{n}\left(a_l + a_l\right)^x$$
后除二就是答案。

根据二项式定理，可以得到
$$\begin{aligned} 

&\sum_{l=1}^{n}\sum_{r=1}^n \left(a_l + a_r\right)^x 
\\ = \ & \sum_{l=1}^{n}\sum_{r=1}^n\sum_{i=0}^x \binom{x}{i} a_l^i a_r^{x-i}
\\ = \ & \sum_{i=0}^x \sum_{l=1}^{n}\sum_{r=1}^n\frac{a_l^i}{i!} x!\frac{a_r^{x-i}}{(x - i)!}
\\ = \ & \sum_{i=0}^x x!\left(\sum_{l=1}^{n}\frac{a_l^i}{i!}\right) \left(\sum_{r=1}^n\frac{a_r^{x-i}}{(x - i)!}\right)

\end{aligned}$$

由于 $x$ 的范围小，可以支持 $O(k^2)$ 的复杂度，我们可以枚举 $x$ 和 $i$ 合并答案。

对每个 $1\le m\le k$ 预处理 
$$\sum_{l=1}^{n}\frac{a_l^m}{m!}$$ 
即可做到 $O(k^2)$ 合并答案。合并答案也可应用卷积，但复杂度瓶颈不在这里。

朴素合并的总时间复杂度为 $O(nk + k^2)$。

$\text{code : }$

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> void get(T & x) {
	x = 0; char ch = getchar(); bool f = false; while (ch < '0' or ch > '9') f = f or ch == '-', ch = getchar();
	while ('0' <= ch and ch <= '9') x = (x << 1) + (x << 3) + ch - '0', ch = getchar(); f && (x = -x); 
} template <typename T, typename ... Args> void get(T & a, Args & ... b) { get(a); get(b...); }
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
const int N = 4e5 + 10;
int n, k, sum[305], a[N], v[305];

signed main() {
	get(n, k); rep(i,1,n) get(a[i]);
    init_fac(305);
    v[0] = n;
    rep(j,1,n) {
        int t1 = 1, t2 = 1;
        rep(i,1,k) {
            t1 = mul(t1, a[j]), t2 = mul(t2, 2 * a[j]);
            v[i] = add(v[i], mul(t1, ifc[i]));
            sum[i] = add(sum[i], t2);
        }
    }
    rep(x,1,k) {
        int ans = 0;
        rep(i,0,x) ans = add(ans, mul(v[i], v[x - i]));
        ans = mul(ans, fac[x]);
        ans = sub(ans, sum[x]);
        cout << mul(ans, inv2) << '\n';
    }
}
```

---

## 作者：Ginger_he (赞：0)

发现直接拆开不好做，所以先考虑容斥，

$$\dfrac{1}{2}(\sum_{l=1}^n\sum_{r=1}^n(a_l+a_r)^x-\sum_{i=1}^n(2a_i)^x)$$

然后前半部分二项式定理展开得到

$$\dfrac{1}{2}\sum_{l=1}^n\sum_{r=1}^n\sum_{i=0}^x\binom{x}{i}a_l^ia_r^{x-i}-2^{x-1}\sum_{i=1}^na_i^x$$

交换求和顺序并因式分解得

$$\dfrac{1}{2}\sum_{i=0}^x\binom{x}{i}(\sum_{l=1}^na_l^i)(\sum_{r=1}^na_r^{x-i})-2^{x-1}\sum_{i=1}^na_i^x$$

于是我们先预处理 $a_i$ 的 $x$ 次方和（其中 $x=1,2,\dots,k$），就可以在 $O(k^2)$ 的时间内求出答案了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define M 305
const int p=998244353;
const int inv=499122177;
int n,k,a[N],v[N],s[M],f[M],g[M],t[M],ans;
int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=1ll*res*a%p;
		b>>=1;
		a=1ll*a*a%p;
	}
	return res;
}
int C(int n,int m)
{
	return 1ll*f[n]*g[m]%p*g[n-m]%p; 
}
int main()
{
	scanf("%d%d",&n,&k);
	f[0]=t[0]=1;
	for(int i=1;i<=k;i++)
		f[i]=1ll*f[i-1]*i%p,t[i]=1ll*t[i-1]*2%p;
	g[k]=quickpow(f[k],p-2);
	for(int i=k-1;~i;i--)
		g[i]=1ll*g[i+1]*(i+1)%p;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),v[i]=1;
	s[0]=n;
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++)
			v[j]=1ll*v[j]*a[j]%p,s[i]=(s[i]+v[j])%p;
	}
	for(int i=1;i<=k;i++)
	{
		ans=0;
		for(int j=0;j<=i;j++)
			ans=(ans+1ll*C(i,j)*s[j]%p*s[i-j]%p)%p;
		ans=1ll*ans*inv%p;
		printf("%d\n",((ans-1ll*s[i]*t[i-1]%p)%p+p)%p);
	}
	return 0;
}
```

---

