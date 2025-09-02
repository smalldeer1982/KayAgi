# [ABC165D] Floor Function

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc165/tasks/abc165_d

整数 $ A $, $ B $, $ N $ が与えられます。

$ N $ 以下の非負整数 $ x $ に対する $ floor(Ax/B)\ -\ A\ ×\ floor(x/B) $ の最大値を求めてください。

ただし、$ floor(t) $ とは、実数 $ t $ 以下の最大の整数のことを表します。

## 说明/提示

### 制約

- $ 1\ <\ =\ A\ <\ =\ 10^{6} $
- $ 1\ <\ =\ B\ <\ =\ 10^{12} $
- $ 1\ <\ =\ N\ <\ =\ 10^{12} $
- 入力は全て整数

### Sample Explanation 1

$ x=3 $ のとき、$ floor(Ax/B)-A×floor(x/B)\ =\ floor(15/7)\ -\ 5×floor(3/7)\ =\ 2 $ となり、これが最大です。

## 样例 #1

### 输入

```
5 7 4```

### 输出

```
2```

## 样例 #2

### 输入

```
11 10 9```

### 输出

```
9```

# 题解

## 作者：zjyqwq (赞：7)

### AT4827 [ABC165D] Floor Function题解
本题为一道数学题。


------------
#### 解题思路
我们的思路是优先考虑后面的那一坨 $a*⌊x/b⌋$ 。

因为后面的那一坨中的后面那一坨 $⌊x/b⌋$ 是向下取整，所以，如果 $x<b$ 的话，后面的一坨就等于 $0$ 了。

而这样的话， $x$ 为 $b-1$ 毫无疑问，是最优的。

然而 $x$ 是有取值范围 $[1,n]$ 的，那么我们只要在 $n$ 和 $b-1$ 当中选取一个最小的就好了。

这样一来，这道题目就十分好解了，公式题目已经给出，且后半部分为 $0$ ，而这个 $x$ 又可以用 $O(1)$ 的方法解出来，就只需将题目的公式改一改就行了。

------------
#### 主要代码
由于这道题目代码较短，所以只出示部分主要的代码。
```cpp
a*min(b-1,n)/b;
```


------------

#### 最后提示
代码就只有输入，和输出上面那部分就好了。

###### 十年OI一场空，不开longlong见祖宗。
本题数据有点大，要开longlong，也就是64位整型。

结束了！！！

---

## 作者：Clouder (赞：3)

看上去很有意思。其实可以比较简单地推导出来。

$$\lfloor\dfrac{ax}{b} \rfloor - a\times \lfloor\dfrac{x}{b} \rfloor$$

$$\implies \lfloor \dfrac{a \times (\lfloor \dfrac{x}{b} \rfloor \times b + x \bmod b)}{b} \rfloor - a \times \lfloor \dfrac{x}{b} \rfloor$$

$$\implies a \times \lfloor \dfrac{x}{b} \rfloor + \lfloor \dfrac{a \times (x \bmod b)}{b} \rfloor - a \times \lfloor \dfrac{x}{b}\rfloor$$

$$\implies \lfloor \dfrac{a \times (x \bmod b)}{b} \rfloor$$

最大化这东西，取 $b - 1$ 即可。如果取不到，则尽量大。

```cpp
printf("%lld\n", a * std::min(n, b - 1) / b);
```

---

## 作者：Acerkaio (赞：2)

### [题面](https://www.luogu.com.cn/problem/AT4827)
### 思路
我们观察减数，小学数学老师教过：减数越小，差越大。

因此，我们考虑使 $a \times \left \lfloor \frac{x}{b} \right \rfloor$ 最小。

小学数学老师还教过：任何数乘零都得零，发现我们只要使 $b<x$ 就可以使 $\left \lfloor \frac{x}{b} \right \rfloor$ 得到零。

所以 $b<x$。

所以最大的重任来到 $\left \lfloor \frac{ax}{b}  \right \rfloor $ 上——无脑开大啊，因此 $b$ 要是小于 $x$ 的最大整数，因题目限制 $x$ 取值于 $ [ 1,n ] $，所以 $x=\max(n,b-1)$。

题目答案就是 $\left \lfloor \frac{ax}{b}  \right \rfloor $，其中 x 值也得到，$O(1)$ 可得结果。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int a,b,n;
	cin>>a>>b>>n;
	cout<<a*min(n,b-1)/b;
	return 0;
}

```


---

## 作者：do_while_true (赞：2)

本篇题解证明并不严谨，只是提供给大家在比赛时更快思考出此类题的思路。

把这个式子两边分成两部分，即我们要尽可能左边大，右边小，才能使差值尽可能大。如果不考虑 $floor$ ，两边式子化简都是 $A*x/B$ 。则我们考虑 $floor$ 对结果的损耗。

下文中的左边式子代表 $floor(A*x/B)$，右边式子代表 $A* floor(x/B)$。

对于右边的式子，最大的损耗显然是 $B$ 的倍数 $-1$（$0$ 倍除外），因为如果不为 $B$ 的倍数，答案和 $x$ 向下离 $B$ 的倍数最近的那一个，也就是考虑一个 $k$ 使得 $k*B\leq x <(k+1)*B$，其中 $x$ 取 $k*B$ 到 $(k+1)*B$(不包含) ，对答案的贡献都是一样的，但是 $x$ 尽可能大又能使左边式子带来尽可能大的收益，所以我们的 $x$ 应该取到 $B$ 的倍数 $-1$。

所以 $x$ 直接取 $B-1$ 即可，因为不管是 $B$ 的几倍，左边式子和右边式子都是 $/B$ 后下取整，不管几倍，答案都是相同的。

特别的，如果 $x$ 取不到 $B-1$，也就是如果 $N<B-2$，直接取最大的 $N$ 即可。

---

## 作者：在下互质数 (赞：2)

```cpp
#include<iostream>
using namespace std;
int main()
{
	long long a,b,c;
	cin>>a>>b>>c;
	long long temp;
	if(b-1<=c) temp=b-1;
	else temp=c;
	long long ans;
	ans=(long long)((double)a*temp/b)-a*(long long)((double)temp/b);
	cout<<ans;
	return 0;
}
```


---

## 作者：钓鱼王子 (赞：1)

其实乱猜都能过，这里还是给一个严谨的证明吧。

⌊ $\dfrac{a+x}{x}$	⌋ $=$ ⌊ $\dfrac{a}{x}$	⌋ $+1$

这个没什么好说的。

所以如果 $x>=B$ 可以把 $B$ 的倍数那一坨提出来，因为都是乘上 $A$，所以答案不变。

当 $x<B$ 时，后式一定为 $0$，令 $x=B-1$，此时前式最大。

注意 $x$ 要对给出的 $N$ 取 $\min$。

计算即可。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,k,ans;
signed main(){
	n=read();m=read();k=read();
	ans=n*min(m-1,k)/m;
	printf("%d",ans);
}

```


---

## 作者：1n1c5c5z (赞：0)

## 题目大意:
给定 $A,B,N$，求 $\lfloor\dfrac{A \times x}{b}\rfloor-A\times\lfloor\dfrac{x}{b}\rfloor(0 \leq x \leq N)$ 的最大值。
## Solution:
设上式为函数 $f(x)$，则当任意 $y$ 使得 $y \equiv x \pmod b$ 时，$f(x)=f(y)$。  
所以可以指考虑 $0 \leq x \leq B-1$ 的情况。  
暴力枚举可发现此时 $f(x)$ 递增。  
答案即为 $f(\min(N,B-1))$。
## Code:
```cpp
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	long long n,a,b;
	cin>>a>>b>>n;
	if (b<=n)
	{
		cout<<a*(b-1)/b<<endl;
	}
	else
	{
		cout<<a*n/b-a*(n/b)<<endl;
	}
	return 0;
}
```


---

## 作者：hanzhongtlx (赞：0)

很多人打表找规律，可我好懒啊，只能尝试证明一下了。   

题意：求当 $x\leq N$ 时，$\left\lfloor\dfrac{Ax}{B}\right\rfloor-A\left\lfloor\dfrac{x}{B}\right\rfloor$ 的最大值。    

比赛的时候理解错题意了...... 

先设：$x<B$。

考虑：
$$\left\lfloor\dfrac{Ax}{B}\right\rfloor=\left\lfloor A(\dfrac{x}{B}-\left\lfloor\dfrac{x}{B}\right\rfloor)\right\rfloor+A\left\lfloor\dfrac{x}{B}\right\rfloor$$    

至于为什么，您去想吧......    
理解起来很简单。     

那么我们要求的式子即为：
$$\left\lfloor A(\dfrac{x}{B}-\left\lfloor\dfrac{x}{B}\right\rfloor)\right\rfloor$$  
的最大值。    
显然最大化 
$$\dfrac{x}{B}-\left\lfloor\dfrac{x}{B}\right\rfloor$$  
即可。    
那么当 $x$ 最大时最大。   

那么当 $x<(k+1)B$ 时同理，由于整数部分在 $\dfrac{x}{B}-\left\lfloor\dfrac{x}{B}\right\rfloor$ 是被抵消的。    

那么当 $x<B$ 是，带入 $x$ 即可，否则直接取 $b-1$ 即可。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;

#define read(x) scanf("%d",&x)
#define readl(x) scanf("%lld",&x)
#define ll long long 
#define ull unsigned long long

ll a,b,n;
ll x;

int main()
{
	cin>>a>>b>>n;
	if(n<b) x=n;
	else x=b-1;
	cout<<floor((double)a*(double(x)/b-floor(double(x)/b)))<<endl;
	return 0;
}
```


---

