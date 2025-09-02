# Cards

## 题目描述

Consider the following experiment. You have a deck of $ m $ cards, and exactly one card is a joker. $ n $ times, you do the following: shuffle the deck, take the top card of the deck, look at it and return it into the deck.

Let $ x $ be the number of times you have taken the joker out of the deck during this experiment. Assuming that every time you shuffle the deck, all $ m! $ possible permutations of cards are equiprobable, what is the expected value of $ x^k $ ? Print the answer modulo $ 998244353 $ .

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 1 5000
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2 2 2
```

### 输出

```
499122178
```

## 样例 #4

### 输入

```
998244352 1337 5000
```

### 输出

```
326459680
```

# 题解

## 作者：NaCly_Fish (赞：28)

在我的博客内看体验更佳（

updated：改为 $\Theta(k)$ 的解法。  
ps：这个复杂度的做法 [iostream](https://www.luogu.com.cn/user/13052) 比我先做出来。

设 $p=1/m$，$q=1-p$，那么枚举第一张为王牌的次数，有这么一个暴力计算的式子

$$\sum_{i=0}^n\binom{n}{i}p^iq^{n-i}i^k$$
后面那个 $i^k$ 可以展开为第二类 Stirling 数
$$\sum_{i=0}^n\binom{n}{i}p^iq^{n-i}\sum_{j=1}^k \begin{Bmatrix} k \\ j \end{Bmatrix}i^{\underline j}$$
$$=\sum_{j=1}^k\begin{Bmatrix} k \\ j \end{Bmatrix}\sum_{i=0}^n\binom{n}{i}p^iq^{n-i}i^{\underline j}$$

考虑化简后面那个式子

$$=\sum_{i=j}^n \binom ni p^i(1-p)^{n-i}\binom{i}{j}j!$$
$$=j!\binom{n}{j}\sum_{i=j}^n\binom{n-j}{i-j}p^i(1-p)^{n-i}$$
$$=n^{\underline j} \sum_{i=0}^{n-j}\binom{n-j}{i}p^{i+j}(1-p)^{n-j-i}$$
$$=n^{\underline j}p^j$$

然后直接得到原式为
$$\sum_{j=0}^k\begin{Bmatrix} k \\ j \end{Bmatrix}n^{\underline j}p^j$$
这样就可以 $\Theta(k \log k)$ 计算了，然而还可以更优。   
暴力拆开原式的 Stirling 数得到
$$ \sum_{j=0}^k\frac{1}{j!}\sum_{i=0}^j(-1)^{j-i}\binom{j}{i} i^k j! \binom nj p^j$$
$$=\sum_{i=0}^ki^k\sum_{j=i}^k(-1)^{j-i} \binom nj \binom ji p^j$$
根据组合数的基本意义可以化为
$$\sum_{i=0}^ki^k\binom ni\sum_{j=i}^k(-1)^{j-i}\binom{n-i}{j-i}p^j$$
后面一个和式改为枚举从 $0$ 到 $k-i$，所有含 $j$ 的式子都 $+i$ 得到
$$\sum_{i=0}^ki^k\binom ni p^i\sum_{j=0}^{k-i}(-1)^j\binom{n-i}{j}p^j$$
设后面那个和式为 $f(i)$，显然有 $f(k)=1$。  
做个差分，再做一些麻烦的推式子，就能得到如下关系：  
（我的推法又臭又长，而且也没什么技术含量，就不放上来了）


$$f(i)=(-p)^{k-i}\binom{n-i-1}{k-i}+(1-p)f(i+1)$$
用线性筛求出 $i^k \ (i\in [1,k])$，时间复杂度就可以做到 $\Theta(k)$。  
要注意的是 $n \le k$ 的时候会有点问题，直接用最开始的式子，暴力计算即可。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 10000003
#define ll long long
#define p 998244353
#define reg register
using namespace std;

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

int n,m,k,cnt;
int f[N],inv[N],pw[N],pr[N>>1],c[N];

int solve1(){
    int mul = (ll)power(p+1-m,n-1)*m%p,invq = power(p+1-m,p-2),res = 0;
    for(reg int i=1;i<=n;++i){
        res = (res+(ll)mul*c[i]%p*pw[i])%p;
        mul = (ll)mul*invq%p*m%p;
    }
    return res;
}

int solve2(){
    int c2,mul,res = 0;
    mul = c2 = f[k] = 1;
    for(reg int i=k-1;i;--i){
        c2 = (ll)c2*(n-i-1)%p*inv[k-i]%p;
        mul = (ll)mul*(p-m)%p;
        f[i] = ((ll)c2*mul+(ll)(p+1-m)*f[i+1])%p;
    }
    mul = m;
    for(reg int i=1;i<=k;++i){
        res = (res+(ll)pw[i]*c[i]%p*mul%p*f[i])%p;
        mul = (ll)mul*m%p;
    }
    return res;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    m = power(m,p-2);
    c[0] = inv[1] = pw[1] = 1;
    c[1] = n;
    for(reg int i=2;i<=k;++i){
        inv[i] = (ll)(p-p/i)*inv[p%i]%p;
        c[i] = (ll)c[i-1]*inv[i]%p*(n-i+1)%p;
        if(!pw[i]){
            pr[++cnt] = i;
            pw[i] = power(i,k);
        }
        for(reg int j=1;j<=cnt&&(ll)i*pr[j]<=k;++j){
            pw[i*pr[j]] = (ll)pw[i]*pw[pr[j]]%p;
            if(i%pr[j]==0) break;
        }
    }
    if(n<=k+1) printf("%d",solve1());
    else printf("%d",solve2());
    return 0;	
}
```

---

## 作者：yijan (赞：14)

### CF1278F Cards

我也不知道公式挂没有，还是建议在 luogu 博客或者下面的链接里面查看。

一道斯特林数的模版练手题。不会可以看 [这里](https://www.yijan.co/si-te-lin-shu-si-te-lin-fan-yan-chu-tan/) 。

我们考虑枚举出现了多少次王牌，出现 $i$ 次王牌的概率，可以从 $n$ 轮操作选择 $i$ 轮抽出王牌，写成式子：

$$\begin{aligned}& \sum_{i\ge 0} i^k{n\choose i}\frac 1 m^{i} \frac{m-1}{m}^{n-i}\\&= \frac{1}{m^n} \sum_{i= 0}^n i^k {n\choose i} (m-1)^{n-i}\\&= \frac 1 {m^n} \sum_{i=0}^n {n\choose i} (m-1)^{n-i} \sum_{j=0}^k \left\{\begin{array}{l} k \\ j \end{array}\right\} i^{\underline j}\\&= \frac 1 {m^n} \sum_{i=0}^n {n\choose i} (m-1)^{n-i} \sum_{j=0}^k \left\{\begin{array}{l} k \\ j \end{array}\right\} {i\choose j}j!\\&= \frac 1 {m^n} \sum_{j=0}^k \left\{\begin{array}{l} k \\ j \end{array}\right\} j! \sum_{i=0}^n {n\choose i} {i\choose j} (m-1)^{n-i}\\&= \frac 1 {m^n} \sum_{j=0}^k \left\{\begin{array}{l} k \\ j \end{array}\right\} j! {n\choose j}\sum_{i=0}^n {n-j\choose i-j} (m-1)^{n-i}\\\end{aligned}$$

最后一步用到了以前写过的那个组合恒等式，就是从 $n$ 个选 $i$ 个再选 $j$ 个，本质上等价于 $n$ 个先选择好 $j$ 个，再从剩下的 $n-j$ 个选择第一步应当选择的 $i-j$ 个。

然后可以看出最后面其实是个二项式定理！

$$= \frac 1 {m^n} \sum_{j=0}^k \left\{\begin{array}{l} k \\ j \end{array}\right\} j! {n\choose j}m^{n-j}$$

然后可以很简便地写 $O(k^2)$ 了，也可以预处理第二类斯特林数的行 $O(k\log k)$ 做。可以去看 [这里](https://www.luogu.com.cn/problem/P6031) 的题解。



---

## 作者：Wen_kr (赞：13)

期望 = 概率 * 权值

考虑设这 $n$ 次中出现王牌的次数集合为 $\{C_1,C_2,\cdots,C_c\}$（在 $C_1,C_2,\cdots,C_c$ 次翻出了王牌）

若我们要求的是期望权值的 1 次方，那么这个集合的价值是集合的大小，这相当于长度为 $1$ 的有序序列个数 $\{C_1\},\{C_2\},\cdots,\{C_c\}$

若我们要求的是期望权值的 2 次方，那么这个集合的价值是集合大小的平方，这相当于长度为 $2$ 的有序序列个数 $\{C_1,C_1\},\{C_1,C_2\},\{C_1,C_3\},\cdots,\{C_c,C_c\}$

同理，若我们求的是 $k$ 次方，那么集合的价值就是长度为 $k$ 的有序序列个数

我们定义两个长度为 $k$ 的有序序列是不同的，当且仅当它们出现的概率不同

观察到两个有序序列不同，当且仅当它们包含的元素种类数不同

现在我们只需要统计本质不同的 $k$-有序序列个数即可

设 $dp[i][j]$ 表示长度为 $i$，里面有 $j$ 种元素的有序序列个数

转移很显然，$dp[i][j] = dp[i-1][j]*j+dp[i-1][j-1]*(n-j+1)$

有 $p$ 种不同元素的有序序列出现的概率为 $\frac{1}{m^p}$，最后 $O(n \log n)$ 或 $O(n)$ 计算期望即可

```cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

long long qpow(long long base,int tms)
{
	long long tmp = 1;
	while(tms)
	{
		if(tms & 1) tmp = tmp * base % mod;
		base = base * base % mod;
		tms >>= 1;
	}
	return tmp;
}

long long dp[5050][5050];
int n,m,k;

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	dp[0][0] = 1;
	for(int i = 1;i <= k; ++ i)
		for(int j = 1;j <= i; ++ j)
			dp[i][j] = (dp[i - 1][j] * j % mod + dp[i - 1][j - 1] * (n - j + 1) % mod) % mod;
	long long ans = 0;
	for(int i = 1;i <= k; ++ i)
		ans = (ans + dp[k][i] * qpow(qpow(m,mod - 2),i) % mod) % mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：dead_X (赞：12)

## 前言

好多年过去了，我来重写一下这篇题解吧（

## 思路

定义一次抽卡的**轮次集合**为所有抽出王的轮数的集合。

对于一个大小为 $x$ 的**轮次集合**，它对答案的贡献是 $x^k$。

我们将其转化为长度为 $k$，每位能选**轮次集合**中的数的序列的数量。

然后不难发现一个序列对答案的贡献只和它的不同元素相关。

我们考虑一个长度为 $k$，有 $i$ 个不同元素的序列。不难发现我们可以 $O(k^2)$ dp 求出。

它能对某个**轮次集合**有贡献，当且仅当这个轮次集合取到了这 $i$ 个元素。

不难发现所有能产生贡献的轮次集合被取到的概率和是 $\frac{1}{m^i}$，这题就做完了。 

## 代码

```
int main()
{
	long long n,m,k;
	cin>>n>>m>>k;
	a[0][0]=1;
	for(int i=1; i<=k; i++) for(int j=1; j<=i; j++) a[i][j]=(a[i-1][j-1]*(n+1-j)+a[i-1][j]*j)%998244353;
	for(int i=1; i<=k; i++) ans+=a[k][i]*power(power(m,998244351),i)%998244353,ans%=998244353;
	cout<<ans;
	return 0;
}
```

---

## 作者：pomelo_nene (赞：6)

注意到，我们只会查看第一张牌是什么，其他的牌不必要管。于是第一张牌只可能是王牌或者是其他 $m-1$ 张牌。因此洗牌后第一张牌为王牌的概率为 $\dfrac{1}{m}$。

令 $A=\dfrac{1}{m},B=1-A$，显然 $A+B=1$。根据题意，可得到答案式子：

$$
\sum_{i=0}^n \dbinom{n}{i} A^i B^{n-i} i^k
$$

注意到这个 $k$ 非常的小，猜测解法的时间复杂度为 $O(k^2)$。

又注意到这个 $k$ 是个定值，考虑将 $i^k$ 转成第二类斯特林数形式，开始魔怔推式：

$$
\sum_{i=0}^n \dbinom{n}{i} A^i B^{n-i} \sum_{j=0}^k 

\begin{Bmatrix} k \\j \end{Bmatrix} 

i^{\underline{j}}
$$

$$
\begin{aligned}
&= \sum_{j=0}^k \begin{Bmatrix} k \\j \end{Bmatrix}  \sum_{i=0}^n A^i B^{n-i} \dbinom{n}{i} i^{\underline{j}} \\
&= \sum_{j=0}^k \begin{Bmatrix} k \\j \end{Bmatrix} j! \sum_{i=0}^n A^i B^{n-i} \dbinom{n}{i} \dbinom{i}{j} \\
&= \sum_{j=0}^k \begin{Bmatrix} k \\j \end{Bmatrix} j! \sum_{i=0}^n A^i B^{n-i} \dbinom{n-j}{i-j} \dbinom{n}{j} n^{\underline{j}} \\
&= \sum_{j=0}^k \begin{Bmatrix} k \\j \end{Bmatrix} j! \dbinom{n}{j} \sum_{i=j}^n A^i B^{n-i} \dbinom{n-j}{i-j} \\
&= \sum_{j=0}^k \begin{Bmatrix} k \\j \end{Bmatrix} n^{\underline{j}} \sum_{i=0}^{n-j} A^{i+j} B^{n-i-j} \dbinom{n-j}{i} \\
&= \sum_{j=0}^k \begin{Bmatrix} k \\j \end{Bmatrix} n^{\underline{j}} A^j \sum_{i=0}^{n-j} A^{i} B^{n-i-j} \dbinom{n-j}{i} \\
&= \sum_{j=0}^k \begin{Bmatrix} k \\j \end{Bmatrix} n^{\underline{j}} A^j (A+B)^{n-j}\\
&= \sum_{j=0}^k \begin{Bmatrix} k \\j \end{Bmatrix} n^{\underline{j}} A^j\\
\end{aligned}
$$

至此 $O(k)$ 计算下降幂，$O(k^2)$ 预处理斯特林数，问题解决。

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
LL S[5005][5005],n,m,k;
LL Calc(LL s,LL t)
{
	LL ans=1;
	for(LL i=s;i>=s-t+1;--i)	ans=ans*i%MOD;
	return ans;
}
int main(){
	scanf("%lld %lld %lld",&n,&m,&k);
	m=QuickPow(m,MOD-2);
	S[0][0]=1;
	for(LL i=1;i<=k;++i)	for(LL j=1;j<=i;++j)	S[i][j]=(S[i-1][j]*j%MOD+S[i-1][j-1])%MOD;
	LL ans=0,st=1;
	for(LL i=0;i<=k;++i)	ans=(ans+S[k][i]*Calc(n,i)%MOD*st%MOD)%MOD,st=st*m%MOD;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：slenbol (赞：2)

### CF1278F 题解

#### 题目分析

根据期望的定义可以得到答案就是概率和权值的乘积。

设 $ P = \frac{1}{m}$，考虑枚举出现的王牌的个数 $x$ 则答案为

$$
f(n,k) = \sum_{x=0}^n \binom{n}{x} P^x (1-P)^{n-x} x^k
$$

直接计算的话是 $O(n)$ 的，考虑用 $k$ 进行递推。

$$
f(n,k+1) = \sum_{x=0}^n \binom{n}{x} P^x (1-P)^{n-x} x^{k+1}
$$

展开组合数 $\binom{n}{x}$ 可得

$$
f(n,k+1) = \sum_{x=0}^n \frac{n !}{x! (n-x)!} P^x (1-P)^{n-x} x^{k+1}
$$

从 $x^{k+1}$ 取出 $x$ 可得

$$
f(n,k+1) = \sum_{x=0}^n \frac{n !}{(x-1)! (n-x)!} P^x (1-P)^{n-x} x^k
$$

从 $n!$ 中取出 $n$，从 $P^x$ 中取出 $x$ 可得

$$
f(n,k+1) = \sum_{x=0}^n \frac{(n-1) !}{(x-1)! (n-x)!} P^{x-1} (1-P)^{n-x} x^k \times P\times n
$$

因为 $x=0$ 时不会对答案造成贡献所以 $x-1$ 的取值为 $[0,n-1]$，考虑枚举 $x-1$ 来代替 $x$ 可得

$$
f(n,k+1) = \sum_{x=0}^{n-1} \frac{(n-1) !}{x! (n-x-1)!} P^x (1-P)^{n-x-1} (x+1)^k \times P\times n
$$

用二项式定理拆解 $(x+1)^k$ 可得

$$
f(n,k+1) =n \times P \times \sum_{x=0}^{n-1} \frac{(n-1) !}{x! (n-x-1)!} P^x (1-P)^{n-x-1} \sum_{i=0}^k \binom{k}{i}x^i
$$

更改求和顺序可得

$$
f(n,k+1) =n \times P \times \sum_{i=0}^k \binom{k}{i} \sum_{x=0}^{n-1} \frac{(n-1) !}{x! (n-x-1)!} P^x (1-P)^{n-x-1}x^i
$$

观察式子后半段，发现即为 $f(n-1,i)$，由此可得

$$
f(n,k+1) =n \times P \times \sum_{i=0}^k \binom{k}{i}f(n-1,i)
$$

由此我们得到了一个 $O(k^3)$ 的记忆化搜索做法。终止状态为 $f(x,0)=1$。

继续优化，考虑每个 $f(x,0)$ 对答案的贡献，贡献式即为

$$
f(n,k)=\sum \binom{k-1}{x_1}\times n\times P\times \binom{x_1-1}{x_2} \times (n-1) \times P \times \dots \times f(x,0)
$$

我们发现 $n \times P \times (n-1) \times P \times \dots \times (x+1) \times P$ 只与 $x$ 相关，这启发我们枚举 $x$ 并计算答案。

我们记 $g(x)=n \times P \times (n-1) \times P \times \dots \times (x+1) \times P$ 则 $f(x,0)$ 对答案的贡献为

$$
f(n,k)=\sum g(x) f(x,0) \prod_{i=0}^{n-x-1} \binom{x_i-1}{x_{i+1}}
$$

其中 $x_0=k$ 并且 $x_{n-x}$ 为 $0$。

考虑后面式子的组合意义就是从 $k$ 个石子中钦定编号最小的不选择，选择剩下的部分任意多个石子，然后递归进行子问题。

考虑动态规划解决问题，设 $dp(i,j)$ 表示考虑前 $i$ 个数，现在在第 $j$ 层子问题的递归中的答案。初始状态 $dp(0,0)=1$。

考虑两种不同转移。

第一种不进行递归，则 $i+1$ 号石子可能属于 $j$ 层中的任意一层。

第二种递归下一层，因为需要钦定编号最小的石子一定不能递归，所以 $i+1$ 号石子一定只能属于 $j+1$ 层。

时间复杂度为 $O(k^2)$。

#### 代码实现

动态规划部分使用的不是题解部分的填表法，而是刷表法。为了保险，分了两个部分，$n>k$ 与 $n \le k$。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;T f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	x*=f;
}
template<typename T,typename ...Arg>inline void read(T &x,Arg &...arg){read(x);read(arg...);}
template<typename T>inline void print(T x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar((x%10)^48);
}
template<typename T>inline void print(T x,char c){print(x);putchar(c);}
template<typename T>inline void output(T x){print(x,' ');}
template<typename T,typename ...Arg>inline void output(T x,Arg ...arg){output(x);output(arg...);}
const int N=5007,mod=998244353;
int n,m,k,P,Q,PX[N],PP[N],PQ[N],fct[N],inv[N],ans,ddd[5007][5007];
int fpow(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1) res=(ll)res*x%mod;
		x=(ll)x*x%mod; y>>=1;
	}
	return res;
}
int __C(int x,int y){return (ll)fct[x]*inv[y]%mod*inv[x-y]%mod;}
void prework()
{
	fct[0]=PP[0]=PQ[0]=1;
	for(int i=1;i<=k;i++)
		PX[i]=fpow(i,k),fct[i]=(ll)fct[i-1]*i%mod,
		PP[i]=(ll)PP[i-1]*P%mod,PQ[i]=(ll)PQ[i-1]*Q%mod;
	inv[k]=fpow(fct[k],mod-2);
	for(int i=k;i>=1;i--)
		inv[i-1]=(ll)inv[i]*i%mod;
}
void solve1()
{
	ans=0;
	for(int x=1;x<=n;x++)
		ans=(ans+(ll)__C(n,x)*PX[x]%mod*PP[x]%mod*PQ[n-x]%mod)%mod;
	print(ans,'\n');
}
void solve2()
{
	ddd[0][0]=1;
	for(int i=0;i<k;i++)
		for(int j=0;j<=k;j++)
			ddd[i+1][j]=(ddd[i+1][j]+(ll)ddd[i][j]*j%mod)%mod,
			ddd[i+1][j+1]=(ddd[i+1][j+1]+ddd[i][j])%mod;
	
	int tot=1; ans=0;
	for(int i=1;i<=k;i++)
		tot=(ll)tot*P%mod*(n-i+1)%mod,
		ans=(ans+(ll)ddd[k][i]*tot%mod)%mod;
	print(ans,'\n');
}
int main()
{
	read(n,m,k); P=fpow(m,mod-2),Q=(1+mod-P)%mod;
	prework();
	if(n<=k) solve1();
	else solve2();
	return 0;
}
```

---

## 作者：pengyule (赞：2)

[1278F Cards](http://codeforces.com/problemset/problem/1278/F)
> 有 $m(m\le 10^9)$ 张牌，其中一张是王牌。现在你执行 $n(n\le 10^9)$ 次如下操作：洗牌后查看第一张牌是什么。
> 令 $x$ 为洗牌后第一张牌为王牌的次数，现在假设洗牌时 $m!$ 种牌的排列出现的概率均相等，求 $x^k(k\le 5000)$ 的期望值。



显然一次顶上为王牌概率 $p=\frac 1m$。
我们称轮次集合为一种方案中王牌在顶的轮次编号构成的集合。大小为 $x$ 的轮次集合产生 $x^k$ 的贡献（概率最后考虑）。
考虑 $x^k$ 的组合意义为构造一个长 $k$ 的序列只能从该轮次集合选数的方案数。
从长 $k$ 序列角度考虑它对包含它的轮次集合们做的总贡献，不难发现贡献只和序列中互异元素的个数 $t$ 有关，若 $f_t$ 为这种序列的个数，则存在这种序列的概率为 $(\frac1m)^t$（也即包含它的轮次集合们被选到的概率总和），因为序列中数本来的意义还是轮次抽到王。容易用 $O(k^2)$ 的 dp 推出 $f_t$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5,mod=998244353;
int n,m,k,ans,f[N][N];
inline int qp(int a,int b){
	int c=1;
	for(;b;b>>=1,a=a*a%mod)if(b&1)c=c*a%mod;
	return c;
}
signed main(){
	cin>>n>>m>>k;
	int p=qp(m,mod-2);
	f[1][1]=n;
	for(int i=2;i<=k;i++)
		for(int j=1;j<=i;j++)
			f[i][j]=(f[i-1][j-1]*(n-j+1)%mod+f[i-1][j]*j%mod)%mod;
	for(int i=1;i<=k;i++)ans=(ans+f[k][i]*qp(p,i)%mod)%mod;
	cout<<ans;
}
```

---

## 作者：dottle (赞：1)

接下来，我们所说的 $m$ 是原题中 $m$ 的倒数，即每堆牌第一张是王牌的概率。

考虑设 $f_{x,i}$ 表示 $x$ 次洗牌后答案 $i$ 次方的期望，则答案就是 $f_{n,k}$。

首先考虑 $f_1$，显然 $f_{1,0}=1,f_{1,i}=m(i\ne0)$（此处认为 $0^0=1$）。

接下来考虑根据 $f_{x}$ 和 $f_y$ 计算 $f_{x+y}$。因为 
$$
(a+b)^k=\sum_{i+j=k} a^ib^j\binom ki
$$
根据期望的线性性可以得到 
$$
f_{x+y,k}=\sum_{i+j=k}f_{x,i}f_{y,j}\binom ki
$$
那这个显然可以倍增算，复杂度 $O(k^2\log n)$。

然后容易发现这是一个卷积的形式，复杂度 $O(k\log k\log n)$。

然后这个卷积是一个 EGF 的形式，那么我们设
$$
F(x)=1+\sum_{i\ge 1}m \frac{x^i}{i!}
$$
答案就是 $k![x^n]F^n(x)$。这个东西可以多项式快速幂，复杂度 $O(k\log k)$。

然后这个东西其实可以转化到鱼题解推的式子，考虑确定 $F^n(x)$ 中哪些因式的次数不为 $0$，次数为 $0$ 因式的系数为 $1$，可以不管。那么
$$
\begin{aligned}
Ans&=\sum_{i=1}^k\binom ni \times [x^k](me^x-m)^i\\
&=\sum_{i=1}\binom ni m^i S_{i}^ki!\\
&=\sum n^{\underline i}m^iS^{k}_{i}
\end{aligned}
$$


---

## 作者：Xiao_mo (赞：1)

# Step1
考虑$O(n)$做法

$ans={\sum\limits_{x=1}^n}C(n,m)×x^k×(m-1)^{n-x}×(\frac{1}{m})^n$

# Step2

$f(n,m)$
~~(因为我代码用的f[i][j])~~
表示把n个相同的球放在m个相同的箱子里,每个箱子至少有一个球

### 小芝士:
$x^k={\sum\limits_{i=0}^k}f(k,i)×i!×C(x,i)$

$C(n,x)×C(x,i)=C(n-i,x-i)×C(n,i)$

${\sum\limits_{x=0}^n}x^i×C(n,i)=(1+x)^n$

所以就可以对$O(n)$的式子进行优化
### $ans$
$={\sum\limits_{x=1}^n}{\sum\limits_{i=0}^k}f(k,i)×i!×C(n,x)×C(x,i)×(m-1)^{n-x}×(\frac{1}{m})^n$

$={\sum\limits_{x=1}^n}{\sum\limits_{i=0}^k}f(k,i)×i!×C(n-i,x-i)×C(n,i)×(m-1)^{n-x}×(\frac{1}{m})^n$

$={\sum\limits_{i=0}^k}{\sum\limits_{x=1}^n}f(k,i)×i!×C(n-i,x-i)×C(n,i)×(m-1)^{n-x}×(\frac{1}{m})^n$

$={\sum\limits_{i=0}^k}f(k,i)×i!×C(n,i)×(\frac{1}{m})^n{\sum\limits_{x=i}^n}C(n-i,x-i)×(m-1)^{n-x}$

$={\sum\limits_{i=0}^k}f(k,i)×\frac{n!}{(n-i)!}×(\frac{1}{m})^n{\sum\limits_{x=i}^n}C(n-i,x-i)×(m-1)^{n-x}$

$={\sum\limits_{i=0}^k}f(k,i)×\frac{n!}{(n-i)!}×(\frac{1}{m})^n×(m-1)^{n-i}{\sum\limits_{x=0}^{n-i}}C(n-i,x)×(\frac{1}{m-1})^x$

$={\sum\limits_{i=0}^k}f(k,i)×\frac{n!}{(n-i)!}×(\frac{1}{m})^n×(m-1)^{n-i}(1+\frac{1}{m-1})^{n-i}$

$={\sum\limits_{i=0}^k}f(k,i)×\frac{n!}{(n-i)!}×(\frac{1}{m})^i$

优化可得$O(k)$的式子
$ans={\sum\limits_{i=0}^k}f(k,i)×\frac{n!}{(n-i)!}×(\frac{1}{m})^i$

# Step3
预处理$f[i][j]$

$f[i][i]=1$

$f[i][j]=f[i-1][j]×j+f[i-1][j-1]$

此处应该为$O(k^2)$

# End
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rg register
using namespace std;
const ll p=998244353;
inline ll read() {
	register ll s=0,f=0;
	register char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
ll n,m,k,f[5001][5001],ans,inv;
inline ll qpow(ll y,ll z) {
	ll sum=1;
	for(ll s=z; s; s>>=1,y=(y*y)%p) {
		if(s&1)sum=(sum*y)%p;
	}
	return sum;
}
inline ll lc(int x) {
	ll sum=1;
	for(int i=1; i<=x; i++)sum=(sum*(n-i+1))%p;
	return sum;
}
int main() {
	n=read(),m=read(),k=read(),inv=qpow(m,p-2);
	for(int i=0; i<=k; i++)f[i][i]=1;
	for(int i=2; i<=k; i++) {
		for(int j=1; j<i; j++)f[i][j]=(f[i-1][j]*j+f[i-1][j-1])%p;
	}
	for(int i=0; i<=k; i++) ans=(ans+f[k][i]*lc(i)%p*qpow(inv,i)%p)%p;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

菜鸡只会做 $O(k^2+\log \text{MOD})$。。。

假设对与一个随机方案，有些轮选了 Joker，有些轮没有。

叫一个向量 $A$ 合法当且仅当 $A[i]$ 里面所有元素都是选 Joker 的轮的编号。那么 $x^k$ 可以表示为有多少个长度为 $k$ 的合法向量。

对与一个向量 $A$（$1\le A[i]\le m$），设 $P(i)$ 为这个向量合法的可能性，也就是对与所有 $A[i]$，在第 $A[i]$ 轮出现一个 Joker 的概率。

设 $S$ 为所有长度为 $k$ 的向量，答案就是 

$$\sum_{A\in S}P(A)$$

但是，$P(A)$ 可能提取的值很少。发现 $P(A)$ 肯定等于 $\frac{1}{m^x}$（不知道为什么请继续），和 $0 < x \le k$。

设 $C(x)$ 为有多少向量 $A$ 使得 $P(A) = \frac{1}{m^x}$，答案就是

$$\sum_{x=1}^k\frac{C(x)}{m^x}$$

可以用 DP 求 $C(x)$。

$C(x)$ 的值就是有多少个长度为 $k$ 的向量使得含有恰好 $x$ 个互不相同元素。为什么呢？假设有一个向量 $A$，和我们已经知道 $P(A)$。如果在 $A$ 里面添加一个原来已经有的元素，$P(A)$ 不会变，应为已经保证这一轮选取 Joker；否则，$P(A)$ 会乘以 $\frac{1}{m}$ 应为只有一个 $\frac{1}{m}$ 可能性来选取 Joker 在一个新的轮里面。

DP 状态是 [向量长度][多少个互不相同元素]。

一个状态 $DP[i][j]$ 对别的状态贡献的值是：

 - 对与 $DP[i+1][j]$，就是加一个原来出现过的元素，有 $j$ 个选择，或者 $j\cdot DP[i][j]$
 - 对与 $DP[i+1][j+1]$，就是添加一个新元素，有 $m-j$ 个选择，或者 $(m-j)\cdot DP[i][j]$
 
在最后直接用上面求和方程就可以了。

主要代码：

```cpp
const int MOD = 998244353;

int dp[5005][5005];

int qpow(const int&b, const int&e) {
	if(!e) return 1;
	if(!(e&1)) return qpow(1ll*b*b%MOD,e>>1);
	return 1ll*b*qpow(b,e-1)%MOD;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, k; gi(n), m = 1, gi(k);
	dp[0][0] = 1;
	rep(len, k+1)
		rep(distinct, min(k,n)+1) {
			dp[len+1][distinct+1] = (1ll*(n-distinct)*dp[len][distinct]+dp[len+1][distinct+1])%MOD;
			dp[len+1][distinct] = (1ll*distinct*dp[len][distinct]+dp[len+1][distinct])%MOD;
		}
	m = qpow(m, MOD-2);
	int ans = 0, cm = 1;
	rep(distinct, min(k,n)+1) {
		ans = (ans+1ll*cm*dp[k][distinct])%MOD;
		cm = 1ll*cm*m%MOD;
	}
	cout << ans << endl;
}
```

---

## 作者：Tony102 (赞：1)

[Link](https://www.luogu.com.cn/problem/CF1278F)

[Blog体验更佳](https://tony102.xyz/index.php/2021/02/25/cf1278f-cards/)


### Sol

现在要求的是

$$E((\sum_{i=0}^{k} x_i)^k)$$

现在设$p = \frac{1}{m}$ ，表示一次性抽中王牌的概率。现在枚举$i$次王牌，那么抽中$i$次王牌的概率为$p^i$，其余$n-i$轮抽中的都不是王牌的概率为$(1-p)^{n-i}$。 那么题目条件中的$x^k$就是$i^k$ 。可以暴力计算把原式化为

$$E = \sum_{i=0}^{n} \binom{n}{i} p^i (1-p)^{n-i}i^k$$

把$i^k$拆成斯特林数的形式。看见这种样子的式子，就要想到类似联合省选组合数问题的把次幂形式的东西转成第二类斯特林数处理。那么有

$$\sum_{i=0}^{n}  \binom{n}{i} p^i (1-p)^{n-i} \sum_{j=0}^{k} \begin{Bmatrix} j \\ k \end{Bmatrix} i^{\underline j} $$

斯特林数预处理计算完成，现在斯特林数没什么要做的了，提前面去。下降幂形式的东西拆开看才会比较有发现。

$$\sum_{j=0}^{k} \begin{Bmatrix} j \\ k \end{Bmatrix} \sum_{i=0}^{n} \binom{n}{i} p^i (1-p)^{n-i} \binom{i}{j} j! $$

看见了吧，$\binom{i}{j} \cdot \binom{n}{i} = \binom{n-j}{i-j} \cdot\binom{n}{j} = \binom{n-j}{n-i} \cdot \binom{n}{j}$ 。为什么这么做？看见$(1-p)^{n-i}$这一项的指数是$n-i$ 现在出了一个组合数$\binom{n-j}{n-i}$ 。怎么搞，二项式定理搞。此外，$\binom{n}{j} \cdot j! = n^{\underline j}$先看下现在的式子

$$\sum_{j=0}^{k} \begin{Bmatrix}j \\ k \end{Bmatrix} n^{\underline j} \sum_{i=0}^{n} \binom{n-j}{n-i} p^i (1-p)^{n-i}$$

实际上枚举$i$的效果和枚举$n-i$效果是一样的嘛，求和上界改成$n-j$ , 因为当$i' > n -j$ 是组合已经无意义

$$\sum_{j=0}^{k} \begin{Bmatrix}j \\ k \end{Bmatrix} n^{\underline j} \sum_{i=0}^{n-j} \binom{n-j}{i} p^{n-j-i} (1-p)^{i}$$

现在的愣头小青年都喜欢OGF，说我不喜欢组合意义，我永远只喜欢生成函数

试试二项式定理，为了方便，设$x=p, y = 1-p$ 。有$x+y = 1$

$$(x+y)^{n-j} = \sum_{i=0}^{n-j} \binom{n-j}{i} x^{n-j-i} y^{i}$$

这玩意就等于 $1$ 吧，所以后面那个和式已经是$1$了。我们要求只有前面那一个和式，也就是

$$\sum_{j=0}^{k} \begin{Bmatrix}j \\ k \end{Bmatrix} n^{\underline j}$$

$k \leq 5 \times 10^3$  所以直接 $O(n^2)$ 预处理组合数，和 $n^{\underline j} = \binom{n}{j} j! = \frac{n!}{(n-j)!}$ 

### Code
[Code请戳这里](https://tony102.xyz/index.php/2021/02/25/cf1278f-cards/)


---

## 作者：RockyYue (赞：0)

# 解题思路
由于本蒟蒻不太会用 $L^A T_E X$ ，本题解题思路改用手写。

![](https://img-blog.csdnimg.cn/7b4b7c3f371b499ea15772a0a1a2cdf1.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6JKf6JK75LiA5p6a,size_20,color_FFFFFF,t_70,g_se,x_16)

# 代码实现

不开 long long 见祖宗，十年 OI 一场空。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5005, P = 998244353;
int a[N], dp[N][N];
int qpow(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) {
			(res *= x) %= P;
		}
		(x *= x) %= P;
		y >>= 1;
	}
	return res;
}
signed main() {
	ios :: sync_with_stdio(0);
	int n, m, k;
	cin >> n >> m >> k;
	a[0] = 1;
	for (int i = 1; i <= k; ++i) {
		a[i] = a[i - 1] * qpow(i, P - 2) % P;
	}
	dp[1][1] = 1;
	for (int i = 2; i <= k; ++i) {
		for (int j = 1; j <= i; ++j) {
			dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % P * j % P;
		}
	}
	int res = 0, mul = qpow(m, P - 2), base = mul, C = n;
	for (int i = 1; i <= k; ++i) {
		(res += base * a[i] % P * dp[k][i] % P * C % P) %= P;
		(base *= mul) %= P;
		(C *= n - i) %= P;
	}
	cout << res << '\n';
	return 0;
}

```


---

