# Shrinking Tree

## 题目描述

给定一棵 $T$（即无环连通图），有 $n$ 个顶点，编号为 $1$ 到 $n$。我们对 $T$ 进行如下操作：当 $T$ 中顶点数大于 $1$ 时，重复以下步骤：

- 等概率随机选择 $T$ 的一条边；
- 收缩所选边：若该边连接顶点 $v$ 和 $u$，则删除 $v$ 和 $u$，新建一个顶点，并使其与所有原本与 $v$ 或 $u$ 相邻的顶点相连。新顶点的编号等概率地取 $v$ 或 $u$ 的编号。

当操作结束时，$T$ 只剩下一个顶点，其编号为 $1, 2, \ldots, n$ 中的某一个。对于每一个编号，求该编号最终成为唯一顶点编号的概率。

## 说明/提示

在第一个样例中，最终顶点编号为 $1$ 当且仅当所有三条边的编号 $1$ 都被保留，因此概率为 $1/2^3 = 1/8$。其余编号由于对称性，概率相等，因此每个概率为 $(1 - 1/8) / 3 = 7/24$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
0.1250000000
0.2916666667
0.2916666667
0.2916666667
```

## 样例 #2

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
3 7
```

### 输出

```
0.0850694444
0.0664062500
0.0664062500
0.1955295139
0.1955295139
0.1955295139
0.1955295139
```

# 题解

## 作者：EternalAlexander (赞：35)

写个人能看的题解。

### 怎么做

我们考虑对每个点分别计算这个概率，为了方便不妨在计算一点答案时将其设为树根。

我们先把“删边”这个操作变成一个比较容易处理的形式。在有根树意义下，删除边 $u-v$ 时，不妨设 $u$ 是 $v$ 的父节点，我们认为，这个操作把 $v$ 的所有子树接到了 $u$ 上，然后删除掉 $v$ 这个节点，之后节点 $u$ 的编号是新选择的编号。

记 $f_{u,j}$ 表示，在 $u$ 的子树中，对于所有删边顺序，仅对最后 $j$ 条边选择保留的编号，而其他边随意选择时，根节点的编号仍然是 $u$ 的概率之和。节点 $x$ 最后的答案是 $\frac{f_{x,n-1}}{(n-1)!}$。

考虑类似树上背包地合并子树的 dp 值。我们分两步完成将 $f_v$ 合并至 $f_u$ 的这一过程。

第一步是，我们要加入边 $u-v$。我们考虑 $v$ 的子树和节点 $u$ 连接在一起形成的这棵树 $T$，令 $g_i$ 表示，在 $T$ 中，对于所有删边顺序，仅对最后 $i$ 条边选择保留的编号时，根节点的编号仍然是 $u$ 的概率之和（和 $f_{u,j}$ 定义是一样的）。

考虑如何计算 $g_i$，我们枚举边 $u-v$ 在倒数第几步被删掉。

第一种情况是，$j\leq i$，也就是说边 $u-v$ 被收缩时，新的编号已经被确定。我们在确定这条边的编号时，必须要选 $u$，因此要乘上一个 $\frac{1}{2}$ 的概率，然后，这条边之前的编号选择是随意的，而收缩之后，剩下 $j-1$ 条边选择编号时都必须保留 $u$，而因为，$v$ 的子树都被连接到了 $u$ 上，这等同于在 $v$ 的子树中保留 $v$，概率之和是 $f_{v,j-1}$，转移式为 $g_i \leftarrow f_{v,j-1}$。

第二种情况是 $j > i$，也就是这条边不需要确定编号，而且在最后 $i$ 条边之前已经被收缩掉了。收缩后 $i$ 条边时，必须保留 $u$ 等同于之前必须保留 $v$，也就是 $g_i \leftarrow f_{v,i}$。

现在，我们已经成功地将 $u-v$ 这条边包含了进来，可以考虑如何与考虑完之前子树的答案合并了。

考虑在之前的子树中选了 $i$ 条边的编号，而在需要合并上来的 $T$ 中选了 $j$ 条边，我们需要把有编号的边放一起，没有编号的边放一起，需要保持两个子树内部删边的相对顺序不变。记 $M$ 和 $N$ 分别为之前已经被合并进来的边数和 $T$ 中的边数，根据组合意义，方案数为 $\binom{i+j}{j} \binom{M+N}{N}$，转移式为 $f_{u,i+j} \leftarrow f_{u,i} g_j \binom{i+j}{j} \binom{M+N}{N}$。

通过树上背包的上下界优化，容易做到 $O(n^4)$。

### 怎么想到这么做

对每个点单独计算贡献可以说是一种常见做法。在转化成有根树之后，我们发现，收缩 $u-v$ 时，这条边之前的编号选择是随意的，之后的话，由于此时的 $v$ 已经变成了 $u$，这些边选择编号时不能把 $v$ 吃掉，至此容易看出子问题的形式，我们需要保证后若干条边不吃掉根节点，记录一下即可。

```cpp
#include <bits/stdc++.h>
int n,u,v,size[55];
double f[55][55],C[55][55],g[55],h[55],fac[55];
std::vector<int>ch[55];

void dfs(int u,int pr){
	f[u][0]=1;size[u]=1;
	for(int v:ch[u]){
		if(v==pr)continue;
		dfs(v,u);
		std::memset(g,0,sizeof(g));
		for(int i=0;i<=size[v];++i)
		for(int j=1;j<=size[v];++j){
			if(j<=i)g[i]+=0.5*f[v][j-1];
			else g[i]+=f[v][i];
		}
		std::memset(h,0,sizeof(h));
		for(int i=size[u]-1;i>=0;--i)
		for(int j=size[v];j>=0;--j)
			h[i+j]+=f[u][i]*g[j]*C[i+j][j]*C[size[u]-i-1+size[v]-j][size[u]-i-1];
		for(int i=0;i<size[u]+size[v];++i)f[u][i]=h[i];
		size[u]+=size[v];
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<=n;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j)C[i][j]=C[i-1][j]+C[i-1][j-1];
	}fac[0]=1;for(int i=1;i<=n;++i)fac[i]=fac[i-1]*i;
	for(int i=1;i<n;++i){
		scanf("%d%d",&u,&v);
		ch[u].push_back(v);
		ch[v].push_back(u);
	}for(int i=1;i<=n;++i){
		std::memset(f,0,sizeof(f));
		dfs(i,0);
		printf("%.7f\n",f[i][n-1]/fac[n-1]);
	}
	return 0;
}
```


---

## 作者：Alex_Wei (赞：22)

- Update on 2023.1.22 重写题解，[原题解链接](https://www.luogu.com.cn/paste/g3fk499q)。

[CF1060F Shrinking Tree](https://www.luogu.com.cn/problem/CF1060F)

这题真的只有 *2900 吗？

排列太复杂，先考虑对于固定的删边顺序，每个点 $x$ 留下的概率。给边标号，设第 $i$ 条边被删去的次序为 $p_i$。

容易发现，包含 $x$ 的连通块每次 “扩张”，都会让 $x$ 留下的概率减半。连通块扩张意味着扩展的这条边 $e$ 在 $e$ 与 $x$ 之间所有边被删去之后才删去，即 $p_e$ 大于 $e$ 与 $x$ 之间所有边。

以 $x$ 为根求解节点 $x$ 的答案。由于每条边 $e = (u, v)(u = fa(v))$ 的子节点 $v$ 互不相同，所以把边权 $p_e$ 赋给其子节点 $v$。

答案即 $\frac {1}{2 ^ c}$，其中 $c$ 为使得 $x$ 与节点 $u$ 之间所有点的点权均不大于 $p_u$ 的 $u$ 的个数，也即扩张次数。

接下来尝试解决原问题。

由于若干子树相对独立，考虑树形 DP。笔者一开始设 $f_{i, j}$ 表示以 $i$ 为根的子树，扩张次数为 $j$ 的方案数。但这样无法封闭转移，因为当 $i$ 的权值为 $v$ 时，子树内原本符合条件但点权 $< v$ 的节点就变得不符合条件了。因此，我们还需记录一维 $k$ 表示当前子树内点权前 $k$ 小的均被忽略，即根到父节点的点权最大值大于当前子树内的 $k$ 个点权。

转移时，先对所有儿子做 $j, k$ 两维的树形背包。合并 $f_{u, j_1, k_1}$ 和 $f_{v, j_2, k_2}$ 时，分配点权带来的贡献系数为 $\binom {k_1 + k_2} {k_1} \binom {sz_u + sz_v - k_1 - k_2} {sz_u - k_1}$。设得到的背包为 $g$。

接下来枚举 $i$ 的点权 $v$（在子树内的相对大小）。若 $v > k$，则不符合条件，因为最大值不能超过 $k$；若 $v = k$，则 $i$ 是一次扩张，$j$ 增加 $1$，新的限制可以任取，但不能超过 $k$；若 $v < k$，则 $i$ 不是一次扩张，$k$ 增加 $1$。

答案即 $\frac {\sum_{j = 0} ^ {n - 1} \frac {f_{x, j, 0}} {2 ^ j}} {(n - 1)!}$。注意对于根节点 $x$ 不需要再枚举其权值，所以 $f_{x, j, 0}$ 就等于背包得到的 $g_{j, 0}$。时间复杂度 $\mathcal{O}(n ^ 5)$，分别枚举 $x, i, j, k, v$。背包部分反而不是瓶颈。

优化：$j$ 这一维可以直接除进 $f$ 里面，即设 $f_{i, k}$ 表示所有方案的 $\frac {1} {2 ^ j}$ 之和。树形背包照常做，$j$ 增加 $1$ 时 DP 值除以 $2$。时间复杂度 $\mathcal{O}(n ^ 4)$。[代码](https://codeforces.com/contest/1060/submission/190103607)。

$v < k$ 的部分全部贡献到 $f_{i, k + 1}$，$v = k$ 可以前缀和优化。时间复杂度 $\mathcal{O}(n ^ 3)$。

---

## 作者：ywy_c_asm (赞：21)

一个比较难以理解的dp神题。

首先我们可以考虑**每次随机缩一条边**等效于**有一个长度为$n-1$的边的操作序列**，那么我们可以用序列计数的角度去处理这个东西，每个操作序列的边都有一半的概率选择一个端点，那对于我们钦定的一个点$rt$，在一个操作序列中它会有一定概率最后保留，那么我们可以求出所有操作序列这个点被保留的概率和，最后除个$(n-1)!$即可。

现在我们干脆把$rt$这个点提成根做一遍树形dp。但是这个dp如何入手呢？我们不妨假设（或者说叫钦定）一种状态就是考虑$u$这个点，$rt$现在已经克服重重困难来到了$u$点，但是$rt$怎么来的$u$点我们并不关心，**我们仅关心$u$子树内的所有边的序列**，因为我们可以使用诸如组合数之类的方式来合并两个操作序列。那么我们的大体思路应该是$dp[u]$为当$rt$这个编号转移到$u$点并将其取代之后，$u$这棵子树缩成一个$rt$编号的大点的操作序列的方案数（或者说是概率）。

我们考虑这个$dp$有没有什么值得转移的地方。我们知道$u$这个操作序列是它儿子的操作序列加上连向儿子的边**混合**而成的。那么我们不妨这样转移：

![](https://cdn.luogu.com.cn/upload/pic/59357.png)

当合并过来一个儿子$v$的边的序列的时候，应该是这个儿子子树的边序列+这条连向儿子的边，所以，我们不妨在每个儿子处单独处理把这条父亲边插到自己的边序列中得到的边序列$g$，这样我们在父亲$u$处就考虑所有儿子$g$序列的合并就行了。

考虑$(u,v)$啥时候加入$v$的边序列，可以分两种情况：

①：$rt$已经移动至$u$，那么现在$u$就相当于$rt$，那么合并$(u,v)$这条边的时候必须有$\frac 1 2$的概率不让$rt$死掉，除此之外我们给$(u,v)$随便插个位置就好了。

②：$rt$还未移动至$u$，那么我合并$(u,v)$这条边最终编号是啥并没有关系，但是，我们现在的问题是必须保证给$(u,v)$插入一个位置的时候$rt$还没有移动至$u$。

那么现在我们就需要改一下$dp$状态了，我们设$dp[u][i]$为**仅考虑$u$子树里的边序列**，当$rt$移动到$u$的时候边序列还有最后$i$条没有合并的边序列的概率和。然后对于那个对儿子扩充的$g$序列我们设$g[v][i]$为**仅考虑$v$子树和它父亲边的边序列**，当$rt$移动到它的父亲$u$时这个序列还剩下最后$i$条没有合并的边序列的概率和。

这样的话，我们重新来看一下上面两个情况：

①：显然对于一个$g[v][i]$，$(u,v)$要插到末尾$i$个位置中去，那枚举$(u,v)$之后有多少条边，然后合并完$(u,v)$就相当于$rt$移动到了$v$上，就归纳到了$v$本身的边序列，所以$g[v][i]=\frac 1 2\sum_{j=0}^{i-1}dp[v][j]$。

②：对于$g[v][i]$这个序列来说我们只需把$(u,v)$插到前$size[v]-i$个已经合并的位置就行了，所以$g[v][i]=(size[v]-i)dp[v][i]$。

那么现在我们把每个儿子的$g$序列搞出来了，如何合并呢？其实，我们并不用考虑那么多，可以发现，儿子的边序列其实是互不影响的，因为在合并$(u,v)$的时候我们已经通过讨论避免了$rt$死掉，而每个儿子迟早会有一个点遇到$rt$，所以我们可以独立的合并儿子的$g$序列，只要我们保证在$rt$移动到$u$这个点的时刻（这是个最关键的时刻）之前已经合并了的边都在前面，之后没合并的边都在后面，就是这样：

![](https://cdn.luogu.com.cn/upload/pic/59362.png)

那么我们考虑两个儿子$x,y$的合并，就是：

$g[x][i]g[y][j]C_{size[x]-i+size[y]-j}^{size[x]-i}C_{i+j}^i\to dp[u][i+j]$

前面的$C$是在这个时刻之前已经合并完的边序列混合起来，后面的$C$是在这个时刻之后的。

然后就$O(n^4)$了，还有要相信$double$，不太大的数据范围它还是能够处理阶乘组合数之类的……

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
namespace ywy {
	double dp[55][55], g[55], jc[55];
	inline double cnm(int n, int m) {
	    if (n < m)
	        return (0);
	    return ((jc[n] / jc[m]) / jc[n - m]);
	}
	typedef struct _b {
	    int dest;
	    int nxt;
	} bian;
	bian memchi[1000001];
	int gn = 1, heads[55];
	inline void add(int s, int t) {
	    memchi[gn].dest = t;
	    memchi[gn].nxt = heads[s];
	    heads[s] = gn;
	    gn++;
	}
	int size[55];
	double h[55];
	void dfs(int pt, int baba) {
	    size[pt] = 1;
	    dp[pt][0] = 1;
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        dfs(memchi[i].dest, pt);
	        for (register int j = 0; j <= size[memchi[i].dest]; j++) {
	            g[j] = 0;
	            for (register int k = 0; k < j; k++) g[j] += 0.5 * dp[memchi[i].dest][k];
	            g[j] += (size[memchi[i].dest] - j) * dp[memchi[i].dest][j];
	        }
	        for (register int j = 0; j <= size[pt] + size[memchi[i].dest]; j++) h[j] = 0;
	        for (register int j = 0; j < size[pt]; j++) {
	            for (register int k = 0; k <= size[memchi[i].dest]; k++) {
	                h[j + k] += dp[pt][j] * g[k] *
	                            cnm(size[pt] - 1 - j + size[memchi[i].dest] - k, size[pt] - 1 - j) *
	                            cnm(j + k, j);
	            }
	        }
	        size[pt] += size[memchi[i].dest];
	        for (register int j = 0; j < size[pt]; j++) dp[pt][j] = h[j];
	    }
	}
	void ywymain() {
	    int n;
	    cin >> n;
	    jc[0] = 1;
	    for (register int i = 1; i <= n; i++) jc[i] = jc[i - 1] * i;
	    for (register int i = 1; i < n; i++) {
	        int s, t;
	        cin >> s >> t;
	        add(s, t);
	        add(t, s);
	    }
	    for (register int i = 1; i <= n; i++) {
	        memset(dp, 0, sizeof(dp));
	        dfs(i, 0);
	        printf("%.10lf\n", dp[i][n - 1] / jc[n - 1]);
	    }
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：psoet (赞：13)

> 有一棵 $n$ 个点的树，每次等概率缩一条边，等概率保留其中的一个编号，求出最终每个点剩下的概率，输出实数。$n \leq 50$

设当前要求点 $rt$ 的答案，把它当作根。

一个麻烦的事情是，因为缩边的过程会改变树的结构，我们无法边缩边边计算概率。

所以先确定缩边的顺序，再确定相应的概率系数。后者是 $0.5$ 的（缩边时与根相连的边数）次方。

给定排列后，一条边缩的时候与根相连当且仅当它比到根路径上所有其他的边都要靠后。

考虑到跟概率有关的问题对连续变量比较友好，我们把排列转成 $(n-1)$ 个 $[0,1]$ 内均匀随机的变量。

令 $f_u(x)$ 表示 $u$ 到根边权最大值是 $x$ 时，子树内的系数贡献期望。

那么 

$$f_u(x)=\prod_v[xf_v(x)+{1\over 2}\int_x^1f_v(t)\mathrm{d}t]$$

维护多项式，总复杂度 $O(n^3)$。

---

## 作者：gayh20 (赞：11)

> 这个题我看到的所有题解状态定义的解释感觉都有问题。。

对于每个点分别计算概率。以要算的这个点为根。

设 $f(x,i)$ 表示 $x$ 子树内，最后删去的 $i$ 条边满足，删去这些边之后，子树的根的编号是删去这 $i$ 条边之前根的编号的概率。我们要求 $f(rt,n-1)$。

为什么要这么设？因为 $(u,v)$ 这条边删之前，$v$ 子树内的边可以随便删，删之后要求不能影响到 $u$。于是有这个状态设计。

$y\to x$ 转移 $f$ 时，分两步：

1. 加入边 $(x,y)$，枚举 $(x,y)$ 在从后往前第 $i$ 步被删掉，设这时转移到的新 dp 数组为 $g_j$。
   - $i\le j$，也即 $(x,y)$ 删的时候（这里 $x,y$ 已经不一定是原来的那两个点了，但地位是等价的），必须选择 $x$ 保留。在这条边之后删的 $i-1$ 条边都需要选择保留 $y$（因为 $y$ 已经合到 $x$ 上，所以就是选择 $x$）概率为 $0.5f(y,i-1)$。
   - $i>j$，则 $(x,y)$ 无论选择谁都不会影响，只需要最后 $j$ 轮符合要求即满足状态定义，故概率为 $f(y,j)$。
2. 接着，考虑合并根相同的两个子树 $(x\to y,x\to z)$。这两个子树状态第二维定义是相同的，所以 $f(y,i),f(z,j)$ 合并时 $i,j$ 这一坨边、$sz_y-1-i,sz_z-1-j$ 这一坨边分别合并，两者之间有明确顺序。合并时的概率，是 $0^x1^y,2^z3^w$ 归并，最终满足 $0,2$ 都在 $1,3$ 前的概率。最终的方案数有 $\dbinom {x+z}x\dbinom {y+w}y$ 种，总的归并方案有 $\dbinom{x+y+z+w}{x+y}$ 种，应该乘上 $\dfrac{\dbinom {x+z}x\dbinom {y+w}y}{\dbinom{x+y+z+w}{x+y}}$。

第一步是 $O(n^4)$ 的，第二步是 $O(n^3)$ 的。总时间复杂度 $O(n^4)$（前缀和一下就 $O(n^3)$ 了）。

---

## 作者：shadowice1984 (赞：8)

dp好题啊……

其实这题强行浮点数输出有点炸精度……

不过只要你和std错的一样的话卡精度什么的根本不存在
__________________

题意已经比较清楚了这里我们就不再赘述

# 本题题解

我们发现$n$的范围相当小只有50,这样的话我们似乎可以依次枚举每一个点,然后计算这个点在最终的点中出现的概率

那么我们可以$O(N!)$的枚举每一种删边的排列,之后对于每一种排列求出点i存活的概率,将这些概率加在一起最后除一个$(n-1)!$就行了

那么此时我们需要做相当重要的一步转化，否则我们无法理解接下来的转移方程是怎么一回事

这个做法基于这样的一个简单的原理,假设枚举到的点是i,我们仅仅保证每一个i最后存活下来的概率被计算一次，至于不合法的方案我们并不管他到底是怎么不合法了

我们做这样一个简单的转化

我们将合并一个边变成删除一个边的操作

然后接下来进行分情况讨论,如果这条边$(u,v)$连接的点都不是i点,那么假设删去这条边之后v和i变得不再联通我们就直接将v的标号改为i

否则我们以50%的概率从$u,v$中选择一个点x并将这两个点的标号都改成$x$同时删除$u,v$这条边

这样转化之后，如果最后所有点的标号全部为$i$的话我们认为点i成功存活了否则点i就不是最后的点

那么这样做的依据何在呢？

我们发现一个重要的事实是在每一个i存活下来的方案当中，如果i存活下来了，他必然在每一个合并操作当中都"顶替"了和他合并的另一个节点，那么这个操作就等价于把另一个点的编号也赋成i这个操作

注意这个操作在i被别的点顶替的时候操作就会变得不等价了，因为此时所有标号为i的点在原来的图上是一个点，我们应该更改所有标号为i的点的标号而不是仅仅更改一个点的标号

**不过这种情况下既然i已经gg了我们为什么要管这种情况呢？**

另一个情况是当我们合并一条和i相连的边时另一个点v已经是好几个点合并之后的结果了,此时我们似乎也会碰到刚才那种修改多个点的标号的情况,然而事实是我们仅仅考虑i成功存活的情况,既然被合并的点早晚都要变成i,并且它变不变成i仅仅和吸收它的点变不变成i有关，我们不如一开始就把这个点赋成i好了

所以这就是为什么我们无脑的把其中一个点赋成i的原因了，因为我们不考虑非法情况而仅仅考虑合法情况，在所有点都要变成i这个大前提下我们所作的转化就是等价的

那么根据这个我们就可以设计一个树形dp了,为了方便起见我们以i为根进行树形dp，这样树中的所有点都在i的子树里了

$dp(u,j)$表示当u的标号变成i的时候假如u的子树当中还剩下j条边,那么u子树中所有点变成i的概率是多少(注意这里的概率其实是乘上了一个(sizu-1)!的，因为我们计数的策略是枚举每一个删边的排列来计算方案)

那么接下来我们就考虑转移了

显然我们的转移可以分为两种转移

1.合并两个子树

2.加一条父亲边

那么我们先来考虑第一个转移如何转移呢

假设我们要合并两个状态$dp(u,p)$和$dp(v,q)$

那么此时我们可以很显然的得出合并之后的状态应该是$dp(u,p+q)$,根据我们状态的定义,所有点变成i的概率就是$dp(u,p)dp(v,q)$但是由于我们状态是枚举所有删边的排列然后再把每种排列对应的概率相加的计算方式,因此我们还需要考虑新生成的排列数目

显然我们之后剩下的边可以任意混合之前删掉的边也可以任意混合,所以我们乘上两个系数${p+q \choose p}$和${siz_{u}+siz_{v}-1-p-q \choose siz_{v}-q}$就行了

所以我们合并的转移方程就是

$$dp(u,n)=\sum_{p+q=n}dp(u,p)dp(v,q){p+q \choose p}{siz_{u}+siz_{v}-1-p-q \choose siz_{v}-q}$$

接下来让我们考虑加一条父亲边的转移

那么我们假如要计算$dp(u,k)$的话我们先枚举一下这剩下的k条边当中包不包含父亲边,假如不包含父亲边的话那么u这个子树就和fa的标号毫无关系(因为当fa的标号变成i之前u和fa之间的边就被割掉了,然后u的标号就被强制赋值成i了)

所以满足不包含父亲边的限制条件的方案数就是$dp(u,k)(siz_{u}-k)$了

如果剩下的k条边当中包含父亲边的话，我们就枚举父亲边断开的时候这k条边中还剩下几条边,由于此时断开的时候i这个标号有1/2的标号会消失,所以要乘上一个$0.5$的系数

所以我们的转移方程就是

$$dp(u,n)=(siz_{u}-n)dp(u,n)+0.5\sum_{i=0}^{n-1}dp(u,i)$$

然后我们就可以愉快的dp了~

边界条件是$dp(u,0)=1$

最后提取答案的时候是$dp(i,n-1)$的值

上代码~

```C
#include<cstdio>
#include<algorithm>
using namespace std;const int N=60;typedef long double ld;
int n;ld fac[N];ld dp[N][N];ld tr[N];
int v[2*N];int x[2*N];int ct;int al[N];int siz[N];
inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
inline ld c(int n,int m){return fac[n]/fac[m]/fac[n-m];}
inline void dfs(int u,int f)
{
    siz[u]=1;dp[u][0]=1;
    for(int i=al[u];i;i=x[i])
    {
        if(v[i]==f)continue;dfs(v[i],u);
        for(int j=0;j<siz[u]+siz[v[i]];j++)tr[j]=0;int tot=siz[u]+siz[v[i]]-1;
        for(int p=0;p<siz[u];p++)
            for(int q=0;q<=siz[v[i]];q++)
                tr[p+q]+=dp[u][p]*dp[v[i]][q]*c(p+q,p)*c(tot-p-q,siz[v[i]]-q);
        siz[u]+=siz[v[i]];for(int j=0;j<siz[u];j++)dp[u][j]=tr[j];
    //	printf("dfs %d\n",u);
    //	for(int j=0;j<=siz[u];j++)printf("%lf ",(double)dp[u][j]);printf("\n");
    }
    if(f!=0)
    {
        for(int i=0;i<=siz[u];i++)tr[i]=0;
        for(int i=0;i<siz[u];i++)
        {
            tr[i]+=(siz[u]-i)*dp[u][i];
            for(int j=i+1;j<=siz[u];j++)tr[j]+=dp[u][i]*0.5;
        }
        for(int i=0;i<=siz[u];i++)dp[u][i]=tr[i];
    }return;
}
int main()
{
    fac[0]=1;for(int i=1;i<=50;i++)fac[i]=fac[i-1]*i;
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),add(u,v),add(v,u);
    for(int i=1;i<=n;i++)
    {dfs(i,0);printf("%.10lf\n",(double)dp[i][n-1]/(double)fac[n-1]);}return 0;
}
```





---

## 作者：szh_AK_all (赞：6)

模拟赛场切了这题。

### 分析

首先枚举每个点 $i$，考虑其最后保留下来的概率。我们可以将 $i$ 看作树的根，然后进行 dp。

删边操作一共要进行 $n-1$ 次，操作时我们在乎的是 $i$ 点有没有在收缩中被删掉以及操作次数，所以可以记 $f_{x,j}$ 表示当前在点 $x$，其子树内还剩下 $j$ 条边没有操作时 $x$ 已经与 $i$ 合并在一起的概率。

对于 $x$ 的每个子节点 $y$，我们当前已经得到了 $f_y$，表示与 $y$ 子树有关的一些概率。而现在我们要计算 $y$ 对 $x$ 的影响，相当于要多考虑 $(x,y)$ 这条边。我们将操作过程展成一个序列，序列的某个前缀是我们当前已经确定的，余下的后缀我们还未考虑。于是可以分成下面两种情况计算：

- $(x,y)$ 这条边是关键的，也就是说当根 $i$ 向下合并时，我们要保证的是它不被删掉，所以在合并这条边时保留根的概率为 $\frac{1}{2}$。我们枚举这条边在操作序列的未操作后缀中排在第几个，显然贡献为 $f_y$ 的一个前缀和乘上 $\frac{1}{2}$。

- $(x,y)$ 这条边不是关键的，也就是这条边在根 $i$ 向下合并之前已经收缩过了，此时删除哪个点是无关紧要的，并且这条边在操作序列的已操作前缀中，那么操作序列的未操作后缀的长度是不变的，所以贡献为操作前缀的长度乘上 $f_y$ 的某个值。

我们可以用 $g_{y,j}$ 来记录子节点 $y$ 对于父亲 $x$ 的贡献，即当前在考虑了 $y$ 子树及 $(x,y)$ 这条边，还剩下 $j$ 条边没有操作时 $x$ 已经与 $i$ 合并在一起的概率。

现在考虑将 $x$ 所有儿子的贡献合并在一起。我们可以很经典的使用背包来解决这个问题，并开一个数组 $now$ 来记录已经遍历过的儿子的合起来的贡献，再开一个数组 $fu$ 来辅助计算当前合并的贡献。具体的，我们枚举前面的所有子节点以及当前的子节点还剩下几个边没操作，分别设为 $p,q$，那么考虑将两种操作序列合并起来的方案数。

令 $bian_x$ 表示 $x$ 子树内边的数量，$nowbian$ 表示当前已经遍历的子节点所包含的边数量。

对于已经遍历过的子节点，它们现在的操作序列是由长度为 $nowbian-p$ 的已操作前缀和长度为 $p$ 的未操作后缀组成的，对于当前考虑的子节点 $y$，它现在的操作序列是由长度为 $bian_y-q+1$ 的已操作前缀和长度为 $q$ 的未操作后缀组成的，现在我们将这两个序列合并，仍然要满足某个前缀是已操作的，余下的后缀是未操作的，显然方案数为 $C_{nowbian-p+bian_y-q+1,nowbian-p}\times C_{p+q,p}$，所以我们用 $C_{nowbian-p+bian_y-q+1,nowbian-p}\times C_{p+q,p}\times now_{p}\times g_{y,q}$ 来更新 $fu_{p+q}$，最后重新将 $fu$ 复制给 $now$。

由于我们转移时并不在乎当前操作序列出现的概率，而只是考虑了边收缩时删除哪个点的概率，所以最后的答案为 $\frac{f_{i,n-1}}{(n-1)!}$。

注意到模拟赛要求的是答案对 $10^9+7$ 取模，而 
Codeforces 需要输出小数。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7, N = 1005;
int n;
int f[N][N], bian[N], g[N][N], now[N][N];
int sum[N][N], er, c[N][N], fu[N], jie[N], inv[N];
vector<int>gg[N];

int C(int n, int m) {
	if (n < m)
		return 0;
	return c[n][m];
}

int qpow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b % 2)
			ans = 1LL * ans * a % mod;
		a = 1LL * a * a % mod;
		b /= 2;
	}
	return ans;
}

inline int mo(int x) {
	if (x >= mod)
		return x - mod;
	return x;
}

void dfs(int x, int fa) {
	now[x][0] = 1;
	for (int y : gg[x]) {
		if (y == fa)
			continue;
		dfs(y, x);
		for (int j = 0; j <= bian[y] + 1; j++) {
			//(x,y)是关键的，合并确保留下
			int su = 0;
			if (j)
				su = sum[y][j - 1];
			g[y][j] = 1LL * er * su % mod;
			//非关键，随意
			g[y][j] = mo(g[y][j] + 1LL * (bian[y] - j + 1) * f[y][j] % mod);
		}
		for (int j = 0; j <= bian[x] + bian[y] + 2; j++)
			fu[j] = 0;
		//bian[y]-p+bian[x]-q+1个板，选bian[x]-q个
		//p+q个板，选p个
		for (int p = 0; p <= bian[y] + 1; p++)
			for (int q = 0; q <= bian[x]; q++)
				fu[p + q] = mo(fu[p + q] + 1LL * g[y][p] * now[x][q] % mod * 1LL * C(bian[y] - p + bian[x] - q + 1,
				               bian[x] - q) % mod * 1LL * C(p + q,
				                       p) % mod);
		bian[x] += bian[y] + 1;
		for (int j = 0; j <= bian[x] + 1; j++)
			now[x][j] = fu[j];
	}
	for (int j = 0; j <= bian[x] + 1; j++)
		f[x][j] = now[x][j];
	sum[x][0] = f[x][0];
	for (int j = 1; j <= bian[x] + 1; j++)
		sum[x][j] = mo(sum[x][j - 1] + f[x][j]);
}

signed main() {
	freopen("shtree.in", "r", stdin);
	freopen("shtree.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	er = qpow(2, mod - 2);
	for (int i = 0; i <= 500; i++) {
		c[i][0] = 1;
		for (int j = 1; j <= i; j++)
			c[i][j] = mo(c[i - 1][j - 1] + c[i - 1][j]);
	}
	jie[0] = 1;
	for (int i = 1; i <= 500; i++)
		jie[i] = 1LL * jie[i - 1] * i % mod;
	for (int i = 0; i <= 500; i++)
		inv[i] = qpow(jie[i], mod - 2);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		gg[x].push_back(y);
		gg[y].push_back(x);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			bian[j] = 0;
			for (int k = 0; k <= n; k++)
				f[j][k] = g[j][k] = now[j][k] = sum[j][k] = 0;
		}
		dfs(i, 0);
		int ans = 1LL * f[i][n - 1] * inv[n - 1] % mod;
		cout << ans << " ";
	}
}
```

---

## 作者：SFlyer (赞：5)

对于每一个 $i$ 求出答案，可以把 $i$ 作为根即可。

考虑如果钦定了 $n-1$ 条边的删除顺序，那么是简单的。对于删除的时候不在 $rt$ 的旁边的边，对于答案没有影响，否则就是乘上 $\frac{1}{2}$ 的贡献（因为只有 $\frac{1}{2}$ 的概率合并到 $rt$）。

对于一个 $u\rightarrow v$ 的边（$dep_u<dep_v$），可以产生贡献的条件是 $rt\sim u$ 路径上没有比他删除时间大的。

尝试设计 $f_{i,x}$ 表示 $rt\sim i$ 的路径上最大的编号是 $x$（表示 rank）的字数内的期望贡献。发现转移儿子的时候不知道上面的路径中有啥，有点难以转移。转移的思路是，两种情况：$i\rightarrow j \in son(i)$ 这条边大于 $x$ 还是小于 $x$，各有一个概率，大于的情况还要加上新的贡献。两种情况加起来再累乘。因此要算出小于 $x$ 的概率。

因此要设计一种编号让上下不影响。发现 $n-1$ 个 $[0,1]$ 的随机变量可以解决这个问题。

那么有 $f_{i,x}=\prod_j (xf_{j,x}+\frac{1}{2}f_{j,y>x})$。第一个系数中的 $x$ 是小于 $x$ 概率，第二个就是有新的最大值的贡献了。

$\frac{1}{2}f_{j,y>x}=\int_{x}^1 f_{j,y}dy$，容易发现 $f_i$ 都是关于 $x$ 的多项式，直接维护每一个点对应的多项式就可以了。具体来说，$F(i)=\prod_j (xF(j)-G(j)+G(j)|_1)$，其中 $G(j)$ 是 $F(j)$ 的原函数。实现多项式加减，乘积，乘以一个 $x$，求积分即可。

最终的答案是 $F_{rt}(0)$，也就是常数项。

复杂度是书上背包的复杂度，可知是总共 $\mathcal{O}(n^3)$。

代码不是小数，不过都一样。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 5e2+2;
const ll mod = 1e9+7;
const ll i2 = (mod+1)/2;

struct poly {
    ll a[N],len;
    poly(){memset(a,0,sizeof a);}
    void init(){memset(a,0,sizeof a);}
    ll cal(ll x){
        ll ans=0;
        for (ll i=0,X=1; i<len; i++,X=X*x%mod){
            ans=(ans+X*a[i]%mod)%mod;
        }
        return ans;
    }
    poly operator * (const ll &x) const {
        poly c=poly();
        c.len=len;
        for (int i=0; i<len; i++) c.a[i]=a[i]*x%mod;
        return c;
    }
    poly operator + (const poly &b) const {
        poly c=poly();
        c.len=max(len,b.len);
        for (int i=0; i<c.len; i++) c.a[i]=(a[i]+b.a[i])%mod;
        return c;
    }
    poly operator - (const poly &b) const {
        poly c=poly();
        c.len=max(len,b.len);
        for (int i=0; i<c.len; i++) c.a[i]=(a[i]-b.a[i]+mod)%mod;
        return c;
    }
    poly operator * (const poly &b) const {
        poly c=poly();
        c.len=len+b.len-1;
        for (int i=0; i<len; i++){
            for (int j=0; j<b.len; j++){
                c.a[i+j]=(c.a[i+j]+a[i]*b.a[j]%mod)%mod;
            }
        }
        return c;
    }
};
poly tx(const poly &a){
    poly c=poly();
    c.len=a.len+1;
    for (int i=1; i<c.len; i++){
        c.a[i]=a.a[i-1];
    }
    return c;
}

ll pw(ll x,ll y){
    ll res=1;
    while (y){
        if (y&1){
            res=res*x%mod;
        }
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

ll iv[N];
poly integral(const poly &a){
    poly b;
    b.len=a.len+1;
    for (int i=0; i<a.len; i++){
        b.a[i+1]=a.a[i]*iv[i+1]%mod;
    }
    return b;
}

int n;
vector<int> g[N];
poly f[N];

void dfs(int u,int fa,int d){
    poly x;
    f[u].a[0]=1;
    f[u].len=1;
    for (auto v : g[u]){
        if (v^fa){
            dfs(v,u,d+1);
            poly tmp=tx(f[v]);
            poly it=integral(f[v]);
            it=it*i2;
            tmp.a[0]=(tmp.a[0]+it.cal(1))%mod;
            tmp=tmp-it;
            f[u]=f[u]*tmp;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n;
    for (int i=1; i<n; i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i=1; i<N; i++) iv[i]=pw(i,mod-2);
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++) f[j].init();
        dfs(i,0,0);
        cout<<f[i].a[0]<<" ";
    }
    cout<<"\n";
    return 0;
}
```

---

## 作者：CYZZ (赞：3)

**[CF1060F Shrinking Tree](https://www.luogu.com.cn/problem/CF1060F)**

尽可能说详细点。

对于每个 $rt$ 计算答案，不妨把 $rt$ 提为根。

考虑树形 dp。注意到 $u$ 子树外的删边情况可能影响到子树内的删边。

具体地，当 $u$ 被“缩”到 $rt$ 上后，删与 $u$ 相邻的边时只能选取 $u$ 的编号。

进一步，我们只关心 $u$ 何时被缩到 $rt$ 上，考虑将其计入状态。

设 $f_{u,i}$ 为：在删 $u$ 子树内第 $i$ 条边后，第 $i+1$ 条边前，$u$ 被缩到了 $rt$ 上。这种情况下删完 $u$ 子树的概率。

转移使用树形背包，把 $u$ 的儿子 $v$ 并入 $u$ 子树。

记 $g_{v,i}$ 为：**点 $u$ 并上 $v$ 子树**这棵树 的答案（具体定义类似 $f_{u,i}$）。

如何转移 $f'_{u,i}$？把 $u$ 缩到 $rt$ 上前后的删边组合一下。
$$
f'_{u,i+j} \larr f_{u,i} \cdot g_{v,j} \cdot \binom{i+j}{i} \cdot \binom{siz_u-1-i+siz_{v}+1-1-j}{siz_u-1-i} 
$$
如何计算 $g_{v,i}$？考虑 $(u,v)$ 的删法，枚举删 $(u,v)$ 时 $v$ 子树内已经删了 $k$ 条边。

1. $k<i$。此时删 $(u,v)$ 没有限制。$g_{v,i} \larr f_{v,i-1}$。
2. $k \ge i$。此时 $u$ 已经缩到 $rt$ 上了。$g_{v,i} \larr \frac{1}{2}f_{v,k}$。

答案为 $\frac{1}{(n-1)!}f_{rt,0}$。

树形背包复杂度 $O(n^2)$，枚举根 $O(n)$，总时间复杂度 $O(n^3)$。

[代码](https://codeforces.com/contest/1060/submission/329571673)

想理解转移方程建议多画图。

想知道如何想出 dp 状态建议阅读第 $2 \sim 5$ 行。

---

## 作者：MurataHimeko (赞：3)

摆了一周，随便做个题。

把当前正在计算答案的点当成根。如果所有边的选中时间已经确定，那么当一条边的选中时间是到根的这条链上的最大值时，答案的概率会乘 $1/2$。

为了方便，把一条边的时间当成权值下放到儿子节点上。根节点的权值为 $0$。

称一个节点是关键的，当且仅当这个点的权值是到根的链上的最大值。

设这样的节点有 $x$ 个，那么当前方案里根保留下来的概率为 $\frac{1}{2^x}$。

因为 $a^x = \sum_{i=0}^{x} (a-1)^i \binom{x}{i}$，所以只需要设 $f_{i,j}$ 表示 $i$ 的子树内钦定了 $j$ 个关键点的答案。

发现在合并 $dp$ 时的信息不够，考虑重新设 $f_{i,j,k}$ 表示 $i$ 子树内钦定了 $j$ 个关键点，最小的关键点的相对大小为 $k$ 的答案。

注意到 $j$ 这一维可以省掉，加入一个新的关键点时乘 $-1/2$ 即可。

前缀和优化可以做到 $O(n^3)$。不过这里偷懒写了 $O(n^4)$。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, f, t) for(int i(f); i <= t; ++i)
#define re(i, t) for(int i(1); i <= t; ++i)
#define per(i, t, f) for(int i(t); i >= f; --i)
#define pe(i, t) for(int i(t); i >= 1; --i) 
#define nx(i, u) for(int i(head[u]); i; i = e[i].nxt)
typedef long long ll; 
using namespace std;
typedef pair <int, int> pii;
#define pb push_back
#define fi first
#define se second
#define ix(l, r) ((l + r) | (l != r)) 
#define ls (ix(l, mid))
#define rs (ix(mid + 1, r))
#define mp(i, j) (make_pair(i, j))
#define inf (int)(1e9+7)
#define INF 0x3f3f3f3f3f3f3f3f

namespace IO {
char buf[1 << 21], *p1 = buf, *p2 = buf, buf1[1 << 21];
inline char gc() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}
template<class I>
inline void read(I &x) {x = 0;I f = 1;char c = gc();while (c < '0' || c > '9') {if (c == '-') {f = -1;} c = gc();}while (c >= '0' && c <= '9') {x = x * 10 + c - '0';c = gc();}x *= f;}
template<class I>
inline void write(I x) {if (x == 0) {putchar('0');return;}I tmp = x > 0 ? x : -x;if (x < 0) {putchar('-');}int cnt = 0;while (tmp > 0) {buf1[cnt++] = tmp % 10 + '0';tmp /= 10;}while (cnt > 0)putchar(buf1[--cnt]);}
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')
} using namespace IO;
#define look_memory cerr<<abs(&sT-&eD)/1024.0/1024<<'\n'
int sT;

const int N = 55;
int n, u, v;
struct node {
	int to, nxt;
}e[N<<1];

int head[N], cnt;

void add (int u, int v) {
	e[++cnt] = (node){v, head[u]};
	head[u] = cnt;
}

double c[N][N];
double f[N][N], g[N];
double fac[N];
int rt, siz[N];

void dfs (int u, int fa) {
	siz[u] = 0;
	f[u][0] = 1;
	nx(o, u) {
		int v = e[o].to;
		if(v == fa) continue;
		dfs(v, u);
		re(i, siz[u]) {
			g[i] = f[u][i];
			f[u][i] = 0;
		}
		re(i, siz[u]) {
			re(j, siz[v]) {
				rep(k, 0, j-1) {
					f[u][i+k] += g[i] * f[v][j] * c[i-1+k][k] * c[siz[u]-i+siz[v]-k][siz[v]-k];
				} 
				rep(k, 0, i-1) {
					f[u][j+k] += g[i] * f[v][j] * c[j-1+k][k] * c[siz[v]-j+siz[u]-k][siz[u]-k];
				}
			}
		}
		re(i, siz[v]) {
			rep(j, 0, siz[u]) {
				f[u][i+j] += f[v][i] * c[i-1+j][j] * c[siz[v]-i+siz[u]-j][siz[v]-i] * fac[siz[u]];
			}
		}
		re(i, siz[u]) {
			rep(j, 0, siz[v]) {
				f[u][i+j] += g[i] * c[i-1+j][j] * c[siz[u]-i+siz[v]-j][siz[v]-j] * fac[siz[v]];
			}
		}
		siz[u] += siz[v]; 
	}  
	f[u][0] = fac[siz[u]];
	if(u != rt) {
		++siz[u]; 
		f[u][0] *= siz[u];
		re(i, siz[u]) g[i] = f[u][i], f[u][i] = 0;
		rep(i, 2, siz[u]) f[u][i] = g[i-1] * (i-1);

		re(i, siz[u]) f[u][i] += -0.5 * fac[siz[u]-1];
		re(i, siz[u]) {
			rep(j, i, siz[u]) {
				f[u][i] += g[j] * -0.5;
			}
		}
		 
	}
}

int main () {
	read(n);
	rep(i, 0, n) {
		c[i][0] = 1;
		re(j, i) c[i][j] = c[i-1][j-1] + c[i-1][j];
	}
	re(i, n-1) {
		read(u),read(v);
		add(u,v),add(v,u);
	}
	fac[0] = 1;
	re(i,n) fac[i] = fac[i-1] *i;
	for(rt = 1; rt <= n; ++rt) {
		memset(f, 0, sizeof(f));
		dfs(rt, 0);
		double ans = 0;
		rep(i, 0, n) ans += f[rt][i];
		printf("%.10lf\n", ans / fac[n-1]);
	}
}
```


---

## 作者：yllcm (赞：3)

好像是一个不太一样的 $\mathcal{O}(n^4)$ 做法，只不过比较麻烦。

考虑对单点求答案，假设它是根。先对原问题做一步转化，发现问题有两个维度：删边的顺序、每次删边保留的点的编号。后者只需要保证如果两个点其中有一个是根，根一定保留就行。所以问题可以看做：计算所有删边顺序构成的排列的权值之和，排列的权值为 $2^{-c}$，$c$ 为删边的过程中两端有一个点是根的边的数量，下文将这些边称为“关键边”。

在原树上钦定一些边为关建边，设钦定 $i$ 条边的权值之和为 $g_i$，则根据二项式反演，最后的答案为：
$$
\sum_{i=0}^{n-1}2^{-i}\sum_{j\geq i}\binom{j}{i}(-1)^{j-i}g_j=\sum_{j=0}^{n-1} g_j(-1)^j\sum_{i\leq j}\binom{j}{i}(-1)^i 2^{-i}=\sum_{j=0}^{n-1}g_j\left(-\frac{1}{2}\right)^j
$$
考虑怎么求出上述式子。先进行进一步的观察，如果已经确定钦定了哪些边，排列需要满足什么条件才能合法。对于一条关键边，它需要满足它被缩掉之前，它的所有祖先边都已经被缩掉。转述一下就是，一条边在排列中的位置需要比它子树中所有边在排列中的位置靠前。

据此进行 DP，对于每个子树，维护它子树内的边的排列，再进行归并。$f_{u,i}$ 表示 $u$ 子树内边构成的排列中，最靠前的关建边位置为 $i$ 的权值总和。转移需要考虑两个问题：

* 归并两棵子树。
  * 若两棵子树中均有关键边，假设两棵子树大小分别为 $x,y$，最靠前的关建边位置为 $i,j$，则两个排列分别为 $\text{A}i\text{B}$ 和 $\text{C}j\text{D}$。不妨设 $i$ 为归并后排列较靠前的一个，那么分别构造 $i$ 以前的排列和 $i$ 以后的排列。
    * 对于 $i$ 以前的排列，枚举 $\text{C}$ 有多少个数在 $i$ 前面，设为 $s$，那么这一部分是 $i-1$ 和 $s$ 归并，系数为 $\dbinom{i-1+s}{s}$。
    * 对于 $i$ 以后的排列，两个排列剩下的部分分别为 $x-i$ 和 $y-s$，系数为 $\dbinom{x-i+y-s}{y-s}$。
    * 注意我们维护的是概率，所以需要先展开为排列再回到概率，系数为 $\dfrac{x!y!}{(x+y)!}$。
  * 若其中一个没有关键边，仿照上述过程讨论即可。
* 讨论是否钦定 $u$ 的父亲边为关键边。
  * 比较简单，需要注意由于关键边数量 $+1$，转移的时候需要额外乘上 $-\dfrac{1}{2}$ 的系数。

单次时间复杂度 $\mathcal{O}(n^3)$，总时间复杂度 $\mathcal{O}(n^4)$。

关于浮点数的问题，注意到 $50$ 以内最大的组合数也只在 $10^{14}$ 级别，可以放心运算。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define FR first
#define SE second
using namespace std;
inline int read() {
    int x = 0; bool op = 0;
    char c = getchar();
    while(!isdigit(c))op |= (c == '-'), c = getchar();
    while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return op ? -x : x;
}
const int N = 55;
db C[N][N];
void init() {
    C[0][0] = 1;
    for(int i = 1; i < N; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    return ;
}
int n;
int sz[N];
db f[N][N], g[N][N];
vector<int> G[N];
void dfs(int u, int fa) {
    for(int i = 0; i <= sz[u]; i++)f[u][i] = 0;
    sz[u] = 0; f[u][0] = 1;
    for(int v : G[u]) {
        if(v == fa)continue;
        dfs(v, u);
        for(int i = 0; i <= sz[u]; i++) {
            g[u][i] = f[u][i]; f[u][i] = 0;
        }
        f[u][0] += g[u][0] * f[v][0]; // 都没有钦定
        for(int i = 1; i <= sz[v]; i++) {
            for(int j = 0; j <= sz[u]; j++) {
                int x = sz[v] - i, y = sz[u] - j;
                db w = g[u][0] * f[v][i];
                w /= C[sz[u] + sz[v]][sz[u]];
                w *= C[i - 1 + j][j] * C[x + y][x];
                f[u][i + j] += w;
            }
        } // v 有钦定
        for(int i = 1; i <= sz[u]; i++) {
            for(int j = 0; j <= sz[v]; j++) {
                int x = sz[u] - i, y = sz[v] - j;
                db w = g[u][i] * f[v][0];
                w /= C[sz[u] + sz[v]][sz[u]];
                w *= C[i - 1 + j][j] * C[x + y][x];
                f[u][i + j] += w;
                // printf("w:%d %d %d %Lf %Lf\n", v, i, j, w, f[u][i + j]);
            }
        } // u 有钦定
        for(int i = 1; i <= sz[u]; i++) {
            for(int j = 1; j <= sz[v]; j++) {
                for(int k = 0; k < j; k++) {
                    int x = sz[u] - i, y = sz[v] - k;
                    db w = g[u][i] * f[v][j];
                    w /= C[sz[u] + sz[v]][sz[u]];
                    w *= C[i - 1 + k][k] * C[x + y][x];
                    f[u][i + k] += w;
                }
            }
        } // 都有钦定，u 的在前面
        for(int i = 1; i <= sz[u]; i++) {
            for(int j = 1; j <= sz[v]; j++) {
                for(int k = 0; k < i; k++) {
                    int x = sz[u] - k, y = sz[v] - j;
                    db w = g[u][i] * f[v][j];
                    w /= C[sz[u] + sz[v]][sz[u]];
                    w *= C[j - 1 + k][k] * C[x + y][x];
                    f[u][j + k] += w;
                }
            }
        } // 都有钦定，v 的在前面
        sz[u] += sz[v];
    }
    if(fa) {
        for(int i = 0; i <= sz[u]; i++) {
            g[u][i] = f[u][i]; f[u][i] = 0;
        }
        f[u][0] += g[u][0]; // 不钦定，之前没有
        for(int i = 1; i <= sz[u] + 1; i++) {
            f[u][i] -= g[u][0] / (sz[u] + 1) / 2;
        } // 钦定，之前没有
        for(int i = 1; i <= sz[u]; i++) {
            f[u][i + 1] += g[u][i] * i / (sz[u] + 1); // 不钦定，之前有
            for(int j = 1; j <= i; j++) {
                f[u][j] -= g[u][i] / (sz[u] + 1) / 2; // 钦定，之前有
            }
        }
    }
    sz[u]++;
    return ;
}
int main() { 
    init();
    n = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read();
        G[u].pb(v); G[v].pb(u);
    }
    for(int i = 1; i <= n; i++) {
        dfs(i, 0);
        db res = 0;
        for(int j = 0; j < n; j++)res += f[i][j];
        printf("%.10Lf\n", res);
    }
    return 0;
}
```




---

## 作者：Itst (赞：3)

$O(n^4)$ 的做法好妙啊 qwq 写一个比较套路的 $O(n^3)$ 做法，但因为数据范围太小所以跑起来跟 $O(n^4)$ 差别并不大。

前置：[CTS2019D2T3](https://www.luogu.com.cn/problem/P5405)

---

先进行一个转化：初始认为树上没有边，每个节点权值为 $1$。枚举一个长度为 $(n-1)!$ 的边集排列，按照这个排列依次加入每条边，加入一条边时将这条边所连接的两个连通块所有点的权值 $\times \frac{1}{2}$。

可以发现所有边均加入后每个点的权值就是在这个边集排列下成为最后节点的概率。

---

枚举节点 $root$ 计算它的答案，把 $root$ 拉作整棵树的根。

首先 $root$ 和它的某个儿子之间的边会让 $root$ 权值乘上 $\frac{1}{2}$。设该儿子是 $v$，$(root,v)$ 加入时，$v$ 会在某个连通块 $S$ 中。

此时对于边集 $\{(p,q)|p \in S \land q \in S\}$ 中的所有边，它一定会在 $(root,v)$ 之前加入。

而对于边集 $\{(p,q)|p \in S \land q \not\in S\}$，这其中的每一条边一定会在 $(root,v)$ 之后加入，且会对答案产生 $\frac{1}{2}$ 的贡献；而在 $(p,q)$ 加入的时候，$q$ 节点又可能在某一个连通块内，可以递归进入 $q$ 的子树考虑。

这样考虑有两个好处：第一个是可以找到边之间加入顺序的偏序关系，第二个是就有子问题的性质。

---

为了描述方便，设对于一个边集排列会让 $root$ 所在连通块变大的边（即会让权值乘上 $\frac{1}{2}$ 的边）称为主动边，反之称为被动边。加入一条主动边时，可能会导致一些被动边的产生（即上文中所提到的连通块 $S$ 中的边）。

之前的思路是枚举边集排列算主被动边，此时发现主被动边思路优势明显，故考虑枚举主动边和主动边产生的被动边。

考虑一张新图，新图上的点与原树上的边一一对应，如果原树上边 $(u,v)$ 需要在边 $(p,q)$ 之后加入则在新图上从 $(u,v)$ 向 $(p,q)$ 连一条边。故新图上会有这样一些边：

- 一条主动边向其产生的所有被动边连边；
- 一条主动边向与其最近的主动边祖先连边（如果存在）。

此时有：新图的所有拓扑序与所有满足当前枚举的主被动边情况的序列的反序一一对应，原因是所有与主动被动边相关的限制全部表现在了图上，而拓扑序正好满足所有偏序关系。

---

现在变成算拓扑序。注意到新图是树形图，因为对于所有被动边仅有产生它的主动边向它连边，而主动边的导出子图是一棵内向树森林。内向树或者外向树的拓扑序易于计算，但它并不是内向树或外向树。

如果做了前置会很自然地想到进行容斥（麻烦做一下前置我这里就不细写了 QAQ）。对主动边与被动边之间的边容斥，那么新图会变为内向森林，此时只需要考虑每个节点在新图上的 $size$。

被动边 $size=1$ 无需考虑，而主动边 $(u,v)$（$u$ 是 $v$ 原树上的父亲）在新图上的 $size$ 可以发现等于 $v$ 在原树上的子树大小减去原树 $v$ 的子树中选择不与主动边连边的被动边数量。那么每条主动边就只关心儿子里面被动边的选择情况了。

DP：设 $f_{i,j}$ 表示原树 $i$ 节点子树内有 $j$ 条被动边选择不与主动边连边，$i$ 节点内部的所有主动边和被动边的贡献总和。

先考虑对于某一个状态 $f_{u,p}$ 如何转移到父亲上，设原树上 $u$ 节点子树大小为 $size_u$：

- $(i,u)$ 是主动边，那么乘上计算拓扑序的贡献 $\frac{1}{size_u-p}$ 和选点概率 $\frac{1}{2}$ 并转移到 $f_{i,p}$；
- $(i,u)$ 是被动边且选择不与主动边连边，那么乘上容斥系数 $1$ 并转移到 $f_{i,p+1}$；
- $(i,u)$ 是被动边且选择与主动边连边，那么乘上容斥系数 $-1$ 并转移到 $f_{i,p}$。

对于多个子树的合并显然是树形背包。答案是 $\prod\limits_{(u,root) \in e} \sum\limits_{i=0}^{size_u-1} \frac{f_{u,i}}{2(size_u-i)}$，原因是 $root$ 的所有儿子必须要是主动边。

然后就做完了。单次的 DP 复杂度是 $O(n^2)$ 的，故总复杂度为 $O(n^3)$。

---

吐槽：容斥主动边和被动边之间的边要开 `long double`，容斥主动边和主动边之间的边开 `double` 就过了？？？

[Code](http://codeforces.com/contest/1060/submission/75706991)

---

## 作者：haochengw920 (赞：2)

刚刚看了多项式老哥的解法让我大受震撼……但是题解里写的状态定义和转移确实让我迷惑了一会。

这里给出一种让我认为更好理解的状态定义解释方式，似乎更加直接（也可能只是我题做少了，对那种定义方式没有很快反应过来）。

你考虑对于一个 $n$ 个点的菊花，假设要求中心的那个点为最终点，那么它需要分别 merge $n-1$ 个叶子，贡献是 $\left(\frac{1}{2}\right)^{n-1}$。

但是如果给这个中心再往外接一个编号为 $n+1$ 的点，钦定 $n+1$ 为最终点，那么它可以把 $(n, n+1)$ 这条边任意放在菊花里的 $n-1$ 条边的排列中，以截断在它前面的边，所以即为 $\sum_{i=1}^{n} \left(\frac{1}{2}\right)^i$。

对于一般的情况，我们钦定 $F_u(x)$ 为 $u$ 节点的子树内有多少条需要和 $u$ merge 的边的概率的生成函数。比如对于上面那个例子， $F_n(x)=x^{n-1}$，$n$ 的子树内只有可能有 $n-1$ 条边需要和 $n$ merge，其他系数均为 $0$。

（这么写只是为了方便理解，实际上 2022shexinyi 大神的状态和这个有一个偏移，那样更好实现。）

那么我们从 $u$ 往它的父亲 $\mathit{fa}$ 转移时，我们考虑 $(u, \mathit{fa})$ 这条边在子树内边的相对排名：

- 把 $(u, \mathit{fa})$ 插入到最前面，那么就是新增一条待合并边，即 $x F_u(x)$。
- 把 $(u, \mathit{fa})$ 插入到待合并边的中间，那么可以插入到任意位置，把这个位置前面的所有待合并边删除。你发现每次插入都是删除一个前缀，所以所有待合并边必然是一个后缀，因此概率相同。这个 sub 需要乘上 $\frac{1}{2}$ 的贡献（钦定 $(u, \mathit{fa})$ 坍缩向 $\mathit{fa}$）。

你可能会考虑把 $(u, \mathit{fa})$ 插入到最前面的概率（方案数）和插入到待合并边的中间的一个概率并不相同，可能需要乘上一个贡献。

但这其实是无所谓的，因为生成函数的每一次幂的系数相互独立，我们只需要保证合并到同一次的系数概率相同即可。

后面的部分就和 2022shexinyi 的题解一样了。

值得一提的是，这种做法在积分时恰好把合并的 $\frac{1}{2}$ 消去了。所以是有组合意义的刻画方式，可以把“随机合并”这个东西刻画成方案数的（类似于我们通过任意边的排列，把“随机选边”刻画成方案数）。那样可能更加优美。

但其实没有太大必要。生成函数本来不就是通过暴力推式子解决复杂组合问题的方法么。只要转换题意到恰好可以推出生成函数的地步，我们动脑的任务就已经完成了。

---

## 作者：crashed (赞：2)

&emsp;&emsp;**去往[原博客](https://www.cnblogs.com/crashed/p/13492935.html)食用更佳。**    
# 题目

&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/CF1060F)看题目。   

# 分析

&emsp;&emsp;好~~美妙~~的思维题目！    

&emsp;&emsp;显然我们可以对于每一个点计算它作为根的答案，这个答案又可以通过 DP 的方式求出来。      

&emsp;&emsp;直接求解概率比较复杂，而操作序列的总方案数比较好求，是 $(n-1)!$。不过，由于**同一个操作序列的成功概率会因为每条边的操作而不同**，因此我们实际上 DP 的不应该是方案数，而是**所有操作序列的成功概率的和**。最后将答案再除以 $(n-1)!$。    

&emsp;&emsp;设 $P(p)$ 为操作序列 $p$ 成功概率。DP 的东西可以理解为：   
$$
\sum_{p\text{是操作序列}} P(p)
$$
&emsp;&emsp;第一眼不难想到这样一个状态：   

&emsp;&emsp;$f(u,i)$：以 $u$ 为根的子树内，剩余的边有 $i$ 条，最后操作到只有一个 $u$ 的概率和。    

&emsp;&emsp;然后发现，如果仅仅局限性地要求根必须保留，就会忽略那些 " 先随意合并，再让根节点过来吞掉 " 的情况。    

&emsp;&emsp;因此，我们可以对状态加上一些限制：   

&emsp;&emsp;$f(u,i)$：以 $u$ 为根的子树内，剩余的边有 $i$ 条，且**当前的 $u$ 标号已经变成了根**的，继续操作留下根的概率和。    

&emsp;&emsp;这样起始状态就是 $f(u,0)=1$，目标状态就是 $f(x,n-1)$（假设我们计算 $x$ 为根的情况）。      

&emsp;&emsp;顺便再规定一下 $s_u$ 为 $u$ 的子树大小。

&emsp;&emsp;首先我们考虑一个比较简单的情况——一棵树 $u$，有 $x$ 条剩余边；另一棵树 $v$，有 $y$ 条剩余边。现在我们要把它们 " **粘** " 起来。这就意味着**边的数量不会变**。    

&emsp;&emsp;根据定义，我们实际上是考虑序列概率和的变化。也就自然分成两个部分：   

&emsp;&emsp;$\mathcal{1.}$序列**贡献的变化**。因为序列的成功概率是可以合并的，所以我们可以得到新的贡献为 $f(u,x)\times f(v,y)$。   

&emsp;&emsp;$\mathcal{2.}$序列**形态的变化**。考虑未操作边，合并的方案是 $\binom{x+y}{x}$；已操作边，合并的方案是 $\binom{s_u-x+s_v-y-2}{s_u-x-1}$。两种边的顺序不可调换，因而一种组合序列对应的方案数是 $\binom{x+y}{x}\times \binom{s_u-x+s_v-y-2}{s_u-x-1}$。    

&emsp;&emsp;可以发现，每种新序列的新形态的方案都相同，因而有新贡献为 $f(u,x)\times f(v,y)\times \binom{x+y}{x}\times \binom{s_u-x+s_v-y-2}{s_u-x-1}$。    

&emsp;&emsp;再考虑节点 $u$ 的转移。我们尝试合并上来 $v$。我们只需要想办法把 $(u,v)$ 合并到 $f(v)$ 的操作序列中，得到**新的贡献** $g(v)$（$g(v,i)$ 表示合并过后有 $i$ 条剩余边的概率和），就可以套用之前的计算方法合并 $u$ 和 $v$ 了。   

&emsp;&emsp;不妨枚举一下我们需要的 $g(v,i)$，再枚举一下 $f(v,j)$，考虑 $f(v,j)$ 对 $g(v,i)$ 的贡献。   

&emsp;&emsp;$\mathcal{1.}\ j>i$，显然这种情况下 $f(v,j)$ 不可能贡献到 $g(v,i)$。       

&emsp;&emsp;$\mathcal{2.}\ j<i$，考虑此时的合法合并：首先，当 $v$ 的子树内剩余 $i-1$ 条边的时候，$u$ 被替换为了根；接着，$v$ 继续合并直到剩余 $j$ 条边；然后，$(u,v)$ 合并并且**保留 $u$ 的标号**；最后进入到 $f(v,j)$。注意到 $u$ 必须保留，因此贡献为  $\frac 1 2f(v,j)$。    

&emsp;&emsp;$\mathcal{3.}\ j=i$，这意味着 $g(v,i)$ 要操作的边就是 $f(v,j)$，那么 $(u,v)$ 就应该随着 $v$ 子树中那些被删除的边一起删除。显然那些边总共有 $s_v-1-j$ 条，对应就有 $s_v-j$ 个空位。注意到 **$u$ 并不一定要保留**，因此贡献就是 $(s_v-j)f(v,j)$。   

&emsp;&emsp;所以我们可以首先处理出来 $g(v)$，然后按照上述方法进行合并，就可以得到 $f(x,n-1)$，除以 $(n-1)!$ 就得到了答案。    

&emsp;&emsp;可以发现这个转移本质上类似于树形背包，因此单次时间应该是 $O(n^2)$。总时间就是 $O(n^3)$。   

# 代码

```cpp
#include <cstdio>

typedef long long LL;

const int MAXN = 55;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

struct edge
{
	int to, nxt;
}Graph[MAXN << 1];

double fac[MAXN];
double f[MAXN][MAXN], g[MAXN], tmp[MAXN];
int head[MAXN], siz[MAXN];
int N, cnt;

void addEdge( const int from, const int to )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

void init()
{
	fac[0] = 1;
	for( int i = 1 ; i <= N ; i ++ )
		fac[i] = fac[i - 1] * i;
}

double C( const int n, const int m ) { return fac[n] / fac[m] / fac[n - m]; }

void DFS( const int u, const int fa )
{
	siz[u] = 1;
	f[u][0] = 1; for( int i = 1 ; i <= N ; i ++ ) f[u][i] = 0;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ( v = Graph[i].to ) ^ fa )
		{
			DFS( v, u );
			for( int k = 0 ; k <= N ; k ++ ) tmp[k] = g[k] = 0;
			for( int k = 0 ; k <= siz[v] ; k ++ )
				for( int j = 0 ; j <= k ; j ++ )
				{
					if( k == j ) g[k] += ( siz[v] - k ) * f[v][j];
					else g[k] += 0.5 * f[v][j];
				}
			for( int j = 0 ; j < siz[u] ; j ++ )
				for( int k = 0 ; k <= siz[v] ; k ++ )
					tmp[j + k] += f[u][j] * g[k] * C( j + k, j ) * C( siz[u] - j - 1 + siz[v] - k, siz[v] - k );
			siz[u] += siz[v];
			for( int k = 0 ; k < siz[u] ; k ++ ) f[u][k] = tmp[k];
		}
}

int main()
{
	read( N );
	for( int i = 1, a, b ; i < N ; i ++ )
		read( a ), read( b ), addEdge( a, b ), addEdge( b, a );
	init();
	for( int i = 1 ; i <= N ; i ++ ) 
	{
		DFS( i, 0 );
		printf( "%.10lf\n", f[i][N - 1] / fac[N - 1] );
	}
	return 0;
}
```


---

## 作者：wrpwrp (赞：2)

~~考试题目的小数版本~~  
可以先考虑一个暴力， 就是枚举一个点$i$作为最后的点， 然后枚举一个删边的序列。这个暴力显然比朴素的暴力复杂度要优秀一点。
考虑基于这个思想来写题。可以枚举一个点作为最后的点， 然后$dp$出所有的删边序列。算出在这个序列下$i$点保留下来的概率， 然后把所有的概率加起来，除以$(n - 1)!$也就是左右序列的个数就是答案了。
实际上下面的$dp$值是记录了一些序列， 然后取前一个前缀删掉。
考虑设$dp[u][i]$表示当$u$的子树里面还有$i$条边没有删掉的时候， 上述的概率和是多少。（模拟题意不难发现， 这题其实就是当做删边来理解并没有什么问题）。由于是概率的和， 实际上$dp$值里面包含的是很多个在当前子树内的边的删边排列的”合法概率和”。
为了方便， 我们把当前枚举的点设置为根。
由于这题和每一条边都有关， 考虑在合并子树之前先把当前点和当前点父亲节点的连边计算到答案里面。
我们考虑怎么计算这个东西。
我们先考虑一下当前的子树里面剩下的边有没有父亲这一条边。
+ 如果没有， 转移为$dp[u][i] += dp[u][i] * (sz[u] - i)$。意思就是子树里面原来删掉了$sz[u] - i - 1$，有$sz[u] - i$个间隙可以插入边。
+ 如果有， 由于我们为了方便， 考虑去掉当前点和父亲连边的影响， 在当前点处计算。枚举一下断掉父亲边的时候当前点子树内还剩下多少边。不难发现， 当前点和父亲点的连边断掉的时候是要强制选择的， 所以还要除以$2$。然后转移就是$dp[u][i] += \sum_{j <= i}dp[u][j] / 2$。
现在考虑怎么合并两个子树。由于我们处理的父边， 那这就比较好写了。

$$tmp[p+q]= dp[u][p]*dp[v][q]*C(p+q, q) * C(sz[u]+sz[v]-1-p-q, sz[v] -q)$$
意思就是把删边序列和留下来的边的序列分别合并， 用组合数就好了。
至于原因一个就是我们要保证两个子树内的相对删边的顺序不变才可以保证这是合法的。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define R register
#define LL long long

inline int read() {
	int x = 0, f = 1; char a = getchar();
	for(; a > '9' || a < '0'; a = getchar()) if(a == '-') f = -1;
	for(; a <= '9' && a >= '0'; a = getchar()) x = x * 10 + a - '0';
	return x * f;
}

const int N = 50 + 5;
const int P = 998244353;

inline int qpow(int x, int k) {
	int res = 1;
	while(k) { 
		if(k & 1) res = 1LL * x * res % P;
		k >>= 1; x = 1LL * x * x % P;
	} return res;
}

const int inv2 = qpow(2, P - 2);

inline int Add(int x, int y) { return x + y >= P ? x + y - P : x + y; }

int n;
int fac[N], ifac[N];
inline int C(int x, int y) { return 1LL * fac[x] * ifac[x - y] % P * ifac[y] % P; }
void init() {
	fac[0] = 1;
	for(R int i = 1; i <= 50; i ++) fac[i] = 1LL * fac[i - 1] * i % P;
	ifac[50] = qpow(fac[50], P - 2);
	for(R int i = 49; i >= 0; i --) ifac[i] = 1LL * ifac[i + 1] * (i + 1) % P;
}

int dp[N][N], tmp[N];

struct edge {
	int to, next;
}e[N << 1];
int cnt, head[N];
void add(int x, int y) { e[++ cnt] = {y, head[x]}; head[x] = cnt; }

int siz[N];

inline void dfs(int u, int f) {
	siz[u] = 1;
	dp[u][0] = 1;
	for(R int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		if(v == f) continue;
		dfs(v, u);
		for(R int j = 0; j < siz[u] + siz[v]; j ++) tmp[j] = 0;
		int tot = siz[u] + siz[v] - 1;
		for(R int p = 0; p < siz[u]; p ++)
			for(R int q = 0; q <= siz[v]; q ++) 
				tmp[p + q] = Add(tmp[p + q], 1LL * dp[u][p] * dp[v][q] % P * C(p + q, p) % P * C(tot - p - q, siz[v] - q) % P);
		siz[u] += siz[v];
		for(R int j = 0; j < siz[u]; j ++) dp[u][j] = tmp[j];
	}
	if(f) {
		for(R int i = 0; i <= siz[u]; i ++) tmp[i] = 0;
		for(R int i = 0; i < siz[u]; i ++) {
			tmp[i] = Add(tmp[i], 1LL * (siz[u] - i) * dp[u][i] % P);
			for(R int j = i + 1; j <= siz[u]; j ++)
				tmp[j] = Add(tmp[j], 1LL * dp[u][i] * inv2 % P);
		}
		for(R int i = 0; i <= siz[u]; i ++) dp[u][i] = tmp[i];
	}
}

signed main() {
	//#ifdef IN
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	//#endif
	init();
	n = read();
	for(R int i = 1; i < n; i ++) {
		int x = read(), y = read();
		add(x, y); add(y, x);
	}
	for(R int i = 1; i <= n; i ++) {
		dfs(i, 0);
		printf("%lld\n", 1LL * dp[i][n - 1] * ifac[n - 1] % P);
	}
	return 0;	
}
```
~~给一份带取模的代码~~

---

## 作者：Claire0918 (赞：1)

本题的数据范围是松的，下文考量 $n \leq 500$ 的加强版。

看到小数据范围套路地想到 DP，首先枚举当前要计算答案的点 $rt$，以其为根做 DP。不同的删边顺序有 $(n - 1)!$ 种，我们考虑最后再将其除掉。还剩 $\mathcal{O}(n^2)$ 的复杂度，考虑设出状态 $f_{u, i}$ 做树上背包，但是 $i$ 应当取怎样的意义呢？

我们发现一个事实：在 $u$ 到根的路径被缩完前，$u$ 子树内缩边保留哪个节点我们并不关心，因为其影响不到根节点是否保留。但是如果 $u$ 已经被缩成了根，那么在考虑缩 $u$ 的边时就仅能保留 $u$ 了。我们又注意到 $u$ 子树内的边数是 $\mathcal{O}(siz_u)$ 级别的，满足树上背包中 $i$ 的条件。

经过以上思路的引导，我们设 $f_{u, i}$ 表示在 $u$ 子树内，且要求在该子树内删去第 $i$ 条边后，第 $i + 1$ 条边前的某一时刻 $u$ 被缩成根的情况下最终保留根的概率。为了转移，我们先设 $g_{v, j}$ 表示要求 $v$ 子树内以及 $v$ 到父亲 $u$ 的边中删去第 $j$ 条后，第 $j + 1$ 条前时 $u$ 缩成根的情况下根保留的概率。如果我们能设法算出 $g_{v, j}$，那么就有转移
$$
f_{u, i} \times g_{v, j} \times {i + j \choose i} \times {siz_u - i - 1 + siz_v - j \choose siz_v - j} \to f'_{u, i + j}
$$
上式中的两个组合数是排列 $u$ 子树和 $v$ 子树内删边顺序的方案数。

为了计算 $g_{v, j}$，我们考虑要求 $v$ 到 $u$ 的边在 $v$ 子树内第 $k$ 条后，第 $k + 1$ 条前被删除，枚举 $k$ 并考量 $f_{v, \cdot}$ 的贡献。如果 $k \leq j$，也就是 $v$ 先缩到 $u$ 上，随后根才缩过来，此时删边的概率应当由 $u$ 计算，贡献为 $f_{v, j}$。如果 $k > j$，也就是 $u$ 先缩到根上，随后 $v$ 缩到根上，此时删边的贡献在 $v$ 处计算，贡献为 $\dfrac{1}{2}f_{v, k}$。

综上，我们有
$$
g_{v, j} = \sum_{k \leq j} f_{v, j} + \sum_{k > j} f_{v, k} = kf_{v, j} + \sum_{k > j}f_{v, k}
$$
倒着枚举 $j$ 维护 $f_{v, k}$ 后缀和即可计算。

综上，我们用树上背包完整地解决了这一问题，答案即为 $\dfrac{f_{rt, 0}}{(n - 1)!}$。时间复杂度 $\mathcal{O}(n^3)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;

const int maxn = 50 + 10;

struct{
    int v, nex;
} edge[maxn << 1];

int n;
int siz[maxn];
double c[maxn][maxn], f[maxn][maxn], g[maxn][maxn], tmp[maxn];
int head[maxn], top = 0;

inline void add(int u, int v, bool o = true){
    edge[++top].v = v, edge[top].nex = head[u], head[u] = top, o && (add(v, u, false), 1538);
}

inline void dfs(int u, int fa){
    siz[u] = 1, f[u][0] = 1;
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        if (v != fa){
            dfs(v, u);
            for (int j = 0; j <= siz[u] + siz[v]; j++){
                tmp[j] = 0;
            }
            for (int j = 0; j <= siz[u]; j++){
                for (int k = 0; k <= siz[v]; k++){
                    tmp[j + k] += f[u][j] * g[v][k] * c[j + k][j] * c[siz[u] - j - 1 + siz[v] - k][siz[v] - k];
                }
            }
            siz[u] += siz[v];
            for (int j = 0; j <= siz[u]; j++){
                f[u][j] = tmp[j];
            }
        }
    }
    double sum = 0;
    for (int j = siz[u]; ~j; j--){
        g[u][j] = sum, j && (g[u][j] += f[u][j - 1] * j), sum += f[u][j - 1] * 0.5;
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i < n; i++){
        int u, v;
        scanf("%d %d", &u, &v), add(u, v);
    }
    for (int i = 0; i <= n; i++){
        c[i][0] = 1;
        for (int j = 1; j <= i; j++){
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= n; i++){
        mem(f, 0), mem(g, 0);
        dfs(i, 0);
        for (int j = 1; j < n; j++){
            f[i][0] /= j;
        }
        printf("%lf\n", f[i][0]);
    }

return 0;
}
```

---

## 作者：良心WA题人 (赞：1)

一道相当牛逼的 DP 题。

删边并合并的操作有点抽象，考虑变成选择一条边，等概率将两侧的连通块染成其中一个连通块的颜色，问最终这个树每种颜色的概率。

这样就舒服很多了。数据范围很小，考虑枚举每个点作为根求这个根留下的概率。

在一个点与它的儿子的连边被操作或这个点被染成根的颜色之前，儿子无论如何染色都不会影响，否则任意一种关于儿子的染色都会影响。发现存在一个影响与不影响的分界点。想到定义状态 $f_{i,j}$ 表示数 $i$ 的子树内，要求最后 $j$ 次染色不能将根的连通块染成别的颜色的每种操作序列的概率和。

发现转移非常的直观！考虑枚举 $u$ 钦定了多少次操作和 $v$ 有多少次操作在 $u$ 钦定的操作之中。枚举 $u\to v$ 的操作在 $v$ 中的操作的排名，则 $v$ 需要钦定多少次操作是显然的。当 $u\to v$ 这条边的操作在 $u$ 被钦定的操作内贡献需要除以 $2$。两个操作穿插需要乘组合数，具体的转移可以看代码。

时间复杂度 $O(n^4)$，前缀和优化可以简单做到 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=54;
double f[NN][NN];
vector<int>g[NN];
int siz[NN];
long long C[NN][NN];
void dfs(int u,int fa)
{
	f[u][0]=1;
	siz[u]=1;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==fa)
			continue;
		dfs(v,u);
		double t[NN]={0};
		for(int j=0;j<siz[u];j++)
			for(int k=0;k<siz[v];k++)
			{
				t[j+k]+=f[u][j]*f[v][k]*C[j+k][j]*C[siz[u]+siz[v]-1-j-k][siz[u]-1-j]*(siz[v]-k);
				for(int l=0;l<=k;l++)
					t[j+k+1]+=f[u][j]*f[v][l]*C[j+k+1][j]*C[siz[u]+siz[v]-2-j-k][siz[u]-1-j]/2;
			}
		memcpy(f[u],t,sizeof(t));
		siz[u]+=siz[v];
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<=n;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		memset(f,0,sizeof(f));
		dfs(i,0);
		double ans=f[i][n-1];
		for(int j=n-1;j;j--)
			ans/=j;
		printf("%.7lf\n",ans);
	}
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：1)

困难的。

考虑对于每个点 $i$，将它提至根，求所有操作方案的概率和。

考虑 $i$ 现在已经和 $u$ 点合并起来，但是还没有和 $u$ 的子结点合并（下文称这种情况为 到达 $u$）。

考察 $u$ 的一个儿子 $v$，我们仅考虑 $v$ 的子树和 $(u,v)$ 边的方案数，且 $i$ 到达 $u$ 时 $v$ 子树内还剩 $j$ 条边，记为 $f_{v,j+1}$；$i$ 到达 $u$ 时子树内还剩 $j$ 条边，记为 $g_{u,j}$。

观察 $f_{v,j}$ 的转移，有两种情况：

- $i$ 先到达 $u$，又和 $v$ 合并：
	- 此时方案数为 $0.5\sum_{k=0}^{j-1}g_{v,k}$，即枚举 $u,v$ 合并的时间。
- $u$ 和 $v$ 合并，$i$ 又到达 $u$：
	- 此时方案数为 $(\text{siz}_v-j)g_{v,j}$，即枚举 $u,v$ 合并的时间。

观察 $g$ 的转移，即把所有子树的 $f$ 缝合：

对于子树的 $f$ 的操作，分为两种类型：$i$ 到达 $u$ 时 $v$ 子树之前的、之后的操作边。

形象地，

![https://cdn.luogu.com.cn/upload/pic/59362.png](https://cdn.luogu.com.cn/upload/pic/59362.png)

 _（来自 @ywy\_c\_asm）_ 


连续段是不会断开的。

$f_{v,x}g_{u,y}\dbinom{x+y}{x}\dbinom{\text{siz}_v-x+\text{siz}_u-y-1}{\text{siz}_u-y-1}\to g_{u,x+y}$。

使用树上背包的套路，时间复杂度 $\mathcal{O}(n^4)$，前缀和优化 $\mathcal{O}(n^3)$。

---

## 作者：Iris_Aurora (赞：0)

考场上把自己绕晕了，不知道怎么刻画一个合并后的状态，遗憾离场。

我们首先枚举每个点 $i$，把它作为树的根进行 dp。

很明显一条边有贡献当且仅当它的一个端点已经与 $i$ 合并在一起了。

我们令 $f_{u,j}$ 表示 $u$ 子树内还剩 $j$ 条边没有操作时点 $u$ 已经与 $i$ 合并在一起的概率。

（我的理解看作状态是对于每个点 $u$ 维护它子树里的边的操作序列，前 $siz_u-j$ 条边已经被操作，后 $j$ 条边未被操作）

我们考虑 $v\in son(u),(u,v)\in E$ 的贡献。

我们令 $g_{v,j}$ 表示 $v$ 子树内还剩 $j$ 条边没有操作时**点 $u$** 已经与 $i$ 合并在一起的概率（这个状态是用来给 $u$ 贡献的，所以我们要把 $(u,v)$ 考虑进去），我们考虑 $(u,v)$ 操作的时间以及它和 $f$ 数组的关系。

若 $(u,v)$ 在 $u$ 和 $i$ 合并之前就已经被操作（即 $u,v$ 在 $u,i$ 之前合并），概率为 $(siz_v-j+1)\times f_{v,j}$（即在 $f_{v,j}$ 维护的长度为 $siz_v-j$ 的已操作前缀中插入 $(u,v)$，且两边是可用的，所以方案数为 $siz_v-j+1$）。

若没有被操作（即 $j$ 条未操作的边中包含 $(u,v)$），那么在选择 $(u,v)$ 进行操作时必须保留 $i$，概率为 $\frac12\times \sum_{i=0}^{j-1} f_{v,i}$（即选择 $(u,v)$ 合并时还有 $i$ 条 $v$ 子树内的边没有操作，在 $(u,v)$ 前操作的边不会产生贡献（因为操作的是 $v$ 子树中的边此时 $u,v$ 还没有合并），然后选择 $i,v$ 合并的时候只能选择保留 $i$ 所以概率为 $\frac12$）。

然后我们很容易想到用树上背包来合并遍历过的儿子的贡献，记当前已遍历的儿子的答案为 $now$，总边数为 $Siz$。

合并是容易的，我们用数组 $tmp$ 辅助转移：

对于当前已遍历的儿子，$now$ 维护的是前 $Siz−i$ 条边已操作，后 $i$ 条边未操作的操作序列，对于当前考虑的子节点 $v$，$g_{v,j}$ 维护的是前 $siz_v+1-j$（$siz_v$ 是 $v$ 子树内的边数，$+1$ 是 $(u,v)$）条边已操作，后 $j$ 条边未操作的操作序列，现在我们要将这两个序列合并成一个前缀已操作，后缀未操作的序列，显然方案数为 $\binom{(Siz-i)+(siz_v+1-j)}{Siz-i}\times \binom{i+j}{i}$（在新序列一共 $(Siz-i)+(siz_v+1-j)$ 个已操作的位置中选 $Siz-i$ 个给 $now$ 中的已操作边，未操作的位置同理）。

$tmp_{i+j}=\binom{(Siz-i)+(siz_v+1-j)}{Siz-i}\times \binom{i+j}{i}\times now_{u,i}\times g_{v,j}$。

每次处理完一个儿子把 $tmp$ 赋值给 $now_u$。

最后的答案为 $\frac{f_{i,n-1}}{(n-1)!}$。（$(n-1)!$ 是操作序列的总方案数，因为是随机生成的所以每个操作序列生成的概率是 $\frac{1}{(n-1)!}$）。

所以其实 $f$ 数组维护的是操作序列乘它最后合并成为 $i$ 的概率，最后再乘这个操作序列本身生成的概率。

时间复杂度 $\mathcal{O}(n^3)$。

```c++
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
#define db long double
#define PII pair<int,int>
using namespace std;
const int MAXN = 5e2 + 10;
int n;
int siz[MAXN];
db f[MAXN][MAXN],g[MAXN][MAXN];
db now[MAXN][MAXN],tmp[MAXN];
db s[MAXN][MAXN];
db C[MAXN][MAXN];
vector<int>G[MAXN];
void dfs(int u,int fa){
	now[u][0]=1,siz[u]=0;
	for(int v:G[u]){
		if(v==fa) continue;
		dfs(v,u);
		FL(j,0,siz[v]+1){
			g[v][j]=0.5*(j?s[v][j-1]:0);
			g[v][j]+=(siz[v]-j+1)*f[v][j];
		}
		FL(j,0,siz[u]+siz[v]+1) tmp[j]=0;
		FL(i,0,siz[u])
			FL(j,0,siz[v]+1)
				tmp[i+j]+=now[u][i]*g[v][j]*C[siz[u]-i+siz[v]+1-j][siz[u]-i]*C[i+j][i];
		siz[u]+=siz[v]+1;
		FL(j,0,siz[u]) now[u][j]=tmp[j];
	}
	FL(j,0,siz[u]) f[u][j]=now[u][j];
	s[u][0]=f[u][0];
	FL(j,1,siz[u]) s[u][j]=s[u][j-1]+f[u][j];
}
signed main(){
//	freopen("shtree.in","r",stdin);
//	freopen("shtree.out","w",stdout);
	scanf("%d",&n);
	FL(i,0,500){
		C[i][0]=C[i][i]=1;
		FL(j,1,i-1)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	db Div=1;
	FL(i,1,n-1) Div=Div*1.0/i; 
	FL(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	FL(i,1,n){
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		dfs(i,0);
		printf("%.11Lf\n",f[i][n-1]*Div);
	}
}
```

---

