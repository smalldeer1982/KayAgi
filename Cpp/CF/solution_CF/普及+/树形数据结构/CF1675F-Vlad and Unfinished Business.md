# Vlad and Unfinished Business

## 题目描述

### 题意简述

有一棵 $n$ 个节点的树，从节点 $x$ 出发，需要到 $a_1,a_2\dots a_k$ 节点完成任务（任意顺序），最终到达终点 $y$。走每条边的花费为 $1$，求最小花费。

## 样例 #1

### 输入

```
3

3 1
1 3
2
1 3
1 2

6 4
3 5
1 6 2 1
1 3
3 4
3 5
5 6
5 2

6 2
3 2
5 3
1 3
3 4
3 5
5 6
5 2```

### 输出

```
3
7
2```

# 题解

## 作者：MeowScore (赞：9)

题意：给出一棵树，给出起点 $x$ 和终点 $y$，以及一些关键点。要求从起点出发，经过所有的关键点（顺序无要求），最后来到终点。每次移动一条边的距离，求最少移动步数。

我们以 $x$ 为树根，可以发现，依次处理 $x$ 的每个子树然后回到 $x$，再处理下一个……这样是最好的。由于包含 $y$ 的那棵子树比较特殊，这里先不考虑。我们来思考如何计算一个子树内对答案的贡献。不难发现，从 $x$ 进入一棵子树，然后经过该子树内的所有关键点，再回到 $x$，最小的步数就是**删掉该子树内所有的极大不含关键点子树后剩余边的数量的二倍**。

最后考虑包含 $y$ 的子树，假定 $y$ 也是关键点，按照上面的规则计算出答案后，由于最后要停在 $y$ 点，那么在最优的情况下，答案再减去 $x$ 和 $y$ 之间的距离（即在原有答案上减去最后一次返回根的步数）。

代码：

```
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
int a[N];
int head[N],to[N*2],nex[N*2],cnt;
void add(int x,int y){
	cnt++;
	to[cnt]=y;
	nex[cnt]=head[x];
	head[x]=cnt;
}
int fa[N],dep[N],sz[N];
int b[N],p[N];
int n,m,st,ed;
void dfs1(int x,int f){
	fa[x]=f;
	dep[x]=dep[f]+1;
	sz[x]=1; 
	if(b[x])
		p[x]=1;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==f)
			continue;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(p[y])
			p[x]=1;
	}
}
int res;
void dfs2(int x){
	if(!p[x]){
		res+=sz[x];
		return;
	}
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==fa[x])
			continue;
		dfs2(y);
	}
}
int main(){
	int T;
	cin>>T;
	while(T--){
		for(int i=1;i<=n;i++)
			head[i]=b[i]=p[i]=sz[i]=dep[i]=fa[i]=0;
		scanf("%d%d%d%d",&n,&m,&st,&ed);
		cnt=0;
		int qwq=0;
		for(int i=1;i<=m;i++){
			scanf("%d",&a[i]);
			b[a[i]]=1;
		}
		b[ed]=1;
		for(int i=1;i<n;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);
			add(y,x);
		}
		dfs1(st,st);
		res=0;
		dfs2(st);
		int ans=(n-1-res)*2-(dep[ed]-1);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：panyanppyy (赞：3)

给出一种贪心做法。
## Problem
$T$ 组数据，给定一个 $n$ 个点的有根树，其中有 $m$ 个点打上了标记，你需要找出一条从起点 $x$ 到终点 $y$ 并经过所有带标记点的路径，求路径**最小**长度（点和边可以**重复经过**）。
## Solution
因为终点也一定要经过，所以也要打上标记。

先考虑标记点不在终点所在子树内的情况。
![](https://cdn.luogu.com.cn/upload/image_hosting/00gzr5c8.png)

如点 $7$，最优情况显然是从 $3$ 先走到 $7$ 并返回还有根节点 $1$，继续遍历 $8$。

可以发现每遍历一个点还要回去，答案累加 $2$。

标记点在终点所在子树内的情况。
1. 在到终点的路径上：显然只需要遍历一遍不用回头，答案累加 $1$。

2. 在终点的子树中：还要回到终点，答案累加 $2$。

**做法**：
钦定 $x$ 为根，给 $y$ 打上标记 $2$ 并上传，再给所有标记点打上较小的标记 $1$ 并上传，取最大的标记。

然后从 $x$ 出发跑 dfs，累加答案即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
int T,n,m,s,t,ans;
int dep[N],g[N];
vector<int>e[N];
inline void dfs1(int u,int rt){
	dep[u]=dep[rt]+1;
	for(int v:e[u])if(v^rt)
		dfs1(v,u),g[u]=max(g[u],g[v]);
}
inline void dfs2(int u,int rt){
	for(int v:e[u])if(v^rt&&g[v]==1)
		dfs2(v,u),ans+=2;
	for(int v:e[u])if(v^rt&&g[v]==2)
		dfs2(v,u),ans++;
}
inline void work(){ans=0;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=n;i++)g[i]=0,e[i].clear();
	g[t]=2;
	for(int i=1,x;i<=m;i++){
		scanf("%d",&x);
		if(g[x])m--,i--;
		else g[x]=1;
	}
	for(int i=1,x,y;i<n;i++)
		scanf("%d%d",&x,&y),e[x].emplace_back(y),e[y].emplace_back(x);
	dfs1(s,0),dfs2(s,0);
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--)work();
	return 0;
}
```

---

## 作者：incra (赞：0)

duel 到的（场切但是 bot 似了怎么评价/cf）

一道有趣题目。

我们先考虑如果我们要遍历整棵树要多少次，显然是点数减去根到所有叶子节点的最大长度。

然后我们就可以想到答案有可能是使得这些点（包括 $s$ 和 $t$）连通的最小边数乘以 $2$ 然后减去 $x$ 到 $y$ 的距离。

然后手玩样例发现是正确的。

代码不给了。

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
有一棵节点数为 $n$ 的树，我们从节点 $x$ 出发，前往几个节点去做任务，最后到达终点 $y$，走每条边代价为 $1$，问做完所有任务到达终点的最小代价。
## 大体思路
我们考虑贪心，很显然每个任务节点（除了从起点到终点的路径之外）做完任务后都要回到起点，所以到这样节点的路径我们都赋值为 $2$，到终点 $y$ 的路径就不用回来了，所以都赋值为 $1$，这里有一个分类：在终点子树上的点，如果在去往终点的路径上，则正常赋值成 $1$；如果在终点之后，则终点和这个点之间的路径赋值为 $2$，如果分叉了，从那个公共祖先到任务节点的路径赋值为 $2$，其他的赋值为 $1$。

最后我们输出所有边的值即可。
## 代码实现
设 $x$ 为根，将 $y$ 到 $x$ 的路径都赋值为 $1$，然后再处理所有的任务节点，到 $x$ 的路径都赋值成 $2$，如果有上面分类的情况，直接覆盖掉 $x$ 给的那个 $2$ 即可。

上述过程都先在所涉及节点上做个标记（我们把边标记化为点标记，这样存图好存），之后一个 dfs 直接处理即可。

最后一个 dfs 累加一下所有的代价，输出即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int bj[200005];
vector<int> tu[200005];
void sc(int x,int fa){
	for(auto v:tu[x]){
		if(v==fa){
			continue ;
		}
		sc(v,x);
		if(bj[x]==1||bj[v]==1){//是终点路径上，就算儿子或自己是2，也得标成1 
			bj[x]=1;
		}
		else if(bj[x]==2||bj[v]==2){//如果不是终点路径上的，如果儿子或自己是2，就标为2 
			bj[x]=2;
		}
	}
}
int ans;
void qsum(int x,int fa){
	for(auto v:tu[x]){
		if(v==fa){
			continue ;
		}
		else{
			qsum(v,x);
			ans+=bj[v];//累加一下我给的标记
		}
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		ans=0;
		int n,k;
		cin>>n>>k;
		int x,y;
		cin>>x>>y;
		for(int i=1;i<=n;i++){//清空一下上一个用过的内存 
			bj[i]=0;
			tu[i].clear();
		} 
		bj[y]=1;//打上1的标记，等待上传处理 
		for(int i=1;i<=k;i++){
			int aa;
			cin>>aa;
			if(!bj[aa]){
				bj[aa]=2;//打上赋值2的标记，等待上传处理 
			}
		}
		for(int i=1;i<n;i++){//正常邻接表存图 
			int xx,yy;
			cin>>xx>>yy;
			tu[xx].push_back(yy);
			tu[yy].push_back(xx);
		}
		sc(x,0);//标记上传 
		qsum(x,0);//处理答案
		cout<<ans<<endl; 
	} 
	return 0;
}
```

---

## 作者：guanyf (赞：0)

### 题意
- 给定一棵 $n$ 个点的无根树，你初始时在点 $x$，你要按任意顺序经过点 $a_1,a_2,a_3,\dots,a_k$，最终到达点 $y$，求经过的最小距离。

- $1 \le n,k \le 2 \times 10^5$

### 分析、思路
由于是从 $x$ 出发，因此可以看作 $x$ 是根。很容易就会想到一种走的策略：对于每个点来说，如果它的一个子树中有**关键点**，则必定要走到它的一个子树中，出入一共是 $2$ 点花费，还要加上子树的根的花费。

由于最终是回到点 $x$，但题目要求可以从任一点来到点 $y$，我们可以先求出点 $y$ 到所有关键点的距离，再去求出走完所有关键点到当前关键点的最小距离。我们已经求出了到点 $x$ 的最小距离，只需要减去当前关键点到点 $x$ 的距离行了。

时间复杂度：$\operatorname{O}(n \log n)$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define Pii pair<int, int>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int T, n, k, x, y, dis[MAXN], DIS[MAXN], jl[MAXN];
vector<int> e[MAXN];
unordered_map<int, bool> vis;
void dfs(int u, int fa) {
  for (auto v : e[u]) {
    if (v != fa) {
      dis[v] = dis[u] + 1;
      dfs(v, u);
    }
  }
}
bool DFS(int u, int fa) {
  bool flag = vis.count(u);
  for (auto v : e[u]) {
    if (v != fa) {
      jl[v] = jl[u] + 1;
      if (DFS(v, u)) {
        flag = 1;
        DIS[u] += DIS[v] + 2;
      }
    }
  }
  return flag;
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    int ans = INT_MAX;
    cin >> n >> k >> x >> y, vis.clear();
    for (int i = 1, x; i <= k; i++) {
      cin >> x, vis[x] = 1;
    }
    for (int i = 1; i <= n; i++) {
      e[i].clear(), dis[i] = DIS[i] = jl[i] = 0;
    }
    for (int i = 1, u, v; i < n; i++) {
      cin >> u >> v;
      e[u].push_back(v), e[v].push_back(u);
    }
    dfs(y, 0);
    DFS(x, 0);
    for (int i = 1; i <= n; i++) {
      (vis.count(i)) && (ans = min(ans, DIS[x] - jl[i] + dis[i]));
      // cout << DIS[i] << ' ' << jl[i] << ' ' << dis[i] << '\n';
    }
    cout << ans << '\n';
  }
  return 0;
}
```


---

## 作者：EnofTeiPeople (赞：0)

先考虑 $x$ 和 $y$ 是同一个点的情形，实际上将所有节点到起点 $x$ 的路径标记上，边数的两倍就是答案，因为需要一去一回，所以每一条边会经过两次。

增加了终点 $y$ 之后，$y$ 也变成了需要经过的点，这时候，我们可以先遍历以 $x$ 为根的树中与 $y$ 不同子树的点，再往 $y$ 走，中途遍历路径外伸出的点，遍历 $y$ 的子树中的点，最后到达 $y$，于是答案是总标记边数减去 $x$ 和 $y$ 的距离。

代码实现中，可以用 $x$ 作树根进行遍历，记录父亲和深度，于是 $x$ 和 $y$ 的距离就是 $y$ 的深度，在从那 $k$ 个点和 $y$ 出发，向上跳父节点并标记。注意调到已经标记的节点时，其上面必定是已经标记了的，由于根节点没有父边，所以不能标记，时间 $O(\sum(n+k))$，空间 $O(\max(n+k))$：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5,M=2e6+6;
inline void File(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
}
namespace fast_rd{
	const int R=1e5+5;
	char buf[R+5],c;
	int it,ed,f;
#define gc (it==ed&&(ed=(it=0)+fread(buf,1,R,stdin),it==ed)?EOF:buf[it++])
	template<typename _Tp>
	inline void read(_Tp &x){
		for(f=0,c=gc;c<48;c=gc)if(c=='-')f=!f;
		for(x=0;c>47;x=x*10+(48^c),c=gc);if(f)x=-x;
	}
	template<typename _Tp,typename..._tps>
	inline void read(_Tp &x,_tps&...y){
		read(x),read(y...);
	}
};
using fast_rd::read;
using ll=long long;
int T,n,k,s,t,f[N],d[N],a[N],ans;
bitset<N>vs;
vector<int>lk[N];
void dfs(int x=s){
	for(int y:lk[x])
		if(y!=f[x])f[y]=x,d[y]=d[x]+1,dfs(y);
}
int main(){
	File();
	read(T);int i,x,y;
	while(T--){
		read(n,k,s,t);
		for(x=1;x<=n;++x){
			vs[x]=f[x]=d[x]=0;
			lk[x].clear();
		}
		lk[0].resize(k+1),lk[0][0]=t;
		for(i=1;i<=k;++i)read(lk[0][i]);
		for(i=1;i<n;++i){
			read(x,y);
			lk[x].push_back(y);
			lk[y].push_back(x);
		}dfs(),ans=-d[t];
		for(int x:lk[0])
			for(y=x;y!=s&&!vs[y];y=f[y])vs[y]=1;
		for(x=1;x<=n;++x)
			if(vs[x])ans+=2;
		printf("%d\n",ans);
	}return 0;
}
```

---

## 作者：ryanright (赞：0)

## Description

Vlad 和 Nastya 住在一个有着 $n$ 栋房子和 $n-1$ 条路的城市。你可以把这座城市理解成一棵树。

Vlad 住在 $x$ 号房里，Nastya 住在 $y$ 号房里。Vlad 打算去拜访 Nastya。然而，他想起来在拜访 Nastya 之前还有 $k$ 件事要做，第 $i$ 件事要在第 $a_i$ 号房子里完成。可以以任何顺序办事，办事不需要时间。Vlad 可以用一分钟从一个房子去到与之有路连接的另一个房子。

求 Vlad 最少要用多久才能办完所有事并来到 Nastya 家。

## Solution

我们以 Vlad 家为根节点，那么我们最后再去 Nastya 家所在的子树。因为如果先去了 Nastya 家那边，还得再回 Vlad 家去别的地方办事，这样就浪费了时间，因为最后还得去 Nastya 家。

因此我们每下到一个结点，就判断这个结点一下是否还有事情要办，如果有事就下去办，如果 Nastya 在那个子树就最后再去。

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int to[200005], fa[200005];
bool task[200005];
vector<int> tr[200005];
bool dfs1(int x) {//建立树结构
	for (int i = 0; i < tr[x].size(); i++) {
		int &go = tr[x][i];
		if (go == fa[x])
			continue;
		fa[go] = x;
		task[x] |= dfs1(go);
	}
	return task[x];
}
bool dfs2(int x, int y) {//找到 Nastya 家
	if (x == y)
		return 1;
	for (int i = 0; i < tr[x].size(); i++) {
		int &go = tr[x][i];
		if (go == fa[x])
			continue;
		if (dfs2(go, y)) {
			to[x] = go;
			return 1;
		}
	}
	return 0;
}
int dfs3(int x) {//正式行动
	int ans = 0;
	for (int i = 0; i < tr[x].size(); i++) {
		int &go = tr[x][i];
		if (go == fa[x])
			continue;
		if (to[x] != go && task[go])
			ans += dfs3(go) + 2;
	}
	if (to[x] != -1)
		ans += dfs3(to[x]) + 2;
	return ans;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(task, 0, sizeof(task));
		memset(to, -1, sizeof(to));
		memset(fa, -1, sizeof(fa));
		int n, k, x, y;
		scanf("%d%d%d%d", &n, &k, &x, &y);
		for (int i = 1; i <= k; i++) {
			int a;
			scanf("%d", &a);
			task[a] = 1;
		}
		for (int i = 1; i < n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			tr[u].emplace_back(v);
			tr[v].emplace_back(u);
		}
		dfs1(x);
		dfs2(x, y);
		int ans = dfs3(x), now = x;
		while (now != y) {//因为 dfs3 最后会回到根节点，因此要减去两人家之间的距离
			now = to[now];
			ans--;
		}
		printf("%d\n", ans);
		for (int i = 1; i <= n; i++)
			tr[i].clear();
	}
	return 0;
}
```

---

## 作者：Hooch (赞：0)

### 题目大意

有一棵 $n$ 个节点的树，小 V 正在 $x$ 节点，他想去小 N 所在的 $y$ 号节点。但是小 V 要去 $k$ 个节点完成任务，任务地点分别为 $a_1,a_2,\cdots a_k$，去这些任务地点的顺序并不重要。每经过一个边就会花费单位 $1$ 的时间，现在小 V 希望尽快做完任务后去小 N 所在的 $y$ 节点，请你求出他最少需要花费的单位时间。

### 基本思路

我们首先不管 $y$ 节点，算出若 $x=y$ 时，只要求完成 $k$ 个任务所需要的最少的时间。

我们发现，去哪个子节点的顺序并不重要，因为 $x=y$ 这个特殊性质，所以每一条到 $a_i$ 的路径都会经历两次。

那么当 $x\ne y$，但是 $y$ 所在的子树不包含任何一个 $a_i$ 的时候呢？

我们也能发现，去哪个子节点的顺序也不重要，因为相当于从 $x=y$ 的情况，再加上一个 $x→y$ 的距离就行了。

在考虑最终没有任何特殊条件的情况，我们发现能从上一种转化成现在这种，不管哪次，$y$ 所在的子树都是最后考虑的。而我们只要单独考虑 $y$ 所在的子树就行了。

我们可以结合下面这个例子理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/ls8gqcmd.png)

（绿色为任务点，蓝色是 $x$，红色是 $y$）

我们先不理 $y$ 点，将其他所有任务都做了，这个时候我们也说过是最优的。

然后，我们到达了 $y$ 点，我们发现在它的下面还有一个任务没做，所以我们就把这个任务做了。

之后我们与上面那些特殊情况不同的就是我们只需要到达 $y$ 节点就行了，并不需要再返回 $x$ 点。

### 代码

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (register int i(l); i <= r; ++i)
#define rep2(i, l, r) for (register int i(l); i >= r; --i)
using namespace std;
const int N = 2e5 + 5;
int n, k, m, t, X, y, a[N]; vector <int> G[N];
bool where[N], vis[N], p[N];
inline pair <bool, bool> dfs1(int x, int f) {
	if (x == y) where[x] = 1;
	if (vis[x]) p[x] = 1;
	rep1(i, 0, (int)G[x].size() - 1) {
		int v = G[x][i];
		if (v == f) continue;
		pair <bool, bool> tmp = dfs1(v, x);
		where[x] |= tmp.first;
		p[x] |= tmp.second;
	}
	return make_pair(where[x], p[x]);
}
inline int dfs2(int x, int f) {
	int ans = 0, flg = 0;
	for (int i = 0; i < (int)G[x].size(); ++i) {
		int v = G[x][i];
		if (v == f) continue;
		if (where[v]) flg = v;
		else if (p[v]) ans += dfs2(v, x) + 1;
	}
	if (flg) {
		ans += dfs2(flg, x) + 1;
		return ans;
	}
	if (x == y) return ans;
	else return ans + 1;
}
#define init(s) memset(s, 0, sizeof s)
signed main(void) {
	ios::sync_with_stdio(false);
	cin >> t; while (t--) {
		init(where); init(vis); init(p); 
		cin >> n >> k >> X >> y; rep1(i, 1, k) cin >> a[i], vis[a[i]] = 1;
		rep1(i, 1, n) G[i].clear();
		memset(where, 0, sizeof where);
		rep1(i, 1, n - 1) {
			int u, v; cin >> u >> v;
			G[u].push_back(v); G[v].push_back(u);
		}
		dfs1(X, -1);
		cout << dfs2(X, -1) << endl;
	}
}
```

---

