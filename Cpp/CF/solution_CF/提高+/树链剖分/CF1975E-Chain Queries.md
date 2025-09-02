# Chain Queries

## 题目描述

给定一棵有 $n$ 个顶点的树，顶点编号为 $1$ 到 $n$。初始时，每个顶点被染成白色或黑色。

你需要进行 $q$ 次操作：

- “u” —— 翻转顶点 $u$ 的颜色（如果原来是白色，则变为黑色；如果原来是黑色，则变为白色）。

每次操作后，你需要回答所有黑色顶点是否构成一条链。也就是说，是否存在两个黑色顶点，使得它们之间的简单路径经过且仅经过所有黑色顶点。特别地，如果只有一个黑色顶点，也视为构成一条链。如果没有黑色顶点，则不构成链。

## 说明/提示

在第二个测试用例中，顶点的颜色变化如下：

初始树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/d67482a066522c11f266b4eca3d7a1ef0055849d.png)

第一次操作翻转顶点 $4$ 的颜色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/4a07e30139deb2cb81867b3706db8e9ec51e4318.png)

第二次操作翻转顶点 $3$ 的颜色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/fd56e11f35468c4b51183822460fd341cde05e88.png)

第三次操作翻转顶点 $2$ 的颜色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/f1f02d1c42e642ef8cfd2174f0e71d8955cb85ac.png)

第四次操作翻转顶点 $5$ 的颜色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/72ebf27a994a252cc8de91446a4beacafa646ddb.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
2 1
1 0
1 2
1
5 4
1 0 0 0 0
1 2
1 3
1 5
3 4
4
3
2
5```

### 输出

```
No
No
Yes
Yes
No```

## 样例 #2

### 输入

```
4
5 3
1 1 1 1 1
3 5
2 5
3 4
1 5
1
1
1
4 4
0 0 0 0
1 2
2 3
1 4
1
2
3
2
1 1
1
1
1 1
0
1```

### 输出

```
Yes
No
Yes
Yes
Yes
Yes
No
No
Yes```

# 题解

## 作者：int08 (赞：20)

## 前言

啥？为啥我的做法跟大家都不一样？

我一直以为我这才是官方解法呢。

（其实差不多，但是我觉得自己这样还要妙一些）

## 题意

树上点染黑白色，每次修改一个点的染色状态，每次修改后询问所有黑点是否成链。

# Solution

如何判定链？这题给了我们一个很好的 Trick。

发现链的每个中间点度数为 $2$，端点度数为 $1$。

不过判定度数实际上是有难度的，比如说，我删去一个黑色点，它所有的儿子都更改了，这是难以修改的。

所以我们希望定义出一个只跟父亲节点相关的状态。

于是我们先定根，再定义初始每个点权值为 $0$，对于黑色点，给它自己权值 $-1$，它的父亲 $+1$。

这样每个节点的状态只与父亲相关，容易发现成链的只有如下两种情况：

1. 链从上到下，此时应该只有权值为 $1,-1$ 的点各一个，其余全为 $0$。

2. 链有两个方向往下，此时有权值为 $1,-1$ 的点各两个，而且权值为 $1$ 的两点中有一点是黑色的。

这大概是充要的，直接维护即可。

使用 `unordered_set<int>` 记录权值为 $-1,1$ 的点，复杂度严格线性。

~~不过由于 CF 优良传统我还是使用了 `set`。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,q,i,j;
int u,v;
vector<int> e[214514];
int f[214514],c[214514],val[214514],tong[414514];
set<int> one;
set<int>::iterator it;
void dfs(int u,int fa)
{
	f[u]=fa;
	for(auto v:e[u]) if(v!=fa) dfs(v,u);
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>q;
		for(i=1;i<=n;i++) cin>>c[i];
		for(i=1;i<n;i++) cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
		dfs(1,0);
		tong[n]=n+1;
		for(i=1;i<=n;i++) if(c[i])
		{
			int fa=f[i];
			tong[val[i]+n]--,tong[val[fa]+n]--;
			tong[--val[i]+n]++,tong[++val[fa]+n]++;
			if(val[fa]==1) one.insert(fa);
			if(val[i]==1) one.insert(i);
			if(val[fa]==2) one.erase(fa);
			if(val[i]==0) one.erase(i);
		}
		while(q--)
		{
			int x;
			cin>>x;
			i=x;int fa=f[i];
			if(c[i]) swap(i,fa),c[fa]^=1;
			else c[i]^=1;
			tong[val[i]+n]--,tong[val[fa]+n]--;
			tong[--val[i]+n]++,tong[++val[fa]+n]++;
			if(val[fa]==1) one.insert(fa);
			if(val[i]==1) one.insert(i);
			if(val[fa]==2) one.erase(fa);
			if(val[i]==0) one.erase(i);
			
			int tg=0;
			if(tong[n]==n-1&&tong[n-1]==1&&tong[n+1]==1) tg=1;
			if(tong[n]==n-3&&tong[n-1]==2&&tong[n+1]==2)
			{
				it=one.begin();u=*it,it++,v=*it;
				if((f[u]==v||f[v]==u)&&(c[u]||c[v])) tg=1;
			}
			cout<<(tg?"Yes":"No")<<endl;
		}
		for(i=0;i<=n+5;i++) e[i].clear(),f[i]=c[i]=val[i]=0;
		for(i=0;i<=2*n+5;i++) tong[i]=0;one.clear();
	}
	return 0;
 } 
```

---

## 作者：tuxuanming2024 (赞：11)

提供一种大力线段树做法。

注意到黑点构成一条链的充要条件是，有两个点度数为 $1$，其余为 $2$。于是我们考虑暴力维护所有点的度数。

具体地，每加入一个黑点，我们就将其度数改为直接与它相连的黑点个数，并把与它相连的所有黑点度数 $+1$。删除一个黑点同理。

由于要修改与一个点相连的所有点，我们考虑 BFS 序，这样一个点的儿子在线段树上是连续的。修改的时候可以区修儿子所对应的区间，单修父亲。

我们需要在每个线段树结点维护当前区间黑点个数，黑点度数的最小值，最小值个数，最大值。

需要注意的是，区间修改的时候不能对白点进行修改。于是在线段树更新一个结点的时候特判一下，如果这个结点内没有黑点，那么不进行修改。同样，在 pushup 的时候也特判一下当前结点是否有黑点。具体实现可以看代码。

复杂度 $O((n+q) \log n)$。

代码：

```cpp
#include <bits/stdc++.h>
#ifdef LOCAL
#include "txm/debug.h"
#endif
using namespace std;
typedef long long ll;
const int N=2e5+5,INF=0x3f3f3f3f;
int n,m,sign,p[N],c[N],prt[N],l[N],r[N],fp[N];
vector<int>e[N];
bool v[N];
struct node {int l,r,mi,cnt,mx,tag,sum;};
struct sgt
{
	node t[N<<2];
	void pushup(node &x,node lc,node rc)
	{
		x.sum=lc.sum+rc.sum;
		if(!x.sum) {x.mi=INF,x.mx=0; return;}
		x.mi=min(lc.mi,rc.mi),x.mx=max(lc.mx,rc.mx);
		if(lc.mi==rc.mi) x.cnt=lc.cnt+rc.cnt;
		else x.cnt=lc.mi<rc.mi?lc.cnt:rc.cnt;
	}
	void build(int x,int l,int r)
	{
		t[x].l=l,t[x].r=r,t[x].tag=0;
		if(l==r)
		{
			t[x].cnt=1,t[x].sum=c[fp[l]];
			if(t[x].sum) t[x].mx=t[x].mi=0;
			else t[x].mx=0,t[x].mi=INF;
			return;
		}
		int mid=(l+r)>>1; build(x<<1,l,mid),build(x<<1|1,mid+1,r);
		pushup(t[x],t[x<<1],t[x<<1|1]);
	}
	void upd(int x,int v) 
	{
		if(t[x].sum) t[x].tag+=v,t[x].mi+=v,t[x].mx+=v;
	}
	void pushdown(int x)
	{
		if(t[x].tag) upd(x<<1,t[x].tag),upd(x<<1|1,t[x].tag),t[x].tag=0;
	}
	void add(int x,int l,int r,int v)
	{
		if(r<t[x].l||l>t[x].r) return;
		if(l<=t[x].l&&r>=t[x].r) {upd(x,v); return;}
		pushdown(x),add(x<<1,l,r,v),add(x<<1|1,l,r,v);
		pushup(t[x],t[x<<1],t[x<<1|1]);
	}
	void modify(int x,int k,int v)
	{
		if(t[x].l==t[x].r)
		{
			if(v>=0) t[x].mi=t[x].mx=v,t[x].cnt=t[x].sum=1;
			else t[x].mi=INF,t[x].mx=0,t[x].sum=0;
			return;
		}
		pushdown(x); int mid=(t[x].l+t[x].r)>>1;
		modify(x<<1|(k>mid),k,v),pushup(t[x],t[x<<1],t[x<<1|1]);
	}
	int ask(int x,int l,int r)
	{
		if(r<t[x].l||l>t[x].r) return 0;
		if(l<=t[x].l&&r>=t[x].r) return t[x].sum;
		pushdown(x);
		return ask(x<<1,l,r)+ask(x<<1|1,l,r);
	}
}t;
void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>c[i],e[i].clear(),v[i]=0;
	for(int i=1,x,y;i<n;i++) cin>>x>>y,e[x].push_back(y),e[y].push_back(x);
	queue<int>q; q.push(1),p[1]=sign=1,v[1]=1,fp[1]=1;
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		l[x]=INF,r[x]=0;
		for(auto y:e[x]) if(!v[y])
		{
			prt[y]=x,p[y]=++sign,fp[sign]=y;
			l[x]=min(l[x],p[y]),r[x]=max(r[x],p[y]);
			q.push(y),v[y]=1;
		}
	}
	t.build(1,1,n);
	for(int i=1;i<=n;i++) if(c[i])
	{
		t.add(1,p[prt[i]],p[prt[i]],1);
		t.add(1,l[i],r[i],1);
	}
	while(m--)
	{
		int x,v; cin>>x;
		v=c[x]?-1:1;
		t.add(1,l[x],r[x],v);
		t.add(1,p[prt[x]],p[prt[x]],v);
		if(c[x]) t.modify(1,p[x],-1);
		else
		{
			int res=t.ask(1,l[x],r[x])+t.ask(1,p[prt[x]],p[prt[x]]);
			t.modify(1,p[x],res);
		}
		c[x]^=1;
		int mx=t.t[1].mx,mi=t.t[1].mi,cnt=t.t[1].cnt;
		if(t.t[1].sum==1) {cout<<"Yes\n"; continue;}
		if(mi==1&&mx<=2&&cnt==2) cout<<"Yes\n";
		else cout<<"No\n";
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin>>t; while(t--) solve();
	return 0;
}
```

---

## 作者：CharlieCai (赞：9)

### 题意

给定一棵 $n$ 个结点的树，第 $i$ 个点有颜色 $c_i$，其中 $c_i=0$ 为白色，$c_i=1$ 为黑色。有 $q$ 次询问，每次询问给定一个正整数 $u$，要求将结点 $u$ 的颜色反转，并判断修改后的树上的所有黑点是否构成一条链。询问不独立。

### 思路

- 由于这是一棵树，一个点只有一个父亲，所以当我们修改某个点的颜色时，我们可以很容易的维护与该点父亲有关的信息，但我们如果挨个修改其儿子的信息则会超时，因此在接下来关于判断黑点是否构成链的条件时，我们应该判断那些容易维护的信息。

- 首先，如果树上的黑点构成一条链，那他们必须是联通的。观察可得，一个黑点的连通块中有且只有一个点的父亲（即该块中所有黑点的公共祖先）不是黑色。因此如果构成链，则树上只有一个黑点父亲不是黑点。

- 其次，如果构成链，则不能有黑点与 $2$ 个或更多黑点相连。分两种情况讨论：一是父亲为黑点且拥有 $2$ 个或更多黑色儿子，二是父亲不为黑点但拥有 $3$ 个或更多黑色儿子。因此我们可以统计有 $2$ 个黑色儿子的黑色点数量和有 $3$ 个黑色儿子的黑色点数量，如果构成链，则前者不大于 $1$，若等于 $1$ 则该点父亲必须不为黑色；后者等于 $0$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 400005
using namespace std;
int T,n,qq,cnt,head[MAXN],c[MAXN],a[MAXN],cnta,cntb,cntc,b[MAXN],fa[MAXN];
queue<int>q;
struct Edge{
	int value,next;
}edge[MAXN];
void addedge(int u,int v){
	edge[++cnt].value=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
void dfs(int x,int father){
	fa[x]=father;
	if(c[x]==1)a[fa[x]]++;
	if(c[x]==1&&c[fa[x]]==0)cnta++;
	for(int i=head[x];i;i=edge[i].next){
		int y=edge[i].value;
		if(y!=fa[x]){
			dfs(y,x);
		}
	}
	if(c[x]==1){
		if(a[x]==2){
			cntc++;
			b[x]=1;
			q.push(x);
		}else if(a[x]>2){
			cntb++;
		}
	}
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&qq);
		while(!q.empty())q.pop();
		cnt=cnta=cntb=cntc=0;
		//cnta表示父亲不是黑色的黑色点数量
		//cntb表示有3个或更多黑色儿子的黑色点数量
		//cntc表示有2个黑色儿子的黑色点数量 
		for(int i=1;i<=n*2;i++){
			edge[i]=(Edge){0,0};
			head[i]=c[i]=b[i]=a[i]=0;
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&c[i]);
		}
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%lld%lld",&u,&v);
			addedge(u,v);
			addedge(v,u);
		}
		dfs(1,0);
		fa[n+1]=n+1;
		c[n+1]=0;
		for(int i=1;i<=qq;i++){
			int x;
			scanf("%lld",&x);
			if(c[x]==1){
				if(c[fa[x]]==0)cnta--;
				cnta+=a[x];
				if(a[x]>=3)cntb--;
				if(a[fa[x]]==3&&c[fa[x]]==1){
					cntb--;
					cntc++;
					b[fa[x]]=1;
					q.push(fa[x]);
				}
				if(a[x]==2){
					cntc--;
					b[x]=0;
				}
				if(a[fa[x]]==2&&c[fa[x]]==1){
					cntc--;
					b[fa[x]]=0;
				}
				c[x]=0;
				a[fa[x]]--;
			}else{
				if(c[fa[x]]==0)cnta++;
				cnta-=a[x];
				if(a[x]>=3)cntb++;
				if(a[fa[x]]==2&&c[fa[x]]==1){
					cntb++;
					cntc--;
					b[fa[x]]=0;
				}
				if(a[x]==2){
					cntc++;
					b[x]=1;
					q.push(x);
				}
				if(a[fa[x]]==1&&c[fa[x]]==1){
					cntc++;
					b[fa[x]]=1;
					q.push(fa[x]);
				}
				c[x]=1;
				a[fa[x]]++;
			}
			int tmp=n+1;
			if(!q.empty()){
				tmp=q.front();
				while(!b[tmp]){
					q.pop();
					if(q.empty())break;
					tmp=q.front();
				}
			}
			//若构成链，则cnta==1且cntb==0且cntc<=1且若cntc等于一，该点父亲不为黑色 
			if(cnta!=1||cntb>0||cntc>1||(cntc==1&&c[fa[tmp]]==1))printf("No\n");
			else printf("Yes\n");
		}
	}
	return 0;
}
```

---

## 作者：SFlyer (赞：6)

考虑黑色节点形成一条链的条件。

- 记自己是黑色的并且没有黑色的儿子的点的个数为 $cnt$。$cnt$ 显然合法，$cnt>2$ 显然不合法。因此我们 $cnt=2$，记这两个点为 $x,y$。

- $x$ 到 $y$ 的路径上都是黑色，并且总的黑色数目等于路径上的数目。

要维护单点修改和查询路径和。显然可以用树剖。因此我们得到了 $\mathcal{O}(n\log^2 n)$ 唐氏做法。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5+5;

ll n,m,w[N];
ll dfn[N],tot,top[N],fa[N],son[N],dep[N],siz[N],rnk[N],ff[N][22];
vector<int> g[N];
ll dat[N<<2],tag[N<<2];
void init(){
	tot=0;
	for (int i=1; i<=n; i++){
		dfn[i]=top[i]=fa[i]=son[i]=dep[i]=siz[i]=rnk[i]=0;
		g[i].clear();
		for (int j=0; j<22; j++){
			ff[i][j]=0;
		}
	}
	for (int i=1; i<=4*n+4; i++){
		dat[i]=tag[i]=0;
	}
}
void pu(int k){
	dat[k]=dat[k<<1]+dat[k<<1|1];
} 
void pd(int k,ll l,ll r){
	if (tag[k]){
		ll mid=l+r>>1;
		tag[k<<1]=tag[k<<1]+tag[k];
		tag[k<<1|1]=tag[k<<1|1]+tag[k];
		dat[k<<1]=dat[k<<1]+(mid-l+1)*tag[k];
		dat[k<<1|1]=dat[k<<1|1]+(r-mid)*tag[k];
		tag[k]=0;
	}
}
void bd(int k,int l,int r){
	tag[k]=0;
	if (l==r){
		dat[k]=w[rnk[l]];
		return;
	}
	int mid=l+r>>1;
	bd(k<<1,l,mid);
	bd(k<<1|1,mid+1,r);
	pu(k);
}
void upd(int k,int l,int r,int ql,int qr,ll ad){
	if (l>qr || r<ql){
		return;
	}
	if (ql<=l && r<=qr){
		tag[k]=tag[k]+ad;
		dat[k]=dat[k]+ad*(r-l+1);
		return;
	}
	pd(k,l,r);
	int mid=l+r>>1;
	upd(k<<1,l,mid,ql,qr,ad);
	upd(k<<1|1,mid+1,r,ql,qr,ad);
	pu(k);
}
ll qy(int k,int l,int r,int ql,int qr){
	if (l>qr || r<ql){
		return 0;
	}
	if (ql<=l && r<=qr){
		return dat[k];
	}
	pd(k,l,r);
	int mid=l+r>>1;
	ll vl=qy(k<<1,l,mid,ql,qr);
	ll vr=qy(k<<1|1,mid+1,r,ql,qr);
	return vl+vr;
}
void dfs1(int u,int fz){
	ll mx=0;
	siz[u]=1,fa[u]=fz,dep[u]=dep[fz]+1;
	ff[u][0]=fz;
	for (int i=1; i<22; i++){
		ff[u][i]=ff[ff[u][i-1]][i-1];
	}
	for (auto v : g[u]){
		if (v^fz){
			dfs1(v,u),siz[u]+=siz[v];
			if (siz[v]>mx){
				mx=siz[v],son[u]=v;
			}
		}
	}
}
void dfs2(int u,int tp){
	top[u]=tp,dfn[u]=++tot,rnk[tot]=u;
	if (!son[u]){
		return;
	}
	dfs2(son[u],tp);
	for (auto v : g[u]){
		if ((v^fa[u]) && (v^son[u])){
			dfs2(v,v);
		}
	}
}
int lca(int u,int v){
	if (dep[u]<dep[v]){
		swap(u,v);
	}
	int dif=dep[u]-dep[v];
	for (int i=0; i<20; i++){
		if (dif>>i&1){
			u=ff[u][i];
		}
	}
	if (u==v){
		return u;
	}
	for (int i=19; i>=0; i--){
		if (ff[u][i]!=ff[v][i]){
			u=ff[u][i],v=ff[v][i];
		}
	}
	return ff[u][0];
}
void upd_chain(int x,int y,ll z){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]){
			swap(x,y);
		}
		upd(1,1,n,dfn[top[x]],dfn[x],z);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]){
		swap(x,y);
	}
	upd(1,1,n,dfn[x],dfn[y],z);
}
ll qy_chain(int x,int y){
	ll ans=0;
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]){
			swap(x,y);
		}
		ans+=qy(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]){
		swap(x,y);
	}
	ans+=qy(1,1,n,dfn[x],dfn[y]);
	return ans;
}

int snc[N],is[N];

void solve(){
	cin>>n>>m;
	init();
	int cnt11=0;
	for (int i=1; i<=n; i++){
		snc[i]=is[i]=0;
		cin>>w[i];
		cnt11+=w[i];
	}
	for (int i=1; i<n; i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,1);
	bd(1,1,n);
	for (int i=1; i<=n; i++){
		if (w[i]){
			snc[fa[i]]++;
		}
	}
	int cnt=0;
	set<int> st;
	for (int i=1; i<=n; i++){
		if (w[i] && snc[i]==0){
			cnt++;
			st.insert(i);
			is[i]=1;
		}
	}
	while (m--){
		int u;
		cin>>u;
		upd_chain(u,u,w[u]==1?-1:1);
		cnt11+=(w[u]==1?-1:1);
		if (!w[u]){
			snc[fa[u]]++;
			if (is[fa[u]] && fa[u] && snc[fa[u]]==1){
				cnt--;
				st.erase(fa[u]);
				is[fa[u]]=0;
			}
			if (snc[u]==0){
				cnt++;
				st.insert(u);
				is[u]=1;
			}
		}
		else{
			snc[fa[u]]--;
			if (w[fa[u]] && fa[u] && snc[fa[u]]==0){
				cnt++;
				st.insert(fa[u]);
				is[fa[u]]=1;
			}
			if (is[u]){
				cnt--;
				st.erase(u);
				is[u]=0;
			}
		}
		w[u]^=1;
		if (cnt==1){
			cout<<"Yes\n";
		}
		else{
			if (cnt==0 || cnt>2){
				cout<<"No\n";
			}
			else{
				int x=-1,y=-1;
				for (auto u : st){
					if (x==-1) x=u;
					else y=u; 
				}
				int cal=qy_chain(x,y);
				if (cal==cnt11 && cal==dep[x]+dep[y]-dep[lca(x,y)]*2+1){
					cout<<"Yes\n";
				}
				else{
					cout<<"No\n";
				}
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	while (t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Hoks (赞：5)

## 前言
降智人，场上开场忘记报名硬控 $10$ 分钟，A 罚时一发而且卡了一会，CD 各 $3$ 发罚时而慌了居然不会这个 E。

我这个做法好像做麻烦了？不管了大力草过去了。
## 思路分析
最开始没感觉，那就直接大力上吧。

分讨一下，看下非法的情况都有哪些。

因为路径不好判断，所以考虑用把这个条件转化为好几个条件合起来的充要条件。

直接对样例开始手搓，可以发现其实只有如下 $2$ 种情况：

1. 所有黑点的导出子树点数与黑点数不相同。
2. 存在黑点 $u$ 满足与他距离为 $1$ 的黑点数大于 $2$。

其中对于 $1$ 情况，很无脑的我就把 [P3320 [SDOI2015] 寻宝游戏](https://www.luogu.com.cn/problem/P3320) 扔上来了。

只要像寻宝游戏那样维护出长度直接判断即可。

接着考虑 $2$ 情况。

貌似还不是很好处理，考虑直接把这个条件再转化了。

3. 同一深度的点不能超过 $2$ 个。

然后去欢喜码代码，直接卡第二个样例上了。

看下第二个样例就会发现会存在这样的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/g9tnumys.png)

（这些点都是黑点。）

我们会发现 $5$ 是一个不符合情况 $2$ 的点，但是情况 $3$ 却判不出。

那么就再次补充一个条件。

因为一条路径要么就是一条链，要么就是走到两端点的 LCA 再拐下去。

所以如果存在有 $2$ 个黑点儿子的点，必然是拐点 LCA。

所以补充条件即为：

4. 存在 $2$ 个黑点儿子的点不为 LCA。

实现上考虑所有黑点的 LCA 即为 $LCA(\min(dfn),\max(dfn))$。

考虑把所有存在大于 $2$ 个黑点儿子的点维护出来。

如果个数大于 $1$ 个即不可行。

如果个数为 $1$ 则这个点必须为 LCA 才可行。

当然个数为 $0$ 个也是可行的。

具体细节可以见代码了。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,mod=1e9+7,V=1e9,INF=0x3f3f3f3f3f3f3f3f;
int T,n,q,a[N],Q[N],c[N],cs[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
namespace tree_decomposition
{
	int cnt;vector<int> e[N];
	int fa[N],son[N],si[N],dep[N];
	int top[N],id[N],dfn[N];
	inline void add(int u,int v) { e[u].emplace_back(v),e[v].emplace_back(u); }
	inline void dfs1(int u,int ff)
	{
		fa[u]=ff,si[u]=1,dep[u]=dep[ff]+1;
		for(auto v:e[u])
		{
			if(v==ff) continue;
			dfs1(v,u);
			si[u]+=si[v];
			if(si[son[u]]<si[v]) son[u]=v;
		}
	}
	inline void dfs2(int u,int topf)
	{
		top[u]=topf,dfn[u]=++cnt,id[cnt]=u;
		if(son[u]) dfs2(son[u],topf);
		for(auto v:e[u])
		{
			if(v==fa[u]||v==son[u]) continue;
			dfs2(v,v);
		}
	}
	inline int LCA(int x,int y)
	{
		while(top[x]!=top[y])
		{
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			x=fa[top[x]];
		}
		return dep[x]<dep[y]?x:y;
	}
}
using namespace tree_decomposition;
inline int dis(int x,int y){return dep[x]+dep[y]-2*dep[LCA(x,y)];}
signed main()
{
    T=read();
    while(T--)
    {
        n=read(),q=read();set<int>s,ss;cnt=0;int tot=0,tt=0,ans=0,gs=0,as=0;for(int i=1;i<=n;i++) a[i]=read();
        for(int i=1;i<=n;i++) e[i].clear(),son[i]=dfn[i]=id[i]=fa[i]=dep[i]=si[i]=c[i]=cs[i]=0;
		for(int i=1,u,v;i<n;i++) u=read(),v=read(),add(u,v);dfs1(1,0),dfs2(1,1);auto it=s.begin();
    	for(int i=1;i<=n;i++) if(a[i]) a[i]=0,Q[++tt]=i;as=tt;for(int i=1;i<=q;i++) Q[++tt]=read();
        for(int i=1,x,y,z,lca;i<=tt;i++)
        {
	        x=Q[i];x=dfn[x];int f=0;
        	if(!a[id[x]])
        	{
        		s.insert(x),tot++,c[dep[Q[i]]]++;
        		if(c[dep[Q[i]]]==3) gs++;cs[fa[Q[i]]]++;
        		if(cs[fa[Q[i]]]==2&&a[fa[Q[i]]]) ss.insert(fa[Q[i]]);
        		if(cs[Q[i]]>=2) ss.insert(Q[i]);//注意此处是 >=
        	}
        	else
        	{
        		if(c[dep[Q[i]]]==3) gs--;
        		if(cs[fa[Q[i]]]==2&&a[fa[Q[i]]]) ss.erase(fa[Q[i]]);
        		if(cs[Q[i]]>=2) ss.erase(Q[i]);//注意此处是 >=
        		tot--;c[dep[Q[i]]]--;cs[fa[Q[i]]]--;
        	}
	        y=id[(it=s.lower_bound(x))==s.begin()?*--s.end():*--it];
	        z=id[(it=s.upper_bound(x))==s.end()?*s.begin():*it];
	        if(a[id[x]]) s.erase(x);x=id[x];int d=dis(x,y)+dis(x,z)-dis(y,z);
	        if(!a[x]) a[x]=1,ans+=d;else a[x]=0,ans-=d;
        	if(s.size()>=2)
        	{
        		lca=LCA(id[*s.begin()],id[*--s.end()]);
        		if(ss.size()==1&&*ss.begin()==lca||ss.empty()) f=1;
        	}
        	if(i>as){if(ans/2==tot-1&&!gs&&f||tot==1) put("YES\n");else put("No\n");}
        }
    }
    genshin:;flush();return 0;
}
```

---

## 作者：Luzhuoyuan (赞：3)

Links: [[Codeforces]](https://codeforces.com/contest/1975/problem/E) [[Luogu]](https://www.luogu.com.cn/problem/CF1975E)

官解太妙了，没想到。介绍一下我又大又慢但是比较好想的做法。

### 题意

给定一棵 $n$ 个结点的树，第 $i$ 个点有颜色 $c_i$，其中 $c_i=0$ 为白色，$c_i=1$ 为黑色。有 $q$ 次询问，每次询问给定一个正整数 $u$，要求将结点 $u$ 的颜色反转，并判断修改后的树上的所有黑点是否构成一条链。（也即：是否存在两个黑点满足它们之间的路径上经过了整颗树上的所有黑点且不经过白点。）特别地，一个黑点构成一条链，若没有黑点则不构成一条链。询问不独立。每个测试点 $t$ 组测试用例。

- $1\le t\le 10^4$；
- $1\le n,q\le 2\cdot 10^5$；
- $\sum n,\sum q\le 2\cdot 10^5$；
- $1\le u\le n$；
- $c_i\in\{0,1\}$。

### 思路

事实上想到这个做法就是因为原题面里就有翻译括号里的那句话。

我们考虑用这句话中的方法来判断。假设我们已经知道可能作为链的两端的两个点，我们只需要计算它们之间的路径上的黑点数量，如果 路径上黑点数量 = 总黑点数量 = 路径上经过的点数，那么就满足条件。要快速算一条路径上的黑点数量，很容易用重链剖分和树状数组来维护。

之后思考路径两端的点是什么。首先可以发现，链经过的每一个深度上的黑点数量为 $1$ 或 $2$，所以我们记录黑点数量为 $1,2$ 的深度有哪些，并记录每个深度的黑点数。先特判掉总黑点数量小于等于 $1$ 的情况以及不存在黑点数量为 $1$ 的深度（必然不合法）的情况，然后分类讨论链的形态。

![](https://cdn.luogu.com.cn/upload/image_hosting/skyc14e7.png)

1. 直链：表现为没有黑点数量为 $2$ 的深度，此时两端分别为黑点数量为 $1$ 的深度最小点和最大点；
1. 两端深度相同的链：表现为黑点数量为 $1$ 的深度有恰好一个，此时两端为黑点数量为 $2$ 的深度最大的两个点；
1. 其他链：此时一端为黑点数量为 $1$ 的深度最大点，另一端为黑点数量为 $2$ 的深度最大的两点之一。

这些东西可以用 `set` 简单维护，于是就做完了。复杂度 $O(n\log^2 n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=2e5+5;
int _,n,m,x,y,tot,a[N],d[N],dfn[N],son[N],sz[N],c[N],top[N],fa[N],cnt;
vector<int> ve[N];
set<int> ps[N],ds[3];
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
void dfs(int u){
	sz[u]=1,d[u]=d[fa[u]]+1;
	for(int v:ve[u])if(v!=fa[u])fa[v]=u,dfs(v),sz[u]+=sz[v],sz[v]>sz[son[u]]&&(son[u]=v);
}
void dfs2(int u,int t){
	dfn[u]=++tot,top[u]=t;
	if(son[u])dfs2(son[u],t);
	for(int v:ve[u])if(v!=fa[u]&&v!=son[u])dfs2(v,v);
}//处理树剖
inline void add(int p,int v){for(;p<=n;p+=p&-p)c[p]+=v;}
inline int getv(int p){int s=0;for(;p;p&=p-1)s+=c[p];return s;}
//树状数组
inline void upd(int p){
	int sz=ps[d[p]].size();
	if(sz&&sz<=2)ds[sz].erase(d[p]);
	if(ps[d[p]].insert(p).second)add(dfn[p],1),cnt++;
	else ps[d[p]].erase(p),add(dfn[p],-1),cnt--;
	sz=ps[d[p]].size();if(sz&&sz<=2)ds[sz].insert(d[p]);
}//反转一个点
inline bool chk(int x,int y){
	int s=0,l=d[x]+d[y];
	while(top[x]!=top[y]){
		if(d[top[x]]<d[top[y]])swap(x,y);
		s+=getv(dfn[x])-getv(dfn[top[x]]-1),x=fa[top[x]];
	}if(dfn[x]>dfn[y])swap(x,y);
	s+=getv(dfn[y])-getv(dfn[x]-1);
	return l-d[x]*2+1==cnt&&s==cnt;
}//判断
inline void prt(bool x){puts(x?"Yes":"No");}
signed main(){
	_=read();
	while(_--){
		n=read(),m=read();tot=cnt=0;
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<n;i++)x=read(),y=read(),ve[x].pb(y),ve[y].pb(x);
		dfs(1);dfs2(1,1);
		for(int i=1;i<=n;i++)if(a[i])upd(i);
		while(m--){
			x=read(),upd(x);
			if(cnt<=1)prt(cnt);else if(ds[1].empty())puts("No");
			else if(ds[2].empty())prt(chk(*ps[*ds[1].begin()].begin(),*ps[*prev(ds[1].end())].begin()));
			else if((int)ds[1].size()==1)x=*prev(ds[2].end()),prt(chk(*ps[x].begin(),*next(ps[x].begin())));
			else x=*ps[*prev(ds[1].end())].begin(),y=*prev(ds[2].end()),
				prt(chk(x,*ps[y].begin())||chk(x,*next(ps[y].begin())));
		}
		for(int i=1;i<=n;i++)ve[i].clear(),son[i]=c[i]=0,ps[i].clear();
		ds[1].clear(),ds[2].clear();
	}
	return 0;
}
```

（逃

---

## 作者：_Ch1F4N_ (赞：2)

考虑维护儿子邻域信息。

具体而言，对每个点维护其儿子中黑色节点的数量，假若这个点本也是黑色，就将这个信息加入桶。下文以信息一词代指一个点儿子中黑色点数量。

对于一条链，情况有二：

1. 儿子到祖先的链，此时桶中一个黑色节点信息为 $0$ 其余为 $1$。

2. 剩余的情况就是两个黑色点信息为 $0$ 一个黑色点信息为 $2$ 其余为 $1$。注意此时这唯一一个信息为 $2$ 的点必须是全局最浅的黑点，以排除一条这样的链上方再挂一条链的情况。

那么对于情况 2 的需要还需开一个 set 维护全局最浅的黑点。

复杂度线性对数。

下面是赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int S[maxn];
int d[maxn],father[maxn],dep[maxn],n,q,sum;
int col[maxn];
set< pair<int,int> > D2,All;//(dep,u)
vector<int> E[maxn];
void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    father[u]=fa;
    for(int v:E[u])
        if(v!=fa) dfs(v,u),d[u]+=col[v];
    if(col[u]==1) S[d[u]]++,sum++,All.insert(make_pair(dep[u],u));
    if(d[u]==2) D2.insert(make_pair(dep[u],u));
}
void ins(int u){
    sum++;
    //染黑
    All.insert(make_pair(dep[u],u));
    if(father[u]!=0&&d[father[u]]==2) D2.erase(make_pair(dep[father[u]],father[u]));
    if(col[father[u]]==1&&father[u]!=0){
        S[d[father[u]]]--;
    }
    if(father[u]!=0) d[father[u]]++;
    if(col[father[u]]==1&&father[u]!=0){
        S[d[father[u]]]++;
    }
    if(d[father[u]]==2&&father[u]!=0) D2.insert(make_pair(dep[father[u]],father[u]));
    if(d[u]==2){
        D2.erase(make_pair(dep[u],u));
    }
    S[d[u]]++;
    if(d[u]==2){
        D2.insert(make_pair(dep[u],u));
    }
}
void del(int u){
    sum--;
    All.erase(make_pair(dep[u],u));
    if(father[u]!=0&&d[father[u]]==2) D2.erase(make_pair(dep[father[u]],father[u]));
    if(col[father[u]]==1&&father[u]!=0){
        S[d[father[u]]]--;
    }
    if(father[u]!=0) d[father[u]]--;
    if(col[father[u]]==1&&father[u]!=0){
        S[d[father[u]]]++;
    }
    if(d[father[u]]==2&&father[u]!=0) D2.insert(make_pair(dep[father[u]],father[u]));
    if(d[u]==2){
        D2.erase(make_pair(dep[u],u));
    }
    S[d[u]]--;
    if(d[u]==2){
        D2.insert(make_pair(dep[u],u));
    }
}
void work(){
    All.clear();
    D2.clear();
    cin>>n>>q;
    d[0]=0;
    S[0]=0;
    for(int i=1;i<=n;i++) S[i]=d[i]=0,cin>>col[i],E[i].clear();
    sum=0;
    for(int i=2;i<=n;i++){
        int x,y;
        cin>>x>>y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    dfs(1,0);
    while(q--){
        int u;
        cin>>u;
        if(col[u]==0) ins(u),col[u]=1;
        else del(u),col[u]=0;
        //cout<<S[0]<<' '<<S[1]<<' '<<S[2]<<' '<<(*D2.begin()).second<<' '<<(*All.begin()).second<<'\n';
        cout<<(((S[0]==1&&S[1]==sum-1)||(S[0]==2&&S[2]==1&&S[1]==sum-3&&(*D2.begin()).second==(*All.begin()).second))?"Yes\n":"No\n");
    }
}
int main(){
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
5 1
1 0 1 1 0
1 2
1 3
1 5
3 4
2
*/
```

---

## 作者：luanyanjia (赞：1)

### 题目简述
给一棵节点为黑色或白色的树。每次修改一个结点的颜色并询问黑色节点是否构成一条链。

### 题目思路

我们将一个节点的度数定义为和它相邻的黑点数。

不难发现，黑色节点构成一条链当且仅当她们的度数只是 $1$ 或 $2$，且度数为一的只有两个（链的两端节点度数为 $1$，其余节点是 $2$），并且每次修改时只会修改她的父亲和儿子，所以我们把树按 BFS 序拍到序列上（这样一个结点的儿子就是连续的了），用线段树维护其度数最大值，最小值，最小值个数即可。对于节点是否为白色我们额外维护一个标记，这个也不难处理。时间复杂度 $O(n\log n)$。

记得特判 $0,1,2$ 个黑点的情况。

~~场上调了一个小时，赛后看到线性做法的我是小丑~~

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	char ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
const int N=2e5+5;
int T,n,Q;
int a[N],fst[N],nxt[N<<1],v[N<<1],idx;
inline void Add(int a,int b){
	v[idx]=b,nxt[idx]=fst[a];
	fst[a]=idx++;
}
int fa[N],degb[N],sons[N],son[N];
void DFS(int x,int f){
	fa[x]=f;
	for(int i=fst[x];~i;i=nxt[i]){
		int y=v[i];
		if(y==f)continue;
		sons[x]++;
		DFS(y,x);
	}
}
queue<int> q;
int dfn[N],fdfn[N],cnt;
void BFS(int s){
	q.push(s);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		dfn[++cnt]=x;
		fdfn[x]=cnt;
		for(int i=fst[x];~i;i=nxt[i]){
			int y=v[i];
			if(y==fa[x])continue;
			if(!son[x])son[x]=y;
			q.push(y);
		}
	}
}
struct Segment{
	int mn,mnnum,mx,ifw,tag;
}t[N<<2];
inline void Push_up(int i){
	if(t[i*2].ifw&&t[i*2+1].ifw)return t[i].ifw=1,t[i].tag=0,void();
	t[i].ifw=0;
	if(t[i*2].ifw)t[i]=t[i*2+1];
	else if(t[i*2+1].ifw)t[i]=t[i*2];
	else{
		t[i].mn=min(t[i*2].mn,t[i*2+1].mn);
		if(t[i*2].mn<t[i*2+1].mn)t[i].mnnum=t[i*2].mnnum;
		else if(t[i*2].mn>t[i*2+1].mn)t[i].mnnum=t[i*2+1].mnnum;
		else t[i].mnnum=t[i*2].mnnum+t[i*2+1].mnnum;
		t[i].mx=max(t[i*2].mx,t[i*2+1].mx);
	}
	t[i].tag=0;
	/*
	这里一定要清空标记，因为叶子结点的标记按我的写法是会留在上面的，
	平常没什么问题，但是这里因为有直接继承可能会把儿子的标记吸上来，
	这样就完美的寄了。 
	*/ 
}
inline void Addtag(int i,int x){
	t[i].mn+=x,t[i].mx+=x;
	t[i].tag+=x;
}
inline void Push_down(int i){
	if(t[i].tag){
		Addtag(i*2,t[i].tag);
		Addtag(i*2+1,t[i].tag);
		t[i].tag=0;
	}
}
void Build(int i,int l,int r){
	t[i].tag=0;
	if(l==r){
		t[i].ifw=!(a[dfn[l]]);
		t[i].mn=t[i].mx=degb[dfn[l]];
		t[i].mnnum=1;
		return ;
	}
	int mid=(l+r)>>1;
	Build(i*2,l,mid);
	Build(i*2+1,mid+1,r);
	Push_up(i);
}
void Update(int i,int l,int r,int L,int R,int x){
	if(L<=l&&r<=R){
		Addtag(i,x);
		return ;
	}
	int mid=(l+r)>>1;
	Push_down(i);
	if(L<=mid)Update(i*2,l,mid,L,R,x);
	if(R>mid)Update(i*2+1,mid+1,r,L,R,x);
	Push_up(i);
}
void Update_col(int i,int l,int r,int x,int col){
	if(l==r)return t[i].ifw=(!col),void();
	int mid=(l+r)>>1;
	Push_down(i);
	if(x<=mid)Update_col(i*2,l,mid,x,col);
	else Update_col(i*2+1,mid+1,r,x,col);
	Push_up(i);
}
int blacks=0;
signed main(){
	rd(T);
	while(T--){
		rd(n,Q);
		idx=cnt=blacks=0;
		for(int i=1;i<=n;i++)fst[i]=-1,degb[i]=sons[i]=son[i]=0;
		for(int i=1;i<=n;i++)rd(a[i]),blacks+=a[i];
		for(int i=1;i<n;i++){
			int x,y;rd(x,y);
			Add(x,y);Add(y,x);
			if(a[x])degb[y]++;
			if(a[y])degb[x]++;
		}
		DFS(1,1);
		BFS(1);
		Build(1,1,n);
		while(Q--){
			int u;rd(u);
			a[u]=!a[u];
			if(a[u]){
				blacks++;
				if(son[u])Update(1,1,n,fdfn[son[u]],fdfn[son[u]]+sons[u]-1,1);
				if(u!=1)Update(1,1,n,fdfn[fa[u]],fdfn[fa[u]],1);
				Update_col(1,1,n,fdfn[u],1);
			}else{
				blacks--;
				if(son[u])Update(1,1,n,fdfn[son[u]],fdfn[son[u]]+sons[u]-1,-1);
				if(u!=1)Update(1,1,n,fdfn[fa[u]],fdfn[fa[u]],-1);
				Update_col(1,1,n,fdfn[u],0);
			}
			if(t[1].ifw)printf("No\n");
			else if(blacks==1)printf("Yes\n");
			else if(t[1].mn==1&&t[1].mx<=2&&t[1].mnnum==2){
				printf("Yes\n");
			}else printf("No\n");
		}
	}
	return 0;
}


```

---

## 作者：TernaryTree (赞：0)

无脑做法。考虑 CF372D 的 set 维护递增 dfn 方式，必要条件是边数等于点数减一。然后 dfn 最小的，也就是 `*set.begin()` 一定是链顶。然后次小的 `*next(set.begin())` 一定是链顶下面的一个点 $v$。在 set 上二分出最后一个属于 $v$ 子树的结点，如果符合条件一定是链的端点。另一个端点应该是 set 的最后一个结点。判断这两个点到链顶的距离和是否为边数即可。单 log。

---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

给定一棵 $n$ 个节点的数，$c_i=1$ 表示这个点为黑色，$c_i=0$ 表示这个点为白色。

接下来有 $q$ 次询问，每次给定一个 $u$，把 $u$ 的颜色取反（即黑变白，白变黑），问黑色点是否构成一条链。

# 题目思路

$k$ 个黑点，构成长度为 $k$ 的链的充要条件是，恰好存在 $k-2$ 个点的度数为 $2$。当然 $k\leq 2$ 需要特判一手。$0$ 个黑点不为链，$1$ 个为链，$2$ 个判断是否相邻。

因此，我们可以得到一个很暴力的做法就是每次维护 $deg_i$ 表示 $i$ 的度数，然后加点删点直接对 $deg_v\gets deg_v-1$。其中 $v$ 是 $u$ 的父亲或者 $u$ 的儿子。

每个点父亲唯一，儿子可能有很多，直接暴力不可取。因此，我们只要一个东西可以快速处理儿子的加减操作即可。

考虑维护 BFS 序。

这样就很容易连续维护自己儿子的贡献。

那么我们直接上线段树，维护『区间加法』，『全局最大值』，『全局最大值出现次数』这三个东西即可。

『全局最大值』和『全局最大值出现次数』是可以直接找根节点信息得到的。

这个是好维护的。

但是这样容易导致我们算进去白点的度数，为了处理这个，我们把白点的度数一开始全设置为 $-\infty$ 即可。每次改成黑点就加上一个 $\infty$。

多测要清空。多清空一点。最后五分钟吃一发 WA on 7 因为清空不到位。

# 完整代码

不是，哥们？我咋写了 $4.7\ \text{kb}$？

```cpp
const int inf = 1e9;
int n, q;
vector<int> a[200020];
int c[200020];
int dfn[200020];
bool vis[200020];
int par[200020];
int L[200020];
int R[200020];
struct SegTree
{
    struct node
    {
        int mx, cnt, lzy;
    } t[200020 << 2];
#define ls id << 1
#define rs id << 1 | 1
    void push_up(int id)
    {
        t[id].mx = max(t[ls].mx, t[rs].mx);
        if (t[ls].mx == t[rs].mx)
            t[id].cnt = t[ls].cnt + t[rs].cnt;
        else if (t[ls].mx > t[rs].mx)
            t[id].cnt = t[ls].cnt;
        else
            t[id].cnt = t[rs].cnt;
    }
    void push_down(int id, int l, int r)
    {
        t[ls].mx += t[id].lzy;
        t[rs].mx += t[id].lzy;
        t[ls].lzy += t[id].lzy;
        t[rs].lzy += t[id].lzy;
        t[id].lzy = 0;
    }
    void build(int id = 1, int l = 1, int r = n)
    {
        if (l == r)
            return t[id].mx = t[id].lzy = 0, t[id].cnt = 1, void();
        int mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        push_up(id);
    }
    void clear(int m)
    {
        for (int i = 1; i <= m << 2; i++)
            t[i].mx = t[i].cnt = t[i].lzy = 0;
    }
    void add(int ql, int qr, int k, int id = 1, int l = 1, int r = n)
    {
        if (r < ql || l > qr)
            return;
        if (ql <= l && r <= qr)
            return t[id].mx += k, t[id].lzy += k, void();
        push_down(id, l, r);
        int mid = l + r >> 1;
        add(ql, qr, k, ls, l, mid);
        add(ql, qr, k, rs, mid + 1, r);
        push_up(id);
    }
} T;
void bfs()
{
    int times = 0;
    for (int i = 1; i <= n; i++)
        vis[i] = 0;
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        dfn[u] = ++times;
        chkmn(L[par[u]], dfn[u]);
        chkmx(R[par[u]], dfn[u]);
        for (int v : a[u])
            if (!vis[v])
                par[v] = u, q.push(v), vis[v] = 1;
    }
}
void solve()
{
    read(n, q);
    for (int i = 1; i <= n; i++)
        dfn[i] = R[i] = par[i] = 0, L[i] = inf, a[i].clear();
    for (int i = 1; i <= n; i++)
        read(c[i]);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        read(u, v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    bfs();
    T.build();
    // for (int i = 1; i <= n; i++)
    //     cout << dfn[i] << " ";
    // cout << endl;
    // for (int i = 1; i <= n; i++)
    //     cout << L[i] << " " << R[i] << endl;
    int black = 0;
    set<int> blk;
    for (int i = 1; i <= n; i++)
    {
        T.add(dfn[i], dfn[i], -inf);
        if (c[i])
        {
            int u = i;
            black++;
            blk.insert(u);
            T.add(dfn[u], dfn[u], inf);
            T.add(dfn[par[u]], dfn[par[u]], 1);
            if (L[u] <= R[u])
                T.add(L[u], R[u], 1);
        }
    }
    while (q--)
    {
        int u;
        read(u);
        if (c[u])
        {
            black--;
            blk.erase(u);
            T.add(dfn[u], dfn[u], -inf);
            T.add(dfn[par[u]], dfn[par[u]], -1);
            if (L[u] <= R[u])
                T.add(L[u], R[u], -1);
            c[u] = 0;
        }
        else
        {
            black++;
            blk.insert(u);
            T.add(dfn[u], dfn[u], inf);
            T.add(dfn[par[u]], dfn[par[u]], 1);
            if (L[u] <= R[u])
                T.add(L[u], R[u], 1);
            c[u] = 1;
        }
        if (!black)
        {
            puts("No");
            continue;
        }
        if (black == 1)
        {
            puts("Yes");
            continue;
        }
        if (black == 2)
        {
            int uu = *blk.begin();
            int vv = *--blk.end();
            puts(par[uu] == vv || par[vv] == uu ? "Yes" : "No");
            continue;
        }
        // cout << T.t[1].mx << " " << T.t[1].cnt << endl;
        if (T.t[1].mx == 2 && T.t[1].cnt == black - 2)
            puts("Yes");
        else
            puts("No");
    }
    T.clear(n + 5);
}
```

---

## 作者：Tachibana_Kimika (赞：0)

首先我们考虑怎么描述这个链的状态。我们考虑对于每个黑点记录他的黑点儿子数量，如果所有黑点的黑点儿子数量都为 $1$，只有一个黑点的黑点儿子数量为 $0$，此时就形成了一个链。如果有一个黑点的黑点儿子数量为 $2$，两个黑点的黑点儿子数量为 $0$，其他黑点的黑点儿子数量为 $1$，此时如果黑点儿子数量为 $2$ 的点父亲为白点，则形成一个链。所以我们记录儿子为 $0,1,2$ 的点，再记录所有儿子为 $2$ 的点的父亲编号总和即可。

---

## 作者：sbno333 (赞：0)

虽然是传统题，但给我的感觉是和通讯题有点像，即将维护的信息转化（不过通讯题是构造）。

于是就变成了找链的性质。

不妨设 $1$ 为根，每次染色能加快处理的除了黑色个数之类的与形态无关的就只与父亲有关，与之对应的要维护儿子信息是容易的，因为每次只需要修改父亲对应儿子信息。

发现链至多有两个黑儿子数为 $0$ 的黑父亲（后文可能也叫它绝后节点），且存在唯一深度最低的节点。

发现深度最低的黑节点的黑儿子数量需要与绝后黑节点数量相同，否则儿子后面到绝后一定有分叉，这显然不可能为链，否则以黑儿子为根的**子树**的黑节点形成以根为起点的链。

显然包括当前节点能形成一个更长的链。

但是最多只能有两个链分支，否则会死。

所以我们只需要维护没有黑儿子的黑节点和最浅黑节点即可，前者我们需要维护每个节点黑儿子数量，对于没黑儿子且为黑的节点在进行照顾，这是容易维护的（每次只会对当前节点和父亲产生影响）。

对于后者，优先队列解决即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a,b;
int ans;
struct st{
	int v,ne;
}sd[1000009];
int h[1000009];
int inn;
void add(int u,int v){
	sd[++inn].v=v;
	sd[inn].ne=h[u];
	h[u]=inn;
}
int fa[1000009];
int d[1000009];
void dfs(int t){//记录深度（记录最浅的节点）和父亲
	d[t]=d[fa[t]]+1;
	for(int i=h[t];i;i=sd[i].ne){
		if(sd[i].v!=fa[t]){
			fa[sd[i].v]=t;
			dfs(sd[i].v);
		}
	}
}
bool v[1000009];//记录颜色
int bs[1000009];//记录黑儿子数量
struct zz{
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
	void add(int t){
		q.push({d[t],t});
	}
	int que(){
		while(q.size()&&!v[q.top().second]){
			q.pop();
		}
		if(!q.size()){
			return 0;
		}
		return q.top().second;
	}
}ss;
void cl(){
	inn+=10;
	while(inn){
		sd[inn--]={0,0};
	}
	for(int i=0;i<=n+10;i++){
		h[i]=fa[i]=d[i]=v[i]=bs[i]=0;
	}
	while(ss.q.size()){
		ss.q.pop();
	}
	ans=0;
}
void _main(){
	int q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>v[i];
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1);
	int bz;//记录绝后
	bz=0;
	int num;
	num=0;
	for(int i=1;i<=n;i++){
		if(v[i]){
			bs[fa[i]]++;
			num++;
			ss.add(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(bs[i]==0&&v[i]){
			bz++;
		}
	}
	
	for(int i=1;i<=q;i++){
		int t;
		cin>>t;
		if(v[t]){
			num--;
			if(bs[t]==0&&v[t]){
				bz--;
			}
			v[t]=0;
			bs[fa[t]]--;
			if(bs[fa[t]]==0&&v[fa[t]]){
				bz++;
			}
		}else{
			if(bs[fa[t]]==0&&v[fa[t]]){
				bz--;
			}
			v[t]=1;
			ss.add(t);
			num++;
			bs[fa[t]]++;
			if(bs[t]==0&&v[t]){
				bz++;
			}
		}
		if(num==0){
			cout<<"No"<<endl;
		}else if(num==1){
			cout<<"Yes"<<endl;
		}else{
			int z;
			z=ss.que();
			if(bs[z]>2){
				cout<<"No"<<endl;
			}else{
				cout<<(bs[z]==bz?"Yes":"No")<<endl;
			}
		}
	}
	cl();
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

题意：给定一棵树，每个点有黑白两种颜色，每次将一个节点的颜色取反，并询问所有黑点是否是一条链。（没有黑点不算链）

随便找一个根，考虑维护所有本身是黑色且子节点均为白色的节点，用一个集合存下来。为了方便表述称之为特殊点。

容易发现每次修改的时候只会影响当前节点和父节点，所以复杂度是对的。

因为一条链的特殊点个数一定是一或者二，所以当特殊点个数大于二或为零时显然黑点不成一条链。当个数为一时显然成一条链，考虑个数为二的情况。

首先我们需要判断这两个特殊点是否连通。若这两个点连通则它们之间的简单路径上所有点都是黑点。考虑再用一个 BIT 维护每个点到根节点的黑点个数，并计算最近公共祖先即可处理。

判断到这，我们已经能够确定这两个点之间的简单路径上所有点都是黑点，但却不能确定最近公共祖先之上是否没有黑点。由于已知特殊点个数为二，所以只需判断最近公共祖先的父亲是否是白点即可。

总时间复杂度 $O(n \log n)$。

---

## 作者：SamHJD (赞：0)

## Chain Queries

> 给出一棵树，每个节点可为黑色或白色。
>
> 支持单点修改，查询树上黑点是否构成一条链。

修改一个点时，合法复杂度内更新子节点的信息是困难的，考虑只更新父节点的信息，那么我们可以维护每个点的黑色子结点的数量。

观察链的性质，每个点至多拥有两个黑色子结点，且拥有两个黑色子结点的点不超过一个，其必为链两端点的 LCA，那么他的父节点必为白色。再判断连通，不难发现如果有两个及以上的黑色结点拥有白色父节点那么一定不连通。

$O(1)$ 维护黑色子结点数量，并更新符合或不符上述条件的结点，判断即可。

---

## 作者：六楼溜刘 (赞：0)

### 题意

- 给定一棵 $n$ 个点的树，每个点是黑色或白色的。
- 有 $q$ 次操作，每次操作是反转某个点的颜色（即黑变白，白变黑）。
- 每次操作后，判断树上的所有黑色点是否恰好是一条链。
- 有多测，$\sum n,\sum q\le 2\times 10^5$。

### 题解

提供一个把脑子扔掉想出来的做法。

首先容易发现黑点组成一个森林。

考虑一个森林是一条链的充要条件是**这个森林中只有一个点**或**没有任何一个点的度数为 $0$，且恰有两个点的度数为** $1$。

前者容易特判，但后者不好维护，原因是一个点的修改会影响它的所有儿子，复杂度能飙到 $O(n^2)$。

这时候题解做法是让你只统计每个点儿子的信息来判，就不会有父亲改儿子的情况了。但这个需要动脑子，非常不好。

不动脑子的想法是用数据结构来维护一个点的所有儿子。一个显然的思路是仿照树上差分，构造一个序列使得单次要维护的东西在序列上是连续的。容易想到维护点被 bfs 到的顺序。这样一个点的所有儿子在序列上就是连续的了。

那么就是在线段树上维护上面那坨东西了。容易发现可以维护区间最小值和最小值出现次数，操作就是单点赋值（白色赋为一个充分大的数，黑色赋为该点周围的黑点数）和区间加一减一。都是线段树能维护的简单操作。另外注意每次修改和查询时记得额外考虑父亲。

复杂度 $O(n+q\log n)$，不建议使用这个做法。

### code

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(int i=(s);i>=(e);i--)
#ifdef DEBUG
#define msg(args...) fprintf(stderr,args)
#else
#define msg(...) void()
#endif
using namespace std;
#define gc getchar()
inline int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=2e5+5,inf=0x3f3f3f3f;
int n,q,a[N],ff[N];
vector<int> e[N];
int cntd[N],bfn[N],st[N],ed[N],Tm,mp[N];
//st 和 ed 分别是直接儿子在 bfs 序列上的起点和终点。
struct Node{
	int mn,cmn;
	Node operator +(const Node &r){
		Node res;
		res.mn=min(mn,r.mn);res.cmn=0;
		if(res.mn==mn) res.cmn+=cmn;
		if(res.mn==r.mn) res.cmn+=r.cmn;
		return res;
	}
};
struct SegTree{
	#define mid ((l+r)>>1)
	#define lson l,mid,id<<1
	#define rson mid+1,r,id<<1|1
	Node info[N<<2];
	int cbl[N<<2],mark[N<<2];
	void PushUp(int id){
		cbl[id]=cbl[id<<1]+cbl[id<<1|1];
		info[id]=info[id<<1]+info[id<<1|1];
	}
	void modi(int id,int x){
		mark[id]+=x;
		info[id].mn+=x;
	}
	void PushDown(int id){
		if(!mark[id]) return;
		modi(id<<1,mark[id]);modi(id<<1|1,mark[id]);
		mark[id]=0;
	}
	void Build(int l=1,int r=n,int id=1){
		mark[id]=0;//带多测的线段树记得清空懒标记。
		if(l==r){
			cbl[id]=a[mp[l]];
			info[id].cmn=1;
			info[id].mn=a[mp[l]]?cntd[mp[l]]:inf;
			return;
		}
		Build(lson);Build(rson);
		PushUp(id);
	}
	void Modify(int L,int R,int X,int l=1,int r=n,int id=1){
		if(R<l||r<L) return;
		if(L<=l&&r<=R){
			modi(id,X);
			return;
		}
		PushDown(id);
		if(L<=mid) Modify(L,R,X,lson);
		if(mid< R) Modify(L,R,X,rson);
		PushUp(id);
	}
	void Change(int P,int X,int l=1,int r=n,int id=1){
  	//单点修改。
		if(l==r){
			info[id].mn=X;
			if(X==inf){
				cbl[id]=0;
			}else{
				cbl[id]=1;
			}
			return;
		}
		PushDown(id);
		if(P<=mid) Change(P,X,lson);
		else       Change(P,X,rson);
		PushUp(id);
	}
	int Query(int L,int R,int l=1,int r=n,int id=1){
   	//将白点改成黑点时求周围的黑点数。
		if(R<l||r<L) return 0;
		if(L<=l&&r<=R){
			return cbl[id];
		}
		PushDown(id);
		int res=0;
		if(L<=mid) res+=Query(L,R,lson);
		if(mid< R) res+=Query(L,R,rson);
		return res;
	}
	bool Ask(){//注意特判只有一个黑点的情况。
		return cbl[1]==1||(cbl[1]&&info[1].mn==1&&info[1].cmn==2);
	}
}mt; 
void bfs(){
	queue<int> q;
	q.push(1);
	Tm=0;
	bfn[1]=++Tm;
	while(q.size()){
		int u=q.front();q.pop();
		st[u]=ed[u]=0;
		mp[bfn[u]]=u;
		for(auto i:e[u]){
			if(i==ff[u]) continue;
			ff[i]=u;
			bfn[i]=++Tm;
			if(!st[u]) st[u]=bfn[i];
			ed[u]=bfn[i];
			q.push(i);
		}
	}
}
void solve(){
	n=read();q=read();
	forup(i,1,n){
		a[i]=read();
		e[i].clear();
		cntd[i]=0;
	}
	forup(i,1,n-1){
		int u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
		cntd[u]+=a[v];cntd[v]+=a[u];
	}
	bfs();
	mt.Build();
	forup(i,1,q){
		int u=read();
		mt.Modify(st[u],ed[u],(!a[u])-a[u]);
		mt.Modify(bfn[ff[u]],bfn[ff[u]],(!a[u])-a[u]);
		if(a[u]){
			mt.Change(bfn[u],inf);
		}else{
			mt.Change(bfn[u],mt.Query(st[u],ed[u])+a[ff[u]]);
		}
		a[u]^=1;
		puts(mt.Ask()?"Yes":"No");
	}
}
signed main(){
	int t=read();
	while(t--){
		solve();
	}
}
```

---

## 作者：yshpdyt (赞：0)

## 题意
一棵树，每个点初始为黑色或白色，每次操作先将一个点颜色取反，然后查询所有黑色点是否都在一条链上。

## Sol
~~赛时看到这种操作直接上了树刨，然后炸掉了~~。

维护儿子黑色节点的个数为 $0,1,2,\ge3$ 的个数即可。

考虑链的特征，以下情况均满足才合法：

0. ~~有黑色结点~~
1. 没有一个节点有三个黑色儿子。
2. 最多一个节点有两个黑色儿子，且该节点必须是黑色。
3. 只有一个黑色节点的父亲是白色，该黑色节点是 lca。

每次修改只需要更改自己的颜色，父亲对黑色儿子的记录，记录儿子黑色节点的个数的节点个数的桶，有两个黑色儿子的点集。

## Code
``` cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll a[N],n,m;
ll tot;
set<ll>q;
vector<ll>v[N];
ll cnt[N];
ll ch[N],fa[N],col;
void dfs(ll x,ll fat){
    ll sum=0;
    fa[x]=fat;
    if(!a[fa[x]]&&a[x])col++;
    for(auto y:v[x]){
        if(y==fa[x])continue;
        if(a[y])sum++;
        dfs(y,x);
    }
    ch[x]=sum;
    cnt[min(sum,3ll)]++;
    if(ch[x]==2)q.insert(x);
}
void sol(){
    col=tot=0;
    q.clear();
    cin>>n>>m;
    cnt[0]=cnt[1]=cnt[2]=cnt[3]=ch[0]=0;
    for(int i=1;i<=n;i++){
        v[i].clear();
        cin>>a[i];
        tot+=a[i];
        ch[i]=fa[i]=0;
    }
    for(int i=1;i<n;i++){
        ll x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        ll x;
        cin>>x;
        if(a[x]){
            cnt[min(ch[fa[x]],3ll)]--;
            if(ch[fa[x]]==2)q.erase(fa[x]);
            ch[fa[x]]--;
            if(ch[fa[x]]==2)q.insert(fa[x]);
            cnt[min(ch[fa[x]],3ll)]++;
            col+=ch[x]-(a[fa[x]]==0);
            tot--;
        }else{
            cnt[min(ch[fa[x]],3ll)]--;
            if(ch[fa[x]]==2)q.erase(fa[x]);
            ch[fa[x]]++;
            if(ch[fa[x]]==2)q.insert(fa[x]);
            cnt[min(ch[fa[x]],3ll)]++;
            col-=ch[x]-(a[fa[x]]==0);
            tot++;
        }
        a[x]^=1;
        if(tot<1){
            cout<<"No\n";
            continue;
        }
        if(cnt[3]){
            cout<<"No\n";
            continue;
        }
        if(cnt[2]>1){
            cout<<"No\n";
            continue;
        }
        if(col!=1){
            cout<<"No\n";
            continue;
        }
        if(cnt[2]==1&&a[fa[*q.begin()]]){
            cout<<"No\n";
            continue;
        }
        cout<<"Yes\n";
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

