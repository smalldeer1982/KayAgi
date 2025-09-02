# [PA 2017] Banany

## 题目描述

Bajtazar 是一名商人，他每天会从自己所在的城市出发，到另一个城市去贩卖香蕉。每条道路都会有一定的过路费，而作为终点的城市能获得一定收益（注意：途经点没有收益）。而每过一天，就会有一条道路的费用发生变化，或者某个城市的收益发生变化。Bajtazar 想知道当他每一天醒来后，以哪个城市作为终点获得的利润最大，而次日他会从该城市继续出发。

有 $n$ 个城市，由 $n - 1$ 条道路连接，且互相都能到达。第 $i$ 个城市有一个收益 $z_i$ ，每条边有一个费用 $w$ 。

如果从 $s$ 到 $t$ 做生意，获得的利润是

$$ z_t - \sum_{e \in \mathrm{Path}(s, t)} w(e) $$

一共有 $q$ 天。

最初 Bajtazar 在 $1$ 号城市。他每天经历了费用的变动后会前往下一个城市。他会选择获得利润最大的，如有多个相同则选择编号最小的，但他不能呆在原来的城市不走。


## 说明/提示

$n,q \le 10^5,1 \le z_i \le 10^{18}$​​, $1 \le w \le 10^{12}$

## 样例 #1

### 输入

```
4 4
10 20 30 50
1 2 5
2 3 7
2 4 57
1 3 28
1 1 25
2 3 2 1
2 2 4 13```

### 输出

```
3 1 3 4```

# 题解

## 作者：kraylas (赞：10)

~~对于树上所有路径的问题显然可以点分治~~

但是点分治难写怎么办

因为是每次从一个点出发，所以可以想到LCT

考虑如何用LCT维护这个东西

因为是一个点的权值减去一条链的权值

所以可以在splay上维护从splay最左边和最右边（因为要翻转）到某一个点的答案最大值

但当前点到其他点显然不是只有一条链

只有一条链的splay好像并不能很好维护这个东西

所以考虑维护虚边

因为一个点的虚边有好多，而且我们要求最大值，而且要支持删除，用`set`可以很好维护

所以第一步的思路就出来了:

- 拆边为点，维护边权和点权(一个点边权为0，一个边点权为-inf)
- 维护splay上从最左边开始到这条链以及所有虚边链接的点的最优答案，和从右开始的最优答案

一个节点维护三个权值表示边权，点权，splay上这个点子树的边权和

再维护两个最大值表示从左和从右的最优答案


```cpp
struct Node{
	Node  *ch[2],*fa;
    int64 pval,eval,sum; //点权，边权，边权和
    Value lmax,rmax;     //左右答案
    set<Value> imax;     //虚边
};
```

然后考虑怎样合并这些信息（也就是push_up）

先考虑sum

很显然sum就是左右两子树的sum之和加上自己的边权

然后是lmax

分为四部分

1. 左边的lmax
2. 左边的sum+自己的边权+虚边上的最大值
3. 左边的sum+自己边权+右子树最大值
4. 左边的sum+自己点权


rmax同理

所以up函数也可以写出来了

```cpp
void up(ptr x){
	x->sum=x->eval+x->ch[0]->sum+x->ch[1]->sum;
	Value imax=x->imax.size()? *x->imax.rbegin():Value(-inf,0);
	x->lmax=max(x->ch[0]->lmax,x->ch[0]->sum+
				max(
					x->eval+max(imax,x->ch[1]->lmax),
					Value(x->pval,x-pool)
				)
			);
	x->rmax=max(x->ch[1]->rmax,x->ch[1]->sum+
				max(
					x->eval+max(imax,x->ch[0]->rmax),
					Value(x->pval,x-pool)
				)
			);
}
```


然后就是LCT板子了，注意`access`的时候把虚边维护好就可以了

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
template<class T> T read(){
	T s,f=1;char ch;
	while(!isdigit(ch=getchar()))(ch=='-')&&(f=-1);
	for(s=ch-'0';isdigit(ch=getchar());s=s*10+ch-'0');
	return s*f;
}
namespace cmp{
template<class T> bool chkmax(T &a,const T &b){return a<b? a=b,1:0;}
template<class T> bool chkmin(T &a,const T &b){return b<a? a=b,1:0;}
}
const int maxn = 1e5+5;
const long long inf = 1LL<<62;
typedef long long int64;


int (*_)()=read<int>;

struct Value{
	int64 val;
	int id;
	Value(int64 val=0,int id=0):val(val),id(id){}
	friend bool operator < (const Value &a,const Value &b){
		return a.val==b.val? a.id>b.id:a.val<b.val;
	}
	friend Value operator + (const int64 &a,const Value &b){
		return Value(b.val+a,b.id);
	}
};


struct Node{
	Node *ch[2],*fa;
	int64 pval,eval,sum;
	Value lmax,rmax;
	bool rev;
	set<Value> imax;
}pool[maxn*2];
typedef Node *ptr;
ptr null=&pool[0];

Node *Nodeinit(Node *p){
	p->ch[0]=p->ch[1]=null;
	p->fa=null;
	p->pval=p->eval=p->sum=0;
	p->lmax=p->rmax=Value(0,0);
	p->rev=0;
	p->imax.clear();
	return p;
}

bool ntr(ptr x){return x->fa->ch[0]==x||x->fa->ch[1]==x;}
bool getd(ptr x){return x->fa->ch[1]==x;}
void up(ptr x){
	x->sum=x->eval+x->ch[0]->sum+x->ch[1]->sum;
	Value imax=x->imax.size()? *x->imax.rbegin():Value(-inf,0);
	x->lmax=max(x->ch[0]->lmax,x->ch[0]->sum+
				max(
					x->eval+max(imax,x->ch[1]->lmax),
					Value(x->pval,x-pool)
				)
			);
	x->rmax=max(x->ch[1]->rmax,x->ch[1]->sum+
				max(
					x->eval+max(imax,x->ch[0]->rmax),
					Value(x->pval,x-pool)
				)
			);
}

void r(ptr p){
	swap(p->ch[0],p->ch[1]);
	swap(p->lmax,p->rmax);
	p->rev^=1;
}

void down(ptr x){
	if(!x->rev)return ;
	if(x->ch[0]!=null) r(x->ch[0]);
	if(x->ch[1]!=null) r(x->ch[1]);
	x->rev=0;
}

void rot(ptr x){
	ptr y=x->fa,z=y->fa;int k=getd(x);ptr w=x->ch[!k];
	if(ntr(y))z->ch[getd(y)]=x;
	x->fa=z;y->fa=x;x->ch[!k]=y;y->ch[k]=w;
	if(w!=null) w->fa=y;
	up(y);
}

void splay(ptr x){
	static ptr st[maxn];
	int top;st[top=1]=x;
	while(ntr(st[top])) st[top+1]=st[top]->fa,top++;
	while(top)down(st[top--]);
	for(;ntr(x);rot(x))
		if(ntr(x->fa)) rot(getd(x->fa)==getd(x)? x->fa:x);
	up(x);
}

void access(ptr x){
	for(ptr y=null;x!=null;x=(y=x)->fa){
		splay(x);
		if(y!=null)
			x->imax.erase(y->lmax);
		if(x->ch[1]!=null)
			x->imax.insert(x->ch[1]->lmax);
		x->ch[1]=y;
		up(x);
	}
}

void makeroot(ptr x){
	access(x);
	splay(x);
	r(x);
}

void link(ptr x,ptr f){
	makeroot(x);
	access(f);
	splay(f);
	x->fa=f;
	f->imax.insert(x->lmax);
	up(f);
}

unordered_map<int64,int>edge;
int64 encode(int x,int y){if(x>y)swap(x,y); return (1LL*x)<<32|y; }
int n,m,q;
int main(){
	Nodeinit(null);
	null->lmax=null->rmax=Value(-inf,n+1);
	null->sum=0;
	n=_();q=_();
	for(int i=1;i<n*2;++i)
		Nodeinit(pool+i);
	for(int i=1;i<=n;++i)
		pool[i].pval=read<int64>(),up(pool+i);
	for(int i=1;i<n;++i){
		int x=_(),y=_();
		int64 z=read<int64>();
		pool[i+n].eval=-z;
		pool[i+n].pval=-inf;
		link(pool+x,pool+i+n);
		link(pool+y,pool+i+n);
		edge[encode(x,y)]=i;
	}
	makeroot(pool+1);
	int nowpos=1;
	for(int i=1;i<=q;++i){
		int op=_();
		if(op==1){
			int x=_();
			int64 z=read<int64>();
			access(pool+x);
			splay(pool+x);
			pool[x].pval=z;
			up(pool+x);
		}else{
			int x=_(),y=_();
			int64 z=read<int64>();
			int id=edge[encode(x,y)]+n;
			access(pool+id);
			splay(pool+id);
			pool[id].eval=-z;
			up(pool+id);
		}
		access(pool+nowpos);
		splay(pool+nowpos);

		int64 tmp=pool[nowpos].pval;
		pool[nowpos].pval=-inf;
		up(pool+nowpos);

		int ans=pool[nowpos].lmax.id;
		pool[nowpos].pval=tmp;
		up(pool+nowpos);

		nowpos=ans;
		makeroot(pool+nowpos);
		printf("%d%c",nowpos,i==q? '\n':' ');
	}
	return 0;
}
```
让我们一起膜拜大佬[olinr](https://www.luogu.org/space/show?uid=88460)

---

## 作者：lhm_ (赞：4)

考虑用动态点分治来解决像本题这样带修的树上路径问题。

首先对原树进行点分治，建出点分树，在点分树每个节点上用动态开点线段树来维护以该节点为起点，到其点分树子树中每个节点的利润。

查询时只需在点分树上当前所在节点往上跳父亲，在其到点分树根节点的链上的每个节点的线段树上查询。跳到一个节点时，在线段树上查询除了当前节点的利润最大值，同时加上其到当前节点的花费。

修改点权只需在点分树上往上跳父亲，在线段树上单点修改即可。

考虑边权的修改影响的是当前根所对应的一个子树，对于边权的修改，从其两个端点在点分树上深度更大，即点分治递归层数更深的点开始往上跳父亲，每次修改在原树上以当前节点为根，深度更浅的那个端点。

点分树上每个节点的线段树在维护时以节点的 $dfs$ 序为下标，修改子树信息只需在线段树上区间修改即可。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 100010
#define maxm 200010
#define maxt 3500010
#define inf 1000000000000000
#define mid ((l+r)>>1)
#define mk make_pair
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,q,tree_cnt,dfn_cnt,tot,root,pos=1;
int fa[maxn],ma[maxn],siz[maxn],num[maxn],d[maxn];
int rt[maxn],ls[maxt],rs[maxt],in[20][maxn],out[20][maxn];
ll v[maxn],tag[maxt];
bool vis[maxn];
map<pair<int,int>,ll> w;
struct edge
{
    int to,nxt;
    ll v;
}e[maxm];
int head[maxn],edge_cnt;
void add(int from,int to,ll val)
{
    e[++edge_cnt]=(edge){to,head[from],val};
    head[from]=edge_cnt;
}
struct node
{
    ll val;
    int id;
}t[maxt];
bool operator <(const node &a,const node &b)
{
    if(a.val==b.val) return a.id>b.id;
    return a.val<b.val;
}
void pushtag(int cur,ll v)
{
    t[cur].val+=v,tag[cur]=v;
}
void pushdown(int cur)
{
    if(!tag[cur]) return;
    pushtag(ls[cur],tag[cur]),pushtag(rs[cur],tag[cur]),tag[cur]=0;
}
void insert(int l,int r,int pos,ll v,int id,int &cur)
{
    if(!cur) cur=++tree_cnt;
    if(l==r)
    {
        t[cur]=(node){v,id};
        return;
    }
    if(pos<=mid) insert(l,mid,pos,v,id,ls[cur]);
    else insert(mid+1,r,pos,v,id,rs[cur]);
    t[cur]=max(t[ls[cur]],t[rs[cur]]);
}
void modify(int L,int R,int l,int r,ll v,int &cur)
{
    if(!cur) cur=++tree_cnt;
    if(L<=l&&R>=r)
    {
        pushtag(cur,v);
        return;
    }
    pushdown(cur);
    if(L<=mid) modify(L,R,l,mid,v,ls[cur]);
    if(R>mid) modify(L,R,mid+1,r,v,rs[cur]);
    t[cur]=max(t[ls[cur]],t[rs[cur]]);
}
node query(int L,int R,int l,int r,int cur)
{
    if(L>R||!cur) return (node){-inf,0};
    if(L<=l&&R>=r) return t[cur];
    pushdown(cur);
    if(R<=mid) return query(L,R,l,mid,ls[cur]);
    if(L>mid) return query(L,R,mid+1,r,rs[cur]);
    return max(query(L,R,l,mid,ls[cur]),query(L,R,mid+1,r,rs[cur]));
}
void dfs_root(int x,int fath)
{
    siz[x]=1,ma[x]=0;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(vis[y]||y==fath) continue;
        dfs_root(y,x),siz[x]+=siz[y],ma[x]=max(ma[x],siz[y]);
    }
    ma[x]=max(ma[x],tot-siz[x]);
    if(ma[x]<ma[root]) root=x;
}
void dfs_dis(int x,int fath,ll dis,int id)
{
    in[d[id]][x]=++dfn_cnt,insert(1,num[id],dfn_cnt,v[x]-dis,x,rt[id]);
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(vis[y]||y==fath) continue;
        dfs_dis(y,x,dis+e[i].v,id);
    }
    out[d[id]][x]=dfn_cnt;
}
void solve(int x,int depth)
{
    int now=tot;
    d[x]=depth,vis[x]=true,num[x]=now,dfn_cnt=0,dfs_dis(x,0,0,x);
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(vis[y]) continue;
        root=0,tot=siz[y];
        if(siz[y]>siz[x]) tot=now-siz[x];
        dfs_root(y,x),fa[root]=x,solve(root,depth+1);
    }
}
int main()
{
    read(n),read(q);
    for(int i=1;i<=n;++i) read(v[i]);
    for(int i=1;i<n;++i)
    {
        int x,y;
        ll v;
        read(x),read(y),read(v);
        add(x,y,v),add(y,x,v);
        if(x>y) swap(x,y);
        w[mk(x,y)]=v;
    }
    tot=ma[0]=n,dfs_root(1,0),solve(root,1);
    while(q--)
    {
        int opt,x,y,p;
        ll val,t;
        node ans=(node){-inf,0};
        read(opt);
        if(opt==1)
        {
            read(x),read(val);
            for(int i=x;i;i=fa[i])
                modify(in[d[i]][x],in[d[i]][x],1,num[i],val-v[x],rt[i]);
            v[x]=val;
        }
        else
        {
            read(x),read(y),read(val);
            if(x>y) swap(x,y);
            t=w[mk(x,y)]-val,w[mk(x,y)]=val;
            if(d[x]<d[y]) p=x;
            else p=y;
            while(p)
            {
                if(in[d[p]][x]>in[d[p]][y]) modify(in[d[p]][x],out[d[p]][x],1,num[p],t,rt[p]);
                else modify(in[d[p]][y],out[d[p]][y],1,num[p],t,rt[p]);
                p=fa[p];
            }
        }
        for(int i=pos;i;i=fa[i])
        {
            node now=max(query(1,in[d[i]][pos]-1,1,num[i],rt[i]),query(in[d[i]][pos]+1,num[i],1,num[i],rt[i]));
            now.val+=query(in[d[i]][pos],in[d[i]][pos],1,num[i],rt[i]).val-v[pos],ans=max(ans,now);
        }
        printf("%d ",pos=ans.id);
    }
    return 0;
}
```

---

## 作者：jucason_xu (赞：3)


_是夜萧索漏星光，一秋叶打漫天霜。钟响，卷地西风扫鸿芒。_

_求索那堪路漫长，重心剖树早相忘。清唱，时空阻限又何妨？_

### PA-2017 Banany

考虑点分树。先把点分树建出来再考虑更多的事情。

对每个分治子树，维护分治子树内所有点到当前分治重心的距离加价值的最大值。考虑使用数据结构进行维护。这里我们选用动态开点线段树，按照原树上的 dfn 序建树。

#### 修改：在潺潺的雨雾里筛出虹

那么，对于修改点权的操作就比较方便，将 $val_i$ 修改为 $z$ 只需要对于 $x$ 在分治树上的所有父亲进行单点修改。

考虑如何进行修改边权。我们发现在修改 $(x,y)$ 边权为 $z$ 的过程中，有如下的性质：

+ 在分治树上，$x,y$ 中的一个是另一个的祖先

这个很好证明，考虑第一个包含 $(x,y)$ 的分治子树，必然是 $x$ 或者 $y$ 作为分治重心。

那么，我们就选取在分治树上的祖先作为 $y$，另一个作为 $x$。

然后考虑什么会改变，如果一个分治子树包含 $(x,y)$ 这条边，那么如果我们将子树在原树上按照这条边分成两部分，分治重心到另一部分的所有点的距离会增加 $z-last_{x,y}$。

那么我们考虑如何进行操作。我们发现，我们可以直接把整棵树用 $(x,y)$ 分成两部分，设在原树以 $1$ 为根开始 dfs 的情况下，$x$ 是 $y$ 的儿子，一部分是区间 $[dfn_x,dfn_x+sz_x-1]$，另一部分是 $[1,dfn_x-1]\cup[dfn_x+sz_x,n]$。我们可以直接在当前根上把另一部分整体加 $z-last_{x,y}$。在 modify 的过程中不增加新节点，不属于当前分治子树的部分虽然加了但是会被自动忽略。

这样，我们就需要维护动态开点线段树的区间加。从 $x$ 开始找到分治树的所有父亲，用 dfn 序判断当前的 $cur$ 在 $x$ 那一半还是 $y$ 那一半上，然后分类讨论进行修改。

#### 查询：心灵深处的誓约

最后考虑如何查询。假设我们处在 $x$，那么我们可以跳 $x$ 在分治树的父亲，假设它是 $cur$。接着在 $cur$ 的线段树上查找离 $cur$ 权值最大的点。将权值加上 $x$ 到 $cur$ 的路径长度，得到它到 $x$ 的距离。在一般的点分树上，这样做是需要先排除掉 $cur$ 分向 $x$ 的子树的点。但是现在边权造成的贡献是负的，也就是应当尽量少走边，那么可能被 $cur$ 扫到的不合法的点一定可以从 $x$ 的更低的祖先用更少的花费走到，所以不需要考虑。

但是这样还是存在问题，我们得到的最优解可能是当前点。为了维护这个问题，我们需要在线段树上维护一下次大值。

不过，还有一个问题，就是如何计算“$x$ 到 $cur$ 的路径长度。我们首先的想法是通过 lca 和树上倍增来计算。

参考如下代码

```cpp
namespace Distance{
	int Fa[100005][21],Dep[100005];ll F[100005][21];
	int Dfn[100005],Ti,Sz[100005]; 
	inline void build_distance(int x,int p,ll pval){
		Fa[x][0]=p,F[x][0]=pval,Dep[x]=Dep[p]+1,Dfn[x]=++Ti,Sz[x]=1;
		rep(i,1,20)Fa[x][i]=Fa[Fa[x][i-1]][i-1];
		rep(i,1,20)F[x][i]=F[x][i-1]+F[Fa[x][i-1]][i-1];
		for(auto e:tr[x])if(e.b!=p)build_distance(e.b,x,e.w),Sz[x]+=Sz[e.b];
	}
	inline int lca(int x,int y){
		if(Dep[x]<Dep[y])swap(x,y);
		per(i,0,20)if(Dep[Fa[x][i]]>=Dep[y])x=Fa[x][i];
		if(x==y)return x;
		per(i,0,20)if(Fa[x][i]!=Fa[y][i])x=Fa[x][i],y=Fa[y][i];
		return Fa[x][0];
	}
	inline int distance(int x,int y){
		ll res=0;
		per(i,0,20)if(Dep[Fa[x][i]]>=Dep[y]){
			res+=F[x][i];
			x=Fa[x][i];
		}return res;
	}
	inline int dis(int x,int y){
		int z=lca(x,y);
		return distance(x,z)+distance(y,z);
	}
}using namespace Distance;
```

但是这样存在问题。因为我们需要的距离是可能因为边权的修改而变化的。树上倍增显然是静态的。

对于此类问题，我们就能想到树剖，通过树剖解决树上两点动态距离。然而树剖查询动态距离本身是 $O(\log^2n)$ 的，如果这样做，复杂度就会来到 $O(n\log^3 n)$。

我们发现，整个程序中只有这里一处地方需要查找距离，而且满足性质 $cur$ 是 $x$ 在点分树上的祖先。那么我们发现其实我们在线段树上已经存储了 $cur$ 到 $x$ 的距离加上 $val_x$ 了，而 $val_x$ 是已知的，我们就可以直接在线段树 $cur$ 上单点查询得到距离了。

#### 实现：来途一片血污，却笑称都是虚无

首先困扰我们的是次大值的维护，我们不仅要维护最大值，次大值，还要维护它们对应的点。

我们可以设立特殊的结构体 `mxx` 和 `twomax` ， `mxx` 用来维护最值和它对应的位置，还要支持在值相同时小编号优先，方便的插入比较和更改数值。如果用 `pair<int,int>` 实现函数就略显繁琐，不如自己定义数据类型，实现 `operator` ，保证程序简单易懂。`twomax` 维护两个 `mxx` ，最大值和次大值，要支持插入 `mxx` ，保证编号不同，以及两个 `twomax` 的合并。

```cpp
struct twomax{
	struct mxx{
		int m;ll v;
		mxx(int _m,ll _v){
			m=_m,v=_v;
		}
		mxx(){
			m=-1,v=-4e18;
		}
		void operator +=(const ll b){
			v+=b;
		}
		bool operator >(const mxx b)const{
			if(v==b.v)return m<b.m;
			return v>b.v;
		}
	}r1,r2;
	twomax(){
		r1=mxx();r2=mxx();
	}
	twomax(int x,ll v){
		r1=mxx(x,v);r2=mxx();
	}
	void operator +=(const mxx b){
		if(b>r1){
			if(r1.m!=b.m)r2=r1;
			r1=b;
		}
		else if(b>r2&&b.m!=r1.m)r2=b;
	}
	void operator +=(const ll b){
		r1+=b,r2+=b;
	}
	twomax operator +(twomax b){
		twomax res=b;
		res+=r1;res+=r2;
		return res;
	}
};
```

同时还利用了 C++ 对于相同的运算符或函数根据运算的数据类型进行区分的特性，调用更加方便。

然后是线段树，我们需要支持动态开点和区间加法。而区间加的过程中是不增加新点的，我们还要在 `modify` 之外单独实现增加新点的单点修改 `build` 。

因为我们的 `twomax` 是使用运算符来操控的，好处就在于线段树可以直接用板子，非常方便。

```cpp

namespace Segtree{
	struct node{
		int ls,rs;ll tg;twomax res;
	}sg[4680005];
	int cnt=0;
	inline int newnode(){
		int x=++cnt;
		sg[x].res=twomax();sg[x].ls=0,sg[x].rs=0;
		return x;
	}
	inline void update(int i){
		sg[i].res=(sg[sg[i].ls].res+sg[sg[i].rs].res);
	}
	inline void pushdown(int i){
		if(!i||!sg[i].tg)return;
		sg[i].res+=sg[i].tg;
		if(sg[i].ls)sg[sg[i].ls].tg+=sg[i].tg;
		if(sg[i].rs)sg[sg[i].rs].tg+=sg[i].tg;
		sg[i].tg=0;
	} 
	inline void build(int &i,int x,int ix,ll v,int l,int r){
		if(!i)i=newnode();
		pushdown(i);
		if(l==r){
			sg[i].res=twomax(ix,v);
			return;
		}int mid=(l+r)>>1;
		if(x<=mid)build(sg[i].ls,x,ix,v,l,mid);
		else build(sg[i].rs,x,ix,v,mid+1,r);
		update(i);
	}
	inline void modify(int i,int L,int R,ll v,int l,int r){
		if(!i)return;
		pushdown(i);
		if(L>r||R<l)return;
		if(L<=l&&r<=R){
			sg[i].tg+=v;
			pushdown(i);
			return;
		}
		int mid=(l+r)>>1;
		modify(sg[i].ls,L,R,v,l,mid);
		modify(sg[i].rs,L,R,v,mid+1,r);
		update(i);
	}
	inline ll qry(int i,int x,int l,int r){
		pushdown(i);
		if(l==r)return sg[i].res.r1.v;
		int mid=(l+r)>>1;
		ll res=0;
		if(x<=mid){
			res=qry(sg[i].ls,x,l,mid);
			pushdown(sg[i].rs);
		}else {
			res=qry(sg[i].rs,x,mid+1,r);
			pushdown(sg[i].ls);
		}update(i);
		return res;
	}
}using namespace Segtree;
```

然后主程序需要实现四个函数：

+ `Build_Vertex(x,y)` 建立 $x$ 的点权为 $y$，在线段树上新建点

+ `Modify_Vertex(x,y)` 将 $x$ 的点权 __增加__ $y$

+ `Modify_Edge(x,y)` 将边 $(x,y)$ 的权值修改为 $y$

+ `Query(x)` 从点 $x$ 开始找到最近的点。

这四个函数都是 $O(\log^2 n)$ 的，其中 `Modify_Edge(x,y)` 常数最大（涉及到 $\log$ 次区间加）

```cpp

inline void build_vert(int x,ll y){
	int cur=x;
	while(cur!=0){
		build(root[cur],dfn[x],x,y,1,n);
		cur=fa[cur];
	}
}
inline void modify_vert(int x,ll y){
	int cur=x;
	while(cur!=0){
		modify(root[cur],dfn[x],dfn[x],y,1,n);
		cur=fa[cur];
	}
}
inline void modify_edge(int x,int y,ll z){
	if(Divid::lay[x]<Divid::lay[y])swap(x,y);
	int cur=x;
	while(cur){
		if(bothside(cur,y,x)){
			if(dfn[x]<=dfn[y]){
				modify(root[cur],1,dfn[y]-1,z,1,n);
				modify(root[cur],dfn[y]+sz[y],n,z,1,n);
			}else{
				modify(root[cur],dfn[x],dfn[x]+sz[x]-1,z,1,n);
			}
		}else{
			if(dfn[y]<=dfn[x]){
				modify(root[cur],1,dfn[x]-1,z,1,n);
				modify(root[cur],dfn[x]+sz[x],n,z,1,n);
			}else{
				modify(root[cur],dfn[y],dfn[y]+sz[y]-1,z,1,n);
			}
		}
		cur=fa[cur];
	}
}
inline int query(int x){
	twomax ans=sg[root[x]].res;
	int cur=fa[x];
	while(cur!=0){
		twomax res=sg[root[cur]].res;
		res+=dis(x,cur);
		ans=(ans+res),cur=fa[cur];
	}
	if(ans.r1.m==x){
		return ans.r2.m;
	}
	return ans.r1.m;
}
```

#### 卡常：此处即为空间的界限，只得到此，不得僭越

我们分析这个算法的空间复杂度。看上去，每个点贡献 $\log n$ 次，每次增加 $\log n$ 的代价这个算法是 $O(n\log^2 n)$ 的空间复杂度。但是这样是可以直接用二叉树卡掉的，果真如此吗？

我们分析二叉树如何卡这个算法，然后我们发现，二叉树上顶端的点几乎都是满的，而满的线段树是 $O(n)$ 的。所以“上面”的点每个点再怎么多也不会超过 $O(n)$ 个。

然后我们根号分析。深度不超过 $\dfrac{\log_2 n}{2}$ 的 $\sqrt{n}$ 个点（$2^{(\log_2 n)/2}=\sqrt{2^{\log_2 n}}=\sqrt{n}$），我们就假设它们都是满的，总空间 $O(n\sqrt{n})$。对于深度超过 $\dfrac{\log n}{2}$ 的点，每个点最多管辖 $\sqrt{n}$ 个点（和上面同理），总空间也是 $O(n\sqrt{n})$。

所以，我们把这个算法的空间复杂度上界分析到了 $O(n\sqrt{n})$，但是凭借这个空间复杂度也是不太可能通过的。我们还需要进一步收缩上界。

在了解正解之前，我们需要了解本题的另一个算法。

也就是，我们在每个分治重心内部将其管辖的所有节点排列，建出完整的线段树。对 $n$ 个点建立线段树是 $O(n)$ 的。而每个点会被贡献 $O(n\log n)$ 次，所以总的空间复杂度显而易见是 $O(n\log n)$ 的。

然后我们考虑现在的做法，其实，我们每个分治子树，对应到线段树的坐标上也是一段近似区间的部分。所以我们其实是对这个区间建立了一个类似满二叉树的东西，然后从根连了一条链到这个小线段树。那么，我们的做法也是 $O(n\log n)$ 的。

而且，这个做法相较于显然 $O(n\log n)$ 的做法还是存在优势的。因为建立完整的线段树理论所需要的空间是 $2n$，但是实际上为了下标访问的合法性，我们需要 $4n$ 的空间来建立。在只有 `250MB` 的题目上，这多出来的开销是致命的，致使我们不得不使用内存池等手段优化。

但是动态开点线段树天然不会存在这个下标访问合法的问题，所以轻轻松松就能卡进原题的空间限制。

```cpp
struct edge{
	int b;ll w;
	edge(int _b,ll _w){
		b=_b,w=_w;
	}
};
int n,m,t,x,y;ill z,val[100005];
int root[100005],fa[100005];
vt<edge>tr[100005],vv[100005];
int dfn[100005],sz[100005],ti;
namespace Divid{
	int lay[100005],del[100005];
	inline void getsz(int x,int p){
		sz[x]=1;
		for(auto e:tr[x])if(!del[e.b]&&e.b!=p){
			getsz(e.b,x);sz[x]+=sz[e.b];
		}
	}
	inline int getcen(int x,int p,int tot){
		for(auto e:tr[x])if(!del[e.b]&&e.b!=p){
			if(2*sz[e.b]>=tot)return getcen(e.b,x,tot);
		}return x;
	}
	inline int Build(int x,int l){
		getsz(x,0);int s=getcen(x,0,sz[x]);
		del[s]=1;lay[s]=l;
		for(auto e:tr[s])if(!del[e.b]){
			int ls=Build(e.b,l+1);
			fa[ls]=s;vv[s].pb({ls,0});
		}
		return s;
	}
}
struct twomax{
	struct mxx{
		int m;ll v;
		mxx(int _m,ll _v){
			m=_m,v=_v;
		}
		mxx(){
			m=-1,v=-4e18;
		}
		void operator +=(const ll b){
			v+=b;
		}
		bool operator >(const mxx b)const{
			if(v==b.v)return m<b.m;
			return v>b.v;
		}
	}r1,r2;
	twomax(){
		r1=mxx();r2=mxx();
	}
	twomax(int x,ll v){
		r1=mxx(x,v);r2=mxx();
	}
	void operator +=(const mxx b){
		if(b>r1){
			if(r1.m!=b.m)r2=r1;
			r1=b;
		}
		else if(b>r2&&b.m!=r1.m)r2=b;
	}
	void operator +=(const ll b){
		r1+=b,r2+=b;
	}
	twomax operator +(twomax b){
		twomax res=b;
		res+=r1;res+=r2;
		return res;
	}
};
namespace Segtree{
struct node{
	int ls,rs;ll tg;twomax res;
}sg[4680005];
int cnt=0;
inline int newnode(){
	int x=++cnt;
	sg[x].res=twomax();sg[x].ls=0,sg[x].rs=0;
	return x;
}
inline void update(int i){
	sg[i].res=(sg[sg[i].ls].res+sg[sg[i].rs].res);
}
inline void pushdown(int i){
	if(!i||!sg[i].tg)return;
	sg[i].res+=sg[i].tg;
	if(sg[i].ls)sg[sg[i].ls].tg+=sg[i].tg;
	if(sg[i].rs)sg[sg[i].rs].tg+=sg[i].tg;
	sg[i].tg=0;
} 
inline void build(int &i,int x,int ix,ll v,int l,int r){
	if(!i)i=newnode();
	pushdown(i);
	if(l==r){
		sg[i].res=twomax(ix,v);
		return;
	}int mid=(l+r)>>1;
	if(x<=mid)build(sg[i].ls,x,ix,v,l,mid);
	else build(sg[i].rs,x,ix,v,mid+1,r);
	update(i);
}
inline void modify(int i,int L,int R,ll v,int l,int r){
	if(!i)return;
	pushdown(i);
	if(L>r||R<l)return;
	if(L<=l&&r<=R){
		sg[i].tg+=v;
		pushdown(i);
		return;
	}
	int mid=(l+r)>>1;
	modify(sg[i].ls,L,R,v,l,mid);
	modify(sg[i].rs,L,R,v,mid+1,r);
	update(i);
}
inline ll qry(int i,int x,int l,int r){
	pushdown(i);
	if(l==r)return sg[i].res.r1.v;
	int mid=(l+r)>>1;
	ll res=0;
	if(x<=mid){
		res=qry(sg[i].ls,x,l,mid);
		pushdown(sg[i].rs);
	}else {
		res=qry(sg[i].rs,x,mid+1,r);
		pushdown(sg[i].ls);
	}update(i);
	return res;
}
}using namespace Segtree;
namespace Distance{
inline void build_distance(int x,int p){
	dfn[x]=++ti,sz[x]=1;
	for(auto e:tr[x])if(e.b!=p)build_distance(e.b,x),sz[x]+=sz[e.b];
}
inline ll dis(int x,int y){
	ll res=qry(root[y],dfn[x],1,n)-val[x];
	return res;
}
inline bool bothside(int z,int y,int x){
	if(dfn[x]<=dfn[y]){//x是y的祖先 
		return (dfn[y]<=dfn[z]&&dfn[z]<dfn[y]+sz[y]);
	}else{//y是x的祖先 
		return !(dfn[x]<=dfn[z]&&dfn[z]<dfn[x]+sz[x]);
	}
}
}using namespace Distance;
int rt=0;
inline void build_vert(int x,ll y){
	int cur=x;
	while(cur!=0){
		build(root[cur],dfn[x],x,y,1,n);
		cur=fa[cur];
	}
}
inline void modify_vert(int x,ll y){
	int cur=x;
	while(cur!=0){
		modify(root[cur],dfn[x],dfn[x],y,1,n);
		cur=fa[cur];
	}
}
inline void modify_edge(int x,int y,ll z){
	if(Divid::lay[x]<Divid::lay[y])swap(x,y);
	int cur=x;
	while(cur){
		if(bothside(cur,y,x)){
			if(dfn[x]<=dfn[y]){
				modify(root[cur],1,dfn[y]-1,z,1,n);
				modify(root[cur],dfn[y]+sz[y],n,z,1,n);
			}else{
				modify(root[cur],dfn[x],dfn[x]+sz[x]-1,z,1,n);
			}
		}else{
			if(dfn[y]<=dfn[x]){
				modify(root[cur],1,dfn[x]-1,z,1,n);
				modify(root[cur],dfn[x]+sz[x],n,z,1,n);
			}else{
				modify(root[cur],dfn[y],dfn[y]+sz[y]-1,z,1,n);
			}
		}
		cur=fa[cur];
	}
}
inline int query(int x){
	twomax ans=sg[root[x]].res;
	int cur=fa[x];
	while(cur!=0){
		twomax res=sg[root[cur]].res;
		res+=dis(x,cur);
		ans=(ans+res),cur=fa[cur];
	}
	if(ans.r1.m==x){
		return ans.r2.m;
	}
	return ans.r1.m;
}
map<int,ll>mp[100005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	sg[0].res=twomax();
	rp(i,n)cin>>val[i];
	rp(i,n-1){
		cin>>x>>y>>z;z=-z;
		tr[x].pb({y,z});mp[y][x]=z;
		tr[y].pb({x,z});mp[x][y]=z;
	}
	rt=Divid::Build(1,0);
	build_distance(1,0);
	rp(i,n)build_vert(i,val[i]);
	rp(i,n)for(auto e:tr[i])if(e.b<i){
		modify_edge(e.b,i,e.w);
	}
	int ans=1;
	rp(_,m){
		cin>>t;
		if(t==1){
			cin>>x>>z;
			modify_vert(x,z-val[x]);
			val[x]=z;
		}else{
			cin>>x>>y>>z;z=-z;
			modify_edge(x,y,z-mp[x][y]);
			mp[x][y]=mp[y][x]=z;
		}ans=query(ans);
		cout<<ans<<" ";
	}
	return 0;
}
//Crayan_r
```

---

## 作者：slenbol (赞：3)

## 洛谷 P4695 Banany 题解

[题目链接](https://www.luogu.com.cn/problem/P4695)

### 题目描述

给你一棵 $n$ 个节点的树，每个节点有权值 $w_i$，每一条边有权值 $v_i$。定义从 $s$ 到 $t$ 的路径的权值为 $w_t-\sum_{e \in path(s,t)} v_e$。一共有 $q$ 次询问，每次询问为修改一个点权或修改边权后，从当前节点出发，能到达的权值最大的点。若有多个权值相同的点选择编号最小的点作为终点，注意，询问后一定需要挪动到其他点，不可以呆着不走。初始时，你在 $1$ 号节点。

### 题目分析

先考虑单次询问，不修改的情况。

因为贡献式与根无关，所以不妨设根为 $1$ 。

考虑将 $\sum _{e \in path(s,t)}v_e$ 拆成 $dis(s)+dis(t)-2 \times dis(lca)$ 其中 $lca$ 表示 $s$ 和 $t$ 的最近公共祖先，$dis(x)$ 为从根到 $x$ 的路径的长度。

那么我们可以枚举 $t$，利用[欧拉序求最近公共祖先](https://oiwiki.com/graph/lca/#%E7%94%A8%E6%AC%A7%E6%8B%89%E5%BA%8F%E5%88%97%E8%BD%AC%E5%8C%96%E4%B8%BA-rmq-%E9%97%AE%E9%A2%98) 以及预处理 $dis(x)$ 可以做到单次 $O(1)$ 的更新答案。

总时间复杂度 $O(n)$。

再考虑不带修但是多次询问不同起点的简化问题。

因为我们是从 $s$ 出发去寻找 $t$ 的，所以 $dis(s)$ 是固定的。

这启发我们在 $lca$ 处统计点对 $s$ 到 $t$ 的贡献。

写出只与 $lca$ 和 $t$ 有关的贡献式，也就是 $2 \times dis(lca)+w_t-dis(t)$ 。因为我们在枚举 $lca$ 统计答案，所以 $dis(lca)$ 也是定值，即能作出贡献的就是 $lca$ 子树中的点。

但是这样统计可能会重复。设 $p$ 为 $lca$ 的祖先。则我们在 $p$ 处同样会统计到 $t$ 的贡献，但是 $s$ 与 $t$ 的最近公共祖先不是 $p$。

虽然如此，因为边权没有负边权，所以 $dis(p)<dis(lca)$。这就意味着，虽然我们重复统计 $t$，但是在 $p$ 统计一定比在 $lca$ 统计劣，所以这样统计是正确的。

同时，这种统计方法也说明在不同的 $s$ 的情况下，如果我们没有修改边权与点权，那么我们会选择同样的 $t$ 作为终点，除了 $t$ 本身。

考虑枚举 $lca$，根据上述证明，我们只需要找到在 $lca$ 子树中，拥有最大 $w_t-dis(t)$ 的 $t$ 与次大的 $t'$ 即可。（需要 $t'$ 是因为不能停留在同一个点，所以需要次大值来更新）。这可以使用 $O(n)$ 的深搜来实现。

时间复杂度 $O(n)$。

现在我们解决了不带修的多次询问起点的简化问题。

考虑带修改的怎么做。

首先总结下这道题的性质：

- 暴力更新答案是朴素的，即我们可以 $O(1)$ 计算 $t$ 对 $s$ 的贡献。
- 在不带修的情况下对于不同的 $s$ 我们需要维护的东西是相同的。

这两点，启发我们使用对询问分块这种做法。

具体的，我们每 $\sqrt n$ 个询问分段，暴力重构一次原树。其中，重构定义为将简化问题中需要维护的 $t$ 与 $t'$ 通过 $O(n)$ 暴力维护出来，但我们并不维护在这 $\sqrt n$ 中被修改点权的点所作出的贡献。并且，我们将修改过边权的边标记出来，这样原树最多被分成 $\sqrt n$ 个子树。

考虑将问题转化为一下几个部分计算：

- $lca$ 与 $t$ 在同一个子树内，且 $t$ 并未修改过。
- $lca$ 与 $t$ 不在同一子树内，且 $t$ 并未修改过。
- $t$ 的点权在这 $\sqrt n$ 个操作中被修改过。

容易发现，这三种情况包含了所有可能的贡献情况。

第一部分 $lca$ 与 $t$ 在同一子树：

写出贡献式子 $2 \times dis(lca)+w_t-dis(t)$。因为我们钦定了 $t$ 未修改点权，所以可能对这个贡献产生影响的操作就是修改边权操作。因为我们把更改过边权的边标记出来了，也就是说，对于每个子树中的所有 $dis(x)$，他们的 $\Delta dis$ 是固定的。所以我们只需要对每个子树维护 $\Delta dis$，具体来说，我们建出这些子树的根所形成的[虚树](https://oiwiki.com/graph/virtual-tree/) ，在修改某条边边权的时候，我们直接遍历这棵虚树的子树中的所有点就好了。但是我们并不需要 $O(siz)$ 的单调栈建立的办法，直接暴力建树就好了。~~反正 $O(n \sqrt n)$ 和 $O(n)$差别不大~~ 。

时间复杂度分为两部分：

- 用每个子树的 $t$ 和 $t'$ 更新答案，一共 $\sqrt n$ 个子树，需要更新 $\sqrt n$ 个答案，所以对于划分好的每段询问的时间复杂度为 $O(n)$，总共划分出了 $\sqrt n$ 段，所以总时间复杂度 $O(n \sqrt n)$。

- 维护每棵子树的 $\Delta dis$，修改共有 $\sqrt n$ 个，虚树的大小为 $\sqrt n$，每段询问的时间复杂度为 $O(n)$，$\sqrt n$ 段的复杂度 $O(n \sqrt n)$。

第二部分 $lca$ 与 $t$ 不在同一子树：

因为 $lca$ 和 $t$ 不在同一子树，所以 $t$ 所在子树的所有点都在 $lca$ 的子树中。根据上面的子问题中的结论，$lca$ 只会选择 $t$ 所在子树中 $w_t-dis(t)$ 最大的 $t$ 与次大的 $t'$。对于 $t$ 所在子树中的点来说 $\Delta dis$ 是固定的，那么 $w_t-dis(t)$ 的最大的 $t$，与次大的 $t'$ 就是我们最开始重构所维护出的 $t$ 与 $t'$ 。

同第一部分的时间复杂度分析，总时间复杂度为 $O(n\sqrt n)$。

第三部分，修改过的 $t$ 对答案做出贡献：

因为修改过的 $t$ 只会有 $\sqrt n$ 个，所以我们可以用最开始提到的 $O(1)$ 更新点对的方法，更新答案。

时间复杂度同前面两部分一样分析，为 $O(n \sqrt n)$。

~~于是我们就轻松把这道题做完了。~~

### 代码实现

代码大致可分为：

- ```prework``` 和 ```ST_table```，用来 $O(1)$ 求解最近公共祖先。

- ```upd``` 用于将 $y$ 的 $t$ 与 $t'$ 给 $x$ 的 $t$ 与 $t'$ 做贡献。

- ```update``` 用于更新每个子树的 $\Delta dis$。

- ```Dis``` 用于计算 $x$ 真正的 $dis(x)$。

- ```Upans``` 用于更新答案。

- ```prebuild``` 用于计算同一子树中的子树的 $t$ 与 $t'$。（有点绕，第一个子树是指把修改过边权的边标记后，形成的 $\sqrt n$ 个子树，第二个子树，就是子树。）

- ```rebuild``` 重构函数，用于维护 $t$ 与 $t'$ 的后缀最优解用于快速更新统计答案的第一部分。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
template <typename T> inline void read(T &x)
{
	x=0;T f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-')f=-1;
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}
template <typename T,typename ...Args>void read(T &x,Args&...args){read(x),read(args...);}
template <typename T> void print(T x)
{
	if(x<0) x=-x,putchar('-');
	if(x>9) print(x/10);
	putchar(x%10+48);
}
template <typename T> void print(T x,char c){print(x); putchar(c);}
template<typename T>inline void output(T x){print(x,' ');}
template<typename T,typename ...Arg>inline void output(T x,Arg ...arg){output(x);output(arg...);}
const int N=200007,M=400;
int n,q,cnt,h[N],euler[N],idx,pos[N],ans,nxt,pa[N],res1[N],res2[N],vis[N],vise[N],top[N];
ll val[N],vale[N],temp,dis[N],now1[N],now2[N],tag[N];
vector<int>chg,chge,edg[N];
struct edge{int to,nxt;}mp[N<<1];
struct ST_table
{
	int f[20][N],lg[N];
	void prework()
	{
		for(int i=2;i<N;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<n<<1;i++) f[0][i]=euler[i];
		for(int i=1;i<20;i++)
			for(int j=1;j+(1<<i)<=n<<1;j++)
			{
				if(pos[f[i-1][j]]<pos[f[i-1][j+(1<<(i-1))]]) f[i][j]=f[i-1][j];
				else f[i][j]=f[i-1][j+(1<<(i-1))];
			}
	}
	int ask(int l,int r)
	{
		int len=lg[r-l+1];
		if(pos[f[len][l]]<pos[f[len][r-(1<<len)+1]]) return f[len][l];
		else return f[len][r-(1<<len)+1];
	}
	int LCA(int x,int y){return ask(min(pos[x],pos[y]),max(pos[x],pos[y]));}
}__st;
struct node{int opt,pos; ll val;}ask[N];
void add(int x,int y)
{
	cnt++;
	mp[cnt].nxt=h[x];
	mp[cnt].to=y;
	h[x]=cnt;
}
void prework(int x,int fa)
{
	euler[++idx]=x; pos[x]=idx; pa[x]=fa;
	for(int i=h[x];i;i=mp[i].nxt)
	{
		int y=mp[i].to;
		if(y==fa) continue;
		vale[y]=dis[(i+1)>>1];
		prework(y,x); euler[++idx]=x;
	}
}
void upd(int x,int y)
{
	if(now1[x]>now1[y])
	{
		ll mx=-0x3f3f3f3f3f3f3f3f; int pos=0;
		if(now2[x]>mx) mx=now2[x],pos=res2[x];
		else if(now2[x]==mx) pos=min(pos,res2[x]);
		if(res1[y]!=res1[x])
		{
			if(now1[y]>mx) mx=now1[y],pos=res1[y];
			else if(now1[y]==mx) pos=min(pos,res1[y]);
		}
		if(res2[y]!=res1[x])
		{
			if(now2[y]>mx) mx=now2[y],pos=res2[y];
			else if(now2[y]==mx) pos=min(pos,res2[y]);
		}
		res2[x]=pos; now2[x]=mx;
	}
	else
	{
		ll mx=-0x3f3f3f3f3f3f3f3f; int pos=0;
		if(now2[y]>mx) mx=now2[y],pos=res2[y];
		else if(now2[y]==mx) pos=min(pos,res2[y]);
		if(res1[x]!=res1[y])
		{
			if(now1[x]>mx) mx=now1[x],pos=res1[x];
			else if(now1[x]==mx) pos=min(pos,res1[x]);
		}
		if(res2[x]!=res1[y])
		{
			if(now2[x]>mx) mx=now2[x],pos=res2[x];
			else if(now2[x]==mx) pos=min(pos,res2[x]);
		}
		res1[x]=res1[y]; now1[x]=now1[y];
		res2[x]=pos; now2[x]=mx;
	}
}
void update(int x,ll del)
{
	tag[x]+=del;
	for(auto y:edg[x])
		update(y,del);
}
ll Dis(int x){return dis[x]+tag[top[x]];}
bool Updans(int x)
{
	if(!x||x==ans) return false;
	int lca=__st.LCA(ans,x); ll now=2*Dis(lca)+val[x]-Dis(x);
	if(now>temp) temp=now,nxt=x;
	else if(now==temp) nxt=min(nxt,x);
	return true;
}
void prebuild(int x,int fa)
{
	now1[x]=now2[x]=-0x3f3f3f3f3f3f3f3f; res1[x]=res2[x]=0;
	if(!vis[x]) res1[x]=x,now1[x]=val[x]-dis[x];
	for(int i=h[x];i;i=mp[i].nxt)
	{
		int y=mp[i].to;
		if(y==fa) continue;
		dis[y]=dis[x]+vale[y];
		prebuild(y,x);
		if(!vise[y]) upd(x,y);
	}
}
void rebuild(int x,int fa,int ntop)
{
	top[x]=ntop;
	for(int i=h[x];i;i=mp[i].nxt)
	{
		int y=mp[i].to;
		if(y==fa) continue;
		if(!vise[y]) upd(y,x);
		if(vise[y]) rebuild(y,x,y),edg[ntop].push_back(y);
		else rebuild(y,x,ntop);
	}
}
int main()
{
	read(n,q); ans=1;
	for(int i=1;i<=n;i++) read(val[i]);
	for(int i=1,x,y;i<n;i++)
		read(x,y,dis[i]),add(x,y),add(y,x);
	prework(1,0); __st.prework();
	for(int i=1,x,y;i<=q;i++)
	{
		read(ask[i].opt);
		if(ask[i].opt==1) read(ask[i].pos,ask[i].val);
		else
		{
			read(x,y);
			if(pos[x]<pos[y]) swap(x,y);
			ask[i].pos=x; read(ask[i].val);
		}
	}
	for(int i=1;i<=q;i+=M)
	{
		chg.resize(0); chge.resize(0); dis[1]=0;
		for(int j=i;j<=q&&j-i<M;j++)
		{
			if(ask[j].opt==1) vis[ask[j].pos]=1,chg.push_back(ask[j].pos);
			else vise[ask[j].pos]=1,chge.push_back(ask[j].pos);
		}
		prebuild(1,0); chge.push_back(1);
		for(int j=1;j<=n;j++)
		{
			if(res1[j]) now1[j]+=dis[j]*2;
			if(res2[j]) now2[j]+=dis[j]*2;
		}
		rebuild(1,0,1);
		for(int j=i,now;j<=q&&j-i<M;j++)
		{
			temp=-0x3f3f3f3f3f3f3f3f;
			if(ask[j].opt==1) val[ask[j].pos]=ask[j].val;
			else update(ask[j].pos,ask[j].val-vale[ask[j].pos]),vale[ask[j].pos]=ask[j].val;
			for(auto pot:chg) Updans(pot);
			for(auto pot:chge) if(!Updans(res1[pot])) Updans(res2[pot]);
			now=ans; while(now){if(!Updans(res1[now])) Updans(res2[now]); now=pa[top[now]];}
			ans=nxt; print(ans,' ');
		}
		for(auto pot:chge) tag[pot]=0,edg[pot].resize(0);
		for(int j=i;j<=q&&j-i<M;j++)
		{
			if(ask[j].opt==1) vis[ask[j].pos]=0;
			else vise[ask[j].pos]=0;
		}
	}
	return 0;
}
```

---

## 作者：hexagon (赞：3)

来一个模拟赛时想出树剖的做法。

记 $d_u$ 表示根到 $u$ 的距离，$l$ 表示 $\operatorname{lca}(s,t)$，则代价可以转化为：
$$
-d_s+(z_t-d_t+2d_{l})
$$

那么就得到了一个暴力做法，每次从 $s$ 暴力向上跳枚举 $l$ ，并用 $z_t-d_t+2d_l$ 更新答案，这里要求 $t$ 在 $l$ 的子树中且不和 $s$ 来自同一棵子树。

这里 $t$ 的限制条件太复杂，考虑简化，注意到如果 $l$ 只是 $s,t$ 的公共祖先，而非最近公共祖先，只会把答案算小并不会影响最终答案，故我们对 $t$ 的限制条件就可以变为：$t$ 在 $l$ 的子树中。

还有一个问题，题目要求 $s\neq t$，我们只需要再记一下次大值即可，由于次大值是类似的，下面就只讲如何维护最大值。

考虑如何加速上面的过程。一种想法是对于每个节点 $u$ 直接维护 $2d_u+z_x-d_x$ 的最大值，其中 $x$ 是 $u$ 子树中的点。树剖后，把这个东西按照 dfs 序放在线段树上，就可以查询了。但问题是修改了点权或边权后，当前点或边到根路径上的所有点的这个值都要被修改，又因为是维护的最大值，所以不太能通过打标记的方式快速修改。

于是就应该想到一个经典套路：只维护轻子树中的节点。就是说，对于每个节点 $u$ 维护 $2d_u+z_x-d_x$ 的最大值，其中 $x$ 是 $u$ 轻子树中的点。

先考虑修改点权，那么每次修改后，只会有 $\log$ 个点会改变（因为包含 $u$ 的轻子树个数是 $\log$ 的）。为了计算这 $\log$ 个点新的最大值，我们需要能够支持查询子树中 $z_x-d_x$ 的最大值，于是还要开一棵线段树维护 $z_x-d_x$ 的区间最大值。

修改边权也是类似的。设这条边为 $(u,v)$ ，**变化量**为 $c$，其中 $v$ 的深度更深。
+ 对于 $v$ 子树中的所有点，$d$ 都会增加 $c$，而对于所有 $v$ 子树中的 $u$ ，$2d_u+z_x-d_x$ 的最大值也会恰好增加 $c$ ，维护一个区间加法标记即可。
+ 对于不在 $v$ 子树中的点，和前面类似，只有 $\log$ 个更改。

总结一下到底维护了什么：

+ 一个 `bit` ，维护 $d_u$，支持区间加，单点查询。
+ 一个 `seg` ，维护 $d_u-z_u$，支持区间加，区间查询 $\max$。
+ 一个 `seg` ，维护 $2d_u+z_x-d_x$（$x$ 是 $u$ 轻子树中的点），支持区间加，单点修改，区间查询 $\max$。

时间复杂度 $O(n\log^2 n)$ ，跑得很快。

---

## 作者：wrkwrkwrk (赞：0)

考虑树分块。这里所说的树分块是保证每个块的点的个数，**并不保证每个块内部连通。**

:::warning[这里不是 [P6177](https://www.luogu.com.cn/problem/P6177) 的树分块！]
使用随机撒点保证的是暴力跳父亲到关键点，而不是每个块的大小。
:::

:::info[为啥不能保证连通？]
考虑菊花图，显然中心点只能在一个连通块中。
:::

使用如下方式：每次选取子树下的待选连通块，如果超过了阈值 $B$ 则用中心点虚拟连接，分到一块并且清空。最后剩下根的分成一块。这样可以保证大小在 $[B,2B]$ 之间。

块内信息更新后暴力重构即可，注意**虚拟连接点的点权**不认为是块内的，而是视作一个仅连接的特殊点。注意分别维护含和不含自己的。

考虑块间信息。我们需要找到这个点到另一个块的最近点然后减去距离。对于第一个问题，可以发现这个等价于块到块的最近距离的所在点。设 $t_i$ 表示实际的深度最小的点（虚拟点转实际点看），如果我们想知道从块 $j$ 出发第一个到 $i$ 的点，那么如果 $t_i$ 是 $t_j$ 的祖先，那么就是从 $t_j$ 开始的最近祖先且满足在 $i$ 中。否则就是 $t_i$。

后面维护距离要求 $O(1)$ 查询，考虑使用 $O(1) ~\text{lca}$ 转成维护深度，利用 DFS 序和使用 $O(\sqrt N)$ 区间修改，$O(1)$ 单点查询的分块数据结构即可完成。

理论时间复杂度 $O(N+Q\sqrt N)$。实际运行时由于不能移到自身，故块内重构常数稍大，设 $B=180$。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool st;
namespace _wrk{;
int dfn[200005];
int n,q;
vector<pair<int,long long>>g[200005];
namespace tools{
    int dfsid[200005],outid[200005];
    int pdep[200005];
    namespace o1lca{
        int fc[200005][21];
        void init(){
            for(int c=1;c<=20;c++){
                for(int i=1;i+(1ll<<c)-1<=n;i++){
                    fc[i][c]=fc[i][c-1];
                    if(pdep[fc[i][c-1]]>pdep[fc[i+(1ll<<(c-1))][c-1]])fc[i][c]=fc[i+(1ll<<(c-1))][c-1];
                }
            }
        }
        int query(int a,int b){
            if(a==b)return a;
            a=dfsid[a];b=dfsid[b];
            if(a>b)swap(a,b);
            b--;
            int len=b-a+1,p=__lg(len);
            int x=fc[a][p],y=fc[b-(1ll<<p)+1][p];
            if(pdep[x]>pdep[y])return y;
            return x;
        }
    }
    struct osqrtchao1qu{
        const int B=900;
        long long bl[200005],fc[200005];
        void ad(int l,int r,long long b){
            if(l!=0){
                ad(0,r,b);ad(0,l-1,-b);return;
            }
            int nc=0;
            while(nc+B-1<=r){
                bl[nc/B]+=b;
                nc+=B;
            }
            while(nc<=r){
                fc[nc]+=b;
                nc++;
            }
        }
        long long query(int a){
            return bl[a/B]+fc[a];
        }
    }zc;
    long long la[200005];
    void chapos(int x,long long y){
        long long delta=y-la[x];la[x]=y;
        zc.ad(dfsid[x],outid[x],delta);
    }
    void chaedge(int a,int b,long long c){
        int x=dfsid[a]>dfsid[b]?a:b;
        chapos(x,c);
    }
    long long getdep(int x){
        return zc.query(dfsid[x]);;
    }
    long long getlen(int a,int b){
        return getdep(a)+getdep(b)-2*getdep(o1lca::query(a,b));
    }
    int cnt=1;
    long long fpc[200005];
    void dfs(int now,int fa,long long fp){
        dfsid[now]=cnt++;
        pdep[now]=pdep[fa]+1;
        fpc[now]=fp;
        for(auto x:g[now]){
            int to=x.first;long long cost=x.second;
            if(to!=fa){
                o1lca::fc[cnt-1][0]=now;
                dfs(to,now,cost);
            }
        }
        outid[now]=cnt-1;
    }
    void init(vector<array<long long,3>>w){
        dfs(1,0,0);
        o1lca::init();
        for(int i=1;i<=n;i++){
            chapos(i,fpc[i]);
        }
        for(auto x:w){
            chaedge(x[0],x[1],x[2]);
        }
    }
    long long getlink(long long a){
        return la[a];
    }
}
int B;
long long p[200005];
list<int>bufc[200005];
int topc[200005],topid[200005];
int tcd[200005];
int bl,cic;
vector<int>cg[200005];
int xcr[200005];
void buildblock(const list<int>&sc,const vector<int>&z,int tid){
    bool f=0;
    for(auto x:sc){
        topc[x]=tid;
        topid[x]=bl;
        if(x==tid)f=1;
    }
    for(auto x:sc){
        for(auto y:g[x]){
            int to=y.first;
            if(topid[to]==topid[x]){
                cg[x].push_back(to);
            }
        }
    }
    if(!f){
        cic++;
        tcd[bl]=cic;
        xcr[cic]=tid;
        for(auto x:z){
            cg[x].push_back(cic);
            cg[cic].push_back(x);
        }
    }else{
        tcd[bl]=tid;
    }
    bl++;
}
void pdfs(int now,int fa){
    vector<int>tops;
    bufc[now].clear();
    for(auto x:g[now])if(x.first!=fa){
        pdfs(x.first,now);
        bufc[now].splice(bufc[now].end(), bufc[x.first]);//拼接
        tops.push_back(x.first);
        if(bufc[now].size()>=B){
            buildblock(bufc[now],tops,now);
            bufc[now].clear();
            tops.clear();
        }
    }
    bufc[now].push_back(now);
}
vector<int>b[200005];
int blo[1003][1003];
bool ue[1003];
void rdfs(int now,int fa){
    b[topid[now]].push_back(now);
    for(auto x:g[now]){
        int to=x.first;
        if(to!=fa){
            if(topid[to]!=topid[now]&&!ue[topid[to]]){
                for(int j=0;j<bl;j++){
                    if(j!=topid[to]&&b[j].size()){
                        blo[topid[to]][j]=b[j].back();
                    }
                }
                ue[topid[to]]=1;
            }
            rdfs(to,now); 
        }
    }
    b[topid[now]].pop_back();
}
void blockinit(){
    for(int i=0;i<=n;i++){
        topid[i]=-1;
        xcr[i]=i;
    }
    cic=n;
    pdfs(1,0);
    buildblock(bufc[1],{},1);
    rdfs(1,0);
    for(int i=0;i<bl;i++){
        for(int j=0;j<bl;j++){
            if(i!=j&&!blo[i][j]){
                blo[i][j]=tcd[j];
            }
        }
    }
}
struct fr{
    long long ans;int pid;
    fr(){
        ans=-1e18,pid=1e9;
    }
    fr(long long ans,int pid):ans(ans),pid(pid){}
};
bool operator>(const fr &a,const fr & b){
    return a.ans==b.ans?a.pid<b.pid:a.ans>b.ans;
}
bool operator<(const fr & a,const fr & b){
    return a.ans==b.ans?a.pid>b.pid:a.ans<b.ans;
}
bool operator==(const fr & a,const fr & b){
    return a.ans==b.ans&&a.pid==b.pid;
}
fr operator+(const fr & a,long long b){
    return {a.ans+b,a.pid};
}
fr operator-(const fr & a,long long b){
    return {a.ans-b,a.pid};
}
fr xc[200005];
fr xxc[200005];
void ddfs1(int now,int fa){
    xxc[now]=fr(-1e18,1e9);
    for(auto x:cg[now]){
        if(x!=fa){
            ddfs1(x,now);
            xxc[now]=max(xxc[now],xc[x]-tools::getlink(x));
        }
    }
    xc[now]=xxc[now];
    if(now<=n)xc[now]=max(xc[now],{p[now],now});
}
void ddfs2(int now,int fa,fr frp){
    fr ma1=fr(-1e18,1e9),ma2=fr(-1e18,1e9);
    auto inc=[&](const fr &x){
        if(x>ma1){
            ma2=ma1;ma1=x;
        }else if(x>ma2){
            ma2=x;
        }
    };
    xxc[now]=max(xxc[now],frp);
    xc[now]=max(xc[now],frp);
    if(fa){
        inc(frp);
    }
    for(auto x:cg[now]){
        if(x!=fa){
            inc(xc[x]-tools::getlink(x));
        }
    }
    if(now<=n){
        inc({p[now],now});
    }
    for(auto x:cg[now]){
        if(x!=fa){
            long long s=tools::getlink(x);
            auto p=xc[x]-s;
            if(p==ma1){
                ddfs2(x,now,ma2-s);
            }else{
                ddfs2(x,now,ma1-s);
            }
        }
    }
}
void rebuild(int blockid){
    ddfs1(tcd[blockid],0);
    ddfs2(tcd[blockid],0,fr(-1e18,1e9));
}
signed main(){
    B=180;
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    if(n==1){
        while(q--)cout<<"1\n";
        return 0;
    }
    for(int i=1;i<=n;i++)cin>>p[i];
    vector<array<long long,3>>ww;
    for(int i=1;i<n;i++){
        int a,b;long long w;
        cin>>a>>b>>w;
        g[a].push_back({b,w});
        g[b].push_back({a,w});
        ww.push_back({a,b,w});
    }
    tools::init(ww);
    blockinit();
    for(int i=0;i<bl;i++){
        rebuild(i);
    }
    int now=1;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            long long x,q;
            cin>>x>>q;
            p[x]=q;
            rebuild(topid[x]);
        }else{
            long long a,b,c;
            cin>>a>>b>>c;
            tools::chaedge(a,b,c);
            int f=tools::pdep[a]>tools::pdep[b]?a:b;
            rebuild(topid[f]);
        }
        fr res=xxc[now];
        for(int i=0;i<bl;i++){
            if(i!=topid[now]){
                fr p=xc[blo[topid[now]][i]];
                p=p-tools::getlen(now,xcr[blo[topid[now]][i]]);
                res=max(res,p);
            }
        }
        cout<<res.pid<<' ';
        now=res.pid;
    }
    return 0;
}
}
bool en;
signed main(){
          return _wrk::main();
}
```

[AC 记录。](https://www.luogu.com.cn/record/232890015)

---

## 作者：xfrvq (赞：0)

先建点分树，枚举 $u$ 点分树上所有祖先，找它们点分树子树内的点即可找到 $u$ 出发所有路径。

对每个点 $i$ 线段树维护它点分树子树 $dis(i,j)+a_j$ 的值。点修改变为 $dep$ 个线段树单点修改。查询直接查 $dep$ 个线段树的全局最小值。由于正权边找最短路，不用考虑数出冗余路径。

现在考虑边修改 $(u,v)$。设**原树上 $u$ 是 $v$ 父亲**，现在**从 $u,v$ 中点分树上更浅的那个**开始跳父亲，跳到的每个点 $p$，对于 $p$ 点分树子树内的 $q$，若 $p,q$ 一个在 $v$ 子树内一个不在，就满足 $p\to q$ 路径包含 $(u,v)$。

于是每棵线段树都按 $dfn$ 顺序维护，边修改就是 $dep$ 次 $dfn$ 区间加。总复杂度 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;

int n,m,p = 1,dp[N];
int ft[N],siz[N],P,X;
int fa[20][N],dep[N],L[N],R[N],dfn;
ll a[N],W[N],T[N];
bool vis[N];
vector<pair<int,ll>> G[N];
vector<int> G2[N];

#define lb(V,x) ranges::lower_bound(V,x) - begin(V) + 1
#define mid ((L + R) / 2)
#define id int L = 1,int R = -1
#define ID(L,R) (L + R | L != R)

struct sgt{
	int _;
	vector<ll> t;
	vector<pair<ll,int>> T0,T1;
	
	void init(int n){ _ = n,t.resize(2 * _ + 5),T0.resize(2 * _ + 5),T1.resize(2 * _ + 5); }
	
	void add(int i,ll x){ t[i] += x,T0[i].first += x,T1[i].first += x; }
	
	void psd(int L,int R){
		int i = ID(L,R),lc = ID(L,mid),rc = ID(mid + 1,R);
		if(t[i]) add(lc,t[i]),add(rc,t[i]),t[i] = 0;
	}
	
	void psu(int L,int R){
		int i = ID(L,R),lc = ID(L,mid),rc = ID(mid + 1,R);
		if(T0[lc] < T0[rc]) T0[i] = T0[lc],T1[i] = min(T1[lc],T0[rc]);
		else T0[i] = T0[rc],T1[i] = min(T1[rc],T0[lc]);
	}
	
	void chg(int p,auto v,id){
		if(R == -1) R = _;
		int i = ID(L,R);
		if(L == R) return T0[i] = v,T1[i] = make_pair(4e18,N),void();
		psd(L,R),p <= mid ? chg(p,v,L,mid) : chg(p,v,mid + 1,R),psu(L,R);
	}
	
	void upd(int l,int r,ll x,id){
		if(R == -1) R = _;
		if(l > r) return;
		int i = ID(L,R);
		if(l <= L && R <= r) return add(i,x);
		psd(L,R);
		if(l <= mid) upd(l,r,x,L,mid);
		if(r > mid) upd(l,r,x,mid + 1,R);
		psu(L,R);
	}
} t[N];

void dfs(int u,int ft){
	dep[u] = dep[fa[0][u] = ft] + 1,L[u] = ++dfn;
	for(int i = 1;i < 20;++i) fa[i][u] = fa[i - 1][fa[i - 1][u]];
	for(auto[v,w] : G[u]) if(v != ft) W[v] = w,dfs(v,u);
	R[u] = dfn;
}

int lca(int x,int y){
	if(dep[x] < dep[y]) swap(x,y);
	for(int i = 19;~i;--i) if(dep[fa[i][x]] >= dep[y]) x = fa[i][x];
	for(int i = 19;~i;--i) if(fa[i][x] != fa[i][y]) x = fa[i][x],y = fa[i][y];
	return x == y ? x : fa[0][x];
}

void add(int l,int r,ll x){
	for(;l <= n;l += l & -l) T[l] += x;
	for(++r;r <= n;r += r & -r) T[r] -= x;
}

ll qry(int p,ll s = 0){ for(;p;p &= p - 1) s += T[p]; return s; }

ll dis(int x,int y){ return qry(L[x]) + qry(L[y]) - 2ll * qry(L[lca(x,y)]); }

int size(int u,int ft,int s = 1){
	for(auto[v,w] : G[u]) if(v != ft && !vis[v]) s += size(v,u);
	return s;
}

void fnd(int u,int ft,int m){
	int x = 0; siz[u] = 1;
	for(auto[v,w] : G[u]) if(v != ft && !vis[v])
		fnd(v,u,m),siz[u] += siz[v],x = max(x,siz[v]);
	if((x = max(x,m - siz[u])) < X) X = x,P = u;
} 

void sol(int u){
	vis[u] = 1;
	for(auto[v,w] : G[u]) if(!vis[v])
		X = 2e9,fnd(v,u,size(v,u)),ft[P] = u,dp[P] = dp[u] + 1,sol(P);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i) scanf("%lld",a + i);
	for(int i = 1,u,v;i < n;++i)
		scanf("%d%d%lld",&u,&v,W),G[u].emplace_back(v,W[0]),G[v].emplace_back(u,W[0]);
	dfs(1,0); X = 2e9,fnd(1,0,n),sol(P);
	for(int i = 2;i <= n;++i) add(L[i],R[i],W[i]);
	for(int i = 1;i <= n;++i)
		for(int j = i;j;j = ft[j]) G2[j].push_back(L[i]);
	for(int i = 1;i <= n;++i) ranges::sort(G2[i]),t[i].init(G2[i].size());
	for(int i = 1;i <= n;++i)
		for(int j = i;j;j = ft[j]) 
			t[j].chg(lb(G2[j],L[i]),make_pair(dis(i,j) - a[i],i));
	for(ll o,x,y,z;m--;){
		scanf("%lld%lld%lld",&o,&x,&y);
		if(o == 1){
			a[x] = y;
			for(int j = x;j;j = ft[j])
				t[j].chg(lb(G2[j],L[x]),make_pair(dis(x,j) - a[x],x));
		} else {
			scanf("%lld",&z);
			ll &w = W[fa[0][y] == x ? y : x];
			if(dp[x] < dp[y]) swap(x,y);
			for(int j = x;j;j = ft[j]){
				if(fa[0][y] == x){
					if(L[y] <= L[j] && L[j] <= R[y]){
						t[j].upd(1,lb(G2[j],L[y] + 1) - 1,z - w);
						t[j].upd(lb(G2[j],R[y]),G2[j].size(),z - w);
					} else t[j].upd(lb(G2[j],L[y]),lb(G2[j],R[y] + 1) - 1,z - w);
				} else {
					if(L[x] <= L[j] && L[j] <= R[x]){
						t[j].upd(1,lb(G2[j],L[x] + 1) - 1,z - w);
						t[j].upd(lb(G2[j],R[x]),G2[j].size(),z - w);
					} else t[j].upd(lb(G2[j],L[x]),lb(G2[j],R[x] + 1) - 1,z - w);
				}
			}
			add(L[fa[0][y] == x ? y : x],R[fa[0][y] == x ? y : x],z - w),w = z;
		}
		pair<ll,int> ans(4e18,N);
		for(int j = p;j;j = ft[j]){
			auto zzh = t[j].T0[ID(1,G2[j].size())].second == p ? t[j].T1[ID(1,G2[j].size())] : t[j].T0[ID(1,G2[j].size())];
			zzh.first += dis(p,j),ans = min(ans,zzh);
		}
		printf("%d ",p = ans.second);
	}
	return 0;
}
```

---

