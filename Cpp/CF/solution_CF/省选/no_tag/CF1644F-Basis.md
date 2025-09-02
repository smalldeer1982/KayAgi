# Basis

## 题目描述

For an array of integers $ a $ , let's define $ |a| $ as the number of elements in it.

Let's denote two functions:

- $ F(a, k) $ is a function that takes an array of integers $ a $ and a positive integer $ k $ . The result of this function is the array containing $ |a| $ first elements of the array that you get by replacing each element of $ a $ with exactly $ k $ copies of that element.For example, $ F([2, 2, 1, 3, 5, 6, 8], 2) $ is calculated as follows: first, you replace each element of the array with $ 2 $ copies of it, so you obtain $ [2, 2, 2, 2, 1, 1, 3, 3, 5, 5, 6, 6, 8, 8] $ . Then, you take the first $ 7 $ elements of the array you obtained, so the result of the function is $ [2, 2, 2, 2, 1, 1, 3] $ .
- $ G(a, x, y) $ is a function that takes an array of integers $ a $ and two different integers $ x $ and $ y $ . The result of this function is the array $ a $ with every element equal to $ x $ replaced by $ y $ , and every element equal to $ y $ replaced by $ x $ .For example, $ G([1, 1, 2, 3, 5], 3, 1) = [3, 3, 2, 1, 5] $ .

An array $ a $ is a parent of the array $ b $ if:

- either there exists a positive integer $ k $ such that $ F(a, k) = b $ ;
- or there exist two different integers $ x $ and $ y $ such that $ G(a, x, y) = b $ .

An array $ a $ is an ancestor of the array $ b $ if there exists a finite sequence of arrays $ c_0, c_1, \dots, c_m $ ( $ m \ge 0 $ ) such that $ c_0 $ is $ a $ , $ c_m $ is $ b $ , and for every $ i \in [1, m] $ , $ c_{i-1} $ is a parent of $ c_i $ .

And now, the problem itself.

You are given two integers $ n $ and $ k $ . Your goal is to construct a sequence of arrays $ s_1, s_2, \dots, s_m $ in such a way that:

- every array $ s_i $ contains exactly $ n $ elements, and all elements are integers from $ 1 $ to $ k $ ;
- for every array $ a $ consisting of exactly $ n $ integers from $ 1 $ to $ k $ , the sequence contains at least one array $ s_i $ such that $ s_i $ is an ancestor of $ a $ .

Print the minimum number of arrays in such sequence.

## 说明/提示

Let's analyze the first example.

One of the possible answers for the first example is the sequence $ [[2, 1, 2], [1, 2, 2]] $ . Every array of size $ 3 $ consisting of elements from $ 1 $ to $ 2 $ has an ancestor in this sequence:

- for the array $ [1, 1, 1] $ , the ancestor is $ [1, 2, 2] $ : $ F([1, 2, 2], 13) = [1, 1, 1] $ ;
- for the array $ [1, 1, 2] $ , the ancestor is $ [1, 2, 2] $ : $ F([1, 2, 2], 2) = [1, 1, 2] $ ;
- for the array $ [1, 2, 1] $ , the ancestor is $ [2, 1, 2] $ : $ G([2, 1, 2], 1, 2) = [1, 2, 1] $ ;
- for the array $ [1, 2, 2] $ , the ancestor is $ [1, 2, 2] $ ;
- for the array $ [2, 1, 1] $ , the ancestor is $ [1, 2, 2] $ : $ G([1, 2, 2], 1, 2) = [2, 1, 1] $ ;
- for the array $ [2, 1, 2] $ , the ancestor is $ [2, 1, 2] $ ;
- for the array $ [2, 2, 1] $ , the ancestor is $ [2, 1, 2] $ : $ F([2, 1, 2], 2) = [2, 2, 1] $ ;
- for the array $ [2, 2, 2] $ , the ancestor is $ [1, 2, 2] $ : $ G(F([1, 2, 2], 4), 1, 2) = G([1, 1, 1], 1, 2) = [2, 2, 2] $ .

## 样例 #1

### 输入

```
3 2```

### 输出

```
2```

## 样例 #2

### 输入

```
4 10```

### 输出

```
12```

## 样例 #3

### 输入

```
13 37```

### 输出

```
27643508```

## 样例 #4

### 输入

```
1337 42```

### 输出

```
211887828```

## 样例 #5

### 输入

```
198756 123456```

### 输出

```
159489391```

## 样例 #6

### 输入

```
123456 198756```

### 输出

```
460526614```

# 题解

## 作者：幻影星坚强 (赞：9)

首先考虑只有 $G$ 时最小的 $m$ 是多少。

显然 $G$ 操作不会改变一个数组不同数的个数。

我们发现对于一个含有 $i$ 个不同数的数组，它能由另外一个含 $i$ 个不同数的数组变换得到，当且仅当对于一个数组的每一种颜色，都在另一个数组存在一种颜色使得它们下标的集合相同，也就是我们将每个下标分配到了某一种颜色，同时颜色是无区别的。它正符合第二类斯特林数的定义，所以对于含 $k$ 个数的数组我们只需要 $\begin{Bmatrix}n \\i\end{Bmatrix}$ 个数组即能全部表示出来。于是对于某一个 $n$ ，我们可以利用二项式反演和卷积通过 $O(n\log n)$ 求出其所有第二类斯特林数。[方法见此](https://www.luogu.com.cn/problem/P5395)。

接下来有了 $F$ 操作，我们发现能由 $F(a,j)$ 这一变换得到的数组，它都满足对于 $[i\times k,\min (n, (i+1)\times k-1)]$ 这一段区间，它的每个数都相同。于是对于每一个 $j$ ，我们可以直接将含有 $i$ 个不同数的方案减去能由 $F(a,j)$ 得到且含有 $i$ 个不同数的方案，而能由 $F(a,j)$ 得到且含有 $i$ 个不同数的方案数即为 $\left\lceil\dfrac{n}{j}\right\rceil$ 个数的数组含有 $i$ 个不同数的方案数，可以 $O(\left\lceil\dfrac{n}{j}\right\rceil\log \left\lceil\dfrac{n}{j}\right\rceil)$ 求得。可以看出一个 $j$ 所算出的方案的会在其倍数再次被算，于是我们利用容斥，我们可以直接求出每一项的容斥系数，或者发现 $j$ 的容斥系数为 $\mu(j)$，复杂度均为 $O(\sum_{i=1}^{n}\left\lceil\dfrac{n}{i}\right\rceil\log \left\lceil\dfrac{n}{i}\right\rceil)=O(n\log^2n)$。

主要代码如下：

```cpp
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	jc[0] = 1;
	
	St.calc(n);
	for (int i = 1; i <= n; ++ i)
	dp[i] = S.a[i], del[i] = -1;
	
	if(min(n, k) >= 2)dp[1] = 0;
	
	for (int i = 2; i <= n; ++ i)
	{
		if(del[i] == 0)continue;
		St.calc((n + i - 1) / i);
		for (int j = 2; j <= (n + i - 1) / i; ++ j)
		{
			(dp[j] += del[i] * S.a[j] + MOD) %= MOD;
		}
		
		for (int j = 2 * i; j <= n; j += i)
		del[j] -= del[i];
	}
	
	long long ans = 0;
	for (int i = 1; i <= min(n, k); ++ i)
	(ans += dp[i]) %= MOD;
	cout << ans;
}
```


---

## 作者：small_john (赞：5)

### 思路

神仙题。

首先考虑没有操作 $F$ 时怎么做。

我们将 $n$ 个数划分为 $k$ 个可以为空的有标号集合，第 $i$ 个集合内的数等于 $i$，此时操作 $G$ 就相当于交换两个集合。可以发现，标号就不重要了，$m$ 应该为将 $n$ 个数划分为 $k$ 个可以为空的**无标号**集合的方案数，用第二类斯特林数表示即为 $\sum\limits_{i=1}^{min(n,k)}\begin{Bmatrix}n \\i\end{Bmatrix}$。

此时加入操作 $F$，对于一个数组，如果每个数相同的极长段（除去最后一段）长度的 $\gcd$ 为 $1$，那么这个数组就一定不能通过操作 $F$ 得到，此时就应该计入答案。

$\gcd$ 为 $1$ 的限制直接做不容易，我们考虑经典容斥。

设 $f(x)$ 表示极长段（除去最后一段）长度都为 $i$ 的倍数是的方案数，那么最后的答案就是 $\sum\limits_{x=1}^{n}\mu(x)f(x)$。

而求 $f(x)$ 是容易的，每 $x$ 个数缩成一个数，最后会缩出来 $\lceil\frac{n}{x}\rceil$ 个，$f(x)$ 就是这些数只做操作 $G$ 时的答案，即 $\sum\limits_{i=1}^{\min(\lceil\frac{n}{x}\rceil,k)}\begin{Bmatrix}\lceil\frac{n}{x}\rceil \\i\end{Bmatrix}$。

此时如果你会 $O(n\log n)$ 的时间复杂度求一行的第二类斯特林数之和（[模板](https://www.luogu.com.cn/problem/P5395)）其实就可以做到 $O(n\ln n\log n)$，虽然足以通过但是还有更优秀的做法。

考虑推式子。

将第二类斯特林数的通项公式代入原式：

$$
f(x)=\sum\limits_{i=1}^{\min(\lceil\frac{n}{x}\rceil,k)}\sum\limits_{j=0}^{i}\frac{(-1)^{i-j}j^{\lceil\frac{n}{x}\rceil}}{j!(i-j)!}
$$

交换枚举顺序：

$$
\sum\limits_{j=0}^{\min(\lceil\frac{n}{x}\rceil,k)}\sum\limits_{i=\max(j,2)}^{\min(\lceil\frac{n}{x}\rceil,k)}\frac{(-1)^{i-j}j^{\lceil\frac{n}{x}\rceil}}{j!(i-j)!}
$$

将只与 $j$ 有关的部分提前：

$$
\sum\limits_{j=0}^{\min(\lceil\frac{n}{x}\rceil,k)}\frac{j^{\lceil\frac{n}{x}\rceil}}{j!}\sum\limits_{i=\max(j,2)}^{\min(\lceil\frac{n}{x}\rceil,k)}\frac{(-1)^{i-j}}{(i-j)!}
$$

设 $i'=i-j$，后面变成枚举 $i'$：

$$
\sum\limits_{j=0}^{\min(\lceil\frac{n}{x}\rceil,k)}\frac{j^{\lceil\frac{n}{x}\rceil}}{j!}\sum\limits_{i'=\max(0,2-j)}^{\min(\lceil\frac{n}{x}\rceil,k)-j}\frac{(-1)^{i'}}{i'!}
$$

预处理阶乘逆元，$\frac{(-1)^{i'}}{i'!}$ 的前缀和，对于每个 $x$ 用线性筛求出 $j^{\lceil\frac{n}{x}\rceil}$（质数使用快速幂，其他的使用一个质数和另一个数的乘积，由于 $n$ 以内质数只有 $O(\frac{n}{\ln n})$ 个，所以还是线性的）。暴力枚举 $j$ 计算即可。

注意特判 $n=1$ 和 $k=1$ 的情况，时间复杂度 $O(n\log n)$，轻松通过。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6+5,mod = 998244353;
int n,k;
inline int qpow(int x,int y)
{
	int res = 1;
	while(y)
	{
		if(y&1) res = res*x%mod;
		y>>=1;
		x = x*x%mod; 
	}
	return res;
}
int fac[N],inv[N],mu[N],p[N],cnt,s[N];
bool vis[N];
inline void init()
{
	fac[0] = inv[0] = 1;
	for(int i = 1;i<N;i++) fac[i] = fac[i-1]*i%mod;
	inv[N-1] = qpow(fac[N-1],mod-2);
	for(int i = N-2;i;i--) inv[i] = inv[i+1]*(i+1)%mod;
	mu[1] = 1;
	for(int i = 2;i<N;i++)
	{
		if(!vis[i]) mu[i] = -1,p[++cnt] = i;
		for(int j = 1;j<=cnt&&i*p[j]<N;j++)
		{
			vis[i*p[j]] = 1,mu[i*p[j]] = -mu[i];
			if(i%p[j]==0)
			{
				mu[i*p[j]] = 0;
				break;
			}
		}
	}
	for(int i = 0;i<N;i++)
	{
		mu[i] = (mu[i]+mod)%mod;
		if(i) s[i] = s[i-1];
		if(i&1) (s[i]+=(mod-1)*inv[i])%=mod; 
		else (s[i]+=inv[i])%=mod;
	}
}
int pw[N];
inline int get(int x)
{
	int now = (n+x-1)/x;
	int lim = min(now,k);
	for(int i = 1;i<=lim;i++) vis[i] = 0;
	cnt = 0;
	pw[1] = 1;
	for(int i = 2;i<=lim;i++) 
	{
		if(!vis[i]) pw[i] = qpow(i,now),p[++cnt] = i;
		for(int j = 1;j<=cnt&&i*p[j]<=lim;j++)
		{
			vis[i*p[j]] = 1,pw[i*p[j]] = pw[i]*pw[p[j]]%mod;
			if(i%p[j]==0) break;
		}
	}
	int res = 0;
	for(int i = 0;i<=lim;i++)
	{
		if(2-i>0) res+=pw[i]*inv[i]%mod*(s[lim-i]-s[2-i-1]);
		else res+=pw[i]*inv[i]%mod*s[lim-i];
		res%=mod;
	}
	return res;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	init();
	cin>>n>>k;
	if(n==1||k==1) return cout<<1,0;
	int ans = 0;
	for(int i = 1;i<=n;i++)
		if(mu[i]) (ans+=mu[i]*get(i))%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：2)

## 思路

抽象做法，我也不知道复杂度对不对，但是可能比较好写？

首先我们要计算的数组个数就是不会被其它数组表示出来的数组个数。

考虑 $G$ 操作实际上帮助我们划分出了若干等价类，对于任意两个等价类里的数组都满足“**每种颜色出现的位置集合的集合**”相同。

如果没有 $F$ 操作，此时的答案就是 $\sum_{i=1}^{\min(n,k)}\begin{Bmatrix} n \\i \end{Bmatrix}$，也就是等价类个数，其中 $\begin{Bmatrix} n \\i \end{Bmatrix}$ 表示第二类斯特林数。

考虑加入 $F$ 操作会怎么样，假如说一个数组 $x$ 能被另一个数组 $y$ 由 $F(y,k)$ 操作得到，那么一定满足：将 $x$ 每 $k$ 个划分一段，划分成 $\lceil \frac{x}{k} \rceil$ 段后每段内的数都相同，并且把每段中的数取一个拼成一个长度为 $\lceil \frac{x}{k} \rceil$ 的序列 $z$，$z$ 是 $y$ 的一个前缀。

![](https://cdn.luogu.com.cn/upload/image_hosting/ofg692q9.png)

所以我们考虑设 $ans_n$ 为要表示所有长度为 $n$ 的序列至少需要多少个长度为 $n$ 的序列。

然后容斥一下，得到：

$$ans_n=\sum_{i=1}^{\min(n,k)}\begin{Bmatrix} n \\i \end{Bmatrix}-\sum_{j=2}^n ans_{\lceil\frac{n}{j}\rceil}$$

直接暴力计算显然复杂度难以接受，然后~~感受一下~~，感觉计算 $n$ 需要用到的 $ans_i$ 个数比较少，所以直接类似杜教筛整除分块，递归然后记忆化就过了。

我在 $n \le 10^4$ 的时候预处理了一下斯特林数，毛估估 $n>10^4$ 的情况很少，通过打表得知大概在 $20 \sim 30$ 个，此时直接暴力 NTT 计算斯特林数即可。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
#define add(x,y) (x=((x+y>=mod)?(x+y-mod):(x+y)))
int const N=2e5+10,mod=998244353;
int n,k,res,S[10005][10005],ans[N];bool vis[N];
inline int get(int x,int y){
	auto it=Board::SecondStirLingLine(x);
    //这里是计算第二类斯特林数一行的值
	int res=0;
	rep(i,1,y) add(res,it[i]);
	return res;
}
inline int work(int n){
	if (vis[n]) return ans[n];
	vis[n]=1;
	if (n<=10000){
		rep(i,1,min(n,k)) add(ans[n],S[n][i]);
	}else ans[n]=get(n,min(n,k));
	for (int l=2,r;l<=n;l=r+1){
        //整除分块
		r=n/(n/l);
		if (n%(n/l)==0) add(ans[n],mod-work(n/l)),++l;
		add(ans[n],mod-1ll*work(n/l+1)*(r-l+1)%mod);
	}
	return ans[n];
}
inline void solve(){
	cin>>n>>k;
	if (n==1 || k==1) return cout<<"1\n",void();
	S[0][0]=1;
	rep(i,1,10000) rep(j,1,min(i,k))
		S[i][j]=(S[i-1][j-1]+1ll*j*S[i-1][j]%mod)%mod;
	cout<<work(n)<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	// cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：UKE_Automation (赞：1)

### CF1644F Basis

[$\text{Link}$](https://codeforces.com/problemset/problem/1644/F)

首先我们先看第一个操作 $F$，这个操作表明对于一个数组，如果除了最后一个连续段以外的所有连续段长度的 $\gcd$ 大于 $1$，那么它就可以被别的数组表示。于是我们希望求出所有 $\gcd=1$ 的数组作为构造出的数组。同时由于 $G$ 操作的存在，我们枚举出连续段之后只需要分组即可，因为不管以什么顺序填进去都是同构的。

那么设 $f(i)$ 表示 $\gcd=i$ 的方案数，$g(i)$ 表示 $i\mid \gcd$ 的方案数，由莫比乌斯反演可得：
$$
g(n)=\sum_{n\mid d} f(d)\Leftrightarrow f(n) =\sum_{n\mid d} \mu(\frac{d}{n}) g(d)
$$
那么答案就是 $f(1)=\sum \mu(d)g(d)$。现在考虑 $g(d)$ 怎么求，我们把 $n$ 每 $d$ 个划分为一段，最后一段看做补齐，那么总段数就是 $\lceil \tfrac{n}{d}\rceil$。只要每段的数字一样就是合法的方案，那么考虑枚举把这些段分成多少组，用第二类斯特林数计算其方案数即可。最后的式子为：
$$
f(1)=\sum_{d=1}^n \mu(d) \sum_{i=2}^{k} {\lceil\tfrac{n}d\rceil \brace i}
$$
注意这里不枚举 $i=1$ 是因为所有数字都相同的情况就只有一个连续段了，而这种情况我们不考虑。那么现在考虑计算这个式子的值。我们每次要求一行上斯特林数的前缀和，其实可以直接 NTT 暴力卷积做，复杂度大概是 $O(\sum \lceil \tfrac{n}{i}\rceil \log \lceil \tfrac{n}{i}\rceil)=O(n\log ^2 n)$ 的，足够通过了。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e5 + 5, Maxm = (1 << 19);
const int Inf = 2e9;
const int Mod = 998244353;
const int G = 3, InvG = 332748118;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b) {int res = 1; for(; b; a = 1ll * a * a % Mod, b >>= 1) if(b & 1) res = 1ll * res * a % Mod; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, k;
int vis[Maxn], tot, prim[Maxn], mu[Maxn];
int fac[Maxn], inv[Maxn];
void init() {
	mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!vis[i]) prim[++tot] = i, mu[i] = -1;
		for(int j = 1, x; (x = i * prim[j]) <= n; j++) {
			vis[x] = 1;
			if(i % prim[j] == 0) {
				mu[x] = 0; break;
			}
			mu[x] = -mu[i];
		}
	}
	fac[0] = 1; for(int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % Mod;
	inv[n] = Inv(fac[n]); for(int i = n; i >= 1; i--) inv[i - 1] = 1ll * inv[i] * i % Mod;
}

int r[Maxm];
void NTT(int *a, int len, int typ) {
	for(int i = 0; i < len; i++) if(i < r[i]) swap(a[i], a[r[i]]);
	for(int h = 1; h < len; h <<= 1) {
		int cur = qpow(typ == 1 ? G : InvG, (Mod - 1) / (h << 1));
		for(int i = 0; i < len; i += (h << 1)) {
			int w = 1;
			for(int j = 0; j < h; j++, w = 1ll * w * cur % Mod) {
				int x = a[i + j], y = 1ll * a[i + j + h] * w % Mod;
				a[i + j] = Add(x, y), a[i + j + h] = Del(x, y);
			}
		}
	}
	if(typ == -1) {
		int iv = Inv(len);
		for(int i = 0; i < len; i++) a[i] = 1ll * a[i] * iv % Mod;
	}
}

int f[Maxm], g[Maxm];
void work(int m) {
	for(int i = 0; i <= m; i++) {
		if(i & 1) f[i] = Mod - inv[i];
		else f[i] = inv[i];
		g[i] = 1ll * inv[i] * qpow(i, m) % Mod;
	}
	int len = 1; while(len <= (m << 1)) len <<= 1;
	for(int i = m + 1; i < len; i++) f[i] = g[i] = 0;
	for(int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) * (len >> 1));
	NTT(f, len, 1), NTT(g, len, 1);
	for(int i = 0; i < len; i++) f[i] = 1ll * f[i] * g[i] % Mod;
	NTT(f, len, -1);
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(n), read(k);
	init();
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(mu[i]) {
			int num = (n - 1) / i + 1;
			work(num); int res = 0;
			for(int j = 2; j <= min(k, num); j++) pls(res, f[j]);
			if(mu[i] == 1) pls(ans, res);
			else sub(ans, res);
		}
	}
	if(ans == 0) ans = 1;
	write(ans);
    Usd();
	return 0;
}

```

---

