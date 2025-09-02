# 「LCOI2022」 Cow Function

## 题目背景

Bessie 和大家正坐在刚刚合并完成的牛棚里，跟着 Farmer John 在一起学习循环展开。

Farmer John 说，如果一个循环展开的步长为 $8$，会对程序效率有很大的提升。

课后，Farmer John 布置了一道题，要求在 $1$ 秒内算出 $f(x)=\sum\limits_{i=1}^x3^{\omega(i)}$。Bessie 用 $20$ 分钟打了一个 $Θ(n\log_2 n\sqrt n)$ 代码，一交直接 TLE。于是，Bessie 来向你求助。

## 题目描述

她想要求出对于 $k\in\{0,1,\dots,7\}$，$f(n)=\sum_{i=1}\limits^n[\omega(i)\equiv k\pmod 8]3^{\omega(i)}$ 的值。

上面的算式中，$\omega(i)$ 表示 $i$ 含有几种质因子，例如 $\omega(12)=\omega(6)=2,\omega(114514)=3$。

## 说明/提示

【数据规模与约定】
|subtask|$n\le$|所占分值|时间限制|
|:-:|:-:|:-:|:-:|
|$1$|$100$|$10$|$500\texttt{ms}$|
|$2$|$2\times10^6$|$20$|$1000\texttt{ms}$|
|$3$|$3\times10^7$|$20$|$1000\texttt{ms}$|
|$4$|$10^9$|$20$|$4000\texttt{ms}$|
|$5$|$10^{10}$|$30$|$4000\texttt{ms}$|



如果你需要循环展开生成器，请前往附件下载。

## 样例 #1

### 输入

```
30```

### 输出

```
1
48
108
27
0
0
0
0```

## 样例 #2

### 输入

```
114514```

### 输出

```
1
32826
344727
1199826
1504818
538731
25515
0
```

# 题解

## 作者：peterwuyihong (赞：8)

抛砖引玉的一个题，其实是人菜，想不到别的解法

给一个[原题面](https://www.luogu.com.cn/problem/U185079)，我觉得我写的很好啊

题意：对于 $k=0,1,2,3,4,5,6,7$，求出：

$$\sum_{i=1}^n[\omega(i)\equiv k(\bmod 8)]3^{\omega(i)}$$

其中 $\omega(i)$ 表示 $i$ 含有**几种质因子**。

题解：

$n\le 100:$ 留给正宗 $O(n\sqrt n\log n)$ 做法。

$n\le 10^5:$ 留给 $O(n\log n)$ 筛法做法。

$n\le 3\times10^7:$ 留给 $O(n)$ 线性筛做法。

$n\le 10^9:$ 留给大常数和神秘做法。

$n\le 10^{10}:$ 看到取模，使用单位根反演，但是模数不一定是 $998244353$ 之类的模数，可以考虑选用一个巨大 $\text{NTT}$ 模数或者用三模 $\text{NTT}$ 原理，用 $\text{(ex)CRT}$ 大力合并。

先放一个单位根反演基本形式

$$[n|k]=\frac 1 n\sum_{i=0}^{n-1}\omega_n^{ik}$$

$$\sum_{i=1}^n[8|(\omega(i)-k)]3^{\omega(i)}=\frac1 8\sum_{i=1}^n3^{\omega(i)}\sum_{j=0}^7\omega_{8}^{j(\omega(i)-k)}$$

$$=\frac 1 8\sum_{j=0}^7\omega_8^{-jk}\sum_{i=1}^n3^{\omega(i)}\omega_8^{j\omega(i)}=\frac 1 8\sum_{j=0}^7\omega_8^{-jk}\sum_{i=1}^n{(3\omega_8^j)}^{\omega(i)}$$

最后一个柿子有 $8$ 个本质不同的底数，于是做 $8$ 次 $\text{Min-25}$ 筛，然后就做完了。

来点观看比赛心路历程

我：我草，这是什么牛逼做法啊

我：好像确实可以循环卷积模拟，麻了

我：大E了大E了咋整啊我草

我：分段打表是什么玩意儿？？？？

我：寄了，只求不成为下一个yz

希望 @Silver187 和 @Remake 可以贡献他们的解法

---

## 作者：Leasier (赞：4)

前置芝士：[Min_25 筛](https://oi-wiki.org/math/number-theory/min-25/)

考虑算贡献。对于 $g(m) > 0$，求出 $g(m) = \displaystyle\sum_{i = 0}^n [\omega(i) = m]$ 后可得 $ans_i = \displaystyle\sum_{i \equiv j \pmod 8} 3^j g(j)$。

考虑先执行 Min_25 筛第一部分求出 $\pi$ 的块筛，再执行类似于 Min_25 筛第二部分的限制质因数幂次的 dfs。

时间复杂度不会算（

具体细节见代码注释。

代码：
```cpp
#include <stdio.h>
#include <math.h>

typedef long long ll;

const int N = 1e5 + 7, M = 2e5 + 7, K = 8;
ll sqrt_n;
int max_prime_cnt[M], id1[N], id2[N];
ll prime[N], number[M], g[M], ans[K + 7];
bool p[N];

inline ll sqrt(ll n){
	ll ans = sqrt((double)n);
	while (ans * ans <= n) ans++;
	return ans - 1;
}

inline ll max(ll a, ll b){
	return a > b ? a : b;
}

inline int get_id(ll n, ll m){
	return n <= sqrt_n ? id1[n] : id2[m / n];
}

inline int init(ll n){
	int cnt = 0, sqrt_cnt, id = 0;
	ll limit;
	sqrt_n = sqrt(n);
	if (sqrt_n == 1) sqrt_cnt = 0;
	limit = max(sqrt_n, 3);
	p[0] = p[1] = true;
	for (register ll i = 2; i <= limit; i++){
		if (!p[i]) prime[++cnt] = i;
		if (i == sqrt_n) sqrt_cnt = cnt;
		for (register int j = 1; j <= cnt && i * prime[j] <= limit; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (register ll i = 1, j; i <= n; i = j + 1){
		ll tn = n / i;
		j = n / tn;
		id++;
		number[id] = tn;
		g[id] = tn - 1;
		if (tn <= sqrt_n){
			id1[tn] = id;
		} else {
			id2[j] = id;
		}
	}
	for (register int i = 1; i <= sqrt_cnt; i++){
		ll t = prime[i] * prime[i];
		for (register int j = 1; j <= id && number[j] >= t; j++){
			g[j] -= g[get_id(number[j] / prime[i], n)] - (i - 1);
		}
	}
	return cnt;
}

inline int get_max_prime_cnt(ll n, int cnt){
    int ans = 0;
    for (register ll i = 1; i <= n && ans <= cnt; i *= prime[ans]) ans++;
    return ans - 1;
}

inline ll quick_pow(ll x, ll p){
	ll ans = 1;
	while (p){
		if (p & 1) ans *= x;
		x *= x;
		p >>= 1;
	}
	return ans;
}

inline ll log(ll n, ll m){
	ll ans = log2(n) / log2(m);
	while (quick_pow(m, ans) <= n) ans++;
	return ans - 1;
}

ll solve(ll n, int m, int k, ll x, int cnt){
	if (m == 0) return 1;
	if (quick_pow(prime[k], m) > n) return 0; // 剪枝
	if (m == 1){
		ll ans = g[get_id(n, x)] - k;
		for (register int i = k + 1; i <= cnt && prime[i] * prime[i] <= n; i++){
			ans += log(n, prime[i]) - 1; // 质数的 > 1 次幂
		}
		return ans;
	}
	int md = m - 1;
	ll ans = 0;
	for (register int i = k + 1; i <= cnt && prime[i] * prime[i] <= n; i++){
		for (register ll j = prime[i]; j <= n; j *= prime[i]){
			ans += solve(n / j, md, i, x, cnt);
		}
	}
	return ans;
}

int main(){
	int cnt, m;
	ll n;
	scanf("%lld", &n);
	cnt = init(n);
	m = get_max_prime_cnt(n, cnt);
	for (register int i = 0, j = 0, k = 1; i <= m; i++, j = (j + 1) % K, k *= 3){
		ans[j] += k * solve(n, i, 0, n, cnt);
	}
	for (register int i = 0; i < K; i++){
		printf("%lld\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：little_cindy (赞：3)

## 思路
### $\mathbf{\mathsf{10}}$ 分

就是题目中 Bessie 最开始想到的 $\Theta(n\sqrt n\log_2 n)$ 做法。

### $\mathbf{\mathsf{30}}$ 分

$\Theta(n\log n)$ 筛法。

### $\mathbf{\mathsf{50}}$ 分

$\Theta(n)$ 线性筛法。

### $\mathbf{\mathsf{70}}$ 分

留给常数较大的做法。

### $\mathbf{\mathsf{100}}$ 分
看到取模，使用单位根反演，但是模数不一定是 $998244353$ 之类的模数，可以考虑选用一个巨大 $\text{NTT}$ 模数或者用三模 $\text{NTT}$ 原理，用 $\text{(ex)CRT}$ 大力合并。

先放一个单位根反演基本形式

$$[n|k]=\frac 1 n\sum_{i=0}^{n-1}\omega_n^{ik}$$

$$
\color{white}
\begin{cases}
\color{black}\ \ \ \ \sum_{i=1}^n[8|(\omega(i)-k)]3^{\omega(i)}\\
\color{black}=\frac1 8\sum_{i=1}^n3^{\omega(i)}\sum_{j=0}^7\omega_{8}^{j(\omega(i)-k)}\\
\color{black}=\frac 1 8\sum_{j=0}^7\omega_8^{-jk}\sum_{i=1}^n3^{\omega(i)}\omega_8^{j\omega(i)}\\
\color{black}=\frac 1 8\sum_{j=0}^7\omega_8^{-jk}\sum_{i=1}^n{(3\omega_8^j)}^{\omega(i)}
\end{cases}
$$

最后一个柿子有 $8$ 个本质不同的底数，于是做 $8$ 次 $\text{Min-25}$ 筛就做完了。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define all(x) x.begin(),x.end()
#define debug(x) cerr<<#x<<' '<<x<<endl
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define maxn 202100
#define int long long
const int p=1231453023109121;
template<class _Tp>void add(_Tp&x,const _Tp& y){((x+=y)>=p)&&(x-=p);}template<class _Tp>_Tp Add(_Tp x,const _Tp y){add(x,y);return x;}
template<class _Tp>void sub(_Tp&x,const _Tp&y){((x-=y)<0)&&(x+=p);}template<class _Tp>_Tp Sub(_Tp x,const _Tp y){sub(x,y);return x;}
template<class _Tp>void mul(_Tp&x,const _Tp&y){x=(__int128)x*y%p;}template<class _Tp>_Tp Mul(const _Tp x,const _Tp y){return (__int128)x*y%p;}
template<class _Tp>_Tp ksm(_Tp a,_Tp b){_Tp ans(1);for(;b;b>>=1,mul(a,a))if(b&1)mul(ans,a);return ans;} 
template<class _Tp>_Tp div2(_Tp a){if(a&1)a+=p;return a>>1;}
const int inv8=(p*7+1)/8;
int lim,N;
int pri[maxn],lpf[maxn],pcnt;
void shai(int n){
	for(int i=2;i<=n;i++){
		if(lpf[i]==0)pri[lpf[i]=++pcnt]=i;
		for(int j=1;j<=lpf[i]&&i*pri[j]<=n;j++)lpf[i*pri[j]]=j;
	}
}
#define id(x) ((x)<=lim?le[(x)]:ge[N/(x)])
int ge[maxn],le[maxn];
int G[maxn],Fprime[maxn][8];
int li[maxn],tot;
int W[8],w[8];
const int wn=ksm(3ll,(p-1)/8);
template <typename T> inline void read(T& x) {
	x=0;T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=x*f;
	return;
}
template <typename T,typename ...Arg>void read(T& x,Arg& ...arg){
	read(x);
	read(arg...);
}
template <typename T>inline void write(T x) {
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
template <typename T,typename ...Arg>void write(T& x,Arg& ...arg){
	write(x);
	putchar(' ');
	write(arg...);
}
void init(int n){
	for(int i=1,j;i<=n;i=n/j+1){
		j=n/i;
		li[++tot]=j;
		id(j)=tot;
		G[tot]=j-1;
	}
	w[0]=1;
	for(int i=1;i<8;i++)w[i]=Mul(w[i-1],wn);
	for(int i=0;i<8;i++)W[i]=Mul(w[i],3ll);
}
void calcFprime(){
	for(int k=1;k<=pcnt;k++)
	for(int i=1;li[i]>=pri[k]*pri[k];i++)
		sub(G[i],G[id(li[i]/pri[k])]-k+1);
	for(int j=0;j<8;j++)
	for(int i=1;i<=tot;i++)Fprime[i][j]=Mul(W[j],G[i]);
}
int K;
int F(int k,int x){
	if(x<pri[k]||x<=1)return 0;
	int d=id(x);
	int ans=Sub(Fprime[d][K],Mul(W[K],k-1));
	for(int i=k;i<=pcnt&&pri[i]*pri[i]<=x;i++){
		int pw=pri[i],pw2=pri[i]*pri[i];
		for(;pw2<=x;pw=pw2,pw2*=pri[i])add(ans,Mul(F(i+1,x/pw)+1,W[K]));
	}
	return ans;
}
int D[8],ans;
signed main(){
	read(N);
	lim=sqrt((long long)N);
	shai(lim+1000);
	init(N);
	calcFprime();
	for(K=0;K<8;K++)D[K]=(F(1,N)+1)%p;
	for(K=0;K<8;K++){
		ans=0;
		for(int j=0;j<8;j++)add(ans,Mul(w[(114512-j*K)%8],D[j]));
		write(Mul(ans,inv8));
		puts("");
	}
}
```      

---

## 作者：Corzica (赞：0)

因为要求余数一定，不难想到单位根反演。

$\sum_{i=1}^n 3^{w(i)}[w(i) \equiv k \pmod 8] = \sum_{i=1}^n 3^{w(i)}\sum_{j=0}^7 w_8^{(w(i)-k)j}/8$。

把最后的除以八拉出来，变成 $\sum_{j=0}^7w_8^{-kj}\sum_{i=1}^n 3^{w(i)} w_8^{w(i)j}$。

可以枚举前面的 $j$，对于相同的 $j$ 而言，即使 $k$ 不同也可以一并计算后面的部分。

令 $f(i)=3^{w(i)}w_8^{w(i)}$，发现 $f$ 是积性函数，可以使用 min25 筛求解。

代码先咕咕。

---

