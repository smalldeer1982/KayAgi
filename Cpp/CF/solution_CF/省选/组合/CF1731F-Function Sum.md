# Function Sum

## 题目描述

Suppose you have an integer array $ a_1, a_2, \dots, a_n $ .

Let $ \operatorname{lsl}(i) $ be the number of indices $ j $ ( $ 1 \le j < i $ ) such that $ a_j < a_i $ .

Analogically, let $ \operatorname{grr}(i) $ be the number of indices $ j $ ( $ i < j \le n $ ) such that $ a_j > a_i $ .

Let's name position $ i $ good in the array $ a $ if $ \operatorname{lsl}(i) < \operatorname{grr}(i) $ .

Finally, let's define a function $ f $ on array $ a $ $ f(a) $ as the sum of all $ a_i $ such that $ i $ is good in $ a $ .

Given two integers $ n $ and $ k $ , find the sum of $ f(a) $ over all arrays $ a $ of size $ n $ such that $ 1 \leq a_i \leq k $ for all $ 1 \leq i \leq n $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

  $ f([1,1,1]) = 0 $  $ f([2,2,3]) = 2 + 2 = 4 $  $ f([1,1,2]) = 1 + 1 = 2 $  $ f([2,3,1]) = 2 $  $ f([1,1,3]) = 1 + 1 = 2 $  $ f([2,3,2]) = 2 $  $ f([1,2,1]) = 1 $  $ f([2,3,3]) = 2 $  $ f([1,2,2]) = 1 $  $ f([3,1,1]) = 0 $  $ f([1,2,3]) = 1 $  $ f([3,1,2]) = 1 $  $ f([1,3,1]) = 1 $  $ f([3,1,3]) = 1 $  $ f([1,3,2]) = 1 $  $ f([3,2,1]) = 0 $  $ f([1,3,3]) = 1 $  $ f([3,2,2]) = 0 $  $ f([2,1,1]) = 0 $  $ f([3,2,3]) = 2 $  $ f([2,1,2]) = 1 $  $ f([3,3,1]) = 0 $  $ f([2,1,3]) = 2 + 1 = 3 $  $ f([3,3,2]) = 0 $  $ f([2,2,1]) = 0 $  $ f([3,3,3]) = 0 $  $ f([2,2,2]) = 0 $ Adding up all of these values, we get $ 28 $ as the answer.

## 样例 #1

### 输入

```
3 3```

### 输出

```
28```

## 样例 #2

### 输入

```
5 6```

### 输出

```
34475```

## 样例 #3

### 输入

```
12 30```

### 输出

```
920711694```

# 题解

## 作者：NaCly_Fish (赞：29)

[题目链接](https://www.luogu.com.cn/problem/CF1731F) $\Theta(\log n)$ 解法。

先说结论，对于 $n>1$：
$$F(x)=\sum_{i=1}^n\sum_{j=0}^{i-1}\binom{i-1}{j}(x-1)^j(m-x+1)^{i-j-1}\sum_{k=j+1}^{n-i}\binom{n-i}{k}(m-x)^kx^{n-i-k}$$
满足 $\deg F(x) = 1$（式中的 $m$ 就是题面中的 $k$）。  



****
首先可以发现，如果最内层和式的 $k$ 每次都从 $0$ 取到 $n-i$，那结果必然是一个常数。考虑将其取值范围改为 $0$ 到 $j$，此结果的度数不大于 $1$，当且仅当 $\deg F(x)\leq 1$：

$$G(x)=\sum_{i=1}^n\sum_{j=0}^{i-1}\binom{i-1}{j}(x-1)^j(m-x+1)^{i-j-1}\sum_{k=0}^j\binom{n-i}{k}(m-x)^kx^{n-i-k}$$

然后我们可以根据
$$\binom{n-i}{k}=[y^{n-i}]\frac{y^k}{(1-y)^{k+1}}$$
将上式化为
$$\begin{aligned} G(x)&=\sum_{i=1}^n[y^{n-i}]\sum_{j=0}^{i-1}\binom{i-1}{j}(x-1)^j(m-x+1)^{i-j-1}\sum_{k=0}^j \frac{y^k(m-x)^k}{(1-xy)^{k+1}}\\ &= \sum_{i=1}^n[y^{n-i}]\sum_{j=0}^{i-1} \binom{i-1}{j}\frac{(x-1)^j(m-x+1)^{i-j-1}}{1-my}\left( 1-\frac{(m-x)^{j+1}y^{j+1}}{(1-xy)^{j+1}}\right)\end{aligned}$$
同样我们发现 $G(x)$ 中提取出一部分是常数，就只需要证明此式度数不大于 $1$：
$$\sum_{i=1}^n[y^{n-i}] \frac{(m-x)y}{(1-xy)(1-my)}\sum_{j=0}^{i-1}\binom{i-1}{j}\left(\frac{(x-1)(m-x)y}{1-xy}\right)^j(m-x+1)^{i-j+1}$$
式子中还可以提取出一个 $(m-x)$ 来，那就只需要证明此式度数为零即可：
$$ \begin{aligned}& [y^n]\sum_{i=1}^n \frac{y^{i+1}}{(1-xy)(1-my)}\left( \frac{(x-1)(m-x)y}{1-xy}+(m-x+1)\right)^{i-1} \\ &= [y^n]\frac{y^2}{(1-xy)(1-my)}\sum_{i=0}^\infty y^i\left( \frac{(x-1)(m-x)y}{1-xy}+(m-x+1)\right)^i \end{aligned}$$
把 $i$ 的求和上界调到无穷大是常用技巧，因为提取 $i>n$ 项的系数必然为零。这样就化简为
$$\begin{aligned} & [y^n]\frac{y^2}{(1-xy)(1-my)} \times \frac{1}{1-y\left( \frac{(x-1)(m-x)y}{1-xy}+(m-x+1)\right)} \\ &=[y^n] \frac{y^2}{(1-my)} \times \frac{1}{(1-xy)-y\left((x-1)(m-x)y+(m-x+1)(1-xy) \right)}  \\ &= [y^n] \frac{y^2}{(1-my)}\times \frac{1}{(1-y)(1-my)}\end{aligned}$$
是一个常数，命题得证。
****
有了这个结论，我们就可以根据

$$F(1)=nm^{n-1}-\frac{1-m^n}{1-m} \ , \ F(m)=0$$
直接解出
$$F(x)=\frac{1+m^{n-1}(nm-n-m)}{(1-m)^2}(m-x)$$
答案为
$$\sum_{i=1}^m i F(i)=\frac{1+m^{n-1}(nm-n-m)}{(1-m)^2}\binom{m+1}{3}$$
时间复杂度 $\Theta(\log n)$。


---

## 作者：xixike (赞：3)

## Description

题目大意：

对于一个长度为 $n$ 的数列 $a$。

定义 $lsl(i)$ 表示 $i$ 左边的数中比 $a_i$ 小的数的个数，即 $\sum\limits_{j = 1}^{i - 1}[a_j < a_i]$。

同样的定义 $grr(i)$ 表示 $i$ 右边的比 $a_i$ 大的数的个数，即 $\sum\limits_{j = i + 1}^n[a_j > a_i]$。

我们称一个位置是好的当且仅当 $lsl(i) < grr(i)$。

我们再对于一个数列 $a$ 定义一个函数 $f(a)$ 为 $\sum\limits_{i = 1}^na_i[i\  \text{is good}]$。

现在给定两个整数 $n, k$，请你求出对于所有长度为 $n$ 且 $1 \leq a_i \leq k$ 的数列 $a$ 的 $f(a)$ 的和是多少。

答案对 $\text{998244353}$ 取模。

## Solution

观察到 $n \leq 50$，启示我们要用 $O(n^4)$ 甚至 $O(n^5)$ 的算法。

那么我们就需要什么枚举什么就行了。

设 $F(t)$ 表示数列中存在一个数等于 $t$ 时对答案的贡献。

我们枚举第 $i$ 个位置等于 $t$，再枚举 $lsl(i)$ 和 $grr(i)$ 分别等于 $x, y$。

那么不难写出一个式子：

$$
F(t) = t \times \sum_{i = 1}^n\sum_{x = 0}^{i - 1}\sum_{y = x + 1}^{n - i}(\dbinom {i - 1}{x}(t - 1)^x(k - t + 1)^{i - 1 - x} \times \dbinom {n - i}{y}(k - t)^yt^{n - i - y})
$$

相信大家一定都能看懂这个式子。

最后答案就是

$$
G(k) = \sum_{i = 1}^kF(i)
$$

但是我们明显无法直接算出来，拉插一下就好了。

时间复杂度 $O(n^4\log n)$

## Code

```cpp
#include <bits/stdc++.h>
#define pb push_back

using namespace std;

namespace IO{
    inline int read(){
        int x = 0, f = 1;
        char ch = getchar();
        while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x * f;
    }

    template <typename T> inline void write(T x){
        if(x < 0) putchar('-'), x = -x;
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 60;
const int mod = 998244353;
int n, k;
int f[N], c[N][N];

inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline int mul(int x, int y) {return 1ll * x * y % mod;}

inline int qpow(int a, int b){
    int res = 1;
    while(b){
        if(b & 1) res = mul(res, a);
        a = mul(a, a), b >>= 1;
    }
    return res;
}

inline int Inv(int x) {return qpow(x, mod - 2);}

inline int lagrange(int n, int k){
    int res = 0;
    for(int i = 1; i <= n; ++i){
        int t1 = f[i], t2 = 1;
        for(int j = 1; j <= n; ++j)
            if(i != j) t1 = mul(t1, k - j), t2 = mul(t2, sub(i - j));
        res = add(res + mul(t1, Inv(t2)));
    }
    return res;
}

signed main(){
#ifndef ONLINE_JUDGE
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    n = read(), k = read();
    for(int i = 0; i <= n; ++i) c[i][0] = 1;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            c[i][j] = add(c[i - 1][j - 1] + c[i - 1][j]);
    for(int t = 1 ; t <= min(n + 2, k); ++t){
        int sum = 0;
        for(int i = 1; i <= n; ++i)
            for(int x = 0; x <= i - 1; ++x)
                for(int y = x + 1; y <= n - i; ++y){
                    int t1 = mul(c[i - 1][x], mul(qpow(t - 1, x), qpow(k + 1 - t, i - 1 - x)));
                    t1 = mul(t1, mul(c[n - i][y], mul(qpow(k - t, y), qpow(t, n - i - y))));
                    sum = add(sum + t1);
                }
        f[t] = mul(t, sum);
    }
    for(int i = 1; i <= n + 2; ++i) f[i] = add(f[i] + f[i - 1]);
    if(k <= n + 2) write(f[k]), puts("");
    else write(lagrange(n + 2, k)), puts("");
    return 0;
}
```

---

## 作者：sunnygreen (赞：1)

先转化一下 $\operatorname{lsl}(i) < \operatorname{grr}(i)$ 这个限制。

注意到 $\operatorname{lsl}(i) = i - \displaystyle\sum_{j=1}^{i} \left [a_j \ge a_i \right ]$。

代入并移项，得到 $i < \displaystyle\sum_{j=1}^{n} \left [a_j > a_i \right ] + \displaystyle\sum_{j=1}^{i} \left [a_j = a_i \right ]$。

枚举 $i,l,r,g$，其中 $l = \displaystyle\sum_{j=1}^{i} \left [a_j = a_i \right ], r = \displaystyle\sum_{j=i+1}^{n} \left [a_j = a_i \right ], g = \displaystyle\sum_{j=1}^{n} \left [a_j > a_i \right ]$。注意 $l \ge 1$。

那么贡献为：

$$ \left [l+g > i \right ] \binom{i-1}{l-1} \binom{n-i}{r} \binom{n-l-r}{g} \sum_{j=1}^{k} (k-j)^{g} (j-1)^{n-l-r-g} j$$

这样枚举的好处是有关 $k$ 的项更简洁。考虑化简，使用二项式定理。

令 $f(y,t) = \displaystyle\sum_{j=1}^{k} (k-j)^{t} (j-1)^{y-t} j$。

$$
\begin{aligned}
f(y,t)
& = \sum_{j=0}^{k-1} (k-1-j)^{t} j^{y-t} (j+1) \\
& = \sum_{j=0}^{k-1} \sum_{i=0}^{t} (-1)^{t-i} \binom{t}{i} (k-1)^{i} j^{t-i} j^{y-t} (j+1) \\
& = \sum_{j=0}^{k-1} \sum_{i=0}^{t} (-1)^{t-i} \binom{t}{i} (k-1)^{i} \left ( j^{y-i} + j^{y-i+1} \right ) \\
& = \sum_{i=0}^{t} (-1)^{t-i} \binom{t}{i} (k-1)^{i} \sum_{j=0}^{k-1} \left ( j^{y-i} + j^{y-i+1} \right )
\end{aligned}
$$

再令 $h(t) = \displaystyle\sum_{j=0}^{k-1} j^t$。注意到指数只有 $O(n)$，考虑第二类斯特林数。

$$
\begin{aligned}
h(t)
& = \sum_{j=0}^{k-1} \sum_{i=0}^{j} \binom{j}{i} i! { t \brace i } \\
& = \sum_{i=0}^{\min(t,k-1)} i! { t \brace i } \sum_{j=i}^{k-1} \binom{j}{i} \\
& = \sum_{i=0}^{\min(t,k-1)} i! { t \brace i } \binom{k}{i+1}
\end{aligned}
$$

预处理 $h(t)$ 即可，总时间复杂度 $O(n^5)$，常数很小。

代码，当 $n = 50$ 时最内层循环仅执行 $5739370$ 次。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define fi first
#define se second
#define mk make_pair
#define eb emplace_back
#define rep(i,l,r) for(int i=(l); i<=(r); ++i)
#define rep_(i,l,r) for(int i=(l); i>=(r); --i)
typedef long long lr;
typedef unsigned long long ull;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
constexpr int mod1=998244353,mod2=1e9+7;
constexpr db pi=3.141592653589793,eps=1e-9;
constexpr int inf32=0x3f3f3f3f,Inf32=0xc0c0c0c0;
constexpr lr inf64=0x3f3f3f3f3f3f3f3f,Inf64=0xc0c0c0c0c0c0c0c0;
template<typename T>il T Max(T x,T y) { return (x>y)? x:y; }
template<typename T>il T Min(T x,T y) { return (x<y)? x:y; }
template<typename T>il T gcd(T x,T y) { return (!y)? x:gcd(y,x%y); }
template<typename T>il T Abs(T x) { return (x>0)? x:(-x); }
template<typename T>il T Rnd(T l,T r,mt19937_64 &eng)
{
	uniform_int_distribution<T> uid(l,r);
	return uid(eng);
}
mt19937_64 eng(chrono::high_resolution_clock::now().time_since_epoch().count());
using Int=const int&;
using U=unsigned;
constexpr int N=55,mod=mod1;
namespace Comb
{
	using V=int; const int NN=N;
	V fac[NN],inv[NN];
	il V Poww(V x,V y)
	{
		V mul=1;
		while(y)
		{
			if(y&1)
				mul=(ull)mul*x%mod;
			x=(ull)x*x%mod,y>>=1;
		}
		return mul;
	}
	il void Init(Int _)
	{
		fac[0]=1;
		rep(i,1,_)
			fac[i]=(ull)fac[i-1]*i%mod;
		inv[_]=Poww(fac[_],mod-2);
		rep_(i,_,1)
			inv[i-1]=(ull)inv[i]*i%mod;
	}
}
il void Reduce(int &_) { (_>=mod)&&(_-=mod); }
int n,k,pwn[N],f[N],s[N][N],c[N][N];
il int calc(int x,int y)
{
	int mul=1;
	rep(i,1,y)
		mul=(ull)mul*(x-i+1)%mod;
	return (ull)mul*Comb::inv[y]%mod;
}
il void Solve()
{
	cin>>n>>k,Comb::Init(n+1);
	pwn[0]=1;
	rep(i,1,n)
		pwn[i]=(ull)pwn[i-1]*(k-1)%mod;
	s[0][0]=1;
	rep(i,1,n)
		rep(j,1,i)
			s[i][j]=((ull)s[i-1][j]*j+s[i-1][j-1])%mod;
	c[0][0]=1;
	rep(i,1,n)
	{
		c[i][0]=1;
		rep(j,1,i)
			Reduce(c[i][j]=c[i-1][j-1]+c[i-1][j]);
	}
	rep(i,0,n)
		rep(b,0,Min(k-1,i))
			f[i]=(f[i]+(ull)Comb::fac[b]*s[i][b]%mod*calc(k,b+1))%mod;
	int ans=0;
	rep(i,1,n)
		rep(l,1,i)
			rep(r,0,n-i)
			{
				int y=n-l-r,tmp=0;
				rep(g,i-l+1,y)
				{
					lr tmp2=0;
					rep(j,0,g)
					{
						int tmp3=(ull)c[g][j]*pwn[j]%mod*(f[y-j]+f[y-j+1])%mod;
						((g-j)&1)? tmp2+=mod-tmp3:tmp2+=tmp3;
					}
					tmp=(tmp+tmp2%mod*c[y][g])%mod;
				}
				ans=(ans+(ull)tmp*c[i-1][l-1]%mod*c[n-i][r])%mod;
			}
	cout<<ans<<'\n';
}
int main()
{
#ifdef LOCAL
	string fpre="test",isuf="in",osuf="out";
	assert(freopen((fpre+"."+isuf).c_str(),"r",stdin));
	assert(freopen((fpre+"."+osuf).c_str(),"w",stdout));
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T=1;
	while(T--)
		Solve();
	return 0;
}
```

---

## 作者：arundo (赞：1)

CF1731F Function Sum 题解。

枚举所有能枚举的东西，可以得到一个式子。

$$\sum_{p=1}^n\sum_{i=0}^{p-1}\sum_{j=i+1}^{n-p}\sum_{w=1}^k w{p-1\choose i}(w-1)^i(k-w+1)^{p-1-i}{n-p\choose j}(k-w)^jw^{n-p-j}$$

即选择 good 的位置 $p$，枚举左边比其小的个数 $i$ 和右边比其大的个数 $j$，分别分配位置和值。

这个式子最大的问题是枚举了 $w$。那么尝试将 $w$ 提到外面。观察发现所有的二项式系数都与 $w$ 和 $k$ 没有关系，而指数都是关于 $n$ 的。发现如果将其看成一个关于 $k$ 的函数 $f(k)$，则其次数最多为 $n+1$。

因此暴力算出前 $n+2$ 项后插值即可。

---

## 作者：Helenty (赞：0)

我们考虑算 $a_i$ 在全部 $k^n$ 种数列中有多少是好的的数量乘 $a_i$。

注意到一个位置一个值左大于右和对称位置这个值右大于左应该是等的，我们考虑用减掉左等于右除二即可。

我们枚举 $i,a_i=j,\text{lsl}(i)=\text{grr}(i)=p$ 即可。

对于 $a_i$ 下面这个记得除二：

$$\sum_{j=1}^kj\times(k^{n-1}-\sum_{p=0}^{\min\{i-1,n-i\}}\binom{i-1}{p}\binom{n-i}{p}(j-1)^{n-i}(k-j)^{i-1})$$

$$\dfrac{k^n(k+1)}{2}-\sum_{j=1}^kj\sum_{p=0}^{\min\{i-1,n-i\}}\binom{i-1}{p}\binom{n-i}{p}(j-1)^{n-i}(k-j)^{i-1}$$

$$\dfrac{k^n(k+1)}{2}-\sum_{p=0}^{\min\{i-1,n-i\}}\binom{i-1}{p}\binom{n-i}{p}\sum_{j=1}^k(j-1)^{n-i+1}(k-j)^{i-1}$$

考虑 $F(j)=(j-1)^{n-i+1}(k-j)^{i-1}$ 是一个 $n$ 次多项式，我们直接插值即可。

复杂度是 $O(n^3\log n)$ 的。

---

## 作者：DerrickLo (赞：0)

先考虑暴力怎么做。

枚举 $j$ 和 $i$ 表示 $a_i=j$，再枚举 $x$ 与 $y$ 表示左边比 $a_i$ 小的个数与右边比 $a_i$ 大的个数，那么答案就是：

$$\sum_{i=1}^{k}\sum_{j=1}^{n}\sum_{x=0}^{j-1}\sum_{y=x+1}^{n-j}i\times (i-1)^x\times (k-i+1)^{j-1-x}\times (k-i)^y\times i^{n-j-y}\times \dbinom{j-1}{x}\times \dbinom{n-j}{y}$$

我们发现里面这个式子可以把 $x$ 和 $y$ 拆开算，所以算一次的复杂度是 $\mathcal O(kn^2\log n)$ 的。

但是 $k$ 太大了。我们发现这个式子是关于 $k$ 的多项式，而这个多项式的阶也是 $\mathcal O(n)$ 级别的，所以可以直接将前 $4n$ 项算出来然后直接拉插。

时间复杂度 $\mathcal O(n^4\log n)$，预处理幂次可以将这个 $\log$ 去掉。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int n,k,fac[55],inv[55],ans,x[205],y[205],s[55];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
int C(int n,int m){
	if(n<m)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int lagrange(int *x,int *y,int xx){
	int ans=0;
	for(int i=1;i<=4*n;i++){
		int a=1,b=1;
		for(int j=1;j<=4*n;j++)if(i!=j)a*=xx-x[j],a%=mod,b*=x[i]-x[j],b%=mod;
		ans+=a*ksm(b,mod-2)%mod*y[i]%mod,ans+=mod,ans%=mod;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k,fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2);
	for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int p=1;p<=4*n;p++){
		x[p]=p,y[p]=0;
		for(int i=1;i<=p;i++){
			for(int j=1;j<=n;j++){
				memset(s,0,sizeof s);
				for(int b=n-j;b;b--)s[b]=s[b+1]+C(n-j,b)*ksm(p-i,b)%mod*ksm(i,n-j-b)%mod,s[b]%=mod;
				for(int a=0;a<j;a++)y[p]+=C(j-1,a)*ksm(i-1,a)%mod*ksm(p-i+1,j-1-a)%mod*s[a+1]%mod*i%mod,y[p]%=mod;
			}
		}
	}
	cout<<lagrange(x,y,k);
	return 0;
}
```

---

