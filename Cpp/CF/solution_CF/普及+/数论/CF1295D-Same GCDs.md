# Same GCDs

## 题目描述

You are given two integers $ a $ and $ m $ . Calculate the number of integers $ x $ such that $ 0 \le x < m $ and $ \gcd(a, m) = \gcd(a + x, m) $ .

Note: $ \gcd(a, b) $ is the greatest common divisor of $ a $ and $ b $ .

## 说明/提示

In the first test case appropriate $ x $ -s are $ [0, 1, 3, 4, 6, 7] $ .

In the second test case the only appropriate $ x $ is $ 0 $ .

## 样例 #1

### 输入

```
3
4 9
5 10
42 9999999967```

### 输出

```
6
1
9999999966```

# 题解

## 作者：caidzh (赞：18)

设$d=gcd(a,m)$，则：

$$gcd(\frac{a}{d},\frac{m}{d})=gcd(\frac{a+x}{d},\frac{m}{d})=1$$

发现$a$仅仅是将$[0,m-1]$的数进行了一段平移，因此答案为$\phi(\frac{m}{d})$

---

## 作者：樱雪喵 (赞：16)

前置知识：
- 辗转相除法
- 欧拉函数

首先，根据辗转相除法求 $\gcd$ 的公式，可得 $\gcd(a+x,m)=\gcd((a+x)\mod m,m)$。  
则题目可以转化为：求有多少 $x$ 满足 $\gcd(x,m)=\gcd(a,m)$，设 $\gcd(a,m)$ 等于定值 $k$。  
等式两边同时除以 $k$，得 $\gcd(\dfrac{x}{k},\dfrac{m}{k})=1$。即求与 $\dfrac{m}{k}$ 互质的数的个数，根据欧拉函数的定义知答案为 $\varphi(\dfrac{m}{k})$。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,m;
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&a,&m);
		int n=m/__gcd(a,m);
		int ans=n;
		for(int i=2;i*i<=n;i++)
		{
			if(n%i==0) ans=ans/i*(i-1);
			while(n%i==0) n/=i;
		}
		if(n>1) ans=ans/n*(n-1);
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Sweetlemon (赞：14)

### [CF1295D Same GCDs](https://www.luogu.com.cn/problem/CF1295D)

#### 题意

给定两个整数 $a,m\ (1\le a<m\le 10^{10})$。计算满足条件 $0 \le x < m$ 且 $\gcd(a,m)=\gcd(a+x,m)$ 的整数 $x$ 的个数。

#### 简单转化

首先可以注意到，$a$ 和 $m$ 都是已知的，因此可以求出 $a,m$ 的最大公因数 $g$。那么，$\gcd(a,m)=\gcd(a+x,m)=g\ (0\le x<m)$ 就等价于 $\gcd(a',m')=\gcd(a'+x',m')=1\ (0\le x'<m')$，其中 $a',m',x'$ 满足 $a=ga',\ m=gm',x=gx'$。

下文中将整数 $u$ 与 $v$ 互质记作 $u\perp v$。为下文叙述方便起见，转化完成后，我们令 $a=a',m=m',x=x'$，即假设我们已经把 $a$ 和 $m$ 都除以了 $g$。那么我们现在就是已知 $a\perp m$，想求满足 $(a+x)\perp m,0\le x<m$ 的整数 $x$ 的个数。

#### 方法 1：莫比乌斯函数

看到“互质”，通常就可以用莫比乌斯函数进行转化了。

$$\begin{aligned}&\sum^{m-1}_{x=0}[(a+x)\perp m]\\=&\sum^{m-1}_{x=0}\sum_{d\mid (a+x)\ \land\  d\mid m}\mu(d)\\=&\sum_{d\mid m}\mu(d)\sum^{m-1}_{x=0}[d\mid (a+x)]\\=&\sum_{d\mid m}\mu(d)\left (\left \lfloor \frac{a+m-1}{d} \right\rfloor-\left\lfloor \frac{a-1}{d} \right\rfloor\right )\end{aligned}$$

第一行是原始统计量，第二行用了 $\sum_{d\mid x}\mu(d)=[x=1]$ 的常见转化，第三行交换了 $x,d$ 两层求和的顺序，第四行把内层求和用式子简化了。

于是现在我们只需对 $m$ 的每一个约数进行上述求和即可。那么我们需要找出 $m$ 的每一个约数，还要算出它每一个约数的 $\mu$ 值。

找约数自然可以 $\mathrm{O}(\sqrt{m})$ 找，那 $\mu$ 值怎么算呢？

设 $m$ 有 $t$ 个不同的质因子，那么实际上 $m$ 只有 $2^t$ 个约数的 $\mu$ 非零，而通过计算发现 $m\le 10^{10}$ 时 $t\le 10$，因此我们只需把 $m$ 质因数分解，再枚举 $m$ 质因子集合的子集，计算出相应的无平方因子约数，更新答案即可。

总时间复杂度 $\mathrm{O}(\sqrt{m}+2^t)=\mathrm{O}(\sqrt{m})$。

#### 方法 2：欧拉函数

赛时我也一度猜想答案就是 $\varphi(m)$，但是因为一时无法证明，并且方法 1 也能想出来，因此就没有更深入地探究。赛后看到讨论区有这个方法，就仔细想了想，还是比较妙的。

既然我们想要证明答案是 $\varphi(m)$，那么我们就要把 “所有与 $m$ 互质的（下文称为合法的）$a+x$” 和 “$[1,m]$ 中所有与 $m$ 互质的整数” 一一对应起来。下面构造一个这样的一一对应。

1. 若 $0\le x\le m-a$，则 $a\le a+x\le m$，合法的 $a+x$ 一一对应 $[a,m]$ 中与 $m$ 互质的数。

2. 若 $m-a+1\le x< m$，则 $m+1\le a+x\le m+a-1$。因为 $\gcd(u+v,v)=\gcd(u,v)$，所以 $u\perp v \Leftrightarrow (u+v)\perp v$，于是我们得到 $(a+x)\perp m\Leftrightarrow (a+x-m)\perp m$。因此合法的 $a+x$ 一一对应 $[1,a-1]$ 中与 $m$ 互质的数。

综上，所有与 $m$ 互质的 $a+x$ 一一对应 $[1,m]$ 中所有与 $m$ 互质的整数，有 $\varphi(m)$ 个。于是我们只需要求出 $\varphi(m)$ 作为答案即可。

这种方法只需要求 $\varphi(m)$，需要对 $m$ 进行质因数分解，时间复杂度 $\mathrm{O}(\sqrt{m})$。

#### 拓展

事实上，任意 $m$ 个连续正整数中与 $m$ 互质的数的个数恰为 $\varphi(m)$；或者说，把这道题中 $a<m$ 的条件去除，答案不变。这个结论可以用上述两种方法来证明。

**用 $\mu$ 证明。** 设 $a=qm+r\ (q,r\in \mathbb{N},0\le r<m)$，则答案式可以进行如下化简：

$$\begin{aligned}&\sum_{d\mid m}\mu(d)\left (\left \lfloor \frac{a+m-1}{d} \right\rfloor-\left\lfloor \frac{a-1}{d} \right\rfloor\right )\\=&\sum_{d\mid m}\mu(d)\left (\left \lfloor \frac{qm+r+m-1}{d} \right\rfloor-\left\lfloor \frac{qm+r-1}{d} \right\rfloor\right )\\=&\sum_{d\mid m}\mu(d)\left (\frac{qm}{d}+\left \lfloor\frac{r+m-1}{d} \right\rfloor-\frac{qm}{d}-\left\lfloor \frac{r-1}{d} \right\rfloor\right )\\=&\sum_{d\mid m}\mu(d)\left (\left \lfloor\frac{r+m-1}{d} \right\rfloor-\left\lfloor \frac{r-1}{d} \right\rfloor\right )\\=&\varphi(m)\end{aligned}$$

第一行带入了方法一的答案式子，第二行把 $a$ 代换为 $qm+r$，第三行利用了整数可以自由移出取整符号的性质，第四行把 $\frac{qm}{d}$ 去除，第五行运用了题目中答案的性质。

**用映射方法证明。** 取这连续 $m$ 个正整数模 $m$ 的余数，一定分别是 $0,1,\cdots,m-1$。我们把这些正整数根据模 $m$ 的余数从小到大排序，分别记为 $n_0,n_1,\cdots,n_k,\cdots,n_{m-1}$；也就是说，$n_k\equiv k\pmod{m}$。由于 $\gcd(a,b)=\gcd(b,a\%b)$，因此 $\gcd(n_k,m)=\gcd(m,k)$，于是我们得到 $n_k\perp m\Leftrightarrow k\perp m$，这样我们就建立了“$n_0,\cdots,n_{m-1}$ 当中与 $m$ 互质的整数”和“$[0,m-1]$ 中与 $m$ 互质的整数”的一一对应（假设 $0$ 不与任何数互质；$m=1$ 的情况特殊，可以单独拿出来讨论）。因此，任意连续 $m$ 个正整数当中，与 $m$ 互质的数一共有 $\varphi(m)$ 个。

同时通过这道题的推导，我们也得到了 $\varphi$ 函数用约数的 $\mu$ 函数表达的式子 $\varphi(n)=\sum_{d\mid n} \mu(d)\frac{n}{d}$，也就是 $\varphi=\mu*\mathrm{id}$。

#### 代码

提供 $\mu$ 版本和 $\varphi$ 版本的代码。

$\mu$ 版本：

```cpp
//Submitted on luogu, mu version
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cmath>
#define MAXIOLG 25
using namespace std;

//Constant area
#define MAXN 109005

typedef long long ll;
typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void); //快读，实现略去
void ayano(io_t x,char spliter='\n'); //快写，实现略去

ll prs[MAXN]; //存储质因子

ll gcd(ll a,ll b);

int main(void){
    int testcases=seto();
    while (testcases--){
        ll a,m,g;
        ll ans=0;
        a=seto(),m=seto(),g=gcd(a,m),a/=g,m/=g;
        if (m==1){
            ayano(1);
            continue;
        }
        ll sqrm=sqrt(m)+2;
        ll mm=m;
        int prcnt=0;
        for (int i=2;i<=sqrm;i++){
            if (m/i*i!=m)
                continue;
            prcnt++,prs[prcnt]=i;
            while (m/i*i==m)
                m/=i;
        }
        if (m>1)
            prcnt++,prs[prcnt]=m;
        m=mm;
        //枚举无平方因子的约数
        int ful=1<<prcnt;
        for (int i=0;i<ful;i++){
            ll res=1;
            int tmu=1;
            int j=i;
            for (int k=1;k<=prcnt;k++){
                if (j&1)
                    res*=prs[k],tmu=-tmu;
                j>>=1;
            }
            ans+=1ll*tmu*((a+m-1)/res-(a-1)/res);
        }
        ayano(ans);
    }
    return 0;
}

ll gcd(ll a,ll b){
    ll t;
    while (b)
        t=a,a=b,b=t%b;
    return a;
}
```

$\varphi$ 版本：

```cpp
//Submitted on luogu, phi version
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cmath>
#define MAXIOLG 25
using namespace std;

//Constant area
#define MAXN 109005

typedef long long ll;
typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void); //快读，实现略去
void ayano(io_t x,char spliter='\n'); //快写，实现略去

ll gcd(ll a,ll b);

int main(void){
    int testcases=seto();
    while (testcases--){
        ll a,m,g;
        a=seto(),m=seto(),g=gcd(a,m),a/=g,m/=g;
        ll sqrm=sqrt(m)+2;
        ll ans=m;
        for (int i=2;i<=sqrm;i++){
            if (m/i*i!=m)
                continue;
            ans/=i,ans*=(i-1);
            while (m/i*i==m)
                m/=i;
        }
        if (m>1)
            ans/=m,ans*=(m-1);
        ayano(ans);
    }
    return 0;
}

ll gcd(ll a,ll b){
    ll t;
    while (b)
        t=a,a=b,b=t%b;
    return a;
}
```

---

## 作者：SDqwq (赞：9)

[博客食用更佳](https://www.luogu.com.cn/blog/Sham-Devour/solution-cf1295d)

[前置芝士：欧拉函数](https://oi-wiki.org/math/euler/)

# $\texttt{Step 0 题意}$

见题面。

# $\texttt{Step 1 正解}$

由辗转相除法得：

$$\gcd(a+x,m)=\gcd((a+x)\mod m,m)$$

显然，当 $x$ 的值域为 $[0,m)$ 时，$(a+x)\mod m$ 的值域也为 $[0,m)$，则：

$$\sum\limits_{x=0}^{m-1}[\gcd(a,m)=\gcd(a+x,m)]=\sum\limits_{x=0}^{m-1}[\gcd(a,m)=\gcd(x,m)]$$

设 $\gcd(a,m)=\gcd(x,m)=d$，容易发现：

$$\gcd(\frac{x}{d},\frac{m}{d})=1$$

于是问题转化为比 $\frac{m}{d}$ 小且与其互质的数的个数，所以答案为：

$$\phi(\frac{m}{\gcd(a,m)})$$

时间复杂度：$\mathcal{O}(\sqrt{\frac{m}{\gcd(a,m)}})$

# $\texttt{Step 2 代码}$

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;
ll gcd (ll x, ll y) {return y == 0 ? x : gcd(y, x % y);}

ll phi (ll n) {
	ll ans = n;
	for (ll i = 2; i * i <= n; i++)
		if (n % i == 0) {
			ans = ans / i * (i - 1);
			while (n % i == 0)
				n /= i;
		}
	if (n > 1)
		ans = ans / n * (n - 1);
	return ans;
}

int main () {
	int T;
	scanf("%d", &T);
	while (T--) {
		ll a, m;
		scanf("%lld %lld", &a, &m);
		printf("%lld\n", phi(m / gcd(a, m)));
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：3)

一眼看上去还是有点难度的。

## 思路

首先看到了 $x$ 是 $[0,m-1]$，正好对应了 $m$ 所有的 mod 值。然后我们可以稍作推导：

$\gcd(a+x,m) = \gcd((a+x) \% m,m)$。

又因为 $x$ 是 $[0,m-1]$ 的，所以得出：

$$\sum\limits_{x=0}^{m-1} (a+x)\%m = \sum_{x=0}^{m-1} x \% m$$

因为，无论 $a\%m$ 取何值，总会“绕一圈”回来。比如：对 5 取模会得到 ```0 1 2 3 4``` 这 5 种不同的值，把这个值的串首尾相连组成一个环，无论从哪个点开始走 $m-1$ 次总会遍历所有的点。

那么原式就转化成：

$$\sum\limits_{x=0}^{m-1}[\gcd(a,m) = \gcd(x,m)]$$

那么我们令 $p = \gcd(a,m)$。于是得到这个式子：

$$\sum\limits_{x=0}^{m-1}[\frac{\gcd(a,m)}{p} = \frac{\gcd(x,m)}{p}]$$

也就是：

$$\sum\limits_{x=0}^{m-1}[1 = \frac{\gcd(x,m)}{p}]$$

即求：

$$\phi(\frac{\gcd(x,m)}{p})$$

这个显然可以 $O(\sqrt{n})$ 求出。总时间复杂度 $O(T \sqrt{n})$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll phi(ll x)
{
	ll ans=x;
	for(ll i=2;i*i<=x;i++)
		if(x%i==0)
		{
			ans=ans/i*(i-1);
			while(x%i==0) x/=i;
		}
	if(x>1) ans=ans/x*(x-1);
	return ans;
}
int main()
{
	int T; cin>>T;
	while(T--)
	{
		ll a,b; cin>>a>>b;
		ll qwq=__gcd(a,b);
		printf("%lld\n",phi(b/qwq));
	}
	return 0;
}
```

---

## 作者：tuzhewen (赞：3)

谔谔，第一篇题解有点过于简略了吧(

进入正题，题目说要求使得$gcd(a+x,m)=gcd(a,m)$成立的$x$的个数

那么这道题显然可以用莫反，但是不必那么麻烦。众所周知，$gcd(a,b)=gcd(a-b,b)$，那么这个题目就成了求多少个$x$满足$gcd(a,m)=gcd(x,m)$。所以答案就是$\varphi(\frac{m}{gcd(a,m)})$了！~~（你看多明了简洁的式子）~~

很好写，因为只求一次，所以并不用处理出所有的$\varphi$，那么就是这个样子的了。

### $ACcode$: 
```
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define D(i,r,l) for(register int i=r;i>=l;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
const int INF=0x3f3f3f3f;
using namespace std;
ll a,m;
int T;
ll phi(ll x) {//开ll啊喂
	ll ans=x;
	F(i,2,sqrt(x)) {
		if(x%i==0) {
			ans=ans/i*(i-1);
			while(x%i==0) x/=i;
		}
	}
	if(x>1) ans=ans/x*(x-1);//根据phi的定义来求解
	return ans;
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%lld%lld",&a,&m);
		printf("%lld\n",phi(m/(__gcd(a,m))));//简单的式子
	}
	return 0;
}
```

~~求反手留赞QAQ~~

---

## 作者：ix35 (赞：3)

好像没有看到什么莫比乌斯反演的解法，这里提供一下。

要令 $gcd(a,m)=gcd(a+k,m)$，什么也看不出来，那就先求出 $d=gcd(a,m)$ 再说吧。

然后我们就是要求 $|\{k|a\leq k\leq a+m-1,gcd(k,m)=d\}|$。

这个东西可以容斥一下，令 $f(x)=|\{k|k\leq x,gcd(k,m)=d\}|$，那么答案就是 $f(a+m-1)-f(a-1)$。

下面就是一个很简单的推导。

$$f(n)=\sum\limits_{i=1}^n [gcd(i,m)=d]$$

$$f(n)=\sum\limits_{i=1}^{n/d} [gcd(i,m/d)=1]$$

$$f(n)=\sum\limits_{i=1}^{n/d} \sum\limits_{p|i,p|\frac{m}{d}} \mu(p)$$

$$f(n)=\sum\limits_{p|\frac{m}{d}}\mu(p) \dfrac{n}{pd}$$

于是枚举 $\dfrac{m}{d}$ 的因数算 $\mu$ 就可以了。

这里我采用了分解素因数后 DFS 算 $\mu$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll t,a,m,tot;
pair<ll,ll> p[30];
ll gcd (ll a,ll b) {return (b==0?a:gcd(b,a%b));}
ll dfs (ll a,ll ly,ll prod,ll n) {
	if (ly==tot+1) {return a*(n/prod);}
	ll res=0;
	for (int i=0;i<=1;i++) {
		res+=dfs(a,ly+1,prod,n);
		prod*=p[ly].first;
		if (i==0) {a*=-1;}
	}
	return res;
}
int main () {
	scanf("%lld",&t);
	for (int ii=1;ii<=t;ii++) {
		scanf("%lld%lld",&a,&m);
		ll cpy=m,tmp=gcd(a,m);
		m/=tmp;
		tot=0;
		for (ll i=2;i*i<=m;i++) {
			if (m%i==0) {
				tot++;
				ll sum=0;
				while (m%i==0) {sum++,m/=i;}
				p[tot]=make_pair(i,sum);
			}
		}
		if (m>1) {p[++tot]=make_pair(m,1);}
		printf("%lld\n",dfs(1,1,1,(a+cpy-1)/tmp)-dfs(1,1,1,(a-1)/tmp));
	}
	return 0;
}
```


---

## 作者：QwQ蒟蒻wjr (赞：2)

[我的blog](https://www.cnblogs.com/wangjunrui/p/12242400.html)
> > 题目链接：[CF1295D Same GCDs](https://www.luogu.com.cn/problem/CF1295D)

$$description$$

给定$a,m$，求出有多少个$x$满足$0\leq x<m$且
$$gcd(a,m)=gcd(a+x,m)$$

$gcd(x,y)$表示$x$和$y$的最大公因数

$$solution$$

数论题

考虑设$d=gcd(a,m)$

肯定满足$d|a,d|m,d|(a+x)$

$\therefore d|x$

### 结论1：
$$gcd(\frac{a+x}{d},\frac{m}{d})=1$$
### 证明：
假设$gcd(\frac{a+x}{d},\frac{m}{d})\neq 1$

即$gcd(\frac{a+x}{d},\frac{m}{d})> 1$

此时
$$gcd(a+x,m)=gcd(\frac{a+x}{d}\times d,\frac{m}{d}\times d)>d$$

即$gcd(a+x,m)\neq gcd(a,m)$

互相矛盾

综上所述：$gcd(\frac{a+x}{d},\frac{m}{d})=1$成立

### 结论2：
答案是
$$\varphi(\frac{m}{d})$$

显然对与任意与m互质的数$p$和任意正整数$k$
满足：
$$gcd(p+\frac {km}{d},\frac{m}{d})=gcd((p+k\frac{m}{d})\ mod\ \frac{m}{d},\frac{m}{d})=gcd(p,\frac{m}{d})=1$$

显然$p+\frac {km}{d}$与$\frac{m}{d}$互质

对于当$a+x\leq m$，答案是$\frac{a}{d}\leq x\leq \frac{m}{d}$的与$\frac{m}{d}$互质的个数

对于与$m<a+x<a+m$，答案是$x<\frac{a}{d}$的与$\frac{m}{d}$互质的个数

两个答案区间合并即是$\varphi(\frac{m}{d})$

### 欧拉函数:
其中$p_1, p_2……p_k$为$n$的所有质因数，$n$是不为$0$的整数。$\varphi(1)=1$（唯一和$1$互质的数就是$1$本身）。

$$\varphi(n)=n\prod _ {i=1}^{k}(1-\frac{1}{p_i})$$ 

因为n最多有一个大于$\sqrt{n}$的质因数

所以可以得到以下代码
```cpp
inline long long Eular(long long n)
{
	long long ans=n;
	for(re int i=2; 1ll*i*i<= n; i++)
	{
		if(n%i==0)
		{
			ans-=ans/i;
			while(n%i==0)
				n/=i;
		}
	}
	if(n>1)
		ans-=ans/n;
	return ans;
}
```
欧拉函数复杂度$O(\sqrt n)$

算法总复杂度$O(T\sqrt n)$

$$code$$

```cpp
#include<cstdio>
#define re register
#define ll long long
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
	return;
}
inline ll gcd(ll a,ll b)
{
	return b==0?a:gcd(b,a%b);
}
 
inline long long Eular(long long n)
{
	long long ans=n;
	for(re int i=2; 1ll*i*i<= n; i++)
	{
		if(n%i==0)
		{
			ans-=ans/i;
			while(n%i==0)
				n/=i;
		}
	}
	if(n>1)
		ans-=ans/n;
	return ans;
}
int T;
int main()
{
	read(T);
	while(T--)
	{
		ll a,m;
		read(a),read(m);
		printf("%lld\n",Eular(m/gcd(a,m)));
	}
 
	return 0;
}



```

---

## 作者：loser_seele (赞：1)

提供一种理论复杂度更优的做法。

由辗转相除法可得 $ \gcd(a+x,m)=\gcd((a+x) \bmod m,m) $

则转化为求 $ m-1 $ 以内满足 $ \gcd(x,m)=\gcd(a,m) $ 的 $ x $ 的个数。

不妨把 $ x $ 除以 $ \gcd(a,m) $ ，则问题转化为求小于 $ \frac{m}{\gcd(a,m)} $ 并与其互质的数的数量，即 $ \varphi(\frac{m}{\gcd(a,m)}) $。

接下来是重点。

因为题目只要求单次询问，所以可以用 Pollard-rho 快速分解质因数的方法在 $ \mathcal{O}(n^{1/4}) $ 的时间复杂度内求出 $ \varphi(n) $ 的值。

具体方法是求出所有质因子之后，设当前质因子为 $ d $ ，计算每个质因子后每次乘上 $ \frac{d-1}{d} $ 即可。

实现上注意两个 $ 10^{10} $ 级别的数相乘需要用快速乘或者开 int128 乘法即可。

实际上跑得很快，但没跑过最优解。

总的时间复杂度是 $ \mathcal{O}(Tn^{\frac{1}{4}}) $。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define gc c=getchar()
#define r(x) read(x)
#define ll long long
#define int long long
template<typename T>
inline void read(T&x)
{
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}
#define li inline
#define re register
inline int add(int a,int b,int p)
{
	a+=b;
	if(a>=p)
    a-=p;
	return a;
}
inline int mul(int a,int b,int mod)
{
return (a*b-(int)((long double)a/mod*b)*mod+mod)%mod;
}
ll pow(ll a, ll b, ll m) 
{
  ll ans = 1;
  for (a %= m; b; b >>= 1, a = mul(a, a, m))
    if (b & 1) 
    ans = mul(ans, a, m);
  return ans;
}
ll gcd(ll a,ll b)
{
	return b?gcd(b,a%b):a;
}
ll lcm(ll a,ll b)
{
	return a/gcd(a,b)*b;
}
bool MR_check(ll a, ll p, ll s, int d) 
{
  ll k = pow(a, s, p);
  if (k == 1) return true;
  for (; d; --d, k = mul(k, k, p)) 
  {
    if (k == p - 1) 
    return true;
    if (k == 1) 
    return false;
  }
  return k == 1;
}
bool MR(ll x) 
{
  static const int cnt = 12;
  static const int p[cnt] = { 2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251 };
  if (x == 1) 
  return false;
  ll s = x - 1; 
  int d = 0;
  while (!(s & 1)) 
  ++d, s >>= 1;
  for (int i = 0; i < cnt; ++i) 
  {
    if (x % p[i] == 0) 
    return x == p[i];
    if (!MR_check(p[i], x, s, d)) 
    return false;
  }
  return true;
}
namespace Pollard_Rho 
{
ll PR_check(ll c, ll p) 
{
  ll y = rand() % p, z = y;
  int k = 1, j = 0;
  while(1145141919810) 
  {
    z = (mul(z, z, p) + c) % p;
    ll t = gcd(p, std::abs(z - y));
    if (t > 1) 
    return t;
    if (++j == k) 
    y = z, k <<= 1;
  }
}
void factor_(ll x, std::vector<ll> &v) 
{
  if (x == 1) return;
  if (MR(x)) { v.push_back(x); return; }
  ll y = x;
  while (y == x) y = PR_check(rand() % x, x);
  factor_(y, v);
  factor_(x / y, v);
}
void factor(ll x, std::vector<ll> &v) 
{
  v.clear();
  if (!(x & 1)) { v.push_back(2); x /= (x & -x); }
  factor_(x, v);
  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
}
}
using Pollard_Rho::factor;
struct fib 
{
  ll a, b; 
  fib(ll a, ll b) : a(a), b(b) {}
};
fib mul(const fib &u, const fib &v, ll m) 
{
  ll x = mul(u.a, v.a, m), y = mul(u.b, v.b, m),
     z = mul(u.a + u.b, v.a + v.b, m);
  return fib((x + y) % m, (z - x + m) % m);
}
bool check_period(ll d, ll m) 
{
  fib ans(1, 0), a(0, 1);
  for (; d; d >>= 1, a = mul(a, a, m))
    if (d & 1) ans = mul(ans, a, m);
  return ans.a == 1 && ans.b == 0;
}
inline int query(int x)
{
	if(x==2)
    return 3;
	if(x==3)
    return 8;
	if(x==5)
    return 20;
	ll t = (x % 10 == 1 || x % 10 == 9) ? x - 1 : 2 * (x + 1);
  vector<ll> d;
  factor(t, d);
  for (auto g : d)
    while (!(t % g) && check_period(t / g, x))
      t /= g;
  return t;
}
inline ll solve(int n)
{
	ll ans=1;
    vector<int>d;
    factor(n, d);
    for(auto res:d)
    {
    int p=1;
    while(n%res==0)
    n/=res,p*=res;
    ans=lcm(ans,p/res*query(res));
    }
	return ans;
}
signed main()
{
    int T;
    for(r(T);T;--T)
    {
    	int a,n;
        r(a),r(n);
        n=n/gcd(a,n);
        vector<int>d;
    	Pollard_Rho::factor(n,d);
        for(auto x:d)
        n/=x,n*=(x-1);
        printf("%lld\n",n);
    }
}
```


---

## 作者：DepletedPrism (赞：1)

提供一种容斥做法, 其实和欧拉函数做法本质没什么区别, ~~毕竟都是容斥~~

首先要求的是这个东西

$$\sum_{i=0}^{m-1} [\ \gcd(a, m) = \gcd(a + i, m)\ ]$$

设 $b = \gcd(a, m)$, 令 $a = p \cdot b,\ m = q \cdot b$, 原式可化为

$$\sum_{i=0}^{m-1} [\ \gcd(pb + \frac{i}{b}, qb) = b \ ]$$

$$\sum_{i=0}^{m-1} [\ \gcd(p + \frac{i}{b}, q) = 1 \ ]$$

即 $[ p,\ p + \lfloor \dfrac{m-1}{b} \rfloor ]$ 同 $q$ 互质个数.

采用 [HDU-4135](https://vjudge.net/problem/HDU-4135) 同样的方法, 对 $q$ 分解质因数后容斥计算即可.

详情可搜索: 区间互质个数, 这里不再赘述

```cpp
// D
// DeP
#include <iostream>
using namespace std;

typedef long long LL;
const int MAXN = 1e5+5;

LL gcd(LL a, LL b) { return !b? a: gcd(b, a % b); }

LL fact[MAXN], tot;

void prime(LL n) {
    tot = 0;
    for (LL i = 2; i*i <= n; ++i) if (n % i == 0) {
        fact[++tot] = i;
        while (n % i == 0) n /= i;
    }
    if (n > 1) fact[++tot] = n;
}

LL calc(LL m) {
    static LL stk[MAXN], top, ret;
    stk[top = 1] = -1, ret = 0;
    for (int i = 1; i <= tot; ++i) {
        int z = top;
        for (int j = 1; j <= z; ++j) stk[++top] = -1LL * stk[j] * fact[i];
    }
    for (int i = 2; i <= top; ++i) ret += m / stk[i];
    return ret;
}

int main() {
    int Ti;
    cin >> Ti;
    while (Ti--) {
        LL a, m, b;
        cin >> a >> m;
        b = gcd(a, m);
        LL q = m / b, p = a / b;
        LL L = p, R = p + (m-1) / b;
        prime(q);
        cout << R - calc(R) - (L-1) + calc(L-1) << endl;
    }
    return 0;
}
```

---

## 作者：syksykCCC (赞：1)

题目是让我们求这个式子:

$$ \sum_{x = 0}^{m - 1} [\gcd(a, m) = \gcd(a + x, m)] $$

然后，根据辗转相除法，我们可以把它转化为：

$$ \sum_{x = 0}^{m - 1} [\gcd(a, m) = \gcd((a + x) \bmod m, m)] $$

右边就是把 $[0, m)$ 的区间向右平移了 $a$ 个单位，取模了以后显然还是 $[0, m)$ 的区间。

于是：

$$\sum_{i = 0}^{m -1} [\gcd(i, m) = \gcd(a, m)]$$

令 $g = \gcd(a, m)$，就是求：

$$\sum_{i = 0}^{m-1} [\gcd(i, m) = g]$$
$$ \sum_{0 \le i <m}^{g|i}\left[ \gcd\left(\dfrac i g , \dfrac m g \right) = 1 \right]$$

然后，左边的就是 $\left[1 , \dfrac m g \right)$ 的一段数，所以，这个就是：

$$ \sum_{i = 1}^{\frac m g - 1} \left[\gcd \left(i, \dfrac m g \right) = 1\right] $$

然后这个就是 $\varphi\left(\dfrac m g \right) = \varphi\left(\dfrac m {\gcd(a, m)} \right)$ 了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL gcd(LL a, LL b) { if(!b) return a; return gcd(b, a % b); }
LL phi(LL x)
{
	LL res = 1;
	for(LL i = 2; i * i <= x; i++)
	{
		if(x % i) continue;
		res *= i - 1; x /= i;
		while(x % i == 0) res *= i, x /= i;
	}
	if(x > 1) res *= x - 1;
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
	LL T;
	cin >> T;
	while(T--)
	{
		LL a, m;
		cin >> a >> m;
		cout << phi(m / gcd(a, m)) << endl;
	}
	return 0;
}
```

---

## 作者：KingPowers (赞：0)

引理：设 $d$ 是 $a,b$ 的一个公因数，$a=t_1d$，$b=t_2d$，那么 $\gcd(a,b)=d$ 当且仅当 $\gcd(t_1,t_2)=1$。

证明显然。

同理，对于本题我们先令 $d=\gcd(a,m)$，将 $a$ 和 $m$ 表示成 $d$ 的倍数的形式。那么原问题转化成了 $[a,a+m-1]$ 里有多少个 $d$ 的倍数除以 $d$ 之后与 $\frac{m}{d}$ 互质，而这些 $d$ 的倍数除以 $d$ 之后显然是一段连续的数。

转化成了一个经典问题：$[1,n]$ 内有多少个数与 $x$ 互质（区间的话差分下就行）。

这个问题有一种容斥做法，我们先补集转换成有多少个数与 $x$ 不互质，那么就相当于求有多少个数与 $x$ 有至少一个公共质因子，直接大力容斥即可，容斥系数为 $(-1)^{\text 公共质因子数+1}$。

展示下这部分代码：

```cpp
int calc(int n, int x){
	if(!n) return 0;
	vector<int> vec;
	for(int i = 2; i * i <= x; i++){
		if(x % i) continue;
		int siz = vec.size() - 1;
		For(j, 0, siz) vec.push_back(-vec[j] * i);
		while(!(x % i)) x /= i;
		vec.push_back(i);
	}
	if(x > 1){
		int siz = vec.size() - 1;
		For(j, 0, siz) vec.push_back(-vec[j] * x);
		vec.push_back(x);
	}
	int res = 0;
	for(int v : vec) res += n / v;
	return n - res;
}
```

这块复杂度应该是 $O(\sqrt n+2^{\omega (n)})$。

[提交记录](https://codeforces.com/contest/1295/submission/254365344)

---

## 作者：Cuiyi_SAI (赞：0)

## 题目描述

问存在多少个 $x$ 满足 $0\le x<m$ ，使得 $\gcd(a,m)=\gcd(a+x,m)$

---

我们将题目形式化：

$$
\sum\limits_{x=0}^{m-1}[\gcd(a,m)=\gcd(a+x,m)]
$$

我们把可以快速求得常数替换掉。设 $k=\gcd(a,m)$，求

$$
\sum\limits_{x=0}^{m-1}[\gcd(a+x,m)=k]
$$

为了看得舒服一点，我们将式子改为

$$
\sum\limits_{x=a}^{m+a-1}[\gcd(x,m)=k]
$$

然后观察式子，我们发现 $\sum\limits_{x=a}^{m+a-1}$ 这种形式的累加类似求一个区间内的和，因此我们可以使用容斥，设

$$
f(n)=\sum\limits_{i=0}^{n}[\gcd(i,m)=k]
$$

那么原式等于 $f(m+a-1)-f(a-1)$。

显然 $f(n)$ 的形式是我们所喜欢的，我们可以直接暴力上莫比乌斯反演。

$$
\begin{aligned}
f(n)&=\sum\limits_{i=0}^{n}[\gcd(i,m)=k]\\
&=\sum\limits_{i=0}^{\left\lfloor\frac{n}{k}\right\rfloor}[\gcd(i,\frac{m}{k})=1]\\
&=\sum\limits_{i=0}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum\limits_{d\mid i,d\mid \frac{m}{k}}\mu(d)\\
&=\sum\limits_{d\mid \frac{m}
{k}}\mu(d)\sum\limits_{i=0}^{\left\lfloor\frac{n}{dk}\right\rfloor}1\\
&=\sum\limits_{d\mid \frac{m}{k}}\mu(d)\left\lfloor\dfrac{n}{dk}\right\rfloor
\end{aligned}
$$

这个式子的复杂度属于我们可接受的范围，直接计算即可。

## CODE：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,a,m,k;
int mu(int x)
{
	int res=1;
	for(int i=2;i*i<=x;i++)
	{
		if(x%i!=0) continue;
		int cnt=0;
		while(x%i==0) x/=i,cnt++;
		if(cnt>1) return 0;
		res*=(-1);
	}
	if(x!=1) res*=(-1);
	return res;
}
int f(int n)
{
	int res=0;
	for(int i=1;i*i<=m;i++)
	{
		if(m%i!=0) continue;
		res+=(mu(i)*n/i);
		if(m/i==i) continue;
		res+=(mu(m/i)*n/(m/i));	
	}
	return res;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t)
	{
		t--;
		cin>>a>>m;
		k=__gcd(a,m);
		m/=k;
		cout<<f((m*k+a-1)/k)-f((a-1)/k)<<'\n';
	}
	return 0;
}
```
## 更优的方法

暴力推式子确实可以通过此题。但是如果我们仔细观察题目中的条件，就能得到一种更加简洁的解题思路。

考虑更相减损法，显然有 $\gcd(a,b)=gcd(a-b,b)$，因此 $\gcd(a+x,m)=\gcd( a+x-a,m)=\gcd(x,m)$，因此原题变为求有多少个 $x$ 使得 $\gcd(x,m)=\gcd(a,m)$，自然也就是 $\varphi\left(\dfrac{m}{\gcd(a,m)}\right)$。

---

## 作者：字如其人 (赞：0)

令 $d=\gcd(a,m)$，则有 $\gcd(a/d,m/d)=1$，所以题意就是求 $\sum_{i=1}^{m/d} [\gcd(i,m/d)=1]=phi(m/d)$。

试除法求 $\phi(m/d)$，总时间复杂度为 $O(T*\sqrt{m})$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,m;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
inline int phi(int x){
	int ans=x;
	for(int i=2;i<=sqrt(x);i++){
		if(x%i==0){
			ans=ans/i*(i-1);
			while(x%i==0)x/=i;
		}
	}
	if(x>1)ans=ans/x*(x-1);
	return ans;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&a,&m);
		int d=gcd(a,m);
		printf("%lld\n",phi(m/d));
	}
	return 0;
}
```


---

## 作者：Energy_Making (赞：0)

## 1.前置知识
[欧拉函数](https://oi-wiki.org/math/euler/)&[gcd](https://oi-wiki.org/math/gcd/)

## 2.推柿子
设 $d = \gcd(a,m)$ 

$$
\therefore \gcd(\frac{a}{d},\frac{m}{d})=\gcd(\frac{a+x}{d},\frac{m}{d})=1
$$
所以答案即为$\varphi(\dfrac md)$,求一下就好啦！

## 3.时间复杂度

$$
\mathcal O(\sqrt\frac{m}{\gcd(a,m)})
$$


---

