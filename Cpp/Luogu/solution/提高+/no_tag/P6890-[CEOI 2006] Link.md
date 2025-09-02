# [CEOI 2006] Link

## 题目描述

网站管理员 Kirk 正在重新组织他学校的网站。网站上有许多页面，内容很好，但他注意到页面之间的链接不够合理。事实上，每个页面都只包含一个链接，指向网站中的其他页面。这是一个糟糕的设计——从主页开始，访问者通常需要点击许多链接才能到达他感兴趣的页面，而且有些页面可能根本无法从主页访问。作为第一步，他想添加一些链接，以便每个页面都可以从主页快速访问。新链接可以添加在网站的任何地方。

网站包含 $N$ 个页面，用整数 1 到 $N$ 标记，主页标记为数字 1。

每个页面也有 $N$ 个链接；**每个页面都包含一个指向其他页面的链接**。对于整数 $K$，如果网站上的每个页面（除了主页）都可以通过**最多 $K$ 个链接**从主页访问，则称该网站是 **K-可达的**。

编写一个程序，给定网站的描述和整数 $K$，找出为了使网站 K-可达所需添加的**最少链接数**。

## 说明/提示

在第二组样例中，一个合法的路径集合 $\{1\to 7,1\to 14,14\to 10\}$。

$2 \leq N \leq 500 000$, $1 \leq K \leq 20 000$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
8 3
1 2
2 3
3 5
4 5
5 6
6 7
7 8
8 5```

### 输出

```
2```

## 样例 #2

### 输入

```
14 4
1 2
2 3
3 4
4 5
7 5
5 6
6 3
8 10
10 9
9 8
14 13
13 12
12 11
11 14```

### 输出

```
3```

# 题解

## 作者：Miraik (赞：8)

对于每棵内向基环树，我们首先不管环，把其他节点解决掉。

考虑一种贪心的想法：连叶子节点，然后将当前距离 $\le k$ 的点删掉，再继续连叶子节点，直至环外所有点都被删去。正确性比较显然，因为这样你自下而上拓展的速度最快。DFS 或 拓扑排序 都可以解决。

考虑环怎么办。刚才处理完了环外的点，因此现在 $1$ 号节点到环上每点的距离是已知的。不妨先利用每个点到 $1$ 号节点的距离在环上差分一下，可以求出那些与 $1$ 号节点距离大于 $k$ 的点，看作关键点。然后暴力扫描，枚举其中一个关键点作为起点，在环上不停向后覆盖，每覆盖一次都直接将指针向后移 $k$ 步，这样我们单次扫描的复杂度就是 $O(\frac{len}{k})$ 的了（$len$ 为环长）。

注意到我们只需要枚举前 $k$ 个关键点（至多前 $k$ 个为一段，那么以它们作为起点的情况已经包含了所有形态），因此对每个环我们这样做的复杂度就是 $O(\frac{len}{k} \times k)=O(len)$。

总时间复杂度 $O(n)$。有一点点细节，比如说 $1$ 号点在环外计算时的特殊处理。

```cpp
void tarjan(int u){ // tarjan 找环
	dfn[u]=low[u]=(++idx);
	stc[++top]=u; ins[u]=1;
	int v=to[u];
	if(!dfn[v]){
		tarjan(v);
		low[u]=min(low[u],low[v]);
	}
	else if(ins[v]) low[u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u]){
		if(stc[top]==u){
			ins[stc[top]]=0; top--;
			return;
		}
		t++;
		while(stc[top]^u)
			g[t].emplace_back(stc[top]),ins[stc[top]]=0,top--;
		g[t].emplace_back(stc[top]),ins[stc[top]]=0,top--;
	}
}
inline int nd(int x){ // x 节点是否被覆盖
	if(x>m) x-=m;
	return c[x]==0;
}
void solve(int x){
	m=g[x].size();
	for(int i=1;i<=m;i++) a[i]=g[x][m-i],c[i]=0; // 注意是 m-i，tarjan 找出来的环是反向的！！！调了好久
	for(int i=1;i<=m;i++){ // 在环上差分
		int tar=i+k-f[a[i]];
		if(tar<=m) c[i]++,c[tar+1]--;
		else c[i]++,c[1]++,c[tar-m+1]--;
	}
	for(int i=1;i<=m;i++) c[i]+=c[i-1];
	cnt=0;
	for(int i=1;i<=m;i++) if(nd(i)) b[++cnt]=i;
	cir=cnt;
	for(int i=1;i<=min(k,cnt);i++){
		int tt=0;
		for(int j=b[i];j<b[i]+m;j++)
			if(nd(j)) tt++,j+=k-1;
		cir=min(cir,tt);
	}
	ans+=cir;
}
main(){
	read(n); read(k);
	for(int i=1;i<=n;i++){
		int u,v; read(u); read(v);
		if(u==v){ to[u]=u; continue; }
		to[u]=v; deg[v]++;
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++) f[i]=k+1;
	for(int i=1;i<=n;i++)
		if(deg[i]==0 || i==1){ // 注意 i=1 的特殊处理
			if(i>1) f[i]=1,ans++;
			else f[i]=0;
			q.push(i);
		}
	while(!q.empty()){
		int u=q.front(); q.pop();
		if(f[u]>k) f[u]=1,ans++; // 距离 > k 且不在环上，给你连条边
		int v=to[u];
		if(v==1) continue;
		f[v]=min(f[v],f[u]+1);
		deg[v]--;
		if(!deg[v]) q.push(v);
	}
	for(int x=1;x<=t;x++) solve(x);
	print(ans);
}
```


---

## 作者：Azazеl (赞：5)

#### 题意
> $~~~~$ 给出内向基环树森林，求最少加多少条边使得 $1$ 到每个点的最短路均不超过 $k$

#### 题解

$~~~~$ 吐槽翻译题目的人，**内向基环树**都没翻出来。

$~~~~$ 显然 $1$ 连其他点是最优的，原因不必过多赘述。  

$~~~~$ 一次我们考虑一棵基环树，其他的树同理。我们先把环丢掉，叶子节点肯定是要连边的（没有给它连边的点，即本身不可达），顺次向上，我们就可以找到每次要连边的点。  

$~~~~$ 然后，对于环上所有不满足条件的点，我们单独提出来，枚举以哪个为起点，每次连向它（这里是假连，实际是跳过它后面的 $k-1$ 个点）后跳 $k$ 步，在跳 $k$ 步后的节点找到下一个不满足条件的点（可能是自己）。

$~~~~$ 发现这样的话枚举 $k$ 个点以上时就会造成重复（只是把某次情况起点改为后移 $k$ 步后的第一个点），因此枚举 $k$ 个点即可。

时间复杂度：$\mathcal{O(\dfrac{n}{k})\times k}=\mathcal{O(n)}$

#### 代码
```cpp
vector <int> G[1000005];//存反图，算距离
int n,k,To[1000005]/*每个点的出边连向的点*/,In[1000005]/*入度*/,dis[1000005],ans,cov[1000005],nxt[1000005]/*跳k步后的点*/;
bool On[1000005]/*是否在环上*/,vis[1000005]/*是否遍历过*/,isCov[1000005]/*是否已经覆盖该环上的点*/;
vector <int> cyc;//存每次的环
void dfs(int u)//倒着来求距离及给树上不满足的点加边
{
	vis[u]=true;
//	if(!In[u]){dis[u]=u!=1;ans+=u!=1;return;}
	dis[u]=1e9;
	for(int i=0;i<(int)G[u].size();i++)
	{
		int v=G[u][i];
		if(On[v]) continue;
		dfs(v);dis[u]=min(dis[u],dis[v]+1);
	}
	if(u==1) dis[u]=0;
	if(!On[u]&&dis[u]>k) dis[u]=1,ans++;
}
int main() {
//	freopen("1.in","r",stdin);
	scanf("%d %d",&n,&k);
	for(int i=1,x,y;i<=n;i++)
	{
		scanf("%d %d",&x,&y);To[x]=y;
		In[y]++;G[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			cyc.clear();int x=i;cyc.push_back(233);
			while(!vis[x]) vis[x]=true,x=To[x];//找环
			cyc.push_back(x);On[x]=true;
			int y=To[x];
			while(y!=x) cyc.push_back(y),On[y]=true,y=To[y];
			int cnt=cyc.size()-1;
			for(int j=1;j<=cnt;j++) dfs(cyc[j]),cov[j]=cov[j+cnt]=0;
			for(int j=1;j<=cnt;j++)//差分找每个点是否覆盖
			{
				if(dis[cyc[j]]<=k)
				{
					cov[j]++;
					if(j+k-dis[cyc[j]]<cnt<<1) cov[j+k-dis[cyc[j]]+1]--;
				}
			}
			for(int j=1;j<=cnt<<1;j++) cov[j]+=cov[j-1];
			for(int j=1;j<=cnt;j++)
			{
				if(cov[j]||cov[j+cnt]) isCov[j]=isCov[j+cnt]=1;
				else isCov[j]=isCov[j+cnt]=0;	
			}
			nxt[(cnt<<1)+1]=(cnt<<1)+1;
			for(int j=cnt<<1;j;j--)
			{
				if(isCov[j]) nxt[j]=nxt[j+1];
				else nxt[j]=j;	
			}
			int Searched=0,Minn=1e9;
			for(int j=1;j<=cnt;j++)//枚举换上的点
			{
				if(isCov[j]) continue;
				int Tmp=0;
				for(x=j;x<j+cnt;)
				{
					Tmp++,x+=k;
					if(x<cnt+j) x=nxt[x];
				}
				Minn=min(Minn,Tmp);
				if(++Searched==k) break;//枚举到k个直接停止
			}
			if(Minn<1e9) ans+=Minn;
		}
	}
	printf("%d",ans);
	return 0;
}
```

~~好久没在代码里写这么多注释了~~

---

## 作者：Leasier (赞：3)

显然原图是一个内向基环树森林，考虑一个一个连通块地讨论。

下面忽略连通块中有 $1$ 的情况。这个是容易在下面讨论的基础上加上去的。

对于树上的部分，显然我们一开始会把 $1$ 连向所有叶子，然后删掉现在跟 $1$ 距离 $\leq k$ 的点，再对新的叶子做上述处理，直到所有非环上的点都被删空。实现时可以考虑每次 bfs 更新 dis 数组。

对于环上的部分，一个直观的想法是把 $1$ 连向某个跟 $1$ 距离仍 $> k$ 的点，然后从这个点出发类似地删边，再找到下一个需要加边的点，直到环上的点都被删空。

但直接枚举从哪里开始删的时间复杂度是 $O(len^2)$ 的，显然不能通过。

注意到连续的至多 $k$ 个需要加边的点中至少有一个可以作为合法的开头，于是我们从第一个开始枚举 $k$ 个需要加边的点，而上述模拟一次的时间复杂度为 $O(\frac{len}{k})$，于是一个环的总时间复杂度为 $O(len)$，可以接受。

综上，时间复杂度为 $O(n)$。

代码：
```cpp
#include <iostream>
#include <queue>
#include <cstdio>

using namespace std;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 0, tm = 0;
int to[500007], head[500007], dis[500007], vis[500007], loop[500007], fa[500007], son_cnt[500007], nxt[1000007];
Edge edge[500007];
queue<int> q;

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs(int u, int father){
	fa[u] = father;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (vis[x] != tm){
			son_cnt[u]++;
			dfs(x, u);
		}
	}
	if (son_cnt[u] == 0) q.push(u);
}

void mark(int u){
	vis[u] = tm;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (fa[x] == u) mark(x);
	}
}

int main(){
	int n = read(), k = read(), ans = 0;
	for (int i = 1; i <= n; i++){
		int x = read(), y = read();
		to[x] = y;
		add_edge(y, x);
	}
	dis[1] = 0;
	for (int i = 2; i <= n; i++){
		dis[i] = 2e9;
	}
	for (int i = 1; i <= n; i++){
		if (vis[i] == 0){
			int u = i, cnt = 0, db;
			tm++;
			while (vis[u] != tm){
				vis[u] = tm;
				u = to[u];
			}
			tm++;
			while (vis[u] != tm){
				vis[u] = tm;
				loop[++cnt] = u;
				u = to[u];
			}
			db = cnt * 2;
			for (int j = 1; j <= cnt; j++){
				dfs(loop[j], 0);
			}
			while (!q.empty()){
				int cur = q.front();
				q.pop();
				for (int j = head[cur]; j != 0; j = edge[j].nxt){
					int x = edge[j].end;
					if (vis[x] != tm) dis[cur] = min(dis[cur], dis[x] + 1);
				}
				if (vis[cur] != tm){
					if (dis[cur] > k){
						dis[cur] = 1;
						ans++;
					}
					if (--son_cnt[to[cur]] == 0) q.push(to[cur]);
				}
			}
			for (int j = 1; j <= 2; j++){
				for (int x = 1; x <= cnt; x++){
					int t = x % cnt + 1;
					dis[loop[t]] = min(dis[loop[t]], dis[loop[x]] + 1);
				}
			}
			nxt[db + 1] = 0x7fffffff;
			for (int j = db; j >= 1; j--){
				nxt[j] = dis[loop[(j - 1) % cnt + 1]] > k ? j : nxt[j + 1];
			}
			if (nxt[1] != 0x7fffffff){
				int cur_ans = 0x7fffffff;
				for (int j = 1, x = 1; j <= cnt && x <= k; j++){
					if (dis[loop[j]] > k){
						int up2 = j + cnt - 1, val = 0;
						for (int y = j; y <= up2; ){
							if (nxt[y] > up2) break;
							y = nxt[y] + k;
							val++;
						}
						if (cur_ans > val) cur_ans = val;
						x++;
					}
				}
				ans += cur_ans;
			}
			tm++;
			for (int j = 1; j <= cnt; j++){
				mark(loop[j]);
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：BINYU (赞：2)

## 题意

有一棵大小为 $n$ 的内向基环树森林，求至少需要添加多少条边，才能使点 $1$ 到其他所有点的距离均不超过 $k$？

## 思路

看到森林，首先考虑一棵树，看到基环树，首先考虑树。

发现如果叶子结点不是 $1$ 那么 $1$ 必须要向这个节点连一条边，然后可以在树上把这个节点的父亲到第 $k-1$ 级祖先全部删除，我们可以用一个 $dis$ 数组来表示 $1$ 号节点到当前节点的距离，初始为 $inf$，特别的，$dis_1 = 0$。

使用拓扑排序向上更新，每次先判断 $u$ 合不合法，如果不合法，将 $dis_u$ 设为 $1$，并计入答案，传递时让 $dis_v = \min(dis_v,dis_u + 1)$ 即可。

可以发现，这部分在树上是最优的，在基环树除了环的部分同样适应，接下来考虑环。

对于环上的点，可以通过一个特定的点暴力的跳到它的儿子，进而找到整个环，同树上的情况，环上每个点的 $dis$ 也可以更新它后继的 $dis$，因为是环，所以我们从同一个点开始更新两次即可。

接下来就是环的套路了：断环成链，假如断环成链后的数组为 $a$，我们可以预处理一个数组 $nxt_i$ 表示在 $i$ 后面（包括 $i$）的第一个不合法的点。

我们暴力的去找到一个不合法的点 $st$，然后再从这个点开始跳，如果当前点为 $i$ 我们修改这个点，那么接下来 $k-1$ 个点就都合法了，直接跳到 $nxt_{i+k}$ 即可，直到跳过了 $st + len - 1$（$len$ 为环长），可以发现，这样跳每一个跳到的点都是这整个部分是 $O(len+\frac{len^2}{k})$ 的，需要优化（但似乎洛谷上到这里就已经过了？不管了，接着讲）。

发现有一些点的枚举是无用的，我们发现，第 $k$ 个不合法的点，它的位置一定在 $k$ 之后（这不是废话么），我们假设这个点是 $u$，可以发现，对于 $a_{u+len}$，一定需要一个下标比 $len$ 大的点（也可以是它本身）使它合法，所以，当我们枚举到 $u$ 之后的点，一定会有一个需要连边的点在 $len$ 之后，这与我们先前直接枚举这个点是重复的。而 $u$ 以前的点因为需要跳的区间不包含这个点而不被影响。

所以，我们实际上只需要枚举 $k$ 个不合法的点，就能得到答案。

最终时空复杂度 $O(n)$，可过。

---

## 作者：Handezheng (赞：0)

## 题解：P6890 [CEOI 2006] Link
[题目传送门](https://www.luogu.com.cn/problem/P6890)
### 题面
> 给定 $n$ 个点 $n$ 条有向边的**内向基环树（不保证连通）**，要求添加最少的有向边使得点 $1$ 到达所有其它点的最短路长度不超过 $K$。
### 思路
首先考虑到内向基环树就是带着一个环的 **DAG**，所以如果有某个点入度为 $0$，肯定要从 $1$ 向它连边。

先把不是环上的点处理好，令 $f_i$ 表示从 $i$ 点还能走多少步满足性质，能够得到转移方程 $f_v = \max{f_v,f_u-1}$，并且发现，若 $f_u=0$，一定要从 $1$ 向它连边，可用拓扑处理。

对于环上的点，我们可以先扩散一遍，得到的 $f_u$ 实质上就是从 $u$ 点能跳到哪个点；对于所有的 $f_u=0$，必须连边并统计贡献。设环上有 $L$ 个点，能够得到单次查询的时间复杂度为 $O(\frac L k)$。

正常情况下我们要以环上的每一个满足 $f_u=0$ 点为起点进行跳跃，时间复杂度 $O(\frac {L^2} k)$。但是我们注意到，在这些满足条件的点中，每 $k$ 个就成一次循环，它们的决策实质上是一样的，所以我们可以只进行 $k$ 次查询，时间复杂度为 $O(\frac {L^2} k \times k)=O(L)$。这样我们就以 $O(n)$ 的复杂度做完了本题。
### 注意事项
1. 题目中并未说明**保证图连通**，所以可能有多棵基环树，多个环，每个都要统计答案，注意处理。
2. 初始状态 $f_1=k+1$，不要忘记。
### 代码
```cpp
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#define int long long
#define F(i,l,r) for(int i=(l); i<=(r); i++)
using namespace std;
const int N = 1e6 + 50, INF=0x3f3f3f3f3f3f3f3f;

int n,K,cnt;
int ind[N], f[N];
int to[N];

inline void Topsort(){
	queue<int> q;
	F(i,1,n) if(!ind[i]){
		q.push(i);
		f[i] = K;
		cnt+=(i!=1);
	}
	f[1]=K+1;
	for(; q.size(); q.pop()){
		int u=q.front(), v=to[u];
		if(!f[u])cnt++, f[u]=K;
		f[v]=max(f[v],f[u]-1);
		ind[v]--;
		if(!ind[v]) q.push(v);
	}
}
inline int fun(int rt, int tot, int cir[]){
	int sum=0, res=0;
	for(int i=rt; sum<tot;){
		int u=cir[i];
		if(f[u]){
			sum+=f[u];
			i = (i+f[u]-1)%tot + 1;
		}else{
			res++;
			sum+=K;
			i = (i+K-1)%tot +1;
		}
	}
	return res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>K;
	F(i,1,n){
		int u,v; cin>>u>>v;
		to[u]=v;
		ind[v]++;
	}
	Topsort();
	F(i,1,n){
		if(ind[i]){
			vector<int> vec;
			
			for(int u=i,v; ind[u]; u=v){
				ind[u]=0;
				vec.push_back(u);
				v=to[u];
				f[v]=max(f[v],f[u]-1);
			}
			
			int cir[vec.size()+3]={0}, tot=0, Cnt=0, mi=INF;
			for(int e:vec) cir[++tot]=e;
			F(j,1,tot){
				if(f[cir[j]]) continue ;
				Cnt++;
				mi = min(mi, fun(j,tot,cir));
				if(Cnt==K) break;
			}
			cnt+=(mi==INF)?0:mi;
		}
	}
	cout<<cnt<<'\n';

	return 0;
}
```
另一种写法
```cpp
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#define int long long
#define F(i,l,r) for(int i=(l); i<=(r); i++)
using namespace std;
const int N = 1e6 + 50, INF=0x3f3f3f3f3f3f3f3f;

int n,K,cnt;
int ind[N], f[N];
int cir[N],tot;
int to[N];

inline void Topsort(){
	queue<int> q;
	F(i,1,n) if(!ind[i]){
		q.push(i);
		f[i] = K;
		cnt+=(i!=1);
	}
	f[1]=K+1;
	for(; q.size(); q.pop()){
		int u=q.front(), v=to[u];
		if(!f[u])cnt++, f[u]=K;
		f[v]=max(f[v],f[u]-1);
		ind[v]--;
		if(!ind[v]) q.push(v);
	}
}
inline int fun(int rt){
	int sum=0, res=0;
	for(int i=rt; sum<tot;){
		int u=cir[i];
		if(f[u]){
			sum+=f[u];
			i = (i+f[u]-1)%tot + 1;
		}else{
			res++;
			sum+=K;
			i = (i+K-1)%tot +1;
		}
	}
	return res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>K;
	F(i,1,n){
		int u,v; cin>>u>>v;
		to[u]=v;
		ind[v]++;
	}
	Topsort();
	F(i,1,n){
		if(ind[i]){
			tot=0;
			for(int u=i,v; ind[u]; u=v){
				ind[u]=0;
				cir[++tot]=u;
				v=to[u];
				f[v]=max(f[v],f[u]-1);
			}
			
			int Cnt=0, mi=INF;
			F(j,1,tot){
				if(f[cir[j]]) continue ;
				Cnt++;
				mi = min(mi, fun(j));
				if(Cnt==K) break;
			}
			cnt+=(mi==INF)?0:mi;
		}
	}
	cout<<cnt<<'\n';

	return 0;
}
```
完结撒花！

---

