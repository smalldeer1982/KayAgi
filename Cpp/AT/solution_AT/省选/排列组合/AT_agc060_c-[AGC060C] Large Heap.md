# [AGC060C] Large Heap

## 题目描述

考虑 $(1,2,\cdots,2^N-1)$ 的一个排列 $P=(P_1,P_2,\cdots,P_{2^N-1})$。当 $P$ 满足以下所有条件时，称其为**堆式**排列：

- $P_i < P_{2i}$（$1 \leq i \leq 2^{N-1}-1$）
- $P_i < P_{2i+1}$（$1 \leq i \leq 2^{N-1}-1$）

给定整数 $A,B$，令 $U=2^A,\ V=2^{B+1}-1$。

从所有堆式排列中等概率随机选取一个，求 $P_U < P_V$ 的概率对 $998244353$ 取模的结果。

概率 $\bmod{998244353}$ 的定义：可以证明，在本题的约束下，所求概率一定是有理数。设其最简分数为 $\frac{P}{Q}$，且 $Q \not\equiv 0 \pmod{998244353}$。因此，存在唯一的整数 $R$ 满足 $R \times Q \equiv P \pmod{998244353},\ 0 \leq R < 998244353$。请输出这个 $R$。

## 说明/提示

### 数据范围

- $2 \leq N \leq 5000$
- $1 \leq A,B \leq N-1$
- 输入的所有数均为整数

### 样例解释 1

堆式排列有 $P=(1,2,3),(1,3,2)$ 共 $2$ 种。$P_2 < P_3$ 的概率为 $1/2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1 1```

### 输出

```
499122177```

## 样例 #2

### 输入

```
3 1 2```

### 输出

```
124780545```

## 样例 #3

### 输入

```
4 3 2```

### 输出

```
260479386```

## 样例 #4

### 输入

```
2022 12 25```

### 输出

```
741532295```

# 题解

## 作者：DeaphetS (赞：32)

看了几篇题解都是从下往上（子树大小从小到大）推的，来整一个从上往下的。

题目链接：[C - Large Heap](https://atcoder.jp/contests/agc060/tasks/agc060_c)

题目大意：称一个大小为 $2^N-1$ 的排列是好排列当且仅当其满足对任意 $1\le i\le 2^{N-1}-1$，有 $P_i<P_{2i}$ 且 $P_i<P_{2i+1}$。给定 $N,A,B$，问在所有的好排列中选取一个排列，其满足 $P_{2^A}<P_{2^{B+1}-1}$ 的概率。

### 分析题意

$P_i<P_{2i}$ 且 $P_i<P_{2i+1}$ 这个限制一眼就是二叉树，那么把排列放到一个以 $1$ 为根的满二叉树上，就可以把它看做是一个小根堆。题目要问的就是深度为 $A$ 的在最左边的点 $U$ 比深度为 $B$ 的在最右边的点 $V$ 小的概率，考虑使用动态规划解决此题。

### 状态设立与转移

考虑从小到大逐一确定每个数字所在位置的过程，一个位置被放上数字当且仅当其父亲上也有数字，那么答案就只与根节点到 $U,V$ 这两个点上路径上的点有关。于是设 $f_{i,j}$ 表示左边深度为 $i$ 的点已经放了，右边深度为 $j$ 的点还没放，且**恰好**放到 $j-1$ 的概率。此时的状态对应的大小关系就是 $P_{2^j-1}<P_{2^i}<P_{2^{j+1}-1}$，最后答案即为 $\sum_{i=1}^{B}f_{A,i}$。

之所以要这么设立状态是因为，当我们在考虑下一个数字放哪的时候，我们需要明确目前参与“招标”的具体是哪两个点。如果仅仅只是知道左边深度为 $i$ 的点小于右边深度为 $j$ 的点，我们是难以保证左边的点其是不是已经在之前战胜了右边的点的祖先的。

考虑如何转移，$f_{i,j}$ 所表示情况是：左边已经放到了深度为 $i$ 的点，右边已经放到了深度为 $j-1$ 的点。那么下一轮要参与 $\text{PK}$ 的就是左边深度为 $i+1$ 的点与右边深度为 $j$ 的点。如果左边胜出则转移至 $f_{i+1,j}$，否则就会发生右边深度为 $j$ 的点**恰好**小于左边深度为 $i+1$ 的点的情况，那么考虑对称性，可以转移到 $f_{j,i+1}$ 上。

考虑每次转移要乘上的概率系数，显然除了以这两个点为根的子树外，其它位置上的值并不会影响对应概率。那么当两子树大小分别为 $x,y$ 时，这两个子树内分配数字的方案总共有 $\binom{x+y}{x}$ 种。若钦定了最小值在左边这个大小为 $x$ 的子树上，那么分配方案就有 $\binom{x+y-1}{x-1}$，计算得出对应概率系数就是 $\frac{x}{x+y}$。

### 常见错误

之前在想这题时陷入了一个误区，把这题扔给队友后他也和我出现了同样的问题，于是记录下来以示警戒。

一种常见的错误就是在设立状态时，直接令 $g_{i,j}$ 表示左边深度为 $i$ 的点比右边深度为 $j$ 的点小的概率，然后用上述方式转移。这样会导致出错，比如在 $n=3$ 时，可以得出 $g_{1,2}=\frac{7}{8}$，那么考虑从 $g_{1,2}$ 转移到 $g_{2,2}$ 的过程，会神奇的得出 $g_{2,2}=g_{1,2}\times \frac{1}{2}=\frac{7}{16}\neq\frac{1}{2}$，于是就寄了。

而寄的原因就是，如果 $\text{DP}$ 时是直接考虑两棵子树的状态，那么在转移计算概率时相当于就是已经钦定了两个子树的状态，与无后效性原则相悖。这也是本人考虑从上往下一个个放数字的过程入手的原因。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 5050
#define LL long long
#define MOD 998244353
int n,a,b,f[N][N],sz[N],ans;
LL qow(LL x,LL y){return y?(y&1?x*qow(x,y-1)%MOD:qow(x*x%MOD,y/2)):1;}
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	sz[n-1]=1;
	f[1][1]=qow(2,MOD-2);
	for(int i=n-2;i>=0;i--)sz[i]=(2ll*sz[i+1]+1)%MOD;
	for(int s=2;s<2*n-2;s++)
	for(int i=1;i<n-1;i++){
		int j=s-i;
		if(j<1 || j>n-1)continue;
		int p=1ll*sz[i+1]*qow(sz[i+1]+sz[j],MOD-2)%MOD;
		f[i+1][j]=(f[i+1][j]+1ll*p*f[i][j])%MOD;
		p=(MOD+1-p)%MOD;
		f[j][i+1]=(f[j][i+1]+1ll*p*f[i][j])%MOD;
	}
	for(int i=1;i<=b;i++)ans=(ans+f[a][i])%MOD;
	printf("%d\n",ans);
}
```

计算概率时显然逆元是可以预处理的，不过时限充裕就懒得优化了（。

加上这一优化时间复杂度可以做到 $O(n^2)$。

---

## 作者：by_chance (赞：14)

[Link](https://www.luogu.com.cn/problem/AT_agc060_c)

简要题意：称一个长为 $2^n-1$ 的排列 $P$ **像堆**，如果 $P_i \lt P_{2i}$,且 $P_i \lt P_{2i+1}$。给定 $a,b$,设 $u=2^a,v=2^{b+1}-1$，在所有**像堆**的排列中任取一个，求 $P_u \lt P_v$ 的概率。

既然这个排列像堆，那就把这个问题放在满二叉树上解决。结点 $i$ 的权值是 $P_i$，子结点是 $2i$ 和 $2i+1$。

首先，如果把结点编号，然后按照权值排列，那么就是对这棵满二叉树做了一次拓扑排序，这里父结点向子结点连有向边。那么，我们只需要考虑结点的一个排列 $S$，使得 $i$ 在其子树的前面。

题目中给定的 $u,v$ 分别是第 $a+1$ 层最左边的结点和第 $b+1$ 层最右边的结点。而题目要求的 $P_u \lt P_v$ 可以看作是从 $u$ 向 $v$ 连了一条有向边，或者说 $S$ 中 $u$ 必须在 $v$ 前面。（下面的叙述中，涉及树的概念都是没有考虑这条边的）

这个拓扑序的开头当然是 $1$，然后整个图被分成了两棵满二叉树，从一棵的某个点向另一棵的某个点连边。

接下来，当然是选择一棵树的根结点。然后，这棵树又被分成了两棵树，其中有一棵是不含 $u,v$ 之一的。那么，在安排好剩下的两棵树之后，将这棵树随意插入已有的排列即可。

想到这里，一个 DP 的方式呼之欲出：设 $dp_{i,j}$ 表示剩下一棵 $i$ 层的满二叉树和一棵 $j$ 层的满二叉树的方案数，则 $dp_{i,j}$ 会从 $dp_{i-1,j}$ 和 $dp_{i,j-1}$ 转移而来。注意，由于 $u,v$ 距离叶子层的深度是不变的，所以这样的状态定义已经足够。再用 $f_{i,j}$ 表示相应的概率。

我们还需要考虑一个普通的 $i$ 层满二叉树的拓扑序总数。设为 $S_i$。

先求 $S_i$ 的递推式。第一步是选择根结点，然后是将两棵子树的所有排列方式放入拓扑序中。所有排列有 $S_{i-1}^2$ 种。每棵子树的拓扑序长度为 $2^{i-1}-1$，所以插入的方式有 $C_{2^i-2}^{2^{i-1}-1}$ 种。于是

$$S_i=S_{i-1}^2 \times C_{2^i-2}^{2^{i-1}-1}$$

设 $u,v$ 分别在倒数第 $A,B$ 层，则 DP 的初始值为 $f_{A-1,j}=1$ 对 $j \ge B$ 成立。

与前面类似可得 $dp_{i,j}$ 的递推式为：

$$dp_{i,j}=dp_{i-1,j} \times S_{i-1} \times C_{2^i+2^j-3}^{2^{i-1}-1}+dp_{i,j-1} \times S_{j-1} \times C_{2^i+2^j-3}^{2^{j-1}-1}$$

又由于

$$f_{i,j}=\frac{dp_{i,j}}{S_i \times S_j \times C_{2^i+2^j-2}^{2^i-1}}$$

所以

$$f_{i,j}=\frac{dp_{i-1,j} \times S_{i-1} \times C_{2^i+2^j-3}^{2^{i-1}-1}+dp_{i,j-1} \times S_{j-1} \times C_{2^i+2^j-3}^{2^{j-1}-1}}{S_i \times S_j \times C_{2^i+2^j-2}^{2^i-1}}$$

$$=\frac{f_{i-1,j} \times S_{i-1}^2 \times S_j \times C_{2^{i-1}+2^j-2}^{2^{i-1}-1} \times C_{2^i+2^j-3}^{2^{i-1}-1}}{S_i \times S_j \times C_{2^i+2^j-2}^{2^i-1}}+$$

$$\frac{f_{i,j-1} \times S_{j-1}^2 \times S_i \times C_{2^i+2^{j-1}-2}^{2^{j-1}-1} \times C_{2^i+2^j-3}^{2^{j-1}-1}}{S_i \times S_j \times C_{2^i+2^j-2}^{2^j-1}}$$

$$=f_{i-1,j} \times \frac{C_{2^{i-1}+2^j-2}^{2^{i-1}-1} \times C_{2^i+2^j-3}^{2^{i-1}-1}}{C_{2^i-2}^{2^{i-1}-1} \times C_{2^i+2^j-2}^{2^i-1}}+$$

$$f_{i,j-1} \times \frac{C_{2^i+2^{j-1}-2}^{2^{j-1}-1} \times C_{2^i+2^j-3}^{2^{j-1}-1}}{C_{2^j-2}^{2^{j-1}-1} \times C_{2^i+2^j-2}^{2^j-1}}$$

结合

$$\frac{C_{2^{i-1}+2^j-2}^{2^{i-1}-1} \times C_{2^i+2^j-3}^{2^{i-1}-1}}{C_{2^i-2}^{2^{i-1}-1} \times C_{2^i+2^j-2}^{2^i-1}}$$

$$=\frac{\frac{(2^{i-1}+2^j-2)!\times(2^i+2^j-3)!}{(2^{i-1}-1)!\times(2^j-1)!\times(2^{i-1}-1)!\times(2^{i-1}+2^j-2)!}}{\frac{(2^i-2)!\times(2^i+2^j-2)!}{(2^{i-1}-1)!\times(2^{i-1}-1)!\times(2^i-1)!\times(2^j-1)!}}$$

$$=\frac{(2^i+2^j-3)!\times(2^i-1)!}{(2^i+2^j-2)!\times(2^i-2)!}$$

$$=\frac{2^i-1}{2^i+2^j-2}$$

最后我们得到了一个漂亮的表达式：

$$f_{i,j}=f_{i-1,j}\times\frac{2^i-1}{2^i+2^j-2}+f_{i,j-1}\times\frac{2^j-1}{2^i+2^j-2}$$

答案是 $f_{n-1,n-1}$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005,mod=998244353;
int n,A,B;
long long pwr2[N],p[N][N],f[N][N];
int power(int a,int b){
	int c=1;
	for(;b;b>>=1){
		if(b&1)c=1ll*c*a%mod;
		a=1ll*a*a%mod;
	}
	return c;
}
int main(){
	scanf("%d%d%d",&n,&A,&B);
	A=n-A;B=n-B;
	for(int i=1;i<=n;i++)pwr2[i]=power(2,i); 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			p[i][j]=(pwr2[i]-1)*power(pwr2[i]+pwr2[j]-2,mod-2)%mod;
	for(int i=B;i<=n;i++)f[A-1][i]=1;
	for(int i=A;i<=n;i++)
		for(int j=B;j<=n;j++)
			f[i][j]=(f[i-1][j]*p[i][j]%mod+f[i][j-1]*p[j][i]%mod)%mod;
	printf("%d\n",f[n-1][n-1]);
	return 0;
}
```

---

## 作者：红黑树 (赞：6)

[可能更好的阅读体验](https://rbtr.ee/agc-060-c)

## [题意](https://atcoder.jp/contests/agc060/tasks/agc060_c)
对于一个排列 $P$，若对于任意 $i \in \left[1, 2^{N - 1} - 1\right]$，都满足 $P_i < \min\left\{P_{2i}, P_{2i + 1}\right\}$，则我们认为 $P$ 是 **heaplike** 的。

给定 $N$，我们等概率随机一个 $1$ 到 $2^N - 1$ 的 **heaplike** 排列 $P$。

给定 $A$ 和 $B$，令 $U = 2^A, V = 2^{B + 1} - 1$。问 $P_U < P_V$ 的概率。

答案对 $998244353$ 取模。

$1 \leq A, B < N \leq 5000$

## 题解
我们发现 $U$ 是从根一直向左儿子走 $A$ 步到达的点，$V$ 则是从根一直往右儿子走 $B$ 不到达的点。因此我们只需要观察这两条链即可。

考虑从小到大在这两条链上加数，DP 算概率。

$f_{i, j}$ 和 $g_{i, j}$ 分别表示 $U$ 所在链已经有了 $i$ 个数，$V$ 所在链已经有了 $j$ 个数，最后一次加在 左边 或 右边 的概率。

当前这个数加在左右两边的概率就取决于他们的相对大小，具体来说，加在左边的概率为 $\dfrac{\mathsf{Size}_{i + 1}}{\mathsf{Size}_{i + 1} + \mathsf{Size}_{j + 1}}$，加在右边的同理。

于是就有转移方程：

$$f_{i + 1, j} = \left(f_{i, j} + g_{i, j}\right) \cdot \frac{\mathsf{Size}_{i + 1}}{\mathsf{Size}_{i + 1} + \mathsf{Size}_{j + 1}}$$

$$g_{i + 1, j} = \left(f_{i, j} + g_{i, j}\right) \cdot \frac{\mathsf{Size}_{j + 1}}{\mathsf{Size}_{i + 1} + \mathsf{Size}_{j + 1}}$$

其中 $\mathsf{Size}_i$ 为第 $i$ 个加入数时的树大小。

最终答案就是 $\sum\limits_{i = 1}^{B - 1}f_{A, i}$。

复杂度是 $\mathcal O\left(AB\right)$ 的。如果在循环里算逆元的话会多一个对数。

## 代码
```cpp
// :/

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  constexpr tp mod = 998244353;
  tp n, a, b; bin >> n >> a >> b;
  vector f(a + 2, vector<tp>(b + 1, 0));  // left
  vector g = f;                           // right
  vector<tp> pw2(n + 1, 1);
  gor(i, 1, n) pw2[i] = pw2[i - 1] * 2 % mod;
  f[0][0] = 1;
  gor(i, 0, a) {
    dor(j, 0, b) {
      tp x = (pw2[n - i - 1] + mod - 1) % mod;
      tp y = (pw2[n - j - 1] + mod - 1) % mod;
      tp inv = RCAL::inverse(x + y, mod);
      f[i + 1][j] = (f[i][j] + g[i][j]) * x % mod * inv % mod;
      g[i][j + 1] = (f[i][j] + g[i][j]) * y % mod * inv % mod;
    }
  }
  bin << accumulate(&f[a][0], &f[a][b], ZERO) % mod << '\n';
  return 0;
}

void MIST() {
}

// :\ */
```

---

## 作者：Purslane (赞：3)

# Solution

前置问题：给定一个 $n$ 个节点的有根树，问随机一个 $n$ 阶排列，使得每个点的权值都比他儿子小的概率。

显然，每个子树的相对大小关系是独立的，因此答案是 $\prod \dfrac{1}{sze_u}$，$sze_u$ 为树上 $u$ 子树的大小。

本题中，考虑到 $U$ 和 $V$ 的 $\rm LCA$ 恰好为 $1$，因此我们考虑把整棵树划分成两条链：极左和极右。我们使用 $\rm DP$ 钦定这两条链上的点的相对大小关系（有点像拓扑排序。。。）

那么这时候我们就可以把这棵树重新整理一下：主干上只有极左和极右的点，剩下的子树挂在主干上。

我们设最上面的点是第一层，目前已经处理了左链的前 $i$ 个节点和右链的前 $j$ 个节点目前已经有的概率。

假设我们要把 $i+1$ 放到新的拓扑序列里，那么原来子树大小是 $2^{n-i} -1$，现在就是 $2^{n-i} + 2^{n-j} - 2$，因此乘上 $\dfrac{2^{n-i}-1}{2^{n-i} + 2^{n-j} - 2}$。

线性预处理逆元，删掉不合法（$P_U > P_V$）的情况，可以做到 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5000+10,MOD=998244353;
int tval=1,n,u,v,pw[MAXN],dp[MAXN][MAXN],inv[MAXN][MAXN];
int qpow(int base,int p) {
	int ans=1; base%=MOD;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>u>>v,u++,v++;
	pw[0]=1; ffor(i,1,n) pw[i]=pw[i-1]*2%MOD;
	dp[1][1]=1; int mul=1;
	ffor(i,1,n) ffor(j,1,n) if(i!=n||j!=n) mul=mul*((pw[n-i]-1+pw[n-j]-1)%MOD)%MOD;
	mul=qpow(mul,MOD-2);
	ffor(i,1,n) ffor(j,1,n) if(i!=n||j!=n) inv[i][j]=mul,mul=mul*((pw[n-i]-1+pw[n-j]-1)%MOD)%MOD;
	mul=1;
	roff(i,n,1) roff(j,n,1) if(i!=n||j!=n) inv[i][j]=inv[i][j]*mul%MOD,mul=mul*((pw[n-i]-1+pw[n-j]-1)%MOD)%MOD;
	inv[n][n]=0;
	ffor(i,1,n) ffor(j,1,n) {
		if(j>=v&&i<u) dp[i][j]=0;
		dp[i+1][j]=(dp[i+1][j]+dp[i][j]*(pw[n-i]-1)%MOD*inv[i][j])%MOD;
		dp[i][j+1]=(dp[i][j+1]+dp[i][j]*(pw[n-j]-1)%MOD*inv[i][j])%MOD;
	}
	cout<<dp[n][n];
	return 0;
}
```

---

## 作者：GGapa (赞：2)

题解都看不懂，只能自己来写了 qaq，[参考博客](https://www.cnblogs.com/cjjsb/p/17006984.html) 图也是偷来的。

-------

考虑到题目中给定 $U$ 和 $V$ 到 $1$ 号节点的路径，分别是最左侧的链和最右侧的链。

考虑从小到大依次加入节点，若先将 $U$ 加入，则说明 $P_U < P_V$ 反之亦然。

考虑当前所在的节点分别为 $a$ 和 $b$，当且仅当新加的节点是在 $a$ 的左子树或 $b$ 的右子树中才是有意义的。

如下图所示，只有白色的节点会影响到答案。

![原图地址 https://img2023.cnblogs.com/blog/1251070/202212/1251070-20221229213901129-1419394450.png](https://s21.ax1x.com/2024/08/21/pAiYffK.png)

定义 $f(a, b)$ 代表两边分别走到 $a$ 和 $b$ 时 $P_U < P_V$ 的概率，显然有 $F(U, b) = 1$，$F(a, V) = 0$，转移方程如下：

$$F(a, b) = F(a + 1, b) \times \frac{siz_a - 1}{siz_a + siz_b - 2} + F(a, b + 1) \times \frac{siz_b - 1}{siz_a + siz_b - 2}$$ 

其中 $siz_i$  代表深度为 $i$ 的节点的子树的大小。注意到 $siz_a - 1 = siz_{a + 1} \times 2$  而 $\times 2$ 会约掉，故可以直接使用 $siz_a - 1$ 计算。

时间复杂度可以做到 $O(n ^ 2)$ 但是代码是用 $O(n ^ 2 \log n)$ 写的。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
#define int long long
using namespace std;
using LL = long long;
using VI = vector<int>;
const int mod = 998244353, N = 5000 + 5;


LL qpow(LL x, LL y){
    LL ret = 1;
    for(; y; y >>= 1) {
        if(y & 1) (ret = ret * x) %= mod;
        (x = x * x) %= mod;
    }
    return ret;
}

LL inv(int x) {return qpow(x, mod - 2);} 

int n, A, B; 
LL F[N][N], si[N];

LL dfs(int i, int j) {
	auto &f = F[i][j];
	if(f != -1) return f;
	if(i == A) return 1; if(j == B) return 0;
	LL s = (si[i + 1] + si[j + 1]) % mod;
	s = inv(s);
	return f = (si[i + 1] * s % mod * dfs(i + 1, j) % mod + si[j + 1] * s % mod * dfs(i, j + 1) % mod) % mod;
} 


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
	cin >> n >> A >> B;
	memset(F, -1, sizeof(F)) ;
	si[n - 1] = 2;
	per(i, n - 2, 0) si[i] = si[i + 1] * 2ll % mod, si[i + 1] = (si[i + 1] - 1 + mod) % mod;
	cout << dfs(0, 0) << '\n'; 
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc060_c)

**题目大意**

> 给定 $n$，随机生成一个深度为 $n$ 的小根堆，权值为 $1\sim 2^n-1$ 的排列。
>
> 求第 $a$ 层最左边节点 $u$ 值小于第 $b$ 层最右边节点的值 $v$ 的概率。
>
> 数据范围：$n\le 5000$。

**思路分析**

先考虑有多少个深度为 $n$ 的小根堆，最小值显然在根上，然后只要把 $2^n-2$ 个数均分到左右子树里，有递推关系：
$$
f_n=f^2_{n-1}\binom{2^n-2}{2^{n-1}-1}
$$
考虑如何用类似的过程解决原本的问题：我们把 $u,v$ 到根的路径分别取出来，并设两个指针 $x=u,y=v$，我们只需要维护 $V=\mathrm{subtree}(x)\cup\mathrm{subtree}(y)$ 之内的大小关系。

每次我们取出 $fa(x),fa(y)$ 中较大的一个（不妨设是 $x$），然后把 $x$ 的兄弟的值域和 $V$ 的值域合并一下即可。

那么考虑用 dp 维护这个过程，$dp_{i,j}$ 表示当前 $x$ 子树深度为 $i$，$y$ 子树深度为 $j$ 的合法概率，对应的方案数 $F_{i,j}=dp_{i,j}\times f_i\times f_j\times \binom{2^i+2^j-2}{2^i-1}$。

转移时枚举上一步加入的是 $x$ 还是 $y$，然后把新的子树和原本值域合并一下：
$$
F_{i,j}=F_{i-1,j}\times\binom{2^i+2^j-3}{2^{i-1}-1}\times f_{i-1}+F_{i,j-1}\times\binom{2^i+2^j-3}{2^{j-1}-1}
$$
展开所有组合数并化简可以得到：
$$
dp_{i,j}=dp_{i-1,j}\times \dfrac{2^i-1}{2^i+2^j-2}+dp_{i,j-1}\times\dfrac{2^j-1}{2^i+2^j-2}
$$
边界条件 $dp_{n-a-1,\ge n-b}=1$，转移之前 $\mathcal O(n^2)$ 预处理所有逆元即可。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5005,MOD=998244353;
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
ll dp[MAXN][MAXN],pw[MAXN],w[MAXN][MAXN],g[MAXN][MAXN];
signed main() {
	int n,A,B;
	scanf("%d%d%d",&n,&A,&B),A=n-A,B=n-B;
	for(int i=pw[0]=1;i<n;++i) pw[i]=pw[i-1]*2%MOD;
	ll P=1;
	for(int i=1;i<n;++i) for(int j=1;j<n;++j) {
		g[i][j]=P,w[i][j]=(pw[i]+pw[j]-2)%MOD,P=P*w[i][j]%MOD;
	}
	P=ksm(P);
	for(int i=n-1;i;--i) for(int j=n-1;j;--j) {
		g[i][j]=g[i][j]*P%MOD,P=P*w[i][j]%MOD;
	}
	for(int i=B;i<n;++i) dp[A-1][i]=1;
	for(int i=A;i<n;++i) for(int j=B;j<n;++j) {
		dp[i][j]=(dp[i-1][j]*(pw[i]-1)+dp[i][j-1]*(pw[j]-1))%MOD*g[i][j]%MOD;
	}
	printf("%lld\n",dp[n-1][n-1]);
	return 0;
}
```

---

## 作者：2008verser (赞：0)

第一步，切换为等价限制：每个点都是子树中最小值。

从上到下想，每个点的限制独立，概率为 $\frac{1}{sz}$。方案数可以被计算为 $\dfrac{(2^n-1)!}{\prod sz}$。

当限制多了一条以后，各个限制不再独立。尝试去除一个限制使其余的独立。

但不存在去除方案使得去除后的限制和原限制等价。我们只好先去除，再在此基础上修补计数内容。

如图，红色是限制（形成一颗树，两两独立），蓝色边（它本来指向下）是我们忽视的限制。求出满足红色的以后，立刻发现，多数的部分是（在满足红色条件下）同时满足蓝色（指向上）的部分。

于是转化为了另一个等价的问题。**不断迭代，直到碰见根。**

具体地，我们用第二张图的答案减去第三张图的答案，结果发现多减的部分是第四张图，于是加上第四张，发现多加的部分是第五张，于是减去第五……直到最后一次你发现没有多减/加。

![](https://cdn.luogu.com.cn/upload/image_hosting/i0ypj9lq.png)

迭代次数是 $V$ 的深度，每次影响两根链上共 $O(n)$ 个点的 $sz$。我写了个 $O(n^2\log mod)$ 直接过了。

**启示：计数等于总量乘以概率。**

[AC 链接](https://atcoder.jp/contests/agc060/submissions/me)

---

## 作者：int08 (赞：0)

## 前言
vp 时候半小时切了，开心 <(＾－＾)>。
# Solution

题目说一个排列像堆，我们干脆就放到堆（这里是满二叉树）上来研究。

发现这个堆和平时使用的堆节点标号方式是相同的，也就是满足节点小于两个儿子节点，$u$ 位于 $a+1$ 层第一个，$v$ 位于 $b+1$ 层最后一个。

但是它是一个排列，如果我们按数字从小到大一个一个将树上的点涂黑，一个点必然会在它父节点涂黑之后再涂黑，这是一个**拓扑序**，原问题也就等价于计算 $u$ 拓扑序小于 $v$ 的概率。

现在感觉简单多了，显然到 $u$ 要走 $a$ 步，到 $v$ 走 $b$ 步，而且路径完全不交（因为点一左一右）。

设 $dp_{i,j}$ 表示左侧走了 $i$ 步，右侧走了 $j$ 步的概率，初始化形如 $dp_{0,0}=1$，转移形如 $dp_{i,j}$ 到 $dp_{i+1,j}$ 或者 $dp_{i,j+1}$。

问题来了，转移系数是多少？

这里计算转移到 $dp_{i+1,j}$ 的概率：设往两个方向走的子树大小分别为 $x=2^{n-1-i}-1,y=2^{n-1-j}-1$，由于两棵子树互不干扰，可以分别求出拓扑序之后归并起来，则 $x$ 子树先走的概率就是 $\frac{x}{x+y}$，可以感性理解，也可以组合数证明。

可以预处理逆元做到 $O(n^2)$，不过我懒。
## AC Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
int n,a,b,p2m1[5080];
int qp(int x,int y)
{
	int ans=1;
	for(int i=1,j=x;i<=y;i*=2,j=j*j%mod) if(i&y) ans=ans*j%mod;
	return ans;
}
int dp[5080][5080];
signed main()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++) p2m1[i]=(p2m1[i-1]*2+1)%mod;
	dp[0][0]=1;
	int ans=0;
	for(int sm=0;sm<a+b-1;sm++)
		for(int i=0;i<=sm;i++)
		{
			int j=sm-i;
			if(i>n-1||j>n-1) continue;
			int is=p2m1[n-i-1],js=p2m1[n-j-1];
			(dp[i+1][j]+=dp[i][j]*is%mod*qp((is+js)%mod,mod-2))%=mod;
			if(i+1==a&&j<b) (ans+=dp[i][j]*is%mod*qp((is+js)%mod,mod-2))%=mod;
			(dp[i][j+1]+=dp[i][j]*js%mod*qp((is+js)%mod,mod-2))%=mod;
		}
	cout<<ans;
	return 0;
 } 
```
# The End.

---

## 作者：Phartial (赞：0)

首先不难发现如果一个排列像堆，则其逆排列即为 $n$ 层满二叉树的一种拓扑序。于是题目转化为计数 $n$ 层满二叉树的拓扑序数量，以及其中满足第 $A$ 层的最左点在拓扑序中小于第 $B$ 层的最右点（为方便，令根在第 $0$ 层）的拓扑序数量。

对于第一问，考虑设 $f_n$ 为 $n$ 层满二叉树的拓扑序数量，显然其第一位必然是根节点。假设我们确定了根节点的左右子树的拓扑序，那么通过归并成一个拓扑序并在开头插入根节点，我们就可以唯一确定这棵树的一种拓扑序。具体的，我们有递推关系：$\displaystyle f_n=f_{n-1}^2{2^n-2\choose2^{n-1}-1}$，且 $f_1=1$。

> 事实上我们可以得到更一般且更优美的结果：对于任意树，设 $f_x$ 为以 $x$ 为根的子树的拓扑序数量，有递推关系 $\displaystyle f_x={\mathrm{size}_x-1\choose\mathrm{size}_{\mathrm{son}_{x,1}},\mathrm{size}_{\mathrm{son}_{x,2}},\cdots}\prod_{i\in \mathrm{son}_x}f_i$，且在叶子节点处有 $f_{x}=1$。
> 
> 直接展开递推式可以发现父亲节点处的 $\frac{1}{\mathrm{size}_{\mathrm{son}_{x,i}}!}$ 会被儿子节点处的 $(\mathrm{size}_{\mathrm{son}_{x,i}}-1)!$ 所抵消成 $\frac{1}{\mathrm{size}_{\mathrm{son}_{x,i}}}$。于是对于非根节点，总是造成 $\frac{1}{\mathrm{size}_x}$ 的贡献，而根节点则造成 $(n-1)!=\frac{n!}{\mathrm{size}_1}$ 的贡献（此处 $n$ 为树大小），于是总方案数为 $\displaystyle n!\prod_{x}\frac{1}{\mathrm{size}_x}$。

对于第二问，不妨令 $S$ 为第 $A$ 层的最左点，$T$ 为第 $B$ 层的最右点。由于 $S$ 和 $T$ 的拓扑序只和它们的祖先有关。我们先只关心 $S$ 的祖先和 $T$ 的祖先之间的拓扑关系，之后将其他子树的拓扑序插入其中。

感性理解一下，这相当于把 $S$ 到根的链和 $T$ 到根的链归并成一条链并保留子树关系，形成一棵新的树（这一步相当于钦定 $S$ 的祖先和 $T$ 的祖先的拓扑关系），然后对这棵新的树计算拓扑序方案数。

记 $\operatorname{anc}(x,k)$ 为 $x$ 位于第 $k$ 层的祖先。考虑设 $f_{i,j}$ 表示现在已经钦定到了 $\operatorname{anc}(S,i)$ 和 $\operatorname{anc}(T,j)$ 之间的拓扑关系时所有可能方案的 $\prod_{x}\frac{1}{\mathrm{size}_x}$ 之和（这里的 $x$ 只算已考虑的节点，即 $S$ 的前 $i$ 层的祖先和 $T$ 的前 $j$ 层的祖先，以及这些点在原树中的其他子树）。考虑两种转移：

- $f_{i,j}\to f_{i+1,j}$：此时相当于钦定 $\operatorname{anc}(S,i+1)$ 在拓扑序中比 $\operatorname{anc}(T,j+1)$ 更靠前，计算出原树中以 $\operatorname{anc}(S,i+1)$ 为根的子树里的所有其他节点的子树大小，并重新计算 $\operatorname{anc}(S,i+1)$ 的子树大小（为原先的子树大小加上还未处理的节点个数）后贡献进答案即可；
- $f_{i,j}\to f_{i,j+1}$：同理。

最后钦定 $S$ 和 $T$ 的拓扑序关系时只能保留 $S$ 在 $T$ 之前的转移，同时需要特殊处理一下边界情况。

时间复杂度 $\mathcal{O}(n^2)$。代码相当屎。

```cpp
#include <atcoder/modint>
#include <iostream>

using namespace std;
using LL = atcoder::modint998244353;

const int kN = 5001;

int n, a, b;
LL p2[kN], f[kN][kN], g[kN], ans;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> a >> b;
  p2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    p2[i] = p2[i - 1] * 2;
  }
  g[1] = 1;
  for (int i = 1; i < n; ++i) {
    g[i + 1] = g[i] * g[i] / (p2[i + 1] - 1);
  }
  f[0][0] = 1 / (p2[n] - 1);
  for (int i = 0; i <= a; ++i) {
    for (int j = 0; j < b; ++j) {
      if (i == a && j == b - 1) {
        cout << (f[a][j] * g[n - b] / g[n]).val();
        return 0;
      }
      if (i < a - 1) {
        f[i + 1][j] += f[i][j] * g[n - i - 2] / (p2[n - i - 1] + p2[n - j - 1] - 2);
      } else if (i == a - 1) {
        f[a][j] += f[i][j] * g[n - a] * (p2[n - a] - 1) / (p2[n - a] + p2[n - j - 1] - 2);
      }
      if (j < b - 1) {
        if (i == a) {
          f[i][j + 1] += f[i][j] * g[n - j - 2] / (p2[n - j - 1] - 1);
        } else {
          f[i][j + 1] += f[i][j] * g[n - j - 2] / (p2[n - i - 1] + p2[n - j - 1] - 2);
        }
      }
    }
  }
  return 0;
}
```


---

