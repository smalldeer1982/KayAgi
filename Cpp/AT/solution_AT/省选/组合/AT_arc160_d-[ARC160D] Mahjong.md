# [ARC160D] Mahjong

## 题目描述

找到可以通过以下两种操作，使得长度为 $N$、元素之和为 $M$ 的数列 $A$ 全为 $0$ 的 $A$ 的个数，再取模 $998244353$。

1. 在 $A$ 中选一个元素，将其减去 $K$。
2. 在 $A$ 中选取长度为 $K$ 的子串，子串中每个元素减去 $1$。

## 说明/提示

- $1\le K\le N\le2000$
- $1\le M\le10^{18}$

## 样例 #1

### 输入

```
3 2 2```

### 输出

```
5```

## 样例 #2

### 输入

```
100 998244353 100```

### 输出

```
0```

## 样例 #3

### 输入

```
2000 545782618661124208 533```

### 输出

```
908877889```

# 题解

## 作者：zsq147258369 (赞：13)

感谢 @_maze 的指正。

搞笑题，笔者会做，但是笔者组合数除了 $0$，笔者更搞笑。

首先判一下无解，就是 $m \not \equiv 0\mod k$，没啥好说的。

考虑倒着加，共操作 $\dfrac mk$ 次，由于在同一个位置操作 $k$ 次操作二相当于在这 $k$ 个位置进行操作一，所以说猜想每个位置最多操作 $k-1$ 次操作二，操作一没有限制，这样操作后的数列唯一。

来证一证。

* 把每个位置上的操作一次数看成一个序列，那么这个操作序列和最后的结果序列一一对应。

这很显然。
由于这个结论，那么可以通过某种方法算出这 $n-k+1$ 位的操作二方案数。

* 若每一位操作二次数小于 $k$，那么就无法通过两个操作合在一起来表示。

其实相当于把最后的序列每一位尽可能的减去 $k$，最后得到的序列只能用操作二表示。

如此，便可枚举操作二的次数 $i$，然后在 $n$ 个位置上随意放置 $\dfrac mk-i$ 个操作一，表示成柿子如下
$$
ans=\sum_{i=0}^{(n-k+1)(k-1)}g(i)\times \binom {n-1+\dfrac mk-i}{n-1}
$$
其中，$g(i)$ 表示操作二方案数，后面的是操作一的方案数。

由于笔者的组合数水平极低，而且也有一颗想暴力草计数的心，所以说笔者采用暴力 DP 的方式求出 $g$。
$$
g(i,j)=\sum_{t=j-k}^jg(i-1,t)
$$
由此，笔者最开始的[代码](https://www.luogu.com.cn/paste/gkqur0e9)出世了！~~$n^3$ 跑 $2000$。~~

样例三跑了 12s，开 Ofast 之后跑到了 10s 左右。

* 优化

注意到算答案时的组合数，枚举的 $i$ 是连续的，那么没必要都算一遍，直接递推即可。

[现在](https://atcoder.jp/contests/arc160/submissions/41453850)样例三可以跑到 2s 多了，但还远远不够。

由于 $g(i,j-1)$ 有 $g(i,j)$ 一部分，那么可以省去前缀和。

因为在一个位置上放 $t$ 个操作一等价于在这个位置先充 $k-1$ 个操作一然后再减去 $t$ 次操作一，那么 $g(i,j)=g(i,i(k-1)-j)$，每次只用算一半即可，终于[优化](https://atcoder.jp/contests/arc160/submissions/41473032)到 2s 以内了！

嗯？？怎么还 WA 了 6 个点呢？？？

在苦思冥想之后，笔者终于决定~~三分套数据了~~！

众所周知，套数据是一种很浪费时间而且不符合信息学精神的方法，所以在用两页提交套出 $n$ 和 $k$ 之后笔者便放弃了。

其实，在本文的开头，笔者埋了一个伏笔：

```
但是笔者组合数除了 0。
```
没错，由于在递推组合数时，很有可能会除一个 $998244353$ 的倍数，也就是 $0$，加一个特判就可以过了。

[最后的代码](https://atcoder.jp/contests/arc160/submissions/41493506)。

---

## 作者：EuphoricStar (赞：9)

搞笑题，我不会做，我更搞笑。

考虑逆序操作，即初始有一个全 $0$ 序列，每次单点加 $k$ 或者长为 $k$ 区间加 $1$。考虑把一个操作集合唯一对应到一个最终序列，不难发现只要限制每个区间加 $1$ 的次数 $< k$ 即可。因为如果正序操作，加上了限制，每个点被每个区间加的次数能算出来。

于是题目变成了统计序列 $b_{1 \sim 2n - k + 1}$ 个数，要求：

- $\sum\limits_{i=1}^{2n - k + 1} b_i = \frac{m}{k}$
- $\forall i \in [1, n - k + 1], b_i < k$

这是一个有上界的插板法，容斥，钦定 $i$ 个元素不合法，其余任意，那我们得到：

$$ans = \sum\limits_{i=0}^{n-k+1} (-1)^i \binom{n-k+1}{i} \binom{\frac{m}{k}-ik+2n-k}{2n-k}$$

暴力计算组合数，时间复杂度 $O(n^2 \log mod)$。

[code](https://atcoder.jp/contests/arc160/submissions/41439136)

---

## 作者：Fido_Puppy (赞：8)

## 题目链接

[[ARC160D] Mahjong](https://atcoder.jp/contests/arc160/tasks/arc160_d)

## 题解

考虑反过来，刚开始 $A$ 数组全为 $0$，每次能给一个长度为 $K$ 的区间加 $1$，或者给一个位置加 $K$，求能够得到的不同的 $A$ 的数量。

设 $B_i$ 表示区间 $[i - K + 1, i]$ 加 $1$ 的操作数，$C_i$ 表示单点 $i$ 加 $K$ 的操作数。

**那么只需要满足 $\forall i, B_i < K$，那么 $A$ 和二元组 $(B, C)$ 形成双射。**

+ 如果 $\exists i, B_i \ge K$，那么 $K$ 次区间 $[i - K + 1, i]$ 加 $1$ 必定能够被单点加 $K$ 替代，所以满足必要性。

+ 先不考虑单点加 $K$ 操作，如果将区间加 $1$ 操作都做好之后，考虑能否唯一的推出操作序列。

+ 首先考虑 $A_1$，其只受区间 $[1, K]$ 加 $1$ 的影响，所以 $[1, K]$ 必定是加了 $A_1$ 次；然后考虑把区间 $[1, K]$ 的影响去掉，那么 $A_2$ 就只受到区间 $[2, K + 1]$ 加 $1$ 的影响了，也能推出 $[2, K + 1]$ 加 $1$ 的操作次数，以此类推，能够唯一地推出所有操作序列。

+ 并且每次 $A_1$，去掉 $[1, K]$ 加操作影响后的 $A_2$ 等等，都必定是 $< K$ 的，所以并不能构造出一种操作序列，使得其包含单点加 $K$ 操作并且能得出一样的 $A$，所以满足充分性。

接下来只需要数 $(B, C)$ 的数量就能够得出 $A$ 的数量。

考虑 $\text{dp}$，设 $f_{i, j}$ 表示前 $i$ 个只对前 $i$ 个位置操作，总和为 $\bm{j \cdot K}$ 的方案数。

容易得到：

$$f_{i, j} \longrightarrow f_{i + 1, j + 0}, f_{i + 1, j + 1}, \cdots, f_{i + 1, j + K - 1} \qquad (\forall i \in [K, N])$$

$$f_{i, j} \longrightarrow f_{i + 1, k} \qquad (\forall i \in [1, N], \forall k \ge j)$$

两个转移分别对应 $B$ 数组和 $C$ 数组。

发现转移比较简单，考虑用生成函数来表示转移，设：

$$F_i = \sum_{j \ge 0} f_{i, j} x ^ j$$

容易得到：

$$\begin{cases} F_i = F_{i - 1} \times \dfrac{1}{1 - x} \qquad (i < K) \\ F_i = F_{i - 1} \times \dfrac{1}{1 - x} \cdot (1 - x ^ K) \times \dfrac{1}{1 - x} \qquad (i \ge K) \end{cases}$$

所以最后答案为：

$$[x ^ {\frac{M}{K}}] {\left(\dfrac{1}{1 - x}\right)} ^ {2N - K + 1} \times {(1 - x ^ K)} ^ {N - K + 1}$$

若 $M \not\equiv 0 \pmod{K}$，那么答案为 $0$。

考虑上述式子如何计算：

- ${(1 - x ^ K)} ^ {N - K + 1}$ 可以用二项式定理拆成 $N - K + 1$ 项。

- ${\left(\dfrac{1}{1 - x}\right)} ^ {2N - K + 1}$ 就是做 $2N - K + 1$ 次前缀和。

$${(1 - x ^ K)} ^ {N - K + 1} = \sum_{i = 0} ^ {N - K + 1} \binom{N - K + 1}{i} \cdot (-1) ^ {N - i + 1} \cdot x ^ {K(N - i + 1)}$$

$$\because \dfrac{1}{(1 - x) ^ m} = \sum_{i \ge 0} \binom{i + m - 1}{m - 1} x ^ i$$

所以求第 $\dfrac{M}{K}$ 项，直接暴力卷积即可，根据上述式子，能够得到答案为：

$$\sum_{i = 0} ^ {N - K + 1} \binom{\dfrac{M}{K} - iK + 2N - K}{2N - K} \cdot (-1) ^ {N - i + 1} \cdot \binom{N - K + 1}{i}$$

组合数暴力算即可，复杂度 $\Theta(N ^ 2)$。

## 代码链接

<https://atcoder.jp/contests/arc160/submissions/41604502>

---

## 作者：Graphcity (赞：6)

我们考虑为每一个合法的序列分配一个唯一的清零方式，这样我们就只需要计数合法的清零方式数量即可。我们要求：不能出现 $k$ 个覆盖同一子串的操作二。通过这个限制我们可以唯一地构筑出来合法序列。

直接大力使用生成函数：操作一为 $\dfrac{1}{1-x}$，操作二为 $\dfrac{1-x^k}{1-x}$，令 $m\gets \dfrac{m}{k}$ 二者合起来：
$$
\begin{aligned}
ans&=[x^m](\frac{1-x^k}{1-x})^{n-k+1}\cdot(\frac{1}{1-x})^n\\
&=[x^m](1-x)^{-(2n-k+1)}\cdot(1-x^k)^{n-k+1}\\
&=[x^m]\sum_{i}\binom{2n-k+i}{2n-k}x^i\sum_{j=0}^{n-k+1}\binom{n-k+1}{j}(-1)^jx^{jk}
\end{aligned}
$$
枚举右边的 $j$ 即可得到答案。时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5,Mod=998244353;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod,y>>=1;
    }
    return res;
}

int n,m,k,fac[Maxn+5],inv[Maxn+5];
inline int C(int x,int y)
{
    if(x<y || y<0) return 0;
    if(x<=Maxn) return fac[x]*inv[x-y]%Mod*inv[y]%Mod;
    int res=1;
    For(i,1,y) res=res*((x-i+1)%Mod)%Mod;
    return res*inv[y]%Mod;
}
inline int sgn(int x) {return (x&1)?Mod-1:1;}

signed main()
{
    cin>>n>>m>>k; fac[0]=inv[0]=1;
    For(i,1,Maxn) fac[i]=fac[i-1]*i%Mod;
    inv[Maxn]=Pow(fac[Maxn],Mod-2);
    Rof(i,Maxn-1,1) inv[i]=inv[i+1]*(i+1)%Mod;
    if(m%k) {cout<<0<<endl; return 0;}
    if(m==0) {cout<<1<<endl; return 0;}
    m/=k; int w=n+n-k+1,ans=0;
    For(i,0,n-k+1)
    {
        if(k*i>m) continue;
        int res=C(n-k+1,i)*sgn(i)%Mod,now=m-k*i;
        res=res*C(w+now-1,w-1)%Mod;
        ans=(ans+res)%Mod;
    }
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：DaiRuiChen007 (赞：4)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc160_d)

**题目大意**

> 定义一个序列是好的当且仅当：它可以通过给长度为 $k$ 的区间 $-1$ 和单点 $-k$ 两种方法清零。
>
> 求长度为 $n$，元素和为 $m$ 的好序列有多少个。
>
> 数据范围：$n,k\le 2000,m\le 10^{18}$。

**思路分析**

考虑一个序列会对应多少清零序列，注意到两个清零序列本质相同只可能是把 $k$ 个区间 $-1$ 和 $k$ 个单点 $-k$ 互相转化。

那么我们钦定区间 $-1$ 操作数量 $<k$。

设 $x_1\sim x_{n-k+1}$ 为每个区间被 $-1$ 的数量，$x_{n-k+2}\sim x_{2n-k+1}$ 表示每个位置被单点 $-k$ 的数量。

那么 $\sum x_i=\dfrac mk,x_1\sim x_{n-k+1}<k$，直接容斥，组合数暴力计算。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD=998244353;
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
ll binom(ll n,ll m) {
	if(n<0||m<0||m>n) return 0;
	ll x=1,y=1;
	for(int i=1;i<=m;++i) x=(n-i+1)%MOD*x%MOD,y=y*i%MOD;
	return x*ksm(y)%MOD;
}
signed main() {
	ll n,m,k,ans=0;
	scanf("%lld%lld%lld",&n,&m,&k);
	if(m%k!=0) return puts("0"),0;
	for(int i=0;i<=n-k+1;++i) {
		ans=(ans+(i&1?-1:1)*binom(n-k+1,i)*binom(m/k-i*k+2*n-k,2*n-k))%MOD;
	}
	printf("%lld\n",(ans+MOD)%MOD);
	return 0;
}
```

---

## 作者：Leasier (赞：3)

由于每次操作都会使原序列中数的和减少 $k$，则当 $k \nmid m$ 时无解。

**直接对合法操作序列计数显然是会算重的，考虑给每个合法的 $a$ 钦定一个唯一的合法操作序列。**

注意到当一个子串被减了 $k$ 次与子串中每个位置加一次 $k$ 等价，考虑强制每个子串操作次数 $< k$。不难发现满足这个条件的操作序列恰好与合法的 $a$ 一一对应。

设 $f_i$ 表示子串 $[i, i + k - 1]$ 被操作的次数，$g_i$ 表示 $i$ 被操作的次数，则其需要满足：

- $\forall 1 \leq i \leq n - k + 1, 0 \leq f_i < k$。
- $\forall 1 \leq i \leq n$，$g_i \geq 0$。
- $\displaystyle\sum_{i = 1}^{n - k + 1} f_i + \sum_{i = 1}^n g_i = \frac{m}{k}$。

这是一个经典的容斥问题，考虑枚举有几个 $f_i$ 不满足条件，可得答案为：

- $\displaystyle\sum_{i = 0}^{n - k + 1} (-1)^i C_{n - k + 1}^i C_{2n + \frac{m}{k} - k(i + 1)}^{2n - k}$。

暴力算组合数即可。时间复杂度为 $O(n(n + \log mod))$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 998244353;

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline ll comb(ll n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	ll up = 1, down = 1;
	for (int i = 1; i <= m; i++){
		up = up * ((n - i + 1) % mod) % mod;
		down = down * i % mod;
	}
	return up * quick_pow(down, mod - 2, mod) % mod;
}

int main(){
	int n, k;
	ll m;
	scanf("%d %lld %d", &n, &m, &k);
	if (m % k != 0){
		printf("0");
		return 0;
	}
	int up = n - k + 1;
	ll ans = 0;
	m /= k;
	for (int i = 0; i <= up; i++){
		if (i % 2 == 0){
			ans = (ans + comb(up, i) * comb(n * 2 + m - (i + 1) * k, n * 2 - k) % mod) % mod;
		} else {
			ans = ((ans - comb(up, i) * comb(n * 2 + m - (i + 1) * k, n * 2 - k) % mod) % mod + mod) % mod;
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：3)

## 思路

记 $B_i$ 表示以 $i$ 为操作区间的左端点进行了多少次 $2$ 操作。$B$ 的长度应该是 $n-k+1$。

如果 $B_i\geq k$，那么我们可以转而进行 $1$ 操作。于是 $B_i<k$，此时这一系列 $2$ 操作是不能被 $1$ 操作替代的。

然后就可以计数了。设 $f_j$ 表示满足 $B_i<k$ 且 $\sum B_i=j$ 的方案数。

$f_j$ 可以多项式快速幂求出。具体地，就是 $n-k+1$ 个长度为 $k$ 的系数全 $1$ 的多项式乘起来。

最后插板地分配 $1$ 操作。乘一个组合数即可。

注意组合数里面要小心 $998244353$ 的倍数。避免 $0$ 的逆元。

复杂度 $\mathcal O(nk(\log nk+\log mod))$。

## code

[最后 1min 极限场切。](https://atcoder.jp/contests/arc160/submissions/41423770)

```cpp
#include<stdio.h>
#define int long long
#define M 1048576
#define mod 998244353
#define g 3
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,m,k,binv[M],pw[M],a[M],b[M],ans;
inline long long ksm(long long a,int b)
{
	long long ans=1;
	for(;b;b>>=1,a*=a,a%=mod)if(b&1)ans*=a,ans%=mod;
	return ans;
}
inline void ntt(int*a,const bool&f)
{
	for(int i=1;i<M;++i)if(binv[i]<i)a[i]^=a[binv[i]]^=a[i]^=a[binv[i]];
	for(int l=1;l<M;l<<=1)
	{
		pw[0]=1;pw[1]=ksm(g,(mod-1)/(l<<1));if(f)pw[1]=ksm(pw[1],mod-2);
		for(int i=2;i<l;pw[i]=pw[i-1]*pw[1]%mod,++i);
		for(int i=0;i<M;i+=l<<1)for(int j=0;j<l;++j)
		{
			int u=a[i|j],v=a[i|j|l]*pw[j]%mod;
			a[i|j]=u+v-mod;a[i|j]>>63&&(a[i|j]+=mod);
			a[i|j|l]=u-v;a[i|j|l]>>63&&(a[i|j|l]+=mod);
		}
	}
	if(f)
	{
		long long nn=ksm(M,mod-2);
		for(int i=0;i<M;a[i]=a[i]*nn%mod,++i);
	}
}
inline int c(const int&n,const int&m)
{
	int ans=1;
	for(int i=1;i<=m;++i)
	{
		if((n-i+1)%mod)ans=ans*((n-i+1)%mod)%mod;
		ans=ans*ksm(i,mod-2)%mod;
	}
	return ans;
}
main()
{
	for(int i=1;i<M;++i)binv[i]=binv[i>>1]>>1,(i&1)&&(binv[i]|=M>>1);
	read(n);read(m);read(k);
	if(m%k){putchar('0');return 0;}
	for(int i=0;i<k;a[i++]=1);b[0]=1;
	ntt(a,0);ntt(b,0);
	for(int i=n-k+1;i;i>>=1)//快速幂
	{
		if(i&1)for(int j=0;j<M;b[j]=b[j]*a[j]%mod,++j);
		for(int j=0;j<M;a[j]=a[j]*a[j]%mod,++j);
	}
	ntt(b,1);m/=k;
	for(int i=0,j=c(n+m-1,n-1);i<=(n-k+1)*(k-1);++i)
	{
		if((n+m-i-1)/mod==(m-i)/mod&&(m-i)>=0)ans=(ans+j*b[i])%mod;//记答案
		if((n-i+m-1)%mod)j=j*ksm((n-i+m-1)%mod,mod-2)%mod;//推组合数
		if((m-i)%mod)j=j*((m-i)%mod)%mod;
	}
	printf("%lld",ans);
}
```



---

## 作者：MrcFrst (赞：2)

### Solution

首先判掉 $k\nmid m$ 时显然无解的情况。

然后考虑倒着做，往序列上加，那么有显然的 dp，记 $f_{i,j}$ 表示考虑前 $i$ 个位置，总共做了 $j$ 次操作的方案数，转移的时候将区间加操作钦定在最后一个位置统计，暴力枚举操作的数量即可转移。

但发现会算重，具体来说，在同一个末位置进行 $k$ 次区间加操作等效于做 $k$ 次单点加。所以我们钦定同一位置只能做最多 $k-1$ 次区间加操作，这样就不会算重了。转移的时候枚举两种操作即可转移，用前缀和优化之类的操作可以优化复杂度，但是复杂度仍然很炸，因为与操作数相关。

考虑到区间加操作有 $k-1$ 的次数限制，而单点加操作没有限制，于是可以把两种操作分开考虑，有 $n-k+1$ 个位置进行区间加，$n$ 个位置进行单电加，相当于限制前者每个数 $\lt k$，后者随便填，这 $2n-k+1$ 个数的总和为操作数 $\frac{m}{k}$。

枚举 $i$ 个位置一定不合法，其他随便填（可以填 $0$），就可以把 $\lt k$ 的限制容斥掉，然后用插板法即可。

$$
ans=\sum_{i=0}^{n-k+1}{(-1)^i {n-k+1\choose i}{\frac{m}{k}-ik+2n-k\choose 2n-k}}
$$

暴力计算组合数，时间复杂度 $O(n^2\log mod)$。

-------------------

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
const int N=2020,mod=998244353;
int n,m,k,ans;
il int read(){
    re int x=0;re char c=getchar(),f=0;
    while(c<'0'||c>'9')f|=(c=='-'),c=getchar();
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();
    return f?-x:x;
}
il int Pow(int a,int b){
    re int res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod,b>>=1;
    }
    return res;
}
il int C(int n,int m){
    if(n<0||m<0||n<m)return 0;
    re int res=1;
    for(re int i=n;i>n-m;i--)res=res*(i%mod)%mod;
    for(re int i=1;i<=m;i++)res=res*Pow(i,mod-2)%mod;
    return res;
}
signed main(){
    n=read(),m=read(),k=read();
    if(m%k)return puts("0"),0;
    m/=k;
    for(re int i=0;i<=n-k+1;i++)
        ans=(ans+((i&1)?mod-1:1)*C(n-k+1,i)%mod*C(m-i*k+(n<<1)-k,(n<<1)-k))%mod;
    cout<<ans;
    return 0;
}
```

---

## 作者：orz_z (赞：1)

若 $m \not\equiv 0 \pmod k$，无解。

考虑将操作二个数限制为 $< k$，否则可转化为几次操作一和 $\le k$ 次操作二，那么一个操作集合唯一对应一种最终序列，于是对操作集合进行计数即可。

记序列 $b_{1\sim n-k+1}$ 为每个点作为二操作开头加了几次，记 $b_{n-k+2\sim 2n-k+1}$ 中 $b_i$ 为点 $i-(n-k+1)$ 用了几次操作一那么计数 $b$ 序列即可。

需要满足以下条件：

* $\forall i\in[1,n-k+1],b_i<k$
* $\sum\limits_{i=1}^{2n-k+1}b_i=\frac{m}{k}$

带限制，考虑容斥，钦定前 $n-k+1$ 个元素中至少有 $i$ 个不合法，则计数和为 $\frac{m}{k}-ik$ 的 $b$ 序列即可，由插板法得：
$$
ans=\sum_{i=0}^{n-k+1}(-1)^{i} \begin{pmatrix}n-k+1\\i\end{pmatrix}\begin{pmatrix}\frac{m}{k}-ik+2n-k\\2n-k\end{pmatrix}
$$
时间复杂度 $\mathcal O(n^2\log mod)$。

---

## 作者：CmsMartin (赞：0)

时光倒流。考虑从一个全 $0$ 的数列往上加。但是这样子会重复。考虑什么情况原始数列会重复。肯定是有一个区间 $+1$ 进行了多于 $k$ 次，这样子显然可以转化为若干次单点加 $k$ 的操作。

知道这个以后我们可以考虑设 $a_i(1\le i \le n - k + 1)$ 表示第 $i$ 个位置作为起点进行懒得多少次 $1$ 操作，$b_i(1 \le i \le n)$ 表示 $i$ 位置进行多少次 $2$ 操作，原问题转化为：

 $$\sum_{i = 1}^{n - k + 1} a_i + \sum_{i = 1}^n b_i = \frac mk$$

注意限制 $\forall i \in [1, n - k + 1] a_i \le k$。 

这个限制考虑容斥。假设前 $n - k + 1$ 个元素大于等于 $i$ 个不合法。然后问题相等于在

$$
\sum_{i = 1}^{n - k + 1}(-1)^i \binom{n - k + 1}{i} \binom{\frac mk - i \times k + 2n - k}{2n - k}
$$

后面的式子相等于隔板法，把 $a$ $b$ 序列放在一块，然后插板使得所有出去钦定的不合法带来的 $ik$ 加起来是 $\frac mk - ik$。然后算出来就行了。

---

## 作者：WRuperD (赞：0)

一道没有那么难但是我还是不会(甚至一开始就想歪了)的计数题。

考虑逆序操作，在一个全零的序列中选择一个数加 $k$ 或连续 $k$ 个数加一。显然这种计数题关键在于如何去重。我们考虑使得每一种最终序列对应唯一的操作序列。发现如果你对于一个长度为 $k$ 的区间进行了 $k$ 次区间加一和你对于其中每一个数分别单点 $+k$ 是等价的。考虑设 $b_i$ 表示在 $[i,i+k-1]$ 操作区间加一的操作次数，则我们可以钦定所有 $\forall i \in [1,n-k+1],b_i < k$。当然还有单点加，我们设 $b_{n-k+1+i}$ 表示在位置 $i$ 进行单点加的操作次数。最后我们只需要对满足条件的不同 $b$ 序列进行简单计数即可。综上，$b$ 序列应满足以下条件：

- $\forall i \in [1,n-k+1],b_i < k$。
- $\sum\limits_{i=1}\limits^{n}b_i = {m\over k}$


计数是简单的，容斥一下，钦定有 $i$ 位不满足条件，相当于先钦定 $i$ 位放有 $k$ 个操作，然后将剩下 ${m\over k} - ik$ 个操作分给 $2n-k$ 个位置，插板法，则有：

$$ans = \sum\limits_{i=0}\limits^{i=n-k+1} (-1)^{i} {n - k + 1 \choose i} {{m\over k} - ik + 2n-k \choose 2n-k}$$

[code](https://atcoder.jp/contests/arc160/submissions/50471291)

---

