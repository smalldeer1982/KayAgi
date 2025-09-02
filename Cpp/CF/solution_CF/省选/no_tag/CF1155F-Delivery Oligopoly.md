# Delivery Oligopoly

## 题目描述

整个 Berland 的快递市场由两家竞争公司 BerEx 和 BerPS 控制。它们都在 Berland 的所有城市间提供快速且可靠的快递服务。

Berland 的地图可以表示为一张无向图，城市为顶点，道路为连接城市之间的边。任意一对城市之间最多只有一条道路，每条道路连接的是不同的城市。

BerEx 和 BerPS 之间竞争激烈，对于每一对城市 $(v, u)$，它们都设置了各自的路径，使得这两条路径之间没有任何一条道路是重合的。保证这样的设置是可行的。

现在，Berland 政府决定通过废弃部分道路来减少道路维护成本。显然，他们希望维护的道路数量尽可能少。但同时，他们又不希望破坏整个快递系统。因此，BerEx 和 BerPS 之间每一对城市之间仍然需要能够有两条不重合的路径。

请问 Berland 政府最少需要维护多少条道路？

更正式地说，给定一张 $2$-边连通的无向图，最少可以保留多少条边，使得保留后的图依然是 $2$-边连通的？

## 说明/提示

以下是样例中的图示，红色边为被维护的道路。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1155F/f8cc8be0ffeaa507611464c133b700c1bfff4218.png)
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1155F/ddf572c9ce5da3caff7f3f945bec8caed610de38.png)
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1155F/396a726bd443525a7d7d772e211f1816f0f1d82f.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
3
1 3
3 2
1 2
```

## 样例 #2

### 输入

```
4 5
1 2
1 4
2 3
4 3
1 3
```

### 输出

```
4
1 4
4 3
3 2
1 2
```

## 样例 #3

### 输入

```
6 10
1 2
2 3
3 1
3 4
4 5
5 6
4 6
2 5
1 6
3 5
```

### 输出

```
6
1 6
6 5
5 4
4 3
3 2
1 2
```

# 题解

## 作者：RedLycoris (赞：13)

我们不难发现毒瘤们想让我们写状压dp，所以我们考虑如何不写状压dp。

由于这题的数据范围很小，所以我们可以考虑随机。

假设当前随机到的数为tmp，则分为3种情况：

1.将所有的点设置为"选择"（因为我们可能在一开始有一个不好的开头）

2.随机删除一条边

3.随机补回一条边

由于要使得最终结果最小，所以2的概率要大点

测试得到1为$\frac{1}{1024}$，2为$\frac{3}{4}$，3为$\frac{1}{4}$时可以过。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mxn=15;
vector<short>g[mxn];
short n,m;
vector<pair<short,short> >edges,cur;
vector<pair<short,short> >erases,ans;
bool used[mxn];
inline bool go(){  //直接暴力判边双
	for(short i=0;i<cur.size();++i){
		memset(g,0,sizeof(g));
		for(short j=0;j<cur.size();++j)if(i!=j)g[cur[j].first].push_back(cur[j].second),g[cur[j].second].push_back(cur[j].first);
		memset(used,0,sizeof(used));
		queue<int>q;q.push(1);
		for(;q.size();){
			int p=q.front();q.pop();
			for(int j=0;j<g[p].size();++j){
				if(!used[g[p][j]]){
					used[g[p][j]]=1;
					q.push(g[p][j]);
				}
			}
		} 
		for(short i=1;i<=n;++i)if(!used[i])return 0;
	}
	return 1;
}
inline void solve(){
	cin>>n>>m;
	for(short i=1,x,y;i<=m;++i){
		cin>>x>>y;
		edges.push_back({x,y});
		ans.push_back({x,y});
	}
	clock_t St=clock();
	cur=edges;
	for(;clock()-St<1900;){  //卡时间
		short rd=rand();
		if(rd%1024==0 or edges.size()==0){
			cur=edges;
			erases.clear();
			continue;
		}
		if(rd%4 or !erases.size()){
			short tmp=rand()%(cur.size());
			pair<short,short>pt=cur[tmp];
			cur.erase(cur.begin()+tmp);
			if(go()){
				if(cur.size()<ans.size())ans=cur;
			}else{
				cur.push_back(pt);
			}
		}else{
			short tmp=rand()%(erases.size());
			cur.push_back(erases[tmp]);
			erases.erase(erases.begin()+tmp);
		}
	}
	cout<<ans.size()<<'\n';
	for(short i=0;i<ans.size();++i)cout<<ans[i].first<<' '<<ans[i].second<<'\n';
}
int main(){
	srand(time(NULL));
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	short T=1;//cin>>T;
	for(;T--;)solve();
}
```

---

## 作者：Kevin090228 (赞：6)

伟大的 zrm 曾经说过：

> 我们不难发现毒瘤们想让我们写状压 dp，所以我们考虑如何不写状压 dp。

但是 zrm 的做法需要试一些概率，这可能在 CF 的比赛中带来一些罚时。所以我们换个做法。

考虑一个生成双联通子图的方法：跑一遍 tarjan，初始时只选择所有树边，每次当一个点即将和父亲断开，也就是他所有儿子的 low 值比他的 dfn 要大的时候，就加入一条子树内往上连的尽量高的边，也就是另一端深度要尽量小。

可惜这个做法得到的子图不一定是最优的。我们可以考虑每次随机选一个点作为根进行 tarjan，然后每次随机打乱邻接表的顺序，跑 $10^5$ 次或者进行一个卡时即可通过。

```cpp
//Author: Kevin5307
#include<bits/stdc++.h>
//#pragma GCC optimize("O2")
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define ALL(x) (x).begin(),(x).end()
#define rALL(x) (x).rbegin(),(x).rend()
#define srt(x) sort(ALL(x))
#define rev(x) reverse(ALL(x))
#define rsrt(x) sort(rALL(x))
#define sz(x) (int)(x.size())
#define inf 0x3f3f3f3f
#define pii pair<int,int>
#define lb(v,x) (int)(lower_bound(ALL(v),x)-v.begin())
#define ub(v,x) (int)(upper_bound(ALL(v),x)-v.begin())
#define uni(v) v.resize(unique(ALL(v))-v.begin())
#define longer __int128_t
void die(string S){puts(S.c_str());exit(0);}
int low[15],dfn[15],low2[15];
int t;
vector<int> G[15];
vector<pii> vec;
pii up[15];
void dfs(int u,int fa)
{
	random_shuffle(ALL(G[u]));
	low[u]=low2[u]=dfn[u]=++t;
	for(auto v:G[u])
		if(v!=fa)
		{
			if(dfn[v])
			{
				if(dfn[v]<low[u])
					up[u]=mp(u,v);
				low[u]=min(low[u],dfn[v]);
			}
			else
			{
				vec.pb(mp(v,u));
				dfs(v,u);
				if(low[u]>low[v])
					up[u]=up[v];
				low[u]=min(low[u],low[v]);
				low2[u]=min(low2[u],low2[v]);
			}
		}
	if(dfn[u]==low2[u]&&fa)
	{
		vec.pb(up[u]);
		low2[u]=low[u];
	}
}
vector<pii> ans;
int main()
{
	srand(114514);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].pb(v);
		G[v].pb(u);
		ans.pb(mp(u,v));
	}
	for(int j=0;j<100000;j++)
	{
		t=0;
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(low2,0,sizeof(low2));
		vec.clear();
		dfs(rand()%n+1,0);
		if(sz(vec)<sz(ans))
			ans=vec;
	}
	printf("%d\n",sz(ans));
	for(auto pr:ans)
		printf("%d %d\n",pr.first,pr.second);
	return 0;
}
```

Bonus：这个做法极其优秀，以至于似乎跑个 $10^3$ 次就能 AC？不太会证。

---

## 作者：Fan_sheng (赞：6)

QAQ 这里是朴素的状压 dp

首先 $n\le14$ 肯定想到状压相关，更进一步的话是子集枚举的复杂度。那么我们容易设出状态 $dp_S$ 表示 $S$ 集合内的点组成边双所需的最小边数。

但是你发现一个集合是边双不代表它的子集都是边双，所以我们要找到一种良好的扩展方式，使得从 $dp_S$ 出发能转移到所有包含 $S$ 的集合。换句话说，使其具有最优子结构。

这里，我们选择每次枚举 $S$ 中两个点 $u,v$（$u,v$ 可以相同），扩展一条连接 $u,v$ 的链 $T$（当 $u=v$ 就是一个环），且 $T$ 上只有 $u,v$ 在 $S$ 集合中。

容易证明扩展后的集合一定是一个边双。至于为什么可以扩展到所有包含 $S$ 的边双，可以考虑耳分解的结论：无向图有耳分解当且仅当其边双联通。耳分解就是将一个图拆成一个环和若干个耳（这里的环和耳就是我们所扩展的链）。有兴趣的可以自己百度一下。

于是我们预处理 $path_{u,v,S}$ 表示从 $u$ 到 $v$，经过点集为 $S$ 的最短链，这个可以直接 dfs。之后通过子集枚举进行 dp 转移。

最后记录转移路径并输出即可。复杂度瓶颈 $\mathbb O(n^23^n)$。

Code

代码写丑了点……

```cpp
#include<bits/stdc++.h>
#define p(x) (1<<((x)-1))
using namespace std;
int n,m;
bool e[15][15];
struct star{int val,u,v,S;}dp[1<<14],path[15][15][1<<14];
void dfs(int id,int from1,int from2,int depth,int s,int S){
	if(path[s][id][S].val<=depth)return;
	path[s][id][S]=(star){depth,from1,0,from2};
	for(int i=1;i<=n;i++)if(e[id][i]){
		e[id][i]=e[i][id]=0;
		dfs(i,id,S,depth+1,s,S|p(i));
		e[id][i]=e[i][id]=1;
	}
}
void out2(int u,int v,int S){
	if(!path[u][v][S].u)return;
	int tmp=path[u][v][S].u;
	printf("%d %d\n",tmp,v);
	out2(u,tmp,path[u][v][S].S);
}
void out(int S){
	if(!dp[S].u)return;
	out((S^dp[S].S)|p(dp[S].u)|p(dp[S].v));
	out2(dp[S].u,dp[S].v,dp[S].S);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
	scanf("%d%d",&u,&v),e[u][v]=e[v][u]=1;
	for(int S=0;S<(1<<n);S++){
		dp[S].val=0x3f3f3f3f;
		for(int u=1;u<=n;u++)
		for(int v=1;v<=n;v++)path[u][v][S].val=0x3f3f3f3f;
	}
	for(int i=1;i<=n;i++)dfs(i,0,0,0,i,p(i)),dp[p(i)].val=0;
	for(int S=0;S<(1<<n);S++)
	for(int u=1;u<=n;u++)if(S&p(u))
	for(int v=u;v<=n;v++)if(S&p(v)){
		int U=((((1<<n)-1)^S)|p(u)|p(v));
		for(int T=U;;T=(T-1)&U){
			if(dp[S|T].val>dp[S].val+path[u][v][T].val)
			dp[S|T]=(star){dp[S].val+path[u][v][T].val,u,v,T};
			if(!T)break;
		}
	}printf("%d\n",dp[(1<<n)-1].val),out((1<<n)-1),exit(0);
}
```


---

