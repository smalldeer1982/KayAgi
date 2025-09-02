# Vasya and Maximum Profit

## 题目描述

有 $n$ 道题目，而我们可亲可敬的 $\tt Coin\; Collection\; Function$（下文简称 $\tt FCC$）正以极高的热情筹备着比赛！

如果 $\tt FCC$ 将第 $i$ 道题作为比赛题，$\tt FCC$ 需要支付 $c_i$ 元给工作人员。但是 $\tt FCC$ 每增加一道题，就可以获得 $a$ 元的“自愿捐助”款。

现在 $\tt FCC$ 想选择一个连续区间 $[l,r]$ 作为比赛题。

题目的难度需要相差不大，否则容易引起选手憎恨。每个题目有一个难度 $d_i$ ，$\tt FCC$ 会额外支付 $\max_{i=l}^{r-1}(d_{i+1}-d_{i})^2$ 元来堵住媒体的嘴。特别的，若 $l=r$ 则无这一笔额外款项。

$\tt FCC$ 精打细算，想要获得最多的钱。请你告诉 $\tt FCC$ ，最多能赚多少钱吧！

## 样例 #1

### 输入

```
5 10
1 15
5 3
6 11
7 2
11 22
```

### 输出

```
13
```

## 样例 #2

### 输入

```
3 5
1 8
2 19
3 11
```

### 输出

```
0
```

# 题解

## 作者：p_b_p_b (赞：6)

[$$\large \color{purple} My \; Blog$$](https://www.cnblogs.com/p-b-p-b/p/10434287.html)

--------------

### 我竟然能在有生之年踩标算！！！

----------------

## 思路

首先考虑暴力：枚举左右端点直接计算。

考虑记录$sum_x=\sum_{i=1}^x c_i$，设选$[l,r]$时那个奇怪东西的平方为$f(l,r)$，使劲推式子：

$$ans_{l,r}=(r-l+1)\times a-sum_r+sum_{l-1}-f(l,r)$$
$$ans_{l,r}+l\times a-a-sum_{l-1}=r\times a-sum_r-f(l,r)$$
$$ans_{l,r}+l\times a-a-sum_{l-1}=F_r-(\max_{i=l+1}^r\{d_{i}-d_{i-1}\})^2$$

发现左边只和$l$有关，右边只有一个$\max$较为麻烦。

考虑$\max$在左端点一定时单调上升，所以左端点每次往左移一格，只会对一小部分$r$造成影响，将他们的$\max$弄成一样的。

既然一样了，那当然可以记录一个$\max_{F_r}$，然后把它们并在一起啊。

用一个单调栈记录$r$，每次$l$往左移一位，就把一堆$r$缩在一起。

栈里每个元素也要存自己下面的$F_r-(\max_{i=l+1}^r\{d_{i}-d_{i-1}\})^2$的最大值，用来统计答案。

复杂度显然是$O(n)$的。

**我踩标算啦！**

（刚写完，过于兴奋，语无伦次，请原谅QwQ）

----------------

```cpp
#include<bits/stdc++.h>
clock_t t=clock();
namespace my_std{
	using namespace std;
	#define pii pair<int,int>
	#define fir first
	#define sec second
	#define MP make_pair
	#define rep(i,x,y) for (int i=(x);i<=(y);i++)
	#define drep(i,x,y) for (int i=(x);i>=(y);i--)
	#define go(x) for (int i=head[x];i;i=edge[i].nxt)
	#define templ template<typename T>
	#define sz 303030
	typedef long long ll;
	typedef double db;
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	templ inline T rnd(T l,T r) {return uniform_int_distribution<T>(l,r)(rng);}
	templ inline bool chkmax(T &x,T y){return x<y?x=y,1:0;}
	templ inline bool chkmin(T &x,T y){return x>y?x=y,1:0;}
	templ inline void read(T& t)
	{
		t=0;char f=0,ch=getchar();double d=0.1;
		while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
		while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
		if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
		t=(f?-t:t);
	}
	template<typename T,typename... Args>inline void read(T& t,Args&... args){read(t); read(args...);}
	char sr[1<<21],z[20];int C=-1,Z=0;
    inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
    inline void print(register int x)
    {
    	if(C>1<<20)Ot();if(x<0)sr[++C]='-',x=-x;
    	while(z[++Z]=x%10+48,x/=10);
    	while(sr[++C]=z[Z],--Z);sr[++C]='\n';
    }
	void file()
	{
		#ifndef ONLINE_JUDGE
		freopen("a.in","r",stdin);
		#endif
	}
	inline void chktime()
	{
		#ifndef ONLINE_JUDGE
		cout<<(clock()-t)/1000.0<<'\n';
		#endif
	}
	#ifdef mod
	ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;return ret;}
	ll inv(ll x){return ksm(x,mod-2);}
	#else
	ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x) if (y&1) ret=ret*x;return ret;}
	#endif
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

int n;ll a;
ll sum[sz];
ll d[sz];
ll F[sz];

struct hh
{
	ll f;
	ll mx;
	ll mxr;
}s[sz];
int top;
inline ll sq(ll x){return x*x;}

int main()
{
	file();
	read(n,a);
	ll x;
	rep(i,1,n) read(d[i],x),sum[i]=sum[i-1]+x,F[i]=a*i-sum[i];
	ll ans=max(a-sum[n]+sum[n-1],0ll);
	s[++top]=(hh){F[n],0,F[n]};
	s[0].mxr=-1e15;
	drep(i,n-1,1)
	{
		ll mxF=-1e15;
		while (top&&s[top].mx<=d[i+1]-d[i]) chkmax(mxF,s[top].f),s[top]=(hh){0,0,0},--top;
		if (mxF!=-1e15) {++top;s[top]=(hh){mxF,d[i+1]-d[i],max(mxF-sq(d[i+1]-d[i]),s[top-1].mxr)};}
		++top;s[top]=(hh){F[i],0,max(F[i],s[top-1].mxr)};
		chkmax(ans,s[top].mxr-a*i+a+sum[i-1]);
	}
	cout<<ans;
	return 0;
}
```





---

## 作者：cosf (赞：2)

分享一个比较典的思路。

我们可以枚举 $(d_i - d_{i + 1})^2$ 的最大值，从大到小枚举。

显然，$(d_i - d_{i + 1})^2$ 作为 $gap$ 的区间的左右端点肯定都在一个特定的区间内。例如左端点，其最右能到 $i$，最左则是某个比他大的 $(d_j - d_{j+1})^2$ 的 $j + 1$。用 set 维护即可。

我们先对 $c_i \gets a - c_i$，那么，接下来就可以使用线段树进行区间 $\max / \min$，然后再利用答案是 $(\sum_{i=l}^r c_i) - gap$，前缀和优化即可。

```cpp
#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
using namespace std;

#define MAXN 300005

using ll = long long;

template <typename T>
T INF = numeric_limits<T>::max() >> 1;

int n;
ll a;

ll d[MAXN], c[MAXN];

ll s[MAXN];

int p[MAXN];

ll t[MAXN << 2][2];

void pushup(int p)
{
    t[p][0] = min(t[p << 1][0], t[p << 1 | 1][0]);
    t[p][1] = max(t[p << 1][1], t[p << 1 | 1][1]);
}

void build(int p, int l, int r)
{
    if (l == r)
    {
        t[p][0] = t[p][1] = s[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

ll qle(int p, int l, int r, int ql, int qr)
{
    if (ql == 0)
    {
        return min(0ll, qle(p, l, r, ql + 1, qr));
    }
    if (qr < ql)
    {
        return 0;
    }
    if (ql <= l && r <= qr)
    {
        return t[p][0];
    }
    int mid = (l + r) >> 1;
    ll res = INF<ll>;
    if (mid >= ql)
    {
        res = min(res, qle(p << 1, l, mid, ql, qr));
    }
    if (mid < qr)
    {
        res = min(res, qle(p << 1 | 1, mid + 1, r, ql, qr));
    }
    return res;
}

ll qri(int p, int l, int r, int ql, int qr)
{
    if (ql == 0)
    {
        return max(0ll, qri(p, l, r, ql + 1, qr));
    }
    if (qr < ql)
    {
        return 0;
    }
    if (ql <= l && r <= qr)
    {
        return t[p][1];
    }
    int mid = (l + r) >> 1;
    ll res = -INF<ll>;
    if (mid >= ql)
    {
        res = max(res, qri(p << 1, l, mid, ql, qr));
    }
    if (mid < qr)
    {
        res = max(res, qri(p << 1 | 1, mid + 1, r, ql, qr));
    }
    return res;
}

int main()
{
    cin >> n >> a;
    ll res = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> d[i] >> c[i];
        c[i] = a - c[i];
        res = max(res, c[i]);
        s[i] = s[i - 1] + c[i];
        p[i] = i;
    }
    build(1, 1, n);
    for (int i = 1; i < n; i++)
    {
        d[i] = (d[i] - d[i + 1]) * (d[i] - d[i + 1]);
    }
    sort(p + 1, p + n, [](int a, int b)
         { return d[a] > d[b]; });
    set<int, greater<int>> sl;
    set<int> sr;
    sl.insert(1);
    sl.insert(n);
    sr.insert(1);
    sr.insert(n);
    for (int i = 1; i < n; i++)
    {
        int l = p[i], r = l + 1;
        int le = *sl.lower_bound(l);
        int ri = *sr.lower_bound(r);
        res = max(res, qri(1, 1, n, r, ri) - qle(1, 1, n, le - 1, l - 1) - d[l]);
        sl.insert(l + 1);
        sr.insert(r - 1);
    }
    cout << res << endl;
    return 0;
}

```

---

同样的思路可以用在很多不同的题，比如说计算 $\max_{1 \le l \lt r \le n} \{(r - l)\min_{i=l}^ra_i\}$ 等等。

---

## 作者：Mihari (赞：2)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1107G)

给定 $n,a$ 以及有 $n$ 个元素的一个数列 $c$ 和一个**单调不降**数列 $d$，求
$$
\max\{(r-l+1)\times a-\sum_{i=l}^r c_i-\text{gap}(l,r)\}
$$
其中 $l\in [1,n],l\le r\le n$ 且
$$
\text{gap}(l,r)=\max_{i=l}^{r-1}(d_{i+1}-d_i)^2
$$
特别地，如果 $l=r$，那么 $\text{gap}(l,r)=0$.

# 题解

分析题目中的柿子，对于一个区间 $[l,r]$，将其的值记为 $\text{val}(l,r)$，即记
$$
\text{val}(l,r)=(r-l+1)\times a-\sum_{i=l}^r c_i-\text{gap}(l,r)
$$
不难看出，我们要快速计算 $\sum_{i=l}^r c_i$，可以先将其处理为前缀和的形式，那么 $\sum_{i=l}^r c_i$ 就变成 $c_r-c_{l-1}$

尝试将 $\text{val}(l,r)$ 进行转化：
$$
\begin{aligned}
\text{val}(l,r)&=(r-l+1)\times a-(c_r-c_{l-1})-\text{gap}(l,r) \\
&=ar-a(l-1)-c_r+c_{l-1}-\text{gap}(l,r) \\
&=(ar-c_r)-\left [ a(l-1)-c_{l-1}\right]-\text{gap}(l,r)
\end{aligned}
$$
发现有形式相同的部分 $ar-c_r$ 与 $a(l-1)-c_{l-1}$，那么我们记
$$
f(x)=ax-c_{x}
$$
柿子就变成
$$
\text{val}(l,r)=f(r)-f(l-1)-\text{gap}(l,r)
$$
考虑移项，有
$$
\text{val}(l,r)+f(l-1)=f(r)-\text{gap}(l,r)
$$
对于每个 $l$，我们所需要做的就是在所有 $r\in [l,n]$ 中找到最大的 $f(r)-\text{gap}(l,r)$，考虑先处理子问题，如果没有 $\text{gap}(l,r)$，那么我们用单调栈，或者退一步用线段树等数据结构都是很好处理的，但是由于这个 $\text{gap}(l,r)$ 涉及 $l$，对于不同的 $l$，这个 $\text{gap}(l,r)$ 的值都不一定相同。

考虑分析 $\text{gap}(l,r)$ 的结构，是所有区间 $[l,r]$ 中 $d$ 的相邻两项的差值的平方的最大值，由于是最大值，那么 $\text{gap}(l,r)$ 在 $r$ 固定，$l$ 变小的情况下，只有可能变大而没可能变小，即其具单调性。

既然有单调性，考虑同样用单调栈维护 $\text{gap}(l,r)$，因为 $d$ 单调不降，那么 $d_{l+1}-d_l\ge 0$，符号全为正，那么我们并不需要直接比较平方而先维护 $\max \Delta d$.

显然，$\max \Delta d$ 在某一段都是连续的，对于有着同样 $\max \Delta d$ 的区间，我们可以考虑将其合并，对于新的一个 $l$，我们要放入 $d_{l+1}-d_l$ 的值，对于那些小于这个值的区间弹出，将他们**合并之后**（因为他们的原 $d$ 都比 $d_{l+1}-d_l$ 小，取最大值后他们的 $d$ 都变为 $d_{l+1}-d_l$，这时他们将被视作 $\max \Delta d$ 相同的区间，需合并）再将 $\max \Delta d$ 更新为 $d_{l+1}-d_l$，最后再放入单点 $l$ 即可。

前面提及

> 如果没有 $\text{gap}(l,r)$，那么我们用单调栈，或者退一步用线段树等数据结构都是很好处理的。

而 $\text{gap}(l,r)$ 经分析后发现可以用单调栈维护，那么我们尝试同时用单调栈维护 $f(r)$ 和 $\text{gap}(l,r)$.

对于有着同样 $\max \Delta d$ 的**区间**，我们记录几个**最大**值：

- $\max\Delta d$，这个还要用于维护单调性；
- $\max \{f-\Delta d\}$，这个用于更新答案；
- $\max f$，这个需要用于更新 $\max \Delta d$ 之后重新计算 $\max \{f-\Delta d\}$；

在我们放入一个新的 $l$ 时，我们实际要放入 $d_{l+1}-d_l$，首先将那些 $\max\Delta d<d_{l+1}-d_l$ 的区间弹出、合并、更新、重新放入，再讲其自己——单点 $l$ 放入栈即可。

至于区间弹出、合并、更新、重新放入，代码中有详细说明。

# 代码

```cpp
#include<cstdio>

#define rep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i<=i##_end_;++i)
#define fep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i>=i##_end_;--i)
#define erep(i,u) for(signed i=tail[u],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
#define writc(a,b) fwrit(a),putchar(b)
#define mp(a,b) make_pair(a,b)
#define ft first
#define sd second
typedef long long LL;
// typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned uint;
#define Endl putchar('\n')
#define int long long
// #define int unsigned
// #define int unsigned long long

#define cg (c=getchar())
template<class T>inline void read(T& x){
    char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    if(f)x=-x;
}
template<class T>inline T read(const T sample){
    T x=0;char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    return f?-x:x;
}
template<class T>void fwrit(const T x){//just short,int and long long
    if(x<0)return (void)(putchar('-'),fwrit(-x));
    if(x>9)fwrit(x/10);
    putchar(x%10^48);
}
template<class T>inline T Max(const T x,const T y){return x<y?y:x;}
template<class T>inline T Min(const T x,const T y){return x<y?x:y;}
template<class T>inline T fab(const T x){return x>0?x:-x;}
inline int gcd(const int a,const int b){return b?gcd(b,a%b):a;}
inline void getInv(int inv[],const int lim,const int MOD){
    inv[0]=inv[1]=1;for(int i=2;i<=lim;++i)inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
}
inline LL mulMod(const LL a,const LL b,const LL mod){//long long multiplie_mod
    return ((a*b-(LL)((long double)a/mod*b+1e-8)*mod)%mod+mod)%mod;
}

const int maxn=3e5;
const LL inf=(1ll<<60);

int n;

LL a,d[maxn+5],c[maxn+5],f[maxn+5];

inline void Init(){
    n=read(1),a=read(1ll);
    rep(i,1,n)d[i]=read(1ll),c[i]=c[i-1]+read(1ll),f[i]=a*i-c[i];
}

struct node{LL d,maxf,maxans;}sta[maxn+5];
int ed;

//返回平方数
inline LL pow2(const LL x){return x*x;}

inline void Get_ans(){
    LL ans=Max(0ll,a-(c[n]-c[n-1]));//先选择单点, 但也有可能不选更好...
    sta[0].maxans=-inf;//在下面的后缀最大中, 为防止 0 干扰后缀最大, 此处赋值为极小值
    sta[++ed]=node{0,f[n],f[n]};//放进去单点, 没有 d, 故 d=0
    LL max_pref;//记录因为 d 太小而被弹出的区间中, maxf 的最大值
    fep(l,n-1,1){max_pref=-inf;
        while(ed>0 && sta[ed].d<=d[l+1]-d[l]){
            max_pref=Max(max_pref,sta[ed].maxf);//为了之后再把这些区间放进去时再用
            sta[ed--]=node{0,0,0};//为了预防干扰计算
        }
        if(max_pref!=-inf)
            //存在某些区间的 d 比放进去的小, 这些需要被更新
            //这个时候需要更新他们的 d, 再把他们合并放进去
            //而此处与前一位置的 maxf 取最大值
            //是因为我们栈的元素中 maxans 并不是这个元素单独的 maxans, 而是栈中的所有元素的 maxans 的后缀最大值
            //我们要用最大值来更新答案, 而不只是单独一个元素的 maxans
            sta[++ed]=node{d[l+1]-d[l],max_pref,Max(max_pref-pow2(d[l+1]-d[l]),sta[ed-1].maxans)};
        //把这个单点 l 放进去
        sta[++ed]=node{0,f[l],Max(f[l],sta[ed-1].maxans)};
        //更新答案
        ans=Max(ans,sta[ed].maxans-f[l-1]);
        // rep(i,0,ed)
        //     printf("sta[%d] : %lld %lld %lld\n",i,sta[i].d,sta[i].maxf,sta[i].maxans);
    }writc(ans,'\n');
}

signed main(){
    Init();
    Get_ans();
    return 0;
}
```



---

## 作者：LJC00118 (赞：2)

每道题做出来得 $ a $ 分，要做这题要 $ -c_{i} $ 分，直接把 $ a $ 加进去，每道题的权值 $ v_{i} = a - c_{i} $

如果题目没有 $ d $ 的限制，当前的答案即为数列中最大子段和

如果有了 $ d $ 的限制，会发现不同的 $ d $ 的限制不超过 $ n - 1 $ 个

考虑分治，每次选出 $ d_{i + 1} - d_{i} $ 最大的一组，找经过 $ i $ 和 $ i + 1 $ 的最大字段和，且不能有 $ j $ 使得 $ j $ 和 $ j - 1 $ 都在最大字段和中且 $ d_{i + 1} - d{i} < d_{j + 1} - d_{j} $

我们用 $ solve(l, r) $ 来进行分治，如果 $ l == r $ 就 return 掉

$ i $ 为使得当前 $ d_{i + 1} - d_{i} $ 最大的数

线段树维护经过 $ i $ 和 $ i + 1 $ 的在区间 $ [l, r] $ 内的最大字段和

$ solve(l, i), solve(i + 1, r) $ 防止再次同时经过 $ i $ 和 $ i + 1 $ 即可

特判只取一个数的情况

```cpp
#include <bits/stdc++.h>
#define int long long
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 3e5 + 5;

struct info {
    int lmax, rmax, sum;
    info () { lmax = rmax = sum = 0; }
};

info merge(info a, info b) {
    info ans;
    ans.lmax = max(a.lmax, a.sum + b.lmax);
    ans.rmax = max(b.rmax, b.sum + a.rmax);
    ans.sum = a.sum + b.sum;
    return ans;
}

struct node_t {
    int l, r;
    info val;
} p[N << 2];

int a[N], d[N];
int n, k, ans;

void build(int u, int l, int r) {
    p[u].l = l; p[u].r = r;
    if(l == r) {
        p[u].val.lmax = p[u].val.rmax = max(0ll, a[l]);
        p[u].val.sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
    p[u].val = merge(p[u << 1].val, p[u << 1 | 1].val);
}

info query(int u, int l, int r) {
    if(l > r) return info();
    if(l <= p[u].l && p[u].r <= r) return p[u].val;
    int mid = (p[u].l + p[u].r) >> 1;
    if(mid >= l && mid + 1 <= r) return merge(query(u << 1, l, r), query(u << 1 | 1, l, r));
    if(mid >= l) { return query(u << 1, l, r); } return query(u << 1 | 1, l, r);
}

int st[N][20], wz[N][20], lg[N];

pii query(int l, int r) {
    int k = lg[r - l + 1];
    int x = st[l][k], y = st[r - (1 << k) + 1][k];
    if(x > y) return make_pair(x, wz[l][k]);
    return make_pair(y, wz[r - (1 << k) + 1][k]);
}

void solve(int l, int r) {
    if(l == r) return;
    pii t = query(l, r - 1);
    int wz = t.second, now = a[wz] + a[wz + 1] - t.first;
    now += (query(1, l, wz - 1).rmax + query(1, wz + 2, r).lmax);
    ans = max(ans, now); solve(l, wz); solve(wz + 1, r);
}

#undef int
int main() {
#define int long long
    read(n); read(k);
    for(register int i = 1; i <= n; i++) read(d[i]), read(a[i]), a[i] = k - a[i], ans = max(ans, a[i]);
    build(1, 1, n);
    for(register int i = 1; i < n; i++) {
        st[i][0] = (d[i + 1] - d[i]) * (d[i + 1] - d[i]);
        wz[i][0] = i;
    }
    lg[0] = -1; for(register int i = 1; i < n; i++) lg[i] = lg[i >> 1] + 1;
    for(register int j = 1; j <= 18; j++) {
        for(register int i = 1; i <= n - (1 << (j - 1)) + 1; i++) {
            int x = st[i][j - 1], y = st[i + (1 << (j - 1))][j - 1];
            if(x > y) st[i][j] = x, wz[i][j] = wz[i][j - 1];
            else st[i][j] = y, wz[i][j] = wz[i + (1 << (j - 1))][j - 1];
        }
    }
    solve(1, n); cout << ans << endl;
    return 0;
}
```

---

## 作者：wangzikang (赞：1)

这题题面很抽象，但是不影响它是一道水 2400。

我们考虑枚举那个叫 Gap 的东西，然后我们发现这个东西是个很典的单调栈，然后考虑怎么确定最大的答案，记 $\{b_n=a-c_n\}$，则剩下的问题就是在一个区间内，确定两个连着的点，找最大区间，这个东西直接分别维护前后缀的 st 表即可。

当然，那个单调栈也可以写二分。

```cpp
 
#include<bits/stdc++.h>
//#include "atcoder/modint"
#define int long long
#define spc() ALL_OUT[++ALL_LEN]=' '
#define nxtl() ALL_OUT[++ALL_LEN]='\n'
#define clrout() ALL_OUT[ALL_LEN+1]=0,fputs(ALL_OUT,stdout),ALL_LEN=-1
#define rt() return clrout(),0;
using namespace std;
const long long P[]={(long long)1,(long long)1e1,(long long)1e2,(long long)1e3,(long long)1e4,(long long)1e5,(long long)1e6,(long long)1e7,(long long)1e8,(long long)1e9,(long long)1e10,(long long)1e11,(long long)1e12,(long long)1e13,(long long)1e14,(long long)1e15,(long long)1e16,(long long)1e17,(long long)1e18};
char OUT_LIST[41],ALL_OUT[100100];
int ALL_LEN=-1;
void write(int x,short l=40){
    const int k=x/10;
	OUT_LIST[l]=(x-(k<<1)-(k<<3))|'0';
    if(x>9)write(k,l-1);
    else{
    	if(ALL_LEN>100000)clrout();
    	for(;l<33;l+=8){
    		ALL_OUT[1+ALL_LEN]=OUT_LIST[l];
    		ALL_OUT[2+ALL_LEN]=OUT_LIST[l+1];
    		ALL_OUT[3+ALL_LEN]=OUT_LIST[l+2];
    		ALL_OUT[4+ALL_LEN]=OUT_LIST[l+3];
    		ALL_OUT[5+ALL_LEN]=OUT_LIST[l+4];
    		ALL_OUT[6+ALL_LEN]=OUT_LIST[l+5];
    		ALL_OUT[7+ALL_LEN]=OUT_LIST[l+6];
    		ALL_OUT[ALL_LEN=(8+ALL_LEN)]=OUT_LIST[l+7];
		}
		switch(40-l){
			case 7:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 6:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 5:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 4:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 3:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 2:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 1:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
			case 0:ALL_OUT[++ALL_LEN]=OUT_LIST[l++];
		}
	}
}
#define xxx const int mid=(L+R)>>1
int read(){
   char ch=getchar();
   int s=0;
   while(ch<'0'||ch>'9')ch=getchar();
   while(ch>='0'&&ch<='9') s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
   return s;
}
const int N=2e5+10;
int n,k,a[N],d[N],b[N],st[21][N],L[N],R[N],lg[N+10],L1[N],R1[N],qzh[N];
pair<int,int>ST[21][N];
int Q(int l,int r){
    int len=r-l+1;
    return max(st[lg[len]][l],st[lg[len]][r-(1<<lg[len])+1]);
} 
pair<int,int> ask(int l,int r){
    int len=r-l+1;
    return max(ST[lg[len]][l],ST[lg[len]][r-(1<<lg[len])+1]);
}
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>d[i]>>a[i];
        a[i]=k-a[i];
        qzh[i]=qzh[i-1]+a[i];
    }
    for(int i=2;i<=N;++i){
        lg[i]=lg[i>>1]+1;
    }
    for(int i=1;i!=n;++i){
        st[0][i]=b[i]=(d[i+1]-d[i]);
    }
    for(int j=1;j<=20;++j)for(int i=1;i!=n;++i){
        st[j][i]=max(st[j-1][i],st[j-1][i+(1<<(j-1))]);
    }
    int ans=0;
    for(int i=1;i<=n;++i){
        ans=max(ans,a[i]);
    }
    for(int i=1;i!=n;++i){
        int l=i,r=n-1,&ans=R[i];
        while(l<=r){
            const int mid=(l+r)>>1;
            if(Q(i,mid)<=b[i]){
                l=mid+1;
                ans=mid;
            }else{
                r=mid-1;
            }
        }
        if(ans!=0){
            ans++;
        }else{
            ans=-1;
        }
    }
    for(int i=1;i!=n;++i){
        int l=1,r=i,&ans=L[i];
        while(l<=r){
            const int mid=(l+r)>>1;
            if(Q(mid,i)<=b[i]){
                r=mid-1;
                ans=mid;
            }else{
                l=mid+1;
            }
        }
        if(!ans)ans=-1;
    }
    for(int i=1;i!=n;++i){
        // cout<<L[i]<<' '<<R[i]<<'\n';
        // ans=max(ans,qzh[R[i]]-qzh[L[i]-1]-(b[i]*b[i]));        
    }
    for(int i=0;i!=N;++i){
        ST[0][i]={-1e18,i};
    }
    for(int i=1;i<=n;++i){
        ST[0][i]={qzh[i],i};
    }
    for(int j=1;j<=20;++j)for(int i=1;i!=n;++i){
        ST[j][i]=max(ST[j-1][i],ST[j-1][i+(1<<(j-1))]);
    }
    for(int i=1;i!=n;++i){//inc i,i+1
        int tmp=-b[i];
        int l=L[i],r=R[i];
        if(l==-1||r==-1)continue;
        R[i]=ask(i+1,r).second;
    }
    for(int i=n;i;--i){
        qzh[i]=qzh[i+1]+a[i];
    }
    for(int i=1;i<=n;++i){
        ST[0][i]={qzh[i],i};
    }
    for(int j=1;j<=20;++j)for(int i=1;i!=n;++i){
        ST[j][i]=max(ST[j-1][i],ST[j-1][i+(1<<(j-1))]);
    }
    for(int i=1;i!=n;++i){//inc i,i+1
        int tmp=-b[i];
        int l=L[i],r=R[i];
        if(l==-1||r==-1)continue;
        L[i]=ask(l,i).second;
    }
    for(int i=1;i<=n;++i){
        qzh[i]=qzh[i-1]+a[i];
    }
    for(int i=1;i!=n;++i){
        // cout<<L[i]<<' '<<R[i]<<'\n';
        ans=max(ans,qzh[R[i]]-qzh[L[i]-1]-(b[i]*b[i]));        
    }
    cout<<ans;
    rt();
}
```

---

## 作者：LinkyChristian (赞：1)

粉兔杯决胜题，慕名前来参观。

题面非常抽象，给的 $a$ 完全没用，我们考虑将 $c_i$ 改为 $a-c_i$ ，将 $d_i$ 改为 $(d_i-d_{i-1})^2$ ，$[l,r]$ 的权值即为区间内 $c_i$ 的和减去区间内最大的 $d_i$ 。

考虑我们用单调栈处理出每个 $d_i$ 作为最大值的区间，然后使用前缀和以及倍增维护一下包含某个特定位置的最大子段和，就做完了。

```cpp
#include<bits/stdc++.h>
#define N 300010
#define int long long
using namespace std;
int n,a,d[N],c[N],tp[22][N],tl[22][N],p1[N],p2[N],sk[N],top,ans;
int query(int l,int r,int p) {
	int k=log2(r-l+1);
	if(p) return max(tp[k][l],tp[k][r-(1<<k)+1]);
	return max(tl[k][l],tl[k][r-(1<<k)+1]);
}
main() {
	cin>>n>>a;
	for(int i=1; i<=n; i++) cin>>d[i]>>c[i],c[i]=a-c[i],ans=max(ans,c[i]);
	for(int i=1; i<=n; i++) tp[0][i]=tp[0][i-1]+c[i];
	for(int i=n; i; i--) tl[0][i]=tl[0][i+1]+c[i],d[i]=(d[i]-d[i-1])*(d[i]-d[i-1]);
	d[1]=0;
	for(int k=1; k<20; k++)
		for(int i=1; i+(1<<k)-1<=n; i++) 
			tp[k][i]=max(tp[k-1][i],tp[k-1][i+(1<<(k-1))]),
			tl[k][i]=max(tl[k-1][i],tl[k-1][i+(1<<(k-1))]);
	for(int i=2; i<=n; i++) {
		while(top&&d[sk[top]]<=d[i]) top--;
		if(top) p1[i]=sk[top];
		else p1[i]=1;
		sk[++top]=i; 
	}
	top=0;
	for(int i=n; i>1; i--) {
		while(top&&d[sk[top]]<=d[i]) top--;
		if(top) p2[i]=sk[top];
		else p2[i]=n+1;
		sk[++top]=i;
	}
	for(int i=2; i<=n; i++) {
		int lmx=query(p1[i],i-1,0)-tl[0][i],rmx=query(i,p2[i]-1,1)-tp[0][i-1];
		ans=max(ans,lmx+rmx-d[i]);
	}
	cout<<ans;
}
```

不是这题凭啥 2400 啊


---

## 作者：StayAlone (赞：0)

神秘，为啥都会枚举 $\max$ 的位置啊？

考虑枚举 $l$。

记 $c$ 的前缀和 $sc_i$，$p_i=(d_{i+1}-d_i)^2$。那么区间 $[l, r]$ 的答案就是 $a(r-l+1)-(sc_r-sc_{l-1})-\max_{i=l}^{r-1}p_{i}=a(1-l)+sc_{l-1}+(ar-sc_r)-\max_{i=l}^{r-1}p_{i}$。

~~单调栈修改线段树即可。~~

从右往左枚举 $l$，线段树上每个位置维护 $(ar-sc_r)-\max_{i=l}^{r-1}p_{i}$。维护 $p$ 的单调栈，每次加入 $l$ 时在对应的区间做区间加，查询区间 $\max$ 即可。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
int n, a, c[MAXN], d[MAXN], st[MAXN], tot; const ll inf = ~0Ull >> 2;
ll ans, sc[MAXN], dp[MAXN], val[MAXN];

struct setr {
	ll tag[MAXN << 2], mx[MAXN << 2];
	
	il void pushdown(int x) {
		if (!tag[x]) return;
		tag[ls(x)] += tag[x]; tag[rs(x)] += tag[x];
		mx[ls(x)] += tag[x]; mx[rs(x)] += tag[x];
		tag[x] = 0;
	}
	
	il void pushup(int x) {
		mx[x] = max(mx[ls(x)], mx[rs(x)]);
	}
	
	il void upd(int x, int l, int r, int ql, int qr, ll k) {
		if (l > qr || r < ql) return;
		if (l >= ql && r <= qr) return mx[x] += k, tag[x] += k, void();
		int mid = l + r >> 1; pushdown(x);
		upd(ls(x), l, mid, ql, qr, k); upd(rs(x), mid + 1, r, ql, qr, k);
		pushup(x);
	}
	
	il ll query(int x, int l, int r, int ql, int qr) {
		if (l > qr || r < ql) return -inf;
		if (l >= ql && r <= qr) return mx[x];
		int mid = l + r >> 1; pushdown(x);
		return max(query(ls(x), l, mid, ql, qr), query(rs(x), mid + 1, r, ql, qr));
	}
} T;

int main() {
	read(n, a);
	rep1(i, 1, n) {
		read(d[i], c[i]);
		sc[i] = sc[i - 1] + c[i];
	}
	rep1(i, 1, n - 1) {
		ll p = d[i] - d[i + 1];
		dp[i] = p * p;
	}
	rep1(i, 1, n) val[i] = -sc[i] + 1ll * a * i;
	st[0] = n + 1;
	rep2(i, n, 1) {
		T.upd(1, 1, n, i, i, val[i]);
		while (tot && dp[st[tot]] < dp[i]) {
			int rr = st[tot - 1], rl = st[tot--] + 1;
			T.upd(1, 1, n, rl, rr, dp[rl - 1] - dp[i]);
		} T.upd(1, 1, n, i + 1, i + 1, -dp[i]); gmax(ans, T.query(1, 1, n, i, n) + sc[i - 1] - a * ll(i - 1)); st[++tot] = i;
	} printf("%lld", ans);
	return 0;
}
```

---

## 作者：Shunpower (赞：0)

和 StayAlone 打 duel 的时候做到的。

------------

考虑区间 $\max$ 的形式不太方便，考虑枚举 $\max\{(d_{i+1}-d_{i})^2\}$ 的 $\max$ 所在位置，那么可以重载权值为 $(d_{i+1}-d_{i})^2$，用单调栈可以简单计算出它作为 $\max$ 的 $l,r$ 两端点所在区间。

考虑把 $a$ 的权值塞进 $c$，然后把花钱变成负数，也就是 $c_i\gets -c_i+a$，那么我们其实希望找一个 $l$ 使得 $[l,i]$ 的 $c$ 的和最大，找一个 $r$ 使得 $[i+1,r]$ 的 $c$ 的和最大。使用前缀和后转成 RMQ。

对于所有 $\max$ 位置取 $\max$，然后特殊考虑一下长度为 $1$ 的区间即可。

时间复杂度 $\mathcal O(n\log n)$，瓶颈在 RMQ。

```cpp
const int N=3e5+10;
int n,a;
ll d[N];
ll c[N];
ll coef[N];
int lef[N],rig[N];
ll sum[N];
#define mid (l+r>>1)
struct sgt{
	ll minn[N<<2],maxn[N<<2];
	void pushup(int p){
		minn[p]=min(minn[p<<1],minn[p<<1|1]);
		maxn[p]=max(maxn[p<<1],maxn[p<<1|1]);
	}
	il void build(int p,int l,int r){
		if(l==r) return minn[p]=maxn[p]=sum[l],void();
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		pushup(p);
	}
	il ll querymax(int p,int l,int r,int ml,int mr){
		if(ml<=l&&r<=mr) return maxn[p];
		ll ans=-1e18;
		if(ml<=mid) ans=max(ans,querymax(p<<1,l,mid,ml,mr));
		if(mid<mr) ans=max(ans,querymax(p<<1|1,mid+1,r,ml,mr));
		return ans;
	}
	il ll querymin(int p,int l,int r,int ml,int mr){
		if(ml<=l&&r<=mr) return minn[p];
		ll ans=1e18;
		if(ml<=mid) ans=min(ans,querymin(p<<1,l,mid,ml,mr));
		if(mid<mr) ans=min(ans,querymin(p<<1|1,mid+1,r,ml,mr));
		return ans;
	}
} T;
#undef mid
int main(){
#ifdef Shun
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin>>n>>a;
	fr1(i,1,n) cin>>d[i]>>c[i];
	fr1(i,1,n) c[i]=-c[i]+a;
	fr1(i,1,n) sum[i]=sum[i-1]+c[i];
	T.build(1,0,n);
	fr1(i,2,n) coef[i]=1ll*(d[i]-d[i-1])*(d[i]-d[i-1]);
	{
		stack <int> st;
		fr1(i,2,n){
			while(!st.empty()){
				if(coef[st.top()]<coef[i]) rig[st.top()]=i,st.pop();
				else break;
			}
			st.push(i);
		}
		while(!st.empty()){
			rig[st.top()]=n+1;
			st.pop();
		}
		fr1(i,2,n) rig[i]--;
	}
	{
		stack <int> st;
		fr2(i,n,2){
			while(!st.empty()){
				if(coef[st.top()]<coef[i]) lef[st.top()]=i,st.pop();
				else break;
			}
			st.push(i);
		}
		while(!st.empty()){
			lef[st.top()]=1;
			st.pop();
		}
		// fr1(i,2,n) lef[i];
	}
	ll ans=0;
	fr1(i,1,n) ans=max(ans,c[i]);
	fr1(i,2,n){
		int llim=lef[i],rlim=rig[i];
		int l=i-1,r=i;
		ll sum0=0,sum1=0;
		ll max0=0,max1=0;
		max0=sum[l]-T.querymin(1,0,n,llim-1,l-1);
		max1=T.querymax(1,0,n,r,rlim)-sum[l];
		// fr2(j,l,llim) sum0+=c[j],max0=max(max0,sum0);
		// fr1(j,r,rlim) sum1+=c[j],max1=max(max1,sum1);
		// cout<<i<<" "<<max0<<" "<<max1<<endl;
		ans=max(ans,max0+max1-coef[i]);
	}
	cout<<ans<<'\n';
	ET;
}
//ALL FOR Zhang Junhao.
```

---

## 作者：IkunTeddy (赞：0)

# 题目分析

考虑到 $\max\limits_{l\le i < r}(d_{i+1}-d_i)$ 不是很好维护，考虑枚举哪一段是最大值。在合法区间内再找答案即可，这就是笛卡尔树的子树信息。

设 $s_i=a-c_i$，$L$ 为当以 $d_{i+1}-d_i$ 为最值时的最远左端点，$R$ 同理。我们就要求 $\max\limits_{L\le l\le i,i+1\le r\le R}{\sum\limits_{j=l}^{r}{s_j}}$。

将 $\sum\limits_{j=l}^{r}{s_j}$ 差分一下为 $pre_r-pre_{l-1}$，现在转为 $\max\limits_{i+1\le r\le R}pre_r-\min\limits_{L\le l\le i}pre_{l-1}$。

这个式子预处理笛卡尔树子树信息即可。

时间复杂度 $O(n)$。

---

## 作者：ifffer_2137 (赞：0)

~~洛谷题面有点【Data Lost】了~~。
### 题意
给定 $n,a$ 和序列 $c_i,d_i$，求：
$$\max_{1\le l\le r\le n}(\max_{i=l}^{r-1}(d_{i+1}-d_i)^2+\sum_{i=l}^ra-c_i)$$
### 分析
看到最优子段容易想到的一种做法是扫描线，但是如果你试过就会发现做不了，因为要把两个数列分别区间赋值/区间加然后求对应位置相加 $\max$，是不可做大 ds。

于是只能换条路，对着柿子的两部分抿一下，发现求和的贡献更容易维护，于是枚一个 $\max$，前面正反两遍单调栈预处理出合法区间，然后相当于求一个左边的最大后缀和加右边的最大前缀和，注意端点被钦定了必选，然后上个类 GSS sgt 维护一下区间和，区间最大前后缀和就好了。

时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=3e5+5;
int n,a,ans;
int d[maxn],c[maxn];
int stk[maxn],tp;
int L[maxn],R[maxn];
int calc(int x){return (d[x+1]-d[x])*(d[x+1]-d[x]);}
struct Data{
	int sm,pre,suf;
	Data(){sm=pre=suf=0;}
	Data(int A,int B,int C){sm=A,pre=B,suf=C;}
	Data operator + (const Data &b) const{
		Data z;
		z.sm=sm+b.sm;
		z.pre=max(pre,sm+b.pre);
		z.suf=max(b.suf,suf+b.sm);
//		cout<<sm<<' '<<pre<<' '<<suf<<'\n';
//		cout<<b.sm<<' '<<b.pre<<' '<<b.suf<<'\n';
//		cout<<z.sm<<' '<<z.pre<<' '<<z.suf<<'\n';
//		cout<<"------\n";
		return z;
	} 
};
class Segment_Tree{
public:
	#define ls (o<<1)
	#define rs (o<<1|1)
	Data tr[maxn<<2];
	void pushup(int o){tr[o]=tr[ls]+tr[rs];}
	void build(int o,int l,int r){
		if(l==r){
			tr[o]=Data(a-c[l],a-c[l],a-c[l]);
			//cout<<l<<' '<<tr[o].sm<<' '<<tr[o].pre<<' '<<tr[o].suf<<'\n';
			return;
		}
		int m=(l+r)>>1;
		build(ls,l,m),build(rs,m+1,r);
		pushup(o);
	}
	Data query(int o,int l,int r,int x,int y){
		if(x>y) return Data(); 
		if(x<=l&&r<=y) return tr[o];
		int m=(l+r)>>1;
		if(x<=m&&y>m) return query(ls,l,m,x,y)+query(rs,m+1,r,x,y);
		if(x<=m) return query(ls,l,m,x,y);
		return query(rs,m+1,r,x,y); 
	}
}sgt;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),a=read();
	for(int i=1;i<=n;i++){
		d[i]=read(),c[i]=read();
		ans=max(ans,a-c[i]);
	}
	for(int i=1;i<n;i++) L[i]=0,R[i]=n+1; 
	for(int i=1;i<n;i++){
		while(tp&&calc(stk[tp])<calc(i)) R[stk[tp--]]=i;
		stk[++tp]=i;
	}
	for(int i=n-1;i>=1;i--){
		while(tp&&calc(stk[tp])<calc(i)) L[stk[tp--]]=i;
		stk[++tp]=i;
	}
	sgt.build(1,1,n);
	for(int i=1;i<n;i++){
		int res=-calc(i),l=L[i]+1,r=R[i];
		res+=sgt.query(1,1,n,l,i).suf+sgt.query(1,1,n,i+1,r).pre;
		ans=max(ans,res);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

