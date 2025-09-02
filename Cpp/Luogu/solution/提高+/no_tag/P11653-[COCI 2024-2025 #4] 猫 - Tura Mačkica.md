# [COCI 2024/2025 #4] 猫 / Tura Mačkica

## 题目背景


译自 [COCI 2024/2025 #4](https://hsin.hr/coci/) T5。$\texttt{0.5s,0.5G}$。满分为 $120$。

猫是有很强的领土意识的动物。

## 题目描述


给定一张 $n$ 个节点，$(n+m)$ 条边的图。

其中 $n$ 条边是无向边，**保证只保留这 $n$ 条边时，图仍然连通。** 无向边**可能有重边自环**。

此外，还有 $m$ 条有向边，每条有向边上有一只猫。有向边**可能有重边**，但没有自环。

大家都喜欢撸猫。为此，你需要找到一条回路，使得这条回路经过每条有向边恰好一次。**每条边至多只能经过一次**。求出合法的回路的长度的最小值。

（注：从两个方向经过同一条无向边，算作经过两次，因此是不合法的。）

## 说明/提示


对于 $100\%$ 的数据，保证：

- $1\le n\le 2\times 10^4$；
- $0\le m\le 2\times 10^4$；  
- $1\le u_i,v_i,x_i,y_i\le n$；
- 只保留 $n$ 条无向边时，图是连通的；
- $x_i\neq y_i$。

| 子任务编号 | $n,m\le$ |  特殊性质 | 得分 |  
| :--: | :--: | :--: |:--: | 
| $ 1 $    | $20$ |  |   $ 11 $   |  
| $ 2 $    | $2\times 10^4$ | A |  $ 41 $   |  
| $ 3 $    | $2\times 10^4$ |   |  $ 68 $   |  

- 特殊性质 A：无向边中存在自环。




## 样例 #1

### 输入

```
5 1
3 1
3 2
3 4
3 5
2 4
3 5```

### 输出

```
2```

## 样例 #2

### 输入

```
6 7
3 2
5 3
1 4
6 1
5 6
4 2
4 5
1 2
4 2
2 6
3 1
1 6
6 4```

### 输出

```
10```

## 样例 #3

### 输入

```
7 3
4 1
4 3
6 4
2 6
5 2
5 7
4 4
3 6
4 1
7 5```

### 输出

```
-1```

# 题解

## 作者：irris (赞：5)

## 鲜花

所以为什么数据范围是 $n, m \leq 2\times 10^4$，明明可以做到 $\mathcal O(n + m)$ 啊？

## 题解

假如选出了一些无向边，并且钦定了它们的方向，这时，为了形成一条欧拉回路，边集合法当且仅当

- 边集是连通的；
- 每个点的入度等于出度。

对于 $m$ 条有向边，初始先让 $d_i = \sum\limits_{i \to v} 1 - \sum\limits_{v \to i} 1$（即出度减入度）。我们的目标是 $d_i = 0$。

考虑一棵树怎么做。注意到对于一片叶子 $u$，与它关联的边只有一条 $(u, v)$，而这条边的不被选择 / 被选择且定向 $u \to v$ / 被选择且定向 $v \to u$ 三种操作对 $d_u$ 的影响互不相同，于是这条边最终的状态可以确定（如果无论如何 $d_u$ 都不能为 $0$，则一定无解）。确定完这条边的状态即可删掉这条边，所以最后的过程形如拓扑排序，我们可以唯一确定选出的边集和每条边的方向，只需检验是否连通即可。

对于基环树，枚举环上一条边的状态即可转化为树。

## 参考实现

```cpp
using pii = std::pair<int, int>;
const int INF = 0x3f3f3f3f;

#define MAXN 20001
std::vector<int> g[MAXN];
int deg[MAXN], deg2[MAXN], vis[MAXN], d[MAXN];

int fa[MAXN], fa2[MAXN];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int solve(int n, std::vector<int> c, const std::vector<int> &r, int t = 0) {
	int ans = 0;
	for (int i = 1; i <= n; ++i) fa[i] = fa2[i];
	if (t) fa[find(c[0])] = find(c.back());
	for (int i = 1, n = c.size(); i < n; ++i) {
		if (std::abs(c[i - 1]) > 1) return INF;
		ans += std::abs(c[i - 1]), c[i] += c[i - 1];
		if (c[i - 1] != 0) fa[find(r[i])] = find(r[i - 1]);
		if (i == n - 1 && c[i] != 0) ans = INF; 
	}
	int con = -1;
	for (int i = 1; i <= n; ++i) if (d[i]) {
		if (con == -1) con = find(i);
		else if (find(i) != con) return INF;
	}
	return ans;
}
int main() {
	int n = read<int>(), m = read<int>(), res = m;
	for (int i = 1, u, v; i <= n; ++i) {
		u = read<int>(), v = read<int>();
		g[u].push_back(v), g[v].push_back(u);
		++deg[u], ++deg[v];
	}
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1, u, v; i <= m; ++i) {
		u = read<int>(), v = read<int>();
		++deg2[u], --deg2[v], fa[find(u)] = find(v), d[u] = d[v] = 1;
	}
	std::queue<int> q;
	for (int i = 1; i <= n; ++i) if (deg[i] == 1) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (std::abs(deg2[u]) > 1) return puts("-1"), 0;
		res += std::abs(deg2[u]), vis[u] = 1;
		for (int v : g[u]) if (!vis[v]) {
			deg2[v] += deg2[u];
			if (deg2[u] != 0) fa[find(u)] = find(v);
			if ((--deg[v]) == 1) q.push(v);
		}
	}
	for (int i = 1; i <= n; ++i) fa2[i] = fa[i];
	std::vector<int> cyc, r;
	for (int i = 1; i <= n; ++i) if (!vis[i]) {
		int u = i;
		while (!vis[u]) {
			cyc.push_back(u), vis[u] = 1;
			for (int v : g[u]) if (!vis[v]) 
				{ u = v; break; }
		}
		r = cyc;
		for (int &u : cyc) u = deg2[u];
		int k = cyc.size(), t = solve(n, cyc, r);
		cyc[0] += 1, cyc[k - 1] -= 1, t = std::min(t, solve(n, cyc, r, 1) + 1);
		cyc[0] -= 2, cyc[k - 1] += 2, t = std::min(t, solve(n, cyc, r, 1) + 1);
		if (t >= INF) res = -1; else res += t;
	}
	print<int>(res, '\n');
	return 0;
}
```

---

## 作者：Register_int (赞：2)

不妨先做 A 性质，即原图是棵树的情况。相当于我们要从无向边中选尽量少的边，使得构成的图有欧拉回路。考虑充要条件：

1. 每个点的入度等于出度。
2. 图连通。

先尝试满足第一个条件。先加 $m$ 条有向边记录每个点的入度减出度，之后直接从下往上确定每条从点到父亲的边的情况。显然每条边只有三种情况：向上、向下和不加入，必然只有最多一种是满足条件的。确定完后即可满足条件一，又由于方案唯一，判连通直接建图搜一遍就好。

考虑没有特殊性质的情况。此时原图是基环树，直接从环上拉下来一条边，枚举他是正向、反向还是不经过，三种情况取最小值。时间复杂度 $O(n+m)$。

---

## 作者：Purslane (赞：2)

# Solution

赛时一眼看出来：等价于给每条无向边 $(u,v)$ 定向，或者删去，使得原图是欧拉回路图。即所有点入度和出度相同，且连通。

发现这个很像无源汇上下界最小费用可行流！

将无向边拆成双向边，有向边强制流量为 $1$，费用都是 $1$。

发现这样一定可以使得所有点入度和出度相同，但是不一定连通。显然最终无向边不会两条双向边都被选，这样比都不选劣，但是效果相同。

如果你直接判连不连通，如果这组解不连通就输出 $-1$。

发现你过了树？唉这种算法看起来挺对。

很容易发现，对于一棵树，从叶子开始考虑每条边的方向，每条边方向唯一。所以如果有解一定会被我们找出来，只需要判断我们的解是否合法。（我被卡在了这一步 qwq）

为什么过不去图。因为基环树在环上边方向无法确定。

所以你随便找到一条环边暴力钦定其方向即可，这样转化为树。

跑的还挺快。

代码放在剪切板里（太难看了，因为贺的是之前的板子，那道题还是任意边权有源汇）：[link](https://www.luogu.com.cn/paste/tldal3gi)。

---

## 作者：huhangqi (赞：1)

首先我们可以发现最无脑的做法就是直接枚举所有无向边是不走，还是走，如果走那么是哪一个方向，然后这就是一个有向图，可以直接通过有向图欧拉路的性质来判断是否合法。

但是这样甚至可能最低的部分分都跑不过。

先考虑树的情况，我们已知知道了每条有向边的方向且这些边必须要走。

那么们从下到上递归遍历，发现在子树内的边已经全部确定时，这棵子树只能通过父亲节点使自己的出度或入度加上一或者不变。我们明显需要使子树内的出入度相等，可以设出为正一，入为负一，这样可以快速求出子树是需要出还是入，确定到父亲的边的方向。

确定了方向之后，我们需要再确定是否满足欧拉路的性质，先判断每个点的出入度是否相等，如果不相等，那么不成立。然后判断是否所有的边都连通，我是拿并查集直接实现的。

考虑变成基环树的情况，那么就是多加上了一条无向边，找到一个删掉以后会变成一个树的边，把这条边的三个方向枚举一遍，取一次最短的结果即可。

时间复杂度 $O(n+m)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,tmpu,tmpv,fa[20005],d[20005],f[20005],ans,du[20005];
int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
vector<int> e[20005],e2[20005],e3[20005];
bool dfs(int p,int fa2,int &res){
	f[p]=d[p];
	for(int i:e[p]){
		if(i==fa2)continue;
		if(dfs(i,p,res))return true;
		f[p]+=f[i];
	}
	for(int i:e3[p])fa[find(i)]=find(p);
	if(abs(f[p])>1)return true;
	if(f[p]==1)e2[fa2].push_back(p),res++,fa[find(fa2)]=find(p);
	if(f[p]==-1)e2[p].push_back(fa2),res++,fa[find(p)]=find(fa2);
	return false;
}
void solve(){
	int res=0;
	for(int i=1;i<=n;i++)for(int j:e3[i])e2[i].push_back(j);
	for(int i=1;i<=n;i++)fa[i]=i;
	if(dfs(1,0,res))return;
	memset(du,0,sizeof(du));
	for(int i=1;i<=n;i++)for(int j:e2[i])du[j]++;
	for(int i=1;i<=n;i++)if(du[i]!=e2[i].size())return;
	int tmp=0;
	for(int i=1;i<=n;i++)if(find(i)!=i){
		if(find(i)==tmp||!tmp)tmp=find(i);
		else return;
	}
	ans=min(ans,m+res);
}
signed main(){
	cin>>n>>m;
	if(!m){
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1,u,v;i<=n;i++){
		cin>>u>>v;
		if(find(u)!=find(v)){
			e[u].push_back(v),e[v].push_back(u);
			fa[find(u)]=find(v);
		}
		else tmpu=u,tmpv=v;
	}
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e3[u].push_back(v);
		d[u]++,d[v]--;
	}
	ans=1e18;
	solve();
	if(tmpu!=tmpv){
		m++;
		for(int i=1;i<=n;i++)e2[i].clear();
		e2[tmpu].push_back(tmpv);
		d[tmpu]++,d[tmpv]--;
		solve();
		for(int i=1;i<=n;i++)e2[i].clear();
		e2[tmpv].push_back(tmpu);
		d[tmpu]-=2,d[tmpv]+=2;
		solve();
	}
	if(ans==1e18)cout<<-1;
	else cout<<ans;
	return 0;
}

``````

---

## 作者：hnczy (赞：0)

这题很明显是一道图论题，无向图部分是一颗基环树。基环树很显然可以转化成树来写，部分分也是这样提醒我们的。在分析一下题目，需要我们构造一个欧拉回路，对于欧拉回路，可以用出度等于入度即出度减入度等于 0 这个性质，那我们先对于已有的边的起点 +1 ，终点 -1，那我们就需要把这整个图都变为值为零的点，而对于每一条边，都有三种情况，正向，不连，反向。又因为这是一个树，所以考虑从叶子开始，往上处理（类似一个拓扑排序），如果这个点的值大于零，就将这个点 -1，它的父亲 +1，即从父亲往下连一条边；小于零同理。如果等于 0 就不用连。当然欧拉回路也需要每个点都联通，这个直接用一个并查集维护即可，最后特判一下即可。

那基环树的情况直接分类讨论一条无向边是正向边还是反向边还是不经过即可。时间复杂度是 $O(n+m)$。

具体实现看代码吧，应该码风比较好。

```c++
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int N=2E4+5;
int n,m,A,B;
bool flag[N];
vector<int>e[N],point;
int ans=1e9,f[N],cnt,g[N],fa[N];
pii l[N];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	fa[x]=y;
}
void dfs(int u,int F){
	flag[u]=1;
	for(int v:e[u]){
		if(v==F)continue;
		dfs(v,u);
	}
	if(g[u]<0)g[u]++,g[F]--,cnt++,merge(u,F),point.push_back(u),point.push_back(F);
	else if(g[u]>0)g[u]--,g[F]++,cnt++,merge(u,F),point.push_back(u),point.push_back(F);
} 
void solve(int add){
	memset(flag,0,sizeof flag);
	point.clear();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)g[i]=f[i];
	cnt=0;
	for(int i=1;i<=n;i++)
		if(!flag[i])dfs(i,0);
	for(int i=1;i<=n;i++)
		if(g[i]!=0)cnt=1e9; 
	for(int i=1;i<=m;i++)
		merge(l[i].first,l[i].second);
	int FA=find(l[1].first);
	for(int i:point)
		if(find(i) != FA){
			cnt=1e9;break;
		}
	ans=min(ans,cnt+add);
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		if(u==v)continue;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	scanf("%d%d",&A,&B);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		f[u]--,f[v]++;
		l[i]={u,v};
	}
	solve(0);//这个不经过 
	f[A]--;f[B]++;
	solve(1);//A->B
	f[A]+=2,f[B]-=2;
	solve(1);//B->A 
	if(ans==1e9)puts("-1");
	else printf("%d",m+ans); 
	return 0;
}
```

---

