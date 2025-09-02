# [USACO24OPEN] Painting Fence Posts S

## 题目背景

**注意：本题的时间限制和内存限制为 3 秒 和 512MB，分别为通常限制的 1.5 倍和 2 倍。**

## 题目描述

Farmer John 的 $N$ 头奶牛（$1\le N\le 10^5$）每头都喜欢日常沿围着牧场的栅栏散步。不幸的是，每当一头奶牛走过栅栏柱子时，她就会碰到它，这要求 Farmer John 需要定期重新粉刷栅栏柱子。

栅栏由 $P$ 根柱子组成（$4\le P\le 2\cdot 10^5$，$P$ 为偶数），每根柱子的位置是 FJ 农场地图上的一个不同的二维坐标点 $(x,y)$（$0\le x,y\le 10^9$）。每根柱子通过垂直或水平线段的栅栏连接到两根相邻的柱子，因此整个栅栏可以被视为各边平行于 $x$ 轴或 $y$ 轴的一个多边形（最后一根柱子连回第一根柱子，确保围栏形成一个包围牧场的闭环）。栅栏多边形是「规则的」，体现在栅栏段仅可能在其端点处重合，每根柱子恰好属于两个栅栏段，同时每两个在端点处相交的栅栏段都是垂直的。

每头奶牛的日常散步都有一个偏好的起始和结束位置，均为沿栅栏的某个点（可能在柱子处，也可能不在）。每头奶牛日常散步时沿着栅栏行走，从起始位置开始，到结束位置结束。由于栅栏形成闭环，奶牛有两条路线可以选择。由于奶牛是一种有点懒的生物，每头奶牛都会选择距离较短的方向沿栅栏行走。值得注意的是，这个选择总是明确的——不存在并列的情况！

一头奶牛会触碰一根栅栏柱子，当她走过这根柱子，或者当这根栅栏柱子是她散步的起点或终点时。请帮助 FJ 计算每个栅栏柱子每天所经历的触碰次数，以便他知道接下来要重新粉刷哪根柱子。

可以证明，给定所有柱子的位置，组成的栅栏仅有唯一的可能性。

## 说明/提示

### 样例解释 1

柱子以如下方式由栅栏段连接：

$$
(3,1)\leftrightarrow(3,5)\leftrightarrow(1,5)\leftrightarrow(1,1)\leftrightarrow(3,1)
$$

各奶牛接触的柱子如下：

1. 柱子 $2$ 和 $4$。
2. 柱子 $2$ 和 $3$。
3. 柱子 $1$ 和 $3$。
4. 无。
5. 无。

### 测试点性质

- 测试点 $4-6$：$N,P\le 1000$。
- 测试点 $7-9$：所有位置均有 $0\le x,y\le 1000$。
- 测试点 $10-15$：没有额外限制。

## 样例 #1

### 输入

```
5 4
3 1
1 5
3 5
1 1
2 1 1 5
1 5 3 4
3 1 3 5
2 1 2 1
3 2 3 3```

### 输出

```
1
2
2
1```

## 样例 #2

### 输入

```
2 8
1 1
1 2
0 2
0 3
0 0
0 1
2 3
2 0
1 1 2 1
1 0 1 3```

### 输出

```
1
0
0
0
1
1
1
2```

## 样例 #3

### 输入

```
1 12
0 0
2 0
2 1
1 1
1 2
3 2
3 3
1 3
1 4
2 4
2 5
0 5
2 2 0 2```

### 输出

```
1
1
1
1
1
0
0
0
0
0
0
0```

# 题解

## 作者：Jerrywang09 (赞：17)

阅读题解前请确保完全理解题面。

首先有一个性质，想不到就没法做题了：假设有柱子 $(x,y_1),(x,y_2),(x,y_3),(x,y_4),\cdots$ 有着相同的横坐标，一定是形如 $(x,y_{2k-1}),(x,y_{2k})$ 的一对柱子中间连了栅栏，形如 $(x,y_{2k}),(x,y_{2k+1})$ 的一对柱子中间一定没连。对于有相同纵坐标的同理。

剩下的比较套路。连边后构成一个环图，dfs 找出环的顺序，破环成链，用差分维护区间修改即可。代码很难写。

在实现中，我将询问中的点与柱子一起处理。然后对于同一行（列）的点，找到相邻的两个柱子，并把其间的询问点一起连上。迭代器的处理也很繁琐。

如何处理重复的点也是个问题。各数组的含义详见代码注释。

```cpp
// Title:  Painting Fence Posts
// Source: USACO24OPEN Silver
// Author: Jerrywang
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=1000010;
using namespace std;

int n, nn, m;
map<int, set<int>> row, col;
// row,col:   相同行（列）上的点的列（行）坐标
map<pii, int> id; pii point[N];
// point[i]:  原始编号为i的点的坐标
// id[{x,y}]: 坐标为(x,y)的点的最小原始编号
vector<int> g[N]; int a[N], a_id[N], cnt[N]; ll d[N];
// a[i]:      环上编号为i的点的原始编号
// a_id[i]:   原始编号为i的点的环上编号
ll dis(pii a, pii b)
{
    return abs(a.F-b.F)+abs(a.S-b.S);
}
void add(int u, int v)
{
    g[u].push_back(v), g[v].push_back(u);
}
bool vis[N];
void dfs(int u)
{
    a[++nn]=u; vis[u]=1;
    for(int v:g[u]) if(!vis[v]) dfs(v);
}

int main()
{
    #ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin);
    #endif
    scanf("%d%d", &m, &n);
    rep(i, 1, n)
    {
        int x, y; scanf("%d%d", &x, &y);
        id[{x, y}]=i, point[i]={x, y};
        row[x].insert(y), col[y].insert(x);
    }
    rep(i, 1, m)
    {
        int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        point[n+i]={x1, y1}, point[n+m+i]={x2, y2};
        if(!id[{x1, y1}])
            id[{x1, y1}]=n+i,   row[x1].insert(y1), col[y1].insert(x1);
        if(!id[{x2, y2}])
            id[{x2, y2}]=n+m+i, row[x2].insert(y2), col[y2].insert(x2);
    }
    for(auto &[x,S]:row)
    {
        auto i=S.begin();
        while(i!=S.end())
        {
            for(; i!=S.end(); i++) if(id[{x, *i}]<=n) break;
            auto j=next(i), k=i;
            for(; j!=S.end(); j++) if(id[{x, *j}]<=n) break;
            if(j==S.end()) break;
            for(; k!=j; k++) add(id[{x, *k}], id[{x, *next(k)}]);
            i=next(j);
        }
    }
    for(auto &[y,S]:col)
    {
        auto i=S.begin();
        while(i!=S.end())
        {
            for(; i!=S.end(); i++) if(id[{*i, y}]<=n) break;
            auto j=next(i), k=i;
            for(; j!=S.end(); j++) if(id[{*j, y}]<=n) break;
            if(j==S.end()) break;
            for(; k!=j; k++) add(id[{*k, y}], id[{*next(k), y}]);
            i=next(j);
        }
    }
    dfs(1);
    rep(i, 1, nn) a[nn+i]=a[i], a_id[a[i]]=i;
    rep(i, 2, nn+nn) d[i]=dis(point[a[i]], point[a[i-1]]), d[i]+=d[i-1];
    rep(i, 1, m)
    {
        int u=a_id[id[point[n+i]]], v=a_id[id[point[n+m+i]]];
        ll d1, d2;
        if(d[u]<d[v])
        {
            d1=d[v]-d[u], d2=d[nn+u]-d[v];
            if(d1<d2)
                cnt[u]++, cnt[v+1]--;
            else
                cnt[v]++, cnt[nn+u+1]--;
        }
        else
        {
            d1=d[u]-d[v], d2=d[nn+v]-d[u];
            if(d1<d2)
                cnt[v]++, cnt[u+1]--;
            else
                cnt[u]++, cnt[nn+v+1]--;
        }
    }
    rep(i, 1, nn+nn) cnt[i]+=cnt[i-1];
    rep(i, 1, n)
        printf("%d\n", cnt[a_id[i]]+cnt[nn+a_id[i]]);
    
    return 0;
}
```

---

## 作者：EnofTaiPeople (赞：15)

考虑如何快速通过银组。

首先题目没有按逆时针顺序给定栅栏，考虑建出这个环。

分析性质，将对于横坐标相同，纵坐标第 $2k-1$ 和 $2k$ 小的点之间连边，另一边同理，这样使图形成一个循环链表。

注意要对于每个横纵坐标开一个 `std::set` 来存储。

接下来，对于每个询问点，尝试在循环链表中插入这些点，使用 `set` 求出前驱后继即可。

然后断环成链，对于每次询问更改差分数组，最后再做一遍前缀和即可，时间 $O((n+P)\log(n+P))$，空间 $O(n+P)$：
```cpp
int T,n,K,m,ct,mp[N],to[N],pr[N],sf[N];
#define MP(x) lower_bound(mp+1,mp+m+1,x)-mp
struct dat{
    int x,y;
    void mc(){
        x=MP(x),y=MP(y);
    }
    int dst(dat &p){
        return abs(mp[x]-mp[p.x])+abs(mp[y]-mp[p.y]);
    }
}d[N];
set<pair<int,int> >tx[N],ty[N];
int upd(int x,int y){
    auto it=tx[x].lower_bound(mkp(y,0));
    int p;
    if(it!=tx[x].end()){
        if(it->first==y)return it->second;
        p=it->second;
        if(d[pr[p]].x==x&&d[pr[p]].y<=y){
            d[++ct]={x,y};
            to[pr[ct]=pr[p]]=ct;
            pr[to[ct]=p]=ct;goto lc1;
        }
        if(d[to[p]].x==x&&d[to[p]].y<=y){
            d[++ct]={x,y};
            pr[to[ct]=to[p]]=ct;
            to[pr[ct]=p]=ct;goto lc1;
        }
    }
    it=ty[y].lower_bound(mkp(x,0));
    p=it->second;
    if(d[pr[p]].y==y&&d[pr[p]].x<=x){
        d[++ct]={x,y};
        to[pr[ct]=pr[p]]=ct;
        pr[to[ct]=p]=ct;goto lc1;
    }
    if(d[to[p]].y==y&&d[to[p]].x<=x){
        d[++ct]={x,y};
        pr[to[ct]=to[p]]=ct;
        to[pr[ct]=p]=ct;goto lc1;
    }
    lc1:tx[x].emplace(y,ct);
    ty[y].emplace(x,ct);
    return ct;
}
struct D2{
    int x,y,l,r;
    void mc(){x=upd(MP(x),MP(y)),y=upd(MP(l),MP(r));}
}d2[N];
ll v[N];
vector<int>lk[N];
void dfs(int x){
    for(int y:lk[x])
        if(x!=to[y]&&!pr[y]){
            pr[to[x]=y]=x;
            if(!to[y])dfs(y);
        }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z;ll v1,v2;
    cin>>T>>n;
    for(x=1;x<=n;++x){
        cin>>l>>r;
        mp[++m]=l,mp[++m]=r;
        d[x]={l,r};
    }
    for(i=1;i<=T;++i){
        cin>>x>>y>>l>>r;
        mp[++m]=x,mp[++m]=y;
        mp[++m]=l,mp[++m]=r;
        d2[i]={x,y,l,r};
    }
    sort(mp+1,mp+m+1),m=unique(mp+1,mp+m+1)-mp-1;
    for(x=1,ct=n;x<=n;++x){
        d[x].mc();
        tx[d[x].x].emplace(d[x].y,x);
        ty[d[x].y].emplace(d[x].x,x);
    }
    for(x=1;x<=m;++x){
        l=0;
        for(auto &p:tx[x]){
            r=p.second;
            if(l){
                lk[l].push_back(r);
                lk[r].push_back(l);l=0;
            }else l=r;
        }
        l=0;
        for(auto &p:ty[x]){
            r=p.second;
            if(l){
                lk[l].push_back(r);
                lk[r].push_back(l);l=0;
            }else l=r;
        }
    }
    dfs(1);
    // for(x=1;x<=ct;++x)printf("x:%d pr:%d to:%d\n",x,pr[x],to[x]);puts("");
    // return 0;
    for(i=1;i<=T;++i)d2[i].mc();
    for(x=to[1];;x=to[x]){
        v[x]=v[pr[x]]+d[x].dst(d[pr[x]]);
        // printf("%d ",x);
        if(x==1)break;
    }
    for(i=1;i<=T;++i){
        l=d2[i].x,r=d2[i].y;
        if(v[l]>v[r])swap(l,r);
        // printf("l:%d r:%d\n",l,r);
        if((v[r]-v[l])*2>v[1]){
            ++sf[to[1]],--sf[to[l]];
            ++sf[r];
        }else{
            ++sf[l];
            if(r!=1)--sf[to[r]];
        }
    }
    for(x=to[to[1]];;x=to[x]){
        sf[x]+=sf[pr[x]];
        if(x==1)break;
    }
    for(x=1;x<=n;++x)printf("%d\n",sf[x]);
    return 0;
}
```

---

## 作者：cff_0102 (赞：6)

调了好久，这码量真的是绿吗。

思路：首先把所有点按 $x$ 排序一次，再按 $y$ 排序一次。将排序后第 $1,2$，第 $3,4$，……，第 $p-1,p$ 个点分别连起来，就能分别得到所有横向和纵向的栅栏，下面的代码中分别用 `udline`（上到下的栅栏）和 `lrline`（左到右的栅栏）来表示。

什么，需要证明？按坐标排序后，先看第一个点，没有 $x$ 或 $y$ 坐标比它小的点，所以它要连出栅栏的话必须向上、右连出两条，碰到第一个柱子再拐弯。这个柱子显然就是排序后的第二个点。后面也以此类推，即可证明：只需要连接排序后连续的两个点就能得到最后的多边形。

把这些栅栏的所有信息，包括两个端点的 $x,y$ 坐标及其最开始在输入中的编号后，就可以从最左下角（$x,y$ 最小）的点开始，一直沿着栅栏走，给所有栅栏在定一个逆时针的顺序。

具体的，在代码中实现了 `findud` 和 `findlr` 两个函数，可以找到 $(x,y)$ 在哪个垂直或水平的栅栏上（如果有的话，没有就返回 $-1$）。实现不难，因为之前已经排序后两两连线组成栅栏，所以现在的栅栏也是排好序的，因此可以使用二分在 $O(\log p)$ 的时间内快速找到。

在把所有栅栏按顺序连起来的同时，还需要按顺序记录下每个经过的点，及其到最初始的 $0$ 号点的距离，也就是代码中的 `dis0`。

好了，以上就是代码的初始化部分。

---

接下来考虑如何处理 $n$ 个奶牛。每次会输入两个点，可以用先前提到的 `findlr` 和 `findud` 快速找到它在哪个栅栏上。首先需要计算出按先前处理顺序走的话，它们之间的距离，因为这样才能知道要走的路径是 $i\to j$ 还是 $i\to0\to(p-1)\to j$。这里可以找到对应的栅栏的起始点（具体方法：先前记录下栅栏编号，对应到点的编号即可），然后计算它们之间的距离 $dis$（即 `dis0[y]-dis0[x]`，如果 $y$ 在 $x$ 前面则需要交换这两个点），再分别计算这两个点到起始点的距离 $dis_1,dis_2$，距离就是 $dis-dis_1+dis_2$。这里有一点需要特判的，就是两个点在同一个栅栏上（且不在柱子的位置）的情况，此时需要判断 $dis$ 是否为 $0$，且 $dis_1,dis_2$ 是否都不为 $0$。如果该条件满足，这个奶牛就可以直接跳过，它不会碰到任何柱子。

接下来考虑剩下的情况，现在当前这个奶牛会选择一条路径从 $i$ 点走到 $j$ 点，有一条路径长度是 $dis-dis_1+dis_2$，还有一条路径长度是 $dis0_n-(dis-dis_1+dis_2)$。它会选择更短的那条路径，此时仍然需要分类讨论。设 $i$ 所在栅栏的前一个点是 $x$，$j$ 所在栅栏的前一个点是 $y$，那么有下面两种情况：
1. 奶牛选择的路径是 $i\to j$，那么在 $x+1$ 到 $y$ 的所有柱子的触碰次数都要加一。还有一个特殊情况，如果 $i=x$，则第 $x$ 个的触碰次数也需要加一。
2. 奶牛选择的路径是 $i\to0\to(p-1)\to j$，那么在 $0$ 到 $x$ 和 $y+1$ 到 $p-1$ 的柱子触碰次数都要加一，特殊情况为当 $j=y$ 时 $y$ 的触碰次数也要加一。这里联系代码更好理解。

现在问题只需要快速让一个区间的数全部加一即可，差分数组就能做到。

最后计算出来记得按输入的点的顺序输出，这也是刚开始需要计算每个点的初始编号的原因~~也是我讨厌这道题的最后一个点~~。

下面是我在学校比赛时写的代码，去掉了一堆调试输出，剩下了一些有用的注释。长度有 $181$ 行。

此题代码细节极多，强烈建议升蓝。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int p;
struct point{
	int x,y;
	int n;
}pts[200005];
bool cmpx(point x,point y){
	if(x.x==y.x)return x.y<y.y;
	return x.x<y.x;
}
bool cmpy(point x,point y){
	if(x.y==y.y)return x.x<y.x;
	return x.y<y.y;
}
struct udline{
	int x;
	int yu,yd;
	int nu,nd;//最开始的编号 
	int n;
}udl[100005];//按x从左到右排的|||||
struct lrline{
	int y;
	int xl,xr;
	int nl,nr;//最开始的编号 
	int n;
}lrl[100005];//按y从下到上排的=====
int findud(int x,int y){
	int l=1,r=p/2;
	while(l<r){
		int mid=(l+r)>>1;
		if(udl[mid].x<x)l=mid+1;
		else if(udl[mid].x>x)r=mid-1;
		else{
			if(udl[mid].yu<y)l=mid+1;
			else if(udl[mid].yd>y)r=mid-1;
			else l=r=mid;
		}
	}
	if(udl[l].x==x&&udl[l].yd<=y&&udl[l].yu>=y)return l;
	else return -1;
}
int findlr(int x,int y){
	int l=1,r=p/2;
	while(l<r){
		int mid=(l+r)>>1;
		if(lrl[mid].y<y)l=mid+1;
		else if(lrl[mid].y>y)r=mid-1;
		else{
			if(lrl[mid].xr<x)l=mid+1;
			else if(lrl[mid].xl>x)r=mid-1;
			else l=r=mid;
		}
	}
	if(lrl[l].y==y&&lrl[l].xl<=x&&lrl[l].xr>=x)return l;
	else return -1;
}
point a[200005];
int cald(int xa,int ya,int xb,int yb){
	return abs(xa-xb+ya-yb);
}
int dis0[200005];
int pa[200005];//chafen cunshuju
int ans[200005];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n>>p;
	for(int i=1;i<=p;i++){
		cin>>pts[i].x>>pts[i].y;
		pts[i].n=i;
	}
	sort(pts+1,pts+1+p,cmpx);
	for(int i=1;i<=p;i+=2){
		udl[(i+1)/2].x=pts[i].x;
		udl[(i+1)/2].yu=max(pts[i].y,pts[i+1].y);
		udl[(i+1)/2].yd=min(pts[i].y,pts[i+1].y);
		if(pts[i].y<pts[i+1].y){
			udl[(i+1)/2].nu=pts[i+1].n;
			udl[(i+1)/2].nd=pts[i].n;
		}else{
			udl[(i+1)/2].nu=pts[i].n;
			udl[(i+1)/2].nd=pts[i+1].n;
		}
	}
	sort(pts+1,pts+1+p,cmpy);
	for(int i=1;i<=p;i+=2){
		lrl[(i+1)/2].y=pts[i].y;
		lrl[(i+1)/2].xr=max(pts[i].x,pts[i+1].x);
		lrl[(i+1)/2].xl=min(pts[i].x,pts[i+1].x);
		if(pts[i].x<pts[i+1].x){
			lrl[(i+1)/2].nr=pts[i+1].n;
			lrl[(i+1)/2].nl=pts[i].n;
		}else{
			lrl[(i+1)/2].nr=pts[i].n;
			lrl[(i+1)/2].nl=pts[i+1].n;
		}
	}
	a[0]=pts[1];
	int cnt=0;
	for(int i=1;i<=p/2;i++){
		int lr=findlr(a[cnt].x,a[cnt].y);
		int xl=lrl[lr].xl,xr=lrl[lr].xr,y=lrl[lr].y;
		if(a[cnt].x==xl){
			//右拐的
			a[++cnt]={xr,y,lrl[lr].nr};
		}else{
			a[++cnt]={xl,y,lrl[lr].nl};
		}
		lrl[lr].n=cnt-1; 
		dis0[cnt]=dis0[cnt-1]+cald(xl,y,xr,y);
		int ud=findud(a[cnt].x,a[cnt].y);
		int yu=udl[ud].yu,yd=udl[ud].yd,x=udl[ud].x;
		if(a[cnt].y==yd){
			a[++cnt]={x,yu,udl[ud].nu};
		}else{
			a[++cnt]={x,yd,udl[ud].nd};
		}
		udl[ud].n=cnt-1;
		dis0[cnt]=dis0[cnt-1]+cald(x,yu,x,yd);
	}
	//a 按(从左下开始逆时针)顺序存了所有点
	//dis0 是按照这个顺序到点 0 的距离
	for(int i=1;i<=n;i++){
		int xa,xb,ya,yb;
		cin>>xa>>ya>>xb>>yb;
		int lra=findlr(xa,ya),uda=findud(xa,ya);
		int lrb=findlr(xb,yb),udb=findud(xb,yb);
		int lpa,lpb;
		if(uda==-1){
			//a 在 lr 上
			lpa=lrl[lra].n;
		}else if(lra==-1){
			//a 在 ud 上
			lpa=udl[uda].n;
		}else{
			lpa=max(lrl[lra].n,udl[uda].n);
		}
		if(udb==-1){
			//b 在 lr 上
			lpb=lrl[lrb].n;
		}else if(lrb==-1){
			//b 在 ud 上
			lpb=udl[udb].n;
		}else{
			lpb=max(lrl[lrb].n,udl[udb].n);
		}
		if(lpa>lpb){
			swap(lpa,lpb);
			swap(lra,lrb);
			swap(uda,udb);
			swap(xa,xb);
			swap(ya,yb);
		}
		int dis1=dis0[lpb]-dis0[lpa];
		int disa=cald(xa,ya,a[lpa].x,a[lpa].y);
		int disb=cald(xb,yb,a[lpb].x,a[lpb].y);
		if(dis1==0&&disa&&disb)continue;
		int dis=dis1-disa+disb;
		if(dis<dis0[p]-dis){
			//a 和 b 之间的要 +1
			pa[lpa+1-(disa==0)]++;
			pa[lpb+1]--;
		}else{
			//0-a,b-(p-1) 的要+1
			pa[0]++;
			pa[lpa+1]--;
			pa[lpb+1-(disb==0)]++;
			pa[p]--;
		}
	}
	for(int i=1;i<=p;i++){
		pa[i]+=pa[i-1];
	}
	for(int i=0;i<p;i++){
		ans[a[i].n]=pa[i];
	}
	for(int i=1;i<=p;i++)cout<<ans[i]<<endl;
	return 0;
}
```

几个细节问题：
1. 开 `long long`。
2. 注意把环拆成链后首尾那个点应该按 $0$ 号点算还是 $p$ 号点算（本代码中是 $0$ 号点）。
3. 注意题面中的 $p$ 是总点数，$n$ 是奶牛数，写代码时别手滑打错了。

---

## 作者：Vindictae (赞：5)

# 吐槽
![此处应有图（图转自tyr_04）](https://cdn.luogu.com.cn/upload/image_hosting/oxkb7eey.png)

图转自 @[tyr_04](/user/747109)。
# 题目大意（形式化）
给你一个多边形，保证边平行于坐标轴，且点连接且仅连接的两条边互相垂直。现在，有一些动点，给定起始坐标和结束坐标（保证在多边形上），它们会选择仅经过多边形的路径中最短的路径行走，途中会路过一些点（包括开始和结束）。求最后，多边形的每个节点被经过了多少次。

# 题目思路（本文精华在于证明）
~~模拟考的时候，花了两个小时写这道题，而本人最后输出样例的原因是 CE 调不出来。~~

首先，文章的输入是一对点，所以肯定需要连边。然后大概花五分钟想一下，就可以得到一个策略：应为按照题目的意思，同一条平行于坐标轴的直线上肯定有偶数个点（假设有 $z \times 2$ 个），我们可以先给点排序（$x$ 相同按照 $y$，$y$ 相同按照 $x$），然后，对于任意一个 $1 \leq i \leq z$，连接第 $i \times 2 - 1$ 个点和第 $i \times 2$ 个点（注意，是排完序之后）。

但是，这样保证正确性吗？

我们可以使用反证法（应该是这个名字吧），假设现在有四个点（集） $a < b < c < d$ 在同一条平行于坐标轴的直线上（$a,d$ 是点集且有奇数个点），按照策略，我们应该让 $a,b$ 相连，$c,d$ 相连。但是，如果我们假设让 $b,c$ 相连，那么，由于两个点集都只有奇数个点，就必定使得它们之间不能完全两两相连，一定会各余出一个点，如果让它们相连，就与题意矛盾了。

所以，可得我们的策略是正确的。

剩下的比较套路。连边后，按照题意，图会构成一个环，深搜找出环的顺序，破环成链，用差分维护区间修改即可。
# AC Code
本题的思维难度只占本题难度的 $25\%$（可能吧），主要是实现很难（把我整 CE 了），所以请读者自己研究，如果实在需要，请[私信作者](https://luogu.com.cn/chat?uid=1038334)。

---

## 作者：int_4096 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P10278)

### 吐槽

~~这是我目前为止写过最讨厌的代码。~~\
这是 `Farmer John` 家的栅栏。（图片来源于 `int_4096`）![](https://cdn.luogu.com.cn/upload/image_hosting/pdmpvbd0.png)  \
~~所以为什么要使用双关键字，害得我调了三天。~~

## 题意简述：

有一个所有边都平行于坐标轴的环（两条共端点的边互相垂直并且端点无序），每次给出两个环上的点，给较短的路径上的所有端点 $+1$，问每个端点的权。

## 分析

### 思路：

找到环，然后破环做差分。\
好像很简单，但是并不好写呀。（~~真的很不好写~~）\
我们逐步解决问题。

### 一、建出环

有一个性质，将 $x$ 或 $y$ 一致的点按另一维排序，连接第 $2i - 1$ 个与第 $2i$ 个。

#### 感性证明

因为拐角全是直角，在同一条轴上必定是垂直进入，沿轴走一段，再垂直离开。![](https://cdn.luogu.com.cn/upload/image_hosting/inpz9gr9.png)\
端点并不重合，所以一定是很多这样的相离的段，大概就感性证明了。\
代码如下：

```cpp
struct Point {
	int x, y, id;
	void input(const int& _id) {
		scanf("%d%d", &x, &y);
		id = _id;
	}
};
bool cmp_x(const Point& u, const Point& v) {
	if (u.x != v.x) return u.x < v.x;
	return u.y < v.y;
}
bool cmp_y(const Point& u, const Point& v) {
	if (u.y != v.y) return u.y < v.y;
	return u.x < v.x;
}
void build() {
	a[n + 1] = {-1, -1, -1};
	for (int i = 1; i <= n + 1; i++)
		dx[i] = dy[i] = a[i]; // point 类
	std::sort(dx + 1, dx + 1 + n, cmp_x);
	for (int i = 1, pre = 1; i <= n; i++)
		if (i == n || dx[i].x != dx[i + 1].x) {
			for (int j = pre; j <= i; j += 2)
				add_edge(dx[j].id, dx[j + 1].id); // 两两连边
			pre = i + 1;
		}
	std::sort(dy + 1, dy + 1 + n, cmp_y);
	for (int i = 1, pre = 1; i <= n; i++)
		if (i == n || dy[i].y != dy[i + 1].y) {
			for (int j = pre; j <= i; j += 2)
				add_edge(dy[j].id, dy[j + 1].id);
			pre = i + 1;
		}
}
```

很显然的排序与连边吧！

### 二、找到环

很简单，使用 `dfs`。

```cpp
Point ring[N];
int rcnt, id[N]; // id 为从编号映射到在环上的位置
bool vis[N];
void dfs(int u) { //
	ring[++rcnt] = a[u];
	vis[u] = 1;
	for (int v : G[u])
		if (!vis[v])
			dfs(v);
}
```

### 三、找到点在哪条边上

简单讨论可以知道要么在垂直于 $x$ 轴的边上，要么在垂直于 $y$ 轴的边上。\
可以使用二分找到 $x$ 相同的左右界。然后二分 $y$ 坐标大于查询的点的点。（可能比较绕，看代码吧。）

```cpp
bool check(int num, int l, int r) { // 检查是否在线段上
	int pl = std::min(l, r), pr = std::max(l, r);
	return (pl <= num && num <= pr);
}
piir check_x(int x, int y) { // 询问 x, y 在垂直于 x 轴的哪条边
	Point idx = {x, y, 0};
	Point* l = std::lower_bound(dx + 1, dx + 1 + n, idx, cmp_x); // 确定 x 相同的左界
	if (l->x != x) return BadPos; // 找不到
	Point* r = std::upper_bound(dx + 1, dx + 1 + n, idx, cmp_x); // 确定 x 相同的开右界
	int u = std::lower_bound(l, r, idx, cmp_y)->id;
	for (int v : G[u])
		if (a[v].x == a[u].x) { // 要垂直于 x 轴
			piir res = {u, v};
			if (id[u] > id[v]) res = {v, u};
			if (res.first == 1 && res.second == ring[n].id)
				std::swap(res.first, res.second);
			if (!check(y, a[res.first].y, a[res.second].y)) return BadPos;
			return res;
		}
	return BadPos;
}
```

有 `if (!check(y, a[res.first].y, a[res.second].y)) return BadPos;` 这一行是因为有如下情况。![](https://cdn.luogu.com.cn/upload/image_hosting/3jpfi61r.png)\
找垂直于 $y$ 轴的边同理。

### 四、破环成链

针对样例一，破环之后得到 $1, 3, 2, 4, 1$（环上 `dfs` 得到的点，最后再添一个 $1$）。\
对于第一个询问 `2 1 1 5` 找到分别在边 $(4, 1)$ 与 $(3, 2)$ 上。
我们描述一条边将更靠前的点放在前面（上面代码也是这样的）。但对于 $(1, n)$ 我们始终把 $n$ 放在前面。\
对于在端点上的点，我们认为它在破环后靠左的那条边上（所以点 `1 5` 在边 $(3, 2)$ 上而并非边 $(2, 4)$ 上）。

### 五、差分

这里有 `corner case`，需要特判（端点和在同一段上）。\
先上代码（别害怕）。

```cpp
ll ans[N], rans[N];
void add(int l, int r) {
	ans[l]++, ans[r + 1]--;
}

for (int rep = 1, x, y, u, v; rep <= q; rep++) {
  scanf("%d%d%d%d", &x, &y, &u, &v);
  piir f = find(x, y), s = find(u, v);
  ll df = dis_sum[id[f.first]] + dis({x, y, 0}, a[f.first]);
  ll ds = dis_sum[id[s.first]] + dis({u, v, 0}, a[s.first]); // 到 1 的距离
  if (df > ds) std::swap(f, s), std::swap(x, u), std::swap(y, v); // f 为更靠左的
  piir sx = {x, y}, sy = {u, v};
  ll dist = dis_sum[id[s.first]] - dis_sum[id[f.second]] + dis({x, y, 0}, a[f.second]) + dis({u, v, 0}, a[s.first]); // 见下方图片
  if (f.first == s.first && f.second == s.second) // 在同一段时需特判
  	dist = dis({x, y, 0}, {u, v, 0});
  ll rhs = ring_dis - dist; // 用总环长减去这一段得到绕一圈的长度
  if (dist < rhs) {
  	int pl = f.first;
  	piir l = {a[pl].x, a[pl].y};
  	if (sx == l || sy == l) add(id[pl], id[pl]);
  	int pr = s.second;
  	l = {a[pr].x, a[pr].y};
  	if (sx == l || sy == l) add(id[pr], id[pr]); // 先判断端点。
  	if (f.first == s.first && f.second == s.second)
  		continue;
  	add(id[f.second], id[s.first]); // 在同一段不应有这个
  } else {
  	add(1, id[f.first]);
  	if (s.second != 1)
  		add(id[s.second], n);
  	if (f.first == s.first && f.second == s.second) // 此时在同一段无需再判断端点，可以自行画图理解
  		continue;
  	int pl = f.second;
  	piir l = {a[pl].x, a[pl].y};
  	if (sx == l || sy == l) add(id[pl], id[pl]);
  	pl = s.first, l = {a[pl].x, a[pl].y};
  	if (sx == l || sy == l) add(id[pl], id[pl]); // 判断端点
  }
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/w1il1oa8.png)\
上图是求 `dist` 的方法。\
当需要绕一圈时，分别做一个前缀加和后缀加。但注意 `s` 为 $(n, 1)$ 时不应再有后缀（显然）。\
判断端点其实比较复杂，因为想要真正理解还是要自己手玩（才不是因为我不想画了），所以请自己画图理解。

### 六、Code

~~觉得题解区的都比较丑，结果自己写出来也不好看啊。。。~~

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <utility>
#include <cmath>
using std::vector;
typedef long long ll;
const int N = 200005;
int q, n;
struct Point {
	int x, y, id;
	void input(const int& _id) {
		scanf("%d%d", &x, &y);
		id = _id;
	}
};
Point a[N], copy[N], same[N];
int top = 0;
vector<int> G[N];
ll dis(const Point& u, const Point& v) {
	return std::abs(u.x - v.x) + std::abs(u.y - v.y);
}
ll dis_sum[N], ring_dis;
bool cmp_x(const Point& u, const Point& v) {
	if (u.x != v.x) return u.x < v.x;
	return u.y < v.y;
}
bool cmp_y(const Point& u, const Point& v) {
	if (u.y != v.y) return u.y < v.y;
	return u.x < v.x;
}
void add_edge(int u, int v) {
	G[u].push_back(v);
	G[v].push_back(u);
}
Point dx[N], dy[N];
void build() { // to build edges;
	a[n + 1] = {-1, -1, -1};
	for (int i = 1; i <= n + 1; i++)
		dx[i] = dy[i] = a[i];
	std::sort(dx + 1, dx + 1 + n, cmp_x);
	for (int i = 1, pre = 1; i <= n; i++)
		if (i == n || dx[i].x != dx[i + 1].x) {
			for (int j = pre; j <= i; j += 2)
				add_edge(dx[j].id, dx[j + 1].id);
			pre = i + 1;
		}
	std::sort(dy + 1, dy + 1 + n, cmp_y);
	for (int i = 1, pre = 1; i <= n; i++)
		if (i == n || dy[i].y != dy[i + 1].y) {
			for (int j = pre; j <= i; j += 2)
				add_edge(dy[j].id, dy[j + 1].id);
			pre = i + 1;
		}
}
Point ring[N];
int rcnt, id[N]; // id 为从编号映射到在环上的位置
bool vis[N];
void dfs(int u) { // to find the circle;
	ring[++rcnt] = a[u];
	vis[u] = 1;
	for (int v : G[u])
		if (!vis[v])
			dfs(v);
}
typedef std::pair<int, int> piir;
const piir BadPos = {-1, -1};
bool check(int num, int l, int r) {
	int pl = std::min(l, r), pr = std::max(l, r);
	return (pl <= num && num <= pr);
}
piir check_x(int x, int y) { // 找 x, y 在垂直于 x 轴的边
	Point idx = {x, y, 0};
	Point* l = std::lower_bound(dx + 1, dx + 1 + n, idx, cmp_x);
	if (l->x != x) return BadPos;
	Point * r = std::upper_bound(dx + 1, dx + 1 + n, idx, cmp_x);
	int u = std::lower_bound(l, r, idx, cmp_y)->id;
	for (int v : G[u])
		if (a[v].x == a[u].x) {
			piir res = {u, v};
			if (id[u] > id[v]) res = {v, u};
			if (res.first == 1 && res.second == ring[n].id)
				std::swap(res.first, res.second);
			if (!check(y, a[res.first].y, a[res.second].y)) return BadPos;
			return res;
		}
	return BadPos;
}
piir check_y(int x, int y) { // 同上，变为 y 轴
	Point idx = {x, y, 0};
	Point* l = std::lower_bound(dy + 1, dy + 1 + n, idx, cmp_y);
	if (l->y != y) return BadPos;
	Point * r = std::upper_bound(dy + 1, dy + 1 + n, idx, cmp_y);
	int u = std::lower_bound(l, r, idx, cmp_x)->id;
	for (int v : G[u])
		if (a[v].y == a[u].y) {
			piir res = {u, v};
			if (id[u] > id[v]) res = {v, u};
			if (res.first == 1 && res.second == ring[n].id)
				std::swap(res.first, res.second);
			if (!check(x, a[res.first].x, a[res.second].x)) return BadPos;
			return res;
		}
	return BadPos;
}
piir find(int x, int y) {
	piir r = check_x(x, y), l = check_y(x, y);
	piir END = {ring[n].id, 1};
	piir cur = {x, y}, fir = {a[1].x, a[1].y};
	if (l == END && cur == fir) return l;
	if (r == END && cur == fir) return r;
	if (r != BadPos && (l == BadPos || id[l.first] > id[r.first])) return r;
	if (l != BadPos && (r == BadPos || id[r.first] > id[l.first])) return l;
	return r;
}
ll ans[N], rans[N];
void add(int l, int r) {
	ans[l]++, ans[r + 1]--;
}
void solve() {
	for (int rep = 1, x, y, u, v; rep <= q; rep++) {
		scanf("%d%d%d%d", &x, &y, &u, &v);
		piir f = find(x, y), s = find(u, v);
		ll df = dis_sum[id[f.first]] + dis({x, y, 0}, a[f.first]);
		ll ds = dis_sum[id[s.first]] + dis({u, v, 0}, a[s.first]);
		if (df > ds) std::swap(f, s), std::swap(x, u), std::swap(y, v);
		piir sx = {x, y}, sy = {u, v};
		ll dist = dis_sum[id[s.first]] - dis_sum[id[f.second]] + dis({x, y, 0}, a[f.second]) + dis({u, v, 0}, a[s.first]);
		if (f.first == s.first && f.second == s.second)
			dist = dis({x, y, 0}, {u, v, 0});
		ll rhs = ring_dis - dist;
		if (dist < rhs) {
			int pl = f.first;
			piir l = {a[pl].x, a[pl].y};
			if (sx == l || sy == l) add(id[pl], id[pl]);
			int pr = s.second;
			l = {a[pr].x, a[pr].y};
			if (sx == l || sy == l) add(id[pr], id[pr]);
			if (f.first == s.first && f.second == s.second)
				continue;
			add(id[f.second], id[s.first]);
		} else {
			add(1, id[f.first]);
			if (s.second != 1)
				add(id[s.second], n);
			if (f.first == s.first && f.second == s.second)
				continue;
			int pl = f.second;
			piir l = {a[pl].x, a[pl].y};
			if (sx == l || sy == l) add(id[pl], id[pl]);
			pl = s.first, l = {a[pl].x, a[pl].y};
			if (sx == l || sy == l) add(id[pl], id[pl]);
		}
	}
}
int main() {
	//qwq
	scanf("%d%d", &q, &n);
	for (int i = 1; i <= n; i++)
		a[i].input(i);
	build();
	dfs(1);
	for (int i = 1; i <= n; i++)
		ring_dis += dis(ring[i], ring[(i == n) ? 1 : i + 1]), id[ring[i].id] = i;
	for (int i = 2; i <= n; i++)
		dis_sum[i] += dis_sum[i - 1] + dis(ring[i], ring[i - 1]);
	solve();
	for (int i = 1; i <= n; i++)
		ans[i] += ans[i - 1];
	for (int i = 1; i <= n; i++)
		rans[ring[i].id] = ans[i];
	for (int i = 1; i <= n; i++)
		printf("%lld\n", rans[i]);
	return 0;
}
```

做这种题还是要仔细呀。

---

