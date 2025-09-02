# Qtree1

## 题目背景

**数据规模和 spoj 上有所不同**。

## 题目描述

给定一棵 $n$ 个节点的树，有两种操作：  
- `CHANGE i t` 把第 $i$ 条边的边权变成 $t$  
- `QUERY a b` 输出从 $a$ 到 $b$ 的路径上最大的边权。当 $a=b$ 时，输出 $0$  

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 10^5$。
- $1 \leq u, v, a, b \leq n$，$1 \leq x < n$。
- $1 \leq w, t \leq 2^{31} - 1$。
- 操作次数不大于 $3 \times 10^5$。

## 样例 #1

### 输入

```
3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE```

### 输出

```
1
3```

# 题解

## 作者：NaCly_Fish (赞：28)

第一次写边权树剖的题目，写篇题解造(bao)福(fu)社会

这题要搞的是对边权的操作，不是点权，怎么搞？  我们注意到一棵$n$个节点的树，有$n-1$个节点(废话)，且每个节点只有**唯一**的父节点。  
那就可以考虑把$u$到其父节点$v$的边权，转移到$u$上存储，这样就可以开开心心的树剖了。   
对于权值的转移，在树剖的第一遍dfs时就能搞定。 

另外，这里要求$u$到$v$节点之间所有**边**的最大权值，不是点。  
不难发现：对于$\text{lca}(u,v)$记录的边权，是不在$u$到$v$的路径上的。所以在计算最大值时，自然不能算进这个节点。   
搞树上路径查询的时候，我们是这样做的：  
$u$和$v$节点不断地跳到其重链顶端，直到一条重链为止。  

此时，若假设$u$比$v$的深度小，那么显然$\text{lca}(u,v)=u$。这个$u$节点时不能算进答案里的，要避开它，我们可以根据树剖的性质：  
>同一条重链上的节点编号连续  

所以在最后一步查询的时候，$\text{query}(\text{id}[u]+1,\text{id}[v])$就行了，因为比$u$的编号大$1$的节点，一定是它的儿子。如此一来，就不会将$\text{lca}$算入结果了。 

是不是很简单啊？  
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<ctime>
#define N 100003
#define inf 0x3f3f3f3f
#define ll long long
#define ls(u) (u<<1)
#define rs(u) (u<<1|1)
#define mid ((l+r)>>1)
using namespace std;

struct edge{
    int u,v,w;
    edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
};

int wl[N],son[N],size[N],top[N],b[N],id[N];
int a[N<<2],tag[N<<2],depth[N],fa[N],mx[N<<2];
edge e[N];
int n,m,r,cnt;
vector<edge> adj[N];

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)){
        x = (x<<3)+(x<<1)+c-'0';
        c = getchar();
    }
}

void print(int x){
    if(x>9) print(x/10);
    putchar(x%10+'0');
}

inline int max(int a,int b){
    return a>b?a:b;
}

//以下为线段树

inline void push_up(int u){
    a[u] = a[ls(u)]+a[rs(u)];
    mx[u] = max(mx[ls(u)],mx[rs(u)]);
}

void build(int u,int l,int r){
    if(l==r){
        a[u] = mx[u] = wl[l];
        return;
    }
    build(ls(u),l,mid);
    build(rs(u),mid+1,r);
    push_up(u);
}

void update(int u,int l,int r,int q,int k){
    if(l==r){
        a[u] = mx[u] = k;
        return;
    }
    if(q<=mid) update(ls(u),l,mid,q,k);
    else update(rs(u),mid+1,r,q,k);
    push_up(u);
}

int qaq(int nl,int nr,int l,int r,int u){
    int res = -inf;
    if(nl<=l&&r<=nr) return mx[u];
    if(nl<=mid) res = max(res,qaq(nl,nr,l,mid,ls(u)));
    if(nr>mid) res = max(res,qaq(nl,nr,mid+1,r,rs(u)));
    push_up(u);
    return res;
}

inline int qmax(int l,int r){
    return qaq(l,r,1,n,1);
}

//以上为线段树

void dfs1(int u,int f){
    fa[u] = f;
    depth[u] = depth[f]+1;
    size[u] = 1;
    int v,t = -1,l = adj[u].size();
    for(int i=0;i<l;++i){
        v = adj[u][i].v;
        if(v==f){
            b[u] = adj[u][i].w;
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
    top[u] = f;
    id[u] = ++cnt;
    wl[cnt] = b[u];
    if(son[u]==0) return;
    dfs2(son[u],f);
    int v,l = adj[u].size();
    for(int i=0;i<l;++i){
        v = adj[u][i].v;
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}

int pathMax(int u,int v){
    int res = -inf;
    while(top[u]!=top[v]){
        if(depth[top[u]]<depth[top[v]])
            swap(u,v);
        res = max(res,qmax(id[top[u]],id[u]));
        u = fa[top[u]];
    }
    if(depth[u]>depth[v]) swap(u,v);
    res = max(res,qmax(id[u]+1,id[v])); //上面提到的避开lca的方法
    return res;
}

int main(){
    int u,v,w,q;
    string str;
    read(n);
    for(int i=1;i<n;++i){
        read(u),read(v),read(w);
        adj[u].push_back(edge(u,v,w));
        adj[v].push_back(edge(v,u,w));
        e[i] = edge(u,v,w);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    string op;
    while(1){
        op = "";
        char c = getchar();
        while(c<'A'||c>'Z') c = getchar();
        while(c>='A'&&c<='Z'){
            op.push_back(c);
            c = getchar();
        }
        if(op=="DONE") break;
        read(u),read(v);
        if(op=="QUERY"){
            if(u==v) putchar('0');
            else print(pathMax(u,v));
            putchar('\n');
        }else{
            if(depth[e[u].u]>depth[e[u].v]) u = e[u].u;
            else u = e[u].v;
            update(1,1,n,id[u],v);
        }
    }
    return 0;
}
```


---

## 作者：Siyuan (赞：25)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[Luogu 4114](https://www.luogu.org/problemnew/solution/P4114)

给定一棵 $n$ 个节点的树，边按照输入顺序编号为 $1\sim n-1$，每条边都有一个权值 $w_i$ 需要对这棵树进行若干次操作，操作分为 $2$ 种：

- `CHANGE i t`：将第 $i$ 条边的权值 $w_i$ 修改为 $t$
- `QUERY a b`：询问从节点 $a$ 到 $b$ 的路径上的边权最大值。

询问以 `DONE` 结束。

数据范围：$n\le10^5$，$\texttt{询问次数}\le 3\times 10^5$，$w_i,t\le 2^{31}-1$

------

## Solution

对于这类树的题目，我们首先可以想到用**树链剖分**维护。而这题需要维护的边的信息，那么我们可以把每条边的信息放在较深的节点上，就转化成了维护点的信息了。

但是这样做需要注意一个问题：每次查询时，$\texttt{LCA}$ 的节点维护的信息是它上方的边，因此这个点不能被查询到。如何解决？我们根据树剖的性质可以发现以下方法：记 $x$ 的 $\texttt{DFS}$ 序为 $d_x$，那么最后查询 $u,v$ 的信息时（这里令 $u$ 的深度比 $v$ 浅），我们可以发现 $u$ 一定是 $\texttt{LCA}$，所以只要查询 $d_u+1,d_v$ 就可以避开 $\texttt{LCA}$ 了。

**时间复杂度**：$O(n\log^2 n)$（这里认为操作次数和 $n$ 同阶）

------

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lson rt<<1
#define rson rt<<1|1
inline char nc() {
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template <class Tp> inline void read(register Tp &s) {
    s=0;
    register bool neg=0;
    register char c=nc();
    for(;c<'0'||c>'9';c=nc()) neg|=(c=='-');
    for(;c>='0'&&c<='9';s=s*10+(c^48),c=nc());
    s=(neg?-s:s);
}

const int N=1e5+5,M=2e5+5;
int n,idx,dfn[N],seq[N],U[N],V[N],W[N],val[N],fa[N],dep[N],top[N],sz[N],hvy[N];
int tot,lnk[N],ter[M],nxt[M],wei[M],seg[N<<2];

void add(int u,int v,int w) {
    ter[++tot]=v,wei[tot]=w,nxt[tot]=lnk[u],lnk[u]=tot;
}
void dfs1(int u,int f) {
    fa[u]=f,dep[u]=dep[f]+1,sz[u]=1,hvy[u]=top[u]=0;
    for(int i=lnk[u];i;i=nxt[i]) {
        int v=ter[i];
        if(v==f) continue;
        val[v]=wei[i];
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[hvy[u]]<sz[v]) hvy[u]=v;
    }
}
void dfs2(int u,int tp) {
    dfn[u]=++idx,seq[idx]=u,top[u]=tp;
    if(!hvy[u]) return;
    dfs2(hvy[u],tp);
    for(int i=lnk[u];i;i=nxt[i]) {
        int v=ter[i];
        if(v==fa[u]||v==hvy[u]) continue;
        dfs2(v,v);
    }
}
void pushup(int rt) {
    seg[rt]=std::max(seg[lson],seg[rson]);
}
void build(int rt,int l,int r) {
    if(l==r) {
        seg[rt]=val[seq[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(rt);
}
void modify(int x,int rt,int l,int r,int val) {
    if(l==r) {
        seg[rt]=val;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) modify(x,lson,l,mid,val);
    else modify(x,rson,mid+1,r,val);
    pushup(rt);
}
int query(int x,int y,int rt,int l,int r) {
    if(x>y) return 0;
    if(x<=l&&r<=y) return seg[rt];
    int mid=(l+r)>>1,res=0;
    if(x<=mid) res=std::max(res,query(x,y,lson,l,mid));
    if(mid<y) res=std::max(res,query(x,y,rson,mid+1,r));
    return res;
}
int chainQuery(int u,int v) {
    if(u==v) return 0;
    int res=0;
    for(int fu=top[u],fv=top[v];fu^fv;u=fa[fu],fu=top[u]) {
        if(dep[fu]<dep[fv]) std::swap(u,v),std::swap(fu,fv);
        res=std::max(res,query(dfn[fu],dfn[u],1,1,n));
    }
    if(dep[u]>dep[v]) std::swap(u,v);
    res=std::max(res,query(dfn[u]+1,dfn[v],1,1,n));
    return res;
}
int main() {
    read(n);
    for(int i=1;i<n;++i) {
        int u,v,w;
        read(u),read(v),read(w);
        add(u,v,w),add(v,u,w);
        U[i]=u,V[i]=v,W[i]=w;
    }
    dfs1(1,0),dfs2(1,1),build(1,1,n);
    while(1) {
        char c=nc();
        while(c<'A'||c>'Z') c=nc();
        if(c=='D') break;
        int x,y;
        read(x),read(y);
        if(c=='C') {
            int u=U[x],v=V[x];
            if(fa[v]==u) std::swap(u,v);
            modify(dfn[u],1,1,n,y);
        } else {
            printf("%d\n",chainQuery(x,y));
        }
    }
    return 0;
}
```



---

## 作者：hhoppitree (赞：19)

### 题意简述：  
给定一棵 $n$ 个节点的树，有两种操作：

- ```CHANGE x t``` 把第 $x$ 条边的边权变成 $t$
- ```QUERY a b``` 输出从 $a$ 到 $b$ 的路径上最大的边权。当 $a=b$ 时，输出 $0$  

### 题目解法：  
由于这道题是在树上进行修改与查询，且树的形态未发生改变，所以我们考虑使用树链剖分来解决这道题。  
由于这道题的修改在边上，而树链剖分适用于关于点的修改，所以需要标记下传。  
但是这样会有一个问题，就是查询时若设 $a$ 和 $b$ 的 LCA 为 $l$，则我们进行统计时不能统计到 $l$，反之可以被如下数据卡掉。  
```
4
1 2 10000
2 3 1
2 4 1
QUERY 3 4
DONE
```
标准输出为 ```1```，而错误解法的输出为 ```10000```。  
如何解决这个问题呢？根据树链剖分的性质，有若 $top_a=top_b$，且 $b$ 为 $a$ 的祖先，则路径 $[a,b)$ 在线段树上的投影为 $[seg_b+1,seg_a]$。  
### 正确代码：  
~~燃鹅我傻X了还开了一堆辅助数组，又把上行下行分开考虑，所以代码基本不可读。~~  
```cpp
#include<bits/stdc++.h>  
#define mp(x,y) make_pair(x,y)
using namespace std;
inline int read(){
	int res=0;
	bool zf=0;
	char c;
	while(((c=getchar())<'0'||c>'9')&&c!='-');
	if(c=='-')zf=1;
	else res=c-'0';
	while((c=getchar())>='0'&&c<='9')res=(res<<3)+(res<<1)+c-'0';
	return (zf?-res:res);
}
const int maxn=100000+5;
typedef pair<pair<int,int>,int>P;
vector<P>G[maxn];
int n;
int dep[maxn],fa[maxn],size[maxn],son[maxn],wh[maxn],top[maxn],seg[maxn],ysb[maxn],cnt;
int dta[maxn],Max[maxn<<2];
void build(int k,int l,int r){
	if(l==r){
		Max[k]=dta[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	Max[k]=max(Max[k<<1],Max[k<<1|1]);
	return;
}
void modify(int k,int l,int r,int pos,int val){
	if(l>pos||r<pos){
		return;
	}
	if(l==r){
		Max[k]=val;
		return;
	}
	int mid=(l+r)>>1;
	modify(k<<1,l,mid,pos,val);
	modify(k<<1|1,mid+1,r,pos,val);
	Max[k]=max(Max[k<<1],Max[k<<1|1]);
	return;
}
int query(int k,int l,int r,int x,int y){
	if(l>y||r<x)return 0;
	if(l>=x&&r<=y){
		return Max[k];
	}
	int mid=(l+r)>>1;
	return max(query(k<<1,l,mid,x,y),query(k<<1|1,mid+1,r,x,y));
}
void dfs1(int now){
	size[now]=1;
	for(register int i=0;i<G[now].size();++i){
		int v=G[now][i].second;
		if(dep[v])continue;
		dep[v]=dep[now]+1;
		fa[v]=now;
		ysb[G[now][i].first.second]=v;
		dfs1(v);
		size[now]+=size[v];
		if(size[v]>size[son[now]]){
			son[now]=v;
			wh[now]=i;
		}
	} 
	return;
}
void dfs2(int now,int val=-1){
	seg[now]=(++cnt);
	if(~val){
		dta[seg[now]]=val;
	}
	if(!son[now])return;
	int v=son[now];
	top[v]=top[now];
	dfs2(v,G[now][wh[now]].first.first);
	for(register int i=0;i<G[now].size();++i){
		int v=G[now][i].second;
		if(v==fa[now]||v==son[now])continue;
		dfs2(top[v]=v,G[now][i].first.first);
	}
	return;
}
inline int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]){
			swap(x,y);
		}
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]){
		swap(x,y);
	}
	return x;
}
inline int ask(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		ans=max(ans,query(1,1,n,seg[top[x]],seg[x]));
		x=fa[top[x]]; 
	}
	ans=max(ans,query(1,1,n,seg[y]+1,seg[x]));
	return ans;
}
signed main(){
	n=read();
	for(register int i=1;i<n;++i){
		int x=read(),y=read(),z=read();
		G[x].push_back(mp(mp(z,i),y)),
		G[y].push_back(mp(mp(z,i),x));
	}
	dfs1(dep[1]=1);
	dfs2(top[1]=1);
	build(1,1,n);
	string s;cin>>s;
	while(s!="DONE"){
		if(s=="CHANGE"){
			int pos=read(),val=read();
			modify(1,1,n,seg[ysb[pos]],val);
		}
		else{
			int x=read(),y=read();
			if(x==y){
				puts("0");
			}
			else{
				int lca=LCA(x,y);
				printf("%d\n",max(ask(x,lca),ask(y,lca)));
			}
		}
		cin>>s;
	}
	return 0;
}
```
如果您没有看懂这篇题解，可以在评论区问我，我将会回答您的问题并且修改这篇题解，使它变得更加通俗易懂，服务更多的 $\text{OIer}$。  
如果您看懂了这篇题解，可以点个赞，使这篇题解的排名上升，服务更多的 $\text{OIer}$。  

---

## 作者：King丨帝御威 (赞：8)

读完题目之后……诶，这不是树链剖分裸题么？？！！

然后……代码写到一半忽然发现是边权……而普通的树链剖分是点权，如果是点权的话，那这道题就是一个裸题了吧。然后，我们可以发现，一个点连向它父亲的边有且只有一个，即一个点只有一个父亲，那么我们就可以用它的点权来代替它与它父亲之间的那条边的边权，然后，就成了一个裸题了……

还有要注意的一点就是，区间查询的时候不要把LCA算上，因为它的点权代表它与它父亲的边权，不在查询的路径上。

具体实现看代码：

```
#include<cstdio>
#include<algorithm>
#include<cctype>
#define maxn 100007
#define ll long long
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
int n,head[maxn],d[maxn],size[maxn],son[maxn],a[maxn],lazy[maxn<<2];
int p[maxn],id[maxn],top[maxn],num,cnt,fa[maxn],maxx[maxn<<2];
char s[10];
inline int qread() {
  char c=getchar();int num=0,f=1;
  for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
  for(;isdigit(c);c=getchar()) num=num*10+c-'0';
  return num*f;
}
struct node {
  int v,w,nxt;
}e[maxn<<1];
inline void ct(int u, int v, int w) {
  e[++num].v=v;
  e[num].w=w;
  e[num].nxt=head[u];
  head[u]=num;
}
inline void pushup(int rt) {
  maxx[rt]=max(maxx[ls],maxx[rs]);
}
inline void pushdown(int rt) {
  if(lazy[rt]>=0) {
    maxx[ls]=maxx[rs]=lazy[ls]=lazy[rs]=lazy[rt];
    lazy[rt]=-1;
  }
}
void build(int rt, int l, int r) {
  lazy[rt]=-1;
  if(l==r) {
    maxx[rt]=a[l];
    return;
  }
  int mid=(l+r)>>1;
  build(ls,l,mid);
  build(rs,mid+1,r);
  pushup(rt);
}
void modify(int rt, int l, int r, int L, int R, int val) {
  if(L>r||R<l) return;
  if(L<=l&&r<=R) {
    maxx[rt]=lazy[rt]=val;
    return;
  }
  pushdown(rt);
  int mid=(l+r)>>1;
  modify(ls,l,mid,L,R,val),modify(rs,mid+1,r,L,R,val);
  pushup(rt);
}
int cmax(int rt, int l, int r, int L, int R) {
  if(L<=l&&r<=R) return maxx[rt];
  int ans=0;
  int mid=(l+r)>>1;
  pushdown(rt);
  if(L<=mid) ans=max(ans,cmax(ls,l,mid,L,R));
  if(R>mid) ans=max(ans,cmax(rs,mid+1,r,L,R));
  return ans;
}
void dfs1(int u, int f) {
  size[u]=1;
  for(int i=head[u];i;i=e[i].nxt) {
    int v=e[i].v;
    if(v!=f) {
      d[v]=d[u]+1;
      fa[v]=u;
      p[v]=e[i].w;             //换边权为点权。
      dfs1(v,u);
      size[u]+=size[v];
      if(size[v]>size[son[u]]) son[u]=v;
    }
  }
}
void dfs2(int u, int t) {
  id[u]=++cnt;
  top[u]=t;
  a[cnt]=p[u];
  if(son[u]) dfs2(son[u],t);
  for(int i=head[u];i;i=e[i].nxt) {
    int v=e[i].v;
    if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
  }
}
int query(int x, int y) {
  int ans=0,fx=top[x],fy=top[y];
  while(fx!=fy) {
    if(d[fx]<d[fy]) swap(x,y),swap(fx,fy);
    ans=max(ans,cmax(1,1,n,id[fx],id[x]));
    x=fa[fx],fx=top[x];
  }
  if(id[x]>id[y]) swap(x,y);
  ans=max(ans,cmax(1,1,n,id[x]+1,id[y]));
  return ans;
}
int main() {
  n=qread();
  for(int i=1,u,v,w;i<n;++i) {
    u=qread(),v=qread(),w=qread();
    ct(u,v,w);ct(v,u,w);
  }
  dfs1(1,0),dfs2(1,1);build(1,1,n);
  while(1) {
    scanf("%s",s);
    if(s[0]=='D') break;
    int x=qread(),y=qread();
    if(s[0]=='Q') {
      if(x==y) printf("0\n");
      else printf("%d\n",query(x,y));
	}
	if(s[0]=='C') {
	  x=d[e[x*2-1].v]<d[e[x<<1].v]?e[x<<1].v:e[x*2-1].v;
      modify(1,1,n,id[x],id[x],y);
	}
  }
  return 0;
}
```
希望这篇题解对大家能有所帮助。

---

## 作者：pipiispig (赞：7)

#
本篇题解不是树链剖分
#
所有的树剖都可以用lct做，并且更方便，快捷！
很多操作没有用到， 因为这个树是固定形态的， 自己看代码吧！
```
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
	return x * f;
}
const int N = 200005;
int ch[N][2], fa[N], rev[N], val[N], v[N];
inline bool chk(int x) {return ch[fa[x]][1] == x;}
inline bool get(int x) {return ch[fa[x]][1] == x || ch[fa[x]][0] == x;}
inline void Rev(int x) {rev[x] ^= 1; swap(ch[x][0], ch[x][1]);}
inline void pushup(int x) {val[x] = max(max(val[ch[x][0]], val[ch[x][1]]), v[x]);}
inline void pushdown(int x) {
	if(rev[x]) {
		if(ch[x][0]) Rev(ch[x][0]);
		if(ch[x][1]) Rev(ch[x][1]);
		rev[x] = 0;
	}
}
inline void rotate(int x) {
	int y = fa[x], z = fa[y], k = chk(x), v = ch[x][k ^ 1];
	if(get(y)) ch[z][chk(y)] = x; ch[y][k] = v; ch[x][k ^ 1] = y;
	if(v) fa[v] = y; fa[x] = z; fa[y] = x;
	pushup(y);pushup(x);
}
int hep[N];
inline void splay(int x) {
	int top = 0, y = x;
	hep[++ top] = y;
	while(get(y)) hep[++ top] = y = fa[y];
	while(top) pushdown(hep[top --]);
	while(get(x)) {
		y = fa[x];
		if(get(y)) chk(x) == chk(y) ? rotate(y) : rotate(x);
		rotate(x); 
	}
	pushup(x);
}
inline void access(int x) {for(int y = 0; x; x = fa[y = x]) splay(x), ch[x][1] = y, pushup(x);}
inline void makeroot(int x) {access(x); splay(x); Rev(x);}
inline int findroot(int x) {access(x); splay(x); while(ch[x][0]) pushdown(x), x = ch[x][0]; return x;}
inline void split(int x, int y) {makeroot(x); access(y); splay(y);}
inline void link(int x, int y) {makeroot(x); if(findroot(y) != x) fa[x] = y;}
inline void cut(int x, int y) {split(x, y); if(findroot(y) == x && fa[x] == y && !ch[x][1]) fa[x] = ch[y][0] = 0, pushup(y);}
int n;
char a[10];
int main() {
	n = read();
	for(int i = 1; i < n; i ++) {
		int x = read(), y = read(), z = read();
		v[i + n] = z;
		link(x, i + n); link(i + n, y); 
	}
	while(true) {
		scanf("%s", a); 
		if(a[0] == 'D') break;
		if(a[0] == 'Q') {int x = read(), y = read();split(x, y);printf("%d\n", val[y]);}
		if(a[0] == 'C') {int x = read() + n, y = read(); access(x); splay(x); v[x] = y;}
	}
	return 0;
}
```

---

## 作者：流逝丶 (赞：6)

~~这不就是个树剖裸题么~~

树剖一下，然后用线段树维护区间最大值

每次是单点修改

这道题的难点在于边权怎么处理

我们可以在两点连的边之间新建一个节点，把边的权值赋给它，对于原树上的节点为了不影响赋成-inf

然后这题就做完了

```cpp
#include<iostream>
#include<cstdio>
#define mid ((l+r)>>1)
#define lson k<<1,l,mid
#define rson k<<1|1,mid+1,r
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int N=100005,inf=1e9;
int n,cnt,tot;
int head[N<<1],siz[N<<1],top[N<<1],fa[N<<1],dep[N<<1],son[N<<1],id[N<<1],vl[N<<1],val[N<<1];
int tr[N<<3];
struct node{
	int to,nxt;
}e[N<<2];
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline void add(int from,int to){
	e[++cnt]=(node){to,head[from]};
	head[from]=cnt;
}
void dfs1(int x,int f,int deep){
	fa[x]=f;siz[x]=1;dep[x]=deep;
	int maxson=-1;
	for(int i=head[x];i;i=e[i].nxt)
		if(e[i].to!=f){
			dfs1(e[i].to,x,deep+1);
			siz[x]+=siz[e[i].to];
			if(siz[e[i].to]>maxson)son[x]=e[i].to,maxson=siz[e[i].to];
		}
}
void dfs2(int x,int topf){
	id[x]=++tot;val[tot]=vl[x];top[x]=topf;
	if(!son[x])return ;
	dfs2(son[x],topf);
	for(int i=head[x];i;i=e[i].nxt){
		if(e[i].to==fa[x]||e[i].to==son[x])continue;
		dfs2(e[i].to,e[i].to);
	}
}
inline void update(int k){
	tr[k]=max(tr[ls],tr[rs]);
}
void change(int k,int l,int r,int x,int y){
	if(l==r&&l==x){
		tr[k]=y;
		return ;
	}
	if(x<=mid)change(lson,x,y);
	else change(rson,x,y);
	update(k);
}
int ask(int k,int l,int r,int x,int y){
	if(l==x&&y==r){
		return tr[k];
	}
	if(y<=mid)return ask(lson,x,y);
	else if(x>mid)return ask(rson,x,y);
	else return max(ask(lson,x,mid),ask(rson,mid+1,y));
}

void build(int k,int l,int r){
	if(l==r){
		tr[k]=val[l];
		return ;
	}
	build(lson);build(rson);
	update(k);
}
int query(int x,int y){
	if(x==y)return 0;
	int ans=-inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		ans=max(ask(1,1,(n<<1)-1,id[top[x]],id[x]),ans);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])x^=y^=x^=y;
	ans=max(ans,ask(1,1,(n<<1)-1,id[y],id[x]));
	return ans;
}
int main(){
	n=read();
	int x,y;
	for(int i=1;i<n;++i){
		x=read();y=read();
		add(x,i+n);add(i+n,x);
		add(y,i+n);add(i+n,y);
		vl[i+n]=read();vl[x]=vl[y]=-inf;
	}
	dfs1(1,0,1);
	dfs2(1,1);
	build(1,1,(n<<1)-1);
	char c[10];
	while(1){
		scanf("%s",c+1);
		if(c[1]=='D')return 0;
		x=read();y=read();
		if(c[1]=='Q')printf("%d\n",query(x,y));
		else change(1,1,(n<<1)-1,id[x+n],y);
	}
}
```


---

## 作者：Treaker (赞：3)

本道题可以用树剖来做。

我们将边权转化为点权。具体做法为把边权赋给这条边的儿子节点（应该不难理解）。

对于change操作，我可以记录一下每条边，然后给儿子节点变一下值即可。

对于query操作，求max即可。

操作时，最后要dfn[y] + 1；
```cpp
#include <iostream>
#include <cstdio>
#define mid ((p -> l + p -> r) >> 1)
const int N = 300100;
int n , cnt;
int u[N] , v[N] , w[N] , dfn[N] , id[N] , head[N] , dep[N] , fa[N] , size[N] , hs[N] , top[N] , a[N];
char s[10];
struct Edge {int to , nxt , dis;}e[N << 1];
void add(int from,int to,int dis)
{
	e[++cnt] = (Edge) {to , head[from] , dis};
	head[from] = cnt;
}
void get_tree(int now)
{
	size[now] = 1;
	for(int i = head[now];i;i = e[i].nxt)
	{
		int to = e[i].to;
		if(dep[to])	continue;
		dep[to] = dep[now] + 1;
		fa[to] = now;
		a[to] = e[i].dis;
		get_tree(to);
		size[now] += size[to];
		if(size[to] > size[hs[now]])	hs[now] = to;
	}
}
void dfs(int now,int topfa)
{
	top[now] = topfa;
	dfn[now] = ++cnt;
	id[cnt] = now;
	if(hs[now])	dfs(hs[now],topfa);
	for(int i = head[now];i;i = e[i].nxt)
	{
		int to = e[i].to;
		if(to == fa[now] || to == hs[now])	continue;
		dfs(to,to);
	}
}
struct LOL
{
	struct node
	{
		node *ls , *rs;
		int l , r, maxn;
		node (int l , int r , int maxn) : l(l) , r(r) , maxn(maxn){ls = rs = NULL;}
		inline int len() {return r - l + 1;}
		inline void push_up() {maxn = std::max(ls -> maxn , rs -> maxn);}
	}*root;
	void build(node *&p,int l,int r)
	{
		p = new node(l,r,0);
		if(l == r)	return (void)(p -> maxn = a[id[l]]);
		build(p -> ls,l,mid);
		build(p -> rs,mid+1,r);
		p -> push_up();
	}
	void chenge(node *p,int x,int k)
	{
		if(p -> l == p -> r)	return (void)(p -> maxn = k);
		if(x <= mid) chenge(p -> ls,x,k);
		else chenge(p -> rs,x,k);
		p -> push_up();
	}
	int query(node *p,int x,int y)
	{
		if(x <= p -> l && p -> r <= y)	return p -> maxn;
		int res = 0;
		if(x <= mid)	res = std::max(res,query(p -> ls,x,y));
		if(y > mid)		res = std::max(res,query(p -> rs,x,y));
		return res;
	}
	inline int sec_max(int x,int y)
	{
		int res = 0;
		while(top[x] != top[y])
		{
			if(dep[top[x]] < dep[top[y]])	std::swap(x,y);
			res = std::max(res,query(root,dfn[top[x]],dfn[x]));
			x = fa[top[x]];
		}
		if(dep[x] < dep[y])	std::swap(x,y);
		if(dfn[y] < dfn[x]) res =std::max(res,query(root,dfn[y] + 1,dfn[x]));
		return res;
	}
}cf;
int main()
{
	scanf("%d",&n);
	for(int i = 1;i < n;i ++)
	{
		scanf("%d%d%d",&u[i],&v[i],&w[i]);
		add(u[i],v[i],w[i]);
		add(v[i],u[i],w[i]);
	}
	cnt = 0 , dep[1] = 1;
	get_tree(1);
	dfs(1,1);
	cf.build(cf.root,1,n);
	while(1)
	{
		int x , y;
		scanf("%s",s);
		if(s[0] == 'D')	break;
		if(s[0] == 'Q')	scanf("%d%d",&x,&y) , printf("%d\n",cf.sec_max(x,y));
		else 
		{
			scanf("%d%d",&x,&y);
			if(fa[u[x]] == v[x])	cf.chenge(cf.root,dfn[u[x]],y);
			else cf.chenge(cf.root,dfn[v[x]],y);
		}
	}
	return 0;
}
```


---

## 作者：子谦。 (赞：3)

Qtree系列都跟树有着莫大的联系，这道题当然也不例外

读完题，我们大概就知道了，这道题非常简单，可以说是模板题。树剖+线段树轻松解决

我这里有一篇树剖入门讲解，各位如果有兴趣可以看一看 [树链剖分](https://www.cnblogs.com/hanruyun/p/9577500.html)

代码附讲解

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#define ll long long
#define gc() getchar()
#define maxn 100010
using namespace std;

inline ll read(){     //很朴素的快读，不多解释
    ll a=0;int f=0;char p=gc();
    while(!isdigit(p)){f|=p=='-';p=gc();}
    while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
    return f?-a:a;
}
void write(ll a){     //很朴素的快写，也不多解释
    if(a>9)write(a/10);
    putchar(a%10+'0');
}
int n,a[maxn];    //a数组表示点与父亲连边的长度

int tot,head[maxn];
struct ahaha1{     //前向星存边
    int w,to,next;
}e[maxn<<1];
inline void add(int u,int v,int w){
    e[tot].w=w;e[tot].to=v;e[tot].next=head[u];head[u]=tot++;
}

int f[maxn],sz[maxn],dep[maxn],son[maxn];     //f表示点的父亲，sz表示点的子树上节点个数，dep表示节点的深度，son表示子树最大的子节点
void dfs(int u,int fa){
    int maxa=0;sz[u]=1;
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].to;if(v==fa)continue;
        f[v]=u;dep[v]=dep[u]+1;a[v]=e[i].w;
        dfs(v,u);sz[u]+=sz[v];
        if(sz[v]>maxa)maxa=sz[v],son[u]=v;
    }
}
int b[maxn],in[maxn],top[maxn];    //b表示当前编号所指向的点，in表示点的编号，top表示点所在链的顶端
void dfs(int u,int fa,int topf){
    in[u]=++tot;b[tot]=u;top[u]=topf;
    if(!son[u])return;
    dfs(son[u],u,topf);
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].to;if(v==fa||v==son[u])continue;
        dfs(v,u,v);
    }
}

#define lc p<<1
#define rc p<<1|1
struct ahaha2{     //线段树太简单不解释
    int v;
}t[maxn<<2];
inline void pushup(int p){
    t[p].v=max(t[lc].v,t[rc].v);
}
void build(int p,int l,int r){
    if(l==r){t[p].v=a[b[l]];return;}
    int m=l+r>>1;
    build(lc,l,m);build(rc,m+1,r);
    pushup(p);
}
void update(int p,int l,int r,int L,int z){
    if(l==r){t[p].v=z;return;}
    int m=l+r>>1;
    if(m>=L)update(lc,l,m,L,z);
    else update(rc,m+1,r,L,z);
    pushup(p);
}
int query(int p,int l,int r,int L,int R){
    if(l>R||r<L)return 0;
    if(L<=l&&r<=R)return t[p].v;
    int m=l+r>>1;
    return max(query(lc,l,m,L,R),query(rc,m+1,r,L,R));
}

inline void solve_1(){    //从第0条边开始存，每条边存两次，所以输入的第i条边对应的是第2*i-2和第2*i-1条边，谁是儿子改谁
    int x=read()*2-2,w=read(),u=e[x].to,v=e[x+1].to;
    if(f[v]==u)update(1,1,n,in[v],w);
    else update(1,1,n,in[u],w);
}
inline void solve_2(){      //链上查询
    int x=read(),y=read(),ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        ans=max(ans,query(1,1,n,in[top[x]],in[x]));    //由于存的是与父亲的距离，而top的父亲直接取所以此处无需加1
        x=f[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    ans=max(ans,query(1,1,n,in[x]+1,in[y]));     //但是最后一次存储必须加1否则会多询问一条边
    write(ans);putchar('\n');
}

int main(){memset(head,-1,sizeof head);
    n=read();
    for(int i=1;i<n;++i){
        int x=read(),y=read(),w=read();
        add(x,y,w);add(y,x,w);
    }
    tot=0;dfs(1,-1);dfs(1,-1,1);
    build(1,1,n);
    char z[10];
    while(1){
        scanf("%s",z);
        if(z[0]=='D')break;
        switch(z[0]){
            case 'C':solve_1();break;
            case 'Q':solve_2();break;
        }
    }
    return 0;
}
```



---

## 作者：顾z (赞：2)

# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

裸的树链剖分题.

将边权转为点权要赋给深度较深的点,这样可以保证一个点权对应一个边权.

注意题目中的$a==b$的时候输出$0$，要不就一遍切了 QAQ.

``代码``

```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cctype>
#define int long long 
#define N 100008
#define R register
using namespace std;
inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}
int n,head[N],tot;
struct cod{int u,v,w,fr;}edge[N<<2];
inline void add(int x,int y,int z)
{
	edge[++tot].u=head[x];
	edge[tot].fr=x;
	edge[tot].v=y;
	edge[tot].w=z;
	head[x]=tot;
}
int son[N],size[N],f[N],depth[N],val[N];
char s[108];
void dfs1(int u,int fa,int dis)
{
	f[u]=fa;depth[u]=depth[fa]+1;size[u]=1;val[u]=dis;
	for(R int i=head[u];i;i=edge[i].u)
	{
		if(edge[i].v==fa)continue;
		dfs1(edge[i].v,u,edge[i].w);
		size[u]+=size[edge[i].v];
		if(son[u]==-1 or size[son[u]]<son[edge[i].v])
			son[u]=edge[i].v;
	}
}
int top[N],idx,dfn[N],fdfn[N];
void dfs2(int u,int t)
{
	top[u]=t;dfn[u]=++idx;fdfn[idx]=u;
	if(son[u]==-1)return;
	dfs2(son[u],t);
	for(R int i=head[u];i;i=edge[i].u)
	{
		if(dfn[edge[i].v])continue;
		dfs2(edge[i].v,edge[i].v);
	}
}
int tr[N<<2];
#define ls o<<1
#define rs o<<1|1
inline void up(int o){tr[o]=max(tr[ls],tr[rs]);}
void build(int o,int l,int r)
{
	if(l==r)
	{
		tr[o]=val[fdfn[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	up(o);
}
void change(int o,int l,int r,int pos,int z)
{
	if(l==r){tr[o]=z;return;}
	int mid=(l+r)>>1;
	if(pos<=mid)change(ls,l,mid,pos,z);
	else change(rs,mid+1,r,pos,z);
	up(o);
}
int query(int o,int l,int r,int x,int y)
{
	if(x<=l and y>=r)return tr[o];
	int mid=(l+r)>>1,res=-214748364766LL;
	if(x<=mid)res=max(res,query(ls,l,mid,x,y));
	if(y>mid)res=max(res,query(rs,mid+1,r,x,y));
	return res;
}
inline int tquery(int x,int y)
{
	int fx=top[x],fy=top[y],res=-214748364766LL;
	while(fx!=fy)
	{
		if(depth[fx]>depth[fy])
		{
			res=max(res,query(1,1,n,dfn[fx],dfn[x]));
			x=f[fx];
		}
		else
		{
			res=max(res,query(1,1,n,dfn[fy],dfn[y]));
			y=f[fy];
		}
		fx=top[x],fy=top[y];
	}
	if(x==y)return res;
	if(dfn[x]>dfn[y])swap(x,y);
	res=max(res,query(1,1,n,dfn[x]+1,dfn[y]));
	return res;
}
signed main()
{
	in(n);memset(son,-1,sizeof son);
	for(R int i=1,x,y,z;i<n;i++)
	{
		in(x),in(y),in(z);
		add(x,y,z);add(y,x,z);
	}
	dfs1(1,0,0);dfs2(1,1);
	build(1,1,n);
	for(R int x,y;;)
	{
		scanf("%s",s+1);
		if(s[1]=='D')break;
		if(s[1]=='Q')
		{
			in(x),in(y);
			if(x==y)puts("0");
			else printf("%lld\n",tquery(x,y));
		}
		else
		{
			in(x),in(y);x*=2;
			if(depth[edge[x].v]<depth[edge[x].fr])
				x=edge[x].fr;
			else x=edge[x].v;
			change(1,1,n,dfn[x],y);
		}
	}
}
```

---

## 作者：yu__xuan (赞：1)

### 题目
[P4114 Qtree1](https://www.luogu.com.cn/problem/P4114)
### 思路
树链剖分。这题是边权。因为给的是一棵树，$dfs$ 一遍，每个点之被访问一遍，我们可以当成每个点的入度最多为 $1$，那么对于一条边我们可以把边权给这条边链接的两个点中 $dfs$ 序大的那个点。

在跳链的时候要注意，如果两个点 $x,y$ 在一条链上了,我们只需要查询 $[dfn[x]+1,dfn[y]]$ 这个区间。因为 $dfn[x]$ 这个点的点权为上面那条边的边权。

### Code
```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#define MAXN 100001

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}

int n,dfn[MAXN],pre[MAXN],w[MAXN],size[MAXN];
int u[MAXN],v[MAXN];

int max(int a,int b) {return a>b?a:b;}

namespace Seg {
	#define lson now<<1
	#define rson now<<1|1
	struct Node {
		int l,r,w;
	}tree[MAXN<<2];
	void build(int l,int r,int now) {
		tree[now].l=l,tree[now].r=r;
		if(tree[now].l==tree[now].r) {
			tree[now].w=w[pre[l]];return;
		}
		int mid=(tree[now].l+tree[now].r)>>1;
		build(l,mid,lson),build(mid+1,r,rson);
		tree[now].w=max(tree[lson].w,tree[rson].w);
	}
	void update(int x,int k,int now) {
		if(tree[now].l==tree[now].r) {
			tree[now].w=k;return;
		}
		int mid=(tree[now].l+tree[now].r)>>1;
		if(x<=mid) update(x,k,lson);
		else update(x,k,rson);
		tree[now].w=max(tree[lson].w,tree[rson].w);
	}
	int query(int x,int y,int now) {
		if(tree[now].l>=x&&tree[now].r<=y) return tree[now].w;
		int mid=(tree[now].l+tree[now].r)>>1,ans=0;
		if(x<=mid) ans=max(ans,query(x,y,lson));
		if(y>mid) ans=max(ans,query(x,y,rson));
		return ans;
	}
}

namespace Cut {
	int cnt,pthn,head[MAXN],dep[MAXN];
	int fa[MAXN],son[MAXN],top[MAXN];
	struct Edge {
		int next,to,w;
	}pth[MAXN<<1];
	void add(int from,int to,int w) {
		pth[++pthn].to=to,pth[pthn].next=head[from];
		pth[pthn].w=w,head[from]=pthn;
	}
	void dfs1(int u,int father) {
		fa[u]=father,dep[u]=dep[father]+1,size[u]=1;
		for(int i=head[u];i;i=pth[i].next) {
			int x=pth[i].to;
			if(x!=father) {
				w[x]=pth[i].w,dfs1(x,u),size[u]+=size[x];
				if(size[son[u]]<size[x]) son[u]=x;
			}
		}
	}
	void dfs2(int u,int tp) {
		top[u]=tp,dfn[u]=++cnt,pre[cnt]=u;
		if(son[u]) dfs2(son[u],tp);
		for(int i=head[u];i;i=pth[i].next) {
			int x=pth[i].to;
			if(x!=fa[u]&&x!=son[u]) dfs2(x,x);
		}
	}
	int ask(int x,int y) {
		int ans=0;
		while(top[x]!=top[y]) {
			if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
			ans=max(ans,Seg::query(dfn[top[x]],dfn[x],1));
			x=fa[top[x]];
		}
		if(dep[x]>dep[y]) std::swap(x,y);
		ans=max(ans,Seg::query(dfn[x]+1,dfn[y],1));
		return ans;
	}
}

int main() {
	read(n);
	for(int i=1,w;i<n;++i) {
		read(u[i]),read(v[i]),read(w);
		Cut::add(u[i],v[i],w),Cut::add(v[i],u[i],w);
	}
	Cut::dfs1(1,1),Cut::dfs2(1,1),Seg::build(1,n,1);
	std::string opt;
	while(1) {
		std::cin>>opt;int x,y;
		if(opt=="DONE") break;
		read(x),read(y);
		if(opt=="QUERY") {
			if(x==y) puts("0");
			else printf("%d\n",Cut::ask(x,y));
		}else Seg::update(max(dfn[u[x]],dfn[v[x]]),y,1);
	}
	return 0;
}
```

---

## 作者：MILLOPE (赞：1)

## 题目
给定一棵n个节点的树，有两个操作：

- CHANGE i ti 把第i条边的边权变成ti

- QUERY a b 输出从a到b的路径中最大的边权，当a=b的时候，输出0

输入输出格式
输入格式：
- 第一行输入一个n，表示节点个数

- 第二行到第n行每行输入三个数，ui，vi，wi，分别表示 ui，vi有一条边，边权是wi

- 第n+1行开始，一共有不定数量行，每一行分别有以下三种可能

- CHANGE，QUERY同题意所述

- DONE表示输入结束

输出格式：
- 对于每个QUERY操作，输出一个数，表示a b之间边权最大值

输入输出样例
输入样例#1： 
```cpp
3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE
```
输出样例#1： 
```cpp
1
3
```

[提交地址](https://www.luogu.org/problemnew/show/P4114)

## 题解
- emmm这题一看就是树链剖分qwq
- 但我们平常都是用线段树维护点权，那么这道题我们可以把两点边权转到深度较深的点的点权上。
- 注意两点之间的$lca$不能被算入答案
- 关于如何避开$lca$我们在询问时假设$x,y$为两点，且在同一重链上，设$dep[x]<dep[y]$，答案查询区间为$[idx[x]+1,y]$，因为$idx[x]$为$lca$，且重链内标号连续。（$dep$记录深度，$idx$记录重新标号后每个节点的标号）

## code
```cpp
#include <map> 
#include <set> 
#include <list> 
#include <cmath> 
#include <deque> 
#include <stack> 
#include <queue> 
#include <cstdio> 
#include <cctype> 
#include <vector> 
#include <string> 
#include <cstring> 
#include <iomanip> 
#include <complex> 
#include <iostream> 
#include <algorithm> 
#include <functional> 
using namespace std; 
const int maxn = 100000 + 100; 

template <class T> inline void read(T &s) { 
	s = 0; T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w; 
}

int n, tot, cnt; 
int lin[maxn], tree[maxn * 4], from[maxn], to[maxn]; 
int siz[maxn], fat[maxn], dep[maxn], val[maxn]; 
int son[maxn], idx[maxn], top[maxn], pre[maxn]; 
struct edge {
	int next, to, dis; 
} e[maxn << 1]; 
inline void add(int from, int to, int dis) {
	e[++tot].to = to; 
	e[tot].dis = dis; 
	e[tot].next = lin[from]; 
	lin[from] = tot; 
}

void dfs1(int u, int fa, int depth) {
	siz[u] = 1; 
	fat[u] = fa; 
	dep[u] = depth; 
	int maxson = -1; 
	for (int i = lin[u]; i; i = e[i].next) {
		int v = e[i].to; 
		if (v == fa) continue; 
		pre[v] = e[i].dis; 
		dfs1(v, u, depth + 1); 
		siz[u] += siz[v]; 
		if (siz[v] > maxson) {
			maxson = siz[v]; 
			son[u] = v; 
		}
	}
}

void dfs2(int u, int tp) {
	top[u] = tp; 
	idx[u] = ++cnt; 
	val[cnt] = pre[u]; 
	if (!son[u]) return ; 
	dfs2(son[u], tp); 
	for (int i = lin[u]; i; i = e[i].next) {
		int v = e[i].to; 
		if (!idx[v]) 
			dfs2(v, v); 
	}
}

void build(int p, int l, int r) {
	if (l == r) { tree[p] = val[l]; return ; }
	int mid = (l + r) >> 1; 
	build(p<<1, l, mid); 
	build(p<<1|1, mid + 1, r); 
	tree[p] = max(tree[p<<1], tree[p<<1|1]);  
}

void modify(int p, int l, int r, int x, int v) {
	if (l == r) { 
		tree[p] = v; 
		return ; 
	}
	int mid = (l + r) >> 1; 
	if (x <= mid) modify(p<<1, l, mid, x, v); 
	else modify(p<<1|1, mid + 1, r, x, v); 
	tree[p] = max(tree[p<<1], tree[p<<1|1]); 
}

int query(int p, int l, int r, int x, int y) {
	if (x > y) return 0; 
	if (x <= l && r <= y) return tree[p]; 
	int ret = 0; 
	int mid = (l + r) >> 1; 
	if (x <= mid) ret = max(ret, query(p<<1, l, mid, x, y)); 
	if (y > mid) ret = max(ret, query(p<<1|1, mid + 1, r, x, y)); 
	return ret; 
}

int TreeQuery(int x, int y) {
	if (x == y) return 0; 
	int ret = 0; 
	while (top[x] ^ top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y); 
		ret = max(ret, query(1, 1, n, idx[top[x]], idx[x])); 
		x = fat[top[x]]; 
	}
	if (dep[x] > dep[y]) swap(x, y); 
	ret = max(ret, query(1, 1, n, idx[x] + 1, idx[y])); 
	return ret; 
}

int main() {
	read(n); 
	for (int i = 1; i < n; ++i) {
		int u, v, w; 
		read(u), read(v), read(w); 
		from[i] = u, to[i] = v; 
		add(u, v, w); 
		add(v, u, w); 
	}

	dfs1(1, 0, 1); 
	dfs2(1, 1); 
	build(1, 1, n); 

	char ch[10]; int x, y; 
	while (1) {
		scanf("%s", ch); 
		if (ch[0] == 'D') return 0; 
		else if (ch[0] == 'Q') {
			read(x), read(y); 
			printf("%d\n", TreeQuery(x, y)); 
		}
		else if (ch[0] == 'C') {
			read(x), read(y); 
			int u = from[x], v = to[x]; 
			if (fat[v] == u) swap(u, v); 
			modify(1, 1, n, idx[u], y); 
		}
	}
	return 0; 
}

```

---

## 作者：殇雪 (赞：1)

这题要用到树链剖分

[不会树剖的同学点这里](http://www.cnblogs.com/rrsb/p/8053151.html "不会树剖的同学点这里")

把边权变为其dep比较深的那个点的点权，然后树剖（注意LCA的权值是不能算进去的。）


//第一次树剖套线段树，以前都是套树状数组的。


```cpp
    #include<bits/stdc++.h>
    #define sight(c) ('0'<=c&&c<='9')
    using namespace std;
    #define N 100017
    #define Mid (l+r>>1)
    #define eho(x) for(int i=head[x];i;i=net[i])
    int fall[N<<1],net[N<<1],cost[N<<1],head[N],f[N],dep[N],siz[N],son[N];
    int ma[N<<2],tot,n,co[N],id[N],tim,tp[N],ans,x,y,w,be[N],df[N];
    char ch[47];
    inline void read(int &x){
        static char c;static int b;
        for (b=1,c=getchar();!sight(c);c=getchar())if(c=='-')b=-1;
        for (x=0;sight(c);c=getchar())x=x*10+c-48;
        x*=b;
    }
    inline void add(int x,int y,int co){
        fall[++tot]=y; net[tot]=head[x]; head[x]=tot; cost[tot]=co; 
    }
    void write(int x){
        if (x<10) {putchar('0'+x); return;} write(x/10),putchar('0'+x%10);
    }
    inline void writeln(int x){
        if (x<0) putchar('-'),x*=-1;write(x); putchar('\n');
    } 
    void dfs1(int x,int fa){//第一遍dfs
        f[x]=fa; dep[x]=dep[fa]+1; siz[x]=1;
        eho(x) if (fall[i]^fa){
            co[fall[i]]=cost[i];
            id[i>>1]=fall[i];//边所对的点
            dfs1(fall[i],x);
            siz[x]+=siz[fall[i]];
            if (siz[son[x]]<siz[fall[i]]) son[x]=fall[i];
        }
    }
    void dfs2(int x,int top) {
        be[x]=++tim;df[tim]=x; tp[x]=top;
        if (son[x]) dfs2(son[x],top);
        eho(x) if (fall[i]^f[x]&&fall[i]^son[x]) dfs2(fall[i],fall[i]);
    }
    void build(int No,int l,int r){
        if (l>=r) {
            ma[No]=co[df[l]]; return;
        }
        build(No<<1,l,Mid); build(No<<1|1,Mid+1,r);
        ma[No]=max(ma[No<<1],ma[No<<1|1]);
    }
    void change(int No,int l,int r,int t,int k){
        if (l==r) {ma[No]=k; return;}
        if (t<=Mid) change(No<<1,l,Mid,t,k);
        else change(No<<1|1,Mid+1,r,t,k);
        ma[No]=max(ma[No<<1],ma[No<<1|1]);
    }
    int query(int No,int l,int r,int L,int R){
        if (L>R) {printf("rr"); return 0;}
        if (L<=l&&r<=R) return ma[No];
        if (R<=Mid) return query(No<<1,l,Mid,L,R);
        if (L >Mid) return query(No<<1|1,Mid+1,r,L,R);
        return max(query(No<<1,l,Mid,L,Mid),query(No<<1|1,Mid+1,r,Mid+1,R));
    }
    int ask(int x,int y){//查询路径
        ans=0;
        while (tp[x]^tp[y]) {
            if (dep[tp[x]]<dep[tp[y]]) swap(x,y);
            ans=max(ans,query(1,1,n,be[tp[x]],be[x]));
            x=f[tp[x]];
        }  
        if (x^y) {//lca 不统计入答案
          if (dep[x]<dep[y]) swap(x,y);
          ans=max(ans,query(1,1,n,be[son[y]],be[x])); 
        } return ans;
    }
    int main () {
        read(n); add(0,0,0);//我们加一条不存在的边，其记号(tot)为1,那么我们的一条边在原读入中就是其tot>>1,因为我们加了2条边。
        for (int i=1;i<n;i++) {
            read(x),read(y),read(w);
            add(x,y,w); add(y,x,w);
        }
        dfs1(1,0);
        dfs2(1,1);
        build(1,1,n);
        while (scanf("%s",ch),ch[0]!='D') {
            scanf("%d %d",&x,&y);
            if (ch[0]=='C') change(1,1,n,be[id[x]],y);
            else writeln(ask(x,y));     
        }  return 0;
    }

```

---

## 作者：灼眼的夏娜 (赞：1)

发现一道水题。。。

这不是树剖的板子吗。。。

线段树只能用于区间问题，放到树上，可以先用树链剖分将树拆成几条链，然后用线段树水过就行了

真没啥好说的，直接放代码好了（要是你不会树剖，~~那你来这里干啥。。。~~ 请先学习树剖）

## code
```cpp
#include<bits/stdc++.h>
#define R register
#define inf 1e9+7;
#define LL k<<1
#define RR k<<1|1

using namespace std;
const int N = 1e5 + 5;
int T, n;
int U[N], V[N], W[N];
int fa[N], son[N], top[N], dep[N], size[N], seg[N << 2], rev[N << 2];
int head[N << 1], cnt, tot, val[N];
int tr[N << 2];
char c[10];
struct saber {
	int nxt, to, val;
} rin[N << 2];

int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {if (c == '-')f = -1; c = getchar();}
	while (c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
	return x * f;
}

inline void add(int from, int to, int val) {
	rin[++cnt].to = to;
	rin[cnt].val = val;
	rin[cnt].nxt = head[from];
	head[from] = cnt;
}

void dfs1(int now, int f) {
	size[now] = 1; fa[now] = f; dep[now] = dep[f] + 1;
	for (int i = head[now]; i ; i = rin[i].nxt) {
		int vc = rin[i].to;
		if (vc == f) continue;
		val[vc] = rin[i].val;
		dfs1(vc, now);
		size[now] += size[vc];
		if (size[vc] > size[son[now]]) son[now] = vc;
	}
}

void dfs2(int now, int tp) {
	top[now] = tp;
	seg[now] = ++tot;
	rev[tot] = val[now];
	if (son[now]) dfs2(son[now], tp);
	for (int i = head[now]; i ; i = rin[i].nxt) {
		int vc = rin[i].to;
		if (vc == fa[now] || vc == son[now]) continue;
		dfs2(vc, vc);
	}
}

inline void update(int k) {tr[k] = max(tr[LL], tr[RR]);}

void build(int k, int l, int r) {
	if (l == r) {
		tr[k] = rev[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(LL, l, mid);
	build(RR, mid + 1, r);
	update(k);
}

void change(int k, int l, int r, int pos, int v) {
	if (l == r) {
		tr[k] = v;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid) change(LL, l, mid, pos, v);
	else change(RR, mid + 1, r, pos, v);
	update(k);
}

int query(int k, int l, int r, int x, int y) {
	if (x > y) return 0;
	if (l >= x && r <= y) return tr[k];
	int mid = (l + r) >> 1, res = -inf;
	if (x <= mid) res = max(res, query(LL, l, mid, x, y));
	if (y > mid) res = max(res, query(RR, mid + 1, r, x, y));
	return res;
}

inline int ask(int x, int y) {
	if (x == y) return 0;
	int res = 0;
	while (top[x] ^ top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		res = max(res, query(1, 1, n, seg[top[x]], seg[x]));
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	res = max(res, query(1, 1, n, seg[x] + 1, seg[y]));
	return res;
}

int main() {
	n = read();
	for (R int i = 1, u, v, w; i < n; ++ i) {
		u = read(); v = read(); w = read();
		U[i] = u, V[i] = v, W[i] = w;
		add(u, v, w); add(v, u, w);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	while (1) {
		scanf("%s", c + 1);
		if (c[1] == 'D') break;
		int x = read(), y = read();
		if (c[1] == 'C') {
			int u = U[x], v = V[x];
			if (fa[v] == u) swap(u, v);
			change(1, 1, n, seg[u], y);
		}
		if (c[1] == 'Q') printf("%d\n", ask(x, y));
	}
	return 0;
}
```


---

## 作者：szbszb (赞：0)

##### 这算是一道树链剖分模板题，但是从维护点权改成了维护边权

宣传一波[博客](https://www.cnblogs.com/szbszb/)

如果不会树链剖分的话请先学习[树链剖分](https://www.luogu.org/problem/P3384)

题解正式开始

这道题的一个难点就是如何维护边权，那肯定要将将边权转化成点权才行。

我们考虑一条边，它一定连接父亲节点和儿子节点（这不肯定的吗……），如果用父亲节点来存的话，该节点的其他儿子的边就没法存，但如果用儿子节点来存的话就没有这种问题（一个节点可以有多个儿子，但不会有超过一个的父亲），这样，将边权值存在哪的问题就解决了。

那怎么存呢？我们考虑一下，存点权的树链剖分是在第二遍DFS的时候处理点权的，因此，我们可以记录从当前节点到它的父节点的边权作为它的点权。

第二遍DFS的代码如下：
```cpp
inline void did2(long long u,long long topf,long long l1)//l1代表该节点到父亲节点的距离。
{
	id[u]=++cnt;
	w[cnt]=l1;//这就是记录边权了
	top[u]=topf;
	if (!son[u]) return;
	long long lx;//因为要先找重儿子，所以提前求出该节点到重儿子的距离
	for (long long i=he[u];i;i=ne[i]) if (to[i]==son[u]) lx=ll[i];
	did2(son[u],topf,lx);
	for (register long long i=he[u];i;i=ne[i])
	{
		register long long v=to[i];
		if (v==f[u]||v==son[u]) continue;
		did2(v,v,ll[i]);//ll数组记录路径长，这就是儿子节点到该节点的距离了
	}
}
```
不要以为这就完事了，当我们要求值时，原本的代码如下：
```cpp
inline long long quimax(long long x,long long y)
{
	register long long ans=0;
	while(top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=(ans+qui(1,id[top[x]],id[x]));
		x=f[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	ans=(ans+qui(1,id[x],id[y]));
	return ans;
}
```
有没有发现有什么问题？

我们发现，最后这一段
```cpp
	ans=(ans+qui(1,id[x],id[y]));
```
中，我们求的其实是f[x]到y的路径的边权和，而不是x到y的路径的边权和，我们考虑到x，y在一条重链上，所以求son[x]，y就相当于求x，y的值了。

正确代码如下：
```cpp
inline long long quimax(long long x,long long y)
{
	register long long ans=-1e11;
	while(top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=max(ans,qui(1,id[top[x]],id[x]));
		x=f[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	ans=max(ans,qui(1,id[son[x]],id[y]));//求x到y的路径的边权和。
	return ans;
}
```

这道题还有一个问题就是如何找出存储第x条边的节点

这就要利用链式前向星的一点性质了

对于一个有向图，第x条边所指向的节点就是to[x]（bian[x].to），而对于无向图的话，第x条边所连接的节点就是to[2 * x]和to[2 * x-1] (bian[2 * s].to和bian[2 * x-1].to,这个依据个人习惯)，而这两个节点中深的那个节点就是儿子节点了（因为深度[儿子]=深度[父亲]+1啊……)，然后修改这个节点就行了……

其他的就和树链剖分的代码一样了……总代码如下，和模板树链剖分一样的和上文解释过的，就不加注释了……（累死了）
```cpp
#include<bits/stdc++.h>
using namespace std;
long long qq,n,m,r1,p,q,i,k,x,y,cnt,top[1000001],w[1000001],a[1000001],dep[1000001],f[1000001],siz[1000001],he[1000001],ll[2000001],ne[2000001],to[2000001],z[4000001],l[4000001],r[4000001],c[4000001],son[1000001],id[1000001];
inline void did1(long long u,long long fat,long long dee)
{
	dep[u]=dee;
	f[u]=fat;
	siz[u]=1;
	register long long max1=-1;
	register long long v;
	for (register long long i=he[u];i;i=ne[i])
	{
		v=to[i];
		if (v==fat) continue;
		did1(v,u,dee+1);
		if (siz[v]>max1)
		{
			son[u]=v;
			max1=siz[v];
		}
		siz[u]+=siz[v];
	}
}
inline void did2(long long u,long long topf,long long l1)
{
	id[u]=++cnt;
	w[cnt]=l1;
	top[u]=topf;
	if (!son[u]) return;
	long long lx;
	for (long long i=he[u];i;i=ne[i]) if (to[i]==son[u]) lx=ll[i];
	did2(son[u],topf,lx);
	for (register long long i=he[u];i;i=ne[i])
	{
		register long long v=to[i];
		if (v==f[u]||v==son[u]) continue;
		did2(v,v,ll[i]);
	}
}
inline void build(long long u,long long l1,long long r1)
{
  l[u]=l1;
  r[u]=r1;
  if (l1==r1)
  {
    z[u]=w[l1];
    return;
  }
  build(u*2,l1,(l1+r1)/2);
  build(u*2+1,(l1+r1)/2+1,r1);
  z[u]=max(z[u*2],z[u*2+1]);
}
inline void jia(long long u,long long l1,long long r1,long long k)
{
  if ((l[u]>r1)||(r[u]<l1)) return;
  if ((l[u]>=l1)&&(r[u]<=r1))
  {
    z[u]=k;
    return;
  }
  jia(u*2,l1,r1,k);
  jia(u*2+1,l1,r1,k);
  z[u]=max(z[u*2],z[u*2+1]);
}
inline long long qui(long long u,long long l1,long long r1)
{
  if ((l1>r[u])||(r1<l[u])) return -1e11;
  if ((l1<=l[u])&&(r1>=r[u])) return z[u];
    return max(qui(u*2,l1,r1),qui(u*2+1,l1,r1));
}
inline long long quimax(long long x,long long y)
{
	register long long ans=-1e11;
	while(top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=max(ans,qui(1,id[top[x]],id[x]));
		x=f[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	ans=max(ans,qui(1,id[son[x]],id[y]));
	return ans;
}
int main()
{
	scanf("%lld",&n);
	for (i=1;i<n;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&r1);//链式前向星
		cnt++;
		ne[cnt]=he[x];
		to[cnt]=y;
		ll[cnt]=r1;
		he[x]=cnt;
		cnt++;
		ne[cnt]=he[y];
		to[cnt]=x;
		ll[cnt]=r1;
		he[y]=cnt;
	}
	did1(1,0,1);
	cnt=0;
	did2(1,1,0);//个人习惯1节点到0节点距离为0……实际上啥都可以。
	build(1,1,n);
	q=getchar();
	while(q<'A'||q>'Z') q=getchar();
	qq=getchar();
	while (qq>='A'&&qq<='Z') qq=getchar();//千万不要用cin，太慢了，作者喜欢用getchar()；
	while(q!='D')
	{
		scanf("%lld%lld",&x,&y);
		if (q=='Q')
			if (x!=y)
				printf("%lld\n",quimax(x,y));
			else
				printf("0\n");
		else
		{
			r1=to[2*x];
			p=to[2*x-1];//找出这条边所连的两个节点
			if (dep[r1]>dep[p]) jia(1,id[r1],id[r1],y);
			else jia(1,id[p],id[p],y);//找出儿子节点，进行修改
		}
		q=getchar();
		while(q<'A'||q>'Z') q=getchar();
		qq=getchar();
		while(qq>='A'&&qq<='Z') qq=getchar();
	}
	return 0；
}
```
这道题就完事了

---

## 作者：dengyaotriangle (赞：0)

总感觉我的写法和所有其它题解都不太一样就写一下我的做法吧

首先显然这是一道树链剖分题

但是树链剖分是求点权而这道题是求边权，所以需要转化

这里使用了一个比较奇怪的技巧，但这个思想在某些其它题中有着广泛的应用

若$ (u,v) $ 间要连一条边权为 $ w $ 的边

那么我们新建一个点$ x $，点权为 $ w $ ,并且连边$ (u,x) $和$ (v,x) $ 

原来的$ u,v $的点权均设为$ 0 $

那么我们就对于每一条边都新建了一个点，可以理解为在一棵树的每一条边的中间“插上”一个点

现在看询问操作，因为这样构造中原节点点权为$ 0 $，对答案没有影响所以直接树链剖分询问就可以了

那么修改操作，修改第$ i $条边的边权，就转化为修改相应在边上插入的点的点权

至此，这道题已经转化为了树链剖分模板题

但这种写法要开两倍多的点所以常数较大，但仍可过本题

代码:
```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn=200005;

int n,m;
int c1,c2;
vector<int> adj[maxn];
int vl[maxn];
int dfn[maxn],hvs[maxn],sz[maxn],top[maxn],fa[maxn],dep[maxn],rk[maxn];

void dfs1(int u){
    sz[u]=1;
    int bi=0,bn=0;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(!dep[v]){
            dep[v]=dep[u]+1;
            fa[v]=u;
            dfs1(v);
            if(sz[v]>bn){
                bn=sz[v];
                bi=v;
            }
            sz[u]+=sz[v];
        }
    }
    hvs[u]=bi;
}

void dfs2(int u){
    dfn[u]=++c2;
    rk[c2]=u;
    if(hvs[u]){
        top[hvs[u]]=top[u];
        dfs2(hvs[u]);
    }
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(dep[v]==dep[u]+1&&v!=hvs[u]){
            top[v]=v;
            dfs2(v);
        }
    }
}

struct node{
    int l,r,v;
    node* c[2];
};
node* rt;
node* nwnode(int l,int r){
    node* nw=new node;
    nw->l=l;nw->r=r;nw->v=0;nw->c[0]=nw->c[1]=NULL;
    return nw;
}

void pu(node* rt){
    if(!rt) return;
    if(rt->l==rt->r ) return;
    rt->v=max(rt->c[0]->v,rt->c[1]->v);
}
node* bt(int l,int r){
    node* nw=nwnode(l,r);
    if(l==r){
        nw->v=vl[rk[l]];
    }else{
        nw->c[0]=bt(l,(l+r)/2);
        nw->c[1]=bt((l+r)/2+1,r);
        pu(nw);
    }
    return nw;
}

void chg(node* rt,int i,int v){
    int cl=rt->l,cr=rt->r,cm=(cl+cr)/2;
    if(cl==cr){
        rt->v=v;
    }else if(i<=cm) chg(rt->c[0],i,v);
    else if(i>cm) chg(rt->c[1],i,v);
    pu(rt);
}

int qry(node* rt,int l,int r){
    int cl=rt->l,cr=rt->r,cm=(cl+cr)/2;
    if(l==cl&&r==cr){
        return rt->v;
    }else if(r<=cm) return qry(rt->c[0],l,r);
    else if(l>cm) return qry(rt->c[1],l,r);
    else return max(qry(rt->c[0],l,cm),qry(rt->c[1],cm+1,r));
}

int qrl(int u,int v){
    int ans=0;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        ans=max(ans,qry(rt,dfn[top[u]],dfn[u]));
        u=fa[top[u]];
    }
    if(dfn[u]>dfn[v]) swap(u,v);
    ans=max(ans,qry(rt,dfn[u],dfn[v]));
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    c1=n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        ++c1;
        adj[u].push_back(c1);
        adj[v].push_back(c1);
        adj[c1].push_back(u);
        adj[c1].push_back(v);
        vl[c1]=w;
    }
    dep[1]=1;
    dfs1(1);
    top[1]=1;
    dfs2(1);
    rt=bt(1,c1);
    while(1){
        char x[10];
        cin>>x;
        if(x[0]=='D') return 0;
        if(x[0]=='Q'){
            int l,r;
            cin>>l>>r;
            cout<<qrl(l,r)<<'\n';
        }else{
            int a,b;
            cin>>a>>b;
            chg(rt,dfn[n+a],b);
        }
    }
    return 0;
}
```

---

## 作者：little_sun (赞：0)

很明显这是一道树剖题

但是，树剖是在点上进行的操作，如何把它转化到边上呢？

不难发现，每一个点与他的父亲节点之间仅有唯一的一条边

于是我们可以把这条边的边权转化为这个儿子节点的点权。

然后还有一点要注意

查询时，我们是不能查询到$(u, v)$的$LCA$的

因为$LCA$的点权是$LCA$与$fa[LCA]$之间的边权

而我们并没有统计这鬼东西

怎么办呢？

注意到当$top[u] = top[v]$时，$v$就是$u$的$LCA$ (默认$dfn[v]<dfn[u]$)

所以我们此时查询$(dfn[v+1], dfn[u])$即可

PS:感谢@Siyuan的博客让我学会了点权转边权

代码:

```cpp
#include <bits/stdc++.h>
const int MaxN = 500010;
struct edge
{
    int next, to, dis;
};
struct node
{
    int max;
    int l, r;
};
edge e[MaxN << 1];
int n, cnt, dfsnum;
int a[MaxN], head[MaxN], dep[MaxN], fa[MaxN], size[MaxN];
int hson[MaxN], dfn[MaxN], top[MaxN], from[MaxN], to[MaxN], pre[MaxN];
struct SegmentTree
{
    node t[MaxN << 2];
    inline void pushup(int id) { t[id].max = std::max(t[id << 1].max, t[id << 1 | 1].max); }
    inline void build(int id, int l, int r)
    {
        t[id].l = l, t[id].r = r;
        if (l == r)
        {
            t[id].max = a[pre[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        pushup(id);
    }
    inline void modify(int id, int l, int r, int val)
    {
        if (t[id].l > r || t[id].r < l)
            return;
        if (l <= t[id].l && t[id].r <= r)
        {
            t[id].max = val;
            return;
        }
        modify(id << 1, l, r, val);
        modify(id << 1 | 1, l, r, val);
        pushup(id);
    }
    inline int query(int id, int l, int r)
    {
        if (l > t[id].r || r < t[id].l)
            return 0;
        if (l <= t[id].l && t[id].r <= r)
            return t[id].max;
        return std::max(query(id << 1, l, r), query(id << 1 | 1, l, r));
    }
} T;
inline void add_edge(int u, int v, int d)
{
    ++cnt;
    e[cnt].to = v;
    e[cnt].dis = d;
    e[cnt].next = head[u];
    head[u] = cnt;
}
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}
inline void dfs1(int u, int f)
{
    size[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if (v == f)
            continue;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        a[v] = e[i].dis;
        dfs1(v, u);
        size[u] += size[v];
        if (size[hson[u]] < size[v])
            hson[u] = v;
    }
}
inline void dfs2(int u, int Top)
{
    ++dfsnum;
    dfn[u] = dfsnum;
    pre[dfsnum] = u;
    top[u] = Top;
    if (hson[u])
        dfs2(hson[u], Top);
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if (v == fa[u] || v == hson[u])
            continue;
        dfs2(v, v);
    }
}
inline void modify(int pos, int val) { T.modify(1, dfn[pos], dfn[pos], val); }
inline int query_chain(int u, int v)
{
    int ans = 0;
    if (dfn[u] < dfn[v])
        std::swap(u, v);
    while (top[u] != top[v])
    {
        if (dfn[u] < dfn[v])
            std::swap(u, v);
        ans = std::max(ans, T.query(1, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dfn[u] < dfn[v])
        std::swap(u, v);
    ans = std::max(ans, T.query(1, dfn[v] + 1, dfn[u]));
    return ans;
}
int main()
{
    n = read();
    for (int i = 1; i < n; i++)
    {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        from[i] = u;
        to[i] = v;
        add_edge(u, v, d);
        add_edge(v, u, d);
    }
    dep[1] = 1, fa[1] = 0;
    dfs1(1, 0), dfs2(1, 1);
    T.build(1, 1, n);
    std::string op;
    std::cin >> op;
    while (op != "DONE")
    {
        if (op == "CHANGE")
        {
            int x = read(), val = read();
            int u = from[x], v = to[x];
            if (fa[v] == u)
                std::swap(u, v);
            modify(u, val);
        }
        else
        {
            int a = read(), b = read();
            printf("%d\n", query_chain(a, b));
        }
        std::cin >> op;
    }
    return 0;
}

```



---

## 作者：FutaRimeWoawaSete (赞：0)

$\text{Qtree}$ 系列是个比较适合树剖新手的系列题目，

这里建议没学过 $\text{Link-Cut-Tree}$ 的同学可以只做前面的 $\text{1}$ ~ $\text{5}$，$\text{T5}$ 的点分治还是友好一些。  

$\text{Qtree}$ 系列的题目都涉及了边处理，此题也不意外。 

---

作为 $\text{Qtree}$ 系列的 $\text{T1}$，我们就来解决这一系列题目的最难点——如何维护边的信息。  

以往维护点的信息的方法，貌似要强行套在边上面不是很好使，于是从边的性质入手：  

边只有 $\text{n - 1}$ 条，与n个点的数量只差 $\text{1}$，所以说我们不妨思考将边上的值转到点上来；

在树上，一个点只与其父亲有且仅只连有一条边，所以根据这个性质，

我们就把一条边的权值存在其一条边上的儿子节点上即可，

这样就解决了边的对应问题；

很明显，这么分配我们的边后我们的根节点就没有可以匹配的边了，这时候我们就根据题目性质：

如果维护最大值最小值就置根节点的权值为 $\text{-INF\ or\ INF}$，维护和就直接记为 $\text{0}$ 即可。

于是这道题我们就按照上述方法把边权往点权上带即可，这道题成了模板题。

注意一下，在我们的 $\text{updRange}$ 和 $\text{qRange}$ 过程中，我们都不能影响到两个节点的最近公共祖先节点。

毕竟他们的最近公共祖先的节点存的权值并不是这条长路径上的一条路径的权值。

所以在最后的一步时 $\text{id[x]}$ 需要 $\text{+ 1}$，以 $\text{qRange}$ 举例，代码如下：  

``` cpp
long long qRange(int x,int y)
{
	long long res = 0;
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x , y);
		res = max(res , query(1 , 1 , n , id[top[x]] , id[x]));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x , y);
	res = max(res , query(1 , 1 , n ,id[x] + 1, id[y]));
	return res;
}
```

注意点也就这些了，个人喜欢在边上就存下这些这条边的权值被放在哪个地方，

实现方式有些大同小异，如带来不适请谅解。 

代码如下：  

``` cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int Len = 1e5 + 5,MAXN = 2147483647; 
long long n,m,wt[Len],w[Len],fa[Len],dep[Len],siz[Len],son[Len],id[Len],top[Len],ans[Len << 2],head[Len],cnt,tot;
struct node
{
	int next,to;
	long long v;
}edge[Len << 1];
void add(int from,int to,long long val)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	edge[cnt].v = val;
	head[from] = cnt;
}
void dfs(int x,int f,long long v)
{
	w[x] = v;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs(to , x , edge[e].v);
	}
}
void dfs1(int x,int f,int deep)
{
	dep[x] = deep;
	fa[x] = f;
	siz[x] = 1;
	int maxson = -1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs1(to , x , deep + 1);
		siz[x] += siz[to];
		if(siz[to] > maxson) maxson = siz[to] , son[x] = to;
	}
}
void dfs2(int x,int topf)
{
	id[x] = ++ tot;
	wt[tot] = w[x];
	top[x] = topf;
	if(!son[x]) return;
	dfs2(son[x] , topf);
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == fa[x] || to == son[x]) continue;
		dfs2(to , to);  
	}
}
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
void push_up(int x){ans[x] = max(ans[ls(x)] , ans[rs(x)]);}
void build(int p,int l,int r)
{
	if(l == r)
	{
		ans[p] = wt[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
}
void update(int p,int l,int r,int idx,long long ch)
{
	if(l == r) 
	{
		ans[p] = wt[l] = ch;
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) update(ls(p) , l , mid , idx , ch);
	else if(idx > mid) update(rs(p) , mid + 1 , r , idx , ch);
	push_up(p);
}
long long query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return ans[p];
	int mid = (l + r) >> 1;long long res = 0;
	if(nl <= mid) res = max(res , query(ls(p) , l , mid , nl , nr));
	if(nr > mid) res = max(res , query(rs(p) , mid + 1 , r , nl , nr));
	return res;
}
long long qRange(int x,int y)
{
	long long res = 0;
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x , y);
		res = max(res , query(1 , 1 , n , id[top[x]] , id[x]));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x , y);
	res = max(res , query(1 , 1 , n ,id[x] + 1, id[y]));
	return res;
}
char s[15];
struct Node
{
	int x,y,z;
	long long val;
}E[Len];
int main()
{
	scanf("%lld",&n);
	for(int i = 1; i < n; i ++) 
	{
		scanf("%d %d %lld",&E[i].x,&E[i].y,&E[i].val);
		add(E[i].x , E[i].y , E[i].val) , add(E[i].y , E[i].x , E[i].val);	
	}  
	dfs(1 , 0 , -MAXN);
	dfs1(1 , 0 , 1);
	dfs2(1 , 1);
	build(1 , 1 , n);
	for(int i = 1; i < n ; i ++)
	{
		if(fa[E[i].x] == E[i].y) E[i].z = E[i].x;
		else E[i].z = E[i].y;
	}
	while(1)
	{
		scanf("%s",s);
		if(s[0] == 'D') break;
		else if(s[0] == 'C')
		{
			int x;long long t;
			scanf("%d %lld",&x,&t);
			update(1 , 1 , n , id[E[x].z] , t);
		}
		else if(s[0] == 'Q')
		{
			int x,y;
			scanf("%d %d",&x,&y);
			if(x == y) printf("0\n");
			else printf("%lld\n",qRange(x , y));
		}
	}
	return 0;
}
```

---

