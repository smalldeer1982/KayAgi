# DFS Checker (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, you are given a generic tree and the constraints on $ n $ and $ q $ are higher. You can make hacks only if both versions of the problem are solved.

You are given a rooted tree consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , and the root is the vertex $ 1 $ . You are also given a permutation $ p_1, p_2, \ldots, p_n $ of $ [1,2,\ldots,n] $ .

You need to answer $ q $ queries. For each query, you are given two integers $ x $ , $ y $ ; you need to swap $ p_x $ and $ p_y $ and determine if $ p_1, p_2, \ldots, p_n $ is a valid DFS order $ ^\dagger $ of the given tree.

Please note that the swaps are persistent through queries.

 $ ^\dagger $ A DFS order is found by calling the following $ \texttt{dfs} $ function on the given tree.

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
3
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
4 6
5 4
1 1 3 4
2 3 4 5 1
5 1
4 5
3 4
2 3```

### 输出

```
YES
YES
NO
YES
NO
NO
YES
YES
NO
NO
YES```

# 题解

## 作者：_liuyi_ (赞：8)

## 思路
先思考相邻的两个数 $p_{i-1}$ 和 $p_i$ 什么时候是合法的。

第一种情况是 $p_{i-1}$ 是 $p_i$ 的父亲，第二种情况是 $p_{i-1}$ 在 $p_i$ 父亲的子树里。记 $dfn_i$ 为 $i$ 在树上的 dfs 序编号，$sz_i$ 为 $i$ 的子树大小，$fa$ 为 $p_i$ 的父亲，那么这两种情况可以合并成 $dfn_{fa} \le dfn_{p_{i-1}}$ 并且 $dfn_{p_{i-1}} \le dfn_{fa} + sz_{fa} - 1$，这个可以 $O(1)$ 判断。

回到原问题，一个排列合法，肯定是合法的点对 $(p_{i-1},p_i)$ 个数为 $n-1$。先预处理一开始排列的合法点对数。修改时是容易的，先撤销 $x$ 和 $y$ 的答案的贡献，交换后再加回去即可，注意不要算重贡献。时间复杂度 $O(n+q)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=(a);i<=(n);++i)
#define per(i,a,n) for(int i=(n);i>=(a);--i)
#define SZ(x) ((int)(x).size())

using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> pii;

const int maxn=3e5+10;

int n,q,fa[maxn],p[maxn],dfn[maxn],idx,sz[maxn],res;
vector<int> e[maxn];

inline void dfs(int u){
	sz[u]=1; dfn[u]=++idx;
	for(auto v:e[u]) dfs(v),sz[u]+=sz[v];
}

inline void init(){
	idx=res=0;
	rep(i,1,n) e[i].clear();
}

inline int calc(int i){
	if(i==1 || i>n) return 0;
	int u=p[i-1],v=p[i];
	return (dfn[u]>=dfn[fa[v]]&&dfn[u]<=dfn[fa[v]]+sz[fa[v]]-1);
}

inline void solve(){
	scanf("%d%d",&n,&q);	
	init();
	rep(i,2,n) scanf("%d",&fa[i]),e[fa[i]].push_back(i);
	rep(i,1,n) scanf("%d",&p[i]);
	dfs(1);
	rep(i,2,n) res+=calc(i);
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y); 
		set<int> st;
		st.insert(x); st.insert(x+1); st.insert(y); st.insert(y+1);
		for(auto i:st) res-=calc(i);
		swap(p[x],p[y]);
		for(auto i:st) res+=calc(i);
		puts(res==n-1?"YES":"NO");
	}
}

signed main(){
    int _=1;
    scanf("%d",&_); 
    while(_--) solve();
}

```

---

## 作者：Ray662 (赞：8)

### 前言

赛时写 D1 时就写出了复杂度非常优秀的做法，于是 D2 直接照搬 D1 代码，但因为忘记改数组大小吃了一发罚时……

---

### 题目大意

给定包含 $n$ 个点的树根为 $1$ 的满二叉树，以及一个 $[1, n]$ 的排列 $a_1, a_2, \cdots, a_n$。

$q$ 次询问，每次询问给定两个数 $x, y$，求交换 $a_x$ 和 $a_y$ 后排列 $a_1, a_2, \cdots, a_n$ 是不是树的一种合法 dfs 序（节点 $a_i$ 的 dfs 序为 $i$），输出 `YES` 或 `NO`。

多组数据，一共 $T$ 组。

D1 (Easy Version): $1 \le T \le 10^4, \sum n \le 65535, \sum q \le 5 \times 10^4$。

D2 (Hard Version): $1 \le T \le 10^4, \sum n \le 3 \times 10^5, \sum q \le 10^5$。

**注意**：

- 题目中树的读入方式是依次输入 $2 \sim n$ 节点的父亲节点编号。

- 交换操作是持久的，即各个询问**不是互相独立的**。

---

### 思路

很容易想到 $O(nq)$ 的做法：对于每个询问，暴力 $O(n)$ 判断交换后合不合法。

但这个做法连 D1 都无法通过，我们考虑如何优化。

由于各个询问不是互相独立的，所以只能在线，$O(q)$ 不可避免，所以我们考虑优化判断合法性。

我们设 $f_i$ 表示 $a_i$ 和 $a_{i + 1}$ 的 dfs 序中相邻的合法性（合法为 $1$，不合法为 $0$），换句话说，就是节点 $a_i$ 和节点 $a_{i + 1}$ 的 dfs 序能否相邻。我们再设 $g_i$ 表示节点 $a_i$ 和 $a_{i + 1}, a_{i - 1}$ 在 dfs 序中相邻的合法性。那么我们很容易得到：

$$
g_i = f_i \land f_{i - 1}
$$

如何求出 $f$？很显然，当 $1 < i < n$ 时，$a_i$ 的 dfs 序比 $a_{i + 1}$ 的 dfs 序小 $1$，只有两种情况：

- $a_i$ 为 $a_{i + 1}$ 的父亲；

- $a_i$ 是叶子结点，且 $\text{lca}(a_i, a_{i + 1})$ 为 $a_{i + 1}$ 的父亲。

特殊地，当 $a_1 = 1$ 时 $f_1 = 1$，否则 $f_1 = 0$；当 $a_n$ 为叶子节点时 $f_n = 1$，否则 $f_n = 0$。

于是我们可以预处理，先 dfs 一遍，把 lca 板子敲上，再赋值每个 $f_i, g_i$。同时我们用 $cnt$ 记录有多少个 $g_i = 0$。

接下来考虑询问如何快速处理。我们可以注意到一个性质：交换 $a_x$ 和 $a_y$，那么 $f$ 或 $g$ 改变的点最多只有 $6$ 个：$x-1,x,x+1,y-1,y,y+1$。

那就做完了啊，每次询问修改上述六个点的值即可。如果一个点的 $g_i$ 从 $0$ 变成了 $1$，`cnt -- `；反之 `cnt ++ `。每次修改完后若 $cnt = 0$ 则此时 $a$ 序列合法，输出 `YES`；否则输出 `NO`。

预处理 $O(n \log n)$，查询 $O(q \log n)$，总复杂度 $O((n + q)\log n)$。

---

**注意**：

- 本题细节比较多，比如修改 $f_{x - 1}$ 和 $g_{x - 1}$ 时下标可能出现负数，需要特判。同理下标大于 $n$ 时也需要特判；

- 注意 $f_i, g_i$ 的定义，统计 $cnt$ 时不要直接 `cnt += g[i]`；

- 每次询问需要修改的 $6$ 个点可能有重复，注意不要重复修改和计算，开一个标记数组即可；

- lca 板子不要敲错了；

- 多组数据，记得清空！！！

[代码](https://codeforces.com/contest/2002/submission/275842678)中变量名和题解中以及题目中有所不同，比如代码中 ok 数组即本题解中的 $g$，为了题解可读性更好则略作修改。

---

PS: 

本场 [Div.1 + Div.2](https://codeforces.com/contest/2002) Rating ${}+ 189$，rk $1022$，$\text{\color{cyan}specialist} \to \text{\color{blue}expert}$。

小疑问：有人能告诉我能过 D1 但不能过 D2 的做法吗？暴力 $O(nq)$ 都过不了，$O((n + q)\log n)$ 两个都能过，$O(q\sqrt n)$ 似乎不太现实，所以 D1 和 D2 有区别吗？

---

## 作者：masonxiong (赞：2)

前面转自[我的 D1 题解](https://www.luogu.com.cn/article/ae2vn9nj)。

# 题目分析

> 题解记号说明：
>
> - $dfn_i$ 是在对树的一次 DFS 中，$i$ 号节点被访问的次序。
> - $size_i$ 是以 $i$ 号节点为根节点的子树大小（节点数量）。
> - $f_i$ 是 $i$ 号节点的父节点。特别的，有 $parent_1=1$。
> - $a_i$ 是 $i$ 号节点全体祖先节点（含其自身）构成的集合。特别的，有 $a_1=\{1\}$。
> - $\operatorname{lca}(x,y)$ 为 $x$ 号节点和 $y$ 号节点的最近公共祖先。

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

那么现在的重点就在于：**给定 $i$，判断是否有 $f_{p_{i+1}}\in a_{p_i}$**。我们有很多的方法来解决这个问题。

## 转 LCA

D1 题解中的暴力跳解法本质上就是判祖先转成 LCA。根据如下性质：

$$x\in a_{y}\iff \operatorname{lca}(x,y)=x$$

我们可以采取任何的技术来高效求解 $\operatorname{lca}(x,y)$，比如你可以用欧拉序搭配 Four Russian RMQ 做到 $O(n)$ 预处理 $O(1)$ 查询。

## size 搭配 dfn

利用 $size$ 搭配 $dfn$ 求解。根据如下性质：

$$x\in a_y\iff[dfn_y,dfn_y+size_y)\subseteq[dfn_x,dfn_x+size_x)$$

> 证明：根据前面的证明，我们知道每一个子树肯定在一个合法 DFS 序中的一个连续的子序列中，并且第一个访问到的节点肯定是这个子树的根节点。
>
> 那么根据定义，$u$ 号节点为根的子树所对应的连续子序列的左端点就是 $dfn_u$，长度是 $size_u$，则这个连续子序列就是 $[dfn_u,dfn_u+size_u)$。
>
> 祖先节点为根的子树肯定包含后辈节点为根的子树，所以它们对应的连续子序列应当也满足这个包含关系。

此解法可以 $O(n)$ 预处理 $O(1)$ 回答询问且常数比 LCA 解法小很多，是本题最优解法。

---

# 代码

以 $size$ 搭配 $dfn$ 为例。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int MaxN = 300000 + 5;
int T, N, Q, dfsTime, validCount;
int dfsOrder[MaxN], dfn[MaxN], parent[MaxN], treeSize[MaxN];
bitset<MaxN> validPosition;
vector<vector<int>> tree;

bool isAncestor(int ancestor, int descendant) {
	return dfn[ancestor] <= dfn[descendant] && dfn[ancestor] + treeSize[ancestor] >= dfn[descendant] + treeSize[descendant];
}

bool initialize() {
	function<int(int)> dfs = [&](int current) {
		treeSize[current] = 1;
		dfn[current] = ++dfsTime;
		for (int i : tree[current])
			treeSize[current] += dfs(i);
		return treeSize[current];
	};
	cin >> N >> Q;
	validCount = 0;
	validPosition.reset();
	tree.assign(N + 1, vector<int>());
	for (int i = 2; i <= N; i++) {
		cin >> parent[i];
		tree[parent[i]].push_back(i);
	}
	for (int i = 1; i <= N; cin >> dfsOrder[i++]);
	dfs(1);
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

## 作者：lfxxx (赞：2)

考虑一下一个排列是合法 dfs 序的充要条件。

1. 对于一个节点 $u$ 其任意一个儿子 $v$，记 $q_u$ 表示 $u$ 在排列中的顺序，则有 $q_u < q_v$ 且 $q_v + sz_v \leq q_u + sz_u$。

两个式子均满足后，可以说明 $v$ 一定在 $u$ 的子树内，若对于每个 $u$ 都满足，则可以从下往上归纳证明排列合法。

那么接下来就是简单的了，用 multiset 维护一下每个 $u$ 的所有儿子 $\max(q_v + sz_v)$ 与 $\min(q_v)$ 的值即可，每次更改两个点的位置显示只会对其父亲的儿子邻域产生影响，所以总复杂度是 $O((n+q) \log n)$ 的。

[代码](https://codeforces.com/contest/2002/submission/275814673)

---

## 作者：Wu_Qi_Tengteng (赞：1)

思考如何优化判断序列是否合法。我们不妨将题目转化一下，判断一个 dfs 序是否合法，等价于判断其中每对相邻的数是否能够相邻。如果都能够相邻，那么意味着这个dfs序就是和法的。这一步的转化可以用反证法证明。

那么现在的问题就变成如和判断两个点是否可以相邻。这个是好判断的。假设我们现在要判断 $p_{i}$ 和 $p_{i+1}$ 是否能够相邻，那么会有两种情况：$fa_{p_{i+1}}=p_i$ 或者 $dfn[fa_{p_{i+1}}]\le dfn[p_i] < dfn[fa_{p_{i+1}}]+siz[fa_{p_{i+1}}]$ 且 $p_i$ 是叶子节点 。我们用 $f_i$ 表示 $i$ 与 $i-1$ 是否能够相邻，$f_1=[p_1=1]$。这是容易预处理的。 我们用 $cnt$ 表示 $f_i$ 中为真的个数。当 $cnt=n$ 的时候就是合法的时候。 

接着发现，每次交换 $x$、$y$ ，最多只会改变 $x$、$x+1$、$y$、$y+1$ 这 $4$ 个点的值，所以暴力修改，然后更新 $cnt$ 就好了。注意判断 $x$ 和 $y$ 本就相邻的情况。

时空复杂度 $\mathcal{O}(n)$。
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5; 
int T,n,q,p[N];
vector<int> G[N];
int dfn[N],siz[N],f[N],fa[N],num;
inline void dfs(int u){
	siz[u]=1;
	dfn[u]=++num;
	for(auto v:G[u])dfs(v),siz[u]+=siz[v];
}
bool check(int i){
	return fa[p[i]]==p[i-1]?1:(dfn[fa[p[i]]]<dfn[p[i-1]]&&dfn[p[i-1]]<dfn[fa[p[i]]]+siz[fa[p[i]]]&&(G[p[i-1]].size()==0));
}
inline void solve(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)G[i].clear();
	for(int i=2;i<=n;i++){
		int x;
		cin>>x;
		G[x].push_back(i);
		fa[i]=x;
	}
	num=0;
	dfs(1);
	for(int i=1;i<=n;i++)cin>>p[i];
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(i<2)f[i]=(p[i]<2);
		else f[i]=check(i);
		cnt+=f[i];
	}
	while(q--){
		int x,y;
		cin>>x>>y;
		if(x>y)swap(x,y);
		if(x+1==y){
			cnt-=f[x]+f[y]+(y<n?f[y+1]:0);
			swap(p[x],p[y]);
			if(x<2)f[x]=(p[x]<2);
			else f[x]=check(x);
			f[y]=check(y);
			if(y<n)f[y+1]=check(y+1);
			cnt+=f[x]+f[y]+(y<n?f[y+1]:0);
		}else{	
			cnt-=(f[x]+f[x+1]+f[y]+(y<n?f[y+1]:0));
			swap(p[x],p[y]);
			if(x<2)f[x]=(p[x]<2);
			else f[x]=check(x);
			f[x+1]=check(x+1);
			f[y]=check(y);
			if(y<n)f[y+1]=check(y+1);
			cnt+=f[x]+f[x+1]+f[y]+(y<n?f[y+1]:0);
		}
		if(cnt==n)printf("YES\n");
		else printf("NO\n"); 
	}
}
signed main(){
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：wyyqwq (赞：1)

### D1

对于排列中相邻的两个数 $(i, j)$，$v_i$ 表示对于 $p_i, p_{i + 1}$ 是否合法，若 $i$ 是 $j$ 的父亲，或 $i$ 在 $j$ 父亲的子树里，$v_i = 1$。当 $\sum v_i = n-1$ 的时候这个排列合法。

若 $i$ 是 $j$ 的父亲，当且仅当 $i = j / 2$。若是后者可以从 $i$ 往上跳。时间复杂度 $O(n + q\log n)$。

### D2

上面算法的时间复杂度是对的，存一下边然后查询的时候倍增跳就可以。

```c++
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 7;
vector<int> v[N];
int vis[N];
int p[N], a[N];
int chk1(int x, int y) {
    if(a[y] == x) return 1;
    return 0;
}

int chk2(int x, int y) {
    int fy = a[y];
    if(fy == 1) return 1;
    while(x != 1) {
        x = a[x];
        if(x == fy) return 1;
    }
    return 0;
}
set<int> t[N];
void solve() {
    int n, q;
    cin >> n >> q;
    for(int i = 2; i <= n; i ++) cin >> a[i];
    for(int i = 2; i <= n; i ++) {
        v[i].push_back(a[i]);
        v[a[i]].push_back(i);
        t[a[i]].insert(i);
    }
    for(int i = 1; i <= n; i ++) cin >> p[i];
    for(int i = 1; i <= n + 1; i ++) vis[i] = 0;
    int nw = 0;
    for(int i = 1; i < n; i ++) {
        if(chk1(p[i], p[i + 1]) || chk2(p[i], p[i + 1])) vis[i] = 1, nw ++;
    }
    for(int i = 1; i <= q; i ++) {
        int x, y;
        cin >> x >> y;
        if(x > y) swap(x, y);
        if(vis[y] && y != n) vis[y] = 0, nw --;
        if(vis[y - 1] && y - 1 != 0) vis[y - 1] = 0, nw --;
        if(vis[x] && x != n && x + 1 != y) vis[x] = 0, nw --;
        if(x != 1 && vis[x - 1]) vis[x - 1] = 0, nw --;
        swap(p[y], p[x]);
        if(y != n && (chk1(p[y], p[y + 1]) || chk2(p[y], p[y + 1]))) vis[y] = 1, nw ++;
        if(y != 1 && (chk1(p[y - 1], p[y]) || chk2(p[y - 1], p[y]) == 1)) vis[y - 1] = 1, nw ++;
        if(x != n && x + 1 != y && (chk1(p[x], p[x + 1]) || chk2(p[x], p[x + 1]) == 1)) vis[x] = 1, nw ++;
        if(x != 1 && (chk1(p[x - 1], p[x]) || chk2(p[x - 1], p[x]) == 1)) vis[x - 1] = 1, nw ++;
        if(nw == n - 1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
int main() {
    int T;
    cin >> T;
    while(T --) solve();
}
```

---

## 作者：_LSA_ (赞：1)

这里提供一种较为麻烦的哈希做法。

首先注意到对于原树的每一棵子树，设子树的根节点为 $u$，在 dfs 序中从 $u$ 开始的 $siz_u$ 个数一定是 $u$ 子树内的节点。

那么我们给每个节点赋一个随机值 $val_u$，并设每棵子树的哈希函数为 $f(u)=val_u\sum_{v\in subtree}val_v$，并对每棵子树的哈希值求和，得到原树的哈希值。

然后对于给的序列 $p$，我们对于每个数 $p_i$ 计算哈希值 $val_{p_i}\sum_{j=i}^{i+siz_{p_i}-1}val_{p_j}$ 并求和。根据上面的结论，序列是合法的 $\text{dfs}$ 序时，则序列和原树的哈希值相等。

考虑怎么快速计算和修改序列的哈希值，可以用树状数组维护 $val_{p_i}$ 的区间和，再用区间修改单点查询的树状数组维护每个 $p_i$ 被前面的哪些数算到哈希值中，修改时改一下贡献就行了。

时间复杂度 $O(n\log n)$。

代码实现中作者~~闲的没事~~写了 $5$ 个哈希，实际上随机哈希的错误率极低，写一个应该是够用的。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
using namespace std;
ll read(){
    ll X = 0 ,r = 1;
    char ch = getchar();
    while(!isdigit(ch) && ch != '-') ch = getchar();
    if(ch == '-') r = -1,ch = getchar();
    while(isdigit(ch)) X = X*10+ch-'0',ch = getchar();
    return X*r;
}
const int N = 3e5+10;
int n,a[N],p[N],siz[N];
mt19937_64 rnd(time(0));
ull val[N][6],sum[N][6];
struct BIT{
    ull t[N];
    void clear(){
        for(int i=1;i<=n;i++) t[i] = 0;
    }
    void add(int x,ull y){
        if(x > n) return ;
        while(x <= n){
            t[x] += y;
            x += x&(-x);
        }
    }
    ull ask(int x){
        ull res = 0;
        while(x){
            res += t[x];
            x -= x&(-x);
        }
        return res;
    }
    ull query(int l,int r){
        return ask(min(r,n))-ask(l-1);
    }
}T[6],TT[6];
void solve(){
    n = read(); int Q = read();
    for(int i=2;i<=n;i++) a[i] = read();
    for(int i=1;i<=n;i++) p[i] = read();
    for(int i=0;i<6;i++) TT[i].clear();
    for(int i=1;i<=n;i++) sum[i][0] = val[i][0] = i,siz[i] = 1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<5;j++) sum[i][j] = val[i][j] = rnd();
    for(int i=n;i;i--) siz[a[i]] += siz[i];
    for(int i=n;i;i--)
        for(int j=0;j<5;j++) sum[a[i]][j] += sum[i][j];
    ull hsh[6] = {0,0,0,0,0,0},now[6] = {0,0,0,0,0,0};
    for(int i=0;i<5;i++) T[i].clear();
    for(int i=1;i<=n;i++)
        for(int j=0;j<5;j++) T[j].add(i,val[p[i]][j]);
    for(int i=1;i<=n;i++)
        for(int j=0;j<5;j++)
            now[j] += val[p[i]][j]*T[j].query(i,i+siz[p[i]]-1);
    for(int i=1;i<=n;i++)
        for(int j=0;j<5;j++) TT[j].add(i,val[p[i]][j]),TT[j].add(i+siz[p[i]],-val[p[i]][j]);
    for(int i=1;i<=n;i++)
        for(int j=0;j<5;j++) hsh[j] += val[i][j]*sum[i][j];
    auto chk = [&]()->bool{
        for(int i=0;i<5;i++)
            if(now[i] != hsh[i]) return false;
        return true;
    };
    
    while(Q--){
        int u = read(),v = read();
        for(int j=0;j<5;j++) now[j] -= val[p[u]][j]*T[j].query(u,u+siz[p[u]]-1);
        for(int j=0;j<5;j++) now[j] -= val[p[v]][j]*T[j].query(v,v+siz[p[v]]-1);
        for(int j=0;j<5;j++) TT[j].add(u,-val[p[u]][j]),TT[j].add(u+siz[p[u]],val[p[u]][j]);
        for(int j=0;j<5;j++) TT[j].add(v,-val[p[v]][j]),TT[j].add(v+siz[p[v]],val[p[v]][j]);
        for(int j=0;j<5;j++) now[j] -= val[p[u]][j]*TT[j].ask(u),now[j] -= val[p[v]][j]*TT[j].ask(v);
        for(int j=0;j<5;j++) T[j].add(u,-val[p[u]][j]),T[j].add(v,-val[p[v]][j]);
        
        swap(p[u],p[v]);
        for(int j=0;j<5;j++) now[j] += val[p[u]][j]*TT[j].ask(u),now[j] += val[p[v]][j]*TT[j].ask(v);
        for(int j=0;j<5;j++) TT[j].add(u,val[p[u]][j]),TT[j].add(u+siz[p[u]],-val[p[u]][j]);
        for(int j=0;j<5;j++) TT[j].add(v,val[p[v]][j]),TT[j].add(v+siz[p[v]],-val[p[v]][j]);
        for(int j=0;j<5;j++) T[j].add(u,val[p[u]][j]),T[j].add(v,val[p[v]][j]);
        for(int j=0;j<5;j++) now[j] += val[p[u]][j]*T[j].query(u,u+siz[p[u]]-1);
        for(int j=0;j<5;j++) now[j] += val[p[v]][j]*T[j].query(v,v+siz[p[v]]-1);
        
        puts(chk() ? "Yes" : "No");
    }
}
int main(){
    int T = read();
    while(T--) solve();
    return 0;
}

```

---

