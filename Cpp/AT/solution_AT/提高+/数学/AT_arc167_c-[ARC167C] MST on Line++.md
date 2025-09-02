# [ARC167C] MST on Line++

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc167/tasks/arc167_c

正整数 $ N,K $ と長さ $ N $ の正整数列 $ A=(A_{1},A_{2},\dots,A_{N}) $ が与えられます。

$ (1,2,\dots\ ,N) $ の順列 $ P=(P_{1},P_{2},\dots\ ,P_{N}) $ に対して以下の「問題 MST on Line」について考え、その答えを $ f(P) $ と書きます。

> **問題 MST on Line**
> 
> 頂点に $ 1 $ から $ N $ までの番号がついた頂点数 $ N $ の重み付き無向グラフ $ G $ があります。$ G $ について $ 1\leq\ i\lt\ j\leq\ N $ を満たす任意の整数の組 $ (i,j) $ に対して以下が成り立ちます。
> 
> - $ j-i\leq\ K $ ならば頂点 $ i $ と頂点 $ j $ の間に辺が存在して、その辺の重みは **$ \max(A_{P_{i}},A_{P_{j}}) $**
> - $ j-i\gt\ K $ ならば頂点 $ i $ と頂点 $ j $ の間に辺は存在しない
>  
> $ G $ の最小全域木の辺の重みの和を求めてください。

全ての $ (1,2,\dots\ ,N) $ の順列 $ P=(P_{1},P_{2},\dots\ ,P_{N}) $ に対する $ f(P) $ の総和を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\leq\ K\lt\ N\leq\ 5000 $
- $ 1\leq\ A_{i}\leq\ 10^{9} $
- 入力は全て整数
 
### Sample Explanation 1

$ P=(1,2,3,4,5) $ としたとき、 頂点 $ 1 $ と $ 2 $ の間に存在する、重み $ 4 $ の辺、 頂点 $ 2 $ と $ 3 $ の間に存在する、重み $ 5 $ の辺、 頂点 $ 2 $ と $ 4 $ の間に存在する、重み $ 4 $ の辺、 頂点 $ 4 $ と $ 5 $ の間に存在する、重み $ 2 $ の辺、 という $ 4 $ つの辺は $ G $ の全域木となり、辺の重みの和は $ 15 $ です。 これ以上辺の重みの和を少なくするように全域木をとることはできないので、$ f(P)=15 $ となります。 以上のように全ての $ (1,2,3,4,5) $ の順列 $ P $ に対する $ f(P) $ の総和を求めると $ 1740 $ になるので、これを出力します。

## 样例 #1

### 输入

```
5 2
3 4 5 2 1```

### 输出

```
1740```

## 样例 #2

### 输入

```
2 1
167 924```

### 输出

```
1848```

## 样例 #3

### 输入

```
12 9
22847 98332 854 68844 81080 46058 40949 62493 76561 52907 88628 99740```

### 输出

```
660459584```

# 题解

## 作者：min_inf (赞：11)

感觉题解都有点抽象了。

题意显然可以转换为将 $a$ 随意排列得到的答案之和。

考虑单个排列 Kruskal 做是怎么样的，从小到大考虑每个数，假设这个数位置是 $i$，那把 $[i-k,i+k]$ 内比 $a_i$ 小的数所在的连通块全部用边合并起来，这个数的贡献就是连通块个数。

容易发现一侧最多只有一个连通块（因为距离都是小于 $k$ 的），所以贡献最多为 $2$。讨论一下（约定 $a_i$ 是第 $r_i$ 小的数，当前讨论的数位置是 $i$）：

- $0$ 个连通块。那就是拿 $n-r_i$ 个数填这个区间（设长度为 $len$），方案数是 $P_{n-r_i}^{len-1} \times (n-len)!$。

- $1$ 个连通块。用 $(n-1)!$ 减去 $0$ 个和 $2$ 个连通块的方案数。

- $2$ 个连通块。可以发现此时存在恰好一对 $x,y$ 满足：

  - $i-k \le x<i<y \le i+k$。
  - $y-x>k$。
  - $\max(r_x,r_y)<r_i$。
  - $\forall x<j<y,r_j \ge r_i$。

假如枚举 $x,i,y$ 那方案数就是 $P_{n-r_i}^{y-x-2} \times P_{r_i-1}^2 \times (n-(y-x+1))!$，不过这样是 $O(n^4)$ 的。容易发现式子只和 $y-x$ 有关，所以只需要枚举 $y-x$ 简单算一下被统计的次数即可。复杂度是枚举 $r_i$ 的复杂度乘上枚举 $i$ 或 $y-x$ 的复杂度，即 $O(n^2)$。

```cpp
void main(){
    cin>>n>>m;
    init(n);
    rep(i,1,n)cin>>a[i];
    sort(a+1,a+n+1);
    rep(i,2,n){
        rep(j,1,n){
            int l=max(1,j-m),r=min(n,j+m);
            ans+=a[i]*(fac[n-1]-P(n-i,r-l)*fac[n-(r-l+1)]);
        }
        rep(j,m+1,n-1){
            ans+=a[i]*P(n-i,j-2)*P(i-1,2)*fac[n-j-1]*max(0,m-(j-m)+1)*(n-j);
        }
    }
    cout<<ans<<'\n';
}
```

---

## 作者：良心WA题人 (赞：11)

## 前言

发现好像很多人的做法比较 hard，这里提供一种几乎不用脑子的做法。

## 思路

对于每个生成树是难以计算的，考虑计算当前的 $a_i$ 会成为多少个边权。

**$a_i$ 按 $p$ 重新排列后**，$i$ 需要在前面选择一个父亲，则选择父亲的这条边的权值为 $a_i$ 当且仅当前面的 $k$ 个 $a$ 中存在一个 $a_j$ 使得 $a_j\le a_j$，其余的随便排。

而 $i$ 向儿子的全部连边中，边权为 $a_i$ 当且仅当儿子 $j$ 前面的 $k$ 个 $a$ 均比 $a_j$ 大且 $a_i$ 为最小的一个。则我们选出 $k$ 个比 $a_i$ 大的数进行排列并钦定这个排列右边的第一个数比 $a_i$ 小即可。

然后就做完了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=5004,P=998244353;
int fac[NN],ifac[NN],a[NN];
int qmi(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=1ll*res*a%P;
		a=1ll*a*a%P;
		b>>=1;
	}
	return res;
}
int C(int a,int b)
{
	if(a<b||b<0)
		return 0;
	return 1ll*fac[a]*ifac[b]%P*ifac[a-b]%P;
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=1ll*fac[i-1]*i%P;
	ifac[n]=qmi(fac[n],P-2);
	for(int i=n-1;~i;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%P;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<k;j++)
			ans=(ans+1ll*a[i]*(C(n-1,j)-C(n-i,j)+P)%P*fac[j]%P*fac[n-j-1]%P)%P;
		ans=(ans+1ll*a[i]*(n-k)%P*(C(n-1,k)-C(n-i,k)+P)%P*fac[k]%P*fac[n-k-1]%P)%P;
		for(int j=1;j<k;j++)
			ans=(ans+1ll*a[i]*C(n-i,j-1)%P*fac[j]%P*fac[n-j-1]%P*(i-1)%P)%P;
		ans=(ans+1ll*a[i]*(n-k)%P*C(n-i,k-1)%P*fac[k]%P*fac[n-k-1]%P*(i-1)%P)%P;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：樱雪喵 (赞：11)

完全不会做，人菜，没救了。

## Description

给定正整数 $n,K$ 和一个长度为 $n$ 的序列 $A$。对于一个 $1\sim n$ 的排列 $P$，我们定义 $f(P)$ 为以下问题的答案：

> 给一个 $n$ 个点的无向带权图，对于两点 $i<j$，当且仅当 $j-i\le K$ 时，它们之间有边，边权为 $\max(A_{P_i},A_{P_j})$。  
求这个图的最小生成树边权和。

对于所有可能的排列 $P$，求出它们的 $f(P)$ 之和，答案对 $998\,244\,353$ 取模。

$1\le K< N\le 5000$，$1\le A_i \le 10^9$。

## Solution

发现我们只要求出每条边被选了几次，就可以统计出它们的权值和。

考虑 Kruskal 求最小生成树的过程，发现按边权排序后，我们会选择哪些边只与边之间的大小关系有关，与具体的边权无关。那么我们把 $A_i$ 升序排序后，令第 $i$ 类边表示边权为 $A_i$ 的边，就可以只关心每类边分别选了几次。

考虑如下的子问题：

> 给定一个边权的限制 $a$ 和一个排列 $P$，对于 $i<j$，$i,j$ 之间有无权边当且仅当 $j-i\le K$ 且 $\max(P_i,P_j)\le a$。求在边之间不形成环的条件下最多选择几条边。

对于一个排列 $P$，边权为 $A_i$ 的边被选择的条数就是 $a=i$ 时的答案减掉 $a=i-1$ 时的答案。

设 $f_{i}$ 表示所有排列 $P$ 在 $a=i$ 时该子问题的答案之和。那么有：

$$
ans=\sum_{i=2}^{n} A_i(f_i-f_{i-1})
$$

考虑 $f_i$ 怎么求。

对于一个排列 $P$，我们令所有 $P_j\le i$ 的下标 $j$ 构成集合 $Q$，$Q$ 中的元素升序排序。因为边权是取 $\max$，不在 $Q$ 内的点一定没有任何连边。  
故所有 $Q_j-Q_{j-1}\le K$ 的下标之间都有连边，且把它们都选上一定是不劣的。对于一个排列 $P$ 的答案就是 $\sum\limits_{j=2}^i [Q_j-Q_{j-1}\le K]$。

枚举一个 $j$，对于所有排列计算满足 $Q_j-Q_{j-1}\le K$ 的数量。$Q_j-Q_{j-1}=k$ 的排列有 $\binom{n-k}{i-1}$ 个，$\le K$ 的就有 $\sum\limits_{j=1}^K \binom{n-j}{i-1}$ 个。那么一共有 $i-1$ 对相邻的下标，一个 $Q$ 序列对答案的贡献是 $(i-1)\sum\limits_{j=1}^K\binom{n-j}{i-1}$。

一个 $Q$ 序列对应的排列 $P$ 的个数是 $i!(n-i)!$，最终的式子是

$$
f_i=i!(n-i)!(i-1)\sum_{j=1}^K \binom{n-j}{i-1}

$$

求 $f_i$ 的时间复杂度为 $O(nK)$，求答案的时间复杂度为 $O(n)$。

```cpp
#define int long long
const int N=5005,mod=998244353;
int n,K,a[N];
int f[N],jc[N],c[N][N];
il void init(int mx)
{
    for(int i=0;i<=mx;i++)
        for(int j=0;j<=i;j++) c[i][j]=j?(c[i-1][j-1]+c[i-1][j])%mod:1;
}
signed main()
{
    n=read(),K=read(); init(n);
    for(int i=1;i<=n;i++) a[i]=read(); sort(a+1,a+n+1);
    jc[0]=1;
    for(int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=K;j++) f[i]=(f[i]+jc[i]*jc[n-i]%mod*(i-1)%mod*c[n-j][i-1]%mod)%mod;
    // for(int i=1;i<=n;i++) cout<<"f "<<i<<" "<<f[i]<<endl;
    int ans=0;
    for(int i=1;i<=n;i++) ans=(ans+a[i]*(f[i]+mod-f[i-1])%mod)%mod;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：7)

真不会数数。

先拆贡献，枚举 $a_i$，考虑边权为 $a_i$ 的边在 MST 中总共出现了几次（下文简称出现了几次）。

回忆 Kruskal 算法如何求解 MST：按边权从小到大考虑是否加入每一条边，一条边在 MST 中等价于加入此边后仍不存在环。

一个巧妙且关键的思考角度：对于排列 $p$ 生成的图，边权为 $w$ 的边的出现次数等于加入权为 $w$ 的边之前的连通块个数和加入之后的作差。  
这个角度有点像：**一次操作的影响相当于操作之前和之后的差异**。

如果将 $a$ 升序排列，设 $f_i$ 表示对于所有排列，只考虑边权 $\le a_i$ 的边时，能同时选出的边的最大数量（即连通块个数 $-1$）。  
答案就是 $\sum\limits_{i=2}^n a_i (f_i - f_{i-1})$。

只需快速求解 $f$。不妨设要求解 $f_m$。

由于 $a$ 已被升序排列，在排列中所有 $>m$ 的元素都不用考虑了，直接变为 $(n-m)!$ 的系数。

把排列 $p$ 中 $\le m$ 的元素的下标拎出来，按升序记为序列 $q$。  
那么 $q$ 中两元素之差 $\le k$ 等价于有连边，需要选出尽可能多的边且不构成环。

另一个关键：**用贪心思想**处理**最大化的限制**。

贪心地，选取的边一定是 $q$ 中两相邻元素构成的，否则一定不优。  
而且，如果两相邻元素构成的边存在一定会选上。  
可以证明这是最优策略。

那直接算次数：考虑 $(q_i,q_{i+1})$ 这条边什么时候被选。  
只需让 $q_{i+1}-q_i \le k$。  
将 $[q_i,q_{i+1}]$ 的数捆成一个数，枚举其长度 $d \le k+1$，相当于 $m-1$ 个数在 $n-(d-1)$ 个值域上的洞中随便选，即 $\sum\limits_{d=2}^{k+1} \binom{n-(d-1)}{m-1} = \sum \limits_{d=1}^k\binom{n-d}{m-1}$。

有 $m-1$ 个 $(q_i,q_{i+1})$。  
$q$ 序列下标映射到 $p$ 序列的元素值上还有 $m!$。

所以 $f_m=(m-1)m!(n-m)!\sum\limits_{d=1}^k\binom{n-d}{m-1}$。

直接计算即可，复杂度 $\mathcal{O(nk)}$。

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/arc167/submissions/47072438)。

---

## 作者：CrTsIr400 (赞：2)

来回顾原问题：

>给你一个长度为 $n$ 的序列 $A$，在这个序列的一个排列上面建立最小生成树，一条边存在仅当坐标差异 $\le k$，边权为 $\max(A_{p_i},A_{p_j})$。
>
>求对于所有排列的最小生成树边权和 $\bmod\ 998244353$。

一个个击破条件，容易想到组合意义上的突破。

----

最先要击破的约束条件是边权，若对于某条边可行，那么我们只需要**可行生成树**即可，这样就能大幅度简化计算过程。

排列计数的基本套路：观察到 $A$ 值无关紧要，可以直接排序。

于是，我们就转化为了下标的问题：边权就变成了 $A[\max(p_i,p_j)]$。

此时难度还是相当大，于是考虑进一步拆贡献，也就是组合计数的基本套路：间接计数。

换而言之，对于边权等于它的所有边，进行计数。

即换而言之，设 $g[a]$ 为所有排列中边权**恰好为** $A[a]$ 的**所有在最小生成树上的**边的数量。那么答案就= $\sum_{i=1}^n a_i g[i]$。

于是我们就击碎了边权的壁垒，变成了可行性计数问题。

---

接着，我们需要把**在最小生成树上**和**恰好**两个条件，一石二鸟，直接击落。

考虑继续**间接计数**，设 $f[a]$ 为所有排列中，边权**不大于** $A[a]$ 且生成最小生成树的所有边的数量。

那么 $g[a]=f[a]-f[a-1]$。

至此，我们把第二个重要约束也给击破了。

边权由点权决定，所以能够生成最小生成树的点集（设之为 $Q$）中点编号一定 $\le a$。

观察只有这个点集里面有边。

此时，第三个约束条件，最小生成树的约束条件，也被我们击破了。

---

最后还剩第四个约束条件：坐标差不超过 $k$。

回顾一下问题，我们已经是要对于某个排列 $P$，求出它的 $h(P)$，此时其**值** $\le a$ 的所有点，**坐标差** $\le k$ 的时候才能连边，求最多的**不能连成环的**边数。我们需要对于 $n$ 的全排列求出 $\sum h(P)$。

此时这个条件已经相当简化了，不是那么棘手了。

设可选点集 $Q$，点的坐标为序列 $B$。

因为这是全排列，可以随便排序。所以把序列 $B$ 排序，如果相邻两个坐标差小于等于 $k$，那么就能连边；否则不能连边。

于是我们就把连边最大化了。至此，我们成功地对于单个序列的 $h(P)$ 求解了出来。

---

接着到了组合计数环节。对于更多的 $h(P)$，我们需要抽象一种操作，可以让它组合计数。

考虑构造所有 $B$ 序列，因为要求值 $\le a$（再次注意，值和坐标的区别），此时我们就有 $a!(n-a)!$ 种可能的 $B$ 序列。

此时 $B$ 序列还有一些贡献，这个时候就需要计算 $\sum_{i=2}^a [B_i-B_{i-1}\le k]$。

---

最后，到了序列计数环节。此时我们的贡献已经拆开，只需要对于所有长度为 $a$ 的排列 $B$，求出 $\sum_{i=2}^a [B_i-B_{i-1}\le k]$ 的值之和。

考虑继续间接求解答案，枚举一个 $i$，对于所有排列统计 $B_i-B_{i-1}\le k$ 的数量。

这个 $B$ 序列有什么性质呢？首先是严格递增，其次是值域在 $[1,n]$ 之间。

若是值恰好等于 $k$ 呢？考虑对于一个 $B_i$，因为已经钦定，所以挖掉前面 $k$ 个空位，差值就一定等于 $k$ 了。别的可以随便选，所以贡献就是 $\binom{n-k}{a-1}$。小于等于 $k$ 时候，因为它们的答案也是互相独立的，所以套个 $\sum$ 即可。

观察对于别的 $B$ 位置，本质的答案贡献是相互独立的，所以贡献要乘上 $(a-1)$。

于是，最终 $f[a]=a!(n-a)!(a-1)\sum_{i=1}^k \binom{n-i}{a-1}$。

这个问题就结束啦。

----

汇总一下，这个问题能让我学会什么：

+ 带边权计数，首先去边权化；
+ 把最小生成树条件变成生成树；
+ 把生成树变为非环最大边数；
+ 对于序列的差值约束，学会使用插板法；
+ 各种容斥的灵活运用和组合数的妙用。

第一次较为独立地做出 \*2400 的题目，不得不说，这些东西还是对我收益匪浅的。

---

## 作者：Jryno1 (赞：2)

## ARC167C

神秘计数，对着官方题解瞪了好一会，主要是题目太绕了。

### 题意

给定一个长度为 $n$ 的序列 $A_i$ 和数字 $k$，对于所有长度为 $n$ 的排列，考虑以下问题：

$\forall 1 \le i < j \le n$，若 $j-i\le K$ 在 $i$ 到 $j$ 之间建一条无向边，边权为 $\max(A_{P_i},A_{P_j})$。

对于这个无向图，求最小生成树的权值和。

问所有排列的答案和。

$n\le 5000$，$A_i\le 10^9$

### Sol

计算所有排列的所有答案之和，显然的想法就是单独计算每一个 $A_i$ 其在最小生成树中出现的次数。先对 $A_i$ 进行排序，这样我们就只需要考虑其相对顺序了。

设 $f(x)$ 表示，对于所有排列 $P$ 以下问题的答案：

$\forall 1 \le i < j \le n$，若 $j-i\le K$ 且 $\max(P_i,P_j)\le x$ 在 $i$ 到 $j$ 之间建一条无向边。求最多能选出来多少条边使之不能够构成任何的环。

那么对于一个 $A_i$ 其出现次数就应该是 $f(i)-f(i-1)$。这个是好理解的，这个 $f$ 的变化量就体现了“由于 $i$ 的变大，新增了多少个边可以选择”，那这个东西恰恰就是 $A_i$ 的出现次数。因此我们要求的答案就是 $\sum A_i(f(i)-f(i-1))$。

思考 $f(x)$ 如何计算。首先我们注意到对于一个排列 $P$，我们并不关心其所有大于 $x$ 的位置。因为他们一定不能够连出来边，而对于所有小于 $x$ 的位置，我们其实也只关系其下表是多少，而不是其具体的值。这时候会发现，其实我们只关心所有 $P_i\le x$ 位置的下标。

我们将这些所有的下标取出来，形成一个序列 $Q$。回到 $j-i\le K$ 的限制，贪心地思考，如果 $Q_i$ 能够向 $Q_{i+1}$ 连边，那么一定是最优的，因为 $Q$ 是一个单调递增的序列。那么问题就变成了，对于所有的 $Q$，我们需要统计其有**多少组** $Q_{i+1}-Q_{i}\le K$。再一次考虑贡献：钦定 $(j,j+1)$ 是一个满足条件的组，那么剩下的数随便选择，唯一的限制就是不能选到 $[Q_{j},Q_{j+1}]$ 之间的数字。那么枚举间隔大小 $k'$ 即可计算。之后发现这样的组一共有 $x-1$ 组，即这个长度为 $x$ 的序列任意两个相邻的位置都可以被钦定。这部分的答案就是 

$$
(x-1)\sum_{k'=1}^{K}\binom{n-k'}{x-1}
$$

可以理解成在这个值域为 $n$ 的序列中挖掉了一块数字。

统计完所有 $Q$ 的贡献，我们只需要在原来下标位置上所有的数都是 $\le x$ 的，这部分贡献是 $x!$ 剩下的 $(n-x)$ 个数字随便排列。因此得到

$$
f(x)=x!\times (n-x)!\times (x-1)\sum_{k'=1}^{K}\binom{n-k'}{x-1}
$$

此时就可以做到 $\mathcal{O}(nK)$ 计算。当然通过预处理做到 $\mathcal{O}(1)$ 计算 $f(x)$。

[ATC 提交记录](https://atcoder.jp/contests/arc167/submissions/46657763)

---

## 作者：Feyn (赞：1)

题非常简单，但是仍然突破了我愚蠢程度的上限。这个故事告诉我们打比赛就打比赛，别老想着开卡上分，不然会出大问题。

套路地对于一条权值为 $v$ 的边，思考它在所有 MST 中的出现次数，记 $n_{v}$ 表示加入所有边权不大于 $v$ 的边之后图形成的连通块数量，那么这条边的贡献显然就是 $(n_v-n_{v-1})v$，于是思考如何求这个连通块数量。

所有点显然可以分成黑点和白点，前者是权值不大于 $v$ 的点，后者是权值大于 $v$ 的点，思考哪些点之间有不大于 $v$ 的边。显然白点和其它点没有边，而忽略 $k$ 的限制后任意白点之间都是有连边的，假设黑点和白点分别有 $x,y$ 个，那么忽略 $k$ 后的答案就是 $y+1$。但是可能存在两个黑点距离太远而没有连边，显然每有相邻的距离太远的一对黑点都会导致连通块数量加一，所以只需要对这样的点对计数即可。这显然是简单的，大概就是由于每个位置的答案相同然后枚举距离计数即可。于是总的复杂度是 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
// #define feyn
#define int long long
using namespace std;
const int N=5010;
const int mod=998244353;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int p[N],q[N],inv[N];
void initC(){
    p[0]=p[1]=q[0]=q[1]=inv[0]=inv[1]=1;
    for(int i=2;i<N;i++){
        p[i]=p[i-1]*i%mod;
        inv[i]=inv[mod%i]*(mod-mod/i)%mod;
        q[i]=q[i-1]*inv[i]%mod;
    }
}
inline int ask(int s1,int s2){
    if(s1<0||s2<0||s1<s2)return 0;
    return p[s1]*q[s1-s2]%mod*q[s2]%mod;
}

int m,n,a[N];

int num[N],Data[N];

int work(int aa){
    int ans=p[m]*(m-aa+1)%mod;
    if(aa==1)return ans;
    int all=0;
    for(int i=n+1;i<m;i++){
        all+=ask(m-i,aa-1);
        all%=mod;
    }
    all=all*(aa-1)%mod*p[aa]%mod*p[m-aa]%mod;
    return (ans+all)%mod;
}

signed main(){
	
    #ifdef feyn
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif

    initC();
    read(m);read(n);
    for(int i=1;i<=m;i++)read(a[i]);
    sort(a+1,a+m+1);
    int cnt=0;num[0]=m*p[m]%mod;
    for(int l=1,r=1;l<=m;){
        r=l;
        while(a[r+1]==a[l]&&r<m)r++;
        Data[++cnt]=a[l];
        num[cnt]=work(r);l=r+1;
    }
    int ans=0;
    for(int i=1;i<=cnt;i++){
        ans+=Data[i]*(num[i-1]-num[i])%mod;
    }
    printf("%lld\n",(ans%mod+mod)%mod);

    #ifdef feyn
    printf("time %f\n",(double)clock()/CLOCKS_PER_SEC);
    #endif

    return 0;
}
```

---

## 作者：zhongpeilin (赞：1)

## 题目大意：
有一个长度为 $N$ 的序列 A，现在对于每个 $1 \sim N$ 的排列，如果 $j - i \le K$，则 $i$ 到 $j$ 有一条 $\max(a_{P_{i}}, a_{P_{j}})$ 的边，求每个排列的最小生成树边权总和。  
## 解题思路：
首先我们不难想到一个 $O(n! \times nk \log nk)$ 的做法，就是暴力去算总和，这显然是过不掉的，那么我们考虑优化。  
因为这道题是全排列，所以我们发现 $[1, 2, 3, 5, 6]$ 和 $[1, 3, 2, 6 , 5]$ 的答案是一样的，而这道题的计算边权的方法通过将 A 从小到大排序后，边权就是 $A_{\max(P_{i}, P_{j})}$，所以我们先将 A 从小到大排序。  
但是这样还是得暴力，那么我们直接考虑算每条边对答案的贡献，$A_{i}$ 的贡献为边权恰好为 $A_{i}$ 的边的出现个数 $\times A_{i}$，即可。  
问题又来了，我们发现这个恰好并不好处理，那么我们将恰好转化成小于等于，那么设 $f_{i}$ 表示边权不超过 $A_{i}$ 的边的个数。那么恰好为 $A_{i}$ 就变成了 $f_{i} - f_{i - 1}$。  
**注：建议读者先把前面的给看几遍，因为下面是本题的难点**。  
剩下就变成了，如何求出 $f_{i}$？  
我们假设现在枚举到了某个排列，而每个小于等于 $i$ 的点的位置分别在 $Q_{1} < Q_{2} < \dots < Q_{i}$，通过 Kruskal 的贪心策略，我们可以得知一定是尽可能放小的边，边权值不超过 $A_{i}$ 的边的个数就是有多少 $1 \le j < i$，满足 $Q_{i + 1} - Q_{i} \le K$，注意这里的 $Q_{i}$ 并不代表 $i$ 所在的位置。  
但是这里又怎么求呢？因为我们是对于 **每个排列**，所以我们还是会超时，那么我们再套用一遍刚刚的套路：每个 $1 \le j < i$ 分别再算一下当他可以连边的时候的方案数。  
那么考虑因为有 $i-1$ 个空位，我们可以枚举一个相邻的 $Q_{i} \sim Q_{i + 1}$ 的 $Q_{i + 1} - Q_{i}$ 设为 $k$，然后将 $Q_{i} \sim Q_{i + 1}$ 看成一个点，然后剩下有 $i - 2$ 个，总共 $i - 1$ 个，而总共剩的空位有 $n - k$，有 $\binom{n-k}{i-1}$ 种，最后乘个 $i-1$ 即可，因为每个空位都是如此。  
那么考虑这里是能连多少边，而我们对于每个 $i$ 都只关心 $\le i$ 的那些数的位置，不关心顺序，而大于 $i$  的同理也要乘个顺序，所以 
$$f_{i} = i! \times (n - i)! \times (i - 1) \times \sum_{1 \le k \le K}\binom{n-k}{i-1} $$
而 
$$ans = \sum (f_{i} - f_{i - 1}) \times A_{i}$$
那么这道题就这么结束了，$O(NK)$。
# CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;

int jc[5005], f[5005];
int n, k, a[5005], C[5005][5005];
signed main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1,a + n + 1);
	C[0][0] = 1;
	jc[0] = 1;
	for(int i = 1; i <= n; i++){ //杨辉三角
		C[i][0] = 1;
		jc[i] = jc[i - 1] * i % mod; /阶乘
		for(int j = 1; j <= i; j++){
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++){ //算f[i]
		for(int j = 1; j <= k; j++){ //枚举 Q[i + 1] - Q[i]
			f[i] = (f[i] + jc[i] % mod * jc[n - i] % mod * (i - 1) % mod * C[n - j][i - 1] % mod) % mod; //计算公式
		}
		ans = (ans + (f[i] - f[i - 1] + mod) % mod * a[i]) % mod;//计算答案
	}
	cout << ans << endl; 
	return 0;
}
```
创作不易，给个赞吧 QWQ！

---

## 作者：Lgx_Q (赞：1)

题意：给出 $n$ 个数 $a_{1...n}$，选一个排列 $p_{1...n}$。对于 $|i-j|\le k$ 的点 $i,j$ 之间有一条权为 $\max(a_{p_i},a_{p_j})$ 的边。对于所有排列 $p$，求对应图的 $\text{MST}$ 边权和的总和。

$1\le k<n\le 5000$


----


首先定义一条边的大小比较方式：若权值不同则按权值比；若权值相同按连接的编号较小的点的编号比；若都相同按编号较大的点的编号比。

考虑一条边 $(x,y)$ 的贡献（$x<y$），他的权值为 $\max(a_{p_x},a_{p_y})$，他能被选入 $\text{MST}$ 当且仅当不存在一条起点为 $x$、终点为 $y$ 的路径，满足路径上的边全部小于他。

这个很好理解，因为如果路径存在大于他的边，完全可以用他来代替这条边。

思考什么情况下不存在这样的路径。

+ 对于 $u(u<x,y-u\le k)$，需满足 $a_{p_u}>\max(a_{p_x},a_{p_y})$。如果 $a_{p_u}\le \max(a_{p_x},a_{p_y})$，那么存在路径 $x\rightarrow u\rightarrow y$，不合法。

+ **若** $a_{p_x}>a_{p_y}$，对于 $u(x<u<y)$，需满足 $a_{p_u} \ge a_{p_x}$。因为如果 $a_{p_u}<a_{p_x}$，那么存在路径 $x\rightarrow u\rightarrow y$，不合法。

显然，我们在此情况下无需找一条边数 $>2$ 的路径，只需要满足上面两个条件即可。

枚举 $val=\max(a_{p_x},a_{p_y})$，算出小于 $val$、等于 $val$ 、大于 $val$ 的数的个数分别有 $cnt_1,cnt,cnt_2$ 个。

分类讨论。

+ $a_{p_x}=a_{p_y}=val$

此时需要满足第一个条件。

枚举 $x$ 前面有多少个这样的 $u$ 需要满足条件，设为 $i$，此刻对于 $y$ 有两种情况：

1. $x=i+1,\space \space x<y\le k$

2. $y\ge k,\space \space y-x+i=k$

一共有 $(k-i-1)+(n-k)=n-i-1$ 种情况。

从 $cnt$ 中选两个数 $a_{p_x},a_{p_y}$ 排列有 $A(cnt,2)$ 种，从 $cnt_2$ 中选 $i$ 个数排列有 $A(cnt_2,i)$ 种，其余随便排有 $(n-i-2)!$ 种。

$$(n-i-1)\times A(cnt,2)\times A(cnt_2,i),\times (n-i-2)!$$

+ $a_{p_x}<a_{p_y}=val$

此时需要满足第一个条件，统计方法其实跟 $a_{p_x}=a_{p_y}$ 是类似的，只不过选择 $a_{p_x},a_{p_y}$ 两个数的方法变为了 $cnt\times cnt_1$。

$$(n-i-1)\times cnt\times cnt_1\times A(cnt_2,i),\times (n-i-2)!$$

+ $a_{p_x}>a_{p_y}$

此时两个条件都需要满足。

分两种情况：

+ $y>k$

枚举 $i$ 表示 $x$ 前面需要满足条件 $1$ 的数个数，不难发现 $y-x=k-i$，即 $x,y$ 中间有 $k-i-1$ 个数。$y$ 的取值有 $n-k$ 种，选择 $a_{p_x},a_{p_y}$ 的方案数为 $cnt\times cnt_1$，从 $cnt_2$ 个中选 $i$ 个数排列有 $A(cnt_2,i)$ 种，从 $(cnt_2+cnt-i-1)$ 个（去掉 $a_{p_y}$ ）中选 $(k-i-1)$ 个数排列有 $A(cnt+cnt_2-i-1,k-i-1)$，其余随便 $(n-k-1)!$ 。


$$(n-k)\times cnt\times cnt_1\times A(cnt_2,i)\times A(cnt+cnt_2-i-1,k-i-1)\times (n-k-1)!$$

+ $y\le k$

我们需要枚举两个：枚举 $i$ 表示 $x$ 前面需要满足条件 $1$ 的数的个数，$j$ 表示 $x,y$ 中间的数个数。

那么 $x=i+1,\space\space y=x+j+1=i+j+2$。

类似上面的式子，有

$$\sum_{j=0}^{k-i-2} cnt\times cnt_2\times A(cnt_2,i)\times A(cnt+cnt_2-i-1,j)\times (n-i-j-2)!$$

化一下

$$
\begin{aligned}
\text{原式} &= cnt\times cnt_1\times A(cnt_2,i)\times \sum_{j=0}^{k-i-2}A(cnt+cnt_2-i-1,j)\times (n-i-j-2)! \\

&= cnt\times cnt_1 \times A(cnt_2,i)\times \sum_{j=0}^{k-i-2} \frac {(cnt+cnt_2-i-1)!}{(cnt+cnt_2-i-j-1)!} \times (n-i-j-2)! \\

&= cnt\times cnt_1\times A(cnt_2,i)\times(cnt+cnt_2-i-1)!\times \sum_{j=0}^{k-i-2} \frac{(n-i-j-2)!}{(cnt+cnt_2-i-j-1)!}
\end{aligned}
$$

设 $g=cnt\times cnt_1\times A(cnt_2,i)\times(cnt+cnt_2-i-1)!$。

设 $w[u,v]=\sum_{j=0}^{\min(u,v)} \frac{(v-j)!}{(u-j)!}$，那么

$$
\begin{aligned}
\text{原式} &= g\times (w[cnt+cnt_2-i-1,n-i-2]-w[(cnt+cnt_2-i-1)-(k-i-2)-1,(n-i-2)-(k-i-2)-1])
\end{aligned}
$$

$w[,]$ 可以 $O(n^2)$ 预处理，时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) ((a)>(b)? (a):(b))
#define min(a,b) ((a)<(b)? (a):(b))
#define pir pair<ll,ll>
#define mkp make_pair
#define pb push_back 
#define ad(a,b) (a=(a+b>=mod? a+b-mod:a+b))
using namespace std;
const ll maxn=5010,mod=998244353;
ll n,m,a[maxn],ans,fac[maxn],inv[maxn],w[maxn][maxn];
ll A(ll n,ll m)
{
	if(n<m) return 0;
	return fac[n]*inv[n-m]%mod;
}
void solve(ll val)
{
	ll cnt=0, cnt1=0, cnt2=0;
	ll res=0;
	for(ll i=1;i<=n;i++) cnt+=(a[i]==val), cnt1+=(a[i]<val), cnt2+=(a[i]>val);
	for(ll i=0;i<m;i++)
	{
		res=(res+(m-i-1 + n-m)*A(cnt,2)%mod*A(cnt2,i)%mod*fac[n-i-2])%mod;
	}
	
	for(ll i=0;i<m;i++)
	{
		res=(res+(m-i-1 + n-m)*cnt%mod*cnt1%mod*A(cnt2,i)%mod*fac[n-i-2])%mod;
	}
	
	for(ll i=0;i<m&&i<cnt2+cnt;i++)
	{
		res=(res+(n-m)*cnt%mod*cnt1%mod*A(cnt2,i)%mod*A(cnt2+cnt-i-1,m-1-i)%mod*fac[n-m-1])%mod;
		ll rs=cnt*cnt1%mod*A(cnt2,i)%mod*fac[cnt2+cnt-i-1]%mod, tc=cnt2+cnt-i-1, nk=n-i-2;
		ll r=(w[tc][nk]-(m-2-i<min(tc,nk)? w[tc-(m-2-i)-1][nk-(m-2-i)-1]:0)+mod)%mod;
		res=(res+r*rs)%mod;
	}
	ans=(ans+res*val)%mod;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++) scanf("%lld",a+i);
	fac[0]=inv[0]=fac[1]=inv[1]=1;
	for(ll i=2;i<=n;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	}
	for(ll i=2;i<=n;i++) inv[i]=inv[i-1]*inv[i]%mod;
	for(ll i=0;i<=n;i++)
	{
		for(ll j=0;j<=n;j++)
		{
			ll v=inv[i]*fac[j]%mod;
			if(i&&j) w[i][j]=(w[i-1][j-1]+v)%mod;
			else w[i][j]=v;
		}
	}
	sort(a+1,a+1+n);
	for(ll i=1;i<=n;i++)
	{
		if(a[i]!=a[i-1])
		{
			solve(a[i]);
		}
	} 
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：roBotic (赞：0)

参考了 @[elbissoPtImaerD](https://www.luogu.com.cn/user/359113) 的题解。我真不会数数啊 /ll。

因为已经枚举了全排列，所以和 $A$ 的顺序无关，先排个序。我们记 $c_i$ 表示小于等于 $A_i$ 的数的个数。

拆贡献，每一个权值造成的贡献分开统计。我们针对某一个权值 $A_i$ 进行考虑。根据 Kruskal 贪心求 MST 的方法，我们一定是越小的边能加入一定加入，我们记 $f_j$ 表示所有排列，权值小于等于 $A_i$ 的 $c_i$ 个位置可以连边，尽可能多连且满足条件且不成环的连边个数的总和。那么 $A_i$ 造成的贡献就是 $f_i-f_{i-1}$，也就是这条边比上条边多连的那些边造成了贡献。

于是考虑怎么求 $f_i$。我们把这 $c_i$ 个位置的下标从排列中拉出来，记为序列 $t$。贪心连边，能发现连的边一定是 $t$ 中相邻的位置，并且相邻的位置能连边一定连边。继续拆贡献，我们钦定 $t_p$ 和 $t_{p+1}$ 连上边，统计方案数，我们枚举 $t_{p+1}-t_p$，记为 $j$，则方案数就是在 $n-j$ 个位置中选择 $c_i-1$ 个位置放 $t$ 元素的方案，求和后就是：

$$\sum_{j=1}^k \binom{n-j}{c_i-1}.$$

然后合并贡献，对于 $t$ 有 $c_i-1$ 对相邻元素，所以乘以 $(c_i-1)$，并且排列的方案数有 $c_i!(n-c_i)!$ 种（我们在求和号中已经组合求过了放置的位置，故只需要乘以一个阶乘），所以：

$$f_i=(c_i-1)c_i!(n-c_i)!\sum_{j=1}^k\binom{n-j}{c_i-1}.$$

然后答案就是：

$$\text{Answer}=\sum_{i=1}^n A_i(f_i-f_{i-1}).$$

能发现这个 $f_i$ 只和 $c_i$ 有关，因此可以令 $f_i=g_{c_i}$，其中：

$$g_i=(i-1)i!(n-i)!\sum_{j=1}^k\binom{n-j}{i-1}.$$

代码实现中的 `F` 数组就是这个 $g$。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 5e3 + 10;
int n, A[N], K, cnt[N]; LL F[N], fact[N], inv[N];
const LL MOD = 998244353;
LL Qpow(LL x, LL k, LL P) {
	LL ret = 1, tmp = (x + P) % P;
	while (k) {
		if (k & 1) ret = ret * tmp % P;
		tmp = tmp * tmp % P; k >>= 1;
	} return ret;
}
void init() {
	fact[0] = 1; for (int i = 1; i <= n; i ++) fact[i] = fact[i - 1] * i % MOD;
	inv[n] = Qpow(fact[n], MOD - 2, MOD);
	for (int i = n - 1; i >= 0; i --) inv[i] = inv[i + 1] * (i + 1) % MOD;
	return ;
}
LL C(LL n, LL m) { return (n < m ? 0 : fact[n] * inv[m] % MOD * inv[n - m] % MOD); }
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> K; init();
	for (int i = 1; i <= n; i ++) cin >> A[i];
	sort(A + 1, A + 1 + n);
	for (int i = 1, pt = 1; i <= n; i ++) {
		while (pt < n && A[pt + 1] <= A[i]) ++ pt;
		cnt[i] = pt; 
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= K; j ++) F[i] = (F[i] + C(n - j, i - 1)) % MOD;
		F[i] = F[i] * fact[i] % MOD * fact[n - i] % MOD * (i - 1) % MOD;
	} LL Ans = 0;
	for (int i = 1; i <= n; i ++) Ans = (Ans + A[i] * (F[cnt[i]] + MOD - F[cnt[i - 1]]) % MOD) % MOD;
	cout << Ans << "\n";
	return 0;
}
```

---

## 作者：AtomAlpaca (赞：0)

## 题意


给定正整数 $n,K$ 和一个长度为 $n$ 的序列 $A$。对于一个 $1\sim n$ 的排列 $P$，我们定义 $f(P)$ 为以下问题的答案：

> 给一个 $n$ 个点的无向带权图，对于两点 $i<j$，当且仅当 $j-i\le K$ 时，它们之间有边，边权为 $\max(A_{P_i},A_{P_j})$。  
求这个图的最小生成树边权和。

对于所有可能的排列 $P$，求出它们的 $f(P)$ 之和，答案对 $998\,244\,353$ 取模。

$1\le K< N\le 5000$，$1\le A_i \le 10^9$。

奇妙深刻数数题。

## 题解

首先发现因为要枚举排列，$A$ 的顺序是无关紧要的，可以升序排序处理。

考虑拆贡献，考虑对于每一个 $A_i$ 计算它在所有情况中被选的次数 $f_i$。答案就是 $\sum_{i}^{n}{f_i  A_i}$。

但是这样还是不好求，我们考虑用小于等于 $A_i$ 的边权被选的次数减去小于等于 $A_{i - 1}$ 的边权的被选次数。这相当于构造了这样一个问题：

对于两点 $i<j$，当且仅当 $j-i\le K$ 且 $\max(A_{P_i},A_{P_j}) \le A_x$ 时，它们之间有边。求最多选择多少条边使得构成的图没有环，对于所有排列 $P$ 求和。

因为取 $\max$，所有 $A_{P_i} > x$ 的 $i$ 都不会被选，被选的只有小于 $A_x$ 的所有位置。

再考虑 $j - i \le K$ 这个条件怎么做。我们这里不妨对于一个所有选出来的数的集合有序 $Q$，考虑钦定 $Q_j - Q_{j - 1} = K$，这样的方案一共有 $\tbinom{n-k}{x-1}$ 种，小于等于 $K$ 的情况就有 $\sum_{i = 1}^{K}{\tbinom{n-k}{x-1}}$ 种。一共有 $x-1$ 个这样的位置，那么贡献总和就是 $(x - 1)\sum_{i = 1}^{K}{\tbinom{n-i}{x-1}}$

又考虑和一个 $Q$ 对应的排列的排列方式应该是选出来的 $x$ 个随便排，剩下的 $n - x$ 个随便排并在一起，方案数应该是 $x!(n - x)!$。

所以上述问题的答案就是 $x!(n - x)!(x - 1)\sum_{i = 1}^{K}{\tbinom{n-i}{x-1}}$。相邻的两项相减就能得到 $f$。

## 代码

```c++
#include <bits/stdc++.h>

typedef long long ll;
const int MAX = 5005;
const int MOD = 998244353;

int n, k; ll ans;
ll frc[MAX], ifrc[MAX], g[MAX], a[MAX];

ll qp(ll a, ll x)
{
  ll res = 1;
  while (x) { if (x & 1) { res = res * a % MOD; } x >>= 1; a = a * a % MOD; }
  return res;
}

void init(int x)
{
  frc[0] = ifrc[0] = 1;
  for (int i = 1; i <= x; ++i) { frc[i] = frc[i - 1] * i % MOD; } ifrc[x] = qp(frc[x], MOD - 2);
  for (int i = x - 1; i >= 1; --i) { ifrc[i] = ifrc[i + 1] * (i + 1) % MOD; }
}

ll C(ll x, ll y) { if (x < y) { return 0; } return frc[x] * ifrc[y] % MOD * ifrc[x - y] % MOD; }

int main()
{
  scanf("%d%d", &n, &k); init(5000);
  for (int i = 1; i <= n; ++i) { scanf("%lld", &a[i]); }
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i)
  {
    ll tmp = 0;
    g[i] = frc[i] * frc[n - i] % MOD * (i - 1) % MOD;
    for (int j = 1; j <= k; ++j)
    {
      tmp = (tmp + C(n - j, i - 1)) % MOD;
    }
    g[i] = g[i] * tmp % MOD;
  }
  for (int i = 1; i <= n; ++i) { ans = (ans + (g[i] - g[i - 1] + MOD) % MOD * a[i] % MOD) % MOD; }
  printf("%lld", ans);
  return 0;
}

```

---

