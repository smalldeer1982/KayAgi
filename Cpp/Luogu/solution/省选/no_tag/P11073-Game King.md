# Game King

## 题目描述

你穿越到了游戏王的世界，现在你正在和你的对手——一张 $n$ 个点 $m$ 条边的有向图决斗。

中间忘了。

真正的决斗者，一切都是必然。为了更好的应对面前的决斗，你需要知道有多少个点 $x$ 满足如下条件。

- 对于任意一个点 $y$，均满足 $x$ 能到达 $y$ 或 $y$ 能到达 $x$（我们认为一个点能到达它自己本身）。

## 说明/提示

### 样例一解释

可以证明，只有点 $1,4$ 满足要求。

由于点 $3$ 无法到达点 $2$ 且无法被点 $2$ 到达，故点 $2,3$ 不满足要求。

### 样例二

见下发文件下的 `gameh2.in` 与 `gameh2.ans`。

该样例约束与测试点 $2$ 一致。

### 样例三

见下发文件下的 `gameh3.in` 与 `gameh3.ans`。

该样例约束与测试点 $3$ 一致。

### 数据范围

本题共有 $10$ 个测试点，测试点不等分，每个测试点的具体分值如下。

|测试点编号|分值|$n=$|$m=$|
|:-:|:-:|:-:|:-:|
|$1\sim 2$|$5$|$10$|$20$|
|$3\sim 4$|$5$|$100$|$10^3$|
|$5\sim 6$|$5$|$10^3$|$10^4$|
|$7\sim 8$|$15$|$5\times 10^4$|$5\times 10^5$|
|$9\sim 10$|$20$|$10^6$|$3\times 10^6$|

对于所有数据，保证 $10\le n\le 10^6$，$20\le m\le 3\times 10^6$。

对于奇数编号测试点，保证给定的图没有**不同点数 $\mathbf{>1}$** 的环。

### 提示

**本题输入输出规模较大，请使用较为快速的输入输出方式。**

## 样例 #1

### 输入

```
4 4
1 2
1 3
2 4
3 4```

### 输出

```
2```

# 题解

## 作者：dehsirehC (赞：8)

## 前言

部分分有点少，但出题人已经尽力了......

## $30\%$ 的数据

对于每一个点， `BFS` 一遍找到所有它能到达的点，再暴力枚举每一个点判断是否合法。

总时间复杂度 $O(nm)$ 。

## $60\%$ 的数据

考虑使用 `bitset` 优化 `30% 的数据` 中的算法，即用 `bitset` 表示一个点能到达的点的集合。

具体的，由于同一个强连通分量内的点互相可达，故可以先对图进行 `缩点` 变成一张有向无环图。

此时我们按照拓扑序从大到小计算每个点能到达的点，每次将它连出去的点的 `bitset` 或起来即可。

总时间复杂度 $O(\frac{nm}{\omega})$ ，其中 $\omega$ 大概可以看作 $64$ ，空间大约是 $n^2$ 个 `bit` 。

## $100\%$ 的数据

同样的，先对图进行 `缩点` 变成一张有向无环图。~~当然不 `缩点` 也可以得到足足 $50\%$ 的分数！~~

注意到拓扑序比较大的点一定无法到达比较小的点，换句话说一个点只可能到达比它拓扑序大的点。

考虑对于每一个点算出它是否能到达所有拓扑序比它大的点，以及能否被所有拓扑序比它小的点到达。

接下来考虑如何计算前者，后者同理。按拓扑序从大到小不断加点，考虑一个点合法的充要条件。

若当前图有至少两个点入度为 $0$ ，则新加入的点不符合条件，因为它无法到达另一个入度为 $0$ 的点。

否则必定符合要求，考虑每个点只保留一个入边，最终每个点沿着入边走必定能走到当前新加入的点。

在 `拓扑排序` 的时候动态维护一下有多少个点入度为 $0$ 即可。总时间复杂度 $O(n+m)$ 。

---

## 作者：aioilit (赞：4)

首先 SCC 缩点，得到一个有向无环图。我们思考在 DAG 上怎样的点是满足条件的。将题目限制转化一下，我们建出正图与反图，若某个点在两个图中能够到达的点集的并集为全集，则该点满足条件。具体地，我们跑正反图上分别跑一次拓扑排序，维护未进过栈的点集，记点 $x$ 在两次拓扑排序中维护的点集为 $A$ 和 $B$，若该点是当前栈中唯一的点，并且这两个点集和点 $x$ 能够覆盖整张图，则它是合法点。由于我们只关心点集的大小，所以不需要哈希集合内点的编号，直接简单处理即可。实现较为容易，时间复杂度线性。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=1000005,M=3000005;
int n,m;
struct Edge{
	int u,v;
}e[M<<1]; 
int cnt;
int siz[N];
int scc[N],dfn[N],low[N],scc_cnt,ck;
int stk[N],top;
vector<int> g[N];
void Tarjan(int u){
	dfn[u]=low[u]=++ck;
	stk[++top]=u;
	for(auto v:g[u]) {
		if(scc[v]) continue;
		if(!dfn[v]) Tarjan(v);
		low[u]=min(low[u],low[v]);
	} 
	if(low[u]^dfn[u]) return ;
	++scc_cnt;
	int it;
	do{
		scc[it=stk[top--]]=scc_cnt;
		++siz[scc_cnt];
	}while(it^u);
}
int deg[N];
vector<int> g2[N];
int ans;
int ok1[N],ok2[N],h1[N],h2[N];
void Solve(int *ok,int *h){
	top=0;
	for(int i=1;i<=scc_cnt;i++) if(!deg[i]) stk[++top]=i;
	int sum=n;
	while(top) {
		int u=stk[top--];
		sum-=siz[u];
		h[u]=sum;
		if(!top) ok[u]=1;
		for(auto v:g2[u])
			if(!--deg[v]) stk[++top]=v;
	}
}
int main(){
	n=read(); m=read();
	for(int i=1;i<=m;i++){
		e[i].u=read(),e[i].v=read();
		int u=e[i].u; int v=e[i].v;
		g[u].push_back(v);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	for(int i=1;i<=m;i++) {
		int u=e[i].u; int v=e[i].v;
		u=scc[u]; v=scc[v];
		if(u==v) continue;
		g2[u].push_back(v); 
		++deg[v];
	}
	Solve(ok1,h1);
	for(int i=1;i<=n;i++) g2[i].clear(),deg[i]=0;
	for(int i=1;i<=m;i++) {
		int u=e[i].u; int v=e[i].v;
		u=scc[u]; v=scc[v];
		if(u==v) continue;
		g2[v].push_back(u);
		++deg[u];
	}
	Solve(ok2,h2);
	for(int i=1;i<=scc_cnt;i++) if(ok1[i]&&ok2[i]&&h1[i]+h2[i]+siz[i]==n) ans+=siz[i];
	printf("%d",ans);
	return 0;
}
```

---

## 作者：CaiZi (赞：3)

## Game King 题解
**[题目链接](https://www.luogu.com.cn/problem/P11073)（[加强版](https://www.luogu.com.cn/problem/CF1062F)）**
### 题目分析
很好玩的题！

首先，每个强连通分量内部的点都可以互相到达，所以只要一个强连通分量内有一个点满足条件，那么其他点都可以先到达这个点，进而也满足条件。于是我们先缩点，于是该图变成一张 DAG（有向无环图）。**接下来我们讲的图均指缩点后的 DAG。**

接下来，由于是一张 DAG，因此对于点 $x$，只能到达拓扑序比它大的点，同样只能被拓扑序比它小的点到达。因此我们现在有两个问题，分别是判断**某个点**能否到达**拓扑序**比它大的点，和**某个点**能否被**拓扑序**比它小的点到达。第一个问题可以直接拓扑排序；而第二个问题，我们先建出**反图**，就可以转换成第一个问题。任何时候拓扑排序中队列中的点都互相不可到达。所以将一个点弹出队列时，如果队列任**有**元素，该点就是不满足条件的。
> 证：因为如果拓扑排序中队列中的点 $a$ 可以到达点 $b$，那么点 $b$ 的入度就会加 $1$，此时需要先将 $a$ 弹出队列，才可以将点 $b$ 加入队列，与假设冲突，故命题成立。

然后，这题还没有做完，我们对于**某个点**，还需要记录两次拓扑排序时，在该点之后被弹出队列（即拓扑序更大）的点的个数，因为**某个点**有可能两次拓扑排序被弹出队列时，队列内均没有点，但是却不满足条件。最简单的情况是图不弱连通，但是图弱连通时应该也有这种情况。所以我们要判断这两个记录的值之和加 $1$ 是否为点的总个数。

最后，对于每个满足条件的点，加上该点所代表强连通分量的大小。
### 代码展示
时间复杂度 $O(n+m)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int head[3000001],to[3000001],nxt[3000001],cnt,dfn[1000001],low[1000001],siz[1000001],be[1000001],tim,scc,in[1000001],a[1000001],n,m,x,y;
bool vis[1000001],b[1000001];
stack<int>t;
queue<int>q;
vector<int>g[1000001];
inline void tarjan(int i){
	vis[i]=true;
	tim++;
	dfn[i]=low[i]=tim;
	t.push(i);
	for(int j=head[i];j!=0;j=nxt[j]){
		if(vis[to[j]]){
			if(!be[to[j]]){
				low[i]=min(low[i],dfn[to[j]]);
			}
		}
		else{
			tarjan(to[j]);
			low[i]=min(low[i],low[to[j]]);
		}
	}
	if(low[i]==dfn[i]){
		scc++;
		int j;
		do{
			j=t.top();
			t.pop();
			be[j]=scc;
			siz[scc]++;
		}while(j!=i);
	}
	return;
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cnt++;
		cin>>x>>to[cnt];
		nxt[cnt]=head[x];
		head[x]=cnt;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=head[i];j!=0;j=nxt[j]){
			if(be[i]!=be[to[j]]){
				g[be[i]].push_back(be[to[j]]);
				in[be[to[j]]]++;
			}
		}
	}
	x=scc;
	for(int i=1;i<=scc;i++){
		b[i]=true;
		if(in[i]==0){
			q.push(i);
		}
	}
	while(!q.empty()){
		y=q.front();
		q.pop();
		x--;
		a[y]+=x;
		if(!q.empty()){
			b[y]=false;
		}
		for(int i:g[y]){
			in[i]--;
			if(in[i]==0){
				q.push(i);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=head[i];j!=0;j=nxt[j]){
			if(be[i]!=be[to[j]]){
				g[be[to[j]]].push_back(be[i]);
				in[be[i]]++;
			}
		}
	}
	x=scc;
	for(int i=1;i<=scc;i++){
		if(in[i]==0){
			q.push(i);
		}
	}
	while(!q.empty()){
		y=q.front();
		q.pop();
		x--;
		a[y]+=x;
		if(!q.empty()){
			b[y]=false;
		}
		for(int i:g[y]){
			in[i]--;
			if(in[i]==0){
				q.push(i);
			}
		}
	}
	x=0;
	for(int i=1;i<=scc;i++){
		if(b[i]&&a[i]+1==scc){
			x+=siz[i];
		}
	}
	cout<<x;
	return 0;
}
```
**[提交记录](https://www.luogu.com.cn/record/178525251)**

---

## 作者：Priestess_SLG (赞：1)

糖丸啦。~~是谁在比赛中获得了 30 分的好成绩来着？~~

首先套路的对图做强连通缩点，得到一个 dag 森林。

考虑什么样的点可以满足题目中给出的那个条件。首先如果 dag 森林在无向环境下不连通那么肯定不可能满足，否则考虑对 dag 森林做拓扑排序，那么 $x$ 点满足条件的充要条件是：

+ $x$ 点可以到达所有拓扑序比 $x$ 大的点。
+ $x$ 点可以被所有拓扑序比 $x$ 小的点到达。

那么什么样的 $x$ 会满足这个条件呢？考虑经典结论：

> 在拓扑排序的任意时刻，队列中任意两点都不可达。

（没见过建议去做 [CF1062F Upgrading Cities](/problem/CF1062F)）。

然后正反建两遍图跑拓扑排序验证上面的结论，然后因为有图不连通等神秘 corner case，还需要两次记录到每一个点的时候，还没有访问过的点的数量是多少，最后再判断一下即可。

时间复杂度为 $O(n)$，但是不知道为什么我跑的很慢（可能写丑了）。

```cpp
// #pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>
#define y1 storz
#define int long long
using namespace std;
const int inf = 2e18;
using ull = unsigned long long;
template<class _T>
using treap = __gnu_pbds::tree<_T, __gnu_pbds::null_type, less_equal<_T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
using POD = pair<double, double>;
const double pi = acos(-1);
using cauto = complex<double>;
const int mod = 998244353;
const int N = 1000010;
stack<int> stk;
vector<int> adj[N];
int dfn[N], low[N], bel[N], siz[N], idx, tot, instk[N];
void dfs(int u) { dfn[u] = low[u] = ++idx, instk[u] = 1, stk.emplace(u);
    for (int &v : adj[u]) if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
    else if (instk[v]) low[u] = min(low[u], dfn[v]);
    if (dfn[u] == low[u]) { ++tot;
        while (stk.top() != u) {
            int t = stk.top(); stk.pop();
            bel[t] = tot, instk[t] = 0, ++siz[tot];
        }
        int t = stk.top(); stk.pop();
        bel[t] = tot, instk[t] = 0, ++siz[tot];
    }
}
int deg[N], vis[N], vis2[N], f[N], g[N];
pair<int, int> edge[N * 3];
signed main() {
    // freopen("count.in", "r", stdin);
    // freopen("count.out", "w", stdout);
    // freopen("debug.err", "w", stderr);
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    srand(time(0));
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].emplace_back(b);
        edge[i] = {a, b};
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) dfs(i);
    for (int i = 1; i <= n; ++i) adj[i].clear();
    // for (int i = 1; i <= n; ++i) bel[i] = i;
    for (int i = 0; i < m; ++i) {
        auto &[a, b] = edge[i];
        if (bel[a] != bel[b]) adj[bel[a]].emplace_back(bel[b]), ++deg[bel[b]];
    }
    queue<int> q;
    for (int i = 1; i <= tot; ++i)
        if (!deg[i]) q.emplace(i), f[i] = siz[i];
    int cnt = n;
    while (q.size()) {
        int t = q.front();
        q.pop();
        if (q.empty()) vis[t] = 1;
        f[t] = cnt;
        cnt -= siz[t];
        for (int &g : adj[t])
            if (!--deg[g]) q.emplace(g);
    }
    for (int i = 1; i <= n; ++i) adj[i].clear(), deg[i] = 0;
    for (int i = 0; i < m; ++i) {
        auto &[a, b] = edge[i];
        if (bel[a] != bel[b]) adj[bel[b]].emplace_back(bel[a]), ++deg[bel[a]];
    }
    for (int i = 1; i <= tot; ++i)
        if (!deg[i]) q.emplace(i), g[i] = siz[i];
    cnt = n;
    while (q.size()) {
        int t = q.front();
        q.pop();
        if (q.empty()) vis2[t] = 1;
        g[t] = cnt;
        cnt -= siz[t];
        for (int &g : adj[t])
            if (!--deg[g]) q.emplace(g);
    }
    for (int i = 1; i <= tot; ++i)
        if (vis[i] && vis2[i] && f[i] + g[i] - siz[i] == n) cnt += siz[i];
    cout << cnt << '\n';
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

很好的 tarjan 练习题，但是我怎么又没有场切啊，我好菜 qwq。

首先暴力就是 dfs 枚举一个点能到达的点，然后建一遍反图再枚举一遍，最后看两次 dfs 能到达的点个数之和是否为 $n+1$，复杂度 $O(nm)$，期望得分 $30$。

观察数据范围后的提示：对于奇数编号测试点，保证给定的图没有**不同点数 $>1$ 的环**，容易想到缩点，变成一个 DAG 后处理。然后对每个点开一个 bitset，第 $i$ 位表示这个点能不能到达点 $i$。然后在缩点后的 DAG 上跑一遍拓扑排序，转移时把两个点的 bitset 按位或一下，拓扑排序后 bitset 中 $1$ 的个数就是该点能到达的点的个数，复杂度为 $O(\frac{nm}{w})$，期望得分 $60$。当然我赛时就是卡在了这里，只获得了 $60pts$。

发现如果一条路径上有分岔，那么这两条岔路上的点自然不可能互相到达。因此如果同时有两个入度为 $0$ 的点，那么这两个点不能互相到达。所以先拓扑排序一次得到每个点的拓扑序，然后按照拓扑序从大到小加边，每次加边更新一下其他点的入度情况和当前入度为 $0$ 的点的个数。如果入度为 $0$ 的点超过一个，则该点不能到达比他拓扑序大的所有点。然后再从小到大操作一次，得到比该点拓扑序小的所有点是否能到达该点，最后统计答案即可。

```cpp
//前面缩点部分省略，f[i]表示i属于的强连通分量编号
for(int i=1;i<=n;i++) for(int j:v[i]) if(f[i]!=f[j]) in[f[j]]++,G[f[i]].push_back(f[j]);
for(int i=1;i<=SCC;i++) if(!in[i]) q.push(i);
memset(dfn,0,sizeof(dfn));
cnt=0;
while(!q.empty())//预处理每个点的拓扑序
{
  int x=q.front();
  dfn[++cnt]=x;//dfn[i]表示拓扑序为i的点的编号
  q.pop();
  for(int y:G[x])
  {
    in[y]--;
    if(in[y]==0) q.push(y);
  }
}
sum=0;
memset(in,0,sizeof(in));
for(int i=SCC;i>=1;i--)
{
  //加入点dfn[i]
  for(int now:G[dfn[i]])//枚举该点能到达的点，更新入度
  {
    if(in[now]==0) sum--;
    in[now]++;
  }
  sum++;
  if(sum==1) vis1[dfn[i]]=1;
}
sum=0;
memset(in,0,sizeof(in));
for(int i=1;i<=SCC;i++) G[i].clear();
for(int i=1;i<=n;i++) for(int j:v[i]) if(f[i]!=f[j]) G[f[j]].push_back(f[i]);
//建反图再跑一遍
for(int i=1;i<=SCC;i++)
{
  for(int now:G[dfn[i]])
  {
    if(in[now]==0) sum--;
    in[now]++;
  }
  sum++;
  if(sum==1) vis2[dfn[i]]=1;
}
for(int i=1;i<=SCC;i++) if(vis1[i]&&vis2[i]) ans+=sz[i];
cout<<ans;
```

---

## 作者：dyc2022 (赞：1)

首先，我们可以将 SCC 先缩起来。原因是一个连通分量内部的点一定可以互相到达。

于是我们考虑在缩点结束的 DAG 上进行操作。一个点可以被拓扑序小于它的所有点到达，显然当且仅当这个点被加入队列后，有且仅有那个点的入度 $=0$。而由于拓扑排序的序列存的是入度等于 $0$ 的点，因此一个点满足条件当且仅当这个点加入队列后队列中只有一个元素。

考虑使用 kosaraju 求 SCC，我们会发现正图反图上两遍 dfs 完了之后，我们得到的 SCC 顺序恰好就是我们的拓扑序。因此我们只需要对于每一个点，枚举邻居进行转移出入队即可。

复杂度 $O(n+m)$，有一点常数，可以通过。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define N 1000006
using namespace std;
int n,m,dfn[N],vis[N],sccno[N],cnt,scc,in[N],siz[N],qsiz,ok[N];
vector<int> G[N],Gr[N];
struct Edge{int u,v;}E[N<<2];
inline int read()
{
    register int ret=0,bas=1;register char ch=getchar_unlocked();
    while(!isdigit(ch)&&ch!='-')ch=getchar_unlocked();
    while(isdigit(ch))ret=(ret<<3)+(ret<<1)+(ch^48),ch=getchar_unlocked();
    return bas*ret;
}
inline void print(int k)
{
    register int nnum[20],tp=0;
    while(k)nnum[++tp]=k%10,k/=10;
    if(!tp)nnum[++tp]=0;
    for(register int i=tp;i;i--)putchar(nnum[i]^48);
}
void dfs1(int u)
{
	vis[u]=1;
	for(int v:G[u])
		if(!vis[v])dfs1(v);
	dfn[++cnt]=u;
}
void dfs2(int u)
{
	sccno[u]=scc,siz[scc]++;
	for(int v:Gr[u])
		if(!sccno[v])dfs2(v);
}
void getscc()
{
	for(int i=1;i<=n;i++)
		if(!vis[i])dfs1(i);
	for(int i=n;i>=1;i--)
		if(!sccno[dfn[i]])scc++,dfs2(dfn[i]);
}
main()
{
	n=read(),m=read();
	for(int i=1,u,v;i<=m;i++)
	{
		u=read(),v=read();
		G[u].push_back(v),Gr[v].push_back(u);
		E[i]={u,v};
	}
	getscc();
	for(int i=1;i<=n;i++)G[i].clear(),Gr[i].clear();
	for(int i=1;i<=m;i++)
	{
		int su=sccno[E[i].u],sv=sccno[E[i].v];
		if(su==sv)continue;
		G[su].push_back(sv),Gr[sv].push_back(su);
	}
	for(int i=scc;i>=1;i--)
	{
		qsiz++;
		for(int v:G[i])if(v>i)
		{
			if(!in[v])qsiz--;
			in[v]++;
		}
		if(qsiz>1)ok[i]=1;
	}
	qsiz=0;
	for(int i=1;i<=scc;i++)in[i]=0;
	for(int i=1;i<=scc;i++)
	{
		qsiz++;
		for(int v:Gr[i])if(v<i)
		{
			if(!in[v])qsiz--;
			in[v]++;
		}
		if(qsiz>1)ok[i]=1;
	}
	int ans=0;
	for(int i=1;i<=scc;i++)ans+=(ok[i]^1)*siz[i];
	print(ans);
	return 0;
}
```

---

## 作者：xiazha (赞：1)

好题，考虑缩点后变成一个有向无环图，那么一个点若满足题目要求，则在拓扑序中，拓扑序比他小的点皆可到他，同时他可到所有拓扑序比他大的点。

考虑如何判断后者，你会发现当你按拓扑序从大到小依次加点时，若当前新加的点能到所有拓扑序比他大的点，当且仅当目前的图中只有他一个点入度为 $0$，若有多个，那么他走不到其他入度为 $0$ 的点。

而对于另一个条件的判断，考虑建反图，按照拓扑序小到大模仿刚才的操作搞一遍就行了。

这里代码有个可以简化的小细节，就是当你 ```tarjan``` 缩点后其实就是个逆拓扑序了，不用再跑一遍拓扑排序直接循环加点即可。

~~要是还有不理解的地方看看代码吧。~~


```
#include<bits/stdc++.h>
using namespace std;
int n,m,dfn[1000001],low[1000001],st[1000001],cnt,tot,top,vis[1000001],num[1000001],scc[1000001],ind1[1000001],ind2[1000001],vv[1000001],ans,h[1000001];
vector<int> g[1000001],g1[1000001],g2[1000001];
inline int read()
{
	int res=0;char c=getchar(),f=1;
	while(c<48||c>57){if(c=='-')f=0;c=getchar();}
	while(c>=48&&c<=57)res=(res<<3)+(res<<1)+(c&15),c=getchar();
	return f?res:-res;
}
void tarjan(int x)
{
	dfn[x]=low[x]=++tot;st[++top]=x;vis[x]=1;
	for(int y:g[x])
		if(!dfn[y]) tarjan(y),low[x]=min(low[x],low[y]);
		else if(vis[y]) low[x]=min(low[x],dfn[y]);
	if(low[x]==dfn[x])
	{
		int y=0;cnt++;
		do
		{
			y=st[top--];
			scc[y]=cnt;num[cnt]++;vis[y]=0;
		}while(y!=x);
	}
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;u=read();v=read();
		g[u].push_back(v);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	for(int x=1;x<=n;x++)
		for(int y:g[x])
			if(scc[x]!=scc[y]&&h[y]!=x)
				g1[scc[x]].push_back(scc[y]),g2[scc[y]].push_back(scc[x]),h[y]=x;
	int now=0;
	for(int x=1;x<=cnt;x++)
	{
		now++;
		for(int y:g1[x])
			if(y<x)
			{
				if(ind1[y]==0) now--;
				ind1[y]++;
			}
		if(now>=2) vv[x]++;
	}
	now=0;
	for(int x=cnt;x>=1;x--)
	{
		now++;
		for(int y:g2[x])
			if(y>x)
			{
				if(ind2[y]==0) now--;
				ind2[y]++;
			}
		if(now>=2) vv[x]++;
	}
	for(int i=1;i<=cnt;i++)
		if(!vv[i]) ans+=num[i];
	cout<<ans;
	return 0;
}

```

---

