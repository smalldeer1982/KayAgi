# [AGC056F] Degree Sequence in DFS Order

## 题目描述

已知整数 $N,M$， 求有多少个整数序列 $a=(a_1,a_2,\cdots,a_N)$ 可以由以下方式生成，答案对 $998244353$ 取模。

- 选择一个 $N$ 个点，$M$ 条边的无向连通图 $G$，要求无自环，但可以有重边。
- 进行 DFS，令 $a_i$ 表示遍历到的第 $i$ 个点的度数，具体的，执行以下代码：

```
a = empty array

dfs(v):
    visited[v]=True
    a.append(degree[v])
    for u in g[v]:
        if not visited[u]:
            dfs(u)

dfs(arbitrary root)
```

这里，$g$ 是图 $G$ 的邻接表，$g[v]$ 是任意顺序的与 $v$ 相连的顶点列表。

举个例子，对于 $N=4,M=5$，一个可能的 $a=(2,4,1,3)$，图 $G$ 如下图所示：

![G](https://img.atcoder.jp/agc056/3bfec17f881ae4cd27eccae94ebeae10.png)

顶点上的数字表示访问他们的顺序，橙色箭头表示遍历时经过的边。

## 说明/提示

- $2\le N\le M\le 10^6$。

## 样例 #1

### 输入

```
2 2```

### 输出

```
1```

## 样例 #2

### 输入

```
3 4```

### 输出

```
9```

## 样例 #3

### 输入

```
10 20```

### 输出

```
186225754```

## 样例 #4

### 输入

```
100000 1000000```

### 输出

```
191021899```

# 题解

## 作者：jun头吉吉 (赞：8)

## 题意
给定 $N,M$ 问选择一个 $N$ 个点 $M$ 条边的无向图，无自环，可以有重边，如下伪代码能生成多少种数组：

```cpp
a = empty array

dfs(v):
    visited[v]=True
    a.append(degree[v])
    for u in g[v]:
        if not visited[u]:
            dfs(u)

dfs(arbitrary root)
```

对 $998244353$ 取模。

$2\le N\le M\le 10^6$。

## 题解


不妨强制 dfs 序就是 $1,2,\dots,N$，然后问能生成多少度数序列。

如果一张无向图的 dfs 序为 $1,2,\dots,N$，一个必要条件是对于 $u>1$，存在边 $(u,v)$ 使得 $v<u$。

但是这个有问题啊。你跑 dfs 的时候必须要跑到底，有可能你还要往下走但是 $u+1$ 就寄了。

但是一个很高妙的结论是如果 $a<b<c<d$，有边 $(a,c),(b,d)$，我们可以变成边 $(a,d),(b,c)$ 并且没有改变度数，也没有改变图是否满足必要条件。这个肯定可以在有限步内结束因为 $\sum_{(u,v)\in E}(u-v)^2$ 是递增的。

我们把满足必要条件的图按照结论不停操作。然后如果已经走过 $1\sim u$。根据 dfs 的原理，假设 $u+1$ 连接的是 $v$，那么从 $u$ 一直往上跳到 $v$，如果只有 $v$ 有未遍历过的出点那么就是合法的。否则有一个点 $a$ 连出了 $b$，因为 $a$ 在 $u\sim v$ 之间所以 $v<a<u+1<b$，然后 $(v,u+1),(a,b)$ 有边与不能操作矛盾。也就是一定能够是 $1,2,\dots,N$。

然后就相当于满足必要条件的图能够生成多少种度数序列 $\{a_i\}$。有三个必要条件：

- $\sum_{i=1}^Na_i=2M$。因为一共有 $M$ 条边每条边提供 $2$ 的度数。
- $\sum_{i=1}^ua_i\ge2(u-1)+1$。内部至少有 $u-1$ 条边，然后 $u+1$ 还要连一条边。
- $a_{u+1}\le M-(u-1)$。前 $u$ 个点内部至少有 $u-1$ 条边，因此最多只有 $M-(u-1)$。

这个应该也是充分的。考虑一个算法：

枚举 $i=2\sim N$，从前面选一个度数最大的点连边。由于第二个条件满足所以一定是可以做的。

然后如果之后不存在 $a_x'>M-(N-1)$，那么肯定可以构造一种合法连边方案。接下来证明不会有这种情况。

显然最多只有一个 $a'_x>M-(N-1)$，不存在其他 $a'_y\ge M-(N-1)$。然后因为 $a_x\le M-(x-2)$，在前面的算法中，如果有一次 $i>x$ 且 $i$ 向 $y$ 连边，那么最后 $a_y'\ge a_x'-1$。前面已经说明了这种情况不存在，所以后 $N-x+1$ 条边都是连向 $x$ 的。

那么 $a_x'=a_x-(N-x+1)\le M-(N-1)$。那就矛盾了啊。所以是一定合法的。

现在的形式已经很简单了，可以有 $\mathcal O(\mathrm{poly}(N,M))$ 的算法。

为了方便不妨设假设我们有数组 $\{b_i\}$， $b_0=a_1,b_i=a_{i+1}-1$，那么三条限制就是：

- $\sum _{i=0}^{N-1}b_i=2M-(N-1)$
- $\sum_{i=0}^{u-1}b_i\ge u$
- $b_u\le M-u$

把这个看做 $(0,0)$ 出发，向上走 $b_0$，向右走 $1$，向上走 $b_1$，向右走 $1$，……，向上走 $b_{N-1}$，到达 $(N-1,2M-(N-1))$。

然后第二条限制就是不能碰到 $y=x-1$。如果不考虑第三条限制那么就是经典的卡特兰数求法，到终点的方案数减去到终点关于线对称点的方案数。也就是 $\binom{2M}{N-1}-\binom{2M}{N-2}$。

接下来说明至多只有一个 $b_K$ 使得 $b_K>M-K$。

设 $p<q$，$b_p\ge M-p+1,b_q\ge M-q+1$，限制二说明 $\sum _{i=0}^{p-1}b_i\ge p$。

所以 $\sum_{i=0}^{N-1}b_i\ge \sum_{i=0}^{p-1}b_i+b_p+b_q\ge 2M-q+2>2M-(N-1)$。

所以我们可以枚举 $K$，就可以计算出所有不合法的方案数。然后就相当于有一组 $\{c_i\}$，满足 $b_K=c_K+(M-K+1),b_i=c_i$。

现在没有第三条限制了。重写前两条：

- $\sum _{i=0}^{N-1}=M-N+K$
- - $u\le K$，仍然是 $\sum_{i=0}^{u-1}b_i\ge u$
  - $u>K$，那么 $\sum_{i=0}^{u-1}b_i=\sum _{i=0}^{u-1}c_i+M-K+1\ge \sum_{i=0}^{K-1}c_i+M-K+1\ge M+1$，显然一定满足。

那么我们现在的区域就类似下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8cpozsbn.png)

不妨枚举第一次碰到 $y=K$ 的点 $(x,K)$，那么方案数就是 $(0,0)$ 不碰到 $y=x-1$ 走到 $(x,K-1)$ 的方案数乘上 $(x,K)$ 走到 $(N-1,M-N+K)$ 的方案数。注意这里要特判 $K=0$ 时是 $\binom{M-1}{N-1}$。

然后就简单化简一下式子：
$$
\begin{aligned}
&\sum_{K=1}^{N-1}\sum_{x=0}^{K-1}\left(\binom{x+K-1}x-\binom{x+K-1}{x-1}\right)\binom{M-x-1}{M-N}\\
=&\sum_{x=0}^{N-2}\binom{M-x-1}{M-N}\sum_{k=x+1}^{N-1}\binom{x+K-1}x-\binom{x+K-1}{x-1}\\
=&\sum_{x=0}^{N-2}\binom{M-x-1}{M-N}\left(
\left(\binom{x+N-1}{x+1}-\binom{2x}{x+1}\right)-
\left(\binom{x+N-1}{x}-\binom{2x}{x}\right)\right)
\end{aligned}
$$
然后用 $\binom{2M}{N-1}-\binom{2M}{N-2}-\binom{M-1}{N-1}$ 减去这一坨就可以了。

复杂度 $\mathcal O(N+M)$。

## 代码
```cpp
const int N=2e6+10;
int n,m;mint fac[N],ifac[N],ans;
mint C(int n,int m){return m<0||n<m?0:fac[n]*ifac[m]*ifac[n-m];}
signed main(){
	fac[0]=1;for(int i=1;i<N;i++)fac[i]=fac[i-1]*i;
	ifac[N-1]=1/fac[N-1];for(int i=N-1;i;i--)ifac[i-1]=ifac[i]*i;
	read(n,m);ans=C(2*m,n-1)-C(2*m,n-2)-C(m-1,n-1);
	for(int x=0;x<=n-2;x++)ans-=C(m-x-1,m-n)*((C(x+n-1,x+1)-C(2*x,x+1))-(C(x+n-1,x)-C(2*x,x)));
	writeln(ans.x);
}
```

---

