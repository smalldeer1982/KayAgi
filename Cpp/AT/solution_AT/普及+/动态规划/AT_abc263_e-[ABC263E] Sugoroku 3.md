# [ABC263E] Sugoroku 3

## 题目描述

一共有 $N$ 个格子编号 $1$ 到 $N$。有一个人站在 $1$ 号格子。

对于 $\forall i \in [1,N-1]$ 号格子有一个 $A_i + 1$ 面的骰子，写有 $0$ 到 $A_i$ 这些数。如果 ta 掷到了 $k$，他将往前走 $k$ 格，走到 $i+k$ 号方格。

求走到 $N$ 号方格的期望次数。对 $998244353$ 取模。

## 说明/提示

$2\leq N\leq 2\times 10^5$

$\forall i \in [1,N-1],1\leq A_i\leq N-i$

## 样例 #1

### 输入

```
3
1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
5
3 1 2 1```

### 输出

```
332748122```

# 题解

## 作者：Ginger_he (赞：6)

## 题目描述

一个人初始站在 $1$ 处，每次从 $i$ 等概率地走到 $i,i+1,\ldots,i+a_i$，求到达 $n$ 的步数期望，答案对 $998244353$ 取模。

## 题解

正着做不知道从哪个点转移过来，所以考虑反着做，$dp_i$ 表从 $i$ 走到 $n$ 的期望步数。

因为每个点可以走到 $i,i+1,\ldots,i+a_i$，因此易得

$$dp_i=1+\frac{1}{a_i+1}\sum_{k=i}^{i+a_i}dp_k$$

化简可得

$$dp_i=\frac{a_i+1}{a_i}+\frac{1}{a_i}\sum_{k=i+1}^{i+a_i}dp_k$$

后半部分可以用后缀和优化，于是就能 $\Theta(n)$ 解决这道题。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
const ll p=998244353;
int n;
ll a[N],dp[N],s[N],inv[N];
int main()
{
	scanf("%d",&n);
	inv[1]=1;
	for(int i=2;i<N;i++)
		inv[i]=(p-p/i)*inv[p%i]%p;
	for(int i=1;i<n;i++)
		scanf("%lld",&a[i]);
	for(int i=n-1;i>=1;i--)
	{
		dp[i]=(((s[i+1]-s[i+a[i]+1])%p+p)%p+a[i]+1)%p*inv[a[i]]%p;
		s[i]=(s[i+1]+dp[i])%p;
	}
	printf("%lld\n",dp[1]);
	return 0;
}
```

---

## 作者：ZBH_123 (赞：2)

### 思路：期望 dp
#### 1.设计状态
对于本题，我们可以设 $dp_i$ 为从 $i$ 号格子走到 $n$ 号格子的期望步数。那么很显然，$dp_n=0$，答案就是 $dp_1$。
#### 2.状态转移方程
按照设计的状态，我们很容易就能推出状态转移方程。由于在每个格子都只能往右跳，所以我们可以从 $n-1$ 开始倒着往前推。那么，对于 $i$ 号格子，$dp_i$ 等于多少呢？第 $i$ 个格子到 $n$ 号格子的期望步数肯定等于它能直接到达的格子的期望步数加一再除以 $i$ 能到达的格子的数量，而 $dp_{i+1} \sim dp_{i+a_i}$ 已经算出，所以我们可以得到下面这个状态转移方程：
$$dp_i = \sum_{j=0}^{a_i} (dp_{i+j}+1) \div (a_i+1)$$
#### 3.化简
由于在上面的状态转移方程中，$dp_i$ 要被用到，但还不清楚具体的值，所以我们要对上式化简：
$$dp_i = \sum_{j=0}^{a_i} (dp_{i+j}+1) \div (a_i+1)$$
整理得：
$$dp_i \cdot (a_i+1)=a_i+1+\sum_{j=0}^{a_i} dp_{i+j}$$
最后可以得到下面这个式子：
$$dp_i=(a_i+1+\sum_{j=1}^{a_i} dp_{i+j}) \div a_i$$
这样我们就可以考虑用后缀和维护 $\sum_{j=1}^{a_i} dp_{i,j}$ 的值。这样就可以用 $O(n)$ 的时间复杂度解决本题了。

由于题目最后要对答案取模，所以我们要把除法转换为乘模 $998244353$ 意义下的逆元。

**AC code:**
```cpp
#include<iostream>
using namespace std;
#define int long long
const int maxn=2e5,mod=998244353;
int n,a[maxn+5],dp[maxn+5],sum[maxn+5],inv[maxn+5];
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>a[i];
	}
	inv[1]=1;
	for(int i=2;i<n;i++){
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	}
	for(int i=n-1;i>=1;i--){
		dp[i]=(a[i]+1+(sum[i+1]-sum[i+a[i]+1]+mod)%mod)%mod*inv[a[i]]%mod;
		sum[i]=(sum[i+1]+dp[i])%mod;
	}
	cout<<dp[1];
	return 0;
}
```

---

## 作者：LastKismet (赞：1)

# [ABC263E](https://atcoder.jp/contests/abc263/tasks/abc263_e) - **Sugoroku 3** | **双陆旗 3**

# Points

1.  期望
2.  后缀和
3.  期望DP
4.  乘法逆元

# Analysis
*期望值，就是对于所有可能的事件，都用它的权值乘它的发生概率，最后求和。*

首先，我们可以将 _掷骰子数_，视作 _行走步数_。假设我们设点 $i$ 的期望值为 $dp_i$，由于在终点无需再次前进，易得 $dp_n=0$。

接下来，我们考虑状态的转移。

但在此之前，我们需要证明当前事件的期望值与它通向的所有期望值关系，才能构建正确方程。

![图示](https://cdn.luogu.com.cn/upload/image_hosting/0mk1dn3b.png)

这里我们当前点在 $A$ 点，有一条 $a$ 权值 $P_1$ 概率的路径通向 $B$，而 $B$ 所有路径中有一条 $b$ 权值 $P_2$ 概率的路径通向终点。

在这个问题中，$P_1,P_2,a,b$ 都是已知的，我们就可以得出这条路径中 **$A$ 到终点的期望值**。
$$
E=P_1 P_2 (a+b)
$$
毫无疑问地，这条道路的总概率就是二者的概率乘积，而总权值就是二者权值之和。

**但是，我们需要的是当前的期望值与下一个点的期望值的关系。**

在下面的公式中，使用 $W$ 代表权值：
$$
E_B=\sum_{j=0}^{a_B}(P_{B,j}W_{B,j})
$$
_具体的，$j$ 表示当前遍历到的下一步点的路径编号。_
$$
\begin{align}
E_A &= \sum_{j=0}^{a_A}(P_{A,j}W_{A_j}) \\
	&= \sum_{j=0}^{a_A}\sum_{k=0}^{a_{B_j}}[P_{1,j}P_{B_j,k}(W_{1,j}+W_{B_j,k})]
\end{align}
$$
_注：此处 $P_1$ 及 $W_1$ 代 $A$ 到 $B$ 的一条路径，而 $P_A$ $W_A$ 则代 $A$ 到 $C$ 的一条路径。（$D$ 为某一点）额外地，令 $B_j$ 为 $A$ 路径 $j$ 指向的点。_

毫无疑问地，$P_1$ 以及 $W_1$ 都是已知的，并且在此题中 $P_1$ 和 $W_1$ 一定，所以：
$$
\begin{align}
E_A &= \sum_{j=0}^{a_A}\sum_{k=0}^{a_{B_j}}[P_{1,j}P_{B_j,k}(W_{1,j}+W_{B_j,k})] \\
	&= P_1\sum_{j=0}^{a_A}\sum_{k=0}^{a_{B_j}}[P_{B_j,k}(W_1+W_{B_j,k})] \\
	&= P_1\sum_{j=0}^{a_A}[\sum_{k=0}^{a_{B_j}}P_{B_j,k}W_1+\sum_{k=0}^{a_{B_j}}(P_{B_j}W_{B_j,k})] \\
	&= \sum_{j=0}^{a_A}[P_1(W_1+E_{B_j})]
\end{align}
$$
*注：$\sum_{k=0}^{a_{B_j}}P_{B_j,k}=1$，因为所有概率的总和为 $1$。*

细致到这道题中，也就是：
$$
E_A = \sum_{j=0}^{a_A}\frac{E_{B_j}+1}{a_A+1}
$$
*注：每条边权值都为 $1$，每种可能概率均等，共有 $a_A+1$ 种可能（包括 $0$）。*

-----

其实我们还有一个更简单的~~理解~~记忆方法。

我们可以将 _期望_ 视作均值，那么某一条 $A$ 到 $C$ 路径的权值，就可以视作 $B$ 到 $C$ 路径的权值均值加上 $A$ 到 $B$ 的权值。

大概可以写成下面这个样子：
$$
W_A=W_1+E_B
$$

$$
E_A = \sum_{j=0}^{a_A}[P_1(W_1+E_{B_j})]
$$

-----

并未结束，我们还要特别考虑 $j=0$ 的情况。

首先，我们提出：$A$ 到 $B$ 的路径，**是包含在某一条 $B$ 到 $C$ 的路径之内的**。究其原因，是因为 $A$ 也有可能成为 $B$ ，也就是当 $j=0$ 时圈地踏圈。

这貌似是一种永无止尽的情况。但事实上，**我们考虑的路径，都是指向 $C$ 的，所以我们所考虑的路径中不包含“永无止尽”的情况**。

那么，我们就可以肯定，即使是 $j=0$ ，也能够求出期望值。

但是，如果我们希望通过**递推**的方式求出期望值，那么就需要把上述这个方程改成一个递推方程式。
$$
\begin{align}
E_A &= \sum_{j=0}^{a_A}\frac{E_{B_j}+1}{a_A+1}  \\
E_A &= \sum_{j=1}^{a_A}\frac{E_{B_j}+1}{a_A+1} + \frac{E_A+1}{a_A+1} \\
(a_A+1)E_A &= \sum_{j=1}^{a_A}(E_{B_j}+1) + E_A + 1 \\
E_A &= \frac{\sum_{j=1}^{a_A}E_{B_j} + a_A + 1}{a_A} \\
E_A &= \frac{\sum_{j=1}^{a_A}E_{B_j} + 1}{a_A} + 1 \\
\end{align}
$$
完成。

# Solution

1.  虽然我们无法确定当前点由哪一个点转移过来，但我们可以确定当前点可以转移到哪一个点，故而我们使用**倒推法**。
2.  由于 $E_{B_j}$ 是连续的一段，我们可以使用**后缀和**求。
3.  介于取模，使用乘法逆元。这里模数是个质数，使用快速幂法。

#  Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=998244353,N=2e5+5;

int n;
int a[N];
ll f[N],s[N];

ll qkm(ll a,int b){
	ll t=1;
	while(b>0){
		if(b&1)t=t*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return t;
}

ll inv(ll num){
	return qkm(num,mod-2)%mod;
}

void solve(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>a[i];
	}
	f[n]=0;s[n]=0;
	for(int i=n-1;i>=1;i--){
		f[i]=((s[i+1]+(mod-s[i+a[i]+1])+1)%mod*inv(a[i])%mod+1)%mod;
		s[i]=(s[i+1]+f[i])%mod;
	}
	cout<<f[1];
}

int main(){
	int t;t=1;
	while(t--){
		solve();
	}
	return 0;
}

```

# Essentials

1.  期望DP。

    通常使用倒推法，公式及推导见Ana部分。

2.  乘法逆元。

    模数为质数推荐快速幂法，是否质数都可以用拓欧求。

---

## 作者：CQ_Bab (赞：1)

# 思路
我们首先可以知道这是一个期望 Dp，然后我们可以定义状态为 $f_i$ 就是从 $i$ 走到 $n$ 的概率，这你要倒着定义是因为我们不能确定上一步是从哪里走来的，但可以确定走到哪里去。然后我们明显可以得到一个转移方程就是 $f_i=(a_i+1+\sum_{j=i+1}^{i+a_i} f_j)\div a_i$ 那么这里我们明显可以用一个后缀和处理即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
const int N=2e6+10,p=998244353;
int a[N],f[N],n;
int s[N],inv[N];
inline qmi(int a,int g) {
	int res=1;
	while(g) {
		if(g&1) res=(res*a)%p;
		a=(a*a)%p;
		g>>=1;
	}
	return res;
}
signed main() {
	cin>>n;
	inv[1]=1;
	rep(i,2,N-1) inv[i]=(p-p/i)*inv[p%i]%p;
	rep(i,1,n-1) cin>>a[i];
	rep1(i,n-1,1) {
		f[i]=((s[i+1]-s[i+a[i]+1]%p+p)%p+a[i]+1)%p*qmi(a[i],p-2)%p;
		s[i]=(s[i+1]+f[i])%p;
	}
	cout<<f[1]<<endl;
	return false;
}
```

---

## 作者：Meickol (赞：0)

一道不错的前缀和优化的期望 DP 题（虽然自己二十五分钟就单出了）。

先来讲一下本题的 DP 状态表示：以 $f_i$ 表示当前在 $i$ 号格子，要跳到 $N$ 号格子期望的跳跃次数。

显然初始化有 $f_N=0$。

然后列出状态转移方程：
$$
\large f_{i}=(f_{i}+1)\times \dfrac{1}{a_i+1}+(f_{i+1}+1)\times \dfrac{1}{a_i+1}+\cdots +(f_{i+a_i}+1)\times \dfrac{1}{a_i+1}
$$
方程两边乘上 $\dfrac{1}{a_i+1}$ 得：
$$
\large (a_i+1)\times f_{i}=f_i+f_{i+1}+\cdots + f_{i+a_i}+a_i+1
$$
移项整理得：
$$
\large f_{i}=\dfrac{(\sum _{j=1}^{a_i}f_{i+j})+a_i+1}{a_i}
$$
于是 $f_i$ 的状态转移方程就表示出来了，但这样转移时间复杂度是 $\mathcal O(N^2)$ 的，显然会超时。

但是我们发现 $\large \sum _{j=1}^{a_i}f_{i+j}$ 这个计算式的下标是连续的，我们可以想到前缀和优化。因为枚举是倒序的，所以求前缀和其实就变求后缀和了。

然后本题就做完了。时间复杂度 $\mathcal O(N \log P)$。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
typedef long long LL;
const int N=2e5+5,MOD=998244353;
int n;
int a[N];
LL f[N];
LL fastpow(LL a,LL n,LL mod){
	LL res=1;
	while(n){
		if(n&1) res=res*a%mod;
		a=a*a%mod;
		n>>=1;
	}
	return res;
}
void solve(){
	cin>>n;
	rep(i,1,n-1) cin>>a[i];
	f[n]=0;
	per(i,n-1,1){
		f[i]=(f[i+1]-f[i+a[i]+1]+a[i]+1)*fastpow(a[i],MOD-2,MOD)%MOD;
		f[i]+=f[i+1];
		f[i]%=MOD;
	}
	cout<<(f[1]-f[2]+MOD)%MOD;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc263_e)

一道 dp 题。

直接顺推需要预处理从 $1$ 走到 $i$ 的概率，考虑倒推会比较简单。设 $dp_i$ 表示从 $i$ 出发走到 $n$ 掷骰子的期望次数。则有，

$$dp_i=\sum_{j=i}^{i+a_i}(dp_j+1)\times\dfrac{1}{a_i+1 }$$

因为 $dp_i$ 转移时用到了本身，所以进行化简：
$$dp_i=\dfrac{1}{a_i + 1}\times(\sum_{j=i}^{i+a_i}dp_j+a_i+1)$$
$$\dfrac{a_i}{a_i+1}\times dp_i=\dfrac{1}{a_i + 1}\times(\sum_{j=i+1}^{i+a_i}dp_j+a_i+1)$$
$$dp_i=\dfrac{\dfrac{1}{a_i + 1}\times(\sum_{j=i+1}^{i+a_i}\limits dp_j+a_i+1)}{\dfrac{a_i}{a_i+1}}$$
$$dp_i=(\dfrac{1}{a_i + 1}\times\sum_{j=i+1}^{i+a_i}\limits dp_j+1)\times \dfrac{a_i+1}{a_i}$$
$$dp_i=\dfrac{1}{a_i}\times \sum_{j=i+1}^{i+a_i}\limits dp_j + \dfrac{a_i+1}{a_i}$$

$\sum_{j=i+1}^{i+a_i}\limits dp_j$ 可以后缀和维护，最后 $dp_1$ 即是答案。

### Code

```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

const long long MOD1 = 998244353;
const long long MOD2 = 1000000007;
const long long MOD3 = 1000000009;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ {
    #define SP(n, x) std :: setprecision(n) << std :: fixed << x
    #define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
    #define fst first
    #define snd second
    template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
    template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
const int N = 200005, MOD = MOD1;
int n;
ll a[N], dp[N], sum[N];
/*
dp[i] 表示从 i 到 n 的期望掷骰子次数 
*/
ll qpow(ll n, ll m, ll p) {
	ll res = 1;
	while (m) {
		if (m & 1) res = res % p * n % p;
		n = n % p * n % p, m >>= 1;
	}
	return res;
}
ll invf(ll x, ll p) { return qpow(x, p - 2, p); }  
int main() {
    // freopen("InName.in", "r", stdin);
    // freopen("OutName.out", "w", stdout);
    ios :: sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i < n; i++) cin >> a[i];
	for (int i = n - 1; i >= 1; i--) {
		dp[i] = ((a[i] + 1) * invf(a[i], MOD) % MOD + (sum[i + 1] - sum[i + a[i] + 1]) * invf(a[i], MOD) % MOD) % MOD;
		sum[i] = (sum[i + 1] % MOD + dp[i] % MOD) % MOD;
	}
	cout << (dp[1] + MOD) % MOD;
    return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

数学+前缀和优化 DP。

由于从 $i$ 走到 $i\sim i+a_i$ 之间的点等概率，可以用 DP 计算期望，转移方程为：
$$dp_i=\dfrac{1}{a_i+1}\times\sum_{j=i}^{i+a_i}dp_j+1$$
有个问题，柿子两边都有 $dp_i$，怎么办？

考虑一个像解方程的做法，做以下转化：
$$dp_i=\dfrac{1}{a_i+1}\times\sum_{j=i+1}^{i+a_i}dp_j+\dfrac{1}{a_i+1}\times dp_i+1$$
移项得：
$$\dfrac{a_i}{a_i+1}\times dp_i=\dfrac{1}{a_i+1}\times\sum_{j=i+1}^{i+a_i}dp_j+1$$
两边同乘 $\dfrac{a_i+1}{a_i}$，得：
$$dp_i=\dfrac{a_i+1}{a_i}\times(\dfrac{1}{a_i+1}\times\sum_{j=i+1}^{i+a_i}dp_j+1)$$
其中 $\sum$ 可以用前缀和优化，逆元预处理，即可。

```cpp
//代码用阶乘求逆元，当然可以用线性递推或单次暴力计算
#include<bits/stdc++.h>
#define int long long
#define ri register int
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
const int p=998244353;
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
		#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
		#define gh() getchar()
	#endif
	inline int r(){
		int o=1,p=0;
		char q=gh();
		while(q<'0'||q>'9'){if(q=='-')o=-1;q=gh();}
		while(q>='0'&&q<='9'){p=(p<<1)+(p<<3)+(q^48);q=gh();}
		return o*p;
	}
	inline char gc(){char q=gh();while(q<=' ')q=gh();return q;}
	inline string gs(){string s="";char g=gh();while(g<=' ')g=gh();while(g>' '){s+=g;g=gh();}return s;}
	inline void Wi(int f){
		if(f==0)return;if(f<0){f=-f;putchar('-');}
		Wi(f/10);putchar((f%10)^48);
	}
	inline void wln(int J){if(J==0)putchar('0');else Wi(J);putchar('\n');}
	inline void w(int J){if(J==0)putchar('0');else Wi(J);}
	inline void ww(int J){if(J==0)putchar('0');else Wi(J);putchar(' ');}
}
using namespace IO;
namespace D1n0{
	int n,a[233333],j[233333],inv[233333],dp[233333];
	inline int Ksm(int x,int y){
		int a=1;
		while(y){
			if(y&1)a=a*x%p;
			x=x*x%p;y>>=1;
		}
		return a;
	}
	inline int inv_(int x){
		return inv[x]*j[x-1]%p;
	}
	inline void zyt(){
		n=r();
		j[0]=1;
		for(ri i=1;i<=n;++i)j[i]=j[i-1]*i%p;
		inv[n]=Ksm(j[n],p-2);
		for(ri j=n-1;j;--j)inv[j]=inv[j+1]*(j+1)%p;
		for(ri i=1;i<n;++i)a[i]=r();
		dp[n]=0;
		for(ri i=n-1;i;--i){
			dp[i]=inv_(a[i])%p*(a[i]+1)%p*(inv_(a[i]+1)*(dp[i+1]-dp[i+a[i]+1]+p)%p+1)%p;
			dp[i]=(dp[i]+dp[i+1])%p;
		}
		wln((dp[1]-dp[2]+p)%p);
	}
}
signed main(){
	D1n0::zyt();
}
```

---

## 作者：VitrelosTia (赞：0)

非常有启发性的 dp。

首先考虑顺推，但是似乎比较困难，因为转移的时候一个格子被某个格子跳到的概率还得维护，那你就考虑倒推，设 $f_i$ 为 $i$ 跳到 $n$ 的期望，这时因为你最后必须要跳到 $n$，所以就不需要考虑其他的东西了。

然后一个简单的转移是 

$$f_i = 1 + \sum^{i+a_i}_{j=i}\dfrac{f_j}{a_i+1}$$

但是这个转移要用到 $f_i$，考虑在转移中直接拿出来尝试搞掉它

$$f_i = 1 + \dfrac{f_i}{a_i+1} + \dfrac{1}{a_i + 1}\sum^{i+a_i}_{j=i+1}f_j$$

$$f_i(a_i + 1) = a_i + 1 + f_i + \sum^{i + a_i}_{j=i+1}f_j$$

$$a_if_i = a_i + 1 + \sum^{i + a_i}_{j=i+1}f_j$$

$$f_i = 1 + \dfrac{1 + \sum^{i + a_i}_{j=i+1}f_j}{a_i}$$

后缀和维护那个 sigma 即可，可以线性预处理逆元再优化一个 log。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5, mod = 998244353;
int n, a[N];

int qpow(int x, int y) {
	int a = 1;
	for (; y; y >>= 1, x = x * x % mod)
		if (y & 1) a = a * x % mod;
	return a;
}
int inv(int x) { return qpow(x, mod - 2); }
int f[N], s[N];

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i < n; i++) cin >> a[i];
	for (int i = n - 1; i >= 1; i--) {
		f[i] = (1 + (1 + s[i + 1] - s[i + a[i] + 1] + mod) % mod * inv(a[i]) % mod) % mod;
		s[i] = (s[i + 1] + f[i]) % mod;
	}
	cout << f[1];
	return 0;
}
```

---

## 作者：allenchoi (赞：0)

### 题意：  
一个人要从 $1$ 号格子走到 $n$ 号格子。 $1$ 号格子到 $n - 1$ 号格子上每格有一个整数 $a_i$ ，表示这个人走到 $i$ 号格子时，会随机在 $[0,a_i]$ 间选取一个整数（设为 $k$ ），移动到 $i + k$ 号格子上，保证不会跳出 $n$ 号格子。求期望移动次数。  
### 科技：  
逆元，期望 DP  
### 思路：  
设 $dp_i$ 表示从 $i$ 号格子到 $n$ 号格子的期望移动次数，初始化 $dp_n=0$ ，答案为 $dp_1$ 。  
考虑转移：  
从第 $i$ 格可能走到的格子号区间为 $[i,i+a_i]$ ，所以就得出 $dp_i=1+\sum_{j = i}^{i+a_i}dp_j\times\frac{1}{a_i+1}=1+\frac{1}{a_i+1}\times dp_i+\sum_{j = i+1}^{i+a_i}dp_j\times\frac{1}{a_i+1}$  
移项得：   
$\frac{a_i}{a_i+1}\times dp_i=1+\sum_{j = i+1}^{i+a_i}dp_j\times\frac{1}{a_i+1}$  
$dp_i=\frac{a_i+1+\sum_{j = i+1}^{i+a_i}dp_j}{a_i}$  
$\sum_{j = i+1}^{i+a_i}dp_j$ 用后缀和求，优化时间；除以 $a_i$ 直接乘逆元（快速幂求 $a_i^{mod-2}$ ）即可。 
### 代码：  
```cpp
#include <cstdio>
using namespace std;
const int mod = 998244353;
int n;
long long a[200010],h[200010],dp[200010];
long long qsm(long long x,long long y)
{
	long long ret = 1;
	while(y)
	{
		if(y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i < n;i++) scanf("%lld",&a[i]);
	for(int i = n - 1;i >= 1;i--)
	{
		dp[i] =  (h[i + 1] - h[i + a[i] + 1] + a[i] + 1 + mod) % mod * qsm(a[i],mod - 2) % mod;
		h[i] = (h[i + 1] + dp[i]) % mod;
	}
	printf("%lld\n",dp[1]);
	return 0;
}
```

---

## 作者：xz001 (赞：0)

首先我们可以 dp，我们倒着干，设立 $f_i$ 表示从 $i$ 到 $n$ 所需的期望步数，则转移为：
$$
f_i=1+\frac{1}{a_i+1}\sum_{j=i}^{i+a_i}f_j
$$
这个不太好求，有环，我们去除掉：
$$
f_i=1+\frac{1}{a_i+1}\sum_{j=i+1}^{i+a_i}f_j+\frac{1}{a_i+1}f_i
$$
$$
\frac{a_i}{a_i+1}f_i=1+\frac{1}{a_i+1}\sum_{j=i+1}^{i+a_i}f_j
$$
$$
f_i=\frac{a_i+1}{a_i}+\frac{1}{a_i}\sum_{j=i+1}^{i+a_i}f_j
$$
然后后缀和优化转移即可。

时间复杂度 $O(n\log n)$，多一个 $\log$ 是因为需要求逆元，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;

const int N = 1e6 + 5;

int ksm (int a, int n) {
	int ans = 1;
	while (n) {
		if (n & 1) ans = ans * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return ans;
}

int n, a[N], f[N], sum[N];

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n - 1; ++ i) scanf("%lld", a + i);
	for (int i = n - 1; i >= 1; -- i) {
		f[i] = ((a[i] + 1) * ksm (a[i], mod - 2) % mod + (((sum[i + 1] - sum[i + a[i] + 1]) % mod + mod) % mod) * ksm (a[i], mod - 2) % mod) % mod;
		sum[i] = (sum[i + 1] + f[i]) % mod;
	}
	printf("%lld\n", f[1]);
	return 0;
}
```

---

