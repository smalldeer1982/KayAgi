# 「dWoi R2」Change / 改造

## 题目背景

入间改造对人类生存繁殖有帮助的工具（~~就是性能工具，具体可以去看看弹丸论破 V3 自由时间与入间美兔的交谈，在这里不方便说吧，毕竟是 青 少 年 编 程 网 站~~）玩腻了，她发现了有一个很 符 合 她 胃 口 的东西，叫做 Galgame，于是她开始打一款叫做 Little Busters 的 Galgame，然后沉迷上了沙耶线最后的场景。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/vxy5rh6c.png)


## 题目描述

在经过 $99$ 次的 Replay 后，沙耶终于发现迷宫是一个有向无环图。为了保证最后一次 Replay 的趣味性，时风瞬给沙耶和理树安排了一个小游戏。

这张有向无环图 $G$ 有 $n$ 个点，$m$ 条边，每条边的长度为 $1$。设 $l_i$ 为初始点 $s$ 到第 $i$ 条边所指向的点 $u$ 的最短路，定义第 $i$ 条边的边权为 $p-l_i$。游戏步骤是这样的（所有选择都是按如下顺序进行，并且每个人的选择都是公开的）。

1. 理树站在点 $s$ 上。  
2. 时风瞬会随机选取一个点作为 $t$（$t$ 可以等于 $s$）。
3. 如果无法从 $s$ 到达 $t$，游戏直接结束。
3. 沙耶需要选择一条边。
4. 理树需要找到一条从 $s$ 到 $t$ 的路径。
5. 若沙耶选择的边在理树所选择的路径上，则理树就会将这条边的边权的钱给沙耶。

理树希望能少输钱，沙耶希望能多拿钱。若两方都采取最优策略，请问沙耶期望能得到多少钱。

## 说明/提示

#### 样例 1 解释

比如 $t=6$ 时，沙耶应该选择连接 $5,6$ 的那条边；$t=8$ 时，沙耶仍然应该选择连接 $5,6$ 的那条边；$t=4$ 时，应该选择连接 $1,4$ 的那条边；$t=5$ 时，沙耶无论选择什么边都不会得到钱。

设 $res_u$ 表示 $t=u$ 时沙耶能获得的最大收益，我们有 $res=\{0,9,9,9,0,7,7,7\}$。

#### 样例 2 解释

设 $res_u$ 表示 $t=u$ 时沙耶能获得的最大收益，我们有 $res=\{0,2,2\}$。

---

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$n,m \le 5$；
- Subtask 2（20 pts）：$m=n-1$，$u_i<v_i$，$s=1$；
- Subtask 3（30 pts）：$n,m \le 10^3$；
- Subtask 4（40 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,m \le 5 \times 10^6$，$1 \le s \le n$，$1 \le u_i,v_i \le n$，$u_i \ne v_i$，$n\le p \le 10^9$。

## 样例 #1

### 输入

```
8 8 1 10
1 2
1 3
1 4
2 5
3 5
5 6
6 7
6 8```

### 输出

```
6```

## 样例 #2

### 输入

```
3 2 1 3
1 2
1 3```

### 输出

```
332748119```

# 题解

## 作者：lgswdn_SA (赞：3)

\王队/\王队/\王队/ 


## Change 官方题解

一个微不足道的贪心：选尽可能靠前的边永远是最好的。题解中我们称对于点 $u$，那么设删掉它能让 $s$ 无法到达 $u$ 的边为支配边。

考虑求出 DAG 上的支配树（空间为 $n\log n$）。我们发现所有能支配一个点的边必然是支配树上的自己或者祖先中所有入度为 $1$ 的点的入边，于是树形 DP 一下即可。可以过 $60$ 分。

实际上并不需要用 $O(m\log )$ 建支配树。我们在拓扑排序的时候，考虑维护四个东西：$t_e$ 表示距离 $e$ 最远的支配边（没有即 0），$g_u$ 表示距离 $u$ 最远的支配边（没有即 0）。

考虑对于 $e=u\to v$，我们做如下转移：

- 若 $g_u=0$，那么将 $t_e$ 设为 $e$；否则 $t_e$ 设为 $g_u$（如果 $u$ 不存在支配边那么必然有选的边不能是 $u$ 之前的边）。
- 若 $g_v$ 还未被设置，则设 $g_v=t_e$；若 $g_v$ 已经被设置且和 $t_e$ 一样，则存在 $t_e$ 作为 $v$ 的支配边；否则就存在两条到达 $v$ 的路径，不存在支配边。

注意一开始的时候要删掉那些 $s$ 无法到达的点，否则无法进行拓扑排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);>=(b);i--)
const int N=6e6+9,mod=998244353;
typedef pair<int,int> pii;

inline long long read() {
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)) {if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9') {x=x*10+c-48; c=getchar();}
	return x*f;
}

struct edge {int to,nxt;} e[N]; int hd[N],tot=1;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]};hd[u]=tot;}

int n,m,s,p,deg[N],out[N],t[N],g[N],d[N],f[N],res[N];
long long ans;
bool in[N],vst[N];
stack<int>st;

long long ksm(long long x,int y,long long ret=1) {
	while(y) {
		if(y%2) ret=ret*x%mod;
		x=x*x%mod, y>>=1;
	} return ret;
}

void topo() {
	queue<int>q; q.push(s);
	memset(g,-1,sizeof(g)); g[s]=0;
	memset(f,0x3f,sizeof(f)); f[s]=0;
	while(!q.empty()) {
		int u=q.front(); q.pop();
		for(int i=hd[u];i;i=e[i].nxt) {
			int v=e[i].to;
			f[v]=min(f[v],f[u]+1);
			d[i]=f[v];
			if(g[u]==0) t[i]=i;
			else t[i]=g[u];
			if(g[v]==-1) g[v]=t[i];
			else if(g[v]!=t[i]) g[v]=0, res[v]=0, t[i]=0;
			if(t[i]) res[v]=p-d[t[i]];
			if((--deg[v])==0) q.push(v);
		}
	}
}

void cfs(int u) {
	vst[u]=1;
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if(!vst[v=e[i].to]) cfs(v=e[i].to);
	}
}

int main() {
	n=read(), m=read(), s=read(), p=read();
	rep(i,1,m) {
		int u=read(), v=read();
		add(u,v);
	}
	cfs(s);
	rep(u,1,n) if(vst[u]) {
		for(int i=hd[u];i;i=e[i].nxt) deg[e[i].to]++;
	}
	topo();
	int kk=ksm(n,mod-2);
	rep(i,1,n) ans=(ans+1ll*kk*res[i])%mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：2)

By lgswdn。

一个微不足道的贪心：选尽可能靠前的边永远是最好的。题解中我们称对于点 $u$，那么设删掉它能让 $s$ 无法到达 $u$ 的边为支配边。

**Subtask1** $n\le 5$。

想咋搞咋搞。

**Subtask2** $m=n-1$ 且 $u>v$ 且 $s=1$。

输出 0 即可，十分送分！

**Subtask3** $n\le 10^5$。

考虑求出 DAG 上的支配树（空间为 $n\log n$）。我们发现所有能支配一个点的边必然是支配树上的自己或者祖先中所有入度为 $1$ 的点的入边，于是树形 DP 一下即可。

**Subtak4** $n\le 5\times 10^6$。

实际上并不需要用 $O(m\log )$ 建支配树。我们在拓扑排序的时候，考虑维护四个东西：$t_e$ 表示距离 $e$ 最远的支配边（没有即 0），$g_u$ 表示距离 $u$ 最远的支配边（没有即 0）。

考虑对于 $e=u\to v$，我们做如下转移：

- 若 $g_u=0$，那么将 $t_e$ 设为 $e$；否则 $t_e$ 设为 $g_u$（如果 $u$ 不存在支配边那么必然有选的边不能是 $u$ 之前的边）。
- 若 $g_v$ 还未被设置，则设 $g_v=t_e$；若 $g_v$ 已经被设置且和 $t_e$ 一样，则存在 $t_e$ 作为 $v$ 的支配边；否则就存在两条到达 $v$ 的路径，不存在支配边。

注意一开始的时候要删掉那些 $s$ 无法到达的点，否则无法进行拓扑排序。

#### Code

支配树 40pts（实际上只要改一改就能 60 pts）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
const int N=5e6+9,mod=998244353;

inline long long read() {
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)) {if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9') {x=x*10+c-48; c=getchar();}
	return x*f;
}

int n,m,s,p,res[N];
long long ans;
bool vst[N];
vector<int>e[N];

long long ksm(long long x,int y,long long ret=1) {
	while(y) {
		if(y%2) ret=ret*x%mod;
		x=x*x%mod, y>>=1;
	} return ret;
}

namespace dag_dominator_tree{
	int dep[N],deg[N],fa[N][25],f[N],g[N];
	vector<int>t[N];
	int lca(int u,int v) {
		if(dep[v]>dep[u]) swap(u,v);
		per(h,23,0) if(dep[fa[u][h]]>=dep[v]) u=fa[u][h];
		per(h,23,0) if(fa[u][h]!=fa[v][h]) u=fa[u][h], v=fa[v][h];
		return u==v?u:fa[u][0];

	}
	void topo() {
		queue<int>q; q.push(s); dep[s]=1;
		memset(f,0x3f,sizeof(f)); f[s]=0;
		rep(i,1,n) if(deg[i]==1) g[i]=1;
		while(!q.empty()) {
			int u=q.front(); q.pop();
			for(auto v:e[u]) {
				f[v]=min(f[v],f[u]+1);
				if(fa[v][0]) fa[v][0]=lca(fa[v][0],u);
				else fa[v][0]=u;
				if((--deg[v])==0) {
					rep(h,1,20) fa[v][h]=fa[fa[v][h-1]][h-1];
					dep[v]=dep[fa[v][0]]+1;
					t[fa[v][0]].push_back(v);
					q.push(v);
				}
			}
		}
	}
	void dfs(int u) {
		res[u]=max(res[u],g[u]*(p-f[u]));
		for(auto v:t[u]) {
			res[v]=max(res[v],res[u]);
			dfs(v);
		}
	}
}
using namespace dag_dominator_tree;

void cfs(int u) {
	vst[u]=1;
	for(auto v:e[u]) {
		if(!vst[v]) cfs(v);
	}
}

signed main() {
	//freopen("change.in","r",stdin);
	//freopen("changedp.out","w",stdout);
	n=read(), m=read(), s=read(), p=read();
	rep(i,1,m) {
		int u=read(), v=read();
		e[u].push_back(v);
	}
	cfs(s);
	rep(i,1,n) if(vst[i]) {
		for(auto v:e[i]) deg[v]++;
	}
	topo();
	dfs(s);
	rep(i,1,n) ans=(ans+ksm(n,mod-2)*res[i])%mod;
	printf("%lld\n",ans);
	return 0;
}
```

正解 100 pts

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);>=(b);i--)
const int N=6e6+9,mod=998244353;
typedef pair<int,int> pii;

inline long long read() {
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)) {if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9') {x=x*10+c-48; c=getchar();}
	return x*f;
}

struct edge {int to,nxt;} e[N]; int hd[N],tot=1;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]};hd[u]=tot;}

int n,m,s,p,deg[N],out[N],t[N],g[N],d[N],f[N],res[N];
long long ans;
bool in[N],vst[N];
stack<int>st;

long long ksm(long long x,int y,long long ret=1) {
	while(y) {
		if(y%2) ret=ret*x%mod;
		x=x*x%mod, y>>=1;
	} return ret;
}

void topo() {
	queue<int>q; q.push(s);
	memset(g,-1,sizeof(g)); g[s]=0;
	memset(f,0x3f,sizeof(f)); f[s]=0;
	while(!q.empty()) {
		int u=q.front(); q.pop();
		for(int i=hd[u];i;i=e[i].nxt) {
			int v=e[i].to;
			f[v]=min(f[v],f[u]+1);
			d[i]=f[v];
			if(g[u]==0) t[i]=i;
			else t[i]=g[u];
			if(g[v]==-1) g[v]=t[i];
			else if(g[v]!=t[i]) g[v]=0, res[v]=0, t[i]=0;
			if(t[i]) res[v]=p-d[t[i]];
			if((--deg[v])==0) q.push(v);
		}
	}
}

void cfs(int u) {
	vst[u]=1;
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if(!vst[v=e[i].to]) cfs(v=e[i].to);
	}
}

int main() {
	//freopen("change.in","r",stdin);
	//freopen("change.out","w",stdout);
	n=read(), m=read(), s=read(), p=read();
	rep(i,1,m) {
		int u=read(), v=read();
		add(u,v);
	}
	cfs(s);
	rep(u,1,n) if(vst[u]) {
		for(int i=hd[u];i;i=e[i].nxt) deg[e[i].to]++;
	}
	topo();
	int kk=ksm(n,mod-2);
	rep(i,1,n) ans=(ans+1ll*kk*res[i])%mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：HPXXZYY (赞：1)

$\color{blue}{\texttt{[Analysis]}}$

比较简单的思路。

首先是一个贪心，离起始点 $s$ 越近的边一定越优。

由于 $s$ 不一定可以到达所有的节点，所以我们可以先进行一次拓扑排序（或者 bfs，随便怎么叫），求出 $s$ 到它可以到达的每一个点的距离和 $s$ 出发可以达到哪些点。

不可以到达的点对答案没有任何贡献，所以把所有不可以到达的节点和它的所有相连的边删去，留下所有可以到达的节点，建立一个新的图（这个图一定是原图的子图）。

结合贪心，现在的问题就是求出新图中从 $s$ 到达特定节点 $u$ 的所有路径中必须经过的离 $s$ 最近的那条边（即从 $s$ 到达节点 $u$ 的所有路径的交集中离 $s$ 距离最小的边），记为点 $u$ 的**最近必经之路**。

记 $\text{Limit}_{u}$ 表示 $u$ 的最近必经之路，考虑节点 $u$ 的所有入边 $(a_{i},u)$

1. 如果点 $u$ 的入度为 $1$。考虑 $\text{Limit}_{a}$，如果它不存在（即 $a$ 没有最近必经之路），那么 $\text{Limit}_{u}=(a,u)$，即这条边就是 $u$ 的最近必经之路。
2. 如果点 $u$ 的入度不为 $1$。如果所有 $\text{Limit}_{a_{i}}$ 都相等，那么点 $u$ 有最近必经之路，否则没有（想一想，为什么）。

所以，再来一次拓扑排序即可。

$\color{blue}{\texttt{[code]}}$

干讲可能不好理解，加上代码后就好多了。

```cpp
//不开 O2 会 T(因为 STL 用太多了)

const int N=5e6+100;
const int mod=998244353;

struct edge{
	int next,to;
}e[N];int h[N],te;
inline void add(int u,int v){
	e[++te]=(edge){h[u],v};h[u]=te;
}

bool Connected[N];
int n,m,s,p,ans,dis[N],ind[N];

inline void bfs(){
	queue<int> q;
	Connected[s]=true;
	memset(dis,127,sizeof(dis));
	dis[s]=0;
	
	for(int i=1;i<=n;i++)
		if (!ind[i]) q.push(i);
	
	while (!q.empty()){
		int u=q.front();q.pop();
		for(int i=h[u];i;i=e[i].next){
			register int v=e[i].to;
			dis[v]=min(dis[v],dis[u]+1);
			if ((--ind[v])==0) q.push(v);
			if (Connected[u]) Connected[v]=true;
		}
	}
}//第一次拓扑，求距离和可达点

vector<int> Graph[N];

inline void Select(){
	for(int u=1;u<=n;u++)
		for(int i=h[u];i;i=e[i].next){
			register int v=e[i].to;
			if (Connected[u]&&Connected[v])
				Graph[u].push_back(v);
		}
	
	memset(ind,0,sizeof(ind));
	memset(h,0,sizeof(h));te=0;
	memset(e,0,sizeof(e));//记得清空原图
	for(int u=1;u<=n;u++) if (Connected[u])
		for(int i=0;i<(int)Graph[u].size();i++){
			add(u,Graph[u][i]);
			++ind[Graph[u][i]];
		}
}//可达点建立新图

int Limit[N];//必经之路 

inline void BFS(){
	queue<int> q;q.push(s);
	memset(Limit,-1,sizeof(Limit));
	
	while (!q.empty()){
		int u=q.front();q.pop();
		for(int i=h[u];i;i=e[i].next){
			register int v=e[i].to;
			if (Limit[v]==-1) Limit[v]=(Limit[u]>0?Limit[u]:i);
			else if (Limit[u]!=Limit[v]) Limit[v]=-2;//无必经之路
			if ((--ind[v])==0) q.push(v);
		}
	}
}//求必经之路

int main(){
	n=read();m=read();
	s=read();p=read();
	
	for(int i=1,u,v;i<=m;i++){
		u=read();v=read();
		add(u,v);++ind[v];
	}//别忘了求原图里的入度
	
	bfs();
	Select();
	BFS();
	
	for(int i=1;i<=n;i++)
		if (Connected[i]&&Limit[i]>0)
			ans=(ans+p-dis[e[Limit[i]].to])%mod;
	
	printf("%lld",1ll*ans*ksm(n,mod-2)%mod);
	
	return 0;
}//ksm:快速幂;read:快读
```

---

## 作者：bh1234666 (赞：1)

题意 : 给一个  DAG  ,求起点到任意点的第一条必经之路

可以发现,当一个点入度为  1  时其入边必定是一条必经之路,入度不为  1  时入边必定不是必经之路

考虑入度不为  1  的点,当其所有入边都有同样一条必经之路时该必经之路也是这个点的必经之路

因此,若起点到某个点有必经之路,则这个点的所有入边的最早必经之路必定相等

因此我们可以进行一遍  bfs  ,维护所有点的最早的必经之路

根据  bfs  的性质,先更新的点的必经之路必定比后更新的点的必经之路更靠近出发点或者距离相同

因此若入度为  1  当当前节点之前的节点有必经之路则将当前节点的最早必经之路更新为之前一个节点的最早必经之路

若之前节点没有必经之路,则该点的入边为该点到起点的最早必经之路

否则判断当前节点入边的最早必经之路是否相等,相等则可以更新,否则说明该点没有必经之路

由于某些边不能由起点到达,因此不能直接使用原图

```cpp
#include<cstdio>
#include<set>
#define mod 998244353
using namespace std;
inline int read() {
	int x=0,f=1; char c=getchar();
	while(c<33||c=='-') {if(c=='-') f=-1; c=getchar();}
	while(c>=33) {x=x*10+c-48; c=getchar();}
	return x*f;
}
struct node{
	int n;
	node* next;
};
node* mp1[5000005];
node use1[5000005];
node* nw1=use1;
void add1(int u,int v)
{
	node* a=nw1++;
	a->n=v;
	a->next=mp1[u];
	mp1[u]=a;
}
node* mp2[5000005];
node use2[5000005];
node* nw2=use2;
void add2(int u,int v)
{
	node* a=nw2++;
	a->n=v;
	a->next=mp2[u];
	mp2[u]=a;
}
int in[5000005],out[5000005];
int qu[5000005],qf,ql;
int dis[5000005];
node* get[5000005];
int cnt[5000005];
int flag[5000005];
bool flag2[5000005];
int min(int x,int y)
{
	if(x>y) return y;
	else return x;
}
inline int inv(int n,int m=mod-2)
{
	if(m==0) return 1;
	int flag=inv(n,m>>1);
	if(m&1) return ((1ll*flag*flag)%mod*n)%mod;
	else return (1ll*flag*flag)%mod;
}
int main()
{
	int i,j;
	int n,m,s,p;
	long long ans=0;
	scanf("%d%d%d%d",&n,&m,&s,&p);
	for(i=1;i<=m;i++)
	{
		int u=read(),v=read();
		add1(u,v);
	}
	for(i=1;i<=n;i++)
		dis[i]=1000000000;
	dis[s]=0;
	qu[ql++]=s;
	while(qf<ql)
	{
		int fl=qu[qf];qf++;
		node* a=mp1[fl];
		while(a)
		{
			if(!flag2[a->n])
			{
				qu[ql++]=a->n;
				flag2[a->n]=1;
			}
			cnt[a->n]++;
			add2(a->n,fl);
			a=a->next;
		}
	}//预处理入度和入边(清理掉无法由起点到达的边)
	qf=ql=0;
	qu[ql++]=s;
	while(qf<ql)
	{
		int fl=qu[qf];qf++;
		node* a=mp1[fl];
		while(a)
		{
			dis[a->n]=min(dis[a->n],dis[fl]+1);//求起点到当前节点的距离
			flag[a->n]++;
			if(flag[a->n]==cnt[a->n])//如果该点所有入边都已经更新
			{
				if(cnt[a->n]==1)//入度为一
				{
					if(get[fl]) get[a->n]=get[fl];//如果前一个节点有最早必经之路则更新为前一个节点的必经之路
					else get[a->n]=a;//如果没有则更新为入边
				}
				else//入度不为一
				{
					node* b=mp2[a->n];
					node* flag=get[b->n];b=b->next;
					while(b)//查找所有入边
					{
						if(get[b->n]!=flag) break;//如果有入边的最早必经之路不同则该点无必经之路
						b=b->next;
					}
					if(!b) get[a->n]=flag;//所有入边最早必经之路相同则将该点的最早必经之路更新
				}
				qu[ql++]=a->n;
			}
			a=a->next;
		}
	}
	for(i=1;i<=n;i++) if(get[i]) ans=ans+p-dis[get[i]->n];ans%=mod;//计算答案
	printf("%d",ans*inv(n)%mod);
	return 0;
}
```


---

