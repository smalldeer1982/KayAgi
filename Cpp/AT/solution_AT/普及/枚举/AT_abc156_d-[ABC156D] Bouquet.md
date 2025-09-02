# [ABC156D] Bouquet

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc156/tasks/abc156_d

あかりさんは $ n $ 種類の花を $ 1 $ 本ずつ持っています。

あかりさんは、これらの花から $ 1 $ 本以上を選び、花束を作ろうとしています。

ただし、あかりさんは $ a $ と $ b $ の $ 2 $ つの数を苦手としていて、いずれかと一致するような本数の花からなる花束は作ることができません。

あかりさんが作ることのできる花束は何種類あるでしょうか。

$ (10^9\ +\ 7) $ で割った余りを求めてください。

ここで $ 2 $ つの花束は、一方では使われているが、 もう一方では使われていない種類の花があるとき、別の種類の花束であるとみなします。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 2\ \leq\ n\ \leq\ 10^9 $
- $ 1\ \leq\ a\ <\ b\ \leq\ \textrm{min}(n,\ 2\ \times\ 10^5) $

### Sample Explanation 1

この場合、あかりさんは $ 2 $ 本または $ 4 $ 本の花を選んで花束を作ることができます。 $ 4 $ 本ある花の中から $ 2 $ 本を選ぶ方法は $ 6 $ 通り、$ 4 $ 本を選ぶ方法は $ 1 $ 通りあるので、 あかりさんが作ることができる花束の種類数は合わせて $ 7 $ 通りです。

### Sample Explanation 2

$ (10^9\ +\ 7) $ で割った余りを出力してください。

## 样例 #1

### 输入

```
4 1 3```

### 输出

```
7```

## 样例 #2

### 输入

```
1000000000 141421 173205```

### 输出

```
34076506```

# 题解

## 作者：Xu__ (赞：5)

#### 题目分析

这道题已经有了线性求逆元、杨辉三角等做法，这里提供一种比较好想的做法。

首先注意到答案即为 $2^n-C_n^a-C_n^b$。
- 对于 $2^n$ 可以直接使用快速幂在 $O(\log_2 n)$ 的时间复杂度内求解。
- 对于组合数，无论是使用定义式直接求还是使用递推式递推都无法在规定时间内求解，但是注意到 $a$ 和 $b$ 的范围较小，所以可以考虑将组合数转化为排列数求解。

$$

C_n^a=a!\cdot A_n^a=a!\cdot\frac{n!}{(n-a)!}=a!\cdot\prod_{i=n-a+1}^{n}i


$$

整个式子可以在 $O(a)$ 的时间复杂度内求解，所以整个问题的时间复杂度即为 $O(a)$。

#### 代码实现
```cpp
#include <bits/stdc++.h>
#define int long long
#define FL(xx, yy, zz) memset(xx, yy, (zz))
#define DEBUG() cout << "¿What Happened?" << endl
#define DG(x) cout << "Debug : " << #x << " = " << x << endl
#define Efor(xx, yy) for(int xx = Head[yy]; xx; xx = Next[xx])
#define Lfor(xx, yy, zz, xyz, ...) for(int xx = yy, ##__VA_ARGS__; xx <= zz; xx += xyz)
#define Rfor(xx, yy, zz, xyz, ...) for(int xx = yy, ##__VA_ARGS__; xx >= zz; xx -= xyz)
using namespace std;
const int kN = 1e6 + 16, INF = ~0u >> 1, Mod = 1e9 + 7;
int n, a, b;
int F_Pow(int a, int b, int p) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int Fac(int x, int p) {
	int ans = 1;
	for (int i = 1; i <= x; ++i) ans = ans * i % p;
	return ans;
}
int Inv(int x, int p) {
	return F_Pow(x, p - 2, p);
}
int C(int n, int m, int p) {
	if (n < m) return 0;
	int ans = 1;
	Lfor (i, n - m + 1, n, 1) ans = ans * i % p;
	return ans * Inv(Fac(m, p), p) % p;
}
signed main() {
#ifdef FIO
    freopen("I:/Code/Data/In.in", "r", stdin);
    freopen("I:/Code/Data/Out.out", "w", stdout);
#endif
	cin >> n >> a >> b;
	cout << (F_Pow(2, n, Mod) - 1 - C(n, a, Mod) - C(n, b, Mod) + Mod + Mod + Mod) % Mod;

}
```


---

## 作者：DengDuck (赞：3)

没难度的容斥题，答案为总方案数减去选 $A$ 个数字的方案数减去选 $B$ 个数字的方案数减去空集。

根据组合数学常识，得:$2^n-\text{C}_{n}^a-\text{C}_{n}^b-1$。

利用快速幂和逆元求组合数即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
const LL N=3e5+5;
const LL M=3e5;
using namespace std;
const LL mod=1e9+7;
LL n,a,b,inv[N];
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ans;
}
LL C(LL n,LL m)
{
	LL ans=1;
	for(int i=1;i<=m;i++)
	{
		ans=ans*(n-m+i)%mod*inv[i]%mod;
	}
	return ans;
}
int main()
{
	scanf("%lld%lld%lld",&n,&a,&b);
	for(int i=1;i<=M;i++)inv[i]=ksm(i,mod-2);
	LL ans=(ksm(2,n)-C(n,a)-C(n,b)-1+3*mod)%mod;
	printf("%lld",ans);
}
```

---

## 作者：orpg (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc156_d)
### 解法分析
从 $n$ 个数中选 $1,2,3,\dots,n$ 个数的方案数是 $C_n^1+C_n^2+\dots+C_n^n$。因为 $C_n^1+C_n^2+\dots+C_n^n=2^n$，所以可知方案数就是 $2^n-1$，最后减掉 $C_n^a$ 和 $C_n^b$ 即可。

tips：本题使用逆元维护数组空间不够，所以组合数可以用暴力求解，具体实现看代码。
### 上代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=2e5+5;
const int mod=1e9+7;
int n;
ll D[maxn],inv[maxn],fac[maxn];
int a,b;
ll qpow(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans%mod;
}
void init(){
    D[1]=0,D[2]=1;
    for(int i=3;i<2e5;i++){
        D[i]=(i-1)*(D[i-1]+D[i-2])%mod;
    }
    fac[0]=fac[1]=1;
    inv[1]=1;
    for(int i=2;i<maxn;i++){
        fac[i]=fac[i-1]*i%mod;
        inv[i]=inv[i-1]*qpow(i,mod-2)%mod;
    }
}
ll C(int n, int m){
    long long ans=1;
    for(int i=n;i>=n-m+1;i--){
        ans*=i;
        ans%=mod;
    }
    ans*=inv[m];
    ans%=mod;
    return ans;
}
main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>a>>b;
    init();
    cout<<(qpow(2,n)%mod-1-C(n,a)%mod-C(n,b)%mod+2*mod)%mod;
    return 0;
}
```


---

## 作者：diqiuyi (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT5341)

**前置芝士**

逆元，不会的先去做一下 [这题](https://www.luogu.com.cn/problem/P3811)。

组合数，这个应该都知道吧。毕竟很常见。

**思路**

显然，从 $n$ 种花里面选若干支的方案数总数为 $C^1_n+C^2_n+\dots+C^n_n$。众所周知，这个数就是 $2^n-C^0_n=2^n-1$。

**证明**

众所周知，$C^n_m=C^{n-1}_{m-1}+C^n_{m-1}(0<n<m)$，那么，

$C^0_m+C^1_m+\dots+C^{m-1}_m+C^m_m$

$=C^0_m+C^0_{m-1}+C^1_{m-1}+C^1_{m-1}+C^2_{m-1}+\dots+C^{m-2}_{m-1}+C^{m-1}_{m-1}+C^m_m$

又 $\because C^0_m=C^0_{m-1}$，$C^m_m=C^{m-1}_{m-1}$，$\therefore \sum_{i=0}^mC^i_m=2\sum_{i=0}^{m-1}C^i_{m-1}$。

然后把 $C^1_1=1$ 代入即可证明。

再把选 $a$ 和 选 $b$ 的减去就行了。

也就是说，答案为 $2^n-C^a_n-C^b_n-1$。

不过，还要注意逆元的处理。可以利用 $inv_i=i^{mod-2}$ 来计算逆元，也可以预处理一下阶乘的逆元，不过 $O(n)$ 预处理大概率会 TLE。

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//不开 long long 见祖宗
//虽说如此，但是不开好像确实问题不大，只要注意一下细节就行
#define mod 1000000007
inline int read(int x=0,bool f=1){
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
	return f?x:-x;
}//快读
int Pow(int x,int y){
	int res=1;
	for(;y;y>>=1,x=x*x%mod)
		if(y&1)
			res=res*x%mod;
	return res;
}//快速幂
int C(int x,int y){
	int ans=1;
	for(int i=x-y+1;i<=x;i++)
		ans=ans*i%mod;
	for(int i=2;i<=y;i++)
		ans=ans*Pow(i,mod-2)%mod;
	return ans;
}
int n,a,b; 
signed main(){
	n=read(),a=read(),b=read();
	printf("%lld\n",(mod+mod+Pow(2,n)-C(n,a)-C(n,b)-1)%mod);
   	//这里加 2 个 mod 是因为 C++ 中负数取模还是负数
	return 0;
}
```
完结撒花 $QAQ$。

---

## 作者：HoshizoraZ (赞：2)

**前置知识：二项式定理及其变形**

二项式定理如下：

$$(x+y)^n=\sum_{i=0}^n\binom n ix^{n-i}y^{i}$$

令 $x=y=1$ ，可以得到一个公式：

$$2^n=\sum_{i=0}^n\binom n i$$

----------

题目大意：求

$$\left(\sum_{i=1}^n\binom n i-\binom n a - \binom n b \right)\bmod 10^9+7$$

首先处理第一部分：

$$
\begin{aligned}
\sum_{i=1}^n\binom n i&=\sum_{i=0}^n \binom n i - \binom n 0\\
&=2^n-1
\end{aligned}$$

用快速幂求解。

然后看 $\binom n a$ 和 $\binom n b$，以 $\binom n a$ 为例：

$$
\begin{aligned}
\binom n a &= \frac{n!}{a! \cdot (n-a)!}\\
&= \frac{1}{a!}\prod_{i=n-a+1}^ni
\end{aligned}
$$

因为 $a \le 2 \times 10^5$，所以 $\frac{1}{a!}$ 可以线性求，后面的部分可以暴力算。

**在写代码时需要注意，C++ 中负数取模可能得到的答案可能为负数，如 $-1 \;\bmod\; 2$ 运行的结果为 $-1$。**

所以作减法运算时，请在取模前加上 $10^9+7$，使其变成非负数。

参考代码：

```cpp
#include <cstdio>
#define MOD 1000000007
typedef long long ll;

ll n, a, b, ans, inv[200010];

ll qpow(ll x, ll y){				// 快速幂 
	ll t = 1;
	while(y){
		if(y & 1) t = t * x % MOD;
		x = x * x % MOD;
		y >>= 1;
	}
	return t;
}

ll solve(ll a, ll b){
	ll t = 1;
	// 以下部分即为 a! / (a - b)!，需要运行 b 次，考虑 b 很小，所以可以暴力算 
	for(ll i = a; i >= a - b + 1; i--)
		t = t * i % MOD;
	return t * inv[b] % MOD;
}

int main(){

	scanf("%lld%lld%lld", &n, &a, &b);
	inv[1] = 1;
	for(ll i = 2; i <= 200000; i++)			// 逆元预处理 
		inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
	for(ll i = 2; i <= 200000; i++)			// 递推变成阶乘的逆元 
		inv[i] = inv[i - 1] * inv[i] % MOD;
		
	ans = (qpow(2, n) - 1 + MOD) % MOD; 
	ans = (ans - solve(n, a) + MOD) % MOD;
	ans = (ans - solve(n, b) + MOD) % MOD;
	printf("%lld\n", ans); 

	return 0;
}
```

---

## 作者：卷王 (赞：0)

此题是一道排列组合题。显然可得答案是 $2^n-C^a_n-C^b_n$。

其中 $2^n$ 可用快速幂得出，两个组合数可以直接套公式暴力乘即可。

由于求组合数的时候最后要除一下，需要使用逆元，由于 $mod$ 是一个质数，$a \times b^{mod-2} \mod 10^9+7$ 就可以求出。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
int a, b;

inline int power(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) res = (res * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return res;
}

inline int C(int x, int y) {
	int res1 = 1, res2 = 1;
	for (int i = 1; i <= x; i++)
		res1 = (res1 * i) % mod;
	for (int i = y - x + 1; i <= y; i++)
		res2 = (res2 * i) % mod;
	return res2 * power(res1, mod - 2) % mod;
}

signed main() {
	n = read(), a = read(), b = read();
	cout << (power(2, n) - 1 - C(a, n) - C(b, n) + mod * 2) % mod;
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# 思路

每一种花可以选或不选，共有 $2^n$ 种选法。选择 $a$ 种花，共有 $C_n^a$ 种选法。选择 $b$ 种花，共有 $C_n^b$ 种选法。一种也不选（空集），共有 $1$ 种选法。

故答案为

$$2^n-C_n^a-C_n^b-1$$

因为 $n$ 非常大，不能直接计算组合数。考虑从范围较小的 $a$ 和 $b$ 入手，即：

$$C_n^a=\frac{n!}{a!\cdot (n-a)!}=\frac{1}{a!}\prod_{i=n-a+1}^{n}i $$

$$C_n^b=\frac{n!}{b!\cdot (n-b)!}=\frac{1}{b!}\prod_{i=n-b+1}^{n}i $$

于是，这道题的时间复杂度成功变为 $O(a+b)$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll p = 1e9 + 7ll;
ll pw[1919810];

ll quickpow(ll n, ll m) {
    if (m == 1ll) {
        return n % p;
    }
    if (m == 0ll) {
        return 1ll % p;
    }
    if (m % 2ll) {
        ll ret = (quickpow(n, m / 2ll)) % p;
        return ret % p * ret % p * n % p;
    } else {
        ll ret = (quickpow(n, m / 2ll)) % p;
        return ret % p * ret % p;
    }
}

ll c(ll n, ll m) {
	ll ans = 1;
    for (ll i = n, j = 1; j <= m; i--, j++) {
    	ans = ans * i % p * quickpow(j, p - 2) % p;
	}
	return ans;
}

int main() {
    
    pw[0] = 1 % p;
    for (ll i = 1; i <= 1000005; i++) {
        pw[i] = (i * pw[i - 1] % p) % p;
    }
    ll n, a, b;
    cin >> n >> a >> b;
    ll ans = quickpow(2, n) - c(n, a) - c(n, b);
    ans += p + p + p + p - 1;
    cout << ans % p;

    return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

校内模拟赛本来就没想到如何求那两个组合数，结果快速幂又打错了，怒写一篇题解。  
### 题意
有 $n$ 种花，选一种或多种花组成花束，花的种类数量不能是 $a$ 或 $b$ ，求方案数。    
### 思路
抛开花的种类数量不能是 $a$ 或 $b$ 不谈，对于每一种花，可以选或不选，所以总共有 $2^n$ 种方案，不过要减去什么都不选的一种方案。因为 $n \le 10^9$，所以要快速幂。    
然后考虑限制。$n$ 种花里面选 $a$ 种或 $b$ 种，所以不合法的方案数为 $C_n^a+C_n^b$。       
那么问题来了：怎么求这两个组合数？    
我们知道 $C_n^m=\dfrac{n!}{m!(n-m)!}$，在这里我们约分一下，把 $\frac{n!}{(n-m)!}$ 变为 $(n-m+1)\times (n-m+2)\times \dots \times n$。   
于是式子就变成了下面的样子：           
$$ \dfrac{\prod _{i=n-m+1}^n i}{m!}$$     
（终于明白自己为什么赛时会困惑上面的问题了：我当时把 $n!$ 和 $m!$ 约分去了……）  
因为有分母和模数，所以要逆元。  
时间复杂度：式子到这里就是完全暴力了，暴力去求 $m!$ 和 $\prod _{i=n-m+1}^n i$，都只是 $O(m)$。因为 $a,b \le 2 \times 10^5$，所以完全可以通过。   

### 代码  
```cpp
#include<stdio.h>
const long long mod=1e9+7;
long long ksm(long long x,long long num)
{
	if(num==0) return 1;
	if(num==1) return x;
	if(num==2) return x*x%mod;
	long long rt=ksm(x,num>>1);
	return rt*rt%mod*(num&1?x:1)%mod;
   //警钟敲烂：我在这里把 x 打成了 rt，望周知。
}
long long n,a,b,ans,jc[200005];
int main()
{
	scanf("%lld%lld%lld",&n,&a,&b),
	jc[0]=1,ans=(ksm(2,n)-1+mod)%mod;
	for(int i=1;i<=200000;i++) jc[i]=jc[i-1]*i%mod;
	long long ls=1;
	for(int i=n-a+1;i<=n;i++) ls=ls*i%mod;
	ans=(ans-ls*ksm(jc[a],mod-2)+mod)%mod,ls=1;
	for(int i=n-b+1;i<=n;i++) ls=ls*i%mod;
	printf("%lld",((ans-ls*ksm(jc[b],mod-2)%mod+mod)%mod+mod)%mod);
    //加那么多 mod 是为了防止负数的出现
    //还有千万不要傻傻去写快速阶乘！！！
}
```

---

## 作者：Paracelestia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc156_d)

## $\texttt{Solution}$

每种花有选和不选两种方案，再减去一种花都不选的方案，总方案数即为 $2 ^ n - 1$。再减去选 $a$ 种和选 $b$ 种的方案数，答案即为 $2 ^ n - 1 - C^a_n - C^b_n$。

在处理 $C^a_n$ 和 $C^b_n$ 时，我采用了这样的方法：

可以发现 
$$
C_n^m = \dfrac{n!}{(n - m)!m!} 
$$
$$
= \dfrac{n!}{\dfrac{(n - m + 1)!}{n - m + 1}(m - 1)!\ m} 
$$
$$
= \dfrac{n!}{(n - (m - 1))!(m - 1)!} \cdot (n - m + 1) \div m
$$
$$
= C^{m - 1}_n \cdot (n - m + 1) \div m
$$

通过这个递推式，我们就能在 $\mathcal{O}(\max(a, b))$ 的时间复杂度内得出 $C_n^a,C_n^b$。

由于对 $10^9 + 7$ 取模，除法用乘法逆元实现。

## $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define debug(x) cout << #x" = " << x << endl;
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout);

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;

#define fi first
#define se second

template<typename T> inline T read() {
    T x = 0, f = 1; char ch = 0;
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch - '0');
    return x * f;
}

template<typename T> inline void write(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

template<typename T> inline void print(T x, char ed = '\n') { write(x), putchar(ed); }

const int N = 2e5 + 10, mod = 1e9 + 7;

#define int long long

namespace GoedelMachine {
    int n, a, b, C[N];

    int qpow(int a, int b) {
        int ret = 1;
        while(b) {
            if(b & 1) ret = ret * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return ret;
    }

    void init() {}
    void main(int tid) {
        n = read<int>(), a = read<int>(), b = read<int>();
        C[0] = 1;
        for(int i = 1; i <= max(a, b); ++ i) 
            C[i] = C[i - 1] * (n - i + 1) % mod * qpow(i, mod - 2) % mod; // 递推计算组合数
        print((qpow(2, n) - 1 - C[a] + mod - C[b] + mod) % mod);
    }
}

signed main() {
    int T = 1;
    //T = read<int>();
    for(int i = 1; i <= T; ++ i) {
        GoedelMachine::init();
        GoedelMachine::main(i);
    }
    return 0;
}
```


---

## 作者：FReQuenter (赞：0)

## 思路：

题目让我们求 $\sum^{n}_{i=1}\binom{n}{i}$ 减去 $\binom{n}{a}$ 和 $\binom{n}{b}$ 的和。

------------

若无特殊注明，以下 $a,b$ 与题目中的 $a,b$ 无关。

由 $\sum^{n}_{i=1}\binom{n}{i}=2^n-1$，
这个式子就转化为 $2^n-1-\binom{n}{a}-\binom{n}{b}$。

关于组合数：注意一下**不要**习惯性地预处理逆元，在 $\binom{a}{b}$ 里直接算即可（$n\leq10^9$）。在一些 $n\leq10^6$ 的题目里建议提前预处理逆元。

总体复杂度 $\operatorname{O}(\max\{a,b\})$ （$a,b$ 为题目中的 $a,b$，复杂度来自求组合数，$\log n$ 的快速幂比 $\operatorname{O}(\max\{a,b\})$ 小，忽略不计）。

## 代码：

```cpp
#define int long long
#define mod 1000000007
inline int qpow(int a,int n){
	//快速幂
	int ans=1;
	while(n){
		if(n&1) ans*=a,n--,ans%=mod;
		n>>=1;
		a*=a,a%=mod;
	}
	return ans;
}
inline int myC(int n,int m){
	//组合数，详细证明可以上网搜索
	int ans=1;
	for(int i=n-m+1;i<=n;i++) ans=ans*i%mod;
	for(int i=2;i<=m;i++) ans=ans*qpow(i,mod-2)%mod;
	return ans;
}
signed main(){
	int n,a,b;
	cin>>n>>a>>b;
	cout<<(mod*2+qpow(2,n)-myC(n,a)-myC(n,b)-1)%mod;
	return 0;
}
```

---

## 作者：Ginger_he (赞：0)

## 题目描述

求从 $n$ 件物品中选若干件（至少为 $1$），且不能选 $a$ 或 $b$ 件的方案数，答案对 $10^9+7$ 取模

## 题解

~~这题顶多是个黄题~~

我们可以将题意转化为下面这个式子

$$\sum_{i=1}^n\mathrm{C}_n^i-\mathrm{C}_n^a-\mathrm{C}^n_b$$

只要接触过组合恒等式就能进行化简

$$2^n-1-\mathrm{C}_n^a-\mathrm{C}^n_b$$

然后用快速幂和逆元计算组合数和乘方即可。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll p=1e9+7;
ll n,a,b;
ll quickpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*a%p;
		b>>=1;
		a=a*a%p;
	}
	return res;
}
ll c(ll n,ll m)
{
	ll x=1,y=1;
	for(ll i=n-m+1,j=1;i<=n,j<=m;i++,j++)
		x=x*i%p,y=y*j%p;
	return x*quickpow(y,p-2)%p;
}
int main()
{
	scanf("%lld%lld%lld",&n,&a,&b);
	printf("%lld\n",((quickpow(2,n)-1-c(n,a)-c(n,b))%p+p)%p);
	return 0;
}
```

---

## 作者：xiaozeyu (赞：0)

[AT5341 [ABC156D] Bouquet](https://www.luogu.com.cn/problem/AT5341)

~~一眼秒杀~~题。

这道题主要还是看文化课进度。

数学学过组合数就知道这个式子的意义。

![图片](https://cdn.luogu.com.cn/upload/image_hosting/jz6m86ha.png)

两数同时取一是初学排列组合时常见的做法，这样所有与 $x$ 和 $y$ 的字母都没了，换成 $1$ 后就是题目给出的式子。

常见的还有取 $-1$ 和 $1$ 之类的操作。纯属经验问题。

但题目要减去两个其中的数。

![图片2](https://cdn.luogu.com.cn/upload/image_hosting/7iaj2sw9.png)

用这个式子，我们只要把分子和分母都分别求好，再用一下乘法逆元就行了。

---

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define f(a) ((a)*(a))
#define p(x) printf("%lld ",(x))
#define fp(x) printf("%.10Lf ",(x))
#define P() puts("")
#define lowbit(x) ((x)&(-(x)))
using namespace std;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
inline char cread()
{
	char c=getchar();
	while(!isalpha(c)) c=getchar();
	return c;
}

inline void write(int re)
{
	if (re>9) write(re/10);
	putchar(re%10+'0');
}
const int maxn=100010;
const int maxm=17;
const int mod=1e9+7;
int n,a,b;
int sum1,sum2,sum3,ans;
inline int qpow(int a,int b)
{
	int x=a,y=b,res=1;
	while(b)
	{
		if(b&1) 
			res=x*res%mod;
		x=x*x%mod;
		b>>=1;
	}
	return res%mod;
}
inline void exgcd(int &x,int &y,int a,int b)
{
	if(b==0)
	{
		x=1;y=0;
		return ;
	}
	exgcd(x,y,b,a%b);
	int t=x;x=y;
	y=t-(a/b)*x;
	
}
inline int C(int n,int m)
{
	int res1=1,res2=1;
	Rep(i,n,n-m+1)
		res1=res1*i%mod;//p(res1);P();
	For(i,1,m)
		res2=res2*i%mod;//p(res2);P();
	int a=res2,b=mod,x=0,y=0;
	exgcd(x,y,a,b);//p(x);P();
	x=((x%mod)+mod)%mod;
	return res1*x%mod;
}
signed main()
{
	//freopen("flower.in","r",stdin);
	//freopen("flower.out","w",stdout);
	n=read();a=read();b=read();
	sum1=qpow(2,n);
	sum2=C(n,a);//p(sum2);P();
	sum3=C(n,b);//p(sum3);P();
	ans=(sum1-1-sum2+mod+mod)%mod;
	ans=(ans-sum3+mod)%mod;
	p(ans);
}


```

---

感谢管理员的审核。


---

## 作者：Eason_AC (赞：0)

## Content
有一个人有 $n$ 种不同的话可供选择，TA 可以选择至少一种花做花束，但是 TA 不喜欢花的种数为 $a$ 或者 $b$ 的花束。求选花的方案数对 $10^9+7$ 取模。

**数据范围：$2\leqslant n\leqslant 10^9$，$1\leqslant a<b\leqslant\min\{n,2\times 10^5\}$。**
## Solution
简单的数数题。

我们先抛开『TA 不喜欢花的种数为 $a$ 或者 $b$ 的花束』这个条件不管，先来看如果是从 $n$ 种花中选至少一种花作为花束的方案数。很显然，每种花都有『选』或者『不选』这两种状态，那么就一共有 $2^n$ 种方案。但是又不能全部都不选，于是最终方案总数为 $2^n-1$。

我们再来看看不选种数为 $a$ 或者 $b$ 的方案总数。根据组合数的定义，我们可以很快求出**选花的种数为 $a$ 的方案**总数为 $C_n^a$，**选花的种数为 $b$ 的方案**总数为 $C_n^b$，又因为题目保证 $a\neq b$，因此**选花的种数为 $a$ 或者 $b$ 的方案**总数为 $C_n^a+C_n^b$。

那么，最终的答案就呼之欲出了，为 $2^n-1-C_n^a-C_n^b$。

那么我们该如何求出答案呢？

首先，$2^n$ 这个部分非常好办，直接上快速幂即可。

再然后就是组合数了。我们不妨先看到**费马小定理**和**乘法逆元**的定义。

- 费马小定理：如果 $p$ 是质数，则对于任意整数 $a$，都有 $a^p\equiv a\pmod p$，或者 $a^{p-1}\equiv 1\pmod p$。
- 乘法逆元：如果 $b,p$ 互质，且 $b\mid a$，则我们存在一个整数 $x$，使得 $\dfrac ab\equiv a\cdot x\pmod p$。

有了这两个东西，我们可以推导出 $a\times a^{p-2}\equiv 1\pmod p$，从而在计算组合数的时候就不用除一个数 $x$，直接乘上 $x^{p-2}$ 即可达到相同的效果。

回到求组合数，由于 $C_n^m=\dfrac{n!}{m!((n-m)!}=\dfrac{\prod\limits_{i=n-m+1}^ni}{m!}$，因此我们可以分两部分暴力去算出分子 $a$ 和分母 $b$，组合数就是 $a\times b^{mod-2}$。

这道题目就算做完了。
## Code
```cpp
const int N = 2e5 + 7, mod = 1e9 + 7;

ii ksm(int a, int b) {
	int res = 1;
	for(; b; b >>= 1, a = 1ll * a * a % mod) if(b % 2) res = 1ll * res * a % mod;
	return res;
}
ii C(int n, int m) {
	if(n < m || n < 0 || m < 0) return 0;
	int res1 = 1, res2 = 1;
	R(int, i, n, n - m + 1) res1 = 1ll * res1 * i % mod;
	R(int, i, m, 1) res2 = 1ll * res2 * i % mod;
	return 1ll * res1 * ksm(res2, mod - 2) % mod;
}

int main() {
	int n = Rint, a = Rint, b = Rint, ans = ksm(2, n) % mod;
	ans = (((ans - C(n, a) + mod) % mod -  C(n, b) + mod) % mod - 1 + mod) % mod;
	return println(ans), 0;
}
```

---

## 作者：leoair (赞：0)

# Bouquet

题目大意:给定整数$n$、$a$和$b$，求$C^0_n+C^1_n+C^2_n+......+C^n_n-C^a_n-C^b_n-1$。

这道题已经有了公式就可以做了。**但是，你有看数据范围吗？你如果直接用除法你不怕TLE吗？所以，我们来研究一下乘法逆元和费马小定理。**

如果你不懂同余是什么，请百度一下。

**费马小定理**:若$p$是质数，则对于任意整数$a$，有$a^p \equiv a(\bmod p)$(摘自**算法竞赛进阶指南**)

**乘法逆元**:

若整数$b$、$m$互质，并且$b \mid a$，则存在一个整数$x$，使得$a \div b \equiv a \times x(\bmod m)$。称$x$为$b$的模$m$乘法逆元，记为$b^{-1}(\bmod m)$(摘自**算法竞赛进阶指南**)

结合**费马小定理**和**乘法逆元**，可以推导出:$\begin{aligned}b^{p-1} & \equiv 1 \\ b \times b^{p-2} & \equiv 1 \end{aligned}$  

因此，有了**费马小定理**和**乘法逆元**，就可以在求组合数的时候把除法转换成乘法了。

接下来看看实现:

### Code:

```cpp
#include <bits/stdc++.h>
#define REP(i, a, b) for (long long i = a; i <= b; ++i)
#define PER(i, a, b) for (long long i = a; i >= b; --i)
#define lyj 1000000007
#define ll long long
using namespace std;

ll n, a, b;

inline ll read(){
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') w *= -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

inline ll ksm(ll c, ll d){														//快速幂 
	ll sum = 1;																	//初始赋值为1 
	for (; d; d >>= 1, c = c * c % lyj)											//d不为0则除以2 
		if (d & 1) sum = sum * c % lyj;											//d为奇数的特判
	return sum;																	//返回答案 
}

inline ll xcj(ll n, ll m){														//求组合数 
	ll a1 = 1, a2 = 1;															//初始赋值为1 
	PER(i, n, n - m + 1) a1 = a1 * i % lyj;										//求约分后的n! 
	REP(i, 2, m) a2 = a2 * i % lyj;												//求约分后的m!(n - m)!
	return a1 * ksm(a2, lyj - 2) % lyj;											//费马小定理 
}

int main(){
	n = read(), a = read(), b = read();
	printf("%lld\n", (ksm(2, n) - 1 - xcj(n, a) - xcj(n, b) + lyj + lyj) % lyj);//求没有限制下的方案数减去题目的限制条件 
	return 0;
}
```



---

## 作者：_zexal_ (赞：0)

注意到本题 $n \leq 10^9$，直接求和组合数肯定会炸，所以不妨考虑换一种思路，我们不妨直接求出所有花的搭配方案总和，再减去不合法的两种即可。这并不难办，因为所有的方案就等于这一个式子。
$$\sum_{i=0}^{n} C_{n}^{i} = 2^{n}$$
我们用二项式定理就可以得证这个式子。接着，我们考虑减去不合法的那两个即可。注意到 $b \leq 2\times 10^5$。直接暴力算即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define F(i,a,b) for(int i=(a); i<=(b); ++i)
#define R(i,a,b) for(int i=(a); i>=(b); --i)
using namespace std;
const int Mod=1e9+7;
const int Maxn=2e6+5;
inline int read();
int gcd(int a,int b);
int fac[Maxn];
int ksm(int a,int b,int mod);
void init();
int inv(int a,int mod);
int C(int n,int m);//C_n ^ m
int a[Maxn],n,m,k,q,mod,x=1,y=1,sum,ans;
signed main() {
	init();
	cin>>n>>k>>q;
	int n1=n;
	ans=ksm(2,n,Mod)%Mod;
	ans%=Mod;
	//cout<<ans<<endl;
	//cout<<fac[q]<<endl;
	for(int i=1; i<=k; i++) {
		x*=n1;
		n1-=1;
		x%=Mod;
	}
	n1=n;
	for(int i=1; i<=q; i++) {
		y*=n1;
		n1-=1;
		y%=Mod;
	}
	//cout<<x<<" "<<y<<endl;
//	cout<<inv(fac[k],Mod)%Mod<< " "<<fac[q]<<endl;
	ans=(ans-(x*(inv(fac[k],Mod)%Mod))+Mod)%Mod;
	ans=(ans-(y*(inv(fac[q],Mod)%Mod))%Mod+Mod)%Mod;
	cout<<(ans+Mod)%Mod-1;
	return 0;
}
void init() {
	fac[0]=1;
	for(int i=1; i<=Maxn; i++) {
		fac[i]=fac[i-1]*i;
		fac[i]%=Mod;
	}
	return;
}
long long read() {
	long long t=0,f=0;
	char v=getchar();
	while(!isdigit(v))f|=(v=='-'),v=getchar();
	while(isdigit(v))t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
inline int inv(int a,int mod) {
	return ksm(a,mod-2,mod);
}
int gcd(int a,int b) {
	if(a<b) swap(a,b);
	if(b==0) return a;
	else return gcd(b,a%b);
}
inline int C(int n,int m) {
	return (fac[n]*inv(fac[m],Mod)%Mod*inv(fac[n-m],Mod)%Mod)%Mod;
}
inline int ksm(int a,int b,int mod) {
	int z=1;
	while(b) {
		if(b&1) z=z*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return z%mod;
}
/*

*/


```


---

