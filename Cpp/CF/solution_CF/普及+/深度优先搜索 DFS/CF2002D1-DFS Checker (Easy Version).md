# DFS Checker (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, the given tree is a perfect binary tree and the constraints on $ n $ and $ q $ are lower. You can make hacks only if both versions of the problem are solved.

You are given a perfect binary tree $ ^\dagger $ consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , and the root is the vertex $ 1 $ . You are also given a permutation $ p_1, p_2, \ldots, p_n $ of $ [1,2,\ldots,n] $ .

You need to answer $ q $ queries. For each query, you are given two integers $ x $ , $ y $ ; you need to swap $ p_x $ and $ p_y $ and determine if $ p_1, p_2, \ldots, p_n $ is a valid DFS order $ ^\ddagger $ of the given tree.

Please note that the swaps are persistent through queries.

 $ ^\dagger $ A perfect binary tree is a tree with vertex $ 1 $ as its root, with size $ n=2^k-1 $ for a positive integer $ k $ , and where the parent of each vertex $ i $ ( $ 1<i\le n $ ) is $ \left\lfloor\frac{i}{2}\right\rfloor $ . Thus, all leaves of this tree are at a distance $ k - 1 $ from the root.

 $ ^\ddagger $ A DFS order is found by calling the following $ \texttt{dfs} $ function on the given tree.

```
<pre class="lstlisting">```
dfs_order = []<br></br><br></br>function dfs(v):<br></br>    append v to the back of dfs_order<br></br>    pick an arbitrary permutation s of children of v<br></br>    for child in s:<br></br>        dfs(child)<br></br>dfs(1)<br></br>
```
```

Note that the DFS order is not unique.

## 说明/提示

In the first test case, the permutation $ p_1, p_2, \ldots, p_n $ after each modification is $ [1,3,2],[1,2,3],[3,2,1] $ , respectively. The first two permutations are valid DFS orders; the third is not a DFS order.

In the second test case, the permutation $ p_1, p_2, \ldots, p_n $ after each modification is $ [1,2,5,4,3,6,7],[1,3,5,4,2,6,7],[1,3,7,4,2,6,5],[1,3,7,6,2,4,5] $ , respectively.

## 样例 #1

### 输入

```
2
3 3
1 1
1 2 3
2 3
3 2
1 3
7 4
1 1 2 2 3 3
1 2 3 4 5 6 7
3 5
2 5
3 7
4 6```

### 输出

```
YES
YES
NO
YES
NO
NO
YES```

# 题解

## 作者：Harrylzh (赞：3)

思路不难，但是赛时写的代码极其抽象，最后没调出来遗憾离场。

## 思路

设变量 $tot$ 表示数组中父节点在 DFS 序相应位置的节点数量，$chk_i$ 表示该点是否满足上述要求。设 DFS 序中第 $i$ 个点的父亲节点在 DFS 序中时第 $f_i$ 项，当 $\frac{p_i}{2} = p_{f_i}$ 时节点 $i$ 满足要求。

当交换两个节点 $p_x,p_y$ 时，受到影响的点有：

- $x,y$
- $x$ 的左右儿子节点
- $y$ 的左右儿子节点

上述节点可能会重复，放进 set 容器处理即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[1000000+5];
int bz[1000000+5],cur=0;
int lz[1000000+5],rz[1000000+5];
void dfs(int stp,int fth)
{
	bz[++cur]=fth;
	if(!lz[fth]) lz[fth]=cur;
	else rz[fth]=cur;
	if((1<<(stp+1))-1==n) return;
	int p=cur;dfs(stp+1,p);dfs(stp+1,p);
}
bool chk[1000000+5];
void upd(int x){if(a[x]/2==a[bz[x]])chk[x]=1;else chk[x]=0;}
void sol()
{
	cur=0;
	cin>>n>>q;
	int tot=0;
	for(int i=0;i<=n+1;i++) lz[i]=0,rz[i]=0,bz[i]=0;//lz左儿子，rz右儿子，bz父亲（DFS 序中）
	for(int i=1;i<n;i++){int o;cin>>o;}
	dfs(0,0);
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		chk[i]=(a[i]/2==a[bz[i]]),tot+=chk[i];
	}
	while(q--)
	{
		int x,y;
		cin>>x>>y;
		swap(a[x],a[y]);
		set<int> st;
		st.insert(x),st.insert(y),st.insert(lz[x]),st.insert(lz[y]),st.insert(rz[x]),st.insert(rz[y]);
		for(set<int>::iterator it=st.begin();it!=st.end();++it)
		{
			if((*it)==0) continue;
			tot-=chk[*it],upd(*it),tot+=chk[*it]; 
		}
		if(tot==n) cout<<"YES\n";
		else cout<<"NO\n";
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		sol();
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

本来要掉大分的场，只因过了 D1 硬生生给我搞上分了，故写题解纪念。

题目良心地告诉我们简单版的 $n,q$ 较小，所以首先考虑暴力，每次修改，然后暴力检查 dfs 序是否合法。复杂度 $O(nq)$ 很明显过不去。因为每次仅仅交换两个节点，却要检查一整棵树，浪费了大量时间。

我们可以对于每次交换只检查该节点的两个儿子是否合法。也就是如果该节点为 $i$，则两个儿子是否为 $2i$ 和 $2i+1$。但是在 dfs 序上怎么找到两个儿子的位置呢？可以先预处理出这棵完美二叉树每个节点的深度和最大深度，分别记作 $dep_i$ 和 $m$。某个节点对应的 dfs 序记作 $num_i$。那么对于点 $x$，他的左儿子的 dfs 序就是 $num_x+1$，右儿子的 dfs 序就是 $num_x+2^{m-dep_x}$。然后根据完美二叉树的性质，检查这两个点是否为 $x$ 的儿子即可。

对于每次交换，我们需要检查被交换的两个节点和他们的父节点是否合法。可以开个数组来记录。检查之后更新一下非法节点个数，如果没有非法节点说明该 dfs 序合法。

```cpp
#include<bits/stdc++.h>
#define N (1<<16)
#pragma GCC optimize("O3")
using namespace std;
int n,m,q,cnt,a[N],dep[N],vis[N],num[N];
bool check(int x)
{
	if(dep[x]==m) return 1;
	if((num[x]+1)>n||num[x]+(1<<(m-dep[x]))>n) return 0;
	if(x!=a[num[x]+1]/2||x!=a[num[x]+(1<<(m-dep[x]))]/2) return 0;
	return 1;
}
void solve()
{
	cin>>n>>q;
	cnt=0;
	for(int i=1;i<=n;i++) vis[i]=0,dep[i]=dep[i/2]+1;
	for(int i=1;i<=16;i++) if(n==((1<<i)-1)) m=i;
	for(int i=1;i<n;i++) {int x;cin>>x;}
	for(int i=1;i<=n;i++) cin>>a[i],num[a[i]]=i;
	for(int i=1;i<=n;i++) if(!check(i)) cnt++,vis[i]=1;
	while(q--)
	{
		int x,y;
		cin>>x>>y;
		swap(num[a[x]],num[a[y]]);
		swap(a[x],a[y]);
		if(dep[a[x]]<m)
		{
			if(check(a[x]))
			{
				if(vis[a[x]]) cnt--;
				vis[a[x]]=0;
			}
			else
			{
				if(!vis[a[x]]) cnt++;
				vis[a[x]]=1;
			}
		}
		if(dep[a[y]]<m)
		{
			if(check(a[y]))
			{
				if(vis[a[y]]) cnt--;
				vis[a[y]]=0;
			}
			else
			{
				if(!vis[a[y]]) cnt++;
				vis[a[y]]=1;
			}
		}
		if(a[x]!=1)
		{
			if(check(a[x]/2))
			{
				if(vis[a[x]/2]) cnt--;
				vis[a[x]/2]=0;
			}
			else
			{
				if(!vis[a[x]/2]) cnt++;
				vis[a[x]/2]=1;
			}
		}
		if(a[y]!=1)
		{
			if(check(a[y]/2))
			{
				if(vis[a[y]/2]) cnt--;
				vis[a[y]/2]=0;
			}
			else
			{
				if(!vis[a[y]/2]) cnt++;
				vis[a[y]/2]=1;
			}
		}
		if(cnt==0) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：masonxiong (赞：0)

# 题目分析

> 题解记号说明：
>
> - $f_i$ 是 $i$ 号节点的父节点。特别的，有 $f_1=1$。
> - $a_i$ 是 $i$ 号节点全体祖先节点（含其自身）构成的集合。特别的，有 $a_1=\{1\}$。

这场做起来最顺手的题目就是 D 了。

每次 $O(n)$ 暴力判断 $p$ 是否合法显然不可取。那么我们就需要对于每次操作维护一些东西，使得查询合法情况可以 $O(1)/O(\log n)$。

我们知道，若 $p$ 是一个合法的 DFS 序，等价于 $p$ 满足这个性质：

- $\forall i\in[1,n-1]\cap\Z,f_{p_{i+1}}\in a_{p_i}$。

注意，**这是充分必要条件**。下面我们对这个性质进行证明。

---

## 充分性证明

即：**若 $p$ 是一个合法的 DFS 序，则 $\forall i\in[1,n-1]\cap\Z,f_{p_{i+1}}\in a_{p_i}$。**

我们按照 $p_i$ 号节点在树中的位置进行分类讨论：

---

### 它是一个非叶子节点

若 $p_i$ 号节点是一个非叶子节点，那么在 DFS 函数中的下一步操作肯定是**访问它的一个子节点**，也就是 $p_{i+1}$ 号节点。那么 $f_{p_{i+1}}$ 就是 $p_i$，满足这条性质。

---

### 它是一个叶子节点

若 $p_i$ 号节点是一个叶子节点，那么在 DFS 函数中的下一步操作肯定是**回溯**，也就是跳回到 $p_i$ 号节点的某个祖先节点，然后访问这个祖先节点的另一个没被访问过的子节点 $p_{i+1}$。那么根据定义 $f_{p_{i+1}}$ 是 $p_i$ 的某个祖先节点，满足这条性质。

---

充分性证明完毕。

---

## 必要性证明

即：**若 $p$ 满足 $\forall i\in[1,n-1]\cap\Z,f_{p_{i+1}}\in a_{p_i}$，则 $p$ 是一个合法的 DFS 序。**

我们任取一个编号为 $u$ 的节点，记以 $u$ 号节点为根的子树为 $U$，并取任何一对 $p_i,p_{i+1}$ 满足 $p_i\notin U,p_{i+1}\in U$。因为 $f_u$ 有不属于 $U$ 的节点（例如 $f_u$ 本身就不属于 $U$），所以有 $p_{i+1}=u$。

这样，我们知道每一个子树至多被访问一次，且肯定在一个合法 DFS 序中的一个连续的子序列中，并且第一个访问到的节点肯定是这个子树的根节点。这足以说明 $p$ 是一个合法的 DFS 序了。

---

# 题目做法

我们有了这条性质，那我们就可以对于每一个 $i\in[1,n-1]\cap\Z$，记录是否有 $vp_i=f_{p_{i+1}}\in a_{p_i}$。同时记录满足此性质的 $i$ 的数量 $vc$。

每次操作时，更新 $x,y$ 所对应的 $vp_x,vp_y$ 以及 $vc$，判断是否有 $vc=n-1$。若满足，则合法；否则不合法。

那么现在的重点就在于：**给定 $i$，判断是否有 $f_{p_{i+1}}\in a_{p_i}$**。由于 D1 规定给出的是一个满二叉树，其深度 $h=O(\log n)$，所以我们有很多特殊的方法来解决这个问题：

- 我们大可直接存储每一个节点的全体祖先构成的集合，并随便找一个数据结构来维护（此处以 `std::unordered_set` 为例）。提前 $O(nh)$ 预处理后即可每次询问 $O(1)$ 回答每次询问。
- 将 $p_i$ 暴力向上跳，如果能经过 $f_{p_{i+1}}$ 则说明 $f_{p_{i+1}}\in a_{p_i}$。$O(nh)$ 预处理，$O(h)$ 回答每次询问。

其余高效解法见我的 D2 题解。

---

# 代码

以最简单的暴力跳为例。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int MaxN = 300000 + 5;
int T, N, Q, dfsTime, validCount;
int dfsOrder[MaxN], parent[MaxN];
bitset<MaxN> validPosition;

bool isAncestor(int ancestor, int descendant) {
	for (; descendant; descendant = parent[descendant])
		if (ancestor == descendant)
			return true;
	return false;
}

bool initialize() {
	cin >> N >> Q;
	validCount = 0;
	validPosition.reset();
	for (int i = 2; i <= N; cin >> parent[i++]);
	for (int i = 1; i <= N; cin >> dfsOrder[i++]);
	for (int i = 1; i < N; i++)
		validCount += validPosition[i] = isAncestor(parent[dfsOrder[i + 1]], dfsOrder[i]);
	return true;
}

bool updateAnswer(int x, int y) {
	function<void(int)> updateValidPosition = [&](int position) {
		if (position != 0 && position != N && isAncestor(parent[dfsOrder[position + 1]], dfsOrder[position]) ^ validPosition[position]) {
			validPosition[position] = isAncestor(parent[dfsOrder[position + 1]], dfsOrder[position]);
			validCount += validPosition[position] ? 1 : -1;
		}
	};
	swap(dfsOrder[x], dfsOrder[y]);
	updateValidPosition(x); updateValidPosition(x - 1);
	updateValidPosition(y); updateValidPosition(y - 1);
	return validCount == N - 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	for (cin >> T; T-- && initialize(); )
		for (int x, y; Q--; cout << (updateAnswer(x, y) ? "Yes\n" : "No\n"))
			cin >> x >> y;
	return 0;
}
```

---

## 作者：MhxMa (赞：0)

### 题意

给定一个根树和一系列查询，每次查询包括交换树的 dfs 序列中的两个元素，然后判断交换后的序列是否仍然是一个有效的 dfs 序列。

### 思路
先进行一遍 dfs，记录每个节点的访问顺序和子树大小。

判断 dfs 序列，对于每个查询，通过比较交换前后的时间戳和子树大小来判断是否仍然是有效的 dfs 序列。

为了提高效率，使用一个数组来记录每个节点在 dfs 序列中的有效区间，即第 $i$ 项记录的区间应该是 $[dfn_i,dfn_i + siz_i - 1]$ 。

简单搜索，用不着 LCA，不做过多解释，详见代码。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int T;
int f[N], p[N]; // 分别存储树中每个节点的父节点和 dfs 序列中的值。
int blk[N], dfn[N]; // 分别存储每个节点在 dfs 序列中的有效区间和时间戳。
int tot, head[N], dis[N];
int dfstime, siz[N];
int ans;

struct Node {
	int from, to;
} edge[N];

void addedge(int u, int v) {
	edge[++tot] = (Node) {
		v, head[u]
	};
	head[u] = tot;
}

void dfs(int u) {
	siz[u] = 1;
	dfn[u] = ++dfstime;
	for (int i = head[u]; i; i = edge[i].to) {
		int v = edge[i].from;
		dfs(v);
		siz[u] += siz[v];
	}
	return;
}

int check(int x, int y) {
	if (!x || x == y) {
		return 1;
	}
	if (dfn[y] >= dfn[x] && dfn[y] < dfn[x] + siz[x] && siz[y] == 1) {
		return 1;
	}
	return 0;
}

void update(int x) {
	ans -= blk[p[x]];
	blk[p[x]] = check(f[p[x]], p[x - 1]);
	ans += blk[p[x]];
	return ;
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		int n, q;
		scanf("%d%d", &n, &q);
		dfstime = 0, ans = 0;

		for (int i = 1; i <= n; ++i) {
			head[i] = 0;
		}
		for (int i = 2; i <= n; ++i) {
			int x;
			scanf("%d", &x);
			addedge(x, i);
			f[i] = x;
		}

		dfs(1);

		for (int i = 1; i <= n; ++i) {
			scanf("%d", &p[i]);
			blk[i] = 0;
		}

		for (int i = 1; i <= n; ++i) {
			update(i);
		}
		for (int i = 1; i <= q; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			swap(p[x], p[y]);
			update(x), update(y);
			if (x < n) {
				update(x + 1);
			}
			if (y < n) {
				update(y + 1);
			}
			if (ans == n) {
				printf("YES\n");
			} else {
				printf("NO\n");
			}
		}
	}
	return 0;
}
```

---

