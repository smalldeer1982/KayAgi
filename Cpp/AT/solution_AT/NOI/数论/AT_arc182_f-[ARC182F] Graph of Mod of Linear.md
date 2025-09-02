# [ARC182F] Graph of Mod of Linear

## 题目描述

给定整数 $N, Q$，以及长度为 $Q$ 的整数列 $A=(A_1, A_2, \ldots, A_Q), B=(B_1, B_2, \ldots, B_Q)$。

对于 $k=1,2,\ldots,Q$，请你解决以下问题：

> 有一个无向图，包含 $N$ 个顶点，顶点编号为 $0$ 到 $N-1$，共有 $N$ 条边。第 $i$ 条边（$0 \leq i < N$）连接顶点 $i$ 和顶点 $(A_k \times i + B_k) \bmod N$。请你求出该无向图的连通分量数。

## 说明/提示

## 限制条件

- $1 \leq N \leq 10^6$
- $1 \leq Q \leq 10^5$
- $0 \leq A_k < N$
- $0 \leq B_k < N$
- 所有输入均为整数

## 样例解释 1

对于 $k=1$，可以分为以下 $2$ 个连通分量：
- 包含顶点 $0,1,3,4$ 的连通分量。
- 包含顶点 $2,5$ 的连通分量。
因此，$k=1$ 时的答案为 $2$。

## 样例解释 2

对于 $k=1$，可以分为以下 $3$ 个连通分量：
- 包含顶点 $0,1,3,6,10$ 的连通分量。
- 包含顶点 $2,5,7,8,9$ 的连通分量。
- 包含顶点 $4$ 的连通分量。
因此，$k=1$ 时的答案为 $3$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 3
2 1
0 1
1 0```

### 输出

```
2
1
6```

## 样例 #2

### 输入

```
11 3
9 1
5 3
8 0```

### 输出

```
3
3
2```

## 样例 #3

### 输入

```
182 3
61 2
77 88
180 55```

### 输出

```
36
14
9```

# 题解

## 作者：definieren (赞：2)

## [**F - Graph of Mod of Linear**](https://atcoder.jp/contests/arc182/tasks/arc182_f)

基本上是翻译了一下官方题解，把一些过程写的更详细了。

对每组询问分别考虑。

如果把边视为有向边，则生成的图是一棵内向基环树，连通块数与环的数量是相等的。

首先特判掉 $A = 1$ 和 $A = 0$ 的情况。$A = 0$ 时答案为 $1$，因为连成了一个菊花；$A = 1$ 时答案为 $\gcd(N, B)$，因为连成了 $\gcd(N, B)$ 个环。

发现如果 $A \perp N$，则 $Ax + B$ 互不相等，连成的是若干个环，所以考虑按 $A$ 与 $N$ 是否互质分类讨论。

### Case1: $\gcd(A, N) > 1$

我们想知道的是环上的点有哪些。考虑如果每个点都沿着出边跳 $N$ 步，最后一定跳到环上且环上的点都会被跳到。

所以记 $f^{N}(x)$ 表示从点 $x$ 跳 $N$ 步到达的点，则：
$$\begin{aligned}
f^{N}(x) & \equiv A(\cdots(A(Ax + B) + B) + \cdots) + B \\
& \equiv A^N x + \sum_{i = 0}^{N - 1} B A^{i}  \equiv A^N x + B \frac{A^N - 1}{A - 1} \pmod N
\end{aligned}$$

记 $d = \gcd(N, A^N)$，发现 $f^N(x + 1) - f^N(x) \equiv A^N \equiv 0 \pmod d$。

这就是在说，对于所有在环上的点，它们都是与 $f^N(0) = B\frac{A^N - 1}{A - 1}$ 模 $d$ 同余的。

所以考虑把这些点单独拉出来，转化到 $\gcd(A, N) = 1$ 的情况。

考虑对于环上的一个点 $u = dk_1 + f^N(0)$ 和它连向的点 $v = dk_2 + f^N(0)$，有：
$$\begin{aligned}
dk_2 + f^N(0) &\equiv A(dk_1 + f^N(0)) + B \\
dk_2 &\equiv Adk_1 + (A - 1)f^N(0) + B \\
dk_2 &\equiv Adk_1 + B A^N \pmod N
\end{aligned}$$

两侧同时除以 $d$，可得：
$$\begin{aligned}
k_2 &\equiv Ak_1 + B \frac{A^N}{d} \quad \left(\bmod{\frac{N}{d}} \right)
\end{aligned}$$

问题就从 $(N, A, B)$ 转化为了 $\left(\frac{N}{d}, A \bmod \frac{N}{d}, B \cdot \frac{A^N}{d} \bmod{\frac{N}{d}}\right)$。

### Case2: $\gcd(A, N) = 1$

连通块数与环的数量相等，考虑怎么数环的数量。

可以将每个点的权值设为它所在环的长度的倒数，这样对于一个环长为 $k$ 的环，它的贡献为 $k \cdot \frac{1}{k} = 1$，求和即为环的数量。

对于点 $x$，如果它在 $K$ 步后回到 $x$，那么有：
$$\begin{aligned}
A^K x + B \frac{A^K - 1}{A - 1} & \equiv x \pmod N \\
\left(A^K - 1 \right) \left( x + \frac{B}{A - 1} \right) & \equiv 0 \pmod N \\
\end{aligned}$$
两边同时除以 $\dfrac{\gcd\big(x(A - 1) +B, N(A - 1)\big)}{A - 1}$，得：
$$\begin{aligned}
A^K \equiv 1 \quad \left( \bmod \frac{N(A - 1)}{\gcd\big(x(A - 1) +B, N(A - 1)\big)} \right)
\end{aligned}$$

化简一下。记 $G = \gcd(A - 1, B)$，则 $A' = \frac{A - 1}{G}$，$B' = \frac{B}{G}$，可得到：
$$
A^K \equiv 1 \quad \left( \bmod \frac{N A'}{\gcd(xA' + B', NA')} \right)
$$

此时有 $xA' + B \perp A'$，所以模数分母上的 $\gcd$ 中不含 $A'$ 的因子，可以全部除掉。

所以记 $N' = \dfrac{N}{\gcd(A'^N, N)}$，可得：
$$
A^K \equiv 1 \quad \left( \bmod \frac{N A'}{\gcd(xA' + B', N')} \right)
$$

记 $y = xA' + B' \bmod N'$，由于 $A' \perp N'$，所以对于 $x \in [0, N') \cap \mathbb Z$，$y$ 互不相同且取遍 $[0, N') \cap \mathbb Z$，那么对于 $x \in [0, N) \cap \mathbb Z$，每个不同的 $y$ 都恰好取到过 $\frac{N}{N'}$ 次。

记 $C_y$ 表示 满足 $y = xA' + B' \bmod N'$ 的点 $x$ 的环长，也即最小的 $k$ 满足：
$$
A^K \equiv 1 \quad \left( \bmod \dfrac{N A'}{\gcd(y, N')} \right)
$$

那么有：
$$
ans = \frac{N}{N'} \sum_{y = 0}^{N' - 1} \frac{1}{C_y}
$$

发现对于 $\gcd(y, N')$ 相同的 $y$ 有相同的 $C_y$，所以考虑将枚举 $y$ 改为枚举 $\gcd(y, N')$。

记 $n = \gcd(y, N')$，则对应的 $y$ 有 $\varphi\left(\dfrac{N'}{n}\right)$ 个，因为除掉 $n$ 之后要互质。

更改 $C_n$ 的定义为 满足 $y = xA' + B' \bmod N', \gcd(y, N') = n$ 的点 $x$ 的环长，那么答案的式子可以改写为：
$$
ans = \frac{N}{N'} \sum_{n \mid N'} \frac{1}{C_n} \varphi\left(\dfrac{N'}{n_1}\right)
$$

现在的问题是计算 $C_n$。

有以下性质：
- $C_1$ 为 $\varphi(NA')$ 的因数。
- 对于 $n_1 \mid N'$，$n_2 \mid N'$，如果 $n_1 \mid n_2$，那么 $C_{n_2} \mid C_{n_1}$。

第一个性质是欧拉定理，第二个性质是考虑：
$$\begin{aligned}
A^{C_{n_1}} \equiv 1 \quad \left( \bmod \frac{N'A}{n_1} \right) \\
A^{C_{n_2}} \equiv 1 \quad \left( \bmod \frac{N'A}{n_2} \right)
\end{aligned}$$

因为 $n_1 \mid n_2$，那么 $\frac{N'A}{n_2} \mid \frac{N'A}{n_1}$，所以：
$$
A^{C_{n_1}} \equiv 1 \quad \left( \bmod \frac{N'A}{n_2} \right)
$$
所以 $C_{n_2} \mid C_{n_1}$。

有了这两个性质就可以通过记搜把 $C_n$ 搜出来。
具体来讲：搜索时记录二元组 $(n, C)$ 表示当前的 $n$ 和上一次的 $C$，枚举 $\varphi(NA')$ 的质因子，不断尝试将他们除掉，可以用快速幂判定，算出当前的 $C$ 后枚举 $N'$ 的质因子 $p$，递归到 $(n \cdot p, C)$。

时间复杂度不怎么会算，感觉大概是什么 $O\big(q \omega(V) d(n)\big)$，可能还要乘个 $\log V$ 啥的，其中 $V \le 10^{12}$，$d(n)$ 表示 $n$ 的因子个数，$\omega(n)$ 表示 $n$ 的质因子个数，感觉完全跑不满。

[代码](https://atcoder.jp/contests/arc182/submissions/56646456)

---

## 作者：WrongAnswer_90 (赞：1)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18356144)

### [[ARC182F] Graph of Mod of Linear](https://www.luogu.com.cn/problem/AT_arc182_f)

首先判掉 $A\leq 1$ 的情况，接下来默认 $A\geq 2$。原图是基环树森林，数连通块数等价于数环的个数。

比较自然的一点是，把问题分为 $A,N$ 是否互质。因为如果 $A$ 和 $N$ 互质，则 $Ai+B$ 在 $\bmod N$ 意义下互不相同，所以每个点都在一个环里。

#### 1. $A\not \perp N$

首先定义 $f^K(i)$ 表示从 $i$ 开始走 $K$ 步会走到哪。显然：

$$f^K(i)=A^Ki+B\sum_{j<K}A^j=A^Ki+B\frac{A^K-1}{A-1}$$

然后是一步神奇的转化。我们希望能只保留在环上的点，而 $f^N(i)$ 一定在环上，并且对于 $i\in[0,N-1]$，$f^N(i)$ 一定涵盖了所有在环上的点（所有在环上的点的 $f$ 已经涵盖了）。所以环上的点可以表示为：

$$(iA^N+B\frac{A^N-1}{A-1})\bmod N$$

对于 $i$ 向后走一步：

$$A(iA^N+B\frac{A^N-1}{A-1})+B\equiv jA^N+B\frac{A^N-1}{A-1}\pmod N$$

取 $d=\gcd(A^N,N)$：

$$
\frac{A^N}{d}j=\frac{A^N}{d}Ai+\frac{A^N}{d}B\pmod {\frac{N}{d}}
$$

因为 $\frac{A^N}{d}$ 和 $\frac{N}{d}$ 互质，所以：

$$
j=Ai+\frac{A^N}{d}B\pmod {\frac{N}{d}}
$$

所以问题可以从 $(A,B,N)$ 变为 $(A\bmod \frac N d,B\times\frac{A^N} d\bmod \frac N d,\frac N d)$，转成了互质的情况。

#### 2. $A\perp N$

设 $C_i$ 表示第 $i$ 个点所在的环长，则 $\sum \frac 1 {C_i}$ 就是答案。

从 $i$ 开始走 $K$ 次走回自己，要求的就是：

$$
A^Ki+B\frac{A^K-1}{A-1}\equiv i\pmod N
$$

这个同余方程的最小解。变形一下：

$$
\begin{aligned}
(A^K-1)(i+B\frac{1}{A-1})&\equiv 0\pmod N\\
A^K&\equiv 1\pmod {\frac{N(A-1)}{\gcd(N(A-1),i(A-1)+B)}}\\
\end{aligned}
$$

把模数再变形一下。设 $d=\gcd(A-1,B)$，令 $A'=\frac{A-1}{d}$，$B'=\frac B d$，则：

$$
A^K\equiv 1\pmod {\frac{NA'}{\gcd(NA',iA'+B')}}
$$

此时 $A',B'$ 已经互质，所以 $NA'$ 的贡献只有 $N$ 中的因子。设 $N'=\frac{N}{\gcd(N,A'^N)}$，则：

$$
A^K\equiv 1\pmod {\frac{NA'}{\gcd(N',iA'+B')}}
$$

令 $y=(iA'+B )\bmod N'$，则如果 $i\in [0,N-1]$，则每个 $y$ 都一定恰好被覆盖了 $\frac N {N'}$ 次。所以现在要求的就是：

$$
\begin{aligned}
&\frac N{N'}\sum_{i<N'} C_{\gcd(i,N')}\\
=&\frac N{N'}\sum_{i|N'} C_i\varphi(\frac{N'}{i})
\end{aligned}
$$

其中 $C_i$ 是满足 $A^{C_i}\equiv 1\pmod {\frac{NA'}{\gcd(N',i)}}$ 的最小整数。

首先有性质：

1. 若 $x|y$，则 $\varphi(x)|\varphi(y)$。
2. $A^k\equiv 1\pmod n$ 的解都是 $\varphi(n)$ 的因数并且 $k$ 一定能被表示成 $xk_0$，其中 $k_0$ 表示最小解。

若 $n1\leq n2,n1|n2,n2|N'$，则：

$$
\begin{aligned}
A^{C_1}&\equiv 1\pmod {\frac{NA'}{n1}}\\
A^{C_1}&\equiv 1\pmod {\frac{NA'}{n2}}\\
A^{C_2}&\equiv 1\pmod {\frac{NA'}{n2}}\\
\end{aligned}
$$

所以 $C_1$ 一定是 $C_2$ 的倍数。所以可以用记忆化搜索的方式求解所有的 $C$：考虑把 $\varphi(NA')$ 质因数分解，$C_1$ 初始化为 $\varphi(NA')$，然后不断尝试除 $\varphi(NA')$ 的因子，继续用快速幂判是否合法。

这样求出 $n=1,C_1$ 的答案，然后将 $n$ 乘一个 $\frac{N'}{n}$ 的质因数，令 $C'$ 初始化为 $C_1$，再进行不断尝试除质因子的过程。复杂度一个很松的上界是 $\mathcal O(q\omega_{max}(10^{12})d_{max}(10^{12})))$，$w$ 表示质因子个数，$d$ 表示因数个数。但是完全跑不满满满，所以还是能过的。

```cpp
int n,m,cnt,phi[1000010],pr[300010];
bitset<1000010> vis;
map<int,bool> hash;
vi V[1000010],ve2;
inline int power(int x,int y,int z){int s=1;for(;y;y>>=1,x=x*x%z)if(y&1)s=s*x%z;return s;}
int solve(int A,int B,int N)
{
	if(__gcd(A,N)!=1)
	{
		int d=__gcd(power(A,N,N),N);
		return solve(A%(N/d),power(A,N,N)/d%(N/d)*B%(N/d),N/d);
	}
	if(A==1)return __gcd(B,N);
	if(A==0||N==1)return 1;
	int A_,N_,G=__gcd(A-1,B);
	A_=(A-1)/G,N_=N;
	int ans=0,x=A_,I=0,J=0,Phi=N*A_;
	vector<pii> L,R,ve;ve2.clear(),hash.clear();
	for(int i=2,c;i*i<=x;++i)if(!(x%i)){c=1;while(!(x%i))x/=i,++c;L.eb(mp(i,c));}
	if(x>1)L.eb(mp(x,1));
	x=N;for(int i=2,c;i*i<=x;++i)if(!(x%i)){c=1;while(!(x%i))x/=i,++c;R.eb(mp(i,c));}
	if(x>1)R.eb(mp(x,1));
	while(I<(int)L.size()&&J<(int)R.size())
	{
		if(L[I].fi==R[J].fi)ve.eb(mp(L[I].fi,L[I].se+R[J].se)),++I,++J;
		else if(L[I].fi<R[J].fi)ve.eb(L[I++]);else ve.eb(R[J++]);
	}
	while(I<(int)L.size())ve.eb(L[I++]);
	while(J<(int)R.size())ve.eb(R[J++]);
	for(auto [x,y]:ve){Phi=Phi/x*(x-1);y>1?ve2.eb(x),0:0;for(auto p:V[x-1])ve2.eb(p);}
	sort(ve2.begin(),ve2.end()),ve2.erase(unique(ve2.begin(),ve2.end()),ve2.end());
	function<void(int,int)> dfs=[&](int n,int C)
	{
		if(hash.find(n)!=hash.end())return;
		hash[n]=1;
		for(auto x:ve2)while(C%x==0&&power(A,C/x,N*A_/n)<=1)C/=x;
		ans+=N/N_*phi[N_/n]/C;
		for(auto p:V[N_/n])dfs(n*p,C);
	};
	dfs(1,Phi);
	return ans;
}
inline void mian()
{
	read(n,m),phi[1]=1;int x,y;
	for(int i=2;i<=1000000;++i)
	{
		if(!vis[i])phi[i]=i-1,pr[++cnt]=i;
		for(int j=1;j<=cnt&&pr[j]*i<=1000000;++j)
		{
			vis[i*pr[j]]=1,phi[i*pr[j]]=phi[i]*(pr[j]-1);
			if(i%pr[j]==0){phi[i*pr[j]]+=phi[i];break;}
		}
	}
	for(int i=1;i<=cnt;++i)for(int j=pr[i];j<=1000000;j+=pr[i])V[j].eb(pr[i]);
	for(int i=1;i<=m;++i)read(x,y),write(solve(x,y,n),'\n');
}
```

---

## 作者：隔壁泞2的如心 (赞：1)

咋就我做法这么奇怪啊……？思路都快成弹跳长颈路了……

 _首先这个连通块数有积性，所以当然要给它拆成一堆素数幂分别算出连通块数，再乘起来就好。_ 

这样就设 $n=p^k$，那么分以下几类来讨论：

- $A=1$：这当然是最简单的情况，每个点都等价，答案就是 $\gcd(n,B)$。

- $A=0$：啊？

- $B=0$：这就相当于是一直乘 $A$，如果 $A$ 不可逆，所有点最后都会连向 $0$，否则求出 $A$ 模上 $p^i(0\le i \le k)$ 的阶数就能算出答案。

- $A-1$ 可逆：注意到 $y+\dfrac{B}{A-1}=A(x+\dfrac{B}{A-1})$，这样问题就被转化为了 $B=0$ 的情况。

- $A-1$ 不可逆：好像不能直接推了……不过至少这下子 $A$ 就可逆了，所以图会是一些不交的环。那就试试对于每个 $i$ 求出有多少个 $x$ 满足 $x$ 递推 $i$ 次之后会变回 $x$，这样也能求出连通块数量。可以列出方程：

$$x(1-A^i)\equiv \dfrac{B(1-A^i)}{1-A}\pmod {n}$$

设 $lb(x)$ 为最大的 $k_0$ 使得 $p^{k_0}$ 整除 $x$。（$lb(0)$ 就设为一个巨大无比的数吧）这种类似 $Px\equiv Q\pmod {p^k}$ 方程的解的数量有三种情况：如果 $P \equiv Q \equiv 0\pmod {p^k}$，那么每个 $x$ 都是解；否则如果 $lb(P) \le lb(Q)$，那么有 $p^{lb(P)}$ 个解；再不然，就没有解了。

回到原方程，那么我们就可以分两类讨论：（先前已讨论的特殊情况忽略不计）

- $lb(B) < lb(1-A)$：这时我们只能指望着第三种情况了，不过这样解的数量要么是 $n$ 要么是 $0$，所以图里所有环都一样大。直接选一个点，枚举 $n$ 的因数判断就好。

- $lb(B) \ge lb(1-A)$：这时 $x$ 的数量就是 $p^{lb(1-A^i)}$，由于 $lb(1-A^i)$ 不大，我们可以枚举 $j$，不妨求出有多少个 $i$ 满足 $lb(1-A^i)=j$。所以我们要求的就是……$A$ 模上 $p^j$ 的阶？？

让我缓缓，我回去再看看那个 $B=0$ 且 $A$ 可逆的情况，这好像有点像啊？等等，根据推理，一旦问题被分类到 $lb(B) \ge lb(1-A)$ 的情况，那么答案和 $B$ 其实没有关系，只要 $lb(B)$ 够大就行——那岂不是直接令 $B=0$，就能算出答案了……？这个 $B$……就这么被消掉了？

然后写完代码，测第三个样例，寄。然后手玩三个素数，原来这题答案没有积性吗？？？

……

啊啊啊我怎么这么失败啊！！~~（打开“发布帖子”）（切到“发布犇犇”）（倒头睡大觉）（心态崩溃）（稍微缓了会儿）（重新思考）~~

诶，好像还有救？将两个连通块合并后产生的连通块数，应该是两个连通块内环长的 $\gcd$……那就可以把相同环长的连通块用 map 存在一起，然后暴力做合并。这样时间复杂度是 $O(q\log^{\color{red}?}n\sqrt{n}^{\color{red}?}d^{\color{red}?}(n))$……啊我是真分析不太出来（

不过直觉上应该能过！那就开写！


```cpp
#include<bits/stdc++.h>
#define int long long
#define mpl map<int,int>
using namespace std;
int n,q,np[76],nk[76],spow[1093760][76],d[1093760][76],cnt=0; 
inline int qpow(int n1,int n2,__int128 mod){
    __int128 n3=n1,n4=1;
    while(n2){
        if(n2&1)n4*=n3,n4%=mod;
        n3*=n3,n3%=mod;n2>>=1;
    }return n4;
}
int getr(int x,int p){
	if(x==0)return 21;
	int ret=0;while(x%p==0)ret++,x/=p;
	return ret;
}
int rk(int p,int k,int a){
	if(k==0)return 1;
	int mod=spow[p][k],nowr=spow[p][k-1]*(p-1);
	for(int i=1;i<=d[p][0];i++){
		while(qpow(a,nowr/d[p][i],mod)==1&&nowr%d[p][i]==0)nowr/=d[p][i];
	}
	return nowr;
}
void add(mpl &mp,int v,int c){
	auto x=mp.find(v);
	if(x==mp.end())mp[v]=c;
	else x->second+=c;
}
inline mpl SR(int p,int k,int a){
	mpl ret;for(int i=0;i<k;i++){
		int r=rk(p,i+1,a);
		add(ret,r,spow[p][i]*(p-1)/r);
	}
	add(ret,1,1); 
	return ret;
}
inline mpl solve(int p,int k,int a,int b){
	int mod=spow[p][k];a%=mod;b%=mod;
	mpl ret;
//	printf("%lld %lld %lld %lld %lld\n",mod,p,k,a,b);
	if((a-1)%p==0){
		if(a==1)add(ret,spow[p][k-min(getr(b,p),k)],spow[p][min(getr(b,p),k)]);
		else if(getr(b,p)<getr(a-1,p)){
			for(int i=0;i<=k;i++){
				int pa=qpow(a,spow[p][i],(a-1)*mod);
				if((pa-1)%mod==(pa-1)/(a-1)%mod*b%mod){
					add(ret,spow[p][i],spow[p][k-i]);break;
				}
			}
		}
		else{
			ret=SR(p,k,a);
		}
	}
	else if(a%p==0){
		add(ret,n,1);
	}
	else{
		ret=SR(p,k,a);
	}
//	for(auto x:ret)printf("(%lld,%lld)",x.first,x.second);printf("\n");
	return ret;
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=2;i<=n;i++){
		int k0=0;
		while(n%i==0)n/=i,k0++;
		if(k0>0){
			np[++cnt]=i,nk[cnt]=k0;
			spow[i][0]=1;for(int j=1;j<=k0;j++)spow[i][j]=i*spow[i][j-1];
			int now=i-1;
			for(int j=2;j*j<=now;j++){
				if(now%j==0){
					d[i][++d[i][0]]=j;
					while(now%j==0)now/=j;
				}
			}
			if(now>1)d[i][++d[i][0]]=now;
			d[i][++d[i][0]]=i;
		}
	}
//	for(int i=1;i<=cnt;i++)printf("%lld %lld\n",np[i],nk[i]);
//	for(int i=1;i<=cnt;i++){for(int j=1;j<=d[np[i]][0];j++)printf("%lld ",d[np[i]][j]);printf("\n");}
	while(q--){
		int A,B;mpl ans;ans[1]=1;scanf("%lld%lld",&A,&B);
		for(int i=1;i<=cnt;i++){
			mpl las;mpl nxt=solve(np[i],nk[i],A,B);
			for(auto xa:ans){
				for(auto xb:nxt){
					int g=__gcd(xa.first,xb.first);
					add(las,(xa.first*xb.first)/g,(xa.second*xb.second)*g);
				}
			}
			ans=las;
		}
		int pri=0;for(auto x:ans)pri+=x.second;
		printf("%lld\n",pri);
	}
}
```

交上去，结果……273ms？！

好好好。至少这一切都是值得的！

---

