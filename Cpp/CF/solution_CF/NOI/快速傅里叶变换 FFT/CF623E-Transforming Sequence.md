# Transforming Sequence

## 题目描述

Let's define the transformation $ P $ of a sequence of integers $ a_{1},a_{2},...,a_{n} $ as $ b_{1},b_{2},...,b_{n} $ , where $ b_{i}=a_{1} | a_{2} | ... | a_{i} $ for all $ i=1,2,...,n $ , where $ | $ is the bitwise OR operation.

Vasya consequently applies the transformation $ P $ to all sequences of length $ n $ consisting of integers from $ 1 $ to $ 2^{k}-1 $ inclusive. He wants to know how many of these sequences have such property that their transformation is a strictly increasing sequence. Help him to calculate this number modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 3
```

### 输出

```
30
```

## 样例 #3

### 输入

```
3 3
```

### 输出

```
48
```

# 题解

## 作者：Rorschachindark (赞：10)

# Transforming Sequence
[题目传送门](https://www.luogu.com.cn/problem/CF623E)
## 思路
差点自闭。。。

我们设$dp[i][j]$表示前面$i$个数的或值有$j$位为一，可以得到转移式:

$$dp[i][j]=\sum_{k=0}^{j} dp[i-1][k]\binom{j}{k}2^{k}$$

这个式子应该很好理解，这里就不进行解释了。

边界条件就是$dp[1][0]=0,dp[1][i]=1(i\le k)$。

我们又发现:

$$dp[n+m][i]=\sum_{j=0}^{i} dp[n][j]\times dp[m][i-j]\binom{i}{j}2^{m\times j}$$

于是，我们就可以使用倍增解决了。即:

$$dp[2n][i]=\sum_{j=0}^{i} dp[n][j]\times dp[n][i-j]\binom{i}{j}2^{n\times j}$$

这都不是难点，其实这道题难点在于任意模数$\text {NTT}$，差点把我搞自闭了。
## $\text {Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define ll long long 
#define MAXN 502151

int quick_pow (int a,int b,int c){
	int res = 1;
	while (b){
		if (b & 1) res = 1ll * res * a % c;
		a = 1ll * a * a % c;
		b >>= 1;
	}
	return res;
}

int inv (int x,int mod){
	return quick_pow (x,mod - 2,mod);
}

int mod = 1e9 + 7,mod1 = 998244353,mod2 = 1004535809,mod3 = 469762049,G = 3;
ll mod_1_2 = 1ll * mod1 * mod2;
int inv1 = inv (mod1,mod2),inv2 = inv (mod_1_2 % mod3,mod3);

struct NewInt{
	int A,B,C;
	NewInt (){}
	NewInt (int _num) : A (_num),B (_num),C (_num) {}
	NewInt (int _A,int _B,int _C) : A (_A),B (_B),C (_C) {}
	NewInt reduce (const NewInt &x){
		return NewInt (x.A + (x.A >> 31 & mod1),x.B + (x.B >> 31 & mod2),x.C + (x.C >> 31 & mod3));
	} 
	NewInt operator + (const NewInt &x){
		return reduce (NewInt (A + x.A - mod1,B + x.B - mod2,C + x.C - mod3));
	}
	NewInt operator - (const NewInt &x){
		return reduce (NewInt (A - x.A,B - x.B,C - x.C));
	}
	NewInt operator * (const NewInt &x){
		return NewInt (1ll * A * x.A % mod1,1ll * B * x.B % mod2,1ll * C * x.C % mod3);
	}
	int get (){
		ll x = 1ll * (B - A + mod2) % mod2 * inv1 % mod2 * mod1 + A;
		return (1ll * (C - x % mod3 + mod3) % mod3 * inv2 % mod3 * (mod_1_2 % mod) % mod + x) % mod;
	}
};

namespace Poly{
	int limit,rev[MAXN << 1];
	NewInt Wn[MAXN << 1 | 1];
	void Init (int N){
		limit = 1;int logn = 0;
		while (limit < N) limit <<= 1,logn ++;
		for (int i = 0;i < limit;++ i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << logn - 1);
		NewInt t = NewInt (quick_pow (G,(mod1 - 1) / limit,mod1),quick_pow (G,(mod2 - 1) / limit,mod2),quick_pow (G,(mod3 - 1) / limit,mod3));
		*Wn = NewInt (1);for (NewInt *i = Wn;i != Wn + limit;++ i) *(i + 1) = *i * t;
	} 
	void NTT (NewInt *a,int type){
		for (int i = 1;i < limit;++ i) if (i < rev[i]) swap (a[i],a[rev[i]]);
		for (int mid = 1;mid < limit;mid <<= 1){
			int t = limit / mid >> 1;
			for (int i = 0;i < limit;i += mid << 1)
				for (int j = 0;j < mid;++ j){
					NewInt W = (type == 1 ? Wn[t * j] : Wn[limit - t * j]);
					NewInt X = a[i + j],Y = W * a[i + j + mid];
					a[i + j] = X + Y,a[i + j + mid] = X - Y;
				}
		}
		if (type == 1) return ;
		NewInt Inv = NewInt (inv (limit,mod1),inv (limit,mod2),inv (limit,mod3));
		for (NewInt *i = a;i != a + limit;++ i) *i = *i * Inv;
	}
};

void Multi (NewInt *a,NewInt *b){
	Poly::NTT (a,1),Poly::NTT (b,1);
	for (Int i = 0;i < Poly::limit;++ i) a[i] = a[i] *b[i];
	Poly::NTT (a,-1);
}

ll n;int k;
NewInt A[MAXN << 1],B[MAXN << 1];

int fac[MAXN];

void Solve (int now){
	if (now == 1){
		A[0] = NewInt (0);
		for (Int i = 1;i <= k;++ i) A[i] = NewInt (inv (fac[i],mod));
		return ;
	}
	Solve (now >> 1);
	B[0] = NewInt (0);
	for (Int i = 1;i <= k;++ i) B[i] = NewInt (1ll * A[i].get() * quick_pow (2,1ll * (now >> 1) * i % (mod - 1),mod) % mod);
	for (Int i = k + 1;i < Poly::limit;++ i) A[i] = B[i] = NewInt (0);
	Multi (A,B);
	if (now & 1){
		B[0] = NewInt (0);
		for (Int i = 1;i <= k;++ i){
			int x = A[i].get();
			A[i] = NewInt (1ll * x * quick_pow (2,i,mod) % mod);
			B[i] = NewInt (inv (fac[i],mod));
		}
		for (Int i = k + 1;i < Poly::limit;++ i) A[i] = B[i] = NewInt (0);
		Multi (A,B);
	}
	for (Int i = 0,x;i <= k;++ i) x = A[i].get(),A[i] = NewInt (x);
}
 
template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

signed main(){
	read (n,k);
	if (n > k){
		puts ("0");
		return 0;
	}
	Poly::Init (k * 2 + 10);
	fac[0] = 1;
	for (Int i = 1;i <= k;++ i) fac[i] = 1ll * fac[i - 1] * i % mod;
	Solve (n);
	int ans = 0;
	for (Int i = 1;i <= k;++ i)	ans = (ans + 1ll * A[i].get() * fac[k] % mod * inv(fac[k - i],mod) % mod) % mod;
	write (ans),putchar ('\n');
	return 0; 
}
```

---

## 作者：_sys (赞：7)

这个题好啊，三篇题解都是不一样的思路！

首先，我们把题意转化为有 $n$ 个集合，$k$ 种元素。每个集合里必须有新的元素，每个集合之前的集合元素可以选择加入或不加入，求不同的集合数。

显然 $n > k$ 时答案为 $0$。

以下默认已特判此情况。

我们考虑递推答案。设 $f_{i, j}$ 表示前 $i$ 个集合，出现了前 $j$ 种元素的方案数（我们假设元素已经从 $1$ 至 $k$ 标号）。则答案为 $\sum _{i=n}^k f_{n, i}\times A_k^i$，其中 $A_k^i$ 为排列数，表示不同的标号方案。

则有

$$f_{i, j}=\sum_{l=i-1}^{j-1} \frac{f_{i-1, l}\times 2^l}{(j-l)!}$$

边界为 $f_{0, 0}=1$。

其中因为已有 $l$ 种元素，每种都可以选或不选，所以乘 $2^l$。因为单个集合里元素由排列关系变为组合关系，所以需要除以 $(j-k)!$。

由于转移都是 $i - 1 \to i$，我们可以除去第一维。则有 

$$f_j=\sum_{l=i-1}^{j-1} \frac{f_l\times 2^l}{(j-l)!}$$

方便起见，我们将 $2^l$ 乘入状态，即 $f_i$ 表示出现了 $i$ 种元素的方案数乘 $2^i$ 的值。则有

$$f_j=2^j\sum_{l=i-1}^{j-1} \frac{f_l}{(j-l)!}$$

最终答案为

$$\sum _{i=n}^k \frac{f_{n, i}\times A_k^i}{2^i}$$

我们观察递推式，发现后面是卷积的形式，我们可以用多项式乘法将其时间复杂度优化至 $O(nk\log k)$。

我们现在考虑如何加速这一过程。发现我们将重复的操作进行了 $n$ 遍，能否进行倍增呢？发现 $2^i$ 难以处理。

我们设 $g_i=\frac 1{i!}$，则有 $f'_i=2^i \sum_j f_jg_{i-j}$。其中 $\ast$ 表示卷积。

$$f'=\sum_i 2^i(\sum_j f_jg_{i-j})x^i=\sum_i (\sum_j f_jg_{i-j})(2x)^i=\sum_i f(2x)\ast g(2x)$$

进行迭代，不难发现最终答案为 $\prod_{i=1}^n g(2^ix)$。这个式子可以进行倍增，设 $P_n(x) =\prod_{i=1}^n g(2^ix)$，则有 $P_{2n}(x)=P_n(x) \ast P_n(2^nx)$。

时间复杂度：$O((n+k)\log n\log k)$。

注意模数为 $10^9+7$，所以还需要一个任意模数 NTT。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;


const int Maxn = 1 << 19 | 5, bloc = 100000;
const long long p1 = 469762049, p2 = 998244353, p3 = 1004535809, p = 1e9 + 7;
int rev[Maxn];
long long fac[Maxn], inv[Maxn], Pow2[Maxn], big_Pow2[Maxn];
void get_rev(int len)
{
	for (int i = 0; i < len; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (len >> 1));
}
long long fast_pow(long long x, long long y, long long mod = p)
{
	long long ans = 1, now = x;
	while (y)
	{
		if (y & 1) ans = ans * now % mod;
		now = now * now % mod;
		y >>= 1;
	}
	return ans;
}
void NTT(long long now[], int len, int p, bool type = false)
{
	long long inv3 = fast_pow(3, p - 2, p);
	get_rev(len);
	for (int i = 0; i < len; i++)
		if (i < rev[i]) swap(now[i], now[rev[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		long long w = fast_pow(type ? inv3 : 3, (p - 1) / (i << 1), p);
		for (int j = 0; j < len; j += (i << 1))
		{
			long long l = 1;
			for (int k = j; k < i + j; k++, l = l * w % p)
			{
				long long x = now[i + k] * l % p, y = now[k];
				now[k] = (x + y) % p;
				now[i + k] = (y - x + p) % p;
			}
		}
	}
	if (type)
	{
		long long inv = fast_pow(len, p - 2, p);
		for (int i = 0; i < len; i++)
			now[i] = now[i] * inv % p;
	}
}
void multi(long long x[], long long y[], long long ans[], int len, int p)
{
	get_rev(len);
	static long long tmpx[Maxn], tmpy[Maxn];
	memcpy(tmpx, x, sizeof(long long[len]));
	memcpy(tmpy, y, sizeof(long long[len]));
	NTT(tmpx, len, p), NTT(tmpy, len, p);
	for (int i = 0; i < len; i++)
		ans[i] = tmpx[i] * tmpy[i] % p;
	NTT(ans, len, p, true);
}
void multi(long long x[], long long y[], int len)
{
	static long long ans1[Maxn], ans2[Maxn], ans3[Maxn];
	multi(x, y, ans1, len, p1), multi(x, y, ans2, len, p2), multi(x, y, ans3, len, p3);
	long long inv_p1 = fast_pow(p1, p2 - 2, p2), inv_p12 = fast_pow(p1 * p2 % p3, p3 - 2, p3);
	for (int i = 0; i < len; i++)
	{
		long long k1 = (ans2[i] - ans1[i] + p2) * inv_p1 % p2;
		long long tmp = (ans1[i] + k1 * p1) % (p1 * p2);
		long long k2 = (ans3[i] - tmp % p3 + p3) * inv_p12 % p3;
		x[i] = (tmp + k2 * p1 % p * p2 % p) % p;
	}
}
long long pow2(int x)
{
	return Pow2[x % bloc] * big_Pow2[x / bloc] % p;
}
long long * work(long long now[], int t, int len)
{
	static long long tmp[Maxn];
	memset(tmp, 0, sizeof(len));
	for (int i = 0; i < len; i++)
		tmp[i] = now[i] * pow2(i * t % (p - 1)) % p;
	return tmp;
}
void poly_pow(long long x[], long long ans[], int y, int len)
{
	int res = 1, Now = 1;
	static long long now[Maxn];
	memcpy(now, x, sizeof(long long[len]));
	ans[0] = 1;
	while (y)
	{
		if (y & 1) multi(ans, work(now, res, len << 1), len << 1), res += Now;
		multi(now, work(now, Now, len << 1), len << 1);
		for (int i = len; i < (len << 1); i++)
			now[i] = ans[i] = 0;
		y >>= 1;
		Now <<= 1;
	}
}
int k;
long long n;
void init(void)
{
	fac[0] = 1;
	for (int i = 1; i <= k; i++)
		fac[i] = fac[i - 1] * i % p;
	inv[k] = fast_pow(fac[k], p - 2);
	for (int i = k - 1; i >= 0; i--)
		inv[i] = inv[i + 1] * (i + 1) % p;
	Pow2[0] = big_Pow2[0] = 1;
	for (int i = 1; i <= bloc; i++)
		Pow2[i] = Pow2[i - 1] * 2 % p;
	for (int i = 1; i <= bloc; i++)
		big_Pow2[i] = big_Pow2[i - 1] * Pow2[bloc] % p;
}
int lower(int x)
{
	int tmp = 1;
	for (; tmp < x; tmp <<= 1);
	return tmp;
}
long long tot, g[Maxn], ans[Maxn];
long long A(int x, int y)
{
	return fac[x] * inv[x - y] % p;
}
int main()
{
	scanf("%lld%d", &n, &k);
	if (n > k)
	{
		puts("0");
		return 0;
	}
	k++;
	init();
	for (int i = 1; i < k; i++)
		g[i] = inv[i];
	poly_pow(g, ans, n, lower(k));
	for (int i = n; i < k; i++)
		(tot += ans[i] * A(k - 1, i) % p * fast_pow(Pow2[i], p - 2) % p) %= p;
	printf("%lld", tot);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

> D. [CF623E Transforming Sequence](https://www.luogu.com.cn/problem/CF623E) *3300

挺没技术含量的一道题。比 CF755G 还要简单的倍增 NTT。

当 $n > k$ 时答案为 $0$，以下默认 $n \leq k$。

设 $f_{i, j}$ 表示前 $i$ 个数或起来二进制上有 $j$ 个 $1$ 的方案数（只是单纯考虑这 $j$ 个 $1$，元素之间无序，且 **忽略掉剩下来 $k - j$ 个位置的存在**），转移为
$$
f_{i, j} = \sum\limits_{p = 1} ^ {j} f_{i - 1, j - p} \dbinom j p 2 ^ {j - p}
$$
含义是从 $j$ 的 $1$ 的位置中选 $p$ 个放新的 $1$，剩下 $2 ^ {j - p}$ 个位置任选。

很好，这很卷积。

把组合数拆掉，有
$$
f_{i, j} = j!\sum\limits_{p = 1} ^ {j} \dfrac{f_{i - 1, j - p}}{(j - p)!} p! 2 ^ {j - p}
$$
答案即 $\sum\limits_{j = 0} ^ k \dbinom k j f_{k, j}$。

这样有了一个做 $n$ 遍卷积的 $\mathcal{O}(nk\log k)$ 过不去做法。

注意到每次转移的式子一模一样，考虑分治。

考察 $f_{i, j}$ 和 $f_{i', j'}$ 两个值，它们会合并到 $f_{i + i', j + j'}$​。尝试探究其系数。

从实际意义角度出发，从 $j + j'$ 个位置中选择 $j$ 个位置归到 $f_{i, j}$ 对应的 $1$，剩下来的位置归到 $f_{i', j'}$ 对应的 $1$。此外，对于后 $i'$ 个下标，每个下标上都有 $j$ 个位置可以自由选。综上，得到 $f_{i, j}$ 和 $f_{i', j'}$ 的合并系数 $\dbinom {j + j'} j 2 ^ {i'j}$。

设 $a + b = i(a, b > 0)$，则转移式即
$$
f_{i, j} = \sum\limits_{p = 0} ^ j f_{a, p} f_{b, j - p} \dbinom j p 2 ^ {bp}
$$
容易写成卷积形式
$$
f_{i, j} = j! \sum\limits_{p = 0} ^ j \dfrac{f_{a, p} 2 ^ {bp}}{p!} \dfrac{f_{b, j - p}}{(j - p)!}
$$

直接取 $i$ 的一半分治递归即可。注意加上记忆化。如果直接递归 $a$ 等于 $i$ 除以 $2$ 下取整，递归 $b = i - a$ 但不加记忆化，可以被卡爆，因为当 $n$ 是奇数时，主定理分析 $T(n) = 2T(\frac n 2) + \mathcal{O}(1)$ 解得要做 $\mathcal{O}(n)$ 次卷积，爆炸。另一种解决方案是直接递归 $a$，当 $i$ 是奇数时先做一遍一步转移卷积得到 $f_b$ 再合并 $f_a$ 和 $f_b$。

要写三模 NTT 或 MTT。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int N = 1 << 16;
const int mod = 1e9 + 7;
int ksm(int a, int b, int p) {
	int s = 1;
	while(b) {
		if(b & 1) s = 1ll * s * a % p;
		a = 1ll * a * a % p, b >>= 1;
	}
	return s;
}
long long n;
int k, ans, rev[N];
int fc[N], ifc[N];
void NTT(vector <int> &a, int op, int p) {
	static ull f[N], w[N];
	for(int i = 0; i < N; i++) f[i] = a[rev[i]];
	for(int k = 1; k < N; k <<= 1) {
		int wn = ksm(op ? 3 : ksm(3, p - 2, p), (p - 1) / k / 2, p); // mod -> p =.= 模数别写错了
		for(int i = w[0] = 1; i < k; i++) w[i] = w[i - 1] * wn % p;
		for(int i = 0; i < N; i += k << 1)
			for(int j = 0; j < k; j++) {
				int y = w[j] * f[i | j | k] % p;
				f[i |j | k] = f[i | j] + p - y, f[i | j] += y;
			}
	}
	int coef = op ? 1 : ksm(N, p - 2, p);
	for(int i = 0; i < N; i++) a[i] = f[i] % p * coef % p;
}
vector <int> conv(vector <int> a, vector <int> b, int p) {
	NTT(a, 1, p), NTT(b, 1, p);
	for(int i = 0; i < N; i++) a[i] = 1ll * a[i] * b[i] % p;
	return NTT(a, 0, p), a;
}
vector <int> operator * (vector <int> a, vector <int> b) { // add operator
	for(int i = N >> 1; i < N; i++) a[i] = b[i] = 0;
	__int128 p[3] = {998244353, 1004535809, 469762049}, M = p[0] * p[1] * p[2];
	vector <int> res[3];
	for(int i = 0; i < 3; i++) res[i] = conv(a, b, p[i]);
	for(int i = 0; i < N; i++) {
		__int128 v = 0;
		for(int j = 0; j < 3; j++) v += res[j][i] * (M / p[j]) * ksm((M / p[j]) % p[j], p[j] - 2, p[j]);
		a[i] = v % M % mod;
	}
	return a;
}
map <int, vector <int>> mp;
vector <int> solve(int n) {
	vector <int> ans(N, 0);
	if(n == 1) {
		for(int i = 1; i <= k; i++) ans[i] = 1;
		return ans;
	}
	if(mp.find(n) != mp.end()) return mp[n];
	int a = n >> 1, b = n - a, pw = ksm(2, b, mod), coef = 1;
	vector <int> f = solve(a), g = solve(b), h;
	for(int i = 1; i <= k; i++) f[i] = 1ll * f[i] * (coef = 1ll * coef * pw % mod) % mod * ifc[i] % mod;
	for(int i = 1; i <= k; i++) g[i] = 1ll * g[i] * ifc[i] % mod;
	h = f * g;
	// for(int i = 1; i <= k; i++) cout << h[i] << endl;
	for(int i = 1; i <= k; i++) h[i] = 1ll * h[i] * fc[i] % mod;
	return mp[n] = h;
}
int main() {
	// freopen("1.in", "r", stdin);
	for(int i = 0; i < N; i++) rev[i] = (rev[i >> 1] >> 1) | (i & 1) << 15;
	for(int i = fc[0] = 1; i < N; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
	ifc[N - 1] = ksm(fc[N - 1], mod - 2, mod);
	for(int i = N - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
	cin >> n >> k;
	if(n > k) puts("0"), exit(0);
	vector <int> res = solve(n);
	for(int i = 1; i <= k; i++) ans = (ans + 1ll * res[i] * fc[k] % mod * ifc[i] % mod * ifc[k - i]) % mod;
	cout << ans << endl;
	return cerr << clock() << endl, 0;
}

/*
2022/4/28
start thinking at 21:26

比 CF755G 还要简单的倍增 NTT.
f_{i, j} 表示 n = i, 有 j 个 1 时的答案.

sb 错误: 下标上界为 k 而不是 n!
mod 和 p 别搞混了. 多模 NTT 不熟练.
老老实实做卷积.
注意 f * g 时 g 要先除掉钦定顺序的 binom(k, j)

=.= 有个地方忘取模了

finish debugging at 23:04
*/
```

---

## 作者：i207M (赞：4)

首先一个很显然的$O(n^2)$DP式子，$dp[i][j]$表示考虑了前i位：

$$dp[i][j]=\sum_{k=1}^{j}{j\choose k}2^{j-k}dp[i-1][j-k]$$

先说说我推这个式子的心路历程：

我们把转移用EGF写出来，就是

$$dp_i(x)=(e^x-1)dp_{i-1}(2x)$$

写下来发现：

$$dp_1(x)=e^x-1$$

$$dp_2(x)=(e^x-1)(e^{2x}-1)$$

以此类推，

$$\begin{aligned}dp_n(x)&=\prod_{i=0}^{n-1} (e^{2^ix}-1)\\&=\sum _{i=0}^{2^n-1}(-1)^{popcount(i)}e^{ix}\end{aligned}$$

注意到最终答案是

$$[x^k]e^xdp_n(x)$$

泰勒展开得到

$$ans=\sum_i^{2^n-1}(-1)^{popcount(i)}(i+1)^k$$

------------

插一个有意思的性质：

$$\sum_i^{2^n-1}(-1)^{popcount(i)}i^k$$

当$n>k$时为0.

如果你在做这道题，你会觉得非常显然；但是如果没有这道题的背景，怎么证？

考虑n元集合，第i个元素的权值为$2^i$，那么$i^k$就是从全集中可重复的选k个，如果这k个的并集不是全集，那么系数和为0，因为$n>k$，所以并集不可能是全集。

--------------

考虑对n倍增，设

$$f(n,k,0)=\sum_i^{2^n-1}[popcount(i)\bmod 2=0]i^k$$

类似的设$f(n,1)$。

那么$n \to 2n$的过程，讨论奇偶组合后，就相当于已知$\sum a^k,\sum b^k$，求$\sum(a+b)^k$，二项式展开，NTT卷积即可。

~~如果这道题模数为998244353我就写了~~

---------------

正常的题解(by ywy)的做法，和我说的本质相同：

![捕获.png](https://i.loli.net/2019/06/11/5cff6ec43a11194983.png)

---

## 作者：Karry5307 (赞：4)

### 题意

给定 $n,k$，求有多少满足以下条件的序列 $A$：

- 对于 $1\leq i\leq n$，$0< A_i< 2^k$。

- 对于 $1<i\leq n$，$B_i>B_{i-1}$。

其中 $B_i$ 为 $A_i$ 的前缀或。

$\texttt{Data Range:}1\leq n\leq 10^{18},1\leq k\leq 3\times 10^4$。

### 题解

题单里的题都做不出来了，这就是我吗/dk

到了最后一步想到了各种东西却想不到倍增，这就是我吗/dk

~~也有可能是自己作死之前学题解做法现在记不起来 自己 yy 了个做法发现做到最后不会了~~

由于某些位如果这 $n$ 个数上这一位都为 $0$ 也能合法，所以先考虑一个弱化的版本：对于每个位，$n$ 个数中至少有一个满足这个位为 $1$。

首先题目的限制相当于对于任意的 $1\leq i\leq n$ ，总存在一个 $j$ 使得前 $i-1$ 个数中的第 $j$ 位都为 $0$，且第 $i$ 个数的第 $j$ 位为 $1$。

所以考虑对于每个数，枚举有多少这样的位。设 $a_i$ 表示第 $i$ 个数中某个位为 $1$ 且前 $i-1$ 个数中某个位为 $0$ 的位的数量，那么显然要满足 $a_i>0$，同时 $a_i$ 的和为 $k$。

考虑第 $i$ 个数中满足条件的 $a_i$ 个位在 $n$ 个数中的填法。首先前 $i-1$ 个数这个位必须取 $0$，然后这个数的这个位必须去 $1$，后面的 $n-i$ 个数的这个位可以任选，所以可以算出这 $a_i$ 个位的贡献，进而推出总的贡献为：

$$\sum\binom{k}{a_1,\cdots,a_n}\prod2^{a_j(n-j)}$$

其中和式枚举的是所有满足条件的序列 $a$。

拆掉多项式系数则可以表示为

$$k!\sum\prod\frac{2^{a_j(n-j)}}{a_j!}$$

如果写的好看一点就是

$$k!2^{nk}\sum\prod\frac{1}{a_j!2^{ja_j}}$$

由于 $\sum a_j=k$，右边的一大坨东西实质上就是 $n$ 个序列的卷积。

考虑对右边使用 GF，注意到

$$\sum\frac{x^i}{i!2^{it}}=e^{\frac{x}{2^t}}$$

但是当 $a_j=0$ 时不合法，贡献为 $0$，所以需要减掉常数项，即

$$\prod_{i=1}^{n}\left(e^{\frac{x}{2^i}}-1\right)$$

~~然后我就不知道这个东西怎么求了~~

设 $F_n(x)$ 为这个式子，那么这个式子可以倍增。具体而言即

$$F_{2n}(x)=F_n(x)F_n\left(\frac{x}{2^n}\right)$$

然后就能方便转移了！但是如果存在若干位置使得没有数在这一位上取 $1$ 又该怎么办呢？这里直接将这些位置枚举出来然后算一下就好了，复杂度 $O(k\log k\log n)$。

代码就不放了，毕竟之前写的东西是学的题解做法，又不是自己现在的做法。

---

## 作者：Soulist (赞：4)

**题意：**


给定 $n$，初始有一个长度为 $n$ 的全 $0$ 串 $s$，接着操作 $k$ 轮，每次选择一个长度为 $n$ 的 $01$ 串 $a$ 操作，令 $s=a|s$，设 $|s|$ 表示其中 $1$ 的数量，那么每次操作后要满足 $|s|$ 单调递增。

求合法的操作方案数，答案对 $998244353$ 取模。


* 与题面的 $n,k$ 刚好是反过来的。


---

- 大概是一个奇怪的容斥做法...

首先我们特判掉 $k>n$ 的情况。

接着考虑操作了 $k$ 次，那么从每个位置上看 $s$ 的值必然是形如 $000111...$

不妨假设这一位上有 $t$ 个 $1$，那么其对答案的贡献为 $2^{t-1}$，如果 $t=0$ 那么贡献为 $1$

所以假设有 $i$ 个位置有值，在不考虑 $|s|$ 单调增的情况下，我们等价于计算 $\sum \prod 2^i=\prod (\sum 2^i)$，所以所有情况权值和为 $\sum_k \binom{n}{k} (\sum 2^i)^k=(\sum 2^i+1)^{n}$

考虑 $|s|$ 单调增的条件，实际上这个条件等价于 $1\sim k$ 上的数均出现至少一次，考虑通过容斥原理来计算，设全集 S 为 $\{1,1,1...k \text{个} 1\}$，我们等价于求：

$$\sum_{T\subseteq S} (-1)^{|S|-|T|}f(T)$$

其中 $f(T)$ 表示集合 $T$ 中的数任意使用的贡献和，那么不妨设 $w(T)$ 为 $\sum_{i\in T}2^i$，则所求为 $f(T)= w(T)^n$

于是我们等价于求：

$$\sum_{T\subseteq S}(-1)^{|S|+|T|}(w(T)+1)^{n}$$

$$(-1)^{|S|}\sum \binom{n}{i}\sum_{T\subseteq S}(-1)^{|T|}w(T)^{i}$$

然后我们考虑通过倍增维护上式，不妨设 $f(z,i)$ 为：

$$f(z,i)=\sum^{2^z-1} (-1)^{|T|}w(T)^i$$

那么考虑：

$$f(2z,i)=\sum^{2^{2z}-1}(-1)^{|T|}w(T)^i$$

$$f(2z,i)=\sum_{T}^{2^z-1}(-1)^{|T|}\sum_S^{2^z-1}(-1)^{|S|}(w(T)+w(S\times 2^z))^i$$

$$f(2z,i)=\sum_{T}^{2^z-1}(-1)^{|T|}\sum_S^{2^z-1}(-1)^{|S|}\binom{i}{j}w(T)^jw(S\times 2^z)^{i-j}$$

将 $f(2z,i)$ 视为关于 $i$ 的指数型生成函数 EGF $F_{2z}(x)$，那么有：

$$F_{2z}=F_{z}(x)F_z(2^zx)$$

我们只需要求出 $F_k[x^i],\{i=1,2\sim n\}$ 就能得到答案了，那么直接多项式倍增即可，复杂度 $O(n\log n\log k)$

讲道理，$10^9+7$ 这个模数真的非人哉。

tips: 代码写了一下午，一开始打算写MTT(4FFT)，最后发现自己调不出来，然后改成了 7FFT /fad，$10^9+7$ 什么的真的是烦死了

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
#define double long double 
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 4e5 + 5 ;
const int P = 1e9 + 7 ; 
const double Pi = acos( -1.0 ) ; 
int n, m, cnt, num, maxn, limit, nAns, L, R[N], Ans[N], Base[N], G[N], base[N], fac[N], inv[N] ; 
struct Complex {
	double x, y ; 
	Complex( double xx = 0, double yy = 0 ) { x = xx, y = yy ; }
	void init() { x = 0, y = 0 ; }
} F[N], Q[N], C[N], A1[N], A2[N], B1[N], B2[N] ; 
Complex Conj( Complex x ) { return Complex( x.x, -x.y ) ; }
int fpow( int x, int k ) {
	int ans = 1, base = x ; 
	while( k ) {
		if( k & 1 ) ans = ans * base % P ;
		base = base * base % P, k >>= 1 ; 
	} return ans ; 
}
Complex operator * ( Complex x, Complex y ) { return Complex( x.x * y.x - x.y * y.y, x.x * y.y + x.y * y.x ) ; }
Complex operator + ( Complex x, Complex y ) { return Complex( x.x + y.x, x.y + y.y ) ; }
Complex operator - ( Complex x, Complex y ) { return Complex( x.x - y.x, x.y - y.y ) ; }
Complex operator / ( Complex x, double y ) { return Complex(x.x / y, x.y / y ) ; }
void FFT( Complex *a, int type ) {
	for( int i = 0; i < limit; ++ i ) if( R[i] > i ) swap( a[R[i]], a[i] ) ;
	for( int k = 1; k < limit; k <<= 1 ) {
		Complex Dw = Complex( cos( Pi / k ), type * sin( Pi / k ) );	
		for( int i = 0; i < limit; i += ( k << 1 ) ) {
			Complex w = Complex( 1, 0 ) ;
			for( int j = i; j < i + k; ++ j, w = w * Dw ) {
				Complex Ny = w * a[j + k], Nx = a[j] ;
				a[j + k] = Nx - Ny,	a[j] = Nx + Ny ; 
			} 
		}
	}	
	if( type != 1 ) rep( i, 0, limit ) a[i] = a[i] / (double)limit ;
}
void init( int x ) {
	limit = 1, L = 0 ; 
	while( limit < x ) limit <<= 1, ++ L ;
	rep( i, 0, limit ) R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
}
void Mul( int *a, int *b, int l ) {
	rep( i, 0, l ) A1[i].x = a[i] / cnt, A2[i].x = a[i] % cnt ; 
	rep( i, 0, l ) B1[i].x = b[i] / cnt, B2[i].x = b[i] % cnt ; 
	FFT( A1, 1 ), FFT( A2, 1 ), FFT( B1, 1 ), FFT( B2, 1 ) ; 
	rep( i, 0, limit ) F[i] = A1[i] * B1[i], Q[i] = ( A1[i] * B2[i] + A2[i] * B1[i] ), C[i] = A2[i] * B2[i] ; 
	FFT( F, -1 ), FFT( Q, -1 ), FFT( C, -1 ) ;
	rep( i, 0, limit ) 
		a[i] = ( (int)(F[i].x + 0.5) % P * num % P + ( (int)(Q[i].x + 0.5) % P * cnt ) % P + (int)(C[i].x + 0.5) % P ) % P,
		F[i].init(), Q[i].init(), C[i].init(), A1[i].init(), A2[i].init(), B1[i].init(), B2[i].init() ; 
	for( re int i = l + l + 1; i <= limit; ++ i ) a[i] = 0 ;
} 
int A[N], B[N] ; 
void Mull( int *a, int *b, int k ) {
	int fs = fpow( 2, k ) ;
	rep( i, 0, limit ) A[i] = a[i] * fpow( fs, i ) % P ; 
	rep( i, 0, limit ) B[i] = b[i] ; 
	Mul( A, B, n ) ;
	rep( i, 0, limit ) a[i] = A[i] % P ; 
	rep( i, n + 1, limit ) a[i] = 0 ; 
	rep( i, 0, limit ) A[i] = 0, B[i] = 0 ;
}
int CC( int x, int y ) {
	return ( y > x ) ? 0 : fac[x] * inv[y] % P * inv[x - y] % P ; 
}
signed main()
{
	m = gi(), n = gi() ; maxn = n + m ; 
	if( m > n ) { puts("0") ; exit(0) ; }
	cnt = 32768, num = cnt * cnt % P ; 
	fac[0] = inv[0] = 1, init(n + n + 1) ; 
	rep( i, 1, limit ) fac[i] = fac[i - 1] * i % P, inv[i] = fpow( fac[i], P - 2 ) ;
	Ans[0] = 1 ; rep( i, 1, limit ) Base[i] = P - inv[i] ; 
	int k = 1, uk = m ; 
	while(m) {
		if( m & 1 ) Mull( Ans, Base, k ) ;
		rep( i, 0, limit ) G[i] = Base[i] ; 
		Mull( Base, G, k ), m >>= 1 ; 
		rep( i, 0, limit ) G[i] = 0 ;  k <<= 1 ; 
	}
	rep( i, 0, n ) nAns = ( nAns + fac[i] * Ans[i] % P * CC( n, i ) % P ) % P ;
	if( uk & 1 ) nAns = P - nAns ; 
	printf("%lld\n", nAns ) ;
	return 0 ;
}
```

---

## 作者：myee (赞：3)

---
### Update
* dp 式没有使用函数形式，否则会与生成函数混淆，请注意。

---
### 前言

手推了好久柿子才推出来，结果最后一步不会，最后看了题解才知道是倍增。

所以，**这算一个教训吧**。

---
### 思路

以下默认 $b_0=0$。

首先 $n>k$ 显然无解，原理是每次 $n$ 加一必然多至少一位值为 $1$。

我们设 $f_{n,k}$ 为**恰好**占用了 $k$ 个二进制位时长度为 $n$ 的序列的方案数。特别的，$n>k$ 时 $f_{n,k}=0$。

由定义，我们有

$$ans=\sum_{i=0}^{k}\binom kif_{n,i}$$

我们发现一个 dp 式：

$$f_{n,k}=\sum_{i=0}^{k-1}\binom ki2^if_{n-1,i}$$

为啥我感觉这个很难想啊（~~因为我最开始没加这个二项式系数，推了 $114514$ 秒后得到了一个假柿子~~），简要说说原理：

* 枚举 $b_{n-1}$ 已经占有的位数 $i$（$f_{n-1,i}$），同时枚举是哪 $i$ 位（$\binom ki$），那么这 $i$ 位 $a_n$ 既可占有亦可不占有（$2^i$）。
* 此外 $k-i$ 位必须占有。

然后，设 $\operatorname{EGF}$：

$$\hat f_n(x)=\sum_{k=0}^{+\infty}f_{n,k}{x^k\over k!}$$

那么：

$$\hat f_n(x)=\sum_{k=0}^{+\infty}{x^k\over k!}\sum_{i=0}^{k-1}{k!\over i!\times(k-i)!}2^i[{x^i\over i!}]\hat f_{n-1}(x)$$

$$=\sum_{k=0}^{+\infty}x^k\sum_{i=0}^{k-1}{1\over (k-i)!}\times{2^i\over i!}[{x^i\over i!}]\hat f_{n-1}(x)$$

$$=\sum_{k=0}^{+\infty}x^k\sum_{i=0}^{k-1}{1\over (k-i)!}[x^i]\hat f_{n-1}(2x)$$

$$=\sum_{i=0}^{+\infty}x^i[x^i]\hat f_{n-1}(2x)\sum_{k=i+1}^{+\infty}x^{k-i}{1\over (k-i)!}$$

$$=\sum_{i=0}^{+\infty}x^i[x^i]\hat f_{n-1}(2x)\sum_{k=1}^{+\infty}{x^k\over k!}$$

$$=(e^x-1)\sum_{i=0}^{+\infty}x^i[x^i]\hat f_{n-1}(2x)$$

$$=(e^x-1)\hat f_{n-1}(2x)$$

即，$\hat f_n(x)=(\exp x-1)\hat f_{n-1}(2x)$。

边界 $\hat f_0(x)=1$。

---

展开来，我们有

$$\hat f_n(x)=\prod_{i=0}^{n-1}(e^{2^ix}-1)$$

而我们要求的，就是

$$ans=\sum_{i=0}^{k}\binom ki[{x^i\over i!}]\hat f_n(x)=k!\sum_{i=0}^{k}{[x^i]\hat f_n(x)\over(k-i)!}$$

因此只要能卷出 $f_n(x) \bmod x^{k+1}$ 就可得答案。

由展开式，我们有：

$$\hat f_{2n}(x)=\hat f_n(x)\times\hat f_n(2^nx)$$

又有

$$\hat f_{2n+1}(x)=\hat f_{2n}(x)\times(e^{2^{2n}x}-1)$$

于是可以倍增或者递归卷出 $\hat f_n(x)$。我采用了后者。

时间复杂度：

$$T(n)=T(\frac n2)+O(n\log n)=O(n\log n)$$

---
### Code

模数 $1000000007$ 太吐了，要 MTT。

![](https://啧.tk/tuu)

代码太长了，扔剪贴板里了。

[链接](https://www.luogu.com.cn/paste/q1rsafsf)。

核心代码的伪代码：

```stein
Integer n,k;
poly f(Integer n)
	if n == 1
		poly ans = "x"
		ans = exp(ans) - 1
		Make deg(ans) = k
		return ans
	poly ans, g
	g = f(n/2)
	ans = g
	Modint w, p
	w = pow(2, n/2)
	p = 1
	for Integer i from 0 to k
		g[i] = g[i] * p
		p = p * w
	ans = ans * g
	Make deg(ans) = k
	if n % 2 == 1
		g = pow(2, n/2) * "x"
		g = exp(g) - 1
		Make deg(g) = k
		ans = ans * g
		Make deg(ans) = k
	return ans
main()
	Input n, k
	if n > k
		Output 0
		return
	poly w = f(n)
	Modint ans
	ans = 0
	for Integer i from n to k
		ans = ans + Inv((k-i)!) * w[i]
	ans = ans * k!
	Output ans
```

---
### 总结

开头说了，我没有想到倍增。

这题说明了**如何快速卷出出自倍增式的多项式组的指定项**。

这确实算是一个教训吧。


---

## 作者：Vocalise (赞：3)

首先考虑题目含义：给出元素个数 $k$ 和集合个数 $n$，从 $1$ 到 $n$ 每一个集合保留前一个集合的所有元素，且至少加入一个前一个集合不存在的元素。求集合序列数。

然后考虑DP。状态的设计需要注意，不妨提出题目中的若干要素：

- 集合是顺序的；
- 元素是标号（有序）的。

所以我们考虑如下状态。

设 $f_{i,j}$ 表示前 $i$ 个集合中**选了 $j$ 个** 元素的方案数。

这里表示的元素是无序的。所以可以得到答案的式子为

$$ans=\sum_{i=1}^{k}\binom ki f_{n,i}$$

无序选出的 $i$ 个元素乘上一个组合给它们标号。

发现若 $n > k$ 到某一个位置时集合就一定会选满，答案为 $0$。$f_{i,j}$ 当 $i > j$ 时也应该为 $0$。但这并不影响我们递推。 

首先有一个式子

$$f_{n,i}=\sum_{j=0}^{i}f_{n-1,j}\binom ij2^j$$

表示上一个集合已经有 $j$ 个元素，剩下 $i-j$ 个元素必须选。乘上组合数确定已选元素的位置后，它们在该集合中可选可不选有 $2^j$ 种方案。

于是得到一个 $O(n^3)$ 的做法。考虑到 $n$ 的大小，我们想到倍增。

首先，根据上式，进一步得到如下式子：

$$f_{n+m,i}=\sum_{j=0}^{i}f_{n,j}\times f_{m,i-j}\binom ij2^{mj}$$

该式意义类似，表示 $n$ 个集合后追加 $m$ 个集合，就自然有 $m\times j$ 个位置可选可不选。

根据倍增FFT的方法，就可以写出再一个重要的式子：

$$f_{2n,i}=\sum_{j=0}^{i}f_{n,j}\times f_{n,i - j}\binom ij2^{nj}$$

又有初始状态 $f_{1,0}=0,f_{1,i}=1,i\in[1,k]$。

于是我们有了从 $f_n$ 推知 $f_{n+1}$ 和 $f_{2n}$ 的方法。如果这两个步骤都是一次多项式乘法就可以做到的，那问题就解决了。

首先在乘积中有一个组合数。~~阅读[这篇文章](https://www.luogu.com.cn/blog/void-basic-learner/generating-function-preview)最后一段后~~发现，固然我们可以拆开组合数，即

$$f_{n,i}=i!\sum_{j=0}^i\frac{f_{n-1,j}2^j}{j!}\times \frac{1}{(i-j)!}$$

也可以推想如果我们一开始就设定 $f_{i,j}$ 为其原本意义乘 $\frac 1{j!}$，就可以自然地忽略式子中的组合数。初始状态便设为 $f_{1,0}=0,f_{1,i}=\frac 1{i!},i\in[1,k]$。

当然答案也变成

$$ans=\sum_{i=1}^{k}f_{n,i}\times A(k,i)$$

就是了。

于是使用倍增FFT方便地解决了该题。具体地，对于一个 $n$ ，若为 $1$，构造初始数列返回；否则递归 $\lfloor\frac n2\rfloor$。如果 $n$ 为奇数，按照普通的一阶递推式推一次。

一共 $O(\log n)$ 次倍增 $O(k\log k)$，最多 $O(\log n)$ 次一阶递推 $O(k\log k)$。总复杂度是 $O(k\log k\log n)$ 的。

以及，因为有奇怪的模数，这里使用 $4$ 次DFT的MTT作乘法。

代码如下，欢迎提问。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

typedef long long ll;
typedef long double ldb;
const int p = 1000000007;
const int MAXN = 1000001;
const int B = 1 << 15;
const ldb pi = acos(-1);

inline ll read() {
    ll x = 0,f = 1; char ch = getchar();
    while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
    do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
    return x * f;
}

int fac[MAXN],ifac[MAXN];
int f[MAXN],g[MAXN];

struct Complex
{
    ldb x,y;
    Complex() { x = y = 0; }
    Complex(const ldb _x,const ldb _y) : x(_x), y(_y) {}
    Complex operator +(const Complex a) { return Complex(x + a.x,y + a.y); }
    Complex operator -(const Complex a) { return Complex(x - a.x,y - a.y); }
    Complex operator *(const Complex a) { return Complex(x * a.x - y * a.y,x * a.y + y * a.x); }
    Complex operator *(const ldb t) { return Complex(x * t,y * t); }
    Complex operator /(const ldb t) { return Complex(x / t,y / t); }
};

Complex I(0,1);

ll n;
int k,r[MAXN]; Complex wn[MAXN];
Complex a0[MAXN],a1[MAXN],b0[MAXN],b1[MAXN];
Complex P[MAXN],Q[MAXN];

int pow2(int b) {
	int res = 1,a = 2;
	while(b) {
		if(b & 1) res = 1ll * res * a % p;
		a = 1ll * a * a % p;
		b >>= 1;
	}
	return res;
}

void FFT(Complex *a,int N) {
    for(int i = 0;i < N;i++) if(i < r[i]) std::swap(a[i],a[r[i]]);
    Complex t1,t2;
    for(int n = 2, m = 1;n <= N;m = n, n <<= 1)
        for(int l = 0;l < N;l += n)
            for(int i = l;i < l + m;i++) {
                Complex w = wn[N / m * (i - l)];
                t1 = a[i], t2 = w * a[i + m];
                a[i] = t1 + t2;
                a[i + m] = t1 - t2;
            }
    return;
}

void IFFT(Complex *a,int N) {
    FFT(a,N);
    std::reverse(a + 1,a + N);
    for(int i = 0;i < N;i++) a[i] = a[i] / N;
    return;
}

void ConnectFFT(Complex *a,Complex *b,int N) {
    for(int i = 0;i < N;i++) a[i].y = b[i].x;
    FFT(a,N);
    b[0] = Complex(a[0].x,-a[0].y);
    for(int i = 1;i < N;i++) b[i] = Complex(a[N - i].x,-a[N - i].y);
    Complex t1,t2;
    for(int i = 0;i < N;i++) {
        t1 = a[i], t2 = b[i];
        a[i] = (t1 + t2) / 2.0;
        b[i] = (t2 - t1) * I / 2.0;
    }
    return;
}

ll rd(const ldb x) {
    if(x >= 0) return ll(x + 0.5) % p;
    else return ll(x - 0.5) % p;
}

void MTT(int *a,int *b,int n,int N) {
    for(int i = 0;i <= N;i++) a0[i].x = a[i] / B, a1[i].x = a[i] % B;
    for(int i = 0;i <= N;i++) b0[i].x = b[i] / B, b1[i].x = b[i] % B;
    for(int i = 0;i < N;i++) wn[i] = Complex(cos(pi / N * i),sin(pi / N * i));
    ConnectFFT(a0,a1,N); ConnectFFT(b0,b1,N);
    for(int i = 0;i < N;i++) {
        P[i] = a0[i] * b0[i] + I * a1[i] * b0[i];
        Q[i] = a0[i] * b1[i] + I * a1[i] * b1[i];
    }
    IFFT(P,N); IFFT(Q,N);
    for(int i = 0;i < n;i++) a[i] = ((1ll * B * B % p * rd(P[i].x) % p + B * rd(Q[i].x + P[i].y) % p) % p + rd(Q[i].y)) % p;
	return;
}

void Solve(int k,int n,int N) {
	if(k == 1) {
		f[0] = 0;
		for(int i = 1;i < n;i++) f[i] = ifac[i];
		return;
	}
	Solve(k >> 1,n,N);
	g[0] = 0;
	for(int i = 1;i < n;i++) g[i] = 1ll * f[i] * pow2(1ll * (k >> 1) * i % (p - 1)) % p;
	MTT(f,g,n,N);
	if(k & 1) {
		g[0] = 0;
		for(int i = 1;i < n;i++) f[i] = 1ll * f[i] * pow2(i) % p;
		for(int i = 1;i < n;i++) g[i] = ifac[i];
		MTT(f,g,n,N);
	}
	return;
}

int main() {
    n = read(), k = read();
	if(n > k) return std::puts("0"), 0; // 之所以还要判，是因为 n 太大，没办法直接算了，否则会MLE。
	fac[0] = ifac[0] = ifac[1] = 1;
    int N = 1, l = -1; while(N <= (k + 1) << 1) N <<= 1, l++;
    for(int i = 1;i < N;i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l);
	for(int i = 1;i < N;i++) fac[i] = 1ll * fac[i - 1] * i % p;
	for(int i = 2;i < N;i++) ifac[i] = 1ll * ifac[p % i] * (p - p / i) % p;
	for(int i = 1;i < N;i++) ifac[i] = 1ll * ifac[i - 1] * ifac[i] % p;
	Solve(n,k + 1,N);
	ll ans = 0;
	for(int i = 1;i <= k;i++) ans = (ans + 1ll * f[i] * fac[k] % p * ifac[k - i] % p) % p;
	std::printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：_Sein (赞：3)

我怎么感觉只有一篇题解(那篇涉及EGF的)我能理解呢？~~其他都是逆向题解吗~~

-------

还是首先先推式子，设 $f_{i,j}$ 表示前 $i$ 个数，有 $j$ 个 $1$ (无关于具体位置)的方案数。

由于无关于具体位置，那么答案为 $\sum\limits_{i=n}^{k}f_{n,i}*\dbinom{k}{i}$

考虑递推:

$$f_{i,j}=\sum\limits_{l=1}^{j-1}f_{i-1,l}\dbinom{j}{l}2^{l}$$

意义为:选择一个 $a_i$ ，使得 $b_i$ 有 $j$ 个 $1$ ，$a_1|a_2|\ldots|a_{i-1}$ 已经包含了 $l$ 个，那么 $a_i$ 必须包含除这 $l$ 个之外的位置的 $1$ ，相当于有 $j$ 个数，让你从中选出 $j-l$ 个数， 就可以得到方案数 $\dbinom{j}{l}$ 。然后 $a_i$ 还可以选择性的含有 $l$ 中 $1$ ，即 $2^l$ 。

显然这个式子可以卷积，也很容易得到 $EGF$。

$F_{n-1}(x)=\sum\limits_{i}f_{n-1,i}\frac{x^i}{i!},e^x-1=\sum\limits_{i}\frac{x^i}{i!}$

观察上述转移方程，实际上 $F_{n}(x)=\sum_{i}(\sum_{j}2^j\dbinom{i}{j}f_{n-1,j})\frac{x^i}{i!}=(e^x-1)F_{n-1}(2x)$

($F(cx)=\sum_ic^i\frac{x^i}{i!}$)

$F_{n-1}(2x)=(e^{2x}-1)F_{n-2}(4x)$

如此往复下去，就可以得到这样一个优美的式子，

$F_{n}=\prod\limits_{i=0}^{n-1}(e^{2^ix}-1)$

边界: $F_0=0,F_{1}=e^x-1$

之后就是套路倍增，关于这一步，大部分题解里面的解释都是口胡或者是感性的理解，所以我们来推一下吧！

$\begin{aligned}F_{2n}&=\prod\limits_{i=0}^{2n-1}(e^{2^ix}-1)\\&=\prod\limits_{i=0}^{n-1}(e^{2^ix}-1)\prod\limits_{i=0}^{n-1}(e^{2^{n+i}x}-1)\\&=\prod\limits_{i=0}^{n-1}(e^{2^ix}-1)\prod\limits_{i=0}^{n-1}(e^{2^i2^nx}-1)\end{aligned}$ 

观察后式，完全可以换元 $u=2^nx$

$\begin{aligned}F_{2n}&=F_n(x)F_n(u)\\&=F_n(x)F_{n}(2^nx)\end{aligned}$

展开回原式:

其中 $F_n(2^nx)$ 展开是这样的:

$\large\sum\limits_{i}2^{in}\frac{x^i}{i!}$

于是卷积之后为:

$\large f_{2n,i}\frac{x^{i}}{i!}=(\sum\limits_j\dbinom{i}{j}2^{jn}f_{n,j}f_{n,i-j})\frac{x^{i}}{i!}$

同样地，也可以卷积，记得用MTT。

优化细节自己想吧，不想卡常了。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<map>
#include<cstdlib>
#include<vector> 
#define gc getchar()
#define ll long long
#define ull unsigned long long
#define file(s) freopen(s".in","r",stdin);freopen(s".out","w",stdout)
#define I inline 
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n)) 
using namespace std;
const int N=4e5+5,mod=1e9+7,M=1<<15;
const double pi=acos(-1);
template<class o>I void qr(o &x)
{
    char c=gc;int f=1;x=0;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc;}
    while(c>='0'&&c<='9'){x=x*10+(c^48);c=gc;}
    x*=f;
}
template<class o>I void qw(o x)
{
    if(x<0)x=-x,putchar('-');
    if(x/10)qw(x/10);
    putchar(x%10+48);
}
I int ksm(int a,int b=mod-2){int ans=1;for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;return ans;}
struct cp
{
	double x,y;
	cp(double x=0.0,double y=0.0):x(x),y(y){}
	I cp operator +(const cp &a)const{return cp(x+a.x,y+a.y);}
	I cp operator -(const cp &a)const{return cp(x-a.x,y-a.y);}
	I cp operator *(const cp &a)const{return cp(x*a.x-y*a.y,x*a.y+y*a.x);}
	I cp operator /(const double &a)const{return cp(x/a,y/a);}
	I cp operator *(const double &a)const{return cp(x*a,y*a);}
	I cp operator +(const double &a)const{return cp(x+a,y+a);}
}w[N<<1];
cp Ii=cp(0,1);
int tr[N<<1],cnt;
I void rev(int n)
{
	if(cnt==n)return ;cnt=n;
	for(int i=0;i<n;i++)tr[i]=(tr[i>>1]>>1|((i&1)?n>>1:0));
}
I void Init(int n){for(int i=1;i<n;i<<=1){w[i]=cp(1,0);for(int j=1;j<i;j++)w[i+j]=(((j&31)==1)?cp(cos(pi*j/i),sin(pi*j/i)):w[i+j-1]*w[i+1]);}}
void dft(cp *g,bool op,int n)
{
	rev(n);
	static cp f[N<<1],t;
	for(int i=0;i<n;i++)f[i]=g[tr[i]];
	for(int p=2,l=1;p<=n;l=p,p<<=1)
		for(int i=0;i<n;i+=p)for(int j=0;j<l;j++)
			t=w[j|l]*f[i|j|l],f[i|j|l]=f[i|j]-t,f[i|j]=f[i|j]+t;
	if(op)for(int i=0;i<n;i++)g[i]=f[i]/n;
	else for(int i=0;i<n;i++)g[i]=f[i];
}
cp a0[N<<1],a1[N<<1],b0[N<<1],b1[N<<1],p[N<<1],q[N<<1];
void calc(cp *a,cp *b,int n)
{
	for(int i=0;i<n;i++)p[i]=a[i]+Ii*b[i];
	dft(p,0,n);q[0]=cp(p[0].x,-p[0].y);
	for(int i=1,j=n-1;i<n;i++,j--)q[i]=cp(p[j].x,-p[j].y);
	for(int i=0;i<n;i++)a[i]=(p[i]+q[i])*0.5,b[i]=(q[i]-p[i])*0.5*Ii;
}
ll num(double x){return x<0?(ll)(x-0.49)%mod:(ll)(x+0.49)%mod;}
void mtt(int *f,int *g,int m)
{
	int n=1;for(;n<(m<<1);n<<=1);
	for(int i=0;i<m;i++)a0[i]=cp(f[i]>>15,0),a1[i]=cp(f[i]&(M-1),0);
	for(int i=0;i<m;i++)b0[i]=cp(g[i]>>15,0),b1[i]=cp(g[i]&(M-1),0);
	for(int i=m;i<n;i++)a0[i]=a1[i]=b0[i]=b1[i]=cp(0,0);
	
	calc(a0,a1,n);calc(b0,b1,n);
	for(int i=0;i<n;i++)p[i]=a0[i]*b0[i]+Ii*a1[i]*b0[i],q[i]=a0[i]*b1[i]+Ii*a1[i]*b1[i];
	reverse(p+1,p+n),reverse(q+1,q+n);
	dft(p,1,n),dft(q,1,n);
	for(int i=0;i<m;i++)f[i]=(1ll*M*M%mod*num(p[i].x)%mod+1ll*M*num(p[i].y+q[i].x)%mod+num(q[i].y)+4ll*mod)%mod;
	for(int i=m;i<n;i++)f[i]=0;
}
int f[N],sav[N],g[N];//f[i]->f[i]/i!
int fac[N],ifac[N],k,dfac[N],pw[N];
void init(int m)
{	
	fac[0]=ifac[0]=pw[0]=1;for(int i=1;i<=m;i++)fac[i]=1ll*fac[i-1]*i%mod,pw[i]=pw[i-1]*2%mod;
	dfac[0]=1;for(int i=1;i<=m;i++)dfac[i]=1ll*dfac[i-1]*(k-i+1)%mod;
	ifac[m]=ksm(fac[m]);for(int i=m-1;i;i--)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
void add(int m)
{
	for(int i=1;i<m;i++)f[i]=1ll*f[i]*pw[i]%mod*ifac[i]%mod;
	mtt(f,sav,m);
	for(int i=1;i<m;i++)f[i]=1ll*f[i]*fac[i]%mod;
}
void mul(int l,int m)
{
	for(int i=1;i<m;i++)f[i]=1ll*f[i]*ifac[i]%mod;cpy(g,f,m);
	for(int i=1;i<m;i++)f[i]=1ll*f[i]*ksm(pw[l],i)%mod;
	mtt(f,g,m);
	for(int i=1;i<m;i++)f[i]=1ll*f[i]*fac[i]%mod;
}
int C(int n,int m)
{
	if(n<m)return 0;
	return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
ll n;
int main()
{
	qr(n),qr(k);int t=n;
	if(n>k){puts("0");return 0;}
	init(k);
	int m=k+1;
	for(n=1;n<(m<<1);n<<=1);
	Init(n);for(int i=1;i<m;i++)f[i]=1,sav[i]=ifac[i];
	int lg=log2(t),j=1;
	for(int i=lg-1;~i;i--)
	{
		mul(j,m);j<<=1;
		if(t&(1<<i))
			add(m),j|=1;
	}
	ll ans=0;
	for(int i=1;i<=k;i++)
		ans=(ans+1ll*f[i]*C(k,i)%mod)%mod;
	qw(ans);puts("");
	return 0;
}
 
```

---

## 作者：LastKismet (赞：2)

# Sol
考虑设计 DP，令 $f_{i,j}$ 表示长为 $i$ 的合法序列或和为 $2^j-1$ 的方案数。

先不说转移，这个状态一眼看上去难以转化为答案，但实际上并不困难。答案可以表示为：
$$
\sum_{j=1}^k \binom{k}{j}f_{n,j}
$$
考虑在 $k$ 位中选出 $j$ 位，其余位显然可以不考虑，此时这种情况的方案等价于凑出 $2^j-1$ 的方案。

然后考虑转移，我们先给出递推式：
$$
f_{n,k}=\sum_{i=1}^{k-1}f_{n-1,i}\binom{k}{i}2^i
$$

接下来解释这个式子，想凑出 $k$ 位 $1$，可以枚举上一步凑出了多少 $1$，$\binom{k}{i}$ 即为上一步凑出的 $1$ 在当前结果中的位置。但我们需要考虑数列中两个数存在一些位均为 $1$ 的重合情况，不难发现对于这一步的新数而言，上一步已经凑出的 $1$ 的位置，其可以任意为 $1$ 或 $0$，共 $2^i$ 种情况。由于严格单调递增，这里 $i$ 的枚举上限应为 $k-1$。严格上来说下限应为 $n-1$，但考虑不合法情况 $f_{n-1,i}=0$，不会造成影响。

但这样一层层枚举显然会 T 爆，我们发现其实不用一位一位加入新点，而可以把一个序列视作两个序列的拼接，于是可得：

$$
f_{x,y}=\sum_{n=0}^{x}\sum_{m=0}^{x}\sum_{i=0}^y\sum_{j=0}^y\left[n+m=x\land i+j=y\right]f_{n,i}f_{m,j}\binom{y}{i}2^{mi}
$$

其余定义是类似的，我们只额外讲一下最后 $2^{mi}$ 的含义。假令长 $m$ 的序列为新拼接入的序列，那么对于其每个元素，$i$ 个原先为 $1$ 的位均可自由选择，于是就有了 $2^{mi}$ 种情况。这里的上下界均宽松，因为不合法状态 $f=0$ 所以没有影响。

到这里其实已经很简单了，上面很显然是一个卷积状物，下面详细讲解一下卷积部分。

展开可得：
$$
\begin{align*}
&\sum_{i=0}^y\sum_{j=0}^y\left[i+j=y\right]f_{n,i}f_{m,j}\binom{y}{i}2^{mi}\\
=&y!\sum_{i=0}^y\sum_{j=0}^y\left[i+j=y\right]\frac{f_{n,i}2^{mi}}{i!}\cdot\frac{f_{m,j}}{j!}
\end{align*}
$$

为了方便，我们转为维护 $f'_{i,j}=\frac{f_{i,j}}{j!}$，同时额外维护 $\frac{f_{n,i}2^{mi}}{i!}$，显然可以在每次转移前得到 $m$ 的值。

然后就很简单了，倍增即可。卷积部分需要使用 MTT。

# Code
```cpp
namespace MTT{
    int P=1e9+7;
    struct clx{
        flt x,y;
        clx(flt a=0,flt b=0){x=a,y=b;}
        inline clx operator+=(const clx &b){return x+=b.x,y+=b.y,*this;}
        friend inline clx operator+(clx a,clx b){return a+=b;}
        inline clx operator-=(const clx &b){return x-=b.x,y-=b.y,*this;}
        friend inline clx operator-(clx a,clx b){return a-=b;}
        inline clx operator*=(const clx &b){return *this=clx(x*b.x-y*b.y,x*b.y+y*b.x);}
        friend inline clx operator*(clx a,clx b){return a*=b;}
        inline clx operator!(){return clx(x,-y);}
    };
    typedef vec<ll> poly;
    typedef vec<clx> Poly;
    const flt Pi=acos(-1);
    vec<int> Rt;
    inline void fft(int lim,Poly &a,int type){
        repl(i,0,lim)if(i<Rt[i])swap(a[i],a[Rt[i]]);
        for(int mid=1;mid<lim;mid<<=1){
            clx w1(cos(Pi/mid),type*sin(Pi/mid));
            for(int j=0;j<lim;j+=(mid<<1)){
                clx w(1,0);
                repl(k,0,mid){
                    clx x=a[j+k],y=w*a[j+mid+k];
                    a[j+k]=x+y;
                    a[j+mid+k]=x-y;
                    w=w*w1;
                }
            }
        }
    }
    inline void operator*=(poly &x,poly y){
        int n=x.size(),m=y.size(),M=ceil(sqrt(P));
        int lim=1,l=0,len=n+m-1;
        while(lim<len)lim<<=1,l++;
        Rt.resize(lim);
        repl(i,0,lim)Rt[i]=(Rt[i>>1]>>1)|((i&1)<<(l-1));
        Poly p(lim),q(lim),s(lim),t(lim);
        x.resize(lim),y.resize(lim);
        repl(i,0,lim)p[i]=clx(x[i]/M,x[i]%M),q[i]=clx(y[i]/M,y[i]%M);
        fft(lim,p,1);fft(lim,q,1);
        repl(i,0,lim){
            clx ka=(p[i]+!p[i?lim-i:i])*clx(0.5,0);
            clx ba=(p[i]-!p[i?lim-i:i])*clx(0,-0.5);
            clx kb=(q[i]+!q[i?lim-i:i])*clx(0.5,0);
            clx bb=(q[i]-!q[i?lim-i:i])*clx(0,-0.5);
            s[i]=ka*kb+ka*bb*clx(0,1);
            t[i]=ba*kb+ba*bb*clx(0,1);
        }
        fft(lim,s,-1);fft(lim,t,-1);
        repl(i,0,lim){
            ll a=(ll)(s[i].x/lim+0.5)%P;
            ll b=(ll)(s[i].y/lim+0.5)%P;
            ll c=(ll)(t[i].x/lim+0.5)%P;
            ll d=(ll)(t[i].y/lim+0.5)%P;
            x[i]=a*M*M%P+(b+c)*M%P+d,x[i]%=P;
        }
        x.resize(len);
        for(auto &i:x)i=(i+P)%P;
    }
    inline void operator+=(poly &a,poly b){
        if(a.size()<b.size())a.resize(b.size());
        repl(i,0,b.size())a[i]=a[i]+b[i],a[i]%=P;
    }
    inline void operator-=(poly &a,poly b){
        if(a.size()<b.size())a.resize(b.size());
        repl(i,0,b.size())a[i]=a[i]-b[i]+P,a[i]%=P;
    }
    poly operator*(poly a,poly b){return a*=b,a;}
    poly operator+(poly a,poly b){return a+=b,a;}
    poly operator-(poly a,poly b){return a-=b,a;}
}using namespace MTT;

const int T=65,N=3e4+5;

ll n;int k;
poly f[T],g[T],ans;
mint jc[N],iv[N];

inline void Main(){
    read(n,k);
    f[0].resize(k+1);g[0].resize(k+1);
    rep(j,1,k)f[0][j]=iv[j].x,g[0][j]=(f[0][j]*((mint)2^j)).x;
    int tt=__lg(n);
    rep(t,1,tt){
        f[t]=g[t-1]*f[t-1];f[t].resize(k+1);
        g[t].resize(k+1);rep(j,1,k)g[t][j]=(f[t][j]*((mint)2^(1ll<<t)^j)).x;
    }
    ans.resize(k+1);
    ans[0]=1;
    rep(t,0,tt)if(n&1ll<<t){
        rep(j,1,k)ans[j]*=((mint)2^(1ll<<t)^j).x,ans[j]%=P;
        ans*=f[t];ans.resize(k+1);
    }
    mint res=0;
    rep(i,1,k)res+=ans[i]*jc[i]*jc[k]*iv[i]*iv[k-i];
    put(res);
}
```

---

## 作者：liangzihao (赞：2)

由于可能有冲突，以下均用$m$来代替题目中的$k$。

要想$B$严格单调，显然插入的这个数至少有一个位置是$1$，而之前全部数该位置都是$0$。

这样就说明了，当$n>m$时，无解。

首先考虑dp，设$f[i][j]$为取了$i$个数，其中有$j$个位置是$1$的方案数，这里不考虑$1$的位置。
那么答案就是$\sum_{i=0}^{m}f[n][i]*\binom{m}{i}$，可以理解为从$m$位选出$i$位是$1$的所有方案乘上$f[i][j]$，还是要记住$f[i][j]$的定义。
可以这样转移：
$$f[i][j]=\sum_{k=0}^{j-1}f[i-1][k]*\binom{j}{k}*2^{k}$$
其中，$\binom{j}{k}$表示从$j$个$1$中哪$k$个位置前面已经占用，而$2^{k}$表示能填的数的个数。显然，那已经占用的$k$的位置可以填$0$或$1$，其他新占用位置只能填$1$，未占用只能填$0$。于是得到了一个$O(k^3)$的算法。

我们考虑优化，先把组合数拆出来，有
$$f[i][j]=\sum_{k=1}^{j-1}f[i-1][k]*\frac{j!}{k!*(j-k)!}*2^{k}$$
$$\frac{f[i][j]}{j!}=\sum_{k=0}^{j-1}\frac{f[i-1][k]*2^{k}}{k!}*\frac{1}{(j-k)!}$$
这是一个卷积形式，用$fft$加速。复杂度为$O(k^2logk)$。

我们发现只从$i-1$转移有点慢，于是我们考虑快速转移，把式子写成这样，
$$f[x+y][i]=\sum_{j=0}^{i}f[x][j]*f[y][i-j]*\binom{i}{j}*2^{y*j}$$
这样我们就可以把第$x$个多项式和第$y$个多项式卷积就是第$x+y$个多项式了，直接快速幂就好了。时间复杂度为$O(klog^2k)$。单位复根要用数组来存，不然会wa。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define LL long long 

using namespace std;

const LL maxk=70007;
const LL p=1e9+7;
const double pi=acos(-1);

LL n,m,len;
LL f[maxk],f1[maxk];
LL jc[maxk],r[maxk],inv[maxk],bit[maxk];

struct rec{
    double x,y;
};

rec operator +(rec x,rec y)
{
    return (rec){x.x+y.x,x.y+y.y};
}

rec operator -(rec x,rec y)
{
    return (rec){x.x-y.x,x.y-y.y};
}

rec operator *(rec x,rec y)
{
    return (rec){x.x*y.x-x.y*y.y,x.x*y.y+x.y*y.x};
}

rec operator /(rec x,LL y)
{
    return (rec){x.x/(double)y,x.y/(double)y};
}

rec operator !(rec x)
{
    return (rec){x.x,-x.y};
}

rec dfta[maxk],dftb[maxk],dftc[maxk],dftd[maxk];
rec a[maxk],b[maxk],w[maxk];

void init(LL len)
{
    LL k=trunc(log(len+0.5)/log(2));
    for (LL i=0;i<len;i++)
    {
        r[i]=(r[i>>1]>>1)|((i&1)<<(k-1));
    }
}

void fft(rec *a,LL f)
{
    for (LL i=0;i<len;i++)
    {
        if (i<r[i]) swap(a[i],a[r[i]]);
    }
    w[0]=(rec){1,0};
    for (LL i=2;i<=len;i*=2)
    {
        rec wn=(rec){cos(2*pi/i),f*sin(2*pi/i)};
        for(LL j=i/2;j>=0;j-=2)w[j]=w[j/2];
        for(LL j=1;j<i/2;j+=2)w[j]=w[j-1]*wn;
        for (LL j=0;j<len;j+=i)
        {
            //rec w=(rec){1,0};
            for (LL k=0;k<i/2;k++)
            {
                rec v=w[k]*a[j+k+i/2];
                a[j+k+i/2]=a[j+k]-v;
                a[j+k]=a[j+k]+v;
            //    w=w*wn;
            }
        }
    }
}

void FFT(LL *x, LL *y, LL *z,LL n,LL m)
{
    len=1;
    while (len<n+m) len*=2;
    init(len);
    for (LL i=0;i<len;i++)
    {
        LL A,B;
        if (i<n) A=x[i]%p; else A=0;
        if (i<m) B=y[i]%p; else B=0;
        a[i]=(rec){A&32767,A>>15};
        b[i]=(rec){B&32767,B>>15};
    }
    fft(a,1); fft(b,1);  	 
    for (LL i=0;i<len;i++)
    {
        LL j=(len-i)&(len-1);
        rec da,db,dc,dd;
        da=(a[i]+(!a[j]))*(rec){0.5,0};
        db=(a[i]-(!a[j]))*(rec){0,-0.5};
        dc=(b[i]+(!b[j]))*(rec){0.5,0};
        dd=(b[i]-(!b[j]))*(rec){0,-0.5};
        dfta[i]=da*dc;
        dftb[i]=da*dd;
        dftc[i]=db*dc;
        dftd[i]=db*dd;
    }    
    for (int i=0;i<len;i++)
    {
    	a[i]=dfta[i]+dftb[i]*(rec){0,1};
    	b[i]=dftc[i]+dftd[i]*(rec){0,1};
    }	
    fft(a,-1); fft(b,-1);
    for (int i=0;i<n+m-1;i++)
    {
        LL da=(LL)(a[i].x/len+0.5)%p;
        LL db=(LL)(a[i].y/len+0.5)%p;
        LL dc=(LL)(b[i].x/len+0.5)%p;
        LL dd=(LL)(b[i].y/len+0.5)%p;
        z[i]=(da%p+(((db+dc)<<15)%p+(dd<<30)%p)%p)%p;
    }
}

LL power(LL x,LL y)
{
    if (y==1) return x;
    LL c=power(x,y/2);
    c=(c*c)%p;
    if (y%2) c=(c*x)%p;
    return c;
}

void solve(LL n,LL k)
{
    if (n==1)
    {
        f[0]=0;
        for (LL i=1;i<=k;i++) f[i]=1;
        return;
    }
    solve(n/2,k);
    for(LL i=1;i<=k;i++)
    {
        f[i]=(LL)f[i]*inv[i]%p;
        f1[i]=(LL)f[i]*power(2,(n/2)*i%(p-1))%p;
    } 	 	    
    FFT(f,f1,f,k+1,k+1); 		   
    if(n&1)
    {
        for(LL i=1;i<=k;i++)
        {
            f[i]=(LL)f[i]*bit[i]%p;
            f1[i]=inv[i];
        }
        FFT(f,f1,f,k+1,k+1);
    }
    for (LL i=1;i<=k;i++)f[i]=(LL)f[i]*jc[i]%p;
}

LL binom(LL x,LL y)
{
    if ((x<0) || (y<0) || (y>x)) return 0;
    if ((x==0) || (y==x))  return 1;
    return jc[x]*inv[y]%p*inv[x-y]%p;
}

int main()
{
    scanf("%lld%lld",&n,&m);
    jc[0]=1; inv[0]=1; bit[0]=1;
    for (LL i=1;i<=m;i++)
    {
        jc[i]=(jc[i-1]*i)%p;
        bit[i]=(bit[i-1]*2)%p;
        inv[i]=power(jc[i],p-2);
    }
    if (n>m)
    {
        printf("0");
        return 0;
    }					
    solve(n,m);	
    LL ans=0;
    for(LL i=1;i<=m;i++)
      ans=(ans+f[i]*binom(m,i)%p)%p;
    printf("%lld",ans);
}
```

---

## 作者：xzCyanBrad (赞：1)

**下面记 $|x|$ 为 $\textbf{popcount}(x)$。**

首先当 $n>k$ 时，答案显然为 $0$。接下来考虑 $n\le k$ 的情况。有一个显然的 $\Theta(nk^2)$ dp 方程，状态分别记录了第 $i$ 位和 $|a_i|$：
$$
f(i,j)=\sum_{x=0}^{j-1}f(i-1,x)\binom{k-x}{k-j}2^{x}
$$

考虑优化。我们钦定 $|a_i|=x,|a_j|=y\ (i<j)$。那么考虑 $f(j,y)$ 有什么简便的计算方法？
$$
f(j,y)=f(i,x)f(j-i,y-x)\binom yx2^{x(j-i)}
$$
这个转移式的意思就是，分成前后两段分别长为 $i$ 和 $(j-i)$，然后合并时先枚举哪些是前面的，其实就是 $y$ 个里选 $x$ 个位；然后又因为后填的一段中前面已经是 $1$ 的 $x$ 位是可以任意的，所以还要乘上 $2^{x(j-i)}$。

那么当 $|a_i|$ 不定的时候：
$$
f(j,y)=\sum_{x}f(i,x)f(j-i,y-x)\binom yx2^{x(j-i)}
$$
这代表我们可以跳跃地推所有 dp 值，求出所有 $f(i,\dots)$ 和 $f(j-i,\dots)$ 之后可以 NTT 优化。就这么推导，如何让复杂度最优？$i=\frac j2$ 的时候。这时的复杂度为 $T(n)=2T(\frac n2)+n\log n$，$T(n)=\Theta(n\log^2 n)$。

注意 $n=1$ 时的边界问题。

这样就做完了！**这道题的关键在于我们发现开头 dp 转移与 $i$ 无关（即，取出一段序列和原序列其实是相似地求，无位置问题），就可以排除 $i$ 阶段带来的干扰了。因为就和分治 FFT 乘法一样的道理，每次合并两个大小接近的东西，是比每次合并大小悬殊巨大的东西快了一个量级的复杂度！**

---

## 作者：Limie (赞：1)

似乎没有卡常就拿到了最优解第二名？

~~[宣](https://www.luogu.com.cn/paste/u4r2fuwt)~~
### 暴力dp

设 $f_{i,j}$ 表示对于前 $i$ 个数，假设只有 $j$ 位且他们或起来的值为 $2^j-1$ 的情况下，满足题目要求的序列 $a$ 的个数。

那么有以下转移方程：
$$
f_{i,j}=\sum_{k=1}^j f_{i-1,j-k} \big (^j_k \big ) 2^{j-k}
$$

意思就是考虑加入第 $i$ 个数中新多了哪些 $1$。

### 推个式子

$$
f_{i,j}=\sum_{k=1}^j f_{i-1,j-k} \big (^j_k \big ) 2^{j-k} \\
f_{i,j}=j!\sum_{k=1}^j \frac{f_{i-1,j-k}2^{j-k}}{(j-k)!} \times \frac{1}{k!}
$$

发现这个式子非常可卷，于是考虑分治。

考虑将长度为 $a,b$ 的序列合并，令 $i=a+b$，则有：

$$
f_{i,j} = \sum_{k=1}^{j-1} f_{a,k} \times f_{b,j-k} \times \big (^j_k \big ) \times 2^{b \times k} \\
f_{i,j} = j! \sum_{k=1}^{j-1} \frac{f_{a,k} \times 2^{b \times k}}{k!} \times \frac{f_{b,j-k}}{(j-k)!} 
$$

发现现在可以分治了。

注意要记忆化，还有 MTT。

### 实现技巧
注意到可以设 $g_{i,j} = \frac{f_{i,j}}{j!}$，这样得到的式子会好做一点。

### Code
本人比较菜，喜欢用 vector 存多项式。

写的是 5 次 FFT 求 MTT。
```cpp
#include<bits/stdc++.h>
namespace Limie{
	#define x first
	#define y second
	using namespace std;
	typedef long long LL;
	typedef pair<int,int> PII;
	typedef unsigned long long ULL;
	typedef long double LD;
	const LD PI=acos(-1);
	struct Complex{
		LD a,b;
		inline Complex operator+(const Complex &w)
		{return Complex{a+w.a,b+w.b};}
		inline Complex operator-(const Complex &w)
		{return Complex{a-w.a,b-w.b};}
		inline Complex operator*(const Complex &w)
		{return Complex{a*w.a-b*w.b,a*w.b+b*w.a};}
		inline Complex operator/(const Complex &w)
		{
			double s=w.a*w.a+w.b*w.b;
			return Complex{(a*w.a+b*w.b)/s,(b*w.a-a*w.b)/s};
		}
	};
	namespace Poly{
		void fft(vector<Complex> &a,const int f)
		{
			int n=a.size();vector<int> rev(n);
			for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1));
			for(int i=0;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		    for(int l=1;l<n;l<<=1){
		        Complex w={cos(PI/l),f*sin(PI/l)};
		        for(int j=0;j<n;j+=(l<<1)){
		            Complex wk={1,0};
		            for(int i=0;i<l;i++){
		                Complex x=a[i+j],y=wk*a[i+j+l];
		                a[i+j]=x+y,a[i+j+l]=x-y;
		                wk=wk*w;
		            }
		        }
		    }
		}
		const int mod=1e9+7;
		int qmi(int a,int b)
		{
			int ans=1;
			while(b){
				if(b&1)ans=(LL)ans*a%mod;
				a=(LL)a*a%mod;
				b>>=1;
			}
			return ans;
		}
		struct poly:vector<int>{
		friend void operator*=(poly &a,poly b)
		{
			int len=a.size()+b.size()-1,n=1;
			while(n<len)n<<=1;
			vector<Complex> x(n),y(n),z(n);
			for(int i=0;i<a.size();i++)x[i].a=a[i]&32767,y[i].a=a[i]>>15;
			for(int i=0;i<b.size();i++)z[i]={b[i]&32767,b[i]>>15};
			fft(x,1),fft(y,1),fft(z,1);
			for(int i=0;i<n;i++)x[i]=x[i]*z[i],y[i]=y[i]*z[i];
			fft(x,-1),fft(y,-1);a.resize(len);
			for(int i=0;i<len;i++){
				LL a1=(LL)(x[i].a/n+.5)%mod;
				LL a2=(LL)((LL)(x[i].b/n+.5)%mod+(LL)(y[i].a/n+.5)%mod)<<15;
				LL a3=((LL)(y[i].b/n+.5)%mod)<<30;
				a[i]=(a1+a2+a3)%mod;
			}
		}
		};
	}
}
using namespace Limie;
using Poly::poly;
using Poly::qmi;
using Poly::mod;
LL n,k;
int infact[30010];
poly f[30010];
void sol(int n)
{
	if(f[n].size())return;
	if(n==1){
		f[1].resize(k+1);for(int i=1;i<=k;i++)f[1][i]=infact[i];
		return;
	}
	int mid=n>>1;
	sol(mid);sol(n-mid);
	int s=1,w=qmi(2,n-mid);
	f[n]=f[mid];
	for(int i=0;i<=k;i++){
		f[n][i]=(LL)f[n][i]*s%mod;
		s=(LL)s*w%mod;
	}
	f[n]*=f[n-mid];f[n].resize(k+1);
}
int main()
{
	int i;
	cin>>n>>k;
	if(n>k)return puts("0"),0;
	int fc=1;
	for(i=1;i<=k;i++)fc=(LL)fc*i%mod;
	infact[k]=qmi(fc,mod-2);
	for(i=k;i>=1;i--)infact[i-1]=(LL)infact[i]*i%mod;
	sol(n);int ans=0;
	for(i=1;i<=k;i++)ans=(ans+(LL)f[n][i]*infact[k-i]%mod)%mod;
	cout<<(LL)ans*fc%mod;
}
```

---

## 作者：Anoshag_Ruwan (赞：1)

~~我宣布场上出任意模数多项式操作的都是大【友善度】~~

首先，显然要求 $popcount(a_i)$（$a_i$ 在二进制下 1 的个数）严格单调递增，所以 $n > k$ 时答案为零，这个数据范围的唯一影响就是 $n$ 要用 long long 读入，不然会寄。

设 $dp_{i,j}$ 表示 $popcount(a_i)=j$ 的方案数，则不难得到 $dp_{i,j}=\sum\limits_{h < j}dp_{i-1,h} \binom{k-h}{j-h}2^h$，初始条件 $dp_{0,j}=[j=0]$，$ans=\sum\limits_{i \leq k}dp_{n,i}$，恭喜你得到了直接转移 $O(n^3)$ 的做法。注意到该转移方程与 $i$ 无关，且其形式类似卷积，容易想到类似多项式快速幂的倍增操作，于是推一下：

$dp_{i,j}(k-j)!=\sum dp_{i-1,h} (k-h)!2^h \times \frac{1}{(j-h)!}$,

设 $f_i(x)=\sum\limits_{j \geq 0} dp_{i,j}(k-j)!x^j$，$g(x)=e^x-1=\sum\limits_{i > 0}\frac{x^i}{i!}$，则有 $f_i(x)=f_{i-1}(2x)g(x)$。

以 $f_0(x)=k!$ 为边界递归下去，则 $f_n(x)=k!\prod\limits^{n-1}_{i=0}g(2^ix)$，后面这个式子可以考虑倍增，令 $h_i(x)=\prod\limits^i_{j=1}g(2^jx)$，则 $h_{2i}(x)=h_i(x)h_i(2^ix)$。

该做法时间复杂度为 $O(n \log ^2n)$，别忘了最后得到 $f_n(x)$ 后每一项除以 $(k-i)!$ 才能得到 $dp_{n,i}$，其实如果不是任意模数，这题不应该评黑……emm。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a1[550011],b1[550011],c[550011],r[550011],frc[500011],inv[500011],d[500011];
long long k1,coe1,coe2,coe3,n,sz;
const long long inf=1e18,sqinf=1e9,p=1e9+7,p1=998244353,p2=167772161,p3=469762049;//三模NTT的模数
inline int ksadd(int x,int y,int z){return x+y>=z?x+y-z:x+y;}
inline void bter(){
	for(int i=0;i<k1;i++)r[i]=(r[i>>1]>>1)|(i&1?k1>>1:0);}
struct xs{
	long long a1,b1,c1;
}w[1100011],v[1100011],v1[1100011],q[500011],l1;//分别为模p1,p2,p3下的值
inline xs modd(xs x,xs y){
	xs z;z.a1=1ll*x.a1*y.a1%p1,z.b1=1ll*x.b1*y.b1%p2,z.c1=1ll*x.c1*y.c1%p3;
	return z;
}inline xs add(xs x,xs y,bool j){
	if(!j)y.a1=y.a1?p1-y.a1:0,y.b1=y.b1?p2-y.b1:0,y.c1=y.c1?p3-y.c1:0;
	xs z;z.a1=ksadd(x.a1,y.a1,p1);z.b1=ksadd(x.b1,y.b1,p2);z.c1=ksadd(x.c1,y.c1,p3);
	return z;
}
struct gjd{long long lw,ht;}crt[4],mo;//用2个long long实现36位高精
inline gjd lltms(long long x,long long y){
	long long u=x/sqinf,v=x-u*sqinf,u1=y/sqinf,v1=y-u1*sqinf,\
		w=(u*v1+v*u1)/sqinf,w1=(u*v1+v*u1-w*sqinf)*sqinf,w2=0;
		if(w1>=inf)w2+=w1/inf,w1-=w2*inf;
		w1+=v*v1;if(w1>=inf)w2+=w1/inf,w1-=w2*inf;
	gjd z;z.ht=w+w2+u*u1,z.lw=w1;
	return z;
}inline gjd gjadd(gjd x,gjd y,gjd z){
	long long m=x.lw+y.lw+z.lw,m1=m/inf;m-=m1*inf;
	long long s=x.ht+y.ht+z.ht+m1;
	gjd r;r.ht=s,r.lw=m;return r;
}inline int gjmod(gjd x,gjd y,int z){
	if(x.ht<y.ht||x.ht==y.ht&&x.lw<y.lw)return (inf%p*(x.ht)%p+x.lw%p)%p;
	long long i,j,l=inf/10,s;gjd u;u.ht=0,u.lw=x.ht;
	for(i=0;i<18;i++){
		u.ht*=10;if(u.lw>=l)j=u.lw/l,u.ht+=j,u.lw-=l*j;u.lw*=10;
		if(u.ht<y.ht||u.ht==y.ht&&u.lw<y.lw)continue;
		while(u.ht>y.ht||u.ht==y.ht&&u.lw>=y.lw){s=0;
			u.lw-=y.lw;if(u.lw<0)u.lw+=inf,s++;
			u.ht-=y.ht+s;}
	}u.lw+=x.lw;s=0;if(u.lw>=inf)u.lw-=inf,s++;u.ht+=s;
	if(u.ht>y.ht||u.ht==y.ht&&u.lw>=y.lw){s=0;
		u.lw-=y.lw;if(u.lw<0)u.lw+=inf,s++;
		u.ht-=y.ht+s;}
	return (inf%p*u.ht%p+u.lw%p)%p;
}//十分答辩的高精取模
inline long long rd(){
	long long i=0;char c=getchar();
	while(c<48||c>57)c=getchar();
	while(c>47&&c<58)i=(i<<3)+(i<<1)+c-48,c=getchar();
	return i;
}
inline int ksm(long long x,long long y,long long z){
	long long k=1,l=x;if(x==1||y==1)return x;
	while(y){if(y&1)k=k*l%z;l=l*l%z;y>>=1;}
	return (int)k;
}
inline void ntt(xs *f,bool m){
	register int i,j,h,k,l;xs t;
	for(i=0;i<k1;i++)if(i<r[i])
		t.a1=f[i].a1,t.b1=f[i].b1,t.c1=f[i].c1,\
		f[i].a1=f[r[i]].a1,f[i].b1=f[r[i]].b1,f[i].c1=f[r[i]].c1,\
		f[r[i]].a1=t.a1,f[r[i]].b1=t.b1,f[r[i]].c1=t.c1;
	for(i=1;i<k1;i<<=1){
		l1.a1=ksm(m?3:332748118,(p1-1)/(i<<1),p1);
		l1.c1=ksm(m?3:156587350,(p3-1)/(i<<1),p3);
		l1.b1=ksm(m?3:55924054,(p2-1)/(i<<1),p2);
		for(j=q[0].a1=q[0].b1=q[0].c1=1;j<i;j++)
			q[j]=modd(q[j-1],l1);
		for(j=0;j<k1;j+=i<<1)
			for(h=j;h<j+i;h++)
				t=modd(f[h+i],q[h-j]),f[h+i]=add(f[h],t,0),f[h]=add(f[h],t,1);
	}return;
}inline void zgrt(int *g){
	long long i,k4,k5,k6;
	for(i=0;i<k1;i++){
		k4=1ll*coe1*v[i].a1;crt[1]=lltms(k4,p2*p3);
		k5=1ll*coe2*v[i].b1;crt[2]=lltms(k5,p1*p3);
		k6=1ll*coe3*v[i].c1;crt[3]=lltms(k6,p1*p2);
		crt[0]=gjadd(crt[1],crt[2],crt[3]);
		g[i]=gjmod(crt[0],mo,i);}
}//Zhongguo Remainder Theorem
inline void mtt(int *f,int *g){
	long long i,j,k4,k5,k6;xs t;
	k4=ksm(k1,p1-2,p1);k5=ksm(k1,p2-2,p2);k6=ksm(k1,p3-2,p3);
	for(i=0;i<k1;i++)
		w[i].a1=f[i]%p1,w[i].b1=f[i]%p2,w[i].c1=f[i]%p3,\
		v[i].a1=g[i]%p1,v[i].b1=g[i]%p2,v[i].c1=g[i]%p3;
	ntt(w,1);ntt(v,1);
	for(i=0;i<k1;i++)v[i]=modd(v[i],w[i]);
	ntt(v,0);
	for(i=0;i<k1;i++)
		v[i].a1=1ll*v[i].a1*k4%p1,\
		v[i].b1=1ll*v[i].b1*k5%p2,\
		v[i].c1=1ll*v[i].c1*k6%p3;
	zgrt(g);
	return;
}//将b多项式模p意义下卷上c
inline void mult(int k,int *b){
	int i,j;if(k==1){
		for(i=1,j=2,b[0]=0;i<=sz;j=(j<<1)%p,i++)
			b[i]=1ll*inv[i]*j%p;;return;}
	mult(k>>1,b);
	for(i=0,j=1;i<=sz;i++,j=1ll*d[k>>1]*j%p)c[i]=1ll*b[i]*j%p;
	for(i=sz+1;i<k1;i++)b[i]=c[i]=0;
	mtt(c,b);
	if(k&1){for(i=sz+1;i<k1;i++)b[i]=c[i]=0;
		for(i=1,j=d[k];i<=sz;i++,j=1ll*d[k]*j%p)c[i]=1ll*inv[i]*j%p;
		mtt(c,b);}
}
int main()
{
	int i,j,ans=0;n=rd(),sz=rd();
	if(n>sz){printf("0\n");return 0;}
	mo=lltms(p1*p3,p2);
	coe1=ksm(p2*p3%p1,p1-2,p1);
	coe2=ksm(p1*p3%p2,p2-2,p2);
	coe3=ksm(p1*p2%p3,p3-2,p3);
	for(k1=1;k1<=(sz<<1);k1<<=1);bter();
	for(i=frc[0]=d[0]=1;i<=sz;i++)
		frc[i]=1ll*frc[i-1]*i%p,d[i]=(d[i-1]<<1)%p;
	for(i=sz,inv[i]=ksm(frc[i],p-2,p);i;i--)
		inv[i-1]=1ll*inv[i]*i%p;
	if(n==1){printf("%d\n",d[sz]-1);return 0;}
	mult(n-1,b1);
	for(i=sz+1;i<k1;i++)b1[i]=0;
	inv[0]=0;mtt(inv,b1);inv[0]=1;
	for(i=n;i<=sz;i++)ans=ksadd(ans,1ll*b1[i]*frc[sz]%p*inv[sz-i]%p,p);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：JustinRochester (赞：1)

[传送门](https://codeforces.com/problemset/problem/623/E)

---

**【分析】**
--

不难想到，令 $f_{n, k}$ 表示前 $n$ 个数，使得 $b_n$ 有 $k$ 个 $1$ 的方案数。

则很容易列出转移方程，由于 $a_i>0$ ，故 $\displaystyle f_{n, k}=\sum_{i=0}^{k-1} \binom k if_{n-1, i}\cdot 2^i$ 。

变形得到 $\displaystyle {f_{n, k}\over k!}x^k=\sum_{i+j=k} {f_{n-1,i}\cdot 2^i\over i!}x^i\cdot {[j>0]\over j!}x^j$ 。

因此得到生成函数的转移关系 $\displaystyle \hat F_{n}(x)=\hat F_{n-1}(2x)\cdot (e^x-1)$ 。

而由 $f_{0, k}=[k=0]$ 得到 $\hat F_0(x)=1$ 。

列举几项得到 $\hat F_1(x)=e^x-1, \hat F_2(x)=(e^{2x}-1)(e^x-1), \hat F_3(x)=(e^{4x}-1)(e^{2x}-1)(e^x-1)$ 。

猜想 $\displaystyle \hat F_n(x)=\prod_{i=0}^{n-1} (e^{2^ix}-1)$ ，若对 $n\leq m$ 时成立。

则 $\displaystyle \hat F_{m+1}(x)=\hat F_m(x)(2x)\cdot (e^x-1)=\prod_{i=0}^{m-1}(e^{2^i\cdot 2x}-1)\cdot (e^x-1)=\prod_{i=0}^m (e^{2^ix}-1)$ 。

由数学归纳法证明猜想正确。

---

设答案为 $A_{n, k}$ ，则 $\displaystyle A_{n, k}=\sum_{i=0}^k \binom k i f_{n, i}\Rightarrow \hat A_n(x)=\hat F_n(x)\cdot e^x$ 。

问题化为如何求解 $\hat F_n(x)$ 不超时。

考虑到 $\displaystyle \hat F_{2n}(x)=\prod_{i=0}^{2n-1}(e^{2^ix}-1)=\prod_{i=0}^{n-1}(e^{2^ix}-1)\cdot \prod_{i=n}^{2n-1}(e^{2^ix}-1)=\prod_{i=0}^{n-1}(e^{2^ix}-1)\cdot \prod_{i=0}^{n-1}(e^{2^{i+n}x}-1)=\hat F_n(x)\cdot \hat F_n(2^n x)$ 。

而 $\displaystyle F(x)=\sum_{i=0}^\infty f_ix^i\Rightarrow F(Ax)=\sum_{i=0}^\infty f_iA^i\cdot x^i$ 。

故已知 $\hat F_n(x)$ ，可以先 $O(n)$ 求解 $\hat F(2^n x)$ ，再多项式卷积 $O(n\log n)$ 求出 $\hat F_{2n}(x)$ 。

因而求解 $\hat F_n(x)$ 时，先递归求解 $\hat F_{n/2}(x)$ ，若 $n$ 为奇数，再利用递推式 $O(n\log n)$ 算出结果。

最后再卷上 $e^x$ 即可得到答案的生成函数。

总复杂度 $\displaystyle T(n)=T({n\over 2})+O(n\log n)=O(n\log n)$ ，常数约为 $20$ 次 FFT 。

---

**【代码】**
---

由于需要任意模数，考虑使用 MTT 。但这题貌似精度需求非常高，用 double 会算出问题，得 long double 。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long double db;
#define fi first
#define se second

struct vir{
    db r, i;
    vir(db r_=0, db i_=0):r(r_), i(i_) {}
};
inline vir operator + (const vir &a, const vir &b) { return vir(a.r+b.r, a.i+b.i); }
inline vir operator - (const vir &a, const vir &b) { return vir(a.r-b.r, a.i-b.i); }
inline vir operator * (const vir &a, const vir &b) { return vir(a.r*b.r-a.i*b.i, a.r*b.i+a.i*b.r); }
inline vir operator / (const vir &a, db b) { return vir(a.r/b, a.i/b); }
inline vir operator ! (const vir &z) { return vir(z.r, -z.i); }
inline vir operator / (const vir &a, const vir &b) { return a*!b/(b*!b); }
const db pi=acos(-1), eps=1e-6;

const int LimBit=18, M=1<<LimBit;
int a[M], b[M], c[M];
struct NTT{
    int Stk[M], curStk;
    int N, na, nb, P, m, N_;
    inline ll kpow(ll a,ll x) { ll ans=1; for(;x;x>>=1,a=a*a%P) if(x&1) ans=ans*a%P; return ans; }
    NTT(int P_=1e9+7):P(P_){
        m=1<<15;
        curStk=0;
		N_=-1;
    }

    vir w[2][M], invN;
    int rev[M];
    void work(){
		if(N_==N) return ; N_=N;
        int d = __builtin_ctz(N);
        w[0][0] = w[1][0] = vir(1, 0);
        vir x = vir(cos(2*pi/N), sin(2*pi/N)), y = !x;
        for (int i = 1; i < N; i++) {
            rev[i] = (rev[i>>1] >> 1) | ((i&1) << (d-1));
            w[0][i] = x * w[0][i-1] , w[1][i] = y * w[1][i-1];
        }
        invN=vir(1.0/N, 0);
    }

    inline void fft(vir *a,int f){
        static vir x;
        for(int i=0;i<N;++i) if(i<rev[i]) swap(a[i],a[rev[i]]);
        for(int i=1;i<N;i<<=1)
            for(int j=0,t=N/(i<<1);j<N;j+=i<<1)
                for(int k=0,l=0;k<i;++k,l+=t)
                    x=w[f][l]*a[j+k+i], a[j+k+i]=a[j+k]-x, a[j+k]=a[j+k]+x;
        if(f) for(int i=0;i<N;++i) a[i]=a[i]*invN;
    }
    inline int mergeNum(ll a1,ll a0,ll b1,ll b0){
        // return ((a1*m+a0+b1)%p*m+b0+p)%p;
        return (( ((a1<<15)+a0+b1)%P<<15 )+b0)%P;
    }
    inline void doit(int *a,int *b,int na,int nb){
        static vir x, y, p0[M], p1[M];
        for(N=1;N<na+nb-1;N<<=1);
        for(int i=na;i<N;++i) a[i]=0;
        for(int i=nb;i<N;++i) b[i]=0;
        for(int i=0;i<N;++i)
            // p1[i]=pdd(a[i]/m,a[i]%m),p0[i]=pdd(b[i]/m,b[i]%m);
            p1[i]=vir(a[i]>>15, a[i]&(m-1)), p0[i]=vir(b[i]>>15, b[i]&(m-1));
        work(); fft(p1,0); fft(p0,0);
        for(int i=0,j;i+i<=N;++i){
            j=(N-1)&(N-i);
            x=p0[i], y=p0[j];
            p0[i]=(x-!y)*p1[i]*vir(0, -0.5);
            p1[i]=(x+!y)*p1[i]*vir(0.5, 0);
            if(i==j) continue;
            p0[j]=(y-!x)*p1[j]*vir(0, -0.5);
            p1[j]=(y+!x)*p1[j]*vir(0.5, 0);
        }
        fft(p1,1); fft(p0,1);
        for(int i=0;i<N;++i)
            a[i]=mergeNum(p1[i].r+0.5, p1[i].i+0.5, p0[i].r+0.5, p0[i].i+0.5);
    }
}ntt;

ll n;
int k, f[M];
inline void init() {
	b[1]=1;
	for(int i=2, P=ntt.P; i<=3e4; ++i)
		b[i]=P-(ll)b[P%i]*(P/i)%P;
	for(int i=2, P=ntt.P; i<=3e4; ++i)
		b[i]=(ll)b[i-1]*b[i]%P;
}
inline void work(ll n) {
	if(n==0) {
		for(int i=0; i<=k; ++i) f[i]=0;
		f[0]=1;
		return ;
	}
	work(n>>1);
	for(int i=0, x=ntt.kpow(2, n>>1), y=1, P=ntt.P; i<=k; ++i)
		a[i]=(ll)f[i]*y%P, y=(ll)y*x%P;
	ntt.doit(f, a, k+1, k+1);

	if(n+1&1) return ;
	for(int i=0, x=2, y=1, P=ntt.P; i<=k; ++i)
		f[i]=(ll)f[i]*y%P, y=(ll)y*x%P;
	ntt.doit(f, b, k+1, k+1);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	init();
	cin>>n>>k;
	work(n);
	++b[0];
	ntt.doit(f, b, k+1, k+1);
	for(int i=0, x=1, P=ntt.P; i<=k; ++i)
		f[i]=(ll)f[i]*x%P, x=(ll)x*(i+1)%P;
	cout<<f[k];
	cout.flush();
	return 0;
}
```

---

## 作者：peterwuyihong (赞：1)

题意：我们定义一个 $a\rightarrow b$ 变换为 $b_i=|_{j=1}^ia_j$（高能生草前缀或，称一个牛逼的 $a$ 为，它的变换是严格单调递增的，那就要问你了，给定 $k$ 有多少 $a$ 满足 $|a|=n$ 且 $\forall 1\le i\le n,s.t.\ 1\le a_i\le 2^k-1$。$1\le n\le 10^{18},1\le k\le 3\times10^4$

我们前缀或是一定不会减少的，问题就是这个单调递增，我们考虑搞一个 $dp$ 方程，设 $f_{i,j}$ 为前 $i$ 个有 $j$ 个 $1$（不保证合法），则：

$$f_{i,j}=\sum_{k=0}^jf_{i-1,k}\binom j k2^{k}$$

就是说，这 $k$ 个位置必然包含于 $j$ 个位置中，于是乘上一个组合数表示所有包含的情况，再乘上一个二的幂表示这 $k$ 个位置可有可无，因为是或运算。

然后我们使用倍增，还有

$$f_{2n,k}=\sum_{i=0}^kf_{n,i}f_{n,k-i}\binom k i2^{ni}$$

原理略同，然后就能整个 $\text{EGF}$ 倍增了。

现在是 $11:41$，我看我什么时候写完。

现在是 $13:08$，我写完了。

各种神秘组合错误，调死我了。

```cpp
long long n;
int k;
poly f,ex_1;
poly solve(int n){
	if(n==1)return ex_1;
	poly f=solve(n>>1);
	poly g=f;
	for(int i=0,j=ksm(2,n>>1),l=1;i<=k;i++,mul(l,j))mul(g[i],l);
	f=mtt(f,g);f.resize(k+1);
	if(n&1){
		for(int i=0,l=1;i<=k;i++,mul(l,2))mul(f[i],l);
		f=mtt(f,ex_1),f.resize(k+1);
	}
	return f;
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n>>k;
	if(n>k)return cout<<0,0;
	init(k);
	ex_1.resize(k+1);
	for(int i=1;i<=k;i++)ex_1[i]=jcinv[i];
	f=solve((int)n);
	int ans=0;
	for(int i=1;i<=k;i++)add(ans,Mul(f[i],Mul(jc[k],jcinv[k-i])));
	cout<<ans;
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
上面是我的多项式板子，[安利一波](https://www.luogu.com.cn/blog/Peterprpr/mu-ban)。

---

## 作者：Rainybunny (赞：1)

&emsp;&emsp;[推销博客 owo](https://www.cnblogs.com/rainybunny/p/13161559.html)。

# 题目

## 题意简述

&emsp;&emsp;[link](https://www.luogu.com.cn/problem/CF623E).

&emsp;&emsp;有一个 $n$ 个元素的集合，你需要进行 $m$ 次操作。每次操作选择集合的一个非空子集，要求该集合不是已选集合的并的子集。求操作的方案数，对 $10^9+7$ 取模。

## 数据规模

&emsp;&emsp;$n\le3\times10^4$。

# $\text{Solution}$

&emsp;&emsp;显然当 $n<m$，答案为 $0$，先特判掉。

&emsp;&emsp;首先列一个 naive 的 DP 方程，令 $f(i,j)$ 为**前 $i$ 次操作选出的集合并大小为 $j$ 的方案数**。易有：
$$
f(i,j)=\sum_{k=1}^j2^{j-k}{n-(j-k)\choose k}f(i-1,j-k)
$$
&emsp;&emsp;那么答案为 $\sum_{i=1}^nf(m,i)$。暴力 DP 是 $\mathcal{O}(mn^2)$ 的。不过很显然这个式子是一个卷积的形式。把它变一下形：
$$
f(i,j)=\frac{1}{(n-j)!}\sum_{k=1}^j\frac{1}{k!}\cdot2^{j-k}[n-(j-k)]!f(i-1,j-k)
$$
&emsp;&emsp;~~忽略毒瘤的模数，~~每次转移 NTT 就可以了，复杂度 $\mathcal{O}(mn\log n)$。

&emsp;&emsp;这个 $f$ 不太好优化。我们换一种形式，令 $g(i,j)$ 为**前 $i$ 次操作选出前 $j$ 个元素的方案数**。所以 $g(i,j)=\frac{f(i,j)}{n\choose j}$。那么对于 $g(1)$，有 $g(1,i)=[0<i\le n]$。来考虑两层状态的合并：
$$
g(u+v,i)=\sum_{j=0}^ig(u,j)g(v,i-j){i\choose j}(2^j)^v
$$
&emsp;&emsp;理解一下：把 $u+v$ 次操作和 $i$ 个选出的元素分拆成两步完成：第一步选 $j$ 个元素，第二步选 $i-j$ 个。由于要在 $i$ 里拿出 $j$ 个给第一步（或说拿出 $i-j$ 给第二步），所以有系数 $i\choose j$。关键点在于 $(2^u)^j$：在第一步中，我们已经选出了 $j$ 个元素，所以在第二步的每次操作，都可以任意取 $j$ 个元素的子集，故有系数 $(2^j)^v$。

&emsp;&emsp;向卷积形式靠拢：
$$
g(u+v,i)=i!\sum_{j=0}^i\frac{2^{jv}g(u,j)}{j!}\cdot\frac{g(v,i-j)}{(i-j)!}
$$
&emsp;&emsp;倍增处理 $g$ 即可。复杂度 $\mathcal{O}(n\log n\log m)$。

## 代码

&emsp;&emsp;这里用 MTT 实现任模 NTT。要特别留意每一步的取模嗷 qwq。

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>

typedef long long LL;

const int MAXN = 1 << 16, P = 1e9 + 7;
const double PI = acos ( -1 );
int n, m, len, lg, rev[MAXN + 5], fac[MAXN + 5], ifac[MAXN + 5], pwr[MAXN + 5];
int F[MAXN + 5], ans[MAXN + 5];

struct Complex {
	double x, y;
	Complex () {} Complex ( const double tx, const double ty ): x ( tx ), y ( ty ) {}
	inline Complex operator + ( const Complex t ) const { return Complex ( x + t.x, y + t.y ); }
	inline Complex operator - ( const Complex t ) const { return Complex ( x - t.x, y - t.y ); }
	inline Complex operator * ( const Complex t ) const { return Complex ( x * t.x - y * t.y, x * t.y + y * t.x ); }
	inline Complex operator / ( const double t ) const { return Complex ( x / t, y / t ); }
} omega[MAXN + 5];

inline void FFT ( const int n, Complex* A, const int tp ) {
	for ( int i = 0; i < n; ++ i ) if ( i < rev[i] ) std::swap ( A[i], A[rev[i]] );
	for ( int i = 2, stp = 1; i <= n; i <<= 1, stp <<= 1 ) {
		for ( int j = 0; j < n; j += i ) {
			for ( int k = 0; k < stp; ++ k ) {
				Complex w ( omega[n / stp * k].x, tp * omega[n / stp * k].y );
				Complex ev ( A[j + k] ), ov ( w * A[j + k + stp] );
				A[j + k] = ev + ov, A[j + k + stp] = ev - ov;
			}
		}
	}
	if ( ! ~ tp ) for ( int i = 0; i < n; ++ i ) A[i] = A[i] / n;
}

inline void initFFT ( const int lg ) {
	int n = 1 << lg;
	for ( int i = 0; i < n; ++ i ) rev[i] = ( rev[i >> 1] >> 1 ) | ( ( i & 1 ) << lg >> 1 );
	for ( int i = 1; i < n; i <<= 1 ) {
		for ( int k = 0; k < i; ++ k ) {
			omega[n / i * k] = Complex ( cos ( PI * k / i ), sin ( PI * k / i ) );
		}
	}
}

inline void polyConv ( const int n, const int* A, const int* B, int* C ) {
	static Complex highA[MAXN + 5], highB[MAXN + 5], lowA[MAXN + 5], lowB[MAXN + 5];
	for ( int i = 0; i < n; ++ i ) {
		lowA[i].x = A[i] & 0x7fff, highA[i].x = A[i] >> 15;
		lowB[i].x = B[i] & 0x7fff, highB[i].x = B[i] >> 15;
		lowA[i].y = highA[i].y = lowB[i].y = highB[i].y = 0;
	}
	FFT ( n, lowA, 1 ), FFT ( n, highA, 1 ), FFT ( n, lowB, 1 ), FFT ( n, highB, 1 );
	for ( int i = 0; i < n; ++ i ) {
		Complex la ( lowA[i] ), ha ( highA[i] ), lb ( lowB[i] ), hb ( highB[i] );
		lowA[i] = ha * hb, highA[i] = la * hb, lowB[i] = ha * lb, highB[i] = la * lb;
	}
	FFT ( n, lowA, -1 ), FFT ( n, highA, -1 ), FFT ( n, lowB, -1 ), FFT ( n, highB, -1 );
	for ( int i = 0; i < n; ++ i ) {
		C[i] = ( ( 1ll << 30 ) % P * ( LL ( round ( lowA[i].x ) ) % P ) % P
			 + ( LL ( round ( highA[i].x ) ) % P << 15 ) % P
			 + ( LL ( round ( lowB[i].x ) ) % P << 15 ) % P
			 + ( LL ( round ( highB[i].x ) ) % P ) ) % P;
	}
}

inline int qkpow ( int a, int b, const int p = P ) {
	int ret = 1;
	for ( ; b; a = 1ll * a * a % p, b >>= 1 ) ret = 1ll * ret * ( b & 1 ? a : 1 ) % p;
	return ret;
}

inline void init ( const int n ) {
	fac[0] = ifac[0] = pwr[0] = 1;
	for ( int i = 1; i <= n; ++ i ) {
		fac[i] = 1ll * i * fac[i - 1] % P;
		pwr[i] = ( pwr[i - 1] << 1 ) % P;
	}
	ifac[n] = qkpow ( fac[n], P - 2 );
	for ( int i = n - 1; i; -- i ) ifac[i] = ( i + 1ll ) * ifac[i + 1] % P;
}

inline void add ( const int fn, const int fm ) {
	if ( ! fn ) {
		for ( int i = 0; i <= n; ++ i ) ans[i] = F[i];
		return ;
	}
	static int A[MAXN + 5], B[MAXN + 5];
	for ( int i = 0; i <= n; ++ i ) {
		A[i] = 1ll * ans[i] * ifac[i] % P * qkpow ( 2, 1ll * i * fm % ( P - 1 ) ) % P;
		B[i] = 1ll * F[i] * ifac[i] % P;
	}
	for ( int i = n + 1; i < len; ++ i ) A[i] = B[i] = 0;
	polyConv ( len, A, B, ans );
	for ( int i = 0; i <= n; ++ i ) ans[i] = 1ll * ans[i] * fac[i] % P;
	for ( int i = n + 1; i < len; ++ i ) ans[i] = 0;
}

inline void shift ( const int cur ) {
	static int A[MAXN + 5], B[MAXN + 5];
	for ( int i = 0; i <= n; ++ i ) {
		A[i] = 1ll * F[i] * ifac[i] % P * qkpow ( 2, 1ll * i * cur % ( P - 1 ) ) % P;
		B[i] = 1ll * F[i] * ifac[i] % P;
	}
	for ( int i = n + 1; i < len; ++ i ) A[i] = B[i] = 0;
	polyConv ( len, A, B, F );
	for ( int i = 0; i <= n; ++ i ) F[i] = 1ll * F[i] * fac[i] % P;
	for ( int i = n + 1; i < len; ++ i ) F[i] = 0;
}

int main () {
	scanf ( "%d %d", &m, &n );
	if ( m > n ) return puts ( "0" ), 0;
	len = 1, lg = 0;
	for ( ; len <= n << 1; len <<= 1, ++ lg );
	initFFT ( lg ), init ( n );
	for ( int i = 1; i <= n; ++ i ) F[i] = 1;
	for ( int i = 0, cur = 0; 1 << i <= m; ++ i ) {
		if ( ( m >> i ) & 1 ) add ( cur, 1 << i ), cur |= 1 << i;
		shift ( 1 << i );
	}
	int sum = 0;
	for ( int i = 0; i <= n; ++ i ) {
		sum = ( sum + 1ll * ans[i] * fac[n] % P * ifac[i] % P * ifac[n - i] ) % P;
	}
	printf ( "%d\n", sum );
	return 0;
}
```


---

## 作者：OtterZ (赞：0)

# 题意
给定 $n,k(n \le 10 ^ {18},k \le 30000)$，求 $n$ 长度 $k$ 位二进制数序列的个数使得前缀或严格单增。
# 转化
前缀或严格单增，意味着每次有新的位变成 $1$，位方便计数，可以转化为：

有 $k$ 个元素，求 $n$ 个元素的集合的序列数，每次要出现一个前所未有的元素。

这样会方便我们得出和理解接下来的过程，也可以立即得出 $n > k$ 时无解，从而缩小要考虑的 $n$ 的范围。~~其实就是常数会小。~~
# 动规

设 $dp_{i,j}$ 为 $i$ 个集合涉及 $j$ 个元素，可以知道对于 $0 \le k < j$，当从 $dp_{i - 1,k}$ 转移到 $dp_{i,j}$ 时，我们有 $(^{n - k}_{j - k})$ 种方法选出新的 $j - k$ 种元素，已出现的元素可有可无，对应 $2 ^ k$ 种方法，得到：

$$
dp_{i,j} = \sum_{0\le k < j}dp_{i - 1,k} \times 2^k \times (^{n - k}_{j - k})
$$

这样我们得到了 $O(nk)$ 的方法。

# 对于转移方程中组合数的处理

由：

$$
(^a_b) = \frac{a!}{b!(a - b)!}
$$

得：

$$
\begin{aligned}
(^{n - k}_{j - k}) &= \frac{(n - k)!}{(j - k)![(n - k) - (j - k)]!}\\
&= \frac{(n - k)!}{(j - k)!(n - k - j + k)!}\\
&= \frac{(n - k)!}{(n - j)!(j - k)!}
\end{aligned}
$$

故：

$$
dp_{i,j} = \sum_{0\le k < j}dp_{i - 1,k} \times 2^k \times \frac{(n - k)!}{(n - j)!(j - k)!}
$$

同时乘 $(n - j)!$ 得：

$$
(n - j)!dp_{i,j} =\sum_{0\le k < j}(n - k)! dp_{i - 1,k} \times 2^k \times \frac{1}{(j - k)!}
$$

此时设 $f_{i,j} = (n - j)!dp_{i,j},g_{i} = \frac{1}{i!}$，有：

$$
f_{i,j} = \sum_{0 \le k < j}f_{i - 1,k} \times 2^ k \times g_{j - k}
$$

呈现出类似卷积的形式，不过距离使用 FFT 优化还有一段距离——对转移式中 $2^k$ 处理。

# 整体化与重新分配

我们对于 $f_{i,j}$ 设其转移路径为从 $f_{0,0}$ 通过方程加到 $f_{i,j}$ 中的一种 $j$ 的变化。对于一条转移路径，我们发现如果创建一个条形图，将每一步的 $j$ 作为高度，则会得到整个路径中 $2$ 的次数为除最后一列外，其他列高度之和：

![](https://cdn.luogu.com.cn/upload/image_hosting/qrwhf3pw.png)

接下来我们试着换成横向统计：

![](https://cdn.luogu.com.cn/upload/image_hosting/gppif3z2.png)

得到：

$$
\operatorname{F}_n(x) = \sum_{i= 0}^k x^if_{n,i} = \prod_{i = 1}^n \operatorname{G}_{i}(x),\operatorname{G}_i(x) = \sum_{j = 0}^k x^j \frac{2^{(n - i)\cdot j}}{j}
$$

即：

$$
\operatorname{F}_n(x) = \sum_{i= 0}^k x^if_{n,i} = \prod_{i = 0}^{n - 1} \operatorname{G}_{i}(x),\operatorname{G}_i(x) = \sum_{j = 0}^k x^j \frac{2^{i\cdot j}}{j}
$$

也就是说，接下来就是要求：

$$
\prod_{i = 0}^{n - 1} \operatorname{G}_{i}(x),\operatorname{G}_i(x) = \sum_{j = 0}^k x^j \frac{2^{i\cdot j}}{j}
$$

# 倍增求答案

我们设：

$$
\operatorname{H}_i(x) = \prod_{i = 0}^{i - 1} \operatorname{G}_{i}(x) = \sum_{j} h_{i,j},\operatorname{L}_{i,j}(x) = \sum_{k}x^k2^{ik}h_{j,k}
$$

有：

$$
\operatorname{L}_{i,j}(x) = \sum_{k}x^k2^{ik}h_{j,k} = \prod_{k = i}^{i + j - 1}\operatorname{G}_k(x) \\
\operatorname{H}_{i + j}(x) = \operatorname{H}_i(x) \cdot \operatorname{L}_{i,j}(x)
$$

这是可以发现求 $\operatorname{H}_{i + j}(x)$ 时 $\operatorname{L}_{i,j}(x)$ 可以通过 $\operatorname{H}_j(x)$ 遍历每一位得到，然后进行卷积，由于每次我们可以只保留后 $k + 1$ 位，故而是 $\operatorname{O}(k\log k)$ 的。此时我们考虑倍增，这样只用进行 $\operatorname{O}(\log k)$ 次求 $\operatorname{H}_{i + j}(x)$ 的操作，得到 $\operatorname{O}(k\log^2 k)$ 的算法。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int k,s[30009],ni[30009],inv[30009];
const int di = 31667,mod = 1000000007;
int fp(int a,int b){
	int t = 1;
	while(b){
		if(b & 1)
			t = 1ll * t * a % mod;
		a = 1ll * a * a % mod;
		b = b >> 1;
	}
	return t;
}
//3DFT + 2IDFT拆位FFT，由于计算涉及的规模过大需要long double 卡精度
long double PI = acos(-1);
typedef complex<long double> cplx;
void FFT(vector<cplx>&f,int l,int t){
	vector<int>to(l,0);
	for(int i = 1; i < l; i ++){
		to[i] = (to[i >> 1] >> 1) | ((i & 1) * (l >> 1));
		if(to[i] > i)
			swap(f[i],f[to[i]]);
	}
	for(int i = 1; (1 << i) <= l; i ++){
		cplx o = cplx(cos(PI / (1 << i - 1)),sin(PI / (1 << i - 1)) * t);
		for(int j = 0; j < l; j += (1 << i)){
			cplx w = cplx(1,0);
			for(int k = j; k < j + (1 << i - 1); k ++){
				cplx u = f[k],v = f[k + (1 << i - 1)] * w;
				f[k] = u + v;
				f[k + (1 << i - 1)] = u - v;
				w *= o;
			}
		}
	}
	if(t == -1){
		for(int i = 0; i < l; i ++)
			f[i] /= l;
	}
}
vector<int>operator*(vector<int>&x,vector<int>&y){
	int l = 1;
	while(l < x.size() + y.size())
		l = l << 1;
	vector<cplx>f1(l,cplx(0,0)),f2(l,cplx(0,0)),f3(l,cplx(0,0));
	vector<int>fx = x,fy = y;
	fx.resize(l,0),fy.resize(l,0);
	for(int i = 0; i < l; i ++){//拆位
		f1[i].real(fx[i] / di);
		f2[i].real(fx[i] % di);
		f3[i].real(fy[i] / di);
		f3[i].imag(fy[i] % di);
	}
	FFT(f1,l,1);
	FFT(f2,l,1);
	FFT(f3,l,1);
	for(int i = 0; i < l; i ++){
		f1[i] = f1[i] * f3[i];
		f2[i] = f2[i] * f3[i];
	}
	FFT(f1,l,-1);
	FFT(f2,l,-1);
	vector<int>ret(l,0);
	for(int i = 0; i < l; i ++){//合并
		long long s1 = f1[i].real() + 0.5,s2 = f1[i].imag() + 0.5,s3 = f2[i].real() + 0.5,s4 = f2[i].imag() + 0.5;
		s1 %= mod,s2 %= mod,s3 %= mod,s4 %= mod;
		ret[i] = (1ll * s1 * di % mod * di % mod + 1ll * (s2 + s3) * di % mod) % mod;
		ret[i] = (ret[i] + s4) % mod;
	//	printf("%d %d %d %d\n",s1,s2,s3,s4);
	}
	return ret;
}
int main(){
	scanf("%lld %d",&n,&k);
	if(n > k){
		puts("0");
		return 0; 
	}
	s[0] = ni[0] = s[1] = ni[1] = inv[1] = 1;
	for(int i = 2; i <= k; i ++){
		inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
		s[i] = 1ll * s[i - 1] * i % mod;
		ni[i] = 1ll * ni[i - 1] * inv[i] % mod;
	}
	vector<int>t(1,s[k]);
	vector<int>f(k + 1,0);
	for(int i = 1; i <= k; i ++){
		f[i] = ni[i];
		//printf("%d\n",f[i]);
	}
	int nw = 0,ws = 1;
	int o = n;
	while(o > 0){
		if(o & 1){
			int p = fp(2,nw);
			int so = 1;
			vector<int>sl = f;//H_j(x) -> L_{i,j}(x)
			for(int i = 0; i <= k; i ++){
				sl[i] = 1ll * sl[i] * so % mod;
				so = 1ll * so * p % mod;
			}
			t = t * sl;
			if(t.size() > k + 1)//只保留后 k + 1 位
				t.resize(k + 1);
			//for(int i = 0; i < t.size(); i ++)
			//	printf("%d\n",t[i]);
			nw |= ws;
		}
		o = o >> 1;
		if(o){
			int p = fp(2,ws);
			int so = 1;
			vector<int>sl = f;//H_j(x) -> L_{i,j}(x)
			for(int i = 0; i <= k; i ++){
				sl[i] = 1ll * sl[i] * so % mod;
				so = 1ll * so * p % mod;
			}
			f = f * sl;
			if(f.size() > k + 1)//只保留后 k + 1 位
				f.resize(k + 1);
			ws = ws << 1;
		}
	}
	int ans = 0;
	for(int i = 0; i <= k; i ++){
		ans = (ans + 1ll * t[i] * ni[k - i] % mod) % mod;
	}
	printf("%d\n",ans);
}
```

---

## 作者：Arghariza (赞：0)

<https://www.cnblogs.com/Ender32k/p/17585748.html>

难点在于卡 `__int128`（？）。

首先 $N>K$ 显然无解，只需考虑 $N\le K$ 的情况。然而这并没有什么用。

把 $b$ 看作集合，显然 $b_i\subset b_{i+1}$。所以令 $f_{n,i}$ 为考虑到 $b_n$ 且 $|b_n|=i$ 的方案数，集合元素无序，即选择 $\{A,B,C\}$ 或者 $\{A,B,D\}\in \{A,B,C,D\}$ 看作**不同**方案，且**不考虑**其它 $k-i$ 种元素。有如下转移：

$$f_{n,i}=\sum\limits_{j=0}^if_{n-1,i-j}\dbinom{i}{j}2^{i-j}$$

即考虑 $b_n\setminus b_{n-1}$ 的大小，从 $b_n$ 中有的选出 $|b_n\setminus b_{n-1}|$ 个一定要选，另外 $|b_{n-1}|$ 个元素对于 $a_n$ 可以任意选择。

把转移形式写得好看一点：

$$f_{n,i}=\sum\limits_{j=0}^if_{n-1,i}\dbinom{i}{j}2^j$$

$$\text{ans}=\sum\limits_{i=1}^{K}f_{N,i}\dbinom{K}{i}$$

注意到 $f$ 的转移组合数拆开后可以写成卷积的形式，于是我们有了 $O(NK\log K)$ 的做法，然而这还是没有什么用。

但是注意到，$f_{n}$ 其实能从任意的 $a+b=n$ 转移而来，具体地：

$$f_{n,i}=\sum\limits_{j=0}^if_{a,j}f_{b,i-j}\dbinom{i}{j}2^{bj}$$

原理是类似的，考虑 $b_n$ 和 $b_a$ 的关系，枚举 $b_a$ 的大小，从 $i$ 个元素中选出 $j$ 个来自 $b_a$，剩下 $b_{a+1}\setminus b_a,b_{a+2}\setminus b_a,\cdots ,b_{n}\setminus b_a$ 这些集合显然也满足前面是后面的子集，于是对这 $b$ 个集合，用 $f_{b,i-j}$ 枚举这样的集合序列的方案数，最后这些集合对于 $b_a$ 中原本有的元素都可以任意挑选。

然后就是套路了，令 $a=\left\lfloor\dfrac{n}{2}\right\rfloor$，$b=\left\lceil\dfrac{n}{2}\right\rceil$，分治求解即可。复杂度 $O(K\log K\log N)$。

要写任意模数 NTT，不能 `#define int __int128`。

彩蛋：

> (官方题解：)We decided to ask the answer modulo $10^9+7$ to not let the participants easily guess that these problem requires FFT :) So, in order to get accepted you had to implement one of the methods to deal with the large modulo in polynomial multiplication using FFT.

```cpp
// Problem: Transforming Sequence
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF623E
// Memory Limit: 250 MB
// Time Limit: 7000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define li __int128
using namespace std;

namespace vbzIO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
    #if ONLINE_JUDGE
    #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    #else
    #define gh() getchar()
    #endif
    #define mt make_tuple
    #define mp make_pair
    #define fi first
    #define se second
    #define pc putchar
    #define pb emplace_back
    #define ins insert
    #define era erase
    typedef tuple<int, int, int> tu3;
    typedef pair<int, int> pi;
    inline li rd() {
        char ch = gh();
        li x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void wr(int x) {
        if (x < 0) x = ~(x - 1), pc('-');
        if (x > 9) wr(x / 10);
        pc(x % 10 + '0');
    }
}
using namespace vbzIO;

const int N = 2e5 + 100;
const int G = 3;
const int P[3] = { 469762049, 998244353, 1004535809 };
const int p = 1e9 + 7;

li n;
int k;
int fac[N], ifac[N];

int Add(int x, int y, int P) { return x += y, (x >= P) ? x - P : x; }
int Mul(int x, int y, int P) { return 1ll * x * y % P; }

int qpow(int p, int q, int P) {
	int res = 1;
	for (; q; q >>= 1, p = Mul(p, p, P))
		if (q & 1) res = Mul(res, p, P);
	return res;
}

void init(int lim) {
	fac[0] = 1;
	for (int i = 1; i <= lim; i++)
		fac[i] = Mul(fac[i - 1], i, p);
	ifac[lim] = qpow(fac[lim], p - 2, p);
	for (int i = lim - 1; ~i; i--)
		ifac[i] = Mul(ifac[i + 1], i + 1, p);
}

void exgcd(li a, li b, li &x, li &y) {
	if (!b) return x = 1, y = 0, void();
	exgcd(b, a % b, y, x), y -= a / b * x;
}

int CRT(int *a) {
	li SP = 1, res = 0;
	for (int i = 0; i < 3; i++) SP *= P[i];
	for (int i = 0; i < 3; i++) {
		li m = SP / P[i], b, y;
		exgcd(m, P[i], b, y);
		(res += a[i] * m * b) %= SP;
	}
	return (res % SP + SP) % SP % p;
}

void NTT(int *f, int len, int lim, int op, int id) {
	static int tr[N];
	int iG = qpow(G, P[id] - 2, P[id]);
	for (int i = 1; i < len; i++) 
		tr[i] = (tr[i >> 1] >> 1) | ((i & 1) << (lim - 1));
	for (int i = 0; i < len; i++)
		if (i < tr[i]) swap(f[i], f[tr[i]]);
	for (int o = 2, k = 1; k < len; o <<= 1, k <<= 1) {
		int tg = qpow(~op ? G : iG, (P[id] - 1) / o, P[id]);
		for (int i = 0; i < len; i += o) {
			for (int j = 0, w = 1; j < k; j++, w = Mul(w, tg, P[id])) {
				int x = f[i + j], y = Mul(w, f[i + j + k], P[id]);
				f[i + j] = Add(x, y, P[id]), f[i + j + k] = Add(x, P[id] - y, P[id]);
			}
		}
	}
	if (~op) return;
	int iv = qpow(len, P[id] - 2, P[id]);
	for (int i = 0; i < len; i++) f[i] = Mul(f[i], iv, P[id]);
}

typedef vector<int> poly;
poly tp;
map<int, poly> ft;

poly Mul(poly x, poly y, int id) {
	static int tf[N], tg[N];
	int len = 1, lim = 0, szx = x.size(), szy = y.size();
	while (len < szx + szy) len <<= 1, lim++;
	for (int i = 0; i < len; i++) tf[i] = tg[i] = 0;
	for (int i = 0; i < szx; i++) tf[i] = x[i];
	for (int i = 0; i < szy; i++) tg[i] = y[i];
	NTT(tf, len, lim, 1, id), NTT(tg, len, lim, 1, id);
	for (int i = 0; i < len; i++) tf[i] = Mul(tf[i], tg[i], P[id]);
	NTT(tf, len, lim, -1, id);
	poly res;
	for (int i = 0; i < szx + szy - 1; i++) res.pb(tf[i]);
	return res;
}

poly MTT(poly x, poly y, int p) {
	poly c[3], res;
	int szx = x.size(), szy = y.size();
	for (int i = 0; i < 3; i++) c[i] = Mul(x, y, i);
	for (int i = 0; i < szx + szy - 1; i++) {
		int t[3] = { c[0][i], c[1][i], c[2][i] };
		res.pb(CRT(t));
	}
	return res;
}

poly conq(int len) {
	if (ft.find(len) != ft.end()) return ft[len];
	int la = len >> 1, lb = len - la, bs = qpow(2, lb, p);
	poly lhs = conq(la), res;
	poly rhs = (la == lb) ? lhs : conq(lb);
	for (int i = 0, w = 1; i < lhs.size(); i++, w = Mul(w, bs, p)) 
		lhs[i] = Mul(lhs[i], Mul(w, ifac[i], p), p);
	for (int i = 0; i < rhs.size(); i++)
		rhs[i] = Mul(rhs[i], ifac[i], p);
	res = MTT(lhs, rhs, p);	
	for (int i = 0; i < res.size() && i <= k; i++) res[i] = Mul(res[i], fac[i], p);
	res.resize(k + 1);
	return ft[len] = res;
}

int main() {
    n = rd(), k = rd();
    if (n > k) return puts("0"), 0;
    tp = poly(k + 1, 1), tp[0]--, init(k + 10), ft[1] = tp;
    poly res = conq(n);
    int ans = 0;
    for (int i = 1; i < res.size(); i++) 
    	ans = Add(ans, Mul(res[i], Mul(fac[k], Mul(ifac[i], ifac[k - i], p), p), p), p);
    wr(ans);
    return 0;
}
```

---

