# Shuffle

## 题目描述

Two hungry red pandas, Oscar and Lura, have a tree $ T $ with $ n $ nodes. They are willing to perform the following shuffle procedure on the whole tree $ T $ exactly once. With this shuffle procedure, they will create a new tree out of the nodes of the old tree.

1. Choose any node $ V $ from the original tree $ T $ . Create a new tree $ T_2 $ , with $ V $ as the root.
2. Remove $ V $ from $ T $ , such that the original tree is split into one or more subtrees (or zero subtrees, if $ V $ is the only node in $ T $ ).
3. Shuffle each subtree with the same procedure (again choosing any node as the root), then connect all shuffled subtrees' roots back to $ V $ to finish constructing $ T_2 $ .

After this, Oscar and Lura are left with a new tree $ T_2 $ . They can only eat leaves and are very hungry, so please find the maximum number of leaves over all trees that can be created in exactly one shuffle.

Note that leaves are all nodes with degree $ 1 $ . Thus, the root may be considered as a leaf if it has only one child.

## 说明/提示

In the first test case, it can be shown that the maximum number of leaves is $ 4 $ . To accomplish this, we can start our shuffle with selecting node $ 3 $ as the new root.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1984E/0496f1e53b8faef700719d0f92212c9f9e0075c9.png)  Next, we are left only with one subtree, in which we can select node $ 2 $ to be the new root of that subtree.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1984E/a280b18a5bea58b0f12cdd08ee4e52dbe699c78a.png)  This will force all $ 3 $ remaining nodes to be leaves, and once we connect them back to our new root, the shuffled subtree looks like this:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1984E/7cf63ffdc63a80cf27ff8fce3a8da6cd1e9078f0.png)  We connect the shuffled subtree back to our new root of our new tree. Our final tree has four leaves (including the root), and looks like this:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1984E/4a077e6e7f7254d7c89391723da6791d33896856.png)In our second test case, we have a line of five nodes. It can be shown that the maximum number of leaves after one shuffle is $ 3 $ . We can start off with node $ 2 $ , which forces node $ 1 $ to become a leaf. Then, if we select node $ 4 $ on the right side, we will also have nodes $ 3 $ and $ 5 $ as leaves.

The third test case is a star graph with six nodes. The number of leaves cannot increase, thus our answer will be $ 5 $ (if we start the shuffling with the original root node).

## 样例 #1

### 输入

```
4
5
1 2
1 3
2 4
2 5
5
1 2
2 3
3 4
4 5
6
1 2
1 3
1 4
1 5
1 6
10
9 3
8 1
10 6
8 5
7 8
4 6
1 3
10 1
2 7```

### 输出

```
4
3
5
6```

# 题解

## 作者：Fesdrer (赞：9)

手玩一下数据可以发现，操作等价于将一棵树不断删点，直到每个连通块只有一个点，则剩下点的数量的最大值即为答案。特别的，如果一开始删的点是叶子，则答案要加一。

因此容易发现，如果一开始删的不是叶子，则答案就是整颗树的最大独立集，如果一开始删的是叶子，答案就是整颗树除去这个叶子后的树的最大独立集。很快我们就会发现，一开始删叶子是更优的，这是因为对于一开始删非叶子的情况，其答案是整颗树的最大独立集，如果最大独立集中有叶子，那么我们一开始先把这个叶子删了，答案只增不减；如果最大独立集没有叶子，则随便选一个叶子删了答案也只增不减。因此先删叶子更优，只要考虑先删叶子的情况。

因此我们需要求出树的最大独立集，并且允许最多一个叶子和其父亲同时被选择。我们用树形 DP 解决，具体的，设 $f_{i,0/1,0/1}$ 表示在子树 $i$ 内，有 $0/1$ 对叶子和其父亲同时被选择，$i$ 本身选或没选的最大选择数量。$f_{i,0}$ 的转移和上司的舞会类似，即：
$$
f_{i,0,0}=\sum_y\max(f_{y,0,0},f_{y,0,1})\\
f_{i,0,1}=\sum_yf_{y,0,0}
$$
而 $f_{i,1,0}$ 则是在 $f_{i,0,0}$ 的基础上选择一个 $\max(f_{y,0,0},f_{y,0,1})$ 替换为 $\max(f_{y,1,0},f_{y,1,1})$。而 $f_{i,1,1}$ 既可以选择一个 $f_{y,0,0}$ 替换成 $f_{y,1,0}$，如果 $i$ 的儿子有叶子也可以直接加 $1$。

这样子转移即可。不要忘记考虑原树的根节点只有一个儿子的情况。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int T,n,f[N][2][2];
vector<int> e[N];
void dfs(int x,int fas){
	f[x][0][1]=f[x][1][1]=1,f[x][0][0]=f[x][1][0]=0;
	int mx1=0,mx2=0;
	for(int y:e[x])	if(y!=fas){
		dfs(y,x);
		f[x][0][0]+=max(f[y][0][0],f[y][0][1]);
		mx1=max(mx1,max(f[y][1][0],f[y][1][1])-max(f[y][0][0],f[y][0][1]));
		f[x][0][1]+=f[y][0][0];
		mx2=max(mx2,f[y][1][0]-f[y][0][0]);
		if(int(e[y].size())==1)	mx2=max(mx2,1);
	}
	f[x][1][0]=f[x][0][0]+mx1;
	f[x][1][1]=f[x][0][1]+mx2;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)	e[i].clear();
		for(int i=1,x,y;i<n;i++){
			cin>>x>>y;
			e[x].push_back(y),e[y].push_back(x);
		}
		dfs(1,0);
		int ans=max(max(f[1][0][0],f[1][0][1]),max(f[1][1][0],f[1][1][1]));
		if(e[1].size()==1)	ans=max(ans,f[1][0][0]+1);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：CCPSDCGK (赞：5)

题目操作可等价成每次删一个点，直到所有连通块大小都 $=1$，易知删掉的点集相当于点覆盖集，即留下的连通块是独立集，所以题目相当于让我们求出该树的**最大独立集**。

但这个转化有一个 bug，并**不是所有删去的点都不能成为叶子**，如果这个点本来就是叶子，且第一个去删它，那么这个点到最后还是叶子，那么答案就变成了去掉这个叶子的树的最大独立集 $+1$。

所以需要求出整棵树的最大独立集以及去掉任意一个叶子的最大独立集的最大值，直接设 $f_{u,0/1,0/1}$ 为以 $u$ 为根的子树中选不选 $u$，**有没有叶子没被选中**的最大独立集大小，转移是平凡的，这里不再赘述。

```cpp
vector<int> edge[200005];
int dp[200005][2][2];
void dfs(int u,int f){
	if(sz(edge[u])==1) dp[u][0][1]=0;
	dp[u][0][0]=0,dp[u][1][0]=1;
	for(int v:edge[u]) if(v^f){
		dfs(v,u);
		dp[u][0][1]=max(dp[u][0][0]+max(dp[v][0][1],dp[v][1][1]),dp[u][0][1]+max({dp[v][0][0],dp[v][0][1],dp[v][1][0],dp[v][1][1]}));
		dp[u][0][0]+=max(dp[v][0][0],dp[v][1][0]);
		dp[u][1][1]=max(dp[u][1][0]+dp[v][0][1],dp[u][1][1]+max(dp[v][0][0],dp[v][0][1]));
		dp[u][1][0]+=dp[v][0][0];
	}
}
int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++) edge[i].clear();
		for(int i=1;i<=n;i++) dp[i][0][0]=dp[i][0][1]=dp[i][1][0]=dp[i][1][1]=-inf;
		for(int i=1;i<n;i++){
			int u,v;cin>>u>>v;
			edge[u].eb(v),edge[v].eb(u);
		}
		if(n==2){
			cout<<2<<endl;continue;
		}
		for(int i=1;i<=n;i++) if(sz(edge[i])>1){
			dfs(i,0);
			cout<<max({dp[i][0][0],dp[i][1][0],dp[i][0][1]+1,dp[i][1][1]+1})<<endl;
			break;
		}
	}
	return 0;
}
```

---

## 作者：Lu_xZ (赞：2)

### E

把一个点的父亲儿子都加到 $T_2$ 后，这个点就是叶子，且与之直接相连的点都不是叶子。（所有相邻点都是这个点的祖先）。

所有的叶子构成一个独立集，我们找去除根后最大的，类似*上司的舞会*。

枚举每个节点作为初始的根，换根 dp。如果根本身就是叶子还要在加一。

具体来说，第一次扫描以 $1$ 为根求出 $f_{x, 1/0}$ 表示以 $x$ 为根的子树中 $x$ 选/不选的最大独立集：

$$
\begin{cases}f_{x, 0} = \sum_{y \in g_x} \max(f_{y, 0}, f_{y, 1}) \\ f_{x, 1} = \sum_{y \in g_x} f_{y, 0}\end{cases}
$$

第二次扫描求出 $h_{x, 1/0}$ 表示选/不选 $x$ 的最大独立集，$h_{1, 0/1} = f_{1, 0/1}$：
$$
\begin{cases}h_{x, 0} = \max(h_{fa, 1},\ f_{x, 0} + (h_{fa, 0} - \max(f_{x, 1}, f_{x, 0})))\\h_{x, 1} = f_{x, 1} + (h_{fa, 0} - \max(f_{x, 1}, f_{x, 0})) \end{cases}
$$

用 $h_{x, 0} + [x \texttt{ is leaf}]$ 更新答案。

```cpp
void solve() {
	int n;
	cin >> n;
	vector<vector<int>> g(n + 1);
	for(int i = 1; i < n; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].eb(y);
		g[y].eb(x);
	}
	vector<array<int, 2>> f(n + 1, {0, 0});
	auto dfs = [&](auto &&dfs, int x, int fa) -> void {
		f[x][0] = 0;
		f[x][1] = 1;
		for(int y : g[x]) {
			if(y != fa) {
				dfs(dfs, y, x);
				f[x][0] += max(f[y][0], f[y][1]);
				f[x][1] += f[y][0];
			}
		}
	};
	dfs(dfs, 1, 0);
	vector<array<int, 2>> h(n + 1);
	
	h[1][0] = f[1][0];
	h[1][1] = f[1][1];
	int ans = h[1][0] + (g[1].size() == 1);
	
	auto dfs2 = [&](auto &&dfs2, int x, int fa) -> void {
		int tmp = h[fa][0] - max(f[x][0], f[x][1]);
		h[x][1] = f[x][1] + tmp; 
		h[x][0] = max(h[fa][1], f[x][0] + tmp);
		tmp = h[x][0] + (g[x].size() == 1);
		ans = max(ans, tmp);
		for(int y : g[x]) {
			if(y != fa) {
				dfs2(dfs2, y, x);
			}
		}
	};
	for(int y : g[1]) {
		dfs2(dfs2, y, 1);
	}
	cout << ans << '\n';
}
```

---

