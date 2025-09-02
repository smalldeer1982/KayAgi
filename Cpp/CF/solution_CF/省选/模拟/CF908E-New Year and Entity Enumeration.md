# New Year and Entity Enumeration

## 题目描述

给你一个整数 m ，设 $M = 2^m - 1$  。  
给你一个包含 $n$  个整数的集合，记作 $T$  。其元素会以 $m$  位二进制串的形式输入。 称一个整数集合是“好”的，当且仅当以下条件同时满足：

- 如果 $a \in S$  , 则 $a \text{ XOR } M \in S$ 
- 如果 $a, b \in S$  , 则 $a \text{ AND } b \in S$ 
- $T \subseteq S$ 
- $S$  的所有元素都不超过 $M$ 

在这里，$\text{XOR}$  和 $\text{AND}$  分别指按位异或、按位与运算。  
求“好”的集合的个数模 $10^9 + 7$  的结果。

## 说明/提示

一个合法的集合 SS 的例子是 $\{ 00000, 00101, 00010, 00111, 11000, 11010, 11101, 11111 \}$  。

感谢@hanako 提供的翻译

## 样例 #1

### 输入

```
5 3
11010
00101
11000
```

### 输出

```
4
```

## 样例 #2

### 输入

```
30 2
010101010101010010101010101010
110110110110110011011011011011
```

### 输出

```
860616440
```

# 题解

## 作者：ComplexPlanck (赞：6)


[衬衫毛（传送门）](https://www.luogu.com.cn/problem/CF908E)

暂且不管 $T$，我们先考虑合法的 $S$ 的数量。

我们根据以下两条定义：

1. $a\in S\Rightarrow a\operatorname{xor} M\in S.$

2. $a,b\in S\Rightarrow a\operatorname{and} b\in S.$

对于第一条，相当于将 $a$ 取反，所以我们不妨认为第一条规则即：

1. $a\in S\Rightarrow (\sim a)\in S.$

注意到：

$$
\begin{aligned}
a\operatorname{or} b&=\sim((\sim a)\operatorname{and}(\sim b))\\
a\operatorname{xor} b&=\sim((\sim(a\operatorname{or} b))\operatorname{or}(a\operatorname{and} b))
\end{aligned}
$$

因此有：

3. $a,b\in S\Rightarrow a\operatorname{or} b\in S.$

4. $a,b\in S\Rightarrow a\operatorname{xor} b\in S.$

---

假设你已经得到了一个合法的 $S$，尝试找出其合法的等价条件。

设 $f(x)$ 表示第 $x$ 位为 $1$ 的元素做按位与后得到的值，特别地，如果不存在第 $x$ 位为 $1$ 的元素，那么定义此时 $f(x)=0.$

显然根据我们之前的结论，$f(x)\in S.$

显然在 $f(x)\ne 0$ 时，$f(x)$ 的第 $x$ 位为 $1$，假设 $f(x)$ 的第 $y$ 位为 $1$，我们随即考虑 $f(y).$（显然一定有 $f(y)\ne 0$）

如果 $f(y)$ 的第 $x$ 位为 $0$，那么设 $z=f(x)\operatorname{xor} f(y)$，于是有 $z\in S$，且 $z$ 的第 $x$ 位为 $1$ 而 $z$ 的第 $y$ 位为 $0$，那么这就尴尬了，因为 $z$ 应该是“第 $x$ 位为 $1$ 的元素按位与后得到 $f(x)$”这个过程中的某个元素，这必然导致 $f(x)$ 的第 $y$ 位为 $0$，产生矛盾。

因此 $f(y)$ 的第 $x$ 位一定为 $1$。

我们再考虑 $f(x)$ 的第 $y$ 位为 $0$ 的情况，此时要么 $f(y)$ 为 $0$，要么 $f(y)$ 不为 $0$ 且其第 $x$ 位一定为 $0$，证明方法和上面类似，但总之都有 $f(y)$ 的第 $x$ 位为 $0$。

也就是说，对于任何两个 $x,y$，要么 $f(x)$ 的第 $y$ 位为 $1$ 且 $f(y)$ 的第 $x$ 位为 $1$，要么 $f(x)$ 的第 $y$ 位为 $0$ 且 $f(y)$ 的第 $x$ 位为 $0$。

随即可以联想到无向图连边，我们将第一种情况称为 $x,y$ 之间存在边，第二种情况称之为 $x,y$ 之间不存在边，然后注意到下面这样一个性质：

> 如果 $x,y$ 之间存在边，$y,z$ 之间存在边，那么 $x,z$ 之间一定存在边。

因为 $x,y$ 之间存在边，所以任何 $x$ 位为 $1$ 的元素 $u$，其第 $y$ 位一定为 $1$，而因为 $y,z$ 之间存在边，那么任何 $y$ 位为 $1$ 的元素 $u$，其第 $z$ 位一定为 $1$，进而任何 $x$ 位为 $1$ 的元素，第 $z$ 位都为 $1$，从而可以得到 $f(x)$ 的第 $z$ 位一定为 $1$。

类似地，可以得到 $f(z)$ 的第 $x$ 位一定为 $1$，从而 $x,z$ 之间一定存在边。

我们再仔细看看按照这个性质连出来的图，你会发现场上是一堆完全图，抽象一下，就是场上是一堆集合。

所以合法的 $S$ 必然导致 $m$ 个位被分成若干集合。

---

那么一个天然的想法就是将 $m$ 个元素分成若干个集合的方案是否和合法的 $S$ 一一对应呢？

的确是一一对应的，我们来详细说说为什么。容易得到这样一件事情，就是对于非空的合法集合 $S$，我们之前说了可以将其抽象成一堆完全图，对于某一个元素，只要有一个导出的完全子图中的一位（即这一位为 $1$），那么对于这个元素，这个完全子图中所有的位都一定为 $1$。

反过来，如果这个元素，对于某个导出的完全子图中的一位为 $0$，那么对于这个元素，这个完全子图中所有的位都一定为 $0$。

所以可以将所有的完全图缩成一个点，每个元素要么有（这个点代表的位），要么没有（这些点代表的位）。而我们又得知，单独一个点，即 $f(...)$ 一定在集合中，我们通过 $\operatorname{or}$ 运算就可以将其扩展为这些点构成的全集。

所以一个合法的 $S$ 和一种将 $m$ 个元素划分为若干个集合的方案一一对应。

---

回到题目中 $T$ 的限制，题目中 $T$ 的限制其实就是告诉我们有一些位一定不在一个完全图当中。

我们可以这样，就是对于给定的 $\{a_0,\cdots,a_{n-1}\}$，求出 $\{b_0,\cdots,b_{m-1}\}$ 它们满足关系式子：

$$b_x=\sum_{i=0}^{n-1}2^i\times(\left\lfloor \dfrac{a_i}{2^x}\right\rfloor\operatorname{mod} 2)$$

其实 $b_x$ 就表示第 $x$ 位为 $1$ 的有哪些元素。

然后如果 $b_x\ne b_y$ 则说明 $x,y$ 一定不在同一个完全图当中，反之则不一定。

我们知道，当没有任何限制的时候，答案应当是贝尔数（Bell number）$B_n$ ：即将 $n$ 个元素划分为若干个集合的方案数。

假设有 $r$ 个位，它们可在可不在一个完全图中，这意味着它们的 $b$ 都相同，这一部分的方案数是 $B_r$。而对于一定不在一个完全图中的情况，又是完全独立的，所以根据乘法原理，答案就应该是 $\prod B_r$。

至于贝尔数，我们其实可以这样得出其递推公式：对于 $B_{n}$，每次从 $1\sim n-1$ 中选择 $k$ 个元素和第 $n$ 个元素形成一个新集合，也就是有递推公式：

$$
\begin{aligned}
B_{n}&=\sum_{i=0}^{n-1}\binom{n-1}{k}B_{n-1-k}\\
\texttt{换元 }k\leftarrow n-1-k:\qquad &=\sum_{i=0}^{n-1}\binom{n-1}{n-1-k}B_k\\
\binom{n}{k}=\binom{n}{n-k}:\qquad&=\sum_{i=0}^{n-1}\binom{n-1}{k}B_k
\end{aligned}
$$

我们可以在 $\mathcal{O}(m^2)$ 的时间内求出 $B_x$。

分析部分很长，代码却很简单，总的时间复杂度是 $\mathcal{O}(m^2+mn)$ 的，具体细节可以参见示例代码。

```cpp
#include <bits/stdc++.h>
using i64 = long long;

const int N = 55, M = 1010, mod = int(1e9) + 7;
int n, m;
std::map<i64, int> mp;
char s[M];
i64 f[M];
int C[M][M], B[M];

inline int Add_eq(int &x, const int &y)
    {if ((x += y) >= mod) x -= mod; return x;}
inline int Add(const int &x, const int &y)
    {if (x + y >= mod) return x + y - mod; return x + y;}
inline int Neg(const int &x)
    {return x ? (mod - x) : 0;}
void prework(int up)
{
    for (int i = 0; i <= up; ++ i)
        C[i][0] = C[i][i] = 1;
    for (int i = 1; i <= up; ++ i)
        for (int j = 1; j <= up; ++ j)
            C[i][j] = Add(C[i - 1][j - 1], C[i - 1][j]);
    B[0] = 1;
    for (int i = 1; i <= up; ++ i)
        for (int j = 0; j < i; ++ j)
            Add_eq(B[i], 1ll * C[i - 1][j] * B[j] % mod);
    return;
}

int main(void)
{
    prework(M - 1);
    
    scanf("%d%d", &m, &n);
    for (int i = 0; i < n; ++ i)
    {
        scanf("%s", s);
        for (int j = 0; j < m; ++ j)
            f[j] |= (i64(s[j] == '1') << i);
    }
    for (int j = 0; j < m; ++ j) ++ mp[f[j]];
    int ans = 1;
    for (auto it = mp.begin(); it != mp.end(); ++ it)
        ans = 1ll * ans * B[it -> second] % mod;
    printf("%d\n", ans);
    
    return 0;
}
```








---

## 作者：daniEl_lElE (赞：3)

考虑 $S$ 中至少有哪些数。

首先感性理解，对于任意两个二进制位使得他们在这些数中出现情况不一样，总能通过一些方式弄出所有两个位置相等/不等的数。而对于两个二进制位使得他们在这些数中出现情况一样，他们总是一起变动。也就是说，如果本质不同的出现情况有 $p$ 钟，那么 $S$ 中最少有 $2^p$ 个数。

总共会有多少种不同的 $S$ 呢？我们考虑可以将出现情况相同的位置拆开，允许他们不同。也就是说假设某一种出现的情况共有 $k$ 位，我们可以将 $k$ 位拆成若干个强制相同的部分。

如何计算有多少种不同的拆分方案？考虑 $dp_i$ 表示拆 $i$ 个的方案数。暴力枚举并上一个 $j$ 个组成的强制相同部分，容易得到：

$$dp_i\times\binom{i+j-1}{i}\to dp_j$$

最后根据乘法原理将所有出现情况的答案乘起来即可。总复杂度 $O(m(n+m))$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
#define min(i,j) ((i<j)?i:j)
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int dp[1005],C[1005][1005],ans[1005];
map<int,int> mp;
int val[1005];
signed main(){
	for(int i=0;i<=1000;i++) C[i][0]=1;
	for(int i=1;i<=1000;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	dp[0]=1;
	for(int i=0;i<=1000;i++){
		for(int j=1;i+j<=1000;j++){
			(dp[i+j]+=dp[i]*C[i+j-1][j-1])%=mod;
		}
//		cout<<dp[i]<<" ";
	}
	int n,m,ans=1; cin>>n>>m;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			char c; cin>>c;
			val[j]+=(1<<(i-1))*(c-'0');
		}
	}
	for(int i=1;i<=n;i++) mp[val[i]]++;
	for(int i=1;i<=n;i++) (ans*=dp[mp[val[i]]])%=mod,mp[val[i]]=0;
	cout<<ans;
	return 0;
}
```

---

## 作者：MyukiyoMekya (赞：3)

先不考虑 $T$ 的限制，考虑什么样的 $S$ 是合法的。

首先我们可以通过与和取反来凑出或：$x\operatorname{or} y=\sim((\sim x)\operatorname{and}(\sim y))$，$\sim$ 表示按位取反。异或差不多。

设 $f(x)$ 表示所有 $S$ 中 $x$ 位为 $1$ 的数的 $\operatorname{and}$ 和，那么假设 $f(x)=2^x \operatorname{or} 2^{x_1}\operatorname{or}2^{x_2}\operatorname{or}\cdots \operatorname{or}2^{x_k}$，

特别的，若 $S$ 中不存在 $x$ 位为 $1$ 的数，$f(x)=0$。

考虑集合 $S$ 一个 $f(x)=2^{x}\operatorname{or}2^{x_1}\operatorname{or}\cdots $，但是 $f(x_1)$ 里面不包含 $2^x$ ，

那么直接把 $f(x)$ 和 $f(x_1)$ 异或起来就可以造出一个有 $2^x$  但没有 $2^{x_1}$ 的数，那么就是说 $f(x)$ 不应该包含 $2^{x_1}$。

所以说这种情况下 $f(x)\operatorname{and} f(x_1)=0$。当然，如果 $f(x)=f(x_1)$ ，那就不存在这种冲突了。

那么就相当于把 $f(1\sim m)$ 划分为若干个集合，方案数就是 $Bell$ 数 $B_m$。

现在可以发现，若 $S$ 中的 $x_1,x_2,\cdots ,x_k$ 位在所有数中要么同为 $1$ ，要么同为 $0$ ，也就是说相同，那么他们的 $f$ 相等。

那么要求 $T\subseteq S$ 也就是说一开始已经限定好了哪些 $f(x)$ 一定不能相等。

那么就直接算一下一开始被划分为哪些联通块，然后每个联通块内分别算一下 $Bell$ 数乘起来就好。

代码可以参考另一篇题解。[mycodelink](https://codeforces.com/contest/908/submission/129719594)

---

## 作者：A_zjzj (赞：3)

### 一道$bell$数题：

[贝尔数-百度百科](https://baike.baidu.com/item/%E8%B4%9D%E5%B0%94%E6%95%B0/9227873?fr=aladdin)

预处理出$bell$数。

我用的这个递推式:

$$B_{n+1}=\sum\limits_{k=0}^{n}C_{n}^k\times B_k$$

然后，如果每个数都有几位是一样的，

（例如样例每个数第一位和第二位一样，第三位和第五位一样，第三位一样(~~这不废话~~)，不妨设设有$a$位相同），

然后就可以直接乘上一个$B_a$

```cpp
#include<cstdio>
#include<map>
#define ll long long
#define mod 1000000007
using namespace std;
int n,m;
ll a[1001],bell[1001],c[1001][1001],x;
map<ll,int>k;
int main() {
	scanf("%d%d",&m,&n);
	for(int i=0;i<=m;i++){
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)scanf("%1lld",&x),a[j]|=(x<<i);
	for(int i=0;i<m;i++)k[a[i]]++;
	bell[0]=1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<i;j++){
			bell[i]=(bell[i]+c[i-1][j]*bell[j]%mod)%mod;
		}
	}
	ll ans=1;
	for(map<ll,int>::iterator i=k.begin();i!=k.end();i++)ans=ans*bell[(*i).second]%mod;
	printf("%lld",ans);
	return 0;
}
```

---

