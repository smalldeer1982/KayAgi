# Labelling Cities

## 题目描述

Oleg the bank client lives in Bankopolia. There are $ n $ cities in Bankopolia and some pair of cities are connected directly by bi-directional roads. The cities are numbered from $ 1 $ to $ n $ . There are a total of $ m $ roads in Bankopolia, the $ i $ -th road connects cities $ u_{i} $ and $ v_{i} $ . It is guaranteed that from each city it is possible to travel to any other city using some of the roads.

Oleg wants to give a label to each city. Suppose the label of city $ i $ is equal to $ x_{i} $ . Then, it must hold that for all pairs of cities $ (u,v) $ the condition $ |x_{u}-x_{v}|<=1 $ holds if and only if there is a road connecting $ u $ and $ v $ .

Oleg wonders if such a labeling is possible. Find an example of such labeling if the task is possible and state that it is impossible otherwise.

## 说明/提示

For the first sample, $ x_{1}=2 $ , $ x_{2}=3 $ , $ x_{3}=x_{4}=1 $ is a valid labeling. Indeed, $ (3,4) $ , $ (1,2) $ , $ (1,3) $ , $ (1,4) $ are the only pairs of cities with difference of labels not greater than $ 1 $ , and these are precisely the roads of Bankopolia.

For the second sample, all pairs of cities have difference of labels not greater than $ 1 $ and all pairs of cities have a road connecting them.

For the last sample, it is impossible to construct a labeling satisfying the given constraints.

## 样例 #1

### 输入

```
4 4
1 2
1 3
1 4
3 4
```

### 输出

```
YES
2 3 1 1 
```

## 样例 #2

### 输入

```
5 10
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
5 4
```

### 输出

```
YES
1 1 1 1 1 
```

## 样例 #3

### 输入

```
4 3
1 2
1 3
1 4
```

### 输出

```
NO
```

# 题解

## 作者：wishapig (赞：6)

## 题目大意

给出 $n$ 个点 $m$ 条边的简单无向连通图。

需要给每个点 $i$ 设定一个 $1$ 至 $10^9$ 的权值 $x_i$，满足：

- 对任意 $1\le i<j\le n$，$|x_i-x_j|\le 1$ **当且仅当** $i,j$ 有边直接相连。

构造任意一组解或判定无解。

$2\le n\le 3\times 10^5,1\le m\le 3\times 10^5$，要求 $1\le x_i\le 10^9$。

---

提供一个和标算完全不一样的**线性**做法。

先特判掉完全图的情况，这个是一定有解的。

由题意，我们有一个非常强的当且仅当的限制，如果确定了一组 $x_i$，那么就能构造出一个与之对应的图：

- $G=(V,E),V=\{1,2,\cdots ,n\},E=\{(u,v)|1\le u<v\le n,|x_u-x_v|\le 1\}$

如果这个图和原图一模一样，那么就 win 了。

考察这个生成图 $G$，由于原图是连通的，因此如果有解，一组合法的 $x_i$ 在值域上是连续的一段。

**把所有点按 $x_i$ 建出分层图，$x_i$ 相同的所有点放在同一层内**，大概就是这样的：

- 每一层连出一个完全图。

- 相邻两层连成一个完全二分图。

![](https://cdn.luogu.com.cn/upload/image_hosting/i30djrum.png)

我们的目标就转而判断原图能否这样分层。

先随意找一个节点作为起点开始 BFS：

1. 如果 BFS 到的最大 dis $\ge 2$，任取一个 dis 最大的点，**这个点一定在最左一层或最右一层**，不妨钦定以它为第一层（$x_i=1$），往后找过去。再从这个点开始做一次 BFS，这样根据第二次所得的 dis 就可以正确分出除了第一/二层的点了（前两层分不出来是因为除了起点 dis 为 $0$，其他的 dis 全部都是 $1$），此时再利用第一次 BFS 所得的 dis 就可以分出前两层了。

2. 如果 BFS 到的最大 dis $\le 1$，这时图相当于只有三层（不可能是两层因为两层相当于一个完全图）。观察到中间一层的所有点 deg 均为 $n-1$，其他点 deg 均不为 $n-1$，这样就可以分出第二层。把第二层的所有点拔掉，应当剩下两个连通块，一个为第一层另一个为第三层（实际在实现的时候，任取一个连通块作为第一层，其他全部作为第三层，不会影响正确性）。

这样就分出层来了，然后需要 check 这个分层方式是否正确（注意它已经是唯一的分层方式了，如果它不正确就直接说明无解）。

首先记录各层的点个数 $siz$，设最大层数 $d$，如果：
$$
\sum_{i=1}^d\binom{siz[i]}{2}+\sum_{i=2}^dsiz[i]\times siz[i-1]\not=m
$$
那么无解（左边是生成图 $G$ 的边数）。

然后，如果原图中每条边两个端点所在层的编号相差均 $\le 1$ 那么就是合法的了。

时间复杂度是线性的。

题外话：

这题一开始给我看蒙了，然后突然想到 md 这个暴力 check 要 $n^2$，那 checker 怎么写啊？然后 YY 出来一个分层图的算法，结果发现它对解题好像是个可行的思路呵呵。

~~忽略快读快输好吧~~

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,m,u,v,mx,pos; long long cnt;
int Eu[N],Ev[N],id[N],siz[N],d1[N],d2[N],deg[N];
queue<int> q;
vector<int> G[N];
void GG(){ puts("NO"); exit(0); }
void dfs(int u){ id[u]=1; for (int v:G[u]) if (!id[v]) dfs(v); }
void BFS(int s, int* d){
	q.push(s); d[s]=0;
	while (!q.empty()){
		int u=q.front(); q.pop();
		for (int v:G[u]) if (d[v]==-1) d[v]=d[u]+1,q.push(v);
	}
}
char *S,*T,buf[1<<22];
#define gc() (S==T?T=(S=buf)+fread(buf,1,1<<22,stdin):0,S==T?EOF:*S++)
inline int read(){
	char ch=gc(); int num=0;
	while (!isdigit(ch)) ch=gc();
	while (isdigit(ch)) num=num*10+ch-'0',ch=gc();
	return num;
}
char obuf[1<<23],*Os=obuf;
inline void Pc(char c){ *Os++=c; }
void P(int x){ if (x>9) P(x/10); Pc(x%10+'0'); }
int main(){
	n=read(),m=read();
	for (int i=1; i<=m; i++){
		u=read(),v=read(); Eu[i]=u,Ev[i]=v;
		G[u].push_back(v),G[v].push_back(u);
		deg[u]++,deg[v]++;
	}
	if (m==1ll*n*(n-1)/2){
		Pc('Y'),Pc('E'),Pc('S'),Pc('\n');
		for (int i=1; i<=n; i++) Pc('1'),Pc(i==n?'\n':' ');
		return fwrite(obuf,1,Os-obuf,stdout),0;
	}
	memset(d1,-1,sizeof(d1));
	memset(d2,-1,sizeof(d2));
	BFS(1,d1);
	for (int i=1; i<=n; i++) if (d1[i]>d1[pos]) pos=i;
	if (d1[pos]>=2){
		BFS(pos,d2);
		for (int i=1; i<=n; i++) id[i]=d2[i]>=2?d2[i]+1:(d1[i]==d1[pos]?1:2);
	} else {
		for (int i=1; i<=n; i++) if (deg[i]==n-1) id[i]=2;
		for (int i=1; i<=n; i++) if (!id[i]){ dfs(i); break; }
		for (int i=1; i<=n; i++) if (!id[i]) id[i]=3;
	}
	for (int i=1; i<=m; i++) if (abs(id[Eu[i]]-id[Ev[i]])>1) GG();
	for (int i=1; i<=n; i++) 	siz[id[i]]++,mx=max(mx,id[i]);
	for (int i=1; i<=mx; i++) cnt+=1ll*siz[i]*(siz[i]-1)/2+1ll*siz[i]*siz[i-1];
	if (cnt!=m) GG();
	Pc('Y'),Pc('E'),Pc('S'),Pc('\n');
	for (int i=1; i<=n; i++) P(id[i]),Pc(i==n?'\n':' ');
	return fwrite(obuf,1,Os-obuf,stdout),0;
}
```

---

## 作者：天命之路 (赞：3)

题目传送门 : [link](https://www.luogu.com.cn/problem/CF794D)

#### 写在前面

相信看到这道题，大家第一眼都会认为是差分约束，但 ...

​	 **if and only if** there is a road connecting u and v .

也就是说，对于无边相连的 $(u,v)$ , $ |x_u - x_v| \gt 1$

噔 噔 咚

---------

#### 正解

然后你想了一下，发现已知算法都不是很可做的样子

考虑推~~（猜）~~结论

我们可以发现，对于 $\forall u,v ,x_u = x_v$ , 他们所相邻的点（即有直接连边的点）也是相同的

因为任意一个点 $x$ 要么与他们都有连边，要么都没有连边，详细证明略

考虑把这个结论反过来，对于两个邻居相同的节点，是否存在一种方案，使得他们具有相同的权值？

是的，如果自己也算自己的邻居的话。

我们来证明一下这个结论：

##### 证明：

因为自己也算自己的邻居，所以如果满足“邻居相同”，这两个点 $u,v$ 必然也是邻居，即 $|x_u - x_v | \le 1$

考虑一种类似反证的思想，设 $x_u = i,x_v = i+1$

则他们的邻居当中不可能有点权值为 $i-1 $ 或 $i + 2$，因为这些邻居与这两个点都相邻

所以只可能为 $i$ 或 $i+1$

显然，令 $x_v \leftarrow i$ ,并不会影响方案的合法性，因为它和邻居之间的差距依旧在 $1$ 以内



$\therefore$  我们可以把每个点的邻居列表预处理出来，把邻居列表相同的点缩起来，建一张新图。

注意到我们在上面已经完成了充分性和必要性的证明，故“邻居相同” 等价于 “权值相同”

所以新图中的点权必须不同，即 $|x_u-x_v| = 1$

接下来证明第二个结论：新图中若有点度数 $\ge 3$ ，则必然无解

##### 证明：

接下来只证明度数 $=3$ 的情况， $>3$ 的情况可以从邻居中任选 $3$ 个，转换为此种情况

设该点为 $u$，邻居分别为 $a,b,c$，权值为 $x$

$u,a,b,c$ 只有三种可选的权值，所以依据抽屉原理，必有两点权值相同，与“点权不同”矛盾，原命题成立



首先，原图联通，新图必然联通

因为新图中度数都 $<=2$ ，所以只有两种情况：环或链

环显然无解，对于链的情况，把链上第 $i$ 个点染色为 $i$ 即可

#### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
typedef long long ll;
pair<vector<int>,int> adj[N];
set<int> adj2[N];
int lab[N],cnt = 0;

int co[N],n,m;
inline void path(int x,int c)
{
	co[x] = c;
	for(set<int>::iterator a = adj2[x].begin();a != adj2[x].end(); ++a)	
	{
		int y = *a;
		if(!co[y])
			path(y,c+1);
	}
}
int X[N],Y[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		adj[i].first.push_back(i),
		adj[i].second = i;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		X[i] = u;Y[i] = v;
		adj[u].first.push_back(v);
		adj[v].first.push_back(u);
	}
	for(int i=1;i<=n;i++)
		sort(adj[i].first.begin(),adj[i].first.end());
	sort(adj+1,adj+n+1);
	for(int i=1;i<=n;i++)
	{
		if(adj[i].first == adj[i-1].first)
			lab[adj[i].second] = cnt;
		else lab[adj[i].second] = ++cnt;
	}
	if(cnt == 1)
	{
		printf("YES\n");
		for(int i=1;i<=n;i++) printf("%d ",lab[i]);
		printf("\n");
		return 0;
	}
	for(int i=1;i<=m;i++)
	{
		int u = X[i],v = Y[i];
		if(lab[u] != lab[v])
		adj2[lab[u]].insert(lab[v]),
		adj2[lab[v]].insert(lab[u]);
	}
	int d1=0,root=0;
	for(int i=1;i<=cnt;i++)
	{
		if(adj2[i].size() > 2)
			return puts("NO"),0;
		if(adj2[i].size() == 1) d1++,root = i;
		else assert(adj2[i].size() == 2);
	}
	if(d1 == 2)
	{
		path(root,1);
		puts("YES");
		for(int i=1;i<=n;i++)
			printf("%d ",co[lab[i]]);
	}
	else
		return puts("NO"),0;
	return 0;
}
```



---

## 作者：_fairytale_ (赞：1)

这个题太牛了。

认为 $i$ 也是 $i$ 号点的邻居，那么存在一种方案，两个点邻居集合相同 $\iff$ 点权相同。

首先点权相同的话邻居集合肯定相同，所以只需证邻居集合相同的点点权相同。

首先两个邻居相同的点 $u,v$ 一定是邻居，假设点权不同，则分别为 $i,i+1$，它们的邻居集合的点的点权也只能是 $i,i+1$ 而不能是 $i-1$ 或 $i+2$。除了这些点之外的点的点权只能在 $[i-1,i+2]$ 之外，因此把 $v$ 的点权从 $i+1$ 调整到 $i$ 是等价的。

找邻居集合相同的点可以哈希，我们把所有点权相同的点都缩成一个，建出新图，则新图中所有点的点权必然不同，因此与新图中一个点相连的点的点权只有不超过两种取值。

然后接下来是我一开始的思路，当时只想到了这一部分。

考虑新图上的一个点，如果它的度数 $\ge 3$，由于与它相连的点只有两种取值，因此至少有一对点点权相同，与条件矛盾，肯定无解。因此只需考虑新图上所有点度数 $\le 2$ 的情况。

这样，图中的连通块要么是链，要么是环。链一定有解，环一定无解，构造是简单的。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define rep(x,qwq,qaq) for(int (x)=(qwq);(x)<=(qaq);++(x))
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define maxn 301000
int n,m,k;
ull a[maxn],h[maxn],b[maxn];
struct edge{
	int u,v;
}e[maxn];
vector<int>g[maxn];
int u,v;
gp_hash_table<int,int>mp[maxn];
int x[maxn],nw=1;
void dfs(int u,int f){
	x[u]=nw++;
	for(int v:g[u]){
		if(v==f)continue;
		dfs(v,u);
	}
}
int deg[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n>>m;
	gp_hash_table<ull,bool>vis;
	rep(i,1,n){
		ull x=rnd();
	    while(vis[x])x=rnd();
		a[i]=x;
		h[i]=a[i];
	}
	rep(i,1,m){
		cin>>u>>v;
		e[i]={u,v};
		h[u]^=a[v];
		h[v]^=a[u];
	} 
	rep(i,1,n)b[i]=h[i];
	sort(b+1,b+n+1);
	k=unique(b+1,b+n+1)-b-1;
	rep(i,1,n)h[i]=lower_bound(b+1,b+k+1,h[i])-b;
	rep(i,1,m){
		u=e[i].u,v=e[i].v;
		if(h[u]==h[v])continue;
		if(!mp[h[u]][h[e[i].v]]){
			g[h[u]].push_back(h[v]);
			g[h[v]].push_back(h[u]);
			mp[h[u]][h[v]]=mp[h[v]][h[u]]=1;
			++deg[h[u]],++deg[h[v]];
		}
	}
	rep(i,1,k)if(deg[i]>=3)return cout<<"NO\n",0;
	rep(i,1,k){
		if(x[i]||deg[i]==2)continue;
		dfs(i,0);
		++nw;
	}
	rep(i,1,n)if(!x[h[i]])return cout<<"NO\n",0;
	cout<<"YES\n";
	rep(i,1,n)cout<<x[h[i]]<<" \n"[i==n];
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

性质题。

如果存在两个点的邻居集合完全相同（邻居包括自己），那么给他们的权值相同一定是不劣的。

注意到这两个点的邻居集合完全相同，那么一定互相之间有连边。考虑给他们不同权值，不妨设分别为 $x$ 和 $x+1$。于是，跟他们相邻的点一定满足权值是 $x$ 或 $x+1$。不难发现给他们相同的权值 $x$ 或 $x+1$ 均符合要求。于是，给邻居集合相同的点相同的权值一定是不劣的。

考虑看成分层图，将邻居集合完全相同的点放在同一层，容易发现这个分层图必须是一层一层的塔状，每一层的点均等于下一层点权值加一，否则一定会有额外边出现，这是不符合要求的。

于是现在目标就是找到每一层，层与层之间是否有边是容易判断的。

考虑如何判断邻居集合完全相同，可以想到使用异或哈希。于是这题就解决了。复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
mt19937 rng(time(0));
vector<int> vc[1000005];
vector<int> nc[1000005];
int val1[1000005],val2[1000005],tot1[1000005],tot2[1000005],cnt,bel[1000005];
bool vis[1000005];
vector<int> deg1;
int deg[1000005];
map<pair<int,int>,int> mp;
map<pair<int,int>,int> ed;
int ans[1000005],prt;
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++) val1[i]=tot1[i]=rng(),val2[i]=tot2[i]=rng();
	int mvv=0;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
		tot1[u]^=val1[v];
		tot1[v]^=val1[u];
		tot2[u]^=val2[v];
		tot2[v]^=val2[u];
	}
	for(int i=1;i<=n;i++){
		mvv=max(mvv,(int)vc[i].size());
		if(!mp[make_pair(tot1[i],tot2[i])]) mp[make_pair(tot1[i],tot2[i])]=++cnt;
		bel[i]=mp[make_pair(tot1[i],tot2[i])];
	}
	for(int i=1;i<=n;i++){
		for(auto v:vc[i]){
			if(!ed[make_pair(bel[i],bel[v])]&&bel[i]!=bel[v]){
				nc[bel[i]].push_back(bel[v]);
				nc[bel[v]].push_back(bel[i]);
//				cout<<bel[i]<<" "<<bel[v]<<"\n";
				deg[bel[i]]++,deg[bel[v]]++;
				ed[make_pair(bel[i],bel[v])]=ed[make_pair(bel[v],bel[i])]=1;
			}
		}
	}
	int maxv=0;
	for(int i=1;i<=cnt;i++){
		if(deg[i]==0) vis[i]=1,ans[i]=(prt+=2);
		if(deg[i]==1) deg1.push_back(i);
		maxv=max(maxv,deg[i]);
	}
	if(maxv>2){
		cout<<"NO";
		return 0;
	}
	for(auto st:deg1){
		if(!vis[st]){
			prt+=2;
			do{
				bool trans=0;
				vis[st]=1;
				ans[st]=++prt;
				for(auto v:nc[st]){
					if(!vis[v]){
						st=v;
						trans=1;
						break;
					}
				}
				if(!trans) break;
			}while(1);
		}
	}
	for(int i=1;i<=cnt;i++){
		if(!vis[i]){
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++) cout<<ans[bel[i]]<<" ";
	return 0;
}
```

---

