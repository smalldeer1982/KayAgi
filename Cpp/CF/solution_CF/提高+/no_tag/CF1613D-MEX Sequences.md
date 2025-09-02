# MEX Sequences

## 题目描述

我们定义一个整数序列 $x_{1}, x_{2}, \ldots, x_{k}$ “MEX 正确”，当且仅当：

对于每一个 $i$（$1 \le i \le k$），都满足 $\lvert x_{i} − \operatorname{MEX}(x_{1},x_{2}, \ldots , x_{i})\rvert \le 1$。

其中，$\operatorname{MEX}(x_{1},x_{2},\ldots,x_{k})$ 即整数序列 $x_{1},x_{2},\ldots,x_{k}$ 中未出现的最小非负整数。例如，$\operatorname{MEX}(1,0,1,3)=2$、$\operatorname{MEX}(2,1,5)=0$。

给定一个由 $n$ 个非负整数组成的数组 $a$。计算给定数组的非空 “MEX 正确” 子序列的数量。子序列的数量可能非常大，因此请将答案对 $998244353$ 取模后输出。

注意：数组 $a$ 的子序列即满足 $1 \le i_{1} < i_{2} < \cdots < i_{m} \le n$ 的序列 $a_{i_{1}}, a_{i_{2}}, \ldots, a_{i_{m}}$。我们认为，当两个子序列中至少存在一个元素在原数组中的下标不同时，这两个子序列不同（即两个子序列所对应的$i_{1}, i_{2}, \ldots, i_{m}$ 不同时，这两个子序列不同）。

## 说明/提示

在样例的 $4$ 组数据中：

第一组中，可行的子序列是 $[0] , [1] , [0,1]$ 和 $[0,2]$。

第一组中，可行的子序列是 $[0] , [1]$。

第三组中，每个非空子序列都是可行的。

## 样例 #1

### 输入

```
4
3
0 2 1
2
1 0
5
0 0 0 0 0
4
0 1 2 3```

### 输出

```
4
2
31
7```

# 题解

## 作者：FifthAxiom (赞：10)

题目大意：

对于一个非负整数序列 $a_1,a_2\cdots,a_n$ ，若该序列满足 $\forall i=1\cdots n$ 都有 $a_i\le|\operatorname{MEX}(a_1,a_2,\cdots,a_i)|$ ，则称其为合法序列 （$\operatorname{MEX}$ 的意义与 $\operatorname{SG}$ 函数中的意义相同，即不在集合中的最小非负整数），给定一个非负整数序列，求合法子序列个数，对 $998244353$ 取模。

## Solution

首先题意中有一个坑点：

>我们定义满足 $\forall i=1\cdots n$ 都有 $a_i\le|\operatorname{MEX}(a_1,a_2,\cdots,a_i)|$ 的序列为合法序列。

因此我们必须按原序统计。

考虑设计一个暴力的 dp ，设 $f(i,s)$ 表示在整个序列的前 $i$ 个数中选，且最后一个数恰好为 $a_i$ ，且 $\operatorname{MEX}(\cdots,a_i)=\begin{cases}a_i-1\quad(s=0)\\a_i+1\quad(s=1)\end{cases}$ 的合法子序列个数，容易列出转移方程：

$$
\begin{aligned}
f(i,0)&=\sum_{j=1}^{i-1}(f(j,0)[a_j=a_i]+f(j,1)[a_j=a_i-2])\\
f(i,1)&=\sum_{j=1}^{i-1}(f(j,0)[a_j=a_i+2]+f(j,1)[a_j=a_i])
\end{aligned}
$$

但是这个 dp 是 $\Theta(n^2)$ 的。不能满足数据范围。但是通过观察数据范围可以发现 $0\le a_i\le n$ 。这是一个很奇怪的性质，它启发我们重新设计一个在 $\operatorname{MEX}$ 值域上进行的 dp 。

设 $f(i,j,s)$ 表示在整个序列的前 $i$ 个数中选，且 $\operatorname{MEX}(\cdots,a_k)=j$ （$a_k$ 表示子序列的最后一个数，以下简记为 $\operatorname{MEX}$），且 $a_k=\begin{cases}j-1\quad(s=0)\\j+1\quad(s=1)\end{cases}$  的合法序列个数。对于每一个输入的 $x$ ，它所能影响的状态显然只有 $f(i,x+1,s)$ 和 $f(i,x-1,s)$ ，所以我们可以由 $x$ 计算每个被影响的状态：

===========

**1. 前 $i$ 个数中 $\operatorname{MEX}=x+1$ 且 最后一个数为 $x$ 的序列，它有三种构造可能：**

1.1. 前 $i-1$ 个数中 $\operatorname{MEX}=x+1$ 且 最后一个数为 $x$ 的序列

1.2. 前 $i-1$ 个数中 $\operatorname{MEX}=x+1$ 且 最后一个数为 $x$ 的序列的末尾添上 $x$ 

1.3. 前 $i-1$ 个数中 $\operatorname{MEX}=x$ 且 最后一个数为 $x-1$ 的序列的末尾添上 $x$ ，这会使得 $\operatorname{MEX}$ 变为 $x+1$

$$
f(i,x+1,0)=2f(i-1,x+1,0)+f(i-1,x,0)
$$

===========

**2. 前 $i$ 个数中 $\operatorname{MEX}=x+1$ 且 最后一个数为 $x+2$ 的序列，它有二种构造可能：**

2.1 前 $i-1$ 个数中 $\operatorname{MEX}=x+1$ 且 最后一个数为 $x+2$ 的序列

2.2前 $i-1$ 个数中 $\operatorname{MEX}=x+1$ 且 最后一个数为 $x+2$ 的序列的末尾加上 $x$

$$
f(i,x+1,1)=2f(i-1,x+1,1)
$$


===========

**3. 前 $i$ 个数中 $\operatorname{MEX}=x-1$ 且 最后一个数为 $x$ 的序列，它有三种构造可能：**

3.1 前 $i-1$ 个数中 $\operatorname{MEX}=x-1$ 且 最后一个数为 $x$ 的序列

3.2 前 $i-1$ 个数中 $\operatorname{MEX}=x-1$ 且 最后一个数为 $x$ 的序列的末尾加上 $x$

3.3 前 $i-1$ 个数中 $\operatorname{MEX}=x-1$ 且 最后一个数为 $x-2$ 的序列的末尾加上 $x$

$$
f(i,x-1,1)=2f(i-1,x-1,1)+f(i-1,x-1,0)
$$

剩下的所有状态都只有从前面的 $i-1$ 个数中选的构造可能，因此直接继承上一阶段的状态即可。

最后的答案为

$$
\sum_{i=0}^n(f(n,i,0)+f(n,i,1))
$$

发现同一阶段的状态都可以直接由上一阶段的状态转移过来，因此我们可以舍去第一维，边读入边转移。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;

typedef long long LL;

const int N = 5e5 + 10, P = 998244353;

namespace io {
  const int SIZE = (1 << 21) + 1;
  char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
  #define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
  char getc () {return gc();}
  inline void flush () {fwrite (obuf, 1, oS - obuf, stdout); oS = obuf;}
  inline void putc (char x) {*oS ++ = x; if (oS == oT) flush ();}
  template <class I> inline void gi (I &x) {for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;}
  template <class I> inline void print (I x) {if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;while (x) qu[++ qr] = x % 10 + '0',  x /= 10;while (qr) putc (qu[qr --]);}
  struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io::gi; using io::putc; using io::print; using io::getc; using io::flush;

int n;
LL f[N][2];

int power(int a, int b) {
    int res = 0;
    for (; b; b >>= 1) {
        if (b & 1) res = (LL)res * a % P;
        a = (LL)a * a % P;
    }
}

int main() {
    //ios::sync_with_stdio(false), cin.tie(NULL);
    
    int T;
    gi(T);
    
    while (T--) {
        gi(n);
        
        for(int i = 0; i <= n; i++) f[i][0] = f[i][1] = 0;
        f[0][0] = 1;//我们这里为了方便计算直接设f(0,0)=1,注意最后算答案时减回来
        for (int i = 1; i <= n; i++) {
            int x;
            gi(x);
            //mex = x + 1
            f[x + 1][0] = f[x + 1][0] * 2 % P;
            f[x + 1][1] = f[x + 1][1] * 2 % P;
            //mex = x
            f[x + 1][0] = (f[x + 1][0] + f[x][0]) % P;
            //mex = x - 1
            if (x) {
                f[x - 1][1] = f[x - 1][1] * 2 % P;
                f[x - 1][1] = (f[x - 1][1] + f[x - 1][0]) % P;
            }
        }
        
        LL res = -1;
        for (int i = 0; i <= n; i++) res = (res + f[i][0] + f[i][1]) % P;
        
        print(res);
        putc('\n');
        flush();
    }
    
    return 0;
}
```

---

## 作者：XL4453 (赞：8)

### 解题思路：

考虑动态规划。

设 $f_{i,j,0/1}$ 表示到第 $i$ 位为止 $MEX$（$MEX$ 同原题定义）等于 $j$ 的方案数，$0$ 表示没有比 $MEX$ 大一的数，$1$ 则表示有。

当出现了在第 $i$ 位的一个数 $j$，推出可能的可以构成的方案是 $f_{i-1,j,0}$、$f_{i-1,j+1,0}$、$f_{i-1,j+1,1}$、$f_{i-1,j-1,0}$、$f_{i-1,j-1,1}$，分别表示 $MEX$ 等于 $j$ 且不存在数 $MEX+1$ 即 $j+1$，$MEX$ 等于 $j+1$ 的有或者没有 $MEX+1$ 即 $j+2$ 两种，$MEX$ 等于 $j-1$ 的有或者没有 $MEX+1$ 即 $j$ 两种。

注意如果选择 $MEX$ 等于 $j$ 且此时存在 $MEX+1$，就会将当前 $MEX$ 直接增大到 $MEX+2$，不满足要求，故不能取。

---

然后考虑对于 $f$ 数组的转移，考虑选择了 $j$ 之后有哪些状态可能存在新的方案，首先所有的 $f_{i,j,0/1}$ 都有对应的 $f_{i-1,j,0/1}$ 种方案，也就是直接不取，$f_{i,j+1,0}$ 可以由 $f_{i-1,j-1,0}$ 和 $f_{i-1,j+1,0}$（选择了之后 $MEX$ 不变，但是确实是一种新的方案）转移，$f_{i,j+1,1}$ 可能方案数是，$f_{i,j-1,1}$ 可以由 $f_{i-1,j-1,1}$ 转移，$f_{i,j-1,1}$ 此时由于存在了 $MEX+1$，可以由 $f_{i,j-1,0}$ 和 $f_{i,j-1,1}$ 转移过来。

直接这样做不可取，注意到第一维其实可以直接压掉，那么空间就只剩下两维了，其中还有一维是常数。

初始时，$f_{0,0}$ 为 $1$，因为直接不取就是一种可行的方案。

---
注意取模。

---
### 代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define int long long
int T,n,a[500005],f[500005][2],ans;
const int MOD=998244353;
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d",&n);
		for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
		for(int i=0;i<=n+2;i++)f[i][0]=f[i][1]=0;
//		memset(f,0,sizeof(f));
		f[0][0]=1;ans=0;
		for(int i=1;i<=n;i++){
			ans=(ans+f[a[i]][0])%MOD;
			ans=(ans+f[a[i]+1][0]+f[a[i]+1][1])%MOD;
			if(a[i]>=1)ans=(ans+f[a[i]-1][0]+f[a[i]-1][1])%MOD;
			
			f[a[i]+1][0]=(f[a[i]+1][0]+f[a[i]][0]+f[a[i]+1][0])%MOD;
			f[a[i]+1][1]=(f[a[i]+1][1]+f[a[i]+1][1])%MOD;
			if(a[i]>=1){
				f[a[i]-1][1]=(f[a[i]-1][1]+f[a[i]-1][1]+f[a[i]-1][0])%MOD;
			}
		}
		printf("%I64d\n",ans%MOD);
	}
	return 0;
}
```


---

## 作者：Genius_Star (赞：4)

### 题意：

求满足以下条件的子序列 $(a_{i_1},a_{i_2},\ldots,a_{i_m})$ 的数量：

对任意的 $j$ ，有 $|a_{i_j}-\operatorname{MEX}(a_{i_1},a_{i_2},\ldots,a_{i_j})| \le 1$。

### 思路：

这里提供一种码量少，思路也很简单的做法。

我们知道，$\operatorname{MEX}$ 是序列中未出现的最小非负整数，所以想要满足以上条件，对于任意的 $j$，$\operatorname{MEX}(a_{i_1},a_{i_2},\ldots,a_{i_j})$ 的值必须比 $a_{i_j}$ 大 $1$ 或者少 $1$。

所以，我们对于对答案有贡献的子序列有以下两种定义：

- 设 $x$ 为该子序列里面的最大值，$\operatorname{MEX}$ 的值比 $x$ 大 $1$，则这个序列需要包含 $[0,x]$ 中的所有整数。（$1$ 号子序列）

- 设 $x$ 为该子序列里面的最大值，$\operatorname{MEX}$ 的值比 $x$ 小 $1$，则这个序列需要包含 $[0,x-2]$ 中的所有整数，并不能包含 $x-1$。（$2$ 号子序列）

对于 $1$ 号子序列，如果要再选一个数，还要保持 $\operatorname{MEX}$ 的值不变，我们只能选择 $x,x+1,x+2$，我们发现，选择 $x$ 和 $x+1$ 之后，该序列仍然是 $1$ 号子序列，选择 $x+2$ 之后就转化为了 $2$ 号子序列。

对于 $2$ 号子序列，如果要再选一个数，还要保持 $\operatorname{MEX}$ 的值不变，我们只能选择 $x-2,x$，这样选择不会变成 $1$ 号字符串。

对于以上的字符串定义，我们考虑动态规划求解答案，我们定义 $dp_{i,0/1}$ 为最大值为 $i$ 的序列中 $1/2$ 号字符串的方案个数，我们定义空串是 $1$ 号字符串，即 $dp_{0,0}=1$。

对于 $1$ 号字符串的状态转移方程：

$$dp_{a_i,0}=2 \times dp_{a_i,0}+dp_{a_i-1,0}$$

可以选择原数 $a_i$，所以对于自身要 $\times 2$，因为选择 $a_i+1$ 的 $\operatorname{MEX}$ 也不变，可以由 $a_{i-1}$ 的值转移过来。

对于 $2$ 号字符串的状态转移方程：

$$dp_{a_i,1}=2 \times dp_{a_i,1}+dp_{a_i-2,0}$$

也可以选择原数 $a_i$，同时 $1$ 号字符串选择 $a_i+2$ 会转化为 $2$ 号字符串，所以要转移过来。

并且，对于 $2$ 号字符串，选择 $a_i-2$ 也会保持 $\operatorname{MEX}$ 不变，那么：

$$dp_{a_i+2,1}=2 \times dp_{a_i+2,1}$$

最后将每一项的 $dp_{i,0/1}$ 的值加起来就是最终的答案了。

这样，我们就在 $O(T \times n)$ 的时间内解决了这个问题。

~~注意取模！~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=500500;
const ll mod=998244353;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
int T,n,ans=0;
int main(){
	T=read();
	while(T--){
		ans=0;
		n=read();
		ll a[n+1],dp[n+4][2]={0};
		for(int i=1;i<=n;i++)
		  a[i]=read()+1;
		dp[0][0]=1;
		for(int i=1;i<=n;i++){
			dp[a[i]][0]=(2*dp[a[i]][0]+dp[a[i]-1][0])%mod;
			dp[a[i]][1]=(dp[a[i]][1]*2)%mod;
			dp[a[i]+2][1]=(dp[a[i]+2][1]*2)%mod;
			if(a[i]>1)
			  dp[a[i]][1]=(dp[a[i]][1]+dp[a[i]-2][0])%mod;
		}
		for(int i=1;i<=(n+1);i++)
		  ans=(ans+dp[i][0]+dp[i][1])%mod;
		write(ans);
		putchar('\n'); 
	}
	return 0;
}
```


---

## 作者：Exber (赞：3)

## 做法

暴力 dp。

我们可以考虑**令 $dp_{j}$ 表示当前 $\operatorname{MEX}=j$ 的子序列数**，那么初始状态显然是 $dp_0=1$ 即空序列的 $\operatorname{MEX}=0$。

接下来观察到，$\operatorname{MEX}(x_1,x_2,\dots,x_i)\not=x_i$，所以它**只有两种情况**。那么转移显然是

$$\begin{cases}dp_{x_i+1}\to dp_{xi+1}+dp_{xi}+dp_{xi+1}\\dp_{x_i-1}\to dp_{xi-1}+dp_{xi-1}\end{cases}$$

但是有一个问题，**$x_i$ 加入之后 $\operatorname{MEX}$ 不一定是 $x_i+1$**。例如这个 $\operatorname{MEX}=4$ 的合法序列：

$$0,1,2,3,5$$

在加入 $4$ 后，变成了这样：

$$0,1,2,3,5,4$$

这时 $\operatorname{MEX}=6$，但是我们的程序认为 $\operatorname{MEX}=5$。

所以考虑给 dp 状态加一维，**令 $dp_{j,0/1}$ 表示当前 $\operatorname{MEX}=j$，序列中没有/有 $j+1$ 的子序列数**。那么**初始状态为 $dp_{0,0}=1$**，有转移：

$$\begin{cases}dp_{x_i+1,0}\to dp_{x_i+1,0}+dp_{x_i,0}+dp_{x_i+1,0}\\dp_{x_i+1,1}\to dp_{x_i+1,1}+dp_{x_i+1,1}\\dp_{x_i-1,1}\to dp_{x_i-1,1}+dp_{x_i-1,0}+dp_{x_i-1,1}\end{cases}$$

最后**不要忘了给 $dp_{0,0}$ 减去 $1$ 因为不包含空序列**，并且不要忘记取模。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int mod=998244353;

int n,a[1919810];
long long dp[1919810][2];

inline void slove()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=0;i<=n;i++)
	{
		dp[i][0]=dp[i][1]=0;
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		dp[a[i]+1][0]=(dp[a[i]+1][0]+dp[a[i]][0]+dp[a[i]+1][0])%mod;
		dp[a[i]+1][1]=(dp[a[i]+1][1]+dp[a[i]+1][1])%mod;
		if(i>0)
		{
			dp[a[i]-1][1]=(dp[a[i]-1][1]+dp[a[i]-1][0]+dp[a[i]-1][1])%mod;
		}
	}
	long long ans=0;
	dp[0][0]=(dp[0][0]-1+mod)%mod;
	for(int i=0;i<=n;i++)
	{
		ans=(ans+dp[i][0]+dp[i][1])%mod;
	}
	printf("%lld\n",ans);
}

int main()
{
	int _;
	scanf("%d",&_);
	while(_--)
	{
		slove();
	}
	return 0;
}
```

---

## 作者：RockyYue (赞：1)

### 题意

定义序列 $x_{1...k}$ 是“好的”，当且仅当对于所有 $i$，满足 $|x_i-MEX(x_1,x_2,...,x_i)|\le 1$。

给定序列 $a_{1...n}$，求有多少个子序列是好的。

其中 $n\le 5\times 10^5,0\le a_i\le n$。

### 做法

若一个子序列是好的，则其所有前缀必然都是好的，故考虑 dp 转移。

设 $f_{i,j}$ 为在 $a_{1...i}$ 中选择子序列，其 MEX 为 $j$ 的方案数。这里之所以不记录子序列最后一位是因为没有必要，只需要用 $i$ 之前的位转移即可。

但是我们发现这样并不能很好地转移，因为我们不能确定在添加了之前区间 MEX 后接下来的 MEX，这个 MEX $+1$ 是否会出现，故我们添加一维 $s\in \{0,1\}$，表示在之前的条件下是否出现过 $j+1$。

则答案为 $\sum_{i=1}^n{f_{i-1,a_i-1,0/1}+f_{i-1,a_i,0}+f_{i-1,a_i+1,0/1}}$。

接下来考虑转移。首先根据定义，$a_i$ 这一位是可以不选的，故 $f_{i,j,s}+=f_{i-1,j,s}$，接下来逐个考虑。

1. $MEX=a_i-1$ $f_{i,a_i-1,1}+=f_{i-1,a_i-1,0/1}$

2. $MEX=a_i+1$

   这里考虑一件事，若 $a_i+2$ 出现过，那么之前的 MEX 至少为 $a_i+1$。因为若 $MEX\le a_i$，那么在 $a_i+2$ 出现时也有 $MEX\le a_i$，此时这个前缀便不是“好的”。那么就可以得到下面的转移。

   $f_{i,a_i+1,1}+=f_{i-1,a_i+1,1}$

   $f_{i,a_i+1,0}+=f_{i-1,a_i,0}+f_{i-1,a_i+1,0}$

这样我们就可以在 $O(n)$ 的时间内完成转移，发现第一维状态可以压缩，空间也达到 $O(n)$。

---

## 作者：Alex_Wei (赞：1)

> *CF1613D. [MEX Sequences](https://codeforces.com/problemset/problem/1613/D)

好题。乍一看没啥思路，考虑挖掘性质：

- *observation 1.* 若出现 $v$，则之后不可能出现 $v-1$。

    不妨设 $x_p=v$，显然 $\mathrm{mex}_{i=1}^px_i$ 等于 $v+1$ 或 $v-1$。无论哪种情况在添加 $v-1$ 后 $\mathrm{mex}$ 都一定 $\geq v+1$，不符题意。

- *observation 2.* 若 $x_{p-1}+2=x_p$，那么 $x_q\ (q>p)$ 只能为 $x_p$ 或 $x_p-2$。

    因为 $x_q$ 不能为 $x_p-1$，而 $x_{p}-1$ 又没有出现过所以接下来的 $\mathrm{mex}$ 值只能为 $x_{p}-1$。得证。

- *observation 3*. 用 $\overline{v}$ 表示连续若干个 $v$，符合题意的序列一定满足形如 $\overline{0},\overline{1},\cdots,\overline{v-2},(\overline{v},\overline{v-2}\cdots)$ **或者 $\overline{1}$**，其中括号是不需要出现的部分。

    - $x_{p}-3\geq x_{p+1}$ 不可能出现。
    - 根据 observation 1 不可能出现 $x_p-1=x_{p+1}$。
    - 若 $x_p-2=x_{p+1}$，此时 $\mathrm{mex}$ 值一定为 $x_p-1$。那么前面必然是从 $0$ 连续递增到 $x_{p}-2$ 的一段，因为若前面这一段有下降的部分，那么只能是下降 $2$，但根据 observation 2 接下来 $\mathrm{mex}$ 不可能上升，不符合题意。

    - $x_p=x_{p+1}$ 或 $x_p+1=x_{p+1}$ 是平凡的。

    - $x_p+2=x_{p+1}$ 只能出现在 observation 2 所述的情况中，不会使 $\mathrm{mex}$ 增加。
    - $x_p+3\leq x_{p+1}$ 不可能出现。

    $\overline{1}$ 的情况平凡。证毕。

考虑设 $g_i$ 表示 $1\sim i$ 有多少以 $a_i$ 结尾的，单调不减且相邻两个数相差不超过 $1$ 的子序列。转移时记录 $f_v$ 表示以 $v$ 结尾的序列个数，那么若 $a_i=0$ 则 $g_i=f_0+1$，若 $a_i>0$ 则 $g_i=f_{a_i}+f_{a_i-1}$。不要忘记令 $f_{a_i}\gets f_{a_i}+g_i$。

接下来只需要考虑对于每个位置 $i$，$i+1\sim n$ 有多少以 $a_i+2$ 开头且在 $a_i$ 和 $a_i+2$ 之间来回震荡的子序列。考虑从后往前 DP：设 $c_v$ 表示以 $v$ 开头且在 $v$ 和 $v-2$ 之间来回震荡的子序列个数，$d_v$ 则表示 $v$ 和 $v+2$。这两个之间可以相互转移：
$$
c_{a_i}\gets 2c_{a_i}+d_{a_i-2}+1\\
d_{a_i}\gets 2d_{a_i}+c_{a_i+2}+1
$$
统计答案就比较简单了，首先正序处理出 $g_i$，然后倒序计算 $c,d$，过程中令答案加上 $g_i\times (c_{a_i+2} + 1)$ 即可。不要忘记最后 $\overline{1}$，计算方案数是平凡的（实际上就是 $c_1$）。时间复杂度线性。

```cpp
const int N = 5e5 + 5;
const int mod = 998244353;
void add(int &x, int y) {x += y; x >= mod && (x -= mod);}
int n, a[N], f[N], g[N], c[N], d[N];
void solve() {
	cin >> n, mem(f, 0, n + 2), mem(c, 0, n + 2), mem(d, 0, n + 2);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		add(f[a[i]], g[i] = (f[a[i]] + (a[i] ? f[a[i] - 1] : 1)) % mod);
	int ans = 0;
	for(int i = n; i; i--) {
		add(c[a[i]], (c[a[i]] + (a[i] >= 2 ? d[a[i] - 2] : 0) + 1) % mod);
		add(d[a[i]], (d[a[i]] + c[a[i] + 2] + 1) % mod);
		add(ans, 1ll * g[i] * (c[a[i] + 2] + 1) % mod);
	} cout << (ans + c[1]) % mod << endl;
}
int main(){
	int T; cin >> T; while(T--) solve();
	return 0;
}
```

---

## 作者：Chivas_Regal (赞：1)

# 任务缩减  
首先我们要弄清楚，什么样的序列可以满足 *MEX-Correct*  
由于一个序列前缀长度从小到大，它的 $MEX$ 一定不会降低，既然我们这个序列要满足 $|a_1-mex|\le1$ 同时 $|a_k-MEX|\le1$  
所以 $mex$ 前面是要一个一个往后推进每次进 $1$  

**长度 $=1$ ：**  
$1.$ 只有 $0$ 和 $1$  满足  

**长度 $\neq1$ ：**  
$1.$ 要从 $1$ 开始可以一个个推进，所以从 $0$ 开始的连续非递减子序列满足，如 $(0,0,1,1,2,3)$  
$2.$ 最后可以以 $mex$ 为中心，成为 $(mex-1,mex+1)$ 这样的跳跃，所以满足条件 $(1)$ 并且结尾反复如上跳跃的序列也满足  
  
我们知道以数值往后推方案数，可以以数值为下标记录递推  

# 状态表示  
我们将上面两种大情况分成：  
$1.dp1[]$ ：连续推进序列（以 $0$ 开头  
$2.dp2[]$ ：非连续推进序列（不以 $0$ 开头或者结尾产生跳跃  
   
这两个 $dp.[x]$ 都以 $x$ 这个数做下标进行递推  
  
# 基本的状态转移  

$x$ 结尾连续的序列只可以跟进 $x-1$ 结尾的连续序列 $(1,2,\dots,x-1,x)$  
与之前算的 $x$ 结尾的连续序列 $(1,2,\dots,x,x)$  
$dp1[x]=dp1[x]+(dp1[x]+dp1[x-1])$  
  
$x$ 结尾的不连续序列可以跟进 $x-2$ 结尾的连续子序列 $(1,2,\dots,x-2,x)$   
与以 $x$ 结尾的不连续序列  $(1,2,\dots,x-2,x,x)$  
$dp2[x]=dp2[x]+(dp2[x]+dp1[x-2])$  
  
$x$ 结尾的不连续序列可以跟进 $x+2$ 结尾的不连续序列 $(1,2,\dots,x+2,x)$  
>但是要注意这个是 $x$ 贡献给 $x+2$ ，不然可能会出现 $(x-2,x,x+2)$ 这样的跳步或者 $(x,x+2,x,x,x)$ 这种后面 $x$ 少计数的情况  

$dp2[x+2]=dp2[x+2]+(dp2[x+2])$  
  
## 转移方程特殊处理  
$x=0$ ：  
没有 $x-2$ 与 $x-1$ 所以忽略加和 $dp1[x-2]$ 与 $dp1[x-2]$  
自己也没有不连续序列，所以忽略 $dp2[x]$  
自己可以作为一个单独的连续序列，所以 $dp1[x]$ 额外加一

```cpp
dp1[x] += dp1[x]; dp1[x] ++;   dp1[x] %= mod;
dp2[x + 2] += dp2[x + 2];      dp2[x + 2] %= mod;
```  
$x=1$ ：  
没有 $x-2$ 忽略 $dp1[x-2]$  
自己单独成为不连续序列，所以 $dp2[x]$ 额外加一  

```cpp
dp1[x] += dp1[x] + dp1[x - 1]; dp1[x] %= mod;
dp2[x] += dp2[x]; dp2[x] ++;   dp2[x] %= mod;
dp2[x + 2] += dp2[x + 2];      dp2[x + 2] %= mod;
```  

其余就是正常的递推了  

```cpp
dp1[x] += dp1[x] + dp1[x - 1]; dp1[x] %= mod;
dp2[x] += dp2[x];              dp2[x] %= mod;
dp2[x] += dp1[x - 2];          dp2[x] %= mod;
dp2[x + 2] += dp2[x + 2];      dp2[x + 2] %= mod;
```  

# 计算答案  
每一个数值为下标计的数都是独立的序列  
所以枚举 $0\rightarrow n$ 累加 $dp1[i]+dp2[i]$ 即可  
  
> 当时还有个bug调了半天是初始化问题，我们初始化 $dp1=dp2=0$ 时要带上 $n+1,n+2$ 不然转移递推时会出问题  

# 总程序  

```cpp
# include <bits/stdc++.h>

# define ll long long

using namespace std;

const int N = 5e5 + 10;
const int mod = 998244353;
ll dp1[N], dp2[N];


inline void Solve () {
        int n; cin >> n;
        for ( int i = 0; i <= n + 2; i ++ ) dp1[i] = dp2[i] = 0;
        for ( int i = 0; i < n; i ++ ) {
                int x; cin >> x;
                if ( x == 0 ) {
                        dp1[x] += dp1[x]; dp1[x] ++;   dp1[x] %= mod;

                        dp2[x + 2] += dp2[x + 2];      dp2[x + 2] %= mod;
                } else if ( x == 1 ) {
                        dp1[x] += dp1[x] + dp1[x - 1]; dp1[x] %= mod;
 
                        dp2[x] += dp2[x]; dp2[x] ++;   dp2[x] %= mod;
                        dp2[x + 2] += dp2[x + 2];      dp2[x + 2] %= mod;
                } else {
                        dp1[x] += dp1[x] + dp1[x - 1]; dp1[x] %= mod;

                        dp2[x] += dp2[x];              dp2[x] %= mod;
                        dp2[x] += dp1[x - 2];          dp2[x] %= mod;
                        dp2[x + 2] += dp2[x + 2];      dp2[x + 2] %= mod;
                }
                dp1[x] %= mod; 
                dp2[x] %= mod;
        }
        ll res = 0;
        for ( int i = 0; i <= n; i ++ ) 
                res = (res + dp1[i] + dp2[i]) % mod;
        cout << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        int cass; cin >> cass; while ( cass -- ) {
                Solve ();
        }
}
```

---

## 作者：FXT1110011010OI (赞：0)

## 具体思路

考虑动态规划。

设状态 $f_{i, j, op}$ 表示在前 $i$ 个数里选、$\text{MEX} = j$ 且 $a_{last} = \left \{ \begin{matrix} j - 1 \ \ \ (op = 0) \\ j + 1 \ \ \ (op = 1) \end{matrix} \right.$ 的合法子序列个数（$a_{last}$ 表示子序列的最后一个数字）。

转移分 $3$ 种情况：

### $1.$ 前 $i$ 个数中选，$\text{MEX} = a + 1$ 且最后一个数为 $a$ 的序列

它有三种构造可能：

#### 前 $i - 1$ 个数中选，$\text{MEX} = a + 1$ 的情况：

① 最后一个数为 $a$；

② 最后一个数为 $a$ 的序列末尾加上一个 $a$。

注意这里 ① 和 ② 的区别在于 ② 的末尾比 ① 多了一个 $a$。

#### 前 $i - 1$ 个数中选，$\text{MEX} = a$ 的情况：

③ 最后一个数为 $a - 1$ 的序列末尾加上一个 $a$。

### $2.$ 前 $i$ 个数中选，$\text{MEX} = a + 1$ 且最后一个数为 $a + 2$ 的序列

它有两种构造可能：

#### 前 $i - 1$ 个数中选，$\text{MEX} = a + 1$ 的情况：

① 最后一个数为 $a + 2$；

② 最后一个数为 $a + 2$ 的序列末尾加上一个 $a + 2$。

### $3.$ 前 $i$ 个数中选，$\text{MEX} = a - 1$ 且最后一个数为 $a$ 的序列

它有三种构造可能：

#### 前 $i - 1$ 个数中选，$\text{MEX} = a - 1$ 的情况：

① 最后一个数为 $a$；

② 最后一个数为 $a$ 的序列末尾加上一个 $a$；

③ 最后一个数为 $a - 2$ 的序列末尾加上一个 $a$。

但是这样写空间会爆，考虑优化：我们发现第 $i$ 层都是由第 $i - 1$ 层算出的，可以优化掉第一维。

式子就是把转移套进去，就不写了，不懂看代码吧。

**注意事项** 不要用 `memset`！！！~~我才不会告诉你我调这个调了半个小时。~~

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL N = 5e5 + 10, mod = 998244353;

LL n, a;
LL f[N][2];
LL res;

int main()
{
    int T;
    scanf("%lld", &T);
    while (T -- )
    {
        scanf("%lld", &n);
        for (LL i = 0; i <= n; i ++ ) f[i][0] = f[i][1] = 0;
        f[0][0] = 1;
        for (LL i = 1; i <= n; i ++ )
        {
            scanf("%lld", &a);
            f[a + 1][0] = f[a + 1][0] * 2 % mod;
            f[a + 1][0] = (f[a + 1][0] + f[a][0]) % mod;
            f[a + 1][1] = f[a + 1][1] * 2 % mod;
            if (a)
            {
                f[a - 1][1] = f[a - 1][1] * 2 % mod;
                f[a - 1][1] = (f[a - 1][1] + f[a - 1][0]) % mod;
            }
        }
        res = -1;
        for (LL i = 0; i <= n; i ++ ) res = (res + f[i][0] + f[i][1]) % mod;
        printf("%lld\n", res);
    }
    return 0;
}
```

---

## 作者：thostever (赞：0)

转化一下题意：要选择一个子序列，就相当于从前往后挨个的“挑数”，对于每个数考虑是否丢进子序列里。那么我们就需要保证挑进去的数始终使子序列合法。

对于已经有了的一个序列 $a_1,a_2,...,a_{i-1}$ ，它的 $\operatorname{MEX}$ 值为 $k$ 。我们要添加一个 $a_i$ 进去。考虑几种情况：

若 $a_i\neq k$ ，则把 $a_i$ 加进去后 $\operatorname{MEX}$ 值不会变，仍为 $k$ 。所以需要 $a_i=k\pm 1$ 。

若 $a_i=k$ ，则加入 $a_i$ 后， $\operatorname{MEX}$ 值一定会变大。又因为要保证 $|a_i-\operatorname{MEX}|\leq 1$ ，所以 $\operatorname{MEX}$ 值只能变为 $k+1$ ，而这样的前提是 $a_1$ 到 $a_{i-1}$ 中不包含 $k+1$ 。

综上所述，我们可以得到几个结论：

1.加入的 $a_i$ 只能为 $k-1/k/k+1$ ，且加入的 $a_i$ 为 $k$ 的前提是当前序列中没有 $k+1$ 。

2.对于一个序列 $a_1,a_2,...,a_i$ 来说，它的 $\operatorname{MEX}=a_i\pm 1$ 。

那么我们就可以开始设计 dp 状态了：

 $dp_{i,0}$ 表示前 $i$ 位，第 $i$ 位在子序列中且加入 $a_i$ 时 $a_i=\operatorname{MEX}-1$ 且序列中不包含 $\operatorname{MEX}+1$ 这个值。

 $dp_{i,1}$ 表示前 $i$ 位，第 $i$ 位在子序列中且加入 $a_i$ 时 $a_i=\operatorname{MEX}-1$ 且序列中包含 $\operatorname{MEX}+1$ 这个值。

 $dp_{i,2}$ 表示前 $i$ 位，第 $i$ 位在子序列中且加入 $a_i$ 时 $a_i=\operatorname{MEX}+1$ 。
 
 
 $dp_{i,3}$ 表示前 $i$ 位，第 $i$ 位在子序列中且加入 $a_i$ 时 $a_i=\operatorname{MEX}$ （序列中肯定不包含 $\operatorname{MEX}+1$ ）

枚举上一位的位置 $j$ ，考虑一下转移。下面是示意图：（箭头表示由什么得来的）

 $dp_{i,0}\to dp_{j,0}+dp_{j,3}$

 $dp_{i,1}\to dp_{j,1}+dp_{j,2}$

 $dp_{i,2}\to dp_{j,0}+dp_{j,1}+dp_{j,2}+dp_{j,3}$

 $dp_{i,3}\to dp_{j,0}+dp_{j,3}$

在转移的时候需要考虑 $a_i$ 和 $a_j$ 的关系。我们可以根据 $a_i$ 推出对应 dp 状态下的 $\operatorname{MEX}$ 值，确认两者关系。

 dp 初值赋为 $0$ ，边界 $dp_{0,0}=1$ 。答案是 $\sum_{i=1}^{n}dp_{i,0}+dp_{i,1}+dp_{i,2}+dp_{i,3}$ 。

这样我们就可以写出 $O(n^2)$ 的代码了！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n;
int a[500010];
int dp[500010][4];
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		a[0]=-1;
		for(int i=0;i<=n;i++) dp[i][0]=dp[i][1]=dp[i][2]=dp[i][3]=0; 
		dp[0][0]=1;
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<i;j++)
			{
				if(a[i]==a[j]) dp[i][0]+=dp[j][0];
				if(a[i]==a[j]) dp[i][0]+=dp[j][3];
				
				if(a[i]==a[j]) dp[i][1]+=dp[j][1];
				if(a[i]==a[j]-2) dp[i][1]+=dp[j][2];
				
				if(a[i]==a[j]+2) dp[i][2]+=dp[j][0];
				if(a[i]==a[j]+2) dp[i][2]+=dp[j][1];
				if(a[i]==a[j]) dp[i][2]+=dp[j][2];
				if(a[i]==a[j]+2) dp[i][2]+=dp[j][3];
				
				if(a[i]==a[j]+1) dp[i][3]+=dp[j][0];
				if(a[i]==a[j]+1) dp[i][3]+=dp[j][3];
			}
			dp[i][0]%=mod; dp[i][1]%=mod; dp[i][2]%=mod; dp[i][3]%=mod;
			ans+=dp[i][0]+dp[i][1]+dp[i][2]+dp[i][3]; ans%=mod;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

考虑一下优化：我们发现所有的 $a_i$ 值都是在 $0$ 到 $n$ 之间的，而每次 dp 转移枚举 $j$ 的时候，都是加上所以 $a_j$ 等于固定值的 dp 项。

那么我们就用一个桶 $s_{i,k}$ 记录所有 $a_j=i$ 的 $dp_{j,k}$ 的和。转移时直接加上即可。

由于存在负数，所以桶可以加上一个常数 $k$ 。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int k=10;
int n;
int a[500010];
int dp[500010][4];
int s[500020][4];
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=0;i<=n;i++) dp[i][0]=dp[i][1]=dp[i][2]=dp[i][3]=0;
		for(int i=0;i<=n+k+k;i++) s[i][0]=s[i][1]=s[i][2]=s[i][3]=0;
		s[-1+k][0]=1;
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			dp[i][0]+=s[a[i]+k][0]+s[a[i]+k][3]; dp[i][0]%=mod;
			dp[i][1]+=s[a[i]+k][1]+s[a[i]+2+k][2]; dp[i][1]%=mod;
			dp[i][2]+=s[a[i]-2+k][0]+s[a[i]-2+k][1]+s[a[i]+k][2]+s[a[i]-2+k][3]; dp[i][2]%=mod;
			dp[i][3]+=s[a[i]-1+k][0]+s[a[i]-1+k][3]; dp[i][3]%=mod;
			s[a[i]+k][0]+=dp[i][0]; s[a[i]+k][0]%=mod;
			s[a[i]+k][1]+=dp[i][1]; s[a[i]+k][1]%=mod;
			s[a[i]+k][2]+=dp[i][2]; s[a[i]+k][2]%=mod;
			s[a[i]+k][3]+=dp[i][3]; s[a[i]+k][3]%=mod;
			ans+=dp[i][0]+dp[i][1]+dp[i][2]+dp[i][3]; ans%=mod;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：Otomune_Kozue (赞：0)

### 题目大意
对于一个非负整数序列 $a_1...a_n$ ，如果对于序列中任意一个数 $a_k$ ，有 $|MEX\{a_1,a_2,...,a_k\}-a_k|\leq1$ ，那么我们称这个序列合法。其中 $MEX\{a_1,a_2,...,a_k\}$ 的定义为不在 $a_1$ 到 $a_k$ 这个集合中的最小非负整数。给定序列 $a$ ，求合法的子序列个数对 $998244353$ 取模的值。


------------
### 思路
我们可以注意到，显然序列只能从 $0$ 或 $1$ 开始，如果序列从 $1$ 开始，则序列的后续只能全部是 $1$ （显然是 $0$ 或是 $2$ 都不行，这里不做过多讨论）我们把这部分情况单独计算，它对答案的贡献为：对于每一个 $a[i]=1$ ， $ans=ans*2+1$ （ $ans$ 此时初值为 $0$ ）

因为 $a$ 序列的值域为 $[0,n]$ ，我们可以设计出 $dp$ 状态：

$dp[a[i]][0/1]$ 表示选到 $a[i]$ 这个数，情况为第 $0/1$ 种

来看序列从 $0$ 开始的部分，我们能够看出两种满足题意的情况：

1.单调递增且相邻两数差为 $1$ ： $dp[a[i]][0]=dp[a[i]][0]*2+dp[a[i]-1][0]$

2.遇到差为 $2$ 的数，我们可以在这两个数之间反复横跳，此时能够根据结束的地方在反复横跳过程的上方还是下方写出两个 $dp$ 方程： $dp[a[i]][1]=dp[a[i]][1]*2+dp[a[i]-2][0]$ ， $dp[a[i]+2][1]=dp[a[i]+2][1]*2$

答案显然为 $\sum_{i=0}^n(dp[i][0]+dp[i][1])+$ 序列从1开始的情况数。

于是我们可以 $AC$ 掉这道题。


------------
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int NR=5e5+5;
const int mod=998244353;
int n;
int a[NR];
int dp[NR],f[NR],res,k;
void solve(){
	cin >> n;
	for(int i=0;i<n;i++) cin >> a[i];
	for(int i=0;i<=n;i++){
		dp[i][0]=dp[i][1]=0;
	}
	res=0;
	for(int i=0;i<n;i++){
		int now=a[i];
		if(now==0) dp[now][0]=(dp[now][0]+dp[now][0]+1)%mod;
		else dp[now][0]=(dp[now][0]+dp[now][0]+dp[now-1][0])%mod;
		if(now>=2) dp[now][1]=(dp[now][1]+dp[now][1]+dp[now-2][0])%mod;
		if(now<=n-2) dp[now+2][1]=(dp[now+2][1]+dp[now+2][1])%mod; 
	}
	for(int i=0;i<n;i++){
		if(a[i]==1) res=(res+res+1)%mod;
	}
	for(int i=0;i<=n;i++) res=(res+dp[i]+f[i])%mod;
	cout << res << endl;
}
signed main(){
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```


---

## 作者：Tyyyyyy (赞：0)

## CF1613D
[原题链接](https://codeforces.com/contest/1613/problem/D)
### 题意简述
- 定义函数 $\operatorname{MEX}(S)$ 表示可重集 $S$ 中**最小的未出现的非负整数**。
- 定义一个序列 $S=\{x_1,x_2,\dots,x_k\}$ 是 `MEX-correct` 的，当且仅当对于所有的 $1 \leq i \leq k$，都有 $|x_i-\operatorname{MEX}(x_1,\dots,x_i)|\leq 1$。
- 求给定长度为 $N$ 的序列 $a_1,\dots,a_N$ 有多少个子序列是 `MEX-correct` 的。
- $1 \leq N \leq 5 \times 10^5,0 \leq a_i \leq N$，答案对 $998244353$ 取模。
- 本题有 $t$ 组数据，$1 \leq t \leq 10^5,\sum N \leq 5 \times 10^5$。

### 分析
考虑计数 dp。定义 $dp_{i,0/1/2}$ 表示考虑到第 $i$ 个数，子序列的 $\operatorname{MEX}$ 值分别为 $a_i-1,a_i+1,a_i+1$ 的情况。$dp_{i,1},dp_{i,2}$ 的区别在于，我们规定$dp_{i,1}$ 包含的子序列中没有 $a_i+2$ 这个元素，而 $dp_{i,2}$ 包含的子序列中有 $a_i+2$ 这个元素。

为什么要这样规定呢？试着考虑没有 $dp_{i,2}$ 的情况，即 $dp_{i,0/1}$ 只以当前子序列的 $\operatorname{MEX}$ 值进行区分。

发现此时转移会有问题：当我们用满足 $a_j=a_i-1$ 的 $dp_{j,1}$ 转移 $dp_{i,1}$ 时，我们不知道之前的子序列中是否有 $a_i+1$ 这个元素，从而出错。

因此我们需要划分是否包含 $a_i+2$ 的情况。

接下来考虑转移，可以得到转移方程：

$$dp_{i,0}=\sum_{a_x=a_i} dp_{x,0}+\sum_{a_y=a_i-2} dp_{y,1}+\sum_{a_z=a_i-2}dp_{z,2}$$

$$dp_{i,1}=\sum_{a_x=a_i-1} dp_{x,1}+\sum_{a_y=a_i} dp_{y,1}$$

$$dp_{i,2}=\sum_{a_x=a_i+2} dp_{x,0}+\sum_{a_y=a_i} dp_{y,2}$$

读者可以自行写出 $dp_{i,0/1/2}$ 对应的条件并依次对照。

发现我们需要记录对应的 $a_i$ 值的 $dp$ 值之和，所以开一个辅助数组 $v$ 记录即可。

初始化：$dp_{i,1}=1(a_i=0),dp_{i,0}=1(a_i=1)$。

答案把所有的 $dp_{i,0/1/2}$ 相加即可。

Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int t,n,a[500010];
int dp[500010][3];//到第i个数，mex为a[i]-1/a[i]+1的情况，a[i]+1的情况分当前集合有无a[i]+2讨论 
int v[500010][3];//当前v[i][k]=当前dp[j][k]的和，a[j]=i。 
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=0;i<=n+2;i++)
			dp[i][0]=dp[i][1]=dp[i][2]=v[i][0]=v[i][1]=v[i][2]=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]==0)dp[i][1]=1;
			if(a[i]==1)dp[i][0]=1;
			dp[i][0]=(dp[i][0]+v[a[i]][0]+(a[i]>=2?v[a[i]-2][1]+v[a[i]-2][2]:0))%mod;
			dp[i][1]=(dp[i][1]+(a[i]>=1?v[a[i]-1][1]:0)+v[a[i]][1])%mod;
			dp[i][2]=(dp[i][2]+v[a[i]+2][0]+v[a[i]][2])%mod;
			v[a[i]][0]=(v[a[i]][0]+dp[i][0])%mod;
			v[a[i]][1]=(v[a[i]][1]+dp[i][1])%mod; 
			v[a[i]][2]=(v[a[i]][2]+dp[i][2])%mod;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			ans=(ans+dp[i][0]+dp[i][1]+dp[i][2])%mod;
		printf("%lld\n",ans);
	} 
	return 0;
}
```

---

