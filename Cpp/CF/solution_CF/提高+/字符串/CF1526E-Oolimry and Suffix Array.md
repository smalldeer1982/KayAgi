# Oolimry and Suffix Array

## 题目描述

Once upon a time, Oolimry saw a suffix array. He wondered how many strings can produce this suffix array.

More formally, given a suffix array of length $ n $ and having an alphabet size $ k $ , count the number of strings that produce such a suffix array.

Let $ s $ be a string of length $ n $ . Then the $ i $ -th suffix of $ s $ is the substring $ s[i \ldots n-1] $ . A suffix array is the array of integers that represent the starting indexes of all the suffixes of a given string, after the suffixes are sorted in the lexicographic order. For example, the suffix array of oolimry is $ [3,2,4,1,0,5,6] $ as the array of sorted suffixes is $ [\texttt{imry},\texttt{limry},\texttt{mry},\texttt{olimry},\texttt{oolimry},\texttt{ry},\texttt{y}] $ .

A string $ x $ is lexicographically smaller than string $ y $ , if either $ x $ is a prefix of $ y $ (and $ x\neq y $ ), or there exists such $ i $ that $ x_i < y_i $ , and for any $ 1\leq j < i $ , $ x_j = y_j $ .

## 说明/提示

In the first test case, "abb" is the only possible solution.

In the second test case, it can be easily shown no possible strings exist as all the letters have to be equal.

In the fourth test case, one possible string is "ddbacef".

Please remember to print your answers modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3 2
0 2 1```

### 输出

```
1```

## 样例 #2

### 输入

```
5 1
0 1 2 3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
6 200000
0 1 2 3 4 5```

### 输出

```
822243495```

## 样例 #4

### 输入

```
7 6
3 2 4 1 0 5 6```

### 输出

```
36```

# 题解

## 作者：namelessgugugu (赞：11)

#### 题意
给定长度为 $n$，字符集大小为 $k$ 的字符串的 $sa$ 数组（后缀数组）。求符合条件的字符串 $S$ 的个数，对 $998244353$ 取模。

$1 \leqslant n,k \leqslant 2 \times 10^5$。
#### Sol
先由 $sa$ 数组推出 $rk$ 数组，不难发现，如果 $rk_i > rk_j$，则 $S_i \geqslant S_j$，问题在于能不能取等。考虑到如果取等，在 $i$ 和 $j$ 代表的后缀对比大小时，将会忽视相同的第一位，从第二位开始比较，因此取等的条件是 $rk_{i+1} > rk_{j+1}$。我们只需对所有 $sa_i,sa_{i+1}$ 进行比较，就能确定整个字符串任意两个字符的大小关系，而且肯定合法。

接下来就是计算方案数，假设有 $m$ 个字符可以与它在 $sa$ 中的前一个字符取等号。每次有一个取了等，值不同的字符就减少一个，设有 $i$ 个取等，剩下的都不取等，则方案数为 $\tbinom{m}{i} \tbinom{k}{n-i}$，其中前者是选 $i$ 个取等的方案数，后者是给 $n-i$ 个字符赋不同值的方案数。

总方案数为 $\sum\limits^m_{i=0} \tbinom{m}{i} \tbinom{k}{n-i}$。这个已经可以算了。

由于 $m \leqslant n$，当 $i > m$ 时 $\tbinom{m}{i} = 0$，因此可以写成 $\sum\limits^n_{i=0} \tbinom{m}{i} \tbinom{k}{n-i} = \tbinom{m+k}{n}$。计算这个更简单，时间复杂度 $O(n+k)$。

#### AC代码

```cpp
#include <cstdio>
const int N = 200005, mod = 998244353;
int n, k, m, sa[N], rk[N], inv[N], ans = 1;
int main(void)
{
	scanf("%d%d", &n, &k), rk[sa[0] = n+1] = 0, inv[1] = 1;
	for(int i = 1;i <= n;++i)
		scanf("%d", sa+i), rk[++sa[i]] = i;
	for(int i = 2;i <= n;++i)
		m += rk[sa[i]+1] > rk[sa[i-1]+1];
	for(int i = m+k;i > m+k-n;--i)
		ans = 1ll*ans*i%mod;
	for(int i = 2;i <= n;++i)
		ans = 1ll*ans*(inv[i] = 1ll*(mod-mod/i)*inv[mod%i]%mod)%mod;
		//计算逆元同时更新答案
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：pigstd (赞：5)

### [CF1526E](https://www.luogu.com.cn/problem/CF1526E)

vp 的时候看到后缀数组就直接跑路了，但是现在看来也不是很难（

下文中令 $sa_i$ 为给定的后缀数组，$rk_i$ 为 $sa_i$ 的反函数，即 $suf_i$ 的排名，$suf_i$ 表示后缀 $s_{i \dots n}$。

知道 $sa_i$ 可以直接求出 $rk_i$。对于 $sa_i$ 和 $sa_{i+1}$，那么有 $suf_{sa_i} < suf_{sa_{i+1}}$，则有 $s_{sa_i} <$ 或 $\le s_{sa_{i+1}}$。

啥时候可以取到等号呢？如果 $s_{sa_i} = s_{sa_{i+1}}$ ，那么如果 $suf_{sa_i} < suf_{sa_{i+1}}$，则有 $suf_{sa_i+1} < suf_{sa_{i+1}+1}$，即 $rk_{sa_i+1}<rk_{sa_{i+1}+1}$。这个也可以直接求出来，这样就可以求出有多少个 $i$ 可以取到等号，记为 $cnt$。

然后就可以枚举取到等号的个数 $i$，在 $cnt$ 个数中找到 $i$ 个取等号的方案数是 $\dbinom{cnt}{i}$，剩下 $n-i$ 个不取等的需要在 $k$ 个字符中选择 $n-i$ 个，而且选出给定的字符集后不难确定出所有的数，方案数就是 $\dbinom{k}{n-i}$，所以最后的答案就是 $\displaystyle \sum_{i=0}^{cnt} \dbinom{cnt}{i} \times \dbinom{k}{n-i}$。

实际上这个东西根据组合意义来看就等于 $\dbinom{k+cnt}{n}$，算是一个经典的 trick，但改变不了复杂度（

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define WT int T=read();while(T--) 
#define NO puts("NO");
#define YES puts("YES");
using namespace std;

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

const int Mod=998244353;
const int M=4e5+10;
int n,k,cnt,sa[M],rk[M],ans;
int fac[M],ifac[M];

int poww(int a,int b)
{
	int res=1;
	while(b)
	{
		if (b&1)res=res*a%Mod;
		a=a*a%Mod,b>>=1;
	}return res;
}
int inv(int x){return poww(x,Mod-2);}
int C(int m,int n)
{
	if (n<0||m<0||n>m)return 0;
	return fac[m]*ifac[m-n]%Mod*ifac[n]%Mod;
}

void init(int n)
{
	fac[0]=ifac[0]=1;
	for (int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%Mod,
		ifac[i]=inv(fac[i]);
}

signed main()
{
	n=read(),k=read();init(n+k);
	for (int i=1;i<=n;i++)sa[i]=read()+1,rk[sa[i]]=i;
	for (int i=1;i<n;i++)
		if (rk[sa[i]+1]<rk[sa[i+1]+1])cnt++;
	cout<<C(cnt+k,n)<<endl;
	return 0;
}
```



---

## 作者：FjswYuzu (赞：4)

知道后缀数组，我们可以求出每个后缀的排名，记为 $rk$。

考虑两个排名相邻的两个后缀，第一个字母分别为 $s_{sa_i},s_{sa_{i+1}}$。这两个字母的关系一定满足 $s_{sa_i}\leq s_{sa_{i}+1}$。

考虑这两个字母取等的条件，如果删去这两个字符串的第一个字符后，第一个字符串仍然小于第二个字符串就可以取等。注意到这两个字符串删去第一个字符后还是一个后缀串，因此可以直接用 $rk$ 比较。因此如果 $rk_{sa_i+1} < rk_{sa_{i+1}+1}$，这两个字符可以取等。

这样的话每个位置的字母大小关系已经被我们限制。这个限制形如一个链覆盖了 $1$ 到 $n$。每个限制都形似 $s_{p_i} < s_{p_{i+1}}$ 或者 $s_{p_i} \leq s_{p_{i+1}}$。我们现在已经算出了小于等于号的个数 $p$，并且知道 $s$ 的值域为 $k$。根据这个我们可以算出答案：
$$
\sum_{i=0}^p \dbinom{p}{i} \dbinom{k}{n-i}
$$
其表示，枚举用了的等号的个数，在 $p$ 个等号里面选 $i$ 个；这样的话我们选出的值共有 $n-p$ 个，需要在 $k$ 个值里面选。

可以直接算。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=998244353;
LL QuickPow(LL x,LL p)
{
	LL ans=1,base=x;
	while(p)
	{
		if(p&1)	ans=ans*base%MOD;
		base=base*base%MOD;
		p>>=1;
	}
	return ans;
}
LL fac[200005],ifac[200005];
LL C(LL n,LL m){return (n<m || m<0)?0:fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;}
LL n,k,sa[200005],rk[200005];
int main(){
	scanf("%lld %lld",&n,&k);
	for(LL i=1;i<=n;++i)	scanf("%lld",&sa[i]),++sa[i],rk[sa[i]]=i;
	LL equ=0;
	for(LL i=1;i<n;++i)	if(rk[sa[i]+1]<rk[sa[i+1]+1])	++equ;
	fac[0]=1;
	for(LL i=1;i<=200000;++i)	fac[i]=fac[i-1]*i%MOD;
	ifac[200000]=QuickPow(fac[200000],MOD-2);
	for(LL i=199999;~i;--i)	ifac[i]=ifac[i+1]*(i+1)%MOD;
	LL ans=0;
	for(LL i=0;i<=equ;++i)	ans=(ans+C(equ,i)*C(k,n-i)%MOD)%MOD;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：2)

## CF1526E 【Oolimry and Suffix Array】

### 题意

+ 长度为 $n$ 的字符串 $s$ 的编号为 $i$ 的后缀为 $s[i,n-1]$；
+ 把字符串 $s$ 的所有后缀按升序排序后，所有后缀对应的编号按后缀排序后的顺序组成的数组为字符串 $s$ 的后缀数组；
+ 给出一个长度为 $n$，字符集大小为 $k$ 的字符串的后缀数组，求有多少种可能的字符串；
+ $n,k\le2\times10^5$。

### 做法

要且只要所有大小相邻的后缀满足大小关系，整个字符串就是合法的。

如果后缀 $i$ 小于后缀 $j$，则 $s_i\le s_j$。如果 $s_i<s_j$，则一定满足后缀 $i$ 小于后缀 $j$；如果 $s_i=s_j$，只有后缀 $i+1$ 小于后缀 $j+1$ 时，才满足后缀 $i$ 小于后缀 $j$。综上，我们只需要知道后缀 $i+1$ 和后缀 $j+1$ 的大小关系就可以判断 $s_i=s_j$ 是否成立，而我们已经知道了后缀数组，所以不难判断。

由上，我们可以推出 $1\le s_{a_1}\le(<) s_{a_2}\le(<)\dots\le(<)s_{a_n}\le k$，此时每个位置的符号已经唯一确定，我们需要求多少个数组 $s$ 满足上式。

发现有两种符号不好处理，不妨把每个小于等于号后面所有数加上一，把小于等于号转换成小于号，原式等价于 $1<s_{a_1}<s_{a_2}<\dots<s_{a_n}<k+b$，$b$ 为原式中小于等于号的个数。

满足上述式子的方案数式经典的计数模型，答案为 $C_{k+b+n}^n$。

---

## 作者：sry_ (赞：2)

#### Oolimry and Suffix Array

##### 题意

给定 $n$ 与 $k$ 和一个长度为 $n $ 的后缀数组 $p_0,p_1,...,p_{n-1}$ 。

你需要求出有多少个当字符集 $\sum$ 为 $k$ 且长度为 $n$ 的字符串的后缀数组为 $p$ 。

$1\leq n,k\leq 200000$ 。

##### 题解

根据后缀数组的定义可得 $s[p_i:]<s[p_{i+1}:]$ ，则有 $s_{p_i}\leq s_{p_{i+1}}$ 。

考虑如何取得 $=$ 条件，假设 $s_{p_i}=s_{p_{i+1}}$ ，那么必须有 $s[p_{i}+1:]<s[p_{i+1}+1:]$ 。  

**简单来说：如果 $p_i+1$ 在 $p_{i+1}+1$ 的后面，则 $s_{p_i}\leq s_{p_{i+1}}$。否则 $s_{p_i}<s_{p_{i+1}}$** 。

这样就可以得到一条不等式链，而这也是**充要条件**。

试图证明这个事情：考虑将原不等式链看成在 $s_{p_0}<s_{p_1}<s_{p_2}<...<s_{p_{n-1}}$ 中添加等号。

我们需要证明对于 $\forall i,suf_{p_i}<suf_{p_{i+1}}$ ，这也是非常好证明的，虽然写不到卷子上（感觉不太直观）

如果 $s_{p_i}<s_{p_{i+1}}$ ，那么无需证明。

对问题迭代一次：由于 $suf_{p_{i}+1}<suf_{p_{i+1}+1}$ ，即 $s_{p_i+1}O_1 s_{x_1} O_2 s_{x_2} ...O_{t} s_{p_{i+1}+1}$ ，其中 $O\in \{<,\leq \}$ 。

若在 $O$ 中存在 $<$ 号，那么无需证明。

否则对问题在迭代一次，这次对 $(p_{i}+1,x_1),(x_1,x_2),...,(x_t,p_{i+1}+1)$ 一起迭代。

那么不等式链会形如 $s_{p_{i}+2}O...Os_{x_1+1}O...Os_{x_2+1}O......Os_{p_{i+1}+2}$ 。

容易发现在出现  $s_{p_{i}+x}> s_{p_{i+1}+x}$ 之前一定会出现一次 $<$ 号。

证毕。

那么就是朴素的计数环节，设在不等式链中有 $L$ 个 $\leq$ ，那么答案可以记为
$$
\sum_{i=0}^L \binom{L}{i}\binom{k}{N-i}=\binom{L+k}{N}
$$
时间复杂度 $\mathcal O(n)$ 。


---

## 作者：一之濑帆波 (赞：2)

[link](https://codeforces.com/contest/1526/problem/E)

> 题意：
>
> 给出字符串长 $n$ 和字符集大小 $k$，以及该字符串后缀排序后的 $sa$ 数组，求有多少种字符串能够生成这样的 $sa$ 数组。
>
> $1\le n,k\le 2\times 10^5$。

首先可以由 $sa$ 数组推出 $rk$ 数组。

约定 $s$ 为字符串，$s_i$ 是第 $i$ 个字符，$s[i:]$ 是以 $i$ 开头的后缀。

$sa$ 数组的每个后缀是按照字典序单调递增排列的，那么这些后缀的首字符也就呈单调不降排列。假设在 $sa$ 数组中 $s[i:]$ 和 $s[j:]$ 相邻，如何确定 $s_i$ 和 $s_j$ 满足 $<$ 或是 $\le$ 关系？

若 $rk(s[i+1:])>rk(s[j+1:])$，当且仅当 $s_i<s_j$ 成立；否则 $s_i\le s_j$。

于是我们可以得到 $s$ 每个字符之间的相对关系，然后在字符集上做一个 DP。

设 $f(n,i)$ 表示字符 $i$ 为当前最大字符时，长为 $n$ 的字符串的方案数，转移很简单，若为 $<$ 关系则 $f(n,i)=\sum_{j<i}f(n-1,j)$，若为 $\le$ 关系类似。

观察到这是一个做高维前缀和的过程，从生成函数的角度入手。

DP 初始值 $\forall i\in[0,k),f(1,i)=1$，生成函数为 $\dfrac{1}{1-x}$；$<$ 关系的转移就是乘 $\dfrac{x}{1-x}$，$\le$ 关系就是乘 $\dfrac{1}{1-x}$。设 $p$ 表示 $<$ 关系个数，$q$ 表示 $\le$ 个数，答案为
$$
\sum_{i=0}^{k-1}[x^i]\frac{1}{1-x}\left(\frac{x}{1-x}\right)^p\left(\frac{1}{1-x}\right)^q
$$
我们将最后的求和也化为生成函数，化简一下
$$
[x^k]\left(\frac{x}{1-x}\right)^{p+1}\left(\frac{1}{1-x}\right)^{q+1}
$$
最后化简得到
$$
[x^{k-p-1}]\left(\frac{1}{1-x}\right)^{p+q+2}
$$

---

求 $\left(\dfrac{1}{1-x}\right)^c$ 的第 $n$ 项系数：
$$
\left(\frac{1}{1-x}\right)^c=\left(1+x+x^2+x^3+\dots\right)^c
$$
这个生成函数的组合意义便是把一个数拆成 $c$ 个非负整数和的方案数。利用插板法可以得到
$$
[x^n]\left(\frac{1}{1-x}\right)^c=\binom{n+c-1}{c-1}=\binom{n+c-1}{n}
$$

---

所以答案为
$$
\binom{k+q}{k-p-1}
$$
线性处理逆元就可以 $\mathcal O(k+n)$ 解决。


**code**

```cpp
#include <bits/stdc++.h>

using i64 = long long;

const int P = 998244353;

int main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    std::vector<int> sa(n), rk(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> sa[i];
        rk[sa[i]] = i;
    }
    rk.push_back(-1);
    int p = 0, q = 0;
    for (int i = 1; i < n; ++i) {
        if (rk[sa[i - 1] + 1] > rk[sa[i] + 1]) ++p;
        else ++q;
    }
    int x = k + q, y = k - p - 1;
    if (x < 0 || y < 0 || x < y) {
        std::cout << 0 << '\n';
        return 0;
    }
    std::vector<int> inv(x + 1), fac(x + 1), ifac(x + 1);
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= x; ++i)
        inv[i] = (i64) (P - P / i) * inv[P % i] % P;
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= x; ++i) {
        fac[i] = (i64) fac[i - 1] * i % P;
        ifac[i] = (i64) ifac[i - 1] * inv[i] % P;
    }
    int ans = (i64) fac[x] * ifac[y] % P * ifac[x - y] % P;
    std::cout << ans << '\n';

    return 0;
}

```

---

## 作者：gan1234 (赞：0)

令 $s_i$ 表示从第 $i$ 位开始的后缀。

我们发现比较两个后缀 $s_i,s_j$ 相当于比较两个二元组 $(c_i,s_{i+1})$ 与 $(c_j,s_{j+1})$。当 $c_i\ne c_j$ 时，比较 $c_i$ 与 $c_j$，当 $c_i=c_j$ 时，比较 $s_{i+1} $ 与 $s_{j+1}$。

考虑从最小后缀开始一个一个填字母，当我们在填最小后缀 $s_i$ 时，我们必须要保证这个最小后缀比次小后缀 $s_j$ 小，如果 $s_{i+1}<s_{j+1}$，那么 $c_i\le c_j$，否则 $c_i<c_j$。

那么我们填字母是一个单调递增的过程，其中一些位置必须严格递增，一些不需要。

问题就转化成了：长度为 $n$，值域为 $k$ 的单调递增序列，其中有一些位置必须至少增加 $1$。我们可以提前将值域减去这些 $1$，这样我们就去除了这些限制。

令 $t$ 表示需要减一的数量。

求这个数列的方案数等价于求其差分数列方案数，也就是 $\sum^{n-1}_{i=1}x_i\le k-t-1,x_i\ge 0$ 的解数，考虑枚举 $\sum^{n-1}_{i=1}x_i$ 的值，用查板法求即可。

答案为：

$$\sum^k_{i=1}\binom{i+n-t-2}{n-1}=\binom{n+k-t-1}{n}$$

---

## 作者：lsj2009 (赞：0)

### Solution

很巧妙 & 套路组合！

感觉类似于 CF1558D。

首先根据 $sa$ 数组求出 $rk$。

注意到一个 $rk_i<rk_j$ 对应的是 $s_i\le s_j$，问题在于是否去等，我们发现，如果 $rk_{i+1}<rk_{j+1}$ 则哪怕 $s_i=s_j$，但是后面的大小仍然可以用来区分 $suf_i$ 和 $suf_j$ 的大小，所以 $s_i\le s_j$ 取等的条件是 $rk_{i+1}<rk_{j+1}$。

那么我们现在就得到了一个 $s_{sa_i}\le s_{sa_{i+1}}$ 的形式，然后知道了其中恰好有 $s=\sum\limits_{i=1}^{n-1} [rk_{sa_i+1}<rk_{sa_{i+1}+1}]$ 个 $\le$ 号。

不妨考虑将所有 $\le$ 号后的数全部加 $1$，则现在所有符号均变成了 $<$ 号，值域为 $k+s$，则答案为 $k+s\choose n$。

由于要求逆元，时间复杂度 $\Theta(n\log{V})$，线性逆元可以做到 $\Theta(n)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e5+5,MOD=998244353;
int qpow(int a,int b) {
	int res=1,base=a;
	while(b) {
		if(b&1)
			res=res*base%MOD;
		base=base*base%MOD; b>>=1;
	}
	return res;
}
int C(int n,int m) {
	if(n<m)
		return 0;
	int res=1;
	rep(i,1,m)
		res=res*(n-i+1)%MOD*qpow(i,MOD-2)%MOD;
	return res;
}
int sa[N],rk[N];
signed main() {
	int n,k;
	scanf("%lld%lld",&n,&k);
	rep(i,1,n) {
		scanf("%lld",&sa[i]);
		rk[sa[i]]=i;
	}
	int cnt=0;
	rep(i,1,n-1)
		cnt+=rk[sa[i]+1]<rk[sa[i+1]+1];
	printf("%lld\n",C(cnt+k,n));
    return 0;
}
```

---

