# [ABC276G] Count Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc276/tasks/abc276_g

以下の条件を満たす項数 $ N $ の整数列 $ A=(a_1,a_2,\ldots,a_N) $ の個数を $ 998244353 $ で割った余りを求めてください。

- $ 0\ \leq\ a_1\ \leq\ a_2\ \leq\ \ldots\ \leq\ a_N\ \leq\ M $
- $ i=1,2,\ldots,N-1 $ それぞれについて、「$ a_i $ を $ 3 $ で割った余り」と「$ a_{i+1} $ を $ 3 $ で割った余り」が異なる

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^7 $
- $ 1\ \leq\ M\ \leq\ 10^7 $
- 入力はすべて整数

### Sample Explanation 1

以下の $ 8 $ 個が条件を満たします。 - $ (0,1,2) $ - $ (0,1,3) $ - $ (0,2,3) $ - $ (0,2,4) $ - $ (1,2,3) $ - $ (1,2,4) $ - $ (1,3,4) $ - $ (2,3,4) $

### Sample Explanation 2

個数を $ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
3 4```

### 输出

```
8```

## 样例 #2

### 输入

```
276 10000000```

### 输出

```
909213205```

# 题解

## 作者：Un1quAIoid (赞：10)

**传送门：** [G - Count Sequences](https://atcoder.jp/contests/abc276/tasks/abc276_g)

--------------------------

**题目大意：**
求长度为 $n$ 的整数序列 $a_i$ 的个数，满足：

- $0 \le a_1 \le a_2 \le \dots \le a_n \le m$.
- $\forall 1 \le i < n,a_i \not \equiv a_{i+1} \pmod{3}$.

--------------------------

生成函数入门题，完全不需要考虑组合意义。

首先有一个很明显的 $O(nm^2)$ dp，记 $f_{i,j}$ 为考虑序列前 $i$ 个数，且 $a_i=j$ 时的序列个数，有转移：

$$
f_{i,j} =
\begin{cases}
1 &i=1\\
\sum_{ 0 \le k \le j, k \not \equiv j } f_{i-1,k} &i > 1
\end{cases}
$$

可以用前缀和优化到 $O(nm)$，但很明显不够，考虑设OGF $F_i(x) = \sum_{j \ge 0} f_{i,j}x^j$，上面的转移式就变成了：

$$
F_i(x) =
\begin{cases}
\dfrac{1}{1-x} &i=1\\
\dfrac{x^2+x}{1-x^3} F_{i-1}(x) &i > 1
\end{cases}
$$

很明显可以得到 $F_i(x)$ 的封闭形式：

$$
F_i(x) = \dfrac{(x^2+x)^{i-1}}{(1-x)(1-x^3)^{i-1}}
$$

最后的答案是 $\sum_{i=0}^m f_{n,i}$，那么我们要求的就是：

$$
\begin{aligned}
&\sum_{i=0}^m[x^i] F_n(x) \\
= &[x^m]\dfrac{1}{1-x}F_{n}(x)\\
= &[x^m] \dfrac{(x^2+x)^{n-1}}{(1-x)^2(1-x^3)^{n-1}}\\
= &[x^m] \dfrac{x^{n-1}(x+1)^{n-1}}{(1-x)^2(1-x^3)^{n-1}}\\
= &[x^{m-n+1}] \dfrac{(x+1)^{n-1}}{(1-x)^2} \cdot \dfrac{1}{(1-x^3)^{n-1}}\\
\end{aligned}
$$

其中 $\dfrac{(x+1)^{n-1}}{(1-x)^2}$ 就是 $(x+1)^{n-1}$ 的二阶前缀和，而 $(x+1)^{n-1},\dfrac{1}{(1-x^3)^{n-1}}$ 均为经典的关于组合数的生成函数：

$$
\begin{aligned}
(x+1)^{n-1} &= \sum_{i \ge 0} \binom{n-1}{i}x^i\\
\dfrac{1}{(1-x^3)^{n-1}} &= \sum_{i \ge 0} \binom{i+n-2}{n-2}(x^3)^i
\end{aligned}
$$

$\dfrac{(x+1)^{n-1}}{(1-x)^2},\dfrac{1}{(1-x^3)^{n-1}}$ 的前 $m-n+1$ 项均可在线性时间内算出，同样可在线性时间内算出二者卷积的第 $m-n+1$ 项，总复杂度线性。

~~感觉这个式子找不出什么组合意义。~~

题外话：使用线性递推可以做到 $O(n \log n \log m)$，$n$ 开到 $10^5$ 级别，此时 $m$ 可以开到 $10^{18}$。

代码：
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define pb push_back
#define mp make_pair
using namespace std;

typedef long long ll;
const int V = 1e7+5;
const int Mod = 998244353;

int n, m, ans;
ll fac[V], finv[V], F[V];

inline int qpow(int a, int b) {
    ll base = a, ans = 1;
    while (b) {
        if (b & 1) ans = ans * base % Mod;
        base = base * base % Mod;
        b >>= 1;
    }
    return ans;
}

inline void Add(int &a, int b) { a += b; if (a >= Mod) a -= Mod; }
inline ll C(int n, int m) {
    if (m > n) return 0;
    return fac[n] * finv[m] % Mod * finv[n - m] % Mod;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < V; i++) fac[i] = fac[i - 1] * i % Mod;
    finv[V - 1] = qpow(fac[V - 1], Mod - 2);
    for (int i = V - 1; i; i--) finv[i - 1] = finv[i] * i % Mod;

    scanf("%d%d", &n, &m);
    
    F[0] = 1;
    for (int i = 1; i <= m - n + 1; i++) F[i] = (F[i - 1] + C(n - 1, i)) % Mod;
    for (int i = 1; i <= m - n + 1; i++) F[i] = (F[i - 1] + F[i]) % Mod;
    for (int i = 0; i <= m - n + 1; i += 3) Add(ans, C(i / 3 + n - 2, n - 2) * F[m - n + 1 - i] % Mod);

    printf("%d", ans);
    return 0;
}
```

---

## 作者：Leowang2009 (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc276_g)
# 思路
先对原数组 ${a}$ 进行差分，得到数组 ${b}$。由于：
$$\forall i\in[2,N],a_i\not\equiv a_{i-1}\pmod{3}$$
故：
$$\forall i\in[2,N],b_i\not\equiv0\pmod{3}$$
所以可以先对所有的 $b_i$ 对 $3$ 取模，此时 $\forall i\in[2,N],b_i\in\begin{Bmatrix}1,2\end{Bmatrix}$ 且 $b_1\in\begin{Bmatrix}0,1,2\end{Bmatrix}$。

所以我们可以枚举 $b_1\bmod 3$ 的值。因为 $a_N\le M$，所以 $\sum b\le M$。下面以 $a_1\equiv0\pmod{3}$ 为例。

我们可以枚举 $b_i$ 中有几个 $1$，自然就知道其中有几个 $2$。不妨设现在有 $k$ 个 $2$，容易知道，此时 $\sum b=N+k-1$。考虑此时将 $3$ 插入，容易知道最多可插入 $cnt=\left\lfloor\dfrac{M-k-N+1}{3}\right\rfloor$ 个 $3$。又因为一共有 $n-1$ 个空，且一个空中可以插入多个 $3$，所以总可能数为 $\sum\limits_{k=0}^{n-1}C_{n-1}^{k}\sum\limits_{j=0}^{cnt} C_{n+j}^{j}$。
# 代码
显然，第二部分很容易做前缀和，复杂度可以优化到 $O(n)$。
## AC Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353,N=2e7+5;
int n,m,fac[N],inv[N],s[N],res;
int qpow(int x,int n){//快速幂
	int res=1;
	while(n){
		if(n&1) res=res*x%mod;
		x=x*x%mod,n>>=1;
	}return res;
}
int C(int n,int m){//组合数
	if(n>m) return 0;
	else if(!n) return 1;
	return fac[m]*inv[m-n]%mod*inv[n]%mod;
}
void prep(){//预处理阶乘、阶乘的数论倒数、以及前缀和
	fac[0]=inv[0]=s[0]=1;
	for(int i=1;i<N;i++) inv[i]=qpow(fac[i]=fac[i-1]*i%mod,mod-2);
	for(int i=1;i<m;i++) s[i]=(s[i-1]+C(n-1,i+n-1))%mod;
}
signed main(){
	scanf("%lld%lld",&n,&m),prep();
	for(int i=0;i<=2;i++)//a1的三种情况都要计算
		for(int j=0;j<n&&j+n-1+i<=m;j++)
			res=(res+C(j,n-1)*s[(m-j-n+1-i)/3]%mod)%mod;//按照思路模拟即可
	printf("%lld",res);//输出答案
	return 0;
}
```
完结撒花！

---

## 作者：analysis (赞：6)

模拟赛场切了，来洛谷发一手。

看到很少 GF 的做法，只有 [Unique_Hanpi](https://www.luogu.com.cn/user/261935) 大佬写了一个 GF 做法。

但是式子有点不一样，所以简单写了篇题解。

---

我们容易将题意转化为：

- $a_{i+1}-a_i > 0$
- $a_{i+1}-a_i \not\equiv 0 \pmod{3}$
- $a_1 \geq 0$，$a_n \leq m$

容易想到要讨论的是 $\Delta = a_{i+1} - a_i$。

那么问题转化为：从 $a_1$ 开始，转移 $n-1$ 次，末尾小于等于 $m$ 的方案数。

设出 $\Delta$ 的 GF，即：

$$
G(x) = \sum_{k \geq 0}x^{3k+1}+x^{3k+2} = \frac{x(1+x)}{1-x^3}
$$

那么答案即为（考虑 $a_1$ 无限制，最终答案归于 $m$ 项）：

$$
[x^m]\frac{G^{n-1}}{(1-x)^2} = [x^m]\frac{x^{n-1}(1+x)^{n-1}}{(1-x^3)^{n-1}(1-x)^2} = [x^{m-n+1}]\frac{(1+x)^{n-1}}{(1-x^3)^{n-1}(1-x)^2}
$$

是 D-Finite 的，于是可以 $O(n)$ 递推。

最后的式子是：

$$
(i+1)f_{i+1}=(n+1)f_{i}-(n-2-i)f_{i-1}-(5-3n-i)f_{i-2}-(n+1)f_{i-3}+(4-2n-i)f_{i-4}\\
$$

```cpp
#include <bits/stdc++.h>
#define int long long
const int mod = 998244353;
using namespace std;
int n, m, k;
int f[10000005];
int inv[10000005];
inline void add(int &x,int y)
{
    x += y;
    if(x >= mod)x -= mod;
}
inline void sub(int &x,int y)
{
    x -= y;
    if(x < 0)x += mod;
}
signed main()
{
    scanf("%lld%lld", &n, &m);
    k = m - (n-1);
    if (k < 0)
    {
        printf("0");
        return 0;
    }
    f[0] = 1;
    for (int i = 0; i < k; i++)
    {
        if (i > 0)
            inv[i + 1] = (mod - mod / (i + 1)) * inv[mod % (i + 1)] % mod;
        else
            inv[i + 1] = 1;
        int res = 0;
        add(res,(n+1)*f[i]%mod);
        if(i-1>=0)
        {
            sub(res,((n-2-i)*f[i-1]%mod + mod) % mod);
        }
        if(i-2>=0)
        {
            sub(res,((5-3*n-i)*f[i-2]%mod + mod) % mod);
        }
        if(i-3>=0)
        {
            sub(res,(n+1)*f[i-3]%mod);
        }
        if(i-4>=0)
        {
            add(res,((4-2*n-i)*f[i-4]%mod + mod) % mod);
        }
        f[i+1]=res*inv[i+1]%mod;
    }
    printf("%lld",f[k]);
    return 0;
}
```

---

## 作者：whhsteven (赞：5)

感觉比较有意思和巧妙的一道题。学习自 [官方题解](https://atcoder.jp/contests/abc276/editorial/5182)。

&nbsp;

首先，将 $A$ 差分得到 $B = (a_1, a_2-a_1, a_3-a_2,\cdots, a_N-a_{N-1})$。$A$ 与 $B$ 构成双射，故对合法的 $B$ 计数，即可知合法的 $A$ 的数目。

因为 $A$ 单调不降且相邻两项对 $3$ 不同余，所以 $B$ 为非负整数数列，且从第 $2$ 项开始模 $3$ 余 $1$ 或余 $2$。又因为 $a_N \le M$，所以 $\sum b \le M$。

问题即转化为求从第二项开始每项模 $3$ 余 $1$ 或余 $2$，且和不超过 $M$ 的非负整数数列的数目。

将 $B$ 的每一项写成带余除法的形式：$b_i = 3k_i + r_i$，这里 $1 \le i \le N,\ k_i \in \mathbb N,\ r_i \in \{0, 1, 2\}$。并记 $K = (k_1, k_2, \cdots, k_N),\ R = (r_1, r_2, \cdots, r_N)$。

考察一个特定的 $R$，则合法的 $K$ 的数目，即为满足长度为 $N$ 且和不超过 $\left\lfloor\frac{M - \sum r}{3}\right\rfloor$ 的非负整数数列的数目。求满足长度为 $N$ 且和等于 $S$ 的非负整数数列数目是经典问题，由隔板法可知答案是 $\binom{S + N - 1}{N - 1}$。对其做前缀和，即得满足长度为 $N$ 且和不超过一给定值的非负整数数列数目。

由上面可知，$R$ 对 $K$ 的影响只来源于 $\sum r$。枚举 $r_1$，枚举 $r_2 \sim r_N$ 中取值为 $1$ 的个数 $c$，容易求出具体排列的方案数 $\binom{N - 1}{c}$，同时容易求出 $\sum r = r_1 + 2N - c - 2$，从而得到对应合法 $K$ 的数目。由此可以求出答案。

&nbsp;

[AT 提交记录](https://atcoder.jp/contests/abc276/submissions/36275343)

---

## 作者：WitzerLW (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc276_g)

# 前言（可跳过）
截至本题解发布之时，本题共有 $14$ 份题解（不包括本篇）。我阅读了所有的 $14$ 篇题解，发现大家的做法都几乎一样 ~~（除了那位 GF 大佬）~~。

大家在枚举完了待求数组模 $3$ 意义下的差分数组后，对于剩下的那些 $3$ 的分配，无不是先枚举了真正分配掉的 $3$ 的个数，再计算并累加答案，甚至为了不爆复杂度而求了一个组合数的前缀和。

作为一名数信~~双休~~双修的学生，我发现最后分配 $3$ 的这一步无需如此折腾，用以下的简单方法，不用求组合数的前缀和即可 $O(n)$ 求出答案。

读者若已通晓本题其他题解的思路，可快进至求解问题的Part 2。欲知全部解题过程，请从下一行开始阅读。

# 明确题意
先明确题意：求长度为 $n$ 的数组 $A$ 的方案数，满足：
- 数组不严格单调递增，且 $a_n \le m$；
- 相邻两个元素对 $3$ 取模的余数不同。

# 思路

### 转化问题
与其直接枚举 $A$ 数组，不如枚举 $A$ 的差分数组。原数组和差分数组是一一对应的；且枚举差分数组时方便处理单调递增；且差分数组的总和即为 $a_n$，因此满足该数组的总和 $\le m$ 即可。以下令 $A$ 数组的差分数组为 $B$ 数组。易知 $B$ 数组的和应 $\le m$。

### 进一步转化问题
我们可以对 $B$ 数组中的每一项取模 $3$ 意义下的余数。这样只需保证余数数组的除第一项以外不等于 $0$ 即可满足第二个条件。以下令 $B$ 数组每一项取模 $3$ 意义下的余数的数组为 $C$ 数组。易得该数组每一项为 $0$ 或 $1$ 或 $2$，以及 $B$ 数组等于 $C$ 数组中的一些元素加上一些 $3$。

$$
A=(a_1,a_2,a_3,\ldots,a_n)
$$

$$
B=(b_1,b_2,b_3,\ldots,b_n)
$$

$$
\sum_{i=1}^nb_i\le m
$$

$$
C=(c_1,c_2,c_3,\ldots,c_n)
$$

$$
c_i\in\{0,1,2\}
$$

为了使得 $B$ 数组中相邻两个元素对 $3$ 取模的余数不同，应当使得 $c_2,\ldots,c_n$ 均不能等于 $0$。

$$
C=(0/1/2,\,1/2,\,1/2,\,\ldots,\,1/2)
$$

$$
c_1\in\{0,1,2\}
$$

$$
c_{2\ldots n}\in\{1,2\}
$$

### 求解问题 Part 1
$C$ 数组比较好枚举。我们首先枚举 $c_1$ 是 $0,1$ 或 $2$，然后对于后面的 $c_2,...,c_n$ 共 $n-1$ 个元素，枚举其中有 $k$ 个 $1$，剩下 $n-1-k$ 个为 $2$（此处这样枚举是方便求余数的和，详见求解问题Part 2）。别忘了还需要一重枚举来分配那些求 $C$ 数组对 $3$ 取余被抹掉的很多个 $3$。答案可以如下表示（$d$ 表示分配剩下的 $3$ 的方案数）：

$$
ans=\sum_{c_1=0}^2\,\cdot\,\sum_{k=0}^{n-1}\,\cdot\;\mathcal{C}_{n-1}^{k}\cdot d
$$

接下来只需要求解 $d$，即求解分配那些 $3$ 的方案数了。

### 求解问题 Part 2
首先要解决的问题是，我们有多少个 $3$ 可以分配。

根据前面的枚举方法，这里 $C$ 数组已经用掉了 $B$ 数组的总和的一部分。这一部分包含 $c_1$，$k$ 个 $1$，以及 $n-1-k$ 个 $2$。他们的和，即 $C$ 数组的和，可以被表示为 $c_1+1\times k\, +2\times (n-1-k)$。我们用 $m$ 减去这个总和，除以 $3$ 再向下取整，即可得出可供分配的 $3$ 的个数。注意，$b_n$ 小于 $m$ 即可，无需严格等于，因此实际无需分配完这些 $3$。以下令 $cnt$ 表示能够分配的 $3$ 的个数。易得：

$$
cnt=\lfloor  \dfrac{m-c_1-n-1-k}{3}  \rfloor
$$

在此基础上，我们需要解决：

**将 $cnt$ 个 $3$ 分配到 $n$ 个位置中，可以不全部分配，可以某些位置分配 $0$ 个。求如此分配的方案数。**

---

其它题解中，接下来的做法是：先枚举实际分配掉了多少个 $3$，再用隔板法枚举这些 $3$ 有多少种分配方案。因为这里需要再进行一重枚举求和，代码中需要预处理组合数的前缀和来避免超时。相关做法详见其它题解。

实际上，不需要这么复杂。

**我们完全可以虚拟出来第 $n+1$ 个位置，用来接收所有没有被分配的 $3$。和其它的位置一样，它可以分配 $0$ 个 $3$，此时所有能被分配的 $3$ 全部被分配。这样问题可以转化为：**

**将 $cnt$ 个 $3$ 分配到 $n+1$ 个位置中，必须全部分配，可以某些位置分配 $0$ 个。求如此分配的方案数。**

这样可以用隔板法轻松解决。由于每个位置可以分配 $0$ 个，不方便直接隔板，我们先强制给每个节点分配 $-1$ 个，即总量向每一个位置“借”$1$ 个。这样借完后，每个位置都需要被强制分配至少一个 $3$，以此避免有一个位置被分配了 $-1$ 个 $3$。

**问题转化为：将 $cnt+n+1$ 个 $3$ 分配到 $n+1$ 个位置中，且每个位置强制至少分配 $1$ 个。**
于是，对于借得之后的 $cnt+n+1$ 个 $3$，其间有 $cnt+n$ 个可以插板的间隙，且需要不计顺序地插入 $n$ 个隔板（不能两个隔板插入同一个间隙，不能将隔板插入最前面和最后面，以此避免有一个被借完后的位置被分配了 $0$ 个）。这一步的方案数为 $\mathcal{C}_{cnt+n}^{n}$。

于是，答案可以如下表示：

$$
ans=\sum_{c_1=0}^2\,\cdot\,\sum_{k=0}^{n-1}\,\cdot\;\mathcal{C}_{n-1}^{k}\,\cdot\,\mathcal{C}_{cnt+n}^{n}
$$

---

这种做法无需再进行一重枚举，也无需求组合数的前缀和，以此做到了常数上更优。



# 策码奔腾

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5,mod=998244353;
int n,m,ans=0;
int fac[N],invFac[N],inv[N];
int qpow(int x,int k){
	int ret=1;
	while(k){
		if(k%2==1) ret*=x,ret%=mod;
		x*=x,x%=mod;
		k/=2;
	}
	return ret;
}
void init(){
	fac[0]=1;
	for(int i=1;i<=N-1;i++) fac[i]=fac[i-1]*i,fac[i]%=mod;
	invFac[N-1]=qpow(fac[N-1],mod-2);
	for(int i=(N-1)-1;i>=0;i--) invFac[i]=(i+1)*invFac[i+1],invFac[i]%=mod;
	for(int i=0;i<=N-1;i++) inv[i]=invFac[i]*fac[i-1],inv[i]%=mod;
}
int C(int x,int y){//此处x在下面y在上面，C(x,y)表示从x个中不计顺序地选y个的方案数
	if(y>x) return 0;
	if(y==0) return 1;
	return fac[x]*invFac[x-y]%mod*invFac[y]%mod;
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	init();
	for(int c1=0;c1<=2;c1++){
		for(int k=0;k<=n-1&&c1+n+k-1<=m;k++){
			int cnt=(m-c1-n-k+1)/3;
			ans+=C(n-1,k)*C(cnt+n,n)%mod,ans%=mod;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：2)

对于答案序列 $a$ 来说，它的差分数组是独一无二的，所以就转化为了求差分数组的方案数，这样转化后可以保证序列单调递增。\
对于差分数组 $b$ 来说，$\sum b_i\le m$，$\forall i\in[2,n]\ \ \ \ b_i\not\equiv 0\pmod{3}$，由于 $b_i$ 只有 $1$ 和 $2$ 两个取值，所以当确定一个取值的数量的时候，另一个取值的数量也确定了。\
考虑枚举 $b_i=2$ 的数量为 $k$，这时方案数为 $\operatorname{C}_{n-1}^k$，$\sum b_i=b_1+2k+(n-1-k)=b_1+n-1+k$，然后还剩下可以加的值为 $s=m-b_1-n-k+1$，为了确保 $b_i\bmod 3$ 不变，所以对于一个 $b_i$，只能给他加上 $3w(w\in\N)$，所以最多可以加 $\lfloor\frac{s}{3}\rfloor$ 个 $3$，这个的数量就是分配数，答案就是求
$$
\sum_{i=0}^{2}\sum_{k=0}^{m-i-n+1}\operatorname{C}_{n-1}^{k}\sum_{j=0}^{\lfloor\frac{s}{3}\rfloor}\operatorname{C}_{n-1+j}^{n-1}
$$
其中第一个求和式枚举 $b_1\bmod 3$ 的取值，第二个求和式枚举 $b_i\bmod 3=2$ 的个数，第三个求和式枚举加 $3$ 的个数，代码只需要预处理阶乘逆元和前缀和即可，世界复杂度 $O(n+m)$。
```cpp
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e7+10,mod=998244353;
int jc[N],ny[N],n,m,ans,s[N];
inline int qpow(int a,int b){int res=1;for(;b;b>>=1,a=a*a%mod)if(b&1)res=res*a%mod;return res;}
inline int C(int x,int y){return jc[x]*ny[y]%mod*ny[x-y]%mod;}
inline void sol(int m){for(int i=0;m-n-i+1>=0&&i<n;++i)ans=(ans+C(n-1,i)*s[(m-n-i+1)/3]%mod)%mod;}
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	n=read(),m=read();if(n>m+1){std::cout<<0<<'\n';exit(0);}
	jc[0]=1;for(int i=1;i<=n+m;++i)jc[i]=jc[i-1]*i%mod;
	ny[n+m]=qpow(jc[n+m],mod-2);for(int i=n+m;i;--i)ny[i-1]=ny[i]*i%mod;
	s[0]=1;for(int i=1;i<=m;++i)s[i]=(s[i-1]+C(n-1+i,n-1))%mod;
	sol(m),sol(m-1),sol(m-2);std::cout<<ans<<'\n';
}
```

---

## 作者：beauty_son_whm (赞：2)

求长度为 $n$ 的满足下列条件的序列 $A$ 的个数：

- $a_1\leq a_2\leq a_3......\leq a_n\leq M$

- $\forall 1\leq i <n,a_i \not \equiv a_{i+1}(\bmod\ 3)$

我们现在对 $A$ 序列作差分。得到 $B$ 序列。我们看看 $B$ 这个序列需要满足的条件：

- $b_i \geq 0 $

- $\forall i>1, \ b_i \bmod3 \not=0$

- $\sum b_i\leq M$

所以我们找到符合条件的 $B$ 序列的个数就可以了。

令 $x_i=b_i \bmod 3,y_i=\lfloor \frac{b_i}{3} \rfloor$ 。如果我们知道了序列 $X$ 是怎样的。那么对应的序列 $Y$ 的个数就等价于非负整数序列，并且满足 $\sum y_i\le \lfloor \frac{M-\sum x_i}{3} \rfloor$ 的个数。这个东西似乎很好算。相当于是有 $n$ 个盒子，一共要放 $T\le \lfloor \frac{M-\sum x_i}{3} \rfloor$ 个数，问你总方案数，其实就是 $\binom{n+T-1}{n-1}$。那么我们只需要知道 $C=\sum x_i$ 的 $X$ 序列有多少个就行了。因为 $x_i$ 的取值只有 $1,2$ 所以我们枚举 $2$ 有几个，这个东西就能随便算了，总式子应该是：

$$\sum_{i=0}^{M-n} \binom{n}{i}\sum_{T=0}^{\lfloor \frac{M-n-i}{3} \rfloor}\binom{n+T-1}{n-1}$$

但是我们还没考虑 $\ b_1 \bmod3=0$ 的情况，将序列长度减一再做一遍就行了。

---

## 作者：zhongpeilin (赞：1)

## 题目大意：
给定 $N, M$，询问有多少整数序列 $a$ 满足：  
$0 \le a_{i} \le a_{2} \le \dots a_{n} \le m$  
$a_{i}$ 和 $a_{i + 1}$ 模 `3` 的余数不同。  
## 解题思路：
首先我们有个 $O(n \times m^2)$ 的 dp，可以通过前缀和优化解决变成 $O(nm)$，接下来就不好转移了，所以我们换个角度。  
设 $b_{i} = a_{i} - a_{i - 1}$，那么将 $b_{i}$ 模 `3` 就会得到以下几个性质：  
$b_{1} = 0, 1, 2$。  
$b_{i} = 1, 2 (2 \le i \le n)$
有了这个，我们只需枚举 $b_{1}$ 以及 $b_{2 \sim n}$ 中有多少 `1` 就能确定我们的整个 $b$ 数组。  
定下 $b_{i}$ 模 `3` 的值之后，我们考虑用排列组合。  
首先我们只定了这个整体有多少 $b_{i} = 1$，所以先乘个 $C_{n - 1}^j$，然后我们枚举 $b_{1 \sim n}$ 一块有多少个 `3`，即 $a_{n}  \div 3$，假设有 $j$ 个，那么考虑插板法。根据可空的插板法公式得：  
$$ans = \sum_{i=0}^{n-1}C_{n - 1}^{i} \times \sum_{j = 0}^{j \times 3 + b_{1} + i \times 1 + (n - 1 - i) \times 2 \le m}C_{n + j - 1}^{n - 1}$$
我们不难发现可以将后面的式子做一个前缀和优化，即可 $O(n)$。  
## code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

int qp(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

int jie[20000005], inv[20000005];
int C(int m, int n){ //这里一定要卡到 O(1)，不然应该过不掉
	if(m > n) return 0;
	return jie[n] * inv[m] % mod * inv[n - m] % mod;
}
int sum[20000005];
int n, m;
signed main(){
	cin >> n >> m;
	if(n > m + 1){ //判掉，方便后面
		cout << 0 << endl;
		return 0;
	}
	int MAX = (m - n + 1) / 3 + n - 1; //表示上文中需要预处理组合数最大值，不加也行，直接设成2e7
	
	jie[0] = 1;
	for(int i = 1; i <= MAX; i++){
		jie[i] = jie[i - 1] * i % mod;
	}
	inv[MAX] = qp(jie[MAX], mod - 2);
	for(int i = MAX - 1; i >= 0; i--){
		inv[i] = inv[i + 1] * (i + 1) % mod; //这里可以先算inv[MAX],然后再一点一点的乘数来算逆元。
	}
	
	sum[0] = 1;
	for(int i = 1; i <= MAX - n + 1; i++){
		sum[i] = (sum[i - 1] + C(n - 1, i + n - 1)) % mod; //前缀和优化
	}
	int ans = 0;
	for(int i = 0; i <= n - 1; i++){
		int Sum = 0;
		for(int val = 0; val < 3; val++){ //b[1]
			if(m - i - (n - 1 - i) * 2 - val < 0) break; //不能超过m
			Sum = (Sum + sum[(m - i - (n - 1 - i) * 2 - val) / 3]) % mod; //前缀和算出最大值
		}
		(ans += Sum * C(i, n - 1) % mod) %= mod;
	}
	printf("%lld\n", ans);
	return 0;
}
```
喜欢的话，点个赞吧 QWQ！

---

## 作者：yukimianyan (赞：1)

## problem
求有多少个单调递增的整数数列，使得相邻两项对三取模的余数不相同。值域为 $[0,m]$，长度为 $n$。$n,m\leq 10^7$。

## solution
考虑差分数组 $b_i=a_i-a_{i-1}$，将问题转换成：
- $b_1\geq 0$.
- $b_i>0\quad(i>1)$.
- $\sum b_i\leq M$.

考虑将 $b_i$ 表示为 $3y_i+x_i$ 之形式，其中 $x_i<3$，显然 $x_i,y_i$ 是独立的，只要满足和的限制就好。具体地，限制为

$$\sum y_i\leq \left\lfloor\frac{M-\sum x_i}{3}\right\rfloor.$$

现在将问题转化成：
1. 如何求 $\sum y_i\leq T$ 的方案数？
2. 如何求 $\sum x_i\leq T$ 的方案数？

### task 1
在所有 $y_i$ 加一后，变成这样一个问题：

- 已知 $\sum y_i$ 且 $y_i\geq 1$，求有多少种分配的方案？

显然这是隔板法，那么 $\sum y_i=T$ 的方案数为 $\binom{T+n-1}{n-1}$，做个前缀和预处理即可。

### task 2
观察到除了 $x_1$ 外每个 $x_i$ 的取值都是 $1$ 或 $2$，那么我直接枚举有多少个 $1$ 即可。对于 $x_1$ 它也只有三种取值。

复杂度线性。
## code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int P=998244353;
const int N=2e7;
int n,m;
LL qpow(LL a,LL b,int p=P){LL r=1;for(a%=P;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p; return r;}
LL fac[N+10],ifac[N+10],s[N+10],ans;
LL C(int n,int m){return fac[n]*ifac[m]%P*ifac[n-m]%P;}
int main(){
	for(int i=fac[0]=ifac[0]=1;i<=N;i++) fac[i]=fac[i-1]*i%P;
	ifac[N]=qpow(fac[N],P-2);
	for(int i=N-1;i>=1;i--) ifac[i]=ifac[i+1]*(i+1)%P;
	scanf("%d%d",&n,&m);
	s[0]=1;
	for(int i=1;i<=m;i++) s[i]=(s[i-1]+C(n+i-1,n-1))%P;//,printf("s[%d]=%lld\n",i,C(n+i-1,n-1));
	for(int x0=0;x0<=2;x0++){
		for(int i=0;m>=n+i-1+x0&&n-1>=i;i++){
			//sum x_i=2i+n-1-i+x0=n+i-1+x0
			//numbers of x_i=C(n-1,i)
			//sum y_i<=(m-sum x_i)/3
			int sumx=n+i-1+x0;
			ans=(ans+C(n-1,i)*s[(m-sumx)/3])%P;
		}
	}
	printf("%lld\n",ans);
	return 0;
}

```

## review
$\sum y_i\leq T$ 的方案数为 $\binom{T+n}{n}$。因为我们有 $\sum_{0\leq i\leq n}\binom{i+m}{m}=\binom{n+m+1}{m+1}$。（参考 [ABC154F](https://www.cnblogs.com/caijianhong/p/solution-ABC154F.html) 的题解）

---

## 作者：zhaoyp (赞：1)

[ABC276G](https://atcoder.jp/contests/abc276/tasks/abc276_g)
$\text{Difficulty : 2278}$。

以此来浅浅纪念下我第一道赛时想出来的 G。

给定 $n,m$，求有多少序列满足以下条件。对大质数取模。

- $0 \le a_1 \le a_2 \le \cdots \le a_n \le m$
- $a_i$ 与 $a_{i+1}$ 对 $3$ 取余的余数不同。

------------

$n$ 个数之间形成了 $n-1$ 个空当。相邻数字间相差对 $3$ 取余的余数为 $1$ 或 $2$。可以枚举 $1$ 的次数 $k$。$k$ 个 $1$ 分配到 $n-1$ 个空当的方案数为 $\dbinom{n-1}{k}$。

假设 $a_1 \equiv 0 \pmod{3}$。

那么还剩下 $cnt = \left\lfloor\dfrac{m-2n+k+2}{3}\right\rfloor$ 个长度为 $3$ 的段，考虑把这 $cnt$ 段插入到 $n+1$ 个空当中（加上 $a_1$ 之前的和 $a_n$ 之后的），根据隔板法可得方法数为 $\dbinom{n+cnt}{n}$。

综上：

$$ans = \sum\limits_{k=0}^{n-1}\dbinom{n-1}{k}\dbinom{n+cnt}{n}$$

然后再对 $a_1 \equiv 1 \pmod{3}$ 和 $a_1 \equiv 2 \pmod{3}$ 的情况再做一次就行了。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e7 + 5;
const int N = 2e7 + 5;
const int mod = 998244353;
long long n,m,fac[maxn],inv[maxn],ans; 
inline int read()
{
	int x = 0,f = 1;char ch = getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return f * x;
}
long long qpow(long long a,long long b){long long ans=1;while(b){if(b&1)ans=ans*a%mod;a=a*a%mod;b>>=1;}return ans;}
inline long long calc(int n,int m){return fac[n] * inv[m] % mod * inv[n - m] % mod;}
void prefix()
{
	fac[0] = 1;
	for(int i = 1;i <= N;i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[N] = qpow(fac[N],mod - 2);
	for(int i = N - 1;i >= 0;i--)
		inv[i] = inv[i + 1] * (i + 1) % mod; 
}
int main()
{
	long long ans = 0;
	prefix();
	cin >> n >> m;
	for(int k = 0;k < n;k++)
	{
		long long cnt = (m - 2 * n + k + 2) / 3;
		if(m - 2 * n + k + 2 >= 0)
			ans = (ans + calc(cnt + n,n) * calc(n - 1,k) % mod) % mod; 
	}
	m--;
	for(int k = 0;k < n;k++)
	{
		long long cnt = (m - 2 * n + k + 2) / 3;
		if(m - 2 * n + k + 2 >= 0)
			ans = (ans + calc(cnt + n,n) * calc(n - 1,k) % mod) % mod; 
	}
	m--;
	for(int k = 0;k < n;k++)
	{
		long long cnt = (m - 2 * n + k + 2) / 3;
		if(m - 2 * n + k + 2 >= 0)
			ans = (ans + calc(cnt + n,n) * calc(n - 1,k) % mod) % mod; 
	}
	cout << ans % mod; 
	return 0 ;
}
/*
NOIP 2022 RP++
*/
```

---

## 作者：JiaY19 (赞：1)

### 题意

要求构造一个值域在 $[0,m]$ 内，有 $n$ 项的单调不降序列，要求相邻两项的数除以三不同余。

### 思路

首先考虑如何使序列单调不降。

我们可以求它的自然数差分序列的方案即可。

考虑如何满足相邻两项不同余。

即除首项外，每一项的值必须 $\equiv 1\pmod 3$ 或 $\equiv 2\pmod 3$。

所以考虑枚举 $\equiv 1\pmod 3$ 的个数。

枚举时，由于还可以给某几项加 $3$。

所以这方面的方案数也需要加上。

答案即为。

$$\sum_{i=1}^{i\le n,n\times2-i\le m}C_{n}^{i}\times \sum_{j=1}^{\lfloor\frac{m-x+i}{3}\rfloor}C^{n-1}_{n+j-1}$$

后面这一堆也就是 $3$ 的方案数，使用隔板法计算，可以考虑预处理。

前面的也就是枚举 $1$ 的方案数，注意加起来不要超过 $m$。

但是上述式子忽略了首项可以为 $0$。

所以我们还需要在算出 $n-1$ 的方案即可，即指定第一个初始为 $0$。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 20000010;
const int mod = 998244353;

int n, m, inv[N], sum[N];

inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}

inline int power(int x , int y)
{
    int res = 1;
    while(y)
    {
        if(y & 1) res = res * x % mod;
        x = x * x % mod, y /= 2;
    }
    return res;
}

inline int C(int x , int y)
{
    return inv[x] * power(inv[x - y], mod - 2) % mod * power(inv[y], mod - 2) % mod;
}

inline int solve(int x)
{
    int ans = 0;
    for (int i = 0; i <= x; i++)
    {
        int op1 = i, op2 = x - i;
        if (op2 * 2 + op1 > m) continue;
        int op3 = (m - op2 * 2 - op1) / 3;
        ans = (ans + C(x , op1) * sum[op3] % mod) % mod;
    }
    return ans;
}

signed main()
{
    n = read(), m = read(), inv[0] = sum[0] = 1;
    for (int i = 1; i <= 2 * max(n, m); i++)
        inv[i] = inv[i - 1] * i % mod;
    for (int i = 1; i <= m / 3; i++)
        sum[i] = (sum[i - 1] + C(n + i - 1 , n - 1)) % mod;
    cout << (solve(n) + solve(n - 1)) % mod << endl;
    return 0;
}
```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

原数组的限制方式很难刻画，看到余数相关，套路的考虑差分。

设差分完的数组为 $f$，$f$ 显然符合 $i\in [2,n],f_i \bmod 3\neq 0$，考虑枚举其中 $f_i \bmod 3=2$ 的个数，设为 $j$，则 $f_i \bmod 3=1$ 的个数为 $n-1-j$，此时 $\sum f_i=2 \times j+n-1-j$ 化简后 $\sum f_i=n+j-1$。

考虑怎么回推得到不同的原数组，发现满足条件的原数组差分后都满足 $\sum f_i\le m$，在保证 $f$ 余数不变的情况下，将 $m$ 减去现在的和剩下的数每 $3$ 个分配给 $f$ 数组里的数即可，能分配的总数是 $\lfloor \frac{m-(n+j-1)}{3}\rfloor$，排列组合可以得到总个数的式子 $\sum\limits_{j=0}^{n-1}C_{n-1}^{j}\sum\limits_{k=0}^{\lfloor \frac{m-(n+j-1)}{3}\rfloor}C_{n+k}^{k}$ 枚举 $f_1$ 的三个取值，前缀和优化即可。

### $\text{code}$

```cpp
int n,m;

int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}

int fac[maxn],inv[maxn];
void init(int maxn){
	fac[0]=1;
	for(int i=1;i<=maxn;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[maxn]=ksm(fac[maxn],mod-2);
	for(int i=maxn-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}

int C(int m,int n){
	if(n<0||m<0||m<n){
		return 0;
	}
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}

int ans=0;
int sum[maxn];

void solve(){
	n=read(),m=read();
	init(maxn-1);
	sum[0]=1;
	for(int i=1;i<=m;i++){
		sum[i]=(sum[i-1]+C(i+n-1,n-1)%mod)%mod;
	}
	for(int i=0;i<=2;i++){
		for(int j=0;j<n;j++){
			if(j+n-1+i>m){
				break;
			}
			ans=(ans+C(n-1,j)*sum[(m-j-n+1-i)/3]%mod)%mod;
		}
	}
	write(ans);
	puts("");
	return ;
}

```

---

## 作者：Caiest_Oier (赞：0)

# [AT_abc276_g](https://www.luogu.com.cn/problem/AT_abc276_g)  

相邻两项的差不能是 $3$ 的倍数，于是考虑从 $3$ 下手。我们考虑对相邻两项差中出现的 $3$ 的个数计数。     

具体的，枚举 $x=\sum_{i=1}^{n-1}\lfloor\frac{a_{i+1}-a_i}{3}\rfloor$，插板计数，再枚举有哪些差分位置模 $3$ 余 $2$，最后统计 $a_1$ 的选择即可，具体式子如下：    

$$\sum_{i=0}^{\frac{m}{3}}{C_{i+n-2}^{n-2}\times\sum_{j=0}^{\min(n-1,m-3\times i-(n-1))}}{C_{n-1}^{j}\times (m-3\times i-(n-1)-j+1)}$$    

考虑如何预处理后面那个式子。发现处理 $C_{n-1}^{j}$ 的前缀和与 $C_{n-1}^{j}\times j$ 的前缀和即可计算。复杂度线性。    

代码：

```cpp
#include<bits/stdc++.h>
#define MOD 998244353
#define int long long
using namespace std;
int jc[10000003],njc[10000003],ans[10000003],pre,n,m,sum;
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
signed main(){
	jc[0]=1;
	for(int i=1;i<=10000000;i++)jc[i]=jc[i-1]*i%MOD;
	njc[10000000]=fstp(jc[10000000],MOD-2);
	for(int i=9999999;i>=0;i--)njc[i]=njc[i+1]*(i+1)%MOD;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		if(i<n)ans[i]=(ans[i-1]-jc[n-1]*(njc[i-1]*njc[n-1-i]%MOD))%MOD;
		else ans[i]=ans[i-1];
	}
	for(int i=0;i<=m;i++){
		if(i<n)pre=(pre+jc[n-1]*(njc[i]*njc[n-1-i]%MOD))%MOD;
		ans[i]=pre*(i+1)+ans[i];
		ans[i]%=MOD;
	}
	for(int i=0;i*3+(n-1)<=m;i++){
		sum=(sum+(jc[i+n-2]*njc[n-2]%MOD)*(njc[i]*ans[m-3*i-(n-1)]%MOD))%MOD;
	}
	sum%=MOD;
	sum+=MOD;
	sum%=MOD;
	printf("%lld",sum);
	return 0;
}
```

---

## 作者：GFyyx (赞：0)

## 解题思路
这是一道思维题，单看题面一时半会可能没有思路。

深入思考一下，因为 $a_i$ 与 $a_{i+1}$ 对 $3$ 取模余数不同且序列 $a$ 单调递增，定义 $c_i=a_i-a_{i-1}$。

有 $c_i\nmid3,i \in [2,n]$ 且 $\sum\limits_{i=1}^n b_i \leq m$。

显然，如果 $c$ 为满足上述条件，则 $a$ 为合法序列合法。

### 问题转化
现在大家应该有一点思路，我们继续化简式子。

因为当 $2 \leq i \leq n $ 时，$c_i\nmid 3$ 设 $c_i=3x_i+k_i,k\in[1,2]$。

有 $\sum\limits_{i=1}^{n}{3x_i+k_i}\leq m$。

移项得 $\sum\limits_{i=1}^{n}{3x_i} \leq m-\sum\limits_{i=2}^{n}{k_i}$。

再化简一下 $\sum\limits_{i=2}^{n}{x_i} \leq\left\lfloor\dfrac{m-\sum\limits_{i=1}^{n}{k_i}}{3}\right\rfloor$。

又因为 $k\in[1,2]$ 我们枚举 $\sum\ {k_i}$，代入上式。

用隔板法即可求出 $x$ 的取值方案数，又因为 $c$ 与 $a$ 构成双射，所以 $x$ 的方案数即为所求。

## AC 代码
变量名略有不同。

```cpp
#include <iostream>
using namespace std;
const int mod=998244353;
inline long long ksm(long long x,long long y){
	long long res=1;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod;y>>=1;
	}
	return res%mod;
}
long long n,m,jc[1919810<<3],inv[1919810<<3],f[1919810<<3],ans;
void init(){
	jc[0]=f[0]=1;
	int maxn=max(n,m);
    for(register int i=1; i<maxn; i++) jc[i]=jc[i-1]*i%mod;
    inv[maxn-1]=ksm(jc[maxn-1],mod-2);
    for(register int i=maxn-1; i; i--) inv[i-1]=inv[i]*i%mod;
}
inline long long C(int n,int m){return m<=n?jc[n]*inv[m]%mod*inv[n-m]%mod:0;}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	init();
    for(register int i=1; i<=m-n+1; i++) f[i]=(f[i-1]+C(n-1,i))%mod;
    for(register int i=1; i<=m-n+1; i++) f[i]=(f[i-1]+f[i])%mod;
    for(register int i=0; i<=m-n+1; i+=3)
    	ans=ans+C(i/3+n-2,n-2)*f[m-n+1-i]%mod;
	cout << ans%mod << endl;
}
```


---

## 作者：hyman00 (赞：0)

给定 $n,m$ 求满足条件的长度为 $n$ 的序列个数：

- $0\le a_1\le a_2\le\dots\le a_n\le m$ 
- $\forall 1\le i\lt n ,a_{i+1}\mod 3\ne a_i\mod 3$ 

记 $d_i=a_{i+1}-a_i$ 

易得 $\forall 1\le i<n,d_i\ne 3k$ 

$d_i$ 除以 3 余数是 1 或 2

枚举头尾余数（0/1/2），中间有多少个 2

可以直接组合数算

```c++
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define sz(a) ((int)a.size())
#define re return
#define all(a) a.begin(),a.end()
#define int long long
#define rept(i,a,b) for(int i=(a);i<(b);i++)
#define rep(i,a) rept(i,0,a)
#define vi vector<int>
#define pii pair<int,int>
#define F first
#define S second
#define elif else if
using namespace std;
const int MOD=998244353,INF=1000000000000000000;
template<typename T>inline void Mx(T &a,T b){a=max(a,b);}
template<typename T>inline void Mi(T &a,T b){a=min(a,b);}
inline int ad(int &a,int b,int c=MOD){re a=(a+b)%c;}
template<typename T>inline T read(){T a;cin>>a;re a;}
inline bool is_digit(int msk,int d){re (msk>>d)&1;}
const int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
void FILEIO(string s){
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}
int fc[20000007],iv[20000007];
inline int qp(int a,int b){
	int c=1;
	while(b){
		if(b&1)(c*=a)%=MOD;
		(a*=a)%=MOD;b>>=1;
	}
	re c;
}
inline int inv(int x){
	re qp(x,MOD-2);
}
inline void init(){
	fc[0]=iv[0]=1;
	rept(i,1,20000005){
		fc[i]=fc[i-1]*i%MOD;
		iv[i]=inv(fc[i]);
	}
}
inline int C(int x,int y){
	re fc[x]*iv[y]%MOD*iv[x-y]%MOD;
}
inline int calc(int n,int m){
	int ans=0;
	rep(l,3)rep(r,3){
		rep(num,n){
			int ned=l+r+n-1+num;
			if(ned>m||(m-ned)%3)continue;
			ned=(m-ned)/3;
			(ans+=C(n-1,num)*C(ned+n,n)%MOD)%=MOD;
		}
	}
	re ans;
}
void run(){
	init();
	int n,m;
	cin>>n>>m;
	cout<<calc(n,m)<<"\n";
}
signed main()
{
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//	for(int tc=read<int>();tc;tc--)
		run();
	re 0;
}


```

---

