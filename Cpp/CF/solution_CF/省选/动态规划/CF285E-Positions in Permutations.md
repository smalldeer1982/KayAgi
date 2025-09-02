# Positions in Permutations

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

We'll call position $ i $ ( $ 1<=i<=n $ ) in permutation $ p_{1},p_{2},...,p_{n} $ good, if $ |p[i]-i|=1 $ . Count the number of permutations of size $ n $ with exactly $ k $ good positions. Print the answer modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The only permutation of size 1 has 0 good positions.

Permutation $ (1,2) $ has 0 good positions, and permutation $ (2,1) $ has 2 positions.

Permutations of size 3:

1. $ (1,2,3) $ — 0 positions
2. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/0be2e55cf7a19e2daea8429a422511a827d2e236.png) — 2 positions
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/581bad7452cc25f3e2dca31dac99a205bf6361ef.png) — 2 positions
4. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/aad15ec07c7621cca60c3be370547e4457323e38.png) — 2 positions
5. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/b2a9b87daae026f62e110bd34347625817635c68.png) — 2 positions
6. $ (3,2,1) $ — 0 positions

## 样例 #1

### 输入

```
1 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 2
```

### 输出

```
4
```

## 样例 #4

### 输入

```
4 1
```

### 输出

```
6
```

## 样例 #5

### 输入

```
7 4
```

### 输出

```
328
```

# 题解

## 作者：command_block (赞：23)

[题目连接](https://www.luogu.org/problem/CF285E)

题意简洁明了,小清新计数题呢~

------------

首先看到恰好……~~这个词太敏感了~~

完美数恰好为 $m$ 的排列数为$G(m)$

另外构造一种方案数:

强行令$m$个位置完美,剩下的放任自流的方案数为$F(m)$

那么,对于一种完美数恰好为 $M$ 的排列,在$F(m)$中会被统计到$\dbinom{M}{m}$次。

那么得到关系式$F(m)=\sum\limits_{i=m}^n\dbinom{i}{m}G(i)$

[二项式反演](https://www.luogu.org/blog/command-block/yi-suo-ji-guai-di-fan-yan)得到

$G(m)=\sum\limits_{i=m}^n(-1)^{i-m}\dbinom{i}{m}F(i)$

现在只要算出$F(0...n)$即可。

我们设计一个$dp$:

要注意,放任自流的部分我们先不用考虑,最后在乘上某个阶乘就好了。

那么我们就不用考虑,随意选择而占用后面完美候选数的情况。

而只用考虑完美位之间的影响:

$f[i][j][0/1][0/1]$为:

$dp$到前$i$个位置,选取了$j$个完美的位置

选或不选$i$和选或不选$i+1$。

那么转移如下:

(1)作为完美位

- (1.1)选择$i-1$

  $f[i][j][0][0]+=f[i-1][j-1][0][0];$
  
  $f[i][j][1][0]+=f[i-1][j-1][0][1];$
  
- (1.1)选择$i+1$

  $f[i][j][0][1]+=f[i-1][j-1][0][0]+f[i-1][j-1][1][0];$
  
  $f[i][j][1][1]+=f[i-1][j-1][0][1]+f[i-1][j-1][1][1];$

(2)不作为完美位

$f[i][j][0][0]+=f[i-1][j][0][0]+f[i-1][j][1][0];$

$f[i][j][1][0]+=f[i-1][j][0][1]+f[i-1][j][1][1];$

当然,在$i=1$和$i=n$的时候是特殊情况:

- $i=1$边界:

啥也不选:$f[1][0][0][0]=1;$

选择$2$:$f[1][1][0][1]=1;$

- $i=n$特殊转移:

那么去掉选择$i+1$的转移就好了。

最终的答案是:

$F(m)=(f[n][m][0][0]+f[n][m][1][0])*(n-m)!$

然后弄个二项式反演即可:

**Code:**

代码里为了方便,把最后两维压了一下。

其实是可以滚动数组的,但是我很懒……

```cpp
#include<algorithm>
#include<cstdio>
#define mod 1000000007
#define MaxN 2050
using namespace std;
int n,m;
long long f[MaxN][MaxN][4],F[MaxN],
          fac[MaxN],inv[MaxN];
long long C(int n,int m)
{return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int main()
{
  scanf("%d%d",&n,&m);
  fac[0]=inv[0]=inv[1]=1;
  for (int i=2;i<=n;i++)
    inv[i]=inv[mod%i]*(mod-mod/i)%mod;
  for (int i=1;i<=n;i++){
    fac[i]=fac[i-1]*i%mod;
    inv[i]=inv[i]*inv[i-1]%mod;
  }
  f[1][0][0]=f[1][1][1]=1;
  for (int i=2;i<n;i++){
    f[i][0][0]=1;
    for (int j=1;j<=i;j++){
      f[i][j][0]=(f[i-1][j-1][0]+f[i-1][j][0]+f[i-1][j][2])%mod;
      f[i][j][2]=(f[i-1][j-1][1]+f[i-1][j][1]+f[i-1][j][3])%mod;
      f[i][j][1]=(f[i-1][j-1][0]+f[i-1][j-1][2])%mod;
      f[i][j][3]=(f[i-1][j-1][1]+f[i-1][j-1][3])%mod;
    }
  }
  f[n][0][0]=1;
  for (int j=1;j<=n;j++){
    f[n][j][0]=(f[n-1][j-1][0]+f[n-1][j][0]+f[n-1][j][2])%mod;
    f[n][j][2]=(f[n-1][j-1][1]+f[n-1][j][1]+f[n-1][j][3])%mod;
  }for (int i=0;i<=n;i++)
    F[i]=(f[n][i][0]+f[n][i][2])*fac[n-i]%mod;
  long long ans=0;
  for (int i=m;i<=n;i++){
    long long sav=C(i,m)*F[i]%mod;
    ans=(ans+ ((i-m)&1 ? mod-sav:sav))%mod;
  }printf("%I64d",ans);  
  return 0;
}
```

---

## 作者：Maniac丶坚果 (赞：6)

【题目大意】

对于一个1-n的排列，定义一个位置是好的位置，当且仅当这个位置是左数第i个，并且这个位置的数是i - 1或i + 1.


给定n，k，求出好的位置恰好有k个的排列个数。由于结果可能很大，请将答案对1e9 + 7取模。


【样例输入】


7 4

【样例输出】


328

【解析】


十分巧妙的DP。


核心思想： “恰好有k个”不好推，那么就推前缀（比k个更多）把。


这个时候，我们可以先选定k个位置是'好的位置' ，无视剩下的数，让他们随意排列。


此时的DP方程是这样的**（个人认为其实也不是那么好想）**


dp[i][j][k = 0|1][l = 0|1] 表示前i个位置里选j个好的位置，i和i+1是否是否再前面被拿掉过的方案数。
三种需要转移的状态：


dp[i][j][l][0] += dp[i - 1][j][k][l] // 第i个位置作为暂时无视的位置

if (k == 0) dp[i][j+1][l][0] += dp[i - 1][j][k][l]//第i个位置放i-1

if (i != n) dp[i][j+1][l][1] += dp[i-1][j][k][l]//第i个位置放i+1


然后，由于每个位置剩下的数可以乱排，所以还要乘上 一个阶乘。


我们这里推出来的超过j个的数目是：Ans[j] =  dp[n][j]$\sum_{k=0}^1 \sum_{l=0}^1 \times (n-j)!$


此时注意答案显然不是Ans[j] - Ans[j + 1].


可以发现，每一个好的位置有j+1个的排列，再算有j个的排列时都会被算j+1次（因为对于这个j+1排列，每一个好位置被无视掉以后都会构成一个j排列）


同理，每一个好的位置有j+2个的排列则会再算j个的排列时重复计算$C_{j+2}^2$次


.... 每一个好的位置有j个的排列会在算i(i < j)的排列时被计算$C_j^{j-i}$（即$C_j^i$)次。


所以，对于Ans[k+1] 到 Ans[n]，进行上述容斥操作，方可得到答案。


代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2005;
const ll mo = (ll) 1e9 + 7;
ll dp[maxn][maxn][2][2],n,k;
ll c[maxn][maxn],ans[maxn],fac[maxn];
//dp[i][j][k][l]代表前i个位置有j个good position,i,i+1是否被使用 
int main()
{
    scanf("%d%d",&n,&k);
    for (int i=1;i<=n;++i)
    {
        c[i][0]=c[i][i]=1LL;
        for (int j=1;j<=i-1;++j)
        {c[i][j]=(c[i][j]+c[i-1][j]+c[i-1][j-1])%mo;}
     } 
     fac[0] = fac[1] = 1LL;
     for (int i = 2; i <= 2001; ++i) fac[i] = (fac[i - 1] * i * 1LL) % mo;
    // for (int i = 1000; i >= 990; --i) printf("%lld ",fac[i]);
     dp[0][0][1][0]=1;    
     for (int i=1;i<=n;++i)
     {
         for (int j=0;j<=i-1;++j)
         for (int now=0;now<2;++now)
         for (int ne=0;ne<2;++ne)
         {
             dp[i][j][ne][0]=(dp[i][j][ne][0]+dp[i-1][j][now][ne])%mo;
             if (!now) dp[i][j+1][ne][0]=(dp[i][j+1][ne][0]+dp[i-1][j][now][ne])%mo;
             if (i<n) dp[i][j+1][ne][1]=(dp[i][j+1][ne][1]+dp[i-1][j][now][ne])%mo;
         }
     }
     for (int i=0;i<=n;++i)
     {
         for (int now=0;now<2;++now)
         for (int ne=0;ne<2;++ne)
         ans[i]=(ans[i]+dp[n][i][now][ne])%mo;
         ans[i] = ans[i] * fac[n - i] % mo;
     } 
//     for (int i=1;i<=n;++i) printf("%lld ",ans[i]);
     int flag=-1;
 
     for (int i=k+1;i<=n;++i)
     {
         ans[k]=(ans[k]+flag*c[i][k]*ans[i]+mo)%mo;
         //对于每一个ans[i],我们要容斥处理。 
         flag*=-1;
     }
     printf("%lld\n",ans[k]);
}
```

---

## 作者：NaCly_Fish (赞：5)

[题目链接](https://www.luogu.com.cn/problem/CF285E)

update：笔误已修复。

这题的组合推导部分其它题解都讲了，这里直接略过。我们有一组递推式
$$\begin{cases} a_{i,j}=a_{i-1,j-1}+a_{i-1,j}+c_{i-1,j} \\ b_{i,j}=a_{i-1,j-1}+c_{i-1,j-1} \\c_{i,j}=b_{i-1,j-1}+b_{i-1,j}+d_{i-1,j} \\ d_{i,j}=b_{i-1,j-1}+d_{i-1,j-1} \end{cases}$$

有边界条件 $a_{0,0}=a_{1,0}=b_{1,1}=1$，我们想求 $a_{n,j}+c_{n,j} \ (j \in[m,n])$ 的值。答案即为
$$\sum_{j=m}^n \binom jm  (-1)^{j-m}(n-j)!(a_{n,j}+c_{n,j})$$

我们直接建立二元 GF，解线性方程组
$$\begin{cases}A=(xy+x)A+xC+1-xy \\ B=xy(A+C) \\ C=(xy+x)B+xD \\ D=xy(B+D) \end{cases}$$
直接解得
$$A+C=\frac{1-xy}{(1+xy)(1-x-2xy+x^2y^2)}$$
别看分母中 $y$ 最高到了三次项，但这些根都可以用不超过二次式来表示，而且其中两个根的常数项都为零。而 $x^n$ 项中 $y$ 的次数是不超过 $n$ 的，由此我们可以发现
$$[x^n](A+C) \equiv \frac{\left( 1+2y+\sqrt{1+4y}\right)^{n+1}}{2^{n+1}(1+4y)} \pmod{y^{n+1}}$$
这是可以整式递推的，具体来说设 $F=(1+2x+\sqrt{1+4x})^n$，它满足 ODE
$$x(1+4x)F''+(1-2n+x(6-8n))F'=2n(1-2n)F$$
直接递推计算，时间复杂度 $\Theta(n)$。（目前最优解）

ps：这里 $F$ 的递推式阶数甚至只有 $1$，也就是说它还是超几何的。

---

## 作者：mqxmm (赞：4)

[$\texttt{Link}$](https://www.luogu.com.cn/problem/CF285E)  

## 前置知识

- 二项式反演  

## $\texttt{Solution}$

对于这一类跟 **数学** 有关系，又是求 **恰好** 的问题，一般都需要使用 **二项式反演**。  

同样地，这道题我们也考虑二项式反演。  

记 $G(i)$ 表示恰好有 $i$ 个数是完美数的方案数，$F(i)$ 表示选定 $i$ 个数为完美数时其它位置乱选的 **总方案数**。  

所以  
$$
F(i) = \sum\limits_{j = i}^n \dbinom j i G(j)
$$

由二项式反演得  
$$
G(i) = \sum\limits_{j = i}^n {(-1)}^{j - i} \dbinom j i F(j)
$$

由上述定义可知，我们需要计算的答案就是 $G(k)$。 $($ $k$ 是题意翻译中的 $m$ $)$  
现在只需要求出 $F$ 的值就可以计算 $G(k)$ 了。  

定义 $f_{i, j, 0/1, 0/1}$ 表示 $1 \sim i$ 的 **位置** 中，选择了 $j$ 个完美 **位置**，**数 $i$** 选择的情况，**数 $i + 1$** 选择的情况。$($ $0$ 表示没有选择，$1$ 表示选择了 $)$  
**特殊说明**：完美数所在的位置就是完美位置，因此有 $k$ 个完美数就有 $k$ 个完美位置，它们的个数是相等的。  
**注意**：如果定义为 $i - 1$ 的选择情况，那么在状态转移的时候 $i - 2$ 是对 $i$ 没有贡献的，所以没有必要定义 $i - 1$ 的选择情况；相反，$i + 1$ 的选择情况是必要的。  

那么 $F(i)$ 的值就是 $(f_{n, i, 0, 0} + f_{n, i, 1, 0}) \times (n - i)!$。

考虑状态转移：

1. 位置 $i$ 填数 $i - 1$，提供 $1$ 的贡献，此时需要保证数 $i - 1$ 在之前没有被选择，数 $i + 1$ 当前不能被选择  
	- $f_{i, j, 0, 0} = f_{i - 1, j - 1, 0, 0}$  
	- $f_{i, j, 1, 0} = f_{i - 1, j - 1, 0, 1}$  
2. 位置 $i$ 填数 $i + 1$，提供 $1$ 的贡献，此时需要保证数 $i + 1$ 在之前没有被选择，数 $i - 1$ 之前的选择情况不定
	- $f_{i, j, 0, 1} = f_{i - 1, j - 1, 0, 0} + f_{i - 1, j - 1, 1, 0}$  
	- $f_{i, j, 1, 1} = f_{i - 1, j - 1, 0, 1} + f_{i - 1, j - 1, 1, 1}$  
3. 位置 $i$ 不填数，就是不让它成为完美位置  
	- $f_{i, j, 0, 0} = f_{i - 1, j, 0, 0} + f_{i - 1, j, 1, 0}$  
	- $f_{i, j, 1, 0} = f_{i - 1, j, 0, 1} + f_{i - 1, j, 1, 1}$  

当然，最后每个 $f$ 的值就是每种情况给它的贡献的和。  

初始状态：$f_{1, 0, 0, 0} = 1, f_{1, 1, 0, 1} = 1$。

## $\texttt{code}$

```cpp
#include <cstdio>

#define int long long
#define uint unsigned int

int rint()
{
	int x = 0, fx = 1; char c = getchar();
	while (c < '0' || c > '9') { fx ^= (c == '-'); c = getchar(); }
	while ('0' <= c && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	if (!fx) return -x;
	return x;
}

const int mod = 1e9 + 7;
const int MAX_n = 1e3;

namespace Math
{
	const int mx = MAX_n;

	int f[mx + 5];
	int inv[mx + 5];

	void init(int up)
	{
		inv[1] = inv[0] = f[0] = 1 % mod;
		for (int i = 1; i <= up; i++)
			f[i] = f[i - 1] * i % mod;
		for (int i = 2; i <= up; i++)
			inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		for (int i = 2; i <= up; i++)
			inv[i] = inv[i - 1] * inv[i] % mod;
	}

	int A(int n, int m) { return (n < m || m < 0) ? 0 : (f[n] * inv[n - m] % mod); }
	int C(int n, int m) { return A(n, m) * inv[m] % mod; }
} using namespace Math;

int n, k;
int dp[MAX_n + 5][MAX_n + 5][2][2];

int F(int x)
{
	return (dp[n][x][0][0] + dp[n][x][1][0]) % mod * f[n - x] % mod;
}

int G(int x)
{
	int res = 0;
	for (int i = x; i <= n; i++)
	{
		int now = C(i, x) * F(i) % mod;
		if ((i - x) & 1) res = (res - now + mod) % mod;
		else res = (res + now) % mod;
	}
	return res;
}

signed main()
{
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
	n = rint(), k = rint(); init(n);
	dp[1][0][0][0] = dp[1][1][0][1] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (j)
			{
				dp[i][j][0][0] = (dp[i][j][0][0] + dp[i - 1][j - 1][0][0]) % mod;
				dp[i][j][1][0] = (dp[i][j][1][0] + dp[i - 1][j - 1][0][1]) % mod;
				dp[i][j][0][1] = (dp[i][j][0][1] + dp[i - 1][j - 1][0][0] + dp[i - 1][j - 1][1][0]) % mod;
				dp[i][j][1][1] = (dp[i][j][1][1] + dp[i - 1][j - 1][0][1] + dp[i - 1][j - 1][1][1]) % mod;
			}
			dp[i][j][0][0] = (dp[i][j][0][0] + dp[i - 1][j][0][0] + dp[i - 1][j][1][0]) % mod;
			dp[i][j][1][0] = (dp[i][j][1][0] + dp[i - 1][j][0][1] + dp[i - 1][j][1][1]) % mod;
		}
	}
	printf("%lld\n", G(k));
	return 0;
}

```


---

## 作者：是个汉子 (赞：4)

我这里和别人不一样的是取模加和乘（我觉得这个东西很好，可能会快一点？

### Solution

首先，它让我们算方案数，所以我们设一个数组 $F(x)$ 表示完美数恰好为 $x$ 的排列数，又由这熟悉的**恰好**，可以再设一个数组 $G(x)$ 表示完美数**指定**为 $x$ 的排列数，那么~~显然~~可以得到： $G(m)=\sum\limits_{i=m}^n\binom imF(i)$ ，来一个正常的二项式反演就可以得到 $F(m)=\sum\limits_{i=m}^n(-1)^{i-m}\binom imG(i)$ ，现在考虑如何求出 $G(x)$ 。

因为每一位的完美情况只和前后有关系，所以我们可以设 $f_{i,j,0/1,0/1}$ 来表示当前位是 $i$ ，有 $j$ 个完美数， $i$ 是/否被选， $i+1$ 是/否被选的方案数。

现在考虑状态转移方程：

选择第 $i$ 位为完美位，并让 $i-1$ 在第 $i$ 位，只需要保证 $i-1$ 一定没被选。
$$
f_{i,j,0,0}=f_{i,j,0,0}+f_{i-1,j-1,0,0},f_{i,j,1,0}=f_{i,j,1,0}+f_{i-1,j-1,0,1}
$$
选择第 $i$ 位为完美位，并让 $i+1$ 在第 $i$ 位，只需要保证 $i+1$ 一定没被选。
$$
f_{i,j,0,1}=f_{i,j,0,1}+f_{i-1,j-1,0,0}+f_{i-1,j-1,1,0},f_{i,j,1,1}=f_{i,j,1,1}+f_{i-1,j-1,0,1}+f_{i-1,j-1,1,1}
$$
不选择第 $i$ 位为完美位
$$
f_{i,j,0,0}=f_{i,j,0,0}+f_{i-1,j,0,0}+f_{i-1,j,1,0},f_{i,j,1,0}=f_{i,j,1,0}+f_{i-1,j,0,1}+f_{i-1,j,1,1}
$$
初始状态： $f_{1,0,0,0}=1,f_{1,1,0,1}=1$ 

因为第 $n$ 位只能选择 $n-1$ 为完美数，所以需要重新转移或者减去 $n+1$ 的部分。我选择的重新转移。

现在就能得到 $G(m)=(f_{n,m,0,0}+f_{n,m,1,0})\times(n-m)!$ ，其中 $(n-m)!$ 是剩下 $n-m$ 个位置随便排的全排列。

最后反演即可。

### 代码

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long

using namespace std;
const int N=2050,mod=1e9+7;
int n,m;
ll f[N][N][2][2],G[N],fac[N],inv[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

ll mul(ll a,ll b){return a*b%mod;}
ll add(ll a,ll b){return a+b>=mod?a+b-mod:a+b;}

inline void init(){
    fac[0]=inv[0]=inv[1]=1;
    for(int i=2;i<=n;i++)
        inv[i]=mul(inv[mod%i],mod-mod/i);
    for(int i=1;i<=n;i++){
        fac[i]=mul(fac[i-1],i);
        inv[i]=mul(inv[i],inv[i-1]);
    }
}

ll C(int n,int m){
    if(n<m) return 0;
    return mul(fac[n],mul(inv[n-m],inv[m]));
}

int main(){
    n=read();m=read();
    init();
    f[1][0][0][0]=f[1][1][0][1]=1;
    for(int i=2;i<=n;i++){
        f[i][0][0][0]=1;
        for(int j=1;j<=i;j++){
            f[i][j][0][0]=add(f[i-1][j-1][0][0],add(f[i-1][j][0][0],f[i-1][j][1][0]));
            f[i][j][0][1]=add(f[i-1][j-1][0][0],f[i-1][j-1][1][0]);
            f[i][j][1][0]=add(f[i-1][j-1][0][1],add(f[i-1][j][1][1],f[i-1][j][0][1]));
            f[i][j][1][1]=add(f[i-1][j-1][0][1],f[i-1][j-1][1][1]);
        }
    }
    f[n][0][0][0]=1;
    for(int i=1;i<=n;i++){
        f[n][i][0][0]=add(f[n-1][i-1][0][0],add(f[n-1][i][0][0],f[n-1][i][1][0]));
        f[n][i][1][0]=add(f[n-1][i-1][0][1],add(f[n-1][i][0][1],f[n-1][i][1][1]));
    }
    //上面是重新转移的n
    for(int i=0;i<=n;i++)
        G[i]=mul(add(f[n][i][0][0],f[n][i][1][0]),fac[n-i]);
    ll ans=0;
    for(int i=m;i<=n;i++){
        ll res=mul(C(i,m),G[i]);
        ans=add(ans,(i-m)&1?mod-res:res);
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：shao0320 (赞：3)

#### CF285E Positions in Permutations

考虑位置为左部，排列中的数为右部进行匹配，则我们要求的就是匹配恰好为$k$个的方案数。

~~由经验可得~~，恰好可以用至少来推，因为至少只有一个限制条件。

考虑$dp$，设$F(i)$表示至少有$i$个匹配，其它边随便连的方案数，那么这个东西可以$dp$来求，考虑这个$dp$模型：

![](https://cdn.luogu.com.cn/upload/image_hosting/l29hy0cx.png)

由于黑边红边互不影响，因此考虑先搞黑边再搞红边。

设$f(i,j,0/1)$表示，考虑了前$i$条边，选了$j$条边，第$i$条边选没选，简单转移即可。

那么考虑通过$F$来求出$G$，$G(i)$表示恰好$i$组的方案数。

注意到$f(i,j,0/1)$时会算重的，但同时它又没计算其它的随便连得那些边，运用简单组合数学知识即可得知：
$$
\sum_{j=k}^{n}G(j)\times\dbinom{j}{i} =F(k)\times (n-k)!
$$


二项式反演即可：
$$
G(j)=\sum_{j=k}^{n}(-1)^{j-i}\times F(i)\times \dbinom{j}{i}
$$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2005
#define int long long
#define mod (long long)(1e9+7)
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,k,f[N][N][2],C[N][N],fac[N];
signed main()
{
	n=read();k=read();fac[0]=1;
	for(int i=0;i<=n;i++)
	{
		C[i][0]=1;if(i!=0)fac[i]=fac[i-1]*i%mod;
		for(int j=1;j<=i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1],C[i][j]%=mod;
	}
//	for(int i=0;i<=n;i++)
//	{
//		for(int j=0;j<=i;j++)
//		{
//			printf("%lld %lld %lld\n",i,j,C[i][j]);
//		}
//	}
	f[0][0][0]=1;
	for(int i=1;i<=2*n-2;i++)
	{
		for(int j=0;j<=n;j++)
		{
			f[i][j][0]+=f[i-1][j][0]+f[i-1][j][1];
			if(j&&i!=n)f[i][j][1]=f[i-1][j-1][0];
			if(j&&i==n)f[i][j][1]=f[i-1][j-1][0]+f[i-1][j-1][1];
			f[i][j][0]%=mod;f[i][j][1]%=mod;
		}
	}
	//for(int i=0;i<=n;i++)
	//{
	//	printf("%d %d\n",f[2*n-2][i][0],f[2*n-2][i][1]);
	//}
	int poww=1,ans=0;
	for(int i=k;i<=n;i++)
	{
		ans+=poww*((f[2*n-2][i][0]+f[2*n-2][i][1])*fac[n-i]%mod)*C[i][k]%mod;
		poww*=-1;ans%=mod;ans=(ans+mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：zhendelan (赞：3)

称一个$1\sim n$的排列的完美数为有多少个$i$满足$|P_i-i|=1$  
求有多少个长度为$n$的完美数恰好为$m$的排列。  

题目提示了恰好，所以可以用广义容斥原理。  

如果不知道可以去看我写的另外一篇 ：  
[广义容斥原理](https://www.luogu.com.cn/blog/13197/guang-yi-rong-chi-yuan-li-yu-er-xiang-shi-fan-yan)

假设完美数至少为$x$的方案数为$F(x)$。  

那么答案$G(m)=\sum_{i=m}^n (-1)^{i-m}*C_i^m*F(i)$  

现在的问题就是求$F(x)$。  

设$f[i][j][0/1][0/1]$为选完前$i$个，完美数为$j$,$i$和$i+1$是否选了的方案数。  

那么当$i$放$i-1$，方程如下
：($upd$就是$x+=y$)  
```cpp
for(int k=0;k<2;k++)
  upd(f[i][j][k][0],f[i-1][j-1][0][k]);
```  
$i-1$一定没选就行。  

那么当$i$放$i+1$，方程如下：  
```cpp
for(int k=0;k<2;k++)
	for(int l=0;l<2;l++)
	upd(f[i][j][k][1],f[i-1][j-1][l][k]);
```
$i+1$选了就行。  

如果$i$放其他数，就是这样：
```cpp
for(int k=0;k<2;k++)
	for(int l=0;l<2;l++)
	upd(f[i][j][k][0],f[i-1][j][l][k]);
```  
之前是什么状态都可以。  

注意$i=1$和$i=n$特判。  
即:  
```
f[1][0][0][0] = 1;
f[1][1][0][1] = 1;
```  
最后$F(x)=\sum f[n][x][0/1][0/1]$  

按照上面的式子求答案就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
#define upd(x,y) x=(x+y)%mod
#define mul(x,y) (1LL*x*y%mod)
#define add(x,y) ((x+y)%mod)
const int N = 1020;
int f[2][N][2][2];
int g[N];
int fac[N],inv[N];
int n,m;
int C(int n,int m)
{
	return mul(fac[n],mul(inv[m],inv[n-m])); 
}
int ksm(int a,int b=mod-2)
{
	int ret = 1;
	while(b)
	{
		if(b&1) ret=mul(ret,a);
		a=mul(a,a);
		b>>=1;
	}
	return ret;
}
int main()
{
	scanf("%d%d",&n,&m);
	f[1][0][0][0] = 1;
	f[1][1][0][1] = 1;
	fac[0] = 1;
	for(int i=1;i<=n;i++)
	  fac[i] = mul(fac[i-1],i);
	inv[n] = ksm(fac[n]);
	for(int i=n-1;i>=0;i--)
	  inv[i] = mul(inv[i+1],(i+1));
	for(int cur=2;cur<=n;cur++)
	{
		int i = cur & 1;
		for(int j=0;j<=n;j++)
		{
		for(int l=0;l<2;l++)
		  for(int k=0;k<2;k++)
		    f[i][j][k][l] = 0;
		for(int k=0;k<2;k++)
		  upd(f[i][j][k][0],f[i^1][j-1][0][k]);
		if(cur!=n)
		for(int k=0;k<2;k++)
		  for(int l=0;l<2;l++)
		  upd(f[i][j][k][1],f[i^1][j-1][l][k]);
		for(int k=0;k<2;k++)
		  for(int l=0;l<2;l++)
		  upd(f[i][j][k][0],f[i^1][j][l][k]);
		}
	}
	for(int j=m;j<=n;j++)
	 for(int k=0;k<2;k++)
	     upd(g[j],f[n&1][j][k][0]);
	for(int j=m;j<=n;j++)
	  g[j] = mul(g[j],fac[n-j]);
	int ans = 0;
	for(int i=0;i+m<=n;i++)
	{
		int j = i+m;
		if(i&1)
		  upd(ans,-mul(C(j,m),g[j]));
		else
		  upd(ans,mul(C(j,m),g[j]));
	}
	upd(ans,mod);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：LuoShaoyinn (赞：1)

这一题本来应该是一个容斥（二项式反演）的题目，但是我不怎么会容斥，于是搞了一种非常奇怪的东西出来。  
首先这题肯定是要 DP 的，于是按照题目直接设计了 DP 定义：  
$f(i,j,mask)$: 做到第 $i$ 位，已经**恰好**有 $j$ 个完美匹配，上一位、当前位、下一位是否已经填数记录在 $mask( mask \in [0,8) )$。

 * 若当前位不产生新的匹配，则直接累加 $f(i-1, j, mask')$ 状态：
 $ \forall_{mask} f(i-1,j - 1,mask) \to f(i,j,mask >> 1) $ 
 * 若当前位在前一位产生新的匹配：
 $ \forall_{mask} f(i-1,j - 1,mask) \to f(i,j,mask >> 1 )  (mask \operatorname{and} 2 == 0) $
 * 若当前位在后一位产生新的匹配：
 $ \forall_{mask} f(i-1,j - 1,mask) \to f(i,j,mask >> 1 \operatorname{or} 4) $

再令 $g(x)$ 表示匹配数总共为 $x$ 有几种方案，则根据定义有 $ g(x) = (n-x)! \times \sum_{mask < 4} f(n,x,mask) $  
写完后发现算出来的方案数比 $n!$ 还大，然后发现有许多情况都算重复了。
具体地，若一个方案有 $x+k$ 个完美匹配，那么这一种情况会在 $g(x)$ 中被计算时会先选择 $x$ 个位置强制匹配，然后再 $(n-x)$ 全排。因此，这一个方案计算 $C_{x+k}^x$ 次。假设我们以及求出了真正的 $g(x+k)$， 那么只需要令 $g(x) \leftarrow g(x) - g(x+k) \times C_{x+k}^x$ 就可以了。

```cpp
// Problem: CF285E Positions in Permutations
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF285E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Started coding at 2021-12-18 18:42:59
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long
using namespace std;

const int MAXN = 1005;
const int MOD  = 1e9 + 7;
const int INF  = 0x3f3f3f3f;
int inline read(){
	int x = 0, f = 0; char ch = getchar();
	while(ch < '0' || ch > '9') f ^= (ch == '-'), ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

int n, m, fac[MAXN], ifac[MAXN];
int f[MAXN][MAXN][8], g[MAXN];
// 0 0 0
// | | +- is pre position fixed
// | +--- is cur position fixed
// +----- is nxt position fixed

int inline qpow(int x, int y) {
	int ret = 1;
	while(y) {
		if(y & 1) ret = ret * x % MOD;
		y >>= 1; x = x * x % MOD;
	}
	return ret;
}
int inline C(int n, int m) {
	return fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;
}

signed main(){
	n = read(); m = read(); f[0][0][3] = fac[0] = 1;
	
	for(int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % MOD;
	ifac[n] = qpow(fac[n], MOD - 2);
	for(int i = n - 1; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
	
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j <= i; ++j) {
			for(int k = 0; k < 8; ++k) f[i][j][k >> 1] += f[i - 1][j][k];
			if(!j) continue;
			
			// place in the prevent bit
			for(int k = 0; k < 8; ++k) if((k & 2) == 0) 
				f[i][j][(k >> 1) | 1] += f[i - 1][j - 1][k];
			// place in the next bit
			for(int k = 0; k < 8; ++k) 
				f[i][j][(k >> 1) | 4] += f[i - 1][j - 1][k];
			
			for(int k = 0; k < 8; ++k) f[i][j][k] %= MOD;
			
			// fprintf(stderr, "( ");
			// for(int k = 0; k < 8; ++k)
				// fprintf(stderr, "%d ", f[i][j][k]);
			// fprintf(stderr, ") ");
		}
		// fprintf(stderr, "\n");
	}
	
	for(int i = 0; i <= n; ++i) for(int k = 0; k < 4; ++k) g[i] += f[n][i][k];
	for(int i = 0; i <= n; ++i) g[i] = g[i] * fac[n - i] % MOD;
	
	// for(int i = 0; i <= n; ++i) fprintf(stderr, "cnt=%d ans=%lld\n", i, g[i]);
	for(int i = n; i >= 0; --i) {
		for(int j = i + 1; j <= n; ++j)
			 g[i] = (MOD + g[i] - g[j] * C(j, i) % MOD ) % MOD;
	}

	printf("%lld\n", g[m]);
	return 0;
}
```

其实我感觉这东西本质也是容斥，但是我太菜了，不知道这是哪一条公式推出来的结果，因为 $g(x)$ 直接求出来的时候似乎没有确切的组合意义。

---

## 作者：tzc_wk (赞：1)

UPD 2021.4.9：修了个 typo

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/285/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF285E)

~~这是一道 *2600 的 D2E，然鹅为啥我没想到呢？wtcl/dk~~

首先第一步我就没想到/kk，看到“恰好”二字我们可以想到一个东西叫做**二项式反演**（qwq 这个套路在刷多项式题时经常见到，可咋换个场景就想不到了呢？显然是我多项式白学了/doge）。我们设 $f_k$ 表示恰好 $k$ 个完美数的排列个数，$g_k$ 表示**钦定 $k$ 个位置**满足 $|p_i-i|=1$，剩下随便乱填的方案数，那么显然对于某个有 $x$ 个完美位置的排列，它被计入 $g_y(y<x)$ 的次数为 $\dbinom{x}{y}$。

也就是说 $g_k=\sum\limits_{i=k}^nf_i\dbinom{i}{k}$。反演一下可得 $f_k=\sum\limits_{i=k}^n(-1)^{i-k}g_i$。

故我们只需求出 $g_i$ 就行了。

怎么求 $g_i$ 呢？这时候就要用到 DP 了，我们设 $dp_{i,j,x,y}$ 表示填好了前 $i$ 个位置，钦定了 $j$ 个位置满足 $|p_i-i|=1$，$x$ 表示 $i$ 是否被选择，$y$ 表示 $i+1$ 是否被选择（这一步我又没想到，看来我 DP 也白学了/ww）。转移就分 $i$ 不是被钦定为“完美位置”，$p_i=i+1,p_i=i-1$ 三种情况转移即可，具体来说：

- $dp_{i,j,0,0}=dp_{i-1,j,0,0}+dp_{i-1,j,1,0}+dp_{i-1,j-1,0,0}$（放 $i-1$ 或者不被钦定为完美位置）
- $dp_{i,j,0,1}=dp_{i-1,j-1,0,0}+dp_{i-1,j-1,1,0}$（$y=1$，只能放 $i+1$）
- $dp_{i,j,1,0}=dp_{i-1,j,0,1}+dp_{i-1,j,1,1}+dp_{i-1,j-1,0,1}$（放 $i-1$ 或者不被钦定为完美位置）
- $dp_{i,j,1,1}=dp_{i-1,j-1,0,1}+dp_{i-1,j-1,1,1}$（$y=1$，只能放 $i+1$）

初始 $dp_{1,0,0,0}=dp_{1,1,0,1}=1$。

最后 $g_k=(dp_{n,k,0,0}+dp_{n,k,1,0})·(n-k)!$（$n+1$ 不能被选择），时间复杂度 $n^2$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1000;
const int MOD=1e9+7;
int n,m,dp[MAXN+5][MAXN+5][2][2];
int fac[MAXN+5],ifac[MAXN+5];
void add(int &x,int y){x+=y;if(x>=MOD) x-=MOD;}
int binom(int x,int y){return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;}
int main(){
	scanf("%d%d",&n,&m);dp[1][1][0][1]=dp[1][0][0][0]=1;
	fac[0]=1;ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i-1]*ifac[i]%MOD;
	for(int i=2;i<=n;i++) for(int j=0;j<=i;j++){
		if(j){
			add(dp[i][j][0][0],dp[i-1][j-1][0][0]);
			add(dp[i][j][1][0],dp[i-1][j-1][0][1]);
			add(dp[i][j][0][1],dp[i-1][j-1][0][0]);
			add(dp[i][j][0][1],dp[i-1][j-1][1][0]);
			add(dp[i][j][1][1],dp[i-1][j-1][0][1]);
			add(dp[i][j][1][1],dp[i-1][j-1][1][1]);
		}
		add(dp[i][j][0][0],dp[i-1][j][0][0]);
		add(dp[i][j][0][0],dp[i-1][j][1][0]);
		add(dp[i][j][1][0],dp[i-1][j][0][1]);
		add(dp[i][j][1][0],dp[i-1][j][1][1]);
	} int ans=0;
	for(int i=m;i<=n;i++){
		int ways=1ll*(dp[n][i][0][0]+dp[n][i][1][0])*fac[n-i]%MOD;
		if((i-m)&1) ans=(ans-1ll*ways*binom(i,m)%MOD+MOD)%MOD;
		else ans=(ans+1ll*ways*binom(i,m))%MOD;
	} printf("%d\n",ans);
	return 0;
}
```


---

## 作者：chenzida (赞：1)

首先，这道题我们强制给连边安排顺序，手玩可以发现，产生贡献的连边有 $2n-2$ 中，我们把它强制化为 $n-1$ 条和 $n-1$ 条，然后发现这两种边互补干扰。于是可以强制把一个放到另一个前面，然后就可以 $dp$ 了。

设 $dp[0/1][i][j]$ 为考虑前 $i$ 条边，选了 $j$ 条边，且第 $i$ 条选/没选的方案数。然后注意特判断点，也就是判断 `i==n`。

我们会发现 $f$ 求的是至少，我们要把它转化为恰好，进行二项式反演即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int NR=2e3+10;
const int mod=1e9+7;
void Min(int& x,int y){x=min(x,y);}
void Max(int& x,int y){x=max(x,y);}
int n,m;
int fac[NR],inv[NR];
int ksm(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)res=(res*a)%mod;
		a=(a*a)%mod;b>>=1;
	}
	return res;
}
int C(int a,int b){return fac[b]*inv[b-a]%mod*inv[a]%mod;}
int dp[2][NR][NR],F[NR];
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),m=read();fac[0]=inv[0]=inv[1]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<=n;i++)inv[i]=ksm(fac[i],mod-2);
	dp[0][0][0]=1;
	for(int i=1;i<=n*2-2;i++)for(int j=0;j<=n;j++)
	{
		dp[0][i][j]=(dp[0][i-1][j]+dp[1][i-1][j])%mod;
		if(j&&i!=n)dp[1][i][j]=dp[0][i-1][j-1];
		if(j&&i==n)dp[1][i][j]=(dp[0][i-1][j-1]+dp[1][i-1][j-1])%mod;
	}
	for(int i=0;i<=n;i++)F[i]=dp[0][n*2-2][i]+dp[1][n*2-2][i];
	int fy=1,ans=0;
	for(int i=m;i<=n;i++)
	{
		ans=(ans+F[i]*fy*fac[n-i]%mod*C(m,i))%mod;
		ans=(ans+mod)%mod;fy*=-1;
	}printf("%lld\n",ans);
	return 0;
}


---

## 作者：MoonPie (赞：1)

真是一道堪比 [**CF840C** On the Bench](https://www.luogu.com.cn/problemnew/show/CF840C) 的好题！

---

## 题意


定义一个 $1$  ~  $n$ 的排列的完美值为下标 $i$ 满足 $|P_i-i|=1$ 的个数.

给你一个 $n,m$ ，$(1\le n\le 1000,0\le m \le n)$ ,

让你求出 完美值恰好是 $m$ 的排列的个数，输出答案对 $10^9+7$ 取模的值.


## 题解


出现“恰好”这样的字眼，

可以用 **[二项式反演](https://www.luogu.com.cn/paste/p14void3)** 转化为对 **“至少”** 求解.

所以现在我们考虑至少有 $m$ 个数在好位置上的方案数，记这个方案数为 $f_m$

然后，让我们考虑一下答案，记为 $g_m$ ，表示恰好有 $m$ 个数在好位置上的排列数，与 $f_m$ 的关系.

很显然有，
$$
f_m = \sum_{i=m}^n{\binom{n}{i}g_i}
$$
所以计算完 $f_m$ 后，我们只要二项式反演一下就好了.

---

考虑计算 $f_m$，

如果我们计算了有 $m$ 个数在好位置上的 **方案数** ，然后乘一个 $(n-m)!$ 就是 $f_m$

考虑一个 $DP$ ，设 $dp_{i,j}$ 表示前 $i$ 个位置上，有 $j$ 个数在好位置上的方案数.

但是这样并不能很好地表示状态，因为每加进来一个位置，我们还需要知道 $i-1$ 和 $i+1$ 有没有被用过.

所以修改状态为 $dp[i][j][0/1][0/1]$ 最后两维分别表示 $i$ 和 $i+1$ 是否用过.

```cpp
    1. 如果 i 作为好位置出现：
        1.1 -> i-1放在i上
            dp[i][j][0][0] += dp[i-1][j-1][0][0]
            dp[i][j][1][0] += dp[i-1][j-1][0][1]
        1.2 -> i+1放在i上
            dp[i][j][0][1] += dp[i-1][j-1][0][0]+dp[i-1][j-1][1][0]
            dp[i][j][1][1] += dp[i-1][j-1][0][1]+dp[i-1][j-1][1][1]
    
    2. 如果 i 不作为好位置：
        dp[i][j][0][0] += dp[i-1][j][1][0] + dp[i-1][j][0][0]
        dp[i][j][1][0] += dp[i-1][j][0][1] + dp[i-1][j][1][1] 
```

然后这道题就做完了.

## Code


```cpp
const int N=1005;
int n,m,dp[N][N][2][2],F[N],G[N],pi[N],inv[N];
int qpow(int x,int y) {
    int res=1;
    for(int i=0;(1<<i)<=y;++i,x=x*x%mod) if(y&(1<<i)) res=res*x%mod;
    return res; 
}
int C(int n,int m) {
    if(m>n || m<0) return 0;
    if(m==n || m==0) return 1;
    return pi[n]*inv[m]%mod*inv[n-m]%mod;
}
void solve() {
    pi[0]=1; for(int i=1;i<N;++i) pi[i]=pi[i-1]*i%mod;
    inv[N-1] = qpow(pi[N-1],mod-2);
    for(int i=N-2;i>=0;--i) inv[i]=inv[i+1]*(i+1)%mod;

    cin>>n>>m;
    
    dp[1][0][0][0] = dp[1][1][0][1] = 1;

    for(int i=2;i<=n;++i) {
        dp[i][0][0][0]=1;
        for(int j=1;j<=i;++j) {
            my_add(dp[i][j][0][0] , dp[i-1][j-1][0][0]);
            my_add(dp[i][j][1][0] , dp[i-1][j-1][0][1]); 
            my_add(dp[i][j][0][1] , dp[i-1][j-1][0][0] + dp[i-1][j-1][1][0]);
            my_add(dp[i][j][1][1] , dp[i-1][j-1][0][1] + dp[i-1][j-1][1][1]);
            my_add(dp[i][j][0][0] , dp[i-1][j][1][0] + dp[i-1][j][0][0]);
            my_add(dp[i][j][1][0] , dp[i-1][j][0][1] + dp[i-1][j][1][1]);
        }
    }

    for(int i=0;i<=n;++i) {
        F[i] = (dp[n][i][1][0]+dp[n][i][0][0])*pi[n-i]%mod;
    }

    int ans=0;
    for(int i=m;i<=n;++i)
    {
        if((i-m)&1)  my_sub(ans , F[i]*C(i,m));
        else my_add(ans , F[i]*C(i,m));
    } 
    cout<<ans<<endl;
}
```

---

## 作者：hegm (赞：0)

### [Positions in Permutations](https://www.luogu.com.cn/problem/CF285E)

提供一种只 dp 的做法。

考虑 $dp$，$dp_{i,j}$ 表示长度为 $i$ 的排列，完美数为 $j$ 个的方案数。

考虑转移，将 $i+1$ 塞入，此时有多种情况。

1. 不交换，那么方案数直接继承 $dp_{i+1,j}\gets dp_{i,j}$。

2. 交换了产生贡献。

3. 交换了不产生贡献。

研究 $2,3$ 会发现决策和 $i$ 的位置相关，因此我们不妨考虑 $i+1$ 和 $i,i-1$ 以及其他的交换关系。
    
所以需要记录 $i,i-1$ 的位置。

$dp_{i,j,0/1/2,0/1}$ 第三维表示 $i$ 在 $i,i-1$ 和其他。第四维表示 $i-1$ 是否在 $i$。

转移巨麻烦。

**开始分讨:**

下方的 `add(a,b)` 函数是指将 $b$ 的值加到 $a$ 上。

大写字母表示位置，小写字母表示元素和值。

- `dp[i][j][0][0]` 转移到其他状态。

	此时序列 $i$ 在 $I$。

    1. $i$ 和 $i+1$ 交换，造成 $2$ 的贡献。
    
    	交换后新的 $I$ 是 $i-1$，$i$ 在 $I-1$。
    
    	`add(dp[i+1][j+2][1][1],dp[i][j][0][0]);`
    2. 和造成贡献的交换，因为 $I$ 位置没有造成贡献，同时 $i$ 没有造成贡献，所以交换过去会减少 $1$ 的贡献，而这样的位置有 $j$ 个。
    
    	由于交换的位置一定不是 $I$，所以新的 $i$ 不在 $I,I-1$。同时 $i$ 的位置不变，因此新的 $i-1$ 在 $I-1$。
    
    	`if(j)add(dp[i+1][j-1][2][0],dp[i][j][0][0]*j);`
    
	 3. 不交换,直接摆烂,那么贡献不变,同时新的 $i$ 在 $I$，$i-1$ 不在 $I$。
     
     `add(dp[i+1][j][0][0],dp[i][j][0][0]);`
     
    4. 和不造成贡献的交换，同时不能和 $i$ 交换，那么有 $i-j-1$ 个可能情况，并且 $i+1$ 的位置不是 $I$，因此贡献不变，新的 $i$ 位置不是 $I,I-1$，并且 $i-1$ 不在 $I$。
    
    `if(i-1-j>0)add(dp[i+1][j][2][0],dp[i][j][0][0]*(i-1-j));`
    
    另外三个主转移同理即可。   
    
### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define N 1005
#define int long long
#define mod 1000000007
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,dp[N][N][3][3];
void add(int &a,int b){a=(a+b%mod)%mod;}
signed main()
{
	n=read();m=read();
	dp[1][0][0][0]=1;
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			add(dp[i+1][j+2][1][1],dp[i][j][0][0]);
			add(dp[i+1][j][0][0],dp[i][j][0][0]);
			if(i-1-j>0)add(dp[i+1][j][2][0],dp[i][j][0][0]*(i-1-j));
			if(j)add(dp[i+1][j-1][2][0],dp[i][j][0][0]*j);
			add(dp[i+1][j+1][1][0],dp[i][j][1][0]);
			add(dp[i+1][j][0][0],dp[i][j][1][0]);
			add(dp[i+1][j][2][1],dp[i][j][1][0]);
			if(i-2-j+1>0)add(dp[i+1][j][2][0],dp[i][j][1][0]*(i-2-j+1));
			if(j)add(dp[i+1][j-1][2][0],dp[i][j][1][0]*(j-1));
			add(dp[i+1][j][0][0],dp[i][j][1][1]);
			add(dp[i+1][j][2][1],dp[i][j][1][1]);
			add(dp[i+1][j][1][0],dp[i][j][1][1]);
			if(i-j>0)add(dp[i+1][j][2][0],dp[i][j][1][1]*(i-j));
			if(j>1)add(dp[i+1][j-1][2][0],dp[i][j][1][1]*(j-2));
			add(dp[i+1][j][0][0],dp[i][j][2][0]);
			add(dp[i+1][j+1][2][1],dp[i][j][2][0]);
			add(dp[i+1][j+1][1][0],dp[i][j][2][0]);
			if(i-j-1>0)add(dp[i+1][j][2][0],dp[i][j][2][0]*(i-j-2));
			if(j)add(dp[i+1][j-1][2][0],dp[i][j][2][0]*j);
			add(dp[i+1][j][0][0],dp[i][j][2][1]);
			add(dp[i+1][j+1][2][1],dp[i][j][2][1]);
			add(dp[i+1][j][1][0],dp[i][j][2][1]);
			if(i-j-1>0)add(dp[i+1][j][2][0],dp[i][j][2][1]*(i-j-1));
			if(j)add(dp[i+1][j-1][2][0],dp[i][j][2][1]*(j-1));
		}
	}
	int ans=0;
	add(ans,dp[n][m][0][0]);
	add(ans,dp[n][m][0][1]);
	add(ans,dp[n][m][1][0]);
	add(ans,dp[n][m][1][1]);
	add(ans,dp[n][m][2][0]);
	add(ans,dp[n][m][2][1]);
	cout<<ans<<"\n";
	return 0;
}


```

事实证明，还是反演和容斥好写。

---

## 作者：FutaRimeWoawaSete (赞：0)

考虑对于原问题，在 $n$ 意义下令 $G(x)$ 表示长为 $n$ 且完美数个数为 $x$ 的排列个数。                        

接着我们定义 $F(x)$ 为在 $n$ 意义下长为 $n$ 且在一开始时指定了 $x$ 个固定完美数其余位置随便放的方案数。

显然 $F(x)$ 会对每个 $G(i),i \geq x$ 重复统计 $\binom{i}{x}$ 次，所以可以得到一个等式：

$F(x) = \sum_{i = x} ^ n \binom{i}{x} G(i)$

可以通过二项式定理变成：         

$G(x) = \sum_{i = x} ^ n (-1) ^ {i - x} \binom{i}{x} F(i)$

考虑快速计算 $F(x)$ 的方法。                

此时需谨慎根据 $F(x)$ 的定义列转移柿，我们显然可以通过枚举哪些位子被固定成了完美数后对答案乘上 $(n - x)!$ 计算，同时一个位子被固定成完美数只与 $(i - 1)$ 和 $(i + 1)$ 有关，从此处设计我们的 dp：

定义 $dp_{i,j,0/1,0/1}$ 表示将前 $i$ 个位置里面固定了 $j$ 个位置变成完美数，其中数 $i$ 在此次抉择之后没选过/选过，数 $i + 1$ 在此次抉择之后没选过/选过的方案数。              

考虑转移，如果当前位置要变成完美数，则：

- 若让 $(i - 1)$ 放到这个位置，那么得保证之前状态里 $(i - 1)$ 未被用过，并且由于我们知道，放数这个过程对于任意数 $i$ 只会放到 $(i - 1)$ 和 $(i + 1)$ 这两个地方，所以若 $i$ 这个位置填了 $(i - 1)$，$(i + 1)$ 这个数肯定未被填过；          

转移方程:

$dp_{i,j,0,0} \leftarrow dp_{i-1,j-1,1,0}$

$dp_{i,j,1,0} \leftarrow dp_{i-1,j-1,1,1}$

- 若让 $(i + 1)$ 放到这个位置，那么不知道 $(i - 1)$ 这个数被放过没有，所以得转移两个状态；

转移方程：

$dp_{i,j,0,1} \leftarrow dp_{i-1,j-1,0,0} + dp_{i - 1,j - 1,1,0}$

$dp_{i,j,1,1} \leftarrow dp_{i-1,j-1,0,1} + dp_{i - 1,j - 1,1,1}$ 

如果当前位置不需变成完美数，显然 $(i + 1)$ 还是不能出现的，所以转移方程：

$dp_{i,j,0,0} \leftarrow dp_{i-1,j,0,0} + dp_{i-1,j,1,0}$

$dp_{i,j,1,0} \leftarrow dp_{i-1,j,0,1} + dp_{i-1,j,1,1}$

最后反演求出 $G(k)$ 即可。

时间复杂度 $O(n^2)$。



---

## 作者：MCAdam (赞：0)

[题目](https://www.luogu.com.cn/problem/CF285E)

前言：其他题解DP都讲的很详细了，主要是想解释一下普通的容斥为什么错误，并且介绍二项式反演

## DP

这种带有位置限制的排列问题，都可以考虑往放车车的问题去想

问题就转变为：在一个$n\times n$的棋盘上，放$n$个互相不攻击的车，并且满足只有$m$辆车，所在的位置（它所在的行为$i$）为$i-1,i+1$中的一个

考虑DP，那么影响第$i$辆车的放置的信息就是：第$i-1,i$位置有没有被放过

设$f[i][j][sta]$表示前$i$辆车（前$i$行），有$j$个满足条件，且$i,i+1$有没有放的状态的方案数

但这样子定义状态，就难以保证剩下不满足条件的车能够不冲突；但如果直接让剩下的车在剩下的位置乱排，不冲突了，但就有可能使满足条件的数量增加，那就容斥一下嘛

改变定义：至少有$j$个满足条件的方案数（也就是如果要放就一定要在满足条件的位置上）。转移：

- 第$i$行满足方案

放在$i-1$：

$f[i][j][0]+=f[i-1][j-1][0]$

$f[i][j][1]+=f[i-1][j-1][2]$

放在$i+1$：

$f[i][j][2]+=f[i-1][j-1][0]+f[i-1][j-1][1]$

$f[i][j][3]+=f[i-1][j-1][2]+f[i-1][j-1][3]$

- 第$i$行不放

$f[i][j][0]+=f[i-1][j][0]+f[i-1][j][1]$

$f[i][j][1]+=f[i-1][j][2]+f[i-1][j][3]$

注意$i=1$和$i=n$时的边界条件

最后的答案：$\displaystyle \sum_{k=m}^{n}(-1)^{k-m}\binom{k}{m}f[n][k]\times (n-k)!$

看似很简单，但却调了很久

注意最后容斥的这一个式子。一开始写觉得应该是$\binom{n}{k}$，也就是选出$k$个满足条件来容斥

但注意递推出的这个$f$和一开始的容斥并不是搭配的，举个例子：$n=2,m=1$

通过递推可以得出$f[2][1][0]=f[2][1][1]=1$

其中$f[2][1][0]$表示$1$位置放了数字$2$，$2$位置没有确定的方案数

$f[2][1][1]$表示$2$位置放了数字$1$,$1$位置没有确定的方案数

很明显这两个是等价的，但因为没有确定的棋子我们让其随便放从而导致会出现重复计算

如果要把这个限制加入到DP中去考虑很麻烦，那就应该放到容斥中去计算了

我们通过举例子发现了重复计算，但却不知道它到底是怎么来的，或者说，暂时不知道如何用数学语言去阐述这个东西，下面将引入二项式反演来解释这个问题

## 二项式反演

- 容斥角度

一直觉得二项式反演的式子很眼熟，后来才意识到在组合数学容斥原理那一节有讲到这个东西，非常简单

首先普通的容斥原理：

$\displaystyle |A_1\cap A_2\cap ...\cap A_n|=|S|-\sum |\bar{A_i}|+\sum|\bar{A_i}\cap \bar{A_j}|-...+(-1)^n|\bar{A_1}\cap \bar{A_2}\cap ...\cap \bar{A_n}|$

$\displaystyle |\bar{A_1}\cap \bar{A_2}\cap ...\cap \bar{A_n}|=|S|-\sum |A_i|+\sum |A_i\cap A_j|-...+(-1)^n |A_1\cap A_2\cap ...\cap A_n|$

考虑一种特殊的情形，如果对于任意$t$个集合它们的交集大小只与$t$有关，即：

$f(t)=|A_{x_1}\cap A_{x_2}\cap ...\cap A_{x_t}|$

因为对于任意$i$个集合的补集的交集大小也只和$t$有关，所以同理可设

$\displaystyle g(t)=|\bar{A_{x_1}}\cap \bar{A_{x_2}}\cap ...\cap \bar{A_{x_t}}|$

并且定义$f(0)=g(0)=|S|$

那么对于第一条容斥原理和第二条容斥原理就有：

>$$\displaystyle f(n)=\sum_{i=0}^{n}(-1)^i\binom{n}{i}g(i)\iff \displaystyle g(n)=\sum_{i=0}^{n}(-1)^i\binom{n}{i}f(i)$$

这样子就得到了两个非常对称的式子，这就是二项式反演公式

- 推广$1$

上面两个式子虽然长得几乎一样，但更常用的是下面两个式子

>$$\displaystyle f(n)=\sum_{i=0}^{n}\binom{n}{i}h(i)\iff h(n)=\sum_{i=0}^{n}(-1)^{n-i}\binom{n}{i}f(i)$$

证明1：设$h(i)=(-1)^ig(i)$，那么：

$\displaystyle f(n)=\sum_{i=0}^{n}(-1)^i\binom{n}{i}g(i) \iff f(n)=\sum_{i=0}^{n}\binom{n}{i}h(i)$

$\displaystyle g(n)=\sum_{i=0}^{m}(-1)^i\binom{n}{i}f(i) \iff \frac{h(n)}{(-1)^n}=\sum_{i=0}^{n}(-1)^i\binom{n}{i}f(i) \iff h(n)=\sum_{i=0}^{n}(-1)^{n+i}\binom{n}{i}f(i)$

显然$n+i$和$n-i,i-n$的奇偶性都是相同的，所以$n+i$可以换成后面两个

证明$2$： 将左边的$h$用$f$来代换

$\displaystyle f(n)=\sum_{i=0}^{n}\binom{n}{i}\sum_{j=0}^{i}(-1)^{i-j}\binom{i}{j}f(j)$

$\displaystyle =\sum_{i=0}^{n}\sum_{j=0}^{i}(-1)^{i-j}\binom{n}{i}\binom{i}{j}f(j)$

$\displaystyle =\sum_{j=0}^{n}f(j)\sum_{i=j}^{n}(-1)^{i-j}\binom{n}{i}\binom{i}{j}$

考虑这样一个组合恒等式：$\displaystyle \binom{x}{y}\binom{y}{z}=\binom{x}{z}\binom{x-z}{y-z}=\binom{x}{z}\binom{x-z}{x-y}$

这个可以直接将组合数展开得证，或者考虑组合意义：

$x$要包括$y$，$y$要包括$z$，那么先把$z$放入到$x$中，然后$y$要包括$z$，除了$z$本身还要再从$x-z$中取$y-z$个

$\displaystyle =\sum_{j=0}^{n}f(j)\binom{n}{j}\sum_{i=j}^{n}(-1)^{i-j}\binom{n-j}{i-j}$

$\displaystyle =\sum_{j=0}^{n}f(j)\binom{n}{j}\sum_{i=0}^{n-j}(-1)^{i}\binom{n-j}{i}$

然后根据二项式定理可得：$\displaystyle \sum_{i=0}^{n-j}(-1)^i\binom{n-j}{i}=\sum_{i=0}^{n-j}\binom{n-j}{i}(-1)^i\times 1^{n-j-i}=0^{n-j}$

显然当$j\neq n$时，$0^{n-j}$都为$0$

当$j=n$时，对于$0^0$就出现了一些定义上的问题，那就不要把它转换过来，仍然用组合数

$\displaystyle f(n)=f(n)\binom{n}{n}(-1)^0\binom{0}{0}=f(n)$

上面的式子推到都没有利用到$i$从$0$开始的性质，所以还可以改写成：

>$$\displaystyle f(n)=\sum_{i=m}^{n}\binom{n}{i}h(i)\iff h(n)=\sum_{i=m}^{n}(-1)^{n-i}\binom{n}{i}f(i)$$

- 推广$2$

>$$\displaystyle f(n)=\sum_{i=n}^{m}\binom{i}{n}h(i)\iff h(n)=\sum_{i=n}^{m}(-1)^{i-n}\binom{i}{n}f(i)$$

这个式子和上面那个非常相似，启示我们同样代换一下就可以了

$\displaystyle f(n)=\sum_{i=n}^{m}\binom{i}{n}\sum_{j=i}^{m}(-1)^{j-i}\binom{j}{i}f(j)$

$\displaystyle =\sum_{j=n}^{m}f(j)\sum_{i=n}^{j}(-1)^{j-i}\binom{j}{i}\binom{i}{n}$

$\displaystyle =\sum_{j=n}^{m}f(j)\binom{j}{n}\sum_{i=n}^{j}(-1)^{j-i}\binom{j-n}{j-i}$

$\displaystyle =\sum_{j=n}^{m}f(j)\binom{j}{n}\sum_{i=0}^{j-n}(-1)^{i}\binom{j-n}{i}$

同理可得，只有当$j=n$时才有取值：

$\displaystyle f(n)=f(n)\binom{n}{n}(-1)^0\binom{0}{0}=f(n)$

## 组合意义

如果令$h(n)$表示恰好选了$n$个数，$f(n)$表示“钦定”选了$n$个数

其中这个“钦定”表示的是什么意思呢？其实只是为了和“恰好”区分开来，$h(n)$表示的是只选$n$个没有重复的方案数

$f(n)$则表示选够$n$个就可以了，剩下的$m-n$个任意的方案数

那么就有$\displaystyle f(n)=\sum_{i=n}^{m}\binom{i}{n}h(i)$，因为$h(i)$肯定是包括选了$n$个的

这里可能比较难理解，而且我们发现其实这个问题正是一开始DP时就提出来的问题

显然$f$的限制比$h$要宽，也就是更加好求，通过反演就可以用$f$来计算$h$了

## 回到这道题

题目要恰好，那就设：

$h(k)$表示恰好有$k$个合法位置的方案数，也就是$h(m)$就是最后的答案

$f(k)$表示强制有$k$个合法位置，剩下的任意的方案数（注意这里的任意，也要满足不能相互攻击的限制）

经过上面的分析，那么$\displaystyle f(k)=\sum_{i=k}^{n}\binom{i}{k}h(i)$

反演得到：$\displaystyle h(k)=\sum_{i=k}^{n}(-1)^{i-k}\binom{i}{k}f(i)$

有了上面DP的式子，可以得到：$f(k)=(f[n][k][0]+f[n][k][1])\times (n-k)!$

最后$\displaystyle h(m)=\sum_{i=m}^{n}(-1)^{i-m}\binom{i}{m}(f[n][i][0]+f[n][i][1])\times (n-i)!$就是答案了

```cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int N=1e3+10;
const ll mod=1e9+7;
ll fac[N],C[N][N],f[N][N][5];
int main()
{
	int n,m; ll ans=0;
	scanf("%d%d",&n,&m);
	fac[0]=C[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	f[1][0][0]=1;
	if(n>1) f[1][1][2]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			(f[i][j][0]+=f[i-1][j][0]+f[i-1][j][1])%=mod;
			(f[i][j][1]+=f[i-1][j][2]+f[i-1][j][3])%=mod;
			if(j==0) continue;
			(f[i][j][0]+=f[i-1][j-1][0])%=mod;
			(f[i][j][1]+=f[i-1][j-1][2])%=mod;
			if(i<n) (f[i][j][2]+=f[i-1][j-1][0]+f[i-1][j-1][1])%=mod;
			if(i<n) (f[i][j][3]+=f[i-1][j-1][2]+f[i-1][j-1][3])%=mod;
		}
	}
	for(int i=m;i<=n;i++)
	{
		ll opt=((i-m)&1?-1:1),sum=f[n][i][0]+f[n][i][1];
		ans=(ans+opt*C[i][m]*sum%mod*fac[n-i]%mod+mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

