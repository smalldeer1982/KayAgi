# [ARC150B] Make Divisible

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc150/tasks/arc150_b

正整数 $ A,\ B $ が与えられます。

非負整数 $ X,\ Y $ であって、 $ B+Y $ が $ A+X $ の倍数となるようなものに対する $ X+Y $ の最小値を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 100 $
- $ 1\ \leq\ A,\ B\ \leq\ 10^9 $
- 入力される値はすべて整数

### Sample Explanation 1

$ 1 $ 個目のテストケースについて、$ X=1,\ Y=1 $ とすると $ B+Y=24 $ は $ A+X=12 $ の倍数になります。このとき $ X+Y=2 $ であり、$ X+Y $ はこれより小さくすることはできないので答えは $ 2 $ です。 $ 2 $ 個目のテストケースについて、$ X=0,\ Y=0 $ とすると $ B+Y=16 $ は $ A+X=8 $ の倍数になります。

## 样例 #1

### 输入

```
5
11 23
8 16
4394 993298361
95392025 569922442
8399283 10293```

### 输出

```
2
0
65
2429708
8388990```

# 题解

## 作者：NobodyThere (赞：7)

### Solution

这里提供一种**根号分治**的做法。

记答案为 $sum$，显然，我们有 $sum<a$。这是因为满足 $a\mid(b+y)$ 的最小的 $y\in\mathbb N$ 小于 $a$。

对 $a$ 的大小进行分类讨论：

1. 当 $a\leq\sqrt b$ 时，直接枚举 $x\in[0,a)$ 即可，复杂度 $\mathcal O(\sqrt b)$。
1. 当 $a>\sqrt b$ 时，不难发现 $\dfrac{b}{a}<\sqrt b$。记 $d=\left\lceil\dfrac{b}{a}\right\rceil$，$d'=\dfrac{b+y}{a+x}$，那么 $sum$ 取 $min$ 时， $d'\leq d$。
	
	证明：
    
    若 $d'>d$，则 $d'(a+x)\geq (d+1)(a+x)$。
    
    于是我们得到：
    
    $$\begin{aligned}&b+y\\
    %=\ &d'(a+x)\\
    \geq\ &(d+1)(a+x)\\
    %=\ &da+dx+a+x\\
    \geq\ &da+(a+x)\\
    %=\ &\left\lceil\dfrac{b}{a}\right\rceil\cdot a+(a+x)\\
    \geq\ &b+(a+x).\end{aligned}$$
    
    所以 $y\geq a+x$。也就是说，$y$ 此时取的不是最优值。
    
    综上，我们只需要枚举 $d'\in[1,d]$ 即可。复杂度 $\mathcal O(d)=\mathcal O(\sqrt b)$。

于是这道题就以 $\mathcal O(\sqrt b)$ 的复杂度做完了。

### Code

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
int T, a, b, s, ans;
int udiv(const int x, const int y) {return (x + y - 1) / y;}
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &a, &b);
		if(a >= b) { // 记得特判 a >= b 的情况
			printf("%d\n", a - b);
			continue;
		}
		s = sqrt(b); ans = std::min(b - a, ((a - b) % a + a) % a);
		if(a <= s) { // 分类讨论
			for(int i = 1; i <= a; i++) {
				int x = a + i;
				ans = std::min(ans, i + ((x - b) % x + x) % x);
			}
		} else {
			for(int i = 2; i <= a; i++) {
				int x = udiv(b, i);
				if(x < a) break; // 本质上，这个边界特判和上述的差不多
				ans = std::min(ans, x - a + ((x - b) % x + x) % x);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：cmrhhh (赞：3)

## [[ARC150B] Make Divisible](https://www.luogu.com.cn/problem/AT_arc150_b)解题报告

### 前言

这题非常好，窝被**根号分治**骗进来，写了数论分块而去，感觉题解区大家思路多少都有点不同。我写的数论题很少，看不懂大佬的过程，只能手推了，下面是蒟蒻的过程。

### 思路

先看 $b\le a$ 时，把 $b$ 补齐 $a$ 即可，之后默认 $b>a$ 虽然没啥用。

然后自然有柿子 $k(A+X)=(B+Y)$，其中 $X,Y\ge 0$ 且 $k\in \mathbb{Z^+}$。

然后很自然就是用 $X,Y>0$ 推出 $k$ 的范围，试一下发现很好解出： 
$$
\left\lfloor\frac{B+Y}{A}\right\rfloor\ge k\ge\left\lceil\frac{B}{A+X}\right\rceil
$$
然后感性理解一波，$B+Y=\left\lceil\frac{B}{A+X}\right\rceil\times(A+X)$。

因为此时 $(A+X)\mid(B+Y)$。

那么完整柿子：
$$
X+Y=X+\left\lceil\frac{B}{A+X}\right\rceil\times(A+X)-B
$$
发现向上取整可以整数分块，怎么搞？感性理解下面柿子：

$$\left\lceil\frac{a}{b}\right\rceil=\left\lfloor\frac{a}{b}+\frac{b-1}{b}\right\rfloor=\left\lfloor\frac{a-1}{b}+1\right\rfloor$$

分块时某一段的左端点一定是一段里面最优的。

### 代码

在实现上出了点锅，在 $r$ 取到最后的时候还要再算一次。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int t;
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>t;
	while(t--){
		ll a,b;
		cin>>a>>b;
		if(a>=b){cout<<a-b<<"\n";continue;}//b不足就补齐
		ll ans=1e18,r;
		for(ll l=a;l<=b-1;l=r+1){
			r=min(b-1,(b-1)/((b-1)/l));
			ans=min(ans,(l-a)+(1+(b-1)/l)*l-b);
		}r++;
		ans=min(ans,(r-a)+(1+(b-1)/r)*r-b);
		cout<<ans<<"\n";
	}
	return 0;
} 
```

$\LaTeX$

---

## 作者：Miraik (赞：2)

然后我们发现对于每个 $i$，答案可以表示为：

$$ ans=\left\{
\begin{array}{rcl}
i      &      & {a+i \mid b}\\
i+(a+i)-(b \bmod (a+i))    &      & {a+i \nmid b}\\

\end{array} \right. $$

设最后的 $a$ 变为 $a+i$，则必然 $b$ 会变为 $\lceil \frac{b}{a+i} \rceil  \times (a+i)$。


于是我们对 $\lceil \frac{b}{a+i} \rceil$ 整除分块。


然后容易有结论：对于每个块，其左端点必然为块内最优值。

证明很简单：设左端点为 $p$。

对于非左端点的数 $q$，对于 $b \bmod p = 0$ 的情况易证；

否则有 $p<q ,b \bmod p > b \bmod q$

然后可知 $(p-i)+(p-(b \bmod p)) < (q-i)+(q-(b \bmod q))$。

于是得证。（这里的 $p,q$ 均指 $a+i$）

然后就很平凡了。

```cpp
int a=read(),b=read();
if(b%a==0){ puts("0"); continue; }
if(b<a){ printf("%d\n",a-b); continue; }
int ans=min(b-a,a-b%a);
for(int i=(b+a-1)/a,l=a;i>1;l=(b+i-2)/(i-1),i=(b+l-1)/l) 
	if(b%l==0) ans=min(ans,l-a);
    else ans=min(ans,(l-a)+l-b%l);
printf("%d\n",ans);
```


---

## 作者：analysis (赞：1)

模拟赛场因为不会向上取整整除分块而死。

现在会了。

---

### 向上取整整除分块

他可以转化为向下取整。

发现：

$$
\lceil\frac{b}{a}\rceil 
= \lfloor\frac{b}{a}\rfloor + [b \bmod a \neq 0] = \lfloor\frac{b}{a} + \frac{a-1}{a}\rfloor = \lfloor\frac{b + a - 1}{a}\rfloor
$$



---

发现确定了 $X$ 后，$Y$ 随之确定。

于是答案为：

$$
X + \lceil\frac{B}{X+A}\rceil(X+A)-B
$$

向上取整整除分块即可，取左端点。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a, b;
int t;
int cil(int up, int dn) { return (up / dn) + (up % dn != 0); }
int gvx(int x) { return x + cil(b, a + x) * (a + x) - b; }
signed main() {
    cin >> t;
    while (t--) {
        cin >> a >> b;
        if (b <= a) {
            cout << a - b << '\n';
            continue;
        }

        int ans = min(b - a, gvx(0));
        for (int i = 1, r; i <= b; i = r + 1) {
            r = (b + i - 1) / ((b + i - 1) / i);
            if (i <= a)
                continue;
            else
                ans = min(ans, gvx(i - a));
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Chase12345 (赞：0)

简单化题意：找到 $B+Y=k \cdot(A+X)$，最小化 $X+Y$。

可以得到 $Y=k \cdot(A+X)-B$，又 $y \ge 0$，所以有 $k \cdot(A+X) \ge B$，$A+X \ge \left \lceil \frac{B}{k} \right \rceil-A$，并且 $X \ge \left \lceil \frac{B}{k} \right \rceil -A$，由于 $X \ge 0$，所以必然：$\left \lceil \frac{B}{k} \right \rceil \ge A$，$k \le \frac{B}{A-1}$。

考虑代入，这里省略过程，给出 $X+Y=\max(0,\left \lceil \frac{B}{k} \right \rceil - A)+k \cdot A-B$。

考虑根号分治。

我们发现，$k \le \sqrt B$ 时，可以考虑暴力枚举。

$k>\sqrt B$ 的话，$\left \lceil \frac{B}{k} \right \rceil \le \sqrt B$，枚举 $t=\left \lceil \frac{B}{k} \right \rceil$，对于 $t$，找到 $k$ 的范围即可。

具体而言，对于 $t$，$\left \lceil \frac{B}{k} \right \rceil\le k \le \left \lfloor \frac{B}{t-1} \right \rfloor$。那么我们可以枚举 $t \in \left[1,\sqrt B\right]$，对于 $t$，取 $k=\left \lceil \frac{B}{t} \right \rceil$，这是 $k$ 的最小值，对应 $X+Y$ 的最小值。

总的复杂度：
* 小的 $k$ 的部分：$O(\sqrt B)$。
* 大的 $k$ 的部分，同样 $O(\sqrt B)$，因为仅仅枚举了 $t$，每个 $t$ 均可以直接对应结果。

则可以通过此题。

---

## 作者：mountain_climber (赞：0)

交了一吨终于过了，原来是多测中特判直接 `return 0;` 了，属实难绷。

首先观察柿子。$(a+x) \mid (b+y)$ 给定 $a,b$ 求 $\min(x+y),0\leq x,y$。我们可以考虑对于一个确定的 $x$ 如何求 $\min(x+y)$ 处的 $y$。

显然，对于 $(a+x) \mid b$ 的情况，$\min(x+y)=x$。

对于 $(a+x) \nmid b$ 的情况，不难发现 $\min(x+y)=x+(a+x)-b \bmod (a+x)$ 将 $b \bmod (a+x)$ 转化为 $b - (a+x) \times \lfloor \frac{b}{a+x} \rfloor$ 原式变为 $x+(a+x)-b + (a+x) \times \lfloor \frac{b}{a+x} \rfloor$。

注意到 $\lfloor \frac{b}{a+x} \rfloor$，可以考虑数论分块。显然的，对于每一块，其左端点会让 $(a+x)$ 尽量的小，从而让整个式子尽量的小，考虑每个块的左端点即可。注意我们不能从 $1$ 开始跳，因为 $a$ 可能在一个块的中间而不是左端点上，所以要从 $a$ 开始跳。对于所有 $(a+x) \mid b$ 的情况，只可能存在于右端点上，顺便统计即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=2e18;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL),cout.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        int a,b;
        cin>>a>>b;
        int ans=inf;
        if(a>b){
            cout<<a-b<<'\n';
            continue;
        }
        for(int l=a,r;l<=b;l=r+1){
            r=b/(b/l);
            if(b%r==0){
                ans=min(ans,r-a);
            }
            ans=min(ans,l*(b/l+2)-(a+b));
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：zhujiangyuan (赞：0)

考虑枚举 $X$，则 $B+Y$ 最小为 $\left\lceil\dfrac{B}{A+X}\right\rceil\times (A+X)$，则 $Y$ 最小值为 $\left\lceil\dfrac{B}{A+X}\right\rceil\times (A+X)-B$。

所以确定 $X$ 后，$X+Y$ 的最小值为 $X+\left\lceil\dfrac{B}{A+X}\right\rceil\times (A+X)-B$。

发现若 $\left\lceil\dfrac{B}{A+X}\right\rceil$ 相同，$X$ 越小越好，考虑向上整除分块，$x$ 每次取块的左端点即可。**注意：整除分块枚举的是 $A+X$ 的值。**

时间复杂度 $O(\sqrt{n})$。

不会向上整除分块可以参考 [oi-wiki](https://oi-wiki.org/math/number-theory/sqrt-decomposition/#%E5%90%91%E4%B8%8A%E5%8F%96%E6%95%B4%E7%9A%84%E6%95%B0%E8%AE%BA%E5%88%86%E5%9D%97)。

```cpp
int cil (int x, int y) { return (x + y - 1) / y; }
int get (int x) { return x + cil (b, a + x) * (a + x) - b;}
void solve () {
    int ans = 1e18;
    cin >> a >> b;
    if (a >= b) return cout << a - b << '\n', void ();
    ans = min (b - a, get (0));
    for (int l = 1, r; l < b; l = r + 1) {
        r = (b - 1) / ((b - 1) / l);
        if (l <= a) continue;
        else ans = min (ans, get (l - a));
    }
    ans = min (ans, get (b - a));
    cout << ans << '\n';
}
```

---

## 作者：LiveZoom (赞：0)

## Description

[link](https://atcoder.jp/contests/arc150/tasks/arc150_b)

## Solution

我们先考虑暴力枚举 $x$ 再求 $y$。

如果 $a+x\big|b$，则 $(x+y)_{\min}=x$。

否则 $(x+y)_{\min}=x+(a+x)-b\bmod (a+x)$。

把 $b\bmod (a+x)$ 转化一下为 $b-(a+x)\times \big\lfloor\dfrac{b}{a+x}\big\rfloor$，令 $f(x)=\big\lfloor\dfrac{b}{a+x}\big\rfloor$，则对于所有 $f(x)$ 相同的 $x$ 中，$x$ 越小越好，于是直接对于 $f(x)$ 整除分块就行了。

时间复杂度：$O(T\sqrt{b})$

## Code

```cpp
#include <cstdio>
#include <iostream>

#define int long long

using namespace std;

int T, a, b;

signed main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("o.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> a >> b;
    if (b % a == 0) {
      cout << "0\n";
      continue;
    } else if (a > b) {
      cout << a - b << '\n';
      continue;
    }
    int ans = min(b - a, a - b % a);
    for (int i = (a + b - 1) / a, l = a; i > 1; l = (b + i - 2) / (i - 1), i = (b + l - 1) / l) {
      if (b % l == 0) {
        ans = min(ans, l - a);
      } else {
        ans = min(ans, l - a + l - b % l);
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

