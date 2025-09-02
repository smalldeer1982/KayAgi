# DFS

## 题目描述

给定一棵有 $n$ 个顶点的树 $T$。考虑一个初始等于 $T$ 的图 $G_0$。你将得到 $q$ 次操作，每次操作给出一对不同的整数 $u_i$ 和 $v_i$。

对于每一次操作 $i$（$1 \le i \le q$），我们定义图 $G_i$ 如下：

- 如果 $G_{i-1}$ 包含边 $\{u_i, v_i\}$，则将其删除，得到 $G_i$。
- 否则，在 $G_{i-1}$ 中加入这条边，得到 $G_i$。

形式化地，$G_i := G_{i-1} \triangle \{\{u_i, v_i\}\}$，其中 $\triangle$ 表示[对称差](https://en.wikipedia.org/wiki/Symmetric_difference)。

此外，保证 $T$ 始终是 $G_i$ 的子图。换句话说，操作不会删除 $T$ 中的边。

考虑一个连通图 $H$，对其进行一次深度优先搜索（DFS）。可以发现，遍历过程中访问到尚未访问的顶点所经过的边（即树边）会构成 $H$ 的一棵生成树。对于同一个图，这棵生成树通常不是唯一的——它依赖于起始顶点以及每个顶点邻居的遍历顺序。

我们称顶点 $w$ 是“好”的，如果存在一种邻居遍历顺序，使得从 $w$ 开始的 DFS 生成的生成树恰好为 $T$。对于每次操作 $i$（$1 \le i \le q$），请你求出当前图中“好”顶点的数量。

## 说明/提示

第一个样例如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044F/6fe1ac052613262c6f3f2a25dd747a307a471728.png)

第一次操作后，$G$ 包含所有三条可能的边。DFS 的结果如下：

- 若起点为 $1$，有两种邻居遍历顺序，分别为 $[2, 3]$ 或 $[3, 2]$。
  - 若选择前者，则先访问 $2$，无论后续如何，下一步都会访问 $3$，生成树包含边 $\{1,2\}$ 和 $\{2,3\}$，不等于 $T$。
  - 若选择后者，生成树包含边 $\{1,3\}$ 和 $\{2,3\}$。
  
  因此，无论如何排序，都无法使 DFS 生成 $T$，所以 $1$ 不是“好”顶点。
- 若起点为 $2$，有两种遍历顺序。若先访问 $3$，生成树为 $\{2,3\}$ 和 $\{1,3\}$，不等于 $T$。若先访问 $1$，只能继续访问 $3$，生成树为 $\{1,2\}$ 和 $\{1,3\}$，等于 $T$，所以 $2$ 是“好”顶点。
- 起点为 $3$ 的情况与 $2$ 对称，因此 $3$ 也是“好”顶点。

所以答案为 $2$。第二次操作后，$2$ 和 $3$ 之间的边被删除，$G = T$，无论起点如何，DFS 生成树都等于 $T$，所以答案为 $3$。

第二个样例中，每次操作后的“好”顶点集合分别为：

- $\{2, 3, 5\}$
- $\{3, 5\}$
- $\{3, 4, 5\}$
- $\{4, 5\}$
- $\{4, 5, 6\}$
- $\{5, 6\}$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
1 2
1 3
2 3
3 2
```

### 输出

```
2
3
```

## 样例 #2

### 输入

```
6 6
1 2
2 3
1 4
4 5
1 6
2 5
3 4
5 2
6 4
3 4
6 5
```

### 输出

```
3
2
3
2
3
2
```

# 题解

## 作者：caidzh (赞：6)

有一个结论是：对于任意图 dfs 树上的非树边相连的两个点，一个点是另一个点的祖先

也就是说，合法的点可以使得所有非树边都连接了一个点及其祖先

跑出原树的 dfs 序，原问题经过分类讨论可以转化为区间求交

但是这里的区间求交比较特殊，一个区间可以是不连续的

补集转化成求区间并，然后再做一个补集可以得到答案

区间并使用线段树维护
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ls (x<<1)
#define rs (x<<1|1)
#define db double
#define inf 2147483647
#define llinf 9223372036854775807
#define ll long long
#define ull unsigned long long
using namespace std;
typedef pair<int,int> PII;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=200010,mod=998244353;
int n,m;vector<int>g[maxn];
int dfn[maxn],sz[maxn],tot,jmp[maxn][20],dep[maxn];map<int,map<int,int> >M;
void dfs(int x,int fa){
	dfn[x]=++tot;sz[x]=1;dep[x]=dep[fa]+1;
	for(int i=1;i<=19;i++)jmp[x][i]=jmp[jmp[x][i-1]][i-1];
	for(int i=0;i<g[x].size();i++){
		int v=g[x][i];if(v==fa)continue;
		jmp[v][0]=x;dfs(v,x);sz[x]+=sz[v];
	}
}
int gets(int x,int y){
	for(int i=19;i>=0;i--)if(dep[jmp[x][i]]>dep[y])x=jmp[x][i];return x;
}
int cover[maxn<<2],len[maxn<<2];
void pushup(int x,int l,int r){
	if(cover[x]>0)len[x]=r-l+1;
	else if(l==r)len[x]=0;
	else len[x]=len[ls]+len[rs];
}
void update(int x,int l,int r,int L,int R,int k){
	if(L>R)return;
	if(L<=l&&r<=R){cover[x]+=k;pushup(x,l,r);return;}int mid=l+r>>1;
	if(L<=mid)update(x<<1,l,mid,L,R,k);
	if(R>mid)update(x<<1|1,mid+1,r,L,R,k);pushup(x,l,r);
}
int main(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		g[x].pb(y);g[y].pb(x);
	}dfs(1,0);
	while(m--){
		int x=read(),y=read();
		if(dfn[x]>dfn[y])swap(x,y);
		if(dfn[y]<=dfn[x]+sz[x]-1&&dfn[y]>=dfn[x]){
			int son=gets(y,x);
			if(M[x][y]){
				M[x][y]=0;
				update(1,1,n,dfn[son],dfn[y]-1,-1);
				update(1,1,n,dfn[y]+sz[y],dfn[son]+sz[son]-1,-1);
			}else{
				M[x][y]=1;
				update(1,1,n,dfn[son],dfn[y]-1,1);
				update(1,1,n,dfn[y]+sz[y],dfn[son]+sz[son]-1,1);
			}
		}else{
			if(M[x][y]){
				M[x][y]=0;
				update(1,1,n,1,dfn[x]-1,-1);
				update(1,1,n,dfn[x]+sz[x],dfn[y]-1,-1);
				update(1,1,n,dfn[y]+sz[y],n,-1);
			}else{
				M[x][y]=1;
				update(1,1,n,1,dfn[x]-1,1);
				update(1,1,n,dfn[x]+sz[x],dfn[y]-1,1);
				update(1,1,n,dfn[y]+sz[y],n,1);
			}
		}printf("%d\n",n-len[1]);
	}return 0;
}
```


---

## 作者：周小涵 (赞：4)

好点的计算比较困难，考虑我们用总点数减去不好的点个数就是答案。

我们分两种情况讨论 $x,y$ 的相对关系。

$1$. 如果 $x,y$ 不是祖先关系，那么除了 $x,y$ 子树内的点所有的点都会变成不好的点，因为一个点从 $x$ 子树往上遍历的话必会被 $x$ 卡住，此时出边只有 $x \to fa_x$ 和其他边，那么此时只要走 $x \to fa_x$ 这条边，回溯到 $x$ 的时候显然不用再走其他边。

$2$. 如果 $x,y$ 是祖先关系，我们设 $x$ 为祖先，$x \to y$ 路径上最接近 $x$ 的点为 $s$，那么变成不好的点就是 $s$ 子树内除了 $y$ 子树内的点以外的所有点，这个情况与第一种是类似的，手动模拟一下即可。

读者可以结合下面两幅图理解一下

![](https://cdn.luogu.com.cn/upload/image_hosting/5hay0t1t.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/g6u3kkut.png)

$Code$
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int N=2e5+5;
int n,q;
int f[N][21],lg[N],dep[N];
int l[N],r[N],cnt;
map<pii,int>mp;
vector<int>G[N];
void dfs(int u,int F){
	l[u]=++cnt;dep[u]=dep[f[u][0]=F]+1;
	for(int i=1;i<=lg[dep[u]];i++)f[u][i]=f[f[u][i-1]][i-1];
	for(auto v:G[u])if(v!=F)dfs(v,u);r[u]=cnt;
}
int val[N<<2],len[N<<2];
void update(int p,int l,int r){
	if(val[p])len[p]=r-l+1;
	else if(l==r)len[p]=0;
	else len[p]=len[p<<1]+len[p<<1|1];
}
void change(int p,int l,int r,int x,int y,int v){
	if(x>y)return;
	if(x<=l&&y>=r){val[p]+=v;update(p,l,r);return;}
	int mid=l+r>>1;
	if(x<=mid)change(p<<1,l,mid,x,y,v);
	if(y>mid)change(p<<1|1,mid+1,r,x,y,v);
	update(p,l,r);
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);G[v].push_back(u);
	}
	dfs(1,0);
	while(q--){
		int u,v,w;scanf("%d%d",&u,&v);
		if(l[u]>l[v])swap(u,v);
		if(!mp[pii(u,v)])mp[pii(u,v)]=1,w=1;
		else mp[pii(u,v)]=0,w=-1;
		if(r[u]>=r[v]){
			int s=v;
			for(int i=20;i>=0;i--)
				if(dep[f[s][i]]>dep[u])s=f[s][i];
			change(1,1,n,l[s],l[v]-1,w);
			change(1,1,n,r[v]+1,r[s],w);
		}else{
			change(1,1,n,1,l[u]-1,w);
			change(1,1,n,r[u]+1,l[v]-1,w);
			change(1,1,n,r[v]+1,n,w);
		}
		printf("%d\n",n-len[1]);
	}
	return 0;
}
```

---

## 作者：Y_ATM_K (赞：1)

[题面](https://www.luogu.com.cn/problem/CF1044F)

## 分析

先考虑只连一条边的情况。我们设连边的两个点为 $u,v$。手画几个图可以发现，对于一个生成树是 $T$ 的走法来说，它肯定是从 $u$ 或 $v$ 进入树上 $u \rightarrow v$ 的链的。

也就是说树上 $u \rightarrow v$ 这条链要从链的两个端点开始遍历而不能从链中间进入链。

这是因为若你走到了链中间，树上的链已经不能走了，所以当你再走到 $u$ 或 $v$ 时，你肯定会走那条非树边。

然后分类讨论：

- $u,v$ 在原树上没有祖先后代关系。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3k8llv76.png)

此时，只有 $u,v$ 的子树是好的。

- $u,v$ 在原树上有祖先后代关系。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/k8hkzu1u.png)

此时，我们设 $u$ 是 $v$ 的祖先，$w$ 为 $u$ 的子节点且 $v$ 在其子树中。那么只有 $w$ 的子树中 除 $v$ 的子树以外的节点是坏的，其他均为好节点。

接着考虑有多条边，显然对于每条边得到的坏节点的并集就是总体的坏节点。

我们可以维护每个点被标记了多少次坏节点，统计次数为 0 的节点数量就是答案。上面两种情况都可以用 dfs 序转化为区间，用线段树维护。找 $w$ 可以倍增。

0 的个数可能不太好维护。因为没有负数，所以转而维护最小值的个数，这反而更好做一点。

时间复杂度 $O((n+q)\log n)$

## 代码
```cpp
#include <bits/stdc++.h>
#define N 200005
#define M 400005
#define mp(x,y) make_pair(x,y)
using namespace std;
int n,Q,tot,first[N],nxt[M],ver[M];
void add(int s,int e) {
	nxt[++tot]=first[s];
	first[s]=tot;
	ver[tot]=e;
}
int dfn[N],size[N],tot_d,fa[N][19];
void dfs(int now,int f) {
	dfn[now]=++tot_d,size[now]=1,fa[now][0]=f;
	for(int i=first[now];i;i=nxt[i]) {
		if(ver[i]==f) continue;
		dfs(ver[i],now);
		size[now]+=size[ver[i]];
	}
}
int find(int u,int v) {
	for(int i=18;i>=0;--i) if(dfn[fa[u][i]]>dfn[v]) u=fa[u][i];
	return u;
}
map<pair<int,int>,bool> vis;
struct Segment_Tree {
	int dat,sum,mn;
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
} tr[N*5];
void update(int p) {
	int x=ls(p),y=rs(p),mn=tr[p].mn=min(tr[x].mn,tr[y].mn);
	tr[p].sum=(tr[x].mn==mn)*tr[x].sum+(tr[y].mn==mn)*tr[y].sum;
}
void spread(int p) {
	if(!tr[p].dat) return;
	int x=ls(p),y=rs(p);
	tr[x].dat+=tr[p].dat,tr[x].mn+=tr[p].dat;
	tr[y].dat+=tr[p].dat,tr[y].mn+=tr[p].dat;
	tr[p].dat=0;
}
void build(int p,int L,int R) {
	if(L==R) return void(tr[p].sum=1);
	int mid=(L+R)>>1;
	build(ls(p),L,mid),build(rs(p),mid+1,R);
	update(p);
}
void change(int p,int L,int R,int x,int y,int d) {
	if(x>y) return;
	if(L>=x&&R<=y) {
		tr[p].dat+=d,tr[p].mn+=d;
		return;
	}
	spread(p);
	int mid=(L+R)>>1;
	if(x<=mid) change(ls(p),L,mid,x,y,d);
	if(y>mid) change(rs(p),mid+1,R,x,y,d);
	update(p);
}
int main() {
	scanf("%d%d",&n,&Q);
	int s,e,f,t;
	for(int i=1;i<n;++i) {
		scanf("%d%d",&s,&e);
		add(s,e),add(e,s);
	}
	dfs(1,0);
	for(int j=1;j<19;++j) for(int i=1;i<=n;++i) {
		fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	build(1,1,n);
	while(Q--) {
		scanf("%d%d",&s,&e);
		if(dfn[s]>dfn[e]) swap(s,e);
		vis[mp(s,e)]^=1;
		f=vis[mp(s,e)]?1:-1;
		if(dfn[s]+size[s]>dfn[e]) {
			t=find(e,s);
			change(1,1,n,dfn[t],dfn[e]-1,f);
			change(1,1,n,dfn[e]+size[e],dfn[t]+size[t]-1,f);
		} else {
			change(1,1,n,1,dfn[s]-1,f);
			change(1,1,n,dfn[s]+size[s],dfn[e]-1,f);
			change(1,1,n,dfn[e]+size[e],n,f);
		}
		printf("%d\n",tr[1].mn?0:tr[1].sum);
	}
	return 0;
}
```

---

## 作者：Jorisy (赞：0)

首先 dfs 树的一个重要性质是所有非树边都是返祖边。

这意味着我们的好点都是在链外侧，并且要求一个区间并。

这不太好做，考虑补集，也就是变成求坏点个数。这些点是在链附近连续的，而且我们只要求一个区间交。

考虑按 dfn 序用线段树维护。

$\gdef\dfn#1{\text{dfn}_{#1}}\gdef\sz#1{\text{sz}_{#1}}$

下面令 $\dfn i,\sz i$ 分别表示节点 $i$ 的 dfn 序和子树大小，$S_i$ 表示 $i$ 的子树集合。

对于新加入或删除的两点 $u,v$，讨论一下关系：

- $u,v$ 是祖先后代关系。

钦定 $\dfn u<\dfn v$，令 $w$ 为距离 $u$ 最近的且在 $u\sim v$ 路径上的节点，那么需要被覆盖的点集就是 $S_w\setminus S_v$，对应的 dfn 区间为 $[\dfn w,\dfn v-1]\cup[\dfn v+\sz v,\dfn w+\sz w-1]$。

- $u,v$ 不是祖先后代关系。

类似地，需要被覆盖的点集为 $S_1\setminus S_u\setminus S_v$，对应 dfn 区间为 $[1,\dfn u-1]\cup[\dfn u+\sz u,\dfn v-1]\cup[\dfn v+\sz v,n]$。

于是就做完了。时间复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
#define N 200005
#define K 25
using namespace std;

vector<int>g[N];
map<pair<int,int>,bool>mp;
int n,q,dfn[N],sz[N],fa[N][K],dep[N];

void dfs(int x,int lst=0)
{
    fa[x][0]=lst;
    dep[x]=dep[lst]+1;
    for(int i=1;i<=20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
    dfn[x]=++dfn[0];
    sz[x]=1;
    for(auto i:g[x])
    {
        if(i==lst) continue;
        dfs(i,x);
        sz[x]+=sz[i];
    }
}

int lcasn(int u,int v)
{
    // if(dep[u]<dep[v]) swap(u,v);
    for(int i=20;~i;i--)
    {
        if(dep[fa[u][i]]>dep[v]) u=fa[u][i];
    }
    return u;
}

struct segt{
    #define mid (l+r>>1)
    #define lc (i<<1)
    #define rc (i<<1|1)
    struct node{
        int len,tag,res;
    }sgt[N<<4];

    void upd(node &x,node y,node z)
    {
        x.res=x.tag?x.len:y.res+z.res;
    }

    void build(int i,int l,int r)
    {
        sgt[i].len=r-l+1;
        if(l>=r) return;
        build(lc,l,mid);
        build(rc,mid+1,r);
    }

    void mdf(int i,int l,int r,int x,int y,int d)
    {
        if(l>r) return;
        if(x<=l&&r<=y)
        {
            sgt[i].tag+=d;
            upd(sgt[i],sgt[lc],sgt[rc]);
            return;
        }
        if(x<=mid) mdf(lc,l,mid,x,y,d);
        if(y>mid) mdf(rc,mid+1,r,x,y,d);
        upd(sgt[i],sgt[lc],sgt[rc]);
    }
    #undef mid
    #undef lc
    #undef rc
}sgt;

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    sgt.build(1,1,n);
    dfs(1);
    while(q--)
    {
        int u,v;
        cin>>u>>v;
        if(dfn[u]>dfn[v]) swap(u,v);
        if(dfn[u]<dfn[v]&&dfn[v]<=dfn[u]+sz[u]-1)
        {
            int w=lcasn(v,u),d;
            mp[{u,v}]=d=!mp[{u,v}];
            d-=!d;
            sgt.mdf(1,1,n,dfn[w],dfn[v]-1,d);
            sgt.mdf(1,1,n,dfn[v]+sz[v],dfn[w]+sz[w]-1,d);
        }
        else
        {
            int d;
            mp[{u,v}]=d=!mp[{u,v}];
            d-=!d;
            sgt.mdf(1,1,n,1,dfn[u]-1,d);
            sgt.mdf(1,1,n,dfn[u]+sz[u],dfn[v]-1,d);
            sgt.mdf(1,1,n,dfn[v]+sz[v],n,d);
        }
        cout<<n-sgt.sgt[1].res<<'\n';
    }
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

首先经过一点简单的观察可以发现，如果在 $x,y$ 之间加边，那么只有以 $x$ 为根，$y$ 子树内和以 $y$ 为根，$x$ 子树内的点有可能给出贡献。

证明：考虑一个不符合这个要求的点，他与 $x,y$ 之间的最短路径上最近的点为 $p$，考虑 $p$ 先 dfs 靠 $x$ 近还是靠 $y$ 近的点，不难发现对于任何一种情况，都会进过 $x,y$ 一条边。

考虑使用线段树维护，每次加边对不符合要求的点全部 $-1$（可以跑出树的 dfn 序维护），每次查询的时候查询全局的最大值与最大值个数，如果最大值为 $0$ 则输出最大值个数，否则答案即为 $0$。删边同理。

总复杂度 $O(n+q\log n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
vector<int> vc[1000005];
int f[1000005][21],ind[1000005],outd[1000005],cnt,dep[1000005];
void dfs(int now,int fa){
	f[now][0]=fa,dep[now]=dep[fa]+1,ind[now]=++cnt;
	for(int i=1;i<=20;i++) f[now][i]=f[f[now][i-1]][i-1];
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
	}
	outd[now]=cnt;
}
int lca(int u,int v){
	if(dep[u]>dep[v]) swap(u,v);
	for(int i=20;i>=0;i--) if(dep[f[v][i]]>=dep[u]) v=f[v][i];
	if(u==v) return u;
	for(int i=20;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
int up(int u,int len){
	for(int i=20;i>=0;i--){
		if(len>=(1<<i)){
			u=f[u][i];
			len-=(1<<i);
		}
	}
	return u;
}
struct sgt{
	int lzt[2000005],maxv[2000005],maxcnt[2000005];
	void pushdown(int i){
		lzt[i*2]+=lzt[i];
		lzt[i*2+1]+=lzt[i];
		maxv[i*2]+=lzt[i];
		maxv[i*2+1]+=lzt[i];
		lzt[i]=0;
	}
	void pushup(int i){
		maxv[i]=max(maxv[i*2],maxv[i*2+1]);
		maxcnt[i]=0;
		if(maxv[i*2]==maxv[i]) maxcnt[i]+=maxcnt[i*2];
		if(maxv[i*2+1]==maxv[i]) maxcnt[i]+=maxcnt[i*2+1];
	}
	pair<int,int> merge(pair<int,int> x,pair<int,int> y){
		pair<int,int> z;
		z.first=max(x.first,y.first);
		z.second=0;
		if(x.first==z.first) z.second+=x.second;
		if(y.first==z.first) z.second+=y.second;
		return z;
	}
	void build(int i,int l,int r){
		if(l==r){
			maxv[i]=0,maxcnt[i]=1;
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		pushup(i);
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql>qr) return ;
		if(ql<=l&&r<=qr){
			lzt[i]+=cg,maxv[i]+=cg;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		pushup(i);
	}
	pair<int,int> qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return make_pair(maxv[i],maxcnt[i]);
		pushdown(i);
		if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		return merge(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree;
int tot=0;
map<pair<int,int>,int> mp;
signed main(){
	int n,q; cin>>n>>q;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs(1,0);
	tree.build(1,1,n);
	for(int i=1;i<=q;i++){
		int op=1;
		int x,y; cin>>x>>y;
		if(x>y) swap(x,y);
		if(mp[make_pair(x,y)]) op=-1;
		tot+=op;
		mp[make_pair(x,y)]^=1;
		if(dep[x]>dep[y]) swap(x,y);
		int t=lca(x,y);
		if(t==x){
			tree.change(1,1,n,ind[y],outd[y],op);
			int p=up(y,dep[y]-dep[x]-1);
			tree.change(1,1,n,1,ind[p]-1,op);
			tree.change(1,1,n,outd[p]+1,n,op);
		}
		else{
			tree.change(1,1,n,ind[x],outd[x],op);
			tree.change(1,1,n,ind[y],outd[y],op);
		}
		auto v=tree.qry(1,1,n,1,n);
		if(v.first==tot) cout<<v.second;
		else cout<<0;
		cout<<"\n";
	}
	return 0;
}
```

---

