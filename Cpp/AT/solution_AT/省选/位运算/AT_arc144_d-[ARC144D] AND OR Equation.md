# [ARC144D] AND OR Equation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc144/tasks/arc144_d

正整数 $ N,\ K $ が与えられます．整数列 $ \bigl(f(0),\ f(1),\ \ldots,\ f(2^N-1)\bigr) $ であって，以下の条件をすべて満たすものの個数を $ 998244353 $ で割った余りを答えてください．

- 任意の非負整数 $ x $ ($ 0\leq\ x\ \leq\ 2^N-1 $) に対して $ 0\leq\ f(x)\leq\ K $.
- 任意の非負整数 $ x,\ y $ ($ 0\leq\ x,\ y\ \leq\ 2^N-1 $) に対して $ f(x)\ +\ f(y)\ =\ f(x\ \,\mathrm{AND}\,\ y)\ +\ f(x\ \,\mathrm{OR}\,\ y) $.

ただし，$ \mathrm{AND} $, $ \mathrm{OR} $ はそれぞれビットごとの論理積，論理和を表します．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 3\times\ 10^5 $
- $ 1\leq\ K\leq\ 10^{18} $

### Sample Explanation 1

条件を満たす整数列は以下の $ 6 $ 個です． - $ (0,0,0,0) $ - $ (0,1,0,1) $ - $ (0,0,1,1) $ - $ (1,0,1,0) $ - $ (1,1,0,0) $ - $ (1,1,1,1) $

## 样例 #1

### 输入

```
2 1```

### 输出

```
6```

## 样例 #2

### 输入

```
2 2```

### 输出

```
19```

## 样例 #3

### 输入

```
100 123456789123456789```

### 输出

```
34663745```

# 题解

## 作者：Mirasycle (赞：10)

$$a_i+a_j=a_{i \operatorname{and} j} + a_{i\operatorname{or} j}$$
看到题目奇怪的二进制式子，第一眼似乎要用二进制运算找规律？其实不用，可以**思考式子的实际意义**，即为 $ A_{i}+A_{j}-A_{i \cap j}=A_{i \cup j}$。这样就是一个集合合并的式子啦。

我们可以构造 $p_{0 \sim i-1}$，令 $A_S =\sum\limits_{i \in S}p_i$，考虑还有哪些式子符合给出一个偏移量则 $a'_S=a_S+c$。

此时可以开始计数，利用题目约束条件可得，$\sum\limits_{p_i>0} p_i+c \le k$ 并且 $\sum\limits_{p_i<0}p_i+c \ge 0$。一个很显然的想法就是枚举 $c$ 然后统计方案。但是我们会发现枚举完 $c$ 之后是一个求和式子小于一个数不太好处理，需要枚举一个可能值再计算这样就麻烦了。那么我们可以转换一下思路，直接枚举求和式，然后 $c$ 单变量的方案数就很显然了。

于是直接枚举正数之和，负数之和以及为 $0$ 的情况，列出 $c$ 的范围是 $ [ -\sum\limits_{p_i<0}p_i,k-\sum\limits_{p_i>0}p_i]$。发现区间长度正好就是 $k+1-\sum\limits \lvert p_i \rvert$，这样又可以简化了,我们只需要枚举绝对值之和，不需要分开枚举了！

答案就是 

$$ \sum\limits_{i=0}^{ \min(n,k)} C^i_n \times 2^i \times \sum\limits_{j=i}^k (k+1-j) \times C^{i-1}_{j-1}= \sum\limits_{i=0}^{ \min(n,k)}C_n^i \times 2^i \times C_{k+1}^{i+1} $$

线性求解即可。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const long long mod=998244353;
const int maxn=3e5+10;
long long inv[maxn];
void init(int n){
	inv[0]=1; inv[1]=1;
	for(int i=2;i<=n+2;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
}
int main(){
	int n; long long k;
	cin>>n>>k; init(n);
	long long ans=(k+1)%mod,pow2=1,C1=1,C2=(k+1)%mod;//这里的C2别忘记取模 
	for(long long i=1;i<=(int)min((long long)n,k);i++){
		pow2=(pow2*2)%mod;
		C1=(C1*(n-i+1)%mod*inv[i])%mod;
		C2=(C2*inv[i+1]%mod*((k-i+1)%mod))%mod; 
		long long sum=pow2*C1%mod*C2%mod;
		ans=(ans+sum)%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_abcd_ (赞：7)

注意到对两个不同的 $2$ 的幂次 $i,j$，有 $a_{i} + a_{j} = a_0 + a_{i+j}$，即 $a_{i+j} = a_i + a_j - a_0$，进一步的，有 $a_{i+j+k} = a_{i+j} + a_k - a_0 = a_i + a_j + a_k - 2 a_0$，用归纳法可得 $a_k$ 为 $k$ 的所有二进制位对应的值相加再减去 $a_0$ 乘 $k$ 的二进制位中 $1$ 的个数减一，即
$$ a_k = \sum\limits_{2^i \text{ and } k \ne 0} a_{2^i} - (popcount(k)-1)a_0 $$

因此只需要确定 $a_0=m$ 和所有 $a_{2^k}$，就能确定整个序列。但是还有一个限制，即值域为 $[0,k]$，那么只要找到最小值和最大值，并保证这两个都在值域内。考虑将每个 $a_{2^i}$ 都减去 $m$，让后令 $b_i$ 为其中 $<0$ 的数取反，$c_i$ 为 $\ge 0$ 的数，那么需要保证
$$ b_1 + b_2 + \cdots + b_{n_1} \le m $$
$$ m + c_1 + c_2 + \cdots + c_{n_2} \le k $$

那么设
$$ x = m - (b_1 + \cdots + b_{n_1}), y = k - (m + c_1 + \cdots + c_{n_2}) $$

就有
$$ x + b_1 + \cdots + b_{n_1} + y + c_1 + \cdots + c_{n_2} = k $$

其中 $b$ 需要保证为正整数，其他都是保证为非负数，因此解的个数就是 $\binom{k+1+n_2}{n+1}$，答案就是 $\sum\limits_{i=0}^n \binom{n}{i} \binom{k+1+i}{n+1}$，枚举 $i$ 并实时维护组合数即可，复杂度 $O(n)$，注意判掉组合数为 $0$ 的情况。

---

### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mset(a,x) memset(a,x,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof a)
#define fls() fflush(stdout)
#define int ll
#define mod 998244353
#define maxn 300005
using namespace std;
int re()
{
    int x=0;
    bool t=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        t=ch=='-'?0:t,ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t?x:-x;
}
int ksm(int x,int y)
{
    int ret=1;
    while(y)
    {
        if(y&1)ret=ret*x%mod;
        x=x*x%mod,y>>=1;
    }
    return ret;
}
int n,m;
int jc[maxn],inv[maxn];
void zh_init()
{
    n++;
    jc[0]=1;
    for(int i=1;i<=n;i++)
        jc[i]=jc[i-1]*i%mod;
    inv[n]=ksm(jc[n],mod-2);
    for(int i=n;i;i--)
        inv[i-1]=inv[i]*i%mod;
    n--;
}
int A(int x,int y)
{
    if(x<y)return 0;
    return jc[x]*inv[x-y]%mod;
}
int C(int x,int y)
{
    return A(x,y)*inv[y]%mod;
}
signed main()
{
    n=re(),m=re()%mod;
    zh_init();
    int ans=0;
    int ss=inv[n+1];
    for(int i=0;i<n;i++)
        (ss*=max(n,m)-i)%=mod;
    for(int i=max(0ll,n-m);i<=n;i++)
    {
        (ss*=(m+i+1))%=mod;
        (ans+=C(n,i)*ss)%=mod;
        (ss*=ksm(m+i-n+1,mod-2))%=mod;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Caiest_Oier (赞：5)

# [AT_arc144_d](https://www.luogu.com.cn/problem/AT_arc144_d)     

考虑一个合法的序列应该满足什么条件。        

首先有一条性质：对于任意一个 $p$ 和 $i,j<2^p$，有：    

$$a_{i}+a_{j}=a_{i \cup j}+a_{i\cap j}$$
$$a_{i+2^p}+a_{j+2^p}=a_{i \cup j+2^p}+a_{i\cap j+2^p}$$
$$a_{i+2^p}+a_{j}=a_{i \cup j+2^p}+a_{i\cap j}$$
$$a_{i}+a_{j+2^p}=a_{i \cup j+2^p}+a_{i\cap j}$$    

前两个式子的和等于后两个式子的和，所以有：     

$$a_{i \cup j}+a_{i\cap j+2^p}=a_{i \cup j+2^p}+a_{i\cap j}$$     
$$a_{i \cap j+2^p}-a_{i\cap j}=a_{i \cup j+2^p}-a_{i\cup j}$$     

我们取 $i=2^p-1$，可以得到对于任意 $j$，$a_{j+2^p}-a_{j}$ 都为定值，这是一个序列合法的必要条件。     

于是我们得到一个合法序列的构造方法。如果当前已经构造出了 $[0,2^p-1]$ 的序列，则 $[2^p,2^{p+1}-1]$ 可以由 $[0,2^p-1]$ 全体加上某个值得到。容易发现这样构造的序列一定是合法的，因为任意在 $[0,2^{p+1}-1]$ 的两个值都可以缩小到 $[0,2^p-1]$ 的范围，于是这个条件充分。又因为这个条件是必要的，所以这个构造对应着所有序列。      

容易发现，这样的构造只有 $n$ 次平移的值是关键的。另外，有一个 $0\le a_i\le k$ 的限制。我们考虑当前构造了 $[0,2^p-1]$，序列最大值为 $r$，最小值为 $l$，则下一步平移要么保持不动，要么拓展 $[l,r]$ 的左端点，要么拓展 $[l,r]$ 的右端点。于是问题转化为求和所有的 $a_0=x$，从 $[x,x]$ 开始，操作 $n$ 次，左端点不小于 $0$，右端点不大于 $k$ 的方案数。接下来我们求解这个问题。       

我们考虑最终拓展的区间。令 $f(l,r,i)$ 表示区间 $[l,r],l\not =r$ 进行逆操作 $i$ 次后变为 $l=r$ 的方案数，则 $f(l,r,i)=\sum_{u=1}^{i}2^{u}C_{r-l-1}^{u-1}$，推导过程是，首先枚举有 $u$ 次区间发生了缩小，然后考虑长度的变化序列（此处长度为 $r-l$），最后为这每一次缩小钦定其是向右缩小还是向左缩小。      

于是答案可以通过枚举最终区间的长度计算，将 $len=0$ 的提出单独计算，式子为：     

$$(k+1)+\sum_{len=1}^{k+1}(k-len+1)\sum_{u=1}^{n}{C_{n}^{u}C_{len-1}^{u-1}\times 2^{u}}$$
$$=(k+1)+\sum_{u=1}^{n}C_{n}^{u}\times 2^{u}\sum_{len=1}^{k+1}(k-len+1){C_{len-1}^{u-1}}$$
$$=(k+1)+\sum_{u=1}^{n}C_{n}^{u}\times 2^{u}\sum_{ed=1}^{k}\sum_{p=1}^{ed}{C_{p-1}^{u-1}}$$
$$=(k+1)+\sum_{u=1}^{n}C_{n}^{u}\times 2^{u}\sum_{ed=1}^{k}{C_{ed}^{u}}$$
$$=(k+1)+\sum_{u=1}^{n}C_{n}^{u}\times 2^{u}\times C_{k+1}^{u+1}$$       

最后那个组合数用下降幂算，其它的正常计算即可，复杂度 $O(n)$。    

代码：      

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
int n,k,ans,jc[500003],njc[500003],k1,k2,k3,k4,k5,k6,k7,k8,k9;
int fstp(int X,int Y){
	int ret=1,bse=X;
	while(Y){
		if(Y&1)ret*=bse;
		bse*=bse;
		ret%=MOD;
		bse%=MOD;
		Y>>=1;
	}
	return ret;
}
int C(int X,int Y){
	if(X<0||Y<0||X<Y)return 0;
	return jc[X]*(njc[X-Y]*njc[Y]%MOD)%MOD;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	ans=(k+1);
	jc[0]=1;
	for(int i=1;i<=500000;i++)jc[i]=jc[i-1]*i%MOD;
	njc[500000]=fstp(jc[500000],MOD-2);
	for(int i=499999;i>=0;i--)njc[i]=njc[i+1]*(i+1)%MOD;
	k1=1;
	k2=(k+1)%MOD;
	for(int i=1;i<=n&&i<=k;i++){
		k1=k1*2ll%MOD;
		k2=k2*((k+1-i)%MOD)%MOD;
		ans=(ans+(C(n,i)*njc[i+1]%MOD)*(k1*k2%MOD))%MOD;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：wangziyue_AK (赞：3)

好题，写篇题解补充一下大部分题解没有提到的最后一步组合意义证明。
## 约束转化：
看到这个 $a_i+a_j=a_{i \land j}+a_{i\lor j}$ 和长度为 $2^n$ 容易想到转化为每个数为一个集合的二进制表示，那约束就表示了两集合的和减去并集等于交集，那么我们只要知道每个基本元素是什么即可确定序列，也就是序列由所有 $a_{2^i}$ 的取值决定，但 $a_0$ 这个空集也可能有值，也就是每个集合有一个基本权值，记为 $c$。现在每个 $a_S=c+\sum_{i \subseteq S} a_i$。
## 另一个限制：
我们还有一个限制 $0 \le a_i \le K$，可以视作最小值大于等于 $0$，最大值小于等于 $K$。考虑什么时候取到最大值或者最小值，一定是把包含所有正值的集合和包含所有负值的集合。那么限制转化为了 $0 \le c+\sum_{a_i<0} a_i$ 和 $c+\sum_{a_i>0} a_i\le K$。此时 $c$ 的取值范围为 $[-\sum_{a_i<0} a_i,K-\sum_{a_i>0}a_i]$，合法 $c$ 的个数为 $K-\sum_{a_i>0} a_i - (- \sum_{a_i<0} a_i)+1$ 也就是 $K-(\sum|a_i|)+1$。
## 推式子：
考虑先枚举有哪几个非零值，每个非零值有两种取法（正负）。再枚举 $\sum|a_i|$，然后就是把这些值给分进非空集合，插板法即可。
$$ans=\sum_{i=0}^{n}\binom{n}{i}2^i\sum_{j=1}^{K}\binom{j-1}{i-1}(K-j+1)$$

这个式子直接做是 $O(nK)$ 的，所以我们要想办法解决 $O(K)$ 的第二重枚举。先给出结论:
$$\sum_{j=1}^{K}\binom{j-1}{i-1}(K-j+1)=\binom{K+1}{i+1}$$

考虑组合意义证明：从 $K+1$ 个数中选 $i+1$ 个数，枚举倒数第二个选的数的位置，在它前面要选 $i-1$ 个数，它后面要选一个数。
但是组合意义只能用来证明或者帮助理解，那该怎么直接退出这个式子呢？考虑把式子换一个形式：
$\sum_{j=0}^{K} \sum_{k=0}^{j-1}\binom{k}{i-1}$，使用一次列求和恒等式（$\sum_{i=0}^{n}\binom{i}{m}=\binom{n+1}{m+1}$）可以得到原式等于 $\sum_{j=0}^{i}\binom{j}{i}$，再用一次即可得到原式等于 $\binom{K+1}{i+1}$，证毕。
## 最终答案：
$ans=\sum_{i=0}^n 2^i\binom{n}{i}\binom{K+1}{i+1}$

---

## 作者：User_Unauthorized (赞：2)

首先我们可以转化题目限制，设 $U = \left\{1, 2, 3, \cdots, N\right\}$，那么题目限制实际上为：

> 对于任意集合 $S, T \subseteq U$，满足 $f(S) + f(T) = f(S \cap T) + f(S \cup T)$。

考虑设 $c = f(\varnothing), x_i = f(\left\{i\right\}) - c$。

我们不难发现，一个多元组 $\left(c, x_1, x_2, \cdots, x_N\right)$ 与 $f$ 一一对应。具体的，取 $f(S) = c + \sum\limits_{i \in S} x_i$ 即可。

因此我们对合法的多元组计数即可。

考虑多元组合法的充要条件，即为：

$$\forall S \subseteq U \rightarrow 0 \le c + \sum\limits_{i \in S} x_i \le K$$

设 $s^{-} = \sum\limits_{i = 1}^{N} \left[x_i < 0\right] x_i, s^{+} = \sum\limits_{i = 1}^{N} \left[x_i > 0\right] x_i$，那么我们有：

$$\forall S \subseteq U \rightarrow s^{-} \le \sum\limits_{i \in S} x_i \le S^{+}$$

因此上述条件可以改写为：

$$\begin{aligned}
0 &\le c + s^{-} \\
c + s^{+} &\le K
\end{aligned}$$

即

$$-s^{-} \le c \le K - s^{+}$$

因此若 $s^{-}$ 和 $s^{+}$ 确定，那么 $c$ 的取值有 $\max\limits\left\{0, K + 1 - s^{+} + s^{-}\right\}$ 种。考虑到 $\sum\limits_{i = 1}^{N} \left\lvert x_i \right\rvert = s^{+} - s^{-}$，那么 $c$ 的取值种数可以表达为 $\max\limits\left\{0, K + 1 - \sum\limits_{i = 1}^{N} \left\lvert x_i \right\rvert\right\}$。

那么我们现在的问题转化为了对于所有满足 $\sum\limits_{i = 1}^{N} \left\lvert x_i \right\rvert \le K$ 的序列 $x$，求出 $K + 1 - \sum\limits_{i = 1}^{N} \left\lvert x_i \right\rvert$ 的和。

首先考虑处理掉绝对值。不妨枚举序列中的非 $0$ 数个数 $n$，后枚举其正负性，这部分的方案数为：

$$\dbinom{N}{n} 2^n$$

进而我们的问题就转化为了对于所有长度为 $n$ 的**正整数**序列 $y$，要求 $\sum\limits_{i = 1}^{n} y_i \le K$，设 $s = \sum\limits_{\sum\limits_{i = 1}^{n} y_i}$，求 $K + 1 - s$ 的和。即 $g(n, s)$ 表示长度为 $n$ 且和为 $s$ 的正整数序列数量，那么我们要求的实际上为：

$$\begin{aligned}
&\sum\limits_{s = 1}^{K} g(n, s) \times \left(K + 1 - s\right) \\
=&\sum\limits_{s = 1}^{K} g(n, s) \sum\limits_{a = 1}^{K + 1 - s} 1 \\
\end{aligned}$$

考虑枚举 $a + s$ 的和 $s_a$，那么我们实际上要求的为：

$$\begin{aligned}
&\sum\limits_{s_a = 1}^{K + 1} g(n + 1, s_a)
\end{aligned}$$

设 $b = K + 2 - s_a$，那么我们有 $b \ge 1$，同时我们有 $s + a + b = K + 2$，发现确定了 $b$ 的取值即可确定出 $s_a$ 的取值。因此我们将 $b$ 拼入序列中是正确的。因此我们要求的为 $g(n + 2, K + 2)$。根据插板法，我们有：

$$g(n, m) = \dbinom{m - 1}{n - 1}$$

因此答案为：

$$\sum\limits_{n = 0}^{N} 2^n \dbinom{N}{n} \dbinom{K + 1}{n + 1}$$

将组合数转化为下降幂即可 $\mathcal{O}(N)$ 计算。

---

## 作者：Register_int (赞：2)

神秘东西。

先考虑到条件限制相当于 $a_S+a_T=a_{S\cap T}+a_{S\cup T}$，直接令 $|S|=|T|=1$ 就能得到，$S$ 中每一位对应的数是固定的，再加上一个 $a_0$ 可以得到 $a_S=a_0+\sum_{y\in S}y$。

接下来计数。有了值域限制后，如果我们确定了 $S$ 中的数，那么 $a_0$ 能取到的区间就是 $\left[-\sum_{y<0}y,k-\sum_{y>0}y\right]$，方案数恰好为 $k+1-\sum_{y\in S}|y|$。由于绝对值，每个不为 $0$ 的 $y$ 都可以有两种取值，所以枚举 $y\not=0$ 的个数以及 $\sum_{y\in S}|y|$，答案为：

$$
\begin{aligned}
&\sum^n_i\dbinom ni2^i\sum^k_{j=i}(k-j+1)\dbinom{j-1}{i-1}\\
=&\sum^n_i\dbinom ni2^i\left((k+1)\sum^k_{j=i}\dbinom{j-1}{i-1}-\sum^k_{j=i}j\dbinom{j-1}{i-1}\right)\\
=&\sum^n_i\dbinom ni2^i\left((k+1)\sum^k_{j=i}\dbinom{j-1}{i-1}-i\sum^k_{j=i}\dbinom ji\right)\\
=&\sum^n_i\dbinom ni2^i\left((k+1)\dbinom ki-i\dbinom{k+1}{i+1}\right)\\
=&\sum^n_i\dbinom ni2^i\left((i+1)\dbinom{k+1}{i+1}-i\dbinom{k+1}{i+1}\right)\\
=&\sum^n_i\dbinom ni\dbinom{k+1}{i+1}2^i\\
\end{aligned}
$$

容易发现这两个组合数都可以直接递推，时间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 10;
const int mod = 998244353;

int n; ll k, x, ans, inv[MAXN];

int main() {
	scanf("%d%lld", &n, &k), inv[1] = 1, x = (k + 1) % mod;
	for (int i = 2; i <= n + 1; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 0; i <= n; i++) {
		ans = (ans + x) % mod;
		x = x * inv[i + 1] % mod * (n - i) % mod * inv[i + 2] % mod * ((k - i) % mod) * 2 % mod;
	}
	printf("%lld", ans);
}
```

---

## 作者：do_it_tomorrow (赞：1)

另类做法，大佬轻喷。

设 $x< 2^i$，那么由题可以得到：

$$f(x)+f(2^{i})=f(0)+f(2^{i}+x)$$

进而可以得到：

$$f(2^{i}+x)=f(x)+f(2^{i})-f(0)$$

设 $y=2^{i}+x$，那么有：

$$f(y)=f(y-2^{i})+f(2^{i})-f(0)$$

容易发现 $y$ 的最高位是第 $i$ 位的时候满足上式。

那么容易理解，只需要 $f(0)$ 和所有的 $f(2^x)$ 确定下来，那么 $f$ 就整个确定了。

设 $g(i)=f(2^i)-f(0)$，那么：

$$f(x)=f(0)+\sum\limits_{2^i\&x\ne 0} g(i)$$
假设 $g$ 已经确定，考虑合法的 $f(0)$ 的数量。

假设 $s1=\sum\limits_{i=0}^{n-1}\max(g(i),0)$，$s2=\sum\limits_{i=0}^{n-1}\min(g(i),0)$。

因为 $0\le f(x)\le k$，所以必然有：

$$\left\{\begin{matrix}f(0)+s1\le k \\f(0)+s2\ge 0\end{matrix}\right.$$

所以解的个数为 $k-s1+s2+1$。

然而因为 $s1-s2=\sum\limits_{i=0}^{n-1} \lvert g(i)\rvert$，所以方案数为：

$$k+1-\sum\limits_{i=0}^{n-1} \lvert g(i)\rvert$$

设 $x=\sum\limits_{i=0}^{n-1} \lvert g(i)\rvert$，$s(x)$ 表示 $x=\sum\limits_{i=0}^{n-1} \lvert g(i)\rvert$ 时 $g$ 的方案数。

那么有：

$$s(x)=[x=0]+\sum\limits_{i=1}^n 2^i\times{x-1\choose i-1}\times {n\choose i}$$

枚举 $0$ 的个数，符号可以乱填，最后把 $x$ 的和分配到 $i$ 个数上要求非空。

所以答案就是：

$$\sum\limits_{x=0}^k(k+1-x)\times s(x)$$

化简：

$$\sum\limits_{x=0}^k s(x)=1+\sum\limits_{i=1}^n 2^i\times{n\choose i}(\sum\limits_{j=i-1}^{k-1}{j-1\choose i-1})$$

后面似乎是 [朱世杰恒等式](https://en.wikipedia.org/wiki/Hockey-stick_identity) ，所以得到：

$$1+\sum\limits_{i=1}^n 2^i\times{n\choose i}\times {k\choose i}$$

另外一个式子：

$$\sum\limits_{x=0}^k x\times s(x)=\sum\limits_{x=0}^k\sum\limits_{i=1}^{n}2^i\times{n\choose i}\times{x\choose i}\times i$$

那么同样的可以得到：

$$\sum\limits_{i=1}^n2^i\times{n\choose i}\times i\times {k+1\choose i+1}$$

所以：

$$Ans=(k+1)\times (1+\sum\limits_{i=1}^n 2^i\times{n\choose i}\times {k\choose i})-\sum\limits_{i=1}^n2^i\times{n\choose i}\times i\times {k+1\choose i+1}$$

时间复杂度为 $O(n)$。

```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=3e5+5,mod=998244353;
int n,k,jc[N],inv[N],f[N];
int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod,b>>=1;
    }
    return ans;
}
void init(int n){
    jc[0]=1;
    for(int i=1;i<=n;i++){
        jc[i]=jc[i-1]*i%mod;
    }
    inv[n]=ksm(jc[n]);
    for(int i=n-1;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%mod;
    }
    f[1]=k;
    for(int i=2;i<N;i++){
        f[i]=f[i-1]*(k-i+1)%mod;
    }
}
int C(int n,int m){
    if(n<m||n<0||m<0) return 0;
    return jc[n]*inv[m]%mod*inv[n-m]%mod;
}
int C1(int x){
    return f[x]*inv[x]%mod;
}
int C2(int x){
    return f[x-1]*(k+1)%mod*inv[x]%mod;
}
int f1(){
    int ans=0;
    for(int i=1,p=2;i<=n;i++,p=p*2%mod){
        ans=(ans+p*C1(i)%mod*C(n,i))%mod;
    }
    return ans+1;
}
int s(int x){
    int ans=!x;
    for(int i=1;i<=n;i++){
        ans=(ans+ksm(2,i)*C(x-1,i-1)*C(n,i))%mod;
    }
    return ans;
}
int f2(){
    int ans=0;
    for(int i=1,p=2;i<=n;i++,p=p*2%mod){
        ans=(ans+p*C(n,i)%mod*i%mod*C2(i+1))%mod;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k,k%=mod;
    init(N-1);
    int ans=0;
    cout<<((k+1)*f1()-f2()+mod)%mod<<'\n';
    return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

感觉整个题从头到尾就透露出一种很神秘的气息，感觉啥也没干，但是啥都干了，然后题就做完了。结论非常简单，所以稍微写一下自己的思考路径。

考虑从边界情况开始研究 $a_i+a_j=a_{i\operatorname{or} j}+a_{i\operatorname{and} j}$ 这个条件：比如 $i \operatorname{and} j=0$ 的情况，这时候 $a_i+a_j=a_{i+j}+a_0$。很容易看出 $a_0$ 十分关键，因为无论 $i,j$ 的取值都会出现这一项。

再边界一点的边界情况？如果 $i=2^x,j=2^y,x\neq y$，那么 $a_{i+j}=a_{i}+a_{j}-a_0$，也就是对于一个 popcount 为 $2$ 的数，他的 $a$ 值就等于他两个位拿出来对应的 $a$ 值减去 $a_0$。

三位呢？设 $i=2^x,j=2^y,j,k=2^z$，$x,y,z$ 互不相同，那么 $a_{i+j+k}=a_{i}+a_{j}+a_{k}-2a_0$。至此结论已经很明显了：对于集合 $S$，$a_S=\sum\limits_{x\in S}a_{\{x\}}-(|S|-1)a_0$。容易归纳证明这是合法且唯一的。把这个 $(|S|-1)a_0$ 均摊到每个元素上，也就是每多选一个元素权值就 $-a_0$，最后加上 $a_0$。

接下来考虑一下怎么计数。我们设序列 $b_{0},b_{1},\dots b_{n}$，对应原序列中的 $a_0,a_1,\dots a_{2^{n-1}}$。做法是枚举可能的 $b_1,\dots b_n$，计算出合法的 $b_0$ 的数量。

回顾一下条件：$0\le a_i\le K$，也就是说，$\forall S\subseteq [n],b_0+\sum\limits_{x\in S}(b_x-b_0)\in [0,K]$。容易发现我们只需要考虑最小和最大的子集和，也就是选出所有 $b_x-b_0<0$ 的 $x$ 和 $b_x-b_0>0$ 的 $x$ 的两种情况。

设 $b_x-b_0$ 中所有负数的和为 $s_1$，所有正数的和为 $s_2$，那么合法的 $b_0$ 需要满足 $b_0 \in [-s_1,K-s_2]$，方案数为 $K-s_2+s_1+1$。发现这实际上就是 $K-\sum\limits_{i=1}^{n}|b_i-b_0|+1$。

这样就可以开始计数了：先假定所有 $b_i-b_0$ 都是非负的，限制这些数的和，再给每个数赋上符号。枚举有 $i$ 个 $b_x-b_0\neq 0$（这些位置的符号是有本质区别的），所有绝对值之和 $=s$。可以得到答案的表达式：

$$\sum\limits_{i=0}^{n}\sum\limits_{s=i}^{K}\binom{n}{i}2^i\binom{s-1}{i-1}(K-s+1)$$

$\binom{n}{i}$ 就是选出这些一些数非零，$2^i$ 就是这 $i$ 个数的符号，$\binom{s-1}{i-1}$ 是一个插板法，算分配总和的方案数，$K-s+1$ 是 $b_0$ 的方案数。

接下来的化简就非常套路了：把最后的括号里的常数项和关于 $s$ 的项拆开：

$$=\sum\limits_{i=0}^{n}\binom{n}{i}2^i\sum\limits_{s=i}^{K}((K+1)\binom{s-1}{i-1}-s\binom{s-1}{i-1})$$

前面那部分是个经典的组合恒等式，后半部分运用吸收恒等式之后也是同样的推法：

$$=\sum\limits_{i=0}^{n}\binom{n}{i}2^i\sum\limits_{s=i}^{K}((K+1)\binom{s-1}{i-1}-i\binom{s}{i})$$

$$=\sum\limits_{i=0}^{n}\binom{n}{i}2^i((K+1)\binom{K}{i}-i\binom{K+1}{i+1})$$

到这里就已经可以 $\mathcal O(n)$ 计算了。如果要进一步得到更简洁的式子，可以对前面那个组合数再用一次吸收恒等式，得到：

$$=\sum\limits_{i=0}^{n}\binom{n}{i}2^i\binom{K+1}{i+1}$$

时间复杂度 $\mathcal O(n)$。


```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e6+9,Mod=998244353;
ll n,K;
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%Mod;
        x=x*x%Mod,p>>=1;
    }
    return res;
}
ll fac[N],ifac[N],c1[N],c2[N],pw2[N];
ll C(ll x,ll y){
    if(x<y||y<0)return 0;
    return fac[x]*ifac[y]%Mod*ifac[x-y]%Mod;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),K=read();
    pw2[0]=1;
    rep(i,1,n+1)pw2[i]=pw2[i-1]*2%Mod;
    fac[0]=1;
    rep(i,1,n+1)fac[i]=fac[i-1]*i%Mod;
    ifac[n+1]=pw(fac[n+1],Mod-2);
    per(i,n,0)ifac[i]=ifac[i+1]*(i+1)%Mod;
    c1[0]=c2[0]=1;
    rep(i,1,n+1)c1[i]=c1[i-1]*((K-i+1)%Mod)%Mod;
    rep(i,1,n+1)c2[i]=c2[i-1]*((K-i+2)%Mod)%Mod;
    ll ans=0;
    rep(i,0,n){
        ll coef=(c1[i]*((K+1)%Mod)%Mod*ifac[i]+(Mod-i)*c2[i+1]%Mod*ifac[i+1])%Mod;
        ans=(ans+coef*pw2[i]%Mod*C(n,i))%Mod;
    }
    write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：Sampson_YW (赞：1)

考虑对于一个二进制位 $i$，对于 $x<2^i$ 让 $x\leftarrow x+2^i$ 会发生什么事。

$a_{x}+a_{2^i}=a_{0}+a_{x+2^i}$，那么 $a_{x+2^i}=a_{x}+(a_{2^i}-a_0)$。

设 $b_{i}=a_{2^i}-a_0$，设 $S_{x}$ 为 $x$ 在二进制下为 $1$ 的位的集合，容易发现 $a_{x}=a_0+\sum_{i\in S_x}b_i$。那么只要确定 $a_0$ 和 $b$ 序列，整个序列 $a$ 就固定了。

但是这个序列还要满足值域的限制，$\forall a_x\in[0,k]$。也就是说，我们要让 $\min a_x\ge 0$，$\max a_x\leq k$。

将 $b$ 中的数分为 $\leq 0$ 和 $>0$ 两类。对于 $\leq 0$ 的数，这些数的和的绝对值 $\leq a_0$。对于 $>0$ 的数，这些数的和 $\leq k-a_0$。

枚举 $\leq 0$ 的数有 $t$ 个，枚举 $a_0$，由插板法可以得到答案（为了美观将 $a_0$ 写成 $a$）

$$
\sum_{t=0}^n\binom{n}{t}\sum_{a=0}^k\binom{a+(t+1)-1}{(t+1)-1}\binom{(k-a+1)-1}{(n-t+1)-1}
$$

后面那部分为 $\sum_a\binom{a+t}{t}\binom{k-a}{n-t}$，利用插板法考虑其组合意义：前面的组合数是 $t+1+a$ 个球分到 $t+1$ 组里（非空），后面的组合数是 $k-a+1$ 个球分到 $n-t+1$ 组里（非空）。

可能组合意义不太明显。可以将 $a\leftarrow a+t$，那么就是将 $a+1$ 个球分到 $t+1$ 组里（非空），将 $k+t-a+1$ 个球分到 $n-t+1$ 组里。这时组合意义就很明显了，枚举的 $a$ 实际上可以看作枚举前 $t+1$ 组一共用了多少个球，对所有的 $a$ 求和就相当于，将 $k+t+2$ 个球分到 $n+2$ 组里（非空）。那么这个式子就变成了 $\binom{k+t+1}{n+1}$。

于是只需要求 $\sum_{t}\binom{n}{t}\binom{k+t+1}{n+1}$，后面这个组合数需要滑动窗口求下降幂，注意判区间中包含模数的倍数的情况。

[code](https://atcoder.jp/contests/arc144/submissions/48160248)

---

## 作者：LiveZoom (赞：1)

## Description

[link](https://www.luogu.com.cn/problem/AT_arc144_d)

## Solution

由于二进制可以等价于一个集合，所以可以把 $f$ 看作一个有关集合的函数。

设 $f(\emptyset)=c$，$f(\{i\})=A_i$。当 $s=\{b_1,b_2,...,b_k\}$ 与 $\{b_{k+1}\}$ 不相交，那么 $f(\{b_1,b_1,...,b_{k+1}\})+f(\emptyset)=f(s)+f(\{b_{k+1}\})$。

所以 $f(\{b_1,b_2,...,b_{k+1}\})=\sum_{i=1}^{k+1}{A_{b_i}})-ck$。

设 $x_i=A_i-k$，那么 $f(s)=\sum_{i\in s}{x_i}-k$。

那么 $0\leq a_i\leq k$ 这个条件就等价于所有 $f$ 函数值 $\in [0,k]$，假设 $X$ 是所有  $x_i$ 中负数的和，$Y$ 是正数的和。

那么 $X+c\geq 0,Y+c\leq k$，所以 $c\in [-X,k-Y]$，$c$ 就有 $\max\{k+1-Y+X,0\}$ 种取值，注意到 $X-Y$ 是 $\sum{|x_i|}$，所以只需要决定 $x$  的绝对值之和即可。

---

考虑枚举绝对值不为 $0$ 的元素个数，设有 $i$ 个。

选出这 $i$ 个数有 $C_{n}^{i}$ 种，正负有 $2^{i}$ 种，内部的方案数有 $\sum\limits_{s=n}^{k+1}{C_{s-1}^{n-1}\cdot s}$。

把最后那个式子化简一下：
$$
\begin{aligned}
&\sum_{s=n}^{k+1}{C_{s-1}^{i-1}\cdot s}\\
=&(k+1)\sum_{s=i-1}^{k}{C_{s}^{i-1}}-\sum_{s=i}^{k+1}{C_{s-1}^{i-1}\cdot s}\\
=&(k+1)\cdot C_{k+1}^{i}-\sum_{s=i}^{k+1}{i\cdot C_{s}^{i}}\\
=&(k+1)\cdot C_{k+1}^{i}-i\cdot C_{k+2}^{i+1}\\
=&\dfrac{(k+1)!\cdot (k+1)}{i!\cdot (k+1-i)!}-\dfrac{(k+2)!\cdot i}{(i+1)!\cdot (k+1-i)!}\\
=&\dfrac{(i+1)\cdot (k+1)\cdot (k+1)!-i\cdot (k+2)!}{(i+1)!\cdot (k-i+1)!}\\
=&\dfrac{(k+1)!\cdot (k-i+1)}{(i+1)!\cdot (k-i+1)!}\\
=&\dfrac{(k+1)!}{(i+1)!\cdot (k-i)!}\\
=&C_{k+1}^{i+1}
\end{aligned}
$$


所以答案就是 $\sum_{i=0}^{n}{2^i C_{n}^{i}C_{k+1}^{i+1}}$。

时间复杂度：$O(n)$。

## Code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int kMaxN = 3e5 + 5, kMod = 998244353;

int n, k;
int fac[kMaxN], ifac[kMaxN], inv[kMaxN], pw[kMaxN];

int C(int m, int n) {
  return 1ll * fac[m] * ifac[n] % kMod * ifac[m - n] % kMod;
}

signed main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> k;
  fac[0] = ifac[0] = fac[1] = ifac[1] = inv[1] = 1;
  pw[0] = 1, pw[1] = 2;
  for (int i = 2; i <= n + 1; ++i) {
    inv[i] = (-1ll * (kMod / i) * inv[kMod % i] % kMod + kMod) % kMod;
    fac[i] = 1ll * fac[i - 1] * i % kMod;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % kMod;
    pw[i] = 2ll * pw[i - 1] % kMod;
  }
  k %= kMod;
  int ans = 0, now = k + 1;
  for (int i = 0; i <= n; ++i) {
    ans = (ans + 1ll * now * ifac[i + 1] % kMod * pw[i] % kMod * C(n, i) % kMod) % kMod;
    now = 1ll * now * ((k - i) % kMod + kMod) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
```



---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc144_d)

**题目大意**

> 给定 $n,k$，求有多少序列 $a_{0}\sim a_{2^n-1}$ 满足值域 $[1,k]$ 且对于所有 $i,j$ 都有：$a_i+a_j=a_{i\operatorname{AND}j}+a_{i\operatorname{OR}j}$。
>
> 数据范围：$n\le 3\times 10^5,k\le 10^{18}$。

**思路分析**

考虑逐位构造，考虑从 $a_{0}\sim a_{2^d-1}$ 推出 $a_0\sim a_{2^{d+1}-1}$。

对于 $i,j<2^d$，我们知道 $a_i+a_{j+d}=a_{i\operatorname{AND}j}+a_{(i\operatorname{OR}j)+d}=a_{i+d}+a_j$ 。

因此 $a_{i+d}-a_{j+d}=a_i-a_j$，即 $a_{2^d}\sim a_{2^{d+1}-1}$ 与 $a_{0}\sim a_{2^d-1}$ 是“相似”的，即差分相同。

那么可以考虑 dp，$f_{d,x}$ 表示当前序列长度 $2^d$，序列极差为 $x$，考虑每次转移时值域的扩张量：$f_{d+1,x+i}\gets f_{d,x}+(1+[i>0])$。

我们要从 $f_{0,0}=1$ 出发，求出 $\sum f_{n,i}(k-i+1)$，枚举 $j$ 表示转移过程中恰好有 $j$ 个时刻增加量 $>0$，得到：
$$
\mathrm{Answer}=\sum_{i=0}^k(k-i+1)\sum_{j=0}^{\min(n,i)}\binom nj2^j\binom{i-1}{j-1}
$$
根据组合恒等式能得到答案为 $\sum_{j=0}^n2^j\binom nj\binom{k+1}{j+1}$，维护 $(k+1)^{\underline{j+1}}$ 即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5,MOD=998244353;
ll inv[MAXN];
signed main() {
	int n; ll k;
	scanf("%d%lld",&n,&k),k%=MOD,inv[1]=1;
	for(int i=2;i<=n+2;++i) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	ll p=k+1,ans=0,C=1,w=1,f=1;
	for(int i=0;i<=n;++i) {
		ans=(ans+w*p%MOD*f%MOD*C)%MOD;
		p=p*(k-i)%MOD,C=C*(n-i)%MOD*inv[i+1]%MOD,w=w*2%MOD,f=f*inv[i+2]%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：0x3F (赞：0)

首先注意到一点：只有 $a_0$ 和 $a_{2^k}(0\le k<n)$ 是有用的，对于 $0\le m<2^n$ 的任意下标 $m$，若 $m=2^{k_1}+2^{k_2}+\cdots+2^{k_t}$，则 $a_m=a_0+\sum(a_{2^{k_i}}-a_0)$，归纳法易证。

此时，我们需要所有 $a$ 的最大值 $\le k$，最小值 $\ge 0$。记 $M=a_0$，$\Delta_i=a_{2^{k}}-a_0(0\le k<n)$，则需要 $\sum\max(\Delta_i,0)\le k-M$ 且 $\sum\max(-\Delta_i,0)\le M$。

使用生成函数。记 $\Delta_i>0$ 为 $x^{\Delta_i}$，$\Delta_i<0$ 为 $y^{-\Delta_i}$，$\Delta_i=0$ 为 $1$。

此时，单个 $i$ 的所有选择构成的生成函数为 $1+x+x^2+\cdots+y+y^2+\cdots=1+\frac{x}{1-x}+\frac{y}{1-y}$。

我们要求 $x$ 的次数不超过 $k-M$，$y$ 的次数不超过 $M$，则方案数为 $\sum_{i=0}^{k-M}\sum_{j=0}^{M}[x^iy^j](1+\frac{x}{1-x}+\frac{y}{1-y})^n$ 即 $[x^{k-M}y^{M}]\frac{1}{1-x}\frac{1}{1-y}(1+\frac{x}{1-x}+\frac{y}{1-y})^n$。

因此，对所有 $M$，答案之和为 $\sum_{M=0}^{k}[x^{k-M}y^{M}]\frac{1}{1-x}\frac{1}{1-y}(1+\frac{x}{1-x}+\frac{y}{1-y})^n$。

我们发现若令 $y=x$，则原本的所有 $x^{k-M}y^{M}$ 项均对应新的 $x^k$ 项。

因此答案为 $[x^k]\frac{(1+x)^n}{(1-x)^{n+2}}$。

直接展开，得到 $\sum\binom{n}{i}\binom{k-i+n+1}{n+1}$，直接算就行了，注意存在有的项是 $p$ 的倍数，需要处理一下。

时间复杂度为 $\mathcal{O}(n\log p)$，精细实现可以做到 $\mathcal{O}(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int p = 998244353;
int qpow(int a, int b) {
	int s = 1;
	while (b) {
		if (b & 1) s = (long long) s * a % p;
		a = (long long) a * a % p;
		(b >>= 1);
	}
	return s;
}
struct node {
	int num;
	int pow;
};
node calc(long long x) {
	int cnt = 0;
	while (!(x % p)) {
		x /= p;
		cnt++;
	}
	return ((node){x%p, cnt});
}
node mul(node a, node b) {
	return ((node){(long long) a.num * b.num % p, a.pow + b.pow});
}
node div(node a, node b) {
	return ((node){(long long) a.num * qpow(b.num, p - 2) % p, a.pow - b.pow});
}
int rev(node a) {
	return ((a.pow) ? (0) : (a.num));
}
int n, ans;
long long k;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	node tmp = calc(1LL);
	for (int i = 1; i <= n+1; i++) {
		tmp = mul(tmp, calc(k+i));
	}
	for (int i = 1; i <= n+1; i++) {
		tmp = div(tmp, calc(i));
	}
	ans = (ans + rev(tmp)) % p;
	for (int i = 1; i <= n && i <= k; i++) {
		tmp = mul(tmp, calc(k+1-i));
		tmp = mul(tmp, calc(n-i+1));
		tmp = div(tmp, calc(n+k+2-i));
		tmp = div(tmp, calc(i));
		ans = (ans + rev(tmp)) % p;
	}
	cout << ans << endl;
}
```

---

## 作者：Feyn (赞：0)

[更多的 ARC 题目](https://www.cnblogs.com/Feyn/p/16977678.html)

猜想合法的形式应该是存在一个大小为 $n$ 的数列 $p$，满足 $a_S=p_0+\sum\limits_{i\in S}p_i$。然而 $p$ 有正有负，把其按照正负性分类，而题目中的限制就变成了负的那些（可以认为是最负的那个集合）不小于零，最大的那个也不应该大于 $k$。然而方案似乎并没有那么好计算。

考虑切换枚举对象。思考每个 $p$ 对应的 $p_0$ 的取值范围，发现其就等于 $k-\sum|p_i|$，而每个 $p_i\ne 0$ 都有两个取值。于是显然想到枚举非零的个数 $n$，可以得到下面的柿子：

$$
\text{ans}=\sum\limits_{0\le n\le m}\binom{m}{n}2^n\sum\limits_{s=n}^{k}(k-s+1)\binom{s-1}{n-1}
$$

右边是个上指标求和的形式。具体地：

$$
\begin{aligned}
&\sum\limits_{s=n}^{k}(k+1)\binom{s-1}{n-1}-\sum\limits_{s=n}^k\binom{s-1}{n-1}s\\
=&(k+1)\binom{k}{n}-\sum\limits_{s=n}^kn\binom{s}{n}\\
=&(k+1)\dfrac{n+1}{k+1}\binom{k}{n}-n\binom{k+1}{n+1}\\
=&\binom{k+1}{n+1}
\end{aligned}
$$

然后就没啦。组合数可以递推，所以总体复杂度可以是线性的，我的代码带了个 $\log$ 但无伤大雅。然后就是这道题的代码真的很短，甚至不用开数组。

```cpp
#include<cstdio>
#define int long long

int m,k,ans,M=998244353;
int qp(int s1,int s2){
    int an=1;
    while(s2)(s2&1)&&(an=an*s1%M),s1=s1*s1%M,s2>>=1;
    return an;
}

signed main(){

    scanf("%lld%lld",&m,&k);
    int a=1,c=1,b=(k+1)%M;ans=k+1;
    for(int n=1;n<=m&&n<=k;n++){
        a=a*(m-n+1)%M;a=a*qp(n,M-2)%M;c=c*2%M;
        b=(k+1-n)%M*b%M;b=b*qp(n+1,M-2)%M;
        ans+=a*c%M*b%M;
    }
    printf("%lld\n",(ans%M+M)%M);

    return 0;
}
```

---

