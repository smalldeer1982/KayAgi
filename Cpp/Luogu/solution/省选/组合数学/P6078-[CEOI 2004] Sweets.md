# [CEOI 2004] Sweets

## 题目描述

John 得到了 $n$ 罐糖果。不同的糖果罐，糖果的种类不同（即同一个糖果罐里的糖果种类是相同的，不同的糖果罐里的糖果的种类是不同的）。第 $i$ 个糖果罐里有 $m_{i}$ 个糖果。John 决定吃掉一些糖果，他想吃掉至少 $a$ 个糖果，但不超过 $b$ 个。问题是 John 无法确定吃多少个糖果和每种糖果各吃几个。有多少种方法可以做这件事呢？  

## 说明/提示

#### 数据范围及限制
对于 $100\%$ 的数据，保证 $1\leq n \leq 10$，$0\leq a \leq b \leq 10^7$，$0 \leq m_{i} \leq 10^6$。

#### 说明
本题译自 [Central European Olympiad
in Informatics 2004](https://www.oi.edu.pl/old/php/ceoi2004.php?module=show&file=news) [Day 1](https://www.oi.edu.pl/old/php/ceoi2004.php?module=show&file=tasks) [T2 Sweets](https://www.oi.edu.pl/old/ceoi2004/problems/swe.pdf)。

## 样例 #1

### 输入

```
2 1 3
3
5```

### 输出

```
9```

# 题解

## 作者：Rui_R (赞：29)

生成函数入门题。

题意：$n$ 种糖，每种糖有 $m_i$ 个，求选出 $l$ 到 $r$ 颗糖的方案数。$1 \le n \le 10,0 \le l,r \le 1e7,0 \le m_i \le 1e6$

[原题](https://www.luogu.com.cn/problem/P6078)

本文适合生成函数入门。

我们尝试用一个函数来描述状态：令系数表示方案数，令指数表示拿了几颗糖。例如，$2x^2$ 表示有两种方法拿两颗糖。

那么，对于每种糖，既然对于任意 $i\le m_i$ 都只有一种方法拿走 $i$ 颗这种糖，它的生成函数就是这个样子：

$$f(i)=\sum_{j=0}^{m_i}\limits x^j$$

我们发现，如果拿 $a_1$ 颗糖有 $b_1$ 种方案，拿 $a_2$ 颗糖有 $b_2$ 种方案，相当于有 $b_1\cdot b_2$ 种拿 $a_1+a_2$ 颗糖的方案。可以用 $b_1x^{a_1} \cdot b_2x^{a_2}=b_1\cdot b_2\cdot x^{a_1+a_2}$ 来描述这个过程。

于是，我们枚举当前这种糖拿几颗，与之前计算得到的结果按上述方法更新答案，这样一步步枚举糖下去最后就是答案。

**实际上这就是乘法。**

所以每种糖的 $f$ 全乘起来，指数在 $l,r$ 之间的系数和就是答案 ( $g$ ) 。

但是，如果大力多项式乘法算 $g$，你看一眼数据范围就知道会出事情。我们考虑有什么巧妙的方法。

首先，问题可以转化为求 $g$ 的系数的前缀和。那么假设我们现在要求从$x^0$ 到 $x^{lim}$ 的系数前缀和。

观察 $f$：
$$f(i)=\sum_{j=0}^{m_i}\limits x^j,x\cdot f(i)=\sum_{j=1}^{m_i+1} x^j$$

$$f(i)-x\cdot f(i)=(1-x)f(i)=1-x^{m_i+1}$$

$$f(i)=\dfrac{1-x^{m_i+1}}{1-x}$$

上面的推导在生成函数中似乎很重要。

于是最后的结果等于 $\dfrac{\prod{(1-x^{m_i+1})}}{(1-x)^n}$

上面的东西，由于 $n \le 10$ ，我们可以直接大力 $\text{dfs}$ 拆式子，假设它拆出来个 $g'$ 好了

观察下面的东西：

$$\dfrac{1}{(1-x)^n} =(1-x)^{-n} $$

二项式定理拆开，得到

$$\sum_{i\ge0}{ \binom{-n}{i} \cdot(-x)^i }$$

$$=\sum_{i\ge0}{\dfrac{(-n)(-n-1)...(-n-i+1)}{i!}\cdot (-x)^i}$$

$$=\sum_{i\ge0}{\dfrac{n(n+1)...(n+i-1)}{i!}\cdot x^i}$$

$$=\sum_{i\ge0}{\binom{n+i-1}{i}\cdot x^i}$$

此时我们将除法转换成了乘法。

那么我们考虑 $g'$ 上一项 $ax^b$ 对答案的贡献是多少。

$$a \cdot \sum_{}^{lim-b}\binom{n+i-1}{i}=a \cdot \binom{n+lim-b}{lim-b}$$

（不知道为什么的话，可以用组合数的递推公式 $\binom{m}{n}=\binom{m-1}{n-1}+\binom{m-1}{n}$ 证一下，不难）

那么现在只剩下最后一个问题，怎么算组合数了。毕竟模数是 $2004$，很不幸不是质数，导致没有逆元。当然可以扩展卢卡斯，但是似乎有更便捷的方法。

$$\binom{n+lim-b}{lim-b}=\binom{n+lim-b}{n}$$

$$=\dfrac{(n+lim-b)(n+lim-b-1)...}{n!}$$

注意到上面的部分总共只会有 $n$ 个，能迅速得到（令其为 $x$），下面的部分也很好算。

令$x=2004\cdot n!\cdot k2+r,\dfrac{x}{n!}\equiv ans \pmod{2004}$，$k$ 为整数

$$\dfrac{x}{n!}=ans+2004\cdot k1$$

$$2004\cdot n! \cdot k2+r=ans\cdot n!+2004\cdot k1\cdot n!$$

$$r=ans\cdot n! + 2004\cdot k'\cdot n!=(ans+2004\cdot k')n!$$

$$\dfrac{r}{n!}=ans+2004\cdot k'$$

$$\dfrac{r}{n!}\equiv ans \pmod{2004}$$

综上，我们可以计算 $x$ 在模 $2004\cdot n!$ 意义下的答案，将其除以 $n!$ 得到 $x$ 除以 $n!$ 在模 $2004$ 意义下的结果。

扩展开来，对于模数非质数的除法，可以先把模数乘上除数，再将运算结果除以除数得到答案。算是个不太有用的小技巧？虽然有点偏题，但是其它题解都没有给出这个的证明。

那么，这道题就解决了。

代码：
```
#include <cstdio>

typedef long long ll;
const int maxn=15,mod=2004;

int n,l,r;ll a[maxn],fac=1,sum=0;

inline ll C(int x,int y){
	ll M=mod*fac,ans=1;
	for(int i=y-x+1;i<=y;i++) ans=(ans*i)%M;
	return (ans/fac)%mod;
}

void dfs(int step,int val,int key,int lim){//step->第几种糖 val->系数 key->次数 lim->前lim次的前缀和
	if(key>lim) return;
	if(step==n+1){
		sum+=1ll*val*C(n,n+lim-key)%mod;
		sum%=mod;return;
	}
	dfs(step+1,val,key,lim),dfs(step+1,-val,key+a[step]+1,lim);
}

inline ll solve(int lim){
	sum=0;dfs(1,1,0,lim);
	return (sum%mod+mod)%mod;
}

int main(){
	scanf("%d%d%d",&n,&l,&r);for(int i=1;i<=n;i++) scanf("%lld",&a[i]),fac=fac*i;//fac不能取模2004，小心顺手打个%mod上去
	printf("%lld\n",((solve(r)-solve(l-1))%mod+mod)%mod);
	return 0;
}

```





---

## 作者：Durancer (赞：9)

### 前言

生成函数入门题，需要一定的组合数学基础

### 前置知识

1、牛顿二项式定理

2、组合数公式递推关系

3、明白生成函数原理

### 思路

首先可以得到在第 $i$ 罐中吃 $j$ 个的方案数贡献一定为 $1$

所以可以得到

$$F_i(x)=\sum_{i=0}^{m_i}x^i=\frac{1-x^{m_i+1}}{1-x}$$

设 $G(x)$ 为吃$k$颗糖的方案数 ($(x^k)$的系数) 为多少，那么总起来就是

$$G(x)=\prod^{n}_{i=1}\frac{1-x^{m_i+1}}{1-x}$$

$$G(x)=(1-x)^{-n}\prod^{n}_{i=1}(1-x^{m_i+1})$$

$$\text{考虑来化简}(1-x)^{-n}$$

$$\text{根据牛顿二项式定理得到}$$

$$(1-x)^{-n}=\sum_{i=0}^{\infty}\binom{-n}{i}(-x)^{i}$$

$$=\sum_{i=0}^{\infty}\frac{(-n)^{\underline{i}}}{i!}(-x)^i$$

$$=\sum_{i=0}^{\infty}\frac{\frac{(-n)!}{(-n-i)!}}{i!}(-x)^i$$

$$=\sum_{i=0}^{\infty}\frac{(-n)(-n-1)(-n-2)…(-n-i+1)}{i!}(-x)^i$$

$$\text{把上面负号消掉,因为分子和-x都是i个负号}$$

$$=\sum_{i=0}^{\infty}\frac{n(n+1)(n+2)…(n+i-1)}{i!}x^i$$

$$=\sum_{i=0}^{\infty}\frac{\frac{(n+i-1)!}{(n+i-1-i)!}}{i!}x^i$$

$$=\sum_{i=0}^{\infty}\binom{n+i-1}{i}x^i$$

$$G(x)=\sum_{i=0}^{\infty} \binom{n+i-1}{i}x^i\times \prod^{n}_{i=1}(1-x^{m_i+1})$$

枚举$\prod_{i=1}^{n} (1-x^{m^{i}+1})$ 中 $x^k$ 的系数，简单表示成 $num_k$

$$num_k \times \sum_{i=a-k}^{b-k}\binom{n-1+i}{i}$$

$$\text{通过}\binom{n}{m}=\binom{n-1}{m-1}+\binom{n-1}{m} \text{可以得到}$$

$$num_k \times ( \binom{n+b-k}{b-k}-\binom{n+a-k-1}{a-k-1})$$

因为 $n$ 的值特别小，所以可以做到 $O(2^n+b)$ 求解答案

### 实现

考虑到 $n$ 很小，所以直接搜索求解

看 $G(x)$ 的右边一式，每一个都是 $-x^{m_i+1}$ 所以，如果选择这一项的话，那么系数要$\times -1$

注意系数的限制，每次搜索要根据系数的限制来确定搜索的范围

每一次搜索分为两种情况

- 选择这种糖果，根据推出来的式子，当前次数要加上 $m_i+1$ ，并且系数要变为负

- 不选择这种糖果，那么直接进入下一层，什么参数都不变

最后找完所有的之后，记得加上组合方案数。

因为考虑到模数不是一个质数，所以不能求逆元，题解区的dalao貌似给出了计算方法的证明，这里就不再多说了

### 代码实现

```
#include<iostream>
#include<cstdio>
#define int long long 
using namespace std;
const int mod=2004;
const int N=100;
int m[N];
int n,a,b;
int fac=1;
int ans;
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-') f=-1;s=getchar();} 
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
int C(int n_,int m)
{
	int MOD=fac*mod;
	int ret=1;
	for(int i=n_-m+1;i<=n_;i++)
		ret=(ret*i)%MOD;
	//mod不是质数，只能通过改变运算来达到模意义下的计算 
	return (ret/fac)%mod;
}
void dfs(int step,int type,int k,int all)//第几类，系数正负,当前次数,最高次限制 
{
	if(k>all) return;
	if(step==n+1)
	{
		ans=(ans+1ll*type*C(n+all-k,n)+mod)%mod;
		ans=(ans+mod)%mod;
		return;
	}	
	dfs(step+1,type,k,all);//不选这个
	dfs(step+1,-type,k+m[step]+1ll,all);//选这个，根据式子推出来可得 
}
int search(int len)
{
	ans=0;
	dfs(1ll,1ll,0ll,len);
	return (ans%mod+mod)%mod;	
} 
signed main()
{
	n=read();
	a=read();
	b=read();
	for(int i=1;i<=n;i++)
		m[i]=read();
	for(int i=1;i<=n;i++)
		fac*=i;
	int lenb=search(b);
	int lena=search(a-1); 
	printf("%lld\n",(lenb-lena+mod)%mod);
	return 0;	
}
```


---

## 作者：lhm_ (赞：8)

对于至少 $a$ 个，不超过 $b$ 个的限制，可以先求出限制不超过 $b$ 个的方案数，然后减去限制不超过 $a-1$ 个的方案数，即为答案。

对第 $i$ 个糖果罐列出其的生成函数，得：
$$
f_i(x)=\sum_{j=0}^{m_i} x^j = \frac{1-x^{m_i+1}}{1-x}
$$
将每个糖果罐对应的生成函数都卷积起来，得到考虑所有糖果罐的生成函数：
$$
f(x)=\prod_{i=1}^{n} f_i(x) = \frac{\prod_{i=1}^n 1-x^{m_i+1}}{(1-x)^n}  = \left(\prod_{i=1}^n 1-x^{m_i+1} \right)\sum_{j \geqslant 0} \binom{n+j-1}{j} x^j
$$
$f(x)$ 的 $0$ 次到 $i$ 次项的系数和即为限制不超过 $i$ 个的方案数，第一项可以直接 $dfs$，后一项可以用 $\binom{n}{m} = \binom{n}{m-1} + \binom{n-1}{m-1}$ 来化简。组合数计算时可以扩大模数，然后将计算得出的答案再除回去即可。

总复杂度为 $O(2^n n)$。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 15
#define p 2004
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,a,b;
int m[maxn];
int C(int n,int m)
{
    if(n<m) return 0;
    ll x=1,y=1,mod=p;
    for(int i=1;i<=m;++i) x*=i,mod*=i;
    for(int i=n-m+1;i<=n;++i) y=y*i%mod;
    return y/x%mod;
}
int dfs(int x,int sum,int type,int tot)
{
    if(x>n) return C(n+tot-sum,n)*type;
    return (dfs(x+1,sum,type,tot)+dfs(x+1,sum+m[x]+1,-type,tot)+p)%p;
}
int main()
{
    read(n),read(a),read(b);
    for(int i=1;i<=n;++i) read(m[i]);
    printf("%d",(dfs(1,0,1,b)-dfs(1,0,1,a-1)+p)%p);
    return 0;
}
```

---

## 作者：cyn2006 (赞：6)

在第 $id$ 罐糖里吃 $k$ 个糖果的生成函数为
$$
f_{id}(x)=\sum_{i=0}^{m_{id}} x^i=\frac{1-x^{m_{id}+1}}{1-x}
$$
然后**总共**吃 $k$ （$k$ 为 $1$ 到 $\max$）颗糖的生成函数为
$$
g(x)=\prod_{i=1}^n f_i(x) =(1-x)^{-n} \times \prod_{i=1}^n (1-x^{m_{id}+1})
$$
由牛顿二项式定理：
$$
g(x)=\left( \frac{1}{1-x} \right)^n \times \prod_{i=1}^n (1-x^{m_{id}+1})
$$

$$
=\left( \sum_{i=1}^n x^i \right)^n \times \prod_{i=1}^n (1-x^{m_{id}+1})
$$

$$
=\sum_{i=0}^{n} \binom{n+i-1}{i} x^i \times \prod_{i=1}^n (1-x^{m_{id}+1})
$$
现在我们观察题目可以发现 $n\leqslant 10$，意味着我们可以对后面的积式暴力展开（当然可以dfs，不过我模拟了多项式乘法）。

我们考虑暴力展开后积式中的 $[x^k]g$ 乘上 $(1-x)^{-n}$ 对答案的贡献（此时 $[x^k]g$ 为吃 $k$ 颗糖的答案）：
$$
[x^k]g(x)\sum_{i=a-k}^{b-k}\binom{n+i-1}{i}
$$

$$
=\left( \binom{n+b-k}{b-k} - \binom{n+a-k-1}{a-k-1} \right) [x^k]g(x)
$$
那么其系数之和即为答案。

然后这里有一个麻烦的事情：$\bmod$ 不是质数。

那么我们先看 $\large \binom{n+b-k}{b-k}$：
$$
\binom{n+b-k}{b-k}
$$

$$
=\frac{(n+b-k)!}{(b-k)!n!}
$$

$$
=\frac{(b-k+1)\times \ldots\times (b-k+n)}{n!}
$$
然后我们发现由于 $n!$ 特别地小，我们先对于原分式的分子 $\bmod (mod\times n!)$，那么最后再除以 $n!$ 即可，这样就解决了不可以用逆元的问题。

$Code:$

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define _rep(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ll long long
typedef std::pair<int,int> pii;
const int mod=2004;
const ll fac[]={1,1,2,6,24,120,720,5040,40320,362880,3628800};

struct poly{
	std::vector<pii> a;
	void clear(int ty){
		a.clear();
		if(ty) a.emplace_back(0,1);
	}
	inline poly operator*(const poly&p)const{
		poly ret; ret.clear(0);
		std::map<int,int> mp; mp.clear();
		for(pii i:a) for(pii j:p.a)
			mp[i.first+j.first]+=i.second*j.second;
		for(auto i:mp) ret.a.emplace_back(i.first,i.second);
		std::sort(ret.a.begin(),ret.a.end());
		return ret;
	}
} base,A;

int n,a,b;
ll pmod;
inline int C(int a,int b){
	if(a<b) return 0;
	ll ret=1;
	rep(i,a-b+1,a) ret=ret*i%pmod;
	return ret/fac[n]%mod;
}

int main(){
	std::cin>>n>>a>>b;
	base.clear(1);
	pmod=fac[n]*mod;
	rep(i,1,n){
		int m; std::cin>>m;
		A.clear(1);
		A.a.emplace_back(m+1,-1);
		base=base*A;
	}
	ll ret=0;
	for(pii i:base.a){
		int k=i.first;
		ret=((ret+i.second*(C(b-k+n,n)-C(a-k+n-1,n))%mod)+mod)%mod;
	}
	std::cout<<ret<<'\n';
	return 0;
}
```

---

## 作者：Genius_Star (赞：4)

**本题解使用 ExLucas 算法，喜提最慢解！**

### 题意：

共 $n$ 种糖，每种糖有 $m_i$ 个，求选出 $[l,r]$ 颗糖的方案数。

### 思路：

对于每种糖，其生成函数为（这里我们令指数表示选的个数，系数表示方案数）：

$$f(i) = \sum_{j=0}^{m_i} x^j$$

注意到：

$$\begin{cases} f(i) \times x = \sum_{j=1}^{m_i+1} x_j \\ f(i) - f(i) \times x = f(i) \times (1-x) =1 - x^{m_i+1}\end{cases}$$

得：

$$f(i) = \frac{1 - x^{m_i+1}}{1-x}$$

则最终答案式子为：

$$\frac{\prod\limits_{i=1}^n (1 - x^{m_i+1})}{(1-x)^n}$$

先考虑下面的式子：

$$\frac{1}{(1-x)^n} = (1-x)^{-n}$$

可以二项式定理：

$$\begin{aligned} (1-x)^{-n} &= \sum_{i=0}^{\inf} (-1)^i \times C_{-n}^i \times x^i \\ &= \sum_{i=0}^{\inf} (-1)^i \times \frac{(-n)!}{(-n-i)! \times i!} \times x^i \\ &= \sum_{i=0}^{\inf} (-1)^i \times \frac{(-n) \times (-n+1) \times \cdots \times (-n -i +1)}{i!} \times x^i \\ &=\sum_{i=0}^{\inf} (-1)^{2 \times i} \times \frac{n \times (n-1) \times \cdots \times (n+i-1)}{i!} \times x^i \\ &= \sum_{i=0}^{\inf} C_{n+i-1}^i \times x^i \end{aligned}$$

那么原式就转化为了：

$$\left( \prod\limits_{i=1}^n (1 - x^{m_i+1}) \right )\sum_{j=0}^{\inf} C_{n+j-1}^j \times x^j$$

那么前面的式子可以直接暴力展开计算，若得到 $a \times x^b$，考虑乘上后面的式子后在一个前缀 $[1,m]$ 的贡献，即：

$$b \sum_{j=0}^{m-b} C_{n+j-1}^j$$

对于后面这个式子，根据组合数递推公式化简一下可得：

$$\sum_{j=0}^{m-b} C_{n+j-1}^j = C_{n+m-b}^{m-b}$$

对于一个区间的差分一下即可。

现在主要是对于非质数取模求出组合数，明显可以扩展卢卡斯定理。

考虑对 $2004$ 质因数分解得 $2^2 \times 3 \times 167$，那么相当于求出下列式子的解：

$$\begin{cases} C_n^m \bmod 2^2 \\ C_n^m \bmod 3 \\ C_n^m \bmod 167\end{cases}$$

因为模数两两是互质的，最后可以用中国剩余定理合并，这里就不详细讲了，有需要的可以去 [here](https://www.luogu.com.cn/problem/P4720) 看看。

每次求组合数的常数很小，不大于为 $O(p)$。

时间复杂度约为 $O(2^N \times p)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll M=5,mod=2004; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,l,r,cnt,x,ans;
ll b[M],c[M],d[M];
map<ll,ll> H;
struct Node{
	vector<pair<ll,ll>> a;
	Node(){
		a.clear();
	}
	void init(){
		a.clear();
	}
	Node operator*(const Node&b)const{
		H.clear();
		Node ans;
		for(auto i:a)
		  for(auto j:b.a)
			H[i.first+j.first]+=i.second*j.second;
		for(auto i:H)
		  ans.a.emplace_back(i.first,i.second);
		sort(ans.a.begin(),ans.a.end());
		return ans;
	}
}B,A;
ll qpow(ll a,ll b,ll mod){
	ll ans=1;
	while(b){
		if(b&1ll)
		  ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1ll;
	}
	return ans;
}
void exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){
		x=1;
		y=0;
		return;
	}
	ll p;
	exgcd(b,a%b,x,y);
	p=x;
	x=y;
	y=p-(a/b)*y;
	return ;
}
ll Inv(ll a,ll mod){
	ll x=0,y=0;
	exgcd(a,mod,x,y);
	return(x%mod+mod)%mod;
}
ll solve(ll n,ll p,ll pk){
	if(!n)
	  return 1;
	ll ans=1;
	for(ll i=1;i<=pk;i++)
	  if(i%p)
	    ans=ans*i%pk;
	ans=qpow(ans,n/pk,pk);
	for(ll i=1;i<=n%pk;i++)
	  if(i%p)
	    ans=ans*i%pk;
	return ans*solve(n/p,p,pk)%pk;
}
ll C(ll n,ll m,ll p,ll pk){
	if(!n||!m||n==m)
	  return 1;
	if(n<m)
	  return 0;
	ll X=solve(n,p,pk),Y=solve(m,p,pk),Z=solve(n-m,p,pk),cnt=0,k=n-m;
	while(n)
	  n/=p,cnt+=n;
	while(m)
	  m/=p,cnt-=m;
	while(k)
	  k/=p,cnt-=k;
	return X*Inv(Y,pk)%pk*Inv(Z,pk)%pk*qpow(p,cnt,pk)%pk;
}
ll CRT(){
	ll M=1,ans=0;
	for(ll i=1;i<=cnt;i++)
	  M*=c[i];
	for(ll i=1;i<=cnt;i++)
	  d[i]=Inv(M/c[i],c[i]);
	for(ll i=1;i<=cnt;i++)
	  ans+=b[i]*(M/c[i])*d[i];
	for(int i=1;i<=cnt;i++)
	  b[i]=c[i]=d[i]=0;
	cnt=0;
	return (ans%M+M)%M;
}
ll ExLucas(ll n,ll m,ll p){
	if(n<m||m<0)
	  return 0;
	if(!n||!m||n==m)
	  return 1;
	ll t=sqrt(p);
	for(ll i=2;i<=t&&p>=1;i++){
		ll pk=1;
		while(p%i==0){
			p/=i;
			pk*=i;
		}
		if(pk>1){
			b[++cnt]=C(n,m,i,pk);
			c[cnt]=pk;
		}
	}
	if(p>1){
		b[++cnt]=C(n,m,p,p);
		c[cnt]=p;
	}
	return CRT();	
}
int main(){
	n=read(),l=read(),r=read();
	B.a.emplace_back(0,1);
	for(int i=1;i<=n;i++){
		x=read();
		A.init();
		A.a.emplace_back(0,1);
		A.a.emplace_back(x+1,-1);
		B=B*A;
	}
	for(auto v:B.a){
		x=v.first;
//		cerr<<n+r-x<<' '<<r-x<<' '<<n+l-x-1<<' '<<l-x-1<<' '<<(ExLucas(n+r-x,r-x,mod)-ExLucas(n+l-x-1,l-x-1,mod))<<'\n';
		ans=(ans+v.second*(ExLucas(n+r-x,r-x,mod)-ExLucas(n+l-x-1,l-x-1,mod))%mod+mod)%mod;
	}
	write(ans);
	return 0;
}
```

---

## 作者：Ame__ (赞：3)

### 题目描述
$John$得到了$n$罐糖果。不同的糖果罐，糖果的种类不同（即同一个糖果罐里的糖果种类是相同的，不同的糖果罐里的糖果的种类是不同的）。第$i$个糖果罐里有$m_{i}$个糖果。$John$ 决定吃掉一些糖果，他想吃掉至少$a$个糖果，但不超过$b$个。问题是 $John$无法确定吃多少个糖果和每种糖果各吃几个。有多少种方法可以做这件事呢？

### 解题思路

生成函数题，考虑对于第$i$堆吃$j$个糖果的方案并写成封闭模式为

$$F_i(x)=\sum_{j=0}^{m_i}x^j=\frac{1-x^{m_i+1}}{1-x}$$

那么对于吃$i$个的方案数为

$$
G(x)=\prod_{i=1}^n F_i(x)=(1-x)^{-n}\prod_{i=1}^n(1-x^{m_i+1})
$$

对于$(1-x)^{-n}$我们使用牛顿广义二项式展开可得$\begin{aligned}(1-x)^{-n}=\sum_{k=0}^{\infty}\dbinom{-n}{k}(-x)^k=\sum_{k=0}^{\infty}(-1)^k\dbinom{n+k-1}{k}(-x)^k=\sum_{k=0}^{\infty}\dbinom{n+k-1}{k}x^k\end{aligned}$

对于后面的柿子我们直接暴搜，怎么暴力怎么来就可以，对于前面的$\begin{aligned}\sum_{k=0}^{\infty}\dbinom{n+k-1}{k}x^k\end{aligned}$，我们考虑对答案的贡献，对于答案是$x^a$~$x^b$对应的系数，则设$\prod_{i=1}^n(1-x^{m_i+1})$枚举到了$x^k$，则为$\begin{aligned}\sum_{i=a-k}^{b-k}\dbinom{n+i-1}{i}\end{aligned}$，展开后对其用加法公式$\dbinom{n}{m}=\dbinom{n-1}{m}+\dbinom{n-1}{m-1}$进行化简可得为$\dbinom{n+b-k}{b-k}-\dbinom{n+a-k-1}{a-k-1}$，然后就可以做了，总体时间复杂度为$O(2^n)$

###细节注意

模数不是质数，组合数用定义进行计算

### $Code$

```cpp
#include<bits/stdc++.h>
    
#define LL long long
    
#define _ 0
    
using namespace std;
    
/*Grievous Lady*/
    
template <typename _n_> void mian(_n_ & _x_){
    _x_ = 0;int _m_ = 1;char buf_ = getchar();
    while(buf_ < '0' || buf_ > '9'){if(buf_ == '-')_m_ =- 1;buf_ = getchar();}
    do{_x_ = _x_ * 10 + buf_ - '0';buf_ = getchar();}while(buf_ >= '0' && buf_ <= '9');_x_ *= _m_;
}
    
const int kato = 20;

LL fac = 1 , ans , n , a , b , m[kato];

#define mod 2004

inline int c(int a , int b){
    if(a < b) return 0;
    LL res = 1 , tmp = fac * mod;
    for(int i = a - b + 1;i <= a;i ++){
        res = res * i % tmp;
    }
    return (res / fac) % mod;
}

void dfs(int x , int opt , int t){
    if(x == n + 1){
        ans = (ans + opt * (c(n + b - t , n) - c(n + a - t - 1 , n))) % mod;
        return;
    }
    dfs(x + 1 , opt , t) , dfs(x + 1 , - opt , t + m[x] + 1);
}

inline int Ame_(){
    mian(n) , mian(a) , mian(b);
    for(int i = 1;i <= n;i ++){
        mian(m[i]);
        fac = fac * i;
    }
    dfs(1 , 1 , 0);
    if(ans < 0) ans += mod;
    printf("%lld\n" , ans);
    return ~~(0^_^0);
}
    
int Ame__ = Ame_();
    
int main(){;}

/*
2 1 3
3
5
*/
```

-----$\mathcal{Ame\_\_}$

---

## 作者：ZBHRuaRua (赞：3)

**生成函数入门题**

每种糖果$m_{i}$个，直接构造每种糖果的生成函数相乘

$\prod_{i=1}^{n}\frac{1-x^{m_{i}+1}}{1-x}$

对于答案其实就是$F(a)-F(b-1)$

对于分母对$i$次项的贡献自然就是$C_{i+n-1}^{n-1}$

而分子我们不太好直接求，发现只有$2^{n}$项，于是直接爆搜即可。

分子求出来的第$i$次项的系数我们设为$p_{i}$

而在求$F(m)$时，它的答案应该是$\sum_{k=0}^{m}p_{k}\sum_{i=0}^{m-k}(C_{i+n-1}^{n-1})$

发现后面这个东西$\sum_{i=0}^{m-k}(C_{i+n-1}^{n-1})$是杨辉三角的同一列

稍微画一下即可发现杨辉三角的性质，就可以把这个东西转化为$C_{n+m-k}^{n}$了

于是答案就是$\sum_{k=0}^{m}p_{k}C_{n+m-k}^{n}$

那么在爆搜分子的时候每搜好一波就统计答案即可

还有个细节是这题要对$2004$取模，不是质数，因此没法直接搞逆元

但是我们在求组合数时要求的是$C_{n+m-k}^{n}$,也就是$\frac{(n+m-k)!}{n!(m-k)!}$

把$(m-k)!$约掉，我们就只用除以$n!$这个东西了，$n$非常小，$mod$也非常小,那我们直接对$n!*mod$取模就好了，最后返回答案时再除以一个$n!$即可。

代码：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<algorithm>
#define ll long long
using namespace std;
const ll mod=2004;
inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+(c-'0');
		c=getchar();
	}
	return x*f;
}
ll n,m1,m2,njc=1;
ll num[1000050];
ll ans;
inline ll C(ll a,ll b)
{
	if(b>a) return 0;
	ll res=1;ll modd=mod*njc;
	for(int i=a-b+1;i<=a;i++) res=res*i%modd;
	res/=njc;
	return res;
}
inline void dfs(int pos,int val,int xs,int d)
{
	if(pos>n)
	{
		ans+=val*C(n+d-xs,n)%mod;
		ans=(ans+mod)%mod;
		return;
	}
	dfs(pos+1,val,xs,d);
	dfs(pos+1,-val,xs+num[pos]+1,d);
}
inline ll solve(ll x)
{
	ans=0;
	dfs(1,1,0,x);
	return ans;
}
int main()
{
	n=read();m1=read();m2=read();
	for(int i=1;i<=n;i++) num[i]=read();
	for(int i=1;i<=n;i++) njc*=i;
	printf("%lld",(solve(m2)-solve(m1-1)+mod)%mod);
	return 0;
}
```


---

## 作者：genshy (赞：2)



### 前置芝士

这里定义 $\dbinom{n}{k} = {n(n-1)(n-2)....(n-k+1)\over{k!}}$。

牛顿二项式定理： $(x+y)^n = \displaystyle\sum_{k=0}^{\infty}\dbinom{n}{k}x^ky^{n-k}$ 

当 $n$ 为正数的时候， $(1+x)^n = \displaystyle\sum_{k=0}^{\infty} \dbinom{n}{k}x^k = \displaystyle\sum_{k=0}^{\infty} C_{n}^{k} x^{k}$ ,(也就是我们熟悉的二项式定理)

对于正整数 $n$ ,我们取 $a = -n$

 $\dbinom{a}{k} = \dbinom{-n}{k} = {{-n(-n-1)(-n-2)...(-n-k+1)}\over{k!}} = (-1)^{k}{n(n+1)(n+2)...(n+k-1)\over k!}=(-1)^{k} \dbinom{n+k-1}{k}$

$\because (1+x)^{a} = \displaystyle\sum_{k=0}^{\infty} \dbinom{a}{k}x^k = \sum_{k=0}^{\infty} (-1)^{k}\dbinom {n+k-1}{k} x^k$ 

$\therefore (1+x)^{-n} = \displaystyle\sum_{k=0}^{\infty} (-1)^{k}\dbinom{n+k-1}{k} x^k$ 

把 $x$ 换成 $-x$ 可得：

$(1-x)^{-n} = \displaystyle\sum_{k=0}^{\infty} \dbinom{n+k-1}{k} x^k = \displaystyle\sum_{k=0}^{\infty} C_{n+k-1}^{k}x^k$

### 题目描述

[luogu](https://www.luogu.com.cn/problem/P6078)

John 得到了 $n$  罐糖果。不同的糖果罐，糖果的种类不同（即同一个糖果罐里的糖果种类是相同的，不同的糖果罐里的糖果的种类是不同的）。第 $i$ 个糖果罐里有 $m_{i}$  个糖果。John 决定吃掉一些糖果，他想吃掉至少 $a$ 个糖果，但不超过 $b$ 个。问题是 John 无法确定吃多少个糖果和每种糖果各吃几个。有多少种方法可以做这件事呢？

**solution**

生成函数入门题。

首先我们把每个糖果的生成函数写出来即： $f(x) = x^0+x^1+x^2 ..... + x^m$.

$\because xf(x) = x^1+x^2+....x^{m+1}$

$\therefore f(x)-xf(x) = 1-x^{m+1}$

$\therefore f(x) = {1-x^{m+1}\over{1-x}}$

把每个糖果的生成函数乘起来： $\displaystyle{\prod_{i=0}^{n} (1-x^{m_i+1})}\over(1-x)^n$

分子展开之后最多有 $2^n$ ，暴力展开即可。

分母由牛顿二项式定理可得： $(1-x)^{-n} = \displaystyle\sum_{k=0}^{\infty}C_{n+k-1}^{k}x^k$

考虑假如说当前分子枚举到 $x^{k}$ ,那么分母对当前答案的贡献即为 $\displaystyle\sum_{i=a-k}^{b-k} C_{n+i-1}^{i}$ .

 由 杨辉三角可得,  $\displaystyle\sum_{i=a-k}^{b-k} C_{n+i-1}^{i} = C_{n+b-k}^{b-k} - C_{n+a-k-1}^{a-k-1}$

可以模数不是质数，没有逆元怎么办？

 $\because C_{n+b-k}^{b-k} = {(n+b-k)!\over{n!(b-k)!}}$ 

$\therefore C_{n+b-k}^{b-k} = {(n+b-k)(n+b-k-1)....(b-k+1)\over n!}$ 

因为 $n! $ 很小，所以可以在算分子的时候把模数变为 $n!\times p$ ,最后在除以 $n!$ 即可。

注意计算 $n!$ 的时候，一定不要模 $p$ (好像只有我这个沙比犯了这个错误)。

**Code**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int p = 2004;
int n,a,b,inv,ans,m[20];
inline int read()
{
    int s = 0,w = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){s = s * 10 + ch - '0'; ch = getchar();}
    return s * w;
}
int C(int tot)
{
    if(tot < 0) return 0;
    int res = 1, mod = inv * p;
    for(int i = tot+1; i <= n+tot; i++) res = res * i % mod;
    return (res / inv) % p;
}
void dfs(int x,int mi,int tmp)
{
    if(x == n+1)
    {
        ans = (ans + tmp * ((C(b-mi) - C(a-mi-1)) % p) % p) % p;
        return;
    }
    dfs(x+1,mi,tmp);
    dfs(x+1,mi+m[x]+1,-tmp);
}
signed main()
{
    n = read(); a = read(); b =  read(); inv = 1;
    for(int i = 1; i <= n; i++) m[i] = read(), inv = inv * i;
    dfs(1,0,1);
    printf("%lld\n",(ans+p)%p);
    return 0;
}
```



---

## 作者：FutaRimeWoawaSete (赞：1)

贺完了来写题解了。                   

继承【】之先志。               

谁让自己数学这么菜呢。

显然对于第 $i$ 罐糖果有以下几种取法：取其中 $0$ 颗糖，取其中 $1$ 颗糖……取其中 $m_i$ 颗糖，写成生成函数的形式就是 $f(i) = x ^ 0 + x ^ 1 + ...... + x ^ {m_i}$ 。                   

那么对于 $n$ 罐糖的生成函数我们直接卷起来后，任意一项 $ax ^ k$ 就表示选择 $k$ 颗糖可以有 $a$ 种方案。               

很显然的答案就是指数在 $[a,b]$ 之间的系数之和，考虑如何快速计算这玩意儿。              

比较显然的我们可以暴力把这 $n$ 个函数卷起来，那么时间复杂度是 $O(\prod_{i = 1} ^ n m_i)$ ，过于暴力。             

用多项式优化一下，跑十次即可，时间复杂度是 $O(10 m \log m)$ 还是会超时。                  

我们考虑利用生成函数对这个式子再化简：                 

$f(i) = x ^ 0 + x ^ 1 + ...... + x ^ {m_i} = \frac{1 - x ^ {m_i + 1}}{1 - x}$           

形式化一下答案：           

$G(x) = \prod_{i = 1} ^ n f(i) = \frac{\prod_{i = 1} ^ n (1 - x ^ {m_i + 1})}{(1 - x) ^ n}$            

对于上面的分子式子我们可以暴力 $O(2 ^ n)$ 展开，就先不管他了，考虑下面的分母。              

$\frac{1}{(1 - x) ^ n} = 1 + C_n^{n - 1}x + C_{n + 1} ^ {n - 1} x ^ 2 + .... $          

考虑先把答案做成差分的形式，即求 $Ans(n)$ 表示糖果数在 $n$ 以内的所有方案那么答案就是 $Ans(b) - Ans(a - 1)$ 。

我们令分子卷起来的函数为 $p$ ，则如果任意的 $p_k$ 要为一个 $Ans(m)$ 贡献的话就是：           

$p_k \times \sum_{i = 0} ^ {m - k} C_{n - 1 + i} ^ {n - 1}$      

就相当于指数乘起来后不能超过 $m$ 嘛。             

考虑快速计算后面的东西，我们不妨先把 $C_{n - 1}^{n - 1}$ 变成 $C_n^n$ ，然后你就会发现 $C_n^n + C_n^{n - 1} = C_{n + 1} ^ {n}$ 再依次和后面的 $C_{n + 1} ^ {n - 1}$ 等结合最后就可以写成 $C_{n + m - k} ^ {n}$ 的形式了。              

然而你还要考虑快速计算这个东西，考虑把 $C_{n + m - k} ^ n$ 写成 $\frac{(n + m - k) \times (n + m - k - 1) ......}{n!}$ 的形式，那么分子分母都只有 $n$ 项就可以考虑暴力算了。             

这个证明和计算方法可以看一下[这一篇](https://www.luogu.com.cn/blog/RUI-R/solution-p6078)博客。通过上述我们就可以在计算分子时用 $2004 \times n!$ 取模最后对答案除上 $n!$ 再对 $2004$ 取模。                   

时间复杂度 $O(2 ^ n \times n)$ 。

---

## 作者：Strelitzia (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6078)

前置知识：生成函数

拿第 i 种糖，生成函数是 $\sum_{j=0}^{m_i}x^j$，然后等比数列求一下和就是 $\frac{1-x^{m_i + 1}}{1-x}$。

这都是一些基本操作，然后，我们把它们乘起来，就是

$$
\prod_{i=1}^{n}\frac{1-x^{m_i + 1}}{1-x}
$$

可以提出来个 $({1-x})^{-n}$

原式变成了

$$
(1-x)^{-n}\prod_{i=1}^{n}1-x^{m_i + 1}
$$

因为 n 很小，所以 $\prod_{i=1}^{n}1-x^{m_i + 1}$ 可以暴力拆。

对于 $(1-x)^{-n}$，我们可以用牛顿二项式定理
$$
(1-x)^{-n} = \sum_{i \geq 0}^{} \dbinom{n + i - 1}{i}x^i
$$

我们枚举 $\prod_{i=1}^{n}1-x^{m_i + 1}$ 这个函数的指数，假设枚举出的指数为 $j$，系数为 $c_j$。

如果 $a \leq i + j \leq b$，答案就是$\dbinom{n+i-1}{i}\times c_j$

转换一下就是

$$
c_j\times \sum_{i=a-k}^{b-k}\dbinom {n + i - 1}{i}
$$

而 $\sum_{i=a-k}^{b-k}\dbinom {n + i - 1}{i}$，可以用 $
\binom{n - 1}{m} + \binom{n - 1}{m - 1} = \binom{n}{m}
$ 化简。

就是
$$
c_j\times 
\dbinom{n +b-k}{b - k}-
c_j\times \dbinom{n +a-k -1}{a - k - 1}
$$

这道题就结束了,代码如下。

```cpp
#include <map>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1500;
const int MOD = 2004;

int n,a,b;
int m[N];

map<int,int> g,f,h;

int C(int n,int m) {
	if (n < m)
		return 0;
	long long t = 1,p1 = 1;
	for (int i = 1 ; i <= m ; ++ i)
		p1 = p1 * i;
	long long mod = 1ll * MOD * p1;
	for (int i = n - m + 1 ; i <= n ; ++ i)
		t = t * i % mod;
	return (t / p1) % MOD;
}

int main () {
	scanf("%d %d %d",&n,&a,&b);
	for (int i = 1 ; i <= n ; ++ i)
		scanf("%d",&m[i]);
	g[0] = 1;
	g[m[1] + 1] = -1;
	for (int i = 2 ; i <= n ; ++ i) {
		f.clear();
		map<int,int>::iterator it1,it2;
		for (it1 = g.begin() ; it1 != g.end() ; ++ it1) {
			f[it1->first] = it1->second;
		}
		g.clear();
		h.clear();
		h[0] = 1;h[m[i] + 1] = -1;
		for (it1 = f.begin() ; it1 != f.end() ; ++ it1) {
			for (it2 = h.begin() ; it2 != h.end() ; ++ it2) {
				int ky = (it1->first) + (it2->first);
				g[ky] = (g[ky] + (1ll * (it1->second) * (it2->second)) % MOD + MOD) % MOD;
			}
		}
	}
	int ans = 0;
	map<int,int>:: iterator it;
	for (it = g.begin() ; it != g.end() ; ++ it) {
		ans = (1ll * it->second * (C(n + b - (it->first),n) - C(n + a - (it->first) - 1,n)) % MOD + ans + MOD) % MOD;
	}
	printf("%d\n",(ans % MOD + MOD) % MOD);
	return 0;
}
```

---

## 作者：huangzirui (赞：0)

有 $n$ 罐糖果，分别有 $a_i$ 个，互相不可区分，求吃掉个数在 $[l,r]$ 之间的方案数。

---

生成函数的入门题。

做这道题需要一定的组合基础，以及理解生成函数的概念：你可以把它当成一个序列，其中的 $x^n$ 项就是序列的第 $n$ 项，而 $x$ 是没有意义的。

那么，假设第 $i$ 堆糖果有 $a_i$ 个，于是吃掉 $s$ 个的方案数就是 $[s \le a_i]$ （因为每堆糖果无法区分）。我们用 $x^s$ 来标记它，那么把所有这些加到一起就可以得到：

$$F_i(x)=\sum_{0 \leq s \leq a_i}x^s$$

根据公式得到

$$F_i(x)=\sum_{n=0}^{a_i}x^n=\dfrac{1-x^{a_i+1}}{1-x}$$

这就是某堆糖果的生成函数，其中 $x^d$ 项表示吃 $d$ 个的方案数。

那么把所有糖果堆代表的生成函数乘到一起，就得到：

$$\prod_{i \leq n}F_i(x)=\frac{\prod_{i\leq n}(1-x^{a_i+1})}{(1-x)^n}$$

此时乘出来的 $x^d$ 项表示在所有糖果堆中吃 $d$ 个的方案数。

考虑到上面的式子可以 $O(2^n)$ 预处理出来，于是只要考虑下面的式子。

首先， $\dfrac{1}{(1-x)^n}=(1-x)^{-n}$

根据牛顿二项式定理： $(1-x)^{-n}=\sum\limits_{i\ge 0}\tbinom{-n}{i}(-x)^i$

分解组合数：

$$\sum\limits_{i\ge 0}\tbinom{-n}{i}(-x)^i=\sum_{i \ge 0}\dfrac{(-n) \times \dots \times (-n-i+1)}{i!}(-x)^i$$

因为上面的部分可以提取出 $i$ 个 $-1$ ，右边的也可以提出 $i$ 个 $-1$，于是就有：

$$=\sum_{i \ge 0}\dfrac{n \times \dots \times (n+i-1)}{i!}x^i=\sum\limits_{i\ge 0}\tbinom{n+i-1}{i}x^i$$

于是原式的分母就等于：

$$\sum\limits_{i\ge 0}\tbinom{n+i-1}{i}x^i$$

考虑我们要求出 $x$ 的 $l\dots r$ 次方的系数，考虑 $c \cdot x^d$ 除以分母的贡献：

$$c\cdot x^d \cdot \sum\limits_{l \le i+d\le r}\tbinom{n+i-1}{i}x^i$$

就可以得到贡献为：

$$c \times \sum_{l-d \le i \le r-d}\tbinom{n+i-1}{i}=c \times(\tbinom{r-d+n}{r-d}-\tbinom{l-d+n-1}{l-d-1})$$

[ 不会的可以翻翻您的组合数学书（雾  ]

于是对于每个 $x^d\ (l\leq d\leq r)$ 求出对于的系数加起来即可。

复杂度 $O(2^n+r)$ 可以通过此题。

---

