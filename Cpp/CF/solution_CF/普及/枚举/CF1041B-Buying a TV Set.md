# Buying a TV Set

## 题目描述

### 题目大意：
给你$a,b,c,d$，求满足$\frac{x}{y}=\frac{c}{d},x\leq a,y\leq b$的$x,y$的对数

## 样例 #1

### 输入

```
17 15 5 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
14 16 7 22
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 2 6 4
```

### 输出

```
1
```

## 样例 #4

### 输入

```
1000000000000000000 1000000000000000000 999999866000004473 999999822000007597
```

### 输出

```
1000000063
```

# 题解

## 作者：dblark (赞：3)

又是一道水题（然而本人除了水题做不出）。

题目大意：给你$a,b,x,y$，求出所有满足条件$(w\le a),(h\le b),(\frac{w}{h}=\frac{x}{y})$的自然数$w,h$。

首先简化$\frac{x}{y}$，将$x,y$同时除以$gcd(x,y)$即可。

然后，分别求出可能的$w,h$的数量，然后求个最小值就行了。

奉上垃圾的Pascal代码：

```pascal
{CF1041B}
var
  a,b,x,y,t:int64;
function min(x,y:int64):int64;
begin
  if x<y then
    exit(x)
  else
    exit(y);
end;
function gcd(x,y:int64):int64;
begin
  if y=0 then
    exit(x)
  else
    exit(gcd(y,x mod y));
end;
begin
  read(a,b,x,y);
  t:=gcd(x,y);
  writeln(min(a div (x div t),b div (y div t)));
end.
```

---

## 作者：Eason_AC (赞：2)

## Content
给定四个数 $a,b,c,d$，求满足以下条件的数对 $(x,y)$ 的个数：

- $x\leqslant a,y\leqslant b$。
- $\dfrac{x}{y}=\dfrac{c}{d}$。

**数据范围：$1\leqslant a,b,c,d\leqslant 10^{18}$。**
## Solution
众所周知，数据范围很大的话一般就得要推结论了。

我们先把这个 $\dfrac{c}{d}$ 化简一下，假设是 $\dfrac{c'}{d'}$。由于很明显，$x,y$ 显然要分别是 $c',d'$ 的倍数，所以设 $x=k_1c',y=k_2d'$，那么我们由上面的条件：

$x\leqslant a,y\leqslant b$

$\Rightarrow k_1c'\leqslant a,k_2d'\leqslant b$

$\Rightarrow k_1\leqslant \dfrac{c'}{a},k_2\leqslant \dfrac{d'}{b}$

又因为 $\dfrac{x}{y}=\dfrac{c'}{d'}$

所以 $\dfrac{c'}{x}=\dfrac{d'}{y}$

那么就只能够从 $k_1,k_2$ 中取较小值了。因此答案就是 $\min\{\dfrac{c'}{a},\dfrac{d'}{b}\}$。
## Code
```cpp
long long a, b, c, d;

int main() {
	scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
	long long gcdcd = __gcd(c, d);
	c /= gcdcd, d /= gcdcd;
	printf("%lld", min(a / c, b / d));
}
```

---

## 作者：ezoixx130 (赞：2)

### 题意：

有一个商店出售电视机，这个商店拥有每一种宽不超过$a$并且高不超过$b$的电视机。

现在Monocarp想买一台电视机，但是他要求这台电视级的宽高比等于一个给定的分数$\frac{x}{y}$，求有多少种方案。

一句话题意：给你$a,b,x,y$，求满足$\frac{w}{h}=\frac{x}{y}$的$(w,h)$对数，其中$1\leq w\leq a$，$1\leq h\leq b$。

### 题解：

#### 算法1：

枚举$w,h$，逐一检验即可。

时间复杂度：$O(ab)$

空间复杂度：$O(1)$

#### 算法2：

枚举$w$，判断是否能找到$h$即可。

时间复杂度：$O(min(a,b))$

空间复杂度：$O(1)$

#### 算法3：

显然面对$10^{18}$范围内的$a,b$，不能枚举。

我们考虑，将$\frac{x}{y}$化简为最简分数$\frac{q}{p}$，则有$\frac{w}{h}=\frac{q}{p}$，那么$w=kq,h=kp$，$k$为正整数，$1\leq w\leq a$，$1\leq h\leq a$。

考虑到$w$有$\left \lfloor \frac{a}{q} \right \rfloor$种取值，$h$有$\left \lfloor \frac{b}{p} \right \rfloor$种取值，那么答案为$min(\left \lfloor \frac{a}{q} \right \rfloor,\left \lfloor \frac{b}{p} \right \rfloor)$。

时间复杂度：$O(log(min(x,y)))$（求gcd所用时间）

空间复杂度：$O(1)$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

long long a,b,x,y,l,r,t;

int main()
{
	scanf("%I64d%I64d%I64d%I64d",&a,&b,&x,&y);
	t=__gcd(x,y);
	x/=t;
	y/=t;
	l=a/x;
	r=b/y;
	printf("%I64d\n",min(l,r));
}
```

---

## 作者：WsW_ (赞：1)

## 思路：
因为 $a,b,c,d,x,y\in\mathrm{Z}$ ，所以一开始考虑求出最小一组的 $x,y$ 并不断增加，直到 $x>a$ 或 $y>b$。  
设 $\dfrac{x}{y}=\dfrac{c}{d}=\dfrac{p}{q}(p\bot q)$ ，由于 $p,q$ 互质，显然 $p,q$ 分别为最小的 $x,y$。  
对第一种思路进行优化，发现 $x,y$ 每次增加的值都是一样的，且等于 $x,y$，求从 $0,0$ 每次增加 $p,q$，到 $a,b$ 最多能增加多少次，显然这是除法的本质。  
由于需要同时满足 $x\leq a,y\leq b$ 两个条件，故需要取两者间的较小值，即结果为：
$$\min\left( \frac{a}{p},\frac{b}{q} \right)$$
其中：
$$p=\frac{c}{\gcd(c,d)},q=\frac{d}{\gcd(c,d)}$$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,c,d;
signed main(){
	cin>>a>>b>>c>>d;
	int g=__gcd(c,d);
	c/=g;//求p
	d/=g;//求q
	cout<<min(a/c,b/d);
	return 0;
}//RemoteJudge挂了，直接交在CF上的。
```

---

## 作者：wol_qq (赞：0)

这道题虽然只是一道橙，但还是很有必要仔细研究一下。

**题意**

翻译给得很清楚了，~~但我还是想水一下题解长度~~。题目的意思是：给你四个数   $a$、$b$、$c$、$d$，然后构造两数 $x$、$y$，使 $\frac{x}{y}$=$\frac{c}{d}$，并且满足 $x \le a$ 且 $y \le b$ 时求 $x$、$y$ 的组数。

**思路**

我们可以先把 $\frac{c}{d}$ 进行约分，设约分后的最简分数为 $\frac{c'}{d'}$，再设 $k=c \div c'=d \div d'$，那么 $\frac{c'}{d'}$。我们都知道，如果 $\frac{c'}{d'}$ 是一组解，那么在 $(m \times c')\le x$ 且 $(m \times d')\le y$（$m$ 为 $\ge 2 $的正整数）的前提下，$\frac{c' \times m}{d' \times m}$ 也是一组解，那我们的目标就是求出有多少个 $m$ 符合要求。那答案就是 $\min(a \div c, b \div d)$。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,x,y,gcd;
int main(){
	cin>>a>>b>>c>>d;
	gcd=__gcd(c,d);
	c/=gcd;
	d/=gcd;
	cout<<min(a/c,b/d);
}
```


---

## 作者：Morax2022 (赞：0)

# Solution
给定 $x,y,a,b(x \le a,y \le b)$ 四个数，求 $a/b = x/y$ 的个数。

调用 $\gcd$ 函数算出 $a,b$ 的最大公约数，此时若 $x/y = (a/\gcd(a,b))/(b/\gcd(a,b))$ 的话，一定满足 $x$ 和 $y$ 皆为一个整数 $k$ 的倍数。所以 $x$ 至多出现 $\left \lfloor a/(x/k) \right \rfloor$ 种情况，同理，$y$ 出现 $\left \lfloor b/(y/k) \right \rfloor$ 种情况，取两种情况较小值即可。
# AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
main()
{
	long long x, y, a, b;
	cin >> x >> y >> a >> b;
	long long gcd = __gcd(a, b);//调用系统函数，gcd前是两条下划线！ 
	a /= gcd, b /= gcd;//约分
	cout << min(x / a, y / b);//自动取下整
} 
```
希望本题解能给大家带来帮助！

---

## 作者：fengxiaoyi (赞：0)

### 思路
先来个证明（这里默认 $a\le c$ 且 $b\le d$）：

若
$$\frac{a}{b}=\frac{c}{d}$$
则
$$c\bmod a=0,d\bmod b=0$$
所以题目就是要求求有多少组 $(x,y)$，满足
$$\max(x,c)\bmod\min(x,c)=0\text{ }\max(y,d)\bmod\min(y,d)=0$$
且
$$x\le a,y\le b$$
为了方便求 $x,y$，我们需先将 $c,d$ 除以他们的最大公约数得到 $c_2,d_2$，接着在枚举一个变量 $k$，判断 $c_2\times k$ 和 $d_2\times k$ 是否符合上述条件即可，如果符合，$ans+1$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,g;
//辗转相除求最大公约数
long long gcd(cll x,cll y){
	if(x%y==0){
		return y;
	}
	return gcd(y,x%y);
}
int main(){
	cin>>a>>b>>c>>d;
	g=gcd(c,d);
	c/=g,d/=g;
	cout<<min(a/c,b/d);
	return 0;
}
```


---

## 作者：Daidly (赞：0)

可以发现：$\frac{x}{y}=\frac{k\frac{c}{\gcd(c,d)}}{k\frac{d}{\gcd(c,d)}}$，满足：$k\frac{c}{\gcd(c,d)}\leq a,k\frac{d}{\gcd(c,d)}\leq b$，求最大的 $k$。

答案即为：$\min(\frac{a}{\frac{c}{\gcd(c,d)}},\frac{b}{\frac{b}{\gcd(c,d)}})=\min(\frac{a\gcd(c,d)}{c},\frac{b\gcd(c,d)}{b})$。

- 开 `long long`。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,c,d;
int gcd(int x,int y){
	if(!y)return x;
	return gcd(y,x%y);
}
signed main(){
	cin>>a>>b>>c>>d;
	int tmp=gcd(c,d);
	c/=tmp,d/=tmp;
	if(a<c||b<d){printf("0");return 0;}
	cout<<min(a/c,b/d);
	return 0;
}
```

---

## 作者：小闸蟹 (赞：0)

```cpp
// 注意x / y要先约分，然后除一下取最小值就好了
#include <iostream>
#include <algorithm>

using ll = long long;

ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    ll a, b, x, y;
    std::cin >> a >> b >> x >> y;

    auto r = gcd(x, y);
    x /= r;
    y /= r;

    std::cout << std::min(a / x, b / y) << std::endl;

    return 0;
}
```

---

## 作者：LRL65 (赞：0)

### 思路：
先化简x/y,同时除以它们的最大公约数。然后看a中有几个x，b中有几个y，小的那个就是答案。

上代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long a,b,x,y,gcd;
int main() {
	cin>>a>>b>>x>>y;//输入
    gcd=__gcd(x,y);//最大公约数
	x/=gcd;//化简
	y/=gcd;//化简
	cout<<min(a/x,b/y)<<endl;//取小的那个
}
```


---

