# Chino 的比赛

## 题目描述

Chino 想要用现在手里有的 $n$ 道题出成一套模拟赛。一开始，这 $n$ 道题按照由易到难的顺序排列。

但是因为 Chino 是一个可爱的妹子，所以她会将这些题目的顺序打乱。具体地，她会执行恰好奇数次操作，每次操作她会将其中两道题的位置交换。一套可能的模拟赛就是这些题的一个排列。

Chino 为了评估一套模拟赛的可爱程度，她定义 $s$ 表示使得开始时的题目顺序变为这套模拟赛的题目顺序的最少操作次数，定义 $t$ 表示开始时与这套模拟赛中位置相同的题目数量，那么这套模拟赛的可爱程度就是 $s/\left(t+1\right)$。

按照套路，你现在应该帮 Chino 计算某一套模拟赛的可爱程度。Chino 觉得这不够可爱，所以她想让你计算所有可能的模拟赛的可爱程度的两倍和。可以发现这一定是一个非负整数。为了避免答案过大，你只需要输出其对质数 $p$ 取模后的结果即可。

形式化地，对于置换 $\pi$，令 $\nu\left(\pi\right)$ 表示其不动点个数，设 $\upsilon\left(\pi\right)$ 为其能够被分解成为的最少个数对换乘积的对换数目。设 $n$ 元对称群为 $S_n$，$n$ 元交错群为 $A_n$，求
$$
2\sum_{\pi\in S_n\land\pi\notin A_n}\frac{\upsilon\left(\pi\right)}{\nu\left(\pi\right)+1}.
$$

这一定是一个非负整数。答案对质数 $p$ 取模后输出。

## 说明/提示

### 样例解释 #1
四道题的所有可能的模拟赛题目排列顺序有：
- $\left\{1,2,4,3\right\}$，可爱程度为 $1/3$；
- $\left\{1,3,2,4\right\}$，可爱程度为 $1/3$；
- $\left\{1,4,3,2\right\}$，可爱程度为 $1/3$；
- $\left\{2,1,3,4\right\}$，可爱程度为 $1/3$；
- $\left\{2,3,4,1\right\}$，可爱程度为 $3$；
- $\left\{2,4,1,3\right\}$，可爱程度为 $3$；
- $\left\{3,1,4,2\right\}$，可爱程度为 $3$；
- $\left\{3,2,1,4\right\}$，可爱程度为 $1/3$；
- $\left\{3,4,2,1\right\}$，可爱程度为 $3$；
- $\left\{4,1,2,3\right\}$，可爱程度为 $3$；
- $\left\{4,2,3,1\right\}$，可爱程度为 $1/3$；
- $\left\{4,3,1,2\right\}$，可爱程度为 $3$。

### 测试点约束
**本题采用捆绑测试。**

对于全部数据，有 $1\le n\le2\times10^7$，$2^{25}<p<2^{31}$，$p$ 为质数。
	
每个子任务的具体限制见下表：

| 子任务编号 | 分值 | $n\le$ | $p=998244353$ |
|:-:|:-:|:-:|:-:|
| 1 | 10 | $2\times10^1$ | $\times$ |
| 2 | 10 | $2\times10^2$ | $\surd$ |
| 3 | 10 | $2\times10^3$ | $\times$ |
| 4 | 20 | $2\times10^4$ | $\times$ |
| 5 | 20 | $2\times10^5$ | $\surd$ |
| 6 | 10 | $2\times10^6$ | $\surd$ |
| 7 | 20 | $2\times10^7$ | $\times$ |

### 更快的取模
本题中你可能会执行大量取模操作，因此你可以参考[几种取模优化方法（译自 min-25 的博客）](https://loj.ac/d/327)来提高取模运算的效率。

## 样例 #1

### 输入

```
4 16777259
```

### 输出

```
40
```

## 样例 #2

### 输入

```
10 2147483647
```

### 输出

```
17167120
```

## 样例 #3

### 输入

```
10000000 998244353
```

### 输出

```
3414058
```

# 题解

## 作者：NaCly_Fish (赞：5)

首先要知道一点：$\upsilon(\pi)$ 就是 $n$ 减去排列 $\pi$ 中环的数量。  
那么设有 $i$ 个环，其中 $j$ 个是自环（不动点）的排列数为 $f_{i,j}$，直接按题意可以写出答案是
$$S_n=2\sum_{i=0}^n[(n-i)\bmod 2=1]\sum_{j=0}^if_{i,j} \frac{n-i}{j+1}$$
对于 $f_{i,j}$，可以直接从 $n$ 个点中选出 $j$ 个作为不动点，剩下的 $n-j$ 个点都属于大小至少为 $2$ 的 $i-j$ 个环，即：
$$f_{i,j}=\binom nj (n-j)![x^{n-j}] \frac{(-\ln(1-x)-x)^{i-j}}{(i-j)!}$$
带回到原式中，推导一下：
$$\begin{aligned}S_n &=2\sum_{j=0}^n \binom nj \frac{(n-j)!}{j+1}[x^{n-j}]\sum_{i=j}^n[(n-i)\bmod 2=1] \frac{(-\ln(1-x)-x)^{i-j}}{(i-j)!}(n-i)  \\ &= 2[x^n]\sum_{j=0}^n \binom nj \frac{(n-j)!}{j+1} x^j\sum_{i=0}^{n-j}[(n-j-i)\bmod 2=1] \frac{(-\ln(1-x)-x)^i}{i!} (n-j-i)\end{aligned}$$
这里先暂停，内层和式中 $i$ 的上界是 $n-j$。但 $i>n-j$ 时单项 $x$ 的最低次已经大于 $n-j$，对答案不会有贡献，我们可以将上界取到无穷大，这样内层就是：
$$\frac 12\sum_{i=0}^\infty(1-(-1)^{n-j-i}) \frac{(-\ln(1-x)-x)^i}{i!}(n-j-i) $$

$$=\frac 12 \left( \frac{\text e^{-x}}{1-x}(n-j+\ln(1+x)+x)-(-1)^{n-j}\text e^x(1-x)(n-j-\ln(1-x)-x)\right)$$

带回去就是：

$$S_n=n![x^n]\sum_{j=0}^n \frac{x^j}{(j+1)!} \left( \frac{\text e^{-x}}{1-x}(n-j+\ln(1-x)+x)-(-1)^{n-j}\text e^x(1-x)(n-j-\ln(1-x)-x)\right)$$
虽然这样就可以 $\Theta(n)$ 计算了（整式递推出 $\text e^{-x}\ln(1-x)$ 与 $\text e^x \ln(1-x)$ 的系数即可），不过（为了装 B）我们可以考虑求出 $S_n$ 的 EGF。

那么还是可以把 $j$ 的上界取到无穷，再将上式整理一下，会得到许多形如 $n f(x)$ 或 $(-1)^n nf(x)$ 的部分，这样的单项会容易计算：
$$\sum_{n=0}^\infty z^n n[x^n]f(x)=\sum_{n=0}^\infty z^n [x^n](xf'(x))=zf'(z)$$
因此：
$$\begin{aligned}\sum_{n=0}^\infty \frac{z^n}{n!}S_n &=\sum_{j=0}^\infty \frac{z^j}{(j+1)!}\left(  \frac{\text e^{-z}}{1-z}(-j+\ln(1-z)+z)\right) \\ &-\sum_{j=0}^\infty \frac{z^j}{(j+1)!}\left( \text e^{-z}(1+z)(-j-\ln(1+z)+z)\right) \\ &+ z\left( \sum_{j=0}^\infty \frac{z^j}{(j+1)!} \frac{\text e^{-z}}{1-z}\right)'  \\ &- z \left(\sum_{j=0}^\infty \frac{z^j}{(j+1)!}\text e^{-z}(1+z)\right)'\end{aligned}$$
这个四个部分就都好办了，只有这里相对麻烦：
$$\sum_{j=0}^\infty \frac{z^j}{(j+1)!}j=\left( \sum_{j=0}^\infty \frac{z^j}{(j+1)!}\right)'z=\left(\frac{\text e^z-1}{z} \right)'z$$
最终我们可以得到（这与官方题解所给出的 EGF 是一致的）：
$$\sum_{n=0}^\infty \frac{z^n}{n!}S_n=\frac{1-\text e^{-z}}{z(1-z)^2}((2-z)z^2+(1-z)\ln(1-z)+(1-z)^2(1+z)\ln(1+z))$$
显然它是微分有限的，也就具有整式递推式。不过整体的递推式显而易见地会很长。通过把式子拆开计算，可以得到空间复杂度 $\Theta(1)$、时间复杂度 $\Theta(n)$；或空间复杂度 $\Theta(\sqrt n)$，时间复杂度 $\Theta(\sqrt n \log n)$ 的做法（不过也都非常麻烦就是了）。

出题人比较卡常，给个参考代码吧：
```cpp
#define uint unsigned int
#define ull unsigned long long

uint inv[N],f[N],g[N];
uint n,ans,p,fac;

inline uint add(uint x,uint y){ return x+y>=p?x+y-p:x+y; }
inline uint dec(uint x,uint y){ return x<y?x+p-y:x-y; }

inline uint power(uint a,uint t){
    uint res = 1;
    while(t){
        if(t&1) res = (ull)res*a%p;
        a = (ull)a*a%p;
        t >>= 1;
    }
    return res;
}

int main(){
    scanf("%u%u",&n,&p);
    inv[1] = 1;
    for(int i=2;i<=n+1;++i) inv[i] = (ull)(p-p/i)*inv[p%i]%p;
    f[0] = 1;
    for(int i=1;i<=n;++i) f[i] = p-(ull)f[i-1]*inv[i+1]%p;
    fac = (n&1)?f[n-1]:p-f[n-1];
    for(int i=1;i<=n;++i) f[i] = add(f[i],f[i-1]);
    for(int i=1;i<=n;++i) f[i] = add(f[i],f[i-1]);
    for(int i=1;i<=n;++i) g[i] = (i&1)?inv[i]:p-inv[i];
    for(int i=n;i>1;--i) g[i] = dec(dec(g[i],g[i-2]),inv[i]);
    g[1] = dec(g[1],1);
    for(int i=n;i>0;--i) g[i] = (g[i]+p-g[i-1])%p;
    g[2] = (g[2]+2)%p,g[3] = (g[3]-1+p)%p;
    for(int i=0;i<=n;++i) ans = (ans + (ull)f[i]*g[n-i])%p;
    ans = (ull)ans*power(fac,p-2)%p;
    printf("%u",ans);
    return 0;
}
```

---

## 作者：Daniel13265 (赞：3)

设答案为 $2f_n$。枚举 $\nu\left(\pi\right)$，对 $\upsilon\left(\pi\right)$ 使用二项式反演求和，可以得到
$$
\begin{aligned}
f_n&=\sum_{i=0}^{n}\frac{1}{i+1}\binom{n}{i}\sum_{j=0}^{n-i}\left(-1\right)^{j}\binom{n-i}{j}\sum_{\pi\in S_{n-i-j}\land\pi\notin A_{n-i-j}}\upsilon\left(\pi\right)\\
&=\sum_{i=0}^{n}\frac{\left(-1\right)^i}{i+1}\binom{n}{i}\sum_{\pi\in S_{n-i}\land\pi\notin A_{n-i}}\upsilon\left(\pi\right).
\end{aligned}
$$

现在我们只需要对于所有 $n$ 求出
$$
p_n=\sum_{\pi\in S_n\land\pi\notin A_n}\upsilon\left(\pi\right).
$$

于是我们假设
$$
a_n=\sum_{\pi\in A_n}\upsilon\left(\pi\right).
$$

显然有 $a_1=p_1=0$。对于 $n>1$，讨论 $\pi\left(n\right)$ 是否为 $n$ 可以得到
$$
\begin{gathered}
	a_n=a_{n-1}+\left(n-1\right)\left(\left\lfloor\frac{\left(n-1\right)!}{2}\right\rfloor+p_{n-1}\right).\\
	p_n=p_{n-1}+\left(n-1\right)\left(\left\lceil\frac{\left(n-1\right)!}{2}\right\rceil+a_{n-1}\right).
\end{gathered}
$$

直接递推即可。时空复杂度 $O\left(n\right)$。不知道有没有更高明的时间复杂度 $O\left(n\right)$ 且空间复杂度低于 $O\left(n\right)$ 的做法。

另外，继续使用生成函数推导可以得到：
$$
		f_n=n!\left[x^n\right]\frac{\left(1-e^{-x}\right)\left(\left(1-x\right)^2\left(1+x\right)\ln\left(1+x\right)+\left(1-x\right)\ln\left(1-x\right)+\left(2-x\right)x^2\right)}{2x\left(1-x\right)^2}.
$$

---

