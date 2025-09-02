# [HNOI2008] Cards

## 题目描述

小春现在很清闲，面对书桌上的 $n$ 张牌，他决定给每张牌染色，目前小春拥有 $3$ 种颜色：红色，蓝色，绿色。他询问 Sun 有多少种染色方案，Sun 很快就给出了答案。

进一步，小春要求染出 $S_r$ 张红色，$S_b$ 张蓝色，$S_g$ 张绿色。他又询问有多少种方案，Sun 想了一下，又给出了正确答案。最后小春发明了 $m$ 种不同的洗牌法，这里他又问 Sun 有多少种不同的染色方案。两种染色方法相同当且仅当其中一种可以通过任意的洗牌法（即可以使用多种洗牌法，而每种方法可以使用多次）洗成另一种。

Sun 发现这个问题有点难度，决定交给你，由于答案可能很大，你只需要求出答案对于 $P$ 取模的结果。 保证 $P$ 为一个质数。

## 说明/提示

有 $2$ 种本质上不同的染色法：`RGB` 和 `RBG`，使用洗牌法 `231` 一次，可得 `GBR` 和 `BGR`，使用洗牌法 `312` 一次，可得 `BRG` 和 `GRB`。


## 样例 #1

### 输入

```
1 1 1 2 7
2 3 1
3 1 2
```

### 输出

```
2
```

# 题解

## 作者：SGColin (赞：41)

因为任意置换的组合一定还在这个置换集合里，注意加上单位置换，此时给出的置换是一个置换群。可以直接上 Burnside 引理。

那么只需要考虑每个置换下的不动点。根据给出的置换很容易求出循环的个数。

考虑每一个循环，他们内部的位置的染色必须是相同的，所以单独考虑每个循环染那种颜色，可以通过一个类似背包的过程实现。

```c++
  f[0][0][0] = 1;
  for (rg int i = 1; i <= tot; ++i)
    for (rg int nr = r; ~nr; --nr)
      for (rg int nb = b; ~nb; --nb)
        for (rg int ng = g; ~ng; --ng) {
          if (nr >= sz[i]) f[nr][nb][ng] = (f[nr][nb][ng] + f[nr-sz[i]][nb][ng]) % mod;
          if (nb >= sz[i]) f[nr][nb][ng] = (f[nr][nb][ng] + f[nr][nb-sz[i]][ng]) % mod;
          if (ng >= sz[i]) f[nr][nb][ng] = (f[nr][nb][ng] + f[nr][nb][ng-sz[i]]) % mod;
        }
  return f[r][b][g];
```

即 $f[i][j][k]$ 表示三种颜色分别用了多少的方案数。

然后把每个置换的不动点数求和再乘上总置换数 $(m+1)$ 的逆元即可。

## Hack：注意 $\frac{(a+b+c)!}{a!b!c!(m+1)}$ 的公式是错的！

这个公式只考虑了单位置换下的不动点数，很容易被卡掉。

```c++
2 1 0 1 7
3 2 1
```

这组数据就可以卡掉了。

此数据单位置换下不动点有 RBR,RRB,BRR

给出置换下不动点有 RBR

根据 Burnside 引理答案为 $\frac{3+1}{2}=2$ ，而所谓公式得出结果为 $\frac{3}{2}$ ，甚至不是整数。

最后附上代码。

```C++
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 60
#define gc getchar
#define rg register
using namespace std;

inline int rd() {
  rg int x = 0;
  rg bool f = 0;
  rg char c = gc();
  while (!isdigit(c)) {
    if(c == '-') f = 1;
    c = gc();
  }
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48);
    c = gc();
  }
  return f ? -x : x;
}

bool vis[N];

int r, b, g, n, m, mod;

int ans, tr[N], sz[N], f[N][N][N];

inline int calc() {
  int tot = 0;
  for (rg int nr = r; ~nr; --nr)
      for (rg int nb = b; ~nb; --nb)
        for (rg int ng = g; ~ng; --ng) f[nr][nb][ng] = 0;
  for (rg int i = 1; i <= n; ++i) vis[i] = 0;
  for (rg int i = 1, p, len; i <= n; ++i)
    if (!vis[i]) {
      p = i; len = 0;
      while (!vis[p]){
        ++len; vis[p] = 1; p = tr[p];
      }
      sz[++tot] = len;
    }
  f[0][0][0] = 1;
  for (rg int i = 1; i <= tot; ++i)
    for (rg int nr = r; ~nr; --nr)
      for (rg int nb = b; ~nb; --nb)
        for (rg int ng = g; ~ng; --ng) {
          if (nr >= sz[i]) f[nr][nb][ng] = (f[nr][nb][ng] + f[nr-sz[i]][nb][ng]) % mod;
          if (nb >= sz[i]) f[nr][nb][ng] = (f[nr][nb][ng] + f[nr][nb-sz[i]][ng]) % mod;
          if (ng >= sz[i]) f[nr][nb][ng] = (f[nr][nb][ng] + f[nr][nb][ng-sz[i]]) % mod;
        }
  return f[r][b][g];
}

inline int qpow(int x, int t) {
  int res = 1;
  while (t) {
    if (t & 1) res = (res * x) % mod;
    x = (x * x) % mod; t >>= 1;
  }
  return res;
}

int main() {
  r = rd(); b = rd(); g = rd();
  n = r + b + g; m = rd(); mod = rd();
  for (rg int i = 1; i <= m; ++i) {
    for (rg int j = 1; j <= n; ++j) tr[j] = rd();
    ans = (ans + calc()) % mod;
  }
  for (rg int j = 1; j <= n; ++j) tr[j] = j;
  ans = (ans + calc()) % mod;
  printf("%d\n", ans * qpow(m + 1, mod - 2) % mod);
  return 0;
}

```


---

## 作者：dovely_seele (赞：11)

Burnside 经典老题，怎么感觉好多题解写的是错的啊？

题目里的“保证任意多次洗牌都可用这 $m$ 种洗牌法中的一种代替，且对每种洗牌法，都存在一种洗牌法使得能回到原状态。”这句话有点绕。其实前者意思就是题目给出的置换不管怎么复合，结果都还在集合里（包括恒等置换），换言之满足封闭性。后者是说任何一个置换的逆元也在集合里。所以题目给的置换集合（包括恒等置换）构成一个群。

题目问的是本质不同的染色方案个数，这个很明显是 Burnside 引理该干的事。Burnside 引理：本质不同的染色方案个数等于群中每个置换（包括恒等置换）的不动点个数的平均值。不动点就是经过一次置换之后和原来一样的染色方案。

显然如果把每个置换拆成若干个循环的循环移位，那么一个染色方案是不动点，当且仅当每个循环中的颜色全部都是相同的。那么求一个置换有多少个不动点的问题就变成了：把一些有标号的数（每个循环的长度）分为三个集合（三种颜色），使第一个集合的和为 $S_r$，第二个集合的和为 $S_g$，第三个集合……既然前两个已经确定了那剩下的就是第三个集合了。求方案数。

数据范围很小，可以想到直接进行一个三维 dp。状态定义：$dp_{i,j,k}$ 为考虑前 $i$ 个数，第一个集合总和为 $j$，第二个集合总和为 $k$ 的方案数。第三个集合不需要考虑了，因为前两个确定了第三个自然也就确定了。转移显然。因为要 dp 多次，所以别忘了清空。

代码是我早年写的，所以可能比较奇怪。

```
#include <iostream>
using namespace std;
int perm[65], v[65], dp[65][65][65]; long long vis;

int qp(int n, int m, int p) {
    int ans = 1, base = n;
    while (m) {
        if (m & 1) (ans *= base) %= p;
        (base *= base) %= p; m >>= 1;
    }
    return ans;
}

int main() {
    int r, g, b, m, p, z, summ=0, summ2;
    cin >> r >> g >> b >> m >> p;
    for (int t=1; t<=m+1; t++) {
        vis = 0; z = 1; summ2 = 0;
        for (int i=1; i<=r+g+b; i++) if (t <= m) cin >> perm[i];
                                     else perm[i] = i;
        for (int i=1; i<=r+g+b; i++) {
            int x = i; v[z] = 0;
            while (!(vis & (1ll << x))) {vis |= 1ll << x; v[z]++; x = perm[x];}
            if (v[z]) z++;
        }
        dp[0][0][0] = 1;
        for (int i=1; i<z; i++) {
            summ2 += v[i];
            for (int j=0; j<=r; j++) {
                for (int k=0; k<=g; k++) {
                    int l = summ2 - j - k;
                    dp[i][j][k] = 0;
                    if (l > b || l < 0) continue;
                    if (j - v[i] >= 0) dp[i][j][k] += dp[i-1][j-v[i]][k];
                    if (dp[i][j][k] >= p) dp[i][j][k] -= p;
                    if (k - v[i] >= 0) dp[i][j][k] += dp[i-1][j][k-v[i]];
                    if (dp[i][j][k] >= p) dp[i][j][k] -= p;
                    dp[i][j][k] += dp[i-1][j][k];
                    if (dp[i][j][k] >= p) dp[i][j][k] -= p;
                }
            }
        }
        summ += dp[z-1][r][g];
        if (summ >= p) summ -= p;
    }
    cout << (summ * qp(m + 1, p - 2, p)) % p;
    return 0;
}
```

---

## 作者：creation_hy (赞：5)

Polya模版题。

# 前置知识

## Polya 定理：

问题：对集合染色。如果两个集合进行某种置换后相同，则称这两个集合相同。问一共能染出多少种不同的集合。

定理：简单来讲就是，答案为：对于每种置换，进行后仍然不同的集合的数量的平均数。

## 逆元：

用来处理除法取模。来做这题的应该都会吧，我就不多讲了。

定理：$\dfrac{a}{b}\bmod p=a\times b^{p-2}\bmod p$

# 思路

暴力 dp 求出对于每种置换有多少种方案即可。

$f[i][j][k]$ 表示使用 $i$ 种红、$j$ 种蓝、$k$ 种绿时的方案数。

```cpp
inline ll calc()
{
    memset(f, 0, sizeof(f));
    f[0][0][0] = 1;
    for (int t = 1; t <= tot; t++)
        for (int i = r; i >= 0; i--)
            for (int j = g; j >= 0; j--)
                for (int k = b; k >= 0; k--)
                {
                    if (sz[t] <= i)
                        f[i][j][k] = (f[i][j][k] + f[i - sz[t]][j][k]) % mod;
                    if (sz[t] <= j)
                        f[i][j][k] = (f[i][j][k] + f[i][j - sz[t]][k]) % mod;
                    if (sz[t] <= k)
                        f[i][j][k] = (f[i][j][k] + f[i][j][k - sz[t]]) % mod;
                }
    return f[r][g][b];
}
```

接下来把每种置换对应的方案取平均数。注意不变也是一种，所以要除以 $m+1$。

```cpp
for (int i = 1; i <= n; i++)
    a[i] = i;
getRing();
ll ans = calc();
for (int i = 1; i <= m; i++)
{
    for (int j = 1; j <= n; j++)
        cin >> a[j];
    getRing();
    ans = (ans + calc()) % mod;
}
cout << ans * qpow(m + 1, mod - 2) % mod;
```

# 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll r, g, b, n, m, a[65], sz[65], vis[65], tot, f[25][25][25], mod;
inline ll qpow(ll x, ll y)
{
    ll res = 1;
    while (y)
    {
        if (y & 1)
            res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}
inline void getRing()
{
    memset(vis, 0, sizeof(vis));
    tot = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
        {
            int pos = i, len = 0;
            while (!vis[pos])
            {
                len++;
                vis[pos] = true;
                pos = a[pos];
            }
            sz[++tot] = len;
        }
}
inline ll calc()
{
    memset(f, 0, sizeof(f));
    f[0][0][0] = 1;
    for (int t = 1; t <= tot; t++)
        for (int i = r; i >= 0; i--)
            for (int j = g; j >= 0; j--)
                for (int k = b; k >= 0; k--)
                {
                    if (sz[t] <= i)
                        f[i][j][k] = (f[i][j][k] + f[i - sz[t]][j][k]) % mod;
                    if (sz[t] <= j)
                        f[i][j][k] = (f[i][j][k] + f[i][j - sz[t]][k]) % mod;
                    if (sz[t] <= k)
                        f[i][j][k] = (f[i][j][k] + f[i][j][k - sz[t]]) % mod;
                }
    return f[r][g][b];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> r >> g >> b >> m >> mod;
    n = r + g + b;
    for (int i = 1; i <= n; i++)
        a[i] = i;
    getRing();
    ll ans = calc();
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
            cin >> a[j];
        getRing();
        ans = (ans + calc()) % mod;
    }
    cout << ans * qpow(m + 1, mod - 2) % mod;
    return 0;
}
```

---

## 作者：Karry5307 (赞：5)

### 题意

略。

$\texttt{Data Range:}1\leq S_r,S_b,S_g\leq 20,1\leq m\leq 60$

### 题解

Burnside 引理，符号化的说就是

$$\vert X/G\vert=\frac{1}{\vert G\vert}\sum\limits_{g\in G}\vert X^g\vert$$

说人话，就是本质不同的染色方案个数就是对于每个变换来说不动点个数的平均值。现在变换都给出来了，所以考虑算不动点个数。

先将置换分解成循环，那每个循环内的点都必须是一个颜色。将循环当成物品，然后三个颜色当成背包，然后这就是一个经典的背包问题，写个 $O(n^3)$ DP 就行了。

这里组合数学的一个错误之处就是认为每一个等价类的大小相同，但其实是不相同的，而且很好卡。比如说 reverse 中非回文串所在等价类的大小为 $2$，而回文串所在等价类的大小为 $1$，就不相同。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=61;
ll n,r,g,b,m,MOD,totc,id,c,res;
ll x[MAXN],f[MAXN][MAXN][MAXN],vis[MAXN],cyc[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
    ll res=1;
    while(exponent)
    {
        if(exponent&1)
        {
            res=(li)res*base%MOD;
        }
        base=(li)base*base%MOD,exponent>>=1;
    }
    return res;
}
inline ll calc()
{
	ll cur;
	totc=0,memset(f,0,sizeof(f)),memset(vis,0,sizeof(vis)),f[0][0][0]=1;
	for(register int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			cyc[++totc]=1,cur=x[i],vis[i]=1;
			while(cur!=i)
			{
				vis[cur]=1,cyc[totc]++,cur=x[cur];
			}
		}
	}
	for(register int i=1;i<=totc;i++)
	{
		cur=cyc[i];
		for(register int j=r;j>=0;j--)
		{
			for(register int k=g;k>=0;k--)
			{
				for(register int l=b;l>=0;l--)
				{
					j>=cur?f[j][k][l]=(f[j][k][l]+f[j-cur][k][l])%MOD:1;
					k>=cur?f[j][k][l]=(f[j][k][l]+f[j][k-cur][l])%MOD:1;
					l>=cur?f[j][k][l]=(f[j][k][l]+f[j][k][l-cur])%MOD:1;
				}
			}
		}
	}
	return f[r][g][b];
}
int main()
{
	r=read(),g=read(),b=read(),m=read(),MOD=read(),n=r+g+b;
	for(register int i=1;i<=m;i++)
	{
		c=1;
		for(register int j=1;j<=n;j++)
		{
			x[j]=read(),c&=(x[j]==j);
		}
		id|=c,res=(res+calc())%MOD;
	}
	if(!id)
	{
		for(register int i=1;i<=n;i++)
		{
			x[i]=i;
		}
		res=(res+calc())%MOD;
	}
	printf("%d\n",(li)res*qpow(m+(id^1),MOD-2)%MOD);
}
```

---

## 作者：littlez_meow (赞：3)

小清新群论题！

[题目指路](https://www.luogu.com.cn/problem/P1446)。

## step 1：群论建模

群论题最重要的是建模。

看到洗牌法很像置换，想到群论，考虑是用 Pólya 定理还是 Burnside 引理。

由于其中的染色是有规定数量的，不是任意染色，并不好用 Pólya 定理，因此考虑 Burnside 引理。

首先是等价类个数 $|X/G|$，这是要求的答案个数。

然后是置换群 $G$。

我们先看题面里说的：“输入数据保证任意多次洗牌都可用这 $m$ 种洗牌法中的一种代替，且对每种洗牌法，都存在一种洗牌法使得能回到原状态。”前半句的意思是满足封闭性，后半句的意思是存在逆元。

洗牌法构成置换群吗？不构成。

回想群的定义，逆元有封闭性有，置换乘法本身满足结合律，但是，没有单位元，即恒等置换。

因此，群 $G$ 应由洗牌法和恒等置换，加上置换乘法组成。

仔细想想你会发现，加上恒等置换并不影响答案，因为恒等置换是说明自己和自己同属一个等价类。

所以得到 $|G|=m+1$。

最后对于置换 $g$ 不动点个数 $|X^g|$，就是染色后进行置换染色不变的方案数。

## step 2：计算不动点

接下来就对于每个置换的不动点个数。

简单分析可以发现，如果 $i$ 置换到 $p_i$，那么原图中 $i$ 和 $p_i$ 一定是一种颜色。

由此推知，将一个置换拆成若干循环置换，这些循环置换对应的位置都只能有一种颜色。

设一共有 $t$ 个循环置换，第 $i$ 个循环置换的长度是 $l_i$，这个问题就转化为：计算把 $l$ 划分成三个集合，使三个集合中元素的和分别为 $S_r,S_b,S_g$ 的方案数。

这是什么？背包问题！

设 $dp_g(x,i,j,k)$ 表示对于置换 $g$，考虑到第 $x$ 个循环置换，三个集合里的和分别为 $i,j,k$ 的方案数。（下面省略 $dp$ 的下标）

边界条件：$dp(0,0,0,0)=1$，即什么都不放一种。

状态转移方程是下面几条：

1. 如果 $i>l_x,dp(x-1,i-l_x,j,k)\to dp(x,i,j,k)$

2. 如果 $j>l_x,dp(x-1,i,j-l_x,k)\to dp(x,i,j,k)$

3. 如果 $k>l_x,dp(x-1,i,j,k-l_x)\to dp(x,i,j,k)$

不动点个数为 $dp(t,S_r,S_b,S_g)$。

第一位可以滚动数组滚掉，空间复杂度 $O(S_rS_bS_g)$。

最后带入 Burnside 引理公式

$$|X/G|=\dfrac 1 {|G|}\sum\limits_{g\in G}|X^g|$$

即答案为
$$\dfrac 1 {m+1}\sum\limits_{g\in G}dp_g(t,S_r,S_b,S_g)$$

时间复杂度 $O(mnS_rS_bS_g)$，这么小的数据肯定能过。

## step 3：附上代码

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i(b);i<=i##i;++i)
#define R(i,a,b) for(int i(a),i##i(b);i>=i##i;--i) 
#define ll long long
using namespace std;
int sr,sb,sg,m,n,p,X[61][61];
int cycle[61],cnt;
inline ll qpow(ll base,int expo){
	ll res(1);
	while(expo){
		if(expo&1) res=res*base%p;
		base=base*base%p;
		expo>>=1;
	}
	return res;
}
inline void calc_cycle(int num){
	memset(cycle,0,sizeof(cycle));
	cnt=0;
	bool book[61]={};
	F(i,1,n){
		if(book[i]) continue;
		int now(i);
		++cnt;
		while(!book[now]) book[now]=1,now=X[num][now],++cycle[cnt];
	}
	return;
}
int ans,dp[2][21][21][21];
inline void dp_stable(){
	memset(dp,0,sizeof(dp));
	dp[0][0][0][0]=1;
	F(t,1,cnt){
		int now=t&1,last=now^1;
		memset(dp[now],0,sizeof(dp[now]));
		F(i,0,sr) F(j,0,sb) F(k,0,sg){
			if(i-cycle[t]>=0) dp[now][i][j][k]+=dp[last][i-cycle[t]][j][k];
			if(j-cycle[t]>=0) dp[now][i][j][k]+=dp[last][i][j-cycle[t]][k];
			if(k-cycle[t]>=0) dp[now][i][j][k]+=dp[last][i][j][k-cycle[t]];
			dp[now][i][j][k]%=p;
		}
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>sr>>sb>>sg>>m>>p;
	n=sr+sb+sg;
	F(i,1,m) F(j,1,n) cin>>X[i][j];
	F(i,1,n) X[0][i]=i;
	F(i,0,m){
		calc_cycle(i);
		dp_stable();
		ans+=dp[cnt&1][sr][sb][sg];
		ans>=p&&(ans-=p);
	}
	cout<<qpow(m+1,p-2)*ans%p;
	return 0;
} 
```

完结撒花 qwq~

---

## 作者：LinkyChristian (赞：2)

去年学了一遍过了一年忘光了导致需要重学，赶紧写下以确保明年不用再学一遍。

本文的目的是让读者快速理解并熟练运用 Pólya 定理，大部分的定理不加证明，如果错误之处请在评论区或私信作者指出。

# 速通Part

## 一、群的定义

若存在一个集合 $S$ 与一个二元运算 $·$ 满足以下性质

> - 封闭性 (Closure)：$\forall a,b \in S,a·b \in S$

> - 结合律 (Associativity)：$\forall a,b,c \in S, (a·b)·c=a·(b·c
)$

> - 单位元/幺元 (Identity element)：$\exists e \in S ,\forall a \in S ,e·a=a·e=a$

> - 逆元 (Inverse element)：$\forall a \in S, \exists b \in S,a·b=b·a=e$ 此处称 $b$ 为 $a$ 的逆元，记作 $b=a^{-1}$

满足这些性质的集合与二元运算的二元组 $(S,·)$ 被称作一个 **群**。

生活中有许多常见的群，如整数加法群 $(\mathbb{Z},+)$ 与正实数乘法群 $(\mathbb{+R},\times)$,可以尝试自己证明这些群的性质。

群 $G$ 的大小即为集合 $S$ 的大小，也可以用 $x \in G$ 表示 $x$ 是群中的元素。和集合有子集一样，群也有子群，不过这个之后再提。

下面开始的定理都只能作用于有限群。事实上，在同构意义下，所有有限群都同构于一个置换群（可以简单的理解成有限群就是置换群）。

## 二、置换

**定义**

有限集合到自身的双射称为置换，例如对于一个集合 $S={a_1,a_2,a_3,...,a_n}$，那么它的一个置换可以表示为

$$
\sigma=\begin{pmatrix}a_{p_1},a_{p_2},\dots,a_{p_{n-1}},a_{p_n}\\
a_{q_1},a_{q_2},\dots,a_{q_{n-1}},a_{q_n}\end{pmatrix}
$$

该置换意为将 $a_{p_i}$ 置换为 $a_{q_i}$，其中 $p_1,p_2,\dots,p_n$ 与 $q_1,q_2,\dots,q_n$ 均为 $1,2,\dots,n$ 的排列。

由于在交换置换中第一行的 $a_{p_i},a_{p_j}$ 的同时交换第二行的 $a_{q_i},a_{q_j}$ 所得到的置换是本质相同的，因此我们默认第一行为 $a_1,a_2,\dots,a_n$，此时置换可以直接写作 

$\sigma=(a_{p_1},a_{p_2},\dots,a_{p_n}) $

大小为 $n$ 的集合 $S$ 的本质不同的置换有 $n!$ 种。

**置换乘法**

置换 

$$
f=\begin{pmatrix}a_1,a_2,\dots,a_{n-1},a_n\\
a_{p_1},a_{p_2},\dots,a_{p_{n-1}},a_{p_n}\end{pmatrix}
$$

与置换

$$
g=\begin{pmatrix}a_{p_1},a_{p_2},\dots,a_{p_{n-1}},a_{p_n}\\
a_{q_1},a_{q_2},\dots,a_{q_{n-1}},a_{q_n}\end{pmatrix}
$$

的乘积

$$
f \circ g = \begin{pmatrix}a_1,a_2,\dots,a_{n-1},a_n\\
a_{q_1},a_{q_2},\dots,a_{q_{n-1}},a_{q_n}\end{pmatrix}
$$

**循环置换**

循环置换是一种特殊的置换，可表示为

$$
(a_1,a_2,\dots,a_{n-1},a_n)=\begin{pmatrix}a_1,a_2,\dots,a_{n-1},a_n\\
a_2,a_3,\dots,a_n,a_1\end{pmatrix}
$$

即将 $a_1,a_2,\dots,a_n$ 向前循环移位一位。

若两个循环置换没有相同元素，则称其 **不相交** 。

任意一个置换都可以分解为若干不相交的循环置换的乘积，例如

$$
\begin{pmatrix}a_1,a_2,a_3,a_4,a_5\\
a_3,a_1,a_2,a_5,a_4\end{pmatrix}=(a_1,a_3,a_2)\circ(a_4,a_5)
$$

证明可以看做是从 $a_{q_i}$ 向 $a_{p_i}$ 连一条边，那么置换构成的图必定是由若干个环组成的，每个环都是一个循环置换。  

 
**置换群**

大小为 $n$ 的集合 $S$ 上的所有 $n!$ 个置换与置换乘法 $\circ$ 构成的群称为 **$n$级对称群** ，记作 $S_n$，显而易见其满足群的性质。

对称群的子群称作 **置换群**  。

所有的循环置换也可以构成一类特殊的置换群，我们称其为 **循环群** 。

## 三、轨道-稳定子定理

**群作用** 

设定一个群 $G=(S,·)$ 与一个集合 $T$，定义运算

$$
\phi(g,a),g\in S,a\in T
$$ 

表示群中的元素 $g$ 作用集合中的元素 $a$，也可以写作 $g(a)$ （此处可以将群中的元素看做一种 **运算/操作**）。这里可能比较难懂，具体可以看后面的例题。 

如果满足

$$
\forall a\in T,\phi(e,a)=a
$$
$$
\forall a\in T,f\in S,g\in S,\phi(f,\phi(g,a))=\phi(f·g,a)
$$

则称群 $G$ 作用于集合 $T$。

特别一提，群作用是可逆的（群中元素存在逆元），即对于 $g\in S,x \neq y \Leftrightarrow g(x) \neq g(y)$

下面开始的定理中群作用的集合都为有限集。

**轨道** 

设群 $G$ 作用于集合 $U$ ，则对于元素 $x\in U$，$x$ 的轨道 $G(x)$ 可以表示为集合 $\{g(x)|g\in S\}$。即群 $G$ 中的元素作用于 $x$ 能达到的集合。

**稳定子** 

对于元素 $x\in U$，$x$ 的稳定子 $G^x$ 表示为 $\{g|g\in S,g(x)=x\}$,即群中满足 $g(x)=x$ 的 $g$ 构成的集合。

**轨道-稳定子定理**

$$
|G^x|\times |G(x)|=|G|
$$

即元素 $x$ 的稳定子个数乘以轨道个数等于群的大小。

## 四、Burnside引理

**等价类**

设群 $G$ 作用于集合 $X$，若对于 $x,y\in X$，存在 $g \in G$ 使得 $g(x)=y$，则称 $x,y$ 属于同一等价类。

对于一类等价类计数问题，我们可以使用Burnside引理

$$
|X/G|=\frac{1}{|G|}\sum_{g\in G} X^g
$$

其中 $|X/G|$ 表示集合 $X$ 在群 $G$ 作用下的等价类的数量，而 $X^g$ 表示 $X$ 在群中元素 $g$ 的作用下的不动点的数量，即集合中满足 $g(x)=x$ 的 $x$ 的数量。

## 五、Pólya定理

Burnside引理中群 $G$ 作用的集合 $X$ 是任意的，而Pólya定理中集合 $X$ 必须是一个集合 $A$ 到一个集合 $B$ 的所有映射构成的集合。

一般情况下，Pólya定理使用于经典的染色问题，即将 $n$ 个元素染成 $m$ 种颜色，那么群 $G$ 为 $n$ 个元素的所有置换构成的集合，集合 $A$ 为 $n$ 个元素，集合 $B$ 为 $m$ 种颜色，集合 $X$ 为集合 $A$ 到一个集合 $B$ 的所有映射构成的集合，即将 $n$ 个元素染成 $m$ 种颜色的所有方案构成的集合。

Pólya定理为 

$$
|X/G|=\frac{1}{G}\sum_{g\in G} |B|^{c(g)} 
$$

在染色问题上，设不同构染色方案数为 $L$，这个公式即为

$$
L=\frac{1}{G}\sum_{g\in G} m^{c(g)} 
$$

解决一般的染色问题直接记下面的公式就好了。

其中 $c(g)$ 表示置换 $g$ 的环数，即设置换 $g$ 为 $(a_1,a_2,...,a_n) $ ,从 $i$ 往 $a_i$ 连一条边，建出来的图中的环的数量，也可以说成是置换 $g$ 能拆分成的不相交的循环置换的数量。

## 例题Part

### [P1446 [HNOI2008] Cards](https://www.luogu.com.cn/problem/P1446)

题目中的 

> 输入数据保证任意多次洗牌都可用这 $m$ 种洗牌法中的一种代替，且对每种洗牌法，都存在一种洗牌法使得能回到原状态。

显然这是在告诉我们所有给出的置换构成了一个群。这启发我们想到 Burnside 引理。根据 Burnside 引理，我们只需求出其在每种置换下的不动点数量即可。考虑每一个循环只能染一种颜色，结合题目对每种颜色数量的限制，我们使用一个背包来统计方案数，设 $f_{i,j}$ 表示第一种颜色染了 $i$ 个点，第二种颜色染了 $j$ 个点的方案数（这里其实可以做一个优化，因为我们可以选择一种颜色不统计，所以我们可以选择最多的颜色数不去统计，这样状态数最多为 $\frac{n^2}{9}$，但本题数据范围较小所以随便 dp 都能过）。

```cpp
#include<bits/stdc++.h>
#define N 65
#define pb push_back
using namespace std;
int n,n1,n2,n3,m,mod,a[N],vis[N],f[25][25],ans;
void add(int& a1,int a2) {a1=a1+a2>=mod?a1+a2-mod:a1+a2;}
int qpow(int a1,int a2) {
	int res=1;
	while(a2) {
		if(a2&1) res=1ll*res*a1%mod;
		a1=1ll*a1*a1%mod;
		a2>>=1;
	} return res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>n1>>n2>>n3>>m>>mod;
	n=n1+n2+n3;
	for(int i=0; i<=m; i++) {
		vector<int> v;
		if(i) for(int j=1; j<=n; j++) cin>>a[j],vis[j]=0;
		else for(int j=1; j<=n; j++) a[j]=j;
		for(int j=1; j<=n; j++) if(!vis[j]) {
			int tot=1,tmp=a[j];vis[j]=1;
			while(tmp!=j) tot++,vis[tmp]=1,tmp=a[tmp];
			v.pb(tot);
		}
		for(int i=0; i<=n1; i++)
			for(int j=0; j<=n2; j++) f[i][j]=0;
		f[0][0]=1;
		for(int x:v) 
			for(int p=n1; ~p; p--)
				for(int q=n2; ~q; q--) {
					if(p>=x) add(f[p][q],f[p-x][q]);
					if(q>=x) add(f[p][q],f[p][q-x]);
				}
		add(ans,f[n1][n2]);
	} printf("%d\n",1ll*ans*qpow(m+1,mod-2)%mod);
}
```


参考文献：

[群论简介 - OI Wiki](https://oi-wiki.org/math/group-theory/)

[置换群 - OI Wiki](https://oi-wiki.org/math/permutation-group/)

[[整理]Polya定理从入门到入土](https://www.cnblogs.com/juruoajh/p/14649943.html)

[[算法笔记] Polya定理 - maoyiting](https://www.cnblogs.com/maoyiting/p/14171300.html#/cnblog/works/article/14171300)

[题解 P4980 【【模板】Polya定理】](https://www.luogu.com.cn/blog/Soulist/solution-p4980)

感谢U群群友的答疑



---

## 作者：Corzica (赞：1)

显然，题中所给的洗牌就是一种置换，并且满足了运算封闭性和存在逆元。我们需要在单位元未加入洗牌集合中加入它，随后这个洗牌操作就是一个置换群。

根据Burnside定理，我们只需要求出每一种置换情况下的不动点的集合大小即可。

我们枚举每一种置换，如果一种方案是不动点，那么对应的环上的每一个点颜色应相同。可以dfs加背包dp解决。

时间复杂度是 $O(mn^3)$

```cpp
#include <bits/stdc++.h>
using namespace std;
int r, b, g, n, m, a[65][65], f[65][65][65], mod, vis[65], cnt, num[65], ans, sum[65];
inline int ksm(int p, int q) {
	int base = 1;
	while (q) {
		if (q & 1) base = base * p % mod;
		q >>= 1;
		p = p * p % mod;
	}
	return base;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> r >> g >> b >> m >> mod;
	n = r + b + g;
	bool flg = false;
	for (int i = 1; i <= m; i++) {
		bool fflg = true;
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] != j) fflg = false;
		}
		flg |= fflg;
	}
	if (!flg) {
		m++;
		for (int i = 1; i <= n; i++) {
			a[m][i] = i;
		}
	}
	for (int i = 1; i <= m; i++) {
		memset(vis, 0, sizeof(vis));
		memset(num, 0, sizeof(num));
		cnt = 0;
		for (int j = 1; j <= n; j++) {
			if (!vis[j]) {
				cnt++;
				int p = j;
				do {
					num[cnt]++;
					vis[p] = 1;
					p = a[i][p];
				} while (!vis[p]);
			}
		}
		memset(f, 0, sizeof(f));
		f[0][0][0] = 1;
		for (int j = 1; j <= cnt; j++) {
			sum[j] = sum[j - 1] + num[j];
		}
		for (int j = 1; j <= cnt; j++) {
//			cout << num[j] << " ";
			for (int p = 0; p <= r; p++) {
				for (int q = 0; q <= g; q++) {
					int w = sum[j - 1] - p - q;
					if (w < 0) continue;
					if (p + num[j] <= r) {
						f[j][p + num[j]][q] = (f[j][p + num[j]][q] + f[j - 1][p][q]) % mod;
					}
					if (q + num[j] <= g) {
						f[j][p][q + num[j]] = (f[j][p][q + num[j]] + f[j - 1][p][q]) % mod;
					}
					if (w + num[j] <= b) {
						f[j][p][q] = (f[j][p][q] + f[j - 1][p][q]) % mod;
					}
//					cout << p << " " << q << " " << j - 1 << " " << f[j - 1][p][q] << "[]\n";
				}
			}
		}
//		cout << f[cnt][r][g] << "==";
//		cout << "\n";
		ans = (ans + f[cnt][r][g]) % mod;
	}
	ans = ans * ksm(m, mod - 2) % mod;
	cout << ans;
}
```

---

## 作者：Z1qqurat (赞：1)

闲话：HN 选手突然发现很多远古 HNOI 题都好有意思啊……而且都是做起来非常舒服，有难度有收获但不是盲目堆积毒瘤元素的那种。虽然这是个 Polya & Burnside 模板题但是这么多年前就考如此前卫的计数技巧属实有点厉害了。

读题发现可以将洗牌方式当作一个群（群内的运算可按照题目声明定义为洗牌方式的叠加），洗牌方式就是该群的函数，题目中保证了**任意多次洗牌都可用这 $m$ 种洗牌法中的一种代替，且对每种洗牌法，都存在一种洗牌法使得能回到原状态。** 这保证了这些洗牌方式就是群的函数，并且不需要复合就可以凑出所有洗牌。所以算上不洗牌，一共有 $m+1$ 种函数。那么题目要求的就是一个置换群计数。

置换群计数考虑 Polya 定理，或者说是 Burnside 引理。回顾一下 Burnside 引理的内容：假设该群的函数集合为 $S_f$，对于每个函数 $f$，它的不动点集合为 $\text{Sta}(f)$。那么置换群数量为 $\frac{\sum\limits_{f\in S_f} |\text{Sta}(f)|}{|S_f|}$。

考虑这个题我们怎么做，也就是怎么求不动点个数：对于每一种群函数，将点进行分组，即每一组内的点都要染上相同的颜色。我们将其转化为图论模型，每种洗牌方式的 $X_i$ 与 $i$ 连边，一个连通块内的点都要连相同的颜色。那么这个函数的不动点就是将最后染色染成 $red$ 个红点，$blue$ 个蓝点，$green$ 个绿点的方案数。直接把一个连通块当作一个物品，跑一个记录方案数的 01 背包即可。设 $f_{i,j,k}$ 表示目前一共染了 $i$ 个点，其中有 $j$ 个红点，$k$ 个蓝点，转移的时候发现因为物品顺序不影响最后结果，滚掉第一维，只用记录红点和蓝点个数，绿点个数也是确定的。最后答案累加上 $f_{red, blue}$ 即可。注意不洗牌也是一个函数，别忘了处理。

$P$ 很小所以不用开 `int64_t`，实现起来没啥细节，1A 了。

```cpp
#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)
using i64 = int64_t;
using std::cin;
using std::cout;
constexpr int N = 65, M = 25;

int cnt, n, m, red, blue, green, P, ans;
std::array<int, N> siz;
std::array<std::array<int, M>, M> f, g;
std::array<bool, N> vis;
std::array<std::vector<int>, N> G;

auto addedge(int x, int y) {
   G[x].emplace_back(y), G[y].emplace_back(x);
   return ;
}

auto qpow(int x, int y) {
   auto ret{1};
   for (; y; x = x * x % P, y >>= 1) {
      if (y & 1) ret = ret * x % P; 
   }
   return ret;
}

auto clear2(std::array<std::array<int, M>, M> &f) {
   for (auto i = 0; i <= red; ++i) f[i].fill(0);
   return ;
}

auto dfs(int u) -> void {
   vis[u] = 1, siz[cnt]++;
   for (auto v : G[u]) 
      if (!vis[v]) dfs(v);
   return ;
}

auto solve(int type) {
   clear2(f), siz.fill(0), vis.fill(0);
   for (auto i = 0; i <= n; ++i) G[i].clear();
   cnt = 0;
   if (type)
      for (auto i = 1, x = 0; i <= n; ++i)
         cin >> x, addedge(i, x);
   
   for (auto i = 1; i <= n; ++i) 
      if (!vis[i]) cnt++, dfs(i);
   
   f[0][0] = 1; auto sum{0};
   for (auto i = 1; i <= cnt; ++i) {
      clear2(g);
      for (auto j = 0; j <= std::min(red, sum); ++j) {
         for (auto k = 0; k <= std::min(blue, sum); ++k) {
            (g[j + siz[i]][k] += f[j][k]) %= P;
            (g[j][k + siz[i]] += f[j][k]) %= P;
            (g[j][k] += f[j][k]) %= P;
         }
      }
      sum += siz[i], f = g;
   }
   ans = (ans + f[red][blue]) % P;
   return ;
}

auto main() -> int {
   std::ios::sync_with_stdio(false);
   cin.tie(nullptr), cout.tie(nullptr);

   cin >> red >> blue >> green >> m >> P;
   n = red + blue + green;
   solve(0);
   for (auto i = 1; i <= m; ++i) solve(1);
   ans = ans * qpow(m + 1, P - 2) % P;
   cout << ans << "\n";
   return 0;
}

---

## 作者：analysis (赞：1)

群论题

Brunside 引理的一个常见用处：颜色的个数有限制，不可以使用 Polya 计数。

根据 Brunside 引理:

$$
L = \frac{1}{|G|}\sum_{a_i \in G}D(a_i)
$$

（其中 $L$ 为本质不同的方案数，$G$ 为置换群，$D(a_i)$ 为对于置换 $a_i$ 不变的方案数）

对于一个置换有一个方案不变当且仅当置换中的所有循环都是同一颜色。

故对于每一个置换，处理出循环个数以及每个循环长度，动态规划方案数即可。

（代码中的 $f_{i,j,k}$ 表示当前这个置换处理了若干个循环，使用了 $i$ 个 `R`，$j$ 个 `G`，$k$ 个 `B` 的方案数）。

```cpp
#include <bits/stdc++.h>
using namespace std;
int f[25][25][25];
int r, g, b, m, p;
int a[65], d[65], vis[65], cnt;
int n;
int sumd = 0;
void dp(int cnt)
{
    memset(f, 0, sizeof f);
    f[0][0][0] = 1;
    for (int i = 1; i <= cnt; i++)
    {
        for (int rr = r; rr >= 0; rr--)
        {
            for (int gg = g; gg >=0; gg--)
            {
                for(int bb = b;bb >= 0;bb--)
                {
                    if(rr >= d[i])f[rr][gg][bb] = (f[rr][gg][bb] + f[rr - d[i]][gg][bb])%p;
                    if(gg >= d[i])f[rr][gg][bb] = (f[rr][gg][bb] + f[rr][gg - d[i]][bb])%p;
                    if(bb >= d[i])f[rr][gg][bb] = (f[rr][gg][bb] + f[rr][gg][bb - d[i]])%p;
                }
            }
        }
    }
    sumd = (sumd + f[r][g][b]) % p;
}
int fpow(int a,int b)
{
    int r = 1;
    while(b)
    {
        if(b&1)r=r*a%p;
        a=a*a%p;
        b>>=1;
    }
    return r%p;
}
signed main()
{
    cin >> r >> g >> b >> m >> p;
    n = r + g + b;
    for(int i=1;i<=n;i++)
    {
        d[i] = 1;
    }
    dp(n);
    for (int k = 1; k <= m; k++)
    {
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        cnt = 0;
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= n; i++)
        {
            if (vis[i])
                continue;
            vis[i] = 1;
            int tmp = 1;
            for (int j = a[i]; j != i; j = a[j])
            {
                vis[j] = 1;
                tmp++;
            }
            d[++cnt] = tmp;
        }
        dp(cnt);
    }
    cout<<(sumd * fpow(m+1,p-2) % p);
}
```

---

## 作者：Fzrcy (赞：0)

Tags：Burnside 引理。

染色问题，考虑用置换的知识去解决。

这里默认不进行任何操作也算一种洗牌法。

注意到题目给出的重要信息：

> 任意多次洗牌都可用这 $m$ 种洗牌法中的一种代替，且对每种洗牌法，都存在一种洗牌法使得能回到原状态。

这表明输入给出的洗牌法本身就是一个置换群，无需考虑洗牌法的组合。

根据 Burnside 引理，答案等于所有洗牌法的不动点的平均数。

考虑对一个洗牌法统计不动点的个数，先将洗牌法分解为循环的乘积，显然每个循环内的牌的颜色必须相同，直接 dp 计算方案数即可。

```cpp
#include <bits/stdc++.h>
#define inl inline
#define RG register
#define R RG int
using namespace std;
constexpr int N=61;
int P;
int f[N][21][21][21],sz[N];
int dp(R n,R a,R b,R c){ // 统计方案数
    for(R i=1;i<=n;i++) for(R j=0;j<=a;j++)
        for(R k=0;k<=b;k++) for(R l=0;l<=c;l++)
            f[i][j][k][l]=0;
    f[0][0][0][0]=1;
    for(R i=1;i<=n;i++)for(R x=0;x<=a;x++)
        for(R y=0;y<=b;y++)for(R z=0;z<=c;z++){
            if(x+sz[i]<=a)(f[i][x+sz[i]][y][z]+=f[i-1][x][y][z])%=P;
            if(y+sz[i]<=b)(f[i][x][y+sz[i]][z]+=f[i-1][x][y][z])%=P;
            if(z+sz[i]<=c)(f[i][x][y][z+sz[i]]+=f[i-1][x][y][z])%=P;
        }
    return f[n][a][b][c];
}
bool ban[N];int a[N],n,A,B,C,m;
int sol(bool flag=0){
    if(flag){
        for(R i=1;i<=n;i++)
            sz[i]=1;
        return dp(n,A,B,C);
    }
    int t=0;
    for(R i=1;i<=n;i++)
        ban[i]=0,cin>>a[i];
    for(R i=1;i<=n;i++)if(!ban[i]){
        int c=0;
        do ++c,ban[i]=1,i=a[i]; while(!ban[i]);
        sz[++t]=c;
    }
    int tmp=dp(t,A,B,C);
    return tmp;
}
int main(){
    cin>>A>>B>>C>>m>>P;n=A+B+C;int ans=sol(1);
    for(R i=1;i<=m;i++)ans=(ans+sol())%P;
    for(R i=1;i<=P-2;i++)ans=ans*(m+1)%P;
    cout<<ans;
    return 0;
}
```



---

## 作者：Remake_ (赞：0)

首先我们发现，这个洗牌操作就是一个置换的形式，然后我们又看到题目中的问题也是求本质不同的染色方案，故而很显然我们可以得知这是一道群论计数问题，接下来我们将所有洗牌法均视作置换，而洗牌法的集合则均视作置换群

但是群论计数问题中置换群得满足条件即其中任意两个置换的乘积仍在该置换群中，这个题目满足吗？

不得不吐槽一下这句话略有些隐蔽：

**输入数据保证任意多次洗牌都可用这 $m$ 种洗牌法中的一种代替，且对每种洗牌法，都存在一种洗牌法使得能回到原状态。**

依据这个简单思考一下便不难得知这句话保证了该置换群满足条件（注意，该置换群中还应对应的有一种保持原状态不动的置换，即对于所有 $i$ 有 $X_i=i$）

接着就可以考虑套用 Burnside 引理了：等价类的个数等于置换群中所有置换的不动点个数的平均值

问题转化为对于每一个置换求不动点个数

简单思考一下发现可以先将每一个置换分解成多个循环的乘积，而一个置换所对应的不动点一定满足这一个置换的每一个循环中有且仅有一种颜色

不难发现基于上面的这条性质这个问题等价于：有多个物品（置换分解为了多个循环），每个物品的质量不一（每个循环的大小不尽相同）且每个物品只能染一个颜色（每个循环中有且仅有一种颜色），有多少种染色方案使得红色物品的总质量为 Sr ，蓝色物品的总质量为 Sb，绿色物品的总质量为 Sg

这个东西显然是可以直接 dp 的

~~不要告诉我你基础 dp 都不会就来做群论计数~~

然后讲一下如何将置换分解为循环（我的方法）：若洗完牌后原本在位置 $i$ 的牌变到了位置 $j$，则 $i$ 和 $j$ 一定在同一个循环当中，所以直接并查集就行了qwq

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
#define timeused() (double)clock()/CLOCKS_PER_SEC
#define rep(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define repp(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x){
   T f=1;x=0;char c=getchar();
   for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
   for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
   x*=f;
   return x;
}
ll a,b,c,m,p,n,k,dp[25][25][25],f[65],qwq[65],ans;
vector<ll> v;
inline ll find(ll x){return x==f[x]?x:find(f[x]);}
ll qp(ll b,ll P){
   ll ans=1,base=b;
   while(P){
      if(P&1) ans=ans*base%p;
      base=base*base%p;
      P>>=1;
   }
   return ans;
}
ll getinv(ll x){return qp(x,p-2);}
int main(){
   rd(a);
   rd(b);
   rd(c);
   rd(m);
   rd(p);
   n=a+b+c;
   rep(i,0,m){
      memset(dp,0,sizeof(dp));
      dp[0][0][0]=1;
      rep(j,1,n) f[j]=j,qwq[j]=0;
      v.clear();
      rep(j,1,n){
         if(i) rd(k);
         else k=j;
         f[find(j)]=find(k);
      }
      rep(j,1,n) ++qwq[find(j)];
      rep(j,1,n) if(qwq[j]) v.pb(qwq[j]);
      rep(j,0,v.size()-1){
         repp(A,a,0) repp(B,b,0) repp(C,c,0){
            if(A>=v[j]) dp[A][B][C]+=dp[A-v[j]][B][C];
            if(B>=v[j]) dp[A][B][C]+=dp[A][B-v[j]][C];
            if(C>=v[j]) dp[A][B][C]+=dp[A][B][C-v[j]];
            dp[A][B][C]%=p;
         }
      }
      ans+=dp[a][b][c];
      ans%=p;
   }
   printf("%lld",ans*getinv(m+1)%p);
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

考虑 $m$ 很小，$S_x , S_y , S_z$ 也很小，所以留意到做的时候可能是个 $O(m ^ 4)$ 之类的时间复杂度。            

考虑用 Burnside 做这道题，还是考虑对每种置换操作建边，然后把它们缩成一些环，然后如果我们原来的颜色排列要成为不动点，那么就需要保证环上所有点的颜色不变。                

那么现在一个环内的颜色都一样，问题就变成了一些有大小的环，然后有 $3$ 种颜色，每种颜色有一定个数但保证总的颜色个数等于所有环相加的大小，然后每用一种颜色染环都得扣除相应的环的大小个颜色，求染环的方案就是这个置换操作下不动点的个数了。        

我们考虑直接用排列组合算不太现实，由于颜色数很小所以直接 $DP$ ，记 $dp_{i,x,y,z}$ 表示当选完第 $i$ 个环后剩余三种颜色卡牌个数分别为 $x , y , z$ 时的方案数，然后就看一下当前 $x + siz_x$ 和 $y + siz_y$ 以及 $z + siz_z$ 是否合法就从相应的 $dp_{i - 1 , x + siz_x , y , z}$ 和 $dp_{i - 1 , x , y + siz_y , z}$ 以及 $dp_{i - 1 , x , y , z + siz_z}$ 转移。           

在写的时候你会发现这是一个 $O(nmS_xS_yS_z)$ 级别的时间复杂度，有可能会跑 $T$ 加上空间也不是很好看，我们考虑转移之和前一个有关所以直接用 $0/1$ 代替前面后面滚掉一维，接着我们记录一下前缀的环大小之和，这样枚举完 $x , y$ 后 $z$ 就可以直接得出，又可以少枚举一维，时间复杂度就也被压下来了。           

最后，由于可能输入的置换操作里面有 $1 , 2 , …… , n$ 的排列所以得特判掉。             

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 65;
int a,b,c,m,P,n,siz[Len],to[Len],cnt,sim,sum[Len];
bool flag[Len];
int dp[2][21][21][21],ans;
void dfs(int x)
{
	if(flag[x]) return;
	sim ++;
	flag[x] |= 1;
	dfs(to[x]);
}
int qpow(int a,int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = res * a % P;
		a = a * a % P;
		b = b >> 1;
	}
	return res;
}
int main()
{
	scanf("%d %d %d %d %d",&a,&b,&c,&m,&P);
	n = a + b + c;
	memset(dp , 0 , sizeof dp);
	memset(flag , 0 , sizeof flag);
	dp[0][a][b][c] = 1 , cnt = 0;
	for(int i = 1 ; i <= n ; i ++) to[i] = i;
	for(int j = 1 ; j <= n ; j ++) if(!flag[j]){sim = 0 ; dfs(j) ; siz[++ cnt] = sim;}
	for(int j = 1 ; j <= n ; j ++) sum[j] = sum[j - 1] + siz[j];
	for(int j = 1 ; j <= cnt ; j ++)
		for(int x = 0 ; x <= a ; x ++)     
		    for(int y = 0 ; y <= b ; y ++)
		    {
		       	int z = n - sum[j] - x - y;
		       	if(z < 0 || z > c) continue;
		       	//printf("%d %d %d %d\n",j,x,y,z);
		        dp[j % 2][x][y][z] = 0;
		        if(x + siz[j] <= a) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x + siz[j]][y][z];
		        if(y + siz[j] <= b) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x][y + siz[j]][z];
		        if(z + siz[j] <= c) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x][y][z + siz[j]];
				dp[j % 2][x][y][z] %= P;
			}
	ans = (ans + dp[cnt % 2][0][0][0]) % P;
	int Sub = 0;
	for(int i = 1 ; i <= m ; i ++)
	{
		memset(flag , 0 , sizeof flag);
	    dp[0][a][b][c] = 1 , cnt = 0;bool flaw = 0;
		for(int j = 1 ; j <= n ; j ++) 
		{
		    scanf("%d",&to[j]);
		    if(to[j] != j) flaw |= 1;
		}
		if(!flaw){Sub ++ ; continue;}
		for(int j = 1 ; j <= n ; j ++) if(!flag[j]){sim = 0 ; dfs(j) ; siz[++ cnt] = sim;}
		for(int j = 1 ; j <= n ; j ++) sum[j] = sum[j - 1] + siz[j];
		for(int j = 1 ; j <= cnt ; j ++)
		    for(int x = 0 ; x <= a ; x ++)     
		        for(int y = 0 ; y <= b ; y ++)
		        {
		        	int z = n - sum[j] - x - y;
		        	if(z < 0 || z > c) continue;
		        	dp[j % 2][x][y][z] = 0;
		        	if(x + siz[j] <= a) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x + siz[j]][y][z];
		        	if(y + siz[j] <= b) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x][y + siz[j]][z];
		        	if(z + siz[j] <= c) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x][y][z + siz[j]];
					dp[j % 2][x][y][z] %= P;
				}
		ans = (ans + dp[cnt % 2][0][0][0]) % P;
		for(int j = 1 ; j <= cnt ; j ++)
		    for(int x = 0 ; x <= a ; x ++)     
		        for(int y = 0 ; y <= b ; y ++) 
		        {
		        	int z = n - sum[j] - x - y;
		        	if(z < 0 || z > c) continue;
		        	dp[0][x][y][z] = dp[1][x][y][z] = 0;
				}
	}
	printf("%d\n",ans * qpow(m + 1 - Sub , P - 2) % P);
	return 0;
}
```

---

## 作者：⚡114514_zzm⚡ (赞：0)

因为有颜色数量的限制，所以Polya就不太可行了.没事，我们还有Burnside       
于是我们要找每个置换下不变的方案数                                  
不难发现，对于每个循环，循环中的颜色必须相同才行            
于是把当前置换的循环处理出来，当成物品跑01背包，就可以求出不变的方案数                             
注意还有额外的一种置换是不洗牌，也就是说不变，要特殊处理                
```
#include<bits/stdc++.h>
#define LL long long
LL in() {
	char ch; LL x = 0, f = 1;
	while(!isdigit(ch = getchar()))(ch == '-') && (f = -f);
	for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
	return x * f;
}
int f[50][50][50];
bool vis[100];
int mp[100];
int siz[100];
int ans;
int a, b, c, m, mod, n;
LL ksm(LL x, LL y) {
	LL re = 1LL;
	while(y) {
		if(y & 1) re = re * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return re;
}
int work(int flag) {
	memset(f, 0, sizeof f);
	for(int i = 1; i <= n; i++) vis[i] = 0, siz[i] = 0;
	int num = 0;
	if(!flag) {
		for(int i = 1; i <= n; i++) {
			if(vis[i]) continue;
			num++;
			int now = i;
			while(!vis[now]) vis[now] = true, siz[num]++, now = mp[now];
		}
	}
	else {
		num = n;
		for(int i = 1; i <= n; i++) siz[i] = 1;
	}
	f[0][0][0] = 1;
	for(int i = 1; i <= num; i++)
		for(int A = a; A >= 0; A--)
			for(int B = b; B >= 0; B--)
				for(int C = c; C >= 0; C--) {
					if(A >= siz[i]) (f[A][B][C] += f[A - siz[i]][B][C]) %= mod;
					if(B >= siz[i]) (f[A][B][C] += f[A][B - siz[i]][C]) %= mod;
					if(C >= siz[i]) (f[A][B][C] += f[A][B][C - siz[i]]) %= mod;
				}
	return f[a][b][c];
}

int main() {
	n = (a = in()) + (b = in()) + (c = in());
	m = in(), mod = in();
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) mp[j] = in();
		(ans += work(0)) %= mod;
	}
	(ans += work(1)) %= mod;
	printf("%lld", 1LL * ans * ksm(m + 1, mod - 2) % mod);
	return 0;
}
```


---

## 作者：zyh2015 (赞：0)

来自我的博客：http://blog.csdn.net/yihan\_z/article/details/68066813


题目大意：给出n张牌，分别染a张红色，b张蓝色，c张绿色(n=a+b+c)，给出m个置换，问不同的染色方案。


置换群中的染色方案问题可用Burnside引理解决。


Burnside引理可以借助[百度百科](http://baike.baidu.com/link?url=\_rsyr3t-Y8QbYNmTuhbcqyx8FqgdWmYXoFyBg0PT5daPM4OxXgieRDGU\_km0AZnL9iQnohP7THrEjZXHOzXadq3w1lHwq6nJaXwe5z43LUOSho4sntk8vgXdrtZDys\_d) 中应用的例1理解，或者参考白书理解。


现在要求出不动点的个数。每个置换中都有若干个循环，不动点在一个循环中的颜色必须相同。可以转化成背包问题，将每个循环看作是一个物品，物品的重量为循环元素个数。

最后做除法在模意义下需要逆元，题目中保证模数为质数所以费马小定理一下就好...

```cpp
#include <cstdio>
#include <cstring>
#define N 105
using namespace std;
typedef long long LL;
int a,b,c,n,m,MOD,p[N];
LL f_pow(LL x,LL y) {
    LL tmp=1;
    while(y) {
        if(y&1) (tmp*=x)%=MOD;
        (x*=x)%=MOD;
        y>>=1;
    }
    return tmp;
}
int calc() {
    static bool k[N];
    static int s[N],top,f[N][N][N];
    memset(k,false,sizeof k);
    top=0;
    for(int i=1;i<=n;i++) {
        if(k[i]) continue;
        int cnt=0,tmp=i;
        while(!k[tmp]) k[tmp]=true, cnt++, tmp=p[tmp];
        s[top++]=cnt;
    }
    memset(f,0,sizeof f);
    f[0][0][0]=1;
    while(top--)
        for(int i=a;~i;i--)
            for(int j=b;~j;j--)
                for(int t=c;~t;t--) {
                    if(i>=s[top]) (f[i][j][t]+=f[i-s[top]][j][t])%=MOD;
                    if(j>=s[top]) (f[i][j][t]+=f[i][j-s[top]][t])%=MOD;
                    if(t>=s[top]) (f[i][j][t]+=f[i][j][t-s[top]])%=MOD;
                }
    return f[a][b][c];
}
int main() {
    scanf("%d%d%d%d%d",&a,&b,&c,&m,&MOD);
    n=a+b+c;
    LL ans=0;
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=n;j++) scanf("%d",p+j);
        ans+=calc();
    }
    for(int j=1;j<=n;j++) p[j]=j;
    ans+=calc();
    printf("%lld\n",ans*f_pow((LL)m+1,(LL)MOD-2)%MOD);
    return 0;
}
```

---

