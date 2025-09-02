# [ARC092F] Two Faced Edges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc092/tasks/arc092_d

$ N $ 頂点 $ M $ 辺の単純な有向グラフが与えられます。 頂点には $ 1,\ 2,\ ...,\ N $ の番号が，辺には $ 1,\ 2,\ ...,\ M $ の番号が付いています。 辺 $ i $ は頂点 $ a_i $ から頂点 $ b_i $ へ伸びています。

それぞれの辺について，もしその辺を反転させたらグラフの強連結成分の個数が変わるかどうかを求めてください。

なお，辺 $ i $ を反転させるとは，グラフから辺 $ i $ を削除し， 新たに頂点 $ b_i $ から頂点 $ a_i $ へ伸びる辺を追加する操作を意味します。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ M\ \leq\ 200,000 $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ N $
- $ a_i\ \neq\ b_i $
- $ i\ \neq\ j $ ならば $ a_i\ \neq\ a_j $ または $ b_i\ \neq\ b_j $

### Sample Explanation 1

辺を反転させない場合強連結成分の個数は $ 3 $ 個ですが，辺 $ 2 $ を反転させると強連結成分の個数は $ 1 $ 個になります。

### Sample Explanation 2

辺を反転させた結果，グラフに多重辺が生じる場合もあります。

## 样例 #1

### 输入

```
3 3
1 2
1 3
2 3```

### 输出

```
same
diff
same```

## 样例 #2

### 输入

```
2 2
1 2
2 1```

### 输出

```
diff
diff```

## 样例 #3

### 输入

```
5 9
3 2
3 1
4 1
4 2
3 5
5 3
3 4
1 2
2 5```

### 输出

```
same
same
same
same
same
diff
diff
diff
diff```

# 题解

## 作者：CYJian (赞：46)

考虑翻转 $u \rightarrow v$ 这条边对于强连通分量数量的影响，只需要考虑下面两个因素就行了：

1. 原图中存在一条 $v \rightarrow u$ 的路径。
2. 原图中存在一条 $u \rightarrow v$ 的路径，且不含上面的那条边。

若上述两个因素中有且仅有一个满足，则强连通分量数量会变化。

考虑原因：

1. 若两个条件均不满足：则说明这个点不管正着还是反着，都不会有强连通分量产生，则不会变化。
2. 若两个条件均满足：则这两条路径拼起来就是一个强连通分量，缩点之后和 $u \rightarrow v$ 这条边的方向没有关系了，所以也不会变化。
3. 若仅有一个条件满足，则说明，如果没有 $u \rightarrow v$ 这条边，则原图中 $u$ 和 $v$ 一定不在同一个强连通分量中。而如果有了 $u \rightarrow v$ 或者 $v \rightarrow u$ 这条边，则分别结合条件 $1$ 和条件 $2$，就能让 $u$ 和 $v$ 在同一个强连通分量中，则说明翻转边一定会让强连通分量的数量改变。

然后考虑如何统计。

首先第一个条件直接 $O(NM)$ 爆搜统计就行了。

第二个条件乍一看有点辣手，但是仔细想想就会发现，它本质上就只是求：$u \rightarrow v$ 的路径中，这条边是不是必经边。你就考虑从 $x$ 开始 DFS，记录 $x$ 经过的点，被遍历到的时候 $x$ 的出边的标号。然后考虑将 $x$ 的出边顺序反过来再 DFS 一遍。如果两次遍历到的时候记录下来的标号不同，则说明 $u \rightarrow v$ 并不是必经边。反之则一定是必经边。

然后就枚举每条边瞎判判就行了。

${\rm Code}$：

```cpp
const int MAXN = 1010;
const int MAXM = 200010;

struct Edge {
	int u, v;

	Edge() {}
	Edge(int u, int v):u(u), v(v) {}
}E[MAXM];

vector<int>to[MAXN];

int Mark[MAXN];
bitset<MAXN>vis;
bool G1[MAXN][MAXN];
bool G2[MAXN][MAXN];

inline void dfs1(int x, int st) {
	G1[st][x] = 1, vis.set(x);
	for(auto u : to[x]) if(!vis[u]) dfs1(u, st);
}

inline void dfs2(int x, int col, int k, int st) {
	if(k) G2[st][x] = Mark[x] != col;
	else Mark[x] = col; vis.set(x);
	for(auto u : to[x]) if(!vis[u]) dfs2(u, col, k, st);
}

int main() {
	int n = ri, m = ri;
	for(int i = 1; i <= m; i++) {
		int u = ri, v = ri;
		to[u].push_back(v);
		E[i] = Edge(u, v);
	}
	for(int i = 1; i <= n; i++) vis.reset(), dfs1(i, i);
	for(int i = 1; i <= n; i++) {
		vis.reset(), vis.set(i);
		memset(Mark, 0, sizeof(Mark));
		int d = to[i].size();
		for(int j = 0; j < d; j++) if(!vis[to[i][j]]) dfs2(to[i][j], j + 1, 0, i);
		vis.reset(), vis.set(i);
		for(int j = d - 1; ~j; --j) if(!vis[to[i][j]]) dfs2(to[i][j], j + 1, 1, i);
	}
	for(int i = 1; i <= m; i++)
		puts(G1[E[i].v][E[i].u] ^ G2[E[i].u][E[i].v] ? "diff" : "same");
	return 0;
}
```

---

## 作者：Caiest_Oier (赞：12)

# [AT_arc092_d](https://www.luogu.com.cn/problem/AT_arc092_d)   
首先我们考虑把图缩点，缩完点后再考虑。   

对于一条从 $u$ 到 $v$ 的边，如果两端点属于一个强连通分量，则如果强连通分量数量发生改变，则意味着当前强连通分量分裂为两个。而我们发现，发生分裂，当且仅当 $u$ 不能再到达 $v$，换句话说就是原来图中，$u$ 到 $v$ 的路径必经过当前边。所以我们就得到了强连通分量分裂的判定条件。    

而如果发生两个强连通分量合并，则当且仅当 $u$ 有至少一条路径可以不经过该边到达 $v$。于是我们得到了对于两种情况的判定方式。    

这个时候我们其实已经可以抛弃缩点了，因为我们已经发现，变化与否只和两个点之间的路径有关系。如果 $v$ 能到 $u$，且 $u$ 到 $v$ 的路径必经过当前边，则分裂；如果 $v$ 不能到 $u$，且 $u$ 到 $v$ 的路径不一定经过当前边，则合并，其他情况数量不变。于是就考虑两个条件的计算。第一个条件可以对于每个点搜索一下就好了。第二个条件我们考虑对于每个 $u$ 来处理，考虑对于每个出边都跑一边广搜，记录到达每一个点的第一条出边（看不懂的可以见代码），再反过来跑一边，如果二者的标记相同，意味着它有一条必经边。问题就解决了。复杂度 $\Theta(nm)$。    

代码：    

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k1,k2,k3,k4,k5,k6,k7,k8,k9;
vector<int>E[100003]; 
int tj1[2003][2003],tj2[2003][2003],e[300003][2];
int mk[10003],vis[10003];
void dfs(int now,int st){
	tj1[now][st]=1;
	for(auto i:E[now]){
		if(tj1[i][st])continue;
		dfs(i,st);
	}
	return;
}
void dfs2(int now,int col,int st,int cs){
	if(cs)tj2[st][now]=(mk[now]!=col);
	else mk[now]=col;
	vis[now]=1;
	for(auto i:E[now]){
		if(vis[i])continue;
		dfs2(i,col,st,cs);
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&e[i][0],&e[i][1]);
		E[e[i][0]].emplace_back(e[i][1]);
	}
	for(int i=1;i<=n;i++)dfs(i,i);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)mk[j]=vis[j]=0;
		vis[i]=1;
		for(int j=0;j<E[i].size();j++)if(!vis[E[i][j]])dfs2(E[i][j],j+1,i,0);
		for(int j=1;j<=n;j++)vis[j]=0;
		vis[i]=1;
		for(int j=E[i].size()-1;j>=0;j--)if(!vis[E[i][j]])dfs2(E[i][j],j+1,i,1);
	}
	for(int i=1;i<=m;i++){
		if(tj1[e[i][0]][e[i][1]]^tj2[e[i][0]][e[i][1]])puts("diff");
		else puts("same");
	}
	return 0;
}
```

upd：代码中的 tj1 指 $i$ 是否可达 $j$，tj2 指 $i$ 到 $j$ 的这条边是否必经。

---

## 作者：xtx1092515503 (赞：8)

一种复杂度 $O(\dfrac{n^3}{\omega}+m)$ 的复杂度更优秀的做法。目前 rank 1。

------

首先，我们不妨考虑 `DAG` 情形的做法：若原图是 `DAG` ，翻转一条边显然不会增加新的强连通分量，只有可能减少强连通分量数量。

假如我们翻转了边 $u\rightarrow v$，这时，我们明显可以发现，当且仅当在删去边 $u\rightarrow v$ 后得到的图上 $u$ 仍可达 $v$（把这种关系记作 $u\rightsquigarrow v$）时，翻转后出现了边 $v\rightarrow u$ ，则 $u\rightsquigarrow v,v\rightarrow u$ ，二者成环，增加了强连通分量。

下面我们考虑非 `DAG` 情形。则此时一个很显然的想法是跑 `Tarjan` 求强连通。则如果 $u\rightarrow v$ 这条边是连接两个不同分量间的边，显然我们 `DAG` 时分析仍然适用。于是我们仅需考虑同一个分量内部的边。

引理1. 翻转这样的边 $u\rightarrow v$ 不会出现新分量。

我们考虑在原分量内部，因为其强连通，故必存在一条完全在分量内部的路径 $v\rightsquigarrow u$。同时，因为其出现了新分量，故在分量外还得存在一条路径 $u\rightsquigarrow v$，于是这样的话，$v\rightsquigarrow u$ 与 $u\rightsquigarrow v$ 这两条路径所处的分量完全可以并作一个大分量，与它们不在同一个分量内的前提相悖。

于是我们仅需考虑分量内部的情形。显然，若有 $u\not\rightsquigarrow v$，即 $u$ 无法不通过 $u\rightarrow v$ 而到达 $v$，则翻转后该大分量一定会分裂，也即分量数一定会增多；否则，则该大分量一定不会分裂，因为出现了新的环将整个分量联系在一起。

于是我们现在只需知道每条边是否有 $u\rightsquigarrow v$ 关系，以及该边两端是否位于同一个 `SCC` 里，就能判断出其是否翻转后分量数会变化。

考虑我们一次性求出从一个固定点 $u$ 出发的所有 $u\rightarrow v$ 的 $u\rightsquigarrow v$ 关系是否成立。

我们考虑将所有的 $v$ 依次编号为 $v_1,v_2,\dots,v_k$。则对于某个 $v_i$，$u\rightsquigarrow v_i$，当且仅当存在一个 $j\neq i$ 且 $v_j\rightsquigarrow v_i$。

考虑顺次从每个 $v_i$ 出发，遍历整张图。显然，若遍历到某个 $v_i$ 时发现它已经被访问过了，则证明存在上述的 $v_j\rightsquigarrow v_i$。否则，就直接bfs遍历即可。

上述过程只处理了 $j<i$，所以我们还要倒序再遍历一次。

显然，单次处理某个 $u$ 时，上述算法复杂度为 $O(n+m)$，因为每个点每条边都最多被访问 $1$ 次。而要处理全部 $u$，因此复杂度 $O(nm)$。

虽然此时已经可以通过，但我们还可以优化！考虑 `bitset` 优化。

我们发现，上述算法的瓶颈在于 `bfs` 时，从某个节点出发要访问其所有出边，不管其另一端点访问与否。

为了避免这种访问，我们令一个 `bitset` $S$ 表示当前所有点是否被访问过，是则为 $0$，否则为 $1$。

若我们当前从 $x$ 出发想遍历其出边，不妨令其出边的 `bitset` 是 $g_x$，则我们只需遍历 $g_x\cap S$ 中的所有元素即可。

遍历 `bitset` 中所有元素是有 $O(\dfrac{n}{\omega})$ 的做法的：

```cpp
for(int i=T._Find_first();i!=T.size();i=T._Find_next(i))
```

于是这样，我们在 `bfs` 过程中就仅遍历了所有连接着未到达节点的边，于是单次复杂度就从 $m$ 变成了 $\dfrac{n^2}{\omega}$。遍历 $n$ 次，复杂度 $O(\dfrac{n^3}{\omega})$。

另外再加上 `Tarjan` 的 $O(n+m)$，复杂度 $O(\dfrac{n^3}{\omega}+m)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef bitset<1010> bs;
int n,m,id[1010][1010],dfn[1010],low[1010],col[1010],c,tot,X[200100],Y[200100];
bs g[1010];
vector<int>v[1010];
stack<int>s;
bool ok[200100];
void Tarjan(int x){
	dfn[x]=low[x]=tot++,s.push(x);
	for(auto y:v[x]){
		if(dfn[y]==-1)Tarjan(y),low[x]=min(low[x],low[y]);
		else if(col[y]==-1)low[x]=min(low[x],dfn[y]);
	}
	if(low[x]!=dfn[x])return;
	while(s.top()!=x)col[s.top()]=c,s.pop();
	col[s.top()]=c,s.pop();
	c++;
}
bs S;
queue<int>q;
void bfs(){
	while(!q.empty()){
		int x=q.front();q.pop();
		bs T=S&g[x];
		for(int i=T._Find_first();i!=T.size();i=T._Find_next(i))S.reset(i),q.push(i);
	}
}
void func(int x){
	S.set(),S.reset(x);
	for(int y=0;y<n;y++){
		if(!id[x][y])continue;
		if(!S.test(y)){ok[id[x][y]]=true;continue;}
		S.reset(y),q.push(y);bfs();
	}
	S.set(),S.reset(x);
	for(int y=n-1;y>=0;y--){
		if(!id[x][y])continue;
		if(!S.test(y)){ok[id[x][y]]=true;continue;}
		S.reset(y),q.push(y);bfs();
	}
}
int main(){
	scanf("%d%d",&n,&m),memset(dfn,-1,sizeof(dfn)),memset(low,-1,sizeof(low)),memset(col,-1,sizeof(col));
	for(int i=1,x,y;i<=m;i++)scanf("%d%d",&x,&y),x--,y--,id[x][y]=i,g[x].set(y),v[x].push_back(y),X[i]=x,Y[i]=y;
	for(int i=0;i<n;i++)if(dfn[i]==-1)Tarjan(i);
	for(int i=0;i<n;i++)func(i);
	for(int i=1;i<=m;i++)puts((col[X[i]]==col[Y[i]])^ok[i]?"diff":"same");
	return 0;
}
```



---

## 作者：xht (赞：6)

> [ARC092F Two Faced Edges](https://atcoder.jp/contests/arc092/tasks/arc092_d)

## 题意

- 给定一张 $n$ 个点 $m$ 条边无重边无自环的有向图。
- 求每条边反向后整张图的强连通分量个数有没有变化。
- $n \le 10^3$，$m \le 2 \times 10^5$。

## 题解

直接上结论：

对于一条边 $u \to v$，反向后整张图的强连通分量个数有变化当且仅当恰好满足下列两个条件中的一个：

1. 忽略这条边后，$u$ 能到达 $v$。
2. 忽略这条边后，$v$ 能到达 $u$。

后者是否忽略没区别，直接对于每个点 dfs 出能到达的点即可，时间复杂度 $\mathcal O(nm)$。

对于前者，我们实际上要求的就是从 $u$ 开始第一条边不走 $u \to v$ 的情况下能否到达 $v$。

考虑对于所有 $u$ 相同的边一起计算，设出边分别为 $v_{1\dots k}$。

首先按照 $v_{1\dots k}$ 的顺序 dfs 一遍，记录下每个点 $k$ 是从哪个 $v_i$ 到达的，记作 $p(k)$。

然后按照 $v_{k \dots 1}$ 的顺序 dfs 一遍，同样记录下每个点 $k$ 是从哪个 $v_i$ 到达的，记作 $q(k)$。

对于一个 $v_i$，若 $p(v_i) = q(v_i) = v_i$，则说明从 $u$ 开始第一条边不走 $u \to v$ 的情况下无法到达 $v$，否则说明可以到达。

总时间复杂度 $\mathcal O(nm)$。

## 代码

```cpp
const int N = 1e3 + 7, M = 2e5 + 7;
int n, m, u[M], v[M];
bool w[N][N];
int p[N][N], q[N][N];
vi e[N];

void dfs(int x, bool *w) {
	w[x] = 1;
	for (int y : e[x])
		if (!w[y]) dfs(y, w);
}

void dfs(int x, int *p, int z) {
	p[x] = z;
	for (int y : e[x])
		if (!p[y]) dfs(y, p, z);
}

int main() {
	rd(n, m);
	for (int i = 1; i <= m; i++) rd(u[i], v[i]), e[u[i]].pb(v[i]);
	for (int x = 1; x <= n; x++) {
		dfs(x, w[x]);
		p[x][x] = q[x][x] = x;
		for (int y : e[x]) if (!p[x][y]) dfs(y, p[x], y);
		reverse(e[x].begin(), e[x].end());
		for (int y : e[x]) if (!q[x][y]) dfs(y, q[x], y);
	}
	for (int i = 1; i <= m; i++)
		prints((w[v[i]][u[i]] ^ (p[u[i]][v[i]] != q[u[i]][v[i]])) ? "diff" : "same");
	return 0;
}
```

---

## 作者：Alex_Wei (赞：5)

> [AT3945 [ARC092D] Two Faced Edges](https://www.luogu.com.cn/problem/AT3945)

强连通性相关首先考虑缩点建出 DAG。

对于连接 SCC $(S_1, S_2)$ 之间的边，反向后使得 SCC 数量减少当且仅当 $S_1$ 在 DAG 上能够不经过该边到达 $S_2$。可以 $\mathcal{O}(nm)$ 求出任意两点之间的路径数对 $2$ 取 $\min$ 判断。或者直接求路径数取模，出错的概率较小。

但是 SCC 内部的边就不好办了。如果反向 $u\to v$，我们断言如果 $u$ 还能到达 $v$ 那么连通性不变。

首先，对于所有 SCC 内部的点对 $(x, y)$，从 $x$ 到 $y$ 要么必经 $u\to v$ 这条边，要么非必经。对于后者，反向 $u\to v$ 不影响 $x, y$ 的连通性。对于前者，若 $u$ 仍能到达 $v$ 则 $x$ 仍能到达 $y$，否则反向边 $v\to u$ 不会产生任何影响。因为必经 $u\to v$ 所以 $x$ 没有其它路径到达 $v$，反向后 $x, v$ 不连通自然引出 $v\to u$ 无用。

综上我们得到了判断 SCC 内部边 $u\to v$ 反向后强连通性不变的充要条件：去掉 $u\to v$ 后 $u$ 仍能到达 $v$。这相当于对于一个点的每条出边 $u\to v_1, v_2, \cdots, v_i$，我们都需求出 $u$ 在不经过 $u\to v_j$ 的情况下能到达哪些点。

考虑这是一个前缀 $v_1 \sim v_{j - 1}$ 和后缀 $v_{j + 1} \sim v_i$ 的形式，因此正反各扫一遍，在扫每条出边时记录时刻每个点的可达性，并且在扫当前出边 $u\to v$ 时若 $v$ 已经可达则将 $u\to v$ 标记为去掉后仍可达。由于我们依次加入所有出边时 SCC 内每个点只会被遍历一次，故总时间复杂度为 $\mathcal{O}(nm)$。

- 注意我们考虑的是保留从 $u$ 出发的一段前缀或后缀的边时从 $u$ 出发每个点的可达情况，因此当再次 `dfs` 到 $u$ 时需及时返回，否则会遍历到从 $u$ 出发的不属于当前前缀或后缀的边。

更进一步地，发现对于连接 SCC 之间的边 $u\to v$，我们也希望判断去掉该边后 $u$ 能否到达 $v$。这和 SCC 内部的边所需要求解的东西是一致的，因此可以将所有边等价考虑。只不过对于不同 SCC 之间的边，若 $u\not\rightsquigarrow v$ 则反转 $u\to v$ 不会改变 SCC 个数，反之则改变。这和 SCC 内部的边恰好相反。这样我们就不需要显式地建出 DAG 了。

对整张图进行 $\mathcal{O}(nm)$ 的深搜会 [T 飞掉](https://atcoder.jp/contests/arc092/submissions/31940423)，我们需要更加高效的算法。考虑每次找到 $u$ 的所有出边中没有被访问的第一个点，可以使用 `bitset` 的 `_Find_first()` 实现。

具体而言，设 `vis` 表示各个节点是否被访问，`e[u]` 表示 $u$ 的所有出点，则 `(~vis & e[u])._Find_first()` 即为所求。时间复杂度 $\mathcal{O}\left(\dfrac {n ^ 3}{w}\right)$。

启示：序列去掉一个位置的信息可由前缀和后缀合并得到。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
const int M = 2e5 + 5;
int n, m;
int cnt, hd[N], nxt[M], to[M], ans[M];
void add(int u, int v) {nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v;}
int dn, dfn[N], low[N], cn, col[N], top, stc[N];
bitset<N> e[N], vis;
void tarjan(int id) {
  low[id] = dfn[id] = ++dn, stc[++top] = id, vis[id] = 1;
  for(int i = hd[id]; i; i = nxt[i]) {
    int it = to[i];
    if(!dfn[it]) tarjan(it), low[id] = min(low[id], low[it]);
    else if(vis[it]) low[id] = min(low[id], dfn[it]);
  }
  if(dfn[id] == low[id]) {
    col[id] = ++cn;
    while(stc[top] != id) vis[stc[top]] = 0, col[stc[top--]] = cn;
    vis[id] = 0, top--;
  }
}
int mark;
void dfs(int id) {
  vis[id] = 1;
  if(id == mark) return; // add this line
  while(1) {
    bitset<N> out = ~vis & e[id];
    int p = out._Find_first();
    if(p == N) break;
    dfs(p);
  }
}
int main() {
#ifdef ALEX_WEI
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  cin >> n >> m;
  for(int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    add(u, v), e[u][v] = 1;
  }
  for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i);
  for(int i = 1; i <= n; i++) {
    mark = i;
    static int lst[N], len;
    len = 0, vis.reset();
    for(int j = hd[i]; j; j = nxt[j]) {
      if(vis[to[j]]) ans[j] = 1;
      else dfs(to[j]);
      lst[++len] = j; 
    }
    vis.reset();
    for(int p = len; p; p--) {
      int j = lst[p];
      if(vis[to[j]]) ans[j] = 1;
      else dfs(to[j]);
    }
  }
  for(int i = 1; i <= n; i++)
    for(int j = hd[i]; j; j = nxt[j])
      if(col[i] ^ col[to[j]])
        ans[j] ^= 1;
  for(int i = 1; i <= m; i++) puts(ans[i] ? "same" : "diff");
  return cerr << "Time: " << clock() << endl, 0;
}
```

---

## 作者：SalN (赞：4)

[link](https://www.luogu.com.cn/problem/AT_arc092_d)

#### 题目大意

给一个 $n$ 点 $m$ 边的有向图。对于每一条边，查询取反其后图的 scc 数量是否改变。

$n\leq10^3,m\leq 2×10^5$

----

#### 题解

首先我们给原图跑一边 tarjan 求出祂的 scc，对于边我们分情况讨论。

对于两端在同一个 scc 的边 $(u,v)$，改变 scc 数量意思是这条边反向会让这个 scc 变成多个 scc（祂不可能使 scc 增加）。减少的情况就是原本可以从 $u$ 走到 $v$ 但是现在不行，这种情况显然是 $u\to v$ 只有只经过 $(u,v)$ 的路径，$u\to v$ 不存在除了 $(u,v)$ 的其它路径。

对于两端不在同一个 scc 的边 $(u,v)$，改变 scc 数量的意思是这条边反向会使多个 scc 连成一个 scc（祂不可能使 scc 减少）。增加的情况就是 $(v,u)$ 把 $u,v$ 连在一个环里面，意思是 $u\to v$ 存在除了 $(u,v)$ 的其它路径。

可以发现，求 $(u,v)$ 的答案，我们关心 ⌈ 原图中 $u,v$ 所在 scc 是否相同 ⌋ 以及 ⌈ $u\to v$ 有没有除了 $(u,v)$ 的其它路径 ⌋，这两者异或即为答案。前者跑 tarjan 就很好求了，我们考虑后者怎么做。

只有 $(u,v)$ 构成的路径显然长度为 1，除非重边，其它 $u\to v$ 的路径长度都大于 1 呀！那我们就有一个不太成熟的想法，可不可以记录 $f[u][v]$ 表示 $u\to v$ 的最长路径长度呢（？我们会发现这玩意儿有点丑陋，我们想办法舍弃。

把 $f$ 的定义舍弃最长，现在仅仅表示路径长度。我们肯定知道 ⌈ 暴力 dfs 不经过重复点 ⌋ 这种姿势算 $f$，是在图中抠出一颗搜索树算点到根的距离。那么这里 $f[u,v]$ 算了什么，有两种可能性，走 $u,v$ 或者走 $u,t_0,...,v$ 算了距离！我们得固定一个 $u$ 一次算祂的所有 $f[u][i]$，不然复杂度爆炸，于是乎我们不容易直接避免 $(u,v)$ 的计算。

那我们怎么办呢，我们可以再搜一个数组 $g[u][v]$，祂与 $f$ 的区别仅为搜索遍历边时顺序相反。如果 $v$ 被搜，$f$ 和 $g$ 肯定一个先搜 $v$ 一个先搜 $t_0$，搜了一个另一条边就不会进搜索树了。这样做我们可以利用 dfs 的小性质，如果 $u\to v$ 的路径不仅仅只有 $(u,v)$ 那么肯定会有 $f[u][v]>1$ 或者 $g[u][v]>1$。这样就可以啦 qwq

下面是 chelsy 不知道可不可爱的代码（

```cpp
#include<bits/stdc++.h>
#define pb push_back

using namespace std;

const int N=2e3, M=4e5;
int n, m, dfn[N], low[N], tim, u[M], v[M], cur[N];
int vis[N], stk[N], top, cnt, f[N][N], g[N][N];
vector<int> to[N];

void tarjan(int x) {
	dfn[x]=low[x]=++tim;
	vis[x]=1, stk[++top]=x;
	for(int i=0; i<to[x].size(); ++i) {
		int y=to[x][i];
		if(vis[y]==2) continue;
		if(!vis[y]) tarjan(y);
		low[x]=min(low[x],low[y]); 
	}
	if(dfn[x]==low[x]) {
		++cnt; int p;
		while(stk[top+1]!=x) {
			p=stk[top--];
			cur[p]=cnt, vis[p]=2;
		}
	}
}

void dfs(int x,int p) {
	for(int i=0; i<to[x].size(); ++i) {
		int y=to[x][i];
		if(f[p][y]==-1) f[p][y]=f[p][x]+1, dfs(y,p);
	}
}

void dfs2(int x,int p) {
	for(int i=to[x].size()-1; i>=0; --i) {
		int y=to[x][i];
		if(g[p][y]==-1) g[p][y]=g[p][x]+1, dfs2(y,p);
	}
}

signed main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=m; ++i) {
		scanf("%d%d", u+i, v+i);
		to[u[i]].pb(v[i]);
	}
	for(int i=1; i<=n; ++i) if(!vis[i]) tarjan(i);
	memset(f,-1,sizeof(f)), memset(g,-1,sizeof(g));
	for(int i=1; i<=n; ++i) f[i][i]=0, dfs(i,i);
	for(int i=1; i<=n; ++i) g[i][i]=0, dfs2(i,i);
	for(int i=1; i<=m; ++i) {
		bool t=(f[u[i]][v[i]]>1)|(g[u[i]][v[i]]>1);
		if(t^(cur[u[i]]==cur[v[i]])) printf("diff\n");
		else printf("same\n");
	}
	return 0;
}
```



---

## 作者：szTom (赞：3)

**题目大意**：给一个 $n$ 个点 $m$ 条边的有向图，对每一条边，求反向这条边后，图上的强连通分量个数是否改变。

让我们首先从一个例子出发思考这个问题，为此考虑下面这个图

![](https://s1.ax1x.com/2022/07/22/jOm2Sx.png)

这个图本身拥有两个强联通分量（SCC）：

![](https://s1.ax1x.com/2022/07/22/jOmO6f.png)

我们不妨首先考虑不属于任何SCC的边。当我们将下图中橙色边反向时，它与蓝色边配合，使得两个SCC合并为一个，因此答案为 `diff`：

![](https://s1.ax1x.com/2022/07/22/jOne74.png)

于是我们得到下面结论：

- 在原来的图上，存在一种不经过橙色边的方案，使得浅黄色点能够到达青色点，但是不存在一种从青色到达浅黄色的路径时，SCC数量减少。

另一方面，没有蓝色边的配合，这种“合二为一”是不可能做到的，即

- 在原来的图上，如果我们去掉蓝色边，此时存在一种不经过橙色边的方案，使得浅黄色点能够到达青色点，也不存在一种从青色到达浅黄色的路径，SCC数量不变。

让我们再来考虑另一种情况，反转原来的SCC中的一条边（下图中橙色边）。这种情况原有的SCC的结构被破坏，使得左边的三个节点不再构成一个SCC，因此答案为 `diff`：

![](https://s1.ax1x.com/2022/07/22/jOnh3q.png)

于是我们得到下面结论：

- 在原来的图上，存在一种不经过橙色边的方案，使得青色点能够到达浅黄色点，但是不存在一种从浅黄色到达青色的路径时，SCC数量增加。

但是SCC内部还（可能）拥有一种不那么重要的边，把下图中的橙色边反转后，右边SCC的结构没有变化，因此答案为 `same`：

![](https://s1.ax1x.com/2022/07/22/jOuZxP.png)
于是我们得到下面结论：

- 在原来的图上，存在一种不经过橙色边的方案，使得青色点能够到达浅黄色点，也存在一种从浅黄色到达青色的路径时，SCC数量不变。

好了，我们已经充分分析了这个图的结构。事实上，这个例子是就有指导性意义的：我们得到了几个基本结论，对于一条选定的边 $u\to v$

1. 如果在去掉选定边的图上，如果 $u\rightsquigarrow v$，但是 $v\not\rightsquigarrow u$ 时，SCC数量减少。
2. 如果在去掉选定边的图上，如果 $u\not\rightsquigarrow v$，同时 $v\not\rightsquigarrow u$ 时，SCC数量不变。
3. 如果在去掉选定边的图上，如果 $u\not\rightsquigarrow v$，但是 $v\rightsquigarrow u$ 时，SCC数量增加。
4. 如果在去掉选定边的图上，如果 $u\rightsquigarrow v$，同时 $v\rightsquigarrow u$ 时，SCC数量不变。

枚举每条边暴力DFS即可，时间复杂度 $\mathcal{O}(nm)$，足以通过此题。


---

## 作者：Dreamunk (赞：3)

这题正解是挺妙的，我这个做法就比较丑。

首先问题的关键在于求出，对每条边 $(u\to v)$，它删掉后， $u$ 是否还能到达 $v$。至于为什么，其他题解已经说得很清楚了。

我的判断方法大概是这样：
1. 枚举起点 $u$；
2. 对于 $u$，考虑把 $u$ 的入边删掉后的新图，把它缩点得到拓扑图；
3. 对于原图中的边 $(u\to v)$，它删掉后 $u$ 仍能到达 $v$，当且仅当满足下列条件之一
 
	* $(u\to v)$ 在拓扑图中所对应的边存在重边；
   * 拓扑图中存在边 $(w'\to v')$，其中 $w'$ 不是 $u$ 对应的点但是能从 $u$ 对应的点到达，而 $v'$ 是 $v$ 对应的点。

至于为什么，拓扑图中存在重边的那种情况显然；对于另一种情况，由于拓扑图中存在边 $(w'\to v')$，则原图中 $w$ 能到 $v$ 但 $v$ 到不了 $w$，所以 $u$ 想要到达 $w$ 就不能往 $(u\to v)$ 走，而 $u$ 能到达 $w$，所以路径 $u\to\cdots\to w\to\cdots\to v$ 必然可以不经过边 $(u\to v)$。

这是 $O(nm)$ 的，用 `vector` 存边就可以 AC。

```cpp
#include<cstdio>
#include<vector>
const int N=1003,M=2e5+3;
std::vector<int>g[N],gr[N],ps[N];
int n,m,ans[M],x[M],y[M],head[N+N],p[N],ord[N],dfc,used[N],d[N],f[N];
void Dfs0(int u,int w){
	int v;
	used[u]=1;
	for(int i=0;i<g[u].size();i++)if((v=g[u][i])!=w&&!used[v])
	  Dfs0(v,w);
	ord[++dfc]=u;
}
void Dfs1(int u,int r,int w){
	int v;
	p[u]=r;
	used[u]=1;
	for(int i=0;i<gr[u].size();i++)if((v=gr[u][i])!=w&&!used[v])
	  Dfs1(v,r,w);
}
void Scc(int w){
	int u;
	dfc=0;for(u=1;u<=n;u++)used[u]=0;
	for(u=1;u<=n;u++)if(u!=w&&!used[u])Dfs0(u,w);
	for(u=1;u<=n;u++)used[u]=0;
	for(int i=dfc;i;i--)if(!used[ord[i]])Dfs1(ord[i],ord[i],w);
}
int main(){
	int u,v,w;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
	  scanf("%d%d",&u,&v);
	  g[u].push_back(v);
	  ps[u].push_back(i);
	  gr[v].push_back(u);
	  x[i]=u,y[i]=v;
	}
	for(w=1;w<=n;w++){
	  Scc(w);
	  for(u=1;u<=n;u++)f[u]=d[u]=0;
	  for(int i=0;i<g[w].size();i++)++f[p[g[w][i]]];
	  for(int i=dfc;i;i--)if(f[p[u=ord[i]]]){
		for(int i=0;i<g[u].size();i++)if((v=g[u][i])!=w&&p[v]!=p[u])
		  f[p[v]]=1,d[p[v]]=1;
	  }
	  for(int i=0;i<g[w].size();i++)
		ans[ps[w][i]]=d[p[g[w][i]]]||f[p[g[w][i]]]>1;
	}
	Scc(0);
	for(int i=1;i<=m;i++)puts(ans[i]^(p[x[i]]==p[y[i]])?"diff":"same");
	return 0;
}
```

---

## 作者：Digital_Sunrise (赞：2)

[link](https://www.luogu.com.cn/problem/AT3945)
## 题解
假设现在需要处理 $u\to v$ 这条边.

如果 $u$ 本身不需要经过此边就能到达 $v$ ，那么 $u\to v$ 这条边似乎就没有什么价值，换成 $v\rightarrow u$ 后的强连通分量数量只能大于原来的数量。

如果原图存在 $v \to u$ 的路径，此时反边似乎没有什么用了，强连通分量数量只能小于等于原来的数量。

所以对于曾经的强连通分量的数量 $s$ 与改变一个边后的强连通分量的数量 $s'$ 的关系，我们似乎得到了一个牵强的条件不等式组。

当满足 $v \to u$ 的路径时（条件 $1$ ），有 $s\ge s' $ ；

当满足删去 $u \to v$ 时仍存在 $u \to v$ 的路径时（条件 $2$ ），有 $s\le s'$ 。

显然，当同时满足或同时不满足条件 $1$ 与条件 $2$ 时，强连通分量的数量不变。

对于条件 $1$ 很好处理，每个点 dfs 一边可以到达的点即可。

条件 $2$ 稍加思考也能想到：

对于一个节点，按照某种特定顺序 dfs 它的相邻节点，

如果发现某个相邻节点 $v$ 在由 $u$ 进行遍历前已经被访问过了，就说明 $u$ 可以通过另一条绕过 $u \to v$ 的路径到达 $v$ 。

为了使第一次按照某种特定顺序 dfs 时第一个被遍历的节点没有被判断过的情况，需要按照这种特定顺序的逆序顺序再次 dfs 。

核心代码：

```cpp
void dfs2(int u,int rt)//顺序遍历 
{
	vis[u] = 1;
	for(auto v : G[u])
	{
		if(vis[v] and u == rt)
			dne[rt][v] = 1;
		if(!vis[v])
			dfs2(v,rt);
	}
}

void dfs3(int u,int rt)//逆序遍历 
{
	vis[u] = 1;
	for(int i = G[u].size() - 1;i >= 0;i--)
	{
		int v = G[u][i];
		if(vis[v] and u == rt)
			dne[rt][v] = 1;
		if(!vis[v])
			dfs3(v,rt);
	}
}
```

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 1010;
const int maxm = 2e5 + 5;

int n,m;
vector <int> G[_];
int u[maxm],v[maxm];
bool arr[_][_];
bool dne[_][_];
bitset <_> vis;

void dfs1(int u)
{
	vis[u] = 1;
	for(auto v : G[u])
	{
		if(!vis[v])
			dfs1(v);
	}
}

void dfs2(int u,int rt)//顺序遍历 
{
	vis[u] = 1;
	for(auto v : G[u])
	{
		if(vis[v] and u == rt)
			dne[rt][v] = 1;
		if(!vis[v])
			dfs2(v,rt);
	}
}

void dfs3(int u,int rt)//逆序遍历 
{
	vis[u] = 1;
	for(int i = G[u].size() - 1;i >= 0;i--)
	{
		int v = G[u][i];
		if(vis[v] and u == rt)
			dne[rt][v] = 1;
		if(!vis[v])
			dfs3(v,rt);
	}
}

int main()
{
	cin >> n >> m;
	for(int i = 1;i <= m;i++)
	{
		cin >> u[i] >> v[i];
		G[u[i]].push_back(v[i]);
//		v[i] = G[u[i]].size() - 1;
	}
	for(int i = 1;i <= n;i++)
	{
		vis = 0;
		dfs1(i);
		for(int j = 1;j <= n;j++)
			arr[i][j] = vis[j];
		vis = 0;
		dfs2(i,i);
		vis = 0;
		dfs3(i,i);
	}
	for(int i = 1;i <= m;i++)
	{
		bool t = (arr[v[i]][u[i]] + dne[u[i]][v[i]]) & 1;
		if(!t)
			cout << "same\n";
		else
			cout << "diff\n";
	}
	return 0;
}
```

---

## 作者：qfpjm (赞：2)

# 题解

- 我们会发现，将一条边 $u\to v$ 反向，如果会影响到强连通分量的数量，仅有可能这一条边满足一下两种情况之一：

1. $v\to u$ 存在路径。

1. $u$ 到 $v$ 之间另外存在一条路径。

- 原因十分简单，如果两条都不满足，这条边就无法产生强连通分量；如果两条都满足，这条边的正反对强连通分量的构成没有影响。

- 由于题目只要求怕判断数量是否改变，所以我们需要判断上述两个条件是否仅有一个成立。

- 第一个询问暴力 `dfs` 即可。

- 第二个询问，对于每一个 $u$，我们枚举相临边，如果已经被访问过了，那么第二问就显然满足。正反各做一遍即可。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, mark[1005];
vector<int> G[1005];
pair<int, int> E[200005];
bool vis[1005], G1[1005][1005], G2[1005][1005];

void dfs1(int u, int st)
{
	G1[st][u] = 1;
	vis[u] = 1;
	for (int i = 0 ; i < G[u].size() ; i ++)
	{
		int v = G[u][i];
		if (!vis[v])
		{
			dfs1(v, st);
		}
	}
}

void dfs2(int u, int col, int k, int st)
{
	if (k)
	{
		if (mark[u] != col)
		{
			G2[st][u] = 1;
		}
	}
	else
	{
		mark[u] = col;
	}
	vis[u] = 1;
	for (int i = 0 ; i < G[u].size() ; i ++)
	{
		int v = G[u][i];
		if (!vis[v])
		{
			dfs2(v, col, k, st);
		}
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 1 ; i <= m ; i ++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		E[i] = make_pair(u, v);
	}
	for (int i = 1 ; i <= n ; i ++)
	{
		memset(vis, 0, sizeof(vis));
		dfs1(i, i);
	}
	for (int i = 1 ; i <= n ; i ++)
	{
		memset(vis, 0, sizeof(vis));
		vis[i] = 1;
		memset(mark, 0, sizeof(mark));
		for (int j = 0 ; j < G[i].size() ; j ++)
		{
			int v = G[i][j];
			if (!vis[v])
			{
				dfs2(v, j + 1, 0, i);
			}
		}
		memset(vis, 0, sizeof(vis));
		vis[i] = 1;
		for (int j = G[i].size() - 1 ; j >= 0 ; j --)
		{
			int v = G[i][j];
			if (!vis[v])
			{
				dfs2(v, j + 1, 1, i);
			}
		}
	}
	for (int i = 1 ; i <= m ; i ++)
	{
		int u = E[i].first, v = E[i].second;
		if (G1[v][u] != G2[u][v])
		{
			puts("diff");
		}
		else
		{
			puts("same");
		}
	}
}
```


---

## 作者：tzc_wk (赞：1)

[Atcoder 题面传送门](https://atcoder.jp/contests/arc092/tasks/arc092_d) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT3945)

~~orz ymx，ymx ddw %%%~~

首先既然题目要我们判断强连通分量个数是否改变，我们首先就将原图 SCC 缩个点呗，缩完点后我们很自然地将图中的边分为两类：在某个强连通分量中，和不在强连通分量中，我们对这两个情况分别进行讨论。

下面又到了喜闻乐见的找性质的时间了。首先，对于不在同一个强连通分量中的边，把它翻转之后不会影响强连通分量个数，因为这条边不在强连通分量里面，即便把它断掉也不影响强连通分量内部的点的可达性，因此把它翻转只可能接链成环，减少强连通分量个数，而把 $u\to v$ 翻转后，强连通分量个数减少当且仅当去掉这条边后仍存在 $u\to v$ 的路径，因为这样会出现 $u\to v\to u$ 的环。其次，对于在同一个强连通分量中的边，把它翻转之后，本来不能到达的点依然不能到达（证明可考虑反证法，对于两个节点 $x,y$，如果本来不存在 $x\to y$，翻转 $u\to v$ 后就存在了，那么必然是因为存在 $x\to v\to u\to y$ 的路径，而根据 $u,v$ 在同一个 SCC 中可知本来就存在 $v\to u$ 的路径 $P$（我们记其为 $x\xrightarrow{P}y$），那么必然存在不经过边 $v\to u$ 的 $x\to y$ 的路径 $x\to v\xrightarrow{P}u\to y$，矛盾），而对于原来可以到达的两个点 $x,y$，如果翻转后 $x$ 不能到达 $y$，那必然有 $x,y$ 在同一个连通分量中，此时连通分量的个数就会改变。我们~~惊奇地~~发现，在两种情况中，虽然情况细分起来不一样，但每种情况我们要求的目标是一样的，即**去掉某条边 $u\to v$ 后**，$u$ 是否还能到达 $v$。对于 $u,v$ 在同一个强连通分量中的边 $(u,v)$，如果上述回答为肯定的那么答案即为 `same`，否则答案为 `diff`，如果 $u,v$ 不在同一个强连通分量则反过来。

接下来考虑怎样求这个东西，考虑枚举 $u$ 并求出以 $u$ 为起点的所有边的答案，我们将以 $u$ 为起点的边按照编号（其实不一定要按编号，哪怕 `random_shuffle` 一下都行，只要钦定一个顺序即可）排序分别为 $e_1,e_2,\cdots,e_k$，它们的另一个端点分别为 $v_1,v_2,\cdots,v_k$。我们从小到大依次枚举这些边并实时维护一个 $vis_x$ 表示 $x$ 的可达性，对于某个 $e_i$，如果我们发现，枚举到 $e_i$ 时候，已经有 $vis_{v_i}=1$，那么说明肯定存在一个 $v_j$ 满足存在 $u\to v_j\to v_i$ 的路径，即去掉这条边后 $u$ 还能到达 $v_i$，否则我们就以 $v_i$ 为起点 BFS 一遍整张图，找到所有可达的点，注意不能经过 $u$，否则就无法说明是否经过 $u\to v_i$ 的边了。（具体实现方法很简单，只需将 $vis_u$ 设为 $1$，然后 BFS 所有 $vis_v\ne 1$ 的点）这样我们只考虑了 $e_j$ 对 $e_i$，$j<i$ 的贡献，因此还需反过来再操作一次，这样即可考虑所有边对 $v_i$ 的贡献，正确性显然，时间复杂度 $nm$，可以通过此题，于是这题就做完了。

什么？你说做完了？如果 $m$ 增大到 $10^6$ 恐怕你就束手无策了吧……因此我们还需探究复杂度更优的做法，注意到上述做法的瓶颈在于每次 BFS 都枚举了每条边，使得 BFS 的复杂度高达 $\mathcal O(m)$，事实上，如果当我们 BFS 到某个点 $u$ 时，只继续 BFS 它的邻居中满足 $vis_v=0$ 的点 $v$，这样 BFS 复杂度可以降到 $\mathcal O(n)$。那么怎么快速找出这些点呢？注意 $vis_v$ 的取值只可能是 $0/1$，因此可以联想到常数巨小无比的……`bitset`！我们建一个 `bitset` $t$，如果 $vis_v=1$，那么 `bitset` 上对应位为 $0$，否则为 $1$，再对每个点维护它与每个点之间是否有直接边相连，记作 $has_x$，那么当我们 BFS $u$ 时，只需遍历 $has_u\&t$ 上为 $1$ 的位即可。事实上，`bitset` 找出所有 $1$ 的复杂度是 $\mathcal O(\dfrac{n}{\omega})$ 的，可以这样实现：

```cpp
for(int y=b._Find_first();y^b.size();y=b._Find_next(y))
```

于是这题就真的做完了，复杂度 $\dfrac{n^3}{\omega}+w$，瓶颈在于 `bitset` 的遍历。

```cpp
const int MAXN=1e3;
const int MAXM=2e5;
int n,m,hd[MAXN+5],to[MAXM+5],nxt[MAXM+5],ec=0;
int U[MAXM+5],V[MAXM+5];
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
bool vis[MAXN+5];
int dfn[MAXN+5],low[MAXN+5],tim=0,bel[MAXN+5],stk[MAXN+5],tp=0,cmp=0;
bitset<MAXN+5> has[MAXN+5];
void tarjan(int x){
	dfn[x]=low[x]=++tim;vis[x]=1;stk[++tp]=x;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];
		if(!dfn[y]) tarjan(y),low[x]=min(low[x],low[y]);
		else if(vis[y]) low[x]=min(low[x],dfn[y]);
	} if(!(dfn[x]^low[x])){
		++cmp;int o;do{
			o=stk[tp--];vis[o]=0;bel[o]=cmp;
		} while(o^x);
	}
}
bool can[MAXM+5];
bitset<MAXN+5> alive;
void bfs(int s){
	queue<int> q;q.push(s);alive.reset(s);
	while(!q.empty()){
		int x=q.front();q.pop();bitset<MAXN+5> to=has[x]&alive;
		for(int y=to._Find_first();y^to.size();y=to._Find_next(y))
			alive.reset(y),q.push(y);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&U[i],&V[i]);adde(U[i],V[i]);
		has[U[i]].set(V[i]);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
//	for(int i=1;i<=n;i++) printf("%d\n",bel[i]);
	for(int i=1;i<=n;i++){
		alive.set();alive.reset(i);stack<pii> stk;
		for(int e=hd[i];e;e=nxt[e]){
			stk.push(mp(to[e],e));
			if(!alive.test(to[e])){can[e]=1;continue;}
			bfs(to[e]);
		} alive.set();alive.reset(i);
		while(!stk.empty()){
			pii x=stk.top();stk.pop();
			if(!alive.test(x.fi)){can[x.se]=1;continue;}
			bfs(x.fi);
		}
	}
	for(int i=1;i<=m;i++) printf("%s\n",((bel[U[i]]==bel[V[i]])^can[i])?"diff":"same");
	return 0;
}
```



---

## 作者：orz_z (赞：0)

### [ARC092D] Two Faced Edges

考虑强联通分量的本质，即其中任意两点 $u,v$ 都有一条 $u\to v$ 的路径，同时也有一条 $v\to u$ 的路径。

考虑转边强联通分量个数改变的情况，设有向边为 $(u,v)$：

* **有**一条反向边 $(v,u)$ 且除了 $(u,v)$ 外**无**一条从 $u$ 到 $v$ 的路径，强联通分量个数减少。
* **无**反向边 $(v,u)$ 且除了 $(u,v)$ 外**有**一条从 $u$ 到 $v$ 的路径，强联通分量个数增加。

个数不改变的情况即为：

* **有**一条反向边 $(v,u)$ 且除了 $(u,v)$ 外**有**一条从 $u$ 到 $v$ 的路径，强联通分量个数减少。
* **无**一条反向边 $(v,u)$ 且除了 $(u,v)$ **无**一条从 $u$ 到 $v$ 的路径，强联通分量个数减少。

总结一下，就是考虑以下几个因素：

* 当前边是否有反向边，维护方法比较简单。
* 除当前边外是否有一条从 $u$ 到 $v$ 的路径，考虑染色判断，方法不讲。

时间复杂度 $\mathcal O(nm)$，可优化。

```cpp
#include<bits/stdc++.h>

using namespace std;

//#define int long long
typedef long long ll;
#define ha putchar(' ')
#define he putchar('\n')

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x * f;
}

inline void write(int x)
{
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int _ = 1010, M = 2e5 + 10;

int n, m, rt, u[M], v[M], flg[_];

bool f1[_][_], f2[_][_];

bitset<_> vis;

vector<int> d[_];

void dfs1(int u)
{
	vis.set(u);
	f1[rt][u] = 1;
	for(int v : d[u])
		if(!vis[v]) dfs1(v);
}

void dfs2(int u, int cxr, bool t)
{
	if(t) flg[u] = cxr;
	else f2[rt][u] = (flg[u] != cxr);
	vis.set(u);
	for(int v : d[u])
		if(!vis[v]) dfs2(v, cxr, t); 
} 

signed main()
{
	n = read(), m = read();
	for(int i = 1; i <= m; ++i)
	{
		u[i] = read(), v[i] = read();
		d[u[i]].push_back(v[i]);
	}
	for(int i = 1; i <= n; ++i)
	{
		vis.reset();
		rt = i;
		dfs1(i); 
	}
	for(int i = 1; i <= n; ++i)
	{
		vis.reset(), vis.set(i);
		memset(flg, 0, sizeof flg);
		int nw = d[i].size();
		rt = i;
		for(int j = 0; j < nw; ++j)
			if(!vis[d[i][j]]) dfs2(d[i][j], j + 1, 1);
		vis.reset(), vis.set(i);
		for(int j = nw - 1; j >= 0; --j)
			if(!vis[d[i][j]]) dfs2(d[i][j], j + 1, 0);
	}
	//	for(int i = 1; i <= n; ++i)
	//	{
	//		for(int j = 1; j <= n; ++j) cout << f1[i][j] << " ";
	//		cout << "\n";
	//	}
	//	cout << "\n";
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= n; ++j) cout << f2[i][j] << " ";
			cout << "\n";
		}
	for(int i = 1; i <= m; ++i)
		puts(f1[v[i]][u[i]] ^ f2[u[i]][v[i]] ? "diff" : "same");
	return 0;
}

```



---

