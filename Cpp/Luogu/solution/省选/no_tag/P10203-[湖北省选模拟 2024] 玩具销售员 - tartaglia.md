# [湖北省选模拟 2024] 玩具销售员 / tartaglia

## 题目背景

孩童时期的梦是最易碎的东西，哪怕放着不管，也总有一天会自己碎掉，所以，一定要有人来保护才行吧。

## 题目描述

“独眼小宝”是托克最喜欢的玩具，作为璃月最好的玩具销售员，达达利亚共招募了 $N$ 位经销商负责分销“独眼小宝”，$N$ 位经销商依次编号为 $1,2,\cdots,N$。

$N$ 位经销商中共形成了 $M$ 对交易关系，依次编号为 $1,2,\cdots,M$，第 $i$ 对交易关系联系起经销商 $u_i,v_i$。对于第 $i$ 对交易关系，当一方获知“独眼小宝”的生产情报时，将有 $\dfrac{p_i}{q_i}$ 的概率告知另一方。形式化地，经销商和他们之间的交易关系构成了一张无向图，**数据保证这张无向图是连通的、无自环的和无重边的。**

一些经销商 $a_1,a_2,\cdots,a_k(k>2)$ 构成**商业集团**，**当且仅当**存在 $k$ 组不同的交易关系，使得第 $w$ 组关系联系起经销商 $a_w,a_{w \bmod k+1}$。形式化地，一个商业集团对应 $k$ 名经销商和他们的交易关系图中的一个简单环。**一名经销商最多属于一个商业集团。**

现在，达达利亚希望对这些经销商进行测试，他共进行了 $Q$ 次**独立的**测试。对于第 $i$ 次测试，达达利亚将“独眼小宝”的生产情报告知了经销商 $S_i$，请问期望条件下，共有多少名经销商会得知该情报？

**可以证明，期望一定可以被表示为 $\dfrac{p}{q}$ 的形式，你需要输出 $p\cdot q^{-1}\pmod {998\ 244\ 353}$ 的值。**

## 说明/提示

### 样例解释 1

![](https://cdn.luogu.com.cn/upload/image_hosting/ii4noq6d.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/qz2o6jfu.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/dbojsfej.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/xq08n2l2.png)

上图展现了所有的 $16$ 种可能的图连通情况，从上至下，从左至右，依次编号为 $1\sim 16$。对于节点 $1$ 的询问，我们依次计算 $16$ 种情况中节点 $1$ 能到达的节点数和该情况对应的概率：

| 图编号 | 节点数 | 概率 | 期望 |
| :--: | :--: | :--: | :--: |
| $1$ | $4$ | $\frac{1}{60}$ | $\frac{1}{15}$ |
| $2$ | $1$ | $\frac{1}{60}$ | $\frac{1}{60}$ |
| $3$ | $4$ | $\frac{1}{30}$ | $\frac{2}{15}$ |
| $4$ | $4$ | $\frac{1}{15}$ | $\frac{4}{15}$ |
| $5$ | $4$ | $\frac{1}{60}$ | $\frac{1}{15}$ |
| $6$ | $1$ | $\frac{1}{30}$ | $\frac{1}{30}$ |
| $7$ | $1$ | $\frac{1}{15}$ | $\frac{1}{15}$ |
| $8$ | $1$ | $\frac{1}{60}$ | $\frac{1}{60}$ |
| $9$ | $3$ | $\frac{2}{15}$ | $\frac{2}{5}$ |
| $10$ | $2$ | $\frac{1}{30}$ | $\frac{1}{15}$ |
| $11$ | $3$ | $\frac{1}{15}$ | $\frac{1}{5}$ |
| $12$ | $1$ | $\frac{2}{15}$ | $\frac{2}{15}$ |
| $13$ | $1$ | $\frac{1}{30}$ | $\frac{1}{30}$ |
| $14$ | $1$ | $\frac{1}{15}$ | $\frac{1}{15}$ |
| $15$ | $2$ | $\frac{2}{15}$ | $\frac{4}{15}$ |
| $16$ | $1$ | $\frac{2}{15}$ | $\frac{2}{15}$ |

求和，得到 $E=\sum E_i=\frac{59}{30}\equiv 565\ 671\ 802\pmod{998\ 244\ 353}$。

### 子任务

对于所有测试数据，保证 $1 \leq N,M,Q \leq 3 \times 10^5$，$1 \le u_i,v_i \le N$，$u_i\neq v_i$，$1 \le p_i,q_i < 998\ 244 \ 353$，$1 \le S_i \le N$。

| 测试点编号 | $N,M,Q\le$ | 特殊性质 |
| :--: | :--: | :--: |
| $1\sim 2$ | $17$ | 无 |
| $3\sim 4$ | $2\times 10^3$ | A |
| $5\sim 7$ | $2\times 10^3$ | B |
| $8\sim 9$ | $2\times 10^3$ | 无 |
| $10\sim 13$ | $3\times 10^5$ | A |
| $14\sim 19$ | $3\times 10^5$ | B |
| $20\sim 25$ | $3\times 10^5$ | 无 |

特殊性质 A：不存在集团。

特殊性质 B：有且只有一个集团。

### 提示

在本题中，你可能需要使用较大的栈空间。在最终测试时，程序可使用的栈空间内存限制与题目内存限制一致。

若你使用 Linux 系统，可使用命令 `ulimit -s unlimited` 解除系统栈空间限制。若你使用 Windows 系统，可在编译命令后添加 `-Wl,--stack=1024000000`，以将系统栈空间限制修改为约 1024MiB。

## 样例 #1

### 输入

```
4 4 1
1 2 1 2
3 2 1 3
3 4 1 5
2 4 1 2
1```

### 输出

```
565671802```

## 样例 #2

### 输入

```
9 9 5
9 3 3 5
9 1 1 2
9 2 1 1
4 7 4 5
2 4 2 3
6 8 1 4
5 6 1 3
3 5 2 5
8 3 3 5
1
3
4
7
5```

### 输出

```
35936800
46584741
380663851
584039500
757135070```

## 样例 #3

### 输入

```
见选手目录下的 tartaglia/tartaglia3.in 与 tartaglia/tartaglia3.ans。```

### 输出

```
该样例满足测试点 1 ∼ 2 的限制。```

## 样例 #4

### 输入

```
见选手目录下的 tartaglia/tartaglia4.in 与 tartaglia/tartaglia4.ans。```

### 输出

```
该样例满足测试点 10 ∼ 13 的限制。```

## 样例 #5

### 输入

```
见选手目录下的 tartaglia/tartaglia5.in 与 tartaglia/tartaglia5.ans。```

### 输出

```
该样例满足测试点 14 ∼ 19 的限制。```

## 样例 #6

### 输入

```
见选手目录下的 tartaglia/tartaglia6.in 与 tartaglia/tartaglia6.ans。```

### 输出

```
```

# 题解

## 作者：览遍千秋 (赞：5)

本题解为官方题解。

---

### 树
设 $f[u]$ 为节点 $u$ 有水流时子树 $u$ 中有流水的节点数量的期望。
		
$f[u]=1+\sum_{v\in son_u} p_{(u,v)}f[v]$。
		
设 $g[u]$ 为节点 $u$ 的答案，则可以进行换根 DP 计算出 $g$。
		
$g[v]=f[v]+p_{(u,v)}(g[u]-p_{(u,v)}f[v])$
		
总时间复杂度为 $O(n+q)$。

### 暴力

$2^m$ 枚举边的联通情况，计算出对应的概率和各个连通块大小累加答案，可以在 $O((n+m)2^m)$ 时间内预处理出所有点的答案，最终时间复杂度 $O((n+m)2^m+q)$。

### 基环树

设 $f[u]$ 为环上的节点 $u$ 如果有水流下挂的子树中有水的期望节点数，这部分可以使用 Tree 部分的 DP 求得。
		
令环上所有边的概率乘积为 $P$，即 $P=\prod_{j\in C} p_j$，则 $g_i=\sum_{i,j\in C} (w(i,j)+\dfrac{P}{w(i,j)}-P)f_j$，其中 $w(i,j)$ 为环上节点 $i,j$ 任意一个方向上之间的边的概率之积。
		
对于该部分，断环成链后对边做前缀积，有 $s_i=\prod_{j\le i} p_j$。

对 $i\geq j$ 和 $i<j$ 分开讨论，得到 $g_i=s_i\sum_{j\le i}\dfrac{f_j}{s_j}+\dfrac{P}{s_i}\sum_{j\le i}f_js_j-P\sum_{j\le i}f_j+\dfrac{1}{s_i}\sum_{j>i}f_js_j+Ps_i\sum_{j>i}\dfrac{f_j}{s_j}-P\sum_{j>i}f_j$
		
正序循环处理 $j\le i$ 的 $\sum$，倒序循环处理 $j>i$ 的 $\sum$。即可求出环上每个点的 $g_u$，然后从环上向下做类似换根 DP 即可得到所有点的 $g$。
		
由于求出 $g$ 的部分需要求出前缀积 $s_i$ 的逆元，时间复杂度为 $O(n\log \operatorname{mod}+m)$。

### 点仙人掌
	
考虑这个图的 dfs 树，由于是点仙人掌，所以每个点只可能在一个简单环中，无向图的 dfs 树形如一棵树与若干条返祖边的组合，我们可以借鉴前述的 Tree 和 Pseudotree 两个部分的算法。
		
首先选择一个节点作为 dfs 树的树根进行 dfs，对于每个节点计算 $f[u]$，表示当该节点有水的时候在不走环边的情况下其 dfs 树子树中期望会有多少个节点有水，由于是点仙人掌，每个点、边均只会属于至多一个环。对于某个环的最顶部节点要特殊处理，环顶部节点的 $f[u]$ 应该为 $u$ 到该 dfs 树子树中的期望联通点数。

计算完成后可以得到根节点的 $g$，然后类似换根 DP 往下做，对于节点 $u$ - 非环节点 $v$，转移方式与树型的转移相同，当一个环的顶部节点得到 $u$ 之后就可以使用基环树的方法算出环上所有点的答案。
		
于是成功的预处理了所有点的答案。

---

### 标准解法

对于非环中的节点，$f[u]$ 代表若节点 $u$ 有水流，在其 dfs 树的子树中期望会有多少个点也会有水流，状态转移方程：
		
$$
g[u]=f[u]=\sum_{v\in son_u} p_{(u,v)}f[v]
$$
		
对于环中的节点，则 $f[u]$ 代表若节点 $u$ 有水流，在不经过环上的边的情况下其 dfs 树的子树中期望会有多少个点也会有水流，状态转移方程：
		
$$
g[u]=f[u]=\sum_{v\in son_u,(u,v)\notin C}p_{(u,v)}f[v]
$$

若该节点为环的顶部节点，则 $f[u]$ 代表若节点 $u$ 有水流，在其 dfs 树的子树中期望会有多少个点也会有水流，此时对于这个环上只考虑子树内的节点的情况下，将其视为一个基环树，根据基环树部分分的计算方法重新计算出 $f[u]$ ，有：
		
$$
f[u]=\sum_{v\in C} (w(u,v)+\dfrac{P}{w(u,v)}-P)f[v]
$$
		
$$
P=\prod_{(x,y)\in C} p_{(x,y)}
$$
		
综上可以计算出每个节点的 $f[u]$。

对于前述的计算每个节点的 $f[u]$ 方法中，如果开始 dfs 的节点为 $root$，那么 $ans[root]=f[root]$，对于其余节点，我们将使用类似换根 DP 的方法自上而下计算 $ans[u]$。
		
考虑从当前节点 $u$ 向 dfs 树上子节点 $v$ 进行推算。
		
我们只考虑 $u,v$ 不在同一个环中的情况。

容易发现此时 $v$ 一定是环的顶部节点，计算 $ans[v]$ 其实就是考虑 $(u,v)$ 这条边会给节点 $v$ 带来的改变，容易发现，$f[v]$ 只考虑了 dfs 树中 $v$ 下方的部分，我们将 $v$ 从 $ans[u]$ 中去掉即可得到一个类似子树的部分的贡献，将其加到 $f[v]$ 中即可得到 $ans[v]$，即：
		
$$
ans[v]=f[v]+p_{(u,v)}(ans[u]-f[v]\times p_{(u,v)})
$$

同时，当一个环的顶部节点的 $ans[]$ 确定之后，其实我们就可以算出环上每个点的 $ans[]$，参考基环树部分，我们需要的就是得到环上每个节点下挂的一个子树对于环上的对应子树根节点的贡献，但是在 Part1 中我们因为无法确认环的顶部节点的这部分值不能立即确定，但是现在可以确定了，对于顶部节点，我们考虑其 dfs 树父亲的那条边带来的额外贡献后就可以算出这个环上的全部 $ans[]$ 了，方法和基环树部分分一样。
		
然后发现，当 $u,v$ 在同一个环中时，$ans[]$ 一定都计算完毕了。

综上计算出了每个点的 $ans[]$，可以 $O(1)$ 回答询问。
		
总时间复杂度 $O((n+m)\log \text{mod}+Q)$。

---

## 作者：zyn_ (赞：1)

## 题意

给定一个点仙人掌 $G=(V,E)$，$|V|=n$，$|E|=m$。构建图 $G'=(V,E')$，对每条 $G$ 中的边 $e\in E$，有 $p(e)$ 的概率出现在 $G'$ 中。（令 $q=n$。）对所有点求出 $G'$ 中它所在的极大连通块的大小的期望。

## 树

显然要树形 DP。先钦定根为 $1$，设 $f_i$ 为 $i$ 子树中 $i$ 所在连通块的大小的期望。转移很简单：

$$
f_i=1+\sum_{j\in son_i}p((i,j))f_j
$$

现在 $f_1$ 就是点 $1$ 的答案。为了计算所有点的答案，考虑换根 DP，设 $g_i$ 为 $i$ 所在连通块中位于 $i$ 子树**外**的点数的期望。那么 $g_1=0$，且对于 $i>1$，

$$
g_i=p((fa_i,i))(g_{fa_i}+f_{fa_i}-p((fa_i,i))f_i)
$$

其中 $g_{fa_i}$ 是位于 $fa_i$ 子树外的点数期望，$f_{fa_i}-p((fa_i,i))f_i$ 是位于 $fa_i$ 子树内 $i$ 子树外的点数期望。

于是对于点 $i$，答案就是 $f_i+g_i$。

```cpp
ll f[N],g[N];
void dfs1(int p,int fa){
    f[p]=1;for(edge e:v[p])if(e.to!=fa)dfs1(e.to,p),f[p]=(f[p]+f[e.to]*e.w)%mod;
}
void dfs2(int p,int fa){
    for(edge e:v[p])if(e.to!=fa)g[e.to]=e.w*(g[p]+f[p]-e.w*f[e.to]%mod+mod)%mod,dfs2(e.to,p);
}
void solve(){
    dfs1(1,0);
    g[1]=0;dfs2(1,0);
    while(q--)scanf("%d",&s),printf("%lld\n",(f[s]+g[s])%mod);
}
```

## 仙人掌

现在不能直接说「子树」了。我们需要改变 $f_i$ 与 $g_i$ 的定义。

考虑将所有的环缩成一个点，得到一棵树（其实就是圆方树）。称缩出来的点是方点，其它点是圆点。于是方点对应一个环上的所有点，圆点对应一个不在环上的点。

我们定义一个点的「子树」，为这个点在圆方树上对应点的子树中的所有点，所对应的所有原图中的点所成集合。现在 $f_i,g_i$ 的定义就确定了，并且不难发现对于点 $i$，答案仍为 $f_i+g_i$。

（注：为避免重名，以下代码中的 `h` 数组指的就是 $g_i$。）

```cpp
int sq;
vector<int> rn[N<<1];
vector<edge> re[N<<1];
vector<ll> pro[N<<1];ll pr[N<<1];
int siz[N<<1];
int stk[N],top;edge se[N];bool instk[N];
int rp[N],rid[N],rpos[N];
void dfs1(int p,int fa){
    stk[++top]=p;instk[p]=true;
    for(edge e:v[p])if(e.to!=fa&&e.to!=rp[p]){
        if(instk[e.to]){
            // Find ring
            rp[e.to]=p;
            ++sq;
            int rc=top;
            while(1){
                rn[sq].push_back(stk[rc]);
                if(stk[rc]==e.to)break;
                --rc;
                re[sq].push_back(se[rc]);
            }
            reverse(rn[sq].begin(),rn[sq].end());
            reverse(re[sq].begin(),re[sq].end());
            re[sq].push_back(e);
            siz[sq]=rn[sq].size();
            pro[sq].push_back(re[sq][0].w);
            for(int i=1;i<siz[sq];++i)pro[sq].push_back(pro[sq][i-1]*re[sq][i].w%mod);
            pr[sq]=pro[sq][siz[sq]-1];
            for(int i=0;i<siz[sq];++i)rid[rn[sq][i]]=sq,rpos[rn[sq][i]]=i;
        }
        else se[top]=e,dfs1(e.to,p);
    }
    stk[top--]=0;instk[p]=false;
}
struct nedge{int u,bu,v,bv;ll w;};
vector<nedge> g[N<<1];
vector<ll> z[N<<1],l[N<<1],r[N<<1];
ll f[N],h[N];
void solve(){
    sq=n;
    // Build Tree
    dfs1(1,0);
    for(int i=1;i<=n;++i)if(!rid[i])rid[i]=i;
    for(int i=1;i<=m;++i)if(!(rid[a[i]]&&rid[a[i]]==rid[b[i]])){
        g[rid[a[i]]].push_back({rid[a[i]],rpos[a[i]],rid[b[i]],rpos[b[i]],p[i]});
        g[rid[b[i]]].push_back({rid[b[i]],rpos[b[i]],rid[a[i]],rpos[a[i]],p[i]});
        assert(rpos[a[i]]==0||rpos[b[i]]==0);
    }
    // Calc f_i
    dfs2(rid[1],0);
    // Calc g_i
    dfs3(rid[1],0);
    while(q--)scanf("%d",&s),printf("%lld\n",(f[s]+h[s])%mod);
}
```

### 计算 $f_i$

在圆方树上 DFS，考虑当前点 $i$ 是圆点还是方点。

设 $i$ 在圆方树上连向其儿子的所有边，在**原图中**对应的边集为 $E_i$。

#### $i$ 是圆点

这个简单。

$$
f_i=1+\sum_{(i,j)\in E_i} p((i,j))f_j
$$

#### $i$ 是方点

这个不好做。需要把 $i$ 对应的原图中环上所有点的 $f_j$ 算出来。对所有 $(j,k)\in E_i$，点 $j$ 期望有 $p((j,k))f_k$ 个在 $j$ 所在连通块且在 $k$「子树」中的点。把这个期望挂在点 $j$ 上，对所有环上的点，设这些期望之和为 $z_j-1$。

（接下来的 $i$ 就是指下标了。）设环上的点按顺时针顺序为 $j_1,j_2,\dots,j_s$（以下下标 $\bmod s$ 理解），$j_i$ 与 $j_{i+1}$ 之间的边有 $c_i=p((j_i,j_{i+1}))$ 的概率在 $G'$ 中。设从 $j_x$ 到 $j_y$ 顺时针方向的所有边均在 $G'$ 中的概率为 $r(x,y)$，逆时针方向的所有边均在 $G'$ 中的概率为 $l(x,y)$。于是

$$
l(x,y)=r(y,x)=\prod_{i=y}^{x-1}c_i \\
r(x,y)=l(y,x)=\prod_{i=x}^{y-1}c_i
$$

容易知 $j_x$ 与 $j_y$ 在 $G'$ 中连通的概率为 $1-(1-l(x,y))(1-r(x,y))=l(x,y)+r(x,y)-l(x,y)r(x,y)$。其中无论 $x,y$ 是多少，都有 $l(x,y)r(x,y)=\prod_{i=1}^s c_i=P$。因此

$$
f_{j_k}=z_k+\sum_{1\le i\le s,i\neq k}(l(k,i)+r(k,i)-P)z_i
$$

如果直接算，总体时间复杂度是 $O(n^2)$ 的，不能通过。考虑需要快速计算的是

$$
X_k=\sum_{1\le i\le s,i\neq k}l(k,i)z_i
$$

不难发现有关系（由题 $c_k\neq 0$）

$$
X_k=\frac{X_{k+1}-z_{k+1}}{c_k}+z_{k+1}\frac{P}{c_k}
$$

于是计算一项 $X_k$ 然后递推即可。

```cpp
void dfs2(int p,int fa){
    if(p<=n){
        f[p]=1;
        for(nedge e:g[p])if(e.v!=fa){
            dfs2(e.v,p);
            if(e.v<=n)f[p]=(f[p]+f[e.v]*e.w)%mod;
            else f[p]=(f[p]+f[rn[e.v][e.bv]]*e.w)%mod;
        }
    }
    else{
        z[p].clear();l[p].clear();r[p].clear();
        for(int i=0;i<siz[p];++i)z[p].push_back(1),l[p].push_back(0),r[p].push_back(0);
        for(nedge e:g[p])if(e.v!=fa){
            dfs2(e.v,p);
            if(e.v<=n)z[p][e.bu]=(z[p][e.bu]+f[e.v]*e.w)%mod;
            else z[p][e.bu]=(z[p][e.bu]+f[rn[e.v][e.bv]]*e.w)%mod;
        }
        ll sum=0;
        for(ll x:z[p])sum=(sum+x)%mod;
        r[p][0]=z[p][0];
        for(int i=1;i<siz[p];++i)r[p][0]=(r[p][0]+z[p][i]*pro[p][i-1])%mod;
        for(int i=1;i<siz[p];++i)r[p][i]=(r[p][i-1]-z[p][i-1]+mod+z[p][i-1]*pr[p])%mod*qpow(re[p][i-1].w,mod-2,mod)%mod;
        l[p][0]=z[p][0];
        for(int i=siz[p]-1;i>=1;--i)l[p][0]=(l[p][0]+z[p][i]*pr[p]%mod*qpow(pro[p][i-1],mod-2,mod))%mod;
        for(int i=siz[p]-1;i>=1;--i)l[p][i]=(l[p][(i+1)%siz[p]]-z[p][(i+1)%siz[p]]+mod+z[p][(i+1)%siz[p]]*pr[p])%mod*qpow(re[p][i].w,mod-2,mod)%mod;
        for(int i=0;i<siz[p];++i)f[rn[p][i]]=((l[p][i]+r[p][i]-z[p][i]-(sum-z[p][i])*pr[p])%mod+mod)%mod;
    }
}
```

### 计算 $g_i$

首先圆方树的根对应的所有原图中的点 $i$，都有 $g_i=0$。

考虑遍历到一个不为根的点 $i$。如果 $fa_i$ 为圆点则 $g_i$ 从 $g_{fa_i}$ 继承，令 $k=fa_i$；如果 $fa_i$ 为方点，设 $i$ 与 $fa_i$ 之间的边在原图上在 $fa_i$ 一侧的点是 $k$，则 $g_i$ 从 $g_k$ 继承。

#### $i$ 是圆点

这个简单。

$$
g_i=p((k,i))(g_{k}+f_{k}-p((k,i))f_i)
$$

#### $i$ 是方点

这个也不难做。设 $i$ 对应的环上的点顺时针顺序为 $j_1,j_2,\dots,j_s$，$i$ 与 $fa_i$ 之间的边在原图上在 $i$ 一侧的点是 $j_1$。那么

$$
g_{j_1}=p((k,j_1))(g_{k}+f_{k}-p((k,j_1))f_{j_1}) \\
g_{j_x}=(l(x,1)+r(x,1)-P)g_{j_1}
$$

其中 $l(x,y),r(x,y),P$ 与前文的定义相同。

于是用前缀积计算即可。

```cpp
void dfs3(int p,int fa){
    if(p<=n){
        for(nedge e:g[p])if(e.v!=fa){
            if(e.v<=n)h[e.v]=e.w*(h[p]+f[p]-e.w*f[e.v]%mod+mod)%mod;
            else{
                ll P;
                for(int i=0;i<siz[e.v];++i){
                    if(i==0)P=1;
                    else P=(pro[e.v][i-1]+pr[e.v]*qpow(pro[e.v][i-1],mod-2,mod)-pr[e.v]+mod)%mod;
                    h[rn[e.v][i]]=P*e.w%mod*(h[p]+f[p]-e.w*f[rn[e.v][e.bv]]%mod+mod)%mod;
                }
            }
            dfs3(e.v,p);
        }
    }
    else{
        for(nedge e:g[p])if(e.v!=fa){
            if(e.v<=n)h[e.v]=e.w*(h[rn[p][e.bu]]+f[rn[p][e.bu]]-e.w*f[e.v]%mod+mod)%mod;
            else{
                ll P;
                for(int i=0;i<siz[e.v];++i){
                    if(i==0)P=1;
                    else P=(pro[e.v][i-1]+pr[e.v]*qpow(pro[e.v][i-1],mod-2,mod)-pr[e.v]+mod)%mod;
                    h[rn[e.v][i]]=P*e.w%mod*(h[rn[p][e.bu]]+f[rn[p][e.bu]]-e.w*f[rn[e.v][e.bv]]%mod+mod)%mod;
                }
            }
            dfs3(e.v,p);
        }
    }
}
```

于是这道题就做完了。

时间复杂度 $O(n\log p)$，其中 $p$ 为模数。使用 $O(1)$ 求逆元应该可以做到 $O(n+\log p)$。

---

## 作者：dAniel_lele (赞：0)

显然，首先应该建出圆方树。

先计算根节点（当做 $1$ 号节点）的答案。考虑 $dp_i$ 表示 $i$ 子树内从 $i$ 开始传，期望有多少人能把消息传到他那里。

圆点的转移是容易的，考虑方点。先用前后缀和算出正半环和反半环传送到的点数量的期望。减去所有人之间都互相传送了的概率乘点数即可。具体转移见代码。

考虑换根 dp 计算所有节点的答案。圆点的换根也是容易的。如果说一个方点周围只有两个点，可以直接把父亲节点的值乘上传送了的概率加到子节点中。否则还是按照被正半环传送到的期望加反半环传送到的期望减所有人之间都互相传送了的概率乘点数来计算答案。观察到转一个点时，正半环的期望相当于乘上一条边出现的概率并减去某个点转一圈的概率。反半环类似。然后就可以直接做了。转移见代码。

总复杂度 $O(n\log n)$ 或 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
vector<int> vc[300005];
vector<int> tr[600005];
int dfn[300005],low[300005],cnt,stk[300005],top,scc=0,n;
int val[600005];
map<int,int> mp[300005];
void dfs(int now,int fa){
	dfn[now]=low[now]=++cnt;
	stk[++top]=now;
	for(auto v:vc[now]){
		if(v==fa) continue;
		if(!dfn[v]){
			dfs(v,now);
			if(low[v]>=dfn[now]){
				scc++;
				tr[scc].push_back(now);
				tr[now].push_back(scc);
				if(stk[top-1]!=now) val[scc]=mp[stk[top]][now];
				else val[scc]=1;
				while(stk[top]!=now){
					tr[scc].push_back(stk[top]);
					tr[stk[top]].push_back(scc);
					(val[scc]*=mp[stk[top-1]][stk[top]])%=mod;
					top--;
				}
			}
		}
		low[now]=min(low[now],low[v]);
	}
}
int pre[600005],suf[600005],sum[600005],dp[600005],ans[600005];
int tmp[600005];
void dfs1(int now,int fa){//第一次 dfs
	if(now<=n){
		for(auto v:tr[now]){
			if(v==fa) continue;
			dfs1(v,now);
			(dp[now]+=dp[v])%=mod;
		}
		(dp[now]+=1)%=mod;
	}
	else{
		for(auto v:tr[now]){
			if(v==fa) continue;
			dfs1(v,now);
			(sum[now]+=dp[v])%=mod;
		}
		for(int i=tr[now].size()-1;i>=1;i--) pre[now]=((pre[now]+dp[tr[now][i]])*mp[tr[now][i]][tr[now][i-1]])%mod;
		for(int i=1;i<tr[now].size();i++) suf[now]=((suf[now]+dp[tr[now][i]])*mp[tr[now][i]][tr[now][(i+1)%tr[now].size()]])%mod;
		dp[now]=(pre[now]+suf[now]+mod-sum[now]*val[now]%mod)%mod;
	}
}
void dfs2(int now,int fa){//第二次 dfs（换根）
	if(now<=n){
		ans[now]=dp[now];
		for(auto v:tr[now]){
			if(v==fa) continue;
			(dp[now]+=mod-dp[v])%=mod;
			dfs2(v,now);
			(dp[now]+=dp[v])%=mod;
		}
	}
	else{
		if(tr[now].size()==2){
			(dp[tr[now][1]]+=dp[fa]*mp[tr[now][0]][tr[now][1]])%=mod;
			dfs2(tr[now][1],now);
			return ;
		}
		(sum[now]+=dp[fa])%=mod;
		for(int i=tr[now].size()-1;i>=1;i--){
			pre[now]=((pre[now]+dp[tr[now][(i+1)%tr[now].size()]])*mp[tr[now][i]][tr[now][(i+1)%tr[now].size()]]+mod-dp[tr[now][i]]*val[now]%mod)%mod,(tmp[tr[now][i]]+=pre[now])%=mod;
		}
		for(int i=1;i<tr[now].size();i++){
			suf[now]=((suf[now]+dp[tr[now][i-1]])*mp[tr[now][i]][tr[now][i-1]]+mod-dp[tr[now][i]]*val[now]%mod)%mod,(tmp[tr[now][i]]+=suf[now])%=mod;
		}
		for(auto v:tr[now]){
			if(v==fa) continue;
			int tp=(tmp[v]+mod-(sum[now]+mod-dp[v])*val[now]%mod)%mod;
			(dp[v]+=tp)%=mod;
			dfs2(v,now);
		}
	}
}
signed main(){
	int m,t; cin>>n>>m>>t;
	for(int i=1;i<=m;i++){
		int u,v,p,q; cin>>u>>v>>p>>q;
		(p*=qp(q,mod-2))%=mod;
		mp[u][v]=mp[v][u]=p;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	scc=n;
	dfs(1,0);
	dfs1(1,0);
	dfs2(1,0);
	while(t--){
		int p; cin>>p;
		cout<<ans[p]<<"\n";
	}
	return 0;
}
```

---

## 作者：Jsxts_ (赞：0)

仙人掌上问题练手题。前置知识是【模板】静态仙人掌。

看到图是个点仙人掌，考虑建出圆方树：对每个环，建一个方点代表环，然后向每个环上的节点连边。

然后关于边权的赋值，我们尽量想让 $v$ 对 $u$ 的贡献表示为在圆方树的链上边权乘积：在链上自然直接为这条边出现的概率，在环上的话，考虑钦定环中在圆方树上 dfs 序最小的那个点 $u$ 为顶点，它向对应方点连权值为 $1$ 的边，其他圆点 $v$ 向方点连的边权值为：该圆点与顶点连通的概率，容斥计算出其概率为 $d+\dfrac{s}{d}-s$，其中 $d$ 为 $v$ 环上到 $u$ 的其中一条路径的乘积，$s$ 表示整个环边权的积。

这样赋权，可以让一条直链（从祖先到后代的链）对应答案为链上边权的积，所以若对于根节点求答案，我们可以直接设出 $f_x$ 表示 $x$ 子树内所有圆点到 $x$ 的边权积的和。

但是，对于一个不为根的点求答案，不能简单地换根求每个点到其它点边权积之和，因为若 $u,v$ 的 LCA 是个方点，那么边权之积不能正确的表示 $v$ 对 $u$ 的贡献。这时，离 LCA 最近的两个点到方点的边权都为到顶点的答案（但实际要的是它们之间的答案！）。不过对于 LCA 为圆点，这样求都是对的。

所以，考虑在换根时分讨，求出 $x$ 子树外所有点对其的贡献：在 dfs 到 $fa_x$ 时计算，若 $fa_x$ 为圆点，则可以简单地继承它其它儿子到 $x$ 的乘积和。否则：

考虑列出 $fa_x$ 的所有儿子 $v_1,v_2,\dots v_k$，那么，$v_2\sim v_k$ 对 $v_1$ 的贡献为：

$$\sum_{i=2}^k (pv_i+\dfrac{S}{pv_i}-S)\times f_i$$

其中 $pv_i=\prod_{j=2}^iw(v_{j-1},v_j)$，$S$ 为整个环的边权之积。

这个式子，在 $v_1\to v_2$ 时容易 $O(1)$ 计算新的贡献，所以这题就做完了。

---

## 作者：qczrz6v4nhp6u (赞：0)

感觉，这个题是不是有点太板了？

再板也不一定打的出来，哦哦哦。

### Solution

显然点 $u$ 的期望可以表示为 $\sum_{v}p(u,v)$，其中 $p(u,v)$ 表示 $u$ 与 $v$ 连通的概率。

考虑树的部分分。显然此时 $p(u,v)=\prod_{(x,y)\in\text{path}(u,v)}w(x,y)$，其中 $w(x,y)$ 是边 $(x,y)$ 激活的概率。

设 $f_u=\sum_{v\in\text{subtree}(u)}p(u,v)$，$g_u=\sum_{v\notin\text{subtree}(u)}p(u,v)$。不难得到转移式：

$$
f_u=1+\sum_{v\in\text{son}(u)}f_v\times w(u,v)\\
g_v=(g_u+f_u-f_v\times w(u,v))\times w(u,v)
$$

考虑正解。由于图是点仙人掌，我们考虑建出广义圆方树并在上面执行类似的 DP。

考虑环上两点 $u,v$ 连通的概率。环上 $u,v$ 之间有两条路径，显然两条路径任意一条连通即可。设两条路径连通的概率分别为 $r,s$，则 $p(u,v)=r+s-r\times s$（减去 $r\times s$ 是因为整个环激活的状态算了两次）。

同样设 $f_u$ 和 $g_u$，分别表示广义圆方树上 $u$ 的子树概率和及子树外概率和。综合树部分的 DP 和环上两点连通概率转移即可，由于转移式较难描述，此处不再展开。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int N=6e5+5,mod=998244353;
int n,m,q;
ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
struct edge{
	int y;ll z;
	edge(){y=z=0;}
	edge(int _y,ll _z){y=_y,z=_z;}
};
vector<edge> Gr[N],T[N];
int dfn[N],low[N],dfc,sta[N],top,tot;
ll w[N],iw[N],to[N];
void dfs(int x,int fa){
	dfn[x]=low[x]=++dfc;
	sta[++top]=x;
	iw[x]=qpow(w[x],mod-2);
	for(auto &o:Gr[x])
		if(!dfn[o.y]){
			w[o.y]=w[x]*o.z%mod;
			dfs(o.y,x);
			low[x]=min(low[x],low[o.y]);
			if(low[o.y]>=dfn[x]){
				int u;++tot;
				w[tot]=w[sta[top]]*iw[x]%mod*to[sta[top]]%mod;
				do{
					u=sta[top--];w[u]=w[u]*iw[x]%mod;
					T[tot].emplace_back(u,w[u]);
					T[u].emplace_back(tot,w[u]);
				}while(u!=o.y);
				T[tot].emplace_back(x,1);
				T[x].emplace_back(tot,1);
			}
		}
		else if(o.y!=fa&&dfn[o.y]<low[x]){
			low[x]=dfn[o.y];
			to[x]=o.z;
		}
}
ll f[N],g[N];
void dp1(int x,int fa){
	if(x<=n){
		f[x]=1;
		for(auto &o:T[x])
			if(o.y!=fa){
				dp1(o.y,x);
				f[x]=(f[x]+f[o.y])%mod;
			}
	}
	else{
		for(auto &o:T[x])
			if(o.y!=fa){
				dp1(o.y,x);
				f[x]=(f[x]+(w[o.y]+w[x]*iw[o.y]-w[x]+mod)%mod*f[o.y])%mod;
			}
	}
}
void dp2(int x,int fa){
	if(x<=n){
		for(auto &o:T[x])
			if(o.y!=fa){
				g[o.y]=(g[x]+f[x]-f[o.y]+mod)%mod;
				dp2(o.y,x);
			}
	}
	else{
		ll sum1=0,sum2=0,sum3=0;
		for(auto &o:T[x])
			if(o.y!=fa){
				g[o.y]=(g[o.y]+sum1*w[o.y]+sum2*iw[o.y]+(mod-sum3)*w[x])%mod;
				sum1=(sum1+w[x]*iw[o.y]%mod*f[o.y])%mod;
				sum2=(sum2+w[o.y]*f[o.y])%mod;
				sum3=(sum3+f[o.y])%mod;
			}
		reverse(T[x].begin(),T[x].end());
		sum1=w[x]*g[x]%mod,sum2=g[x],sum3=g[x];
		for(auto &o:T[x])
			if(o.y!=fa){
				g[o.y]=(g[o.y]+sum1*iw[o.y]+sum2*w[o.y]+(mod-sum3)*w[x])%mod;
				sum1=(sum1+w[x]*w[o.y]%mod*f[o.y])%mod;
				sum2=(sum2+iw[o.y]*f[o.y])%mod;
				sum3=(sum3+f[o.y])%mod;
			}
		for(auto &o:T[x])
			if(o.y!=fa)
				dp2(o.y,x);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int x,y,p,q;ll v;
		cin>>x>>y>>p>>q;v=p*qpow(q,mod-2)%mod;
		Gr[x].emplace_back(y,v);
		Gr[y].emplace_back(x,v);
	}
	w[1]=1,tot=n;
	dfs(1,0);
	for(int i=1;i<=tot;i++)
		iw[i]=qpow(w[i],mod-2);
	dp1(1,0);
	dp2(1,0);
	while(q--){
		int u;
		cin>>u;
		cout<<(f[u]+g[u])%mod<<'\n';
	}
	return 0;
}
```

---

