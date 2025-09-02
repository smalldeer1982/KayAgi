# Tourists

## 题目描述

A double tourist path, located at a park in Ultima Thule, is working by the following principle:

- We introduce the Cartesian coordinate system.
- At some points of time there are two tourists going (for a walk) from points $ (-1,0) $ and $ (1,0) $ simultaneously. The first one is walking from $ (-1,0) $ , the second one is walking from $ (1,0) $ .
- Both tourists in a pair move at the same speed $ 1 $ (distance unit per second), the first one moves along line $ x=-1 $ , the second one moves along line $ x=1 $ , both of them are moving in the positive direction of the $ Oy $ axis.
- At some points of time walls appear. Wall $ (l_{i},r_{i}) $ is a segment between points $ (0,l_{i}) $ and $ (0,r_{i}) $ . Each wall appears immediately.

The Ultima Thule government wants to learn this for each pair of tourists that walk simultaneously: for how long (in seconds) will they not see each other? Two tourists don't see each other if the segment that connects their positions on the plane intersects at least one wall. Two segments intersect if they share at least one point. We assume that the segments' ends belong to the segments.

Help the government count the required time. Note that the walls can intersect (in any way) or coincide.

## 样例 #1

### 输入

```
2 2
1 4 3
3 6 5
0 1
```

### 输出

```
2
4
```

## 样例 #2

### 输入

```
3 3
0 3 4
0 1 2
2 4 0
1 3 4
```

### 输出

```
2
4
4
```

# 题解

## 作者：Seauy (赞：5)

建立平面直角坐标系，如果将 y 坐标看成位置，x 坐标看成时间，那么一堵 $(L,R,t)$ 的墙在坐标系上就是 $x \in [t,+\infty), y\in [L,R]$ 的右边无限延长的矩形，一对从时间 $t$ 开始走的人图像应该为 $y=x-t$。

计算目标转化为求 $y=x-q_i$ 与所有墙点的交集的并集投影到 x 轴上的长度。

如果拿样例 2 来画图的就是

![](https://cdn.luogu.com.cn/upload/image_hosting/2s6immhe.png)

发现墙与墙之间也可能有交集，我们可以把所有墙的 y 坐标都离散化，设离散化数组为 $d_i$，对于每个 $[d_i,d_{i+1}]$，找到所有 $[L,R]$ 覆盖它的墙中 $t$ 最小的，转换成 $(d_i,d_{i+1},t_{min})$ 的墙。这样离散化出的最多 $2m-1$ 堵墙不会有重叠部分。

发现查询的直线带有斜率，可以考虑把坐标系上的每个点 $(x,y) \to (x-y,y)$，这样样例的图又变成

![](https://cdn.luogu.com.cn/upload/image_hosting/pv0nvu7i.png)

现在要计算的东西变成一条 $x=q_i$ 的直线跟所有梯形相交的线段长度之和。

一个梯形可以拆成一个等腰直角三角形和一个矩形。考虑从左到右扫描线，对于一个 $q$，它有可能跟三角形相交，有可能跟矩形相交。跟矩形相交的长度之后就不会变了，对于一个三角形，设左边的顶点（比如图中的点 $I,B,E$）坐标为 $(a,b)$，那么对答案的贡献为 $q-a$，而随着 $q$ 的增大，会超出原先的三角形区域，进入矩形区域。

开个堆，维护有交集的三角的个数 $p$ 和 $ s=\sum_{i=1}^{p} a_{i}$，以及矩形长度之和 $l$，那么对于一个 $q$，答案就为 $pq-s+l$。

记得开 long long，时间 $O(n \log n+ m \log m)$ 空间 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN=1e5,MAXV=1e9;

struct Segment
{
	int L,R,t;
	void Scan() {scanf("%d %d %d",&L,&R,&t);}
}wall[MAXN+5];

int n,m;
int discre[2*MAXN+5],Tail;
vector<int> Ins[2*MAXN+5],Del[2*MAXN+5];
bool mapn[MAXN+5];
priority_queue< pair<int,int> > Q;
ll ans[MAXN+5];

int Search(int x)
{
	for(int L=1,R=Tail,mid;1;)
	{
		mid=(L+R)>>1;
		if(discre[mid]==x) return mid;
		if(discre[mid]<x) L=mid+1;
		else R=mid-1;
	}
	return 0;
}

struct Operation
{int x,t,l,d;
}ope[4*MAXN+5];int tot;

bool cmpO(Operation a,Operation b) {return a.x<b.x;}

struct Query {int q,ID;}Ask[MAXN+5];

bool cmpQ(Query a,Query b) {return a.q<b.q;}

ll trian,tnum,len;

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		wall[i].Scan();
		discre[++Tail]=wall[i].L;
		discre[++Tail]=wall[i].R;
	}
	sort(discre+1,discre+Tail+1);
	Tail=unique(discre+1,discre+Tail+1)-discre-1;
	for(int i=1;i<=m;i++)
	{
		Ins[Search(wall[i].L)].push_back(i);
		Del[Search(wall[i].R)].push_back(i);
	}
	for(int i=1;i<Tail;i++)
	{
		for(int j=0;j<Ins[i].size();j++)
		{
			mapn[Ins[i][j]]=1;
			Q.push(make_pair(-wall[Ins[i][j]].t,Ins[i][j]));
		}
		for(int j=0;j<Del[i].size();j++) mapn[Del[i][j]]=0;
		while(!Q.empty())
			if(!mapn[Q.top().second]) Q.pop();
			else break;
		//x=a -> y=-x+a
		if(!Q.empty()) //y=-x-Q.top().first
		{
			int a=-Q.top().first;
			/*
				-x+a=discre[i]
				-x+a=discre[i+1]
				
				[a-discre[i+1],a-discre[i]]
			*/
			ope[++tot]=Operation{a-discre[i+1],a-discre[i+1],0                    , 1};
			ope[++tot]=Operation{a-discre[i  ],discre[i+1]-a,discre[i+1]-discre[i],-1};
		}
	}
	sort(ope+1,ope+tot+1,cmpO);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&Ask[i].q);
		Ask[i].ID=i;
	}
	sort(Ask+1,Ask+n+1,cmpQ);
	for(int i=1,j=0;i<=n;i++)
	{
		while(j<tot)
			if(ope[j+1].x<=Ask[i].q)
			{
				++j;
				trian+=ope[j].t;
				tnum+=ope[j].d;
				len+=ope[j].l;
			}
			else break;
		ans[Ask[i].ID]=tnum*Ask[i].q-trian+len;
	}
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：Umbrella_Leaf (赞：1)

### 题意

阴间翻译。。。

> 平面上有 $n$ 面墙，第 $i$ 面在 $(0,l_i)$ 到 $(0,r_i)$ 之间（包括端点），从时刻 $t_i$ 开始出现，之后不会消失。
> 
> $m$ 次询问，第 $i$ 次询问给出 $q_i$，表示在 $q_i$ 时刻有两个人分别从 $(1,0)$ 和 $(-1,0)$ 出发，问他们有多少时间互相看不见（注意是时间而非时刻）。
> 
> $1\le n,m\le 10^5,0\le l_i<r_i\le 10^9,0\le t_i,q_i\le 10^9$。

实际题面的 $n,m$ 和这里是相反的，但是“$n$ 次询问”实在不太顺眼。

### 题解

每个时刻两人所在位置显然是相同且固定的。

假设所有墙不相交，我们只需计算每面墙的贡献，加起来即可。

第 $i$ 面墙对从 $x$ 时刻出发的人贡献为 $\min(r_i-l_i,\max(r_i+x-t_i,0))$，也就是一个关于 $x$ 的分段函数。

可以离线所有询问，把分段点扔进小根堆里，然后从小到大枚举 $x$ 并维护这个和。

现在有墙相交的情况，但是每个位置的墙只需要取那个出现时间最早的。也就是我们直接预处理出最早出现时间的连续段即可。显然这个连续段数是 $O(n)$ 的。

怎么找连续段？先把墙按 $t_i$ 从小到大排序，那么现在要支持对某个区间中所有空位置进行覆盖。用 `set` 维护所有空的段，每次类似 ODT 进行空段的分裂和合并即可。

实际上这一步也可以离散化后用线段树解决。

总时间复杂度 $O((n+m)\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;
struct node{
    int l,r,x;
    bool operator <(const node &b)const{return x<b.x;}
}a[100005],b[300005];int cnt;
set<pair<int,int>>S;
struct Query{
    int x,id;
    bool operator <(const Query &b)const{return x<b.x;}
}que[100005];
int ans[100005];
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].x);
    sort(a+1,a+n+1);
    S.insert(make_pair(0,1e9));
    for(int i=1;i<=n;i++){
        int l=a[i].l,r=a[i].r;
        auto it=S.lower_bound(make_pair(l,0));
        if(it!=S.begin()){
            auto p=*--it;
            if(l<p.second){
                S.erase(p);
                S.insert(make_pair(p.first,l));
                S.insert(make_pair(l,p.second));
            }
        }
        it=S.lower_bound(make_pair(r,0));
        if(it!=S.begin()){
            auto p=*--it;
            if(r<p.second){
                S.erase(p);
                S.insert(make_pair(p.first,r));
                S.insert(make_pair(r,p.second));
            }
        }
        it=S.lower_bound(make_pair(l,0));
        while(it!=S.end()&&(*it).first<r){
            b[++cnt]=(node){(*it).first,(*it).second,a[i].x};
            S.erase(it);
            it=S.lower_bound(make_pair(l,0));
        }
    }
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>que1,que2;
    for(int i=1;i<=cnt;i++)que2.push(make_pair(b[i].x-b[i].r,i));
    for(int i=1;i<=m;i++)scanf("%d",&que[i].x),que[i].id=i;
    sort(que+1,que+m+1);
    ll sum=0;int tot=0;
    for(int i=1;i<=m;i++){
        while(!que2.empty()&&que2.top().first<=que[i].x){
            int j=que2.top().second;que2.pop();
            sum+=b[j].r-b[j].x;tot++;
            que1.push(make_pair(b[j].x-b[j].l,j));
        }
        while(!que1.empty()&&que1.top().first<=que[i].x){
            int j=que1.top().second;que1.pop();
            sum+=b[j].x-b[j].l;tot--;
        }
        ans[que[i].id]=sum+1ll*tot*que[i].x;
    }
    for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

[原题传送门](http://codeforces.com/problemset/problem/286/D)

[洛谷传送门](https://www.luogu.com.cn/problem/CF286D)

## 分析
先把所有墙右端点减一，这样就把时间区间变成时刻。

首先，对于一段墙，我们关注的是它最早什么时候出现。所以先把墙离散化，然后按出现的时间顺序做区间覆盖。我是用了序列并查集。

接下来考虑一段在 $x$ 时刻出现，覆盖了 $[l, r]$ 的墙。通过一些分析，可以发现设出发时间为 $t$，则若 $t < x - r$，则这段墙会被完全避开。若 $t \in [x - r, x - l)$，则 $t$ 每增加 $1$，就会增加一个被挡住的时刻。当 $t \ge x - l$ 时，这段墙的每一个点都不能避开。也就是说，随着出发时间的推迟，一段墙上无法避开的点数是先为 $0$，随后不断加一，最后不变。使用线段树维护差分数组，就可以知道每一个时刻出发时会在多少个点被挡住。由于维护的是差分数组，线段树的下标应该不能离散化。使用动态开点线段树，支持区间加，区间求和即可。

关于动态开点线段树到底开多少空间，我的建议是能开多大开多大。

## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <time.h>
#define int long long
using namespace std;
bool bg;
const int inf = 2147483647;
const int N = 1000000000;
int n, m;
int d[200005], dcnt;
map<int, int> mp;
int _mp[200005];
int l[100005], r[100005], t[100005];
int ct[200005];
int f[200005];
int getf(int x) { return (f[x] == x ? x : (f[x] = getf(f[x]))); }
void Cover(int x, int y, int z) {
    for (x = getf(x); x <= y; x = getf(x)) {
        ct[x] = z;
        f[x] = x + 1;
    }
}
int rt;
struct node {
    int l, r, s, tg;
} T[7500005];
int ncnt;
struct Segment_Tree {
    void tag(int& o, int l, int r, int v) {
        if (!o) 
            o = ++ncnt;
        T[o].tg += v, T[o].s += (r - l + 1) * v;
    }
    void pushdown(int o, int l, int r) {
        if (!T[o].tg) 
            return;
        int mid = (l + r) >> 1;
        tag(T[o].l, l, mid, T[o].tg);
        tag(T[o].r, mid + 1, r, T[o].tg);
        T[o].tg = 0;
    }
    void Add(int& o, int l, int r, int L, int R) {
        if (!o) 
            o = ++ncnt;
        if (L <= l && r <= R) {
            tag(o, l, r, 1);
            return;
        }
        pushdown(o, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) 
            Add(T[o].l, l, mid, L, R);
        if (R > mid) 
            Add(T[o].r, mid + 1, r, L, R);
        T[o].s = T[T[o].l].s + T[T[o].r].s;
    }
    int Query(int o, int l, int r, int L, int R) {
        if (!o) 
            return 0;
        if (L <= l && r <= R) 
            return T[o].s;
        pushdown(o, l, r);
        int mid = (l + r) >> 1;
        if (R <= mid) 
            return Query(T[o].l, l, mid, L, R);
        if (L > mid) 
            return Query(T[o].r, mid + 1, r, L, R);
        return Query(T[o].l, l, mid, L, R) + Query(T[o].r, mid + 1, r, L, R);
    }
} seg;
int ord[100005];
bool ed;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cerr << (&ed - &bg) / 1024.0 / 1024.0 << "\n";
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        ord[i] = i;
        cin >> l[i] >> r[i] >> t[i];
        --r[i];
        d[++dcnt] = l[i];
        d[++dcnt] = r[i] + 1;
    }
    sort(ord + 1, ord + n + 1, [](int a, int b) { return t[a] < t[b]; });
    sort(d + 1, d + dcnt + 1);
    d[0] = -1;
    for (int i = 1; i <= dcnt; i++) d[i] != d[i - 1] ? (_mp[mp[d[i]] = mp[d[i - 1]] + 1] = d[i]) : 0;
    dcnt = mp[d[dcnt]];
    for (int i = 1; i <= dcnt + 1; i++) f[i] = i, ct[i] = inf;
    for (int j = 1; j <= n; j++) {
        int i = ord[j];
        l[i] = mp[l[i]];
        r[i] = mp[r[i] + 1];
        Cover(l[i], r[i] - 1, t[i]);
    }
    for (int i = 1; i < dcnt; i++) {
        if (ct[i] == inf) 
            continue;
        int ll = _mp[i], rr = _mp[i + 1] - 1;
        seg.Add(rt, 1, N + N + 1, ct[i] - rr + N + 1, ct[i] - ll + N + 1);
    }
    while (m--) {
        int x;
        cin >> x;
        cout << seg.Query(rt, 1, N + N + 1, 1, x + N + 1) << "\n";
    }
    return 0;
}
```

---

