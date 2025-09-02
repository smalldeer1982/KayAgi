# [ABC301Ex] Difference of Distance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc301/tasks/abc301_h

頂点には $ 1 $ から $ N $ の番号が、辺には $ 1 $ から $ M $ の番号がついた $ N $ 頂点 $ M $ 辺の連結無向グラフがあります。 辺 $ i $ は頂点 $ U_i $ と頂点 $ V_i $ を結んでおり、重みとして整数 $ W_i $ が定められています。 ここで、$ 1\leq\ s,t\ \leq\ N,\ s\neq\ t $ に対して $ d(s,t) $ を以下で定義します。

- 頂点 $ s $ と頂点 $ t $ を結ぶすべてのパスに対する「パス上の辺の重みの最大値」の最小値
 
今から与えられる $ Q $ 個のクエリにそれぞれ答えてください。$ j $ 番目のクエリは以下の通りです。

- $ A_j,S_j,T_j $ が与えられる。辺 $ A_j $ の重みを $ 1 $ 増やすと $ d(S_j,T_j) $ がいくつ変化するか求めよ。
 
なお、各クエリにおいて実際には辺の重みは変更しないことに注意してください。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 2\times\ 10^5 $
- $ N-1\leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ U_i,V_i\ \leq\ N $
- $ U_i\ \neq\ V_i $
- $ 1\ \leq\ W_i\ \leq\ M $
- 与えられるグラフは連結
- $ 1\leq\ Q\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_j\ \leq\ M $
- $ 1\ \leq\ S_j,T_j\ \leq\ N $
- $ S_j\neq\ T_j $
- 入力は全て整数
 
### Sample Explanation 1

![image of the given graph](https://img.atcoder.jp/abc301/00609898872063e16f2e7b43c6436c6d.png) 上の図においては、辺の番号を黒字で、辺の重みを青字で表記しています。 $ 1 $ 番目から $ 6 $ 番目のクエリについて説明します。 まず与えられたグラフにおける $ d(4,6) $ について考えます。 $ 4\ \rightarrow\ 1\ \rightarrow\ 2\ \rightarrow\ 6 $ というパス上の辺の重みの最大値は $ 5 $ ですが、 これは頂点 $ 4 $ と頂点 $ 6 $ を結ぶパスの中での最小値であるため、$ d(4,6)=5 $ です。 次に、辺 $ x\ (1\ \leq\ x\ \leq\ 6) $ の重みを $ 1 $ 増やすと $ d(4,6) $ がいくつ変化するか考えます。 $ x=6 $ のとき $ d(4,6)=6 $ となるため変化量は $ 1 $ ですが、$ x\ \neq\ 6 $ のときは $ d(4,6)=5 $ となるため変化量は $ 0 $ です。 たとえば $ x=3 $ のとき、$ 4\ \rightarrow\ 1\ \rightarrow\ 2\ \rightarrow\ 6 $ というパス上の辺の重みの最大値は $ 6 $ になりますが、 $ 4\ \rightarrow\ 3\ \rightarrow\ 1\ \rightarrow\ 2\ \rightarrow\ 6 $ というパス上の辺の重みの最大値が $ 5 $ であるため $ d(4,6) $ は変わらず $ 5 $ のままです。

### Sample Explanation 2

与えられるグラフは多重辺を含むこともあります。

## 样例 #1

### 输入

```
6 6
1 2 1
3 1 5
4 1 5
3 4 3
5 6 4
2 6 5
7
1 4 6
2 4 6
3 4 6
4 4 6
5 4 6
6 4 6
5 6 5```

### 输出

```
0
0
0
0
0
1
1```

## 样例 #2

### 输入

```
2 2
1 2 1
1 2 1
1
1 1 2```

### 输出

```
0```

# 题解

## 作者：EuphoricStar (赞：5)

基础图论。

考虑快速求出 $d(s, t)$，那么边权要 $+1$ 的边仅当边权等于 $d(s, t)$ 时答案可能为 $1$。求 $d(s, t)$ 可以建出 Kruskal 重构树，查两点 $\text{LCA}$ 点权得出。

考虑把询问离线，把相同的 $d(s, t)$ 的询问和相同边权的边放在一起考虑。边权 $< d(s, t)$ 的边在之前合并。现在问题变成了有一个图，询问假设删掉其中一条边，会不会使得两点不连通。边双缩点后，如果这条边在一个边双内，或者两点在同一边双内，答案显然为 $0$，否则查这条边是否在两点路径上即可。

时间复杂度 $O(m \log m)$。

[code](https://atcoder.jp/contests/abc301/submissions/41438878)

---

## 作者：541forever (赞：4)

因为本题要求的是最小瓶颈路，可以考虑建出原图的最小生成树，那么最小瓶颈一定为 MST 上两点路径边权的最大值。

考虑修改一条边会有什么影响，可以发现，除非你修改的这条边恰为 s 到 t 的瓶颈，你的修改是一定没有贡献的。若它为瓶颈边，设其权值为 $w$，则若加入所有权值 $\le w$ 的非树边进去后 $(s,t)$ 能联通，答案仍不变。

具体维护时，我们可以将所有边按 $w$ 排序，每次将非树边的 $(u,v)$ 在树上的路径上的所有点合并进一个并查集中，这样，每次断开树边 $(x,y)$ 时（设 $x$ 为深度较大的那个点），我们只需查询 $x$ 是否与它的祖先中任意一个在同一个并查集内即可。

[Code](https://atcoder.jp/contests/abc301/submissions/41639401)

---

## 作者：云浅知处 (赞：4)

简单题！

我们直接来解决任意修改边权的问题。先建一个最小生成树出来。

考虑修改一条边 $(u,v)$ 后最小生成树会发生什么变化：

- 若 $(u,v)$ 不在最小生成树上，自然地，最小生成树不会发生变化。
- 否则，考虑这棵树上 $(u,v)$ 这条边断开后形成的两个连通块，此时应当选择两边分别在两连通块内的最小边。

对于第二种边，容易想到转 DFS 序求矩形最小值，可以简单做到 $O(N\log^2N)$；不过实际上我们可以对每条非树边 $(x,y,z)$，在 $x,y$ 的线段树上分别在 $\text{DFN}(y),\text{DFN}(x)$ 处插入 $z$。最后做一遍线段树合并即可对每个点求出「一端点在这个子树内，一端点在子树外」的所有非树边的边权最小值。这样时间复杂度为 $O(N\log N)$。

还需要写一个数据结构维护树上两点边权最小值。这些都可以在 $O(N\log N)$ 时间内完成，于是就得到了时间复杂度为 $O(N\log N)$ 的在线算法。

```cpp
#include<bits/stdc++.h>

#define ll long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=1e9+7;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int N=2e5+5;

#define fi first
#define se second
#define mk make_pair

int st[N],ed[N],n,m,q,ww[N];

struct S{
	int u,v,w;
	S(int U,int V,int W):u(U),v(V),w(W){}
	S(){}
};
S op(S x,S y){
	if(x.w<y.w)return x;
	else return y;
}
const int INF=1e9;
S e(){return S(0ll,0ll,INF);}
struct Node{int ls,rs;S val;};
int root[N];
struct SegTree{
	Node d[N<<5];int tot;
	#define ls(p) (d[p].ls)
	#define rs(p) (d[p].rs)
	void clear(){tot=0;for(int i=0;i<(N<<5);i++)d[i].ls=d[i].rs=0,d[i].val=e();}
	void pushup(int p){d[p].val=op(d[ls(p)].val,d[rs(p)].val);}
	void ins(int x,S k,int ql,int qr,int &p){
		if(!p)p=++tot;
		if(ql==qr){d[p].val=op(d[p].val,k);return ;}
		int mid=(ql+qr)>>1;
		if(x<=mid)ins(x,k,ql,mid,ls(p));
		if(x>mid)ins(x,k,mid+1,qr,rs(p));
		pushup(p);
	}
	S qmin(int l,int r,int ql,int qr,int p){
		if((!p)||l>r)return e();
		if(l<=ql&&qr<=r)return d[p].val;
		int mid=(ql+qr)>>1;S ans=e();
		if(l<=mid)ans=op(ans,qmin(l,r,ql,mid,ls(p)));
		if(r>mid)ans=op(ans,qmin(l,r,mid+1,qr,rs(p)));
		return ans;
	}
	int merge(int p,int q,int l,int r){
		if(!p||!q)return p+q;
		if(l==r){d[p].val=op(d[p].val,d[q].val);return p;}
		int mid=(l+r)>>1;
		d[p].ls=merge(ls(p),ls(q),l,mid),d[p].rs=merge(rs(p),rs(q),mid+1,r);
		pushup(p);return p;
	}
}T;

struct Edge{
	int to,cost;
	Edge(int T,int C):to(T),cost(C){}
	Edge(){}
};
vector<Edge>G[N];
void adde(int u,int v,int w){
	G[u].emplace_back(Edge(v,w));
	G[v].emplace_back(Edge(u,w));
}

struct zkw{
	int d[N<<2],M,k;
	void build(int n){
		k=0,M=1;while(M<n)M<<=1,k++;
		for(int i=1;i<=M+M-1;i++)d[i]=0;
	}
	void upd(int p){d[p]=max(d[p<<1],d[p<<1|1]);}
	void Set(int p,int x){
		d[p+=M-1]=x;
		for(int i=1;i<=k;i++)upd(p>>i);
	}
	int qmax(int l,int r){
		int res=0;
		for(l+=M-1,r+=M;l<r;l>>=1,r>>=1){
			if(l&1)res=max(res,d[l++]);
			if(r&1)res=max(res,d[--r]);
		}
		return res;
	}
}Y;

namespace HLD{
	int dep[N],fa[N],sz[N],dfn[N],top[N],hson[N],dis[N],fval[N];
	
	void dfs1(int u,int de){
		dep[u]=de,sz[u]=1;
		for(auto e:G[u]){
			int v=e.to,w=e.cost;
			if(v==fa[u])continue;
			fval[v]=w,fa[v]=u,dfs1(v,de+1),sz[u]+=sz[v];
			if(sz[v]>sz[hson[u]])hson[u]=v;
		}
	}
	
	int tot=0;
	void dfs2(int u,int tp){
		top[u]=tp,dfn[u]=++tot;
		if(u==hson[fa[u]])dis[u]=max(dis[fa[u]],fval[u]);
		else dis[u]=fval[u];
		if(hson[u])dfs2(hson[u],tp);
		for(auto e:G[u]){
			int v=e.to;
			if(v==fa[u]||v==hson[u])continue;
			dfs2(v,v);
		}
	}
	
	void DS_build(){
		Y.build(n);
		for(int i=2;i<=n;i++)Y.Set(dfn[i],fval[i]);
	}
	
	int dist(int u,int v){
		int res=0;
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]])swap(u,v);
			res=max(res,dis[u]),u=fa[top[u]];
		}
		if(dep[u]>dep[v])swap(u,v);
		res=max(res,Y.qmax(dfn[u]+1,dfn[v]));
		return res;
	}
};

using HLD::dist;
using HLD::dfn;
using HLD::sz;
S val[N];

void dfs(int u,int fa){
	for(auto e:G[u]){
		int v=e.to,w=e.cost;
		if(v==fa)continue;
		dfs(v,u),root[u]=T.merge(root[u],root[v],1,n);
	}
	val[u]=op(T.qmin(1,dfn[u]-1,1,n,root[u]),T.qmin(dfn[u]+sz[u],n,1,n,root[u]));
}

int fa[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

struct Ed{int u,v,w,id;}E[N];
bool intree[N];

bool is_anc(int x,int y){
	return dfn[y]<=dfn[x]+sz[x]-1&&dfn[y]>=dfn[x];
}

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif

	n=read(),m=read();
	for(int i=1;i<=m;i++)st[i]=E[i].u=read(),ed[i]=E[i].v=read(),ww[i]=E[i].w=read(),E[i].id=i;
	sort(E+1,E+m+1,[](const Ed &x,const Ed &y){return x.w<y.w;});
	for(int i=1;i<=n;i++)fa[i]=i;
	T.clear();
	for(int i=1;i<=m;i++){
		int u=find(E[i].u),v=find(E[i].v),w=E[i].w;
		if(u!=v)fa[u]=v,adde(E[i].u,E[i].v,w),intree[E[i].id]=1;
	}
	HLD::dfs1(1,1),HLD::dfs2(1,1),HLD::DS_build();
	for(int i=1;i<=m;i++)if(!intree[i]){
		T.ins(dfn[ed[i]],S(st[i],ed[i],ww[i]),1,n,root[st[i]]);
		T.ins(dfn[st[i]],S(st[i],ed[i],ww[i]),1,n,root[ed[i]]);
	}
	dfs(1,0);
	q=read();
	while(q--){
		int id=read(),u=read(),v=read();
		if(!intree[id]){cout<<0<<'\n';continue;}
		if(dfn[st[id]]>dfn[ed[id]])swap(st[id],ed[id]);
		assert(HLD::fa[ed[id]]==st[id]);int p=ed[id];
		if(is_anc(p,v)==is_anc(p,u)){cout<<0<<'\n';continue;}
		if(!is_anc(p,u))swap(u,v);assert(is_anc(p,u));
		S edge=op(val[p],S(ed[id],st[id],ww[id]+1));
		if(!is_anc(p,edge.u))swap(edge.u,edge.v);assert(is_anc(p,edge.u));
		cout<<max(edge.w,max(dist(edge.u,u),dist(edge.v,v)))-dist(u,v)<<'\n';
	}

	return 0;
}
```

---

## 作者：Miraik (赞：4)

考虑按边权分层，从小往大加边。

考虑每一层在上一层的基础上缩边双。对于涉及到当前层边的询问，其答案为 $1$，当且仅当：

- 在这层的边加入之前，$S$ 与 $T$ 不连通。

- 边 $A$ 为当前层的图的割边（如果不是，那么 $S$ 可以从其他路径走到 $T$，最大边权不变）

- 进一步的，$A$ 处于边双森林中 $S$ 与 $T$ 的路径上。

而树上边 $(u,v)$ 在 $s \to t$ 的路径上等价于 $dis(u,s)+dis(u,t)=dis(s,t)$ 且 $dis(v,s)+dis(v,t)=dis(s,t)$。

在具体实现时，我使用了 set 判断割边，并查集维护联通性，再在边双树上树剖，复杂度为 $O(n \log n)$。实现代码时细节较多。

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define mp make_pair
using namespace std;
const int N=200005;
int n,m,Q,idx,ru[N],rv[N],col[N],dfn[N],low[N],fa[N],fu[N],fv[N],ans[N];
int tr[N],siz[N],dep[N],top[N],tfa[N],son[N];
set<pii>cut; vector<int>b; vector<pii>e[N];
inline int find(int x){ return fa[x]==x?fa[x]:fa[x]=find(fa[x]); }
struct O{ int u,v,w,id; }; vector<O>o[N],q[N];
inline void tarjan(int u,int fa){
    dfn[u]=low[u]=++idx;
    for(int i=0;i<e[u].size();i++){
        int v=e[u][i].first,w=e[u][i].second;
        if(!dfn[v]){
            tarjan(v,w);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]) cut.insert(mp(u,v)),cut.insert(mp(v,u));
        }
        else if(w!=fa) low[u]=min(low[u],dfn[v]);
    }
}
inline void dfs(int u){
    col[u]=1;
    for(int i=0;i<e[u].size();i++){
        int v=e[u][i].first;
        if(col[v]||cut.count(mp(u,v))) continue;
        fa[find(v)]=find(u); dfs(v);
    }
}
inline void dfs1(int u){
	siz[u]=1;
	for(int i=0;i<e[u].size();i++){
        int v=e[u][i].first;
		if(v==tfa[u]) continue;
		tfa[v]=u; dep[v]=dep[u]+1; tr[v]=tr[u];
		dfs1(v); siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
inline void dfs2(int u,int tp){
	top[u]=tp;
	if(!son[u]) return;
	dfs2(son[u],tp);
	for(int i=0;i<e[u].size();i++){
        int v=e[u][i].first;
		if(v==tfa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
inline int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=tfa[top[u]];
	}	return dep[u]<dep[v]?u:v;
}
inline int dist(int x,int y){
	if(!tr[x]||!tr[y]||tr[x]!=tr[y]) return inf;
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>m;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w; ru[i]=u; rv[i]=v;
        o[w].emplace_back(O{u,v,w,i});
    }
    cin>>Q;
    for(int i=1,x,s,t;i<=Q;i++){
        cin>>x>>s>>t;
        q[x].emplace_back(O{s,t,0,i});
    }
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++){
        for(int j=0;j<o[i].size();j++){
            int u=find(o[i][j].u),v=find(o[i][j].v);
            if(e[u].empty()) b.emplace_back(u);
            if(e[v].empty()) b.emplace_back(v);
            e[u].emplace_back(mp(v,j)); e[v].emplace_back(mp(u,j));
            fu[j]=u; fv[j]=v;
        }
        for(int j=0;j<b.size();j++) if(!dfn[b[j]]) tarjan(b[j],-1);
        for(int j=0;j<b.size();j++) if(!col[b[j]]) dfs(b[j]);
        for(int j=0;j<b.size();j++) e[b[j]].clear();
        for(int j=0;j<o[i].size();j++){
            int y=o[i][j].id;
            if(!cut.count(mp(fu[j],fv[j]))) continue;
            int u=find(ru[y]),v=find(rv[y]);
            e[u].emplace_back(mp(v,0));
            e[v].emplace_back(mp(u,0));
        }
		for(int j=0;j<b.size();j++) if(find(b[j])==b[j]&&!tr[b[j]]){
			tr[b[j]]=++idx;
			dfs1(b[j]); dfs2(b[j],b[j]);
		}
		for(int j=0;j<o[i].size();j++){
            int y=o[i][j].id;
            if(!cut.count(mp(fu[j],fv[j]))) continue;
            int xu=find(ru[y]),xv=find(rv[y]);
            for(int k=0;k<q[y].size();k++){
                int u=find(q[y][k].u),v=find(q[y][k].v);
                if(u!=v&&dist(xu,u)+dist(xu,v)==dist(u,v)&&dist(xv,u)+dist(xv,v)==dist(u,v))
					ans[q[y][k].id]=1;
            }
        }
        for(int j=0;j<o[i].size();j++) fa[find(o[i][j].u)]=find(o[i][j].v);
        for(int j=0;j<b.size();j++)
			low[b[j]]=dfn[b[j]]=col[b[j]]=dep[b[j]]=tr[b[j]]=tfa[b[j]]=son[b[j]]=top[b[j]]=siz[b[j]]=0,e[b[j]].clear();
		cut.clear(); b.clear();
    }
    for(int i=1;i<=Q;i++) cout<<ans[i]<<'\n';
    return 0;
}
```


---

## 作者：orz_z (赞：3)

建立原图的最小生成树，那么两点路径最大值的最小值即为 `MST` 上两点路径最大边权。

设修改边 $(x,y)$，原权值为 $w$。

首先查询 $s$ 到 $t$ 的最小瓶颈是否是 $w$，如果不是，显然没有影响。

否则问题转化为：仅考虑边权 $\leq w$ 的边，$(x,y)$ 是否为 $s,t$ 之间的割边。

将询问离线下来，扫描线按边权排序，将边权 $\leq w$ 的非树边 $(u,v)$ 加入，将 $u$ 到 $v$ 的点合并，并查集维护。

最后查询 $s,t$ 点是否在同一个并查集且 $(x,y)$ 是否在 $s,t$ 在 `MST` 的路径上即可，因为加的是非树边，所以若 $s,t$ 不连通则无法从 $s$ 通过非树边到达 $t$，故此时 $(x,y)$ 为割边。

时间复杂度 $\mathcal O(n \log n)$。

---

## 作者：xkcdjerry (赞：2)

题解区貌似主要是 Tarjan 求割边，还有一些二维数点的。  
这里给个非常容易想，比较容易写（笔者除了文末提到的一个特判之外一遍过），而且可以拓展到一次增加多条边的权值的做法：

令 $d(u,v)$ 为原图中 $u,v$ 之间的最短瓶颈路，那么边 $e$ 能够影响其的**必要不充分**条件如下：（注意这个可以被应用给边权加任意值 $k$，只要把第二个条件中的 $+1$ 改为 $+k$ 即可，原因显然）    
* $w_e \leqslant d(u,v)$，否则最初的路线中不存在这条边，无论怎么改都不会使答案变大
* $w_e+1>d(u,v)$，否则即使走这条边也不会影响最终答案
  
不满足必要条件的边显然可以直接丢弃，对于本题来说直接输出 $0$ 即可。

$d(u,v)$ 可以通过建一棵最小生成树然后倍增 $O(n \log n) - O(\log n)$ 求出。  
或者想卡常的话也可以建一棵 Kruskal 重构树然后用树剖，ST表等算法求 LCA 解决。这里不是复杂度瓶颈就采用了倍增方法。


----

这里全部假定有 $w_e \leqslant d(u,v) < w_e+k$：

考虑 $d(u,v)$ 不变的情况下可能走哪些边：所有满足 $w_i \leqslant d(u,v), i \neq e$ 的边。

换句话说如果 $u,v$ 可以通过上面所述的这些边联通，那么证明了删去 $e$ 之后仍然存在一条至多为 $d(u,v)$ 的瓶颈路，即答案为 $0$。  
反之，若 $u,v$ 不能通过所述边联通，说明至少要经过一条边权超过 $d(u,v)$ 的边，即瓶颈路 $>d(u,v)$，答案为 $1$。

至此，我们把问题转化为了一个动态加删边求连通性的问题。可以直接套可撤销并查集+线段树分治维护了……吗？

考虑最劣的情况下，可能询问的 $d(u,v)$ 在最大值和最小值之间反复横跳，那么每次都需要插入/删除 $O(m)$ 条边，复杂度高达 $O(mq \log n)$。  
解决方式也很简单：既然线段树分治已经需要连通性的询问离线了，那么刚好把原题的询问也离线下来按 $d(u,v)$ 排序。  
那么，不考虑 $i \neq e$ 造成的删边的话，每个边最多会被插入 $1$ 次。而每个被询问的边至多会造成一次删除和一次插入。故总段数为 $O(m+q)$。

最终复杂度：  
空间 $O(q \log q)$，瓶颈在于线段树分治。  
时间 $O((m+q) \log q \log n)$，线段树和可撤销并查集各贡献一只 $\log$。

**“但是，谁问你了？”**：  
注意可能会出现不存在任何满足必要条件的询问，如果直接建树会 RE/MLE/TLE，需要特判掉这种情况跳过线段树分治过程。

代码：（给出了一些注释解释各部分的功能和拓展到多条边的方式）

```c++
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
#define N 200010
using std::map;
using std::sort;
using std::vector;

int n,m,q;
// 两个 operator< 用于询问离线时的 sort
struct edge
{
    int u,v,w,i;
    bool operator<(edge b) const {return w<b.w;}
}orig[N],a[N];
struct query
{
    int u,v,a,w,i;
    bool operator<(query b) const {return w<b.w;}
}ask[N]; int ans[N];

// Kruskal求最小生成树+倍增求瓶颈路
namespace Neck
{
    struct edge{int v,w;};
    int fa[N]; vector<edge> e[N];
    int f[21][N],g[21][N],dep[N];
    int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
    bool merge(int x,int y)
    {
        x=find(x), y=find(y);
        if(x==y) return false;
        fa[x]=y; return true;
    }
    inline int max(int x,int y){return x>y?x:y;}
    void dfs(int x,int F)
    {
        f[0][x]=F,dep[x]=dep[F]+1;
        for(auto i:e[x]) if(i.v!=F)
            g[0][i.v]=i.w, dfs(i.v,x);
    }
    void init()
    {
        for(int i=1;i<=n;i++) fa[i]=i;
        for(int i=0;i<m;i++) if(merge(a[i].u,a[i].v))
            e[a[i].u].push_back({a[i].v,a[i].w}),
            e[a[i].v].push_back({a[i].u,a[i].w});
        dfs(1,0);
        for(int i=1;i<=20;i++) for(int j=1;j<=n;j++)
            f[i][j]=f[i-1][f[i-1][j]],
            g[i][j]=max(g[i-1][j],g[i-1][f[i-1][j]]);
    }
    int query(int u,int v)
    {
        if(dep[u]<dep[v]) {int t=u; u=v; v=t;}
        int ans=0;
        for(int i=20;i>=0;i--) if(dep[f[i][u]]>=dep[v])
            ans=max(ans,g[i][u]), u=f[i][u];
        if(u==v) return ans;
        for(int i=20;i>=0;i--) if(f[i][u]!=f[i][v])
            ans=max(ans,max(g[i][u],g[i][v])), u=f[i][u], v=f[i][v];
        return max(ans,max(g[0][u],g[0][v]));
    }
}

// 可撤销并查集板子
int fa[N],rank[N],stk[N],top;
int find(int x) {return fa[x]==x?x:find(fa[x]);}
void merge(int x,int y)
{
    x=find(x), y=find(y);
    if(x==y) {stk[top++]=-1; return;}
    if(rank[x]<rank[y]) fa[x]=y, stk[top++]=x;
    else if(rank[x]>rank[y]) fa[y]=x, stk[top++]=y;
    else fa[x]=y, rank[x]++, rank[y]++, stk[top++]=x;
}
void undo()
{
    int x=stk[--top]; if(x==-1) return;
    int y=fa[x]; fa[x]=x;
    if(rank[x]==rank[y]) rank[x]--, rank[y]--;
}

// 线段树分治判动态连通性板子
struct duo{int u,v;};
struct seg
{
    int l,r;
    vector<duo> v;
}T[N*4];
void init(int l,int r,int o)
{
    T[o].l=l, T[o].r=r;
    if(l!=r)
    {
        int mid=(l+r)/2;
        init(l,mid,o<<1), init(mid+1,r,o<<1|1);
    }
}
void ins(int l,int r,duo e,int o)
{
    if(T[o].l==l&&T[o].r==r) {T[o].v.push_back(e); return;}
    int mid=(T[o].l+T[o].r)/2;
    if(r<=mid) ins(l,r,e,o<<1);
    else if(l>mid) ins(l,r,e,o<<1|1);
    else ins(l,mid,e,o<<1),ins(mid+1,r,e,o<<1|1);
}
void dfs(int o)
{
    for(auto i:T[o].v) merge(i.u,i.v);
    if(T[o].l==T[o].r)
    {
        query x=ask[T[o].l];
        ans[x.i]=(find(x.u)!=find(x.v));
    }
    else dfs(o<<1), dfs(o<<1|1);
    for(auto i:T[o].v) undo();
}

// 线段树分治的接口
std::map<int,int> M;
void ins_edge(int i,int t) {M[i]=t;}
void del_edge(int i,int t)
{
    if(M[i]<t) ins(M[i],t-1,duo{orig[i].u,orig[i].v},1);
    M.erase(i);
}
void flush_edge(int t)
{
    for(auto i:M) if(i.second<t)
        ins(i.second,t-1,duo{orig[i.first].u,orig[i.first].v},1);
    M.clear();
}


int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0,u,v,w;i<m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        orig[i]=a[i]={u,v,w,i};
    }
    std::sort(a,a+m);
    Neck::init();

    scanf("%d",&q); int cnt=0;
    for(int i=0,u,v,e;i<q;i++)
    {
		// 题里的边是从 1 开始编号的
        scanf("%d%d%d",&e,&u,&v), e--;
        int neck=Neck::query(u,v);
        if(orig[e].w==neck)
			// 与最初提交不同，用瓶颈路排序便于兼容
			// 修改多条边的情况
            ask[cnt++]={u,v,e,neck,i};
    }
	// 特判“谁问你了”
    if(!cnt)
    {
        for(int i=0;i<q;i++) printf("0 ");
        return 0;
    }
    std::sort(ask,ask+cnt);
    int p=0; init(0,cnt-1,1);
    for(int i=0;i<cnt;i++)
    {
        while(p<m&&a[p].w<=ask[i].w) ins_edge(a[p].i,i),p++;
		// 这段改为遍历所有符合必要条件的边并擦除其在 i 时刻的存在
		// 就可以拓展到一次增加多条边的情况
        del_edge(ask[i].a,i), ins_edge(ask[i].a,i+1);
    }
    flush_edge(cnt);
    for(int i=1;i<=n;i++) fa[i]=i;
    dfs(1);
    for(int i=0;i<q;i++) printf("%d\n",ans[i]);
}
```

[提交记录](https://atcoder.jp/contests/abc301/submissions/50289868)



---

## 作者：WrongAnswer_90 (赞：2)

[AT_abc301_h [ABC301Ex] Difference of Distance](https://www.luogu.com.cn/problem/AT_abc301_h)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17766886.html)

一道基础图论，很好口胡，但是实现不太简单。

考虑离线，把询问挂在边上，按边权从小到大处理。

处理到一个边权时，把边权小于它的边的两端用并查集合并，对于等于这个边权的边在并查集上建图，跑一边 tarjan，因为问的是边，所以把边双锁点。

对于当前的边权，一个询问的答案是 $1$ 当且仅当它的两个点属于不同的边双并且两个边双的树上路径上有这条边，可以转化一下，设 $x,y$ 为两个边双的编号，$(l,r)$ 为询问的这条边，上面的限制等价于 $dis(x,l)+dis(y,r)+1=dis(x,y)$ 或 $dis(x,r)+dis(y,l)+1=dis(x,y)$，树剖或者倍增都可以。

实现的时候要小心一些，否则复杂度就假了。我们只能对属于当前边权的边的两个端点进行 tarjan，需要开数组记录，这样对于每一条边会遍历它两端的端点，复杂度是线性的。建树和建图的时候只把需要的节点的数据清空。复杂度为 $\mathcal O(n\log n)$。

```cpp
int n,m,q,len=0,num,color,cnt,tot,top[200001],dep[200001],fa[200001][21],col[200001],head[200001],to[400001],nex[400001],vis[200001],dfn[200001],low[200001],b[200001],ans[200001];
inline void add(int x,int y){to[++cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
namespace DSU
{
	int fat[200001];
	int find(int x){return x==fat[x]?x:fat[x]=find(fat[x]);}
}
using namespace DSU;
struct Node{int x,y,z;};
struct Edge{int x,y,z;vector<Node> q;}a[200001];
bool cmp(Edge e1,Edge e2){return e1.z<e2.z;}
stack<int> st;
vector<int> T[200001];
void tarjan(int k,int from)
{
	dfn[k]=low[k]=++num,st.e(k);
	for(int i=head[k];i;i=nex[i])
	{
		if(i==(from^1))continue;
		if(!dfn[to[i]])tarjan(to[i],i),low[k]=min(low[k],low[to[i]]);
		else low[k]=min(low[k],dfn[to[i]]);
	}
	if(dfn[k]==low[k])
	{
		int y;dep[++color]=0;
		do col[y=st.top()]=color,st.pop();while(y!=k);
	}
}
void dfs(int k,int fat)
{
	dep[k]=dep[fat]+1,top[k]=top[fat],fa[k][0]=fat;
	for(int i=1;i<=20;++i)fa[k][i]=fa[fa[k][i-1]][i-1];
	for(auto to:T[k])if(to!=fat)dfs(to,k);
}
inline int LCA(int x,int y)
{
	if(dep[x]>dep[y])swap(x,y);
	for(int i=20;i>=0;--i)if(dep[fa[y][i]]>=dep[x])y=fa[y][i];
	for(int i=20;i>=0;--i)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return x==y?x:fa[x][0];
}
inline int dis(int x,int y){return dep[x]+dep[y]-2*dep[LCA(x,y)];}
inline void mian()
{
	read(n,m);int x,y,z;
	for(int i=1;i<=m;++i)read(a[i].x,a[i].y,a[i].z);
	read(q);
	for(int i=1;i<=q;++i)read(z,x,y),a[z].q.eb((Node){x,y,i});
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=n;++i)fat[i]=i;
	for(int i=1,j=0;i<=m;i=j+1)
	{
		tot=0;
		while(a[i+1].z==a[i].z)++i;
		for(int k=j+1;k<=i;++k)
		{
			int x=find(a[k].x),y=find(a[k].y);
			if(x!=y)
			{
				if(!vis[x])vis[x]=1,dfn[x]=0,head[b[++tot]=x]=0;
				if(!vis[y])vis[y]=1,dfn[y]=0,head[b[++tot]=y]=0;
			}
		}
		cnt=1,num=color=0;
		for(int k=j+1;k<=i;++k)
		{
			int x=find(a[k].x),y=find(a[k].y);
			if(x!=y)add(x,y),add(y,x);
		}
		for(int k=1;k<=tot;++k){vis[b[k]]=0;if(!dfn[b[k]])tarjan(b[k],0);}
		for(int k=1;k<=color;++k)T[k].clear();
		for(int k=j+1;k<=i;++k)
		{
			int l=col[find(a[k].x)],r=col[find(a[k].y)];
			if(l!=r)T[l].eb(r),T[r].eb(l);
		}
		for(int k=1;k<=tot;++k)if(!dep[col[b[k]]])top[0]=col[b[k]],dfs(col[b[k]],0);
		for(int k=j+1;k<=i;++k)
		{
			int l=col[find(a[k].x)],r=col[find(a[k].y)];
			if(l==r)continue;
			for(auto [x,y,z]:a[k].q)
			{
				int xx=find(x),yy=find(y);
				if(!col[xx]||!col[yy]||xx==yy||top[col[xx]]!=top[col[yy]])continue;
				int d=dis(col[xx],col[yy]);
				if(dis(col[xx],l)+dis(col[yy],r)+1==d||dis(col[xx],r)+dis(col[yy],l)+1==d)
				ans[z]=1;
			}
		}
		for(int k=1;k<=tot;++k)col[b[k]]=0;
		while(j<m&&a[j+1].z<=a[i].z)
		++j,find(a[j].x)==find(a[j].y)?0:fat[find(a[j].x)]=find(a[j].y);
	}
	for(int i=1;i<=q;++i)write(ans[i],'\n');
}
```

---

## 作者：HJY2022 (赞：2)

一道图论题。讲一个比较容易想到的方法。

首先在线做法可能比较困难，所以考虑离线下来把查询挂在边上。

考虑查询的本质就是把除了这条边以外的所有边权小于等于它的全部加入并查集，然后看两个点是否联通。如果加入这条边之前不连通，加入后联通的话，那么说明这条边在修改后瓶颈路也会修改。

注意到如果这条边加入前和加入后都不连通并不会修改瓶颈路。

考虑如何维护这个过程。由于题目时间限制十分宽松，所以我们可以考虑分块。

对于每一种边权的边我们一起处理。设某一种边权的边有 $k$ 个，将这些边分为大小为 $B$ 的块。在每个块外的边我们直接暴力加入并查集，总加入时间复杂度为 $O(\frac{k}{B}k\log k)$。

对于每个块内的部分，考虑使用带撤销的并查集维护，每次把这条边前面的和后面的加入，最后在撤销，时间复杂度为 $O(Bk\log k)$。

取 $B=\sqrt{k}$ 即可得到最优复杂度 $O(k\sqrt{k}\log k)$，总时间复杂度为 $O(m\sqrt{m}\log n)$，尽管复杂度并不优秀，但是可以通过此题。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MX = 2e5;

struct Edge{
	int u,v,c,id;
}e[MX + 7];

struct Query{
	int id,x,y,u,v;
};

vector<int > g[MX + 7]; 
vector<Query > query[MX + 7];
int fa[MX + 7],sz[MX + 7],topx[MX + 7],topy[MX + 7],top;
bool mark[MX + 7],t1[MX + 7],t2[MX + 7];
int n,m,q;

int find(int x){
	if(fa[x] == x)return fa[x];
	return find(fa[x]);
}

void merge(int x,int y){
	top++;
	int xx = find(x),yy = find(y);
	if(xx == yy){
		topx[top] = topy[top] = -1;
		return;
	}
	if(sz[xx] > sz[yy])swap(xx,yy);
	topx[top] = xx,topy[top] = yy;
	fa[xx] = yy;
	sz[yy] += sz[xx];
}

void undo(){
	if(topx[top] != -1){
		fa[topx[top]] = topx[top];
		sz[topy[top]] -= sz[topx[top]];
	}
	top--;
}

bool cmp(Edge x,Edge y){
	return x.c < y.c;
}

void input(){
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		cin >> e[i].u >> e[i].v >> e[i].c;
		e[i].id = i;
	}
	cin >> q;
	for(int i = 1;i <= q;i++){
		int x,y,a;
		cin >> a >> x >> y;
		Query tmp;
		tmp.x = x,tmp.y = y;
		tmp.u = e[a].u,tmp.v = e[a].v;
		tmp.id = i;
		query[a].push_back(tmp);
	}
}

void add(int l,int r,int tl,int tr){//左闭右开 
	for(int i = l;i < tl;i++)merge(e[i].u,e[i].v);
	for(int i = tr;i < r;i++)merge(e[i].u,e[i].v);
}

void undos(int l,int r,int tl,int tr){
	for(int i = l;i < tl;i++)undo();
	for(int i = tr;i < r;i++)undo();
}

int main(){
	input();
	sort(e + 1,e + 1 + m,cmp);
	for(int i = 1;i <= n;i++)fa[i] = i,sz[i] = 1;
	for(int c = 1;c <= m;){
		int t = c + 1;
		while(e[t].c == e[c].c)t++;
		int len = t - c,B = sqrt(len) + 5;
		for(int st = c;st < t;st += B){
			int ed = min(t,st + B);
			add(c,t,st,ed);
			for(int i = st;i < ed;i++){
				add(st,ed,i,i + 1);
				int a = e[i].id;
				for(int j = 0;j < query[a].size();j++)t1[query[a][j].id] = find(query[a][j].x) == find(query[a][j].y);
				merge(e[i].u,e[i].v);
				for(int j = 0;j < query[a].size();j++)t2[query[a][j].id] = find(query[a][j].x) == find(query[a][j].y);
				undo();
				undos(st,ed,i,i + 1);
			}
			undos(c,t,st,ed);
		}
		for(int i = c;i < t;i++)merge(e[i].u,e[i].v);
		c = t;
	}
	for(int i = 1;i <= q;i++)
		if(!t1[i] && t2[i])cout << "1\n";
		else cout << "0\n";
	return 0;
}
```

一些鲜花：如果使用 LCT 并非分块来维护，可以优化时间复杂度至 $O(m\log m)$，但是显然没有别人的做法好写，所以意义可能不大。

---

## 作者：dami826 (赞：1)

首先注意到任何询问的结果一定是 $1$ 或 $0$，因为一条边边权增加 $1$，最极端的情况下答案也只会最大增加 $1$，而询问结果为 $1$，当且仅当：  
1. 此边在两点在 MST 上的路径上
2. 此边为两点 MST 路径上边权最大的边
3. 此边一定出现在所有 MST 上

证明：  
1. **结论一的必要性**  
如果此边不在任何一条两点间的路径上，显然它的边权改变不会影响两点间最小瓶颈值；如果此边在两点间的非 MST 路径上，由 MST 的性质得，这条路径不会成为两点间瓶颈值最小的路径，则它的边权改变也不会影响两点间最小瓶颈值。

2. **结论二的必要性**  
如果此边不是两点 MST 路径上边权最大的边，则设此边边权为 $w$，最大边权为 $\max w$，则 $w+1 \leq \max w$，由于询问互相独立，显然 $w$ 的变化不会影响 $\max w$，即最小瓶颈值不会改变。

3. **结论三的必要性**  
如果此边不不出现在所有 MST 上，则必有一条边权与它相等的边可以代替它的作用组成新的 MST，由于 MST 的连通性，则代替边一定可以带来一条瓶颈值与此边相等且不经过此边的 MST 路径，此时如果此边边权更改，代替边所在的 MST 路径会成为新的瓶颈值最小的路径，所以最小瓶颈值也不会改变。

4. **充分性**  
如果结论一、二、三同时满足，则此边边权由 $w$ 变为 $w+1$ 时，MST 不会变化，进而瓶颈值最小的路径也仍是它所在的 MST 路径，而此边又是瓶颈值最小的路径上的边权最大边，所以此边的边权变化必然引起瓶颈值最小的路径的瓶颈值变化，进而引起最小瓶颈值变化。

现在考虑如何判断一条边是否满足以上三个条件。  
- 首先考虑条件三，想要判断一条边是否在所有MST上，此时可以借用 [CF160D](https://www.luogu.com.cn/problem/CF160D) 的结论，按照边权从低到高遍历，第 $i$ 次遍历建出所有边权第 $i$ 小的边，然后跑 tarjan 求割边，是割边则证明出现在所有 MST 上，最后将当前图中的每个连通块缩成一个点。总时间复杂度 $O(n+m)$。
- 考虑条件二，kruskal 建出任意一棵 MST（因为满足条件的边在任意一棵 MST 上，所以具体哪一棵不重要），然后在它上面树剖+线段树维护边权最大值即可。时间复杂度 $O(m \log m+q \cdot \log n \cdot \log n)$。
- 考虑条件一，该条件可转化为这条边的两端均在路径上，所以问题就转化为判断一个点是否在另两个点之间的树上路径上，而一个点在另两个点之间的树上路径上可以转化为这个点在另两个点中至少一个到根节点的路径上且不在两者 lca 父亲到根节点的路径上，所以问题再次转化为找两点 lca（树剖可做）以及判断一个点是否在另一个点到根节点的路径上，这可以树剖跳重链 $O(\log n)$ 解决。时间复杂度 $O(q \log n)$。

```cpp
#include<bits/stdc++.h>
#define OK puts("OK");
using namespace std;
int n,m,q,en,minn=INT_MAX,maxn,head[200010],dfn[200010],low[200010],pnum,cut[200010],anc[200010],fa[200010],falen[200010],dfn2[200010],dep[200010],siz[200010],num,heav[200010],top[200010];
bool vis[200010],ans[200010],MST[200010];
vector<pair<pair<int,int>,int> > vct[200010];
struct edge{
	int to,nxt,len,id;
}e[400010];
void link(int from,int to,int len,int id){
//	printf("link %d %d %d %d\n",from,to,len,id);
	e[++en]=(edge){to,head[from],len,id};
	head[from]=en;
}
void tarjan(int now,int pre){
//	printf("dfs %d %d %d\n",now,pre,head[now]);
	dfn[now]=++pnum;
	vis[now]=1;
	low[now]=dfn[now];
	for(int i=head[now];i;i=e[i].nxt){
//		printf("in %d %d %d\n",e[i].id,now,e[i].to);
		if(e[i].id==pre){
			continue;
		}
		if(vis[e[i].to]){
			low[now]=min(low[now],dfn[e[i].to]);
			continue;
		}
		tarjan(e[i].to,e[i].id);
		low[now]=min(low[now],low[e[i].to]);
		if(low[e[i].to]>dfn[now]){
			cut[e[i].id]=1;
//			printf("cut %d\n",e[i].id);
		}
	}
//	printf("back\n");
}
struct line{
	int from,to,len,id;
	bool operator <(const line x)const{
		return len>x.len;
	}
}tmp[200010];
vector<line> qu[200010];
int find(int x){
	if(anc[x]==x){
		return x;
	}
	anc[x]=find(anc[x]);
	return anc[x];
}
void dfs(int now,int dp){
//	printf("dfs %d %d %d\n",now,dp,head[now]);
	dep[now]=dp;
	siz[now]=1;
	vis[now]=0;
	int maxn=0;
	for(int i=head[now];i;i=e[i].nxt){
//		printf("faaa %d %d %d %d %d %d\n",e[i].to,fa[now],i,e[i].nxt,MST[e[i].id],vis[e[i].to]);
		if(e[i].to==fa[now]||!MST[e[i].id]||!vis[e[i].to]){
			continue;
		}
		fa[e[i].to]=now;
//		printf("fa %d %d %d\n",e[i].to,now,i);
		falen[e[i].to]=e[i].len;
		dfs(e[i].to,dp+1);
		siz[now]+=siz[e[i].to];
		if(siz[e[i].to]>maxn){
			maxn=siz[e[i].to];
			heav[now]=e[i].to;
		}
	}
}
void dfs2(int now,int tp){
//	printf("dfs2 %d %d %d\n",now,tp,head[now]);
	top[now]=tp;
	dfn[now]=++num;
	dfn2[num]=now;
	vis[now]=1;
	if(heav[now]){
		dfs2(heav[now],tp);
	}
	for(int i=head[now];i;i=e[i].nxt){
		if(e[i].to==fa[now]||!MST[e[i].id]||vis[e[i].to]){
			continue;
		}
		dfs2(e[i].to,e[i].to);
	}
}
struct segment_tree{
	int tree[800010];
	void pushup(int index){
		tree[index]=max(tree[index<<1],tree[index<<1|1]);
	}
	void build(int index,int left,int right){
		if(left==right){
			tree[index]=falen[dfn2[left]];
			return;
		}
		int mid=(left+right)>>1;
		build(index<<1,left,mid);
		build(index<<1|1,mid+1,right);
		pushup(index);
	}
	int search(int gleft,int gright,int index,int left,int right){
		if(right<gleft||gright<left){
			return 0;
		}
		if(gleft<=left&&right<=gright){
			return tree[index];
		}
		int mid=(left+right)>>1;
		return max(search(gleft,gright,index<<1,left,mid),search(gleft,gright,index<<1|1,mid+1,right));
	}
}tr;
int query(int x,int y){
//	printf("query %d %d %d %d\n",x,y,top[x],top[y]);
	int res=0;
	while(top[x]!=top[y]){
//		printf("jump %d %d %d %d %d %d\n",x,y,top[x],top[y],dep[top[x]],dep[top[y]]);
		if(dep[top[x]]<dep[top[y]]){
			swap(x,y);
		}
		res=max(res,tr.search(dfn[top[x]],dfn[x],1,1,n));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]){
		swap(x,y);
	}
	res=max(res,tr.search(dfn[x]+1,dfn[y],1,1,n));
	return res;
}
bool query2(int x,int y,int z){
	int xx=x,yy=y,lca;
	bool res1=0,res2=0;
	while(top[x]!=top[y]){
//		printf("xy%d %d\n",x,y);
		if(dep[top[x]]<dep[top[y]]){
			swap(x,y);
		}
		x=fa[top[x]];
//		printf("xy%d %d\n",x,y);
	}
	if(dep[x]>dep[y]){
		swap(x,y);
	}
	lca=x;
//	printf("lca %d\n",lca);
	x=xx,y=yy;
	while(x){
		if(top[x]==top[z]&&dep[z]<=dep[x]){
			res1=1;
			break;
		}
		x=fa[top[x]];
	}
	while(y){
		if(top[y]==top[z]&&dep[z]<=dep[y]){
			res2=1;
			break;
		}
		y=fa[top[y]];
	}
	if(dep[z]<dep[lca]){
		return false;
	}
	return res1||res2;
}
int main(){
//	freopen("ABC301H.in","r",stdin);
//	freopen("ABC301H.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		anc[i]=i;
	}
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		qu[w].push_back((line){u,v,w,i});
		tmp[i]=(line){u,v,w,i};
		minn=min(minn,w);
		maxn=max(maxn,w);
	}
	for(int i=minn;i<=maxn;i++){
		en=0;
    	for(int j=0;j<qu[i].size();j++){
    		int ff=find(anc[qu[i][j].from]),ft=find(anc[qu[i][j].to]);
    		head[ff]=head[ft]=0;
		}
    	for(int j=0;j<qu[i].size();j++){
    		int ff=find(anc[qu[i][j].from]),ft=find(anc[qu[i][j].to]);
    		if(ff!=ft){
    			link(ff,ft,i,qu[i][j].id); 
    			link(ft,ff,i,qu[i][j].id); 
    			vis[ff]=0;
    			vis[ft]=0;
    			dfn[ff]=0;
    			dfn[ft]=0;
//    			printf("link %d %d %d\n",ff,ft,i);
			}
			else{
				ans[qu[i][j].id]=-1;
			}
		}
		for(int j=0;j<qu[i].size();j++){
			int ff=find(anc[qu[i][j].from]),ft=find(anc[qu[i][j].to]);
			if(ff==ft||dfn[ff]){
				continue;
			}
			pnum=0;
			tarjan(ff,0);
		}
		for(int j=0;j<qu[i].size();j++){
    		anc[find(qu[i][j].from)]=anc[find(qu[i][j].to)];
		}
	}
	for(int i=1;i<=m;i++){
		MST[i]=0;
	}
	for(int i=1;i<=n;i++){
		anc[i]=i;
		head[i]=0;
	}
	en=0;
	for(int i=1;i<=m;i++){
		link(tmp[i].from,tmp[i].to,tmp[i].len,tmp[i].id); 
		link(tmp[i].to,tmp[i].from,tmp[i].len,tmp[i].id); 
	}
	for(int i=minn;i<=maxn;i++){
		for(int j=0;j<qu[i].size();j++){
			int ff=find(anc[qu[i][j].from]),fs=find(anc[qu[i][j].to]);
			if(ff!=fs){
				MST[qu[i][j].id]=1;
				if(ff>fs){
					swap(ff,fs);
				}
				anc[fs]=ff;
			}
		}
	}
	dfs(1,0);
	dfs2(1,1);
	tr.build(1,1,n);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int a,s,t;
		scanf("%d %d %d",&a,&s,&t);
		if(cut[a]&&query(s,t)==e[2*a].len&&query2(s,t,e[2*a].to)&&query2(s,t,e[2*a-1].to)){
			printf("1\n");
		}
		else{
			printf("0\n");
		}
//		if(i==32){
//			return 0;
//		}
	}
	return 0;
}
```

---

## 作者：Helloworldwuyuze (赞：1)

## AT_abc301_h

### Des

给一个 $n$ 点 $m$ 边的带边权无向图，定义一条路径 $s\to u_1\to u_2\to \dots\to u_m\to t$ 的 $w$ 为 $s\to u_1,u_1\to u_2,\dots,u_m\to t$ 中的最大权值。而两个点 $(u,v)$ 的最小瓶颈路指的是所有 $u$ 到 $v$ 的路径中 $w$ 最小的那个。

现在有询问 $a, u, v$ 表示令第 $i$ 条边的权值 $+1$，会不会改变 $u\to v$ 的最小瓶颈路对应的 $w$。

### Sol

翻了一遍题解都没有发现 $O(n\alpha(n))$ 的题解，感觉思路并不难想，写一篇题解分享一下吧。

首先，显然的是，两个点 $(u,v)$ 的最小瓶颈路一定有一条在这张图的最小生成树上。这个自行理解即可。

于是，我们考虑使用 $\text{Kruskal}$ 建出生成树的过程。假设我们已经处理完了边权 $< w$ 的点，并且使用并查集将已经连在一起的点缩了起来。那么：

- 如果现在有一条边 $(u,v)$，其中 $(u,v)$ 已经在一个集合之中，那么显然这条边是毫无用处的，它不会改变任何事情。

- 否则，我们将它加入。具体的，我们建立一条包含 $u$ 并查集编号到包含 $v$ 的并查集编号的边。然后，把这个图拎出来跑一遍 $\text{Tarjan}$，那么，对于一次询问 $a,u,v$，它的值为 $1$ 当且仅当 $a$ 为割边切 $u,v$ 所在的并查集编号在 $a$ 这条边的两端。

  $a$ 这条边是割边保证了如果 $(u,v)$ 在 $a$ 的两端，那么它只有这一条路径可以从 $u$ 的联通块到达 $v$ 的联通块。而 $u,v$ 所在的并查集的编号在 $a$ 这条边的两端保证了它们需要跨过 $a$。

至于如何判断两个点在某条边的两端，直接判断一个在子树内另一个不在即可。

精细实现这一过程可以做到 $O(n\alpha(n))$ 的时间复杂度，$O(n)$ 的空间复杂度。复杂度瓶颈在于并查集。

跑得飞起，一发冲到最优解（截至24.11.14）。

```cpp
#define endl '\n'
using namespace std;

const int INF = 0x3f3f3f3f;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
typedef pair<int,bool*> PIB;
const int N = 2e5 + 10;
const int M = 1e6 + 10;
inline int max(int x,int y){ return x<y ? y : x; }
inline int min(int x,int y){ return x<y ? x : y; }

int fa[N], n, m, q, a, u, v, mx, sz[N];
struct edge{ int u, v, id; };
vector<edge> e[N];
vector<int> bri;
vector<PII> g[N];
bool del[N];

bool bridge[N];
int dfn[N], low[N], idx, siz[N];
bool ans[N], vis[N], in[N];

inline int find(int x){ return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
inline void merge(int x,int y){
	int fx = find(x), fy = find(y);
	if(sz[fx] > sz[fy])	swap(fx, fy);
	fa[fx] = fy;
}
vector<int> pnt;
void Tarjan(int x){
	pnt.pb(x);
	dfn[x] = low[x] = ++idx, siz[x] = 1, vis[x] = true;
	for(auto y:g[x])
		if(!dfn[y.fi]){
			del[y.se] = true, Tarjan(y.fi), low[x] = min(low[x], low[y.fi]);
			if(low[y.fi] > dfn[x] && !bridge[y.se])	bridge[y.se] = true, bri.pb(y.se);
			siz[x] += siz[y.fi];
		}else if(!del[y.se])	low[x] = min(low[x], dfn[y.fi]);
}
vector<edge> qu[N];
bool flag[N];

inline bool insubtree(int x,int u){
	return dfn[u] <= dfn[x] && dfn[x] < dfn[u] + siz[u];
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u, v, w; cin>>u>>v>>w;
		e[w].pb(edge{u, v, i}), mx = max(mx, w);
	}
	cin>>q;
	for(int i=1;i<=q;++i){
		int u, v, a; cin>>a>>u>>v;
		qu[a].pb(edge{u, v, i});
	}
	for(int i=1;i<=n;++i)	fa[i] = i;
	for(int i=1;i<=mx;++i){
		static vector<int> p; int tot = -1;
		vector<int>().swap(p);
		for(edge c : e[i]){
			int fx = find(c.u), fy = find(c.v); ++tot;
			if(fx == fy)	continue;
			if(!in[fx])	in[fx] = true, p.pb(fx);
			if(!in[fy])	in[fy] = true, p.pb(fy);
			g[fx].pb(mk(fy, tot)), g[fy].pb(mk(fx, tot));
		}
		for(int x : p){
			if(!vis[x]){
				bri.clear(); pnt.clear();
				Tarjan(x);
				for(int id : bri){
					edge tmp = e[i][id];
					int fu = find(tmp.u), fv = find(tmp.v);
					int u = dfn[fu] < dfn[fv] ? fu : fv;
					int v = dfn[fu] < dfn[fv] ? fv : fu;
					for(edge c : qu[tmp.id]){
						int x = find(c.u), y = find(c.v);
						if(!dfn[x] || !dfn[y])	continue;
						if(insubtree(x, v) ^ insubtree(y, v))	ans[c.id] = true;
					}
				}
				for(int x : pnt)	dfn[x] = low[x] = siz[x] = 0;
			}
		}
		for(edge c : e[i])	merge(c.u, c.v);
		for(int x : p)	vis[x] = in[x] = false, g[x].clear();
		for(int i=0;i<=tot;++i)	del[i] = bridge[i] = false;
		idx = 0;
	}
	for(int i=1;i<=q;++i)	cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：1)

这怎么放到 Ex 的啊 /fn

**【简要题意】**

$n$ 个点 $m$ 条边的无向图，$q$ 次询问，每次询问 $(i,u,v)$ 表示给第 $i$ 条边边权 $+1$ 后 $u \to v$ 的最小瓶颈路，询问互相独立。$n,m,q \le 2 \times 10^5$。

**【题解】**

经典结论是 $u \to v$ 的最小瓶颈路等于最小生成树上 $u,v$ 之间的最大边权。

建最小生成树，考虑第 $i$ 条边的位置，如果它根本不在 $u,v$ 的路径上，或者小于 $u,v$ 路径上的 $\max$，那么对答案肯定没有影响。否则，我们需要找到这条边边权 $+1$ 后新的最小生成树，其实就是断开边 $i$ 后连接两个连通块的最小边权。令边 $i$ 为 $(x,y)$ 且 $dep_x > dep_y$，注意新边 $(x',y')$ 需要满足 $x'$ 在 $x$ 子树内且 $y'$ 不在 $x$ 的子树内，转化为 dfn 序后是**二维数点**模型。由于 $\min$ 没有可减性，我们用树套树维护。

找到新的最小生成树后，只需要求出新的最小生成树上 $u,v$ 之间的最大边，拆成 $(u,x'),(x',y'),(y',v)$ 三段路径在原树上求 $\max$ 即可。

复杂度瓶颈在树套树，时空复杂度均为 $\mathcal O(n \log^2 n)$。

事实上，由于每次二维数点一定有一维形如 $[1,x]$ 或 $[x,n]$，可以正着倒着各做一遍扫描线，线段树维护另一维的 $\min$ 即可做到一只 $\log$。

两只 $\log$ 的实现虽然代码略长（$\text{4.51KB}$），但是基本没有细节，调试较为简单。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int top[N],son[N],fa[N],siz[N],dfn[N],dep[N],rt[N*40],tot,ti,tu,tv,u,a,v,q,p[N],mx[N][22],ans[N],f[N][22],val[N],vis[N],n,m,au[N],av[N],aw[N];
int t[N*300],ls[N*300],rs[N*300];
int cmp(int x,int y){return aw[x] < aw[y] ? x : y;}
struct ges{
    struct seg{
        void upd(int &s,int l,int r,int x,int k){
            if(!s) s = ++tot;
            if(l == r) return t[s] = cmp(t[s],k),void();
            int mid = (l + r) / 2; 
            if(x <= mid) upd(ls[s],l,mid,x,k); else upd(rs[s],mid+1,r,x,k);
            t[s] = cmp(t[ls[s]],t[rs[s]]);
        }int qry(int s,int l,int r,int ql,int qr){
            if(ql <= l && r <= qr) return t[s];
            int mid = (l + r) / 2,ans = 0;
            if(ql <= mid) ans = cmp(ans,qry(ls[s],l,mid,ql,qr));
            if(qr > mid) ans = cmp(ans,qry(rs[s],mid+1,r,ql,qr));
            return ans;
        }
    }sg;
    void upd(int s,int l,int r,int x,int y,int k){
        sg.upd(rt[s],1,n,y,k); int mid = (l + r) / 2;
        if(l == r) return ;
        if(x <= mid) upd(s*2,l,mid,x,y,k); else upd(s*2+1,mid+1,r,x,y,k);
    }int qry(int s,int l,int r,int ql,int qr,int tl,int tr){
        if(ql > qr || tl > tr) return 0;
        if(ql <= l && r <= qr) return sg.qry(rt[s],1,n,tl,tr);
        int mid = (l + r) / 2,ans = 0;
        if(ql <= mid) ans = cmp(ans,qry(s*2,l,mid,ql,qr,tl,tr));
        if(qr > mid) ans = cmp(ans,qry(s*2+1,mid+1,r,ql,qr,tl,tr));
        return ans;
    }
}seg;
struct dsu{
    int fa[N];
    int fd(int x){return x == fa[x] ? x : fa[x] = fd(fa[x]);}
    void init(){for(int i = 1;i <= n;i ++) fa[i] = i;}
    void mg(int x,int y){x = fd(x),y = fd(y),fa[x] = y;}    
}d;
vector<pair<int,int>> g[N];
void dfs1(int u,int ft){
    fa[u] = ft,dep[u] = dep[ft] + 1,siz[u] = 1,f[u][0] = ft,mx[u][0] = val[u];
    for(int i = 1;i <= __lg(dep[u]);i ++) f[u][i] = f[f[u][i-1]][i-1],mx[u][i] = max(mx[u][i-1],mx[f[u][i-1]][i-1]);
    for(auto [v,w] : g[u]) if(v != ft) if(val[v] = w,dfs1(v,u),siz[u] += siz[v],siz[v] > siz[son[u]]) son[u] = v;
}void dfs2(int u,int tp){
    top[u] = tp,dfn[u] = ++ti; if(son[u]) dfs2(son[u],tp);
    for(auto [v,w] : g[u]) if(v != son[u] && v != fa[u]) dfs2(v,v);
}int qrymax(int u,int v){
    if(dep[u] < dep[v]) swap(u,v); int ans = 0;
    for(int i = __lg(dep[u]);i >= 0;i --) if(dep[f[u][i]] >= dep[v]) ans = max(ans,mx[u][i]),u = f[u][i];
    return ans;
}int lca(int u,int v){
    while(top[u] != top[v])
        if(dep[top[u]] > dep[top[v]]) u = fa[top[u]]; else v = fa[top[v]];
    return dep[u] < dep[v] ? u : v;
}bool ck(int u,int v,int x,int y){
    int fx = 0,fy = 0;
    auto kc = [&](int l,int r,int x){return l <= x && x <= r;};
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        fx |= kc(dfn[top[u]],dfn[u],dfn[x]),fy |= kc(dfn[top[u]],dfn[u],dfn[y]),u = fa[top[u]];
    }if(dfn[u] > dfn[v]) swap(u,v);
    fx |= kc(dfn[u],dfn[v],dfn[x]),fy |= kc(dfn[u],dfn[v],dfn[y]);
    return fx && fy;
}int qpath(int u,int v){int d = lca(u,v); return max(qrymax(u,d),qrymax(v,d));}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m; d.init(); aw[0] = 1e9;
    for(int i = 1;i <= m;i ++) cin >> au[i] >> av[i] >> aw[i],p[i] = i;
    sort(p + 1,p + m + 1,[&](int x,int y){return aw[x] < aw[y];});
    auto add = [&](int x,int y,int w){g[x].emplace_back(y,w),g[y].emplace_back(x,w);};
    for(int i = 1;i <= m;i ++)
        if(u = d.fd(au[p[i]]),v = d.fd(av[p[i]]),u != v) vis[p[i]] = 1,d.mg(u,v),add(au[p[i]],av[p[i]],aw[p[i]]);
    dfs1(1,0),dfs2(1,1);
    for(int i = 1;i <= m;i ++) if(!vis[i]) seg.upd(1,1,n,dfn[au[i]],dfn[av[i]],i),seg.upd(1,1,n,dfn[av[i]],dfn[au[i]],i);
    for(cin >> q;q --;){
        cin >> a >> u >> v,tu = au[a],tv = av[a]; if(dep[tu] < dep[tv]) swap(tu,tv);
        if(!ck(u,v,tu,tv)) {cout << "0\n"; continue;}
        int d = lca(u,v),mx = max(qrymax(u,d),qrymax(v,d));
        if(aw[a] != mx) {cout << "0\n"; continue;}
        int k = cmp(seg.qry(1,1,n,dfn[tu],dfn[tu] + siz[tu] - 1,1,dfn[tu] - 1),
                    seg.qry(1,1,n,dfn[tu],dfn[tu] + siz[tu] - 1,dfn[tu] + siz[tu],n));
        if(aw[k] < mx) cout << "0\n";
        else if(aw[k] > mx) cout << "1\n";
        else{
            auto ck = [&](int u,int v){return dfn[u] <= dfn[v] && dfn[v] <= dfn[u] + siz[u] - 1;};
            int ru = au[k],rv = av[k];
            if(!ck(tu,ru)) swap(ru,rv);
            if(min(qpath(u,ru),qpath(v,rv)) <= aw[a]) cout << "0\n"; else cout << "1\n";
        }
    }
}
```

---

## 作者：yzq_yzq (赞：0)

简单做法

一条边权为 $w$ 的边加 $1$ 过后不是瓶颈路等价于把边权 $\leq w$ 的除自己以外的边加上过后 $x,y$ 不连通。

可以转化成把 $\leq w$ 的边加上过后删掉这条边过后是否连通，于是可以考虑线段树分治维护连通性。

考虑构造时间轴 $[1,lim]$ ，我们要把边权相同的边放在一个共同的时间 $[L,R]$ 上，然后假如一条边有询问，就把它的询问挂在 $i$ 上，然后在 $[L,i)$ ，$(i,lim]$ 加入这条边，否则直接加在 $[L,lim]$ 上。最后判是否连通即可。

注意要特判原本瓶颈路就大于 $w$ 的情况。

有不懂的看代码。

```cpp
#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = x; i <= y; ++i)
#define drep(i, x, y) for (int i = x; i >= y; --i)
#define ll long long
#define pb push_back
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 200020;
int n, m, q, ti, mx, ans[N];
struct edge { int u, v, w, id; } E[N], Q[N];
struct qry { int u, v, id; } ;
struct DSU {
	int fa[N], siz[N], x[N], y[N], tp;
	DSU() { tp = 0; rep(i, 0, N - 1) fa[i] = i, siz[i] = 1; }
	inline int find(int x) { while(fa[x] != x) x = fa[x]; return x; }
	inline bool merge(int u, int v) {
		u = find(u), v = find(v);
		if(u == v) return 0;
		if(siz[u] > siz[v]) swap(u, v);
		++tp, x[tp] = u, y[tp] = v;
		fa[u] = v, siz[v] += siz[u]; return 1;
	}
	inline void undo(int lst) {
		while(tp > lst) {
			siz[y[tp]] -= siz[x[tp]];
			fa[x[tp]] = x[tp];
			--tp;
		}
	}
} D;
#define pii pair<int, int>
vector<pii> T[N << 4];
vector<int> p[N], q2[N];
vector<qry> vec[N << 2];
inline void ins(int ql, int qr, pii x, int p = 1, int l = 1, int r = mx) {
	if(qr < l || r < ql) return;
	if(ql <= l && r <= qr) return void(T[p].pb(x));
	int mid = (l + r) >> 1;
	ins(ql, qr, x, p << 1, l, mid), ins(ql, qr, x, p << 1 | 1, mid + 1, r);
}
inline void solve(int p = 1, int l = 1, int r = mx) {
	int lst = D.tp;
	for(auto [u, v] : T[p]) D.merge(u, v);
	if(l == r) {
		for(auto [u, v, i] : vec[l])
			ans[i] = (D.find(u) != D.find(v));
	} else {
		int mid = (l + r) >> 1;
		solve(p << 1, l, mid);
		solve(p << 1 | 1, mid + 1, r);
	} D.undo(lst);
}
int main() {
	IOS; cin >> n >> m;
	rep(i, 1, m) cin >> E[i].u >> E[i].v >> E[i].w, p[E[i].w].pb(i);
	cin >> q; rep(i, 1, q) cin >> Q[i].w >> Q[i].u >> Q[i].v, q2[Q[i].w].pb(i), Q[i].id = i;
	mx = m * 3 + q;
	rep(i, 1, m) {
		int L = ti + 1, cnt = p[i].size();
		if(!cnt) continue; ++ti;
		for(int j : p[i]) if(!q2[j].size()) ins(L, mx, {E[j].u, E[j].v});
		for(int j : p[i]) {
			if(!q2[j].size()) continue; int x = ++ti;
			ins(L, x - 1, {E[j].u, E[j].v});
			ins(x + 1, mx, {E[j].u, E[j].v});
			for(int k : q2[j]) vec[x].pb({Q[k].u, Q[k].v, k});
		}
	}
//	cout << mx << " " << ti << "\n";
	solve();
	sort(Q + 1, Q + 1 + q, [&](edge x, edge y) { return E[x.w].w < E[y.w].w; });
	rep(i, 1, q) Q[i].w = E[Q[i].w].w;
	sort(E + 1, E + 1 + m, [&](edge x, edge y) { return x.w < y.w; });
	int pos = 0;
	rep(i, 1, q) {
		while(pos < m && E[pos + 1].w <= Q[i].w) ++pos, D.merge(E[pos].u, E[pos].v);
		if(D.find(Q[i].u) != D.find(Q[i].v)) ans[Q[i].id] = 0;
	}
	D.undo(0);
	rep(i, 1, q) {
		while(pos < m && E[pos + 1].w < Q[i].w) ++pos, D.merge(E[pos].u, E[pos].v);
		if(D.find(Q[i].u) == D.find(Q[i].v)) ans[Q[i].id] = 0;
	}
	D.undo(0);
	rep(i, 1, q) cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：liuziqin (赞：0)

# [题目](https://www.luogu.com.cn/problem/AT_abc301_h)

## 前置知识

**树链剖分**，**吉司机线段树**，**LCA**，**最小生成树**。

## 思路

首先应该意识到最小瓶颈路一定是原图的最小生成树 $S$ 到 $T$ 上路径边权的最大值。

考虑在什么时候边权加 $1$ 会产生影响。我们设当前边为 $(u,v)$，查询路径为 $(S,T)$。显然，只有当边 $(u,v)$ 在路径 $(S,T)$ 上且 $(u,v)$ 的边权为最大边权时才有可能对答案产生影响。

当 $(u,v)$ 恰好为最大边权时，如果最小瓶颈路不会发生改变，就一定存在一条非树边 $(x,y)$ 满足 $w_{(x,y)}\le w_{(u,v)}$ 且断开边 $(u,v)$ 时，连接 $(x,y)$ 可以 $S$ 和 $T$ 联通。

对于每一条非树边 $(x,y)$，我们找出所有的边 $(u,v)$ 满足断开边 $(u,v)$ 时再连接边 $(x,y)$ 可以使原生成树联通。

那么显然这样的边 $(u,v)$ 只有可能是生成树上的路径 $(x,y)$ 上。

![](https://cdn.luogu.com.cn/upload/image_hosting/kxhuw6kf.png?x-oss-process=image/resize,m_lfit,h_300,w_1000)

如图，对于一条非树边 $(3,7)$，当标绿的边断开时，连接边 $(3,7)$ 可以使原树联通。

我们对于每一条树边求出它的替代边的边权的最小值，这个操作可以用**树链剖分**进行维护。

当加入一条非树边的贡献时，需要对一条链中每一条边与当前边权取最小值，这在树剖的线段树上显然是一个区间最值操作，可以用**吉司机线段树**进行维护。

## 细节
对于如何判断边 $(u,v)$ 是否在路径 $(s,t)$ 上，可以直接在树剖的过程中用 **dfs 序**判断。
## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005;
const int INF=1e9;
int n,m;
struct edge{
	int to,nxt,w;
}e[N<<1];
int head[N],cur;
void add_edge(int u,int v,int w){
	e[++cur].to=v;
	e[cur].nxt=head[u];
	e[cur].w=w;
	head[u]=cur;
}//加边
struct tree{
	struct segtree{
		int mx[N<<2],mx_sec[N<<2],mn[N<<2],mx_cnt[N<<2];
		int lazy_min[N<<2];
		void pushup(int p){
			if(mx[p*2]==mx[p*2+1]){
				mx[p]=mx[p*2];
				mx_sec[p]=max(mx_sec[p*2],mx_sec[p*2+1]);
				mx_cnt[p]=mx_cnt[p*2]+mx_cnt[p*2+1];
			}
			else if(mx[p*2]>mx[p*2+1]){
				mx[p]=mx[p*2];
				mx_cnt[p]=mx_cnt[p*2];
				mx_sec[p]=max(mx[p*2+1],mx_sec[p*2]);
			}
			else {
				mx[p]=mx[p*2+1];
				mx_sec[p]=max(mx[p*2],mx_sec[p*2+1]);
				mx_cnt[p]=mx_cnt[p*2+1];
			}
			mn[p]=min(mn[p*2],mn[p*2+1]);
		}
		void a_lazy_min(int p,int v){
			if(mx[p]<=v)return ;
			if(mn[p]==mx[p])mn[p]=v;
			mx[p]=lazy_min[p]=v;
		}
		void push_down(int p){
			if(lazy_min[p]==INF)return ;
			a_lazy_min(p*2,lazy_min[p]);
			a_lazy_min(p*2+1,lazy_min[p]);
			lazy_min[p]=INF;
		}
		void build(int p,int l,int r){
			lazy_min[p]=INF;
			if(l==r){
				mx[p]=mn[p]=INF;
				mx_sec[p]=-INF;
				mx_cnt[p]=1;
				return ;
			}
			int mid=(l+r)>>1;
			build(p*2,l,mid);
			build(p*2+1,mid+1,r);
			pushup(p);
		}
		void add_min(int p,int l,int r,int x,int y,int v){
			if(mx[p]<=v)return ;
			if(l>=x&&r<=y&&mx_sec[p]<v){
				a_lazy_min(p,v);
				return ;
			}
			int mid=(l+r)>>1;
			push_down(p);
			if(mid>=x)add_min(p*2,l,mid,x,y,v);
			if(mid<y)add_min(p*2+1,mid+1,r,x,y,v);
			pushup(p);
		}
		int query_mn(int p,int l,int r,int x,int y){
			if(l>=x&&r<=y)return mn[p];
			int mid=(l+r)>>1,ans=INF;
			push_down(p);
			if(mid>=x)ans=min(ans,query_mn(p*2,l,mid,x,y));
			if(mid<y)ans=min(ans,query_mn(p*2+1,mid+1,r,x,y));
			return ans;
		}
	}st;//线段树区间最值操作
	int son[N],dfn[N],rnk[N],dep[N],fa[N],siz[N],top[N],cnt;
	void dfs1(int u,int ft){
		siz[u]=1;
		son[u]=-1;
		dep[u]=dep[ft]+1;
		fa[u]=ft;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v==ft)continue;
			dfs1(v,u);
			siz[u]+=siz[v];
			if(son[u]==-1||siz[v]>siz[son[u]])son[u]=v;
		}
	}
	void dfs2(int u,int tp){
		top[u]=tp;
		cnt++;
		dfn[u]=cnt;
		rnk[cnt]=u;
		if(son[u]!=-1)dfs2(son[u],tp);
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v==son[u]||v==fa[u])continue;
			dfs2(v,v);
		}
	}//树链剖分的预处理
	void add(int x,int y,int v){
		int fx=top[x],fy=top[y];
		while(fx!=fy){
			if(dep[fx]>=dep[fy])st.add_min(1,1,n,dfn[fx],dfn[x],v),x=fa[fx];
			else st.add_min(1,1,n,dfn[fy],dfn[y],v),y=fa[fy];
			fx=top[x];
			fy=top[y];
		}
		if(dfn[x]<dfn[y])st.add_min(1,1,n,dfn[x]+1,dfn[y],v);
		else st.add_min(1,1,n,dfn[y]+1,dfn[x],v);
	}//加入非树边
	bool check(int u,int v,int x,int y){
		bool used1=0,used2=0;
		int fx=top[x],fy=top[y];
		while(fx!=fy){
			if(dep[fx]>=dep[fy]){
				if(dfn[fx]<=dfn[u]&&dfn[u]<=dfn[x])used1=1;
				if(dfn[fx]<=dfn[v]&&dfn[v]<=dfn[x])used2=1;
				x=fa[fx];
			}
			else {
				if(dfn[u]>=dfn[fy]&&dfn[u]<=dfn[y])used1=1;
				if(dfn[v]>=dfn[fy]&&dfn[v]<=dfn[y])used2=1;
				y=fa[fy];
			}
			fx=top[x];
			fy=top[y];
		}
		if(dfn[x]<dfn[y]){
			if(dfn[x]<=dfn[u]&&dfn[u]<=dfn[y])used1=1;
			if(dfn[x]<=dfn[v]&&dfn[v]<=dfn[y])used2=1;
		}
		else{
			if(dfn[y]<=dfn[u]&&dfn[u]<=dfn[x])used1=1;
			if(dfn[y]<=dfn[v]&&dfn[v]<=dfn[x])
				used2=1;
		}
		return used1&&used2;
	}//检查(u,v)是否在(s,t)上
	int query(int u,int v){
		int lca=max(dfn[u],dfn[v]);
		return st.query_mn(1,1,n,lca,lca);
	}//单点查可替代的最小边权
}s1;
struct LCA{
	int fa[N][25],mx[N][25],dep[N];
	void dfs(int u,int ft){
		dep[u]=dep[ft]+1;
		fa[u][0]=ft;
		for(int i=1;i<=20;i++){
			fa[u][i]=fa[fa[u][i-1]][i-1];
			mx[u][i]=max(mx[u][i-1],mx[fa[u][i-1]][i-1]);
		}
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,w=e[i].w;
			if(v==ft)continue;
			mx[v][0]=w;
			dfs(v,u);
		}
	}
	int get_lca(int x,int y){
		if(dep[x]<dep[y])swap(x,y);
		for(int i=20;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
		if(x==y)return x;
		for(int i=20;i>=0;i--)
		if(fa[x][i]!=fa[y][i]){
			x=fa[x][i];
			y=fa[y][i];
		}
		return fa[x][0];
	}
	int get_mx(int x,int y){
		int lca=get_lca(x,y);
		int ans=0;
		for(int i=20;i>=0;i--){
			if(dep[fa[x][i]]>=dep[lca])ans=max(ans,mx[x][i]),x=fa[x][i];
			if(dep[fa[y][i]]>=dep[lca])ans=max(ans,mx[y][i]),y=fa[y][i];
		}
		return ans;
	}
}s2;//LCA 求链上最大边权
struct node{
	int u,v,w,id;
}in[N],a[N];
bool used[N];
bool cmp(node a,node b){
	return a.w<b.w;
}
int fa[N];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool merge(int x,int y){
	int p=find(x),q=find(y);
	if(p==q)return 0;
	fa[p]=q;
	return 1;
}
void krukstra(){
	for(int i=1;i<=n;i++)fa[i]=i;
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		if(!merge(a[i].u,a[i].v))continue;
		add_edge(a[i].u,a[i].v,a[i].w);
		add_edge(a[i].v,a[i].u,a[i].w);
		used[a[i].id]=1;
	}
}//建出最小生成树
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>in[i].u>>in[i].v>>in[i].w;
		a[i].u=in[i].u;
		a[i].v=in[i].v;
		a[i].w=in[i].w;
		a[i].id=i;
	}//输入
	krukstra();
	s1.dfs1(1,0);
	s1.dfs2(1,1);
	s1.st.build(1,1,n);
	s2.dfs(1,0);//各种预处理
	for(int i=1;i<=m;i++){
		if(used[i])continue;
		int u=in[i].u,v=in[i].v,w=in[i].w;
		s1.add(u,v,w);
	} //加入非树边
	int q;
	cin>>q;
	while(q--){
		int i,s,t;
		cin>>i>>s>>t;
		if(!used[i]){
			cout<<"0\n";
			continue;
		}//不是树边就直接输0
		int u=in[i].u,v=in[i].v,w=in[i].w;
		int ft=s2.get_lca(s,t);
		if(s1.check(u,v,s,t)){
			int mx=s2.get_mx(s,t);
			int tmp=s1.query(u,v);
			if(w<mx){
				cout<<"0\n";
				continue;
			}//边权小于最大边权直接输0
			cout<<min(1ll,tmp-w)<<"\n";//判断替代边是否能使边权变小
			continue;
		}//如果该边在路径上
		cout<<"0\n";
	}
	return 0;
}
```

---

