# 「SWTR-4」Easy Math Problems

## 题目背景

数学老师给小 A 布置了 $2$ 道 Easy Math Problems。

## 题目描述

给定 $n,c,f,l,r$，有集合 $S=\{x\in\mathbb{N_+}\mid\gcd(x,n)\leq c\}$ 和集合 $Q=\{x\in S\mid l\leq x\leq r\}$。

- 集合 $S$ 为所有与 $n$ 的 $\gcd$ 不超过 $c$ 的正整数，集合 $Q$ 为 $S$ 中不小于 $l$，不大于 $r$ 的数。

第一问：请求出集合 $S$ 中第 $f$ 小的数。

第二问：请求出集合 $Q$ 中包含的元素个数。

由于数字很大，所以小 A 想请你帮他求出问题的答案。

## 说明/提示

【样例 $1$ 说明】

$S=\{1,2,3,5,7,9,10,11,13,14,15,17,\dots\},Q=\{10,11,13,14,15,17\}$，可知集合 $S$ 第 $8$ 小的数为 $11$，集合 $Q$ 中包含的元素个数为 $6$。

【数据范围与约定】

**本题使用捆绑测试**。

子任务 $1(15\%)$：$n\leq 10^3$，$r\leq 10^3$，$f\leq 10^3$。

子任务 $2(35\%)$：$n\leq 10^5$，$r\leq 10^5$，$f\leq 10^5$。

子任务 $3(35\%)$：$n\leq 10^6$，$r\leq 10^{12}$，$f\leq 10^{12}$。

子任务 $4(15\%)$：$n\leq 10^7$，$r\leq 10^{10^5}$，$f\leq 10^{10^5}$。

对于 $100\%$ 的数据，$1\leq c\leq n\leq 10^7$，$1\leq l\leq r\leq 10^{10^5}$，$1\leq f\leq 10^{10^5}$。

【Tips】

想用 $n\log n$ 过这道题？

【时间限制】

对于前 $3$ 个子任务，时间限制 $1\rm{s}$，剩下一个子任务 $500\rm{ms}$。

【Source】

[Sweet Round 04](https://www.luogu.com.cn/contest/26414)$\ \ $B

idea & std：[Alex_Wei](https://www.luogu.com.cn/user/123294)，验题：[xtx1092515503](https://www.luogu.com.cn/user/123369) & [FrenkiedeJong21](https://www.luogu.com.cn/user/203968) & [chenxia25](https://www.luogu.com.cn/user/138400)

## 样例 #1

### 输入

```
12 3 8 10 17
```

### 输出

```
11
6```

## 样例 #2

### 输入

```
72 5 66 13 89
```

### 输出

```
94
54```

## 样例 #3

### 输入

```
360360 123 20200202 123456789 987654321
```

### 输出

```
21751721
802555475```

# 题解

## 作者：Leasier (赞：8)

考虑化简第二问所求式子。

设该式子的值为 $g(n, r, c) - g(n, l - 1, c)$，则需要化简 $g$ 函数。

$g(n, m, k) = \displaystyle\sum_{i = 1}^m [\gcd(i, n) \leq k]$

$ = \displaystyle\sum_{d \mid n}^k \displaystyle\sum_{i = 1}^m [\gcd(i, n) = d]$

$ = \displaystyle\sum_{d \mid n}^k \displaystyle\sum_{i = 1}^{\lfloor \frac{m}{d} \rfloor} [\gcd(i, \frac{n}{d}) = 1]$

设第二层 $\sum$ 的值为 $f(\frac{n}{d}, \lfloor \frac{m}{d} \rfloor)$，则需要化简 $f$ 函数。

$f(n, k) = \displaystyle\sum_{i = 1}^k [\gcd(i, n) = 1]$

$ = \displaystyle\sum_{i = 1}^k \sum_{d\ | \gcd(i, n)} \mu(d)$

$ = \displaystyle\sum_{d \mid n} \mu(d) \lfloor \frac{k}{d} \rfloor$

对于第一问，考虑二分答案。

我们可以先消除所有长度为 $n$ 的 $\gcd$ 周期的影响（单个周期为 $g(n,  n, c)$），从而使二分答案范围降低为 $1 \sim n$，然后进行二分答案，最后再将整周期的贡献加上即可。~~时间复杂度还是不会算。~~

具体细节见代码注释。

代码：
```python
import math

def mu(n):
	ans = 1
	i = 2
	while i * i <= n:
		if n % i == 0:
			n //= i
			if n % i == 0:
				return 0
			ans = -ans
		i += 1
	if n > 1:
		ans = -ans
	return ans

def f_function(n, k):
	t = min(int(math.sqrt(n)), k)
	ans = 0
	for i in range(1, t + 1):
		if n % i == 0:
			ans += mu(i) * (k // i)
			if i * i != n and n // i <= k:
				ans += mu(n / i) * (k // (n // i))
	return ans

def g(n, m, k):
	t = min(int(math.sqrt(n)), k)
	ans = 0
	for i in range(1, t + 1):
		if n % i == 0:
			ans += f_function(n // i, m // i)
			if i * i != n and n // i <= k:
				ans += f_function(i, m // (n / i))
	return ans

def search(n, m, k):
	l = 1
	r = n
	while l < r:
		mid = (l + r) >> 1
		if g(n, mid, m) < k:
			l = mid + 1
		else:
			r = mid;
	return l

n, c, f, l, r = map(int, input().split())
x = g(n, n, c)
if f % x == 0: # 整周期，可能会出现实际端点在 1 ~ n 中的情况。
	y = (f // x - 1) * n
	f = x
else:
	y = f // x * n
	f %= x
print(search(n, c, f) + y)
print(g(n, r, c) - g(n, l - 1, c), end = "")
```

---

## 作者：QQ82272760 (赞：4)

~~这道题推式子要莫反你跟我说是绿题~~

第一问貌似不太好做我们先看到第二问

他要求个数而且是区间内，根据套路最后一步应该是 $\mathrm{cnt}(r)-\mathrm{cnt}(l-1)$，也就是说只要求 $\mathrm{cnt}(m)$ 即 $[1,m]$ 内的个数就行了。

$$
\mathrm{cnt}(m)=\sum_{i=1}^m[\gcd(i,n)\le c]
$$

如果令

$$
f(n)=[n\le c]=\sum_{d|n}g(d)
$$

根据莫比乌斯反演

$$
g(n)=\sum_{d|n}\mu\left(\frac nd\right)f(d)
$$

于是

$$
\begin{aligned}
\mathrm{cnt}(m)

&=\sum_{i=1}^m\sum_{d|i,d|n}g(d)\\

&=\sum_{d=1}^n[d|n]g(d)\left\lfloor\frac md\right\rfloor

\end{aligned}
$$

这个 $m$ 太大还是做不了，但对答案有贡献的 $d$ 一定满足 $d|n$，所以可以令 $m=kn+r(0\le r<n)$

$$
\begin{aligned}
\mathrm{cnt}(m)

&=k\sum_{d=1}^n[d|n]g(d)\frac{n}d+\sum_{d=1}^n[d|n]g(d)\left\lfloor\frac rd\right\rfloor\\

&=k\mathrm{cnt}(n)+\mathrm{cnt}(r)

\end{aligned}
$$

直接通过暴力求出 $\mathrm{cnt}(1\dots n)$（$O(n\log n)$ 貌似不太行，需要卡卡常，看代码），然后 $k$ 和 $r$ 都能直接高精除求出来。

第一问 $f=k\mathrm{cnt}(n)+\mathrm{cnt}(r)$，也可以直接高精除，再花 $O(n)$ 枚举或者 $O(\log n)$ 二分查找得到 $r$ 就好了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define pr pair<num,int>
#define mp make_pair
#define fst first
#define scd second
#define re register
using namespace std;
int n,c;
int cnt[10000005];
char s[100005];
struct num{
	int a[100010],len;
	void operator--(){
		int res=1;
		for(re int i=1;i<=len;++i){
			if(!res) break;
			if(a[i]) --a[i],res=0;
			else a[i]=9;
		}
		if(len>1){
			if(!a[len]) --len;
		}
		return;
	}
	void operator+=(int y){
		for(re int i=1;i<=len;++i){
			a[i]+=y;
			y=a[i]/10; a[i]%=10;
			if(!y) break;
		}
		while(y) a[++len]=y%10,y/=10;
		return;
	}
	void operator-=(num y){
		int res=0;
		for(re int i=1;i<=len;++i){
			if(i>y.len) a[i]-=res;
			else a[i]-=(res+y.a[i]);
			if(a[i]<0) a[i]+=10,res=1;
			else res=0;
		}
		while(len>1){
			if(!a[len]) --len;
			else break;
		}
		return;
	}
	void operator*=(int y){
		if(!y) a[len=1]=0;
		int res=0;
		for(re int i=1;i<=len;++i){
			a[i]=res+a[i]*y;
			res=a[i]/10; a[i]%=10;
		}
		while(res) a[++len]=res%10,res/=10;
		return;
	}
}f,l,r,ans;
void read(num &x){
	scanf("%s",s); x.len=strlen(s);
	for(re int i=1;i<=x.len;++i){
		x.a[i]=(s[x.len-i]^48);
	}
	return;
}
void write(num x){
	for(int i=x.len;i>=1;i-=1) printf("%d",x.a[i]);
	printf("\n");
	return;
}
pr operator/(num x,int y){
	int res=0;
	num z; z.len=0;
	for(re int i=x.len;i>=1;--i){
		res=(res<<1)+(res<<3)+x.a[i];
		z.a[i]=res/y; res%=y;
		if(z.a[i]&&!z.len) z.len=i;
	}
	return mp(z,res);
}
inline int check(int x,int y){
	if(y){
		if(x<=c) return 1;
		return check(y,x%y);
	}
	else return (x<=c);
}
num solve(num x){
	pr g=x/n; num res;
	res=g.fst;
	res*=cnt[n];
	res+=cnt[g.scd];
	return res;
}
int main(){
	scanf("%d%d",&n,&c);
	int m=n+1>>1;
	for(re int i=1;i<=n;++i){
		if(i<=m) cnt[i]=check(n,i);
		else cnt[i]=cnt[n-i];
	}
	for(re int i=1;i<=n;++i) cnt[i]+=cnt[i-1];
	read(f); pr g=(f/cnt[n]); ans=g.fst;
	if(!g.scd) --ans,g.scd=cnt[n];
	for(re int i=g.scd;i<=n;i+=(g.scd-cnt[i])){
		if(cnt[i]==g.scd){
			ans*=n; ans+=i; break;
		}
	}
	write(ans);
	read(l); --l; read(r);
	ans=solve(r); ans-=solve(l);
	write(ans);
	return 0;
}
```
**后(zheng)记(wen)**

后来我发现用莫反只是为了证周期性，但如果只是要证周期性的话，那大可不必这么麻烦。其实 $\gcd(n,m)=\gcd(n,m-n)$ 它们同时大于 $c$ 或同时不大于 $c$，也就是相隔 $n$ 的两个函数值相等，每 $n$ 个加起来结果就一样。

~~这样一来，这题评绿题也是合理的~~

Thanks~

---

## 作者：Kevin090228 (赞：3)

魏老师的题，很酷！

题解区全是 $O(n)$ 的，但是实际上完全不需要。

考虑求出所有 $\gcd(i,n)$ 之后，剩余的部分都是简单的高精度运算，所以我们需要做的其实是尽量快地求出所有 $\gcd(i,n)$。普通的 $O(n\log n)$ 做法显然被卡掉了，但是在考虑莫反这种高级算法之前，我们可以继续尝试暴力。

考虑对于 $n$ 的每个质因数 $p$，我们暴力地给 $p^1,p^2,\cdots$ 的倍数的 $\gcd$ 数值乘 $p$。这玩意的操作次数是 $\frac{n}{p}$ 到 $\frac{n}{p-1}$ 之间的一个数。因为 $2\times 3\times 5\times 7\times 11\times 13\times 17\times 19$ 和 $10^7$ 很接近，直接计算操作次数最大值就可以发现操作次数是可以接受的。

事实上写出代码跑在最后一个 sub 跑出了 $\text{50ms}$ 的好成绩。

---

## 作者：2018ljw (赞：3)

相对毒瘤的推式子题。

- 变量名称提醒：$n,c,l,r$ 与原题中一致，题解中的 $f$ 均表示函数。除去推导公式中出现的 $k$，其余的 $k$ 均表示原题中的 $f$。

首先看第一问，求第 $k$ 大。比较直观的想法是二分或性质。但暂时想不到什么，先过。

再看第二问，求区间合法个数。传统套路肯定是转化为前缀相减。所以考虑如何求出 $[1,r]$ 的合法个数。

设 $f(m)$ 表示区间 $[1,m]$ 的答案，那么我们的式子即为 $f(m)=\sum\limits_{i=1}^m\left[\gcd(i,n)\le c\right]$。

枚举 $\gcd$，发现一定为 $n$ 的因数。
$$
f(m)=\sum_{k\mid n,k\le c}\sum_{i=1}^m[gcd(i,n)=k]\\
=\sum_{k\mid n,k\le c}\sum_{i=1}^{\lfloor\frac mk\rfloor}[gcd(i,\frac nk)=1]\\
=\sum_{k\mid n,k\le c}\sum_{i=1}^{\lfloor\frac mk\rfloor}\sum_{d\mid i,d\mid \frac nk}\mu(d)\\
=\sum_{k\mid n,k\le c}\sum_{dk\mid n}\mu(d)\lfloor\frac{m}{dk}\rfloor
$$

改为枚举 $dk$

$$
f(m)=\sum_{T\mid n}\lfloor\frac mT\rfloor\sum_{k\mid T,k\le c}\mu(\frac Td)
$$

记 $g(m)=\sum\limits_{d\mid m,d\le c}\mu(\frac md)$，则 $f(m)=\sum\limits_{T\mid n}\lfloor\frac mT\rfloor g(T)$。

关注到实际需要计算的 $T$ 只有 $n$ 的约数，$10^7$ 以内约数个数最多的是 $8648640$，约数个数为 $448$。所以 $g$ 我们可以 $500^2$ 预处理。

至此，前三个子任务均可整除分块 $O(\sqrt m+d(n)^2)$ 完成。$d(n)$ 表示 $n$ 的约数个数。

考虑我们的复杂度瓶颈在于 $\lfloor\frac mT\rfloor$，尝试将其破开。基于整除的定义，我们假设 $m=xn+y$，其中 $x,y\ge 0$ 且 $y<x$。

那么有 $\large f(xn+y)=\sum\limits_{T\mid n}\lfloor\frac {xn+y}T\rfloor g(T)$。

因为 $T\mid n$，所以将整除拆开， $x$ 可以提出去。得到 $\large f(xn+y)=x\sum\limits_{T\mid n}\frac {n}Tg(T)+\sum \limits_{T\mid n}\lfloor\frac yT\rfloor g(T)$

左边一定是整除，于是有 $f(xn+y)=xf(n)+f(y)$。

至此，问题变为求出 $f(1\dots n)$。

考虑每个 $T$ 对所有 $f$ 的贡献。即 $f(x)+=\lfloor\frac xT\rfloor g(T)$。

$g(T)$ 是常量不用管，从整除角度考虑，发现从 $1\dots n$，我们的 $x$ 递增，显然每增加 $T$，整除的值都会多 $1$。因此变为一堆区间的加法，直接差分累计前缀和即可。对于每个 $T$，其都有 $\frac nT$ 个不同的加法区间。因此复杂度 $\sum\limits_{T\mid n}\frac nT=\sum\limits_{T\mid n}T$，即 $n$ 的约数之和。

显然其远小于调和级数，多次测试后发现其与 $n$ 同阶（$n=8648640$ 时最大，约为 $4\times 10^7$）。

所以预处理 $g,f$ 的总复杂度 $O(n)$ 级别。

此外，我们还得到了一个重量级结论：$f(xn+y)=xf(n)+f(y)$。

因此，第二问可以直接解决。需要高精度全家桶，其中由于乘除取模均对低精进行，可以 $O(len)$ 完成。

考虑第一问，我们等效于求最小的 $x$，使得 $f(x)=k$。

显然 $f$ 不严格单调的，那么是二分吗？

虽然看起来很像，但并不是。我们计算一次 $f(m)$ 复杂度为 $O(len)$，二分的值域为 $[1,10^{10^5}]$，$\log_210^{10^5}$ 约为 $3.4\times 10^5$，这两个再乘起来，$10^{10}$ 显然无法通过。

回头看我们的结论会发现，因为 $f$ 单调不减，所以一定有 $f(n)\ge f(y)$。那么我们直接将 $k$ 除以 $f(n)$，得到商即为系数后，找到等于余数且最小的位置合并，是不是就对了？

是，但不完全是。因为这样算第一个样例会输出 $12$。

为什么？$f(12)=8$，那么余数为 $0$，商为 $1$。但显然 $f(11)=8$。所以我们需要特判余数为 $0$ 时，商自减，找到等于 $f(n)$ 且最小的位置作为贡献统计进答案。

复杂度 $O(len+\log n)$。不过反正前面已经有个 $O(n)$ 了，这里直接暴力找也没啥问题。

总复杂度 $O(n)$。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
bool isp[10000001];
int p[1000001],u[10000001],tot,n,c;
int ys[500],cnt,g[501],f[10000001];
struct gj{
	int a[100001],len;
	//高精度全家桶
	//pushup 用来处理进位退位。
	void pushup(){
		int i;
		for(i=1;i<=len;i++){
			if(a[i]<0)a[i+1]-=(-a[i]+9)/10,a[i]=(a[i]%10+10)%10;
		}
		for(i=len;i;i--){
			len=i;
			if(a[i])break;
		}
		for(i=1;i<len;i++){
			a[i+1]+=a[i]/10,a[i]%=10;
		}
		for(i=len;a[i]>=10;i++){
			len=i+1;
			a[i+1]=a[i]/10;
			a[i]%=10;
		}
	}
	void operator/=(int y){
		int tmp=0,i;
		for(i=len;i;i--){
			tmp=tmp*10+a[i];
			a[i]=tmp/y;
			tmp%=y;
		}
		pushup();
	}
	void operator*=(int y){
		int i;
		for(i=1;i<=len;i++)a[i]*=y;
		pushup();
	}
	void operator-=(int y){
		a[1]-=y;
		pushup();
	}
	void operator+=(int y){
		a[1]+=y;
		pushup();
	}
	void print(int t){
		int i;
		for(i=len;i;i--)printf("%d",a[i]);
		if(t)putchar(t);
	}
	int cint(){
		//将高精度数转化为低精度数
		//仅用于取模后。
		int i,res=0;
		for(i=len;i;i--)res=res*10+a[i];
		return res;
	}
};
gj x,y,z,res1,res2;
gj operator-(gj x,gj y){
	int i;
	for(i=1;i<=x.len;i++)x.a[i]-=y.a[i];
	x.pushup();
	return x;
}
void s(){
	//线性筛+预处理 f,g
	int i,j;
	u[1]=1;
	for(i=2;i<=n;i++){
		if(!isp[i])p[++tot]=i,u[i]=-1;
		for(j=1;j<=tot&&i*p[j]<=n;j++){
			isp[i*p[j]]=1;
			if(i%p[j]==0)break;
			u[i*p[j]]=u[i]*u[p[j]];
		}
	}
	for(i=1;i*i<n;i++)if(n%i==0)ys[++cnt]=i,ys[++cnt]=n/i;
	if(i*i==n)ys[++cnt]=i;
	std::sort(ys+1,ys+cnt+1);
	for(i=1;i<=cnt;i++){
		if(ys[i]>c)break;
		for(j=i;j<=cnt;j++){
			if(ys[j]%ys[i])continue;
			g[j]+=u[ys[j]/ys[i]];
		}
	}
	for(i=1;i<=cnt;i++)for(j=ys[i];j<=n;j+=ys[i])f[j]+=g[i];
	for(i=1;i<=n;i++)f[i]+=f[i-1];
}
char t[1000001];
int main(){
	int i,j,res=0;
	scanf("%d%d",&n,&c);
	s();
	scanf("%s",t+1);
	x.len=strlen(t+1);
	for(i=1;i<=x.len;i++)x.a[i]=t[x.len-i+1]-'0';
	y=x;y/=f[n];
	res1=y;res1*=n;
	y*=f[n];y=x-y;
	int tt=y.cint();
	//余数
	if(tt){
		for(i=0;i<n;i++){
			if(tt==f[i]){
				res1+=i;
				break;
			}
		}
	}
	else{
		res1-=n;
		//前面已经乘过了，所以直接 -n
		for(i=n;i;i--){
			if(f[i]!=f[n]){
				res1+=i+1;
				break;
			}
		}
	}
	res1.print(10);
	res1=res2;y=res2;x=res2;
	//第一问，结束。清空用到的高精度数。
	scanf("%s",t+1);
	y.len=strlen(t+1);
	for(i=1;i<=y.len;i++)y.a[i]=t[y.len-i+1]-'0';
	y-=1;
	x=y;x/=n;
	res1=x;res1*=f[n];
	x*=n;x=y-x;
	tt=x.cint();
	res1+=f[tt];
	x=res2;y=res2;
	scanf("%s",t+1);
	for(i=1;i<=y.len;i++)y.a[i]=0;
	y.len=strlen(t+1);
	for(i=1;i<=y.len;i++)y.a[i]=t[y.len-i+1]-'0';
	x=y;x/=n;
	res2=x;res2*=f[n];
	x*=n;x=y-x;
	tt=x.cint();
	res2+=f[tt];
	res2=res2-res1;
	res2.print(0);
}
```

---

## 作者：wwt100127 (赞：0)

## 题意：（~~题目已经说得简洁了~~）

## 思路
我们发现其实只需求：
对于某个 $m$，

$$
\sum_{i = 1}^{n} \ [\gcd(d,n) \le c]
$$

我们不妨令：

$$
h(m)= [\gcd(d,n) \le c]
$$

$$
f(m)= \sum_{i = 1}^{m} h(d)
$$

显然 $f(m)$ 单调不减，可以处理第一问。

当 $d \ge n$ 时，$\gcd(d,n)=\gcd(d \bmod n,n)$，所以 $ h(m) $ 显然是周期性的，周期是 $n$，所以就只需要考虑 $m<n$ 的情况就可以了。

$$
f(m)=
\sum_{k \mid n,k \le c} 
\sum_{k=1}^{\frac{m}{k}}
[\gcd(i,\frac{n}{k})=1]
$$

枚举 $\gcd(i,n/k)$ 得：
$$
f(m)=
\sum_{d=1}^{n}
\sum_{k \mid n,k \le c}
\sum_{i=1}^{\frac{m}{k}}
[d \mid i][d \mid \frac{n}{k}]*\mu(d)
$$
令 $d \ast k=T$，显然有 $\frac{m}{T}$ 个 $i$ 满足 $d \mid i$。

所以
$$
f(m)=
\sum_{k \mid n,k \le c}
\sum_{T \mid n}
\mu(d)*\frac{m}{T}
$$

即
$$
f(m)=
\sum_{T \mid n} \frac{m}{T}*
\sum_{k \mid T,k \le c}
\mu(\frac{T}{d})
$$

令 $g(T)=\sum_{d \mid T,d \le c}\mu(\frac{T}{d})$。

那么现在考虑怎样求 $g$，枚举 $n$ 的因数后爆算就行了。

~~感觉本题难点在高精度上~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){ int x=0; bool flag=1; char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') flag=0;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return flag? x:-x;}
const int maxn=1e7+5;
const int SIZE_BIG=1e5+5;
int n,m,c;

int Mu[maxn],Yi[1005];
int F[maxn],g[1005];
int Prime[maxn],cnt;
bool vis[maxn];
void init()
{
	int i,j,num=0;
	Mu[1]=1;
	for(i=2;i<=n;i++)
	{
		if(vis[i]==0)
		{
			Prime[++cnt]=i;
			Mu[i]=-1; 
		}
		for(j=1;j<=cnt && i*Prime[j]<=n;j++)
		{
			vis[i*Prime[j]]=1;
			if(i%Prime[j]==0)
			{
				Mu[i*Prime[j]]=0;
				break;
			}
			Mu[i*Prime[j]]=-Mu[i];
		}
	}
	
	for(i=1;i*i<=n;i++)
	{
		if(n%i==0)
		{
			Yi[++num]=i;
			Yi[++num]=n/i;
		}
	}
	sort(Yi+1,Yi+1+num);
	num=unique(Yi+1,Yi+1+num)-Yi-1;
	for(i=1;i<=num;i++)
	{
		if(Yi[i]>c) break;
		for(j=i;j<=num;j++)
		{
			if(Yi[j]%Yi[i]==0)
			g[j]+=Mu[Yi[j]/Yi[i]];
		}
	}
	for(i=1;i<=num;i++)
	{
		for(j=Yi[i];j<=n;j+=Yi[i])
		F[j]+=g[i];
	}
	for(i=1;i<=n;i++) F[i]+=F[i-1];
}

char s[SIZE_BIG];
struct Big
{
	int a[SIZE_BIG],len;
	void Clear(){memset(a,0,sizeof(a));len=0;}
	void clear(){while(len>1 && a[len]==0) len--;}
	void read()
	{
		scanf("%s",s+1);
		len=strlen(s+1);
		for(int i=1;i<=len;i++)
		a[i]=(s[len-i+1]^48);
	}
	void write()
	{
		clear();
		for(int i=len;i>=1;i--)
		putchar(a[i]+48);
		putchar('\n');
	}
	int &operator [](int i){return a[i];}
	Big friend operator +(Big a,int b)
	{
		int i; a[1]+=b;
		for(i=1;i<=a.len;i++)
		{
			if(a[i]>=10)
			{
				a[i+1]+=a[i]/10;
				a[i]%=10;
				if(i==a.len)
				a.len++;
			}
		}
        a.clear();
		return a;
	}
	Big friend operator -(Big a,int b)
	{
		int i; a[1]-=b;
		for(i=1;i<=a.len;i++)
		{
			if(a[i]<0)
			{
				a[i]+=10;
				a[i+1]--;
			}
		}
		a.clear();
		return a;
	}
	Big friend operator -(Big a,Big b)
	{
		int i;
		for(i=b.len;i>=1;i--) a[i]-=b[i];
		for(i=1;i<=a.len;i++)
		{
			if(a[i]<0)
			{
				a[i]+=10;
				a[i+1]--;
			}
		}
		a.clear();
		return a;
	}
	Big friend operator *(Big a,int b)
	{
		int i;
		for(i=1;i<=a.len;i++) a[i]*=b;
		for(i=1;i<=a.len;i++)
		{
			if(a[i]>=10)
			{
				a[i+1]+=a[i]/10;
				a[i]%=10;
				if(i==a.len)
				a.len++;
			}
		}
		return a;
	}
	Big friend operator /(Big a,int b)
	{
		int i,x=0;
		for(i=a.len;i>=1;i--)
		{
			x=x*10+a[i];
			a[i]=x/b;
			x%=b;
		}
        a.clear();
		return a;
	}
	int friend operator %(Big a,int b)
	{
		int i,x=0;
		for(i=a.len;i>=1;i--)
		{
			x=x*10+a[i];
			a[i]=x/b;
			x%=b;
		}
		return x;
	}
}f,ans,L,R,Ans;
signed main()
{
	int i,kkk=0;
	n=read(),c=read(); init();
	f.read(); ans=f/F[n]*n; kkk=f%F[n];
	if(kkk==0)
	{
		ans=ans-n;
		for(i=n;i>=1;i--)
		{
			if(F[i]!=F[n])
			{
				ans=ans+(i+1);
				break;
			}
		}
	}
	else
	{
		for(i=0;i<n;i++)
		{
			if(kkk==F[i])
			{
				ans=ans+i;
				break;
			}
		}
	}
	ans.write(); ans.Clear();
	f.read(); f=f-1; kkk=f%n;
	ans=f/n*F[n]+F[kkk];
	f.Clear(); f.read(); kkk=f%n;
	Ans=f/n*F[n]+F[kkk];
	ans=Ans-ans; ans.write();
	return 0;
}
```

---

