# Peaks

## 题目描述

在 Bytemountains 有 $n$ 座山峰，每座山峰有他的高度 $h_i$。有些山峰之间有双向道路相连，共 $m$ 条路径，每条路径有一个困难值，这个值越大表示越难走。  

现在有 $q$ 组询问，每组询问询问从点 $v$ 开始只经过困难值小于等于 $x$ 的路径所能到达的山峰中第 $k$ 高的山峰，如果无解输出 $-1$。

## 说明/提示

### 数据规模与约定
对于 $100\%$ 的数据，$n \le 10^5$，$0 \le m,q \le 5\times 10^5$，$h_i,c,x \le 10^9$。

## 样例 #1

### 输入

```
10 11 4
1 2 3 4 5 6 7 8 9 10
1 4 4
2 5 3
9 8 2
7 8 10
7 1 4
6 7 1
6 4 8
2 1 5
10 8 10
3 4 7
3 4 6
1 5 2
1 5 6
1 5 8
8 9 2```

### 输出

```
6
1
-1
8
```

# 题解

## 作者：bztMinamoto (赞：46)

更好的阅读体验->[这里](https://www.cnblogs.com/bztMinamoto/p/9680934.html)

据说离线做法是主席树上树+启发式合并（然而我并不会）

据说bzoj上有强制在线版本只能用克鲁斯卡尔重构树，那就好好讲一下好了

这里先感谢LadyLex大佬的博客->[这里](https://www.cnblogs.com/LadyLex/p/7275821.html)

克鲁斯卡尔重构树可以用来解决一类诸如“查询从某个点出发经过边权不超过val的边所能到达的节点”的问题

首先不难发现，上面这个问题肯定是在最小生成树上走最优，其他边都可以不用去管

那么我们就在建最小生成树的时候搞事情

克鲁斯卡尔重构树的思想就是在建最小生成树的时候不是直接连边，而是新建一个节点，并把这个节点的值设为边权，然后令两个连通块的代表点分别作为它的左右儿子。然后令这个新节点成为整个连通块的代表点

说了那么多跟没说一样……举个栗子好了

假设现在有四个节点，要求他们的克鲁斯卡尔重构树

![](https://i.loli.net/2018/09/20/5ba343c58872b.png)

我们按最小生成树的方法找，先把边按权值从小到大排序。

然后设第一条边权值为4，连接1和2这两个连通块

然后新建一个节点5，点权设为4，并把1和2作为他的左右儿子

![](https://i.loli.net/2018/09/20/5ba343c59c335.png)

第二条边权值为6，连接3和4这两个连通块

然后新建一个节点6，点权设为6，并把3和4作为他的左右儿子

![](https://i.loli.net/2018/09/20/5ba343c59c29c.png)

第三条边权值为7，连接1和2，那么我们就是要把4和6的连通块相连了（这两个是连通块的代表点）

然后新建一个节点7，点权设为7，并把5和6作为他的左右儿子

![](https://i.loli.net/2018/09/20/5ba343c5afce7.png)

然后这一棵克鲁斯卡尔重构树就建好了٩(๑>◡<๑)۶

不难发现它有一个性质，每一个儿子节点的权值都小于等于自己的权值（因为我们是按最小生成树的顺序建的）

那么要查“查询从某个点出发经过边权不超过val的边所能到达的节点”

因为我们一个原来图上的点肯定是叶子结点，所以我们只要从叶子结点开始往上找，直到找到最后一个点权小于等于$val$的点

那么这个点为根的子树里的所有点都能到达

怎么找呢？倍增就行了

放到这一题里，因为要查询第$k$大，所以还得套个主席树上树

然而就差不多了
```
//minamoto
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(int x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=2e5+5,M=N*16,K=5e5+5;
struct node{
	int from,to,cost;
	node(){}
	node(int from,int to,int cost):from(from),to(to),cost(cost){}
	inline bool operator <(const node &b)const
	{return cost<b.cost;}
}E[K];
int head[N],Next[N],ver[N],sum[M],L[M],R[M],bin[25],cnt,tot;
int fa[N],f[N][20],ls[N],rs[N],rt[N],val[N],num;
int h[N],limit,b[N],n,q,m,ans=0,dfn;
inline void mission(int u){
	for(int i=1;bin[i]<=n;++i)
	f[u][i]=f[f[u][i-1]][i-1];
}
inline void add(int u,int v){
	ver[++tot]=v,Next[tot]=head[u],head[u]=tot;
}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void update(int last,int &now,int l,int r,int x){
	sum[now=++cnt]=sum[last]+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(x<=mid) R[now]=R[last],update(L[last],L[now],l,mid,x);
	else L[now]=L[last],update(R[last],R[now],mid+1,r,x);
}
int query(int a,int x,int k){
	int l=1,r=limit;
	for(int j=18;~j;--j)
	if(f[a][j]&&val[f[a][j]]<=x) a=f[a][j];
	int v=rt[rs[a]],u=rt[ls[a]-1];
	if(sum[v]-sum[u]<k) return -1;
	while(l<r){
		int tmp=sum[R[v]]-sum[R[u]],mid=(l+r)>>1;
		if(tmp>=k) v=R[v],u=R[u],l=mid+1;
		else v=L[v],u=L[u],r=mid,k-=tmp;
	}
	return b[r];
}
void dfs(int u){
	mission(u),ls[u]=++num;
	if(u<=n) update(rt[num-1],rt[num],1,limit,h[u]);
	else rt[num]=rt[num-1];
	for(int i=head[u];i;i=Next[i]) dfs(ver[i]);
	rs[u]=num;
}
int main(){
//	freopen("testdata.in","r",stdin);
	n=read(),m=read(),q=read();
	bin[0]=1;for(int i=1;i<=22;++i) bin[i]=bin[i-1]<<1;
	for(int i=1;i<=2*n;++i) fa[i]=i;
	for(int i=1;i<=n;++i) b[i]=h[i]=read();
	for(int i=1,u,v,e;i<=m;++i)
	u=read(),v=read(),e=read(),E[i]=node(u,v,e);
	sort(b+1,b+1+n),limit=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;++i) h[i]=lower_bound(b+1,b+1+limit,h[i])-b;
	sort(E+1,E+1+m);dfn=n;
	for(int i=1;i<=m;++i){
		int u=find(E[i].from),v=find(E[i].to);
		if(u!=v){
			val[++dfn]=E[i].cost,fa[u]=fa[v]=dfn;
			add(dfn,u),add(dfn,v),f[u][0]=f[v][0]=dfn;
			if(dfn-n==n-1) break;
		}
	}
	for(int i=1;i<=dfn;++i) if(!ls[i]) dfs(find(i));
	while(q--){
		int v=read(),x=read(),k=read();
		print(query(v,x,k));
	}
	Ot();
	return 0;
}
```

---

## 作者：Soulist (赞：30)

首先用$Kruskal$重构树，这样我们就能很方便的处理比$x$小的限制条件了

然后它询问的是高度中的第$k$大，会自然地想到要用主席树，只是说，要注意一个细节。

不难发现，重构树的某一个非叶节点（边）会管辖某些叶子节点(点)，有趣的是，其管辖的叶子节点构成一个区间，换而言之是连续的（想不出来的可以画一张图$QAQ$）

所以我可以先$Kruskal$重构树，然后做一遍$dfs$，这遍$dfs$的过程中，我们把所有的叶子节点 **"摘"** 下来，形成一个序列，并对每个节点维护其管辖的区间。

然后每次询问就变成了：先在重构树上跳，跳到某个节点$x$后询问$L[x]$到$R[x]$这一段区间内第$k$大的数是谁？—主席树板子

然后注意离散化，以及特判无解的情况。下面是丑陋的代码。

```cpp

#include<bits/stdc++.h>
using namespace std;
int read(){
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9'){
    	if(cc == '-') flus = -flus;
		cc = getchar();
	}
	while(cc >= '0' && cc <= '9')
	    cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 2e5 + 5;
const int M = 5e5 + 5;
const int inf = 999999999;
struct E{
	int to, next;
}e[N * 2];
struct Node{
	int x, y, z;
}q[M], hh[N];
struct Tree{
	int l, r, val;
}t[N * 27];
int h[N], head[N], fa[N], val[N], fath[N][24], L[N], R[N], b[N];
int n, m, Q, cnt, tot, pop, rot[N], ctt;
bool cmp(Node x, Node y){
	return x.z < y.z;
}
void add(int x, int y){
	e[++cnt] = (E){y, head[x]}; head[x] = cnt;
}
void input(){
	n = read(), m = read(), Q = read();
	val[0] = inf;
	for(int i = 1; i <= n; i++) h[i] = read(), hh[i].x = i, hh[i].z = h[i];
	sort(hh + 1, hh + n + 1, cmp);
	for(int i = 1; i <= n; i++) h[hh[i].x] = i;
	for(int i = 1; i <= m; i++)
		q[i].x = read(), q[i].y = read(), q[i].z = read();
	return ;
}
int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void Kruskal()
{
	sort(q + 1, q + m + 1, cmp);
	for(int i = 1; i <= n; i++) fa[i] = i;
	tot = n;
	for(int i = 1; i <= m; i++)
	{
		int u = find(q[i].x), v = find(q[i].y);
		if(u == v) continue;
		val[++tot] = q[i].z, fa[tot] = fa[u] = fa[v] = tot;
		add(tot, u), add(tot, v);
	}
}
void dfs(int x, int fa)
{
	fath[x][0] = fa;
	for(int i = 1; i <= 19; i ++)  
		fath[x][i] = fath[fath[x][i - 1]][i - 1];
	L[x] = pop;
	if(head[x] == 0) { b[++pop] = x; R[x] = pop; return ; }
	for(int i = head[x]; i; i = e[i].next)
		dfs(e[i].to, x);
	R[x] = pop;
}
//主席树 
void build(int &root, int ll, int rr)
{
	root = ++ctt;
	if(ll == rr)  return ;
	int mid = (ll + rr) >> 1;
	build(t[root].l, ll, mid); build(t[root].r, mid + 1, rr);
}
void change(int &root, int node, int ll, int rr, int k)
{
	root = ++ctt; t[root] = t[node];
	if(ll == rr) {  t[root].val ++;  return ; }
	int mid = (ll + rr) >> 1;
	if(mid >= k) change(t[root].l, t[node].l, ll, mid, k);
	else change(t[root].r, t[node].r, mid + 1, rr, k);
	t[root].val = t[t[root].l].val + t[t[root].r].val;
}
int find_tr(int x, int k)
{
	int now = x;
	for(int i = 19; i >= 0; i--)
		if(val[fath[now][i]] <= k) now = fath[now][i];
	return now;
}
int query(int root1, int root2, int k, int l, int r)
{
	int rkid = t[t[root1].r].val - t[t[root2].r].val, mid = (l + r) >> 1;
	if(l == r){
		if(k - (t[root1].val - t[root2].val) == 0) //这里注意特判
        	return l;
		return 0;
	}
	if(rkid >= k) return query(t[root1].r, t[root2].r, k, mid + 1, r);
	else return query(t[root1].l, t[root2].l, k - rkid, l, mid);
}
void solve(){
	Kruskal(), dfs(tot, tot);
	build(rot[0], 1, n);
	for(int i = 1; i <= pop; i++)
		change(rot[i], rot[i - 1], 1, n, h[b[i]]);
	int v, x, k;
	hh[0].z = -1;
	for(int i = 1; i <= Q; i++)
	{
		v = read(), x = read(), k = read();
		int vip = find_tr(v, x);
		int ans = query(rot[R[vip]], rot[L[vip]], k, 1, n);
		printf("%d\n", hh[ans].z);
	}
}
signed main()
{
	input();
	solve();
	return 0;
}

```

---

## 作者：asd369 (赞：24)

感谢[HRLYB](https://www.luogu.org/space/show?uid=126621)的指出

#### [更多内容在我的博客](https://www.cnblogs.com/asd369-blog/p/P4197-Peaks.html)

以惊人的毅力调完了这道题
~~（虽然最后发现是个sb错误）~~

其实这道题还是很裸的……由于有困难值的限制，所以想到$Kruskal$重构树，然后对于询问中不能经过困难值大于$x$的路径，反映在重构树上就是只**在点权小于等于$x$的节点的子树上移动**

样例的重构树大概长这样
~~(图难看忍忍)~~
![](https://cdn.luogu.com.cn/upload/pic/67842.png)
#### （红色括号内是点权，白色的点是$Kruskal$重构树中新加的点）
接着是求第$k$大（显然用主席树啦$qwq$）  

一开始我想直接打个$dfs$序，因为是子树上的问题。但通过上面的图，发现其实**每个点都对应一段区间**，例如$19$对应的区间就是$(0,10]$，于是问题就变得更为简化了。


~~丑陋的代码~~（休想直接复制）：
```cpp
#pragma GCC optimize(3) //手动O3
#include<bits/stdc++.h>

using namespace std;

template <typename T> inline void Read(T &t)
{
    int c=getchar(),f=0;
    for(;c<'0'||c>'9';c=getchar())f=(c=='-');
    for(t=0;c>='0'&&c<='9';c=getchar())t=(t<<3)+(t<<1)+(c^48);
    if(f)t=-t;
}

const int N=2e5+5,M=5e5+5;
int n,m,q,tot,cnt,num,size;
int head[N],b[N],h[N],f[N],diff[N],fa[N][25];
int Rt[N],range[N][2];

struct Edge
{
    int u,v,dif,next;
    void add(int x, int y, int d) {u=x,v=y,dif=d;}
    void _add(int x, int y) {v=y,next=head[x],head[x]=tot;}
    bool operator < (Edge e1) const {return dif<e1.dif;}
}e[M],E[M];

struct HJTtree //主席树（黄嘉泰=Hu Jintao）
{
private:
    int lc[N<<5],rc[N<<5],sum[N<<5];
public:
    void build(int &rt, int l, int r)
    {
        rt=++cnt;
        if(l==r)return;
        int mid=(l+r)>>1;
        build(lc[rt],l,mid);
        build(rc[rt],mid+1,r);
    }
    void modify(int pre, int &rt, int l, int r, int x)
    {   
        rt=++cnt;
        lc[rt]=lc[pre],rc[rt]=rc[pre],sum[rt]=sum[pre]+1;
        if(l==r)return;
        int mid=(l+r)>>1;
        if(x<=mid)modify(lc[pre],lc[rt],l,mid,x);
        else modify(rc[pre],rc[rt],mid+1,r,x);
    }
    int query(int x, int y, int l, int r, int k)
    {
        if(l==r)return l;
        int mid=(l+r)>>1,d=sum[rc[y]]-sum[rc[x]];
        if(k<=d)return query(rc[x],rc[y],mid+1,r,k);
        else return query(lc[x],lc[y],l,mid,k-d);
    }
}t;

void dfs(int x)
{
    for(int i=1;i<=20;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    range[x][0]=num; //对应区间的左端点（左开右闭）
    if(!head[x])
    {
        int kkk=lower_bound(b+1,b+size+1,h[x])-b;
		range[x][0]=++num;
        t.modify(Rt[num-1],Rt[num],1,size,kkk);
        return;
    }
    for(int i=head[x],flag=0;i;i=E[i].next)
        dfs(E[i].v);
    range[x][1]=num;
}

int Find(int x) {return f[x]==x?x:f[x]=Find(f[x]);}

void kruskal()
{
    sort(e+1,e+m+1);
    for(int i=1;i<=n;i++)f[i]=i;
    int temp=n;
    for(int i=1;i<=m;i++)
    {
        int u=Find(e[i].u),v=Find(e[i].v);
        if(u==v)continue;
        diff[++temp]=e[i].dif;
        f[u]=f[v]=f[temp]=temp;
        E[++tot]._add(temp,u),E[++tot]._add(temp,v);
		fa[u][0]=fa[v][0]=temp;
    }
    t.build(Rt[0],1,size);
    dfs(temp);
} 

int main()
{
    Read(n),Read(m),Read(q);
    for(int i=1;i<=n;i++)
        Read(h[i]),b[i]=h[i];
    sort(b+1,b+n+1);
    size=unique(b+1,b+n+1)-b-1; //离散化
    for(int i=1,x,y,d;i<=m;i++)
    {
        Read(x),Read(y),Read(d);
        e[i].add(x,y,d);
    }
    kruskal();
    while(q--)
    {
        int x,d,k;
        Read(x),Read(d),Read(k);
        for(int i=20;i>=0;i--)
            if(fa[x][i]&&diff[fa[x][i]]<=d)x=fa[x][i]; //找到深度最小且点权不大于k的祖先
        if(sum[Rt[range[x][1]]]-sum[Rt[range[x][0]]]<k) {puts("-1");continue;} //如果查询的k大于该区间高度值个数，无解
                       //如果这里写range[x][1]-range[x][0]也是一样的
        printf("%d\n",b[t.query(Rt[range[x][0]],Rt[range[x][1]],1,size,k)]);
    }
    return 0;
}
```

---

## 作者：NaCly_Fish (赞：20)

就当是学习线段树合并的练习题吧。

这一堆询问不太好搞，但是没有修改：所以我们可以离线下来，把所有询问按照 $x$ 从小到大排序。

类似的，把所有边也按困难值从小到大排序。

这样一来，在处理询问的时候，如果要求的路径困难值 $\le x$，就把困难值 $\le x$ 的边都加进来就可以了。

要注意的是，在每次加入边的时候，不用从头开始加，直接从上一次的基础上搞。  
因为此时重构一遍，也要加入上次的那些边。  

对于每个询问，加完边之后直接查询点所在连通块中的第 $k$ 大。

关于加边和查询的方法，就要用到线段树合并。  
可以参考这道题：[
[HNOI2012]永无乡](https://www.luogu.org/problem/P3224)  

最后，此题很坑的一点：  
查询的不是山峰下标，而是高度。

时间复杂度 $\Theta((n+q)\log n)$。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 100003
#define M 2000003
#define reg register
#define mid ((l+r)>>1)
#define ll long long
using namespace std;

inline void read(int &x){
	x = 0;
	char c = getchar();
	while(c<'0'||c>'9') c = getchar();
	while(c>='0'&&c<='9'){
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
}

struct edge{
	int u,v,w;
	inline edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
	inline bool operator < (const edge& ed) const{
		return w < ed.w;
	}
}e[N*5];

struct query{ //记录询问
	int u,x,k,id;
	inline query(int u=0,int x=0,int k=0,int id=0):u(u),x(x),k(k),id(id){}
	inline bool operator < (const query& b) const{
		return x < b.x;
	}
}qy[N*5];

int n,m,q,cnt,len;
int fa[N],rt[N],ans[N*5],h[N],b[N];
int sum[M],ls[M],rs[M],size[N];

inline int find(int x){ 
	while(x!=fa[x]) x = fa[x] = fa[fa[x]];
	return x;
}

void insert(int &u,int l,int r,int pos){ //动态开点线段树的修改
	if(!u) u = ++cnt;
	if(l==r){
		++sum[u];
		return;
	}
	if(pos<=mid) insert(ls[u],l,mid,pos);
	else insert(rs[u],mid+1,r,pos);
	sum[u] = sum[ls[u]]+sum[rs[u]];
} 

int merge(int u,int v,int l,int r){ //合并
	if(!u||!v) return u|v;
	if(l==r){
		sum[u] += sum[v];
		return u;
	}
	ls[u] = merge(ls[u],ls[v],l,mid);
	rs[u] = merge(rs[u],rs[v],mid+1,r);
	sum[u] = sum[ls[u]]+sum[rs[u]];
	return u;
}

int ask(int u,int l,int r,int k){ //直接在线段树上二分找第 k 大
	if(l==r) return l;
	if(sum[rs[u]]>=k) return ask(rs[u],mid+1,r,k);
	return ask(ls[u],l,mid,k-sum[rs[u]]);
}

int main(){
	int u,v,w,x,k,pt = 0;
    read(n),read(m),read(q);
    for(reg int i=1;i<=n;++i){
    	read(h[i]);
		b[i] = h[i];	
		size[i] = 1;
	}
	sort(b+1,b+1+n);
	len = unique(b+1,b+1+n)-b-1; //喜闻乐见的离散化三连
	for(reg int i=1;i<=n;++i){
		x = lower_bound(b+1,b+1+len,h[i])-b;
		insert(rt[i],1,len,x);
	}
    for(reg int i=1;i<=m;++i){
    	read(u),read(v),read(w);
    	e[i] = edge(u,v,w);
	}
	sort(e+1,e+1+m);
	for(reg int i=1;i<=q;++i){
		read(u),read(x),read(k);
		qy[i] = query(u,x,k,i);
	}
	sort(qy+1,qy+1+q);
	for(reg int i=1;i<=n;++i) fa[i] = i;
	for(reg int i=1;i<=q;++i){
		x = qy[i].x;
		while(e[pt+1].w<=x&&pt<m){ //pt 表示指针,把困难度 <=x 的边都加入
			++pt;
			u = e[pt].u,v = e[pt].v;
			u = find(u),v = find(v);
			if(u==v) continue;
			fa[v] = u;
			size[u] += size[v];
			rt[u] = merge(rt[u],rt[v],1,len);
		}
		u = qy[i].u,k = qy[i].k;
		if(size[find(u)]<k) ans[qy[i].id] = -1; //注意判无解
		else ans[qy[i].id] = b[ask(rt[find(u)],1,len,k)];
	}
	for(reg int i=1;i<=q;++i) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：L______ (赞：16)

怎么都是kruscal重构树啊。不会啊，还是太菜了，考到这道题的时候试了一下并查集+vector维护，发现其实洛谷上可以跑，洛谷数据甚至裸跑比我自己打的线段树合并还快（~~可能还是因为我太菜了~~）。后面发现打的vector合并还不是很优秀，尝试了一下上次听大佬wqy @[wucstdio](https://www.luogu.org/space/show?uid=54214) 讲的根号平衡（~~好像是这个东西~~）进行了时间上的玄学优化，目前待在最优解的前面。

这个时间复杂度是怎么个卡法呢，对于vector合并的时候，我最开始的想法是将个数少的集合中的每一个元素二分查找位置然后用vectoer中的insert函数插入，这样时间复杂度对于每一个元素大约是O($\sqrt{y}\times{log_{2}y}$),总的时间复杂度就是O($x\times{\sqrt{y}\times{log_{2}y}}$)其中y是被插入的集合中的元素个数，x是需要插入到y集合中的集合的元素个数。这样在插入元素个数较小的时候是比较优秀了，但是当元素个数多了的时候很慢,怎么办呢。我们发现，vector有一个更优秀的插入函数push_back可以实现将元素插入在末尾时间复杂度大概是O(2)可以看做O(1)，我们之所以要用二分查找和insert插入是为了维护vector中的有序性。那么在元素个数很多的时候其实可以先将元素全部插入在末尾再进行排序操作,可以做到时间复杂度是O（$x+(x+y)\times{log_2(x+y)}$）


那么我们考虑当上面两个的时间复杂度相等时，

$x\times{\sqrt{y}\times{log_{2}y}}=x+(x+y)\times{log_2(x+y)}$

我们可以假装里面一些同等级的值是相同的，化简后大约就可以看做$x=\sqrt{y}$（其实可以化成更有道理的分界条件，只是因为我太懒了……）

于是我们每次合并时保证$x<y$，当$x<\sqrt{y}$是我们就使用第一种方式合并，否则就进行第二种合并方式。这样可以大概可以将每次合并的时间复杂度限制在$(x+y)\times{log_2{(x+y)}}$下。

目前跑的最快的那篇717ms的代码实际上是有问题的，我是每次需要查找答案时再排序，然后标记，如果集合没变过之后就不用排序了，但是这样时间复杂度极度不稳定，洛谷数据跑的很快，其他地方数据可以卡死。

而对于后面两个796ms的代码就是我使用的~~根号平衡~~（**我确实是不清楚这样说是否准确，我在这里的方法大概就是调整时间复杂度**），但是前面那份代码也是有一点问题，我在交换fx和fy时没有交换sizex和sizey，所以实际上在交换后根本没有判断到分界条件，所以也是假的。（~~逃~~~

后面那份目前没有发现什么问题。（~~一大堆卡常都是基本操作啦~~）

**Code**（~~卡常被我删了~~）

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define ll long long
#define re register
#define N 100010
#define M 500010
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,m,Q,fa[N],h[N],ans[M];
vector<int> v[N];
struct E{
	int from,to,w;
}edge[M];
bool cmp(const E &a,const E &b){
	return a.w<b.w;
}
struct question{
	int id,u,num,val;
}q[M];
bool cmp2(const question &a,const question &b){
	return a.val<b.val;
}

inline int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

int main(){
	n=read(),m=read(),Q=read();
	for(re int i=1;i<=n;i++) h[i]=read(),fa[i]=i,v[i].push_back(h[i]);
	for(re int i=1;i<=m;i++) edge[i].from=read(),edge[i].to=read(),edge[i].w=read();
	sort(edge+1,edge+m+1,cmp);
	for(re int i=1;i<=Q;i++){
		q[i].id=i,q[i].u=read(),q[i].val=read(),q[i].num=read();
	}
	sort(q+1,q+Q+1,cmp2);
	int last=0;
	for(re int t=1;t<=Q;t++){
		for(re int i=last+1;i<=m;i++){
			if(edge[i].w<=q[t].val){
				int x=edge[i].from,y=edge[i].to;
				int fx=find(x),fy=find(y);
				if(fx!=fy){
					int sizex=v[fx].size(),sizey=v[fy].size();
					if(sizex>sizey) swap(fx,fy),swap(sizex,sizey);
					fa[fx]=fy;
					if((ll)sizex*sizex<sizey){//调整时间复杂度的玄学分界条件 
						for(re int j=0;j<sizex;j++){
							v[fy].insert(lower_bound(v[fy].begin(),v[fy].end(),v[fx].at(j)),v[fx].at(j));
						}
					}
					else{
						for(int j=0;j<sizex;j++){
							v[fy].push_back(v[fx].at(j));
						}
						sort(v[fy].begin(),v[fy].end());
					}
				}
				last=i;
			}
			else break;
		}
		int x=find(q[t].u);
		if(v[x].size()<q[t].num) ans[q[t].id]=-1;
		else ans[q[t].id]=v[x].at(v[x].size()-q[t].num);
	}
	for(re int i=1;i<=Q;i++) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：GKxx (赞：6)

一句话题解：kruskal重构树的dfs序建立主席树就好了。

按照困难值从小到大把kruskal重构树建出来，那么从一个点x出发只走困难值小于等于x的路径能到达的所有点就是重构树上的一棵包含x的子树，我们可以用树上倍增找到这个子树的根，那么问题变成了询问子树里的所有叶节点中的k大值

注意到一棵子树的dfs序连续，所以可以把dfs序求出来 问题转化为区间k大值，建立主席树即可。

主席树懒得离散化 反正都动态开点了

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}
#if __cplusplus >= 201103L
template <typename T, typename... Args>
inline void read(T& t, Args&... args) {
    read(t); read(args...);
}
#else
template <typename T1, typename T2>
inline void read(T1& t1, T2& t2) { read(t1); read(t2); }
template <typename T1, typename T2, typename T3>
inline void read(T1& t1, T2& t2, T3& t3) { read(t1, t2); read(t3); }
template <typename T1, typename T2, typename T3, typename T4>
inline void read(T1& t1, T2& t2, T3& t3, T4& t4) { read(t1, t2, t3); read(t4); }
template <typename T1, typename T2, typename T3, typename T4, typename T5>
inline void read(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5) { read(t1, t2, t3, t4); read(t5); }
#endif	// C++11

#ifdef WIN32
#define LLIO "%I64d"
#else
#define LLIO "%lld"
#endif	// WIN32 long long
#define rep(I, A, B) for (int I = (A); I <= (B); ++I)
#define rrep(I, A, B) for (int I = (A); I >= (B); --I)
#define erep(I, X) for (int I = head[X]; I; I = next[I])

const int maxn = 1e5 + 207;
const int maxm = 5e5 + 207;
const int moren = maxn << 1;
struct Edge {
    int x, y, w;
    Edge(int f, int t, int ww = 0)
        : x(f), y(t), w(ww) {}
    Edge() : x(0), y(0), w(0) {}
};
inline bool operator<(const Edge& lhs, const Edge& rhs) {
    return lhs.w < rhs.w;
}
Edge e[maxm];
int height[maxn];
int v[moren], head[moren], next[moren], value[moren], ind[moren], leaf[moren];
int anc[moren][50], pos[moren], st[moren], ed[moren];
int pa[moren];
int n, m, q, xys, etot, index;

int findf(int x) { return pa[x] == x ? x : (pa[x] = findf(pa[x])); }

inline void ae(int x, int y) { v[++etot] = y; next[etot] = head[x]; head[x] = etot; }

void dfs(int x) {
    pos[++index] = x; st[x] = index;
    for (int i = 1; 1 << i <= (n << 1); ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    erep(i, x) if (v[i] != anc[x][0]) {
        anc[v[i]][0] = x;
        dfs(v[i]);
        leaf[x] += leaf[v[i]];
    }
    if (!leaf[x]) leaf[x] = 1;
    ed[x] = index;
}

int sum[moren << 5], left[moren << 5], right[moren << 5], root[moren], tot;
void insert(int &curr, int l, int r, int pos, int val) {
    left[++tot] = left[curr]; right[tot] = right[curr];
    sum[tot] = sum[curr] + val; curr = tot;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) insert(left[curr], l, mid, pos, val);
    else insert(right[curr], mid + 1, r, pos, val);
}
int queryKth(int lt, int rt, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int s = sum[right[rt]] - sum[right[lt]];
    if (k <= s) return queryKth(right[lt], right[rt], mid + 1, r, k);
    else return queryKth(left[lt], left[rt], l, mid, k - s);
}

inline int query(int x, int val, int k) {
    rrep(i, 25, 0) if (anc[x][i] && value[anc[x][i]] <= val) x = anc[x][i];
    if (leaf[x] < k) return -1;
    int l = st[x], r = ed[x];
    return queryKth(root[l - 1], root[r], 0, 1e9, k);
}

int main() {
    read(n, m, q);
    rep(i, 1, n) read(height[i]);
    rep(i, 1, m) read(e[i].x, e[i].y, e[i].w);
    std::sort(e + 1, e + m + 1);
    rep(i, 1, (n << 1)) pa[i] = i;
    xys = n;
    rep(i, 1, m) {
        int fx = findf(e[i].x), fy = findf(e[i].y);
        if (fx != fy) {
            value[++xys] = e[i].w;
            pa[fx] = pa[fy] = xys;
            ae(xys, fx); ae(xys, fy); ++ind[fx]; ++ind[fy];
        }
    }
    rep(i, 1, xys) if (!ind[i]) dfs(i);
    rep(i, 1, xys) {
        root[i] = root[i - 1];
        if (pos[i] <= n) insert(root[i], 0, 1e9, height[pos[i]], 1);
    }
    rep(i, 1, q) {
        int x, val, k; read(x, val, k);
        printf("%d\n", query(x, val, k));
    }
    return 0;
}
```

---

## 作者：Tyher (赞：6)

- $Kruskal$重构树
- 倍增
- 主席树

做一遍$Kruskal$重构树

那么点权从深度大的到小的单调不降

从$v$倍增到最后一个小于等于$x$的点

此时这个点的子树就是$v$能到达的满足要求的点的集合

主席树维护子树第$k$大即可.

这样一个码题居然是蓝色的……

---

## 作者：寒鸽儿 (赞：5)

[博客食用效果更佳](https://www.luogu.org/blog/oldherd/solution-p4197)  
刚刚看到这题目还是挺方的，什么思路也没有。  
然而受到[P3224 永无乡](https://www.luogu.org/problemnew/show/P3224)的解法的启发还是想了出来。如果最近在大量刷线段树的同学可能有做过。该题与本题相近，在给定重要度的岛屿之间连边和查询操作交替，查询的是连通块内第k大重要度的岛屿，在那题中用并查集维护连通性，权值线段树维护区间查询。连边的操作通过并查集合并和线段树合并解决。  
回到本题，对照很容易想出离线解法。将询问按照x(路径难度)排序，将边也排序，然后动态地遍历排好序的询问，将小于该询问且当前没有被加入的边加入(除非边的两端已经在一个连通块中)，同时合并线段树，返回区间查询的值。  
下面附上AC代码：  
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100010, maxm = 500010, maxq = 500010;
int a[maxn], rnk[maxn], rnans[maxq], fa[maxn], ans[maxq];


struct edge{
	int u, v, w;
	bool operator < (const edge& o) const { return w < o.w; }
}e[maxm];

struct ask{
	int v, x, k;
}as[maxq];

bool cmp1(int i, int j) {
	return a[i] > a[j];
} 

bool cmp2(int i, int j) {
	return as[i].x < as[j].x;	
}

inline int get(int x) {
	if(fa[x] == x) return x;
	return fa[x] = get(fa[x]);
}

inline void mg(int x, int y) {
	x = get(x); y = get(y);
	fa[y] = x;	
}

struct stree{
	int ls, rs, val;
}t[30*maxm];
int root[maxn], tot = 1;

inline int newnode() {
	t[tot].ls = t[tot].rs = t[tot].val = 0;
	return tot++;
}

inline void insert(int p, int lp, int rp, int pls) {
	if(lp == rp) { t[p].val++; return; }
	int mid = (lp + rp) >> 1;
	if(pls <= mid) {
		if(!t[p].ls) t[p].ls = newnode();
		insert(t[p].ls, lp, mid, pls);
	} else {
		if(!t[p].rs) t[p].rs = newnode();
		insert(t[p].rs, mid+1, rp, pls);
	}
	t[p].val = t[t[p].ls].val + t[t[p].rs].val;
}

inline int merge(int p, int q, int lp, int rp) {
	if(!p || !q) return p|q;
	if(lp == rp) { t[p].val += t[q].val; return p; }
	int mid = (lp + rp) >> 1;
	t[p].ls = merge(t[p].ls, t[q].ls, lp, mid);
	t[p].rs = merge(t[p].rs, t[q].rs, mid+1, rp);
	t[p].val = t[t[p].ls].val + t[t[p].rs].val;
	return p;
}

inline int query(int p, int lp, int rp, int k) {
    if(lp == rp) return lp;
    int mid = (lp + rp) >> 1;
    if(t[t[p].ls].val >= k) return query(t[p].ls, lp, mid, k);
    else return query(t[p].rs, mid+1, rp, k-t[t[p].ls].val);
}

int main() {
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= n; i++) scanf("%d", a+i), rnk[i] = fa[i] = i;
	sort(rnk+1, rnk+n+1, cmp1);
	for(int i = 1; i <= m; i++) scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
	sort(e+1, e+m+1);
	for(int i = 1; i <= q; i++) scanf("%d %d %d", &as[i].v, &as[i].x, &as[i].k), rnans[i] = i;
	sort(rnans+1, rnans+q+1, cmp2);
	int p = 1;
	for(int i = 1; i <= n; i++) {
		root[rnk[i]] = newnode();
		insert(root[rnk[i]], 1, n, i);
	}
	for(int i = 1; i <= q; i++) {
		int v = as[rnans[i]].v, x = as[rnans[i]].x, k = as[rnans[i]].k;
		while(e[p].w <= x && p <= m) {
			if(get(e[p].u) == get(e[p].v)) { p++; continue;}
			root[e[p].u] = root[e[p].v] = merge(root[get(e[p].u)], root[get(e[p].v)], 1, n);
			mg(e[p].u, e[p].v);
			p++;
		}
		v = get(v);
		if(t[root[v]].val < k) ans[rnans[i]] = -1;
		else ans[rnans[i]] = a[rnk[query(root[v], 1, n, k)]];
	}
	for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);
	return 0;
}
```  
欢迎互相关注(然而在oi界蒟蒻的圈很小)。  
最后再次安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)  

---

## 作者：cloud_9 (赞：3)

离线显然就很简单了

把边按权值排序

询问按x排序

写个线段树合并+并查集维护就行了

```cpp
#include <map>
#include <set>
#include <stack>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mxn=1e6+5,inf=1e9;
int n,m,qq,cnt,tot,h[mxn],fa[mxn],hd[mxn],ans[mxn];
int sz[mxn<<5],ls[mxn<<5],rs[mxn<<5],rt[mxn<<5];

inline int read() {
	char c=getchar(); int x=0,f=1;
	while(c>'9'||c<'0') {if(c=='-') f=-1;c=getchar();}
	while(c<='9'&&c>='0') {x=(x<<3)+(x<<1)+(c&15);c=getchar();}
	return x*f;
}
inline void chkmax(int &x,int y) {if(x<y) x=y;}
inline void chkmin(int &x,int y) {if(x>y) x=y;}

struct ed {
	int u,v,w;
	friend bool operator < (ed a,ed b) {
		return a.w<b.w;
	}
}t[mxn<<1];

struct Q {
	int u,x,k,id;
	friend bool operator < (Q a,Q b) {
		return a.x<b.x;
	}
}q[mxn];

int find(int x) {
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int merge(int u,int v,int l,int r) {
	if(!u||!v) return u+v;
	if(l==r) {
		sz[u]+=sz[v];
		return u;
	}
	int mid=(l+r)>>1;
	ls[u]=merge(ls[u],ls[v],l,mid); 
	rs[u]=merge(rs[u],rs[v],mid+1,r);
	sz[u]=sz[ls[u]]+sz[rs[u]];
	return u;
} 

void update(int l,int r,int val,int &p) {
	if(!p) p=++tot;
	if(l==r) {++sz[p]; return ;}
	int mid=(l+r)>>1;
	if(val<=mid) update(l,mid,val,ls[p]);
	else update(mid+1,r,val,rs[p]);
	sz[p]=sz[ls[p]]+sz[rs[p]];
}

int query(int l,int r,int k,int p) {
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(k<=sz[ls[p]]) return query(l,mid,k,ls[p]);
	else return query(mid+1,r,k-sz[ls[p]],rs[p]);
}

void add(int x) {
	int a=find(t[x].u),b=find(t[x].v);
	if(a==b) return ;
	fa[a]=b; rt[b]=merge(rt[b],rt[a],1,inf);
}

int ask(int u,int k) {
	int a=find(u);
	if(sz[rt[a]]<k) return -1;
	return query(1,inf,sz[rt[a]]-k+1,rt[a]);
}

int main()
{
	n=read(); m=read(); qq=read(); 
	for(int i=1;i<=n;++i) fa[i]=i;
	for(int i=1;i<=n;++i) h[i]=read(),update(1,inf,h[i],rt[i]);
	for(int i=1;i<=m;++i) 
		t[i].u=read(),t[i].v=read(),t[i].w=read();
	sort(t+1,t+m+1);
	for(int i=1;i<=qq;++i) 
		q[i].u=read(),q[i].x=read(),q[i].k=read(),q[i].id=i;
	sort(q+1,q+qq+1); int pos=1;
	for(int i=1;i<=qq;++i) {
		while(pos<=m&&t[pos].w<=q[i].x) add(pos),++pos;
		ans[q[i].id]=ask(q[i].u,q[i].k);
	}
	for(int i=1;i<=qq;++i) printf("%d\n",ans[i]);
    return 0;
}

```


---

## 作者：arfa (赞：2)

[$\texttt{cnblogs}$](https://www.cnblogs.com/FibonacciHeap/articles/10501667.html)

$\texttt{Kruskal}$ 重构树 —— 需要一定基础的简单算法

题目大意:

- 给你一个无向图,可能有很多个连通块
- 给定一些询问 $v,x,k$,代表在 $v\{\}$ 这个连通块里面找到一些路径 
$v \Longrightarrow u\{\}$ 的边权 $max\{val\{\}\} \leq x$。求 $u_k$。

首先我们思考,我们要满足最小的边权,那么是整个图的最小生成树的点,而不是 $v \Longrightarrow u$ 的最短路径 (有可能最大值会大,但是总值小)。**因为最小生成树互相连的都是最小的边**。

举个很简单的例子 : 

![](https://i.loli.net/2019/03/09/5c8370dd46e05.png)

$V_3 \Longrightarrow V_4$ 的最短路应该是 $V_3 \Longrightarrow V_4$,距离为 $5$,最大值为 $5$。而最小生成树以后,$V_3 \Longrightarrow V_4$ 的路是 $V_3 \Longrightarrow V_6 \Longrightarrow V_4$,距离为 $6$,最大值为 $4$。

> 然后我们知道,最小生成树了以后就变成了一棵树,然后可以再这上面做文章。如果我们表示一种东西,它的存在满足所有路径通过自己的时候,自己的值为这条道路的最大值,并且满足一定的点在某一个地方,一定的点在另一个地方,每一个点要经过一些必须点来通过。

所以有一种东西叫 $\texttt{Kruskal}$ 重构树。

首先我们先把边排好,然后开始一条一条重构。

假如我们有一个图 :

![](https://i.loli.net/2019/03/09/5c836bd23bdf0.png)

那么我们先按边最小的 $1 \Longrightarrow 2$ 开始。

我们新建一个节点,编号随便,权值为 $val\{1 \Longrightarrow 3\}$,也就是 $2$。

![](https://i.loli.net/2019/03/09/5c836ce951b83.png)

然后是 $2 \Longrightarrow 4$

![](https://i.loli.net/2019/03/09/5c836d223660a.png)

做到 $1 \Longrightarrow 2$ 时候我们发现 $1$ 和 $2$ 各自已经有父亲,或者说各自形成了各自的树,现在是一个森林局面。然后我们把各自的根相连,权值为 $\{1,3\} \Longrightarrow \{2,4\}$,也就是 $1 \Longrightarrow 2$,为 $3$。

![](https://i.loli.net/2019/03/09/5c836e7257cc9.png)

然后最后一条边为 $2 \Longrightarrow 3$,我们发现这两个点已经在同一个树,就不用管它们了。

以上是重构过程,我们来看一下其性质。首先一个非叶子节点 $u$ 代表自己的子树的叶子节点到达 $u$ 的路径的最小权值为 $u$,且其所包含的叶子节点绝对在同一个连通块。其次,这棵树一定是一个二叉堆,二叉是因为每一次是两两结合,最大堆是因为从小到大排序后依次合并。

这时候我们就可以知道,如果我们从 $v$ 这个点一直往上跑,然后找到一个点 $p$,满足 $val_p \leq k$ 且 $val_{father_{p}} > key$ 的时候,这棵树的叶子节点就可以表示所有的 $v$ 能到达的图中的点。

好了,以上暴力。

我们考虑到一个性质,这是一个二叉堆,但不是完全二叉树,所以高度不一定是 $O(\log N)$ 的,有可能会卡到 $O(N)$。(高度会被卡成是 $\frac{N}{2}-1$)

所以我们用到树剖。

我们假设有这样一个重构树,然后按照轻重链剖分搞出来。

![](https://i.loli.net/2019/03/09/5c8371de07fb4.png)

假如我们求从 $4$ 往上找,一直找到 $u$ 满足 $val_u \leq 5$。那么显然 $5$ 是 $7$ 的右二子。 (这两个点我讲得是权值不是编号)

我们到 $4$ 的父亲,然后找这条链的最大值,发现是 $2$ ,继续往上跳,跳到 $3$,这个链的最大值是 $7$,然后我们就二分,找到这个点就好了。

![](https://i.loli.net/2019/03/09/5c8373264207d.png)

最后我们只需要求非叶子节点的子树中的叶子节点的最左边的编号和最右边的编号,求这些点的高度的第 $k$ 大,这个编号为 $\texttt{Dfs}$ 到的顺序。这个图可能有很多个连通块,你的 $dfn$ 一直增加也是没有问题的。

求第 $k$ 大? 划分树。

```pascal
Uses math;

Const
    total=100010 << 1; // 点数
    edge=400010 << 1; // 边数

var
    dsu,num,val,dfn,dep,top,size,recf,father:array[-1..total] of longint;
    tree,toleft:array[-1..21,-1..total] of longint;
    son,element:array[-1..total,-1..2] of longint;
    input:array[-1..edge,-1..3] of longint;
    i,n,m,x,y,k,sa,hop,test,tail,root,dfnum:longint;

function Get(x:longint):longint; // 并查集
begin
    if dsu[x]=x then exit(x) else begin Get:=Get(dsu[x]); dsu[x]:=Get; end;
end;

procedure Sort(l,r:longint); // 排序
var i,j,s:longint;
begin
    i:=l; j:=r; s:=input[(l+r) >> 1,3];
    repeat
        while (input[i,3]<s) do inc(i);
        while (input[j,3]>s) do dec(j);
        if i<=j then
        begin
            input[0]:=input[i]; input[i]:=input[j]; input[j]:=input[0];
            inc(i); dec(j);
        end;
    until i>=j;
    if i<r then Sort(i,r);
    if j>l then Sort(l,j);
end;

procedure Dfs_1(x:longint); // 轻重链剖分
var i:longint;
begin
    size[x]:=1;
    for i:=1 to 2 do
        if (dep[son[x,i]]=0)and(son[x,i]<>0) then
        begin
            dep[son[x,i]]:=dep[x]+1;
            father[son[x,i]]:=x;
            Dfs_1(son[x,i]); inc(size[x],size[son[x,i]]);
            if size[son[x,i]]>size[son[x,0]] then son[x,0]:=son[x,i];
        end;
end;

procedure Dfs_2(x,centre:longint); // 同样是树剖
var i:longint;
begin
    inc(dfnum); dfn[x]:=dfnum; recf[dfnum]:=x; top[x]:=centre; 
    if son[x,0]=0 then
    begin
        inc(tail); val[tail]:=num[x];
        element[x,1]:=tail; element[x,2]:=tail; exit; // element[x,0/1] 是这个点的编号
    end;
    Dfs_2(son[x,0],centre);
    for i:=1 to 2 do if (son[x,i]<>son[x,0]) then Dfs_2(son[x,i],son[x,i]);
    element[x,1]:=min(element[son[x,1],1],element[son[x,2],1]); // 叶子节点最大编号
    element[x,2]:=max(element[son[x,1],2],element[son[x,2],2]); // 叶子节点最小编号,这两个在一起用来指导第 k 大的范围
end;

function Refer(x,key:longint):longint; // 查询 u 点的所在位置
var l,r,mid,tmp:longint;
begin
    x:=father[x];
    while (x<>root) do
    begin
        if num[top[x]]>key then break; // 如果这条链的最大值 > x
        x:=top[x]; 
        if num[father[x]]<=key then x:=father[x] else break; // 如果下一条链有 u (如果下一条链合法)
    end;
    l:=1; r:=dep[x]-dep[top[x]]+1; // 二分,因为一条链的 dfn 在一起
    while l<=r do
    begin
        mid:=(l+r) >> 1; tmp:=recf[dfn[x]-mid+1];
        if num[tmp]<=key then begin l:=mid+1; Refer:=tmp; end else r:=mid-1;
    end;
end;

procedure Build(left,right,deep:longint); // 划分树预警
var i,mid,same,ls,rs,flag:longint;
begin
    if left=right then exit;
    mid:=(left+right) >> 1; same:=mid-left+1;
    for i:=left to right do if tree[deep,i]<val[mid] then dec(same);
    ls:=left; rs:=mid+1;
    for i:=left to right do
    begin
        flag:=0;
        if (tree[deep,i]<val[mid])or((tree[deep,i]=val[mid])and(same>0)) then
        begin
            flag:=1; tree[deep+1,ls]:=tree[deep,i]; inc(ls);
            if tree[deep,i]=val[mid] then dec(same);
        end else begin tree[deep+1,rs]:=tree[deep,i]; inc(rs); end;
        toleft[deep,i]:=toleft[deep,i-1]+flag;
    end;
    Build(left,mid,deep+1); Build(mid+1,right,deep+1);
end;

function Query(left,right,k,l,r,deep:longint):longint;
var mid,x,y,cnt,rx,ry:longint;
begin
    if left=right then exit(tree[deep,left]);
    mid:=(l+r) >> 1;
    x:=toleft[deep,left-1]-toleft[deep,l-1];
    y:=toleft[deep,right]-toleft[deep,l-1];
    ry:=right-l-y; rx:=left-l-x; cnt:=y-x;
    if cnt>=k then Query:=Query(l+x,l+y-1,k,l,mid,deep+1)
    else Query:=Query(mid+rx+1,mid+ry+1,k-cnt,mid+1,r,deep+1);
end;

begin
    read(n,m,test); 
    for i:=1 to n do read(num[i]); 
    for i:=1 to n << 1 do dsu[i]:=i; 
    for i:=1 to m do read(input[i,1],input[i,2],input[i,3]); 
    Sort(1,m); 
    for i:=1 to m do // 建立重构树
    begin
        x:=input[i,1]; y:=input[i,2]; dsu[x]:=get(x); dsu[y]:=get(y);
        if dsu[x]=dsu[y] then continue;
        inc(n); num[n]:=input[i,3]; son[n,1]:=Get(x); son[n,2]:=Get(y);
        dsu[Get(x)]:=dsu[n]; dsu[Get(y)]:=dsu[n];
    end;
    for i:=1 to n do // 做树剖操作
    begin
        if father[i]<>0 then continue; root:=Get(i);
        dep[root]:=1; father[root]:=root; Dfs_1(root); Dfs_2(root,root);
    end;
    for i:=1 to tail do begin tree[0,i]:=val[i]; input[i,3]:=val[i]; end;
    Sort(1,tail); 
    for i:=1 to tail do val[i]:=input[i,3]; 
    Build(1,tail,0);
    for i:=1 to test do
    begin
        read(x,y,k); hop:=Refer(x,y); sa:=element[hop,2]-element[hop,1]+1;
        if sa<k then begin writeln(-1); continue; end;
        writeln(Query(element[hop,1],element[hop,2],sa-k+1,1,tail,0));
    end;
end.
```

时间复杂度为 $O(M \log N)$,查询点 $u$ 每一次用 $2$ 个 $\log$,划分树用 $1$ 个 $\log$。




---

## 作者：Captain_Paul (赞：2)

题意：给定一个无向图，询问从一个点出发只经过不超过指定边权的边能到达的点的第$k$大点权

这道题可以离线也可以在线做

bzoj上有强制在线的加强版

离线做法就是用线段树维护联通块，启发式合并即可。

这里采用在线做法:$Kruskal$重构树

这个算法是NOI2018 D1T1的解法

如果有不会的同学可以自行学习

这道题步骤如下：

先构造$Kruskal$重构树

用倍增找到x在最小生成树上的瓶颈（边权不超过y）

然后查询这个点的子树中的第k小值

然后？就没了orzzzzzz

```
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#define reg register
using namespace std;
const int N=2e5+5,M=5e5+5;
struct E
{
    int from,to,dis;
    inline friend bool operator < (E a,E b) {return a.dis<b.dis;}
}e[M];
struct node
{
    int to,nxt;
}edge[N<<2];
int n,m,T,num,head[N],fa[N],noww,val[N],cnt,L[N],R[N],tim,tot;
int f[N][20],sum[N*30],ls[N*30],rs[N*30],a[N],w[N],t[N],rt[N];
inline int read()
{
    int x=0,w=1;
    char c=getchar();
    while (!isdigit(c)&&c!='-') c=getchar();
    if (c=='-') c=getchar(),w=-1;
    while (isdigit(c))
    {
        x=(x<<1)+(x<<3)+c-'0';
        c=getchar();
    }
    return x*w;
}
inline void add_edge(int from,int to)
{
    edge[++num]=(node){to,head[from]};
    head[from]=num;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline void Kruskal()
{
    for (reg int i=1;i<=n;i++) fa[i]=i;
    for (reg int i=1,tt=0;i<=m;i++)
    {
        int x=find(e[i].from),y=find(e[i].to);
        if (x==y) continue;
        val[++cnt]=e[i].dis;
        add_edge(cnt,x); add_edge(cnt,y);
        fa[x]=fa[y]=fa[cnt]=cnt;
        if (++tt==n-1) break;
    }
}
void dfs(int k,int fh)
{
    L[k]=++tim; a[tim]=k; f[k][0]=fh;
    for (reg int i=1;i<=19;i++) f[k][i]=f[f[k][i-1]][i-1];
    for (reg int i=head[k];i;i=edge[i].nxt)
    {
        int v=edge[i].to;
        if (v!=fh) dfs(v,k);
    }
    R[k]=tim;
}
void insert(int &now,int pre,int l,int r,int x)
{
    now=++tot; sum[now]=sum[pre]+1;
    ls[now]=ls[pre]; rs[now]=rs[pre];
    if (l>=r) return; int mid=(l+r)>>1;
    if (x<=mid) insert(ls[now],ls[now],l,mid,x);
    else insert(rs[now],rs[now],mid+1,r,x);
}
int query(int now,int pre,int l,int r,int x)
{
    if (l>=r) return l;
    int mid=(l+r)>>1,tmp=sum[ls[now]]-sum[ls[pre]];
    if (x<=tmp) return query(ls[now],ls[pre],l,mid,x);
    return query(rs[now],rs[pre],mid+1,r,x-tmp);
}
int main()
{
    cnt=n=read(),m=read(),T=read();
    for (reg int i=1;i<=n;i++) w[i]=t[i]=read();
    for (reg int i=1;i<=m;i++)
      e[i].from=read(),e[i].to=read(),e[i].dis=read();
    sort(t+1,t+n+1); sort(e+1,e+m+1);
    noww=unique(t+1,t+n+1)-t-1;
    for (reg int i=1;i<=n;i++) w[i]=lower_bound(t+1,t+noww+1,w[i])-t;
    Kruskal(); dfs(cnt,cnt);
    for (reg int i=1;i<=cnt;i++)
      if (a[i]<=n) insert(rt[i],rt[i-1],1,noww,w[a[i]]); else rt[i]=rt[i-1];
    while (T--)
    {
        int x=read(),y=read(),k=read(),ans;
        for (reg int i=19;~i;i--) if (val[f[x][i]]<=y) x=f[x][i];
        int res=sum[rt[R[x]]]-sum[rt[L[x]-1]];
        if (res<k) ans=-1;
        else ans=t[query(rt[R[x]],rt[L[x]-1],1,noww,res-k+1)];
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Holy_Push (赞：2)

咕咕了那么多次之后再来看这道题……（之前看题解都是$Kruskal$重构树把我吓到了就放弃了），终于靠自己的能力做出来啦（撒花），顺便作为短时间回归后的第一篇题解来留个纪念。
 
乍一看这道题看起来很麻烦的样子……但一般这种可以离线并且跟第$k$大相关的题目，当然还是选择离线了！

我们将询问按$x$的大小从小到大排序，顺便把边按照困难值$c$也从小到大排序。这样我们每进行一个询问，我们就可以把该询问需要用到的边加进去。然后就是考虑怎么把边加进去了。

实际上把边$E(u,v)$加到图中与将$u$和$v$所在联通块合并是一个道理。所以我们接下来就考虑合并的问题。

首先考虑维护连通性。连通性我们可以很容易想到用并查集，于是菜鸡$hsy$选择略过这一段$Q\omega Q$

然后考虑如何维护第$k$大。由于在同一个联通块内的是可以互相到达的，所以我们实际上可以把这个联通块中的信息存在并查集的根节点中。然后我们需要选择一种可以支持快速合并、快速求第$k$大的结构。

有人会说，这不是平衡树裸题吗$Q\omega Q$，实际上平衡树的合并需要用到启发式合并，多一只$log$，所以我们选择线段树合并。（不会线段树合并、线段树求第$k$大的可以去找一些模板$QwQ$）

有了线段树合并和并查集以及离线操作之后，这道题就变得非常简单啦$QwQ!$

总结一波：

$1.$ 将询问和边按照某一个元素排序。

$2.$ 依次处理询问，处理每一个问题之前，利用线段树合并以及并查集将需要用到的边加入到图中。

$3.$ 利用线段树求第$k$大。

$4.$ 完结！$QwQ$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6;
int n,m,Q,fa[N],rt[N],len,h[N],to[N],ans[N];

struct In
{
	int val,pos;
	bool operator <(const In &x) const {return val<x.val;}
} u[N];

struct Edge
{
	int u,v,h;
	bool operator <(const Edge &x) const {return h<x.h;}
} e[N];

struct Que
{
	int v,x,k,id;
	bool operator <(const Que &p) const {return x<p.x;}
} q[N];

struct node
{
	int lson,rson,sum;
} t[N*10];

void update(int &i,int l,int r,int x)
{
	if (!i) i=++len;t[i].sum++;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (mid>=x) update(t[i].lson,l,mid,x);
		else update(t[i].rson,mid+1,r,x);
}

int getfa(int x)
{
	if (x==fa[x]) return x;
	return fa[x]=getfa(fa[x]);
}

int merge(int r1,int r2)
{
	if (!r1||!r2) return r1|r2;
	t[r1].sum+=t[r2].sum;
	t[r1].lson=merge(t[r1].lson,t[r2].lson);
	t[r1].rson=merge(t[r1].rson,t[r2].rson);
	return r1;
}

int query(int i,int l,int r,int k)
{
	if (l==r) if (t[i].sum<k) return -1;else return to[l];
	int mid=(l+r)>>1;
	if (t[t[i].rson].sum>=k) return query(t[i].rson,mid+1,r,k);
	return query(t[i].lson,l,mid,k-t[t[i].rson].sum);
}

int main()
{
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=n;i++) scanf("%d",&u[i].val),u[i].pos=i;
	sort(u+1,u+n+1);
	for (int i=1;i<=n;i++)
		if (u[i].val==u[i-1].val) h[u[i].pos]=h[u[i-1].pos];
			else h[u[i].pos]=h[u[i-1].pos]+1,to[h[u[i].pos]]=u[i].val;
	for (int i=1;i<=n;i++) fa[i]=i,update(rt[i],1,n,h[i]);
	for (int i=1;i<=m;i++) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].h);
	for (int i=1;i<=Q;i++) scanf("%d%d%d",&q[i].v,&q[i].x,&q[i].k),q[i].id=i;
	sort(q+1,q+Q+1);sort(e+1,e+m+1);
	int now=1;
	for (int i=1;i<=Q;i++)
	{
		while (now<=m&&e[now].h<=q[i].x)
		{
			int u=e[now].u,v=e[now].v,f1=getfa(u),f2=getfa(v);
			if (f1!=f2) fa[f1]=f2,rt[f2]=merge(rt[f2],rt[f1]);
			++now;
		}
		ans[q[i].id]=query(rt[getfa(q[i].v)],1,n,q[i].k);
	}
	for (int i=1;i<=Q;i++) printf("%d\n",ans[i]);
}
```





---

## 作者：撤云 (赞：2)

### $Solution$
首先来介绍一下kruskal重构树:[详见](http://baidu.physton.com/?q=kruskal重构树)  
知道kruskal重构树后这一道题就可以几乎没了.  
利用kruskal重构树的性质,一个节点的左右儿子都比他小(其实就是一个堆),所以从点$v$开始只经过困难值小于等于$x$的路径实际上就是找到一个权值小于等于$x$的且深度最小的点
我们将这个点叫做$K$.那么点$v$可以走的路径就是点$K$的子树.现在要求第k高的山峰,这直接用主席树+dfs序搞一搞就好了
### $Code$

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200011; 
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9') f=(c=='-')?-1:1,c=getchar();
    while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
    return f*x;
}
struct node1 {
	int to,next;
}e[500001];
struct node{
	int x,y,v;
}b[500001];
struct node2 {
	int l,r,v;
}a[N*20];
int root,tot,res,cnt,n,m,t,h[N],pre[N],head[N],T[N];
int fa[N][21],dep[N],bin[101],val[N],r[N],l[N],tail[N];
void add(int x,int y){ e[++cnt].to=y,e[cnt].next=head[x],head[x]=cnt; }
int find(int x){ return pre[x]==x?x:pre[x]=find(pre[x]); }
bool cmp(const node & a , const node & b ){ return a.v<b.v; }
int query(int x,int v){
	for(int i=19;i>=0;i--)
		if(dep[x]>=bin[i]&&val[fa[x][i]]<=v)
			x=fa[x][i];
	return x;
}
void dfs(int x){
	if(x<=n)
		h[++tot]=tail[x];
	l[x]=tot;
	for(int i=1;i<=16;i++)
		if(dep[x]>=bin[i])
			fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=head[x];i;i=e[i].next)
		dep[e[i].to]=dep[x]+1,fa[e[i].to][0]=x,dfs(e[i].to);
	r[x]=tot;
}
void build(){
	res=n,sort(b+1,b+1+m,cmp);
	for(int i=1;i<=m;i++){
		int fx=find(b[i].x),fy=find(b[i].y);
		if(fx!=fy)
			val[++res]=b[i].v,pre[fx]=res,pre[fy]=res,add(res,fx),add(res,fy);
		if(res==n*2-1)
			break;
	}
}
void insert(int &k,int l,int r,int v){
	a[++root]=a[k],k=root,a[k].v++;
	if(l==r) return ;
	int mid=(l+r)>>1;
	if(v<=mid)
		insert(a[k].l,l,mid,v);
	else insert(a[k].r,mid+1,r,v);
}
int answer(int x,int k,int l,int r,int v){
	if(l==r) return l;
	int mid=(l+r)>>1,pos=a[a[k].l].v-a[a[x].l].v;
	if(v<=pos)
		return answer(a[x].l,a[k].l,l,mid,v);
	else return answer(a[x].r,a[k].r,mid+1,r,v-pos);
}
void solve(){
	int last=-1;
	while(t--){
		int v=read(),x=read(),k=read();
		if(last!=-1)
			v^=last,x^=last,k^=last;
		int now=query(v,x);
		(r[now]-l[now]<k)?last=-1:last=tail[answer(T[l[now]],T[r[now]],1,n,r[now]-l[now]-k+1)];
		printf("%d\n",last);
	}
}
int main(){
	n=read(),m=read(),t=read(),bin[0]=1;
	for(int i=1;i<=n;i++)
		tail[i]=read();
	for(int i=1;i<n*2;i++)
		pre[i]=i;
	for(int i=1;i<=19;i++)
		bin[i]=bin[i-1]<<1;
	for(int i=1;i<=m;i++)
		b[i].x=read(),b[i].y=read(),b[i].v=read();
	build(),dfs(find(1));
	sort(tail+1,tail+1+n);
	int k=unique(tail+1,tail+1+n)-tail-1;
	for(int i=1;i<=n;i++)
		T[i]=T[i-1],insert(T[i],1,k,lower_bound(tail+1,tail+1+k,h[i])-tail);
	n=k,solve();
}

```

---

## 作者：Monster_Qi (赞：2)

## 解题思路
　　看见各位大佬都是克鲁斯卡尔重构树，蒟蒻来个线段树合并水一水。。

　　首先这是个离线做法，刚开始把边和询问各用一个结构体存起来，然后边按照边权排序，询问按照$x$进行排序。这样因为边权是有序的，所以解决询问的时候可以把$<=x$的边都加进去。查询第$k$大用权值线段树就好了，刚开始的时候每个点开一个线段树，加边时用并查集维护连通性，如果不连通就把两点所在联通块的根进行线段树合并，时间复杂度$O(nlogn)$。
  
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;
const int N=100005;
const int M=500005;

inline int rd(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) f=ch=='-'?0:1,ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return f?x:-x;  
}

int n,m,Q,F[N],cpy[N],a[N],u,rt[N],tot,ans[M];

struct Edge{
    int x,y,w;  
    friend bool operator<(const Edge A,const Edge B){
        return A.w<B.w; 
    }
}edge[M];

struct Query{
    int x,v,k,id;
    friend bool operator<(const Query A,const Query B){
        return A.x<B.x; 
    }
}q[M];

struct Segment_Tree{
    int ls[N*40],rs[N*40],sum[N*40];
    void build(int &x,int l,int r,int pos){
        x=++tot; sum[x]=1; if(l==r) return;
        int mid=(l+r)>>1; 
        if(pos<=mid) build(ls[x],l,mid,pos);
        else build(rs[x],mid+1,r,pos);
    }
    int merge(int x,int y,int l,int r){
        if(!x || !y) return (x|y); 
        if(l==r) {sum[x]+=sum[y]; return x;}
        int mid=(l+r)>>1;
        ls[x]=merge(ls[x],ls[y],l,mid); 
        rs[x]=merge(rs[x],rs[y],mid+1,r);
        sum[x]=sum[ls[x]]+sum[rs[x]];
        return x;
    }
    int find(int x,int l,int r,int k){
        if(l==r) return l; int mid=(l+r)>>1;
        if(sum[rs[x]]>=k) return find(rs[x],mid+1,r,k);
        else return find(ls[x],l,mid,k-sum[rs[x]]);
    }   
}tree;

int get(int x){
    if(x==F[x]) return x;
    return F[x]=get(F[x]);  
}

int main(){
    n=rd(),m=rd(),Q=rd(); int x,y,z;
    for(int i=1;i<=n;i++) cpy[i]=a[i]=rd(),F[i]=i;
    sort(cpy+1,cpy+1+n); u=unique(cpy+1,cpy+1+n)-cpy-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(cpy+1,cpy+1+u,a[i])-cpy;
    for(int i=1;i<=n;i++) tree.build(rt[i],1,u,a[i]);
    for(int i=1;i<=m;i++){
        x=rd(),y=rd(),z=rd();
        edge[i].x=x,edge[i].y=y,edge[i].w=z;
    }
    sort(edge+1,edge+1+m);
    for(int i=1;i<=Q;i++) {
        x=rd(),y=rd(),z=rd(); q[i].id=i;
        q[i].v=x; q[i].x=y; q[i].k=z;   
    }
    sort(q+1,q+1+Q); int now=1;
    for(int i=1;i<=Q;i++){
        while(now<=m && edge[now].w<=q[i].x) {
            x=edge[now].x; y=edge[now].y; x=get(x); y=get(y);
            now++; if(x==y) continue; F[y]=x;
            rt[x]=tree.merge(rt[x],rt[y],1,u);  
        }
        x=get(q[i].v);
        if(tree.sum[rt[x]]<q[i].k) ans[q[i].id]=-1;
        else ans[q[i].id]=cpy[tree.find(rt[x],1,u,q[i].k)];
    }
    for(int i=1;i<=Q;i++) printf("%d\n",ans[i]);
    return 0;   
}
```
[~~打波广告~~](http://www.cnblogs.com/sdfzsyq)

---

## 作者：lahlah (赞：1)

[luogu P4197 Peaks](https://www.luogu.org/problem/P4197)
# 题目大意很清楚了，就不解释了
第一眼kruskal重构树 + 主席树毒瘤码农题

然后发现貌似可以离线

然后就可以愉快地线段树合并 + 并查集了


具体思路就是

先把所有的边按照边权排序，然后再把询问按照x排序（从小到大)


然后对于每个点维护一个动态开点线段树

询问时 如果当前边边权小于x就把u，v对应的线段树合并一下（用并查集维护连通性）

然后就很愉快了

具体看代码吧

code:
```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
struct A{int u, v, c;} a[N];
int cmp(A x, A y){
	return x.c < y.c;
}
struct Q{int u, x, k, id;} q[N];
int cmp1(Q x, Q y){
	return x.x < y.x;
}
int fa[N];
int get(int x){
	return x == fa[x]? x:(fa[x] = get(fa[x]));
}
int size[N << 5], ch[N << 5][2], tot;
void insert(int &rt, int l, int r, int x){
	if(!rt) rt = ++ tot;
	size[rt] ++;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(x <= mid) insert(ch[rt][0], l, mid, x);
	else insert(ch[rt][1], mid + 1, r, x);
}
int merge(int x, int y){
	if(!x && !y) return 0;
	if(!x) return y;
	if(!y) return x;
	size[x] += size[y];
	ch[x][0] = merge(ch[x][0], ch[y][0]);
	ch[x][1] = merge(ch[x][1], ch[y][1]);
	return x;
}
int find(int rt, int l, int r, int k){
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(size[ch[rt][0]] >= k) return find(ch[rt][0], l, mid, k);
	else return find(ch[rt][1], mid + 1, r, k - size[ch[rt][0]]);
}
int n, m, Q, h[N], b[N], root[N], ANS[N];
int main(){
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= n; i ++) scanf("%d", &h[i]), b[i] = h[i];
	sort(b + 1, b + 1 + n);
	for(int i = 1; i <= n; i ++){
		int pos = lower_bound(b + 1, b + 1 + n, h[i]) - b; //离散化
		insert(root[i], 1, n, pos); fa[i] = i;//对于每个点维护一个动态开点线段树
	}
	for(int i = 1; i <= m; i ++) scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].c);
	for(int i = 1; i <= Q; i ++) scanf("%d%d%d", &q[i].u, &q[i].x, &q[i].k), q[i].id = i;
	sort(a + 1, a + 1 + m, cmp);
	sort(q + 1, q + 1 + Q, cmp1);//把边和边权离线
	int pos = 0;
	for(int i = 1; i <= Q; i ++){
		while(a[pos + 1].c <= q[i].x && pos < m){//把满足条件的边插进去
			int x = get(a[pos + 1].u), y = get(a[pos + 1].v);//找ba ba
			if(x != y){//如果不在同一个连通块
				merge(root[x], root[y]);//线段树合并
				fa[y] = x;
			}
			pos ++;
		}
		int x = get(q[i].u);
		if(size[root[x]] < q[i].k) ANS[q[i].id] = -1;
		else ANS[q[i].id] = b[find(root[x], 1, n, size[root[x]] - q[i].k + 1)];//因为时第k大，所以要变一下
	}
	for(int i = 1; i <= Q; i ++) printf("%d\n", ANS[i]);//输出
	return 0;
}
```
竟然1A，好感动QWQ

~~正常~~

离线是个好东西

---

## 作者：mulberror (赞：1)

# 题目链接
[【洛谷】](https://www.luogu.org/problemnew/show/P4197)   
【BZOJ】没有权限号嘤嘤嘤。题号：3545  
# 题解
窝不会克鲁斯卡尔重构树怎么办？？？  
可以离线乱搞。  
我们将所有的操作全都存下来。  
为了解决小于等于$x$的操作，那么我们按照长度来排一个序。  
如果询问和加边长度相同，这加边优先。  
对于每一个连通块进行权值线段树。   
权值线段树解决$k$大的问题。  
每一次合并，并查集判联通，线段树暴力合并。  
时间复杂度$O(nlogn)$。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IOstream {
	#define gc getchar
	template <typename T>
	inline void read(T &x) {
		x = 0; T fl = 1; char c = 0;
		for (; c < '0' || c > '9'; c = gc())
			if (c == '-') fl = -1;
		for (; c >= '0' && c <= '9'; c = gc())
			x = (x << 1) + (x << 3) + (c ^ 48);
		x *= fl;
	}
	#undef gc
} using namespace IOstream;
int n, m, q;
const int N = 100000 + 5; 
int val[N], id[N];
namespace seg {
	#define ls(x) tr[x].lc
	#define rs(x) tr[x].rc
	struct node {
		int lc, rc, s; node() { lc = rc = s = 0; }
	} tr[N * 50];
	int tot = 0; 
	void upd(int &k, int l, int r, int val) {
		if (!k) k = ++ tot; 
		tr[k].s = 1; 
		if (l == r) return; 
		int mid = (l + r) >> 1;
		if (val <= mid) upd(ls(k), l, mid, val);
		else upd(rs(k), mid + 1, r, val);
	}
	int kth(int k, int l, int r, int rk) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (rk <= tr[ls(k)].s) return kth(ls(k), l, mid, rk);
		else return kth(rs(k), mid + 1, r, rk - tr[ls(k)].s);
	}
	int merge(int x, int y) {
		if (!x || !y) return x + y;
		if (!ls(x) && !rs(x)) { tr[x].s += tr[y].s; return x; }
		ls(x) = merge(ls(x), ls(y));
		rs(x) = merge(rs(x), rs(y)); 
		tr[x].s = tr[ls(x)].s + tr[rs(x)].s; 
		return x; 
	} 
}
struct ASK {
	int a, b, c, d, id;
} Q[N * 10];
int fa[N], rt[N], ans[5 * N];
bool cmp_ASK(ASK A, ASK B) {
	return A.c == B.c ? A.d < B.d : A.c < B.c; 
}
int gf(int x) {
	return x == fa[x] ? fa[x] : fa[x] = gf(fa[x]); 
}
signed main() {
	read(n); read(m); read(q); 
	for (int i = 1; i <= n; i ++) read(val[i]), id[i] = val[i], fa[i] = i; 
	sort(id + 1, id + 1 + n);
	for (int i = 1; i <= n; i ++) 
		val[i] = lower_bound(id + 1, id + 1 + n, val[i]) - id;
	for (int i = 1; i <= m; i ++) 
		read(Q[i].a), read(Q[i].b), read(Q[i].c), Q[i].d = 0;
	for (int i = m + 1; i <= m + q; i ++) 
		read(Q[i].a), read(Q[i].c), read(Q[i].b), Q[i].d = 1, Q[i].id = i - m;
	sort(Q + 1, Q + 1 + m + q, cmp_ASK);
	for (int i = 1; i <= n; i ++) seg::upd(rt[i], 1, n, val[i]);
	for (int i = 1; i <= m + q; i ++) {
		if (!Q[i].d) {
			int x = gf(Q[i].a), y = gf(Q[i].b);
			if (x != y) {
				fa[x] = y; 
				rt[y] = seg::merge(rt[x], rt[y]);
			} 
		} else {
			int x = gf(Q[i].a);
			if (seg::tr[rt[x]].s < Q[i].b) ans[Q[i].id] = -1;
			else ans[Q[i].id] = id[seg::kth(rt[x], 1, n, seg::tr[rt[x]].s - Q[i].b + 1)]; 
		}
	}
	for (int i = 1; i <= q; i ++) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：GoldenPotato137 (赞：1)

[戳我获得更好的阅读体验qwq](https://www.goldenpotato.cn/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/luogu-p4197-peaks/)

---
# Solution
这题的确是可以用库鲁斯卡尔重构树+主席树来搞，~~但是本蒟蒻太菜了并不会~~，因此只能给大家讲讲离线+splay启发式合并的搞法。

首先，我们考虑把询问离线下来并按限制从小到大排序。然后我们可以考虑把边一条一条插入到图里面去，直到某个询问的限制。这样子，问题就变为了询问某一个连通块的K小值，连通块可以合并。

这个问题就肥肠简单了，我们可以用各种各样的数据结构来处理，线段树合并，splay启发式合并都可以。

考虑到每个点期望加入$logn$次，时间复杂度为$O(nlogn)$

---
# Code
**我这题因为TLE调了很久，原因是我在查询的时候没有splay，导致势能分析失效，请各位读者引以为戒**
```cpp
//Luogu P4197 Peaks
//Mar,7th,2019
//splay启发式合并
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long read()
{
	long long x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=100000+100;
const int M=50*N;
struct SPLAY
{
	#define root son[r][1]
	int son[M][2],size[M],cnt[M],fa[M],w[M],to,toUse[M],top;
	inline void update(int x)
	{
		size[x]=size[son[x][0]]+size[son[x][1]]+cnt[x];
	}
	inline void rotate(int x,int type)
	{
		int y=fa[x],z=fa[y];
		fa[x]=z,son[z][y==son[z][1]]=x;
		fa[son[x][type]]=y,son[y][!type]=son[x][type];
		fa[y]=x,son[x][type]=y;
		update(y),update(x);
	}
	void splay(int x,int to)
	{
		while(fa[x]!=to)
		{
			if(fa[fa[x]]!=to and x==son[fa[x]][fa[x]==son[fa[fa[x]]][1]])
				rotate(fa[x],x==son[fa[x]][0]),
				rotate(x,x==son[fa[x]][0]);
			else
				rotate(x,x==son[fa[x]][0]);
		}
	}
	int newNode()
	{
		if(top!=0)
		{
			son[toUse[top]][0]=son[toUse[top]][1]=0;
			size[toUse[top]]=fa[toUse[top]]=cnt[toUse[top]]=w[toUse[top]]=0;
			return toUse[top--];
		}
		return ++to;
	}
	void Insert(int num,int r)
	{
		if(root==0)
		{
			root=newNode(),fa[root]=r;
			w[root]=num,cnt[root]=1;
			update(root);
			return;
		}
		int now=root,last=r;
		while(now!=0)
		{
			if(w[now]==num)
			{
				cnt[now]++,update(now);
				splay(now,r);
				return;
			}
			last=now,now=son[now][num>w[now]];
		}
		now=newNode();
		fa[now]=last,son[last][num>w[last]]=now;
		w[now]=num,cnt[now]=1,update(now);
		splay(now,r);
	}
	int Query(int now,int r,int K)
	{
		if(size[son[now][1]]>=K)
			return Query(son[now][1],r,K);
		K-=(cnt[now]+size[son[now][1]]);
		if(K<=0)
		{
			splay(now,r);
			return w[now]; 
		}
		return Query(son[now][0],r,K);
	}
	void dfs(int now,int r)
	{
		if(now==0) return;
		for(int i=1;i<=cnt[now];i++)//有可能一个点上有多个数字
			Insert(w[now],r);
		dfs(son[now][0],r);
		dfs(son[now][1],r);
		toUse[++top]=now;
	}
	#undef root
}splay;
int fa[N],size[N],root[N];
int FindFather(int x)
{
	if(fa[x]==0) return x;
	return fa[x]=FindFather(fa[x]);
}
void Merge(int x,int y)
{
	if(FindFather(x)==FindFather(y)) return;
	if(size[FindFather(x)]>size[FindFather(y)]) swap(x,y);
	splay.dfs(splay.son[root[FindFather(x)]][1],root[FindFather(y)]);
	//cerr<<x<<" "<<y<<" "<<size[FindFather(x)]<<" "<<size[FindFather(y)]<<" "<<splay.size[splay.son[root[FindFather(y)]][1]]<<endl;
	size[FindFather(y)]+=size[FindFather(x)];
	fa[FindFather(x)]=FindFather(y);
}
struct edge
{
	int s,t,w;
	friend bool operator < (edge x,edge y)
	{
		return x.w<y.w;
	}
}e[M];
struct Query
{
	int x,K,w,ans,no;
	friend bool operator < (Query a,Query b)
	{
		return a.w<b.w;
	}
}query[M];
bool cmp(Query a,Query b)
{
	return a.no<b.no;
}
int Ask(int x,int K)
{
	if(size[FindFather(x)]<K) return -1;
	return splay.Query(splay.son[root[FindFather(x)]][1],root[FindFather(x)],K);
}
int n,m,q,h[N];
int main()
{
	int t=clock();
	freopen("4197.in","r",stdin);
	freopen("4197.out","w",stdout);
	
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++)
		h[i]=read();
	
	for(int i=1;i<=n;i++)
		root[i]=splay.newNode(),size[i]=1;
	for(int i=1;i<=n;i++)
		splay.Insert(h[i],root[i]);
	for(int i=1;i<=m;i++)
		e[i].s=read(),e[i].t=read(),e[i].w=read();
	for(int i=1;i<=q;i++)
		query[i].x=read(),query[i].w=read(),query[i].K=read(),query[i].no=i;
		
	sort(e+1,e+1+m);
	sort(query+1,query+1+q);
	
	int w_to=1;
	for(int i=1;i<=q;i++)
	{
		//cerr<<i<<endl;
		for(;e[w_to].w<=query[i].w and w_to<=m;w_to++)
			Merge(e[w_to].s,e[w_to].t);
		query[i].ans=Ask(query[i].x,query[i].K);
	}
	
	sort(query+1,query+1+q,cmp);
	for(int i=1;i<=q;i++)
		printf("%d\n",query[i].ans);
	cerr<<clock()-t<<endl;
	return 0;
}

```






---

## 作者：浪贱圣 (赞：1)

看各位大佬都是在线做法，我就讲一讲离线做法。

先将询问与边都按权值从小到大排序，对于每个询问，将权值小于询问的边都加进去。就是对于这些边，若它连着的两点不在同一棵平衡树上，则将这两棵平衡树合并。最后查询第K大就行了。

上代码（自己觉得还是写得比较好懂）
```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1000000;
int high[maxn+5],n,fa[maxn],a[maxn][2],num[maxn][2],m,q,root,ans[maxn];
struct d{
	int x,y,value;
}c[maxn*5+5];
struct e{
	int v,x,k,id;
}b[maxn*5+5];
inline int read(){
	int k=0,g=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0'){
		k=k*10+ch-48;
		ch=getchar();
	}
	return k*g;
}
bool cmp_1(d g,d h){
	return g.value<h.value;
}
bool cmp_2(e g,e h){
	return g.x<h.x;
}
void rot(int x){
	int y=fa[x],z=fa[y],l=(x!=a[y][0]),r=l^1;
	if(fa[y]){
		if(a[z][0]==y)a[z][0]=x;
		else a[z][1]=x;
	}
	else root=x;
	fa[x]=z;fa[y]=x;fa[a[x][r]]=y;
	a[y][l]=a[x][r];
	num[y][l]=num[x][r];
	a[x][r]=y;
	num[x][r]=num[y][0]+num[y][1]+1;
}
void splay(int x){
	int y,z;
	while(fa[x]){
		y=fa[x],z=fa[y];
		if(z){
			if(x==a[y][0]^y==a[z][0])rot(x);
			else rot(y);
		}
		rot(x);
	}
}
void insert(int x){
	int p=root,f=0;
	while(p){
		f=p;
		if(high[x]<high[p]){
			++num[p][0];
			p=a[p][0];
		}
		else {
			++num[p][1];
			p=a[p][1];
		}
	}
	fa[x]=f;
	if(!f)return;
	if(high[x]<high[f])a[f][0]=x;
	else a[f][1]=x;
	splay(x);
}
int ask(int now,int k){
	if(!now)return -1;
	if(num[now][1]+num[now][0]+1<k)return -1;
	if(num[now][1]+1==k)return high[now];
	if(num[now][1]>=k)return ask(a[now][1],k);
	else return ask(a[now][0],k-num[now][1]-1);
}
void merge(int y){//一定要先插入儿子，再插入这个点 
	if(a[y][0])merge(a[y][0]);
	if(a[y][1])merge(a[y][1]);
	a[y][0]=a[y][1]=0;
	num[y][0]=num[y][1]=0;
	insert(y);
}
int main(){
	n=read();
	m=read();
	q=read();
	for(register int i=1;i<=n;++i){
		high[i]=read();
	}
	for(register int i=1;i<=m;++i){
		c[i]=(d){read(),read(),read()};
	}
	for(register int i=1;i<=q;++i){
		b[i]=(e){read(),read(),read(),i};
	}
	sort(c+1,c+1+m,cmp_1);
	sort(b+1,b+1+q,cmp_2);
	int now=1;
	for(register int i=1;i<=q;++i){
		while(now<=m&&c[now].value<=b[i].x){
			splay(c[now].x);
			int g=c[now].y;
			while(fa[g])g=fa[g];//看是否在同一棵树里 
			if(g==c[now].x){
				++now;
				continue;
			}
			splay(c[now].y);
			if(num[c[now].y][0]+num[c[now].y][1]<num[c[now].x][0]+num[c[now].y][1]){//启发式合并 
				root=c[now].x;
				merge(c[now].y);
			}
			else {
				root=c[now].y;
				merge(c[now].x);
			}
			++now;
		}
		splay(b[i].v);
		ans[b[i].id]=ask(b[i].v,b[i].k);
	}
	for(register int i=1;i<=q;++i)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：天依赛高！ (赞：1)

用kruskal重构树,倍增记录树上一点到祖先的最大路径

易知若一点能够走到,该点子树中任意一点一定能被走到 ( kruskal的建边顺序 ) 

于是只需根据dfs序建主席树 ( 这里有点复杂,请自己好好想想 ) 

每次询问,利用与处理的倍增数组跳到深度最浅的祖先,

祖先的子树在dfs序上是这样一段: dfn[祖先]~dfn[祖先]+size[祖先]-1 ( size是子树大小 ( 包括自己 ) )

然后询问这一段的主席树即可

这题数组开大了显示RE而非MLE,我调了好久

```
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#define rg register
#define _ (int)100010
using namespace std;
int n,m,Q,record[_<<1],num_of_edges=1,dad[_<<1],an[_<<1][19],num,depth[_<<1],size[_<<1],dfn[_<<1],dfns,zhan[_<<1],root[_<<1],H[_<<1],S;
int maxx[_<<1][19],rank[_<<1],Hills[_<<1];
struct pppp
{
	int h,id;
}hill[_<<1];
struct ppp
{
	int cnt,son[2],it/*,size*/;
}tr[(_<<1)*19];
struct pp
{
	int next,to,w;
}edge[_<<1];
struct p
{
	int x,y,w;
}way[_*5];
inline void add(int from,int to,int ww)
{
	edge[++num_of_edges]=(pp){record[from],to,ww};
	record[from]=num_of_edges;
}
inline bool operator <(p x,p y){   return x.w<y.w;   }
int find(int x){   if(x^dad[x])dad[x]=find(dad[x]);   return dad[x];   }
inline int read()
{
	rg int save=0,w=1;rg char q=getchar();
	while(q<'0'||q>'9'){if(q=='-')w=-1;q=getchar();}
	while(q>='0'&&q<='9')save=(save<<3)+(save<<1)+q-'0',q=getchar();
	return save*w;
}
inline int max(int x,int y){   return x<y?y:x;   }
inline void Input()
{
	n=read(),m=read(),Q=read();
	num=n;
	int i;
	for(i=1;i<=n;++i)H[i]=read();
	for(i=1;i<=m;++i)way[i]=(p){read(),read(),read()};
	sort(way+1,way+m+1);
}
inline void kruskal()
{
	int k=0;
	for(int i=1;i<=n;++i)dad[i]=i;
	for(int i=1;i<=m;++i)
	{
		int fx=find(way[i].x),fy=find(way[i].y);
		if(fx^fy)
		{
			++num;
			dad[fx]=dad[fy]=dad[num]=num;
			add(num,fx,way[i].w);
			add(num,fy,way[i].w);
			k++;
			if(k==n-1)break;
		}
	}
}
void insert(int &now,int pos,int l,int r)
{
	tr[++S]=tr[now];
	now=S;
	tr[now].cnt++;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(mid>=pos)insert(tr[now].son[0],pos,l,mid);
	else insert(tr[now].son[1],pos,mid+1,r);
}
void dfs(int i)
{
	dfn[i]=++dfns,zhan[dfns]=i;
	size[i]=1;
	int j,ceng=log(depth[i])/log(2)+1;
	for(j=1;j<=ceng;++j)
		an[i][j]=an[an[i][j-1]][j-1],
		maxx[i][j]=max(maxx[i][j-1],maxx[an[i][j-1]][j-1]);
	bool flag=0;
	for(j=record[i];j;j=edge[j].next)
	{
		int to=edge[j].to;
		depth[to]=depth[i]+1,   an[to][0]=i,   maxx[to][0]=edge[j].w;
		dfs(to);
		size[i]+=size[to];
		Hills[i]+=Hills[to];
		flag=1;
	}
	if(!flag)Hills[i]=1;
}
inline bool operator <(pppp x,pppp y){   return x.h>y.h;   }
inline void pre()
{
	kruskal();
	depth[num]=1;
	dfs(num);
	int j=0;
	for(int i=1;i<=dfns;++i)
		if(H[zhan[i]])
			hill[++j]=(pppp){H[zhan[i]],i};
	sort(hill+1,hill+n+1);
	for(int i=1;i<=n;++i)rank[hill[i].id]=i;
	for(int i=1;i<=dfns;++i)
	{
		root[i]=root[i-1];
		if(rank[i])insert(root[i],rank[i],1,n);
	}
}
inline int ask(int i,int x)
{
	int ceng=log(depth[i])/log(2)+1;
	for(int j=ceng;j>=0;--j)
		if(maxx[i][j]<=x&&(depth[an[i][j]]))i=an[i][j];
	return i;
}
int k_th(int le,int ri,int k,int l,int r)
{
	if(l==r)return l;
	int Num=tr[tr[ri].son[0]].cnt-tr[tr[le].son[0]].cnt;
	int mid=(l+r)>>1;
	if(Num>=k)return k_th(tr[le].son[0],tr[ri].son[0],k,l,mid);
	else return k_th(tr[le].son[1],tr[ri].son[1],k-Num,mid+1,r);
}
inline void doit()
{
	int lastans=0;
	for(int i=1;i<=Q;++i)
	{
		int v=read(),x=read(),k=read();
		if(lastans!=-1)v^=lastans,x^=lastans,k^=lastans;
		int a=ask(v,x);
		if(Hills[a]<k)puts("-1"),lastans=-1;
		else 
			printf("%d\n",lastans=hill[k_th(root[dfn[a]-1],root[dfn[a]+size[a]-1],k,1,n)].h);
	}
}
int main()
{
	Input();
	pre();
	doit();
	return 0;
}

```

---

## 作者：chenxinyang2006 (赞：1)

题意：给你一张无向图，点有点权，边有边权，每次询问从$v$点出发，在只走边权$\le x$的边能到达的点中，询问点权$kth$大的点的点权

显然，边权$> x$的边在解决所有$\le x$的询问时都是没有用处的

所以考虑按边权从小到大做线段树合并，$v$点的线段树表示$v$点能到达的点的所有点权（权值线段树），然后每次询问的时候线段树上二分一下就解决了

按理说应该可持久化线段树合并，每次合并的时候建立新节点的，但是我太懒了，所以直接离线

时间复杂度：$O(q\ log(h))$

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,m,q;

namespace IO{//快读快输板子 
	inline void read(int &x){
		x = 0;
		char ch = getchar();
		while(ch < '0' || ch > '9') ch = getchar();
		while(ch >= '0' && ch <= '9'){
			x = x * 10 + ch - '0';
			ch = getchar();
		}
	}
	void W(int x){
		if(x > 9) W(x / 10);
		putchar(x % 10 + '0');
	}
	inline void write(int x){
		if(x < 0){
			putchar('-');
			W(-x);
		}else{
			W(x);
		}
	}
};
	
namespace OFFLINE{
	struct line{
		int a,b,c;
	}map[500005];//存图 
	struct NODE{
		int v,x,k,id;
	}Q[500005];//离线询问 
	int ans[500005];
	bool cmp1(line x,line y){
		return x.c < y.c;
	}//按困难度排序 
	bool cmp2(NODE a,NODE b){
		return a.x < b.x;
	}
};
	
namespace BIN{//并查集 
	int bin[100005];
	void init(){
		for(int i = 1;i <= n;i++){
			bin[i] = i;
		}
	}
	int F(int x){//注意路径压缩控制复杂度 
		if(bin[x] == x) return x;
		return bin[x] = F(bin[x]);
	}
	void M(int x,int y){
		if(F(x) != F(y)) bin[F(x)] = F(y);
	}
}	
	
namespace segment{//动态开点线段树，支持线段树合并，线段树内二分 
    int T[100005];//存根的编号 
	int cnt;
	struct node{
		int l,r,val;//l左儿子编号，r右儿子编号 
	}tree[100005 << 5];//log(10 ^ 9)差不多1 << 5 
	int upload(int l,int r,int id){//返回值是节点编号 
		int rt = ++cnt;
		tree[rt].val++;
		if(l == r){	
			return rt;
		}
		int mid = l + r >> 1;
		if(id <= mid){
			tree[rt].l = upload(l,mid,id);
		}else{
			tree[rt].r = upload(mid+1,r,id);
		}
		return rt;
	}
	int MERGE(int x,int y,int l,int r){
		if(x == 0) return y;//这样剪枝后复杂度正确 
		if(y == 0) return x;
		tree[x].val += tree[y].val;//合并节点信息，这样直接合并不用再多消耗空间（其实就是懒得可持久化） 
		if(l == r) return x;
		int mid = l + r >> 1;
		tree[x].l = MERGE(tree[x].l,tree[y].l,l,mid);//分别合并 
		tree[x].r = MERGE(tree[x].r,tree[y].r,mid+1,r);
		return x;
	}
	int kth(int rt,int l,int r,int k){
		if(l == r) return l;
		int mid = l + r >> 1;
		if(tree[tree[rt].r].val >= k){//kth大落在右边 
		    return kth(tree[rt].r,mid+1,r,k);
		}else{//落在左边 
			return kth(tree[rt].l,l,mid,k - tree[tree[rt].r].val);
		}
	}
};	
using namespace IO;
using namespace OFFLINE;
using namespace BIN;
using namespace segment;

int main(){
	int tmp,now = 1;//now是当前合并到的边 
	read(n),read(m),read(q);
	init();
	for(int i = 1;i <= n;i++){
		read(tmp);
		T[i] = upload(-1,1000000000,tmp);
	}
	for(int i = 1;i <= m;i++){
		read(map[i].a),read(map[i].b),read(map[i].c);
	}
	sort(map+1,map+m+1,cmp1);
	for(int i = 1;i <= q;i++){
		read(Q[i].v),read(Q[i].x),read(Q[i].k);
		Q[i].id = i;
	}
	sort(Q+1,Q+q+1,cmp2);
	for(int i = 1;i <= q;i++){
		while(map[now].c <= Q[i].x && now <= m){//注意now <= m 
			int X = F(map[now].a),Y = F(map[now].b);//注意找到联通块的根再做，因为不可能给每个联通块的点都合并一次 
			if(X != Y){
				T[X] = MERGE(T[X],T[Y],-1,1000000000);
				T[Y] = T[X];
				M(X,Y);
			}
			now++;
		}
		ans[Q[i].id] = kth(T[F(Q[i].v)],-1,1000000000,Q[i].k);//只有联通块的根存了正确的线段树 
	}
	for(int i = 1;i <= q;i++){
		write(ans[i]);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Santiego (赞：1)

# Peaks 线段树合并

[$\text{My Blog}$](https://www.cnblogs.com/santiego/p/11752328.html)

线段树合并好题。~~吊打主席树、Kruskal重构树的典范~~

首先发现可以离线，我们将所有询问按$x$排序，随着询问再去加边，这样可以去掉路径上$h_i\le x$这一条件使问题极大简化。

然后从$v_i$开始能经过的所有山峰可以看做联通块，于是我们愉快地用并查集维护，用权值线段树查询第$k$大，合并联通块时合并权值线段树即可。很像[[HNOI2012]永无乡](https://www.luogu.org/problem/P3224)。

另外注意此题是查询第$k$大，不是第$k$小。

```cpp
#include <cstdio>
#include <algorithm>
#define MAXN 100010
#define MAXM 500005
using namespace std;
int n,m,q;
inline int read(){
    char ch=getchar();int s=0;
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') s=s*10+ch-'0', ch=getchar();
    return s;
}
int h[MAXN],h_sort[MAXN],rnk[MAXN];
struct nod{
    int u,v,val;
} edge[MAXM];
bool cmp_nod(const nod &a, const nod &b){
    return a.val<b.val;
}
struct question{
    int v,x,k;
    int id;
} qs[MAXM];
bool cmp_qs(const question &a, const question &b){
    return a.x<b.x;
}
int res[MAXM];
int fa[MAXN];
int get_fa(int x){
    if(fa[x]==x) return x;
    return fa[x]=get_fa(fa[x]);
}
#define MAXT MAXN*20
int rot[MAXN],tot,s;
int tre[MAXT],sl[MAXT],sr[MAXT];
void change(int &x, int l, int r, int pos){
    if(x==0) x=++tot;
    tre[x]+=1;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) change(sl[x], l, mid, pos);
    else change(sr[x], mid+1, r, pos);
}
int query(int x, int l, int r, int k){
    if(x==0||tre[x]<k) return 0; // 如果不存在则返回0
    if(l==r) return l;
    int mid=(l+r)>>1;
    if(tre[sr[x]]>=k) return query(sr[x], mid+1, r, k); // 找第k大所以先找右儿子
    else return query(sl[x], l, mid, k-tre[sr[x]]);
}
int merge(int a, int b, int l, int r){
    if(a==0||b==0) return a+b;
    if(l==r){
        tre[a]+=tre[b];
        return a;
    }
    int mid=(l+r)>>1;
    sl[a]=merge(sl[a], sl[b], l, mid);
    sr[a]=merge(sr[a], sr[b], mid+1, r);
    tre[a]=tre[sl[a]]+tre[sr[a]]; // 记得合并后更新
    return a;
}
void merge_edge(int x){
    int fa1=get_fa(edge[x].u),fa2=get_fa(edge[x].v);
    if(fa1==fa2) return; // 如果已经都联通了则不需要合并线段树了
    fa[fa2]=fa1;
    rot[fa1]=merge(rot[fa1], rot[fa2], 1, s);
}
int main(){
    n=read(),m=read(),q=read();
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=n;++i) h_sort[i]=h[i]=read();
    sort(h_sort+1, h_sort+1+n);
    s=unique(h_sort+1, h_sort+1+n)-(h_sort+1);
    for(int i=1;i<=n;++i){
        rnk[i]=lower_bound(h_sort+1, h_sort+1+s, h[i])-h_sort; // 离散化
        change(rot[i], 1, s, rnk[i]);
    }
    for(int i=1;i<=m;++i) edge[i].u=read(),edge[i].v=read(),edge[i].val=read();
    sort(edge+1, edge+1+m, cmp_nod);
    for(int i=1;i<=q;++i) qs[i].v=read(),qs[i].x=read(),qs[i].k=read(),qs[i].id=i;
    sort(qs+1, qs+1+q, cmp_qs);
    int pos=1;
    for(int i=1;i<=q;++i){
        int x=qs[i].x,v=qs[i].v,k=qs[i].k;
        while(pos<=m&&edge[pos].val<=x) merge_edge(pos),++pos; // 把小于等于x的边加入
        int ans=query(rot[get_fa(v)], 1, s, k);
        if(ans==0) res[qs[i].id]=-1;
        else res[qs[i].id]=h_sort[ans]; // 最后答案不是下标而是对应的值
    }
    for(int i=1;i<=q;++i) printf("%d\n", res[i]);
    return 0;
}

```




---

## 作者：Genius_Z (赞：0)

做了这道题发现$kruskal$重构树似乎和$LCT$非常搭配

由于$kruskal$重构树具有非常优美的单调性，即随深度的减小边节点的权值会增大，根节点为权值最大的节点，整棵树是一个大根堆。

那如果我们把权值取负变为小根堆就可以得到更加优美的性质：

### 若只考虑点到根的路径，深度与权值在这棵重构树上同增同减

我们考虑$LCT$的本质，$LCT$是以深度为关键字的$Splay$森林。

那么此时，在重构树上，$LCT$同时也可以看做以权值为关键字的$Splay$森林，此时的$Splay$已经可以同时维护序列与权值，同时具有维护序列的能力和平衡树的性质。

在构建重构树的时候的并查集也可以不用写了，直接用$LCT$判断连通性。

回到本题，我们发现要找的是点$v$困难值小于等于$x$的祖先，那么此时直接把$v$到根的路径提取出来然后在这颗$Splay$上二分即可。之后求子树$k$大就是线段树合并或$dfs$序主席树板子了，这里的$LCT$不需要$makeroot$，所以常数不大，写起来也很短。

$\large Code:$

```cpp
struct edge {
	int u, v, w;
	bool operator<(const edge& e)const {
		return w < e.w;
	}
}e[1000001];
int h[200001], n, m, q, cnt, rt[200001], dfn[200001], siz[200001], mp[200001], org[200001], a[200001], mx;
vector<int>ve[200001];
struct node { int fa, child[2], w; }t[200001];
#define poi(x) (rs(fa(x))==(x))
#define nroot(x) (ls(fa(x))==(x)||rs(fa(x))==x)
inl void rotate(int x) {
	re f = fa(x), gf = fa(f), fs = poi(x), gfs = poi(f), s = son(x, fs ^ 1);
	if (nroot(f))son(gf, gfs) = x;
	son(x, fs ^ 1) = f, son(f, fs) = s;
	if (s)fa(s) = f;
	fa(f) = x, fa(x) = gf;
}
inl void splay(int x) {
	while (nroot(x)) {
		if (nroot(fa(x)))rotate(poi(fa(x)) == poi(x) ? fa(x) : x);
		rotate(x);
	}
}
inl void access(int x) { for (re i = 0; x; x = fa(i = x)) splay(x), rs(x) = i; }
inl int getrk(int x, int w) {
	access(x), splay(x);
	while (son(x, w > t[x].w) && t[x].w != w) x = son(x, w > t[x].w);
	if (t[x].w < w) {
		splay(x), x = rs(x);
		while (ls(x))x = ls(x);
	}
	return splay(x), x;
}
inl int findroot(int x) {
	access(x), splay(x);
	while (ls(x))x = ls(x); splay(x);
	return x;
}
inl void kruskal(void) {
	sort(e + 1, e + 1 + m);
	for (re i = 1, k = 0; i <= m && k < n - 1; i++) {
		re x = findroot(e[i].u), y = findroot(e[i].v);
		if (x != y) k++, t[k + n].w = -e[i].w, fa(x) = fa(y) = k + n, ve[k + n].push_back(x), ve[k + n].push_back(y);
	}
}
#undef ls
#undef rs
struct stnode { int l, r, w; }st[50000001];
#define ls(x) st[x].l
#define rs(x) st[x].r
inl void upd(int k) { st[k].w = st[ls(k)].w + st[rs(k)].w; }
inl void add(int &k, int pre, int l, int r, int p) {
	if (!k)k = ++cnt;
	if (l == r)return (void)(st[k].w = st[pre].w + 1);
	re mid = l + r >> 1;
	if (p <= mid)add(ls(k), ls(pre), l, mid, p), rs(k) = rs(pre);
	else add(rs(k), rs(pre), mid + 1, r, p), ls(k) = ls(pre);
	upd(k);
}
inl void dfs(int x) {
	siz[x] = 1, dfn[x] = ++dfn[0], mp[dfn[0]] = x;
	for (auto i : ve[x]) dfs(i), siz[x] += siz[i];
}
inl int query(int id, int k) {
	re pre = rt[dfn[id] - 1], x = rt[dfn[id] + siz[id] - 1];
	k = st[x].w - st[pre].w - k + 1;
	if (k < 1 || k > st[x].w - st[pre].w)return -1;
	re l = 1, r = mx, mid;
	while (l < r) {
		mid = l + r >> 1;
		if (st[ls(x)].w - st[ls(pre)].w >= k)x = ls(x), pre = ls(pre), r = mid;
		else k -= st[ls(x)].w - st[ls(pre)].w, x = rs(x), pre = rs(pre), l = mid + 1;
	}
	return a[l];
}
signed main(void) {
	n = read<int>(), m = read<int>(), q = read<int>();
	for (re i = 1; i <= n; i++)org[i] = h[i] = read<int>();
	for (re i = 1; i <= m; i++)e[i].u = read<int>(), e[i].v = read<int>(), e[i].w = read<int>();
	kruskal(); dfs(findroot(1));
	sort(org + 1, org + 1 + n), mx = unique(org + 1, org + 1 + n) - org - 1;
	for (re i = 1; i <= n; i++) {
		re k = h[i];
		a[h[i] = lower_bound(org + 1, org + 1 + mx, h[i]) - org] = k;
	}
	for (re i = 1; i <= dfn[0]; i++) {
		if (mp[i] <= n)add(rt[i], rt[i - 1], 1, mx, h[mp[i]]);
		else rt[i] = rt[i - 1];
	}
	while (q--) {
		re x = read<int>(), w = read<int>(), k = read<int>();
		writeln(query(getrk(x, -w), k));
	}
}
```



---

## 作者：Erina (赞：0)

正解: Kruskal重构树

但是我不会怎么办? 发现这一道题不需要强制在线, 珂以强制离线然后线段树合并搞......

江所有查询按照最大困难值排个序, 发现每一次查询时能走的边只会变多不会变少.

然后我们就逐个加入就好了, 然后加个线段树合并查询就行了.

码风略显毒瘤, 敬请见谅.

代码如下:

```cpp
#include<iostream>
#include<algorithm>
#include<tuple>
#define mid ((l+r)>>1)
using namespace std;
namespace fio {
	streambuf* in = cin.rdbuf();
	char bb[1000000], * s = bb, * t = bb;
#define gc() (s==t&&(t=(s=bb)+in->sgetn(bb,1000000),s==t)?EOF:*s++)
	inline int read() {// 快读
		int x = 0;
		char ch = gc();
		while (ch < 48)ch = gc();
		while (ch >= 48)x = x * 10 + ch - 48, ch = gc();
		return x;
	}
}using fio::read;
int n, m, q;
int arr[100005], brr[100005], fa[100005], root[100005], ans[500005];
int ls[50000005], rs[50000005], siz[50000005], cnt;
void insert(int& root, int x, int l, int r, int v) {// 插入元素
	siz[root = ++cnt] = siz[x] + 1;
	if (l != r)if (v <= mid)insert(ls[root], ls[x], l, mid, v), rs[root] = rs[x];
	else ls[root] = ls[x], insert(rs[root], rs[x], mid + 1, r, v);
}
int mergex(int x, int y) {// 线段树合并
	if (!min(x, y))return max(x, y);
	siz[x] = siz[x] + siz[y];
	ls[x] = mergex(ls[x], ls[y]), rs[x] = mergex(rs[x], rs[y]);
	return x;
}
int query(int x, int l, int r, int k) {// 查询第k大
	if (k > siz[x])return 0;
	if (l == r)return l;
	else if (siz[rs[x]] >= k)return query(rs[x], mid + 1, r, k);
	else return query(ls[x], l, mid, k - siz[rs[x]]);
}
typedef tuple<int, int, int>mt;
typedef tuple<int, int, int, int>mmt;
mt rds[500005]; mmt ask[500005];// 离线数组, 分别是路径和查询
int find(int x) { return x == x[fa] ? x : x[fa] = find(x[fa]); }
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y)return;
	fa[y] = x, root[x] = mergex(root[x], root[y]);
}
void w(int x) {// 快速输出
	if (x < 0)x = -x, putchar('-');
	if (x >= 10)w(x / 10);
	putchar(x % 10 + 48);
}
int main() {
	n = read(), m = read(), q = read();
	for (int i = 1; i <= n; i++)arr[i] = brr[i] = read(), fa[i] = i; brr[0] = -1;
	sort(brr + 1, brr + n + 1);
	for (int i = 1; i <= n; i++)arr[i] = lower_bound(brr + 1, brr + n + 1, arr[i]) - brr;// 离散化
	for (int i = 1; i <= n; i++)insert(root[i], 0, 1, n, arr[i]);
	for (int i = 1; i <= m; i++)rds[i] = { read(),read(),read() };
	for (int i = 1; i <= q; i++)ask[i] = { read(),read(),read(),i };
	sort(rds + 1, rds + m + 1, [](mt a, mt b)->bool {return get<2>(a) < get<2>(b); }), sort(ask + 1, ask + q + 1, [](mmt a, mmt b)->bool {return get<1>(a) < get<1>(b); });// 对所有路径和询问排序
	for (int i = 1, ptr = 0; i <= q; i++) {
		while (get<2>(rds[ptr + 1]) <= get<1>(ask[i]) && ptr < m)ptr++, merge(get<0>(rds[ptr]), get<1>(rds[ptr]));
		ans[get<3>(ask[i])] = brr[query(root[find(get<0>(ask[i]))], 1, n, get<2>(ask[i]))];
	}
	for (int i = 1; i <= q; i++)w(ans[i]), putchar('\n');
}
```


---

