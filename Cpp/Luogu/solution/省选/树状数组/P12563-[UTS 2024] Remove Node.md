# [UTS 2024] Remove Node

## 题目描述

给定一棵包含 $n$ 个顶点的有根树，每个顶点 $x$ 被赋予一个权值 $a_x$。树的根节点为 $1$ 号节点。

你可以执行以下操作：将两个相邻节点 $x$ 和 $y$ 合并为一个新节点 $z$，$z$ 的权值为这两个节点权值的最小值。该操作会将原本与 $x$ 或 $y$ 相连的边改为与 $z$ 相连。操作的成本为 $|a_x - a_y|$，多次操作的总成本为各次操作成本之和。

你需要处理两种查询：
1. $1\ x\ y$：将节点 $x$ 的权值更新为 $y$；
2. $2\ x$：询问将以 $x$ 为根的子树通过操作合并为单个节点的最小总成本。

## 说明/提示

- （$4$ 分）：$n \le 1000$，$q=1$；
- （$13$ 分）：$q=1$；
- （$15$ 分）：树为链状且仅包含第二类查询；
- （$24$ 分）：仅包含第二类查询；
- （$12$ 分）：$p_i=1$（所有非根节点的父节点均为根节点）；
- （$32$ 分）：无额外限制。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
4 7 9 7 4 1 2
1 1 3 2 3 2
1
2 1```

### 输出

```
11```

## 样例 #2

### 输入

```
7
6 6 5 1 6 6 4
1 1 2 3 3 3
3
2 1
1 1 1
2 1```

### 输出

```
7
11```

# 题解

## 作者：流水行船CCD (赞：1)

首先考虑换一种方式去思考原问题的操作（因为合并点太丑了，不好分析，考虑寻找一种不改变树形态的刻画方法）：发现其等价于每次在原树上选择一条边断开，断开的代价就是两端连通块最小值的差的绝对值，最后需要使得所有边全部断开且最小化代价和。

通过对样例的手玩，不难发现尽可能使最小值最早被删成孤立点（即删除最小点的所有出边）一定最优。证明不妨设 $x$ 是最小点，考虑 $x$ 的出边 $(x,y)$，不妨设我们先删去了 $y$ 方向连通块的一条边 $(u,v)$，橙色联通块最小值为 $A$，绿色联通块最小值为 $B$，此时的代价就是 $(A-a_x)+(B-a_x)$，不优于先删 $(x,y)$ 的代价 $(\min(A,B)-a_x)+|A-B|$。所以每次选权值最小的点，将其出边全部删除，这样得到的方案就是最优解。

![](https://cdn.luogu.com.cn/upload/image_hosting/94yjgg9m.png)

可以做到 $O(nq)$ 或 $O(nq\log n)$，有 $17$ 分。

由于答案形如：$\sum a_y-a_x(a_x \le a_y)$，考虑分别统计 $\sum a_x$（作为最小点）和 $\sum a_y$（作为最小点出边连通块中的最小点）的值。

首先考虑 $\sum a_x$ 的值，考虑每一条边被断开时是以哪个端点为最小点，因此其可以写成：

$$
\sum_{(u,v) \in E} \min(a_u,a_v)
$$

可以用一棵平衡树/值域线段树维护一个点所有儿子的权值集合，那么不难通过线段树二分在 $O(\log n)$ 的时间中求得一个点到它儿子所有边的贡献和，把这个贡献和放在一颗 dfn 线段树上就可以支持单点修改，子树查询了。

平衡树优势是空间线性，动态开点值域线段树优势是常数相对较小且实现简易。

其次考虑 $\sum a_y$ 的值，由于一个点作为某一个最小点 $x$ 出边连通块中的最小点计算过一次后，那么下一次该出边连通块中删点时它一定就会作为最小点了，也就是说每个点至多被作为某个最小点出边连通块中最小点计算一次！考虑哪些点从来没有被计算过，发现只有最开始的最小点！

所以使用 dfn 线段树维护子树的权值和和最小值即可。

$O((n + q)\log n)$。

---

## 作者：Miss_SGT (赞：1)

考虑 $q=1$。

显然全局的最小值无论怎么合并值都不变，而且最小值与其他点合并的成本非常大。所以我们希望与最小值合并的次数尽量少且与其合并的数尽量小。于是我们将最小值点删掉（多个时随便选一个），将剩下连通块变成子问题，最后每个连通块会变成其最小值，再和这个点合并。这样就是一次 $O(n^2)$ 的了。

如果我们让每个点向其分出去的连通块的最小值连有向边，那么这个将构成一个树，每个点的贡献为 $值 \times ([有父亲] - 儿子数量)$。

有父亲这一项是简单的，只要不是子树最小值都有父亲，只需线段树维护子树最小值。

儿子数量就是与当前点相邻的值大于等于他的数量。因为在当前点作为最小值时这条边一定没被断开，则一定会产生一个儿子。注意相邻两点值相等时只能算一次。这个暴力做就是 $O(n)$ 的了。

如果我们将每条边的贡献放到上面那个点上，则单点修改只会修改该点与其父亲的贡献。对父亲的直接算就完了。令修改的点为 $x$ ，修改成的值为 $y$。则对于自己的，只有值在 $[\min(a_x,y),\max(a_x,y)-1]$ 里的儿子才有贡献，这个可以用动态开点线段树维护。计算方式可以分讨 $a_x$ 与 $y$ 的大小关系，不难。

以上所有修改的贡献都可以使用树状数组维护。

两棵线段树有点屎：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,R=1e9;
int n,q,a[N],f[N],cnt[N],op[N],x[N],y[N],w[N];
int head[N],nxt[N],dfn[N],low[N],xl[N],idx;
void dfs(int p){
	xl[dfn[p]=++idx]=p;
	for(int v=head[p];v;v=nxt[v]) dfs(v);
	low[p]=idx;
}
#define ll long long
ll bt[N];
inline void add(int x,ll y){for(;x<=n;x+=x&-x) bt[x]+=y;}
inline ll query(int x,ll ans=0){
	for(;x;x-=x&-x) ans+=bt[x];
	return ans;
}
struct Tree{
	int ls,rs,cnt;ll sum;
	inline Tree operator+(Tree y)const{return (Tree){0,0,cnt+y.cnt,sum+y.sum};}
}t[N*60];
int root[N],tot;
#define mid ((l+r)>>1)
void change(int &p,int l,int r,int x,int y){
	if(!p) p=++tot;
	if(!(t[p].cnt+=y)) return p=0,void();
	t[p].sum+=x*y;
	if(l==r) return;
	if(x<=mid) change(t[p].ls,l,mid,x,y);
	else change(t[p].rs,mid+1,r,x,y);
}
const Tree zero={0,0,0,0};
Tree query(int p,int l,int r,int lt,int rt){
	if(!p) return zero;
	if(t[p].ls<0) return lt<=t[p].rs&&t[p].rs<=rt?t[p]:zero;
	if(lt<=l&&r<=rt) return t[p];
	return (lt<=mid?query(t[p].ls,l,mid,lt,rt):zero)+(mid<rt?query(t[p].rs,mid+1,r,lt,rt):zero);
}
int mi[1<<19];
void build(int p,int l,int r){
	if(l==r) return mi[p]=a[xl[l]],void();
	build(2*p,l,mid);
	build(2*p+1,mid+1,r);
	mi[p]=min(mi[2*p],mi[2*p+1]);
}
void update(int p,int l,int r,int x){
	if(l==r) return mi[p]=a[xl[l]],void();
	if(x<=mid) update(2*p,l,mid,x);
	else update(2*p+1,mid+1,r,x);
	mi[p]=min(mi[2*p],mi[2*p+1]);
}
int qmin(int p,int l,int r,int lt,int rt){
	if(lt<=l&&r<=rt) return mi[p];
	return min(lt<=mid?qmin(2*p,l,mid,lt,rt):R,mid<rt?qmin(2*p+1,mid+1,r,lt,rt):R);
}
inline ll Val(int x,int y){return (x>y?-y:0)+(x<=y?-x:0);}
int main(){
	read(n);
	for(int i=1;i<=n;++i) read(a[i]);
	for(int i=2;i<=n;++i) read(f[i]),nxt[i]=head[f[i]],head[f[i]]=i;
	dfs(1);
	for(int i=1;i<=n;++i){
		ll res=a[i];cnt[i]=1;
		for(int v=head[i];v;v=nxt[v]){
			change(root[i],1,R,a[v],1);
			res+=Val(a[i],a[v]);
			cnt[i]-=(a[v]>=a[i]);
		}
		add(dfn[i],res);
	}
	build(1,1,n);
	read(q);
	while(q--){
		int op,x,y;
		read(op),read(x);
		if(op==1){
			read(y);
			if(a[x]==y) continue;
			if(f[x]){
				cnt[f[x]]-=(y>=a[f[x]])-(a[x]>=a[f[x]]);
				add(dfn[f[x]],Val(a[f[x]],y)-Val(a[f[x]],a[x]));
				change(root[f[x]],1,R,a[x],-1);
				change(root[f[x]],1,R,y,1);
			}
			ll res=1ll*cnt[x]*(y-a[x]);
			Tree w=query(root[x],1,R,min(a[x],y),max(a[x],y)-1);
			res+=(w.sum-1ll*w.cnt*y)*(y<a[x]?1:-1);
			cnt[x]-=w.cnt*(y<a[x]?1:-1);
			add(dfn[x],res);
			a[x]=y;
			update(1,1,n,dfn[x]);
		}else print(query(low[x])-query(dfn[x]-1)-qmin(1,1,n,dfn[x],low[x])),pc('\n');
	}
	flush();
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

考察对于一棵树如何计算答案。

我们发现对于权值最大的点，如果不立刻将其与周围的点合并，后面的操作中周围的点权值只会变小，再合并就不优了，所以一定是每次把权值最大的点和其周围权值最大的点合并。

我们需要一个更好的统计贡献方式以快速支持修改与计算一个子树的答案。

由于贡献式带了一个绝对值，考虑枚举 $k$ 然后把值按照是否 $\leq k$ 映射到 $0,1$ 上计算答案，不难发现这样是正确的，因为可以任意决定相同数内部的合并方式，同时我们发现贡献就是 $1$ 的连通块数量，当然要排除全部是 $1$ 的所有情况，考虑用点边容斥计算连通块数量，于是需要一个线段树维护子树 $\min$，用树状数组维护点和边对其祖先的贡献，对于每个点开个平衡树维护儿子边贡献即可，时间复杂度 $O((n+q) \log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+114;
vector<int> E[maxn];
int fa[maxn];
int a[maxn];
int sz[maxn];
int L[maxn],R[maxn],dfncnt;
int node[maxn];
void dfs(int u){
	L[u]=++dfncnt;
	node[dfncnt]=u;
	for(int v:E[u]){
		dfs(v);
	}
	R[u]=dfncnt;
}
int tr[maxn<<2];
void pushup(int cur){
	tr[cur]=min(tr[cur<<1],tr[cur<<1|1]); 
}
void upd(int cur,int lt,int rt,int pos){
	if(lt==rt){
		tr[cur]=a[node[lt]];
		return ;
	}
	int mid=(lt+rt)>>1;
	if(pos<=mid) upd(cur<<1,lt,mid,pos);
	else upd(cur<<1|1,mid+1,rt,pos);
	pushup(cur);
}
int askmin(int cur,int lt,int rt,int l,int r){
	if(r<lt||rt<l) return 1e9;
	if(l<=lt&&rt<=r) return tr[cur];
	int mid=(lt+rt)>>1;
	return min(askmin(cur<<1,lt,mid,l,r),askmin(cur<<1|1,mid+1,rt,l,r));
}
struct FHQ{
	int rk,val;
	int cnt,sum;
	int ls,rs;
	FHQ(){
		rk=val=cnt=sum=ls=rs=0;
	}
}treap[maxn<<1];
void update(int cur){
	if(cur==0) return ;
	treap[cur].cnt=treap[treap[cur].ls].cnt+treap[treap[cur].rs].cnt+1;
	treap[cur].sum=treap[treap[cur].ls].sum+treap[treap[cur].rs].sum+treap[cur].val;
}
int merge(int u,int v){
	if(u==0||v==0) return u+v;
	if(treap[u].rk>treap[v].rk){
		treap[u].rs=merge(treap[u].rs,v);
		update(u);
		return u;
	}else{
		treap[v].ls=merge(u,treap[v].ls);
		update(v);
		return v;	
	}
	return -1;
}
void split(int cur,int &l,int &r,int k){//<=k -> l
	if(cur==0){
		l=r=0;
		return ;
	}
	if(treap[cur].val<=k){
		l=cur;
		split(treap[l].rs,treap[l].rs,r,k);
		update(l);
	}else{
		r=cur;
		split(treap[r].ls,l,treap[r].ls,k);
		update(r);
	}
}
int root[maxn],tot;
int ask(int u){
	int x=0,y=0;
	split(root[u],x,y,a[u]);
	int res=treap[x].sum+treap[y].cnt*a[u];
	root[u]=merge(x,y);
	return a[u]-res;
}
mt19937 rd(time(0));
void ins(int u,int c){
	tot++;
	treap[tot].rk=rd();
	treap[tot].val=treap[tot].sum=c;
	treap[tot].cnt=1;
	int x=0,y=0;
	split(root[u],x,y,c);
	root[u]=merge(x,merge(tot,y));
}
void del(int u,int c){
	int x=0,y=0,z=0;
	split(root[u],x,y,c-1);
	split(y,y,z,c);
	y=merge(treap[y].ls,treap[y].rs);
	root[u]=merge(x,merge(y,z));
}
int n,q;
int bit[maxn];
void add(int u,int c){
	u=L[u];
	while(u<=n) bit[u]+=c,u+=u&(-u);
} 
int solve(int u){
	int x=R[u],res=0;
	while(x>0) res+=bit[x],x-=(x&(-x));
	x=L[u]-1;
	while(x>0) res-=bit[x],x-=(x&(-x));
	return res;
} 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++){
		cin>>fa[i];
		E[fa[i]].push_back(i);
	}
	dfs(1);
	for(int i=2;i<=n;i++){
		ins(fa[i],a[i]);
	}
	for(int i=1;i<=n;i++) upd(1,1,n,L[i]);
	for(int i=1;i<=n;i++) add(i,ask(i));
	cin>>q;
	while(q--){
		int opt;
		cin>>opt;
		if(opt==1){
			int x,y;
			cin>>x>>y;
			add(x,-ask(x));
			if(fa[x]!=0) add(fa[x],-ask(fa[x])),del(fa[x],a[x]);
			a[x]=y;
			upd(1,1,n,L[x]);
			if(fa[x]!=0) ins(fa[x],a[x]),add(fa[x],ask(fa[x]));
			add(x,ask(x));
		}else{
			int x;
			cin>>x;
			cout<<solve(x)-askmin(1,1,n,L[x],R[x])<<"\n";
		}
	}
	return 0;
}
```

---

