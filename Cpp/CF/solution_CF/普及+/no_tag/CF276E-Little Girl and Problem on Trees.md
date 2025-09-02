# Little Girl and Problem on Trees

## 题目描述

A little girl loves problems on trees very much. Here's one of them.

A tree is an undirected connected graph, not containing cycles. The degree of node $ x $ in the tree is the number of nodes $ y $ of the tree, such that each of them is connected with node $ x $ by some edge of the tree.

Let's consider a tree that consists of $ n $ nodes. We'll consider the tree's nodes indexed from 1 to $ n $ . The cosidered tree has the following property: each node except for node number 1 has the degree of at most 2.

Initially, each node of the tree contains number 0. Your task is to quickly process the requests of two types:

- Request of form: $ 0 $ $ v $ $ x $ $ d $ . In reply to the request you should add $ x $ to all numbers that are written in the nodes that are located at the distance of at most $ d $ from node $ v $ . The distance between two nodes is the number of edges on the shortest path between them.
- Request of form: $ 1 $ $ v $ . In reply to the request you should print the current number that is written in node $ v $ .

## 样例 #1

### 输入

```
3 6
1 2
1 3
0 3 1 2
0 2 3 1
0 1 5 2
1 1
1 2
1 3
```

### 输出

```
9
9
6
```

## 样例 #2

### 输入

```
6 11
1 2
2 5
5 4
1 6
1 3
0 3 1 3
0 3 4 5
0 2 1 4
0 1 5 5
0 4 6 2
1 1
1 2
1 3
1 4
1 5
1 6
```

### 输出

```
11
17
11
16
17
11
```

# 题解

## 作者：玖梦 (赞：4)

## 算法概述

 显然，树的形态就是根上挂了很多条链，考虑利用这个形态的特殊性。

首先，如果距离 $d$ 以内的点均与 $u$ 在同一条链上，那么很好处理，直接线段树维护链上的区间权值即可，因为同一条链上的点dfs序是连续的，以下用 $id[u]$ 表示节点 $u$ 的dfs序。

但是这道题并没有那么简单，这个 $d$ 完全有可能超过 $dep[u]$，那么就会绕过根影响到 $u$ 所在的链以外的点，如果直接将链以外的点的权值也一同处理了，则时间复杂度显然不行。

考虑在根上挂标记，将需要增加的点权暂时保留在根上。以 $val[i]$ 表示距离根 $i$ 以内的点需要加上的权值，这个定义等价于深度小于等于 $i$ 的点需要加上的权值（定义根节点深度为0）。

我们用 $dep[u]$ 表示节点 $u$ 的深度，那么在查询节点 $u$ 时，其保留在根上的还需增加的点权即为 $val[dep[u],dep[u]+1,…,n-1]$（一共 $n$ 个节点，深度最大为 $n-1$），也就是一段后缀和，故我们可以用树状数组维护。

于是，我们就得到了一个可以很好解决这个问题的算法：

对于修改操作：若 $d<dep[u]$，直接线段树维护即可；若 $d>=dep[u]$，则先在根上加标记，$val[d-dep[u]]$ 加上 $x$，然后处理链，由于在根上加了标记之后，原链上距离根 $d-dep[u]$ 以内的点已经被覆盖了，所以考虑有没有过多覆盖（即覆盖的范围超出了本来需要修改的范围），这显然不可能（反证：若过多覆盖，即 $d-dep[u]>dep[u]+d => dep[u]<0$，矛盾！）。所以已覆盖的范围是必然小于等于我们原本需要覆盖的范围的，那么我们只需考虑还需修改的范围（但是已覆盖的范围可能已经包括了链的末端，所以还需要特判）。这个范围的顶端显然是链顶（$id[u]-dep[u]+1$）加上已覆盖的范围（$d-dep[u]$），即 $id[u]-2*dep[u]+d+1$，而末端可能为原链的链尾（$id[u]+len[ch[u]]-dep[u]$），也有可能是 $id[u]+d$，两者相比较一下取小即可。然后对于这个范围，用线段树做一下区间修改即可。

为了快速得到链尾，我们可以预处理出 $ch[u]$ 表示节点 $u$ 所在的链的编号，$len[i]$ 表示编号为 $i$ 的链的长度，即链尾节点的深度。

对于查询操作：一部分是已修改的权值，直接线段树单点查询即可，另一部分是待修改的权值，被我们挂在根上，故树状数组区间查询后缀和即可。

还有一个细节需要注意，由于树状数组维护的下标范围是从1开始的，而我们的深度最小是0，所以我们需要在对树状数组执行操作时的下标整体后移一位。

时间复杂度显然是 $O(mlogn)$。
## 参考代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=1e5+10;
struct Edge{
	int to,next;
}edge[N<<1];int idx;
int h[N];

void add_edge(int u,int v){edge[++idx]={v,h[u]};h[u]=idx;}

struct Segment_Tree{
	int l,r;
	ll sum;
	ll add;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define sum(p) tree[p].sum
	#define add(p) tree[p].add
}tree[N<<2];

void push_up(int p){sum(p)=sum(p<<1)+sum(p<<1|1);}

void spread(int p)
{
	if(add(p))
	{
		sum(p<<1)+=add(p)*(r(p<<1)-l(p<<1)+1);
		sum(p<<1|1)+=add(p)*(r(p<<1|1)-l(p<<1|1)+1);
		add(p<<1)+=add(p);
		add(p<<1|1)+=add(p);
		add(p)=0; 
	}
}

void build(int p,int l,int r)
{
	l(p)=l,r(p)=r;
	if(l==r)return;
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}

void change(int p,int l,int r,int v)
{
	if(l<=l(p)&&r>=r(p))
	{
		sum(p)+=(ll)v*(r(p)-l(p)+1);
		add(p)+=v;
		return;
	}
	spread(p);
	int mid=l(p)+r(p)>>1;
	if(l<=mid)change(p<<1,l,r,v);
	if(r>mid)change(p<<1|1,l,r,v);
	push_up(p);
}

int query(int p,int pos)
{
	if(l(p)==r(p))return sum(p);
	spread(p);
	int mid=l(p)+r(p)>>1;
	if(pos<=mid)return query(p<<1,pos);
	else return query(p<<1|1,pos);
}

int dep[N],id[N];
int len[N],ch[N];
int timestamp,cnt;

void dfs(int p,int f,int ch_id)
{
	id[p]=++timestamp;
	dep[p]=dep[f]+1;
	ch[p]=ch_id; //处理链的编号 
	len[ch_id]=max(len[ch_id],dep[p]); //每条链的最大深度 
	for(int i=h[p];~i;i=edge[i].next)
	{
		int to=edge[i].to;
		if(to==f)continue;
		dfs(to,p,ch_id);
	}
}

void init()
{
	dep[1]=0;
	id[1]=++timestamp;
	for(int i=h[1];~i;i=edge[i].next)
	{
		int to=edge[i].to;
		dfs(to,1,++cnt);
	}
}

int tr[N];
int n,m;

int lowbit(int x){return x&-x;}

void add_tree(int x,int y){for(;x<=n;x+=lowbit(x))tr[x]+=y;}

int ask(int x)
{
	int ans=0;
	for(;x;x-=lowbit(x))ans+=tr[x];
	return ans;
}

int main()
{
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof h);
	for(int i=1;i<=n-1;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	init();
	build(1,1,n);
	while(m--)
	{
		int tp;scanf("%d",&tp);
		if(!tp) //修改操作 
		{
			int u,x,d;scanf("%d%d%d",&u,&x,&d);
			if(u==1)add_tree(d+1,x); //根节点直接特殊处理，d+1是下标后移一位 
			else if(d<dep[u]) //完全在链上的情况 
				change(1,max(id[u]-d,id[u]-dep[u]+1),min(id[u]+len[ch[u]]-dep[u],id[u]+d),x); //顶端取max，末端取min 
			else //需要在根上挂标记的情况 
			{
				add_tree(d-dep[u]+1,x); //处理根上的标记，+1同样也是因为下标后移一位 
				if(id[u]+len[ch[u]]-dep[u]<id[u]+d-2*dep[u]+1)continue; //链尾<未被覆盖的第一个点，即链尾已被覆盖 
				change(1,id[u]+d-2*dep[u]+1,min(id[u]+len[ch[u]]-dep[u],id[u]+d),x); //末端取min 
			}
		}
		else //查询操作 
		{
			int u;scanf("%d",&u);
			int ans=query(1,id[u]); //已经被修改的部分 
			int sum=ask(n)-ask(dep[u]); //还保留在根上的待修改部分，范围是[dep[u],n-1]，下标后移一位[dep[u]+1,n]
			//由于树状数组查询的是前缀和，所以查询1~n和1~dep[u]相减即可。 
			printf("%d\n",ans+sum); //两部分相加即为答案 
		}
	}
	
	return 0;
}
```



---

## 作者：_edge_ (赞：2)

提供一种奇怪的倍增做法，但是可用于处理有边权的情况。

首先分析题目的条件，发现它是一个菊花下面挂了不少条链。

我们发现修改一个操作，比较麻烦尝试把它分解掉。

一种情况是修改根节点，这时候直接把深度小于某个值的全都加上去就可以了，这是树状数组维护。

另外一种情况稍微麻烦一点，考虑它没有覆盖根节点，那咋办，相当于是一条链上的修改。

链上修改可以直接把它拆成两条链，即 $[l,r]$ 变成 $[1,l-1]$ 和 $[1,r]$ 的操作，查询的时候直接查询子树和，这是树上差分的基本操作。

如果说它覆盖了根节点，那么就转化为第一种情况。

需要注意的是，这里覆盖根节点可能也会覆盖当前的链的一部分，要把它先减去。

同时，我这里用了倍增的做法，可以处理有边权的情况。

即，当前跳第一个满足条件的链尾和链头。

注意这边儿子也要进行倍增。

当然你也完全可以把它变成 DFS 序，然后在 DFS 序上直接修改，因为它是一条链。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=3e5+5;
struct _node_edge{
	int to_,next_;
}edge[INF<<1];
int n,q,head[INF],tot,dep[INF],pre[INF],dfn[INF],fa1[INF][25],son1[INF][25],sz[INF];
void add_edge(int x,int y) {
	edge[++tot]=(_node_edge){y,head[x]};
	head[x]=tot;return ;
}
void DFS(int x,int fa) {
	fa1[x][0]=fa;sz[x]=1;
	dep[x]=dep[fa]+1;dfn[++dfn[0]]=x;pre[x]=dfn[0];
//	cout<<x<<" "<<pre[x]<<" fadddddd\n";
	for (int i=1;i<=23;i++)
		fa1[x][i]=fa1[fa1[x][i-1]][i-1];
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (v==fa) continue;
		DFS(v,x);son1[x][0]=v;sz[x]+=sz[v];
	}
	for (int i=1;i<=23;i++)
		son1[x][i]=son1[son1[x][i-1]][i-1];
}
struct BIT{
	int tree[INF];
	void add(int x,int y) {for (int i=x;i<=1e5;i+=i&-i) tree[i]+=y;}
	int query(int x) {int sum=0;for (int i=x;i;i-=i&-i) sum+=tree[i];return sum;}
}T1,T2;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>q;
	for (int i=1;i<n;i++) {
		int x=0,y=0;cin>>x>>y;
		add_edge(x,y);add_edge(y,x);
	}
	DFS(1,0);
//	cout<<pre[2]<<" ????\n";
	for (int i=1;i<=q;i++) {
		int op=0,x=0,y=0,z=0;cin>>op;
		if (op==0) {
			cin>>x>>z>>y;
			if (x==1) T1.add(y+1,z);
			else {
				if (dep[x]-y>=1) {
//					cout<<" ok?\n";
					int xx=x,yy=dep[x]+y;
					for (int i=23;i>=0;i--) {
						if (!son1[xx][i]) continue;
						if (dep[son1[xx][i]]>yy) continue;
						xx=son1[xx][i];
					}
					T2.add(pre[xx],z);
					
					xx=x,yy=dep[x]-y;
					for (int i=23;i>=0;i--) {
						if (!fa1[xx][i]) continue;
						if (dep[fa1[xx][i]]<yy) continue;
						xx=fa1[xx][i];
					}
					xx=fa1[xx][0];
					if (xx) T2.add(pre[xx],-z);
				}
				else {
					int xx=x,yy=dep[x]+y;
					for (int i=23;i>=0;i--) {
						if (!son1[xx][i]) continue;
						if (dep[son1[xx][i]]>yy) continue;
						xx=son1[xx][i];
					}
//					cout<<xx<<" "<<y-dep[x]+1<<" over?\n";
					T2.add(pre[xx],z);
					T1.add(y-dep[x]+2,z);
					xx=x,yy=y-dep[x]+2;int fl=0;
					if (dep[xx]>yy) fl=1;
					for (int i=23;i>=0;i--) {
						if (!fa1[xx][i]) continue;
						if (dep[fa1[xx][i]]<=yy) continue;
						xx=fa1[xx][i];
					}
//					cout<<fl<<" faddd\n";
					if (fl) xx=fa1[xx][0];
					if (!fl) {
						xx=x,yy=y-dep[x]+2;
						for (int i=23;i>=0;i--) {
							if (!son1[xx][i]) continue;
							if (dep[son1[xx][i]]>yy) continue;
							xx=son1[xx][i];fl=1;
						}
					}
//					if (!fl && dep[x]>=yy) continue;
//					cout<<xx<<" fad?\n";
					T2.add(pre[xx],-z);
				}
			}
		}
		else {
			int x=0;cin>>x;
//			cout<<T1.query(1e5)-T1.query(dep[x]-1)<<" ??\n";
			cout<<T1.query(1e5)-T1.query(dep[x]-1)+T2.query(pre[x]+sz[x]-1)-T2.query(pre[x]-1)<<"\n";
		}
	}
	return 0;
}
```


---

## 作者：MeowScore (赞：2)

挺有趣的题目，所以写写题解。用的是线段树 qwq

[传送门](https://www.luogu.com.cn/problem/CF276E)

重新描述一下题面，这题目翻译给了个错的。

给一棵树，初始点权都为 $0$，保证除了 $1$ 号节点以外的节点度数不超过 $2$。换句话说，这棵树就是 $1$ 号节点下面挂了若干条链形成的（下文提到根节点下挂的链不包含根节点）。有两种操作：

+ $(0,v,x,d)$：把距离 $v$ 号点距离不超过 $d$ 的点点权加 $x$。

+ $(1,v)$：查询 $v$ 号点的点权。

不难想到 dfs 计算时间戳。由于此题树的形状的特殊性，根节点下每一条链上的时间戳都是连续的，就可以把树上的修改转移到序列上的区间修改，又想到了在时间戳上建立线段树。

先考虑两种最简单的情况。

第一种简单情况，如果 $x$ 向上走 $d$ 的距离之后还在这条链上，那我们直接进行一个区间加即可。为了不越界，dfs 的时候可以处理出来每个点所在链的最高点和最低点。

麻烦的情况是向上走 $d$ 的距离就超过链上最高点了，此时需要走到根节点，再进行一个拐弯。

第二种简单情况，我们不妨考虑对根节点执行第一种操作的情况，不难发现修改的点其实是一个深度范围内的所有点。例如要修改距离根节点不超过 $114$ 的所有点，实际上就是修改所有深度小于等于 $115$ 的点！此时我们想要修改这些所有的点很困难，可以再开一棵线段树，建立在深度上，表示一个深度上的所有点被一起加了多少。查询的时候一个点的答案就是记录在第一棵线段树上的权值加上它所在深度应该加上的值。

然后我们发现，这两种简单的情况结合起来似乎就可以应对所有情况了。也就是先在链上区间修改，如果还没走到头，计算一下走到根节点再拐弯下来要修改多少深度的节点。注意两次的操作可能会重复修改一段节点，求出来逆操作即可（区间减）。

边界之类的还是挺细节的，要谨慎。

代码：

```
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int n,m;
int read(){
	int ss=0,ww=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			ww=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ss=ss*10+ch-'0';
		ch=getchar();
	}
	return ss*ww;
}
int head[N],to[N*2],nex[N*2],cnt;
void add(int x,int y){
	cnt++;
	to[cnt]=y;
	nex[cnt]=head[x];
	head[x]=cnt;
}
int tp[N],bt[N],dfn[N],tot,dep[N],id[N];
void dfs(int x,int f){
	tot++;
	id[tot]=x;
	dfn[x]=tot;
	dep[x]=dep[f]+1;
	if(f==1)
		tp[x]=dfn[x];
	else
		tp[x]=tp[f];
	bool b=0;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==f)
			continue;
		b=1;
		dfs(y,x);
		bt[x]=bt[y];
	}
	if(!b)
		bt[x]=dfn[x];
}
struct ST1{
	int tag;
	int sum;
}st1[N*4];//建立在时间戳上
struct ST2{
	int tag;
	int sum;
}st2[N*4];//建立在深度上
int res1;
void push_down1(int root,int l,int r){
	int k=st1[root].tag;
	int mid=(l+r)/2;
	st1[root].tag=0;
	st1[root*2].tag+=k;
	st1[root*2+1].tag+=k;
	st1[root*2].sum+=(mid-l+1)*k;
	st1[root*2+1].sum+=(r-mid)*k;
}
void add1(int root,int l,int r,int x,int y,int k){
	if(l>=x&&r<=y){
		st1[root].tag+=k;
		st1[root].sum+=(r-l+1)*k;
		return;
	}
	int mid=(l+r)/2;
	push_down1(root,l,r);
	if(mid>=x)
		add1(root*2,l,mid,x,y,k);
	if(mid+1<=y)
		add1(root*2+1,mid+1,r,x,y,k);
}
void ask1(int root,int l,int r,int x){
	if(l==r){
		res1=st1[root].sum;
		return;
	}
	int mid=(l+r)/2;
	push_down1(root,l,r);
	if(mid>=x)
		ask1(root*2,l,mid,x);
	else
		ask1(root*2+1,mid+1,r,x);
}
int res2;
void push_down2(int root,int l,int r){
	int k=st2[root].tag;
	int mid=(l+r)/2;
	st2[root].tag=0;
	st2[root*2].tag+=k;
	st2[root*2+1].tag+=k;
	st2[root*2].sum+=(mid-l+1)*k;
	st2[root*2+1].sum+=(r-mid)*k;
}
void add2(int root,int l,int r,int x,int y,int k){
	if(l>=x&&r<=y){
		st2[root].tag+=k;
		st2[root].sum+=(r-l+1)*k;
		return;
	}
	int mid=(l+r)/2;
	push_down2(root,l,r);
	if(mid>=x)
		add2(root*2,l,mid,x,y,k);
	if(mid+1<=y)
		add2(root*2+1,mid+1,r,x,y,k);
}
void ask2(int root,int l,int r,int x){
	if(l==r){
		res2=st2[root].sum;
		return;
	}
	int mid=(l+r)/2;
	push_down2(root,l,r);
	if(mid>=x)
		ask2(root*2,l,mid,x);
	else
		ask2(root*2+1,mid+1,r,x);
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<n;i++){
		int x,y;
		x=read();
		y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1,1);
	while(m--){
		int opt;
		opt=read();
		if(opt==0){
			int x,y,k;
			x=read();
			k=read();
			y=read();
			if(x==1){
				add2(1,1,n,1,y+1,k);
				continue;
			}
			add1(1,1,n,dfn[x],min(dfn[x]+y,bt[x]),k);
			if(dep[x]-2>=y)
				add1(1,1,n,dfn[x]-y,dfn[x]-1,k);
			else{
				if(tp[x]!=dfn[x])
					add1(1,1,n,tp[x],dfn[x]-1,k);
				int DEP=y-(dep[x]-dep[id[tp[x]]]);
				add2(1,1,n,1,DEP,k);
				if(DEP!=1)
					add1(1,1,n,tp[x],min(tp[x]+DEP-2,bt[x]),-k);
			}
		}
		else{
			int x;
			x=read();
			res1=0;
			ask1(1,1,n,dfn[x]);
			res2=0;
			ask2(1,1,n,dep[x]);
			printf("%d\n",res1+res2);
		}
	}
	return 0;
}
```

---

## 作者：shao0320 (赞：2)

CF276E Little Girl and Problem on Trees

一个大菊花，支持两种操作，对距离某个点不超过 $d$ 的点加 $x$ ，查询某个点的值。

考虑 $dfs$ 序 + 线段树维护。

$1$ 操作可以先特殊处理根，对于不是根的点我们显然有，如果到根的距离小于  $d$ ，那么就可以直接加，如果大于等于 $d$ （设这个点的深度为 $dep$ ）就需要让深度不超过 $d-dep$ 的点都加上一个数，那么可以用另一颗线段树维护，最后一个点真实的值就是两个线段树的和。


---

## 作者：23forever (赞：2)

有点意思的数据结构题。

首先，我们知道这个题一种可以大力动态点分治，然后再对点分树维护一棵线段树就完事儿。

但是，我们再读一遍英文题面，会发现这棵树有一个很特殊的性质：除了根节点，其他点度数不超过2。所以这棵树是一个没有柄的扫把型。它由很多条链在根节点相交而成。

我们可以想到对于一个点$u$，和它距离$d$的点，只可能和它在同一条链上，或者绕过根节点跑到其他子树。

对于第一种情况，我们可以直接对链维护一棵线段树。因为链上的dfs序连续，所以很好维护链的情况。

对于第二种情况，我们可以发现修改与$u$距离$d$的点，最远会对每条链的某一层节点产生影响。所以我们要再统一维护一下每一层的信息。这一部分，对层数也建一棵线段树即可。

最后，我们将上述两种情况进行统一，就能得到正解：用两棵线段树维护修改和查询。需要注意的是，一个点不能同时被两种情况覆盖。所以我们还要进行一些更细节的讨论，这一部分可以代码，或者自己画图感受一下。

```cpp
// Author: 23forever
#include <bits/stdc++.h>
#define pb push_back
#define lson p << 1
#define rson p << 1 | 1
const int MAXN = 100000;
using namespace std;

int n;

struct SegmentTree {
  struct Node {
    int sum, tag;
  } s[MAXN * 4 + 5];
  SegmentTree() {}

  void add(int p, int val, int len) {
    s[p].sum += val * len, s[p].tag += val;
  }
  void pd(int p, int len) {
    if (s[p].tag) {
      add(lson, s[p].tag, len - len / 2);
      add(rson, s[p].tag, len / 2);
      s[p].tag = 0;
    }
  }
  void upd(int p) {
    s[p].sum = s[lson].sum + s[rson].sum;
  }
  void modify(int p, int l, int r, int x, int y, int val) {
    if (x <= l && y >= r) {
      add(p, val, r - l + 1); return;
    }
    pd(p, r - l + 1);
    int mid = (l + r) >> 1;
    if (x <= mid) modify(lson, l, mid, x, y, val);
    if (y > mid) modify(rson, mid + 1, r, x, y, val);
    upd(p);
  }
  int query(int p, int l, int r, int x) {
    if (l == r) return s[p].sum;
    pd(p, r - l + 1);
    int mid = (l + r) >> 1;
    if (x <= mid) {
      return query(lson, l, mid, x);
    } else {
      return query(rson, mid + 1, r, x);
    }
  }

} Chain, D;

namespace tree {
vector < int > adj[MAXN + 5];
int sz[MAXN + 5], depth[MAXN + 5], dfn[MAXN + 5], idx;

void addEdge(int u, int v) {
  adj[u].pb(v), adj[v].pb(u);
}

void dfs(int u, int fa) {
  dfn[u] = ++idx;
  for (int v: adj[u]) {
    if (v == fa) continue; 
    depth[v] = depth[u] + 1, dfs(v, u);
    sz[u] = sz[v] + 1;
  }
}

void modify(int u, int x, int d) {
  if (u == 1) {
    D.modify(1, 1, n, 1, min(d + 1, n), x);
    return;                 
  } 
  
  int dis = d - depth[u], qr = dfn[u] + min(d, sz[u]);
  if (dis > 0) {
    D.modify(1, 1, n, 1, dis + 1, x);
    Chain.modify(1, 1, n, dfn[u] - depth[u] + dis + 1, qr, x);
  } else if (dis == 0) {
    Chain.modify(1, 1, n, 1, 1, x);
    Chain.modify(1, 1, n, dfn[u] - d + 1, qr, x);
  } else {
    Chain.modify(1, 1, n, dfn[u] - d, qr, x);
  }
}

int query(int u) {
  return Chain.query(1, 1, n, dfn[u]) + D.query(1, 1, n, depth[u] + 1);
}
}

int m;

void init() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    tree::addEdge(u, v);
  }
  tree::dfs(1, 0);
}

int main() {
#ifdef forever23
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif
  init();

  while (m--) {
    int opt, u; cin >> opt >> u;
    if (opt == 0) {
      int x, d; cin >> x >> d;
      tree::modify(u, x, d);     
    } else {
      cout << tree::query(u) << endl;
    }
  }
  return 0;
}
```

---

## 作者：qiyue7 (赞：1)

KD树树上染色经典题   
首先需要支持范围modify和查询的KD树的板子

除根节点以外每个节点度数最多为2，则画图后可以看出树的形状接近于一个各边延长版的菊花图，则我们可以分类讨论实际染色区域就把可以把问题解决了，具体分类讨论细节看代码（~~算染色区域的坐标略微繁琐~~）


AC主代码：

```cpp
array<vector<int>, 310000> edge;
array<int, 310000> B, E, deep, id, ans2;
array<bool, 310000> vis;
vector<tuple<int, int, int> > PP;
int len = 0;
void dfs(int a)
{
	vis[a] = true;
	B[a] = ++len;
	id[len] = a;
	for (auto &p : edge[a])
		if (!vis[p])
			deep[p] = deep[a] + 1, dfs(p);
	E[a] = len;
	PP[a - 1] = make_tuple(B[a], deep[a], 0);
}
int32_t main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n, m, op, x, y, u, v, q,d;
	vis.fill(false);
	deep[1] = 0;
	cin >> n >> q;
	PP.resize(n);
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1);
	tr.build(PP);
	while (q--)
	{
		cin >> op;
		if (op == 0)
		{
			cin >> x >> y >> d;
			if (x == 1)
			{
				Point l(B[x], deep[x]), r(E[x], deep[x] + d);
				tr.rt->add_sum(l, r, y);
			}
			else  if (deep[x] - d >= 1)
			{
				Point l(B[x] - d, deep[x] - d), r(E[id[B[x] - d]], deep[x] + d);
				tr.rt->add_sum(l, r, y);
			}
			else if (deep[x] - d < 1)
			{
				int kkk = deep[1] + d - deep[x];
				Point l(1, deep[1]), r(E[1], deep[1]+d-deep[x]), l2(B[x] - deep[x]+kkk+1,0), r2(E[id[B[x] - deep[x] + kkk +1]], deep[x] + d);
				tr.rt->add_sum(l, r, y);
				if(B[x] - deep[x] + kkk + 1<=E[x])
				tr.rt->add_sum(l2, r2, y);
			}
		}
		else
		{
			cin >> x;
			cout << (tr.query(B[x], deep[x], B[x], deep[x])) << '\n';
		}
	}
	return 0;
}
```


---

## 作者：Yuby (赞：0)

[题面](https://www.luogu.com.cn/problem/CF276E)

点数：2100

#### 标签：

欧拉序，树状数组，线段树

#### 分析：

注意到 $n \leq 10^5$ 和 $q\leq 10^5$，那么空间复杂度最多 $O(n\log n)$ 和时间复杂度最多为 $O(n\log n+q\log n)$。意味着对于每一个修改和查询我们只能用 $O(\log n)$ 的范围内实现。

我们发现其实对于两个操作来说就是维护第一个，查询第二个。那我们把重点放到维护第一个操作上面。

似乎在一个树上去维护这样一个修改并不好搞，我们返回题目。题目中提到除 1 号节点外，其他节点的度均为 2，且这是一棵树。翻译成人话：一堆链，起始节点都是 1 号节点。

回到操作上，你会发现操作 1 其实是对所有深度为 $d-dep_v$ 和在当前链上距离小于 $d$ 的节点进行区间加法。不难想到欧拉序 + 树状数组维护。

不妨维护两个欧拉序，一个是对深度的，另一个是对链的。

注意在树状数组维护时，如果深度超过了 $d$ 也就是说 $dep_u>d$ 的话只会更改当前链的。

总复杂度：$O(n+q\log n)$。主要是树状数组。

#### 代码解释：

$fir_i$ 表示第 $i$ 个节点所在链的第一个节点（不包括 1 号节点的情况下）

$las_i$ 表示第 $i$ 个节点所在链的最后一个节点（不包括 1 号节点的情况下）

$lin_i$ 是按照 dfs 序的编号。

$dfn_i$ 是按照 bfs 序的编号。

$in_i$ 表示第 $i$ 层的初始节点。

$out_i$ 表示第 $i$ 层的结束节点。

#### 代码：

```cpp
#include<bits/stdc++.h>//author:Yuby163
#define mem(a,b) memset(a,b,sizeof(a));//C++20+O2 2.69KB 10.11s 70.31MB
#define pc putchar
using namespace std;
typedef long long ll;
const ll INF=ll(1e9+7);
inline ll lowbit(ll x){return x&(-x);}
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
const ll MAXN=4e5+7,MAXM=4e5+7;
ll head[MAXN],edgenum;
ll n,q,dep[MAXN];
vector<ll>pos[MAXN];
ll dfn[MAXN],dfncnt[MAXN],in[MAXN],out[MAXN];//对每一层维护
ll lin[MAXN],dfnn,las[MAXN],fa[MAXN],fir[MAXN];//对每一条链维护
struct node
{
	ll u,v,nxt,w;
}edge[MAXM];
struct TREE
{
	ll tree[MAXN];
	void add(ll x,ll k)
	{
		for(ll i=x;i<=n;i+=lowbit(i))
			tree[i]+=k;
	}
	ll sum(ll x)
	{
		ll res=0;
		for(ll i=x;i>0;i-=lowbit(i))
			res+=tree[i];
		return res;
	}
	ll get_ans(ll x)
	{
		return sum(x);
	}
}t1,t2;//t1是对每一层维护，t2是对每条链维护
void add_edge(ll u,ll v)
{
	edge[++edgenum].nxt=head[u];
	edge[edgenum].v=v;
	edge[edgenum].u=u;
	head[u]=edgenum;
}
void dfs(ll u,ll fat)
{
	dfn[u]=++dfncnt[dep[u]];
	lin[u]=++dfnn;
	pos[dep[u]].push_back(u);
	las[u]=dfnn;
	for(ll i=head[u];i;i=edge[i].nxt)
	{
		ll v=edge[i].v;
		if(v==fat)continue;
		dep[v]=dep[u]+1;
		fa[v]=u;
		dfs(v,u);
		if(u==1)fir[v]=lin[v];
		las[u]=dfnn;
	}
}
void dfs1(ll u,ll fat)
{
	for(ll i=head[u];i;i=edge[i].nxt)
	{
		ll v=edge[i].v;
		if(v==fat)continue;
		if(u!=1)fir[v]=fir[u];
		dfs1(v,u);
	}
}
void solve(ll v,ll x,ll d)
{
	if(v==1)
	{
		t1.add(in[0],x);
		t1.add(out[d]+1,-x);
	}
	else if(dep[v]<=d)
	{
		t1.add(1,x);t1.add(out[d-dep[v]]+1,-x);
		t2.add(min(las[v]+1,fir[v]+d-dep[v]),x);
		t2.add(min(las[v],lin[v]+d)+1,-x);
	}
	else
	{
		t2.add(max(fir[v],lin[v]-d),x);
		t2.add(min(las[v],lin[v]+d)+1,-x);
	}
}
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read(),q=read();
    for(ll i=1;i<n;i++)
    {
    	ll u=read(),v=read();
    	add_edge(u,v);
    	add_edge(v,u);
	}
	dfs(1,0);dfs1(1,0);//预处理出欧拉序
	ll pre=0;
	for(ll i=0;i<=n;i++)
	{
		if(!dfncnt[i])break;
		in[i]=INF;
		for(ll j=0;j<pos[i].size();j++)//把所有的欧拉序连起来
		{
			ll son=pos[i][j];
			dfn[son]+=pre;
			in[i]=min(in[i],dfn[son]);
			out[i]=max(out[i],dfn[son]);
		}
		pre+=dfncnt[i];
	}
	for(ll i=0;i<=n;i++)
	{
		if(out[i])continue;
		out[i]=n+1;in[i]=n+1;
	}
	while(q--)
	{
		ll op=read();
		if(op)
		{
			ll v=read();
			write(t1.get_ans(dfn[v])+t2.get_ans(lin[v])),pc(10);
		}
		else
		{
			ll v=read(),x=read(),d=read();
			solve(v,x,d);
		}
	}
	return 0;
}
```



---

## 作者：meizhuhe (赞：0)

由于除了根节点，其他节点的度数都最多为 $2$ ，因此我们可以发现其实就是根节点上挂了很多的链。设链的数量为 $k$ ，考虑维护 $k$ 个树状数组，包含操作区间加和单点求值操作（其实是用树状数组维护差分）；一个根节点的标记，代表根节点的值

设节点 $x$ 所在链的编号为 $mp[x]$  ,且 $x$ 为该链中下标值为 $pos[x]$ 的节点。那么的对于 $pos[x]\geq d$ 的情形很容易就能解决，即直接在维护该链上的树状数组上修改。那么对于 $pos[x]<d$ 的情形有应该怎么办呢？

设 $td=d-pos[x]$，在最后一中情形下修改我们发现其实是这样的两段：一段是修改**该链**上的值，另一端是修改**除了该链**的其他链的前 $td$ 个值（其实还有第三段就是根节点得加一下）。明显，第一段也包含前 $td$ 个，故将第一段拆开，变成修改**该链**上的 $[1,td]$ 和**该链**上的 $[td+1,pos[x]+d]$。于是我们就将原来所需修改的两段转化成了这样的两段：

(1).将**所有链**的前 $td$ 个值进行修改

(2).将**该链**的 $[td+1,pos[x]+d]$ 进行修改

对于(2)直接修改就行了，关键是(1)。这使我们想到维护一个全局的树状数组，所有共同加的操作就加在这个树状数组就行了。

查询操作就很显而易见了，只要算全局树状数组查询值+所在链的查询值即可。

```
#include <bits/stdc++.h>
#define MAXN 100009
using namespace std;
int mp[MAXN],pos[MAXN],ltn;
int d0; // the value in node 1
deque<int> G[MAXN];
inline int lowbit(int x){ return x&(-x); }
class bitree{
    vector<int> c;
    int size;
public:
    bitree() : c(1,0),size(0){}
    inline void grow(){ c.push_back(0);++size; }
    inline void build(int n){ c.resize(n+1);size=n;}
    inline int length(){ return size; }
    int getval(int x){
        int sum=0;
        for(int i=x;i;i-=lowbit(i))
            sum+=c[i];
        return sum;
    }
    void updata(int x,int d){
        if(x>size) return;
        for(int i=x;i<=size;i+=lowbit(i))
            c[i]+=d;
    }
    void updata(int l,int r,int d){
        updata(l,d);
        updata(r+1,-d);
    }
} path,lt[MAXN];
void dfs(int u,int fa,int ltid){
    lt[ltid].grow();
    mp[u]=ltid;
    pos[u]=lt[ltid].length();
    for(auto v:G[u]){
        if(v==fa) continue;
        dfs(v,u,ltid);
    }
}
int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    pos[0]=mp[0]=mp[1]=pos[1]=-1;
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(auto rt:G[1]){
        dfs(rt,1,ltn);
        ++ltn;
    }
    path.build(n);
    while(q--){
        int op;
        scanf("%d",&op);
        if(op==0){
            int v,x,d;
            scanf("%d%d%d",&x,&v,&d);
            if(x==1){
                d0+=v;
                path.updata(1,d,v);
            }
            else if(pos[x]>d)
                lt[mp[x]].updata(pos[x]-d,pos[x]+d,v);
            else if(pos[x]==d){
                lt[mp[x]].updata(1,pos[x]+d,v);
                d0+=v;
            }
            else {
                int td=d-pos[x];
                path.updata(1,td,v);
                lt[mp[x]].updata(td+1,pos[x]+d,v);
                d0+=v;
            }
        }
        else if(op==1){
            int x;
            scanf("%d",&x);
            if(x==1)
                printf("%d\n",d0);
            else
                printf("%d\n",path.getval(pos[x])+lt[mp[x]].getval(pos[x]));
        }
    }
    return 0;
}
```


---

## 作者：MCAdam (赞：0)

[题目](https://www.luogu.com.cn/problem/CF276E)

翻译里忘说了，除了$1$号点，每个点的度数最多为$2$，~~也就是一个大菊花~~

那么除了$1$号节点，其他的节点都属于其中一条链

思路很简单：对于修改的某一个节点，如果它延伸的范围没有超过它所在的链的范围，就只用修改这条链上的某一个区间；否则其他的链也要修改

思路都大同小异，关键是怎么写，这里提供一种自认为较为简单的写法：

- 要维护的操作

因为只需要区间修改、单点查询，所以不需要维护懒标记，直接在当前区间权值加，递归到下一层时传下去（其实就是懒标记和权值合成一个了）。这样写起来，感觉比差分的树状数组要好一点，代码量都差不多（而且都是板子），但细节比树状数组要少

```cpp
struct tree
{
	int val[4*N];
	inline void pushdown(int p)
	{
		if(val[p])
		{
			val[p*2]+=val[p];
			val[p*2+1]+=val[p];
			val[p]=0;
		}
	}
	inline void change(int p,int left,int right,int l,int r,int c)
	{
		if(l>r) return;
		if(l<=left&&r>=right){ val[p]+=c; return; }
		pushdown(p);
		int mid=(left+right)/2;
		if(l<=mid) change(p*2,left,mid,l,r,c);
		if(r>mid) change(p*2+1,mid+1,right,l,r,c);
	}
	inline int query(int p,int left,int right,int pos)
	{
		if(left==right) return val[p];
		pushdown(p);
		int mid=(left+right)/2;
		if(pos<=mid) return query(p*2,left,mid,pos);
		else return query(p*2+1,mid+1,right,pos);
	}
}t1,t2;
```


- 线段树的个数

因为有多条链，当然可以选择对每一条链都开一棵线段树，然后修改多条链时，一条条修改？复杂度爆炸！

首先没有必要开多棵线段树，只要保证在同一条链上的节点，对应到线段树上是挨在一起的就可以了。所以我们对每一个节点的$dfs$序维护一棵线段树

那怎么同时修改多条链呢？注意到，修改多条链时都是从$1$号点出发，每条链都固定地从起点修改$dis$长度，就类似于一个同心圆扩散出去，一层层修改。换句话说，如果要多条链同时修改，那么同一深度（同一层）的节点对应到线段树是挨在一起的。所以我们再对每一个节点的$bfs$序维护一棵线段树

- 关于编号

自己在做这道题时，把上面“线段树的个数”想好后，就急冲冲地想开打$dfs$和$bfs$。然后意识到，除了要知道每个节点的$dfs,bfs$序，还要知道它属于哪条链，每一条链的开头和结尾的$dfs$序，并且因为每条链的长度不同，一层层扩散出去时，可能有的链已经没有了，有的链却还能往后，所以还要知道每一深度$bfs$序最大是多少，好麻烦！！！

而这一切都只是因为一个问题：每条链的长度不同！既然如此，那我们手动把每一条链都拉成一样长的不就好了吗？把每一条链的长度都拉成最长那条链那么长就可以了

为什么这样写会很简单？只要知道了链的个数$cnt$，最长的链的长度$maxn$，每个节点的深度$dep[p]$（$1$号点的深度为$0$），和它所属的链$col[p]$（从$1$开始编号），就能快速计算出上面需要的所有信息，也不用真的去给每条链后面加上一些新的点。想一想就知道了，举个例子，计算$p$的$dfs,bfs$序：

$dfs(p)=(col[p]-1)\times maxn+dep[p]$

$bfs(p)=(dep[p]-1)\times cnt+col[p]$

现在只需要枚举从$1$出发的每个点$dfs$就好了，就可以知道上面需要的四个信息

```cpp
for(int i=fir[1];i;i=e[i].nxt)//链式前向星
{
	int q=e[i].to;
	cnt++,dfs(q,1);
	maxn=max(maxn,h[cnt]);
}

inline void dfs(int p,int fa)
{
	dep[p]=dep[fa]+1;
	for(int i=fir[p];i;i=e[i].nxt)
		if(e[i].to!=fa) dfs(e[i].to,p);
	col[p]=cnt,h[cnt]=max(h[cnt],dep[p]);
}
```

- 一些细节

1、特判$1$号点修改和查询的情况

2、修改时注意修改的右端点是否越界：修改一条链时，和这条链的结尾的$dfs$序取$\min$（同样可以直接计算出来）；修改多条链时，和整个树的大小取$\min$（包括那些虚空加上去的点）

3、注意，如果修改某个点能扩展到其他的链，那么修改它本身这条链和所有链一起修改时会有重复修改的情况，算一下这个点跑到$1$再跑回来最多能跑到哪里,修改这条链就从这个位置$+1$开始，上面的就让另外一棵线段树来修改

$st=1+(col[p]-1)*maxn+(dep[b]-d)+1$

完整代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N=2e5+10;
int tot,cnt;
int fir[N],dep[N],col[N],h[N];
struct edge
{
	int to;
	int nxt;
}e[2*N];
inline void add(int x,int y)
{
	e[++tot].to=y; e[tot].nxt=fir[x]; fir[x]=tot;
	e[++tot].to=x; e[tot].nxt=fir[y]; fir[y]=tot;
}
inline void dfs(int p,int fa)
{
	dep[p]=dep[fa]+1;
	for(int i=fir[p];i;i=e[i].nxt)
		if(e[i].to!=fa) dfs(e[i].to,p);
	col[p]=cnt,h[cnt]=max(h[cnt],dep[p]);
}
struct tree//线段树
{
	int val[4*N];
	inline void pushdown(int p)
	{
		if(val[p])
		{
			val[p*2]+=val[p];
			val[p*2+1]+=val[p];
			val[p]=0;
		}
	}
	inline void change(int p,int left,int right,int l,int r,int c)
	{
		if(l>r) return;
		if(l<=left&&r>=right){ val[p]+=c; return; }
		pushdown(p);
		int mid=(left+right)/2;
		if(l<=mid) change(p*2,left,mid,l,r,c);
		if(r>mid) change(p*2+1,mid+1,right,l,r,c);
	}
	inline int query(int p,int left,int right,int pos)
	{
		if(left==right) return val[p];
		pushdown(p);
		int mid=(left+right)/2;
		if(pos<=mid) return query(p*2,left,mid,pos);
		else return query(p*2+1,mid+1,right,pos);
	}
}t1,t2;
int main()
{
	int n,m,opt,a,b,c,maxn=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	for(int i=fir[1];i;i=e[i].nxt)
	{
		int q=e[i].to;
		cnt++,dfs(q,1);
		maxn=max(maxn,h[cnt]);
	}
	n=cnt*maxn+1;//注意修改树的大小
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&opt,&a);
		if(opt)
		{
			if(a==1){ printf("%d\n",t1.query(1,1,n,1)+t2.query(1,1,n,1)); continue; }//特判在1查询的情况
			int id1=1+(col[a]-1)*maxn+dep[a];//dfs序
			int id2=1+(dep[a]-1)*cnt+col[a];//bfs序
			printf("%d\n",t1.query(1,1,n,id1)+t2.query(1,1,n,id2));
		}
		else
		{
			scanf("%d%d",&c,&b);
			if(a==1){ t2.change(1,1,n,1,min(1+b*cnt,n),c); continue; }//特判在1修改的情况
			int id1=1+(col[a]-1)*maxn+dep[a];//dfs序
			int id2=1+(col[a]-1)*maxn+(b-dep[a]);//重合的最深的点
			int len=1+col[a]*maxn;
			if(dep[a]>b) t1.change(1,1,n,id1-b,min(id1+b,len),c);
			else
			{
				t1.change(1,1,n,id2+1,min(id1+b,len),c);//id2+1就是这条链上修改的起点
				t2.change(1,1,n,1,min(1+(b-dep[a])*cnt,n),c);
			}
		}
	}
	return 0;
}
```



---

## 作者：_lxy_ (赞：0)

### 题意

略。

### 分析

首先处理出所有链，对于修改操作，可以分两种情况讨论。设当前节点为 $u$ ，距离为 $d$ ，位于第 $num$ 条链，在根以下第 $depth$ 层。

第一种情况，若 $depth \geq d$ ，此时操作与其它链无关。可以给每条链建一个线段树，每次给区间 $[depth-d,depth+d]$ 的节点都加上 $x$ 。

第二种情况，若 $depth < d$ ,此时所有在根以下 $[1,d-depth]$ 层的节点都需要加上 $x$ ，由于每次都是对整层的节点进行操作，因此再建一棵线段树，维护每一层加上的权值。除此之外，自己链上的符合要求的节点也需要加，就按照第一种情况的做法就行，需要注意刨掉在之前加过的几层里的节点。

对于查询操作，输出它所在层加的权值加上在本链中加的权值，需要注意特判一下大根。

开线段树时需要使用 vector ，不然 $10^5 \times 10^5$ 肯定会 MLE。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mem(a,b) memset(a,b,sizeof(b))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> Pair;
const int inf=2139062143;
const int MAXN=1e5+7;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
    register T1 x=0;register bool f=false;char ch=getchar();
    while(ch<'0') f|=(ch=='-'),ch=getchar();
    while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x=(f?-x:x);a=x;qread(b...);
}
inline int qmax(const int &x,const int &y){return x>y?x:y;}
inline int qmin(const int &x,const int &y){return x<y?x:y;}
int n,q,cnt,dep[MAXN],mp[MAXN],sz[MAXN];
vector<int>tree[MAXN];
vector<int>b[MAXN];
void dfs(int u,int fa,int x)
{
    int tmp=x;
    if(fa==1) tmp=++cnt;
    if(fa!=-1) b[tmp].push_back(u);
    for(auto v:tree[u])
    {
        if(fa==v) continue;
        if(fa==1||fa==-1) dfs(v,u,tmp);
        else dfs(v,u,x);
    }
}
struct Seg_Tree
{
    vector<ll>Tree,tag;
    inline ll ls(ll p){return p<<1;}
    inline ll rs(ll p){return p<<1|1;}
    inline void push_up(ll p){Tree[p]=Tree[ls(p)]+Tree[rs(p)];}
    inline void f(ll p,ll l,ll r,ll k)
    {
        tag[p]+=k;
        Tree[p]+=(r-l+1)*k;
    }
    void push_down(ll p,ll l,ll r)
    {
        ll mid=(l+r)>>1;
        f(ls(p),l,mid,tag[p]);
        f(rs(p),mid+1,r,tag[p]);
        tag[p]=0;
    }
    void update(ll p,ll l,ll r,ll L,ll R,ll k)
    {
        if(L<=l&&r<=R) 
            Tree[p]+=(r-l+1)*k,tag[p]+=k;
        else
        {
            ll mid=(l+r)>>1;
            push_down(p,l,r);
            if(L<=mid) update(ls(p),l,mid,L,R,k);
            if(R>mid) update(rs(p),mid+1,r,L,R,k);
            push_up(p);
        }
    }
    ll query(ll p,ll l,ll r,ll L,ll R)
    {
        if(L<=l&&r<=R) return Tree[p];
        else
        {
            ll mid=(l+r)>>1,res=0;
            push_down(p,l,r);
            if(L<=mid) res+=query(ls(p),l,mid,L,R);
            if(R>mid) res+=query(rs(p),mid+1,r,L,R);
            return res;
        }
    }
}t1,t[MAXN];
signed main()
{
    qread(n,q);int i,j,mx=0,cnt1=0; // cnt1记录的是大根加的权值
    for(i=0;i<n-1;i++)
    {
        int u,v;qread(u,v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1,-1,0); // 处理出每条链
    for(i=1;i<=cnt;i++) 
    {
        b[i].insert(b[i].begin(),0);
        for(j=1;j<b[i].size();j++) 
        {
            mp[b[i][j]]=i; // 记录节点所在链的编号
            dep[b[i][j]]=j; // 记录节点在根下的层数
        }
        mx=qmax(mx,b[i].size()-1); // 最大深度
        sz[i]=b[i].size()-1; // 链的长度
    }
    for(i=1;i<=cnt;i++)
    {
        t[i].Tree.resize(mx<<2);
        t[i].tag.resize(mx<<2);
    }
    t1.tag.resize(mx<<2);t1.Tree.resize(mx<<2);
    while(q--)
    {
        int op,u,x,d;qread(op,u);
        int depth=dep[u],num=mp[u];
        if(op) // 查询
        {
            if(u==1) printf("%d\n",cnt1);
            else printf("%d\n",t1.query(1,1,mx,depth,depth)+t[num].query(1,1,sz[num],depth,depth));
        }
        else
        {
            qread(x,d);
            if(u==1) // 特别处理为大根的情况
            {
                cnt1+=x;
                t1.update(1,1,mx,1,qmin(d,mx),x);
                continue;
            }
            if(depth-d>=0) // 不牵扯其它链
            {
                t[num].update(1,1,sz[num],depth-d,qmin(depth+d,sz[num]),x);
                if(depth==d) cnt1+=x;
            }
            else // 牵扯其它链
            {
                cnt1+=x;
                if(d-depth+1<=sz[num]) t[num].update(1,1,sz[num],qmin(d-depth+1,sz[num]),qmin(depth+d,sz[num]),x);
                t1.update(1,1,mx,1,qmin(d-depth,mx),x);
            }
        }
    }
    return 0;
}
```

---

