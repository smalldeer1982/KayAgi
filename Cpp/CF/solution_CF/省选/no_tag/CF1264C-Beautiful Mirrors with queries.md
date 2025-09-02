# Beautiful Mirrors with queries

## 题目描述

Creatnx has $ n $ mirrors, numbered from $ 1 $ to $ n $ . Every day, Creatnx asks exactly one mirror "Am I beautiful?". The $ i $ -th mirror will tell Creatnx that he is beautiful with probability $ \frac{p_i}{100} $ for all $ 1 \le i \le n $ .

Some mirrors are called checkpoints. Initially, only the $ 1 $ st mirror is a checkpoint. It remains a checkpoint all the time.

Creatnx asks the mirrors one by one, starting from the $ 1 $ -st mirror. Every day, if he asks $ i $ -th mirror, there are two possibilities:

- The $ i $ -th mirror tells Creatnx that he is beautiful. In this case, if $ i = n $ Creatnx will stop and become happy, otherwise he will continue asking the $ i+1 $ -th mirror next day;
- In the other case, Creatnx will feel upset. The next day, Creatnx will start asking from the checkpoint with a maximal number that is less or equal to $ i $ .

There are some changes occur over time: some mirrors become new checkpoints and some mirrors are no longer checkpoints. You are given $ q $ queries, each query is represented by an integer $ u $ : If the $ u $ -th mirror isn't a checkpoint then we set it as a checkpoint. Otherwise, the $ u $ -th mirror is no longer a checkpoint.

After each query, you need to calculate [the expected number](https://en.wikipedia.org/wiki/Expected_value) of days until Creatnx becomes happy.

Each of this numbers should be found by modulo $ 998244353 $ . Formally, let $ M = 998244353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test after the first query, the first and the second mirrors are checkpoints. Creatnx will ask the first mirror until it will say that he is beautiful, after that he will ask the second mirror until it will say that he is beautiful because the second mirror is a checkpoint. After that, he will become happy. Probabilities that the mirrors will say, that he is beautiful are equal to $ \frac{1}{2} $ . So, the expected number of days, until one mirror will say, that he is beautiful is equal to $ 2 $ and the answer will be equal to $ 4 = 2 + 2 $ .

## 样例 #1

### 输入

```
2 2
50 50
2
2
```

### 输出

```
4
6
```

## 样例 #2

### 输入

```
5 5
10 20 30 40 50
2
3
4
5
3
```

### 输出

```
117
665496274
332748143
831870317
499122211
```

# 题解

## 作者：Zimo_666 (赞：13)

## [CF1264C] Beautiful Mirrors with queries

### 题意

●有 $n$ 个关卡，每关有 $p_i$ 的通过概率，通过进下一关，没通过从最近的存档点重新开始。

●关卡 $1$ 默认为存档点，会有 $q$ 次修改，每次修改一个关卡是否为存档点的设置，并询问对应的期望通关步数。

### 分析

我们先考虑一个简化版的问题，即 [CF1265E](https://www.luogu.com.cn/problem/CF1265E)。题意只有 $1$ 为存档点，没有修改。我们考虑这道题的做法，不如设 $f_i$ 表示通过关卡 $i$ 的期望步数，显然我们有 $f_{i}=f{i-1}+1+(1-p_i)\times f_{i}$ 即通过该关卡成功及失败情况步数和，解得 $f_i=\frac{f_{i-1}+1}{p_i}$。直接递推+逆元就可以求得本题解。

那么考虑这道题我们首先可以找一些优雅的规律，首先对于上一题，我们可以手推发现一些规律。

$f_1= \frac {1}{p_1}$，$f_2=\frac{1}{p_2}+\frac{1}{p_1p_2}$，$f_3=\frac{1}{p_3}+\frac{1}{p_2p_3}+\frac{1}{p_1p_2p_3}$，...

于是我们不妨设从 $l$ **走到** $r$ 的期望步数为 $g(l,r)=\frac {1}{p_{r-1}}+\frac {1}{p_{r-1}p_{r-2}}+...+\frac{1}{p_{r-1}p_{r-2}...{p_l}}$。

我们考虑找寻一种方法维护所有存档点，以及两个相邻存档点的距离。

我们考虑两个存档点 $l,r$ 中间加入一个新存档点 $x$ 的情况，我们不妨最先把 $1$ 和 $n+1$ 丢进 set 中（因为最开始考虑就是从 $1$ 走到 $n+1$ 的情况）。

而后我们使用 set 查找目前最近的 $l,r$ 存档点。

代码如下

```cpp
l=*--_set.lower_bound(x),r=*_set.upper_bound(x);
```

而后我们依照题意考虑如下情况

- 若 $x$ 原本不是存档点，则一段 $g(l,r)$ 会被修改为 $g(l,x)+g(x,r)-g(l,r)$。
- 若 $x$ 是存档点，则一段 $g(l,r)$ 会被修改为 $-g(l,x)-g(x,r)+g(l,r)$。

则我们考虑复杂度瓶颈，即快速计算形如上面那式子。

我们考虑维护一个形如后缀积的东西，设它为 $edf_i=\frac{1}{p_ip_{i+1}p_{i+1}...p_{n}}$，我们易有 $edf_r \times g(l,r)=edf_{r-1}+edf_{r-2}+...+edf{i}$。那么我们显然可以考虑使用前缀和维护形如后面区间和的 $edf$，我们有令 $sum_i=\sum_{j=1}^{i}edf_i$，这样的话我们就可以使用前缀和维护出 $g(l,r)=\frac{sum_{r-1}-sum_{i-1}}{edf_{r}}$。那么我们考虑 $O(n)$ 预处理前缀和和类后缀积数组就可以 $O(1)$ 求得答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,q;
const int N=1e6+7;
int edf[N],sum[N];
int p[N];
const int mod=998244353;
struct node{
  int inv[2000100],fac[2000100];
  int qpow(int shu,int cifang){
    int ans=1;int k=cifang;
    while(k){
      if(k&1){ans=ans*shu%mod;ans%=mod;shu=shu*shu%mod;shu%=mod;}
      else{shu=shu*shu%mod;shu%=mod;}
      k>>=1;
    }
    return ans%mod;
  }
  void init(int len){
    fac[0]=1;
    for(int i=1;i<=len;i++) fac[i]=fac[i-1]*i%mod;
    inv[len]=qpow(fac[len],mod-2);
    for(int i=len;i;i--){
      inv[i-1]=inv[i]*(i)%mod;
    }
  }
  int C(int n,int m){
    return fac[n]%mod*inv[m]%mod*inv[n-m]%mod;
  }
  int _inv(int x){
    return qpow(x,mod-2);
  }
}lg_get;
int calc(int l,int r){
  return ((sum[r-2]-sum[l-1]+mod)%mod*lg_get._inv(edf[l-1])+1)%mod*edf[l-1]%mod*lg_get._inv(edf[r-1])%mod;
}
set<int> _set;
signed main(){
  cin>>n>>q;
  edf[0]=1;
  int inv100=lg_get._inv(100);
  for(int i=1;i<=n;i++){
    scanf("%lld",&p[i]);
    p[i]=p[i]*inv100%mod;
    edf[i]=edf[i-1]*p[i]%mod;
    sum[i]=sum[i-1]+edf[i];
    sum[i]%=mod;
  }
  _set.insert(1),_set.insert(n+1);
  int ans=calc(1,n+1);
  int x;
  while(q--){
    scanf("%lld",&x);
    int l=*--_set.lower_bound(x),r=*_set.upper_bound(x);
    if(_set.count(x)){
      ans=ans-calc(l,x)-calc(x,r)+calc(l,r),_set.erase(x);
      ans%=mod;ans+=mod;ans%=mod;
    }
    else{
      ans=ans+calc(l,x)+calc(x,r)-calc(l,r),_set.insert(x);
	  ans%=mod;ans+=mod;ans%=mod;
    }
    printf("%lld\n",ans%mod);
  }
  return 0;
}
```

---

## 作者：不知名用户 (赞：5)

# Part 0 Free Talk

原题链接：[CF1264C](https://www.luogu.com.cn/problem/CF1264C)

发现好几次问题，想改但是要重审，在此放上[更好的阅读体验（实时更新）](https://www.luogu.com.cn/blog/nothavename/cf1264c-bei-fen)，原来有问题的博文占楼就不修改重审了。

看了几篇题解都没看懂，于是自己写了篇题解希望大家能看懂。如有哪里没看懂或有问题请及时私信我，我会及时回复。

# Part 1 Main

考虑[弱化版（无检查点）CF1265E](https://www.luogu.com.cn/problem/CF1265E) 怎么做。

一个人前往后走，一共有 $n$ 个镜子，第 $i$ 个镜子有 $p_i$ 的概率通过，否则回到 1。问通过第 $n$ 期望步数。

记 $f_i$ 表示通过 $i$ 的期望步数，不难发现：

$$
\begin{aligned}
& f_i=(p_i\cdot(f_{i-1}+1)+(1-p_i)\cdot(f_{i-1}+1+f_i)\\
& \iff f_i = \frac{p_i\cdot(f_{i-1}+1)+(1-p_i)\cdot(f_{i-1}+1)}{p_i}\\
& \iff f_i=\frac{f_{i-1}+1}{p_i}
\end{aligned}
$$

归纳易知 $\Large f_x=\frac{1}{p_x}+\frac{1}{p_xp_{x-1}}+\cdots+\frac{1}{p_xp_{x-1}\cdots p_1}=\sum\limits_{i=1}^x\frac{1}{\prod\limits_{j=i}^xp_j}$。

回归本题。

那么，从一个检查点 $l$ 走到（不通过）下一个检查点 $r$ 需要 $\Large \frac{1}{p_{r-1}}+\frac{1}{p_{r-1}p_{r-2}}+\cdots+\frac{1}{p_{r-1}p_{r-2}\cdots p_l}=\sum\limits_{i=l}^r\frac{1}{\prod\limits_{j=i}^rp_j}$ 步，令为 $\text{calc}_{l,r}$。

一开始 $1$ 和 $n+1$ 是天然的检查点。把 $a$ 从非检查点变成检查点，设左边第一个检查点为 $l$，右边第一个为 $r$，那么 $\text{answer}$ 变为 $\text{answer}+\text{calc}_{l,a}+\text{calc}_{a,r}-\text{calc}_{l,r}$。反之，$a$ 从检查点变为非检查点，$\text{answer}$ 变为 $\text{answer}+\text{calc}_{l,r}-\text{calc}_{l,a}-\text{calc}_{a,r}$。

# Part 2 Details

如何知道 $a$ 快速求 $l,r$？

用 `set` 维护，快达 $\Theta(\log n)$。但是我太逊了，用二分和树状数组 $\Theta(\log^2n)$。

如何在 $\Theta(1)$ 求出 $\text{calc}_{l,r}$？

$$
\begin{aligned}
& \text{calc}_{l,r}\\
= & \frac{1}{p_{r-1}}+\frac{1}{p_{r-1}p_{r-2}}+\cdots+\frac{1}{p_{r-1}p_{r-2}\cdots p_l}\\
= & (p_rp_{r+1}\cdots p_{n})(\frac{1}{p_{r-1}p_{r}\cdots p_n}+\frac{1}{p_{r-2}p_{r-1}\cdots p_n}+\cdots+\frac{1}{p_lp_{l+1}\cdots p_n})\\
= & (p_rp_{r+1}\cdots p_{n})[(\frac{1}{p_1p_2\cdots p_n}+\frac{1}{p_2p_3\cdots p_n}+\cdots+\frac{1}{p_{r-1}p_r\cdots p_n})-(\frac{1}{p_1p_2\cdots p_n}+\frac{1}{p_2p_3\cdots p_n}+\cdots+\frac{1}{p_{l-1}p_l\cdots p_n})]
\end{aligned}
$$

令 $\large\text{wt}_i=\frac{1}{p_ip_{i+1}\cdots p_n},\text{wp}_i=\text{wt}_1+\text{wt}_2+\cdots+\text{wt}_{i}$，故 $\large\text{calc}_{l,r}=\frac{1}{\text{wt}_r}\cdot(\text{wp}_{r-1}-\text{wp}_{l-1})$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10, mod = 998244353;

int c[N], st[N], n;

int p[N], wp[N], wt[N], ans;

int power(int a, int b)
{
	int c = 1, d = b, e = a;
	while(d)
	{
		if(d&1) c = c * e % mod;
		d >>= 1;
		e = e * e % mod;
	}
	return c;
}

template<typename T> T lb(T x)
{
	return x & -x;
}

void add(int a, int x)
{
	for(;a<=n+1;a+=lb(a)) c[a] += x;
}

int ask(int a)
{
	int ans = 0;
	for(;a;a-=lb(a)) ans += c[a];
	return ans;
}

int calc(int l, int r)
{
	return power(wt[r],mod-2) * (wp[r-1] - wp[l-1]) % mod;
}

signed main()
{
	int m, a, i, L, R, mid, l, r;
	int x, y;
	scanf("%lld%lld", &n, &m);
	for(i=1;i<=n;i++)
	{
		scanf("%lld", &a);
		p[i] = a * power(100,mod-2) % mod;
	}
	wt[n+1] = 1;
	for(i=n;i;i--) wt[i] = wt[i+1] * power(p[i],mod-2) % mod;
	for(i=1;i<=n;i++) wp[i] = (wp[i-1] + wt[i]) % mod;
	add(1,1);
	add(n+1,1);
	ans = wp[n];
	while(m--)
	{
		scanf("%lld", &a);
		L = 1, R = a;
		while(L < R)
		{
			mid = L + R + 1 >> 1;
			if(ask(a-1)-ask(mid-1)) L = mid;
			else R = mid - 1;
		}
		l = L;
		L = a + 1, R = n + 1;
		while(L < R)
		{
			mid = L + R >> 1;
			if(ask(mid)-ask(a)) R = mid;
			else L = mid + 1;
		}
		r = L;
		x = calc(l,a) + calc(a,r);
		y = calc(l,r);
		if(!st[a]) ans = ans - y + x, add(a,1);
		else ans = ans + y - x, add(a,-1);
		st[a] = 1 - st[a];
		ans = ((ans % mod) + mod) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：Rainbow_qwq (赞：4)



设 $f(i)$ 为将要问 $i$ ，从 $i$ 走到终点的期望步数，$f(n+1)=0$ 。

跟 CF1265E(easy version) 差不多的递推式：

$f(i)= p_i f(i+1)+(1-p_i) f(c)$，c 为 $i$ 前的第一个 check-point 。

考虑 两个 check-point 之间怎么转移。

设 $c1,c2$ 为两个相邻 check-point，$c1<c2$。

然后发现这个就是 CF1265E 中从 $1$ 走到 $n$ 的那个做法，推式子可以看[那题的题解](https://www.luogu.com.cn/blog/Rainbowsjy/solution-cf1265e)

这题可看做先走到 $c1$ ，再到 $c2-1$，中间失败退回 $c1$。

$f(c1)=f(c2)+\dfrac{1+p_{c1}+p_{c1}\times p_{c1+1}+\cdots +p_{c1}\times p_{c1+1} \cdots \times p_{c2-2}}{p_{c1}\times p_{c1+1}\times \cdots \times p_{c2-1}}$

设后面那坨东西为 $calc(c1,c2)$

可以预处理 
$$mul[x]=\prod_{i=1}^{x} p_i,sum[x]=\sum_{i=1}^{x} mul[i]$$

那么可得 
$$calc(c1,c2)=\dfrac{1+\frac{sum[c2-2]-sum[c1-1]}{mul[c1-1]}}{\frac{mul[c2-1]}{mul[c1-1]}}$$

然后，$ans=f(1)=f(1)-f(c_1)+f(c_1)-f(c_2)..+f(c_{m-1})-f(n)=calc(1,c_1)+calc(c_1,c_2)+...+calc(c_{m-1},n)$

用一个 set 维护所有 check-points 。加入一个 check-point $x$时，找到前驱预后继，然后 $ans+=calc(l,x),ans+=calc(x,r),ans-=calc(l,r)$，删除就反着来。

Code,[完整版](https://codeforces.com/contest/1264/submission/96358069)
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define mod 998244353
struct modint{
    int x;
    //...
};

/*
f[c]=f[c']+f(c,c')
f(c,c')=(1+pc+pc*pc+1+...+pc*pc+1*pc'-2)/(pc* *p c'-1)
res=f(1,c1)+f(c1,c2)+..+f(Cm,n+1)
*/
#define maxn 1000005
int n,m;
modint res,mul[maxn],sum[maxn];
set<int>s;
inline modint calc(int l,int r){
	return ((sum[r-2]-sum[l-1])/mul[l-1]+1)/mul[r-1]*mul[l-1];
}

int main()
{
	n=read(),m=read();
	mul[0]=1;
	For(i,1,n){
		modint p=read();p/=100;
		mul[i]=mul[i-1]*p;
		sum[i]=sum[i-1]+mul[i];
	}
	s.insert(1),s.insert(n+1);
	res=calc(1,n+1);
	while(m--)
	{
		int x=read();
		int l=*--s.lower_bound(x),r=*s.upper_bound(x);
		if(s.count(x))
			 res-=calc(l,x)+calc(x,r),res+=calc(l,r),s.erase(x);
		else res+=calc(l,x)+calc(x,r),res-=calc(l,r),s.insert(x);
		cout<<res.x<<endl;
	}
    return 0;
}

```


---

## 作者：Reywmp (赞：3)

- ## CF1264C 【Beautiful Mirrors with queries】

一道期望入门好题，有着非常巧妙的解法。

-----------

- ### Prelude

对于这个题面我们一眼望去会想到线性递推一个期望dp式子求解。

但是发现无法实现。

原因很明显，对于断点的修改和维护，我们并不能每次都重新 $O(n)$ 做一遍

我又想到用数据结构维护答案，但是其实大材小用了。

其实我们只需要推出一个区间的通项式来 $O(1)$ 求解即可。

这种思路其实经常存在于一些线段树的数据结构题中，推出可行的懒惰标记的 $O(1)$ 下传公式。

至少我是在 $\texttt{P6327}$ 和 $\texttt{P2122}$ 中深有这种体会。

------------

- ### Solution

推dp时，我们考虑题面中 $\text{从编号小于等于当前镜子的且最近的检查点开始提问}$ 中不难想到为了防止后效性，我们

应该定义 $f_i$ 为从 $i$ 点开始询问一直到 $n$ 点的期望值。

起初每次伤心后会从第一个点开始。则有
$$
f_i=p_i\times f_{i+1}+(100\%-p_i)\times f_1
$$
移项消元得到
$$
f_1=\frac{1}{p_n}+\frac{1}{p_n\times p_{n-1}}+\dots+\frac{1}{p_n\times p_{n-1}\times \dots\times p_{1}}
$$
毕竟 $f_1$ 就是 $f(1\rightarrow n)$  ，那么根据 期望 的线性性质我们可以引入区间 $[l,r]$ ( $l,r$ 都是复活点), 可以得到
$$
f_l-f_r=f(l\rightarrow r)=\frac{1}{p_r}+\frac{1}{p_r\times p_{r-1}}+\dots+\frac{1}{p_r\times\dots\times p_l}
$$
$$
=\frac{\prod_{i\in [l,r-1]}p_i+\prod_{i\in [l,r-2]}p_i+\dots+p_l+1}{\prod_{i=1}^rp_i/\prod_{i=1}^{l-1}p_i}
$$
那么现在我们又只需要维护：

- $\displaystyle m_x=\prod_{i=1}^{x}p_i$ (分母)；
- $\displaystyle s_x=\sum_{i=1}^xm_i$ (分子)；
- 和 $\displaystyle ans=\sum_{l,r\in \texttt{check-points}} f(l\rightarrow r)$；



每次修改的 $\texttt{check-points}$ 可以用 `set` 在 $O(\log n)$ 时间维护。

-----------

- ### Code

题面有要求求逆，而逆元可以直接用快速幂求解。

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<map>
#include<stack>
#include<set>
//#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define INL inline
//Tosaka Rin Suki~
using namespace std;

INL void read(ll &x)
{
	 x=0;ll w=1;
	 char ch=getchar();
	 while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	 if(ch=='-')w=-1,ch=getchar();
	 while(ch>='0'&&ch<='9')
	 {x=(x<<1)+(x<<3)+ch-48,ch=getchar();}
	 x*=w;
}

INL int mx(int a,int b){return a>b?a:b;}
INL int mn(int a,int b){return a<b?a:b;}

const ll MOD=998244353;
const int N=200005;

ll n,q,p;
ll prod[N],sp[N];
set <int> s;

inline ll P(ll x,ll p)
{
    ll res=1;
    while(p)
    {
        if(p&1)res=res*x%MOD;
        x=x*x%MOD;p>>=1;
    }
    return res;
}

inline ll calc(ll l,ll r)
{
    ll phi=sp[r-1]-sp[l-1]+MOD;
    if(phi>=MOD)phi-=MOD;
    return (phi*P(prod[l-1],MOD-2)%MOD+1)*P(prod[r]*P(prod[l-1],MOD-2)%MOD,MOD-2)%MOD;
}

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
    read(n);read(q);
    prod[0]=1;
    for(int i=1;i<=n;i++)
    {
        read(p);p=p*P(100,MOD-2)%MOD;prod[i]=prod[i-1]*p%MOD;
        sp[i]=(sp[i-1]+prod[i])%MOD;//维护前缀积和前缀积的前缀和
    }
    ll ans=(sp[n-1]+1)%MOD*P(prod[n],MOD-2)%MOD;
    s.insert(1);s.insert(n+1);
    for(int i=1;i<=q;i++)
    {
        read(p);
        set<int>::iterator it=s.lower_bound(p);
        if(*it==p)
        {
            int l=*(--it);
            it++;
            int r=*(++it);
            ans=ans-calc(l,p-1)+MOD;
            if(ans>=MOD)ans-=MOD;
            ans=ans-calc(p,r-1)+MOD;
            if(ans>=MOD)ans-=MOD;
            ans+=calc(l,r-1);
            if(ans>=MOD)ans-=MOD;
            s.erase(p);//非复活点
        }
        else
        {
            int l=*(--it);
            it++;
            int r=*it;
            ans=ans-calc(l,r-1)+MOD;
            if(ans>=MOD)ans-=MOD;
            ans=ans+calc(l,p-1)+MOD;
            if(ans>=MOD)ans-=MOD;
            ans+=calc(p,r-1);
            if(ans>=MOD)ans-=MOD;//参考公式
            s.insert(p);//复活点
        }
        printf("%lld\n",ans%MOD);
    }
	return 0;
}
```



---

## 作者：Lvlinxi2010 (赞：2)

### CF1265E

可以先看弱化版
[CF1265E](https://www.luogu.com.cn/problem/CF1265E)。

我们设 $f_i$ 表示从第 $i$ 面镜子开始到停止询问的期望天数，终态 $f_{n+1} = 0$。

$$f_i = P_i\times f_{i+1}+(1-P_i)\times f_1+1$$

那么我们解方程求解 $f_1$：

$$f_1 = P_1\times f_2 +(1-P_1)\times f_1 + 1$$

$$P_1\times f_1 = P_1\times f_2 +1$$

解得 $f_1=f_2+\frac{1}{P_1}$。

$$f_2 = P_2\times f_3 +(1-P_2)\times f_1 + 1$$

$$f_1 - \frac{1}{P_1}= P_2\times f_3 +(1-P_2)\times f_1 + 1$$

$$P_2\times f_1 - \frac{1}{P_1}= P_2\times f_3  + 1$$

$$P_2\times f_1 = P_2\times f_3  + 1+\frac{1}{P_1}$$

解得 $f_1=f_3+\frac{1}{P_2} + \frac{1}{P_1\times P_2}$。

以此类推：
$f_1=f_{n+1}+\frac{1}{P_n} + \frac{1}{P_{n-1}\times P_n}+\dots+\frac{1}{P_1\times P_2\times\dots\times Pn}$

解得 $f_1=\frac{1}{P_n} + \frac{1}{P_{n-1}\times P_n}+\dots+\frac{1}{P_1\times P_2\times\dots\times P_n}$。

通分得到：$f_1=\frac{1+P_1+(P_1\times P_2) + \dots +(P_1\times P_2\times \dots \times P_{n-1})}{P_1\times P_2\times\dots\times P_n}$

### CF1264C

那我们再来看本题，

我们考虑两个检查点 $A$、$B$ $(A<B)$ 之间的的情况是和弱化版中 $1$ 和 $n+1$ 的情况一样的:

$f_A=f_{B}+\frac{1}{P_{B-1}} + \frac{1}{P_{B-2}\times P_B}+\dots+\frac{1}{P_A\times P_{A+1}\times\dots\times P_{B-1}}$

令 $calc(A,B)=\frac{1}{P_{B-1}} + \frac{1}{P_{B-2}\times P_B}+\dots+\frac{1}{P_A\times P_{A+1}\times\dots\times P_{B-1}}= \frac{1+P_A+(P_A\times P_{A+1}) + \dots +(P_A\times P_{A+1}\times \dots \times P_{B-2})}{P_A\times P_{A+1}\times\dots\times P_{B-1}}$。

我们考虑维护 $a_x=\prod\limits_{i=1}^xP_i$，$s_x=\sum\limits_{i=1}^xa_i$，然后上式就可以 $\mathcal{O(1)}$ 求出了。

修改操作可以用 set 维护做到 $\mathcal{O(\log n)}$。

设要操作的检查点为 $x$，它最近的前驱节点为 $l$，最近的后继节点为 $r$。

插入时减去 $[l,r]$ 的贡献，加上 $[l,x]$ 和 $[x,r]$  的贡献，即 $ans\rightarrow ans + calc(l,x)+calc(x,r)-calc(l,r)$，删除反之。

附上代码：


```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(ll i=(a);i<=(b);i++)
#define FR(i,a,b) for(ll i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const ll MAXN = 2e5 + 10;
const ll mod = 998244353; 
ll s[MAXN],a[MAXN],p[MAXN];
set<int>st;
ll qpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
ll calc(int l,int r){
	return ((s[r-2]-s[l-1]+mod)%mod*qpow(a[l-1],mod-2)%mod+1)*a[l-1]%mod*qpow(a[r-1],mod-2)%mod;
}
int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	FL(i,1,n) scanf("%lld",&p[i]),p[i]=p[i]*qpow(100,mod-2)%mod;
	a[0]=1;
	FL(i,1,n){
		a[i]=a[i-1]*p[i]%mod;
		s[i]=(s[i-1]+a[i])%mod; 
	}
	st.insert(1),st.insert(n+1);
	ll ans=calc(1,n+1);
	while(q--){
		int x;
		scanf("%d",&x);
		int l=*(--st.lower_bound(x)),r=*st.upper_bound(x);
		if(st.find(x)==st.end()){
			ans=(ans-calc(l,r)+mod)%mod;
			ans=(ans+calc(l,x))%mod;
			ans=(ans+calc(x,r))%mod;
			st.insert(x);
		}
		else{
			ans=(ans+calc(l,r))%mod;
			ans=(ans-calc(l,x)+mod)%mod;
			ans=(ans-calc(x,r)+mod)%mod;
			st.erase(x);
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：流水行船CCD (赞：1)

期望 DP 的套路题。

让我们先考虑不带修改的情况。

设 $f_i$ 表示从起点开始问到第 $i$ 个镜子且当前镜子回答是的期望天数。

设 $g_i$ 表示从最近的检查点开始问到第 $i$ 个镜子且当前镜子回答是的期望天数。

有初始值 $f_0=g_0=0$，所求的答案即为 $f_n$。

通过分讨当前这一次询问的结果，我们不难根据定义得到基础转移：

$$
\begin{aligned}
f_i &= p_i\times(f_{i-1}+1)+(1-p_i)\times(f_{i-1}+1+g_{i})\\
g_i &= 
\left\{\begin{aligned}
&p_i\times 1+(1-p_i)\times(1+g_{i}) \\
&p_i\times(g_{i-1}+1)+(1-p_i)\times(g_{i-1}+1+g_{i})
\end{aligned}\right.\quad
\begin{aligned}
&\operatorname{i\ is\ a\ checkpoint.}\\
&\operatorname{Otherwise.}
\end{aligned}\\
\end{aligned}
$$

这个转移是有环的，根据期望题目的套路，我们将上述式子视作关于 $f_i,g_i$ 的线性方程组，进行移项消元，下面给出推导：

$\mathbf{Case\ 1}$ 当前点 $i$ 是检查点：

$$
\begin{aligned}
\because g_i &= p_i + (1-p_i) \times (1+g_i)\\
(1-(1-p_i))g_i&= 1\\
\therefore g_i&=\frac{1}{p_i}\\
\end{aligned}
$$

$$
\begin{aligned}
\because f_i &= p_i\times(f_{i-1}+1)+(1-p_i)\times(f_{i-1}+1+g_{i})\\
\therefore f_i&= f_{i-1}+1+\frac{1-p_i}{p_i}\\
\end{aligned}
$$

$\mathbf{Case 2}$ 当前点 $i$ 不是检查点：

$$
\begin{aligned}
\because g_i &= p_i\times(g_{i-1}+1)+(1-p_i)\times(g_{i-1}+1+g_{i})\\
(1-(1-p_i))g_i&= g_{i-1}+1\\
\therefore g_i&=\frac{g_{i-1}+1}{p_i}\\
\end{aligned}
$$

$$
\begin{aligned}
\because f_i &= p_i\times(f_{i-1}+1)+(1-p_i)\times(f_{i-1}+1+g_{i})\\
\therefore f_i&= f_{i-1}+1+\frac{1-p_i}{p_i} \times (g_{i-1}+1)\\
\end{aligned}
$$


接下来考虑支持动态修改：

如果你做过动态 DP 的题目，你会发现这个 DP 转移可以用矩阵乘法来描述：

$\mathbf{Case\ 1}$ 当前点 $i$ 是检查点：

$$
\begin{bmatrix}
f_{i-1},g_{i-1},1
\end{bmatrix} 
\times 
\begin{bmatrix}
1&0&0\\
0&0&0\\
1+\frac{1-p_i}{p_i}&\frac{1}{p_i}&1\\
\end{bmatrix} 
=
\begin{bmatrix}
f_{i},g_{i},1
\end{bmatrix} 
$$

$\mathbf{Case 2}$ 当前点 $i$ 不是检查点：

$$
\begin{bmatrix}
f_{i-1},g_{i-1},1
\end{bmatrix} 
\times 
\begin{bmatrix}
1&0&0\\
\frac{1-p_i}{p_i}&\frac{1}{p_i}&0\\
1+\frac{1-p_i}{p_i}&\frac{1}{p_i}&1\\
\end{bmatrix} 
=
\begin{bmatrix}
f_{i},g_{i},1
\end{bmatrix} 
$$

而矩阵乘法拥有结合律，我们用线段树维护矩阵即可支持单次 $\mathcal{O}(\log n)$ 的单点修改求 DP 值。

```cpp
/// **************************
/// @author flowing_boat
/// @date 2025 五月 09 下午6:49
/// **************************
#include <bits/stdc++.h>
using namespace std;
namespace fast_IO{
...
} using namespace fast_IO;
#define  ll long long
#define  ull unsigned long long
#define  REP(i, l, r) for (int i = l; i <= r; ++i)
#define  PER(i, l, r) for (int i = l; i >= r; --i)
#define  bitcount(x) __builtin_popcount(x)
// #define  ld cin
// #define  jyt cout
// #define  int long long
const int N = 2e5 + 7;
const int inf = 1e9 + 7;
const int P = 998244353;
namespace JoKing {
    inline long long qpow(long long x, long long y) {long long R = 1; for (; y; (x *= x) %= P, y >>= 1ll) if (y & 1ll) (R *= x) %= P; return R;}
    int n, q, op[N]; ll p[N];
    struct Mat { // o[0][0] : f | o[0][1] : g | o[0][2] : 1
        ll o[3][3];
        explicit Mat() {memset(o, 0, sizeof(o));}
        friend Mat operator * (const Mat &a, const Mat &b) {
            Mat res;
            REP(i, 0, 2) REP(j, 0, 2) res.o[i][j] = (a.o[i][0] * b.o[0][j] + a.o[i][1] * b.o[1][j] + a.o[i][2] * b.o[2][j]) % P;
            return res;
        }
    } tr[N << 2], KEY[2][N], I; // tr 为线段树维护矩阵数组
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
    inline void upd(const int x, const int l, const int r, const int now) { // 反转 now 点的状态
        if (l == r) return tr[x] = KEY[op[now] ^= 1][now], void();
        const int mid = (l + r) >> 1;
        (now <= mid ? upd(ls(x), l, mid, now) : upd(rs(x), mid + 1, r, now)), tr[x] = tr[ls(x)] * tr[rs(x)];
    }
    signed main() { int x = 0;
        ld >> n >> q, I.o[0][2] = 1; // I 是 DP 初始值
        REP(i, 1, n) { // 维护 i 不是检查点的转移矩阵 KEY[0][i] 和 i 是检查点的转移矩阵 KEY[1][i]
            ld >> p[i], (p[i] *= qpow(100, P - 2)) %= P, op[i] = (i != 1);
            KEY[0][i].o[0][0] = 1, KEY[0][i].o[1][0] = (1 - p[i] + P) % P * qpow(p[i], P - 2) % P, KEY[0][i].o[2][0] = 1 + (1 - p[i] + P) % P * qpow(p[i], P - 2) % P;
            KEY[0][i].o[1][1] = qpow(p[i], P - 2), KEY[0][i].o[2][1] = qpow(p[i], P - 2);
            KEY[0][i].o[2][2] = 1;
            KEY[1][i].o[0][0] = 1, KEY[1][i].o[2][0] = 1 + (1 - p[i] + P) % P * qpow(p[i], P - 2) % P;
            KEY[1][i].o[2][1] = qpow(p[i], P - 2);
            KEY[1][i].o[2][2] = 1;
            upd(1, 1, n, i);
        }
        REP(i, 1, q) ld >> x, upd(1, 1, n, x), jyt << (I * tr[1]).o[0][0] << '\n';
        return 0;
    }
}
signed main() {
#ifdef WYY
	freopen("code.in", "r", stdin);
	freopen("code.out", "w", stdout);
	freopen("code.err", "w", stderr);
#endif
//	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    JoKing::main(); return 0;
}
```

---

## 作者：rzh123 (赞：1)

一种更简洁的矩阵做法。  

**本题解中用 $p_i$ 表示第 $i$ 个镜子回答“是”的概率，即原题中的 $\dfrac{p_i}{100}$。**

先考虑暴力做法，类比 [CF1265E](https://www.luogu.com.cn/problem/CF1265E) 的正推做法，$f_i$ 表示从开始走到 $i$ 期望时间，发现转移的时候还需要用到从 $\lt i$ 的最近的检查点走到 $i$ 的期望时间，用 $g_i$ 表示。  

用 $flg_i$ 表示 $i$ 是否为检查点，  

$$
g_i = \begin{cases}
  0+(1-p_{i-1})\times g_i & flg_{i-1}=1 \\
  (g_{i-1}+1)+(1-p_{i-1})\times g_i & flg_{i-1}=0  \\
\end{cases}  
$$  

$$
f_i = (f_{i-1}+1)+(1-p_{i-1})*g_i
$$  

化简得：  

$$
g_i = g_{i-1}\times[flg_{i-1}=0]\times p_{i-1}+\dfrac{1}{p_{i-1}} 
$$  

$$
f_i = f_{i-1}+1+(1-p_{i-1})\times g_{i}
$$

要支持修改，用矩阵表示这个转移。  

$$
\left[ \begin{array}{l}
f_{i+1}&g_{i+1}&1
\end{array} \right]  
= \left[ \begin{array}{l}
f_{i}&g_{i}&1
\end{array} \right]
\times\left[ \begin{array}{l}
1&0&0\\
Z_i&X_i&0\\
W_i&Y_i&1
\end{array} \right]   
$$  

其中  
$$X_i=\dfrac{[flg_i=0]}{p_i} $$  
$$Y_i=\dfrac 1{p_i}$$  
$$Z_i=(1-p_i)\times X_i$$  
$$W_i=(1-p_i)\times Y_i+1$$  

用线段树维护区间矩阵乘积，支持单点修改。  

代码：  

```cpp
// https://www.luogu.com.cn/problem/CF1264C

#include <cstdio>
#include <cstring>
#include <cmath>
#include <array>
using namespace std;
constexpr int N=2e5+7,P{998244353},I100{828542813};
int n,qc,ans;
array<int,N> p,ip;
array<bool,N> flg;

inline int qp(int x,int y){
    int z{1};
    for(;y;x=1LL*x*x%P,y>>=1)
        if(y&1) z=1LL*z*x%P;
    return z;
}
inline int inv(int v){return qp(v,P-2);}

struct Mat{
    static constexpr int M=3;
    int a[M][M];
    inline void clear(){
        memset(a,0,sizeof a);
    }
    inline void unit(int v){
        for(int i{0};i<M;++i)
            for(int j{0};j<M;++j)
                a[i][j]=(i==j)*v;
    }
    inline Mat(){clear();}
    inline Mat(int _v){unit(_v);}
    inline int *operator[](unsigned i){return a[i];}
    inline const int *operator[](unsigned i)const{return a[i];}
    inline Mat operator*(const Mat &b)const{
        Mat c; c.clear();
        for(int k{0};k<M;++k)
            for(int i{0};i<M;++i)
                for(int j{0};j<M;++j)
                    c[i][j]=(c[i][j]+1LL*a[i][k]*b[k][j]%P)%P;
        return c;
    }
};

struct SegTr{
    array<Mat,(N<<2)> s;
    inline void init(int k,int i){
        auto &me=s[k];
        me.clear();
        int X=(!flg[i])*ip[i],
            Y=ip[i],
            Z=1LL*((1-p[i]+P)%P)*X%P,
            W=(1LL*((1-p[i]+P)%P)*Y+1LL)%P;
        me[0][0]=me[2][2]=1;
        me[1][0]=Z;
        me[1][1]=X;
        me[2][0]=W;
        me[2][1]=Y;
    }
    inline void pup(int k){
        s[k]=s[k<<1]*s[k<<1|1];
    }
    void build(int k,int l,int r){
        if(l==r){
            init(k,l);
            return;
        }
        int md{(l+r)>>1};
        build(k<<1,l,md),
        build(k<<1|1,md+1,r);
        pup(k);
    }
    void modify(int k,int l,int r,int x){
        if(l==r){
            init(k,x);
            return;
        }
        int md{(l+r)>>1};
        if(x<=md) modify(k<<1,l,md,x);
        else modify(k<<1|1,md+1,r,x);
        pup(k);
    }
    Mat query(){
        return s[1];
    }
}tr;

//inline int bfdp(){
//  static array<int,N> f,g;
//  f[1]=g[1]=0;
//  for(int i{2};i<=n+1;++i){
//      if(flg[i-1]) g[i]=ip[i-1];
//      else g[i]=1LL*(g[i-1]+1LL)*ip[i-1]%P;
//      f[i]=(f[i-1]+1ll+1ll*((1-p[i-1]+P)%P)*g[i]%P)%P;
//  }
//  return f[n+1];
//}

inline int dp(){
    Mat a,b;
    b=tr.query();
    a.clear(); a[0][2]=1;
    b=a*b;
    return b[0][0];
}
int main(){
    scanf("%d%d",&n,&qc);
    for(int i{1};i<=n;++i){
        scanf("%d",&p[i]);
        p[i]=1LL*p[i]*I100%P;
        ip[i]=inv(p[i]);
    }
    flg[1]=true;
    tr.build(1,1,n);
    for(int i(1);i<=qc;++i){
        int u;scanf("%d",&u);
        if(u){
            flg[u]=!flg[u];
            tr.modify(1,1,n,u);
        }
        ans=dp();
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：SJZ2010 (赞：0)

怎么只有我写了个常数巨大的矩阵做法……

参照 1265E，不难得出 dp 的转移式子（对于复活点，$dp_{i - 1}$ 当作 $0$）：

$$dp_i = \frac{100}{p_i}(dp_{i - 1} + 1)$$

然后复活点将这 $n$ 个分成了很多段，每个段分别 dp，最后加起来就行了。我们只要快速算出一个段则么则么样即可。（似乎有不用分段的，但那个没想到，以为不行）

由于有修改，我们想到动态 dp。上面这个式子显然可以矩阵维护，如下：

$$
\begin{bmatrix}
dp_{i - 1} & 1
\end{bmatrix}
\begin{bmatrix}
\frac{100}{p_i} & 0 \\
\frac{100}{p_i} & 1 \\
\end{bmatrix}
=
\begin{bmatrix}
dp_{i} & 1
\end{bmatrix}
$$

一段就是把这段里的乘起来，然后左边乘一个初始 dp 值

$$
\begin{bmatrix}
0 & 1 \\
\end{bmatrix}
$$

就是了。

于是我们用线段树维护矩阵，`set` 维护复活点，即可修改答案。但是我写的常数巨大，把矩阵写成数组然后非递归线段树终于卡进去了。

[AC](https://codeforces.com/contest/1264/submission/326091835).

---

## 作者：daniEl_lElE (赞：0)

## 思路

令 $f_i$ 为从 $i$ 期望问多少次才能到 $i+1$ 镜子。

令 $dp_i$ 为从上一个检查点到 $i$ 的 $f_i$ 之和。

以下的 $p_i$ 均表示真实概率，即给出的 $\frac{p_i}{100}$。

考虑转移，$f_i=1+(1-p_i)(dp_i+f_i)$，后面表示如果没说漂亮会回到检查点再过来。

移项，简单操作得：

$$f_i=1+(1-p_i)dp_i+(1-p_i)f_i$$

$$p_if_i=1+(1-p_i)dp_i$$

$$f_i=\frac{1}{p_i}+\frac{1-p_i}{p_i}dp_i$$

当 $i+1$ 不是检查点时，$dp_{i}=dp_{i-1}+f_i$。

当 $i+1$ 是检查点时，$dp_{i}=0$。

不难发现以上 $f_i,dp_i$ 的转移可以刻画为矩阵的形式，修改直接使用动态 dp 即可，复杂度 $O(w^3q\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1) 
using namespace std;
const int mod=998244353;
int qp(int a,int b){
	if(b<0){
		return qp(qp(a,mod-2),-b);
	}
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
struct mtx{
	int a[5][5];
}ept;
mtx mul(mtx x,mtx y){
	mtx z=ept;
	for(int i=1;i<5;i++) for(int j=1;j<5;j++) for(int k=1;k<5;k++) (z.a[i][j]+=x.a[i][k]*y.a[k][j])%=mod;
	return z;
}
mtx qp(mtx a,int b){
	mtx ans; for(int i=1;i<5;i++) for(int j=1;j<5;j++) ans.a[i][j]=(i==j);
	while(b){
		if(b&1) ans=mul(ans,a);
		a=mul(a,a);
		b>>=1; 
	}
	return ans;
}
mtx a[200005];
struct sgt{
	mtx f[1000005];
	void build(int i,int l,int r){
		if(l==r){
			f[i]=a[l];
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=mul(f[i*2],f[i*2+1]);
	}
	void change(int i,int l,int r,int pos,mtx cg){
		if(l==r){
			f[i]=cg;
			return ;
		}
		if(pos<=mid) change(i*2,l,mid,pos,cg);
		else change(i*2+1,mid+1,r,pos,cg);
		f[i]=mul(f[i*2],f[i*2+1]);
	}
}tree;
int lzt[1000005];
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int n,q; cin>>n>>q;
	int p[n+1];
	for(int i=1;i<=n;i++){
		cin>>p[i];
		(p[i]*=qp(100,-1))%=mod;
		//f dp ans 1
		a[i].a[2][1]=qp(p[i],-1)*(1+mod-p[i])%mod;
		a[i].a[4][1]=qp(p[i],-1);
		a[i].a[2][2]=(1+qp(p[i],-1)*(1+mod-p[i]))%mod;
		a[i].a[4][2]=qp(p[i],-1);
		a[i].a[2][3]=qp(p[i],-1)*(1+mod-p[i])%mod;
		a[i].a[4][3]=qp(p[i],-1);
		a[i].a[3][3]=1;
		a[i].a[4][4]=1;
	}
	tree.build(1,1,n);
	while(q--){
		int u; cin>>u;
		if(lzt[u-1]){
			a[u-1].a[2][2]=(1+qp(p[u-1],-1)*(1+mod-p[u-1]))%mod;
			a[u-1].a[4][2]=qp(p[u-1],-1);
			tree.change(1,1,n,u-1,a[u-1]);
		}
		else{
			a[u-1].a[2][2]=a[u-1].a[4][2]=0;
			tree.change(1,1,n,u-1,a[u-1]);
		}
		lzt[u-1]^=1;
		cout<<tree.f[1].a[4][3]<<"\n";
	}
}
```

---

## 作者：Terry2022 (赞：0)

来一个无脑做法。

**题意**：

长为 $n$ 的序列，每个点有权值 $a_i$ 表示有 $a_i$ 的概率能通过这一个点，否则后退至上一个标记点（包含自己），$q$ 次修改，每次将一个点 $x$ 由标记转为未标记，或由未标记转为标记，求通过这 $n$ 个点的期望步数，保证 $1$ 永远是标记点。

$n,q\le 2\times 10^5$

**思路**：

先考虑暴力 $\mathrm{dp}$，设 $f_i$ 表示通过点 $i$ 所需的期望步数，答案即为 $\sum_{i=1}^{n}f_i$，转移非常简单：$f_i=1+(1-p_i)\sum_{j=lst_i}^{i}f_j$，化简得到：$f_i=\frac{1}{p_i}+\frac{1-p_i}{p_i}\sum_{j=lst_i}^{i-1}f_j$。

还是解释一下转移：$1$ 是尝试走 $i\to i+1$，而有 $1-p_i$ 的概率会失败，然后退回 $lst_i$，然后从 $lst_i$ 再走到 $i+1$，即 $\sum_{j=lst_i}^{i}f_j$。

然后你发现修改是单点修改，而且是 $\mathrm{dp}$，直接考虑矩阵改写转移然后 $\mathrm{ddp}$。

对于非标记点 $i$，转移为：
$$
\begin{aligned}
\begin{bmatrix}
0 &\frac{1-p_i}{p_i} &\frac{1}{p_i} &0\\
0 &1+\frac{1-p_i}{p_i} &\frac{1}{p_i} &0\\
0 &0 &1 &0\\
0 &\frac{1-p_i}{p_i} &\frac{1}{p_i} &1
\end{bmatrix}
\begin{bmatrix}
f_{i-1}\\
S\\
1\\
ans
\end{bmatrix}
=
\begin{bmatrix}
f_{i}\\
S'\\
1\\
ans'
\end{bmatrix}
\end{aligned}
$$
对于标记点 $i$，转移为：
$$
\begin{aligned}
\begin{bmatrix}
0 &0 &\frac{1}{p_i} &0\\
0 &0 &\frac{1}{p_i} &0\\
0 &0 &1 &0\\
0 &0 &\frac{1}{p_i} &1
\end{bmatrix}
\begin{bmatrix}
f_{i-1}\\
S\\
1\\
ans
\end{bmatrix}
=
\begin{bmatrix}
f_{i}\\
S'\\
1\\
ans'
\end{bmatrix}
\end{aligned}
$$
然后直接线段树即可，时间复杂度为 $O(4^3n\log n)$，完全不卡常，不展开矩乘，不用 $\mathrm{zkw}$ 都可以 $\mathrm{1s}$ 内跑完，而且重点是这个做法不需要脑子，最多半个小时就能写完。

注意一点：我上面的式子是左乘（好像是这么叫的），所以线段树维护要反过来乘。

**代码**：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
const int Q=200005;
const int INF=(1<<30);
const int mod=998244353;
const int iv100=828542813;
typedef long long ll;
#define rg register int
#define cint const register int
char ibuf[1<<21],*IP1=ibuf,*IP2=ibuf;
#define gc() (IP1==IP2&&(IP2=(IP1=ibuf)+fread(ibuf,1,1<<21,stdin),IP1==IP2)?EOF:*IP1++)
inline bool ig(const char c){return c>=48&&c<=57;}
inline void read(rg&oi){char c;rg f=1,res=0;while(c=gc(),(!ig(c))&&c^'-');c^'-'?res=(c^48):f=-1;while(c=gc(),ig(c))res=res*10+(c^48);oi=f*res;}
inline void print(rg oi){char io[23];rg l=0;if(oi<0)putchar('-'),oi=~oi+1;do io[++l]=(oi%10+48);while(oi/=10);for(;l;--l)putchar(io[l]);}
inline void write(cint oi,const char c){print(oi);putchar(c);}
inline int inc(cint x,cint y){return x+y<mod?x+y:x+y-mod;}
inline int dec(cint x,cint y){return x>=y?x-y:x-y+mod;}
inline int mul(cint x,cint y){return 1ll*x*y%mod;}
inline int pow(rg x,rg y){rg res=1;for(;y;y>>=1,x=mul(x,x))if(y&1)res=mul(res,x);return res;}
inline int Inv(cint x){return pow(x,mod-2);}
int n,m,a[Q],iv[Q],v01[Q],v11[Q];bool is[Q];
struct mat{
	int a[4][4];mat()=default;
	inline void clear(){for(rg i=0;i<4;++i)for(rg j=0;j<4;++j)a[i][j]=0;}
	inline mat operator*(const mat&rhs)const{
		mat res;res.clear();
		for(rg i=0;i<4;++i)for(rg k=0;k<4;++k)for(rg j=0;j<4;++j)res.a[i][j]=inc(res.a[i][j],mul(a[i][k],rhs.a[k][j]));
		return res;
	}
	inline mat operator*=(const mat&rhs){return *this=*this*rhs;}
};
namespace Sgt{
	mat t[Q<<2];
	inline void set(cint x,cint p){
		t[x].clear();if(!is[p]){
			t[x].a[0][1]=v01[p];t[x].a[0][2]=iv[p];t[x].a[1][1]=v11[p];t[x].a[1][2]=iv[p];
			t[x].a[2][2]=t[x].a[3][3]=1;t[x].a[3][1]=v01[p];t[x].a[3][2]=iv[p];
		}
		else{t[x].a[0][2]=t[x].a[1][2]=t[x].a[3][2]=iv[p];t[x].a[2][2]=t[x].a[3][3]=1;}
	}
	inline void bld(cint l,cint r,cint x){
		if(l==r)return set(x,l);cint mid=l+r>>1;
		bld(l,mid,x<<1);bld(mid+1,r,x<<1|1);t[x]=t[x<<1|1]*t[x<<1];
	}
	inline void mdy(cint q,cint l,cint r,cint x){
		if(q>r||l>q)return;if(l==r)return set(x,l);cint mid=l+r>>1;
		mdy(q,l,mid,x<<1);mdy(q,mid+1,r,x<<1|1);t[x]=t[x<<1|1]*t[x<<1];
	}
	inline int calc(){return t[1].a[3][2];}
}
inline void mdy(cint x){is[x]^=1;Sgt::mdy(x,1,n,1);write(Sgt::calc(),'\n');}
int main(){
	read(n);read(m);for(rg i=1;i<=n;++i)read(a[i]);
	for(rg i=1;i<=n;++i)a[i]=mul(a[i],iv100),iv[i]=Inv(a[i]),v01[i]=mul(dec(1,a[i]),iv[i]),v11[i]=inc(1,v01[i]);
	is[1]=1;Sgt::bld(1,n,1);for(rg x;m--;read(x),mdy(x));
	return 0;
}
```



---

