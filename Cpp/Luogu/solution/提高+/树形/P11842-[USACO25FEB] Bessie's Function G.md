# [USACO25FEB] Bessie's Function G

## 题目描述

Bessie 有一个特别的函数 $f(x)$，接收一个 $[1, N]$ 内的整数作为输入，并返回一个 $[1, N]$ 内的整数（$1 \le N \le 2 \cdot 10^5$）。她的函数 $f(x)$ 由 $N$ 个整数 $a_1 \ldots a_N$ 定义，其中 $f(x) = a_x$（$1 \le a_i \le N$）。

Bessie 希望这个函数是幂等的。换句话说，它应当对于所有整数 $x \in [1, N]$ 满足 $f(f(x)) = f(x)$。

Bessie 可以以代价 $c_i$ 将 $a_i$ 的值修改为 $[1, N]$ 内的任意整数（$1 \le c_i \le 10^9$）。求 Bessie 使 $f(x)$ 变为幂等所需要的最小总代价。

## 说明/提示

样例 1 解释：

我们可以修改 $a_1 = 4$，$a_4 = 4$，$a_5 = 4$。由于所有 $c_i$ 均等于 $1$，所以总代价等于 $3$，即修改的数量。可以证明，不存在仅进行 $2$ 次或更少修改的解。

样例 2 解释：

我们修改 $a_3 = 3$ 以及 $a_4 = 4$。总代价为 $2+5=7$。

- 测试点 $3$: $N \le 20$。
- 测试点 $4\sim 9$: $a_i \ge i$。
- 测试点 $10\sim 15$: 所有 $a_i$ 各不相同。
- 测试点 $16\sim 21$: 没有额外限制。

除此之外，在后三个子任务中，前一半的测试点将满足对于所有 $i$ 有 $c_i=1$。


## 样例 #1

### 输入

```
5
2 4 4 5 3
1 1 1 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
8
1 2 5 5 3 3 4 4
9 9 2 5 9 9 9 9```

### 输出

```
7```

# 题解

## 作者：MoonCake2011 (赞：8)

大金龙助阵。

![](https://cdn.luogu.com.cn/upload/image_hosting/mnrv67xm.png)

不难，发现此题的关系成一棵基环内向树。

尝试基环树找环然后 dp。

我们又发现修改只会将 $a_i$ 修改成 $i$，然后所有 $a_j=i$ 的数都可以满足条件，这是最优的。

于是对于每颗树，可以令 $dp_{i,0}$ 为不改变 $i$ 所求出的 $i$ 的子树的最小总代价，$dp_{i,1}$ 同理。

这有点像没有上司的舞会这道题，基础树形 dp。

```cpp
inline void dfs(int x,int fa){
	dp[x][1]=c[x];
	for(int i=head[x];i;i=nxt[i]){
		if(to[i]==fa) continue;
		dfs(to[i],x);
		dp[x][0]+=dp[to[i]][1];
		dp[x][1]+=min(dp[to[i]][0],dp[to[i]][1]);
	}
}
```

在环上的每个点 $t_1,t_2\dots t_m$，对他们的子树进行上面的树形 dp。

又继续考虑环形 dp。

设 $f_{i,0/1,0/1}$ 为编号为 $i$ 的节点，选或不选，环上的第一个点选或不选。

选择改变每个点的权值为 $dp_{i,1}$，不改变的为 $dp_{i,0}$。

对于每个环，最后将 $f$ 数组判断一个首尾相接就行了。

代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
struct node{
	int a,c,l,r;
}a[200010];
bool operator < (node x,node y){
	return x.c<y.c;
}
bool vis[200010];
int id[200010];
bool r[200010];
vector<int>rg;
int head[200010],to[200010],nxt[200010],tot;
inline void add(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
int dp[200010][2],f[200010][2][2];
inline void dfs(int x){
	dp[x][1]=a[x].c;
	for(int i=head[x];i;i=nxt[i]){
		if(r[to[i]]) continue;
		dfs(to[i]);
		dp[x][0]+=dp[to[i]][1];
		dp[x][1]+=min(dp[to[i]][0],dp[to[i]][1]);
	}
}
signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].a,add(a[i].a,i);
	for(int i=1;i<=n;i++) cin>>a[i].c;
//	sort(a+1,a+n+1);//最开始想贪心
//	memset(f,0x3f,sizeof f);
	int ans=0;
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		int x=i;
		while(!vis[x]) vis[x]=1,id[x]=i,x=a[x].a;
		if(id[x]<i) continue;
		rg.clear();
		while(!r[x]) r[x]=1,rg.push_back(x),x=a[x].a;
		int l=0,T=rg[rg.size()-1];
		if(rg.size()==1){//注意这里要特判
			dfs(T);
			ans+=dp[T][1]-a[T].c;//因为已经是自环了，所以减去修改根的权值，可以证明，这一定比 dp[T][0] 小
			continue;
		}
		for(int j=0;j<rg.size();j++){
			int t=rg[j];
			dfs(t);//树形 dp
			if(j>0){
				f[t][0][0]=f[l][1][0]+dp[t][0];
				f[t][0][1]=f[l][1][1]+dp[t][0];
				f[t][1][0]=min(f[l][0][0],f[l][1][0])+dp[t][1];
				f[t][1][1]=min(f[l][0][1],f[l][1][1])+dp[t][1];
			}
			else{
				f[t][0][0]=dp[t][0];
				f[t][0][1]=1e18;
				f[t][1][1]=dp[t][1];
				f[t][1][0]=1e18;
			}
			l=t;
		}
		ans+=min(f[T][0][1],min(f[T][1][1],f[T][1][0]));//首尾相接加入答案
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：SmokingTurtle (赞：7)

# 前置芝士
## 基环树和基环树森林
> 如果一张无向连通图包含恰好一个环，则称它是一棵基环树。
> 
> 如果一张有向连通图每个点的入度都为 1，则称它是一棵基环外向树。
> 
> 如果一张有向连通图每个点的出度都为 1，则称它是一棵基环内向树。
> 
> 多棵基环树可以组成基环森林，多棵基环外向树可以组成基环外向树森林，多棵基环内向树可以组成基环内向森林。
>
> ——摘自 [OIWIKI](https://oi-wiki.org/graph/concept/)

基环树一般的处理办法转化为树上问题+环上问题。具体来说，一般会将环断开，变为若干棵树，每棵树单独计算，最后在环上统计答案。

## tortoise-hare（乌龟-野兔）算法

见我的这篇[专栏](https://www.luogu.com.cn/article/pjde9p8z)

# 题意概括
给定数列 $a_1,a_2,\cdots,a_n$，你可以修改其的若干项，使得对于任意 $i$，满足 $a_{a_i}=a_i$。修改第 $i$ 项的代价为 $c_i$。
# 题目分析
## 建模
我们发现题目中用到了 $a_{a_i}$ 甚至 $a_{a_{a_i}}$ 这种东西，导致下标可能会无限套下去，直接做显然十分困难。

考虑一个非常典的模型：将数列下标视为点，然后从 $i$ 到 $a_i$ 连一条有向边。

此时，由于有 $n$ 个点，每个点有且仅有一条出边（出度为 $1$），所以图构成了一个基环树森林。

显然，连通块之间互不影响，所以我们单独考虑每一个基环树。

我们发现，如果要修改 $a_i$，那么一定会将 $a_i$ 修改成 $i$。证明比较显然：
> 对于一种将 $a_i$ 修改为 $x\ \left(x\neq i\right)$ 的方案，我们知道此时不存在满足 $a_j=i$ 的 $j$（不然 $a_j=i\text{ 而 }a_{a_j}=x$）。既然如此，我们只需要考虑 $i$ 和 $a_i$ 的代价。
>
> 此时，如果 $a_i\neq i$，那么要求 $a_{a_i}=a_i$。然而，如果将 $a_i$ 改为 $i$，则不会增加代价，而且不会出现这条附加限制，所以肯定不劣。

接下来，我们考虑不修改的 $i$。对于这样的 $i$，要求 $a_{a_i}=a_{i}$。

于是，现在问题变成了：在基环树上选择若干个点，使得如果 $i$ 没有选择，那么 $i$ 的出边指向的节点必须选。

我们考虑转化为树上问题+环上问题（前文所说的套路）。


## 求解

### 找环
这里可以用前文所说的 tortoise-hare 算法。

### 树上部分
对于树上部分，他是一个比较典的树形 DP 题目。在[没有上司的舞会](https://www.luogu.com.cn/problem/P1352)这道题中将最大化收益改为最小化代价即可。具体的，令  $r_i$ （那道题中的快乐度）等于 $-c_i$（本题中的代价的相反数）即可。

大概思路是令 $dp_{i,0/1}$ 表示以 $i$ 为根的子树，$i$ 选/不选的代价。

转移方程：

$$dp_{i,0}=c_i+\sum\limits_{u\text{ 是 }i\text{ 的儿子}}\min(dp_{u,0},dp_{u,1})$$
$$dp_{i,1}=\sum\limits_{u\text{ 是 }i\text{ 的儿子}}dp_{u,0}$$

**upd 2025/03/23：第二个方程之前打错了，感谢 @[lcy6](/user/1396083)**

原因读者可以自行推导或者看上面提到的[没有上司的舞会](https://www.luogu.com.cn/problem/P1352)的题解，这里不再赘述。

### 环上问题
不妨设这个环上的所有点依次为 $ring_0,ring_1,\cdots,ring_{len-1}$。其中 ，$a_{ring_0}=ring_1,a_{ring_1}=ring_2,\cdots,a_{ring_{len-2}}=ring_{len-1},a_{ring_{len-1}}=ring_0$。

环上问题一般有三种解法：
1. 将环复制两遍，转化为在一个长度为 $2\times len$ 的序列上面寻找一个最优的长度为 $len$ 的区间。这个是最基础的，但是一般较慢（因为区间有 $O(n^2)$ 个）
2. 随意找一个地方将环断开，然后枚举最后一项和第一项之间的关系，转化为两个相似的序列问题。例题：[P6064 Naptime](https://www.luogu.com.cn/problem/P6064)。
3. 设每个点的答案分别为 $dp_1, dp_2,\cdots, dp_n$，求出相互之间关系，高斯消元求解。这种方法一般适用于期望 DP，较为复杂，超出了本题的讨论范围。

这里，我们肯定是选用第二种方法。具体的，设 $f_{i,0/1}$ 表示考虑 $ring_0,ring_1,\cdots ,ring_i$，其中 $ring_i$ 选/不选的答案。

那么转移方程和 $dp$ 数组类似：
$$f_{i,0}=dp_{ring_i,0}+\min(f_{i-1,0},f_{i-1,1})$$
$$f_{i,1}=dp_{ring_i,1}+f_{i-1,0}$$

其实维护两个变量即可，但是感觉这样稍微清晰一点。

那么初始值和最终答案是多少呢？那我们枚举 $ring_{len-1}\sim ring_0$ 的情况：
1. $ring_{len-1}$ 的 $a$ 值不修改：
> 此时，$ring_0$ 必须修改，所以 $f_{0,0}=dp_{ring_0,0},\ f_{0,1}=+\infin$。由于我们钦定 $ring_{len-1}$ 的 $a$ 不修改，所以最终答案为 $f_{len-1,1}$。
2. $ring_{len-1}$ 的 $a$ 值修改：
> 此时，$ring_0$ 可以修改也可以不修改，所以 $f_{0,0}=dp_{ring_0,0},\ f_{0,1}=dp_{ring_0,1}$。由于我们钦定 $ring_{len-1}$ 的 $a$ 修改，所以最终答案为 $f_{len-1,0}$。

因此，对于这两种情况，我们各自计算一次 $f$，然后将 $f_{len-1,1/0}$ 取一个 $\min$ 即可。

### 总结
现在，我们已经做完了这道题，再简要总结一下方法：
1. 首先，我们找到所有连通块。
2. 其次，对于每个连通块，我们找到环。
3. 然后，我们断开环上的边，对于环上每个点都作为根跑一遍树形 DP。
4. 接着，在环上再跑两次 DP 统计答案。
5. 最后，把所有连通块的答案全部加起来得到最终答案。
## code
```cpp
#include<iostream>
#include<vector>
using namespace std;
long long dp[200005][2],f[200005][2],c[200005];
bool done[200005],onring[200005];
vector<int> out[200005],ring;
const long long inf=4e18;
int in[200005];
void dfs(int u)//求 dp 数组的值
{
	done[u]=1;
	dp[u][0]=(u!=in[u])*c[u];
	for(int v:out[u])
		if(!onring[v] && !done[v])
			dfs(v),dp[u][0]+=min(dp[v][0],dp[v][1]),dp[u][1]+=dp[v][0];
}
long long deal(int x)//处理包含 x 的连通块的答案
{
	ring.clear();
	int y=x;
	do ring.push_back(y),onring[y]=1,y=in[y]; while(y!=x);//找环
	for(int u:ring)	dfs(u);//计算dp
	int len=ring.size();
	if(len==1)	return min(dp[ring[0]][0],dp[ring[0]][1]);
	for(int i=0;i<len;i++)	f[i][0]=f[i][1]=inf;
	f[0][0]=dp[ring[0]][0];
	for(int i=1;i<len;i++)
		f[i][0]=min(f[i][0],min(f[i-1][0],f[i-1][1])+dp[ring[i]][0]),
		f[i][1]=min(f[i][1],f[i-1][0]+dp[ring[i]][1]);
	long long ans=min(f[len-1][0],f[len-1][1]);

	for(int i=0;i<len;i++)	f[i][0]=f[i][1]=inf;
	f[0][0]=dp[ring[0]][0];
	f[0][1]=dp[ring[0]][1];
	for(int i=1;i<len;i++)
		f[i][0]=min(f[i][0],min(f[i-1][0],f[i-1][1])+dp[ring[i]][0]),
		f[i][1]=min(f[i][1],f[i-1][0]+dp[ring[i]][1]);
	ans=min(ans,f[len-1][0]);
	return ans;
}
int main()
{
	int n;
	cin>>n;
	long long ans=0;
	for(int i=1;i<=n;i++)	cin>>in[i],out[in[i]].push_back(i);
	for(int i=1;i<=n;i++)	cin>>c[i];
	for(int i=1;i<=n;i++)
		if(!done[i])//如果i所在连通块没有被遍历
		{
			int x=in[i],y=i;
			while(x!=y)	x=in[in[x]],y=in[y];//Floyd's Tortoise and Hare algorithm 算法
			long long tmp=deal(x);
			ans+=tmp;//最终对所有连通块求和
		}
	cout<<ans<<endl;
}
```

---

## 作者：DengStar (赞：5)

推荐 [**在博客园中查看**](https://www.cnblogs.com/dengstar/p/18738170)

> ([题目链接](https://www.luogu.com.cn/problem/P11842)) 给定一个长度为 $N$ 的序列 $a$，定义映射 $f: [1, N] \to [1, N]$，$\forall 1 \le x \le N$，$f(x) = a_{x}$。你可以花费 $c_{i}$ 的代价把 $a_{i}$ 修改成 $[1, N]$ 中的任何整数，求：最少花费多少代价修改序列 $a$，使得 $\forall 1 \le x \le N$，$f(f(x)) = f(x)$。

画个图有助于加深我们对问题的理解。如果把 $[1, N]$ 中的整数看作节点，对每个 $x$，从 $x$ 向 $a_{x}$ 连一条有向边，就得到了一个有向图。把 $x$ 映射到 $f(x)$ 就相当于从 $x$ 出发走一步，把 $f(x)$ 映射到 $f(f(x))$ 就相当于从 $x$ 出发走两步（由于每个点只有一条出边，所以走的路径唯一确定）。$f(f(x)) = f(x)$ 就意味着：从 $x$ 出发走一步和两步到达的节点相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/ctjcvidf.png)

如图所示：上层点代表 $x$，下层点代表 $a_{x}$。第一次映射把上层的点映射到下一层，第二次映射在下层的点中沿出边行走一步。以样例 2 为例，只有节点 $1$ 和 $2$ 是满足要求的。

![](https://cdn.luogu.com.cn/upload/image_hosting/mmhuq1s8.png)

把 $a_{3}$ 和 $a_{4}$ 分别修改为 $3$ 和 $4$ 后，所有点都满足了要求。

可以总结出，满足条件的点 $x$ 有两种情况：

1. $x$ 有一个自环，即 $a_{x} = x$。
2. $a_{x}$ 有一个自环，即 $a_{a_{x}} = a_{x}$。

为了使 $f(f(x)) = f(x)$ 对所有 $x$ 都成立，要么 $x$ 自身有一个自环，要么 $a_{x}$ 有一个自环。有了这个观察之后，我们就知道：每次修改操作一定是把某个点改成自环，其它的改变一定不优于改成自环。（所以一个部分分是暴力枚举选择哪些点改成自环）

由于每个点的出边唯一，所以图实际上构成一个**内向基环树森林**。不妨假设图是连通的，如果不连通，则分别处理各个连通块。那么问题可以抽象成：给定一棵内向基环树，每个点有点权。对于每个没有自环的点 $u$（显然，在基环树上，最多有一个自环），必须在 $u$ 和 $u$ 连向的点中选择至少一个，求选择的点的最小点权和。（有点类似 **[最小点覆盖](https://oi-wiki.org/graph/concept/#%E7%82%B9%E8%A6%86%E7%9B%96)** 问题，但不完全相同。）

![](https://cdn.luogu.com.cn/upload/image_hosting/gijfts3x.png)

 _（样例 2 的图示：选择节点 3 和 4 是最优的）_ 

这个问题和树上最大权独立集很像，容易想到用 dp 解决这个问题。由于基环树可以看作树上多了一条边，不妨先忽略这条边，这样它就变成了一棵树。设 $f(u, 1/0)$ 表示在 $T(u)$ 内选择点，并且选/不选 $u$ 时，选择的点的最小点权和。容易列出转移方程：
$$
\begin{cases}
f(u, 0) = \sum_{v \in son(u)} f(v, 1) \\
f(u, 1) = \sum_{v \in son(u)} \min(f(v, 1), f(v, 0))
\end{cases}
$$
需要注意的是对于状态 $f(u, 0)$，由于没有选择 $u$，所以 $T(u)$ 中 $u$ 没有被覆盖。（这就是本问题和最小点覆盖问题的区别：这个问题中边是单向的；如果是无向图，那么这种情况下 $u$ 被覆盖）因此统计答案时 $f(root, 0)$ 不能作为答案，因为根节点没有被选上。

现在回到基环树的问题。处理基环树问题的常见套路是把环上的任意一个节点视为根，然后忽略根节点的出边，按照一棵树处理，最后解决根节点的出边对答案的影响。（例如基环树最大权独立集  [P1453 城市环路](https://www.luogu.com.cn/problem/P1453)）本题中，由于根节点 $root$ 和 $a_{root}$ 必须选择至少一个，所以我们做两次树形 dp，分别代表强制选择 $root$ 和强制选择 $a_{root}$。第一次 dp 的答案为 $f(root, 1)$，第二次 dp 时令 $f(a_{root}, 0) \gets +\infty$，答案为 $\min(f(root, 0), f(root, 1))$。

不过上述做法少考虑了一种情况：如果 $a_{root} = root$，那么“根节点 $root$ 和 $a_{root}$ 必须选择至少一个”这个限制就不存在了——$root$ 本身就有自环，因此不用选。此外，$f(root, 0)$ 也可以从 $f(v, 0), v \in son(root)$ 转移过来了。所以我们要特殊处理这种情况。

代码实现上，一个需要解决的问题是找到基环树上的环。对于内向基环树，这个问题相对容易：用拓扑排序，依次删除入度为 $0$ 的点，最后没有被删除的点就在环上。

```cpp
// dp in pseudo tree
#include<bits/stdc++.h>

using namespace std;

typedef long long i64;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

int n, rt;
bool flag;
i64 ans;
vector<int> a, c, deg, vis, cir, comp;
vector<vector<int>> G, T;
vector<array<i64, 2>> f;

void lable(int u) {
    vis[u] = 1, comp.push_back(u);
    for(int v: T[u]) {
        if(!vis[v]) lable(v);
    }
}

void dfs(int u) {
    f[u][0] = 0, f[u][1] = c[u];
    if(u != rt && (G[u].empty() || (G[u].size() == 1 && u == a[rt]))) { // leaf
        if(u == a[rt] && flag) f[u][0] = INF;
        return;
    }
    for(int v: G[u]) {
        if(v == rt) continue;
        dfs(v);
        if(u == rt && a[rt] == rt) f[u][0] += min(f[v][1],f[v][0]);
        else f[u][0] += f[v][1];
        f[u][1] += min(f[v][0], f[v][1]);
    }
    if(u == a[rt] && flag) f[u][0] = INF;
}

void solve(int s) {
    comp.clear(), lable(s);

    if(comp.size() == 1) return;

    queue<int> que;
    for(int u: comp) {
        if(deg[u] == 0) {
            que.push(u);
        }
    }
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        cir[u] = 0, deg[a[u]]--;
        if(deg[a[u]] == 0) {
            que.push(a[u]);
        }
    }

    rt = -1;
    for(int u: comp) {
        if(cir[u]) {
            rt = u; break;
        }
    }
    assert(rt != -1);

    i64 add = INF;
    flag = 0, dfs(rt), add = f[rt][1];
    if(a[rt] == rt) {
        add = min(f[rt][0], f[rt][1]);
        ans += add;
        return;
    }
    if(a[rt] == rt) add = min(add, f[rt][0]);
    flag = 1, dfs(rt), add = min({add, f[rt][0], f[rt][1]});
    ans += add;
}

int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);

    cin >> n;
    a.resize(n + 1), c.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    G.resize(n + 1), T.resize(n + 1), deg.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        G[a[i]].push_back(i);
        T[a[i]].push_back(i), T[i].push_back(a[i]);
        deg[a[i]]++;
    }

    vis.resize(n + 1), cir.resize(n + 1, 1);
    f.resize(n + 1, {0, 0});
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            solve(i);
        }
    }

    cout << ans << '\n';

    return 0;
}
```

[USACO AC 记录](https://usaco.org/current/viewsource.php?sid=7241847) | [洛谷 AC 记录](https://www.luogu.com.cn/record/206119384)

---

## 作者：未来姚班zyl (赞：1)

### 题目大意

给定长度、值域为 $n$ 的序列 $a_{1\sim n}$。定义 $f(x)=a_x$，定义序列 $a_{1\sim n}$ 合法，当且仅当对于 $1\le i\le n,f(f(x))=f(x)$。

给定序列 $c_{1\sim n}$，你可以花费 $c_i$ 的代价修改 $a_i$，求出让 $a$ 合法的最小代价，要求线性。

### 题目分析

图论建模。建边 $i\rightarrow a_i$，则要求每个点 $x$ 指向的点 $y$ 必须指向点 $y$。所以我们修改一个点 $i$ 最优一定是使 $a_i=i$。

由于出度都是 $1$，所以图为内向基环树森林，我们考虑分树上和环上 dp。

对于树上 dp，设 $dp_x$ 表示不修改 $x$，使得 $x$ 的子树合法的最小代价，$g_x$ 表示修改 $x$，$x$ 子树合法的最小代价。转移是树上背包板子。

环上更简单，断环为链即可，复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
#define yy puts("Yes"),exit(0)
#define nn puts("No"),exit(0)
#define YY return puts("Yes"),void()
#define	NN return puts("No"),void()
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=2e5+5,M=1e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,a[N],c[N],to[N];
vector<int>p[N];
int s[N],tp;
bool vis[N],inc[N];
inline int dfs(int x){
	vis[x]=1;
	if(to[x]==x)return s[++tp]=to[x],-1;
	if(vis[to[x]])return s[++tp]=to[x],to[x];
	int w=dfs(to[x]);
	if(w==-1)return -1;
	s[++tp]=to[x];
	return w==x?-1:w;
}
int dp[N],g[N];
inline void Dfs(int x){
	g[x]=c[x],vis[x]=1;
	E(x)if(!inc[y])Dfs(y),dp[x]+=g[y],g[x]+=min(dp[y],g[y]); 
}
int F[N],G[N];
inline void Main(){
	n=read();
	repn(i)to[i]=read(),p[to[i]].pb(i);
	repn(i)c[i]=read();
	int ans=0;
	repn(x)if(!vis[x]){
		tp=0,dfs(x);
		rep(i,1,tp)inc[s[i]]=1;
		rep(i,1,tp)Dfs(s[i]);
		if(tp==1)ans+=g[s[1]]-c[s[1]];
		else {
			int Ans=llf;
			rep(i,1,tp)F[i]=G[i]=llf;
			F[1]=g[s[1]],G[1]=dp[s[1]];
			rep(i,2,tp){
				F[i]=min(F[i-1],G[i-1])+g[s[i]],G[i]=F[i-1]+dp[s[i]];
			}
			Ans=min(Ans,F[tp]);
			F[1]=g[s[1]],G[1]=llf;
			rep(i,2,tp)F[i]=min(F[i-1],G[i-1])+g[s[i]],G[i]=F[i-1]+dp[s[i]];
			Ans=min(Ans,min(G[tp],F[tp]));
			ans+=Ans;
		}
	}
	cout <<ans;
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

题意可以转变为：给出一个内向基环树森林，更改 $i$ 节点的父节点的代价为 $c_i$，求最少需要多少的代价，才能使得 $\forall i\in[1,n],f_{f_i}=f_i$。

首先一个很显然的结论是如果更改 $i$ 的父节点，就一定是让 $f_i=i$。这一定比将 $f_i$ 改成其他的点更有价值，因为直接连向他的点也满足了限制。

这启示我们进行基环树 DP。$dp_{i,0/1}$ 表示已 $i$ 为根节点的子树达到要求，且 $i$ 选或不选所需要的最少的代价。处理方式就是经典的断环，然后强制限制。注意一定要特殊处理环是自环的情况。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int>son[200005]; bool vis[200005],ris[200005];
int n,ans,dp[200005][2],a[200005],v[200005],fp,sp;
int ms1p;
inline void dps(int p,bool bypa){
	vis[p]=1; dp[p][0]=dp[p][1]=0;
	for(int sp:son[p]){
		if(vis[sp]) continue;
		dps(sp,bypa), dp[p][0]+=dp[sp][1],
		dp[p][1]+=min(dp[sp][0],dp[sp][1]);
	}
	if(p==ms1p) dp[p][0]=1e15;
	if(a[p]!=p)dp[p][1]+=v[p]; if(bypa) vis[p]=0;
}
inline void fring(int p){
	ris[p]=1;
	int sp=a[p];
		if(ris[sp]){
			fp=p,::sp=sp;
		}
		else fring(sp);
}
signed main(){
	ios::sync_with_stdio(0); cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) cin>>v[i];
	for(int i=1;i<=n;++i)
		if(a[i]!=i) son[a[i]].emplace_back(i);
	for(int i=1;i<=n;++i)
		if(!vis[i]){
			fring(i);
			if(fp==sp){
				dps(fp,0); ans+=min(dp[fp][0],dp[fp][1]);
			}
			else{
				int ret=1e15;
				ms1p=sp; dps(fp,1);
				ret=min({ret,dp[fp][0],dp[fp][1]});
				ms1p=0; dps(fp,0);
				ret=min(ret,dp[fp][1]);
				ans+=ret;
			}
		}
	cout<<ans<<endl;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

注意到每个点要不连向一个自环，要不自己是一个自环。

故我们考虑基环树 dp，先搜出一个联通块的环，然后对于环上的点连的树进行树形 dp，最后再在环上进行 dp。

具体考虑 $f_{u, 0 / 1}$ 表示树上是否自环的最小操作数：

$$f_{u, 0} = \sum_{v \in son_u} f_{v, 1}$$

$$f_{u, 1} = \sum_{v \in son_u} \min(f_{v, 0}, f_{v, 1})$$

然后考虑 $g_{u, 0/ 1, 0/ 1}$ 表示环上第一个点/第 $i$ 个点是否自环的方案数，转移几乎差不多，这里就不详细说了。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll ans;
int n, top;
int a[N], w[N];
ll f[N][2], g[2][N][2];
bool vis[N], flag[N];
vector<int> V;
vector<int> E[N];
map<pair<int, int>, bool> mp;
inline void add(int u, int v){
	if(u > v)
	  swap(u, v);
	if(mp[{u, v}])
	  return ;
	mp[{u, v}] = 1;
	E[u].push_back(v);
	E[v].push_back(u);
}
inline void dfs(int u, int fa){
	vis[u] = 1;
	for(auto v : E[u]){
		if(v == fa)
		  continue;
		if(vis[v]){
			if(flag[v])
			  continue;
			top = v;
			flag[u] = 1;
			V.push_back(u);
		}
		else{
			int pre = top;
			dfs(v, u);
			if(!pre && top){
				flag[u] = 1;
				V.push_back(u);
				if(u == top)
				  top = 0;
			}
		}
	}
}
inline void Treedp(int u, int fa){
	f[u][1] = w[u];
	for(auto v : E[u]){
		if(v == fa || flag[v])
		  continue;
		Treedp(v, u);
		f[u][0] += f[v][1];
		f[u][1] += min(f[v][0], f[v][1]);
	}
}
inline void Circledp(){
	int len = V.size() - 1;
//	len = max(len, 0);
	g[0][0][0] = f[V[0]][0], g[1][0][0] = g[0][0][1] = g[1][0][1] = f[V[0]][1];
	for(int i = 1; i <= len; ++i){
		g[0][i][0] = g[0][i - 1][1] + f[V[i]][0];
		g[0][i][1] = min(g[0][i - 1][0], g[0][i - 1][1]) + f[V[i]][1];
		g[1][i][0] = g[1][i - 1][1] + f[V[i]][0];
		g[1][i][1] = min(g[1][i - 1][0], g[1][i - 1][1]) + f[V[i]][1];		
	} 
	ans += min(g[0][len][1], g[1][len][0]);
}
inline void getdp(int i){
	if(V.empty()){
		Treedp(i, 0);
		ans += min(f[i][0], f[i][1]);
		return ;
	}
	for(auto u : V)
	  Treedp(u, 0);
	Circledp();
	V.clear();
}
bool End;
int main(){
	n = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		if(i != a[i])
		  add(i, a[i]);
		else
		  vis[i] = 1;
	}
	for(int i = 1; i <= n; ++i){
		w[i] = read();
		if(vis[i])
		  w[i] = vis[i] = 0;
	}
	for(int i = 1; i <= n; ++i){
		if(vis[i])
		  continue;
		dfs(i, 0);
		getdp(i);
	}
	write(ans);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}

```

---

## 作者：Jorisy (赞：0)

连边 $i\to a_i$，有一个内向基环树森林。考虑 $f(i)=f(f(i))$ 等价于自环 $i\to i$ 或一条边连向一个自环 $i\to j\to j$。

套路地，我们考虑对树和环分别 dp。记 $f_{i,0/1}$ 表示节点 $i$ 为根的子树，且 $i$ 连向父亲/自己的最小代价。转移是容易的。

对环上断环后有同理的 $g_{i,0/1}$。

赛时代码写得稍许烦了一点。
```cpp
#include<bits/stdc++.h>
#define N 200005
#define ll long long
#define mod 
using namespace std;

struct dsuni{
    int fa[N];
    void init(int n){iota(fa+1,fa+n+1,1);}
    int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
    void merge(int u,int v)
    {
        u=find(u);
        v=find(v);
        if(u==v) return;
        fa[v]=u;
    }
}dsu;
vector<pair<int,int>>tr[N];
vector<int>v;
int n,a[N],c[N];
bool vis[N],cir[N],fl;
ll ans,f[N][2],g[N][2];// 0:fa 1:self

void dfs0(int x,int lst=0)
{
    cir[x]=1;
    v.push_back(x);
    for(auto i:tr[x])
    {
        int y=i.first,id=i.second;
        if(id==lst) continue;
        if(cir[y])
        {
            v.push_back(y);
            fl=1;
            return;
        }
        dfs0(y,id);
        if(fl) return;
    }
    cir[x]=0;
    v.pop_back();
}

void dfs(int x,int lst=0)
{
    vis[x]=1;
    f[x][0]=0;
    f[x][1]=c[x];
    for(auto i:tr[x])
    {
        int y=i.first,id=i.second;
        if(y==lst||cir[y]) continue;
        dfs(y,x);
        f[x][0]+=f[y][1];
        f[x][1]+=min(f[y][0],f[y][1]);
    }
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    dsu.init(n);
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        dsu.merge(x,i);
        tr[x].push_back({i,i});
        tr[i].push_back({x,i});
    }
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=n;i++)
    {
        if(vis[i]) continue;
        v.clear();
        fl=0;
        dfs0(i);
        for(auto j:v) cir[j]=0;
        auto vec=v;
        v.clear();
        bool fl=0;
        for(auto j:vec)
        {
            if(cir[j]) break;
            if(!fl&&j==*--vec.end()) fl=1;
            if(fl) v.push_back(j),cir[j]=1;
        }
        for(auto j:v) dfs(j);
        if(v.size()==1)
        {
            ans+=min(f[v[0]][0],f[v[0]][1]-c[v[0]]);
            continue;
        }
        int m=v.size();
        g[0][0]=f[v[0]][0];
        g[0][1]=1e18;
        for(int j=1;j<m;j++)
        {
            g[j][0]=g[j-1][1]+f[v[j]][0];
            g[j][1]=min(g[j-1][0],g[j-1][1])+f[v[j]][1];
        }
        ll val=g[m-1][1];
        g[0][0]=1e18;
        g[0][1]=f[v[0]][1];
        for(int j=1;j<m;j++)
        {
            g[j][0]=g[j-1][1]+f[v[j]][0];
            g[j][1]=min(g[j-1][0],g[j-1][1])+f[v[j]][1];
        }
        ans+=min({val,g[m-1][0],g[m-1][1]});
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

连边 $(i,a_i)$，连成一个内向基环树森林。修改一个点相当于任意重定向这个点的出边。要求将这个森林中的每一棵基环树改为环长为 $1$，树高不超过 $2$ 的基环树。

首先发现修改一个点指向自己一定不劣，因为既可以将自己改为合法，又能将有边连向它的点变为合法。

每棵基环树都是独立的。问题可以拆成两部分：环部分和非环部分。

对于非环部分，删掉基环树的环，将原来环上的点定为根。显然当 $u$ 改时儿子可改可不改，否则儿子必须改。于是设 $f_{u,0/1}$ 表示考虑 $u$ 为根的子树，$u$ 不修改/修改出边，使这颗子树合法的最小代价。则 $f_{u,0}=\sum_{v\isin \text{son}_u}f_{v,1},f_{u,1}=c_u+\sum_{v\isin \text{son}_u}{\min(f_{v,0},f_{v,1})}$。

接下来考虑环部分的问题，单独提取出环上的点，先直接断环为链，设 $g_{i,0/1}$ 表示考虑到 $i$，$i$ 不改/改的最小代价，则 $g_{i,0}=g_{i-1,1},g_{i,1}=\min(g_{i-1,0},g_{i-1,1})+f_{i,1}$。考虑原先环的限制，先初始化 $g_{1,0}=0,g_{1,1}=\inf$，跑一遍后取 $g_{c,1}$；再初始化 $g_{1,0}=\inf,g_{1,1}=f_{1,1}$，跑一遍后取 $\min(g_{c,0},g_{c,1})$ 即可。

时间复杂度：$\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define mp make_pair 
#define pob pop_back
using namespace std;
typedef long long ll;
const ll maxn=200007,ee=1e18;
ll n,a[maxn],c[maxn],f[maxn][2],vis[maxn],v2[maxn],ans;
vector<ll> edge[maxn],st,vec[maxn];
void dfs(ll u){
	for(auto v:edge[u]){
		dfs(v);
		f[u][0]+=f[v][1],f[u][1]+=min(f[v][0],f[v][1]);
	}
	f[u][1]+=c[u];
}
int main(void){
    //freopen("data.in","r",stdin); 
    //freopen("data.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>c[i];
    for(ll i=1,u;i<=n;i++)if(!vis[i]){
    	st.clear();
    	for(u=i;;vis[u]=i,u=a[u]){
    		st.pb(u);
    		if(vis[u]) break;
    	}
    	if(vis[u]==i){
    		vec[u].pb(u),v2[u]=1;
    		for(ll v=a[u];v!=u;v=a[v]) vec[u].pb(v),v2[v]=1;
    	}
    	for(ll j=0;j<st.size()-1;j++){
    		if(v2[st[j]]) break;
    		edge[st[j+1]].pb(st[j]);
    	}
    }
    for(ll i=1,cur,m,g0,g1,gl0,gl1;i<=n;i++)if(!vec[i].empty()){
    	cur=ee;
    	for(auto x:vec[i]) dfs(x);
    	if(vec[i].size()==1){ans+=f[vec[i][0]][1]-c[vec[i][0]]; continue;}
    	m=vec[i].size(); gl0=f[vec[i][0]][0],gl1=ee;
    	for(ll j=1;j<m;j++){
    		g0=gl1+f[vec[i][j]][0],g1=min(gl0,gl1)+f[vec[i][j]][1];
    		gl0=g0,gl1=g1;
    	}
    	cur=min(cur,g1); gl0=ee,gl1=f[vec[i][0]][1];
    	for(ll j=1;j<m;j++){
    		g0=gl1+f[vec[i][j]][0],g1=min(gl0,gl1)+f[vec[i][j]][1];
    		gl0=g0,gl1=g1;
    	}
    	cur=min(cur,min(g0,g1));
    	ans+=cur;
    }
	cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：Wei_Han (赞：0)

简单题。

我们令 $i \to a_i$，那么 $f_i$ 与 $f_{a_i}$ 只要有一个被修改就合法了，这样的话，所有的连边会形成内向基环树森林，问题变成在基环树上求当前点与相邻节点至少有一个被选择的最小代价是什么，这个问题就很典了，对于基环树，我们找环上一条边断掉即可，然后对两边跑 dp，对于 dp，设 $f_{i,0/1}$ 表示以 $i$ 为根的子树内 $i$ 点是否选的最小代价，有转移 $f_{i,0} = \sum_{j \in son_i} f_{j,1}$，$f_{i,1} = \sum_{j\in son_i} \min(f_{j,1},f_{j,0})$，直接转移即可，对于选择的环上两点 $u,v$，他们两个至少有一个需要被取，所以答案加上 $\min(f_{u,1},f_{v,1})$ 即可。

这是对于基环树的处理方式，类似的，我们发现有的点可能已经满足了 $a_i = i$，那么就令 $c_i \gets 0$，然后按正常树的处理办法处理就好了，对于二元环，因为断环之后不联通，所以特判一下也按照树的处理方式做就好了，记得还要特判 $a_i > n$ 的情况，直接累加 $c_i$ 就好了。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define pb push_back
//#define pis pair<ll,char >
//#pragma GCC optimize(2)
using namespace std;
//typedef int ll;
typedef long long ll;
//typedef __int128 ll;
typedef double db;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const ll N=2e6+5,M=5e6,mod=998244353;
ll a[N],c[N],f[N][2],g[N][2],vis[N],ans,flag,n;
vector<ll> G[N];pii cir;
queue<ll> q;map<pii,ll> mp1,mp;
inline void check(ll x,ll fa)
{
	vis[x]=1;q.push(x);
	for(ll y:G[x])
	{
		if(y==fa) continue;
		if(vis[y]) return cir={x,y},flag=1,void();
		check(y,x);if(flag) return;
	}
}
inline void Clear(ll x,ll fa){vis[x]=1;for(ll y:G[x]) if(y!=fa&&!vis[y]) Clear(y,x);}
inline void dfs(ll x,ll fa,ll (&f)[N][2])
{
	f[x][0]=0,f[x][1]=c[x];
	for(ll y:G[x])
	{
		if(mp1[{x,y}]||y==fa) continue;
		dfs(y,x,f);f[x][0]+=f[y][1];f[x][1]+=min(f[y][0],f[y][1]);
	}
}
inline void solve(ll x)
{
	cir={0,0};flag=0;check(x,0);while(q.size()) vis[q.front()]=0,q.pop();Clear(x,0);
	if(flag&&(mp[{cir.fi,cir.se}]!=1||mp[{cir.se,cir.fi}]!=1))
	{
		x=cir.fi;ll y=cir.se;
		mp1[{x,y}]=mp1[{y,x}]=1;
		dfs(x,y,f),dfs(y,x,g);
		ans+=min(f[x][1],g[y][1]);
		mp1[{x,y}]=mp1[{y,x}]=0;
	}
	else dfs(x,0,f),ans+=min(f[x][0],f[x][1]);
}
signed main(){
	read(n);fo(1,i,n) read(a[i]);fo(1,i,n) read(c[i]);fo(1,i,n) fo(0,j,1) f[i][j]=g[i][j]=INF;
	fo(1,i,n) if(a[i]==i) c[i]=0;fo(1,i,n) if(a[i]>n) ans+=c[i],vis[i]=1;else if(a[i]!=i){mp[{i,a[i]}]=1;if(!mp[{a[i],i}]) G[i].pb(a[i]),G[a[i]].pb(i);}
	fo(1,i,n) if(!vis[i]) solve(i);
	wr(ans),pr;
	return 0;
}
``````

---

