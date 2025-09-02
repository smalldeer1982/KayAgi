# Jzzhu and Numbers

## 题目描述

Jzzhu have $ n $ non-negative integers $ a_{1},a_{2},...,a_{n} $ . We will call a sequence of indexes $ i_{1},i_{2},...,i_{k} $ $ (1<=i_{1}<i_{2}<...<i_{k}<=n) $ a group of size $ k $ .

Jzzhu wonders, how many groups exists such that $ a_{i1} $ & $ a_{i2} $ & ... & $ a_{ik}=0 $ $ (1<=k<=n) $ ? Help him and print this number modulo $ 1000000007 $ $ (10^{9}+7) $ . Operation $ x $ & $ y $ denotes bitwise AND operation of two numbers.

## 样例 #1

### 输入

```
3
2 3 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4
0 1 2 3
```

### 输出

```
10
```

## 样例 #3

### 输入

```
6
5 2 0 5 2 1
```

### 输出

```
53
```

# 题解

## 作者：Tgotp (赞：41)

来说个简单的：

若设$f_s$表示与和为$f_s$的方案数

发现并不好处理，令$f_s$表示子集含ｓ的方案数，

那么实际上$f_s$就是所有含ｓ的集合的高维前缀和

倒着处理一遍所有含ｓ的ａ的个数，那么显然是$f_s=2^{num_s} -1$

然后差分回去就完了

ｃ＋＋代码如下：

```
#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
const int N = 2e6 + 50,mod = 1e9 + 7;
ll f[N];
int n,s;
inline int ksm(int x,int y)
{
	int ans = 1;
	while(y)
	{
		if(y&1) ans = 1ll * ans * x % mod;
		y >>= 1;x = 1ll * x * x % mod;
	}
	return ans;
}

inline void doit(int F)
{
	rep(i,0,19)
		repd(j,s,0)
			if((j&(1<<i))==0)
				f[j] = (f[j] + f[j|(1<<i)] * F %mod + mod)%mod;
}

int main()
{
	scanf("%d",&n);	
	rep(i,1,n) { int x;scanf("%d",&x); ++ f[x]; }
	s = (1 << 20) - 1;
	doit(1);
	rep(i,0,s) f[i] = ksm(2,f[i]) - 1;
	doit(-1);
	cout << f[0] << endl;
	return 0;
}
```

---

## 作者：leozhang (赞：38)

状压妙啊...

本题的主体思路：状压+容斥原理（或状压+数位dp）

记g[i]表示按位与后结果所有位上至少有i个1的方案数

那么根据容斥原理，ans=g[0]-g[1]+g[2]-g[3]+g[4]...

于是如果我们求出了g，就可以求出ans

可是怎么求出g呢

我们记f[i]表示a&i==i这样的a的个数，那么如果i某一位上为1，则a这一位上也为1

于是我们可以枚举所有可能的结果（0-10^6），然后观察这个结果是否是某一个可能结果的子集，如果是的话就累计个数

详细说一下，就是我首先读入所有数据，每读入一个数据x记录f[x]++作为初始值，然后不断更新

在更新的时候，我们首先枚举每一位j，然后枚举1~10^6的所有值i，如果某个值这一位上是1，则更新：

dp[i^(1<<j)]+=dp[i];

就是去掉j位的个数加上i

什么?怎么证明这样统计是不重不漏的？

首先，我们是按位枚举的，一开始只有初始读入的部分有值，剩下的没有值。那么，当我们枚举第一位时，我们只会更新由初值去掉第一位所能获得的所有值

以此类推，当我们更新第二位时，我们只会更新初值去掉前两位和初值只去掉第二位能获得的所有值

也就是说，我们在更新每一位时，都不会产生重复的状态，都是原来的状态+这一位，所以是不重的，而由于这样的枚举能够遍历所有数位的组合，所以也是不漏的

好，我们处理出了f，接下来？

我们可以枚举所有结果，统计他有几位上是1，那么如果有1位上是1，就会对g[1]产生贡献，等等，以此类推

然后我们再考虑，产生多少贡献？

我们会发现，如果这个结果对应的数有k个，那么答案应为2^k-1（即每个数都有选或不选两种状态，但不能全不选）

所以他产生的贡献就是2^k-1

什么？这种方法的正确性何在？

首先，根据容斥原理，答案的正确性是很显然的

那么我们只需证明g求解的正确性即可

首先回顾一下g的定义：“至少”包含i个1的取法的方案数

也就是说，我所找出的东西数位中1的个数只需>=i即可

那这个是很显然能够保证的

于是为什么不重呢？

由于每个结果互不相同，而我们最后事实上是按结果取的，所以每一种取法都是互不相同的，保证了正确性。

最后代码：

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
#define mode 1000000007
#define maxx 1000000
ll v[1000005];
ll dp[1000005];
ll f[25];
int n;
int main()
{
	v[0]=1;
	scanf("%d",&n);
	for(int i=1;i<=maxx;i++)
	{
		v[i]=(v[i-1]<<1)%mode;
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		dp[x]++;
	}
	for(int j=0;j<=20;j++)
	{
		for(int i=1;i<=maxx;i++)
		{
			if(((1<<j)&i))
			{
				dp[i^(1<<j)]+=dp[i];
			}
		}
	}
	ll ans=0;
	for(int i=0;i<=maxx;i++)
	{
		int cnt=0;
		for(int j=0;j<=20;j++)
		{
			if((1<<j)&i)
			{
				cnt++;
			}
		}
		f[cnt]+=((v[dp[i]]-1)%mode+mode)%mode;
	}
	for(int i=0;i<=20;i++)
	{
		if(i%2)
		{
			ans-=f[i];
			ans%=mode;
		}else
		{
			ans+=f[i];
			ans%=mode;
		}
	}
	printf("%I64d\n",(ans%mode+mode)%mode);
	return 0;
}
```

---

## 作者：asuldb (赞：19)

[题目](https://www.luogu.org/problemnew/show/CF449D)

提供一个非容斥做法——$FWT$

我们发现我们要求的东西就是一个背包，只不过是在$and$意义下的

自然有

$$dp_{i,j}=\sum_{k\&a_i=j}dp_{i-1,k}+dp_{i-1,j}$$

我们发现这个柿子本质上就是一个和卷积

于是两边取$fwt$，我们就可以得到一个暴力$fwt$的代码

```cpp
for(re int i=1;i<=n;i++) {
    	memset(A,0,sizeof(A));
    	A[a[i]]=1;Fwtand(A,1);
    	for(re int j=0;j<len;j++) S[j]=S[j]+S[j]*A[j];
}
Fwtand(S,-1);
```
我们发现其实$fwt$的正向变换求得是超集和，又因为我们这里只有一个$A[a[i]]=1$，所以所有$A_j$最多就是$1$，$A_j=1$的时候会使得$S_j$翻倍，所以整体下来我们只需要关心$S_j$翻了多少倍

显然有多个$a_i$是$j$的超集就能翻多少倍，于是我们对$A$整体来一个$fwt$就好了

但是非常蛇皮的一点就是当$a$全是$0$的时候会把空集算入答案，因此需要特判一下

代码


```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
const int maxn=2500005;
const int mod=1e9+7;
inline int read() {
    char c=getchar();int x=0;while(c<'0'||x>'9') c=getchar();
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
int len,n,M;
LL S[maxn],A[maxn],a[maxn],pw[maxn];
inline void Fwt(LL *f,int o,int mod) {
    for(re int i=2;i<=len;i<<=1)
        for(re int ln=i>>1,l=0;l<len;l+=i)
            for(re int x=l;x<l+ln;++x)
                f[x]+=o*f[ln+x],f[x]=(f[x]+mod)%mod;
}
int main() {
    n=read();
    for(re int i=1;i<=n;i++) a[i]=read(),M=max(M,a[i]);
    len=1;while(len<=M) len<<=1;
    pw[0]=1;
    for(re int i=1;i<=n;i++) pw[i]=(pw[i-1]+pw[i-1])%mod;
    for(re int i=1;i<=n;i++) A[a[i]]++;
    Fwt(A,1,mod-1);
    for(re int i=0;i<len;i++) A[i]=pw[A[i]];
    Fwt(A,-1,mod);
    if(A[0]==pw[n]) std::cout<<A[0]-1;
    else std::cout<<A[0];
    return 0;
}
```


---

## 作者：caidzh (赞：14)

非常高明的数数题

首先我们知道多个相同的数通过与运算得到的结果还是这个数，所以我们对一个数出现的个数进行统计

如果我们需要一个数，当然可以通过在等于这个数的数中选择若干个，显而易见的，我们可以有$2^p-1$（去掉空集）种选择方案$(1)$

正好等于一个数的方案确实不好求。不显然地，我们考虑做一个类似后缀和的东西，然后再容斥

我们不妨用$f_i$表示$i$的超集中有几个数，我们再定义$g_i$为结果为$i$的超集的选择方案有多少个，然后我们来考虑这两个东西到底怎么求

$f$的求法是一个非常经典的状压$dp$，当然你叫它高维前缀和其实也没有毛病
```cpp
for(int i=1;i<=n;i++)a[i]=read(),f[a[i]]++;
for(int i=0;i<20;i++)
	for(int j=(1<<20)-1;j>=0;j--)
		if(!(j&(1<<i)))f[j]=f[j]+f[j|(1<<i)];
```

接下来的问题是怎么求出$g$，利用上面所述的$(1)$，我们可以发现，结果为：$g_i=2^{f_i}-1$

最后我们考虑怎么算答案，显然这是一个利用容斥原理的过程，最终答案：

$$ans=\sum_{i=0}^n(-1)^{\text{i中1的个数}}g_i$$
```cpp
#include<bits/stdc++.h>
#define int LL
#define LL long long
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=1e6+10,mod=1e9+7;
int n,a[maxn],f[1<<20],g[1<<20],sum[1<<20];
int Pow(int x,int y){
	int ans=1;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;
}
int Get(int x){
	int num=0;while(x){if(x&1)num++;x>>=1;}return num;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),f[a[i]]++;
	for(int i=0;i<20;i++)
		for(int j=(1<<20)-1;j>=0;j--)
			if(!(j&(1<<i)))f[j]=f[j]+f[j|(1<<i)];
	for(int i=0;i<(1<<20);i++)g[i]=((Pow(2,f[i])-1)%mod+mod)%mod;
	for(int i=0;i<(1<<20);i++)sum[i]=(Get(i)&1)?-1:1;int ans=0;
	for(int i=0;i<(1<<20);i++)ans=(ans+(sum[i]*g[i]%mod+mod)%mod)%mod;
	cout<<ans<<endl;return 0;
}
```


---

## 作者：1saunoya (赞：12)

考虑高维前缀和？（好像有人叫这个 SOSdp？）

类似状压的过程。

我们可以求出来 $f_i = \sum_{i \& j == i} a_j$ 

这种就是高维前缀和了。当然可以扩展到 $\max$ 和 $\min$。

我们先开个桶计数，令这个桶为 $a_i$，表示 $i$ 出现了几次（

然后就是高维前缀和的操作了。

$f_i = \sum_{i \& j == i} a_j$

通过枚举位，然后加进去贡献。

```cpp
for (int i = 0; i < 20; i++) {
  for (int j = 1048575; ~j; --j) {
    if (!(j & (1 << i))) { f[j] = add(f[j], f[j ^ (1 << i)]); }
  }
}
```
然后我们处理出的 $f_i$ 的意义就是 $j \& i == i$ 的个数。

令 $g_i = 2^{f_i}-1$ 也就是 $\texttt{and}$ 和为 $j$，且 $j \& i == i$ 的方案数。

我们设 $h_i$ 为 $\texttt{and}$ 和为 $i$ 的方案数。

那么 $g_i = \sum_{i\&j==i} h_j$ （显然）

于是我们把前缀和变成差分就好了。

---

## 作者：Nemlit (赞：8)

给一个无脑做法：

考虑答案为所有$(x^{U}+x^{a_i})$的$and$卷积之积（$U$为全集）。如果直接暴力乘或者分治乘复杂度为$O(NMlogM)$或者$O(NlogNMlogM)$

众所周知，$and$卷积的矩阵只有$(1,0)$处是$0$，其余地方都是$1$，根据$FWT$定义式，$FWT(i)=\sum c(i, j)f_j$，由于要求的卷积只有两项所以只有在$f_U,f_{a_i}$处为$1$。不难发现，$FWT(i)$的值只有$1, 2$两种。所以我们如果将所有$(x^{U}+x^{a_i})$的点值相乘，那么一定会得到$1^x\times 2^{n-x}$的权值

考虑$FWT$是一个线性变换，满足$\sum(FWT(F(i)))=FWT(\sum F(i))$，于是我们容易计算出$\sum FWT(F(i))$，那么实际上我们可以得到$F'(i)=1\times x + 2\times (n - x)$，只需要解一个方程即可得到$x$。于是可以得到$\prod FWT(i)$，在用一次$IFWT$还原即可。
```cpp
/* This code is written by Nemlit */
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define rep(i, a, b) for(re int i = (a); i <= (b); ++ i)
#define int long long
#define mod 1000000007
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define maxn (1 << 22) + 5
int n, a[maxn], f[maxn], lim = 1, m = 1;
il int qpow(int a, int b) { int r = 1; while(b) { if(b & 1) r = r * a % mod; a = a * a % mod, b >>= 1; } return r; }
il void FWT(int *f, int opt) {
	for(re int mid = 1; mid < lim; mid <<= 1) {
		for(re int j = 0; j < lim; j += mid << 1) {
			for(re int k = j; k < j + mid; ++ k) {
				if(opt == 0) f[k] = (f[k] + f[k + mid]) % mod;
				else f[k] = (f[k] - f[k + mid] + mod) % mod;
			}
		}
	}
}
signed main() {
	n = read();
	rep(i, 1, n) a[i] = read(), m = max(m, a[i]), ++ f[a[i]];
	while(lim <= m * 2) lim <<= 1;
	f[lim - 1] += n, FWT(f, 0);
	rep(i, 0, lim - 1) {
		int x = (2 * n - f[i] + mod) % mod;
		f[i] = qpow(2, n - x);
	}
	FWT(f, 1), printf("%lld", f[0]);
	return 0;
}
```

---

## 作者：chenxia25 (赞：7)

~~容斥 + 高维前缀和一般题（ymx 附体）~~

选的一个集合满足条件，显然当且仅当每一位都有人是 $0$。于是我们考虑每个数能够满足哪些位（就是取反）。

考虑反面考虑，求至少有一位没有被满足的方案数。这样就可以很舒服的容斥了。于是现在只要求对于任意 bitmask $x$，$x$ 内的位不被满足，其他位随便的方案数。这显然就是只有 $x$ 的补 bitmask 的子集才能选，而且任意一种选的方案都是可以的，那么设 $x$ 的补 bitmask 的子集中有 $cnt$ 个给定的，那么它对答案的贡献就是 $2^{cnt}$ 乘以容斥系数。

那么问题就成了求对于所有 bitmask，求出他的被给定的子集数。那这不就是个高维前缀和板子嘛？

**_[code](https://www.luogu.com.cn/paste/yivelxt2)_**

---

## 作者：YLWang (赞：6)

高明的数数题。

考虑打一个暴力。

```
For(i, 1, n) For(j, 1, (1 << 20) - 1)
	f[j & a[i]] += f[j];

```

暴力是个背包，正确性显然故从略。

容易发现这是个 and 卷积的形式。

于是考虑 fwt。

暴力 fwt 就是考虑把每个 $a_i$ 单点的变化值 $fwt(a_i)$ 求出来暴力乘一遍最后 fwt 回去。发现屁用没有。

但是这玩意性质非常优秀。我们发现这个东西每一位要么是 $1$ 要么是 $0$，在当前位是 $1$ 的时候对应位的 $f$ 值会翻倍，否则不会翻倍。那么把每一个 $fwt(a_i)$ 对应位加起来然后 2 的幂次方一下就可以了。

考虑到 and 卷积 fwt 的本质是高维后缀和，所以可以把一堆东西拼起来做一遍 fwt，等价于做一堆 fwt 之后加起来。复杂度 $O(n \log n)$。

比较令人头秃的一件事是边界问题。

我们考虑每次会多算一个空集。所以减一个 1。十分合理。

代码极其好写。不贴了。

关于这个题 CF 只有 2400 这档事，可能是因为他的想法可能性比较单一吧。你列出这个式子不 fwt 应该没什么办法了。

---

## 作者：Martian148 (赞：6)

# link
[CF449D Jzzhu and Numbers](https://www.luogu.com.cn/problem/CF449D)
# solve
我们发现直接去统计方案数不大现实，我们就考虑用容斥的做法，用全部的方案数-不为 $0$ 的方案数，我们就可以定义 $F[i]$ 表示 $a[i]\&i==i$ 的个数，我们先按位枚举,然后从1-1e6枚举j如果j在这一位上有数，我们就可以把这一位上的数去掉作为上一状态转移过来，即 $dp[j^(1<<i-1)]+=dp[j]$ 为什么要讲小的状态加上大的状态，因为防止刷重

怎样来确定正确性，我们先刷了去掉第一位的，然后枚举到第二位时刷去掉前两位的和去掉第二位的，枚举到第n位时刷了前面的组合和去掉第n位的，所以我们把所有状态都刷到了，因此答案是正确的。

考虑答案，我们发现，有些答案被统计了两次，比如F[101]在F[100]的时候统计了一次，在F[001]的时候也被统计了一次，所以在我们要把F[101]减去一次，就是容斥的原理，所以二进制下1的个数为奇数就加上，为偶数就减去，最后注意模数就好了。

# code
代码的数组名称和题解不同

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define mod 1000000007
#define N 3000000
using namespace std;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int n,x,dp[N],g[N];
long long f[N];
long long ans=0;
int main()
{
	scanf("%d",&n);
	int mx=(1<<20)-1;
	for(int i=1;i<=n;i++)dp[read()]++;
	f[0]=1;
	for(int i=1;i<=n;i++) f[i]=(f[i-1]<<1)%mod;
	for(int i=1;i<=20;i++)
	for(int j=0;j<=mx;j++)
	if(j&(1<<i-1)){
		dp[j^(1<<i-1)]+=dp[j];
	}
	ans=f[n]-1;
	for(int i=1;i <= mx;i++)
	{
		g[i]=g[i>>1]+(1&i);
		if(g[i]&1) ans=(ans-(f[dp[i]]-1)+mod)%mod;
		else ans=(ans+(f[dp[i]]-1)+mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：do_while_true (赞：4)

实际上就是个位运算卷积的背包，只需要每个 $F_i=x^{a_i}+x^{U}$ 位运算卷积卷起来即可（$U$ 是全集），如果直接暴力把每个 $F$ 都卷起来是 GG 的，注意到这个做 FMT 也就是后缀和，所有位置不是 $1$ 就是 $2$，或者说只有 $a_i$ 的前缀是 $2$，其他都是 $1$。

所以 $\prod FMT(F_i)$ 的每个位置都是一个 $2$ 的次幂，而指数就是有多少个 $a_i$ 的前缀包含它。

那么对 $a$ 开个桶做一个高维后缀和，每个位置就是 $\prod FMT(F_i)$ 每个位置的指数，求出 $\prod FMT(F_i)$ 再 $IFMT$ 回去。	

[code](https://codeforces.com/contest/449/submission/127484123)

---

## 作者：Soulist (赞：4)

首先题意的那个依次$\le$的限制是为了告诉你一个方案只能被判定一次。

然后我们首先会想到一个特别naive的做法，令$f_i$表示最后序列的$\&$值为 $i$ 的方案数。

然后你会发现$f_i$的转移过程中只会变小而不会增大，但是由于状态本身之间的重叠所以它并不可做。

在常见的操作中，由于状态计数时出现了重叠，我们常常采取两种措施(可能还有，但wtcl不知道= =)：

$1.$增加维度来进行限制。

$2.$利用容斥原理。

本题中使用方法$1$反正我是搞不来，所以我们会采取第$2$种思路

不妨令$f_i$表示最后序列的$\&$值至少是$i$，即包括了 $i$ 中的所有 $1$，而$g_i$则表示恰好。

那么很明显的有：

$$g_i=f_i-\sum_{k\&i=i}g_k$$

注意到最后的答案只关乎$g_0$

所以我们应该有：

$$g_0=f_0-\sum_{i=1}^{2^n-1}g_i$$

继续展开后有：

$$g_0=\sum_{i=0}^{2^n-1}f_i\times (-1)^{|i|}$$

于是问题仅关乎求$f_i$

不难注意到，$f_i$应该为：$2^s-1$，其中$s$为有多少个数$x$，满足$x\& i=i$

注意到这个形式一脸$\rm FWT$的样子，具体写为：

$$f_i=\sum_{k\& i=i}count(k)-1~,~count(k)\text{为$k$的出现次数}$$

于是上个$\rm FWT$即可...

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 1e9 + 7 ;
const int N = 2e6 + 5 ; 
int f[N], n, c[N], d[N], limit = 1, m, Ans ; 
int lowbit( int x ) {
	return x & ( -x ) ;
}
int fpow( int x, int k ) {
	int ans = 1, base = x ; 
	while( k ) {
		if( k & 1 ) ans = ans * base % P ; 
		base = base * base % P, k >>= 1 ; 
	} return ans ; 
}
void FWT( int *a, int type ) { //and
	for( re int k = 1; k < limit; k <<= 1 )
	for( re int i = 0; i < limit; i += ( k << 1 ) )
	for( re int j = i; j < i + k; ++ j )
		a[j] += a[j + k] ;
}
signed main()
{
	n = gi() ; int x ; 
	rep( i, 1, n ) x = gi(), ++ c[x], m = max( m, x ) ; 
	while( limit <= m ) limit <<= 1 ; 
	FWT( c, 1 ), d[0] = 1 ; 
	for( re int i = 0; i < limit; ++ i ) {
		if( !d[i] ) d[i] = - d[i ^ lowbit(i)] ; 
		Ans = ( Ans + d[i] * ( fpow( 2, c[i] ) - 1 ) % P + P ) % P ; 
	}
	printf("%I64d\n", Ans ) ;
	return 0 ;
}
```

---

