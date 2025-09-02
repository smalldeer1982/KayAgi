# [ARC163F] Many Increasing Problems

## 题目描述

[PCT 君](https://atcoder.jp/contests/arc163/tasks/arc163_f) 出了如下题目。

> **递增问题**  
> 给定一个长度为 $N$ 的非负整数序列 $A_1,A_2,\dots,A_N$。你可以进行任意次数（也可以不进行）的如下操作：
> 
> - 选择一个满足 $1 \le i \le N$ 的整数 $i$，将 $A_i$ 增加 $1$ 或减少 $1$。
> 
> 你的目标是将 $A$ 变为广义单调递增序列。请你求出达成目标所需的最小操作次数。

PCT 君认为这个问题太简单，不适合放在比赛最后，于是将其改编如下：

> **多个递增问题**  
> 长度为 $N$ 且所有元素都在 $1$ 到 $M$ 之间的整数序列 $A$ 一共有 $M^N$ 个。对于所有这样的序列 $A$，将其对应的 **递增问题** 的答案求和，并对 $998244353$ 取模，输出结果。

请你解决 **多个递增问题**。

## 说明/提示

### 数据范围

- $1 \le N, M \le 10^5$

### 样例解释 1

长度为 $2$，所有元素在 $1$ 到 $2$ 之间的数列共有 $M^N = 4$ 个。对于每个序列 $A$，其 **递增问题** 的答案如下：
- $A=(1,1)$ 时，答案为 $0$
- $A=(1,2)$ 时，答案为 $0$
- $A=(2,1)$ 时，答案为 $1$
- $A=(2,2)$ 时，答案为 $0$

因此，答案为 $0+0+1+0=1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 2```

### 输出

```
1```

## 样例 #2

### 输入

```
6 4```

### 输出

```
14668```

## 样例 #3

### 输入

```
163 702```

### 输出

```
20728656```

## 样例 #4

### 输入

```
98765 99887```

### 输出

```
103564942```

# 题解

## 作者：Otomachi_Una_ (赞：5)

## Part 0. 前言

本题很妙。其他题解需要转下降幂或多点求值，本篇题解提供一个仅需要多项式求逆的方法，时间效率也会比其他题解快。

## Part 1. Increasing Problem 的解法

我们可以执行以下的算法：

- 维护一个集合 $S$，一开始为空。
- 遍历每个 $i\in[1,n]$ 执行以下操作：
  - 加入两个 $a_i$ 到 $S$ 当中。
  - 删除 $S$ 中的最大元素。
- 最终 $\sum a_i-\sum S$ 为答案。

具体证明可以见 CF13C。

对于 $\sum a_i$ 对所有 $a_i$ 求和应该是 $n\times m^{n-1}\times \dfrac{m\times (m+1)}{2}$。我们只要求 $\sum S$ 即可。

## Part 2. 01 序列下的 $S$

解决这类问题的关键是先推个式子。

我们只考虑 $\texttt{01}$ 序列下的 $S$。假设所有 $\leq x$ 的记为 $0$，反之记为 $1$。那么每一次操作：

- 有 $x$ 种情况让 $1$ 的个数减一，有 $m-x$ 的情况让 $1$ 加一。
- 如果当前没有 $1$ 就不会减。

我们发现后面的情况相当棘手。我们先转化问题：

- 路径从 $(0,0)$ 出发 $(n,*)$ 结束。
- 有 $x$ 条路径从 $(p,q)$ 到达 $(p+1,\max(q-1,0))$，$m-x$ 条路径从 $(p,q)$ 到 $(p+1,q+1)$。

就是 $\max$ 的条件比较棘手。我们考虑如下变换：

- 如果在 $(p,0)$ 处还要减一，那么我们在开头的时候就抬高 $1$，也就是把 $([0,p],*)$ 的路径上全部抬高 $1$。

这样子就不用考虑 $\max$ 的问题了。举个栗子：

![](https://cdn.luogu.com.cn/upload/image_hosting/9314o53o.png)

原来是蓝色的路径，在 $0$ 处有两次减。第一次我们把 $([0,2],*)$ 全部抬高 $1$，第二次我们把 $([0,5],*)$ 全部抬高 $1$。这样子我们的原路径就变成了红色路径。

这样子变换后的新路径终点坐标不会改变，起点纵坐标会增加，而且整条路径必须碰到 $y=0$ 这一条线。

这个计数就相当方便了。也就是求从 $(0,x)$ 到达 $(n,y)$ 的方案数，必须碰到 $y=0$ 但不能越过。

后面的条件可以变成 「必须不能越过 $y=-1$ 的方案数」 减去 「必须不能越过 $y=0$ 的方案数」。

这个问题是经典的反射容斥，下面会简单介绍一下：

> 反射容斥：以原问题不能经过 $y=0$ 为例。对于经过 $y=0$ 的路径，我们把它从第一次接触的地方开始按照 $y=0$ 反射过去：
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/vo3490ey.png)
>
> 这样子中点就变到了 $(n,-y)$。不难发现每条接触到 $y=0$ 的线和 $(0,x)\to (n,-y)$ 的线是一一对应的。也就是最终的条数为：
> 
> $$\left(\dbinom{n}{\dfrac{n+y-x}{2}}-\dbinom{n}{\dfrac{n+y+x}{2}}\right)\times x^{\frac{n+x-y}{2}}\times (m-x)^{\frac{n-x+y}{2}}$$
> 

我们对两个式子作差得到：
$$
\left(\dbinom{n}{\dfrac{n+y+x}{2}}-\dbinom{n}{\dfrac{n+y+x}{2}+1}\right)\times x^{\frac{n+x-y}{2}}\times (m-x)^{\frac{n-x+y}{2}}
$$
由于我们只关心终点 $y$ 的值，不关心起点 $x$。我们假设 $\dfrac{n+x-y}{2}=i$，那么 $\dfrac{n+x+y}{2}=i+y$。我们可以把上面的式子改写为：
$$
\left(\dbinom{n}{i+y}-\dbinom{n}{i+y+1}\right)\times x^i\times (m-x)^{n-i}
$$
注意到 $i$ 的取值范围为 $i\in [\left\lceil\frac{n+y}{2}\right\rceil,n-y]$。

至此我们可以得到一个多项式做法。

## Part 3. 式子的推导优化

我们把上面的式子完整写下来：
$$
\sum_{y=0}^n \sum_{i=\left\lceil\frac{n+y}{2}\right\rceil}^{n-y}\sum_{x=1}^m y\times \left(\dbinom{n}{i+y}-\dbinom{n}{i+y+1}\right)\times x^i\times (m-x)^{n-i}
$$
上面第一项 $y$ 的意思是中点有在 $(n,y)$ 的意义为有 $y$ 个数 $>x$，注意到 $x=\sum_{j=0}^\infty [j<x]$，于是我们需要把上面路径的权值记为 $y$。

首先把 $y$ 用 $j$ 来代替会让式子好看一些：
$$
\sum_{j=0}^n \sum_{i=\left\lceil\frac{n+j}{2}\right\rceil}^{n-j}\sum_{x=1}^m j\times \left(\dbinom{n}{i+j}-\dbinom{n}{i+j+1}\right)\times x^i\times (m-x)^{n-i}
$$
不难发现 $x$ 只和后面的 $x^i\times (m-x)^{n-i}$ 有关，也就是只和 $i$ 有关。我们可以记为 $F_i$。

> $F_i$ 的快速求法：注意到 $F_i=\sum_{x=1}^m x^i\times (m-x)^{n-i}$。可以改写成 $\sum_{x=1}^m (m-x)^{n}\times \left(\dfrac{x}{m-x}\right)^i$。
>
> 定义 $g_i(x)=(m-i)^n(1+\dfrac{i}{m-i}x+\left(\dfrac{i}{m-i}\right)^2x^2+\dots)=(m-i)^n\dfrac{1}{1-\frac{i}{m-i}x}$。定义 $F_i$ 的生成函数为 $F$，那么就会有 $F=g_1+g_2+\dots +g_m$。我们已经把 $g_i$ 写成了一种分式的形式，我们可以分治通分解决。

把 $i\geq \left\lceil\frac{n+j}{2}\right\rceil$ 变换成 $2i+j\geq n$，原来的式子就会变成：
$$
\sum_{j=0}^n\sum_{2i+j\geq n}^{n-j}j\times F_i\times \left(\dbinom{n}{i+j}-\dbinom{n}{i+j+1}\right)
$$
这个式子依然不好做，后面的组合数仍然不好看，我们记 $k=i+j$，把 $i$ 拉倒前面就会有：
$$
\sum_{i=0}^n \sum_{k= \max(i,n-i)}^{n} F_i\times (k-i)\times \left(\dbinom{n}{k}-\dbinom{n}{k+1}\right)
$$
我们只看 $k$，原来 $\sum _k k\times \left(\dbinom{n}{k}-\dbinom{n}{k+1}\right)$ 的部分可以用前缀和维护，原来 $\sum_k i\times \left(\dbinom{n}{k}-\dbinom{n}{k+1}\right)$ 展开后基本所有项都抵消掉了，可以直接 $\mathcal O(1)$ 求。

至此我们只需要枚举 $i$，后面的东西经过前缀和预处理都是可以 $\mathcal O(1)$ 求的。我们就完成了本题。

## Part 4. 代码实现

本题的瓶颈在于求 $F_i$，时间复杂度为 $\mathcal O(n\log^2 n)$。由于题目较复杂，这里放出完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define LL __int128
#define MP make_pair
#define vll vector<long long>
const int MAXN=4e5+5;
const int MOD=998244353;
const ll inv2=(MOD+1)/2;
namespace polynomial{// yjl poly plank 5.0 ver
int bfly[MAXN];ll inver[MAXN];
int clogg(int x){return (int)ceil(log2(x));} 
ll ksm(ll a,int b){ll res=1;while(b){if(b&1)res=res*a%MOD;a=a*a%MOD,b>>=1;}return res;}
void butterfly(int l){
	static int las;
	if(las!=l){
		las=l; 
		for(int i=1;i<(1<<l);i++)
			bfly[i]=(bfly[i>>1]>>1)|((i&1)<<l-1);
	} 
}
void NTT(vll &f,int l,int typ){
	butterfly(l);f.resize(1<<l);
	for(int i=0;i<(1<<l);i++)
		if(bfly[i]<i) swap(f[i],f[bfly[i]]);
	for(int i=0;i<l;i++){
		ll step=ksm(3,MOD-1+(MOD-1>>i+1)*typ);
		for(int j=0;j<(1<<l);j+=(1<<i+1)){
			ll cur=1,l=j+(1<<i);
			for(int k=j;k<l;k++){
				ll u=f[k],v=f[k|(1<<i)]*cur%MOD;
				f[k]=(u+v>MOD?u+v-MOD:u+v);
				f[k|(1<<i)]=(u>=v?u-v:u-v+MOD);
				cur=cur*step%MOD;
			}
		}
	}
	if(typ==-1){
		ll val=ksm(1<<l,MOD-2);
		for(int i=0;i<(1<<l);i++)
			f[i]=val*f[i]%MOD;
	}
	return;
}
vll operator *(vll f,vll g){
	int n=f.size()+g.size(),l=clogg(f.size()+g.size());
	if(n<=64){
		vll h(n-1);
		for(int i=0;i<f.size();i++)
			for(int j=0;j<g.size();j++)
				h[i+j]+=f[i]*g[j]%MOD;
		for(ll &i:h) i%=MOD;
		return h;
	}
	NTT(f,l,1);NTT(g,l,1);
	for(int i=0;i<(1<<l);i++)
		f[i]=f[i]*g[i]%MOD;
	NTT(f,l,-1);f.resize(n-1);
	return f;
}
vll operator +(vll f,vll g){
	int n=max(f.size(),g.size());
	f.resize(n);g.resize(n);
	for(int i=0;i<n;i++)
		f[i]=(f[i]+g[i]>=MOD?f[i]+g[i]-MOD:f[i]+g[i]);
	return f;
}
vll inv(vll f,int st=1){
	int n=f.size(),l=clogg(n);
	f.resize(1<<l);
	vll g{ksm(f[0],MOD-2)},_f;
	for(int i=st;i<=l;i++){
		_f=vll(begin(f),begin(f)+(1<<i));
		NTT(g,i+1,1);NTT(_f,i+1,1);
		for(int j=0;j<(1<<i+1);j++)
			g[j]=(2*g[j]-g[j]*g[j]%MOD*_f[j]%MOD+MOD)%MOD;
		NTT(g,i+1,-1);
		fill(begin(g)+(1<<i),end(g),0);
	}
	g.resize(n);
	return g;
}
vll integ(vll f){
	int n=f.size();f.resize(n+1);
	if(!inver[1]){
		for(int i=1;i<MAXN;i++) inver[i]=ksm(i,MOD-2);
	}
	for(int i=n;i>=1;i--) f[i]=f[i-1]*inver[i]%MOD;
	f[0]=0;
	return f;
}
vll diff(vll f){
	int n=f.size();
	for(int i=0;i<n-1;i++)
		f[i]=f[i+1]*(i+1)%MOD;
	f.pop_back();
	return f;
} 
vll ln(vll f){
	vll f_=diff(f),_f=inv(f);
	int n=f_.size(),m=_f.size();
	int l=clogg(n+m);
	NTT(f_,l,1);NTT(_f,l,1);
	for(int i=0;i<(1<<l);i++)
		f_[i]=f_[i]*_f[i]%MOD;
	NTT(f_,l,-1);
	f_=integ(f_);
	f_.resize(f.size());
	return f_;
}
vll exp(vll f){
	vll g{1},_f,_g;
	int n=f.size(),l=clogg(n);
	f.resize(1<<l);
	for(int i=1;i<=l;i++){
		_f=vll(begin(f),begin(f)+(1<<i));
		_g=ln(g);
		NTT(g,i+1,1);NTT(_f,i+1,1);NTT(_g,i+1,1);
		for(int j=0;j<(1<<i+1);j++)
			g[j]=g[j]*(1-_g[j]+_f[j]+MOD)%MOD;
		NTT(g,i+1,-1);
		fill(begin(g)+(1<<i),end(g),0);
	}
	g.resize(n);
	return g;
}
vll sqrt(vll f){
	vll g{1},_f,_g;
	int n=f.size(),l=clogg(n);
	f.resize(1<<l);
	for(int i=1;i<=l;i++){
		_f=vll(begin(f),begin(f)+(1<<i));
		_g=inv(g);
		NTT(_f,i+1,1);NTT(_g,i+1,1);NTT(g,i+1,1);
		for(int j=0;j<(1<<i+1);j++)
			g[j]=(_f[j]+g[j]*g[j]%MOD)*inv2%MOD*_g[j]%MOD;
		NTT(g,i+1,-1);
		fill(begin(g)+(1<<i),end(g),0);
	}
	g.resize(n);
	return g;
} 
void div(vll f,vll g,vll &q,vll &r){// 构造 p,q 使得 f=g*q+r; 
	int n=f.size()-1,m=g.size()-1;
	reverse(f.begin(),f.end());
	reverse(g.begin(),g.end());
	g.resize(n+1);
	q=(f*inv(g));q.resize(n-m+1);
	reverse(q.begin(),q.end());
	g.resize(m+1);
	reverse(g.begin(),g.end());
	reverse(f.begin(),f.end());
	vll h=q*g;
	r.resize(m);
	for(int i=0;i<m;i++) r[i]=(f[i]-h[i]+MOD)%MOD;
	return;
}
vll eval(vll f,vll x){
	vector<vll> func; map<pair<int,int>,int> mp;
	function<vll(int,int)> prod=[&](int l,int r){
		vll ans;
		if(l==r) ans=(vll){MOD-x[l],1};
		else {
			int mid=l+r>>1;
			ans=prod(l,mid)*prod(mid+1,r);
		} 
		func.push_back(ans);
		mp[MP(l,r)]=func.size()-1;
		return ans;
	};prod(0,x.size()-1);
	int t=-1;
	function<vll(vll,int,int)> solve=[&](vll f,int l,int r){
		if(l==r){
			ll val=0;
			for(int i=f.size()-1;i>=0;i--)
				val=(val*x[l]+f[i])%MOD;
			return (vll){val};
		}
		int mid=l+r>>1;
		vll p0=func[mp[MP(l,mid)]],p1=func[mp[MP(mid+1,r)]];
		vll d,q;
		div(f,p0,d,q);
		vll ans=solve(q,l,mid);
		div(f,p1,d,q);
		vll _ans=solve(q,mid+1,r);
		for(int i:_ans) ans.push_back(i);
		return ans;
	};
	return solve(f,0,x.size()-1);
}
}using namespace polynomial;
ll fac[MAXN],inf[MAXN];ll n,m; 
ll f[MAXN],s[MAXN];
ll C(int x,int y){return (x<0||x>y?0:fac[y]*inf[x]%MOD*inf[y-x]%MOD);} 
ll solve(){
	ll ans=0;
	function<pair<vll,vll>(int,int)> solve=[&](int l,int r){
		if(l==r){return MP(vll{ksm(l,n)},vll{1,MOD-(m-l)*ksm(l,MOD-2)%MOD});} 
		int mid=l+r>>1;
		pair<vll,vll> ls=solve(l,mid),rs=solve(mid+1,r);
		return MP(ls.first*rs.second+ls.second*rs.first,ls.second*rs.second);
	};
	pair<vll,vll> pv=solve(1,m);
	pv.second.resize(n);
	vll f=pv.first*inv(pv.second);f.resize(n+1);
	for(int i=n;i>=1;i--)
		s[i]=(s[i+1]+i*(C(i,n)-C(i+1,n)+MOD))%MOD;
	for(int j=0;j<=n;j++){
		int i=max(j,(int)n-j);
		ans+=(s[i]-j*C(i,n)%MOD+MOD)%MOD*f[j]%MOD;
	}
	return ans%MOD;
}
int main(){
	ios::sync_with_stdio(false);
	fac[0]=inf[0]=1;
	for(int i=1;i<MAXN;i++) inf[i]=ksm(fac[i]=fac[i-1]*i%MOD,MOD-2);
	cin>>n>>m;
	cout<<((m*(m+1)/2%MOD)*ksm(m,n-1)%MOD*n%MOD-solve()+MOD)%MOD;
	return 0;
}
```



---

## 作者：Leasier (赞：5)

~~原问题是一个相当经典的贪心题（~~

设新序列中存在一个值 $t \in [1, m)$，若我们把原序列中 $\leq t, > t$ 的分别标记为 $0, 1$（设该序列为 $b$），我们的目标是用最小操作次数让新序列变得有序。

感性地，可以发现原问题的答案等价于转化为 $m - 1$ 个上述问题答案之和。

不妨来回忆一下原问题的贪心做法：

- 抓出一个大根堆，初始为空。
- 将当前 $a_i$ 入堆。
- 若堆顶 $> a_i$，将答案加上堆顶 $- a_i$，弹出堆顶后将当前 $a_i$ 入堆。

考虑仿照原问题的贪心做法执行下面这个过程：

- 初始位于 $(0, 0)$。
- 若 $b_i = -1$，从 $(i - 1, y)$ 移到 $(i, \max(y - 1, 0))$；若 $b_i = 1$，从 $(i - 1, y)$ 移到 $(i, y + 1)$。
- 答案为斜率为 $-1$ 的段数之和。

考虑钦定在 $(j, y)$ 处向下，则从它向上开始包含一段**不包含**在 $x$ 轴行走的从 $(i, y)$ 走到 $(j, y)$ 的路径，此时：

- $j - i > 0$ 为偶数。
- 第一步向上、最后一步向下（为了只在每一小段的起点和终点讨论）。
- 其中**恰好一半**的步数向下，即贡献为 $\frac{j - i}{2}$。

于是贡献由如下部分构成：

- 钦定起终点：$h_{\frac{j - i}{2} - 1}$，其中 $h$ 表示卡特兰数。
- 钦定中间的值：$(t(m - t))^{\frac{j - i}{2}}$。
- 钦定外面的值：$m^{n - (j - i)}$。

即答案为 $\displaystyle\sum_{1 \leq i < j \leq n, (j - i) \bmod 2 = 0} h_{\frac{j - i}{2} - 1} (t(m - t))^{\frac{j - i}{2}} m^{n - (j - i)}$。

考虑枚举 $k = \frac{j - i}{2}$，得 $\displaystyle\sum_{k = 1}^{\lfloor \frac{n}{2} \rfloor} (n - 2k + 1) h_{k - 1} (t(m - t))^k m^{n - 2k}$。

注意到这个东西实际上是关于 $t(m - t)$ 的 $\lfloor \frac{n}{2} \rfloor$ 次多项式，于是我们直接上多项式多点求值即可。时间复杂度为 $O(n \log n + m \log^2 n)$。

代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

typedef struct {
	int n;
	ll a[262147];
	
	inline void clear(int limit){
		for (register int i = n + 1; i < limit; i++){
			a[i] = 0;
		}
	}
} Polynomial;

typedef struct {
	int l;
	int r;
	vector<ll> v;
} Node;

const int mod = 998244353, mod_g = 3, mod_g_inv = 332748118;
Polynomial f, L, R, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
int rev[262147];
ll h[100007], power[100007], query[100007], save[100007];
Polynomial level[27];
Node tree[400007];

inline void init1(int n){
	int m = n >> 1;
	for (register int i = 1; i < n; i++){
		rev[i] = rev[i >> 1] >> 1;
		if (i & 1) rev[i] += m;
	}
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void NTT(Polynomial &a, int limit, int type){
	for (register int i = 0; i < limit; i++){
		if (i < rev[i]) swap(a.a[i], a.a[rev[i]]);
	}
	for (register int i = 1; i < limit; i <<= 1){
		int j = i << 1;
		ll wn = quick_pow(type == 1 ? mod_g : mod_g_inv, (mod - 1) / j, mod);
		for (register int k = 0; k < limit; k += j){
			int r = k + i;
			ll w = 1;
			for (register int l = k; l < r; l++){
				int x = l + i;
				ll y = a.a[l], z = w * a.a[x] % mod;
				a.a[l] = (y + z) % mod;
				a.a[x] = ((y - z) % mod + mod) % mod;
				w = w * wn % mod;
			}
		}
	}
	if (type == -1){
		ll inv_limit = quick_pow(limit, mod - 2, mod);
		for (register int i = 0; i < limit; i++){
			a.a[i] = a.a[i] * inv_limit % mod;
		}
	}
}

void operator *=(Polynomial &a, Polynomial &b){
	int limit = 1, t = a.n + b.n;
	while (limit <= t) limit <<= 1;
	init1(limit);
	a.clear(limit);
	a.n = t;
	temp1.n = b.n;
	temp1.clear(limit);
	for (register int i = 0; i <= b.n; i++){
		temp1.a[i] = b.a[i];
	}
	NTT(a, limit, 1);
	NTT(temp1, limit, 1);
	for (register int i = 0; i < limit; i++){
		a.a[i] = a.a[i] * temp1.a[i] % mod;
	}
	NTT(a, limit, -1);
}

void operator -=(Polynomial &a, Polynomial &b){
	if (a.n < b.n){
		a.clear(b.n + 1);
		a.n = b.n;
	}
	for (register int i = 0; i <= b.n; i++){
		a.a[i] = ((a.a[i] - b.a[i]) % mod + mod) % mod;
	}
}

inline void init2(int n, int m){
	h[0] = 1;
	for (register int i = 1; i <= n; i++){
		h[i] = h[i - 1] * (i * 4 - 2) % mod * quick_pow(i + 1, mod - 2, mod) % mod;
	}
	power[0] = 1;
	for (register int i = 1; i <= n; i++){
		power[i] = power[i - 1] * m % mod;
	}
}

inline void update(int x){
	int ls = x * 2, rs = x * 2 + 1;
	L.n = tree[ls].v.size() - 1;
	for (register int i = 0; i <= L.n; i++){
		L.a[i] = tree[ls].v[i];
	}
	R.n = tree[rs].v.size() - 1;
	for (register int i = 0; i <= R.n; i++){
		R.a[i] = tree[rs].v[i];
	}
	L *= R;
	tree[x].v.clear();
	for (register int i = 0; i <= L.n; i++){
		tree[x].v.push_back(L.a[i]);
	}
}

void build(int x, int l, int r, ll query[]){
	tree[x].l = l;
	tree[x].r = r;
	if (l == r){
		tree[x].v.clear();
		tree[x].v.push_back((mod - query[l]) % mod);
		tree[x].v.push_back(1);
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid, query);
	build(x * 2 + 1, mid + 1, r, query);
	update(x);
}

inline void transform(int x, Polynomial &a){
	a.n = tree[x].v.size() - 1;
	for (register int i = 0; i <= a.n; i++){
		a.a[i] = tree[x].v[i];
	}
}

inline void reverse(Polynomial &a, Polynomial &b){
	b.n = a.n;
	for (register int i = 0; i <= a.n; i++){
		b.a[i] = a.a[a.n - i];
	}
}

void inv(Polynomial &a, Polynomial &b, int len){
	if (len == 0){
		b.n = 0;
		b.a[0] = quick_pow(a.a[0], mod - 2, mod);
		return;
	}
	int limit = 1, t1 = len / 2, t2 = len + t1 * 2;
	inv(a, b, t1);
	while (limit <= t2) limit <<= 1;
	init1(limit);
	b.clear(limit);
	b.n = temp2.n = len;
	temp2.clear(limit);
	for (register int i = 0; i <= len; i++){
		temp2.a[i] = a.a[i];
	}
	NTT(b, limit, 1);
	NTT(temp2, limit, 1);
	for (register int i = 0; i < limit; i++){
		b.a[i] = (b.a[i] * (2 - b.a[i] * temp2.a[i] % mod) % mod + mod) % mod;
	}
	NTT(b, limit, -1);
}

inline void divide(Polynomial &a, Polynomial &b, Polynomial &c, Polynomial &d){
	if (a.n < b.n) return;
	int len = a.n - b.n;
	reverse(a, temp3);
	temp3.n = len;
	reverse(b, temp4);
	temp4.n = len;
	inv(temp4, temp5, len);
	temp3 *= temp5;
	temp3.n = len;
	reverse(temp3, c);
	temp6.n = b.n;
	for (register int i = 0; i <= b.n; i++){
		temp6.a[i] = b.a[i];
	}
	temp6 *= c;
	d.n = a.n;
	for (register int i = 0; i <= a.n; i++){
		d.a[i] = a.a[i];
	}
	d -= temp6;
	d.n = max(b.n - 1, 0);
}

void solve(int x, int depth, ll ans[]){
	if (depth > 0){
		transform(x, temp7);
		divide(level[depth - 1], temp7, temp8, level[depth]);
	}
	if (tree[x].l == tree[x].r){
		ans[tree[x].l] = level[depth].a[0];
		return;
	}
	int depth_i = depth + 1;
	solve(x * 2, depth_i, ans);
	solve(x * 2 + 1, depth_i, ans);
}

inline void evaluate(Polynomial &a, int n, ll query[], ll ans[]){
	build(1, 1, n, query);
	transform(1, temp7);
	if (a.n < n) a.n = n;
	divide(a, temp7, temp8, level[0]);
	solve(1, 0, ans);
}

int main(){
	int n, m;
	cin >> n >> m;
	if (m == 1){
		cout << 0;
		return 0;
	}
	ll ans = 0;
	f.n = n / 2;
	init2(n, m);
	for (register int i = 1; i <= f.n; i++){
		f.a[i] = h[i - 1] * (n - i * 2 + 1) % mod * power[n - i * 2] % mod;
	}
	for (register int i = 1; i < m; i++){
		query[i] = (ll)i * (m - i) % mod;
	}
	evaluate(f, m - 1, query, save);
	for (register int i = 1; i < m; i++){
		ans = (ans + save[i]) % mod;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Kevin090228 (赞：4)

## F

**Increasing Problem** 是 CF13C 的加强版。具体的做法是：

```
for i in [1,n]
    add a[i] into set
    add a[i] into set
    delete largest number from set
answer = sum of a[i] - sum of numbers in set
```

在新问题中，`sum of a[i]` 是好求的，考虑如何求 `sum of numbers in set`。我们对于每个数 $x\in [1,m]$ 计算它对答案的贡献。光考虑 $x$ 的出现总次数再乘 $x$ 不方便计算，我们可以转化为每次求 $\geq x$ 的数的出现次数，然后再全部相加。

我们将 $\geq x$ 的 $a_i$ 看做 $1$，$<x$ 的看做 $0$。$[1,n]$ 中的每个时刻，有 $x$ 种情况中 $1$ 的个数会增加 $1$，剩余的 $m-x$ 种情况中 $1$ 的个数会减少 $1$。当然，在原个数为 $0$ 时个数不减少。我们令 $f(i,j)$ 表示考虑到第 $i$ 个时刻，$1$ 有 $j$ 个的方案数。容易发现，$f(i,j)$ 其实是一个关于 $x$ 的多项式。

在原个数为 $0$ 时个数不减少这件事比较难办，我们可以在每个这样的时刻，令这个时刻前的每个时刻 $1$ 的个数增加 $1$。形象点说，我们在时刻 $0$ 变出一个虚拟的 $1$ 来应对这一次操作。这时我们不要求 $0$ 时刻个数为 $0$，但是必须存在一个时刻的个数为 $0$。

这时我们能转化为一个网格图上路径问题：

- 路径的起点是 $(0,*)$，终点是 $(n,*)$。
- 从 $(a,b)$ 有 $x$ 种可能走到 $(a+1,b+1)$，有 $m-x$ 种可能走到 $(a+1,b-1)$。
- 路径上至少有一个 $(*,0)$ 点且所有点纵坐标均非负。

令 $W_i$ 表示终点为 $(n,i)$ 的路径个数，最终需要求的总出现次数就是 $\sum iW_i$。

路径上至少有一个 $(*,0)$ 点这个条件不太好处理。我们可以容斥掉它，具体地，令 $W^0_i$ 表示所有点纵坐标非负的方案数，$W_i^1$ 表示所有点纵坐标 $\geq 1$ 的方案数，有 $W_i=W_i^0-W_i^1$。

对于 $W_i^0$ 和 $W_i^1$ 的求法，我们有经典的反射容斥。推一推式子可以得到：
$$
W_i^0=\sum\limits_{\frac{n-i}{2}\leq j\leq n}x^j(m-x)^{n-j}\left[\binom{n}{j}-\binom{n}{i+j+1}\right]
$$
类似地，有：
$$
W_i^1=\sum\limits_{\frac{n-i}{2}\leq j\leq n}x^j(m-x)^{n-j}\left[\binom{n}{j}-\binom n{i+j}\right]
$$


作差可得：
$$
W_i=W_i^0-W_i^1=\sum\limits_{\frac{n-i}{2}\le j\le n}x^j(m-x)^{n-j}\left[\binom n{i+j}-\binom n{i+j+1}\right]
$$
将 $W_i$ 代回总出现次数的式子可得：
$$
\sum iW_i=\sum\limits_{i=0}^nx^i(m-x)^{n-i}\sum\limits_{j\geq \max(i,n-i)}(j-i)\left[\binom n j-\binom n {j+1}\right]
$$
这个式子显然可以 $O(n^2)$ 求，然后求出自然数幂前缀和代入计算，就可以得到一个 $O(n^2)$ 的做法。

考虑使用多项式优化这个东西。第二个和式的值可以拆成 $F(k_i)+G(k_i)i$ 的形式，其中 $k_i=\max(i,n-i)$，$F$ 和 $G$ 都是可以线性预处理的后缀和数组。转化一手，有：
$$
\sum iW_i=\sum\limits_{i=0}^nx^im^{n-i}\sum\limits_{j=0}^i\binom i j(-1)^{i-j}\left[F(k_j)+G(k_j)j\right]
$$
这个东西显然可以卷积，所以我们以 $O(n\log n)$ 的复杂度求出答案多项式的系数。我们现在还需要求 $x$ 取 $[1,m]$ 时多项式值的和。可以将多项式转成下降幂然后做前缀和，最后将 $m$ 代入求值即可。

时间复杂度 $O(n\log^2 n)$。

---

## 作者：DaiRuiChen007 (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc163_f)

**题目大意**

> 对于每个长度为 $n$，值域为 $[1,m]$ 的序列求 [CF13C](https://www.luogu.com.cn/problem/CF13C) 的答案。
>
> 数据范围：$n,m\le 10^5$。

**思路分析**

考虑那一题的反悔贪心做法：给大根堆中加入两个 $a_i$ 然后弹出堆顶，答案为 $\sum a$ 减去最终堆中元素和 $S$。

$\sum a$ 容易求，只要知道每种情况中最终堆里的元素之和。

很自然考虑堆里 $>k$ 的元素数量，转 01 序列，此时有 $m-k$ 个 $1$ 和 $k$ 个 $0$。

每当我们向堆中加入一个 $1$，那么 $S\gets S+1$，否则 $S\gets \max(S-1,0)$。

可以把 $S$ 的变化看成从 $(0,0)$ 到 $(n,i)$ 的格路，贡献为 $i$，但是 $S=0$ 时不下降是一个很棘手的条件。

我们不妨把令该格路在 $S=0$ 的时候下降，那么贡献就是 $i-x$，其中 $x$ 表示路径最低点。

不妨重设 $x$ 为 $y$ 轴，那么格路变成 $(0,x)\to (n,y)$，贡献为 $y$ 且经过 $y=0$ 不经过 $y=-1$。

路径数可以反射容斥，用不经过 $y=-1$ 的路径数减去不经过 $y=0$ 的路径数得到：
$$
\left(\binom{n}{\dfrac{n+x-y}{2}}-\binom{n}{\dfrac{n+x+y+2}{2}}\right)-\left(\binom {n}{\dfrac{n+x-y}{2}}-\binom {n}{\dfrac{n+x+y}{2}}\right)\\
=\binom{n}{\dfrac{n+x+y}2}-\binom{n}{\dfrac{n+x+y+2}2}
$$
记 $i=\dfrac{n+x-y}2$ 表示填入 $0$ 的数量，由于 $y\ge x$，那么要求 $\dfrac{n-y}2\le i\le n$。

那么答案就是：
$$
\mathrm{Ans}=\sum_{k=0}^{m-1}\sum_i k^i(m-k)^{n-i}\sum_yy\left(\binom{n}{i+y}-\binom{n}{i+y+1}\right)\\
$$

设 $i+y=j$，则 $j\ge i,j\ge n-i$，记 $j_0=\max(i,n-i)$那么后面一部分的贡献 $g_i$ 就是：
$$
\begin{aligned}
g_i&=\sum_{j\ge j_0} (j-i)\left(\binom{n}{j}-\binom{n}{j+1}\right)\\
&=\sum_{j\ge j_0}\left(j\binom{n}{j}-j\binom{n}{j+1}\right)-i \sum_{j\ge j_0} \left(\binom{n}{j}-\binom{n}{j+1}\right)\\
&=(j_0-i)\binom n{j_0}-\sum_{j>j_0}\binom nj
\end{aligned}
$$
预处理组合数后缀和即可。

现在问题转化为对于每个 $i\in[0,n)$ 求出：
$$
\begin{aligned}
f_i
&=\sum_{k=0}^{m-1} k^i(m-k)^{n-i}\\
&=\sum_{k=0}^{m-1} (m-k)^n\left(\dfrac{k}{m-k}\right)^i\\
&=\sum_{k=0}^{m-1} (m-k)^n[z^i]\dfrac{1}{1-\dfrac{k}{m-k}z}\\
&=\sum_{k=0}^{m-1} (m-k)^n[z^i]\dfrac{m-k}{m-k-kz}
\end{aligned}
$$
因此：
$$
\sum f_iz^i=\sum_{k=0}^{m-1}\dfrac{(m-k)^{n+1}}{m-k-kz}
$$
可以用分治 NTT 维护通分相加的过程，最后多项式求逆把分母除掉，就能求出 $f_i$ 的生成函数。

时间复杂度 $\mathcal O(n\log n+m\log ^2m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Polynomial {
const int MOD=998244353,N=1<<18,G=3;
int rev[N],inv[N],w[N<<1];
int ksm(int a,int b=MOD-2,int p=MOD) {
	int ret=1;
	for(;b;a=1ll*a*a%p,b=b>>1) if(b&1) ret=1ll*ret*a%p;
	return ret;
}
void poly_init() {
	inv[1]=1;
	for(int i=2;i<N;++i) inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
	for(int k=1;k<=N;k<<=1) {
		int x=ksm(G,(MOD-1)/k); w[k]=1;
		for(int i=1;i<k;++i) w[i+k]=1ll*x*w[i+k-1]%MOD;
	}
}
int plen(int x) { int y=1; for(;y<x;y<<=1); return y;  }
void ntt(int *f,bool idft,int n) {
	for(int i=0;i<n;++i) {
		rev[i]=(rev[i>>1]>>1);
		if(i&1) rev[i]|=n>>1;
	}
	for(int i=0;i<n;++i) if(rev[i]<i) swap(f[i],f[rev[i]]);
	for(int k=2,x,y;k<=n;k<<=1) {
		for(int i=0;i<n;i+=k) {
			for(int j=i;j<i+k/2;++j) {
				x=f[j],y=1ll*f[j+k/2]*w[k+j-i]%MOD;
				f[j]=(x+y>=MOD)?x+y-MOD:x+y,f[j+k/2]=(x>=y)?x-y:x+MOD-y;
			}
		}
	}
	if(idft) {
		reverse(f+1,f+n);
		for(int i=0,x=ksm(n);i<n;++i) f[i]=1ll*f[i]*x%MOD;
	}
}
void poly_inv(const int *f,int *g,int n) {
	static int a[N];
	g[0]=ksm(f[0]);
	int k=2;
	for(;k<(n<<1);k<<=1) {
		for(int i=0;i<k;++i) a[i]=f[i];
		ntt(g,0,k<<1),ntt(a,0,k<<1);
		for(int i=0;i<(k<<1);++i) {
			g[i]=(2-1ll*a[i]*g[i]%MOD)*g[i]%MOD;
			if(g[i]<0) g[i]+=MOD;
		}
		ntt(g,1,k<<1);
		memset(g+k,0,sizeof(int)*k);
	}
	memset(g+n,0,sizeof(int)*(k-n));
	memset(a,0,sizeof(int)*k);
}
}
const int MOD=998244353,N=1<<18;
using Polynomial::ntt;
using Polynomial::ksm;
using Polynomial::plen;
int n,m,bi[N],sum[N],f[N],g[N],a[N],b[N],c[N],d[N],p[N],q[N];
void solve(int l,int r) { //2l~2r-1
	if(l==r) {
		f[2*l]=ksm(m-l,n+1),g[2*l]=m-l,g[2*l+1]=MOD-l;
		return ;
	}
	int mid=(l+r)>>1,len=plen(r-l+2);
	solve(l,mid),solve(mid+1,r);
	for(int i=0;i<=mid-l+1;++i) a[i]=f[2*l+i],b[i]=g[2*l+i];
	for(int i=0;i<=r-mid;++i) c[i]=f[2*(mid+1)+i],d[i]=g[2*(mid+1)+i];
	ntt(a,0,len),ntt(b,0,len),ntt(c,0,len),ntt(d,0,len);
	for(int i=0;i<len;++i) {
		p[i]=(1ll*a[i]*d[i]+1ll*b[i]*c[i])%MOD;
		q[i]=1ll*b[i]*d[i]%MOD;
	}
	ntt(p,1,len),ntt(q,1,len);
	for(int i=0;i<=r-l+1;++i) f[2*l+i]=p[i],g[2*l+i]=q[i];
	for(int i=2*l+(r-l+1)+1;i<=2*r+1;++i) f[i]=g[i]=0;
	memset(a,0,sizeof(int)*len);
	memset(b,0,sizeof(int)*len);
	memset(c,0,sizeof(int)*len);
	memset(d,0,sizeof(int)*len);
	memset(p,0,sizeof(int)*len);
	memset(q,0,sizeof(int)*len);
}
signed main() {
	Polynomial::poly_init();
	scanf("%d%d",&n,&m);
	bi[0]=1;
	for(int i=1;i<=n;++i) bi[i]=1ll*bi[i-1]*(n-i+1)%MOD*ksm(i)%MOD;
	for(int i=n;~i;--i) sum[i]=(sum[i+1]+bi[i])%MOD;
	solve(0,m-1);
	for(int i=0;i<=min(m,n-1);++i) a[i]=f[i],b[i]=g[i];
	Polynomial::poly_inv(b,c,n);
	int len=plen(2*n);
	ntt(a,0,len),ntt(c,0,len);
	for(int i=0;i<len;++i) d[i]=1ll*a[i]*c[i]%MOD;
	ntt(d,1,len);
	for(int i=0;i<n;++i) f[i]=d[i];
	int ans=1ll*m*(m+1)/2%MOD*n%MOD*ksm(m,n-1)%MOD;
	for(int i=0;i<n;++i) {
		int k=max(i,n-i);
		ans=(ans+MOD-(sum[k+1]+1ll*(k-i)*bi[k])%MOD*f[i]%MOD)%MOD;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：1)

真是神仙题呀，看完题面的第一反应居然觉得是缝合怪，还是太菜了。

Increasing Problem 的标准做法是 slope trick，考虑前 $i$ 个数之后得到的分段函数是 $G_i(x)$，则令 $F_{i}(x)=G_{i-1}(x)+|a_i-x|$，然后让 $F_i(x)$ 做一下前缀取 $\min$ 就可以得到 $G_i(x)$ 了。

就是：

```cpp
#include<bits/stdc++.h>
#define endl '\n'

using namespace std;
typedef long long ll;

const int N=1e6+10;
int a[N],n,b[N];ll ans;
priority_queue < int > S;

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];S.push(a[i]);
		if(S.top()>a[i]){int x=S.top();S.pop();ans+=x-a[i];S.push(a[i]);}
		b[i]=S.top();
	}
	cout<<ans<<endl;
	return 0;
}
```

思考 Many Increasing Problems 能不能类似做？

$n,m\le 10^5$ 有点吓人。

发现本质上算的是 $\sum a_i-\sum\limits_{x\in S}x$，$\sum a_i$ 是容易算的，考虑计算 $\sum\limits_{x\in S} x$。

形式化地考虑 $S$ 是怎么算的：

1. 朝 $S$ 中加入两个 $a_i$。
2. 弹出 $S$ 的最大值。

发现还是不好做，如果序列只有 $01$ 就好了。

考虑差分计算，将数列中 $\le x$ 的部分变成 $0$，$> x$ 的部分变成 $1$，那么每次有 $x$ 种方法令 $S$ 减少一个 $1$，有 $m-x$ 种方法使 $S$ 多一个 $1$。

考虑转到网格上，坐标 $(a,b)$ 表示考虑了前 $a$ 个点，目前有 $b$ 个 $1$，那么现在有两种走法：

1. 走到 $(a+1,\max(b-1,0))$，有 $x$ 种方案。
2. 走到 $(a+1,b+1)$，有 $m-x$ 种方案。

发现 $\max(b-1,0)$ 是一个很难刻画的条件，思考如何替代，这里有一个比较牛的 trick。

先不考虑对 $0$ 取 $\max$，假如一条路径走过的最低点的在 $0$ 下第 $z$ 个格子，那么就把路径整体抬高 $z$ 个格子，需要注意的是 $z$ 明显始终是非负数。

这样做为什么是对的呢？举个例子吧（红线是原路径，绿线是抬高后的路径）：

![](https://cdn.luogu.com.cn/upload/image_hosting/09vzk3rk.png)

所以终点其实是没变的，问题转化到了求从 $(0,a)$ 开始到 $(n,b)$ 结束，至少经过一次 $y=0$ 但不经过 $y=-1$ 的路径的方案数了。

发现确定起点和终点，可以直接做两次反射容斥求出方案。

发现我们在知道起点和终点的情况下减少 $1$ 和增加 $1$ 的次数都清楚，就只用看方案数就行了。方案数是不经过 $y=-1$ 的方案数减去不经过 $y=0$ 的方案数。

不经过 $y=-1$ 的方案数：

$$
{n\choose \frac{n+b-a}{2}}-{n\choose\frac{n-b-a}{2}-1}
$$

不经过 $y=0$ 的方案数：

$$
{n\choose \frac{n+b-a}{2}}-{n\choose\frac{n-b-a}{2}}
$$

做差得 ${n\choose\frac{n-b-a}{2}}-{n\choose\frac{n-b-a}{2}-1}$。

令 $i=\frac{n-b-a}2,j=\frac{n+b-a}2$，则有 $b=j-i$。

注意到 $i$ 的上界为 $\lfloor\frac{n}{2}\rfloor$，下界为 $0$，$j$ 的上界为 $n-i$，下界为 $i$。

写出式子，准备开心消消乐，注意 $0^0=1$：
$$
\begin{aligned}
Ans&=\sum_{x=0}^m\sum_{i=0}^{\lfloor\frac{n}{2}\rfloor}\sum_{j=i}^{n-i}\left({n\choose i}-{n\choose i-1}\right)x^{n-j}(m-x)^j(j-i)\\
&=\sum_{i=0}^{\lfloor\frac{n}{2}\rfloor}\sum_{j=i}^{n-i}(j-i)\left({n\choose i}-{n\choose i-1}\right)\sum_{x=0}^mx^{n-j}(m-x)^j\\
\end{aligned}
$$

令 $F(z)=\sum\limits_{i=0}^\infty z^i\sum\limits_{x=0}^mx^{n-i}(m-x)^i$，处理一下：

$$
\begin{aligned}
F(z)&=\sum_{i=0}^\infty z^i\sum_{x=0}^mx^{n-i}(m-x)^i\\
&=\sum_{i=0}^\infty \sum_{x=0}^mx^nx^{-i}(m-x)^iz^i\\
&=\sum_{x=0}^mx^n\sum_{i=0}^\infty(\frac{m-x}{x}z)^i\\
&=\sum_{x=0}^m\frac{x^n}{1-\frac{m-x}xz}
\end{aligned}
$$

常规地 NTT 分治暴力合并分子分母就行了，这一部分是 $O(n\log^2n)$。

约定 $f_i=[z^i]F(z)$，继续往下看：

$$
\begin{aligned}
Ans
&=\sum_{i=0}^{\lfloor\frac{n}{2}\rfloor}\left({n\choose i}-{n\choose i-1}\right)\sum_{j=i}^{n-i}(j-i)f_j\\
\end{aligned}
$$

发现 $\sum\limits_{j=i}^{n-j}(j-i)f_j$ 是好预处理的，线性做了。

最后再线性遍历一次，总时间是 $O(n\log^2 n)$，瓶颈在于 NTT 分治。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();x=0;
        	while(c<'0'||c>'9') c=getchar();
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
#define cin Fastio :: cin
#define cout Fastio :: cout

const int g=3;
const int mod=998244353;
const int invg=(mod+1)/3;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    inline int Mod(const int x){return x>=mod?x-mod:x;}
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint operator-() const { return modint(norm(-val)); }
    modint& operator+=(const modint& o) { return val = Mod(val + o.val), *this; }
    modint& operator-=(const modint& o) { return val = norm(val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
	friend Fastio :: Writer& operator<<(Fastio :: Writer& os, modint a) { return os << a.val; }
	friend Fastio :: Reader& operator>>(Fastio :: Reader& is, modint& a) { return is >> a.val; }
};

const int N=1e6+10;
int rev[N],n,m;

template < int Max >
struct Choose{
	modint frac[Max+10],inv[Max+10];
	Choose(){
		frac[0]=inv[0]=1;for(int i=1;i<=Max;++i) frac[i]=frac[i-1]*i;
		inv[Max]=frac[Max].inv();for(int i=Max-1;i;--i) inv[i]=inv[i+1]*(i+1);
	}
	modint operator ()(const int x,const int y){return x<y||y<0?0:frac[x]*inv[y]*inv[x-y];}
};
Choose < N > C;

inline void GetRev(const int lim){int bit=log2(lim)-1;for(int i=0;i<lim;++i) rev[i]=((rev[i>>1]>>1)|((i&1)<<bit));}
inline int CalRev(const int len){int lim=1;for(;lim<=len;lim<<=1);GetRev(lim);return lim;}
inline modint expow(modint x,int y){modint res=1;for(;y;y>>=1){if(y&1)res*=x;x*=x;}return res;}

struct Poly{
	modint a[N];
	modint& operator [](const int x){return a[x];}
	inline void Readin(const int len){for(int i=0;i<len;++i) cin>>a[i].val;}
	inline void out(const int len){for(int i=0;i<len;++i) cout<<a[i]<<' ';cout<<endl;}
	inline void NTT(const int limit,const int type){
		for(int i=0;i<limit;++i) if(i<rev[i]) swap(a[i],a[rev[i]]);
		for(int i=1;i<limit;i<<=1){
			modint Gn=expow(type==1?g:invg,(mod-1)/(i<<1));
			for(int j=0;j<limit;j+=(i<<1)){
				modint G=1;
				for(int k=0;k<i;++k,G*=Gn){
					modint x=a[j+k],y=a[i+j+k]*G;
					a[j+k]=x+y;a[i+j+k]=x-y;
				}
			}
		}
		if(~type) return ;
		modint inv=expow(limit,mod-2);
		for(int i=0;i<limit;++i) a[i]*=inv;
	}
}x,y;

struct Frac{
	Poly s[2];
	inline void NTT(int lim,int op){s[0].NTT(lim,op);s[1].NTT(lim,op);}
}s[20],res;

inline void getinv(Poly &y,Poly &x,const int len){
	static Poly s,tmp;
	int lim=2,bas=1;s[0]=expow(x[0],mod-2);
	while(bas<(len<<1)){
		for(int i=0;i<bas;++i) tmp[i]=x[i];
		GetRev(lim);tmp.NTT(lim,1);s.NTT(lim,1);
		for(int i=0;i<lim;++i) s[i]=s[i]*2-s[i]*s[i]*tmp[i];
		s.NTT(lim,-1);for(int i=bas;i<lim;++i) s[i]=0;
		bas<<=1;lim<<=1;
	}
	for(int i=0;i<len;++i) y[i]=s[i];
	for(int i=0;i<bas;++i) s[i]=tmp[i]=0;
}

void Solve(Frac &t,int dep,int l,int r){
	if(l==r){
		t.s[0][0]=expow(l,n);
		t.s[1][0]=1;
		t.s[1][1]=-((modint(l).inv())*(m-l));
		return ;
	}
	int mid=(l+r)>>1,len=r-l+1;
	for(int i=0;i<=(len<<2);++i) t.s[0][i]=t.s[1][i]=0;
	Solve(s[dep],dep+1,l,mid);
	Solve(t,dep+1,mid+1,r);
	int lim=CalRev(len);
	s[dep].NTT(lim,1);t.NTT(lim,1);
	for(int i=0;i<lim;++i){
		modint tmp=t.s[1][i];
		t.s[0][i]=s[dep].s[0][i]*tmp+s[dep].s[1][i]*t.s[0][i];
		t.s[1][i]=s[dep].s[1][i]*tmp;
		s[dep].s[0][i]=s[dep].s[1][i]=0;
	}
	t.NTT(lim,-1);
}

modint F[N],G[N];

inline modint Get(modint *v,int l,int r){return v[r]-(l?v[l-1]:0);}

inline modint Calc(){
	Solve(res,0,1,m);modint ans=0;
	for(int i=n+1;i<N;++i) res.s[0][i]=res.s[1][i]=0;
	getinv(res.s[1],res.s[1],n+1);int lim=CalRev((n+2)<<1);
	res.NTT(lim,1);for(int i=0;i<lim;++i) res.s[0][i]*=res.s[1][i];
	res.s[0].NTT(lim,-1);
	for(int i=0;i<=n;++i){
		F[i]=res.s[0][i];
		G[i]=F[i]*i;
		if(i){
			F[i]+=F[i-1];
			G[i]+=G[i-1];
		}
	}
	F[n]+=expow(m,n);G[n]+=expow(m,n)*n;
	for(int i=0;i<=n/2;++i){
		ans+=(C(n,i)-C(n,i-1))*(Get(G,i,n-i)-Get(F,i,n-i)*i);
	}
	return ans;
}

int main(){
	modint ans=0;cin>>n>>m;
	for(int i=1;i<=m;++i) ans+=expow(m,n-1)*i*n;
	cout<<ans-Calc();
	return 0;
}
```

---

## 作者：yyyyxh (赞：1)

双倍经验 ARC163F/P8923。

一个 $O(n\log n)$ 且复杂度与 $m$ 几乎无关的做法。

不难发现让我们计数的问题是保序回归 $L_1$ 中一条链的情况。这个情况有一个简单的 slope-trick 做法：用堆维护斜率，每次 `push` 进去两个当前的数，然后 `pop` 出一个最大值。最终所有数的和减去堆中的数的和就是答案。

有一个来自 [ARC128F](https://atcoder.jp/contests/arc128/tasks/arc128_f) 经典思维技巧：对于这类弹堆压堆还要求堆中元素和的计数问题，考虑转化成值域为 01 的问题。即活用 $i=\sum_{x=1}^{\infin} [i\ge x]$ 的等式。将 $\ge x$ 的数标成 $1$，剩余的数标成 $0$。那么如果原先堆中有 $s$ 个 $1$，遇到一个 $1$ 会变成一个 $s+1$，遇到一个 $0$ 会变成 $\max(s-1,0)$。这就是一个格路游走问题，容易验证最终 $s$ 的值等于路程中 $1$ 的个数减去路程中 $0$ 的个数再加上如果没有对 $0$ 取 $\max$ 的情况下，$s$ 在整个过程中的最小值。

发现唯一难算的就是最后一部分的“最小值之和”。考虑继续运用上面的思维技巧，继续活用等式 $i=\sum_{x=1}^{\infin} [i\ge x]$，将 $s$ 的游走过程看作 $(0,0)$ 到 $(n,\times)$ 的游走过程，那么最小值之和（的相反数）可以拆成触碰 $y=-t\ (t>0)$ 这条线的方案数之和。钦定触碰一条线的格路游走就是我们熟悉的反射容斥。我们设原来有 $p$ 个 $1$，那么原先终点在 $(n,2p-n)$，如果 $2p-n>t$ 则经过那条线的方案数等于到终点 $(n,-2t-2p+n)$ 的方案数。

所以对于一个固定的 $p$，我们需要对以下东西求和：

$$
S_p=\sum_{t=1}^{\infin} {n\choose \min(n-t-p,p)}
$$

这个可以预处理 ${n\choose \times}$ 这一行的组合数前缀和简单算出来。

现在考虑对于 $x$ 你需要依次带入 $x=1,2,\dots,m$，不妨把结果看成一个关于 $x$ 的多项式，则这个多项式实际上是：

$$
F(x)=\sum_{p=0}^n x^p(m-x)^{n-p}S_p
$$

展开 $(m-x)^{n-p}$，容易发现可以用一遍卷积求出 $F$。

最后我们只需要解决 $\sum_{i=1}^m F(i)$，相当于要对一个固定的 $n$ 求出 $k=0,1,2,\dots,n$ 的自然数幂和 $S_k(n)=\sum_{i=0}^n i^k$，可以用多项式求逆求出伯努利数，然后卷一次得到自然数幂和。于是我们就做到复杂度 $O(n\log n)$。

[关于伯努利数求自然数幂和](https://www.cnblogs.com/yyyyxh/p/18263819/many_isotonic_regression_countings)。

```cpp
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
// headers
struct poly{/** my poly template **/};
int n,m;
const int N=100103;
int fac[N],fiv[N];
int arr[N],pre[N];
int coe[N],pw[N];
inline int C(int a,int b){return (ll)fac[a]*fiv[b]%P*fiv[a-b]%P;}
void calc(int lim){
	pw[0]=1;
	for(int i=1;i<=lim;++i) pw[i]=(ll)pw[i-1]*m%P;
	fac[0]=1;
	for(int i=1;i<=lim;++i) fac[i]=(ll)fac[i-1]*i%P;
	fiv[lim]=qp(fac[lim]);
	for(int i=lim;i;--i) fiv[i-1]=(ll)fiv[i]*i%P;
}
int main(){
	n=read();m=read();
	calc(n+3);int res=(ll)n*(m-1)%P*pw[n]%P;
	if(res&1) res+=P;
	res>>=1;
	pre[0]=1;
	for(int i=1;i<=n;++i){
		pre[i]=pre[i-1]+C(n,i);
		if(pre[i]>=P) pre[i]-=P;
	}
	poly F(n+1),G(n+1);
	for(int i=0;i<=n;++i){
		if(2*i<=n) F[i]=(pre[i-1]+(ll)C(n,i)*(n-i*2))%P;
		else F[i]=pre[n-1-i];
		F[i]=(ll)F[i]*fac[n-i]%P;
	}
	for(int i=0;i<=n;++i) if(i&1) G[i]=fiv[i];else G[i]=P-fiv[i];
	G=F*G;
	for(int i=0;i<=n;++i) coe[i]=(ll)G[i]*pw[n-i]%P*fiv[n-i]%P;
	F.f.resize(n+2);
	G.f.resize(n+2);
	for(int i=0;i<=n+1;++i) F[i]=fiv[i+1];
	F=F.inv(n+2);
	for(int i=0,tt=1;i<=n+1;++i){
		G[i]=(ll)tt*fiv[i]%P;
		tt=(ll)tt*(m+1)%P;
	}
	G=F*G;
	for(int i=0;i<=n;++i) res=(res+(ll)coe[i]*(G[i+1]-F[i+1]+P)%P*fac[i])%P;
	res-=coe[0];
	if(res<0) res+=P;
	printf("%d\n",res);
	return 0;
}
```

---

