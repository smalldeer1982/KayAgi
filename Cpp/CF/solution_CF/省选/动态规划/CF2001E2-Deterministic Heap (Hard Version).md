# Deterministic Heap (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the two versions is the definition of deterministic max-heap, time limit, and constraints on $ n $ and $ t $ . You can make hacks only if both versions of the problem are solved.

Consider a perfect binary tree with size $ 2^n - 1 $ , with nodes numbered from $ 1 $ to $ 2^n-1 $ and rooted at $ 1 $ . For each vertex $ v $ ( $ 1 \le v \le 2^{n - 1} - 1 $ ), vertex $ 2v $ is its left child and vertex $ 2v + 1 $ is its right child. Each node $ v $ also has a value $ a_v $ assigned to it.

Define the operation $ \mathrm{pop} $ as follows:

1. initialize variable $ v $ as $ 1 $ ;
2. repeat the following process until vertex $ v $ is a leaf (i.e. until $ 2^{n - 1} \le v \le 2^n - 1 $ ); 
  1. among the children of $ v $ , choose the one with the larger value on it and denote such vertex as $ x $ ; if the values on them are equal (i.e. $ a_{2v} = a_{2v + 1} $ ), you can choose any of them;
  2. assign $ a_x $ to $ a_v $ (i.e. $ a_v := a_x $ );
  3. assign $ x $ to $ v $ (i.e. $ v := x $ );
3. assign $ -1 $ to $ a_v $ (i.e. $ a_v := -1 $ ).

Then we say the $ \mathrm{pop} $ operation is deterministic if there is a unique way to do such operation. In other words, $ a_{2v} \neq a_{2v + 1} $ would hold whenever choosing between them.

A binary tree is called a max-heap if for every vertex $ v $ ( $ 1 \le v \le 2^{n - 1} - 1 $ ), both $ a_v \ge a_{2v} $ and $ a_v \ge a_{2v + 1} $ hold.

A max-heap is deterministic if the $ \mathrm{pop} $ operation is deterministic to the heap when we do it for the first and the second time.

Initially, $ a_v := 0 $ for every vertex $ v $ ( $ 1 \le v \le 2^n - 1 $ ), and your goal is to count the number of different deterministic max-heaps produced by applying the following operation $ \mathrm{add} $ exactly $ k $ times:

- Choose an integer $ v $ ( $ 1 \le v \le 2^n - 1 $ ) and, for every vertex $ x $ on the path between $ 1 $ and $ v $ , add $ 1 $ to $ a_x $ .

Two heaps are considered different if there is a node which has different values in the heaps.

Since the answer might be large, print it modulo $ p $ .

## 说明/提示

For the first testcase, if we choose $ v = 1 $ and do the operation, we would have $ a = [1, 0, 0] $ , and since $ a_2 = a_3 $ , we can choose either of them when doing the first $ \mathrm{pop} $ operation, so such heap is not a deterministic max-heap.

And if we choose $ v = 2 $ , we would have $ a = [1, 1, 0] $ , during the first $ \mathrm{pop} $ , the following would happen:

- initialize $ v $ as $ 1 $
- since $ a_{2v} > a_{2v + 1} $ , choose $ 2v $ as $ x $ , then $ x = 2 $
- assign $ a_x $ to $ a_v $ , then $ a = [1, 1, 0] $
- assign $ x $ to $ v $ , then $ v = 2 $
- since $ v $ is a leaf, assign $ -1 $ to $ a_v $ , then $ a = [1, -1, 0] $

And during the second $ \mathrm{pop} $ , the following would happen:

- initialize $ v $ as $ 1 $
- since $ a_{2v} < a_{2v + 1} $ , choose $ 2v + 1 $ as $ x $ , then $ x = 3 $
- assign $ a_x $ to $ a_v $ , then $ a = [0, -1, 0] $
- assign $ x $ to $ v $ , then $ v = 3 $
- since $ v $ is a leaf, assign $ -1 $ to $ a_v $ , then $ a = [0, -1, -1] $

Since both the first and the second $ \mathrm{pop} $ operation are deterministic, this is a deterministic max-heap. Also, if we choose $ v = 3 $ , $ a $ would be a deterministic max-heap, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
6
2 1 998244353
3 2 998244853
3 3 998244353
3 4 100000037
4 2 100000039
4 3 100000037```

### 输出

```
2
12
40
100
32
224```

## 样例 #2

### 输入

```
1
100 500 100000037```

### 输出

```
66681128```

## 样例 #3

### 输入

```
2
87 63 100000037
13 437 100000039```

### 输出

```
83566569
54517140```

# 题解

## 作者：sunkuangzheng (赞：4)

2.5h 才调出来这玩意，无敌了，喜提 $\text{CM} \to \text{E}$。

- 设 $f_{i,j,k},g_{i,j},h_{i,j,k}$ 分别是深度为 $i$，根节点权值为 $j$，（根的较大儿子权值是 $k$） 的**一合法堆**、任意堆、**二合法堆**数量。记 $af_{i,j}$ 表示深度为 $i$，根节点权值为 $j$的**一合法堆**数量，显然有 $af_{i,j} = \sum_k f_{i,j,k}$。
- $g$ 和 $f$ 的转移和 E1 相同。
    - $g$ 的转移显然。稍微注意一下不要算重。
    - $f$ 的转移考虑钦定左子树大于右子树，那么要求左子树是**一合法堆**，右子树任意。即，$f_{i,j + l,j} \gets af_{i-1,j} \cdot g_{i-1,l}$。
- $h$ 的转移考虑两种情况：（以下钦定左子树根 $j$ 大于右子树根）
   - 左子树大儿子 $p$ 小于右子树根 $l$，此时删去左子树后会去删除右子树，因此要求左右都是**一合法堆**，即 $h_{i,j+l,j} \gets f_{i-1,j,p} \cdot af_{i-1,l}$。
   - 左子树大儿子 $l$ 大于右子树根 $p$，此时会连续删左子树，右子树没有限制，因此要求左子树是**二合法堆**，即 $h_{i,j+p,j} \gets h_{i-1,j,l} \cdot g_{i-1,p}$。
- 最后输出 $\sum_p h_{n,k,p}$ 即可。
- 直接暴力实现的复杂度是 $\mathcal O(nk^3)$，前缀和优化后可以做到 $\mathcal O(nk^2)$。空间开不下，需要滚动数组优化。
- 参考代码：

```cpp
/**
 *    author: sunkuangzheng
 *    created: 20.08.2024 22:46:11
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
#define int long long
using ll = long long;
const int N = 2,M = 500+5;
using namespace std;
int T,n,k,f[N][M][M],h[N][M][M],g[N][M],mod,af[N][M],sf[N][M][M],sh[N][M][M];
void los(){
    cin >> n >> k >> mod;
    // for(int i = 1;i <= n;i ++) for(int j = 0;j <= k;j ++) g[t][j] = qp(qp(2,i) - 1,j);
    memset(f,0,sizeof(f)),memset(g,0,sizeof(g)),memset(af,0,sizeof(af)),memset(h,0,sizeof(h)),
    memset(sf,0,sizeof(sf)),memset(sh,0,sizeof(sh));
    for(int i = 0;i <= k;i ++) f[1][i][0] = h[1][i][0] = g[1][i] = af[1][i] = 1;
    auto ad = [&](int &x,int y){x = (x + y) % mod;};
    for(int i = 1;i <= 1;i ++){
        int t = 1;
        for(int j = 0;j <= k;j ++){
            sf[t][j][0] = f[t][j][0]; sh[t][j][k + 1] = h[t][j][k + 1];
            for(int l = 1;l <= k + 1;l ++) ad(sf[t][j][l],f[t][j][l] + sf[t][j][l-1]);
            for(int l = k;l >= 0;l --) ad(sh[t][j][l],sh[t][j][l + 1] + h[t][j][l]);
        }
    }for(int i = 2;i <= n;i ++){
        int t = (i & 1);
        for(int j = 0;j <= k;j ++){
            if(j + j <= k) g[t][j + j] = (g[t][j + j] + g[!t][j] * g[!t][j]) % mod;
            for(int l = 0;l < j;l ++){
                if(j + l <= k) ad(f[t][j + l][j + 1],af[!t][j] * g[!t][l]);
            }
            for(int l = 0;l < j;l ++){
                if(j + l <= k) g[t][j + l] = (g[t][j+l] + 2 * g[!t][j] * g[!t][l]) % mod,
                ad(h[t][j + l][j + 1],af[!t][l] * sf[!t][j][l]);
                // for(int p = -1;p < l;p ++)
                //     if(j + l <= k) ad(h[t][j + l][j + 1],f[!t][j][p + 1] * af[!t][l]);
            }
            // for(int l = -1;l <= j;l ++){
            //     for(int p = 0;p < l;p ++)
            //         if(j + p <= k) ad(h[t][j + p][j + 1],h[!t][j][l + 1] * g[!t][p]);
            // }
            for(int p = 0;p <= j;p ++)
                if(j + p <= k) ad(h[t][j + p][j + 1],g[!t][p] * sh[!t][j][p + 2]);
        }for(int j = 1;j <= k;j ++) {
            for(int l = 0;l <= k + 1;l ++) f[t][j][l] = (f[t][j][l] + f[t][j-1][l]) % mod,
                h[t][j][l] = (h[t][j][l] + h[t][j-1][l]) % mod;
            g[t][j] = (g[t][j] + g[t][j-1]) % mod;
        }
        for(int j = 0;j <= k;j ++){
            for(int l = 0;l <= k + 1;l ++)
                f[t][j][l] = 2ll * f[t][j][l] % mod,ad(h[t][j][l],h[t][j][l]),ad(af[t][j],f[t][j][l]);
            sf[t][j][0] = f[t][j][0]; sh[t][j][k + 1] = h[t][j][k + 1];
            for(int l = 1;l <= k + 1;l ++) ad(sf[t][j][l],f[t][j][l] + sf[t][j][l-1]);
            for(int l = k;l >= 0;l --) ad(sh[t][j][l],sh[t][j][l + 1] + h[t][j][l]);
        }memset(f[!t],0,sizeof(f[!t])),memset(g[!t],0,sizeof(g[!t])),
        memset(af[!t],0,sizeof(af[!t])),memset(h[!t],0,sizeof(h[!t])),
        memset(sf[!t],0,sizeof(sf[!t])),memset(sh[!t],0,sizeof(sh[!t]));
    }cout << sh[n & 1][k][0] << "\n";
}signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

## 作者：_lfxxx_ (赞：2)

### 题意

对于一个大小为 $2^n-1$ 的完全二叉大根堆，我们定义它的 $\operatorname{pop}$ 操作是好的，当且仅当此次操作中任意时刻，我们 $\operatorname{pop}$ 的结点在变成叶子弹出之前左右儿子权值不相等，也就是只有一种将根节点弹出去的方案。

我们将会进行恰好 $k$ 次 $\operatorname{add}$ 操作，其中每次操作你可以选一个结点，然后将根到这个节点的路径上的所有节点加 $1$。

初始我们有一个大小 $2^n-1$ 的完全二叉大根堆，每个结点权值均为 $0$。

问最后会有多少个本质不同的完全二叉大根堆的第一次和第二次 $\operatorname{pop}$ 操作是好的。

对给定质数 $p$ 取模。

$1 \le n \le 100, 1 \le k \le 500$。

------

跟 Easy 版本不一样的地方变成要求两次 $\operatorname{pop}$ 操作都是好的。

考虑把两个一次操作的子树合并成两次操作的子树，那就需要额外开一个 dp 数组。

并且，我们还发现，合并的时候结点权值之间小于要求的限制涉及到一个结点的兄弟和儿子，因此我们的状态还有涉及到权值较大的儿子。

因此，我们设 $f_{i,j}$ 表示 $i$ 层的堆进行 $j$ 次操作有多少种无限制的堆，$g_{i,j,k}$ 表示 $i$ 层的堆进行 $j$ 次操作较大儿子权值为 $k$ 有多少种的堆 $\operatorname{pop}$ 一次是好的，$h_{i,j,k}$  表示 $i$ 层的堆进行 $j$ 次操作较大儿子权值为 $k$ 有多少种的堆 $\operatorname{pop}$ 两次是好的。

接下来只要根据大小关系确定转移的范围然后类似 Easy 版本转移就行了，具体大小限制关系见下图：（$a \to b$ 表示 $a < b$）

![ ](https://mirror.codeforces.com/predownloaded/fd/29/fd29b91221d5315499505646a4c1f6dfb9c008c3.jpg)

前缀和优化即可 $O(nk^2)$。

[提交记录](https://mirror.codeforces.com/contest/2001/submission/278253470)

---

## 作者：xyz105 (赞：1)

$$\begin{Bmatrix}\color{red}\LARGE\bold{Solution}\\\normalsize\texttt{No.013 }\bold{CF2001E2}\end{Bmatrix}\times\footnotesize\texttt{ By Xyz105}$$


### 题目描述

有一棵高为 $n$，点数为 $2^n-1$ 的满二叉树，其中根为 $1$ 号节点，非叶子节点 $i$ 的两个儿子编号为 $2i$ 和 $2i+1$。将这棵树上的所有节点 $i$ 各附上一个权值 $a_i$，使得这棵树是**大根堆**，具体构造方式如下：
- 给定一个常数 $k$。初始令所有 $a_i=0$。执行 $k$ 次操作，每次任选一个点 $x$，将根节点到 $x$ 路径上所有的点权加 $1$。
- 注：此处**大根堆**定义为，对于每个非叶子节点 $i$ 都满足 $a_i \ge \max(a_{2i}, a_{2i+1})$。

定义一次**删除操作**如下：
- 令 $u=1$。设 $u$ 的两个儿子中权值较大的为 $v1$ 节点，较小的为 $v2$ 节点，交换 $u$ 和 $v1$ 两点。若 $u$ 为叶子节点，则删除 $u$ 点，操作终止。特别地，若出现 $v1,v2$ 权值相等的情况，则认为这次删除操作**不确定**。

一个堆是**确定**的，当且仅当对它执行的**两次删除操作**都不是**不确定**的。现有 $t$ 次询问，每次给定 $n,k,p$，求在常数 $k$ 的构造方式下，**确定**的树高为 $n$ 的堆的方案数（对 $p$ 取模）。$(t \le 50$，$n \le 100$，$k \le 500)$


### 解题思路

$n,k$ 范围较小，考虑 DP。

首先，“常数 $k$ 的构造方式”是什么东西呢？我们可以把它转化为：
- 所有节点的权值 $a_i$ 都满足 $\ge 0$。
- 特别地，对于根节点，$a_1=k$；对于非叶子节点 $i$，有 $a_i \ge a_{2i}+a_{2i+1}$。

**Part 01: DP 设计**

目标当然是求出 在 $a_1=k$ 的前提下，满足其余条件的树高为 $n$ 的堆的方案数。也就是说，DP 过程中至少用到两个维度：**树高** 和 **根节点的权值**。

假设进行的 两次删除操作 中，第一次影响到的链为 $1\sim u$，第二次影响到的链为 $1\sim v$（令 $u,v$ 均为叶子节点，当然 $u\neq v$）。那么 $1\sim\text{LCA}(u,v)$ 这条链被影响到**两次**，同时 $\text{LCA}(u,v)\sim u$ 和 $\text{LCA}(u,v)\sim v$ 两条链只被影响到**一次**，其它的链都没受到任何影响。  
这启发了一件事——在设计 DP 时，可以把这棵树被删 $0/1/2$ 次的情况分别计算。

考虑最简单的，也就是这棵树被删 $0$ 次的情况。设 $f0_{n,k}$ 表示 根节点的权值为 $k$ 时，**确定**的树高为 $n$ 的堆的方案数（**没有删除操作**，对 $p$ 取模）。  
不难想到权值只要满足 $a_i \ge a_{2i}+a_{2i+1}$ 这一个条件；于是有
$$f0_{n,k}=\sum_{i+j\le k} f0_{n-1,i}\times f0_{n-1,j}\tag{1}$$

这棵树被删 $2$ 次的情况是最为复杂的。不妨假设当前根节点为 $u$，其左儿子为 $v1$ 节点，右儿子为 $v2$ 节点，令 $a_{v1}>a_{v2}$。分类讨论：
1. 第一次删除操作影响 $v1$ 子树，第二次删除操作影响 $v2$ 子树。  
  那么额外的限制是 $v1$ 的左右两个儿子的权值均小于 $a_{v2}$。因为如果不满足这个限制，那么在第一次删除操作之后，$v1$ 的一个儿子被上调到 $v1$ 处，此时 $a_{v1}\ge a_{v2}$，故第二次删除操作仍不会影响 $v2$ 子树（或者**不确定**）。
2. 两次删除操作都只影响 $v1$ 子树。  
  那么额外的限制是 $v1$ 的左右两个儿子的权值有至少一个大于 $a_{v2}$。因为如果不满足这个限制，那么同理，在第一次删除操作之后会有 $a_{v1}\le a_{v2}$，故第二次删除操作会转而去影响 $v2$ 子树（或者**不确定**）。

所以，被删 $1$ 次的情况还要考虑根节点 **左右儿子都 $\le$ 一个特定的值** 这一维；被删 $2$ 次的情况还要考虑根节点 **左右儿子中权较大者 $\ge$ 一个特定的值** 这一维。

设 $f1_{n,k,k1}$ 表示 被删 $1$ 次、根节点权为 $k$、树高为 $n$、根节点左右儿子都 $\le k1$、**确定**的堆的方案数；  
设 $f2_{n,k,k1}$ 表示 被删 $2$ 次、根节点权为 $k$、树高为 $n$、根节点左右儿子中权较大者 $\ge k1$、**确定**的堆的方案数。  
于是可得：
$$f2_{n,k,k1}=2\times (\sum_{i+j\le k,i>j,i\ge k1}f2_{n-1,i,j+1}\times f0_{n-1,j}+f1_{n-1,i,j-1}\times f1_{n-1,j,j})\tag{3}$$
> 解释：
> - 最前面 $\times 2$ 是因为咱们一直认为 $a_{v1}>a_{v2}$，但 $a_{v1}<a_{v2}$ 也是可能的，方案与前者对称。（$a_{v1}=a_{v2}$ 非法，因为是不确定的）
> - 令 $i=a_{v1},j=a_{v2}$。如果 $v1$ 子树删 $2$ 次，$v2$ 子树删 $0$ 次，那么方案数为 $f2_{n-1,i,j+1}\times f0_{n-1,j}$。注意 $v1$ 左右儿子中权较大者 $\ge j+1$。
> - 如果 $v1,v2$ 子树都删 $1$ 次（$v1$ 子树先被删），那么方案数为 $f1_{n-1,i,j-1}\times f1_{n-1,j,j}$。注意 $v1$ 左右儿子都应 $\le j-1$。

同理可求出 $f1$：
$$f1_{n,k,k1}=2\times (\sum_{i+j\le k,j<i\le k1} f1_{n-1,i,i}\times f0_{n-1,j})\tag{2}$$
这公式就比较好理解了，也就是 $v1$ 子树删 $1$ 次，$v2$ 子树不删。

直接 DP 会 $O(nk^3)$，TLE。

**Part 02: DP 优化**

前缀和优化。对于 $(1)$ 式子，可变为：
$$f0_{n,k}=\sum_{i=0}^k f0_{n-1,i}\times (\sum_{j=0}^{k-i} f0_{n-1,j})$$
枚举时对 $f0_{n-1,j}$ 计算前缀和即可。

对于 $(2)$ 式子，可变为：
$$f1_{n,k,k1}=2\times (\sum_{i=0}^{k1} f1_{n-1,i,i}\times (\sum_{j=0}^{\min\{i-1,k-i\}}f0_{n-1,j}))$$
枚举时对 $f0_{n-1,j}$ 及 所有的 $i$ 的结果 都计算前缀和即可。

$(3)$ 式子最难办。不妨令
$$g1_{n,i,k}=\sum_{j=0}^k f1_{n,i,j-1}\times f1_{n,j,j}\\g2_{n,i,k}=\sum_{j=0}^k f2_{n,i,j+1}\times f0_{n,j}$$
则有
$$f2_{n,k,k1}=2\times (\sum_{i=k1}^k g2_{n-1,i,\min\{i-1,k-i\}}+g1_{n-1,i,\min\{i-1,k-i\}})$$
枚举时对 所有的 $i$ 的结果 都计算前缀和即可。

总时间复杂度降至 $O(nk^2)$。

在代码实现时要注意空间限制，将 $n$ 这一维开成滚动的即可。


### 参考代码

[Submission on Codeforces](https://codeforces.com/contest/2001/submission/287934134)。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

ll f0[2][510], f1[2][510][510], f2[2][510][510];
ll g1[2][510][510], g2[2][510][510];

bool vis[2][510];

int n, k, q; ll p;

inline int div_(int a, int b) {return (a + b - 1) / b;}

inline void get_g(int n1, int i)
{
	ll res1 = 0, res2 = 0;
	for (int j = 0; j < i; j++)
	{
		if (j > 0) res1 = (res1 + f1[n1 & 1][i][j - 1] * f1[n1 & 1][j][j]) % p;
		res2 = (res2 + f2[n1 & 1][i][j + 1] * f0[n1 & 1][j]) % p;
		g1[n1 & 1][i][j] = res1, g2[n1 & 1][i][j] = res2;
	}
}

inline void get_f(int n1, int k1)
{
	if (vis[n1 & 1][k1]) return; else vis[n1 & 1][k1] = 1;
	
	if (n1 == 1)
	{
		f0[n1 & 1][k1] = 1;
		for (int i = k1; i <= k; i++) f1[n1 & 1][k1][i] = 1;
		for (int i = 0; i <= k1; i++) f2[n1 & 1][k1][i] = 1;
		return;
	}
	
	ll res = 0, res1 = 0;
	for (int i = 0; i <= k1; i++)
		res1 = (res1 + f0[(n1 - 1) & 1][i]) % p,
		res = (res + f0[(n1 - 1) & 1][k1 - i] * res1) % p;
	f0[n1 & 1][k1] = res;
	
	res = 0, res1 = f0[(n1 - 1) & 1][0]; int j1 = 0, j2;
	for (int i = 1; i <= k1; i++)
	{
		j2 = min(i - 1, k1 - i);
		while (j1 < j2) res1 = (res1 + f0[(n1 - 1) & 1][++j1]) % p;
		while (j1 > j2) res1 = (res1 + p - f0[(n1 - 1) & 1][j1--]) % p;
		res = (res + f1[(n1 - 1) & 1][i][i] * res1) % p;
		f1[n1 & 1][k1][i] = (res * 2 % p);
	}
	
	res = 0;
	for (int i = k1; i > 0; i--)
	{
		j2 = min(i - 1, k1 - i);
		res = (res + g2[(n1 - 1) & 1][i][j2] + g1[(n1 - 1) & 1][i][j2]) % p;
		f2[n1 & 1][k1][i] = (res * 2 % p);
	}
}

int main()
{
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d%lld", &n, &k, &p);
		memset(g1, 0, sizeof(g1)), memset(g2, 0, sizeof(g2));
		for (int i = 1; i <= n; i++)
		{
			memset(f0[i & 1], 0, sizeof(f0[i & 1]));
			memset(f1[i & 1], 0, sizeof(f1[i & 1])), memset(f2[i & 1], 0, sizeof(f2[i & 1]));
			memset(g1[i & 1], 0, sizeof(g1[i & 1])), memset(g2[i & 1], 0, sizeof(g2[i & 1]));
			memset(vis[i & 1], 0, sizeof(vis[i & 1]));
			for (int j = 0; j <= k; j++) get_f(i, j);
			for (int j = 0; j <= k; j++) get_g(i, j);
		}
		
		printf("%lld\n", f2[n & 1][k][1]);
	}
	
	return 0;
}
```

---

## 作者：happybob (赞：0)

题意：

定义一个**堆**为一棵树高为 $n$，点数为 $2^n-1$ 的满二叉树，点权序列为 $\{a\}$，对于每一个非叶子节点 $i(1 \le i \le 2^{n-1}-1)$，其儿子应为 $2i$ 和 $2i+1$，且满足 $a_i \ge \max(a_{2i}, a_{2i+1})$。

一次**删除操作**的伪代码如下：

1. 初始令 $v=1$。
2. 执行 $a_v \gets \max(a_{2v},a_{2v+1})$，并令 $v$ 为 $a_{2v},a_{2v+1}$ 中较大者的下标（若相等则认为这次删除操作**不确定**，$v$ 变为 $2v$ 或 $2v+1$ 中任意一个）。
3. 若 $2v+1 \le 2^{n}-1$，返回第 2 条。
4. 执行 $a_v \gets -1$。

定义一个堆是**确定**的，当且仅当执行**两次删除操作**的过程中，不存在**不确定**的操作。

定义一个堆是**可构造**的，当且仅当对于给定常数 $k$，一个堆的点权序列可以通过以下方式构造出：

+ 初始所有 $a_i=0$。执行 $k$ 次操作，每次任选一个点 $1 \le x \le 2^n-1$，将根节点到 $x$ 路径上所有的点权加 $1$。

$t$ 次询问，每次给出 $n,k,p$，求有多少个树高为 $n$ 的**可构造**的堆是**确定**的，答案对 $p$ 取模。

$t \le 50$，$\sum n \le 100$，$\sum k \le 500$， $10^8 \le p \le 10^9$，$p$ 是质数。

解法：

对于 E1，题意区别在于确定的堆只需要满足一次操作确定即可。其简略做法是记 $f_{i,j}$ 表示深度为 $i$ 的二叉树，进行了 $j$ 次操作构成的确定堆方案数，以及 $g_{i,j}$ 表示堆不需要确定的方案数。

对于 E2，考虑如何刻画操作两次。可以发现两次操作的第一个走向不同位置只依赖于另一个方向的两个儿子点权最大值。考虑记 $h_{i,j,k}$ 表示深度为 $i$ 的堆，进行了 $j$ 次操作，两个儿子点权最大值为 $k$，且可以进行一次操作的方案数。$s_{i,j,k}$ 表示可以进行两次的方案数。可以发现转移只需要枚举左儿子和右儿子点权，维护前缀和即可。为了更加方便可以直接将状态变为儿子最大值 $\leq k$，复杂度 $O(nk^2)$，可以通过。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <array>
using namespace std;

using ll = long long;

constexpr int N = 105, M = 505;

int n, m;
ll MOD;
int t;
array<array<ll, M>, N> g, f;
array<ll, M> cf;
array<array<ll, M>, M> cf2;
array<array<array<int, M>, M>, N> s, h;

inline void subadd(int l, int r, ll v, array<ll, M>& cf)
{
	cf[l] += v;
	cf[l] >= MOD ? cf[l] -= MOD : 0;
	cf[r + 1] = cf[r + 1] - v + MOD;
	cf[r + 1] >= MOD ? cf[r + 1] -= MOD : 0;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> m >> MOD;
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= m; j++) f[i][j] = g[i][j] = 0;
		}
		for (int i = 0; i <= m; i++) f[1][i] = 1, g[1][i] = 1;
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= m; j++)
			{
				for (int k = 0; k <= m; k++) s[i][j][k] = h[i][j][k] = 0;
			}
		}
		for (int j = 0; j <= m; j++)
		{
			for (int k = 0; k <= m; k++) s[1][j][k] = h[1][j][k] = 1;
		}
		auto clears = [&]
			{
				for (int j = 0; j <= m + 1; j++)
				{
					for (int k = 0; k <= m + 1; k++) cf2[j][k] = 0;
				}
				for (int j = 0; j <= m + 1; j++) cf[j] = 0;
			};
		for (int i = 2; i <= n; i++)
		{
			g[i][0] = 1ll;
			clears();
			// solve g
			for (int x = 0; x <= m; x++)
			{
				for (int y = 0; y + x <= m; y++)
				{
					subadd(x + y, m, g[i - 1][x] * g[i - 1][y] % MOD, cf);
				}
			}
			for (int x = 1; x <= m; x++)
			{
				cf[x] = cf[x] + cf[x - 1];
				cf[x] >= MOD ? cf[x] -= MOD : 0;
				g[i][x] = cf[x];
			}
			clears();
			for (int x = 0; x <= m; x++)
			{
				for (int y = 0; y + x <= m; y++)
				{
					if (x == y) continue;
					subadd(x + y, m, f[i - 1][max(x, y)] * g[i - 1][min(x, y)] % MOD, cf);
				}
			}
			for (int x = 1; x <= m; x++)
			{
				cf[x] = cf[x] + cf[x - 1];
				cf[x] >= MOD ? cf[x] -= MOD : 0;
				f[i][x] = cf[x];
			}
			clears();
			// solve h
			for (int x = 0; x <= m; x++)
			{
				for (int y = 0; y + x <= m; y++)
				{
					if (x == y) continue;
					ll val = f[i - 1][max(x, y)] * g[i - 1][min(x, y)] % MOD;
					subadd(x + y, m, val, cf2[max(x, y)]);
				}
			}
			for (int k = 0; k <= m; k++)
			{
				for (int j = 1; j <= m; j++)
				{
					cf2[k][j] += cf2[k][j - 1];
					cf2[k][j] >= MOD ? cf2[k][j] -= MOD : 0;
				}
				for (int j = 0; j <= m; j++)
				{
					h[i][j][k] = cf2[k][j];
				}
			}
			for (int j = 0; j <= m; j++)
			{
				for (int k = 1; k <= m; k++)
				{
					h[i][j][k] += h[i][j][k - 1];
					h[i][j][k] >= MOD ? h[i][j][k] -= MOD : 0;
				}
			}
			// solve s
			clears();
			for (int x = 0; x <= m; x++)
			{
				for (int y = 0; y + x <= m; y++)
				{
					if (x == y) continue;
					bool tag = (x < y);
					if (tag) swap(x, y);
					// case1: 两次均为左侧
					// k>y
					ll ret = (s[i - 1][x][m] - s[i - 1][x][y] + MOD) * g[i - 1][y] % MOD;
					if (i == 2) ret = 0ll;
					subadd(x + y, m, ret, cf2[x]);
					// case2: 第一次左，第二次右
					// k<y
					ret = (y == 0 ? 0 : h[i - 1][x][y - 1]);
					if (i == 2) ret = 1;
					ret >= MOD ? ret -= MOD : 0;
					ret = ret * f[i - 1][y] % MOD;
					subadd(x + y, m, ret, cf2[x]);
					//if (i == 3) cout << "??: " << x + y << " " << ret << "\n";
					if (tag) swap(x, y);
				}
			}
			for (int k = 0; k <= m; k++)
			{
				for (int j = 1; j <= m; j++)
				{
					cf2[k][j] += cf2[k][j - 1];
					cf2[k][j] >= MOD ? cf2[k][j] -= MOD : 0;
				}
				for (int j = 0; j <= m; j++)
				{
					s[i][j][k] = cf2[k][j];
				}
			}
			for (int j = 0; j <= m; j++)
			{
				for (int k = 1; k <= m; k++)
				{
					s[i][j][k] += s[i][j][k - 1];
					s[i][j][k] >= MOD ? s[i][j][k] -= MOD : 0;
				}
			}
		}
		cout << s[n][m][m] << "\n";
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF2001E2)

**题目大意**

> 给定一棵高为 $n$ 的满二叉树，进行 $k$ 次操作，每次把一条到根的链上点权 $+1$，容易发现形成大根堆。偶
>
> 执行两次 pop 操作，要求每次操作访问到的非叶子节点的左右儿子权值不相等，求方案数。
>
> 数据范围：$n\le 100,k\le 500$。

**思路分析**

称点权较大的儿子为重儿子，根的重儿子为重链。

能生成题目中的结构当且仅当 $a_i\ge a_{ls}+a_{rs}$，可以进行一次 pop 操作相当于每个点的重儿子左右子树权值不同。

那么可以 dp：$h_{i,j}$ 表示深度为 $i$ 的堆，根节点权值为 $j$ 的合法方案数，由于轻儿子中无限制，还要记录 $g_{i,j}$ 表示没有 pop 限制的方案数。

然后考虑第二次 pop，此时如果 $u$ 在重链上，那么 $a_u$ 变成其重儿子 $v$ 的点权 $a_v$，而 $a_{v}$ 变成原先 $v$ 的重儿子 $a_w$。

我们的限定条件变成 $a_w\ne a_{x}$，其中 $x$ 是 $u$ 的轻儿子。

因此在 dp 状态中要记录重儿子的权值，$f_{i,j,t}$ 表示重儿子权值为 $t$ 的方案数。

然后要讨论 $a_w,a_x$ 的大小关系决定递归到哪个子问题中：

- 如果 $a_w>a_x$，那么相当于 $u$ 的重子树支持 pop 两次，从 $f_{i-1,a_v,*}$ 转移，而 $u$ 的轻子树不需要 pop，从 $g_{i-1,a_x}$ 转移。
- 否则左右子树都能 pop 一次，从 $h_{i-1,a_v,*},h_{i-1,a_x,*}$ 转移。

转移使用前缀和优化。

时间复杂度 $\mathcal O(nk^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace FastMod {
typedef unsigned long long ull;
typedef __uint128_t uLL;
ull b,q,r; uLL m;
inline void init(const ull &B) { b=B,m=(uLL(1)<<64)/B; }
inline ull mod(const ull &a) {
	r=a-((m*a)>>64)*b;
	return r>=b?r-b:r;
}
}
#define o(x) FastMod::mod(x)
int n,k,MOD,f[505][505],g[505][505],s[505],h[505],u[505][505],t[505][505];
inline void add(int &x,const int &y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
void solve() {
	memset(f,0,sizeof(f));
	memset(h,0,sizeof(h));
	scanf("%d%d%d",&n,&k,&MOD),FastMod::init(MOD);
	for(int i=1;i<=k;++i) for(int j=0;j<i&&i+j<=k;++j) f[i+j][i]+=2;
	for(int i=1;i<=k;++i) for(int j=0;j<=i;++j) add(f[i][j],f[i-1][j]),u[i][j]=f[i][j];
	for(int i=0;i<=k;++i) for(int j=0;i+j<=k;++j) ++h[i+j];
	for(int i=1;i<=k;++i) add(h[i],h[i-1]);
	for(int d=3;d<=n;++d) {
		memset(t,0,sizeof(t));
		for(int i=1;i<=k;++i) for(int j=0;j<=i;++j) {
			t[i][j]=u[i][j],add(t[i][j],j?t[i][j-1]:0);
		}
		
		memset(g,0,sizeof(g));
		for(int i=1;i<=k;++i) {
			memset(s,0,sizeof(s));
			for(int j=i;j>=0;--j) s[j]=f[i][j],add(s[j],s[j+1]);
			for(int j=0;j<i&&i+j<=k;++j) {
				g[i+j][i]=o(g[i+j][i]+2ll*h[j]*s[j+1]+2ll*t[i][j-1]*t[j][j]);
			}
		}
		for(int i=1;i<=k;++i) for(int j=0;j<=i;++j) add(g[i][j],g[i-1][j]);
		memcpy(f,g,sizeof(f));
		
		memset(g,0,sizeof(g));
		for(int i=1;i<=k;++i) for(int j=0;j<i&&i+j<=k;++j) {
			g[i+j][i]=o(g[i+j][i]+2ll*t[i][i]*h[j]);
		}
		for(int i=1;i<=k;++i) for(int j=0;j<=i;++j) add(g[i][j],g[i-1][j]);
		memcpy(u,g,sizeof(u));
		
		memset(s,0,sizeof(s));
		for(int i=0;i<=k;++i) for(int j=0;i+j<=k;++j) s[i+j]=o(s[i+j]+1ll*h[i]*h[j]);
		for(int i=1;i<=k;++i) add(s[i],s[i-1]);
		memcpy(h,s,sizeof(h));
	}
	int ans=0;
	for(int i=0;i<=k;++i) add(ans,f[k][i]);
	printf("%d\n",ans);
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：居然有个高手 (赞：0)

无敌超级大构思。

文中 $K$ 表示题面中的 $k$。

不妨考虑首次删除操作经过的点的权值 $a_1,a_2,\cdots,a_n$，发现第二次删除所经过的点的权值一定是 $a_2,a_3,\cdots,a_i,b_{i+1},b_{i+2},\cdots,b_n$，其中满足 $b_{i+1},a_{i+1}$ 是 $i$的两个儿子的权值，且 $i$ 是第一个满足 $a_{i+1} < b_{i+1}$ 的结点。

发现若进入 $b_{i+1}$ 子树后方案数便只与 $i$ 这个点的深度与 $b_{i+1}$ 这个权值有关，$f_{i,j}$ 表示子树根深度为 $i$ 时，子树内有 $j$ 个权值还未分配，且子树需要满足删除一次时操作唯一的方案数，另记 $pw_{i,j}$（表示子树根深度为 $i$，$j$ 次任意操作的方案数）辅助转移。

随后，我们考虑综合计算两次删除的方案数。记 $g_{i,j,k}$ 表示深度为 $i$，还有 $j$ 次操作，上一个挂着的 $b_{i+1} = k$ 时的方案数。特别的，$k=K+1$ 时代表已经计算了第二次删除的贡献。根据定义有如下转移：

1. $g_{i,j,K+1} \to g_{i+1,x,K+1}$，此转移代表第二次删除已被算过，只关心第一次删除子树内的操作。转移要求显然是 $j\le x$。转移所带权值为 $\sum_{p=0}^{\min(j-x,x-1)} pw_{i+1,p}$，表示另一子树内的点的数量的取值范围。转移时枚举 $i,j,x$，对 $pw$ 预处理前缀和可做到 $O(nk^2)$。

2. $g_{i,j,k} \to g_{i+1,x,K+1}$，此转移代表进入 $b_{i+1}$ 的时间点就在当次转移中。转移要求为 $j<k$。所带权值为 $\sum_{p=0}^{\min(j-x,x-1)} pw_{i+1,p} \times f_{i,k}$。转移时枚举 $i,j,x$，记录一个 $f_{i,k}\times g_{i,j,k}$ 的前缀和转移。同样是 $O(nk^2)$ 的。

3. $g_{i,j,k}\to g_{i+1,x1,x2}$，此转移代表直至目前都还未进入 $b_{i+1}$。转移要求是 $x1+x2\le j,x1>k$。所带权值为 $pw_{i+1,k}$，意味着上一个子树乱填。实际转移时处理一个二维前缀和即可。还是 $O(nk^2)$ 的。

发现 $g$ 数组空间较大，滚动数组优化一下空间复杂度。

综上，时间复杂度 $O(nk^2)$，空间复杂度 $O(k^2)$。

贴个代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=105,M=505;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*f;
}
int T,n,k,mod,f[N][M],g[2][M][M],sum[M],s2[M][M],h[M],t[M][M],pw[N][M],pw2[N],inv[M],S[N][M];
inline int md(int x){
    return x>=mod?x-mod:x;
}
inline int ksm(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }return ans;
}
int main(){
    T=read();
    while(T--){
        n=read(),k=read(),mod=read();
        pw2[0]=1;
        for(int i = 1;i<=n;i++)pw2[i]=md(pw2[i-1]*2);
        inv[0]=inv[1]=1;
        for(int i = 2;i<=k;i++)inv[i]=inv[mod%i]*1ll*(mod-mod/i)%mod;
        t[0][0]=1;
        for(int i = 1;i<=k;i++)for(int j = i;j<=k;j++){
            t[i][j]=0;
            for(int o = 1;o<=j-i+1;o++)t[i][j]=md(t[i][j]+t[i-1][j-o]);
        }
        for(int i = 1;i<=n;i++){
            for(int j = 0;j<=k;j++){
                pw[i][j]=0;
                for(int o = 0,C=1;o<=j &&(i>=9 || o<=(1<<i)-1);o++)pw[i][j]=(pw[i][j] + 1ll*C*t[o][j])%mod,C=1ll*C*inv[o+1]%mod*(pw2[i]-1-o)%mod;
            }
        }
        //pw[i][j]:高为i的子树内j次操作的方案数
        for(int i = 0;i<=k;i++)f[n][i]=1;
        for(int i = n-1;i>=1;i--){
            for(int j = 0;j<=k;j++)h[j]=0;
            for(int j = 1;j<=k;j++){
                for(int o = 0;o<j&&j+o<=k;o++)h[j+o]=(h[j+o]+2ll*f[i+1][j]*pw[n-i][o])%mod;
            }
            for(int j = 1;j<=k;j++)h[j]=md(h[j]+h[j-1]);
            for(int j = 0;j<=k;j++)f[i][j] = h[j];
        }
        //f[i][j]:深为i的子树内j次操作且满足条件的方案数
        for(int i = 1;i<=n;i++){
            S[i][0]=pw[i][0];
            for(int j = 1;j<=k;j++)S[i][j]=md(pw[i][j]+S[i][j-1]);
        }
        for(int i = 0;i<=1;i++)for(int j = 0;j<=k;j++)for(int o = 0;o<=k+1;o++)g[i][j][o]=0;
        g[1][k][0]=1;
        for(int i = 1,now=0;i<n;i++,now^=1){
            for(int j = 0;j<=k;j++)for(int o = 0;o<=k+1;o++)g[now][j][o]=0;
            for(int j = 0;j<=k;j++){
                int s = 0;
                for(int x = j;x>=1;x--){
                    g[now][x][k+1]=(1ll*g[now^1][j][k+1]*S[n-i][min(j-x,x-1)]+g[now][x][k+1])%mod;
                    g[now][x][k+1]=(g[now][x][k+1] + 1ll*s*S[n-i][min(j-x,x-1)])%mod;
                    s=(s + 1ll*g[now^1][j][x]*f[i][x])%mod;
                }
            }
            for(int j = 0;j<=k;j++){
                for(int o = 0;o<=k;o++){
                    s2[j][o]=g[now^1][j][o]*1ll*pw[n-i+1][o]%mod;
                    if(o)s2[j][o]=md(s2[j][o]+s2[j][o-1]);
                }
            }
            for(int j = k-1;j>=0;j--){
                for(int o = 0;o<=k;o++)s2[j][o]=md(s2[j+1][o]+s2[j][o]);
            }
            for(int j = 1;j<=k;j++)for(int o = 0;o<j&&j+o<=k;o++){
                g[now][j][o]=s2[j+o][j-1];
            }
            for(int j = 0;j<=k;j++)for(int o = 0;o<=k+1;o++){
                g[now][j][o]=md(g[now][j][o]*2);
            }
        }
        int ans=0;
        for(int i =0;i<=k;i++)for(int j = 0;j<=k+1;j++)ans=md(ans+g[n&1][i][j]);
        printf("%d\n",ans);
    }
    return 0;
}
```

---

