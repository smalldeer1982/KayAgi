# [NOISG 2022 Finals] Grapevine

## 题目描述

Syrup 有一个巨大的葡萄藤。这个葡萄藤上共有 $N$ 片叶子，用 $1 \sim N$ 编号；这些叶子之间有 $N-1$ 条藤连接。第 $i$ 条藤连接第 $A_i$ 和第 $B_i$ 片叶子，长度为 $W_i$。换句话说，这些叶子和藤组成了一棵树。没有两个葡萄藤的两端相同，且这些叶子之间都可以相互到达。

Syrup 精通养护葡萄藤。他可以向一个叶子 $j$ **浇水**，使得这里飞速生长。如果这片叶子上还没有葡萄，那么浇完水后会立刻长出；如果已经有葡萄了，那么这个葡萄会因为水分过多而消失。

他也可以选择一条树枝，并**改变它的长度**。因为这个葡萄藤实在太大了，所以他需要站在叶子上，并快速**找到**离它距离最近的一个葡萄。

现在，刚刚经历过暴风雨的葡萄藤上没有葡萄。在这一周内，Syrup 打算进行 $Q$ 次以上操作，他想让你帮他快速回答出他的问题。

## 说明/提示

**【数据范围】**

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$6$|$N,Q\le2000$|
|$2$|$14$|对于所有查询操作，保证 $q=1$|
|$3$|$15$|整个葡萄藤是一颗完全二叉树，$A_i=\lfloor\frac{i+1}{2}\rfloor,B_i=i+1$|
|$4$|$15$|在任意时刻整个葡萄藤上都最多只有一个葡萄|
|$5$|$18$|所有 `2` 操作都在 `1` 和 `3` 操作之前，且对于所有 `3` 操作，$w=0$|
|$6$|$32$|无|

对于 $100\%$ 的数据，$2 \le N \le 100000,1 \le Q \le 100000,1 \le A_i \not = B_i \le N,0 \le W_i \le 10^9$。

## 样例 #1

### 输入

```
7 11
1 2 2
2 3 4
5 6 1
5 3 6
3 7 6
2 4 9
2 6
2 4
2 7
1 1
3 2 3 0
1 1
3 6 5 0
1 1
3 3 5 0
3 2 4 0
1 1
```

### 输出

```
11
8
8
2```

## 样例 #2

### 输入

```
6 11
1 2 3
1 3 4
2 4 1
2 5 4
3 6 6
2 3
1 2
2 4
3 1 3 2
1 1
2 3
3 2 1 2
2 4
1 3
2 2
1 3
```

### 输出

```
7
2
-1
4```

## 样例 #3

### 输入

```
7 8
1 2 2
2 3 3
3 6 2
4 6 1
5 6 4
6 7 3
2 3
1 4
2 3
2 5
1 1
3 6 7 4
1 5
1 7
```

### 输出

```
3
11
0
8```

# 题解

## 作者：RainySoul (赞：6)

我来写一篇点分树题解。点分树无脑干就完了，但是为啥没人写呢？等你写完就知道了。。。。

淀粉树上每个点开一个线段树，下标按照这个连通块遍历的 $\text{dfn}$ 序建。叶子节点维护连通块内每个点到当前点的 $dis$，其他节点就是区间 $\min$。

初始所有点皆为白点。

操作 $1$：查询距离点 $x$ 最近的黑点。点分树上暴力跳祖先，查当前点到点分树上当前点子树内所有点的 $dis$ 的 $\min$。最优化问题，来自同子树的一定不优，所以无需考虑消除 $u$ 与 $fa_u$ 子树内的重叠贡献。

操作 $2$：反转点 $x$ 颜色。暴力跳祖先直接维护。

操作 $3$：修改一条边 $(a,b)$ 的边权。首先边权变化动态维护 $dis$ 可以使用树剖，边权转点权。然后考虑这个操作对当前场上的黑点是有影响的，前面按照连通块遍历 $\text{dfn}$ 序的处理就是为这个操作服务的，这样可以保证每次涉及修改的点都是一个连续区间，从点分树上 $a$ 和 $b$ 的 $\text{LCA}$ 开始暴力跳祖先，区间加。

一些麻烦的地方是你需要记录每一个连通块中每个点的 $\text{dfn}$ 序，总点数是 $O(n \log n)$ 级别的，需要一些动态的数据结构记录，这里使用平板电视中的 `cc_hash_table`。

看起来是不是非常简单！但是由于笔者很唐，他与这道题鏖战了一天，无敌了。

相信聪明的你一定可以很快切穿它的！

AC code：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define inf 1e18
#define int long long
using namespace std;
using namespace __gnu_pbds;
const int N=100010,lgN=50;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}

//树剖
struct SegementTree1{//这个是求dis用的树剖线段树
    int w[N<<2];
    inline void update(int u,int l,int r,int x,int k){
        if(l==r){
            w[u]=k;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid)update(u*2,l,mid,x,k);
        else update(u*2+1,mid+1,r,x,k);
        w[u]=w[u*2]+w[u*2+1];
    }
    inline int query(int u,int l,int r,int x,int y){
        if(x<=l&&r<=y)return w[u];
        int mid=(l+r)>>1;
        int res=0;
        if(x<=mid)res+=query(u*2,l,mid,x,y);
        if(y>mid)res+=query(u*2+1,mid+1,r,x,y);
        return res;
    }
}T1;
struct zyx{int to,w;};
vector<zyx> e[N];
struct csq{int u,v,w;};
vector<csq> edge;
int n,Q,cnt;
int fa[N],sz[N],dep[N],son[N],top[N],dfn[N],rnk[N];
inline void dfs1(int now,int fz){
    fa[now]=fz;
    sz[now]=1;
    dep[now]=dep[fz]+1;
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i].to;
        if(to==fz)continue;
        dfs1(to,now);
        sz[now]+=sz[to];
        if(sz[to]>sz[son[now]])son[now]=to;
    }
}
inline void dfs2(int now,int topf){
    top[now]=topf;
    dfn[now]=++cnt;
    rnk[cnt]=now;
    if(!son[now])return;
    dfs2(son[now],topf);
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i].to;
        if(to==fa[now]||to==son[now])continue;
        dfs2(to,to);
    }
}
int getdis(int x,int y){
    int res=0;
    while(top[x]!=top[y]){
        if(dep[top[y]]>dep[top[x]])swap(x,y);
        res+=T1.query(1,1,n,dfn[top[x]],dfn[x]);
        x=fa[top[x]];
    }
    if(dep[y]>dep[x])swap(x,y);
    res+=T1.query(1,1,n,dfn[y]+1,dfn[x]);
    return res;
}
//树剖

//建点分树
struct SegementTree2{
    int w[N*lgN],ls[N*lgN],rs[N*lgN],lazy[N*lgN];
    int rt[N],tot;
    inline void pushdown(int u){
        if(!lazy[u])return;
        w[ls[u]]+=lazy[u];
        w[rs[u]]+=lazy[u];
        lazy[ls[u]]+=lazy[u];
        lazy[rs[u]]+=lazy[u];
        lazy[u]=0;
    }
    inline void update1(int &u,int l,int r,int x,int k){//单点修改
        if(!u)u=++tot;
        if(l==r){
            w[u]=k;
            return;
        }
        int mid=(l+r)>>1;
        pushdown(u);
        if(x<=mid)update1(ls[u],l,mid,x,k);
        else update1(rs[u],mid+1,r,x,k);
        w[u]=min(w[ls[u]],w[rs[u]]);
    }
    inline void update2(int &u,int l,int r,int x,int y,int k){//区间加
        if(!u)u=++tot;
        if(x<=l&&r<=y){
            w[u]+=k;
            lazy[u]+=k;
            return;
        }
        int mid=(l+r)>>1;
        pushdown(u);
        if(x<=mid)update2(ls[u],l,mid,x,y,k);
        if(y>mid)update2(rs[u],mid+1,r,x,y,k);
        w[u]=min(w[ls[u]],w[rs[u]]);
    }
    inline void build(int &u,int l,int r){
        if(!u)u=++tot;
        w[u]=inf;
        if(l==r)return;
        int mid=(l+r)>>1;
        build(ls[u],l,mid);
        build(rs[u],mid+1,r);
    }
}T2;
int maxnson[N],vis[N],FA[N],sum,rt,dep2[N],tcnt;
cc_hash_table<int,int> dfn2[N],sz2[N];
inline void getrt(int now,int fz){
    maxnson[now]=0;
    sz[now]=1;
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i].to;
        if(to==fz||vis[to])continue;
        getrt(to,now);
        sz[now]+=sz[to];
        maxnson[now]=max(maxnson[now],sz[to]);
    }
    maxnson[now]=max(maxnson[now],sum-sz[now]);
    if(maxnson[now]<maxnson[rt])rt=now;
} 
inline void dfs(int from,int now,int fa){
    dfn2[from][now]=++tcnt;//这里存一下每个点在以from为根的连通块中的dfn序与sz
    sz2[from][now]=1;
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i].to;
        if(to==fa||vis[to])continue;
        dfs(from,to,now);
        sz2[from][now]+=sz2[from][to];
    }
}
inline void solve(int now){
    vis[now]=1;tcnt=0;
    dfs(now,now,0);
    T2.build(T2.rt[now],1,sz2[now][now]);//给这棵线段树全开inf
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i].to;
        if(vis[to])continue;
        rt=0,sum=sz2[now][to];
        getrt(to,now);
        FA[rt]=now;dep2[rt]=dep2[now]+1;//dep2记录每个点在点分树上的深度
        solve(rt);
    }
}
//建点分树

//处理询问
inline int getans(int x){
    int res=inf,temp=x;
    while(temp){
        res=min(res,getdis(temp,x)+T2.w[T2.rt[temp]]/*直接查询点分树上temp子树的最小值*/);
        temp=FA[temp];
    }
    return res;
}
inline void Update(int x,int k){
    int temp=x;
    while(temp){
        int DIS=getdis(x,temp);
        if(k==1)T2.update1(T2.rt[temp],1,sz2[temp][temp],dfn2[temp][x],DIS);
        else if(k==-1)T2.update1(T2.rt[temp],1,sz2[temp][temp],dfn2[temp][x],inf);
        temp=FA[temp];
    }
}
inline void calc(int x,int y,int w){
    int p=x,q=y;
    if(dep2[p]<dep2[q])swap(p,q);
    while(dep2[p]>dep2[q])p=FA[p];
    while(p!=q)p=FA[p],q=FA[q];
    while(p){
        if(dfn2[p][x]<dfn2[p][y])swap(x,y);
        T2.update2(T2.rt[p],1,sz2[p][p],dfn2[p][x],dfn2[p][x]+sz2[p][x]-1,w);//线段树的r别手滑开到n去了
        p=FA[p];
    }
}
int yes[N],tot;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    n=read(),Q=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),w=read();
        e[u].push_back((zyx){v,w});
        e[v].push_back((zyx){u,w});
        edge.push_back((csq){u,v,w});
    }
    dfs1(1,0);dfs2(1,1);//树剖
    for(int i=0;i<n-1;i++){
        int u=edge[i].u,v=edge[i].v,w=edge[i].w;
        if(dep[u]<dep[v])swap(u,v);
        T1.update(1,1,n,dfn[u],w);
    }//下放边权
    rt=0,maxnson[rt]=inf,sum=n;
    getrt(1,0);
    solve(rt);
    for(int i=1;i<=Q;i++){
        int op=read();
        if(op==1){
            int q=read();
            if(tot==0)cout<<"-1\n";
            else cout<<getans(q)<<'\n';
        }
        else if(op==2){
            int u=read();
            if(yes[u]){
                yes[u]=0;
                tot--;
                Update(u,-1);
            }
            else if(!yes[u]){
                yes[u]=1;
                tot++;
                Update(u,1);
            }
        }
        else if(op==3){
            int a=read(),b=read(),w=read();
            if(dep[a]<dep[b])swap(a,b);
            calc(a,b,w-getdis(a,b));
            T1.update(1,1,n,dfn[a],w);
        }
    }
    return 0;
}
```

---

## 作者：Purslane (赞：5)

# Solution

本题即维护一棵树，可以加减关键点，改变边权，求一个点到最近的关键点的距离。

有一个比较显然的点分树 + 线段树 + `multiset` 的做法，但是看起来常数巨大且无脑，复杂度是 $O(n \log^2 n)$ 但是……难写。

**如果强制限制关键点必须在查询点的子树中**，比较简单，开一棵线段树维护**所有关键点的深度**，修改边权的时候区间加减，查询的时候询问区间最小值即可。

对于子树外的点，考虑枚举它和询问点 $u$ 的 LCA，同时进行轻重链剖分，得到下图结构：

![](https://s21.ax1x.com/2024/12/23/pAXRtn1.png)

发现我们需要维护一个点所有轻子树中关键点距离的最小值 $v_i$。（修改一条边，只会对 $O(\log n)$ 个 $v$ 产生修改。）

用线段树维护 $v_i - dep_i$，发现只有单点修改和区间加减，询问区间最小值，能做！

复杂度 $O(n \log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100000+10,INF=0x3f3f3f3f3f3f3f3f;
int n,q,sze[MAXN],son[MAXN],rev[MAXN],fa[MAXN],dep[MAXN],top[MAXN],dfn[MAXN],tot,fval[MAXN];
vector<pair<int,int>> G[MAXN];
void dfs1(int u,int f) {
	fa[u]=f,sze[u]=1;
	for(auto pr:G[u]) {
		int v=pr.first,w=pr.second;
		if(v==f) continue ;
		fval[v]=w,dep[v]=dep[u]+w,dfs1(v,u),sze[u]+=sze[v];
		if(sze[v]>sze[son[u]]) son[u]=v;
	}
	return ;
}
void dfs2(int u) {
	dfn[u]=++tot,rev[tot]=u;
	if(son[u]) top[son[u]]=top[u],dfs2(son[u]);
	for(auto pr:G[u]) {
		int v=pr.first,w=pr.second;
		if(v==fa[u]||v==son[u]) continue ;
		top[v]=v,dfs2(v);
	}
	return ;
}
int tr[MAXN];
void update(int pos,int v) {while(pos<=n) tr[pos]+=v,pos+=pos&-pos;return ;}
int query(int pos) {int ans=0;while(pos) ans+=tr[pos],pos-=pos&-pos;return ans;}
struct SEG {
	vector<int> mn,tag;
	void init(void) {
		return mn.resize(4*n+5),tag.resize(4*n+5),void();
	}
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid (l+r>>1)
	void push_down(int k,int l,int r) {
		return tag[lson]+=tag[k],tag[rson]+=tag[k],mn[lson]+=tag[k],mn[rson]+=tag[k],tag[k]=0,void();	
	}
	void modify(int k,int l,int r,int pos,int v) {
		if(l==r) return mn[k]=v,void();
		push_down(k,l,r);
		if(pos<=mid) modify(lson,l,mid,pos,v);
		else modify(rson,mid+1,r,pos,v);
		return mn[k]=min(mn[lson],mn[rson]),void();
	}
	void update(int k,int l,int r,int x,int y,int v) {
		if(x<=l&&r<=y) return mn[k]+=v,tag[k]+=v,void();
		push_down(k,l,r);
		if(x<=mid) update(lson,l,mid,x,y,v);
		if(y>mid) update(rson,mid+1,r,x,y,v);	
		return mn[k]=min(mn[lson],mn[rson]),void();
	}
	int query(int k,int l,int r,int x,int y) {
		if(x>y) return INF;
		if(x<=l&&r<=y) return mn[k];
		push_down(k,l,r);
		if(y<=mid) return query(lson,l,mid,x,y);
		if(x>mid) return query(rson,mid+1,r,x,y);
		return min(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));	
	}
}s1,s2;
int cnt,flg[MAXN];
int cdep(int u) {return dep[u]+query(dfn[u]);}
int calc(int u,int fbd) {
	if(fbd==0) return s1.query(1,1,n,dfn[u],dfn[u]+sze[u]-1)-cdep(u);
	return min(s1.query(1,1,n,dfn[u],dfn[fbd]-1),s1.query(1,1,n,dfn[fbd]+sze[fbd],dfn[u]+sze[u]-1))-cdep(u);	
}
int Query(int u) {
	if(!cnt) return -1;
	int ou=u,ans=calc(u,0),val=cdep(u);
	while(u) {
		ans=min(ans,s2.query(1,1,n,dfn[top[u]],dfn[u])+val);
		u=top[u];
		if(u!=1) ans=min(ans,calc(fa[u],u)+val-cdep(fa[u])),u=fa[u];
		else break ;
	}
	return ans;
}
void renew(int u) {
	if(!u) return ;
	return s2.modify(1,1,n,dfn[u],calc(u,son[u])-cdep(u)),renew(fa[top[u]]),void();
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n-1) {
		int u,v,w;
		cin>>u>>v>>w;
		G[u].push_back({v,w}),G[v].push_back({u,w});
	}
	dfs1(1,0),top[1]=1,dfs2(1);
	s1.init(),s2.init();
	ffor(i,1,n) s1.modify(1,1,n,i,INF),s2.modify(1,1,n,i,INF);
	ffor(i,1,q) {
		int op;
		cin>>op;
		if(op==2) {
			int u;
			cin>>u;
			if(flg[u]) cnt--,flg[u]=0,s1.modify(1,1,n,dfn[u],INF);
			else cnt++,flg[u]=1,s1.modify(1,1,n,dfn[u],cdep(u));
			renew(u);
		}
		else if(op==1) {
			int u;
			cin>>u,cout<<Query(u)<<'\n';
		}
		else {
			int a,b,w;
			cin>>a>>b>>w;
			if(fa[a]==b) swap(a,b);
			s2.update(1,1,n,dfn[b],dfn[b]+sze[b]-1,fval[b]-w);
			update(dfn[b],w-fval[b]),update(dfn[b]+sze[b],fval[b]-w);
			s1.update(1,1,n,dfn[b],dfn[b]+sze[b]-1,w-fval[b]),fval[b]=w;
			renew(a);
		}
	}
	return 0;
}
```

---

## 作者：Mirasycle (赞：4)

思考一条 $u$ 到关键点 $v$ 的路径，必然是 $u-\operatorname{lca}-v$。考虑枚举 $\operatorname{lca(u,v)}$，那么 $u-\operatorname{lca}$ 这条路径固定了，然后从该公共祖先点往下查询子树关键点深度最小值即可。

可是我们不能暴力枚举 $u$ 的所有祖先，于是可以用重链剖分，每次从 $u$ 往上跳重链进行查询。整合一下思路，我们要开两颗线段树，两个的下标都是 dfs 序。第一颗 $t_1$ 维护每个点深度和区间最小值，这样子我们可以快速得到子树最浅关键点的深度。第二颗线段树 $t_2$ 维护的是每个点**轻子树**的关键点最浅深度减去两倍该点的深度，原因是 $dis=dep_u+dep_v-2\times dep_{\operatorname{lca(u,v)}}$，在 $dep_u$ 固定的情况下我们只需要维护后两项即可。这样子我们每次对于一条重链可以快速得到该重链的答案。因为有修改边权操作，所以直接对于每个点的深度直接开一个维护修改量差分的树状数组即可。

注意上述轻子树的要求，一开始我搞麻烦了。我当时觉得可以直接忽略这个要求，直接维护整个子树不是形式统一更简单吗（毕竟从重子树来的肯定不优，所以算上去也不会影响答案）？但其实这会很麻烦，遇到后续的修改操作，我们跳重链修改的时候，会是一个区间更新，而且对于维护的 $dep_v-2\times dep_{\operatorname{lca(u,v)}}$ 在遇到增加关键点是前半部分有改动，遇到加减边权，前后部分会发生不同程序的变化或者整体一起变，超级麻烦。但是维护轻子树的时候，每次只会在一条重链的一个位置（从下面上来遇到的第一个位置）进行修改，这是一个单点修改很好维护。

同时上述约束下情况维护的是轻子树的答案千万不能带上重儿子，我一开始为了方便，在用子树信息更新 $t_2$ 的时候没有去掉重儿子，导致了答案错误，你可能会想重儿子上来的信息不会让答案更优那为什么会让答案错误呢？因为在修改的时候，我们并不会从重儿子那里上来更新该点的修改，所以这个信息无法被后续修改更新，在后面可能变成错误信息。

现在需要维护一下修改操作，对于加减某个关键点 $s$，直接在深度的线段树上添加/删除该点的信息，然后跳重链用 $dep_s$ 去更新祖先答案即可。

对于修改边权的话，先在树状数组上更新每个点的深度。对下就是子树每个点的深度改变了，因此就是在 $t_1$ 和 $t_2$ 上进行子树加减。对上的影响是会影响到 $t_2$ 上的重链答案，跳重链更新即可。

时间复杂度 $O(n\log^2n)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
const ll inf=0x3f3f3f3f3f3f3f3f;
void cmax(ll &x,ll y){ x=x>y?x:y; }
void cmin(ll &x,ll y){ x=x<y?x:y; }
int n,q; vector<pair<int,int> > G[maxn];
int Is[maxn],upv[maxn],num=0; ll dep[maxn];
struct BIT{
	ll c[maxn];
	void init(){ memset(c,0,sizeof(c)); }
	int lowbit(int x){ return x&-x; }
	void add(int x,ll v){ for(;x<=n;x+=lowbit(x)) c[x]+=v; }
	ll query(int x){ ll res=0; for(;x;x-=lowbit(x)) res+=c[x]; return res; }
}bit;
struct SegmentTree{
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid ((l+r)>>1)
	ll tag[maxn<<2],mn[maxn<<2];
	void pushup(int p){ mn[p]=min(mn[ls],mn[rs]); }
	void init(){ memset(tag,0,sizeof(tag)); memset(mn,inf,sizeof(mn)); }
	void pushdown(int p){
		mn[ls]+=tag[p]; mn[rs]+=tag[p]; 
		tag[ls]+=tag[p]; tag[rs]+=tag[p]; tag[p]=0; 
	}
	void modify(int p,int l,int r,int ql,int qr,ll v){
		if(ql<=l&&r<=qr){ mn[p]+=v; tag[p]+=v; return ; }
		pushdown(p);
		if(ql<=mid) modify(ls,l,mid,ql,qr,v);
		if(qr>mid) modify(rs,mid+1,r,ql,qr,v);
		pushup(p);
	}
	void update(int p,int l,int r,int x,ll v){
		if(l==r){ mn[p]=v; return ; }
		pushdown(p);
		if(x<=mid) update(ls,l,mid,x,v);
		else update(rs,mid+1,r,x,v);
		pushup(p);
	}
	ll query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return mn[p];
		pushdown(p); ll res=inf;
		if(ql<=mid) cmin(res,query(ls,l,mid,ql,qr));
		if(qr>mid) cmin(res,query(rs,mid+1,r,ql,qr)); 	
		return res;
	}
}t1,t2;
struct chain{
	int dfn[maxn],sz[maxn],son[maxn];
	int id[maxn],top[maxn],pa[maxn],tot;
	void dfs(int u,int fa){
		sz[u]=1; pa[u]=fa;
		for(auto z:G[u]){
			int v=z.fi,w=z.se;
			if(v==fa) continue;
			dep[v]=dep[u]+w; upv[v]=w; dfs(v,u);
			sz[u]+=sz[v]; if(sz[son[u]]<sz[v]) son[u]=v;
		}
	}
	void dfs2(int u,int fa,int z){
		top[u]=z; dfn[u]=++tot; id[tot]=u;
		if(son[u]) dfs2(son[u],u,z);
		for(auto z:G[u])
			if(z.fi!=fa&&z.fi!=son[u]) dfs2(z.fi,u,z.fi); 
	}
	ll D(int u){ return dep[u]+bit.query(dfn[u]); }
	ll get(int u,int z){
		if(Is[u]) return -D(u);
		if(z){
			if(sz[son[u]]+1<sz[u]) return t1.query(1,1,n,dfn[u]+sz[son[u]]+1,dfn[u]+sz[u]-1)-2*D(u);
			else return inf;
		}else return t1.query(1,1,n,dfn[u],dfn[u]+sz[u]-1)-2*D(u);
	}
	ll query(int u){
		if(!num) return -1; ll ans=inf; int tmp=u;
		while(u){
			cmin(ans,get(u,0));
			cmin(ans,t2.query(1,1,n,dfn[top[u]],dfn[u]));
			u=pa[top[u]];
		}
		return ans+D(tmp);
	}
	void update(int u){
		while(u){
			t2.update(1,1,n,dfn[u],get(u,1));
			u=pa[top[u]];
		}
	}
}t;
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>q; bit.init(); t.tot=0;
	for(int i=1;i<=n-1;i++){
		int u,v,w; cin>>u>>v>>w;
		G[u].pb(v,w); G[v].pb(u,w);
	}
	t.dfs(1,0); t.dfs2(1,0,1);
	t1.init(); t2.init();
	for(int i=1;i<=q;i++){
		int type,u,v,w; cin>>type>>u;
		if(type==2){
			if(Is[u]) num--,t1.update(1,1,n,t.dfn[u],inf);
			else num++,t1.update(1,1,n,t.dfn[u],t.D(u));
			Is[u]^=1; t.update(u);
		}else if(type==3){
			cin>>v>>w; if(t.dfn[u]>t.dfn[v]) swap(u,v);
			t1.modify(1,1,n,t.dfn[v],t.dfn[v]+t.sz[v]-1,w-upv[v]);
			t2.modify(1,1,n,t.dfn[v],t.dfn[v]+t.sz[v]-1,upv[v]-w);
			bit.add(t.dfn[v],w-upv[v]); bit.add(t.dfn[v]+t.sz[v],upv[v]-w); 
			upv[v]=w; t.update(u);
		}else cout<<t.query(u)<<"\n"; 
	}
	return 0;
}
```

---

## 作者：R_shuffle (赞：1)

我们不妨考虑暴力怎么做，即我们对于一棵边权可修改树，有若干个可以变动的关键点，给出一个点，问距离这个点最近的关键点的距离是多少。考虑朴素做法，我们可以枚举这个点的祖先，然后在最开始遍历整棵树的时候就存每个点的儿子中的关键点的深度，然后把这个点个消掉之后求每个祖先深度最浅的儿子即可。

那么显然暴力的话修改和询问都应该是 $O(n)$ 的复杂度，我们不能接受，考虑其他思路。实际上，我们在往上暴力跳的时候，这样会导致一条边被重复经过很多次，所以考虑减少这个次数，所以不难想到用树链剖分来维护这个过程。

考虑我们在重链上维护什么信息。显然，我们一定会维护一条重链上的点的深度与深度的最小值，这样就能快速更新最小值信息；但是只维护这个显然是少了，再考虑维护一个点的子树内的关键点的深度最小值和自己深度的二倍的差，树上差分可以知道，对于任意一个点，只要确定了一个点作为一条路径两个端点的最近公共祖先，维护了上面的信息就可以确定这个点上的答案了。但是我们发现实际上这样维护会导致我们必须修改一段连续的链的答案，这样问题就又退化成 $O(n)$ 的了，所以考虑借鉴动态 dp，只维护轻儿子的信息，这样就可以只在跳到轻边修改，直接变成 $O(\log n)$ 的了。

那么考虑每种修改怎么做，首先是加入或删除一个关键点，我们直接在深度的信息上加入或删除这个点的信息，具体可以考虑把值变为真实值或极大值。修改边权直接在子树上修改，然后再向上跳重链修改。但是问题就在于深度的真实值，实际上我们可以再开一个线段树维护，这是好做的。时间复杂度 $O(n\log^2n)$，是树剖的正常复杂度。

```cpp
/*胡金梁*/
#include<bits/stdc++.h>
using namespace std;
#define __MY_TEST__ 0
#define int long long
inline int read()
{
	int f=1,re=0;
	char ch=getchar();
	while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar();}
	while( isdigit(ch)) re=(re<<3)+(re<<1)+(ch^'0'),ch=getchar();
	return re*f;
}
const int N=1e5+5;
const long long inf=1e17;
int n,q;
long long dis[N];
int top[N],dfn[N],tot,sze[N],f[N],son[N],fe[N],sum,rev[N];
vector<pair<int,int> >gra[N];
bool fg[N];
struct sgt
{

long long t[N<<2],tag[N<<2];
void build(int num,int l,int r)
{
	if(l==r)
	{
		t[num]=dis[rev[l]];
		return ;
	}
	int mid=(l+r)>>1;
	build(num*2,l,mid);
	build(num*2+1,mid+1,r);
}
void modify(int num,int l,int r,int pl,int pr,int x)
{
	if(l>=pl&&r<=pr)
	{
		tag[num]+=x;
		return ;
	}
	int mid=(l+r)>>1;
	if(pl<=mid) modify(num*2,l,mid,pl,pr,x);
	if(pr>mid) modify(num*2+1,mid+1,r,pl,pr,x);
}
long long query(int num,int l,int r,int pos)
{
	if(l==r) return t[num]+tag[num];
	int mid=(l+r)>>1;
	if(pos<=mid) return query(num*2,l,mid,pos)+tag[num];
	else return query(num*2+1,mid+1,r,pos)+tag[num];
}

}T;
struct SGT
{

long long minn[N<<2],tag[N<<2];
SGT()
{
	for(int i=0;i<(N<<2);i++) minn[i]=inf;
}
void push_up(int num)
{
	minn[num]=min(minn[num*2],minn[num*2+1]);
}
void push_down(int num)
{
	minn[num*2]+=tag[num];
	minn[num*2+1]+=tag[num];
	tag[num*2]+=tag[num];
	tag[num*2+1]+=tag[num];
	tag[num]=0; 
}
void modify(int num,int l,int r,int pl,int pr,long long x)
{
	if(l>=pl&&r<=pr)
	{
		minn[num]+=x;
		tag[num]+=x;
		return ;
	}
	push_down(num);
	int mid=(l+r)>>1;
	if(pl<=mid) modify(num*2,l,mid,pl,pr,x);
	if(pr>mid) modify(num*2+1,mid+1,r,pl,pr,x);
	push_up(num);
}
void modify_val(int num,int l,int r,int pos,long long x)
{
	if(l==r)
	{
		minn[num]=x;
		return ;
	}
	push_down(num);
	int mid=(l+r)>>1;
	if(pos<=mid) modify_val(num*2,l,mid,pos,x);
	else modify_val(num*2+1,mid+1,r,pos,x);
	push_up(num);
}
long long query(int num,int l,int r,int pl,int pr)
{
	if(l>=pl&&r<=pr) return minn[num];
	push_down(num);
	int mid=(l+r)>>1;
	long long re=inf;
	if(pl<=mid) re=min(re,query(num*2,l,mid,pl,pr));
	if(pr>mid) re=min(re,query(num*2+1,mid+1,r,pl,pr));
	return re;
}

}t1,t2;
void dfs(int u,int fa)
{
	f[u]=fa;
	sze[u]=1;
	for(auto x:gra[u])
	{
		int v=x.first,w=x.second;
		if(v==fa) continue;
		dis[v]=dis[u]+w;
		fe[v]=w;
		dfs(v,u);
		sze[u]+=sze[v];
		if(sze[v]>sze[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int tp)
{
	top[u]=tp;
	rev[dfn[u]=++tot]=u;
	if(!son[u]) return ;
	dfs2(son[u],tp);
	for(auto x:gra[u])
	{
		int v=x.first;
		if(v==f[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
long long ask(int u)
{
	if(!sum) return -1;
	long long re=inf;
	int ts=u;
	while(u)
	{
		re=min(re,t2.query(1,1,n,dfn[top[u]],dfn[u]));
		if(fg[u]) re=min(re,-T.query(1,1,n,dfn[u]));
		else re=min(re,t1.query(1,1,n,dfn[u],dfn[u]+sze[u]-1)-2*T.query(1,1,n,dfn[u]));
		u=f[top[u]];
	}
	return re+T.query(1,1,n,dfn[ts]);
}
void change(int u)
{
	while(u)
	{
		if(fg[u])
			t2.modify_val(1,1,n,dfn[u],-T.query(1,1,n,dfn[u]));
		else if(sze[son[u]]+1<sze[u])
			t2.modify_val(1,1,n,dfn[u],t1.query(1,1,n,dfn[u]+sze[son[u]]+1,dfn[u]+sze[u]-1)-2*T.query(1,1,n,dfn[u]));
		else t2.modify_val(1,1,n,dfn[u],inf);
		u=f[top[u]];
	}
}
signed main()
{
#if __MY_TEST__
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	n=read(),q=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read(),w=read();
		gra[u].emplace_back(v,w);
		gra[v].emplace_back(u,w);
	}
	dfs(1,0);
	dfs2(1,1);
	T.build(1,1,n);
	for(int i=1;i<=q;i++)
	{
		int op=read();
		if(op==1)
		{
			cout<<ask(read())<<'\n';
		}
		else if(op==2)
		{
			int u=read();
			if(fg[u])
			{
				sum--;
				t1.modify_val(1,1,n,dfn[u],inf);
				fg[u]=0;
			}
			else
			{
				sum++;
				t1.modify_val(1,1,n,dfn[u],T.query(1,1,n,dfn[u]));
				fg[u]=1;
			}
			change(u);
		}
		else
		{
			int u=read(),v=read(),w=read();
			if(dfn[u]>dfn[v]) swap(u,v);
			t1.modify(1,1,n,dfn[v],dfn[v]+sze[v]-1,w-fe[v]);
			t2.modify(1,1,n,dfn[v],dfn[v]+sze[v]-1,fe[v]-w);
			T.modify(1,1,n,dfn[v],dfn[v]+sze[v]-1,w-fe[v]);
			fe[v]=w;
			change(u);
		}
	}
}

```

---

## 作者：lzyqwq (赞：1)

这种简单题没能一遍胡对，是不是该退役了。

**[P11330 [NOISG 2022 Finals] Grapevine](https://www.luogu.com.cn/problem/P11330)**

> - 给出 $n$ 个点的树，初始所有点都是白色，有 $3$ 种操作共 $q$ 次：
>   - `1 u`：求所有黑点到 $u$ 的距离的最小值。
>   - `2 u`：反转点 $u$ 的颜色。
>   - `3 u v w`：将连接 $u,v$ 的边权值改为 $w$。
> - $n,q\le 10^5$。

考虑两点树上距离 $\text{dis}(u,v)=\text{dep}_u+\text{dep}_v-2\text{dep}_{\text{LCA}(u,v)}$。那么首先暴力地考虑枚举 $\text{LCA}(u,v)$。

当 $\text{LCA}(u,v)=u$ 时，只需要选取子树内深度最小的点即可。

否则，考虑 $u$ 根链 $1\rightsquigarrow \text{fa}_u$ 上的一个点 $p$ 作为 $\text{LCA}(u,v)$，则 $v$ 必须在 $p$ 子树内且不在 $p$ 在 $1\rightsquigarrow u$ 路径上的子节点 $\text{son}_p$ 的子树中。此时只需要求这个区域内 $\text{dep}_v-2\text{dep}_p$ 的最小值。

考虑重剖，则 $1\rightsquigarrow u$ 上只有 $\mathcal{O}(\log n)$ 条轻边。则对于路径上这些边没有覆盖的点 $p$，$\text{son}_p$ 都是 $p$ 的重儿子。记 $f_p$ 表示在 $p$ 子树中且不在 $p$ 重儿子子树中的黑点 $v$ 的 $\text{dep}_v-2\text{dep}_p$ 的最小值。那么对于根链上的每一条重链，她有一部分贡献就是除去底端的一段前缀，在 $\text{dfn}$ 序上也是一段区间。

对于重链底端的点，只有 $\mathcal{O}(\log n)$ 个，并且一定是一条重链顶端的父亲 $\text{fa}$。那么对于每一条重链，计算在她顶端的父亲子树中且不在她顶端子树中的区域内的黑点 $v$ 的 $\text{dep}_v$ 的最小值。贡献就是 $\text{dep}_u+\text{dep}_v-2\text{dep}_{\text{fa}}$。

至此，跳链时的所有查询都能被表示成 $\mathcal{O}(1)$ 个 $\text{dfn}$ 上的区间的并。由于有修改还要区间查询，考虑线段树维护。

由于仅查询黑点的信息，因此维护的时候，对于黑点就维护她的 $\text{dep}$，对于白点维护她的深度加上 $\inf$。记处理过后的深度为 $D$，和真实深度 $\text{dep}$ 区分。那么 $f_p$ 就变成对应区域内 $D_v-2\text{dep}_p$ 的最小值。

对于 `2 u` 操作，相当于对 $D_u$ 加或减 $\inf$。还要考虑哪些 $f_p$ 会发生变化，显然 $p$ 满足：

- $u$ 在 $p$ 的子树中。
- $u$ 不在 $p$ 重儿子的子树中。

那么 $p$ 只能是 $1\rightsquigarrow u$ 上轻边连接的深度较小的结点。这样的 $p$ 只有 $\mathcal{O}(\log n)$ 个，直接暴力跳链然后重新计算即可。

对于 `3 u v w` 操作，不妨记 $u$ 为较深的结点。假设这条边权值增加了 $k$。考虑她对 $D,\text{dep},f$ 分别有什么影响：

- $D,\text{dep}$：$u$ 子树内的点的信息都要加 $k$。
- $f$：$u$ 子树内的点 $\text{dep}$ 值会发生变化，考虑哪些 $p$ 会用到这些变化的值。
  - **口胡时没考虑到的地方**：对于 $u$ 子树内的点 $p$，其子树内黑点 $v$ 和 $p$ 的 $\text{dep}$ 都要 **加 $k$**。结合式子发现每个点的新贡献都变成原来的贡献减 $k$，那么肯定仍然选择先前选的点，对应的子树内的所有 $f_p$ 减 $k$，转化成 $\text{dfn}$ 序后是区间加。
  - 对于 $1\rightsquigarrow \text{fa}_u$ 上的点，和上面只有 $\mathcal{O}(\log n)$ 个点的 $f$ 会用到 $u$ 子树内的黑点，对于这些点暴力重新计算即可。
  - 对于剩下的点，其子树内部一点不存在 $u$ 子树内的点，不用考虑。

那么基本做完了。最后整理一下，因为实现和思路有一些小出入：

- 用线段树维护 $D,f$。维护 $f$ 理论上比 $D$ 多一个单点修改，但我不想写两个线段树，所以在代码中先查询一遍原来的值，然后加上增量。
- 由于重新计算 $f$ 和求答案的时候需要用到单点 $\text{dep}_u$，而修改是 `3 u v w` 操作的区间加，因此用树状数组维护。
- 用 `map` 存每一时刻的边权。用一个数组记录每个点的颜色。

[AC Link](https://www.luogu.com.cn/record/191462216) / [Code](https://www.luogu.com.cn/paste/bdo9zmi2)

---

