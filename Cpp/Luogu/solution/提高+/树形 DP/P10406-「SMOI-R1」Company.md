# 「SMOI-R1」Company

## 题目背景

LAR 被老板炒了，下面都是他的梦。

## 题目描述

城市中有 $n$ 所公司，第 $i$ 所公司有 $m_i$ 个人。

一所公司可以用一棵**根为 $1$ 的**树来表示，**最初时**节点 $1$ 是老板，每个节点的子节点都是他的下属，每个节点的父节点都是他的上司。第 $i$ 棵树的大小为 $m_i$，节点从 $1$ 到 $m_i$ 编号。

公司很多，政府管理起来非常麻烦，所以政府想让 LAR 把这些公司合并起来。两所公司要合并起来，需要**一所**公司的一名**最初没有下属**的人（员工或**老板**）成为**另一所**公司现在的**老板的上司**。当两个公司合并完，两所公司就是**一所公司**了。

只有**互为上司和下属**的两个人才认识。

myz 是第 $1$ 棵树的节点 $x$，ljs 是第 $2$ 棵树的节点 $y$。因为 myz 和 ljs 性格十分不相符（他们不认识），所以 LAR 想让他们的**关系越远越好**。

互相认识的人距离为 $1$，**两人的关系**定义为两人的人际关系网上的最短距离（可以简单认为是最终形成的树中两点的最短距离）。例如，$1$ 认识 $2$，$2$ 认识 $3$，那么 $1$ 和 $3$ 的关系就是 $2$。

## 说明/提示

### 样例解释
在还没有进行合并操作时，城市中公司如下（括号中的数是节点**初始时**所在的公司）：
![](https://cdn.luogu.com.cn/upload/image_hosting/1g1uvci4.png)

想要让关系值最大，可以让最终的公司形成下图的样子：
![](https://cdn.luogu.com.cn/upload/image_hosting/cj518ep6.png)

答案为 $8$。
### 数据范围
**本题采用捆绑测试**。

subtask编号|$n\leq$|$\sum m \leq$|特殊情况|分值
-|-|-|-|-
$1$|$2$|$10^3$|无|$20$
$2$|$10^5$|$10^6$|$x = 1$，$y=1$|$20$
$3$|$10^5$|$10^6$|所有树都是随机树|$20$
$4$|$10^5$|$10^6$|无|$40$

**随机树产生规则**：对于节点 $i$ （$2 \le i \le m$）的上司从 $1$ 到 $i - 1$ 中**等概率**产生。

对于 $100\%$ 的数据，$2\leq n\leq 10^5$，$1 \le m_i$，$\sum m \leq 10^6$，$1\leq x\leq m_1$，$1\leq y\leq m_2$。

## 样例 #1

### 输入

```
3
3 1 1
3 1 2
4 1 2 1
2 3```

### 输出

```
8```

# 题解

## 作者：ran_qwq (赞：6)

首先，假设将一个公司看成一个“大点”，则连接最后的“大树”每个点度数最多为 $2$，否则可以将一棵子树接到另一棵子树上，这样更优。

这里有两种情况：一是一条链，二是两条链通过一个公司连接在一起。

对于第一种情况，又有最顶是 $1$ 号树、最底是 $2$ 号树，和最顶是 $2$ 号树、最底是 $1$ 号树两种子情况。对于第一种子情况，选离 $x$ 最远的节点，接上另外一棵子树的根节点，产生 $dis(x,l)$ 的贡献（$l$ 是选中的叶子节点）；$3\sim n$ 只要接的都是距离最远的叶子节点就可以随便接；而 $2$ 子树会产生 $dis(1,y)$ 的贡献；再加上自己加的 $n-1$ 条边使其相连。第二种子情况类似，取个最大值即可。

对于第二种情况，枚举“大树”的根 $r$，这样在 $r$ 中的贡献会减去最大深度，加上最大叶子节点距离（类似树的直径的求法）。贪心取两者之差最大的。与第一种情况类似，但是还要加上 $dis(1,x)+dis(1,y)$。

讲的有点抽象，放个丑陋的代码：

```cpp
int n,ans,mx1,mx2,mx3,x,y,d1[M],d2[M],mx[N],dmx[N]; vi G1[M],G2[M]; 
struct Tree {
	int m; vi dep,dep2; vector<vi> G;
	void dfs(int u,int fa=0) {for(int v:G[u]) if(v!=fa) dep[v]=dep[u]+1,dfs(v,u);}
	void rdfs(int u,int fa=0) {for(int v:G[u]) if(v!=fa) dep2[v]=dep2[u]+1,rdfs(v,u);}
}T[N];
void dfs1(int u,int fa=0) {for(int v:T[1].G[u]) if(v!=fa) {d1[v]=d1[u]+1; if(v!=1&&T[1].G[v].size()<=1) mx1=max(mx1,d1[v]); dfs1(v,u);}}
void dfs2(int u,int fa=0) {for(int v:T[2].G[u]) if(v!=fa) {d2[v]=d2[u]+1; if(v!=1&&T[2].G[v].size()<=1) mx2=max(mx2,d2[v]); dfs2(v,u);}}
void QwQ() {
	n=rd(),ans=n-1,mx3=-INF;
	for(int i=1;i<=n;i++) {
		T[i].m=rd(),T[i].G.resize(T[i].m+1),T[i].dep.resize(T[i].m+1),T[i].dep2.resize(T[i].m+1);
		for(int j=2,x;j<=T[i].m;j++) x=rd(),T[i].G[x].pb(j),T[i].G[j].pb(x);
	}
	x=rd(),y=rd(),dfs1(x),dfs2(y);
	for(int i=1,s;i<=n;i++) {
		T[i].dfs(1),s=-1;
		for(int j=2;j<=T[i].m;j++) if(T[i].dep[j]>=mx[i]&&T[i].G[j].size()==1) mx[i]=T[i].dep[j],s=j;
		if(i>2) ans+=mx[i];
		if(!~s) continue; T[i].rdfs(s);
		for(int j=2;j<=T[i].m;j++) if(T[i].G[j].size()==1) dmx[i]=max(dmx[i],T[i].dep2[j]);
	}
	for(int i=1;i<=n;i++) mx3=max(mx3,dmx[i]-mx[i]);
	wr(max(ans+max(d1[1]+mx2,d2[1]+mx1),mx3!=-INF?ans+mx3+d1[1]+d2[1]:0),"\n");
}
```

---

## 作者：larsr (赞：6)

## Part 1
对于 subtask 1。

因为只有两所公司，枚举最后的老板是哪所公司的，再枚举这个公司的哪个人成为另一所公司的上司。时间复杂度 $O(n)$。
## Part 2
为方便叙述，下文中**大公司**是最后合并后的公司，**公司是**初始时的公司。

通过贪心，我们可以想到最优的大公司如果用公司之间的关系表示，是呈现链的形态的，并且链的两头分别是 myz 和 ljs 所在的公司。
## Part 3
对于大公司的老板所在的公司，我们可以称之为**组公司**。

我们很容易想到，当链的形态固定时，组公司想让对答案的贡献最大，需要让他相连的两个公司，通过它的两个距离最远的叶节点连接。

不过当组公司是 myz 和 ljs 所在的树时就不一样了，它只需要连接一个公司，想要贡献最大，用距离 myz（或 ljs）最远的叶结点连接。
## Part 4
处理完组公司之后，就剩不是组公司的了。

如果这个公司是 myz（或 ljs）所在的树，对答案的贡献是 myz（或 ljs）到根的距离。

否则对答案的贡献是树的深度。
## Part 5
设 $a_i$ 是第 $i$ 所公司是组公司时对答案的最大贡献，$b_i$ 是第 $i$ 所公司不是是组公司时对答案的最大贡献。

答案为，
$$Ans = \max_{1\le i\le n}( a_i + \sum_{1 \le j \le n,j\neq i}b_j)$$

如果直接算，复杂度是 $O(n^2)$。但是我们可以转化为，
$$Ans = \max_{1\le i\le n}( a_i - b_i + \sum_{1 \le j \le n}b_j)$$
即，
$$Ans = \max_{1\le i\le n}( a_i - b_i) + \sum_{1 \le j \le n}b_j$$
时间复杂度 $O(n)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#define N 1000010
using namespace std;
int n, x, y, m[N], tot = 0, root[N];
int a[N], b[N];
int dea[N], lea[N], ds[N];
int ok = 0;
vector<int>e[N];
int dfs_d(int now, int fa, int d)
{
	int maxn = d;
	dea[now] = ds[now] = d;
	for(int i = 0; i < e[now].size(); i++)
	if(e[now][i] != fa)
	{
		if(ok)
		lea[now] = 1;
		maxn = max(maxn, dfs_d(e[now][i], now, d + 1));
		dea[now] = max(dea[now], dea[e[now][i]]);
	}
	return maxn;
}
int dfs_zh(int now, int fa, int d)
{
	int maxn = 0, max1 = 0, max2 = 0;
	for(int i = 0; i < e[now].size(); i++)
	if(e[now][i] != fa)
	{
		int to = e[now][i];
		maxn = max(maxn, dfs_zh(to, now, d + 1));
		if(dea[to] - d >= max1)max2 = max1, max1 = dea[to] - d;
		else if(dea[to] - d > max2)max2 = dea[to] - d;
	}
	if(max1 && max2) maxn = max(maxn, max1 + max2);
	return maxn;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", m + i);
		root[i] = tot + 1;
		for(int j = 2; j <= m[i]; j++)
		{
			int f;
			scanf("%d", &f);
			e[f + tot].push_back(j + tot);
			e[j + tot].push_back(f + tot);
		}
		tot += m[i];
	}
	scanf("%d%d", &x, &y);
	ok = 1;
	dfs_d(root[1], 0, 0);
	ok = 0;
	a[1] = ds[x] - ds[1];
	dfs_d(x, 0, 0);
	for(int i = 1; i <= m[1]; i++)
		if(!lea[i])
			b[1] = max(b[1], ds[i]);
	y += m[1];
	ok = 1;
	dfs_d(root[2], 0, 0);
	ok = 0;
	a[2] = ds[y] - ds[root[2]];
	dfs_d(y, 0, 0);
	for(int i = m[1] + 1; i <= m[1] + m[2]; i++)
		if(!lea[i])
			b[2] = max(b[2], ds[i]);
	for(int i = 3; i <= n; i++)
	{
		a[i] = dfs_d(root[i], 0, 0);
		b[i] = dfs_zh(root[i], 0, 0);
	}
	int ans = 0, maxn = -1e9;
	for(int i = 1; i <= n; i++) ans += a[i], maxn = max(maxn, b[i] - a[i]);
	printf("%d\n", ans + maxn + n - 1);
	return 0;
}
```

---

## 作者：cppcppcpp3 (赞：2)

[Link](https://www.luogu.com.cn/problem/P10406)

记第 $i$ 棵树为 $T_i$。最优情况下，$x$ 到 $y$ 的路径肯定经过了原来所有的树。考虑固定住 $T_1$，有几种较优的合并方式：

- 从 $T_1$ 不断往下接其它的树。

![unk](https://cdn.luogu.com.cn/upload/image_hosting/eh0x8zwc.png?x-oss-process=image/resize,m_lfit,h_350,w_400)

此时 $T_i(3\le i\le n)$ 接入根节点到最深的叶子这条路径最优。

记 $d_x,d_y$ 分别为 $x$ 到 $T_1$ 中离 $x$ 最远叶子的距离、$y$ 到 $T_2$ 中离 $y$ 最远叶子的距离；$dep_x,dep_y$ 分别为 $x$ 到 $T_1$ 根节点和 $y$ 到 $T_2$ 根节点的距离；$mxd_i$ 为 $T_i$ 中点的最大深度（根节点深度为 $0$）

这种情况的答案为 

$$d_x+dep_y+\sum_{i=3}^n mxd_i$$

- 从 $T_1$ 不断往上接其它的树。

![unk](https://cdn.luogu.com.cn/upload/image_hosting/uzn59dyz.png?x-oss-process=image/resize,m_lfit,h_350,w_400)

类似上一种情况，答案为 

$$d_y+dep_x+\sum_{i=3}^n mxd_i$$

- 从 $T_1$ 不断往上接，最上面的是 $T_p$，然后在 $T_p$ 另一个叶子下面接剩下的树。

![unk](https://cdn.luogu.com.cn/upload/image_hosting/fc0sdavd.png?x-oss-process=image/resize,m_lfit,h_300,w_400)

此时 $T_1,T_2$ 分别贡献了 $dep_x,dep_y$，$T_p$ 贡献了树上两两叶子距离的最大值（记作 $mxx_p$），剩下的树贡献的是 $mxd_i$，答案即

$$dep_x+dep_y+mxx_p+\sum_{i=3}^nmxd_i-mxd_p$$

上面涉及到的东西都可以几次 DFS 得到。最终答案在三者中取 $\max$。注意 $n$ 棵树还要用 $n-1$ 条边合并，这些边都在 $x$ 到 $y$ 的路径上，也计入答案。

时间复杂度线性。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;

int m,X,Y,as;

struct node{
	int n,mxd,mxx,dis,lp,pos;
	vector<vector<int>> g;
	vector<int> deg;
	void init(int sz){n=sz,g.resize(n+1),deg.resize(n+1),mxd=mxx=dis=-1;}
	
	void dfs1(int u,int fa,int w){
		if(mxd<w) mxd=w,pos=u;
		for(int v:g[u]) if(v^fa) dfs1(v,u,w+1);
	}
	
	void dfs2(int u,int fa,int w){ // mxx 类似于求直径
		if(mxx<w && !deg[u]) mxx=w,pos=u;
		for(int v:g[u]) if(v^fa) dfs2(v,u,w+1);
	}
	
	void DFS(int u,int fa,int w){ // d[x],d[y]
		if(dis<w && !deg[u]) dis=w;
		for(int v:g[u]) if(v^fa) DFS(v,u,w+1);
	}
	
	void getd(int u,int fa,int w,int tt){ // dep[x],dep[y]
		if(u==tt) return lp=w,void();
		for(int v:g[u]) if(v^fa) getd(v,u,w+1,tt);
	}
};

vector<node> T(1);

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >> m;
	
	for(int i=1,x;i<=m;++i){
		node tt; cin >> x,tt.init(x);
		for(int j=2,u;j<=x;++j) cin >> u,tt.g[u].push_back(j),tt.g[j].push_back(u),++tt.deg[u]; 
		tt.dfs1(1,0,0),tt.dfs2(tt.pos,0,0);
		T.push_back(tt);
	}
	
	cin >> X >> Y;
	T[1].DFS(X,0,0),T[2].DFS(Y,0,0);
	T[1].getd(1,0,0,X),T[2].getd(1,0,0,Y);
	
	int res=0;
	for(int i=3;i<=m;++i) res+=T[i].mxd; 
	
	as=T[1].dis+T[2].lp+res;
	as=max(as,T[2].dis+T[1].lp+res);
	for(int i=3;i<=m;++i) as=max(as,T[i].mxx+T[1].lp+T[2].lp+res-T[i].mxd);
	as+=m-1,cout << as;
}
```

---

## 作者：Supor__Shoep (赞：1)

~~不是很理解题意到底哪里有问题，我觉得挺清楚的啊。。。~~

反正现在出题人也重新解释了题意，我就不再说了（）

首先，如果要使得 $x,y$ 的距离最后是尽可能远的，我们就要考虑一些满足最优解的性质。

不难想到一个结论：如果将初始时每一棵树缩成一个节点，那么最优解形成的新的树**必然是一条链**，且链的两端分别是初始的第 $1,2$ 棵树。因为只有这样才能保证每一棵树都对答案产生了影响，否则说明必然存在一棵树是对 $x,y$ 的距离毫无影响的。下文记 $t_i$ 表示初始第 $i$ 棵树。

由于初始每棵树都有根，且题中的连边方式是让叶子节点与树根连边，也就是说最终形成的树也一定是一个有根树。我们不妨来探讨一下这个树根：

- 如果树根为 $t_1$ 或者 $t_2$，这就很显而易见了。假设现在树根为 $t_1$，那么就说明树中最深的节点就是 $t_2$。我们记录一个当前节点下标 $j$，初始时 $j=x$，每次我们找到 $j$ 所在的树 $t_i$ 中距离 $j$ 最远的一个**叶子**节点 $j\prime$，接着让 $j$ 移动到 $j\prime$ 处，这个时候我们再考虑跳到另一个树的根上。总的来说，我们到达的树的先后顺序是 $1\to (3\to 4\to\dots\to n)\to 2$，括号中的可以任意改变顺序。因此，对于所有 $i>2$ 的 $t_i$，$j$ 在其中移动的距离一定是**树的深度**；对于 $t_1$，$j$ 移动的距离是 $x$ **到某一个叶子节点的最远距离**；对于 $t_2$，$j$ 移动的距离则是 $y$ 的深度。计算此类情况的答案时，只需要计算它们的和就行了。

- 如果树根不是 $t_1$ 或者 $t_2$，则说明 $j$ 的移动方向是先往上，后往下。我们考虑枚举这个树根 $t_k$（$k>2$）。由于 $j$ 在除了 $t_1,t_2,t_k$ 以外的所有树中经过的距离都是其深度，所以这些树的排放并不重要。而对于 $t_1,t_2$，$j$ 的其中移动的距离分别是 $x,y$ 在树中的深度；对于 $t_k$，由于它肯定是选择了两个叶子节点进行连边，所以 $j$ 在其中移动的最大距离就是**最远的两个叶子节点之间的距离**。由于枚举的时间复杂度是 $O(n)$，我们记 $d_i$ 表示第 $i$ 棵树的最大深度，然后计算 $sum=\sum_{i=3}^n d_i$，每次计算除了 $t_1,t_2,t_k$ 之外的树的总代价时，我们只需要用 $sum$ 减去 $d_k$ 就行了。

综上，对于 $t_1,t_2$，我们要计算 $x,y$ 在其中的深度以及 $x,y$ 到达某个叶子节点的最长距离。对于 $t_i$（$i>2$），我们要计算 $d_i$ 以及其中最远的两个叶子节点的距离。然后按照上述方法计算就行了。

但是要注意，树与树之间的连边也会计入答案。考虑到最终的树的组成形态，我们可以知道一共会添加 $n-1$ 条边，并且它们都会计入 $x\to y$ 的最长距离。

可能我的讲述比较晦涩（因为这道题是森林，确实不太好描述 QAQ），如果不理解大致思路就最好先多举几个小例子手玩一下，如果看不懂思路，看代码的话应该可以感性理解：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
const int MAXM=1e6+5;
int N,n,p,q;
struct Tree
{
	int n;
	vector<int> fa;
}a[MAXN];
int w1,w2,w3,w4;
int head[MAXM],nxt[MAXM<<1],to[MAXM<<1],tot;
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int dis[MAXM],maxx[MAXM],bel[MAXM];
void dfs1(int x,int fa)
{
	for(int i=head[x];i;i=nxt[i])
	{
		if(to[i]==fa)	continue;
		dis[to[i]]=dis[x]+1,dfs1(to[i],x);
	}
}
void dfs2(int x,int fa)
{
	int flag=0;
	for(int i=head[x];i;i=nxt[i])
	{
		if(to[i]==fa)	continue;
		dis[to[i]]=dis[x]+1,flag=1;
		dfs2(to[i],x);
		if(maxx[x]<maxx[to[i]])	maxx[x]=maxx[to[i]],bel[x]=bel[to[i]];
	}
	if(!flag)	maxx[x]=dis[x],bel[x]=x;
	if(x==1&&!flag)	maxx[x]=0;
}
struct node
{
	int v1,v2;
}w[MAXN];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>N;
	for(int i=1;i<=N;i++)
	{
		cin>>a[i].n,a[i].fa.resize(a[i].n+2);
		for(int j=2;j<=a[i].n;j++)	cin>>a[i].fa[j];
	}
	cin>>p>>q;
	for(int i=2;i<=a[1].n;i++)	add(a[1].fa[i],i),add(i,a[1].fa[i]);
	dfs1(1,0),w1=dis[p];
	for(int i=1;i<=a[1].n;i++)	dis[i]=0;
	dfs2(p,0),w2=maxx[p];
	for(int i=1;i<=a[1].n;i++)	head[i]=0;
	tot=0;
	for(int i=1;i<=a[2].n;i++)	dis[i]=maxx[i]=0;
	for(int i=2;i<=a[2].n;i++)	add(a[2].fa[i],i),add(i,a[2].fa[i]);
	dfs1(1,0),w3=dis[q];
	for(int i=1;i<=a[2].n;i++)	dis[i]=0;
	dfs2(q,0),w4=maxx[q];
	for(int i=3;i<=N;i++)
	{
		for(int j=1;j<=a[i].n;j++)	head[j]=0,dis[j]=0,maxx[j]=0,bel[j]=0;
		tot=0;
		for(int j=2;j<=a[i].n;j++)	add(a[i].fa[j],j),add(j,a[i].fa[j]);
		dfs2(1,0),w[i].v1=maxx[1];
		for(int j=1;j<=a[i].n;j++)	maxx[j]=0,dis[j]=0;
		int id=bel[1];
		dfs2(id,0),w[i].v2=maxx[id];
	}
	int sum1=0,res=0;
	for(int i=3;i<=N;i++)	sum1+=w[i].v1;
	for(int i=3;i<=N;i++)	res=max(res,w1+w3+sum1-w[i].v1+w[i].v2);
	res=max(res,w1+w4+sum1),res=max(res,w2+w3+sum1);
	cout<<res+N-1;
	return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

看到有人发帖就来做了一下，超级大分（讨）啊。

而且还是这题第 100 通过诶。

---

第一种情况是好想的，我们把多出来的树看成由根到叶节点的链，然后搭个天梯挂下来，此时只需要分讨第一棵树与第二棵树的上下情况即可。

这个可以对每一棵树做树形 dp 求出链长与两人到根的距离，然后再分别以两人为根跑 dp 求出最长**人到叶子**距离，注意**不是直径**。

但是过不了。

仔细观察题面，注意到不一定要以她们所在公司为总根，这启示我们第二种情况。

也就是说，某一棵树的两个叶子结点分别挂下天梯，梯子下的两端分别各自一人。

于是再求一个最大的由原形式改为**叶子到叶子**距离的**收益**，就可以算答案了。注意仍然**不是直径**。

然后三种情况取最小就是答案，大力模拟上述思路即可。

记得初始化 dp 数组。

还有，收益可以是负数，但这种情况改变了树的形态，最后是可能有益于答案的。

总的来说这题讨论里 hack 很多，过不了的去看看确有帮助。

```cpp
#include<bits/stdc++.h>
#define qwq ve[op][x]
using namespace std;
int sum;
vector<int>ve[3][1000005];
int dp[3][1000005];
int max_=-1e9;
int M[3];
void dfs(int x,int fa,int op){
    for(int i=0;i<qwq.size();i++){
        if(qwq[i]==fa)continue;
        dp[op][qwq[i]]=dp[op][x]+1;
        dfs(qwq[i],x,op);
    }
}
int A[3],B[3];
bool lf[3][1000005];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int m;
        cin>>m;
        if(i<=2){
            M[i]=m;
            dp[i][1]=1;
            for(int j=2;j<=m;j++){
                int x;
                cin>>x;
                ve[i][x].push_back(j);
                ve[i][j].push_back(x);
                lf[i][x]=1;
            }
            dfs(1,0,i);
        }else{
            int flc=0;
            for(int j=1;j<=m;j++)
                ve[0][j].clear(),dp[0][j]=0,lf[0][j]=1;
            dp[0][1]=1;
            for(int j=2;j<=m;j++){
                int x;
                cin>>x;
                ve[0][x].push_back(j);
                ve[0][j].push_back(x);
                lf[0][x]=0;
            }
            dfs(1,0,0);
            int maxi;
            for(int j=1;j<=m;j++)
                if(flc<dp[0][j])
                    flc=dp[0][j],maxi=j;
            sum+=flc;
            for(int j=1;j<=m;j++)
                dp[0][j]=0;
            dp[0][maxi]=1;
            dfs(maxi,0,0);
            int fflc=0;
            for(int j=1;j<=m;j++)
                if(lf[0][j])
                    fflc=max(fflc,dp[0][j]);
            max_=max(max_,fflc-flc-1);
        }
    }
    for(int i=1;i<=2;i++){
        int x;
        cin>>x;
        A[i]=dp[i][x];
        memset(dp[i],0,sizeof dp[i]);
        dp[i][x]=1;
        dfs(x,0,i);
        for(int j=1;j<=M[i];j++)
        if(!lf[i][j])B[i]=max(B[i],dp[i][j]);
    }
    // cout<<A[1]<<' '<<A[2]<<'\n';
    // cout<<B[1]<<' '<<B[2]<<'\n';
    // cout<<sum<<' '<<max_<<'\n';
    int ans=sum+max({A[1]+B[2]-1,A[2]+B[1]-1,max_+A[1]+A[2]});
    cout<<ans;
    return 0;
}
```

---

## 作者：_zuoqingyuan (赞：0)

[传送门。](https://www.luogu.com.cn/problem/P10406)

# 题意分析

给定 $n$ 颗以 $1$ 号节点为根的树。

定义**合并操作**为：选定两颗树，将一棵树的**根**与另一棵树的**叶子节点**连接，构成一棵新树。

指定**第一颗树上的某个节点 $x$，第二棵树上某个节点 $y$**。要求你输出将所有树都合并时，**$x,y$ 之间距离的最大值**，其中，距离是指两点在树上简单路径的长度。

# 思路分析

**最优方案一定如下**：一棵树上最多有两个叶子节点分别连接另一颗树，其余树均只有一个叶子节点连接某棵树，且第一颗树和第二棵树必然在连接成的新树的最两端。

很好证明，如果存在一棵树下连接三颗或以上的树，或者多颗树下连接不止一棵树，我们都可以把**多出的树“抽”出来，“插入”到第一棵树和连接其的树的中间**，这样一定可以增加 $x,y$ 之间的距离。

如果第一颗树和第二棵树不在连接成的新树的最两端。我们也可以把它们抽出来，连接在最两端，也一定可以增加 $x,y$ 之间的距离。

有了具体雏形，我们应当如何计算？

## 定义

我们定义新合并产生的数叫做**合并树**；原本的树中位于合并树的根的位置的树，称其为**树干**；其余树则称其为**树枝**；连接另一颗树树根的叶子节点称为**树杈**；第一棵树为合并树的**左端**；第二棵树为合并树的**右端**，特殊的，左右端也可以是树干；为了方便，原树中根节点的深度按 $0$ 来算。

## 树枝

我们发现，如果一棵树是树枝，那么他对答案产生的影响就是这棵树树杈与根节点的距离，根据贪心，这个距离越大越好，我们就取原树中**所有节点的最大深度值**为这个距离。

如果合并树的左右端是树杈呢？以左端为例：它在最后对答案的贡献是**原树根节点到 $x$ 的距离**，即为 $x$ 在原树的深度。同理，右端则是 $y$ 在原树中的深度。

## 树干

树干对答案的贡献就是**两个树杈之间的距离**，根据贪心，这个距离越长越好；如果左右端是树干，以左端为例，这个距离是**节点 $x$ 到树杈的距离**。同理可得左端。

## 其余

每合并一次，就会在 $x,y$ 路径上多增加一条连接的边，这些边一共 $n-1$ 条。

# 实现过程

对于树枝部分，普遍和深度有关，我们用 DFS 实现即可，时间复杂度 $O(n)$。

对于树干部分，类似求树的直径，两次 DFS 实现，时间复杂度 $O(n)$。

**值得注意的点是**：树杈部分必须是叶子节点，而并非树的直径，例如当树成一条链时，该树不可能连接两颗其他的树，但如果按树的直径来算，则可以，两个树杈分别是树根和唯一一个叶子节点。

这一点有许多解决方法，这里我选择记录节点的度数，如果一个节点是叶子节点则度数一定小于 $1$（还有孤立点的情况），且编号不为 $1$。

如果第 $i$ 颗树做树枝对答案的影响为 $a_i$，做树干对答案的影响为 $b_i$。我们可以这样计算答案。

因为树干只有一个，我们枚举树干。一颗树当树干，就当不了树枝，这时答案为 $b_i+\sum\limits_{j=1,j\ne i}^na_j=b_i+\sum\limits_{j=1}^na_j-a_i$。

我们令 $S=\sum\limits_{i=1}^na_i$。显然 $S$ 可以提前算出来，最后的答案就是：

$$S+\max\{b_i-a_i\}+n-1$$

我们遍历 $i$，取最大的 $b_i-a_i$ 就好。

也说不上树形 dp，时间复杂度 $O(n)$。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int N=1e5+10,M=1e6+10;
vector<int>v[N],g[M];
int n,x,y,de[M],cnt,len[N],maxn=-1e9,pos,ans,tp,tot,a[N],b[N],maxde,d[N];
void dfs(int x,int fa){
    de[x]=de[fa]+1;
    if(de[x]>maxde)maxde=de[x],pos=x;
    for(auto y:g[x])if(y!=fa)dfs(y,x);
}
int main(){
    scanf("%d",&n);de[0]=-1;
    for(int i=1,sum,f;i<=n;i++){
        scanf("%d",&sum);
        v[i].push_back(0);
        v[i].push_back(sum);
        for(int j=2;j<=sum;j++){
            scanf("%d",&f);
            v[i].push_back(f);
        }
    }
    scanf("%d %d",&x,&y);
    for(int i=1;i<=n;i++){
        int m=v[i][1];
        for(int j=2;j<=m;j++){
            g[j].push_back(v[i][j]);d[j]++;
            g[v[i][j]].push_back(j);d[v[i][j]]++;
        }
        if(i==1){
            maxde=0,dfs(1,0),ans+=de[x],a[1]=de[x];
            maxde=0,dfs(x,0);
            for(int j=1;j<=m;j++)if(j!=1&&d[j]<=1)b[1]=max(b[1],de[j]);
        }else if(i==2){
            maxde=0,dfs(1,0),ans+=de[y],a[2]=de[y];
            maxde=0,dfs(y,0);
            for(int j=1;j<=m;j++)if(j!=1&&d[j]<=1)b[2]=max(b[2],de[j]);
        }else{
            maxde=0,dfs(1,0),ans+=maxde,a[i]=maxde;
            maxde=0,dfs(pos,0);
            for(int j=1;j<=m;j++)if(j!=1&&d[j]<=1)b[i]=max(b[i],de[j]);
        }
        for(int j=1;j<=m;j++)g[j].clear(),de[j]=0,d[j]=0;
    }
    for(int i=1;i<=n;i++)maxn=max(maxn,b[i]-a[i]);
    printf("%d\n",maxn+ans+n-1);
    return 0;
}
```

如有错误请指出。

### 闲话

赛时用的树的直径求法，还忘记清空 $maxde$ 了，$60\text{ pts}$ 变 $0\text{ pts}$。

---

