# [PKUWC2018] Slay the Spire

## 题目描述

九条可怜在玩一个很好玩的策略游戏：Slay the Spire，一开始九条可怜的卡组里有 $2n$ 张牌，每张牌上都写着一个数字$w_i$，一共有两种类型的牌，每种类型各 $n$ 张：

1. 攻击牌：打出后对对方造成等于牌上的数字的伤害。

2. 强化牌：打出后，假设该强化牌上的数字为 $x$，则其他剩下的**攻击牌**的数字都会乘上 $x$。**保证强化牌上的数字都大于 1**。

现在九条可怜会等概率随机从卡组中抽出 $m$ 张牌，由于费用限制，九条可怜最多打出 $k$ 张牌，假设九条可怜永远都会采取能造成最多伤害的策略，求她期望造成多少伤害。

假设答案为 $\text{ans}$ ，你只需要输出

$$\left (\text{ans}\times \frac{(2n)!}{m!(2n-m)!}\right) ~\bmod 998244353$$

即可。其中 $x!$ 表示 $\prod_{i=1}^{x}i$，特别地，$0!=1$ 。


## 说明/提示

#### 样例解释
例如九条可怜抽到了攻击牌 $\{1,2\}$ 和强化牌 $\{3\}$，那最优策略是先用掉强化牌 $3$，此时攻击牌的数值变成 $\{3,6\}$，然后打出 $6$。


#### 数据范围

对于所有数据，有 $1\leq k\leq m\leq 2n\leq 3000$，且$1\leq w_i\leq 10^8$。

**保证强化牌上的数字都大于 1**。

以下 $(\sum 2n)$ 表示对于输入中所有数据的$2n$的和。

对于 $10\%$ 的数据，有 $1\leq \sum 2n\leq 10$

对于 $20\%$ 的数据，有 $1\leq \sum 2n\leq 100$

对于 $30\%$ 的数据，有 $1\leq \sum 2n\leq 500$

另有 $20\%$ 的数据，满足所有攻击牌的数值相同。

另有 $20\%$ 的数据，满足 $m=k$。

对于 $100\%$ 的数据，有 $1\leq \sum 2n\leq 30000$


## 样例 #1

### 输入

```
2
2 3 2
2 3
1 2
10 16 14
2 3 4 5 6 7 8 9 10 11
1 2 3 4 5 6 7 8 9 10```

### 输出

```
19
253973805```

# 题解

## 作者：TheLostWeak (赞：19)

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/Luogu5299.html)

**大致题意：** 有$n$张强化牌$a_i$和$n$张攻击牌$b_i$，每张牌有一个权值（强化牌的权值大于$1$），每张强化牌能使所有攻击牌的权值乘上这张强化牌的权值，每张攻击牌造成的伤害等于这张攻击牌的权值。现在，以等概率抽出$m$张牌，并以最优策略使用其中至多$k$张牌造成最大的伤害。求所有情况下，造成伤害总和。

### 何为最优策略

这道题看似毫无头绪，因此，我们先要好好推一推性质。

假设现在我们已经选好了$m$张牌，那么最优策略是什么？

首先，如果我们已经确定要用$x$张强化牌和$y$张攻击牌，那么根据贪心的想法，肯定是先使用权值最大的$x$张强化牌，再使用权值最大的$y$张攻击牌。

因此我们把$a$和$b$分别**从大到小**排序。

同时，同样依据贪心，我们可以知道答案就是**强化牌的乘积**乘上**攻击牌之和**。

然后我们考虑，在什么情况下，把第$y$张攻击牌换成第$x+1$张强化牌，与原先答案相比不会变劣。

原先答案是：

$$\prod_{i=1}^xa_i\cdot\sum_{i=1}^y b_i$$

变化后的答案是：

$$\prod_{i=1}^{x+1}a_i\cdot\sum_{i=1}^{y-1}b_i$$

则两式相减，即为答案的变化量，也就是：

$$(a_{x+1}-1)\cdot(\prod_{i=1}^xa_i\cdot\sum_{i=1}^{y-1}b_i)-(\prod_{i=1}^xa_i)\cdot b_y$$

当变化后答案不变劣，说明变化量$\ge 0$，即：

$$(a_{x+1}-1)\cdot(\prod_{i=1}^xa_i\cdot\sum_{i=1}^{y-1}b_i)\ge(\prod_{i=1}^xa_i)\cdot b_y$$

我们把式子中的$\prod_{i=1}^xa_i$去掉，就得到：

$$(a_{x+1}-1)\cdot(\sum_{i=1}^{y-1}b_i)\ge b_y$$

由于题目中说明，强化牌权值大于$1$，所以$a_{x+1}-1\ge 1$。

而在$y>1$时，因为$b$数组经过了从大到小排序，所以$\sum_{i=1}^{y-1}b_i$肯定大于等于$b_y$。

所以我们可以发现，在$y>1$时，$(a_{x+1}-1)\cdot(\sum_{i=1}^{y-1}b_i)\ge b_y$是始终成立的。

也就是说，**在保有至少一张攻击牌的前提下，肯定是尽量选择强化牌会更优**。

这么一来，这道题一下就可做得多了。

### 预处理

在正式开始解题之前，我们还需要进行预处理，定义几个变量。

设$f_{i,j,0}$表示**在前$i$张强化牌中选择$j$张**且**第$i$张被选中**的所有情况下，**这$j$张牌的乘积之和**，$g_{i,j,0}$表示**在前$i$张攻击牌中选择$j$张**且**第$i$张被选中**的所有情况下，**这$j$张牌的和之和**。

同时，定义$f_{i,j,1}=\sum_{x=1}^if_{x,j,0},g_{i,j,1}=\sum_{x=1}^ig_{x,j,0}$来辅助转移。

则不难发现，有转移方程：

$$f_{i,j,0}=a_i\cdot f_{i-1,j-1,1}$$

$$f_{i,j,1}=f_{i,j,0}+f_{i-1,j,1}$$

$$g_{i,j,0}=b_i\cdot C_{i-1,j-1}+g_{i-1,j-1,1}$$

$$g_{i,j,1}=g_{i,j,0}+g_{i-1,j,1}$$

注意，$g_{i,j,0}$的转移中，$C_{i-1,j-1}$表示在$i-1$个数中选择$j-1$个数的方案，即从$g_{i-1,j-1,1}$转移到$g_{i,j,0}$共有$C_{i-1,j-1}$种情况，而每种情况卡牌权值和加上了$b_i$，就相当于共加上了$b_i\cdot C_{i-1,j-1}$。

至于这些东西究竟有什么用，待会儿你就会知道了。

### 组合数学

接下来，就是分类讨论+推式子啦。

**第一类：当$m$张牌中，强化牌的数量小于$k-1$张时。**

此时必然是选上所有的强化牌，然后选上权值最大的一些攻击牌。

不难发现，其实等于$k-1$张时也符合这一类情况的操作方案，但为了方便起见，我们把等于$k-1$的情况放入另一类情况中中。

对于这一种情况，我们枚举$i,j$分别表示**强化牌有$i$张**和**最后被选中的攻击牌是第$j$张**。

在强化牌中选择$i$张的所有合法情况下的乘积之和，其实就是$f_{n,i,1}$。

而强化牌中选择$i$张，攻击牌中就要选择$k-i$张，又由于最后被选中的攻击牌是第$j$张，所以所有合法情况下攻击牌的和之和，其实就是$g_{j,k-i,0}$。

而若要最终选出的$k$张牌是这$k$张牌，就剩余$m-k$张牌就需要满足：

- 不存在强化牌。
- 所有攻击牌都必须在第$j$张之后，否则选这张攻击牌肯定比选第$j$张优。

因此方案数就是$C_{n-j}^{m-k}$。

总结一下，就是枚举$i,j$，然后每次答案加上$f_{n,i,1}\cdot g_{j,k-i,0}\cdot C_{n-j}^{m-k}$。

**第二类：当$m$张强化牌中，强化牌的数量大于等于$k-1$时。**

此时必然是选上权值最大的$k-1$张强化牌，然后选上权值最大的一张攻击牌。

对于这一种情况，我们枚举$i,j$分别表示**最后被选中的强化牌是第$i$张**和**被选中的攻击牌是第$j$张**。

在前$i$张强化牌中选择$k-1$张，且第$i$张必选，所有合法情况下的乘积之和，其实就是$f_{i,k-1,0}$。

选择第$j$张攻击牌，攻击牌之和其实就是第$j$张攻击牌的权值，也就是$b_j$。

而若要最终选出的$k$张牌是这$k$张牌，就剩余$m-k$张牌就需要满足：

- 所有强化牌都必须在第$i$张之后。
- 所有攻击牌都必须在第$j$张之后。

因此方案数就是$C_{2n-i-j}^{m-k}$。

总结一下，就是枚举$i,j$，然后每次答案加上$f_{i,k-1,0}\cdot b_j\cdot C_{2n-i-j}^{m-k}$。

具体实现可见代码。

### 代码

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define Reg register
#define RI Reg int
#define Con const
#define CI Con int&
#define I inline
#define W while
#define N 6000
#define X 998244353
using namespace std;
int n,m,k,a[N+5],b[N+5],C[N+5][N+5],f[N+5][N+5][2],g[N+5][N+5][2];
I bool cmp(CI x,CI y) {return x>y;}
int main()
{
	RI i,j;for(C[0][0]=i=1;i<=N;++i) for(C[i][0]=j=1;j<=i;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%X;//预处理组合数
	RI Tt,ans;scanf("%d",&Tt);W(Tt--)
	{
		for(scanf("%d%d%d",&n,&m,&k),ans=0,i=1;i<=n;++i) scanf("%d",a+i);
		for(i=1;i<=n;++i) scanf("%d",b+i);sort(a+1,a+n+1,cmp),sort(b+1,b+n+1,cmp);//从大到小排序
		for(f[0][0][0]=f[0][0][1]=i=1;i<=n;++i) for(f[i][0][1]=j=1;j<=i;++j)//预处理f
			f[i][j][0]=1LL*a[i]*f[i-1][j-1][1]%X,f[i][j][1]=(f[i][j][0]+f[i-1][j][1])%X;
		for(i=1;i<=n;++i) for(j=1;j<=i;++j)//预处理g
			g[i][j][0]=(1LL*b[i]*C[i-1][j-1]+g[i-1][j-1][1])%X,g[i][j][1]=(g[i][j][0]+g[i-1][j][1])%X;
		for(i=0;i<k-1;++i) for(j=1;j<=n;++j) ans=(1LL*f[n][i][1]*g[j][k-i][0]%X*C[n-j][m-k]+ans)%X;//当强化牌数量小于k-1时
		for(i=0;i<=n;++i) for(j=1;j<=n;++j) ans=(1LL*f[i][k-1][0]*b[j]%X*C[2*n-i-j][m-k]+ans)%X;//当强化拍数量大于等于k-1时
		printf("%d\n",ans);//输出答案
	}return 0;
}
```



---

## 作者：asuldb (赞：7)

[题目](https://www.luogu.org/problemnew/show/P5299)

我竟然能做出九老师的组合计数题，尽管这题很呆

我们先考虑一个简单的问题，如果给定你要选出来的$m$张卡牌，如何做到攻击伤害最高

非常显然，因为保证了强化牌上的数字大于$1$，所以我们优先选择那些强化牌，毕竟最小的一张只能翻两倍的强化牌都要比选择攻击牌好；选完强化牌之后剩下的攻击牌自然是越大越好

当然了，我们也不可能选出$k$张强化牌来，这样什么伤害都造不成，所以如果强化牌数量大于$k$，我们就选择前$k-1$大的强化牌，配上最大的攻击牌

我们发现给定的强化牌和攻击牌都是无序的，我们先排序再说

之后我们就可以大力$dp$了

设$dp_{i,j}$表示前$i$张强化牌里选出$j$张所有强化牌乘积的和，$f_{i,j}$表示前$i$张强化牌里选择了$j$张且第$i$张一定被选择的乘积和

显然有转移

$$dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-1}\times a_i$$

$$f_{i,j}=dp_{i-1,j-1}\times a_i$$

攻击牌这边我们设$h_{i,j}$表示前$i$张攻击牌里选择了$j$张的所有方案的和，$g_{i,j}$表示强迫选择第$i$张

也有转移

$$h_{i,j}=h_{i-1,j}+h_{i-1,j-1}+C_{i-1}^{j-1}\times b_i$$

$$g_{i,j}=h_{i-1,j-1}+C_{i-1}^{j-1}\times b_i$$

现在我们考虑枚举选择了多少张强化牌

设选择了$i$张强化牌，自然也就需要选择$m-i$张攻击牌

如果$i<k$，那么这些强化牌都是要直接用的，选择的$m-i$张攻击牌里能被用于打出的$k$张的也就只有$k-i$张，而剩下的$m-i-(k-i)=m-k$张牌我们在后面随便选一下

于是答案就是

$$\sum_{j=0}^nf_{j,i}\times \sum_{j=0}^ng_{j,k-i}C_{n-j}^{m-k}$$

如果$i>=k$，那么我们也只能选择$k-1$张强化牌，剩下的多选出来的$i-k+1$张我们还是从后面的位置里选出来，实际上需要的攻击牌也就只有$1$张，需要额外多选的攻击牌也就只有$m-i-1$张

答案就是

$$\sum_{j=0}^nf_{j,k-1} C_{n-j}^{i-k+1}\times  \sum_{j=0}^ng_{j,1}C_{n-j}^{m-i-1}$$

代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define re register
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
inline int read() {
	char c=getchar();int x=0;while(c<'0'||x>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
const int mod=998244353;
const int maxn=3005;
int c[maxn][maxn];
int dp[maxn][maxn],f[maxn][maxn];
int g[maxn][maxn],h[maxn][maxn];
int T,n,m,k;
int a[maxn],b[maxn];
inline int C(int n,int m) {if(m>n) return 0;return c[n][m];}
inline int cmp(int A,int B) {return A>B;}
int main() {
	T=read();int M=maxn-5;
	for(re int i=0;i<=M;i++) c[i][0]=c[i][i]=1;
	for(re int i=1;i<=M;i++)
		for(re int j=1;j<i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	while(T--) {
		n=read(),m=read(),k=read();
		for(re int i=1;i<=n;i++) a[i]=read();
		for(re int i=1;i<=n;i++) b[i]=read();
		std::sort(a+1,a+n+1,cmp);std::sort(b+1,b+n+1,cmp);
		dp[0][0]=1;
		for(re int i=1;i<=n;i++)
			for(re int j=0;j<=i;j++) {
				dp[i][j]=dp[i-1][j];
				if(j) dp[i][j]=(dp[i][j]+1ll*dp[i-1][j-1]*a[i]%mod)%mod;
			}
		f[0][0]=1;
		for(re int i=1;i<=n;i++) 
			for(re int j=1;j<=i;j++) 
				f[i][j]=1ll*dp[i-1][j-1]*a[i]%mod;
		h[0][0]=0;
		for(re int i=1;i<=n;i++)
			for(re int j=0;j<=i;j++) {
				h[i][j]=h[i-1][j];
				if(j) h[i][j]=(h[i][j]+1ll*C(i-1,j-1)*b[i]%mod+h[i-1][j-1])%mod;
			}
		for(re int i=1;i<=n;i++)
			for(re int j=1;j<=i;j++)
				g[i][j]=(1ll*C(i-1,j-1)*b[i]%mod+h[i-1][j-1])%mod;
		int ans=0;
		for(re int i=0;i<m;i++) {
			int now=0;
			for(re int j=0;j<=n;j++) {
				if(i<=k-1) now=(now+f[j][i])%mod;
					else now=(now+1ll*f[j][k-1]*C(n-j,i-k+1)%mod)%mod;
			}
			int tot=0,res=0;
			if(i<=k-1) res=k-i;else res=1;
			for(re int j=0;j<=n;j++) 
				tot=(tot+1ll*g[j][res]*C(n-j,m-i-res)%mod)%mod;
			ans=(ans+1ll*now*tot%mod)%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：ViXbob (赞：6)

[滋磁去我的博客看吖](https://www.vixbob-lwc.pw/2019/04/26/plan-of-pratice/)

考虑一个性质: 在保证能选一张攻击牌的情况下, 剩下的选择强化牌一定比选择攻击牌更优. 

证明: 因为每张强化牌的权值大于$\text{1}$, 并且被选出的攻击牌一定是最大的, 所以将已选出的攻击牌的和翻倍一定比再选一张攻击牌优.

知道上述性质, 我们将攻击牌和强化牌都降序排序, 就可以直接$\text{dp}$了.

设$p[i]$为第$i$张强化牌上的数值, $w[i]$为第$i$张攻击牌上的数值

设$\text{f[i][j][0/1]}$表示考虑了前$\text{i}$张牌**选了**$\text{j}$张牌第$\text{i}$张牌有没有用的所有方案的乘积和

设$\text{g[i][j][0/1]}$表示考虑了前$\text{i}$张牌**用了**$\text{j}$张牌第 $\text{i}$ 张牌有没有用的所有方案的和

很显然我们不会用超过$k-1$张强化牌但是我们会选超过$k-1$张强化牌, 所以对于$j \le k-1$的情况有转移:
$$\begin{aligned}f[i][j][0] \leftarrow& f[i-1][j][0]+f[i-1][j][1]\\f[i][j][1]\leftarrow& (f[i-1][j-1][0]+f[i-1][j-1][1])\times p[i]\end{aligned}$$
对于$j \ge k$的情况, 设$F[i][j]$表示考虑前$i$张选了$j$张强化牌用了$k-1$张的所有方案的乘积的和, 则有转移:
$$\begin{aligned}F[i][j] \leftarrow F[i-1][j] + f[i][k-1][1] \times \binom{n - i}{j - k + 1}\end{aligned}$$
对于$g$有转移:
$$\begin{aligned}g[i][j][0]\leftarrow& g[i-1][j][0]+g[i-1][j][1]\\g[i][j][1]\leftarrow& g[i-1][j-1][0]+g[i-1][j-1][1]+\binom{i-1}{j-1}\times w[i]\end{aligned}$$
最后我们枚举一下选了多少张强化牌, 就可以直接计算答案了

代码:

```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define dep(i, j, k) for(int i = j; i >= k; --i)
#define SIZE(x) (int)(x.size())
#define sqr(x) ((double)(x) * (x))
#define inv(x) (ksm(x, P - 2))

typedef long long ll;

using namespace std;

const int maxn = 3e3 + 15;
const int P = 998244353;

int n, m, k, T, f[maxn][maxn][2], fac[maxn], ifac[maxn], p[maxn], w[maxn], g[maxn][maxn][2], ans;
int F[maxn], G[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) { if(ch == '-') f = -1; ch = getchar(); }
	while(isdigit(ch))  { u = u * 10 + ch - 48; ch = getchar(); } return u * f;
}

inline int pls(int x, int y) { x += y; return x >= P ? x - P : x; }
inline int dec(int x, int y) { x -= y; return x < 0 ? x + P : x; }
inline int mul(int x, int y) { return 1ll * x * y % P; }
inline int mul(int a, int b, int c) { return 1ll * a * b % P * c % P; }
inline int mul(int a, int b, int c, int d) { return 1ll * a * b % P * c % P * d % P; }
inline int ksm(int x, int k, int rnt = 1) {
	for(int i = k; i; i >>= 1, x = mul(x, x)) if(i & 1) rnt = mul(rnt, x);
	return rnt;
}
inline int C(int n, int m) { return n >= m ? mul(fac[n], ifac[m], ifac[n - m]) : 0; }

int main() {
	T = read(); fac[0] = 1;
	rep(i, 1, maxn - 1) fac[i] = mul(fac[i - 1], i);
	ifac[maxn - 1] = inv(fac[maxn - 1]);
	dep(i, maxn - 2, 0) ifac[i] = mul(ifac[i + 1], i + 1);
	while(T--) {
		n = read(); m = read(); k = read(); ans = 0;
		rep(i, 1, n) p[i] = read();
		rep(i, 1, n) w[i] = read();
		sort(p + 1, p + 1 + n, greater<int>());
		sort(w + 1, w + 1 + n, greater<int>());
		memset(F, 0, sizeof(F)); memset(f, 0, sizeof(f));
		memset(G, 0, sizeof(G)); memset(g, 0, sizeof(g));
		f[0][0][0] = 1;
		rep(i, 1, n) {
			f[i][0][0] = 1;
			rep(j, 1, min(k, i)) {
				f[i][j][0] = pls(f[i - 1][j][0], f[i - 1][j][1]);
				f[i][j][1] = mul(p[i], pls(f[i - 1][j - 1][0], f[i - 1][j - 1][1]));
				g[i][j][0] = pls(g[i - 1][j][0], g[i - 1][j][1]);
				g[i][j][1] = pls(pls(g[i - 1][j - 1][0], g[i - 1][j - 1][1]), mul(C(i - 1, j - 1), w[i]));
			}
			if(i >= k - 1)
				rep(j, k, min(m, n)) F[j] = pls(F[j], mul(f[i][k - 1][1], C(n - i, j - k + 1)));
		}
		rep(i, 0, k - 1) F[i] = pls(f[n][i][0], f[n][i][1]);
		if(k == 1) rep(i, 0, m) F[i] = C(n, i);
//		rep(i, 0, m) cerr << "F[" << i << "] = " << F[i] << endl;
//		rep(i, 0, m) cerr << "G[" << i << "] = " << G[i] << endl;
		rep(i, 0, m) {
			int Gi = k - min(k - 1, i), tot = m - i;
			if(tot > n) continue;
			int p = 0;
			rep(j, 1, n) p = pls(p, mul(g[j][Gi][1], C(n - j, tot - Gi)));
			ans = pls(ans, mul(p, F[i]));
		}
		cout << ans << endl;
	}
	return 0;
}
/*
*/
```

---

## 作者：Resurgammm (赞：3)

假期望，计数题。

不难想到一个很显然的贪心策略是尽可能的将所有的强化牌打出，然后从大到小走脸攻击牌。

所以把将强化牌和攻击牌先从小到大排序。

设 $F_{i,j}$ 为选出的 $m$ 张牌里有 $i$ 张是强化牌，打出 $j$ 张强化牌时所有方案的倍率和，$G_{i,j}$ 为选出的 $m$ 张牌里有 $i$ 张是攻击牌，打出 $j$ 张攻击牌时所有方案的伤害和。

那么根据上面提到的贪心，枚举打出强化牌的个数进行分类讨论：

* $i<k-1:ans\gets ans+F_{i,i}\times G_{m-i,k-i}$

* $i\geq k-1:ans\gets ans+F_{i,k-1}\times G_{m-i,1}$

考虑如何求出 $F,G$

设 $f_{i,j}$ 为选了 $i$ 张强化牌，最后一张是第 $j$ 张强化牌的倍率和，$g_{i,j}$ 为选了 $i$ 张攻击牌，最后一张是第 $j$ 张攻击牌的伤害和。

不难想到转移式子：

$$\begin{cases}f_{i,j}=\sum\limits_{k=j+1}^{n}f_{i-1,k}\times up_j \\ g_{i,j}=\sum\limits_{k=j+1}^{n}g_{i-1,k}+atk_j\times \binom{n-j}{i-1}\end{cases}$$

注意 $up,atk$ 都是排好序的。

这样转移是 $O(n^3)$ 的，用前缀和可以优化到 $O(n^2)$。

对于 $F_{i,j}$ ，需要满足的是打出的最小的牌一定比不打出的最大的牌还要大，所以枚举打出的牌中最小的牌的排名 $k$，然后乘上 $\binom{k-1}{i-j}$ 即可。

$G$ 和 $F$ 同理。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
#define int long long
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout)
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		if(x<0) putchar('-'),x=-x;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(x,y,sizeof(y))
	
	const int maxn=3e3+5,mod=998244353;
	
	int T,n,m,k,ans;
	int atk[maxn],up[maxn],f[maxn][maxn],g[maxn][maxn],sum[maxn][maxn],C[maxn][maxn];
	inline void init(){
		for(int i=0;i<maxn;i++){
			C[i][0]=1;
			for(int j=1;j<=i;j++)
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	inline int F(int x,int y){
		if(x<y) return 0;
		if(!y) return C[n][x];
		int res=0;
		for(int i=x-y+1;i<=n-y+1;i++) res=(res+f[y][i]*C[i-1][x-y]%mod)%mod;		
		return res;
	}
	inline int G(int x,int y){
		if(x<y) return 0;
		if(!y) return C[n][x];
		int res=0;
		for(int i=x-y+1;i<=n-y+1;i++) res=(res+g[y][i]*C[i-1][x-y]%mod)%mod;
		return res;
	}	
	inline void reset(){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) f[i][j]=g[i][j]=0;
		ans=0;
	}
	
	inline int main(){
		T=read(); init();
		while(T--){
			n=read(); m=read(); k=read();
			for(int i=1;i<=n;i++) up[i]=read();
			for(int i=1;i<=n;i++) atk[i]=read();
			sort(up+1,up+1+n); sort(atk+1,atk+1+n);
			for(int i=1;i<=n;i++)
				f[1][i]=up[i],sum[1][i]=(sum[1][i-1]+up[i])%mod;
			for(int i=2;i<=n;i++){
				for(int j=1;j<=n-i+1;j++)
					f[i][j]=(sum[i-1][n]-sum[i-1][j]+mod)%mod*up[j]%mod;
				for(int j=1;j<=n;j++)
					sum[i][j]=(sum[i][j-1]+f[i][j])%mod;	
			}
			for(int i=1;i<=n;i++)
				g[1][i]=atk[i],sum[1][i]=(sum[1][i-1]+atk[i])%mod;
			for(int i=2;i<=n;i++){
				for(int j=1;j<=n-i+1;j++)
					g[i][j]=((sum[i-1][n]-sum[i-1][j]+mod)%mod+atk[j]*C[n-j][i-1]%mod)%mod;
				for(int j=1;j<=n;j++)
					sum[i][j]=(sum[i][j-1]+g[i][j])%mod;
			}
			for(int i=0;i<=m;i++){
				if(i<k-1) ans=(ans+F(i,i)*G(m-i,k-i)%mod)%mod;
				else ans=(ans+F(i,k-1)*G(m-i,1)%mod)%mod;
			}
			printf("%lld\n",ans); reset();
		}
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：yqaty (赞：3)

假设我们选择了 $i$ 张强化牌， $m-i$ 张攻击牌，若 $i < k$ 则我们便先使用 $i$ 张强化牌，再使用最大的 $k-i$ 张攻击牌即可，若 $i \geq k$，则先使用最大的 $k-1$ 张强化牌，再使用最大的一张攻击牌，很明显这样的决策是最优的。

所以我们最优策略下，分别求出选 $i$ 张强化牌的强化值总和，$i$ 张攻击牌的攻击值总和，两两相乘即可。

先将数组从大到小排序。

设 $f_{i,j}$ 表示在前 $i$ 张强化值牌中，随机选择 $j$ 张，所取得的最大强化值之和。当 $j < k-1$ 时，第 $i$ 张牌加入要算上其贡献， $j \geq k$ 时，第 $i$ 张牌加入不计算其贡献，所以转移为：

$$f_{i,j} = f_{i-1,j-1} \cdot a_i + f_{i-1,j},j < k$$
$$f_{i,j} = f_{i-1,j-1} + f_{i-1,j},j \geq k$$

设 $g_i$ 表示选择了 $i$ 张攻击牌所得的最大攻击值之和，
所以我们选择了 $m-i$ 张强化牌，根据之前的结论，我们需要使用的攻击牌数量为 $num = \min(k,\max(1,k-m+i))$，我们考虑枚举第 $num$ 张牌，设 $j$ 为第 $num$ 张牌，则前面 $j-1$ 张我们要选 $num-1$ 张，后面 $n-j$ 张我们要选 $i-num$ 张，前 $num-1$ 张的期望为 $\frac{num-1}{j-1}\sum\limits_{k=1}^{j-1} b_k$，以及加上必须选的第 $j$ 张牌，所以：

$$g_i = \sum\limits_{j=num}^{n} C^{num-1}_{j-1}C^{n-j}_{i-num} (b_j + \frac{num-1}{j-1}\sum\limits_{k=1}^{j-1} b_k)$$

最终 $ans = \sum\limits_{i=1}^{m} f_{n,m-i} \cdot g_{i}$。

```cpp
#include<bits/stdc++.h>
#define IL inline 
#define LL long long
using namespace std;
const int N=3e3+3,p=998244353;
int n,m,k,a[N],b[N],fac[N],ifac[N],inv[N],f[N][N],g[N],pre[N],ans;
IL int in(){
	char c;int f=1;
	while((c=getchar())<'0'||c>'9')
	  if(c=='-') f=-1;
	int x=c-'0';
	while((c=getchar())>='0'&&c<='9')
	  x=x*10+c-'0';
	return x*f;
}
IL int mod(int x){return x>=p?x-p:x;}
IL int ksm(int a,int b){
	int c=1;
	while(b){
		if(b&1) c=1ll*c*a%p;
		a=1ll*a*a%p,b>>=1;
	}
	return c;
}
IL void init(int n){
	fac[0]=1;for(int i=1;i<=n;++i) fac[i]=1ll*fac[i-1]*i%p;
	ifac[n]=ksm(fac[n],p-2);for(int i=n;i;--i) ifac[i-1]=1ll*ifac[i]*i%p;
	inv[1]=1;for(int i=2;i<=n;++i) inv[i]=1ll*(p-p/i)*inv[p%i]%p;
}
IL int C(int n,int m){if(n<m||m<0) return 0;return 1ll*fac[n]*ifac[m]%p*ifac[n-m]%p;}
void solve(){
	n=in(),m=in(),k=in(),ans=0;
	for(int i=1;i<=n;++i) a[i]=in();
	for(int i=1;i<=n;++i) b[i]=in();
	int res=0;
	sort(a+1,a+n+1,greater<int>()),
	sort(b+1,b+n+1,greater<int>());
	for(int i=1;i<=n;++i) pre[i]=mod(pre[i-1]+b[i]);
	memset(g,0,sizeof(g));
	for(int i=0;i<=n;++i) f[i][0]=1;
	for(int i=1;i<=n;++i)
	  for(int j=1;j<k;++j)
	  	f[i][j]=mod(1ll*f[i-1][j-1]*a[i]%p+f[i-1][j]);    
	for(int i=k;i<=n;++i)
	  for(int j=k;j<=min(m,i);++j)
	    f[i][j]=mod(f[i-1][j-1]+f[i-1][j]);
	for(int i=1;i<=min(n,m);++i){
		int num=min(k,max(1,k-m+i));g[i]=0;
		for(int j=num;j<=n;++j)
			g[i]=mod(g[i]+1ll*C(j-1,num-1)*C(n-j,i-num)%p*mod(b[j]+1ll*pre[j-1]*(num-1)%p*inv[j-1]%p)%p);
	}
	for(int i=max(1,m-n);i<=min(n,m);++i) ans=mod(ans+1ll*f[n][m-i]*g[i]%p);
	printf("%d\n",ans);
}
int main()
{
	init(3e3);
	int T=in();
	while(T--) solve();
	return 0;
}
```


---

## 作者：lhm_ (赞：1)

先考虑有 $m$ 张牌，打 $k$ 张的最优策略。发现强化牌的效果至少是翻倍，所以最优策略一定是在至少打出一张攻击牌的前提下，尽可能的多打强化牌，强化牌数量不够时，再由大到小打攻击牌。

设 $F_{i,j}$ 为选出 $i$ 张强化牌，打出 $j$ 张的效果， $G_{i,j}$ 为选出 $i$ 张攻击牌，打出 $j$ 张的效果，根据最优策略，枚举选出强化牌的个数，得答案为：
$$
\large\begin{aligned}
 ans&=\sum_{i=\max(m-n,0)}^{\min(n,m)} val_i \\
\\
 val_i &= 
\begin{cases}
F_{i,i}G_{m-i,k-i} &i < k \\
\\
F_{i,k-1}G_{m-i,1}  & i \geqslant k \\
\end{cases}
\end{aligned}
$$
发现直接求 $F,G$ 不好求，因为最优策略一定是先打权值大的牌，所以先将两种牌从大到小排序，设 $f_{i,j}$ 为考虑了排序后的前 $i$ 张强化牌且第 $i$ 张必选，选了 $j$ 张牌的效果，$g_{i,j}$ 为考虑了排序后的前 $i$ 张攻击牌且第 $i$ 张必选，选了 $j$ 张牌的效果，得：
$$
\large\begin{aligned}
	f_{i,j}&=v_i\sum_{k=j-1}^{i-1} f_{k,j-1} \\
	
	g_{i,j}&=\binom{i-1}{j-1}v_i + \sum_{k=j-1}^{i-1} g_{k,j-1}
\end{aligned}
$$
乘上组合数的原因是考虑转移过来的方案数，这里可以前缀和优化为 $O(n^2)$。然后考虑 $f,g$ 对 $F,G$ 的贡献，得：
$$
\large\begin{aligned}
	F_{i,j} = \sum_{k=j}^n \binom{n-k}{i-j}  f_{k,j} \\
	
	G_{i,j} = \sum_{k=j}^n \binom{n-k}{i-j}  g_{k,j} \\	
\end{aligned}
$$
直接计算 $F,G$ 是 $O(n^3)$ 的，但通过 $f,g$ 计算，需要哪个算哪个，复杂度就是 $O(n^2)$ 了。

```cpp
#include<bits/stdc++.h>
#define maxn 3010
#define all 3000
#define p 998244353
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int T,n,m,k;
ll v1[maxn],v2[maxn],s1[maxn],s2[maxn],f[maxn][maxn],g[maxn][maxn],fac[maxn],ifac[maxn];
bool cmp(const ll &a,const ll &b)
{
    return a>b;
}
ll inv(ll x)
{
    ll y=p-2,v=1;
    while(y)
    {
        if(y&1) v=v*x%p;
        x=x*x%p,y>>=1;
    }
    return v;
}
void init()
{
    fac[0]=ifac[0]=1;
    for(int i=1;i<=all;++i) fac[i]=fac[i-1]*i%p;
    ifac[all]=inv(fac[all]);
    for(int i=all-1;i;--i) ifac[i]=ifac[i+1]*(i+1)%p;
}
ll C(int n,int m)
{
    if(n<m) return 0;
    return fac[n]*ifac[n-m]%p*ifac[m]%p;
}
ll F(int i,int j)
{
    ll v=0;
    for(int k=j;k<=n;++k)
        v=(v+C(n-k,i-j)*f[k][j]%p)%p;
    return v;
}
ll G(int i,int j)
{
    ll v=0;
    for(int k=j;k<=n;++k)
        v=(v+C(n-k,i-j)*g[k][j]%p)%p;
    return v;
}
ll solve()
{
    read(n),read(m),read(k);
    for(int i=1;i<=n;++i) read(v1[i]);
    for(int i=1;i<=n;++i) read(v2[i]);
    sort(v1+1,v1+n+1,cmp),sort(v2+1,v2+n+1,cmp);
    f[0][0]=1,memset(s1,0,sizeof(s1)),memset(s2,0,sizeof(s2));
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=i;++j)
        {
            s1[j-1]=(s1[j-1]+f[i-1][j-1])%p,f[i][j]=v1[i]*s1[j-1]%p;
            s2[j-1]=(s2[j-1]+g[i-1][j-1])%p,g[i][j]=(C(i-1,j-1)*v2[i]%p+s2[j-1])%p;
        }
    }
    ll ans=0;
    for(int i=max(m-n,0);i<=min(n,m);++i)
    {
        if(i<k) ans=(ans+F(i,i)*G(m-i,k-i)%p)%p;
        else ans=(ans+F(i,k-1)*G(m-i,1)%p)%p;
    }
    return ans;
}
int main()
{
    init(),read(T);
    while(T--) printf("%lld\n",solve());
    return 0;
}
```

---

## 作者：_louhc (赞：1)

# 思路

首先,我们很容易想到一个贪心策略,就是在保证能用至少一张攻击牌的前提下,尽量多选强化牌.当然,要从大选到小. 因为强化牌至少能让伤害翻倍,而攻击牌顶多能让伤害翻倍.  

我们枚举强化牌选了几张,令 $f[i]$ 表示选 $i$ 张强化牌(其中用了 $\min\{i,K-1\}$ 张)所有方案翻的倍数之和,令 $g[i]$ 表示选 $i$ 张攻击牌(其中用了 $\max\{K-M+i,1\}$ 张)所有方案产生的攻击之和.那么最终答案就是 $\sum_{i=0}^M f[i]g[M-i]$.  

先对强化牌**从大到小**排序,第 $i$ 张记为 $w_1[i]$. 对于 $f[i]$ , 我们暂时把它看成 $f[i,j]$ ,也就是多一维表示当前处理到第 $i$ 张强化牌.  
如果选的强化牌不到 $K-1$ 张时,第 $i$ 张选了就得用,或者干脆不选, $f[i,j]=f[i-1,j-1]\times w_1[i]+f[i-1,j]$.  
如果选的强化牌不少于 $K-1$ 张时,第 $i$ 张选了也用不得,或者不选也没关系, $f[i,j]=f[i-1,j-1]+f[i-1,j]$.  
虽然没有必要,但是滚动数组可以滚到一维.  

对攻击牌**从小到大**排序,第 $i$ 张记为 $w_2[i]$. 对于 $g[i]$ , 我们也暂时看成 $g[i,j]$.  
如果选的攻击牌不多于 $M-K+1$ 张时,选的强化牌张数不少于 $K-1$ 张,也就是说攻击牌只能选 $1$ 张,用组合数计算一下第$w_2[i]$产生的贡献(显然,如果选了 $i$ 之后的攻击牌, $w_2[i]$ 就没有贡献了,所以只能在前 $i-1$ 里面选剩下的 $j-1$ 张牌),$g[i,j]=g[i-1,j]+w_2[i]\times\binom{i-1}{j-1}$.  
如果选的攻击牌多于 $M-K+1$ 张时,选的强化牌张数小于 $K-1$ 张,转移时除了 $w_i$ 产生的贡献以外(计算方法同上),还要加上之前 $i-1$ 张攻击牌产生的贡献,即 $g[i-1,j-1]$.  
这也可以滚动数组.

上面这个转移是怎么做到用的攻击牌数满足要求的呢?很明显当 $j\in[1,M-K+1]$ 时保证了只用一张.根据下面那个转移可以发现,对于 $j>M-K+1$ ,都是用了 $j-(M-K)$ 张,而此时强化牌用了 $M-j$ 张,加起来就是 $K$ 啦.


# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define i64 long long
#define f80 long double
#define rgt register
#define fp( i, b, e ) for ( int i(b), I(e); i <= I; ++i )
#define fd( i, b, e ) for ( int i(b), I(e); i >= I; --i )
#define go( i, b ) for ( int i(b), v(to[i]); i; v = to[i = nxt[i]] )
template<typename T> inline bool cmax( T &x, T y ){ return x < y ? x = y, 1 : 0; }
template<typename T> inline bool cmin( T &x, T y ){ return y < x ? x = y, 1 : 0; }
#define getchar() ( p1 == p2 && ( p1 = bf, p2 = bf + fread( bf, 1, 1 << 21, stdin ), p1 == p2 ) ? EOF : *p1++ )
char bf[1 << 21], *p1(bf), *p2(bf);
template<typename T>
inline void read( T &x ){ char t(getchar()), flg(0); x = 0;
	for ( ; !isdigit(t); t = getchar() ) flg = t == '-';
	for ( ; isdigit(t); t = getchar() ) x = x * 10 + ( t & 15 );
	flg ? x = -x : x;
}

const int _ = 1515, mod = 998244353;
int T, N, M, K, w1[_], w2[_], C[_][_];
int f[_], g[_];
inline int dec( int x ){ return x >= mod ? x - mod : x; }
inline bool cmp( int x, int y ){ return x > y; }

signed main(){
	read(T), C[0][0] = 1;
	fp( i, 1, 1500 ){
		C[i][0] = 1; fp( j, 1, 1500 ) C[i][j] = dec(C[i - 1][j - 1] + C[i - 1][j]);
	}
	while( T-- ){
		read(N), read(M), read(K);
		fp( i, 1, N ) read(w1[i]); fp( i, 1, N ) read(w2[i]);
		sort(w1 + 1, w1 + N + 1, cmp), sort(w2 + 1, w2 + N + 1);
		memset( f, 0, sizeof f ), memset( g, 0, sizeof g ), f[0] = 1;
		fp( i, 1, N ) fd( j, min(i, M - 1), 1 )
			f[j] = j < K ? (f[j] + (i64)f[j - 1] * w1[i]) % mod : dec(f[j] + f[j - 1]);
		fp( i, 1, N ) fd( j, min(i, M), 1 )
			g[j] = (g[j] + (i64)w2[i] * C[i - 1][j - 1] + (j > M - K + 1 ? g[j - 1] : 0)) % mod;
		int ans(0); fp( i, max(0, M - N), min(N, M) ) ans = (ans + (i64)f[i] * g[M - i]) % mod;
		printf( "%d\n", ans );
	}
	return 0;
}
```



---

## 作者：徐致远 (赞：1)


[本蒟蒻的Blog](https://www.chnxuzhiyuan.cn/2019/12/19/%E3%80%8CPKUWC2018%E3%80%8D%E9%A2%98%E8%A7%A3-Solution/)

### 题解

首先考虑一下，在抽到了$m$张牌之后，怎样打才比较优。

不难发现，肯定挑权值大的牌打，所有要打的攻击牌肯定都是在要打的强化牌打完之后才打的。

并且，由于强化牌上的数字最少为$2$，所以如果抽到的强化牌数量够多的话，一定会打出权值前$k-1$大的强化牌，然后再打出一张权值最大的攻击牌；如果抽到的强化牌数量比较少，那肯定会全部打出。

首先对两种牌的权值从大到小排序。

设权值第$i$大强化牌的权值为$p_i$，权值第$i$大的攻击牌的权值为$w_i$。

考虑两个DP：

- $F[i][j][0/1]$：表示考虑了前$i$张强化牌，打出了$j$张，第$i$张强化牌没打/打了时所有方案强化牌的乘积的和。
- $G[i][j][0/1]$：表示考虑了前$i$张攻击牌，打出了$j$张，第$i$张攻击牌没打/打了时所有方案攻击牌的加和的和。

不难推出转移方程：
$$
F[i][j][0]=F[i-1][j][0]+F[i-1][j][1]
$$
$$
F[i][j][1]=(F[i-1][j-1][0]+F[i-1][j-1][1])\cdot p[i]
$$
$$
G[i][j][0]=G[i-1][j][0]+G[i-1][j][1]
$$
$$
G[i][j][1]=G[i-1][j-1][0]+G[i-1][j-1][1]+\tbinom{i-1}{j-1}\cdot w[i]
$$

上述两个数组处理好之后，可以开始考虑计算答案了。

首先可以枚举一下抽中的牌中强化牌的数量，设共$i$张，分两种情况考虑：

1. $i<k$，那么这种情况对答案的贡献为:

$$
(\sum_{j=1}^{n}{F[j][i][1]})\cdot(\sum_{j=1}^{n}{G[j][k-i]\cdot \tbinom{n-j}{m-k}})
$$

2. $i\geq k$，此时的贡献为：

$$
(\sum_{j=1}^{n}{F[j][k-1][1]\cdot\tbinom{n-j}{i-k+1}})\cdot(\sum_{j=1}^{n}{G[j][1]\cdot \tbinom{n-j}{m-i-1}})
$$

累加起来即可得到答案。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=3005,TT=998244353;
int T,n,m,k,C[maxn][maxn],w[maxn],p[maxn],F[maxn][maxn][2],G[maxn][maxn][2],ans;
inline int read()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
int main()
{
	for(int i=0;i<=3000;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if(j==0) C[i][j]=1;
			else C[i][j]=(C[i-1][j-1]+C[i-1][j])%TT;
		}
	}
	T=read();
	while(T--)
	{
		n=read();m=read();k=read();ans=0;
		for(int i=0;i<=n;i++) F[i][0][0]=1;
		for(int i=1;i<=n;i++) p[i]=read();
		for(int i=1;i<=n;i++) w[i]=read();
		sort(w+1,w+1+n);reverse(w+1,w+1+n);
		sort(p+1,p+1+n);reverse(p+1,p+1+n);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=i;j++)
			{
				F[i][j][0]=F[i-1][j][0]+F[i-1][j][1];
				if(F[i][j][0]>=TT) F[i][j][0]-=TT;
				F[i][j][1]=((LL)F[i-1][j-1][0]+F[i-1][j-1][1])*p[i]%TT;
				G[i][j][0]=G[i-1][j][0]+G[i-1][j][1];
				if(G[i][j][0]>=TT) G[i][j][0]-=TT;
				G[i][j][1]=((LL)G[i-1][j-1][0]+G[i-1][j-1][1]+(LL)C[i-1][j-1]*w[i])%TT;
			}
		}
		for(int i=0;i<=m&&i<=n;i++)
		{
			int sum1=0,sum2=0;
			if(i<k)
			{
				for(int j=1;j<=n;j++)
				{
					sum1+=F[j][i][1];if(sum1>=TT) sum1-=TT;
					sum2=(sum2+(LL)G[j][k-i][1]*C[n-j][m-k])%TT;
				}
			}
			else
			{
				for(int j=1;j<=n;j++)
				{
					sum1=(sum1+(LL)F[j][k-1][1]*C[n-j][i-k+1])%TT;
					sum2=(sum2+(LL)G[j][1][1]*C[n-j][m-i-1])%TT;
				}
			}
			if(k==1||i==0) sum1=C[n][i];
			ans=(ans+(LL)sum1*sum2)%TT;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

## 

---

## 作者：541forever (赞：0)

首先，本题显然有个结论是说，如果强化牌足够，至多选一张攻击牌。因此，如果已知 $m$ 张牌，最优的策略是在选至少一张攻击牌的情况下，尽可能多选强化牌。不难想到将 $a,b$ 排序后 dp 处理出一些信息，设 $f_{i,j}$ 表示前 $i$ 张强化牌里选了 $j$ 张牌且选了第 $i$ 张牌的总贡献（即这 $j$ 张强化牌的积的和），$g_{i,j}$ 表示前 $i$ 张攻击牌里选了 $j$ 张且选了第 $i$ 张的总贡献（即选 $j$ 张攻击牌的和的和）。转移是容易的。即
$$f_{i,j}=a_i\times \sum_{k\le i} f_{k,j-1}$$

$$g_{i,j}=C_{i-1}^{j-1}\times b_i+\sum_{k\le i}g_{k,j-1}$$
接着，考虑如何计算答案，简单分讨一下，当强化牌不足 $k-1$ 张时，考虑枚举强化牌有 $i$ 张，最小的攻击牌是 $j$，对答案的贡献即为 $g_{j,k-i}\times C_{n-j}^{m-k}\times \sum_{u=0}^n f_{u,i}$，当强化牌有至少 $n-1$ 张时，枚举最小的强化牌是 $i$，最小的攻击牌为 $j$，对答案的贡献即为 $f_{i,k-1}\times b_j \times C_{2\times n-i-j}^{m-k}$。

[Code](https://www.luogu.com.cn/paste/2uq0c5t6)

---

## 作者：hzoi_zxb (赞：0)

首先，看到最后的式子乘上一个数，明显假期望，这是一道计数题。

题目要求选 m 张牌，打掉 k 张牌，并且是最优策略。这是本题的特色，也是突破口。考虑强化牌的系数大于 1，那么肯定是有多少打多少。如果大于 k 张就打 $k-1$ 张。至于攻击牌就是捡大的打就好。那么我们首先需要做的就是排序。

因为操作中涉及乘法和加法，这东西肯定要分开转移。

设计状态 $f_{i,j}$ 为攻击牌选了 i 张，排完序后最后一张是 j所有方案的总和。$g_{i,j}$ 为强化牌选了 i 张，排完序后最后一张是 j 所有方案乘积的总和。$num_{i,j}$ 表示与上面同样意义的情况下的方案数。

得到 DP 方程：
$$f_{i,j}=\sum_{k=1}^{j-1}{f_{i-1,k}+num_{i-1,k}\times val_j}$$

$$g_{i,j}=\sum_{k=1}^{j-1}{g_{i-1,k}\times w_j}$$

$$num_{i,j}=\sum_{k=1}^{j-1}{num_{i-1,k}}$$

这是三维的，复杂度太高，观察到有一堆求和，显然可以前缀和优化砍掉一维。

下一步我们考虑统计答案，按照我们上面的思路，我们需要枚举这 m 张牌强化牌选了多少张。分类讨论：

1. 选的牌数小于 k，那么这个时候是选多少打多少。

2. 选的牌数大于等于 k，这时打 $k-1$ 张。

接下来得把状态用上，选 i 张打 j 张的贡献：

$$ans=\sum_{l=1}^{n}{f_{j,l}\times C_{n-l}^{i-j}}$$

g 数组的贡献与其相同，这个组合数的意义很简单，就是当前是打了 j 张，最后一张在 l，然后对于没打的是在剩下的 $n-l$ 中选出 $i-j$ 张牌。

需要注意当 $k=1$ 时，强化牌的强化为 1，但是强化牌的组合是不止一个的，于是要乘上 $C_{n}^{i}$。





---

