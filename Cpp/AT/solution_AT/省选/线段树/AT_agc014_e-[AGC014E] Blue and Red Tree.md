# [AGC014E] Blue and Red Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc014/tasks/agc014_e

$ N $ 頂点からなる木があり、頂点には $ 1 $ から $ N $ の番号がついています。 また、 $ N-1 $ 本の辺の内、$ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。

はじめ、各辺は青色に塗られています。 そこで、高橋君は以下の操作を $ N-1 $ 回行い、赤色の木に作り替えることにしました。

- 青色の辺のみからなるパスを一つ選び、そのパス上の辺を一つ取り除く。
- その後、初めに選んだパスの両端点間に赤色の辺を追加する。

最終的に、各 $ i $ に対し、頂点 $ c_i $ と頂点 $ d_i $ を結ぶ赤い辺が存在するような $ N $ 頂点の木に作り替えたいです。

これが可能であるかどうか判定してください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ a_i,b_i,c_i,d_i\ ≦\ N $
- $ a_i\ ≠\ b_i $
- $ c_i\ ≠\ d_i $
- 入力で与えられるグラフはどちらも木である。

### Sample Explanation 1

高橋君は以下の手順で目標の赤い木を作ることができます。 - まず、頂点 $ 1 $ と頂点 $ 3 $ を結ぶパスを選び、青い辺 $ 1-2 $ を削除する。そして、赤い辺 $ 1-3 $ を追加する。 - 次に、頂点 $ 2 $ と頂点 $ 3 $ を結ぶパスを選び、青い辺 $ 2-3 $ を削除する。そして、赤い辺 $ 2-3 $ を追加する。

## 样例 #1

### 输入

```
3
1 2
2 3
1 3
3 2```

### 输出

```
YES```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5
3 4
2 4
1 4
1 5```

### 输出

```
YES```

## 样例 #3

### 输入

```
6
1 2
3 5
4 6
1 6
5 1
5 3
1 4
2 6
4 3
5 6```

### 输出

```
NO```

# 题解

## 作者：AsunderSquall (赞：36)

**题意**  
给定一棵 $n$ 个节点的树，一开始所有边都是蓝色的。  
每次选择一条所有边都是蓝色的路径，删掉其中一条边，然后在路径的两个端点之间连一条红边。求最后能不能得到目标形态的红树。  

**题解**  



题解区几乎全部都是树剖的做法，唯一一篇[非树剖和 LCT 的题解](https://www.luogu.com.cn/blog/user34444/solution-at2377)感觉过于简略。  
提供一个代码简洁做法，看到的同学麻烦点个赞顶上去。  

~~像我这种懒人连线段树都懒得写会去写树剖？~~  

~~看到 Blue and Red Tree 我们应该想到[向北方的 Red and Blue Tree](https://www.luogu.com.cn/discuss/show/137272)。~~  

不过我们确实可以用红黑树（指 `set` 和 `map`） 来做这道题。（草）  

考虑倒推，最后一条被替换的边，一定本身就是红树上的边，然后这个时候这条边两边的联通块一定已经处理好了。    
再考虑这两边的联通块在形成可行的联通块之前，一定也有类似的重边进行了处理。  

然后我们考虑，不停进行这样的处理：如果发现有一条边既是红边又是蓝边，我们就将这条边连接的两个点进合并成一个点。如果最后能合并成 $1$ 个点说明可行。  

可能有点抽象，这里放一下样例 $2$ 的前三步过程。  
![](https://cdn.luogu.com.cn/upload/image_hosting/wnxol2s6.png)  
![](https://cdn.luogu.com.cn/upload/image_hosting/8die6yug.png)  
![](https://cdn.luogu.com.cn/upload/image_hosting/v76lpqwc.png)  

合并两个点的时候我们采用启发式合并来保证复杂度。具体来说维护每个点对应出去的边集的 `multiset`，然后逐个加入新边即可。  
然后我们用 `map` 来判重，避免重复合并边。  




**代码**  
```cpp
int n,l,r,cnt;
multiset<int> S[N];
map<pii,int> Map;
pii Q[N];
void add(int x,int y){if (x>y) swap(x,y);if (x==y) return;if (++Map[mp(x,y)]==2) Q[++r]=mp(x,y);S[x].insert(y),S[y].insert(x);}
signed main()
{
    rd(n);for (int i=1,x,y;i<=2*n-2;i++) rd(x),rd(y),add(x,y);
    while (cnt<n-1)
    {
        if (l>=r) {puts("NO");return 0;}
        l++;pii p=Q[l];if (!Map[p]) continue;
        int u=p.fi,v=p.se;
        if (S[u].size()<S[v].size()) swap(u,v);
        for (int x:S[v]) {Map[mp(min(x,v),max(x,v))]=0;S[x].erase(S[x].find(v));add(x,u);}
        S[v].clear();cnt++;
    }
    puts("YES");
}
```



---

## 作者：p_b_p_b (赞：11)

[$$\large \color{purple}My\;Blog$$](https://www.cnblogs.com/p-b-p-b/p/10355976.html)

-----------

## 思路

官方题解是倒推，这里提供一种正推的做法。

不知道你们是怎么想到倒推的……感觉正推更好想啊QwQ~~就是不好码~~

把每一条红边，将其转化为蓝树上的一条路径。为了连这条红边，需要保证这条路径仍然完整。

考虑连完之后要删掉的那条蓝边，显然它只能被当前连的红路径覆盖而没有被其他路径覆盖，否则就玩不下去了。

即：每次只能删掉一条被覆盖一次的蓝边。

有没有可能一条蓝边没有被覆盖过呢？显然是不可能的，因为每条蓝边最终都要删去，若没有覆盖过则无法删去。

那么做法就很显然了：树剖，线段树维护最小值和覆盖了这个区间的红边编号。每次找一个只被覆盖了一次的蓝边，删掉它（将它的值赋为$\infty$），也去除那条红边的影响。如果能做到最后就是合法，否则不合法。

然而我太久没写树剖，而且$n$和$n-1$总分不清，结果贡献了一页的评测记录……

而且在~~毒瘤的~~洛谷上选c++11交到AtCoder上就变成了c++14……对AtCoder不熟，各种奇怪的错误都来了。

代码巨丑，凑合着看吧QwQ

---------

## 代码

```cpp
#include<bits/stdc++.h>
namespace my_std{
    using namespace std;
    #define pii pair<int,int>
    #define fir first
    #define sec second
    #define MP make_pair
    #define rep(i,x,y) for (int i=(x);i<=(y);i++)
    #define drep(i,x,y) for (int i=(x);i>=(y);i--)
    #define go(x) for (int i=head[x];i;i=edge[i].nxt)
    #define sz 101010 
    typedef long long ll;
    template<typename T>
    inline void read(T& t)
    {
        t=0;char f=0,ch=getchar();
        double d=0.1;
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
        if(ch=='.')
        {
            ch=getchar();
            while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();
        }
        t=(f?-t:t);
    }
    template<typename T,typename... Args>
    inline void read(T& t,Args&... args){read(t); read(args...);}
//	void file()
//	{
//		#ifndef ONLINE_JUDGE
//		freopen("a.txt","r",stdin);
//		#endif
//	}
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;
//	clock_t t=clock();

int n;
struct hh{int t,nxt;}edge[sz<<1];
int head[sz],ecnt;
void make_edge(int f,int t)
{
    edge[++ecnt]=(hh){t,head[f]};
    head[f]=ecnt;
    edge[++ecnt]=(hh){f,head[t]};
    head[t]=ecnt;
}
int size[sz],son[sz],top[sz],fa[sz],dep[sz],dfn[sz],cnt=-1;
#define v edge[i].t
void dfs1(int x,int fa)
{
    dep[x]=dep[::fa[x]=fa]+1;size[x]=1;
    go(x) if (v!=fa)
    {
        dfs1(v,x);
        size[x]+=size[v];
        if (size[v]>size[son[x]]) son[x]=v;
    }
}
void dfs2(int x,int fa,int tp)
{
    top[x]=tp;dfn[x]=++cnt;
    if (son[x]) dfs2(son[x],x,tp);
    go(x) if (v!=fa&&v!=son[x]) dfs2(v,x,v);
}
#undef v

bool del[sz];
int F[sz],T[sz];
int mn[sz<<2],tag[sz<<2];
vector<int>tr[sz<<2];
#define ls k<<1
#define rs k<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
void Add(int k,int t){tag[k]+=t;mn[k]+=t;}
void pushdown(int k){int &t=tag[k]; if (!t) return; Add(ls,t); Add(rs,t); t=0; return;}
void pushup(int k){mn[k]=min(mn[ls],mn[rs]);}
void add(int k,int l,int r,int x,int y,int t)
{
    if (x<=l&&r<=y) return tr[k].push_back(t),Add(k,1);
    pushdown(k);
    int mid=(l+r)>>1;
    if (x<=mid) add(lson,x,y,t);
    if (y>mid) add(rson,x,y,t);
    pushup(k);
}
void change(int k,int l,int r,int x,int y,int s)
{
    if (x<=l&&r<=y) return Add(k,s);
    pushdown(k);
    int mid=(l+r)>>1;
    if (x<=mid) change(lson,x,y,s);
    if (y>mid) change(rson,x,y,s);
    pushup(k);
}
int K;
int getmn(int k,int l,int r)
{
    if (mn[k]>1) return -1; // -1 : don't have 1
    int ret;
    while (!tr[k].empty()&&del[tr[k].back()]) tr[k].pop_back();
    ret=tr[k].empty()?0:tr[k].back(); // 0 : don't know which edge
    if (l==r) return K=l,ret;
    pushdown(k);
    int mid=(l+r)>>1,cur;
    cur=getmn(lson); if (cur!=-1) { if (cur) return cur; if (ret) return ret; }
    cur=getmn(rson); if (cur!=-1) { if (cur) return cur; if (ret) return ret; }
    return ret;
}

void add(int x,int y,int t)
{
    while (top[x]!=top[y])
    {
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        add(1,1,n-1,dfn[top[x]],dfn[x],t);
        x=fa[top[x]];
    }
    if (dfn[x]>dfn[y]) swap(x,y);
    if (x!=y) add(1,1,n-1,dfn[x]+1,dfn[y],t);
}
void erase(int x,int y)
{
    while (top[x]!=top[y])
    {
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        change(1,1,n-1,dfn[top[x]],dfn[x],-1);
        x=fa[top[x]];
    }
    if (dfn[x]>dfn[y]) swap(x,y);
    if (x!=y) change(1,1,n-1,dfn[x]+1,dfn[y],-1);
}
void del_mn()
{
    if (mn[1]!=1) puts("NO"),exit(0);
    int e=getmn(1,1,n-1);
    del[e]=1;
    change(1,1,n-1,K,K,sz);
    erase(F[e],T[e]);
}


int main()
{
//	file();
    int x,y;
    scanf("%d",&n);
    rep(i,1,n-1) scanf("%d %d",&x,&y),make_edge(x,y);
    dfs1(1,0);dfs2(1,0,1);
    rep(i,1,n-1) scanf("%d %d",&x,&y),add(x,y,i),F[i]=x,T[i]=y;
    rep(i,1,n-1) del_mn();
    puts("YES");
//	cout<<1.0*(clock()-t)/CLOCKS_PER_SEC;
    return 0;
}
```

---

## 作者：小粉兔 (赞：6)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC014.html](https://www.cnblogs.com/PinkRabbit/p/AGC014.html)。

操作即是删去一条蓝边，然后加上一条红边以连通删去后留下的两个连通块。

此时加上的红边必须要满足其两端点都处在删蓝边前，那条蓝边所在的通过蓝边能到达的连通子图中。

考虑删去的第一条蓝边，从蓝树上考虑，显然那条被加入的红边两端点在蓝树上经过的路径覆盖了这条蓝边。

而且此后就不能再有红边对应的路径覆盖这条蓝边了，否则将违反上述限制。

那么做法就呼之欲出了：只需找到被覆盖次数恰好为 $1$ 的蓝边，以及覆盖它的路径，把路径经过的蓝边的被覆盖次数减去 $1$。

不断重复上述过程直到每条蓝边都被删去即可，如果过程中找不到合法的蓝边则无法成功变换成红树。

具体实现时使用树链剖分 + 线段树对每条蓝边维护它的被覆盖次数，以及将其覆盖的所有路径的编号的异或和。

时间复杂度为 $\mathcal O (N \log^2 N)$。

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>

const int Inf = 0x3f3f3f3f;
const int MN = 100005, MS = 1 << 18 | 7;

int N, ex[MN], ey[MN];
std::vector<int> G[MN];

int par[MN], dep[MN], siz[MN], pref[MN], top[MN], dfn[MN], dfc;
void DFS0(int u, int p) {
	dep[u] = dep[par[u] = p] + 1, siz[u] = 1;
	for (int v : G[u]) if (v != p) {
		DFS0(v, u);
		siz[u] += siz[v];
		if (siz[pref[u]] < siz[v]) pref[u] = v;
	}
}
void DFS1(int u, int t) {
	dfn[u] = ++dfc, top[u] = t;
	if (pref[u]) DFS1(pref[u], t);
	for (int v : G[u]) if (v != par[u] && v != pref[u]) DFS1(v, v);
}

#define li (i << 1)
#define ri (li | 1)
#define mid ((l + r) >> 1)
#define ls li, l, mid
#define rs ri, mid + 1, r
struct dat {
	int mn, v, i;
	dat() { mn = Inf; }
	dat(int z) { mn = v = 0, i = z; }
	dat(int x, int y, int z) { mn = x, v = y, i = z; }
} tr[MS];
struct tag {
	int a, w;
	tag() { a = w = 0; }
	tag(int x, int y) { a = x, w = y; }
} tg[MS];
inline dat operator + (dat a, dat b) { return a.mn < b.mn ? a : b; }
inline void operator += (tag &a, tag b) { a.a += b.a, a.w ^= b.w; }
inline void operator += (dat &a, tag b) { a.mn += b.a, a.v ^= b.w; }
inline void P(int i, tag x) { tr[i] += x, tg[i] += x; }
void Pushdown(int i) { if (tg[i].a || tg[i].w) P(li, tg[i]), P(ri, tg[i]), tg[i] = tag(); }
void Build(int i, int l, int r) {
	if (l == r) return tr[i] = dat(l), void();
	Build(ls), Build(rs);
	tr[i] = tr[li] + tr[ri];
}
void Mdf(int i, int l, int r, int a, int b, tag x) {
	if (r < a || b < l) return ;
	if (a <= l && r <= b) return P(i, x);
	Pushdown(i);
	Mdf(ls, a, b, x), Mdf(rs, a, b, x);
	tr[i] = tr[li] + tr[ri];
}

inline void Modify(int x, int y, tag z) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		Mdf(1, 1, N, dfn[top[x]], dfn[x], z);
		x = par[top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	if (x != y) Mdf(1, 1, N, dfn[x] + 1, dfn[y], z);
}

int main() {
	scanf("%d", &N);
	for (int i = 1, x, y; i < N; ++i) {
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	DFS0(1, 0), DFS1(1, 1);
	Build(1, 1, N);
	Mdf(1, 1, N, 1, 1, tag(Inf, 0));
	for (int i = 1; i < N; ++i) {
		scanf("%d%d", &ex[i], &ey[i]);
		Modify(ex[i], ey[i], tag(1, i));
	}
	for (int i = 1; i < N; ++i) {
		if (tr[1].mn != 1) return puts("NO"), 0;
		int j = tr[1].v;
		Mdf(1, 1, N, tr[1].i, tr[1].i, tag(Inf, 0));
		Modify(ex[j], ey[j], tag(-1, j));
	}
	puts("YES");
	return 0;
}
```

---

## 作者：i207M (赞：4)

我们观察修改树的操作：选择一条路径，删掉其中一条边，再连接两个端点。那么我们有一些显然的观察：

如果一条边在两棵树中都存在，那么我们肯定会在最后选择它的两个端点，且这样的边不影响判断。

我们把新树上的边对应原树的路径找出来，我们能够选择一条路径，当且仅当这条路径上存在一条可以删的边，只被这个路径覆盖，此时我们选择这个路径，删除这条边。

我们需要维护什么？每条边的覆盖次数：树剖解决。那么如何查覆盖这条边的路径的编号呢？我们当然可以暴力地用数据结构做，但是更好的是——**在链上打异或标记！当一条边只被覆盖一次，它的异或标记就是它的编号！**

好像实际做法很简单...：考虑在两棵树中都存在的边，它们不影响答案，我们把它们缩点。然后递归到子问题，继续进行，中间用并查集/启发式合并维护。

```cpp
#define N 100005
#define M N*4
#define ls (x<<1)
#define rs (x<<1|1)
const int rt=1,inf=1e9;
pii mn[M];
int laz[M],xt[M];
il void up(int x)
{
    mn[x]=min(mn[ls],mn[rs]);
}
il void give(int x,int v1,int v2)
{
    mn[x].fi+=v1,laz[x]+=v1,xt[x]^=v2;
}
il void down(int x)
{
    if(laz[x]||xt[x])
    {
        give(ls,laz[x],xt[x]),give(rs,laz[x],xt[x]);
        laz[x]=xt[x]=0;
    }
}
bool zer[N];
void build(int x,int l,int r)
{
    if(l==r)
    {
        if(zer[l]) mn[x]=mp(0,l);
        else mn[x]=mp(inf,l);
        return;
    }
    gm; build(ls,l,mid),build(rs,mid+1,r);
    up(x);
}
void upd(int x,int l,int r,int ql,int qr,int v1,int v2)
{
    if(ql<=l&&r<=qr) return give(x,v1,v2);
    gm; down(x);
    if(ql<=mid) upd(ls,l,mid,ql,qr,v1,v2);
    if(qr>mid) upd(rs,mid+1,r,ql,qr,v1,v2);
    up(x);
}
int ask(int x,int l,int r,int p)
{
    if(l==r) return xt[x];
    gm; down(x);
    if(p<=mid) return ask(ls,l,mid,p);
    else return ask(rs,mid+1,r,p);
}
void upd2(int x,int l,int r,int p)
{
    if(l==r) {mn[x]=mp(inf,l); return;}
    gm; down(x);
    if(p<=mid) upd2(ls,l,mid,p);
    else upd2(rs,mid+1,r,p);
    up(x);
}
int n;
vector<int> E[N];
int dfn[N],dk,sz[N],hsn[N],fa[N],top[N],dep[N];
void dfs(int x,int _fa)
{
    sz[x]=1,fa[x]=_fa,dep[x]=dep[_fa]+1;
    for(solid v:E[x])
    {
        if(v==_fa) continue;
        dfs(v,x); sz[x]+=sz[v];
        if(sz[v]>sz[hsn[x]]) hsn[x]=v;
    }
}
void efs(int x,int _tp)
{
    dfn[x]=++dk,top[x]=_tp;
    if(hsn[x]) efs(hsn[x],_tp);
    else return;
    for(solid v:E[x])
    {
        if(v==fa[x]||v==hsn[x]) continue;
        efs(v,v);
    }
}
il void lineupd(int x,int y,int v1,int v2)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        upd(rt,1,n,dfn[top[x]],dfn[x],v1,v2);
        x=fa[top[x]];
    }
    if(x==y) return;
    if(dfn[x]>dfn[y]) swap(x,y);
    upd(rt,1,n,dfn[x]+1,dfn[y],v1,v2);
}
set< pii > hve,nwe;
int ea[N],eb[N],cnt;
signed main()
{
#ifdef M207
    freopen("in.in","r",stdin);
    // freopen("ot.out","w",stdout);
#endif
    in(n);
    for(ri i=1,a,b; i<n; ++i)
    {
        in(a,b);
        E[a].pb(b),E[b].pb(a);
        if(a>b) swap(a,b);
        hve.insert(mp(a,b));
    }
    for(ri i=1; i<n; ++i)
    {
        ++cnt,in(ea[cnt],eb[cnt]);
        if(ea[cnt]>eb[cnt]) swap(ea[cnt],eb[cnt]);
        if(hve.count(mp(ea[cnt],eb[cnt]))) hve.erase(mp(ea[cnt],eb[cnt])),--cnt;
    }
    dfs(1,0);
    efs(1,1);
    for(ri i=2; i<=n; ++i)
    {
        int a=i,b=fa[i];
        if(a>b) swap(a,b);
        if(hve.count(mp(a,b))) zer[dfn[i]]=1;
    }
    build(rt,1,n);
    for(ri i=1; i<=cnt; ++i) lineupd(ea[i],eb[i],1,i);
    int del=0;
    while(1)
    {
        pii tmp=mn[rt];
        if(tmp.fi>1) break;
        if(tmp.fi==0)
        {
            upd2(rt,1,n,tmp.se);
            continue;
        }
        int t=ask(rt,1,n,tmp.se);
        ++del;
        lineupd(ea[t],eb[t],-1,t);
    }
    puts(del==cnt?"YES":"NO");
    return 0;
}
```


---

## 作者：Karry5307 (赞：4)

### 题意

有一棵 $n$ 个节点的树和 $n-1$ 条路径，一开始树上的边全是蓝边。每一次可以选择一条全是蓝边的路径，将其中的一条替换为红边。问有没有方法可以将树变成全是红边的数。

$\texttt{Data Range:}2\leq n\leq 10^5$

### 题解

这题比较简单，但是代码写起来比较恶心，感觉别的题解的代码写的比较奇葩。

将所有路径看成对边的覆盖，那么每一次肯定是选取只被一条路径覆盖的边去操作，这样才不会对别的路径造成影响。

所以可以先路径覆盖，每次查询所有边中有没有被覆盖次数为 $1$ 的，如果没有就不行，有的话就暴力对这条边进行操作。

这些操作都可以用树剖维护，具体的话就是将用 $u$ 的权值代表边 $(u,fa_u)$ 的覆盖次数，然后维护一下所有边被覆盖次数的最小值以及最小值出现的位置。同时还可以维护覆盖了这条边的所有路径编号的异或和，这样当这条边只被一条路径覆盖的时候可以方便的查询被哪条路径覆盖到了，于是这题就完了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51,inf=0x3f3f3f3f;
struct Edge{
	ll to,prev;
};
struct SegmentTree{
	ll l,r,xv,mn,p,tag,tag2;
};
Edge ed[MAXN<<1];
SegmentTree tree[MAXN<<2];
ll n,from,to,tot,totd,c;
ll last[MAXN],fa[MAXN],depth[MAXN],sz[MAXN],hv[MAXN],dfn[MAXN];
ll rdfn[MAXN],top[MAXN],u[MAXN],v[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void addEdge(ll from,ll to)
{
	ed[++tot].prev=last[from];
	ed[tot].to=to;
	last[from]=tot;
}
inline void dfs(ll node,ll f)
{
	ll mx=-1;
	depth[node]=depth[fa[node]=f]+1,sz[node]=1;
	for(register int i=last[node];i;i=ed[i].prev)
	{
		if(ed[i].to!=f)
		{
			dfs(ed[i].to,node),sz[node]+=sz[ed[i].to];
			sz[ed[i].to]>mx?mx=sz[hv[node]=ed[i].to]:1;
		}
	}
}
inline void dfs2(ll node,ll link)
{
	ll to;
	rdfn[dfn[node]=++totd]=node,top[node]=link;
	if(!hv[node])
	{
		return;
	}
	dfs2(hv[node],link);
	for(register int i=last[node];i;i=ed[i].prev)
	{
		(to=ed[i].to)!=fa[node]&&to!=hv[node]?dfs2(to,to):(void)1;
	}
}
#define ls node<<1
#define rs (node<<1)|1
inline void update(ll node)
{
	tree[node].mn=min(tree[ls].mn,tree[rs].mn);
	tree[node].p=tree[ls].mn<tree[rs].mn?tree[ls].p:tree[rs].p;
	tree[node].xv=tree[ls].mn<tree[rs].mn?tree[ls].xv:tree[rs].xv;
}
inline void create(ll l,ll r,ll node)
{
	tree[node]=(SegmentTree){l,r,0,0,0,0,0};
	if(l==r)
	{
		return (void)(tree[node].p=l);
	}
	ll mid=(l+r)>>1;
	create(l,mid,ls),create(mid+1,r,rs),update(node);
}
inline void spread(ll node)
{
	if(tree[node].tag)
	{
		ll tag=tree[node].tag;
		tree[ls].mn+=tag,tree[rs].mn+=tag,tree[ls].tag+=tag,tree[rs].tag+=tag;
		tree[node].tag=0;
	}
	if(tree[node].tag2)
	{
		ll tag=tree[node].tag2;
		tree[ls].xv^=tag,tree[rs].xv^=tag;
		tree[ls].tag2^=tag,tree[rs].tag2^=tag,tree[node].tag2=0;
	}
}
inline void add(ll l,ll r,ll val,ll c,ll node)
{
	if(l<=tree[node].l&&r>=tree[node].r)
	{
		tree[node].xv^=c,tree[node].tag2^=c;
		return (void)(tree[node].mn+=val,tree[node].tag+=val);
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	spread(node);
	l<=mid?add(l,r,val,c,ls):(void)1,r>mid?add(l,r,val,c,rs):(void)1;
	update(node);
}
inline void add(ll x,ll y,ll val,ll c)
{
	while(top[x]!=top[y])
	{
		depth[top[x]]<depth[top[y]]?swap(x,y):(void)1;
		add(dfn[top[x]],dfn[x],val,c,1),x=fa[top[x]];
	}
	depth[x]>depth[y]?swap(x,y):(void)1;
	x!=y?add(dfn[x]+1,dfn[y],val,c,1):(void)1;
}
int main()
{
	n=read();
	for(register int i=0;i<n-1;i++)
	{
		from=read(),to=read(),addEdge(from,to),addEdge(to,from);
	}
	dfs(1,0),dfs2(1,1),create(1,n,1),add(1,1,inf,0,1);
	for(register int i=1;i<n;i++)
	{
		u[i]=read(),v[i]=read(),add(u[i],v[i],1,i);
	}
	for(register int i=1;i<n;i++)
	{
		if(tree[1].mn!=1)
		{
			return puts("NO"),0;
		}
		c=tree[1].xv,add(tree[1].p,tree[1].p,inf,0,1),add(u[c],v[c],-1,c);
	}
	puts("YES");
}
```

---

## 作者：大菜鸡fks (赞：4)

首先可以发现最终状态替换的红边和蓝边一定是重边。把这条边两端的联通块看成一个点。

往回推，要形成这两个点，必须也要有类似的重边。

这样就可以得到一种做法。每次把重边两端的放入队列，并把边集合并（启发式合并），把这两个联通块合并

再把重边放入，直至更新完成

```cpp
#include<cstdio>
#include<set>
#include<map>
#include<algorithm>
#define mp(x,y) make_pair(x,y)
#define pi pair<int,int>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=1e5+5;
set<int >se[N];
map<pi,int> ma;
pi q[N];
int n,h,t,fa[N];
inline int getfa(int x){
	return (fa[x]==x)?x:fa[x]=getfa(fa[x]);
}
inline void init(){
	n=read();
	for (int i=1;i<=n*2-2;i++){
		int u=read(),v=read();
		se[u].insert(v); se[v].insert(u);
		ma[mp(u,v)]++; ma[mp(v,u)]++;
		if (ma[mp(u,v)]==2) q[++t]=make_pair(u,v);
	}
}
inline void solve(){
	for (int i=1;i<=n;i++) fa[i]=i;
	set<int >::iterator it;
	while (h<t){
		int u=q[++h].first,v=q[h].second;
		u=getfa(u); v=getfa(v);
		se[u].erase(v); se[v].erase(u);
		if (se[u].size()<se[v].size()) swap(u,v);
		for (it=se[v].begin();it!=se[v].end();++it){
			int to=(*it);
			ma[mp(to,v)]=ma[mp(v,to)]=0;
			se[to].erase(v); se[to].insert(u);
			ma[mp(to,u)]++; ma[mp(u,to)]++;
			if (ma[mp(to,u)]==2) q[++t]=make_pair(to,u);
			se[u].insert(to);
		}
		fa[v]=u;
		se[v].clear();
	}
	int s=0;
	for (int i=1;i<=n;i++) s+=fa[i]==i;
	if (s==1) puts("YES"); else puts("NO");
}
int main(){
	init(); solve();
	return 0;
}
```

---

## 作者：shinkuu (赞：3)

居然自己想出了 AGC E。

首先考虑删边再加红边的本质是什么。容易发现，如果一条目标树上的边当前还没有被加上，且这条边所连两点在原树上的路径被切断，则此时一定无解。因为不管怎么加删边，这都是一棵树，而此时两点路径上一定有红边。

所以，我们就可以得到此时可以新增一条边 $(u,v)$ 的条件：路径上存在一条边，没有一条没有新增过的目标树上的边 $(u',v')$，使得原树上 $(u',v')$ 的路径不经过改变。容易发现，这等同于在原树上把所有 $(u,v)$ 路径上边的边权 $+1$，查询路径上有没有边权为 $1$ 的边。简单树剖维护即可。

作者在写的时候降智了，找到对应 $(u,v)$ 时没有想到维护编号和，于是在 SGT 上每个点用了个 set 维护区间内有的编号，时空复杂度 $O(n\log^3n)$。其实可以 $O(n\log^2n)$。但是常数小，无所谓了（bushi）。

code：

```cpp
int n,m;
int dep[N],fa[N],siz[N],son[N];
int cur,top[N],dfn[N];
int tr[N<<2],tag[N<<2];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
pii d[N];
set<int> st[N<<2],E;
inline void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
void dfs1(int u,int f){
	dep[u]=dep[f]+1;
	fa[u]=f;
	siz[u]=1;
	go(i,u){
		int v=e[i].to;
		if(v==f)
			continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
			son[u]=v;
	}
}
void dfs2(int u,int t){
	top[u]=t;
	dfn[u]=++cur;
	if(!son[u])
		return;
	dfs2(son[u],t);
	go(i,u){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])
			continue;
		dfs2(v,v);
	}
}
inline void pushup(int o){
	tr[o]=min(tr[o<<1],tr[o<<1|1]);
}
inline void reset(int l,int r,int o,int k){
	tr[o]+=k;
	tag[o]+=k;
}
inline void pushdown(int l,int r,int o){
	int mid=(l+r)>>1;
	reset(l,mid,o<<1,tag[o]);
	reset(mid+1,r,o<<1|1,tag[o]);
	tag[o]=0;
}
void update(int l,int r,int o,int x,int y,int k,int op){
	if(l>=x&&r<=y){
		if(op){
			st[o].insert(k);
			reset(l,r,o,1);
		}else{
			st[o].erase(k);
			reset(l,r,o,-1);
		}
		return;
	}
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(x<=mid)
		update(l,mid,o<<1,x,y,k,op);
	if(y>mid)
		update(mid+1,r,o<<1|1,x,y,k,op);
	pushup(o);
}
int query(int l,int r,int o){
	if(st[o].size())
		return *st[o].begin();
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(tr[o<<1]<tr[o<<1|1])
		return query(l,mid,o<<1);
	return query(mid+1,r,o<<1|1);
}
void change(int l,int r,int o){
	if(l==r){
		tr[o]=inf;
		return;
	}
	change(l,(l+r)>>1,o<<1);
	pushup(o);
}
void work(int l,int r,int o){
	if(l==r){
		tr[o]=inf;
		return;
	}
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(tr[o<<1]<tr[o<<1|1])
		work(l,mid,o<<1);
	else 
		work(mid+1,r,o<<1|1);
	pushup(o);
}
void modify(int u,int v,int k,int op){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		update(1,n,1,dfn[top[u]],dfn[u],k,op);
		u=fa[top[u]];
	}
	if(dfn[u]>dfn[v])
		swap(u,v);
	if(dfn[u]<dfn[v])
		update(1,n,1,dfn[u]+1,dfn[v],k,op);
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	rep(i,1,n-1){
		scanf("%d%d",&d[i].fi,&d[i].se);
		modify(d[i].fi,d[i].se,i,1);
	}
	change(1,n,1);
	rep(i,1,n-1){
		E.clear();
		if(tr[1]>1){
			puts("NO");
			return;
		}
		int p=query(1,n,1);
		modify(d[p].fi,d[p].se,p,0);
		while(!tr[1])
			work(1,n,1);
	}
	puts("YES");
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：kczno1 (赞：2)

第一次看到这么水的$E$，我的方法跟题解不同。  
把原树建出来，把目标树变成原树上的$n-1$条路径。  
因为加边的时候，那条路径上的边必须都还在，所以只用每次删掉只被一条路径覆盖的边，然后删掉这个路径，看看能否重复$n-1$次操作即可。  
用轻重链剖分+线段树实现，时间$O(n\log^{2}_{}n)$。  
```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=l;i<=r;++i)
const int N=1e5+5,T=N*30;
int nex[T],pre[T],tot,have[N],qx[N],qy[N];
vector<int>lk[N];
int n;
int dfn[N],fa[N],deep[N],sz[N],son[N],top[N];
namespace TREE
{
int tot;
namespace DFS1
{
void dfs(int x,int fr)
{
	fa[x]=fr;
	deep[x]=deep[fr]+1;
	sz[x]=1;
	for(auto y:lk[x])
	if(y!=fr)
	{
		dfs(y,x);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])son[x]=y;
	}
}
};
namespace DFS2
{
void dfs(int x,int ntop)
{
	top[x]=ntop;
	dfn[x]=++tot;
	if(!son[x])return ;
	dfs(son[x],ntop);
	for(auto y:lk[x])
	if(y!=son[x]&&y!=fa[x])dfs(y,y);
}
};
void init()
{
	DFS1::dfs(1,0);
	tot=-1;
	DFS2::dfs(1,1);
}
};
int mn[N*4],ad[N*4];
int ql,qr;
#define in (ql<=l&&qr>=r)
#define out (ql>r||qr<l)
#define mid ((l+r)/2)
#define cl (k*2)
#define cr (cl+1)
namespace SEG
{
int n;
void up(int k)
{
	mn[k]=min(mn[cl],mn[cr])+ad[k];
}
namespace ADD
{
void dfs(int k,int l,int r)
{
	if(in)
	{
		++tot;
		pre[nex[tot]=nex[k]]=tot;
		pre[tot]=k;
		nex[k]=tot;
		
		++ad[k];++mn[k];
		return ;
	}
	if(out)return ;
	dfs(cl,l,mid);
	dfs(cr,mid+1,r);
	up(k);
}
};
namespace DEL
{
void dfs(int k,int l,int r)
{
	if(in)
	{
		--ad[k];--mn[k];
		return ;
	}
	if(out)return ;
	dfs(cl,l,mid);
	dfs(cr,mid+1,r);
	up(k);
}
};
void add(int l,int r)
{
	ql=l;qr=r;
	ADD::dfs(1,1,n);
}
void del(int l,int r)
{
	ql=l;qr=r;
	DEL::dfs(1,1,n);
}
int get_mn()
{
	int k=1,l=1,r=n;
	while(l!=r)
	if(mn[cl]<mn[cr])
	{
		k=cl;
		r=mid;
	}
	else
	{
		k=cr;
		l=mid+1;
	}
	return k;
}
};
#define fx top[x]
#define fy top[y]
void add(int x,int y)
{
	while(fx!=fy)
	{
		if(deep[fx]<deep[fy])swap(x,y);
		SEG::add(dfn[fx],dfn[x]);
		x=fa[fx];
	}
	if(dfn[x]>dfn[y])swap(x,y);
	SEG::add(dfn[x]+1,dfn[y]);
}
void del(int x,int y)
{
	while(fx!=fy)
	{
		if(deep[fx]<deep[fy])swap(x,y);
		SEG::del(dfn[fx],dfn[x]);
		x=fa[fx];
	}
	if(dfn[x]>dfn[y])swap(x,y);
	SEG::del(dfn[x]+1,dfn[y]);
}
#undef fx
#undef fy
void del_mn()
{
	int k=SEG::get_mn();
	mn[k]=N;
	int i=nex[k];
	while(k>>=1)
	{
		SEG::up(k);
		if(!i)i=nex[k];
	}
	i=lower_bound(have+1,have+n,i)-have;
//	cerr<<i<<endl;
	rep(x,have[i-1]+1,have[i])
	{
		pre[nex[x]]=pre[x];
		nex[pre[x]]=nex[x];
	}
	del(qx[i],qy[i]);
}

int main()
{
	freopen("1.in","r",stdin);freopen("1.out","w",stdout);
	cin>>n;SEG::n=n-1;
	rep(i,1,n-1)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		lk[x].push_back(y);lk[y].push_back(x);
	}
	TREE::init();
	have[0]=tot=N*4;
	rep(i,1,n-1)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		have[i]=tot;
		qx[i]=x;qy[i]=y;
	}
	rep(tmp,1,n-1)
	{
		if(mn[1]!=1)
		{
			puts("NO");
			exit(0);
		}
		del_mn();
	}
	puts("YES");
}
```

---

## 作者：约瑟夫用脑玩 (赞：1)

感觉好多题解都是 $\log^2{n}$ 的算法，这里提供一种 $\log{n}$ 还特别短的小清新算法。

做法解释不多赘述，~~感觉十分显然~~，其他题解都有详细说明，这里仅简要提一下做法：

- 对于每条红边对应到蓝树上的一条路径，将其路径覆盖次数 +1。

  每次选择一条只被覆盖一次的蓝边，将覆盖它的红边的贡献消去，如果找不到这样的蓝边说明或是在消去某条红边时将其他蓝边减到 0 了则无解。
  
  这里找覆盖此蓝边的红边可以用异或简单实现。

解决这个问题有显然的树剖套线段树的 $\log^2{n}$ 做法，毒瘤且对接下来的算法没有帮助，不作考虑。

对于这种近乎裸的路径问题，可以很显然的想到 LCT，注意到除了一开始就只被覆盖了一次的蓝边，其他的蓝边都是在消去红边贡献时出现的。

设当前消去红边对应路径为 $l$，那么我们可以不断的提取出 $l$ 对应路径上覆盖次数为 1 的蓝边，将这条蓝边对应红边贡献消去后其覆盖次数就变为了 0，就可以继续在 $l$ 上提新的蓝边了。

对于每次消去红边对应路径贡献时将蓝边提完，这样就可以保证算法的正确性了。

如果这样做有亿些小细节：

- 首先是你要用 LCT 找覆盖次数为 1 的边，如果直接用最小值会找到覆盖次数 0 的边，所以要注意消去红边贡献时顺便将当前蓝边清为 inf，那么剩下的就是 LCT 板子了。

- 然后是你在消去 $l$ 这条路径后可能提出一些新的蓝边，但提一条蓝边又要消一次其红边对应路径，于是是个递归的过程，写个函数还是不难实现。

- 最后还要记得判无解。

这样已经不失为一种思路简单，代码不长(一个 LCT 板子总比树剖套线段树两个数据结构短吧)，复杂度还优秀的算法了，但我~~由于懒~~将其**进一步简化了**一下。

利用 LCT 中是 Splay 这种优秀的工具，我们一次消去红边贡献时暴力 DFS 下去找 Splay 中，也就是这条路径上的蓝边。

找到一个 Splay 一个或是找完再把它们都 Splay 上来都行，这样也就利用了 Splay 的均摊复杂度暴力地取出了所有蓝边并且时间复杂度还是正确的 $O(n\log{n})$，因为每条蓝边只会被找一次。

这样就没有什么花里胡哨的递归了，就是一个暴力 LCT(+Splay里面自带) 板子模拟最初的算法流程，这样做也就常数略大而已，但敌不过它代码简单且理论复杂度上的优势。

由于笔者毒瘤的码风代码就不放了，但这种写法是真的又短又好写。

---

## 作者：Felix72 (赞：0)

这铜题怎么比红题还简单（小声）

但是可以一题两吃，来提供两种思路。

### 顺向

出现一条红边意味着要删除一条蓝边，那么红边和蓝边之间构成映射。考虑可能的第一条红边，其对应的蓝边一定不被其他红边对应的路径覆盖，也就是其被覆盖次数恰为 $1$。删除这条红边和蓝边，余下一个森林，我们发现这还是原问题。

因此可以如此反复删边，用数据结构维护被覆盖次数最小的蓝色边，每次检验其被覆盖次数是否为 $1$，然后删掉对应的红边并去除影响即可。顺利执行完 $n - 1$ 次删除即有解。

重链剖分可以做到 $O(n \log^2n)$。

### 逆向

删一条蓝色边后效性大的没边了，但是加一条蓝色边后效性不怎么大，因此考虑从红色树往蓝色树回溯的过程。

这个过程如下：

> 对一棵初始为红色的树重复执行 $n - 1$ 次操作：
>
> - 找两个点 $x, y$，要求存在 $x', y'$ 满足 $x', y'$ 之间有红色边，且 $x$ 和 $x'$ 由蓝色边连通，$y$ 和 $y'$ 由蓝色边连通。在 $x, y$ 之间添加一条蓝色边。

对连通性的要求比较烦，考虑直接把连通块视作元素，则过程如下：

> 你有若干个连通块，有两类边连接着某些连通块，重复以下操作知道剩下一个连通块：
>
> - 选择两个连通块 $x,y$ 满足他们之间同时存在红色和蓝色的边。合并 $x, y$。

容易看出这是一个贪心过程，即能合并就合并。用你喜欢的数据结构维护连通块即可。

码量比较小的写法是 set + map，我使用了 dsu + sgt，导致代码较长，但是复杂度是一样的。

代码（逆向解法）：

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 100010;

int n;
struct Dsu
{
	int prt[N];
	inline void init(int n) {for(int i = 1; i <= n; ++i) prt[i] = i;}
	inline int find(int x) {return ((prt[x] == x) ? x : (prt[x] = find(prt[x])));}
	inline void merge(int x, int y)
	{
		x = find(x), y = find(y);
		if(x != y) prt[x] = y;
	}
}; Dsu dsu;

int idx;
struct SGT
{
	int ls, rs; bool tag[2], data;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	#define tag(x) tree[x].tag
	#define data(x) tree[x].data
} tree[N * 256];
inline void pushup(int now) {data(now) = (data(ls(now)) || data(rs(now)));}
inline void insert(int &now, int l, int r, int pos, int type, bool state)
{
	if(!now) now = ++idx;
	if(l == r)
	{
		tag(now)[type] = state;
		data(now) = (tag(now)[0] && tag(now)[1]); return ;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) insert(ls(now), l, mid, pos, type, state);
	else insert(rs(now), mid + 1, r, pos, type, state);
	pushup(now);
}
inline void merge(int &px, int py, int l, int r)
{
	if(!px || !py) {px += py; return ;}
	if(l == r)
	{
		for(int type = 0; type <= 1; ++type) tag(px)[type] |= tag(py)[type];
		data(px) = (tag(px)[0] && tag(px)[1]);
		return ;
	}
	int mid = (l + r) >> 1;
	merge(ls(px), ls(py), l, mid);
	merge(rs(px), rs(py), mid + 1, r);
	pushup(px);
}
inline int get(int now, int l, int r)
{
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(data(ls(now))) return get(ls(now), l, mid);
	else return get(rs(now), mid + 1, r);
}
inline void debug(int now, int l, int r, int type)
{
	if(l == 1 && r == n) {cerr << "type " << type << " : ";}
	if(l == r) {if(tag(now)[type]) cerr << l << " "; return ;}
	int mid = (l + r) >> 1;
	debug(ls(now), l, mid, type); debug(rs(now), mid + 1, r, type);
}

queue < int > que; bool que_state[N];
inline void in_queue(int x)
{
	if(que_state[x]) return ;
	que_state[x] = true; que.push(x);
}
inline int pop_queue()
{
	int x = que.front();
	que_state[x] = false; que.pop();
	return x;
}

struct Connected_Blocks
{
	int rt; vector < int > con[2];
}; Connected_Blocks block[N]; int merge_cnt;
inline void block_refresh(int id) {if(data(block[id].rt)) in_queue(id);}
inline void block_merge(int px, int py)
{
	if(px == py)
	{
		int id = get(block[px].rt, 1, n);
		for(int type = 0; type <= 1; ++type) insert(block[px].rt, 1, n, id, type, false);
		block_refresh(px); return ;
	}
//	cerr << "block_merge " << px << " " << py << '\n';
	++merge_cnt;
	if(block[px].con[0].size() + block[px].con[1].size() < block[py].con[0].size() + block[py].con[1].size()) swap(px, py);
	// 把 py 连接的边改为 px
	for(int type = 0; type <= 1; ++type)
	{
		for(int to : block[py].con[type])
		{
			if(dsu.find(to) == px) continue;
			block[px].con[type].push_back(to);
			
			to = dsu.find(to);
			insert(block[to].rt, 1, n, py, type, false);
			insert(block[to].rt, 1, n, px, type, true);
			block_refresh(to);
		}
	}
	// 互相删除 
	for(int type = 0; type <= 1; ++type)
	{
		insert(block[px].rt, 1, n, py, type, false);
		insert(block[py].rt, 1, n, px, type, false);
	}
	// 合并 px,py 出边，并查集上合并 
	merge(block[px].rt, block[py].rt, 1, n);
	dsu.merge(py, px);
	// 刷新 
	block_refresh(px);
//	debug(block[px].rt, 1, n, 0); cerr << '\n';
//	debug(block[px].rt, 1, n, 1); cerr << '\n';
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	dsu.init(n);
	for(int type = 0; type <= 1; ++type)
	{
		for(int i = 1, x, y; i < n; ++i)
		{
			cin >> x >> y;
			block[x].con[type].push_back(y);
			block[y].con[type].push_back(x);
			insert(block[x].rt, 1, n, y, type, true);
			insert(block[y].rt, 1, n, x, type, true);
		}
	}
	for(int i = 1; i <= n; ++i) block_refresh(i);
	while(!que.empty())
	{
		int id = pop_queue(); id = dsu.find(id);
		if(!data(block[id].rt)) continue;
		int to = get(block[id].rt, 1, n); to = dsu.find(to);
		block_merge(id, to);
	}
	if(merge_cnt == n - 1) cout << "YES" << '\n';
	else cout << "NO" << '\n';
	return 0;
}
/*

*/
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc014_e)

**题目大意**

> 给定一棵 $n$ 个点的树，每次选择一条边割掉，然后在两端连通块中选一个点，在第二棵树上连起来，求能否在第二棵树上构造出目标树。
>
> 数据范围：$n\le 10^5$。

**思路分析**

考虑第一条删除的边 $e$，此后两个连通块中不会再连边，因此第一次连的边必须是唯一跨越 $e$ 的边。

因此一个朴素的做法就是把目标树上的边看成路径，覆盖在第一棵树上，每次取出被覆盖次数恰好 $=1$ 的一条边割断，连接覆盖这条边的路径。

遇到多个覆盖次数 $=1$ 的边时，可以任选一条，用树剖维护该过程即可。

时间复杂度 $\mathcal O(n\log^2n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5,inf=1e9;
int n,rk[MAXN],cov[MAXN];
struct ZkyGt1 {
	static const int N=1<<17;
	int tr[N<<1];
	void psu(int p) {
		int k=min(tr[p<<1],tr[p<<1|1]);
		tr[p]+=k,tr[p<<1]-=k,tr[p<<1|1]-=k;
	}
	void init() {
		for(int i=0;i<N;++i) tr[i+N]=(1<i&&i<=n?cov[rk[i]]:inf);
		for(int i=N-1;i;--i) psu(i);
	}
	void add(int l,int r,int x) {
		for(l+=N-1,r+=N+1;l^r^1;l>>=1,r>>=1) {
			if(~l&1) tr[l^1]+=x;
			if(r&1) tr[r^1]+=x;
			psu(l>>1),psu(r>>1);
		}
		for(;l>1;l>>=1) psu(l>>1);
	}
	int qry() {
		int p=1;
		while(p<N) {
			p<<=1;
			if(tr[p]>tr[p^1]) p^=1;
		}
		tr[p]=inf;
		for(int x=p;x>1;x>>=1) psu(x>>1);
		return rk[p-N];
	}
}	T;
struct FenwickTree {
	int tr[MAXN],s;
	void add(int x,int v) { for(;x<=n;x+=x&-x) tr[x]^=v; }
	int qry(int x) { for(s=0;x;x&=x-1) s^=tr[x]; return s; }
}	Q;
int st[MAXN],ed[MAXN],siz[MAXN],dep[MAXN],fa[MAXN],hson[MAXN],top[MAXN],dfn[MAXN],dcnt;
vector <int> G[MAXN];
void dfs0(int u,int fz) {
	siz[u]=1,dep[u]=dep[fz]+1,fa[u]=fz;
	for(int v:G[u]) if(v^fz) {
		dfs0(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[hson[u]]) hson[u]=v;
	}
}
void dfs1(int u,int rt) {
	top[u]=rt,dfn[u]=++dcnt,rk[dcnt]=u;
	if(hson[u]) dfs1(hson[u],rt);
	for(int v:G[u]) if(v!=fa[u]&&v!=hson[u]) dfs1(v,v);
}
int LCA(int u,int v) {
	while(top[u]^top[v]) {
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}
void add(int u,int v,int k) {
	while(top[u]^top[v]) {
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		T.add(dfn[top[u]],dfn[u],k),u=fa[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	if(u^v) T.add(dfn[v]+1,dfn[u],k);
}
void dfs3(int u) {
	for(int v:G[u]) if(v^fa[u]) dfs3(v),cov[u]+=cov[v];
}
signed main() {
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1,u,v;i<n;++i) cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
	dfs0(1,0),dfs1(1,1);
	for(int i=1;i<n;++i) {
		cin>>st[i]>>ed[i];
		Q.add(dfn[st[i]],i),Q.add(dfn[ed[i]],i);
		++cov[st[i]],++cov[ed[i]];
		cov[LCA(st[i],ed[i])]-=2;
	}
	dfs3(1),T.init();
	for(int o=1;o<n;++o) {
		if(T.tr[1]!=1) return puts("NO"),0;
		int x=T.qry(),i=Q.qry(dfn[x]+siz[x]-1)^Q.qry(dfn[x]-1);
		add(st[i],ed[i],-1);
		Q.add(dfn[st[i]],i),Q.add(dfn[ed[i]],i);
	}
	puts("YES");
	return 0;
}
```

---

## 作者：Kinandra (赞：0)

标签:树链剖分.

我们发现在原树(称为**蓝树**)上删除一条蓝边, 然后在目标树(称为**红树**)上删除一条红边的操作与原操作是等价的.

我们需要规划好每条红边的删除顺序, 和**每条红边删除时**对应删除的是那条蓝边. 发现如果**蓝树**上某条边被唯一一条未被删除的红边覆盖, 那么我们可以删除这条蓝边和其对应的红边. 若**蓝树**上每条边都被至少两条未被添加的红边覆盖, 删除任意一条蓝边只能删除覆盖其的一条红边, 并且覆盖其的另一条红边无法被删除, 所以无解.

于是可以用树链剖分来维护每条蓝边被多少条红边覆盖, 每次找到一条只被覆盖一次的蓝边, 删除其和唯一覆盖其的红边, 就可以解决了. 但是我们知道一条蓝边只被覆盖一次时, 应该如何维护覆盖其的红边的编号呢?.

一种解决方法是**异或和**, 我们利用树链剖分对于**每一条蓝边**维护**覆盖其的红边编号的异或和**, 则当其只被一条红边覆盖时, 异或和即为覆盖其红边的编号(显然用**和**或**模大素数意义下的积**也是可以的, 不过异或和在时间常数方面上有较大优势).

时间复杂度$\mathcal O(n\log n)$

```cpp
#include <bits/stdc++.h>
#define root 1, n, 1, pre[top[u]], pre[u]
#define ls l, mid, k << 1
#define rs mid + 1, r, k << 1 | 1
#define L k << 1
#define R k << 1 | 1
using namespace std;
int read();

int n;
vector<int> e[200005];
void add(int f, int t) { e[f].push_back(t), e[t].push_back(f); }
int fa[200005], dep[200005], sn[200005], sz[200005];

void dfs1(int u) {
	sz[u] = 1;
    for (vector<int>::iterator v = e[u].begin(); v != e[u].end(); v++)
        if ((*v) != fa[u]) {
			dep[*v] = dep[u] + 1, fa[*v] = u, dfs1(*v);
			sz[u] += sz[*v], sn[u] = sz[sn[u]] < sz[*v] ? *v : sn[u];
		}
}

int pre[200005], top[200005], dfn;
void dfs2(int u) {
	pre[u] = ++dfn;
	if (!sn[u]) return;
	top[sn[u]] = top[u], dfs2(sn[u]);
    for (vector<int>::iterator v = e[u].begin(); v != e[u].end(); v++)
		if ((*v) != fa[u] && (*v) != sn[u]) top[*v] = *v, dfs2(*v);
}

queue<int> q;

struct Seg {
	int mn[400005], xsum[400005];
	int tag1[400005], tag2[400005];
	void Tag1(int k, int v) { mn[k] += v, tag1[k] += v; }
	void Tag2(int k, int v) { xsum[k] ^= v, tag2[k] ^= v; }
	void psd1(int k) { Tag1(L, tag1[k]), Tag1(R, tag1[k]), tag1[k] = 0;	}
	void pi2(1, n, 1, pre[u] + 1, pre[v], id);
}

struct E {
	int u, v;
	void init(int i) { modi(u = read(), v = read(), 1, i); }
} p[200005];

int main() {
    n = read();
    for (int i = 1; i < n; ++i) add(read(), read());
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1);
    for (int i = 1, u, v; i < n; ++i) p[i].init(i);
	seg.mdi1(1, n, 1, 1, 1, 100000000),	seg.work(1, n, 1);
	int cnt = 0;
	while (!q.empty()) {
		int t = q.front();
		cerr << t << endl;
		q.pop(), cnt++, modi(p[t].u, p[t].v, -1, t), seg.work(1, n, 1);
	}
    puts(cnt == n - 1 ? "YES" : "NO");
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

```


---

## 作者：ljk123 (赞：0)

# Blue and Red Tree题解
首先，我们很容易发现在两棵树上连接相同的点的边无需删去。

接着，首先删那条边？

我们把红树上不与蓝树重合的边看作覆盖蓝树边的路径，

那么，我们首先删除被红树边覆盖多次的边么？

肯定不行，删除这条边后，就不存在构成其他覆盖这条蓝边的红边所需的蓝边链了。

所以，我们每次找出只被覆盖一次的蓝边，删去覆盖它的红遍，并去除红
边影响，如果做到最后，自然可以。

### 代码：
```cpp
#include<bits/stdc++.h>
#define lc (x<<1)
#define rc (x<<1|1) 
using namespace std;
const int N=60006,inf=1e9,mod=201314;
int n,m,t1,t2,t3,cnt=0,dfn=0,tot=0,f[N],a[N],d[N],son[N],siz[N],num[N],top[N],lazy[N<<2],w[N<<2],head[N],ans[N];
struct xd{int i,flag,x,y;}q[N<<1];
struct edge{int nxt,to;}e[N<<1];
inline void add(int u,int v){e[++cnt].nxt=head[u],e[cnt].to=v,head[u]=cnt;}
inline int read(){
   int T=0,F=1; char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-') F=-1; ch=getchar();}
   while(ch>='0'&&ch<='9') T=(T<<3)+(T<<1)+(ch-48),ch=getchar();
   return F*T;
}
void dfs(int x){
     d[x]=d[f[x]]+1,siz[x]=1; int maxt=0,maxa=-1;
     for(int i=head[x];i;i=e[i].nxt){
            dfs(e[i].to),siz[x]+=siz[e[i].to];
            if(maxa<siz[e[i].to]) maxt=e[i].to,maxa=siz[maxt];
         } 
     son[x]=maxt;
}
void dfs2(int x,int topx){
     num[x]=++dfn,top[x]=topx; 
     if(son[x]) dfs2(son[x],topx);
     for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=f[x]&&e[i].to!=son[x]) dfs2(e[i].to,e[i].to); 
}
void pushdown(int x,int len){if(lazy[x]) lazy[lc]=(lazy[lc]+lazy[x])%mod,lazy[rc]=(lazy[rc]+lazy[x])%mod,w[lc]=(w[lc]+lazy[x]*(len-(len>>1))%mod)%mod,w[rc]=(w[rc]+lazy[x]*(len>>1)%mod)%mod,lazy[x]=0;}
void update(int l,int r,int p,int q,int x,int y){
     if(p<=l&&r<=q){w[x]=(w[x]+(r-l+1)*y%mod)%mod,lazy[x]=(lazy[x]+y)%mod; return;}
     pushdown(x,r-l+1);
     int mid=l+r>>1;
     if(p<=mid) update(l,mid,p,q,lc,y);
     if(q>mid) update(mid+1,r,p,q,rc,y);
     w[x]=(w[lc]+w[rc])%mod;
}
int query(int l,int r,int p,int q,int x){
     if(p<=l&&r<=q) return w[x];
     pushdown(x,r-l+1);
     int mid=l+r>>1,ans=0;
     if(p<=mid) ans=query(l,mid,p,q,lc);
     if(q>mid) ans=(ans+query(mid+1,r,p,q,rc))%mod;
     return ans;
}
void lj_update(int x,int y){
    while(top[x]!=top[y]){
         if(d[top[x]]<d[top[y]]) swap(x,y);
         update(1,n,num[top[x]],num[x],1,1);
         x=f[top[x]];
    }
    if(d[x]>d[y]) swap(x,y);
    update(1,n,num[x],num[y],1,1); 
}
int lj_query(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
         if(d[top[x]]<d[top[y]]) swap(x,y);
         ans=(ans+query(1,n,num[top[x]],num[x],1))%mod;
         x=f[top[x]];
    }
    if(d[x]>d[y]) swap(x,y);
    ans=(ans+query(1,n,num[x],num[y],1))%mod; 
    return ans;
}
bool cmp(xd u,xd v){return u.x<v.x;}
int main(){
    n=read(),m=read();
    for(int i=2;i<=n;++i) f[i]=read()+1,add(f[i],i);
    dfs(1),dfs2(1,1);
    for(int i=1;i<=m;++i){
        t1=read(),t2=read()+1,t3=read()+1;
        q[++tot].flag=0,q[tot].i=i,q[tot].x=t1,q[tot].y=t3;
        q[++tot].flag=1,q[tot].i=i,q[tot].x=t2,q[tot].y=t3; 
    }
    sort(q+1,q+tot+1,cmp),q[0].x=0;
    for(int i=1;i<=tot;++i){
        for(int j=q[i-1].x+1;j<=q[i].x;++j)
            lj_update(1,j);
        if(!q[i].flag) ans[q[i].i]=-lj_query(1,q[i].y);
        else ans[q[i].i]=(ans[q[i].i]+lj_query(1,q[i].y)+mod)%mod;
    }
    for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
    return 0;
}  
```

---

