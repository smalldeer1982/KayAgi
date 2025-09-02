# Bipartite Checking

## 题目描述

You are given an undirected graph consisting of $ n $ vertices. Initially there are no edges in the graph. Also you are given $ q $ queries, each query either adds one undirected edge to the graph or removes it. After each query you have to check if the resulting graph is bipartite (that is, you can paint all vertices of the graph into two colors so that there is no edge connecting two vertices of the same color).

## 样例 #1

### 输入

```
3 5
2 3
1 3
1 2
1 2
1 2
```

### 输出

```
YES
YES
NO
YES
NO
```

# 题解

## 作者：Halberd_Cease (赞：19)

从这个线段树分治板子题，从头整理一下线段树分治的一些重点。

首先看到本题，如果只有添加边一种操作的话，显然是可以用扩展域并查集维护的，如果不会可以翻到本文最后面有讲。

但是本题有删除边的操作，这就不能只用并查集维护了。

我们考虑一个 $O(n^2)$ 的暴力（设 $n,m$ 同阶），对每一个询问，找到有哪些边在这个询问时是存在的，然后直接在空并查集上加边，最后判断是否为二分图。

考虑这个暴力不足的地方：由于操作是对一个时间区间都存在，有一些边在下一个询问中仍然是存在的，但是我们将其全部删掉了。我们的并查集虽然不能支持删除边，但是可以撤销（可撤销并查集也见文末）！如果我们知道相对下一个询问，我们需要撤销哪些边，再加上哪些边，是不是可以优化复杂度呢？

### 线段树分治的思想

我们对时间（询问）建立一颗线段树，树的节点存的信息是【覆盖了这个区间的操作】。

考虑遍历整颗线段树，维护一颗可撤销并查集。当进入一个线段树的子节点时，在并查集上添加覆盖这个区间的边。然后继续递归子节点，直到叶子节点（对应的就是一个询问），统计对应的答案。回溯时，将这个节点加的边在并查集上撤销。

这样，递归到每一个叶子节点时，并查集中的边都是这个询问的完整状态。

分析复杂度，遍历线段树的时间是 $O(n\log n)$ 的，总共 $O(n)$ 个操作，每一个操作在线段树上最多覆盖 $\log n$ 个节点，可撤销并查集由于不能使用路径压缩，所以按秩合并的复杂度是 $O(\log n)$ 的，维护操作的复杂度是 $O(n\log^2n)$ 的。

这就是线段树分治。

### 看到什么应该想到线段树分治？

- 多个操作，每一个操作的影响范围是一个区间（时间区间，询问区间）。

- 多个询问，询问（某个时间时，某个操作后的）答案。

比如本题：操作为删除或者添加边，也就是说一条边的影响范围是一个区间。同时在每一次操作后求答案（是否为二分图）。

### 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
struct BCJ //可撤销并查集
{
    int n;
    int fa[200010];
    int dep[200010];
    void init(int x)
    {
        n=x;
        for(int i=1;i<=2*n;i++)
        {
            fa[i]=i;
            dep[i]=1;
        }
    }
    int find(int x)
    {
        return x==fa[x]?x:find(fa[x]);
    }
    void merge(int x,int y,stack<int>&sta)
    {
        x=find(x),y=find(y);
        if(x==y)return;
        if(dep[x]<dep[y])swap(x,y);
        fa[y]=x;
        dep[x]=max(dep[x],dep[y]+1);
        sta.push(y);
    }
    void roll_back(stack<int>&sta)
    {
        while(!sta.empty())
        {
            int x=sta.top();
            sta.pop();
            fa[x]=x;
        }
    }
}bcj;
struct EDGE
{
    int x,y;
}edge[200010];
vector<int> tr[800010];
int n,m;
bitset<200010>ans;
void update(int now,int l,int r,int ll,int rr,int e)
{
    if(l>rr||r<ll)return ;
    if(ll<=l&&rr>=r)
    {
        tr[now].push_back(e); //操作标记
        return ;
    }
    int mid=l+r>>1;
    update(now<<1,l,mid,ll,rr,e);
    update(now<<1|1,mid+1,r,ll,rr,e);
}
void getans(int now,int l,int r)
{
    stack<int>sta;
    for(auto x:tr[now]) //加边
    {
        if(bcj.find(edge[x].x)==bcj.find(edge[x].y))
        {
            for(int i=l;i<=r;i++)
            {
                ans[i]=0;
            }
            bcj.roll_back(sta);
            return ;
        } //剪枝，如果在边没加完就已经冲突了，再加边也不可能成为二分图，于是整个区间都不可能成为答案。
        bcj.merge(edge[x].x,edge[x].y+n,sta);
        bcj.merge(edge[x].x+n,edge[x].y,sta);
    }
    if(l!=r) //非叶子节点继续递归
    {
        int mid=l+r>>1;
        getans(now<<1,l,mid);
        getans(now<<1|1,mid+1,r);
    }
    bcj.roll_back(sta);
}
map<pair<int,int>,int>mp;
int cnte=0;
signed main()
{
    ans.set();
    cin>>n>>m;
    bcj.init(n);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        if(mp[{x,y}])
        {
            int from=mp[{x,y}];
            cnte++;
            edge[cnte].x=x,edge[cnte].y=y;
            update(1,1,m,from,i-1,cnte);
            mp[{x,y}]=0;
        }
        else
        {
            mp[{x,y}]=i;
        }
    }
    for(auto x:mp)
    {
        if(x.second)
        {
            cnte++;
            edge[cnte].x=x.first.first,edge[cnte].y=x.first.second;
            update(1,1,m,x.second,m,cnte);
        }
    }
    getans(1,1,m);
    for(int i=1;i<=m;i++)
    {
        cout<<(ans[i]?"YES\n":"NO\n");
    }
}
```

不知道谁的[线段树分治题单](https://www.luogu.com.cn/training/231450)，希望有用。


### 扩展域并查集

有很多形式，这里只讲维护二分图的。

考虑对于每一个真实的点，建立【反点】，并查集上点 $x$ 和点 $y$ 的反点连一条边，意义是点 $x$ 不能和点 $y$ 在二分图的同一个部。

真实的图中连一条边，说明两个点不能在一个部中，这时分别给对方的反点在并查集上连边，完成操作。

如果一次操作连接点 $x$ 和点 $y$，但是并查集中 $x$ 和 $y$ 在一个树中，就不是二分图。

### 可撤销并查集

考虑并查集操作：把 $x$ 指向 $y$，操作前 $x,y$ 都是根节点，撤销一次操作就是把 $x$ 指向自己。

撤销需要按操作的顺序来，也就是说需要用栈将进行的操作存下来，需要撤销的时候直接弹栈，令 $fa_x\gets x$ 即可。

具体可以参考上面的代码理解。

---

## 作者：hehelego (赞：5)

喜闻乐见的EDU round板子题.
~~坐等神仙@NaCly_Fish发在线做法~~

套用线段树分治.保证一条边被插入次数是$O(log\,m)$的.然后dfs这个线段树.
保证进入区间$[l,r]$时,有且仅有在时间$[l,r]$一直存在的边被考虑到.

一直维持这个性质走到叶子即可回答询问.回溯时可以反向撤销.这样我们维护的所谓动态图只有加边,判同色不相邻能否二染色,撤销最后一条加入的边.~~显然是LCT~~用带权并查集的trick判断二分图,用按size/height合并保证树高,并且保证单次merge只改变$O(1)$条并查集中的边所以可以支持高效撤销.


哦似乎没扯怎么判二分图?我们维护原图的任意一个生成树,插入一条边,如果是连接两个不相交的树,那么必然没有矛盾.

如果插入的边形成奇环,那么之后不论如何加入边都不是二分图,奇环?就是生成树上的距离为偶数,再加一条边形成的.$d(x,y)\equiv d(x)+d(y)-2d(lca)\pmod 2$很明显后面的没了...然后就是维护到根的距离...这个是带权并查集可以做的.当然也可以暴力LCT...看样子时间很松.lct也能轻松过?

----

思想讲完了.我们扔代码跑路...线段树分治这个trick.可以参考这里学习.

2014年集训队论文:线段树在一类分治问题上的应用.
(btw,这个东西和所谓cdq/gyz分治应该是比较接近的东西....有点类似于点分治和重心剖分的关系...线段树分治这个技巧中要建出了分治过程的递归树结构)


```cpp
#include <bits/stdc++.h>
const int N=200000+10;
int n,m,ans[N];
struct E{ int u,v; E(int a,int b):u(a),v(b){} };
std::map<int,int> g[N];

int L[N<<2],R[N<<2];
std::vector<E> tag[N<<2];
#define lc (o<<1)
#define rc ((o<<1)|1)
void build(int o,int l,int r){
	L[o]=l;R[o]=r; if(l==r) return ;
	int mid=(l+r)>>1;
	build(lc,l,mid); build(rc,mid+1,r);
}
// 把一条边拆到logm个区间上去.
// 可以说线段树只是用来保证复杂度的...
void query(int o,int l,int r,const E&e){
	if(L[o]>r||R[o]<l) return ;
	if(l<=L[o]&&R[o]<=r){ tag[o].push_back(e); return ; }
	query(lc,l,r,e); query(rc,l,r,e);
}

//merged tree(root=x)->tree(root=y)
struct P{ int x,y; P(int a,int b):x(a),y(b){} };
int fa[N],size[N],dis[N];
inline int getpar(int x){
	while(fa[x]!=x) x=fa[x];
	return x;
}

// 到并查集根所经过的边数mod2.
// mod2意义下的加法即为xor.
// 用来查询x和根是不是相同颜色.
inline int getdis(int x){
	int d=0;
	while(fa[x]!=x){ d^=dis[x]; x=fa[x]; }
	return d;
}
/// 按照size合并.
inline int solve(int x,int y,std::stack<P> &stk){
	int dx=getdis(x),dy=getdis(y);
	x=getpar(x);y=getpar(y);
	if(x==y) return (dx^dy);
	if(size[x]>size[y]){ std::swap(x,y); std::swap(dx,dy); }
	size[y]+=size[x];
	fa[x]=y; dis[x]=(dx^dy^1);
	stk.push(P(x,y));
	return 1;
}
// 撤销(x->y)的合并.拆出来,size改回去.dis改成0
inline void back(P p){
	int x=p.x,y=p.y;
	size[y]-=size[x];
	dis[fa[x]=x]=0;
}
// 递归线段树,进入区间[l,r]时
// 保证时间轴上[l,r]范围内一直可用的边都被加入了
void dfs(int o,int flag){
	std::stack<P> stk;
	for(auto e:tag[o]) flag&=solve(e.u,e.v,stk);
	if(L[o]==R[o]) ans[L[o]]=flag;
	else{ dfs(lc,flag); dfs(rc,flag); }
// 撤销操作...不然从爸爸进入兄弟节点的时候开始讲到的那个性质会被破坏.
// 注意撤销顺序...
	while(!stk.empty()){ back(stk.top()); stk.pop(); }
}

int read(){
	int x=0;char c;
	do{c=getchar();}while(!isdigit(c));
	do{x=x*10+c-'0';c=getchar();}while(isdigit(c));
	return x;
}
int main(){
	n=read();m=read(); build(1,1,m);
	int x,y;
	for(int i=1;i<=m;i++){
		x=read();y=read(); if(x>y) std::swap(x,y);
		if(g[x][y]==0) g[x][y]=i;
		else{
			query(1,g[x][y],i-1,E(x,y));
			g[x][y]=0;
		}
	}
	for(int i=1;i<=n;i++){
		size[fa[i]=i]=1;
		for(auto p:g[i]) if(p.second>0)
			query(1,p.second,m,E(i,p.first));
	}
	dfs(1,1);
	for(int i=1;i<=m;i++) puts(ans[i]?"YES":"NO");
	return 0;
}

```



---

## 作者：SSerxhs (赞：3)

线段树分治+带权并查集

用线段树维护时间轴，把每条边覆盖的时间用vector存在对应的线段树节点上。遍历线段树时使用可撤销带权并查集维护两点之间距离奇偶，在连边时如果两点之间距离为2的倍数则图不是二分图，直接把当前节点下的所有询问都回答NO。当递归到叶子的时候答案为YES。

```cpp
#include <stdio.h>
#include <string.h>
#include <set>
#include <vector>
using namespace std;
typedef pair<int,int> pa;
const int N=1e5+2,M=4e5+2;
vector<pa> s[M];
set<pa> lj[N];
set<pa>::iterator it;
pa st[N],cr;
int f[N],rk[N],len[N],l[M],r[M];
int n,m,q,i,x,y,z,u,v,c,tp;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
void build(int x)
{
	while (l[x]<r[x])
	{
		l[c=x<<1]=l[x];r[c]=l[x]+r[x]>>1;
		l[c|1]=r[c]+1;r[c|1]=r[x];
		build(c);x=x<<1|1;
	}
}
void add(int x)
{
	if ((z<=l[x])&&(r[x]<=y))
	{
		s[x].push_back(cr);
		return;
	}
	if (z<=r[x<<1]) add(x<<1);
	if (y>r[x<<1]) add(x<<1|1);
}
void getf(int &x,int &y)
{
	y=0;
	while (f[x]!=x)
	{
		y^=len[x];
		x=f[x];
	}
}
inline int uni(int x,int y)
{
	getf(x,u);getf(y,v);
	if (x!=y)
	{
		if (rk[x]>rk[y]) swap(x,y);
		f[x]=y;cr.first=x;len[x]=u^v^1;
		cr.second=rk[y];
		if (rk[x]==rk[y]) ++rk[y];
		st[++tp]=cr;return 0;
	}
	return (u^v^1);
}
inline void del(pa &x)
{
	rk[f[x.first]]=x.second;
	f[x.first]=x.first;
}
void sum(int x)
{
	int cur=tp;
	for (i=0;i<s[x].size();i++) if (uni(s[x][i].first,s[x][i].second))
	{
		while (tp>cur) del(st[tp--]);
		for (i=l[x];i<=r[x];i++) puts("NO");
		return;
	}
	if (l[x]==r[x]) {puts("YES");while (tp>cur) del(st[tp--]);return;}
	sum(x<<1);sum(x<<1|1);
	while (tp>cur) del(st[tp--]);
}
int main()
{
	read(n);read(q);m=n<<1;
	r[l[1]=1]=q;build(1);
	for (i=1;i<=n;i++) f[i]=i;
	for (i=1;i<=q;i++)
	{
		read(u);read(v);
		if (u>v) swap(u,v);
		cr.first=v;cr.second=0;
		it=lj[u].lower_bound(cr);
		if ((it==lj[u].end())||((*it).first!=v))
		{
			cr.second=i;
			lj[u].insert(cr);
		}
		else
		{
			z=(*it).second;y=i-1;
			lj[u].erase(it);
			cr.first=u;cr.second=v;add(1);
		}
	}
	for (i=1;i<=n;i++) for (it=lj[i].begin();it!=lj[i].end();it++)
	{
		cr.first=i;cr.second=(*it).first;
		z=(*it).second;y=q;add(1);
	}
	sum(1);
}
```


---

## 作者：da32s1da (赞：3)

分治+LCT

考虑把每条边出现的区间$[L,R]$找出来，然后分治。

每次加入一条边$(u,v,L,R)$时，若$u,v$不连通，直接连，若联通，判断长度是否为偶数，为偶数则$[L\dots R]$全为$NO$，为奇数**不进行任何操作**。

然后分治$[l,mid]$，$[mid+1,r]$。最后撤销加入的边。

```
#include<cstdio>
#include<map>
#include<vector>
using namespace std;
const int N=1e5+50;
int n,q,x,y,z;
int zn[N],cnt;
map<int,int>mp[N];
typedef map<int,int>::iterator IT;
struct node{
	int x,y,l,r;
	node(){}
	node(int X,int Y,int L,int R):x(X),y(Y),l(L),r(R){}
};
vector<node>vp;
inline void swap(int &u,int &v){int o=u;u=v;v=o;}
struct lct{
	int ch[N][2],fa[N],tagrev[N],sum[N];
	bool isrot(int x){
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	void rev(int x){
		tagrev[x]^=1;
		swap(ch[x][0],ch[x][1]);
	}
	void pushdown(int x){
		if(!isrot(x))pushdown(fa[x]);
		if(!tagrev[x])return;
		tagrev[x]=0;
		rev(ch[x][0]);rev(ch[x][1]);
	}
	void update(int x){
		sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+1;
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],opt=(ch[y][1]==x),w=ch[x][opt^1];
		if(!isrot(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
		ch[y][opt]=w;fa[w]=y;
		ch[x][opt^1]=y;fa[y]=x;
		update(y);update(x);
	}
	void splay(int x){
		int y,z;pushdown(x);
		while(!isrot(x)){
			y=fa[x];z=fa[y];
			if(!isrot(y))
			rotate(((ch[y][0]==x)^(ch[z][0]==y))?x:y);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])
		splay(x),ch[x][1]=y,update(x);
	}
	void mktrot(int x){
		access(x);splay(x);rev(x);
	}
	void mkvrot(int x){
		access(x);splay(x);
	}
	void link(int x,int y){
		mktrot(x);mkvrot(y);
		fa[x]=y;
	}
	void cut(int x,int y){
		mktrot(x);mkvrot(y);
		ch[y][0]=fa[x]=0;
		update(y);
	}
	int query(int x,int y){
		mktrot(x);mkvrot(y);int z;
		for(z=y;ch[z][0];z=ch[z][0]);
		return x==z?sum[y]:0;
	}
}s;
void solve(int l,int r,vector<node>&t){
	vector<node>L,R;int cnt_=cnt,mid=l+r>>1;
	for(int i=0,j;i<t.size();i++){
		if(t[i].l==l&&t[i].r==r){//加入边
			j=s.query(t[i].x,t[i].y);//查询两点间路径长度（这里是点的个数）
			if(j&1){//有偶环（奇数个点）
				for(;l<=r;l++)puts("NO");//输出NO
				for(;cnt>cnt_;cnt--)s.cut(t[zn[cnt]].x,t[zn[cnt]].y);//撤销已经加入的边
				return;
			}
			if(!j)s.link(t[i].x,t[i].y),zn[++cnt]=i;//没有连通，则连接
			continue;
		}
		if(t[i].l>mid)R.push_back(t[i]);
		else if(t[i].r<=mid)L.push_back(t[i]);
		else L.push_back(node(t[i].x,t[i].y,t[i].l,mid)),R.push_back(node(t[i].x,t[i].y,mid+1,t[i].r));
	}
	if(l==r){
		puts("YES");
		for(;cnt>cnt_;cnt--)s.cut(t[zn[cnt]].x,t[zn[cnt]].y);//撤销
		return;
	}
	solve(l,mid,L);solve(mid+1,r,R);//分治左右两边
	for(;cnt>cnt_;cnt--)s.cut(t[zn[cnt]].x,t[zn[cnt]].y);//撤销
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)s.sum[i]=1;
	for(int i=1;i<=q;i++){
		scanf("%d%d",&x,&y);
		if(x>y)swap(x,y);
		z=mp[x][y];
		if(z)vp.push_back(node(x,y,z,i-1)),mp[x][y]=0;
		else mp[x][y]=i;
	}
	for(int i=1;i<=n;i++)
	for(IT j=mp[i].begin();j!=mp[i].end();++j)
	if(j->second)vp.push_back(node(i,j->first,j->second,q));
    //vp数组里放了所有边的存在时间
	solve(1,q,vp);
}
```

---

## 作者：zhangzhixing99 (赞：2)

如果您想拥有更好的阅读体验，您可以尝试[隐藏评论区](https://www.luogu.me/paste/4xb7m0qw)。
## 题目摘要
给你一张动态的图，实时问你它是不是二分图。
## 前置知识
- [动态图连通性](https://www.cnblogs.com/laijinyi/p/18302813/HLT)（~~贴心的~~编者附上了[可撤销并查集](https://zhuanlan.zhihu.com/p/538166784)和[线段树](https://blog.csdn.net/m0_62652820/article/details/138116144)的链接）
- [二分图](https://blog.nowcoder.net/n/0e9a713d93f54bc79739588e928f091a)（看最前面的那些定义就够了，感兴趣的可以往后看看，但这道题不需要）
## 正题开始
第一眼看题目，发现这张图会动态地添加一条边或者删除一条边。  
于是我们想到了动态图连通性。

那如何在维护连通性的过程中判断二分图呢？

根据二分图的定义，我们知道所有的节点都能分在两个集合之一，我们暂且管分在第一个集合的节点叫做$\color{red}{红色节点}$，分在第二个集合的节点叫做$\color{blue}{蓝色节点}$。  
那么我们考虑边。根据定义，我们知道每条边只可能连接一个$\color{red}{红色节点}$和一个$\color{blue}{蓝色节点}$。  
很容易想到，一张图不是二分图，当且仅当一条边连接了相同颜色的节点。

于是我们尝试利用可撤销并查集来维护这个过程。  
根据并查集的性质，我们会在图中选取一个起到代表作用的节点，我们暂且称这是图的"根"。

我们仍然考虑当前图还可以展开成一颗树（即没有环）的情况。  
我们设节点 $u$ 的深度为 $dep_u$，可得 $dep$ 奇偶性相同的节点同颜色，$dep$ 奇偶性不同的节点不同色。  
我们分类讨论：

如果当前节点使一幅图形成了环，则有两种情况：
- 奇偶性相同，即一条边连结了相同颜色的节点。这条边的存在破坏了这幅图的二分图性质，在这条边的生效期间，一直输出 ```NO```。
- 奇偶性不同，即一条边连结了不同颜色的节点，那么这条边的存在没有意义。
---
如果当前节点连接了两幅图（因为一条边连接一幅图的两个节点就会形成环，否则加边之前的图不连通，我们将其拆成两幅图来看）：

我们只需要保查询奇偶性即可，于是我们只需要修改第二幅图的"根"的 $dep$ 即可。  
我们设 $tag_u$ 为当前节点的奇偶性是否被改过。$tag$ 只需要使用 $\text{bool}$ 数组存储即可，因为修改了两次等价于没修改。

---
这样就衍生出一个问题：根节点修改过后，整幅图所有节点的 $dep$ 都需要修改，时间复杂度爆炸。

我们可以使用动态求 $dep$ 的方法解决这一过程。  
注意到父节点的 $dep$ 可以向子节点传递，于是我们得到：

$dep_u=\begin{cases}
1&\text{if }u=top_u\\
dep_{top_u}+1+tag_u&\text{otherwise}
\end{cases}$

其中 $top_u$ 代表 $u$ 的父亲节点。  
这是一个递归的过程。  
时间复杂度与并查集中的找根函数 $\text{Find}()$ 类似，使用启发式合并可以使时间复杂度降至 $\Theta(\text{log}_2n)$。

于是这道题的理论部分到此结束。
## 实现方法
我们可以使用线段树和可撤销并查集来维护动态图（见```前置知识```中的```动态图连通性```链接）。  
$\text{dfs}()$ 时，每加入一条边，就按照上述过程进行判断，如果判断出加入这条边后破坏了二分图的性质，则直接输出 $r-l+1$ 个 ```NO```（其中 $l$ 和 $r$ 表示在线段树中遍历到的当前线段的左端点和右端点下标）。否则遍历到叶子节点时输出 ```YES```。

我们根据节点构建并查集，根据操作序列构建线段树。  
输入一次操作时，有以下两种情况：
- 没有出现过输入的这条边。加入这条边。
- 出现过这条边。将这条边的出现区间 $\text{push}$ 进线段树后删除这条边的操作记录（即再一次出现输入这条边时就会进入第一种情况）。

输入结束后将残留的拥有操作记录的边一齐 $\text{push}$ 进线段树。  
最后执行一遍 $\text{dfs}()$ 即可。

建议将并查集和线段树写入数据结构中使用。
## 时间复杂度
- 并查集：初始化 $\Theta(n)$，$\text{Find}()$，$\text{Depth()}$，$\text{Merge}()$ 函数均为 $\Theta(\text{log}_2n)$。$\text{undo()}$ 函数时间复杂度 $\Theta(1)$。
- 线段树：初始化 $\Theta(q\text{log}_2q)，$区间修改 $\Theta(\text{log}_2q)$，遍历一遍 $\Theta(q\text{log}_2q)$（只看线段树部分）。
- ```map```：$\Theta(\text{log}_2q)$。
- 总时间复杂度 $\Theta(n+q\text{log}_2q+q{\text{log}_2}^2q+q\text{log}_2q\text{log}_2n)=\Theta(n+q{\text{log}_2}^2q+q\text{log}_2q\text{log}_2n)$。
## 空间复杂度
- 并查集：$\Theta(n+q)$。
- 线段树：$\Theta(q)$。
- 使用 ```map``` 存储输入的边，空间复杂度 $\Theta(q)$。
- 总空间复杂度：$\Theta(n+q)$。
- **不要忘记线段树需要开四倍数组。**
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define EOL '\n'

struct Edge
{
	int u, v;
	Edge(int _u = -1, int _v = -1): u(_u), v(_v) {}
	bool operator < (const Edge &ed) const
	{
		if (u != ed.u)
		{
			return u < ed.u;
		}
		return v < ed.v;
	}
};

struct dsu
{
	int top[100010], sz[100010];
	bool tag[100010];
	stack<Edge> stk;
	dsu() {}
	void init(int n)
	{
		iota(top + 1, top + n + 1, 1);
		fill(sz + 1, sz + n + 1, 1);
		fill(tag + 1, tag + n + 1, false);
		while (!stk.empty())
		{
			stk.pop();
		}
	}
	int Find(int u)
	{
		return (u == top[u]? u : Find(top[u])); 
	}
	int Depth(int u)
	{
		return (u == top[u]? 1: Depth(top[u]) + !tag[u]);
	}
	bool Merge(int u, int v)
	{
		int tu = Find(u), tv = Find(v);
		if (sz[tu] < sz[tv])
		{
			swap(u, v);
			swap(tu, tv);
		}
		int du = Depth(u), dv = Depth(v);
		if (tu == tv)
		{
			stk.push(Edge(-1, -1));
			return (du & 1) != (dv & 1);
		}
		top[tv] = tu;
		tag[tv] = ((du & 1) != (dv & 1));
		stk.push(Edge(tu, tv));
		return true;
	}
	void undo()
	{
		Edge ed = stk.top();
		stk.pop();
		int u = ed.u, v = ed.v;
		if (u == -1)
		{
			return;
		}
		top[v] = v;
		tag[v] = false;
	}
} G;

struct Node
{
	int lft, rht;
	vector<Edge> edges;
	Node(int __lft = -1, int __rht = -1): lft(__lft), rht(__rht)
	{
		edges.clear();
	}
};

struct sgt
{
	Node nodes[400010];
	sgt() {}
	void build(int u, int l, int r)
	{
		nodes[u] = Node(l, r);
		if (l != r)
		{
			int mid = l + ((r - l) >> 1);
			build(u << 1, l, mid);
			build(u << 1 | 1, mid + 1, r);
		}
	}
	void init(int n)
	{
		build(1, 1, n);
	}
	void push(int u, int l, int r, Edge ed)
	{
		int L = nodes[u].lft, R = nodes[u].rht;
		if (l <= L && R <= r)
		{
			nodes[u].edges.push_back(ed);
			return;
		}
		if (l <= nodes[u << 1].rht)
		{
			push(u << 1, l, r, ed);
		}
		if (nodes[u << 1 | 1].lft <= r)
		{
			push(u << 1 | 1, l, r, ed);
		}
	}
	void dfs(int u)
	{
		int cnt = 0;
		bool no = false;
		for (Edge ed: nodes[u].edges)
		{
			++cnt;
			int u = ed.u, v = ed.v;
			if (!G.Merge(u, v))
			{
				no = true;
				break;
			}
		}
		if (no)
		{
			for (int i = nodes[u].lft; i <= nodes[u].rht; ++i)
			{
				cout << "NO" << EOL;
			}
			while (cnt--)
			{
				G.undo();
			}
			return;
		}
		if (nodes[u].lft != nodes[u].rht)
		{
			dfs(u << 1);
			dfs(u << 1 | 1);
		}
		else
		{
			cout << "YES" << EOL;
		}
		while (cnt--)
		{
			G.undo();
		}
	}
} Q;

map<Edge, int> dfn;

int main()
{
	int n, q;
	cin >> n >> q;
	G.init(n);
	Q.init(q);
	for (int t = 1; t <= q; ++t)
	{
		int u, v;
		cin >> u >> v;
		Edge ed = Edge(u, v);
		if (dfn.count(ed))
		{
			Q.push(1, dfn[ed], t - 1, ed);
			dfn.erase(ed);
		}
		else
		{
			dfn[ed] = t;
		}
	}
	for (pair<Edge, int> timestamp: dfn)
	{
		Q.push(1, timestamp.second, q, timestamp.first);
	}
	Q.dfs(1);
	return 0;
}
```

---

## 作者：LYY_yyyy (赞：2)

线段树分治板子题没人写题解吗？

用 map 记录每条边还未撤销的那条边的编号，输入一条边时看一下是否有还未撤销的边，如果有就把还未撤销的边的时间区间右端点记为当前时间 -1。处理完之后把所有还未确定右端点的边的右端点记为 $m$ 即可。剩下直接拉线段树分治板子即可。用线段树维护时间轴，每次将存在时间划分为线段树上的 $O(\log m)$ 段，最后 dfs 整颗线段树，进入时加边，退出时撤销，用拓展域并查集判断二分图即可。

注意启发式合并时要判断两者是否已经在同一颗树中再累加子树大小，不然启发式是错的。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;typedef pair<int,int> pii;
int g[200010],si[200010],st[200010],tp;
map<pair<int,int>,int> s;
bool ans[200010];
struct node
{
	int l,r;vector<pii> s;
}tr[400010];
struct nod
{
	int x,y,l,r;
}q[100010];
void build(int u,int l,int r)
{
	tr[u]={l,r};if(l==r) return;
	int mid=l+r>>1;build(u<<1,l,mid);build(u<<1|1,mid+1,r);
}
inline int find(int x) 
{
	if(x==g[x]) return x;
	return find(g[x]);
}
inline void op(int x,int y)
{
	x=find(x);y=find(y);
	if(si[x]>si[y]) swap(x,y);
	if(x!=y) si[y]+=si[x];st[++tp]=x;g[x]=y;
}
inline void del()
{
	int p=st[tp--];if(g[p]==p) return;
	si[g[p]]-=si[p];g[p]=p;
}
void dfs(int u)
{
	int cnt=0;
	for(auto o:tr[u].s) 
	{
		op(o.first,o.second+n);op(o.second,o.first+n);cnt+=2;
		if(find(o.first)==find(o.first+n)) 
		{
			while(cnt--) del();
			return;
		}
	}
	if(tr[u].l==tr[u].r)
	{
		ans[tr[u].l]=1;cnt=tr[u].s.size();cnt*=2;while(cnt--) del();
		return;
	}
	dfs(u<<1);dfs(u<<1|1);cnt=tr[u].s.size();cnt*=2;while(cnt--) del();
}
void modify(int u,int x,int y,int l,int r)
{
	if(tr[u].l>=l&&tr[u].r<=r)
	{
		tr[u].s.push_back({x,y});return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify(u<<1,x,y,l,r);
	if(r>mid) modify(u<<1|1,x,y,l,r);
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;for(int i=1;i<=2*n;i++) g[i]=i,si[i]=1;
	int tot=0;build(1,1,m);
	for(int i=1;i<=m;i++)
	{
		int x,y;cin>>x>>y;
		if(!s[{x,y}]) q[++tot]={x,y,i,0},s[{x,y}]=tot; 
		else q[s[{x,y}]].r=i-1,s[{x,y}]=0;
	}
	for(int i=1;i<=tot;i++) if(!q[i].r) q[i].r=m;
	for(int i=1;i<=tot;i++) modify(1,q[i].x,q[i].y,q[i].l,q[i].r);
	dfs(1);string p;
	for(int i=1;i<=m;i++) p=ans[i]?"YES":"NO",cout<<p<<"\n";
	return 0;
}

```

---

## 作者：Llx2022 (赞：2)

# 线段树分治+可撤销并查集+二分图判定的模板题
# Pre Knowledge
**线段树分治**是一种**处理动态修改和询问的离线**算法。

线段树分治**主要思想**：通过将某一元素的出现**时间段**在线段树上保存，最后**离线**处理答案，通过遍历整棵线段树，运用可撤销数据结构维护来得到每个时间点的答案。


简单来说线段树分治就是线段树对应的下标对应的是操作时间，就是个**时间戳**，每个节点存的信息其实就是对于一个在某段时间对答案有影响的操作。

这样的话我们就借助线段树，从根节点进入，每次都执行操作，知道处理到某个时间点的答案，然后回溯，回溯是记得要恢复原貌，这样才能对别的时间没有影响。

**可撤销并查集**：对于每步操作，在操作前维护一下原信息，然后通过启发式合并，进行集合的合并。注意必须**要采用按秩合并**，**不能采用路径压缩**，这里我们引入一个秩的概念：为每一个结点维护一个秩，它表示以该节点为根的树的高度的上界。在做合并操作时，将秩小的根指向秩大的结点。


**二分图判定**：二分图定义就是，节点由两个集合组成，且两个集合内部没有边的图。那么我们找找性质，发现一个很重要的结论就是**二分图不存在长度为奇数的环**，这是因为因为每一条边都是从一个集合走到另一个集合，只有走偶数次才可能回到同一个集合。因此通过这个我们可以快速处理答案。

# **Solution**
对于这题的话我们就维护一个**基于时间**的线段树，每个节点维护个**栈信息**，处理答案的时候，把对当前时间有影响的操作做一遍，回溯又得消除影响，这里使用可撤销并查集，对于二分图判定，我们用并查集维护二分图的连通性，我们选择**扩展域并查集**，每次合并所加的边，这样在之后查询若发现有两个点处在同一个集合，那就必然不是二分图了。
**注意**：因为题目中要求若之前出现过这条边，那么就删除掉，到最后有一些点没有删除，就是相当于到了时间轴的末尾，我们得记得加上这些操作。
# **Time complexity**
线段树带个 $\log$，可撤销并查集的启发式合并带个 $\log$，因此是带两个 $\log$ 的。
$$O(n  \log^2n)$$
# **Code**

```cpp
#include<iostream>
#include<vector>
const int N=1E5+9;
using namespace std;
vector<int> t[N*4*2];
int n,m;
int height[N*2],top,fa[N*2];
struct edge{
	int x,y;
}e[N*2]; 
struct stack{
    int x,y,add;
}st[N*2];
int find(int x){
    while(x!=fa[x]) x=fa[x];
    return fa[x];
}
void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(height[fx]>height[fy]) swap(fx,fy);
    st[++top]={fx,fy,height[fx]==height[fy]};
    fa[fx]=fy;
    //这里别写反了，否则复杂度就爆炸了
    if(height[fx]==height[fy]) height[fy]++;
}
void update(int u,int l,int r,int ql,int qr,int x){
    if(l>qr||r<ql) return ;
    if(ql<=l&&r<=qr){t[u].push_back(x);return;}
    int mid=l+r>>1;
    if(l<=mid)update(u<<1,l,mid,ql,qr,x);
    if(r>mid) update(u<<1|1,mid+1,r,ql,qr,x);
}
void solve(int u,int l,int r){
    int ans=1;
    int lasttop=top;
    int sz=t[u].size();
    for(int i=0;i<sz;i++){
        int a=find(e[t[u][i]].x);
        int b=find(e[t[u][i]].y);
        if(a==b){
            for(int k=l;k<=r;k++){
                puts("NO");
            }
            ans=0;
            break;
        }
        merge(e[t[u][i]].x,e[t[u][i]].y+m);
        merge(e[t[u][i]].y,e[t[u][i]].x+m);
    }
    if(ans){
        if(l==r) puts("YES");
        else{
            int mid=l+r>>1;
            solve(u<<1,l,mid);
            solve(u<<1|1,mid+1,r);
        }
    }
    while(top>lasttop){
        height[fa[st[top].x]]-=st[top].add;
        fa[st[top].x]=st[top].x;
        top--;
    }
    return ;
}
#include<map>
#include<utility>
map<pair<int,int>,int> q;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&e[i].x,&e[i].y);
        if(!q[{e[i].x,e[i].y}])q[{e[i].x,e[i].y}]=i;
        else update(1,1,m,q[{e[i].x,e[i].y}],i-1,i),q[{e[i].x,e[i].y}]=0;
    }
    for(auto i:q){
        if(i.second) update(1,1,m,i.second,m,i.second);
	}
    for(int i=1;i<=2*m;i++){
        fa[i]=i;
        height[i]=1;
    }
    solve(1,1,m);
    return 0;
}
```


---

## 作者：niuzh (赞：1)

此题为线段树分治板子题，所以主要讲解一下线段树分治。

#### 前置芝士

1. 可撤销并查集。
  - 核心思想就是开一个栈存储每一步把哪个根节点变成了某个根节点的儿子，撤销时把存的节点与父亲的边断掉。
2. [线段树](https://oi-wiki.org/ds/seg/)。

#### 思想

二分图可以用并查集判断，但并查集无法删除边，所以可以考虑用线段树分治。

具体思路时用线段树来维护时间轴，每个区间记录这个区间内一直存在的操作。

记录答案时遍历整颗线段树，维护一颗可撤销并查集，当进入一个线段树的子节点时，在并查集上添加覆盖这个区间的边。然后继续递归子节点，直到叶子节点（对应的就是一个询问），统计对应的答案。回溯时，将这个节点加的边在并查集上撤销。

时间复杂度是 $O(m\log n+n\log^2n)$ 的，可以通过。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct unionfind_rollback
{
	int fa[N],sze[N],cnt;
	void init(int x)
	{
		cnt=x;
		for (int i=1; i<=x; i++)
		{
			fa[i]=i;
			sze[i]=1;
		}
	}
	int find(int x)
	{
		return x==fa[x]?x:find(fa[x]);
	}
	void merge(int x,int y,stack<int> &s)
	{
		x=find(x);
		y=find(y);
		if (x==y) return;
		if (sze[x]<sze[y]) swap(x,y);
		sze[x]+=sze[y];
		cnt--;
		fa[y]=x;
		s.push(y);
	}
	void back(stack<int> &s)
	{
		while (!s.empty())
		{
			int tp=s.top();
			s.pop();
			if (tp!=find(tp))
			{
				cnt++;
				sze[find(tp)]-=sze[tp];
			}
			fa[tp]=tp;
		}
	}
} u;
struct node
{
	int x,y;
} edge[N];
vector<int> tree[N];
int n,m,cnt=0;
bitset<N> ans;
map<pair<int,int>,int> mp;
void update(int now,int l,int r,int x,int y,int val)
{
	if (x<=l&&y>=r)
	{
		tree[now].push_back(val);
		return ;
	}
	int mid=l+r>>1;
	if (mid>=x)update(now<<1,l,mid,x,y,val);
	if (mid<y)update(now<<1|1,mid+1,r,x,y,val);
}
void getans(int now,int l,int r)
{
	stack<int> st;
	for (auto x:tree[now])
	{
		if (u.find(edge[x].x)==u.find(edge[x].y))
		{
			for (int i=l; i<=r; i++)
			{
				ans[i]=0;
			}
			u.back(st);
			return ;
		}
		u.merge(edge[x].x,edge[x].y+n,st);
		u.merge(edge[x].x+n,edge[x].y,st);
	}
	if (l!=r)
	{
		int mid=l+r>>1;
		getans(now<<1,l,mid);
		getans(now<<1|1,mid+1,r);
	}
	u.back(st);
}
signed main()
{
	ans.set();
	cin>>n>>m;
	u.init(2*n);
	for (int i=1; i<=m; i++)
	{
		int x,y;
		cin>>x>>y;
		if (mp[ {x,y}])
		{
			int u=mp[ {x,y}];
			cnt++;
			edge[cnt].x=x;
			edge[cnt].y=y;
			update(1,1,m,u,i-1,cnt);
			mp[ {x,y}]=0;
		}
		else
		{
			mp[ {x,y}]=i;
		}
	}
	for (auto x:mp)
	{
		if (x.second)
		{
			cnt++;
			edge[cnt].x=x.first.first,edge[cnt].y=x.first.second;
			update(1,1,m,x.second,m,cnt);
		}
	}
	getans(1,1,m);
	for (int i=1; i<=m; i++)
	{
		cout<<(ans[i]?"YES\n":"NO\n");
	}
	return 0;
}
```

---

## 作者：KobeBeanBryantCox (赞：1)

# CF813F Bipartite Checking 题解

--------------

[题目传送门](https://www.luogu.com.cn/problem/CF813F)。

板子题。

--------------

## 题意

每次加入或删除一条边，问操作完后原图是不是二分图。

--------------

## 思路

首先我们有[这个题](https://www.luogu.com.cn/problem/P5787)。

~~然后就做完。上代码。~~

不能这么水。讲一下线段树分治的思想。

用线段树维护时间轴，将一条边的存在时间放在线段树上，被划分为 $\log n$ 个线段树节点。

这样所有的边的存在时间都在线段树上表示出来了。

然后对线段树 dfs，进入的时候加入这一条边，加入时判断是不是二分图，出去的时候删除这一条边。

加入、删除和判断是不是二分图可以使用 LCT（这个题也可以纯 LCT，不用线段树分治）。

但是这种做法不优美。我们可以使用扩展域可撤销并查集。具体的就是在[关押罪犯](https://www.luogu.com.cn/problem/P1525)中加了个可撤销。

然后怎么求出一条边存在的区间？考虑使用一个 map 存一条边的出现时间，然后删除时再放进线段树中。最后会有一些从始到终都没有删除的边。遍历 map 依次加入线段树即可。

注意这是 CF 题，所以尽量不要用 unordered_map。

因为 CF 有 hack，有些毒瘤会根据 unordered_map 的哈希源码来 hack，让你的 unordered_map 卡到 $O(n)$。

但是有应对方法，你自己手写一个与源码不同的哈希规则即可。

---------------

## AC 代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
int in()
{
	int k=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
void out(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
const int N=1e5+10;
struct dsu
{
	int f[N],high[N],top=0;
	pair<int,int>st[N];
	void init(int n){for(int i=1;i<=n;i++)f[i]=i,high[i]=1;}
	int find(int x){return x==f[x]?x:find(f[x]);}
	void merge(int x,int y)
	{
		x=find(x),y=find(y);
		if(x==y)return;
		if(high[x]>high[y])swap(x,y);
		f[x]=y,st[++top]={x,high[x]==high[y]};
		if(high[x]==high[y])high[y]++;
	}
	void revoke(int lastop)
	{
		for(;top>lastop;top--)
		{
			int x=st[top].first,add=st[top].second;
			high[f[x]]-=add,f[x]=x;
		}
	}
}f;
struct edge{int x,y;}e[N];
bool ans[N];int n;
struct Seg
{
	struct node{int l,r;vector<int>id;}tr[N<<2];
	#define lc (x<<1)
	#define rc (x<<1|1)
	void build(int x,int l,int r)
	{
		tr[x].l=l,tr[x].r=r;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(lc,l,mid),build(rc,mid+1,r);
	}
	void insert(int l,int r,int v,int x=1)
	{
		if(tr[x].l>=l&&tr[x].r<=r)return tr[x].id.push_back(v),void();
		int mid=(tr[x].l+tr[x].r)>>1;
		if(l<=mid)insert(l,r,v,lc);
		if(r>mid)insert(l,r,v,rc);
	}
	void solve(int x=1)
	{
		bool ok=true;int lastop=f.top;
		int mid=(tr[x].l+tr[x].r)>>1;
		for(int i:tr[x].id)
		{
			int u=e[i].x,v=e[i].y;
			if(f.find(u)==f.find(v)){ok=false;break;}
			f.merge(u,v+n),f.merge(v,u+n);
		}
		if(ok)
			if(tr[x].l==tr[x].r)ans[tr[x].l]=1;
			else solve(lc),solve(rc);
		f.revoke(lastop);
	}
}T;
map<pair<int,int>,int>mp;
int cnt=0;
int main()
{
	n=in();int m=in();
	f.init(2*n),T.build(1,1,m);
	for(int i=1;i<=m;i++)
	{
		int x=in(),y=in();
		if(!mp.count({x,y})){mp[{x,y}]=i;continue;}
		e[++cnt]={x,y},T.insert(mp[{x,y}],i-1,cnt);
		mp.erase({x,y});
	}
	for(auto v:mp)e[++cnt]={v.first.first,v.first.second},T.insert(v.second,m,cnt);
	T.solve();
	for(int i=1;i<=m;i++)puts(ans[i]?"YES":"NO");
	return 0;
}
```

------------

## 后记

若不清楚或错误，欢迎评论或私信。

---

## 作者：gyyyyx (赞：1)

模板题

用 map 给每条边编号，然后用一个数组记录该边上一次出现的时间，这样就可以将每条边放进线段树里了。

众所周知，二分图可以用并查集来判定，因此可以用线段树分治加并查集求出答案。

由于我们加入一条边后判断出图不是二分图后无论再怎么加边都不可能让图再变为二分图，因此线段树上一个点如果不是二分图，则它代表的时间段中所有点都不是二分图。

可以略微优化时间复杂度。

代码：

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,m,cnt;
struct Edge{
	int u,v;
	Edge(int a=0,int b=0):u(a),v(b){}
	inline bool operator < (const Edge&x) const
	{return u^x.u?u<x.u:v<x.v;}
};
struct Edge E[N];
map <Edge,int> id;
int lst[N];
vector <int> Node[N<<2];
int fa[N<<1],dep[N<<1];
stack <int> st1,st2;
int top;
void Update(int k,int l,int r,int s,int t,int e){
	if(s<=l&&r<=t){
		Node[k].push_back(e);
		return;
	}
	int ls(k<<1),rs(k<<1|1),mid(l+r>>1);
	if(s<=mid) Update(ls,l,mid,s,t,e);
	if(mid<t) Update(rs,mid+1,r,s,t,e);
}
int Find(int x){
	if(fa[x]==x) return x;
	return Find(fa[x]);
}
inline void Merge(int x,int y){
	x=Find(x);y=Find(y);
	if(dep[x]>dep[y]) swap(x,y);
	st1.push(x);st2.push(dep[y]);
	fa[x]=y;dep[y]=max(dep[x]+1,dep[y]);
	++top;
}
inline void Delete(){
	int x(st1.top());st1.pop();
	int d(st2.top());st2.pop();
	dep[fa[x]]=d;fa[x]=x;--top;
}
void Solve(int k,int l,int r){
	int lst(top);bool flg(0);
	for(int i(0);i<Node[k].size();++i){
		int e(Node[k][i]),u(E[e].u),v(E[e].v);
		if(Find(u)==Find(v)){flg=1;break;}
		Merge(u,v+n);Merge(u+n,v);
	}
	if(flg) for(int i(l);i<=r;++i) puts("NO");
	else{
		if(l==r) puts("YES");
		else{
			int ls(k<<1),rs(k<<1|1),mid(l+r>>1);
			Solve(ls,l,mid);Solve(rs,mid+1,r);
		}
	}
	while(top>lst) Delete();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i(1);i<=m;++i){
		int u,v;scanf("%d%d",&u,&v);
		if(u>v) swap(u,v);
		int p(id[Edge(u,v)]);
		if(p){
			if(lst[p]){
				Update(1,1,m,lst[p],i-1,p);
				lst[p]=0;
			}
			else lst[p]=i;
		}
		else{
			E[++cnt]=Edge(u,v);
			id[E[cnt]]=cnt;
			lst[cnt]=i;
		}
	}
	for(int i(1);i<=cnt;++i)
		if(lst[i]) Update(1,1,m,lst[i],m,i);
	for(int i(1);i<=(n<<1);++i) fa[i]=i,dep[i]=1;
	Solve(1,1,m);
	return 0;
}
```

---

