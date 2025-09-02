# [ABC264E] Blackout 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc264/tasks/abc264_e

ある国には $ N $ 個の都市と $ M $ 個の発電所があります。これらを総称して地点と呼びます。  
 地点には $ 1,2,\dots,N+M $ の番号がつけられており、そのうち都市は地点 $ 1,2,\dots,N $ で発電所は地点 $ N+1,N+2,\dots,N+M $ です。

この国には電線が $ E $ 本あり、電線 $ i $ ( $ 1\ \le\ i\ \le\ E $ ) は地点 $ U_i $ と地点 $ V_i $ を双方向に結びます。  
 また、ある都市に **電気が通っている** とは、ある都市から電線をいくつか辿って少なくともひとつの発電所に辿り着くことができる状態を言います。

今、 $ Q $ 個のイベントが起こります。そのうち $ i $ ( $ 1\ \le\ i\ \le\ Q $ ) 番目のイベントでは電線 $ X_i $ が切れ、その電線を辿ることができなくなります。一度切れた電線は、その後のイベントにおいても切れたままです。

全てのイベントについて、そのイベントが終わった直後に電気が通っている都市の数を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N,M $
- $ N+M\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ Q\ \le\ E\ \le\ 5\ \times\ 10^5 $
- $ 1\ \le\ U_i\ <\ V_i\ \le\ N+M $
- $ i\ \neq\ j $ ならば、 $ U_i\ \neq\ U_j $ または $ V_i\ \neq\ V_j $
- $ 1\ \le\ X_i\ \le\ E $
- $ X_i $ は相異なる

### Sample Explanation 1

はじめ、全ての都市に電気が通っています。 - $ 1 $ 番目のイベントによって地点 $ 5 $ と地点 $ 10 $ を結ぶ電線 $ 3 $ が切れます。 - これにより、都市 $ 5 $ に電気が通らなくなり、電気が通っている都市の数は $ 4 $ となります。 - $ 2 $ 番目のイベントによって地点 $ 2 $ と地点 $ 9 $ を結ぶ電線 $ 5 $ が切れます。 - $ 3 $ 番目のイベントによって地点 $ 3 $ と地点 $ 6 $ を結ぶ電線 $ 8 $ が切れます。 - これにより、都市 $ 2,3 $ に電気が通らなくなり、電気が通っている都市の数は $ 2 $ となります。 - $ 4 $ 番目のイベントによって地点 $ 1 $ と地点 $ 8 $ を結ぶ電線 $ 10 $ が切れます。 - $ 5 $ 番目のイベントによって地点 $ 4 $ と地点 $ 10 $ を結ぶ電線 $ 2 $ が切れます。 - $ 6 $ 番目のイベントによって地点 $ 1 $ と地点 $ 7 $ を結ぶ電線 $ 7 $ が切れます。 - これにより、都市 $ 1 $ に電気が通らなくなり、電気が通っている都市の数は $ 1 $ となります。

## 样例 #1

### 输入

```
5 5 10
2 3
4 10
5 10
6 9
2 9
4 8
1 7
3 6
8 10
1 8
6
3
5
8
10
2
7```

### 输出

```
4
4
2
2
2
1```

# 题解

## 作者：DengDuck (赞：6)

首先我们考虑如何处理加边的问题，发现可以利用并查集维护。

并可以写出以下代码：

```cpp
LL find(LL x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void merge(LL x,LL y)
{
	LL fx=find(x),fy=find(y);
	if(is[fy]&&!is[fx])is[fx]=1,cnt+=sz[fx];
	if(!is[fy]&&is[fx])is[fy]=1,cnt+=sz[fy];
	if(fx==fy)return;
	fa[fy]=fx,sz[fx]+=sz[fy];
}
```

其中 `is` 表示某个城市作为根，是否链接了某个电气厂。

`sz` 表示某个树中城市的数量，注意不包含电气厂。

如果我们发现两树合并时会使其中某个 `is` 值变化，则可以在原答案减去得到电气厂的这个树的城市数，即 `sz`。

那么删除怎么做呢？我们把它离线下来，反过来做，就变成加边了。

这个技巧非常经典。

```cpp
#include<bits/stdc++.h>
#define LL int
using namespace std;
const LL N=2e6;
LL n,m,e,q,x[N],y[N],d[N],vis[N],fa[N],sz[N],is[N],cnt,ans[N];
LL find(LL x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void merge(LL x,LL y)
{
	LL fx=find(x),fy=find(y);
	if(is[fy]&&!is[fx])is[fx]=1,cnt+=sz[fx];
	if(!is[fy]&&is[fx])is[fy]=1,cnt+=sz[fy];
	if(fx==fy)return;
	fa[fy]=fx,sz[fx]+=sz[fy];
}
int main()
{
	scanf("%d%d%d",&n,&m,&e);
	for(int i=1;i<=e;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&d[i]);
		vis[d[i]]=1; 
	}
	for(int i=1;i<=n;i++)
	{
		sz[i]=1;
	}
	for(int i=1;i<=m;i++)
	{
		is[i+n]=1;
	}
	for(int i=1;i<=n+m;i++)
	{
		fa[i]=i;
	}
	cnt=0;
	for(int i=1;i<=e;i++)
	{
		if(vis[i]==0)//维护出原问题最后的图的并查集
		{
			merge(x[i],y[i]);
		}
	}
	for(int i=q;i>=1;i--)//反方向加边
	{
		ans[i]=cnt;
		merge(x[d[i]],y[d[i]]);
	}
	for(int i=1;i<=q;i++)
	{
		printf("%d\n",ans[i]);
	}
}
```

---

## 作者：封禁用户 (赞：2)

## 分析

考虑倒着维护答案。

很显然，我们倒着维护答案的时候，是只有加边，没有删边操作的。所以我们能够联系无向边直接想到并查集。每次合并两个集合的时候，我们尽量以发电站为基准点，这样方便答案的转移。定义 $\mathit{cnt}_{i}$ 表示以 $i$ 为基准点的集合 $i$ 中，一共有 $\mathit{cnt}_{i}$ 个地点。如果合并的两个集合里，有一个的基准点 $x$ 为发电站，另一个基准点 $y$ 不为发电站，则我们可以在 $cnt_y$ 转移至 $cnt_x$ 的同时，将当前的答案增加 $cnt_y$。可以保证，在尽量使基准点为发电站的情况下，基准点不为发电站的集合必定不会有一个点有被供电。

注：在每个询问之后，我们还需要将这个询问之前删掉的边加上哦。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
const int N=2e6+10;
PII edge[N];
int n,m,e,q;
int Q[N],vis[N];
int fa[N],ANS[N],cnt[N],now_ans;//now_ans即每个询问的答案 
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void get(int a,int b){
	int x=find(a),y=find(b);
	if(x==y) return ;
	else if(x>n){
		cnt[x]+=cnt[y],fa[y]=x;
		if(y<=n) now_ans+=cnt[y];
		cnt[y]=0;
	}
	else if(x<=n){
		cnt[y]+=cnt[x],fa[x]=y;
		if(y>n) now_ans+=cnt[x];
		cnt[x]=0;
	}
	return ;
}
void read(){
	cin>>n>>m>>e;
	for(int i=1;i<=e;i++)
		cin>>edge[i].x>>edge[i].y;
	cin>>q;
	for(int i=1;i<=q;i++)
		cin>>Q[i],vis[Q[i]]=1;
	for(int i=1;i<=n+m;i++)
		fa[i]=i,cnt[i]=1;
	return ;
}
void solve(){
	for(int i=1;i<=e;i++)
		if(!vis[i]) get(edge[i].x,edge[i].y);
	for(int i=q;i>=1;i--) 
		ANS[i]=now_ans,get(edge[Q[i]].x,edge[Q[i]].y);
	for(int i=1;i<=q;i++) 
		cout<<ANS[i]<<"\n";
	return ; 
}
signed main(){
	read(),solve();
	return 0;
}
```


---

## 作者：CQ_Bab (赞：1)

# 思路
一眼并查集，我们首先可以把所有的边先删去然后我们对于一个询问将他的答案算完后在把这条边加上即可，就是和[ P1197 [JSOI2008] 星球大战 ](https://www.luogu.com.cn/problem/P1197)差不多，然后我们就来想一下如何统计答案。

我们首先在对于每一次合并时都把祖先大的连向祖先小的，那么我们若有两个要连的点有一个已经通电则可把没通电的那一方的所有点加上，然后再把祖先小的连向祖先大的。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;--i)
const int N=5e5+10;
int f[N],x[N],y[N];
int fa[N],n,q,siz[N];
int res[N],m,e;
int shan[N];
int find(int x) {
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
signed main() {
	cin>>n>>m>>e;
	rep(i,1,e) cin>>x[i]>>y[i];
	cin>>q;
	rep(i,1,q) {
		cin>>shan[i];
		f[shan[i]]=1;
	}
	rep(i,1,m+n) {
		fa[i]=i;
		siz[i]=1;
	}
	int cnt=0;
	rep(i,1,e) {
		if(!f[i]) {
			int tx=find(x[i]),ty=find(y[i]);
			if(tx!=ty) {
				if(tx>n&&ty>n) {
					fa[tx]=ty;
					siz[ty]+=siz[tx];
					siz[tx]=0;
				} else {
					if(ty>n) {
						cnt+=siz[tx];
						fa[tx]=ty;
						siz[ty]+=siz[tx];
						siz[tx]=0;
					} else if(tx>n) {
						cnt+=siz[ty];
						fa[ty]=tx;
						siz[tx]+=siz[ty];
						siz[ty]=0;
					} else {
						fa[tx]=ty;
						siz[ty]+=siz[tx];
						siz[tx]=false;
					}
				}
			}
		}
	}
	rep1(i,q,1) {
		res[i]=cnt;
		int tx=find(x[shan[i]]),ty=find(y[shan[i]]);
		if(tx==ty) continue;
		if(tx>n&&ty>n) {
			fa[tx]=ty;
			siz[ty]+=siz[tx];
			siz[tx]=0;
		} else {
			if(ty>n) {
				cnt+=siz[tx];
				fa[tx]=ty;
				siz[ty]+=siz[tx];
				siz[tx]=0;
			} else if(tx>n) {
				cnt+=siz[ty];
				fa[ty]=tx;
				siz[tx]+=siz[ty];
				siz[ty]=0;
			} else {
				fa[tx]=ty;
				siz[ty]+=siz[tx];
				siz[tx]=false;
			}
		}
	}
	rep(i,1,q) cout<<res[i]<<endl;
	return false;
}
```

---

## 作者：Smg18 (赞：1)

[更~~差~~的阅读体验。](https://www.luogu.com.cn/blog/smz18/solution-at-abc264-e)

## 做法：

+ 地方通电，与该点是否与发电站有关。那么该问题模块可以抽象为**并查集**，并使用图来维护。

+ 注意，因为是**并查集**，我们算法是离线的。

+ 顺序删边使用逆序加边，所以我们要存好删除的边。

## 有关改变数量的重点思路：

+ 如果不通电 $u$ 连接不通电 $v$ 不会增加数量。

+ 如果通电 $u$ 连接通电 $v$ 不会增加数量。

+ 如果通电 $u$ 连接不通电 $v$ 会改变通电数量，并且与 $v$ 连通点都可以通电。

## 详情见代码：

```cpp
#include<bits/stdc++.h>//万能头？
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e6+10,NN=1e4+10;
ll n,m,k,len,T;
ll minn=INT_MAX,maxn=0;
ll arr[N],c[N],q,x[N],y[N],vis[N],cnt,ans[N];
ll fa[N];
vector<ll> g[N];//建边

ll find(ll x){
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[x]);
}
void uu(ll u,ll v){
	ll x=find(u);//并查集建立 
	ll y=find(v);
    //可能出现电站连城市
	if(x<y)fa[x]=y;
	else{
		fa[y]=x;
	}
}
void dfs(int x,int y){
	vis[x]=1;
	for(int i = 0;i<g[x].size();i++){
		ll t=g[x][i];
		if(vis[t]==0){
			uu(t,y);//连通
			cnt++;
			dfs(t,y);
		}
	}
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n+m;i++)fa[i]=i;//并查集初始化 
	for(int i=1;i<=k;i++)cin>>x[i]>>y[i];
	cin>>q;
	for(int i = 1;i<=q;i++){//存删边，记为1
		cin>>c[i];
		arr[c[i]]=1;
	}
   //构造，并标记
	for(int i = 1;i<=k;i++){//逆序加边
		if(arr[i]==0){
			int u = x[i],v=y[i];
			uu(u,v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		
	}
	for(int i = 1;i<=n+m;i++){
		if(n+1<=find(i)){
			vis[i]=1;
			if(i<=n)cnt++;//统计有连接电站数
		}
	}
	int e=0;//记录答案数，方便输出
	for(int i =q;i>=1;i--){
		int u = x[c[i]],v=y[c[i]];
		g[u].push_back(v);
		g[v].push_back(u);
		ans[++e]=cnt;
        //一个通，一个不通
		if(find(v)>n^find(u)>n){
			vis[u]=vis[v]=1;
			if(find(u)>=n+1)swap(u,v);
			cnt++;
			uu(u,v);
			dfs(u,v);
		}
	}
	for(int i = e;i>=1;i--)cout<<ans[i]<<endl;//输出
	return 0;
}
```

---

## 作者：Hell0_W0rld (赞：1)

# [abc264e](https://atcoder.jp/contests/abc264/tasks/abc264_e) Solution

## 题目大意
给定 $N+M$ 点 $E$ 边的无向图，$Q$ 个问询，每一次删掉第 $X$ 条边，操作完后问 $1\sim N$ 中有几个点和 $N+1\sim N+M$ 中的点有连边。
## 解题思路
在线查询删边不太好做，我们逆序回答问题，变成了加边操作，就可以简单地用并查集维护。

我们再维护并查集的 `merge()` 操作的时候，如果一个无电集合和有电集合合并，注意更新答案。所以还要维护 $k$ 所在并查集的大小。

推荐题目：[P1197 \[JSOI2008\] 星球大战](https://www.luogu.com.cn/problem/P1197)

最后，注意一下编号：边从 $1$ 开始编号。
## Talk is cheap, show my code.
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define repD(i,u,E) for(register ll i=hd[u];i;i=E[i].nxt)
#define all(x) x.begin(),x.end()
/*
If there're more than one test case, you must remember to clear the arrays.
If you debug for a long time, you can rewrite the code.
Remember code modularity.
Please keep the code clear, so that you can debug easily.
*/
using namespace std;
void upd_s(ll&x,ll v){x=min(x,v);}
void upd_b(ll&x,ll v){x=max(x,v);}
const ll N=200009;
ll id[N];
ll root(ll u){
	return id[u]==u?u:id[u]=root(id[u]);
} 
bool ele[N];
ll cnt,sz[N];
void merge(ll u,ll v){
	ll ru=root(u),rv=root(v);
	if(ru==rv)return;
	if(!ele[ru]&&ele[rv]){
		cnt+=sz[ru];
	}
	else if(!ele[rv]&&ele[ru]){
		cnt+=sz[rv];
	}
	id[rv]=ru;
	ele[ru]|=ele[rv];
	sz[ru]+=sz[rv];
}
const ll E=500009;
ll x[E],u[E],v[E],ans[E]; 
int main(){
	ll n,m,e,q;cin>>n>>m>>e;
	rep(i,1,n+m)id[i]=i,sz[i]=1,ele[i]=(i>n);
	cnt=m;
	rep(i,1,e)cin>>u[i]>>v[i];
	cin>>q;
	rep(i,1,q)cin>>x[i];
	set<ll> s;
	rep(i,1,q)s.insert(x[i]);
	rep(i,1,e){
		if(!s.count(i)) merge(u[i],v[i]);
	}
	Rep(i,1,q){
		ans[i]=cnt-m;
		merge(u[x[i]],v[x[i]]);
	}
	rep(i,1,q)cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：WaterSun (赞：1)

# 思路

一道很经典的题，运用了一种叫「时光倒流」的技巧。

「时光倒流」本质上就是将所有删边（或删点）的操作，通过倒序循环求值的方式转化为加边（或加点）。

「时光倒流」具体实现通常伴随着并查集出现，维护一个连通块的某种性质。

首先，我们需要将所有从始至终没有删过的边加入并查集。在这里，我们的并查集不仅仅要维护某个点 $i$ 的祖先 $f_i$，还要维护某个点 $i$ 所在的连通块是否有电，如果有电记作 $st_i = 1$，否则记作 $st_i = 0$；以及某个点 $i$ 所在连通块的大小 $sz_i$。

那么，我们就可以在合并的时候维护这些东西，以及答案。假设当前我们要合并 $x,y$ 所在的连通块。我们可以先找到它们的祖先，记作 $a,b$，不难发现，如果合并两个连通块会对答案产生贡献，当且仅当其中有一个连通块有电，另一个没电，分类讨论即可。

1. $st_a = 0,st_b = 1$，说明在合并两个连通块后，$x$ 所在联通块中的所有节点都将变为有电，所以，我们可以将 $st_a \leftarrow 1,ans \leftarrow ans + sz_a$。

2. $st_a = 1,st_b = 0$，同理，将 $st_b \leftarrow 1,ans \leftarrow ans + sz_b$。

最后维护一下 $sz$ 和 $f$ 值的变化即可。

# code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 5e5 + 10;
int n,m,e,q,sum;
int f[N],sz[N],del[N],ans[N];
bool st[N],vis[N];
pii g[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int find(int x){
	if (f[x] != x) return f[x] = find(f[x]);
	return f[x];
}

inline void merge(int x,int y){
	int a = find(x);
	int b = find(y);
	if (!st[a] && st[b]){
		st[a] = true;
		sum += sz[a];
	}
	else if (st[a] && !st[b]){
		st[b] = true;
		sum += sz[b];
	}
	if (a == b) return;
	f[a] = b;
	sz[b] += sz[a];
}

int main(){
	n = read();
	m = read();
	e = read();
	for (re int i = 1;i <= e;i++){
		g[i].fst = read();
		g[i].snd = read();
	}
	for (re int i = 1;i <= n;i++) sz[i] = 1;
	for (re int i = 1;i <= n + m;i++) f[i] = i;
	for (re int i = n + 1;i <= n + m;i++) st[i] = true;//所有发电站都是有电的 
	q = read();
	for (re int i = 1;i <= q;i++){
		del[i] = read();
		vis[del[i]] = true;
	}
	for (re int i = 1;i <= e;i++){
		if (!vis[i]) merge(g[i].fst,g[i].snd);
	}
	for (re int i = q;i;i--){
		ans[i] = sum;
		merge(g[del[i]].fst,g[del[i]].snd);
	}
	for (re int i = 1;i <= q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

题目大意：一个国家 $n$ 个普通城市 $m$ 个发电站，$e$ 条边连接两个地点。如果一个城市和发电站之间有路径连接，那么称这个城市有电。    
现在有 $q$ 次操作，每次操作删掉一条边（删除操作不会在下一次询问时恢复），问删掉这条边后还有电的城市的数量。      
首先如何判断一个城市是否有电呢？我们可以使用并查集维护。     
但更棘手的问题是：如何处理断边的问题？     
其实我们可以把询问倒过来处理，改断边为加边。      
先把询问记录下来，把询问中断掉的边全部断掉，然后从最后一个询问开始回答。     
每做完一个回答，把当前的边重新加回去，再接着处理下一个（其实在原来的问题列表中是上一个）问题。    
最后把问题对应的答案对应地输出即可。
```cpp
#include<stdio.h>
int n,m,e,q,a[500005],b[500005],which,first[200005],num,
father[200005],question[500005],ans[500005],dq,size[200005];
bool f[500005],have[200005];
int find(int where)
{
    if(where==father[where]) return where;
    return father[where]=find(father[where]);
}
void merge(int x,int y)
{
    int fax=find(x),fay=find(y);
    if(fax==fay) return;
    else if((!have[fax])&&have[fay])
    have[fax]=1,dq+=size[fax],father[fax]=fay,size[fay]+=size[fax];
    else if((!have[fay])&&have[fax])
    have[fay]=1,dq+=size[fay],father[fay]=fax,size[fax]+=size[fay];
    else father[fax]=fay,size[fay]+=size[fax];
}
int main()
{
    scanf("%d%d%d",&n,&m,&e);
    for(int i=1;i<=n;i++) father[i]=i,size[i]=1;
    for(int i=n+1;i<=n+m;i++) father[i]=i,have[i]=size[i]=1;
    for(int i=1;i<=e;i++) scanf("%d%d",&a[i],&b[i]);
    scanf("%d",&q);
    for(int i=1;i<=q;i++) scanf("%d",&question[i]),f[question[i]]=1;
    for(int i=1;i<=e;i++) if(!f[i]) merge(a[i],b[i]);
    for(int i=q;i>=1;i--)
    ans[i]=dq,merge(a[question[i]],b[question[i]]);
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
}
```

---

## 作者：yqr123YQR (赞：0)

### 题意
现给定一 $N+M$ 点 $E$ 边无向图及 $Q$ 次断边操作，问前 $i$ 次操作后，有多少个非特殊点（即城市）所处连通块中有特殊点（即发电站）。

### 思路
断边不好维护，这种断边的题一般都是用并查集 + 操作离线来完成。用离线的方式，我们可以从结束时刻的状态开始，逐步反推，将断边转化为连边。
而连边操作就可以用并查集以接近 $O(1)$ 的时间复杂度来快速维护每个连通块的状态。

接下来，我们考虑每个连通块要维护哪些信息。

首先，我们要用 $vis$ 记录当前块内有无发电站；其次，为方便统计，还要记录当前块内未通电的点数（城市数）$size$。这些都可以在 $\operatorname{merge}$ 操作时 $O(1)$ 合并。

合并时，只有在一个块通电，一个块未通电时，才会影响通电点数。此时，统计答案的 $cnt$ 就要加上两个块总的未通电点数，即。

总时间复杂度：$O(N+M+(E+Q)\alpha(n))$，$\alpha(n)$ 为反阿克曼函数。

### 代码
我认为我的 $\operatorname{merge}$ 操作是写的较为简洁的，~~自夸 ing~~
```cpp
#include<stdio.h>
#define maxn 200000
#define maxm 500000
struct edge {int st, to;}e[maxm + 5];
int n, m, k, q, cnt, x[maxm + 5], fath[maxn + 5], size[maxn + 5]/*当前连通块内未通电的点数*/, ans[maxm + 5];
bool vis[maxn + 5]/*当前块是否通电*/, flag[maxm + 5];
int get_father(int x)
{
	if(fath[x] != x) fath[x] = get_father(fath[x]);
	return fath[x];
}
void merge(int x, int y)
{
	int fx = get_father(x), fy = get_father(y);
    if(fx == fy) return;
	if(vis[fx] != vis[fy]) cnt += size[fx] + size[fy];//即一个块有发电站，一个块没有发电站
	fath[fx] = fy;
	vis[fy] |= vis[fx];
	if(vis[fy]) size[fy] = 0;//全部通电
	else size[fy] += size[fx];//均未通电
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n + m; i++)
	{
		fath[i] = i;
		if(i > n) vis[i] = true;//发电站
		else size[i] = 1;//城市
	}
	for(int i = 1; i <= k; i++) scanf("%d%d", &e[i].st, &e[i].to);
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		scanf("%d", &x[i]);
		flag[x[i]] = true;
	}
	for(int i = 1; i <= k; i++)
	{
		if(!flag[i]) merge(e[i].st, e[i].to);//处理最终状态，连上从未被删的边
	}
	for(int i = q; i; i--)//反推
	{
		ans[i] = cnt;
		merge(e[x[i]].st, e[x[i]].to);//先记录答案，再连边。因为统计答案原本是在操作之后，反过来就在操作之前。
	}
	for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：落花月朦胧 (赞：0)

这个题是 $2022$ 年 $8$ 月 $13$ 日在 `abc264` 场切的，第一次切 `E` 题，今天是 $2023$ 年 $7$ 月 $31$ 日， 时隔一年再见此题，特此纪念。还记得当时上课讲的并查集，做了 [星球大战](https://www.luogu.com.cn/problem/P1197) 这个题，和这个题有异曲同工之妙。

# 题意

有 $n$ 个城市和 $m$ 个发电站，有一些线路，有电的定义是只要一个城市与任何一个有电的城市有道路，这个城市就可以说是有电的。现在我们要让一些线路断掉，实时查询有多少个城市还在供电。

首先有一个很重要的思想，我们发现断掉不太好处理，反过来，如果我们从终止情况倒过来考虑，**断掉就被转换成了连接**，此时就可以用**并查集**进行维护。

首先我们把**一定不会断掉的边**，即从头到尾都是连接的边给用并查集连上，这就是全部会断掉的电路断掉后的情况。

然后我们把询问**倒过来看**，从最后一个询问开始考虑。只要连接的两端有一个有电，另一个没有电，这样就是导致对答案的贡献，答案就加上没有电那部分的连通块的大小。注意，**无论对答案有没有贡献都要用并查集套在一起**。

发现多个发电站是没有用的，我们把它们全部和任何一个发电站连边，判断一个城市有没有电就可以看是否和这个固定的发电站在用一个连通块里就行了。

代码还有一些细节，比如我们计算终止情况的时候要减去连上的 $m$ 个发电站，再比如我们的 ans 数组应该不停的和上一个累加，等等。

# Code

并查集是别人的板子。

```cpp
#include <bits/stdc++.h>

using i64 = long long;
constexpr int inf = 1E9;

struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n, m, e;
    std::cin >> n >> m >> e;

    std::vector<std::pair<int, int>> adj(e);
    for (int i = 0; i < e; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[i] = {u, v};
    }

    int q; std::cin >> q;
    std::vector<int> que(q + 1);
    std::map<int, int> mp;
    for (int i = 1; i <= q; i++) {
        std::cin >> que[i];
        que[i]--;
        mp[que[i]] = 1;
    }

    DSU d(n + m);
    for (int i = n; i < n + m - 1; i++) {
        d.merge(i, i + 1);
    }
    int ans = 0;
    std::vector<int> Ans(q + 1);
    for (int i = 0; i < e; i++) {
        if (!mp[i]) {
            d.merge(adj[i].first, adj[i].second);
        }
    }
    Ans[q] = d.size(n) - m;
    for (int i = q; i; i--) {
        int p = que[i];
        int u = adj[que[i]].first, v = adj[que[i]].second;
        if (i + 1 <= q) Ans[i] += Ans[i + 1];
        if (!d.same(u, n) && d.same(v, n)) {
            Ans[i - 1] += d.size(u);
        }
        if (d.same(u, n) && !d.same(v, n)) {
            Ans[i - 1] += d.size(v);
        }
        d.merge(u, v);
    }

    for (int i = 1; i <= q; i++) std::cout << Ans[i] << "\n";
    
    return 0;
}
```

---

## 作者：stupid_collie (赞：0)

考虑使用并查集求解。

不难发现，每次拆掉一条边，就有可能将原来的一个连通块一分为二。由此，我们可以倒过来考虑，先预先拆掉所有的边，再一个个将边加回去，逐个统计答案。对于每一个里边有发电站的连通块，将其标记为 `true`。在合并并查集的时候，若其中之一为 `true`，就可以将另外一个也标记成 `true`，再将两个点所在连通块的大小相加。

这里记得要判断当前边的两个端点已经在同一个连通块中的情况。最后可以用一个 `stack` 倒序输出。

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>

const int maxn = 5e5 + 9;
using namespace std;

int n,m,e,op[maxn];
pii ed[maxn];
bool vis[maxn],brk[maxn];

vector<int> g[maxn>>1];

int fa[maxn],cnt[maxn],tag[maxn];

void dfs(int u,int tg){
  tag[u] = tg;
  if(u>n)vis[tg] = true;
  else cnt[tg]++;
  for(int i = 0;i<g[u].size();i++){
    int v = g[u][i];
    if(!tag[v])dfs(v,tg);
  }
}

int getf(int x){
  if(fa[x]==x)return x;
  return fa[x] = getf(fa[x]);
}

void merge(int x,int y){
  int fx = getf(x),fy = getf(y);
  fa[fx] = fy;
  cnt[fy] += cnt[fx];

  if(vis[fx])vis[fy] = true;
}

int main(){
  scanf("%d%d%d",&n,&m,&e);
  for(int i = 1,u,v;i<=e;i++){
    scanf("%d%d",&u,&v);
    ed[i] = make_pair(u,v);
  }

  int q;
  scanf("%d",&q);
  for(int i = 1;i<=q;i++)scanf("%d",&op[i]),brk[op[i]] = true;;
  for(int i = 1,u,v;i<=e;i++){
    if(!brk[i]){
      u = ed[i].first,v = ed[i].second;
      g[u].push_back(v),g[v].push_back(u);
    }
  }

  int idx = 0,ans = 0;
  for(int i = 1;i<=n+m;i++){
    if(!tag[i]){
      dfs(i,++idx);
      if(vis[idx]){
        ans += cnt[idx];
      }
    }
  }

  for(int i = 1;i<=idx;i++)fa[i] = i;

  stack<int> st;
  for(int i = q,u,v;i>=1;i--){
    u = tag[ed[op[i]].first],v = tag[ed[op[i]].second];
    st.push(ans);
    if(i==1)continue;

    u = getf(u),v = getf(v);
    if(u==v)continue;
    if(vis[u]&&!vis[v])
      ans += cnt[v];
    else if(vis[v]&&!vis[u])
      ans += cnt[u];

    merge(u,v);
  }

  while(st.size())
    printf("%d\n",st.top()),st.pop();
}

```

---

## 作者：Light_az (赞：0)

## 并查集好题

第一眼看这道题目感觉可以使用模拟，但是看到数据范围后知道这个做法一定会超时，因此我们可以巧妙地采用并查集思想来完成这道题目。

## 思路

对于删边操作，我们可以将顺序反过来，变成了加边操作，然后每次加边进行特判。首先定义数组来表示：并查集的父亲编号，该节点的子节点数量，该节点是否与发电站联通。然后对于每一次 $(u,v)$ 的加边操作，我们可以分类讨论：

- 当 $u = v$ 时，跳过因为该操作没有意义。

- 当 $u > v$ 时，交换节点因为我们要对节点进行并查集操作，所以 $u$ 一定小于 $v$。

- 上述操作后如果 $u$ 不与发电站联通且 $v$ 与发电站联通，那么答案加上 $u$ 的子节点数量。

- 最后将 $u$ 的父亲编号更改为 $v$，并且将 $v$ 的子节点数加上 $u$ 的子节点数。

然后倒叙输出每一次操作后的结果即可通过本题。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define Tr(v,e) for(int v:e)
#define D double
#define ps push_back
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10,NN=1e4+10;
ll n,m,k,x,y,u[N],v[N],w,cnt=0,ans[N],t=0,l,r,len,T;
ll mini=INT_MAX,maxi=0,p=998244353;
string s1,s2;
ll f[N],c[N],S[N],flag[N],E,Q,id[N],vis[N];
void add(ll u,ll v){
	if(u==v) return ;//跳过 
	if(u>v) swap(u,v);//交换 
	if(!flag[u]&&flag[v]) cnt+=S[u];//链接后 u 与发电站联通，答案增加 
	f[u]=v,S[v]+=S[u];//并查集后操作 
}
ll find(ll x){//并查集查询 
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
int main(){
	cin>>n>>m>>E;
	F(i,1,n+m){
		f[i]=i,S[i]=1;//初始化 
		if(i>n) flag[i]=1;//发电站已经与发电站（自己）联通 
	} 
	F(i,1,E) cin>>u[i]>>v[i];
	cin>>Q;
	F(i,1,Q) cin>>id[i],vis[id[i]]=1;//先不删边 
	F(i,1,E){
		if(!vis[i]){//建图且该边没有被删除 
			x=find(u[i]),y=find(v[i]);
			add(x,y);//操作 
		}
	}
	ans[Q]=cnt;//倒叙记录答案 
	for(int i=Q;i>1;i--){
		x=find(u[id[i]]),y=find(v[id[i]]);
		add(x,y);//操作 
		ans[i-1]=cnt;//记录答案 
	}
	F(i,1,Q) cout<<ans[i]<<"\n";//已经倒叙记录，因此可以正序输出 
	return 0;
}
```


---

## 作者：allenchoi (赞：0)

### 科技：  
并查集  
### 思路：  
原题是把图进行分裂操作，这个不好处理，但是如果倒过来，就变成合并了，容易很多。把所有会被删掉的边打上标记，最先只对没有标记的边的两个端点进行合并，在将被删掉的边倒序进行合并操作。关于实现方法，可以用并查集维护连通块大小及是否有电，每次合并时看一下是否一个连通块有电，另一个没有，把答案加上对应连通块大小即可。  
### 代码：  
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5e5 + 5;
int n,m,e,q,t1,t2,cnt,a[N],b[N],vis[N],x[N],f[N],flag[N],siz[N],ans[N];
int find(int x)
{
	if(f[x] == x) return x;
	return f[x] = find(f[x]);
}
void merge(int x,int y)
{
	if(x == y) return ;
	if(flag[y]) swap(x,y);
	if(flag[x] && !flag[y]) cnt += siz[y];
	f[y] = x,siz[x] += siz[y];
}
int main()
{
	scanf("%d%d%d",&n,&m,&e);
	for(int i = 1;i <= n;i++)
	{
		f[i] = i;
		siz[i] = 1;
	}
	for(int i = n + 1;i <= n + m;i++)
	{
		f[i] = i;
		flag[i] = 1;
		siz[i] = 1;
	}
	for(int i = 1;i <= e;i++) scanf("%d%d",&a[i],&b[i]);
	scanf("%d",&q);
	for(int i = 1;i <= q;i++)
	{
		scanf("%d",&x[i]);
		vis[x[i]] = 1;
	}
	for(int i = 1;i <= e;i++)
		if(!vis[i])
		{
			t1 = find(a[i]),t2 = find(b[i]);
			merge(t1,t2);
		}
	ans[q] = cnt;
	for(int i = q;i > 1;i--)
	{
		t1 = find(a[x[i]]),t2 = find(b[x[i]]);
		merge(t1,t2);
		ans[i - 1] = cnt;
	}
	for(int i = 1;i <= q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：lsj2009 (赞：0)

### Problem

给定 $n+m$ 个点和 $e$ 条边，下标为均从 $1$ 开始。进行 $q$ 次操作，表示断掉一条边（操作是永久性的），求每次操作之后有几个下标 $1\sim n$ 的点与下标 $n+1\sim n+m$ 的点连通。

link-><https://atcoder.jp/contests/abc264/tasks/abc264_e>。

### Solution

经典操作：删边比较麻烦，考虑逆序操作，每次加边，考虑使用并查集维护，每次合并时，更新集合大小和该集合内是否有下标 $n+1\sim n+m$ 的点，顺手更新当前满足条件的点的数量。由于维护了集合大小，不妨使用路径压缩按轶合并。复杂度 $O((n+m)\alpha(n+m)+e)$。需要注意的一点是，合并时需要判断两点是否在同一集合，否则集合大小会出问题。

### Code


``` cpp
#include<bits/stdc++.h>
#define INF 0x7fffffff
#define inf 0x3f3f3f3f
#define inf2 0x3f3f3f3f3f3f3f3f
#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e6+5;
int fa[N],used[N],vis[N],s[N],qu[N],x[N],n,m,e,q,ans;
vector<PII> edge;
int find(int x) {
	if(fa[x]!=x)
		fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int x,int y) {
	x=find(x); y=find(y);
  	if(s[y]>s[x])
    	swap(x,y);
	if(x!=y) {
		if(used[x]&&!used[y])
			ans+=s[y];
		if(!used[x]&&used[y])
			ans+=s[x];
		used[x]=used[x]|used[y];
		s[x]+=s[y];
		fa[y]=x;		
	}
}
signed main() {
	scanf("%lld%lld%lld",&n,&m,&e);
	_for(i,1,n)
		fa[i]=i,s[i]=1,used[i]=0;
	_for(i,n+1,n+m)
		fa[i]=i,s[i]=1,used[i]=1;
	_for(i,1,e) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		edge.push_back({u,v});
	}
	scanf("%lld",&q);
	_for(i,1,q)
		scanf("%lld",&x[i]),vis[--x[i]]=1;
	_for(i,0,e-1) {
		if(!vis[i])
			merge(edge[i].first,edge[i].second);
	}
	_rep(i,q,1) {
//		printf("after query %d:\n",i);
//		_for(i,1,n+m)
//			printf("%d ",find(i));
//		puts("");
		qu[i]=ans;
		merge(edge[x[i]].first,edge[x[i]].second);
	}
//	printf("Ans =\n");
	_for(i,1,q)
		printf("%lld\n",qu[i]);
	return 0;
}
```

---

