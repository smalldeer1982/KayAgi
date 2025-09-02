# New Year and the Permutation Concatenation

## 题目描述

Let $ n $ be an integer. Consider all permutations on integers $ 1 $ to $ n $ in lexicographic order, and concatenate them into one big sequence $ p $ . For example, if $ n = 3 $ , then $ p = [1, 2, 3, 1, 3, 2, 2, 1, 3, 2, 3, 1, 3, 1, 2, 3, 2, 1] $ . The length of this sequence will be $ n \cdot n! $ .

Let $ 1 \leq i \leq j \leq n \cdot n! $ be a pair of indices. We call the sequence $ (p_i, p_{i+1}, \dots, p_{j-1}, p_j) $ a subarray of $ p $ . Its length is defined as the number of its elements, i.e., $ j - i + 1 $ . Its sum is the sum of all its elements, i.e., $ \sum_{k=i}^j p_k $ .

You are given $ n $ . Find the number of subarrays of $ p $ of length $ n $ having sum $ \frac{n(n+1)}{2} $ . Since this number may be large, output it modulo $ 998244353 $ (a prime number).

## 说明/提示

In the first sample, there are $ 16 $ subarrays of length $ 3 $ . In order of appearance, they are:

 $ [1, 2, 3] $ , $ [2, 3, 1] $ , $ [3, 1, 3] $ , $ [1, 3, 2] $ , $ [3, 2, 2] $ , $ [2, 2, 1] $ , $ [2, 1, 3] $ , $ [1, 3, 2] $ , $ [3, 2, 3] $ , $ [2, 3, 1] $ , $ [3, 1, 3] $ , $ [1, 3, 1] $ , $ [3, 1, 2] $ , $ [1, 2, 3] $ , $ [2, 3, 2] $ , $ [3, 2, 1] $ .

Their sums are $ 6 $ , $ 6 $ , $ 7 $ , $ 6 $ , $ 7 $ , $ 5 $ , $ 6 $ , $ 6 $ , $ 8 $ , $ 6 $ , $ 7 $ , $ 5 $ , $ 6 $ , $ 6 $ , $ 7 $ , $ 6 $ . As $ \frac{n(n+1)}{2} = 6 $ , the answer is $ 9 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4
```

### 输出

```
56
```

## 样例 #3

### 输入

```
10
```

### 输出

```
30052700
```

# 题解

## 作者：一扶苏一 (赞：3)

## Description

给定一个数 $n$，将所有 $1~\sim~n$ 的排列按照字典序放到一个序列中，求有多少长度为 $n$ 的子序列 $p_i~p_{i+1}~\dots~p_{i + n - 1}$ 满足 $\sum_{u = i}^{i + n - 1}~p_u~=~\frac{n~\times~(n - 1)}{2}$ 答案对 $998244353$ 取模

## Input

一行一个整数代表 $n$

## Output

一行一个整数代表答案对 $998244353$ 取模的结果

## Hint

$1~\leq~n~\leq~10^6$

## Solution

做法有很多呐……

对于一个合法的序列，显然其中 $1~\sim~n$ 每个元素都出现了一次。可以使用反证法或按照 $n$ 进行数学归纳证明

那么对于一个合法的序列 $q$，一共只有两种情况：

> 1、它是由一段完整的排列构成的
>
> 2、它是由前面一段排列的后 $k$ 位和后面一段排列的前 $n - k$ 位拼成的。

情况一显然有 $n!$ 种，于是我们只考虑情况二的答案

考虑求 next_permutation 的算法：找出原排列中最长的单调降序后缀，记长度为 $k$，然后在后缀中找最小的大于原排列第 $(n - k - 1)$ 位的值，将这两个位置交换。然后将新的后缀按照升序排序（因为原先是降序的，所以这个操作等价于进行reverse）

考虑两个相邻的排列，在前面排列中选 $k$ 个，后面选 $n - k$ 的情况，若这种情况合法，则后面一个排列的前 $n - k $ 位与前面一个排列的前 $n - k$ 位是相同的，即这一段没有发生交换。所以他的后缀的长度 $len$ 必须满足 $len~<~k$。

我们考虑用总方案数减去不合法的方案数：考虑我们对一个排列固定一个选择的数的个数 $k$，那么它不合法当且仅当整个后缀是单调降序，前面怎么排无所谓，于是这样的排列共有 $A_n^{n - k}~=~\frac{n!}{k!}$ 个。这些排列在选后面 $k$ 个作为选出子序列的前缀时全部是不合法的。考虑我们这样等价于枚举选择前一个排列的 $k$ 的位置，而总共有 $n~\times~n!$ 个数字，于是这样的位置一共有 $n~\times~n!$ 种，即方案有这么多种，减去不合法的方案数即为

$$n~\times~n!~-~\sum_{k = 1}^{n - 1} \frac{n!}{k!}$$

以上是官方题解

第二种做法与第一种类似，同样依据上面的结论。不过是直接计算方案数。考虑我们如果选择一个排列的后 $k$ 个位置，我们设这个排列的后 $k$ 位是单调递增的，则对前面选择没影响的是后 $(n - k)!$ 次排列，因为这几次排列是将后面 $k$ 位从升序排列到降序，对前面没有影响。

考虑直接枚举 $k$，前面怎么选无所谓，方案数 $A_n^k$，后面共有 $(n - k)!$ 种排列。后面这些排列共有 $(n - k)! - 1$ 对，即这么多贡献。于是直接枚举统计答案即可。

以上参考 @[DDOSvoid](https://www.luogu.org/space/show?uid=34531) 神仙的做法

第三种做法直接打表找规律，设 $f_i$ 为输入为 $i$ 的答案，则

$$f_i~=~(f_{i - 1}~+~(n - 1)!~-~1)~\times~n$$

~~天知道他们是怎么看出规律的~~

## Code

代码依据官方题解算法写成

```cpp
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 1000010;
const int MOD = 998244353;

int n, ans;
int inv[maxn], fac[maxn], fac_inv[maxn];

void Get_Inv(ci);

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	Get_Inv(n);
	fac[1] = 1;
	for (rg int i = 2; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % MOD;
	ans = 1ll * n * fac[n] % MOD;
	for (rg int i = 1; i < n; ++i) {
		ans = (ans - 1ll * fac[n] * fac_inv[i] % MOD) % MOD;
	}
	qw((ans + MOD) % MOD, '\n', true);
	return 0;
}

void Get_Inv(ci x) {
	inv[1] = 1;fac_inv[1] = 1;
	for (rg int i = 2; i <= x; ++i) fac_inv[i] = 1ll * fac_inv[i - 1] * (inv[i] = (1ll * - (MOD / i) * inv[MOD % i]) % MOD) % MOD;
}
```





---

## 作者：info___tion (赞：2)

第一次在$\mathrm{CF}$比赛中杠出了有技术含量的题目，写篇题解纪念一下。

（下文中以$s$表示长度为$n*n!$的那个长字符串$p$中任意一个长度为$n$的子串。）

---
## Preparation

依据个人风格，先抛些引理出来：

---
### 引理（〇）
> $s$有且只有两种形式：

> 1. $s$是一个完整的$1 \sim n$的排列；
> 2. 存在一个分割点$k$($1 \leqslant k < n $)，使$s[1...k]$是一个排列的末尾，$s[k+1...n]$是**下一个排列**的开头。

---
### 引理（一）

> 如果$s$中的元素的和为$\frac{n(n+1)}{2}$，$s$中的元素一定**不重不漏地**取遍$1 \sim n$。

### 证明

~~其实挺难证的~~

证明看[这里](https://www.luogu.org/paste/gfbsfre3)

### 推论

> 一个$s$，其中元素的和不等于$\frac{n(n+1)}{2}$，当且仅当$s$是由**两段排列**组成的，且左边的排列中的数是**降序**的。

这个证明里面有讲过，想详细了解的自己去看吧^_^。

---
## Main

搞完上面这些，剩下的内容就简单了。

- 首先，答案至少是$n!$（因为至少会有$n!$个**纯粹**的排列符合题意（对应引理〇中的第一类$s$））。

- 至于第二类$s$，我们可以枚举分割点$k$

	然后，左半部分的**可能**方案数就是$A_n^k$。
    
    接着，在左边被选出的$k$个数中，只有一种顺序是使得这$k$个数是降序的，也就是与顺序无关的（可以理解成**无序**），所以**降序**的方案数就是$C_n^k$。
    
    所以左半部分的**合法方案数**就是$A_n^k-C_n^k$。
    
    最后，右半部分取的就是左半部分取剩的数，所以其方案数就是$A_{n-k}^{n-k}$。
    
整理得：$$ans=n!+\sum\limits_{k=1}^{n-1}(A_n^k-C_n^k)*A_{n-k}^{n-k}$$

阶乘可以$O(n)$预处理，再加上取模时的除法需要求的逆元，这种解法的时间复杂度就是$O(n\log n)$。可过。~~（只可惜当时比赛的时候我手边没有电脑，不然我说不定能涨到$\color{blue}{expert}$）~~。

---
## Addition

后来分析了一下，因为上面$A_n^k-C_n^k$在取模意义下可能会搞出一个负数，在进行乘法的时候容易出错，所以上面的柿子需要转化一下~~（顺便减少常数）~~。

~~乱搞了一轮，~~柿子可以转化为$$ans=n*n!-\sum\limits_{k=1}^{n-1} \frac{n!}{k!}$$

这条柿子在$\mathrm{CF}$那场比赛的官方题解里面有，这里就不再详细讲了。

最后唠叨一下，实际操作中，如果答案减出一个负数，那么可以把答案直接加上$998244353$，不影响答案正确性。

---
## Code

```cpp
#include<stdio.h>

const int maxn=1000002,mod=998244353;
typedef long long ll;

int fac[maxn];

void Init(int n)
{
    fac[0]=1;

    for(int i=1;i<=n;i++)
        fac[i]=(ll)fac[i-1]*i%mod;

    return;
}

int niyuan(int x)
{
    int exp=mod-2;
    int res=1,tmp=x;

    while(exp)
    {
        if( exp&1 ) res=(ll)res*tmp%mod;
        tmp=(ll)tmp*tmp%mod,exp>>=1;
    }

    return res;
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d",&n);

    Init(n);

    int ans=(ll)n*fac[n]%mod;

    for(int i=1;i<n;i++)
        ans=( (ll)ans-(ll)fac[n]*niyuan(fac[i])%mod+mod )%mod;

    printf("%d",ans);

    return 0;
}
```

---

## 作者：SovietPower✨ (赞：1)

$Description$

给定$n$。将$n!$种$n$的排列按字典序从小到大拼接成一个长为$n*n!$的序列，求该序列中有多少个长为$n$的子段，满足它们的和为$\frac{n(n+1)}{2}$（就是$1,...,n$各出现一次）。

$n\leq 10^6$。

$Solution$

> 打出表来，发现什么都$OEIS$不到。再猜答案和$n*n!$有关系。然后用$n*n!$一减答案发现这个数列可以被$OEIS$到，然后套几个式子/数列再用$n*n!$一减就得到答案了。。

没看懂官方题解在说啥。写一下(神仙)$\mathbb{mjt}$的做法orz。

对于$n=3$，$p=[1,2,3,1,3,2,2,1,3,2,3,1,3,1,2,3,2,1]$，（结合样例解释）我们猜，把排列分成$n$段，也就是以不同数开头的排列为一段，这些段的答案是一样的。（对于$n=3$就是分成$[1,2,3,1,3,2]$，$[2,1,3,2,3,1]$，$[3,1,2,3,2,1]$三段）

事实上也确实是这样，对于相邻两段比如：$2,n,...1,3,1,...,n$，它们之间也形不成合法子段。

所以我们现在只考虑怎么算以某个数开头的排列的答案（比如$[1,2,3,1,3,2]$），再乘$n$就是答案了。

我们猜是可以递推的。也就是假设我们知道$n-1$时的答案$f_{n-1}$，怎么求$f_n$？

拿$n=4$来说，考虑此时以$4$开头的排列，就是在每个$3$的排列前面加上一个$4$再拼在一起。

显然我们可以得到$3!$种合法子段。而$f_3$中的每种方案，在$n=4$时也都能和一个$4$组成合法的子段（写一写看）。但唯独最后面的$4,3,2,1$算了两次。所以有：$f_n=\left[f_{n-1}+(n-1)!-1\right]*n$。

按这个式子递推就行了。不放代码了。

---

## 作者：_sry (赞：1)


 

link

题目大意
给$n!$个$n$的排列，按字典序从小到大连成一条序列，例如$3$的情况为：$[1,2,3, 1,3,2, 2,1,3 ,2,3,1 ,3,1,2 ,3,2,1]$,问其中长度为$n$，且和为$sum=n\times (n+1)/2$的序列有多少个？

试题分析
对于合理的序列有两种情况，第一种是就是排列的，第二种就是前面$k$个与后面的$n-k$的一块组成。

对于第一种情况，答案只要$n$个，所以我们只考虑第二种情况。

当$n=3$时，$n\times n!=3!\times 3\text{=}18$

而直接生成的序列为$[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]$

而我们思考$next\_permutatin$是怎么判断下一个排列的，假设某一个序列长度为$n$，最长的递减的后缀长度$k$，那么它的下一个排列是这样产生的：选取序列第$n-k$个数，与后$k$个数中最小的那个交换（其实就是最后一个），然后将后$k$个数按从小到大排序。

 ![](https://img2018.cnblogs.com/blog/1446832/201812/1446832-20181231200128829-1500639151.png)

如图所示，若想要成为第二种情况，则$A$集合需等于$A’$集合。

而这时我们能确定$A$当前的一定不是递减的，所以问题可以转换成排除法当前序列末尾$k$个是按序递减的情况数。

举个例子:

$k=1$时，排除$[3,1,3],[2,2,1],[3,2,3],[1,3,1].[2,3,2]$

$k=2$时，排除$[(3,2),2],[(3,1),3]$

所以说我们现在只要求不行的方案数即可。

只要确定了前$k-x$个数，那么后面关于$x$的递减顺序是一定的。

所以当k=x时，排除方案数为$A_n^k$,但是最后一个是没有连接的，所以要-1，即为$A_n^k-1$

所以总方案数为$n\times n!-(n-1) - \sum_{k=1}^{n-1} (\frac{n!}{k!}-1)$.

整理的$n\times n!-\sum_{k=1}^{n-1} \frac{n!}{k!}$
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define int long long
#define mod 998244353
using namespace std;
inline int read()
{
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
const int N=2000001;
int ans,n,fac[N],f[N];
signed main(){
    n=read();fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i,fac[i]%=mod;
    f[n]=1;
    for(int i=n-1;i>=1;i--) f[i]=f[i+1]*(i+1),f[i]%=mod;
    ans=n*fac[n];
    for(int i=1;i<n;i++) ans=((ans-f[i])%mod+mod)%mod;
    printf("%d\n",ans);
}
```

---

## 作者：Trimsteanima (赞：0)

~~对着题意困惑了很长时间...~~

题意：给n!个n的排列，按字典序从小到大连成一条序列，例如3的情况为：$[1,2,3, 1,3,2, 2,1,3 ,2,3,1 ,3,1,2 ,3,2,1]$,问其中长度为n，且和为sum=n*(n+1)/2的序列有多少个？

![题意来源](https://blog.csdn.net/aiqiyizz/article/details/85530211)

本来我是想贴steps大佬给我的题意，后来发现这个qq太垃圾，找不到消息记录...这个题意也挺好的

官方题解：There is also a simple recurrence counting the same answer, found by arsijo:d(n)=(d(n−1)+(n−1)!−1)⋅n

正常思路先打表找规律...然后就能得到这个公式

如果不想用打表也可看https://www.cnblogs.com/si-rui-yang/p/10203170.html

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=5e6+7,mod=998244353;
ll n,a[N];
int main(){
    scanf("%I64d",&n);
    a[n+1]=1;
    for(ll i=n;i>=0;i--)
    　　　　a[i]=(a[i+1]*i)%mod;
    ll num=n;
    for(ll i=1;i<=n;i++)
        num=(num*i)%mod;
    num=((num-n+1)%mod+mod)%mod;
    for(ll i=1;i<n;i++){
        ll ans=(((a[i+1]-a[i+2])%mod+mod)%mod*i)%mod;
        num=((num-ans)%mod+mod)%mod;
    }
    printf("%I64d",num);
    return 0;
}
```

---

## 作者：DDOSvoid (赞：0)

注意到长度为 n，且和为 $n*(n+1)/2$ ，那么就只能是 $[1,n]$ 都出现一次

我们来考虑一个方法计数

注意到相邻的若干个排列，假设前 k 位组成的集合相同，那么后 $n-k$ 位组成的集合也一定相同，那么前一个的后 $n-k$ 位和后一个的前 $k$ 位一定是一个合法的序列

举个例子，当 $n=3$ 时，前 $1$ 位是 $1$ 的后面 $2$ 一定相同，$1,2,3,~1,3,2$

这个应该是比较好理解的 = =

好像不太好理解，实际上就是前 $k$ 位是 $a_1,a_2,\cdots,a_k$，它的下 $(n-k)!$ 个排列，变换的只有后 $n-k$ 位的顺序，实际上就是后 $n-k$ 位从升序到降序的过程，也就是后 $n-k$ 位做一次全排列的过程，次数也就是 $(n-k)!$

那么我们直接枚举 k，那么前 k 为的选择方法有 $A_n^{k}$，后面的选择是 $(n-k)!$，注意还要再减 1，因为只有相邻的才能造成 1 的贡献

最后别忘加上 $n!$，时间复杂度为 $O(n)$

 ```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define maxn 1000010
using namespace std;

const int p = 998244353;

ll pow_mod(ll x, ll n) {
    ll s = 1;
    for (; n; n >>= 1) {
        if (n & 1) s = s * x % p;
        x = x * x % p;
    }
    return s; 
}

int n;

ll fac[maxn], inv[maxn];
ll A(int n, int m) {
    return fac[n] * inv[n - m] % p; 
}

ll ans;
int main() {
    cin >> n;
    fac[0] = 1; for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % p;
    inv[n] = pow_mod(fac[n], p - 2);
    for (int i = n - 1; ~i; --i) inv[i] = inv[i + 1] * (i + 1) % p; 
    for (int i = 1; i <= n; ++i) ans = (ans + A(n, i) * (fac[n - i] - 1)) % p;
    ans = (ans + fac[n]) % p; cout << (ans + p) % p; 
    return 0;
} 
 ```

---

