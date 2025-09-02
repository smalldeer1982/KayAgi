# List Of Integers

## 题目描述

Let's denote as $ L(x,p) $ an infinite sequence of integers $ y $ such that $ gcd(p,y)=1 $ and $ y>x $ (where $ gcd $ is the greatest common divisor of two integer numbers), sorted in ascending order. The elements of $ L(x,p) $ are $ 1 $ -indexed; for example, $ 9 $ , $ 13 $ and $ 15 $ are the first, the second and the third elements of $ L(7,22) $ , respectively.

You have to process $ t $ queries. Each query is denoted by three integers $ x $ , $ p $ and $ k $ , and the answer to this query is $ k $ -th element of $ L(x,p) $ .

## 样例 #1

### 输入

```
3
7 22 1
7 22 2
7 22 3
```

### 输出

```
9
13
15
```

## 样例 #2

### 输入

```
5
42 42 42
43 43 43
44 44 44
45 45 45
46 46 46
```

### 输出

```
187
87
139
128
141
```

# 题解

## 作者：JK_LOVER (赞：4)

[更好的阅读体验](https://www.luogu.com.cn/blog/xzc/solution-cf920g)
# 分析
求第 $k$ 大的大于等于 $x$ 且与 $p$ 互质的数，那么我们先考虑如果我们枚举第 $k$ 大是谁，其实并不好做。这样时间复杂度的的下限至少为 $O(tn)$ 。那么我们考虑二分一个值 $pos$ ，$[1,pos]$ 与 $p$ 互质的数的总个数求出来，这样二分的值就具有单调性了，也可以很好的处理大于等于 $x$ 这个条件，做一次差分就好了。那么现在算法的主要问题就是如何求出 $[1,pos]$ 有几个数与 $p$ 互质。如果我们学习过 $\varphi(p)$ ，那么我们可以很快从这里找到相似点， $\varphi(p)$ 的定义为 $[1,p-1]$ 中有几个数与 $p$ 互质。而 $\varphi(p)$ 的求解方式为 $\varphi(p)=p\prod(1-\frac{1}{P_i})$ ，我们发现并不能很好的拓展到 $[1,pos]$ ，但是我们不要忘了 $\varphi(p)$ 最根本的求解方法，容斥。 $\varphi(n) = \sum_{S\subseteq\{p_1,p_2,..p_k\}}(-1)^{|S|}\frac{n}{\prod_{p_i\in S}p_i}$ 。我们发现这个的定义其实比较简单，我们先去掉 $p_1,p_2,p_3..p_k$ 的倍数，再加上 $p_1p_2,p_1p_3..,p_{k-1}p_k$ 的倍数，因为它们被减去了两次，以此类推，枚举完所有子集，那么我们推广到 $[1,pos]$ 就比较好做了，先减去 $p_1,p_2..p_k$ 的倍数，再加上两两的倍数 $...$ 。那么只需要做一个容斥就好了。
# 算法
- 先唯一分解，将 $p$ 分解为 $P_1^{a_1}P_2^{a_2}..P_{k}^{a_k}$ 的形式。
- $k$ 先加上 $[1,x]$ 的与 $p$ 互质的个数。 
- 二分答案，这里有个小细节要处理。我们二分的答案如果已经满足了，我们要考虑更小的答案，因为当前答案可以并不与 $p$ 互质。但是个数的变化一定是一个连续的区间，所有取最小的满足的答案，才是我们要的答案。
- 令 $w$ 为质因子个数，时间复杂度为 $O(t\times \log p(\sqrt{p}+2^{w}))$ 。但其实 $w$ 很小，所以跑的还是挺快的。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
    int x = 0,f = 0;char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-')f = 1;ch = getchar();}
    while(isdigit(ch)) {x = x * 10 + ch - '0';ch = getchar();}
    return f ? -x : x;
}
const int N = 1e6 + 100;
int P[60];
int Solve(int x,int a,int type) {
    if(a == P[0] + 1) {return x * type;}
    else {
        return Solve(x,a+1,type) + Solve(x/P[a],a+1,type * -1);
    }
}
int solve(int x) {
    return Solve(x,1,1); 
} 
int main() {
    int T = read();
    while(T--) {
        int limit = read(),p = read(),k = read();P[0] = 0;
        int x = p;
        for(int i = 2;i * i <= x;i++) {
            if(x % i) continue;
            P[++P[0]] = i;
            while(!(x % i)) x = x / i;
        }
        if(x > 1) P[++P[0]] = x;
        k += solve(limit);
        int l = limit + 1,r = 1e9,ans = 0;
        while(l <= r) {
            int mid = l + r >> 1;
            x = solve(mid);
            if(x >= k) r = mid - 1,ans = mid;
            else l = mid + 1;
        }
        cout << ans << endl;
    }
}
```

---

## 作者：_Fontainebleau_ (赞：4)

### 题意

- 给定 $x,p,k$，求第 $k$ 个大于 $x$ 且与 $p$ 互质的数。多组测试。
- $1\le x,p,k\le 10^6$

### 做法

看到第 k 大这个东西，可以条件反射地想到 **二分**。

于是这道题就转化成求

$$\sum_{i=1}^x\left[\gcd\left(i,p\right)=1\right]$$

**莫比乌斯反演** 一下就没了。

怎么反演呢？把 $\left[\gcd\left(i,p\right)=1\right]$ 写成 $\displaystyle \sum_{d\mid \gcd\left(i,p\right)}\mu\left(d\right)$，然后改变求和顺序，先枚举 $d$ 即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/qns9ze68.png)

线性筛 $\mu$ 函数是 $O(n)$ 的，枚举 $d$ 是 $O\left(\sqrt p\right)$ 的，最终复杂度就是 $O\left(n+t\log n \sqrt p\right)$，可以通过此题。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int prime[100006];
bitset<1000006> used;
int mu[1000006],cnt;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f; 
}
inline void sieve(int n)
{
	mu[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!used[i])	prime[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=n;j++)
		{
			used[i*prime[j]]=1;
			if(i%prime[j])	mu[i*prime[j]]=-mu[i];
			else	break;
		}
	}
}
inline int get(int x,int p)
{
	int l=sqrt(p),ans=0;
	for(int i=1;i<=l;i++)
		if(p%i==0)
		{
			ans+=mu[i]*(x/i);
			if(i*i!=p)
			{
				int tmp=p/i;
				ans+=mu[tmp]*(x/tmp);
			}
		}
	return ans;
}
int main()
{
	int tc=read();
	sieve(1000000);
	while(tc--)
	{
		int x=read(),p=read(),k=read();
		int l=x+1,r=1e7,ans=-1,tmp=get(x,p);
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(get(mid,p)-tmp>=k)	ans=mid,r=mid-1;
			else	l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：2huk (赞：2)

[更好的阅读体验](https://www.cnblogs.com/2huk/p/18000967)。

> $t$ 组询问，求第 $k$ 个大于 $x$ 且与 $P$ 互质的数。

看到第 $k$ 大这个东西，首先想到二分答案。

令当前的二分中点为 $m$，那么如果 $[x + 1, m]$ 中与 $p$ 互质的数大于等于 $k$ 个，往下缩小二分范围。否则往上缩小二分范围。

同时，求 $[x + 1, m]$ 中与 $p$ 互质的数的数量可以前缀和转化为 $[1, m]$ 中与 $p$ 互质的数的数量减去 $[1, x]$ 中与 $p$ 互质的数的数量。那么现在问题就变成了：

> 求 $[1, x]$ 中有多少数与 $p$ 互质。

这个东西没法直接求。考虑容斥。

将 $p$ 质因数分解。那么一个整数 $q$ 与 $p$ 不互质当且仅当将 $q$ 质因数分解后，存在与 $p$ 相同的质因子。那么，我们可以 dfs 枚举 $p$ 的每一个质因子是否是 $q$ 的质因子。若令选择的所有质因子的乘积为 $t$，那么 $\left \lfloor \dfrac xt \right \rfloor$ 即为满足这个条件的 $q$ 的数量。

然后做容斥。如果总共选择了偶数个质因子，将答案加上 $\left \lfloor \dfrac xt \right \rfloor$。反之减去 $\left \lfloor \dfrac xt \right \rfloor$。

[代码](https://codeforces.com/contest/920/submission/243990375)。

---

## 作者：yybyyb (赞：2)

先不考虑题目

怎么求$\sum_{i=1}^n[gcd(i,p)=1]$

这个枚举$p$的因数做一个容斥就好

剩下的就直接二分答案然后容斥计算个数

时间复杂度$O(nlog\sqrt{n})$
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define MAX 10000000
#define ll long long
inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
bool zs[MAX+1];
int pri[MAX+1],tot,mu[MAX+1],smu[MAX+1];
void pre()
{
	zs[1]=true;mu[1]=1;
	for(int i=2;i<=MAX;++i)
	{
		if(!zs[i])pri[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&i*pri[j]<=MAX;++j)
		{
			zs[i*pri[j]]=true;
			if(i%pri[j])mu[i*pri[j]]=-mu[i];
			else break;
		}
	}
	for(int i=1;i<=MAX;++i)smu[i]=smu[i-1]+mu[i];
}
int Count(int p,int n)
{
	int ret=0;
	for(int i=1;i*i<=p;++i)
	{
		if(p%i)continue;
		ret+=mu[i]*(n/i);
		if(p/i!=i)ret+=mu[p/i]*(n/(p/i));
	}
	return ret;
}
int main()
{
	int T=read();pre();
	while(T--)
	{
		int x=read(),p=read(),K=read();
		int ss=Count(p,x);
		int l=x+1,r=1e7,ans;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			int sss=Count(p,mid);
			if(sss-ss>=K)ans=mid,r=mid-1;
			else l=mid+1;	
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：WhisperingWillow (赞：1)

二分答案 $mid$，则问题变为求 $\sum_{i=1}^x[\gcd(i,p)]=1$ 的值。

考虑莫反。

原式显然可以化为 $\sum_{d|p}\dfrac{x}{d}\mu(p)$。

[Code](https://codeforces.com/contest/920/submission/248842365)

---

## 作者：xz001 (赞：1)

二分答案，判定需要求 $[x+1,mid]$ 内有多少个与 $p$ 互质的数，我们把它转化为求 $[1,x]$ 和 $[1,mid]$ 内与 $p$ 互质的数，然后后者减前者。我们容斥一下，把 $p$ 分解质因数，求出有多少个**不与** $p$ 互质的数，条件就是包含 $p$ 的至少一个质因子，由于 $p\le 10^6$，不同的质因子数不超过 $8$。直接暴力 $2^8$ 深搜即可。

代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

// define
#define re register
#define fi first
#define se second
#define il inline
#define co const
#define ls (u << 1)
#define rs (u << 1 | 1)
#define fup(x, l, r) for (re int x = (l), eNd = (r); x <= eNd; ++ x )
#define fdw(x, r, l) for (re int x = (r), eNd = (l); x >= eNd; -- x )
#define min(a, b) ((a)<(b)?(a):(b))
#define int long long

// typedef
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

// const
const int N = 1e6 + 10, M = 2e6 + 10;
const int INF = 2e9, mod = 1e9 + 7;
const double eps = 1e-6;

int x, p, k, t;

vector <int> v;

int dfs (int i, int j, int sum, int n) {
	if (i == v.size()) {
		return (j & 1) ? -n / sum : n / sum; 
	}
	return dfs (i + 1, j + 1, sum * v[i], n) + dfs (i + 1, j, sum, n);
}

int query (int x) {
	return dfs (0, 0, 1, x);
}

signed main() {
    scanf("%lld", &t);
    while (t -- ) {
    	scanf("%lld%lld%lld", &x, &p, &k);
    	v.clear();
    	for (int j = 2; j * j <= p; ++ j) {
    		if (p % j == 0) {
    			v.push_back(j);
    			while (p % j == 0) p /= j;
			}
		}
		if (p != 1) v.push_back(p);
		int l = 1, r = 1e18, ans = 0, sl = query(x);
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (query(mid) - sl < k) {
				ans = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		printf("%lld\n", ans + 1);
	}
	return 0;
}
```

---

## 作者：Leasier (赞：1)

~~好久没做莫反题了，来水一道~~

前置芝士：[莫比乌斯反演](https://oi-wiki.org/math/number-theory/mobius/)

看到“第 $k$ 个大于 $x$”，容易想到二分答案。二分后问题转变为快速求出 $f(a, b) = \displaystyle\sum_{i = 1}^a [\gcd(i, b) = 1]$。

右边的形式显然可以莫比乌斯反演，有：

$f(a, b) = \displaystyle\sum_{i = 1}^a \sum_{d \mid \gcd(i, b)} \mu(d)$

$ = \displaystyle\sum_{d \mid b} \mu(d) \sum_{d \mid i}^a 1$

$ = \displaystyle\sum_{d \mid b} \mu(d) \lfloor \frac{a}{d} \rfloor$

直接枚举因数计算即可。时间复杂度为 $O(t \sqrt{p} \log M + N)$。

代码：
```cpp
#include <stdio.h>
#include <math.h>

const int N = 1e6 + 7;
int prime[N], mu[N];
bool p[N];

inline void init(){
	int cnt = 0;
	p[0] = p[1] = true;
	mu[1] = 1;
	for (register int i = 2; i < N; i++){
		if (!p[i]){
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for (register int j = 1; j <= cnt && i * prime[j] < N; j++){
			int t = i * prime[j];
			p[t] = true;
			if (i % prime[j] == 0){
				mu[t] = 0;
				break;
			}
			mu[t] = -mu[i];
		}
	}
}

inline int solve(int a, int b){
	int t = sqrt(b), ans = 0;
	for (register int i = 1; i <= t; i++){
		if (b % i == 0){
			ans += mu[i] * (a / i);
			if (i * i != b){
				int tb = b / i;
				ans += mu[tb] * (a / tb);
			}
		}
	}
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	init();
	for (register int i = 1; i <= t; i++){
		int x, p, k, l, r = 1e7, temp, ans;
		scanf("%d %d %d", &x, &p, &k);
		l = x + 1;
		temp = solve(x, p);
		while (l <= r){
			int mid = (l + r) >> 1;
			if (solve(mid, p) - temp >= k){
				r = mid - 1;
				ans = mid;
			} else {
				l = mid + 1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：shao0320 (赞：1)

很好的数学题。

拿到这题第一反应是觉得可以求出$\phi(p)$然后乱搞，但是这样可能会被卡$TLE$

考虑求$[1,pos]$之间与$p$互质的数量的另一种方法：容斥。

设$p$有$n$个因数分别为$a_1-a_n$，那么可以用这样一种方法求出$[1,pos]$之间与$p$互质的数量：用$pos$减去$[1,pos]$内$a_1,a_2...a_n$的因数，加上$a1a2,a1a3,a1a4....a_{n-1}a_n$的倍数，以此类推。而我们发现，这个可以用线性筛，在$O(N)$的时间内与预处理出来每个数所做的贡献，因为每个数的贡献是不变的，这取决于它的质因数个数。

仅仅知道这个还不够，因为我们还是没法找到一个$pos$，而我们发现，设$f(x,p)$表示$1-x$之内与$p$互质的数，这个东西是单调不降的，因此考虑二分答案$x$并且在$O(\sqrt n)$内求出$f(x,p)$。

而在$(x,pos]$之间的问题同样可以转化为$[1,pos]$间的问题，方法是在最开始就加上$f(x,p)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000005
#define MAXN 1000000
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int pri[N],vis[N],val[N],cnt,T;
void init()
{
	vis[1]=val[1]=1;
	for(int i=2;i<=MAXN;i++)
	{
		if(!vis[i])val[i]=-1,pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<=MAXN;j++)
		{
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
			val[i*pri[j]]=-val[i];
		}
	}
}
int solve(int p,int n)
{
	int res=0;
	for(int i=1;i*i<=p;i++)
	{
		if(p%i)continue;
		res+=val[i]*(n/i);
		if(i*i!=p)res+=val[p/i]*(n/(p/i));
	}
	return res;
}
int main()
{
	init();
	T=read();
	while(T--)
	{
		int x=read(),p=read(),k=read();
		k+=solve(p,x);
		int l=x+1,r=1e7,mid,ans=0;
		//cout<<k<<endl;
		while(l<=r)
		{
			mid=(l+r)>>1;
			//cout<<l<<" "<<r<<" "<<mid<<" "<<solve(p,mid)<<" "<<k<<endl;
			if(solve(p,mid)>=k)
			{
				ans=mid,r=mid-1;
				//cout<<"NICE!!!!!!!!!!"<<endl;
			}
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：lgx57 (赞：0)

考虑二分答案。问题相当于求出 $\displaystyle\sum_{i=1}^x [\gcd(i,p)=1]$。

然后莫比乌斯反演。

$$\begin{aligned} \sum_{i=1}^x[\gcd(i,p)=1] &=\sum_{i=1}^x \sum_{d \mid i,d \mid p} \mu(d) \\ &= \sum_{d \mid p} \mu(d) \sum_{i=1}^x [d \mid i] \\ &= \sum_{d \mid p} \mu(d) \lfloor \frac{x}{d} \rfloor\end{aligned}$$

提前处理出 $p$ 的所有因子，每一次查询仅需 $O(\sqrt{p})$。

时间复杂度：$O(p+\log V \sqrt p)$

---

## 作者：mango2011 (赞：0)

典型的容斥应用题。首先看到了这个题目，我们就可以想到二分：

二分出一个数 $t$，如果 $F(t,p)-F(x,p)<k$，则说明 $t$ 小了；$F(t,p)-F(x,p)\ge k$ 说明 $t$ 可能还不够小。其中 $F(a,b)$ 表示 $1\sim a$ 中与 $b$ 互质的正整数个数。

于是我们的重点就是如何计算 $F(a,b)$：

令 $q_1,q_2,q_3,\dots,q_d$ 为 $b$ 的所有不同质因子（经过计算，可以发现 $d\le7$）。

计算与某数互素的数的个数并不容易，所以我们考虑用总的减去不互素的。令 $A_i=\{x|1\le x\le a,x\in N_{+},q_i |x\}$。我们想要求出来的就是 $|A_1\cup A_2\cup \dots \cup A_d|$。前面的式子等于 $|A_i|-|A_i \cap A_j|+|A_i\cap A_j\cap A_k|-\dots +(-1)^{d-1} |A_1\cap A_2\cap\dots \cap A_d|$。

于是我们就可以在 $O(2^d d)$ 的复杂度内求出 $F(a,b)$。

还有最后一个问题，就是如何设置上界。笔者一开始设置了 $10^{18}$。但是经过计算，发现答案最大为 $6539381$。

总的复杂度就是 $O(q 2^d d\log B )$，其中 $d\le7$，$B$ 取 $6539381$。

[上界小](https://codeforces.com/contest/920/submission/272630395)

[上界大](https://codeforces.com/contest/920/submission/272629900)

---

## 作者：ifffer_2137 (赞：0)

### 题意
 $T$ 组询问，求第 $k$ 个大于 $x$ 且与 $p$ 互质的数。
### 分析
我们定义函数：
$$f(n)=\sum_{i=1}^{n}[\gcd(i,p)=1]-\sum_{i=1}^{x}[\gcd(i,p)=1]$$ 
发现具有单调性，考虑二分判断。现在我们要快速求 
$$\sum_{i=1}^{n}[\gcd(i,p)=1]$$
的值，套路化地考虑莫比乌斯反演：
$$\begin{aligned}
{}&\sum_{i=1}^{n}[\gcd(i,p)=1]&\\
=&\sum_{i=1}^n\sum_{d|i,d|p}\mu(d)&\\
=&\sum_{d|p}\mu(d)\lfloor \frac{n}{d} \rfloor&\\
\end{aligned}$$
然后线性筛一下莫比乌斯函数，就可以 $O(\sqrt p)$ 枚举因数计算该函数值了，总时间复杂度 $O(T\log V\sqrt p)$ ，可以通过。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e6+5;
int T;
int x,p,k;
int isp[maxn],mu[maxn];
vector<int> pri;
void init(){
	mu[1]=isp[1]=1;
	for(int i=2;i<=1000000;i++){
		if(!isp[i]){
			pri.push_back(i);
			mu[i]=-1;
		}
		for(int j:pri){
			if(i*j>1000000) break;
			isp[i*j]=1;
			if(i%j==0){
				mu[i*j]=0;
				break;
			}
			mu[i*j]=-mu[i];
		}
	}
}
vector<int> d;
int calc(int x){
	int res=0;
	for(int i:d){
		res+=mu[i]*(x/i);
	}
	return res;
}
signed main(){
	cin.tie(0),cout.tie(0);
	init();
	T=read();
	while(T--){
		x=read(),p=read(),k=read();
		d.clear();
		for(int i=1;i*i<=p;i++){
			if(p%i==0){
				d.push_back(i);
				if(i*i!=p) d.push_back(p/i);
			}
		}
		int t=calc(x);
		int l=x+1,r=1e18,ans=1e18;
		while(l<=r){
			int m=(l+r)/2;
			if(calc(m)-t>=k){
				ans=m;
				r=m-1;
			}else{
				l=m+1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：RegisterFault (赞：0)

 - 算法：binary-search，莫比乌斯反演。
 
 - 题目大意：给定 $x, p, k$。求 $ > x$ 的第 $k$ 小的与 $p$ 互质的数。
 
 - 分析：
 
 首先，发现答案具有可二分性。二分答案，发现问题转化为：求 $\sum \limits_{i = 1}^{n}[(i, p) = 1]$。
 
 对这个式子进行莫反变形：
 
 $$\sum_{i = 1}^{n} [(i, p) = 1] $$
 
 $$ = \sum_{i = 1}^{n} \sum_{d | (i, p)}^{} \mu(d)$$
 
 $$ = \sum_{d | p}^{} \mu(d) \sum_{i = 1}^{\frac{n}{d}} 1$$
 
 $$ = \sum_{d | p}^{} \mu(d) \left \lfloor \dfrac{n}{d} \right \rfloor$$
 
 筛出 $\mu$ 之后这个东西可以直接 $O(d(p))$ 的复杂度算。
 
 tips：一定要提前预处理出来 $p$ 的约数。否则会在 #5 超时。
 
 时间复杂度 $O(\max \{p\} + T d(p) \log V)$。
 
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define int long long

using namespace std;

const int N = 1000010;
int q, x, p, k;
int mu[N], pri[N], cnt;
bool st[N];
vector<int> vec;
void get_prime(int n) {
	mu[1] = 1;
	for (int i = 2; i <= n; i ++ ) {
		if (!st[i]) pri[ ++ cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt and i * pri[j] <= n; j ++ ) {
			st[i * pri[j]] = true;
			if (i % pri[j] == 0) break;
			mu[i * pri[j]] = -mu[i];
		}
	}
}
int get(int n) {
	int ans = 0;
	for (auto d : vec)
		ans += mu[d] * (n / d);
	return ans;
}
bool check(int mid) {
	return get(mid) >= k;
}
signed main() {
	get_prime(N - 1);
	scanf("%lld", &q);
	while (q -- ) {
		scanf("%lld%lld%lld", &x, &p, &k);
		vec.clear();
		for (int i = 1; i <= p / i; i ++ )
			if (p % i == 0) {
				vec.push_back(i);
				if (i * i != p) vec.push_back(p / i);
			}
		int delta = get(x);
		k += delta;
		int l = 1, r = (int)1e8;
		while (l < r) {
			int mid = l + r >> 1;
			if (check(mid)) r = mid;
			else l = mid + 1;
		} printf("%lld\n", l);
	} return 0;
}
```

---

## 作者：Deuteron (赞：0)

写在前面：次掉 cfz 喵！

题意：

 $T$ 组询问，求第 $k$ 个大于 $x$ 且与 $p$ 互质的数。
 
$T \le 3 \times 10^4,p,x,k \le 10^6$
 
## solution

回学校的路上 15min 就想完了qwq

令 $\operatorname{calc} (x,y) $ 表示 $ \le x$ 且与 $y$ 互质的数的个数。

首先考虑二分答案，若 $\operatorname{calc}(mid,p)-\operatorname{calc}(x,p) \ge k$ 就说明可行的数多了，应该 $r=mid$，反之亦然。（就是差分一下。）

注意最后求出的 $l$ 不一定是要求的那个，注意到素数一定满足要求，所以减的次数就是 $\log n$ 的级别，直接暴力减就行了。

然后如何求出 $\operatorname{calc}(x,y)$ 呢？

考虑容斥，令 $P$ 为 $p$ 的素因子集合，则 $P$ 的子集 $S$ 对答案的贡献就是 $\lfloor \dfrac{x}{\Pi{S}}\rfloor \times (-1)^{|S|}$ 。原因联系 $\phi$ 的实际计算过程可得。

注意 $\le 10^6$ 的数的不同素因子个数一定 $\le 7$，所以直接暴力算。

~~似乎还有莫反做法，但是没想到。~~

实现的时候线性筛出 $n$ 的最小素因子 $f_n$ ，提前求出 $\operatorname{calc}(x,p)$ ，对于每组询问在二分前求出所有 $\Pi{S}$ 以及 $(-1)^{|S|}$。

时间复杂度很玄学，大概是 ~~O(能过)~~ $O(n+T(7\times 2^7+\log n \times 2^7+\log^2 n)$ 这样的，反正跑得很快。

## code

```cpp
#include<iostream>
#include<vector>
using namespace std;
int t,x,p,k;
const int N=1e6+5;
int pr[N],ip[N],f[N],cnt,pre;
int P[N],tot,pro[N],tr[N];
void work(int n){//线性筛
	for(int i=2;i<=n;i++){
		if(!ip[i]){
			pr[++cnt]=i;
            f[i]=i;
		}
		for(int j=1;j<=cnt&&i*pr[j]<=n;j++){
			ip[i*pr[j]]=1;
            f[i*pr[j]]=pr[j];
			if(i%pr[j]==0) break;
		}
	}
}
int calc(int x,int p){//calc过程
    int ans=0;
    for(int i=0;i<(1<<tot);i++){
        ans+=(x/pro[i])*tr[i];
    }
    return ans;
}
int check(int x,int p){
    //cout<<x<<" "<<p<<" "<<calc(x,p)<<" "<<pre<<endl;
    return calc(x,p)>=k+pre;//pre就是calc(x,p)
}
int gcd(int x,int y){
    if(y==0) return x;
    return gcd(y,x%y);
}
int main(){
    work(N-5);
    cin>>t;
    while(t--){
        cin>>x>>p>>k;
        int s=p;
        tot=0;//p的质因数个数
        while(s>1){
            P[tot++]=f[s];
            int T=f[s];
            while(s%T==0) s/=T;//暴力分解质因数
        }
        for(int i=0;i<(1<<tot);i++){//预处理集合的积以及容斥系数
            pro[i]=tr[i]=1;
            for(int j=0;j<=tot;j++){
                if(i&(1<<j)){
                    pro[i]*=P[j];
                    tr[i]*=-1;
                }
            }
        }
        pre=calc(x,p);
        int l=x+1,r=5e7;//上界为了保险，多设了点
        while(l<r){//二分
            int mid=(l+r)>>1;
            if(check(mid,p)) r=mid;
            else l=mid+1;
        }
        while(gcd(p,l)>1) l--;//调整l
        cout<<l<<endl;
        for(int i=0;i<=tot;i++) P[i]=0;//别忘清空
    }
    return 0;
}//一发过2200，庆祝一下
```


---

## 作者：45dino (赞：0)

另一道考察莫比乌斯函数的练习题，实质上是对@[yybyyb](https://www.luogu.com.cn/user/21283)的题解的补充。

莫比乌斯函数模板题见[P4450](https://www.luogu.com.cn/problem/P4450)

很容易想到二分，经过一系列转换，现在只要对于一个 $n$，计算这个小于它有多少个数和 $p$ 互质即可，具体做法如下。
$$\sum_{i=1}^n[\gcd(i,p)=1]$$
$$=\sum_{i=1}^n\sum_{l|gcd(i,p)}\mu(l)$$
$$=\sum_{l|p}\sum_{i=1}^n\mu(l)\times[l|i]$$
$$=\sum_{l|p}\mu(l)\times\lfloor \frac n l\rfloor$$
单次计算的时间复杂度为 $\Theta(\sqrt p)$ 的，因此对于一组数据，运算量为 $\sqrt n\times\log (10^7)$，大概是 $2\times10^4$ 的级别？。

---

## 作者：STPGUY (赞：0)

# [List of Intergers](https://www.luogu.com.cn/problem/CF920G)

## 题目大意
求第$k$大的大于等于 $x$ 且与 $p$ 互质的数

## 分析

即，求最小的 $y$ 使：

$$
\sum_{i=1}^y[i\perp p]-\sum_{i=1}^x[i\perp p]=k
$$

## 莫比乌斯反演

那么看见这个形式，自然而然地会想到这个东西：$\mu*1=\epsilon$

所以就可以把 $[i\perp p]$ 写成：

$$
\sum_{d|\gcd(i,p)}\mu(d)
$$

那么交求和顺序，先枚举 $p$ 的因子 $d$，可以得到:

![](https://s1.ax1x.com/2020/09/25/099nlq.png)

那么，这个时候，后面这一块，已经是十分好求的了，可以直接枚举 $\sqrt y$ 范围内 $y$ 的因子(顺便得到 $>\sqrt y$ )的因子，按照这个直接加就可以了

## 容斥

还是考虑$[i\perp p]$，换一种写法呢就是$[\gcd(i,p)==1]$

那么就是说，不合法的就是$\gcd(i,p) > 1$

那么按照套路，还是应该用总共的减去不合法的，

那么就要枚举$p$的每个因子对答案的贡献

同样的，还是可以得到容斥系数就是$\mu$

那么还是能够得到同一个式子：
$$
\sum_{i=1}^y[i\perp p]=\sum_{d|p}^y\mu(d)\left\lfloor\frac y d\right\rfloor
$$
当然，这并不是巧合，有兴趣的同学可以自行了解一下

时间复杂度为$O(n\log n\sqrt n)$

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 1e7 + 10;
const int mod = 1e9 + 7;

inline int __read()
{
    int x(0), t(1);
    char o (getchar());
    while (o < '0' || o > '9') {
        if (o == '-') t = -1;
        o = getchar();
    }
    for (; o >= '0' && o <= '9'; o = getchar()) {
        x = (x << 1) + (x << 3) + (o ^ 48);
    }
    return x * t;
}

int mu[maxn], pr[maxn], cnt, line;
bool vis[maxn];

inline void Init()
{
    mu[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (!vis[i]) pr[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && i * pr[j] < maxn; ++j) {
            vis[i * pr[j]] = 1;
            if (i % pr[j]) mu[i * pr[j]] = -mu[i];
            else break;
        }
    }
}

inline int Query(int n, int x)
{
    int ans(0);
    for (int l = 1; l * l <= x; ++l) {
        if (x % l) continue;
        ans += mu[l] * (n / l);
        if (l * l < x) ans += mu[x / l] * (n / (x / l));
    }
    return ans;
}

signed main()
{
    Init();
    int T = __read();
    while (T--) {
        int x = __read(), p = __read(), k = __read();
        int l(1), r(1e7), ans(0);
        line = Query(x, p);
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (Query(mid, p) - line >= k) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        printf ("%d\n", ans);
    }
    system("pause");
}
```

---

