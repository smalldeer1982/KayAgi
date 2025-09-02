# Two Hypercubes

## 题目背景

注：数据已经加强。

## 题目描述

$T$ 次询问，每次给定 $A,B,C$，求：

$$\Big(\sum_{x=1}^A\sum_{y=1}^B\sum_{z=1}^C[y^x=x^z]\Big)\bmod (10^9+7).$$

## 说明/提示

【样例 1 解释】

第一组询问 $A=1,B=2,C=3$，满足条件的三元组 $(x,y,z)$ 有 $(1,1,1),(1,1,2),(1,1,3).$

第二组询问 $A=3,B=4,C=5$，满足条件的三元组 $(x,y,z)$ 有：

$(1,1,1),(1,1,2),(1,1,3),(1,1,4),(1,1,5),(2,2,2),(2,4,4),(3,3,3).$

第三组询问 $A=6,B=7,C=8$，满足条件的三元组 $(x,y,z)$ 有：

$(1,1,1),(1,1,2),(1,1,3),(1,1,4),(1,1,5),(1,1,6),(1,1,7),(1,1,8);$

$(2,2,2),(2,4,4),(3,3,3),(4,2,2),(4,4,4),(5,5,5),(6,6,6).$

---

【数据范围】

对 $100\%$ 的数据，满足 $1\leq T\leq 2\times 10^4,\ 1\leq A,B,C\leq 10^{18}$。


- $\text{Subtask}\ 0(5\ \text{pts})$：$T,A,B,C\leq 11$。
- $\text{Subtask}\ 1(7\ \text{pts})$： $T\leq 20,\ A,B,C\leq 3333$。
- $\text{Subtask}\ 2(17\ \text{pts})$：$T\leq 20,\ A,B\leq 10^{10},\ C\leq 3333$。
- $\text{Subtask}\ 3(17\ \text{pts})$：$T\leq 20,\ A,B,C\leq 10^{10}$。
- $\text{Subtask}\ 4(27\ \text{pts})$：$A,B,C\leq 10^{11}$。
- $\text{Subtask}\ 5(27\ \text{pts})$：无特殊限制。

## 样例 #1

### 输入

```
3
1 2 3
3 4 5 
6 7 8```

### 输出

```
3
8
15```

## 样例 #2

### 输入

```
2
999 9999 99999
2000 20000 200000```

### 输出

```
101202
202276```

# 题解

## 作者：I_am_Accepted (赞：12)

哥我尝试阅读了一下你的 P8380 题解，看了一整天了，真的好抽象，，完全看不懂，您这个思路虽然很简单但是我真的看不懂，式子是怎么推的。。我还是去写不高明的做法了

$$\begin{aligned}
&\sum_{x=1}^A\sum_{y=1}^B\sum_{z=1}^C[y^x=x^z]
\\=&
C+\sum_{d>1}\sum_{x=1}^{\log_dA}\sum_{y=1}^{\log_dB}[x\perp y]\sum_{z=1}^C[yd^x=xz]
\\=&
C+\sum_{d>1}\sum_{x=1}^{\log_dA}\sum_{y=1}^{\log_dB}[x\perp y][x|d^x][y\frac{d^x}{x}\le C]
\\=&
C+\sum_{x=1}^{\log_2A}\sum_{y=1}^{\log_2B}[x\perp y]\sum_{d>1}[d^x\le\min(A,\frac{xC}{y}),d^y\le B][x|d^x]
\end{aligned}$$

$x=1$ 时内部为
$$
\sum_{y=1}^{\log_2B}\sum_{d>1}[d\le\min(A,\frac{C}{y}),d^y\le B]
$$

$x=2$ 时内部为
$$
\sum_{y=1}^{\log_2B}[2\nmid y]\sum_{d>1,2|d}[d^2\le\min(A,\frac{2C}{y}),d^y\le B]
$$

$x\ge 3$ 时，$d\le 10^6$，预处理
$$
f^{(x)}(c)=\sum_{d=2}^c[x|d^x]
$$
即可。

快速处理 $d^a\le b$ 的 $d$ 的上界可以对每个 $a$ 预处理 $d^a$ 数组查询时二分即可。

复杂度 $O(n^{1/3}\log+T\log^2\cdot\log\log)$，其中 $\log\log$ 的由来：
$$
\sum_{i=3}^{\log}\log(n^{1/i})=\log \cdot \sum_{i=1}^{\log}\frac{1}{i}=\log\cdot\log\log
$$

---

## 作者：FireBladeMaster (赞：12)

因为五哥 APIO 获得了 221.36 分的高分，位居中国国际金牌外 rk2，所以有了这篇题解。

显然如果 $y^x=x^z$，那么一定有 $x=p^a,y=p^b$。

考虑保证 $(a,b)=1$，把这玩意代入进去。

$$(p^b)^{p^a}=(p^a)^z$$

$$p^{bp^a}=p^{az}$$

$$bp^a=az$$

$$p^a=\dfrac a b z$$

先特判掉 $p=1$ 的情况之后啊，这个 $p\ge 2$，所以 $a,b$ 也就 $<\log V$了。

然后枚举这个 $a,b$，考虑怎么快速去计算有多少 $p,z$ 使得 $p^a=\dfrac a b z$。

那左边是个 $a$ 次方数，右边也是 $a$ 次方数，而 $(a,b)=1$ 所以 $z$ 得是 $b$ 的倍数。记 $z'=\dfrac z b$，则 $p^a=az'$，$z'\le \dfrac C b$。

然后又可以把右边表示成 $af_az''$，其中 $f_a$ 是满足 $af_a$ 是 $a$ 次方数的最小正整数。这玩意可以预处理出来。这样只要 $z''$ 是 $a$ 次方数并且 $\sqrt[a]{af(a)}|p$ 就行了。

那这玩意最后就是求 $\sqrt[a]{r}$ 这样的东西下取整，直接 pow 之类有精度损失，手写个二分就能过了。


---

## 作者：gyc18 (赞：12)

此题解为官方题解

考虑设 $y^x=x^z=d^{[x,z]}$，然后枚举 $g=(x,z)$，再将 $x$ 除掉 $g$。

然后可以得到 $y^{gx}=(gx)^z=d^{xz}$，即 $d=\sqrt[x]{gx}$，同时有 $y=d^{\frac{z}{g}}$。同时我们要求 $g|z$ 且 $z/g\perp x$。

然后改写式子。

$$\sum_{z=1}^C\sum_{g|z}\sum_{x=1}^{\lfloor\frac{A}{g}\rfloor}[\sqrt[x]{gx}\in\mathbb Z][(\sqrt[x]{gx})^{\frac{z}{g}}\leq B][z/g\perp x]$$

$$\sum_{g=1}^{\min\{A,C\}}\sum_{x=1}^{\lfloor\frac{A}{g}\rfloor}\sum_{z=1}^{\lfloor\frac{C}{g}\rfloor}[\sqrt[x]{gx}\in\mathbb Z][(\sqrt[x]{gx})^{z}\leq B][z\perp x]$$

$$\sum_{g=1}^{\min\{A,C\}}\sum_{z=1}^{\lfloor\frac{C}{g}\rfloor}[g\in\mathbb Z][g^{z}\leq B][z\perp 1]+\sum_{g=1}^{\min\{A,C\}}\sum_{x=2}^{\lfloor\frac{A}{g}\rfloor}\sum_{z=1}^{\lfloor\frac{C}{g}\rfloor}[\sqrt[x]{gx}\in\mathbb Z][(\sqrt[x]{gx})^{z}\leq B][z\perp x]$$

$$\sum_{g=1}^{\min\{A,C\}}\sum_{z=1}^{\lfloor\frac{C}{g}\rfloor}[g^{z}\leq B]+\sum_{g=1}^{\min\{A,C\}}\sum_{x=2}^{\lfloor\frac{A}{g}\rfloor}\sum_{z=1}^{\lfloor\frac{C}{g}\rfloor}[\sqrt[x]{gx}\in\mathbb Z][(\sqrt[x]{gx})^{z}\leq B][z\perp x]$$

$$\sum_{g=1}^{\min\{A,C\}}\min\{\lfloor\log_gB\rfloor,\lfloor C/g\rfloor\}+\sum_{g=1}^{\min\{A,C\}}\sum_{x=2}^{\lfloor\frac{A}{g}\rfloor}\sum_{z=1}^{\lfloor\frac{C}{g}\rfloor}[\sqrt[x]{gx}\in\mathbb Z][(\sqrt[x]{gx})^{z}\leq B][z\perp x]$$

左边只有 $\log$ 段，二分出每一段然后直接算 $O(\log^2n)$（$n=\max A,B,C$），考虑如何计算右边。

换序求和：

$$\sum_{x=2}^{A}\sum_{z=1}^{C}[z\perp x]\sum_{g=1}^{+\infty}[gx\leq A][gz\leq C][\sqrt[x]{gx}\in\mathbb Z][(\sqrt[x]{gx})^{z}\leq B]$$

考虑求出一个最小的 $f(x)$ 使得 $\sqrt[x]{xf(x)}$ 能开出来，然后所有的 $g$ 都可以被表示成 $k^xf(x)$，其中 $k$ 是正整数。因为 $xf(x)\geq 2^x$，所以 $f(x)\leq A$ 的 $x$ 最多是 $\log $ 量级的。

$$\sum_{x=2}^{A}\sum_{z=1}^{C}[z\perp x]\sum_{k=1}^{+\infty}[k^xxf(x)\leq A][k^xzf(x)\leq C][k^z(\sqrt[x]{xf(x)})^{z}\leq B]$$

$$\sum_{x=2}^{A}[xf(x)\leq A]\sum_{z=1}^{C}[(\sqrt[x]{xf(x)})^{z}\leq B][z\perp x]\sum_{k=1}^{+\infty}[k^xxf(x)\leq A][k^xzf(x)\leq C][k^z(\sqrt[x]{xf(x)})^{z}\leq B]$$

这样前两个求和都可以暴力，第三个求和可以对上界进行二分。看起来是一个 3log 做法？

考虑到 $x$ 很小的时候，$f(x)$ 大多等于 $x^{x-1}$，所以第一个求和可以视作是 $\dfrac{\log n}{\log\log n}$ 的。

而最后的二分上界在最坏情况下依次是 $n,n^{1/2},n^{1/3},\cdots$，所以后面两个求和号的复杂度是 $\sum_{i=1}^{\log n}\log n^{1/i}=\sum_{i=1}^n\frac{1}{i}\log n=\log n\log\log n$ 的。

所以这一部分的复杂度是 $\dfrac{\log n}{\log\log n}\times\log n\log\log n=\log^2n$ 的。

于是做完了。总复杂度 $O(T\log^2n)$。


## 代码
```cpp

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=70,M=59;
const ll P=1e9+7,MX=1e18;
ll t,a,b,c,ans,sja[N],sjb[N],sj[N],f[N],cp[N][N];
ll gcd (ll a,ll b) {return (b==0?a:gcd(b,a%b));}
ll qpow (ll a,ll b) {
	ll res=1;
	while (b) {
		if (b&1) {
			if (res>MX/a) {return MX+1;}
			res*=a;
			if(b==1)break;
		}
		if (a>MX/a) {return MX+1;}
		a*=a,b>>=1;
	}
	return res;
}
ll gt (ll a,ll b) {
	ll l=1,r=sj[b];
	while (l<r) {
		ll mid=(l+r+1)>>1;
		if (qpow(mid,b)<=a) {l=mid;}
		else {r=mid-1;}
	}
	return l;
}
ll calc (ll x) {
	ll res=1,cpx=x;
	for (int i=2;i<=x;i++) {
		if (x%i==0) {
			ll cnt=0;
			while (x%i==0) {cnt++,x/=i;}
			cnt=(cnt+cpx-1)/cpx;
			for (int j=1;j<=cnt;j++) {res*=i;}
		}
	}
	return res;
}
int main () {
	for (int i=1;i<=M;i++) {
		sj[i]=MX;
		sj[i]=gt(MX,i),f[i]=calc(i);
		for (int j=1;j<=M;j++) {cp[i][j]=(gcd(i,j)==1);}
	}
	scanf("%lld",&t);
	for (int i=1;i<=t;i++) {
		scanf("%lld%lld%lld",&a,&b,&c);
		ans=c%P;
		for (int i=1;i<=M;i++) {sja[i]=gt(a,i),sjb[i]=gt(b,i);}
		for (int i=1;i<=M;i++) {
			for (int j=1;j<=M;j++) {
				if (!cp[i][j]) {continue;}
				ll l=0,r=min(sja[i],sjb[j])/f[i];
				while (l<r) {
					ll mid=(l+r+1)>>1;
					if (qpow(mid*f[i],i)/i<=c/j) {l=mid;}
					else {r=mid-1;}
				}
				ans=(ans+l)%P;
				if (f[i]==1&&j/i<=c) {ans=(ans+P-1)%P;}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Vidoliga (赞：4)

出在模拟赛里面了，推的式子不能浪费，所以提供两种解法。

玩一下什么情况 $y^x=x^z$ 就是考虑将 $x$ 表示为 $m^a$ 的形式，$y$ 表示为 $m^b$ 的形式，然后需要满足的是 $m^{bx}=m^{az}$，而由于我们是在计数，考虑构造一种双射的形式：对于一个三元组 $(m,a,b)$ 能唯一对应一个 $(x,y)$，对于一组合法的 $(x,y)$ 一定能射到一组 $(m,a,b)$ 上。

不妨通过应定 $\gcd(a,b)=1$ 来保证这一点，考虑一组 $(x,y)$ 能表示成 $(m,a,b)$ 而 $\gcd(a,b)\not=1$，不难通过变化为 $(m^{\gcd(a,b)},\dfrac{a}{\gcd(a,b)},\dfrac{a}{\gcd(a,b)})$ 来保证计数不重。

那么可以很轻松地写出式子：

$$\sum\limits_{x=1}^{A} \sum\limits_{y=1}^{B} \sum\limits_{z=1}^{C} [y^x=x^z]$$

特判一下 $m=1$ 的情况：

$$=C+\sum\limits_{m> 1}^{} \sum\limits_{a=1}^{\log _{m}A} \sum\limits_{b=1}^{\log _{m}B} [\gcd(a,b)=1][\dfrac{bm^a}{a}\leq C][a|bm^a]$$

由于 $\gcd(a,b)=1$：

$$=C+\sum\limits_{m> 1}^{} \sum\limits_{a=1}^{\log _{m}A} \sum\limits_{b=1}^{\log _{m}B} [\gcd(a,b)=1][\dfrac{bm^a}{a}\leq C][a|m^a]$$

$$=C+ \sum\limits_{a=1}^{\log _{2}A} \sum\limits_{b=1}^{\log _{2}B} \sum\limits_{m> 1}[\gcd(a,b)=1][\dfrac{bm^a}{a}\leq C][a|m^a][m^a \leq A][m^b \leq B]$$

$$=C+ \sum\limits_{a=1}^{\log _{2}A} \sum\limits_{b=1}^{\log _{2}B} \sum\limits_{m> 1}[\gcd(a,b)=1][\dfrac{bm^a}{a}\leq C][a|m^a][m^a \leq A][m^b \leq B]$$

实际上，推到这步这题就结束了，但是这题是个~~大粪~~卡常题。

你但凡观察一下，你直接枚举 $a,b$ 然后算出 $m$ 的上界 $t$，然后算个 $\sum\limits_{m=2}^{t} [a|m^a]$ 就没了。

然后想了一下，你可能想在 $t$ 比较小的时候预处理这部分。

而不难发现，当 $a\geq 3$，有 $t\leq 10^6$。

然后对于 $a=1$ 这个 $a|m^a$ 没有限制，而 $a=2$，$a|m^2$ 其实就是 $2|m$。

好，这个做法通过 pow 调整可以做到 $O(n\log n+T \log^2 n)$，或者通过二分做到 $O(n\log n+T \log^2 n \log \log n)$。

有预处理的做法没意思，我们搞点有意思的，这部分大致是我赛时的思路（虽然赛时没有预处理而是后面这部分暴力做了）。

考虑一下你在写暴力判断 $a|m^a$ 怎么判断的，初始一个 $q=a$，不断将 $q \rightarrow \dfrac{q}{\gcd(q,m)}$ 操作 $a$ 次，若 $q=1$ 则返回 true。

这个是在做什么？考虑 $m$ 的所有质因子 $p^e$，考虑 $a$ 中含有的同样质因子 $p^{e^{\prime}}$，上述判断相当于是对于所有 $p$，判断是否都有 $ea\geq e^{\prime}$，所以相当于我给每个 $a$ 中质因子 $p$ 的指数在 $m$ 中都有限制。

那么不难算出这个偏序关系中最小的 $m^{\prime}$，那么对于 $m$ 是 $m^{\prime}$ 的倍数就是 $a|m^a$ 成立的充要条件。

设这个 $m^{\prime}=f(a)$，那么 $\sum\limits_{m=2}^{t}[a|m^a]=[f(a)=1](t-1)+[f(a)>1] \lfloor\dfrac{t}{f(a)}\rfloor$

这个做法的复杂度同样是 $O(T \log^2 n \log \log n)$。

Code：

```cpp
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
//#pragma GCC optimize("Ofast","unroll-loops","inline")
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define pb push_back
using namespace std;
const int N=1e6+20,M=1e6+20,mod=1e9+7,LGN=63;
const int mx[]={0,1000000000000000010ll,1000000010,1000010,32000,4000,1010};
const int Mx=2e18;
const int Lim=1e18;
namespace FastIO {
	struct IO {
	    char ibuf[(1 << 20) + 1], *iS, *iT, obuf[(1 << 20) + 1], *oS;
	    IO() : iS(ibuf), iT(ibuf), oS(obuf) {} ~IO() { fwrite(obuf, 1, oS - obuf, stdout); }
		#if ONLINE_JUDGE
		#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
		#else
		#define gh() getchar()
		#endif
		inline bool eof (const char &ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == 't' || ch == EOF; }
	    inline long long read() {
	        char ch = gh();
	        long long x = 0;
	        bool t = 0;
	        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
	        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
	        return t ? ~(x - 1) : x;
	    }
	    inline void read (char *s) {
	    	char ch = gh(); int l = 0;
	    	while (eof(ch)) ch = gh();
	    	while (!eof(ch)) s[l++] = ch, ch = gh();
	    }
	    inline void read (double &x) {
	    	char ch = gh(); bool t = 0;
	    	while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
	    	while (ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gh();
	    	if (ch != '.') return t && (x = -x), void(); ch = gh();
	    	for (double cf = 0.1; '0' <= ch && ch <= '9'; ch = gh(), cf *= 0.1) x += cf * (ch ^ 48);
	    	t && (x = -x);
	    }
	    inline void pc (char ch) {
	    	#ifdef ONLINE_JUDGE
	    	if (oS == obuf + (1 << 20) + 1) fwrite(obuf, 1, oS - obuf, stdout), oS = obuf; 
	    	*oS++ = ch;
	    	#else
	    	putchar(ch);
	    	#endif
		}
		template<typename _Tp>
	    inline void write (_Tp x) {
	    	static char stk[64], *tp = stk;
	    	if (x < 0) x = ~(x - 1), pc('-');
			do *tp++ = x % 10, x /= 10;
			while (x);
			while (tp != stk) pc((*--tp) | 48);
	    }
	    inline void write (char *s) {
	    	int n = strlen(s);
	    	for (int i = 0; i < n; i++) pc(s[i]);
	    }
	} io;
	inline long long read () { return io.read(); }
	template<typename Tp>
	inline void read (Tp &x) { io.read(x); }
	template<typename _Tp>
	inline void write (_Tp x) { io.write(x); }
}
using namespace FastIO;
int fl[LGN][LGN],f[LGN],pw[LGN][N],L[LGN];
int qpow(int a,int b){
	if(b==0) return 1;
	int res=1;
	while(b){if(b&1){if(res>Lim/a) return Lim+1;res=res*a;}b>>=1;if(!b) break;if(a>Lim/a) return Lim+1;a=a*a;}
	return res;
}
inline int get(int x,int v){
	if(v==1) return x;
	if(v==2) return sqrtl(x);
	int l=0,r=L[v],ans=0;
	while(l<=r){
		int mid=(l+r)/2;
		if(pw[v][mid]<=x) l=mid+1,ans=mid;
		else r=mid-1;
	}
	return ans;
}
inline int Lg(int x,int B){
	int res=0,p=1;
	while(p<=B/x) p*=x,res++;
	return res;
}
inline int calc(int i,int A,int B,int C){
	int p=Lg(2,B),res=0;
	int g=f[i];
	for(int y=1;y<=p;y++) if(fl[i][y]){
		int lim=get(B,y);
		lim=min(lim,get((ll)min((__int128)A,((__int128)C*i/y)),i));
		if(g==1){
			if(lim>1) res=(res+lim-1)%mod;
		}
		else res=(res+lim/g)%mod;
	}return res;
}
int A,B,C;
vector<int> e[LGN];
inline int gcd(int a,int b){if(!b||!a) return a+b;int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=(az>bz)?bz:az,t;b>>=bz;while(a) a>>=az,t=a-b,az=__builtin_ctz(t),b=a<b?a:b,a=t<0?-t:t;return b<<z;}
inline bool chk(int x,int d){
	int p=x,tot=x;
	while(p!=1&&tot){
		int g=gcd(d,p);
		if(g==1) break;
		p/=g,tot--;
	}
	return p==1;
}
int g[LGN][N];
void solve(){
	A=read();B=read();C=read();
	int lim=Lg(2,A),L=Lg(2,B),res=0;
	for(int i=1;i<=lim;i++) res=(res+calc(i,A,B,C))%mod;
	write((C+res)%mod);io.pc('\n');
}
signed main(){
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	for(int x=1;x<=62;x++){
		for(int y=1;y<=62;y++) if(gcd(x,y)==1) fl[x][y]=1,e[x].pb(y);
	}
	for(int x=3;x<=60;x++){
		L[x]=1;
		for(;qpow(L[x],x)<=Lim;L[x]++) ;
		for(int i=1;i<=L[x];i++) pw[x][i]=qpow(i,x);
	}
	for(int x=1;x<=62;x++){
		for(int y=1;y<=x;y++) if(x%y==0&&chk(x,y)){
			f[x]=y;break;
		}
	}
	int T=read();
	while(T--) solve();
	return 0;
}
```

没有精细实现，跑得很慢。

---

## 作者：Jeefy (赞：1)

本题解算是对 [I_am_Accepted](https://www.luogu.com.cn/user/101868) 老哥 [题解](https://www.luogu.com.cn/blog/ShaoJia/solution-p8380#) 的细化（对我等蒟蒻友好一点。

首先有如果 $y^x = x^z$ 那么 $x, y$ 一定可以表示为 $x = p^a, y = p^b$。

此时存在 $(p^a)^{p^b} = p^{bz}$，可以得到 $ap^b = bz$，注意特判一下 $p = 1$ 的情况，此时答案就是 $C$，于是后文默认 $p \gt 1$。

（这里 $x, y$ 含义有变化）于是式子化为：

$$
C + \sum_{p > 1} \sum_{x = 1}^{\log_d A} \sum_{y = 1}^{\log_dB} [x \bot y] \sum_{z = 1}^C [yp^x = xz]
$$

之所以需要 $[x \bot y]$ 是因为会在 $(\frac x {\gcd(x, y)}, \frac y {\gcd(x, y)})$ 的时候算到，所以需要互质保证不重复计数。

发现如果 $x, y, p$ 确定，那么 $z$ 也将确定，稍稍将 $p^x \le A$， $p^y \le B$ 和 $z \le C$ 的限制加上，可以得到：

$$
C + \sum_x \sum_y [x \bot y] \sum_p [x | p^x] [p^x \le A][d^y \le B][z = y \frac {p^x}x \le C]
$$

再化简一下

$$
C + \sum_x \sum_y [x \bot y] \sum_p [x | p^x] [p^x \le \min(A, \frac {Cx}{y})][p^y \le B]
$$
其实到这里就可以求出答案了。

考虑 $x = 1$ 时，后面的式子可以转化为 $\sum_p [p \le \min(A, \frac {C}{y})][p^y \le B]$。枚举 $y$，这在每一次都可以二分快速求解，注意 $p \gt 1$。

考虑 $x = 2$ 时，同理，转化为 $\sum_{y \equiv 1 \bmod 2} \sum_{p \equiv 0 \bmod 2} [p^2 \le \min(A, \frac {2C}y)][p^y \le B]$。同样 $p$ 的上界可以很容易的二分求出，此时只有一半的有用，故假定上界为 $k$，那么对答案的贡献为 $\lfloor \frac k2 \rfloor$。

剩下的时候考虑到 $A \le 10^{18}$，所以 $p$ 至多可以到达 $10^6$，于是预处理，对于每一个 $x$，枚举 $p$，判断是否满足 $[x | p^x]$，如果满足，加入一个数组中（注意是有序的），在求解的时候在这个数组中二分满足 $[p^x \le \min(A, \frac {Cx}{y})][p^y \le B]$ 的个数即可，注意 $\frac {Cx}{y}$ 可以爆 `long long`，这边建议使用 `double` 对 $10^{18}$ 取 $\min$。

接下来，如果发现 TLE，那么可以尝试如下卡常操作：

- 记忆化 $\gcd(x, y) = 1$，由于当 $x, y$ 很大的时候实际上的操作没有多少，而 $\gcd$ 可以高达 $10$ 次操作，所以很不优秀（能 $O(1)$ 就别 $O(\log)$
- 在预处理的时候，可以另开一个数组保存 $p^x$，这样在 $p \ge 3$ 二分的时候就不用计算 $p^x$ 了。
- 在 $p \ge 3$ 二分的时候，观察到如果 $x \ge y$ 并且 $p^x \le B$，那么一定有 $p^y \le B$，所以可以大胆的剪枝优化常数。

所以这种写法复杂度是 $O(T \log^3 V \log \log V)$ 的，但是能过……于是可以愉快的 $\texttt{\colorbox{#52C41A}{\textcolor{white}{AC}}}$ 本题了。

~~常数巨大且十分丑陋的~~代码链接：[洛谷云剪切板](https://www.luogu.com.cn/paste/bzv8uko9)

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8380)。

## 思路

容易得到 $x=t^a,y=t^b,(\gcd(a,b)=1)$，否则一定不满足条件，继续推导有 $t^{bt^a}=t^{az}$，即 $bt^a=az$，我们可以得到 $z=\dfrac{bt^a}{a}$，由于 $a,b$ 互质，那么 $a\mid t^a$。

接下来枚举 $t,a,b$。

$$
\begin{aligned}
&\ \ \ \ \ C+\sum_{t\ge 2}\sum_{a= 1}^{\log_t A}\sum_{b= 1}^{\log_t B}[a\bot b][a\mid t^a][\frac{bt^a}{a}\le C]\\
&=C+\sum_{a\ge 1}\sum_{b\ge 1}[a\bot b]\sum_{t\ge 2}[a\mid t^a][t^a\le A][t^b\le B][\frac{bt^a}{a}\le C]\\
&=C+\sum_{a\ge 1}\sum_{b\ge 1}[a\bot b]\biggl\lfloor \dfrac{\min(\sqrt[a]{Ca/b},\sqrt[a]{A},\sqrt[b]{B})}{f(a)} \biggl\rfloor
\end{aligned}
$$

其中 $f(a)=\prod_{p\in\mathbb{P},p\mid a}p$。

注意 $a=1$ 的情况要特判。

时间复杂度可以做到 $\mathcal O (T\log^2 n)$。

---

## 作者：hfjh (赞：0)

# P8380 Two Hypercubes 题解 
方法和题解一一样，但讲了一下细节，希望大家能懂。
## 题意

$T$ 次询问，每次给定 $A,B,C$，求：

$$
\Big(\sum_{x=1}^A\sum_{y=1}^B\sum_{z=1}^C[y^x=x^z]\Big)\bmod (10^9+7)
$$

## 题解

设 $x = p^a, y = p^b$ ，我们枚举 $a,b$ 算有多少种 $p$ 合法，避免算重我们事先只考虑 $gcd(a,b) = 1$ 的 $(a,b)$。

则

$$
\begin{aligned}
&p^{bp^a} = p^{az}\\
&bp^a = az\\
&p^a = \frac a b z\\
\because &\gcd(a,b) = 1\\
\therefore &z|b 
\end{aligned}
$$

我们设 $z' = \frac z b, p^a = az',a|p^a$。

我们将 $a$ 质因数分解变成 $a= p_1^{q_1}p_2^{q_2}\cdots p_n^{q_n}$。

设 $f(a) = p_1p_2p_3\cdots p_n$。

那么 $\forall w\in Z,p^a = (wf(a))^a, p = wf(a)$  只要不超过 $A,B,C$ 限制都合法。

我们可以二分 $w$。

下面就是要让每个数都在范围里面了。

$p^a\le A, p^b \le B,z\le C$。

$$
\begin{cases}
p\le \min(\sqrt[a]A,\sqrt[b]B)\\

w\le \frac p {f(a)}\le \frac {\min(\sqrt[a]A,\sqrt[b]B)}{f(a)}\\

\frac {p^a} a \le \frac C b\rightarrow \frac {(wf(a))^a} a\le \frac C b
\end{cases}
$$

以 $l= 0, r= \frac {\min(\sqrt[a]A,\sqrt[b]B)}{f(a)}$，根据 $\frac {(wf(a))^a} a\le \frac C b$ 单调性二分出 $w$。

直接 `ans += w`。

我们枚举 $a,b$ 的时候 $a=1$ 时 $f(a)$ 刚好 $=1$,  $b$ 无论等于多少都有一种 $p = 1, x= 1, y = 1$ 的情况，我们需要特判掉。

这样我们还需要加上 $(1,1,1),(1,1,2),\cdots,(1,1,C)$ 的 $C$ 组贡献。

### 温馨提示

本题极度卡时限，$\forall x,y\in[1,64]$ 需要预处理：

$\sqrt[x]{10^{18}},f(x),\gcd(x,y)$。

对于已知 $A,B$ 预处理 $\sqrt[x]A,\sqrt[x]B$。

开根使用二分答案，对 $\sqrt[x]A,\sqrt[x]B$ 求解时二分答案上界设成 $\sqrt[x]{10^{18}}$。
## 代码

```
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 60, mod = 1e9 + 7;
const ll inf = 1e18; 
int t;
ll A, B, C;
ll l, r, mid, sj[N + 10], sja[N + 10], sjb[N + 10], f[N + 10], ans;
int d[N + 10][N + 10];
int gcd(int x, int y){
	return (y == 0 ? x : gcd(y, x % y));
}
ll read(){
	ll ans = 0;
	char c = getchar();
	while(c < '0' || c > '9'){
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		ans = ans * 10 + c - '0';
		c = getchar();
	}
	return ans;
}
ll mpow(ll x, ll k){
	ll ans = 1;
	while(k){
		if(k & 1){
			if(ans > inf / x) return inf + 10;
			ans *= x; 
			if(k == 1) break;
		}
		if(x > inf / x) return inf + 10;
		x = x * x; k >>= 1;
	} 
	return ans;
}
ll calc1(ll x, ll lim){
	l = 1, r = sj[x];
	while(l < r){
		mid = (l + r + 1) >> 1; 
		if(mpow(mid, x) <= lim) l = mid;
		else r = mid - 1;
	}
	return l;
}
ll calc2(ll x){
	ll ans = 1;
	for(ll i = 2; i <= x; ++i){
		if(x % i == 0){
			while(x % i == 0) x /= i;
			ans = ans * i;
		}
	}
	return ans;
}
void pre(){
	for(int i = 1; i <= N; ++i){
		sj[i] = inf;
		sj[i] = calc1(i, inf);
		f[i] = calc2(i);
		for(int j = 1; j <= N; ++j){
			d[i][j] = (gcd(i, j) == 1);		
		}
	}
}
void op(){
	ans = C % mod;
	for(int i = 1; i <= N; ++i) sja[i] = calc1(i, A), sjb[i] = calc1(i, B);
	for(int i = 1; i <= N; ++i){
		for(int j = 1; j <= N; ++j){
			if(!d[i][j]) continue;
			l = 0, r = min(sja[i], sjb[j]) / f[i];
			while(l < r){
				mid = (l + r + 1) >> 1;
				if(mpow(mid * f[i], i) / i <= C / j) l = mid;
				else r = mid - 1;
			} 
			ans = (ans + l) % mod;
			if(f[i] == 1 && j / i <= C) ans = (ans - 1 + mod) % mod;
		} 
	}
}
int main(){
	pre(); 
	t = read();
	while(t--){
		A = read();
		B = read();
		C = read();
		op();
		cout<<ans<<'\n';
	}
	
}
```

---

