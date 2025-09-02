# [AGC038C] LCMs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc038/tasks/agc038_c

長さ $ N $ の整数列 $ A_0,A_1,\cdots,A_{N-1} $ があります。 次式の値を求めてください。

- $ \sum_{i=0}^{N-2}\ \sum_{j=i+1}^{N-1}\ \mathrm{lcm}(A_i,A_j) $

ここで、$ \mathrm{lcm}(x,y) $ は、$ x $ と $ y $ の最小公倍数を意味します。 なお、答えは非常に大きくなることがあるので、$ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ A_i\ \leq\ 1000000 $
- 入力される値はすべて整数である。

### Sample Explanation 1

$ \mathrm{lcm}(2,4)+\mathrm{lcm}(2,6)+\mathrm{lcm}(4,6)=4+6+12=22 $ です。

## 样例 #1

### 输入

```
3
2 4 6```

### 输出

```
22```

## 样例 #2

### 输入

```
8
1 2 3 4 6 8 12 12```

### 输出

```
313```

## 样例 #3

### 输入

```
10
356822 296174 484500 710640 518322 888250 259161 609120 592348 713644```

### 输出

```
353891724```

# 题解

## 作者：Cherished (赞：23)

---
title: [AGC038C] LCMs
tags: [数学, 莫比乌斯反演]


---

[题目来源](https://atcoder.jp/contests/agc038/tasks/agc038_c)

##### 前言

因为这道题中包含了比较多的常见套路所以写了这篇题解，给想学习数论的人，下文中如果出现比较常见的套路，都会着重说明

### 题面描述

- 给定一个长度为 $N$ 的数列 $A_1, A_2, A_3, \dots, A_N$。
- 请你求出 $\sum_{i=1}^{N}\sum_{j=i+1}^{N}\mathrm{lcm}(A_i,A_j)$ 的值模 $998244353$ 的结果。
- $1 \leq N \leq 2 \times 10^5$，$1 \leq A_i \leq 10^6$。

### 题目解答

首先$\sum_{i=1}^{N}\sum_{j=i+1}^{N}\mathrm{lcm}(A_i,A_j)$ 第二个 $\sum$ 不是从 $1$ 开始的这让我们很难受，所以：
$$
\sum_{i=1}^{N}\sum_{j=i+1}^{N}\mathrm{lcm}(A_i,A_j)=\frac{\sum_{i=1}^{N}\sum_{j=1}^{N}\mathrm{lcm}(A_i,A_j)-\sum_{i=1}^{N}{A_i}}{2}
$$
现在我们的就是要算 $\sum_{i=1}^{N}\sum_{j=1}^{N}\mathrm{lcm}(A_i,A_j)$，之后的过程就比较套路了。（下文中会使用 $(A_i,A_j)$ 表示 $A_i$ 和 $A_j$ 的最大公约数）
$$
\begin{aligned}
\sum_{i=1}^{N}\sum_{j=1}^{N}\mathrm{lcm}(A_i,A_j)&=\sum_{i=1}^{N}\sum_{j=1}^{N}{\frac{A_i \times A_j}{(A_i, A_j)}} \\
&=\sum_{i=1}^{N}\sum_{j=1}^{N}\sum_{d=1}^{Max}{\frac{A_i \times A_j}{d}[(A_i,A_j)=d]}
\end{aligned}
$$
然后是数论题的常见处理方法，把后面的 $\sum$ 提到前面，至于如何判断什么时候能向前提，下面会简单的说以下：

+ 我们发现 $\frac{A_i \times A_j}{d}[(A_i,A_j)=d]$ 。这个式子中 $\frac{1}{d}$ 这一项只和 $d$ 有关，而和 $i,j$ 无关，但是我们是在最后一个 $\sum$ 处枚举的 $d$ ，那么这个时候我们就可以考虑把最后一个 $\sum$ 向前提取。

$$
\begin{aligned}
\sum_{i=1}^{N}\sum_{j=1}^{N}\mathrm{lcm}(A_i,A_j)&=\sum_{i=1}^{N}\sum_{j=1}^{N}\sum_{d=1}^{Max}{\frac{A_i \times A_j}{d}[(A_i,A_j)=d]} \\
&=\sum_{d=1}^{Max}\frac{1}{d}\sum_{i=1}^{N}\sum_{j=1}^{N}{A_i\times A_j\times [(A_i,A_j)=d]}
\end{aligned}
$$

我们看到了 $[(A_i,A_j)=d]$ 这种式子，这个时候就要多加注意了，因为当我们看到形如 $[k=1]$ 这种式子时我们就可以进行反演了，方法如下。
$$
[k=1]=\sum_{d|k}\mu(d)
$$
但是 $[(A_i,A_j)=d]$ 这个式子，后面的是 $d$ 而不是 $1$ ，那我们考虑一下怎么把它转化成 $1$。
$$
[(A_i,A_j)=d][d|A_i][d|A_j]=[(\frac{A_i}{d},\frac{A_j}{d})=1][d|A_i][d|A_j]
$$
因为我们发现 $d|A_i,d|A_j$ 所以就有上面的转化。
$$
\begin{aligned}
\sum_{i=1}^{N}\sum_{j=1}^{N}\mathrm{lcm}(A_i,A_j)&=\sum_{d=1}^{Max}\frac{1}{d}\sum_{i=1}^{N}\sum_{j=1}^{N}{A_i\times A_j\times [(A_i,A_j)=d]} \\
&=\sum_{d=1}^{Max}\frac{1}{d}\sum_{i=1}^{N}\sum_{j=1}^{N}{A_i\times A_j\times [d|A_i][d|A_j][(\frac{A_i}{d},\frac{A_j}{d})=1]}
\end{aligned}
$$
之后进行反演
$$
\begin{aligned}
\sum_{i=1}^{N}\sum_{j=1}^{N}\mathrm{lcm}(A_i,A_j)&=\sum_{d=1}^{Max}\frac{1}{d}\sum_{i=1}^{N}\sum_{j=1}^{N}{A_i\times A_j\times [d|A_i][d|A_j][(\frac{A_i}{d},\frac{A_j}{d})=1]} \\
&=\sum_{d=1}^{Max}\frac{1}{d}\sum_{i=1}^{N}\sum_{j=1}^{N}{A_i\times A_j\times [d|A_i][d|A_j]\sum_{t|(\frac{A_i}{d},\frac{A_j}{d})}}{\mu(t)}
\end{aligned}
$$
还是和上面一样，最后的式子之和 $t$ 有关，和 $i,j,d$没有关系，所以我们也把它往前提。（这个地方可以放在 $d$ 的前面也可以放在后面）
$$
\begin{aligned}
\sum_{i=1}^{N}\sum_{j=1}^{N}\mathrm{lcm}(A_i,A_j)&=\sum_{d=1}^{Max}\frac{1}{d}\sum_{i=1}^{N}\sum_{j=1}^{N}{A_i\times A_j\times [d|A_i][d|A_j]\sum_{t|(\frac{A_i}{d},\frac{A_j}{d})}}{\mu(t)} \\
&=\sum_{d=1}^{Max}\sum_{t=1}^{\lfloor \frac{Max}{d} \rfloor}\frac{\mu(t)}{d}\sum_{i=1}^{N}\sum_{j=1}^{N}{A_i\times A_j\times [d|A_i][d|A_j][t|A_i][t|A_j]} \\
&=\sum_{d=1}^{Max}\sum_{t=1}^{\lfloor \frac{Max}{d} \rfloor}\frac{\mu(t)}{d}\sum_{i=1}^{N}\sum_{j=1}^{N}{A_i\times A_j\times [dt|A_i][dt|A_j]}
\end{aligned}
$$
我们来观察后面这个式子 $\sum_{i=1}^{N}\sum_{j=1}^{N}{A_i\times A_j\times [d|A_i][d|A_j]}$ ，对于任何一个 $d|A$ 都会对任何一个 $d|B$ ，包括 $A$ 和 $B$ 是一个数的时候。

回忆一下我们在初中学习过的公式：

+ $$
  (a+b)^2=a^2+b^2+2ab
  $$

+ $$
  (a+b+c)^2=a^2+b^2+c^2+2ab+2bc+2ca
  $$

+ $$
  \dots\dots
  $$

注意到 $(A_1+A_2+A_3+A_4+\dots+A_k)^2$ 刚好就是 $A_x (x \in [1,k])$ 对于所有 $A_y(y \in [1,k])$ 都有贡献，所以：
$$
\sum_{i=1}^{N}\sum_{j=1}^{N}{A_i\times A_j\times [dt|A_i][dt|A_j]}=(\sum_{i=1}^{N}A_i\times [dt|A_i])^2
$$

$$
\begin{aligned}
\sum_{i=1}^{N}\sum_{j=1}^{N}\mathrm{lcm}(A_i,A_j)&=\sum_{d=1}^{Max}\sum_{t=1}^{\lfloor \frac{Max}{d} \rfloor}\frac{\mu(t)}{d}(\sum_{i=1}^{N}A_i\times [dt|A_i])^2
\end{aligned}
$$

我们发现 $A_i$ 的值域只有 $10^6$ ，所以我们可以用 $c_i$ 表示有多少个 $i$，这样就有：
$$
\sum_{i=1}^{N}A_i\times [dt|A_i]=\sum_{dt|i}^{Max}i\times c_i
$$
$\sum_{T|i}^{Max}i\times c_i$显然可以用类似筛法的一个东西用 $O(nlog(n))$的方法求出对于每一个 $T$ 的值，具体的时间复杂度证明大概就是（虽然极为不严谨）：
$$
\int_{1}^{n}\frac{n}{x}\ dx \sim n\times\ln(n)
$$
当然如果你做过[这道题](https://www.luogu.com.cn/problem/P5495)，并掌握了 $4$ 种卷集，那么你也可以用 $O(nloglog(n))$ 的时间复杂度解决它。

现在我们的式子变成了：
$$
\sum_{i=1}^{N}\sum_{j=1}^{N}\mathrm{lcm}(A_i,A_j)=\sum_{d=1}^{Max}\sum_{t=1}^{\lfloor \frac{Max}{d} \rfloor}\frac{\mu(t)}{d}(\sum_{dt|i}^{Max}i\times c_i)^2
$$
那么我们只需要枚举 $d$ 再枚举 $t$ 就可以利用 $O(nlog(n))$ 的时间算出答案。
既然我们已经计算出了 $\sum_{i=1}^{N}\sum_{j=1}^{N}\mathrm{lcm}(A_i,A_j)$ 的值，我们把它减去 $\sum_{i=1}^{N}{A_i}$ ，再除 $2$，就可以算出答案了。

写的时候注意一下常数，少一点除法 QAQ

```cpp
int n, m, a[N], p[M], c, f[M], mu[M];
modint C[M], Ans, Mu[M];

int main() {
	read(n), Build_Mod(998244353);
	for (int i = 1; i <= n; i++) read(a[i]), m = max(m, a[i]);
	mu[1] = 1;
	for (int i = 2; i <= m; i++) {
		if (!f[i]) p[++c] = i, f[i] = 1, mu[i] = -1;
		for (int j = 1; j <= c && i * p[j] <= m; j++) {
			f[i * p[j]] = 1, mu[i * p[j]] = -mu[i];
			if (i % p[j] == 0) {mu[i * p[j]] = 0; break;}
		}
	}
	for (int i = 1; i <= n; i++) C[a[i]] += a[i];
	for (int j = 1; j <= c; j++)
		for (int i = m / p[j]; i >= 1; i--)
			C[i] += C[i * p[j]];
	for (int i = 1; i <= m; i++) Mu[i] = Ch(mu[i]), C[i] = C[i] * C[i];
	for (int i = 1; i <= m; i++) {
		modint t = (modint)1 / i;
		for (int j = 1; j <= m / i; j++)
			Ans += Mu[j] * C[i * j] * t;
	}
	for (int i = 1; i <= n; i++) Ans -= a[i];
	print(Ans / 2);
	return 0;
}
```



---

## 作者：xiaoyaowudi (赞：14)

~~我不明白这题为什么要莫比乌斯反演~~

### 题意
求 $\sum_{i< j}\operatorname{lcm}\left(a_i,a_j\right)$，且 $a_i\le10^6$。
### 解答
令
$$
\begin{aligned}
f\left(x\right)&=\sum_{i=1}^n\sum_{j=i+1}^{n}a_ia_j\left[x \mid \gcd\left(a_i,a_j\right)\right]\\
&=\sum_{i=1}^n\sum_{j=i+1}^{n}\left(a_i\left[x\mid a_i\right]\right)\left(a_j\left[x\mid a_j\right] \right) \\
&=\dfrac{1}{2}\cdot\left(\left(\sum_{x\mid i}^{n}a_i\right)^2-\sum_{x\mid i}^{n}a_i^2\right) \\
g\left(x\right)&=\sum_{i=1}^n\sum_{j=i+1}^{n}a_ia_j\left[ \gcd\left(a_i,a_j\right)=x\right] \\
&=\sum_{i=1}^n\sum_{j=i+1}^{n}a_ia_j\left[x \mid \gcd\left(a_i,a_j\right)\right]-\sum_{k>x,x\mid k}^n\sum_{i=1}^n\sum_{j=i+1}^{n}a_ia_j\left[\gcd\left(a_i,a_j\right)=k\right] \\
&=f\left(x\right)-\sum_{k>x,x\mid k}^ng\left(k\right)
\end{aligned}
$$
则从小到大枚举 $x$ 即可计算出所有的 $f$，$g$，时间复杂度为 $\sum_{i=1}^A\dfrac{A}{i}+\mathcal{O}\left(n\right)=\mathcal{O}\left(A\ln A+n\right)$，答案为
$$
\begin{aligned}
\sum_{i=1}^n\sum_{j=i+1}^{n}\operatorname{lcm}\left(a_i,a_j\right)&=\sum_{i=1}^n\sum_{j=i+1}^{n}\dfrac{a_ia_j}{\gcd\left(a_i,a_j\right)}\\
&=\sum_{d\ge1}\sum_{i=1}^n\sum_{j=i+1}^{n}\dfrac{a_ia_j}{d}\left[\gcd\left(a_i,a_j\right)=d\right]\\
&=\sum_{d\ge1}\dfrac{g\left(d\right)}{d}
\end{aligned}
$$
### 代码
```cpp#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
constexpr int N=200010,K=1000010,p=998244353;
int inv[K],sum[K],a[N],n,cnt[K];
int main(){
    scanf("%d",&n);for(int i=1;i<=n;++i) scanf("%d",&a[i]),++cnt[a[i]];
    inv[1]=1;for(int i=2;i<K;++i) inv[i]=1ll*(p-p/i)*inv[p%i]%p;
    int ans=0;
    for(int i=K-1;i;--i){
        int s1=0,s2=0;
        for(int j=i;j<K;j+=i) s1=(s1+1ll*cnt[j]*j%p)%p,s2=(s2+1ll*cnt[j]*j%p*j%p)%p;
        sum[i]=1ll*(1ll*s1*s1%p-s2+p)*inv[2]%p;
        for(int j=(i<<1);j<K;j+=i) sum[i]=(sum[i]-sum[j]+p)%p;
        // if(i<10) printf("%d %d %d %d %d\n",i,sum[i],s1,s2,inv[i]);
        ans=(ans+1ll*inv[i]*sum[i]%p)%p;
    }
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：xixike (赞：9)

[更好的阅读体验](https://www.cnblogs.com/xixike/p/15695569.html)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/AT5200)

## SOlution

题意非常清晰明了，下面我们来谈一谈如何求解。

实际上跟 P3911 是一样的，我们先考虑 $i$ 和 $j$ 都从 1 开始的情况，即：



$$\sum\limits_{i = 1}^n\sum\limits_{j = 1}^nlcm(a_i, a_j)$$



直接求是不太行的，所以我们把输入的属放到一个桶里面，设为 $t$。

那么我们最终要求的答案就是：
$$
\sum_{i=1}^n\sum_{j=1}^n lcm(i,j)\times t[i] \times t[j]
$$
下面就是~~喜闻乐见~~的推式子环节啦。

$$\sum_{i=1}^n\sum_{j=1}^n \frac{i \times j\times t[i] \times t[j]}{\gcd(i,j)} $$
$$\sum_{i=1}^n\sum_{j=1}^n\sum\limits_{d = 1}^n\frac{i \times j\times t[i] \times t[j]}{d}[\gcd(i,j) == d]$$

把 $d$ 提前：
$$
\sum_{d=1}^n\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{n}{d} \rfloor}\frac{id \times jd\times t[id] \times t[jd]}{d}[\gcd(i,j) == 1]
$$
上下同时除以 $d$：
$$
\sum_{d=1}^n\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{n}{d} \rfloor}[\gcd(i,j)=1]d\times i \times j \times t[id] \times t[jd]
$$
经典莫比乌斯反演：
$$
\sum_{d=1}^n\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{k|(i,j)}\mu(k) \times d\times i \times j \times t[id] \times t[jd]
$$
把 $k$ 提前：
$$
\sum_{d=1}^n\sum_{k=1}^{\lfloor \frac{n}{d}\rfloor}\sum_{i=1}^{\lfloor \frac{n}{kd}\rfloor}\sum_{j=1}^{\lfloor \frac{n}{kd}\rfloor}\mu(k)\times d \times i \times j \times k^2 \times t[idk] \times t[jdk]
$$
套路的令 $T = dk$：

$$\sum\limits_{T = 1}^n\sum\limits_{k | T}\sum_{i=1}^{\lfloor \frac{n}{T}\rfloor}\sum_{j=1}^{\lfloor \frac{n}{T}\rfloor}\mu(k)\times T \times k \times i \times j \times t[iT] \times t[jT]$$

$$\sum_{T=1}^{n}T\times(\sum_{i=1}^{\lfloor \frac{n}{T} \rfloor}i\times t[iT])^2 \times \sum_{k|T}\mu(k)\times k$$



至此，我们的式子就推完了，最后一项预处理，前面的暴力计算答案即可。

但是我们现在求的是 $j$ 从 1 开始的情况，那从 $i + 1$ 开始的话答案是多少呢？

也很简单，看一张图就明白了：

![AT5200](https://s4.ax1x.com/2021/12/05/oDzu9K.jpg)

我们推的式子是第一个完整的正方形，而答案要求的是右边那个上三角。

所以我们减去对角线再除以二就是题目要求的答案了。

即：

$$ans = \frac{res - \sum\limits_{i = 1}^nlcm(a_i, a_i) }{2}$$

> $res$ 是上面推的式子所求的值，对角线上的值显然就是 $a$ 数组的和。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 5e4;
int n, m;
int t[N + 10], p[N + 10], mu[N + 10], tot;
ll sum[N + 10];
bool vis[N + 10];

inline void euler(int n){
    mu[1] = 1;
    for(int i = 2; i <= n; ++i){
        if(!vis[i]) p[++tot] = i, mu[i] = -1;
        for(int j = 1; j <= tot && i * p[j] <= n; ++j){
            vis[i * p[j]] = 1;
            if(i % p[j] != 0) mu[i * p[j]] = -mu[i];
            else break;
        }
    }
    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; j += i)
            sum[j] += 1ll * mu[i] * i;
}

inline ll solve(int n){
    ll ans = 0;
    for(int T = 1; T <= n; ++T){
        ll res = 0;
        for(int i = 1; i <= n / T; ++i) res += 1ll * i * t[i * T];
        ans += 1ll * T * res * res * sum[T];
    }
    return ans;
}

int main(){
    n = read();
    for(int i = 1, x; i <= n; ++i)
        t[x = read()]++, m = max(m, x);
    euler(m);
    write(solve(m)), puts("");
    return 0;
}
```

$$\_EOF\_$$

---

## 作者：CYJian (赞：7)

以下讨论中，令 $M=\max(A_i)$。

$$ \sum_{i=1}^{N}\sum_{j=i+1}^{N} \mathrm{lcm}(A_i, A_j) $$

考虑将上面的式子变个形：

$$ \frac{\sum_{i=1}^{N}\sum_{j=1}^{N} \mathrm{lcm}(A_i, A_j)-\sum_{i=1}^{N}A_i}{2} $$

其他的部分都好算，我们现在的主要问题是 $ \sum_{i=1}^{N}\sum_{j=1}^{N} \mathrm{lcm}(A_i, A_j) $ 的计算。

考虑 $\mathrm{lcm}(x,y)=\frac{x \times y}{\gcd(x,y)}$：

$$ \sum_{i=1}^{N}\sum_{j=1}^{N} \frac{A_i \times A_j}{\gcd(A_i, A_j)} $$

然后枚举 $d = \gcd(A_i,A_j)$：

$$ \sum_{d=1}^{M}\frac{1}{d}\sum_{i=1}^{N}\sum_{j=1}^{N} A_i \times A_j [\gcd(A_i,A_j)=d] $$

$$ \sum_{d=1}^{M}\frac{1}{d}\sum_{i=1}^{N}\sum_{j=1}^{N} A_i \times A_j [d|A_i][d|A_j]\sum_{t|\frac{A_i}{d}\ \mathrm{and}\ t|\frac{A_j}{d}} \mu(t)$$

$$ \sum_{d=1}^{M}\sum_{t=1}^{M/d} \frac{\mu(t)}{d}\sum_{i=1}^{N}\sum_{j=1}^{N} A_i \times A_j [td|A_i][td|A_j]$$

$$ \sum_{d=1}^{M}\sum_{t=1}^{M/d}\frac{\mu(t)}{d}\left(\sum_{i=1}^{N} A_i [td|A_i]\right)^2 $$

现在的主要问题是，如何计算 $\left(\sum_{i=1}^{N} A_i [td|A_i]\right)^2$。

考虑开一个桶 $C_x$ 表示满足 $A_i=x$ 的 $A_i$ 的和。那么我们令 $f_x$ 表示满足 $x|A_i$ 的 $A_i$ 的和，则有 $f_x = \sum_{x|d}C_d$。

$C_x$ 的计算可以 $O(n)$ 完成。$f_x$ 的计算可以用类似埃式筛的写法，做到 $O(M \log M)$。大概就是枚举 $x$，然后枚举 $x$ 的倍数。枚举的次数是 $\sum_{i=1}^{M}\left\lfloor\frac{M}{i}\right\rfloor \approx M \ln M$。

我们将 $f_x$ 带入原式得到：

$$ \sum_{d=1}^{M}\sum_{t=1}^{M/d}\frac{\mu(t)f_{td}^2}{d} $$

这里就不难用 $O(M \log M)$ 的时间计算了。原理和上面计算 $f_x$ 一样。

然后再带回到二式，就可以计算出最后的结果了。

下面的代码略有不同，原因在于其中计算 $f_x$ 的时候，将二式也考虑进去了，也就是代码中的 $f_d'$ 表示 $\frac{f_d^2-\sum_{d|A_i}A_i^2}{2}$。这应该也不难理解。

$\rm Code$：

```cpp
const int MAXN = 200100;
const int MAXV = 1000100;
const int mod = 998244353;

inline void Add(int&x, int y) { x += y, x -= x >= mod ? mod : 0; }
inline int Mod(int x) { return x >= mod ? x - mod : x; }

template<typename T>
inline void chkmax(T&a, T b) { a = a > b ? a : b; }

int a_1[MAXV + 1];
int a_2[MAXV + 1];
int f_d[MAXV + 1];

int tot;
int pri[MAXV + 1];
int miu[MAXV + 1];
int inv[MAXV + 1];
int chk[MAXV + 1];
int F[MAXV + 1];

inline int init(int mx) {
	inv[1] = 1, miu[1] = 1;
	for(int i = 2; i <= mx; i++) {
		inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
		if(!chk[i]) pri[++tot] = i, miu[i] = mod - 1;
		for(int j = 1; j <= tot; j++) {
			if(i * pri[j] > mx) break;
			chk[i * pri[j]] = 1;
			if(i % pri[j] == 0) break;
			miu[i * pri[j]] = mod - miu[i];
		}
	}
	for(int i = 1; i <= mx; i++) {
		for(int j = i << 1; j <= mx; j += i)
			Add(a_1[i], a_1[j]), Add(a_2[i], a_2[j]);
		f_d[i] = 1LL * (1LL * a_1[i] * a_1[i] - a_2[i] + mod) % mod * inv[2] % mod;
	}
}

int main() {
	int n = Re, N = 0;
	for(int i = 1; i <= n; i++) {
		int v = Re;
		chkmax(N, v); Add(a_1[v], v);
		Add(a_2[v], 1LL * v * v % mod);
	} init(N); int res = 0;
	for(int d = 1; d <= N; d++) {
		for(int T = d, t = 1; T <= N; T += d, ++t) {
			Add(res, 1LL * inv[d] * miu[t] % mod * f_d[T] % mod);
		}
	} printf("%d\n", res);
	return 0;
}
```

---

## 作者：__gcd (赞：4)

upd：修改了一处笔误

莫比乌斯反演。

先把这个式子转化一下：

$$\frac{1}{2}(\sum_{i=1}^n\sum_{j=1}^n\operatorname{lcm}(a_i,a_j)-\sum_{i=1}^na_i)$$

接下来我们只看前面这个东西。把 $\operatorname{lcm}(a_i,a_j)$ 换掉：

$$\sum_{i=1}^n\sum_{j=1}^n\frac{a_ia_j}{\gcd(a_i,a_j)}$$

套路地枚举 $\gcd$。

$$\sum_{d=1}^n\frac{1}{d}\sum_{i=1}^n\sum_{j=1}^n[\gcd(a_i,a_j)=d]a_ia_j$$

令 $f(x)=\sum_{i=1}^n\sum_{j=1}^n[\gcd(a_i,a_j)=x]a_ia_j$。尝试把它反演：

$$F(x)=\sum_{x|d}f(d)=\sum_{i=1}^n\sum_{j=1}^n[x|\gcd(a_i,a_j)]a_ia_j=\sum_{i=1}^n[x|a_i]a_i\sum_{j=1}^n[x|a_j]a_j$$

令 $g(d)=\sum_{i=1}^n[d|a_i]a_i$，则 $F(x)=g^2(x)$。$g$ 函数可以在 $O(C\log C)$ 的时间内求出。$C$ 为值域。

从 $F(x)$ 中得到 $f(x)$：

$$f(x)=\sum_{x|d}F(d)\mu(\frac{d}{x})$$

带入：

$$\sum_{d=1}\frac{1}{d}\sum_{d|t}F(t)\mu(\frac{t}{d})$$

上面这个式子也可以 $O(C\log C)$ 计算。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define re register
#define int long long
using namespace std;
inline int read() {
	int x = 0; bool op = false;
	char c = getchar();
	while(!isdigit(c))op |= (c == '-'), c = getchar();
	while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return op ? -x : x;
}
const int C = 1e6;
const int N = 2e5 + 10;
const int Mod = 998244353;
int n, tot;
int f[C + 10], pri[C], miu[C + 10], vis[C + 10], inv[C + 10];
int mod(int x) {return (x % Mod + Mod) % Mod;}
void sieve(int x) {
	miu[1] = 1;
	for(int i = 2; i <= x; i++) {
		if(vis[i] == 0) {pri[++tot] = i; miu[i] = -1;}
		for(int j = 1; j <= tot; j++) {
			int p = pri[j];
			if(i * p > x)break;
			vis[i * p] = 1;
			if(i % p == 0) {miu[i * p] = 0; break;}
			miu[i * p] = -miu[i];
		}
	}
	for(int i = 1; i <= x; i++) {
		for(int j = 2; i * j <= x; j++) {
			f[i] = (f[i] + f[i * j]) % Mod;
		}
	}
	return ;
}
signed main() {
	n = read();
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		int x = read();
		f[x] = (f[x] + x) % Mod;
		sum = (sum + x) % Mod;
	} 
	sieve(1000000);
	inv[1] = 1;
	for(int i = 2; i <= C; i++)inv[i] = mod(-inv[Mod % i] * (Mod / i));
	int ans = 0;
	for(int i = 1; i <= C; i++) {
		int res = 0;
		for(int j = 1; i * j <= C; j++) {
			res = mod(res + mod(f[i * j] * f[i * j] * miu[j]));
		}
		ans = mod(ans + mod(inv[i] * res));
	}
	printf("%lld", mod((ans - sum) * 499122177));
	return 0;
}

```


---

## 作者：chihik (赞：3)

$$\sum_{i=1}^n\sum_{j=i+1}^n\text{lcm}(A_i,A_j)$$

$$\frac{\sum_{i=1}^n\sum_{j=1}^n\text{lcm}(A_i,A_j)-\sum_{i=1}^nA_i}{2}$$

所以只需要快速求到 $\sum_{i=1}^n\sum_{j=1}^n lcm(A_i,A_j)$ 即可 , 其实就是 [P3911](https://www.luogu.com.cn/problem/P3911)。

下面给一下过程：

令 $c_i$ 表示 $i$ 出现的次数，$n$ 为最大数字。

$$\sum_{i=1}^n \sum_{j=1}^nc_i  \times c_j \times lcm(i,j)$$

$$\sum_{i=1}^n \sum_{j=1}^nc_i  \times c_j \times \frac{i \times j}{gcd(i,j)}$$

$$\sum_{k=1}^n\sum_{i=1}^n \sum_{j=1}^n [gcd(i,j)=k] c_i  \times c_j \times \frac{i \times j}{k}$$

$$\sum_{k=1}^n\sum_{i=1}^{\lfloor \frac{n}{k} \rfloor } \sum_{j=1}^{\lfloor \frac{n}{k} \rfloor} [gcd(i,j)=1] c_{ik}  \times c_{jk} \times i \times j \times k$$

$$\sum_{k=1}^n\sum_{i=1}^{\lfloor \frac{n}{k} \rfloor } \sum_{j=1}^{\lfloor \frac{n}{k} \rfloor} \sum_{d|gcd(i,j)}\mu(d) \times c_{ik}  \times c_{jk} \times i \times j \times k$$

$$\sum_{k=1}^n\sum_{d=1}^{\lfloor \frac{n}{k} \rfloor} \mu(d) \times d^2 \sum_{i=1}^{\lfloor \frac{n}{kd} \rfloor } \sum_{j=1}^{\lfloor \frac{n}{kd} \rfloor}  c_{ikd}  \times c_{jkd} \times i \times j \times k$$

$$\sum_{k=1}^n\sum_{kd=1}^{n}\mu(d) \times d^2\sum_{i=1}^{\lfloor \frac{n}{kd} \rfloor } \sum_{j=1}^{\lfloor \frac{n}{kd} \rfloor} c_{ikd}  \times c_{jkd} \times i \times j \times k$$

$$\sum_{T=1}^n T(\sum_{d|T}\mu(d) \times d )\sum_{i=1}^{\lfloor \frac{n}{T} \rfloor } \sum_{j=1}^{\lfloor \frac{n}{T} \rfloor} c_{iT}  \times c_{jT} \times i \times j$$

$$\sum_{T=1}^n T(\sum_{d|T}\mu(d) \times d ) (\sum_{i=1}^{\lfloor \frac{n}{T} \rfloor } c_{iT} \times i)^2$$

第一个括号预处理，第二个括号直接暴力算。

预处理和查询复杂度均为 $\Theta(n \ln n)$。



```cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 1e6 , Mod = 998244353;
int n , m , Ans , cnt[ MAXN + 5 ];

int k , prime[ MAXN + 5 ] , mu[ MAXN + 5 ] , f[ MAXN + 5 ];
bool vis[ MAXN + 5 ];
void sieve( ) {
    mu[ 1 ] = 1;
    for( int i = 2 ; i <= MAXN ; i ++ ) {
        if( !vis[ i ] ) {
            prime[ ++ k ] = i;
            mu[ i ] = -1;
        }
        for( int j = 1 ; j <= k && i * prime[ j ] <= MAXN ; j ++ ) {
            vis[ i * prime[ j ] ] = 1;
            if( i % prime[ j ] == 0 ) break;
            mu[ i * prime[ j ] ] = -mu[ i ];
        }
    }
    for( int i = 1 ; i <= MAXN ; i ++ )
        for( int j = i ; j <= MAXN ; j += i )
            f[ j ] = ( f[ j ] + i * mu[ i ] + Mod ) % Mod;
}

int main( ) {
    sieve( );
    scanf("%d",&n);
    for( int i = 1 , x ; i <= n ; i ++ ) {
        scanf("%d",&x) , Ans = ( Ans - x + Mod ) % Mod;
        cnt[ x ] ++ , m = max( m , x );
    }
    n = m;

    for( int i = 1 ; i <= n ; i ++ ) {
        int tmp = 0;
        for( int j = 1 ; j <= n / i ; j ++ )
            tmp = ( tmp + 1ll * cnt[ i * j ] * j % Mod ) % Mod;
        Ans = ( Ans + 1ll * i * f[ i ] % Mod * tmp % Mod * tmp % Mod ) % Mod;
    }

    printf("%d", 1ll * Ans * 499122177 % Mod );
    return 0;
}
```


---

## 作者：Dream404 (赞：2)

显然问题等价于求

$$\sum_{i=1}^n\sum_{j=1}^n\text{lcm}(A_i,{A_j)}$$

$$=\sum_{d=1}^n\frac 1d\sum_{i=1}^nA_i\sum_{j=1}^nA_j[\gcd(A_i,A_j)==d]$$

反演，设

$$F(d)=\sum_{i=1}^nA_i\sum_{j=1}^nA_j[d|\gcd(A_i,A_j)]$$

$$f(d)=\sum_{i=1}^nA_i\sum_{j=1}^nA_j[\gcd(A_i,A_j)==d]$$

$$F(d)=\sum_{d|e}f(e)$$

$$f(d)=\sum_{d|e}F(e)\mu(\frac ed)$$

显然$F(d)$可以暴力枚举约数然后开一个桶记录再平方。

那么再枚举一次约数就好了。

复杂度$O(n\ln n)$ 

---

## 作者：Saber_Master (赞：1)

[AT5200 [AGC038C] LCMs](https://www.luogu.com.cn/problem/AT5200)

$$\sum_{i=1}^{n}\sum_{j=i+1}^{n}lcm(A_i,A_j)=\frac{\sum_{i=1}^n\sum_{j=1}^nlcm(A_i,A_j) -\sum_{i=1}^n A_i}{2}$$

我们先考虑求出$\sum_{i=1}^n\sum_{j=1}^nlcm(A_i,A_j)$这个式子.

设$cnt_x$表示$x$出现的次数，则有如下式子：


$$\begin{aligned}
\sum_{i=1}^{n} \sum_{j=1}^{n} lcm(A_i, A_j)&=\sum_{i=1}^n \sum_{j=1}^n lcm(i, j)\cdot cnt_i\cdot cnt_j \\
&=\sum_{i=1}^n  \sum_{j=1}^n\frac{i\cdot j}{gcd(i,j)}\cdot cnt_i \cdot cnt_j\\
&=\sum_{d=1}^n \sum_{i=1}^n \sum_{j=1}^n[gcd(i, j)==d]\frac{i\cdot j}{d}\cdot cnt_i \cdot cnt_j \\
&=\sum_{d=1}^n \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor} \sum_{j=1}^{\lfloor \frac{n}{d}\rfloor}[gcd(i, j)==1]\frac{id\cdot jd}{d}\cdot cnt_{id} \cdot cnt_{jd}\\
&=\sum_{d=1}^n \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor} \sum_{j=1}^{\lfloor \frac{n}{d}\rfloor}[gcd(i, j)==1] i\cdot j\cdot d\cdot cnt_{id} \cdot cnt_{jd}\\

&=\sum_{d=1}^n \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor} \sum_{j=1}^{\lfloor \frac{n}{d}\rfloor}\sum_{s|gcd(i, j)}\mu(s)\cdot i\cdot j\cdot d\cdot cnt_{id} \cdot cnt_{jd}\\
&=\sum_{d=1}^n d\sum_{i=1}^{\lfloor \frac{n}{d}\rfloor} \sum_{j=1}^{\lfloor \frac{n}{d}\rfloor}\sum_{s|gcd(i, j)}\mu(s)\cdot i\cdot j\cdot cnt_{id} \cdot cnt_{jd}\\
&=\sum_{d=1}^nd\sum_{s=1}^{\lfloor \frac{n}{d}\rfloor}\mu(s)\sum_{i=1}^{\lfloor \frac{n}{ds} \rfloor}\sum_{j=1}^{\lfloor \frac{n}{ds} \rfloor}s^2\cdot i\cdot j\cdot cnt_{ids}\cdot cnt_{jds}\\

&=\sum_{d=1}^nd\sum_{s=1}^{\lfloor \frac{n}{d}\rfloor}\mu(s)s^2(\sum_{i=1}^{\lfloor \frac{n}{ds} \rfloor}i\cdot cnt_{ids})^2\\

&=\sum_{ds=1}^n ds \sum_{s|ds}\mu(s)\cdot s\cdot (\sum_{i=1}^{\lfloor \frac{n}{ds} \rfloor}i\cdot cnt_{ids})^2
\end{aligned}
$$

令$T=ds$,则有
$$\begin{aligned}
\sum_{i=1}^{n} \sum_{j=1}^{n} lcm(A_i, A_j)&=\sum_{T=1}^{n}T\sum_{s|T}(\mu(s)\cdot s)\cdot (\sum_{i=1}^{\lfloor \frac{n}{T} \rfloor}i\cdot cnt_{iT})^2
\end{aligned}
$$

中间括号可以爆算，后面括号也可以爆算，具体做法是枚举倍数刷表，复杂度为调和级数，上界$O(n\log n)$.

注意两个小点：

-  记得开$long \ long$
- 最后的除以$2$需要转化为乘上$2$的逆元，在模$998244353$意义下其值是$499122177$

```cpp
const ll N=1e6+6;

ll prime[N], tot, mu[N];
bool book[N];

inline void euler_solve(ll lim){
	mu[1]=1;
	for (R ll i=2; i<=lim; i++){
		if (!book[i]) prime[++tot]=i, mu[i]=-1;
		for (R ll j=1; j<=tot && 1ll*prime[j]*i<=lim; j++){
			book[i*prime[j]]=true;
			if (i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=-mu[i];
		}
	}
} 

ll n, cnt[N];

ll sum1[N], sum2[N];
ll res;

inline ll quick_pow(ll x, ll y){
	ll res=1; 
	for (; y; y>>=1){
		if (y&1) (res*=x)%=mod;
		(x*=x)%=mod;
	}
	return res;
}

inline ll inv(ll x){
	return quick_pow(x, mod-2);
}
int main(){
	read(n);
	for (R ll i=1, x; i<=n; i++){
		read(x); ++cnt[x];
	}
	euler_solve(1000000);
	for (R ll i=1; i<=1000000; i++)
		for (R ll j=i; j<=1000000; j+=i)
			sum1[j]+=mu[i]*i;
	for (R ll i=1; i<=1000000; i++){
		for (R ll j=1; j<=1000000/i; j++) (sum2[i]+=j*cnt[j*i])%=mod;
	}
	for (R ll i=1; i<=1000000; i++) (res+=i*sum2[i]%mod*sum2[i]%mod*sum1[i])%=mod;
	for (R ll i=1; i<=1000000; i++) if (cnt[i]) (res-=i*cnt[i])%=mod;
	((res%=mod)+=mod)%=mod;
	(res*=inv(2))%=mod;
	writeln(res);
}
```


---

## 作者：Polaris_Dane (赞：1)

给出数列$a_1,a_2,a_3\cdots a_n$

求$\sum_{i=1}^n\sum_{j=1}^n\text{lcm}(a_i,a_j)$

我们考虑列一个表

那么第$i$行，第$j$列代表$\text{lcm}(a_i,a_j)$

那么我们要求的就是这个正方形表不包含对角线的下(上)三角形

考虑如何计算，我们可以很容易计算$\sum_{i=1}^n\sum_{j=1}^n\text{lcm}(a_i,a_j)$

令$f_i$为是$i$的倍数的数的两两之乘积

$g_i$为最大公因数是$i$的数两两之乘积

$m$为值域大小

当然也可以直接暴力莫反，这个方法比较简单

$f_i=\sum\limits_{i|d} g_d$

然后一次反演得到

$g_i=\sum\limits_{i|d}\mu(\dfrac {d} {i})f_d$

答案就是$\sum_{i=1}^m\dfrac {g_i} {i}$

来自于$\text{lcm}(i,j)=\dfrac {ij} {\gcd(i,j)}$

完美解决

这个正方形表是对称的，且对角线就是数列$a$

所以答案就出来了，即

$\dfrac {\sum_{i=1}^n\sum_{j=1}^n\text{lcm}(a_i,a_j)-\sum_{i=1}^na_i} {2}$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<set>
#include<queue>
#define M 1000020
#define inf 0x3f3f3f3f
#define LL long long
#define int long long
const int mod=998244353;
using namespace std;
inline int read(){
	int f=1,x=0;char s=getchar();
	while (!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while (isdigit(s)){x=(x<<1)+(x<<3)+(s^48),s=getchar();}
	return x*f;
}
int n,a[M],f[M],cnt[M],prime[M],tot,mu[M],is[M],g[M],ans,maxx,inv[M];
inline void init(void){
	mu[1]=1,inv[1]=1;
	for (int i=2;i<=M-10;i++){
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		if (!is[i]) prime[++tot]=i,mu[i]=mod-1;
		for (int j=1;j<=tot&&prime[j]*i<=M-10;j++){
			is[i*prime[j]]=1;
			if (i%prime[j]) mu[i*prime[j]]=mod-mu[i];
			else break;
		}
	}
}
signed main(void){
	n=read();init();
	for (int i=1;i<=n;i++) a[i]=read(),cnt[a[i]]++,maxx=max(maxx,a[i]);
	for (int i=1;i<=maxx;i++){
		for (int j=i;j<=maxx;j+=i) f[i]=(f[i]+cnt[j]*j%mod)%mod;
		f[i]=f[i]*f[i]%mod;
	}
	for (int i=1;i<=maxx;i++){
		for (int j=i;j<=maxx;j+=i)
			g[i]=(g[i]+mu[j/i]*f[j]%mod)%mod;
		ans=(ans+g[i]*inv[i]%mod)%mod;
	}
	for (int i=1;i<=n;i++) ans=(ans-a[i]+mod)%mod;
	printf("%lld",ans*inv[2]%mod);
	return 0;
}
```


---

## 作者：紫钦 (赞：0)

# 前言

本题的做法在已有题解中已经阐述得较为详细了，本篇题解旨在补充一个**进一步**化简式子的方法，以及与之匹配的预处理、计算方式。

# 优化方法：狄利克雷卷积

设 $f(T)$ 表示 $\{a_n\}$ 中的 $T$ 的倍数和，并设 $m=\max\{a_i\}$，则可得：

$\ \ \ \ \sum_{i=1}^{n}\sum_{j=1}^n\text{lcm}(a_i,a_j)$

$=\sum_{d=1}^m\sum_{k=1}^{\lfloor\frac{m}{d}\rfloor}\frac{\mu(k)}{d} f^2(dk)$

此处，注意到 $d$ 和 $k$ 的上限乘积不超过 $m$，且式子里 $f(dk)$ 项，故考虑枚举 $d$ 与 $k$ 的乘积。

设 $T=dk$，则有：

$\ \ \ \ \sum_{d=1}^m\sum_{k=1}^{\lfloor\frac{m}{d}\rfloor}\frac{\mu(k)}{d} f^2(dk)$

$=\sum_{T=1}^{m}\sum_{d|T}\frac{1}{d}\mu(\frac{T}{d})f^2(T)$

其中，$\sum_{d|T}\frac{1}{d}\mu(\frac{T}{d})$ 是狄利克雷卷积的形式，我们尝试研究该函数。

设 $g(n)=(\frac{1}{id}\times \mu)(n)=\sum_{d|n}\frac{1}{d}\mu(\frac{n}{d})$，

由于 $\frac{1}{id}(n)$ 和 $\mu(n)$ 均为积性函数，由于积性函数与积性函数的狄利克雷卷积也是积性函数，故 $g(n)$ 是积性函数。

（关于“积性函数与积性函数的狄利克雷卷积也是积性函数”性质的证明，可见我的这篇博客[狄利克雷卷积](https://www.luogu.com.cn/blog/user37839/di-li-ke-lei-juan-ji)，证明在该篇博客的中部）

积性函数一定是可以线性筛的，所以下面来研究 $g(n)$ 的性质：

+ $g(1)=1$；

+ 设 $P$ 是质数，则 $g(P)=\frac{1}{P}(1-P)$；

+ 设 $P$ 是质数，$k\geqslant 1$，则 $g(P^k)=\frac{1}{P^k}(1-P)$；

+ 设 $P$ 是质数，且 $i$ 与 $P$ 互质，则 $g(iP)=g(i)g(P)$；

+ 设 $P$ 是质数，且 $i$ 与 $P$ 不互质，不妨设 $i=jP^k$，其中 $j$ 与 $P$ 互质，则 $g(iP)=g(j)\frac{1}{P^{k+1}}(1-P)=g(j)g(P^k)\frac{1}{P}=g(i)\frac{1}{p}$；

其中第二条性质给出了质数的 $g$ 函数计算方法，第四、第五条性质给出了线性筛时计算被筛元素的 $g$ 函数的方法。

注意到本题是在对 $998244353$ 取模的意义下进行计算的，故我们在计算 $g(n)$ 时需要求出每个质数的逆元。而 $1\sim n$ 中的质数个数大约是 $\Theta(\frac{n}{\ln n})$ 的，使用费马小定理求逆元时，单次复杂度为 $O(\log n)$，故预处理 $g(1)\sim g(n)$ 的复杂度为 $O(n)$。

于是可以线性筛出 $g(n)$，使得计算的复杂度降为 $O(n)$。

然而预处理 $f(T)$ 的复杂度为 $m\ln m$，所以对于计算式复杂度的优化只能算作常数优化了。不过化为狄利克雷卷积的形式再做优化是莫比乌斯反演题目的常见操作，此处可以练习一下。

# $AC$ 代码：

```cpp
#include<cstdio>
#define ljm 998244353
#define MAXN 200005
#define MAXM 1000006
#define endl putchar('\n')

int g[MAXM],f[MAXM],prime[78500],iv[MAXM]; /* prime[78498]=999983. */
bool vis[MAXM];

inline int max(int a,int b) {return a<b?b:a;}
int Mod(int a) {return a<ljm?a:a-ljm;}
long long fast_pow(long long a,int b)
{
	a%=ljm;
	long long ans=1;
	while(b) {
		if(b&1) ans=ans*a%ljm;
		b>>=1; a=a*a%ljm; 
	}
	return ans;
}
long long inv(int n)
{
	if(iv[n]) return iv[n];
	else return iv[n]=fast_pow(n,ljm-2);
}
void init(int n)
{
	static int cnt=0;
	long long k;
	g[1]=1;
	for(int i=2;i<=n;++i) {
		if(!vis[i]) prime[++cnt]=i,g[i]=inv(i)*(1ll-i+ljm)%ljm;
		for(int j=1;j<=cnt && (k=(long long)i*prime[j])<=n;++j) {
			vis[k]=true;
			if(i%prime[j]) g[k]=(long long)g[i]*g[prime[j]]%ljm;
			else {
				g[k]=(long long)g[i]*inv(prime[j])%ljm;
				break;
			}
		}
	}
	for(int i=1;i<=n;++i) {
		//if(!f[i]) continue; /* f[i]定义时并没有要求 i 一定在数列 {an} 中，所以这句不能写。 */
		for(int j=i<<1;j<=n;j+=i) f[i]=Mod(f[i]+f[j]);
	}
}
int read()
{
	char ch=getchar();int x=0;
	while(ch<'0' || ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x*10)+(ch^48),ch=getchar();
	return x;
}
int main()
{
	int n,s,m,ans;
	n=read();
	m=0;
	s=0;
	for(int i=1,a;i<=n;++i) {
		a=read();
		f[a]=Mod(f[a]+a);
		s=Mod(s+a);
		m=max(m,a);
	}
	init(m);
	ans=0;
	for(int i=1;i<=m;++i) ans=(ans+(long long)g[i]*f[i]%ljm*f[i])%ljm;
	printf("%lld",(ans-s+ljm)*inv(2)%ljm);
	return 0;
} 
```

---

## 作者：derta (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT5200)

一道莫比乌斯反演题

首先~~将柿子魔改一下~~容易看出原式为
$$\dfrac{(\sum_{i=1}^{n}\sum_{j=1}^{n}\operatorname{lcm}(A_i,A_j))-\sum_{i=1}^{n}A_i}{2}$$

其他的好求，就是
$$\sum_{i=1}^{n}\sum_{j=1}^{n}\operatorname{lcm}(A_i,A_j)$$
比较烦人，那我们把它单独拎出来

首先，根据 $\operatorname{lcm}(a,b)=\dfrac{ab}{\gcd(a,b)}$，得
$$\sum_{i=1}^n\sum_{j=1}^n\dfrac{A_iA_j}{\gcd(A_i,A_j)}$$

令 $M=\max \limits_{1 \leqslant i \leqslant n}A_i$，枚举 $\gcd(A_i,A_j)$ 的值
$$\sum_{k=1}^M\sum_{i=1}^n\sum_{j=1}^n[k|A_i][k|A_j][\gcd(A_i,A_j)=k]\dfrac{A_iA_j}{k}$$

套路地将 $A_i,A_j$ 除以 $k$
$$\sum_{k=1}^M\sum_{i=1}^n\sum_{j=1}^n[k|A_i][k|A_j][\gcd(\dfrac{A_i}{k},\dfrac{A_j}{k})=1]\dfrac{A_iA_j}{k}$$

然后换成 $\mu$
$$\sum_{k=1}^M\sum_{i=1}^n\sum_{j=1}^n[k|A_i][k|A_j]\dfrac{A_iA_j}{k}\sum_{d|\frac{A_i}{k},d|\frac{A_j}{k}}\mu(d)$$

把 $d$ 与 $\dfrac{1}{k}$ 拎到前面
$$\sum_{k=1}^M\dfrac{1}{k}\sum_{d=1}^{\lfloor\frac{M}{k}\rfloor}\mu(d)\sum_{i=1}^n\sum_{j=1}^n[kd|A_i][kd|A_j]A_iA_j$$

把与 $j$ 无关的拎出来
$$\sum_{k=1}^M\dfrac{1}{k}\sum_{d=1}^{\lfloor\frac{M}{k}\rfloor}\mu(d)\sum_{i=1}^n[kd|A_i]A_i\sum_{j=1}^n[kd|A_j]A_j$$

我们发现最后的两个 $\sum$ 是一样的
$$\sum_{k=1}^M\dfrac{1}{k}\sum_{d=1}^{\lfloor\frac{M}{k}\rfloor}\mu(d)(\sum_{i=1}^n[kd|A_i]A_i)^2$$

先看后面的一坨

令
$$h(x)=\sum_{i=1}^{n}[A_i=x]$$
$$f(x)=\dfrac{\sum_{i=1}^n[x|A_i]A_i}{x}$$

则
$$f(x)=\sum_{x|d}^{M}h(d)\dfrac{d}{x}$$

这个是可以 $O(M \log M)$ 筛出 $f(1),f(2),\cdots,f(M)$ 的，具体看代码就能理解了

代回原式，得
$$\sum_{k=1}^M\dfrac{1}{k}\sum_{d=1}^{\lfloor\frac{M}{k}\rfloor}\mu(d)(f(kd)kd)^2$$

化简，得
$$\sum_{k=1}^M\sum_{d=1}^{\lfloor\frac{M}{k}\rfloor}\mu(d)f(kd)kd^2$$

这个就很容易做到 $O(M \log M)$ 了，直接模拟即可

最后的最后，别忘了代回去最开始的柿子

于是这题就没了

$\rm{My \  Code}:$

```cpp
#include <iostream>
const int MAXN = 200000, MAXA = 1000000, lnMAXA = 10, MOD = 998244353;
int Prime[MAXA/lnMAXA + 5], size;
//Prime[i]表示第i个质数，size表示筛到现在质数的数量 
bool not_prime[MAXA + 5];
//not_prime[i]为true表示i不是质数，为false则是质数 
int mu[MAXA + 5];
//mu[i]即第i个莫比乌斯函数 
int f[MAXA + 5], h[MAXA + 5], sum, m;
//f[i], h[i]如柿子所述 
int n;

inline int minus_to_mod(int n)
{ return n >= MOD ? n - MOD : n; }

inline int plus_to_mod(int n)
{ return n < 0 ? n + MOD : n; }

//这个函数用来避免不能整除2或res-sum<0的情况 
inline int change(int n) {
	int t = plus_to_mod(n);
	return (t & 1) ? t + MOD : t;
}

//读入 
void input() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	//cin, cout优化 
	std::cin >> n;
	for(int i = 1; i <= n; ++i) {
		int a;
		std::cin >> a;
		++h[a]; //更新h[a] 
		sum = minus_to_mod(sum + a); //由于a<=1e6，所以最多做一次减法 
		if(m < a) m = a; //更新最大值 
	}
}

//筛 
void sieve() {
	//筛mu 
	not_prime[1] = true;
	mu[1] = 1; 
	for(int i = 2; i <= m; ++i) {
		if(not_prime[i] == false) { //不是质数 
			Prime[size++] = i; //加入质数表 
			mu[i] = MOD - 1; //mu[i]=-1, mod MOD意义下为MOD-1 
		}
		for(int j = 0; j < size && i*Prime[j] <= m; ++j) {
			not_prime[i*Prime[j]] = true;
			if(i%Prime[j] == 0) break;
			mu[i*Prime[j]] = MOD - mu[i];
			//mu[i*Prime[j]]=-mu[i], mod MOD意义下为MOD-mu[i] 
		}
	}
	//筛f 
	for(int i = 1; i <= m; ++i)
		for(int j = 1; i*j <= m; ++j)
			f[i] = (1LL*f[i] + 1LL*h[i*j]*j)%MOD; //别忘了乘1LL 
}

long long solve() {
	//直接算答案 
	int res = 0;
	for(int i = 1; i <= m; ++i)
		for(int j = 1, k = i; k <= m; ++j, k += i)
			res = minus_to_mod(res + 1LL*mu[j]*f[k]%MOD*f[k]%MOD*k%MOD*j%MOD); //疯狂取余 
	return change(res - sum) >> 1;
}

int main() {
	input();
	sieve();
	std::cout << solve() << "\n";
	return 0;
}
```

---

## 作者：lzk5627 (赞：0)

首先orz楼上CYJian
对于这种题目,什么lcm,gcd之类的,首先可以联想到莫比乌斯

然后我们可以考虑枚举 $lcm$ 计算出来每个 $lcm$ 的个数,设 $nu_i$ 表示 $a_i$ 为 $i$ 的数有多少个,为了方便计算,我们可以先把相同的 $a_i$ 的 $lcm$ 算出来,那么式子就变成了这样

$\sum_{i=1}^{m}\sum_{j=i+1}^{m}\frac{ij}{gcd(i,j)}nu_inu_j$

然后考虑划式子,套路枚举gcd

$\sum_{d=1}^md\sum_{i=1}^{m/d}\sum_{j=i+1}^{m/d}ijnu_{id}nu_{jd}$

$\sum_{d=1}^md\sum_{k=1}^{m/d}k^2\mu(k)\sum_{i=1}^{m/dt}\sum_{j=i+1}^{m/dt}ijnu_{idt}nu_{jdt}$

$\sum_{T=1}^mT\sum_{d|T}d\mu(d) \sum_{i=1}^{m/T}inu_{iT}\sum_{j=i+1}^{m/T}jnu_{jT}$

那么最后枚举 $T$ ,就是计算 $2$ 个部分的东西

$\sum_{d|T}d\mu(d)$ 显然是可以直接 $O(mln(m))$ 计算的

$\sum_{i=1}^{m/T}inu_{iT}\sum_{j=i+1}^{m/T}jnu_{jT}$这个可以用一个后缀和计算,总复杂度也是 $O(mlnm)$

然后这题就做完了

附代码


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	register int x=0;
	register char ch=getchar();
	while(ch<'0'||ch>'9')	ch=getchar();
	while(ch>='0'&&ch<='9')	x=x*10+(ch^48),ch=getchar();
	return x;
}
const int N=1e6+5;
const int P=998244353;
int n,m,now,a[N],b[N],c[N],vi[N];
long long f(int T){
	int k=m/T,sum=0,ans=0;
	for(int i=1;i<=k;i++)	sum=(sum+1LL*i*a[i*T])%P;
	for(int i=1;i<=k;i++){
		sum=(sum-1LL*i*a[i*T]%P+P)%P;
		ans=(ans+1LL*sum*i%P*a[i*T]%P)%P;
	}
	return ans;
}
int main(){
	n=read(),b[1]=1;
	for(int i=1,x;i<=n;i++)
		++a[x=read()],m=max(m,x);
	for(int i=2;i<=m;i++){
		if(!vi[i])	c[++now]=i,b[i]=-1;
		for(int j=1;j<=now&&c[j]*i<=m;j++){
			vi[c[j]*i]=1;
			if(i%c[j]==0)	break;
			else	b[i*c[j]]=-b[i];
		}
	}
	for(int i=1;i<=m;i++)	c[i]=(P+b[i]*i)%P;
	for(int i=m;i;i--)
		for(int j=i*2;j<=m;j+=i)	c[j]=(c[j]+c[i])%P;
	long long ans=0;
	for(int i=1;i<=m;i++)	ans=(ans+1LL*a[i]*(a[i]-1)/2%P*i)%P;
	for(int i=1;i<=m;i++)	ans=(ans+i*f(i)%P*c[i])%P;
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：zzw4257 (赞：0)

> 经过转化，求$\displaystyle \sum _{i=1}^n\sum _{j=1}^n[A_i,A_j]$


于是许久未碰莫反的我真的脑残

首先前情化简

$$
\begin{aligned}
&\sum _{i=1}^n\sum _{j=1}^n[A_i,A_j]
 =\sum _{i=1}^n\sum _{j=1}^n\frac{A_iA_j}{(A_i,A_j)}
\\=&\sum_d\frac{1}{d}\sum _{i=1}^n\sum _{j=1}^n[(A_i,A_j)=d]A_iA_j
\\=&\sum_d\frac{1}{d}\sum _{d|A_i}\sum _{d|A_j}[(\frac{A_i}{d},\frac{A_j}{d})=1]A_iA_j
\\=&\sum_d\sum_{p=1}^{\lfloor\frac{|A_{max}|}{d}\rfloor}\frac{\mu(p)}{d}\left(\sum_{dp|A_i}A_i\right )^2
\end{aligned}
$$

设$\displaystyle f(n)=\sum_{d|n}\frac{\mu(\frac{n}{d})}{d}=\mu\cdot \frac{1}{id}$，$\displaystyle g(n)=\sum_{n|A_i}A_i=\sum_{n|i}B_i=\mathcal{B}\cdot I$,其中$B_i=i\sum\limits_{j=1}^n[A_j=i]$，则$ans=\sum\limits_{T}f(T)g^2(T)$,前者可以线性筛(也可以真·狄利克雷卷)，后者可以狄利克雷后缀和做到$\mathcal {O(n\ln\ln n)}$求出

```cpp
#include<bits/stdc++.h>
#define N 1000001
#define mod 998244353
using namespace std;
inline void Add(int&x,int y){x=(x+y>=mod)?x+y-mod:x+y;}
int n,lim,pri[N],vis[N],f[N],g[N],inv[N],ans;
inline int qpow(int a,int b){int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;}
inline void Sieve(void){
	int i,j,t;
	g[1]=1;
	for(i=2;i<=lim;++i){
		if(!vis[i])g[pri[++*pri]=i]=(1ll+mod-i)*(inv[i]=qpow(i,mod-2))%mod;
		for(j=1;(t=pri[j]*i)<=lim;++j){
			vis[t]=1;if(!(i%pri[j])){g[t]=1ll*g[i]*inv[pri[j]]%mod;break;}g[t]=1ll*g[pri[j]]*g[i]%mod;
		}
	}for(i=1;i<=*pri;++i)for(j=lim/pri[i];j;--j)Add(f[j],f[pri[i]*j]);
}
signed main(void){
	int i,x;scanf("%d",&n);
	for(i=1;i<=n;++i)scanf("%d",&x),Add(f[x],x),Add(ans,mod-x),lim=max(lim,x);
	Sieve();
	for(i=1;i<=lim;++i)ans=(ans+1ll*g[i]*f[i]%mod*f[i])%mod;
	printf("%lld\n",499122177ll*ans%mod);
	return 0;
}

```

---

## 作者：ricky0916 (赞：0)

这道题其实与[$ P3911 $](https://www.luogu.com.cn/problem/P3911)差不多 ~~（比P3911毒瘤）~~

好，现在我们假设我们已经求出了$ \sum_{i=1}^n\sum_{j=1}^nlcm(i,j) $

那么$ \sum_{i=1}^n\sum_{j=i+1}^nlcm(i,j)=
\frac{\sum_{i=1}^n\sum_{j=1}^nlcm(i,j)-\sum_{i=1}^na_i}{2} $

但是显然不能直接除以$ 2 $（因为~~题目太毒瘤~~除的是分子膜$ 998244353 $的值），所以要乘上$ 998244353^{-1}=499122177 $

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,a[1000010],prime[1000010],check[1000010],miu[1000010],tot,maxx,sum[1000010];
void init(){
    miu[1]=1;
    for(int i=2;i<=1000000;i++){
        if(!check[i]){
            prime[tot++]=i;
            miu[i]=-1;
        }
        for(int j=0;j<tot&&i*prime[j]<=1000000;j++){
            check[i*prime[j]]=1;
            if(i%prime[j]==0){
                miu[i*prime[j]]=0;
                break;
            }
            miu[i*prime[j]]=-miu[i];
        }
    }
    for(int i=1;i<=1000000;i++){
        for(int j=i;j<=1000000;j+=i) sum[j]=(sum[j]+1ll*i*miu[i])%mod;
    }
}
int work(){
    int ans=0;
    for(int i=1;i<=maxx;i++){
        int temp=0;
        for(int j=1;j<=maxx/i;j++){
            temp=(temp+1ll*a[i*j]*j%mod)%mod;
        }
        ans=(ans+1ll*temp*temp%mod*sum[i]%mod*i%mod)%mod;
    }
    return ans;
}
int main(){
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	int temp;
        scanf("%d",&temp);
        a[temp]++;
        maxx=max(maxx,temp);
    }
    int ans=work();
    for(int i=1;i<=1000000;i++) ans=1ll*(ans-1ll*a[i]*i%mod+mod)%mod;
    ans=1ll*ans*((mod+1)/2)%mod;
    printf("%d",ans);
    return 0;
}
```




---

