# 【MX-X2-T4】「Cfz Round 4」Gcd with Xor

## 题目背景

原题链接：<https://oier.team/problems/X2D>。

---

ねえ もしも全て投げ捨てられたら  
呐 若然能将一切舍弃的话

笑って生きることが楽になるの  
笑着活下去这样的事就会变的轻松吗

## 题目描述

给定两个正整数 $n,k$。

定义 $\displaystyle f(x)=\sum_{i=1}^x \gcd(i,i\oplus x)^k$。计算 $\displaystyle \sum_{i=1}^n f(i)$。其中 $\gcd(a,b)$ 表示 $a$ 和 $b$ 的最大公因数，$\oplus$ 表示**按位异或**，即 C++ 中的 `^`。

由于答案可能很大，所以你只需要输出答案对 $10^9+7$ 取模的结果。

## 说明/提示

**【样例解释】**

对于第 $1$ 组测试数据：

$f(1)=\gcd(1,0)^2=1$。

$f(2)=\gcd(1,3)^2+\gcd(2,0)^2=5$。

$f(3)=\gcd(1,2)^2+\gcd(2,1)^2+\gcd(3,0)^2=11$。

$f(1)+f(2)+f(3)=17$。

**【数据范围】**

对于所有测试数据，$1\le T\le 1000$，$1\le n\le 2\times 10^5$，$\sum n\le 2\times 10^5$，$1\le k\le 10^9$。

**本题采用捆绑测试。**

设 $\sum n$ 表示单个测试点中 $n$ 的和。

- Subtask 1（10 points）：$\sum n\le 2000$。
- Subtask 2（12 points）：$\sum n\le 10^4$。
- Subtask 3（15 points）：$k=1$。
- Subtask 4（45 points）：$\sum n\le 10^5$。
- Subtask 5（18 points）：无特殊限制。

## 样例 #1

### 输入

```
5
3 2
10 1
261 261
2333 2333
124218 998244353```

### 输出

```
17
134
28873779
470507314
428587718
```

# 题解

## 作者：Zzzcr (赞：35)

upd：为防止歧义换了个变量名。

---

提供一个唐氏做法，不需要莫比乌斯反演。

首先把原式放到一起：

$$\sum_{i=1}^n{\sum_{j=1}^{i}\gcd(j,i\oplus j)^k}$$

这个 $\gcd^k$ 和 $\oplus$ 看着都比较丑，考虑先枚举 $\gcd$，记作 $d$，只需要对于每个 $d$，求得 $i\oplus j$ 和 $j$ 都是 $d$ 的倍数的合法 $(i, j)$ 个数，记作 $r_d$，并做简单容斥就能求出答案，于是只需要考虑如何快速求出每个 $r_d$。

令 $x=i\oplus j$，我们可以容易的找到一种表述 $r_d$ 的方式，即：
$$
r_d=\sum_{d\mid x}\sum_{t=x}^{n}[d\mid t\oplus x]
$$

考虑优化这个计算过程。

考虑维护一个序列 $a$，枚举 $d$，再在每个 $x$ 处做单点 $+1$。发现对于每对 $(x,i)$，$a_{x\oplus i}$ 会对 $r_d$ 造成贡献，当且仅当 $x\oplus i \le n$。我们当然可以通过枚举 $i$ 来做到 $O(n^2 \log{n})$，但这并不够优秀，回顾一下刚才对 $a$ 进行的操作，只有单点 $\pm1$，全局下标 $\operatorname{xor}$ 和区间求和，这显然可以使用线段树优化，于是我们便用 $O(n\log^2{n})$ 的复杂度解决了此题。

---

## 作者：min_inf (赞：17)

咋大家都在莫反，来个简单的不用脑子做法。

首先答案显然等于 $\sum\limits_{i=1}^n\sum\limits_{j=i}^n\gcd(i,i\oplus j)^k$。对每个 $\gcd$ 分别求方案数，可以先统计所有 $d\mid\gcd$ 的方案数然后减掉已经求过的倍数的方案数。

现在我们要求 $\sum\limits_{d\mid i}^n\sum\limits_{j=i}^n[d\mid(i\oplus j)]$。对右边的求和符号差分一下，然后对上界的每个二进制下为 $1$ 的位求出如果 $j$ 在这一位及更高位都和上界一致且低位随便放的答案，显然这对应了一段区间，直接算即可。

时间复杂度显然为 $O(n\log^2n+n\log k)$。

```cpp
void solve(){
    cin>>n>>k;
    Z ans=0;
    per(i,n,1){
        f[i]=0;
        auto calc=[&](int l,int r){return l?r/i-(l-1)/i:r/i+1;};
        rep(j,1,n/i){
            int v=i*j,lim=n+1;
            per(k,18,0)if(lim>>k&1){
                int l=v>>k<<k,r=l+(1<<k)-1;
                f[i]+=calc(l,r),v^=1<<k;
            }
            v=i*j,lim=v;
            per(k,18,0)if(lim>>k&1){
                int l=v>>k<<k,r=l+(1<<k)-1;
                f[i]-=calc(l,r),v^=1<<k;
            }
        }
        rep(j,2,n/i)f[i]-=f[i*j];
        ans+=f[i]*(Z(i)^k);
    }
    cout<<ans<<'\n';
}
```

---

## 作者：masterhuang (赞：8)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17773631.html)！第 $20$ 篇。

记 $ans$ 表示最终答案。

$$
\begin{aligned}
ans&=\sum\limits_{i=1}^n\sum\limits_{j=i}^n (i,i\ \text{xor}\ j)^k
\\
&=\sum\limits_{i=1}^n\sum\limits_{d\mid i}d^k\sum\limits_{j=i}^n[(i,i\ \text{xor}\ j)=d]
\\
&=\sum\limits_{i=1}^n\sum\limits_{d\mid i}d^k\sum\limits_{j=i}^n\sum\limits_{dD\mid i,dD\mid i\ \text{xor}\ j,i\le j\le n}\mu(D)
\\
&=\sum\limits_{T=1}^n \left(\sum\limits_{d\mid T}d^k\mu(T/d)\right)\sum\limits_{T\mid i}\sum\limits_{j=i}^n[T\mid (i\ \text{xor}\ j)]
\end{aligned}
$$

此时注意到 $j\in[i,n],i\ \text{xor}\ j$ 显然能被分成 $\log$ 段区间，再加上调和级数的 $\ln$，后半部分的复杂度是 $O(n\ln n\log n)$。

至于 $f(T)=\sum\limits_{d\mid T}d^k\mu(T/d)$ 部分，为了避免 $\log k$ 的出现，可以线性筛 $O(n)$ 预处理 $1^k,2^k,\cdots ,n^k$。

此时前半部分计算的复杂度就是调和级数的 $O(n\ln n)$。

于是复杂度 $O(n\log^2 n)$，常数别写太劣就能过。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=2e5+5,mod=1e9+7;
int T,n,k,pr[N],mu[N],pw[N],s;bool v[N];
basic_string<int>d[N];
inline int md(int x){return x>=mod?x-mod:x;}
inline int ksm(int x,int p){int s=1;for(;p;(p&1)&&(s=1ll*s*x%mod),x=1ll*x*x%mod,p>>=1);return s;}
inline void init(int M)
{
    for(int i=2;i<=M;i++)
    {
        if(!v[i]) pr[++pr[0]]=i,mu[i]=-1;
        for(int j=1;j<=pr[0]&&i*pr[j]<=M;j++)
        {
            v[i*pr[j]]=1;if(i%pr[j]==0) break;
            mu[i*pr[j]]=-mu[i];
        }
    }mu[1]=1;
    for(int i=1;i<=M;i++) for(int j=i;j<=M;j+=i) d[j]+=i; 
}//预处理 mu 以及因子
inline void ipw(int M)
{
    pr[0]=0;
    for(int i=2;i<=M;i++)
    {
        if(!v[i]) pr[++pr[0]]=i,pw[i]=ksm(i,k);
        for(int j=1;j<=pr[0]&&i*pr[j]<=M;j++)
        {
            v[i*pr[j]]=1;pw[i*pr[j]]=1ll*pw[i]*pw[pr[j]]%mod;
            if(i%pr[j]==0) break;
        }
    }pw[1]=1;
}//O(nln k/ln n) 预处理 1^k,2^k,...,n^k
inline int get(int l,int r,int d){return r/d+1-((l>0)?(l-1)/d+1:0);}
void dfs(int l,int r,int L,int R,int x)
{
    if(L<=l&&r<=R)
    {
        int t=__lg((l^r)+1),y=(L^l)>>t<<t;
        s=md(s+get(y,y+(1<<t)-1,x)); return;
    }int mid=(l+r)>>1;
    if(L<=mid) dfs(l,mid,L,R,x);
    if(mid<R) dfs(mid+1,r,L,R,x);
}//拆成 log 段区间算后半部分贡献
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>T;init(N-5);
    while(T--)
    {
        cin>>n>>k;ipw(n);int ans=0,U=1<<(__lg(n)+1);
        for(int i=1;i<=n;i++)
        {
            int A=0;s=0;
            for(int j:d[i]) A=(A+1ll*pw[j]*(mod+mu[i/j]))%mod;//前半部分直接枚举
            for(int j=i;j<=n;j+=i) dfs(0,U-1,j,n,i);ans=(ans+1ll*A*s)%mod;//后半部分
        }cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：5)

怎么感觉题解做法都这么神秘。个人认为这是最明显的思路。

### Solution

$$\begin{aligned}
&\sum_{i=1}^n\sum_{j=1}^i\gcd(j,i\oplus j)^k\\
=&\sum_{j=1}^n\sum_{i=j}^n\gcd(j,i\oplus j)^k\\
=&\sum_{j=1}^n\sum_{i=0}^m\gcd(i,j)^k[j\le i\oplus j\le n]\\
=&\sum_{j=1}^n\sum_{i=0}^m\gcd(i,j)^k([i\oplus j\le n]-[i\oplus j\le j-1])
\end{aligned}$$

其中 $m=2^{\lfloor\log_2n\rfloor+1}-1$。

有经典结论：对于一个 $x$，满足 $x\oplus i\le n$ 的 $i$ 形成的区间是 $O(\log n)$ 个的。证明可以使用 Trie 从上往下考虑。

设一个区间为 $[l,r]$，显然可以一步差分转化为 $[1,r]-[1,l-1]$。接下来我们考虑求出 $f(x,n)=\sum_{i=1}^n\gcd(x,i)^k$。

$$\begin{aligned}
&\sum_{i=1}^n\gcd(x,i)^k\\
=&\sum_{d|x}d^k\sum_{j=1}^{\lfloor\frac nd\rfloor}[\gcd(\frac xd,i)=1]\\
=&\sum_{d|x}d^k\sum_{t|\frac xd}\mu(t)\lfloor\frac n{dt}\rfloor\\
=&\sum_{T|x}\lfloor\frac nT\rfloor\sum_{d|T}d^k\mu(\frac Td)
\end{aligned}$$

$\sum_{d|T}d^k\mu(\frac Td)$ 显然可以直接预处理，计算答案时直接对于 $x$ 的每个约数算即可，这是 $n\ln n$ 的。

总的时间复杂度是 $O(n\ln n\log n)$。

### Code

因为之前用 vector 存每个数的约数被制裁了，所以写了 dfs 的写法。

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
constexpr int N=2e5+5,mod=1e9+7;
int n,m,k,val;
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
int p[N],plen,mu[N],lpf[N];bool v[N];
void sieve(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!v[i])p[++plen]=i,mu[i]=mod-1,lpf[i]=i;
		for(int j=1;i*p[j]<=n;j++){
			v[i*p[j]]=1;
			lpf[i*p[j]]=p[j];
			if(i%p[j]==0)break;
			mu[i*p[j]]=(mod-mu[i])%mod;
		}
	}
}
int X,prm[N],cnt[N],tot,dvs[N],len;
ll g[N];
void dfs(int x,ll cur){
	if(x==tot+1){
		dvs[++len]=cur;
		return;
	}
	for(int i=0;i<=cnt[x];i++,cur*=prm[x])
		dfs(x+1,cur);
}
void init(int x){
	tot=len=0;X=x;
	for(;x>1;x/=lpf[x]){
		if(prm[tot]!=lpf[x])
			prm[++tot]=lpf[x],cnt[tot]=1;
		else
			++cnt[tot];
	}
	dfs(1,1);
}
ll ask(int n){ // sum_{1<=i<=n} gcd(x,i)^k
	ll res=0;
	for(int i=1;i<=len;i++)
		res=(res+(n/dvs[i])*g[dvs[i]])%mod;
	return res;
}
ll f(int l,int r){
	if(!l&&!r)return qpow(X,k);
	else if(!l)return (qpow(X,k)+ask(r))%mod;
	else if(l==1)return ask(r);
	else return (ask(r)-ask(l-1)+mod)%mod;
}
ll get(int v,int n){ // sum_i f(i)*[i xor v <= n]
	ll res=0;
	for(int i=m;i>=0;i--)
		if(n>>i&1)
			res=(res+f(v&~((1<<i)-1),v|((1<<i)-1)))%mod,v^=1<<i;
	return (res+f(v,v))%mod;
}
void conv(){
	for(int i=1;i<=n;i++)g[i]=0;
	for(int i=1;i<=n;i++){
		ll v=qpow(i,k);
		for(int j=1;i*j<=n;j++)
			g[i*j]=(g[i*j]+v*mu[j])%mod;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _Test;cin>>_Test;
	sieve(2e5);
	while(_Test--){
		cin>>n>>k;m=__lg(n);
		conv();
		ll ans=0;
		for(int i=1;i<=n;i++){
			init(i);
			ans=(ans+get(i,n)-get(i,i-1)+mod)%mod;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Transfixion_ (赞：5)

题目链接：[$\texttt{Link}$](https://www.luogu.com.cn/problem/P10855)

比赛当天去数竞了没打，赛后写了 Trie 做法，个人认为和现有题解相比对位运算技巧的要求更低。

## $\textbf{Solution}$

首先答案为

$$\sum_{i=1}^n\sum_{j=1}^i\gcd(i,i\oplus j)^k$$

莫反部分比较简单，可以参考其他莫反的题解。推一下式子得到的结果是：

$$\sum_{T=1}^n\sum_{d|T}d^k\mu(T/d)\sum_{T|i,1\le i\le n}\sum_{j=i}^n[T\mid (i\oplus j)]$$

记

$$f(T)=\sum_{d|T}d^k\mu(T/d)\\g(T)=\sum_{T|i,1\le i\le n}\sum_{j=i}^n[T\mid (i\oplus j)]$$

则答案即为 $\sum_{T=1}^nf(T)g(T)$。

$f(T)$ 是容易的。线筛 $\mu$ 可以做到 $\mathcal O(\log n\log k)$，线筛自然数幂可以去掉 $\log k$。实际表现没有区别。

问题在于如何计算 $g(T)$。暴力算 $g(T)$ 只有暴力分，[Submission](https://www.luogu.com.cn/record/171885857)。

交换求和符号的条件和贡献（以下推导省略第一个 $\sum$ 的条件）：

$$\begin{aligned}g(T)&=\sum_{i}\sum_{T\mid (i\oplus j)}[i\le j\le n]\\&=\sum_{i}\sum_{k\ge 0}[i\le i\oplus kT\le n]\end{aligned}$$

暴力求这个式子可以拿比暴力高一点的分，[Submission](https://www.luogu.com.cn/record/171887876)。

枚举 $i$。把后面那个 $\sum$ 差分掉，写成普遍形式：给定 $T$、常数 $x$ 和上界 $y$，求 $\sum_{k\ge 0}[kT\oplus x\le y]$。

如果你对位运算技巧比较熟练，到这里就可以直接算了。对于位运算苦手的我来说，直接计算有点困难。

考虑对每个 $T$ 建一棵 Trie，因为 $kT$ 实质上是两个 $\le n$ 的正整数的异或和，所以要插入 $[0,2^{18}-1]$ 内的所有 $kT$。建 Trie 总时间复杂度 $\mathcal O(n\log^2 n)$。

则所求即为 Trie 内异或上 $x$ 后 $<y+1$ 的数的个数，可以 $\mathcal O(\log n)$ 直接算，具体实现参考代码。于是计算 $g(T)$ 的复杂度降至 $\mathcal O(\log^2n)$。

总时间复杂度 $\mathcal O(n\log^2n)$，可以通过本题。预处理比较慢，喜提最优解倒数，[Submission](https://www.luogu.com.cn/record/171917519)。

## $\textbf{AC Code}$

```cpp
#include <bits/stdc++.h>
#define gc() (iS == iT && (iT = (iS = buf) + fread(buf, 1, 1 << 20, stdin), iS == iT) ? EOF : *iS++)
char buf[1 << 20], *iS = buf, *iT = buf;
template <typename _Tp> inline void read(_Tp& x) {
	x = 0; char c = gc(); bool f = 0;
	for(; !std::isdigit(c); c = gc()) f |= c == '-';
	for(; std::isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c ^ 48);
	f ? x = ~x + 1 : 1;
}
template <> inline void read(std::string& x) {
	x.clear(); char c = gc();
	for(; !std::isgraph(c); c = gc());
	for(; std::isgraph(c); c = gc()) x += c;
}
template <typename _Tp, typename ...Args> 
inline void read(_Tp& x, Args& ...args) {
	read(x), read(args...);
}
typedef long long i64;
constexpr int mod = 1e9 + 7;
constexpr int N = 2e5 + 5;
constexpr int M = 36103793 + 5;
inline void inc(int& x, int y) { (x += y) >= mod && (x -= mod); }
inline void dec(int& x, int y) { (x += mod - y) >= mod && (x -= mod); }
inline int add(int x, int y) { inc(x, y); return x; }
inline int sub(int x, int y) { dec(x, y); return x; }
inline int qpow(int a, int b) { int res = 1; for(; b; b >>= 1, a = 1ll * a * a % mod) if(b & 1) res = 1ll * res * a % mod; return res; }
int T, n, k, mu[N], pr[N], pw[N];
std::bitset<N> isp;
std::vector<int> fac[N];

inline void sieve(int n) {
	isp.set();
	isp[0] = isp[1] = 0, mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(isp[i]) pr[++*pr] = i, mu[i] = mod - 1;
		for(int j = 1; j <= *pr && 1ll * i * pr[j] <= n; j++) {
			isp[i * pr[j]] = 0;
			if(i % pr[j] == 0) {
				mu[i * pr[j]] = 0;
				break;
			} else mu[i * pr[j]] = mod - mu[i];
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i; j <= n; j += i) {
			fac[j].emplace_back(i);
		}
	}
}

inline void getpow(int n, int k) {
	isp.set();
	*pr = isp[0] = isp[1] = 0;
	pw[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(isp[i]) pw[i] = qpow(i, k);
		for(int j = 1; j <= *pr && 1ll * i * pr[j] <= n; j++) {
			isp[i * pr[j]] = 0;
			pw[i * pr[j]] = 1ll * pw[i] * pw[pr[j]] % mod;
			if(i % pr[j] == 0) break;
		}
	}
}

int totT, son[M][2], siz[M];
struct Trie {
	int rt;
	inline void insert(int x) {
		int p = rt;
		siz[p]++;
		for(int i = 17; ~i; i--) {
			int c = x >> i & 1;
			if(!son[p][c]) son[p][c] = ++totT;
			siz[p = son[p][c]]++;
		}		
	}
	inline int query(int x, int y) {
		y++;
		int p = rt, res = 0;
		for(int i = 17; ~i; i--) {
			int c = x >> i & 1;
			if(y >> i & 1) {
				res += siz[son[p][c]];
				p = son[p][c ^ 1];
			} else p = son[p][c];
			if(!p) {
				res += siz[p];
				break;
			}
		}
		return res;
	} // sum [x xor _ <= y]
} tr[N];

inline void build(int n) {
	for(int i = 1; i <= n; i++) tr[i].rt = ++totT;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < (1 << 18); j += i) {
			tr[i].insert(j);
		}
	}
}

inline void solve() {
	int ans = 0;
	read(n, k), getpow(n, k);
	for(int T = 1; T <= n; T++) {
		int fT = 0, gT = 0;
		for(auto& d : fac[T]) inc(fT, 1ll * pw[d] * mu[T / d] % mod);
		for(int i = T; i <= n; i += T) {
			inc(gT, tr[T].query(i, n));
			dec(gT, tr[T].query(i, i - 1));
		}
		inc(ans, 1ll * fT * gT % mod);
	}
	printf("%d\n", ans);
}

signed main() {
	sieve(N - 5), build(N - 5);
	for(read(T); T--; ) solve();	
	return 0;
}
```

---

## 作者：SmileMask (赞：5)

**这是一篇不需要莫比乌斯反演的题解。**

不妨将题目中要求的式子化简。
$$
\begin{equation}
\begin{split}
\sum\limits_{i=1}^n\sum\limits_{j=1}^i \gcd(j,i\oplus j)^k&= \sum\limits_{j=1}^n\sum\limits_{i=j}^n \gcd(j,i\oplus j)^k\\
&=\sum\limits_{j=1}^n\sum\limits_{x=1}^{\min(2^{18}-1,2n)} \gcd(j,x)^k[j\le x\oplus j \le n] \\

&=\sum\limits_{d=1}^nd^k\sum\limits_{j=1}^ n\sum\limits_{x=1}^{\min(2^{18}-1,2n)} [d\mid j][d\mid x][j\le x\oplus j \le n] \\
\end{split}
\end{equation}
$$
不妨记 $f_d$ 为 $\sum\limits_{j=1}^ n\sum\limits_{x=1}^{\min(2^{18}-1,2n)} [d\mid j][d\mid x][j\le x\oplus j \le n] $，本质上表示合法的 $d\mid \gcd(j,x)$  的数量，记 $g_d$ 为合法的 $d=\gcd(j,x)$ 的数量，有 $g_d=f_d-\sum\limits_{i=1}^n g_i[d\mid i]$。

考虑如何计算 $f_d$ ，有异或操作通常在 Trie 上进行操作，将所有合法的 $x$ 加入 Trie 中，将 $[j\le x\oplus j \le n]$ 差分，只统计 $[x\oplus j \le r]$ 两遍即可，而这是较为容易的，具体见代码。

总复杂度为 $
\mathcal{O}(\sum\limits_{i=1}^n \frac{n}{i}\times \log n)=
\mathcal{O}(n\log^2n)$，可以通过此题。
```
const int mod=1e9+7;
const int N=4e5+10;
const int M=(1<<18)-1;

int n,k,ans,f[N];
int ch[N*2][2],cnt[N*2],tot=1;

void Add(int &x,int y){
	x+=y;if(x>=mod) x-=mod;
}

int qmi(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}
	return res;
}

void Main(){
	n=rd,k=rd,tot=1,ans=0;
	for(int i=1;i<=n;i++) f[i]=0;
	for(int i=n;i>=1;i--){
		for(int j=0;j<=min(M,2*n);j+=i){
			int u=1;
			for(int k=17;~k;k--){
				if(!ch[u][j>>k&1]) ch[u][j>>k&1]=++tot;
				u=ch[u][j>>k&1],cnt[u]++;
			}
		}
		for(int j=i;j<=n;j+=i){
			int u=1;
			for(int k=17;(~k)&&u;k--){
				if(n>>k&1) Add(f[i],cnt[ch[u][j>>k&1]]);
				u=ch[u][(j>>k&1)^(n>>k&1)];
			}Add(f[i],cnt[u]);
			u=1;
			for(int k=17;(~k)&&u;k--){
				if((j-1)>>k&1) Add(f[i],mod-cnt[ch[u][j>>k&1]]);
				u=ch[u][((j-1)>>k&1)^(j>>k&1)];
			}Add(f[i],mod-cnt[u]);
		}
		for(int j=i*2;j<=n;j+=i)
			Add(f[i],mod-f[j]);
		Add(ans,1ll*qmi(i,k)*f[i]%mod);
		for(int j=0,u=1;j<=min(M,2*n);j+=i,u=1)
			for(int k=17;~k;k--)
				u=ch[u][j>>k&1],cnt[u]--;
	}
	printf("%d\n",ans);
	for(int i=1;i<=tot;i++) 
		ch[i][0]=ch[i][1]=cnt[i]=0;
}
```

---

## 作者：xhgua (赞：5)

考虑枚举 $\gcd$，答案即为：

$$
\sum\limits_{g = 1} ^ n g^k\sum\limits_{x = 1}^{n}\sum\limits_{i = 1}^{x}[\gcd(i, i\oplus x) = g]
$$
调换求和顺序，枚举 $i$ 为 $g$ 的倍数得到：

$$
\begin{aligned}
&\sum\limits_{g = 1} ^ n g^k\sum\limits_{i = 1}^{\lfloor \frac{n}{g}\rfloor}\sum\limits_{x = ig}^{n}[\gcd(ig, ig\oplus x) = g]\\
=&\sum\limits_{g = 1} ^ n g^k\sum\limits_{i = 1}^{\lfloor \frac{n}{g}\rfloor}\sum\limits_{x = ig}^{n}[g \mid ig\oplus x][\gcd(i, \frac{ig\oplus x}{g}) = 1]
\end{aligned}
$$

上莫反，得：

$$
\begin{aligned}
&\sum\limits_{g = 1} ^ n g^k\sum\limits_{i = 1}^{\lfloor \frac{n}{g}\rfloor}\sum\limits_{x = ig}^{n}[g \mid ig\oplus x]\sum\limits_d [d \mid i][d \mid \frac{ig\oplus x}{g}]\mu(d)\\
=&\sum\limits_{g = 1} ^ n g^k\sum\limits_{d = 1}^{\lfloor\frac{n}{g}\rfloor}\mu(d)\sum\limits_{i = 1}^{\lfloor \frac{n}{gd}\rfloor}\sum\limits_{x = ig}^{n}[gd \mid igd\oplus x]
\end{aligned}
$$

令 $T = gd$，枚举 $T$ 得：

$$
\begin{aligned}
&\sum\limits_{g = 1} ^ n g^k\sum\limits_{d = 1}^{\lfloor\frac{n}{g}\rfloor}\mu(d)\sum\limits_{i = 1}^{\lfloor \frac{n}{T}\rfloor}\sum\limits_{x = iT}^{n}[T \mid iT\oplus x] \\
=&\sum\limits_{T = 1} ^ n \sum\limits_{g \mid T} g^k\mu(\frac{T}{g})\sum\limits_{i = 1}^{\lfloor \frac{n}{T}\rfloor}\sum\limits_{x = iT}^{n}[T \mid iT\oplus x]
\end{aligned}
$$

记 $\displaystyle f(T) = \sum\limits_{g \mid T} g^k\mu(\frac{T}{g}), g(i, T) = \sum\limits_{x = iT}^{n}[T \mid iT\oplus x]$，于是答案为：

$$
\sum\limits_{T = 1} ^ n f(T)\sum\limits_{i = 1}^{\lfloor \frac{n}{T}\rfloor}g(i, T)
$$

$f(T)$ 可以简单预处理出来，问题在于如何快速求 $g(i, T)$。

先将 $g$ 做个变形：$\displaystyle g(i, T) = \sum\limits_{x}[iT\leq x\leq n][T\mid iT\oplus x]$，我们考虑如何计算满足条件的 $x$ 个数。

前面的东西可以拆成两个前缀相减，于是我们只用解决如何计算 $\displaystyle \sum\limits_{x = 1}^n[T\mid iT\oplus x]$。

我们考虑对 $n$ 做类似数位 dp 的东西，枚举当前位 $b$，发现当 $n$ 二进制下第 $b$ 位为 $1$ 时，我们往 $x$ 这一位填 $0$，前面的几位和 $n$ 保持一致（记当前形成的数为 $c$），此时后面的位置可以随便填，也就是合法的 $x$ 形成了一段 $[c, c + 2 ^ {b})$ 的区间，此时我们将其异或上 $iT$ 后，得到的还是一段长度为 $2 ^ {b}$ 的连续区间，然后就可以 $\mathcal{O}(1)$ 计算出该连续区间内有多少 $T$ 的倍数。

加上外层的调和级数枚举，总时间复杂度为 $\mathcal{O}(n\ln n\log n)$。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 5;

using Z = ModInt<(int)1e9 + 7>;

int T, n, k, tot, prime[N], mu[N];
bool isp[N];
std::vector<int> d[N];
Z F[N], pw[N];

void sieve(int n) {
	memset(isp, true, sizeof(isp));
	isp[0] = isp[1] = false; mu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (isp[i]) prime[++tot] = i, mu[i] = -1;
		for (int j = 1; j <= tot && 1ll * i * prime[j] <= n; j++) {
			int p = prime[j]; isp[i * p] = false;
			if (i % p == 0) {
				mu[i * p] = 0;
				break;	
			}
			else mu[i * p] = -mu[i];
		}
	}
	for (int i = 1; i <= n; i++) pw[i] = power(Z(i), k);
	for (int i = 1; i <= n; i++) {
		F[i] = 0;
		for (auto g : d[i]) F[i] += pw[g] * mu[i / g];
	}
}

int calc(int l, int r, int x) {
	if (l == 0) return r / x + 1;
	return r / x - (l - 1) / x;
}

Z G(int n, int i, int T) {
	int a = i * T;
	Z ret = ((n ^ a) % T == 0);
	for (int i = 18; i >= 0; i--) if (n >> i & 1) {
		int c = (n >> (i + 1) << (i + 1)), d = (a >> i << i), e = c ^ d;
		ret += calc(e, e + (1 << i) - 1, T);
	}
	return ret;
}

void solve() {
	std::cin >> n >> k; sieve(n);

	Z ans = 0;
	for (int T = 1; T <= n; T++) {
		Z res = 0;
		for (int i = 1; i <= n / T; i++) res += G(n, i, T) - G(i * T - 1, i, T);
		ans += F[T] * res;
	}
	std::cout << ans << "\n";
}

int main() {

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	for (int i = 1; i < N; i++) for (int j = i; j < N; j += i) d[j].push_back(i);

	std::cin >> T;
	while (T--) solve();

	return 0;
}
```

---

## 作者：Luciylove (赞：4)

不是，哥们，这个题为啥要观察啊？

考虑算出每一个对子 $\gcd(i, i\oplus x) = d$ 的个数，然后直接快速幂，但是想要直接地知道这个对子疑似有点难了。考虑经典套路，**高维差分**，考虑算出对子 $d \mid \gcd(i, i \oplus x)$ 的数量。然后逆向地狄利克雷前缀和即可。

然后现在就只需要知道上面那个对子的数量，然后我们经典调和级数枚举 $d$ 的所有倍数，然后就可以转化为对于：$S = \{x \mid (d \mid x)\}$ 的计数问题。

考虑枚举 $i, i \oplus x = t$，那么只需要对于这个集合计数：$x, y \in S, n \geq x \oplus y \geq x$ 的 $(x, y)$ 数量就好了。

这个东西不难使用 01Trie 维护。

复杂度：$O(n \ln n \log V)$。

代码找我要。

---

## 作者：luckydrawbox (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/P10855)

## 题意

求 $\sum_{x=1}^n\sum_{i=1}^x\gcd(i,i\oplus x)^k$ 对 $10^9+7$ 取模的结果。

## 分析

既然 $O(n\log^2 n)$ 的做法已经被说烂了，那我就来一个更烂的 $O(n\log^3n)$ 的做法。

令 $n$ 二进制下的最高位为 $tn$，$n2=2^{tn+1}$。

直接开始推式子，$\gcd^k$ 显然拆不开，考虑枚举它：

$$=\sum_{d=1}^nd^k\sum_{x=1}^n\sum_{i=1}^x[\gcd(i,i\oplus x)=d]$$
$$=\sum_{d=1}^nd^k(1+\sum_{i=1}^n\sum_{j=1}^{n2}[\gcd(i,j)=d\land i\le i\oplus j\le n])$$

多出来的 $1$ 是 $j=0$ 的情况。

接着考虑处理条件 $i\le i\oplus j=x$，由于 $j\neq 0$，所以 $i<x$。

不放设 $i$ 与 $x$ 第 $t+1\sim tn$ 位均相同，第 $t$ 位时 $i_t=0,x_t=1$，那么就有 $j_t=1$ 且 $j_{t+1\sim tn}=0$。也就是说当且仅当 $i_t=0$，$t$ 为 $j$  的最高位时 $i<x$！于是令 $U_t$ 表示 $\{i|i_t=0\land i\le n\}$，$V_t$ 表示 $\{j|j_t=1\land 2^{t+1}>j\land j\le n2\}$，那么答案为：

$$\sum_{d=1}^nd^k(1+\sum_{t=0}^{tn}\sum_{i\in U_t}\sum_{j\in V_{t}}[\gcd(i,j)=d\land i\oplus j\le n])$$

令 $f(p)=\sum_{t=0}^{tn}\sum_{i\in U_t\land p|i}\sum_{j\in V_{t}\land p|j}[i\oplus j\le n]$，显然这个东西可以在 $\texttt{Trie}$ 树上预处理出来，均摊后总复杂度为 $O(tn^2 n\log n)$ 。

接着对 $[\gcd(i,j)=d]$ 进行莫比乌斯反演：

$$\sum_{d=1}^nd^k(1+\sum_{c=1}^{n/d}\mu(c) f(cd))$$

这部分计算的复杂度是 $O(n\log n)$ 的，总复杂度大概为 $O(n\log ^3n)$，看起来十分过不了，然而给出的数的值是连续的，所以其在 $U,V$ 中的分布是均匀的，~~只要大力卡常~~就能在单点大约 $\texttt{980ms}$ 内通过。~~别缩短时限啊qwq~~

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std; 
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();} 
	return x*f;
}
void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const int N=(1<<18)+10,M=19;
const ll mod=1e9+7;
int T,n,k,Log[N],tn;
ll dk[N],f[N];
ll qmi(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;b>>=1;
	}
	return ans;
}
vector<int>U[M],V[M],sep[N],facu[N],facv[N];
int m,pri[N],vis[N],miu[N];
void init(int n){
	vis[1]=1;miu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			vis[i]=pri[++m]=i;
			miu[i]=-1;
		}
		for(int j=1;j<=m&&i*pri[j]<=n;j++){
			vis[i*pri[j]]=pri[j];
			miu[i*pri[j]]=miu[i]*-1;
			if(i%pri[j]==0){
				miu[i*pri[j]]=0;break;
			}
		}
	}
}
int find(int d,int x,int l,int r){
	if(facu[d][r]<x)return r+1;
	int mid;
	while(l<r){
		mid=(l+r)>>1;
		if(facu[d][mid]>=x)r=mid;
		else l=mid+1;
	}
	return l;
}
struct Trie{
	int ch[N*20][2],tot=1,p;
	int sz[N*20];
	void change(register int x,int v){
		sz[p=1]+=v;
		for(int i=tn,c;i>=0;i--){
			c=(x>>i)&1;
			if(!ch[p][c])ch[p][c]=++tot;
			p=ch[p][c];
			sz[p]+=v;
		}
	}
	void clear(){
		for(register int i=1;i<=tot;i++)ch[i][0]=ch[i][1]=0;
		tot=1;
	}
	ll ask(int p,int t,int d,int ms,int l,int r){
		if(!p||!sz[p]||l>r)return 0;
		if(t==-1){
			return 1ll*sz[p]*(r-l+1);
		}
		ll ans=0;
		int mpos=find(d,ms|(1<<t),l,r);
		if((n>>t)&1){
			if(l<=mpos-1){
				ans+=1ll*sz[ch[p][0]]*(mpos-l);
				ans+=ask(ch[p][1],t-1,d,ms,l,mpos-1);
			}
			if(mpos<=r){
				ans+=1ll*sz[ch[p][1]]*(r-mpos+1);
				ans+=ask(ch[p][0],t-1,d,ms|(1<<t),mpos,r);
			}
		}
		else{
			ans+=ask(ch[p][0],t-1,d,ms,l,mpos-1);
			ans+=ask(ch[p][1],t-1,d,ms|(1<<t),mpos,r);
		}
		return ans;
	}
}tr;
void solve(){
	tn=Log[n];int n2=(1<<tn+1);
	for(register int t=0;t<=tn;t++){
		U[t].clear();V[t].clear(); 
		for(register int i=1;i<=n;i++){
			if(!((i>>t)&1))
				U[t].push_back(i);
		}
	}
	for(register int i=1,j,tc;i<n2;i++){
		j=i;tc=-1;
		while(j)j>>=1,tc++;
		V[tc].push_back(i);
	}
	for(register int i=1;i<=n;i++){
		dk[i]=qmi(i,k);
		f[i]=0;
	}
	for(register int t=0;t<=tn;t++){
		for(register int i=1;i<=n;i++){
			facu[i].clear();
			facv[i].clear();
		}
		for(register auto x:U[t]){
			for(register auto p:sep[x])
				facu[p].push_back(x);
		}
		for(register auto x:V[t]){
			for(register auto p:sep[x])
				facv[p].push_back(x);
		}
		for(register int d=1;d<=n;d++){
			for(register auto x:facv[d])
				tr.change(x,1);
			f[d]=(f[d]+tr.ask(1,tn,d,0,0,facu[d].size()-1))%mod;
			for(register auto x:facv[d])
				tr.change(x,-1);
		}
	}
	ll ans=0,res;
	for(register int d=1;d<=n;d++){
		res=1;
		for(register int c=1;c<=n/d;c++)
			res+=miu[c]*f[c*d];
		ans=(ans+dk[d]*res%mod);
	}
	ans=(ans%mod+mod)%mod;
	write(ans);putchar('\n');
}
int main(){
	T=read();
	Log[0]=-1;
	for(register int i=1;i<N;i++)Log[i]=Log[i>>1]+1;
	for(register int i=1;i<N;i++){
		for(register int j=1;j*j<=i;j++){
			if(i%j==0){
				sep[i].push_back(j);
				if(j*j!=i)
					sep[i].push_back(i/j);
			}
		}
	}
	init(N-5);
	while(T--){
		tr.clear();
		n=read();k=read();
		solve();
	}
	return 0;
}
```

---

## 作者：Presentation_Emitter (赞：2)

这里给出一个（可能）比较好想但是略难实现的做法。

要求的式子可以这样转化（$[p]$ 为艾弗森括号，其值在 $p$ 成立时为 $1$，不成立时为 $0$，其中 $p$ 为一个命题）：

$$
\begin{aligned}
&\sum\limits_{i=1}^n\sum\limits_{j=1}^i \gcd(j,j \oplus i)^{k}\\
=&\sum\limits_{j=1}^n\sum\limits_{i=j}^n \gcd(j,j \oplus i)^{k}\\
=&\sum\limits_{j=1}^n\sum\limits_{i=j}^n \gcd(j,j \oplus i)^{k}\\
=&\sum\limits_{j=1}^n\sum\limits_{i \ge 0} \gcd(j,i)^{k}[j \le i \oplus j \le n]
\end{aligned}
$$

注意到可以对每个 $d$ 求出 $\sum\limits_{j=1}^n\sum\limits_{i \ge 0} [(d |\gcd(j,i)) \land (j \le i \oplus j \le n)]$ 的值然后容斥算出答案，于是可以首先枚举一个 $j$，再枚举 $j$ 的因子 $d$，然后对所有 $i$ 计算上式并按 $d$ 累加。

记 $t$ 为 $n$ 在二进制表示下的最高位位置，并令 $m=2^t$。我们把 $i,j$ 按照是否 $<m$ 分成四类并分别计算。

### 1. $i,j<m$

此时 $i \oplus j \le n$ 的限制必定满足，于是我们只需要求 $\sum\limits_{i=0}^{m-1}[(d | i) \land (j \le i \oplus j)]$。对于 $i > 0$ 的情况，考虑 $i$ 的二进制下最高位，它必定满足 $j$ 的对应二进制位为 $0$，于是只需要枚举 $j$ 中所有 $0$ 的位置并计算贡献。最后算上 $i=0$ 的情况。

### 2. $j<m$，$i \ge m$

此时 $j \le i \oplus j$ 的限制必定满足，考虑类似数位 dp 的过程，对于 $i<n$ 的情况，枚举 $n$ 在二进制下的某一位，钦定 $i$ 在这一位与 $n \oplus j$ 不同，更高的位置与 $n \oplus j$ 相同。如果 $n$ 在这一位上为 $1$，那么 $i \oplus j$ 在这一位上为 $0$，于是更低位就可以任意填。最后算上 $i=n$ 的情况。

### 3. $i,j \ge m$

此时 $j \le i \oplus j$ 的限制必定不满足，贡献为 $0$。

### 4. $i<m$，$j \ge m$

可以把原本的限制条件转为 $[j \le i \oplus j]-[n < i \oplus j]$，于是 $j<m$ 时的两种做法可以分别解决这两个条件。

注意到枚举因子的复杂度是 $T(n)=\sum\limits_{k=1}^{n}\lfloor\frac{n}{k}\rfloor=\Theta(n \log n)$，于是总时间复杂度为 $\Theta(n (\log n)^2)$。

[Code](https://oier.team/record/66b7312ce8c4e274b2018a42)

---

## 作者：LKY928261 (赞：2)

说句闲话，我场上摁推莫反硬控自己 3 小时，赛后看到是蓝题才意识到还有简单做法/hsh

以下是使用了莫反的赛时做法，供大家参考。

### Solution

记答案为 $S$。

看到 $\gcd$ 就先莫比乌斯反演把它干掉：

$$
\begin{aligned}
S&=\sum_{i=1}^{n}\sum_{j=1}^{i}\gcd(j,j\operatorname{xor}i)^k\\
&=\sum_{t=1}^{n}t^k\sum_{i=1}^{n}\sum_{j=i}^{n}[\gcd(i,i\operatorname{xor}j)=t]\\
&=\sum_{t=1}^{n}t^k\sum_{t\mid i,1\le i\le n}\ \sum_{t\mid(i\operatorname{xor}j),i\le j\le n}[\gcd(\frac{i}{t},\frac{i\operatorname{xor}j}{t})=1]\\
&=\sum_{t=1}^{n}t^k\sum_{t\mid i,1\le i\le n}\ \sum_{t\mid(i\operatorname{xor}j),i\le j\le n}\ \sum_{d\mid\gcd(\frac{i}{t},\frac{i\operatorname{xor}j}{t})}\mu(d)\\
&=\sum_{d=1}^{n}\mu(d)\sum_{t=1}^{n}t^k\sum_{td\mid i,1\le i\le n}\sum_{j=i}^{n}[td\mid(i\operatorname{xor}j)]\\
&=\sum_{g=1}^{n}\left(\sum_{d\mid g}\mu(d)\cdot\left(\frac{g}{d}\right)^k\right)\sum_{g\mid i,1\le i\le n}\sum_{j=i}^{n}[g\mid(i\operatorname{xor}j)]
\end{aligned}
$$

记 $a_g=\sum_{d\mid g}\mu(d)\cdot\left(\frac{g}{d}\right)^k$，这一部分可以直接 $\mathcal{O}(n\ln n)$ 预处理。

对于剩下的部分，令 $x=i\operatorname{xor}j$，则：

$$
\begin{aligned}
S&=\sum_{g=1}^{n}a_g\sum_{g\mid i,1\le i\le n}\sum_{j=i}^{n}[g\mid x]\\
&=\sum_{g=1}^{n}a_g\sum_{g\mid i,1\le i\le n}\sum_{g\mid x}[i\le(i\operatorname{xor}x)\le n]
\end{aligned}
$$

设 $f(n,i,g)=\sum_{g\mid x}[(i\operatorname{xor}x)\le n]$，那么：

$$
S=\sum_{g=1}^{n}a_g\sum_{g\mid i,1\le i\le n}(f(n,i,g)-f(i-1,i,g))
$$

对于快速求 $f(n,i,g)$，可以把区间 $[0,n]$ 拆成不超过 $\log$ 段形如 $[x,x+2^k)$ 的区间，其中 $2^k\le\text{lowbit}(x)$。对于每段区间，其整体异或一个数后得到的依然是一段区间，对每段区间求出其中 $g$ 的倍数的个数再求和即可。

前面枚举 $g,i$ 的部分是调和级数 $\mathcal{O}(n\ln n)$，单次计算 $f(n,i,g)$ 可以 $\mathcal{O}(\log n)$ 解决，总时间复杂度 $\mathcal{O}(n\ln n\log n)$，足够通过本题。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=2e5+5,M=1e9+7;
inline ll qp(ll x,ll y){ll z=1;for(;y;y>>=1,x=x*x%M)if(y&1)z=z*x%M;return z;}
ll N,n,m,k,x,s,a[_],T,prm[_],mu[_],i,j;bool f[_];
inline ll p(ll n,ll k){
	ll t=0,x,i;
	for(i=0;n;i++)if((n>>i)&1){
		x=(n-1)^k;x-=x&((1<<i)-1);
		t+=(x+(1<<i)-1)/j-(x+j-1)/j+1;
		n^=(1<<i);
	}
	return t;
}
inline void P(){
	cin>>n>>k;s=0;
	for(i=1;i<=n;i++)a[i]=0;
	for(i=1;i<=n;i++)for(x=qp(i,k),j=i;j<=n;j+=i)a[j]+=x*mu[j/i];
	for(i=1;i<=n;i++)a[i]=(a[i]%M+M)%M;
	for(j=1;j<=n;j++){
		for(x=0,i=j;i<=n;i+=j)(x+=p(n+1,i)-p(i,i))%=M;
		s+=x*a[j]%M;
	}
	cout<<s%M<<'\n';
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(i=mu[1]=f[0]=f[1]=1;++i<_;){
		if(!f[i])prm[T++]=i,mu[i]=-1;
		for(j=0;x=i*prm[j],j<T&&x<_;j++){
			f[x]=1;
			if(i%prm[j])mu[x]=-mu[i];
			else{mu[x]=0;break;}
		}
	}
	cin>>N;while(N--)P();
}
```

---

## 作者：Iratis (赞：1)

比 E 难，*2000

题目要求 $ \gcd^k $，显然求法是求出 $ \gcd=i $ 的个数。记 $ g_i $ 表示需要统计的 $ \gcd $ 中 $ =i $ 的个数，答案为 $ \displaystyle\sum_{i=1}^ni^kg_i $。套路的求 $ i\mid\gcd $ 的个数 $ f_i $，然后使用莫反获得 $ g $，这一步不过多阐述。

$$ f_d=\sum_{i=1}^n\sum_{j=1}^i[d\mid\gcd(j,j\oplus i)] $$

设 $ x=j\oplus i $，有 $ 1\leq j \leq i \leq n $，即 $ 1\leq j\leq (j\oplus x)\leq n $。

$$ f_d=\sum_{i=1}^n\sum_{j}^{}[d\mid\gcd(i,i\oplus j)][1\leq i \leq (i\oplus j)\leq n] $$

$$ f_d=\sum_{i=1}^n\sum_{j}^{}[d\mid i][d\mid (i\oplus j)][1\leq i \leq (i\oplus j)\leq n] $$

由于整除限制，倘如单次做到 $ O(c\times\frac{n}{d}) $，有时间复杂度 $ O(cn\ln n) $，可以接受，故考虑枚举每一个 $ d\mid i $，求有多少个 $ j $ 满足 $ 1\leq i\leq (i\oplus j)\leq n $，发现 $ j $ 的上界为 $ 2n $，考虑将他们都插入 Trie 中，每次查询在 Trie 上询问即可。

考虑具体如何实现，由 $ i\leq (i\oplus j) $ 可知，合法的 $ j $ 一定存在一段前导 0，接着的在下一位上，$ i $ 的二进制位为 $ 0 $，而 $ j $ 为 $ 1 $，所以可以枚举前缀 $ 0 $ 个数，目前常数 $ c=\log V $。

继续处理条件 $ (i\oplus j)\leq n $，而这在 Trie 树上是一个常见的套路，不过多赘述，发现此时常数 $ c=\log^2 V $，似乎过不去，笔者赛时并未尝试实现。

继续考虑分析性质，发现在大多数时候，满足第一条限制后，$ (i\oplus j)\leq n $ 都是成立的，更具体一点，只存在至多一个枚举位，使得 $ (i\oplus j) $ 并不对于所有 $ i\leq (i\oplus j) $ 的 $ j $ 成立，所以复杂度降为 $ c=\log V $。

整体时间复杂度 $ O(n \ln n \log V) $，足以通过此题。

---

