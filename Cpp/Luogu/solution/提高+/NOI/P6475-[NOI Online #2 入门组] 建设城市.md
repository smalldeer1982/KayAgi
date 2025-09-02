# [NOI Online #2 入门组] 建设城市

## 题目描述

球球是一位建筑师。一天，他收到市长的任务：建设城市。球球打算建造 $2n$ 座高楼。为了保证城市美观，球球做出了如下计划：

- 球球喜欢整齐的事物。他希望高楼从左向右排成一行，编号依次为 $1\sim 2n$。

- 球球喜欢整数，他要求每座高楼的高度都是正整数。

- 由于材料限制，高楼的高度无法超过 $m$。

- 球球喜欢中间高，两边低的造型。他要求前 $n$ 座高楼的高度不下降，后 $n$ 座高楼的高度不上升。

- 球球打算选两座编号为 $x,y$ 的高楼作为这座城市的地标。他认为只有当这两座高楼高度相等时，才会让城市变得美观。

球球把自己的想法告诉了市长。市长希望得知所有建设城市的方案数。两种方案不同，当且仅当某座高楼的高度在两个方案中不同。这个问题可难倒了球球。球球找到了你，希望你能帮他算出答案。由于答案可能很大，你只需要给出答案对 $998244353$ 取模后的结果。

## 说明/提示

对于样例 $1$，所有的方案为：$\{1,1,1,1\},\{1,2,1,1\},\{1,3,1,1\},\{2,2,2,1\},\{2,2,2,2\},\\\{2,3,2,1\},\{2,3,2,2\},\{3,3,3,1\},\{3,3,3,2\},\{3,3,3,3\}$。

对于 $10\%$ 的数据，$1\le n,m\le 5$。

对于 $30\%$ 的数据，$1\le n,m\le 100$。

对于 $60\%$ 的数据，$1\le n,m\le 1000$。

对于 $100\%$ 的数据，$1\le x < y \le 2n$， $1\le n,m \le 10^5$。

## 样例 #1

### 输入

```
3 2 1 3```

### 输出

```
10```

## 样例 #2

### 输入

```
1000 1000 535 1477```

### 输出

```
295916566```

# 题解

## 作者：Alex_Wei (赞：57)

> [题面传送门](https://www.luogu.com.cn/problem/P6475)。

> 前置知识：组合数学（[P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)，利用乘法逆元求组合数）。

---

题目没有告诉我们 $x,y$ 是否是在 $n$ 的两侧，所以要分情况讨论。

- Case $1$：$x\leq n<y$。

  枚举 $x,y$ 的高度。假设当前 $x,y$ 的高度为 $i$，则：
  
  - $x$ 左边的 $x-1$ 个高楼高度范围为 $[1,i]$。
  - $x$ 右边 $n$ 左边（包含 $n$）的 $n-x$ 个高楼高度范围为 $[i,m]$。
  - $n$ 右边（不包含 $n$）$y$ 左边的 $y-n-1$ 个高楼高度范围为 $[i,m]$。
  - $y$ 右边的 $2n-y$ 个高楼高度范围为 $[1,i]$。
  
  考虑怎么求单独一块区域的贡献。显然不上升和不下降贡献相等。如果一块区域有 $a$ 栋高楼，$b$ 个高度可以选，则相当于 **$a$ 个相同的球放入 $b$ 个不同的盒子** 的方案数。根据小学二年级（？的数学知识，可以将其看做 **$a+b$ 个相同的球放到 $b$ 个不同的盒子中，每个盒子至少放一个球**，插板法即可得 $\binom{a+b-1}{b-1}$。
  
  为什么是 $a$ 个**相同**的球？因为题目要求高楼高度不上升/不下降，所以**方案与是什么高楼无关，只和每个高楼的高度有关**。
  
  根据乘法原理，将上述四块区域的贡献相乘即为 $x,y=i$ 时的方案数。

- Case $2$：$x,y\leq n$ 或 $x,y>n$。

  将 $[x,y]$ 中间的高楼看成一个高楼，则根据 Case $1$ 的 trick，答案为 $\binom{n+m-1}{m-1}\times\binom{n+x-y+m-1}{m-1}$。

$O(n)$ 预处理阶乘及其逆元即可做到 $O(n)$ 求答案。

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N=2e5+5;
const int p=998244353;
ll ksm(ll a,ll b){ll s=1,m=a; while(b){if(b&1)s=s*m%p; m=m*m%p,b>>=1;} return s;}

ll m,n,x,y,ans,fc[N],ifc[N];
ll C(ll m,ll n){return fc[n+m-1]*ifc[n]%p*ifc[m-1]%p;}

int main(){
	cin>>m>>n>>x>>y;
	fc[0]=1; for(int i=1;i<=m+n;i++)fc[i]=fc[i-1]*i%p;
	ifc[m+n]=ksm(fc[m+n],p-2); for(int i=m+n-1;~i;i--)ifc[i]=ifc[i+1]*(i+1)%p;
	if(x<=n&&y>n)for(int i=1;i<=m;i++)ans=(ans+C(i,x-1)*C(m-i+1,n-x)%p*C(m-i+1,y-n-1)%p*C(i,2*n-y))%p;
	else ans=C(m,n)*C(m,n+x-y)%p;
	cout<<ans<<endl;
	return 0;
}
```

写的比较匆忙，如有笔误还请尽快指出，感激不尽！

Upd on 2020.5.3：修改部分文字和代码。

---

## 作者：Velix (赞：26)


[如果公式挂了请私信我并到博客查看](https://www.luogu.com.cn/blog/cxy-blog-2333/solution-p6475)

---
前言：

	这个人网络爆炸了，于是pj成功爆了0。可恶的土豆服务器(〃＞皿＜)
    
    由于半年没写过关于组合数的题了，所以有锅别怪我（
    
---

## 正文开始

前置知识：快速幂，组合数学（初赛时有讲），逆元。

---

首先我们设一个函数$f(i,j)$表示值域为$1+x \sim j+x|x\in N$（可以证明不管$x$为多少都对答案没有多大关系），序列长度为$i$的序列的排列方案。

然后由插板法可得
$$f(i,j)=\dbinom{i+j-1}{j-1}$$

---

接下来就开始狂废脑子了……

对于答案的统计，需要分情况讨论

+ $x<=n,y>n$

对于这种情况我们可以做一个图示：

![](https://cdn.luogu.com.cn/upload/image_hosting/uqk2m04y.png)

在此时，这个序列便分为四个区间：$1\sim x-1,x+1\sim n,n+1\sim y-1,y+1\sim n*2$

通过枚举$m$以及乘法原理，我们可以得到这种情况的答案：
$$ans=\sum\limits_{i=1}^m f(x-1,i)*f(n-x,m-i+1)*f(y-n-1,m-i+1)*f(2*n-y,i)$$

+ $n<x<y$或$x<y<=n$

图示：

![](https://cdn.luogu.com.cn/upload/image_hosting/xjleremv.png)

注意到$x$与$y$是相等的，所以我们可以把区间$x\sim y$合并成一个点。

又根据乘法原理，我们可以$O(1)$计算出答案：
$$ans=f(n,m)*f(n+x-y,m)$$

---
完了？完了。

似乎忘了什么……

对了：

### 如何$O(1)$计算$f$函数啊!!!∑(ﾟДﾟノ)ノ

我们之前提到过$f(i,j)$就是$\dbinom{i+j-1}{j-1}$

所以求$f$函数又转化为求组合数

而众所周知，
$$\dbinom{n}{m}=\dfrac{n!}{m!(n-m)!}$$

所以

$$f(i,j)=\dfrac{(i+j-1)!}{i!(j-1)!}$$

我们现在剩下的任务就是求$1!\sim 200000!$的逆元（$n+m$最大为$200000$，当然你也可以只预处理到$n+m$）。

[实在不知道逆元的到这来](https://www.luogu.com.cn/problemnew/solution/P3811)

接下来介绍两种求逆元的方法：

+ 无需理解，会逆元就行

学过都知道，一个数$x$的逆元就是$x^{mod-2}$（不会的记得这个公式就行了）

所以在循环的时候，直接每次利用求出的$fra$数组（也就是阶乘）以及快速幂进行求逆元就行了

时间复杂度$\Theta(nlogn)$

代码
```cpp
void prework()
{
	fac[0]=inv[0]=1;
	for(int i=1;i<=200000;i++)fac[i]=(fac[i-1]*i)%mod;
	for(int i=1;i<=200000;i++)inv[i]=quick(fac[i],mod-2);
}
```

+ 速度快，但需要进行理解

首先我们还需要求出$fra$数组。

然后求出$inv[n+m]$。

最后后从后往前循环，每次求$inv[i]$（阶乘逆元）时，将$inv[i+1]$乘以$(i+1)$即可得到$inv[i]$。

证明？

$$(n+1)! * \dfrac{1}{n+1}=n!$$

时间复杂度为$\Theta(n)$

代码
```cpp
void prework()
{
	fac[0]=inv[0]=1;
	for(int i=1;i<=200000;i++)fac[i]=(fac[i-1]*i)%mod;
	inv[200000]=quick(fac[200000],mod-2);
	for(int i=199999;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
```
---
然后调用$f$数组时的代码：
```cpp
ll f(int n,int m){return fac[n+m-1]*inv[n]%mod*inv[m-1]%mod;}
```

---

### Final Code
```cpp
#include<iostream>
#include<cstdio>
#define mod 998244353
#define ll long long
using namespace std;
ll fac[200001],inv[200001],n,m,x,y,ans;
ll quick(ll a,ll b)
{
	ll xx=a,yy=1;
	while(b)
	{
		if(b&1) yy=yy*xx%mod;
		xx=xx*xx%mod;
		b/=2;
	}
	return yy;
}
ll f(int nn,int mm){return fac[mm+nn-1]*inv[nn]%mod*inv[mm-1]%mod;}
int main()
{
	fac[0]=inv[0]=1;
	for(int i=1;i<=200000;i++)fac[i]=(fac[i-1]*i)%mod;
	inv[200000]=quick(fac[200000],mod-2);
	for(int i=199999;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	cin>>m>>n>>x>>y;
	if(x<=n&&y>n)
		for(int i=1;i<=m;i++)
			ans=(ans+f(x-1,i)*f(n-x,m-i+1)%mod*f(2*n-y,i)%mod*f(y-n-1,m-i+1))%mod;
	else ans=f(n,m)*f(n+x-y,m)%mod;
	cout<<ans;
}
```


---

## 作者：NaCly_Fish (赞：14)

设 $f_{i,j}$ 为以 $j$ 结尾、长度为 $i$ 的单调不降序列数，那么枚举第 $i-1$ 个的值，就有转移：

$$f_{i,j} = \sum_{k=1}^jf_{i-1,k}=f_{i,j-1}+f_{i-1,j}$$
对于边界条件，显然有 $f_{1,j}=1$。

如果对组合数比较熟悉，很快就能发现其通项为
$$f_{i,j}= \binom{j+i-2}{i-1}$$
那么要计算长度为 $i$、**值域** 为 $j$ 的单调不降序列数 $g_{i,j}$，就是
$$g_{i,j}=\sum_{k=1}^jf_{i,k}=\binom{j+i-1}{i-1}$$
前面说这些有什么用呢？我们枚举 $x,y$ 位置的高度，就可以转化为上述问题了。

注意要分类讨论一下 $x,y$ 同侧/异侧的情况，题目中并没有说 $x\le n < y$！

~~如何做到更快：计算式中的 $g$ 显然都是整式递推数列，其乘积、前缀和也是整式递推数列，可以 $\Theta(\sqrt m \log m)$ 解决。~~

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 200005
#define ll long long
#define reg register
#define p 998244353
using namespace std;

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

int fac[N],ifac[N];

void init(int n){
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for(reg int i=2;i<=n;++i) fac[i] = (ll)fac[i-1]*i%p;
    ifac[n] = power(fac[n],p-2);
    for(reg int i=n-1;i;--i) ifac[i] = (ll)ifac[i+1]*(i+1)%p;
}

inline int g(int n,int m){
    return (ll)fac[n+m-1]*ifac[n]%p*ifac[m-1]%p;
}

int n,m,x,y,ans;

int main(){
    scanf("%d%d%d%d",&m,&n,&x,&y);
    init(n+m+1);
    if((y>n)^(x>n)){ //异侧
        if(y>n) y = (n<<1)-y+1; // 把位置转到 [1,n] 中
        for(reg int k=1;k<=m;++k)
            ans = (ans+(ll)g(x-1,k)*g(n-x,m-k+1)%p*g(y-1,k)%p*g(n-y,m-k+1))%p;
    }else{ //同侧
        if(y>n) y = (n<<1)-y+1;
        if(x>n) x = (n<<1)-x+1;
        if(x>y) swap(x,y);
        for(reg int k=1;k<=m;++k) // 这是一个卷积式，可以不用循环解决
            ans = (ans+(ll)g(x-1,k)*g(n-y,m-k+1))%p;
        ans = (ll)ans*g(n,m)%p;
    }
    printf("%d",ans);    
    return 0;   
}
```

---

## 作者：PYD1 (赞：6)

# 审题

[P6475](https://www.luogu.com.cn/problem/P6475)

略

# 分析
题目中给了我们如下的条件
- 楼的编号为$1-2n$
- 高度均为正整数且不超过$m$
- 前n座楼高度不下降，后n座楼高度不上升（即像一座山的形状）
- $x,y$两楼高度相等

我们发现只有最后一个条件比较特殊，所以尝试从最后一个条件入手。

经过简单的思考，不难得到，这道题目有两种情况：$x,y$不在同一侧，$x,y$在同一侧

### 1° 当$x,y$不在同一侧时，即$1\le x\le n<y\le2n$时

我们可以考虑将其分为四段来计算:

![](https://cdn.luogu.com.cn/upload/image_hosting/c639ttdf.png)

$1 \ -\ x,x+1 \ - \ n,n+1 \ - \ y,y + 1 \ - \ 2n$

不妨设$x,y$的高度都为$i$

则我们要计算的就是：
- $x-1$座高楼（$x$高度已固定，$y$同理）高度不超过$i$
- $n-x$座高楼高度在$i\ - \ m$范围内（即高度不超过$m-i+1$）
- $y-n-1$座高楼高度在$i\ - \ m$范围内（即高度不超过$m-i+1$）
- $2n-y$座高楼高度不超过$i$

的方案数，再由乘法原理相乘即可得到结果

注意到，其中出现了好几次$a$座高楼高度不超过$b$的表述，考虑将其写成一个函数$f(a,b)$来计算值

要解决这个问题，我们可以把它看成是有$a$个小球（高楼）放入$b$个盒子（高度），求方案总数的问题

我们可以先在每个盒子里都放上一个小球，现在一共有$a+b$个小球，$b$个盒子，每个盒子里至少有一个小球，考虑使用插板法：将这些小球摆成一排，在球与球之间的空隙中插入$b-1$块板子，第1个板子之前的放入第1个盒子，第2个板子至第1个板子之间的放入第2个盒子……以此类推。

这样，方案总数就被我们转移成了$a+b-1$个空隙中选取$b-1$个空隙插入板子的问题，熟悉组合数学的同学已经知道，这就是$C_{a+b-1}^{b-1}$（不了解的同学可以百度[组合数](https://baike.baidu.com/item/%E7%BB%84%E5%90%88%E6%95%B0/2153250?fr=aladdin)）

而由组合数的定义，我们有$C_{a+b-1}^{b-1}=\dfrac{(a+b-1)!}{(b-1)!((a+b-1)-(b-1))!}=\dfrac{(a+b-1)!}{(b-1)!a!}$

（感谢@[bluebayou](https://www.luogu.com.cn/user/143233)的建议，下方写出另一种理解方式，供大家参考：
$C_{a+b-1}^{b-1}=C_{a+b-1}^{a}=\dfrac{(a+b-1)!}{a!(a+b-1-a)!}=\dfrac{(a+b-1)!}{a!(b-1)!}$
）

所以$f(a,b)=\dfrac{(a+b-1)!}{(b-1)!a!}$

我们能够计算出$f(a,b)$后，用一个for循环从1至$m$枚举$k$，再计算$f(x-1,k)*f(n-x,m-k+1)*f(y-n-1,m-k+1)*f(2n-y,k)$求和即可，即求：

$$\sum_{k=1}^mf(x-1,k)*f(n-x,m-k+1)*f(y-n-1,m-k+1)*f(2n-y,k)$$

### 2°当$x,y$在同一侧时，即$1\le x<y\le n$或$n<x<y\le 2n$时
![](https://cdn.luogu.com.cn/upload/image_hosting/2y0lzo2m.png)

 我们可以将$[x,y]$（即$x$至$y$包括$x,y$）这一段高楼合并为一座高楼
 
 分为两部分计算：
 - 左边$n+x-y$座高楼高度不超过$m$
 - 右边$n$座高楼高度不超过$m$
 
 当$[x,y]$这“一栋”大楼获得自己的高度时，我们再把它展开，方案总数不变
 
 所以方案总数为：
 
 $$f(n+x-y,m)*f(n,m)$$
 
#  预处理
如果每次求$f(a,b)$时都套用$f(a,b)=\dfrac{(a+b-1)!}{(b-1)!a!}$来计算，那么每次都要计算阶乘，过于耗时。所以我们考虑预处理，使得我们能够$O(1)$计算$f(a,b)$

### 首先
显而易见，我们需要预处理阶乘数组$jc$，使得$jc[i]=i!$。将$jc[0]$赋值为1，然后for $i$ 从1至$n+m$（因为最多就能用到$(n+m-1)!$），$jc[i]=jc[i-1]*i$即可。代码比较简单，如下：（不要忘记取余）

```cpp
jc[0] = 1;
for (register long long i = 1;i <= n + m;i++) jc[i] = (jc[i - 1] * i) % MOD;
```
### 其次
注意到我们实际上并不想知道$f(a,b)$，而是想知道$f(a,b)\% \ MOD$，又注意到$f(a,b)$是一个分式，取余时会用到乘法逆元，所以考虑预处理乘法逆元数组$ny$，使得$i! * ny[i]\equiv 1\ (\bmod \ MOD)$（即$ny[i]$为$i!$的乘法逆元）

（不会的同学可以看我的[乘法逆元](https://www.luogu.com.cn/blog/PYD/cheng-fa-ni-yuan)）

代码也很简单，如下：（使用的是费马小定理版本）
```cpp
long long _pow(long long a,long long k){
	long long ans = 1;
	for (;k;k >>= 1,(a *= a) %= MOD){
		if (k & 1) (ans *= a) %= MOD;
	}
	return ans;
}//快速幂

void init(){
	ny[0] = 1;
	for (register long long i = 1;i <= n + m;i++) ny[i] = _pow(jc[i],MOD - 2);
}
```

将两个合并，就得到了预处理的代码（快速幂省略）：
```cpp
void init(){
	for (register long long i = 1;i <= n + m;i++) jc[i] = (jc[i - 1] * i) % MOD;
	for (register long long i = 1;i <= n + m;i++) ny[i] = _pow(jc[i],MOD - 2);
}
```

由$jc$数组和$ny$数组，
$$f(a,b) = \dfrac{(a+b-1)!}{(b-1)!a!}\equiv \dfrac{jc[a+b-1]}{jc[b-1]*jc[a]}\equiv jc[a+b-1]*ny[b-1]*ny[a] \ (\bmod \ MOD)$$

所以我们可以写出 $f$函数：（不要忘了每乘一项就$\% MOD$）
```
long long f(long long a,long long b){
	return jc[a + b - 1] * ny[a] % MOD * ny[b - 1] % MOD;
}
```

# 完整代码

码风不好请见谅

```cpp
#include <bits/stdc++.h>//万能头，不想用的用#include <cstdio>即可 
using namespace std;

const long long MOD = 998244353;
long long m,n,x,y,jc[2000001] = {1},ny[2000001] = {1},ans;//定义jc阶乘数组，ny逆元数组（注意！这里ny[i]为i!的逆元而不是i的逆元） 

long long _pow(long long a,long long k){
	long long ans = 1;
	for (;k;k >>= 1,(a *= a) %= MOD){
		if (k & 1) (ans *= a) %= MOD;
	}
	return ans;
}//快速幂 

void init(){
	for (register long long i = 1;i <= n + m;i++) jc[i] = (jc[i - 1] * i) % MOD;
	for (register long long i = 1;i <= n + m;i++) ny[i] = _pow(jc[i],MOD - 2);
}//初始化（jc[0]和ny[0]在最初已经被赋值为1，此处不用再赋值 

long long f(long long a,long long b){
	return jc[a + b - 1] * ny[a] % MOD * ny[b - 1] % MOD;
}//f函数，具体解释请看上文“初始化”部分 

int main(){
	scanf("%d %d %d %d",&m,&n,&x,&y),init();//读入&初始化 
	if (x <= n && y > n){//如果x,y不在同一侧 
		for (register long long i = 1;i <= m;i++) ans = (ans + f(x - 1,i) * f(n - x,m - i + 1) % MOD * f(y - n - 1,m - i + 1) % MOD * f(n * 2 - y,i) % MOD) % MOD;//计算，求和 
	}else ans = f(n,m) * f(n + x - y,m) % MOD;//否则即为x,y在同一侧，计算 
	printf("%d",ans);//输出答案 
	return 0;
}
```
完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：syksykCCC (赞：6)

记 $h_i$ 表示第 $i$ 个楼的高度。题意就是说求满足下面三个条件的数列的个数：

1. $h_1 \le h_2 \le \cdots \le h_n, h_{n+1} \ge h_{n+2} \ge \cdots \ge h_{2n}$
2. $h_x = h_y$
3. $\forall 1 \le i \le 2n, h_i \in [1, m]$

如果没有 $h_x = h_y$ 的限制，方案数应该是什么呢？

显然上升部分和下降部分的方案数是相等的，我们只考虑前面一个部分（也就是用 $[1, m]$ 拼长度为 $n$ 的不下降序列的方案数 $f(n, m)$）。利用隔板法的思想，可以先把楼排成一行，在中间依次插上 $m - 1$ 个隔板，相邻两个隔板之间的楼的高度相等，求不同的插法。

当然，这时可能会有多个隔板在一个位置，比如楼房高度为 $\{1, 1, 3\}$ 时，隔板的插法就是 $\{ \circ \circ \ |\ |\ \circ \}$。

这违背了隔板法的要求，所以我们加 $m$ 个楼进去，确保这些新加的楼的高度分别为 $1 \sim m$，然后就可以用隔板法了。

比如 $m = 3$，$\{ \circ\circ |\circ |\circ\circ \}$ 这种插法对应的就是 $\{1, 3\}$，因为我们要在每两个隔板见去掉一个。

所以，相当于是有 $n + m$ 个楼，插 $m - 1$ 个隔板的方案数。隔板显然是插在间隔里，$n + m$ 个楼有 $n+m-1$ 个间隔，所以，方案数就是：

$$ f(n, m)=\binom{n+m-1}{m-1} $$

接下来，考虑加上 $h_x = h_y$ 的条件。

* 如果 $x, y$ 在同一侧，那么显然 $h_x , h_{x+1} \cdots h_y$ 都是相等的，可以视作一个楼（所以少了 $y - x$ 个楼），所以，这一侧的方案数就是 $f(n - (y - x), m) = f(n + x - y, m)$，另一侧不变，也就是 $f(n, m)$。综上，答案为：

$$ f(n+x-y, m) \times f(n, m) $$

* 如果 $x, y$ 不在同一侧，不妨枚举一下 $h_x$ 等于多少，比如枚举到的是 $h_x = i$，那么序列会分为 $4$ 段：
  * $h_1 \sim h_{x - 1}$ 这 $x - 1$ 个楼应当 $\in [1, i]$，所以方案数为 $f(x - 1, i)$；
  * $h_{x+1} \sim h_n$ 这 $n - x$ 个楼应当 $\in[i, m]$，所以方案数为 $f(n - x, m - i + 1)$；
  * $h_{n+1} \sim h_{y-1}$ 这 $y-n-1$ 个楼应当 $\in[i, m]$，所以方案数为 $f(y-n-1, m - i + 1)$；
  * $h_{y+1} \sim h_{2n}$ 这 $2n - y$ 个楼应当 $\in[1, i]$，所以方案数为 $f(2n - y, i)$。
  
  然后，对于每个 $i$ 的加起来就是了，也就是说，答案为：
  
$$ \sum_{i=1}^{m} f(x - 1, i) \times f(n - x, m - i + 1) \times f(y-n-1, m - i + 1) \times f(2n - y, i) $$

提前 $O(n)$ 预处理阶乘和逆元，这题就解决了，情况 1 计算时间复杂度 $O(1)$，情况 2 是 $O(m)$，可以通过此题，代码就不贴了。

~~其实把 n 开到 1e9 也没啥呀，分块打表很香啊~~

---

## 作者：dengyaotriangle (赞：4)

我们首先要知道怎么快速计算 $S(n,m)$ 代表用 $[1,m]$ 中的正整数组成的长度为 $n$ 的非降序列个数

给出结论，$S(n,m)=\binom{n+m-1}{n}$ 或者用小学组合数的写法，$S(n,m)=\operatorname{C}_{n+m-1}^n$

原因？考虑一个长 $n+m-1$ 的操作序列，其中有 $n$ 个 `x` 操作，$m-1$ 个 `+` 操作

设一个数 $v$ ，初始 $v=1$，序列 $a$，初始为空。依次执行这个操作序列的每一项，若为 `+`，则 $v\gets v+1$ ，若为 $x$ ，则将 $v$ 加入到序列 $a$ 后面。

显然，这样构造的序列非降且长度为 $n$ 且每个数在 $[1,m]$ 之间，并且易证每一个序列唯一对应着一个操作序列。

所以我们对操作序列计数即可。显然一共 $n+m-1$ 个操作，我们选择其中 $n$ 个为 `x` （其它自然为 `+`），即 $n+m-1$ 中取 $n$ 个的方案数，即 $S(n,m)=\binom{n+m-1}{n}$ 

接下来就不是问题了

题目告诉我们两边分别是一个非降和非升序列，值域在$[1,m]$，而 $a_x=a_y$（$a$是任意一个合法序列）

我们分类讨论，若$x\leq n<y$， $x,y$ 在序列两边

又因为 $a_x=a_y$，我们考虑枚举 $a_x$

则对于 $a_x=a_y=k$，方案数为 $S(x-1,k)S(n-x,m-k+1)S(2n-y,k)S(y-(n+1),m-k+1)$

就是说，把序列分成四段，$[1,x-1],[x+1,n],[n+1,y-1],[y+1,2n]$，发现枚举了 $k$ 之后，可以确定它们中的元素的值域分别应该是 $[1,k],[k,m],[k,m],[1,k]$，且每个都是非降/非升序列，所以直接套用原来的公式。

否则，不妨设 $x<y\leq n$

我们发现右边完全没有限制，看左边。

依然枚举 $a_x=a_y=k$ 方案数为 $S(x-1,k)S(n-y,m-k+1)S(n,m)$

我们发现 $[x,y]$ 间的元素一定都 $=k$，考虑两侧，$[1,x-1],[y+1,n]$ 的值域分别为 $[1,k],[k,m]$。又因为右边完全没有限制，直接是 $S(n,m)$ 故得上式。


综上，预处理组合数 $O(n+m)$，枚举 $k$ 需要 $O(m)$ ，总复杂度 $O(n+m)$

---

## 作者：A_zjzj (赞：2)

一看，这个就是一个组合数学，如图所示
![A_zjzj](https://img-blog.csdnimg.cn/20200426132448426.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0Ffemp6ag==,size_16,color_FFFFFF,t_70)
这样，很容易想到分类讨论，如果$x,y$在两侧和$x,y$在同侧。

如果是两侧的话，就可以枚举这两个位置的高度然后用组合数算出来就可以了。然后的话如果在同侧就不用管什么东西，把第$x$个位置到第$y$个位置的所有位置都是一样高的，就可以看成一个城市，剩下的左边$x-1(x-n-1)$个，右边$n-y(2\times n-y)$个，加上中间的一个就是$x+n-y($两种刚好一样$)$，就直接算出来就可以了。

因为要组合数，所以我们一开始可以处理一下组合数，公式：$C_n^m=C_{n-1}^m+C_n^{m-1}$个，然后直接用就可以了，然后我们推一下有$x$个位置，可以选$y$种不同的高度的可能数，其实就是一个组合数$C_y^{x+1}$直接用即可。

复杂度$O(nm)$，得分$60$

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
int n,m,x,y;
int t;
int f[5005][5005];
int main(){
	scanf("%d%d%d%d",&m,&n,&x,&y);
	for(int i=1;i<=n+2;i++){
		f[i][1]=1;
		for(int j=2;j<=m+1;j++){
			f[i][j]=(f[i-1][j]+f[i][j-1])%mod;
		}
	}
	if(x<=n&&y>n){
		int ans=0;
		for(int i=1;i<=m;i++){
			ans=(ans+((ll)f[x][i]*f[n-x+1][m-i+1]%mod*f[y-n][m-i+1]%mod*f[n*2-y+1][i]%mod))%mod;
		}
		printf("%d",ans);
	}
	else{
		printf("%d",(ll)f[n+1][m]*f[x+n-y+1][m]%mod);
	}
	return 0;
}
```
然后，我们来谈谈$100$分的做法，因为这个组合数十分不好，复杂度太高，于是我们想到了这个式子$C_{n}^{m}=\frac{n!}{m!(n-m)!}$，那么我们就可以预处理出阶乘，可是这样是取模之后的结果，不能直接用来除，这里就要用到逆元的知识：

例如$ax\equiv1\pmod{b}$，其实就是求$a$关于$b$$(b$其实就是模数$)$的逆元$x$，因为$x\equiv x+kb\pmod{b}$

所以$ax\equiv1\pmod{b}$就相当于$ax+by\equiv1\pmod{b}$

我谔谔，这个不就是[扩展欧几里得算法](https://blog.csdn.net/A_zjzj/article/details/105675729)吗，直接求得$x$就好了，然后要注意最后要转换成正的。

逆元这个东西，其实是在取模运算中改变符号，就像实数取相反数和分数取倒数一样的，都是改变符号，一个数$a$关于$b$的逆元用$inv(a,b)$表示，所以原来的$C_{n}^{m}=\frac{n!}{m!(n-m)!}$就可以转换成$C_{n}^{m}=n!\times inv(m!,mod)\times inv((n-m)!,mod)\bmod mod$，这样只要处理出这个$inv$函数就可以了(前面说过)

```cpp
void exgcd(int a,int b,int &xx,int &yy){
	if(b==0){
		xx=1,yy=0;
		return;
	}
	exgcd(b,a%b,xx,yy);
	int t=xx;
	xx=yy;
	yy=t-a/b*yy;
}
int inv(int a){
	int xx,yy;
	exgcd(a,mod,xx,yy);
	return (xx%mod+mod)%mod;//转换成正的
}
```
复杂度$O(m\ log n)$，已经可以过了。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
int n,m,x,y;
int k[500001];
void exgcd(int a,int b,int &xx,int &yy){
	if(b==0){
		xx=1,yy=0;
		return;
	}
	exgcd(b,a%b,xx,yy);
	int t=xx;
	xx=yy;
	yy=t-a/b*yy;
}
int inv(int a){
	int xx,yy;
	exgcd(a,mod,xx,yy);
	return (xx%mod+mod)%mod;
}
int f(int xx,int yy){
	int a=inv(k[yy-1]),b=inv(k[xx]),p=k[xx+yy-1];
	return (ll)p*a%mod*b%mod;
}
int main(){
	scanf("%d%d%d%d",&m,&n,&x,&y);
	k[0]=1;
	for(int i=1;i<=500000;i++)k[i]=(ll)k[i-1]*i%mod;
	if(x<=n&&y>n){
		int ans=0;
		for(int i=1;i<=m;i++){
			ans=(ans+((ll)f(x-1,i)*f(n-x,m-i+1)%mod*f(y-n-1,m-i+1)%mod*f(n*2-y,i)%mod))%mod;
		}
		printf("%d",ans);
	}
	else{
		printf("%d",(ll)f(n,m)*f(x+n-y,m)%mod);
	}
	return 0;
}
```
如果还觉得太慢，可以考虑线性求逆元(模数相同)，用$inv_i$或$i^{-1}$表示$i$关于$p$的逆元，因为$p\bmod i+\lfloor\dfrac{p}{i}\rfloor\times i=p$

所以，设$a=p\bmod i,b=\lfloor\dfrac{p}{i}\rfloor$

则$a+b\times i=p$

$a+b\times i\equiv0\pmod{p}$

$b\times i\equiv-a\pmod{p}$

$i\equiv-\dfrac{a}{b}\pmod{p}$

$i^{-1}\equiv-\dfrac{b}{a}=-b\times a^{-1}\pmod{p}$

也就是$i$的逆元$inv(i)$就是$-\lfloor\dfrac{p}{i}\rfloor\times inv_{p\bmod i}\bmod p=(p-\lfloor\dfrac{p}{i}\rfloor)\times inv_{p\bmod i}\bmod p$

于是就可以线性求出逆元了，初始化：$inv_1=1$

```cpp
inv[1]=1;
for(int i=2;i<=n;i++)inv[i]=(long long)(p-p/i)*inv[p%i]%p;
```
然后，这题却要维护一个阶乘数组的逆元。

$n!=(n-1)!\times n$

所以$n!^{-1}=(n-1)!^{-1}\times n^{-1}$

然后，就可以先处理出$1$到$n$的逆元，然后就可以递推求出阶乘数组的逆元了。

## 代码

```cpp
#include<bits/stdc++.h>
#define f(x,y) ((long long)k[x+y-1]*invk[y-1]%mod*invk[x]%mod)
#define ll long long
#define mod 998244353
using namespace std;
int n,m,x,y;
int k[200001];
int inv[200001];
int invk[200001];
int main(){
	scanf("%d%d%d%d",&m,&n,&x,&y);
	register int i,ans=0;
	k[0]=inv[1]=invk[0]=1;
	for(i=2;i<=n+m;i++)inv[i]=((ll)mod-mod/i)*inv[mod%i]%mod;//处理1到n的逆元
	for(i=1;i<=n+m;i++)k[i]=(ll)k[i-1]*i%mod;//处理阶乘
	for(i=1;i<=n+m;i++)invk[i]=(ll)invk[i-1]*inv[i]%mod;//处理阶乘数组的逆元
	if(x<=n&&y>n){
		for(i=1;i<=m;i++)ans=(ans+((ll)f(x-1,i)*f(n-x,m-i+1)%mod*f(y-n-1,m-i+1)%mod*f(n*2-y,i)%mod))%mod;
		printf("%d",ans);
	}
	else{
		printf("%d",(ll)f(n,m)*f(x+n-y,m)%mod);
	}
	return 0;
}
```
# 谢谢--zhengjun

---

## 作者：YoOXiii (赞：2)

首先考虑单纯计算一个不减序列的方案数。利用一个常见的套路，把第$a_i$项的数加上$i$，就转化为严格单增序列，取值从$2$到$n+m$，方案数即为$C^{n}_{n+m-1}$，直接利用预处理阶乘逆元的组合数计算即可。

考虑如何处理$a_x=a_y$的情况。

如果在异侧，我们考虑直接枚举其值$k$。在$a_x$左右，都相当于前面所提到的“计算一个不减序列的方案数”，分别为$C^{x-1}_{x+k-2}$
以及$C^{n-x}_{n+m-x-k}$，对$a_y$也类似，直接利用组合数可以直接得出方案数，再全部相加即可，注意取模。

如果在同侧，则只有一个单调区间受到影响，另一个的贡献恒为$C^{n}_{n+m-1}$。同样枚举$k$，发现在$a_x,a_y$之间的高度一定相等，两边的方案数分别为$C^{x-1}_{x+k-2}$和$C^{n-y}_{n+m-y-k}$，用类似的方法计算即可。

详见代码。

```cpp
#include <iostream> 
#include <cstdio>

#define int long long int

using namespace std;

const int maxn=200005;
const int mod=998244353;

int m,n,x,y;
int jc[maxn];

inline void init() {
	jc[0]=1;
	for (int i=1;i<=m+n;i++) jc[i]=jc[i-1]*i%mod;
}

inline int power(int a,int b) {
	int ans=1;
	while (b) {
		if (b&1) ans*=a,ans%=mod;
		a*=a,a%=mod;
		b>>=1;
	}
	return ans;
}

inline int inv(int k) {
	return power(k,mod-2);
}

inline int C(int m,int n) {
    return ( (jc[m] * inv(jc[n]) % mod) * inv(jc[m-n]) ) % mod;
}

signed main() {
	cin >> m >> n >> x >> y;
	if (x>y) swap(x,y);
	init();
	int ans=0;
	if (x<=n && y>n) {
		y=2*n-y+1;
		for (int i=1;i<=m;i++) {
			int valx=i+x,valy=i+y;
			int tmp=1;
			tmp*=C(valx-2,x-1),tmp%=mod;
			tmp*=C(valy-2,y-1),tmp%=mod;
			tmp*=C(n+m-valx,n-x),tmp%=mod;
			tmp*=C(n+m-valy,n-y),tmp%=mod;
			ans+=tmp,ans%=mod;
		}
		printf("%lld",ans);
		return 0;
	}
	else {
		if (x>n) x-=n,y-=n;
		for (int i=1;i<=m;i++) {
			int valx=i+x,valy=i+y;
			int tmp=1;
			tmp*=C(valx-2,x-1),tmp%=mod;
			tmp*=C(n+m-valy,n-y),tmp%=mod;
			ans+=tmp,ans%=mod;
		} 
		ans*=C(n+m-1,n),ans%=mod;
		printf("%lld",ans);
		return 0;
	}
}
```


---

## 作者：Y_B_Y (赞：1)

这一题充分体现了我有多么菜$qwq$,逆元不会线性推,用exgcd直接算(虽然并没什么关系),公式不会用组合数知识推,靠非常naive的找规律才发现...

根据**题意**,我们可以知道,如果我们能快速的求出有$i$种数字选择,组成长度为$l$的不上升序列(由于不下降序列的种类也是一样所以这里只考虑一种),那么这一题只要分类讨论一下就可以很轻松的解决了

我们先来看$f[i][1]$,不难发现它为$i$(1到i都可以选),再来看$f[i][2]$,我们可以设第一个数字为$x(0<x≤i)$,所以第二个数字的选择等同于有$x$种数字选择长度为1的种类,所以种类数为,$f[i][2]=\sum_{x=1}^{i}f[x][1]$,不难得出$f[i][l]=\sum_{x=1}^{i}f[x][l-1]$,我们将$i=1,2,3,4,5,l=0,1,2,3,4$($f[i][0]$上文没提,不难知道其值为$1$)的值全部求出来,列成表,如下(第x行y列为$f[x][y-1]$)


```cpp
1 1 1  1  1
1 2 3  4  5
1 3 6  10 15
1 4 10 20 35
1 5 15 35 70
```

如果你侧着看它,你会发现它是一个杨辉三角(如下图),然后根据杨辉三角与组合数的关系,不难发现我们可以通过组合数快速求出$f[i][l]$的值

![](https://cdn.luogu.com.cn/upload/image_hosting/quz68k13.png)

通过观察可以发现,$f[i][1]$(第$i$行,第2列)对应的是$C_{i-1}^{1}$,我们将其往右移一格,移到$f[i][2]$的位置,可以发现其对应的是$C_{i}^{2}$(可以看图理解),多找几次规律,不难发现,$f[i][l]=C_{i+l-1}^{l}$,根据$C_{n}^{m}=\frac{n!}{m!(n-m)!}$,预处理一下阶乘和逆元(没学过,可以搜索乘法逆元)就可以快速求出$f[i][l]$了

然后现在来看怎么使用上面的结论,我们可以枚举x,y位置的楼房高度,然后分类讨论求出答案就可以了,再把每次枚举高度的答案加起来就可以了,如图

![](https://cdn.luogu.com.cn/upload/image_hosting/ocxkjo1v.png)

细节看代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e5,P=998244353;
ll ex,ey;
void exgcd(ll a,ll b,ll &ex,ll &ey)//ex
{
    if(!b){ex=1;ey=0;return;}
    exgcd(b,a%b,ey,ex),ey-=a/b*ex;
}
ll n,m,x,y,ans,sum,jc[4*N],njc[4*N];
ll c(ll x,ll y){return jc[x]%P*njc[y]%P*njc[x-y]%P;}
ll f(ll x,ll y){return x>=0?c(x+y-1,y)%P:0;}
int main()
{
	cin>>m>>n>>x>>y;
	if(x>y) swap(x,y);
	jc[0]=njc[0]=1;
	for(int i=1;i<=2*n+m+1;i++) jc[i]=(jc[i-1]*i)%P;
	for(int i=1;i<=2*n+m+1;i++)
	{
		exgcd(jc[i],P,ex,ey);
		njc[i]=(ex+P)%P;
	}
	for(int i=1;i<=m;i++)
	{
		ans=1;
		if(x<=n) //x在左侧
		{
		    if(x-1>0) ans=(ans*f(i,x-1))%P;
		    if(y<=n) //y也在左侧
			{
			   if(n-y>0) ans=ans*f(m-i+1,n-y)%P;
			   ans=ans*f(m,n)%P;
			}
		    else //不在
		    {
		    	if(n-x>0) ans=(ans*f(m-i+1,n-x))%P;
		    	if(y-n-1>0) ans=(ans*f(m-i+1,y-n-1))%P;
		    	if(2*n-y>0) ans=(ans*f(i,2*n-y))%P;
			}
	    }
		else//x在右侧
		{
        //由于x在右侧时,y肯定在右侧所以无需判断
			ans=(ans*f(m,n))%P;
			if(x-n-1>0) ans=(ans*f(m-i+1,x-n-1))%P;
			if(2*n-y>0) ans=(ans*(f(i,2*n-y)))%P;
		}
		sum=(sum+ans)%P;//累加
	}
	return printf("%lld",sum%P),0;//输出
}
```




---

