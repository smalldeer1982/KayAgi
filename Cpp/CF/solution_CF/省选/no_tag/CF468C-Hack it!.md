# Hack it!

## 题目描述

小 X 最近遇到了下面的问题。

我们定义函数 $f(x)$ 为 $x$ 的各个数位之和。比如说，$f(1234)=1+2+3+4=10$。任务是，计算 $\sum_{i=l}^rf(i)\operatorname{mod} a$ 的值。

小 X 很快就解决了这个问题。于是小X锁定了这道题，然后开始 hack 别人。他看到了下面这段代码：

```cpp
ans = solve(l, r) % a;
if (ans <= 0) ans += a;
```

显而易见地，这段代码会在 $\sum_{i=l}^rf(i)\equiv 0 \pmod a$ 时输出错误。小 X 会告诉你题目中的 $a$ 是多少，现在请你为小 X 构造一个 hack 数据。

## 样例 #1

### 输入

```
46
```

### 输出

```
1 10
```

## 样例 #2

### 输入

```
126444381000032
```

### 输出

```
2333333 2333333333333
```

# 题解

## 作者：da32s1da (赞：85)

思考过程极为巧妙。

我们首先考虑一个数字$x$，若$f(x)=y$，则$f(x+10^{18})=f(x)+1=y+1.$ 这是很显然的事情。

我们设$\sum_{i=0}^{10^{18}-1}f(i)\equiv p ~(\!\!\mod\! a~)$，则

$\sum_{i=1}^{10^{18}}f(i).$

$=f(10^{18}+0)+\sum_{i=1}^{10^{18}-1}f(i).$

$=1+f(0)+\sum_{i=1}^{10^{18}-1}f(i).$

$=1+\sum_{i=0}^{10^{18}-1}f(i)\equiv p+1 ~(\!\!\mod\! a~).$

同样，我们可以推出

$\sum_{i=2}^{10^{18}+1}f(i)\equiv p+2 ~(\!\!\mod\! a~).$

$\sum_{i=3}^{10^{18}+2}f(i)\equiv p+3 ~(\!\!\mod\! a~).$

$....$

$\sum_{i=r}^{10^{18}+r-1}f(i)\equiv p+r ~(\!\!\mod\! a~).$

$....$

$\sum_{i=a-p}^{10^{18}+a-p-1}f(i)\equiv p+a-p ~(\!\!\mod\! a~).$

即$\sum_{i=a-p}^{10^{18}+a-p-1}f(i)\equiv 0 ~(\!\!\mod\! a~).$

所以$l=a-p,r=10^{18}+a-p-1$时，满足条件。

可见，我们主要的事情是求出$p$，即$\sum_{i=0}^{10^{18}-1}f(i).$

注意到
$\sum_{i=0}^{10^{18}-1}f(i)$

$=45\times 10^{17}+10\times \sum_{i=0}^{10^{17}-1}f(i)$

$=45\times 10^{17}+10\times (45\times 10^{16})+100\times \sum_{i=0}^{10^{16}-1}f(i)$

$=....$

$=18\times 45\times 10^{17}$

$=81\times 10^{18}.$

即$p=81\times 10^{18} \!\mod a.$

于是就可以愉快的$AC$掉本题啦！
```
#include<cstdio>
typedef long long LL;
LL l,r,inf=1e18,mod;
int main(){
    scanf("%lld",&mod);
    l=mod-inf%mod*9%mod*9%mod;
    r=l+inf-1;
    printf("%lld %lld\n",l,r);
}
```

---

## 作者：Nemlit (赞：16)

构造题果然都非常神仙啊

~~首先翻译有点问题，$L, R$的范围应该为$[1, 10^{200}]$~~

由于模数a达到了$10^{18}$，所以我们可以发现，当$i<10^{18}$时，$f()$有一个性质：

$$ f(i+10^{18}) = f(i)+1$$

我们令$g=\sum_{i=1}^{10^{18}}f(i)\ (mod\ a)$

于是我们有：$g+1=\sum_{i=2}^{10^{18}+1}f(i)\ (mod\ a)$

$g+a-g=\sum_{i=a-g+1}^{10^{18}+a-g}f(i)\ (mod\ a)=0\ (mod\ a)$

所以我们可以构造出一组解为$[a-g, 10^{18}+a-g+1]$

于是我们现在问题就变成了求出$g$

$g=\sum_{i=1}^{10^{18}-1}f(i)+1$

对于$10^{18}-1$的所有数位出现次数都是一样长的

所以答案应该为$45*$每一个数位出现多少次

这个东西就可以用~~数位DP~~组合数来求了：我们把原问题想象成：有18个空位，你可以放$[0, 9]$中的所有数，问$i$放了多少次

$$ans=\sum_{i=1}^{18}C_{18}^i*9^{18-i}$$
然后用$__int128$跑一下，答案为$45*18*10^{17}+1=81*10^{18}+1$

## $Code:$
```
#include<bits/stdc++.h>
using namespace std;
long long a, pax = 1e18 + 1;
signed main() {
	cin >> a;
	long long l = a - pax % a * 9 % a * 9 % a, r = pax + l - 1;
	printf("%lld %lld", l, r);
	return 0;
}
```

---

## 作者：konyakest (赞：10)

首先，一般的 $\sum_{i=l}^rf(i)$ 是没有什么性质的，所以我们需要想一想什么样的 $l,r$ 有性质。

我们不难想到两两配对：$f(10^x-1)+f(10^x)=f(10^x-2)+f(10^x+1)=\dots=9x+1$。

证明是显然的，因为它们末几位刚还是一个“配对”的关系，所以刚好可以配凑起来。

于是我们有以下构造：取 $x\ge19$，则 

$$
\begin{aligned}
\displaystyle \sum_{i=10^x-a}^{10^x+a-1}f(i)&=\sum_{i=1}^af(10^x-a)+f(10^x+a-1)\\&=\sum_{i=1}^a9x+1\\&=(9x+1)a\\&\equiv0\pmod a
\end{aligned}
$$

代码：（可能是最短解？）

```python
a=int(input())
print(10**50-a,10**50+a-1)
```

---

## 作者：yzy1 (赞：7)

构造个锤头，为啥不直接退火．

我们设函数 $F(n)$ 为 $f(n)$ 的前缀和对 $a$ 取模，即

$$
F(n) = (\sum_{i=1}^n f(i)) \bmod a.
$$

题意转化为，找到整数对 $(i,j)$ 满足 $i \ne j$ 且 $F(i) = F(j)$．

观察到这个 $F$ 的图像就很像若干段从零上升到 $a$ 然后再突变为 $0$ 的曲线．

我们发现这个 $F$ 有地方会突变为零，性质不是很好，考虑设 $g(i) = |F(i) - \lfloor a/2 \rfloor|$．这个 $g$ 的图像就会变成一堆 W 形收尾拼接起来．我们固定 $i,j$ 都在 $g$ 的极小值处取得．注意到由于 $f(i)$ 的值是 $O(\log i)$ 级别的，也就是说，$g(i)$ 的局部最小值只会取到 $[0, O(\log a)]$ 范围．根据抽屉原理，$g$ 的极小值只有 $O(\log a)$ 种不同的取值．考虑不断跑模拟退火求出这个函数的随机一个极小值点，然后判断这个位置 $F$ 的取值是否和之前跑到过的位置相等．

尝试分析这个做法的时间复杂度．首先显然可以使用数位 dp 或者直接计算每一位贡献等方式，以 $O(\log i)$ 的时间复杂度单点求 $g(i)$．又由于 $g$ 函数在极小值处附近的上升下降的趋势明显，模拟退火在求这种函数的极值时非常高效，几乎可以看作三分，因为我们认为模拟退火的复杂度为 $O(\log a)$．再算上模拟退火最多跑 $O(\log a)$ 次，最终的的时间复杂度为 $O((\log a)^3)$．实际上远远跑不到这个上界．

代码参考见 [原始 OJ 提交](https://codeforces.com/contest/468/submission/224568660)．


---

## 作者：Soulist (赞：7)

首先有一个性质，对于$1\le x< 10^{18}$有$f(x+10^{18})=f(x)+1$

可以注意到：

$$\sum_{i=1}^{10^{18}-1}f(i)=x(~mod~~a~ )$$

于是就有：

$$\sum_{i=1}^{10^{18}}f(i)=\sum_{i=1}^{10^{18-1}}+f(0+10^{18})-f(0)=x+1(~~mod~~a ~~)$$

同样也可以得到：

$$\sum_{i=t}^{10^{18}-1+t}f(i)=x+t(~mod~~a~)$$

假设 $x=0$，那么直接输出 $1$ 和 $10^{18}-1$

否则可以想到 $t=a-x$

然后直接输出 $l=t$ 和 $r=10^{18}-1+t$ 即可

于是问题的关键就在于$\sum_{i=0}^{10^{18}-1}f(i)$是多少了

下面给出简略证明

可以发现每一个数位贡献的次数是固定的，可以考虑将$10^{18}-1$看作是$18$个格子，然后放入一些数字，求所有方案放入的数字和

于是可以枚举一个数$0\le x\le 9$来计算其贡献次数

可以考虑其恰好出现 $i$ 次时的答案，那么可以枚举$i$个位置选入这个数$x$，然后接下来$18-i$个位置都可以放入除了$x$之外的所有数，所以有其贡献次数为：

$$i\times \dbinom{i}{18}\times 9^{18-i}$$

所以答案就是：

$$\sum_{x=0}^9x\times \sum_{i=0}^{18}i\times \dbinom{i}{18}\times 9^{18-i}$$

$$45\times \sum_{i=0}^{18}i\times \dbinom{i}{18}\times 9^{18-i}$$

$$45\times \sum_{i=0}^{18}i\times \dfrac{18!}{i!(18-i)!}\times 9^{18-i}$$

$$45\times \sum_{i=1}^{18} \dfrac{18\times 17!}{(i-1)!((18-1)-(i-1))!}\times 9^{(18-1)-(i-1)}$$

$$18\times45\times \sum_{i=0}^{17} \dfrac{17!}{i!(17-i)!}\times 9^{17-i}$$

$$18\times45\times \sum_{i=0}^{17} \dbinom{17-i}{17} 9^{17-i}$$

$$18\times45\times10^{17}$$

$$9\times 9\times 10^{18}$$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
int P = 1e18, l, r ;
signed main()
{
	int A = gi() ; 
	l = A - ( ( P % A ) * 9 % A * 9 ) % A, r = l + P - 1 ;
	printf("%lld %lld", l, r ) ;
	return 0 ;
}
```

qwq

---

## 作者：qwaszx (赞：6)

这里有一个莫名其妙的我也不知道为什么复杂度对的做法.

考虑先钦定左端点为 $1$ ，然后跑一个最大的右端点 $r$ 满足 $[1,r]$ 的 $f$ 的和小于等于 $a$

然后暴力双指针移动区间直到和等于 $a$.

找右端点的过程是简单的数位 $dp$ ，预处理出后 $i$ 位随便填的数位和，然后从高位到低位枚举每一位填什么.

复杂度根据某个人的原话是 $f$ 很小所以指针移动次数不会太多，但我也不知道为什么一定能很快凑出来

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
long long a;
long long f[100],pw[100];
int calc(long long x){return x?calc(x/10)+x%10:0;}
long long find(long long t)
{
	long long s=0,w=0;int pres=0;
	for(int i=15;i>=1;i--)
	{
		for(int x=0;x<=9;x++)
			if(t>s+f[i-1]+(pres+x)*pw[i-1])s+=f[i-1]+(pres+x)*pw[i-1];
			else
			{
				pres+=x;w+=x*pw[i-1];break;
			}
	}
	if(s+pres==t)return w;
	else return s;
}
void solve()
{
	pw[0]=1;for(int i=1;i<=18;i++)pw[i]=pw[i-1]*10;
	f[0]=0;for(int i=1;i<=18;i++)f[i]=pw[i-1]*i*45;
	long long s=0,w=0;int pres=0;
	for(int i=17;i>=1;i--)
	{
		for(int x=0;x<=9;x++)
			if(a>s+f[i-1]+(pres+x)*pw[i-1])s+=f[i-1]+(pres+x)*pw[i-1];
			else
			{
				pres+=x;w+=x*pw[i-1];break;
			}
	}
	if(s+pres==a){cout<<1<<" "<<w<<endl;return;}
	long long r=w-1,l=1;
	for(;s!=a;)
	{
		s-=calc(l);l++;
		while(s+calc(r+1)<=a)++r,s+=calc(r);
	}
	cout<<l<<" "<<r<<endl;
}
int main()
{
	scanf("%lld",&a);
	solve();
	return 0;
}

```

---

## 作者：雅儿贝德 (赞：6)

这是道紫色的构（da）造（du）题（liu）

不过我都能get到的想必也不是啥难题

[题目链接](https://www.luogu.org/problemnew/show/CF468C)

看完题目先去看$a$的取值范围

嗯?$10^{18}$?什么数字位数和会大于等于$10^{18}$?

再看看$l,r$的取值范围顿时明白

**$r$的取值一定大于$10^{18}$**

先不管$l$,先利用**前缀和思想**

设$g(x)=f(1)+f(2)+f(3)+...+f(x)$

则$g(r)=f(1)+f(2)+f(3)+...+f(10^{18})+...$

暂时不知道右边要加到哪里，先放着

则$g(10^{18})=f(1)+f(2)+f(3)+...+f(10^{18})$

设$g(10^{18})\equiv b(mod \; a)$

**注意$a$和$b$是唯一确定的可以求的**

则$g(r)\equiv b+...(mod\; a)$

这有个$b$!

很显然我们**要消去$b$**

再引申出一个很显然的推论

$f(x+10^{18})=f(x)+1(x<=10^{18})$

所以

$g(r)=f(1)+f(2)+...+f(10^{18})+f(10^{18}+1)+...+f(10^{18}+a-b)$

$g(r)=b+1*(a-b)+f(1)+f(2)+f(3)+f(a-b)$

$g(r)=a+g(a-b)$

如此**消去了$b$**

这又有个$g(a-b)$,只有把它消去我们才能使$g(r)$在模$a$意义下为$0$

回到题目要求的是一个区间，**用$g(l-1)=g(a-b)$**，就能使这段区间之和模$a$意义下为$0$

总结一下

$g(l-1)=g(a-b)$

$g(r)=g(10^{18}+a-b)$

则

$l=a-b+1$

$r=10^{18}+a-b$

如此构造出了答案

什么你问我$b$怎么求？

~~随缘填坑（因为我现在在上课）~~

我来填坑了！

从小往大先用$for$循环枚举大法推一波规律

$1-9$的和为$45=45*1$

$1-99$的和为$900=45*20$

$1-999$的和为$13500=45*300$

$1-9999$的和为$180000=45*4000$

豁然开朗！

$g(10^t-1)=45*t*10^{t-1}$

$g(10^t)=45*t*10^{t-1}+1$

如此可以简便算出$g(10^{18})=45*18*10^{17}+1=81*10^{18}+1$

至于证明。。。

我感性思考一下:

首位每个数字会出现$t$次

其他位置都有$10$种可能一共$10^{t-1}$个可能

且$0-9$数字的和为$45$

附：我的blog书写次序是按我的理解思路来的，如果有逻辑混乱的地方，恳请指正

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

LL a,inf=1e18;

int main()
{
    cin>>a;
    LL b;
    b=(inf%a*9%a*9%a+1%a)%a;//拆成9*9是害怕爆炸
    LL l=a-b+1,r=1e18+a-b;
    //cout<<b<<endl;
    cout<<l<<" "<<r;
    return 0;
} 
```


---

## 作者：Fading (赞：2)

给一个 $\log^3$ 的垃圾题解，正解太 nb 了，我人都看傻了...

考虑暴力。首先 $l,r$ 是 $\leq10^{200}$，因此 $f_i$ 与 $f_{i-1}$ 之间相差不到 $1800$ ，于是我们拿出 $\bmod \leq1800$ 的位置考虑。这样经过 $i\in[mj,m(j+1)]$ 一轮下来至少会填上 $1800$ 中的一位。

所以我们发现暴力做最多 $1800$ 轮，而且有一个很有趣的事情就是常数根本跑不满，第一轮就可以填上很多数字而且如果相同直接输出就完事了。

然后怎么找呢？观察地再仔细一点你就可以发现更好玩的事情：$r$ 根本取不到 $10^{200}$ 次。$r$ 可以放缩到 $10^{18}\times\alpha($ 这个指 $f_i$ 与 $f_{i-1}$ 之间最大差值 $)$。再放缩可以得到这样一个上界：$2\times 10^{20}$。

这个数很小，我们可以二分+数位 dp 找到下一轮的初始位置，然后暴 力 填 充，最多 $200$ 轮。时间复杂度（不严谨）$O(w^2\log^3n)$。$w$ 指进制。

发现需要__int128，结果我兴冲冲写完交上去 CE 了，...~~垃圾CF~~

再仔细看看，一次加 $200$ 完全是满的，而且一轮到后面根本就不需要 $m$ 次。我们不妨设 $\beta$ 表示一轮平均有多少个数，$\alpha$ 表示 $f_i$ 与 $f_{i-1}$ 之间差值的平均值。

上界变成了 $\alpha\beta=m$ ，再加上不可能做满，前两轮都可以清掉很多数，于是我们把上界摸到 $10^{17}$ ，皆大欢喜。

最大的点 31ms...

代码不贴了。


---

## 作者：Aiopr_2378 (赞：1)

# Solution CF468C Hack it!

一道非常神的构造题。

~~不是数学题吗~~

根据题目，我们可以知道 $f(x)$ 表示 $x$ 的各个数位之和。

我们设 $\sum_{i=0}^{10^{18}-1} f(i)\equiv p\pmod{a}$ .

那么不难得出： $\sum_{i=1}^{10^{18}} f(i)\equiv p+1\pmod{a}$ .

在举例： $\sum_{i=2}^{10^{18}+1} f(i)\equiv p+2\pmod{a}$ .

故： $\sum_{i=a-p}^{10^{18}+a-p-1} f(i)\equiv p+a-p\pmod{a}$ .

所以， $l=a-p$ ，且 $r=10^{18}+a-p-1$ 时符合题意。

那么，我们只要求出 $\sum_{i=0}^{10^{18}-1} f(i)$ 即可知道答案。

进而，式 $\sum_{i=0}^{10^{18}-1} f(i)$ 

 $=10^{17}\times 45 +\sum_{i=0}^{10^{17}-1} f(i)$ 
 
 $=81\times10^{18}$ 
 
 即， $p=81\times10^{18} \bmod{a}$ 
 
###  AC！

参考代码：

```cpp
#include<iostream>//短小精悍的代码
using namespace std;
long long l,r,mod,inf=1e18;
int main(){
	cin>>mod;
	l=mod-inf%mod*9%mod*9%mod;//这里不能直接*81，会爆long long
	r=l+inf-1;
	cout<<l<<" "<<r;
    return 0;
}
```

谢谢观看

---

## 作者：Jayun (赞：1)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/CF468C)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14539563.html)

# 题目大意:

设 $f(x)$ 表示 $x$ 的各个数位之和。

给定一个正整数 $a$，请您找到 $l,r$ 满足 $\sum\limits_{i=l}^r f(i)\equiv0\pmod{a}$。

$1\leq l,r\leq 10^{200}$，$1\leq a\leq10^{18}$。

# 正文：

是道神仙题。首先有一个显而易见的性质：当 $f(x)=x$ 时，$f(x+10^{18})=x+1$（这里加上 $10^{18}$ 是因为这是 $a$ 的上界）。

那么当 $\sum\limits_{i=0}^{10^{18}-1}f(i)\equiv x\pmod{a}$，则有：

$$\sum\limits_{i=1}^{10^{18}}f(i)\equiv x+1\pmod{a}$$

以此类推得到：

$$\sum\limits_{i=a-x}^{10^{18}-1+a-x}f(i)\equiv x+a-x\equiv 0\pmod{a}$$

所以我们可以得到一组 $[a-x,10^{18}-1+a-x]$ 的解。接下来的问题就可以转化到如何求 $\sum\limits_{i=0}^{10^{18}-1}f(i)$ 了。

--- 

然后根据初赛知识，这个玩意可以递归求得。

先设函数 $F(x)=\sum_{i=0}^{10^x-1}f(i)$，它可以这么递归：

$$F(x)=\left\{\begin{matrix}
45&(x=1)\\
45\times10^{x-1}+10F(x-1)&(x>1)
\end{matrix}\right.$$

然后就可以暴力实现了：

```cpp
ll qpow(ll a, int b)
{
	ll ans = 1;
	for (; b; a *= a, b >>= 1)
		if(b & 1) ans *= a;
	return ans;
}

ll F(int x)
{
	return x == 1? 45ll: 45ll * qpow(10, x - 1) + 10ll * F(x - 1);
}

int main()
{
	printf ("%lld\n", F(17));
	return 0;
}
```

这里直接算 $F(18)$ 会溢出，所以先算出 $F(17)=7.65\times10^{18}$，然后用电脑上自带的计算器得到 $F(18)=8.1\times 10^{19}$。于是便得到了答案。

# 代码：

```cpp
ll n, inf = 1e18;

int main()
{
	scanf ("%lld", &n);
	ll l = n - inf % n * 9 % n * 9 % n, r = inf + l - 1; //注意这里直接乘81会溢出，所以乘两遍9。
	printf ("%lld %lld\n", l, r);
	return 0;
}
```

---

## 作者：sipu6174 (赞：1)

来一发另类的构造方法。

对于$f(x)$有一个性质：

$$ f(i+10^{k}) = f(i)+1  (k>0)$$

由此式子可得另一个推广性质：

$$\sum_{i=x+1}^{x+10^k}f(i)= \sum_{i=1}^{10^k}f(i)+x(x<10^k)$$

我们可以把两边都有的那些f(i)减去，那么我们就可以发现两边剩余的分别是

$1+10^k$和$1$

$2+10^k$和$2$

......

$x+10^k$和$x$

根据第一个性质，左边的每一项的函数值都比右边对应项的函数值大$1$，总共加起来就大了$x$。

**你只需要性质二就可以做题了。**

1. 首先通过数位dp求出1e0~1e19以内的数字之和，具体方法见[P2602](https://www.luogu.com.cn/problem/P2602).

2. 只要我们当前的这个10的幂次的前缀和的答案加上一个小于当前幂次的数模a能变成0，那么我们就可以构造出一个答案。

3. 注意处理前缀和时要取模，~~如果你要使用__int128，务必记得开C++11.~~

```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
ll a,b,k,ans;
ll ten[30]={1},f[30];
ll cnt[30];
ll mi[30];
ll solve(ll x)
{
    memset(cnt,0,sizeof cnt);
    ll num[30]={0},sum=0;
    int len=0;
    while(x)
    {
        num[++len]=x%10;
        x=x/10;
    }
    for(int i=len;i>=1;i--)
    {
        for(int j=0;j<=9;j++)
        cnt[j]+=f[i-1]*num[i];
        for(int j=0;j<num[i];j++)
        cnt[j]+=ten[i-1];
        ll num2=0;
        for(int j=i-1;j>=1;j--)
        {
            num2=num2*10+num[j];
        }
        cnt[num[i]]+=num2+1;
        cnt[0]-=ten[i-1];
    }
    for(int i=1;i<=9;i++) sum=(sum+i*cnt[i])%k;
    return sum;
}
int main()
{
    scanf("%llu",&k);
    for(int i=1;i<=19;i++)
    {
        f[i]=f[i-1]*10+ten[i-1];
        ten[i]=10*ten[i-1];
    }
    for(int i=0;i<=19;i++)
        mi[i]=solve(ten[i]);
    for(int i=0;i<=19;i++)
        if(k-mi[i]%k<ten[i])
        {
            a=k-mi[i]%k+1;
            b=a+ten[i]-1;
            break;
        }
    printf("%llu %llu",a,b);
    return 0;
}
```





---

## 作者：mango09 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF468C)

[更好的观赏体验](https://www.luogu.com.cn/blog/305532/post-ti-xie-cf468c)

------------

**前言**

这真的是我见过的代码最短的紫题了！

**但是**正解并不好想，构造过程很奇特。


------------

**下面进入主题**

我们设 $f(n)$ 表示自然数 $n$ 的数字和。

不难发现，当 $n\le10^{18}$ 时有一个性质：

$\boxed{f(n + 10^{18})=f(n)+1}$

设 $\sum_{i=1}^{10^{18}}f(i)=k$

则:

$\sum_{i=2}^{10^{18}+1}f(i)=f(10^{18}+1)-f(1)+\sum_{i=1}^{10^{18}}f(i)=f(10^{18})+f(1)-f(1)+\sum_{i=1}^{10^{18}}f(i)=1+\sum_{i=1}^{10^{18}}f(i)\equiv k+1\pmod{a}$

同理可得

$\sum_{i=3}^{10^{18}+2}f(i)\equiv k+2\pmod{a}$

$……$

$\sum_{i=l}^{10^{18}+l-1}f(i)\equiv k+l\pmod{a}$

可以构造出：

$\sum_{i=a-k}^{10^{18}+a-k-1}f(i)\equiv k+(a-k)\equiv0\pmod{a}$

所以可以构造出一组解：$l=a-k,r=10^{18}+a-k-1$

于是问题就转化成求出 $k$。

$k=\sum_{i=1}^{10^{18}}f(i)=45\times10^{17}+10\sum_{i=1}^{10^{17}}f(i)=45\times10^{17}+10\times(45\times10^{16})+10^2\sum_{i=1}^{10^{16}}f(i)=……=(18\times45)\times10^{17}=81\times10^{18}$

综上，$p\equiv81\times10^{18}\pmod{a}$

**温馨提示：记得开 long long！**

**代码**

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;

int a, x = 1e18, l, r;

signed main()
{
	scanf("%lld", &a);
	l = a - x % a * 9 % a * 9 % a;
	r = x + l - 1;
	printf("%lld %lld", l, r);
	return 0;
}
```

然后你测样例就会发现 WA 了

？？？

不要急，直接交就会发现 AC 了（应该是 spj 吧）。

---

## 作者：suxxsfe (赞：0)

http://codeforces.com/problemset/problem/468/C  
设 $f(x)$ 为 $x$ 的十进制下各个位上数字之和，给定 $a(a\le 10^{18})$，求 $l,r(l\le r\le 10^{200})$，使得：  

$$\sum_{i=l}^{r} f(i)\equiv 0 \pmod a$$  

-----------------  

这题是真的真的真的妙哇  

设 $inf=10^{18}$，也就是 $a$ 的最大值  
显然有：$f(i+10^x)=f(i)+1,10^x>i$  
设一个 $p$，使得 $\sum_{i=0}^{inf-1}f(i)\equiv p \pmod a$  
那么根据上面那个式子，可以知道 $\sum_{i=1}^{inf}f(i)\equiv p-f(0)+f(0+inf)\equiv p+1\pmod a$  
不断通过这种变换，就可以得到：  

$$\sum_{i=k}^{inf+k-1}\equiv p+k\pmod a$$  

当 $k=a-p$ 时，有：  

$$\sum_{i=a-p}^{inf+a-p-1}\equiv 0\pmod a$$  

则 $l=a-p,r=inf+a-p+1$ 即为一组解  

那么剩下的问题就是求出 $p$，考虑最高位，也就是第 $18$ 位，它取一到九之间的任意一个数，分别存在 $10^{17}$ 种方案，那么这一位对答案的贡献就是 $45\times 10^{17}$  
在考虑剩下的 $17$ 位，就是一共 $10$ 个 $\sum_{i=0}^{10^{17}-1}f(i)$，这样就有了一个比较像递归的解决方法：  

$$\sum_{i=0}^{10^{18}-1}f(i)$$  

$$45\times 10^{17}+10\sum_{i=0}^{10^{17}-1}f(i)$$  

$$45\times 10^{17}+450\times 10^{16}+100\sum_{i=0}^{10^{16}-1}f(i)$$  

$$\cdots$$  

最终结果：  

$$45\times 18\times10^{17}=81\cdot inf$$  

于是就做完了（（  
但是注意处理 $r$ 的时候，用 $inf+l-1$ 来算，不能取膜，否则可能造成 $l>r$ 的情况  
另外不能直接乘 $81$，乘两个 $9$ 来代替，否则爆 long long  

```cpp  
#include<cstdio>
int main(){
	long long a,inf=1e18;
	scanf("%lld",&a);
	long long l=a-(inf%a*9%a*9%a);//防止溢出，有个点就卡这个
	long long r=l+inf-1;
	printf("%lld %lld",l,r);
}
```

---

