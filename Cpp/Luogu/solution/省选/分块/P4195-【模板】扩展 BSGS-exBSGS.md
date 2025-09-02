# 【模板】扩展 BSGS/exBSGS

## 题目背景

题目来源：SPOJ3105 Mod

## 题目描述

给定 $a,p,b$，求满足 $a^x≡b \pmod p$ 的最小自然数 $x$ 。


## 说明/提示

对于 $100\%$ 的数据，$1\le a,p,b≤10^9$ 或 $a=p=b=0$。

2021/5/14 加强 by [SSerxhs](https://www.luogu.com.cn/user/29826)。  
2021/7/1 新添加[一组 Hack 数据](https://www.luogu.com.cn/discuss/391666)。

## 样例 #1

### 输入

```
5 58 33
2 4 3
0 0 0```

### 输出

```
9
No Solution```

# 题解

## 作者：白鲟 (赞：40)

## 前言
clockwhite 写了一篇此题题解。

~~我也要写！~~

## 问题

求出使 $a^x\equiv b\pmod p$ 成立的最小 $x$，或判断方程无解。

## 解法与证明
同一般 BSGS 做法进行根号平衡，设 $t=\lceil \sqrt{2\varphi(p)} \rceil,x=pt-q(0\le q<t)$ ，考虑对原式进行变形：

$$
a^{pt-q}\equiv b\pmod {p}
$$
$$
a^{pt} \equiv ba^q\pmod p
$$

注意到两步间并非等价变形，后者是前者的必要条件。预先将 $a^{pt}(0\le p\le t)$ 的值存入散列表，之后枚举 $a^q$ 并在散列表中查询 $ba^q$ 的值是否存在。若存在，则所对应的 $pt-q$ 即为 $x$ 的一个可能值，代入原式可知是否确实能成为 $x$。

事情至此尚未解决，这是由于$a^{pt}$ 的值可能出现重复。对于重复的值，仅前两个出现的位置可能成为答案。查询时两值均进行检验即可。

时间复杂度为 $\operatorname{O}(\sqrt{\varphi(p)})$。

然后是正确性证明。

首先证明答案上界。前文设 $t=\lceil \sqrt{2\varphi(p)} \rceil$，意味着 $2\varphi(p)$ 是答案的上界。事实上确实如此。根据扩展欧拉定理 $a^{x}\equiv a^{x\bmod {\varphi(p)}+\varphi(p)}$，若 $x>2\varphi(p)$，必然有 $x\bmod {\varphi(p)}+\varphi(p)$ 是更优的答案。上界得证。

之后证明仅保留前两个相等的值的正确性。由扩展欧拉定理，形象化地说，$a^x$ 的值形成了一个 $\rho$ 形，即在经过长度不超过 $\varphi(p)$ 的非循环数后进入长度不超过 $\varphi(p)$ 的循环节。若一个值出现多次，则它的每一次出现均在循环节上。由于 $q<t$，某一个值第二次出现时对应的 $a^{p't-q}$ 必然大于第一次出现时对应的 $a^{pt}$，这意味着只有第一次出现某一个值时 $a^{pt-q}$ 才可能在非循环数中。由于在循环节中得到的答案不会产生差异，取前两次必定能考虑到答案的所有情况。

## 代码
update: 再加快读即可通过，懒得加了。希望以后不会再有这么无聊的 hack。

加强数据后已通过。

先取模再跑即可。
```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
const long long maxn=1e5,mod=1145141,inf=0xffffffffffffffll;
long long base,rest,prime,baby[maxn+1],giant[maxn+1],key[mod],comment[2][mod],stk[mod<<1|1];
long long Hash(long long value)
{
	long long now=value*value%mod;
	while(key[now]&&key[now]!=value)
		now=(now+1)%mod;
	if(!key[now])
		stk[++stk[0]]=now;
	key[now]=value;
	return now;
}
long long phi(long long x)
{
	long long res=x;
	for(long long i=2;i*i<=x;++i)
		if(x%i==0)
		{
			res=res/i*(i-1);
			while(x%i==0)
				x/=i;
		}
	if(x>1)
		res=res/x*(x-1);
	return res;
}
long long exBSGS(void)
{
	long long res=inf,block=ceil(sqrt(2*phi(prime)));
	baby[0]=1;
	for(long long i=1;i<=block;++i)
		baby[i]=baby[i-1]*base%prime;
	comment[0][Hash(1)]=0;
	giant[0]=1;
	for(long long i=1;i<=block;++i)
	{
		giant[i]=giant[i-1]*baby[block]%prime;
		long long now=Hash(giant[i]);
		if(!comment[0][now])
			comment[0][now]=i;
		else if(!comment[1][now])
			comment[1][now]=i;
	}
	for(long long i=0;i<=block;++i)
	{
		long long now=Hash(rest*baby[i]%prime),t0=comment[0][now],t1=comment[1][now];
		if(t0&&giant[t0-1]*baby[block-i]%prime==rest)
			res=min(res,t0*block-i);
		else if(t1&&giant[t1-1]*baby[block-i]%prime==rest)
			res=min(res,t1*block-i);
	}
	return res;
}
signed main()
{
	while(scanf("%lld%lld%lld",&base,&prime,&rest)!=EOF)
	{
		while(stk[0])
		{
			key[stk[stk[0]]]=comment[0][stk[stk[0]]]=comment[1][stk[stk[0]]]=0;
			--stk[0];
		}
		if(!prime&&!base&&!rest)
			break;
		base%=prime;
		rest%=prime;
		long long res=exBSGS();
		if(res==inf)
			puts("No Solution");
		else printf("%lld\n",res);
	}
	return 0;
}
```



---

## 作者：suxxsfe (赞：32)

[推荐到我的博客查看，并不会有更好的阅读体验（雾](https://www.cnblogs.com/suxxsfe/p/12666760.html)

# BSGS  

BSGS，全称叫 BabyStepGiantStep，也就是大步小步  
其实还是比较暴力的  

它可以$O(\sqrt p)$的复杂度内解出：  

$$a^x\equiv n\pmod p,\gcd(a,p)=1$$  

中$x$的值  
如果$\gcd(a,p)\neq 1$就要用到 exBSGS 了  

我们考虑令$x=im-k,0\le k<m$  
那么原式变为  

$$a^{im-k}\equiv n\pmod p$$  
$$a^{im}\equiv na^k\pmod p$$  

那么，我肯可以枚举$k\in[0,m)$，计算出$na^k\bmod p$的值，然后把对应的$k$存下来  
可以用`map`或 hash，用`map`会多一个$\log$  

然后，再枚举$i\in[0,\lceil\frac{p}{m}\rceil]$，计算出$a^{im}\bmod p$  
然后看一看之前有没有一个$k$，使得$na^k\equiv a^{im}\pmod p$，且$im>=k$  
如果有，那么答案肯定就是$im-k$  
如果一直没找到，那么就无解  

复杂度是$O(\max(m,\frac{p}{m} ))$，显然，让$m=\lceil \sqrt p \rceil$时最优，即为$O(\sqrt p)$  

但是，我们考虑的只是$x\in[1,p]$的情况，那为什么要找的这个$x$一定满足这样的性质呢？  
首先$\gcd(a,p)=1$，满足欧拉定理的条件，也就是会有$a^{\varphi(p)}\equiv 1\pmod p\Rightarrow a^{q\varphi(p)}\equiv 1\pmod p,q\in\mathbb{N^*}$  
那么，$k\bmod \varphi(p)=k-q\varphi(p)<\varphi(p)<p$  
则$a^{k\bmod \varphi(p)}=\dfrac{a^k}{a^{q\varphi(p)}}$  
又由于那个分母在$\bmod p$中同余于$1$  
所以$a^{k\bmod \varphi(p)}\equiv a^k\pmod p$  

则可以得知，要求的最小的$x$，如果有解，一定满足$x<\varphi(p)<p$  

模板题：[P3846 [TJOI2007] 可爱的质数](https://www.luogu.com.cn/problem/P3846)  
这题保证了$a,n<p$，所以不需要一些奇奇怪怪的特判  

```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<map>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
std::map<int,int>map;
inline int power(int a,int b,int p){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%p;
		b>>=1;a=1ll*a*a%p;
	}
	return ret;
}
inline int BSGS(int a,int n,int p){
	reg int m=std::ceil(std::sqrt(p));
	for(reg int i=0,s=n;i<m;i++,s=1ll*s*a%p) map[s]=i;
	for(reg int i=0,tmp=power(a,m,p),s=1;i<=m;i++,s=1ll*s*tmp%p)
		if(map.find(s)!=map.end())
			if(i*m>=map[s]) return i*m-map[s];
	return -1;
}
int main(){
	int p=read(),a=read(),n=read();
	LL ans=BSGS(a,n,p);
	ans==-1?std::puts("no solution"):std::printf("%lld",ans);
	return 0;
}
```  

# exBSGS  

用于处理上面哪个问题$\gcd(a,p)\neq 1$的情况  
~~有些细节稍显恶心（其实还好~~  

首先，原来那个同余方程可以等价的写成：  

$$a^x+kp=n$$  

设$\gcd(a,p)=d$  
由于斐蜀定理，这个式子有解的充要条件是$d\mid n$，否则直接返回无解  
那么上面的式子就是：  

$$a^{x-1}\cdot \frac{a}{d}+k\cdot\frac{p}{d}=\frac{n}{d}$$  

此时，$a^{x-1}\rightarrow a^x,\frac{p}{d}\rightarrow p,\frac{n}{d}\rightarrow n$  
那么一直递归，直到$\gcd(a,p)=1$  

所以此时设一共递归了$cnt$次，这所有次递归的$d$的乘积是$d$~~（用一个字母说起来省事~~  
原式就是  

$$a^{x-cnt}\cdot \frac{a^{cnt}}{d}\equiv \frac{n}{d}\pmod {\frac{p}{d}}$$  

那么我们就用$a'=a,n'=\frac{n}{d},p'=\frac{p}{d}$来跑一次 BSGS 就行了  

当然，答案还要再加上$cnt$   
而且，还有一个$\dfrac{a^{cnt}}{d}$的系数要乘上，具体对应代码中的变量`ad`，要传参到 BSGS 的函数里  

模板题：[SP3105 MOD - Power Modulo Inverted](https://www.luogu.com.cn/problem/SP3105)，[P4195 【模板】exBSGS](https://www.luogu.com.cn/problem/P4195)  
还是双倍经验，但是这个不保证$a,n<p$，所以要先模一下，然后判断一下是不是等于$0$，具体看代码  
而且这个还卡常，必须要用`unordered_map`，它的内部实现是哈希表，而`map`是红黑树，前者构建好像稍慢，但是查询快，适合这个题  
~~话说我写这题的时候听说卡常，然后T了以后猛卡常数，结果后来发现是写法错了，于是就对着错误的程序卡了一晚上常直至自闭~~  
不过是 c++11 的东西，noip可能不能用，编译时要加上`-std=c++11`  

当然写 hash 也可以，但我不太会/kk  

```cpp  
#include<cstdio>
#include<map>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
std::unordered_map<int,int>map;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
inline int BSGS(int a,int n,int p,int ad){
	map.clear();
	reg int m=std::ceil(std::sqrt(p));
	reg int s=1;
	for(reg int i=0;i<m;i++,s=1ll*s*a%p) map[1ll*s*n%p]=i;
	for(reg int i=0,tmp=s,s=ad;i<=m;i++,s=1ll*s*tmp%p)
		if(map.find(s)!=map.end())
			if(1ll*i*m-map[s]>=0) return 1ll*i*m-map[s];
	return -1;
}
inline int exBSGS(int a,int n,int p){
	a%=p;n%=p;
	if(n==1||p==1) return 0;
	reg int cnt=0;
	reg int d,ad=1;
	while((d=gcd(a,p))^1){
		if(n%d) return -1;
		cnt++;n/=d;p/=d;
		ad=(1ll*ad*a/d)%p;
		if(ad==n) return cnt;
	}
//		std::printf("a: %d n: %d p: %d ad:%d\n",a,n,p,ad);
	LL ans=BSGS(a,n,p,ad);
	if(ans==-1) return -1;
	return ans+cnt;
} 
signed main(){
	int a=read(),p=read(),n=read();
	while(a||p||n){
		int ans=exBSGS(a,n,p);
		if(~ans) std::printf("%d\n",ans);
		else std::puts("No Solution");
		a=read();p=read();n=read();
	}
	return 0;
}
```

---

## 作者：mydcwfy (赞：20)

**Update on 2021-11-01：** 更新了代码，可能会提升阅读效果吧。

**Update on 2022-07-04：** 被 @RainFestival Hack 了，更新了代码，已经可以通过。

## 0. 前置知识 & 废话

逆元。

[我的逆元 Blog](https://www.luogu.com.cn/blog/mydcwfy-342891/inverse-element)

## 1. 普通版 BSGS

要求 $\gcd(a,p)=1$。

其实就是一个分块的思想。

设 $t=\lceil\sqrt p\rceil$，我们可以将每一个答案 $x=i\times t-m$，其中 $i,m\leq t$。

$a^{i\cdot t-m}=b\pmod p\Leftrightarrow a^{i\cdot t}=b\times a^{m}\pmod p$。

我们枚举每一个 $i$，怎么找到右边的呢？

其实，我们可以先将 $b\times a^m$ 全部用 Hash 存下来。

这样就可以直接查找了。

## 2. 扩展版 BSGS

想办法解决问题，我们应该实现 $\gcd(a,p)=1$。

首先，同余具有一条性质：
$$
a=b\pmod c (\gcd(a,c)=1)\Leftrightarrow a\times d=b\times d\pmod {c\times d}
$$
可以感性的理解一下 （~~主要是不会证~~）。

那么，我们就可以执行消除因子。

每次在两边除以 $d=\gcd(a,p)$。
$$
a^x=b\pmod p\Rightarrow \dfrac{a}{d}\times a^{x-1}=\dfrac{b}{d}\pmod {\dfrac{p}{d}}
$$
重复执行该语段，直到 $\gcd(a,p)=1$ 为止。

将所有的 $\dfrac{a}{d}$ 都乘起来，记为 $tot$。

假设执行了 $cnt$ 次，则原问题转化为 $tot\times a^{x-cnt}=b\pmod p\Leftrightarrow a^{x-cnt}=b\times tot^{-1}\pmod p$

注意，这里有一些细节：

1. 如果 $b$ 不被 $d$ 整除，则直接返回无解。
2. 答案可能小于 $cnt$，我们必须枚举 $[0,cnt-1]$ 的解，看有没有。

于是就转化为了普通的 BSGS 了。

```cpp
using LL = long long;

int Mod;

int Gcd(int a, int b) { return b ? Gcd(b, a % b) : a; }

void ExGcd(int a, int b, LL &x, LL &y)
{
	if (!b) return x = 1, y = 0, void();
	ExGcd(b, a % b, y, x), y -= a / b * x;
}

inline int& adj(int &x) { return x += x >> 31 & Mod; }

int qpow(int a, int k)
{
	int res = 1;
	for (; k; k >>= 1, a = (LL) a * a % Mod)
		(k & 1) && (res = (LL) res * a % Mod);
	return res;
}

int ExBSGS(int a, int b)
{
	a %= Mod, b %= Mod;
	if (b == 1 || Mod == 1) return 0;
	if (!a) return b ? -1 : 1;
	int t, cur = 1, g = 0;
	while ((t = Gcd(a, Mod)) != 1)
	{
		if (b % t) return -1;
		++ g, b /= t, Mod /= t, cur = (LL) cur * (a / t) % Mod;
		if (cur == b) return g;
	}
	std::map<int, int> mp;
	int B = std::sqrt(Mod) + 1;
	LL x, y;
	ExGcd(cur, Mod, x, y), x = (x % Mod + Mod) % Mod;
	cur = (LL) x * b % Mod;
	mp[cur] = 0;
	for (int i = 1; i <= B; ++ i) mp[cur = (LL) cur * a % Mod] = i;
	int pw = qpow(a, B);
	cur = 1;
	for (int i = 1; i <= B; ++ i)
		if (mp.count(cur = (LL) cur * pw % Mod))
			return i * B - mp[cur] + g;
	return -1;
}

int main()
{
    int a, b;
    while (read(a, Mod, b), a || b || Mod)
    {
        int res = ExBSGS(a, b);
        if (~res) write(res, '\n');
        else write("No Solution\n");
    }
    return 0;
}
```

---

## 作者：MY（一名蒟蒻） (赞：15)

[我的 BSGS 算法学习笔记](https://www.luogu.com.cn/blog/nizhuan/bsgs-xue-xi-bi-ji)

[P4195 【模板】扩展 BSGS/exBSGS](https://www.luogu.com.cn/problem/P4195)

[SP3105 MOD - Power Modulo Inverted](https://www.luogu.com.cn/problem/SP3105)

好耶，紫色的双倍经验！

普通的 BSGS 只能解决 $a$ 与 $p$ 互质的情况，而 exBSGS 不需要这个条件。

不互质咋办？变成互质！

[OI Wiki 上的讲解](https://oi-wiki.org/math/bsgs/#_8)

方程两边同时除以 $\gcd(a,p)$ ，注意模数 $p$ 也要除，若 $\gcd(a,p) \nmid b$ 则无解。

若仍不互质则重复进行上述过程，直至 $p$ 与 $a$ 互质。

记 $d$ 为每次的 $\gcd$ 的乘积，一共除了 $cnt$ 次，则方程转化为：

$$\frac{a^{cnt}}{d}\times a^{x-cnt} \equiv \frac{b}{d}\pmod {\frac{p}{d}}$$

因为 $a\perp \frac{p}{d}$ ，所以 $\frac{a^{cnt}}{d}$ 在 $\bmod \frac{p}{d}$ 意义下有逆元，移项求解 $x-cnt$ 然后加上 $cnt$ 即可。

当然有时候 $x=cnt$ ，这种情况直接返回 $cnt$ 就好了。

## Code

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

int exgcd(int a,int b,int &x,int &y)
{
	if(!b) {x=1; y=0; return a;}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

map <int,int> _hash;
inline int exBSGS(int a,int b,int p)
{
	a%=p; b%=p;
	if(b == 1 || p == 1) return 0;
	int d,ax=1,cnt=0,x,y;
	while((d=exgcd(a,p,x,y))^1)
	{
		if(b%d) return -1;
		b/=d; p/=d; cnt++;
		ax=1ll*ax*(a/d)%p;
		if(ax == b) return cnt;
	}
	
	exgcd(ax,p,x,y);
	int inv=(x%p+p)%p;
	b=1ll*b*inv%p;
	
//	BSGS
	_hash.clear();
	int t=ceil(sqrt(p)),val=1;
	for(int i=0;i<t;i++)
	{
		_hash[1ll*b*val%p]=i;
		val=1ll*val*a%p;
	}
	a=val; val=1;
	
	if(!a) return !b? 1+cnt:-1;
	for(int i=0,j;i<=t;i++)
	{
		j=_hash.find(val) == _hash.end()? -1:_hash[val];
		if(~j && i*t-j >= 0) return i*t-j+cnt;
		val=1ll*val*a%p;
	}
	return -1;
}

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	int a,b,p,ans;
	while(scanf("%d%d%d",&a,&p,&b) == 3 && a && b && p)
	{
		ans=exBSGS(a,b,p);
		if(~ans) printf("%d\n",ans);
		else puts("No Solution");
	}
//	fclose(stdin); fclose(stdout);
	return 0;
}
```

由于我太菜，在 luogu 上没找到其他 exBSGS 的题，如果您有这样的题目推荐，可以私信或者下方回复。谢谢您的鼓励和支持！

## $\text{Thank you for your reading !}$

---

## 作者：FifthAxiom (赞：10)

# $\text{BSGS}$ 算法

## 概念

BSGS 算法用于求解离散对数同余方程
$$
a^t\equiv b\pmod{p}
$$

## 算法

我们先讨论 $a$ 和 $p$ 互质的情况。

首先由欧拉定理可以知道
$$
a^{t}\equiv a^{t\mod{\varphi(p)}}\pmod{p}
$$
而又知 $\varphi(p)<p$ ，那么考虑暴力枚举 $1\sim p$，一定可以找出最小的非负整数 $t$ 

设 $k=\sqrt{p}+1$ ，$t=kx-y$  ，其中 
$$
\begin{aligned}
x\in[1,\ k],\quad y\in[0,\ k-1]
\end{aligned}
$$
这样通过枚举 $x,y$ ，一定可以遍历到 $1\sim p$ 。当然开始时要对 $x=0$ 进行特判。

发现 $x,y\sim \Theta(\sqrt{p})$ 。那么考虑优化：首先将问题转化为求解
$$
a^{kx}\equiv b\cdot a^y\pmod{p}
$$
用一个 Hash 表将右边所有的取值与 $y$ 的对应存下来，然后枚举 $x$ ，在 Hash 表中查找是否有与 $a^{kx}$ 对应的 $y$ 即可。预处理和枚举的时间复杂度都是 $\Theta(\sqrt{p})$ 级别，因此总复杂度就是 $\Theta(\sqrt{p})$ 。

## Q & A

>Q : 为什么 $x$ 一定要从 $1$ 开始枚举？
>
>A : 考虑 $x=0$ 的情况，如果继续上面的枚举，那么相当于求 $1\equiv ba^y\pmod{p}$ ，这样的 $y$ 一定是负数，而 BSGS 求解的 $t$ 经常要求是非负整数。所以从 $1$ 开始枚举。

## exBSGS

此时不要求 $a,p$ 互质，那么怎么求解呢？

注意到
$$
a^t\equiv b\pmod{p} \Leftrightarrow a^t+kp=b
$$
令 $d=\gcd(a,p)$ ，等式的左边显然能被 $d$ 整除，那么可分为两种情况

1. $d\nmid b$ ，此时无解

2. $d \mid b$ ，那么将等式两边同时除 $d$ 得
    $$
    \begin{aligned}
    &\dfrac{a}{d}a^{t-1}+k\dfrac{p}{d}=\dfrac{b}{d}\\
    \Leftrightarrow & \dfrac{a}{d}a^{t-1}\equiv \dfrac{b}{d}\pmod{\dfrac{p}{d}}\\
    \Leftrightarrow & a^{t-1}\equiv \dfrac{b}{d}\cdot\left(\dfrac{a}{d}\right)^{-1}\pmod{\dfrac{p}{d}}\\
    \end{aligned}
    $$
    

如果 $a$ 和 $\dfrac{p}{d}$ 已经互质了，那么直接用 BSGS 求解即可，如果不互质，递归执行步骤。事实上，由于因数有限，递归次数一定不会超过 $\mathcal{O}(\log p)$

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long LL;

const int INF = 0x3f3f3f3f;

int a, b, p;
unordered_map<int, int> hs;

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int BSGS(int a, int b, int p) {
    if (1 % p == b % p) return 0;
    int k = sqrt(p) + 1;
    hs.clear();
    for (int y = 0, r = b % p; y < k; y++) {
        hs[r] = y;
        r = (LL)r * a % p;
    }
    int ak = 1;
    for (int i = 1; i <= k; i++) ak = (LL)ak * a % p;
    for (int x = 1, l = ak; x <= k; x++) {
        if (hs.count(l)) return k * x - hs[l];
        l = (LL)l * ak % p;
    }
    return -INF;
}

int exBSGS(int a, int b, int p) {
    b = (b % p + p) % p;
    if (1 % p == b % p) return 0;
    int x, y;
    int d = exgcd(a, p, x, y);
    if (d > 1) {
        if (b % d) return -INF;
        exgcd(a / d, p / d, x, y);
        return exBSGS(a, (LL)b / d * x % (p / d), p / d) + 1;
    }
    return BSGS(a, b, p);
}

int main() {
    while (~scanf("%d%d%d", &a, &p, &b), a || b || p) {
        int res = exBSGS(a, b, p);
        if (res < 0) puts("No Solution");
        else printf("%d\n", res);
    }
    return 0;
}
```

---

## 作者：_Sein (赞：5)

$\operatorname{BSGS}$要解决的**问题**:
给定整数$a,b,p$，其中$a,p$互质，求一个非负整数$x$,使得
$$a^x \equiv b(mod~p)$$
首先我们先可以了解一下,[欧拉定理](https://blog.csdn.net/zyszlb2003/article/details/89356152)
$$a^{\varphi(n)}\equiv 1(mod~n)$$
设$x=i*m+w$,其中$m=\left \lceil\ \sqrt{p}\right\rceil,0\leq w\leq m-1$，为什么要向上取整呢，因为我们要保证遍历到$p$，才能保证$\varphi(p)$被遍历到，保证覆盖到最小正整数解。
则原问题转化为:
$$a^{i*m+w}\equiv b(mod~n)$$
即:
$$a^{i*m}*a^w\equiv b(mod~n)$$
~~使用时空扭曲术！~~ 设$A=a^{i*m},B=n,x=a^w,k=b.$~~使用大复原术！~~ 得到:
$$A*x+B*y=k$$
~~这不是同余方程吗！~~ 通过[$\operatorname{exgcd}$](https://blog.csdn.net/zyszlb2003/article/details/89349052)，求出$x$,即$a^w$.
最小整数解即为第一个符合条件的$i*m+w$.
关于怎么实现快速查找$w$,我们需要打一个hash表，~~用map也行~~，查表即可
```cpp
struct hash
{
    struct node
    {
        ll t,next,p;
    }a[maxn<<2];
    int v[maxn<<2],num,len;
    void ins(int p,ll t)
    {
        ll k=t&maxn;
        if(v[k]!=num)
        {
            v[k]=num;
            a[k].next=-1;a[k].t=t;a[k].p=p;
        }
        else
        {
            for(;;k=a[k].next)
            {
                if(t==a[k].t)return ;
                if(a[k].next==-1)break;
            }
            a[k].next=++len;a[len].t=t;a[len].p=p;a[len].next=-1;
        }
    }
    ll check(ll t)
    {
        ll k=t&maxn;
        if(v[k]!=num)return -1;
        for(;k!=-1;k=a[k].next)if(a[k].t==t)return a[k].p;
        return -1;
    }
}h;
```
这是怎么一回事呢？就是说，我预处理将$a_1,a_2,......,a_{m-1}$加密到$hash$表中,由于$0\le w<m$，就可以快速查询出$w$的值了。
那么
我们代码的流程就是
1.将$a_1,a_2,......,a_m$预处理进hash表
2.后枚举$i*m,0\leq i \leq m$，判断是否可行。
代码
```cpp
ll bsgs(ll A,ll B,ll p)
{
    //ll t=1%p;for(ll i=0;i<=100;i++){if(t==B)return i;t=t*A%p;}
    ll D=1%p;ll t;
    ll m=(int)sqrt(p)+1;
    t=1%p;h.len=maxn;
    for(int i=0;i<m;i++)
        {h.ins(i,t);t=t*A%p;}
    //h.ins(m,t);
	ll am=t;
    for(int i=0;i<=m;i++)
    {
        ll a=D,b=p,k=B,x,y;
        ll d=exgcd(a,b,x,y);
        x=((x*(k/d))%(b/d)+(b/d))%(b/d);
        ll w=h.check(x);
        if(w!=-1)return i*m+w;
        D=D*am%p;
    }
    return -1;
}
```
**$exBSGS$算法**

若$a,p$不互质，怎么办呢？
$$a^x\equiv b(mod~p)$$
那我们就想办法让它互质呗。
设$d_1=gcd(a,p)$,则
$$a^x+py=b$$
$$a^{x-1}*\frac{a}{d_1}+\frac{p}{d_1}*y=\frac{b}{d_1}$$
$$a^{x-1}*\frac{a}{d_1}\equiv  \frac{b}{d_1}(mod ~\frac{p}{d_1})$$
设$D_1=\frac{a}{d_1},b_1=\frac{b}{d_1},p_1=\frac{p}{d_1}$
若依旧不互质，则设$d_2=gcd(a,p_1)$,则
$$a^{x-2}*D_1*\frac{a}{d_2}\equiv\frac{b_1}{d_2}(mod~\frac{p_1}{d_2})$$
$$.................$$
经过多次运算，得到最后一条互质的~~柿子~~

$$a^{x-n}*D_n\equiv b_n(mod~p_n) $$  

其中$$D_n=\prod_{i=1}^n\frac{a}{d_i},b_n=\frac{b}{\prod _{i=1}^{n}d_i},p_n=\frac{p}{\prod _{i=1}^{n}d_i}$$

由$\operatorname{BSGS}$可知，设$x-n=i*m+w$,其中$m=\left \lceil\ \sqrt{p_n}\right\rceil,0\leq w\leq m-1$
则原问题转化为:
$$a^{i*m+w}*D_n\equiv b_n(mod~p_n)$$
即:
$$a^{i*m}*a^w*D_n\equiv b_n(mod~p_n)$$
~~使用时空扭曲术！~~ 设$A=a^{i*m}*D_n,B=p_n,x=a^w,k=b_n.$~~使用大复原术！~~ 得到:
$$A*x+B*y=k$$
最后答案就为$i*m+w+n$.
回到$\operatorname{BSGS}$即可
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#define ll long long
using namespace std;
const ll maxn=(1<<16)-1;
struct hash
{
    struct node
    {
        ll t,next,p;
    }a[maxn<<2];
    int v[maxn<<2],num,len;
    void ins(int p,ll t)
    {
        ll k=t&maxn;
        if(v[k]!=num)
        {
            v[k]=num;
            a[k].next=-1;a[k].t=t;a[k].p=p;
        }
        else
        {
            for(;;k=a[k].next)
            {
                if(t==a[k].t)return ;
                if(a[k].next==-1)break;
            }
            a[k].next=++len;a[len].t=t;a[len].p=p;a[len].next=-1;
        }
    }
    ll check(ll t)
    {
        ll k=t&maxn;
        if(v[k]!=num)return -1;
        for(;k!=-1;k=a[k].next)if(a[k].t==t)return a[k].p;
        return -1;
    }
}h;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b){x=1;y=0;return a;}
    else
    {
        ll tx,ty;ll d=exgcd(b,a%b,tx,ty);
        x=ty;y=tx-(a/b)*ty;
        return d;
    }
}
ll exbsgs(ll A,ll B,ll p)
{
    //ll t=1%p;for(ll i=0;i<=100;i++){if(t==B)return i;t=t*A%p;}
    ll D=1%p;ll g=0,d;ll t;
    B%=p;if(B==1||C==1)return 0;
    while((d=gcd(A,p))!=1)
    {
        if(B%d)return -1;
        B/=d;p/=d;D=D*(A/d)%p;g++;
        if(B==D)return g;
    }
    ll m=(int)sqrt(p)+1;
    t=1%p;h.len=maxn;
    for(int i=0;i<m;i++)
        {h.ins(i,t);t=t*A%p;}
    //h.ins(m,t);
	ll am=t;
    for(int i=0;i<=m;i++)
    {
        ll a=D,b=p,k=B,x,y;
        ll d=exgcd(a,b,x,y);
        x=((x*(k/d))%(b/d)+(b/d))%(b/d);
        ll w=h.check(x);
        if(w!=-1)return i*m+g+w;
        D=D*am%p;
    }
    return -1;
}
int main()
{
    ll A,p,B;h.num=0;
    while(scanf("%lld%lld%lld",&A,&p,&B)!=EOF)
    {
    	if(!A&&!p&&!B)break;
        h.num++;
        ll x=exbsgs(A,B,p);
        if(x==-1)puts("No Solution");
        else printf("%lld\n",x);
    }
    return 0;
}
```

经过我们机房日日夜夜地辛苦奋战，成功将不用$exgcd$的方法出炉啦！
设$x-n=i*m-w$,其中$m=\left \lceil\ \sqrt{p_n}\right\rceil,0\leq w\leq m-1$
则原问题转化为:
$$a^{i*m-w}*D_n\equiv b_n(mod~p_n)$$
即:
$$a^{i*m}*D_n\equiv b_n*a^w(mod~p_n)$$
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#define ll long long
using namespace std;
const int maxn=(1<<16)-1;
struct hash
{
    int v[maxn<<2];int num;
    struct node
    {
        ll t;int p,next;
    }a[maxn<<2];int len;
    hash(){num=0;}
    inline void ins(int p,ll t)
    {
        int k=t&maxn;
        if(v[k]!=num)
        {
            v[k]=num;a[k].next=-1;a[k].p=p;a[k].t=t;
        }
        else 
        {
        	for(;;k=a[k].next)
        	{
        		if(t==a[k].t){a[k].p=p;return ;}
        		if(a[k].next==-1)break;
        	}
            a[k].next=++len;a[len].p=p;a[len].t=t;a[len].next=-1;
        }
    }
    inline int find(ll t)
    {
        int k=t&maxn,p=-1;
        if(v[k]!=num)return -1;
        for(;k!=-1;k=a[k].next)
            if(t==a[k].t)p=a[k].p;
        return p;
    }
}h;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll exbsgs(ll A,ll B,ll p)
{
    ll d,D=1%p;ll g=0;B=B%p;
    if(B==1||p==1)return 0;
    while((d=gcd(A,p))!=1)
    {
        if(B%d)return -1;
        B/=d;p/=d;D=(D*A/d)%p;
        g++;if(B==D)return g;
    }
    ll t=1%p;ll m=(int)sqrt(p)+1;
    h.len=maxn;
    for(int i=0;i<m;i++)
        {h.ins(i,(t*B)%p);t=t*A%p;}
    ll am=t;
    for(int i=0;i<=m;i++)
    {
        ll w=h.find(D);
        if(w!=-1&&i*m-w>=0)return i*m-w+g;
        D=D*am%p;
    }
    return -1;
}
int main()
{
    ll a,b,p;
    while(scanf("%lld%lld%lld",&a,&p,&b)!=EOF)
    {
        if(!a&&!b&&!p)break;h.num++;
        ll ans=exbsgs(a,b,p);
        if(ans!=-1)printf("%lld\n",ans);
        else puts("No Solution");
    }
    return 0;
}
```

其实每次加密时，我们只要插入$B*A^j$，查表即可

---

## 作者：_Fontainebleau_ (赞：4)

### 题目

求解

$$a^x\equiv b\pmod p$$

与 [可爱的质数](https://www.luogu.com.cn/problem/P3846)不同的是，这里的 $a$ 和 $p$ 并不一定互质。这意味着我们需要引入一种新的算法——exBSGS。

### exBSGS

**前置芝士**
- [原根](https://www.luogu.com.cn/problem/P6091)
- [BSGS](https://www.luogu.com.cn/problem/P3846)
- [exgcd](https://www.luogu.com.cn/problem/P5656)

当然如果您觉得一个一个点开看麻烦的话，可以康一康[我的数论总结](https://www.luogu.com.cn/blog/181775/shu-lun)，也欢迎大佬来指出错误。

**exBSGS**

虽然 $a,p$ 不一定互质。我们可以想办法让她们互质。

具体地，设 $d_1=\gcd(a,p)$。若 $d_1 \nmid b$，方程无解。否则将方程同时除以 $d_1$，得：

$$\frac{a}{d_1}·a^{x-1}\equiv \frac b{d_1}\pmod {\frac p{d_1}}$$

若 $a$ 和 $\frac{p}{d_1}$ 仍不互质就继续重复上面的步骤，直到 $\displaystyle \gcd\left(a,\frac{p}{\prod _{i=1}^{k} d_i}\right )$。

记 $D=\prod \limits_{i=1}^k d_i$，原方程被化为：

$$\frac {a^k}{D}\times a^{x-k}\equiv \frac{b}{D}\pmod {\frac{p}{D}}$$

此时 $\gcd \left( \dfrac{a^k}{D},p\right)=1$，故 $\dfrac{a^k}{D}$ 存在逆元，可以丢到式子右边。

这就是一个平凡的 BSGS 了。求解出 $x-k$ 再加上 $k$ 就是原方程的解。

如果有可能存在 $x\le k$ 的情况。我们在消去因子前先 $O(k)$ 枚举一下 $a^i\equiv b\pmod p$ 即可。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,p;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int exgcd(int a,int b,int &x,int &y)
{
	if(!b)
	{
		x=1,y=0;
		return a;
	}
	int gcd=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return gcd;
}
inline int exBSGS(int a,int b,int mod)
{
	b%=mod;
	if(b==1||mod==1)	return 0;
	int g=0,val=1;
	while(true)
	{
		int d=gcd(a,mod);
		if(d==1)	break;
		if(b%d)	return -1;
		b/=d,mod/=d,val=val*a/d%mod;
		g++;
		if(b==val)	return g;
	}
	int x,y;
	exgcd(val,mod,x,y);
	x=(x%mod+mod)%mod;
	b=b*x%mod,a%=mod;
	map<int,int>mp;
	int t=ceil(sqrt(mod));
	int z=1;
	for(int i=0;i<t;i++)
		mp[b*z%mod]=i,z=z*a%mod;
	int p=1;
	for(int i=1;i<=t;i++)
	{
		p=p*z%mod;
		if(mp.count(p))	return i*t-mp[p]+g;
	}
	return -1;
}
signed main()
{
	a=read(),p=read(),b=read();
	while(a||b||p)
	{
		int ans=exBSGS(a,b,p);
		if(ans==-1)	puts("No Solution");
		else	printf("%lld\n",ans);
		a=read(),p=read(),b=read();
	}
	return 0;
}

```


---

## 作者：WeLikeStudying (赞：3)

**题意**
- 在大约 $O(\sqrt n)$ 时间求解关于 $x$ 的方程 $a^x\equiv b\pmod n$。
- 若有解要求输出最小的自然数 $x$。

**大步小步**
- 我们先来解决离散对数问题的简单形式：已知 a,b 和质数 p，求 x 满足 $a^x\equiv b\pmod p$
- 根据费马小定理，如果有解一定存在 $0\leq x<p-1$ 的可行解，当然我们还是不能直接枚举。
- 设 $m=\sqrt p$ ，x 可以变为 $k_1m+k_2$ 的形式，且有：
$$a^{k_1m}\equiv\frac b {a^{k_2}}\pmod p$$
- 先枚举 $k_2$ 将 $\frac b {a^{k_2}}$ 放入某个数据结构维护，然后枚举 $k_1$ 查询 $a^{k_1m}$，时间是 $O(\sqrt p)$ 或 $O(\sqrt p\log p)$ 的。
- [模板题](https://www.luogu.com.cn/problem/P3846)。
- [代码实现](https://www.luogu.com.cn/paste/yu718sqa)。

**拓展大步小步**
- 再拓展一下更一般的情况，模数是一个非质数 $n$，找到 $x$ 使得 $a^x\equiv b\pmod n$。
- 如果 $a\perp n$ 没什么好说的，可以用拓展欧几里得求逆元，方法跟之前一模一样~~我都不好意思讲~~。
- 否则令 $d=\gcd(a,n)$，若 $d\nmid b$ 显然无解~~除非b=1~~，否则就有：
$$\frac{a^x}d\equiv \frac bd\pmod {\frac n d}$$
$$\frac ad a^{x-1}\equiv \frac bd\pmod {\frac n d}$$
$$a^{x-1}\equiv \frac ba\pmod {\frac n d}$$
- $x$ 若有解显然 $x\ge1$。
- 不过一定要注意，$a$ 不一定与 $\dfrac nd$ 互质啊（比如 $a=2,n=2^8$），所以可能得反复求 gcd 使得常数稍大，但考虑到根号级别的算法复杂度这个还是完全可以接受的。
- [模板题](https://www.luogu.com.cn/problem/P4195)。
- 这道题有许多特判，其中有一个问题是大步小步会刷到重复的（但其实这样反而简单，因为可能的 $a^x\bmod n$ 一定不超过 $\sqrt n$ 种）。
- [代码实现](https://www.luogu.com.cn/paste/xzftk7u8)。

---

