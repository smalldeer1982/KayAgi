# Carry Bit

## 题目描述

Let $ f(x,y) $ be the number of carries of $ x+y $ in binary (i. e. $ f(x,y)=g(x)+g(y)-g(x+y) $ , where $ g(x) $ is the number of ones in the binary representation of $ x $ ).

Given two integers $ n $ and $ k $ , find the number of ordered pairs $ (a,b) $ such that $ 0 \leq a,b < 2^n $ , and $ f(a,b) $ equals $ k $ . Note that for $ a\ne b $ , $ (a,b) $ and $ (b,a) $ are considered as two different pairs.

As this number may be large, output it modulo $ 10^9+7 $ .

## 说明/提示

Here are some examples for understanding carries:

$$ \begin{aligned} &\begin{array}{r} 1_{\ \ }1_{\ \ }1\\ +\ _{1}1_{\ \ }0_{\ \ }0\\ \hline \ 1_{\ \ }0_{\ \ }1_{\ \ }1 \end{array} &\begin{array}{r} \ 1_{\ \ }0_{\ \ }1\\ +\ _{\ \ }0_{\ \ }0_{1}1\\ \hline \ 0_{\ \ }1_{\ \ }1_{\ \ }0 \end{array} & &\begin{array}{r} \ 1_{\ \ }0_{\ \ }1\\ +\ _{1}0_{1}1_{1}1\\ \hline \ 1_{\ \ }0_{\ \ }0_{\ \ }0 \end{array} \end{aligned}  $$ 

So  $ f(7,4)=1 $ ,  $ f(5,1)=1 $  and  $ f(5,3)=3 $ .

In the first test case, all the pairs meeting the constraints are  $ (1,1),(1,5),(2,2),(2,3),(3,2),(4,4),(4,5),(4,6),(4,7),(5,1),(5,4),(5,6),(6,4),(6,5),(7,4)$.

## 样例 #1

### 输入

```
3 1```

### 输出

```
15```

## 样例 #2

### 输入

```
3 0```

### 输出

```
27```

## 样例 #3

### 输入

```
998 244```

### 输出

```
573035660```

# 题解

## 作者：Alex_Wei (赞：14)

考虑钦定一些位置进位，设 $f(x)$ 表示第 $x$ 位是否被钦定进位。除去进位的影响，每一位的决策显然是独立的。

- 若 $f(x) = 1$ 且 $f(x - 1) = 1$，则 $a_x$ 和 $b_x$ 不能同时为 $0$，有 $3$ 种方案。
- 若 $f(x) = 1$ 且 $f(x - 1) = 0$，则 $a_x$ 和 $b_x$ 必须同时为 $1$，有 $1$ 种方案。
- 若 $f(x) = 0$ 且 $f(x - 1) = 1$，则 $a_x$ 和 $b_x$ 必须同时为 $0$，有 $1$ 种方案。
- 若 $f(x) = 0$ 且 $f(x - 1) = 0$，则 $a_x$ 和 $b_x$ 不能同时为 $1$，有 $3$ 种方案。

我们发现对于一个极长进位段 **连带着它前面一位**，对方案数的贡献为 $3 ^ {\mathrm{length} - 2}$。也就是说，本来方案数为 $3 ^ n$，但每个极长进位段会让方案数的指数减小 $2$，除了顶到最高位的进位段只会让方案数的指数减小 $1$。

考虑枚举进位段数 $i\in [1, k]$ 且最高位是否进位。首先有将 $k$ 个进位位分成 $i$ 段的方案数 $\dbinom {k - 1} {i - 1}$。

- 若进位，则剩余 $r = n - k + i + 1$ 个自由位，需要插到 $i$ 个空隙当中（最高位之前不能插），方案数为 $3 ^ {n - 2i + 1} \dbinom {r + i - 1} {i - 1}$。
- 若不进位，则剩余 $r = n - k + i$ 个自由位，需要插到 $i + 1$ 个空隙当中，方案数为 $3 ^ {n - 2i} \dbinom {r + i} i$。

时间复杂度 $\mathcal{O}(n)$，注意特判 $k = 0$ 的情况。[代码](https://codeforces.com/contest/1761/submission/183450884)。

---

## 作者：Autream (赞：10)

#### 题意简述

给定 $n,k$，求出在长度为 $n$ 的二进制数中（含前导 $0$），有多少对 $(a,b)$，满足 $a+b$ 在二进制加法下进位数为 $k$。

---

#### 题目分析

### Step 0

先来分析性质，观察在二进制下什么时候进位，什么时候不进位。

1. 进位：当且仅当前一位**进位**，且当前位**不为** $0 \ 0$ 或前一位**不进位**，且当前位**为** $1 \ 1$。

2. 不进位：当且仅当前一位**不进位**，且当前位**不为** $1 \ 1$ 或前一位**进位**，且当前位**为** $0 \ 0$。

于是我们就可以把这两个长度为 $n$ 的 $01$ 串分成 $k$ 个进位，$n-k$ 个不进位的小块，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/cqih8jf7.png)

其中红色的表示进位的小块，蓝色的表示不进位的小块。红色小块数量为 $k$，蓝色为 $n-k$。

由上面的性质可以得知，进位或不进位是可以传递的，即可以将若干个小块连接成几个大块。

我们对于如何分块进行分类讨论。

### Step 1

先求对进位的位组合的方案数。

考虑将 $k$ 块红色小块分成 $i$ 大块。

可以使用插板法的思想，此时蓝色大块就是板子，在 $k$ 个块中有 $k-1$ 个空隙，分成 $i$ 块就需要插 $i-1$ 块板子（如下图是一种 $k=5,i=2$ 的方案），所以分组方法有 $\begin{pmatrix} k-1 \\ i-1 \end{pmatrix}$ 种选择方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/ba4wthj1.png)

再考虑每一个块中，除了前一位不进位的情况（最后一位）只有一种选择外，其余位置都有 $0 \ 1, 1 \ 0, 1 \ 1$ 三种选择，故每一个大块的方案数为 $3^{len-1}$。

总方案数为：

$$
\begin{pmatrix}
k-1 \\
i-1
\end{pmatrix}
\times
3^{\sum \limits _{j=1} ^{i} len_j -1} =
\begin{pmatrix}
k-1 \\
i-1
\end{pmatrix}
\times
3^{k - i}
$$

**Tips：对于上述化简，因为我们是将 $k$ 个小块分组成 $i$ 个，所以这 $i$ 个大块长度的和为 $k$。**

### Step 2

再来考虑对不进位的位组合的方案数。

反过来，将红色大块当作板子，就相当于在 $n-k-1$ 个空隙中插 $i,i-1,i-2$ 块板（因为左右两端可能有空缺），根据红块左右两端是否有多余蓝块，可以分出 $i-1,i,i+1$ 三种情况。

对于分出 $i+1$ 块的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/cqih8jf7.png)

前 $i$ 个块中，除了最后一位只有一种选择外，其余位置都有 $0 \ 1, 1 \ 0, 0 \ 0$ 三种选择，故前 $i$ 个大块每块的方案数为 $3^{len-1}$。

对于最后一个大块，由于没有下一位的影响，其最后一位有也 $3$ 种选择，故最后一个大块的方案数为 $3^{len}$ 总方案数为：

$$
\begin{pmatrix} n-k-1 \\ i \end{pmatrix} \times (3^{\sum \limits _{j=1} ^i len_{i}-1} \times 3^{len_{i+1}}) = \begin{pmatrix} n-k-1 \\ i \end{pmatrix} \times 3^{n-k-i}
$$

对于分出 $i$ 块的情况：

- 第一个蓝块在最高位

![](https://cdn.luogu.com.cn/upload/image_hosting/1xxilq5a.png)

对于所有 $i$ 个蓝块，除了最后一位只有一种选择外，其余位置都有 $0 \ 1, 1 \ 0, 0 \ 0$ 三种选择，故每个块的方案数为 $3^{len-1}$。

总方案数为：

$$
\begin{pmatrix} n-k-1 \\ i-1 \end{pmatrix} \times 3^{\sum \limits _{j=1} ^{i} len_j-1} = \begin{pmatrix} n-k-1 \\ i-1 \end{pmatrix} \times 3^{n-k-i}
$$

-  最后一个蓝块在最低位

![](https://cdn.luogu.com.cn/upload/image_hosting/64uwecz8.png)

对于前 $i-1$ 个蓝块，除了最后一位只有一种选择外，其余位置都有 $0 \ 1, 1 \ 0, 0 \ 0$ 三种选择，故前 $i-1$ 个大块每块的方案数为 $3^{len-1}$。

对于最后一个大块，由于没有下一位的影响，其最后一位有也 $3$ 种选择，故最后一个大块的方案数为 $3^{len}$。

总方案数为：

$$
\begin{pmatrix} n-k-1 \\ i-1 \end{pmatrix} \times 3^{\sum \limits _{j=1} ^{i-1} len_{j -1}} \times 3^{len_i} = \begin{pmatrix} n-k-1 \\ i-1 \end{pmatrix} \times 3^{n-k-i+1}
$$

对于分出 $i-1$ 块的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/lsy1bza9.png)

对于所有 $i-1$ 个蓝块，除了最后一位只有一种选择外，其余位置都有 $0 \ 1, 1 \ 0, 0 \ 0$ 三种选择，故每个块的方案数为 $3^{len-1}$。

总方案数为：

$$
\begin{pmatrix} n-k-1 \\ i-2 \end{pmatrix} \times 3^{\sum \limits _{j=1} ^{i-1} len_j-1} = \begin{pmatrix} n-k-1 \\ i-2 \end{pmatrix} \times 3^{n-k-i+1}
$$

### Step 3

最终答案对于每个 $i$，将 Step 1 的答案与 Step 2 的四个答案的和乘起来求和。
即：

$$
\sum _{i=1} ^{k} \begin{pmatrix} k-1 \\ i-1 \end{pmatrix} \times 3^{k - i} \times \left ( \begin{pmatrix} n-k-1 \\ i \end{pmatrix} \times 3^{n-k-i}+\begin{pmatrix} n-k-1 \\ i-1 \end{pmatrix} \times 3^{n-k-i}+\begin{pmatrix} n-k-1 \\ i-1 \end{pmatrix} \times 3^{n-k-i+1}+\begin{pmatrix} n-k-1 \\ i-2 \end{pmatrix} \times 3^{n-k-i+1} \right )
$$

---

#### AC Code

```cpp
// Problem: Carry Bit
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1761D
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Author: Li_Feiy
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)a[i]=read()
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
int read() {
    char ch=getchar();
    int r=0,w=1;
    while(ch<'0'||ch>'9') w=ch=='-'?-1:w,ch=getchar();
    while(ch>='0'&&ch<='9') r=r*10+ch-'0',ch=getchar();
    return r*w;
}
CI N=1e6+5,MOD=1e9+7;
int n,k,ans,fac[N],inv[N];
int qpow(int a,int b) {
    if(b<0) return 0;
    int ans=1;
    while (b) {
        if (b&1) {
            ans=ans*a%MOD;
        }
        a=a*a%MOD;
        b>>=1;
    }
    return ans;
}
void pre() {
    fac[0]=inv[0]=1;
    rep(i,1,N-5) fac[i]=fac[i-1]*i%MOD;
    inv[N-5]=qpow(fac[N-5],MOD-2);
    dep(i,N-6,0) inv[i]=inv[i+1]*(i+1)%MOD;
}
int C(int n,int m) {
    return n<m?0:fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
signed main() {
    pre();
    n=read(),k=read();
    if(!k) {
        std::cout<<qpow(3,n);
        exit(0);
    }
    rep(i,1,k) {
        ans=(ans+(C(k-1,i-1)*qpow(3,k-i))%MOD
        *(
        (C(n-k-1,i)*qpow(3,n-k-i))%MOD
        +(C(n-k-1,i-1)*qpow(3,n-k-i))%MOD
        +(C(n-k-1,i-1)*qpow(3,n-k-i+1))%MOD
        +(C(n-k-1,i-2)*qpow(3,n-k-i+1))%MOD
        ))%MOD;
    }
    std::cout<<ans;
    return 0;
}
```

---

## 作者：MSqwq (赞：9)

感觉这题比同场的 E 难了好多，可能是我数学比较菜吧。  


------------
题意：  

给你 $n,k(0 \le k < n \le 10^6)$，问有多少对 $(a,b)$ 满足 $0 \le a,b < 2^n$ 且在二进制下的加法的时候，产生了 $k$ 次进位。  


------------
题解：  
我们设 $dp_{i,j,0/1}$ 为前 $i$ 位 进了 $j$ 位，$1$ 表示该位进了位，$0$ 表示该位没有进位。  
这样可以推出式子，但是复杂度为 $O(nk)$，显然不行，考虑优化。  
从这个 dp 我们可以发现，当且仅当当前位置的进位状态和前一位进位状态相同是，有 $3$ 种情况，反之则只有 $1$ 种情况。  
具体的：  
1. 如果当前位置和前一位都不进位，那么当前的 $a,b$ 的二进制位数对可以为 $(0,0)$，$(0,1)$， $(1,0)$。  
2. 如果当前位置和前一位都要进位，那么当前的 $a,b$ 的二进制位数对可以为 $(1,1)$，$(0,1)$， $(1,0)$。   
3. 如果前一位不进位，当前位进位，那么当前的 $a,b$ 的二进制位数对只能为 $(1,1)$。  
4. 如果前一位进位，当前位不进位，那么当前的 $a,b$ 的二进制位数对只能为 $(0,0)$。    

知道了这个之后我们将进位的状态列出来，设一个 $f$ 数组，如果 $f_i = 0$ 则说明第 $i$ 位没有进位，反之如果 $f_i = 1$ 则说明第 $i$ 位进位了。  
根据我们的结论 如果 $f_i = f_{i-1}$，那么就要乘个 $3$，其实问题就变成数连续段了。  
我们不妨设有 $n+1$ 位，另 $f_0 =0$，那么就天然的规定了，$f$ 的形式为若干个 $0$，然后接着若干个 $1$，这里的若干可以只为一个。  
我们设有 $x$ 个位置满足 $f_i \ne f_{i-1}$ ,那么就有 $x+1$ 个 $01$ 串，其中 $0$ 串有 $\lceil \frac{x + 1}{2} \rceil$ 个， $1$ 串有 $x+1-\lceil \frac{x + 1}{2} \rceil$ 个。  
回到本题，我们有 $k$ 个 $1$ 要填，那么相对应的，我们要填 $n+1-k$ 个 $0$。  
那么问题就变成把 x 个数，分为连续的 y 段的方案，就是 $\binom{x-1}{y-1}$。  
接下来就可以一口气写完全部啦  
$\sum\limits_{i = 0}^{n} 3^{n-i} \times \binom{(n+1-k)-1}{((i+1)-(i+1)/2)-1} \times \binom{k-1}{(i+1)/2-1}$  
题外话：  
好像有另外一种算的方法，过程就不写了，丢个结论在这里：  
$\sum\limits_{i = 1}^{n} 3^{k-i} \times 3^{n-k-i}\times \binom{k-1}{i-1	} \times \binom{n-k}{i} \ \ \ \ \ \  (n-k-i\ge0)$   
$\sum\limits_{i = 1}^{n} 3^{k-i} \times 3^{n-k-i+1}\times \binom{k-1}{i-1	} \times \binom{n-k}{i-1} \ \ \ \ \ \  (n-k-i+1\ge0)$   
第一个式子的代码：  
https://codeforces.com/contest/1761/submission/182127636  
第二个式子的代码：  
https://codeforces.com/contest/1761/submission/182087368

---

## 作者：Arghariza (赞：6)

#### Description

设 $f(x,y)$ 是 $x+y$ 的二进制进位数(即 $f(x,y)=g(x)+g(y)-g(x+y)$ ，其中 $g(x)$ 是 $x$ 的二进制表示中 $1$ 的个数)。

给定两个整数 $n$ 和 $k$ ，求出满足$0 \leq a,b < 2^n$ 且 $f(a,b) = k$ 的有序对 $(a,b)$ 的个数。注意，对于$a\neq b$，$(a,b)$ 和 $(b,a)$ 被认为是两个不同的对。

由于这个数可能很大，对它取模 $10^9+7$ 输出。


$0\le k<n\le  10^6$。

#### Solution

考虑什么时候两个数 $x+y$ 在 $i$ 处有进位：

- $x_i=y_i=1$，则必然有进位
- $x_i\ \text{xor}\ y_i=1$，并且之前一位有进位，也会有进位。

但是之前一位是否有进位你是不知道的，所以以上分类讨论还不能发挥什么作用。

那我们就连着上一位一同分类：

- 上一位没有进位，这一位也没有进位，那么 $x,y$ 所对应的位可以是 $(0,0),(0,1),(1,0)$。
- 上一位有进位，这一位没有进位：$x,y$ 只能对应 $(0,0)$。
- 上一位没有进位，这一位有进位：$x,y$ 只能对应 $(1,1)$。
- 上一位有进位，这一位也有进位：$x,y$ 能够对应 $(1,0),(0,1),(1,1)$。

我们发现当且仅当**上一位和这一位的进位状态相同时**，这种方案对答案的贡献才能增加。为了方便，不妨使用一个长度 $n+1$ 的 $01$ 序列 $t$ 记录 $0$ 到 $n$ 位的进位状态。显然有 $t_{n}=0$ 并且这一位其实是不需要的，但是为了方便我们可以加入这一位，这样的话我们知道当 $f_i\neq f_{i+1}$ 的个数一定时必然是 $0$ 的连续段更多。

于是我们设有 $i$ 个 $f_i\neq f_{i+1}$ 的地方，那么一共有 $i+1$ 个段，那么 $0$ 的连续段数为 $\left\lceil\dfrac{i+1}{2}\right\rceil$，$1$ 的连续段个数就是 $\left\lfloor\dfrac{i+1}{2}\right\rfloor$。

由于有 $k$ 次进位，所以有 $k$ 个 $1$；由于一共 $n+1$ 个位，所以 $0$ 就有 $n+1-k$ 个。

于是变成长度为 $n$ 的序列分成 $m$ 段的方案数，显然是 $\dbinom{n-1}{m-1}$。

由于有 $i$ 个 $f_i\neq f_{i+1}$，那么有 $n-i$ 个 $f_i=f_{i+1}$，那么有 $3^{n-i}$ 的贡献。

于是答案就是：

$$ans=\sum\limits_{i=0}^{n}3^{n-i}\dbinom{n-k}{\left\lceil\dfrac{i+1}{2}\right\rceil-1}\dbinom{k-1}{\left\lfloor\dfrac{i+1}{2}\right\rfloor-1}$$

直接 $O(n\log n)$ 做即可，预处理 $3$ 的幂优化至 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 1e6 + 100;
const int mod = 1e9 + 7;
int n, k, fac[maxn], ifac[maxn], inv[maxn];;

int qpow(int p, int q) {
	int res = 1;
	while (q) {
		if (q & 1) res = res * p % mod;
		p = p * p % mod, q >>= 1;
	}
	return res;
}

int C(int n, int m) { return n < m ? 0 : fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

signed main() { 
	n = read(), k = read();
	fac[0] = ifac[0] = inv[1] = 1;
	for (int i = 1; i <= n; i++) {
		if (i > 1) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
		fac[i] = fac[i - 1] * i % mod, ifac[i] = ifac[i - 1] * inv[i] % mod;
	}
	if (k == 0) return write(qpow(3, n)), 0;
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		(ans += qpow(3, n - i) * C(n - k, (i + 2) / 2 - 1) % mod * C(k - 1, i + 1 - ((i + 2) / 2) - 1) % mod) %= mod;
	}
	write(ans);
	return 0;
}
```

---

## 作者：myee (赞：5)

[本题加强版](https://loj.ac/p/6851)。

以下为加强版的题解。

### 思路

**组合意义天地灭，代数推导保平安**！

定义 $L(v)=\log_2\operatorname{lowbit}(v+1)$；也就是说，$L(v)$ 是 $v$ 在二进制下末位 $1$ 的个数。

例如，$L((1011)_2)=2,L((11100100111)_2)=3$。

然后定义

$$C(n,k,l)=\sum_{i=0}^{2^n-1}\sum_{j=0}^{2^n-1}[f(i,j)=k,L(i+j)=l]$$

则，答案可以被描述为

$$S(n,k)=\sum_{l=0}^nC(n,k,l)$$

考虑对其做递推。

通过对 $i,j$ 末位做分类讨论，容易得到

$$C(n,k,l)=\begin{cases}1&n=0\\2C(n-1,k,l-1)&l>0\\\sum_pC(n-1,k,p)+\sum_pC(n-1,k-p-1,p)&\text{otherwise.}\end{cases}$$

而这立刻给出

$$C(n,k,l)=\begin{cases}1&n=0\\2^lC(n-l,k,0)&l>0\\\sum_p2^pC(n-p-1,k,0)+\sum_p2^pC(n-p-1,k-p-1,0)&\text{otherwise.}\end{cases}$$

$$Ans_{n,k}=\sum_{l=0}^n2^lC(n-l,k,0)$$

也就是说，我们只用去研究 $C(n,k,0)$，就可以获得答案了！

于是对其，我们定义一个 BGF（二元生成函数）

$$F(z,u)=\sum_n\sum_kC(n,k,0)z^nu^k$$

然后就得到

$$F=1+F\times\sum_p\left(2^pz^{p+1}+2^pz^{p+1}u^{p+1}\right)$$

$$F=1+F\times(\frac z{1-2z}+\frac{zu}{1-2zu})$$

$$F=\frac1{1-(\frac z{1-2z}+\frac{zu}{1-2zu})}$$

$$F=\frac{(1-2z)(1-2zu)}{1-3z-3zu+8z^2u}$$

这样，我们的答案就是

$$S(n,k)=[z^nu^k]\frac F{1-2z}=[z^nu^k]\frac{1-2zu}{1-3z-3zu+8z^2u}$$

考虑如何计算 $S(n,k)$。

$$S(n,k)=[z^nu^k]\frac{1-2zu}{1-3z-3zu+8z^2u}=[z^nu^k]\frac1{1-3z-3zu+8z^2u}-2[z^{n-1}u^{k-1}]\frac1{1-3z-3zu+8z^2u}$$

这两部分是类似的，现在我们就考虑第一部分（为了减少手算量）。我们仅仅观察第一部分好了。

不妨称之为 $A_n$。

$$A_n=[z^nu^k]\frac1{1-3z-3zu+8z^2u}=[z^{n-k}]\frac{(3-8z)^k}{(1-3z)^{k+1}}$$

考虑使用 ODE 来计算所有 $A_n$。

设

$$G(z)=\frac{(3-8z)^k}{(1-3z)^{k+1}}$$

$$G_t=[z^t]G$$

则

$$G'=\frac{-8k(3-8z)^{k-1}(1-3z)+3(k+1)(3-8z)^k}{(1-3z)^{k+2}}$$

于是

$$(1-3z)(3-8z)G'=\frac{-8k(3-8z)^k(1-3z)+3(k+1)(3-8z)^{k+1}}{(1-3z)^{k+1}}=(-8k(1-3z)+3(k+1)(3-8z))G$$

即

$$(3-17z+24z^2)G'=(k+9-24z)G$$

$$3(t+1)G_{t+1}-17tG_t+24(t-1)G_{t-1}=(k+9)G_t-24G_{t-1}$$

从而

$$G_{t+1}=\frac{(9+17t+k)G_t-24tG_{t-1}}{3(t+1)}$$

考虑边界，也就是

$$G_0=3^k,G_1=3^{k-1}(9+k)$$

于是我们就可以在 $O(n)$ 时间内计算出数列 $G$ 了。

合并两次计算的贡献即可求出一列的答案。


---

## 作者：Polaris_Australis_ (赞：3)

拆位考虑，$a$ 和 $b$ 的二进制每一位看成一个二元组，考虑一个长度为 $s$ 的满足 $(0,0),...,(1,1)$ 的连续段，其中中间部分的二元组里至少有一个元素为 $1$，则这一段对答案的贡献是 $s-1$，所以直接枚举连续段个数求方案数。设连续段个数为 $i$，则相当于要从一个长度为 $n$ 的序列中取出 $i$ 段，长度和为 $k+i$，且每段长度 $\ge2$，这是一个经典套路，直接组合数即可。具体方法：先从序列中刨除 $k$ 个位置，从剩余的 $n-k$ 个位置中选出 $i$ 个位置作为每一段的末尾，即 $\binom{n-k}{i}$，再把之前刨出的 $k$ 个位置分成 $i$ 份就可以了，即 $\binom{k-1}{i-1}$。还有一个坑点：第一段的开头可以是 $n+1$，单独算一下就行了。

代码：

```
// Problem: D. Carry Bit
// Contest: Codeforces - Pinely Round 1 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1761/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define gdb
#ifdef gdb
#define dbg cerr<<"Wilson_Inversion\n"
#define debug(x) cerr<<"["<<#x<<"="<<x<<"]\n"
#define DEBUG(x,__n){                                          \
	cerr<<"["<<#x<<":\n";                                      \
	for(int __i=0;__i<__n;++__i)cerr<<__i<<":"<<x[__i]<<",\n"; \
	cerr<<__n<<":"<<x[__n]<<"]\n"                              \
}
#else
#define dbg 0
#define debug(x) 0
#define DEBUG(x,__n) 0
#endif
#define pb push_back
#define mk make_pair
#define ff first
#define ss second
#define int long long
#define db double
#define miny(x,y) x=min(x,y)
#define maxy(x,y) x=max(x,y)
#define lowbit(x) ((x)&(-(x)))
#define fu(i,l,r) for(int i=(l);i<=(r);++i)
#define fd(i,r,l) for(int i=(r);i>=(l);--i)
#define mem(x,y) memset(x,y,sizeof(x))
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
#define mod 1000000007
#ifdef int
#define inf 0x3f3f3f3f3f3f3f3f
#else
#define inf 0x3f3f3f3f
#endif
#define inv(x) qp(x,mod-2)
using namespace std;
namespace Std{
	void read(int &x){
		x=0;
		int y=1;
		char c=getchar();
		while(c<'0'||c>'9'){
			if(c=='-')y=-1;
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<1)+(x<<3)+(c&15);
			c=getchar();
		}
		x*=y;
	}
	void write(int x){
		char s[50];
		int tot=0;
		while(x){
			s[++tot]=(x%10);
			x/=10;
		}
		while(tot)putchar(s[tot--]);
	}
	int qp(int x,int y){
		int cmp=1;
		while(y){
			if(y&1)(cmp*=x)%=mod;
			(x*=x)%=mod;
			y>>=1;
		}
		return cmp;
	}
	int n,k,fac[2000010],ifac[2000010];
	int C(int x,int y){
		if(y>x||y<0||x<0)return 0;
		return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
	}
	void main(){
		read(n);
		read(k);
		fac[0]=1;
		for(int i(1);i<=2000000;++i)fac[i]=fac[i-1]*i%mod;
		ifac[2000000]=inv(fac[2000000]);
		for(int i(1999999);~i;--i)ifac[i]=ifac[i+1]*(i+1)%mod;
		if(!k){
			printf("%lld\n",qp(3,n));
			return;
		}
		int ans=0;
		for(int i=1;i<=k;++i){
			if(n-i*2>=0)ans+=qp(3,n-i*2)*C(n-k,i)%mod*C(k-1,i-1)%mod;
			if(n-i*2+1>=0)ans+=qp(3,n-i*2+1)*C(n-k,i-1)%mod*C(k-1,i-1)%mod;
		}
		printf("%lld\n",ans%mod);
	}
}  // namespace Std
#undef int
int main(){
	Std::main();
	return 0;
}
```


---

## 作者：linyihdfj (赞：3)

## CF1761D Carry Bit
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
不要管题目里给的那个式子，就是迷惑人的。

我们发现进位都是连续的一段一段的，所以其实可以分段考虑。

考虑一段进位意味着什么（我们上面一行代表 $a$ 的二进制，下面一行代表 $b$ 的二进制），只有可能是这种情况：
$$
\begin{aligned}
0 \cdots 1 \\
0 \cdots 1
\end{aligned}
$$
其实也就是最左端为 $(0,0)$ 最右端为 $(1,1)$，中间因为必须一直连续地进位下去所以必须至少含有一个 $1$ 也就是以下三种情况之一：
$$
\begin{aligned}
0 \ 1 \ 1 \\
1 \ 0 \ 1 
\end{aligned}
$$
而对于不参与进位的位置来说，为了不进位，显然只可以是以下三种情况之一：
$$
\begin{aligned}
0 \ 0 \ 1 \\
0 \ 1 \ 0
\end{aligned}
$$
然后就可以考虑枚举分了多少段，假设分了 $p$ 段，也就是说我们要将 $k$ 个进位分配到 $p$ 段里每段大于等于 $1$，经典问题。

然后将剩余的 $n - k - p$ 个不进位的位置分配到 $p$ 段分割成的 $p + 1$ 个段内。$n - k - p$ 是因为我们进位不算最前面的 $(0,0)$ 但是它也可以理解为和我们的某一段是捆绑在一起的，因为这个就是为了预防影响外界的。

然后将上面分析的三种情况乘一下，就是乘以 $3^{k - p} \times 3^{n - k - p}$

总结一下，设 $calc(i,j)$ 表示将 $i$ 个球放到 $j$ 个盒子里，每个盒子里至少有一个的方案数，那么答案就是这个值：
$$
3^{n - k - p} \times 3^{k - p} \times calc(k,p) \times calc(n - k - p + (p + 1),p+1) 
$$

别急啊，这样会发现不对，少算了一些情况，少算的其实是类似这样的情况：
$$
\begin{aligned}
1 \ 0 \ 0\\
1 \ 1 \ 0
\end{aligned}
$$
我们会发现开头的这一段的左端点不是 $(0,0)$，因为这种情况下对于最高位而言比他还高就不可以选所以必然是 $(0,0)$ 只不过不会体现出现罢了，但是这种情况会发现也是很好算的。

只需要限制第一段之前没有任何位置不进位然后多了一个不进位的位置而已，类比一下答案就是这个：
$$
3^{n - k - p + 1} \times 3^{k - p} \times calc(k,p) \times calc(n - k - p + 1 + p,p) 
$$
两种情况显然不会重复，因为第一种相当于默认第一段最左边是 $(0,0)$，所以直接加起来就是答案。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e6+5;
const int MOD = 1e9+7;
int fac[N],inv[N],pw[N];
int mod(int x){
	return (x % MOD + MOD)%MOD;
}
int power(int a,int b){
	int res = 1;
	while(b){
		if(b & 1)	res = mod(res * a);
		a = mod(a * a);
		b >>= 1;
	}
	return res;
}
int C(int n,int m){
	if(n < m)	return 0;
	return mod(fac[n] * mod(inv[m] * inv[n - m]));
}
int calc(int x,int y){
	return C(x-1,y-1);
}
signed main(){
	int n,k;
	scanf("%lld%lld",&n,&k);
	pw[0] = 1;
	for(int i=1; i<=n+k; i++)	pw[i] = mod(pw[i-1] * 3);
	fac[0] = 1;
	for(int i=1; i<=n+k; i++)	fac[i] = mod(fac[i-1] * i);
	inv[n+k] = power(fac[n+k],MOD-2);
	if(k == 0){
		printf("%lld\n",pw[n]);
		return 0;
	}
	for(int i = n + k - 1; i>=0; i--)	inv[i] = mod(inv[i+1] * (i + 1));
	int ans = 0;
	for(int p=1; p<=k; p++){   //枚举划分成多少段
		if(n - k - p >= 0){
			int tmp = mod(pw[n - k - p] * pw[k - p]);   //这里相当于做的是不考虑他在最前面不要 (0,0) 的情况 
			int tmp2 = calc(k,p);	//把 k 个小球划分到 p 个盒子里
			int tmp3 = calc(n - k - p + p + 1,p + 1);  
			//把 n - k - p 个剩余的空位置，划分到 p + 1 个盒子里，每个盒子大于等于 0 
			ans = mod(ans + mod(mod(tmp * tmp2) * tmp3)); 
		}
		if(n - k - p + 1 >= 0){
		//如果考虑不要 (0,0) 的话
			int tmp = mod(pw[n - k - p + 1] * pw[k - p]);
			int tmp2 = calc(k,p);
			int tmp3 = calc(n - k - p + 1 + p,p);
			ans = mod(ans + mod(mod(tmp * tmp2) * tmp3)); 
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Zi_Gao (赞：2)

首先很显然有一个 $\mathcal{O}\left(nk\right)$ 的朴素 DP 做法，具体地设 $dp_{i,j,0/1}$ 表示当前考虑了前 $i$ 位，进位了 $j$ 次，并且 $i$ 位上是否向 $i+1$ 进位的方案数。考虑刷表计算，从 $dp_{i,j,0/1}$ 向下推，分类讨论一下第 $i+1$ 位两个数的情况可以得到：

1. $dp_{i,j,0}$ 下一位分别选 $\{0,0\},\{0,1\},\{1,0\}$ 三种情况都可以转移到 $dp_{i+1,j,0}$。

2. $dp_{i,j,0}$ 下一位分别选 $\{1,1\}$ 一种情况都可以转移到 $dp_{i+1,j+1,1}$。

3. $dp_{i,j,1}$ 下一位分别选 $\{0,1\},\{1,0\},\{1,1\}$ 三种情况都可以转移到 $dp_{i+1,j+1,1}$。

4. $dp_{i,j,1}$ 下一位分别选 $\{0,0\}$ 一种情况都可以转移到 $dp_{i+1,j,0}$。

最终答案是 $dp_{n,k,0}$ 或者 $dp_{n,k-1,1}$。发现可以重新给这个 DP 式子一个组合意义：有一个变量 $x=0$，每次有三种操作将 $x$ 异或上 $1$，一种操作异或上 $0$，然后任意操作 $n$，让每个时刻的 $x$ 的状态构成一个长度为 $n+1$ 的 $01$ 序列，答案就是有多少中操作方案使得最终序列里面有 $k$ 个 $1$。枚举 x 变化的总次数 $i$，那么 $01$ 串中有 $\lceil\frac{i}{2}\rceil$ 个 $0$ 的连续段，$\lfloor\frac{i}{2}\rfloor$ 个 $1$ 的连续段，$0$ 连续段的总长必须为 $n+1−k$，$1$ 连续段的总长必须为 $k$，用插板法计算方案数。

```cpp
MODINT::MODNUM pw3[2000010];

#define PC_DATA_TYPE long long

const PC_DATA_TYPE PC_MOD=1000000007;
const PC_DATA_TYPE PC_DATA_SIZE=2000010;

PC_DATA_TYPE inv[PC_DATA_SIZE],fact[PC_DATA_SIZE],invfact[PC_DATA_SIZE];

void init_pc(int n){
    register int i;
    for(inv[0]=0,inv[1]=fact[0]=fact[1]=invfact[0]=invfact[1]=1,i=2;i<=n;++i)
        invfact[i]=invfact[i-1]*(inv[i]=PC_MOD-PC_MOD/i*inv[PC_MOD%i]%PC_MOD)%PC_MOD,fact[i]=fact[i-1]*i%PC_MOD;
    return;
}

PC_DATA_TYPE A(int n,int m){
    if(n<0||m<0||n<m) return 0;
    return fact[n]*invfact[n-m]%PC_MOD;
}
PC_DATA_TYPE C(int n,int m){
    if(n<0||m<0||n<m) return 0;
    return fact[n]*invfact[n-m]%PC_MOD*invfact[m]%PC_MOD;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    MODINT::init(1000000007);

    register int i;
    register MODINT::MODNUM res=0;
    int n=read();
    int k=read();

    init_pc(n*2);
    for(i=pw3[0]=1;i<=n*2;++i) pw3[i]=pw3[i-1]*3;

    if(k==0) return print(pw3[n]),0;

    for(i=1;i<=k;++i){
        if(n-i*2>=0) res+=pw3[n-i*2]*C(n-k,i)*C(k-1,i-1);
        if(n-i*2+1>=0) res+=pw3[n-i*2+1]*C(n-k,i-1)*C(k-1,i-1);
    }

    print(res);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

## 作者：Imiya (赞：1)

刚看到这个问题没啥头绪，感觉进位次数比较难刻画，他给的转化感觉也没啥用，dp 的话只会一个状态 $O(nk)$ 的方法，看起来比较难以优化。

假如我们暴枚具体在哪几位产生了进位，看看会不会在计算方案的过程中发现一些优良的性质。

| $2^3$ | $2^2$ | $2^1$ | $2^0$ |
|-:|-:|-:|-:|
| 不进 | 进 | 进 | 不进 |
| $(0,0)$ | $(0,1)\\(1,0)\\(1,1)$ | $(1,1)$ | $(0,0)\\(0,1)\\(1,0)$ |

随便手模一个例子，发现只有两种情况会产生 $\times 3$ 的贡献：上一位没有进位且这一位也没进位，上一位进位且这一位也进位。

等价转化一下，若钦定的进位情况序列中有 $p$ 个连续进位段，$q$ 个连续不进位段，则这个序列对应 $3^{k-p}\cdot3^{n-k+1-q}=3^{n+1-p-q}$ 种方案（首位一定不会受到进位，相当于在首位前补一个不进位）。

考虑有多少将 $k$ 个进位与 $n-k+1$ 个不进位各自划分成 $p$ 段和 $q$ 段的方案数。

先看进位段：  
$k$ 个进位划分成 $p$ 段，插板法，有 $C_{k-1}^{p-1}$ 种方案。

考虑不进位段：首先发现 $p$ 与 $q$ 有关系，若最高位进位，则 $p=q$，否则 $p+1=q$。  
若 $p=q$，有 $C_{n-k}^{p-1}$ 种方案。  
否则，有 $C_{n-k}^{p}$ 种方案。

枚举 $p$。

$$ans=\sum3^{n+1-2p}C_{k-1}^{p-1}C_{n-k}^{p-1}+3^{n-2p}C_{k-1}^{p-1}C_{n-k}^{p}$$

---

## 作者：baka24 (赞：0)

考虑什么样的位置会进位。

两种情况，前一位无进位时此位为 $(1,1)$ 或者上一位有进位且这一位不为 $(0,0)$。

考虑什么样的位置不会进位。

两种情况，前一位无进位时此位不为 $(1,1)$ 或者上一位有进位且这一位为 $(0,0)$。

你发现我们可以将需要进位的位置划分成若干个块，设块长为 $m$ 那么这个块的方案数即 $3^{m-1}$。

考虑枚举划分成多少个块。

当进位的位被划分成 $i$ 个块时，进位的部分的方案数为 $C_{k-1}^{i-1}\times 3^{k-i}$，即划分方案数乘内部可能性。

不进位的部分分别可以划分成 $i+1,i,i-1$ 个块。

即
![pkUGTLd.png](https://s21.ax1x.com/2024/06/11/pkUGTLd.png)
![pkUGOFP.png](https://s21.ax1x.com/2024/06/11/pkUGOFP.png)
或
![pkUGzQg.png](https://s21.ax1x.com/2024/06/11/pkUGzQg.png)
![pkUJPwn.png](https://s21.ax1x.com/2024/06/11/pkUJPwn.png)

四种情况，分别进行考虑。

分成 $i+1$ 个块时，前 $i$ 个块的最后一位固定是 $(0,0)$，所以总答案为 $C_{n-k-1}^{i}\times 3^{n-k+i}$。

分成 $i$ 个块时，有两种情况，其中一种最后一个块不受限制，另一种所有块都受限制，所以答案为 $C_{n-k-1}^{i-1}\times 3^{n-k+i}\times 4$。

分成 $i-1$ 个块时，所有块的最后一位固定是 $(0,0)$，所以总答案为 $C_{n-k-1}^{i-2}\times 3^{n-k+i+1}$。

加和后乘上进位部分的方案数即可。

注意 $k=0$ 需要特判。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){int x=0,f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}x=c-'0';c=getchar();while(c<='9'&&c>='0'){x*=10;x+=c-'0';c=getchar();}return x*f;}
const int MAXN=1000010,Mod=1000000007;
int n,k,m,ans,a[MAXN],b[MAXN],jc[MAXN],ny[MAXN];
int Pow(int x,int y){if(y<0)return 0;int rt=1;while(y){if(y&1)rt=rt*x%Mod;x=x*x%Mod,y>>=1;}return rt;}//快速幂
int C(int x,int y){//组合数
    return x<y?0:jc[x]*ny[x-y]%Mod*ny[y]%Mod;
}
void slv(){
    n=read(),k=read();
    jc[0]=ny[0]=1;
    for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%Mod,ny[i]=Pow(jc[i],Mod-2);
    if(!k)ans=Pow(3,n);
    for(int i=1;i<=k;i++){
        ans+=C(k-1,i-1)*Pow(3,k-i)%Mod//进位部分
        *(
            C(n-k-1,i)*Pow(3,n-k-i)%Mod//i+1
            +(C(n-k-1,i-1)*Pow(3,n-k-i)%Mod*4)%Mod//i
            +C(n-k-1,i-2)*Pow(3,n-k-i+1)%Mod//i-1
        )%Mod;

        ans%=Mod;
    }
    printf("%lld",ans);
}
signed main(){
	slv();
    return 0;
} 	
```

---

## 作者：WilliamFranklin (赞：0)

### 主要思路

首先可以先考虑设一个 DP，$f_{i,j,0/1}$ 表示已经填了 $a$ 和 $b$ 二进制下的最低 $i$ 位，共 $j$ 次进位，第 $i$ 位是否有进向第 $i + 1$ 位的进位。

那么转移的情况，就是有 $f_{i, j, 0}$ 有 $3$ 种情况转移到 $f_{i + 1, j, 0}$，有 $1$ 种情况转移到 $f_{i + 1, j + 1, 1}$，同样，$f_{i, j, 1}$ 有 $3$ 种情况转移到 $f_{i + 1, j + 1, 1}$，有 $1$ 种情况转移到 $f_{i + 1, j, 0}$。

那么就可以看成：一开始有一个变量 $x = 0$，并且 $x$ 的值只能是 $0$ 或 $1$，然后进行 $n$ 次操作，每一次操作都有 $3$ 种方案使得 $x$ 不变，有 $1$ 种方案使得 $x$ 改变。那么将 $x$ 在每一时刻的情况记录下来，就可以得到一个长度为 $n$ 的序列，仅有 $0$ 和 $1$ 组成，那么 $1$ 的个数，就是题目中进位的次数。

那么考虑枚举 $x$ 的变换次数 $i$，那么就有 $i + 1$ 个块，并且全为 $0$ 的块有 $\lceil\frac{i + 1}{2}\rceil$ 个，全为 $1$ 的块有 $\lfloor\frac{i + 1}{2}\rfloor$ 个，并且 $0$ 的个数必须是 $n - k + 1$，$1$ 的个数必须是 $k$，所以可以考虑用插板法解决这个问题，那么就可以得到答案：

$$ans = \sum_{i = 0}^n{3^{n - i}\binom{n - k}{\lceil\frac{i + 1}{2}\rceil - 1}\binom{k - 1}{\lfloor\frac{i + 1}{2}\rfloor - 1}}$$

好，看下代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 1e6 + 5, mod = 1e9 + 7;
int n, k;
long long fac[N];
long long ifac[N];
long long fac3[N];
long long quickpow(long long a, long long b, long long mod) {
	long long res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1; 
	}
	return res;
}
long long C(long long a, long long b) {
	if (a < b) return 0;
	return fac[a] * ifac[b] % mod * ifac[a - b] % mod;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> k;
	if (k == 0) {
		cout << quickpow(3, n, mod);
		return 0;
	} 
	fac[0] = 1;
	For(i, 1, n) fac[i] = fac[i - 1] * i % mod;
	For(i, 0, n) ifac[i] = quickpow(fac[i], mod - 2, mod);
	fac3[0] = 1;
	For(i, 1, n) fac3[i] = fac3[i - 1] * 3 % mod;
	long long ans = 0;
	For(i, 0, n) {
		ans = (ans + fac3[n - i] * C(n - k, ceil((i + 1) / 2.0) - 1) % mod * C(k - 1, (i + 1) / 2 - 1) % mod) % mod;
		//cout << ans << '\n';
	}
	cout << ans;
	return 0;
} 
```

### 谢谢观看

---

