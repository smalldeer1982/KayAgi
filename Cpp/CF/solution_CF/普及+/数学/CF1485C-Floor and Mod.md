# Floor and Mod

## 题目描述

A pair of positive integers $ (a,b) $ is called special if $ \lfloor \frac{a}{b} \rfloor = a \bmod b $ . Here, $ \lfloor \frac{a}{b} \rfloor $ is the result of the integer division between $ a $ and $ b $ , while $ a \bmod b $ is its remainder.

You are given two integers $ x $ and $ y $ . Find the number of special pairs $ (a,b) $ such that $ 1\leq a \leq x $ and $ 1 \leq b \leq y $ .

## 说明/提示

In the first test case, the only special pair is $ (3, 2) $ .

In the second test case, there are no special pairs.

In the third test case, there are two special pairs: $ (3, 2) $ and $ (4, 3) $ .

## 样例 #1

### 输入

```
9
3 4
2 100
4 3
50 3
12 4
69 420
12345 6789
123456 789
12345678 9```

### 输出

```
1
0
2
3
5
141
53384
160909
36```

# 题解

## 作者：fanfansann (赞：13)

整套题目全部题解链接：[Codeforces Round #701 (Div. 2) A ~ F ，6题全，超高质量良心题解【每日亿题】2021/2/13](https://fanfansann.blog.csdn.net/article/details/113799739) 


## C - Floor and Mod
**Problem C Floor and Mod**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210213140030922.png)

**Translation**

定义一对数 $(a,b)$ 是特殊的，当且仅当 $\lfloor\dfrac{a}{b}\rfloor=a\bmod b$

给定 $x$ 和 $y$ ，求一共有多少对特殊的数 $(a,b)$ ，当  $1\le a\le x,1\le b\le y$。 

**Solution**


~~签到题~~  

看数据范围，显然这是一个结论题或者 $O(\sqrt n)$ 枚举题，我们根据题目中给定的柿子：

$$\begin{aligned}&\lfloor\dfrac{a}{b}\rfloor=a \bmod b &\\&
 \lfloor\dfrac{a}{b}\rfloor=a-\lfloor\dfrac{a}{b}\rfloor\times b&\\&
 a=\lfloor\dfrac{a}{b}\rfloor\times (b+1)&\\&
 \dfrac{a}{b+1}=\lfloor\dfrac{a}{b}\rfloor\end{aligned}$$

因为$\lfloor\dfrac{a}{b}\rfloor$ 一定是整数，所以 $\dfrac{a}{b+1}$ 一定是整数，所以 $b+1\ |\ a$。

所以一个很直观的想法就是枚举 $b$ ，对于每一个 $b$ ， $b+1$ 的倍数 $a$ 显然有 $\dfrac{x}{b+1}$ 个，显然可以整除分块。

但是需要注意题目中的给定的条件为 $\lfloor\dfrac{a}{b}\rfloor=a\bmod b$

即： $\lfloor\dfrac{a}{b}\rfloor<b$ 

即：$\dfrac{a}{b+1}<b\Rightarrow a<b^2+b$

即 $a\in [0,b^2+b-1]$。那么符合题意的 $a$ 的个数就是： $\dfrac { b^2+b-1}{b+1}$ 

并且 $a$ 的上限是 $x$，故最终的答案为：
 
$$\sum\limits_{b=1}^{y} ans = \dfrac {\min \{x, b^2+b-1\}}{b+1}$$

我们可以先枚举 $b<\sqrt x$ ，计算 $\dfrac { b^2+b-1}{b+1}$ 

剩余的 $b=\sqrt x \sim y$，显然 ${\min\{x, b^2+b-1\}}=x$，直接整除分块即可，其中整除分块的时候，我们需要计算的是 $\lfloor \dfrac{x}{b+1}\rfloor$，我们令 $l,r$ 代表 $b+1$ 即可。
 
时间复杂度 $O(\sqrt x)$

**Code**

```cpp
// Problem: C. Floor and Mod
// Contest: Codeforces - Codeforces Round #701 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1485/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e5 + 7;

int n, m, t;
int x, y;

int main()
{
	scanf("%d", &t);
	while(t -- ) {
		scanf("%d%d", &x, &y);
		int a = 1, b = 1;
		ll ans = 0;
		for(; b * b + b - 1 < x && b <= y; ++ b) 
			ans += (b * b + b - 1) / (b + 1);	   

		int l = b + 1, r;  
		for(; l <= x && l <= y + 1; l = r + 1) {
			r = min(x / (x / l), y + 1);
			ans += x / l * (r - l + 1); 
			if(r == y + 1) break;
		} 
		cout << ans << endl;
	}		
	return 0;
}
```

---

## 作者：7KByte (赞：6)

求满足 $a\ \bmod b \ =\ \left\lfloor\dfrac{a}{b}\right\rfloor$ 的正整数对 $(a,b)$ 数量。

不难发现满足条件的 $(a,b)$中 $a\bmod b$ 不超过$\sqrt{a}$ 。

所以我们枚举 $k= a \bmod b$，不难发现有$\min\{b,\dfrac{a-k}{k}\}-k$对$(a,b)$，累加一下即可。

时间复杂度$O(T\sqrt a)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
using namespace std;
void solve(){
	int a,b;scanf("%d%d",&a,&b);
	long long ans=0;
	rep(k,1,sqrt(a))ans+=max(0,min(b,(a-k)/k)-k);
	printf("%lld\n",ans);
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：WydnksqhbD (赞：2)

# [CF1485C Floor and Mod](https://www.luogu.com.cn/problem/CF1485C) 题解
## 题目大意
给定 $x,y$，求所有 $1\le a\le x,1\le b\le y$ 且 $\lfloor\frac{a}{b}\rfloor=a\bmod b$ 的数对 $(a,b)$ 个数。
## 思路
设 $\lfloor\frac{a}{b}\rfloor=a\bmod b=k$，则 $1\le k<b$。

有 $a=kb+b$。

由于 $b>k$，$a=kb+b\ge k(k+1)+k+1=k^2+2k+1=(k+1)^2>k^2$。

故 $k<\sqrt{x}$。枚举 $k$，确定 $b,a$ 即可。

所以
$$\text{ans}=\sum_{k=1}^{\sqrt{x}-1}\max\{0,\min\{\frac{x-k}{k},y\}\}$$
## 代码
不开 `long long` 见祖宗。
```cpp
# include <bits/stdc++.h>
# define int long long
int max ( int a , int b ) { return a > b ? a : b ; }
int min ( int a , int b ) { return a < b ? a : b ; }
inline void solve ( )
{
	int x , y , ans = 0 ;
	std :: cin >> x >> y ;
	for ( int i = 1 ; i * i < x ; i ++ )
		ans += max ( 0 , min ( ( x - i ) / i , y ) - i ) ;
	std :: cout << ans << std :: endl ;
}
signed main ( )
{
	std :: ios :: sync_with_stdio ( 0 ) ;
	std :: cin . tie ( 0 ) ;
	std :: cout . tie ( 0 ) ;
	int t ;
	std :: cin >> t ;
	while ( t -- ) solve ( ) ;
	return 0 ;
}
```

---

## 作者：xrk2006 (赞：2)

 # 【题解】CF1485C Floor and Mod
 
[博客园食用效果更佳](https://www.cnblogs.com/xrkforces/p/CF1485C.html)

emmm……NOIP 考前两周，跟 CSP 考前一样（虽然最后并没有去考），写篇题解增加以下 RP（雾）。

提供一篇思路大体和题解区相同但用了二分写法的题解。

## 题目链接

[CF1485C Floor and Mod](https://www.luogu.com.cn/problem/CF1485C)

## 题意概述

求 $1\le a\le x,1\le b\le y$ 且 $\lfloor\frac{a}{b}\rfloor =a\bmod b$ 的 $(a,b)$ 个数。

## 数据范围

- $1 \le x,y \le 10^9$

## 思路分析

首先我们设 $\left\lfloor \dfrac{a}{b}\right \rfloor=k$，则：$a=bk+k=k(b+1)$。也就是说 $a$ 是 $b+1$ 的倍数。

那么题意转化为：

> 在 $[1,x]$ 里找一个 $a$，在 $[1,y]$ 里找一个 $b$，满足 $a$ 是 $b+1$ 的倍数，问有多少对这样的 $(a,b)$。

那么我们考虑对于 $[1,y]$ 里的每一个 $b$，$[1,x]$ 中有多少个 $a$ 满足题意。其实就相当于问 $[1,x]$ 中有多少个 $b+1$ 的倍数，显然有 $\left\lfloor\dfrac{x}{b+1}\right\rfloor$ 个。

那么总的答案就为 
$$
 \sum \limits_{i=1}^y \left\lfloor\frac{x}{i+1}\right\rfloor=\sum \limits_{i=2}^{y+1}  \left\lfloor\frac{x}{i}\right\rfloor
$$
那么可以直接整除分块解决。

~~结果我写完发现样例都过不了。。~~所以显然是有问题的。

我们发现 $b$ 首先不能为 $1$，因为任何数是 $1$ 的倍数，而任何数除以 $1$ 不可能为 $0$。

所以我们的下界应该从 $3$ 开始。

其次，在 $a=bk+k=k(b+1)$ 中，我们忽略了一个重要条件，$k$ 在这里相当于 $a\bmod b$，是余数，而余数不能大于等于除数，即 $k<b$。

所以对于 $[3,y]$ 的每一个 $b$，其实只有 $\left \lfloor \dfrac{a}{b+1}\right\rfloor<b$ 的 $a$ 才满足题意。

那么这样的 $a$ 在 $[1,x]$ 中有 $\left\lfloor\dfrac{\min(b+1)(b-1),x}{b+1}\right\rfloor$ 个。

那么整个答案就为：
$$
 \begin{aligned}\sum \limits_{i=2}^y\left\lfloor\dfrac{\min((i+1)(i-1),x)}  {i+1}\right\rfloor&=\sum \limits_{i=3}^{y+1}\left\lfloor\dfrac{\min(i(i-2),x)}  {i}\right\rfloor\\&=\sum \limits_{i=3}^{lim} (i-2)+ \sum \limits_{i=lim+1}^{y+1}\left\lfloor  \dfrac{x}{i}\right\rfloor\\&=\frac{(1+lim-2)\times(lim-3+1)}{2}+\sum  \limits_{i=lim+1}^{y+1}\left\lfloor\dfrac{x}{i}\right\rfloor\end{aligned}
$$
其中 $lim$ 表示的是使得 $i\times(i-2)\le x$ 的最后一个 $i$。

那么 $lim$ 直接枚举/解不等式/二分都可，我这里采用的是二分。

最后的式子中，第一项显然可以 $O(1)$ 求出，第二项显然可以整除分块，于是整道题成功解决。

时间复杂度：$O(T(\log y+\sqrt y))$。

## 易错点

没啥细节，只是需要开 long long。

## 代码实现

```cpp
//CF1485C
#include<iostream>
#include<cstdio>
#include<cmath>
#define int long long
using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int work(int n,int k,int lim)
{
	int ret=0;
	for(int l=lim,r;l<=n;l=r+1)
	{
		if(k/l==0)break;
		r=min(k/(k/l),n);
		ret+=(k/l)*(r-l+1);
	}
	return ret;
}

signed main()
{
	int T;
	T=read();
	while(T--)
	{
		int x,y;
		x=read();y=read();
		int now=0;
		for(int step=(1ll<<30);step>=1;step>>=1)
		{
			if(now+step<=(y+1)&&(now+step)*(now+step-2)<=x)now+=step;
		}
		int lim=now;
		cout<<(lim-2)*(lim-1)/2+work(y+1,x,lim+1)<<'\n';
	}
}
```



---

## 作者：Azazеl (赞：2)

#### 题意
> $\ \ \ \ $ 求 $1\leq a\leq x$,$1\leq b\leq y$ 且 $\lfloor \dfrac{a}{b} \rfloor=a \bmod b$ 的组数。

---
#### 题解
这里提供一个不用整除分块的找规律做法。  

首先先打一个暴力，找一下满足最后一个式子的 $a$ 和 $b$ 的关系，为了直观，我们把 $a$ 作为 $x$，$b$ 作为 $y$ 描点连线。  

![](https://cdn.luogu.com.cn/upload/image_hosting/vwsbk1u9.png)

仔细观察，其实就是若干条  
$$y=\dfrac{1}{k}x-1(k\times (k+1)<x)$$
的直线，其中 $k$ 为正整数。  

所以我们就变成了数 $(0,0)$ 为左下角，$(x,y)$ 为右上角的矩形中该函数整点个数。  

那么枚举每条函数，判断是否出界后选择 $x$ 和 $y$ 的极值去计算界限，选择均符合的一个计算即可。 

---
#### 代码  
记得开 `long long`
```cpp
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
int main() {
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int x,y;
		ll Ans=0;
		scanf("%d %d",&x,&y);
		for(int i=1;i<=x;i++)
		{
			if(i*(i+1)>x) break;
			double bj1=1.0/i*x-1,bj2=(y+1)*i;
			if(bj1<=y) Ans+=(x-i*(i+1))/i;
			else if(bj2<=x&&bj2>=i*(i+1))Ans+=(bj2-i*(i+1))/i;
			
		}
		printf("%lld\n",Ans);
	}
	return 0;
}
```


---

## 作者：Daidly (赞：1)

> $T$ 组给定 $x,y$ 求 $1\leq a\leq x,1\leq b\leq y$ 且满足 $\lfloor\frac{a}{b}\rfloor=a\bmod b$ 的数对个数。$T\leq 100,x,y\leq 10^9$

推一下式子就可以得到 $\lfloor\frac{a}{b}\rfloor=\frac{a}{b+1}$，记 $i=\lfloor\frac{a}{b}\rfloor=\frac{a}{b+1}$，则 $a=i(b+1)$。

由 $i=\lfloor\frac{a}{b}\rfloor$ 得 $ib\leq a\leq (i+1)b-1$，即 $ib\leq i(b+1)\leq (i+1)b-1$，则 $i+1\leq b$。

假设我们枚举 $i$，然后枚举 $b$，对于 $i+1\leq b\leq y$ 的 $y-i$ 个 $b$，都有一个 $a$ 能与其满足条件。

这样的 $a=(i+2)i,(i+3)i,\cdots ,x$，一共有 $\lfloor\frac{x}{i}\rfloor-i-1$ 个。

对于 $i$，需要满足 $y-i>0$ 且 $\lfloor\frac{x}{i}\rfloor-i-1>0$ 并在其中取 $\min$。

准确计算出 $i$ 的范围并在其中整除分块即可，注意整除分块计算右端点代入的是 $x$，而并不是 $i$ 的最大值。

代码如下：

```cpp
#define int long long
void solve(){
	x=read(),y=read();
	int ans=0,n=min(y-1,((int)sqrt(4*x+1)-1)/2);
    for(int l=1,r;l<=n;l=r+1){
        r=min(x/(x/l),n);
        ans+=(r-l+1)*min(x/l-1,y)-(l+r)*(r-l+1)/2;
    }
	print(ans),puts("");
}
```



---

## 作者：spider_oyster (赞：1)

我们直接拆式子：

$\lfloor \frac{a}{b} \rfloor=a$ $mod$ $b$；

$\lfloor \frac{a}{b} \rfloor=a-\lfloor \frac{a}{b} \rfloor\times b$；

$\lfloor \frac{a}{b} \rfloor=\frac{a}{b+1}$。

------------

此时可以发现 $b+1|a$ ，然后商的范围是 $0\leq \frac{a}{b+1} <b $。

把上面式子整理一下：$0\leq a< b^2+b$；

因为 $a,b$ 都是整数，于是：$0\leq a\leq  b^2+b-1$。

我们枚举 $b$，当前 $a$ 的个数就是 $\lfloor \frac{min_{b^2+b-1,x}}{b+1} \rfloor$，取 $min$ 因为 $a\in [1,x]$。

------------

这个式子不好求，我们考虑把他拆开。

因为 $b-1 \geq 0$，所以我们可以把这一坨去掉（意 * 一下），$b \leq \sqrt x$ 时 $b^2+b-1 \leq x$。

答案为：$\sum_{b=1}^{\sqrt x} \frac{b^2+b-1}{b+1}+\sum_{\sqrt x}^{y}\frac{x}{b+1}$，前面暴力枚举，后面这一坨整除分块即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

void solve()
{
	ll x,y;cin>>x>>y;
	ll ans=0,b;
	for(b=1;b*b+b-1<=x&&b<=y;b++)
		ans+=(b*b+b-1)/(b+1);
	for(ll l=b,r;l<=y&&l<x;l=r+1)
	{
		r=min(x/(x/(l+1))-1,y);
		ans+=x/(l+1)*(r-l+1);
	}
	cout<<ans<<endl;
}

int main()
{
	int t;cin>>t;
	while(t--) solve(); 
}
```


---

## 作者：11D_Beyonder (赞：1)

### Idea
&emsp;&emsp;令 $a=kb+m$，有 $k,m\in\mathbb N$，且 $k\geq 0,0\leq m<b$；那么 $\left\lfloor\frac{a}{b}\right\rfloor=k=m$，将 $k$ 用 $m$ 代替，得到 $a=(b+1)m$；可以看到，$m=0$ 是不可行的。

&emsp;&emsp;首先枚举 $b$，已知 $1\leq b\leq y$。当 $b$ 确定时，枚举 $m$，可得 $a$；已知 $1\leq a\leq x$，故得到不等式组 $1\leq m<b$ 和 $1\leq (b+1)m\leq x$。

&emsp;&emsp;显然，$m$ 的上限值为 $\min\left(\left\lfloor\frac{x}{b+1}\right\rfloor,b-1\right)$。

&emsp;&emsp;综上所述，答案为 $\sum\limits_{b=1}^y\min\left(\left\lfloor\frac{x}{b+1}\right\rfloor,b-1\right)$。

&emsp;&emsp;令 $\frac{x}{b+1}\le b-1$，得到 $b\ge\sqrt{x+1}$；可知 $\sqrt{x+1}$ 附近有 $B$，是满足 $\left\lfloor\frac{x}{b+1}\right\rfloor\le b-1$ 最小的 $b$。

&emsp;&emsp;$\begin{aligned}\text{answer}&=(0+1+2\cdots +B-2)+\left(\left\lfloor\frac{x}{B+1}\right\rfloor+\left\lfloor\frac{x}{B+2}\right\rfloor+\cdots+\left\lfloor\frac{x}{y+1}\right\rfloor\right)\\&=\sum\limits_{i=1}^{B-2}i+\sum\limits_{i=B+1}^{y+1}\left\lfloor\frac{x}{i}\right\rfloor\end{aligned}$

&emsp;&emsp;求等差数列和数论分块。

### Code 

```cpp
/******************************************************************
Copyright: 11D_Beyonder All Rights Reserved
Author: 11D_Beyonder
Problem ID: CF1485C
Date: 2021 Feb. 28th
Description: Number Theory, Counting
*******************************************************************/
#include<cmath>
#include<iostream>
using namespace std;
typedef long long ll;
const int N=100005;
int _;
int main(){
	for(cin>>_;_;_--){
		ll x,y;
		cin>>x>>y;
		ll B=sqrt(x+1);
		while(x/(B+1)>B-1){
			//找到取x/(B+1)的临界值
			B++;
		}
		ll ans=0;
		if(B-1>y){
			//全都取b-1
			ans+=y*(y-1)/2;
		}else{
			ans+=(B-1)*(B-2)/2;
		}
		for(ll l=B+1,r;l<=y+1;l=r+1){
			if(l>x){
				//除数为0
				break;
			}
			r=min(x/(x/l),y+1);
			ans+=(x/l)*(r-l+1);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：wgyhm (赞：1)

## C. Floor and Mod

### 题意

* $T$ 组询问，每次给出两个整数 $x,y,1\le x,y\le 10^9$ ，求共有多少整数对 $(a,b),1\le a\le x,1\le b\le y$ ，满足 $\left\lfloor\dfrac{a}{b}\right\rfloor=a\bmod b$。

### 题解

不妨设 $a=br+r=(b+1)r,0\le r<b$

有 $r=\dfrac{a}{b+1}$ 。

因为 $r$ 必须为整数。不妨枚举 $b+1$ ，$sum=\sum\limits_{i=2}^{y+1}\left\lfloor\dfrac{x}{i}\right\rfloor$。

显然是不正确的，因为没有考虑到 $r<b$ ，所以有 $a<b(b+1),a\le b^2$。

所以 $sum=\sum\limits_{i=2}^{y+1}\min\{\left\lfloor\dfrac{x}{i}\right\rfloor,\left\lfloor\dfrac{(i-1)^2}{i}\right\rfloor\}=\sum\limits_{i=2}^{y+1}\left\lfloor\dfrac{\min\{x,(i-1)^2\}}{i}\right\rfloor$。
找到 $(i-1)^2\le x,i^2>x$ 的 $i$ ，之前的用暴力解决，之后的用数论分块。

复杂度 $O(T(x^{\frac{1}{2}}+y^{\frac{1}{2}}))$。

### Code

写的有点奇怪。。。（缩进可能有点出问题了将就着看吧）。

```cpp
inline int solve(int x,int y){
    rg int l,r,ans=0;y--;
    for(l=1,r;l<=y+1;l=r+1) {
        if (x/l) r=min(y+1,x/(x/l));
        else r=y+1;
        ans+=(x/l)*(r-l+1);
    }
    return ans;
}
inline void work(void){
    rg int i,x,y,l,r,ans=0;
    read(x);read(y);
    for (i=2;(i-1)*(i-1)<=x&&i<=y+1;i++) ans+=(i-1)*(i-1)/i;
    printf("%lld\n",ans-solve(x,i-1)+solve(x,y+1));
}
signed main(){
    rg int T;
    read(T);
    while (T--) work();
    return 0;
}
```

完整题解 [Codeforces Round #701](https://www.luogu.com.cn/blog/51569/codeforces-round-701-post)。

---

## 作者：cppcppcpp3 (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1485C)

设 $\lfloor \frac{a}{b} \rfloor=a \bmod b=r$，则 $a=\lfloor\frac{a}{b}\rfloor b+a\bmod b=r(b+1)$，其中 $r \in [0,b-1]$。那么数 $b$ 就对应 $\min(b-1,\lfloor \frac{x}{b+1}\rfloor)$ 个 $a$。因此答案为 $\sum_{b=1}^y\min(b-1,\lfloor \frac{x}{b+1}\rfloor)$，分段计算：

- 所有 $\le \sqrt{x+1}$ 的 $b$ 的贡献：$\sum_{b=1}^{\lfloor \sqrt{x+1} \rfloor} (b-1)=\frac{\lfloor \sqrt{x+1} \rfloor\lfloor \sqrt{x+1}-1 \rfloor}{2}$。

- 所有 $> \sqrt{x+1}$ 的 $b$ 的贡献，$\sum_{b=\lfloor \sqrt{x+1} \rfloor}^{y}\lfloor \frac{x}{b+1}\rfloor$，整除分块算出 $\sum_{i=1}^{y+1} \lfloor \frac{x}{i}\rfloor$ 和 $\sum_{i=1}^{\lfloor \sqrt{x+1} \rfloor+1} \lfloor \frac{x}{i}\rfloor$，相减即可。

时间复杂度 $O(T\sqrt x)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,m,as;

int calc(int n,int m){
	int as=0;
	for(int l=1,r;l<=min(n,m);l=r+1){
		r=min(m,n/(n/l));
		as+=(r-l+1)*(n/l);
	}
	return as;
}

void solve(){
	n=wrd(),m=wrd();
	if(m*m-1<=n) return printf("%lld\n",m*(m-1)/2),void();
	int t=sqrt(n+1);
	as=t*(t-1)/2+calc(n,m+1)-calc(n,t+1);
	printf("%lld\n",as);
}

signed main(){
	int T=wrd();
	while(T--) solve();
	return 0;
}
```

---

## 作者：__yun__ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1485C)  
### 结论
答案：
$$\sum_{i=1}^{min\{\sqrt{x},y\}} \max\{\min\{y,\frac{x-i}{i}\}-i,0\}$$

### 证明
设  $\lfloor \frac{a}{b}  \rfloor = a \bmod b = k$，那么 $a=kb+k$。

$\because b>k$  
$\therefore bk>k^2$  
$\therefore bk+k>k^2$  
$\text{即} \ a>k^2$  
$\therefore k< \sqrt{a}$  
$\text{又} \because a<= x$  
$\therefore k<\sqrt{x}$  
$\text{又}\because 0\leq k < b \ ,b\leq y,k=0 \text{时一定不合法}$  
$\therefore 1\leq k \leq min\{\sqrt{x},y\}$

$\because a=bk+k$  
$\therefore b=\frac{a-k}{k}$  
$\text{又}\because a\leq x,k<b,b \leq y$  
$\therefore k < b \leq \min\{\frac{x-k}{k},y\}$  
$\therefore \text{当}a\bmod b=k\text{时},\text{有} \max\{\min\{y,\frac{x-k}{k}\}-k,0\}\text{组解符合题意}$

### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x,y,ans;
signed main(){
	int t;
	cin>>t;
	while(t--){
		ans=0;
		cin>>x>>y;
		for(int i=1;i<=min((int)sqrt(x),y);i++){
			ans+=max(min(y,(x-i)/i)-i,0ll);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：User_Authorized (赞：0)

**[更好的阅读体验](https://www.cnblogs.com/User-Unauthorized/p/solution-CF1485C.html)**

## 题面
给定 $x, y$，求

$$\sum\limits_{a = 1}^{x} \sum\limits_{b = 1}^{y} \left[\left\lfloor\dfrac{a}{b}\right\rfloor = a \bmod b\right]$$

（$1 \le x, y \le 10^9, 1 \le T \le 100$）。

## 题解
考虑钦定 $\left\lfloor\dfrac{a}{b}\right\rfloor = a \bmod b = k$，那么有

$$b \cdot k + k = a \Leftrightarrow b + 1 = \dfrac{a}{k}$$

因为有 $k = a \bmod b$，所以 $k < b$，结合上式，可得

$$k < \dfrac{a}{k} - 1 \Leftrightarrow k \left(k + 1\right) = a$$

所以 $k$ 的取值是 $\sqrt{x}$ 级别的，考虑枚举 $k$ 的值并计算符合 $\left\lfloor\dfrac{a}{b}\right\rfloor = a \bmod b = k$ 的数对 $\left(a, b\right)$ 个数。

首先根据上文等式可得 $b = \dfrac{a}{k} - 1$，该条件对 $b$ 的限制为 $b \in \left[1, \left\lfloor\dfrac{x}{k}\right\rfloor\right)$。再考虑到有 $k < b \Rightarrow b > k$，综上可得 $b$ 的取值范围为 $\left(k, \left\lfloor\dfrac{x}{k}\right\rfloor\right) \cap \left[1,Y\right]$，$\mathcal{O}(1)$ 计算即可。总复杂度为 $\mathcal{O}(T \sqrt{x})$，可以通过本题。

## Code

```cpp
//Codeforces - 1485C
#include <bits/stdc++.h>

typedef long long valueType;

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType X, Y;

        std::cin >> X >> Y;

        valueType ans = 0;

        for (valueType i = 1; i * (i + 1) < X && i < Y; ++i) {
            ans += std::min(X / i - 1, Y) - i;
        }

        std::cout << ans << '\n';
    }

    std::cout << std::flush;

    return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

一个经典的结论是 $\lfloor\frac{a}{b}\rfloor =a\bmod b=a-b\lfloor\frac{a}{b}\rfloor$。

即 $\dfrac a {b+1}=\lfloor\frac{a}{b}\rfloor$，显然 $b+1\mid a$。

又因为 $a\bmod b<b$，则 $\dfrac a{b+1}<b$，$a<b^2+b$。

结合简单的不等式知识可以得到 $0\le a\le b^2+b-1$。

结合上面推出的结论，$b+1\mid a$，则对于这个 $b$ 存在的答案数为 $\dfrac {\min(x,b^2+b-1)} {b+1}$。

对于 $b^2+b-1< x$，嗯枚举，对于 $b^2+b-1\ge x$，整除分块即可。

安利一下正在写的[博客](https://www.luogu.com.cn/blog/Etinorally/zheng-chu-fen-kuai)。

```cpp
#include <iostream>
using namespace std;
using ll=long long;
#define rep(i,l,r) for(i=l;i<=r;++i)
inline ll solve(ll x,ll y)
{
	ll ret=0,l,r,i;
	for(i=1;i*i+i-1<x && i<=y;++i)
		ret+=(i*i+i-1)/(i+1);
	for(l=i+1;l<=x && l<=y+1;l=r+1)
	{
		r=min(x/(x/l),y+1);
		ret+=(r-l+1)*(x/l);
	}
	return ret;
}
int main()
{   ll x,y;
    ios::sync_with_stdio(false);
    cin.tie(0);int t;
    cin>>t;
    while(t--)
    {
	    cin>>x>>y;
    	cout<<solve(x,y)<<endl;
    }
}
```


---

## 作者：Doubeecat (赞：0)

> [C. Floor and Mod](https://codeforces.ml/contest/1485/problem/C)
> 
> 定义一对数 $(a,b)$是漂亮的，有 $\lfloor\frac{a}{b}\rfloor = a \mod b$，求 $1\le a \le x, 1 \le b \le y$ 中有多少对 $(a,b)\$是漂亮的。
> 
> $x,y \leq 10^9$

## Solution:

首先我们把式子化简一下：

$$
\begin{aligned}
    \lfloor\frac{a}{b}\rfloor &= a \mod b\\
    \lfloor\frac{a}{b}\rfloor &= a - (\lfloor\frac{a}{b}\rfloor * b)\\
    (b+1) \lfloor\frac{a}{b}\rfloor &= a \\
    \lfloor\frac{a}{b}\rfloor &= \frac{a}{b+1} = k\\
\end{aligned}
$$

得 $a = kb + k(k < b)$ ，并且注意到，如果没有限制的话，实际上会有 $b-1$ 组解。

所以我们可以枚举这个 $b$ ，得
$$
\sum_{i=2}^y \min(i-1,\frac{x}{i+1})
$$

然后我们把这个 $\min$ 拆开，找到中间点 $i = \sqrt{x+1}$，最后得到这个式子

$$
\sum_{i=2}^{\sqrt{x+1}} i-1 + \sum_{i=\sqrt{x+1}+1}^y \frac{x}{i+1}
$$

前面暴力计算即可，后面数论分块。

但是这边的数论分块形式并不像我们平常见到的 $\sum_{i=1}^n \frac{x}{i}$，所以我们可以稍加处理一下代码，变成：

```cpp
for (;l <= x && l-1 <= y; l = r + 1) {
    r = x/(x/l);
        if (r <= y + 1) ans += (r - l + 1) * (x / l);
        else break;
    }
    if (l <= x) {
        r = y + 1;ans += (r - l + 1) * (x / l);
}
```

Code:

```cpp
void solve() {
    ll l,r;ans = 0;
    read(x,y);
    for (l = 1;l * l + l - 1 <= x && l <= y;++l) {
        ans += (l * l + l - 1) / (l+1);
    }
    ++l;
    for (;l <= x && l-1 <= y; l = r + 1) {
        r = x/(x/l);
        if (r <= y + 1) ans += (r - l + 1) * (x / l);
        else break;
    }
    if (l <= x) {
        r = y + 1;ans += (r - l + 1) * (x / l);
    }

    printf("%lld\n",ans);
}
```

---

## 作者：xh39 (赞：0)

## 翻译

翻译:求 $a/b==a\%m$ 的正整数解的个数,并保证 $a<=x,b<=y$。(```/```表示整除,```%```表示取余)。

输入:多组数据,第 $1$ 行 $1$ 个整数 $t$ 表示数据组数,接下来 $t$ 行每行 $2$ 个正整数 $a,b$。

输出:$t$ 行每行 $1$ 个整数表示方程正整数解的个数。

数据范围:$1<=t<=100;1<=a,b<=10^{9}$。

## 正解

数学基础:初一下,一元一次不等式。算法要求:无,学完了基本语言,会for循环即可。

发现所有可以写成 $\frac{a(b+1)}{b}$ 且 $a>b$ 的分数都可以满足要求。

所有就是要求解不等式组 $\{^{a(b+1)<=x}_{^{b<=y}_{a>b}}$ 的正整数解的个数。

因为 $a>b$,所以 $a$ 只需要枚举到 $\sqrt{x}$ 就可以了。枚举完 $a$ 就变成了一元一次不等式组,这里就不演示怎么解了,解得 $a<b<=\frac{x-a}{a}$ 且 $b<=y$。
```cpp
#include<iostream>
#include<cmath>
using namespace std;
void Main(){
	long long x,y,sqrtx,sum=0,l,r,a,b;
	cin>>x>>y;
	sqrtx=sqrt(x);
	for(a=sqrtx;a>=1;a--){
		l=a+1ll;
		r=min(y,(x-a)/a); //同时小于两个东西则取最小值。
		sum+=max(0ll,r-l+1ll); //l>r则说明没有,但最少也有0个,不能统计负数,与0取最大值。
	}
	cout<<sum<<endl;
	return;
}
int main(){
	long long t,i;
	cin>>t;
	for(i=0;i<t;i++){
		Main();
	}
	return 0;
}
```

---

