# [ABC367G] Sum of (XOR^K or 0)

## 题目描述

给定正整数 $N, M, K$ 以及非负整数序列 $A=(A_1, A_2, \ldots, A_N)$。

对于任意非空的非负整数序列 $B=(B_1, B_2, \ldots, B_{|B|})$，定义其**得分**如下：

- 当 $B$ 的长度是 $M$ 的倍数时，得分为 $(B_1 \oplus B_2 \oplus \dots \oplus B_{|B|})^K$；
- 否则得分为 $0$。

其中，$\oplus$ 表示按位异或运算。

请计算 $A$ 的所有非空子序列（共 $2^N-1$ 个）各自的得分之和，并对 $998244353$ 取模后输出。

按位异或的定义如下：对于非负整数 $A, B$，$A \oplus B$ 的二进制表示中，第 $2^k$ 位（$k \geq 0$）的数等于 $A, B$ 的二进制表示中第 $2^k$ 位的数中恰有一个为 $1$ 时为 $1$，否则为 $0$。

例如，$3 \oplus 5 = 6$（二进制表示为：$011 \oplus 101 = 110$）。
一般地，$k$ 个整数 $p_1, \dots, p_k$ 的异或为 $(\cdots((p_1 \oplus p_2) \oplus p_3) \oplus \cdots \oplus p_k)$，并且可以证明其结果与顺序无关。

## 说明/提示

### 限制条件

- $1 \leq N, K \leq 2 \times 10^5$
- $1 \leq M \leq 100$
- $0 \leq A_i < 2^{20}$
- 所有输入均为整数

### 样例解释 1

$A$ 的所有非空子序列（共 $2^3-1=7$ 个）各自的得分如下：

- $(1)$：$0$
- $(2)$：$0$
- $(3)$：$0$
- $(1,2)$：$(1\oplus2)^2=9$
- $(1,3)$：$(1\oplus3)^2=4$
- $(2,3)$：$(2\oplus3)^2=1$
- $(1,2,3)$：$0$

因此，总和为 $0+0+0+9+4+1+0=14$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2 2
1 2 3```

### 输出

```
14```

## 样例 #2

### 输入

```
10 5 3
100 100 100 100 100 100 100 100 100 100```

### 输出

```
252000000```

## 样例 #3

### 输入

```
16 4 100
7053 3876 3178 8422 7802 5998 2334 6757 6889 6637 7365 9495 7848 9026 7312 6558```

### 输出

```
432440016```

# 题解

## 作者：小粉兔 (赞：17)

在博客园食用更佳：<https://www.cnblogs.com/PinkRabbit/p/-/ABC367>。

## 题意简述（\*3110）

给定长度为 $n$ 的值域在 $[0, 2^b)$ 内的非负整数序列 $(a_1, \ldots, a_n)$ 和正整数 $m, k$。求

$$
\left( \sum_{\substack{S \subseteq \{ 1, \ldots, n \} \\ \lvert S \rvert \equiv 0 \pmod{m}}} [S \ne \varnothing] \Biggl( \bigoplus_{i \in S} a_i \Biggr)^k \right) \bmod 998244353 \text{。}
$$

数据范围：$n \le 2 \times 10^5$，$a_i < 2^b$，$b \le 20$，$m \le 100$，$1 \le k \le 2 \times 10^5$。

## 题解

由于 $b \le 20$，考虑 $\tilde{\mathcal O}(2^b)$ 的做法是自然的。

如果可以对于每个值 $v \in [0, 2^b)$ 求出有多少个满足限制的 $S$ 使得 $\displaystyle \bigoplus_{i \in S} a_i$ 就等于 $v$，不妨记这样的 $S$ 的数量为 $f_v$，则答案为 $\displaystyle \Biggl( \sum_{v = 0}^{2^b - 1} (f_v - [v = 0]) \cdot v^k \Biggr) \bmod 998244353$。  
（减去 $[v = 0]$ 是因为要扣除 $S$ 为空集的情况，其恰好对应 $v = 0$。不过本题保证 $k \ge 1$，因此 $v = 0$ 时 $v^k = 0$，所以不管也行。）

只需求出所有 $f_v \bmod 998244353$ 即可。本题没有需要讨论数论性质的部分（除了要除以 $2^b$），故后文中省略对模 $998244353$ 的讨论。

有 $\displaystyle f_v = [x^v y^0] \prod_{i = 1}^{n} (1 + x^{a_i} y)$，其中元 $x$ 进行**异或卷积**，元 $y$ 进行**长度为 $\bm m$ 的循环卷积**。

可以对 $x$ 的维度进行 Walsh 变换将异或卷积转换为点积，但由于缺乏 $m$ 次单位根 $\omega_m$，保留 $y$ 的维度进行普通的循环卷积。这里我们的底气是 $m \le 100$ 范围不大。

我们知道 $1$（即 $x^0$，仅有 $0$ 处的值非零且为 $1$ 的序列）的 Walsh 变换为全 $1$ 序列。设 $x^a$（即仅有 $a$ 处的值非零且为 $1$ 的序列）的 Walsh 变换为序列 $({h^a}_w)$，这里每个 ${h^a}_w$ 均为 $1$ 或 $-1$。根据 Walsh 变换的线性性，一个因子 $(1 + x^a y)$ 的 Walsh 变换就为序列 $({g^a}_w)$，其中 ${g^a}_w = 1 + {h^a}_w y$。

于是将每个因子的序列 $({g^a}_w)$ 全部点积起来后再取 $y^0$ 次项，就得到 $(f_v)$ 的 Walsh 变换 $\mathcal W f$。可知 $\displaystyle \mathcal W f_w = [y^0] \prod_{i = 1}^{n} (1 + {h^{a_i}}_w y)$，由于每个 ${h^{a_i}}_w$ 均为 $1$ 或 $-1$，简化为 $\mathcal W f_w = [y^0] (1 + y)^{c_w} (1 - y)^{n - c_w}$，其中 $c_w$ 为满足 ${h^{a_i}}_w = 1$ 的 $i$ 的数量。

问题来到如何对每个 $w$ 计算 $c_w$，即满足 ${h^{a_i}}_w = 1$ 的 $i$ 的数量。由于每个 ${h^{a_i}}_w$ 均为 $1$ 或 $-1$，有 $\displaystyle \sum_{i = 1}^{n} {h^{a_i}}_w = c_w \cdot (1) + (n - c_w) \cdot (-1) = 2 c_w - n$，逆用此式即得 $\displaystyle c_w = \frac{1}{2} \Biggl( n + \sum_{i = 1}^{n} {h^{a_i}}_w \Biggr)$。

根据 Walsh 变换的线性性，既然 $({h^{a_i}}_w)$ 是 $x^{a_i}$ 的 Walsh 变换，就有 $\displaystyle \Biggl( \sum_{i = 1}^{n} {h^{a_i}}_w \Biggr)$ 是 $\displaystyle \sum_{i = 1}^{n} x^{a_i}$ 的 Walsh 变换。于是只需对 $\displaystyle \sum_{i = 1}^{n} x^{a_i}$ 进行一次快速 Walsh 变换即可求得所有的 $c_w$。

接下来解决已知 $c_w$ 求 $\mathcal W f_w = [y^0] (1 + y)^{c_w} (1 - y)^{n - c_w}$ 的部分。注意 $m \le 100$ 的范围使得 $\mathcal O(n m)$ 的复杂度是可以接受的，可以直接对每个 $0 \le i \le n$ 预处理出每个 $(1 + y)^i$ 和 $(1 - y)^i$（注意是循环卷积，所以长度只有 $m$），然后就有 $\displaystyle [y^0] (1 + y)^c (1 - y)^{n - c} = \sum_{j = 0}^{m - 1} \bigl( [y^j] (1 + y)^c \bigr) \cdot \bigl( [y^{m - j}] (1 - y)^{n - c} \bigr)$。这部分的时空复杂度均为 $\mathcal O(n m)$。

最后，在求得 $(\mathcal W f_w)$ 后，将 $\mathcal W f$ 进行一次快速逆 Walsh 变换即得 $(f_v)$，直接计算 $\displaystyle \sum_{v = 0}^{2^b - 1} f_v \cdot v^k$ 即可。

时间复杂度为 $\mathcal O(n m + 2^b (b + \log k))$，空间复杂度为 $\mathcal O(n m + 2^b)$。其中 $\log k$ 来自求 $v^k$ 时使用的快速幂。

注：
- 熟知快速 Walsh 变换的时间复杂度为 $\mathcal O(2^b b)$。
- 求 $v^k$ 时可以使用线性筛法将 $\mathcal O(2^b \log k)$ 变为 $\mathcal O(2^b b^{-1} \log k)$。
- 延伸阅读：
  - [UOJ NOI Round #2 Day1 C. 黎明前的巧克力](https://uoj.ac/contest/39/problem/310)（UOJ310）；
  - [IOI 2023 集训队互测 Round 8 A. 环覆盖](https://qoj.ac/contest/1046/problem/5089)（QOJ5089）；
  - [Codeforces Global Round 2 H. Triple](https://codeforces.com/contest/1119/problem/H)（CF1119H）。

## 参考 AC 代码

代码中逆 Walsh 变换时没有除以 $2^b$，改为在输出答案前除。

```cpp
#include <iostream>
#include <vector>
using std::cin, std::cout;

#define F(i, a, b) for(int i = a; i <= (b); ++i)
#define F2(i, a, b) for(int i = a; i < (b); ++i)

void Solve();
int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    Solve();
    return 0;
}

using LL = long long;
const int Mod = (119 << 23) + 1;
const int B = 20, V = 1 << B, iV = Mod - ((Mod - 1) >> B);

int qPow(int b, int e) {
    int a = 1;
    for (; e; e >>= 1, b = (int)((LL)b * b % Mod))
        if (e & 1)
            a = (int)((LL)a * b % Mod);
    return a;
}

void Solve() {
    int n, m, k;
    cin >> n >> m >> k;
    std::vector<int> v(n + 1, 0); /* to build v */ {
        std::vector<std::vector<int>> plus(n + 1, std::vector<int>(m, 0));
        auto minus = plus;
        plus[0][0] = minus[0][0] = 1;
        F(i, 1, n)
            F2(j, 0, m) {
                int j2 = j ? j - 1 : m - 1;
                plus[i][j] = (plus[i - 1][j] + plus[i - 1][j2]) % Mod;
                minus[i][j] = (minus[i - 1][j] - minus[i - 1][j2] + Mod) % Mod;
            }
        F(i, 0, n)
            F2(j, 0, m)
                v[i] = (int)((v[i] + (LL)plus[i][j] * minus[n - i][j ? m - j : 0]) % Mod);
    }
    std::vector<int> f(V, 0);
    F(i, 1, n) {
        int a;
        cin >> a;
        ++f[a];
    }
    F2(j, 0, B)
        F2(i, 0, V)
            if (~i >> j & 1) {
                int x = f[i];
                int& y = f[i | 1 << j];
                f[i] = x + y;
                y = x - y;
            }
    F2(i, 0, V)
        f[i] = v[(f[i] + n) / 2];
    F2(j, 0, B)
        F2(i, 0, V)
            if (~i >> j & 1) {
                int x = f[i];
                int& y = f[i | 1 << j];
                f[i] = (x + y) % Mod;
                y = (x - y + Mod) % Mod;
            }
    int ans = 0;
    F2(i, 0, V)
        if (f[i])
            ans = (int)((ans + (LL)f[i] * qPow(i, k)) % Mod);
    ans = (int)((LL)ans * iV % Mod);
    cout << ans << '\n';
}
```

后记：我本来想的线性基，在提示做法涉及 FWT 后想出来了，所以总体上算独立做出的。

---

## 作者：yanzihe (赞：3)

## 题意简述
求 $\sum_{S\subseteq\{1, 2,...,n\},m\mid(|S|)}(\bigoplus_{i\in SA_i})^k$。  
$n, k\leq2\times10^5$  
$m\leq 100$  
$A_i\leq2^{20}$

## 前言
用到的前置知识：FWT，生成函数。  


这篇题解从代数推导的角度入手，相信有一定生成函数基础的人理解起来并不困难。

本文用到的一些术语：
- $FWT()$：异或的沃尔什正变换。
- $FWT^{-1}()$：异或的沃尔什逆变换。  
- $[x^a]f(x)$：多项式 $f(x)$ 中 $x^a$ 前的系数。例如 $[x^2](3x^3-4x^2+2)=-4$。
- $a\oplus b$：$a$ 异或 $b$。
- $popcount(x)$：$x$ 二进制下 $1$ 的个数。
- $f(x)\cdot g(x)$：将多项式 $f(x)$ 和 $g(x)$ 的对应项系数相乘。
- $[P]$：艾佛森括号，条件 $P$ 为真时 $[P]=1$，否则 $[P]=0$。  
建议阅读方法：在阅读摘要后先简要阅读两个引理和主要推导过程，初步了解推导思想后阅读总结。最后再仔细阅读一次引理和推导过程，加深理解。

## 概要
本题的核心思想：异或和的 $k$ 次方没有良好的性质，因此考虑枚举异或和是 $a$，设有 $cnt_a$ 种选数方案（选出 $m$ 的倍数个数）能够让选出的数的异或和为 $a$，答案就是 $\sum_{a=0}^Va^kcnt_a$。

因此我们必须快速求出 $cnt$ 数组。为此我们设计出生成函数 $\prod_{i=1}^{n}(x^{A_i}y+x^0)$（其中 $x$ 的乘法是异或卷积，即 $x^a\times x^b=x^{a\oplus b}$，$y$ 的乘法是模 $m$ 的循环卷积，即 $y^a\times y^b=y^{(a+b)\mod m}$）。  


容易注意到该生成函数 $x^ay^b$ 前的系数等于从 $\{A_i\}$ 种选出若干个数，使得它们的异或和为 $a$，且选出的数的个数 $\mod m=b$ 的方案数。所以有 $cnt_a=$ 生成函数中 $x^ay^0$ 前的系数。  


为了快速计算出该生成函数，我把计算过程拆分为三部分。其中两部分放入了如下的两个引理中。


## 两个引理

> 引理 1：存在解法能够在 $O(n+VlogV)$ 时间内对于给定的数列 $\{A_i\}$，求出 $j=0,2,......,V$ 时 $\sum_{i=1}^n[popcount(A_i\&j)是偶数]$。

引理 1 证明：(以下 $FWT()$ 均表示异或的沃尔什正变换， $FWT^{-1}()$ 表示异或的沃尔什逆变换)  


$\sum_{i=1}^n[popcount(A_i\&j)是偶数]$   


$=\sum_{i=1}^n[(-1)^{popcount(A_i\&j)}=1]$  


$=\frac{1}{2}(n+\sum_{i=1}^{n}(-1)^{popcount(A_i\&j)})$  


$=\frac{1}{2}(n+\sum_{i=1}^{n}[x^j]FWT(x^{A_i}))$  


$=\frac{1}{2}(n+[x^j]\sum_{i=1}^{n}FWT(x^{A_i}))$  


$=\frac{1}{2}(n+[x^j]FWT(\sum_{i=1}^{n}x^{A_i}))$   


解释一下第二个等号，$\sum_{i=1}^{n}(-1)^{popcount(A_i\&j)}=\sum_{i=1}^n[popcount(A_i\&j)是偶数]-\sum_{i=1}^n[popcount(A_i\&j)是奇数]$  


又因为 $\sum_{i=1}^n[popcount(A_i\&j)是偶数]+\sum_{i=1}^n[popcount(A_i\&j)是奇数]=n$，联立即可证明第二个等号。  


第三个等号是 $FWT$ 的定义。  


第五个等号是由 $FWT$ 的线性性得出。


因此只需要对 $\sum_{i=1}^{n}x^{A_i}$ 进行一次 $FWT$ 即可。  
引理证毕。

> 引理 2：存在解法能在 $O(VlogV+nm)$ 的时间内，
对于给定的数列 $\{A_i\}$ 和所有的 $j$，求出 $[y^0]\prod_{i=1}^n(1+(-1)^{popcount(A_i\&j)}y)$ （注意这里的多项式乘法是模 $m$ 意义下的循环卷积，即 $y^a\times y^b=y^{(a+b)\mod m}$）  


证明：$\prod_{i=1}^n(1+(-1)^{popcount(A_i\&j)}y)$ 


$=(1+y)^{\sum_{i=1}^n[popcount(A_i\&j)是偶数]}(1-y)^{\sum_{i=1}^n[popcount(A_i\&j)是奇数]}$  


考虑对每个 $i$ 预处理出 $(1+y)^i$ 和 $(1-y)^i$ 的表达式，然后使用引理 1 求出 $\sum_{i=1}^n[popcount(A_i\&j)是偶数]$ 即可。  


因为次数是模 $m$ 意义下的，所以多项式的项数不超过 $m$，因为 $m$ 很小，所以完全可以暴力计算多项式乘法，复杂度是 $O(nm^2)$，但是注意到只有 $y^0$ 的系数对我们有用，所以可以只计算 $y^0$ 系数，复杂度降低至 $O(nm)$。加上引理 1 里的 $O(VlogV)$，总复杂度 $O(nm+VlogV)$。


引理证毕。



## 主要推导部分


#### 


题目求的是   
$\sum_{S\subseteq\{1, 2,...,n\},m\mid(|S|)}(\bigoplus_{i\in SA_i})^k$ 


$=\sum_{a=0}^{V} a^k\sum_{S\subseteq\{1, 2,...,n\},m\mid(|S|)}[\bigoplus_{i\in SA_i}=a]$  


$=\sum_{a=0}^{V} a^k[x^ay^0]\prod_{i=1}^{n}(x^{A_i}y+x^0)$（$x$ 的乘法是异或卷积，$y$ 的乘法是模 $m$ 意义下的循环卷积）  


现在我们来研究 $\prod_{i=1}^{n}(x^{A_i}y+x^0)$

$\prod_{i=1}^{n}(x^{A_i}y+x^0)$


$=FWT^{-1}(F_1(x)\cdot F_2(x)\cdot ...... \cdot F_n(x))$（“$\cdot$”表示对应项的系数相乘）  


其中 $F_i=FWT(x^{A_i}y+x^0)$  


$=FWT(x^{A_i}y)+FWT(x^0)$  


$=\sum_{j=0}^{V}
((-1)^{popcount({A_i}\&j)}y+1)x^j$  


所以 $\prod_{i=1}^{n}(x^{A_i}y+x^0)$  


$=FWT^{-1}(\sum_{j=0}^{V}(\prod_{i=1}^n(1+(-1)^{popcount(A_i\&j)}y))x^j)$  

使用引理 2 的方法算出 $[y^0](\prod_{i=1}^n(1+(-1)^{popcount(A_i\&j)}y))$，然后进行 $FWT^{-1}$ 即可得到 $\prod_{i=1}^{n}(x^{A_i}y+x^0)$ 的各项系数，于是这道题就做完了。

### 总结
如果 $m=1$，这题并不困难，但是 $m$ 的约束很难单独处理，因此巧妙地设计出了二元生成函数，从而做到同时满足 $m$ 的约束和异或和的约束。

而在处理二元生成函数卷积时，采用了主元的思想，将 $y$ 视作常数进行 FWT。

快速计算 $\sum_{i=0}^n[popcount(A_i\&j)是偶数]$ 也是一个难点。因为这个式子的形式和异或卷积的形式非常相似，所以尝试构造一个生成函数，对它进行沃尔什正变换，再恒等变形后得到 $\sum_{i=0}^n[popcount(A_i\&j)是偶数]$。

### 代码
代码还是十分容易编写的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i, a, b) for(ll i=a;i<=b;i++)
#define rrep(i, a, b) for(ll i=a;i>=b;i--)
const ll N=2e6+9, MOD=998244353;
ll n, k;
ll m;
ll a[N];
void multiply(vector <ll> &res, vector <ll> &a, vector <ll> &b){//模m意义下循环卷积,让res变成a*b
    res.resize(m, 0);
    rep(i, 0, a.size()-1){
        rep(j, 0, b.size()-1){
            (res[(i+j)%m]+=a[i]*b[j])%=MOD;
        }
    }
}
ll multiply0(vector <ll> &a, vector <ll> &b){//模m意义下循环卷积,返回a*b这个多项式的常数项
    ll ans=0;
    rep(i, 0, a.size()-1){
        if(m-i<b.size())(ans+=a[i]*b[m-i])%=MOD;
    }
    if(!a.empty()&&!b.empty())ans+=a[0]*b[0];ans%=MOD;
    return ans;
}   
vector <ll> yadd1={1, 1}, fyadd1={1, -1};
void FWT_XOR(ll w, ll *a){//对长度为2^w的数组a进行异或卷积
    for(ll len=1;len<=(1LL<<w);len<<=1){
        for(ll l=0;l<(1LL<<w);l+=len){
            rep(i, 0, len/2-1){
                ll x=a[l+i], y=a[l+len/2+i];
                a[l+i]=x+y;a[l+i]%=MOD;
                a[l+len/2+i]=x-y+MOD;a[l+len/2+i]%=MOD;
            }
        }
    }
}
ll power(ll u, ll t){
    ll ans=1;
    while(t){
        if(t&1)ans=ans*u%MOD;
        u=u*u%MOD;
        t>>=1;
    }
    return ans;
}
void IFWT_XOR(ll w, ll *a){
    FWT_XOR(w, a);
    ll n1=power((1LL<<w), MOD-2);
    rep(i, 0, (1LL<<w)-1){
        a[i]*=n1;a[i]%=MOD;
    }
}
ll cntEven[N], cntOdd[N];
ll A[N];
vector <ll> Y1[N], Y2[N];//y1[i]存储(1+y)^i,y2[i]存储(1-y)^i
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n >> m >> k;
    rep(i, 1, n){
        cin >> A[i];
    }
    ll V=(1LL<<20);
    //第一步，对于每一个j，计算它和多少个a的与的popcount是偶数（引理1）
    rep(i, 1, n){
        a[A[i]]++;
    }
    FWT_XOR(20, a);
    ll p2=power(2, MOD-2);
    rep(j, 0, V-1){
        cntEven[j]=p2*(n+a[j])%MOD;
        cntOdd[j]=n-cntEven[j];
    }
    //第二步，计算生成函数x^j的系数（引理2）
    //注意到我们只需要提取x^j的系数中y^0的系数
    Y1[0].emplace_back(1);Y2[0].emplace_back(1);
    rep(i, 1, n){
        multiply(Y1[i], Y1[i-1], yadd1);
        multiply(Y2[i], Y2[i-1], fyadd1);
    }
    fill(a, a+N-2, 0);
    rep(j, 0, V-1){
        a[j]=multiply0(Y1[cntEven[j]], Y2[cntOdd[j]]);
    }
    //第三步，逆向FWT
    IFWT_XOR(20, a);
    //第四步，计算答案
    ll ans=0;
    rep(i, 0, V-1){
        ans+=power(i, k)*a[i];ans%=MOD;
    }
    cout << ans << endl;
    return 0;
}

```

---

## 作者：qczrz6v4nhp6u (赞：3)

长脑子了。

### Solution

不难发现答案即为

$$\sum_{i=0}^{V}i^K[x^iy^0]\prod_{j=1}^n(1+x^{a_j}y)$$

其中 $x$ 的卷积是 xor 卷积，$y$ 的卷积是循环卷积。

现在我们考虑求后面那坨式子。记 $\hat F$ 为 $F$ 的 FWT 结果，即 $\hat F_i=\sum_{j}(-1)^{{\rm popcount}(i{~\rm and~}j)}F_j$。

我们考虑 $(1+x^py)$ 的 FWT 是什么样的。显然 FWT 后的每个位置只可能是 $1+y$ 或 $1-y$，考虑如何应用这个性质。

记 $G=\sum_{i=1}^n(1+x^{a_i}y)$。由 FWT 的线性性，$\hat G$ 等于 $(1+x^{a_i}y)$ 的 FWT 结果之和。由于 $(1+x^{a_i}y)$ 的每个位置是 $1+y$ 或 $1-y$，则 $\hat G_i$ 可以表示为 $n+t_i\times y$ 的形式。

设 $1+y$ 共有 $u_i$ 个，$1-y$ 共有 $v_i$ 个。比较系数有 $u_i+v_i=n,u_i-v_i=t_i$。不难解出 $u_i,v_i$。

记 $H=\prod_{i=1}^n(1+x^{a_i}y)$，那么 $\hat H_i=(1+y)^{u_i}(1-y)^{v_i}$，直接预处理 $1+y$ 和 $1-y$ 的幂次，最后找到 $y^0$ 的系数 FWT 回去即可。

时间复杂度 $O(V\log V+Vm+nm)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=2e5+5,M=105,V=(1<<20)+5,mod=998244353;
int n,m,K;
ll F[V],G[V],P1[N][M],P2[N][M];
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
void FWT(ll *F,int n,int type){
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=i<<1)
			for(int k=0;k<i;k++){
				ll x=F[j|k],y=F[i|j|k];
				F[j|k]=(x+y)%mod,F[i|j|k]=(x-y+mod)%mod;
			}
	if(type==-1){
		ll inv=qpow(2,mod-__lg(n)-1);
		for(int i=0;i<n;i++)F[i]=F[i]*inv%mod;
	}
}
void mul(ll *c,ll *a,ll *b){
	for(int i=0;i<m;i++)c[i]=0;
	for(int i=0;i<m;i++)
		for(int j=0;j<2;j++)
			c[(i+j)%m]=(c[(i+j)%m]+a[i]*b[j])%mod;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>K;
	for(int i=1;i<=n;i++){
		int a;cin>>a;
		++F[a];
	}
	FWT(F,1<<20,1);
	P1[0][0]=1,P2[0][0]=1;
	if(m==1)P1[1][0]=2;
	else P1[1][0]=P1[1][1]=P2[1][0]=1,P2[1][1]=mod-1;
	for(int i=2;i<=n;i++)
		mul(P1[i],P1[i-1],P1[1]),mul(P2[i],P2[i-1],P2[1]);
	for(int i=0;i<(1<<20);i++){
		int u=(n+F[i])%mod>>1,v=n-u;
		for(int j=0;j<m;j++)
			G[i]=(G[i]+P1[u][j]*P2[v][(m-j)%m])%mod;
	}
	FWT(G,1<<20,-1);
	ll ans=0;
	for(int i=0;i<(1<<20);i++)
		ans=(ans+qpow(i,K)*G[i])%mod;
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：3)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18383402)

### [[ABC367G] Sum of (XOR^K or 0)](https://www.luogu.com.cn/problem/AT_abc367_g)

考虑求出 $ans_i$ 表示选了 $m$ 的倍数个数，异或和是 $i$ 的方案数再统计答案。

先考虑 $m=1$ 怎么做。相当于是 $ans_i=[x^i]\prod_j (x^0+x^{a_j})$，这里的乘法是异或卷积。如果直接 `xor-FWT` 复杂度不如暴力。令 $F_i(x)$ 表示第 $i$ 个数对应的集合幂级数，列出式子：

$$
\begin{aligned}
f_k&=[x^k]\text{FWT}(\prod_i F_i(x))\\
&=\prod_i ((-1)^{\text{popcount}(k\And a_i)}+(-1)^{\text{popcount}(k\And 0)})\\
&=\prod_i ((-1)^{\text{popcount}(k\And a_i)}+1)\\
\end{aligned}
$$

所以只需要对于每个 $k$ 求出求出 $\text{popcount}(k\And a_i)$ 是奇数和偶数的 $j$ 的个数。考虑构造一个新的集合幂级数 $G_i(x)$，满足 $G_i(x)=x^{a_i}$，所以 $\text{FWT}(G_i(x))=\sum_j x^j(-1)^{\text{popcount}(j\And a_i)}$。

$$
g_k=\sum_{i}(-1)^{\text{popcount}(k\And a_i)}=\sum_i [x^k]\text{FWT}(G_i(x))
$$

因为 FWT 是线性变换，所以

$$
g_k=[x^k]\text{FWT}(\sum_i G_i(x))
$$

$x$ 表示 $\text{popcount}(k\And a_i)$ 是偶数的个数，$y$ 表示奇数，则有

$$
\left\{\begin{matrix}
x+y=n\\
x-y=g_k
\end{matrix}\right.
$$

可以对于每个 $k$ 解出来 $x,y$。这样就求出来了异或卷积的 FWT 数组 $f_i$，把 $f$ IFWT 回去就得到了 $ans_i$。

对于如何拓展到 $m\not=1$，其实也很简单，看成在 $x$ 中选若干个，$y$ 中选若干个，要求选的总数是 $m$ 的倍数并且在 $y$ 中每选一个都要乘一个 $-1$。预处理 $a_{i,j}=\sum_{k\equiv j\pmod m}\binom{i}{k}$ 和 $b_{i,j}=\sum_{k\equiv j\pmod m}\binom{i}{k}(-1)^k$，然后把 $a,b$ 合并起来就能求出 $c_i$ 表示有 $i$ 个 $1$，$n-i$ 个 $-1$，在之中选 $m$ 的倍数个的所有方案的权值乘积和，然后令 $f_i=c_x$ 即可。总复杂度 $\mathcal O(nm+k2^k)$，其中 $k=20$。

```cpp
const int N=1<<20;
int n,m,K,f[N],F[200010][110],G[200010][110],H[200010];
inline void mian()
{
	read(n,m,K),F[0][0]=G[0][0]=1;int x,y,iv=power(N,MOD-2),ans=0;
	for(int i=0;i<n;++i)for(int j=0;j<m;++j)
	Madd(F[i+1][j],F[i][j]),Madd(F[i+1][(j+1)%m],F[i][j]),
	Madd(G[i+1][j],G[i][j]),Mdel(G[i+1][(j+1)%m],G[i][j]);
	for(int i=0;i<=n;++i)for(int j=0;j<m;++j)
	Madd(H[i],Cmul(F[i][j],G[n-i][(m-j)%m]));
	for(int i=1;i<=n;++i)read(x),++f[x];
	for(int i=1;i<N;i<<=1)for(int j=0;j<N;j+=i<<1)for(int k=j;k<j+i;++k)
	x=f[k]+f[k+i],y=f[k]-f[k+i],f[k]=x,f[k+i]=y;
	for(int i=0;i<N;++i)f[i]=H[(n+f[i])>>1];
	for(int i=1;i<N;i<<=1)for(int j=0;j<N;j+=i<<1)for(int k=j;k<j+i;++k)
	x=Cadd(f[k],f[k+i]),y=Cdel(f[k],f[k+i]),f[k]=x,f[k+i]=y;
	for(int i=0;i<N;++i)Madd(ans,Cmul(f[i],iv,power(i,K)));
	write(ans);
}
```

---

## 作者：喵仔牛奶 (赞：2)

# Soluton

令 $v=2^{20}-1$。

异或和的次幂非常不可做，考虑求出异或和为 $i$ 的方案数 $ct_i$，答案即为 $\sum_{i=0}^{v}ct_i\times i^k$。

考虑集合幂级数。设 $x,y$，它们的乘法分别定义为 $x^a\cdot x^b=x^{a\text{ xor }b}$，$y^a\cdot y^b=y^{(a+b)\bmod m}$。那么 $ct_t$ 就是：
$$[x^ty^0]\prod_{i=1}^{n}(1+yx^{A_i})$$

加入 $\text{FWT}$，简易说明一下 $\text{FWT}$：
$$[x^i]\text{FWT}(A)=\sum_j(-1)^{\text{popcount(i\text{ and }j)}}[x^j]A$$

原来那个式子变成：
$$[x^ty^0]\text{IFWT}(\sum x^i\prod_{j=1}^{n}[x^i]\text{FWT}(1+yx^{A_j}))$$

由于 $\text{FWT}$ 的线性性，把 $[y^0]$ 放进去：
$$[x^t]\text{IFWT}(\sum x^i[y^0]\prod_{j=1}^{n}[x^i]\text{FWT}(1+yx^{A_j}))$$

外面的 $\text{IFWT}$ 最后做一下就好了，不用管它，我们来观察 $\prod_{j=1}^{n}[x^i]\text{FWT}(1+yx^{p})$ 有没有啥性质。

容易发现：
$$[x^i]\text{FWT}(1+yx^{p}))=\begin{cases}1+y&\text{popcount}(i\text{ and }p)\equiv 0\pmod 2\\1-y&\text{popcount}(i\text{ and }p)\equiv 1\pmod 2\end{cases}$$

那么我们设 $\prod_{j=1}^{n}[x^i]\text{FWT}(1+yx^{A_j}))=(1+y)^{a_i}(1-y)^{b_i}$。这个 $a_i,b_i$ 怎么求呢？
$$
\begin{cases}
a_i+b_i=n,\\
a_i-b_i=\sum_{i=1}^{n}(-1)^{\text{popcount}(i\text{ and }A_i)}
\end{cases}
$$

可以发现设 $f=\sum x^i\sum_{j=1}^{n}[A_j=i]$，$a_i-b_i$ 就是 $[x^i]\text{FWT}(f)$。

我们再把式子拿回来：
$$[x^t]\text{IFWT}(\sum x^i[y^0](1+y)^{a_i}(1-y)^{b_i})$$

$(1+y)^{a_i},(1-y)^{b_i}$ 都可以 $\mathcal{O}(nm)$ 预处理展开后的系数。而 $(a_i,b_i)$ 总共只有 $n+1$ 种，每种 $(1+y)^{a_i}(1-y)^{b_i}$ 的 $y^0$ 项系数可以 $\mathcal{O}(m)$ 求出。这部分预处理总复杂度 $\mathcal{O}(nm)$。

综上，我们在 $\mathcal{O}(nm)$ 时间内处理出了 $\sum x^i\cdot[y^0]((1+y)^{a_i}(1-y)^{b_i}$，最后 $\text{IFWT}$ 一下即可得出答案。

求 $i^k$ 部分拿个线性筛可以变成 $\frac{v\log k}{\log v}$，不过没啥必要。

时间复杂度 $\mathcal{O}(nm+v\log v+v\log k)$。

# Summary

主要思路：
- 写出式子
- 化简 $\prod_{j=1}^{n}[x^i]\text{FWT}(1+yx^{A_j}))$。
- 直接做即可。

# Code

```cpp
const int N = 2e5 + 5, M = 105, K = 1.1e6 + 5, mod = 998244353;
typedef Mint<mod> MI;
int n, m, k, x; MI rs, f[K], A[N][M], B[N][M], coe[N];
void fwt(MI* f, int n, int op) {
	MI inv2 = (MI)1 / 2;
	REP(i, 0, n - 1) REP(j, 0, (1 << n) - 1) {
		if (j >> i & 1) continue;
		MI x = f[j], y = f[j ^ 1 << i];
		f[j] = x + y, f[j ^ 1 << i] = x - y;
		if (op < 0) f[j] *= inv2, f[j ^ 1 << i] *= inv2;
	}
}
int main() {
	cin >> n >> m >> k;
	REP(i, 1, n) cin >> x, f[x] += 1;
	A[0][0] = B[0][0] = 1;
	REP(i, 0, n - 1) REP(j, 0, m - 1) {
		A[i + 1][j] += A[i][j];
		A[i + 1][(j + 1) % m] += A[i][j];
		B[i + 1][j] += B[i][j];
		B[i + 1][(j + 1) % m] -= B[i][j];
	}
	REP(i, 0, n) REP(j, 0, m - 1)
		coe[i] += A[i][j] * B[n - i][(m - j) % m];
	fwt(f, 20, 1);
	REP(i, 0, (1 << 20) - 1)
		f[i] = coe[(f[i] + n).x / 2];
	fwt(f, 20, -1);
	REP(i, 0, (1 << 20) - 1)
		rs += f[i] * qpow((MI)i, k);
	cout << rs << '\n';
	return 0;
}
``

---

## 作者：Starrykiller (赞：2)

我们知道 $\operatorname{FWT}(A\ast B)=\operatorname{FWT}(A)\cdot \operatorname{FWT}(B)$。在模板题中，我们就是利用了点积可以快速计算的性质，来快速解决了位运算卷积问题。


不妨记序列 $V_i=(V_{i,0},V_{i,1},\cdots,V_{i,2^{L}-1})$。其中，$V_{i,0}=0$，$V_{i,A_i}=z$。特别地，$A_i=0$ 时，$V_{i,0}=1+z$。将这 $N$ 个序列（异或卷积）卷起来后 IFWT，每个位置上多项式的零次项系数即为异或出它的方案数。注意这里的乘法是 $\pmod {z^M-1}$ 的，也就是循环卷积。

然而，这样的复杂度过高（$\Theta(NL2^L)$），无法接受。

当然，**也可以先对每个序列做 FWT，再将 $N$ 个序列点乘起来**。这显然也是无法接受的。

设 $V_i$ FWT 后得到 $\hat V_i$。

注意到我们有一个很好的性质：每个序列 $V_i$ 中，非零的元素很少（最多只有 $2$ 种，也就是 $1$ 和 $z$）。注意到 $\displaystyle \operatorname{FWT}(A)_i=\sum_{j=0}^{2^L-1}(-1)^{\operatorname{popcount}(i\operatorname{and}j)} A_j$，这意味着，$\hat V_i$ 中的元素只有两种：$1\pm z$（对于 $A_i=0$ 的情况，注意到 $\hat V_i=(1+z,1+z,\cdots)$，也被包含在了这种情况中）。我们想要知道最后 $N$ 个 $\hat V_i$ 点乘的结果，那么只需要知道：对于 $j=0,1,\cdots,2^{L}-1$，$1+z$，$1-z$ 分别在 $i=1,2,\cdots,N$ 的 $\hat V_i^{(j)}$ 中出现了几次。不妨设它们分别出现了 $a,b$ 次，则这一位点乘之后就是 $(1+z)^a(1-z)^b$。

现在问题的关键化为了找到 $a,b$ 的值。

考虑对 $B=(\mathrm{cnt}_0,\mathrm{cnt}_1,\cdots,\mathrm{cnt}_{2^L-1})$ 做 FWT 后会得到的 $\hat B$ 的形状，其中 $\mathrm{cnt}_i=\sum_{k=1}^N [A_k=i]$。由定义我们得到 $\hat B_i=\sum_{j=0}^{2^L-1}(-1)^{\operatorname{popcount}(i\operatorname{and}j)} B_j=\sum_{j=0}^{2^L-1}(-1)^{\operatorname{popcount}(i\operatorname{and}j)} \sum_{k=1}^N [A_k=j]=\sum_{j=0}^{2^L-1}\sum_{k=1}^N (-1)^{\operatorname{popcount}(i\operatorname{and}j)} [A_k=j]$。

考虑到，对 $U_k=(0,0,\cdots,\underset{\text{第 }A_k\text{ 位}}{z},\cdots,0)$ 做 FWT 时，得到的是 $\hat U_k^{(i)}=\sum_{j=0}^{2^L-1}(-1)^{\operatorname{popcount}(i\operatorname{and}j)}U_j=\sum_{j=0}^{2^L-1}(-1)^{\operatorname{popcount}(i\operatorname{and}j)}[A_k=j]z$。本质上来说，**$\boldsymbol{\hat B}$ 就相当于把所有 $\boldsymbol{\hat U_k}$ 加起来，而这意味着 $\boldsymbol{\hat B_i=a-b}$**。注意到 $\boldsymbol{a+b=N}$，现在我们已经得知了 $a,b$ 的值。

最后只需要对 $2^L$ 个位置求一个 $[z^0](1+z)^a(1-z)^{n-a} \bmod (z^M-1)$ 即可。不难 $\Theta(NM)$ 预处理。

综上，我们在 $\Theta(NM+2^L(L+\log K))$ 的时间复杂度内解决了本题。

[代码](https://atcoder.jp/contests/abc367/submissions/56857725)。

CF1119H 是本题中有三种不同的值的情况。

----

非常感谢 @[NaCly_Fish](https://www.luogu.com.cn/user/115864) 的耐心细致的教学！/qq/qq

[Madoka 酱](https://www.luogu.com.cn/user/361356)贴贴！爱你！我会一直等着你的 www

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc367_g)

**题目大意**

> 定义一个集合 $S$ 的权值为其内部元素的异或和的 $k$ 次方。
>
> 给定 $a_1\sim a_n$，求其所有大小为 $m$ 的倍数的子集的权值和。
>
> 数据范围：$n\le 2\times 10^5,a_i<2^{20},m\le 100$。

**思路分析**

考虑用生成函数的语言描述，很显然我们同时关心集合大小和元素异或和，因此可以用 $F(x,z)=\prod (1+x^{a_i}z)$ 描述，其中 $z$ 是形式幂级数，$x$ 是集合幂级数。

不妨把 $z$ 看成参数，那么这就是若干个关于 $x$ 的集合幂级数做异或卷积。

考虑 FWT，那么 $\mathrm{FWT}(x^{\varnothing}+x^{a_i}z)=\sum_s\left(1+(-1)^{\mathrm{popcount}(a_i\operatorname{AND}s)}z\right)x^s$。

那么 $[x^s]\mathrm{FWT}(F)$ 就是若干 $1+z$ 和 $1-z$ 的乘积，具体来说就是 $\sum_sx^s(1+z)^{w_s}(1-z)^{n-w_s}$。

我们只要求出这些 $w_s$，直接对 $\sum x^{a_i}$ FWT 即可得到 $w_s-(n-w_s)$ 然后就能算出 $w_s$。

然后我们要求 $[z^{km}]\mathrm{IFWT}(\sum_sx^s(1+z)^{w_s}(1-z)^{n-w_s})$。

不难发现这就等于 $\mathrm{IFWT}(\sum_sx^s[z^{km}](1+z)^{w_s}(1-z)^{n-w_s})$。

那么只要对每个 $w$ 求出 $[z^0](1+z)^{w}(1-z)^{n-w}\bmod{z^m-1}$ 然后 IFWT 回去，暴力处理即可。

时间复杂度 $\mathcal O(nm+V\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5,N=1<<20,MOD=998244353,i2=(MOD+1)/2;
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
int n,m,pw,c[N],f[MAXN][105],g[MAXN][105];
ll ans=0,w[MAXN],d[N]; //[z^0](1+z)^i(1-z)^n-i
inline void add(int &x,const int &y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
inline void sub(int &x,const int &y) { x=(x>=y)?x-y:x+MOD-y; }
signed main() {
	scanf("%d%d%d",&n,&m,&pw);
	for(int i=1,x;i<=n;++i) scanf("%d",&x),++c[x];
	for(int k=1;k<N;k<<=1) for(int i=0;i<N;i+=k<<1) for(int j=i;j<i+k;++j) {
		int x=c[j],y=c[j+k]; c[j]=x+y,c[j+k]=x-y;
	}
	f[0][0]=g[0][0]=1;
	for(int i=1;i<=n;++i) {
		memcpy(f[i],f[i-1],sizeof(f[i]));
		memcpy(g[i],g[i-1],sizeof(g[i]));
		for(int j=0;j<m;++j) {
			add(f[i][(j+1)%m],f[i-1][j]);
			sub(g[i][(j+1)%m],g[i-1][j]);
		}
	}
	for(int i=0;i<=n;++i) {
		for(int j=0;j<m;++j) w[i]=(w[i]+1ll*f[i][j]*g[n-i][(m-j)%m])%MOD;
	}
	for(int s=0;s<N;++s) d[s]=w[(n+c[s])>>1];
	for(int k=1;k<N;k<<=1) for(int i=0;i<N;i+=k<<1) for(int j=i;j<i+k;++j) {
		ll x=d[j],y=d[j+k]; d[j]=(x+y)*i2%MOD,d[j+k]=(x-y)*i2%MOD;
	}
	for(int s=0;s<N;++s) ans=(ans+d[s]*ksm(s,pw))%MOD;
	printf("%lld\n",(ans+MOD)%MOD);
	return 0;
}
```

---

## 作者：forest114514 (赞：1)

不久前刚从黎明前的巧克力学到了这种非常巧妙的做法，没想到在这里又遇见了。

考虑将每一个数看做多项式 $x^{a_i}y+1$，答案为 $\sum\limits_{v}v^k[x^ky^0]\prod\limits_{i=1}^{n}(x^{a_{i}}y+1)$，其中 $x$ 做的是异或卷积，$y$ 做的是 $m$ 次循环卷积，显然这个式子不能直接 FWT，不然不如暴力。

注意到 FWT_XOR 变换的点值就是 $[x^{S}]FWT(F)=\sum\limits_{T}(-1)^{|S\cap T|} [x^T]F$，然后发现 $F_{i}=(x^{{a_i}}y+1)$ 这个多项式做 FWT 后的点值是好算的，就是 $[x^S]FWT(F_i)=1+(-1)^{|S\cap a_i|}y$，显然点值相乘就是若干 $1\pm y$ 相乘，所以 $[x^ky^0]\prod\limits_{i=1}^{n}(x^{a_{i}}y+1)=(1-y)^{A_{k}}(1+y)^{n-A_k}$，现在问题在于求出 $A_k$。

可以照搬黎明前的巧克力的做法，因为 $A_{k}(1-y)+(1+y)(n-A_k)$ 显然是一个关于 $y$ 的一次多项式，随便算就能知道 $A_k$ 是什么了，又因为 $FWT(A+B)=FWT(A)+FWT(B)$，所以直接把所有 $(x^{a_{i}}y+1)$ 相加做一遍 FWT 即可。

然后对所有位求出 $[y^0](1-y)^{A_{k}}(1+y)^{n-A_k}$ 后再 IFWT 回去就能得到 $\sum\limits_{v}v^k[x^ky^0]\prod\limits_{i=1}^{n}(x^{a_{i}}y+1)$ 了，预处理所有 $(1-y)^{n-i}(1+y)^{i}$ 即可，最后时间就是 $O(nm+2^V\log k+V2^V),V=20$。

[提交记录](https://atcoder.jp/contests/abc367/submissions/57882815)

---

## 作者：Nityacke (赞：1)

首先对于异或的次幂我们加入一个数后看起来不能通过什么方式从原来的答案得到，我们考虑对于每种异或值 $x$，算出 $x$ 的方案数 $ans_x$，则答案就是
$$
\sum_{i=0}^Vans_ii^k
$$
然后对于计算 $a_x$，我们可以考虑集合幂级数，由于我们需要数的个数是 $m$ 的倍数，所以我们引入一个变量 $y$，如果我们对于 $y$ 做关于 $y^m$ 的循环卷积，对于 $x$ 做异或卷积，然后我们就知道:
$$
ans_i=[y^0x^i]\prod_{i=1}^n(1+yx^{a_i})
$$
然后我们考虑计算这个东西，暴力 FWT 后乘起来再 IFWT 复杂度是 $O(nV\log V\text{poly}(m))$ 无法通过。

考虑 [【UNR #2】黎明前的巧克力](https://uoj.ac/problem/310) 相同的做法。

由于我们知道
$$
\hat F_S=\sum_T (-1)^{|S\cap T|}F_T
$$
然后我们每一个多项式是 $1+yx^{a_i}$ 的简单形式，所以我们知道 FWT 后的数组的每个位置只可能是  $1+y$ 和 $1-y$ 。

知道了这个有什么用了，我们发现，由于 FWT 的线性性，我们可以把所有的 $1+yx^{a_i}$ 求和，然后一起 FWT。

这样我们每个位置形如 $n+z_i\times y$ ，这样我们就知道了设 $1+y,1-y$ 的个数分别是 $A,B$，则 $A+B=n,A-B=z_i$，这样我们可以得到 $A,B$ 的值。

当然由于我们发现每个位置的常数项一定为 $n$，可以只维护 $y$ 的系数即可，可以减少常数。

我们回到我们暴力计算的方法，发现我们 FWT 后每个位置乘起来就是 $(1+y)^A(1-y)^B$，所以我们预处理后可以 $O(m)$ 得到每个位置 $[y^0]$ 的系数，这个时候我们只需要 IFWT 回来就可以得到每个位置的 $ans_i$。

直接计算答案即可，时间复杂度 $O(V\log V+Vm+n)$。

```cpp
#include<bits/stdc++.h>
#define poly vector<int>
using namespace std;
const int N=2e5+5,V=1<<20,H=998244353;
poly f1[N],f2[N],a;
int n,m,k;
inline int qp(int a,int b=H-2){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%H)
		if(b&1) ans=1ll*ans*a%H;
	return ans;
}
inline void add(int &x,int v){if((x+=v)>=H) x-=H;}
inline poly operator*(poly a,poly b){
	poly c(min(m,(int)a.size()+(int)b.size()-1),0);
	for(int i=0;i<(int)a.size();++i)
		for(int j=0;j<(int)b.size();++j)
			add(c[(i+j)%m],1ll*a[i]*b[j]%H);
	return c;
}
inline void FWT(poly &f,int L,int v){
	for(int mid=1;mid<L;mid<<=1)
		for(int i=0;i<L;i+=mid<<1)
			for(int j=i,t1,t2;j<i+mid;++j)
				t1=f[j],t2=f[j+mid],
				f[j]=1ll*(t1+t2)*v%H,f[j+mid]=1ll*(t1+H-t2)*v%H;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k,a.resize(V);
	for(int x,i=1;i<=n;++i) cin>>x,++a[x];
	f1[0]=f2[0]={1};
	if(m==1) f1[1]={2},f2[1]={0};
	else f1[1]={1,1},f2[1]={1,H-1};
	for(int i=2;i<=n;++i) f1[i]=f1[i-1]*f1[1],f2[i]=f2[i-1]*f2[1];
	FWT(a,V,1);
	for(int i=0;i<V;++i){
		int A=(1ll*(n+a[i])*(H+1)/2)%H,B=(1ll*(n+H-a[i])*(H+1)/2)%H,ans=0;
		for(int j=0;j<m;++j)
			if(j<f1[A].size()&&(m-j)%m<f2[B].size()) add(ans,1ll*f1[A][j]*f2[B][(m-j)%m]%H);
		a[i]=ans;
	}
	FWT(a,V,(H+1)/2);
	int ans=0;
	for(int i=0;i<V;++i) add(ans,1ll*qp(i,k)*a[i]%H);
	cout<<ans<<"\n";
}
```

---

## 作者：Otomachi_Una_ (赞：0)

相当于求 $\prod_{i=1}^n (1+yx^{a_i})\pmod{y^M-1}$。其中对 $x$ 是异或卷积，$y$ 是正常卷积。

考虑先 FWT，$\operatorname{FWT}(1+yx^{a_i})=\sum_{k=0} (1+(-1)^{\operatorname{sgn}(a_i\operatorname{ AND }k)}y)x^k$。

我们发现对每个 $x^k$ 只有 $1+y,1-y$ 两种可能。我们容易通过类 FWT 算出每个 $k$ 有多少个 $1+y$，多少个 $1-y$。

我们只需要解决类似 $[y^0]((1+y)^k(1-y)^{n-k}\pmod {y^M-1})$ 这样的问题。

通过递推算出每个 $i=0,1,2,\dots,n$，$(1±y)^{i}\pmod{y^M-1}$ 即可。

---

## 作者：pan_g (赞：0)

[传送门1](https://www.luogu.com.cn/problem/AT_abc367_g)
[传送门2](https://atcoder.jp/contests/abc367/tasks/abc367_g)

看到这道题，可以直接考虑求 $H$ ，其中 $H_i$ 表示大小为 $M$ 的倍数子序列 $B$ 且异或和为 $i$ 的个数。

令 $L = 20$ ，那么答案就是 $\sum_{i=0}^{2^L-1} H_i i^K$ 。

但是因为涉及到 $\operatorname{xor}$ 运算，考虑 FWT （没做过 FWT 的题，赛时想到这就没了），于是就开始构造 GF ：

有 $N$ 个 GF $S_i = x^{A_i}y + 1$ ，其中 $x$ 按 $\operatorname{xor}$ 卷积， $y$ 按加卷积，于是如果令 $V = \bigcirc_{i=1}^{N}S_i$ ，那么 $H_i = \sum_{j=0}^{\lceil\frac{N}{M}\rceil} [y^{jM}][x^i]V$ ，或者说是 $H_i = [y^0][x^i]V\pmod {y^M - 1}$ 。

但是直接这么暴力去卷肯定不行，时间复杂度 $O(NL2^L)$ 。

于是考虑一些优化，可以先考虑分别 FWT 再点积，最后 IFWT 回去。

同样的 FWT 有一个很重要的性质 $\operatorname{FWT}(A)_i = \sum_{j=0}^{N}(-1)^{\operatorname{popcount}(i \operatorname{and} j)} A_j$ 。

因为**每个多项式都只有 $1\sim 2$ 项**，可以得到每一个多项式的 FWT 的 $x^i$ 的每个系数都是 $(1+y)$ 或者 $(1-y)$ 。

那么 IFWT 前的 $H'_i$ 一定可以表示为 $(1+y)^a(1-y)^b$ ，其中 $a + b = N$ ，所以只要算出 $a$ 即可，假设第 $i$ 项的 $a,b$ 分别是 $F_{i,0/1}$ 。

先考虑如何处理 $H'_i$ ，其实可以 $O(NM)$ 简单预处理 $G_i = \sum_{j=0}^{\lceil\frac{N}{M}\rceil} [y^{jM}]((1 + y)^i(1 - y)^{N - i})$ ，然后我们要做的是算出 $F_{i,0}$ 带到 $G_{F_{i,0}}$ 里面，那么 $H_i = G_{F_{i,0}}$ 。

接下来，才是重头戏，怎样去算 $F$ 。

接下来主要是利用了 FWT 的运算方式还有 FWT 的性质 $\operatorname{FWT}(A)_i = \sum_{j=0}^{N}(-1)^{\operatorname{popcount}(i \operatorname{and} j)} A_j$ 。

那么根据性质我们可以看出 $F_{i,j} = \sum_{\operatorname{popcount}(i \operatorname{and} k) \bmod 2 = j} \operatorname{cnt}(k)$ ，其中 $\operatorname{cnt}(x)$ 表示 $x$ 在 $A$ 中出现的次数。

暴力是 $O(N^2)$ 的，我们不满意（接下来的有关二进制的内容可以方便很多学过 FFT 的人写代码）。

于是我们发现，在 FWT 的过程中，发生运算的恰好是只有一位是不同的，所以**只用考虑当前幂级数上的值**就好了，因为 $0 \operatorname{and} 0 = 0 \operatorname{and} 1 = 1 \operatorname{and} 0 = 0$ ，所以这种情况 $\operatorname{popcount}$ 的奇偶性不会变，唯独 $1 \operatorname{and} 1 = 1$ 会变，所以可以结合之前的奇偶性推出下面的式子。

也就是，

$$
\begin{aligned}
F_{i, 0} &= F_{i, 0} + F_{i + \frac{n}{2}, 0} \\
F_{i, 1} &= F_{i, 1} + F_{i + \frac{n}{2}, 1} \\
F_{i + \frac{n}{2}, 0} &= F_{i, 0} + F_{i + \frac{n}{2}, 1} \\
F_{i + \frac{n}{2}, 1} &= F_{i, 1} + F_{i + \frac{n}{2}, 0} \\
\end{aligned}
$$

最开始的时候肯定是 $F_{i, 0} = \operatorname{cnt}(i)$ 。

时间复杂度 $\Theta(NM + 2^L(L + \log_2K))$ 。

```cpp
#include <bits/stdc++.h>
#define endl "\n"
typedef long long i64;

template <class T> constexpr T Pow(T a, i64 b){
    T res = 1;
    for( ; b ; b >>= 1, a *= a) if(b & 1) res *= a;
    return res;
}
template <int P> struct mint{
// 一个 modint 的板子，无需在意
};
constexpr int P = 998244353;
using Z = mint<P>;

signed main(){
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    int N, M, K;
    std::cin >> N >> M >> K;

    std::vector<std::vector<Z> > qwq(N + 1, std::vector<Z>(M, 0)); // (x + 1) ^ i
    std::vector<std::vector<Z> > awa(N + 1, std::vector<Z>(M, 0)); // (x - 1) ^ i
    // O(NM) 预处理 G_i
    qwq[0][0] = awa[0][0] = 1;
    for(int i = 0;i < N;i++){
        for(int j = 0;j < M;j++){
            int nj = j + 1 == M ? 0 : j + 1;
            // 做一个循环卷积
            qwq[i + 1][j] += qwq[i][j];
            qwq[i + 1][nj] += qwq[i][j];
            awa[i + 1][j] += awa[i][j];
            awa[i + 1][nj] -= awa[i][j];
        }
    }
    std::vector<Z> g(N + 1, 0);
    for(int i = 0;i <= N;i++){
        for(int j = 0;j < M;j++){
            int nj = M - j == M ? 0 : M - j;
            g[i] += qwq[i][j] * awa[N - i][nj];
            // 为了保证是 M 的倍数，且加和为 N
        }
    }

    std::vector<int> A(N);
    for(int i = 0;i < N;i++){
        std::cin >> A[i];
    }
    constexpr int L = 20, V = 1 << 20;
    std::vector<std::array<int, 2> > dp(V, {0, 0});
    // 初始化 F
    for(int i = 0;i < N;i++){
        dp[A[i]][0] ++;
    }
    // 利用 FWT 的过程和性质求 F （最重要的一部分）
    for(int i = 1;i < V;i <<= 1){
        for(int j = 0;j < V;j += (i << 1)){
            for(int k = 0;k < i;k++){
                auto [a, b] = dp[j + k];
                auto [c, d] = dp[i + j + k];
                dp[j + k] = {a + c, b + d};
                dp[i + j + k] = {a + d, b + c};
            }
        }
    }
    // 让 H_i = G_{F_i}
    std::vector<Z> h(V, 0);
    for(int i = 0;i < V;i++){
        h[i] = g[dp[i][0]];
    }

    // IFWT (xor version)
    Z inv2 = Z(2).inv();
    for(int i = 1;i < V;i <<= 1){
        for(int j = 0;j < V;j += (i << 1)){
            for(int k = 0;k < i;k++){
                Z x = h[j + k];
                Z y = h[i + j + k];
                h[j + k] = (x + y) * inv2;
                h[i + j + k] = (x - y) * inv2;
            }
        }
    }

    // 最终求解
    Z ans = 0;
    for(int i = 0;i < V;i++){
        ans += h[i] * Pow(Z(i), K);
    }
    std::cout << ans.val() << endl;
    return 0;
}
```

---

## 作者：tobie (赞：0)

前置芝士：

记 $x\circ y = \mathrm{popcnt}(x \ \mathrm{and}\  y)\bmod 2$

$$[t^w] \mathrm{FWT}(A)=\sum_{i\circ w=0} A_i - \sum_{i\circ w=1} A_i$$

注意到值域不大，所以我们只需要求出对于所有情况，每个异或值出现的次数。

考虑占位多项式：

$$\prod(1+xt^{A_i})$$

其中 $x$ 的乘法为循环卷积，$t$ 的乘法为异或卷积

以 $t$ 为主元，那么 $t^w$ 位置存了一个 $m$ 次多项式，则 $w$ 位置上 $x$ 的零次项就是最终异或值为 $w$ 的方案数。

那么我们以 $t$ 为主元进行 $\mathrm{FWT}$ ，化简为

$$\mathrm{IFWT}\left(\prod \mathrm{FWT}(1+xt^{A_i}) \right )$$

其中求积符号改为对位相乘。

外面的 $\mathrm{IFWT}$ 可以最后处理，先扔掉。我们现在聚焦于 $t^w$ 的项，手玩一下，我们发现只有 $i$ 和 $0$ 会对答案产生贡献，于是我们得到一个重要结论：

$$[t^w]\mathrm{FWT}(1+xt^{A_i})=\left \{
\begin{matrix}
1+x & x\circ w=0\\
1-x & x\circ w=1\\
\end{matrix}
\right .$$

因为是对位相乘，所以我们可以发现

$$[t^w]\prod\mathrm{FWT}(1+xt^{A_i})=(1+x)^a(1-x)^b$$

所以我们如果能对于每一位计算出 $a,b$ 的值，那么可以 $O(nm)$ 预处理 $(1+x)^k$ 和 $(1-x)^k$，最后对于每一位，我们只在乎零次项，所以可以在 $O(m)$ 合并贡献。

我们注意到 $a+b=n$，根据定义有 $a=\sum [A_i\circ w=0],b=\sum[A_i\circ w=1]$，所以我们把输入的 $A$ 扔到一个桶 $B$ 中，对 $B$ 做异或 $\mathrm{FWT}$ 就可以得到每一位上 $a-b$ 的值。

最后用一次 $\mathrm{IFWT}$ 还原每个值的最终次数，统计答案即可。

时间复杂度 $O(mn+mV+V\log V)$

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
const int N=2e5+9,V=2e6+9,M=109,mod=998244353;
void fmt(int *a)
{
	int nn=(1<<20);
	for(int len=1;len*2<=nn;len<<=1)
	for(int i=0;i<nn;i+=len*2)
	for(int j=0;j<len;j++)
	{
		int p=a[i+j],q=a[i+j+len];
		a[i+j]=p+q,a[i+j+len]=p-q;//这里需要知道 a-b 的值，所以不取模
	}
}
void ifmt(int *a)
{
	int nn=(1<<20);
	for(int len=1;len*2<=nn;len<<=1)
	for(int i=0;i<nn;i+=len*2)
	for(int j=0;j<len;j++)
	{
		int p=a[i+j],q=a[i+j+len];
		a[i+j]=(p+q+mod)*499122177%mod,a[i+j+len]=(p-q+mod)*499122177%mod;
	}
}
int n,K,m,a[N];
int x1[N][M*2],x2[N][M*2];
int tj[V],f[V];
int ksm(int x,int y){int z=1;for(;y;x=x*x%mod,y>>=1) if(y&1) z=z*x%mod;return z;}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&K);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	x1[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=0;j--)
		x1[i][j]=((j>0?x1[i-1][j-1]:0)+x1[i-1][j])%mod;
		(x1[i][0]+=x1[i][m])%=mod;
		x1[i][m]=0;
	}
	x2[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=0;j--)
		x2[i][j]=((j>0?mod-x2[i-1][j-1]:0)+x2[i-1][j])%mod;
		(x2[i][0]+=x2[i][m])%=mod;
		x2[i][m]=0;
	}
	for(int i=1;i<=n;i++) tj[a[i]]++;
	fmt(tj);
	int nn=(1<<20),ans=0;
	for(int i=0;i<nn;i++)
	{
		int x=(n+tj[i])/2,y=(n-tj[i])/2;
		f[i]=x1[x][0]*x2[y][0]%mod;
		for(int j=0;j<m;j++) (f[i]+=x1[x][j]*x2[y][m-j]%mod)%=mod;
	}
	ifmt(f);
	for(int i=0;i<nn;i++) (ans+=f[i]*ksm(i,K)%mod)%=mod;
	printf("%lld\n",ans);
}
```

---

