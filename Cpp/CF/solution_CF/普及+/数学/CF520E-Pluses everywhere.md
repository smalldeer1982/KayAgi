# Pluses everywhere

## 题目描述

Vasya is sitting on an extremely boring math class. To have fun, he took a piece of paper and wrote out $ n $ numbers on a single line. After that, Vasya began to write out different ways to put pluses ("+") in the line between certain digits in the line so that the result was a correct arithmetic expression; formally, no two pluses in such a partition can stand together (between any two adjacent pluses there must be at least one digit), and no plus can stand at the beginning or the end of a line. For example, in the string 100500, ways 100500 (add no pluses), 1+00+500 or 10050+0 are correct, and ways 100++500, +1+0+0+5+0+0 or 100500+ are incorrect.

The lesson was long, and Vasya has written all the correct ways to place exactly $ k $ pluses in a string of digits. At this point, he got caught having fun by a teacher and he was given the task to calculate the sum of all the resulting arithmetic expressions by the end of the lesson (when calculating the value of an expression the leading zeros should be ignored). As the answer can be large, Vasya is allowed to get only its remainder modulo $ 10^{9}+7 $ . Help him!

## 说明/提示

In the first sample the result equals $ (1+08)+(10+8)=27 $ .

In the second sample the result equals $ 1+0+8=9 $ .

## 样例 #1

### 输入

```
3 1
108
```

### 输出

```
27```

## 样例 #2

### 输入

```
3 2
108
```

### 输出

```
9```

# 题解

## 作者：Heartlessly (赞：6)

## Description

给定一个 $n$ 位数 $a$，请你在这些数位之间添加 $m$ 个 `+` 号，得到一个表达式。求所有可能的不同表达式的和，答案对 $10^9 + 7$ 取模。

$(0 \leq m < n \leq 10^5)$

## Solution

考虑单独计算每一个 $a_i$ 的贡献。

首先一共有 $n - 1$ 个位置可以放加号，根据离 $a_i$ 最近且在 $a_i$ 之后的加号位置分情况讨论：

若最近的加号在 $a_i$ 后面，则剩下 $m - 1$ 个加号，有 $n - 2$ 个位置可以放，$a_i$ 的贡献为 $a_i \times {\rm C}_{n-2}^{m - 1}$；

若最近的加号在 $a_{i+1}$ 后面，则剩下 $m - 1$ 个加号，有 $n - 3$ 个位置可以放，$a_i$ 的贡献为 $a_i \times 10 \times {\rm C}_{n-3}^{m - 1}$；

若最近的加号在 $a_{i+2}$ 后面，则剩下 $m - 1$ 个加号，有 $n - 4$ 个位置可以放，$a_i$ 的贡献为 $a_i \times 10^2 \times {\rm C}_{n-4}^{m - 1}$；

……

若最近的加号在 $a_{i+n-m-1}$ 后面，则剩下 $m - 1$ 个加号，有 $m - 1$ 个位置可以放，$a_i$ 的贡献为 $a_i \times 10^{n - m - 1} \times {\rm C}_{m - 1}^{m - 1}$ 。（当且仅当其它加数都是一位数时 $a_i$ 的单次贡献为 $a_i \times 10^{n - m - 1}$）

特殊地，当最近的加号在 $a_{n}$ 后面时，剩下 $m$ 个加号，有 $i - 1$ 个位置可以放，$a_i$ 的贡献为$a_i \times 10^{n - i} \times {\rm C}_{i - 1}^{m}$ 。

答案就是贡献总和。

直接枚举 $a_i$ 的贡献为 $10^j$ 的时间复杂度是 $O(n^2)$ 的。

我们发现贡献是 $10^j$ 的数字乘上的组合数是相同的，因此前缀和预处理出能产生 $10^j$ 贡献的数字总和即可，注意加号放在 $a_n$ 后时要单独计算，时间复杂度为 $O(n)$ 。

最后的式子：

$$\sum\limits_{i = 1}^{n - m} 10^{i - 1} \times \left(\sum\limits_{j = 1}^{n - i}a_j \times {\rm C}_{n - 1 - i}^{m - 1} + a_{n - i + 1} \times {\rm C}_{n - i}^{m}\right)$$

枚举 $i$，计算所有 $i$ 位数产生的贡献。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

inline void readDigit(int &x) {
    char c = getchar();
    for (; !isdigit(c); c = getchar());
    x = c ^ 48;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 1e5, MOD = 1e9 + 7;
int n, m, ans, a[MAXN + 5], pre[MAXN + 5], fac[MAXN + 5], inv[MAXN + 5];

inline int quickPow(int x, int p) {
    int res = 1;
    for (; p; p >>= 1, x = 1ll * x * x % MOD)
        if (p & 1) res = 1ll * res * x % MOD;
    return res;
}

inline void init() {
    fac[0] = 1;
    for (int i = 1; i <= MAXN; ++i) fac[i] = 1ll * fac[i - 1] * i % MOD;
    inv[MAXN] = quickPow(fac[MAXN], MOD - 2);
    for (int i = MAXN - 1; ~i; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
}

inline int c(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return 1ll * fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        readDigit(a[i]);
        pre[i] = pre[i - 1] + a[i];
    }
    init();//预处理组合数 
    for (int cur = 1, i = 1; i <= n - m; ++i, cur = 1ll * cur * 10 % MOD)
        ans = (ans + 1ll * cur * (1ll * pre[n - i] * c(n - 1 - i, m - 1) % MOD + 
        1ll * a[n - i + 1] * c(n - i, m) % MOD) % MOD) % MOD;
    write(ans);
    putchar('\n');
    return 0;
}
```



---

## 作者：QwQcOrZ (赞：5)

### 祭我在考场上AC了此题

考虑第$i$位数，在取出的数中是第$j$位出现的贡献：

- 数值$=V_i \times 10^j$

- 出现次数$=C^{k-1}_{i-1+n-i-j-1}=C^{k-1}_{n-j-2}$

- 贡献$=$数值$\times$出现次数$=V_i \times 10^j \times C(k-1,n-j-2)$

出现次数即为把$k-1$个"$+$"填入剩余可以填的位置的方案数（为什么是$k-1$？因为当前这个数后面可以确定一个加号）

方案数可以由左边空余可以填的位置与右边空余可以填的位置相加得到，不难推出是：$C^{k-1}_{(i-1)+(n-i-j-1)}=C^{k-1}_{n-j-2}$

可以发现出现次数与$i$无关

那么将$V$处理成前缀和的形式，枚举$j$，计算贡献即可

-------------------

但是如果直接这么做我们会发现样例$wei$了

为什么？因为如果当前确定的数的末位在最后一位，那么它后面是不能跟加号的，此时出现的次数变成了$C^k_{n-i-1}$

特判即可

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e5+1e3;
const ll p=1e9+7;

ll read()
{
	ll s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(ll x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(ll x,char c='\n')
{
	write(x);
	putchar(c);
}
ll a[N],fact[N],inv[N],base[N],ans=0;//fact[i]:i!,inv[i]:i!的逆元,base[i]:10^i 
ll power(ll a,ll b)
{
	ll ans=1;
	while (b)
	{
		if (b&1) ans=ans*a%p;
		a=a*a%p;
		b/=2;
	}
	return ans;
}
ll C(ll n,ll m)
{
	if (n>m) return 0;
	return fact[m]*inv[n]%p*inv[m-n]%p;
}

int main()
{
	ll n=read(),k=read();
	for (ll i=1;i<=n;i++)
	{
		char c=getchar();
		while (c<'0'||'9'<c) c=getchar();
		a[i]=(a[i-1]+c-'0')%p;//将a处理成前缀和的形式 
	}
	fact[0]=base[0]=1;
	for (ll i=1;i<=n;i++) fact[i]=fact[i-1]*i%p;
	inv[n]=power(fact[n],p-2);
	for (ll i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%p;
	for (ll i=1;i<=n;i++) base[i]=base[i-1]*10ll%p;
	for (ll i=0;i<n;i++)
	{
		ans=(ans+a[n-i-1]*base[i]%p*C(k-1,n-i-2)%p)%p;
		ans=(ans+(a[n-i]-a[n-i-1]+p)%p*base[i]%p*C(k,n-i-1)%p)%p; 
	} 
	print(ans);

	return 0;
}
```

~~应该没有人不开long long吧~~

---

## 作者：Farkas_W (赞：3)

### 思路：

$\quad$这是一道数学题，分别计算每一个点分别作个位，十位... $n-k$ 位的贡献即可(不可做这一数位的数的这一数位的贡献为 $0$ )，如字符串 $9876543210$ 中 $0$ 只可以作个位， $1$ 只可以作个位和十位，其他数位的贡献为 $0$ ，所以可以得到 

$ans=a_n \times C_{n-1}^{k} + a_{n-1}\times C_{n-2}^{k-1} + 10\times a_{n-1}\times C_{n-2}^k + a_{n-2}\times C_{n-2} + 10\times a_{n-2}\times C_{n-3}^{k-1} + 100\times a_{n-2}\times C_{n-3}^{k}.....$

化简得：

$ans =\sum_{i=1}^{n-k}(10^{i-1}\times (a_{n-i-1}\times C_{n-i}^{k})+\sum_{j=1}^{n-i}a_j\times C_{n-i-1}^{k-1})$

$\quad$所以只需要用数组 $b$ 记录前缀和，用数组 $d$ 记录 $1! - n!$ ，用数组 $inv$ 记录每个阶乘的逆元，最后注意取模即可，很有价值的一题，建议式子再推一遍，尤其是边界。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cstring>
using namespace std;
#define re register int
#define int long long
#define LL long long
#define il inline
#define lowbit(x) x&(-x)
#define next nee
#define inf 1e18
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=1e5+5,MOD=1e9+7;
int n,m,k,a[N],b[N],inv[N]={1,1},ans,d[N]={1};
string s;
il int C(int a,int b){return d[a]*inv[b]%MOD*inv[a-b]%MOD;}
signed main()
{
  n=read();k=read();cin>>s;int ret=1;
  for(re i=1;i<=n;i++)a[i]=s[i-1]-'0',b[i]=a[i]+b[i-1],d[i]=d[i-1]*i%MOD;//计算前缀和，阶乘 1!-n!
  for(re i=2;i<=n;i++)inv[i]=inv[MOD%i]*(MOD-MOD/i)%MOD;//计算1-n每个数的逆元
  for(re i=2;i<=n;i++)inv[i]=inv[i]*inv[i-1]%MOD;计算1！-n！的逆元
  for(re i=1;i<=n-k;i++)
    {
      ans=(ans+ret*(a[n-i+1]*C(n-i,k)%MOD)%MOD)%MOD;
      ans=(ans+ret*(b[n-i]*C(n-i-1,k-1)%MOD)%MOD)%MOD;
      ret=ret*10%MOD; //ret表示10的i-1次方
      }
  print(ans);
  return 0;
}
```

---

## 作者：Arcturus1350 (赞：2)

ps:可能组合数一不小心打错了，请发现的大佬提出，谢谢。

我们来讨论每一位数$a_{i}$被算了多少次。

总共有$n-1$个空位可以放$'+'$所以，$a_{i}$左边有$i-1$个空位，右边$n-1-(i-1)$个。

举个例子来说~~（手动模拟一下）~~，如果数$a_{i}$右边有一个加号，则剩下$n-2$个空位放$k-1$个加号的方案里，每种方案$a_{i}$都当做各位记录到答案里，所以对答案影响：$C^{k-1}_{n-2}*$ $a_{i}$。
假设右边第一个不放，第二个放加号，则还有$n-3$个空位，$k-2$个加号。（因为$a_{i}$右边的以为不能放加号）对答案影响： $C_{n-3}^{k-2}*10*$ $a_{i}$。

$emm……$规律好像找出来了。

这样一直递推下去~~（找规律）~~的话。到$a_{n-1}$ 和 $a_{n}$ 位填的话。对答案的影响： $C^{1}_{n-k-2}*10^{k-1}*a_{i}$ 

但是，我们发现，最后一位数的后面好像并不能放加号。也就是说，最后一位需要特判。。。

所以，当右边全空着的时候对答案的贡献 $10^{i}*C_{n-i-1}^{i}*a_{i}$

全部统计起来，输出就好。
代码奉上。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const long long p=1e9+7; 
int n,k;
long long ans[100010];
char a[100010];

long long pen[100010];//阶乘
long long rpen[100010];//阶乘逆元 
long long num[100010];//系数 

long long pow2(long long a,long long b)
{
    long long res=1;
    for(;b;b>>=1,a=a*a%p) if(b&1) res=res*a%p;
    return res%p;
}

void rebiut()
{
	num[0]=pen[0]=rpen[0]=1;
	for(int i=1;i<=n;i++)
		pen[i]=pen[i-1]*i%p,
		rpen[i]=pow2(pen[i],p-2),
		num[i]=10*num[i-1]%p;
	return ;
}

long long C(long long n,long long k)//计算组合数，n下面，k上面 
{
	if(k<0||k>n||n<0) return 0;
	else return ((pen[n]*rpen[k])%p)*rpen[n-k]%p;
}

long long now;

int main()
{
	scanf("%d%d",&n,&k);
	scanf("%s",a);
	rebiut();

	for(int i=0;i<n;i++) now=(now+num[i]*(a[n-i-1]-'0'))%p;
	if(k==0) {printf("%lld ",now);return 0;}
	
	int d=n-k-1;
	ans[0]=C(n-2,k-1);

	for(int i=0;i<=d;i++) ans[i]=(ans[i-1]+num[i]*C(n-i-2,k-1))%p;
	for(int i=d+1;i<n;i++) ans[i]=ans[i-1];
	for(int i=0;i<=d;i++) ans[i]=(ans[i]+num[i]*C(n-i-2,k))%p;
	now=0;
	for(int i=0;i<n;i++) now=(now+ans[n-i-1]*(a[i]-'0'))%p;
	printf("%lld ",now);
	return 0;
}
```

---

## 作者：_Passerby_ (赞：1)

更好的阅读体验：[cnblogs](https://www.cnblogs.com/Eliauk-FP/p/18513410)。**注意，博客园里面包含了CF520这一套题的题解！**

【题目大意】

给定 $n$ 个数 $a_i$，每次操作可以在这些数中间添加 $k$ 个 $+$ 号，得到若干个不同的表达式，求这些表达式的和。

【解题思路】

考虑对每个 $a_i$ **单独**计算它的贡献。

若在 $a_{i + j}$ 的后面放加号，$a_i$ 在表达式中的实际值为 $a_i \times 10 ^ j$。剩下 $k - 1$ 个加号，有 $n - j - 2$ 个位置可以放加号，这样，这个表达式的出现次数为 $C_{n - j - 2}^{k - 1}$，$a_i$ 这时的贡献为 $a_i \times 10 ^ j \times C_{n - j - 2}^{k - 1}$。特别地，当 $a_i$ 后面没有加号时，它的贡献为 $a_i \times 10 ^ {n - i} \times C_{i - 1}^k$。

综上，$a_i$ 的贡献为

$$
a_i \times ((\sum_{j = 0}^{n - i - 1}10 ^ j \times C_{n - j - 2}^{k - 1}) +  10^{n - i} \times C_{i - 1}^k)
$$

转化成方便处理的形式得到

$$
a_i \times ((\sum_{j = 1}^{n - i}10 ^ {j - 1} \times C_{n - j - 1}^{k - 1}) +  10^{n - i} \times C_{i - 1}^k)
$$

则有总答案

$$
Ans = \sum_{i = 1}^n(a_i \times ((\sum_{j = 1}^{n - i}10 ^ {j - 1} \times C_{n - j - 1}^{k - 1}) +  10^{n - i} \times C_{i - 1}^k))
$$

考虑化简 $Ans$，首先，将其拆分为两个式子 $A_1$ 和 $A_2$ 的和，即

$$
Ans = A_1 + A_2
$$

其中

$$
A_1 = \sum_{i = 1}^n a_i \times \sum_{j = 1}^{n - i}10 ^ {j - 1} \times C_{n - j - 1}^{k - 1},
$$

$$
A_2 = \sum_{i = 1}^n a_i \times 10^{n - i} \times C_{i - 1}^k
$$

在 $A_1$ 中，考虑将 $j$ 提取到外层，注意到当 $n - j - 1 < k - 1$，即 $j > n - k$ 时，$C_{n - j - 1}^{k - 1} = 0$，则 $j$ 最大值为 $n - k$，即

$$
A_1 = \sum_{j = 1}^{n - k} 10 ^ {j - 1}  \times \sum_{i = 1}^{n - j} a_i \times C_{n - j - 1}^{k - 1}
$$

在 $A_2$ 中，令 $j = n - i + 1$，有

$$
A_2 = \sum_{j = 1}^n 10^{j - 1} \times  a_{n - j + 1} \times C_{n - j}^k
$$

同理，$j$ 的最大值为 $n - k$，又有

$$
A_2 = \sum_{j = 1}^{n - k} 10^{j - 1} \times a_{n - j + 1} \times C_{n - j}^k
$$

在计算总答案 $Ans$ 时，可以将 $A_1$ 和 $A_2$ 最外层循环合并，所以有

$$
Ans = \sum_{j = 1}^{n-k}10^{j - 1}\times((\sum_{i = 1}^{n - j}a_i\times C_{n-j-1}^{k-1})+a_{n-j+1}\times C_{n-j}^k
$$

化简，得

$$
Ans = \sum_{j = 1}^{n-k}10^{j - 1}\times((C_{n-j-1}^{k-1}\times\sum_{i = 1}^{n - j}a_i)+a_{n-j+1}\times C_{n-j}^k)
$$

对于内层 $\sum_{i = 1}^{n - j}a_i$ 的计算，可以通过前缀和优化为 $O(1)$，这样，总复杂度为 $O(n)$，可以通过本题。

---

## 作者：Mihari (赞：1)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF520E)

# 题解

如果 $\text{Latex}$ 炸掉，可以前往[这里](https://www.cnblogs.com/Arextre/p/13635216.html)阅读.

每个数对答案的贡献单独考虑.

对于一个数 $a_p$，它的贡献只和它后面填的第一个加号的距离有关，当第一个加号的位置出现在离它的距离为 $i$，它的贡献就固定了，为 $10^i\times a_p$，而其他的加号可以在除了从 $p$ 到 $p+i$ 这一段的任意空位中填（因为要保证我们固定填的加号是第一个出现在 $a_p$ 之后的），所以就可以算出这样的贡献，为
$$
10^i\times a_p\times C_{n-1-(i-p+1)}^{k-1}
$$
为了方便处理，我们重新定义 $i$ 为在 $a_p$ 之后的 $a_i$ 后面填上了一个加号，这时 $a_p$ 的贡献，那么我们就有
$$
Ans=\sum_{p=1}^n\left (\sum_{i=p}^{n} a_p\times 10^{i-p}\times {{n+p-i-1-[i\neq n]}\choose k-[i\neq n]}\right )
$$
至于为什么组合数中有 $[i\neq n]$，是因为我们在最后一个数后面填的 $+$ 是虚假的，只是为了帮助我们计算答案而非真实存在，故算其他括号的时候不能将其计算上.

这个柿子显然是 $\mathcal O(n^2)$ 的，我们不能接受，现在考虑化简这个式子.

令 $j=i-p$，那么就有 $i=j+p$.

由于 $i\le n$，故 $j+p\le n$ 即 $j\le n-p$，我们用 $j$ 重新写这个式子：
$$
\begin{aligned}
Ans&=\sum_{p=1}^n\left (\sum_{i=p}^{n} a_p\times 10^{i-p}\times {{n+p-i-1-[i\neq n]}\choose k-[i\neq n]}\right ) \\
&=\sum_{p=1}^n\left (\sum_{j=0}^{n-p} a_p\times 10^j\times {{n+p-(j+p)-1-[j+p\neq n]}\choose k-[j+p\neq n]}\right ) \\
&=\sum_{p=1}^n\left (\sum_{j=0}^{n-p} a_p\times 10^j\times {{n-j-1-[j+p\neq n]}\choose k-[j+p\neq n]}\right ) \\
&=\sum_{j=0}^n\sum_{p=1}^{n-j}a_p\times 10^j\times {{n-j-1-[j+p\neq n]}\choose k-[j+p\neq n]} \\
&=\sum_{j=0}^n10^j\times \sum_{p=1}^{n-j}a_p\times {{n-j-1-[j+p\neq n]}\choose k-[j+p\neq n]} \\
\end{aligned}
$$
由于 $[j+k\neq n]$ 太烦了，我们考虑将其单独处理，那么式子就变成了
$$
\begin{aligned}
Ans&=\sum_{j=0}^n10^j\times \sum_{p=1}^{n-j}a_p\times {{n-j-1-[j+p\neq n]}\choose k-[j+p\neq n]} \\
&=\sum_{j=0}^n10^j\times \left [ \sum_{p=1}^{n-j-1}a_p\times {{n-j-2}\choose {k-1}} +a_p\times {{n-p-1}\choose k}\right ] \\
&=\sum_{j=0}^n10^j\times \left [ {{n-j-2}\choose {k-1}}\sum_{p=1}^{n-j-1}a_p +a_{n-j}\times {{n-p-1}\choose k}\right ]
\end{aligned}
$$
其中，$10^j$ 可以预处理，而 $\sum_{p=1}^{n-j-1}a_p$ 即前缀和，这样式子就是 $\mathcal O(n)$ 的了.

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13635216.html
```



---

## 作者：dsjkafdsaf (赞：1)

# [My blog](https://www.cnblogs.com/dsjkafdsaf/)
## 题目描述

给出一个长度为 $n$ 的字符串，给出一个非负整数 $k$，要求给这个字符串中间添加 $k$ 个$$+$’号，变成一个表

达式，比如”$1000101$”,添加两个$＋$号，可以变成”$10+001+01$”,或者”$1000+1+01$”,表达式的值分别是$12$ 和 $1002$。

问所有的添加加号的方案的表达式的值的和是多少。

## Input

两个整数 $n，k$，一个字符串$ s$ $(0<=k<n<=1e5).$

## Output

一个整数，模$ 1000000007$

## Sample Input

```
3 1
108

3 2
108
```
## Sample Output
```
27
9
```
计数$DP$

首先，看到那么大的数据范围肯定是对于每个数计算贡献。

那么我们该如何计算贡献呢？

对于题目给出的那个字符串$S$，从左往右每个数字依次为$a_{n-1},a_{n-2}....a_{1},a_0$.

现在，我们对于$a_t$，讨论其贡献。

$a_t$右边有$t$个位置可以放置加号，同时一共有$n-1$个位置放置加号。

若$a_t$右边第一个位置放置了加号，则$a_t$被当成个位，还有$n-2$个空位，$k-1$个加号，一共有$C(k-1,n-2)$种方案。

其贡献为$C(k-1,n-1)*10^{0}*a_t$。

若$a_t$右边第一个位置为空，第二个位置放置加号，则$a_t$为十位，还有$n-3$个空位，$k-1$个加号，共有$C(k-1,n-3)$种方案。

贡献为$C(k-1,n-2)*10^{1}*a_t$.

依次类推，

若$a_t$右边为空，则贡献为$C(k,n-t-2)*10^{t}*a_t$。

所以，$a_t$这个数的贡献为$(10^{t}*C(k,n-t-2)+\sum^{t}_{j=0}10^{j}*C(k-1,n-j-2))*a_t$。

于是我们可以得到第$i$个数的贡献计算公式$A_i=10^{i}*C(k,n-i-2)+\sum^{i}_{j=0}10^{j}*C(k-1,n-j-2)$。

最后，$Ans=\sum^{n-1}_{i=0}A_i*a_i$。

## 代码如下
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define int long long
#define reg register
#define Raed Read
#define clr(a,b) memset(a,b,sizeof a)
#define Mod(x) (x>=mod)&&(x-=mod)
#define debug(x) cerr<<#x<<" = "<<x<<endl;
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)>(b)?(b):(a))
#define rep(a,b,c) for(reg int a=(b),a##_end_=(c); a<=a##_end_; ++a)
#define ret(a,b,c) for(reg int a=(b),a##_end_=(c); a<a##_end_; ++a)
#define drep(a,b,c) for(reg int a=(b),a##_end_=(c); a>=a##_end_; --a)
#define erep(i,G,x) for(int i=(G).Head[x]; i; i=(G).Nxt[i])
#pragma GCC target("avx,avx2,sse4.2")
#pragma GCC optimize(3)

inline int Read(void) {
	int res=0,f=1;
	char c;
	while(c=getchar(),c<48||c>57)if(c=='-')f=0;
	do res=(res<<3)+(res<<1)+(c^48);
	while(c=getchar(),c>=48&&c<=57);
	return f?res:-res;
}

template<class T>inline bool Min(T &a, T const&b) {
	return a>b?a=b,1:0;
}
template<class T>inline bool Max(T &a, T const&b) {
	return a<b?a=b,1:0;
}


const int N=1e5+5,M=1e6+5,mod=1e9+7;

bool MOP1;

int Fac[N],Inv[N];

inline int Pow(int x) {
	int res=1,y=mod-2;
	while(y) {
		if(y&1)res=(res*x)%mod;
		x=(x*x)%mod,y>>=1;
	}
	return res;
}

inline int C(int x,int y) {
	if(!x)return 1;
	return (Fac[y]*((Inv[x]*Inv[y-x])%mod))%mod;
}

int A[N],Pow_10[N];

char S[N];

bool MOP2;

inline void _main() {
	int n=Read(),k=Read(),Ans=0,tot=0;
	scanf("%s",S),Fac[0]=Pow_10[0]=Inv[0]=1;
	if(!k) {
		int Ans=0;
		ret(i,0,n)Ans=(Ans*10+(S[i]^48))%mod;
		printf("%lld\n",Ans);
		return;
	}
	rep(i,1,n) {
		Fac[i]=(Fac[i-1]*i)%mod;
		Pow_10[i]=(Pow_10[i-1]*10)%mod;
		Inv[i]=Pow(Fac[i]);
	}
	A[0]=C(k-1,n-2);
	int P=n-k-1;
	rep(i,0,P)A[i]=(A[i-1]+Pow_10[i]*C(k-1,n-i-2))%mod;
	rep(i,P+1,n)A[i]=A[i-1];
	rep(i,0,P)A[i]=(A[i]+Pow_10[i]*C(k,n-i-2));
	ret(i,0,n)Ans=(Ans+(S[i]^48)*A[n-i-1])%mod;
	printf("%lld\n",Ans);
}

signed main() {
	_main();
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
给定一个 $n$ 位的十进制数，可以再数字之间加 $k$ 个 $+$，得到一个式子，求每种方案的这个式子和的和。
### 分析
推柿子。

考虑每一个数产生的贡献，受到它处在一个数的第几位上，所以枚举该数之后的最靠近它的 $+$ 位置，用实际值乘上方案数累加即可。

初步列出以下柿子：
 $$\sum_{i=1}^na_i\sum_{j=0}^{n-i-1}\dbinom{n-j-2}{k-1}10^j$$
 解释一下，$\dbinom{n-j-2}{k-1}$ 是在第 $i+j$ 个位置后加入最近的 $+$ 的方案数，还剩 $n-j-2$ 个位置，要填 $k-1$ 个 $+$。

然后可以交换一下枚举顺序，变成：
$$\sum_{i=1}^{n-k-1}\dbinom{n-i-2}{k-1}10^i\sum_{j=1}^{n-i-1}a_j$$

可以前缀和预处理一下，做到 $\mathcal O(n)$ 了。

但是我们忘了考虑一种情况，就是最后一个数后面没有 $+$，贡献没有统计进去。

所以答案还要再加上这个：
$$\sum_{k+1}^n\dbinom{i-1}{k}10^{n-i}a_i$$
算这个还是比较简单的。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e5+5;
const int mod=1e9+7;
int n,k;
int ans;
int a[maxn],s[maxn];
int fac[maxn],inv[maxn],pw[maxn];
int qpow(int a,int x){
	int s=1;
	while(x){
		if(x&1) s=s*a%mod;
		a=a*a%mod;
		x>>=1;
	}
	return s;
}
void init(){
	fac[0]=pw[0]=1;
	for(int i=1;i<maxn;i++){
		fac[i]=fac[i-1]*i%mod;
		pw[i]=pw[i-1]*10%mod;
	}
	inv[maxn-1]=qpow(fac[maxn-1],mod-2);
	for(int i=maxn-2;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}
int C(int n,int m){
	if(n<m) return 0;
	return fac[n]*inv[n-m]%mod*inv[m]%mod;
}
signed main(){
	cin.tie(0),cout.tie(0);
	init();
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		a[i]=c-'0';
		s[i]=s[i-1]+a[i];
	}
	for(int i=0;i<=n-k-1;i++){
		ans=(ans+C(n-i-2,k-1)*pw[i]%mod*s[n-i-1]%mod)%mod;
	}
	for(int i=k+1;i<=n;i++){
		ans=(ans+C(i-1,k)*pw[n-i]%mod*a[i]%mod)%mod;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：STrAduts (赞：0)

### Step 1.

转化一步题目：考虑有 $n$ 个小球，每个小球有 $a_i$ 的价值，$m$ 个板子，把板子插进小球间的空隙，且不能插在第 $1$ 个球之前与第 $n$ 个球之后。

且规定对于任意一个方案，若第 $i$ 个球与下一块板子间相隔 $j$ 个球，则该球对答案的贡献为 $10^j a_i$。现需要求出每一个方案每一个球的贡献和。

这题显然和原题是等价的（转化可能是因为它更组合一些 www），因为对于任意一个方案中的任意一个数字来说，只有它和**下一个加号之间的数的个数**会影响它对总答案的贡献。

于是我们考虑上面那个问题的答案。

对于第 $i$ 个球，我们枚举 $j$，并尝试求出会有多少方案使得目前的状态成立。可以发现 $0 \leq j \leq n - i$。

可以明确第 $i$ 个球后的 $j$ 个球之间都不能再插板，且第 $j$ 个球和第 $j + 1$ 个球之间一定需要插板、总共有 $n - 1$ 个位置可以插板。那么也就是说总方案应该是在剩下的 $n - 1 - j - 1$ 个空位中插 $m - 1$ 个板的方案数，即 $\dbinom {n - j - 2} {m - 1}$。

特殊的，如果 $j = n - i$，则柿子会有所改变。因为第 $n$ 个球后不能插板，所以说可以转化为在 $i$ 以前的能插的位置中插入 $m$ 个板的方案，即 $\dbinom {i - 1} {m}$。

显然当前状态的第 $i$ 个球的贡献应是 $10^j a_i$，故总答案为 ${\large \sum \limits _{i = 1}^{n}} {\large \sum \limits _{j = 0}^{n - i - 1}} \dbinom {n - j - 2} {m - 1} 10^j a_i + {\large \sum \limits _{i = 1}^{n}} \dbinom {i - 1} {m} 10^{n - i} a_i$。

这是 $O(n^2)$ 的求解过程，不能通过，于是考虑优化。

---

### Step 2.

你会发现，如果我们，确定了 $j$，则我们也可以确定有多少 $i$，可以得到该 $j$ 的贡献，具体来讲，对于一个 $j$，所有 $1 \leq i \leq n - j$，都能得到 $j$ 的贡献，因为这些球的后面都有 $j$ 个球可以用于隔开自己和下一个加号。

当然这里仍需要考虑**当前球后面都不再放加号**的特殊情况，仍是单拎出来计算。

于是就可以直接来枚举 $j$。记 $S(x) = {\large \sum \limits _{i = 1}^{x}} a_i$，则答案可写为 ${\large \sum \limits _{j = 0}^{n - 1}} 10^jS(n - j - 1)\dbinom {n - i - 2} {m - 1} + {\large \sum \limits _{i = 1}^{n}} \dbinom {i - 1} {m} 10^{n - i} a_i$。

提前初始化组合数、$10$ 的次方都是基本功了嘛。

---

### Code

```cpp
#include <cstdio>

typedef long long LL;
int Abs(int x) { return x < 0 ? -x : x; }
int Max(int x, int y) { return x > y ? x : y; }
int Min(int x, int y) { return x < y ? x : y; }

int read() {
    int x = 0, k = 1;
    char s = getchar();
    while(s < '0' || s > '9') {
        if(s == '-')
            k = -1;
        s = getchar();
    } 
    while('0' <= s && s <= '9') {
        x = (x << 3) + (x << 1) + (s ^ 48);
        s = getchar();
    }
    return x * k;
}

void write(int x) {
    if(x < 0) {
        x = -x;
        putchar('-');
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void print(int x, char s) {
    write(x);
    putchar(s);
}

const int mod = 1e9 + 7;
const int MAXN = 1e5 + 5;

char s[MAXN];
int fac[MAXN], inv[MAXN], q[MAXN], p[MAXN], sum[MAXN];

inline int Sub(int x) { return x < 0 ? x + mod : x; }
inline int Plus(int x) { return x >= mod ? x - mod : x; }
inline int C(int n, int m) { 
    if(n < m)
        return 0;
    return (LL)fac[n] * inv[m] % mod * inv[n - m] % mod; 
}

void init() {
    inv[1] = 1;
    for(int i = 2; i < MAXN; i++)
        inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
    fac[0] = 1, inv[0] = 1, p[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        p[i] = (LL)p[i - 1] * 10 % mod;
        fac[i] = (LL)fac[i - 1] * i % mod;
        inv[i] = (LL)inv[i - 1] * inv[i] % mod;
    }
}

int main() {
    init();
    int n = read(), m = read();
    scanf ("%s", s + 1);
    for(int i = 1; i <= n; i++) {
        q[i] = s[i] - '0';     
        sum[i] = Plus(sum[i - 1] + q[i]);   
    }
    int ans = 0;
    for(int i = 0; i < n; i++)
        ans = Plus(ans + (LL)sum[n - i - 1] * p[i] % mod * C(n - i - 2, m - 1) % mod);
    for(int i = 1; i <= n; i++)
        ans = Plus(ans + (LL)q[i] * p[n - i] % mod * C(i - 1, m) % mod);
    print(ans, '\n');
    return 0;
}
```

---

