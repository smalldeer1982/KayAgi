# Cipher

## 题目描述

题目翻译：

对于单词（字符串） $s$  ，保证它只由小写字母组成。

设 $ s$ 的长度为 $len$ ，下文单词（字符串）下标从 $1$ 开始.

如果一个词可以通过零次或多次运算转换成另一个词，则我们认为这两个词的意思是一致的。

运算仅仅包含以下两种方式。

- 方式一：指定任意一个位置 $p$ $(1 \le p \le len)$使 $s_p$ 上的字母变成 **字母表上** 的后一个字母(如 a 变成 b ，x 变成 y)，而 $s_{p+1}$ 则要变成 **字母表上** 的前一个字母(如 d 变成 c)。
- 方式二：指定任意一个位置 $p$ $(1 \le p \le len)$使 $s_p$ 上的字母变成 **字母表上** 的前一个字母，而 $s_{p+1}$ 则要变成 **字母表上** 的后一个字母。

你需要回答对于输入的单词，一共有多少种与它意思一致的单词。

另外，对于字母 a ，不能将它变成前一个字母（因为它在字母表上没有前一个字母），同理 字母 z 也不能变成后一个字母。

给出多个单词（字符串），你需要分别对它们做出回答。

## 样例 #1

### 输入

```
1
ab
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1
aaaaaaaaaaa
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
ya
klmbfxzb
```

### 输出

```
24
320092793
```

# 题解

## 作者：lenlen (赞：22)

### Problem

题目大意：给定一个字符串，每一次你可以选一个位置是其变成字母表上前一位，其后面一个位置变成字母表上后一位，或者反过来，问你可以变成多少个字符串（不算原来的）。

数据范围： $t \leq 10^4,n \leq 100$。

### Solution

大佬讲的容斥我不会，所以只好用 DP 了。

首先这个题目我们可以发现将 $[a,z]$ 转化为 $[1,26]$ 的话，容易发现它们的和是不变的。而容易想到，我们可以给每一位 $+1$，后一位 $-1$ 或者当前位 $-1$，后一位 $+1$ 相当于只要保证和不遍的任意一种状态我都能到达，所以题目变成了：给定一个数字 $s$，把他分成 $n$ 个 $[1,26]$ 之间的数字有多少种分法。

设 $dp_{i,j}$ 表示前 $i$ 个数用了 $j$ 的方案数，转移显然：

$$dp_{i,j}= \sum\limits_{k-1}^{26} dp_{i-1,j-k}$$

而这样的时间复杂度是 $O(26^2 n^2)$ 的，放在 $t$ 循环中肯定会超，而经过我们的研究，其实根输入的字符串没有很大关系，只根转换之后的值有关系，所以我们完全可以预处理出来，然后 $O(1)$ 查询。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2732,mod=1e9+7;
long long dp[102][N];
int n,t,sum;
string s;
int main()
{
	scanf("%d",&t);
    dp[0][0]=1;
    for(int i=1;i<=100;i++)
    for(int j=i;j<=26*i;j++)
    for(int k=1;k<=26&&k<=j;k++) dp[i][j]=(dp[i][j]+dp[i-1][j-k])%mod;
    while(t--)
    {
        cin>>s;sum=0;
        n=s.size();s='?'+s;
        for(int i=1;i<=n;i++) sum+=s[i]-'a'+1;
        printf("%lld\n",dp[n][sum]-1);
    }
}


```


---

## 作者：xyf007 (赞：14)

其实只是来提供复杂度更优的解法（

以下默认求解一个串，长度为 $n$。  
把 $\texttt{a,b,\ldots,z}$ 分别看成 $1,2,\ldots,26$ 的整数，让相邻位一个加一另一个减一的操作，整个字符串的和不变。同时我们还可以任意分配每一位上的值。  
因此本题可以转化成如下问题:
> 给定总和 $s$，求将其分成 $n$ 个 1~26 的整数之和的方案数。

其他题解都是使用 DP 求解，复杂度至少 $O(n^2)$。但是这就是一个容斥的经典题目，可以 $O(n)$ 解决。  
假设不考虑小于等于 $26$ 这一个限制，这就是一个求不定方程组的解的数量的问题，直接使用隔板法。现在要求每个数小于等于 $26$，我们钦定 $i$ 个数大于 $26$，剩下随意，贡献是 $(-1)^i$，相当于给 $i$ 个数预先分配 $26$ 再做正常的不定方程求解。故答案为
$$ \sum_{i=0}^n(-1)^i\binom{n}{i}\binom{s-26i-1}{n-1} $$
时间复杂度 $O(tn)$。
```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
constexpr int kMod = 1e9 + 7;
int t, fac[2601], inv[2601];
char s[101];
int Ksm(int a, int b)
{
    int s = 1;
    while (b)
    {
        if (b & 1)
        {
            s = s * static_cast<long long>(a) % kMod;
        }
        a = a * static_cast<long long>(a) % kMod;
        b >>= 1;
    }
    return s;
}
long long C(int x, int y)
{
    if (x < y || y < 0)
    {
        return 0LL;
    }
    return static_cast<long long>(fac[x]) * inv[x - y] % kMod * inv[y] % kMod;
}
int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    fac[0] = 1;
    for (int i = 1; i <= 2600; i++)
    {
        fac[i] = fac[i - 1] * static_cast<long long>(i) % kMod;
    }
    inv[2600] = Ksm(fac[2600], kMod - 2);
    for (int i = 2599; i >= 0; i--)
    {
        inv[i] = inv[i + 1] * static_cast<long long>(i + 1) % kMod;
    }
    std::cin >> t;
    while (t--)
    {
        std::cin >> (s + 1);
        std::size_t n = std::strlen(s + 1);
        int tot = 0, ans = 0, f = -1;
        for (size_t i = 1; i <= n; i++)
        {
            tot += s[i] - 'a' + 1;
        }
        for (size_t i = 0; i <= n; i++)
        {
            f *= -1;
            ans = (ans + f * C(n, i) * C(tot - 26 * i - 1, n - 1) % kMod + kMod) % kMod;
        }
        std::cout << (ans - 1 + kMod) % kMod << '\n';
    }
    return 0;
}
```

---

## 作者：fanypcd (赞：5)

如果将字符 $\texttt{a} - \texttt{z}$ 分别映射为 $[1,26]$ 的整数后，容易发现任意操作后整个字符串的和不变。

于是问题转化为求不定方程 $\sum \limits_{i = 1} ^{n} x_i = k$ 的正整数解个数，限制条件： $\forall x_i(1 \leq i \leq n),x_i \in \mathbb{N} \cap [1,26]$。

可以设状态 $f_{i,j}$ 表示 $i$ 个数，和为 $j$ 的合法的解的个数。

易得状态转移方程为：

$$f_{i,j} = \sum \limits_{k = 1} ^{26} f_{i - 1,j - k}$$

在回答询问之前预处理所有的 $f_{i,j}$，复杂度 $O(26\times n^2)$，然后 $O(q)$ 回答。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
const int mod = 1e9 + 7;
#define N 105
#define V 2605
int n, m;
char s[N];
int f[N][V];
void init()
{
	f[0][0] = 1;
	for(int i = 1; i <= N - 5; i++)
	{
		for(int j = i; j <= i * 26; j++)
		{
			for(int k = 1; k <= 26 && j - k >= 0; k++)
			{
				f[i][j] = (f[i][j] + f[i - 1][j - k]) % mod;
			}
		}
	}
	return;
}
signed main()
{
	init();
	int T;
	read(T);
	while(T--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		m = 0;
		for(int i = 1; i <= n; i++)
		{
			m += s[i] - 'a' + 1;
		}
		printf("%d\n", (f[n][m] - 1 + mod) % mod);
	}
	return 0;
}
```

---

## 作者：Daniel_yuan (赞：5)

#### 题意简述

有 $t\leq 10^4$ 组询问，每组询问给你一个长度小于等于 $100$ 的仅包含小写字母的字符串。

对于一个长度为 $n$ 的字符串，定义一次操作是选择一个数 $i$，满足 $1\leq i < n$，然后使 $s_i=s_i+1,s_{i+1}=s_{i+1}-1$ 或 $s_i=s_i-1,s_{i+1}=s_{i+1}+1$。需要保证操作之后 $s_i$ 和 $s_{i+1}$ 都还是小写字母。

你可以对该字符串做任意多次操作，问最后除了原始字符串外，还可以形成多少个本质不同的字符串。

定义两个字符串 $S,T$ 本质不同，是存在一个位置 $k$，使得 $S_k\not=T_k$。

#### 题解

乍一看操作只能选择两个相邻的位置，使得一个加一，另一个减一，实则不然。

假设我们想要让 $s_i$ 减一，$s_j$ 加一（$i<j$)，考虑证明只要在操作之后 $s_i$ 和 $s_j$ 都合法，那么这个操作一定可以被完成。

考虑找到一个小于 $j$ 的最大的 $k$，使得 $s_k\not=\rm{'a'}$，那么就可以通过几次操作使 $s_k$ 减一,$s_j$ 加一（因为 $(k,j)$ 中的字符都是 $\rm{'a'}$，所以中途不会不合法），那么问题就转化成了一个比之前规模更小的问题：让 $s_i$ 减一，$s_k$ 加一，且 $k<j$，那么直到某次选择的 $k=i$，就完成了这次操作。

所以现在问题就变成了，你可以任意选两个位置，在保证操作后序列合法的情况下，使得一个位置加一，另一个位置减一，问最终有多少种状态。

不难发现，无论怎么操作，这个序列所有位置的权值之和是不变的，所以如果 $A,B$ 长度相等，且 $A$ 中所有位置的权值之和等于 $B$ 中所有位置的权值之和，那么 $A,B$ 可以互相通过操作而得到。

那么 DP 式子就逐渐清晰了。考虑从前往后填字符，设 $f[len][res]$ 表示当前剩余 $len$ 个空还没填，剩下的权值和为 $res$ 的方案数，转移就直接枚举这一位填什么字符即可。状态数 $O(26len^2)$，转移 $O(26)$，所以单次复杂度是 $(26len)^2$ 。

这样跑多组数据显然过不了，但是可以发现，DP 数组是可以共用的，那么多测的时候不清空就好了 ~~（多测清空反而会导致 TLE）~~

代码如下，写的是记忆化搜索：
```cpp

#include <bits/stdc++.h>
#define RI register int
typedef long long LL;

#define FILEIO(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

using namespace std;

int const MAXN = 105, mod = 1e9 + 7;
int f[MAXN][MAXN * 26];
char s[MAXN];

int DP(int now, int res) {
  if (res < 0) return 0;
  if (!now) return !res;
  if (f[now][res] != -1) return f[now][res];
  f[now][res] = 0;
  for (RI i = 0; i < 26; ++i)
    (f[now][res] += DP(now - 1, res - i)) %= mod;
  return f[now][res];
}

int main() {
  
#ifdef LOCAL
  FILEIO("a");
#endif

  int T; cin >> T;
  memset(f, -1, sizeof(f));
  while (T--) {
    cin >> (s + 1);
    int len = strlen(s + 1), sum = 0;
    for (RI i = 1; i <= len; ++i)
      sum += s[i] - 'a';
    cout << (DP(len, sum) + mod - 1) % mod << endl;
  }

  return 0;
}

// created by Daniel yuan
/*
     ________
    /        \
   / /      \ \
  / /        \ \
  \            /
   \  ______  /
    \________/
*/


```

---

## 作者：_Spectator_ (赞：4)

[可能更好的食用体验](/blog/523641/CF156C) $|$ 
[题目传送门](/problem/CF156C) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------

${\large\color{#00CD00}\text{思路}}$

首先为了方便处理可以把字母映射成 $1\sim26$ 的整数。

然后不难发现，如果按照题目的方式变换一个字符串，这些整数的**和**都是始终不变的。我们令这个和为 $\operatorname{Sum}(s)$。也就是说，两个字符串 $s_1$ 和 $s_2$“意思是一致的”，当且仅当 $|s_1|=|s_2|$ 且 $\operatorname{Sum}(s_1)=\operatorname{Sum}(s_2)$。

然后考虑把 $\operatorname{Sum}(s)$ 拆分成 $n$ 个正整数之和有几种方式。根据小学的组合数学知识，可以想到使用**隔板法**。

[隔板法说明，会的可不看](/paste/qcuec94f)

但是直接算组合数显然是错的。因为当 $\operatorname{Sum}(s)$ 很大时，组合数会考虑到所有的情况，而这时**考虑到的数可能会大于** $26$，也就不能用字母表示出来了。

但是我们还不用彻底放弃隔板法这个思路。~~经过机房大佬的指点~~还可以使用 dp 处理情况总数！我们定义 $f_{i,j}$ 为前 $i$ 个小球，插了 $j$ 块板得到的情况总数。那么状态转移方程为：
$$f_{i,j}=\sum\limits_{k=1}^{\min(i,26)}f_{i-k,j-1}$$

即：枚举一个最多为 $26$ 的区间长度 $k$，$f_{i,j}$ 就只能由这些区间内的状态转移过来。

这样做的时间复杂度为 $O(|\Sigma|^2\times n^2)$，其中 $|\Sigma|$ 表示的是字符集大小，在这里是 $26$。如果每次询问都做一遍的话显然会超时。但是由于 $f$ 与实际数据的大小并无关系，所以只需要在程序开始时做一遍预处理，询问时 $O(1)$ 查询即可。

具体实现细节详见代码。

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long T,n,sum,ans;
int f[2605][105];
char s[105];
void init() //预处理出 f 的值
{
	f[0][0]=1;
	for(int i=1; i<=2600; i++)
		for(int j=1; j<=min(i,100); j++) //注意循环的范围
			for(int k=1; k<=min(26,i); k++)
				f[i][j]=(f[i][j]+f[i-k][j-1])%mod; //记得模
} //这里理论上还可以用一个前缀和优化至 O(26*n²)。但是由于我懒所以就懒得搞了（划掉）
int main()
{
	init();
	cin>>T;
	while(T --> 0)
	{
		cin>>s;
		sum=0,n=strlen(s);
		for(int i=0; i<n; i++) sum+=s[i]-96; //将字母映射成数字并求和
		cout<< f[sum][n]-1 << endl; //-1是减掉自己
	}
	return 0;
}
```

---

## 作者：是个汉子 (赞：3)

[洛谷题目](https://www.luogu.com.cn/problem/CF156C)	[CF原题](http://codeforces.com/problemset/problem/156/C)

见过计数 DP，也见过字符串的计数 DP，但是这样的是第一次见。

### Solution

看到要求方案数，那么一定是计数 DP了。~~这字符串你还想用组合数？详情请见[这个](https://www.luogu.com.cn/blog/xyf007/solution-cf156chttps://www.luogu.com.cn/blog/xyf007/solution-cf156c)~~

但是设计什么状态能够得到最后答案呢？限制有点多诶^_~

发现题面中的两种运算都是**对称**的，一个往字母表后，另一个必定往前。

等等，字母表？ ASCII 码？

哦~一个 ASCII 码增加 $x$ ，另一个减少 $x$ 吖(oﾟvﾟ)ノ（注意不是一个位置只能运算一次）。也就是说整个字符串的 ASCII 码之和是不变的。

那么可以设 $dp_{i,j}$ 表示长度为 $i$ ，ASCII 码之和为 $j$ 的方案数

可得一个显然的转移方程：
$$
dp_{i,j}=\sum_{k=\min(1,j-26)}^{26}dp_{i-1,j-k}
$$
而且，最最最重要的是我们得到的 $dp$ 数组是可以预处理出来的，不用每次查询现转移。

小细节：因为题目要求的是**一共有多少种与它意思一致的单词**，所以要减去它本身，即 $-1$ 

### Code

```c++
#include<bits/stdc++.h>

using namespace std;
const int mod=1e9+7;
int dp[110][3010],t,sum;
string s;

int main(){
    scanf("%d",&t);
    for(int i=1;i<=26;i++) dp[1][i]=1;
    for(int i=2;i<=101;i++)
        for(int j=i;j<=26*i;j++)
            for(int k=max(1,j-26);k<=j-1;k++)
                dp[i][j]=(dp[i][j]+dp[i-1][k])%mod;
    while(t--){
        cin>>s;
        sum=0;
        for(int i=0;i<s.size();i++) sum+=s[i]-'a'+1;
        printf("%d\n",(dp[s.size()][sum]-1)%mod);
    }
    return 0;
}
```



---

## 作者：xfrvq (赞：2)

[$\tt Link$](/problem/CF156C)。

首先我们定义一种映射 $\mathsf a\to1,\mathsf b\to2,\cdots$。

然后你会发现这个字符串无论怎么变，其每个字符映射后和都不变。

然后还可以发现映射后和与它相同的字符串都可以由它变到。

方法很简单：对于 $s,t$，分别让 $s$ 从左往右每一位变成 $t$ 的对应位。

---

简单转化后问题变成：求不定方程

$$x_1+x_2+\cdots+x_n=s$$

的解个数。

其中 $n$ 代表字符串长度，$s$ 代表字符串映射后的和。并且 $x_i\in[1,26]$。

我们先看没有值域限制。此时理解为有 $s$ 个物品排在一起，现在要在其中 $s-1$ 个空隙中放入 $n-1$ 个隔板，答案是 $\displaystyle\binom{s-1}{n-1}$。

然后有值域限制，这时我们知道容斥的关键结论：

> **至少一个满足的答案，减去至少两个满足的答案，加上至少三个满足的答案，以此类推，就是全部的答案。**

这里就是 **至少 $\bm k$ 个（大于 $\bm{26}$）的答案**。我们发现它实际上就等价于：先让 $s$ 减去 $26k$，然后剩下的在做隔板法（相当于随意，怎么样都行），即

$$\binom{n}{k}\binom{s-26k-1}{n-1}$$

前者是在 $n$ 个里选出 $k$ 个来减去 $26$，后面的就是正常的隔板法。

最后的答案就是

$$\sum_{k=0}^n\binom{n}{k}\binom{s-26k-1}{n-1}(-1)^k$$

预处理阶乘算组合数，做完了。

---

## 作者：vvauted (赞：2)

## Solution of CF156C

记 $s_i$ 的编号为 $f(s_i)$，易观察得两个操作后 $\sum f(s_i)$ 不变，且可以通过两个操作使得任意一对 $(i,j)$，使 $f_i$ 增 $1$，$f_j$ 减 $1$，则问题可以转化为：

> 有一个数 $M=\sum f(s_i)$，把它分解成 $N$ 个可重数字，且这些数字在 $[1,C]$ 中，求分解方案。

运用一点生成函数知识，构造：

$$f(x)=
\sum_{i=1}^C x^i$$

那么答案则为：

$$[x^M]f^N(x)$$

显然 $\deg f^N =CN$，我们有通过多项式 $\ln,\exp$ 最快 $O(TCN\log CN)$ 计算出答案的做法，通过此题绰绰有余，但是出题人放过了 $O(T(CN)^2)$ 的 $dp$ 做法，于是我们可以尝试使用多项式暴力乘法通过。

显然只需对 $i\in[1,\max N]$，预处理 $f^i(x)$ 即可，那么我们的复杂度即为 $O(n(CN)^2+Tn)$，可以通过此题。

```cpp
#include <bits/stdc++.h>
#define Maxn 3005
#define Nep(i, l, r) for(int i = l; i != r; ++ i)
#define Rep(i, l, r) for(int i = l; i <= r; ++ i)
#define rep(i, l, r) for(int i = l; i < r; ++ i)
#define Lep(i, l, r) for(int i = l; i >= r; -- i)
#define lep(i, l, r) for(int i = l; i > r; -- i)
#define Max(a, b) a = std :: max(a, b)
#define ll long long
#define ull unsigned long long
#define int long long

const int mod = 1e9 + 7;

int read() {
	int x = 1, res = 0, ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') x = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
	return x * res;
}

int lim;
int add(int x, int y) { return (x + y) % mod; }
int mul(int x, int y) { return (x * y) % mod; }

struct poly {
    int x[Maxn], siz;

    friend poly operator * (poly x, poly y) {
        poly z = {}; z.siz = x.siz + y.siz;
        Rep(i, 0, z.siz) Rep(j, 0, i) z.x[i] = add(z.x[i], mul(x.x[j], y.x[i - j]));
        return z; 
    }
}A;

poly P[101];

signed main() {
    int t = read();
    Rep(i, 1, 26) P[1].x[i] = 1; P[1].siz = 26;
    Rep(i, 2, 100) P[i] = P[i - 1] * P[1];
    
    while(t --) {
        std :: string s; std :: cin >> s; int l = s.size();
        int n = 0; rep(i, 0, l) n += s[i] - 'a' + 1;
        printf("%lld\n", P[l].x[n] - 1);
    }
}
```


---

## 作者：lgswdn_SA (赞：1)

这道题其实并不难。

有一个熟为人知地结论：对于一个序列，如果允许相邻两个数交换，我们就可以类似地，通过这种方法，让任意两个数交换。这道题也一样，可以类似的推出这样一个结论：对于一个序列，如果允许相邻两个数一个加一一个减一，我们就可以类似于传递，让任意两个数一个数加一一个数减一。

有了这个小结论，我们可以发现，只要新序列字母之和（若 a 代表 1，b 代表 2 以此类推）和原序列字母之和一样，我们总是可以通过这种操作来让他们意思一致。

于是现在问题就变成了，给定一个 sum，问有多少个长度为  $n$ 的字母序列的字母之和为 sum，即一个整数拆分问题。复杂度 $O(Tn^226^2)$

还有一个在CF中不常有的技巧：我们并不需要每一个数据都算一遍 DP，在一开始与计算一下就行了。所以复杂度变成了 $O(n^226^2)$，方可过这道题目。


```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=109,M=2609,mod=1000000007;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int T,n,f[N][M];
char c[N];

signed main() {
	T=read();
	f[0][0]=1;
	rep(i,1,100) {
		rep(j,1,2600) {
			rep(k,1,min(j,26ll)) {
				f[i][j]=(f[i][j]+f[i-1][j-k])%mod;
			}
		}
	}
	while(T--) {
		scanf("%s",c+1);
		int n=strlen(c+1),sum=0;
		rep(i,1,n) sum+=c[i]-'a'+1;
		printf("%lld\n",f[n][sum]-1);
	}
	return 0;
}
```

---

## 作者：NaN_HQJ2007_NaN (赞：0)

容易发现，如果把字母表映射到 $[1,26]$ 上，那么无论怎么操作总和都不变。

于是可已将问题转化为：有多少种长度为 $n$ 的序列，满足每个元素在 $[1,26]$ 之间，总和为 $sum$。

定义 $f_{i,j}$ 表示处理到第 $i$ 个元素，总和为 $j$ 的合法方案数。

转移方程为 $f_{i,j}=\sum\limits_{k=1}^{26}f_{i-1,j-k}$，其中 $f_{0,0}=1$。

复杂度 $O(n^226^2)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100+5,mod=1e9+7;
ll T,f[N][27*N];
string s;
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>T;
  f[0][0]=1;
  for(int i=1;i<=100;++i){
    for(int j=1;j<=2600;++j){
      for(int k=1;k<=min(26,j);++k){
        f[i][j]=(f[i][j]+f[i-1][j-k])%mod;
      }
    }
  }
  while(T--){
    cin>>s;
    ll sum=0,len=s.size();for(int i=0;i<len;++i)sum+=s[i]-'a'+1;
    cout<<f[len][sum]-1<<endl;
  }
  return 0;
}

```


---

## 作者：WZKQWQ (赞：0)

个人建议评绿。

首先我们可以把字符串看成每个元素在 $[0,25]$ 中的数组，原题面的操作可以认为是任意一个加，任意一个减，因为可以连加连减。至于遇到 $0$ 或 $25$ 可以分割操作（一个操作变两个），所以等于把 $x$ 个球分配到 $n$ 个盒子，球相同盒子不同且每个盒子最多 $25$ 个球。

然后就是简单的 $\text{DP}$ 了，设 $f_{i,j}$ 是 $i$ 个盒子 $j$ 个球的方案数，转移显然，然后先预处理再读入字符串做，复杂度 $O((26n)^2 + Tn)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7;
int T;
string s;
int n,f[105][2505];
int main(){
	cin >> T;
	f[0][0] = 1;
	for(int i = 1;i <= 100;++i)
		for(int k = 0;k < 26;++k)
			for(int j = k;j <= 2500;++j){
				f[i][j] += f[i - 1][j - k];
				if(f[i][j] >= P) f[i][j] -= P;
			} 
	while(T--){
		cin >> s;
		n = s.size();
		int tmp = 0;
		for(int i = 0;i < n;++i) tmp += s[i] - 'a';
		cout << f[n][tmp] - 1 << endl;
	}
	return 0;
}
```


---

## 作者：Tenshi (赞：0)

~~一开始想了一个复杂度爆炸的 DP~~

## 分析

首先考察题目的性质：

方便起见，将字符看成是 $[0,25]$ 的值。

注意到操作可以等价于选择任意两个下标，然后对应的两个值一加一减或者一减一加。

这样的操作显然不会改变字符串的**值和**（也就是字符串中每个字符对应的值的和）

进一步地，可以发现答案就是与当前字符串值和（记为 $val$）相等的字符串个数（当然因为当前字符串本身不计入，所以答案即为所有合法且值和为 $val$ 的字符串个数减 $1$）

> 这里合法字符串就是每个字符为小写字符的字符串。

考虑 DP 求解：

记长 $i$ 个字符，值和为 $j$ 的合法字符串有 $f(i, j)$ 个。

 那么有转移：$f(i, j) = \sum_c f(i-1, j-c)$，其中 $c\in [0, 25]$ 且 $j-c \geq 0$。



```cpp
// Problem: Cipher
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF156C
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
 
#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define pb push_back
#define all(x) (x).begin(), (x).end()
 
#define x first
#define y second
using pii = pair<int, int>;
using ll = long long;
 
inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=110, mod=1e9+7;

int f[N][2605];

int add(int x, int y){
	return x+y>=mod? x+y-mod: x+y<0? x+y+mod: x+y;
}

void init(){
	f[0][0]=1;
	rep(i, 1, 100){
		rep(j, 0, 2600){
			rep(c, 0, 25){
				if(j-c>=0) f[i][j]=add(f[i][j], f[i-1][j-c]);
			}
		}
	}
}

void solve(){
	string s; cin>>s;
	int n=s.size();
	int val=0;
	for(auto i: s) val+=(i-'a');
	cout<<add(f[n][val], -1)<<endl;
}

signed main(){
	init();
	int cs; cin>>cs;
	while(cs--) solve();
	return 0;
}
```



---

## 作者：qwq___qaq (赞：0)

首先我们将字母转化为数字，也就是说，$a\rightarrow1,b\rightarrow2,\cdots,z\rightarrow26$。

容易发现，无论是加 $1$ 还是减 $1$，这个串所有位置上的数字之和是不变的，也就是说，我们需要用设 $s$ 中所有元素的总和为 $sum$，长度为 $len$，那么我们就可以转化题目为求长度为 $len$ 的总和为 $sum$ 的所有元素均小于等于 $26$ 的数字串的方案数。

容易想到 dp：设 $dp_{i,j}$ 表示长度为 $i$ 元素和为 $j$ 的方案数，因为 $i$ 可以选择 $[1,26]$，所以 $dp_{i,j}\gets\sum\limits_{k=1}^{26}dp_{i-1,j-k}$。

答案就是 $dp_{len,sum}$，因为数据数量较多，所以要先初始化 dp。

---

## 作者：Yansuan_HCl (赞：0)

把 `a~z` 看成 $1$ 到 $26$ 的整数。可以手玩一下，发现性质：对于**源序列**和**目标序列**合法的操作，一定存在一种操作方案。感性理解类似于“传递”。[特殊情况的例子。](https://www.luogu.com.cn/paste/mu7jsau2)

于是，问题转化为：有 $t$ 个 $1$，要求分配给 $n$ 个数，使得每个数在 $[1,26]$ 之间。

假如没有 $26$ 的上限，则显然可以插板。

直接计数我不会，考虑容斥。先算出没有上限的，再减去**至少有 $1$ 个数**大于 $26$ 的，再加上**至少有 $2$ 个数**大于 $26$ 的……以此类推，最终 $\forall k$ **恰有 $k$ 个数大于** $26$ 的方案都会被减去。

至少有 $i$ 个数，先在 $n$ 个数中选出 $i$ 个大于 $26$ 的，再“分配”出 $26i$ 个 $1$ 给这些数，剩下的数插板。答案即为

$$\sum_{i=0}^n(-1)^{i+1}\binom{n}{i}\binom{t-26i-1}{n-1}$$

可以 $O(n)$ 计算。

[代码。](https://www.luogu.com.cn/paste/kg846g5h)

---

## 作者：laboba (赞：0)

看了下题解里只有 $O((26\times n)^2)$  的 DP 和 $O(tn)$ 数学做法，这里给一个优化后 $O(26\times n^2)$ 的 DP。

首先分析题目中规定的操作，等价于求将给定的和划分为 $n$ 个 $1\sim 26$ 上的整数的方案数，严谨证明可以用数学归纳乱搞下。

容易想到 DP 的状态 $f_{i,j}$ 表示考虑到前 $i$ 个数，和为 $j$ 的方案数。然后枚举第 $i$ 位所填的数进行转移，可以得到柿子：$f_{i,j}=\sum\limits_{k=1}^{26}f_{i-1,j-k}$ 直接计算是 $O((26\times n)^2)$ 的。思考一下会发现对于 $f_{i,j},f_{i,j-1}...$，转移都需要计算 $f_{i-1,j-1},f_{i-1,j-2}...$ 等大量重叠部分的和，所以可以用前缀和优化掉一个 $26$。

考虑不使用前缀和的一种方法：还是因为上面所说的原因，想到能否直接从 $f_{i,j-1}$ 转移到 $f_{i,j}$。发现如果强制第 $i$ 位数属于范围 $[2,25]$，两者可以建立这样的一一映射：对于 $f_{i,j-1}$ 的每一种方案 $a_1,a_2...a_i$ 令 $a_1,a_2...a_{i-1}$ 不变、$a_i$ 变成 $a_i+1$ 就得到了 $f_{i,j}$ 的一种方案，限制范围 $[2,25]$ 是因为有 $f_{i,j}$ 中 $a_i=1$ 和 $f_{i,j-1}$ 中 $a_i=26$ 这两个特例，单独处理就能得到 $O(26\times n^2)$ 的柿子：$f_{i,j}=f_{i,j-1}+f_{i-1,j-1}-f_{i-1,j-27}$ 其中 $f_{i-1,j-27}$ 是指令 $a_i=26$ 时 $f_{i,j-1}$ 的方案数。

代码实现还是非常容易的：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int N=110,mod=1000000007;
long long f[N][N*27];
char ch[N];
int main(){
	for(int i=1;i<=26;i++)f[1][i]=1;
	for(int i=2;i<N;i++)
	for(int j=i;j<=i*26;j++){
		f[i][j]=f[i][j-1]+f[i-1][j-1];
		if(j>=27)f[i][j]-=f[i-1][j-27];
		f[i][j]%=mod;
	}
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%s",ch+1);
		int sum=0,n=strlen(ch+1);
		for(int i=1;i<=n;i++)sum+=ch[i]-'a'+1;
		printf("%d\n",(f[n][sum]+mod)%mod-1);
	}
}
```


---

## 作者：C　C　A (赞：0)

$$\Large \rm [CF156C]Cipher$$

$\quad$将这个字符串转换成一个长度为 $n$，每一个元素都是 $0\sim 25$ 的整数的序列，记所有数的和为 $S$.

$\quad$可以知道，两个字符串 “意思一致” 当且仅当它们转换成序列后的 $n$ 和 $S$ 相等。

> $\mathcal{Proof}$:
> $\quad$必要性显然。考虑 “同义变换” 时每一个 $1$ 的位置变动，由其每次都是移向相邻位置可知它能遍历到所有位置，所以每一种 $n$ 和 $S$ 相同的情况都可以通过 “同义变换” 得到，充分性得证。

$\quad$于是问题转化成 : 求如下不定方程的解数 ：

$$x_1+x_2+\cdots +x_n=S~(\forall i,x_i\in [0,25])$$

$\quad$考虑对每个未知数构造生成函数 $f(x)=\sum_{i=0}^{25}x^i$，而方案数即为生成函数 $F(x)=[f(x)]^n=\sum_{i=0}^{\infty}a_ix^i$ 第 $S$ 项的系数 $a_S$.

$$F(x)=[f(x)]^n$$

$$=[\sum_{i=0}^{25}x^i]^n$$

$$=\left(\frac{1-x^{26}}{1-x}\right)^n$$

$$=(1-x^{26})^n\times \frac{1}{(1-x)^n}$$

$$=\left[\sum_{i=0}^n\dbinom{n}{i}(-1)^ix^{26i}\right]\times \left[\sum_{i=0}^{\infty}\dbinom{n-1+i}{n-1}x^i\right]$$

$$\therefore a_S=\sum_{i=0}^{\lfloor\frac{S}{26}\rfloor}\dbinom{n}{i}(-1)^i\dbinom{n-1+S-26i}{n-1}$$

$\quad$时间复杂度 $\Theta(Tn)$.

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define dep(i, r, l) for (int i = r; i >= l; --i)

const int N = 1e6 + 10, mod = 1e9 + 7;

int T, n, S, fac[N], inv[N], ans;
char s[N];

int Pow (int a, int k) {
	if (k == 1) return a;
	int S = Pow(a, k >> 1);
	if (k & 1) return 1ll * S * S % mod * a % mod;
	else return 1ll * S * S % mod;
}

int C (int n, int m) {
	if (n < m) return 0;
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main () {

	fac[0] = 1; rep(i, 1, N - 1) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = Pow(fac[N - 1], mod - 2);
	dep(i, N - 2, 0) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod; 

	scanf("%d", &T); while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1), S = ans = 0;
		rep(i, 1, n) S += s[i] - 'a';
		rep(i, 0, S / 26) ans = (ans + (i & 1 ? -1ll : 1ll) * C(n, i) * C(n - 1 + S - 26 * i, n - 1) % mod + mod) % mod;
		printf("%d\n", (ans - 1 + mod) % mod);
	}

	return 0;
}
```

---

