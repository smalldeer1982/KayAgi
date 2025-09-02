# [AGC056E] Cheese

## 题目描述

有一个长度为 $N$ 的圆周。在圆周上的某个固定点，从该点顺时针前进距离 $x$ 的位置，称为坐标 $x$ 的点。

对于每个整数 $i$（$0 \leq i \leq N-1$），在坐标 $i+0.5$ 处有一只老鼠。

すぬけ君现在要进行 $N-1$ 次扔奶酪的操作。具体来说，以下操作会重复 $N-1$ 次：

- 随机选择一个整数 $y$（$0 \leq y \leq N-1$）。其中，选择 $y=i$ 的概率为 $A_i\%$。每次选择都是独立的。
- 然后，从坐标 $y$ 处扔出奶酪。奶酪会沿着圆周顺时针移动。当奶酪经过有老鼠的位置时，会发生以下情况：
  - 如果该老鼠之前没有吃过奶酪：
    - 以 $1/2$ 的概率吃掉奶酪，被吃掉的奶酪就会消失。
    - 以 $1/2$ 的概率什么都不发生。
  - 如果该老鼠之前已经吃过奶酪：
    - 什么都不发生。
- 奶酪会一直沿着圆周移动，直到被某只老鼠吃掉为止。

经过 $N-1$ 次扔奶酪后，恰好只剩下 $1$ 只老鼠没有吃过奶酪。对于每个 $k=0,1,\cdots,N-1$，请计算坐标 $k+0.5$ 处的老鼠最终没有吃到奶酪的概率，并对 $998244353$ 取模。

概率 $\bmod\ 998244353$ 的定义：可以证明，所求概率一定是有理数。此外，在本题的约束下，将其表示为最简分数 $\frac{P}{Q}$ 时，$Q \not\equiv 0 \pmod{998244353}$ 也成立。因此，存在唯一的整数 $R$ 满足 $R \times Q \equiv P \pmod{998244353},\ 0 \leq R < 998244353$。请输出这个 $R$。

## 说明/提示

### 约束

- $1 \leq N \leq 40$
- $0 \leq A_i$
- $\sum_{0 \leq i \leq N-1} A_i = 100$
- 输入的所有值都是整数

### 样例解释 1

必然会选择 $y=1$。从这里扔出奶酪时，会发生以下情况：
- 以 $1/2$ 的概率，坐标 $1.5$ 的老鼠吃掉奶酪。
- 以 $1/4$ 的概率，坐标 $0.5$ 的老鼠吃掉奶酪。
- 以 $1/8$ 的概率，坐标 $1.5$ 的老鼠吃掉奶酪。
- 以 $1/16$ 的概率，坐标 $0.5$ 的老鼠吃掉奶酪。
- $\vdots$
最终，这块奶酪被坐标 $0.5, 1.5$ 的老鼠吃掉的概率分别为 $1/3, 2/3$。
因此，最终没有吃到奶酪的概率分别为 $2/3, 1/3$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
0 100```

### 输出

```
665496236 332748118```

## 样例 #2

### 输入

```
2
50 50```

### 输出

```
499122177 499122177```

## 样例 #3

### 输入

```
10
1 2 3 4 5 6 7 8 9 55```

### 输出

```
333507001 91405664 419217284 757959653 974851434 806873643 112668439 378659755 979030842 137048051```

# 题解

## 作者：jun头吉吉 (赞：7)

## 题意
给定一个长度为 $n$ 的环。$x$ 表示某一个点顺时针走 $x$ 的距离。

$0\le i<n$，有一只坐标为 $i+0.5$ 的老鼠。

会投掷 $n-1$ 次奶酪，每次：

- 随机选一个 $0\sim n-1$ 的整数 $y$，$y=i$ 的概率为 $a_i/100$。
- 从 $y$ 位置投掷奶酪。奶酪会以顺时针方向沿圆周前进。当奶酪遇到一只老鼠时：
  - $1/2$ 的概率老鼠吃掉奶酪。奶酪和老鼠一起消失。
  - $1/2$ 的概率什么都不做。
- 奶酪一直前进，直到消失。

对于每个整数 $0\le k\le n-1$，请输出坐标为 $k + 0.5$ 的老鼠没有吃奶酪的概率模 $998244353$ 的值。

$1\le n \le 40,\ 0\le a_i,\ \sum_{0\le i \le n-1}a_i = 100$。

## 题解

考虑 $(a,b)$ 表示 $a$ 奶酪到了 $b$ 老鼠前面。那么判定就类似于这样：
$$
\begin{aligned}
&(1,a_{1,1}),(1,a_{1,2}),\dots,(1,a_{1,p_1})\\
&(2,a_{2,1}),(2,a_{2,2}),\dots,(2,a_{2,p_2})\\
&\dots\\
&(n-1,a_{n-1,1}),(n-1,a_{n-1,2}),\dots,(n-1,a_{n-1,p_{n-1}})
\end{aligned}
$$
每次判定提供 $\frac12$ 的贡献。最后一次判定是被吃掉了。

然后这个是原题的判定顺序，一个结论是在保持 $(i,a_{i,1}),\dots,(i,a_{i,p_i})$ 顺序不变的前提下，我们可以任意的顺序判定。

考虑交换两次相邻的判定。如果两次判定的奶酪不同，那么交换显然没有影响。如果相同，设为 $(x,a)$ 和 $(y,a)$，但是都没有吃，也没有影响。唯一有影响的就是前一个没吃后一个吃了。发现交换后我们可以还是判定前一个没吃后一个吃了，然后把后面所有的 $(x,*)$ 改成$(y,*)$。

那么实际上就相当于我们可以同时把所有奶酪都放好，然后每次选一个奶酪走，这样答案是不变的。

然后我们不妨设要计算 $0.5$ 位置的老鼠没有吃到奶酪的概率。那么我们可以先让所有奶酪顺时针走到 $0$ 的位置并判定。这个过程可以用dp描述，设 $f_{i,j,k}$ 表示处理到过程 $i$，现在已经放了 $j$ 块奶酪，被吃了 $k$ 块的贡献和。（过程就形如 在 $1$ 加入奶酪，判定 $1.5$ 的老鼠，在 $2$ 加入奶酪，判定 $2.5$ 的老鼠，……，在 $n$ 加入奶酪）

如果当前是加入奶酪，如果概率是 $A_p$，那么转移就是：
$$
f_{i+1,j+w,k}\leftarrow f_{i,j,k}\times A_p^w/w!
$$
要除 $w!$ 是因为这 $n-1$ 块奶酪最后要按顺序放下去，要乘上重排数。

然后当前是判定老鼠，那么转移是：
$$
\begin{aligned}
&f_{i+1,j,k}\leftarrow f_{i,j,k}\times 1/2^{j-k}\\
&f_{i+1,j,k+1}\leftarrow f_{i,j,k}\times\left(1-1/2^{j-k}\right)
\end{aligned}
$$
然后现在全部在 $0$ 位置了，设现在有 $k$ 块奶酪和 $k+1$ 只老鼠，我们可以依次判定每块奶酪。我们考虑第一块不被 $0.5$ 吃掉的概率，发现就是：
$$
\left(\frac1{2^2}+\frac1{2^3}+\dots+\frac1{2^{k+1}}\right)\times \left(1+\frac1{2^{k+1}}+\frac1{2^{2(k+1)}}+\dots\right)
$$
第一部分就是一圈内被不是 $0.5$ 的老鼠吃掉的概率。然后每次有 $1/2^{k+1}$ 的概率没有吃就要进入下一圈。

第二块奶酪实际上是 $k$ 只老鼠的情况，然后一直到两只老鼠的情况。

上面的先化简是：
$$
\frac{2^k-1}{2^{k+1}-1}
$$
所以最后的概率就是：
$$
\prod_{i=1}^{k}\frac{2^i-1}{2^{i+1}-1}=\frac{1}{2^{k+1}-1}
$$
所以最后的答案就是：
$$
\sum f_{lst,n-1,i}\times (n-1)!/(2^{n-i}-1)
$$
单次复杂度 $\mathcal O(n^4)$，总复杂度为 $\mathcal O(n^5)$。

## 代码
```cpp
const int N=41;
int n;mint ans[N],a[N],dp[2][N][N];
mint fac[N],ifac[N],pw[N];
signed main(){
	fac[0]=ifac[0]=pw[0]=1;for(int i=1;i<N;i++)fac[i]=fac[i-1]*i,pw[i]=pw[i-1]*2,ifac[i]=1/fac[i];
	read(n);for(int i=0;i<n;i++)read(a[i]),a[i]/=100;
	for(int X=0;X<n;X++){
		memset(dp,0,sizeof dp);int cur=0,pre=1;
		dp[cur][0][0]=1;
		for(int i=1;i<=n;i++){
			swap(pre,cur);memset(dp[cur],0,sizeof dp[cur]);
			for(int j=0;j<n;j++)for(int k=0;k<=j;k++)if(dp[pre][j][k].x){
				mint v=dp[pre][j][k];
				for(int w=0;j+w<n;w++,v*=a[(X+i)%n])dp[cur][j+w][k]+=v*ifac[w];
			}
			if(i==n)break;
			swap(pre,cur);memset(dp[cur],0,sizeof dp[cur]);
			for(int j=0;j<n;j++)for(int k=0;k<=j;k++)if(dp[pre][j][k].x){
				mint _=1/pw[j-k];
				dp[cur][j][k]+=dp[pre][j][k]*_;
				dp[cur][j][k+1]+=dp[pre][j][k]*(1-_);
			}
		}
		mint ans=0;
		for(int i=0;i<n;i++)ans+=fac[n-1]*dp[cur][n-1][i]/(pw[n-i]-1);
		write(ans.x);pc(" \n"[X+1==n]);
	}
}
```

---

## 作者：kkio (赞：2)

这里默认奶酪是正常的，不是吃老鼠的奶酪。

如果奶酪出现位置确定了，那么先走哪个奶酪，吃了哪个奶酪不影响概率，你可以通过修改判定奶酪得到相同概率的判定序列。所以对于相同的奶酪可重集合，计算重排列个数即可。

我们假设 $k$ 等于 $n$，否则通过旋转 $a$ 使 $k$ 对应 $n$。那么我们可以先将奶酪挪到相同的位置判定，根据前面的推断，概率是一样的。

所以我们可以 dp 了。设 dp 状态为 $f_{i,j,k}$ 和 $g_{i,j,k}$ 表示放奶酪和移动奶酪两个步骤，当前位置为 $i$，放了 $j$ 个奶酪，吃了 $k$ 个的概率，有方程。

$$f_{i,j,k} = \sum_{l \leq j}{g_{i-1,l,k} \times a_i^{j-l} \times \dfrac{1}{(j-l)!}}$$

$$g_{i,j,k} = f_{i,j,k} \times \dfrac{1}{2^{j-k}} +f_{i,j,k-1} \times (1 - \dfrac{1}{2^{j-k-1}})$$

但是如果你还剩一些奶酪的话，它就会在最后的几只老鼠那里转圈圈，这个概率可以分类比较，假设第 $i$ 个老鼠没吃的概率为 $p_i$，那么当相邻两个一个没吃，一个吃了时，才对 $p$ 有影响。假如转到剩 $x$ 个奶酪，当 $i$ 吃了时，概率为   $(1-\dfrac{1}{2^x})(\dfrac{1}{2^{x-1}})$，否则概率为 $(\dfrac{1}{2^x})(1-\dfrac{1}{2^{x-1}})$。所以有 $p_{i+1} = 2p_i$，解得 $p_0 = \dfrac{1}{2^k-1}$。

注意到 $n$ 时，由于计算的是 $p_0$，所以不需要吃奶酪。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=90,mod=998244353,inv2=(mod+1)/2;
int c[maxn],a[maxn],f[maxn][maxn][maxn];
int pw[maxn],ipw[maxn],fac[maxn],ifac[maxn],inv[maxn],n;
int ksm(int b,int p)
{
    int ret=1;
    while(p)
    {
        if(p&1)ret=1ll*ret*b%mod;
        b=1ll*b*b%mod;
        p>>=1;
    }
    return ret;
}
int solve()
{
    memset(f,0,sizeof f);
    f[0][0][0]=1;
    for(int i=1;i<=2*n;i+=2)
    {
        for(int j=0;j<=n-1;j++)
            for(int k=0;k<=j;k++)
            {
                for(int l=0;l+j<=n-1;l++)
                    f[i][l+j][k]=(f[i][l+j][k]+1ll*f[i-1][j][k]*ksm(a[(i+1)/2],l)%mod*ifac[l]%mod)%mod;
            }  
        for(int j=0;j<=n-1;j++)
            for(int k=0;k<=j;k++)
            {
                f[i+1][j][k]=(f[i+1][j][k]+1ll*f[i][j][k]*ipw[j-k]%mod)%mod;
                f[i+1][j][k+1]=(f[i+1][j][k+1]+1ll*f[i][j][k]*(mod+1-ipw[j-k])%mod)%mod;
            }
    }
    int ans=0;
    for(int i=0;i<=n;i++)
        ans=(ans+1ll*f[2*n-1][n-1][i]*ksm(pw[n-i]-1,mod-2)%mod)%mod;
    ans=1ll*ans*fac[n-1]%mod;
    return ans;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&c[i]),c[i]=1ll*c[i]*ksm(100,mod-2)%mod;
    pw[0]=ipw[0]=fac[0]=ifac[0]=inv[1]=1;
    for(int i=1;i<=n;i++)pw[i]=1ll*pw[i-1]*2%mod,ipw[i]=1ll*ipw[i-1]*inv2%mod;
    for(int i=2;i<=n;i++)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
    for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod,ifac[i]=1ll*ifac[i-1]*inv[i]%mod;
    for(int i=0;i<n;i++)
    {
        for(int j=1;j<=n;j++)a[j]=c[(i+j)%n+1];
        printf("%d ",solve());
    }
    return 0;
}
```


---

## 作者：Leasier (赞：2)

考虑分开计算每个老鼠没有吃到奶酪的概率。不妨钦定当前讨论的老鼠位于 $0.5$。

释放老鼠的顺序实在是太抽象了，考虑对其进行简化。

设 $(x, y)$ 表示第 $x$ 块奶酪经过了 $y$，则整个过程可以被表述为若干 $(x, s_x), (x, s_x + 1), \cdots, (s, t_x)$ 的拼接，最终在 $t_x + 1$ 处被吃掉。

我们显然不能一块一块地加入——因为这样就需要记录哪些老鼠还没有吃到这样的信息。我们期待的是顺序决策在每个 $i$ 处加了几块奶酪。

注意到以下性质：

- 我们不能交换 $(x, s_x)$ 和 $(s, s_x + 1)$。
- 若 $x \neq y, z \neq w$，我们可以交换 $(x, z), (y, w)$，因为两者互不干涉。
- 若 $x \neq y$，我们也可以交换 $(x, z), (y, z)$。因为若 $z + 0.5$ 没有吃 $x, y$ 则无影响，$z + 0.5$ 吃了 $x$ 则我们将其视为吃了 $y$，且把后面的 $(y, w)$ 改成 $(x, w)$，这样修改后显然等价。

于是我们可以考虑先转一圈加入所有奶酪，并先处理出第一圈老鼠吃奶酪的情况。

具体地，设 $dp_{i, j, k}$ 表示现在讨论完了 $[1, i]$ 中的奶酪，一共加入了 $j$ 块奶酪，有 $k$ 块奶酪被 $[1, i] + 0.5$ 中的老鼠吃了的方案数。

转移是一个可重集排列，较为简单，此处略去。

最后，我们还需要知道每块在第一圈没被吃掉的奶酪后续没有被 $0.5$ 吃掉的概率。

设此时还剩 $x$ 块奶酪，则：

- 考虑其中第一块被吃掉的奶酪，则其必然是在前若干圈中没有被吃掉，在最后一圈中被吃掉了。
- 枚举前 $i \geq 0$ 圈没有被吃掉，则概率为 $\displaystyle\sum_{i = 0} (\frac{1}{2 \times 2^x})^i (1 - \frac{1}{2^x}) = \frac{1 - \dfrac{1}{2^x}}{1 - \dfrac{1}{2^{x + 1}}}$。
- 由于最终所有奶酪必然是一块一块被吃掉的，则答案为 $\displaystyle\prod_{i = 1}^x \dfrac{1 - \dfrac{1}{2^i}}{1 - \dfrac{1}{2^{i + 1}}} = \frac{1}{2(1 - \dfrac{1}{2^{x + 1}})}$。

单次 dp 的时间复杂度为 $O(n^4)$，则总时间复杂度为 $O(n^5)$。

注意要在 dp 时特判 $0.5$ 不能吃奶酪。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int inv2 = 499122177, inv100 = 828542813, mod = 998244353;
ll fac[47], inv_fac[47], power[47], val[47], p[87][47], dp[87][47][47];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n){
	fac[0] = 1;
	for (int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[n] = quick_pow(fac[n], mod - 2, mod);
	for (int i = n - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
	power[0] = 1;
	for (int i = 1; i <= n; i++){
		power[i] = power[i - 1] * inv2 % mod;
		val[i] = inv2 * quick_pow(((1 - power[i]) % mod + mod) % mod, mod - 2, mod) % mod;
	}
}

inline ll solve(int l, int r, int n){
	ll ans = 0;
	for (int i = l - 1; i <= r; i++){
		for (int j = 0; j < n; j++){
			for (int k = 0; k <= j; k++){
				dp[i][j][k] = 0;
			}
		}
	}
	dp[l - 1][0][0] = 1;
	for (int i = l - 1; i < r; i++){
		for (int j = 0; j < n; j++){
			for (int k = 0; k <= j; k++){
				for (int x = 0; j + x < n; x++){
					dp[i + 1][j + x][k] = (dp[i + 1][j + x][k] + dp[i][j][k] * p[i + 1][x] % mod * inv_fac[x] % mod * power[j + x - k] % mod) % mod;
					if (i + 1 < r && j + x - k > 0) dp[i + 1][j + x][k + 1] = ((dp[i + 1][j + x][k + 1] + dp[i][j][k] * p[i + 1][x] % mod * inv_fac[x] % mod * (1 - power[j + x - k]) % mod) % mod + mod) % mod;
				}
			}
		}
	}
	for (int i = 0; i < n; i++){
		ans = (ans + dp[r][n - 1][i] * fac[n - 1] % mod * val[n - i] % mod) % mod;
	}
	return ans;
}

int main(){
	int n;
	scanf("%d", &n);
	init(n);
	for (int i = 1; i <= n; i++){
		int a, i_ = i + n;
		scanf("%d", &a);
		p[i][0] = p[i_][0] = 1;
		p[i][1] = p[i_][1] = (ll)a * inv100 % mod;
		for (int j = 2; j < n; j++){
			p[i][j] = p[i_][j] = p[i][j - 1] * p[i][1] % mod;
		}
	}
	for (int i = 1; i <= n; i++){
		printf("%lld ", solve(i + 1, i + n, n));
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc056_e)

**题目大意**

> 给定 $n$ 个洞排成一圈，位置为 $0\sim n-1$，随机 $n-1$ 次，每次取出一个球，以 $a_i$ 的概率放在 $i$ 上，然后从 $i$ 出发，每到一个还没有球洞口，就以 $\dfrac 12$ 的概率放进这个洞口，否则继续考虑下一个洞口。
>
> 对于每个洞口 $i$，求最后没有球的洞口恰好是 $i$ 的概率。
>
> 数据范围：$n\le 40$。

**思路分析**

用 $C(x,y)$ 表示判定第 $x$ 个球能否扔进第 $y\bmod n$ 个洞，设第 $i$ 个球的起点是 $p_i$，那么题目中的过程形如：
$$
\begin{aligned}
&C(1,p_1),C(1,p_1+1),\dots\\
&C(2,p_2),C(2,p_2+1),\dots\\
&\vdots\\
&C(n-1,p_{n-1}),C(n-1,p_{n-1}+1),\dots
\end{aligned}
$$
显然直接用 dp 维护这个判定过程是很难的，考虑重排这些判定事件。

首先我们要求 $C(x,y)$ 比 $C(x,y+1)$ 先判定，这个是不能改变的。

那么我们只能考虑交换 $C(x_1,y)$ 和 $C(x_2,y)$，事实上这是可以的，如果 $C(x_2,y)$ 成功，那么我们可以交换 $C(x_2,y+k),C(x_1,y+k)$，然后就等价于 $C(x_1, y)$ 成功了。

因此我们可以按 $y$ 从小到大判定，对于若干 $C(x_1,y)\sim C(x_q,y)$，如果有一个成功，钦定为 $C(x_1,y)$ 成功。

很显然我们只要求出第 $0$ 个洞最终没有球的概率，其他的旋转 $a$ 后等价。

我们只需要处理 $y=1\sim n-1$ 的情况并记录剩余的球数，不妨设还有 $k$ 个球等待判定 $C(x_1,n)\sim C(x_k,n)$。

此时所有球一起判定比较不优，考虑把判定顺序换回先判定 $C(x_1,n),C(x_1,n+1)\cdots$。

对于 $x_1$，如果在 $C(x_1,n+1)\sim C(x_1,2n-1)$ 中成功判定，概率为 $\dfrac 1{2^2}+\dots+\dfrac 1{2^{k+1}}$，因为 $C(x_1,n)$ 必须失败，然后在剩余的 $k$ 个洞中进入其中的一个。

并且 $x_1$，有 $\dfrac 1{2^{k+1}}$ 的概率回到 $C(x_1,2n)$，因此 $x_1$ 最终未进入 $0$ 的概率为 $\left(\dfrac 1{2^2}+\dots+\dfrac 1{2^{k+1}}\right)\times \dfrac 1{1-2^{-(k+1)}}$，即 $\dfrac{2^k-1}{2^{k+1}-1}$。

那么对于 $x_1\sim x_k$ 都未进入 $0$ 的概率就是 $\prod\limits_{i\le k}\dfrac{2^i-1}{2^{i+1}-1}=\dfrac1{2^{k+1}-1}$。

因此我们只要求出还剩 $k$ 个球判定到 $C(x_1,n)\sim C(x_k,n)$ 的概率。

考虑 dp，设 $f_{i,j,k}$ 表示当前判定到 $y=i$，一共加入 $j$ 个球，还剩 $k$ 个球没有判定成功的概率。

那么转移时先加入若干 $p_x=i$ 的球，由于球之间有顺序，因此转移时要乘组合数：
$$
f_{i,j,k}\gets f_{i-1,j-t,k-1}\times (a_i)^t\times \binom{j}{t}
$$
然后要考虑是否存在某个 $C(x,i)$ 判定成功，都不成功的概率是 $2^{-k}$，成功一个的概率就是 $1-2^{-k}$。

因此有转移 $f_{i,j,k}\gets f_{i,j,k}\times 2^{-k}$ 和 $f_{i,j,k}\gets f_{i,j,k+1}\times (1-2^{-k})$。

最终答案是 $\sum\dfrac{f_{n-1,n-1,k}}{2^{k+1}-1}$。

时间复杂度 $\mathcal O(n^6)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=45,MOD=998244353,inv=828542813;
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
ll f[MAXN][MAXN],g[MAXN][MAXN],a[MAXN],pw[MAXN],fac[MAXN],ifac[MAXN];
int n;
inline void add(ll &x,const ll &y) { x=(x+y)%MOD; }
ll solve() {
	memset(f,0,sizeof(f)),f[0][0]=1;
	for(int i=1;i<=n;++i) {
		memcpy(g,f,sizeof(g)),memset(f,0,sizeof(f));
		for(int j=0;j<n;++j) for(int k=0;k<=j;++k) {
			ll pr=1;
			for(int x=0;j+x<n;++x) {
				add(f[j+x][k+x],g[j][k]*pr%MOD*ifac[x]);
				pr=pr*a[i]%MOD;
			}
		}
		if(i==n) break;
		memcpy(g,f,sizeof(g)),memset(f,0,sizeof(f));
		for(int j=0;j<n;++j) for(int k=0;k<=j;++k) {
			ll pr=ksm(pw[k]);
			add(f[j][k],g[j][k]*pr);
			if(k) add(f[j][k-1],g[j][k]*(1+MOD-pr));
		}
	}
	ll s=0;
	for(int i=0;i<n;++i) add(s,f[n-1][i]*fac[n-1]%MOD*ksm(pw[i+1]-1));
	return s;
}
signed main() {
	for(int i=pw[0]=fac[0]=ifac[0]=1;i<MAXN;++i) {
		pw[i]=pw[i-1]*2%MOD,ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	}
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),a[i]=a[i]*inv%MOD;
	for(int i=1;i<=n;++i) rotate(a+1,a+2,a+n+1),printf("%lld ",solve());
	puts("");
	return 0;
}
```

---

## 作者：FZzzz (赞：1)

我其实不会这题，这个是瞎口胡的，要是错了请 D 爆我。

我们只考虑求 $n-1$ 的答案，求其他的答案只需要旋转一下做 $n$ 次就行了。

考虑固定在每处投下的奶酪个数，把在 $i$ 处投下的奶酪个数记为 $a_i$，我们欲对这样的情况计算第 $n-1$ 老鼠最后吃不到奶酪的概率。

考虑设经过了 $-0.1$ 点的奶酪个数为 $x$，则可以得到经过 $i+0.1$ 点的奶酪个数 $b_i=x-i+\sum\limits_{j=0}^ia_j$。$n-1$ 以外的每个老鼠 $i$，这 $b_i$ 个奶酪至少有一个要被它吃掉，概率 $1-\dfrac1{2^{b_i}}$，而 $n-1$ 不能吃奶酪，概率 $\dfrac1{2^{b_{n-1}}}$。这么一堆东西乘起来，记为 $f(x)$。出现 $b_i<0$ 就会有 $b_i=0$，所以不需要特别处理。

官方题解是这样讲的。看起来非常有道理？但是仔细想一下你会发现上面的这玩意好像是扯淡，因为它啥意义都没有——它既不代表经过 $-0.1$ 的奶酪数为 $x$ 的概率，也不代表这个前提下第 $n-1$ 个老鼠吃不到奶酪的概率，更不代表这俩乘起来。

……

如果我们给这个东西硬凑一个意义呢？比如，每个点有 $b_i$ 个 $\dfrac12$，我们如果考虑它第一次成立是在第几个，记为 $p_i$。我们假装它就是吃掉了这个奶酪，那么后面的所有 $\dfrac12$ 无论成不成立就都无所谓了，它都会被 $f$ 给计算到。

但是这样有个问题：$x$ 应当是 $p_i+i-\sum\limits_{j=0}^ia_j$ 的最大值，而不是现在的 $b_i+i-\sum\limits_{j=0}^ia_j$ 。虽然对于 $i\ne n-1$ 这不会影响它吃到经过它的第 $p_i$ 个奶酪的概率，但它会影响 $n-1$ 吃不到奶酪的概率：这给它多乘了一堆 $\dfrac12$。

到这里，我们发现我们不仅可以说出 $f(x)$ 的意义，还可以说出 $\sum\limits_{x=0}^\infty f(x)$ 的意义了！这就代表，所有 $n-1$ 吃不到奶酪的情况的概率，再乘上任意个 $\dfrac12$，最后加起来。虽然上两段讲的比较玄学，但是至此这已经是可以验证的了。另外，你也可以发现我们只关心被丢到 $i$ 点的奶酪有几个而不关心丢下去的顺序是正确的。

那么我们需要求出 $\sum\limits_{x=0}^\infty f(x)$。发现 $f(x)$ 是 $\dfrac1{2^x}$ 的多项式，那么只需要求出这个多项式就可以用无限项的等比求和求出这个式子了。然后，发现每种情况可以被乘上任意个 $\dfrac12$，那加起来相当于乘了一个 $2$，所以我们把这个式子除以二就可以在每个点奶酪个数已知的情况下得到 $n-1$ 吃不到奶酪的概率了。

那么在每个点奶酪个数不固定的情况下，只需要用 dp 求出所有情况下 $f(x)$ 的加权和就可以了。嘛，我感觉这我应该不需要讲了……总之单次 dp 时间复杂度 $O(n^4)$，总复杂度 $O(n^5)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=40+5;
int n;
const ll mod=998244353,inv2=499122177,inv100=828542813;
ll ksm(ll a,ll b){
	ll ans=1;
	while(b){
		if(b%2==1) ans=ans*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return ans;
}
ll fac[maxn],ifac[maxn],pw[maxn],ipw[maxn],a[maxn];
typedef vector<ll> poly;
poly operator +(poly A,poly B){
	int n=max(A.size(),B.size());
	A.resize(n);
	B.resize(n);
	for(int i=0;i<n;i++) A[i]=(A[i]+B[i])%mod;
	return A;
}
poly operator *(poly A,poly B){
	int n=A.size(),m=B.size();
	poly C(n+m-1);
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) C[i+j]=(C[i+j]+A[i]*B[j]%mod)%mod;
	return C;
}
poly F[2][maxn];
ll solve(){
	for(int i=1;i<n;i++) F[1][i]={0};
	F[1][0]={1};
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++) F[i%2][j]={0};
		for(int j=0;j<n;j++){
			ll t1=ksm(a[i],j)*ifac[j]%mod;
			for(int k=0;k<n-j;k++){
				ll t2=j+k>=i?ipw[j+k-i]:pw[i-j-k];
				F[i%2][j+k]=F[i%2][j+k]+F[!(i%2)][k]*(i==n-1?(poly){0,t2}:(poly){1,(mod-t2)%mod})*(poly){t1};
			}
		}
	}
	ll ans=0;
	for(int i=1;i<=n;i++) ans=(ans+F[(n-1)%2][n-1][i]*ksm((1-ipw[i]+mod)%mod,mod-2)%mod)%mod;
	return ans*fac[n-1]%mod*inv2%mod;
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	for(int i=0;i<n;i++) a[i]=readint()*inv100%mod;
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	ifac[n]=ksm(fac[n],mod-2);
	for(int i=n-1;i>=0;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
	pw[0]=ipw[0]=1;
	for(int i=1;i<=n;i++){
		pw[i]=pw[i-1]*2%mod;
		ipw[i]=ipw[i-1]*inv2%mod;
	}
	for(int i=0;i<n;i++){
		a[n]=a[0];
		for(int i=0;i<n;i++) a[i]=a[i+1];
		printf("%lld ",solve());
	}
	#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
	#endif
	return 0;
}
```
感觉是不是……还是讲得过于玄学了……

---

