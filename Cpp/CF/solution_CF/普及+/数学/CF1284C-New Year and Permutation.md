# New Year and Permutation

## 题目描述

Recall that the permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

A sequence $ a $ is a subsegment of a sequence $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end. We will denote the subsegments as $ [l, r] $ , where $ l, r $ are two integers with $ 1 \le l \le r \le n $ . This indicates the subsegment where $ l-1 $ elements from the beginning and $ n-r $ elements from the end are deleted from the sequence.

For a permutation $ p_1, p_2, \ldots, p_n $ , we define a framed segment as a subsegment $ [l,r] $ where $ \max\{p_l, p_{l+1}, \dots, p_r\} - \min\{p_l, p_{l+1}, \dots, p_r\} = r - l $ . For example, for the permutation $ (6, 7, 1, 8, 5, 3, 2, 4) $ some of its framed segments are: $ [1, 2], [5, 8], [6, 7], [3, 3], [8, 8] $ . In particular, a subsegment $ [i,i] $ is always a framed segments for any $ i $ between $ 1 $ and $ n $ , inclusive.

We define the happiness of a permutation $ p $ as the number of pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ , and $ [l, r] $ is a framed segment. For example, the permutation $ [3, 1, 2] $ has happiness $ 5 $ : all segments except $ [1, 2] $ are framed segments.

Given integers $ n $ and $ m $ , Jongwon wants to compute the sum of happiness for all permutations of length $ n $ , modulo the prime number $ m $ . Note that there exist $ n! $ (factorial of $ n $ ) different permutations of length $ n $ .

## 说明/提示

For sample input $ n=3 $ , let's consider all permutations of length $ 3 $ :

- $ [1, 2, 3] $ , all subsegments are framed segment. Happiness is $ 6 $ .
- $ [1, 3, 2] $ , all subsegments except $ [1, 2] $ are framed segment. Happiness is $ 5 $ .
- $ [2, 1, 3] $ , all subsegments except $ [2, 3] $ are framed segment. Happiness is $ 5 $ .
- $ [2, 3, 1] $ , all subsegments except $ [2, 3] $ are framed segment. Happiness is $ 5 $ .
- $ [3, 1, 2] $ , all subsegments except $ [1, 2] $ are framed segment. Happiness is $ 5 $ .
- $ [3, 2, 1] $ , all subsegments are framed segment. Happiness is $ 6 $ .

Thus, the sum of happiness is $ 6+5+5+5+5+6 = 32 $ .

## 样例 #1

### 输入

```
1 993244853```

### 输出

```
1```

## 样例 #2

### 输入

```
2 993244853```

### 输出

```
6```

## 样例 #3

### 输入

```
3 993244853```

### 输出

```
32```

## 样例 #4

### 输入

```
2019 993244853```

### 输出

```
923958830```

## 样例 #5

### 输入

```
2020 437122297```

### 输出

```
265955509```

# 题解

## 作者：34ytw8ew7ft (赞：5)

## 写在前面
看了一些巨佬的解法，大家的解法都差不多，但是由于我比较菜……所以用了另一种更便于理解的解法推出了不同的式子，希望对各位有所帮助。

本题解假设您目前还不会排列组合，但会加法乘法原理，若觉得过于简单可以直接跳过。

## 要干什么
题意已经说的很明白了，就是求长度为$n$的$1-n$的序列的所有全排列中共有几段排序后数字为连续的区间。  
原因显然：序列中除去最大值最小值后共有$l-r-1$个数字，为保证这些数字$>p_{min}$且$< p_{max}$，那只有他们是连续的时候才可以满足。

那具体怎么计算呢？下面将详细说明。

## 计算

一开始肯定没有任何头绪，那我们可以通过加法原理对区间**按照长度**先分为$n$类，再逐一计算。  
对于每种长度为$i$的区间，我们干的事情无非四步：

1. 选数——在$l=1$时从1开始选出$i$个连续的数，生成一个基本区间
2. 打乱——可以把基本区间中的元素打乱来产生其他新的区间
3. 换数——我们可以把基本区间中的数统一加上一个$\le n-i$的**自然数**产生其他新的区间
4. 换序——我们可以把基本区间在排列中向右移动$\le n-i$的**自然数**个单位生成新的区间

可以发现这是一个分步执行的过程，所以应该用乘法原理计数。

### Step1.选数

考虑小学概率。

众所周知，长度为$n$的序列的全排列共有$n!$种。我们要从中选$i$个数。有$n$种数有可能作为$p_1$，然而我们只要1，那么$p_1$有$\frac{1}{n}$种选法。同理可得在$p_1$确定的情况下$p_2$有$\frac{1}{n-1}$种选法，以此类推，$p_q$有$\frac{1}{n-i+1}$种选法。显而易见，这又是一个乘法原理计数，所以最后的结果就是：

$$\frac{n!}{n \times (n-1) \times (n-2) \times ... \times (n-i+1)}= \frac{n!}{\frac{n!}{(n-i)!}}=(n-i)!$$

### Step2.打乱

众所周知，长度为$n$的序列的全排列共有$n!$种。所以对于基本区间共有$i!$种换序方式。

### Step3.换数

现在要把基本区间中的每个数加上任意一个$\le n-i$的自然数，考虑加法原理，对于这个自然数有$(n-i+1)$中选法。（什么？+1从哪来的？这个自然数可以为0啊！）

### Step4.换序

同Step3。



我们把上面四步全部算完之后，就可以开心相乘出结果了！最后我们就得到在区间长度为$i$的情况下区间个数$r_i=(n-i)!+i!+(n-i+1)^2$  
那么最后加法原理加和一下就可以得到：

$$r=\sum^{n}_{i=1} \quad (n-i)!+i!+(n-i+1)^2$$

计算即可。

## Code

我也不知道我为什么要用龟速乘和ull……

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() 
{
    register int x = 0 , ch = getchar(); 
    while( !isdigit( ch ) ) ch = getchar(); 
    while( isdigit( ch ) ) x = x * 10 + ch - '0' , ch = getchar();
    return x; 
}
unsigned long long quick_power(unsigned long long a,unsigned long long b,unsigned long long p)
{
    unsigned long long ans=1;
    while(b)
    {
        if(b%2)
        {
            ans=ans*a%p;        
        }
        a=a*a%p;
        b=(b>>1);
    }
    return ans;
}
unsigned long long turtle_muti(unsigned long long ain,unsigned long long bin,unsigned long long modn)
{
    unsigned long long res=0;
    for(;bin;bin>>=1) 
    {
        if(bin&1)
            res=(res+ain)%modn;
        ain=(ain<<1)%modn;
    }
    return res;
}
 
int n,m;
unsigned long long nfac[250010];
unsigned long long ans;
int main()
{
    n=read(),m=read();
    nfac[0]=1,nfac[1]=1;
    for(int i=2;i<=n;i++)
        nfac[i]=turtle_muti(nfac[i-1],i,m);
    for(int i=1;i<=n;i++)
    {
        unsigned long long qwq=1;
        qwq=turtle_muti(qwq,nfac[n-i],m);
        qwq=turtle_muti(qwq,nfac[i],m);
        qwq=turtle_muti(qwq,quick_power(n-i+1,2,m),m);
        ans+=qwq;
        ans%=m;
    }
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：Meatherm (赞：3)

首先有非常重要的一点，也是非常显然的一点。如果排列的一个子串 $b=[p_l,p_{l+1},...,p_r]$ 对答案有贡献，那么 $[l,r]$ 的数字一定是连续的。

让我们来单独考虑每一个长度的区间对答案的贡献。

对于一个长度为 $i$ 的区间且它对答案有贡献，那么有多少种排列使得这个区间存在呢？

组合数基本套路，因为区间不能分割，所以把这个长度为 $i$ 的区间看作一个整体，再计算排列数。于是有 $A_{n-i+1}^{n-i+1}=(n-i+1)!$ 种排列存在这个区间。

长度为 $i$ 的区间里可以是 $1,2,...,i$，也可以是 $2,3,...,i+1$，等等，只要它们是连续的就行。于是又可以乘上一个 $n-i+1$。

数字确定的区间，顺序是无所谓的，所以还要乘上 $A_{i}^{i}=i!$。

于是答案就呼之欲出了：

$$\sum _{i=1}^{n} \ \ \ \ (n-i+1)! \times i!\times (n-i+1)$$

阶乘要预处理一下，节省时间。最好开个 `long long`，保证你不会因为取模频率低了而 WA 掉。

```cpp
# include <bits/stdc++.h>
# define rr register
# define int long long
const int N=250010;
int MOD;
int n;
int sum;
int seque[N];
signed main(void){
	scanf("%I64d%I64d",&n,&MOD);//是 Codeforces 。千万不能用 %lld
	seque[0]=1;
	for(rr int i=1;i<=n;++i){
		seque[i]=(seque[i-1]*i)%MOD;
	}
	for(rr int i=1;i<=n;++i){
		sum=(sum+((n-i+1)%MOD*(seque[i])%MOD)%MOD*(seque[n-i+1])%MOD);
	}
	printf("%I64d",sum%MOD);
	return 0;
}
```

---

## 作者：qwq___qaq (赞：1)

排列数量太多，容易想到求解每个区间的贡献；又因为所有长度相等的区间等价，所以容易想到枚举区间的长度，然后乘上这个长度的数量。

对于一个区间 $[l,r]$，长度为 $r-l+1$，那么我们就可以得到 $\max\limits_{i=l}^ra_i-\min\limits_{i=l}^ra_i=r-l$。

我们可以先确定 $\min\limits_{i=l}^ra_i$，然后就能确定 $\max\limits_{i=l}^ra_i$，于是 $[l,r]$ 中的元素就在 $[\min\limits_{i=l}^ra_i,\max\limits_{i=l}^ra_i]$ 中。

也就是说，对于 $[l,r]$ 中的元素，只能选择 $[\min\limits_{i=l}^ra_i,\max\limits_{i=l}^ra_i]$ 中的 $r-l+1$ 个元素，那么就是 $A_{r-l+1}^{r-l+1}$。

对于 $\min\limits_{i=l}^ra_i$，可以得到 $\min\limits_{i=l}^ra_i+r-l\le n$，可以得到一共有 $n-r+l=n-(r-l+1)+1$ 种可能。

剩下的元素随便组合，答案就是 $A_{n-(r-l+1)}^{n-(r-l+1)}$。

也就是说，对于 $[l,r]$，答案就是 $A_{r-l+1}^{r-l+1}\times(n-r+l)\times A_{n-(r-l+1)}^{n-(r-l+1)}$。

那么对于一个长度 $x$，由 $l+x-1\le n$ 得。一共有 $n-x+1$ 个 $l$，对于每个 $l$，答案是 $A_x^x\times(n-x+1)\times A_{n-x}^{n-x}$。

那么 $x$ 的答案就是 $A_x^x\times A_{n-x}^{n-x}\times(n-x+1)^2$。

$x$ 可以取的范围是 $[1,n]$，所以答案就是 $\sum\limits_{x=1}^nA_x^x\times A_{n-x}^{n-x}\times(n-x+1)^2$，注意全排列要先初始化阶乘，时间复杂度 $O(n)$。

---

## 作者：Poncirus (赞：1)

算一个序列中有多少个合法数对是很麻烦的，那么不妨换个角度想，对于每个数对，计算能被多少个序列包含。

容易发现对于 $[l, r]$，设最小值为 $l + v$，最大值为 $r + v$，那么剩余的 $r-l-1$ 个数既不能比 $l+v$ 小，也不能比 $r+v$ 大，还不能重复，那么就与 $(l+v,r+v)$ 对应。也就是说，左端点的值确定后，区间包含元素唯一确定。

对于所有长度为 $i$ 的区间，左端点有 $n-i+1$ 种选择，区间所在的位置有 $n-i+1$ 种选择，区间可任意排列，不影响极差，所以有 $A_i^i$ 种排列方式，除该区间以外的数有 $A_{n-i}^{n-i}$ 种排列方式（这一步，因为每个数列的每个合法区间都要计算，所以不用对该区间之外的合法区间去重）。

乘法原理，全部相乘即可得到长度为 $i$ 的所有区间的答案，枚举 $i$，相加即可。

特别地，对于长度为 $1$ 的区间，每个区间都被 $A_n^n$ 个区间包含，共有 $n\times A_n^n$ 个。


```cpp
namespace XSC062 {
using namespace fastIO;
const int maxn = 2.5e5 + 15;
int n, mod, ans;
int u[maxn], inv[maxn];
inline int qkp(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1)
			(res *= x) %= mod;
		(x *= x) %= mod;
		y >>= 1;
	}
	return res;
}
inline void Init(int n) {
	u[0] = 1;
	inv[0] = 1;
	for (int i = 1; i <= n; ++i) {
		u[i] = (u[i - 1] * i) % mod;
		inv[i] = qkp(u[i], mod - 2);
	}
	return;
}
inline int A(int n, int m) {
	return (u[n] * inv[n - m]) % mod;
}
int main() {
	read(n);
	read(mod);
	Init(n + 5);
	ans = (A(n, n) * n) % mod;
	for (int i = 2; i <= n; ++i) {
		(ans += (((n - i + 1) * (n - i + 1)) % mod
				* A(i, i)) % mod * A(n - i, n - i)
				% mod) %= mod;
	}
	printf("%lld", ans);
	return 0;
}
} // namespace XSC062
```

---

## 作者：I_am_Accepted (赞：1)

有任何关于此篇题解的问题皆可私信[我](https://www.luogu.com.cn/user/101868)。

### 题目分析

其实也就是 **$p_l$ 到 $p_r$ 内是一组连续的数的集合**呗。

接下来我们来算贡献，考虑每一个长度的区间对答案的贡献。

对一个长度为 $k$ 的连续区间，我们选这个区间**在原序列的位置有 $n-k+1$ 种选法**，将这 $k$ 个数**打乱有 $k!$ 种方法**。

然后合法的方案要求选择的区间内元素连续，所以**把这个区间看成一个整体元素**，和其他 $n-k$ 个数做个排列，有 $(n-k+1)!$ 种方法。

例如：

![](https://i.loli.net/2021/07/25/qkofHQxUzw8jECc.png)

统计每种长度的区间，所以**答案就是 $\sum_{k=1}^n(n-k+1)!k!(n-k+1)$**。

时间复杂度 $O(n)$

### Details

写给像我一样的数论新手：**预处理**出每个数的阶乘的模数。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,j,k) for(register int i=j;(j<k)?(i<=k):(i>=k);i+=(j<k)?1:(-1))
#define IO ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 255000

ll n,mod;
ll f[N];//带模阶乘 
ll sum=0;//ans求和 
void init(){
	f[0]=1;
	FOR(i,1,n) f[i]=f[i-1]*i%mod;
}
signed main(){
    IO;
    cin>>n>>mod;
    init();
    FOR(i,1,n) sum=(sum+f[n-i+1]*f[i]%mod*(n-i+1)%mod)%mod;
	cout<<sum<<endl;
    return 0;
}
```

---

## 作者：gyh20 (赞：1)

$n$过大，考虑算贡献。

对于一个长度为$len$的合法区间，它的最小值有$(n-len+1)$种方案，然后该区间内部有$len!$种摆放方案，外部有$(n-len)!$种摆放方案，而长度为$len$的区间有$(n-len)+1$个，所以最终答案即为$∑le n!*(n-len)!*(n-len+1)^2$

代码如下(和第一题差不多长):

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0'||v>'9')v=getchar();
	while(v>='0'&&v<='9'){
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t;
}
long long n,m,jc[250002];
long long ans;
int main(){
n=read();
m=read();
jc[0]=1;
for(re int i=1;i<=n;++i)jc[i]=jc[i-1]*i%m;
for(re int i=1;i<=n;++i){
	ans+=(n-i+1)*jc[i]%m*(n-i+1)%m*jc[n-i]%m;
	ans%=m;
}
printf("%lld",ans);
}
```


---

## 作者：Grisses (赞：0)

upd:累加漏了一项。

[题面](https://www.luogu.com.cn/problem/CF1284C)

因为题目要求的是 $n$ 的排列，所以符合条件的 $l,r$ 一定是满足一段连续的长度为 $r-l+1$ 的数在一起。

所以我们枚举这个长度。

对于长度为 $len$ 的一串数，他们有 $n-len+1$ 种选择。同时又有 $n-len+1$ 个位置供他们选择。并且内部有 $A_{len}^{len}$ 种排列方式，然后其他的 $n-i$ 个数有 $(n-1)!$ 种排列方式。所以总共的方案数就是 $(n-len+1)^2\times A_{len}^{len}\times (n-i)!$。

答案就是对其累加求和。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,mod;
  long long ans,C[250005];
  signed main()
  {
      scanf("%d%d",&n,&mod);
      C[0]=1;
      for(int i=1;i<=n;i++)C[i]=C[i-1]*i%mod;//预处理阶乘
      for(int i=1;i<=n;i++){
          ans=(ans+1LL*(n-i+1)*C[i]%mod*(n-i+1)%mod*C[n-i]%mod)%mod;//求和
      }
      printf("%lld",ans);
      return 0;
  }

```

---

## 作者：liuyz11 (赞：0)

# 题解 CF1284C 【New Year and Permutation】

[本场比赛的题解](https://www.cnblogs.com/nblyz2003/p/12151883.html)

题目大意：这题的翻译就是我提供的，删掉了。

这道题一开始看的时候有点慌，浪费了好多时间。

后来一想，不就分别统计长度为i的子段满足条件。

我们可以很轻松的求出不同子段出现次数，所有该长度的子段出现次数为:

    排列个数×每个排列中出现的次数 = n！×（n - i +1）

然后该长度不同子段的个数为n！/ (n - i)！，稍微证明一下或者列举几个便可以得出。

然后求所有符合条件的字段个数，(1，2，…，i ) 到（n - i + 1，n - i + 2，…， n ）一共有n - i + 1种，然后每种的排列有i！个。

    所有长度为i的字段对答案的贡献 = 不同子段的出现个数 × 符合的长度为i子段的个数

    = n！× (n - i + 1) / ( n！/ ( n - i )！) × ( n - i + 1 ) × i！

    = ( n - i )！ × ( n - i + 1) × ( n - i +1 ) × i！

这个式子看上去挺好看的，然后求个总和就好。

代码特别短：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 250005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
int p;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int pow[MAXN];

int main(){
	int n;
	scanf("%d%d", &n, &p);
	pow[0] = 1;
	rep(i, 1, n){
		pow[i] = 1ll * pow[i - 1] * i % p;
	}
	int ans = 0;
	rep(i, 1, n){
		int s = 1ll * pow[n - i] * (n - i + 1) % p * (n - i + 1) % p * pow[i] % p;
		ans = (ans + s) % p;
	}
	printf("%d\n", ans);
    return 0;
}

```


---

## 作者：Kewth (赞：0)


直接考虑一个排列的贡献是不现实的，应分离算贡献，考虑每个连续的段出现的次数。

枚举段长 $l$ 和段中最大值 $x$ ，那么这段就是由 $x - l + 1$ 到 $x$ 构成的一个连续区间。

这个区间在所有排列的出现次数是很好统计的，首先在 $n$ 个位置选出长为 $l$ 的区间的方案为 $n - l + 1$ ，  
然后段内随意排列，方案为 $l!$ ，段外随意排列，方案为 $(n - l)!$ 。

然而枚举 $l, x$ 是 $O(n^2)$ 的，但是从上面的分析不难看出一个长为 $l$ 的区间的出现次数与 $x$ 无关。

那么只需要 $O(n)$ 枚举 $l$ ，其对应的 $x$ 有 $(n - l + 1)$ 个。

也就是说答案为 $\sum_{l=1}^n l! (n-l)! (n-l+1)^2$ 。

参考实现：

```cpp
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 250005;
ll fac[maxn];

int main() {
	int n = read, mod = read;

	fac[0] = 1;
	for(int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;

	ll ans = 0;
	for(int l = 1; l <= n; l ++)
		(ans += fac[l] * fac[n - l] % mod * (n - l + 1) % mod * (n - l + 1)) %= mod;
	printf("%lld\n", ans);
}

```

---

## 作者：caidzh (赞：0)

~~简单的组合数学题？~~

先加上长度为$1$的序列的贡献：$n\times n!$

我们枚举$d=r-l$，显然它可以在排列中找出$n-d$个位置去放我们的合法序列（比如$1,2,3$就是一个$d=2$的合法序列）

我们可以选择最大值和最小值，有$n-d$种选择，然后把最大值和最小值放进序列，有$d(d+1)$种选择

在这个长度为$d+1$的合法序列中，还有$d-1$个位置等待填入，由于我们只能选择最大值和最小值之间的数，所以直接排列，有$(d-1)!$种选择

剩下还有$n-d-1$个数，直接排列，有$(n-d-1)!$种选择，因此最终的式子是：

$$\sum_{d=1}^{n-1}(n-d)^2(d+1)!(n-d-1)!+n\times n!$$

这个式子通过预处理阶乘就可以$O(n)$算，那么这题就做完了

---

