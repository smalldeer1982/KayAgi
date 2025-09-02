# [AGC039F] Min Product Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc039/tasks/agc039_f

$ N $ 行 $ M $ 列のマス目の全てのマスに $ 1 $ 以上 $ K $ 以下の整数を書き込む方法 $ K^{NM} $ 通りすべてに対して以下の値を求め、 それらすべての総和を $ D $ で割ったあまりを求めてください。

- $ NM $ 個の各マスに対し、それと同じ行あるいは同じ列のマス (自分自身を含む) に書かれた整数の最小値を求め、それら $ NM $ 個すべての積を取って得られる値

## 说明/提示

### 制約

- $ 1\ \leq\ N,M,K\ \leq\ 100 $
- $ 10^8\ \leq\ D\ \leq\ 10^9 $
- $ N,M,K,D $ は整数である
- $ D $ は素数である

### Sample Explanation 1

$ NM $ 個の値の積が $ 16 $ になる書き込み方が $ 1 $ 通り、$ 2 $ になる書き込み方が $ 4 $ 通り、$ 1 $ になる書き込み方が $ 11 $ 通りあります。

## 样例 #1

### 输入

```
2 2 2 998244353```

### 输出

```
35```

## 样例 #2

### 输入

```
2 3 4 998244353```

### 输出

```
127090```

## 样例 #3

### 输入

```
31 41 59 998244353```

### 输出

```
827794103```

# 题解

## 作者：小粉兔 (赞：33)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC039F.html](https://www.cnblogs.com/PinkRabbit/p/AGC039F.html)。

### 题意简述

有一个 $N \times M$ 的矩阵，其中元素是 $1 \sim K$ 之间的整数。显然总共有 $K^{N M}$ 种不同的矩阵。

定义一个矩阵的权值为：枚举每个元素 $(i, j)$，将这个元素的所在行和所在列中的所有元素（共 $N + M - 1$ 个）中的最小值求出来，记作 $f(i, j)$，则权值为所有 $f(i, j)$ 的乘积，即 $\displaystyle \prod_{\substack{1 \le i \le N \\ 1 \le j \le M}} f(i, j)$。

求所有 $K^{N M}$ 种不同的矩阵的权值之和，对 $\mathrm{MOD}$ 取模，其中 ${10}^8 \le \mathrm{MOD} \le {10}^9$。

- $1 \le N, M, K \le 100$。

### 题解

我们将这个矩阵称为 $A$。

考虑枚举 $A$ 的每一行的最小值和每一列的最小值，分别记作 $x_{1 \sim N}$ 和 $y_{1 \sim M}$。  
也就是 $\displaystyle x_i = \min_{j = 1}^{M} A_{i, j}$ 以及 $\displaystyle y_j = \min_{i = 1}^{N} A_{i, j}$。

假设 $x, y$ 已知，则迅速得到 $A$ 的权值就为 $\displaystyle \prod_{\substack{1 \le i \le N \\ 1 \le j \le M}} \min(x_i, y_j)$。

我们考虑一种可以在已知 $x, y$ 的条件下，在 $\mathcal O (N + M)$ 个乘法运算内求出此权值的方法：  
将 $x, y$ 从小到大排序，每次加入一个最小的元素，如果来自 $x$ 则称为加入一行，否则称为加入一列。  
假设已经加入 $i$ 行 $j$ 列，则加入一个元素 $t$ 时产生的贡献为 $t^{M - j}$（来自 $x$）或 $t^{N - i}$（来自 $y$）。  
将每次加入元素时产生的贡献全部相乘即可得到权值。

其原因是：因为从小到大加入，所以在第一次加入时本行/列就全部被这个元素限制了，直接乘上 $t$ 的还未被限制的元素数量次方。

以上是从小到大考虑，还有一种从大到小考虑的方法：  
每次加入一个最大的元素，假设已经加入 $i$ 行 $j$ 列，则加入一个元素 $t$ 时产生的贡献为 $t^j$（来自 $x$）或 $t^i$（来自 $y$）。

原因相似，因为从大到小加入，所以每个元素是被行列较晚加入的那个限制的，这就导致影响到的元素数量为已加入的行/列个数。

---

接下来会用到这两种求法。以上是 $x, y$ 固定的情况，现在我们考虑枚举 $x, y$。

首先可以发现 $x, y$ 是有序的（不同顺序算不同种），但上述过程的 $x, y$ 无序（不同顺序算同种，换句话说被人为排序了）。

这提示我们把 $x, y$ 看作无序，从小到大加入元素，但是必须一次性加入所有一样的元素，以便用多重组合数转为有序的情况。

枚举 $x, y$ 之后，其权值可以确定，但是还需要计算满足 $A$ 的行列最小值恰好等于 $x, y$ 的矩阵 $A$ 的数量。

「**恰好**」提示我们需要容斥：假设不是恰好，而是 $A$ 的行列最小值**大于等于** $x, y$。

也就是已知 $x, y$，对于 $A_{i, j}$，它的取值为 $\max(x_i, y_j) \sim K$ 之间的正整数。

如果我们把权值在 $[1, K]$ 内取反，可以发现「从小到大」枚举 $x, y$ 中的元素就变成了「从大到小」，恰好对应上述第二种方法。

枚举 $c$ 行 $d$ 列容斥，则这些行列的限制就不是**大于等于**而是**大于**，或者说是**大于等于**「原限制加 $1$」，且容斥系数为 ${(-1)}^{c + d}$。

可以把这 $c$ 行 $d$ 列混进从小到大加入 $x, y$ 中的元素的过程中，也就是从小到大加入，并且分为是否「被容斥」两种类型。

考虑这样的 DP 过程：令 $\mathrm{f}[t][i][j]$ 表示加入了 $x, y$ 中所有**小于等于** $t$ 的元素，所有可能情况下的系数之和。

注意必须一次加入所有相同元素以使用多重组合数确定还原成有序的 $x, y$ 的方法数量。

先枚举 $a$，加入 $a$ 行**不被容斥**的值为 $t$ 的行：

$${\color{red}{\mathrm{f}[t][i + a][j]}} \gets \left[ {\color{orange}{\binom{N - i}{a}}} \cdot {\color{blue}{t^{a (M - j)}}} \cdot {\color{green}{{(K - t + 1)}^{a j}}} \cdot {\color{red}{\mathrm{g}[i][j]}} \right]$$

然后枚举 $b$，加入 $b$ 列**不被容斥**的值为 $t$ 的列：

$${\color{red}{\mathrm{f}[t][i][j + b]}} \gets \left[ {\color{orange}{\binom{M - j}{b}}} \cdot {\color{blue}{t^{(N - i) b}}} \cdot {\color{green}{{(K - t + 1)}^{i b}}} \cdot {\color{red}{\mathrm{g}[i][j]}} \right]$$

然后枚举 $c$，加入 $c$ 行**被容斥**的值为 $t$ 的行：

$${\color{red}{\mathrm{f}[t][i + c][j]}} \gets \left[ {\color{orange}{\binom{N - i}{c}}} \cdot {\color{blue}{t^{c (M - j)}}} \cdot {\color{green}{{(K - t)}^{c j}}} \cdot {\color{brown}{{(-1)}^c}} \cdot {\color{red}{\mathrm{g}[i][j]}} \right]$$

最后枚举 $d$，加入 $d$ 列**被容斥**的值为 $t$ 的列：

$${\color{red}{\mathrm{f}[t][i][j + d]}} \gets \left[ {\color{orange}{\binom{M - j}{d}}} \cdot {\color{blue}{t^{(N - i) d}}} \cdot {\color{green}{{(K - t)}^{i d}}} \cdot {\color{brown}{{(-1)}^d}} \cdot {\color{red}{\mathrm{g}[i][j]}} \right]$$

其中 $\mathrm{g}$ 就表示上一阶段的 DP 数组。可以滚动数组优化，具体实现详见代码。

下面是代码，时间复杂度为 $\mathcal O (K N M (N + M))$：

```cpp
#include <cstdio>
#include <algorithm>

typedef long long LL;
int Mod;
const int MN = 105, MK = 105;

int Binom[MN][MN], Pow[MK][MN];
int N, M, K;
int f[2][MN][MN];

int main() {
	scanf("%d%d%d%d", &N, &M, &K, &Mod);
	for (int i = 0; i <= std::max(N, M); ++i) {
		Binom[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			Binom[i][j] = (Binom[i - 1][j - 1] + Binom[i - 1][j]) % Mod;
	}
	for (int i = 0; i <= K; ++i) {
		Pow[i][0] = 1;
		for (int j = 1; j <= std::max(N, M); ++j)
			Pow[i][j] = (LL)Pow[i][j - 1] * i % Mod;
	}
	int o = 0;
	f[0][0][0] = 1;
#define Z0(x) for (int i = 0; i <= N; ++i) for (int j = 0; j <= M; ++j) f[x][i][j] = 0;
	for (int t = 1; t <= K; ++t) {
		Z0(o ^ 1);
		for (int i = 0; i <= N; ++i) for (int j = 0; j <= M; ++j) if (f[o][i][j]) {
			int x = f[o][i][j], y = (LL)Pow[K - t + 1][j] * Pow[t][M - j] % Mod;
			for (int a = 0; i + a <= N; ++a, x = (LL)x * y % Mod)
				f[o ^ 1][i + a][j] = (f[o ^ 1][i + a][j] + (LL)Binom[N - i][a] * x) % Mod;
		} o ^= 1;
		Z0(o ^ 1);
		for (int i = 0; i <= N; ++i) for (int j = 0; j <= M; ++j) if (f[o][i][j]) {
			int x = f[o][i][j], y = (LL)Pow[K - t + 1][i] * Pow[t][N - i] % Mod;
			for (int b = 0; j + b <= M; ++b, x = (LL)x * y % Mod)
				f[o ^ 1][i][j + b] = (f[o ^ 1][i][j + b] + (LL)Binom[M - j][b] * x) % Mod;
		} o ^= 1;
		Z0(o ^ 1);
		for (int i = 0; i <= N; ++i) for (int j = 0; j <= M; ++j) if (f[o][i][j]) {
			int x = f[o][i][j], y = (LL)(Mod - Pow[K - t][j]) * Pow[t][M - j] % Mod;
			for (int c = 0; i + c <= N; ++c, x = (LL)x * y % Mod)
				f[o ^ 1][i + c][j] = (f[o ^ 1][i + c][j] + (LL)Binom[N - i][c] * x) % Mod;
		} o ^= 1;
		Z0(o ^ 1);
		for (int i = 0; i <= N; ++i) for (int j = 0; j <= M; ++j) if (f[o][i][j]) {
			int x = f[o][i][j], y = (LL)(Mod - Pow[K - t][i]) * Pow[t][N - i] % Mod;
			for (int d = 0; j + d <= M; ++d, x = (LL)x * y % Mod)
				f[o ^ 1][i][j + d] = (f[o ^ 1][i][j + d] + (LL)Binom[M - j][d] * x) % Mod;
		} o ^= 1;
	}
	printf("%d\n", f[o][N][M]);
	return 0;
}
```

注意到编译器是不会使用 Barrett Reduction 算法优化对变量取模的时间常数的。  
但是由于 AtCoder 实际上是支持 `__uint128_t` 的，所以可以使用手写的 Barrett Reduction 算法以大幅度减小常数。  
官方题解中提到了一种每个 $t$ 仅需分 $2$ 个阶段进行转移的做法，也就是不需要使用容斥原理，应该也有一半的常数。

---

## 作者：关怀他人 (赞：25)

### AGC 039F
#### Solution
首先，对于一个矩阵$A$，它的权值等价于重新填一个矩阵$B$，满足$B_{i,j}$要小于等于$A_{i,j}$对应位置上的那$n+m−1$个值中的最小值的方案数，等价于$B$中每行的最大值小于等于$A$中对应行的最小值，$B$中每列的最大值小于等于$A$中对应列的最小值的方案数。

那么最终答案可以转化为所有合法的矩阵对$(A,B)$的个数。

设$f[k][i][j]$表示已经确定$B$中$i$行的最大值，以及$A$中$j$列的最小值，并且它们都小于等于$k$的方案数。转移分为两步

1. 枚举$B$中有多少行的最大值为$k+1$，然后对于已经确定最小值的列，在$A$中填上大于等于$k+1$的数，对于没有确定最小值的列，在$B$中填上小于等于$k+1$的数，并满足在这些行中，每行至少有$1$个$k+1$。

2. 枚举$A$中有多少列的最小值为$k+1$，然后对于已经确定最大值的行，在$A$中填上大于等于$k+1$的数，并保证这些列中每列至少有一个数为$k+1$，对于没有确定最大值的行，在$B$中填上小于等于$k+1$的数。

额外记一个$0/1$表示转移的两步，注意需要预处理转移的系数，不然会TLE。

时间复杂度$\mathcal O(nmk(n+m))$
#### Code
```cpp
int n,m,K,MOD;
int C[MAXN][MAXN],coef[MAXN][MAXN][MAXN][2],f[MAXN][MAXN][MAXN][2];

int power(int x,int y){
    int res = 1;
    while(y){
        if(y & 1) res = 1ll * res * x % MOD;
        x = 1ll * x * x % MOD;
        y >>= 1;
    }
    return res;
}

void Init(int N){
    C[0][0] = 1;
    for(int i = 1;i <= N;i++){
        C[i][0] = C[i][i] = 1;
        for(int j = 1;j < i;j++)
            C[i][j] = add(C[i - 1][j],C[i - 1][j - 1]);
    }
}

int main(){
    scanf("%d%d%d%d",&n,&m,&K,&MOD);
    Init(max(n,m));
    for(int k = 1;k <= K;k++){
        for(int i = 0;i <= m;i++){
            int t = 1ll * power(K - k + 1,i) * sub(power(k,m - i),power(k - 1,m - i)) % MOD;
            coef[k][i][0][0] = 1;
            for(int j = 1;j <= n;j++)
                coef[k][i][j][0] = 1ll * coef[k][i][j - 1][0] * t % MOD;
        }
    }
    for(int k = 1;k <= K;k++){
        for(int i = 0;i <= n;i++){
            int t = 1ll * power(k,n - i) * (sub(power(K - k + 1,i),power(K - k,i))) % MOD;
            coef[k][i][0][1] = 1;
            for(int j = 1;j <= m;j++)
                coef[k][i][j][1] = 1ll * coef[k][i][j - 1][1] * t % MOD;
        }
    }
    f[1][0][0][0] = 1;
    for(int k = 1;k <= K;k++){
        for(int i = 0;i <= n;i++){
            for(int j = 0;j <= m;j++){
                for(int l = 0;l <= n - i;l++)
                    addmod(f[k][i + l][j][1],1ll * f[k][i][j][0] * C[n - i][l] % MOD * coef[k][j][l][0] % MOD);
                for(int l = 0;l <= m - j;l++)
                    addmod(f[k + 1][i][j + l][0],1ll * f[k][i][j][1] * C[m - j][l] % MOD * coef[k][i][l][1] % MOD);
            }
        }
    }
    printf("%d\n",f[K + 1][n][m][0]);
    return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：10)

### 说在题解前的话

感觉这道题挺好的，标解~~翻译~~也挺好的，为什么在兔下面呢？可能是说得不够清楚，我斗胆发表一下自己的理解。

## 题解

对于一个矩阵 $A$ 的贡献为 $\prod_{x,y}\min(\min_{1\le i\le N}A_{i,y},\min_{1\le j\le M}A_{x,j})$。

考虑转化贡献，对于每个矩阵 $B$ 满足：

$\forall x\in [1,N],y\in [1,M],B_{x,y}\le \min(\min_{1\le i\le N}A_{i,y},\min_{1\le j\le M}A_{x,j})$

都会有 1 的贡献。

那么所有的矩阵对 $(A,B)$ 的个数即为答案。

要构造出合法的矩阵对 $(A,B)$，那么在满足 $A,B$ 之间的限制下统计所有方案即可。

我们需要寻求一个好的满足限制的统计方式，于是我们先转换一下限制。

对 $B$ 有：

$\forall x\in [1,N],y\in [1,M],B_{x,y}\le \min_{1\le i\le N}A_{i,y}\& B_{x,y}\le \min_{1\le j\le M}A_{x,j}$

反之，对 $A$ 有：

$\forall x\in [1,N],y\in [1,M],A_{x,y}\ge \max_{1\le i\le N}B_{i,y}\& A_{x,y}\ge \max_{1\le j\le M}B_{x,j}$

显然有对应限制满足其一即可。

那么我们定义矩阵 $B$ 的行最大，即满足行小于且有至少一个等于值 $mx$，即：

$\forall i\in [1,N],j\in [1,M],B_{i,j}\le mx_{i}\&\exists j\in [1,M],B_{i,j}= mx_{i}$

于是有限制：

$\forall i\in [1,N],j\in [1,M],A_{i,j}\ge mx_{i}$

定义矩阵 $A$ 的列最小，即满足列大于且有至少一个等于值 $mn$，即：

$\forall i\in [1,N],j\in [1,M],A_{i,j}\ge mn_{j}\&\exists i\in [1,N],A_{i,j}= mn_{j}$

限制同理：

$\forall i\in [1,N],j\in [1,M],B_{i,j}\le mn_{j}$

那么现在我们就容易在满足这样的限制下统计所有方案：

我们从小到大枚举限制的值 $t$，并枚举有多少行/列的限制取这个值，设当前 $f_{i,j}$ 为 $B$ 中 $i$ 行已经确定了行最大，$A$ 中 $j$ 列已经确定了列最小的合法方案数，$g_{i,j}$ 为上一阶段的方案数。

发现对于 $i,j$ 转移时可以分开转移，即 $mn=t$ 和 $mx=t$ 互不影响，于是再设 $h_{i,j}$ 为只多转移了 $mx=t$ 的方案，再转移 $mn=t$ 至 $f_{i,j}$ 给下一阶段用。

对于 $i,j$，当 $mx_{i},mn_{j}$ 都确定时，有$A_{i,j}\in[\max(mx_{i},mn_{j}),K],B_{i,j}\in[1,\min(mx_{i},mn_{j})]$，那么只要满足能取到 $mx_{i},mn_{j}$ 就可以直接乘上方案数了，这个随便算一下容斥即可。

但我们这里是分开转移的，考虑当前选了行 $i$，使 $mx_{i}=t$ 。

那么对于 $A$ 中之前就已经确定了 $mn$ 的列 $j$，$mn_{j}$一定小于当前的限制值 $t$，于是 $A_{i,j}$ 的值就可以直接在 $[\max(mx_{i},mn_{j})=mx_{i},K]$ 中任选一个，而 $B_{i,j}$ 还不能确定其限制，在以后才会统计方案。

同理，对于那些 $A$ 中之前未已经确定 $mn$ 的列 $j$，$A_{i,j}$ 会在以后统计，而 $B_{i,j}$ 可以直接在 $[1,\min(mx_{i},mn_{j})=mx_{i}]$ 中选了。

注意这里要保证必须有一个 $B$ 选到 $mx_{i}$，要记得容斥一下。

当前选列 $j$，使 $mn_{j}=t$ 的转移同理。

对于 $B$ 中之前就已经确定了 $mx$ 的行 $i$，$A_{i,j}$ 的值就可以直接在 $[\max(mx_{i},mn_{j})=mn_{j},K]$ 中任选一个，而 $B_{i,j}$ 在以后统计方案。

对于 $B$ 中之前未已经确定 $mx$ 的行 $i$，$A_{i,j}$ 会在以后统计，而 $B_{i,j}$ 直接在 $[1,\min(mx_{i},mn_{j})=mn_{j}]$ 中选。

这里也要保证必须有一个 $A$ 选到 $mn_{j}$，容斥一下。

提前处理好转移系数，时间复杂度 $O(Knm(n+m))$。

## 代码

```cpp
inline int C(int x,int y)
{
	return F.Mod(F.Mod((ULL)inv[y]*inv[x-y])*fac[x]);
}
signed main()
{/*注：这里我取模变量与转移数组重名了，与上文描述不符。
实际上，上一阶段为G，中间阶段为H，下一阶段为I*/
	int i,j,k,p,mx;
	n=read();mx=Max(n,m=read());K=read();F=Fast_Mod(read());
	for(i=fac[0]=1;i<=mx;i++)
	{
		fac[i]=F.Mod((ULL)fac[i-1]*i);
	}
	for(inv[mx]=Inv(fac[mx]),i=mx-1;~i;i--)
	{
		inv[i]=F.Mod((ULL)inv[i+1]*(i+1));
	}
	for(i=1;i<=K;i++)
	{//限制为i
		for(j=0;j<=m;j++)
		{//之前选了j列
			p=F.Mod((ULL)Ksm(K-i+1,j)*(Ksm(i,m-j)-Ksm(i-1,m-j)+F.M));
			#define nw num[0][i][j]
			for(nw[0]=k=1;k<=n;k++)
			{//这次选了k行
				nw[k]=F.Mod((LL)nw[k-1]*p);
			}
			#undef nw
		}
	}
	for(i=1;i<=K;i++)
	{//限制为i
		for(j=0;j<=n;j++)
		{//之前选了j行
			p=F.Mod((ULL)Ksm(i,n-j)*(Ksm(K-i+1,j)-Ksm(K-i,j)+F.M));
			#define nw num[1][i][j]
			for(nw[0]=k=1;k<=m;k++)
			{//这次选了k列
				nw[k]=F.Mod((LL)nw[k-1]*p);
			}
			#undef nw
		}
	}
	for(G[0][0]=i=1;i<=K;i++)
	{//限制为i
		for(j=0;j<=n;j++)
		{//之前选了j行
			for(k=0;k<=m;k++)
			{//之前选了k列
				for(p=0;p<=n-j;p++)
				{//这次选了p行
					Add(H[j+p][k],F.Mod(F.Mod((ULL)C(n-j,p)*num[0][i][k][p])*G[j][k]));
				}
				for(p=0;p<=m-k;p++)
				{//这次选了p列
					Add(I[j][k+p],F.Mod(F.Mod((ULL)C(m-k,p)*num[1][i][j][p])*H[j][k]));
				}
			}
		}
		for(j=0;j<=n;j++)
		{
			for(k=0;k<=m;k++)
			{
				G[j][k]=I[j][k];
				H[j][k]=I[j][k]=0;
			}
		}
	}
	writenum(G[n][m],10);
	return output;
}
```

---

## 作者：喵仔牛奶 (赞：7)

# Preface

这个题 mak 对着我们讲了半小时多我才听懂 /kk

以及，我比较笨，所以题解比较长，包含了一些我觉得不太容易懂的细节。

# Solution
## Part I

如果知道了每行的最小值 $r_i$ 与每列的最小值 $c_i$，就可以得出权值：
$$\prod_{i=1}^{n}\prod_{j=1}^{m}\min\{r_i,c_i\}$$

满足 $r_i,c_i$ 的矩阵数直接不好算，不妨考虑计算每行每列最小值**大于等于** $r_i,c_i$ 的矩阵数：
$$\prod_{i=1}^{n}\prod_{j=1}^{m}(K-\max\{r_i,c_i\}+1)$$

考虑容斥。引入 $R_i,C_i$，表示是否钦定第 $i$ 行 / 列大于 $r_i/c_i$。枚举所有 $R_i,C_i$，可以计算满足的矩阵数：
$$\sum_{R,C}(-1)^{\sum R_i+\sum C_i}\prod_{i=1}^{n}\prod_{j=1}^{m}(K-\max\{r_i+R_i,c_i+C_i\}+1)$$

把第一个式子和上面的式子相乘：
$$f(r,c,R,C)=(-1)^{\sum R_i+\sum C_i}\prod_{i=1}^{n}\prod_{j=1}^{m}\min\{r_i,c_i\}(K-\max\{r_i+R_i,c_i+C_i\}+1)$$
$$ans=\sum_{r,c}\sum_{R,C}f(r,c,R,C)$$

这样一来，我们需要做的就变成了数 $r,c,R,C$ 四个序列的权值和。

## Part II

我们定义一个点 $(i,j)$ 的贡献是 $\min\{r_i,c_i\}(K-\max\{r_i+R_i,c_i+C_i\}+1)$。

观察一下 $f$，我们发现对于一个位置 $(i,j)$，如果确定了 $r_i,c_i$（以及 $r_i+R_i,c_i+C_i$）的大小关系，就可以确定 $(i,j)$ 的贡献。

设 $f_{k,i,j}$ 是用 $1\sim k$ 的数，填了 $i$ 个 $r_i,R_i$， $j$ 个 $c_i,C_i$，已经**确定贡献的点**的贡献乘积，再乘上最前面那个容斥系数（没填过的 $R_i,C_i$ 当成 $0$），在所有方案中的**和**。

转移时，从小到大枚举 $k$。这样转移有一个好处，就是 $r_i,c_i$ 只会是 $k$，并且 $r_i+R_i,c_i+C_i$ 只会是 $k$ 或 $k+1$。也就是说，我们只要先填 $R_i,C_i=0$ 时的情况，再填 $R_i,C_i=1$ 时的情况，就可以保证 $\min$ 里面和 $\max$ 里面的数都有**单调性**！


因为 $R_i,C_i$ 的贡献只有 $0,1$，可以枚举它们的值来转移。由于 $r_i,c_i$ 的转移**互相独立**（也就是填的数的贡献之和它自己有关），所以可以**分次转移**：
- 第一次，转移 $r_i$，且 $R_i=0$。枚举新填的行数 $d$，易得 $d(m-j)$ 个格子中 $\min=r_i$（这些格子的 $r_i,c_i$ 没有被填过），$dj$ 个格子中 $\max=r_i$（这些格子的 $c_i$ 被填过了，填上 $r_i=k$ 后无法再填）。
- 第二次，转移 $c_i$，且 $C_i=0$。转移类似上一个。
- 第三次，转移 $r_i$，且 $R_i=1$。枚举新填的行数 $d$，转移类似第一个，不过别忘了 $\sum R_i$ 加上了 $d$，容斥系数要乘上 $(-1)^d$。
- 第四次，转移 $c_i$，且 $C_i=1$。转移类似上一个。

把它们都写出来：
$$\displaystyle f_{k,i+d,j}\gets f_{k-1,i,j}\times\binom{n}{d}k^{d(m-j)}(K-k+1)^{dj}$$
$$\displaystyle f_{k,i,j+d}\gets f_{k-1,i,j}\times\binom{m}{d}k^{d(n-i)}(K-k+1)^{di}$$
$$\displaystyle f_{k,i+d,j}\gets (-1)^d f_{k-1,i,j}\times\binom{n}{d}k^{d(m-j)}(K-k)^{dj}$$
$$\displaystyle f_{k,i,j+d}\gets (-1)^d f_{k-1,i,j}\times\binom{m}{d}k^{d(n-i)}(K-k)^{di}$$

注意，对于一个 $k$，要一个转移**全部完成**后才能进行下一个转移（可以见代码）。

然后就做完了。根据 Part I 的结论，题目所求答案是所有 $r,c,R,C$ 的贡献和，即为 $f_{K,N,M}$。

时间复杂度 $\mathcal{O}(KNM(N+M))$，比较卡常。比较有效的手段是预处理幂与组合数。

# Code

```cpp
namespace Milkcat {
	using namespace Math;
    typedef long long LL;
    typedef pair<LL, LL> pii;
    const int N = 105;
    typedef DMint MI;
	LL n, m, V, mod; MI C[N][N], f[N][N][N], g[3][N][N];
	int pown1(int x) { return x & 1 ? -1 : 1; }
    int main() {
		cin >> n >> m >> V >> mod, MI::setMod(mod);
        f[0][0][0] = C[0][0] = 1;
        REP(i, 1, max(n, m)) REP(j, 0, max(n, m)) {
        	if (!j) C[i][j] = 1;
        	else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
        REP(k, 1, V) {
        	vector<MI> pk(n * m + 1), pvk(n * m + 1), pr(n * m + 1);
        	pk[0] = pvk[0] = pr[0] = 1;
        	REP(i, 1, n * m) {
        		pk[i] = pk[i - 1] * k;
        		pvk[i] = pvk[i - 1] * (V - k + 1);
        		pr[i] = pr[i - 1] * (V - k);
			}
        	mems(g, 0);
        	REP(i, 0, n) REP(j, 0, m) {
        		if (!f[k - 1][i][j].x) continue;
        		REP(d, 0, n - i) g[0][i + d][j] += C[n - i][d] * pk[d * (m - j)] * pvk[d * j] * f[k - 1][i][j];
			}
        	REP(i, 0, n) REP(j, 0, m) {
        		if (!g[0][i][j].x) continue;
        		REP(d, 0, m - j) g[1][i][j + d] += C[m - j][d] * pk[d * (n - i)] * pvk[d * i] * g[0][i][j];
			}
        	REP(i, 0, n) REP(j, 0, m) {
        		if (!g[1][i][j].x) continue;
        		REP(d, 0, n - i) g[2][i + d][j] += C[n - i][d] * pk[d * (m - j)] * pr[d * j] * g[1][i][j] * pown1(d);
			}
        	REP(i, 0, n) REP(j, 0, m) {
        		if (!g[2][i][j].x) continue;
        		REP(d, 0, m - j) f[k][i][j + d] += C[m - j][d] * pk[d * (n - i)] * pr[d * i] * g[2][i][j] * pown1(d);
			}
		}
		cout << f[V][n][m] << '\n';
		return 0;
    }
}
```

---

## 作者：xht (赞：4)

## [Min Product Sum](https://atcoder.jp/contests/agc039/tasks/agc039_f)

### 题意

- 有一个 $n \times m$ 的矩阵 $a$，每个位置上有一个 $[1,k]$ 的整数。
- 对于一种填数方案，设 $f(x,y) = \min(\min_{i=1}^n a_{i,y}, \min_{j=1}^m a_{x,j})$，则这种方案的权值为 $\prod_{x=1}^n \prod_{y=1}^m f(x,y)$。
- 求一共 $k^{nm}$ 种方案的权值和。
- $n,m,k \le 100$，答案对 $P$ 取模。

### 题解

首先转化题意：

- 有两个 $n \times m$ 的矩阵 $a,b$，每个位置上有一个 $[1,k]$ 的整数。
- 另外要求 $b_{x,y} \le \min(\min_{i=1}^n a_{i,y}, \min_{j=1}^m a_{x,j})$。
- 求方案数。

显然这两者是等价的。

设 $x_i = \min_{j=1}^m a_{i,j}$，$y_j = \min_{i=1}^n a_{i,j}$，假设我们已经设定了所有 $x_i,y_j$，考虑如何求方案数。

对于 $a$，$a_{i,j}$ 可以填 $[\max(x_i, y_j), k]$；对于 $b$，$b_{i,j}$ 可以填 $[1,\min(x_i,y_i)]$。

然而这样填是有问题的，并不能保证最小值恰好 $x_i,y_j$，于是需要容斥一下，即枚举有多少行多少列的最小值大于设定值，乘上 $-1$ 的那么多次方。

考虑 DP，从小到大填 $x_i,y_i$，设 $f_{t,i,j}$ 表示已经填了 $1 \sim t$，用了 $i$ 行 $j$ 列，$a$ 已经填了这 $i$ 行 $j$ 列的交的位置，$b$ 已经填了这 $i$ 行 $j$ 列的并的位置，的方案数。

转移时枚举填 $t$ 的不被容斥的行列数 $p,q$，被容斥的行列数 $u,v$，则有：
$$
f_{t,i+p+u,j+q+v} \leftarrow (-1)^{u+v} \binom {n-i}{p,u} \binom {m-j}{q,v} \cdot (k-t+1)^{iq+pj+pq}(k-t)^{iv+pv+uj+uq+uv}t^{(p+u)(m-j)+(n-i)(q+v)-(p+u)(q+v)} \cdot f_{t-1,i,j}
$$
然而设 $n,m,k$ 同阶，这个 DP 复杂度是 $\mathcal O(n^7)$，显然要优化。

依然从小到大枚举 $t$，在这一层转移时，可以发现我们不必同时枚举 $p,q,u,v$，而只需要依次枚举，每次把贡献计算清楚即可。

具体而言，先让 $f_t$ 继承 $f_{t-1}$。

再枚举 $p$，转移为：
$$
f_{t,i+p,j} \leftarrow \binom {n-i}{p} \cdot (k-t+1)^{pj}t^{p(m-j)} \cdot f_{t,i,j}
$$
再枚举 $q$，转移为：
$$
f_{t,i,j+q} \leftarrow \binom {m-j}{q} \cdot (k-t+1)^{iq}t^{q(n-i)} \cdot f_{t,i,j}
$$
再枚举 $u$，转移为：
$$
f_{t,i+u,j} \leftarrow (-1)^u\binom {n-i}{u} \cdot (k-t)^{uj}t^{u(m-j)} \cdot f_{t,i,j}
$$
再枚举 $v$，转移为：
$$
f_{t,i,j+v} \leftarrow (-1)^v\binom {m-j}{v} \cdot (k-t)^{iv}t^{v(n-i)} \cdot f_{t,i,j}
$$
时间复杂度 $\mathcal O(n^4)$，很卡常，要进行一定程度的预处理，尽可能减少取模次数。

### 代码

```cpp
const int N = 107;
int n, m, k;
int f[N<<2][N][N], g[N][N*N], c[N][N];

inline void upd(int &x, int y, int z) {
	x = (x + 1ll * y * z) % P;
}

int main() {
	rd(n, m, k), rd(P);
	init(max(n, m));
	for (int i = 0; i <= k; i++) {
		g[i][0] = 1;
		for (int j = 1; j <= n * m; j++) g[i][j] = 1ll * g[i][j-1] * i % P;
	}
	for (int i = 0; i <= max(n, m); i++)
		for (int j = 0; j <= i; j++) c[i][j] = binom(i, j).x;
	f[0][0][0] = 1;
	for (int t = 1, o = 0; t <= k; t++) {
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++)
				if (!!f[o][i][j]) {
					ll x = f[o][i][j], y = 1ll * g[k-t+1][j] * g[t][m-j] % P;
					for (int p = 0; i + p <= n; p++, (x *= y) %= P) upd(f[o+1][i+p][j], c[n-i][p], x);
				}
		++o;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++)
				if (!!f[o][i][j]) {
					ll x = f[o][i][j], y = 1ll * g[k-t+1][i] * g[t][n-i] % P;
					for (int q = 0; j + q <= m; q++, (x *= y) %= P) upd(f[o+1][i][j+q], c[m-j][q], x);
				}
		++o;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++)
				if (!!f[o][i][j]) {
					ll x = f[o][i][j], y = P - 1ll * g[k-t][j] * g[t][m-j] % P;
					for (int u = 0; i + u <= n; u++, (x *= y) %= P) upd(f[o+1][i+u][j], c[n-i][u], x);
				}
		++o;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++)
				if (!!f[o][i][j]) {
					ll x = f[o][i][j], y = P - 1ll * g[k-t][i] * g[t][n-i] % P;
					for (int v = 0; j + v <= m; v++, (x *= y) %= P) upd(f[o+1][i][j+v], c[m-j][v], x);
				}
		++o;
	}
	print(f[k<<2][n][m]);
	return 0;
}
```

---

## 作者：Lgx_Q (赞：1)

很厉害的一道 Ad-hoc 题！假定我们填写的矩阵为 $A$。

直接填写 $A$ 计算贡献是基本做不到的，考虑挖掘一些神奇的东西。

**问题转化**：考虑 $\prod\limits_{i=1}^n \prod \limits_{j=1}^m f(i,j)$ 相当于构造另一个 $B$ 矩阵，满足 $B_{i,j}\le \min(A_{i,1...m},A_{1...n,j})$，问矩阵对 $(A,B)$ 的个数。

继续挖掘条件，发现 $\forall (i,j), \ B_{i,j} \le \min A_{i,1...m} \Leftrightarrow \forall (i,j) , \ A_{i,j} \ge \max B_{i,1...m}$，列同理。

所以我们两边一起跑，设 $x_i=\max B_{i,1...m},\ y_j=\min A_{1...n,j}$。

而矩阵对合法的充要条件转化为 $\forall (i,j) , \ B_{i,j} \le \min(x_i,y_j) \ \wedge \ A_{i,j} \ge \max(x_i,y_j)$，且 $B_{i,1...m}$ 至少一个等于 $x_i$，$A_{1...n,j}$ 至少一个等于 $y_j$。

依次填写 $x_{1...n},y_{1...m}$，设 $f[i,x,y]$ 表示填写了 $\le k$ 的数，其中 $x_{1...n}$ 填写了 $x$ 个，其中 $y_{1...m}$ 填写了 $y$ 个。

考虑在填写 $x_{1...n},y_{1...m}$ 时一起填写矩阵 $A,B$。对于 $B_{i,j}$，当填写了 $x_i,y_j$ 中较小者后计算贡献；对于 $A_{i,j}$，当填写了 $x_i,y_j$ 中较大者后计算贡献。

考虑从 $f[i-1,x,y]$ 转移过来，枚举 $p,q$ 表示 $x_{1...n},y_{1...m}$ 中等于 $=k$ 的数的个数。

+ 对于 $x_s=k,\ y_t<k$，那么 $A_{s,t}$ 贡献为 $k-i+1$。

+ 对于 $x_s=k,\ y_t\ge k$，那么 $B_{s,t}$ 贡献为 $i$，并且对于每个 $s$ 都至少一个 $B_{s,t}$ 等于 $i$。

+ 对于 $x_s\le k,\ y_t=k$，那么 $A_{s,t}$ 贡献为 $k-i+1$，并且对于每个 $t$ 都至少一个 $A_{s,t}$ 等于 $i$。

+ 对于 $x_s>k,\ y_t=k$，那么 $B_{s,t}$ 贡献为 $i$。

枚举的 $p,q$ 之间显然没有任何关系，可以分步转移。

预处理一些必要的系数，时间复杂度 $O(knm(n+m))$。

代码中部分变量名与上述分析中的不同。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define mkp make_pair
#define pir pair<ll,ll>
#define ull unsigned ll
#define pb push_back
#define i128 __int128
using namespace std;
const ll maxn=110;
ll n, m, t, mod;
ll power(ll a,ll b=mod-2){
	ll s=1;
	while(b){
		if(b&1) s=s*a%mod;
		a=a*a%mod; b>>=1;
	} return s;
}
ll f[maxn][maxn], g[maxn][maxn], r[maxn][maxn], c[maxn][maxn], pw[maxn][maxn];
ll P_pw[maxn][maxn][maxn], P_r[maxn][maxn][maxn];
int main(){
	scanf("%lld%lld%lld%lld",&n,&m,&t,&mod);
	c[0][0]=1;
	for(ll i=1;i<=n||i<=m;i++){
		c[i][0]=1;
		for(ll j=1;j<=i;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod; 
	}
	for(ll i=1;i<=t;i++) pw[0][i]=1;
	for(ll i=1;i<=n||i<=m;i++)
		for(ll j=1;j<=t;j++) pw[i][j]=pw[i-1][j]*j%mod;
	for(ll i=1;i<=n||i<=m;i++)
		for(ll j=1;j<=t;j++)
			r[i][j]=(power(j,i)-power(j-1,i)+mod)%mod;
	for(ll i=0;i<=n||i<=m;i++)
		for(ll j=1;j<=t;j++){
			P_pw[i][j][0]=P_r[i][j][0]=1;
			for(ll k=1;k<=n||k<=m;k++)
				P_pw[i][j][k]=P_pw[i][j][k-1]*pw[i][j]%mod,
				P_r[i][j][k]=P_r[i][j][k-1]*r[i][j]%mod;
		}
	f[0][0]=1;
	for(ll k=1;k<=t;k++){
		memset(g,0,sizeof g); 
		for(ll i=0;i<=n;i++)
			for(ll j=0;j<=m;j++){
				for(ll x=0;i+x<=n;x++){
					g[i+x][j]=(g[i+x][j]+f[i][j]*P_r[m-j][k][x]%mod*
					P_pw[j][t-k+1][x]%mod*c[n-i][x])%mod;
				}
			}
		memset(f,0,sizeof f); 
		for(ll i=0;i<=n;i++)
			for(ll j=0;j<=m;j++){
				for(ll y=0;j+y<=m;y++){
					f[i][j+y]=(f[i][j+y]+g[i][j]*P_pw[n-i][k][y]%mod*
					P_r[i][t-k+1][y]%mod*c[m-j][y])%mod;
				}
			}
	} printf("%lld",f[n][m]);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc039_f)

**题目大意**

> 对于一个 $n\times m$ 的值域 $[1,k]$ 的矩阵 $A$，定义 $x_i$ 表示第 $i$ 行最小值，$y_j$ 表示第  $j$ 列最小值。
>
> 定义一个矩阵权值为 $\prod_{i=1}^n\prod_{j=1}^m\min(x_i,y_j)$，求所有矩阵权值和。
>
> 数据范围：$n,m,k\le 100$。

**思路分析**

考虑如何刻画矩阵的权值。

假设我们已知 $\{x_i,y_j\}$，那么一个矩阵的权值就是有多少个矩阵 $B$ 使得 $B_{i,j}\le \min(x_i,y_j)$。

同理 $A$ 矩阵就要求 $A_{i,j}\ge \max(x_i,y_j)$，但是要容斥至少一个 $A_{i,j}=x_i$，容斥处理某一列 $A_{i,j}>x_i$ 即可。

我们从大到小填每个 $x_i,y_j$，插入时处理对应行列的贡献，注意到我们可以分步转移，即每次插入若干个 $x/y$ 相等的正常行或列 或有容斥限制的行或列。

具体来说，我们设 $f_{v,i,j}$ ，表示插入了值域为 $[1,v]$ 的元素，已经填了 $i$ 行 $j$ 列，分步转移如下：

- 插入 $p$ 个被正常的行：
  $$
  f_{v,i+p,j}\gets f_{v,i,j}\times \binom{n-i}p\times (v^{m-j}\times  (k-v+1)^j)^p
  $$
  即有 $j$ 个列的值 $<k$，这些交点的 $\max(x_i,y_j)$ 确定可以填 $A_{i,j}$，每个 $k-v+1$ 种方案，$m-j$ 个列的值 $\ge k$，这些交点的 $\min(x_i,y_j)$ 确定，可以填 $B_{i,j}$，每个有 $v$ 种方案。

- 插入 $p$ 个被容斥的行：
  $$
  f_{v,i+p,j}\gets f_{v,i,j}\times\binom{n-i}p\times(-1)^p\times  (v^{m-j}\times(k-v)^j)^p
  $$
  此时 $j$ 个 $\max(x_i,y_j)$ 确定的交点因为容斥必须填 $>v$ 的数，方案数 $k-v$，容斥系数 $(-1)^p$。

- 插入 $p$ 个正常的列：
  $$
  f_{v,i,j+p}\gets f_{v,i,j}\times\binom{m-j}{p}\times (v^{n-i}\times (k-v+1)^i)^p
  $$
  意义同上。

- 插入 $p$ 个被容斥的列：
  $$
  f_{v,i,j+p}\gets f_{v,i,j}\times \binom{m-j}p\times (-1)^p\times (v^{n-i}\times (k-v)^i)^p
  $$
  意义同上

根据如上过程分步转移即可，本题轻微卡常，注意实现常数。

时间复杂度 $\mathcal O(knm(n+m))$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace FastMod {
typedef unsigned long long ull;
typedef __uint128_t uLL;
ull b,m;
inline void init(ull B) { b=B,m=ull((uLL(1)<<64)/B); }
inline ull mod(ull a) {
	ull q=((uLL(m)*a)>>64),r=a-q*b;
	return r>=b?r-b:r;
}
};
#define o(x) FastMod::mod(x)
const int MAXN=105;
int f[MAXN][MAXN],g[MAXN][MAXN],pw[MAXN][MAXN],C[MAXN][MAXN];
void trs(int &x,ll y) { x=o(x+y); }
signed main() {
	int n,m,k,MOD;
	scanf("%d%d%d%d",&n,&m,&k,&MOD);
	FastMod::init(MOD);
	for(int i=0;i<=max(n,m);++i) for(int j=C[i][0]=1;j<=i;++j) {
		C[i][j]=o(C[i-1][j]+C[i-1][j-1]);
	}
	for(int i=1;i<=k;++i) for(int j=pw[i][0]=1;j<=max(n,m);++j) {
		pw[i][j]=o(1ll*pw[i][j-1]*i);
	}
	f[0][0]=1;
	for(int v=1;v<=k;++v) {
		memcpy(g,f,sizeof(g)),memset(f,0,sizeof(f));
		for(int i=0;i<=n;++i) for(int j=0;j<=m;++j) if(g[i][j]) {
			//add normal row
			ll x=g[i][j],y=o(1ll*pw[k-v+1][j]*pw[v][m-j]); int *B=C[n-i];
			for(int p=0;p<=n-i;++p,x=o(x*y)) trs(f[i+p][j],x*B[p]);
		}
		memcpy(g,f,sizeof(g)),memset(f,0,sizeof(f));
		for(int i=0;i<=n;++i) for(int j=0;j<=m;++j) if(g[i][j]) {
			//add normal col
			ll x=g[i][j],y=o(1ll*pw[k-v+1][i]*pw[v][n-i]); int *B=C[m-j];
			for(int p=0;p<=m-j;++p,x=o(x*y)) trs(f[i][j+p],x*B[p]);
		}
		memcpy(g,f,sizeof(g)),memset(f,0,sizeof(f));
		for(int i=0;i<=n;++i) for(int j=0;j<=m;++j) if(g[i][j]) {
			//add reverse row
			ll x=g[i][j],y=MOD-o(1ll*pw[k-v][j]*pw[v][m-j]); int *B=C[n-i];
			for(int p=0;p<=n-i;++p,x=o(x*y)) trs(f[i+p][j],x*B[p]);
		}
		memcpy(g,f,sizeof(g)),memset(f,0,sizeof(f));
		for(int i=0;i<=n;++i) for(int j=0;j<=m;++j) if(g[i][j]) {
			//add reverse col
			ll x=g[i][j],y=MOD-o(1ll*pw[k-v][i]*pw[v][n-i]); int *B=C[m-j];
			for(int p=0;p<=m-j;++p,x=o(x*y)) trs(f[i][j+p],x*B[p]);
		}
	}
	printf("%d\n",f[n][m]);
	return 0;
}
```

---

## 作者：Phartial (赞：0)

非常厉害的题！

设 $r_i=\min\limits_{j=1}^ma_{i,j}$，$c_j=\min\limits_{i=1}^na_{i,j}$，则矩阵 $a$ 的权值即为 $\displaystyle\prod_{i=1}^n\prod_{j=1}^m\min(r_i,c_i)$。

假设我们已经知道了 $r_i,c_i$，则我们想求出第 $i$ 行的最小值恰好为 $r_i$ 且第 $j$ 行的最小值恰好为 $c_j$ 的矩阵个数。

“恰好”启示我们使用容斥将其变形为第 $i$ 行的最小值大于等于 $r_i+p_i$（$p_i$ 为 01 变量，表示该行是否被钦定为大于 $r_i$）且第 $j$ 列的最小值等于等于 $c_j+q_j$（$q_j$ 与 $p_i$ 意义类似）。

此时有 $a_{i,j}\ge\max(r_i+p_i,c_j+q_j)$，总方案数为 $\displaystyle\prod_{i=1}^n\prod_{j=1}^m(k-\max(r_i+p_i,c_j+q_j)+1)$。

把权值和方案数乘起来可以得到答案为：

$$
\sum_{r,c,p,q}(-1)^{\sum p+\sum q}\prod_{i=1}^n\prod_{j=1}^m\min(r_i,c_i)(k-\max(r_i+p_i,c_j+q_j)+1)
$$

中间的 $\min$ 和 $\max$ 并不好处理，于是考虑以从小到大的顺序填充 $r$ 和 $c$，并顺便钦定得到 $p,q$。

设 $f_{t,i,j}$ 表示此时已经填完了（并钦定了对应的 $p,q$）$i$ 个 $r$ 和 $j$ 个 $c$，且填的数都 $\le t$ 时所有方案的权值和（只考虑由这 $i$ 行 $j$ 列组成的子矩阵）。

转移时，考虑枚举 $x,y,u,v$ 表示有 $x$ 行 $r$ 填了 $t$，有 $u$ 行 $r$ 填了 $t$ 且被钦定，有 $y$ 行 $c$ 填了 $t$，有 $v$ 行 $c$ 填了 $t$ 且被钦定。转移式很混乱邪恶，时间复杂度也是混乱邪恶的 $\mathcal{O}(n^7)$，显然过不去。

注意到 $x,y,u,v$ 的枚举其实相对独立，于是考虑把它分为多个阶段进行转移。

设只枚举了 $x$/枚举了 $x,y$/枚举了 $x,y,u$/枚举了 $x,y,u,v$ 四个阶段的状态分别为 $f_{t,i,j,0/1/2/3}$，则有转移：

$$
f_{t,i,j,0}=\sum_xf_{t-1,i-x,j,3}{n-i+x\choose x}t^{x(m-j)}(k-t+1)^{xj}\\
f_{t,i,j,1}=\sum_yf_{t,i,j-y,0}{m-j+y\choose y}t^{y(n-i)}(k-t+1)^{yi}\\
f_{t,i,j,2}=\sum_uf_{t,i-u,j,1}(-1)^u{n-i+u\choose u}t^{u(m-j)}(k-t)^{uj}\\
f_{t,i,j,3}=\sum_vf_{t,i,j-v,2}(-1)^v{m-j+v\choose v}t^{v(n-i)}(k-t)^{vi}\\
$$

最终答案为 $f_{k,n,m,3}$，时间复杂度 $\mathcal{O}(n^4)$，可能有点卡常。

```cpp
#include <iostream>
#include <atcoder/modint>

using namespace std;
using LL = atcoder::modint;

const int kN = 102;

int n, m, k, kMod;
LL c[kN][kN], p[kN][kN * kN], f[kN][kN][kN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> k >> kMod;
  LL::set_mod(kMod);
  for (int i = 0; i <= max(n, m); ++i) {
    c[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }
  }
  for (int i = 0; i <= k; ++i) {
    p[i][0] = 1;
    for (int j = 1; j <= n * m; ++j) {
      p[i][j] = p[i][j - 1] * i;
    }
  }
  f[0][0][0] = 1;
  for (int t = 1; t <= k; ++t) {
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= m; ++j) {
        LL _f = 0;
        for (int x = 0; x <= i; ++x) {
          _f += f[t - 1][i - x][j] * c[n - i + x][x] * p[t][x * (m - j)] * p[k - t + 1][x * j];
        }
        f[t][i][j] = _f;
      }
    }
    for (int i = n; i >= 0; --i) {
      for (int j = m; j >= 0; --j) {
        LL _f = 0;
        for (int y = 0; y <= j; ++y) {
          _f += f[t][i][j - y] * c[m - j + y][y] * p[t][y * (n - i)] * p[k - t + 1][y * i];
        }
        f[t][i][j] = _f;
      }
    }
    for (int i = n; i >= 0; --i) {
      for (int j = m; j >= 0; --j) {
        LL _f = 0;
        for (int u = 0; u <= i; ++u) {
          _f += ((u & 1) ? -1 : 1) * f[t][i - u][j] * c[n - i + u][u] * p[t][u * (m - j)] * p[k - t][u * j];
        }
        f[t][i][j] = _f;
      }
    }
    for (int i = n; i >= 0; --i) {
      for (int j = m; j >= 0; --j) {
        LL _f = 0;
        for (int v = 0; v <= j; ++v) {
          _f += ((v & 1) ? -1 : 1) * f[t][i][j - v] * c[m - j + v][v] * p[t][v * (n - i)] * p[k - t][v * i];
        }
        f[t][i][j] = _f;
      }
    }
  }
  cout << f[k][n][m].val();
  return 0;
}
```

---

