# [ABC154F] Many Many Paths

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc154/tasks/abc154_f

$ 2 $ 次元平面があります。この平面上に立っているすぬけ君は、一回の操作で $ x $ 軸正の方向に $ 1 $ もしくは $ y $ 軸正の方向に $ 1 $ 移動することができます。

また、以下のように関数 $ f(r,c) $ を定義します。

- $ f(r,c)\ := $ (すぬけ君が点 $ (0,0) $ から点 $ (r,c) $ まで上記の操作を繰り返して到達する経路の個数)

整数 $ r_1,\ r_2,\ c_1,\ c_2 $ が与えられます。 $ r_1\ <\ =\ i\ <\ =\ r_2 $ かつ $ c_1\ <\ =\ j\ <\ =\ c_2 $ を満たす全ての整数の組 $ (i,j) $ に対する $ f(i,j) $ の 総和を求め、 $ (10^9+7) $ で割った余りを計算してください。

## 说明/提示

### 制約

- $ 1\ <\ =\ r_1\ <\ =\ r_2\ <\ =\ 10^6 $
- $ 1\ <\ =\ c_1\ <\ =\ c_2\ <\ =\ 10^6 $
- 入力はすべて整数

### Sample Explanation 1

例えば、点 $ (0,0) $ から点 $ (1,1) $ までの経路は、$ (0,0) $ → $ (0,1) $ → $ (1,1) $ と $ (0,0) $ → $ (1,0) $ → $ (1,1) $ の $ 2 $ 通りあるので、 $ f(1,1)=2 $ です。 同様に、$ f(1,2)=3 $, $ f(2,1)=3 $, $ f(2,2)=6 $ なので、求める総和は $ 14 $ です。

## 样例 #1

### 输入

```
1 1 2 2```

### 输出

```
14```

## 样例 #2

### 输入

```
314 159 2653 589```

### 输出

```
602215194```

# 题解

## 作者：w33z8kqrqk8zzzx33 (赞：10)

组合题。。

先转换查询乘4个二维前缀查询，独立计算。

第一个观察是 $f(r,c)=\binom{r+c}{c}$，应为到达 $(r,c)$ 的路径和一个有 $r$ 个 `U` 和 $c$ 个 `L` 有一一对应（假如一个 `U` 就是往上走，一个 `L` 就是往左走）。

第二个观察是到 $(r,0),(r,2),\dots,(r,C)$ 的路径和到 $(r+1,C)$ 的路径有一一对应：到达 $(r,c)$ 以后，走到 $(r+1,c)$ 然后一直往上到 $(r+1,C)$；这样构造的每一个路径都互不相同。

在重复用一下这个观察，得到 $f(1,C)+f(2,C)+\dots+f(R+1,C)=f(R+1,C+1)-1$，这就是对一个二维前缀和的答案。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

int fac[2000006], inv[2000006], invfac[2000006];

int calc(int r, int c) {
    // -1 + r+c+2 choose r+1
    return ((1ll * fac[r+c+2] * invfac[r+1] % MOD * invfac[c+1] % MOD) + MOD - 1) % MOD;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
    fac[0] = 1; invfac[0] = 1;
    inv[0] = 1; inv[1] = 1;
    rep1(i, r2+c2+2) {
        if(i != 1) inv[i] = 1ll * inv[MOD % i] * (MOD - MOD/i) % MOD;
        fac[i] = 1ll * fac[i-1] * i % MOD;
        invfac[i] = 1ll * invfac[i-1] * inv[i] % MOD;
    }
    cout << (4ll*MOD + calc(r2, c2) - calc(r1-1, c2) - calc(r2, c1-1) + calc(r1-1, c1-1)) % MOD << endl;
}


```

---

## 作者：Minecraft万岁 (赞：10)

第一篇~~题解~~，希望能过吧  
闲话少叙，进入~~正题~~  
看一下这个棘手的 $f(r,c) $
 ~~显然~~，需要化成直观的数学柿子   
考虑从 $(0,0)$ 走到 $(r,c) $一共走了 $r+c$ 步 我们只要在这几步中确定 $r$ 步向上 **或** $c$ 步向右 在 $r+c$ 中的不同摆放位置 那么就确定不同的走法 则有:  
$$f(r,c)=C^r_{r+c}=C^c_{r+c}$$  
到这里 这个~~可怕的~~函数变为了组合数  
分割线下正式推柿子！

------------
替换函数得到 
 $$\sum\limits_{i=r1}^{r2}{\sum\limits_{j=c1}^{c2} C^i_{i+j} }$$   

**前置知识**  $\sum\limits_{i=0}^m{C^n_{n+i}}={C^{n+1}_{n+m+1}}$ ~~很重要~~      

观察刚刚替换函数的柿子  
$$\sum\limits_{i=r1}^{r2}{\sum\limits_{j=c1}^{c2} C^i_{i+j} }$$ 
找不到符合上面~~结论~~的部分   
#### ~~~~怕什么~~ 拆一拆~~  
得到  
$$\sum\limits_{i=r1}^{r2}{\left(\sum\limits_{j=0}^{c2} C^i_{i+j}-\sum\limits_{j=0}^{c1-1} C^i_{i+j}\right) }$$ 

一拆为二 同时压缩两个求和变为两个组合数 ~~太妙了~~ 得到  
$$\sum\limits_{i=r1}^{r2}{\left({{C^{i+1}_{i+c2+1}}-{C^{i+1}_{i+c1-1+1}}}\right) }$$  
这个 $+1-1$ 抵消了 ~~写出来看的清楚点~~ 
最后化简
$$\sum\limits_{i=r1}^{r2}{\left({{C^{i+1}_{i+c2+1}}-{C^{i+1}_{i+c1}}}\right) }$$    


------------
~~呼的一口气~~ 但是这个组合数怎么~~快速的~~求呢   
我们可以想到~~暴力~~卢卡斯定理   
看起来可以~~过的样子~~ 
贴上代码 
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll mod=1000000007;
ll r1,r2,c1,c2;
ll ans;
inline void read(ll &x)//快读
{
	ll f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
//卢卡斯定理模板
inline ll qpow(ll a,ll b)
{
	ll rest=1;
	while(b)
	{
		if(b&1) rest=(rest*a)%mod;
		b>>=1;
		a=(a*a)%mod;
	}
	return rest;
}
inline ll C(ll n,ll m) 
{
    if(n<m) return 0;
    if(m>n-m) m=n-m;
    ll s1=1,s2=1;
    for(ll i=0;i<m;++i) 
	{
        s1=(s1*(n-i))%mod;
        s2=(s2*(i+1))%mod;
    }
    return s1*qpow(s2,mod-2)%mod;
}
inline ll lucas(ll n,ll m)
{
	if(m==0) return 1;
	else return (C(n%mod,m%mod)*lucas(n/mod,m/mod))%mod;
}
//模板到此为止
int main()
{
	read(r1);read(c1);read(r2);read(c2);
	for(ll i=r1;i<=r2;i++)
	{
		ans=(ans+(lucas(i+c2+1,i+1)-lucas(i+c1,i+1))%mod)%mod;//推出的公式
	}
	printf("%lld\n",ans);//输出答案
	return 0;
}

```


看看结果 [评测结果](www.luogu.com.cn/record/30518749)  
#### 超时了 ~~显然~~ 不够快  
~~肿么办~~ 看看什么地方时间用的比较多  
这个利用费马小定理的快速幂求逆元~~好像~~有点慢  
那就用线性求逆元吧  
给个博客我就是看这个学卢卡斯定理的 [一个大佬的博客](blog.csdn.net/nhl19961226/article/details/79663924)    
这可以大大降低计算次数 
给出我丑丑的代码 
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll mod=1000000007;//取模数 
ll r1,r2,c1,c2; 
ll ans;//最后的答案存在这里 
ll n; 
ll fac[2000005],inv[2000005];//阶乘与线性求解逆元的数组 
inline void read(ll &x)//快读 
{
	ll f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline ll qpow(ll a,ll b)//还是要快速幂 
{
	ll rest=1;
	while(b)
	{
		if(b&1) rest=(rest*a)%mod;
		b>>=1;
		a=(a*a)%mod;
	}
	return rest;
}
inline ll C(ll n,ll m)//这样算组合数快多了 
{
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
inline ll mx(ll _x,ll _y)//手写的max函数 感觉手写的快 
{
	return _x>_y?_x:_y;
}
int main()
{
	read(r1);read(c1);read(r2);read(c2);//读入数据 
	n=mx(r2,c2)*2+1;//看一下最大要算到哪里 不用一直算到 2000004
	fac[0]=1;//初始化 细节1 不然阶乘算出来全是0 
	for(ll i=1;i<=n;i++) 
		fac[i]=fac[i-1]*i%mod;//算阶乘 
	inv[n]=qpow(fac[n],mod-2);//愉快的线性求解每个数的逆元 
	for(ll i=n-1;i>=0;i--) 
		inv[i]=inv[i+1]*(i+1)%mod;//推一推 
	for(ll i=r1;i<=r2;i++)
	{
		ans=(ans+(C(i+c2+1,i+1)-C(i+c1,i+1))%mod)%mod;//依旧是之前的公式 
	}
	printf("%lld\n",(ans+mod)%mod);//这里注意一下 ans算出来可能为负数 需要特殊处理一下
	return 0;
}

```
  
### 其实理解最重要 理解了什么意思 写出来会~~容易很多~~

---

## 作者：Steadywelkin (赞：6)

### 题意

定义 $f(x,y)$ 表示在坐标轴上从 $(0,0)$ 到达 $(x,y)$ 的最短路径数量，给定 $x_1,y_1,x_2,y_2$ ，要求出：

$\begin{aligned}
\sum\limits_{x=x_1}^{x_2}
\sum\limits_{y=y_1}^{y_2}
f(i,j)
\end{aligned}$

### 思路

题目将答案范围限定在了一个离开坐标轴的矩形区块上，根据一般经验，考虑通过容斥将答案分离出来：

![](https://cdn.luogu.com.cn/upload/image_hosting/l9kjvqke.png)

如图，我们要得到 $[(x_1,y_1),(x_2,y_2)]$ 的答案，可以通过求出 

$
\begin{cases}
sum_1=[(0,0),(x_2,y_2)]\\
sum_2=[(0,0),(x_1-1,y_2)]\\
sum_3=[(0,0),(x_2,y_1-1)]\\
sum_4=[(0,0),(x_1-1,y_1-1)]
\end{cases}
$ 

的答案之后容斥得到（注意本题中是闭区间）

$ans=sum_1+sum_4-sum_2-sum_3$

现在我们将问题转化为了求出四个紧贴坐标轴的矩形对答案的贡献，这就是本题中最关键的地方。

本题中的 $f(x,y)$ 的本质上就是从 $(0,0)$ 到 $(x,y)$ 的路径上一共走了 $x+y$ 次，其中有 $x$ 次向右走的方案数，也就是 $C_{x+y}^{x}$

组合数的求值问题，最容易想到的就是杨辉三角，那么我们先从杨辉三角入手。

![](https://cdn.luogu.com.cn/upload/image_hosting/m47mqslb.png)

很容易发现，在上面这个正方形的范围之内，左下方的部分就是杨辉三角，但是右上角就只有部分的杨辉三角，我们无法保证直接通过杨辉三角求和（我们也无法保证可以一定是一个正方形），那么我们考虑进一步维护这个杨辉三角得到答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/p281y05i.png)

如图，我们要维护的是蓝色的部分，我们先将整个刚好包含所求区间的杨辉三角表现出来，那么我们可以通过求出整个杨辉三角的部分之后再减去绿色的部分，从而得到答案。

就下来就是考虑如何将绿色的部分对答案的影响消除，对于上面和下面的三角部分，一定有以下性质：

> 如果是上面的三角形，那么它必然会穿过 $y=b+1$ 这一行，如果是下面的三角形，那么它必然会穿过 $y=a+1$ 这一行（为了避免冲突，这里假设矩形右上方的坐标为 $(a,b)$）

我们考虑通过这个性质消除多余部分的影响：

只考虑上面的三角形部分，发现对于每一个点，它只能从下面或者左边转移得到。

由于在上方去重的部分不能有重复，我们只计入从 $y=b$ 转移上去的方案数。

同时发现上面多余的部分贡献恰好又是杨辉三角，那么就有（设多余部分为 $extra$，$s$ 表示杨辉三角总和）：

> $\begin{aligned}
extra=
\sum\limits_{i=0}^{x-1}
C_{b+i}^{i}s[a-i-1]+
\sum\limits_{i=0}^{y-1}
C_{a+1}^{i}s[b-i-1]
\end{aligned}$

通过这样的方式求得四块的贡献之后容斥即可

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#define int long long
using namespace std;
typedef long long ll;

inline int read()
{
	int a=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())
		if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())
		a=(a<<3)+(a<<1)+ch-'0';
	return a*f;
}

void write(int x)
{
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar((x%10)^48);
}

inline void writen(int x)
{write(x);puts("");}

const int mod=1e9+7;
const int N=2e6+5;
const int M=2e6;
const int INF=0x3f3f3f3f;
const double PI=acos(-1);

int fac[N],inv[N],s[N];
int a,b,c,d,ans,two[N];
//int check[100][100];

inline int qpow(int a,int n)
{
	int ans=1ll;
	for(;n;n>>=1,a=a*a%mod)
		if(n&1)ans=ans*a%mod;
	return ans;
}

void getfac(void)
{
	fac[0]=inv[0]=two[0]=s[0]=1;
	for(int i=1;i<=M;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		two[i]=two[i-1]*2%mod;
		s[i]=(two[i]*2-1)%mod;
	}
	inv[M]=qpow(fac[M],mod-2);
	for(int i=M-1;i>=1;i--)
		inv[i]=inv[i+1]*(i+1)%mod;
	return;
}

inline int calc(int n,int m){
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

inline int getans(int x,int y)
{
	int ans=s[x+y];
	for(int i=0;i<=x-1;i++)
		ans=(ans-(calc(y+i,i)*s[x-i-1]%mod))%mod;
	for(int i=0;i<=y-1;i++)
		ans=(ans-(calc(x+i,i)*s[y-i-1])%mod)%mod;
	return (ans+mod)%mod;
}

signed main()
{
	getfac();
  
	a=read();b=read();
	c=read();d=read();

	int sum1=(getans(c,d)+getans(a-1,b-1))%mod;
	int sum2=(getans(a-1,d)+getans(c,b-1))%mod;
	int ans=((sum1-sum2)%mod+mod)%mod;
	
	writen(ans);
	return 0;
}

```


---

## 作者：Super_Cube (赞：3)

# Solution

如果学过卡特兰的组合数通项公式，就很容易看出 $f(r,c)=\displaystyle\binom{r+c}{c}$。

原理：为了走到 $(r,c)$，一定走了共 $r+c$ 步，且有 $r$ 步是向右走的。

所以答案转化为：$\displaystyle\sum_{i=r_1}^{r_2}\sum_{j=c_1}^{c_2}\binom{i+j}{j}$。

直接计算复杂度为平方，需要优化。

搬出我们的组合恒等式：$\displaystyle\sum_{i=0}^n \binom{m+i}{i}=\binom{n+m+1}{n}$。

然后把前面的式子拆开：$\displaystyle\sum_{i=r_1}^{r_2}\left(\sum_{j=0}^{c_2}\binom{i+j}{j}-\sum_{j=0}^{c_1-1}\binom{i+j}{j}\right)$。

接着套进去：$\displaystyle\sum_{i=r_1}^{r_2}\binom{i+c_2+1}{c_2}-\binom{i+c_1}{c_1-1}$。

嗯，好了，现在这个式子的复杂度变成线性的了。

只需要预处理出阶乘与逆元直接套组合数进去算就完了。

其实这个式子还能化简，尽管上面那样已经能够通过。

换个写法：$\displaystyle\sum_{i=r_1+1}^{r_2+1}\binom{c_2+i}{i}-\binom{(c_1-1)+i}{i}$。

拆开：$\left[\displaystyle\sum_{i=0}^{r_2+1}\binom{c_2+i}{i}-\binom{(c_1-1)+i}{i}\right]-\displaystyle\left[\sum_{i=0}^{r_1}\binom{c_2+i}{i}-\binom{(c_1-1)+i}{i}\right]$。

再把组合恒等式套进去：$\displaystyle\binom{r_2+c_2+2}{r_2+1}-\binom{r_2+c_1+1}{r_2+1}-\binom{r_1+c_2+1}{r_1}+\binom{r_1+c_1}{r_1}$。

嗯，这下舒服了，如此美妙。

---

## 作者：luuia (赞：2)

### Question

给定 $a,b,c,d$，求

$$\sum_{i = a}^b\sum_{j = c}^dC_{i + j}^j$$

对 $10^9+7$ 取模。

### Solution

首先考虑容斥，记 

$$f(n,m) = \sum_{i = 1}^n\sum_{j = 1}^mC_{i + j}^j$$

那么上式的答案为 $f(c,d) - f(a - 1,d) - f(c,b - 1) + f(a - 1,b - 1)$，因此我们只需要求出 $f$ 即可。

关于 $f$ 的计算，使用组合数的递推公式：

$$C_n^m = C_{n - 1}^m + C_{n - 1}^{m - 1}$$

先考虑内层的循环：

$$
\begin{aligned}
\sum_{j = 1}^mC_{i + j}^j 
&= C_{i + 1}^1 +C_{i + 2}^2 + \cdots + C_{i + m}^m\\
&= C_{i + 2}^1 +C_{i + 2}^2 + \cdots + C_{i + m}^m\\
&= C_{i + 3}^2 +C_{i + 3}^3 + \cdots + C_{i + m}^m\\

&= C_{i + m + 1}^m
\end{aligned}
$$

外层循环是同样的道理，得到答案为 $C_{m + n + 2}^{n+1} - C_{m+1}^1$。

因此只需要 $O(n)$ 预处理出组合数，$O(1)$ 回答询问即可，注意预处理上界要开到 $2 \times 10^6$。

### Code

[AC 记录](https://www.luogu.com.cn/record/174745591)

代码放在 [云剪贴板](https://www.luogu.com.cn/paste/2759p0h3) 里了。

---

## 作者：2huk (赞：2)

## 题目描述

定义函数 $f(r, c)$ 表示从 $(0, 0)$ 走到 $(r, c)$ 且一步只能向上或向右走的方案数。

求 $\sum\limits_{i=r_1}^{r_2} \sum\limits_{j=c_1}^{c_2}f(i,j) \bmod (10^9 + 7)$ 的值。

## 数据范围

$1 \le r_1 \le r_2 \le 10^6$

$1 \le c_1 \le c_2 \le 10^6$

## 转化

思考一个问题：$f(r, c)$ 的值如何直接求？

从 $(0, 0)$ 走到 $(r, c)$，且一步只能向上或向右走，就说明无论如何只能一共向上走 $r$ 步向右走 $c$ 步，一共走 $r+c$ 步。换句话说，在总共的 $r+c$ 步中，需要选择 $r$ 步向上走和 $c$ 步向右走，所以 $f(r, c) = C_{r+c}^r = C_{r+c}^c$。原式就变成了：

$$
\sum\limits_{i=r_1}^{r_2} \sum\limits_{j=c_1}^{c_2} C_{i+j}^i
$$

求一段区间并不好算，采用前缀和的思想，先求出 $\sum\limits_{j=0}^{c_2} C_{i+j}^i$ 和 $\sum\limits_{j=0}^{c_1-1} C_{i+j}^i$ 然后相减即可，即：

$$
\sum\limits_{i=r_1}^{r_2} \left(\sum\limits_{j=0}^{c_2} C_{i+j}^i - \sum\limits_{j=0}^{c_1-1} C_{i+j}^i\right)
$$

问题来到了求这两个式子上。

## 求解

看 $\sum\limits_{j=0}^{c_2} C_{i+j}^i$ 这个式子不方便，我们把它改成 $\sum\limits_{i=0}^{n} C_{x+i}^x$。

把这个式子拆开成 $C_{x}^x + C_{x+1}^x+ C_{x+2}^x + \dots + C_{x+n}^x$，然后对应到杨辉三角中，试着发现规律。

|          |           $x$           |       $x+1$       |
| :------: | :----------: | :---------------: |
|   $x$    |   $\color{blue}C_x^x$   |        $0$        |
|  $x+1$   | $\color{blue}C_{x+1}^x$ |  $C_{x+1}^{x+1}$  |
|  $x+2$   | $\color{blue}C_{x+2}^x$ |  $C_{x+2}^{x+1}$  |
| $\vdots$ |  $\color{blue}\vdots$   |     $\vdots$      |
|  $x+n$   | $\color{blue}C_{x+n}^x$ |  $C_{x+n}^{x+1}$  |
| $x+n+1$  |      $C_{x+n+1}^x$      | $C_{x+n+1}^{x+1}$ |

我们要做的是求出所有蓝色数的和。

我们知道，在杨辉三角中，$(x,y)$ 位置的值等于 $(x-1,y)$ 和 $(x-1,y-1)$ 上的值的和，所以有：

$C_{x+1}^{x+1} = C_x^x + 0$

$C_{x+2}^{x+1} = C_{x+1}^x + C_{x+1}^{x+1} = C_{x+1}^x + C_x^x$

$C_{x+3}^{x+1} = C_{x+2}^x + C_{x+2}^{x+1} = C_{x+2}^x + C_{x+1}^x + C_x^x$

$\vdots$

$C_{x+n+1}^{x+1} = C_{x+n}^x + C_{x+n}^{x+1} = C_{x+n}^x + C_{x+n-1}^x + \dots + C_{x+1}^x + C_x^x$ 

所以也就得出：

$$
\sum\limits_{i=0}^{n} C_{x+i}^x = C_{x+n+1}^{x+1}
$$

回到原式，也就有了这个式子：

$$
\sum\limits_{i=r_1}^{r_2} \left( C_{i+c_2+1}^{i+1} - C_{i+c_1-1+1}^{i+1} \right)
$$

$-1+1$ 抵消了，所以最终的答案式为：

$$
\sum\limits_{i=r_1}^{r_2} \left( C_{i+c_2+1}^{i+1} - C_{i+c_1}^{i+1} \right)
$$

$\Theta(n)$ 求解即可。

## 代码

```cpp
int main()
{
	init(1e6 + 10);		// 预处理组合数
	
	read(r1), read(c1), read(r2), read(c2);		// 读入 
	
	for (int i = r1; i <= r2; i ++ )
		res = add(res, C(i + c2 + 1, i + 1), -C(i + c1, i + 1));		// 按公式求解 
	
	cout << res; 	// 输出答案 
	
	return 0;
}
```


---

## 作者：KokiNiwa (赞：2)

# F - Many Many Paths（组合数，性质）

[题目链接](https://atcoder.jp/contests/abc154/tasks/abc154_f)

小清新题目...其实可以出多组询问的（$\text{1e6}$组？）。

## 题目叙述

给你一个网格图，设$f(x,y)$为从$(0,0)$到$(x,y)$一共有多少种走法。求$\sum_{i=r_1}^{r_2}\sum_{j=c_1}^{c_2}f(x,y)$。

## 题解

对于每一行，计算一下和。我们考虑$O(1)$计算每一行的和。形式化的，就是用$O(1)$的时间计算$\sum_{i=l}^r f(i,j)$（$j$给定）。这个东西有个性质，就是它等于$f(r,j+1)-f(l-1,j+1)$。这个的证明，可以考虑在这个的左侧补上$f(l-1,j)$。于是一行的数的和可以$O(1)$ 计算。

当然，还有一个更优化做法，对于每一行，我们发现是同一列的后面的一个数减去同一列前面的一个数（同一列指的是每一行的列数相同）。而每一列的连续一串数的和可以化为两个数相减，于是$O(1)$就行了。

## 代码

```cpp
#include <cstdio>
using namespace std;
const int mapSize = 1e6 + 5, mod = 1e9 + 7;
int fac[mapSize * 2], inv[mapSize * 2];
void Init() {
	fac[1] = inv[1] = 1;
	for (int i = 2; i <= (int) 2e6 + 1; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % mod;
		int res = mod % i, div = mod / i;
		inv[i] = 1ll * inv[res] * (mod - div) % mod;
	}
	for (int i = 2; i <= (int) 2e6 + 1; ++i)
		inv[i] = 1ll * inv[i] * inv[i - 1] % mod;
	fac[0] = inv[0] = 1;
}
int C(int down, int up) {
	return 1ll * fac[down] * inv[up] % mod * inv[down - up] % mod;
}
int rowSum(int rowId, int colL, int colR) {
	int tmp1, tmp2, ret = ((tmp1 = (C(rowId + 1 + colR, colR)) - (tmp2 = C(rowId + colL, colL - 1))) % mod + mod) % mod;
	return ret;
}
int main() {
	Init();
	int r1, c1, r2, c2;
	scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
	int ans = 0;
	for (int rowId = r1; rowId <= r2; ++rowId)
		ans = (ans + rowSum(rowId, c1, c2)) % mod;
	printf("%d\n", ans);
	return 0;
}
```

## 知识点

+ 网格图上的小性质。

---

## 作者：ix35 (赞：2)

好像暂时没有暴力题解，我来写一篇。

首先，$(0,0)$ 到 $(r,c)$ 需要向右 $r$ 步，向上 $c$ 步，总共是 $r+c$ 步，组合一下可以得到 $f(r,c)=\binom{r+c}{c}$。

题目要求是二维区间 $f(r,c)$ 和，可以容斥成四个二维前缀和，然后来看怎么求二维前缀和：

$$Ans=\sum\limits_{i=1}^n\sum\limits_{j=1}^m \binom{i+j}{i}$$

$$Ans=\sum\limits_{i=1}^{n+m}\sum\limits_{j=\max(0,i-m)}^n \binom{i}{j}$$

令 $S(i,j)$ 表示 $\sum\limits_{k=1}^j \binom{i}{k}$，那么：

$$Ans=\sum\limits_{i=1}^{n+m}S(i,n)-S(i,\max(-1,i-m))$$

发现我们需要的只有 $S(i,n)$ 和 $S(i,i-m)$，这个可以随意递推，比如 $S(i+1,n)=2S(i,n)-\binom{i}{n}$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2000010,P=1e9+7;
int fac[MAXN],inv[MAXN];
ll s1[MAXN],s2[MAXN];
int r1,c1,r2,c2;
int qpow (int a,int b) {
	int res=1;
	while (b) {
		if (b&1) {res=(1ll*res*a)%P;}
		a=(1ll*a*a)%P,b>>=1; 
 	}
 	return res;
}
void init (int x) {
	fac[0]=inv[0]=1;
	for (int i=1;i<=x;i++) {fac[i]=(1ll*fac[i-1]*i)%P;}
	inv[x]=qpow(fac[x],P-2);
	for (int i=x-1;i>=1;i--) {inv[i]=(1ll*inv[i+1]*(i+1))%P;}
	return;
}
int c (int n,int m) {return (1ll*fac[n]*((1ll*inv[m]*inv[n-m])%P))%P;}
ll calc (int n,int m) {
	if (n==0) {return m+1;}
	if (m==0) {return n+1;}
	for (int i=0;i<=n;i++) {s1[i]=qpow(2,i);}
	for (int i=n+1;i<=n+m;i++) {s1[i]=(s1[i-1]*2-c(i-1,n)+P)%P;}
	for (int i=1;i<=m;i++) {s2[i]=0;}
	s2[m+1]=1;
	for (int i=m+2;i<=n+m;i++) {s2[i]=(s2[i-1]*2-c(i-1,i-m-2)+c(i,i-m-1)+P)%P;}
	ll res=0;
	for (int i=0;i<=n+m;i++) {
		res=(res+s1[i]-s2[i]+P)%P;
	}
	return res;
}
int main () {
	scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
	init(2000000);
	printf("%d",(calc(r2,c2)+calc(r1-1,c1-1)-calc(r1-1,c2)-calc(r2,c1-1)+P+P)%P);
	return 0;
}
```


---

## 作者：qazqazqaz (赞：1)

题意：设 $f(x,y)$ 表示每次只能向上或向右走一步，从 $(0,0)$ 走到 $(x,y)$ 的方案数，求 

$$\sum_{i=r_1}^{r_2}\sum_{j=c_1}^{c_2}f(i,j)$$ 

首先我们考虑如何求 $f(x,y)$ ，显然有：

$$f(x,y)=f(x-1,y)+f(x,y-1)$$

代入边界可以得到 $f(x,y)=\binom{x+y}{x}$

那么就要求：

$$\sum_{i=r_1}^{r_2}\sum_{j=c_1}^{c_2}\binom{i+j}{i}$$

看到下标有下界，我们考虑容斥一下，设 $r_1=0 \ , \ c_1=0$ 时的答案为 $g(r_2,c_2)$，那么我们要求的就是 $g(r_2,c_2)-g(r_1-1,c_2)-g(r_2,c_1-1)+g(r_1-1,c_1-1)$，也就是求中间的子矩形的值。

$$\begin{aligned}
g(n,m) & = \sum_{i=0}^{n}\sum_{j=0}^{m}\binom{i+j}{i} \\
&=\sum_{i=0}^{n}\binom{i+m+1}{i+1} \\
&=\sum_{i=0}^{n}\binom{i+m+1}{m} \\
&=\sum_{i=0}^{n+m+1}\binom{i}{m}-\sum_{i=0}^{m}\binom{i}{m} \\
&=\binom{n+m+2}{m+1}-1          
\end{aligned}$$

这样就可以直接线性处理阶乘及逆元直接计算了。

代码：


```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=2e6+5;
int jc[N],inv[N];
int r1,r2,c1,c2;
int qpow(int a,int b)
{
	int ans=1,base=a;
	while(b)
	{
		if(b&1)
		{
			ans=1LL*ans*base%mod;
		}
		base=1LL*base*base%mod;
		b>>=1;
	}
	return ans;
}
int binom(int a,int b)
{
	return 1LL*jc[a]*inv[b]%mod*inv[a-b]%mod;
}
int calc(int x,int y)
{
	return binom(x+y+2,y+1);
}
signed main()
{
	cin>>r1>>c1>>r2>>c2;
	jc[0]=1;
	for(int i=1;i<=r2+c2+2;i++)
	{
		jc[i]=1LL*jc[i-1]*i%mod;
	}
	inv[r2+c2+2]=qpow(jc[r2+c2+2],mod-2);
	for(int i=r2+c2+2;i;i--)
	{
		inv[i-1]=1LL*inv[i]*i%mod;
	}
	cout<<(((calc(r2,c2)-calc(r1-1,c2)+mod)%mod-calc(r2,c1-1)+mod)+mod+calc(r1-1,c1-1))%mod;
	return 0;
} 
```

---

## 作者：coding_goat (赞：1)

前置知识：乘法逆元，组合数学。

在讲思路之前，我们先证明一个等式：$\sum_{i=0}^{n} \binom{a+i}{a} = \binom{a+n+1}{a+1}$。

组合数 $\binom{n}{m}$ 可以这么理解，有 $n$ 个小球，不管顺序的挑出 $m$ 个的情况总数，所以我们可以证明 $\binom{n}{m}=\binom{n}{m-1}+\binom{n-1}{m-1}$。

因为 $\binom{a}{a} = \binom{a+1}{a+1}$，所以我们可以把 $\binom{a}{a}$ 和 $\binom{a+1}{a}$ 合起来，变成 $\binom{a+2}{a+1}$，然后再把 $\binom{a+2}{a}$ 和 $\binom{a+2}{a+1}$ 变成 $\binom{a+3}{a+1}$，以此类推，将 $\binom{a+n}{a+1}$ 和 $\binom{a+n}{a}$ 变成 $\binom{a+n+1}{a+1}$。所以有 $\sum_{i=0}^{n} \binom{a+i}{a} = \binom{a+n+1}{a+1}$。

从 $(0,0)$ 走到 $(a,b)$ 一共 $a+b$ 步，其中有 $a$ 步用于向上走，故 $(0,0)$ 到 $(a,b)$ 的情况数为 $\binom{a+b}{a}$。

我们先将第二维循环拆成前缀和的形式：

$$\sum_{i=r_1}^{r_2}(\sum_{j=0}^{c2} \binom{i+j}{i} - \sum_{j=0}^{c1-1} \binom{i+j}{i})$$

然后根据 $\sum_{i=0}^{n} \binom{a+i}{a} = \binom{a+n+1}{a+1}$，将式子改写成：

$$\sum_{i=r_1}^{r_2}(\binom{i+c2+1}{i+1} - \binom{i+c1}{i+1})$$

然后直接计算即可。

---

## 作者：Leaper_lyc (赞：1)

一道很好的组合题。

对于从 $(0,0)$ 走到 $(r,c)$，要往上走 $r$ 步，往右走 $c$ 步，那么一共要走 $(r+c)$ 步，那么 $f(r,c)$ 就等同于从 $(r+c)$ 步中选 $r$ 步向上走的方案数，即 $f(r, c) = C_{r + c}^r = C_{r + c}^c$。
那么代换一下就是要求：
$$
\sum\limits_{i=r1}^{r2}\sum\limits_{j=c1}^{c2}C_{i+j}^c
$$
由组合数的性质：
$$
\sum\limits_{i=0}^{m}C_{n+i}^n=C_{n+m+1}^{n+1}
$$
可得：
$$
\sum\limits_{i=r1}^{r2}(C_{i+c2+1}^{i+1}-C_{i+c1}^{i+1})
$$

这样，该式子就可以直接统计啦！

组合数很好求，预处理阶乘和阶乘的逆元就可以了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int _ = 2e6 + 10;
const int mod = 1e9 + 7;

int r1, r2, c1, c2;
int fac[_], inv[_], ans = 0;

inline int qpow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1) {
        if (y & 1) res = 1ll * res * x % mod;
        x = 1ll * x * x % mod;
    }
    return res;
}

void init(int N) {
    fac[0] = 1;
    for (int i = 1; i <= N; i++)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[N] = qpow(fac[N], mod - 2);
    for (int i = N; i; i--)
        inv[i - 1] = 1ll * inv[i] * i % mod;
}

inline int C(int n, int m) {
    return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

signed main() {
    cin >> r1 >> c1 >> r2 >> c2;
    init(max(r2, c2) * 2 + 1);
    for (int i = r1; i <= r2; i++)
        ans = 1ll * (ans + 1ll * (C(i + c2 + 1, i + 1) - C(i + c1, i + 1)) % mod) % mod;
    cout << (ans + mod) % mod;
}
```
~~自认为码风优良。~~

---

## 作者：cyq32ent (赞：0)

找规律，发现 $\sum_{i=1}^{c}f(r,i)=f(r+1,c)$，$\sum_{i=1}^{r}f(i,c)=f(r,c+1)$。所以 $\sum_{i=1}^{r} \sum_{j=1}^{c}f(i,j)=f(r+1,c+1)-1=C_{r+1}^{r+c+2}$。我们尝试证明这个结论。不难证明 $f(r,c)=C^{r+c}_c$，故有

$$\sum_{i=1}^{r}f(i,c)= \sum_{i=1}^{r}C^{i+c}_{c}=C^{r+c+1}_{c+1}=f(r,c+1)$$

直接使用前缀和算即可。
代码：
```cpp
#include<iostream>
using I=int64_t;
const I M=1e9+7;
#define e(_,$) (a[_+$+2]*b[_+1]%M*b[$+1]%M-1+M)%M
I r,c,R,C,a[1<<21]={1,1},b[1<<21]={1,1},d[1<<21]={1,1};
int main(){
	std::cin>>r>>c>>R>>C;
	for(I i=1;++i<R+C+3;)
		a[i]=a[i-1]*i%M,b[i]=b[i-1]*(d[i]=d[M%i]*(M-M/i)%M)%M;
	std::cout<<((e(R,C)+e(r-1,c-1)-e(r-1,C)-e(R,c-1))%M+M)%M;
	return 0;
}
```

---

## 作者：Iceturky (赞：0)

题解区里的式子都好简洁。但是我不会那么多公式怎么办。

这里有一个只需要组合数递推式就能做的方法。

-----

求 $\sum_{i=a}^b\sum_{j=l}^r C_{i+j}^{j}$。

$10^6$，考虑处理和式的变化。

如果只考虑内层和式或交换求和顺序都会因为每一项都要单独乘一个不同的系数而寄掉。

但是发现把它画到杨辉三角上发现是一个平行四边形，如果考虑杨辉三角上一行到下一行的变化会容易一些（因为可以应用我们的递推式）。

![](https://cdn.luogu.com.cn/upload/image_hosting/iklkww4c.png)

（就是求红色平行四边形内元素和）

原来的和式相当于斜着扫描这个平行四边形或竖着从左往右扫。

这样不是很能用递推式来优化。

考虑在杨辉三角形上横着从上往下扫，每次处理左端点和右端点的变化。

那么杨辉三角上的行编号 $x$ 对应的就是 $i+j$。

考虑列编号 $y$ 范围。

只需要满足 $l\leq y \leq r \land a\leq x-y\leq b$ 即可。因为列编号就是原式中的 $j$（但是并不是同一次求和内的）。

把后面式子简单化简一下就是 $x-b\leq y\leq x-a$。

题目转化为求一个 $\sum_{x=l+a}^{r+b} \sum_{y=\max(x-b,l)}^{\min(x-a,r)} C_x^y$ 。

满足条件的位置显然是一个连续区间，且发现左端点和右端点每次最多只会单调增加 $1$。

在行之间递推求和即可。

对于每一行分讨一下这一行求和区间与上一行求和即可。

考虑每一个元素都会贡献两次，分别是正下方和右斜下方。

若左端点向右移了一位，那么上一行的左端点往下递推的时候会有一个被转移的数不在求和区间内（正下方）。

左端点没有往右移则新一行的左端点会少一个正上方的递推贡献来源（上一行左端点的左边）。

右端点如果没有往右移，则会贡献到没有被求和的元素上（斜下方）。

如果右端点往右移了一位，则新一行的右端点会少一个正上方的来源（也即上一行右端点的右边）。

分别加减即可。复杂度 $\mathrm{O(n)}$。

code

```cpp
int J[N],inv[N];

int qp(int x,int y){
	int ans=1;
	for(int i=1;i<=y;i<<=1){
		if(i&y)
			ans=ans*x%mod;
		x=x*x%mod;
	}return ans;
}
int C(int n,int m){
	if(m<0||m>n)return 0;
	return J[n]*inv[n-m]%mod*inv[m]%mod;
}

signed main()
{
	int tmp=2e6;
	J[0]=inv[0]=1;
	for(int i=1;i<=tmp;i++)
		J[i]=J[i-1]*i%mod;
	inv[tmp]=qp(J[tmp],mod-2);
	for(int i=tmp-1;i>=1;i--)
		inv[i]=inv[i+1]*(i+1)%mod;
	int A=read(),L=read(),B=read(),R=read();
	int l=max(L+A-B,L),r=min(L+A-A,R);
	int sum=0,ans=0;
	for(int i=l;i<=r;i++)//先把第一行算出来 
		sum+=C(L+A,i),sum%=mod;
	ans=sum;
	for(int x=L+A+1;x<=B+R;x++){
		int ls=l,rs=r;
		l=max(L,x-B),r=min(R,x-A);
		int nsum=0;
		if(r>rs)
			nsum+=C(x-1,r);//新的右端点少了一个正上方的贡献 
		else
			nsum+=mod-C(x-1,rs);//旧的右端点多做了一个右下方的贡献 
		if(l>ls)
			nsum+=mod-C(x-1,ls);//旧的左端点多作了一个正下方的贡献 
		else
			nsum+=C(x-1,l-1);//新的左端点少了一个左上方的贡献 
		nsum%=mod;
		sum=sum*2%mod+nsum;//每一个元素都有两个新元素贡献，再加上维护好的左右端点的处理。 
		sum%=mod;
		ans=(ans+sum)%mod;
	}print(ans),pc('\n');
	return 0;
}

```

---

## 作者：NATO (赞：0)

组合数学题。

首先我们可以套路地拆询问：$\sum\limits_{i=r_1}^{r_2} \sum\limits_{j=c_1}^{c_2}f(i,j)=\sum\limits_{i=0}^{r_2} \sum\limits_{j=0}^{c_2}f(i,j)-\sum\limits_{i=0}^{r_2} \sum\limits_{j=0}^{c_1-1}f(i,j)-\sum\limits_{i=0}^{r_1-1} \sum\limits_{j=0}^{c_2}f(i,j)+\sum\limits_{i=0}^{r_1-1} \sum\limits_{j=0}^{c_1-1}f(i,j)$

显然，只要找到了求 $\sum\limits_{i=0}^{n} \sum\limits_{j=0}^{m}f(i,j)$ 的方法，我们就解决了这道题。

我们先来考虑 $f(i,j)$ 的取值。

考虑你一共要走 $i+j$ 步，其中有 $i$ 步是要向 $x$ 轴正方向走一步，那么每一种不同的选择这 $i$ 步的方法就是一种不同的走法，那么 $f(i,j)$ 就相当于 $i+j$ 个物品中选 $i$ 个物品的组合数，即：

$f(i,j)=C_{j+i}^{i}$

考虑使用数学归纳法进行证明。

首先考虑边界情况。

显然，$f(0,0)=1$，由于 $f(0,j)$ 只能从左边走来，故一直为 $1$，$f(i,0)$ 同理，故 $f(i,0)=C_{i}^{i}$ 和 $f(0,j)=C_{j}^{0}$ 成立。

假设我们已经证明了对于 $\forall a\le i,b\le j$，$a=i$ 和 $b=j$ 不同时该结论成立，那么：

$$
\begin{aligned}

&f(i,j)=f(i-1,j)+f(i,j-1)\\

&=C_{i+j-1}^{i-1}+C_{i+j-1}^{i}

\end{aligned}$$

根据杨辉三角我们知道：$C_{p}^{q}=C_{p-1}^{q}+C_{p-1}^{q-1}$

是故 $f(i,j)=C_{i+j-1}^{i-1}+C_{i+j-1}^{i}=C_{i+j}^{i}$。

证毕。

那么 $\sum\limits_{i=0}^{n} \sum\limits_{j=0}^{m}f(i,j)=\sum\limits_{i=0}^{n} \sum\limits_{j=0}^{m}C_{i+j}^{i}$，我们考虑只看 $\sum\limits_{j=0}^{m}C_{i+j}^{i}$ 这一坨。

根据 $\sum\limits_{k=l}^{n}C_{k}^{l}=C_{n+1}^{l+1}$ 可知：

$\sum\limits_{j=0}^{m}C_{i+j}^{i}=C_{i+m}^{i+1}$

那么 $\sum\limits_{i=0}^{n} \sum\limits_{j=0}^{m}f(i,j)=\sum\limits_{i=0}^{n} \sum\limits_{j=0}^{m}C_{i+j}^{i}=\sum\limits_{i=0}^{n}C_{i+m}^{i+1}$。

如果我们暴力计算，复杂度仍然与暴力动规无异，是 $O(nm)$ 的。

考虑寻找 $C_{i+m}^{i+1}$ 随 $i$ 变化的规律。

我们将它按照组合数的定义展开后可发现 $i$ 加 $1$ 后它多乘上了一个 $i+m+1$，多除上了一个 $i+1$，那么我们就可以随着 $i$ 迭代地每次 $O(1)$ 更新 $C_{i+m}^{i+1}$ 即可累加答案。

至此，我们便发现了 $O(n)$ 求 $\sum\limits_{i=0}^{n} \sum\limits_{j=0}^{m}f(i,j)$ 的方法，解决了本题。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007ll
using namespace std;
ll r1,r2,c1,c2;
ll inv[2000005];
ll qpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)res=res*a%MOD;
		a=a*a%MOD;b>>=1;
	}
	return res;
}
ll C(ll n,ll m)
{
	ll res=1;
	for(ll i=m+1;i<=n;++i)res=res*i%MOD;
	ll ls=1;
	for(ll i=1;i<=n-m;++i)ls=ls*inv[i]%MOD;
	return res*ls%MOD;
}
ll get_res(ll n,ll m)
{
	ll res=1;
	ll st=1;
	for(ll i=1;i<=m;++i)
	{
		st=st*(n+i-1)%MOD*inv[i]%MOD;
		res=(res+st)%MOD;
	}	
	return res;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>r1>>c1>>r2>>c2;
	for(ll i=1;i<=2000000;++i)inv[i]=qpow(i,MOD-2);
	++r1;++c1;++r2;++c2;
	cout<<((get_res(r2,c2)-get_res(r2,c1-1)-get_res(r1-1,c2)+get_res(r1-1,c1-1))%MOD+MOD)%MOD;
}
```


---

## 作者：small_john (赞：0)

## 思路

首先，需要知道每一个 $f(i,j)$ 怎么求。

小学奥数交给我们了一个方法：标数法。

![](https://cdn.luogu.com.cn/upload/image_hosting/melqgbu0.png)

等等，这不是杨辉三角吗？杨辉三角……组合数！对，组合数！$f(i,j)=\binom{i+j}{j}$。

题目就被我们转化成了：求 $\displaystyle \sum_{i=r1}^{r2}\sum_{j=c1}^{c2}\binom{i+j}{j}$。

那这个怎么求呢？

观察一下，可以得到 $\displaystyle \sum_{i=1}^{n}\sum_{j=1}^{m}\binom{i+j}{j}=\binom{n+m+2}{m+1}-1$。

那这样，就可以用前缀和的思想求解，即：$\displaystyle \sum_{i=r1}^{r2}\sum_{j=c1}^{c2}\binom{i+j}{j}=\sum_{i=1}^{r2}\sum_{j=1}^{c2}\binom{i+j}{j}-\sum_{i=1}^{r2}\sum_{j=1}^{c1-1}\binom{i+j}{j}-\sum_{i=1}^{r1-1}\sum_{j=1}^{c2}\binom{i+j}{j}+\sum_{i=1}^{r1-1}\sum_{j=1}^{c1-1}\binom{i+j}{j}=\binom{r2+c2+2}{c2+1}-\binom{r2+c1+1}{c1}-\binom{r1+c2+1}{c2+1}+\binom{r1+c1}{c1}$。

~~式子推了好久，不喜勿喷。~~

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9+7,N = 3e6+5;
int fac[N],iv[N],inv[N];
void init()
{
	fac[0] = 1;
	for(int i = 1;i<N;i++)
		fac[i] = fac[i-1]*i%mod;
	iv[1] = 1;
	for(int i = 2;i<N;i++)
		iv[i] = (mod-mod/i)*iv[mod%i]%mod;
	inv[0] = 1;
	for(int i = 1;i<N;i++)
		inv[i] = inv[i-1]*iv[i]%mod;
}
int C(int n,int m)
{
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int a,b,c,d;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	init();
	cin>>a>>b>>c>>d;
	int ans = C(c+d+2,d+1)-C(c+b+1,b)-C(a+d+1,d+1)+C(a+b,b);//后面的减1可以忽略
	cout<<(ans%mod+mod)%mod;//转整数
	return 0;
}
```

---

## 作者：ljlawa (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc154_f)

给定 $r1,r2,c1,c2$，求 $\sum_{i = r1}^{r2}\sum_{j = c1}^{c2}f(i,j)$。

在做这道题之前我们需要了解一些式子。

$1.\ C_n^m + C_n^{m+1} = \frac {n!}{m!(n-m)!}+\frac {n!}{(m+1)m!(n-m-1)!}$

$ = \frac {n!}{m!(n-m)!}+\frac {(n-m)n!}{(m+1)m!(n-m)!}$

$ = \frac {(m+1)n!}{(m+1)m!(n-m)!}+\frac {(n-m)n!}{(m+1)m!(n-m)!}$

$ = \frac {(n+1)!}{(m+1)!(n-m)!} $

$ = C_{n + 1} ^ {m + 1}$

------------

$2.\ \sum_{k=0}^n C_k^m = C_m^m + C_{m+1}^m+\cdots+C_n^m$

$ = (C_{m + 1}^{m + 1} + C_{m + 1} ^m) + \cdots+C_n^m$

$ = C_{m + 2}^{m + 1} + C_{m + 2} ^m + \cdots+C_n^m$

$ = \cdots = C_{n + 1}^{m + 1}$

------------

$3.\ f(i,j) = C_{i+j}^{i}$

自己推，容易发现。

------------

回到题目，求 $\sum_{i = r1}^{r2}\sum_{j = c1}^{c2}f(i,j)$ 。

我们先枚举 $i$，然后要求 $\sum_{j=c1}^{c2}f(i,j)$，然后考虑用上面的第二个式子优化掉，把原式变为 $\sum_{j=0}^{c2}f(i,j) - \sum_{j=0}^{c1 - 1}f(i,j)$，然后直接使用第二个式子得到 $C_{c2 + i + 1}^{i+1} - C_{c1 + i}^{i+1}$。

于是问题就解决了。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int P = 1e9 + 7;
const int N = 5e6 + 5;

int fac[N], inv[N];

int ksm (int a, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = 1ll * ans * a % P;
		a = 1ll * a * a % P;
		b >>= 1; 
	}
	return ans;
}

void init (int n)
{
	fac[0] = inv[0] = 1;
	for (int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % P;
	inv[n] = ksm (fac[n], P - 2);
	for (int i = n - 1; i; i --) inv[i] = 1ll * inv[i + 1] * (i + 1) % P;
}

int C(int n, int m)
{
	if (m > n) return 0; 
	return 1ll * fac[n] * inv[n - m] % P * inv[m] % P;
}

int r1, r2, c1, c2, ans;
int main()
{
	init (4000000);
	cin >> r1 >> c1 >> r2 >> c2;
	for (int i = r1; i <= r2; i ++)
	{
		ans = (1ll * ans + 1ll * C(c2 + i + 1, i + 1) - 1ll * C(c1 + i, i + 1)) % P;
		ans = (ans + P) % P;
	}
	cout << ans;
 	return 0;
}
```


---

## 作者：daniEl_lElE (赞：0)

## 思路

转化一下 $\sum_{i=c_1}^{c_2}\sum_{j=r_1}^{r_2}\dbinom{i+j}{i}$。

推一推 $\sum_{i=c_1}^{c_2}(\sum_{j=r_1}^{r_2}\dbinom{i+j}{i}+\dbinom{i+r_1}{i+1}-\dbinom{i+r_1}{i+1})=\sum_{i=c_1}^{c_2}(\dbinom{i+r_2+1}{i+1}-\dbinom{i+r_1}{i+1})$。

再推一推 $\sum_{i=c_1}^{c_2}(\dbinom{i+r_2+1}{i+1}-\dbinom{i+r_1}{i+1})=\dbinom{c_2+r_2+2}{c_2+1}-\dbinom{c_1+r_2+1}{c_1}-\dbinom{c_2+r_1+1}{r_1}+\dbinom{r_1+c_1}{r_1}$。

然后就没有然后了。

不清楚这个式子的可以观察杨辉三角或自己把组合数拆开：

$\dbinom{i}{j}+\dbinom{i}{j+1}=\dfrac{i!}{j!(i-j)!}+\dfrac{i!}{(j+1)!(i-j-1)!}=\dfrac{((j+1)+(i-j))i!}{(j+1)!(i-j)!}=\dfrac{(i+1)!}{(j+1)!(i-j)!}=\dbinom{i+1}{j+1}$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[10000005],inv[10000005];
void init(){
	fac[0]=1;
	for(int i=1;i<=10000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[10000000]=qp(fac[10000000],mod-2);
	for(int i=9999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[i-j]%mod*inv[j]%mod;
}
signed main(){
	init();
	int r1,c1,r2,c2;
	cin>>r1>>c1>>r2>>c2;
	cout<<(C(r2+1+c2+1,r2+1)+C(r1+c1,r1)+mod+mod-C(r1+c2+1,r1)-C(r2+c1+1,c1))%mod;
	return 0;
}
```

---

