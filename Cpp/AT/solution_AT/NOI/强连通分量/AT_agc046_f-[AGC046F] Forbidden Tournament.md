# [AGC046F] Forbidden Tournament

## 题目描述

给定整数 $N,K$ 和素数 $P$。请计算满足以下所有条件的 $N$ 个顶点的有向图 $G$ 的个数，并输出其对 $P$ 取模的结果。注意，顶点之间是有区分的。

- $G$ 是一个锦标赛图。也就是说，$G$ 中没有重边和自环，对于 $G$ 的任意两个不同顶点 $u,v$，恰好存在 $u \to v$ 或 $v \to u$ 其中之一的有向边。
- $G$ 中每个顶点的入度都不超过 $K$。
- 对于 $G$ 的任意四个不同的顶点 $a,b,c,d$，不存在 $a\to b,\ b\to c,\ c\to a,\ a\to d,\ b\to d,\ c\to d$ 这 $6$ 条边全部同时存在的情况。

## 说明/提示

## 限制

- $4 \leq N \leq 200$
- $\frac{N-1}{2} \leq K \leq N-1$
- $10^8 < P < 10^9$
- $N,K$ 为整数
- $P$ 为素数

## 样例解释 1

在 $4$ 个顶点的图中，共有 $64$ 个锦标赛图，其中有 $8$ 个包含被禁止的诱导子图，剩下 $56$ 个满足条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 3 998244353```

### 输出

```
56```

## 样例 #2

### 输入

```
7 3 998244353```

### 输出

```
720```

## 样例 #3

### 输入

```
50 37 998244353```

### 输出

```
495799508```

# 题解

## 作者：jun头吉吉 (赞：2)

## 题意

定义 $H$ 有四个点 $a,b,c,d$ 构成，并且满足 $ a\to\ b,\ b\to\ c,\ c\to\ a,\ a\to\ d,\ b\to\ d,\ c\to\ d $。

问有 $N$ 个点且每个点度数不超过 $K$ 的竞赛图的数目使得不存在 $H$。

$4\le N\le200$。

## 题解

这 都 能 数 ？

以下内容 $a\to b$ 表示有从 $a$ 到 $b$ 的有向边。$a\to b$ 和 $b\not\to a$ 是等价的。

以下内容需要用到的结论有如果竞赛图有环，那么一定存在三元环。~~证明留作习题~~ 就考虑一个 $>3$ 的环中间割一条边变成一个较小的环，最终肯定可以到达三元环。

题目中禁止出现的子图，直观的理解就是**三元环上三个点都连向一个点**。

很厉害的题目。考虑如果有入度为 $0$ 的点，那么可以把这个点删掉变成一个 $N-1,K-1$ 的子问题。所以我们枚举删了 $i$ 个点，就是一个 $N-i,K-i$ 的子问题，系数是 $\binom Nii!$，删除这 $i$ 个点是有顺序的。

然后接下来我们考虑的问题**每个点至少有一个入度**。

考虑我们拉出来一个点 $v$，记 $Y=\{w|v\to w\}$，也就是 $v$ 的出边连向的点的集合，$X=V\setminus Y$，也就是 $v$ 的入边加上 $v$ 自己。

然后如果 $X$ 中有环，也就是有三元环，首先 $v$ 肯定不在环内，那么这个环都向 $v$ 连边，然后就构成了 $H$。所以我们得到了第一条结论：

**结论$\mathrm I.$** $X$ 是一个 DAG，存在一个 $x_1,\dots,x_k$ 且 $x_k=v$ ，满足若 $i<j$，则 $x_i\to x_j$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ml6rmrcb.png)

如图1所示，对于 $u\in X,w\in Y$，如果 $w\to u$，且 $w\to w'$，我们可以推出 $w'\to u$，否则就会构成 $H$。

**性质$\mathrm I.$** 如果 $u\in X,w\in Y$，如果 $w\to u$，则所有 $w$ 能走到的 $w'$ 都有 $w'\to u$

然后一个显然的结论就是如果 $Y$ 中有环，那么没有 $w$ 能走到三元环，要么环缩点之后在 $w$ 之前，三个点都和 $w$ 右边。观察图2和图3不难发现两种情况必然会有 $H$ 出现。

**性质$\mathrm {II}.$** 如果存在 $u\in X,w\in Y$，且 $w\to u$，那么 $Y$ 也一定没有环。

然后我们保证了每个点至少有一个入度，所以取 $u=x_1$，至少存在一个 $w$ 满足 $w\to u$，那么 $Y$ 一定没有环。

**结论$\mathrm {II}.$** $Y$ 是一个 DAG，存在一个 $y_1,\dots,y_l$ ，满足若 $i<j$，则 $y_i\to y_j$。

**结论$\mathrm {III}.$** 当 $Y$ 是 DAG 时 **性质$\mathrm I$** 可以变成若 $y_j\to x_i$，那么对于 $j'\in[j,l]$，$y_{j'}\to x_i$。

然后发现如果 $y_l\not\to x_1$，那么不会有 $y_i\to x_1$，这与入度至少为 $1$ 矛盾，因此：

**结论$\mathrm {IV}.$** $y_l\to x_1$ 一定成立。

![](https://cdn.luogu.com.cn/upload/image_hosting/71oo7fsh.png)

如图4，对于 $2\le i\le k$，如果  $y_l\not\to x_i$，那么对于 $i'\in[i+1,k]$，如果 $y_l\to x_{i'}$，那么显然就构成了 $H$，所以我们可以断定：

**结论$\mathrm V.$**如果 $i'>i,y_l\not\to x_i$，则 $y_l\not\to x_{i'}$。

对于我们找到最大的 $t$ 满足 $y_l\to x_t$，那么对于 $i\in [1,t],j\in[1,l-1],i'\in[i+1,t]$，如果 $x_i\to y_j$，那么已经有三元环了，如果 $y_j\to x_{i'}$，我们又可以推出 $y_l\to x_{i'}$，然后就构成了 $H$。由此，我们推出最后一条结论：

**结论$\mathrm {VI}.$** 对于 $1\le i'<i\le t$，如果 $y_j\to x_i$，则 $y_j\to x_{i'}$。

不难验证如果满足所有六条结论，则一定不存在 $H$。

如果我们画一个 $k\times l$ 的网格图，$y_j\to x_i$ 则将 $(i,j)$ 涂黑，那么这个网格图满足：

- 如果 $(i,j)$ 为黑，则所有$1\le i'< i$， $(i',j)$ 也为黑
- 如果 $(i,j)$ 为黑，则所有 $j<j'\le l$，$(i,j')$ 也为黑
- $(1,l)$ 为黑

当然因为 $v=x_k$，所以 $(k,j)$ 必然不能为黑。

没有度数就直接网格图上dp这一段阶梯状物即可。

有度数限制就相当于一行的黑色数量不能超过某个值，一列的白色数量不能超过某个值。这个不难在 $\mathcal O(kl)$ 的复杂度求出。

然后求方案数就是钦定 $v=1$，枚举 $k,l$ 网格图上填色。然后 $x_1,\dots,x_{k-1},y_1,\dots,y_l$ 的方案数是 $(n-1)!$，其中 $n$ 指的是当前子问题的规模。

复杂度 $\mathcal O(N^4)$。

## 代码
```cpp
const int N=3e2+10;
int n,k;
mint C[N][N],fac[N];
mint dp[N][N];
mint calc(int k,int l,int up){
	dp[0][0]=1;
	for(int j=1;j<=l;j++){
		mint sum=0;
		for(int i=0;i<k;i++){
			sum+=dp[j-1][i];
			if((i-1)+(l-j+1)<=up&&(j-1)+(k-i)<=up)
				dp[j][i]=sum;
			else dp[j][i]=0;
		}
	}
	mint ans=0;
	for(int i=1;i<k;i++)ans+=dp[l][i];
	return ans;
}
mint calc(int n,int k){
	if(n==1)return 1;
	mint ans=0;
	for(int i=1;i<=k+1;i++)ans+=calc(i,n-i,k);
	return ans*fac[n-1];
}
signed main(){
	read(n,k,mod);
	fac[0]=1;for(int i=1;i<N;i++)fac[i]=fac[i-1]*i;
	for(int i=0;i<N;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}mint ans=0;
	for(int i=0;i<=k;i++)ans+=calc(n-i,k-i)*C[n][i]*fac[i];
	writeln(ans.x);
}
```

---

## 作者：syzf2222 (赞：2)

这个题是可以做的。

---

注意到一个竞赛图可以缩成链状，如果我们在非链底处存在一个三元环就寄了。

**引理1：一个不小于 $3$ 的 SCC 中必然存在三元环。**

证明：考虑归纳。$n=3$ 时显然。

$n>3$ 时，由于 SCC 必然存在哈密顿回路，那我们把这个回路提出来，形如 $1\to 2\to 3\to...\to n\to 1$。

若 $3\to 1$，则 $(1,2,3)$ 已经是三元环，否则把 $2$ 剔除仍是 SCC。

所以现在非链底的 SCC 都只能是单点了。

现在考虑最后一个 SCC,当然我们只讨论不是单点的情况。随便拉出一个单点 $x$。

**引理2：$x$ 的前驱和后继都形成一条链。**

证明：前驱是显然的，如果不是单点就必然有三元环了。设前驱的链顶为 $S$。

考虑后继。若不形成一个链，则在最后有一个 SCC。

如果这个 SCC 中所有点都是连向 $S$ 的，则这些中形成了要求的子图了。

否则一定存在两个非空集合 $S_1,S_2$，$S_1$ 中连向 $S$，$S_2$ 中被 $S$ 连向。

不存在 $a\in S_1,b\in S_2,a\to b$，否则 $(x,S,a,b)$ 为要求的子图。

故 $S_2\to S_1$，所以这不是 SCC！

现在考虑其前驱序列 $\{I_p\}$ 与后继集合 $\{O_q\}$ 的连边情况。

首先一定有 $O_q\to I_1$，因为要形成一个 SCC。

注意到每个 $I$ 向 $O$ 的连边一定是一个前缀是出边。否则如果 $\exists i<j,I_a\to O_j,O_i\to I_a$，则 $(I_a,O_i,x,O_j)$ 是要求的子图。

设 $P_i$ 为分界点，即 $\forall j\in [1,P_j],I_i\to O_j,j\in (P_i,q],O_j\to I_i$。

发现 $P$ 是不降的，否则 $\exists i,P_i>P_{i+1}$，则 $(I_i,O_{P_i},O_{P_i+1},I_{i+1})$ 是要求的子图。

但是显然这个条件显然要把 $P_i=q$ 排除在外，但是真的要排除在外吗？

若存在 $i<j,q=P_i>P_j$，则 $(I_1,O_q,I_i,I_j)$ 是要求的子图。

那么现在所有的情况都讨论完了，以上的条件就是充要的。

于是现在可以计算了。首先枚举一开始有多少个单点最为前缀，其次枚举在链底的 SCC 内有前驱大小，然后 $dp$ 连边情况。

设 $dp_{i,j}$ 表示 $P_i=j$ 的方案数，可以从 $dp_{i-1,k},k\leqslant j$ 处转移来。

注意 $dp_{i,j}$ 存在当且仅当 $I_i$ 和 $O_j$ 的度数都不超过限制，而这两个都可以 $O(1)$ 计算得到。

时间复杂度 $O(n^4)$。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=205;
int mod,C[N][N],fac[N],ans,dp[N][N];
inline int calc(int n,int m){
	if(m<=0)return 0;int res=0;
	for(int p=1;p<n-1;p++){
		int q=n-1-p,sum=0;dp[1][q]=0;
		if(max(p,q)>m)continue;
		for(int i=0;i<q;i++){
			dp[1][i]=1;
			if(q-i>m)dp[1][i]=0;
			if(i&&p+i>m)dp[1][i]=0;
		}for(int i=2;i<=p;i++)
			for(int j=0,S=0;j<=q;j++){
				S=(S+dp[i-1][j])%mod,dp[i][j]=S;
				if(i-1+q-j>m)dp[i][j]=0;
				if(j&&p-i+1+1+j-1>m)dp[i][j]=0;
			}
		for(int i=0;i<=q;i++)
			sum=(sum+dp[p][i])%mod;
		res=(res+1ll*C[n-1][p]*fac[p]%mod*fac[q]%mod*sum)%mod;
	}return res;
}
int n,m;
int main(){
	n=read(),m=read(),mod=read();
	fac[0]=C[0][0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=1;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}if(m==n-1)ans=fac[n];
	for(int i=0;i<=n-3;i++)
		ans=(ans+1ll*fac[i]*C[n][i]%mod*calc(n-i,m-i))%mod;
	printf("%d\n",ans);
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：Cindy_Li (赞：1)

神秘性质题，笔者希望尽力解释寻找这些性质背后的想法。

记号约定：$\to $ 表示边定向，$\Rightarrow $ 表示能直接/间接到达。

参考：[jun头吉吉](https://www.luogu.com.cn/article/2bu087mk)

---------------

真难则反，“满足任意一种” 转化成 “两种都不满足”。

于是转化为同时满足：
1. 入度 $\le k$。
2. 不存在形如三元环指向同一个点的导出子图。

显然度数限制是弱的，子图限制是强的。

**Lemma 1：竞赛图存在任意环则定存在三元环。** 

证明采用归纳，考虑从一个点开始不断缩环，最后一定只剩下三元环。

则我们可以想办法把竞赛图限定成 DAG，而竞赛图如果是 DAG，就会有确定的形态：
- 有向无环竞赛图的拓扑序对应图上的一条有向链。
- 不妨记为 $x_1,x_2,\dots,x_k$，则 $\forall i<j,x_i\to x_j$。

这对于我们的后续分析是非常有利的，于是考虑找到 DAG 的限制。

----------

竞赛图计数的经典套路是删 $0$ 度点，去掉 $i$ 个 $0$ 度点的方案数是 ${n\choose i}i!$。

接下来，考虑找到“指向”的这个点，不妨任意钦定一个点 $v$，记它的入度点集为 $X$，出度点集为 $Y$。

**Lemma 2：$X$ 导出子图为 DAG。**

这是显然的，接下来考虑证明 $Y$ 导出子图也没有三元环，即若存在三元环，定不合法。

记三元环为 $(a,b,c)$。找到非环内的点 $w\in Y$:
- 若 $a\to w,b\to w,c\to w$，则不合法（如图3）。
- 否则，$\forall w\in Y$，$w\Rightarrow a,b,c$。

**Lemma 3：若 $w,w'\in Y,u\in X,w\to u,w\Rightarrow w'$，则 $w'\to u$。**

证明如图1，$4$ 个点确定 $5$ 条边，已经有了三元环 $(u,v,w)$，那么 $w'\to u$ 就被确定了。

![](https://cdn.luogu.com.cn/upload/image_hosting/ml6rmrcb.png)
（借用一下这位老师的图）

由于 $w\Rightarrow a,b,c$，$(a,b,c,u)$ 就形成了非法子图（如图2）。
而由于每个点至少有一个入度，取 $u=x_1$ 则一定可以找到合法的 $w$。

**Lemma 4：Y 的导出子图是 DAG。**

---------

接下来，$X,Y$ 两部分内部已经变成链了，考虑 $X,Y$ 之间的边（这一部分是最神秘的）。

注意到，在 Lemma 4 的前提下，Lemma 3 可以改写为：
- 若 $y_j\to x_i$，则 $y_{[j,l]}\to x_i$

显然，一定有 $y_l\to x_1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/71oo7fsh.png)

我们还是考虑寻找三元环，如图 4，此时 $(x_1,x_i,y_l)$ 形成了三元环。

**Lemma 5：若 $y_l\not\to x_i$，则 $y_l\not\to x_{[i+1,k]}$。**

此时 $y_l$ 向 $X$ 集合连边形如：
- 对于 $i\in [1,t]$，$y_l\to x_i$。
- 对于 $i\in [t+1,k]$，$y_l\not\to x_i$。

**Lemma 6：若 $y_j\to x_i$，则 $y_j\to x_{[1,i]}$。**

如图5，若存在 $i\in [1,t],y_j\not\to x_i$，则 $x_i,y_j,y_l$ 形成了三元环，若 $y_j\to x_{i'}$ 则 $y_l\to x_{i'}$，形成了不合法子图。

-------------

可以验证，满足了上述条件的图，就一定符合题目要求。

接下来考虑刻画 $X$，$Y$ 之间的连边，发现在 $k\times l$ 的网格图中形如右下阶梯。

```
00111111
00000111
00000011
00000000
```
（$0$ 表示 $x_i\to y_j$）

注意到，$y_l\to x_1$，则 $(1,l)$ 一定是 `1`；$x_k=v$ 则最后一行一定全 `0`。

容易从左到右 dp 出合法网格图的数量。

对于度数限制，考虑 $X$ $Y$ 集合分别的贡献，在 dp 过程中判断即可。

-----------------

code:

```c++
int f[N][N];
inline int calc(int k,int l,int lm){
    f[0][0]=1;
    rep(j,1,l){
        int sum=0;
        rep(i,0,k){
            sum=pls(sum,f[j-1][i]);
            if(i-1+l-j+1<=lm && j-1+k-i<=lm)
                f[j][i]=sum;
            else f[j][i]=0;
        }
    } 
    int res=0;
    rep(i,1,k-1) res=pls(res,f[l][i]);
    return res;
}
int fac[N],ivf[N];
inline int calc(int n,int k){
    if(n==1) return 1;
    int res=0;
    rep(i,1,k+1) res=pls(res,calc(i,n-i,k));
    return mul(res,fac[n-1]);
}


int main(){
    int n,k;read(n),read(k),read(mod);
    fac[0]=ivf[0]=1;
    rep(i,1,n) fac[i]=mul(fac[i-1],i);
    ivf[n]=fp(fac[n],mod-2);
    per(i,n-1,1) ivf[i]=mul(ivf[i+1],i+1);
    int ans=0;
    rep(i,0,k) ans=pls(ans,mul(calc(n-i,k-i),mul(fac[n],ivf[n-i])));
    printf("%d\n",mul(mns(fp(2,n*(n-1)/2),ans),fp(fp(2,n*(n-1)/2),mod-2)));
    return 0;
}
```

---

## 作者：JWRuixi (赞：1)

### 题意

计数满足如下条件的大小为 $n$ 的竞赛图数量：

- 每个点入度不超过 $k$；
- 不存在一个三元环且这三个点有一个共同的出点。

答案对 $P$ 取模。

### 分析

**Lemma $1$**：竞赛图上一个大小不小于 $3$ 的强连通分量一定包含一个三元环。

**证明**：对于一个环，在其中任意非相邻节点连边都会产生一个更小的环，所以最小环长不超过 $3$。

首先考虑简化一下图的形态：首先如果对其进行缩点，那么结果一定是一条链，那么如果其中除了叶子以外存在一个 SCC，那么由引理 $1$ 就一定存在不合法结构。所以正确的图一定是由一个 DAG 连向一个 SCC。

我们接下来考虑底下 SCC 的部分。考虑枚举其中的一个节点 $u$，将整个 SCC 分成前驱 $U$ 和后继 $D$ 两个部分。

**Lemma $2$**：$U$ 的导出子图是一个 DAG。

**证明**：考虑反证：若 $|U| \ge 3$，存在一个三元环，且环中的节点均连向 $u$；若 $|U| < 3$，显然是一个 DAG。

对于 $v \in D$，设 $S_v = \{w | w \in U, (v, w) \in E\}$（换而言之就是 $v$ 后继与 $U$ 的交集）。

**Lemma $3$**：对于 $p, q \in D$，若 $p \to q$，则 $S_p \subseteq S_q$。

**证明**：反之则 $\exist r, p \to r, q \not \to r$，则 $((u, p, r), q)$ 是一个非法结构。

**Lemma $4$**：$D$ 的导出子图是一个 DAG。

**证明**：反之存在一个三元环 $(p, q, r)$。由引理 $3$ 我们知道 $S_p = S_q = S_r$，又他们不能有共同出点，所以 $S_p = S_q = S_r = \empty$。考虑另外一个点 $t \in D$，显然如果 $p, q, r$ 均指向 $t$ 的就非法了，所以至少存在一条由 $t$ 指向环的边，则 $S_t \subseteq S_p = \empty$。所以我们证明了 $\forall v \in D, S_v = \empty$，换而言之 $U$ 这个 DAG 完全指向 $u \cup D$，与这是一个 SCC 的假设矛盾。

那么现在可能出现矛盾的部分只能是 $U, D$ 之间。

我们发现一种限制很强的情况：假设 $p_1, p_2 \in U, q_1, q_2 \in D$，不妨 $p_1 \to p_2, q_1 \to q_2$。显然不存在 $((p_1, p_2, q_1), q_2)$（考虑 $q_1 \to p_1, q_2 \not \to p_1$ 与 $S_{q_1} \subseteq S_{q_2}$ 矛盾），若以只能是 $((q_1, q_2, p_1), p_2)$，也就是说 $p_1 \in S_{q_2}, p_1 \not \in S_{q_1}, p_2 \in S_{q_1}, S_{q_2}$ 不能只连向后而不连向前意味着 $\forall v \in D$，$S_v$ 是 $U$ 组成的链的一个前缀。

我们不难发现这个限制同样可以满足 $((p_1, p_2, q_1), p_3)$ 和 $((q_1, q_2, p_1), q_3)$ 也包含在这个范围中。

我们将 $U, D$ 这两条链一次标号，不关心具体是谁，设 $a_i$ 表示 $D$ 上第 $i$ 个点连向 $U$ 上 $1 \sim a_i$ 这个前缀，那么需要满足：

- $v \in D$：$i + |U| - a_i \le k$；
- $v \in U$：$\sum[a_j \ge i] + i - 1 \le k$。

对于第二条限制，我们考虑贪心取最有可能出事的位置，就有 $|D| - i + 1 + a_i - 1 \le k$，这样就分别得到了 $a_i$ 的上下界。

设计 $dp_{i, j}$：考虑 $1 \sim i, a_i = j$ 的方案数，暴力枚举 DAG 的大小和 $|U|$ 的大小，用前缀和优化转移即可。

时间复杂度 $\mathcal O(n^3k)$。

### Code

提交记录：<https://atcoder.jp/contests/agc046/submissions/49350128>。

---

## 作者：UltiMadow (赞：1)

引理 $1$：竞赛图中若没有三元环则是 DAG。

证明：考虑反证，假设图中最小环为 $p_1,p_2,\dots,p_k(k\ge 4)$，则考虑 $p_1$ 和 $p_3$ 之间的边，无论以什么方向连都会产生一个更小的环，矛盾。

考虑一张竞赛图，若其中存在一个入度为 $0$ 的点，则可以去掉这个点，转化为一个更小的子问题，所以只需要考虑所有点入度 $>0$ 的情况。

任意取一个点 $u$，记 $V$ 表示 $u$ 的前驱集合，$V' $ 表示 $u$ 的后继集合。

引理 $2$：$V$ 的导出子图是 DAG。

证明：若 $V$ 不是 DAG，则有三元环，设为 $p_1,p_2,p_3$，则 $((p_1,p_2,p_3),u)$ 不合法。

记 $S_v(v\in V')$ 表示 $v$ 的后继中在 $V$ 集合中的点集。

引理 $3$：若对于 $p_1,p_2\in V'$，边 $p_1\to p_2$ 存在，则 $S_{p_1}\subseteq S_{p_2}$。

证明：考虑反证，若存在 $v\in V$ 使得 $v\in S_{p_1}\land v\notin S_{p_2}$ 成立，则 $((d,v,p_1),p_2)$ 不合法，矛盾。

引理 $4$：$V'$ 的导出子图是 DAG。

证明：考虑反证，若存在三元环 $p_1,p_2,p_3$，则 $S_{p_1}=S_{p_2}=S_{p_3}=\emptyset$ 成立（否则取 $v\in S_{p_1}$，有 $((p_1,p_2,p_3),v)$ 不合法）。

再任取 $p_4\in V'$，若不存在 $p_4\to p_i$ 的边，则 $((p_1,p_2,p_3),p_4)$ 不合法，所以一定存在 $p_4\to p_i$ 的边，则 $S_{p_4}\subseteq S_{p_i}=\emptyset$，即 $S_{p_4}=\emptyset$。

由于 $V$ 的导出子图为 DAG，所以取其中入度为 $0$ 的点，由于 $V' $ 中所有 $S$ 都为空集，所以这个点的总入度为 $0$，与入度 $>0$ 矛盾，得证。

接下来考虑形如 $(p_1,p_2,q_1,q_2)$ 的不合法情况，其中 $p_1,p_2\in V,q_1,q_2\in V'$，不妨设有边 $p_1\to p_2$，$q_1\to q_2$。

根据引理 $3$ 可知 $((p_1,p_2,q_1),q_2)$ 不合法的情况不存在。

若 $((p_1,q_1,q_2),p_2)$ 不合法，则 $p_1\in S_{q_2},p_2\in S_{q_1},p_2\in S_{q_2}$，可知 $S_v$ 一定是 $V$ 中拓扑序的一段前缀。

而对于其他形式的不合法情况，这个条件也是充分的。

记 $a_i=|S_v|$，其中 $v$ 在 $V'$ 的导出子图中拓扑序为 $i$，可以把限制进行如下转换：

1. $0\le a_1\le a_2\le\dots\le a_{|V'|}$，且 $a_{|V'|}\ge 1$（由于所有点入度 $>0$ 所以 $V$ 中拓扑序最小的点一定在 $a_{|V'|}$ 中）。
  
2. 对于任意 $1\le i\le |V'|$，有 $|V|-a_i+i\le k$。
  
3. 对于任意 $1\le i\le |V|$，有 $\sum[a_i\ge i]+i-1\le k$。
  

第三个条件可以直接拿所有的 $j=a_i$ 来判，所以可以转化为对于任意 $1\le i\le |V'|$ 有 $|V'|-i+a_i\le k$。

即每个 $a_i$ 都有个范围，且要求递增。

设 $f_{i,j}$ 表示考虑前 $i$ 个数，$a_i=j$ 的方案数，用前缀和维护转移即可。

时间复杂度 $\mathcal O(n^4)$。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 210
using namespace std;
int n,d,p;
int qpow(int x,int y){
	int ret=1;
	for(;y;y>>=1,x=x*x%p)if(y&1)ret=ret*x%p;
	return ret;
}
int fac[MAXN],ifac[MAXN];
int C(int x,int y){return x<y?0:fac[x]*ifac[y]%p*ifac[x-y]%p;}
int f[MAXN][MAXN],sum[MAXN];
int l[MAXN],r[MAXN];
int solve(int n,int d){
	if(n==1)return 1;
	int ret=0;
	for(int v=1;v<n-1;v++){
		int cv=n-v-1;if(v>d||cv>d)continue;
		for(int i=1;i<=cv;i++)
			l[i]=max(v+i-d,0ll),r[i]=min(d+i-cv,v);
		memset(f,0,sizeof(f));f[0][0]=1;
		for(int i=1;i<=cv;i++){
			memset(sum,0,sizeof(sum));
			sum[0]=f[i-1][0];
			for(int j=1;j<=v;j++)sum[j]=(sum[j-1]+f[i-1][j])%p;
			for(int j=l[i];j<=r[i];j++)f[i][j]=sum[j];
		}int res=0;
		for(int i=1;i<=v;i++)res=(res+f[cv][i])%p;
		ret=(ret+res*fac[n-1])%p;
	}return ret;
}
signed main(){
	scanf("%lld%lld%lld",&n,&d,&p);
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%p;
	ifac[n]=qpow(fac[n],p-2);
	for(int i=n;i;i--)ifac[i-1]=ifac[i]*i%p;
	int ans=0;
	for(int i=0;i<=d;i++)ans=(ans+solve(n-i,d-i)*C(n,i)%p*fac[i]%p)%p;
	printf("%lld",ans);
	return 0;
}
```

---

