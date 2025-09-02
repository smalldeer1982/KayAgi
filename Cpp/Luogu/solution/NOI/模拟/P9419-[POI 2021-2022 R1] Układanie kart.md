# [POI 2021/2022 R1] Układanie kart

## 题目背景

译自 [XXIX Olimpiada Informatyczna – I etap](https://sio2.mimuw.edu.pl/c/oi29-1/dashboard/) [Układanie kart](https://sio2.mimuw.edu.pl/c/oi29-1/p/ukl/)。

## 题目描述

我们用以下方法将一个排列递增排序:

一次操作：记第一个数字为 $k$，在排列中找到 $k-1$（$k=1$ 则取 $n$），把 $k-1$ 拉到排列的第一个位置，中间的数字依次后移。

一次操作的价值：$k-1$（或 $n$）在原排列的位置（这个从 $0$ 开始标号）。

一个排列的价值：进行若干次操作直到排列有序，价值为每次操作的价值之和。

给你 $n,m$，求所有 $n!$ 个排列的价值之和，对 $m$ 取模。

## 说明/提示

对于所有数据，$2\leq n\leq 1000000$，$2\leq m\leq 10^9$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $n\leq 10$ | 10 |
| 2 | $n\leq 2000$ | 60 |
| 3 |  | 30 |

## 样例 #1

### 输入

```
2 100
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 100
```

### 输出

```
15
```

## 样例 #3

### 输入

```
10 1000
```

### 输出

```
100
```

## 样例 #4

### 输入

```
500 100000
```

### 输出

```
60000
```

## 样例 #5

### 输入

```
100000 1000
```

### 输出

```
0
```

# 题解

## 作者：_•́へ•́╬_ (赞：13)

困难的。看了官方题解。

## 思路

把操作产生的排列之间的转化关系画成一棵内向树。下图是 $n=3,4$ 的：

![](https://cdn.luogu.com.cn/upload/image_hosting/emooz8y8.png)

可以找到规律：这棵树可以分成 $n$ 个部分，每个部分之间有代价为 $n-1$ 的边相连。

然后官方题解从这里就开始飚式子了。我继续找规律。

下图是 $n=5$ 的图的 $\frac 1 5$。

![](https://cdn.luogu.com.cn/upload/image_hosting/haqnewjj.png)

[这](https://cdn.luogu.com.cn/upload/image_hosting/cdk7o9k6.png) [些](https://cdn.luogu.com.cn/upload/image_hosting/715zn20l.png) [是](https://cdn.luogu.com.cn/upload/image_hosting/3mtsor61.png) $n=6$ [的](https://cdn.luogu.com.cn/upload/image_hosting/3mtsor61.png) [图](https://cdn.luogu.com.cn/upload/image_hosting/iwbbtf23.png) 的 $\frac 1 6$。我把它们打印出来找到了规律：

在 $n-2$ 棵大子树中，第 $i$ 棵大子树的前 $i-1$ 棵小子树与前 $i-1$ 棵大子树完全一样，第 $i$ 棵大子树的其余小子树都与第 $i-1$ 棵大子树完全一样。

## code

```cpp
#include<stdio.h>
#define int long long
int n,mod,ans,pfxcnt,nowcnt,pfxans,nowans,fac;
main()
{
	scanf("%lld%lld",&n,&mod);
	if(n==2){putchar('1');return 0;}
	ans=1;pfxcnt=nowcnt=nowans=pfxans=1;
	for(int i=2;i<=n-2;++i)
	{
		nowans=(pfxans+nowans*(n-i)+nowcnt*((n-i+1)*(n-i)/2%mod))%mod;
		nowcnt=(pfxcnt+nowcnt*(n-i)+1)%mod;
		nowans=(nowans+nowcnt*i)%mod;
		pfxcnt=(pfxcnt+nowcnt)%mod;
		pfxans=(pfxans+nowans)%mod;
		ans=(ans+nowans)%mod;
	}
	fac=1;for(int i=2;i<n;fac=fac*i%mod,++i);
	printf("%lld",(ans*n+fac*((n-1ll)*n/2%mod)%mod*(n-1))%mod);
}
```



---

## 作者：psoet (赞：2)

> 我们用以下方法将一个排列递增排序:

> 一次操作：记第一个数字为 $k$，在排列中找到 $k-1$（$k=1$ 则取 $n$），把 $k-1$ 拉到排列的第一个位置，中间的数字依次后移。

>一次操作的价值：$k-1$（或 $n$）在原排列的位置（这个从 $0$ 开始标号）。

>一个排列的价值：进行若干次操作直到排列有序，价值为每次操作的价值之和。

>给你 $n,m$，求所有 $n!$ 个排列的价值之和，对 $m$ 取模。$n\leq 10^7$

设 $p_1 = x$，操作序列形如 $x-1,x-2,\cdots, 1(,n,n-1,\cdots,1)$。

由于 $m$ 是合数，计算前 $x-1$ 次操作的贡献并不容易（否则可以用组合数暴力搞）。

所以我们把操作拆成 $x-1\sim x$ 和 $x-1\sim 1$ 两个阶段，再容斥减去没有进行 $(,n,n-1,\cdots,1)$ 的排列的贡献。

$x-1\sim 1$ 的贡献就是 $(x-1)(n-1)$。

对于 $x-1\sim x$ 的部分，相当于给出一个排列 $t_{1\sim n}(t_n = 1)$，依次将 $t$ 中的数按顺序挪到开头。

考虑 $(i,j)(i<j)$ 的贡献。如果 $i$ 在 $t$ 中排名靠后，贡献是 2，否则贡献是 1。

对于 $i,j>1$，在所有 $(n-1)!$ 种可能排列中，它们的平均贡献是 1.5。所以所有 $x-1\sim x$ 的贡献和是 $n!/2\times 3(n-1)(n-2)/2$。

最后需要减去没有进行 $(,n,n-1,\cdots,1)$ 的排列的贡献，每个都是 $n(n-1)$。

这样的排列数量等于 $\sum_{x=1}^n{n-1\choose x-1}(x-1)!$。令这个值是 $f_{n-1}$，则 $f_0 = 1$，$f_i = if_{i-1}+1$，递推即可。

```cpp
#include <bits/stdc++.h>

#define For(i, a, b) for (int i = a, i##end = b; i <= i##end; ++i)
#define rFor(i, b, a) for (int i = b, i##end = a; i >= i##end; --i)
#define eFor(i, u, v) for (int i = head[u], v = e[i].to; i; i = e[i].next, v = e[i].to)

typedef long long ll;

typedef std::pair<int, int> pii;
#define fi first
#define se second

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
template<typename T> 
T myrand(T l, T r) {
	return std::uniform_int_distribution<T>(l, r)(rnd);
}

template<typename T, typename ...Args> 
void LOG(T str, Args ...args) {
#ifndef NDEBUG
	fprintf(stderr, str, args...);
#endif
}

#define fre(s) freopen(#s ".in", "r", stdin), freopen(#s ".out", "w", stdout)

const int kN = 1e7 + 5;

int n, m, f[kN], fac[kN], fd2[kN];

int main() {
	scanf("%d%d", &n, &m);
	if (n == 1) {
		printf("0");
		return 0;
	}
	fac[0] = f[0] = fd2[0] = 1;
	For(i, 1, n) {
		f[i] = (1ll * i * f[i - 1] + 1) % m;
		fac[i] = 1ll * i * fac[i - 1] % m;
		if (i != 2) fd2[i] = 1ll * fd2[i - 1] * i % m;
		else fd2[i] = fd2[i - 1];
	}
	int ans = (ll(n - 1) * (n - 2) / 2 % m * 3 * fd2[n] + 2ll * fac[n] * (n - 1) + 1ll * n * (n - 1) / 2 % m * (n - 1) % m * fac[n - 1]) % m;
	ans = (ans + m - 1ll * f[n - 1] * n % m * (n - 1) % m) % m;
	printf("%d", ans);
	return 0;
}
/* PAY ATTENTION TO: */
/* 1. Memory Limit, Array Size */
/* 2. Integer Overflow */
/* 3. Multi-test */
/* 4. Potential Constant-speedup */
/* Stay organized and write things down. */

```

---

## 作者：__staring__ (赞：1)

分享模拟赛赛时做法，或许是比较不用推式子的题解（？。

记 $x=p_1$，即初始排列的首项，不难发现排序过程可以分成三部分：

- 第一部分结束时，$\forall i\in[1,x],p_i=i$，且 $\{p_i\mid i\in[x+1,n]\}=[x+1,n]$。

- 第二部分结束时，$\forall i\in[1,n-x],p_i=x+i$，且 $\forall i\in[n-x+1,n],p_i=i-(n-x)$。

- 第三部分结束时，$\forall i\in[1,n],p_i=i$。

于是对每个 $x\in[1,n]$，算出所有排列的三部分代价和，对于第一部分结束时已经排好序的排列，减去第二部分的额外代价即可。

发现所有排列第二部分结束后，位于 $[1,n]$ 顺次链接的环上。也就是说若排列 $p,q$ 有 $p_1\ne q_1$，那么存在置换使得 $q$ 的一二部分排序过程在置换后，和 $p$ 的过程完全一致。

所以一二部分可以看作等价操作，即直接对每个排列都操作 $n-1$ 次，只需要求出 $p_1$ 为某个特定 $x$ 的排列代价和，乘上 $n$ 即为所有排列代价和，那么不妨令 $p_1=n$。

假设当前已经把 $[t+1,n]$ 排在了序列开头，正在计算 $t$ 移动的代价。那么 $t$ 的位置有 $t$ 种，每种位置的原排列有 $\frac{(n-1)!}{t}$ 个。怎么理解呢，考虑当 $p_{n-t+k}=t$ 时，$p_1=n$，$p_{2,\dots,n-t}$ 可以任意排列，$p_{n-t+1,\dots,n}$ 也可以任意排列，但要求 $t$ 是其中的第 $k$ 项，于是有 $\binom{n-1}{t}(t-1)!(n-t-1)!$ 个原排列，化简得到 $\frac{(n-1)!}{t}$。

而对于 $t$ 种位置，移动到排列首项的代价依次为 $n-t,n-t+1,n-t+2,\dots,n-1$，求和为 $\frac{(2n-t-1)t}{2}$，那么，所有排列移动 $t$ 的代价和，为 $\frac{(2n-t-1)t(n-1)!}{2t}$。

现在来考虑额外代价，对不同的 $x=p_1$ 需要分开计算。如果排列 $p$ 在第一部分结束时已有序，说明值域上 $[x+1,n]$ 的部分在原排列有序，这样的排列有 $\binom{n-1}{n-x}x!=\frac{(n-1)!}{(n-x)!}$ 种，而每个排列在第二部分排序的额外代价，是 $[x+1,n]$ 的每个数移动了 $n-1$ 次到排列首项，因此第二部分 $p_1=x$ 的额外代价为 $\frac{(n-1)!(n-x)(n-1)}{(n-x)!}$。

对于第三部分的代价，$p_1=n$ 没有贡献，其余同样分开计算。由于 $p_1=x$ 的排列共有 $(n-1)!$ 个，去掉提前有序的序列，剩下的序列需要对 $x$ 个数，每个都移动 $n-1$ 次到排列首项，因此第三部分 $p_1=x$ 的代价为 $x(n-1)((n-1)!-\frac{(n-1)!}{(n-x)!})$。

于是最终答案为：

$$
(n\sum_{i=1}^{n-1} \frac{i(2n-i-1)}{2}\cdot\frac{(n-1)!}{i})
\\
-(\sum_{i=1}^n (n-i)(n-1)\cdot\frac{(n-1)!}{(n-i)!})
\\
+(\sum_{i=1}^{n-1} i(n-1)((n-1)!-\frac{(n-1)!}{(n-i)!}))
$$

可以自行化简。不难发现虽然模数不保证质数，但是第一部分的 $/2$ 可以直接除掉，$/i$ 可以通过处理 $(n-1)!$ 的前后缀积来规避，二三部分的 $/(n-i)!$ 也可以通过后缀积规避。

复杂度 $O(n)$。

~~如果模数保证质数我可能会写出非线性的代码。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace staring
{
    using LL = long long;
    using ULL = unsigned long long;
    #define fir first
    #define sec second

    #define FOR(i,a,b) for(int i = (a), i##E = (b); i <= i##E; i++)
    #define ROF(i,a,b) for(int i = (a), i##E = (b); i >= i##E; i--)

    template<typename TYPE>
    int gmax(TYPE &x, const TYPE& y){return x < y? x = y, 1 : 0;}
    template<typename TYPE>
    int gmin(TYPE &x, const TYPE& y){return y < x? x = y, 1 : 0;}

    static constexpr int SIZE = 1 << 20;
    static char buffin[SIZE]{}, *pin1{}, *pin2{};
    static char buffout[SIZE]{}, *pout{buffout};
    #define GETC() (pin1 == pin2 && (pin2 = (pin1 = buffin) + fread(buffin, 1, SIZE, stdin), pin1 == pin2)? EOF : *pin1++)
    #define PUTC(c) (pout - buffout == SIZE && (fwrite(buffout, 1, SIZE, stdout), pout = buffout), (*pout++ = c))
    template<typename TYPE>
    void read(TYPE &x)
    {
        static int signf{0}, chin{0};
        x = signf = 0, chin = GETC();
        while(chin < '0' || chin > '9') signf |= chin == '-', chin = GETC();
        while(chin >= '0' && chin <= '9') x = (x << 3) + (x << 1) + (chin ^ 48), chin = GETC();
        if(signf) x = -x;
    }
    template<typename TYPE>
    void write(TYPE x, char ch = ' ')
    {
        static int stack[64]{}, top{0};
        !x && PUTC('0'), x < 0 && (x = -x, PUTC('-'));
        while(x) stack[top++] = x % 10, x /= 10;
        while(top) PUTC(stack[--top] | 48);
        if(ch) PUTC(ch);
    }

}using namespace staring;

constexpr int N = 1e6 + 5;

int pre[N], suf[N];

void mainSolve()
{
    int n, MOD;
    read(n), read(MOD);

    pre[0] = 1, suf[n] = 1;
    FOR(i, 1, n) pre[i] = 1ll * pre[i - 1] * i % MOD;
    ROF(i, n - 1, 1) suf[i] = 1ll * suf[i + 1] * i % MOD;

    int sum = 0;
    ROF(j, n - 1, 1)
    {
        int val = (1ll * (n - j + n - 1) * j >> 1) % MOD;
        sum = (sum + 1ll * pre[j - 1] * suf[j + 1] % MOD * val) % MOD;
    }

    int res = 1ll * n * sum % MOD;
    FOR(i, 1, n)
    {
        res = (res + MOD - 1ll * suf[n - i + 1] * (n - i) % MOD * (n - 1) % MOD) % MOD;
        if(i < n) res = (res + 1ll * i * (n - 1) % MOD * (pre[n - 1] + MOD - suf[n - i + 1])) % MOD;
    }
    write(res);
}
    
int main()
{
    auto fileIO = [](string file)
    {
        string In = file + ".in";
        string Out = file + ".out";
        freopen(In.c_str(), "r", stdin);
        freopen(Out.c_str(), "w", stdout);
    };
    // fileIO("");

    int testCount = 1;
    // read(testCount);
    while(testCount--) mainSolve();

    fwrite(buffout,1,pout-buffout,stdout);
    return 0;
}
```

---

## 作者：Disjoint_cat (赞：1)

# [P9419 Układanie kart](https://www.luogu.com.cn/problem/P9419)

## 题意

对于一个长度为 $n$ 的排列 $a$，用以下方法计算其代价：

> 重复执行以下操作，直至 $a$ 递增：
>
> - 将序列中 $(a_1-2)\bmod n+1$ 这个数移到第一位，这会使某些数后移一位。设该数的位于 $a_t$，则其代价为 $t-1$。
>
> 这个排列的代价为所有操作的代价总和。

现在给定 $n$，则共有 $n!$ 个这样的排列 $a$。求所有这些排列的代价之和 $\bmod M$。

$2\le n\le10^6$。

## 题解

推式子题。

我们先考虑单次操作。

设 $f(x)$ 为：

> 假设我们要进行一次操作。钦定 $x$ 个数一定在要移动的数前面，则 $f(x)$ 为此时进行一次操作代价的期望值。

显然，这 $x$ 个数对期望的贡献为 $1$，剩下 $n-1-x$ 个数的期望贡献是 $\dfrac 12$。所以有：

$$\begin{aligned}f(x)&=x+\frac{n-1-x}2\\&=\frac{n+x-1}2\end{aligned}$$

这个 $f$ 函数对下文非常有用。

---

我们考虑排好序的过程：

一次操作，是将 $a_1-1$ 拉到 $a_1$ 左边。那么，假设初始时 $a_1=S$，则 $S-1$ 次操作后 $a_1$ 会变成 $1$。

此时如果已经排好序，直接结束。

否则，我们会依次把 $n,n-1,n-2,\ldots,2,1$ 拉到排列开头。可以看到，在 $S+n-1$ 此操作后，排列必然有序。

那我们枚举 $S$，然后把贡献拆成两部分计算：

- 前 $S-1$ 次操作的贡献（所有 $(n-1)!$ 个排列）；
- 后 $n$ 次操作的贡献（如果有）。

---

### 一、前 $S-1$ 次操作

注意：我们是在**同时考虑所有 $a_1=S$ 的排列**。

首先考虑将 $S-1$ 拉到第一位：$S$ 一定在其前面，而其他的不确定。期望贡献为 $f(1)$。

然后考虑 $S-2$：此时 $S$ 和 $S-1$ 一定在他前面，其他的不确定。期望贡献为 $f(2)$。

……

考虑 $1$：此时 $2,3,\ldots,S$ 都一定在 $1$ 前面。期望贡献为 $f(S-1)$。

所以，对于所有 $(n-1)!$ 个排列，前 $S-1$ 次操作的贡献和为：

$$\begin{aligned}&(n-1)!\sum_{i-1}^{S-1}f(i)\\=&(n-1)!\sum_{i=1}^{S-1}\frac{n+i-1}2\\=&(n-1)!\frac{(n-1)(S-1)+\frac{S(S-1)}2}2\\=&\frac{(n-1)!(2n+S-2)(S-1)}4\end{aligned}$$

### 二、后 $n$ 次操作

这要求在前 $S-1$ 次操作后排列**并非有序**。

我们可以**整体减空白**：先算出所有序列的贡献，再减去有序的情况。

分成两部分计算：

- 前 $n-S$ 次操作：

  此时设需把 $i$ 拉到开头，则有 $1\sim S$ 全部在该数前，$i+1\sim n$ 也在 $i$ 前，期望贡献为 $f(n-i+S)$。

- 后 $S$ 次操作：此时 $i$ 一定在最后，贡献为 $n-1$。

总贡献为：

$$\begin{aligned}&(n-1)!\left(\left(\sum_{i=S+1}^n\frac{n+(n-i+S)-1}2\right)+S(n-1)\right)\\=&(n-1)!\left(\frac{\sum_{i=S+1}^n(2n+S-1-i)}2+S(n-1)\right)\\=&(n-1)!\left(\frac{(2n+S-1)(n-S)-\frac{(n+S+1)(n-S)}2}2+S(n-1)\right)\\=&(n-1)!\left(\frac{(n-S)(4n+2S-2-n-1-S)}4+S(n-1)\right)\\=&(n-1)!\left(\frac{(n-S)(3n+S-3)}4+S(n-1)\right)\end{aligned}$$

最后，我们要减掉完全有序的情况。

如果做完 $S-1$ 次操作后有序，则 $S+1,S+2,\ldots,n$ 这 $n-S$ 个数必须在原序列中就有序。

这样的排列一共有 $\dfrac{(n-1)!}{(n-S)!}$ 个。

所以答案要减去 $\dfrac{(n-1)!}{(n-S)!}\times n(n-1)$。

然后就做完了。

---

时间复杂度 $\Theta(n)$。

一些注意事项：

- 模数不一定是质数，所以你没法使用逆元。注意代码实现。~~我写代码的时候这个地方贼烦人。~~

- 样例很弱（因为模数太整然后答案也变得很整），这里提供一组数据~~其实是我调不出来下载的~~：输入 `6 6997`，输出 `3226`。

## 代码实现

不放了。

---

