# Geometrical Progression

## 题目描述

For given $ n $ , $ l $ and $ r $ find the number of distinct geometrical progression, each of which contains $ n $ distinct integers not less than $ l $ and not greater than $ r $ . In other words, for each progression the following must hold: $ l<=a_{i}<=r $ and $ a_{i}≠a_{j} $ , where $ a_{1},a_{2},...,a_{n} $ is the geometrical progression, $ 1<=i,j<=n $ and $ i≠j $ .

Geometrical progression is a sequence of numbers $ a_{1},a_{2},...,a_{n} $ where each term after first is found by multiplying the previous one by a fixed non-zero number $ d $ called the common ratio. Note that in our task $ d $ may be non-integer. For example in progression $ 4,6,9 $ , common ratio is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF758F/aca20a9143c643513aefd4868a103ba2e067b031.png).

Two progressions $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{n} $ are considered different, if there is such $ i $ ( $ 1<=i<=n $ ) that $ a_{i}≠b_{i} $ .

## 说明/提示

These are possible progressions for the first test of examples:

- $ 1 $ ;
- $ 2 $ ;
- $ 3 $ ;
- $ 4 $ ;
- $ 5 $ ;
- $ 6 $ ;
- $ 7 $ ;
- $ 8 $ ;
- $ 9 $ ;
- $ 10 $ .

These are possible progressions for the second test of examples:

- $ 6,7 $ ;
- $ 6,8 $ ;
- $ 6,9 $ ;
- $ 7,6 $ ;
- $ 7,8 $ ;
- $ 7,9 $ ;
- $ 8,6 $ ;
- $ 8,7 $ ;
- $ 8,9 $ ;
- $ 9,6 $ ;
- $ 9,7 $ ;
- $ 9,8 $ .

These are possible progressions for the third test of examples:

- $ 1,2,4 $ ;
- $ 1,3,9 $ ;
- $ 2,4,8 $ ;
- $ 4,2,1 $ ;
- $ 4,6,9 $ ;
- $ 8,4,2 $ ;
- $ 9,3,1 $ ;
- $ 9,6,4 $ .

These are possible progressions for the fourth test of examples:

- $ 4,6,9 $ ;
- $ 9,6,4 $ .

## 样例 #1

### 输入

```
1 1 10
```

### 输出

```
10```

## 样例 #2

### 输入

```
2 6 9
```

### 输出

```
12```

## 样例 #3

### 输入

```
3 1 10
```

### 输出

```
8```

## 样例 #4

### 输入

```
3 3 10
```

### 输出

```
2```

# 题解

## 作者：Error_Eric (赞：2)

### 前言

CSP 初赛前的题解

AFO countdown 1day

### 正文

题目大意：

求出长度为 $n$ ，并且所有元素在 [l,r] 范围之内的[等比数列](https://baike.baidu.com/item/%E7%AD%89%E6%AF%94%E6%95%B0%E5%88%97/1129457)的个数。

当且仅当数列 $a$ （$a_1,a_2,a_3...a_n$） 与数列 $b$ （$b_1,b_2,b_3...b_n$）中存在 $i$ ，使得 $a_i\not=b_i$ 时，我们认为 $a$ 和 $b$ 是不同的数列。

前置芝士:

[枚举有理数的方法](https://www.luogu.com.cn/problem/P1014) （不是吧不是吧难道有人没有做过这道题？）

[如何在 $\log n$ 的时间内计算 $a^n$](https://www.luogu.com.cn/problem/P1226)

[等比数列](https://baike.baidu.com/item/%E7%AD%89%E6%AF%94%E6%95%B0%E5%88%97/1129457)

一个有用的证明：$n>40$ 不存在解。

$(i)$

如果公差是分数 $\dfrac{q}{p}((q,p)=1)$ 第一项是 $a_1$ 。

显然第 $n$ 项是 $a_1\times(\dfrac{q}{p})^{(n-1)}=\dfrac{a_1\times q^{(n-1)}}{p^{n-1}}$ 。

$\because$ 第 $n$ 项是正整数 （$a_n\in \mathbb{Z}$）并且 $(q,p)=1$ 。

$\therefore p^{n-1}|a_1$

又$\because p\not=1$

$\therefore {a_1}_{min}=2^{40} $ 远大于数据限制。

$(ii)$

如果公差是整数。

$a_n=a_1\times p^n$ 最小为 $2^{40}$ 远大于数据限制。

综上所述，$n>40$ 不存在解。

### code

思路：暴力枚举公比+特判。

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define ll long long
ll n,l,r;
ll power(ll base,ll idx){//朴素的快速幂
	if(idx==1)return base;
	if(idx==0)return 1ll;
	ll p=power(base,idx/2);
	if(idx%2)return p*p*base;
	else return p*p;
}
void solve(){//这里通过枚举正整数p,q来达到枚举有理数q/p的目的
             //注意由于每一项都是整数，枚举到r即可
	ll ans=0,l_,r_;
	for(ll p=2;p<r;p++){
		r_=r/power(p,n-1);//最大可以取到几
		if(r_==0)break;//等比数列不允许存在0
		for(ll q=1;q<p;q++){
			l_=(l-1)/power(q,n-1)+1;//最小可以取到几
			if(l_>r_)continue;//无解
			if(__gcd(p,q)==1)ans+=(r_-l_+1);//两数互质，加上方案数目
							//注意如果不加判断会导致q/p,2q/2p都被枚举到，就会出现问题。
		}
	}
	printf("%lld\n",ans*2);//倒着来也可以，所以乘上2
}
int main(){
	scanf("%lld%lld%lld",&n,&l,&r);//输入
	switch(n){//特判
		case 1:printf("%lld\n",r-l+1);return 0;//只有一个，随便取一个。
		case 2:printf("%lld\n",(r-l+1)*(r-l));return 0;//只有两个，取任意两个。
		default:(n>40)?(puts("0"),exit(0)):(solve());return 0;//如果大于40那么无解。
	}
} 
```

---

## 作者：jhdonghj (赞：1)

# 题意

求出长度为$n$，并且所有元素都在$[l,r]$范围之内的等比数列的个数。

$n,l,r\le 10^7$

# 题解

首先我们知道指数函数的增长率很大，所以我们根据直觉猜测当$n$很大的时候答案是$0$，那么我们接下来尝试证明它。

令数列公比$q=\frac qp$，数列首项为$a$，那么数列末项应该是$a(\frac qp)^{n-1}$，因为所有的数字都要在$[l,r]$范围之内并且都为整数，所以$p^{n-1}|a,a(\frac qp)^{n-1}\le r$，不妨设$a=p^{n-1}b$，于是我们就得到了两个限制：
$$
l\le a=p^{n-1}b\le r\\
l\le a(\frac qp)^{n-1}=q^{n-1}b\le r
$$
即
$$
b\in[\lceil\frac l{p^{n-1}}\rceil,\lfloor\frac r{p^{n-1}}\rfloor]\bigcap[\lceil\frac l{q^{n-1}}\rceil,\lfloor\frac r{q^{n-1}}\rfloor]
$$
同时注意到当$n\ge25$时，$p^{n-1}\ge2^{24}=16,777,216>10^7$，一定无解。

于是我们就可以暴力枚举$\frac qp$进而统计答案，但是当$n=1,2$时这个算法会退化为$O(r^2)$，而这是无法通过的，考虑特判。当$n=1$时，答案就是$r-l+1$；当$n=2$时，答案就是$(r-l+1)(r-l)$，不难证明。排除了这两种情况之后，$p,q$的搜索范围至多是$O(\sqrt r)$的，总时间复杂度就是$O(r)$，可以解决该问题。

# Code

```c++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, l, r, ans, pw[10100];
int qpow(ll a, int b) {
    ll res = 1;
    while(b) {
        if(b & 1) res *= a;
        a *= a, b >>= 1;
    }
    return res > INT_MAX ? INT_MAX : res;
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
signed main() {
    scanf("%d %d %d", &n, &l, &r);
    if(n > 24) return puts("0"), 0;
    if(n == 1) return printf("%d\n", r - l + 1), 0;
    if(n == 2) return printf("%lld\n", (r - l + 1ll) * (r - l)), 0;
    for(int i = 1; ; i++) if((pw[i] = qpow(i, n - 1)) > r) break;
    for(int p = 1; pw[p] <= r; p++)
        for(int q = 1; pw[q] <= r; q++)
            if(gcd(p, q) == 1 && Mp(p, q) != Mp(1, 1)) {
                int L = max((l + pw[p] - 1) / pw[p], (l + pw[q] - 1) / pw[q]);
                int R = min(r / pw[p], r / pw[q]);
                ans += max(0, R - L + 1);
            }
    printf("%d\n", ans);
    return 0;
}
```



---

## 作者：maxyzfj (赞：0)

### 题目链接
[CF](https://codeforces.com/problemset/problem/758/F)，[luogu](https://www.luogu.com.cn/problem/CF758F)。

### 标签
数论，暴力枚举。

### 题意简述

求使得所有项都在 $[l,r]$ 之间的 $n$ 项的等比数列的数量（公比不为 $1$）。

### 题解

声明：以下内容中的 $V$ 均指值域（即 $10^7$）。

设公比为 $\dfrac{q}{p}\ (\gcd (p,q)=1,\dfrac{q}{p}\not=1)$，则首项为 $p^{n-1}$ 的倍数，末项为 $q^{n-1}$ 的倍数。

因此，虽然 $n$ 有 $10^7$ 的级别，但是当 $n\ge25$ 时，答案都是零（因为首项和末项至少有一个大于等于 $2^{n-1}$）。

我们先特判掉 $n=1$ 和 $n=2$ 的情况。

对于 $n\ge 3$ 的情况，考虑一个暴力做法：枚举 $p$（范围从 $1$ 到 $\sqrt{V}$），再枚举 $p^{n-1}$ 的倍数作为首项，再枚举 $q$（范围从 $1$ 到 $\sqrt{V}$）。为了防止重复，应当预处理 $\gcd$ 并判掉 $\gcd(p,q)\not=1$ 的情况。

这样计算次数在 $\sum\limits_{p=1}^{\sqrt{V}}(\dfrac{V}{p^2}\cdot\sqrt{V})$ 左右，约为 $\dfrac{\pi^2V\sqrt{V}}{6}$，所以暴力做法的时间复杂度为 $O(V\sqrt{V})$，我们考虑优化。

我们注意到等比数列是成对出现的（原数列和将其反转），例如 $9,6,4$ 和 $4,6,9$。我们发现每一对中两个数列的公比互为倒数，因此我们只需要枚举小于 $1$ 的公比，即将暴力做法中 $q$ 的枚举范围改为 $1$ 到 $p-1$。

这样计算次数是 $\sum\limits_{p=1}^{\sqrt{V}}(\dfrac{V}{p^2}\cdot p)$，时间复杂度为 $O(V\ln V)$，时限 4s，可以通过。

[CF AC 记录](https://codeforces.com/problemset/submission/758/299451992)。

---

