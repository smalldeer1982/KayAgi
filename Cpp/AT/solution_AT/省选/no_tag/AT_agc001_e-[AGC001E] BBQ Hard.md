# [AGC001E] BBQ Hard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc001/tasks/agc001_e

高橋君はバーベキューをしようとしています。 バーベキューでは $ 2 $ 本の串にいくつかの具材を刺した*串焼き*を $ 1 $ 個作る予定です。

串焼きセットが $ N $ 個あり、$ i $ 番目のセットには串が $ 1 $ 本、肉が $ A_i $ 個、野菜が $ B_i $ 個入っています。

セットを $ 2 $ 個選び、セット $ 2 $ つに含まれる全ての具材を好きな順番で串 $ 2 $ 本に刺すことを考えます。 このとき、作ることの出来る串焼きは何通り考えられるでしょうか？ ただし、串どうしは区別でき、肉どうしや野菜どうしは区別できないものとします。 答えは非常に大きな数になる可能性があるので、$ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2≦N≦200,000 $
- $ 1≦A_i≦2000,\ 1≦B_i≦2000 $

### Sample Explanation 1

図のような $ 26 $ 通りの串焼きを作ることが出来ます。 灰色の棒は串を表しており、串に書かれた数はその串が含まれていたセットの番号を表しています。 また、茶色の長方形は肉、緑色の長方形は野菜を表しています。 !\[ebbq.png\](https://agc001.contest.atcoder.jp/img/agc/001/Gg9pvPKw/ebbq.png)

## 样例 #1

### 输入

```
3
1 1
1 1
2 1```

### 输出

```
26```

# 题解

## 作者：Konnyaku_LXZ (赞：51)

# 这是一篇能让像我一样蒻的蒟蒻看的懂题解

# 50分做法：

预处理阶乘及阶乘逆元，然后枚举每一个 $i,j$ ，O(1)计算出 $\binom{a_i+a_j+b_i+b_j}{a_i+a_j}$ ，将结果全部相加即可。

# 正解：

我们先考虑将50分的做法优化。

可是我们发现，50分的做法一定要枚举每一个 $i,j$ ，才能计算出组合数的值，复杂度一定是 $O(n^2)$ 的，无法优化，于是我们只能放弃这种做法，另辟蹊径。

我们来看题目的取值范围 $2≦N≦200,000,1≦A_i≦2000,1≦B_i≦2000$

我们发现，虽然 $N$ 很大，但是 $A_i,B_i$ 都很小，所以我们可以考虑在这上面下手。

观察题目所求的组合数的形式，我们可以联想到组合数的几何意义: **$\binom{x+y}{x}$ 其实就是从点 $(0,0)$ 到点 $(x,y)$ ，每次只能向上或者向右的不同的走法的方案数。**

有了这个性质之后，我们就可以进行一个dp。设 $f[i][j]$ 表示从点 $(0,0)$ 到点 $(i,j)$ 的路径条数，则显然有 $f[i][j]=f[i-1][j]+f[i][j-1]$ 。由于 $1≦A_i,B_i≦2000$ ，这个dp在时间复杂度上是吃得消的。

但是问题又来了：我们预处理好dp数组之后，对于每一个 $i,j$ 我们都需要统计一遍 $f[A_i+A_j][B_i+B_j]$ ，而这个统计依然是 $O(n^2)$ 的。同样，我们考虑优化。

我们希望可以 $O(n)$ 统计，即方案数只跟每一个 $i$ 相关。我们发现我们要到达的点与 $i,j$ 的取值都是有关的，所以我们希望能够 (~~控制单一变量~~) **控制它的取值只和其中的一个有关**，所以我们想把 $i$ 这一维给消掉。如何消掉呢？我们考虑**平移**。

将从 $(0,0)$ 到 $(A_i+A_j,B_i+B_j)$ 平移成从 $(-A_i,-B_i)$ 到 $(A_j,B_j)$ ，相当于坐标的左边同时减去 $A_i$ ，右边同时减去 $B_i$ ，这样所得的新的方案数与原来的是相同的。

为什么呢？我们分别以起点和终点的坐标为左下角，右上角的顶点，画出一个矩形，只要这个矩形的长和宽不变，那么从左下角的顶点到右上角的顶点的方案数一定是不变的。而我们的平移，只改变了矩形的位置，并没有改变矩形的长和宽，因此是可行的。

平移完之后就简单了。我们的起点只与 $i$ 有关，终点只与 $j$ 有关。所以我们一次性将**所有的** $f[-A_i][-B_i]$ 加一，这样我们的 $f[i][j]$ 就变成从点 $(i,j)$ 到**所有的** $(-A_i,-B_i)$ 的**路径条数之和**。最后的结果自然就是把每一个 $f[A_i][B_i]$ 加起来了。但是要注意，题目中要求 $i!=j$ ，所以我们要减去从 $(-A_i,-B_i)$ 到 $(A_i,B_i)$ 的路径条数。这个我们可以用组合数算，路径条数为 $\binom{2A_i+2B_i}{2A_i}$ 。全部减完之后，又因为题目要求 $i<j$ ，所以我们还要将最后的结果除以二。

时间复杂度： $O((max(A_i)+max(B_i))^2+N)$

Code:

	#include<iostream>
	#include<cstdio>
	#include<cmath>
	#include<algorithm>
	#include<cstring>
	#define rg register
	using namespace std;
	const int MAXN1=2e5+50,MAXN2=2100,MOD=1e9+7,S=2050;
	typedef long long LL;
	LL N,a[MAXN1],b[MAXN1],mul[MAXN2<<2],invv[MAXN2<<2],f[MAXN2<<1][MAXN2<<1],ans=0;
	inline LL qpow(LL a,LL b){//快速幂 
		LL res=1;
		while(b){
			if(b&1) res=(res*a)%MOD;
			b>>=1;
			a=(a*a)%MOD;
		}
		return res;
	}
	inline LL inv(LL x){return qpow(x,MOD-2)%MOD;}//求逆元 
	inline LL C(LL n,LL m){return mul[n]*invv[n-m]%MOD*invv[m]%MOD;}//求组合数 
	int main()
	{
		memset(f,0,sizeof(f));
		scanf("%lld",&N);
		for(rg LL i=1;i<=N;i++) scanf("%lld%lld",&a[i],&b[i]),f[S-a[i]][S-b[i]]++;//将所有的起点的dp值都加一 
		mul[0]=1,invv[0]=inv(mul[0]);//预处理阶乘及阶乘逆元 
		for(rg LL i=1;i<=8000;i++) mul[i]=mul[i-1]*i%MOD,invv[i]=inv(mul[i]);
		for(rg LL i=1;i<=S*2;i++)//dp 
			for(rg LL j=1;j<=S*2;j++)
				f[i][j]=(f[i][j]+(f[i-1][j]+f[i][j-1])%MOD)%MOD;
		for(rg LL i=1;i<=N;i++){
			ans=(ans+f[S+a[i]][S+b[i]])%MOD;//累加答案 
			ans=(ans-C(2*a[i]+2*b[i],2*a[i]))%MOD;//减去重复计算的 
			ans=(ans+MOD)%MOD;//防止ans为负数 
		}
		ans=(ans*500000004)%MOD;//除以二，也就是乘2的逆元 
		printf("%lld\n",ans);
		return 0;
	}

---

## 作者：LCuter (赞：30)

**组合意义没有精神！！我们代数解法才是你们的老大哥！！**

题目等价于求：
$$
\sum_{i=1}^{n}\sum_{j=1}^n\binom{t_i+t_j}{a_i+a_j}
$$
其中 $t_i=a_i+b_i$。

我们希望将 $i$ 与 $j$ 拆开，那么只需利用范德蒙德卷积：
$$
\begin{aligned}
	\sum_{i=1}^{n}\sum_{j=1}^n\sum_{k}\binom{t_i}{a_i-k}\binom{t_j}{a_j+k}
\end{aligned}
$$
显然可以交换求和次序，然后记
$$
F(k)=\sum_{i=1}^n\binom{t_i}{a_i+k}
$$
则原式化为：
$$
\sum_{k}F(k)F(-k)
$$


问题转为求解 $F(k)$。

直接计算是 $O(nk)$ 的，略去不提。

考察数列：
$$
T_i(k)=\binom{t_i}{a_i+k},k\in[-a_i,b_i]
$$
不妨将 $T_i(k)$ 看作二维平面的一个点 $(t_i,a_i+k)$，该点会给 $F(k)$ 贡献 $T_i(k)$，容易发现 $T_i$ 构成了垂直 $x$ 轴于 $(t_i,0)$ 且高为 $t_i$ 的线段。

观察 $x=x_0$ 上的线段，它们的高度是一致的，只是贡献区间平移了（这取决于 $a$ 的值）。

现在问题转化为，有一个初始全为 $0$ 的模板序列，$q$ 次修改，第 $i$ 次修改给出一个修改序列和一个区间 $[l_i,r_i]$，要求把修改序列合并到模板序列的对应区间上，最后求模板序列。

当然，修改序列还有个特点，它是：
$$
\binom{t_i}{0},\binom{t_i}{1},\cdots,\binom{t_i}{t_i}
$$
那么我们将这些东西看作是对 OGF 的修改，再次进行转化。

首先让原来的这个东西整体向右平移一定单位 $S$，现在下标一定是非负的。

对于一个修改序列，我们发现它的 OGF 就是 $(1+x)^{t_i}$。那么我们要让它平移整体平移量与自身平移量，也就是 $S-a_i$。
$$
\sum_{i=1}^nx^{S-a_i}(1+x)^{t_i}
$$
为了方便，我们将问题转为计算：
$$
A(x)=\sum_{i=1}^{n}x^{p_i}(1+x)^{q_i}
$$
或者说是计算：
$$
\begin{aligned}
A(x)=\sum_{i=1}^m(1+x)^iQ_i(x)
\end{aligned}
$$
使用秦九韶算法即可 $O(n+m^2)$ 解决，值得一提的是，我乱实现的屑代码目前领先其它所有洛谷提交。



---

## 作者：Ebola (赞：20)

题目要求的东西非常明显吧。就是$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\binom{A_i+A_j+B_i+B_j}{A_i+A_j}$

考虑一下这玩意儿的组合意义。我们知道$\binom{x+y}{x}$可以表示坐标轴上从$(0,0)$走到$(x,y)$，每次只能向右或向上的路径条数。发现我们要求的式子恰好就是这种形式。问题变成了求坐标轴上从$(0,0)$走到$(A_i+A_j,\;B_i+B_j)$的路径条数

我们平移一下，求$(-A_i,\;-B_i)$到$(A_j\;B_j)$的路径条数。我们现在换一个思维，将所有的$(-A_i,\;-B_i)$作为起点，然后求出所有点$(x,y)$有多少条能到达它的路径

考虑dp。初始时枚举所有的$i$，然后让$dp[-A_i][-B_i]$加一。然后转移$dp[x][y]=dp[x-1][y]+dp[x][y-1]$

那么将所有的$dp[A_i][B_i]$加起来就是答案了。但是我们的dp实际上求了$(-A_i,-B_i)$到$(A_i,B_i)$的路径条数，我们要减去这部分贡献。这部分贡献是$\binom{2A_i+2B_i}{2A_i}$，直接减去即可

```cpp
#include<bits/stdc++.h>
#define ha 1000000007
#define inv2 500000004
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=200010;
const int M=8000;
int fac[M+10],ifac[M+10];
int f[M/2+10][M/2+10],base=M/4+2;
int n,A[N],B[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void Init()
{
    fac[0]=1;
    for(int i=1;i<=M;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[M]=Pow(fac[M],ha-2);
    for(int i=M-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

int C(int n,int m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int main()
{
    Init(); n=read();
    for(int i=1;i<=n;i++)
    {
        A[i]=read(),B[i]=read();
        f[base-A[i]][base-B[i]]++;
    }
    for(int i=1;i<=M/2+2;i++)
        for(int j=1;j<=M/2+2;j++)
            f[i][j]=(f[i][j]+(f[i-1][j]+f[i][j-1])%ha)%ha;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=(ans+f[A[i]+base][B[i]+base])%ha;
        ans=(ans-C(2*A[i]+2*B[i],2*A[i]))%ha;
    }
    ans=(ans+ha)%ha;
    ans=1ll*inv2*ans%ha;
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：Fido_Puppy (赞：10)

$$\texttt{Description}$$

[AT1983 [AGC001E] BBQ Hard](https://www.luogu.com.cn/problem/AT1983)

$$\texttt{Solution}$$

首先我们能够发现题目中的式子是对称的，所以我们可以把它转换成如下的式子：

$$\sum^{n}_{i=1}\sum^{n}_{j=1} {a_i + b_i + a_j + b_j \choose a_i + a_j} - \sum_{i=1}^{n}{2a_i + 2b_i \choose 2a_i}$$

后面的式子明显是可以 $\mathcal{O(n\ log\ n)}$ 求出来的（算上求逆元的时间复杂度）。

我们目前要解决的就是前面的式子。

我们考虑一个组合数 ${m + n \choose n}$ 的几何意义。

不难发现，这就是在坐标轴上每次只能向上或向右走一个单位，从 $(0,0)$ 走到 $(m,n)$ 的方案数。

**证明：**

向上走的步数必定等于 $m$，向右走的步数必定等于 $n$，所以把向右走的步数是哪几步确定即可。

问题转换为从一共 $n + m$ 步中可以选择 $n$ 步的方案数。

答案即为：

$${n + m \choose n}$$

所以问题就变成了在坐标轴上从 $(0, 0)$ 走到 $(a_i + a_j, b_i + b_j)$ 的方案数。

我们转换一下，就只需要求从 $(-a_i, -b_i)$ 走到 $(a_j, b_j)$ 的方案数。

于是我们就可以在坐标轴上把这一个点都给表示出来，并且由于 $a_i,b_i \le 2000$，所以我们可以用动态规划直接求出方案数。

设 $dp_{i,j}$ 表示走到 $(i, j)$ 的方案数。

初始化就把所有点 $(-a_i, -b_i)$ 的 DP 值加上 1。

```cpp
for (int i = 1; i <= n; i++)
	dp[ 2000 - a[i] ][ 2000 - b[i] ]++;

dp[i][j] = dp[ i - 1 ][j] + dp[i][ j - 1 ]; // 状态转移方程
```

$$\texttt{Notice}$$

由于 $(-a_i, -b_i)$ 会出现负数，所以表示坐标时要加上 2000。

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
const int mod = 1e9 + 7;

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' ' && __c != '\n' && __c != '\r'; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

int n;
vector <int> a(1e6 + 10), b(1e6 + 10);
vector < vector <int> > dp(5001, vector <int> (5001));
vector <int> fac(8001);

static inline
int qpow(int x, int p) {
	int ans = 1;
	while (p) {
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

int C(int m, int n) {
	return fac[m] * qpow(fac[n], mod - 2) % mod * qpow(fac[ m - n ], mod - 2) % mod;
}

signed main() {
	gi(n);
	fac[0] = 1;
	for (int i = 1; i <= 8000; i++) fac[i] = fac[ i - 1 ] * i % mod;
	for (int i = 1; i <= n; i++) gi(a[i]), gi(b[i]);
	for (int i = 1; i <= n; i++) {
		dp[ 2000 - a[i] ][ 2000 - b[i] ]++;
	}
	for (int i = 0; i <= 4000; i++)
		for (int j = 0; j <= 4000; j++) {	
			if (i) (dp[i][j] += dp[ i - 1 ][j]) %= mod;
			if (j) (dp[i][j] += dp[i][ j - 1 ]) %= mod;
		}
	int ans = 0;
	for (int i = 1; i <= n; i++) (ans += dp[ a[i] + 2000 ][ b[i] + 2000 ]) %= mod;
	for (int i = 1; i <= n; i++) ans = (ans - C(2 * a[i] + 2 * b[i], 2 * a[i]) + mod) % mod;
	print(ans * qpow(2, mod - 2) % mod);
	return 0;
}
```


$$\texttt{Thanks for watching!}$$

---

## 作者：ImmortalWatcher (赞：8)

大佬口中所说的经典题。

组合意义天地灭，代数推导保平安。

考虑先将题目柿子的限制弄小一点。

$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^n \binom{a_i+b_i+a_j+b_j}{a_i+a_j}$$

然后大力推导。

$$
\begin{aligned}
& \sum\limits_{i=1}^{n}\sum\limits_{j=1}^n \binom{a_i+b_i+a_j+b_j}{a_i+a_j}\\
=& [x^{a_i+a_j}]\sum\limits_{i=1}^{n}\sum\limits_{j=1}^n (1+x)^{t_i+t_j} & t_i=a_i+b_i\\
=& [x^0]\sum\limits_{i=1}^{n}\sum\limits_{j=1}^n x^{-a_i-a_j}(1+x)^{t_i+t_j}\\
=&[x^0]\left( \sum\limits_{i=1}^{n}x^{-a_i}(1+x)^{t_i}\right)^2\\
=&[x^0]\left( \sum\limits_{i=1}^{m}Q_i(1+x)^i\right)^2 & Q_k=\sum\limits_{t_i=k}x^{-a_i}\\
\end{aligned}
$$

发现最后一个柿子可以用秦九韶算法快速计算，卷积暴力卷即可。

然后回到原题，修一修边界即可。

时间复杂度 $O(n+m^2)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=8000,c=4000;
const int mo=1e9+7;
int n,a[200010],b[200010],fac[8010],inv[8010],ans,Ans[8010],mx;
vector<int> Q[8010];
inline int ksm(int x,int y)
{
	int ret=1;
	for (;y;y>>=1)
	{
		if (y&1) ret=1ll*ret*x%mo;
		x=1ll*x*x%mo;
	}
	return ret;
}
inline int C(int x,int y){return 1ll*fac[x]*inv[y]%mo*inv[x-y]%mo;}
void mul()
{
	for (int i=N;i>=1;i--)
		Ans[i]=(Ans[i]+Ans[i-1])%mo;
}
int main()
{
	fac[0]=1;inv[0]=1;
	for (int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mo;
	inv[N]=ksm(fac[N],mo-2);
	for (int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mo;
	scanf("%lld",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		Q[a[i]+b[i]].push_back(-a[i]+c);
		mx=max(mx,a[i]+b[i]);
	}
	for (int i=c;i;i--)
	{
		for(auto v:Q[i])
			Ans[v]=(Ans[v]+1)%mo;
		mul();
	}
	for (int i=-c;i<=c;i++) 
		ans=(ans+1ll*Ans[c-i]*Ans[c+i]%mo)%mo;
	for (int i=1;i<=n;i++)
		ans=(ans-C(2*a[i]+2*b[i],2*a[i])%mo+mo)%mo;
	ans=1ll*ans*inv[2]%mo;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：K8He (赞：6)

# 「题解报告」[[AGC001E] BBQ Hard](https://www.luogu.com.cn/problem/AT_agc001_e)

一个比较经典的东西是 $\dbinom{x + y}{x}$ 可表示从 $(0, 0)$ 出发只能向右或向上走走到 $(x, y)$ 的方案数。

那么 $\dbinom{a_i + b_i + a_j + b_j}{a_i + a_j}$ 的组合意义就是从 $(-a_i, -b_i)$ 出发只能向右或向上走走到 $(a_j, b_j)$ 的方案数。

那么设 $f_{x, y}$ 表示共有多少种方案可以走到 $(x, y)$，初始所有 $f_{-a_i, -b_i}$ 为 $1$。转移方程：$f_{i, j} = f_{i, j} + f_{i - 1, j} + f_{i, j - 1}$。

注意到会把从 $(-a_i, -b_i)$ 走到 $(a_i, b_i)$ 给算上，这一部分是多余的。同时还要求 $i < j$，因此答案要除二。那么最后统计答案为 $\dfrac{1}{2}\sum_{i = 1}^{n}(f_{a_i, b_i} - \dbinom{2a_i + 2b_i}{2a_i})$。

Code:

```cpp
const ll N = 2e5 + 10, M = 4e3 + 10, P = 1e9 + 7;
namespace SOLVE {
	ll n, a[N], b[N], f[M][M], ans;
	ll fac[M << 1], inv[M << 1];
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
	inline ll C (ll x, ll y) { return fac[x] * inv[y] % P * inv[x - y] % P;}
	inline void Pre () {
		fac[0] = 1;
		_for (i, 1, 8000) fac[i] = fac[i - 1] * i % P;
		inv[8000] = FastPow (fac[8000], P - 2);
		for_ (i, 7999, 0) inv[i] = inv[i + 1] * (i + 1) % P;
		return;
	}
	inline void In () {
		n = rnt ();
		_for (i, 1, n) a[i] = rnt (), b[i] = rnt ();
		return;
	}
	inline void Solve () {
		Pre ();
		_for (i, 1, n) ++f[2001 - a[i]][2001 - b[i]];
		_for (i, 1, 4001) _for (j, 1, 4001) f[i][j] = (f[i][j] + f[i - 1][j] + f[i][j - 1]) % P;
		_for (i, 1, n) {
			ll qwq = f[a[i] + 2001][b[i] + 2001];
			ll awa = C (2 * (a[i] + b[i]), 2 * a[i]);
			ans = (ans + qwq - awa + P) % P;
		}
		return;
	}
	inline void Out () {
		printf ("%lld\n", ans * FastPow (2, P - 2) % P);
		return;
	}
}
```


---

## 作者：CYJian (赞：4)

## AGC001E

首先观察题目中要求的式子：

$$ \sum_{i=1}^{n} \sum_{j=i+1}^{n} \binom{a_i + b_i + a_j + b_j}{a_i + a_j} $$

可以变成：对于每一个 $(-a_i,-b_i)$，算出所有的 $(a_j,b_j)$ 到它的方案数。然后减去 $(-a_i,-b_i)$ 到 $(a_i,b_i)$ 的方案数再除 $2$ 就是答案。

然后发现，这个东西就是一个简单 $dp$ ：设 $f_{i,j}$ 表示从所有的第三象限的点走到 $(i, j)$ 的方案数之和。

容易发现，可以有这样的一个转移： $f_{i,j} =f_{i-1,j} + f_{i,j-1} + cnt_{i,j}$，其中 $cnt_{x,y}$ 表示有多少个数对 $(a_i,b_i)$ 满足 $-a_i=x,-b_i=y$ 。

然后直接拿着做就是 $O((Val_a+Val_b)^2)$ 的。可以通过。

代码简单，就不贴了。

upd：已修正 LaTeX 格式问题。

---

## 作者：小木虫 (赞：2)

### Preface  
思维好题。  
### Problem  
有 $n$ 个数对 $(A_i,B_i)$，求出
$$\sum_{i=1}^{n}\sum_{j=i + 1}^{n}{a_i+b_i+a_j+b_j \choose a_i+a_j}$$
答案对 $10^9+7$ 取模。  
### Solution  

首先我们根据组合意义可知 $C_{x+y}^{x}$ 为在网格图中只能往上和右走从 $(0,0)$ 走到 $(x,y)$ 的方案数。因为这相当于在长度为 $x+y$ 的路径中选出 $x$ 个往上的边。这样我们就把一个组合数转化为了一个矩形。  

已知值域很小，可以满足暴力 dp。  
很显然我们可以通过 dp 来解决网格问题，但是统计仍是 $O(n^2)$ 的。  
我们的目标是匹配 $n^2$ 个矩形，我们发现出发点仅有 1 个，但是结束点却是 $n^2$ 个，这很明显是不平衡的，要配上 $n^2$ 个对很明显最优的方案为开始 $n$ 个结束 $n$ 个。  

于是我们开始思考如何将出发点增大的同时使结束点减少。  
现在对于每一个矩形为 $(0,0)\sim (a_i+a_j,b_i+b_j)$。  

因为我们无法接受 $i$ 与 $j$ 在同一侧所造成的巨大复杂度，我们将 $i$ 移向开始点（矩形长宽不变），变为：  
$$(-a_i-b_i)\sim (a_j+b_j)$$  

现在我们成功通过加上一个 2 的常数，平衡了开始结束点。  
我们对于每个 $i$，将 $(-a_i-b_i)$ 的 dp 值加上 1。  
然后再在每个 $i$ 的 $(a_i+b_i)$ 处进行累加统计。

最后，因为 $i$ 不能等于 $j$，我们发现会有 $(-a_i-b_i)\sim (a_i+b_i)$ 的无效计算，再进行一次的 dp 将多余的答案减掉即可。具体来说，我们可以将每一个这样的矩形转换为 $(0,0)\sim (2a_i,2b_i)$，然后就可以一次 dp 解决了。

$i<j$，所以答案除二。  
code：  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4010;
const int mod=1e9+7;
const int inv=(mod+1)/2;
int n;int a[N*50],b[N*50];
int dp[N][N];int ans;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++){
		dp[2000-a[i]][2000-b[i]]++;
	}
	for(int i=0;i<=4000;i++){
		for(int j=0;j<=4000;j++){
			if(i!=0)dp[i][j]+=dp[i-1][j],dp[i][j]%=mod;
			if(j!=0)dp[i][j]+=dp[i][j-1],dp[i][j]%=mod;
		}
	}
	for(int i=1;i<=n;i++){
		ans+=dp[2000+a[i]][2000+b[i]];
		ans%=mod;
	}
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(int i=0;i<=4000;i++){
		for(int j=0;j<=4000;j++){
			if(i!=0)dp[i][j]+=dp[i-1][j],dp[i][j]%=mod;
			if(j!=0)dp[i][j]+=dp[i][j-1],dp[i][j]%=mod;
		}
	}
	for(int i=1;i<=n;i++){
		ans-=dp[2*a[i]][2*b[i]];
		ans+=mod;ans%=mod;
	}
	ans*=inv;ans%=mod;
	cout<<ans;
}
```


---

## 作者：Limit (赞：2)

~~呦，来一次久违的BBQ吧！~~

AT题...日本的题库质量一向很高

这题是有关组合数的DP...

想必大家都知道杨辉三角与组合数是意义对应的
具体可以点[这里](https://wenku.baidu.com/view/4f933e626ad97f192279168884868762cbaebb45.html)

对于题面中的问题
$\sum_{i=1}^{n}\sum_{j=i + 1}^{n}{a_i+b_i+a_j+b_j \choose a_i+a_j}$
提出${a_i+b_i+a_j+b_j \choose a_i+a_j}$这部分
可以理解为原点到$(a_i+b_i,a_j+b_j)$的路径的个数...
但是这样貌似要O(N^2)枚举...显然T,所以我们还要继续优化这个式子

...

将原点平移可以理解为$(a_i,a_j)$到$(b_i,b_j)$的路径个数
是不是觉得很好处理了...
但是$\sum_{i=1}^{n}\sum_{j=i + 1}^{n}$之一部分中并没有自己到自己的条数,所以需要减去
这里如果使用杨辉三角预处理要O(4000^2*2)感觉十分的不保险,所以就要使用到快速计算组合数,组合数的计算中需要用到除法,可以点[这里](https://blog.csdn.net/qq_34531807/article/details/79795261)
最后上代码

```cpp
#include<bits/stdc++.h>
#define rap(i,first,last) for(int i=first;i<=last;++i)
using namespace std;
const int maxN=2005;
const int mod=1e9+7;
const int inv2=500000004;//预处理2的逆元
long long fac[maxN*4+100],inv[maxN*4+100];
long long dp[maxN*2+100][maxN*2+100],N;
int A[1000005],B[1000005];
long long C(int n,int m)//计算组合数
{
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main()
{
	//预处理组合数
	fac[0]=inv[0]=inv[1]=1;
	rap(i,1,maxN*4)fac[i]=1ll*fac[i-1]*i%mod;
	rap(i,2,maxN*4)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	rap(i,1,maxN*4)inv[i]=1ll*inv[i-1]*inv[i]%mod;
	scanf("%d",&N);
	rap(i,1,N)
	{
		scanf("%d%d",&A[i],&B[i]);
		dp[maxN-A[i]][maxN-B[i]]++;//在-A[i],-B[i]位置加一
	}
	rap(i,-maxN+1,maxN)
	rap(j,-maxN+1,maxN)
	{
		dp[maxN+i][maxN+j]+=dp[maxN+i-1][maxN+j]+dp[maxN+i][maxN+j-1];//类似杨慧三角的DP
		dp[maxN+i][maxN+j]%=mod;
	}
	long long answer=0;
	rap(i,1,N)
	{
		answer+=dp[maxN+A[i]][maxN+B[i]];//对答案加上这个位置的方案数
		answer%=mod;
		answer-=C(A[i]*2+B[i]*2,A[i]*2);//减去自己到自己的方案数
		answer=(answer+mod)%mod;
	}
	answer*=inv2;//可以发现多计算了一遍,需要除二,在膜域中也就是乘上2的逆元
	answer%=mod;
	printf("%lld\n",answer);//输出answer
	return ~0;
}
```
看似一道简单的DP,其中涉及了各种方面的知识点只有对膜域和组合数掌握的很好才能在做这类题时得心应手.


---

## 作者：ListenSnow (赞：1)

## 题意

有 $n$ 个数对 $(a_i,b_i)$，求：

$\sum_{i=1}^{n} \sum_{j=i+1}^n \begin{pmatrix}  
  a_i+b_i+b_j+a_j\\  
  a_i+a_j  
\end{pmatrix}  $。

#### 数据范围

$2 \leq N \leq 200000$。

$1\leq a_i,b_i \leq 2000$。

### 思路

预处理出阶层，直接枚举的时间复杂度为 $O(n^2)$。显然需要更优的做法。

可以考虑题目要求的式子的几何意义，$\begin{pmatrix}  
  a_i+b_i+b_j+a_j\\  
  a_i+a_j  
\end{pmatrix}  $ 可以看成是从直角坐标系的原点 $(0,0)$，只向上或向右走，走到 $(a_i+a_j,b_i+b_j)$ 的方案数（因为只向上或向右走，需要走 $a_i+a_j+b_i+b_j$ 步，而其中 $a_i+a_j$ 步是要向右走的，枚举哪几步向右走就是这个公式）。

但是这样还是无法做到更优的复杂度。可以考虑进一步转化为从 $(-a_i,-b_i)$ 走到 $(a_j,b_j)$ 的方案数，含义不变。对于每一个终点 $(a_i,b_i)$，都可以从所有的 $(-a_j,-b_j)$ 走过来，可以直接 $O(\max (a_i+a_j)^2)$ dp 算出所有的答案（具体实现可以看代码）。这样计算会多算 $i \geq j$ 的方案，于是可以先减去从 $(-a_i,-b_i)$ 走到 $(a_i,b_i)$ 的方案数，最终再把答案除以 $2$ （乘以 $2$ 的逆元）。

最终的时间复杂度就是 $O(n+4000^2)$。

### code：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int mod=1e9+7;
const int N=4040,NLC=2020,M=2e5+10;
int f[N][N],ans,n,inv[N<<1],fac[N<<1],infac[N<<1],a[M],b[M];
void init()
{
	fac[0]=fac[1]=inv[0]=inv[1]=infac[0]=infac[1]=1;
	for(int i=2;i<N<<1;i++)
	{
		fac[i]=1ll*fac[i-1]*i%mod;
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		infac[i]=1ll*infac[i-1]*inv[i]%mod;
	}
}
int C(int n,int m){return 1ll*fac[n]*infac[m]%mod*infac[n-m]%mod;}
int main()
{
	init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]),f[NLC-a[i]][NLC-b[i]]++;//直接储存负数会 RE，需要整体加上一个偏移量
	for(int i=1;i<N;i++)
	    for(int j=1;j<N;j++)
	        f[i][j]=(f[i][j]+f[i][j-1]+f[i-1][j])%mod;
	for(int i=1;i<=n;i++)
	{
		ans=(ans+f[NLC+a[i]][NLC+b[i]])%mod;
		ans=((ans-C(2*a[i]+2*b[i],2*a[i]))%mod+mod)%mod;
	}
	printf("%d\n",1ll*ans*inv[2]%mod);
	return 0;
}
```


---

## 作者：pomelo_nene (赞：1)

定义 $F(i,j)$ 为 $\dbinom{a_i+b_i+a_j+b_j}{a_i+a_j}$，改一改问题：

$$
\sum_{i=1}^n \sum_{j=1}^n F(i,j)
$$

这个式子稍微变变就是问题答案，咱先不讨论

考虑 $F(i,j)$ 的组合意义，实际上我们可以将其看成从 $(0,0)$ 这个点，通过向右/向上两种移动到达点 $(a_i+a_j,b_i+b_j)$ 的方案数。

考虑对于每一个 $i$，快速求出 $\displaystyle \sum_{j=1}^n F(i,j)$。想要快速计算它，我们就要用一个好方法将起点移到一块儿去。

发现 $a_i,b_i$ 是不变的，并且当我们的起点和终点的纵与横坐标差不变，方案数也是不变的，于是将起点挪动到 $(-a_i,-b_i)$，计算要走到每一个 $(a_j,b_j)$ 的方案数。

显然我们可以放在一起 dp。知道这个之后，不难想到我们可以直接将每一个 $i$ 会造成的贡献可以直接扔到整个坐标系 dp。时间复杂度 $O(m^2)$，其中 $m$ 为值域。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int LL;
const LL MOD=1e9+7,COR=2000;
long long fac[8005],inv[8005];
long long C(int a,int b){return fac[a]*inv[b]%MOD*inv[a-b]%MOD;}
LL n,dp[4005][4005],a[200005],b[200005];
long long QuickPow(int x,int p)
{
	long long ans=1,base=x;
	while(p)
	{
		if(p&1)	ans*=base,ans%=MOD;
		base*=base;
		base%=MOD;
		p>>=1;
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(LL i=1;i<=n;++i)
	{
		scanf("%d %d",&a[i],&b[i]);
		++dp[COR-a[i]][COR-b[i]];
	}
	for(LL i=0;i<=4000;++i)
	{
		for(LL j=0;j<=4000;++j)
		{
			if(i==0 && j==0)	continue;
			else if(i==0)	dp[i][j]+=dp[i][j-1];
			else if(j==0)	dp[i][j]+=dp[i-1][j];
			else	dp[i][j]+=dp[i][j-1]+dp[i-1][j];
			if(dp[i][j]>=MOD)	dp[i][j]-=MOD;
		}
	}
	fac[0]=1;
	for(int i=1;i<=8000;++i)	fac[i]=fac[i-1]*i%MOD;
	inv[8000]=QuickPow(fac[8000],MOD-2);
	for(int i=7999;~i;--i)	inv[i]=inv[i+1]*(i+1)%MOD;
	long long ans=0;
	for(LL i=1;i<=n;++i)	ans+=dp[COR+a[i]][COR+b[i]],ans=(ans>=MOD?ans-MOD:ans);
	for(LL i=1;i<=n;++i)	ans-=C(a[i]+b[i]+a[i]+b[i],a[i]+a[i]),ans=(ans<0?ans+MOD:ans);
	printf("%lld",(long long)ans*(MOD/2+1)%MOD);
	return 0;
}
```

---

## 作者：Leasier (赞：0)

- **组合数转路径计数的套路。**

这里 $a_i, b_i$ 没啥特殊性质，直接代数冲看上去不是很方便，考虑其几何意义：从 $(0, 0)$ 到 $(a_i + a_j, b_i + b_j)$ 的路径计数。

**我们希望 $i, j$ 相对独立。**

考虑平移坐标系，将上述路径变为从 $(-a_i, -b_i)$ 到 $(a_j, b_j)$。

此时考虑 dp。设 $dp_{i, j}$ 表示从某个 $(-a_k, -b_k)$ 到 $(i, j)$ 的方案数，则 $\displaystyle\sum_{i = 1}^n \sum_{j = 1}^n C_{a_i + a_j + b_i + b_j}^{a_i + a_j} = \displaystyle\sum_{i = 1}^n dp_{a_i, b_i}$。

去掉 $i = j$ 的贡献后除以 $2$ 即为答案。时间复杂度为 $O(n + N^2)$，其中 $N$ 为坐标系值域 $2 \times 10^3$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 2e5 + 7, M = 4e3, K = 8e3, P = 2e3, mod = 1e9 + 7, inv2 = 500000004;
int a[N], b[N], dp[M + 7][M + 7];
ll fac[K + 7], inv_fac[K + 7];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(){
	fac[0] = 1;
	for (int i = 1; i <= K; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[K] = quick_pow(fac[K], mod - 2, mod);
	for (int i = K - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline ll comb(int n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	return fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

int main(){
	int n;
	ll ans = 0;
	scanf("%d", &n);
	init();
	for (int i = 1; i <= n; i++){
		scanf("%d %d", &a[i], &b[i]);
		dp[-a[i] + P][-b[i] + P]++;
	}
	for (int i = 0; i <= M; i++){
		for (int j = 0; j <= M; j++){
			if (i > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
			if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
		}
	}
	for (int i = 1; i <= n; i++){
		ans = ((ans + dp[a[i] + P][b[i] + P] - comb((a[i] + b[i]) * 2, a[i] * 2)) % mod + mod) % mod;
	}
	printf("%lld", ans * inv2 % mod);
	return 0;
}
```

---

## 作者：eastcloud (赞：0)

题目让我们求一个二项式系数之和，暴力时间复杂度为 $O(N^2)$，我们考虑能不能把 $i$，$j$ 两部分拆开分别计算后再进行合并。

考虑组合意义，从一堆里面选出若干个可以等价于将堆分成两堆，这两堆选出的物品个数之和为要求的个数的方案数，我们枚举其中一堆选出的物品个数，原式可以化为 $ \sum_{i}^{n} \sum_{j}^{n} \sum_{k} \binom{a_i+b_i}{a_i-k} \binom{a_j+b_j}{a_j+k} $，把求和次序交换，外层枚举 $k$ 内层相当于两个多项式相乘，但是这里预处理的时间复杂度不会超标，直接计算可以做到 $O(nk)$。

还有没有其他做法呢？这看起来就很像个卷积，但是单项计算复杂度就是 $O(n)$ 的，我们只好换个思路，考察二项式系数原本的定义，转化柿子为 $[x^{a_i+a_j}] \sum_{i}^{n} \sum_{j}^{n} (x+1)^{a_i+a_j+b_i+b_j}$，这下可以卷了，除掉 $x$ 后将两边分开可以变成 $[x^0]\left(\sum^{2n}_{k}Q_k\left(1+x\right)^k\right)^2$，其中 $Q_i$ 为所有 $a_i+b_i$ 为 $k$ 的 $x^{-a_i}$ 之和。

由于一个数列每次乘 $(1+x)$ 都是加一遍自己和自己移位之后的数列，我们这里只记录每一项的系数，预处理 $Q_k\left(1+x\right)^k$，倒序循环枚举 $i$ 从 $k$ 到 0，把对应 $-a_i$ 位置加 1 后整体乘上 $(1+x)$，即每个位置向后移一位后加一遍原本的序列即可，这也等价于自己前面每个数加一遍自己前面的系数，这个倒序枚举每次乘 $x$（此处为 $(1+x)$） 的做法也叫作秦九韶算法。最后别忘记去重，我们不能使 $i=j$。

还有没有其他做法呢？考虑原式的组合意义，即从 $(0,0)$ 走到 $(a_i+b_i,a_j+b_j)$ 的方案数，考虑分离两部分，我们平移坐标轴，把起点设为 $(-a_i-a_j)$，之后考虑多个起点的 dp 进行统计即可，这种方法也不要忘记去重。

---

## 作者：Leap_Frog (赞：0)

### P.S.
高质量好题，太高妙了。![](//xn--9zr.tk/qiang)  
~~早上%你赛时一直在想，还是没想出来~~![](//xn--9zr.tk/wq)  

### Description.
给定 $\{a_i\}$ 和 $\{b_i\}$，求
$$\sum_{i=1}^n\sum_{j=i+1}^n\dbinom{a_i+b_i+a_j+b_j}{a_i+a_j}$$

### Solution.
~~组合意义~~。  
这个东西的组合意义显然就是从 $(-a_i,-b_i)$ 走到 $(a_j,b_j)$ 的方案数。（只走网格  
~~然后就做完了~~。  
大概就是分别统计贡献，因为值域很小，所以可以快速计算。  
设计一个 dp 让表示当前这个点有多少种不同的到它的方法。  
然后每个点从它下面和右边转移过来。  
简单地化一下式子，让它变成
$$\sum_{i=1}^n\sum_{j=i+1}^n\dbinom{a_i+b_i+a_j+b_j}{a_i+a_j}$$
$$=\frac12\left(\sum_{i=1}^n\sum_{j=1}^n\dbinom{a_i+b_i+a_j+b_j}{a_i+a_j}-\sum_{i=1}^n\dbinom{a_i+b_i+a_i+b_i}{a_i+a_i}\right)$$

然后直接根据 dp 值算就好了。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
const int P=1e9+7,S=2001;int n,a[200005],b[200005],dp[4005][4005],fc[8005],fi[8005],res;
inline int ksm(int x,int q=P-2) {int r=1;for(;q;q>>=1,x=1ll*x*x%P) if(q&1) r=1ll*r*x%P;return r;}
inline int C(int n,int m) {return n<0||m<0||n<m?0:1ll*fc[n]*fi[m]%P*fi[n-m]%P;}
int main()
{
	read(n);for(int i=1;i<=n;i++) read(a[i]),read(b[i]),dp[S-a[i]][S-b[i]]++;
	fc[0]=1;for(int i=1;i<=8000;i++) fc[i]=1ll*fc[i-1]*i%P;
	fi[8000]=ksm(fc[8000]);for(int i=8000;i;i--) fi[i-1]=1ll*fi[i]*i%P;
	for(int i=1;i<=S+S;i++) for(int j=1;j<=S+S;j++) dp[i][j]=((ll)dp[i][j]+dp[i-1][j]+dp[i][j-1])%P;
	for(int i=1;i<=n;i++) res=((ll)res+dp[S+a[i]][S+b[i]]-C(a[i]+a[i]+b[i]+b[i],a[i]+a[i])+P)%P;
	return printf("%lld\n",1ll*res*ksm(2)%P),0;
}
```

---

## 作者：marTixx (赞：0)

## Pro

有 $n$ 组烧烤材料,每组有 $1$ 根竹签，$A_i$ 片牛肉和 $B_i$ 片青椒。所有的竹签都不同，但是所有的牛肉和青椒都不可区分。

用其中恰好两组材料做烧烤。每一组中的所有材料会以任意顺序从左到右放置在并排的两根竹签上。

两种方式是不同的当且仅当选的材料集合不同或者食材放置的形式不同。问方案数。

$\large n\leq 200,000, 1\leq A_i , B_i ≤ 2000$

## Sol

柿子为
$$
\large \sum_{i=1}^{n}\sum_{j=i+1}^{n}\dbinom{a_i+b_i+a_j+b_j}{a_i+a_j}
$$
数形结合，我们把后面那一个组合数转化，其实它表示的意思就是一个整点 $\large (-a_i,-b_i)$ 到 $\large (a_j,b_j)$ 的路径条数。

此时问题变成要求 $\large n$ 个点到 $\large n$ 个点的路径条数之和。

看到这里点的值域为$\large [1,2000]$，我们回归路径条数最原始的递推式，

设 $\large f_{i,j}$ 表示 $\large n$ 个点到点 $\large (i,j)$ 的路径条数之和，则 $\large f_{i,j}=f_{i-1,j}+f_{i,j-1}$

**很妙的是，我们给 $\large n$ 个出发点的 $\large f_{a_i,b_i}$ 初值设为 $\large 1$，就完美的完成了 $\large n$ 个点的转移**

最后注意给答案减去自己到自己点的路径条数，由于原题目柿子里的 $\large j=i+1$，所以我们还要给答案除以二。

## Code

```cpp
#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 2e5 + 30;
const int MX = 4e3 + 31;
const int MOD = 1e9 + 7;

int n, mx, my;
LL ans;
int a[N], b[N], f[MX][MX], c[2 * MX][MX];

int read()
{
    int s = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
    return s;    
}

int main()
{
    n = read();
    for (int i = 1; i <= n; ++ i) a[i] = read(), b[i] = read(), mx = std::max(mx, a[i] + 1), my = std::max(my, b[i] + 1);
    for (int i = 1; i <= n; ++ i) ++ f[mx - a[i]][my - b[i]];
    for (int i = 1; i <= 2 * mx; ++ i)
        for (int j = 1; j <= 2 * my; ++ j) f[i][j] = (f[i][j] + f[i - 1][j] + f[i][j - 1]) % MOD;
    c[1][0] = c[1][1] = 1;
    for (int i = 2; i <= 2 * MX - 58; ++ i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= MX - 30; ++ j) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
    }
    for (int i = 1; i <= n; ++ i) ans = (ans + f[a[i] + mx][b[i] + my] - c[2 * b[i] + 2 * a[i]][2 * b[i]] + MOD) % MOD;
    ans = (1ll * 500000004 * (ans + MOD)) % MOD;
    printf ("%lld\n", ans);
    return 0;
}
```



---

## 作者：Strelitzia (赞：0)

[题目传送门1](https://vjudge.net/problem/AtCoder-agc001_e)
[题目传送门2](https://www.luogu.com.cn/problem/AT1983)


---

首先，我们可以看出，这个题可以 $n^2$ 做，虽然这样会 $\mathrm{TLE}$。

我们考虑你敬爱的教练是如何向你引入组合数的。

![](https://cdn.luogu.com.cn/upload/image_hosting/3pe23ese.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


是这张图吧，$\dbinom{10}{6}$，就是从 $(0,0)$ 到 $(6,4)$ 只向上或右的方案数。

所以我们可以转换为 $(0,0)$ 到 $(a_i+a_j,b_i+b_j)$ 的方案数，

其实，我们如果把点都移到一块，统计答案就很快了。

我们可以把问题变为 $(-a_i,-b_i)$ 到 $(a_j,b_j)$ 的方案数，

这样就可以直接统计到 $(a_j,b_j)$ 的方案数。

然后就是根据这个图的计算方法，往上或往右。

最后减去 $(-a_i,-b_i)$ 到 $(a_i,b_i)$ 的距离，

除一个二（这里式子是从 $j = i + 1$ 开始的），避免重复计算。

```cpp
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<typename T>void Swap(T &x,T &y) {T z = x;x = y;y = z;}
template<typename T>T Min(T x,T y) {return x < y ? x : y;}
template<typename T>T Max(T x,T y) {return x > y ? x : y;}
template<typename T>T Abs(T x) {return x < 0 ? -x : x;}

const int M   = 	2000;
const int MOD = 1e9  + 7;
const int N   = 2e5  + 5;

int n;
int ans;
int f[(M << 1) + 5][(M << 1) + 5];
int a[N],b[N],fac[(M << 2) + 5],inv[(M << 2) + 5];

int A(int n,int m) {return 1ll * fac[n] * inv[n - m] % MOD;}
int C(int n,int m) {return 1ll * fac[n] * inv[n - m] % MOD * inv[m] % MOD;}
int quickPow(int a,int b) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = 1ll * ans * a % MOD;
		b >>= 1;
		a = 1ll * a * a % MOD;
	}
	return ans;
}

int main () {
	read(n);
	for (int i = 1 ; i <= n ; ++ i) {
		read(a[i]);read(b[i]);
		f[M - a[i]][M - b[i]] ++;
	}
	fac[0] = inv[0] = 1;
	for (int i = 1 ; i <= 8000 ; ++ i) fac[i] = 1ll * fac[i - 1] * i % MOD;
	inv[8000] = quickPow(fac[8000],MOD - 2);
	for (int i = 7999 ; i ; -- i) inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
	for (int i = 0 ; i <= 4000 ; ++ i) {
		for (int j = 0 ; j <= 4000 ; ++ j) {
			if (i == 0 && j == 0) continue;
			else if (i == 0) f[i][j] = (f[i][j] + f[i][j - 1]) % MOD;
			else if (j == 0) f[i][j] = (f[i][j] + f[i - 1][j]) % MOD;
			else if (i && j) f[i][j] = (f[i][j] + (f[i - 1][j] + f[i][j - 1]) % MOD) % MOD;
		}
	}
	for (int i = 1 ; i <= n ; ++ i) ans = ans + f[M + a[i]][M + b[i]],ans = ans > MOD ? ans - MOD : ans;
	for (int i = 1 ; i <= n ; ++ i) ans = ans - C(a[i] + b[i] << 1,a[i] << 1),ans = ans < 0 ? ans + MOD : ans;
	print(1ll * ans * quickPow(2,MOD - 2) % MOD);
	return 0;
}
```

---

## 作者：foreverlasting (赞：0)

[题面](https://www.luogu.org/problemnew/show/AT1983)

这里先提一句，题面的公式好像是错的哎。公式里的$j$应该是从$i+1$开始。

DP。

我们首先会知道一个结论：在一个平面中，从$A(a,b)$走到$B(c,d)$且只能向右或者向上走的方案数等于$C(c+d-a-b,c-a)$。那么就可以把这题转换成从$(-aj,bj)$走到$(ai,bi)$的方案数。

然后容斥+DP就好了。

code:
```
//2018.9.20 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register LL
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline LL read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline LL _abs(const res &x){
    return x>0?x:-x;
}
inline LL _max(const res &x,const res &y){
    return x>y?x:y;
}
const LL kcz=1e9+7;
const LL N=2e6+10,P=2e3+10;
namespace MAIN{
    LL inv[N],fac[N];
    inline void pre(){
        inv[0]=inv[1]=fac[0]=fac[1]=1;
        for(res i=2;i<=N-10;i++)fac[i]=(LL)fac[i-1]*i%kcz,inv[i]=(LL)inv[kcz%i]*(kcz-kcz/i)%kcz;
        for(res i=2;i<=N-10;i++)inv[i]=(LL)inv[i]*inv[i-1]%kcz;
    }
    inline LL C(const res &x,const res &y){
        return (LL)fac[x]*inv[y]%kcz*inv[x-y]%kcz;
    }
    LL n;
    LL dp[P*2+1000][P*2+1000];
    LL a[N],b[N],ans;
    inline void add(res &x,const res &y){
        x+=y;
        x=(x%kcz+kcz)%kcz;
    }
    inline LL qpow(res x,res y){
        res ans=1;
        while(y){
            if(y&1)ans=(LL)ans*x%kcz;
            y>>=1,x=(LL)x*x%kcz;
        }
        return ans%kcz;
    }
    inline void MAIN(){
        pre();
        n=read();
        for(res i=1;i<=n;i++)a[i]=read(),b[i]=read(),dp[P-a[i]][P-b[i]]++;
        for(res i=1;i<=2*P;i++)
            for(res j=1;j<=2*P;j++)
                add(dp[i][j],dp[i-1][j]+dp[i][j-1]);
        for(res i=1;i<=n;i++)add(ans,dp[P+a[i]][P+b[i]]),add(ans,kcz-C((a[i]+b[i])*2,a[i]*2));
        printf("%lld\n",ans*qpow(2,kcz-2)%kcz);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：hzoi_liuchang (赞：0)

## 分析
这一道题的暴力是比较好打的，我们两两枚举 $i,j$ ,每次计算  $C_{a[i]+a[j]+b[i]+b[j]}^{a[i]+a[j]}$ 将价值累加即可

我们会发现，暴力的算法总会枚举 $i$ 和 $j$，这样的效率肯定是 $n^2$ 的

于是，我们考虑组合数的几何意义

我们可以把 $C_{n+m}^{n}$ 看成从原点出发，只能向上或者向右走，到达坐标为 $(n,m)$ 的点的方案数

因此上面的式子可以理解到达坐标为 $(a[i]+a[j],b[i]+b[j])$ 的点的方案数

我们将原点和目标点向左下方平移，即同时减去 $(a[i],b[i])$ 

这样出发点就变成了 $(-a[i],-b[i])$ ，终点就变成了 $(a[j],b[j])$

这样就不用分别枚举 $i$ 和 $j$

此时我们设 $f[i][j]$ 为 $n$ 个点走到 $(i,j)$ 的方案数之和

初始时我们要把 $f[-a[i]][-b[i]]$ 加一

转移时，根据组合数的性质，有 $f[i][j]+=f[i-1][j]+f[i][j-1]$

最后统计答案时，我们要把自己到自己的贡献减去，还要把起点终点互换的情况减去

## 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3+101;
const int mod=1e9+7;
int n,m,a[maxn*100],b[maxn*100],ny[maxn*4],jc[maxn*4],jcc[maxn*4],f[maxn*2][maxn*2],s=2050;
long long getC(int n,int m){
	return (long long)jc[n]%mod*jcc[n-m]%mod*jcc[m]%mod;
}
int main(){
	scanf("%d",&n);
	ny[1]=1;
	for(int i=2;i<maxn*4;i++){
		ny[i]=(long long)((long long)mod-mod/i)*ny[mod%i]%mod;
	}
	jc[0]=jcc[0]=1;
	for(int i=1;i<maxn*4;i++){
		jc[i]=(long long)jc[i-1]*i%mod;
		jcc[i]=(long long)jcc[i-1]*ny[i]%mod;
	}
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		f[s-a[i]][s-b[i]]++;
	}
	for(int i=1;i<2*maxn-5;i++){
		for(int j=1;j<2*maxn-5;j++){
			f[i][j]=(long long)((long long)f[i][j]%mod+(long long)f[i-1][j]%mod+(long long)f[i][j-1]%mod)%mod;
		}
	}
	long long ans=0;
	for(int i=1;i<=n;i++){
		ans=(ans+(long long)f[s+a[i]][s+b[i]])%mod;
		ans=(ans-getC(2*a[i]+2*b[i],2*a[i]))%mod;
		ans=(ans+mod)%mod;
	}
	printf("%lld\n",(long long)ans*ny[2]%mod);
	return 0;
}

```



---

