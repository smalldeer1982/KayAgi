# Bracket Insertion

## 题目描述

Vika likes playing with bracket sequences. Today she wants to create a new bracket sequence using the following algorithm. Initially, Vika's sequence is an empty string, and then she will repeat the following actions $ n $ times:

- Choose a place in the current bracket sequence to insert new brackets uniformly at random. If the length of the current sequence is $ k $ , then there are $ k+1 $ such places: before the first bracket, between the first and the second brackets, $ \ldots $ , after the $ k $ -th bracket. In particular, there is one such place in an empty bracket sequence.
- Choose string "()" with probability $ p $ or string ")(" with probability $ 1 - p $ and insert it into the chosen place. The length of the bracket sequence will increase by $ 2 $ .

A bracket sequence is called regular if it is possible to obtain a correct arithmetic expression by inserting characters '+' and '1' into it. For example, sequences "(())()", "()", and "(()(()))" are regular, while ")(", "(()", and "(()))(" are not.

Vika wants to know the probability that her bracket sequence will be a regular one at the end. Help her and find this probability modulo $ 998\,244\,353 $ (see Output section).

## 说明/提示

In the first example, Vika will get a regular bracket sequence () with probability $ p = \frac{3}{4} $ , and she will get an irregular bracket sequence )( with probability $ 1 - p = \frac{1}{4} $ . The sought probability is $ \frac{3}{4} $ , and $ 249\,561\,089 \cdot 4 \equiv 3 \pmod{998\,244\,353} $ .

In the second example, the sought probability is $ \frac{11}{25} $ .

## 样例 #1

### 输入

```
1 7500```

### 输出

```
249561089```

## 样例 #2

### 输入

```
2 6000```

### 输出

```
519087064```

## 样例 #3

### 输入

```
5 4000```

### 输出

```
119387743```

# 题解

## 作者：NaN_HQJ2007_NaN (赞：26)

[Bracket Insertion](https://www.luogu.com.cn/problem/CF1781F)

神仙 DP 题，不愧是 tourist。

容易发现，括号序列一共有 $1\cdot 3\cdot 5...\cdot (2n-1)$ 种生成方式。

假如 `(` 为 $1$，`)` 为 $-1$，那么一个序列合法的充要条件为：最小前缀和为 $0$，且以 $0$ 结尾。

现在考虑维护这些前缀和。

如果我们在当前序列某一位后插入一个 `()`，且那一位的前缀和为 $x$,那么相当于把 $x$ 替换成 $[x,x+1,x]$。

同理可知，插入 `)(` 相当于把 $x$ 替换成 $[x,x-1,x]$。

定义 $f_{n,x}$ 为，执行 $n$ 次操作，初始前缀和为 $x$ 的方案数。

那么显然有两种转移：

$$f_{n,x}=\sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{n-1}p\cdot \dbinom{n-1}{i}\cdot \dbinom{n-i-1}{j}\cdot f_{i,x}\cdot f_{j,x+1}\cdot f_{n-i-j-1,x}+\sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{n-1}(1-p)\cdot \dbinom{n-1}{i}\cdot \dbinom{n-i-1}{j}\cdot f_{i,x}\cdot f_{j,x-1}\cdot f_{n-i-j-1,x}$$

其中，$i$ 对应第一个 $x$，$j$ 对应 $x+1$ 和 $x-1$，$n-i-j-1$ 对应第二个 $x$。

由于每个部分的操作都是独立的，所以还要乘上组合数。

状态 $n^2$，转移枚举 $O(n^2)$，总复杂度 $O(n^4)$，无法接受。

我们考虑优化掉一个 $\sum$。将与 $j$ 有关的都提到前面来。

$$f_{n,x}=\sum\limits_{j=0}^{n-1}\dbinom{n-1}{j}\cdot\left[p\cdot f_{j,x+1}+(1-p)\cdot f_{j,x-1}\right]\cdot \sum\limits_{i=0}^{n-j-1}\dbinom{n-j-1}{i}\cdot f_{i,x}\cdot f_{n-i-j-1,x}$$

定义 $g_{n,x}=\sum\limits_{i=0}^{n}\dbinom{n}{i}\cdot f_{i,x}\cdot f_{n-i,x}$

那么转移方程最终可化简为：

$$f_{n,x}=\sum\limits_{j=0}^{n-1}\dbinom{n-1}{j}\cdot\left[p\cdot f_{j,x+1}+(1-p)\cdot f_{j,x-1}\right]\cdot g_{n,n-j-1}$$

最后输出 $\frac{f_{n,0}}{1\cdot 3\cdot 5...\cdot (2n-1)}$ 即可。

复杂度 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int N = 500 + 5, mod = 998244353;
ll n, p, c[N][N], f[N][N], g[N][N];
ll ksm(ll x, ll y) {
	ll res = 1;
	while (y) {
		if (y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> p; p = p * ksm(10000, mod - 2) % mod;
	for (int i = 0; i <= n; ++i) c[i][0] = 1;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= i; ++j) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	for (int i = 0; i <= n; ++i) f[0][i] = g[0][i] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int x = 0; x <= n; ++x) {
			for (int j = 0; j < i; ++j) {
				f[i][x] = (f[i][x] + (p * f[j][x + 1] + (1 - p + mod) * (x ? f[j][x - 1] : 0)) % mod * c[i - 1][j] % mod * g[i - j - 1][x] % mod) % mod;
			}
			for (int j = 0; j <= i; ++j) {
				g[i][x] = (g[i][x] + c[i][j] * f[j][x] % mod * f[i - j][x] % mod) % mod;
			}
		}
	}
	ll ans = f[n][0];
	for (int i = 1; i <= 2 * n; i += 2) ans = ans * ksm(i, mod - 2) % mod;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：绝顶我为峰 (赞：16)

场上 40min 秒了这个题成功冲上 IGM！写篇题解纪念一下。

一般括号序列 dp 的套路是记录 $dp_{l,r,0/1}$ 表示区间 $[l,r]$ 是合法括号序列，上一次转移是外面套一层括号/两个区间拼起来的方案数，然后转移直接按照括号序列的递归定义转移即可，注意两个区间拼起来的时候钦定第一个区间必须是从 $dp_{l,*,0}$ 转移过来，这样才能保证不算重。

但这里的问题在于括号序列不一定合法，我们需要找到一个可以进行类似 dp 的东西。

我们对每个括号串生成一个序列，即把每个括号的位置替换为是第几次插入的数字，比如 $(())$ 就转化成 $1221$。

如果一个区间 $[l,r]$ 满足每个在区间内出现过的数都出现了两次，意味着这个区间完整的包含了一部分操作，我们称这样的区间是合法区间。这样的区间有类似于合法括号序列的优美性质：两个合法区间拼起来还是合法区间，合法区间两侧同时加相同的数还是合法区间……这启示我们对合法区间进行 dp。

但是合法区间不一定是合法的括号序列，我们需要一个简单且可以合并的状态来刻画一个序列是否合法。套路地将括号序列转化为 $+1,-1$ 序列，但这里 $($ 对应 $-1$。那么一个合法区间是合法括号序列当且仅当区间的前缀 $\max$ 是 $0$。

这个状态是容易合并的，因为合法区间的一个性质是区间和一定是 $0$，因此合并两个区间后这个状态就是取 $\max$。

不妨记录 $dp_{l,r,k,0/1}$ 表示区间 $[l,r]$ 前缀 $\max$ 是 $k$，上一步是外面套一层/拼接得来的串的概率，分别考虑两种转移。

第一种是两部分拼起来，不难得到转移 $\dbinom{r-l+1}{i-l+1}\times dp_{l,i,x,0}\times (dp_{i+1,r,y,0}+dp_{i+1,r,y,1})\rightarrow dp_{l,r,\max(x,y),1}$，组合数是因为两边是独立的。

第二种是外面套一层，枚举套的是 $()$ 还是 $)($ 可以得到转移 $p\times(dp_{l+1,r-1,k,0}+dp_{l+1,r-1,k,1})\rightarrow dp_{l,r,\max(k-1,0),0}$ 和 $(1-p)\times (dp_{l+1,r-1,k,0}+dp_{l+1,r-1,k,1})\rightarrow dp_{l,r,k+1,0}$。

最后的答案就是 $(dp_{1,n,0,0}+dp_{1,n,0,1})\prod\limits_{i=1}^n\frac1{2i-1}$，直接做是 $O(n^5)$ 的，注意到第一种转移前缀 $\max$ 一维的合并是取 $\max$，可以直接前缀和优化，变成 $O(n^4)$。

再进一步发现相同长度的不同区间本质上没有区别，那么记 $f_{i,j,0/1}$ 表示长度是 $i$，前缀 $\max$ 是 $j$ 的区间，上次是套了一层/两个拼起来的概率，那么 $dp_{l,r,x,y}=f_{r-l+1,x,y}$，因此只要对每个区间长度做一次 dp 即可，时间复杂度 $O(n^3)$，可以通过此题。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int mod=998244353;
int n,p,dp[501][501][2],sum[501][501][2],c[501][501];
inline void init()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}
inline int read()
{
    int x;
    cin>>x;
    return x;
}
inline int pw(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)
            res=1ll*res*a%mod;
        b>>=1;
        a=1ll*a*a%mod;
    }
    return res;
}
inline int Mod(int x)
{
    return x>=mod? x-mod:x;
}
int main()
{
    init();
    n=read(),p=1ll*read()*pw(10000,mod-2)%mod;
    c[0][0]=dp[0][0][0]=1;
    for(int i=1;i<=n;++i)
    {
        c[i][0]=1;
        for(int j=1;j<=i;++j)
            c[i][j]=Mod(c[i-1][j]+c[i-1][j-1]);
    }
    for(int i=0;i<=n;++i)
        sum[0][i][0]=1;
    for(int i=1;i<=n;++i)
        for(int j=0;j<=n;++j)
        {
            for(int k=1;k<i;++k)
                dp[i][j][1]=Mod(dp[i][j][1]+1ll*c[i][k]*Mod(1ll*sum[k][j][0]*Mod(sum[i-k][j][0]+sum[i-k][j][1])%mod-(j? 1ll*sum[k][j-1][0]*Mod(sum[i-k][j-1][0]+sum[i-k][j-1][1])%mod:0)+mod)%mod);
            dp[i][j][0]=Mod(dp[i][j][0]+1ll*p*Mod(dp[i-1][j+1][0]+dp[i-1][j+1][1])%mod);
            if(!j)
            {
                dp[i][j][0]=Mod(dp[i][j][0]+1ll*p*Mod(dp[i-1][j][0]+dp[i-1][j][1])%mod);
                sum[i][j][0]=dp[i][j][0];
                sum[i][j][1]=dp[i][j][1];
            }
            else
            {
                dp[i][j][0]=Mod(dp[i][j][0]+1ll*Mod(1-p+mod)*Mod(dp[i-1][j-1][0]+dp[i-1][j-1][1])%mod);
                sum[i][j][0]=Mod(sum[i][j-1][0]+dp[i][j][0]);
                sum[i][j][1]=Mod(sum[i][j-1][1]+dp[i][j][1]);
            }
        }
    int ans=Mod(dp[n][0][0]+dp[n][0][1]);
    for(int i=1;i<=n;++i)
        ans=1ll*ans*pw(i+i-1,mod-2)%mod;
    cout<<ans<<'\n';
    cout.flush();
    return 0;
}
```

---

## 作者：Little09 (赞：10)

场上差一步，于是被别人区分了。其实也不算是很难的题，但是还是需要对这个类型的 DP 比较熟练。

首先插入括号串可以画出折线，如果我们维护原串的前缀和，把 `(` 看做 $+1$，`)` 看做 $-1$，那么括号串合法的充要条件是前缀和所有元素非负。原本还需要最后一项为 $0$，但是本题的限制显然符合。

考虑每次插入一对括号对前缀和序列的影响。由于总是有一个 `(` 和一个 `)`，所以它后面的前缀和一定不会变化。假设插入位置前面的前缀和是 $x$，那么可以得到：如果插入 `()`，会生成 $x,x+1$；如果插入 `)(`，会生成 $x,x-1$。所以容易发现这和序列每个元素的位置也无关。

问题转化为：给定一个集合，初始为 $\{0\}$，每次随机选择一个元素 $x$，有 $p$ 的概率将 $x+1,x$ 加入集合，有 $1-p$ 的概率将 $x-1,x$ 加入集合，求最终所有元素非负的概率。

到这里其实不难。接下来我们把概率转方案数：注意到 $k$ 次操作后的集合大小一定为 $2k+1$，所以其实概率是可以计算的。如果我们给每次操作赋权值 $p$ 和 $1-p$，一个合法操作集合的权值是每次操作的权值积，那么我们可以将问题转化为：所有合法操作集合的权值和。

这个问题考虑 DP。定义 $f(n,x)$ 表示初始为 $x$ 这个数，进行 $n$ 次操作后仍然合法的操作集合的权值和。我们可以得到：

$$f(n,x)= \sum\limits_{i=0}^{n-1} \sum\limits_{j=0}^{n-1-i} p \cdot \binom{n-1}{i} \cdot \binom{n-1-i}{j} \cdot f(i, x) \cdot f(j, x + 1) \cdot f(n - 1 - i - j, x) +$$

$$+ \sum\limits_{i=0}^{n-1} \sum\limits_{j=0}^{n-1-i} (1 - p) \cdot \binom{n-1}{i} \cdot \binom{n-1-i}{j} \cdot f(i, x) \cdot f(j, x - 1) \cdot f(n - 1 - i - j, x)$$

这个式子的含义是，考虑这个 $x$ 第一次操作会变成什么，有 $p$ 权值会变成 $x,x,x+1$，有 $1-p$ 权值会变成 $x,x,x-1$。考虑接下来 $n-1$ 次操作，每次可以分配到这三个集合里的一个，所以是用组合数相乘。

这样喜提 $O(n^4)$，过不去。但是注意到这个式子太特殊了，有重复项，可以提出来。这一步并不困难。考虑定义

$$g(k, x) = \sum\limits_{i=0}^{k} \binom{k}{i} \cdot f(i, x) \cdot f(k - i, x)$$

可以得到

$$f(n, x) = \sum\limits_{j=0}^{n-1} (p \cdot f(j, x + 1) + (1 - p) \cdot f(j, x - 1)) \cdot \binom{n-1}{j} \cdot g(n - 1 - j, x)$$

这样我们就得到了 $O(n^2)$ 状态，$O(n)$ 转移，时间复杂度是 $O(n^3)$。其实这样优化是把两个 $x$ 合并在一起算了。

注意到最终算的是权值和，要除以 $1\times 3\times ...\times (2n-1)=(2n-1)!!$。

------------

以上部分公式来自 tourist 题解，膜拜 tourist。

---

## 作者：yyyyxh (赞：8)

拒绝当口胡型选手。

首先原题过程发现有点难以维护，考虑直接对最终的括号串进行 DP。

我们将同一次操作插入的两个字符串匹配，在最终的括号串中发现这也是一个”括号串“的结构。

假设对于一个最终串，我们同时 DP 出了它的字符状态和匹配状态，那么原问题的结果应当是插入这些匹配的顺序乘这种方案数。

注意这些匹配是不能随便插入的，如 $\texttt{)()(}$，第一个字符和第四个字符构成的匹配必须比中间的匹配先插入。

这些匹配是一个树形结构，那么插入顺序的方案数相当于树形拓扑序方案数 $n!\prod_{i=1}^n \frac{1}{size_i}$，将 $\frac{1}{size_i}$ 放入 DP 中统计即可。

具体怎么 DP：考虑每次在首尾加入一对 $\texttt{)(}$ 或 $\texttt{()}$，对于中间那段括号串的影响相当于将其前缀和折线整体上移/整体下移。

设 $g_{i,j}$ 表示长度为 $2i$ 的且首尾一定是一对匹配的括号串（不一定合法），其前缀和最小值为 $j$ 的方案数。

$f_{i,j}$ 表示若干个 $g_{i,j}$ 中的串拼起来，长度为 $2i$，前缀和最小值为 $j$ 的方案数。

前后加匹配：$\frac{pf_{i,x}}{i+1}\to g_{i+1,x+1}$ 和 $\frac{(1-p)f_{i,x}}{i+1}\to g_{i+1,x-1}$

拼接两个串的转移： $f_{i,x}g_{j,y}\to f_{i+j,\min(x,y)}$，前缀和优化一下。

最后别忘了除以总方案变成概率以及乘上 $n!$。

总复杂度 $O(n^3)$。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=(x<<1)+(x<<3)+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
const int N=503,P=998244353;
typedef long long ll;
int qp(int a,int b=P-2){
	int res=1;
	while(b){
		if(b&1) res=(ll)res*a%P;
		a=(ll)a*a%P;b>>=1;
	}
	return res;
}
int f[N][N],g[N][N],dp[N][N],h[N],inv[N];
int n,p;
void inc(int &x,int v){if((x+=v)>=P) x-=P;}
int pref[N][N],preg[N][N],res[N];
void convol(int t){
	for(int i=0;i<=t;++i)
		for(int j=0;j<=t;++j){
			pref[i][j]=f[i][j];
			preg[i][j]=g[i][j];
			if(j){
				inc(pref[i][j],pref[i][j-1]);
				inc(preg[i][j],preg[i][j-1]);
			}
		}
	for(int i=0;i<t;++i)
		for(int j=0;j<=t;++j){
			inc(f[t][j],(ll)pref[i][j]*g[t-i][j]%P);
			if(j) inc(f[t][j],(ll)preg[t-i][j-1]*f[i][j]%P);
		}
}
int main(){
	n=read();p=(ll)read()*qp(10000)%P;inv[1]=1;
	for(int i=2;i<=n;++i) inv[i]=(ll)inv[P%i]*(P-P/i)%P;
	int res=1;
	f[0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<i;++j){
			inc(g[i][max(j-1,0)],(ll)f[i-1][j]*p%P*inv[i]%P);//()
			inc(g[i][j+1],(ll)f[i-1][j]*(P+1-p)%P*inv[i]%P);//)(
		}
		convol(i);
		res=(ll)res*i%P*qp(i+i-1)%P;
	}
	res=(ll)res*f[n][0]%P;
	printf("%d\n",res);
	return 0;
}
```


---

## 作者：qweradf (赞：7)

c++14 怎么这么慢 /qd/qd/qd

[link](https://www.luogu.com.cn/problem/CF1781F)

先不考虑每次插入的是 `()` 还是 `)(`，只考虑插入的两个字符在最终串中的位置。一共有 $(2n-1)!!$ 种方案。

将 `(` 视为 $1$，`)` 视为 $-1$，最终得到的一个括号串合法的充要条件是其最小前缀和 $\geq 0$。

我们考虑最终串的第一个字符，它必须是 `(`，与它对应的字符必须是 `)`。剩下的限制有：这两个括号之间的子串的最大前缀和应 $\geq -1$；右括号右边的子串最大前缀和应 $\geq 0$。

对于两个括号间子串的子问题，同样考虑第一个字符以及它对应的字符，这时它们可以是 `()` 或 `)(`。如果是 `()`，则这两个括号间的子串最大前缀和 $\geq -2$；否则最大前缀和 $\geq 0$。

这启发我们进行 DP。令 $f_{i,j}$ 表示：长度为 $2i$ 的串，所有 $(2i-1)!!$ 种插入方案中，每种方案最大前缀和 $\geq -j$ 的概率之总和。

转移：

$$f_{i,j} = p \cdot \sum_{k=0}^{i-1} f_{k,j+1} \cdot f_{i-1-k,j} \cdot \binom i{k+1}+[j>0] \cdot (1-p) \cdot \sum_{k=0}^{i-1} f_{k,j-1} \cdot f_{i-1-k,j} \cdot \binom i{k+1}$$

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
const ll N=505,P=998244353;
ll qpow(ll x,ll y=P-2){ll z=1;while(y){if(y&1)z=z*x%P;x=x*x%P,y>>=1;}return z;}
ll n,p,f[N][N],fac[N],inv[N];
ll C(ll n,ll m){return fac[n]*inv[m]%P*inv[n-m]%P;}
int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	ll i,j,k;
	cin>>n>>p,p=p*796898467%P;
	fac[0]=inv[0]=1;for(i=1;i<=n;i++) fac[i]=fac[i-1]*i%P,inv[i]=qpow(fac[i]);
	for(i=0;i<=n+1;i++) f[0][i]=1;
	for(i=1;i<=n;i++){
		f[i][n+1]=1;
		for(j=0;j<=n;j++){
			for(k=0;k<=i-1;k++) (f[i][j]+=p*f[k][j+1]%P*f[i-1-k][j]%P*C(i,k+1))%=P;
			if(j) for(k=0;k<=i-1;k++) (f[i][j]+=(P+1-p)*f[k][j-1]%P*f[i-1-k][j]%P*C(i,k+1))%=P;
		}
	}
	ll ans=1;
	for(i=1;i<=2*n;i+=2) ans=ans*i%P;
	ans=qpow(ans);
	cout<<ans*f[n][0]%P<<'\n';
	return 0;
}
```

---

## 作者：zzzYheng (赞：3)

#### 题意：

有一个字符串 $S$，初始为空。

执行 $n$ 次操作，每次随机选取一个空位（总共长度加 $1$ 个空位），并以 $p$ 的概率插入一个 `()`，以 $(1-p)$ 的概率插入一个 `)(`。

问最终 $S$ 为合法括号串的概率。

数据范围：$n \le 500$。

#### 思路：

首先把括号串转为折线。（起点为 $(0,0)$，`(` 看作向右上走一步，`)` 看作向右下走一步。括号串合法等价于终点在 $x$ 轴上且行走过程中没有走到过 $x$ 轴下方）

插入 `()` 相当于在折线上插入一个 `^`，插入 `)(` 相当于在折线上插入一个 `v`。

考虑折线上每个点的纵坐标，继而又可以将题意转化为：有一个序列 $a$，初始为 $\{0\}$，每次随机选一个 $a_i$，$p$ 的概率将其变为 $a_i,a_i+1,a_i$，$1-p$ 的概率将其变为 $a_i,a_i-1,a_i$。问最终所有数都 $\ge 0$ 的概率。

观察发现将 $a_i$ 变成 $a_i,a_i\pm 1,a_i$ 后，这三个数之后的变化是相对独立的，只在分配操作的时候不独立。

但是操作的分配和操作过程无关，我们可以先将操作次数分配掉。令 $f_{i,j,k}$ 表示对初始为 $\{x,y,z\}$ 的序列操作 $i+j+k$ 次，$x$ 变成的序列恰好操作 $i$ 次，$y$ 变成的序列恰好操作 $j$ 次，$z$ 变成的序列恰好操作 $k$ 次的概率。容易做到 $\Theta(n^3)$。

因此可以考虑 dp 解决这个问题，令 $g_{i,j}$ 表示序列初始为 $\{j\}$，操作 $i$ 次后每个数都 $\ge 0$ 的概率。

操作一次后序列变成 $3$ 个数，枚举最终对这 $3$ 个数变成的序列各操作了多少次，然后就变成 $3$ 个独立的子问题了。

因此得到转移：
$$
g_{i,j}=\sum_{x+y+z=i-1} f_{x,y,z} \cdot (p\cdot g_{x,j}\cdot g_{y,j+1}\cdot g_{z,j}+(1-p)\cdot g_{x,j}\cdot g_{y,j - 1}\cdot g_{z,j})
$$
直接枚举可以做到 $\Theta(n^4)$。

怎么优化，考虑 $a_i$ 变成 $a_i,a_i\pm 1,a_i$ 后，两个 $a_i,a_i$ 的变化是相似的，因此考虑一起处理。

令 $h_{i,j}$ 表示序列初始为 $\{j,j\}$，操作 $i$ 次后每个数都 $\ge 0$ 的概率。

求 $h_{i,j}$ 只需枚举两个 $j$ 各分配了多少次操作，而求出 $h$ 后求 $g_{i,j}$ 就只需枚举 $j\pm 1$ 和 $\{j,j\}$ 各分配了多少次操作即可。

这样可以做到时间复杂度 $\Theta(n^3)$。

---

## 作者：OtterZ (赞：2)

~~复习一下官解~~
# 题意
$n$ 次操作，每次操作在随机一个空插入 `()` 或 `)(`，问产生合法括号序列的概率。
# 随机选位置转为指定位置
我们可以发现第 $i$ 次选位置每个位置被选中几率总是 $\frac{1}{2 \times i - 1}$，我们可以把 $\prod \frac{1}{2 \times i - 1}$ 提出，这样我们把这道题转化成了指定位置的题。
# 转化
我们把 `(` 转为 $1$，把 `)` 转为 $-1$，将括号序列转化为差分序列，我们进行一次操作，对修改前与修改后的序列进行对比得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/fs0ki6p0.png)

我们的修改相当于选一个数 $[x]$，操作:

- 加入 `()`：$[x] -> [x,x + 1,x]$;
- 加入 `)(`：$[x] -> [x,x - 1,x]$。

这样就方便进行动态规划了。
# 转移

设 $f_{x,y}$ 为经过 $x$ 次操作后 $y$ 不出现负数的贡献。得到：

1. $f_{0,x} = 1,\forall x \ge 0$;
1. $[x] -> [x,x + 1,x]$：$p \times f_{i,x} \times f_{j,x + 1} \times f_{n - 1 - i - j,x} \times (^{n - 1}_{j}) \times (^{n - 1 - j}_{i}) \rarr f_{n,x}$;
2. $[x] -> [x,x - 1,x]$：$(1 - p) \times f_{i,x} \times f_{j,x - 1} \times f_{n - 1 - i - j,x} \times (^{n - 1}_{j}) \times (^{n - 1 - j}_{i}) \rarr f_{n,x}$。

这样我们得到了 $\operatorname{O}(n^4)$ 做法。我们预处理 $g_{n - 1 - j,x} = \sum \{f_{i,x} \times f_{n - 1 - i - j,x} \times (^{n - 1 - j}_{i})\}$ 可以优化成 $\operatorname{O}(n^3)$ 并解决此题，答案为 $f_{n,0} \times\prod \frac{1}{2 \times i - 1}$。

# 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,p,inv[10009],f[509][509],g[509][509],s[509],ni[509],sp = 1;
constexpr int mod = 998244353;
int c(int x,int y){
	if(x < y)
		return 0;
	else
		return 1ll * s[x] * ni[y] % mod * ni[x - y] % mod;
}
int main(){
	scanf("%d %d",&n,&p);
	inv[1] = 1;
	for(int i = 2; i <= 10000; i ++){
		inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	//	printf("%d\n",inv[i]);
	}
	p = 1ll * p * inv[10000] % mod;
	for(int i = 0; i <= n; i ++){
		f[0][i] = g[0][i] = 1;
	}
	s[0] = ni[0] = 1;
	for(int i = 1; i <= n; i ++){
		s[i] = 1ll * i * s[i - 1] % mod;
		ni[i] = 1ll * inv[i] * ni[i - 1] % mod;
	}
	for(int i = 1; i <= n; i ++){
		sp = 1ll * sp * inv[2 * i - 1] % mod;
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 0; j <= n; j ++){
			for(int k = 0; k < i; k ++){
				f[i][j] = (f[i][j] + 1ll * p * c(i - 1,k) % mod * g[i - 1 - k][j] % mod * f[k][j + 1] % mod) % mod;
				if(j > 0)
					f[i][j] = (f[i][j] + 1ll * (mod + 1 - p) * c(i - 1,k) % mod * g[i - 1 - k][j] % mod * f[k][j - 1] % mod) % mod;
			}
		//	printf("%d %d %d\n",i,j,f[i][j]);
			for(int k = 0; k <= i; k ++){
				g[i][j] = (g[i][j] + 1ll * c(i,k) * f[k][j] % mod * f[i - k][j] % mod) % mod;
			}
		}
	}
	printf("%d\n",1ll * f[n][0] * sp % mod); 
}
```

---

## 作者：do_it_tomorrow (赞：2)

见过很多次但是都没有切掉的题目。

显然通过题目的方式生成括号序列的方案数有 $\prod\limits_{i=1}^n 2i-1$ 种，考虑 DP 求出方案数然后最后再除以所有的方案数。

假设 $\texttt{(}$ 是 $1$，$\texttt{)}$ 是 $-1$ 那么容易想到一个合法的括号序列的充要条件就是前缀和恒不小于 $0$ 而且以 $0$ 结尾。

如果我们在某一个括号序列后面添加 $\texttt{()}$ 或者 $\texttt{)(}$，那么如果原本的前缀和为 $x$ 添加后就会多出 $x+1,x$ 或者 $x-1,x$。

考虑设状态 $f_{i,j}$ 表示经过 $i$ 次操作之后初始的前缀和为 $j$ 的方案数。

那么对于插入 $\texttt{()}$，有转移：

$$f_{n,x}\gets f_{n,x}+\sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{n-1}p \dbinom{n-1}{i} \dbinom{n-i-1}{j} f_{i,x}\cdot f_{j,x+1}\cdot f_{n-i-j-1,x}$$

对于插入 $\texttt{)(}$，有转移：

$$f_{n,x}\gets f_{n,x}+\sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{n-1}(1-p) \dbinom{n-1}{i} \dbinom{n-i-1}{j} f_{i,x}\cdot f_{j,x-1}\cdot f_{n-i-j-1,x}$$

其转移的思路是通过插入的 $2$ 个字符将整个字符串拆分为 $3$ 个部分，分别是第 $1$ 个字符之前、两个字符中间和第 $2$ 个字符之后。

因为题目只要求在最后合法，所以插入的顺序可以随意发挥，所以方案数需要乘上组合数。

把和 $j$ 有关的从上面的式子中提出来，得到：


$$f_{n,x}=\sum\limits_{j=0}^{n-1}\dbinom{n-1}{j}\cdot\left[p\cdot f_{j,x+1}+(1-p)\cdot f_{j,x-1}\right]\cdot \sum\limits_{i=0}^{n-j-1}\dbinom{n-j-1}{i}\cdot f_{i,x}\cdot f_{n-i-j-1,x}$$

那么把后面的依托提前预处理出来，最后输出的时候除以总共的方案数就行了，时间复杂度为 $O(n^3)$。

---

## 作者：eastcloud (赞：2)

题目要求我们对合法的随机过程计数，而合法条件是括号串合法，考虑以此为特征进行求解。

括号串计数的一个经典方法是区间 dp，每次要么将当前区间劈成两半要么把最外层的括号去掉，但是此题的随机过程中的串不一定合法，于是我们尝试能不能找到一些类似的特征对其做相似的划分。

注意到我们上面说的 dp 过程其实是在找第一个括号的匹配，然后根据这个匹配划分子问题，虽然在这个问题中第一个括号不一定有合法匹配，但是第一个括号仍然会有唯一一个和它一起加进来的括号，不妨把这一对当成一对匹配进行计数。

第一个括号和一起加进来的括号会把整个串切割成两部分，左边这部分必须在这个括号加进来之后加入，右边则没有限制，枚举左半边括号长度，乘个组合数合并即可。

但是我们还没有考虑对于括号串必须要合法的限制，不过可以直接加一维表示目前所有前缀左括号个数减右括号个数最小值的绝对值的最大值（很拗口，但是大概就是前面还要加多少个左括号），相当于表示当前合不合法。

设长度为 $i$，前面还要多加小于等于 $j$ 个左括号才可能合法的串中能被生成的串有 $f_{i,j}$ 个（注意这里不是种，因为不同的生成方式可能对应相同的一个串，把“恰好”改为“至少“是为了方便转移），初值为 $f_{0,j}=1$。

- 当插入的是 $\text{()}$ 时，有转移：
$$f_{i,j}\leftarrow\sum_{k=0}^{i-1} \binom{i}{k+1}p\cdot f_{k,j+1} \cdot f_{i-k-1,j} $$

- 插入 $\text{)(}$ 时则是：

$$f_{i,j}\leftarrow [j\neq 0]\sum_{k=0}^{i-1} \binom{i}{k+1}p\cdot f_{k,j-1} \cdot f_{i-k-1,j}$$

思路在于枚举 $k$ 表示分割后前半部分的长度，然后乘上组合数表示这 $k+1$ 次（包括第一个括号这次）是在哪些时刻被加进来的，时间复杂度 $O(n^3)$，可以 NTT 优化到 $O(n^2 \log n)$，但是没啥必要。

---

## 作者：WilliamFranklin (赞：2)

**Hint:**  

- 将 `(` 看作 $+1$，`)` 看作 $-1$，找出符合题意的一个合法括号序列的充要条件。

- 考虑前缀和的性质，并在括号序列中插入 `()` 和 `)(` 都分别代表什么，有何特殊之处。

**Tutorial:**

首先将 `(` 看作 $+1$，将 `)` 看作 $-1$，则一个序列合法即为每一个前缀和的值都非负。

再发现若在 $i$ 的位置（此时第 $i$ 的前缀和为 $x$）后面插入一个 `()`，则就相当于在前缀和数组中插入 $x + 1, x$ 两个数，插入 `)(`，则就相当于在前缀和数组中插入 $x - 1,x$ 两个数。所以容易发现这和序列每个元素的位置也无关。

那么将问题就可以转化成：一开始有一个集合（可重集） $S\{0\}$，每一次都可以选择一个 $x(x\in S)$，然后向集合中以 $p$ 的概率插入 $x + 1, x$ 两个数，以 $1 - p$ 的概率插入 $x - 1, x$ 两个数，求最后执行 $n$ 次后，集合中所有元素都非负的概率。

考虑设 $f_{i,j}$ 表示在 $j$ 这个数后插入 $i$ 次操作后合法的概率。那么我们考虑先执行一次操作，则一共用三个位置可以执行剩下的操作，这三个为位置分别是（红色的代表当前的这个 $j$）：$\color{red}{j}$ $,\ \Delta,\ j \pm 1,\ \Delta,\ j,\ \Delta$，此时设第一个位置执行 $a$ 次，第二个位置执行 $b$ 次，第三个位置执行 $c$ 次，且必须要满足 $a + b + c = i - 1$，那么就有如下的转移方程：

$$f_{i,j}=\sum_{a = 0}^{i - 1}{\sum_{b = 0}^{i - 1 - a}{(p \cdot f_{b, j + 1} + (1 - p) \cdot f_{b, j - 1}) \cdot \binom{i - 1}{a} \cdot \binom{i - a - 1}{b} \cdot f_{a, j} \cdot f_{i - a - b, j}}}$$

但容易发现这个的时间复杂度是 $O(n^4)$ 的。

考虑优化。我们发现 $i - a - b = c$，那么我们可以考虑枚举 $a, c$ 而不是 $a, b$，那么转移方程就变为：

$$f_{i,j}=\sum_{a = 0}^{i - 1}{\sum_{c = 0}^{i - 1 - a}{(p \cdot f_{i - a - c, j + 1} + (1 - p) \cdot f_{i - a - c, j - 1}) \cdot \binom{i - 1}{a} \cdot \binom{i - a - 1}{c} \cdot f_{a, j} \cdot f_{c, j}}}$$

考虑 $a, c$ 在这个式子中所承担的角色就是 $\binom{i - 1}{a} \cdot \binom{i - a - 1}{c} \cdot f_{a, j} \cdot f_{c, j}$ 和 $a + c$，那么设 $d = a + c$，且设 $g_{i, j}$：

$$g_{i, j} = \sum_{k = 0}^{i}{\binom{i}{k} \cdot f_{k, j} \cdot f_{i - k, j}}$$

那么我们就可以得到如下式子：

$$f_{i,j}=\sum_{d = 0}^{i - 1}{(p \cdot f_{i - d, j + 1} + (1 - p) \cdot f_{i - d, j - 1}) \cdot \binom{i - 1}{d} \cdot g_{d, j}}$$

那么这样我们就可以做到 $O(n^3)$ 了。

**Solution:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 705, mod = 998244353;
long long f[N][N];
long long g[N][N];
long long fac[N], ifac[N];
int n;
long long x, y;
long long quickpow(long long a, long long b, long long mod) {
	long long res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
long long C(long long x, long long y) {
	return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> x >> y;
	fac[0] = 1;
	For(i, 1, n) fac[i] = fac[i - 1] * i % mod;
	For(i, 0, n) ifac[i] = quickpow(fac[i], mod - 2, mod);
	long long iny = quickpow(y, mod - 2, mod);
	f[0][0] = 1;
	long long p = x * iny % mod;
	long long q = (1 - p + mod) % mod;
	For(i, 0, n) f[0][i] = g[0][i] = 1;
	For(i, 1, n) {
		For(j, 0, n - i) {
			For(k, 0, i - 1) {
				f[i][j] = (f[i][j] + (p * f[k][j + 1] % mod + q * f[k][j - 1] % mod) % mod * g[i - 1 - k][j] % mod * C(i - 1, k) % mod) % mod;
			}
		}
		For(j, 0, n) {
			For(k, 0, i) {
				g[i][j] = (g[i][j] + C(i, k) * f[k][j] % mod * f[i - k][j] % mod) % mod;
			}
		}
	}
	long long ans = f[n][0];
	for (int i = 1; i <= 2 * n; i += 2) {
		ans = ans * quickpow(i, mod - 2, mod) % mod;
	}
	cout << ans;
	return 0;
} 
```

---

## 作者：Purslane (赞：1)

# Solution

好玩的题目。感觉要把控好概率和期望的关系。

首先观察题目两种插入符号是在干什么。插入 `()` 永远不会改变括号合法与否，但是插入 `)(` 可能会让合法的括号变得不合法，当且仅当在插入位置的前面已经是匹配的括号串的时候不合法。

于是考虑用 $\pm 1$ 序列来刻画括号串是否匹配。那么再值 $x$ 后面插入 `()` 相当于用 $\{x,x+1,x\}$ 来替换它；插入 `)(` 相当于用 $\{x
,x-1,x\}$ 来替换它。

那么一个自然的想法就是记录一下目前长度为 $|S|+1$ 的序列中有多少等于 $0$ 的数。不过这样会很不科学，因为你得记录当前有多少个 $1$，否则你无法搞明白多少种情况下会给序列新增 $0$；你还得记录当前有多少个 $2$。（这样有点 DP 套 DP 的感觉，但是状态数太多不合理）。

那么考虑我们把 $x$ 变成三个数之后，事实上它们之间的操作是独立的（我们最后不是求有多少种合法的括号串，而是求出所有的 $1 \times 3 \times \cdots \times (2n-1)$ 种插入空格的方式中，每种方式最后合法的概率之和）。这样的好处是如果你只考虑一个数操作 $n$ 次依旧合法的概率，你再合并多种独立的状态的时候，并不能直接求概率的平均数，因为从古典概型的角度来考虑，将不同的操作次数分配给这三个数之后，不同情况的样本空间大小是不一样的，会很麻烦。

于是可以想到一个非常简单的 DP：设 $dp_{n,k}$ 为将 $k$ 从一个数开始进行 $n$ 次操作，最终得到的 $1 \times 3 \times \cdots \times (2n-1)$ 种插入方式中，每种的最终变成合法括号串的概率。

很容易写出转移式：

$$
dp_{n,k} = \sum_{l=0}^{n-1} \sum_{r=0}^{n-1-l} p\binom{n-1}{l+r}\binom{l+r}{l} dp_{l,k}dp_{r,k}dp_{n-1-l-r,k+1} + \sum_{l=0}^{n-1} \sum_{r=0}^{n-1-l} (1-p)\binom{n-1}{l+r}\binom{l+r}{l} dp_{l,k}dp_{r,k}dp_{n-1-l-r,k-1} 
$$

这个转移是 $O(n^4)$ 的。不过一眼就容易发现一个卷积：当 $l+r$ 为定值的时候，$\sum \dbinom{l+r}{l} dp_{l,k} dp_{r,k}$。这个可以用 $O(n^3)$ 快速计算，同时把 DP 优化为 $O(n^3)$ 的。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=500+10,MOD=998244353;
int n,p,g[MAXN][MAXN],dp[MAXN][MAXN],C[MAXN][MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>p,p=p*qpow(10000,MOD-2)%MOD;
	C[0][0]=1;
	ffor(i,1,n) {C[i][0]=1;ffor(j,1,n) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;}
	ffor(i,0,n) dp[0][i]=1,g[0][i]=1;
	ffor(i,1,n) {
		ffor(j,0,n) {
			ffor(x,0,i-1) dp[i][j]=(dp[i][j]+p*C[i-1][x]%MOD*g[x][j]%MOD*dp[i-1-x][j+1])%MOD;
			if(j) ffor(x,0,i-1) dp[i][j]=(dp[i][j]+(1-p)*C[i-1][x]%MOD*g[x][j]%MOD*dp[i-1-x][j-1])%MOD;
		}
		ffor(j,0,n) ffor(x,0,i) g[i][j]=(g[i][j]+dp[x][j]*dp[i-x][j]%MOD*C[i][x])%MOD;
	}
	int res=dp[n][0];
	ffor(i,1,n) res=res*qpow(2*i-1,MOD-2)%MOD;
	cout<<(res+MOD)%MOD;
	return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

某机构模拟赛 T3。

先考虑计数，问题变为填 `()` 权值乘 $p$，填 `)(` 权值乘 $1-p$，问权值和。

首先，发现若一个串最后是合法的，则在操作过程中也一定合法。

考虑把 `(` 当成 $1$，`)` 当成 $-1$，使用前缀和描述括号序列。

此时在值为 $x$ 的元素后面加 `()` 等价于加上 $x+1,x$，加 `)(` 等价于加上 $x-1,x$。

因为抛去了概率，我们可以认为操作间是独立的，设 $f_{n,v}$ 表示对于一个数 $v$，进行 $n$ 次操作的答案。

转移时先分讨填 `()` 还是 `)(`，在把剩余的 $n-1$ 次操作分给三个数即可，可以得到转移式：

$$f_{n,v}=\sum\limits_{i+j+k=n-1}p\binom{n-1}{i,j,k}f_{i,v}f_{j,v}f_{k,v+1}+\sum\limits_{i+j+k=n-1}(1-p)\binom{n-1}{i,j,k}f_{i,v}f_{j,v}f_{k,v-1}$$

此时暴力做是 $O(n^4)$，需要优化。

转化一下右边，得：

$$\begin{aligned}
& \sum\limits_{i+j+k=n-1}p\binom{n-1}{i,j,k}f_{i,v}f_{j,v}f_{k,v+1}+\sum\limits_{i+j+k=n-1}(1-p)\binom{n-1}{i,j,k}f_{i,v}f_{j,v}f_{k,v-1}
\\&=\sum\limits_{i+j+k=n-1}\binom{n-1}{i,j,k}f_{i,v}f_{j,v}(pf_{k,v+1}+(1-p)f_{k,v-1})
\\&=(n-1)!\sum_{k=0}^{n-1}\dfrac{pf_{k,v+1}+(1-p)f_{k,v-1}}{k!}\sum\limits_{i+j=n-1-k}\dfrac{f_{i,v}f_{j,v}}{i!j!}
\end{aligned}$$

可以使用辅助数组 $g_{n,v}$ 表示 $\sum\limits_{i+j=n}\dfrac{f_{i,v}f_{j,v}}{i!j!}$，在求 $f$ 的时候维护 $g$ 就可以做到 $O(n^3)$。

答案是 $f_{n,0}$，但要转化为期望，故要除总方案数 $\prod\limits_{i=1}^{n}(2i-1)=(2i-1)!!$。

代码：


```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define bi __int128_t
#define lb(x) ((x)&(-(x)))
#define gp(i,j) (((i)>>(j-1))&1)
#define ppc __builtin_popcount
using namespace std;
const int N=550,mod=998244353;
const ll inf=1e18+10;
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;};
void Sub(int &a,int b){a-=b;if(a<0) a+=mod;}
void Mul(int &a,int b){a=1ll*a*b%mod;}
int qp(int a,int b){
    int x=1;
    while(b){
        if(b&1) Mul(x,a);
        Mul(a,a);b>>=1;
    }return x;
}
int f[N][N],g[N][N],fac[N<<1],inv[N<<1];
int n,p;
int main(){
    cin>>n>>p;p=1ll*p*qp(10000,mod-2)%mod;
    int fp=(mod+1-p)%mod;fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    for(int i=0;i<=n;i++) inv[i]=qp(fac[i],mod-2);
    for(int i=0;i<=n;i++) f[0][i]=1,g[0][i]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=i-1;k++){
                int sum=0;
                if(j!=n) Add(sum,1ll*f[k][j+1]*p%mod);
                if(j!=0) Add(sum,1ll*f[k][j-1]*fp%mod);
                Add(f[i][j],1ll*sum*g[i-1-k][j]%mod*inv[k]%mod);
                //cout<<i<<' '<<j<<' '<<k<<' '<<f[i][j]<<' '<<sum<<endl;
            }Mul(f[i][j],fac[i-1]);
            //cout<<i<<' '<<j<<' '<<f[i][j]<<endl;
            for(int k=0;k<=i;k++){
                Add(g[i][j],1ll*f[k][j]*f[i-k][j]
                %mod*inv[k]%mod*inv[i-k]%mod);
                //cout<<i<<' '<<j<<' '<<k<<' '<<f[k][j]<<' '<<f[i-k][j]<<' '<<inv[i-k]<<endl;
            }//cout<<i<<' '<<j<<' '<<g[i][j]<<endl;
        }
    }int ans=f[n][0];
    for(int i=1;i<=n;i++){
        Mul(ans,qp(2*i-1,mod-2));
    }cout<<ans<<endl;
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 前言

一开始不会，看了题解的状态设计之后，想了好久（大概几个小时）才大概想明白。不愧是 tourist 的神题！Orz

## 题解

不难发现总方案数是 $\prod_{i=1}^{n}(2i-1)$。所以我们只需要求方案数，然后除以这个就是概率。

首先可以把括号转成 $+1$ 和 $-1$，然后求一个前缀和。我们就让这个前缀和的前缀 $\min=0$ 即可。

考虑区间 DP。我们发现仅仅按套路存储 $l,r,0/1$（左端点、右端点、转移是加一层还是切割）是不够的，所以考虑把前缀 $\min$ 放进去。

然后考虑转移：

如果添加 `()`，那么相当于把 $x$ 变成了 $x,x+1,x$；如果添加 `)(`，相当于把 $x$ 变成了 $x,x-1,x$。

我们对于每个区间，考虑两种转移：

- 如果是两边拼起来，那么我们枚举分界点，计算两边的 DP 值乘起来。但是还需要乘上一个 $\binom{r-l+1}{i-l+1}$，因为两边是任意的，可以在区间内任选 $i-l+1$ 个位置，以子序列的形式插入。

- 如果是外面加一层，那么直接分 `()` 和 `)(` 转移就好了。

转移方程：

$$\begin{cases}dp_{l,r,x,0}=p \cdot (dp_{l+1,r-1,x-1,0}+dp_{l+1,r-1,x-1,1})+(1-p) \cdot (dp_{l+1,r-1,x+1,0}+dp_{l+1,r-1,x+1,1})\\dp_{l,r,x,1}=\sum_{i=l}^{r-1}\sum_{y=x}^{r-l+1}\dbinom{r-l+1}{i-l+1}\cdot \left[dp_{l,i,x,0} \cdot (dp_{i+1,r,y,0}+dp_{i+1,r,y,1})+dp_{l,i,y,0} \cdot (dp_{i+1,r,x,0}+dp_{i+1,r,x,1})\right]\end{cases}$$

乍一看暴力做是 $O(n^5)$ 的。查表转移不好优化，因此改成刷表，然后就变成枚举 $x,y$ 之后对 $\min
\{x,y\}$ 做贡献，使用前缀和优化即可，这样就是 $O(n^4)$ 了。

考虑进一步优化，观察到我们的 DP 只和区间长度有关，所以把前两维压成一维，转移的枚举用组合数代替。

$f_{i,x,0/1}$ 表示长度为 $2i$（操作 $i$ 次），前缀 $\min$ 为 $x$，最后一步是添加 / 合并而来的括号序列的方案数。不难发现 $f_{i,x,p}=\sum\limits_{r-l+1=i}dp_{l,r,x,p}$。

转移和上面是类似的，复杂度 $O(n^4)$。同样的，考虑优化这个方程。

不难发现，令 $f_{i,j,k}$ 为 $dp_{i,j,k}$ 在 $j$ 这一维上的前缀和。我们显然可以根据上面的方程求出对于任意一个 $j$，前缀 $\min \geq j$ 的方案数 $G_{j}$：

$$G_j=\binom{i}{j} \cdot [f_{j,x,0} \cdot (f_{i-j,x,0}+f_{i-j,x,1})-f_{j,x-1,0} \cdot (f_{i-j,x-1,0}+f_{i-j,x-1,1})]$$

我们需要的是前缀 $\min$ 恰好为 $j$ 的情况，那么我们直接拿 $G_j-G_{j-1}$ 求出即可。最后，注意 $x=0$ 的时候不能有非法转移。

[Code & Submission](https://codeforces.com/contest/1781/submission/225758221)

---

