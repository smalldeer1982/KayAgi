# Omkar and Tours

## 题目描述

Omkar is hosting tours of his country, Omkarland! There are $ n $ cities in Omkarland, and, rather curiously, there are exactly $ n-1 $ bidirectional roads connecting the cities to each other. It is guaranteed that you can reach any city from any other city through the road network.

Every city has an enjoyment value $ e $ . Each road has a capacity $ c $ , denoting the maximum number of vehicles that can be on it, and an associated toll $ t $ . However, the toll system in Omkarland has an interesting quirk: if a vehicle travels on multiple roads on a single journey, they pay only the highest toll of any single road on which they traveled. (In other words, they pay $ \max t $ over all the roads on which they traveled.) If a vehicle traverses no roads, they pay $ 0 $ toll.

Omkar has decided to host $ q $ tour groups. Each tour group consists of $ v $ vehicles starting at city $ x $ . (Keep in mind that a tour group with $ v $ vehicles can travel only on roads with capacity $ \geq v $ .) Being the tour organizer, Omkar wants his groups to have as much fun as they possibly can, but also must reimburse his groups for the tolls that they have to pay. Thus, for each tour group, Omkar wants to know two things: first, what is the enjoyment value of the city $ y $ with maximum enjoyment value that the tour group can reach from their starting city, and second, how much per vehicle will Omkar have to pay to reimburse the entire group for their trip from $ x $ to $ y $ ? (This trip from $ x $ to $ y $ will always be on the shortest path from $ x $ to $ y $ .)

In the case that there are multiple reachable cities with the maximum enjoyment value, Omkar will let his tour group choose which one they want to go to. Therefore, to prepare for all possible scenarios, he wants to know the amount of money per vehicle that he needs to guarantee that he can reimburse the group regardless of which city they choose.

## 说明/提示

A map of the first sample is shown below. For the nodes, unbolded numbers represent indices and bolded numbers represent enjoyment values. For the edges, unbolded numbers represent capacities and bolded numbers represent tolls.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583H/5086f7eeb8bc4933d6a72b8178b1c2b0de20b6ed.png)For the first query, a tour group of size $ 1 $ starting at city $ 3 $ can reach cities $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , and $ 5 $ . Thus, the largest enjoyment value that they can reach is $ 3 $ . If the tour group chooses to go to city $ 4 $ , Omkar will have to pay $ 8 $ per vehicle, which is the maximum.

For the second query, a tour group of size $ 9 $ starting at city $ 5 $ can reach only city $ 5 $ . Thus, the largest reachable enjoyment value is still $ 3 $ , and Omkar will pay $ 0 $ per vehicle.

For the third query, a tour group of size $ 6 $ starting at city $ 2 $ can reach cities $ 2 $ and $ 4 $ . The largest reachable enjoyment value is again $ 3 $ . If the tour group chooses to go to city $ 4 $ , Omkar will have to pay $ 2 $ per vehicle, which is the maximum.

A map of the second sample is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583H/afb6838e2139f1b619fb5d324b31f7d86d4a3c92.png)For the first query, a tour group of size $ 5 $ starting at city $ 1 $ can only reach city $ 1 $ . Thus, their maximum enjoyment value is $ 1 $ and the cost Omkar will have to pay is $ 0 $ per vehicle.

For the second query, a tour group of size $ 4 $ starting at city $ 1 $ can reach cities $ 1 $ and $ 2 $ . Thus, their maximum enjoyment value is $ 2 $ and Omkar will pay $ 1 $ per vehicle.

For the third query, a tour group of size $ 3 $ starting at city $ 1 $ can reach cities $ 1 $ , $ 2 $ , and $ 3 $ . Thus, their maximum enjoyment value is $ 3 $ and Omkar will pay $ 1 $ per vehicle.

For the fourth query, a tour group of size $ 2 $ starting at city $ 1 $ can reach cities $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ . Thus, their maximum enjoyment value is $ 4 $ and Omkar will pay $ 1 $ per vehicle.

For the fifth query, a tour group of size $ 1 $ starting at city $ 1 $ can reach cities $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , and $ 5 $ . Thus, their maximum enjoyment value is $ 5 $ and Omkar will pay $ 1 $ per vehicle.

## 样例 #1

### 输入

```
5 3
2 2 3 3 3
1 2 4 7
1 3 2 8
2 4 8 2
2 5 1 1
1 3
9 5
6 2```

### 输出

```
3 8
3 0
3 2```

## 样例 #2

### 输入

```
5 5
1 2 3 4 5
1 2 4 1
1 3 3 1
1 4 2 1
2 5 1 1
5 1
4 1
3 1
2 1
1 1```

### 输出

```
1 0
2 1
3 1
4 1
5 1```

## 样例 #3

### 输入

```
5 5
1 2 2 2 2
1 2 5 8
1 3 6 3
1 4 4 5
1 5 7 1
4 1
5 1
6 1
7 1
8 1```

### 输出

```
2 8
2 8
2 3
2 1
1 0```

# 题解

## 作者：qkm66666 (赞：8)

第一问的做法比较简单。

我们将询问离线，按照限制从小到大排序，随时加入变为合法的边，并查集维护一下即可。

难点在于第二问。

注意到两点间费用为边权的最大值。我们考虑建立原树的 $\texttt{Kruscal}$ 重构树，就将求路径上最大值转化为了求 lca 的点权。由于 $\texttt{Kruscal}$ 重构树为一个大根堆，因此深度最小的 lca 即为第二问的答案。

我们有引理，要使两点之间 lca 的深度最小，应当尽量让两点的 dfs 序差异尽量大。这一点画图很好理解，网上也有很多证明，这里就不再赘述。

由此我们可以知道，一个点到一个联通点集之间最小深度的 lca 有两种情况：从这个点到点集中 dfs 序最小的节点，或者到点集中 dfs 序最大的节点。同样可以并查集维护。

时间复杂度 $\mathcal O((n+q)\ logn)$，取决于 lca 的求法。

[AC代码](https://codeforces.com/contest/1586/submission/132305080)

---

## 作者：jerry3128 (赞：7)

数据结构有风险，倒序开题需谨慎。
![](https://cdn.luogu.com.cn/upload/image_hosting/l1g25h7n.png)

-----

首先一定可以发现，每一次询问的连通块一定是由边权大于询问给定限定值的边集组成。所以直接想到将所有询问离线，按边权排序，每次直接查询连通块即可。

对于每次查询，我们要找到
- 连通块的最大值。
- 当前节点到多个最大值节点中，路径上边的花费最大值最大的一条路径。

这需要我们写一个数据结构支持维护连边，与维护连通块内的最大节点与最大节点上的权值。

考虑使用 LCT，连通块的最大值可以通过 LCT 的常见子树维护方式得到，那么路径上的最大值：
- 我们令一个 pair 存储，第一位为 最大节点，第二位为最大边花费。
- 考虑在 pushup 的时候进行对路径最大值的讨论。
	- 如果 pair 第一位由 splay 上左儿子继承，则将其路径最大值直接置于当前第二位。
   - 如果 pair 第一位接受了来自虚儿子或者右儿子的信息，则第二位需要与当前节点的花费取 max。（拆边为点，原树点“花费”为空）
- 同时用 set 进行对于子树的维护。那么就能够得到一个 $\mathcal O(n\log^{2} n)$ 的大常数算法。
![](https://cdn.luogu.com.cn/upload/image_hosting/vf7bs9qx.png)

多次卡常也不行，我们需要从复杂度的根本上对进行优化。我们考虑瓶颈在于虚儿子转移边的 set 中存储了虚儿子的所有信息，插入与删除的时间。

由于我们只取子树中最大节点的信息，这样的虚儿子一定只有一个。发现在实链 splay 上，左右儿子也可能成为最大值。最重要的，本题在询问离线后只有连边操作。那么当 set 的大小大于 3 时，直接弹出最小元素。这样，set 维护虚儿子信息的时间可视为常数。得到一个 $\mathcal O(n\log n)$ 的算法。

[code](https://codeforces.ml/contest/1583/submission/132588024)

---

## 作者：enucai (赞：5)

**2021.10.27 Update:** 修正了[I_am_Accepted](https://www.luogu.com.cn/user/101868)提出的询问。

一篇来自蒟蒻的题解，不喜误喷，有误请私信。

## 题意简述

给一幅 $n$ 个点的树，每条边都有两个值：$c$ 与 $t$，其中 $c$ 表示这条边能承载的最大的重量，$t$ 表示通过这条边所需要的花费。每个点也有一个点权 $e$，表示这个点的有趣程度。两个点之间路径的费用是这两个点之间的路径的所有花费中最大的值。现在有 $q$ 组询问，每组询问给出两个值 $v$ 与 $x$，表示有一辆重量为 $v$ 车从 $x$ 点出发，问你这辆车能到达的所有点中有趣程度最大的那个点的有趣程度，以及到达这些点的所有路径中的花费的最大值。

## 题目分析

> 想A掉一道复杂的题，先从她的简化版开始分析。

假设所有的点的有趣程度各不相同，那么我们可以用离线的做法。处理询问时，我们可以先将所有的询问按照 $v$ 值排序，**从大到小**还是**从小到大**呢？

如果我们要从小到大排序的话，我们就要进行删边操作，有没有什么数据结构支持删边维护连通块的呢？似乎没有，有也很难操作。

因此，我们选择按照 $v$ 值从大到小来排序询问。加边操作只要用一个并查集来维护连通块即可。因此我们可以先将这棵树跑一边dfs，然后用倍增算出 $fa$ 与 $mxval$ 两个数组。其中 $fa[u][i]$ 表示 $u$ 的第 $2^i$ 辈祖先是谁，$mxval[u][i]$ 表示点 $u$ 向上的 $2^i$ 条边中 $t$ 值的最大值。然后就可以 $\log_n$ 求出两点间的距离了（这不是模板吗）。

然后将所有边按照 $c$ 值排序，一条条加边，当加到的边的 $c$ 值到某一组询问的 $v$ 值时，查询一下就好了。

加边的时候合并并查集，每个并查集内记录有趣程度最大的值的编号，输出的时候就很方便了，最大值是 $e[u]$ ，距离就是 $x$ 与 $u$ 之间的距离。

> 想完了简化版的题目，想想简化版的与标准版的有什么区别

我们发现，一个并查集内可能有多个 $e$ 值最大的点。

做法是在每个并查集中记录两个值：$mxi$ 与 $mx$，其中 $mxi$ 表示这个并查集中 $e$ 值最大的点的编号，$mx$ 表示记录编号的那个点到并查集中其他 $e$ 值最大的点的最大距离。合并的时候比较一下两个并查集中 $e[mxi]$ 的大小。

假设我们要合并两个并查集的根为 $u$ 与 $v$，并且合并后以 $u$ 作为根。那么分类讨论：

- $mxi[u]=mxi[u],mx[u]=mx[u]$，当满足 $e[mxi[u]]>e[mxi[v]]$

- $mxi[u]=mxi[v],mx[u]=mx[v]$，当满足 $e[mxi[u]]<e[mxi[v]]$

- $mxi[u]=mxi[u],mx[u]=\max(mx[u],mx[v],getmx(mxi[u],mxi[v]))$，当满足 $e[mxi[u]]=e[mxi[v]]$

其中 $getmx(u,v)$ 表示从 $u$ 点到 $v$ 点的路径的花费。

前两个都很好理解，只有 $mx[u]=\max(mx[u],mx[v],getmx(mxi[u],mxi[v]))$ 可能要稍微想一下。因为他们的最大值要么是在 $u$ 的块中，要么是在 $v$ 的块中，要么就是经过新加的边的一条路经，而这条路径的花费就是 $getmx(mxi[u],mxi[v])$，所以取个max就好了。

问题就这样被解决了……

代码细节应该还好，虽然我交了几发才A，一定是wtcl。

### Talk is cheap, show me the code!

[Codeforces Status](https://codeforces.com/contest/1583/submission/132659594)

```cpp
int n,q;
int fun[200010];
struct Edge{
    int u,v,c,t;
    bool operator<(const Edge &p)const{
        return c>p.c;
    }
}rec[200010];
struct Qry{
    int v,x,ans,ansi,id;
    bool operator<(const Qry &p)const{
        return v>p.v;
    }
}qry[200010];
bool reorder(Qry x,Qry y){
    return x.id<y.id;
}
vector<Edge> e[200010];
void add(int u,int v,int c,int t){e[u].pb((Edge){u,v,c,t});}
int dep[200010],fa[200010][25],mxval[200010][25];
int father[200010],sz[200010],mxi[200010],mx[200010];
int getmx(int u,int v){
    int ans=0;
    if(dep[u]<dep[v]) swap(u,v);
    int dc=dep[u]-dep[v];
    Ror(i,0,20) if(dc&(1<<i)){
        dc^=(1<<i);
        ckmx(ans,mxval[u][i]);
        u=fa[u][i];
    }
    if(u==v) return ans;
    Ror(i,0,20){
        if(fa[u][i]!=fa[v][i]){
            ckmx(ans,max(mxval[u][i],mxval[v][i]));
            u=fa[u][i];
            v=fa[v][i];
        }
    }
    ckmx(ans,max(mxval[u][0],mxval[v][0]));
    return ans;
}
int find(int x){
    return father[x]==x?x:father[x]=find(father[x]);
}
void merge(int u,int v){
    int fu=find(u),fv=find(v);
    if(fu==fv) return;
    if(sz[fu]<sz[fv]) swap(fu,fv);  
    sz[fu]+=sz[fv];
    if(fun[mxi[fu]]>fun[mxi[fv]]);
    else if(fun[mxi[fu]]<fun[mxi[fv]]) mxi[fu]=mxi[fv],mx[fu]=mx[fv];
    else if(fun[mxi[fu]]==fun[mxi[fv]]) mx[fu]=max(max(mx[fu],mx[fv]),getmx(mxi[fu],mxi[fv]));
    father[fv]=fu;
}
void dfs(int u,int f,int val){
    dep[u]=dep[f]+1;
    fa[u][0]=f;
    mxval[u][0]=val;
    For(i,1,20){
        fa[u][i]=fa[fa[u][i-1]][i-1];
        mxval[u][i]=max(mxval[u][i-1],mxval[fa[u][i-1]][i-1]);
    }
    for(auto p:e[u]){
        int v=p.v;
        if(v==f) continue;
        dfs(v,u,p.t);
    }
}
signed main(){
    n=read(),q=read();
    For(i,1,n) fun[i]=read();
    For(i,1,n-1){
        rec[i].u=read();
        rec[i].v=read();
        rec[i].c=read();
        rec[i].t=read();
        add(rec[i].u,rec[i].v,rec[i].c,rec[i].t);
        add(rec[i].v,rec[i].u,rec[i].c,rec[i].t);
    }
    For(i,1,q){
        qry[i].v=read();
        qry[i].x=read();
        qry[i].id=i;
    }
    sort(rec+1,rec+n);
    sort(qry+1,qry+q+1);
    dfs(1,0,0);
    For(i,1,n){
        sz[i]=1;
        father[i]=i;
        mxi[i]=i;
        mx[i]=0;
    }
    int pos=1;
    For(i,1,q){
        while(pos+1<=n&&rec[pos].c>=qry[i].v){
            merge(rec[pos].u,rec[pos].v);
            pos++;
        }
        int fx=find(qry[i].x);
        qry[i].ansi=fun[mxi[fx]];
        qry[i].ans=max(getmx(qry[i].x,mxi[fx]),mx[fx]);
    }
    sort(qry+1,qry+q+1,reorder);
    For(i,1,q){
        printf("%lld %lld\n",qry[i].ansi,qry[i].ans);
    }
    return 0;
}
```

---

## 作者：Little_Fox_Fairy (赞：2)

两问分开考虑。

第一问离线后将边权排序，加边的时候用并查集维护最大值即可。

第二问考虑建 kruskal 重构树，最大费用在 kruskal 重构树即表现为两个点的 LCA。

现在的问题就是要考虑这个连通块中这个点和哪个点的 LCA 深度最小。

显然，要让两个点的 LCA 深度最小，那么就是要让两个点的 dfs 序差值最大。

那么维护并查集的时候顺便维护联通块内 dfs 序最大和最小值的点即可。

## Code
```cpp
//私は灰の魔女イレーナです
#include<bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back 
#define eb emplace_back
#define rep(i,a,b) for (int i=(a);i<=(b);i++) 
#define Rep(i,a,b) for (int i=(a);i>=(b);i--)
#define grep(i,a,b) for (auto i : a[b]) 
using namespace std;
namespace fast_IO {
	#define IOSIZE 100000
		char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
	#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
	#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
	#define isdigit(ch) (ch>47&&ch<58)
	#define isspace(ch) (ch<33)
		template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
		template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
		template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
		inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
		inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
		inline void print(char x) { putchar(x); }
		inline void print(char *x) { while (*x) putchar(*x++); }
		inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
		inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
		inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
		inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
		inline void print(bool b) { putchar(b+48); }
		template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
		template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
		struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
		template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
		template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
	#define cout io
	#define cin io
	#define endl '\n'
} using namespace fast_IO;
const int N=5e5+10;
struct Edge {
    int u,v,w,t;
}ed[N];
struct Ques {
    int x,v,idx;
}q[N];

int n,m,val[N],fa[N],maxx[N],ans1[N],ans2[N],cnt,f[N][20],dfn[N],seq[N],tim;
int maxidx[N],minidx[N],dep[N];
int a[N];
vector<int> e[N];
inline int find(int u) {return (fa[u]==u)?u:(fa[u]=find(fa[u]));}
inline void dfs(int u,int fth) {
	f[u][0]=fth,dfn[u]=++tim,seq[tim]=u,dep[u]=dep[fth]+1;
	rep(i,1,19) f[u][i]=f[f[u][i-1]][i-1];
	for (auto v : e[u]) {
		if (v==fth) continue;
		dfs(v,u);
	}
	return ;
}
inline void kruskal() {
    sort(ed+1,ed+n,[](Edge x,Edge y){return x.t<y.t;});
    cnt=n;
    rep(i,1,n<<1) fa[i]=i;
	rep(i,1,n-1) {
		int u=ed[i].u,v=ed[i].v,w=ed[i].t;
		int x=find(u),y=find(v);
		if (x==y) continue;
		cnt++,a[cnt]=w;
		fa[x]=fa[y]=fa[cnt]=cnt;
		e[cnt].eb(x),e[cnt].eb(y);
		e[x].eb(cnt),e[y].eb(cnt);
	}
	return dfs(cnt,0);
}
inline int LCA(int x,int y) {
    if (x==y) return x;
	if (dep[x]<dep[y])swap(x,y);
	Rep(i,19,0) if (dep[f[x][i]]>=dep[y]) x=f[x][i];
	if (x==y) return x;
	Rep(i,19,0) if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
signed main() {
	cin>>n>>m;
    rep(i,1,n) cin>>val[i],maxx[i]=val[i];
    rep(i,1,n-1) {
        int u,v,w,t;cin>>u>>v>>w>>t;
        ed[i]={u,v,w,t};
    }
    rep(i,1,m) cin>>q[i].v>>q[i].x,q[i].idx=i;
    kruskal();
    sort(q+1,q+m+1,[](Ques x,Ques y){return x.v>y.v;});
    sort(ed+1,ed+n,[](Edge x,Edge y){return x.w>y.w;});
    int it=1;
    rep(i,1,n) fa[i]=i,maxidx[i]=dfn[i],minidx[i]=dfn[i];
    rep(i,1,m) {
        while (it<=n and ed[it].w>=q[i].v) {
            int u=ed[it].u,v=ed[it].v;
            int x=find(u),y=find(v);
            if (x==y) continue;
            if (maxx[x]==maxx[y]) maxidx[x]=max(maxidx[x],maxidx[y]);
            else maxidx[x]=(maxx[x]>maxx[y]?maxidx[x]:maxidx[y]);
            if (maxx[x]==maxx[y]) minidx[x]=min(minidx[x],minidx[y]);
            else minidx[x]=(maxx[x]>maxx[y]?minidx[x]:minidx[y]);
            maxx[x]=max(maxx[x],maxx[y]);
            fa[y]=x;it++;
        }
        int pos=find(q[i].x);
        ans1[q[i].idx]=maxx[pos];
        ans2[q[i].idx]=max(a[LCA(seq[minidx[pos]],q[i].x)],a[LCA(seq[maxidx[pos]],q[i].x)]);
    }
    rep(i,1,m) cout<<ans1[i]<<" "<<ans2[i]<<endl;
	return (0-0);
} 
```

---

## 作者：james1BadCreeper (赞：2)

第一问比较经典，离线，将询问按照 $v$ 从大到小排序，依次加入边，DFS 合并连通块，维护最大值即可。

第二问，希望路径上 $t$ 的最大值尽可能大，Kruskal 重构树！建立一棵基于 $t$ 的边权重构树。设能到达的节点是 $y$，那么答案为 $\max\{a_{\operatorname{LCA}(x,y)}\}$。

由于 LCA 必定在 $x$ 到根节点的路径上，也就是说，我们希望该 LCA 的深度尽可能小。什么时候满足呢？将所有 $y$ 按照 DFS 序排序，其中 DFS 序最小和最大的可能称为答案（Kruskal 重构树是一棵二叉树，想要 LCA 离 $x$ 越远，那么 $y$ 就必定离 $x$ 越远，也就是 DFS 序差越大）。

实现上只需要先建出 Kruskal 重构树，然后在第一问时并查集维护 DFS 序最大最小值。时间复杂度在 $O(n\log n)$ 级别。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n, q, ans1[200005], ans2[200005]; 
int a[200005]; 
struct Query {
    int v, x, id; 
    bool operator< (const Query &a) const { return v > a.v; }
} Q[200005];
struct edge {
    int a, b, c, t; 
    bool operator< (const edge &a) const { return c > a.c; }
} e[200005];
vector<int> G[400005]; 

int bin[400005], val[400005], mx[200005], mn[200005]; 
int find(int x) { return bin[x] == x ? x : bin[x] = find(bin[x]); }

int dfn[400005], num, mi[19][400005], lg[400005], idx[400005]; 
inline int get(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
void dfs(int x, int fa) {
    mi[0][dfn[x] = ++num] = fa; idx[num] = x; 
    for (int y : G[x]) if (y != fa) dfs(y, x); 
}
inline int LCA(int u, int v) {
    if (u == v) return u; 
    if ((u = dfn[u]) > (v = dfn[v])) swap(u, v); 
    int k = lg[v - u]; 
    return get(mi[k][u + 1], mi[k][v - (1 << k) + 1]); 
}

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> q; 
    for (int i = 1; i <= n; ++i) cin >> a[i]; 
    for (int i = 1; i <= n * 2; ++i) bin[i] = i; 
    for (int i = 2; i <= n * 2; ++i) lg[i] = lg[i >> 1] + 1; 

    // 建立 Kruskal 重构树
    for (int i = 1; i < n; ++i) cin >> e[i].a >> e[i].b >> e[i].c >> e[i].t; 
    sort(e + 1, e + n, [&](edge a, edge b) { return a.t < b.t; });    
    int tot = n; 
    for (int i = 1; i < n; ++i) {
        int u = find(e[i].a), v = find(e[i].b); 
        val[++tot] = e[i].t; bin[u] = bin[v] = tot; 
        G[tot].emplace_back(u); G[u].emplace_back(tot); 
        G[tot].emplace_back(v); G[v].emplace_back(tot); 
    } dfs(tot, 0); 
    for (int i = 1; i <= lg[n * 2]; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n * 2 - 1; ++j)
            mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]); 
    
    for (int i = 1; i <= q; ++i) cin >> Q[i].v >> Q[i].x, Q[i].id = i; 
    for (int i = 1; i <= n; ++i) bin[i] = i, val[i] = a[i], mn[i] = mx[i] = dfn[i]; 
    sort(e + 1, e + n); sort(Q + 1, Q + q + 1); 
    for (int i = 1, j = 0; i <= q; ++i) {
        while (j < n - 1 && e[j + 1].c >= Q[i].v) {
            ++j; 
            int u = find(e[j].a), v = find(e[j].b); 
            if (val[u] == val[v]) mx[v] = max(mx[v], mx[u]); 
            else mx[v] = val[u] > val[v] ? mx[u] : mx[v]; 
            if (val[u] == val[v]) mn[v] = min(mn[v], mn[u]); 
            else mn[v] = val[u] > val[v] ? mn[u] : mn[v]; 
            val[v] = max(val[v], val[u]); 
            bin[u] = v; 
        }
        int id = Q[i].id, x = Q[i].x, u = find(x); 
        ans1[id] = val[u]; 
        if (idx[mx[u]] != x) ans2[id] = max(ans2[id], val[LCA(x, idx[mx[u]])]);
        if (idx[mn[u]] != x) ans2[id] = max(ans2[id], val[LCA(x, idx[mn[u]])]); 
    }

    for (int i = 1; i <= q; ++i) cout << ans1[i] << " " << ans2[i] << "\n"; 
    return 0; 
}
```

---

## 作者：FutaRimeWoawaSete (赞：2)

首先存在一种比较简单的做法：对于询问 $1$ 随便做，对于询问 $2$ 我们可以对于原图按照**边的费用权**建立 Kruscal 重构树并确定每个点的 dfs 序，按照**边的容量权**离线下来套路动态连图的同时，维护连通块内点权最大的点中 dfs 序最大与 dfs 序最小的位置，最后的答案只有可能是这两个点。

然后显然维护的东西具有结合律，可以维护，时间复杂度瓶颈在于排序。

这里提出一种有关动态树维护的方法。不难发现一个比较简单的事实：将 $x$ 提为原连通块的根，记 $1$ 类查询的答案为 $as_1$，问题转化成了查询所有子树内 $\max_{v_i = as_1} W(i , x)$，其中 $W(i,x)$ 为 $i \sim x$ 路径上边权的最大值。

观察边权不好处理，用 kruscal 重构树边权转点权的方法将一条边变成一个点，连接 $x,y$ 并将边权转移到点权上，方便维护。

再次考虑到我们的查询都是以 $x$ 为根查询的，启发我们在以 $x$ 为根建立的 LCT 的实链中，**任意一条祖先-子孙链**都可以变成 $x$ 到一个节点的路径的一部分。

考虑这样维护：在实链 Splay 中的一个点，我们维护一个二元组 $(x,y)$，其中 $x$ 表示点权最大节点的点权，$y$ 表示当前 Splay 子树中一条 $\max(c)$ 最大的路径。

分为 Splay 中的左子树，右子树，以及 $x$ 的虚子树分开贡献：

- 对于左右虚子树的答案提取上来更新；

- 对于右子树和虚子树，将答案二元组的 $x$ 与左子树内**维护出来最大的一条边权 $y$ 进行组合贡献答案**；

- 涉及 makeroot 操作，维护一个反向答案。

考虑这么做显然能维护每一条实链向任意虚子树行走的路径，维护是正确的。

然后照抄了一个 @[jerry3128](https://www.luogu.com.cn/user/27338) 题解中基于 set 的小优化，时间复杂度变成 $O((n + q) \log n)$。

```cpp
/*
注意到最后查询是在一个点为根时查询，所以就在 LCT 上可以分类讨论维护 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 4e5 + 5;
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x*f;
}
void print(long long x) {
    if(x>9) print(x/10);
    *O++=x%10+'0';
}

#define Pair pair<int,int> 
#define pr make_pair
int n,m;
struct node
{
	int ch[2],f,rev,val,mxcst,cst;
	Pair L,R;//正向信息和 reverse 后的信息 
	node(){ch[0] = ch[1] = f = rev = val = mxcst = cst = L.first = L.second = R.first = R.second = 0;}
	multiset<Pair> smdd;
};
struct LCT
{
	node t[Len];
	#define ls t[x].ch[0]
	#define rs t[x].ch[1]
	Pair get(int x){return t[x].smdd.size() ? *t[x].smdd.rbegin() : pr(-1 , -1);}
	void ins(int x,int y)
	{
		if(!y) return;
		t[x].smdd.insert(t[y].L);
		while(t[x].smdd.size() > 3) t[x].smdd.erase(t[x].smdd.find(*t[x].smdd.begin()));
	}
	void del(int x,int y)
	{
		if(!y) return;
		if(t[x].smdd.find(t[y].L) != t[x].smdd.end()) t[x].smdd.erase(t[x].smdd.find(t[y].L));
	}
	void push_up(int x)
	{
		t[x].mxcst = max(t[x].cst , max(t[ls].mxcst , t[rs].mxcst));
		Pair fk = get(x);
		t[x].L = t[ls].L;
		int ls1 = t[ls].mxcst;
		if(x <= n) t[x].L = max(t[x].L , pr(t[x].val , ls1));
		else ls1 = max(ls1 , t[x].cst);
		t[x].L = max(t[x].L , pr(fk.first , max(fk.second , ls1)));
		t[x].L = max(t[x].L , pr(t[rs].L.first , max(t[rs].L.second , ls1)));
		//实链反转信息
		t[x].R = t[rs].R;
		int ls2 = t[rs].mxcst;
		if(x <= n) t[x].R = max(t[x].R , pr(t[x].val , ls2));
		else ls2 = max(ls2 , t[x].cst);
		t[x].R = max(t[x].R , pr(fk.first , max(fk.second , ls2)));
		t[x].R = max(t[x].R , pr(t[ls].R.first , max(t[ls].R.second , ls2)));
		//printf("%d %d %d %d %d\n",x,t[x].L.first,t[x].L.second,t[x].R.first,t[x].R.second);
	}
	void push_rev(int x)
	{
		if(!x) return;
		t[x].rev ^= 1;
		swap(t[x].ch[0] , t[x].ch[1]);
		swap(t[x].L , t[x].R);
	}
	void push_down(int x)
	{
		if(t[x].rev)
		{
			push_rev(t[x].ch[0]);
			push_rev(t[x].ch[1]);
			t[x].rev = 0;
		}
	}
	int idf(int x)
	{
		if(!t[x].f) return -1;
		if(t[t[x].f].ch[0] == x) return 0;
		if(t[t[x].f].ch[1] == x) return 1;
		return -1;
	}
	void llcon(int son,int fa,int opt)
	{
		if(opt != -1) t[fa].ch[opt] = son;
		t[son].f = fa;
	}
	void push_all(int x)
	{
		if(idf(x) != -1) push_all(t[x].f);
		push_down(x);
	}
	void rotate(int x)
	{
		int y = t[x].f , z = t[y].f , opx = idf(x) , opy = idf(y) , u = t[x].ch[opx ^ 1];
		llcon(u , y , opx);
		llcon(y , x , opx ^ 1);
		llcon(x , z , opy);
		push_up(y) , push_up(x);
	}
	void Splay(int x)
	{
		//printf("###%d %d\n",x,t[x].f);
		push_all(x);
		while(idf(x) != -1)
		{
			int ff = t[x].f;
			if(idf(ff) == -1) rotate(x);
			else
			{
				if(idf(ff) == idf(x)) rotate(ff) , rotate(x);
				else rotate(x) , rotate(x);
			}
		}
	}
	void access(int x)
	{
		//printf("###%d\n",x);
		int lst = 0;
		while(x)
		{
			Splay(x);
			ins(x , t[x].ch[1]);
			del(x , lst);
			t[x].ch[1] = lst;
			push_up(x);
			lst = x;
			x = t[x].f;
		}
	}
	void makeroot(int x)
	{
		//printf("((((%d\n",x);
		access(x);
		Splay(x);
		push_rev(x);
		//printf("))))%d\n",x);
	}
	void link(int x,int y)
	{
		//printf("???%d %d\n",x,y);
		makeroot(y);
		access(x);
		Splay(x);
		t[x].ch[1] = y , t[y].f = x;
		push_up(x);
	}
}LLCT;
struct Node
{
	int x,y,id,w1,w2;
	Node(){x = y = id = w1 = w2 = 0;}
	Node(int X,int Y,int ID,int W1,int W2){x = X , y = Y , id = ID , w1 = W1 , w2 = W2;}
}Edge[Len],Q[Len];
int Print[Len][2];
bool cmp(Node x,Node y){return x.w1 > y.w1;}
int main()
{
	n = read() , m = read();
	for(int i = 1 ; i <= n ; i ++)
	{
		int x;x = read();
		LLCT.t[i].val = x;LLCT.push_up(i);
	}
	for(int i = 1 ; i < n ; i ++)
	{
		int u,v,c,t;u = read() , v = read() , c = read() , t = read();
		Edge[i] = Node(u , v , i , c , t);
		LLCT.t[i + n].cst = t;LLCT.push_up(i + n);
	}
	//puts("");
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;y = read() , x = read();
		Q[i] = Node(x , 0 , i , y , 0);
	}
	sort(Edge + 1 , Edge + n , cmp);
	sort(Q + 1 , Q + 1 + m , cmp);
	int now = 1;
	for(int i = 1 ; i <= m ; i ++)
	{
		while(now < n && Q[i].w1 <= Edge[now].w1) 
		{
			LLCT.link(Edge[now].x , Edge[now].id + n);
			LLCT.link(Edge[now].y , Edge[now].id + n);
			now ++;
		}
		LLCT.makeroot(Q[i].x);
		Print[Q[i].id][0] = LLCT.t[Q[i].x].L.first;
		Print[Q[i].id][1] = LLCT.t[Q[i].x].L.second;
	} 
	for(int i = 1 ; i <= m ; i ++) 
	{
		print(Print[i][0]);
		*O ++ = ' ';
		print(Print[i][1]);
		*O ++ = '\n';
	}
	fwrite(obuf,O-obuf,1,stdout);
	return 0;	
} 
```

---

## 作者：ax_by_c (赞：1)

upd：把 **DSU** 改成了 **并查集** 以防有人看不懂

~~大家好我又来找借口了：题解想到的东西我全想到了，为什么我没会/yiw~~

第一问显然离线后跑并查集即可。

对于第二问，假装对连通块内权值最大的点（关键点）建虚树，然后分类。

- 给定点在虚树上。

  虚树上最大边权。

- 给定点不在虚树上。

  虚树上最大边权与给定点到任意关键点路径上最大边权的较大值。

好吧其实不用分。

考虑维护虚树上最大边权，先把它记下来，每次要么是继承一边的虚树要么是两个虚树合并，合并时只要任意找两个关键点即可统计新加的那些边的贡献。

于是维护连通块内任意关键点即可解决一切问题。

时间复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
const int N=2e5+5;
const int LN=22;
int n,q,a[N];
struct edge{
	int u,v,c;
};
vector<edge>E;
bool cmpe(edge x,edge y){
	return x.c>y.c;
}
struct Q{
	int u,w,id;
};
vector<Q>qs;
bool cmpq(Q x,Q y){
	return x.w>y.w;
}
struct EE{
	int v,w;
};
vector<EE>g[N];
int fa[N],de[N],tf[N];
void dfs(int u){
	for(auto e:g[u]){
		if(e.v==fa[u])continue;
		fa[e.v]=u;
		de[e.v]=de[u]+1;
		tf[e.v]=e.w;
		dfs(e.v);
	}
}
int lt[N][LN],mx[N][LN];
int get(int x,int y){
	if(de[x]>de[y])swap(x,y);
	int res=0;
	for(int i=20;i>=0;i--)if(de[y]-(1<<i)>=de[x])res=max(res,mx[y][i]),y=lt[y][i];
	for(int i=20;i>=0;i--)if(lt[x][i]&&lt[x][i]!=lt[y][i])res=max({res,mx[x][i],mx[y][i]}),x=lt[x][i],y=lt[y][i];
	if(x!=y)res=max({res,tf[x],tf[y]});
	return res;
}
struct DSU{
	struct node{
		int fa,sz,mx,mxd,val;
	}fa[N];
	void Init(int n){
		for(int i=1;i<=n;i++)fa[i]={i,1,a[i],i,0};
	}
	int find(int x){
		if(fa[x].fa==x)return x;
		return fa[x].fa=find(fa[x].fa);
	}
	bool meg(int x,int y){
		x=find(x);
		y=find(y);
		if(x==y)return 0;
		if(fa[x].sz>fa[y].sz)swap(x,y);
		fa[x].fa=y;
		fa[y].sz+=fa[x].sz;
		if(fa[x].mx>fa[y].mx)fa[y].mx=fa[x].mx,fa[y].mxd=fa[x].mxd,fa[y].val=fa[x].val;
		else if(fa[x].mx==fa[y].mx)fa[y].val=max({fa[y].val,fa[x].val,get(fa[x].mxd,fa[y].mxd)});
		return 1;
	}
	int Qmx(int u){
		return fa[find(u)].mx;
	}
	int Qval(int u){
		return max(fa[find(u)].val,get(u,fa[find(u)].mxd));
	}
}dsu;
int ans1[N],ans2[N];
void main(){
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1,u,v,c,t;i<n;i++){
		scanf("%d %d %d %d",&u,&v,&c,&t);
		E.push_back({u,v,c});
		g[u].push_back({v,t});
		g[v].push_back({u,t});
	}
	for(int i=1,v,x;i<=q;i++){
		scanf("%d %d",&v,&x);
		qs.push_back({x,v,i});
	}
	sort(E.begin(),E.end(),cmpe);
	sort(qs.begin(),qs.end(),cmpq);
	dfs(1);
	for(int i=1;i<=n;i++)lt[i][0]=fa[i],mx[i][0]=tf[i];
	for(int j=1;j<=20;j++)for(int i=1;i<=n;i++)lt[i][j]=lt[lt[i][j-1]][j-1],mx[i][j]=max(mx[i][j-1],mx[lt[i][j-1]][j-1]);
	dsu.Init(n);
	int ad=0;
	for(auto it:qs){
		while(ad<(int)E.size()&&E[ad].c>=it.w){
			dsu.meg(E[ad].u,E[ad].v);
			ad++;
		}
		ans1[it.id]=dsu.Qmx(it.u);
		ans2[it.id]=dsu.Qval(it.u);
	}
	for(int i=1;i<=q;i++)printf("%d %d\n",ans1[i],ans2[i]);
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：bryce (赞：1)

## [Omkar and Tours](https://www.luogu.com.cn/problem/CF1583H)
### 思路
考虑第一个问题非常好做，直接对所有询问离线下来，排个序，并查集维护连通块。

如何做第二个问题？对 $t$ 求一个 kruskal 重构树，由于是棵树，所以 $lca$ 权值即为两点之间最大费用，由于 $lca$ 越浅费用越大，排完序后用并查集维护当前这个连通块中的最大点权和最大点权的点之间的 $lca$，最后用这个 $lca$ 与要求的 $x$ 取一个 $lca$ 即可。
### 代码
```cpp
#include<iostream>
#include<algorithm>

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 4e5 + 10;
int n, q, ans1[N], ans2[N];
int c[N];
struct node{
    int u, v, w;
    bool operator < (const node &b) const{
        return w < b.w;
    }
}f[N];
struct edge{
    int u, v, w;
    bool operator < (const edge &b) const{
        return w > b.w;
    }
}e[N];
int fi[N], val[N];
int find(int x){
    return (x == fi[x] ? fi[x] : fi[x] = find(fi[x]));
}
struct kru{
    int v, nxt;
}k[N << 1];
int head_kru[N], cnt_kru;
void add_kru(int u, int v){
    k[++cnt_kru] = (kru){v, head_kru[u]};
    head_kru[u] = cnt_kru;
}
void kruskal(){
    sort(f + 1, f + n);
    for (int i = 1; i < (n << 1); i++) fi[i] = i;
    int tot = 0;
    for (int i = 1; i < n; i++){
        int eu = find(f[i].u), ev = find(f[i].v);
        if (eu == ev) continue;
        tot++;
        fi[eu] = fi[ev] = n + tot;
        add_kru(eu, n + tot), add_kru(n + tot, eu);
        add_kru(ev, n + tot), add_kru(n + tot, ev);
        val[n + tot] = f[i].w;
    }
}
int fa[N][21], dep[N];
void dfs(int u, int fu){
    fa[u][0] = fu;
    dep[u] = dep[fu] + 1;
    for (int i = head_kru[u]; i; i = k[i].nxt){
        int v = k[i].v;
        if (v == fu) continue;
        dfs(v, u);
    }
}
void init(){
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j < (n << 1); j++) fa[j][i] = fa[fa[j][i - 1]][i - 1];
}
int lca(int x, int y){
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (int i = 19; i >= 0; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
struct Query{
    int c, x, id;
    bool operator < (const Query &b) const{
        return c > b.c;
    }
}Q[N];
struct dsu{
    int fa, mx, pos;
}d[N];
int fd(int x){
    return (x == d[x].fa ? d[x].fa : d[x].fa = fd(d[x].fa));
}
void merge(int u, int v){
    int eu = fd(u), ev = fd(v);
    d[ev].fa = eu;
    if (d[ev].mx > d[eu].mx){
        d[eu].mx = d[ev].mx;
        d[eu].pos = d[ev].pos;
    }else if (d[eu].mx == d[ev].mx){
        d[eu].pos = lca(d[eu].pos, d[ev].pos);
    }
}

int main(){
    n = read(), q = read();
    for (int i = 1; i <= n; i++) c[i] = read();
    for (int i = 1; i < n; i++){
        int u = read(), v = read(), w = read(), t = read();
        e[i] = (edge){u, v, w};
        f[i] = (node){u, v, t};
    }
    kruskal();
    dfs((n << 1) - 1, 0);
    init();
    for (int i = 1; i <= q; i++) Q[i] = (Query){read(), read(), i};
    sort(e + 1, e + n);
    sort(Q + 1, Q + q + 1);
    for (int i = 1; i <= n; i++) d[i].fa = d[i].pos = i, d[i].mx = c[i];
    for (int i = 1, j = 0; i <= q; i++){
        while (e[j + 1].w >= Q[i].c && j < n){
            j++;
            merge(e[j].u, e[j].v);
        }
        int y = fd(Q[i].x);
        ans1[Q[i].id] = d[y].mx;
        ans2[Q[i].id] = val[lca(Q[i].x, d[y].pos)];
    }
    for (int i = 1; i <= q; i++) cout << ans1[i] << ' ' << ans2[i] << '\n';
    return 0;
}
```

---

## 作者：Leasier (赞：1)

前置芝士：[Kruskal 重构树](https://oi-wiki.org/graph/mst/#kruskal-重构树)

看到两维 $c, t$ 的限制，果断先对 $c$ 那维离线，按 $c$ 从大到小依次加入并回答询问。

此时我们不难解决第一问：离线加边时在并查集里维护 $e_i$ 的最大值即可。

现在考虑加上第二问，此时我们需要知道**从 $x$ 出发，到所有 $e_i$ 最大的点经过的最大边权的最大值**。

不难想到可以先建出以 $t$ 为权值的 Kruskal 重构树，然后在并查集里维护当前集合内所有 $e_i$ 最大的点在重构树上的 LCA，查询时输出 $x$ 与 $x$ 所在集合维护的 LCA 处的点值即可。时间复杂度为 $O(n \log n + q(\log n + \log q))$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

typedef struct {
	int nxt;
	int start;
	int end;
	int dis;
	int cost;
} Edge;

typedef struct {
	int id;
	int v;
	int x;
} Query;

int cnt = 0;
int root[400007], happy[400007], cur_lca[400007], e[200007], fa[400007][27], head[400007], val[400007], depth[400007], ansa[200007], ansb[200007];
Edge edge1[200007], edge2[400007];
Query query[200007];

bool operator <(const Query a, const Query b){
	return a.v > b.v;
}

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		root[i] = happy[i] = cur_lca[i] = i;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

bool cmp1(const Edge a, const Edge b){
	return a.cost < b.cost;
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline void add_edge(int start, int end){
	cnt++;
	edge2[cnt].nxt = head[start];
	head[start] = cnt;
	edge2[cnt].end = end;
}

void dfs(int u){
	int t;
	depth[u] = depth[fa[u][0]] + 1;
	t = log2(depth[u]);
	for (register int i = 1; i <= t; i++){
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (register int i = head[u]; i != 0; i = edge2[i].nxt){
		dfs(edge2[i].end);
	}
}

bool cmp2(const Edge a, const Edge b){
	return a.dis > b.dis;
}

inline int lca(int u, int v){
	if (u == 0) return v;
	if (v == 0) return u;
	if (depth[u] < depth[v]) swap(u, v);
	while (depth[u] > depth[v]) u = fa[u][(int)log2(depth[u] - depth[v])];
	if (u == v) return u;
	for (register int i = log2(depth[u]); i >= 0; i--){
		if (fa[u][i] != fa[v][i]){
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

inline void merge(int x, int y){
	int x_root = get_root(x), y_root = get_root(y);
	if (x_root != y_root){
		root[y_root] = x_root;
		if (e[happy[x_root]] < e[happy[y_root]]){
			e[happy[x_root]] = e[happy[y_root]];
			cur_lca[x_root] = cur_lca[y_root];
		} else if (e[happy[x_root]] == e[happy[y_root]]){
			cur_lca[x_root] = lca(cur_lca[x_root], cur_lca[y_root]);
		}
	}
}

int main(){
	int n = read(), q = read(), m = n;
	init(n * 2 - 1);
	for (register int i = 1; i <= n; i++){
		e[i] = read();
	}
	for (register int i = 1; i < n; i++){
		edge1[i].start = read();
		edge1[i].end = read();
		edge1[i].dis = read();
		edge1[i].cost = read();
	}
	sort(edge1 + 1, edge1 + n, cmp1);
	for (register int i = 1; i < n; i++){
		int u = get_root(edge1[i].start), v = get_root(edge1[i].end);
		m++;
		root[u] = root[v] = fa[u][0] = fa[v][0] = m;
		val[m] = edge1[i].cost;
		add_edge(m, u);
		add_edge(m, v);
	}
	dfs(m);
	for (int i = 1; i <= q; i++){
		query[i].id = i;
		query[i].v = read();
		query[i].x = read();
	}
	init(n);
	sort(edge1 + 1, edge1 + n, cmp2);
	sort(query + 1, query + q + 1);
	for (register int i = 1, j = 1; i <= q; i++){
		int x_root;
		while (j < n && edge1[j].dis >= query[i].v){
			merge(edge1[j].start, edge1[j].end);
			j++;
		}
		x_root = get_root(query[i].x);
		ansa[query[i].id] = e[happy[x_root]];
		ansb[query[i].id] = val[lca(query[i].x, cur_lca[x_root])];
	}
	for (register int i = 1; i <= q; i++){
		cout << ansa[i] << " " << ansb[i] << endl;
	}
	return 0;
}
```

---

## 作者：TulipeNoire (赞：0)

**CF1583H**

此题看起来形式非常像 kruskal 重构树，所以直接考虑使用 kruskal 重构树解决第一问。具体地，我们可以将边按照 $c$ 从大到小排序，建立重构树，点权为 $c$。令 $p$ 为满足点权大于等于 $v$ 的 $x$ 的最浅祖先，那么显然我们可以发现所有能到达的点就是，以 $v$ 为根的子树的所有叶节点所表示的点。

第二如何处理呢？继续考虑 kruskal 重构树。以 $t$ 从小到大再建一颗重构树，点权为 $t$。那么，两点之间的最大边就是重构树上的 $\text{lca}$ 的点权。假如在第一问中，满足条件的点有 $k$ 个。我们实际上就是对每一个来与 $x$ 求新重构树上的 $\text{lca}$。这样做时间复杂度是较高的，我们考虑一个性质：在这 $k$ 个点中，只需要求两个就好了，分别是在第二棵重构树中 $\text{DFS}$ 序最大和最小的。这个较为易证，也可以感性理解。

所以，我们在建第一棵重构树时，再维护一下子树的叶结点中再在第二棵重构树中 $\text{DFS}$ 序最大和最小的即可。时间复杂度 $O((n+q)\log n)$，理论上可达到线性空间。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,q,e[N],fa[2][N<<1],to[2][N<<1],cnt0,cnt1,tmp;
struct edge {
    int u,v,c,t;
}a[N];
struct P {
    int fa[20],dat,dfn,minn,maxn,val,dep;//val是子树中叶子点权最大值，只对第一颗线段树有用
    vector<int>G;
}tr[2][N<<1];//0表示第一颗重构树，1表示第二棵
inline bool cmp1(edge x,edge y) {
    return x.c>y.c;
}
inline bool cmp2(edge x,edge y) {
    return x.t<y.t;
}
int get(int t,int x) {
    if (fa[t][x]==x) return x;
    return fa[t][x]=get(t,fa[t][x]);
}
inline void merge(int t,int x,int y) {
    fa[t][get(t,x)]=get(t,y);
    return;
}
void dfs(int t,int p,int lst) {
    tr[t][p].dfn=++tmp;
    to[t][tmp]=p;
    tr[t][p].dep=tr[t][lst].dep+1;
    tr[t][p].fa[0]=lst;
    for (int i=1;i<20;i++) tr[t][p].fa[i]=tr[t][tr[t][p].fa[i-1]].fa[i-1];
    for (int i=0;i<tr[t][p].G.size();i++) dfs(t,tr[t][p].G[i],p);
    return;
}
inline int lca(int x,int y) {//倍增求lca
    if (tr[0][x].dep<tr[0][y].dep) swap(x,y);
    for (int i=19;i>=0;i--) {
        if (tr[0][tr[0][x].fa[i]].dep>=tr[0][y].dep) x=tr[0][x].fa[i];
    }
    if (x==y) return x;
    for (int i=19;i>=0;i--) {
        if (tr[0][x].fa[i]!=tr[0][y].fa[i]) x=tr[0][x].fa[i],y=tr[0][y].fa[i];
    }
    return tr[0][x].fa[0];
}
int main() {
    scanf("%d %d",&n,&q);
    for (int i=1;i<=n;i++) scanf("%d",&e[i]),fa[0][i]=fa[1][i]=i;
    for (int i=1;i<n;i++) scanf("%d %d %d %d",&a[i].u,&a[i].v,&a[i].c,&a[i].t);
    sort(a+1,a+n,cmp2);
    cnt0=cnt1=n;
    for (int i=1;i<n;i++) {//建立kruskal重构树
        ++cnt0;
        fa[0][cnt0]=cnt0;
        tr[0][cnt0].dat=a[i].t;
        tr[0][cnt0].G.push_back(get(0,a[i].u));
        tr[0][cnt0].G.push_back(get(0,a[i].v));
        merge(0,a[i].u,cnt0);
        merge(0,a[i].v,cnt0);
    }
    dfs(0,cnt0,0);
    sort(a+1,a+n,cmp1);
    for (int i=1;i<=n;i++) tr[1][i].val=e[i],tr[1][i].minn=tr[1][i].maxn=tr[0][i].dfn;
    for (int i=1;i<n;i++) {
        ++cnt1;
        fa[1][cnt1]=cnt1;
        tr[1][cnt1].dat=a[i].c;
        int getu=get(1,a[i].u),getv=get(1,a[i].v);
        tr[1][cnt1].G.push_back(getu);
        tr[1][cnt1].G.push_back(getv);
        tr[1][cnt1].val=max(tr[1][getu].val,tr[1][getv].val);
        if (tr[1][getu].val==tr[1][getv].val) {
            tr[1][cnt1].minn=min(tr[1][getu].minn,tr[1][getv].minn);
            tr[1][cnt1].maxn=max(tr[1][getu].maxn,tr[1][getv].maxn);
        } else if (tr[1][getu].val>tr[1][getv].val) {
            tr[1][cnt1].minn=tr[1][getu].minn;
            tr[1][cnt1].maxn=tr[1][getu].maxn;
        } else {
            tr[1][cnt1].minn=tr[1][getv].minn;
            tr[1][cnt1].maxn=tr[1][getv].maxn;
        }
        merge(1,a[i].u,cnt1);
        merge(1,a[i].v,cnt1);
    }
    dfs(1,cnt1,0);
    for (int i=1;i<=q;i++) {
        int v,x;
        scanf("%d %d",&v,&x);
        int cur=x;
        for (int j=19;j>=0;j--) {
            if (tr[1][tr[1][cur].fa[j]].dat>=v) cur=tr[1][cur].fa[j];
        }//找到题解中的p
        printf("%d ",tr[1][cur].val);
        int l=to[0][tr[1][cur].minn],r=to[0][tr[1][cur].maxn];
        printf("%d\n",max(tr[0][lca(x,l)].dat,tr[0][lca(x,r)].dat));
    }
    return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：0)

考场一眼口胡出来的 $O((n+q)\log n)$ 的并查集+**树剖**+虚树的做法，~~因为在考场上不想打 LCT 于是这个做法没有 LCT~~。

由于是口胡的可能有很多地方实现费拉不堪，还请及时指出。

------------

以下用边重和边权来区分限重大小和边权大小。

首先将边按边重从大到小加入，并用并查集维护连通块内的点权最大值，而这个最大值可能有很多个点，我们只记录一个点即可。

对于每个询问我们可以在对应的时刻找到其可以到达的最大点权，同时记录其中一个点以备后用。

这里显然是 $O(n\log n+(n+q)\alpha(n))$ 的。

------------

将每个询问挂在其对应的最大点权上，然后对于每种权值的所有点，我们在此称其为关键点，建虚树，用于处理询问。

首先我们要求出虚树上相邻点之间的边重和边权，对应到树上就是一段求到祖先的路径最大值，精细实现一下可以做到单次 $O(\log n)$。

由于虚树总大小是 $O(n)$ 的，而求一条边又是 $O(\log n)$，故此处复杂度并不超过 $O(n\log n)$。

------------

这里提一嘴怎么树剖精细实现单 $\log$，知道的请跳过，算是个小 trick。

一条到祖先的链会被拆成 $O(\log n)$ 条重链上连续的区间，更具体的，是 $O(\log n)$ 个重链前缀询问和 $1$ 个重链区间询问，而前缀询问可以预处理后 $O(1)$ 得到，故可以在单次 $O(\log n)$ 得到最大值。

------------

然后我们还是按边重从大到小将虚树边加入到虚树中，并再次用并查集维护连通块的最大边权。

**注意**：这里合并边权的时候要注意细节，如果只是某个 LCA 而没有接到关键点上应该让 LCA 先挂在关键点并查集的下面，后面有关键点通过这个 LCA 并进来的时候再把边权信息合并。

然后在对应时刻处理询问，不难发现，询问的最大边权就是连通块内的最大边权和**询问点接到连通块的那段路径上的最大边权**取 $\max$。

连通块的最大边权已经用并查集维护出来了，于是考虑另一个最大边权。

我们的目标转化为找到询问点到某时刻一个连通块的路径最大边权，发现**询问点到任意一个关键点的路径必定包含了所需的这条路径**（其实是个常用 trick 来着）。

（附：有一种再建一棵虚树并对其树剖然后仍然是 $O(\log)$ 能够精确地找到这段路径的办法，由于写了可能就上 7k 了，不再赘述）

于是我们随便 $O(\log)$ 询问到某个关键点的路径取个 $\max$ 即可，这里可以用我们一开始就用并查集找到的某一个点。

至此我们就可以完完全全在 $O((n+q)(\log(n+q)+\alpha(n)))$ 的复杂度内解决这道题。

这种离奇的实现方法常数应该不大（唯一的夙愿就是跑得比 LCT 快）。

---

