# Primitive Primes

## 题目描述

It is Professor R's last class of his teaching career. Every time Professor R taught a class, he gave a special problem for the students to solve. You being his favourite student, put your heart into solving it one last time.

You are given two polynomials $ f(x) = a_0 + a_1x + \dots + a_{n-1}x^{n-1} $ and $ g(x) = b_0 + b_1x + \dots + b_{m-1}x^{m-1} $ , with positive integral coefficients. It is guaranteed that the cumulative GCD of the coefficients is equal to $ 1 $ for both the given polynomials. In other words, $ gcd(a_0, a_1, \dots, a_{n-1}) = gcd(b_0, b_1, \dots, b_{m-1}) = 1 $ . Let $ h(x) = f(x)\cdot g(x) $ . Suppose that $ h(x) = c_0 + c_1x + \dots + c_{n+m-2}x^{n+m-2} $ .

You are also given a prime number $ p $ . Professor R challenges you to find any $ t $ such that $ c_t $ isn't divisible by $ p $ . He guarantees you that under these conditions such $ t $ always exists. If there are several such $ t $ , output any of them.

As the input is quite large, please use fast input reading methods.

## 说明/提示

In the first test case, $ f(x) $ is $ 2x^2 + x + 1 $ and $ g(x) $ is $ x + 2 $ , their product $ h(x) $ being $ 2x^3 + 5x^2 + 3x + 2 $ , so the answer can be 1 or 2 as both 3 and 5 aren't divisible by 2.

In the second test case, $ f(x) $ is $ x + 2 $ and $ g(x) $ is $ x + 3 $ , their product $ h(x) $ being $ x^2 + 5x + 6 $ , so the answer can be any of the powers as no coefficient is divisible by the given prime.

## 样例 #1

### 输入

```
3 2 2
1 1 2
2 1```

### 输出

```
1```

## 样例 #2

### 输入

```
2 2 999999937
2 1
3 1```

### 输出

```
2```

# 题解

## 作者：suxxsfe (赞：11)

[CF1316C 【Primitive Primes】](https://codeforces.com/problemset/problem/1316/C)  
给出两个多项式$a_0+a_1x+a_2x^2+\dots +a_{n-1}x^{n-1}$和$b_0+b_1x+b_2x^2+ \dots +a_{m-1}x^{m-1}$，每个多项式的系数的$\gcd$都为1  
给出质数$p$，求在这两个多项式乘积的系数中，任意一个不能被$p$整除的系数  
比赛的时候没想到，居然了想用线段树维护，~~什么都想用线段树。。然后悲惨掉分~~  
设乘积的系数序列为$c$  
我们可以设在这两个序列中，**第一个**不能被$p$整除的数分别是$a_i$和$b_j$（肯定会存在这样的$i,j$，否则它们的gcd就是$p$了）  
则可以证明要求的系数为$c_{i+j}$  
$$c_{i+j}=\sum_{k=0}^{i+j}a_k\times b_{i+j-k}$$  
这里假设有足够多的项（$i+j\leq n,m$）  
因为$a_0,a_1,a_2\dots a_{i-1}$和$b_0,b_1,b_2\dots b_{j-1}$都能被$p$整除  
所以上面的式子中，只有$a_i\times b_j$这一项不能被$p$整除，其他项中都含有一个$a_k(k<i$)或$b_k(k<j)$  
所以原式相当于一个$p$的倍数加一个非$p$的倍数的数  
那么其当然不能被$p$整除  
```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	int x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int n,m,p;
int main(){
	n=read();m=read();p=read();
	int a=-1,b=-1;
	for(reg int x,i=0;i<n;i++){
		x=read();
		if(x%p&&a==-1) a=i;
	}
	for(reg int x,i=0;i<m;i++){
		x=read();
		if(x%p&&b==-1) b=i;
	}
	std::printf("%d",a+b);
	return 0;
}
```

---

## 作者：一扶苏一 (赞：3)

# 【数学】【CF1316C】Primitive Primes

## Description

- 给定两个序列 $a$ 和 $b$，其中序列 $a$ 的长度为 $n$，序列 $b$ 的长度为 $m$。
- 分别保证序列中所有数字的最大公约数为 $1$。即 $\gcd(a_0, a_1 \dots a_{n - 1}) = 1$，$\gcd(b_0, b_1, \dots b_{m - 1}) = 1$。
- 设 $a$ 与 $b$ 卷积的结果为序列 $c$。即 $c_k = \sum\limits_{0 \leq i \leq k \land i < n \land k - i < m } a_i \times b_{k - i}$。
- 给出一个 **质数** $p$，请你求出一个下标 $t$，满足 $c_t$ **不能**被 $p$ 整除。如果有多个满足要求的 $t$，请任意输出一个。
- $1 \leq n, m \leq 10^6$，$1 \leq p, a_i, b_i \leq 10^9$。

## Solution

~~事实证明做不出题的时候去个洗手间冷静一下有助于开拓思路~~。

为了简化叙述，约定一个数 $x$ “符合要求”指 $x$ 不是 $p$ 的倍数，即 $p \not\mid x$；而一个数 $x$ “不符合要求”指 $x$ 是 $p$ 的倍数，即 $p \mid x$。请注意符合要求是指符合**题目要求**的**不能**被 $p$ 整除。

首先考虑 $c_0$，若 $a_0$ 与 $b_0$ 均不是 $p$ 的倍数，由于 $p$ 是一个质数，所以 $a_0 \times b_0$ 一定不是 $p$ 的倍数。因此直接输出 $0$ 即可。

换句话说，若 $c_0$ 不符合要求，则 $a_0$ 与 $b_0$ 至少有一个数存在质因子 $p$。现在分情况讨论。

1. 两数中有且仅有一个数存在质因子 $p$，不妨设这个数为 $a_0$。现在考虑 $c_1 = a_0 \times b_1 + a_1 \times b_0$。若 $c_1$ 也不符合要求，由于 $a_0$ 是 $p$ 的倍数，则 $a_1 \times b_0$ 也需要是 $p$ 的倍数。又因为 $b_0$ 不是 $p$ 的倍数，所以 $a_1$ 一定也是 $p$ 的倍数。

   对 $a_i$ 进行数学归纳可以证明，这种情况下，若 $a_0$ 到 $a_{k - 1}$ 都是 $p$ 的倍数，且 $b_0$ 不是 $p$ 的倍数，则 $c_k$ 符合要求当且仅当 $a_k$ 不是 $p$ 的倍数。

   由于保证了 $a$ 序列中所有数字的最大公约数为 $1$，所以一定存在一个 $k$，满足 $a_k$ 不是 $p$ 的倍数，此时输出 $k$ 即可。

2. 两数均是 $p$ 的倍数。设答案为 $t$，这种情况下我们注意到 $a_0$ 会乘上 $b_t$，$a_t$ 会乘上 $b_0$，而这两项模 $p$ 的结果都是 $0$，即他们对 $c_k$ 是没有贡献的，因此我们不管这两项，从第 $1$ 项开始按照上述方法重新讨论即可。

更一般的，设 $a$ 与 $b$ 的前 $(i - 1)$ 项都是 $p$ 的倍数，分三种情况讨论：

1. 若第 $i$ 项均不是 $p$ 的倍数，则令 $a_i$ 与 $b_i$ 卷在一起的一项为答案即可，即输出 $i + i$。
2. 若有且仅有一个序列的第 $i$ 项是 $p$ 的倍数，不妨设为 $a$ 序列，则向后找到 $a$ 序列的第一个不是 $p$ 的倍数的位置 $j$，我们要令 $a_j$ 与 $b_i$ 卷在一起的一项为答案，因此输出 $i + j$ 即可。
3. 否则两序列的前 $i$ 项均为 $p$ 的倍数，迭代考虑第 $(i + 1)$ 项即可。

## Code

代码中数列下标是从 $1$ 开始的，因此输出时要 $-2$。

```cpp
const int maxn = 1000006;
 
int n, m, p;
int A[maxn], B[maxn];
 
int main() {
  freopen("1.in", "r", stdin);
  qr(n); qr(m); qr(p);
  for (int i = 1; i <= n; ++i) {
    qr(A[i]);
  }
  for (int j = 1; j <= m; ++j) {
    qr(B[j]);
  }
  int *a = A, *b = B;
  for (int i = 1; ; ++i) {
    if ((a[i] % p) > (b[i] % p)) std::swap(a, b);
    if ((a[i] % p) == 0) {
      if ((b[i] % p) != 0) {
        for (int j = i + 1; ;++j) if ((a[j] % p) != 0) {
          printf("%d\n", j + i - 2);
          return 0;
        }
      }
    } else {
      printf("%d\n", i + i - 2);
      return 0;
    }
  }
  return 0;
```



   

---

## 作者：Andrewzdm (赞：3)

**UPD：** 修正了笔误（~~NNT~~ $\to$ NTT）

# [CF1316C Primitive Primes](https://www.luogu.com.cn/problem/CF1316C)

~~这道毒瘤题，卡了我1h30min还没做出来。啊啊啊啊……~~

其实刚开始我的思路是算出所有的 $c$ 再枚举 $t$ 。

于是想到NTT。

然后TLE了。

我又想找到计算系数的规律并优化。

然而还是失败了……

（肯定不是NTT，Div.2 的C题怎么可能是省选难度……）

接下来我开始思考：
1. 为什么题目要规定 $p$ 是质数？
2. 为什么题目中有如下两个条件？
$\gcd(a_0,a_1,a_2\dots a_{n-1})=1$  
$\gcd(b_0,b_1,b_2\dots b_{m-1})=1$

然后我开始思考 $p$ 是质数能得到什么，接着我就想出了正解——

首先，
$c_i = a_0\cdot b_i+a_1\cdot b_{i-1}+a_2\cdot b_{i-2}+\dots +a_{i-2}\cdot b_2+a_{i-1}\cdot b_1+a_i\cdot b_0$.

要让 $c_i \bmod p \neq 0$，则上方多项式的每一项中，有且仅有一项中的 $a$ 和 $b$ 满足 $a \bmod p \neq 0$ 且 $b\bmod p \neq 0$ 。

所以我们在 $a$ 数组中找到第一个 $a_x \bmod p\neq 0$ ，在  $b$ 数组中找到第一个 $b_y \bmod p\neq 0$ ，满足条件的 $t$ 就等于 $x+y$ 。

那么又有一个问题——$\gcd(a_0,a_1,a_2\dots a_{n-1})=\gcd(b_0,b_1,b_2\dots b_{m-1})=1$ 有什么用？

这句话向我们保证了不可能对于所有的 $i \in [0,n-1]$ , $a_i \bmod p=0$ ，
以及不可能对于所有的 $i\in [0,m-1]$ , $b_i \bmod p=0$ 。
简单来说——题目保证有解。

（不过题目已经说了一定存在符合条件的 $t$ ）

AC代码如下：（真的很简单）
```cpp
#include<cstdio>
const int maxx = 1000010;
int a[maxx], b[maxx];

inline int read()
{
    int res = 0;
    char ch = getchar();
    bool f = true;
    for (; ch < '0' || ch > '9'; ch = getchar())
        if (ch == '-')
            f = false;
    for (; ch >= '0' && ch <= '9'; ch = getchar())
		res = (res << 1) + (res << 3) + (ch ^ 48);
    return f ? res : -res;
}

int main()
{
	int n, m, p;
	n = read();
	m = read();
	p = read();
	for(int i = 0; i < n; i++)
		a[i] = read();
	for(int i = 0; i < m; i++)
		b[i] = read();
	int x = 0;
	while(a[x] % p == 0)
		x++;
	int y = 0;
	while(b[y] % p == 0)
		y++;
	printf("%d\n",x+y);
	return 0;
}
```
时间复杂度 $O(n+m)$ 

---

## 作者：__LiChangChao__ (赞：1)

### 思路

有一个结论：

> 若 $x\mod p \not = 0, y\mod p \not=  0$，且 $p$ 为质数，则 $xy\mod p \not = 0$。

证明：
> 设 $x=k_{1}p+a_{1},y=k_{2}p+a_{2}$，且 $1\le a_{1},a_{2}<p$，$k_{1},k_{2}$ 为非负整数。
>
> 则 $xy=(k_{1}p+a_{1})(k_{2}p+a_{2})=k_{1}k_{2}p^{2}+(k_{1}a_{2}+k_{2}a_{1})p+a_{1}a_{2}$。
>
> 显然 $xy \mod p = a_{1}a_{2} \mod p$。
>
> 但是 $a_{1},a_{2}<p$，而且 $p$ 为质数，所以 $a_{1}a_{2}$ 不可能存在质因子 $p$。
>
> 这是因为整数唯一分解定理，所以如果 $a_{1}a_{2}$ 存在质因子 $p$ ，则 $a_{1},a_{2}$ 中一定最少一个含有质因子 $p$，与 $a_{1},a_{2}<p$ 矛盾，得证。

再来看题，首先有：

$$
c_{i}=\sum_{j=0}^{i} a_{j}b_{i-j+1}
$$

那么要 $c_i\mod p \not = 0$。

假设当前有两个位置 $l_{1},l_{2}$，满足 $a_{0},\dots,a_{l_{1}-1} \mod p =0,a_{l_{1}}\mod p \not = 0,b_{0},\dots,b_{l_{2}-1} \mod p =0,b_{l_{2}}\mod p \not = 0$。

那么是不是一定有：
$$\sum_{j=0}^{l_{1}+l_{2}}a_{j}b_{l_{1}+l_{2}-j+1}=\sum_{j=0}^{l_{1}-1}a_{j}b_{l_{1}+l_{2}-j+1}+a_{l_{1}}b_{l_{2}}+\sum_{j=0}^{l_{1}+1}a_{j}b_{l_{1}+l_{2}-j+1} \mod p = a_{l_{1}}b_{l_{2}} \mod p\not = 0$$

所以找到 $l_{1},l_{2}$ 即可。

> $\gcd(a_{1},\dots,a_{n})=1,\gcd(b_{1},\dots,b_{m})=1$ 意味着一定有数不是 $p$ 的倍数，否则 $\gcd$ 应该是 $p$。

所以这种方法一定能找出一种解。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p;
int a,b;
int ans1,ans2;
int main(){
	scanf("%d%d%d",&n,&m,&p);
	for(int i=0;i<n;i++){
		scanf("%d",&a);
		if(a%p&&!ans1){
			ans1=i;
		}
	}
	for(int i=0;i<m;i++){
		scanf("%d",&b);
		if(b%p&&!ans1){
			ans2=i;
		}
	}
	printf("%d",ans1+ans2);
}
```


---

