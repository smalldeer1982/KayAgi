# Minimum spanning tree for each edge

## 题目描述

你 $n$ 个点，$m$ 条边，如果对于一个最小生成树中要求必须包括第 $i(1 \le i \le m)$ 条边，那么最小生成树的权值总和最小是多少。


## 说明/提示

数据范围：

$1 \le n \le 2 \times 10^5$，$n-1 \le m\le 2 \times 10^5$，$1 \le u_i,v_i \le n$，$u_i \neq v_i$，$1 \le w_i \le 10^9$。

## 样例 #1

### 输入

```
5 7
1 2 3
1 3 1
1 4 5
2 3 2
2 5 3
3 4 2
4 5 4
```

### 输出

```
9
8
11
8
8
8
9
```

# 题解

## 作者：Fido_Puppy (赞：11)

## Question

[CF609E Minimum spanning tree for each edge](https://www.luogu.com.cn/problem/CF609E)

## Solution

+ [**Kruskal**](https://www.cnblogs.com/yoke/p/6697013.html)

+ [**树链剖分**](https://www.cnblogs.com/ivanovcraft/p/9019090.html)

先用 Kruskal 求出最小生成树，

接着对我们求出的这棵最小生成树（其实也是棵树）进行树链剖分。

### 理想做法

对于第 i 个查询，先加上第 i 条边，

接着在构成的这个环中减去一条边权最大的边（第 i 条边除外）。

### 实际做法

首先这个第 i 条边肯定是不能真的加上去的（输出时加上这条边的边权就行辣）

设第 i 条边是连接节点 u 和节点 v 的。

我们可以发现这个环除去第 i 条边后就是 u 和 v 的最短路径（在最小生成树上）。

那这个环中最大边权（第 i 条边的边权除外）就可以用树链剖分求出来了。

可是还有一个问题：

普通的树链剖分是点权，而这里是边权。

其实我们只要每一个点上存这个点到它的父亲的边的边权，根上存一个 0 就行了。

接着在树链剖分的查询上注意一下，与普通的树链剖分略有不同，自己画图推一下。

## Code

### Notice

十年 OI 一场空，不开 **long long** 见祖宗。

```cpp
#include"bits/stdc++.h"
using namespace std;
#define N (long long)(2e5+10)
long long n,m;
vector<long long>g[N];
vector<long long>e[N];
struct ee {
	long long a,b,c;
}edge[N],d[N];
long long f[N],Ans=0,a[N];
long long dep[N],father[N],siz[N],hson[N],top[N],seg[N],rev[N],tot=1;
struct node {
	long long l,r,Max;
}t[N<<2];
inline long long find(long long x) {
	if (f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
inline bool cmp(ee a,ee b) {
	return a.c<b.c;
}
inline void dfs1(long long u,long long f) {
	dep[u]=dep[f]+1;
	father[u]=f;
	siz[u]=1;
	for(long long i=0;i<g[u].size();i++) {
		long long v=g[u][i];
		if (v!=f) {
			a[v]=e[u][i];
			dfs1(v,u);
			siz[u]+=siz[v];
			if (siz[v]>siz[hson[u]]) hson[u]=v;
		}
	}
}
inline void dfs2(long long u,long long f) {
	if (hson[u]) {
		top[hson[u]]=top[u];
		seg[hson[u]]=++tot;
		rev[tot]=hson[u];
		dfs2(hson[u],u);
		for(long long i=0;i<g[u].size();i++) {
			long long v=g[u][i];
			if (v!=f&&v!=hson[u]) {
				top[v]=v;
				seg[v]=++tot;
				rev[tot]=v;
				dfs2(v,u);
			}
		}
	}
}
inline void build(long long p,long long l,long long r) {
	t[p].l=l; t[p].r=r;
	if (l==r) {
		t[p].Max=a[rev[l]];
		return ;
	}
	long long mid=(t[p].l+t[p].r)>>1;
	build(p<<1,l,mid); build(p<<1|1,mid+1,r);
	t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
}
inline long long query(long long p,long long x,long long y) {
	if (x>y) return 0;
	if (t[p].l>=x&&t[p].r<=y) return t[p].Max;
	long long ans=0,mid=(t[p].l+t[p].r)>>1;
	if (x<=mid) ans=max(ans,query(p<<1,x,y));
	if (mid<y) ans=max(ans,query(p<<1|1,x,y));
	return ans;
}
inline long long qrange(long long x,long long y) {
	long long ans=0;
	while (top[x]!=top[y]) {
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=max(ans,query(1,seg[top[x]],seg[x]));
		x=father[top[x]]; if (x==0) x=1;
	}
	if (dep[x]>dep[y]) swap(x,y);
	ans=max(ans,query(1,seg[hson[x]],seg[y]));
	return ans;
}
signed main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(long long i=1;i<=m;i++) cin>>edge[i].a>>edge[i].b>>edge[i].c,d[i]=edge[i];
	for(long long i=1;i<=n;i++) f[i]=i;
	sort(edge+1,edge+m+1,cmp);
	for(long long i=1;i<=m;i++) {
		long long fx=find(edge[i].a),fy=find(edge[i].b);
		if (fx==fy) continue;
		f[fx]=fy;
		g[edge[i].a].push_back(edge[i].b); e[edge[i].a].push_back(edge[i].c);
		g[edge[i].b].push_back(edge[i].a); e[edge[i].b].push_back(edge[i].c);
		Ans+=edge[i].c;
 	}
 	dfs1(1,0); top[1]=seg[1]=rev[1]=1; dfs2(1,0);
 	build(1,1,n);
 	for(long long i=1;i<=m;i++) {
 		cout<<Ans+d[i].c-qrange(d[i].a,d[i].b)<<endl;
 	}
	return 0;
}
```

完结撒花！ ^.^

---

## 作者：grass8cow (赞：10)

**算法：kruskal 求最小生成树+树剖+ST表**

我们可以先用 kruskal 跑出最小生成树，统计出其边权和，记其为 $anss$ 。然后对于每条边，如果其在最小生成树内，直接输出 $anss$ ，否则强行在原树上连 $u$ 到 $v$ 的边，在 $u$ 到 $v$ 的路径上寻找一条权值最大的边，记它边权为 $t$ ，将其删去，答案为 $anss+w-t$ 。寻找这条最大的边，可以倍增，树剖，这个嘛，怎么开心怎么来。我选择树剖，不过上跳统计答案时并不用线段树，而是 $O(n\log n)$ 预处理，$O(1)$ 查询的 ST 表，和线段树比优势明显。这道题就可以解决了。

求最小生成树复杂度 $O(m\log m)$ ，树剖预处理 $O(n)$ ,ST表预处理 $O(n \log n)$ ，查询总复杂度 $O((m-n)\log n)$ ，总复杂度 $O(m\log m+m \log n+n)$ ，可以通过本题。

**Q: 为什么要删去 $u$ 到 $v$ 的路径上权值最大的边？**

A: 你要最小生成树，所以要删最大的边；删边后是一棵树，也就是要图联通，删去一条边，两端的点没法直接相连，但之间能互相到达，这就得经过 $u$ 到 $v$ 这条边。想一想，发现这条边必须在 $u$ 到 $v$ 的路径上，可以画图理解。

代码就是很简单的了。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge
{
	int u,v,w,id,fl;
}p[200010];
bool cmp(edge a,edge b)
{
	return a.w<b.w;
}
int f[200010];
int find(int x)
{
	if(x==f[x])return x;
	return f[x]=find(f[x]);
}
//kruskal
int st[200001][21];
int ask(int l,int r)
{
	int k=log2(r-l+1);
	return max(st[l][k],st[r-(1<<k)+1][k]);
}
void solve()
{
	for(int j=1;j<=22;j++)for(int i=1;i+(1<<j)-1<=n;i++)st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}//ST表 
struct qq
{
	int v,w,nex;
}o[400010];
int cnt,head[200010];
int fa[2000010],top[200001],siz[200001],son[200001],d[200001],id[200001],ab[200001],a[200001];
void add(int u,int v,int w)
{
	o[++cnt]=(qq){v,w,head[u]};head[u]=cnt;
}
void dfs(int x,int f,int deep)
{
	d[x]=deep;fa[x]=f;siz[x]=1;
	for(int i=head[x],v,maxn=-1;i;i=o[i].nex)
	{
		v=o[i].v;if(v==fa[x])continue;
		dfs(v,x,deep+1);ab[v]=o[i].w;
		siz[x]+=siz[v];
		if(maxn<siz[v])maxn=siz[v],son[x]=v;
	}
}
void dfs2(int x,int fafa)
{
	top[x]=fafa;st[id[x]=++id[0]][0]=ab[x];if(!son[x])return;
	dfs2(son[x],fafa);
	for(int i=head[x],v;i;i=o[i].nex)
	{
		v=o[i].v;if(v==son[x]||v==fa[x])continue;
		dfs2(v,v);
	}
}//树剖 
int ta(int u,int v)
{
	int ans=-2100000000;
	while(top[u]!=top[v])
	{
		if(d[top[u]]<d[top[v]])swap(u,v);
		ans=max(ans,ask(id[top[u]],id[u]));
		u=fa[top[u]];
	}
	if(d[u]>d[v])swap(u,v);
	if(u!=v)ans=max(ans,ask(id[u]+1,id[v]));
	return ans;
}//求u到v最大的边 
int n,m;
long long ans[200010],anss;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		p[i]=(edge){u,v,w,i,0};
	}
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=m;i++)if(find(p[i].u)!=find(p[i].v))
	{
		f[find(p[i].u)]=find(p[i].v);
		add(p[i].u,p[i].v,p[i].w);add(p[i].v,p[i].u,p[i].w);
		p[i].fl=1;anss+=p[i].w;
	}
	dfs(1,0,1);dfs2(1,1);solve();
	for(int i=1;i<=m;i++)if(p[i].fl)ans[p[i].id]=anss;else ans[p[i].id]=anss+p[i].w-ta(p[i].u,p[i].v);
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：IL杰佣 (赞：9)

有一说一，感觉这道题的难度可能达不到紫，不过理解的才是好的对吧。

首先我们来了解下题目大意：就是让你求出这棵树的最小生成树，然后用删去所输入点相连的最大权值在加上边权。

而这道题本蒟蒻是用 LCA+Kruskal 做的，比较容易理解。

### 话不多说，上代码！

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
struct node				//输入输入所用的结构体
{
    long long dis;
	int u,v,id;
}t[400010];
struct EDGE				//前向星结构体
{
    long long dis;
	int ver,nxt;
}p[400010];
int depth[200010],f[200020][21],vis[200010],fa[200010],cnt,head[200010],n,m,x,y,q,start,end;
long long w[200020][21],alltreelong;
int find(int x)				//并查集合并操作
{
    if(fa[x]!=x) 
	fa[x]=find(fa[x]);
    return fa[x];
}
void add(int u,int v,long long l)	//前向星
{
    p[++cnt].dis=l;
    p[cnt].nxt=head[u];
    p[cnt].ver=v;
    head[u]=cnt;
}
int cmp(node a,node b)			//Kruskal 快排求最短边
{
    return a.dis<b.dis;
}
int cmp2(node a,node b)			//后期根据 ID 还原顺序
{
    return a.id<b.id;
}
void kru()				//Kruskal 合并
{
    sort(t+1,t+m+1,cmp);
    for(int i=1;i<=n;i++)
	fa[i]=i;
    for(int i=1;i<=m;i++)
	{
        int x=t[i].u,y=t[i].v,fx=find(x),fy=find(y);
        if(fx!=fy)
		{
            fa[fx]=fy;
			add(fx,fy,t[i].dis);
			add(fy,fx,t[i].dis);
			alltreelong+=t[i].dis;
        }
    }
}
void dfs(int u)				//深搜建树
{
    vis[u]=1;
    for(int j=1;j<=20;j++)
	{

		f[u][j]=f[f[u][j-1]][j-1] ;
		w[u][j]=max(w[u][j-1],w[f[u][j-1]][j-1]) ;
	}
    for(int i=head[u];i;i=p[i].nxt)
	{
        int v=p[i].ver;
        if(vis[v])
		continue;
        depth[v]=depth[u]+1;
        f[v][0]=u;
		w[v][0]=p[i].dis;
        dfs(v);
    }
}
long long lca(int x,int y)		//LCA 求最近公共祖先	
{
    long long ans=0;
    if (depth[x]<depth[y])  swap(x,y);
    for(int i=20;i>=0;i--)
	{
        if(depth[f[x][i]]>=depth[y])
		{
            ans=max(ans,w[x][i]);
			x=f[x][i];
        }
    }
    if (x==y)	return ans;
    for(int i=20;i>=0;i--)
	{
       if(f[x][i]!=f[y][i])
		{
            ans=max(ans,max(w[x][i],w[y][i]));
            x=f[x][i];
				y=f[y][i];
        }
    }
    return max(ans,max(w[x][0],w[y][0]));
} 
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
	 {
        cin>>t[i].u>>t[i].v>>t[i].dis;
			t[i].id=i;		//将各自ID记录
    }
    kru();
    dfs(1);
    long long ans;
    sort(t+1,t+m+1,cmp2);		//还原，否则顺序不对
    for (int i=1;i<=m;i++)
	{
        ans=alltreelong+t[i].dis-lca(t[i].u,t[i].v);
		printf("%lld\n",ans);
    }
    return 0;
}
```
#### 码风还是比较大众化的，重在理解！

---

## 作者：E1_de5truct0r (赞：5)

人生中第一次在 20 秒内想出来 `*2100` 难度的题的正解，纪念一下。

另，题解区没看到在 Kruskal 重构树上进行 LCA 的题解，因此顺手写了没坏处。

## 思路

首先，跑一遍最小生成树。

对于每条边，分成两种情况：

1. 当前边在最小生成树上：直接输出最小生成树大小即可。

2. 不在最小生成树上：贪心策略为找到所有联通 $u$ 和 $v$ 的边，取最大值。

对于 1 操作我们不需要考虑了，只需要考虑如何快速求解 2 操作。我正好在做这个题之前学习了 Kruskal 重构树。Kruskal 重构树在每一次合并两个集合的时候，都会新建一个节点，点权就是当前这条边的边权。那么，由于我们 Kruskal 的时候，边权是从小到大处理的，因此新建的节点越往后，其权值越大。

这意味着什么呢？一个点的子树内所有边权的最大值就是它自己。而一个子树内保证 $x,y$ 联通的边，一定位于 $x \rightarrow \operatorname{LCA}(x,y)$ 和 $y \rightarrow \operatorname{LCA}(x,y)$ 这两个路径上。而我们惊奇的发现他们的最大值恰好就是 $\operatorname{LCA}(x,y)$ 的点权。

所以，我们每次倍增求出 $\operatorname{LCA}$，然后用最小生成树的边权和减去这个点的点权，加上当前边的边权即可。

时间复杂度：$O(m(\log m+\alpha(m))+m \log n)$，可以通过。（Kruskal 排序 + 并查集的复杂度 + 求最多 $m$ 次 LCA 复杂度）

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
inline int qr(){
	char ch=getchar(); bool f=1; int w=0;
	for(;ch<'0' || ch>'9';ch=getchar()) if(ch=='-')f=0;
	for(;ch>='0' && ch<='9';ch=getchar()) w=w*10+ch-'0';
	return f?w:-w;
}
using namespace std;

const int MAXN=400005; // 重构树新建 n-1 个节点，一定要开二倍空间！
struct Edge{
	int u,v,w,id;
	const bool operator<(const Edge &e)const{
		return w<e.w;
	}
}a[MAXN];
bool cmp(const Edge &u,const Edge &v){
	return u.id<v.id;
}
vector<int> E[MAXN];
int n,m,fa[MAXN],w[MAXN],sum=0;
int dep[MAXN],f[MAXN][25];
bool used[MAXN];

int find(int k){
	if(fa[k]==k) return k;
	return fa[k]=find(fa[k]);
}
void Kruskal(){
	for(int i=1;i<=n<<1;i++) fa[i]=i; // 预处理并查集
	int j=1; sort(a+1,a+1+m);
	for(int i=1;i<n;i++){
		while(find(a[j].u)==find(a[j].v)) j++;
		int fu=find(a[j].u),fv=find(a[j].v);
		used[a[j].id]=1; // 记录这条边在最小生成树上
		E[i+n].push_back(fu); // 重构树新建的节点和已有的两个节点连边（注意是 find(u) 和 find(v)，不是直接连边！）
		E[i+n].push_back(fv);
		f[fu][0]=f[fv][0]=i+n; // 预处理出 LCA 的第一层
		fa[fu]=fa[fv]=i+n; // 并查集合并（这里和普通 Kruskal 不同，是把 u 和 v 一起合并到新建的节点上，这样方便计算）
		w[i+n]=a[j].w; // 新建节点的点权就是边权
		sum+=a[j].w; // 计算最小生成树大小
		j++;
	}
}
void dfs(int u,int fa){
	dep[u]=dep[fa]+1; // 计算深度
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(v==fa) continue;
		dfs(v,u);
	}
}
int LCA(int u,int v){ // 求 LCA
	if(dep[u]<dep[v]) swap(u,v);
	int tmp=dep[u]-dep[v];
	for(int j=22;j>=0;j--)
		if((tmp>>j)&1) u=f[u][j]; // 先跳到同一深度
//	cout<<u<<" "<<v<<" "<<dep[u]<<" "<<dep[v]<<endl;
	if(u==v) return u;
	for(int j=22;j>=0;j--){
		if(f[u][j]==f[v][j]) continue;
		u=f[u][j],v=f[v][j]; // 再一起往上跳
	}
	return f[u][0];
}
signed main(){
	n=qr(),m=qr();
	for(int i=1;i<=m;i++){
		a[i]=(Edge){qr(),qr(),qr(),i}; // 建边
	}
	Kruskal(); // 最小生成树 + Kruskal 重构树
	dfs(n+n-1,0); // 预处理每个点的深度，供 LCA 用
	for(int j=1;j<=22;j++)
		for(int i=1;i<=n<<1;i++)
			f[i][j]=f[f[i][j-1]][j-1]; // 倍增预处理 LCA
	sort(a+1,a+1+m,cmp); // 记得重新排回输入顺序！
	for(int i=1;i<=m;i++){
		if(used[i]) cout<<sum<<endl; // 如果是最小生成树上的边，那么直接输出最小生成树大小
		else{
			int t=LCA(a[i].u,a[i].v); // 算出重构树的 LCA
//			cout<<a[i].u<<" "<<a[i].v<<" "<<t<<endl;
			cout<<sum-w[t]+a[i].w<<endl; // 计算答案
		}
	}
	return 0;
}
```

目测代码相对于许多题解的树剖常数较小并且简洁qwq

---

## 作者：tommymio (赞：4)

求出必然包含第 $i$ 条边的 $\text{MST}$，可以想到是先求出原图的最小生成树 $T$，再在 $T$ 上加上第 $i$ 条边，并删去一条边令得到的生成树权值最小。

对于每个确定的 $i$，第 $i$ 条边的权值是一个定值，自然删去的边权最大，才能取到最小权值和。在最小生成树上加上第 $i$ 条边 $(x,y)$，记这个图为 $G'$，必然构成一个环 $x\to y\to \text{lca}(x,y)$。如下图所示，蓝色的虚线边为加入的第 $i$ 条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/8z4g8c1f.png)

为了使删去一条边后 $G'$ 变为树，我们只能断开环上的边，也就是只能删除 $x\to y$ 路径上最大的边。求 $x\to y$ 路径上最大的边可以使用倍增 $/$ 树剖+$\text{ST}$ 表轻松实现，总时间复杂度为 $O(m+n \log n)$。

```cpp
#include<cstdio>
#include<algorithm>
typedef long long ll;
int cnt=0;
struct edge {int x,y,w,id;} e[200005];
int fa[200005];
int h[200005],to[400005],ver[400005],w[400005];
int f[200005][25],g[200005][25],dep[200005],rev[200005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x,int y,int z) {to[++cnt]=y;ver[cnt]=h[x];w[cnt]=z;h[x]=cnt;}
inline bool cmp(const edge &x,const edge &y) {return x.w<y.w;}
inline void swap(int &x,int &y) {int tmp=y;y=x;x=tmp;}
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline int find(int x) {return x==fa[x]? x:fa[x]=find(fa[x]);}
inline void prework(int x) {
	for(register int i=1;i<=20;++i) f[x][i]=f[f[x][i-1]][i-1],g[x][i]=max(g[x][i-1],g[f[x][i-1]][i-1]);
	for(register int i=h[x];i;i=ver[i]) {int y=to[i]; if(y==f[x][0]) continue; f[y][0]=x; g[y][0]=w[i]; dep[y]=dep[x]+1; prework(y);}
}
inline int ask(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	int res=0;
	for(register int i=20;i>=0;--i) {if(dep[f[x][i]]>=dep[y]) {res=max(res,g[x][i]);x=f[x][i];}} if(x==y) return res;
	for(register int i=20;i>=0;--i) if(f[x][i]!=f[y][i]) {res=max(res,max(g[x][i],g[y][i]));x=f[x][i];y=f[y][i];}
	return max(res,max(g[x][0],g[y][0]));
}
int main() {
	int n=read(),m=read(); ll sum=0;
	for(register int i=1;i<=n;++i) fa[i]=i;
	for(register int i=1;i<=m;++i) {e[i].x=read();e[i].y=read();e[i].w=read();e[i].id=i;}
	std::sort(e+1,e+1+m,cmp);
	for(register int i=1;i<=m;++i) rev[e[i].id]=i;
	for(register int i=1;i<=m;++i) {
		int fx=find(e[i].x),fy=find(e[i].y);
		if(fx!=fy) {sum+=e[i].w; add(e[i].x,e[i].y,e[i].w); add(e[i].y,e[i].x,e[i].w); fa[fx]=fy;}
	}
	dep[1]=1; prework(1);
	for(register int i=1;i<=m;++i) {printf("%lld\n",sum-ask(e[rev[i]].x,e[rev[i]].y)+e[rev[i]].w);}
	return 0;
}
```

---

## 作者：跃动の光は (赞：4)

# 题目大意

给出一个无向图，每条边有边权，求出包含第i条边的最小生成树的权值

# 思路

这道题还是比较妙的，首先想到每次跑$m$遍最小生成树，强制选第$i$条边，但数据范围是$n,m\leq 2 \times 10^5$的，绝逼会爆(~~不然这道题也不会是CF的E题~~)。

有一个巧妙的方法，就是跑一遍最小生成树，查询**去掉一条权值最大的边**，然后**把这条边换成当前查询的边**。这样就跑的快多了。

先证明一波。设原图的最小生成树有$n$个点，$n-1$条边，那么连接点$u$和点$v$，它就变成了一个图，**并且出现了环**，那么**任意删去点$u$和点$v$环上的一条边**，这个环就消失了，并且**它又变成了一棵树**，(还是$n$个点，$n-1$条边，且任意两点可互达，没有环，不信的童鞋可以自己画一下)

然后就出现了两种情况：

①：第$i$条边在最小生成树上，那么答案就是最小生成树的边权和。

②：第$i$条边不在最小生成树上，就是上面说的那个方法，**加上这条边的权值，同时删去这条边的端点$u$,$v$之间权值最大的那条边（当然是在最小生成树里的）**，这样得出的树**一定是包含这条边的最小生成树**（可能会有点绕，建议画图理解一下）

~~(当然也可以像我一样懒一点直接混成一种情况考虑，这样也是正确的)~~

对于第一种情况，直接输出最小生成树的权值和。第二种情况稍微复杂一点，要求树上两点之间的边权最大值，就可以用各种玄学数据结构了。本蒟蒻用的是倍增lca ~~(因为太菜了)~~ 。

~~（码风有些奇怪，不喜误喷。）~~


### 上代码
------------
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std ;
typedef long long ll ;
const int maxn=200000+20 ;
int p[maxn][30] ;
ll ans[maxn][30] ; 
int N,M ;
int head[maxn],tot,deep[maxn];
int fa[maxn] ;
ll dis ; //最小生成树的权值和 
struct node{
	int v,next ;
	ll w ;
}e[maxn<<1]; 
struct edge{
	int v;
	ll w ;
	int u ;
}krus[maxn<<1],krus2[maxn<<1];
inline bool cmp(edge a,edge b){

	return a.w<b.w ;
} 
inline void addedge(int u,int v,ll w){
	e[++tot].v=v ;
	e[tot].w=w ;
	e[tot].next=head[u] ;
	head[u]=tot ;
}
inline int getf(int a){
	return fa[a]==a?a:fa[a]=getf(fa[a]) ;
}
inline void kruskal(){
	for(int i=1;i<=N;i++) fa[i]=i ;
	sort(krus+1,krus+M+1,cmp) ;
	int cnt=0 ;
	for(int i=1;i<=M;i++){
		int u=krus[i].u,v=krus[i].v ;
		if(getf(u)==getf(v)) continue ;
			fa[getf(v)]=getf(u) ;
			cnt++ ;
			addedge(u,v,krus[i].w) ;
			addedge(v,u,krus[i].w) ;
			dis+=krus[i].w ;
		if(cnt==N-1) break ; 
	} //正常的kruskal最小生成树 
	return ;
}
inline void dfs(int u,int fa,ll val){
	deep[u]=deep[fa]+1 ;
	p[u][0]=fa ;
	ans[u][0]=val ;
	for(int j=1;j<=20;j++){

		p[u][j]=p[p[u][j-1]][j-1] ;
		ans[u][j]=max(ans[u][j-1],ans[p[u][j-1]][j-1]) ;
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v ;
		if(v==fa) continue ;
		dfs(v,u,e[i].w) ;
	} 
}
inline ll lca(int a,int b){

	ll tryans=0 ;
	if(deep[a]>deep[b]) swap(a,b) ;
	for(int j=20;j>=0;j--){

		if(deep[a]<=deep[p[b][j]]){

			tryans=max(tryans,ans[b][j]) ;
			b=p[b][j] ;
		}
	}
	if(a==b) return tryans  ;
	for(int j=20;j>=0;j--){

		if(p[a][j]==p[b][j]) continue ;
			tryans=max(ans[b][j],max(tryans,ans[a][j])) ;
			b=p[b][j] ;
			a=p[a][j] ;
	}
	// 倍增求出 a,b 之间 边权 的最大值 
	return max(ans[b][0],max(tryans,ans[a][0])) ;
}
int main(){
	scanf("%d%d",&N,&M) ;
	for(int i=1;i<=M;i++){
		scanf("%d%d%lld",&krus2[i].u,&krus2[i].v,&krus2[i].w) ;
		krus[i].u=krus2[i].u;
		krus[i].v=krus2[i].v;
		krus[i].w=krus2[i].w;
	}
	kruskal() ;
	dfs(1,0,0) ;//倍增 预处理 
	ll nowans ;
	for(int i=1;i<=M;i++){
		nowans=dis+krus2[i].w-lca(krus2[i].u,krus2[i].v) ;// 替换操作，本蒟蒻因为太懒了就把两种情况混在一起，证明略 
		printf("%lld\n",nowans) ; 
	}
	return 0 ;
}

```



---

## 作者：NaCly_Fish (赞：4)

这题要求出必须包含第$i$条边的最小生成树大小，可以考虑先跑一遍最小生成树，然后我们分两种情况讨论：
- 1：当前边在最小生成树上  

这种情况没什么好说的，结果显然为最小生成树的大小，直接输出即可。  

- 2：当前边不在最小生成树上  

假设这条边连接$u$和$v$两个节点，为了保证连出来的图仍然是一棵树，就必须拆掉最小生成树中$u,v$路径上的一条边。  
因为我们还要保证新的树权值和最小，所以把权值最大的边拆掉就好。

由于这题没有修改，所以求树上路径最大边权是可以$\Theta(\log n)$做的。  
这里我没有用倍增，在树剖第二遍dfs时，每个点记录到重链顶的最大权值即可。   
这个可以递推得到，时间复杂度还是线性的。   
加了这个小优化，跑的还算比较快，$8968\text{ms}$  

这题也有坑点，做边权树剖时，要注意边权转点权等细节，具体见代码。  
代码写的比较长，$194$行：  
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#define N 200003
#define ll long long
#define inf 0x3f3f3f3f
#define mid ((l+r)>>1)
#define ls (u<<1)
#define rs (u<<1|1)
using namespace std;

struct edge{
	int u,v,w,id;
	edge(int u=0,int v=0,int w=0,int id=0):u(u),v(v),w(w),id(id){}
	bool operator < (const edge& a) const{
		return w < a.w;
	}
};

int un[N],tpmax[N],top[N],son[N],fa[N],bd[N];
int size[N],dep[N],id[N],a[N],mx[N<<2];
edge e[N],selc[N],nsel[N];
int n,m,lena,lenb,cid;
ll sum;
ll ans[N];
vector<edge> adj[N];

inline void read(int &x);
void print(ll x);
inline int max(int x,int y);
void kruskal();
int find(int x);
void dfs1(int u,int f);
void dfs2(int u,int f);
void build(int u,int l,int r);
inline void push_up(int u);
int inline query(int l,int r);
int qwq(int nl,int nr,int l,int r,int u);
inline int queryPath(int u,int v);

int main(){
	int u,v,w,t;
	read(n),read(m);
	for(int i=1;i<=n;++i) un[i] = i;
	for(int i=1;i<=m;++i){
		read(u),read(v),read(w);
		e[i] = edge(u,v,w,i);
	}
	kruskal();
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=lena;++i)
		ans[selc[i].id] = sum; //kruskal的排序打乱了边的顺序，所以要用一个答案数组来记录
	for(int i=1;i<=lenb;++i){
		u = nsel[i].u,v = nsel[i].v;
		w = nsel[i].w;
		t = queryPath(u,v);
		ans[nsel[i].id] = sum+w-t;
	}
	for(int i=1;i<=m;++i){
		print(ans[i]);
		putchar('\n');
	}
	return 0;
}

int qwq(int nl,int nr,int l,int r,int u){
    int res = -inf;
    if(nl<=l&&r<=nr) return mx[u];
    if(nl<=mid) res = max(res,qwq(nl,nr,l,mid,ls));
    if(nr>mid) res = max(res,qwq(nl,nr,mid+1,r,rs));
    push_up(u);
    return res;
}

inline int query(int l,int r){
	return qwq(l,r,1,n,1);
}

inline void push_up(int u){
	mx[u] = max(mx[ls],mx[rs]);
}

void build(int u,int l,int r){
	if(l==r){
		mx[u] = bd[l];
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(u);
}

inline int queryPath(int u,int v){
	int res = -inf;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		res = max(res,tpmax[u]);
		u = fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	res = max(res,query(id[u]+1,id[v])); //为了避开两点的lca，这里查询要+1
	return res;
}

void dfs1(int u,int f){
	fa[u] = f;
	dep[u] = dep[f]+1;
	size[u] = 1;
	int t = -1,v,l = adj[u].size();
	for(int i=0;i<l;++i){
		v = adj[u][i].v;
		if(v==f){
			a[u] = adj[u][i].w; //每个点的点权为到其父亲边的边权
			continue;
		}
		dfs1(v,u);
		size[u] += size[v];
		if(size[v]>t){
			t = size[v];
			son[u] = v;
		}
	}
}

void dfs2(int u,int f){
	id[u] = ++cid;
	bd[cid] = a[u];
	top[u] = f;
	if(u==f) tpmax[u] = a[u];
	else tpmax[u] = max(a[u],tpmax[fa[u]]); //记录每个点到其重链顶端的最大权值
	if(son[u]==0) return;
	dfs2(son[u],f);
	int v,l = adj[u].size();
	for(int i=0;i<l;++i){
		v = adj[u][i].v;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}

void kruskal(){
	int u,v,w,j,cnt = 0;
	sort(e+1,e+1+m);
	for(int i=1;i<=m;++i){
		if(cnt==n-1){
			j = i;
			break;
		}
		u = e[i].u,v = e[i].v;
		w = e[i].w;
		if(find(u)==find(v)){
			nsel[++lenb] = e[i];
			continue;
		}
		sum += w;
		un[find(u)] = find(v);
		++cnt;
		adj[u].push_back(edge(u,v,w,e[i].id));
		adj[v].push_back(edge(v,u,w,e[i].id));
		selc[++lena] = e[i];
	}
	for(int i=j;i<=m;++i) nsel[++lenb] = e[i];
}

int find(int x){
	if(x==un[x]) return x;
	un[x] = find(un[x]);
	return un[x];
}

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
}

void print(ll x){
    if(x>9) print(x/10);
    putchar(x%10+'0');
}

inline int max(int x,int y){
	return x>y?x:y;
}
```

---

## 作者：Sangber (赞：2)

~~好像还没有树剖的题解？~~

### 题目描述
给定一张$n$个点，$m$条边的无向图，要求对于每一条边所在生成树的最小权值。

----
### 基本思路
首先对原图跑一遍$Kruskal$，在$MST$上再跑树剖，维护一下最大边权  
（我用的线段树，不过好像树状数组也能做？[戳这里](https://www.luogu.org/blog/Chanis/super-BIT)）  
然后对于每一条边，判断一下：  
若该边为$MST$上的边，则直接输出$MST$的权，否则输出$MST+dis(e)-qmax(u,v)$  
（$dis(e)$为当前这条边的权，$u,v$为该边两端的点）  

### 细节注意事项
1. 记得开$long\ long$
1. 这题还是要**边权转点权**，记得别把$LCA$算进来~~应该没人和我一样吧~~

----
### 参考代码
```cpp
#include <cstdio>
#include <algorithm>
#define rg register
#define int long long
const int MAXN = 200010;
using namespace std;
inline int max(int a, int b) { return a > b ? a : b; }
inline void swap(int& a, int& b) { int t = a; a = b; b = t; }
inline int read() {
    int s = 0; bool f = false; char c = getchar();
    while (c < '0' || c > '9') f |= (c =='-'), c = getchar();
    while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar();
    return f ? -s : s;
}
int n, m; struct edge{ int u, v, d, p; }g[MAXN];
inline bool cmp1(const edge& x, const edge& y) { return x.d < y.d; }
inline bool cmp2(const edge& x, const edge& y) { return x.p < y.p; }
int tot, head[MAXN], nxt[MAXN << 1], ver[MAXN << 1], w[MAXN << 1];
inline void Add_edge(int u, int v, int d)
{ nxt[++tot] = head[u], head[u] = tot, ver[tot] = v, w[tot] = d; }
int fa[MAXN], mst[MAXN];
inline int findd(int k) { return fa[k] == k ? k : fa[k] = findd(fa[k]); }
inline void unionn(int u, int v) { fa[findd(u)] = findd(v); }
inline int Kruskal() {
    int MST = 0;
    for (rg int i = 1; i <= n; ++i) fa[i] = i;
    sort(g + 1, g + 1 + m, cmp1);
    for (rg int u, v, d, i = 1; i <= m; ++i) {
        u = g[i].u, v = g[i].v, d = g[i].d;
        if (findd(u) == findd(v)) continue;
        MST += d, mst[g[i].p] = 1, unionn(u, v), Add_edge(u, v, d), Add_edge(v, u, d);
    }
    sort(g + 1, g + 1 + m, cmp2);
    return MST;
}
int val[MAXN], Max[MAXN << 2];
int top[MAXN], seg[MAXN], rev[MAXN];
int dep[MAXN], son[MAXN], siz[MAXN], father[MAXN];
inline int lc(int rt) { return rt << 1; }
inline int rc(int rt) { return rt << 1 | 1; }
inline void pushup(int rt) { Max[rt] = max(Max[lc(rt)], Max[rc(rt)]); }
inline void build(int rt, int l, int r) {
    if (l == r) { Max[rt] = val[rev[l]]; return; }
    int mid = (l + r) >> 1;
    build(lc(rt), l, mid), build(rc(rt), mid + 1, r), pushup(rt);
}
inline int query(int rt, int l, int r, int x, int y) {
    if (x <= l && r <= y) return Max[rt];
    int mid = (l + r) >> 1, res = 0;
    if (x <= mid) res = max(res, query(lc(rt), l, mid, x, y));
    if (y > mid) res = max(res, query(rc(rt), mid + 1, r, x, y));
    return res;
}
inline void dfs1(int u, int fa) {
    siz[u] = 1, father[u] = fa, dep[u] = dep[fa] + 1;
    for (rg int v, i = head[u]; i; i = nxt[i])
        if (!dep[v = ver[i]]) {
            dfs1(v, u), siz[u] += siz[v], val[v] = w[i];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
}
inline void dfs2(int u, int topf) {
    top[rev[seg[u] = ++seg[0]] = u] = topf;
    if (!son[u]) return; dfs2(son[u], topf);
    for (rg int v, i = head[u]; i; i = nxt[i])
        if (!top[v = ver[i]]) dfs2(v, v);
}
inline int qmax(int x, int y) {
    int res = 0; 
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        res = max(res, query(1, 1, n, seg[top[x]], seg[x]));
        x = father[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return max(res, query(1, 1, n, seg[x] + 1, seg[y]));
}
signed main() {
    n = read(), m = read();
    for (rg int u, v, d, i = 1; i <= m; ++i)
        u = read(), v = read(), d = read(), g[i] = (edge) { u, v, d, i };
    int MST = Kruskal();
    dfs1(1, 0), dfs2(1, 1), build(1, 1, n);
    for (rg int i = 1; i <= m; ++i) {
        if (mst[i]) printf("%lld\n", MST);
        else printf("%lld\n", MST + g[i].d - qmax(g[i].u, g[i].v));
    }
    return 0;
}

```
**完结撒花**$qwq$

---

## 作者：KSToki (赞：1)

这道题其实和次小生成树挺像的。

我们如果暴力地每次求最小生成树，那复杂度会达到 $O(m^2)$，显然会 T。那么我们考虑每一条边，如果它在最小生成树上，那答案就是最小生成树的大小；如果不在，设两个端点为 $x,y$，那么在最小生成树上加上这条边并删去路径 $x->lca->y$ 上边权最大的边即可。我们在倍增求 LCA 的过程中就顺便处理出来了，时间复杂度 $O(mlogn)$，可以通过。

注意要开 `long long`，并且排序后边的顺序会打乱，需要用一个数组存答案。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	char ch=getchar();
	while(ch<'0'||ch>'9')
	    ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res;
}
struct edge
{
	int x,y;
	int w;
	int id;
}e[200001];
int n,m,father[200001],cnt,head[200001],to[400001],nxt[400001],w[400001],tot,depth[200001],up[200001][19],Max[200001][19];
ll sum,res[200001];//能不用long long就不用
bool inmst[200001];
inline bool cmp(edge e1,edge e2)
{
	return e1.w<e2.w;
}
int find(int x)//并查集
{
	if(x==father[x])
		return x;
	return father[x]=find(father[x]);
}
inline void add(int x,int y,int z)//建图
{
	to[++tot]=y;
	w[tot]=z;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfs(int x,int fa)//倍增预处理
{
	up[x][0]=fa;
	depth[x]=depth[fa]+1;
	for(register int i=head[x];i;i=nxt[i])
		if(to[i]!=fa)
		{
			Max[to[i]][0]=w[i];
			dfs(to[i],x);
		}
}
int main()
{
	n=read();
	m=read();
	for(register int i=1;i<=n;++i)
		father[i]=i;
	for(register int i=1;i<=m;++i)
	{
		e[i].x=read();
		e[i].y=read();
		e[i].w=read();
		e[i].id=i;
	}
	sort(e+1,e+m+1,cmp);
	for(register int i=1;cnt<n-1;++i)
	{
		int xx=find(e[i].x),yy=find(e[i].y);
		if(xx==yy)
			continue;
		++cnt;
		father[yy]=xx;
		sum+=e[i].w;
		inmst[i]=1;
		add(e[i].x,e[i].y,e[i].w);
		add(e[i].y,e[i].x,e[i].w);
	}//跑出最小生成树并建树
	dfs(1,0);
	for(register int i=1;i<19;++i)
		for(register int j=1;j<=n;++j)
		{
			up[j][i]=up[up[j][i-1]][i-1];
			Max[j][i]=max(Max[j][i-1],Max[up[j][i-1]][i-1]);
		}//预处理
	for(register int i=1;i<=m;++i)//倍增求解
	{
		if(inmst[i])
		{
			res[e[i].id]=sum;
			continue;
		}
		int maxx=0,tx=e[i].x,ty=e[i].y;
		if(depth[tx]<depth[ty])
			swap(tx,ty);
		for(register int j=18;j>=0;--j)
			if(depth[up[tx][j]]>=depth[ty])
			{
				maxx=max(maxx,Max[tx][j]);
				tx=up[tx][j];
			}
		if(tx==ty)
		{
			res[e[i].id]=sum+e[i].w-maxx;
			continue;
		}
		for(register int j=18;j>=0;--j)
			if(up[tx][j]!=up[ty][j])
			{
				maxx=max(maxx,max(Max[tx][j],Max[ty][j]));
				tx=up[tx][j];
				ty=up[ty][j];
			}
		maxx=max(maxx,max(Max[tx][0],Max[ty][0]));
		res[e[i].id]=sum+e[i].w-maxx;
	}
	for(register int i=1;i<=m;++i)
		printf("%lld\n",res[i]);//完！
	return 0;
}
```


---

## 作者：Islauso (赞：1)

题意很清楚，给定一张带权无向图，对于图上的每一条边，询问包括这一条边的生成树中边权权值之和最小的。

首先想到的方法是每次都先把要求的这条边加入最小生成树，然后跑一遍 Kruskal，但用膝盖想一下都知道这样肯定是会 T 飞的，所以我们可以直接在原来的最小生成树上进行修改，也就是说，把这一条边强行塞进最小生成树，由于这样很明显会形成一个环，所以我们还需要从这个环里再删掉一条边。

假设此时这条边连接的是 $u$ 和 $v$ 两个点，则从 $u$ 到 $v$ 的最短路径应该会经过 $\operatorname{LCA}(u,v)$，所以这个环应该是从 $u$ 到 $\operatorname{LCA}(u,v)$ 再到 $v$ 最后回到 $u$，因此，我们需要删掉的边应该是在从 $u$ 到 $\operatorname{LCA}(u,v)$ 再到 $v$ 这条路径上，又因为要求新的最小生成树的权值和最小，所以我们应该尽量删掉权值较大的边。

因此，这道题就变成了先求出最小生成树，然后对于每一条边，询问其两个端点在树上的最短路径中边权最大的边。

这种问题本来可以用树剖做，但由于没有修改操作，不需要那么麻烦~~其实就是懒~~，使用倍增求 LCA，在求每个点的第 $2^i$ 个父亲的时候，另外开一个数组，求每个点到它第 $2^i$ 个父亲这条路径上最大的边权，然后在往上跳的时候顺便用一个变量统计一下就可以了，具体的看代码。

```cpp
#include<bits/stdc++.h>
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
using namespace std;
struct Edge
{
	long long u;
	long long v;
	long long c;
	long long id;
};
bool cmp(Edge a,Edge b)
{
	return a.c<b.c;
}
bool cmp2(Edge a,Edge b)//这个是求完最小生成树后还原所有边的顺序的，虽然也可以再开一个数组，但是我懒。
{
	return a.id<b.id;
}
Edge a[200001];
vector<pll> edge[200001];
long long n,m,cnt,k,log2n,f[200001],dep[200001],fa[200001][21],maxn[200001][21];
long long find(long long x)
{
	return f[x]==x? f[x]:f[x]=find(f[x]);
}
void dfs(long long u,long long father)
{
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(long long i=1;(1<<i)<=dep[u];i++)
	{
		fa[u][i]=fa[fa[u][i-1]][i-1];
		maxn[u][i]=max(maxn[u][i-1],maxn[fa[u][i-1]][i-1]);//求 u 到它第 2^i 个父亲这条路径上最大的边权。
	}
	for(long long i=0;i<edge[u].size();i++)
	{
		long long v=edge[u][i].first,c=edge[u][i].second;
		if(v!=father)
		{
			maxn[v][0]=c;//在搜索儿子前先把这个初始化一下。
			dfs(v,u);
		}
	}
}
long long lca(long long u,long long v)
{
	long long depu=dep[u],depv=dep[v],ans=0;//ans 用来统计最大边权。
	if(depu!=depv)
	{
		if(depu<depv)
		{
			swap(depu,depv);
			swap(u,v);
		}
		for(long long i=0;(1<<i)<=depu-depv;i++)
			if((depu-depv)&(1<<i))
			{
				ans=max(ans,maxn[u][i]);
				u=fa[u][i];
			}
	}
	if(u==v)
		return ans;
	for(long long i=log2n;i>=0;i--)
		if(fa[u][i]!=fa[v][i])
		{
			ans=max(ans,max(maxn[u][i],maxn[v][i]));
			u=fa[u][i];
			v=fa[v][i];
		}
	return max(ans,max(maxn[u][0],maxn[v][0]));
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<=n;i++)
		f[i]=i;
	for(long long i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld",&a[i].u,&a[i].v,&a[i].c);
		a[i].id=i;
	}
	sort(a+1,a+1+m,cmp);
	for(long long i=1;i<=m;i++)//Kruskal 求最小生成树。
	{
		long long t1=find(a[i].u),t2=find(a[i].v);
		if(t1!=t2)
		{
			f[t1]=t2;
			cnt++;
			k+=a[i].c;
			edge[a[i].u].push_back(mp(a[i].v,a[i].c));
			edge[a[i].v].push_back(mp(a[i].u,a[i].c));
		}
		if(cnt==n-1)
			break;
	}
	sort(a+1,a+1+m,cmp2);
	log2n=log(n)/log(2)+0.5;
	dfs(1,0);
	for(long long i=1;i<=m;i++)
		printf("%lld\n",k+a[i].c-lca(a[i].u,a[i].v));//加上当前这条的边权，删去路径上最大的边权。
	return 0;
}
```


一开始的时候我还想着要不要判断一下这条边是否是树边，但其实如果是树边的话，那么加上的也是它，删去的也是它，根本没有发生变化，所以没必要特判。

另外，这道题一定要开 long long，因为 $10^9\times 2\cdot10^5$ 很明显炸 int 了。

---

## 作者：MILLOPE (赞：1)

## 题目
给你n个点，m条边，如果对于一个最小生成树中要求必须包括第i(1<=i<=m)条边，那么最小生成树的权值总和最小是多少。

输入格式

第一行n，m

后面m行每行u,v,w代表一条边

输出格式

m行，第i行一个整数代表包括第i条边时的最小权值和

[CF609E](https://www.luogu.org/problemnew/show/CF609E)

## 题解
- 先对原图跑一遍最小生成树
- 对于在最小生成树中的边直接输出最小生成树的边权和
- 将其余边加进去后（其实不用真的加进去），会构成一个环，我们只需找到环上除刚加进去的那条边权值最大的边即可
- 可以树链剖分来找

## code
```cpp
#include <bits/stdc++.h>
using namespace std; 
const int maxn = 200000 + 1000; 
const int inf = 0x3f3f3f3f; 
typedef long long LL; 

template <class T> 
inline void read(T &s) {
	s = 0; 
	T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w; 
}

LL SumTree; 
LL tree[maxn * 4], ans[maxn], val[maxn][5]; 
int n, m, cnt, tot, size_val; 
int f[maxn], dep[maxn], siz[maxn], fat[maxn]; 
int idx[maxn], top[maxn], son[maxn], lin[maxn]; 
struct MST { 
	int from, to, id; 
	LL dis; 
	bool operator <(const MST &A) const {
		return dis < A.dis; 
	}
} t[maxn * 4]; 
struct node{ int next, to; } edge[maxn << 1]; 

inline int get(int k) { 
	return f[k] == k ? f[k] : f[k] = get(f[k]);
}

inline void add(int from, int to) {
	edge[++tot].to = to; 
	edge[tot].next = lin[from]; 
	lin[from] = tot; 
}

void Kruskal() {
	sort(t + 1, t + m + 1); 
	for (int i = 1; i <= n; ++i) f[i] = i; 
	for (int i = 1; i <= m; ++i) {
		int u = get(t[i].from), v = get(t[i].to); 
		int dis = t[i].dis, id = t[i].id; 
		if (f[u] != v) {
			f[u] = v; 
			SumTree += dis; 
			add(t[i].from, t[i].to); 
			add(t[i].to, t[i].from); 
			++size_val; 
			val[size_val][0] = t[i].from; 
			val[size_val][1] = t[i].to; 
			val[size_val][2] = t[i].dis; 
		}
	}
}

void dfs1(int u, int fa, int depth) {
	siz[u] = 1; 
	fat[u] = fa; 
	dep[u] = depth; 
	int maxson = -1; 
	for (int i = lin[u]; i; i = edge[i].next) {
		int v = edge[i].to; 
		if (v == fa) continue; 
		dfs1(v, u, depth + 1); 
		siz[u] += siz[v]; 
		if (siz[v] > maxson) {
			maxson = siz[v]; 
			son[u] = v; 
		}
	}
}

void dfs2(int u, int tp) {
	idx[u] = ++cnt; 
	top[u] = tp; 
	if (!son[u]) return ; 
	dfs2(son[u], tp); 
	for (int i = lin[u]; i; i = edge[i].next) {
		int v = edge[i].to; 
		if (!idx[v]) 
			dfs2(v, v); 
	}
}

void update(int p, int l, int r, int pos, int v) {
	if (l == r) {
		tree[p] = v; 
		return ; 
	}
	int mid = (l + r) >> 1; 
	if (pos <= mid) update(p<<1, l, mid, pos, v); 
	else update(p<<1|1, mid + 1, r, pos, v); 
	tree[p] = max(tree[p<<1], tree[p<<1|1]); 
}

LL queryMax(int p, int l, int r, int x, int y) {
	if (x > r || y < l) return 0; 
	if (x <= l && y >= r) return tree[p]; 
	int mid = (l + r) >> 1; 
	LL sum = 0ll; 
	sum = max(sum, queryMax(p<<1, l, mid, x, y)); 
	sum = max(sum, queryMax(p<<1|1, mid + 1, r, x, y)); 
	return sum; 
}

LL TreeMax(int x, int y) {
	LL sum = 0ll; 
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y); 
		sum = max(sum, queryMax(1, 1, cnt, idx[top[x]], idx[x])); 
		x = fat[top[x]]; 
	}
	if (x == y) return sum; 
	if (dep[x] > dep[y]) swap(x, y); 
	sum = max(sum, queryMax(1, 1, cnt, idx[son[x]], idx[y])); 
	return sum; 
}

int main() {
	read(n); read(m); 
	for (int i = 1; i <= m; ++i) {
		read(t[i].from), read(t[i].to), read(t[i].dis); 
		t[i].id = i; 
	}

	Kruskal(); 

	int rt = (n / 2) + 1; 
	dfs1(rt, 0, 1); 
	dfs2(rt, rt); 

	for (int i = 1; i <= size_val; ++i) {
		if (dep[val[i][0]] > dep[val[i][1]]) swap(val[i][0], val[i][1]); 
		update(1, 1, cnt, idx[val[i][1]], val[i][2]); 
	}

	for (int i = 1; i <= m; ++i) {
		ans[t[i].id] = SumTree + t[i].dis - TreeMax(t[i].from, t[i].to);  
	}
	for (int i = 1; i <= m; ++i) 
		printf("%lld\n", ans[i]); 
	return 0; 
}

```


---

## 作者：Sol1 (赞：1)

放一篇倍增的题解。

我们可以观察到这样一个性质：在MST上面任意加一条边，就会形成恰好一个环。然后从这个环上面任意拆一条边，就又会形成一棵生成树。

那么这题的做法就很明显了：如果某条边就在MST上面，那么没什么可说的，就是MST权值；否则，我们从这条环上面拆掉除该边以外最大的一条边，就可以得到答案了。

在求MST加入边$(u,v)$后形成的环上的最大值时，我们实际要求的是$u$到$v$的路径上的最大边权。显然，这里可以用倍增优化。

总复杂度$\Theta(N \log N)$。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
//邻接表存边
struct Edge {
    long long to, nxt, len;
    Edge() {
        nxt = -1;
    }
};
//Kruskal存边，idx对应输入顺序
struct Edge2 {
    long long u, v, w, idx;
    bool operator < (const Edge2& e) const {
        return w < e.w;
    }
    bool operator > (const Edge2& e) const {
        return idx < e.idx;
    }
};
Edge e[400005];
Edge2 e2[200005];
long long n, m, hd[200005], pnt, fa[200005][25], dep[200005], rt[200005], mst, mx[200005][25];
bool book[200005];
//以下3个函数均为并查集操作
void Init() {
    for (long long i = 1;i <= n;i++) {
        rt[i] = i;
    }
}

long long GetRoot(long long v) {
    if (rt[v] == v) {
        return v;
    }
    rt[v] = GetRoot(rt[v]);
    return rt[v];
}

bool Merge(long long x, long long y) {
    long long u = GetRoot(x), v = GetRoot(y);
    if (u != v) {
        rt[v] = u;
        return 1;
    }
    return 0;
}
//在邻接表内加入一条边
void AddEdge(long long u, long long v, long long w) {
    e[++pnt].to = v;
    e[pnt].len = w;
    e[pnt].nxt = hd[u];
    hd[u] = pnt;
}

void Read() {
    scanf("%lld%lld", &n, &m);
    for (long long i = 1;i <= m;i++) {
        scanf("%lld%lld%lld", &e2[i].u, &e2[i].v, &e2[i].w);
        e2[i].idx = i;
    }
}
//以下两个函数为倍增预处理
void Dfs(long long u, long long f) {
    for (long long i = hd[u];i != -1;i = e[i].nxt) {
        if (e[i].to != f) {
            fa[e[i].to][0] = u;
            mx[e[i].to][0] = e[i].len;//倍增求最大值
            dep[e[i].to] = dep[u] + 1;
            Dfs(e[i].to, u);
        }
    }
}

void Prefix() {
    for (long long j = 1;j <= 20;j++) {
        for (long long i = 1;i <= n;i++) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
            mx[i][j] = max(mx[i][j - 1], mx[fa[i][j - 1]][j - 1]);
        }
    }
}
//求MST以及MST内有哪些边
void Kruskal() {
    sort(e2 + 1, e2 + m + 1);
    Init();
    long long cnt = 0;
    for (long long i = 1;i <= m;i++) {
        if (Merge(e2[i].u, e2[i].v)) {
            cnt++;
            mst += e2[i].w;
            AddEdge(e2[i].u, e2[i].v, e2[i].w);
            AddEdge(e2[i].v, e2[i].u, e2[i].w);
            book[e2[i].idx] = 1;
        }
        if (cnt == n - 1) {
            break;
        }
    }
    sort(e2 + 1, e2 + m + 1, greater <Edge2> ());
}
//求LCA
long long Lca(long long u, long long v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (long long i = 20;i >= 0;i--) {
        if (dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (long long i = 20;i >= 0;i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
//求链上最大值
long long QueryMax(long long u, long long v) {
    long long ans = 0;
    for (long long i = 20;i >= 0;i--) {
        if (dep[fa[u][i]] >= dep[v]) {
            ans = max(ans, mx[u][i]);
            u = fa[u][i];
        }
    }
    return ans;
}

void Solve() {
    for (long long i = 1;i <= m;i++) {
        if (book[i]) {
            printf("%lld\n", mst);
        } else {
            long long k = Lca(e2[i].u, e2[i].v);
            printf("%lld\n", mst - max(QueryMax(e2[i].u, k), QueryMax(e2[i].v, k)) + e2[i].w);//拆掉一条边再连上当前边
        }
    }
}

int main() {
	memset(hd, -1, sizeof(hd));
    Read();
    Kruskal();
    dep[1] = 1;
    Dfs(1, -1);
    Prefix();
    Solve();
    return 0;
}
```

---

## 作者：Delta_Rain (赞：1)

### solution CF609E

题意简单，求图上包含第$i$条边的最小生成树。

首先跑一遍Kruskal最小生成树，同时记录下在最小生成树上的边。

然后树链剖分维护边权最大值。

对于每条边，如果在最小生成树上，就直接输出最小生成树边权和。如果边x---y不在树上，删掉最小生成树上的在链x->y上的最大边并加入当前边即可。

### code

```cpp
#include <bits/stdc++.h>
const int M = 2e5 + 5;
int n, m, tot, uset[M], to[M << 1], nxt[M << 1], h[M], dfn[M], d[M], siz[M], son[M], top[M], f[M], you[M];
long long ans, now[M];
struct edge { int x, y, id; long long w; } a[M];
int operator <(edge ax, edge bx) { return ax.w < bx.w; }
int find(int x) { return uset[x] = uset[x] == x ? x : find(uset[x]); }
#define debug putchar('*')
void add_edge(int u, int v) {
    to[++tot] = v, nxt[tot] = h[u], h[u] = tot;
    to[++tot] = u, nxt[tot] = h[v], h[v] = tot;
}
void dfs(int x) {
    siz[x] = 1;
    for(int i = h[x]; i; i = nxt[i]) {
        if(d[to[i]]) continue;
        d[to[i]] = d[x] + 1, f[to[i]] = x;
        dfs(to[i]);
        siz[x] += siz[to[i]];
        if(siz[to[i]] > siz[son[x]]) son[x] = to[i];
    }
}
void sfd(int x, int tp) {
    top[x] = tp, dfn[x] = ++dfn[0];
    if(son[x]) sfd(son[x], tp);
    for(int i = h[x]; i; i = nxt[i])
        if(to[i] != f[x] && to[i] != son[x]) sfd(to[i], to[i]);
}
inline int lca(int x, int y) {
    for(; top[x] ^ top[y]; x = f[top[x]])
        if(d[top[x]] < d[top[y]]) std::swap(x, y);
    return d[x] < d[y] ? x : y;
}
long long tr[M << 2];
#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define mid (l + r >> 1)
long long qmax(int rt, int l, int r, int sl, int sr) {
    if(sl <= l && r <= sr) return tr[rt];
    long long ret = 0;
    if(sl <= mid) ret = std::max(ret, qmax(ls, l, mid, sl, sr));
    if(sr > mid) ret = std::max(ret, qmax(rs, mid + 1, r, sl, sr));
    return ret;
}
void modify(int rt, int l, int r, int pos, long long k) {
    if(l > pos || r < pos) return;
    if(l == r) { tr[rt] = k; return; }
    modify(ls, l, mid, pos, k), modify(rs, mid + 1, r, pos, k);
    tr[rt] = std::max(tr[ls], tr[rs]);
}
long long tree_max(int x, int y) {
    long long ret = 0;
    for(; top[x] ^ top[y]; x = f[top[x]])
        ret = std::max(ret, qmax(1, 1, n, dfn[top[x]], dfn[x]));
    return std::max(ret, qmax(1, 1, n, dfn[y] + 1, dfn[x]));
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i)
        scanf("%d%d%lld", &a[i].x, &a[i].y, &a[i].w), a[i].id = i;
    for(int i = 1; i <= n; ++i) uset[i] = i;
    std::sort(a + 1, a + m + 1);
    for(int i = 1, k; i <= m; ++i) {
        int fx = find(a[i].x), fy = find(a[i].y);
        if(fx ^ fy) uset[fx] = fy, ++k, add_edge(a[i].x, a[i].y), ans += a[i].w, you[a[i].id] = 1;
        if(k == n - 1) break;
    }
    d[1] = 1, f[1] = 1;
    dfs(1), sfd(1, 1);
    for(int i = 1; i <= m; ++i)
        if(you[a[i].id]) {
            if(d[a[i].x] > d[a[i].y]) modify(1, 1, n, dfn[a[i].x], a[i].w);
            else modify(1, 1, n, dfn[a[i].y], a[i].w);
        }
    for(int i = 1; i <= m; ++i) {
        if(you[a[i].id]) now[a[i].id] = ans;
        else {
            int acl = lca(a[i].x, a[i].y);
            now[a[i].id] = ans + a[i].w - std::max(tree_max(a[i].x, acl), tree_max(a[i].y, acl));
        }
    }
    for(int i = 1; i <= m; ++i)
        printf("%lld\n", now[i]);
}
```

---

## 作者：Night_Bringer (赞：0)

# 前言
[博客园体验更佳](https://www.cnblogs.com/C202202chenkelin/p/15033423.html)

[题目链接：CodeForces](https://codeforces.com/problemset/problem/609/E)
# 题意
给你 $n$ 个点，$m$ 条边，如果对于一个最小生成树中要求必须包括第 $i(1\leq i\leq m)$ 条边，那么最小生成树的权值总和最小是多少。
# 思路
首先求出该图的最小生成树。最小生成树的边的答案就是最小生成树的权值和。记录下来这个权值和，记为 $ans$。

考虑必须包含不在生成树中的边，强行加入了最小生成树对于答案的影响。

就相当于现将这条边加入生成树中，然后再跑 kruskal，需要找到被并查集查到相同的父亲的那条边，且这条边在最小生成树内。

可以发现，直接在生成树中加入这条边形成的环，都有可能受这条边的影响。

由于按照 kruskal 的思想，边是被排了序的，影响到的边，只有权值最大的一条。

于是可以维护不带修改的树上路径最大值。用LCA或者树剖+ST表/线段树 都可以维护。
# Code
开了long long就不会死。
```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define LL long long
const int MAXN = 2e5 + 5;
struct Edge {
	int To, Dis, Next;
};
int head[MAXN], tot = 1;
Edge edge[MAXN << 1];
void Addedge(int u, int v, int w) {
	edge[++tot].Next = head[u], edge[tot].To = v, edge[tot].Dis = w, head[u] = tot;
	edge[++tot].Next = head[v], edge[tot].To = u, edge[tot].Dis = w, head[v] = tot;
}
struct Edge1 {
	int u, v, w, id;
	friend bool operator < (Edge1 x, Edge1 y) {
		return x.w < y.w;
	}
};
Edge1 e[MAXN];
int dp[MAXN][40], maxn[MAXN][40];
int fa[MAXN], dep[MAXN], n, m;
bool flag[MAXN];
LL ans;
int Find(int x) {
	return fa[x] == x ? x : (fa[x] = Find(fa[x]));
}
void Union(int x, int y) {
	fa[Find(x)] = fa[Find(y)];
}
int Maxpast(int x, int y) {
	int res = 0;
	if (x == y) return res;
	if (dep[x] < dep[y])
		swap(x, y);
	for (int i = 30; i >= 0; i--) {
		if (dep[x] - (1 << i) >= dep[y]) {
			res = max(res, maxn[x][i]);
			x = dp[x][i];
		}
	}
	if (x == y) return res;
	for (int i = 30; i >= 0; i--) {
		if (dp[x][i] != dp[y][i]) {
			res = max(res, max(maxn[x][i], maxn[y][i]));
			x = dp[x][i];
			y = dp[y][i];
		}
	}
	res = max(res, max(maxn[x][0], maxn[y][0]));
	return res;
}
void dfs(int u, int fa) {
	dp[u][0] = fa;
	dep[u] = dep[fa] + 1;
	for (int i = head[u]; i; i = edge[i].Next) {
		int v = edge[i].To;
		if (v == fa) continue;
		dfs(v, u);
		maxn[v][0] = edge[i].Dis;
	}
}
bool cmp(Edge1 x, Edge1 y) {
	return x.id < y.id;
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
		e[i].id = i;
	}
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	sort(e + 1, e + 1 + m);
	for (int i = 1; i <= m; i++) {
		int u = Find(e[i].u), v = Find(e[i].v);
		if (u == v) continue;
		Union(u, v);
		ans += e[i].w;
		flag[e[i].id] = 1;
		Addedge(e[i].u, e[i].v, e[i].w);
	}
	dfs(1, 0);
	for (int j = 1; j <= 30; j++) {
		for (int i = 1; i <= n; i++) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
			maxn[i][j] = max(maxn[i][j - 1], maxn[dp[i][j - 1]][j - 1]);
		}
	}
	sort(e + 1, e + 1 + m, cmp);
	for (int i = 1; i <= m; i++) {
		LL tmp = 0;
		if (flag[i])
			tmp = ans;
		else
			tmp = ans - Maxpast(e[i].u, e[i].v) + e[i].w;
		printf("%lld\n", tmp);
	}
	return 0;
}
```

---

## 作者：lory1608 (赞：0)

其实这道题很像[P4180[BJWC2010]严格次小生成树](https://www.luogu.com.cn/problem/P4180)。
****

首先求出最小生成树，然后在最小生成树上建立数据结构（重链剖分，倍增，  $lct$），用来维护链上的最大值。

每次的答案就是（最小生成树的权值$+$该边边权$-$该边连接的两个点之间的链的权值最大值）。

用lct维护时，将边转化为一个点，向他所连得两个点连边即可（具体实现看代码）

**注意：一定要开long long**
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<bitset>
#define ll long long
#define ull unsigned long long
using namespace std;
const int maxn=4e5+5;
int fa[maxn],n,m,f[maxn],val[maxn];
ll ans[maxn];
ll sum;
struct edge
{
	int u,v,w,bh;
	inline bool operator<(const edge&rhs)const
	{
		return w<rhs.w;
	}
}e[maxn];
namespace LCT
{
	struct lct
	{
		int son[maxn][2],maxv[maxn];
		bool rev[maxn];
		inline void pushdown(int u)
		{
			if(rev[u])
			{
				rev[son[u][1]]^=1;
				rev[son[u][0]]^=1;
				swap(son[u][0],son[u][1]);
				rev[u]=0;
			}
		}
		inline void pushup(int u)
		{
			maxv[u]=max(val[u],max(maxv[son[u][0]],maxv[son[u][1]]));
		}
		inline bool nroot(int x)
		{
			return son[fa[x]][0]==x||son[fa[x]][1]==x;
		}
		inline void rotate(int x)
		{
			int y=fa[x],z=fa[y],k=son[y][1]==x;
			if(nroot(y))son[z][son[z][1]==y]=x;
			fa[x]=z;
			son[y][k]=son[x][k^1];
			fa[son[x][k^1]]=y;
			son[x][k^1]=y;
			fa[y]=x;
			pushup(y);
			pushup(x);
		}
		inline void pushall(int x)
		{
			if(nroot(x))pushall(fa[x]);
			pushdown(x);
		}
		inline void splay(int x)
		{
			pushall(x);
			while(nroot(x))
			{
				int y=fa[x],z=fa[y];
				if(nroot(y))
				{
					if((son[z][1]==y)^(son[y][1]==x))rotate(x);
					else rotate(y);
				}
				rotate(x);
			}
		}
		inline void access(int x)
		{
			for(int y=0;x;y=x,x=fa[x])
			{
				splay(x);
				son[x][1]=y;
				pushup(x);
			}
		}
		inline void makeroot(int x)
		{
			access(x);
			splay(x);
			rev[x]^=1;
		}
		inline int findroot(int x)
		{
			access(x);
			splay(x);
			pushdown(x);
			while(son[x][0])
			{
				x=son[x][0];
				pushdown(x);
			}
			splay(x);
			return x;
		}
		inline void link(int x,int y)
		{
			makeroot(x);
			if(findroot(y)!=x)
			{
				fa[x]=y;
			}
		}
		inline void split(int x,int y)
		{
			makeroot(x);
			access(y);
			splay(y);
		}
		inline int query(int x,int y)
		{
			split(x,y);
			return maxv[y];
		}
	}lct;
	inline void work()
	{
		for(int i=1;i<=m;++i)
		{
			ans[e[i].bh]=sum+e[i].w-lct.query(e[i].u,e[i].v);
		}
		for(int i=1;i<=m;++i)
		{
			printf("%lld\n",ans[i]);
		}
	}
}
namespace MST
{
	inline int get(int x)
	{
		if(x==f[x])return x;
		else return f[x]=get(f[x]);
	}
	inline void work()
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)f[i]=i;
		for(int i=1;i<=m;++i)
		{
			scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
			e[i].bh=i;
			val[i+n]=e[i].w;
		}
		sort(e+1,e+m+1);
		for(int i=1;i<=m;++i)
		{
			int fu=get(e[i].u),fv=get(e[i].v);
			if(fu==fv)continue;
			else
			{
				f[fu]=fv;
				LCT::lct.link(e[i].u,e[i].bh+n);
				LCT::lct.link(e[i].v,e[i].bh+n);
				sum+=e[i].w;
			}
		}
	}
}
int main()
{
	MST::work();
	LCT::work();
}
```

---

