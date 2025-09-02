# [USACO21DEC] HILO P

## 题目描述

Bessie 有一个数 $x+0.5$，其中 $x$ 是某个 $0$ 到 $N$ 之间的整数（$1\le N\le 5000$）。

Elsie 正试着猜这个数。她可以以如下形式对于某个 $1$ 到 $N$ 之间的整数提问：「$i$ 是大了还是小了？」如果 $i$ 大于 $x+0.5$，Bessie 会回答 "HI!"，如果 $i$ 小于 $x+0.5$ 则回答 "LO!"。

Elsie 想到了以下猜测 Bessie 的数的策略。在进行任何猜测之前，她创建了一个包含 $N$ 个整数的序列，其中从 $1$ 到 $N$ 的每个数均恰好出现一次（换句话说，这个序列是长为 $N$ 的一个排列）。然后她遍历这一列表，按列表中的数的顺序依次猜数。然而，Elsie 会跳过所有不必要的猜测。也就是说，如果 Elsie 将要猜某个数 $i$，而 Elsie 之前已经猜过了某个 $j < i$ 并且 Bessie 回答 "HI!"，Elsie 不会再猜 $i$，而是继续猜序列中的下一个数。类似地，如果她将要猜某个数 $i$，而她之前已经猜过了某个 $j > i$ 并且 Bessie 回答 "LO!"，Elsie 不会再猜 $i$，而是继续猜序列中的下一个数。可以证明，使用这一策略，对于 Elsie 创建的任意序列，她都可以唯一确定 $x$。

如果我们将所有 Bessie 回答的 "HI" 或 "LO" 拼接成一个字符串 $S$，那么 Bessie 说 "HILO" 的次数为 $S$ 等于 "HILO" 的长为 $4$ 的子串数量。

Bessie 知道 Elsie 将要使用这一策略，并且已经选定了值 $x$，但她不知道 Elsie 会使用什么排列。你的目标是对于所有 Elsie 可能选用的排列，计算 Bessie 说 "HILO" 的次数之和，对 $10^9+7$ 取模。

## 说明/提示

【样例解释1】

在这个测试用例中，Bessie 的数是 $2.5$。

例如，如果 Elsie 的排列是 $(4,1,3,2)$，那么 Bessie 会说 ""HILOHILO"，总计两次 "HILO"。又例如，如果 Elsie 的排列是 $(3,1,2,4)$，那么 Bessie 会说 "HILOLO"，总计一次 "HILO"。

【样例解释2】

确保输出总和对 $10^9+7$ 取模的结果。

【数据范围】

- 测试点 3-10 满足 $N\le 50$；
- 测试点 11-18 满足 $N\le 500$；
- 测试点 19-26 没有额外限制。

## 样例 #1

### 输入

```
4 2```

### 输出

```
17```

## 样例 #2

### 输入

```
60 10```

### 输出

```
508859913```

# 题解

## 作者：ETHANK (赞：19)

> 题目难度：USACO P/省选-

不难发现猜 HI 的数不会使猜 LO 的数被跳过。设 $y=N-x$ ，那么原题相当于将 $a_1,a_2,\dots,a_x$ 和 $b_1,b_2,\cdots,b_y$ 排列，只记录 $a,b$ 的每次下标最大值的出现位置，求期望 $ba$ 的数量。

这可以 dp ，设 $dp[i][j][0/1]$ 为当前最大出现 $a_i,b_j$ 以及最后一个出现的是 $a/b$ ，通过简单的转移可以做到 $O(N^3)$ 。前缀和优化可以做到 $O(N^2)$ ，这里不再赘述。

比较吸引我的是在赛后讨论中看到的 $O(N)$ 做法，这里简单的证明一下。

结论：令 $H_0=0,H_N=1+\frac{1}{2}+\cdots+\frac{1}{N}$ . 有
$$
E[\#(ba)]=\frac{1}{2}(H_x+H_y-H_N+\frac{y}{N})\\
$$
证明：

$x=0$ 或 $y=0$ 时结论显然成立，不妨对 $y$ 归纳。即证 $(x,y)\to(x,y+1)$ 后期望的变化为：
$$
\Delta=\frac12(\frac1{y+1}-\frac{1}{N+1}+\frac{y+1}{N+1}-\frac{y}{N})=\frac{1}{2(y+1)}-\frac{y}{2N(N+1)}
$$
计算对 $a_1a_2\dots a_xb_2b_3\dots b_y$ 的排列中插入 $b_1$ 对答案的贡献， $b_1$ 只能排在第一个出现的 $b$ 之前，否则会被跳过。$y$ 个 $b$ 将 $x$ 个 $a$ 分成 $y+1$ 段，故第一个 $b$ 前 $a$ 的期望个数为 $\frac{x}{y+1}$ 个。设前面有 $k$ 个 $a$ 。

接下来，只要 $b_1$ 被插入在 $k$ 个 $a$ 中最大的 $a$ 前面，都会对期望贡献一个 "ba" 。最大的 $a$ 的期望位置为：
$$
E[index]=\left\{\begin{matrix} 
 \frac{k+1}2,\qquad k>0\\
 0,\qquad k=0\\
\end{matrix}\right. 
$$
$k=0$ 即为原排列首项是 $b$ 的概率，为 $\frac{y}{N}$ 。 能得出：
$$
\Delta = \frac{1}{N+1}(\frac{1}{2}\times(\frac{x}{y+1}+1)-\frac{y}{N}\times\frac{0+1}{2})\\
=\frac{1}{2(y+1)}-\frac{y}{2N(N+1)}
$$


```cpp
const int N=2e5+5,P=1e9+7;
int n,x;
ll H[N],inv[N];
int main(){
    n=read(),x=read();
    inv[1]=1;
    ll fac = 1;
    rep(i,2,n){
        inv[i]=(P-P/i)*inv[P%i]%P;
        fac = fac*i%P;
    }
    rep(i,1,n)H[i]=(H[i-1]+inv[i])%P;
    int y = n-x;
    cout<<(fac*inv[2]%P*(inv[n]*y%P+H[x]+H[y]-H[n])%P+P)%P;
    return 0;
}
```



---

## 作者：牛瓜瓜 (赞：18)

本篇文章**翻译**自官方题解。由于笔者考场上没有通过此题，如有不当之处，还请在评论区指出。

还有这里因该比 Gold 那题难不少吧，建议评紫(?。

------

> Suppose that we have already constructed some prefix of the permutation, and there are $j$ remaining non-redundant values below Bessie's number and $k$ remaining non-redundant values above Bessie's number (we define non-redundant numbers as numbers that Elsie could guess that would give her more information). Also, consider the two cases where Bessie has most recently said either "HI" or "LO". Let $b=0$ be the case where Bessie has most recently said "LO" and let $b=1$ be the case where Bessie has most recently said "HI". Then, the expected number of "HILO"s for the original problem is just the case where $j=x, k=N-x, b = 0$.

考虑 dp 状态，假设我们已经算到了某个位置，并且剩余了 $j$ 个有效的小于 $x$ 的值和 $k$ 个*有效*的大于 $x$ 的值（在这里*有效*指之后还可以被猜到的数）。此时，我们令状态中的 $b=0$ 若前一次是`LO`，$b=1$ 若前一次是`HI`。这样的话，`HILO`出现的期望次数就是 $j=x, k=N-x, b = 0$ 对应的状态。



> Thus, it is sufficient to count the expected number of "HILO"s for each $j \leq x, k \leq N-x,$ and $b = 0$ or $b=1$. Call this quantity $dp[b][j][k]$. Now, note that all redundant values do not affect the expected number of "HILOs", so we ignore all of them. Then, there are $j+k$ possible values for the next number in the permutation, each of which occurs with probability $\frac{1}{j+k}$.

因而，我们只需对每个 $j \leq x, k \leq N-x$ 计算`HILO`出现的**期望**次数。定义状态为 $dp[b][j][k]$。因为所有这些*无效*的数对答案都没有影响，所以说排列中的下一个数只有 $j+k$ 种可能的值，每种数出现的概率都为 $\frac{1}{j+k}$。



> We will first consider the case where $b=0$. Suppose that the next value in th.e permutation is less than $x+0.5,$ of which there are $j$ possibilities. Denote these values as $v_0, v_1, v_2, \cdots v_{j-1}$ such that $x+0.5 > v_0 > v_1 > v_2 \cdots > v_{j-1}$.

首先考虑 $b=0$ 的边界情况，假设排列中的下一个数是比 $x+0.5$ 小的 $j$ 种情况之一，记这样的数为 $v_0, v_1, v_2, \cdots v_{j-1}$，满足 $x+0.5 > v_0 > v_1 > v_2 \cdots > v_{j-1}$。



> Suppose the next value in the permutation is $v_{j_2}$ for some $0 \leq j_2 < j$. Then, Bessie says "LO" (because $v_{j_2} < x+0.5$) and there are $j_2$ remaining nonredundant values below Bessie's number. The $k$ initial nonredundant values above Bessie's number are still nonredundant, so the expected number of HILOs in the remaining sequence of values is $dp[0][j_2][k]$.

设再往下的一个数为 $v_{j_2}$ 且  $0 \leq j_2 < j$，那么 Bessie 将会说`LO`因为$v_{j_2} < x+0.5$），然后将会剩下 $j_2$ 个*有效*的值小于 $x$ ，而原本的 $k$ 个大于 $x$ 的有效的值将会保持不变，那期望下剩下的`HILO`的出现次数就是 $dp[0][j_2][k]$。



> Similarly, if we consider the values greater than $x+0.5,$ which we label $x+0.5 < u_0 < u_1 < u_2 \cdots < u_{k-1},$ if we choose one of these values $u_{k_2}$, Bessie says "HI" and there are $k_2$ remaining nonredundant values above Bessie's number, so the expected number of HILOs in the remaining sequence of values is $dp[1][j][k_2]$.
>
> 

相似地，如果我们考虑的值是比 $x+0.5$ 大的，即 $x+0.5 < u_0 < u_1 < u_2 \cdots < u_{k-1}$ 中的一个数 $u_{k_2}$，Bessie 就会说`HI`，并剩下 $j_2$ 个*有效*的值大于于 $x$ ，那期望下之后`HILO`的出现次数就是 $dp[1][j_2][k]$。



> So, we have the recurrence $dp[0][j][k] = \frac{\sum_{j_2 < j} dp[0][j_2][k] + \sum_{k_2 < k} dp[1][j][k_2]}{j+k}$.

因此，我们得到转移方程 $dp[0][j][k] = \frac{\sum_{j_2 < j} dp[0][j_2][k] + \sum_{k_2 < k} dp[1][j][k_2]}{j+k}$。



> For computing $dp[1][j][k],$ we can apply the same technique. However, since Bessie has just said "HI", if we now choose a value $v_{j_2} < x+0.5,$ Bessie will then say "LO" and the number of "HILO"s increases by one. We choose a value less than $x+0.5$ with probability $\frac{j}{j+k},$ so the expected number of "HILO"s increases by $\frac{j}{j+k}.$

在计算 $dp[1][j][k]$ 时，我们可以使用相似的技巧。不过由于Bessie可能刚说了`HI`，如果我们现在选的数 $v_{j_2} < x+0.5$ 则 Bessie 就会说`LO`那么`HILO`的出现次数就会加一。因为选一个小于 $x+0.5$  的值的概率为 $\frac{j}{j+k}$，所以`HILO`的期望出现次数会增加 $\frac{j}{j+k}$。



> So, we have the recurrence $dp[1][j][k] = \frac{\sum_{j_2 < j} dp[0][j_2][k] + \sum_{k_2 < k} dp[1][j][k_2]}{j+k} + \frac{j}{j+k}.$

这样，我们得到转移方程 $dp[1][j][k] = \dfrac{\sum_{j_2 < j} dp[0][j_2][k] + \sum_{k_2 < k} dp[1][j][k_2]}{j+k} + \frac{j}{j+k}$。



> Now, we can compute every value of $dp[b][j][k]$ by iterating over all $j_2 < j, k_2 < k$ and using the above recurrences. Since there are $N^2$ dp states and we sum over $N$ smaller states, this leads to a time complexity of $\mathcal{O}(N^3),$ which is enough for the first two subtasks.

至此，我们可以通过遍历一遍 $j_2 < j, k_2 < k$ 来计算得到 $dp[b][j][k]$ 。因为有 $N^2$ 个状态，每次转移 $\mathcal O(N)$，因此我们得到一个时间复杂度 $\mathcal{O}(N^3)$ 的算法，可以通过前两个 subtask。



> To speed this up, note that the bottleneck of the runtime comes from computing the terms like $\sum_{j_2 < j} dp[0][j_2][k].$ Now, suppose we are computing the value $dp[0][j][k]$ and want to find the value $\sum_{j_2 < j} dp[0][j_2][k]$ without using a loop. To do this, note that we have already computed the value of $dp[0][j-1][k],$ which required the value of $\sum_{j_2 < j-1} dp[0][j_2][k].$ Since we have already computed $\sum_{j_2 < j-1} dp[0][j_2][k],$ we can use the fact that $\sum_{j_2 < j} dp[0][j_2][k] = dp[0][j-1][k]+\sum_{j_2 < j-1} dp[0][j_2][k],$ which takes $\mathcal O(1)$ time instead of $\mathcal O(N)$ time to compute.

考虑优化转移，注意到算法的瓶颈在于计算像 $\sum_{j_2 < j} dp[0][j_2][k]$ 的东西。我们计算 $dp[0][j][k]$ 时希望不用遍历就得到 $\sum_{j_2 < j} dp[0][j_2][k]$ 的值。注意到我们计算 $dp[0][j-1][k]$ 时就已经用到 $\sum_{j_2 < j-1} dp[0][j_2][k]$，我们注意到 $\sum_{j_2 < j} dp[0][j_2][k] = dp[0][j-1][k]+\sum_{j_2 < j-1} dp[0][j_2][k]$ 来把转移的时间复杂度由 $\mathcal O(N)$ 优化到 $\mathcal O(1)$。



> Since we can now compute the $N^2$ terms of the DP in $\mathcal O(1)$ time each, our overall time complexity is now $\mathcal{O}(N^2).$

这样我们就可以以 $\mathcal O(1) $ 复杂度计算 $N^2$ 个状态，最终时间复杂度为 $\mathcal{O}(N^2)$，可以通过此题。

---
翻译到此结束，以下提供优质 500B 代码。
```
// Nothing is Given, Everything is Earned.
#include<bits/stdc++.h>
using namespace std;
using L=long long;
const int N=5.1e3,P=1e9+7;
int dp[2][N][N],sum1[N],sum0[N],inv[N];
int main()
{
	int n,x,y; cin>>n>>x; y=n-x;
	inv[1]=1;
	for(int i=2;i<=n;i++) inv[i]=1ll*(P-P/i)*inv[P%i]%P;
	for(int j=0;j<=x;j++)
		for(int k=0;k<=y;k++)
		{
			dp[0][j][k]=1ll*(sum1[j]+sum0[k])*inv[j+k]%P;
			dp[1][j][k]=1ll*(sum1[j]+sum0[k]+j)*inv[j+k]%P;
			(sum1[j]+=dp[1][j][k])%=P;
			(sum0[k]+=dp[0][j][k])%=P;
		}
	L ans=dp[0][x][y];
	for(L i=1;i<=n;i++) ans=1ll*ans*i%P;
	cout<<ans<<endl;
    return 0;
}


---

## 作者：lzqy_ (赞：5)

$O(n)$ 线性做法。

dp 总是需要刻画 $x$ 两侧数的状态，这至少需要 $O(n^2)$ 的时间。考虑从计算 `HILO` 贡献的角度入手。

考虑**数对（而非位置）** $(j,k)$ 的贡献$\,(j >x,k \le x)$，设在 $j$ 之前存在的 $\le x$ 的最大数为 $i$（显然 $i$ 要小于 $k$），则其他数的放置情况大致如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p3zalycv.png)

注意到其他数的放置是与 $k$ 无关的，因此我们直接枚举 $i,j$，贡献就是 $A(n,n-j+\max(i-1,0))\times (x-i)\times (j-i-2)!$ 。

第一项是扣掉 $[1,i)\cup(j,n]$ 的方案，第二项是枚举 $k$ 的方案，第三项是在 $k$ 后方任意放 $(i,j)/\{k\}$ 的方案。

先把 $i=0$ 的情况特殊处理掉去除 $\max$，那么原式变为

$$\sum\limits_{1\le i <x}\sum\limits_{x<j \le n}(x-i)\frac{n!}{(j-i+1)!}(i-j-2)!$$

整理得

$$\sum\limits_{1\le i <x}(x-i)\sum\limits_{x<j \le n}n!\frac{1}{(j-i+1)(j-i)(j-i-1)}$$

设 $g=j-i:$

$$\sum\limits_{g}n!\frac{1}{(g+1)g(g-1)}\sum\limits_{i}x-i$$

容易发现后一个 $\sum$ 中 $(x-i)$ 的取值是连续的，可以直接算出来。

于是整个式子便可以线性求了。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int mod=1e9+7;
const int maxn=1000010;
il int fpow(int n,int m,int x=1){
    for(;m;m>>=1,n=1ll*n*n%mod)
        if(m&1) x=1ll*x*n%mod;
    return x;
}
int n,x;
int fac[maxn],ifac[maxn];
il int C(int n,int m){return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;}
il int A(int n,int m){return 1ll*fac[n]*ifac[n-m]%mod;}
int S(int l,int r){
    return 1ll*(r-l+1)*(l+r)/2%mod;
}
int main(){
    scanf("%d%d",&n,&x);
    fac[0]=ifac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    for(int i=1;i<=n;i++) ifac[i]=fpow(fac[i],mod-2);
    int ans=0;
    for(int j=x+1;j<=n;j++)
        ans=(ans+1ll*x*fac[j-2]%mod*A(n,n-j))%mod;
    for(int g=2,tmp,l,r;g<n;g++){
        tmp=fpow(1ll*(g-1)*g%mod*(g+1)%mod,mod-2);
        r=x-max(x-g+1,1),l=x-min(n-g,x-1);
        tmp=1ll*tmp*fac[n]%mod*S(l,r)%mod;
        (ans+=tmp)%=mod;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：PengAo (赞：4)

听说同学用容斥写这题卡了几天，我试着从 DP 的角度想很快就过了。看到题解区没人与我的思路相同，于是前来写一篇题解。

***

[题目传送门](https://www.luogu.com.cn/problem/P7986)

既然是从 DP 的角度考虑，我们先想一想如何设计状态。题目要求 DP 一个排列，一个自然的想法是状压，但在本题的数据范围下显然无法通过。观察到题目只不关心排列中各个数具体的值，而只关心排列中各数的大小关系，故我们可以不在 DP 状态中记录数值而是记录排名。

> 如果您不是很明白“记录当前数在已考虑数中的排名”的实现，或者是第一次见到这个 Trick，可以先写一写 [AT_dp_t Permutation](https://www.luogu.com.cn/problem/AT_dp_t) 和 [P2467 [SDOI2010] 地精部落](https://www.luogu.com.cn/problem/P2467) 两道题。

总之，我们可以设计状态：当前考虑到排列的某一个前缀，其中有 $i$ 个数小于 $x+0.5$，$j$ 个数大于 $x+0.5$，Bessie 上一次回答的是 `LO`/`HI` 的方案数和所有方案中说出过的子串 `HILO` 总数，分别记为 $c_{i,j,0/1}$ 和 $d_{i,j,0/1}$。接下来考虑如何转移（即往排列中插入新的数）：

1. 上一个回答是 `LO`，这次插入的数小于 $x+0.5$：
$$ \begin{aligned} d_{i+1,j,0} &\leftarrow d_{i+1,j,0} + (i+1) d_{i,j,0} \\ c_{i+1,j,0} &\leftarrow c_{i+1,j,0} + (i+1) c_{i,j,0} \end{aligned} $$
2. 上一个回答是 `LO`，这次插入的数大于 $x+0.5$，但是被 Elsie 跳过：
$$ \begin{aligned} d_{i,j+1,0} &\leftarrow d_{i,j+1,0} + j \cdot d_{i,j+1,0} \\ c_{i,j+1,0} &\leftarrow c_{i,j+1,0} + j \cdot c_{i,j+1,0} \end{aligned} $$
3. 上一个回答是 `LO`，这次插入的数大于 $x+0.5$，没有被 Elsie 跳过：
$$ \begin{aligned} d_{i,j+1,1} &\leftarrow d_{i,j+1,1} + d_{i,j,0} \\ c_{i,j+1,1} &\leftarrow c_{i,j+1,1} + c_{i,j,0} \end{aligned} $$
4. 上一个回答是 `HI`，这次插入的数大于 $x+0.5$：
$$ \begin{aligned} d_{i,j+1,1} &\leftarrow d_{i,j+1,1} + (j+1) d_{i,j,1} \\ c_{i,j+1,1} &\leftarrow c_{i,j+1,1} + (j+1) c_{i,j,1} \end{aligned} $$
5. 上一个回答是 `HI`，这次插入的数小于 $x+0.5$，但是被 Elsie 跳过：
$$ \begin{aligned} d_{i+1,j,0} &\leftarrow d_{i+1,j,0} + i \cdot d_{i,j,1} \\ c_{i+1,j,0} &\leftarrow c_{i+1,j,0} + i \cdot c_{i,j,1} \end{aligned} $$
6. 上一个回答是 `HI`，这次插入的数小于 $x+0.5$，没有被 Elsie 跳过：
$$ \begin{aligned} d_{i+1,j,0} &\leftarrow d_{i+1,j,0} + d_{i,j,1} + {\color{ff0000}c_{i,j,1}} \\ c_{i+1,j,0} & \leftarrow c_{i+1,j,0} + c_{i,j,1} \end{aligned} $$

> 标红的部分计算了 `HILO` 的出现次数，一定要记得加上。

至于初始值，只需将 $c_{1,0,0}$ 和 $c_{0,1,1}$ 置为 $1$，剩下的全零即可。最终的答案就是 $d_{x,n-x,0} + d_{x,n-x,1}$。然后我们就可以愉快地开始 DP 辣。同时别忘了滚动数组，否则会爆空间。[提交记录](https://www.luogu.com.cn/record/188835929)

---

## 作者：快乐的大童 (赞：3)

## P7986 [USACO21DEC] HILO P
一种纯推式子的方法，不需要期望和 dp。

下面记原题的 $x$ 为 $k$，原排列为 $p$。

修改了一些排版问题（）
### $O(n^5)$ solution
考虑计算每一对 `HILO` 对答案造成的贡献，发现一对 `HILO` 必定能由排列中的一对有序对 $(x,y)$ 表示，其中 $x>k,y\le k$。

于是直接枚举 $x,y$ 以及它们在排列中所在的位置 $i,j$，如果要让 $(x,y)$ 产生贡献，必须要满足：

- 对于所有 $1\le l<j,p_l >x$ 或者 $p_l<y$，记作条件 1。

这样才会使 $x,y$ 不被跳过。

但这是不够的。考虑排列 `1 5 2 3 4 6`，在 $k=3$ 的情况下，虽然 $(5,3)$ 满足上述条件，但是并不会造成贡献。为了保证 $(x,y)$ 能顺利配对造成贡献，我们还需要让 $[i+1,j-1]$ 中每一个 $<k$ 的数都被跳过，即让它们小于 $[1,i)$ 中的最大的 $<k$ 的数。设这个数为 $z$。

按照 $z$ 的有无分类讨论：

- 若存在，对于每一个 $x,y,i,j,z$，答案即为 $A_{n-x+z-1}^{j-3}\times (n-j)!\times (i-1)$，表示在能选的所有数（即 $[x+1,n],[1,z-1]$ 之间的所有数）之中选出一些数放在前 $j-3$ 个位置上（前 $j$ 个位置去掉已经钦定好了的 $x,y,z$）并随意排列，$j$ 之后的数任意排列，$z$ 可以放置在 $[1,i-1]$ 的任意位置的方案数，其中 $A$ 是排列数。
- 若不存在，对于每一个 $x,y,i,j$，答案即为 $A_{n-x}^{j-2}\times(n-j)!$，意义和存在的情况类似。

枚举 $x,y,z,i,j$ 对上述答案求和即可，注意要让 $z$ 满足条件 1，即 $z<y$。

通过第一个子任务。

```cpp
void On5sol(){
	rep(i,2,n)rep(j,i+1,n)rep(x,k+1,n)rep(y,1,k)rep(z,1,y-1){
		ans=(ans+A(n-x+z-1,j-3)*fac[n-j]%mod*(i-1)%mod)%mod;
	}
	rep(i,1,n)rep(j,i+1,n)rep(x,k+1,n)rep(y,1,k){
		ans=(ans+A(n-x,j-2)*fac[n-j]%mod)%mod;
	}
}
```
### $O(n^4)$ solution
优化上述式子，发现答案式子与 $y$ 无关，所以我们不再枚举 $y$，改为直接枚举 $z$，计算能对当前枚举的 $z$ 造成贡献的 $y$ 的数量。显然是 $k-z$，即 $[z+1,k]$ 之间的所有 $y$。将原式乘以 $k-z$。

注意在不存在 $z$ 的情况中，通过观察式子，发现每一个 $y$ 都能对答案造成贡献，直接原式乘以 $k$。

通过第一个子任务。

```cpp
void On4sol(){
	rep(i,2,n)rep(j,i+1,n)rep(x,k+1,n)rep(z,1,k){
		ans=(ans+A(n-x+z-1,j-3)*fac[n-j]%mod*(i-1)%mod*(k-z)%mod)%mod;
	}
	rep(i,1,n)rep(j,i+1,n)rep(x,k+1,n){
		ans=(ans+A(n-x,j-2)*fac[n-j]%mod*k%mod)%mod;
	}
}
```
### $O(n^3)$ solution
继续优化上述式子，以存在 $z$ 的情况的答案式子为例，发现答案式子 $\sum_{i=1}^n\sum_{j=i+1}^n\sum_{x=k+1}^n\sum_{z=1}^kA_{n-x+z-1}^{j-3}\times (n-j)!\times(i-1)$ 中， $(n-j)!,(i-1)$ 均与 $x,y$ 无关，将它们提出来，将答案式子化为 $\sum_{i=1}^n(i-1)\sum_{j=i+1}^n(n-j)\sum_{x=k+1}^n\sum_{z=1}^kA_{n-x+z-1}^{j-3}$，预处理每个 $j$ 对应的 $\sum_{x=k+1}^n\sum_{z=1}^kA_{n-x+z-1}^{j-3}$ 的值即可，记作 $dp_j$。统计答案时只需要枚举 $i,j$，将后面一大串式子代入成 $dp_j$ 即可。

不存在 $z$ 的情况同理，把这一部分优化成 $O(n^2)$。

预处理是 $O(n^3)$ 的，统计是 $O(n^2)$。

~~虽然名字是 dp 但这个做法真的与 dp 无关~~

通过第一，二个子任务。

```cpp
void On3sol(){
	rep(j,3,n)rep(x,k+1,n)rep(z,1,k)dp[j]=(dp[j]+A(n-x+z-1,j-3)*fac[n-j]%mod*(k-z)%mod)%mod;
	rep(i,2,n)rep(j,i+1,n)ans=(ans+(i-1)*dp[j]%mod)%mod;
	rep(j,2,n)rep(x,k+1,n)dp2[j]=(dp2[j]+A(n-x,j-2)*fac[n-j]%mod*k%mod)%mod;
	rep(i,1,n)rep(j,i+1,n)ans=(ans+dp2[j])%mod;
}
```
### $O(n^2)$ solution
仍然继续优化上述式子，发现计算的瓶颈是预处理，拎出预处理式子 $dp_j=\sum_{x=k+1}^n\sum_{z=1}^kA_{n-x+z-1}^{j-3}$，发现 $\sum_{z=1}^kA_{n-x+z-1}^{j-3}$ 中 $j-3$ 固定，$n-x+z-1$ 是一段区间，前缀和优化掉即可。

通过第一、二、三个子任务。

```cpp
void On2sol(){
	rep(j,3,n){
		int sum=0;s[0]=A(0,j-3);//注意A(0,j-3)也是可能有取值的
		rep(i,1,n)s[i]=(s[i-1]+A(i,j-3))%mod;
		rep(z,1,k)sum=(sum+(s[n-k+z-2]-(z==1?0:s[z-2])+mod)%mod*(k-z)%mod)%mod;
		dp[j]=sum*fac[n-j]%mod;
	}
	rep(i,2,n)rep(j,i+1,n)ans=(ans+(i-1)*dp[j]%mod)%mod;
	rep(j,2,n)rep(x,k+1,n)dp2[j]=(dp2[j]+A(n-x,j-2)*fac[n-j]%mod*k%mod)%mod;
	rep(i,1,n)rep(j,i+1,n)ans=(ans+dp2[j])%mod;
}
```



---

## 作者：serene_analysis (赞：3)

先考虑暴力 DP。设 $tot_{i,j,k,0/1}$ 表示已经放完了 $i$ 个数，猜过的不大于 $x$ 的最大数为 $j$，大于 $x$ 的最大数为 $k$，上一次是 HI 还是 LO 的方案数，同理记 $sum_{i,j,k,0/1}$ 表示 HILO 出现的次数总和，转移枚举填 $[j+1,x],[x+1,k],[1,j-1] \cup [k+1,n]$ 三个区间中的哪一个即可做到 $\mathcal{O}(n^4)$，使用前缀和可以做到 $\mathcal{O}(n^3)$。

上面那个 DP 状态是 $\mathcal{O}(n^3)$ 的，感觉没啥前途。计数题的另一个常用方法是贡献法，可以考虑一下。但是直接考虑满足 $i \leq x,j \gt x$ 的 $(i,j)$ 对答案的贡献也不是很好做，因为有可能在 $j,i$ 之间会出现一个小于 $i$ 的数提前 LO，那不妨直接考虑 $j \gt x$ 的 $j$ 的贡献。一个想法是枚举在 $j$ 之前出现的小于等于 $x$ 的最小数 $i$，那么现在 $[1,i-1]$ 和 $[j+1,n]$ 之内的数就不会产生任何影响，用一个排列数算一下系数之后，问题变成求满足 $i$ 在 $j$ 前且 $j$ 之后第一个数在 $[i+1,x]$ 之间的排列数，这个系数就是 $(x-i) \times (j-i-2)!$，而这个计算是可以 $\mathcal{O}(1)$ 完成的，于是问题在 $\mathcal{O}(n^2)$ 时间内得到解决。注意要特殊处理不存在小于等于 $x$ 的数出现在 $j$ 之前的情况。

实际上把式子写出来化简是可以做到 $\mathcal{O}(n)$ 的，不过这个并不重要。

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
const int maxn=5e3+5;
const int mod=1e9+7;
int inv[maxn],fact[maxn],finv[maxn];
void init(){
	inv[0]=inv[1]=fact[0]=fact[1]=finv[0]=finv[1]=1;
	for(int i=2;i<=maxn-2;i++){
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		fact[i]=1ll*fact[i-1]*i%mod;
		finv[i]=1ll*finv[i-1]*inv[i]%mod;
	}
	return;
}
int biga(int n,int k){return 1ll*fact[n]*finv[n-k]%mod;}
int n,x;
signed main(){
	init();
	scanf("%d%d",&n,&x);
	int ans=0;
	for(int j=x+1;j<=n;j++)for(int i=0;i<=x-1;i++){
		int ba=n-j,fr=std::max(0,i-1),p=x-i,q=j-x-1;
		(ans+=1ll*biga(n,ba+fr)*fact[p+q-1]%mod*p%mod)%=mod;
	}
	printf("%d",ans);
	return 0;
}
//namespace burningContract
```

感谢你的阅读。

---

## 作者：steambird (赞：2)

这里补充一些官方题解中不容易理解的细节，~~以照顾我这种 DP 彩笔~~。

## 思路

### Step 1. 确定思维方向

将 Elsie 的询问分为两类：Bessie 会回答 `HI` 的和会回答 `LO` 的，个数分别为 $n-x$ 个与 $x$ 个。设 $dp_{latest,j,k}$ 表示上一个选择了 $latest$（用 $0$ 表示 `LO` 或连什么都无法产生贡献的东西，$1$ 表示 `HI`），当前选择时能选择 $j$ 个 `LO`，$k$ 个 `HI` 时，产生 `HILO` 个数的期望对 $10^9 + 7$ 分数取模的结果（即平均每个 Elsie 的询问序列能产生多少个 `HILO`）。

为什么用期望？因为选择一个数后将会产生很多会被跳过的数，对它们分类讨论可做，但是细节较多，很难不重不漏。通过下面的推式子可以发现，本题用期望的实现十分优雅（~~当然前提是能理解~~）。

### Step 2. 推式子

我们**倒推**，考虑当前选择的值从下一次选择的值转移过来。显然，当前我们有 $j+k$ 种选法（一次可以选一个较大或较小的数询问，使得后面某些数可以跳过，可以视作一次选择了多个连续的 `HI` 或 `LO`）。则可以列出：

- 对于 $latest = 0$，当前选什么都不会产生贡献，贡献全部来源于后面的选择（注意，期望运算时已经隐含概率，所以下面的两个求和式不需要再乘系数），即：

   $$ dp_{0,j,k} = {1 \over {j+k}} \times (\sum_{x=0}^{j-1} dp_{0, x, k} + \sum_{x=0}^{k-1} dp_{1, j, x}) $$
  
- 对于 $latest = 1$，当前选 `LO` 时能产生贡献，其它贡献来源于后面的选择，即：

   $$ dp_{1,j,k} = {j \over {j+k}} + {1 \over {j+k}} \times (\sum_{x=0}^{j-1} dp_{0, x, k} + \sum_{x=0}^{k-1} dp_{1, j, x}) $$

- 边界条件 $dp_{0,0,0} = dp_{1,0,0} = 0$。显然，什么都不能选时无法产生答案。

对于最终所求的期望 $ans$，我们要求第一个选 `HI` 或 `LO` 都不能产生贡献，也就是 $latest=0$ 的情况。因此，$ans = dp_{latest,x,n-x}$。

注意，最终我们求的是对所有序列的总数，因此最终答案是 $ans \times n!$。

### Step 3. 实现

直接计算上面的式子，时间复杂度 $O(n^3)$。注意到上面的求和式可以用前缀和优化，开前缀和数组即可，时间复杂度优化到 $O(n^2)$，可以通过本题。**注意：如果直接在 DP 数组中存前缀和值（而不是真实值），则要注意循环顺序和取最终答案的实现等细节。**

同时注意本题需要预处理一些乘法逆元，否则复杂度将变为 $O(n^2 \log V)$，其中 $V = 10^9 + 7$，$\log V \approx 30$，将会超时。

## 代码

没写线性求逆元，不过 $O(n \log V)$ 预处理足够通过本题了。

```c++
#include <bits/stdc++.h>
using namespace std;

inline void train() {
	   ios::sync_with_stdio(false);
	   cin.tie(0);
	   cout.tie(0);
}

inline int maxi(int a, int b) {
	return a > b ? a : b;
}

inline int mini(int a, int b) {
	return a < b ? a : b;
}

constexpr int N = 5003;
constexpr long long MODER = 1e9+7;
int dp[N][N][2], su0[N], su1[N], n, x, inv[N];

long long fastpow(long long a, long long b) {
	if (b <= 0) return 1ll;
	else if (b&1) return a * fastpow(a, b-1) % MODER;
	else {
		long long v = fastpow(a, b>>1);
		return v * v % MODER;
	}
}

int main() {

	train();
	
	cin>>n>>x;
	long long v = 1ll;
	for (int i = 1; i <= n; i++) v = (v * i) % MODER; 
	for (int i = 1; i <= n; i++) inv[i] = fastpow(i, MODER-2);
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= n-x; j++) {
			dp[i][j][0] = su0[j];
			dp[i][j][1] = su1[i];
			long long bs = inv[i+j];//fastpow(i+j, MODER-2);
			dp[i][j][0] = ((1ll * dp[i][j][0] + 1ll * dp[i][j][1]) % MODER) * bs % MODER;
			dp[i][j][1] = (dp[i][j][0] + (1ll * i * bs % MODER)) % MODER;
			su0[j] = (1ll * su0[j] + dp[i][j][0]) % MODER;
			su1[i] = (1ll * su1[i] + dp[i][j][1]) % MODER; 
		}
	}
	cout<<(1ll * dp[x][n-x][0] * v % MODER)<<endl;
	
	//cout<<flush;

	return 0;
}

```

---

