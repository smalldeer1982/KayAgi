# [Math×Girl] 距离

## 题目背景

>“哥哥，你说什么呢？” 尤里问道。  
>“看上去仙女座也在研究数学。”我回答道。  
>“那里也有图书室吗？”泰朵拉微笑道。  
>“以居住的星球为模，是不是存在跟我们同余的宇宙人呢？”米尔嘉说道。


## 题目描述

给你两个数 $a$ 和 $b$ ，每次可以对任意一个数 $\pm1$。  
求最少进行多少次操作，才能使 $a\mid b$ 或 $b\mid a$。

其中 $\mid$ 为整除符号，$a\mid b$ 表示 $a$ 整除 $b$。  


## 说明/提示

### 样例解释

第一个例子为 $(15+1)\mid(33-1)$。  
第二个例子为 $(34+1)\mid(2024+6)$。  

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $15$ | $a,b\in[1,10^4]$ |
| $1$ | $10$ | $T\in[1,10],a,b\in[1,10^8]$ |
| $2$ | $5$ | $a,b\in[1,10^8]$ |
| $3$ | $20$ | $T\in[1,10],\frac{a}{b}\in[10^{-8},10^8]$ |
| $4$ | $5$ | $\frac{a}{b}\in[10^{-8},10^8]$ |
| $5$ | $25$ | $T\in[1,10]$ |
| $6$ | $20$ | - |

对于 $100\%$ 数据，保证 $T\in[1,1000],a,b\in[1,10^{16}]$。

本题请相信你的算法的常数。

## 样例 #1

### 输入

```
3
15 33
2024 34
1145141919810721 987654321666```

### 输出

```
2
7
388749955```

# 题解

## 作者：Naszt (赞：27)

# 距离

## 观前提醒

本题利用几何有更直观的做法，详见我用 [desmos](https://www.desmos.com/calculator/bpwk1cbntp) 画的。  
不过为了严谨性，你可以结合着看下面的步骤。

## 思路分析

### 部分分

设 $x=\max\{a,b\},y=\min\{a,b\},x'=ky'$，  
我们要最小化 $ans:=|x-x'|+|y-y'|$。  
令 $y'=y$，有一个显然的上界 $ans\le\left\lfloor\frac{y}{2}\right\rfloor$。

**若 $y$ 较小，我们可以枚举 $y'$：**  
确定了 $y'$ 的意义下，我们则要最小化 $|x-x'|$，  
有：$k=\left\lfloor\frac{x}{y'}\right\rfloor \text{or} \left\lceil\frac{x}{y'}\right\rceil$。  
再根据 $x'=ky'$ 即可算出 $x'$。

为了确保答案的正确性，我们可以枚举所有的：$|y-y'|<ans$  
时间复杂度为 $\Theta(2ans)=O(y)$。

**若 $\frac{x}{y}$ 较小，我们可以枚举 $k$：**  
确定了 $k$ 的意义下，我们则要最小化 $|y-y'|$，  
有：$y'=\left\lfloor\frac{x}{k}\right\rfloor \text{or} \left\lceil\frac{x}{k}\right\rceil$。  
再根据 $x'=ky'$ 即可算出 $x'$。

为了确保答案的正确性，我们可以枚举所有的：$|y-\frac{x}{k}|<ans$  
时间复杂度为 $\Theta\left(\frac{x}{y-ans}-\frac{x}{y+ans}\right)=O\left(\frac{x}{y}\right)$。

### 合并做法

若 $y<\sqrt x$ 采用第一个方法，否则采用第二个做法。  
这样的时间复杂度是 $O(\sqrt x)$ 的。  
~~这何尝又不是一种分治。~~ 

但是这题的 $T$ 比较大，我们需要更好的复杂度分析。

### 时间复杂度

_※ 这一部分内容可以没必要看，毕竟这是信息学（雾）。_

我们以概率的方法分析 $ans$ 的值，  
为了分析简单，我们只统计满足 $x'<x,y'<y$ 的 $(x',y')$。

确定了 $y'$ 的意义下我们定义 $X_{y'}=x\bmod y'$，  
可以发现 $ans\le dis:=X_{y'}+|y-y'|$，  
假设其是均匀且独立分布随机变量 $X_{y'}\in[0,y']\in\mathbb{Z}$，有：

$$
\begin{aligned}
&P(ans>v)\\
<&P(\min\{dis\}>v)\\
=&P\left(\min_{y'=1}^y\{X_{y'}+|y-y'|\}>v\right)\\
=&\prod_{y'=1}^yP(X_{y'}+y-y'>v)\\
=&\prod_{y'=y-v}^yP(y'-X_{y'}<y-v)\\
=&\prod_{y'=y-v}^y\frac{y-v}{y'}\\
=&\frac{(y-v)^v(y-v)!}{y!}\\
\approx&\frac{(y-v)^v\sqrt{2\pi(y-v)}(\frac{y-v}{e})^{y-v}}{\sqrt{2\pi y}(\frac{y}{e})^{y}}\\
\approx&e^{v}\left(\frac{y-v}{y}\right)^{y+0.5}
\end{aligned}
$$

_※ 可能会有一定程度上的误差，这里无伤大雅。_

可以发现我们时间复杂度最大时是 $y^2=x$ 时，  
这时 $y$ 最大能取到 $10^8$，  
但是 $P(ans>10^5)<10^{-50}$。

于是我们可以认为时间复杂度的上界为 $10^5$，足够通过本题的数据了。

当然，如果你想更精确的分析这个时间复杂度也可以，  
我们设最坏概率为 $\epsilon$，这个解可以用朗伯 $W$ 函数表示，有：
$$v=y+(0.5+y)W\left(-\frac{y\sqrt[0.5+y]{e^{-y}ϵ}}{0.5+y}\right)$$
$$v\approx y\left(1+W\left(-\frac{ϵ^{1/y}}{e}\right)\right)$$

更进一步的分析可以发现这个算法的时间复杂度是极快的，这里就不写了。

## 代码实现

### 工程细节

如果你真的把 $ans$ 取到 $\left\lfloor\frac{y}{2}\right\rfloor$ 来写代码，那下面的时间复杂度分析就没用了。

我们可以取 $ans$ 为当前的最优解，不断动态调整，先从 $y'=y$ 或 $k=\left\lfloor\frac{x}{y}\right\rfloor$ 开始遍历。

具体实现方法和更多细节可以看代码。

### 出题人代码

```cpp
#include<bits/stdc++.h>
typedef long long i8;
i8 T,x,y;

i8 ydis(i8 ty){
  i8 kc=x/ty+1,xc=kc*ty,c=abs(ty-y)+abs(xc-x);
  i8 kf=x/ty  ,xf=kf*ty,f=abs(ty-y)+abs(xf-x);
  return std::min(c,f);
}i8 ysolve(){
  i8 ans=ydis(y);
  for(i8 t=1;t<ans;t++)
    ans=std::min(ans,ydis(y-t)),
    ans=std::min(ans,ydis(y+t));
  return ans;
}

i8 kdis(i8 k){
  i8 yc=x/k+1,xc=k*yc,c=abs(yc-y)+abs(xc-x);
  i8 yf=x/k  ,xf=k*yf,f=abs(yf-y)+abs(xf-x);
  return std::min(c,f);
}i8 ksolve(){
  i8 ans=kdis(x/y);
  for(i8 t=1;abs(1.0*x/(x/y-t)-y)<ans;t++)
    ans=std::min(ans,kdis(x/y-t));
  for(i8 t=1;abs(1.0*x/(x/y+t)-y)<ans;t++)
    ans=std::min(ans,kdis(x/y+t));
  return ans;
}

int main(){
  std::cin>>T;
  while(T--){std::cin>>x>>y;
    if(x<y)std::swap(x,y);
    std::cout<<(y<x/y?ysolve():ksolve())<<"\n";
  }return 0;
}
```

### 验题人代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;

ll x, y;

ll GetDistY(ll yy){
	ll ka = x / yy, xa = ka * yy;
	ll kb = x / yy + 1, xb = kb * yy;
	return min(abs(xa - x), abs(xb - x)) + abs(yy - y);
}

ll GetDistK(ll k){
	ll ya = x / k, xa = k * ya;
	ll yb = x / k + 1, xb = k * yb;
	return min(abs(xa - x) + abs(ya - y), abs(xb - x) + abs(yb - y));
}

ll Solve(){
	if(x < y) swap(x, y);
	if(x % y == 0) return 0;
	ll ans = 114514 + 1919810;
	if(y <= x / y){
		ans = GetDistY(y);
		for(ll i = 1; i < ans; ++i) ans = min(ans, min(GetDistY(y + i), GetDistY(y - i)));
	}
	else{
		ans = GetDistK(x / y);
		for(ll i = x / y + 1; y - 1.0L * x / i < ans; ++i) ans = min(ans, GetDistK(i));
		for(ll i = x / y - 1; 1.0L * x / i - y < ans; --i) ans = min(ans, GetDistK(i));
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T--){
		cin >> x >> y;
		cout << Solve() << endl;
	}
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：8)

随便写了一发不知道为啥就最优解了？

仔细看了一下发现出题人是不是没加 `inline`。

最开始这个东西是冲着 $50$ 到 $80$ 分去的，过过去之后以为是假的，看了题解才发现挺有道理。

首先钦定 $x>y$，则最后一定是 $\exist k\in\N,x=ky$。

发现经典的乘积式，考虑对 $y$ 和 $\sqrt x$ 的关系进行阈值分治。

$y\le \sqrt x$ 时枚举 $y$ 最后变成啥样，否则枚举 $k$。

发现确定了 $k$ 或者 $y$ 的最后样子之后答案好算，不再赘述。

交上去之后含泪 $30$ 分，于是加上一个剪枝：如果此时 $y$ 的变化量已经超过了 $ans$，那么再枚举就没有意义了，直接 ```break``` 后拿下最优解。

```
/*
	首先钦定 x>y。
	y*y<=x 则枚举 y 的变化量，否则 x/y 一定很小。
	好像是根号的。视常数有 50 到 80 分。
	有一个剪枝是如果 y 的变化量已经超过答案直接 break。 
	有点能跑啊，没大样例？ 
*/

#include<bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

int T,x,y,ans;

inline int Calcy(int z){//y 变成 z，至少几步满足条件 
	return min(x-x/z*z,((x-1)/z+1)*z-x)+(y<z?z-y:y-z);
}
inline int CalcK(int k){//k=x/y
	return min(abs(x/k*k-x)+abs(x/k-y),abs(x/k*k+k-x)+abs(x/k+1-y)); 
}

int Calc(){
	
	if(y<=x/y){//md 会炸 longlong，没素质。 
		ans=Calcy(y);
		for(int i=1;i<ans;++i)  ans=min(ans,min(Calcy(y+i),Calcy(y-i)));
		//不会 <0
	}else {
		ans=CalcK(x/y);
		for(int i=x/y;y-x/i<ans;++i) ans=min(ans,CalcK(i));
		for(int i=x/y;x/i-y<ans;--i) ans=min(ans,CalcK(i));
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>T;
	while(T--){
		cin>>x>>y;
		if(x<y) swap(x,y);
		if(x%y) cout<<Calc()<<endl;
		else cout<<0<<endl;
	}
	return 0;
}
```

---

