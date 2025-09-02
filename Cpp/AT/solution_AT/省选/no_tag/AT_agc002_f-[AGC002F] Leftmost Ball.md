# [AGC002F] Leftmost Ball

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc002/tasks/agc002_f



# 题解

## 作者：墨尔 (赞：70)

考虑最后可能的序列，有 $k$ 个白球，$n$ 种其他颜色的球各 $k-1$ 个。显然只有当任意前缀中白球的个数均大等于其他颜色的种类数时合法。

设 $f[i][j]$ 表示已经放了 $i$ 个白球和 $j$ 种其他的颜色的可行方案数。$(j \leq i)$

转移时考虑合法序列的从左到右的第一个空位放什么。

放白球：即从 $f[i-1][j]$ 转移，因为是在第一个空位放置白球，转移过来必定合法。

放新的颜色的球：即从 $f[i][j-1]$ 转移，先在剩下 $n-j+1$ 种没有放置过的颜色中选择一个作为这次放置的颜色，放置在第一个空位（按转移规则，已经放置的 $i$ 个白球一定都在当前第一个空位的前面，因此必定合法）。放完后还剩 $k-2$ 的这个颜色的球没有放，显然只需要在剩下的后面 $n\times k-i-(j-1)\times (k-1)-1$ 个空位里找任意 $k-2$ 个空位放就好，有 $C_{n\times k-i-(j-1)\times (k-1)-1}^{k-2}$ 种方案

综上，转移方程为 $f[i][j]=f[i-1][j]+f[i][j-1]\times (n-j+1)\times C_{n\times k-i-(j-1)\times (k-1)-1}^{k-2}$

初始状态为 $f[i][0]=1$，即前 $i$ 个位置都放白球，答案为$f[n][n]$。

再注意一下 $k=1$ 的特判即可。

---

## 作者：pkh68 (赞：37)


看到这道题的时候，我其实是非常懵逼的。看了几篇博客，终于略通一二。下面是我对此题的理解。

### 题目大意

给你$n$种颜色的球，每个球有$k$个，把这$n\times{k}$个球排成一排，把每一种颜色的最左边出现的球涂成白色(初始球不包含白色)，求有多少种不同的颜色序列，答案对$1e9+7$取模。

### 分析

数据规模是$\leq2000$,考虑$O(n^2)$的做法：

我们观察发现：对于任意方法的任意前缀，白色的球的个数一定大于等于其颜色种类数，这就给了我们递推的条件——我们可以把白色球与其他颜色球分开看：

现在我们有$n\times{k}$位置：

![](https://cdn.luogu.com.cn/upload/pic/37367.png)
设$f(i,j)$表示在这些位置上已经放了$i$个白球，$j$种其他颜色的球。$(i<j)$

考虑转移：

我们可以从$f(i-1,j)$多放一个白球转移，也可以从$f(i,j-1)$多放一种颜色转移，那么转移方程已经呼之欲出，但我们需要注意，此处计算方案不能算重，那么我们人为规定每一次放颜色球时，第一个球一定放在当前第一个空格。
![](https://cdn.luogu.com.cn/upload/pic/37369.png)

1.初始状态。
2.先放绿色。
3.先放白色。
4.方案算重。

所以有转移方程：
$$f(i,j)=f(i-1,j)+f(i,j-1)\times{(n-j+1)}\times{c(k-2,n-i+(n-j+1)\times(k-1)-1)}$$


最后记得一定要特判$k=1$的情况（因为上面那个~~霸道的~~（雾）规定）。


### 代码如下

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#define re register
#define LL long long
#define N 2005
#define Maxn 4000000
using namespace std;
const int Mod=1e9+7;
int n,k;
LL f[N][N],fac[Maxn+5],inv_fac[Maxn+5];
inline LL C(int n,int m){ return (((fac[m]*inv_fac[n])%Mod)*inv_fac[m-n])%Mod; }
LL power(LL x,int P){
	LL ans=1,m=x;
	while(P){
		if(P&1) (ans*=m)%=Mod;
		P>>=1;(m*=m)%=Mod;
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&k);
	if(k==1){ printf("%d\n",1); return 0; }
	fac[0]=1; for(re int i=1;i<=Maxn;++i) fac[i]=(fac[i-1]*i)%Mod;
	inv_fac[Maxn]=power(fac[Maxn],Mod-2); for(re int i=Maxn-1;i>=0;--i) inv_fac[i]=(inv_fac[i+1]*(i+1))%Mod;
	f[0][0]=1;
	for(re int i=1;i<=n;++i){
		for(re int j=0;j<=i;++j){
			f[i][j]=f[i-1][j];
			if(!j) continue;
			(f[i][j]+=f[i][j-1]*(n-j+1)%Mod*C(k-2,n-i+(n-j+1)*(k-1)-1)%Mod)%=Mod;
		}
	}
	printf("%lld\n",f[n][n]);
	return 0;
}
```

### 后记

这道题我的理解还有一些生硬，须进一步体会。有什么不对的地方也请大佬指教。


---

## 作者：ezoixx130 (赞：20)

考虑钦定除 $0$ 以外的所有颜色的首次出现的顺序，即从前往后 $1$ 先出现，$2$ 再出现，然后是 $3,4,\cdots,n$。最后把答案乘一个 $n!$ 就行了。

钦定了顺序之后，就可以把最前面的 $0$ 按顺序分配给 $1$ 到 $n$ 了。考虑从 $n$ 到 $1$，对于每个 $k$，每次插 $1$ 个 $0$ 和 $m-1$ 个 $k$。这时 $0$ 必须插到序列最前面，而第一个 $k$ 必须插在原序列中第一个非零数的前面。

注意到插法跟第一个非零数的位置有关。受到这点的启发，我们可以直接 dp，设 $f_{i,j}$ 表示已经插了 $n-i+1$ 到 $n$，序列前端有 $j$ 个 $0$ 的方案数。该 dp 的转移是：
$f_{i,j+1} = \sum_{k>=j} f_{i-1,k} \times g(m\times(i-1)-j+1,m-2)$。


其中 $g(x,y)$ 表示把 $y$ 个数插到 $x$ 个空当中（可以相邻）的方案数，即 $g(x,y)=C^y_{x+y-1}$。

注意到这个转移后面的那个组合数跟 $k$ 根本没有关系。所以我们直接维护 $f_i$ 的后缀和进行转移就行啦。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAXN 2010
#define mod 1000000007

int n,k,fac[MAXN*MAXN],inv[MAXN*MAXN],f[MAXN][MAXN];

int qpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)res=(long long)res*a%mod;
		a=(long long)a*a%mod;
		b>>=1;
	}
	return res;
}

int c(int n,int m)
{
	if(n<0 || n<m)return 0;
	return (long long)fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int main()
{
	scanf("%d%d",&n,&k);
	if(k==1)
	{
		puts("1");
		return 0;
	}
	fac[0]=inv[0]=1;
	for(int i=1;i<=n*k;++i)fac[i]=(long long)fac[i-1]*i%mod;
	inv[n*k]=qpow(fac[n*k],mod-2);
	for(int i=n*k-1;i>=1;--i)inv[i]=(long long)inv[i+1]*(i+1)%mod;
	f[0][0]=1;
	for(int i=0;i<=n;++i)
		for(int j=i;j>=0;--j)
		{
			f[i+1][j+1]=(f[i+1][j+1]+(long long)f[i][j]*c(i*k-j+k-2,k-2)%mod)%mod;
			if(j)f[i][j-1]=(f[i][j-1]+f[i][j])%mod;
		}
	printf("%lld\n",(long long)f[n][0]*fac[n]%mod);
}
```

---

## 作者：Sata_moto (赞：16)


[$ \large{}\color {#6495ED} \mathcal{MyBlog} $](https://xjx885.coding-pages.com/)

---

$
$

## 前言：

$\quad \quad$ 本题是一道略有难度的DP思维题...

$\quad \quad$ 适合我这样的蒟蒻入门DP...

---

$
$

## 题目大意：

$\quad \quad$ 给你$n$种颜色的球，每个球有k个，把这$n*k$个球排成一排，把每一种颜色的最左边出现的球涂成白色(初始球不包含白色)，求有多少种不同的颜色序列，答案对$1e9+7$取模

$\quad \quad$ ~~(上段文本来自Ctrl + V)~~

---


$
$
## 思路分析:

$\quad \quad$ 拿到本题后，略(yi)一(kan)思(ti)索(jie)就知道这是一道DP题...

$\quad \quad$ 乍看上去这似乎很像一个$O(n*k)$的线性DP...

$\quad \quad$ 按照线性DP的一般思路，我们很容易想到设$f[i]$表示放球放到了第$i$位...

$\quad \quad$ 很显然这样是没有办法转移的...我们考虑增加维度...

$\quad \quad$ 增加一维使用过的颜色种数显然是没有用的...

$\quad \quad$ 按照一般线性DP的思路，这里需要设出所有颜色的球分别放下的个数才可以转移...

$\quad \quad$ 显然，这个状态相当庞大，是绝对设不出来的....

$\quad \quad$ 事实上，如果我们考虑每个球的状态，设$f[i]$表示放球放到了第$i$位，那么复杂度已经是$O(n*k)$了，剩下的复杂度根本无法维护其它的任何状态...

$\quad \quad$ 这说明本题并非经典的线性DP模型，从前向后一个个放球是不可以的...

$\quad \quad$ 我们注意到，本题要求的是放球的方案数，所以我们其实并不在乎每个位置放的什么球...

$\quad \quad$ 我们尝试把某种颜色的球在一次转移时一起处理...

$\quad \quad$ 假如并没有把某个球涂成白色这种奇葩设定...

$\quad \quad$ 我们不妨设$f[i]$表示已经放好了i种颜色的球...

$\quad \quad$ 转移很好理解：已经放好了i种颜色的球意味着还有(n-i)*k个位置没有放球...

$\quad \quad$ 我们本次要放k个球，所以放球的方案数是一个组合数...

$\quad \quad$ 同时我们这次可以放剩下的（n-i)个颜色中任意一种颜色的球...

$\quad \quad$ 所以得到：$f[i+1]=f[i]\ \ \ *(n-i)* \ \ \ C(k,(n-i)*k) $

$\quad \quad$ 但是这样显然会有重复计算的部分...

$\quad \quad$ 我们考虑为什么会有重复：

$\quad \quad$ 每次放球的操作我们可以抽象为一个二元组（x,y）表示第x次放球，是按照y的模式放的。y既表示放下去的球的颜色，又表示放下去的球的位置集合...

$\quad \quad$ 递推过程中，假设我们先进行操作（x1,y1），再进行操作(x2,y2)，那么它就会与先进行操作(x1,y2)，后进行操作(x2,y1)重复...

$\quad \quad$ 就比方说，我们在第一次操作的时候在1，3，5位置放下了绿球，在第二次操作的时候在2，4位置放下了红球。这与我们在在第一次操作的时候在2，4位置放下了红球，在第二次操作的时候在1，3，5位置放下了绿球是等价的....

$\quad \quad$ 如何避免重复？

$\quad \quad$ 我们可以在每一次放球的时候，把这一次放球的第一个球放在尽可能靠前的位置上...

$\quad \quad$ 显然，这样做的结果是，先进行的操作放下的球的第一个球的位置一定比后进行的操作放下的球的第一个球的位置靠前....（有点绕啊0.0）

$\quad \quad$ 为什么这样就不会重复了呢？

$\quad \quad$ 我们可以反证法证明：如果存在矛盾，那么我们先进行操作（x1,y1），再进行操作(x2,y2)是合法的，同时先进行（x1,y2），再进行操作(x2,y2)也是合法的。

$\quad \quad$ 因为先进行操作（x1,y1），再进行操作(x2,y2)是合法的，那么$y1->place[1]$（表示y1这个放球模式放下的第一个球的位置）$<y2->place[1]$

$\quad \quad$ 又因为先进行操作（x1,y2），再进行操作(x2,y1)是合法的，那么$y1->place[1] > y2->place[1]$

$\quad \quad$ 显然矛盾...

$\quad \quad$ 至此，我们可以给出在不考虑白球的情况下的递推式：$f[i+1]=f[i]*(n-i)* C(k-1,(n-i)*k-1)$(这个式子与上面的不同在于选定了一个球的位置（尽可能靠前的那一个位置）)

$\quad \quad$ 现在我们考虑球的染色...

$\quad \quad$ DP显然是不支持动态染色的...我们不妨把“染色”转化一下...

$\quad \quad$ 我们发现，被染成白色的球最多只有$n$个...

$\quad \quad$ 我们不妨把白球作为一种单独的球，而不是被染色的球考虑...

$\quad \quad$ 我们又发现：白球对其他球的唯一影响在于：在放第i个颜色时，前面应该至少有i个白球...

$\quad \quad$ 不妨在之前的基础上再开一维$f[i][j]$表示放置了i个白球，放置了j种颜色的球（不含白色）...

$\quad \quad$ 显然，在i一定时，j的转移就是我们在上面讨论很久的转移模式....

$\quad \quad$ 也就是说：$f[i][j+1]+=f[i][j] * (n-j) * C(k-2,(n-j)*(k-1)-1-i)$

$\quad \quad$ 与之前的方程的不同在于：白球的存在导致每种球的个数从k个减少到了k-1个...而且之前摆放的i个白球也会占位置...

$\quad \quad$ 当然，转移的时候要注意$j+1<=i$

$\quad \quad$ 至于i方向的转移，直接放下去就好，对我们的状态没有什么影响...

$\quad \quad$ 也就是说：$f[i+1][j] += f[i][j];$

$\quad \quad$ 至于初末状态，边界条件，都比较显然，这里略去...

---

$
$

## 代码实现：


$\quad \quad$ 虽然上面讲的都是刷表法实现的，但是本蒟蒻的代码是填表法实现的，略有不同...

$\quad \quad$ 另外，O(n)求阶乘逆元（算C要用）应该都会吧...原理是：$\dfrac{1}{x!}=\dfrac{1}{(x+1)!}*(x+1)$在模意义下也成立...

$\quad \quad$ 所以只需要求出最后那个阶乘的逆元，然后反推就行了...

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2010;
const int MOD = 1e9 + 7;

int n, K, f[N][N];
int fac[N*N], rev[N*N];

int quick_pow(int x, int times)
{
	if(x == 0) return 0;
	int ans = 1, mult = x;

	while(times)
	{
		if(times & 1)
			ans *= mult, ans %= MOD;
		mult *= mult, mult %= MOD, times >>= 1;
	}
	return ans;
}

void init()
{
	fac[0] = fac[1] = 1;
	for(register int k = 2; k <= n * K; k++)
		fac[k] = fac[k - 1] * k % MOD;

	rev[n * K] = quick_pow(fac[n * K], MOD - 2);
	for(register int k = n * K - 1; k >= 0; k--)
		rev[k] = (rev[k + 1] * (k + 1)) % MOD;
}

int C(int up, int down)
{
	return ((fac[down] * rev[up] % MOD) * rev[down - up]) % MOD;
}

signed main()
{
	scanf("%lld %lld", &n, &K), init();
	if(K == 1)
	{
		printf("1");
		return 0;
	}

	f[0][0] = 1;
	for(register int i = 1; i <= n; i++)
		for(int j = 0; j <= i; j++)
		{
			f[i][j] += f[i - 1][j];
			if(j - 1 >= 0)
				f[i][j] += (f[i][j - 1] * (n - j + 1) % MOD) * C(K - 2, n * K - i - (j - 1) * (K - 1) - 1) % MOD, f[i][j] %= MOD;
		}

	printf("%lld", f[n][n]);

	return 0;
}
```



---

$
$

## 结语：

$\quad \quad$ 如果本题解有BUG，还请评论或私信作者....

---

$$ \large{END}$$

---

## 作者：Kinandra (赞：8)

标签: DP.

一个方案合法当且仅当对于该方案的每一个前缀, 白色球的个数 $i$ 大于非白色的颜色种类数 $j$ .

考虑在 $n\times k$ 个位置上放球, 设计状态 $f_{i,j}$ 表示已经放入 $i$ 个白球, $j$ 种非白的颜色的**所有球**的合法方案数, 可以通过加入一个白球或加入一中颜色来转移. 为避免算重:

* 加入白球时, 我们强制白球放入最靠左位置.
* 加入一中颜色是, 我们强制该颜色的第一个球放在能使方案合法的最靠左的位置.

这样转移式子就可以很容易写出来了: 

$f_{i,j}=f_{i-1,j}+(n-j+1){nk-i-(j-1)(k-1)-1\choose k-2}f_{i,j-1}$.

时间复杂度 $\mathcal O(n^2)$.

```cpp
#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
int read();
int M(int x) { return x >= mod ? x - mod : x; }
int fsp(int bs, int p) {
    int rt = 1;
    while (p) {
        if (p & 1) rt = 1ll * rt * bs % mod;
        bs = 1ll * bs * bs % mod, p >>= 1;
    }
    return rt;
}

int n, k;
int fac[4000006], caf[4000006];
void init() {
    int lim = 4000000;
    fac[0] = 1;
    for (int i = 1; i <= lim; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    caf[lim] = fsp(fac[lim], mod - 2);
    for (int i = lim; i >= 1; --i) caf[i - 1] = 1ll * caf[i] * i % mod;
}
int C(int x, int y) { return 1ll * fac[x] * caf[y] % mod * caf[x - y] % mod; }
int f[2003][2003];

int main() {
    n = read(), k = read(), init();
    if (k == 1) return puts("1"), 0;
    for (int i = 1; i <= n; ++i) f[i][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            f[i][j] = M(f[i - 1][j] +
                        1ll * f[i][j - 1] * (n - j + 1) % mod *
                            C(n - i + (n - j + 1) * (k - 1) - 1, k - 2) % mod);
    printf("%d\n", f[n][n]);
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```



---

## 作者：_LHF_ (赞：4)

一道计数题。

显然这并不是一个双射，考虑如何做到不重不漏。

我们钦定第 $i$ 种颜色第二次出现的位置（因为第一次出现被染白了） $<$ 第 $i+1$ 种颜色第二次出现的位置。

然后数出来的答案$\times n!$ 即为所求。

我们先把白色摆出来，那么显然第 $i$ 个白色球后面的颜色种类数（不算白色）$\le n-i+1$。

我们考虑枚举第 $i=n\sim 1$ 种颜色的摆放，然后可以通过简单的 $dp$ 计算得出。

---

## 作者：tzc_wk (赞：3)

[Atcoder 题面传送门](https://atcoder.jp/contests/agc002/tasks/agc002_f) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT2000)

~~这道 Cu 的 AGC F 竟然被我自己想出来了！！！（（（~~

首先考虑什么样的序列会被统计入答案。稍微手玩几组数据即可发现，一个颜色序列 $c_1,c_2,\cdots,c_{nk}$ 满足条件当前仅当对于从左往右数第 $i$ 个 $0$ 号颜色的位置 $p_i$，$[1,p_i-1]$ 中非零颜色的种类 $<i$。简单证明一下，必要性：如果 $\exist i\in[1,n]$ 满足 $[1,p_i-1]$ 中颜色种类 $\ge i$，那么 $[1,p_i-1]$ 中至少出现了 $i$ 种颜色，也就至少应当有 $i$ 个 $0$ 号颜色的球。但事实上 $[1,p_i-1]$ 中只有 $i-1$ 个 $0$ 号颜色的球，矛盾。充分性：我们假设第 $i$ 种颜色第二次出现的位置（也就是第一次出现的位置被替换为 $0$ 后，剩余部分第一次出现的位置）为 $q_i$，我们将 $q_i$ 从小到大排个序，由假设第 $i$ 小的 $q_i$ 必定 $\le p_i$，因此我们只需将第 $i$ 个黑球替换为第 $i$ 小的 $q_i$ 对应的颜色即可还原出原序列。

接下来考虑发现这个性质之后怎样计算答案，我们考虑一个填补空隙的思想，设 $dp_{i,j}$ 表示填好了 $i$ 个黑球的位置以及前 $j$ 种颜色的剩余 $k-1$ 个球的位置的方案数，考虑转移，由以下两种情况：

- 我们新放了一个黑球，为了避免重复，我们强制要求该黑球必须放在从左往右数的第一个空隙处，方案唯一，即 $dp_{i+1,j}\leftarrow dp_{i,j}$
- 我们新添了一种颜色，那么我们需先从剩余 $n-j$ 种颜色中选择一种颜色，再将这种颜色的剩余 $k-1$ 个球任意放入剩余 $nk-j(k-1)-i$ 个空隙，方案数为 $\dbinom{nk-j(k-1)-i}{k-1}\times(n-j)$。可真的是这样吗？不难发现这样会重复计算，举个例子，$n=2,k=2$，现在已经填好了两个 $0$ 的位置，即 $0\ 0\ -\ -$（其中 $-$ 表示空隙），那么我们在 $dp$ 转移的过程中会出现先选择一个 $1$，填入 $3$ 位置，再选择一个 $2$，填入 $4$ 位置，即 $0\ 0\ -\ -\to 0\ 0\ 1\ -\to 0\ 0\ 1\ 2$，也有可能出现先选择一个 $2$，填入 $4$ 位置，再选择一个 $1$，填入 $3$ 位置，$0\ 0\ -\ -\to 0\ 0\ -\ 2\to 0\ 0\ 1\ 2$，不难发现这两种情况的结局是一样的，都是 $0\ 0\ 1\ 2$，不过却因为钦定填颜色的顺序不同而被我们算了两次。怎样解决这个问题呢？这里有一个避免重复的技巧，我们还是将 $k-1$ 个球塞入 $nk-j(k-1)-i$ 个空隙，不过我们强制要求有一个球必须放入从左往右数的第一个空隙中，方案数就变为了 $\dbinom{nk-j(k-1)-i-1}{k-2}\times(n-j)$，不难发现在这种情况下，我们塞球的顺序永远是先塞第一次出现位置最靠前的颜色，也就不会出现上面的情况了。$dp$ 转移方程式为 $dp_{i,j+1}\leftarrow dp_{i,j}\times\dbinom{nk-j(k-1)-i-1}{k-2}\times(n-j)$。

到这里你可能还有个小问题，就是上面“从左往右数第 $i$ 个 $0$ 号颜色的位置 $p_i$，$[1,p_i-1]$ 中非零颜色的种类 $<i$”怎样在 DP 方程中体现出来。其实很简单，我们在求 DP 值的时候只保留 $j\le i$ 的 $dp_{i,j}$ 即可，显然这样转移总是合法的。

时间复杂度 $\mathcal O(nk)$。

~~最后，文件名打错，爆零两行泪，这题是某场模拟赛的题，现场想到正解了，却因为文件名打错而爆零了/kk~~

```cpp
const int MAXN=2e3;
const int MOD=1e9+7;
int n,k,dp[MAXN+5][MAXN+5];
int fac[MAXN*MAXN+5],ifac[MAXN*MAXN+5];
void init_fac(int n){
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i]*ifac[i-1]%MOD;
}
int binom(int x,int y){return 1ll*fac[x]*ifac[x-y]%MOD*ifac[y]%MOD;}
int main(){
//	freopen("colorful.in","r",stdin);freopen("colorful.out","w",stdout);
	scanf("%d%d",&n,&k);if(!(k^1)) return printf("1\n"),0;
	dp[0][0]=1;init_fac(n*k);
	for(int i=1;i<=n;i++) for(int j=0;j<=i;j++){
		dp[i][j]=(dp[i-1][j]+1ll*dp[i][j-1]*binom(n*k-(j-1)*(k-1)-i-1,k-2)%MOD*(n-j+1)%MOD)%MOD;
	} printf("%d\n",dp[n][n]);
	return 0;
}
```



---

## 作者：lmki (赞：3)

[题目链接](https://atcoder.jp/contests/agc002/tasks/agc002_f)

​	先特判一下 $ k = 1$ 的情况， 然后将每个颜色第一次出现的位置严格从小到大计数， 最后答案乘 $n!$ 即可。

​	之后考虑 DP, 我们假设已经求解已经出现了 $i - 1$ 种颜色的排列的数量, 我们要用这来推出 $i$ 种颜色的排列的数量, 那么我们考虑将原本 $i - 1$ 种颜色的排列所有非 0 元素 +1, 然后把 $0\dots1111$ 插进原排列种, 于是就避免了第 $i$ 种颜色和第 $i - 1$ 种颜色出现的位置的讨论,  之后我们发现这数量以之前的排列中前面 0 的数量有关, 于是考虑多设一个状态记前面 0 的数量, 很容易就得到以下方程。

​	记 $dp_{i,j}$ 表示出现 $i$ 种颜色， 左边**至少**有 $j$ 个 0 的排列的数量， 则
$$
dp_{i,j}=dp_{i,j + 1} + dp_{i - 1, j - 1}\times{\binom{i\times k - (j + 1)}{k - 2}}
$$
​	按此方程递推即可。答案为 $dp_{n,1}\times n!$。



---

## 作者：Aw顿顿 (赞：3)

## 题意

给定 $n$ 种颜色的球，每个球有 $k$ 个，把这 $n\times k$ 个球排成一排，把每一种颜色的最左边出现的球涂成白色(初始球不包含白色)，求有多少种不同的颜色序列，答案对 $10^9+7$ 取模。

## 分析

看了好几份题解发现有一些步骤一笔带过，看起来有一点吃力，这里想写一篇相对详细的题解。其他题解中的一些基于状态设计的表述容易让初学者引起“这道题居然能放白球吗”的误解，这一点私以为可以注意一下。

--------

从任何一个角度来看，难点都主要在于设计状态。

我们定义 $f(i,j)$ 表示当前序列中有 $i$ 个白球、$j$ 种其他颜色的情况。不难发现一定存在 $i\ge j$，为什么？因为每一种白球都代表着一种颜色的最左端，如果白球个数少于其他颜色的个数，那么就一定存在某种颜色没有对应的白球，这是不妥当的。

为什么可能存在白球个数大于其他颜色个数呢？因为到目前为止可能会存在某些颜色只出现了一次，而这单独的一次会被染色成白色，因此就不能计算在“其它颜色的种类”这一变量之中。

我们接下来考虑这种状态应该从哪一种状态之中来。首先如果到达这个状态是放了一个白球，那么显然就是放了一个白球而已，因此我们可以从 $f(i-1,j)$ 进行转移。这时候只有单纯的选择方案，但是如果要选择新的一种颜色，事情就不太一样了。

因为我们选择颜色一定要从剩下的颜色之中选，所以要在剩下的 $n-j+1$ 种颜色填入（一共有 $n$ 种颜色已经用了 $j-1$ 种，接下来要用第 $j$ 种），与此同时 $nk-i-1-(j-1)\times(k-1)$ 个位置中选择 $k-2$ 个填入下一种颜色，也就是：

$$\large\text{C}_{nk-i-1-(j-1)\times (k-1)}^{k-2}$$

那么这样的状态转移就容易写出来了。

其中组合数的计算可以考虑一下 $m!\cdot inv_n\cdot inv_{n-m}$，最后要记得对 $10^9+7$ 取模。对于逆元，可以用线性复杂度的方法递推一下，其中要注意，我们求的逆元实际上是前缀积的逆元。


## 代码

代码实现不难。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define N 2005
using namespace std;
int n,k,inv[N*N],fac[N*N],f[N][N];
int C(int n,int m){
   return fac[n]*inv[m]%mod*inv[n-m]%mod;
}void Inv(){
	inv[0]=inv[1]=1;
	for(int i=2;i<=n*k;i++)inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	for(int i=2;i<=n*k;++i)inv[i]=inv[i-1]*inv[i]%mod;
}void Fac(){
	fac[0]=fac[1]=1;
	for(int i=2;i<=n*k;++i)fac[i]=fac[i-1]*i%mod;
}signed main(){
	scanf("%lld%lld",&n,&k);
	Inv();Fac();
	if(k==1){
		puts("1");
		return 0;
	}for(int i=0;i<=n;++i)f[i][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			f[i][j]=(f[i-1][j]+
					f[i][j-1]*(n-j+1)%mod
					*C(n*k-i-1-(j-1)*(k-1),k-2)%mod)%mod;
//			cout<<"("<<i<<','<<j<<") ";
//			cout<<f[i][j]<<"\t";
		}//puts("");
	}cout<<f[n][n]<<endl;
	return 0;
}
```

不才拙笔，至此章卒。

---

## 作者：pomelo_nene (赞：2)

一个比较显然的性质，也就是这个序列合法，当且仅当在任意位置，这个位置之前出现的白球个数大于等于其他颜色的种类数。

还是考虑常规定义吗？定义 $dp_{i,j}$ 为前 $i$ 个球，第 $j$ 个球放什么颜色。我们发现这样不仅不能够很好的转移，并且看上去挺麻烦的。于是考虑换一个思路去定义。定义 $dp_{i,j}$ 为放了 $i$ 个白球，并且放置了 $j$ 种另外的颜色。根据我们转化的定义，显然的需要对于任意转移点，$j \leq i$。

考虑 $dp_{i,j}$ 这个状态会由什么方式得来。分类讨论：

- 这个球是白球，直接 $dp_{i-1,j}$；   
- 否则，我们还有 $n-j+1$ 种颜色没有放置；首先放好一个准备在这次放下的颜色，在剩下 $k-2$ 个球中，我们有 $n \times k -i-(j-1)\times(k-1)-1$ 个位置还没有放置。这里可以随便放，所以方案数应该是 $\binom{n \times k -i-(j-1)\times(k-1)-1}{k-2} \times (n-j+1) \times dp_{i,j-1}$。

转移方程综合上面得来。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
LL dp[2005][2005],n,k,fac[4000005],inv[4000005];
LL QuickPow(LL x,LL p)
{
	LL base=x,ans=1;
	while(p)
	{
		if(p&1)	ans*=base,ans%=MOD;
		p>>=1;
		base*=base;
		base%=MOD;
	}
	return ans;
}
LL C(LL n,LL m){return fac[m]*inv[n]%MOD*inv[m-n]%MOD;}
int main(){
	fac[0]=1;
	scanf("%lld %lld",&n,&k);
	if(k==1)	return puts("1")&0;
	for(LL i=1;i<=n*k;++i)	fac[i]=fac[i-1]*i%MOD;
	inv[n*k]=QuickPow(fac[n*k],MOD-2);
	for(LL i=n*k-1;~i;--i)	inv[i]=inv[i+1]*(i+1)%MOD;
	for(LL i=0;i<=n;++i)	dp[i][0]=1;
	for(LL i=1;i<=n;++i)
	{
		for(LL j=1;j<=i;++j)
		{
			dp[i][j]=(dp[i-1][j]+dp[i][j-1]*(n-j+1)%MOD*C(k-2,n*k-i-(j-1)*(k-1)-1)%MOD)%MOD;
		}
	}
	printf("%lld\n",dp[n][n]);
	return 0;
}
```

---

## 作者：SIXIANG32 (赞：2)

这道题的状态有点难想出来，除此之外都挺简单的。  
闲话少说，切入正题——  

---
这道题的状态很别致：$f_{i, j}$ 表示摆了 $i$ **个**白球 $j$ **种**非白球的方案数量。  
为了防止重复我们严格规定 $j \le i$。  
然后我们来推推方程：  
首先要不然我们会放一个白球，白球得在最左边的空位，所以是 $f_{i - 1, j}$。  
然后我们考虑放一个非白球，这种非白球从 $f_{i, j - 1}$ 转移过来，先放一个非白球。为了保证不重复，我们要放最左边的，所以现在有 $n - j + 1$ 种颜色可以放置，每种颜色各有 $k - 2$（刚放的一个白球和非白球）个球，一共有 $n \times k - i - (j - 1) \times (k - 1) - 1$ 个位置能放，显然这就是个组合数的问题。  
所以状态转移方程出来啦——  
$$f_{i,j} = f_{i - 1,j} + f_{i,j - 1} \times (n - j + 1) \times C^{k - 2}_{n \times k - i - (j - 1) \times (k - 1) - 1}$$  

*PS：以上做法不适用于 $k = 1$ 的情况，要特判*

---
那么唯一的问题就是怎么求组合数了，组合数有一种求法是 $fac_m \times inv_n \times inv_{m - n} \mod Mod$  
（$fac$ 代表阶乘，$inv$ 代表 $fac_{i}$ 再取余 $Mod$ 意义下的逆元）  
设一个常量 $LIM$ 代表最高需要求的数，顶多就 $2000\times 2000 = 4000000$，首先预处理一下 $fac$，然后预处理 $inv$。  
考虑到 $4000000!\mod Mod$ 肯定会很大，所以我们不能用线性求逆元和 exgcd（不好取余），要用费马小定理。  

---
代码：  
```cpp
#include <iostream>
#define int unsigned long long
#define MAXN 3000
#define LIM 4000000
#define Mod 1000000007
#define QWQ cout << "QWQ" << endl;
using namespace std;
int n, k, f[MAXN + 10][MAXN + 10], fac[MAXN * MAXN + 10];
int inv[MAXN * MAXN + 10];
int qpow(int n, int m){
	int ans = 1;
	while(m) {
		if(m & 1) ans = ans * n % Mod;
		n = n * n % Mod, m>>=1; 
	}
	return ans % Mod; 
}
void init() {//计算逆元
	fac[0] = 1;
	for(int p = 1; p <= LIM; p++) fac[p] = fac[p - 1] * p % Mod;
	for(int p = 0; p <= LIM; p++) inv[p] = qpow(fac[p], Mod - 2) % Mod;
}
int C(int n, int m) {//组合数
	if(n > m) return 0;
	return ((fac[m] * inv[n] % Mod) * inv[m - n] % Mod) % Mod;
}
signed main() {
	cin >> n >> k;
	init();
	if(k == 1) {
		cout << 1 << endl;
		return 0;
	}
	for(int p = 0; p <= n; p++)//初始状态
		f[p][0] = 1;
	for(int p = 1; p <= n; p++)//dp
		for(int i = 0; i <= p; i++)
			f[p][i] = ((f[p - 1][i] % Mod + f[p][i - 1] % Mod * (n - i + 1) % Mod * C(k - 2, n * k - p - (i - 1) * (k - 1) - 1) % Mod) + Mod) % Mod;
	cout << f[n][n] % Mod << endl;
}
```


---

## 作者：_Clown_ (赞：1)

$$\huge\mathbb{DESCRIPTION}$$
编号：$AT2000$

算法：乘法逆元、$\mathcal{DP}$

时间复杂度：$\mathcal O(N^2)$
$$\huge\mathbb{SOL}$$
我们直接来推式子吧...

首先如果$K=1$，就直接输出1。

设$Dp[i][j]$表示用了$i$个白球和$j$个彩色球的合法的方案数量。

首先，如果你已经放了$i-1$个白球和$j$个彩球，这时你再在后面放一个白球肯定不影响。

因此，$Dp[i][j]$可以有$Dp[i-1][j]$转移过来。

其次，$Dp[i][j]$也可以有$Dp[i][j-1]$转移而来。

我们看看为什么吧...

因为已经选了$j-1$个彩球，所以还有$N-j+1$个彩球没有选。

如果我们选了某一种颜色的球，我们就必须从这种颜色的$K$个彩球里选一个放上。

此时，这种颜色的彩球减少了$2$个，一个被涂成了白色，一个没有变色。

所以还剩$K-2$个这种彩球。

所以我们需要在剩下的$N*K-i-1(j-1)*(K-1)$个位子中选$K-2$个位子。

所以我们就得出了状态转移方程：
$$
Dp[i][j]=Dp[i-1][j]+Dp[i][j-1]*(N-j+1)*C_{N*K-i-1(j-1)*(K-1)}^{K-2}
$$
转移前求一下阶乘和逆元即可。
$$\huge\mathbb{CODE}$$
```cpp
#include<bits/stdc++.h>
#define MOD 1000000007
#define MAX 2001
using namespace std;
long long N,K;
long long Inv[MAX*MAX];
long long Dp[MAX][MAX];
long long Factorial[MAX*MAX];
inline long long Quick_Power(long long X,int P)
{
	register long long Return;
	Return=1;
	while(P)
	{
		if(P&1)
		{
			Return=Return*X%MOD;
		}
		X=X*X%MOD;
		P>>=1;
	}
	return Return;
}
inline long long Combination(long long A,long long B)
{
	return Factorial[A]*Inv[B]%MOD*Inv[A-B]%MOD; 
}
int main(void)
{
	register long long i,j;
	cin>>N>>K;
	if(K==1)
	{
		cout<<1<<endl;
		return 0;
	}
	Factorial[0]=1;
	for(i=1;i<=N*K;i++)
	{
		Factorial[i]=Factorial[i-1]*i%MOD;
	}
	Inv[N*K]=Quick_Power(Factorial[N*K],MOD-2);
	for(i=N*K-1;i>=0;i--)
	{
		Inv[i]=Inv[i+1]*(i+1)%MOD;
	}
	Dp[0][0]=1;
	for(i=1;i<=N;i++)
	{
		for(j=0;j<=i;j++)
		{
			if(!j)
			{
				Dp[i][j]=Dp[i-1][j];
				continue;
			}
			Dp[i][j]=Dp[i-1][j]+Dp[i][j-1]*(N-j+1)%MOD*Combination(N*K-i-1-(j-1)*(K-1),K-2)%MOD;
		}
	}
	cout<<Dp[N][N]<<endl;
	return 0;
}
```

---

## 作者：henry_y (赞：1)

设$f[i][j]$表示当前有$i$个白球，一共放完了$j$种球
显然有$j <= i$
对于每个状态目前已经放下去的球是固定了的，那么考虑转移
* 放白球 从$f[i - 1][j]$转移
* 放没有出现过的球 $(n - j + 1) * f[i][j - 1] * C(k - 2, n * k - i - (j - 1) * (k - 1) - 1)$

第二种的C是钦定第一个球放在已经构造好了的合法序列的后面第一个空位，然后剩下的$k-2$个球放在剩下的$n * k - i - (j - 1) * (k - 1) - 1$空位上。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2020;
const int mod = 1e9 + 7;

int inv[N * N], fac[N * N];
int f[N][N];
int n, k;

int power(int a, int b) {
	a %= mod; int ans = 1;
	while(b) {
		if(b & 1) ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod; b >>= 1;
	}
	return ans;
}

int C(int n, int m) {
	return 1ll * fac[m] * inv[n] % mod * inv[m - n] % mod;
}

int main() {
	scanf("%d%d", &n, &k);
	if(k == 1) return printf("%d\n", 1), 0;
	fac[0] = 1;
	for(int i = 1; i < N * N; ++i) 
		fac[i] = 1ll * fac[i - 1] * i % mod;
	for(int i = 0; i < N * N; ++i) 
		inv[i] = power(fac[i], mod - 2);
	for(int i = 0; i <= n; ++i) f[i][0] = 1;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= i; ++j) {
			f[i][j] = f[i - 1][j];
			(f[i][j] += 1ll * (n - j + 1) * f[i][j - 1] % mod * C(k - 2, n * k - i - (j - 1) * (k - 1) - 1) % mod) %= mod;
			(f[i][j] += mod) %= mod;
		}
	}
	printf("%lld\n", (f[n][n] % mod + mod) % mod);
	return 0;
}
```

---

## 作者：Elma_ (赞：1)

考虑 dp。设 $f_{i,j}$ 为当前已经放置了 $i$ 个白球， $j$ 种其他不同颜色的球的方案数，容易发现最终可能的序列的任意一个前缀中，白球的个数 $i$ 都大于其中其他颜色的种数 $j$。转移如下：

- 放置白球：$f_{i,j}=f_{i,j}+f_{i - 1,j}$；
- 放置一种其他颜色的全部球，需要乘上当前可选的颜色数和剩下空位中的所有放置方案数，因此这部分转移为：$f_{i,j}=f_{i,j} + f_{i,j-1} \times \binom{(n\times k-i-(j-1)\times (k-1))}{k-1} \times (n - j + 1)$。

显然这个转移是会算重的，为了避免算重，我们钦定每次放置白球时都将白球放置在最靠左的空位上，每次放置某种颜色时也钦定第一个球放置在当前最靠左的空位上，因此最终的转移为：

$$f_{i,j}=f_{i-1,j}+f_{i,j-1} \times \binom{(n\times k-i-(j-1)\times (k-1))-1}{k - 2} \times (n - j + 1)$$

需要特判一下 $k=1$ 的情况。转移时注意 $j$ 的范围，可以预处理阶乘和逆元算组合数，最终时间复杂度为 $O(n ^ 2)$。好像还是挺有意思的一道题（可能状态似乎比较难想到？）。

```cpp
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 2e3 + 5;
const int maxm = 5e6 + 5;
const int mod = 1e9 + 7;
const int inf = 1e9;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

int fac[maxm], inv[maxm];
inline int qpow(int a, int b) {
	int res = 1;
	for (;b;b >>= 1, a = a * a % mod) {
		if (b & 1) res = res * a % mod;
	}
	return res;
}
inline void init(int n) {
	fac[0] = 1;
	for (int i = 1;i <= n * n;i++) fac[i] = fac[i - 1] * i % mod;
	inv[n * n] = qpow(fac[n * n], mod - 2);
	for (int i = n * n;i >= 1;i--) inv[i - 1] = inv[i] * i % mod;
}
inline int C(int n, int m) {
	return fac[m] * inv[n] % mod * inv[m - n] % mod;
}

int n, k, f[maxn][maxn];

signed main() {
	n = read(), k = read(), init(maxn);
	if (k == 1) return puts("1"), 0;
	for (int i = 0;i <= n;i++) f[i][0] = 1;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= i;j++) {
			f[i][j] = (f[i][j] + f[i - 1][j]) % mod;
			f[i][j] = (f[i][j] + f[i][j - 1] * (n - j + 1) % mod * C(k - 2, n * k - i - (j - 1) * (k - 1) - 1) % mod) % mod;
		}
	}
	printf("%lld\n", f[n][n]);
	return 0; 
}
```


---

## 作者：hzoi_liuchang (赞：1)

## 分析
观察这一道题的数据范围，我们可以使用 $n^2$ 的做法

一个比较容易得出的结论是，如果你从左向右数的话，那么白球的数量一定大于等于经你已选择的颜色种类数

因此，我们设 $f[i][j]$ 为当前已经放置了 $i$ 个白球和 $j$ 种其它颜色的球的合法方案数

下面我们考虑转移

首先， $f[i][j]$ 一定可以由 $f[i-1][j]$ 转移过来

因为如果当前你已经放置了 $i-1$ 个白球和 $j$ 种其他颜色的球，那么你在后面再放一个白球是没有影响的

接下来我们考虑 $f[i][j-1]$ 的转移

首先，当前已经选择了 $j-1$ 种颜色的球，那么我们还有 $i-j+1$ 种颜色没有选择

对于某一种颜色的球，如果我们选择了它，那么我们必须从中选出一个球放在最前面

这样可以避免重复的情况

此时，这一种颜色的球已经被选择了 $1$ 个放在最前面，还有 $1$ 个被涂成了白球

还剩下 $k-2$ 个

我们只需要从剩下的 $n \times k-i-1- (j-1) \times (k-1)$中选择 $k-2$ 个位置就可以

我们默认之前的 $j-1$ 种颜色的球已经放好

因此递推式为

$$f[i][j]=f[i-1][j]+f[i][j-1] \times (n-j+1) \times C_{n*k-i-1-(j-1)*(k-1)}^{k-2}$$

最后注意一下 $k=1$ 时的特判

## 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int maxn=2005;
int f[maxn][maxn],ny[maxn*maxn],jc[maxn*maxn],jcc[maxn*maxn];
int getC(int n,int m){
	return jc[n]*jcc[m]%mod*jcc[n-m]%mod;
}
signed main(){
	int n,k;
	scanf("%lld%lld",&n,&k);
	if(k==1){
		printf("1\n");
		return 0;
	}
	ny[1]=1;
	for(int i=2;i<=4000000;i++){
		ny[i]=(mod-mod/i)*ny[mod%i]%mod;
	}
	jc[0]=1,jcc[0]=1;
	for(int i=1;i<=4000000;i++){
		jc[i]=jc[i-1]*i%mod;
		jcc[i]=jcc[i-1]*ny[i]%mod;
	}
	for(int i=0;i<=n;i++) f[i][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			f[i][j]=f[i-1][j]%mod+f[i][j-1]%mod*(n-j+1)%mod*getC(n*k-i-1-(j-1)*(k-1),k-2)%mod;
		}
	}
	printf("%lld\n",f[n][n]%mod);
	return 0;

}
```

---

## 作者：lemondinosaur (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT2000)

[ATCODER传送门](https://atcoder.jp/contests/agc002/tasks/agc002_f)

设 $dp[i][j]$ 表示放完 $i$ 个白球和 $j$ 种有颜色的球的情况。

首先 $dp[i][j]$ 显然可以从 $dp[i-1][j]$ 转移（多放一个白球的方案）。

然后 $dp[i][j]$ 可以从 $dp[i][j-1]$ 转移（多添加一种颜色的方案）。

既然要多添加一种颜色，那么就要选择剩下 $n-j+1$ 种颜色填入，

并且要在剩下的 $nk-i-1-(j-1)\times(k-1)$ 个位置中选择 $k-2$ 个填入下一种颜色，也就是 $C_{nk-i-1-(j-1)\times (k-1)}^{k-2}$。

补充说明：

1. 排列长度 $n\times k$，放入 $i$ 个白球和 $j-1$ 种颜色（每种颜色为 $k-1$ 个）
2. 为什么是 $k-2$，如果不指定当前剩下的第一个位置为该颜色，
那么当选择其它颜色填入时这种方案就会算重，所以是 $k-2$，并且剩下的总位置也要减 1。

预处理阶乘和乘法逆元就可以了。
```cpp
#include <cstdio>
#define rr register
using namespace std;
const int mod=1000000007,N=2001;
int n,k,inv[N*N],fac[N*N],dp[N][N];
inline signed mo(int x,int y){
    return x+y>=mod?x+y-mod:x+y;
}
inline signed c(int n,int m){
   return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	inv[0]=inv[1]=fac[0]=fac[1]=1,scanf("%d%d",&n,&k);
	if (k==1) return !putchar(49);
	for (rr int i=2;i<=n*k;++i)
        inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
	for (rr int i=2;i<=n*k;++i) fac[i]=1ll*fac[i-1]*i%mod;
   for (rr int i=2;i<=n*k;++i) inv[i]=1ll*inv[i-1]*inv[i]%mod;
	for (rr int i=0;i<=n;++i) dp[i][0]=1;
	for (rr int i=1;i<=n;++i)
   for (rr int j=1;j<=i;++j)
	    dp[i][j]=mo(dp[i-1][j],1ll*dp[i][j-1]*(n-j+1)%mod*c(n*k-i-1-(j-1)*(k-1),k-2)%mod);
	return !printf("%d\n",dp[n][n]);
}
```

---

