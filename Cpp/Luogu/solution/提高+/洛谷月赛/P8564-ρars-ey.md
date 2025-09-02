# ρars/ey

## 题目描述

给定一颗有 $n$ 个节点的有根树，其中根节点是 $1$。你可以进行若干次以下操作:

-   选择一个节点，删去其子树内除其以外的点。

此操作的代价为 $f_i$，其中 $i$ 是你选择的节点子树大小。

你希望删掉除了 $1$ 以外的所有点，请问代价的最小值是多少？







## 说明/提示

【样例解释】

先删除节点 $8$ 的子树内除了它自身的 $5$ 个点，再删除节点 $1$ 的子树内除了它自身的 $2$ 个点，代价为 $f_6+f_3=63744$。可以证明这是最小的代价。

【数据范围】

对于所有数据，保证 $1\le n\le 5000$，$1\le f_i\le 10^9$。
$$
\def\arraystretch{1.5}
\begin{array}{c|c|c}\hline 
\textbf{测试点编号}&\bm{~~~~~~~~n\le~~~~~~~~}&~~~~\textbf{特殊限制}~~~~\cr\hline 
\textsf1\sim \sf2 & 8& \cr\hline 
\sf3\sim 6 & 15&  \cr\hline 
\sf7\sim 8 & 400&\textsf{A}\cr\hline 
\textsf9 & 400 &\sf B\cr\hline 
\sf10\sim 12 & 400&\cr\hline
\sf13\sim 14 & &\sf C\cr\hline
\sf15\sim 20 & &\cr\hline
\end{array}
$$

$\textsf A$：保证树上所有点度数均小于等于 $2$，其中 $1$ 号点度数为 $1$。

$\textsf B$：保证树上只有 $1$ 号点度数大于等于 $2$。

$\textsf C$：保证树随机生成，随机生成方式是，对于 $i\ge 2$，从 $[1,i-1]$ 中随机一个整数 $x$，在 $x$ 与 $i$ 之间连边。然后随机打乱所有节点的编号。

## 样例 #1

### 输入

```
8
11000 18640 32793 36187 45104 64932 66425 
6 8
3 6
3 7
1 8
1 4
3 5
2 7```

### 输出

```
63744```

# 题解

## 作者：retep (赞：23)

## 题目简述

给定一棵有 $n$ 个节点的树，树上的每个节点都可以选择将子树中除自己外的节点全部删除，删除不同的个数会有相应的代价。求将除根节点以外的节点全部删除需要的最小代价是多少。

数据范围：$1\le n \le 5000$

算法标签：树上背包、动态规划、

题目传送门：[P8564 ρars/ey](https://www.luogu.com.cn/problem/P8564)

## 题目分析

强烈建议没做过的同学去做一下 [P2014 [CTSC1997] 选课](https://www.luogu.com.cn/problem/P2014)，这是树上背包的模板题，而本题也是用树上背包解决的。

本蒟蒻读完题第一个联想到的是经典的切钻石问题（或者切木头），切成不同大小能卖不同的价格，问最大价值。这里则变成了树上的切割，所以考虑用树上DP来解决。

$f_{i,j}$ 表示 $i$ 号节点删除子树中 $j$ 个节点的最小代价。那么答案就是 $f_{1,sz-1}$，其中 $sz$ 表示子树大小。

树上DP最重要的是理清楚儿子节点应该给父亲节点什么信息，父亲节点怎么处理这些信息。此处，父亲节点应该从所有儿子那里得到一个数组，表示删除子树中不同数量的节点的最小代价，也就是 $f_{i,j}$。父亲节点要用这些数组完成自己的数组，方便爷爷使用。

现在假设父亲节点要删 $j$ 个节点，分两种情况讨论：

**第一种情况**，父亲节点自己不去删，因为自己去删了最后一定只剩自己了，大部分时候不能这样。于是要将需要删除的数量合理分配给所有儿子，找到最小代价。我们不能枚举所有的分配方案，因为有几个儿子节点就需要几层循环来枚举，这样太慢了。所以考虑用动态规划的方式：$g_{i,j}$ 表示前 $i$ 个儿子节点，总共删除 $j$ 个节点，最少需要代价是多少。我们像切割钻石那样枚举当前儿子删多少，剩下的给前面的儿子删，那么转移方程为：

$$g_{i,j}=\min_{x=1}^{j}(g_{i-1,j-x}+cost(x))$$

$x$ 表示当前儿子节点删多少个节点，cost则是代价函数。

$g$ 数组算到最后一层得到的就是当前节点的 $f$ 数组，再加上面的方程式显然可以滚动数组，所以不需要新定义一个 $g$ 数组（这里是为了方便讲解），直接在 $f$ 里计算即可。

**第二种情况**，父亲节点自己主动删。这里需要注意的是，并不是说父亲去删了，其它节点都可以摆烂了，大部分情况是需要在父亲删之前为他分担代价的。同时，不管儿子怎么奋斗，他们都删不了自己，这时就需要父亲出马来完善 $f$ 数组了。因为父亲主动去删的话就一定只剩他自己一个了，所以 $j$ 一定等于 $sz-1$。再加上第一种情况里算好的 $g$ 数组（或者说是有一点点不完整的 $f$），我们只需要枚举一下儿子删多少，剩下的留给父亲删就行了，于是有：

$$ f_{i,sz-1}= \min_{x=1}^{sz-1}(f_{i,x}+cost(sz-x-1))$$

$x$ 表示儿子们一共删多少个节点，所以父亲就需要删 $sz-x-1$。

聪明读者可能会有疑惑，到头来这不是 $n^3$ 的吗？这不铁定超时吗？的确是这样的，但我们只需要加一点点小优化即可：**依靠子树大小，加入循环的上下界**。这是树上背包的经典优化，看似简单，实则作用巨大。

## code

```cpp
#include<bits/stdc++.h>
#define N 5005
#define ll long long
using namespace std;

int n,cost[N];
vector<int> to[N];
ll f[N][N],sz[N],son[N];


void solve(int u,int fa){ //树上背包
	sz[u]=1;
    // 第一种情况
	for(int i=0,cnt=0;i<to[u].size();i++){
		int v=to[u][i];
		if(v==fa)continue;
		solve(v,u); cnt++; //cnt记录第几个儿子，因为可能遇到连到父亲节点的边
		for(int x=sz[u]+sz[v]-cnt-1;x>=1;x--) //滚动数组
			for(int y=max(x-sz[u],1ll);y<=x&&y<sz[v];y++) //一共删x个，y个给当前儿子删，注意此处两个循环的上下界
				f[u][x]=min(f[u][x],f[u][x-y]+f[v][y]);
		sz[u]+=sz[v]; //计算子树大小
	}
    // 第二种情况
	for(int i=0;i<=sz[u]-son[u]-1;i++) //儿子节点删i个
		f[u][sz[u]-1]=min(f[u][sz[u]-1],f[u][i]+cost[sz[u]-i-1]);
}

int main(){
	cin>>n;
	for(int i=1;i<n;i++)
		cin>>cost[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		son[i]=to[i].size()-1;
		for(int j=1;j<=n;j++)f[i][j]=1e13;
	}
	son[1]++,solve(1,0);
	cout<<f[1][sz[1]-1];
	return 0;
}
```

---

## 作者：JohnVictor (赞：8)

与题目中不同的是，代价数组用 $a$ 而不是 $f$ 来表示。

#### Solution 1

直接爆搜，每一次枚举一个可以删除的节点删除它的子树。

时间复杂度 $O(n \times n!)$，期望通过数据点 $1 \sim 2$。

#### Solution 2

我们枚举所有节点是否被操作。这里操作指在某个时刻删除它的子树。

注意一个节点操作的时候它子树中的节点都已经完成了操作或者永远也不会再操作，我们就能确定删除它的时候究竟删除了几个节点，进而计算出最后的答案。

时间复杂度 $O(n2^n)$ 或者 $O(n^22^n)$，期望通过数据点 $1\sim 6$。

#### Solution 3

如果树是一个菊花，答案只能是 $a_n$。

如果树是一条链，那么令 $f_i$ 为 $i$ 被操作过，并且删掉 $i$ 的子树内的点需要的最小代价。

类似普通的背包，我们有转移 $f_i=\min\limits_{j>i}(f_j+a_{j-i+1})$，直接实现就能达到 $O(n^2)$ 的复杂度。

期望通过数据点 $7\sim 9$。

#### Solution 4

我们试图扩展链的情况的 dp。我们还是用相同的状态定义，但是转移显得没有那么简单，因为转移式变成的如下形式：（其中 $S$ 遍历 $i$ 为根的子树中所有包含 $i$ 的连通块；$L(s)$ 表示 $S$ 的叶子集合）

$f_i=\min \limits_S (\sum\limits_{t \in L(s)}f_t+a_{|S|})$

枚举 $S$ 的复杂度显得不可接受，回忆一般的树形 dp，我们希望所有信息能直接通过儿子来转移。

为此，我们修改状态如下：令 $f_{i,t}$ 为以 $i$ 为根的子树中，去掉一个包含 $i$ 的连通块并且剩下的部分恰好需要删除 $t$ 条边的最小代价。（为什么会这么设计会在后面的转移式中发现）最终要求的答案便是 $f_{1,n-1}$。

这个状态的好处是我们可以类似背包的转移。具体地，设点 $i$ 的儿子依次为 $v_1,v_2,\cdots,v_k$，那么我们有以下转移：（这里 $sz(i)$ 表示以 $i$ 为根的子树中的边数，很容易 $O(n)$ dfs 预处理）

$f_{i,j}=\min\limits_{u_1+u_2+\cdots +u_k=j}(f_{v_1,u_1}+f_{v_2,u_2}+\cdots+f_{v_k,u_k})$

$f_{i,sz(i)}=\min\limits_{j}f_{i,j}+a_{sz(i)-j}$

这里，第一个式子是 $i$ 没有被操作的情况，第二个式子则是 $i$ 被操作的情况。

第一个式子的转移虽然不能暴力枚举，但是这是一个背包问题，我们可以单独处理。

具体地，令 $g_{i,l,j}$ 为 $\min\limits_{u_1+u_2+\cdots +u_l=j}(f_{v_1,u_1}+f_{v_2,u_2}+\cdots+f_{v_l,u_l})$，那么要求的就是 $g_{i,k,j}$，并且类似背包有如下转移：

$g_{i,l+1,j}=\min \limits_{0 \le t\le j} g_{i,l,t}+f_{v_{l+1},j-t}$

复杂度乍一看是 $O(n^3)$ 的，但实际上是 $O(n^2)$ 的，证明同树形背包。期望通过所有数据点。

#### 实现细节

要达到 $O(n^2)$ 必须要把 $f,g$ 处理到合适的长度（$g$ 的 $i,k$ 这两维其实都可以不用记录的），这里说明一下上面的转移式中并没有体现具体的范围。由于 $f_i$ 只用处理 $sz(i)$ 位，$g_{i,l}$ 也只用处理 $i$ 的前 $l$ 个子树的大小和的位数。这时的复杂度证明才和树形背包类似。 如果实现不当，退化成 $O(n^3)$ 的做法只能通过数据点 $1\sim 12$，有可能通过数据点 $13\sim 14$。



---

## 作者：Dregen_Yor (赞：6)

### [更好的阅读体验。](http://dregen-yor.123ds.tk/index.php/2022/10/05/p8564/)

# 思路

根据题意，我们不难发现这是一道树上背包问题。

我们可以考虑用 $dp_{i,j}$ 表示 $i$ 的子树中剩余 $j$ 个节点的最小花费，但是这样的话 $j$ 的信息很难维护，于是我们考虑用 $dp_{i,j}$ 表示 $i$ 的子树中删除 $j$ 个节点的最小花费，这样的话状态就容易维护的多了。

状态转移方程：$dp_{i,j}=\min_{v \in son(i)}\{dp_{i, j - k} + dp_{v,k}\}$，其中 $v$ 表示 $i$ 的子树。

这个状态转移方程最多到 $siz_i-sumson_i-1$ 个节点的情况，对于清空当前点的子树的最小花费，有如下转移方程：

$dp_{i,siz_{i} - 1} = \min\{dp_{i,j} + f_{siz_{i} - 	j}\}$。

同时这道题还有几个需要注意的点，先放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,f[5010],dp[5010][5010],siz[5010];
vector <int> G[5010];
void dfs(int x,int fa){
	int sum=0;
	siz[x]++;
	dp[x][0]=0;
	for(auto to:G[x]){
		if(to==fa){
			continue;
		}
		dfs(to,x);
		sum+=siz[to];
		for(int i=sum-1;i;i--){//点1
			for(int j=max(1ll,i-siz[x]);j<=i&&j<=siz[to]-1;j++){//点2
				if(dp[to][j]>2e9||dp[x][i-j]>2e9)continue;
				dp[x][i]=min(dp[x][i],dp[x][i-j]+dp[to][j]);
			}
		}
		siz[x]+=siz[to];
	}
	for(int i=0;i<siz[x]-1;i++){
		dp[x][siz[x]-1]=min(dp[x][i]+f[siz[x]-i],dp[x][siz[x]-1]);
	}
//	dp[x][0]=0;
}
signed main(){
	scanf("%lld",&n);
	memset(dp,0x7f,sizeof(dp));
	int l,r;
	l+r>>1;
	for(int i=2;i<n;i++){
		scanf("%lld",&f[i]);
	}
	f[1]=0;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs(1,1);
	printf("%lld",dp[1][n-1]);
	return 0;
}
```

### 点1

我们合并子树状态时，考虑新的子树中删去 $j$ 个点的情况，但这种情况只能是从新的子树中找 $j$ 个点的情况，所以必须要从后往前统计答案，如果从前往后统计答案的话，可能会出现这样一种情况：从子树中选 $k$ 个点删除，但他是从新子树中删去 $2$ 个点和删去 $k-2$ 个点的情况合并而来，而且这 $k$ 个点中存在重复计算的情况。

### 点2

设合并前当前新子树前的子树的大小为 $siz_x$，合并后子树的大小为 $sum$，其中删去节点数量为 $[siz_x,sum-1]$ 之间的情况一定是从前面 $siz_x$ 的情况合并过来的。所以只要考虑从子树中删去 $i-siz_x$ 到 $siz_to$ 个节点的情况即可，这样可以节省大量的复杂度，没有这一句只能得 $70$ 分。 

---

## 作者：farfarqwq (赞：3)

树上背包板子（？）题。

## 正文

### 思路
考虑背包，$dp_{i,j}$ 表示以 $i$ 为根的子树上删 $j$ 个点的最小代价。

显然可以从子树中转移过来（$p$ 为当前点，$v$ 为子节点），转移方程：

$$dp_{p,j+k} = \min(dp_{p,j+k},dp_{p,j}+dp_{v,k})$$

但这样是不够的，他光从子树转过来并没有自己执行操作，所以可以 for 循环一遍枚举已删掉的数量把剩下的（当然除了他自己）删掉，转移方程为：

$$dp_{p,size_{p}-1}=\min(dp_{p,size_{p}-1},dp_{p,i}+f_{size_{p}-i})$$

其中 $size_{p}$ 表示以 $p$ 为根的子树的大小。

核心代码：
```cpp
void dfs(int p, int f) {
	sz[p] = 1;//相当于size[p]
	dp[p][0] = 0;//初始化不选的情况
	for (int i = 1; i < N; i++)
		dp[p][i] = 1e18;//自己写初始化是怕memset爆long long
	for (int i = head[p]; i; i = e[i].next) {
		int v = e[i].v;
		if (v != f) {
			dfs(v, p);
			for (int j = sz[p] - 1; j >= 0; j--)//注意要倒着循环
				for (int k = sz[v] - 1; k >= 0; k--)
					dp[p][j + k] = min(dp[p][j + k], dp[p][j] + dp[v][k]);//转移
			sz[p] += sz[v]
		}
	}
	for (int i = 0; i < sz[p] - 1; i++)
		dp[p][sz[p] - 1] = min(dp[p][sz[p] - 1], dp[p][i] + F[sz[p] - i]);//把剩下的删掉
}
```

### 关于复杂度

很多人会发现每个子树在合并时都有两个 size 相乘的复杂的。总的复杂度应该是 $O(n^3)$ 的，其实不然。

我们把枚举删几个看成 $u,v$ 里面各选一个点，这样每个点在合并子树的过程中相当于选出两个 lca（最近公共祖先）是 $u$ 的点。两个点不可能有多个 lca，所以复杂度是 $O(n^2)$ 的。

## 后记

祝大家 CSP-JS RP++！

---

upd on 2022-10-18：修改了一些隐私问题

upd on 2023-07-24：修改了一些隐私问题&笔误、修改了公式格式

---

## 作者：ykzzldz (赞：2)

这篇题解着重说一下背包时的枚举上下界的问题。

设 $f_{u,i}$ 表示 $u$ 子树删 $i$ 个点最小代价，分两部分转移：

1. 删 $u$：$f_{u,siz_u-1}=\min(f_{u,siz_u-1},f_{u,i}+w_{siz_u-i})$

2. 不删 $u$：$f_{u,i}=\min(f_{u,i},f_{u,i-j}+f_{v,j})$

方程中，$siz_u$ 表示 $u$ 的子树大小，$v$ 为 $u$ 的儿子。

这样转移，如果你随便定上下界，只能获得 $n^3$ 和随机数据的 $70$ 分。

这里，先给出不删 $u$ 部分的转移（因为删 $u$ 部分的转移复杂度为 $O(n^2)$，是可以接受的）：

```cpp
for(int i=siz[u]+siz[v];i>=1;i--){
    for(int j=max(1ll,i-siz[u]);j<=min(siz[v],i);j++){
        f[u][i]=min(f[u][i],f[u][i-j]+f[v][j]);
    }
}
siz[u]+=siz[v];
```

这样的总复杂度是 $O(n^2)$ 的，转移 $v$ 删的个数时我们只需要从 $i-siz_u$ 枚举到 $\min(siz_v,i)$ 即可，前者是因为在 $j$ 更小时一定无解（因为要满足 $v$ 删的加其他删的等于 $u$ 删的），后者比较明显，就不多说了。这样写完后，我们发现就可以成功通过了，这是树上背包的一个经典的优化。

---

## 作者：Steve_xh (赞：2)

# 题意

[题目传送门](https://www.luogu.com.cn/problem/P8564)

**题目大意：**

给定一棵有根树，每次可以选择其中一个结点删去**其子树内除了该结点的所有结点**并根据子树大小花费，求将整棵树删至仅剩根结点所需最少花费。

# 思路

为了避免歧义，以下称题目中的 $f$ 为 $a$。

显然树形 dp。考虑设计状态 $f_{i,j}$ 为结点 $i$ 删去 $j$ 个结点的最小花费（此处状态若设计成删成仅剩 $j$ 个结点则会更难维护）。提前 dfs 出每个结点的子树大小 $sz_i$，则答案为 $f_{1,(sz_1-1)}$。

如何转移？在 dfs 时对于每个结点 $i$，考虑枚举自己可以提前删去的结点数 $k$，再枚举仅操作每个儿子可以删去的结点数 $j$，则此时在子树 $i$ 上总共删去的结点有 $(k+j)$ 个，且可以分成**自己删去的**和**当前枚举到的儿子删去的**两部分。若设当前枚举到的儿子为 $v$，则这两部分分别表示为 $f_{i,k}$ 与 $f_{v,j}$。那么此处可得转移方程：

$$f_{i,k+j}=\min(f_{i,k+j}, f_{i,k}+f_{v,j})$$

注意此时的转移是通过操作儿子得到的答案。不仅如此，我们还要考虑操作父结点并加上花费可以得到的答案。设此时 $sz_i$ 为 $s$，枚举当前结点可以提前删去的结点数 $m$，则剩下的结点需要通过花费 $a_{s-m}$ 来删除。那么此处可得转移方程：

$$f_{i,s-1}=\min(f_{i,s-1}, f_{i,m}+a_{s-m})$$

把上述方法结合即可得到正解……吗？

每层 dfs 会出现**枚举儿子**、**枚举当前结点删除结点数量**与**枚举当前儿子删除结点数量**，共三重循环即共 $\Theta(n^3)$。那么如何优化？注意到在操作某个子树时无论如何都不能把其根结点删掉。根据这一点可以知道在仅操作结点 $i$ 的直接儿子时，最终会剩下的结点数量（除去结点 $i$）一定不小于 $i$ 的直接儿子数量。图示理解如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/cv0bat2x.png)

那么可以统计每个结点的直接儿子数量 $num_i$，在枚举 $i$ 总共删去的结点数量时以其作为上界。别看这点优化之小，实则可以跑得飞快。

# 代码

```cpp
#include<bits/stdc++.h>
#define inf (1145141919810ll)
#define toi (e[i].to)
#define fore(now,i) for(int i=head[now];i;i=e[i].next)
#define int long long
using namespace std;
int n,cnt=0,head[5005],f[5005][5005],p[5005],num[5005],a[5005],sz[5005];
// f为dp数组，p用于记录父亲，num, a, sz同正文描述
struct EDGE{
    int to,next;
}e[5005<<1|1];
inline void addedge(int u,int v){
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;

    e[++cnt].to=u;
    e[cnt].next=head[v];
    head[v]=cnt;
}
void dfs0(int now,int fa){ // 首次dfs出基本信息
    // cerr<<"now: "<<now<<" fa: "<<fa<<'\n';
    p[now]=fa;
    sz[now]=1;
    num[now]=0;
    fore(now,i){
        if(toi==fa)
            continue;
        dfs0(toi,now);
        num[now]++;
        sz[now]+=sz[toi];
    }
}
void dfs(int now){ // dp核心内容
    // cerr<<"now: "<<now<<'\n';
    int maxn=sz[now]-1-num[now]; // 最多可删点的数量
    fore(now,i){
        if(toi==p[now])
            continue;
        dfs(toi); // 先处理子树
        for(int k=maxn;k>=0;k--){ // 枚举父结点可以提前删的点数量，注意这里倒序是为了避免取不到值
            if(f[now][k]>=inf) // 如果没有取过值也没有转移的必要了
                continue;
            for(int j=0;j<sz[toi];j++){ // 枚举儿子可删点数
                if(k+j>maxn) // 上界优化
                    break;
                f[now][k+j]=min(f[now][k+j],f[now][k]+f[toi][j]);
            }
        }
    }
    for(int i=0;i<=maxn;i++)
        f[now][sz[now]-1]=min(f[now][sz[now]-1],f[now][i]+a[sz[now]-i]);
}
signed main(){
    for(int i=0;i<5005;i++)
        for(int j=0;j<5005;j++)
            f[i][j]=inf; // 初始化为inf
    scanf("%lld",&n);
    for(int i=2;i<=n;i++)
        scanf("%lld",a+i);
    for(int i=1,u,v;i<n;i++){
        scanf("%lld%lld",&u,&v);
        addedge(u,v);
    }
    dfs0(1,1);
    for(int i=1;i<=n;i++)
        f[i][0]=0,f[i][sz[i]-1]=a[sz[i]]; // 边界条件显然
    dfs(1);
    printf("%lld",f[1][sz[1]-1]);
    return 0;
}
```

---

## 作者：Alex_Eon (赞：2)

#### [$\color{red}博客内食用效果更佳（点我）$](https://www.luogu.com.cn/blog/Ksy/solution-p8564)
### 思路：树上背包
### 复杂度：$O(n^2)$

### 题解中涉及到的变量：

| 变量名 | 含义 |
| :----------: | :----------: |
| $val_i$ | 操作代价（题目给出的） |
| $f_{i,j}$ | 对于节点 $i$ 的子树，删去 $j$ 个节点的最小代价 |

------------

### 主体思路

操作代价与当前子树大小相关，不难想到用树上背包去解决此问题，设 $f_{now,j}$ 表示对于节点 $now$，删去 $j$ 个节点的最小代价。


#### 当不对当前节点进行删除操作时：  
转移方程：

$$f_{now,j}=\max_{0\le k\le j}\{f_{son,k}+f_{now,j-k}\}$$
注意到这样转移复杂度不够优，考虑控制上下界，设 $siz_{now}$ 表示枚举到当前子节点**之前**的子树大小，$siz_{son}$ 为当前子节点大小，$cnt$ 为枚举到的子节点个数。有 $j,k$ 范围：
$$1\le j\le siz_{now}+siz_{son}-1-cnt$$
$$\max\{1,j-siz_{now}\}\le k\le\min\{siz_{son}-1,j\}$$

#### 当对当前节点进行删除操作时：
转移方程（其中 $siz_{now}$ 表示当前节点子树大小）：
$$f_{now,siz_{now}-1}=\min_{0\le j\le siz_{now}-2}\{f_{now,i}+val_{siz_{now}-1-i}\}$$

### 代码实现需要注意的地方：

- 一定要注意上下界的限制，不然退化为 $O(n^3)$。
- 开 **long long** 防炸。
- 注意初值设置。

### 参考代码：
代码中的 $to$ 为 $son$。  
参考代码中其他变量名与题解中均一致，详见注释。
```cpp
#define LL long long
#define UN unsigned
#include<bits/stdc++.h>
using namespace std;
//--------------------//
const int N=5005;

int n,val[N];
//--------------------//
//Edge
const int M=1e4+5;

struct Edge
{
    int to,nex;
}edge[M];
int tot,head[N];
void add(int from,int to)
{
    edge[++tot]={to,head[from]};
    head[from]=tot;
}
//----------//
//DP
LL f[N][N];
int siz[N];
void DFS(int now,int fa)
{
    siz[now]=1;
    f[now][0]=0;
    for(int to,cnt=0,i=head[now];i;i=edge[i].nex)
    {
        to=edge[i].to;
        if(to==fa)
            continue;
        DFS(to,now);
        cnt++;//更新子节点个数
        for(int j=siz[now]+siz[to]-1-cnt;j>0;j--)//倒序枚举，上下界优化
            for(int k=max(j-siz[now],1);k<=min(siz[to]-1,j);k++)
                f[now][j]=min(f[now][j],f[now][j-k]+f[to][k]);//转移
        siz[now]+=siz[to];//更新子树大小
    }
    for(int i=0;i<siz[now]-1;i++)//对当前节点进行操作的最小代价
        f[now][siz[now]-1]=min(f[now][siz[now]-1],f[now][i]+val[siz[now]-1-i]);
}
//--------------------//
int main()
{
    memset(f,0x3f,sizeof(f));
    scanf("%d",&n);
    for(int i=1;i<n;i++)
        scanf("%d",&val[i]);
    for(int from,to,i=1;i<n;i++)
        scanf("%d%d",&from,&to),add(from,to),add(to,from);
    DFS(1,0);
    printf("%d",f[1][siz[1]-1]);//答案，显著的
    return 0;
}
```


---

## 作者：XiaoQuQu (赞：2)

设 $f_{i,j}$ 表示子树 $i$ 中删去 $j$ 个节点的最小代价，显然答案为 $f_{1,n-1}$。

对于任意一个节点 $i$，我们大致可以分为两类：

1. 直接删去 $i$ 的所有子结点；
2. 让 $i$ 的子结点删去它的子结点；

我们可以分别列出以下的转移方程：

1. 对于 $i$ 的每一个子结点 $u$，$k$ 表示要求在 $u$ 中删去 $k$ 个节点，则 $f_{i,j} = \min (f_{i, j-k}+f_{u,k})$
2. 考虑将 $j$ 个节点扔给子结点们删，自己删去剩下的 $sz_i-j$ 个，则 $f_{i,sz_i - 1}=\min(f_{i,j}+c_{sz_i-j})$，其中 $c_i$ 就是题目里的 $f_i$。

在第一种情况转移时，我们需要按照 $j$ 从大到小的顺序枚举，相当于是 0/1 背包。因为 $1$ 节点不可能被删空，所以在统计 $1$ 节点的儿子数时，需要多加 $1$，避免特判。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid (l + r) >> 1
#define endl '\n'

const int MAXN = 5e3 + 5;
int n, f[MAXN][MAXN], c[MAXN], sz[MAXN], son[MAXN];
vector<int> G[MAXN];

void dfs(int x, int fa) {
    sz[x] = 1; int p = 0;
    for (auto u:G[x]) {
        if (u == fa) continue;
        int las = sz[x]; ++p;
        dfs(u, x);
        sz[x] += sz[u];
        for (int i = sz[x] - p - 1; i >= 1; --i) {  // 考虑删去多少个点，由于这部分不可以直接删去子结点，所以要减去 p
            for (int j = max(0LL, i - las); j <= i && j < sz[u]; ++j) {  // 考虑分配多少个点给 u
                f[x][i] = min(f[x][i], f[x][i - j] + f[u][j]);
            }
        } 
    }
    for (int i = 0; i < sz[x] - son[x]; ++i) {
        f[x][sz[x] - 1] = min(f[x][sz[x] - 1], f[x][i] + c[sz[x] - i]);
    }
}

signed main(void) {
    ios::sync_with_stdio(false), cin.tie(NULL);
    cin >> n;
    for (int i = 2; i <= n; ++i) cin >> c[i];
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        son[i] = G[i].size() - 1;
        for (int j = 1; j <= n; ++j) f[i][j] = INT_MAX;
    }
    son[1]++;
    dfs(1, 0);
    cout << f[1][n - 1] << endl;
    return 0;
}
```

---

## 作者：scp020 (赞：2)

### 题目大意

给定一颗树，其中有 $n$ 个节点，根节点为 $1$。每次可以选择一个节点，其子树的大小为 $i$，删去该节点子树上的所有节点（不包括该节点），代价为 $val_i$。

求：当删去了除 $1$ 节点以外的所有节点时，总代价最小为多少。

### 做法

考虑树形 dp。

规定 $f_{i,j}$ 数组表示在在 $i$ 节点的子树中删去 $j$ 个节点的代价最小值。显然，答案为 $f_{1,n-1}$，因为无法删去 $1$ 节点。

考虑删除过程。下图是样例的节点连接情况。作图来自 [graph_editor](https://csacademy.com/app/graph_editor/)。

![](https://cdn.luogu.com.cn/upload/image_hosting/eu0afl4d.png)

因为最终要删去除了节点 $1$ 以外所有的节点，所以我们遍历它的儿子。

观察到，如果删去 $8$ 节点的子树是经济的，所以第一次删去 $8$ 节点的子树，代价为 $val_6 = 45104$。现在的树如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/oq8lhaoq.png)

第二次删去剩余的 $1$ 的子树，代价为 $val_3 = 18640$。所以答案为 $63744$。

给出状态转移方程，其中 $son$ 表示 $i$ 节点的儿子，$num$ 表示子树大小：$f_{i,j}=\min \limits _{k \in [\max(1,j-num_i),\min(j,num_{son}-1)]} \{ f_{i,j-k}+f_{son,k} \}$。

对于每个节点，在动态规划后还要进行一次答案更新：$f_{i,num_i-1}=\min \limits _{j \in [0,num_i-1)} \{ f_{i,j}+val_{num_i-j} \}$。

最后注意一下，因为我们不知道树的方向，所以我们双向连边。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Getchar() p1==p2 and (p2=(p1=Inf)+fread(Inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
char Inf[1<<21],*p1,*p2;
inline void read(int &x,char c=Getchar())
{
	bool f=c!='-';
	x=0;
	while(c<48 or c>57) c=Getchar(),f&=c!='-';
	while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
	x=f?x:-x;
}
int n,val[5010],f[5010][5010],num[5010];
vector<int> v[5010];
inline void solve(int pos,int fa,int cnt=0)//双向连边，fa防止向上搜索
{
	for(int i=0;i<v[pos].size();i++)
	{
		if(v[pos][i]!=fa)
		{
			solve(v[pos][i],pos),cnt+=num[v[pos][i]];
			for(int j=cnt-1;j>=1;j--)
				for(int k=max((long long)1,j-num[pos]);k<=min(j,num[v[pos][i]]-1);k++)//j不能为负数，否则越界
					f[pos][j]=min(f[pos][j],f[pos][j-k]+f[v[pos][i]][k]);
			num[pos]+=num[v[pos][i]];
		}
	}
	for(int i=0;i<num[pos]-1;i++) f[pos][num[pos]-1]=min(f[pos][num[pos]-1],f[pos][i]+val[num[pos]-i]);
}
signed main()
{
	read(n),memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++) f[i][0]=0,num[i]=1;
	for(int i=2;i<=n;i++) read(val[i]);
	for(int i=1,x,y;i<n;i++) read(x),read(y),v[x].push_back(y),v[y].push_back(x);
	solve(1,0),cout<<f[1][num[1]-1];//这里无所谓，因为节点 1 的子树中有 num[1]=n 个节点
	return 0;
}
```



---

## 作者：封禁用户 (赞：1)

### 题面
给定一颗有 $n$ 个节点的有根树，其中根节点是 $1$。你可以进行若干次以下操作：

- 选择一个节点，删去其子树内除其以外的点。

此操作的代价为 $f_i$，其中 $i$ 是你选择的节点子树大小。

最小化删去 $1$ 以外的节点的代价。

### 思路
删去一个点 $x$，并不对上面的造成影响。

考虑树上背包。

对于这个节点 $x$，设 $f_{x,i}$ 为删去他子树中 $i$ 个节点的最小代价。

简单的小转移：

$$f_{x,i}=\sum_{u=1}^{son_x}\sum_{j=\max(i-sz_x,1)}^{\min(i,sz_u-1)}\min (f_{x,i-j}+f_{u,j})$$

模板的背包，$sz_x$ **为搜过的大小**，意为：$x$ 节点删 $i$ 个时，他的儿子已经删了 $j$ 个的最小值。

然后，关于 $i$，我们惊吓地发现他最多是 $x$ 子树大小减去儿子个数和自己，因为儿子不能删掉自己。

为了方便，下面把 $sz_x$ 称作 $x$ 整个子树大小，$son_x$ 称作儿子个数。

所以我们要特别维护 $i=sz_x-1$ 的玩意，于是有了下面：

$$f_{x,sz_x-1}=\sum_{i=0}^{sz_x-son}\min(f_{x,i}+g_{sz_x-i-1})$$

$g_i$ 是原题面中的 $f_i$（一不小心重名了）。

然后~~有管理说：时间复杂度分析有误所以就不分析了吗~~，以至这个看似 $n^3$ 的算法在控制循环范围的常规优化以及树的性质下，他的时间复杂度惊奇的控制在 $O(n^2)$ 以内~~（同机房大佬们教的）~~。。。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 5005 
using namespace std;
int sz[Maxn],f[Maxn][Maxn],g[Maxn];
vector<int> q[Maxn];
void solve(int x,int fa) {
    sz[x]=1; int son=0;
    for(int u:q[x]) {
        if(u == fa)continue;
        son++; solve(u,x);
        for(int i=sz[x]+sz[u]-son-1;i>0;i--)
            for(int j=max(i-sz[x],1ll);j<=min(i,sz[u]-1);j++)
                f[x][i]=min(f[x][i],f[x][i-j]+f[u][j]);
        sz[x]+=sz[u];
    }
    for(int i=0;i<=sz[x]-son-1;i++)
        f[x][sz[x]-1]=min(f[x][sz[x]-1],f[x][i]+g[sz[x]-1-i]);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<n;i++)
        cin>>g[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=1e13;
    for(int i=1;i<n;i++) {
        int u, v;
        cin>>u>>v;
        q[u].push_back(v);
        q[v].push_back(u);
    } solve(1,0);
    cout<<f[1][sz[1]-1];
    return 0;
}
```

---

## 作者：快斗游鹿 (赞：1)

## 思路

树上背包。

设 $f_{i,j}$ 表示第 $i$ 个点，其子树中删除了 $j$ 个点所要花费的最小代价。$size_i$ 表示点 $i$ 的子树大小，$son_i$ 表示点 $i$ 儿子数。然后可以分当前节点进行操作或不进行来讨论。

如果当前点 $i$ 不进行操作，根据题目，它的子树中**最多删掉** $size_u-son_u-1$ 个点。为什么？首先它自身不会被删，其次因为它不进行操作，所以它的儿子无论执不执行操作，都不会被删。那么显然有转移方程：

$f_{i,j}=\displaystyle\min_{k=1}^jf_{v,k}+f_{u,j-k}$。其中 $v$ 是 $i$ 的儿子。

而如果它自身被删，同样儿子最多帮它删掉 $size_u-son_u-1$ 个点，则有转移方程：

$f_{i,size_i-1}=\displaystyle\min_{j=0}^{size_u-son_u-1}f_{i,j}+cost_{size_u-j}$。其中 $cost_i$ 即题目中的 $f_i$。

需要特别注意转移的上下界。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5;
struct edge{
	int to,nxt;
}e[N<<1];
int n,f[N],dp[N][N],cnt,head[N],size[N];//f(i,j)第i个点子树删j个 
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int u,int fa){
	size[u]=1;int son=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		son++;
		dfs(v,u);//自己不删 
		for(int j=size[u]+size[v]-son-1;j>=1;j--){//删几个 
			for(int k=max(1ll,j-size[u]);k<=j&&k<size[v];k++){//以前负担几个 
				dp[u][j]=min(dp[u][j],dp[v][k]+dp[u][j-k]);
			}
		}
		size[u]+=size[v];
	}//自己删 
	for(int i=0;i<=size[u]-son-1;i++){//儿子删了几个 
		dp[u][size[u]-1]=min(dp[u][size[u]-1],dp[u][i]+f[size[u]-i]);
	}
}
signed main(){
	freopen("T2ex2.in","r",stdin);
	n=read();
	for(int i=2;i<=n;i++){
		f[i]=read();
	} 
	f[0]=1e13;
	for(int i=1;i<n;i++){
		int u,v;u=read();v=read();add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)dp[i][j]=1e13;
	}
	dfs(1,0);
	/*for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++)cout<<dp[i][j]<<" ";
		cout<<endl;
	}*/
	cout<<dp[1][n-1];
	return 0;
}

```


---

## 作者：船酱魔王 (赞：1)

# P8564 ρars/ey 题解

## 题意回顾

给定一棵 $ n $ 点，根为 $ 1 $ 的有根树，每次可以选择一个点并删除其子树内所有点，付出 $ f_x $（$ x $ 为子树大小）的代价。找出删除除了 $ 1 $ 以外的所有点的最小代价。

$ 1 \le n \le 5000 $。

## 分析

考虑设计动态规划，设 $ dp_{i,j} $ 表示 $ i $ 结点子树删去 $ j $ 个点的最小代价。

则对于每个子结点进行转移 $ dp_{u,j} \leftarrow \min\{dp_{u,j-k}+dp_{v,k}\} $。最后 $ dp_{u,sz_u-1} \leftarrow min\{dp_{u,j}+f_{sz_u-1-j}\} $。

注意卡好转移枚举上下界可以做到 $ O(n^2) $，否则会退化到大约 $ O(n^3) $。

因为如果卡好上下界每次枚举的都是合法状态，对于每次合并，时间复杂度为之前的子树和目前的子树的乘积，我们可以理解为两两子树大小乘积求和，本质上理解为两个子树内各选一点，在子树的根节点合并，因为合并位置一定是 $ \operatorname{LCA} $，因此任意两点只会合并 $ 1 $ 次，时间复杂度是 $ O(n^2) $ 的。

注意实现细节，见 AC 代码。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 5005;
int n;
int w[N];
vector<int> g[N];
int sz[N];
long long dp[N][N];
int dfs(int u, int fa) {
	sz[u] = 1;
	int v;
	int ct = 0;
	dp[u][0] = 0;
	for(int vi = 0; vi < g[u].size(); vi++) {
		if(g[u][vi] == fa) {
			continue;
		}
		ct++;
		v = g[u][vi];
		dfs(v, u);
		for(int i = sz[u] + sz[v] - ct - 1; i >= 1; i--) {
			for(int j = max(1, i - (sz[u] - ct)); j <= min(sz[v] - 1, i); j++) {
				dp[u][i] = min(dp[u][i], dp[u][i - j] + dp[v][j]);
			}
		}
		sz[u] += sz[v];
	}
	for(int i = 0; i < sz[u] - 1; i++) {
		dp[u][sz[u] - 1] = min(dp[u][sz[u] - 1], dp[u][i] + w[sz[u] - i]);
	}
	return sz[u];
}
int main() {
	cin >> n;
	for(int i = 2; i <= n; i++) {
		cin >> w[i];
	}
	int x, y;
	for(int i = 1; i < n; i++) {
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			dp[i][j] = 1e13;
		}
	}
	dfs(1, 0);
	cout << dp[1][n - 1] << endl;
	return 0;
}
```

---

## 作者：云浅知处 (赞：1)

发现在 $1$ 处进行一次操作就可以完成目标，但是不一定最优，我们可以先消掉几个子树再删除自己，这取决于 $f$ 具体是什么。

不难想到设 $\text{dp}(u,j)$ 表示考虑以 $u$ 为根的子树，删到只剩 $j$ 个点所需的最小代价。

转移时，若我们在 $u$ 处进行了操作，则最终一定会变为 $\text{dp}(u,1)$ 的形态。影响结果的只是在 $u$ 处进行操作的时机。

这启发我们先不考虑在 $u$ 处的操作，将 $u$ 的各个儿子的 $\text{dp}$ 值做背包合并上来，接下来只需要枚举 $k\in[1,\text{size}(u)]$，用 $\text{dp}(u,k)+f_k$ 来更新 $\text{dp}(u,1)$ 即可。具体可以看代码。

算法的时间复杂度为 $O(n^2)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}

const int N=5005;
const int INF=1e14;
int dp[N][N],n,f[N],sz[N];
vector<int>G[N];
void chk(int &x,int v){x=min(x,v);}

int g[N];
void DP(int u,int fa){
	sz[u]=1;dp[u][1]=0;
	for(int v:G[u]){
		if(v==fa)continue;DP(v,u);
		for(int i=0;i<=sz[u]+sz[v];i++)g[i]=INF;
		for(int i=0;i<=sz[u];i++){
			for(int j=0;j<=sz[v];j++)chk(g[i+j],dp[u][i]+dp[v][j]);
		}
		for(int i=0;i<=sz[u]+sz[v];i++)dp[u][i]=g[i];sz[u]+=sz[v];
	}
	dp[u][sz[u]]=0;for(int i=1;i<=sz[u];i++)chk(dp[u][1],dp[u][i]+f[i]);
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif

	n=read();memset(dp,63,sizeof(dp));
	for(int i=2;i<=n;i++)f[i]=read();
	for(int i=1;i<=n-1;i++){
		int u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	DP(1,0);cout<<dp[1][1]<<endl;

	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

首先显然这道题一眼就是类似树形背包的一个 dp。

对于一个点，考虑它剩下多少个点不删，记 $dp_{i,j}$ 表示第 $i$ 个点子树内，去掉包含 $i$ 的某一个联通块之后，剩下 $j$ 条边需要单独删掉的时候的最小值。

每次的转移就是枚举它的儿子，$dp_{i,j}$ 从最小的 $dp_{i,k}+dp_{v,j-k}$ 转移过来。

最后发现还有一种情况就是残暴的把 $i$ 直接删了。令 $S_i$ 为 $i$ 子树大小，则显然删除的时候的答案，是首先通过一遍 $dp$ 得到剩下 $j$ 个的时候的答案，然后我们枚举剩下多少个，显然子树大小减去剩下多少个就是我们这一次删除的数量。

显然最后的答案就是直接删 $1$ 的时候的答案，因为 $1$ 的子节点必须通过 $1$ 删掉~~而不能自己刀了自己~~。

复杂度 $O(n^2)$。注意到实现中有一些小细节：

- 建议刷表而不是查表，因为查表太难赋初始值了。

- 注意转移的顺序，避免后效性。（也可以新开一个临时数组或者转移之后赋一个 `INF` 之类的）

- 最好不要无脑从 $0$ 开始枚举背包维，应该算一下上下界，否则这道题的初始值会让你头疼不已。

- 复杂度的话为什么看起来是三维循环但是只有 $n^2$ 呢，是因为第三维和第二维的复杂度乘起来实质是 $O(\sum S_v)=S_u$，由于 $S_u$ 是 $O(n)$ 量级的，所以本质上是 $O(n^2)$ 的。其他的赋初始值等不要 `memset`，否则复杂度退化成 $O(\dfrac{2}{3}n^3)$。

其他的还有很多，我就不再赘述了。

---

