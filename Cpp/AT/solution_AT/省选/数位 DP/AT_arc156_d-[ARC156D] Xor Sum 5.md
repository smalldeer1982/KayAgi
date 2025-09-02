# [ARC156D] Xor Sum 5

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc156/tasks/arc156_d

長さ $ N $ の非負整数列 $ A=(A_1,A_2,\dots,A_N) $ 、および正整数 $ K $ が与えられます。

$ 1\ \leq\ X_i\ \leq\ N\ (1\leq\ i\ \leq\ K) $ を満たす長さ $ K $ の正整数列 $ X=(X_1,X_2,\dots,X_K) $ は $ N^K $ 通り考えられますが、それらすべてに対する $ \displaystyle\ \sum_{i=1}^{K}\ A_{X_i} $ のビット単位 $ \mathrm{XOR} $ を求めてください。

   ビット単位 $ \mathrm{XOR} $ 演算とは  非負整数 $ A,\ B $ のビット単位 $ \mathrm{XOR} $ 、$ A\ \oplus\ B $ は、以下のように定義されます。

- $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。  
 一般に $ k $ 個の非負整数 $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ のビット単位 $ \mathrm{XOR} $ は $ (\dots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \dots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ の順番によらないことが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ K\ \leq\ 10^{12} $
- $ 0\ \leq\ A_i\ \leq\ 1000 $
- 与えられる入力はすべて整数
 
### Sample Explanation 1

$ X $ として考えられるのは $ (X_1,X_2)=(1,1),(1,2),(2,1),(2,2) $ の $ 4 $ 通りであり、それぞれに対する $ A_{X_1}+A_{X_2} $ は $ 20,40,40,60 $ です。よって答えは $ 20\ \oplus\ 40\ \oplus\ 40\ \oplus\ 60=40 $ となります。

## 样例 #1

### 输入

```
2 2
10 30```

### 输出

```
40```

## 样例 #2

### 输入

```
4 10
0 0 0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
11 998244353
314 159 265 358 979 323 846 264 338 327 950```

### 输出

```
236500026047```

# 题解

## 作者：Sol1 (赞：30)

给个简单做法，不用 Lucas 定理，不用生成函数！

考虑到异或满足相同抵消为 $0$，这是一个和模 $2$ 计数相似的性质，提示我们寻找双射。

不难发现对于一个序列 $(X_1,X_2,\cdots,X_K)$，如果它不是一个回文序列，则可以直接将其双射到它反过来的序列 $(X_K,X_{K-1},\cdots,X_1)$，两者的 $\sum A_{X_i}$ 显然是一样的，于是相互抵消。

于是我们只需要对回文的 $X$ 序列求 $\sum A_{X_i}$ 的异或和即可。

此时，如果 $K$ 是偶数，则将序列从中间折半，必有前后两半的 $\sum A_{X_i}$ 相等。于是可以直接将 $K$ 除以 $2$ 之后递归做。具体来说，设 $f_i$ 为 $K=i$ 时的答案，则我们有 $f_{2i}=2f_{i}$。

然而如果 $K$ 是奇数就不能直接折半了，因为最后整体的和要加上中间的一项。

于是一个很自然的想法就是把整体加的这一项记下来。发现这样就可以完成所有计算：

- 对于 $K$ 是奇数的情况，可以直接枚举中间的项是什么，然后把它加到整体加的项里面，即可转化为 $K$ 是偶数的情况。
- 对于 $K$ 是偶数的情况，最后一位的值只和整体加的量，以及折半以后可能的序列个数有关。前者已经被记录，后者只和 $N\bmod 2$ 有关，于是可以计算出最后一位；剩下的位就是折半后整体加当前的整体加的量的二分之一下取整的值。（这一部分可以结合下面的转移式理解）

于是我们就得到了最终的做法：

设 $f(i,j)$ 表示：对所有长度为 $i$ 的序列 $(X_1,X_2,\cdots,X_i)$，$j+\sum_{k=1}^i A_{X_k}$ 的异或和。

对于偶数 $i=2x$，有：

- $f(2x,j)=2f(x,\lfloor\frac{j}{2}\rfloor)+(Nj\bmod 2)$。

对于奇数 $i=2x+1$，有：

- $f(2x+1,j)=\bigoplus_{p=1}^N\big(2f(x,\lfloor\frac{j+A_p}{2}\rfloor)+(N(j+A_p)\bmod 2)\big)$。

边界状态：

- $f(1,j)=\bigoplus_{p=1}^N(A_p+j)$。

目标状态为 $f(K,0)$。

归纳易证第二维的最大值就是序列 $A$ 的最大值，而第一维显然只有 $\log K$ 个。转移再乘上一个 $N$，总复杂度即为 $O(N\log K\cdot \max A)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a[1005];
long long k, dp[77][1005];
bool vis[77][1005];

inline void Read() {
    cin >> n >> k;
    for (int i = 1;i <= n;i++) cin >> a[i];
}

inline long long Dfs(int dep, int pls) {
    if (vis[dep][pls]) return dp[dep][pls];
    if ((k >> dep) == 1) {
        vis[dep][pls] = 1;
        for (int i = 1;i <= n;i++) dp[dep][pls] ^= (a[i] + pls);
        return dp[dep][pls];
    }
    vis[dep][pls] = 1;
    if (!((k >> dep) & 1)) return dp[dep][pls] = (Dfs(dep + 1, pls >> 1) << 1) | ((pls & 1) && (n & 1));
    else {
        dp[dep][pls] = 0;
        for (int i = 1;i <= n;i++) dp[dep][pls] ^= (Dfs(dep + 1, (pls + a[i]) >> 1) << 1) | (((pls + a[i]) & 1) && (n & 1));
        return dp[dep][pls];
    }
}

int main() {
    Read();
    cout << Dfs(0, 0) << endl;
    return 0;
}
```















---

## 作者：mod998244353 (赞：16)

如果枚举 $A_i$ 出现的次数 $c_i$，那么答案可以写成如下式子：

$\operatorname{xor}_{\sum c_i=k}(\begin{pmatrix}k\\c_1,c_2,\cdots,c_n\end{pmatrix}\bmod2)\sum\limits_{i=1}^n A_ic_i$

$\begin{pmatrix}k\\c_1,c_2,\cdots,c_n\end{pmatrix}\equiv1\pmod2$ 时才会对答案有贡献。

$\begin{pmatrix}k\\c_1,c_2,\cdots,c_n\end{pmatrix}$ 其实可以写成组合数的形式：

$\begin{pmatrix}k\\c_1,c_2,\cdots,c_n\end{pmatrix}=\prod\limits_{i=1}^n\begin{pmatrix}k-\sum\limits_{j=1}^{i-1}c_i\\c_i\end{pmatrix}$

设 $n$ 在二进制下第 $i$ 位为 $n_{2,i}$

根据卢卡斯定理，$\begin{pmatrix}n\\m\end{pmatrix}\equiv\prod\limits_{i=0}^{\infty}\begin{pmatrix}n_{2,i}\\m_{2,i}\end{pmatrix}\pmod2$

而 $\begin{pmatrix}0\\0\end{pmatrix}=\begin{pmatrix}1\\0\end{pmatrix}=\begin{pmatrix}1\\1\end{pmatrix}=1,\begin{pmatrix}0\\1\end{pmatrix}=0$

所以 $\exists i,n_{2,i}=0,m_{2,i}=1$ 和 $\begin{pmatrix}n\\m\end{pmatrix}\equiv0\pmod2$ 互为充分必要条件。

也就是说，如果把 $n,m$ 看做是集合在二进制下的状态压缩，那么 $m$ 是 $n$ 的子集才会满足 $\begin{pmatrix}n\\m\end{pmatrix}\equiv1\pmod2$

所以 $\begin{pmatrix}k\\c_1,c_2,\cdots,c_n\end{pmatrix}\equiv1\pmod2$ 时，$c_1,c_2,\cdots,c_n$ 是集合 $k$ 的一种划分。

由于 $\lfloor\log_2 k\rfloor<40$，$c_1,c_2,\cdots,c_n$ 中最多 $40$ 个数非 $0$。

所以我们考虑数位 dp：

设 $f_{i,S}$ 表示末 $i-1$ 位已经确定，第 $[i,i+10]$ 位目前值是 $S$ 的所有方案的答案，$g_{i,S}$ 表示末 $i-1$ 位已经确定，第 $ [i,i+10] $ 位目前值是 $S$ 时的方案数对 $2$ 取模。

初始状态为 $f_{0,0}=0,g_{0,0}=1$。

显然由 $i$ 转移到 $i+1$，根据第 $i$ 位是不是 $1$ 来转移：（用 $a\leftarrow b$ 表示状态 $b$ 要转移到状态 $a$）

当 $k_{2,i}=0$ 时，$f_{i+1,\lfloor\frac{S}{2}\rfloor}\leftarrow f_{i,S},g_{i+1,\lfloor\frac{S}{2}\rfloor}\leftarrow g_{i,S}$

当 $k_{2,i}=1$ 时，枚举 $j$ 表示将 $i$ 划分给 $c_j$：$f_{i+1,a_j+\lfloor\frac{S}{2}\rfloor}\leftarrow f_{i,S},g_{i+1,a_j+\lfloor\frac{S}{2}\rfloor}\leftarrow g_{i,S}$

具体的转移细节看代码吧，时间复杂度 $O(n(\max{a_i})\log k)$：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2048,N=51;
int n,a[MAXN];
ll k,f[N+1][MAXN],g[N+1][MAXN];
bool vis[N+1][MAXN];//vis数组表示这个状态的方案数是否大于0
int main() {
    scanf("%d%lld",&n,&k);
    for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
    g[0][0]=vis[0][0]=1;
    for(int i=0; i<N; ++i)
        for(int j=0; j<MAXN; ++j)
            if(vis[i][j]) {//状态要方案数大于0
                if((k>>i)&1) {
                    for(int y=1,x; y<=n; ++y) {//枚举划分的a
                        x=a[y]+(j>>1);
                        g[i+1][x]^=g[i][j];
                        f[i+1][x]^=f[i][j];
                        vis[i+1][x]=true;
                        if(g[i][j]&j&1) f[i+1][x]^=(1ll<<i-1);//方案数为奇数且那一位为1
                    }
                } else {
                	vis[i+1][j>>1]=true;
                	f[i+1][j>>1]^=f[i][j];
                	if(g[i][j]&j&1) f[i+1][j>>1]^=(1ll<<i-1);
                	g[i+1][j>>1]^=g[i][j];
				}
            }
    printf("%lld\n",f[N][0]);
    return 0;
}
```

---

## 作者：DeaphetS (赞：13)

题目链接：[D - Xor Sum 5](https://atcoder.jp/contests/arc156/tasks/arc156_d)

题目大意：给定一个长度为 $N(1\le N\le 1000)$ 的数组 $A(0\le A_i\le 1000)$，以及一个正整数 $K(1\le K\le 10^{12})$。现在要在这 $N$ 个数字里挑一个 $A_i$ 出来，并重复 $K$ 次这样的操作，对应的得分就是挑出来的 $A_i$ 之和。一共有 $N^K$ 种挑选方案，求所有挑选方案对应得分的异或和。

### 简化问题

将问题转化成生成函数来表示，那就是令 $P(x)=(x^{A_1}+x^{A_2}+...+x^{A_N})^K$，并求所有系数为奇数对应项的指数之和。那么考虑模 $2$ 意义下的多项式运算，就是求满足 $[x^S](x^{A_1}+x^{A_2}+...+x^{A_N})^K$ 的值为 $1$ 对应的所有 $S$ 的异或和。

接着考虑模 $2$ 意义下的一个经典式子：

$$(x_1+x_2+...+x_n)^2\equiv x_1^2+x_2^2+...+x_n^2+2\sum_{i<j}x_ix_j\equiv x_1^2+x_2^2+...+x_n^2$$

反复套用对应式子，我们得到：

$$(x_1+x_2+...+x_n)^{2^k}\equiv x_1^{2^k}+x_2^{2^k}+...+x_n^{2^k}$$

其实对于这个式子，我们也可以用 $\texttt{Lucas}$ 定理的推论来证明：

- 经典推论：$(x+y)^P\equiv x^P+y^P\pmod P$，其中 $P$ 为质数（考虑 $\binom{P}{i}$ 不为 $P$ 的倍数当且仅当 $i=0$ 或 $P$）
- 对 $P=2$，得出 $(x+y)^2\equiv x^2+y^2 \pmod 2$
- 反复套用该式，得出 $(\sum_{i=1}^n x_i)^2\equiv (\sum_{i=1}^{n-1} x_i)^2+x_n^2\equiv ...\equiv \sum_{i=1}^n x_i^2$

回到原问题，考虑 $K$ 的二进制表达 $K=\sum_{i=1}^{M}2^{k_i}$，那么就有：

$$[x^S](x^{A_1}+x^{A_2}+...+x^{A_N})^K\equiv [x^S]\prod_{i=1}^M(x^{A_1\times 2^{k_i}}+x^{A_2\times 2^{k_i}}+...+x^{A_N\times 2^{k_i}})$$

记第 $i$ 次选择的数字下标为 $X_i$，于是问题就由求 $\sum_{i=1}^K A_{X_i}$ 的异或和变成了求 $\sum_{m=1}^M A_{X_m}\times 2^{k_m}=S$ 的异或和。

### 组合计数

我们可以将这一问题转化为一道组合计数问题：对每个结果 $S$，确定 $\sum_{m=1}^M A_{X_m}\times 2^{k_m}=S$ 的方案数。由于我们最后求的是异或和，那么我们只需要统计方案数为奇数的答案即可，进一步地，我们考虑求和结果在二进制的某一位上为 $1$ 的方案数。

考虑动态维护所有满足方案数为奇数的 $S$ 组成的集合。设当前考虑的是二进制第 $i$ 位上的答案，显然更低位的信息我们是不需要的，所以我们动态维护所有的 $\lfloor\frac{S}{2^i}\rfloor$。又因为当 $k_m>i$ 时，$A_{X_m}\times 2^{k_m}$ 对答案的第 $i$ 位不产生贡献，所以我们可以等到 $i=k_m$ 时再考虑对应 $A_{X_m}\times 2^{k_m}$ 的选择。

于是在过程中，当我们考虑到第 $i$ 位时，集合中的元素个数。可以估算得出，集合中元素的最大值对应上界为：

$$\sum_{j=0}^{i} \lfloor\frac{\max(A)\times2^j}{2^i}\rfloor \le \sum_{j=0}^{i}\frac{\max(A)\times2^j}{2^i}=\max(A)\times \sum_{j=0}^{i} 2^{-j}\le 2\max (A)$$

所以在这个过程中，集合的大小始终是不超过 $2\max (A)$ 的。于是我们直接暴力维护集合即可在 $O(N^2\log K)$ 的复杂度内解决问题，每次统计答案时只需要统计集合内有多少个奇数即可。使用 $\texttt{bitset}$ 可以进行进一步的常数优化。

要注意的是，由于在考虑前面几位的答案时，对于 $k_m>i$ 对应的 $A_{X_m}\times 2^{k_m}$ 选择方案数还没有被统计进来，所以实际上这时对应的方案数还要乘上一个 $N$ 的若干次方 $N^{\text{阿巴阿巴}}$。因此当还存在 $k_m>i$ 时，我们还需要根据 $N$ 的奇偶性来判断当前位置是否可能有值。此外当 $i=k_M$ 时我们也可以直接计算最终答案，具体实现见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2048
int n;
bitset<N>a,s,t;
long long k,ans;
int main()
{
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		a.flip(x);
	}
	s[0]=1;
	for(int i=0;i<=40;i++){
		for(int j=0;j<N;j++)if(s[j])
			s.flip(j/2),s.flip(j);
		if(k>>i&1){
			t.reset();
			k^=(1ll<<i);
			for(int x=0;x<N/2;x++)if(a[x])
				t=t^(s<<x);
			s=t;
		}
		if(k==0){
			long long res=0;
			for(int j=0;j<N;j++)if(s[j])res^=j;
			ans+=res<<i;
			return printf("%lld\n",ans),0;
		}
		if(n&1){
			long long o=0;
			for(int j=1;j<N;j+=2)if(s[j])o^=1;
			ans+=o<<i;
		}
	}
}
```


---

## 作者：wishapig (赞：9)

考虑记录每个下标在 $X$ 中出现的次数，分别为 $c_1,c_2,\cdots c_n$，那么：

- 和为 $\sum_{i=1}^nc_ia_i$，方案数为 $\dbinom{K}{c_1,c_2,\cdots ,c_n}$。

当后面这个组合数为偶数时，这种 $c$ 序列是没有贡献的，考虑什么时候这个组合数是奇数。

> 由 Lucas 定理的推论，这个组合数是奇数当且仅当在二进制下 $c_1,c_2,\cdots ,c_n$ 形成了对 $K$ 的划分。

因此，$K$ 的二进制表示中的每一个 $1$ 都是统一贡献到一个 $c_i$ 上的。

于是就可以设计数位 dp 了，设 $dp[i][j]$ 表示考虑 $K$ 的前 $i$ 个二进制位，第 $i$ 位及以上的进位为 $j$ 的方案数，那么第一位的大小为 $O(\log (K\cdot a_i))$，取 $50$，第二维的大小为 $O(a_i)$，有两倍常数，取 $2048$。

转移分两类，如果 $K$ 的第 $i$ 位为 $0$，那么这一位不产生贡献，转移（贡献方式为异或）为：
$$
dp[i-1][j]\rightarrow dp[i][\lfloor j/2\rfloor]
$$
如果 $K$ 的第 $i$ 位为 $1$，枚举这位分给了哪个 $a_t$，有转移：
$$
dp[i-1][j]\rightarrow dp[i][\lfloor j/2\rfloor+a_t]
$$
最低位在 dp 初始化时需要额外讨论一下，是容易的。

怎么计算答案？对第 $i$ 个二进制位，看有多少种加和的方案使和中的第 $i$ 位为 $1$，如果方案数是奇数那么就会有贡献，利用 $dp[i][]$ 的进位信息不难进行计算，注意需要异或上更高位的选择（因为 $dp[i][]$ 只决策到了前 $i$ 位，$K$ 中后面的 $1$，每个还是会有 $n$ 种分法的）。

总复杂度为 $O(n\cdot a_i\cdot \log(K\cdot a_i))$，常数较小。

考场代码，略丑

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int B=2048,L=50;
#define F first
#define S second
int dp[55][2050],a[1005];
int n; ll k,ans;
void calc(int i){
	int c=1;
	for (int j=i+1; j<L; j++)
		if ((k>>j)&1) c=c*n%2;
	if (!c) return;
	for (int j=0; j<B; j++)
		if (j%2==1 && dp[i][j]) ans^=1ll<<i;
}
int main(){
	scanf("%d%lld",&n,&k);
	for (int i=1; i<=n; i++) scanf("%d",&a[i]);
	if (k&1){
		for (int i=1; i<=n; i++) dp[0][a[i]]^=1;
	} else dp[0][0]=1;
	calc(0);
	for (int i=1; i<L; i++){
		if (!((k>>i)&1)){
			for (int j=0; j<B; j++) dp[i][j/2]^=dp[i-1][j];
		} else {
			for (int j=0; j<B; j++)
				for (int t=1; t<=n; t++) dp[i][j/2+a[t]]^=dp[i-1][j];
		}
		calc(i);
	}
	printf("%lld\n",ans);
}
```

---

## 作者：EnofTaiPeople (赞：6)

### Part1 问题陈述
题意给定 $N,K,a_{1\sim N}$，求 $\sum\limits_{i=1}^Ka_{X_i}$ 的异或和，其中 $X_i$ 会遍历 $N^K$ 种情况，$N,a_i\le1000,K\le10^{12}$。

### Part2 转化

看似这题很可做，但又不会转化。

考虑 $K$ 一般很大，所以许多 $X_i$ 会重复很多次，而且等价集合 $\{X_i\}$ 也会出现很多次。

要是 $\{X_i\}$ 的出现次数为偶数就好了，那样就可以抵消掉贡献了。

例如，$N=4$ 时，$\{1,1,1,2\}$ 这个集合会出现 $\dbinom 4 3=4$ 次，所以不会产生贡献，$N=5$ 时，$\{1,1,1,2,2\}$ 这个集合会出现 $\dbinom 5 3=10$ 次，也不会产生贡献，于是我就莫名其妙的扯到组合数上去了。

事实上，一个由 $a$ 个 $X_1$ 和 $b$ 个 $X_2$ 二元可重集会产生贡献当且仅当 $\dbinom{a+b}a\bmod2=1$，这就是组合数奇偶性，等价于 $a|(a+b)=a+b$。

### Part3 多重集组合数奇偶性
我们猜测多重集组合数 $\dbinom{a_1+\dots+a_n}{a_1,\dots,a_n}=\dfrac{(\sum\limits_{i=1}^na_i)!}{\prod\limits_{i=1}^na_i!}\bmod2=1$ 当且仅当 $a_1|\dots|a_n=a_1+\dots+a_n$，事实上这是正确的。


我们可以使用逐步 choose 的方法来证明，即 $\dbinom{a_1+\dots+a_n}{a_1,\dots,a_n}=\prod\limits_{i=1}^n\dbinom{\sum\limits_{j=1}^ia_j}{a_i}$，于是我们需要这些组合数全部都是奇数，这只要归纳递推回去就行了。

所以，原问题只有 $K$ 的每一个二进制位均被一个数字使用时才会产生贡献。

### Part4 使用递推实现

好像不能称之为动态规划吧，发现我们可以对每一个二进制位单独考虑，设 $f_{i,j}$ 表示还没有使用 $K$ 的第 $2^i$ 位，当前数字整除 $2^{i-1}$ 的值为 $j$，这部分因为之前最大的和不超过 $1000\times2^i$，所以第二维最多只要 $2048$ 就好了，暴力转移时间复杂度为 $na\log K$，可以通过。

### Part5 后记

这样的题目还是给个代码吧，其实还是有点意思的：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6,M=998244353;
using ll=long long;
ll f[59][2122],K,ans;
int n,a[N];
int main(){
	ios::sync_with_stdio(false);
	int i,j,k,l,r,x,y;
	cin>>n>>K;
	for(x=1;x<=n;++x)cin>>a[x];
	f[0][0]=1;
	for(x=0;x<=53;++x)
		if((K>>x)&1){
			for(y=1;y<=n;++y)
				for(k=0;k<2048;++k){
					f[x+1][a[y]+(k>>1)]^=f[x][k];
				}
		}else{
			for(k=0;k<2048;++k)
				f[x+1][k>>1]^=f[x][k];
		}
	for(x=1;x<=54;++x)
		if((n&1)||!(K>>x-1)){
			for(l=k=0;k<2048;++k)
				if(k&1)l^=f[x][k];
			if(l)ans|=1ll<<x-1;
		}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：do_while_true (赞：5)

异或有很好的性质，相同直接抵消。那考虑按照将 $X$ 看成多重集来划分等价类，仅大小为奇数的等价类贡献答案。考虑这个多重集的形态，假设下标 $i$ 出现了 $c_i$ 次，那么总的出现次数就是：$\binom{K}{c_1,c_2,\cdots,c_n}$（多重集的排列数）

欲求其出现次数奇偶性，考察其 $2$ 的次幂是否为 $0$，仿照 Kummer 定理，容易猜出 $2$ 的次幂为 $c_1+c_2+\cdots+c_n$ 在二进制下的进位次数，而证明与 Kummer 定理证明几乎一致故略去。那么现在 $\binom{K}{c_1,c_2,\cdots,c_n}$ 为奇数当且仅当 $c_1,c_2,\cdots,c_n$ 两两无交。（ Lucas 定理？）

也就是将 $K$ 二进制分解，每个二进制位分配给一个 $c_i$，这样得出来的 $c$ 才是会给答案产生贡献的。

那么思路就转到在数位上考虑，观察到 $N,A$ 都比较小，所以想到设数位 dp $f_{i,j}$ 表示从低到高考虑到第 $i$ 位，总和在第 $i$ 位这里进的位是 $j$，所有方案的异或是多少。如果这一位是 1 转移就枚举这个 1 分配给哪个 $A$，然后为了 $f$ 能够转移还要记一下模 2 下的方案数 $g$．

注意到 $j$ 的上界是 $\sum_{i\geq 1} \lfloor\frac{A}{2^i}\rfloor=\mathcal{O}(A)$，那么时间复杂度是 $\mathcal{O}(NA\log K)$．

补一下中间那个证明：

$v_2(n!)=\sum_{i\geq 1}\lfloor\frac{n}{2^i}\rfloor$，令 $\lfloor\frac{n}{2^i}\rfloor=S_i(n)$．

$v_2(\frac{n!}{c_1!c_2!\cdots})=\sum_{i\geq 1}S_i(n)-S_i(c_1)-S_i(c_2)-\cdots$．

那么 $S_i(n)$ 实际意义为 $n$ 截取最底 $i$ 个二进制位之后的值。

$\sum_{j}S_i(c_j)$ 实际为所有 $c$ 仅看除去最底 $i$ 个二进制位之后的值再求和。

$n=\sum_j c_j$，那么 $S_i(n)-\sum_{j}S_i(c_j)$ 即为“所有 $c$ 仅看最底 $i$ 个二进制位求和后再截掉最底 $i$ 位”，也就是在第 $i$ 位进了多少位。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
ll bit(int x){
	return 1ll<<x;
}
const int N=1010;
int n;
ll k,a[N];
ll f[41][N];
int g[41][N];
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n,k);
	for(int i=1;i<=n;i++)read(a[i]);
	g[0][0]=1;
	for(int i=0;i<40;i++)
		for(int j=0;j<=1000;j++)
			if(f[i][j]||g[i][j]){
				auto zy=[&](int v){
					f[i+1][v/2]^=f[i][j];
					g[i+1][v/2]^=g[i][j];
					if((v&1) && g[i][j])
						f[i+1][v/2]^=bit(i);
				};
				if(bit(i)&k){
					for(int o=1;o<=n;o++)
						zy(j+a[o]);
				}
				else
					zy(j);
			}
	ll ans=0;
	for(int j=0;j<=1000;j++){
		ans^=f[40][j];
		if(g[40][j])
			ans^=(1ll*j)<<40;
	}
	cout << ans << '\n';
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：Southern_Dynasty (赞：3)

相当妙的题。

异或有个很好的性质，就是异或两次会抵消。这样我们只需要考虑出现次数为奇数的方案即可。

我们设 $t_i$ 表示 $a_i$ 的出现次数。那么这种方案的和 $sum=\sum_{i=1}^{n}a_it_i$，出现次数为

$$
\prod_{i=1}^{n}\binom{k-\sum_{j=1}^{i-1}t_j}{t_i}
$$

可以这么理解：先把前 $i-1$ 个数选了，然后考虑 $a_i$ 放在哪些位置。

由于我们要求其 $\bmod 2$ 的值是否为 $1$，而只有一堆 $1$ 乘起来才是 $1$，所以只有当每个组合数都是 $1$ 的时候结果才是 $1$。现在问题转化为：给你一堆组合数，判断是否每个组合数对 $2$ 取模的值都是 $1$。

由 Lucas 定理，可得 $\binom{n}{m}\bmod 2=1$ 当且仅当不存在任何一个 $i$，使得 $m$ 的第 $i$ 位为 $1$ 而 $n$ 的第 $i$ 位为 $0$。换句话说，$m$ 的二进制表示是 $n$ 的二进制表示的**子集**。

再代回原式，$t_1$ 是 $k$ 的子集，$t_2$ 是 $k-t_1$ 的子集……我们会发现 $t_1,...t_n$ 构成了 $k$ 的一个**划分**！换句话说，对于 $k$ 二进制下的每一位 $1$，其只能分配给某一个 $t_i$。

然后我们逐位计算异或和。考虑数位 dp，设 $f_{i,j}$ 表示从低到高考虑到第 $i$ 位，$j$ 为 $sum$ 截掉 $i-1$ 及更低位之后的值（也就是 $sum$ 除以 $2^{i-1}$ 之后的值）。因为前 $i-1$ 位都计算过了，就只需要考虑后面的位。

初始有 $f_{0,0}=1$。然后考虑转移。假设枚举到第 $i$ 位（$0\sim60$，**不是** $k$ 的每一位），$k$ 在第 $i$ 位上的值为 $up$，那么有：

- $f_{i-1,j}=0$。方案数如果已经是偶数了那之后再怎么乘还是偶数，跳过。

- $up=0$，$f_{i,\lfloor\frac{j}{2}\rfloor}\leftarrow f_{i,\lfloor\frac{j}{2}\rfloor}\oplus f_{i,j}$ ，即 $f_{i,\lfloor\frac{j}{2}\rfloor}\leftarrow f_{i,\lfloor\frac{j}{2}\rfloor}\oplus 1$


- $up=1$，枚举这一位选什么。设选了 $a_p$，那么 $f_{i,\lfloor\frac{j+a_p}{2}\rfloor}\leftarrow f_{i,\lfloor\frac{j+a_p}{2}\rfloor}\oplus f_{i,j}$ ，即 $f_{i,\lfloor\frac{j+a_p}{2}\rfloor}\leftarrow f_{i,\lfloor\frac{j+a_p}{2}\rfloor}\oplus 1$。

最后在 dp 过程中统计答案。

第 $i$ 位的贡献不仅要考虑 $f_{i,j}$，还要考虑后面没选的位的方案数。设 $k$ 一共有 $M$ 位 $1$，当前考虑了前 $m$ 个 $1$，则后面的位的方案数为 $n^{M-m}$。显然这玩意只有当 $n$ 为奇数或者 $M=m$ 的时候才是奇数，会对答案产生贡献。

第一个条件容易判断，第二个条件可以记录一下 $k$ 最高的 $1$ 是哪一位。假设为 $high$，那么只有当此时的 $i\ge high$ 时满足条件。最后还要判断 $sum$ 的第 $i$ 位是否为 $1$，直接查 $j/j+a_p$ 的最低位即可。如果都满足条件，就给答案异或上 $2^i$。

时间复杂度 $O(n\max a_i\log k)$，因为 $j$ 的上界只有 $\max a_i$。空间容易通过滚动数组优化到 $O(n+\max a_i)$，但是注意 $j$ 还要加上个 $a_p$ 所以 dp 数组要开到 $2\max a_i$。

代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define gt getchar
#define pt putchar
#define fst first
#define scd second
typedef long long ll;
const int N=2005;
using namespace std;
using namespace __gnu_pbds;
typedef pair<int,int> pii;
inline bool __(char ch){return ch>=48&&ch<=57;}
template<class T> inline void read(T &x){
	x=0;bool sgn=0;char ch=gt();
	while(!__(ch)&&ch!=EOF) sgn|=(ch=='-'),ch=gt();
	while(__(ch)) x=(x<<1)+(x<<3)+(ch&15),ch=gt();
	if(sgn) x=-x;
}
template<class T,class ...T1> inline void read(T &x,T1 &...x1){
	read(x);
	read(x1...);
}
template<class T> inline void print(T x){
	static char st[70];short top=0;
	if(x<0) pt('-');
 	do{st[++top]=x>=0?(x%10+48):(-(x%10)+48),x/=10;}while(x);
    while(top) pt(st[top--]);
}
template<class T> inline void printsp(T x){
	print(x);
	putchar(' ');
}
template<class T> inline void println(T x){
	print(x);
	putchar('\n');
}
int n,a[N],high;
ll k,ans;
bool f[N],g[N];
signed main(){
	read(n,k);
	for(int i=1;i<=n;++i) read(a[i]);
	high=60;
	while(!((k>>high)&1)) high--;
	f[0]=1;
	for(int x=0;x<=60;++x){
		memset(g,0,sizeof(g));
		int up=(k>>x)&1;
		for(int val1=0;val1<=1000;++val1){
			if(!f[val1]) continue;
			if(!up){
				if(((n%2)||(x>=high))&&(val1&1)) ans^=(1ll<<x);
				g[val1>>1]^=1;
			}else{
				for(int i=1;i<=n;++i){
					int val2=val1+a[i];
					if(((n%2)||(x>=high))&&(val2&1)) ans^=(1ll<<x);
					g[val2>>1]^=1;
				}
			}
		}
		memcpy(f,g,sizeof(f));
	}
	println(ans);
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc156_d)

**题目大意**

> $n$ 个值 $c_1\sim c_n$ 填入 $a_1\sim a_k$，可以重复（相等的 $c$ 算不同元素），求所有 $\sum_{i=1}^k a_i$ 的异或和。
>
> 数据范围：$n,c_i\le 1000,k\le 10^{12}$。

**思路分析**

首先根据 Lucas 定理 $\binom nm\bmod 2=[m\subseteq n]$，那么假设我们知道 $c_1\sim c_n$ 的出现次数 $b_1\sim b_n$。

那么对应的方案数 $\binom{k}{b_1,\dots,b_n}$ 为奇数当且仅当 $b_1\sim b_n$ 构成了 $k$ 在二进制下的一个划分，即 $\forall i\ne j,b_i\operatorname{AND}b_j=0$。

那么我们只要知道每个 $k$ 的二进制位被哪个 $c_i$ 选了即可。

从低到高考虑每一个二进制位 $d$，可以直接 $dp_i$ 记录前面的位对当前的进位为 $i$ 的方案数，如果 $d\in k$ 则枚举 $a_i$，加入 $a_i\times 2^d$。

注意 $2\mid n$ 时如果 $d$ 小于 $k$ 的最高位，这些方案数始终是偶数，不能计算贡献（最高位有 $n$ 中方案）。

显然进位数不超过 $2V$，直接 dp 即可。

时间复杂度：$\mathcal O(nV\log k)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int V=2048;
ll ans,m;
int n;
bool f[V],g[V];
signed main() {
	scanf("%d%lld",&n,&m);
	vector <int> a(n);
	for(int &i:a) scanf("%d",&i);
	f[0]=1;
	for(int d=0;d<60;++d) {
		memset(g,0,sizeof(g));
		bool q=0;
		for(int i=0;i<V;++i) if(f[i]) {
			if(m&(1ll<<d)) for(int j:a) g[(i+j)>>1]^=1,q^=(i+j)&1;
			else g[i>>1]^=1,q^=i&1;
		}
		m^=m&(1ll<<d);
		if(q&&((n&1)||!m)) ans|=1ll<<d;
		memcpy(f,g,sizeof(f));
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Schi2oid (赞：2)

### 题意简述

给定 $N$ 个数的数列 $A$ 和一个整数 $K$。

对于所有长度为 $K$，值域为 $[1,N]$ 的数列 $p$，求出 $\sum _{i=1}^{K} a_{p_i}$ 的异或和。

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ K\ \leq\ 10^{12} $
- $ 0\ \leq\ a_i\ \leq\ 1000 $

### 思路分析
借助生成函数描述题意，即我们需要求出 $\bigoplus S$ ，其中 $[x^S](x^{a_1}+x^{a_2}+…+x^{a_n})^K \bmod 2=1$。设 $K$ 在二进制下分解为 $M$ 位，即 $K=\sum_{i=1}^{M} 2^{k_i}$，我们可以将式子改写成：
$$
[x^S]\prod_{m=1}^{M} (x^{a_1}+x^{a_2}+…+x^{a_n})^{2^{k_m}} \bmod 2 =1
$$

再考虑一个经典式子：
$$
(x_1+x_2+…+x_n)^2\equiv x_1^2+x_2^2+…+x_n^2 (\bmod 2)
$$

反复套用这一式子，我们得到：

$$
(x_1+x_2+…+x_n)^{2^t} \equiv x_1^{2^t}+x_2^{2^t}+…+x_n^{2^t} (\bmod 2)
$$

所以，我们可以将上述式子化为：

$$[x^S]\prod_{m=1}^{M} (x^{a_1 2^{k_m}}+x^{a_2 2^{k_m}}+…+x^{a_n 2^{k_m}}) \bmod 2 =1$$

再将这一式子的含义进行翻译，这相当于我们进行 $M$ 次选择，每次选择 $a$ 中的一个数，设第 $i$ 次选择 $a_{X_i}$，那么我们需要保证有奇数种选择序列使得 $\sum_{m=1}^M a_{X_m}2^{k_m}=S$，此时 $S$ 是一个有效的结果，再将所有的有效答案异或起来即为答案。

考虑怎么完成有效答案异或的过程，我们考察对于每一位，有多少种选择序列使得其最终的 $S$ 在这一位为 $1$。那么，如果有奇数种，那么最终答案在这一位上就是 $1$。我们从小到大考察每一位 $i$，动态统计对于哪些 $S$，构成它们的选择序列种数在这一位上是 $1$。我们直接将 $S$ 抹去后 $i$ 位的结果存在一个集合中，每挪动一位将集合内所有数右移一位，对于每一次选择，我们直接暴力枚举对于每一个存在于集合中的 $S$，其在这一轮选择了哪一个数，然后更新集合。在这里，如果某个 $S$ 的选择序列种数为偶数，显然我们可以直接视为这一个 $S$ 完全没有出现过，这是因为它们对于后续答案产生的贡献一定为 $0$。同时还要注意的是，如果在考察到某一次选择之后，某一位上是 $1$，虽然后续选择都不会改变每一个操作序列导出的 $S$ 在这一位上的值，但是不能忘记每一个操作序列都还会分裂成许许多多个不同的操作序列。设还需经过 $T$ 轮，那么最后它会变成 $N^T$ 种选择序列。因此，答案某一位是 $1$ 的充要条件其实包含两点：1）有奇数种选择序列使得其当前 $S$ 在这一位为 $1$。2） $N^T$ 是奇数。

关于集合大小，容易发现每次更新时只会将集合内已经存在的元素加上一个 $a_i$，而每挪动一位，集合里所有数都会减半。这个过程保证集合内最大值不会超过 $a$ 中最大值的两倍。因此，集合大小与 $N$ 同阶。

时间复杂度 $O(N^2\log K)$，借助 bitset 优化可以降低常数。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bitset<3000>A,S,T;
signed main(){
	int n,k,a;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		A.flip(a);
	}
	int ans=0;
	S[0]=1;
	for(int i=0;i<=60;i++){
		T.reset();
		for(int j=0;j<=2000;j++) if(S[j]) T.flip(j>>1); 
		S=T;
		if(k&1){
			T.reset();
			for(int j=0;j<=2000;j++) if(S[j]) T^=A<<j;
			S=T;
		}
		k>>=1;
		int c=0;
		for(int j=1;j<=2000;j+=2) if(S[j]) c^=1;
		if(c&&((n&1)||(!k))) ans^=1ll<<i;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：analysis (赞：0)

看了题解后只觉得自己太菜了

---

题目要求所有 $B = \sum_{i}^{k}A_{X_i}$ 的异或和。

看到这个式子这种选数累加的形式，我们不妨设一个 OGF：

$$
G(x) = (x^{A_1} + x^{A_2} + \cdots) ^ k
$$

上面这个式子的组合意义显然，$[x^B]G(x)$ 表示选数加和组成 $B$ 的方案数。

由于最后要求的是异或和，所以我们可以对 $G(x)$ 模 $2$。

最后答案即为 $\bigoplus_{B}[[x^B]G(x)=1]B$。

$k$ 很大，有 $10^{12}$，我们不可能直接硬刚上面的 OGF。

有一个式子：

$$
(a_1+a_2+\cdots)^2 = (a_1^2 + a_2^2 + \cdots + 2\sum_{i}\sum_{j}a_ia_j) \equiv (a_1^2 + a_2^2 + \cdots)\pmod{2}
$$

推广一下：

$$
(a_1+a_2+\cdots)^{(2^k)} \equiv (a_1^{(2^k)} + a_2^{(2^k)} + \cdots)\pmod{2}
$$

所以，上述 OGF 可以转化为：

$$
G(x) = \prod_{i=0,k_i=1}^{M}(x^{A_1 \cdot 2^{k_i}} + x^{A_2 \cdot 2^{k_i}} + \cdots)
$$

$2^{40} > 10^{12}$，所以 $M = 40$ 即可。

但是，这样仅仅优化了 OGF 乘的过程，并没有缩小 $x$ 的指数的值域，我们仍然不能做。

此时，我们可以考虑按位统计贡献。

- 对于最终答案的第 $i$ 位，任何一个数的第 $j(j \neq i)$ 位没有贡献。

对于 $j > i$ 的位，它没有贡献，所以我们可以在按位枚举到 $j$ 时再更新他的贡献。

对于 $j < i$ 的位，他已经没有贡献了。于是，我们可以把原来维护的上标 $B$，改为维护 $\lfloor\frac{B}{2^i}\rfloor$。

可以估算一下，枚举到第 $i$ 位时集合大小：

$$
\lfloor\frac{B}{2^{i-1}}\rfloor \leq \frac{|S_{lst}|}{2} + \max(A) \leq 2\max(A)
$$

可以接受。

需要注意的是：在判断第 $i$ 位的贡献时，虽然 $j > i$ 对这位上的取值时 $1$ 还是 $0$ 没有影响，但对于方案数有影响。方案最后会乘上 $n^{cnt}$（$cnt$ 表 $k$ 剩下几个 $1$）。

只有奇数与奇数相乘仍为奇数，所以在当前不是 $k$ 的最高位 $1$ 时要判是否 $n \equiv 1 \pmod{2}$，是才计算贡献。

剩下看代码应该就懂了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k;
bitset<3000> a, s, t;
int ans;
signed main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        int tmp;
        cin >> tmp;
        a[tmp] = a[tmp] ^ 1;
    }
    s[0] = 1;
    for (int i = 0; i <= 40; i++)
    {
        for (int j = 0; j < 3000; j++)
        {
            if (s[j])
            {
                s[j >> 1] = s[j >> 1] ^ 1;
                s[j] = s[j] ^ 1;
            }
        }
        if (k >> i & 1)
        {
            t.reset();
            k ^= (1ll << i);
            for (int x = 0; x < 3000; x++)
            {
                if (a[x])
                {
                    t = t ^ (s << x);
                }
            }
            s = t;
        }
        if (k == 0)
        {
            int res = 0;
            for (int j = 0; j < 3000; j++)
            {
                if (s[j])
                {
                    res ^= j;
                }
            }
            ans += res << i;
            cout << ans;
            return 0;
        }
        if (n & 1)
        {
            int o = 0;
            for (int j = 1; j < 3000; j += 2)
            {
                o ^= s[j];
            }
            ans += o << i;
        }
    }
}
```

---

