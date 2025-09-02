# 『MdOI R2』Resurrection

## 题目背景

如果你不清楚本题的某些定义，可以阅读【说明/提示】部分。

## 题目描述

有一棵包含 $n$ 个节点的树 $T$，它的所有边依次编号为 $1$ 至 $n-1$。

保证对于 $T$ 中任意一个节点 $u$ ，从 $u$ 到 $n$ 号节点的简单路径都不经过任何编号小于 $u$ 的节点。

按照如下步骤生成一张包含 $n$ 个节点的无向图 $G$：

选取一个 $1 \sim n-1$ 的排列 $p$，然后依次进行 $n-1$ 次操作。在进行第 $i$ 次操作时，首先删除树 $T$ 中编号为 $p_i$ 的边 $(a,b)$，然后，记 $u$ 和 $v$ 分别为当前树 $T$ 中与 $a,b$ 联通的所有点中，编号最大的点，并在图 $G$ 的 $u$ 号点和 $v$ 号点之间连一条边。

求对于给定的树 $T$，按上述方式一共可以生成多少种本质不同的图 $G$。图 $G_1$ 和 $G_2$ 本质不同当且仅当存在 $u$ 和 $v$ 满足在 $G_1$ 中不存在边 $(u,v)$，而 $G_2$ 中存在。 

因为答案可能很大，你只需要求出答案对 $998244353$ 取模的值。


## 说明/提示

【帮助与提示】

为方便选手测试代码，本题额外提供一组附加样例供选手使用。  

[样例输入](https://www.luogu.com.cn/paste/09anxo5k) [样例输出](https://www.luogu.com.cn/paste/3idipkty)      

---

【样例解释】

样例一中可能生成的图 $G$ 如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/aaq591b7.png)

当 $p = \{1,2,3\},\{2,1,3\},\{2,3,1\}$ 时将生成右侧的图，否则将生成左侧的图。

对于样例二，我有一个绝妙的解释，只可惜这里空白的位置太小，写不下。

---

【数据范围】

**本题采用捆绑测试。**

对于全部数据，保证 $1 \leq n \leq 3 \times 10^3$，$1 \leq u,v \leq n$。

保证，输入的边形成一棵树，且对于任意一个节点 $u$ ，从 $u$ 到 $n$ 号节点的简单路径都不经过任何编号小于 $u$ 的节点。

| 子任务编号 | $n\leq$ |         特殊性质          | 分值 |
| :--------: | :-----: | :-----------------------: | :--: |
| Subtask 1  |   $5$   |            无             | $32$ |
| Subtask 2  |  $14$   |            无             | $16$ |
| Subtask 3  | $10^3$  | 所有节点都与 $n$ 号点直接相连 | $1$  |
| Subtask 4  | $10^3$  |     树的形态是一条链      | $7$  |
| Subtask 5  |  $50$   |            无             | $22$ |
| Subtask 6  | $3 \times 10^3$  |            无             | $22$ |

---

下面是本题用到的一些定义：

- 一棵树是一张有 $n$ 个节点，$n-1$ 条边的无向连通图。

- 边 $(u,v)$ 表示连接点 $u$ 和点 $v$ 的一条边。

- 一条路径是一个序列 $p_1,p_2 \ldots p_k$ ，满足对于任意 $1 \leq i < k$，边 $(p_i,p_{i+1})$ 都存在于 $T$ 中，且 **没有被之前的操作删除**。

- 点 $u$ 和 $v$ 联通当且仅当存在一条路径 $p_1,p_2 \ldots p_k$ 满足 $p_1=u$ 且 $p_k=v$。任何一个点都和自己联通。





## 样例 #1

### 输入

```
4
1 4
2 3
3 4
```

### 输出

```
2```

## 样例 #2

### 输入

```
11
1 4
2 6
3 11
4 6
5 6
6 7
7 9
8 9
9 10
10 11
```

### 输出

```
4605```

# 题解

## 作者：EternalAlexander (赞：12)

好像没啥比较靠谱的题解，估计一堆过掉的人都是猜的结论，早知道出构造了。

## 性质

首先观察到，生成的图 $G$ 是一棵树，且假如把原树和新树都看作以 $n$ 为根的有根树，那么新树的任意节点的父节点都是它在原树中的祖先节点。

我们考虑什么样的树可能是生成的新树。

一个必要条件是，任意两个祖先-后代节点到父边的连线要么相离，要么某一条包含另一条。也就是说，不存在 $u$，$v$，$u$ 在 $G$ 中的父节点是 $x$，$v$ 是 $y$，满足 $u$ 是 $v$ 的祖先，且 $y$ 是 $u$ 的祖先，且 $x$ 是 $y$ 的祖先。

我们考虑 $u$ 的父边被断开的时候，在那之前，$u$ 到 $x$ 之间的任何边都不能被断开，否则 $u$ 到 $x$ 的连边将无法完成。又因为，$y$ 被包含在 $u$ 到 $x$ 的路径中，$v$ 所在联通块最大点至少是 $x$，其到 $y$ 的连线不可能在这之前完成。而在这之后，$v$ 和 $y$ 不再联通，不可能相互连边。

同时，这个条件是充分的。考虑这样构造方案：维护一个决策集合，一开始只有根的子节点。

每次取决策集合中编号最小的点，断开它在原树中到父节点的边，然后将它在新树中的子节点加入决策集合。

这样构造的方案一定是合法的，考虑点 $u$ 到父节点的连边，这个点不可能比它的目标父节点 $v$ 大，因为只有在 $v$ 到父节点的边被断开后 $u$ 才可能加入决策集合。

同时这个点也不可能比 $v$ 小，假如这个点比 $v$ 小，那么一定有 $u-v$ 中某一条边被断开了，又因为这些点的编号都比 $u$ 大，必须它们比 $u$ 先加入决策集合才能出现这种情况。

然而，根据这个条件的必要性， $v$ 一定是这些节点在 $G$ 中的祖先节点，否则将会出现连线交叉的情况。因此，这些
节点都不早于
$u$ 加入决策集合。矛盾。

## 做法

每个节点会向自己的某个祖先节点连边，并且两条连线不能交叉。我们要计算这样的方案数。

考虑dp。我们记 $f_{i,j}$ 表示考虑到节点 $i$，祖先中有 $j$ 个可以向其连边的节点时，子树中连边的方案数。

考虑枚举点 $u$ 和从下往上数，第 $x$ 个节点连边。那么，这条连线会覆盖掉 $x-1$ 个可以连边的节点，然后对于子树中的所有节点，$u$ 都是一个可以连边的节点。

可以写出转移：$f_{i,j} = \sum_{x=1}^j \prod f_{v,j-(x-1)+1}$，前缀和优化即可得到 $O(n^2)$ 做法。

---

## 作者：冰冷的心 (赞：6)

这道题与传统的树形dp不同

传统的树形dp是从子树中合并答案上来 

即先确定子树对祖先的影响，然后确定当前节点的影响

这道题目显然不太好这样做，因为当前考虑的点的深度变小的时候，本来有限制的现在没有了限制，这样就非常不好设状态

那么我们反过来考虑，首先确定父亲对儿子的影响 然后dp。 

首先观察可以发现 最终的答案肯定是这样的形态：

![](https://cdn.luogu.com.cn/upload/image_hosting/d1ua7e58.png)
而没有：
![](https://cdn.luogu.com.cn/upload/image_hosting/g2uees7t.png)

就是父亲选好以后子树的点要么选父亲选的点上面的点 要么选父亲下面的点
而没有交叉的情况（手玩得证）

这样可以设$f[u][i]$表示点$u$的上面还有$i$个点可供它选择去限制。每次枚举$u$限制了几个点，然后把儿子相应的答案乘起来

形式化的说就是$f[u][i]= \sum_{j=0}^{i-1}\prod_{v} f[v][i-j+1]$ 加1表示下面儿子可以多$u$这个点

直接做是$n^3$的 考虑这个$dp$的第二维，发现由$i$->$i+1$只有一项不同，$i+1$每次继承$i$的状态 在单独算一下自己的特有的项

# code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e3 + 11;
const int mod = 998244353;
int f[N][N], n;
vector<int> G[N];
int dfs(int u, int res, int fa){
	if(f[u][res] != -1)return f[u][res];
	if(G[u].size() == 1){
		return f[u][res] = res;
	}
	int &F = f[u][res];
	F = 0;
	if(res > 1)(F += dfs(u, res - 1, fa)) %= mod;
	int sum = 1;
	int s = G[u].size();
	for(int i = 0;i < s; i++){
		int v = G[u][i];
		if(v == fa)continue;
		sum = 1LL * sum * dfs(v, res + 1, u) % mod;
	}
	F = (F + sum) % mod;
	return F;
}
int main(){
	cin>>n;
	int u, v;
	memset(f, -1, sizeof f);
	for(int i = 1;i < n; i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int ans = 1;
	int s = G[n].size();
	for(int i = 0;i < s; i++){
		int v = G[n][i];
		ans = 1ll * ans * dfs(v, 1, n) % mod;
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：m1kusama (赞：2)

首先注意到每个点的父节点编号都大于他的编号这个性质。

手玩一下性质，观察下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/8neqfp6m.png)

考虑断掉边 $(5,7)$，那么原图被分成了两个联通块，其中 $5,2,1$ 所在的联通块的最大点是 $5$，另一个联通块的最大点是 $7$。那么在新生成的图中就有 $(5,7)$ 这条边。

再割一条试试。这次断掉边 $(3,6)$，发现新生成的图中要连 $(3,7)$ 这条边。

发现规律：根据上文性质，每个联通块都是深度最小的点之间连边。给边定向，规定深度大的点向深度小的点连边，那么一个点可以连的边只能是祖先节点。

但是发现这个限制太松了。再深挖性质，发现这样一种情况是非法的：

![](https://cdn.luogu.com.cn/upload/image_hosting/zr4co4ph.png)

发现无论什么删边顺序都不能使得这两条相交的边同时出现。

考虑证明：

若 $(1,3)$ 边出现，那么 $(1,2)$ 这条边就得先于 $(2,3)$ 删除。

若 $(2,4)$ 边出现，那么 $(2,3)$ 这条边就得先于 $(3,4)$ 删除。

所以 $(1,2)$ 要先于所有边删除，那么必定出现 $(1,4)$ 这条边，矛盾。
 
得出结论：在新图上，若一个点 $u$ 向祖先节点 $f$ 连边，那么 $u$ 的后代 $v$ 必不能向处于 $u$ 到 $f$ 链上的点连边。

那么新树生成的方案数就转化为了合法的连边方案数。

设 $dp_{i,j}$ 表示 $i$ 点向祖先连边，只有 $j$ 个点可连。

考虑枚举 $i$ 向 $k$ 连边，那么后代能连的点只有 $(dep_k-1)+1$。其中 $+1$ 是因为后代还可以连 $i$。

写出转移：
$$dp(x,i)=\prod_{y \in xson}\sum_{k=0}^{i-1} dp(y,i-j)$$

使用前缀和优化上式后半部分的求和，时间复杂度 $O(n^2)$。

代码参考：

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N=3e3+10,mod=998244353;
int M(int x){
	if(x>=mod)return x%mod;
	if(x<0)return (x%mod+mod)%mod;
	return x;
}
int n,ans=1;
vector<int>e[N];
int dp[N][N];
int sum[N][N];
void dfs(int now,int fa){
	for(int i=1;i<=n;i++)dp[now][i]=1;
	if(now==n)dp[now][0]=1;
	for(auto it:e[now]){
		if(it==fa)continue;
		dfs(it,now);
		for(int i=1;i<=n;i++){
			dp[now][i]=M(dp[now][i]*sum[it][i+1]);
		}
	}
	sum[now][1]=dp[now][1];
	for(int i=2;i<=n;i++){
		sum[now][i]=M(dp[now][i]+sum[now][i-1]);
	}
}

void solve(){
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(n,0);
	for(auto it:e[n])ans=M(ans*dp[it][1]);
	cout<<ans;
}
signed main(){
//	freopen("reflection.in","r",stdin);
//	freopen("reflection.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T=1;
//	cin>>T;
	while(T--)solve();
}
```

---

## 作者：耶梦加得 (赞：2)

首先，生成的图 G 有 $n$ 个点

其次，每在原来的树上删去一条边，就会在图 G 中，产生一条边。也就是说，图 G 中边的数量也同样是 $n - 1$ ，即图 G 也是一棵树 

树 + 方案计数，显然这是一个**树形DP**

另外，题目明示 n 是一个非常特殊的节点，我们可以把 n 设为原树

于是我试图写出用子树推导父亲的转移方程式

写不出来，~~还是看题解吧~~

~~（以上基本上是废话）~~

我们略加思索，会发现这题比较特殊——原树的根节点具备特殊性质，而子树则不一定有，所以我们很难对子树进行 DP 。
 
那么反过来，我们考虑用**父节点的状态更新儿子节点**

极易知道，除了根节点，每个节点必然与父节点有唯一一条连边，且一定会在某个时刻断开。

我们可以根据这点

### 推断转移方程

首先，假设这个点为 $u$ 断开这条边之后，新图中出现了边 $(u, v)$ 

~~然后呢~~

这个小小的举动，可以让我们获得以下信息：

1. 在此之前，所有从 $v$ -> $u$ 的路径上的边都没有被删去 
2. 当前， $v$ 是其所在联通块编号最大的点

性质2看不出有什么用，我们分析性质1

假设我们后来某个时刻断开了路径上一条边 $(x, y)$

那么，假如此时 $y$ 和 $v$ 联通，那么一定有 $v > y$ 矛盾

所以此刻 $y$ 一定和 $x$ 联通（删边之前），但是和 $v$ 断开

也就是说， $y$ 一定是这条路径上某个点！

我们得出结论：**所有的连边不存在交叉**（具体定义可以找其他题解）

如此一来，我们可以算出满足”没有两边交叉“，以 $n$ 为根的树有多少种，**先假定它是答案**（后面给出证明）

状态的第一维显然是当前节点 $u$

由于我们从父亲节点推导儿子节点，而由刚才的讨论，**我们知道 $u$ 会从祖先节点里面选出一个连边**

由此不难得出**决策**就是选择哪一个祖先节点，考虑将**第二个状态**设置成“当前可以选择的祖先节点数量”

根据乘法原理和加法原理~~废话~~，得出方程：

$f[u][i] = \sum_{j=0}^{i-1}\prod_{v}f[v][i - j + 1]$

意思是选择一个祖先节点，将 $j$ 个祖先保护在内，这是加法

对于每一个儿子，从 $i - j$ 个祖先和 $u$ 自身中选择一个，连边，这里使用乘法原理


### 最后证明

对于每个这样的图 G 一定会有满足条件的连边方法

构造：首先把与 n 相连的点扔进集合

接下来，每次取出集合中编号最小的点，假设是 $u$ ，父节点为 $x$ ，删去边 $(u, x)$ ，然后把图 G 中所有 $u$ 的子节点加入集合。我们假设在我们构造出的这个图 G 中，$u, v$ 有边相连

#### 首先， $u$ 一定是其所在联通块最大的点

假设存在点 $y$ ，满足 $u$ 是它的祖先，并且 $y > u$

那么 $u$ 在 $y$ 到 n 的简单路径上，但是 $u < y$ ，矛盾！

#### 其次， $v$ 一定是其所在联通块最大的点

假如存在 $z$ ， 满足 $z$ 是 $u$ 的祖先， $z$ > $u$

由于 $u$ 在集合中，

1. $v = n$ ，那么易知 $z < v$
2. $v$ 不等于 $n$ ，因此， $v$ 必然断开了与父节点的连边

我们得出结论，假如点 $z$ 是 $v$ 的祖先，那么一定与 $u$ 断开，矛盾

所以 $v$ 在 $z$ 到 n 的简单路径上，但是 $v$ < $z$ 矛盾！

#### 最后， $u$ $v$ 删边之前一定在同一个联通块

否则，假设路径上 $a_1$ 和 父节点断开了

那么在此之前 $a_1$ 被加入了集合，假设点 $a_2$ 是图 G 中它的父亲（显然存在），那么我们可以知道在此之前 $a_2$ 被加入了集合……

但是，$a_i$ 必须是 $v$ 的后代（否则会产生交叉），矛盾！


## 极度丑陋的代码：
```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define miu 3007
using namespace std;
const long long mod = 998244353;
inline int read() {
    register int x = 0; register char ch = getchar();
    while(ch < '0' || ch > '9')ch = getchar();
    while(ch >= '0' && ch <= '9'){x = x * 10 + ch - 48; ch = getchar();}
    return x;
}
template<class T>inline T mmax(register T x, register T y) {
    return x > y ? x : y;
}
template<class T>inline void add(register T & x, register long long y) {
    x += y; if(x > mod)x -= mod;
}
vector<int> g[miu];
int n, par[miu];
long long f[miu][miu], ans = 1ll;
long long dfs(int u, int x) {
    if(f[u][x] != -1)return f[u][x];
    if(g[u].size() == 1)return x;
    f[u][x] = 0;
    if(x > 1)add(f[u][x], dfs(u, x - 1));
    long long tmp = 1ll;
    for(int i = 0; i < g[u].size(); ++i) {
        int to = g[u][i];
        if(to == par[u])continue;
        par[to] = u;
        tmp = tmp * dfs(to, x + 1) % mod;
    }
    add(f[u][x], tmp);
    return f[u][x];
}
signed main() {
    memset(f, -1, sizeof(f));
    n = read();
    for(int i = 1; i < n; ++i) {
        int a = read(), b = read();
        g[a].push_back(b);
        g[b].push_back(a);
    }
    //par[n] = 0;
    for(int i = 0; i < g[n].size(); ++i) {
        int to = g[n][i]; par[to] = n;
        ans = ans * dfs(to, 1) % mod;
    }
    cout << ans % mod << endl;
    return 0;
}
```









---

## 作者：Lgx_Q (赞：2)

随便画几下，发现利用儿子贡献父亲好像要很多条件……所以，思考利用祖先的条件计算儿子。

对于一个点 $u$，从它到 $n$ 的路径上，每条边都会有一个删除顺序。比如，路径为 $u-u_1,u_1-u_2,u_2-n$。为了 DP 顺利，思考 $u_1-u_2,u_2-n$ 两条边对 $u-u_1$ 删边的影响。

1. 先删 $u_1-u_2$：那么我们发现，$u$ 在 $G$ 中的边必定连不到 $u_2$，无论如何安排顺序，只能连到 $u_1,n$ 两个点。

2. 先删 $u_2-n$：则 $u$ 在 $G$ 中存在一种顺序，能连到 $3$ 个点。

更一般化，我们设路径上每条边的删除时间为 $t_1,t_2,...,t_m$，那么 $u$ 其实只能连到 $t_{p_1},t_{p_2},...$ 所对应边的儿子，其中 $p_i$ 为按时间排序后从上到下的顺序递增（贪心处理的）的第 $i$ 条边。

能连到的点个数是一个变量，设 $f_{u,i}$ 表示当前 $u$ 能连到的父亲有 $i$ 种选择，对于 $u$ 子树的方案数。

枚举一下 $u$ 连向的父亲是从上到下第 $j$ 个点，那么在第 $j$ 个点删完边后直接跳到 $u$，对于所有儿子来说共有 $j+1$ 个点可选择。

$$f_{u,i}=\sum_{j=1}^i\prod_{v}f_{v,j+1}$$

发现 $f_{u,i}$ 比 $f_{u,i-1}$ 只多了 $j=i$ 的情况，前缀和优化即可。

---

## 作者：FZzzz (赞：1)

稍微不太一样的思维过程，可能不需要猜结论，但是本质相同。

首先以 $n$ 为根，那么每次断掉一个点的父边时我们实际上把这个点和它最近的父边没有被断掉的祖先在 $G$ 中连接起来。

可以发现，我们可以任意选择挂在 $n$ 上的点。选好以后，贡献是：对于每个被选的点，它的子树中去掉所有其他被选的点的子树，剩下的这个子树的答案，之积。因为，被选的点的父边一定先于这个子树里任何一条边被删掉。

但是剩下的这个子树的形态很没法描述。我们不妨大胆一点，继续往下考虑。对于每个被选的点，它又要在这个子树里选点挂在它上面，然后重复，等等。

这样，我们不妨直接考虑每个点在第几层时被选中。即，每个点在 $G$（根据上面的分析显然是树）中的深度。考虑这个深度有什么限制。发现，只需要每个点的深度不大于它的父亲的深度加一即可。

所以最后我们得到的是，我们给每个点一个标号，满足：$n$ 的标号是 $0$，其他点的标号是正整数，并且不大于它的父亲的标号加一。结论是，一个这样的标号方案可以与一个合法的 $G$ 形成双射。具体证明略过。

这样就很好做，把每个点的标号计入状态进行 dp 即可，前缀和优化做到 $O(n^2)$ 时间。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=3e3+5;
int n;
vector<int> g[maxn];
const ll mod=998244353;
ll f[maxn][maxn];
void dfs(int u,int fa){
	for(int i=1;i<=n;i++) f[u][i]=1;
	for(int v:g[u]) if(v!=fa){
		dfs(v,u);
		for(int i=1;i<=n;i++)
			f[u][i]=f[u][i]*f[v][i+1]%mod;
	}
	for(int i=2;i<=n+1;i++)
		f[u][i]=(f[u][i]+f[u][i-1])%mod;
}
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();
		v=read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(n,0);
	ll ans=1;
	for(int v:g[n]) ans=ans*f[v][1]%mod;
	printf("%lld\n",ans);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：ZillionX (赞：1)

# Description

有一棵包含 $n$ 个节点的树 $T$，它的所有边依次编号为 $1$ 至 $n-1$。

保证对于 $T$ 中任意一个节点 $u$ ，从 $u$ 到 $n$ 号节点的简单路径都不经过任何编号小于 $u$ 的节点。

按照如下步骤生成一张包含 $n$ 个节点的无向图 $G$：

选取一个 $1 \sim n-1$ 的排列 $p$，然后依次进行 $n-1$ 次操作。在进行第 $i$ 次操作时，首先删除树 $T$ 中编号为 $p_i$ 的边 $(a,b)$，然后，记 $u$ 和 $v$ 分别为当前树 $T$ 中与 $a,b$ 联通的所有点中，编号最大的点，并在图 $G$ 的 $u$ 号点和 $v$ 号点之间连一条边。

求对于给定的树 $T$，按上述方式一共可以生成多少种本质不同的图 $G$。图 $G_1$ 和 $G_2$ 本质不同当且仅当存在 $u$ 和 $v$ 满足在 $G_1$ 中不存在边 $(u,v)$，而 $G_2$ 中存在。 

答案对 $998244353$ 取模。

$n \le 3 \times 10^3$，时限 1s。

# Solution

观察题目中“从 $u$ 到 $n$ 号节点的简单路径都不经过任何编号小于 $u$ 的节点”这句话，可以想到若以 $n$ 为根，则所有根到子树的路径都是单调下降的。

考虑新图的生成过程，可以发现每次操作类似于边分治，无非就是在两个连通块中的最浅点间建边。

那么显然我们构造出来的 $G_2$ 是一棵树。

现在我们手玩几组样例，挖掘一些结论。

有结论：合法的建边必然使得新边两两不交叉，而对于不交叉的新边我们都可以构造出一种合法的建边方案。

这是因为每次操作会把原树劈成两半，从此分成两个互不相干的子问题，不会再有它们之间的连边。

此时问题转化为：每个点都可以向祖先连边，你要使得新边之间两两不交叉，求总方案数。

大力树形 DP，考虑祖先向当前点连的边。设 $f_{u,x}$ 表示 $u$ 的祖先中有 $x$ 个点可以向下连边。

有转移

$$f_{u,x}=\sum_{v \in {\rm son}_u}\sum_{j=1}^x f_{v,j+1}$$

这是因为考虑 $u$ 向第几个祖先连边，若与第 $j$ 个连边，则 $v$ 可选的还有 $1 \sim j$ 和 $u$ 自己。

这个不难把后面部分用前缀和优化。

复杂度 $\mathcal O(n^2)$。

# Code

```cpp
const int N=3e3+5;
const LL mod=998244353;
int n;
LL f[N][N];
vector<int> g[N];
void dfs(int u,int fa,int d) {
	if (g[u].sze()==1) {
		for (int i=1;i<=d;i++) f[u][i]=i;
		return;
	}
	for (int v:g[u])
		if (v!=fa) dfs(v,u,d+1);
	static LL t[N]; 
	for (int i=1;i<=d+1;i++) t[i]=1;
	for (int v:g[u])
		if (v!=fa)
			for (int i=1;i<=d+1;i++)
				t[i]=t[i]*f[v][i]%mod;
	for (int i=1;i<=d;i++) f[u][i]=(f[u][i-1]+t[i+1])%mod;
}
int main() {
	scanf("%d",&n);
	for (int i=1;i<n;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].pb(v),g[v].pb(u);
	}
	LL ans=1;
	for (int v:g[n]) {
		dfs(v,n,1);
		ans=ans*f[v][1]%mod;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Hilaria (赞：0)

### [P6383 『MdOI R2』Resurrection](https://www.luogu.com.cn/problem/P6383)

- 题意：

给定一棵 $n$ 个点的树，保证所有边是从大到小连接的。

按照如下步骤生成一张包含 $n$ 个节点的无向图 $G$：

选择原树上的一条边 $(u,v)$ 删除，分别记 $u,v$ 删除后所在的连通块的最大点为 $a,b$，在新树上连接 $a,b$。

求对于给定的树 $T$，按上述方式一共可以生成多少种本质不同的图 $G$。图 $G_1$ 和 $G_2$ 本质不同当且仅当存在 $u$ 和 $v$ 满足在 $G_1$ 中不存在边 $(u,v)$，而 $G_2$ 中存在。

因为答案可能很大，你只需要求出答案对 $998244353$ 取模的值。

$n\leq 3\times 10^3$

- 思路：

我们手玩一下可以发现，对于一条链，父亲的指向和儿子的指向不能相交。

也就是说，我们可以用父亲去限制儿子的选择，考虑到我们只需要保证指向的相对位置不变，所以可以直接定义一个 $f_{p,i}$ 为 $p$ 点上面有 $i$ 个可选择的祖先时的方案数，也就是说，我们不在意这 $i$ 个点实际上在什么位置，我们只需要算有 $i$ 个点时的相对位置不同的连接方案（例如一个深度为 $3$ 的叶子节点，当计算他上面有 $1$ 个可连接的祖先时，方案应为 $1$，即你的方案数是不管祖先是谁，在哪的）。


然后可以钦定父亲选择 $i$ 个点中从下到上的第 $x$ 个点，那么儿子只能选 $i-(x-1)+1$ 个点（加一是 $p$ 点也可以选），所以转移显然是：

$f_{p,i} = \sum_{j=1}^{i} \prod_{v\in p} f_{v,i-(j-1)+1}$

然后前缀和优化一下即可达到 $O(n^2)$。

---

## 作者：_Cheems (赞：0)

呜呜呜看不懂题解所以来写一篇。

根据题意，以 $n$ 为根的树满足 $u\le fa$，那么建图的过程可以视作：选取 $(u,fa)$ 删去，从 $fa$ 开始往上走找到第一个满足父边已被删除的点 $p$，建边 $(u,p)$。

这启示我们关注一条到根的链，假设已经确定了链上每条边删除时间的相对顺序，从底至上记为 $t_m\dots t_0$，为了方便可以认为根有一条父边且删除时间为 $0$。

若在链尾新接一条边 $(u,fa)$，其删除时间为 $t_{m+1}$，考虑 $u$ 可以选择和哪些点建边，容易发现它们一定是 $t_m\dots t_0$ 的单调栈里的点（栈单调递减）。

于是可以 dp，记 $f_{u,i}$ 表示已知 $t_m\dots t_0$ 的单调栈大小为 $i+1$ 时（显然 $t_0=0$ 一定在栈内），$u$ 子树内的点的向上建边方案。转移枚举加入 $t_{m+1}$ 后单调栈的大小即可，子树相互独立故直接相乘：

$$f_{u,i}=\sum\limits_{j=1}^{i+1}\prod f_{v,j}$$

考虑边界条件（即叶子），记叶子到根有 $dep$ 条边，则：

$$f_{u,i}=i+1$$

最后答案即为 $\prod\limits_{v\in son_n} f_{v,0}$。

复杂度 $O(n^3)$，前缀和优化一下就 $O(n^2)$。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e3 + 5, mod = 998244353;
int n, u, v, f[N][N], ans = 1;
vector<int> to[N];

inline void dfs(int u, int fa, int dep){
	bool leaf = true; 
	for(auto v : to[u]) if(v ^ fa) leaf = false, dfs(v, u, dep + 1);
	for(int i = 0; i <= dep - 1; ++i){
		int res = 1;
		for(auto v : to[u]) if(v ^ fa) res = res * f[v][i + 1] % mod;
		f[u][i] = ((!i ? 0 : f[u][i - 1]) + res) % mod;
	}
	if(leaf) for(int i = 0; i <= dep - 1; ++i) f[u][i] = i + 1;
}
signed main(){
	cin >> n;
	for(int i = 1; i < n; ++i) scanf("%lld%lld", &u, &v), to[u].push_back(v), to[v].push_back(u);
	dfs(n, 0, 0);
	for(auto v : to[n]) ans = ans * f[v][0] % mod;
	cout << ans;
	return 0;
}
```

---

## 作者：lyhqwq (赞：0)

# Solution

神题。

注意到原树 $n$ 号点特殊的性质，我们以 $n$ 号点为根，这棵树满足它的每棵子树中编号最大的节点都是根节点。

删掉原树的 $n-1$ 条边，对应的图 $G$ 上加了 $n-1$ 条边，所以图 $G$ 是一棵树。

接下来考虑一个点 $u$，如果 $u$ 向它的祖先 $v$ 连边，那么一定满足 $u$ 的父边已经被删除，且 $v$ 是 $u$ 的祖先中深度最大的父边被删除的点。

考虑这样一种不合法的方案，$x$ 为 $u$ 到 $v$ 的路径上的点，$y$ 为 $v$ 到根路径上的点。此时 $(x,y)$ 与 $(u,v)$ 两条边存在交叉。若没有交叉， 我们一定可以构造一个合法的排列。

令 $f_{u,i}$ 表示以 $u$ 为根的子树，$u$ 的祖先有 $i$ 个可以与 $u$ 连边，考虑枚举 $u$ 和哪个祖先连边，有 $f_{u,i}=\sum\limits_{j=1}^i\prod\limits_v f_{v,j+1}$。前缀和优化可做到 $O(n^2)$。

# Code
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=3005;
const int Mod=998244353;
struct edge{
    int v,nxt;
}edge[N<<1];
int head[N],cnt;
int n;
LL f[N][N],g[N][N];
int dep[N];
void addedge(int u,int v){
    edge[++cnt].v=v,edge[cnt].nxt=head[u],head[u]=cnt;
}
void dfs(int u,int fa){
    for(int j=2;j<=dep[u]+1;j++) g[u][j]=1;
    int son=0;
    for(int i=head[u];i;i=edge[i].nxt){
        int v=edge[i].v;
        if(v==fa) continue;
        son++;
        dep[v]=dep[u]+1;
        dfs(v,u);
        for(int j=2;j<=dep[u]+1;j++) g[u][j]=g[u][j]*f[v][j]%Mod;
    }
    if(!son) for(int j=1;j<=dep[u];j++) f[u][j]=j;
    else for(int j=1;j<=dep[u];j++) f[u][j]=(f[u][j-1]+g[u][j+1])%Mod;

}
int main(){
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs(n,0);
    LL ans=1;
    for(int i=head[n];i;i=edge[i].nxt){
        int v=edge[i].v;
        if(v==n) continue;
        ans=(ans*f[v][1])%Mod;
    }
    printf("%lld\n",ans);
    return 0;
}

```

---

