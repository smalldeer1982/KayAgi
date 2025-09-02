# Subtree Minimum Query

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. Each vertex has a number written on it; number $ a_{i} $ is written on vertex $ i $ .

Let's denote $ d(i,j) $ as the distance between vertices $ i $ and $ j $ in the tree (that is, the number of edges in the shortest path from $ i $ to $ j $ ). Also let's denote the  $ k $ -blocked subtree of vertex $ x $ as the set of vertices $ y $ such that both these conditions are met:

- $ x $ is an ancestor of $ y $ (every vertex is an ancestor of itself);
- $ d(x,y)<=k $ .

You are given $ m $ queries to the tree. $ i $ -th query is represented by two numbers $ x_{i} $ and $ k_{i} $ , and the answer to this query is the minimum value of $ a_{j} $ among such vertices $ j $ such that $ j $ belongs to $ k_{i} $ -blocked subtree of $ x_{i} $ .

Write a program that would process these queries quickly!

Note that the queries are given in a modified way.

## 样例 #1

### 输入

```
5 2
1 3 2 3 5
2 3
5 1
3 4
4 1
2
1 2
2 3
```

### 输出

```
2
5
```

# 题解

## 作者：kouylan (赞：11)

## 题解 CF893F 【Subtree Minimum Query】

[luogu 题面](https://www.luogu.com.cn/problem/CF893F)

[Codeforces 题面](https://codeforces.com/contest/893/problem/F)

一看到这种深度差不超过 $k$ 的题，十有八九就是按深度建主席树，此题也不例外。

我们把每个点的 dfs 序求出来，在按照深度递增的顺序加到主席树中，查询的时候，只需要查询在 树$(dep_x)$ 到 树$(dep_x+k)$ 中下标在 $[dfn_x,dfn_x+siz_x-1]$ 中点的点权最小值即可。又因为在 $x$ 上方，没有点的深度在 $[dep_x,dep_x+k]$ 之间，所以我们只需要算 树$(dep_x+k)$ 即可，连前缀线段树相减都不需要了。

最后一个小注意点，$dep_x+k$ 有可能大于 $n$，注意判断。

下面是 AC 代码。
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mid (l+r>>1)

const int INF = 0x7f7f7f7f;

int n,r,q,a[100005],ans;
int ee,h[100005],nex[100005<<1],to[100005<<1];
int cnt,dfn[100005],dep[100005],siz[100005];
int p[100005];
int root[100005];
struct hjtree{
	int l,r,mn;
}t[100005<<6];

void addedge(int x,int y)
{
	nex[++ee] = h[x];
	to[ee] = y;
	h[x] = ee;
}

void dfs(int x,int pre)
{
	dep[x] = dep[pre]+1;
	dfn[x] = ++cnt;
	siz[x] = 1;
	for(int i=h[x];i;i=nex[i])
		if(to[i]!=pre)
		{
			dfs(to[i],x);
			siz[x] += siz[to[i]]; 
		}
}

bool cmp(int x,int y)
{
	return dep[x]<dep[y];
}

void build(int &o,int pre,int l,int r,int x,int v)
{
	o = ++cnt;
	t[o] = t[pre];
	if(l==x && r==x)
	{
		t[o].mn = v;
		return;
	}
	if(x<=mid)
		build(t[o].l,t[pre].l,l,mid,x,v);
	else
		build(t[o].r,t[pre].r,mid+1,r,x,v);
	t[o].mn = min(t[t[o].l].mn,t[t[o].r].mn);
}

int query(int o,int l,int r,int ql,int qr)
{
	if(l>=ql && r<=qr)
		return t[o].mn;
	int res=INF;
	if(ql<=mid)
		res = min(res,query(t[o].l,l,mid,ql,qr));
	if(qr>mid)
		res = min(res,query(t[o].r,mid+1,r,ql,qr));
	return res;
}

signed main()
{
	t->mn = INF;
	cin>>n>>r;
	for(int i=1;i<=n;scanf("%lld",a+i),i++);
	for(int i=1,x,y;i<n&&scanf("%lld%lld",&x,&y);i++)
		addedge(x,y), addedge(y,x);
	dfs(r,0);
	for(int i=1;i<=n;i++)
		p[i] = i;
	sort(p+1,p+1+n,cmp);
	cnt = 0;
	for(int i=1;i<=n;i++)
		build(root[dep[p[i]]],root[dep[p[i-1]]],1,n,dfn[p[i]],a[p[i]]);
	cin>>q;
	while(q--)
	{
		int x,k;
		scanf("%lld%lld",&x,&k);
		x = (x+ans)%n+1, k = (k+ans)%n;
		printf("%lld\n",ans=query(root[min(dep[x]+k,dep[p[n]])],1,n,dfn[x],dfn[x]+siz[x]-1));
	}
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：GoldenPotato137 (赞：8)


蒟蒻博客：[QwQ](https://www.cnblogs.com/GoldenPotato/p/9814348.html)

------------

#### 题目大意：给你一颗有根树，点有权值，问你每个节点的子树中距离其不超过k的点的权值的最小值。（边权均为1，强制在线）
------------
## Solution


这题很有意思。

 .

我们一般看到这种距离不超过k的题目，第一反应一般是建以深度为下标，以dfs序为时间轴的的主席树。

如果点权不重复的话，我们可以通过权值主席树+树上二分来解决这个问题。

很不幸，这题点权有重复。

.


所以说，这题妙在思想的转换。

考虑**以dfs序为下标，以深度为时间轴建一颗主席树**。

我们可以bfs，按深度一层层地把点加进去。

这样子，我们就可以查询对应深度之内的这颗子树的最小权值啦。

. 

就酱，我们就可以把这题切掉啦ヽ(￣▽￣)ﾉ



------------

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
long long read()
{
    long long x=0,f=1; char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int N=100000+1000;
const int M=30*N;
int n,r,a[N];
vector <int> e[N];
struct SegmentTree
{
    static const int inf=0x3f3f3f3f;
    #define mid ((now_l+now_r)>>1)
    int MIN[M],son[M][2],cnt;
    inline void update(int now)
    {
        MIN[now]=min(MIN[son[now][0]],MIN[son[now][1]]);    
    }
    void Build(int now,int now_l,int now_r)
    {
        if(now_l==now_r)
        {
            MIN[now]=inf;
            return;    
        }
        Build(son[now][0]=++cnt,now_l,mid);
        Build(son[now][1]=++cnt,mid+1,now_r);
        update(now);
    }
    void Change(int x,int num,int now,int pre,int now_l,int now_r)
    {
        if(now_l==now_r)
        {
            MIN[now]=num;
            return;
        }
        if(x<=mid) son[now][1]=son[pre][1],Change(x,num,son[now][0]=++cnt,son[pre][0],now_l,mid);
        else son[now][0]=son[pre][0],Change(x,num,son[now][1]=++cnt,son[pre][1],mid+1,now_r);
        update(now);
    }
    int Query(int L,int R,int now,int now_l,int now_r)
    {
        if(now_l>=L and now_r<=R)
            return MIN[now];
        int ans=inf;
        if(L<=mid) ans=min(ans,Query(L,R,son[now][0],now_l,mid));
        if(R>mid) ans=min(ans,Query(L,R,son[now][1],mid+1,now_r));
        return ans;
    }
    void Print(int now,int now_l,int now_r)
    {
        cerr<<"no."<<now<<" now_l&r:"<<now_l<<" "<<now_r<<" sonl&r"<<son[now][0]<<" "<<son[now][1]<<" MIN:"<<MIN[now]<<endl;
        if(now_l!=now_r)
        {
            Print(son[now][0],now_l,mid);
            Print(son[now][1],mid+1,now_r);    
        }
    }    
    #undef mid
}sgt;
int dfn[N],depth[N],dfn_to,size[N],depth_MAX;
void dfs(int now)
{
    depth_MAX=max(depth_MAX,depth[now]);
    dfn[now]=++dfn_to;
    size[now]=1;
    for(int i=0;i<int(e[now].size());i++)
        if(dfn[e[now][i]]==0)
        {
            depth[e[now][i]]=depth[now]+1;
            dfs(e[now][i]);
            size[now]+=size[e[now][i]];    
        }
}
int dl[N],front,tail,root[N];
void bfs()
{
    dl[tail++]=r;
    int depth_now=0;
    while(tail>front)
    {
        int now=dl[front];
        int temp=root[depth_now];
        if(depth[now]!=depth_now)
        {
            depth_now=depth[now];
            temp=root[depth_now-1];
        }
        root[depth_now]=++sgt.cnt;
        sgt.Change(dfn[now],a[now],root[depth_now],temp,1,n);
        //sgt.Print(root[depth_now],1,n);
        //cerr<<endl;
        for(int i=0;i<int(e[now].size());i++)
            if(depth[e[now][i]]>depth[now])
                dl[tail++]=e[now][i];
        front++;    
    }
}
int main()
{
    n=read(),r=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    for(int i=1;i<n;i++)
    {
        int s=read(),t=read();
        e[s].push_back(t);
        e[t].push_back(s);
    }
    
    depth[r]=1;
    dfs(r);
    sgt.Build(0,1,n);
    //sgt.Print(0,1,n);
    //cerr<<endl;
    bfs();
    
    int m=read(),lans=0;
    for(int i=1;i<=m;i++)
    {
        int x=read(),K=read();
        x=((x+lans)%n)+1,K=(K+lans)%n;
        int temp=min(depth[x]+K,depth_MAX);
        lans=sgt.Query(dfn[x],dfn[x]+size[x]-1,root[temp],1,n);
        printf("%d\n",lans);    
    }
    return 0;
}
```

---

## 作者：mrsrz (赞：7)

主席树。

设给出的询问为$u,k$，则查询的是$u$子树中，深度在$[dep_x,dep_x+k]$内的节点的最小点权。

按dfs序维护，则每个子树对应着一整段连续的区间。

查询深度$[dep_x,dep_x+k]$可以用主席树的思路，差分成$[1,dep_x+k]$和$[1,dep_x-1]$。

我们考虑建出深度小于等于$p$的节点构成的主席树$d_p$，保存每个节点的权值，维护区间最小值。

那么对于$[1,dep_x+k]$这一段，直接在下标为$dep_x+k$的线段树树上区间查询这一整棵子树即可。

而由于子树$x$中没有节点的深度小于$dep_x$，所以上面查询的时候，$[1,dep_x-1]$这段区间其实本身就没有。

所以只需要对线段树可持久化一下，然后区间查询即可。

时间复杂度$O(m\log n)$。

注意$dep_x+k$可能会大于整棵树的最大深度。

## Code：
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#define N 100005
class istream{
    char buf[21000003],*s;
    public:
        inline istream(){
            buf[fread(s=buf,1,21000001,stdin)]='\n';
            fclose(stdin);
        }
        template<typename T>
        inline istream&operator>>(T&rhs){
            for(rhs=0;!isdigit(*s);++s);
            while(isdigit(*s))rhs=rhs*10+(*s++&15);
            return*this;
        }
}cin;
struct ostream{
    char buf[12000005],*s;
    inline ostream(){s=buf;}
    inline void operator<<(int d){
        if(!d){
            *s++='0';
        }else{
            static int w;
            for(w=1;w<=d;w*=10);
            for(;w/=10;d%=w)*s++=d/w^'0';
        }
        *s++='\n';
    }
    inline~ostream(){fwrite(buf,1,s-buf,stdout);}
}cout;
struct edge{
	int to,nxt;
}e[N<<1];
struct Nodes{
	int ls,rs,mn;
}d[N*333];
int n,m,ans,rt[N],c[N],dep[N],dfn[N],idx=0,sz[N],head[N],cnt=0,idfn[N],tmp[N],node=0,r;
int ret;
void dfs(int now){
	sz[now]=1,idfn[dfn[now]=++idx]=now;
	for(int i=head[now];i;i=e[i].nxt)
	if(!dep[e[i].to]){
		dep[e[i].to]=dep[now]+1;
		dfs(e[i].to);
		sz[now]+=sz[e[i].to];
	}
}
void add(int&o,int P,int l,int r,int pos){
	d[o=++node]=d[P];
	if(l==r)d[o].mn=c[idfn[pos]];else{
		const int mid=l+r>>1;
		if(pos<=mid)add(d[o].ls,d[P].ls,l,mid,pos);else add(d[o].rs,d[P].rs,mid+1,r,pos);
		d[o].mn=std::min(d[d[o].ls].mn,d[d[o].rs].mn);
	}
}
void query(int o,int l,int r,const int&L,const int&R){
	if(!o)return;
	if(L<=l&&r<=R)ret=std::min(ret,d[o].mn);else{
		const int mid=l+r>>1;
		if(L<=mid)query(d[o].ls,l,mid,L,R);
		if(mid<R)query(d[o].rs,mid+1,r,L,R);
	}
}
int main(){
	d->mn=2e9;
	cin>>n>>r;
	for(int i=1;i<=n;++i)cin>>c[i];
	for(int i=1;i<n;++i){
		int u,v;cin>>u>>v;
		e[++cnt]=(edge){v,head[u]};head[u]=cnt;
		e[++cnt]=(edge){u,head[v]};head[v]=cnt;
	}
	dep[r]=1;
	dfs(r);
	for(int i=1;i<=n;++i)tmp[i]=i;
	std::sort(tmp+1,tmp+n+1,[](const int&a,const int&b){return dep[a]<dep[b];});
	for(int i=1;i<=n;++i)
	add(rt[dep[tmp[i]]],rt[dep[tmp[i-1]]],1,n,dfn[tmp[i]]);
	cin>>m;
	while(m--){
		int u,k;cin>>u>>k;
		u=(u+ans)%n+1,k=(k+ans)%n;
		ret=2e9;
		query(rt[std::min(dep[u]+k,dep[tmp[n]])],1,n,dfn[u],dfn[u]+sz[u]-1);
		ans=ret;
		cout<<ans;
	}
	return 0;
}
```

---

## 作者：tommymio (赞：3)

### 题意

一棵 $n$ 个点的有根树，$m$ 个询问，每次询问给出 $x,k$，求 $x$ 的子树内与 $x$ 距离不超过 $k$ 的点的权值的最小值。

### Solution

拆一拆约束，发现大概是：
$$
\begin{cases}
\mathrm{dfn}_x\leq \mathrm{dfn}_y\leq \mathrm{dfn}_x+\mathrm{size}_x-1
\\
\mathrm{dep}_y\leq \mathrm{dep}_x+k
\end{cases}
$$

以 $\text{dfn}$ 为下标，以深度为时间轴，建主席树。

查询时只需要查询时间 $\mathrm{dep_x}+k$ 的主席树中 $[\mathrm{dfn}_x,\mathrm{dfn}_x+\mathrm{size}_x-1]$ 的最小值即可。

正确性？由于 $<\mathrm{dep}_x$ 的 集合 $S$ 中 不存在元素 $\mathrm{dfn}_y\in[\mathrm{dfn}_x,\mathrm{dfn}_x+\mathrm{size}_x-1]$ 

由于本题求最小值的特殊性，所以时间轴上是无法选取一段区间的，只能选取一段前缀或后缀。这就是不选取下标作为时间轴的原因。因为深度作为下标无法划分所求，而时间轴也无法取出区间。

### Code

```cpp
#include<cstdio>
#include<queue>
int cnt=0,num=0,tot=0;
int DEPTH_MAX;
int a[100005];
int rt[100005],lson[10000005],rson[10000005],mn[10000005];
int dfn[100005],dep[100005],high[100005];
int h[100005],to[200005],ver[200005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void dfs(int x,int fa) {
	dfn[x]=++num; DEPTH_MAX=max(DEPTH_MAX,dep[x]);
	for(register int i=h[x];i;i=ver[i]) {
		int y=to[i]; if(y==fa) continue;
		dep[y]=dep[x]+1; dfs(y,x);
	}
	high[x]=num;
}
inline void assign(int x,int y) {mn[x]=mn[y]; lson[x]=lson[y]; rson[x]=rson[y];}
inline void changeTree(int &p,int lst,int l,int r,int x,int val) {
	if(!p||p==lst) assign(p=++tot,lst); 
	if(mn[p]) mn[p]=min(mn[p],val);
	else mn[p]=val;
	if(l==r) return;
	int mid=l+r>>1;
	if(x<=mid) changeTree(lson[p],lson[lst],l,mid,x,val);
	else changeTree(rson[p],rson[lst],mid+1,r,x,val);
}
//inline void change(int &p,int l,int r,int x,int val) {
//	if(!p) {p=++tot; mn[p]=val;} else {mn[p]=min(mn[p],val);}//exists mn[p]=0
//	if(l==r) return;
//	int mid=l+r>>1;
//	if(x<=mid) change(lson[p],l,mid,x,val);
//	else change(rson[p],mid+1,r,x,val);
//}
inline int ask(int p,int l,int r,int L,int R) {
	if(!p) return 1e9+5;
	if(L<=l&&r<=R) return mn[p];
	int mid=l+r>>1;
	if(R<=mid) return ask(lson[p],l,mid,L,R);
	if(L>mid) return ask(rson[p],mid+1,r,L,R);
	return min(ask(lson[p],l,mid,L,mid),ask(rson[p],mid+1,r,mid+1,R));
}
inline void bfs(int u) {
	std::queue<int> Q;
	Q.push(u); int cur=1;
	while(Q.size()) {
		int x=Q.front(); Q.pop();
		changeTree(rt[dep[x]],rt[dep[x]-1],1,num,dfn[x],a[x]);
		for(register int i=h[x];i;i=ver[i]) {
			int y=to[i]; if(dep[y]<dep[x]) continue;
			Q.push(y);
		}
	}
}
int main() {
	int n=read(),RT=read();
	for(register int i=1;i<=n;++i) a[i]=read();
	for(register int i=1;i<n;++i) {
		int x=read(),y=read();
		add(x,y); add(y,x);
	}
	dep[RT]=1; dfs(RT,-1); bfs(RT);
	int Q=read(),lastans=0;
	while(Q--) {
		int x=(read()+lastans)%n+1,k=(read()+lastans)%n;
		printf("%d\n",lastans=ask(rt[min(DEPTH_MAX,dep[x]+k)],1,num,dfn[x],high[x]));
	}
	return 0;
}

```

---

## 作者：Owen_codeisking (赞：2)

这为什么是主席树？？？

这不是区间线段树+动态开点吗？？？~~其实也差不多~~

我们以 $dfs$ 序为区间，动态开点，再以 $bfs$ 序加入新的点就行了，维护一下最小点权

推荐一道更难的题 [七彩树](https://www.lydsy.com/JudgeOnline/problem.php?id=4771)

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=100000+10;
const int inf=0x3f3f3f3f;
int n,m,rt,maxdep,a[maxn],id[maxn],dep[maxn],st[maxn],ed[maxn],tim;
int head[maxn],to[maxn<<1],nxt[maxn<<1],tot;
int T[maxn],L[maxn*20],R[maxn*20],sum[maxn*20],cnt;

inline int read(){
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}
inline void add(int x,int y){
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}

bool cmp(int a,int b){return dep[a]<dep[b];}

void dfs(int x,int f){
	st[x]=++tim;
	dep[x]=dep[f]+1;
	for(int i=head[x],y;i;i=nxt[i]){
		y=to[i];
		if(y==f) continue;
		dfs(y,x);
	}
	ed[x]=tim;
}

void pushup(int now){
	sum[now]=min(L[now]?sum[L[now]]:inf,R[now]?sum[R[now]]:inf);
}

void update(int pre,int &now,int l,int r,int x,int v){
	now=++cnt;
	L[now]=L[pre];R[now]=R[pre];
	if(l == r){sum[now]=v;return ;}
	int mid=(l+r)>>1;
	if(x <= mid) update(L[pre],L[now],l,mid,x,v);
	else update(R[pre],R[now],mid+1,r,x,v);
	pushup(now);
}

int query(int now,int Le,int Ri,int l,int r){
	if(!now) return inf;
	if(Le <= l && r <= Ri){
		return sum[now];
	}
	int mid=(l+r)>>1,ans=inf;
	if(Le <= mid) ans=min(ans,query(L[now],Le,Ri,l,mid));
	if(Ri > mid) ans=min(ans,query(R[now],Le,Ri,mid+1,r));
	return ans;
}

int main()
{
	n=read(),rt=read();
	for(int i=1;i<=n;i++) a[i]=read();
	int opt,x,y,k,lastans=0;
	for(int i=1;i<n;i++){
		x=read(),y=read();
		add(x,y);add(y,x);
	}
	dfs(rt,0);
	for(int i=1;i<=n;i++) id[i]=i;
	sort(id+1,id+n+1,cmp);
	maxdep=dep[id[n]];
	for(int i=1;i<=n;i++){
		if(!T[dep[id[i]]]) T[dep[id[i]]]=T[dep[id[i]]-1];
		update(T[dep[id[i]]],T[dep[id[i]]],1,n,st[id[i]],a[id[i]]);
	}
	m=read();
	for(int i=1;i<=m;i++){
		x=(read()+lastans)%n+1,k=(read()+lastans)%n;
		printf("%d\n",lastans=query(T[min(dep[x]+k,maxdep)],st[x],ed[x],1,n));
	}
	return 0;
}
```

---

## 作者：DPair (赞：1)

提供一种类似分散层叠优化区域树的做法。

~~纯属口胡，但个人感觉挺靠谱的，要是有问题欢迎来 D 我~~

## 思路


看到 “子树” ，看到 “深度距离” 首先考虑把 dfs 序拉下来，然后把每一个点深度拉下来。

那么不难发现问题变成了强制在线询问某一个矩形内的最小值。

一种做法是主席树，这里不用主席树，改用一种更为暴力的做法——树套树。

但是一般的树套树是 $O(n\log^2 n)$ 的， $m=10^6$ 的情况下可能会松不过去。

不难发现，一般的树套树结构中，我们都是在多棵内层树当中把结果查询出来之后合并，但是由于内层树也是线段树故要多乘一只 $\log$ 。

但是我们这里做的是 $\text{RMQ}$ 问题，用线段树处理就显得有些不太优秀。

我们考虑把内层结构改成 **st表** ，对于每一个节点储存这段区间内所有节点排序后的结果，然后建 st 表。

但是这样每一次询问还要二分，复杂度并没有得到优化。

不难发现我们在线段树上的每一个父亲节点上都可以存储当前节点在儿子中的后继，那么我们直接在根节点上二分一次，后面的节点就都可以 $O(1)$ 查询了。

复杂度 $O(n\log^2n+m\log n)$ ，用四毛子处理 $\text{RMQ}$ 问题也许可以做到 $O(n\log n + m\log n)$ ，但没必要。

---

## 作者：Erusel (赞：1)

因为在子树内部，所以不能使用 $\text{BFS}$ 序进行维护

我们考虑用 $\text{DFS}$ 序维护这段区间

有一个非常显然的思路就是把深度差分，由于在子树中没有比根节点更深的点，所以我们只需要维护 $dep \in [1,dep[u]+k]$ 这段区间

我们考虑用主席树，每次 $\text{BFS}$ 加入新的点，维护所有深度小于等于 $dep$ 的点即可

时间复杂度只有一只 $\text{log}$

(看完英文版题面脑子抽了，本身想用 $\text{BFS}$ 序维护


---

## 作者：23forever (赞：1)

首先，题意已经很清楚了，就不讲了。

这题要求强制在线，不然dsu on tree就完事儿了。

考虑如果只有关于根节点的询问，可以想到维护一棵关于深度的线段树。

此时，树上的问题和序列上的问题就是等价的了。

我们将对根节点维护线段树的做法，拓展到整棵树上。不难想到对于一个根节点$u$的数据结构，${\forall v, v \in \text{son[u]}} $都会对它产生影响。所以我们可以用一种可合并的数据结构维护这棵树。显然，动态开点线段树和dfs序+主席树都是OK的。

我只写了一下动态开点线段树的方法，维护关于每个点的线段树，然后大力合并即可。

```cpp
#include <bits/stdc++.h>
#define lson s[p].ls
#define rson s[p].rs
#define pb push_back
const int MAXN = 1e5;
const int INF = 0x3f3f3f3f;
using namespace std;

int rt[MAXN + 5];

struct SegmentTree {
  struct Node {
    int ls, rs, mn;
  } s[MAXN * 50 + 5];
  int tot;
  SegmentTree() {}
  void upd(int p) {
    int lm = lson ? s[lson].mn : INF, rm = rson ? s[rson].mn : INF;
    s[p].mn = min(lm, rm);
  }
  void insert(int &p, int l, int r, int u, int val) {
    if (!p) p = ++tot;
    if (l == r) {
      s[p].mn = val; return;
    }
    int mid = (l + r) >> 1;
    if (u <= mid) {
      insert(lson, l, mid, u, val);
    } else {
      insert(rson, mid + 1, r, u, val);
    }
    upd(p);
  }
  int query(int p, int l, int r, int x, int y) {
    if (!p) return INF;
    if (x <= l && y >= r) return s[p].mn;
    int mid = (l + r) >> 1, ret = INF;
    if (x <= mid) ret = query(lson, l, mid, x, y);
    if (y > mid) ret = min(ret, query(rson, mid + 1, r, x, y));
    return ret;
  }
  int merge(int x, int y) {
    if (!x || !y) return x + y;
    int p = ++tot; s[p].mn = min(s[x].mn, s[y].mn);
    lson = merge(s[x].ls, s[y].ls);
    rson = merge(s[x].rs, s[y].rs);
    return p; 
  }
} Sgt;

int n, a[MAXN + 5], depth[MAXN + 5], tree_rt;

namespace tree {
vector < int > adj[MAXN + 5];

void addEdge(int u, int v) {
  adj[u].pb(v), adj[v].pb(u);
}
void dfs(int u, int fa) {
  Sgt.insert(rt[u], 1, n, depth[u], a[u]);
  for (int v: adj[u]) {
    if (v == fa) continue; 
    depth[v] = depth[u] + 1, dfs(v, u);
    rt[u] = Sgt.merge(rt[u], rt[v]);
  }
}
}

void init() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> tree_rt;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    tree::addEdge(u, v);
  }
  depth[tree_rt] = 1, tree::dfs(tree_rt, 0);
}

int last_ans, m;

int main() {
#ifdef forever23
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif
  init();

  cin >> m; 
  while (m--) {
    int u, k; cin >> u >> k;
    u = (u + last_ans) % n + 1, k = (k + last_ans) % n;
    last_ans = Sgt.query(rt[u], 1, n, depth[u], min(depth[u] + k, n));
    cout << last_ans << endl;
  }
  return 0;
}
```

---

## 作者：zhengrunzhe (赞：1)

由于我比较菜 我懒得写主席树合并 我就写了个树套树

由于最小值不具有可减性 单纯主席树肯定是不行的 除非合并等操作

然后我就写了个线段树套FhqTreap

线段树维护区间[dfn[x],end[x]] (end[x]是x的子树的dfn的结尾)

内部套平衡树 每个点按照key排序 维护val的最小值 这里用深度dep当作key  点权当作val

fhqtreap分离区间[dep[x],dep[x]+k]然后获取答案

```cpp
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using std::min;
const int N=1e5+10,INF=1e9+10;
int n,r,m,w[N],lastans;
int head[N],cnt,to[N<<1],next[N<<1];
inline const void link(int u,int v)
{
	next[++cnt]=head[v];to[head[v]=cnt]=u;
	next[++cnt]=head[u];to[head[u]=cnt]=v;
}
int dep[N],dot[N],dfn[N],end[N],dfc;
inline const void dfs(int p,int fa)
{
	dot[dfn[p]=++dfc]=p;
	for (int son,i=head[p];i;i=next[i])
		if ((son=to[i])^fa)
			dep[son]=dep[p]+1,dfs(son,p);
	end[p]=dfc;
}
namespace Fhq_Treap
{
	struct tree
	{
		int mn,val,key,priority;
		tree *lson,*rson;
		inline const void pushup()
		{
			mn=min(val,min(lson->mn,rson->mn));
		}
	}memory_pool[N*25],*tail,*null;
	inline const void init()
	{
		tail=memory_pool;
		null=tail++;
		null->val=null->mn=INF;
		null->key=null->priority=0;
		null->lson=null->rson=null;
	}
	inline tree *spawn(int key,int val)
	{
		tree *p=tail++;
		p->key=key;
		p->mn=p->val=val;
		p->priority=rand();
		p->lson=p->rson=null;
		return p;
	}
	inline const void split(tree *p,int x,tree *&a,tree *&b)
	{
		if (p==null)return (void)(a=b=null);
		if (p->key<=x)a=p,split(p->rson,x,a->rson,b);
		else b=p,split(p->lson,x,a,b->lson);
		p->pushup();
	}
	inline tree *merge(tree *a,tree *b)
	{
		if (a==null&&b==null)return null;
		if (a==null)return b;
		if (b==null)return a;
		if (a->priority<b->priority)return a->rson=merge(a->rson,b),a->pushup(),a;
		return b->lson=merge(a,b->lson),b->pushup(),b;
	}
	inline const void insert(tree *&root,int key,int val)
	{
		tree *a,*b;
		split(root,key,a,b);
		root=merge(a,merge(spawn(key,val),b));
	}
	inline const int query(tree *&root,int l,int r)
	{
		tree *a,*b,*c;
		split(root,r,a,b);
		split(a,l-1,c,a);
		int mn=a->mn;
		root=merge(c,merge(a,b));
		return mn;
	}
}using namespace Fhq_Treap;
class Segment_Tree
{
	private:
		struct tree
		{
			Fhq_Treap::tree *root;
			tree *lson,*rson;
			inline const int query(int l,int r,int l1,int r1,int l2,int r2)
			{
				if (l>r1||r<l1)return INF;
				if (l>=l1&&r<=r1)return Fhq_Treap::query(root,l2,r2);
				int mid=l+r>>1;
				return min(lson->query(l,mid,l1,r1,l2,r2),rson->query(mid+1,r,l1,r1,l2,r2));
			}
		}*root,memory_pool[N<<2],*tail;
		inline const void build(tree *&p,int l,int r)
		{
			p=tail++;p->root=null;
			for (int i=l;i<=r;i++)insert(p->root,dep[dot[i]],w[dot[i]]);
			if (l==r)return;
			int mid=l+r>>1;
			build(p->lson,l,mid);
			build(p->rson,mid+1,r);
		}
	public:
		inline Segment_Tree(){tail=memory_pool;}
		inline const void build(){build(root,1,n);}
		inline const int query(int l1,int r1,int l2,int r2){return root->query(1,n,l1,r1,l2,r2);}
}sgt;

int main()
{
	scanf("%d%d",&n,&r);
	for (int i=1;i<=n;i++)scanf("%d",&w[i]);
	for (int a,b,i=1;i<n;i++)scanf("%d%d",&a,&b),link(a,b);
	dfs(r,0);scanf("%d",&m);
	init();sgt.build();
	for (int x,k;m--;)
		scanf("%d%d",&x,&k),
		x=(x+lastans)%n+1,k=(k+lastans)%n,
		printf("%d\n",lastans=sgt.query(dfn[x],end[x],dep[x],dep[x]+k));
	return 0;
}
```

---

## 作者：Aleph1022 (赞：1)

本文同步发表于我的博客：https://www.alpha1022.me/articles/cf-893f.htm

炒鸡大水题，套路得要死（

看到「子树」，就有线段树合并和 DFS 序——考虑到维护的最小值没有区间减法，使用线段树合并。  
强制在线，可持久化一下就好了。

代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5;
int n,m,r;
int a[N + 5];
int to[(N << 1) + 5],pre[(N << 1) + 5],first[N + 5];
int lastans;
inline void add(int u,int v)
{
    static int tot = 0;
    to[++tot] = v,pre[tot] = first[u],first[u] = tot;
}
struct node
{
    int min;
    int ls,rs;
} seg[(N << 7) + 10];
int rt[N + 5];
int seg_tot;
void insert(int x,int k,int &p,int tl,int tr)
{
    if(!p)
        p = ++seg_tot,seg[p].min = 0x3f3f3f3f;
    seg[p].min = min(seg[p].min,k);
    if(tl == tr)
        return ;
    int mid = tl + tr >> 1;
    x <= mid ? insert(x,k,seg[p].ls,tl,mid) : insert(x,k,seg[p].rs,mid + 1,tr);
}
int query(int l,int r,int p,int tl,int tr)
{
    if(!p || (l <= tl && tr <= r))
        return seg[p].min;
    int mid = tl + tr >> 1;
    int ret = 0x3f3f3f3f;
    if(l <= mid)
        ret = min(ret,query(l,r,seg[p].ls,tl,mid));
    if(r > mid)
        ret = min(ret,query(l,r,seg[p].rs,mid + 1,tr));
    return ret;
}
int merge(int x,int y)
{
    if(!x || !y)
        return x | y;
    int p = ++seg_tot;
    seg[p].min = min(seg[x].min,seg[y].min);
    seg[p].ls = merge(seg[x].ls,seg[y].ls),seg[p].rs = merge(seg[x].rs,seg[y].rs);
    return p;
}
int fa[N + 5],dep[N + 5];
void dfs(int p)
{
    insert(dep[p],a[p],rt[p],1,n);
    for(register int i = first[p];i;i = pre[i])
        if(to[i] ^ fa[p])
            fa[to[i]] = p,dep[to[i]] = dep[p] + 1,dfs(to[i]),rt[p] = merge(rt[p],rt[to[i]]);
}
int main()
{
    seg[0].min = 0x3f3f3f3f;
    scanf("%d%d",&n,&r);
    for(register int i = 1;i <= n;++i)
        scanf("%d",a + i);
    int u,v;
    for(register int i = 1;i < n;++i)
        scanf("%d%d",&u,&v),add(u,v),add(v,u);
    dep[r] = 1,dfs(r);
    scanf("%d",&m);
    int x,k;
    while(m--)
    {
        scanf("%d%d",&x,&k);
        x = (x + lastans) % n + 1,k = (k + lastans) % n;
        printf("%d\n",lastans = query(dep[x],min(dep[x] + k,n),rt[x],1,n));
    }
}
```

---

