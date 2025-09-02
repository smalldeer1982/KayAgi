# [PA 2014] Plemiona

## 题目描述

远古时代，在吉丽王国的版图上分布着 $n$ 个部落。建立平面直角坐标系后，每个部落都是一个边平行于坐标轴的矩形。有些地盘可能同时属于多个部落。随着时间推移，部落之间会发生融合。具体来说，若两个部落的公共面积严格大于零，它们会合并成一个新的部落，新部落的形状是包含原来两个部落的最小矩形（边平行于坐标轴）。

数百万年后，部落之间终于达到了稳定状态（任两个部落都不能再合并了），然而吉丽也已经老了。他想知道最终还剩下几个部落，以及各个部落的位置。你能替他完成遗业吗？

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^5$，$0\le x1<x2\le 10^6$，$0\le y1<y2\le 10^6$。

## 样例 #1

### 输入

```
5
7 8 1 4
1 5 2 3
4 5 2 7
2 3 5 9
4 6 8 9```

### 输出

```
2
1 6 2 9
7 8 1 4
```

# 题解

## 作者：zesqwq (赞：5)

# P5998 [PA2014]Plemiona 题解

## Analysis

很巧妙的东西，终于是胡出来了。

首先，我们对矩形按照操作的 $y$ 值右端点排序。

然后我们考虑用线段树维护 $x$ 轴。

我们发现两个相交的线段所覆盖到的线段树节点上一定有某一对节点呈父子关系，原因显然。

但是在线段树上一个节点的子树太大了，我们考虑用孩子数祖先。

我们给每个线段树节点开 $2$ 个 `vector`，姑且叫它 `vec1` 和 `vec2`。

我们把矩形加入线段树时就加入所有 **访问过** 的节点的 `vec2`，并且加入其完全覆盖的最上层节点（也就是我们平时线段树维护区间操作的那些节点）的 `vec1`。

我们合并矩形时时就计算与 **访问过** 的节点的 `vec1` 的矩形是否有交，并且计算其完全覆盖的最上层节点（也就是我们平时线段树维护区间操作的那些节点）的 `vec2` 是否有交。

我们发现这个 `vec1` 和 `vec2` 在排序之后符合单调性，即你可以从其末尾开始访问，但有一个不符合条件的时候就 `break`。

这个做法的正确性显然，
实际上这个做法的均摊时间复杂度是 $O(n \log n)$ 的，空间复杂度也一样，显然是可以通过的。

最后贴一下代码。


## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
int tab[N << 2], len, n;
struct Square {
    int lx, ly, rx, ry;
    inline void read() {
        scanf("%d %d %d %d", &lx, &rx, &ly, &ry), ++lx, ++ly;
        tab[++len] = lx, tab[++len] = rx;
    }
    inline void print() { printf("%d %d %d %d\n", tab[lx] - 1, tab[rx], ly - 1, ry); }
    inline bool operator<(const Square &b) const { return ry < b.ry; }
    inline Square operator+(const Square &b) const { return {min(lx, b.lx), min(ly, b.ly), max(rx, b.rx), max(ry, b.ry)}; }
} a[N];
bool vis[N];
inline bool calc(int x, int y) { return !((a[x].ly > a[y].ry) || (a[y].ly > a[x].ry)); }
struct SegmentTree {
    vector<int> vec[N << 2], vec2[N << 2];  // vec 染色到矩形所有包含的线段上，vec2染色到所有有交该矩形的线段上。
    void update(int u, int L, int R, int l, int r, int v) {
        if (L > r || R < l) return;
        vec2[u].push_back(v);
        if (L >= l && R <= r) {
            vec[u].push_back(v);
            return;
        }
        int M = L + R >> 1;
        update(u << 1, L, M, l, r, v), update(u << 1 | 1, M + 1, R, l, r, v);
    }
    bool merge(int u, int L, int R, int l, int r, int v) {
        if (L > r || R < l) return 0;
        bool flag = 0;
        for (int i = vec[u].size() - 1; ~i; i = vec[u].size() - 1) {
            if (vis[vec[u][i]]) {
                vec[u].pop_back();
                continue;
            }
            if (!calc(vec[u][i], v)) break;
            a[v] = a[v] + a[vec[u][i]], vis[vec[u][i]] = 1;
            vec[u].pop_back();
            flag = 1;
        }
        if (L >= l && R <= r) {
            for (int i = vec2[u].size() - 1; ~i; i = vec2[u].size() - 1) {
                if (vis[vec2[u][i]]) {
                    vec2[u].pop_back();
                    continue;
                }
                if (!calc(vec2[u][i], v)) break;
                a[v] = a[v] + a[vec2[u][i]], vis[vec2[u][i]] = 1;
                vec2[u].pop_back();
                flag = 1;
            }
            return flag;
        }
        int M = L + R >> 1;
        return flag | merge(u << 1, L, M, l, r, v) | merge(u << 1 | 1, M + 1, R, l, r, v);
    }
} seg;
inline bool cmp(Square a, Square b) { return a.lx != b.lx ? a.lx < b.lx : (a.rx != b.rx ? a.rx < b.rx : (a.ly != b.ly ? a.ly < b.ly : a.ry < b.ry)); }
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) a[i].read();
    sort(a + 1, a + n + 1), sort(tab + 1, tab + len + 1), len = unique(tab + 1, tab + len + 1) - tab - 1;
    for (int i = 1; i <= n; i++) {
        a[i].lx = lower_bound(tab + 1, tab + len + 1, a[i].lx) - tab;
        a[i].rx = lower_bound(tab + 1, tab + len + 1, a[i].rx) - tab;
    }
    for (int i = 1; i <= n; i++) {
        while (seg.merge(1, 1, len, a[i].lx, a[i].rx, i))
            ;
        seg.update(1, 1, len, a[i].lx, a[i].rx, i);
    }
    // for (int i = 1; i <= n; i++) --a[i].lx, --a[i].ly;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) a[++cnt] = a[i];
    sort(a + 1, a + cnt + 1, cmp), cout << cnt << endl;
    for (int i = 1; i <= cnt; i++) a[i].print();
    return 0;
}
```

---

## 作者：cmk666 (赞：2)

[题目传送门](/problem/P5998)

题目大意：给定一些矩形，重叠面积大于 $0$ 的会合并成一个大矩形，求最后剩下矩形的数目和位置。

使用并查集维护矩形的合并情况。那么只要判断对于一个矩形，有哪些和它重叠即可。

发现值域可以离散化，因此并不大，考虑在 $x$ 轴上建立一颗线段树。线段树中维护这段区间被哪些包含和包含哪些即可。合并矩形的时候遍历所有被包含的，以及包含两个端点的区间就行。注意判断 $y$ 轴的重叠。

易得时空复杂度都是 $O(n\log n)$ 级别的，~~虽然常数巨大，代码巨长，但竟然能过~~。核心代码如下：
```cpp
struct QWQ
{
	int x1, x2, y1, y2;
	inline void rd() { read(x1), read(x2), read(y1), read(y2); }
	inline void print() { printf("%d %d %d %d\n", x1, x2, y1, y2); }
}	a[100009], ans[100009];
int n, x, y, cnt, id[100009], num[200009], N; vector < int > stk;
namespace BCJ
{
	int fa[100009];
	inline void init(int x) { For(i, 1, x) fa[i] = i; }
	inline int fat(int x) { return x == fa[x] ? x : fa[x] = fat(fa[x]); }
	inline void unionn(int x, int y)
	{
		x = fat(x), y = fat(y);
		if ( x == y ) return;
		a[x].x1 = min(a[x].x1, a[y].x1), a[x].y1 = min(a[x].y1, a[y].y1),
		a[x].x2 = max(a[x].x2, a[y].x2), a[x].y2 = max(a[x].y2, a[y].y2),
		fa[y] = x;
	}
}	using BCJ::fa, BCJ::fat;
namespace ST
{
	struct node
	{
		vector < int > p, q;
	}	t[200009 << 2];
	inline int lc(int x) { return x << 1; }
	inline int rc(int x) { return lc(x) | 1; }
	inline int md(int x, int y) { return ( x + y ) >> 1; }
	inline void insert(int p, int l, int r, int lp, int rp)
	{
		if ( lp > r || rp < l ) return;
		if ( lp <= l && r <= rp ) { stk.push_back(p); return; }
		insert(lc(p), l, md(l, r), lp, rp),
		insert(rc(p), md(l, r) + 1, r, lp, rp);
	}
	inline void update(int p, int x)
	{
		for ( int i = p ; i ; i >>= 1 ) t[i].p.push_back(x);
	}
	inline int getroot(int p, int l, int r, int pos)
	{
		if ( l == r ) return p;
		return pos <= md(l, r) ? getroot(lc(p), l, md(l, r), pos)
							   : getroot(rc(p), md(l, r) + 1, r, pos);
	}
}	using ST::t;
int main()
{
	read(n); For(i, 1, n) a[i].rd(), id[i] = i, a[i].x1++, a[i].y1++;
	For(i, 1, n) num[i] = a[i].x1, num[i + n] = a[i].x2;
	sort(num + 1, num + 2 * n + 1),
	N = unique(num + 1, num + 2 * n + 1) - num - 1;
	For(i, 1, n)
		a[i].x1 = lower_bound(num + 1, num + N + 1, a[i].x1) - num,
		a[i].x2 = lower_bound(num + 1, num + N + 1, a[i].x2) - num;
	sort(id + 1, id + n + 1, [](int x, int y) {
		return a[x].y2 != a[y].y2 ? a[x].y2 < a[y].y2 : x < y;
	}), BCJ::init(n);
	For(i, 1, n)
	{
		for ( bool flag = true ; flag ; )
		{
			flag = false, stk.clear(),
			ST::insert(1, 1, N, a[id[i]].x1, a[id[i]].x2);
			for ( int j : stk ) Fol(k, t[j].p.size() - 1, 0)
			{
				x = t[j].p[k];
				if ( x != fa[x] || fat(x) == fat(id[i]) )
				{ t[j].p.pop_back(); continue; }
				if ( a[id[i]].y1 > a[x].y2 ) break;
				BCJ::unionn(id[i], x), flag = true, t[j].p.pop_back();
			}
			for ( int j = ST::getroot(1, 1, N, a[id[i]].x1) ; j ; j >>= 1 )
				Fol(k, t[j].q.size() - 1, 0)
				{
					x = t[j].q[k];
					if ( x != fa[x] || fat(x) == fat(id[i]) )
					{ t[j].q.pop_back(); continue; }
					if ( a[id[i]].y1 > a[x].y2 ) break;
					BCJ::unionn(id[i], x), flag = true, t[j].q.pop_back();
				}
			for ( int j = ST::getroot(1, 1, N, a[id[i]].x2) ; j ; j >>= 1 )
				Fol(k, t[j].q.size() - 1, 0)
				{
					x = t[j].q[k];
					if ( x != fa[x] || fat(x) == fat(id[i]) )
					{ t[j].q.pop_back(); continue; }
					if ( a[id[i]].y1 > a[x].y2 ) break;
					BCJ::unionn(id[i], x), flag = true, t[j].q.pop_back();
				}
		}
		ST::update(ST::getroot(1, 1, N, a[id[i]].x1), id[i]);
		if ( a[id[i]].x1 != a[id[i]].x2 )
			ST::update(ST::getroot(1, 1, N, a[id[i]].x2), id[i]);
		ST::insert(1, 1, N, a[id[i]].x1, a[id[i]].x2);
		for ( int j : stk ) t[j].q.push_back(id[i]);
	}
	For(i, 1, n) if ( fa[i] == i ) ans[++cnt] = a[i];
	For(i, 1, cnt)
		ans[i].x1 = num[ans[i].x1] - 1, ans[i].x2 = num[ans[i].x2], ans[i].y1--;
	sort(ans + 1, ans + cnt + 1, [](const QWQ &x, const QWQ &y) {
		return x.x1 != y.x1 ? x.x1 < y.x1 : x.x2 != y.x2 ? x.x2 < y.x2 :
			   x.y1 != y.y1 ? x.y1 < y.y1 : x.y2 < y.y2;
	}), printf("%d\n", cnt);
	For(i, 1, cnt) ans[i].print();
	return 0;
}
```

---

## 作者：fangzichang (赞：1)

因为是最优解所以写一个。

前置知识：颜色段均摊，启发式合并。

看完题发现数据不好造，考虑乱搞。

通式扫描线，考虑按上边界从低到高扫，用一个颜色段均摊维护当前每个位置上**最高**的矩形。每次这样就可以方便地维护横坐标与当前插入的矩形相交的有哪些矩形。

::::warning[注意相交的定义]
本题中，相交部分面积严格大于 $0$ 才算相交。实现时可以将所有矩形的右边界和上边界分别缩一个单位长度，让相交的定义变成有点相交。
::::

然后考虑现在取出了若干个和当前矩形横坐标上有交的矩形。如果纵坐标也有交的话，两个矩形就将合并。合并是容易的，对四个边界分别取极值作为新边界即可。  

合并过程中，使用并查集维护“每种颜色现在对应哪个矩形”，这样可以减少对颜色段均摊的修改。

![](https://cdn.luogu.com.cn/upload/image_hosting/28vi7gex.png)

如图，插入黑色矩形时，将会检定与它相交的红橙绿蓝四个颜色段，其中红橙蓝三个矩形会直接与之合并。

```cpp
struct Node{
	mutable int l,r,v;
	bool operator<(const Node&p)const{return l<p.l;}
};
struct ODT:set<Node>{
#define iter ODT::iterator
	int n;void init(int _n){insert({0,n=_n,0});}//0 表示没有被覆盖过
	iter _find(int x){return prev(upper_bound({x,0,0}));}
	iter spilt(int x){
		if(x>n)return end();
		iter it=_find(x);
		if(it->l==x)return it;
		int l=it->l,r=it->r,v=it->v;
		erase(it),insert({l,x-1,v});
		return insert({x,r,v}).x;
	}
	void assign(int l,int r,int v){
		iter itr=spilt(r+1),itl=spilt(l);//找到和 [l,r] 有交的颜色段区间
		for(iter it=itl;it!=itr;erase(it++))
			if(it->v&&::find(it->v)!=::find(v))::merge(v,it->v);//尝试合并
		insert({l,r,::find(v)});//颜色段均摊标准操作
	}
#undef iter
}odt;
```

如果纵坐标没有交的话，直接将这一个颜色段覆盖掉，会出现这样的问题：

![](https://cdn.luogu.com.cn/upload/image_hosting/f5550mjj.png)

如图，红色矩形被三个更高的黑色矩形完全覆盖，最后插入那个很长的黑色矩形时，不能在维护颜色段均摊的数据结构上找到红色矩形并合并。

因为颜色段均摊的优秀性质，可以直接在覆盖颜色时，从高的矩形向低的矩形连一条出边，表示“这两个矩形横坐标相交，纵坐标暂时不相交，但是如果高的矩形在扫描线过程中与别的矩形合并了，纵坐标就有可能相交”。  

使用 `std::set` 存储，动态将所有出边按照矩形上边界从高到低排序，那每次合并时检定最高的若干个出边并合并，就可以保证复杂度正确。

比如说上图中，前三个黑色矩形会合并成一个大矩形，它的出边包含红色矩形。大矩形与细长黑色矩形合并时，这条出边会被检定，这样就不会漏掉红色矩形了。

::::warning[为什么不需要考虑那个什么情况？]
排序时不需要考虑“较低的矩形与其他矩形合并之后变高”的情况，它不影响合并的正确性与复杂度，原因容易证明：如果较低的矩形在扫描线过程中的“未来”变高了，那它变高之后必然会穿过我们当前考虑的较高的矩形，到时候必定要合并这两个矩形。在下面的流程中，这种情况一定不会被漏掉。
::::

::::warning[那个什么情况也不用吗？]
维护一些冗余的出边（比如两个矩形已经被合并过了，或者一个矩形被添加多次）不会让复杂度变劣。冗余出边的影响是容易用并查集处理的。
::::

合并两个矩形后，记得将出边集合也一并合并，可以使用启发式合并实现。

```cpp
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
struct Info{
	int l,r,u,d;
}w[N],res[N];
set<pii,greater<pii>>t[N];
bool chk(int l,int r,int l0,int r0){//check 两个区间是否有交
	if(l>l0)swap(l,l0),swap(r,r0);
	return l0<=r;
}
bool chk(Info a,Info b){//check 两个矩形是否有交
	return chk(a.l,a.r,b.l,b.r)&&chk(a.d,a.u-1,b.d,b.u-1);
}
void merge(int u,int v){
	if(u=find(u),v=find(v);u==v)return;
	if(w[u].d<w[v].d)swap(u,v);//将深的矩形合并到浅的矩形上，以减少分类讨论
	if(!chk(w[u],w[v]))//加出边
		return t[u].insert(pii(w[v].u,v)),void();
	vector<int>vt;
	fa[v]=u,
	chkmn(w[u].l,w[v].l),chkmx(w[u].r,w[v].r),
	chkmn(w[u].d,w[v].d),chkmx(w[u].u,w[v].u);
	for(auto it=t[u].begin();it!=t[u].end();t[u].erase(it++)){
		if(w[find(it->y)].u<=w[v].d)break;//考虑到可能在懒惰合并期间发生了别的合并，判定时需要先 find
		if(find(u)!=find(it->y))vt.pb(it->y);//检定出边中最高的若干个矩形，如果有交，也即出边矩形的上边界高于当前矩形的下边界，就合并进当前矩形
	}
	for(auto it=t[v].begin();it!=t[v].end();t[v].erase(it++)){//理论上这个循环会直接退出
		if(w[find(it->y)].u<=w[v].d)break;
		if(find(u)!=find(it->y))vt.pb(it->y);
	}
	if(t[u].size()<t[v].size())swap(t[u],t[v]);//启发式合并剩余的出边
	for(pii p:t[v])t[u].insert(pii(w[find(p.y)].u,p.y));
	for(int nv:vt)merge(u,nv);//将刚才拿出来的出边递归合并
}
```

因为是模拟赛期间实现的，所以没有那么精细，一些合并操作是明显冗余的。无论如何，它目前都是最优解。

然后回到刚才的问题，合并完一轮之后，当前矩形的宽度和高度都可能增加。因为颜色段均摊的优秀性质，将当前矩形直接重新再加入一次是没有问题的。是的，它会访问到刚刚插入的表示当前矩形的颜色段，但是这也只有一个。

所以重复插入直到矩形不再扩张为止。

```cpp
	for(int i=1;i<=n;i++)
		if(w[i].l<=--w[i].r&&w[i].d<w[i].u){//模拟赛的题面说可能有矩形退化成线，所以加了判断，实际上可能并没有这样的数据
			int l,r,u,d;
			R://需要注意的是，并查集合并了若干轮之后，并查集的根可能不是 i
			l=w[find(i)].l,r=w[find(i)].r;
			u=w[find(i)].u,d=w[find(i)].d;
			odt.assign(w[find(i)].l,w[find(i)].r,find(i));
			if(auto[_l,_r,_u,_d]=w[find(i)];
				l!=_l||r!=_r||u!=_u||d!=_d)
				goto R;
		}
```

时间复杂度：根据颜色段均摊的结论，操作的区间数量关于操作次数成线性。如果认为总共出边集合大小是 $O(n)$ 级别的，那么瓶颈在启发式合并，复杂度不高于 $O(n\log^2 n)$；实践上常数极小。可能可以分析出更低的复杂度。

::::info[full code]
```cpp
#include<bits/extc++.h>
#include<bits/stdc++.h>
//#pragma GCC optimize(2)
//This code contains niche emotional elements. It is recommended to watch it after the age of 18.
#ifdef __unix__
#define gc getchar_unlocked
#define pc putchar_unlocked
#else
#define gc _getchar_nolock
#define pc _putchar_nolock
#endif
#ifdef local
#define fileio(x,y) freopen(#x"/"#x#y".in","r",stdin),freopen(#x".out","w",stdout);
#else
#define fileio(x,y) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#endif
#define debugline fprintf(stderr,"--------------------------\n")
#define debug(x) fprintf(stderr,"Line %d,%s=%lld\n",__LINE__,#x,(ll)(x))
#define dbgln0 fprintf(stderr,"------------- What is mind?   No matter.  -------------\n")
#define dbgln1 fprintf(stderr,"============= What is matter? Never mind. =============\n")
#define all(x) x.begin(),x.end()
#define min(args...) min({args})
#define max(args...) max({args})
#define pii pair<int,int>
#define Inf (int)INFINITY
#define ldb long double
#define inf 0x3f3f3f3f
#define i128 __int128
#define pb push_back
#define ll long long
#define db double
#define endl '\n'
#define y second
#define x first
using namespace std;
const int N=1e5+10;
mt19937 rnd(20071020);
template<typename T>inline void chkmn(T&a,const T&b){a=min(a,b);}
template<typename T>inline void chkmx(T&a,const T&b){a=max(a,b);}
void read(){};
template<class T1,class...T2>
inline void read(T1&ret,T2&...rest){
	ret=0;char c=gc();bool f=0;
	for(;!isdigit(c);c=gc())f=c=='-';
	for(;isdigit(c);c=gc())ret=ret*10+c-'0';
	f&&(ret=-ret),read(rest...);
}
#define cin(...) read(__VA_ARGS__)
template<class T>
inline void print(T x){
	static short s[35],t=0;
	bool f=x<0;if(f)x=-x;
	do s[t++]=x%10,x/=10;while(x);
	for(f&&pc('-');t;)pc(s[--t]+'0');
}
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
struct Info{
	int l,r,u,d;
}w[N],res[N];
set<pii,greater<pii>>t[N];
int n,m,V;
bool chk(int l,int r,int l0,int r0){
	if(l>l0)swap(l,l0),swap(r,r0);
	return l0<=r;
}
bool chk(Info a,Info b){
	return chk(a.l,a.r,b.l,b.r)&&chk(a.d,a.u-1,b.d,b.u-1);
}
void merge(int u,int v){
	if(u=find(u),v=find(v);u==v)return;
	if(w[u].d<w[v].d)swap(u,v);
	if(!chk(w[u],w[v]))
		return t[u].insert(pii(w[v].u,v)),void();
	vector<int>vt;
	fa[v]=u,
	chkmn(w[u].l,w[v].l),chkmx(w[u].r,w[v].r),
	chkmn(w[u].d,w[v].d),chkmx(w[u].u,w[v].u);
	for(auto it=t[u].begin();it!=t[u].end();t[u].erase(it++)){
		if(w[find(it->y)].u<=w[v].d)break;
		if(find(u)!=find(it->y))vt.pb(it->y);
	}
	for(auto it=t[v].begin();it!=t[v].end();t[v].erase(it++)){
		if(w[find(it->y)].u<=w[v].d)break;
		if(find(u)!=find(it->y))vt.pb(it->y);
	}
	if(t[u].size()<t[v].size())swap(t[u],t[v]);
	for(pii p:t[v])t[u].insert(pii(w[find(p.y)].u,p.y));
	for(int nv:vt)merge(u,nv);
}
struct Node{
	mutable int l,r,v;
	bool operator<(const Node&p)const{return l<p.l;}
};
struct ODT:set<Node>{
#define iter ODT::iterator
	int n;void init(int _n){insert({0,n=_n,0});}
	iter _find(int x){return prev(upper_bound({x,0,0}));}
	iter spilt(int x){
		if(x>n)return end();
		iter it=_find(x);
		if(it->l==x)return it;
		int l=it->l,r=it->r,v=it->v;
		erase(it),insert({l,x-1,v});
		return insert({x,r,v}).x;
	}
	void assign(int l,int r,int v){
		iter itr=spilt(r+1),itl=spilt(l);
		for(iter it=itl;it!=itr;erase(it++))
			if(it->v&&::find(it->v)!=::find(v))::merge(v,it->v);
		insert({l,r,::find(v)});
	}
#undef iter
}odt;
signed main(){
	cin(n),iota(fa+1,fa+n+1,1);
	for(int i=1,l,r,d,u;i<=n;i++)
		cin(l,r,d,u),w[i]={l,r,u,d},chkmx(V,r);//我习惯于将 d 设为较小的值，因此交换了一下
	sort(w+1,w+n+1,[&](Info a,Info b){
		return a.u^b.u?a.u<b.u:a.l<b.l;
	});
	odt.init(V);
	for(int i=1;i<=n;i++)
		if(w[i].l<=--w[i].r&&w[i].d<w[i].u){
			int l,r,u,d;
			R:
			l=w[find(i)].l,r=w[find(i)].r;
			u=w[find(i)].u,d=w[find(i)].d;
			odt.assign(w[find(i)].l,w[find(i)].r,find(i));
			if(auto[_l,_r,_u,_d]=w[find(i)];
				l!=_l||r!=_r||u!=_u||d!=_d)
				goto R;
		}
	for(int i=1;i<=n;i++)
		if(find(i)==i)res[++m]=w[i],res[m].r++,swap(res[m].u,res[m].d);
	print(m),pc(endl);
	sort(res+1,res+m+1,[&](Info a,Info b){
		return make_tuple(a.l,a.r,a.u,a.d)<make_tuple(b.l,b.r,b.u,b.d);
	});
	for(int i=1;i<=m;i++)
		print(res[i].l),pc(' '),print(res[i].r),pc(' '),print(res[i].u),pc(' '),print(res[i].d),pc(endl);
//	for(int i=1;i<=m;i++){
//		if(res[i].l==res[i].r||res[i].u==res[i].d)continue;
//		for(int j=1;j<i;j++){
//			if(res[j].l==res[j].r||res[j].u==res[j].d)continue;
//			if(chk(res[i].l,res[i].r-1,res[j].l,res[j].r-1)&&
//				chk(res[i].u,res[i].d-1,res[j].u,res[j].d-1)){
//				cerr<<i<<" "<<j<<endl;
////				assert(0);
//			}
//		}
//	}
	return 0;
}
```
::::

---

## 作者：tuget (赞：0)

似乎没人写 K-D Tree 的做法，来水一篇题解。

看到题目后显然想到用一个数据结构快速找出与当前矩形有交的矩形，删除后更新当前矩形，并再一次查找，若某一次查找未找到符合要求的矩形，就 break，这么做均摊下来相当于 $O(nF(n))$，$F(n)$ 即该数据结构单次的修改和查询的复杂度。

我们考虑用 K-D Tree。我们以矩形左下角为 K-D Tree 的关键点建树，因为插入前会先删除有交的矩形，所以所有矩形不交，这么做等同于原来的对点取中位数。插入用二进制分组来优化，详见 oi-wiki。删除直接打标记即可。

为了保证复杂度，当当前子树的矩形的并被查询矩形包含时，另外写一个 clear 函数，把子树内的所有点标记为删除，然后断开父边。

一个剪枝，当一棵子树中所有点被完全删除时，把这棵子树连向父亲的边断掉。

代码:

```
#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define ll long long
#define frp freopen
#define fio(in,out) frp(in,"r",stdin),frp(out,"w",stdout)
char B[1<<19 | 5],*P,*G;
#define gc() ((P==G && (G=(P=B)+fread(B,1,1<<19,stdin)),P==G)?EOF:*P++)
inline void bug(){cout<<endl;}
template<typename TS,typename ... T>
inline void bug(TS p,T ... x){cout<<p<<" ";bug(x...);}
template<class T=int>
inline T read()
{
	T res=0,f=1;char c;
	for(;(c=gc())<'0' || c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9')res=(res<<3)+(res<<1)+(c^48),c=gc();
	return res*f;
}
void write(int x)
{
	if(x==0){putchar('0');return;}
	short st[15],top=0;
	do st[top++]=x%10,x/=10;while(x);
	while(top)putchar(st[--top]+'0');
}
int n,m,ls[maxn],rs[maxn],rt[32],cnt,b[maxn],lg[maxn];
bool is,del[maxn],f[maxn];
struct rect{
	int x1,x2,y1,y2,i;
	rect operator+(const rect &b)const{
		return {min(x1,b.x1),max(x2,b.x2),min(y1,b.y1),max(y2,b.y2),i};
	}
}a[maxn],c[maxn];
bool chk(rect &a,rect &b)
{
	rect c={max(a.x1,b.x1),min(a.x2,b.x2),max(a.y1,b.y1),min(a.y2,b.y2),0};
	return (c.x2-c.x1>0)&&(c.y2-c.y1>0);
}
bool cmp(rect a,rect b)
{
	if(a.x1^b.x1)return a.x1<b.x1;
	if(a.x2^b.x2)return a.x2<b.x2;
	return a.y1==b.y1?a.y2<b.y2:a.y1<b.y1;
}
bool in(rect &a, rect &b){
	return a.x1<=b.x1&&a.x2>=b.x2&&a.y1<=b.y1&&b.y2<=a.y2;
}
int build(int l,int r,int fl)
{
	int mid=l+r>>1,x;
	if(fl)nth_element(b+l,b+mid,b+r+1,[](int x,int y){return a[x].x2<a[y].x2;});
	else nth_element(b+l,b+mid,b+r+1,[](int x,int y){return a[x].y2<a[y].y2;});
	c[x=b[mid]]=a[x];
	if(l<mid)ls[x]=build(l,mid-1,1^fl);
	if(mid<r)rs[x]=build(mid+1,r,1^fl);
	if(ls[x])c[x]=c[x]+c[ls[x]];
	if(rs[x])c[x]=c[x]+c[rs[x]];
	return x;
}
void clear(int x)
{
	del[x]=1;
	if(ls[x])clear(ls[x]);
	if(rs[x])clear(rs[x]);
}
void work(int &x,int nw)
{	
	if(in(a[nw],c[x]))clear(x),x=0;
	if(del[x]==0&&chk(a[x],a[nw]))
		f[x]=del[x]=1,a[nw]=a[nw]+a[x],is=1;
	if(ls[x]&&chk(c[ls[x]],a[nw]))work(ls[x],nw);
	if(rs[x]&&chk(c[rs[x]],a[nw]))work(rs[x],nw);
	if(rs[x])f[x]&=f[rs[x]];if(ls[x])f[x]&=f[ls[x]];
	if(f[x])x=0;
}
void append(int &x)
{
	if(!x)return;
	if(!del[x])b[++cnt]=x;f[x]=0;
	append(ls[x]),append(rs[x]);
	x=0;
}
mt19937 rnd((unsigned ll)(new char));
int main()
{
	int i,j;
	//fio("ans.in","ans.out");
	m=n=read();
	for(i=1;i<=n;++i)a[i]={read(),read(),read(),read()};
	shuffle(a+1,a+n+1,rnd);
	for(i=1;i<=n;++i)a[i].i=i;
	lg[0]=-1,f[0]=1;
	for(i=1;i<=n;++i){
		is=1;lg[i]=lg[i>>1]+1;
		while(is)
			for(is=j=0;j<=lg[i];++j)work(rt[j],i);
		b[cnt=1]=i;
		for(j=0;;++j){
			if(!rt[j]){rt[j]=build(1,cnt,1);break;}
			else append(rt[j]);
		}
	}
	for(i=1;i<=n;++i)if(del[i])a[i].x1=1e9,--m;
	sort(a+1,a+n+1,cmp);
	write(m),putchar('\n');
	for(i=1;i<=m;++i)
		write(a[i].x1),putchar(' '),
		write(a[i].x2),putchar(' '),
		write(a[i].y1),putchar(' '),
		write(a[i].y2),putchar('\n');
	return 0;
}
```

---

## 作者：eastcloud (赞：0)

矩形并类似的问题先考虑转扫描线，我们扫描其中一维，再单独处理另外一维，且尝试在扫描线的过程中合并矩形。

如何快速找到和当前矩形可能合并在一起的矩形呢？一个想法是扫描到 $l$ 的时候加入，扫到 $r+1$ 的时候删除，但是这样我们没法简单地维护另外一维，你会发现若使用常见的数据结构我们就没办法处理删除操作。

既然如此我们就不考虑删除，直接加入并在另一维拉出来所有可能的矩形并尝试合并，我们对于另一维建立线段树，并将每个矩形的投影加入线段树，不难发现两个矩形相交的充要条件是插入其中一个矩形时存在一个经过的节点是插入另一个矩形时一个停止节点的父亲。

上面的条件只要在每个节点处维护它是那些矩形的经过节点和终止节点即可，现在的问题是有可能的矩形会很多，我们得简化一点状态。考虑把矩形按照第一维右端点从大到小的顺序插入，这样每个节点可能合并的就是节点存储的序列上的一个后缀，合并均摊是 $O(n)$ 的，不能合并直接 break 然后懒惰删除即可。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define pi pair<int,int>
#define fi first
#define se second
#define cpy(x,y,s) memcpy(x,y,sizeof(x[0])*(s))
#define mem(x,v,s) memset(x,v,sizeof(x[0])*(s))
#define all(x) begin(x),end(x)
#define vi vector<int> 
#define arr array
#define pb push_back
#define mp make_pair

#define N 200005

using namespace std;

int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9')f=(ch=='-'?-1:f),ch=getchar();
    while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
void write(int x){
    if(x<0)x=-x,putchar('-');
    if(x/10)write(x/10);
    putchar(x%10+'0');
}

struct Node{
    int a,b,x,y;
    Node(int a=0,int b=0,int x=0,int y=0):a(a),b(b),x(x),y(y){}
    Node operator +(Node d){
        return Node(min(a,d.a),max(b,d.b),min(x,d.x),max(y,d.y));
    }
}c[N],f[N];

int X[N],Y[N],cntx,cnty;
int vis[N],cnt,flag=0;

bool inter(int x,int y){
    if(c[x].b>=c[y].a)return true;
    return false;
}

struct seg{
    int tot,ls[N<<1],rs[N<<1];
    vi vec[N<<1],vec2[N<<1];
    void build(int &x,int l=1,int r=200005){
        x=++tot;if(l==r)return;int mid=(l+r)>>1;
        build(ls[x],l,mid);build(rs[x],mid+1,r);
    }
    void update(int x,int L,int R,int v,int l=1,int r=200005){
        for(int i=vec[x].size()-1;i>=0;i--){
            int p=vec[x][i];
            if(vis[p]){vec[x].pop_back();continue;}
            if(!inter(p,v))break;
            vis[p]++;vec[x].pop_back();c[v]=c[v]+c[p];flag=1;
        }
        if(l>=L && r<=R){
            for(int i=vec2[x].size()-1;i>=0;i--){
                int p=vec2[x][i];
                if(vis[p]){vec2[x].pop_back();continue;}
                if(!inter(p,v))break;
                
                vis[p]++;vec2[x].pop_back();c[v]=c[v]+c[p];flag=1;
            }
            return;
        }
        int mid=(l+r)>>1;
        if(L<=mid)update(ls[x],L,R,v,l,mid);
        if(R>mid)update(rs[x],L,R,v,mid+1,r);
    }
    void insert(int x,int L,int R,int v,int l=1,int r=200005){
        if(l>=L && r<=R)return vec[x].push_back(v);
        int mid=(l+r)>>1;vec2[x].push_back(v);
        if(L<=mid)insert(ls[x],L,R,v,l,mid);
        if(R>mid)insert(rs[x],L,R,v,mid+1,r);
    }
}T;

bool cmp(Node x,Node y){
    if(x.a!=y.a)return x.a<y.a;
    if(x.b!=y.b)return x.b<y.b;
    if(x.x!=y.x)return x.x<y.x;
    return x.y<y.y;
}

int main(){
    #ifdef EAST_CLOUD
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
    int n=read();

    for(int i=1;i<=n;i++){
        c[i].a=read()+1;c[i].b=read();c[i].x=read()+1;c[i].y=read();
        X[++cntx]=c[i].a;X[++cntx]=c[i].b;Y[++cnty]=c[i].x;Y[++cnty]=c[i].y;
    }
    sort(X+1,X+cntx+1);sort(Y+1,Y+cnty+1);
    cntx=unique(X+1,X+cntx+1)-X-1;cnty=unique(Y+1,Y+cnty+1)-Y-1;
    for(int i=1;i<=n;i++){
        c[i].a=lower_bound(X+1,X+cntx+1,c[i].a)-X;
        c[i].b=lower_bound(X+1,X+cntx+1,c[i].b)-X;
        c[i].x=lower_bound(Y+1,Y+cnty+1,c[i].x)-Y;
        c[i].y=lower_bound(Y+1,Y+cnty+1,c[i].y)-Y;
    }
    
    sort(c+1,c+n+1,[](Node x,Node y){return x.b<y.b;});
    int rt;T.build(rt);

    for(int i=1;i<=n;i++){
        do{
            flag=0;
            T.update(rt,c[i].x,c[i].y,i);
        }while(flag);
        T.insert(rt,c[i].x,c[i].y,i);
    }

    int res=0;
    for(int i=1;i<=n;i++){
        if(!vis[i])res++,f[++cnt]=c[i];
    }

    sort(f+1,f+cnt+1,cmp);
    write(res);putchar('\n');
    for(int i=1;i<=cnt;i++){
        write(X[f[i].a]-1);putchar(' ');
        write(X[f[i].b]);putchar(' ');
        write(Y[f[i].x]-1);putchar(' ');
        write(Y[f[i].y]);putchar('\n');
    }
}
```

---

