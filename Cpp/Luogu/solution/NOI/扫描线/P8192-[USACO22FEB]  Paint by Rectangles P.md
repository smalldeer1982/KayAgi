# [USACO22FEB]  Paint by Rectangles P

## 题目背景

翻译来自 @wlzhouzhuan。

## 题目描述

在她之前的作品受到好评后，Bessie 得到了一份设计绘画套装的工作。她通过在平面中选择 $N\ (1\le N\le 10^5)$ 个平行于坐标轴的矩形来设计该画作，没有两条边是共线的。这些矩形的边界定义了绘画着色区域的边界。

作为一名先锋艺术家，Bessie 觉得这幅画应该像一头荷斯坦奶牛。更具体地，由矩形构成的每个区域都被着色为黑色或白色，没有两个相邻区域具有相同的颜色，并且所有矩形之外的区域都被着色为白色。

选完矩形后，Bessie 想根据参数 $T$ 让你输出：

- 若 $T=1$，则输出区域总数；
- 若 $T=2$，则依次输出白色区域数量和黑色区域数量。

**注意：本题的时间限制为 4s，是默认的 2 倍。**

## 说明/提示

**【样例解释 #1】**

有 $2$ 个白色区域和 $2$ 个黑色区域，共有 $4$ 个区域。所有矩形的边界连通，因此该输入满足 subtask 3。

![](https://cdn.luogu.com.cn/upload/image_hosting/v34kpbhi.png)

**【样例解释 #2】**

右上方的矩形不与其余的矩形连通，因此该输入不满足 subtask 4。

![](https://cdn.luogu.com.cn/upload/image_hosting/boqnrha0.png)

**【数据范围】**

- subtask 1：数据 $3\sim 4$ 满足 $N\le 10^3$；
- subtask 2：数据 $5\sim 7$ 满足不存在两个矩形相交；
- subtask 3：数据 $8\sim 10$ 满足 $T=1$，且所有矩形的边界连通；
- subtask 4：数据 $11\sim 13$ 满足 $T=2$，且所有矩形的边界连通；
- subtask 5：数据 $14\sim 18$ 满足 $T=1$；
- subtask 6：数据 $19\sim 23$ 满足 $T=2$。

## 样例 #1

### 输入

```
2 1
1 1 3 3
2 2 4 4 ```

### 输出

```
4```

## 样例 #2

### 输入

```
5 2
1 5 3 6
5 4 7 9
4 1 8 3
9 8 10 10
2 2 6 7```

### 输出

```
4 5```

# 题解

## 作者：cff_0102 (赞：18)

题目很良心，不需要离散化，但是要开 `long long`。

看到平面上那么多矩形，首先上一个扫描线。从左往右扫，不难发现碰到的边有一个矩形的左边缘和右边缘两种可能。

先不管矩形的右边缘，假设矩形是无限向右延伸的，看看怎么求出答案。

设 $wcnt$ 是白色块的数量，$bcnt$ 是黑色块的数量。

![](https://cdn.luogu.com.cn/upload/image_hosting/x85n03b9.png)

扫描到一个左边缘时，可以知道这条边缘覆盖的范围。它实际上的作用是对扫描线上这段范围的颜色取反，或者说异或了 $1$。但是我们只管答案，可以发现只要知道线扫过去之后右边改变了几块的颜色，就可以对应更新答案。比如上图的扫描线扫到第二个左边缘时，多出现了从上至下的黑、白、黑三块，所以就要将 $bcnt$ 增加 $2$，将 $wcnt$ 增加 $1$。

这一块的实现确实不难。~~如果这题只考虑左边缘的话也不可能评黑了~~。

接下来考虑右边缘。先随便画几种情况看看。

![](https://cdn.luogu.com.cn/upload/image_hosting/lq6zi84v.png)

可以发现，在这两种情况中，扫描线经过一个右边缘的时候，原本左边最上面和最下面两块到右边就会“消失”（实际上就是和上方的异色块“合并”了），而中间的其它块会反色且数量保持不变。最终答案应该增加中间的那些色块的数量。

听起来好像没什么问题，但是注意到刚刚说到“上下两块会‘消失’”，那么如果上下在同一块呢？可以直接不处理吗？

这是不行的。考虑下图左边的情况，扫描线扫到下一个右边缘后，上下两边的黑色块“合并”了，导致之前计算为两块的黑色块实际上是一块，所以 $bcnt$ 此时应该自减 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/an1yrowq.png)

但是再看上图右边的情况，这里扫到右边缘时，又不应该把外面的颜色数量 $-1$，因为它们在前面已经是连在一块的了，这里并没有被当成多块算。

所以什么时候才应该 $-1$ 呢？

扫描线经过当前右边缘，且碰到这种特殊情况时，要将外面颜色的颜色数量 $-1$，当且仅当这个右边缘上下两块先前被当成了两块。不难发现，如果**当前扫过的矩形和外面那块的矩形边界连通**，才会导致外面的矩形的这两个部分**在扫描线扫过里面这个矩形的右边缘之前一直被当做是两块**（因为，如果中间不连通，断开了，那么在断开的那个时候上下两块就已经被连接在一起了，**此时并没有被当成是不同的两块**）。所以，在扫到右边缘且碰到这种特殊情况时，只需要判断当前右边缘所在的矩形与它外面（上方、下方、右侧）的那个矩形（如果有的话），边界是否连通即可。如果连通，再将对应颜色的答案 $-1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/705a9cz2.png)

说起来倒容易，但实际上应该怎么确定外面的那个矩形是几号呢（比如上图的情况）？实际上并不需要这样做，每次碰到右边缘的这种特殊情况就直接将外面的这个 $-1$ 即可。减多了怎么办？加回去就行了。注意到**每次减多的时候**，里面的这个矩形和外面的不连通，即这是另一个连通块。考虑一整个连通块，这个连通块外侧的颜色必然是相同的。假设这个连通块的某个右边缘“减多了”。首先这个右边缘必然在最外侧（如果在内侧就不是“减多了”），所以被减多的颜色应该是这整个连通块外面的颜色。显然，这个颜色在第一次扫到这个连通块时就能得到。在每次扫到一个新的连通块时将外面那个颜色答案直接 $+1$ 就可以避免被多减的情况了。至于为什么只会被多减一次，既然拿一个一维的扫描线去扫这个二维的平面，是不可能在中间把外面的区域分成三份还让它们都在某个右边缘合并消失的，除非这不止一个连通块。

至于如何判断连通块嘛，提前再拿一个扫描线扫一遍，用并查集合并就可以了。

两次扫描可以使用一棵线段树实现：

- 线段树的节点维护当前区间内存在的所有横边的位置。
- 第一次扫描时，每次碰到一个竖边，把它与它覆盖的所有横边对应的矩形合并：
  - 每个区间有一个标记 $tag$。如果这个区间内部没有被访问和修改，这个标记保持不变。
  - 假设当前线段树节点对应的区间是 $[nl,nr]$，要与编号为 $rect$ 的矩形合并的区间是 $[ml,mr]$，且 $[nl,nr]\in[ml,mr]$，即现在这一整个区间里的所有横边对应的矩形都需要与 $rect$ 合并。那么：
    - 若当前区间 $tag=0$，直接将 $tag$ 修改为 $rect$。在这之后要删除里面的一条横边时会将 $tag$ 下传，所以不用担心 $rect$ 最终不能合并到这个区间的所有矩形。
	- 否则，说明还有一个矩形同时也要和当前区间的所有矩形合并，那么直接将并查集的 $tag$ 和 $rect$ 合并即可，在以后 $tag$ 会带着 $rect$ 与这段区间中的矩形合并的。
  - 这样就能成功把所有连通块使用并查集正确合并。
  - 这部分需要注意，如果一个区间里面本来就没有横边，即 $sum=0$，那么 $rect$ 不需要和这个区间的任何矩形合并，也就不需要修改 $tag$。
- 第二次扫描时，要知道一块的颜色，可以转化成求这里到最外面要经过的矩形边缘数量，因此可以通过求解当前 $[1,x]$ 中横边的数量来得到当前这一块的颜色。接下来按照前面所说的方法实现，注意一些细节问题，其它就没什么了。具体可以参照代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n;
struct uf{
	int fa[N];
	void setup(){
		for(int i=1;i<=n;i++)fa[i]=i;
	}
	int find(int x){
		if(x==fa[x])return x;
		return fa[x]=find(fa[x]);
	}
	void merge(int x,int y){
		fa[find(x)]=find(y);
	}
}rec;
struct segtree{
	struct node{
		int l,r;
		int sum,tag;
	}a[N<<4];
	#define lc(x) (x<<1)
	#define rc(x) ((x<<1)|1)
	void build(int p,int l,int r){
		a[p].l=l,a[p].r=r;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(lc(p),l,mid);
		build(rc(p),mid+1,r);
	}
	void pd(int p){
		if(!a[p].tag)return;
		int tag=a[p].tag;
		a[p].tag=0;
		if(a[lc(p)].sum){
			if(!a[lc(p)].tag)a[lc(p)].tag=tag;
			else rec.merge(a[lc(p)].tag,tag);
		}
		if(a[rc(p)].sum){
			if(!a[rc(p)].tag)a[rc(p)].tag=tag;
			else rec.merge(a[rc(p)].tag,tag);
		}
	}
	void pu(int p){
		a[p].sum=a[lc(p)].sum+a[rc(p)].sum;
	}
	void add(int p,int ad,int x){
		int l=a[p].l,r=a[p].r;
		if(r<ad||l>ad)return;
		if(l==r){
			a[p].sum+=x;
			//不用打 tag，因为这里先前已经被 merge 到了
			return;
		}
		pd(p);
		add(lc(p),ad,x);
		add(rc(p),ad,x);
		pu(p);
	}
	void merge(int p,int ml,int mr,int rect){
		int nl=a[p].l,nr=a[p].r;
		if(nr<ml||nl>mr)return;
		if(nl>=ml&&nr<=mr){
			if(!a[p].sum)return;
			if(!a[p].tag)a[p].tag=rect;
			else rec.merge(rect,a[p].tag);
			return;
		}
		pd(p);
		merge(lc(p),ml,mr,rect);
		merge(rc(p),ml,mr,rect);
		//pu(p);其实不需要 
	}
	int sum(int p,int sr){
		int nl=a[p].l,nr=a[p].r;
		if(nl>sr)return 0;
		if(nr<=sr)return a[p].sum;
		return sum(lc(p),sr)+sum(rc(p),sr); 
	} 
}st;
struct line{
	int yd,yu;
	int rect;
	bool in;
}l[N];//垂直线段
bool vis[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>n>>t;
	for(int i=1;i<=n;i++){
		int xa,xb,ya,yb;cin>>xa>>ya>>xb>>yb;
		l[xa]={ya,yb,i,1};
		l[xb]={ya,yb,i,0};
	}
	rec.setup();
	st.build(1,1,n<<1);
	for(int i=1;i<=(n<<1);i++){
		int yu=l[i].yu,yd=l[i].yd;
		st.merge(1,yd,yu,l[i].rect);
		if(l[i].in){
			st.add(1,yd,1);
			st.add(1,yu,1);
		}else{
			st.add(1,yd,-1);
			st.add(1,yu,-1);
		}
	}
	int wcnt=1,bcnt=0;
	for(int i=1;i<=(n<<1);i++){
		if(l[i].in){
			//加边
			int d=st.sum(1,l[i].yd),u=st.sum(1,l[i].yu);
			int ch=u-d+1;//改变了几块的颜色
			bool col=d%2;//最下面的颜色（1 黑 0 白）
			if(!vis[rec.find(l[i].rect)]){//这是一个新的连通块！
				vis[rec.find(l[i].rect)]=1;
				if(col)bcnt++;
				else wcnt++;
			}
			if(col){
				//从下到上：白黑白黑……
				wcnt+=(ch+1)/2;
				bcnt+=ch/2;
			}else{
				//从下到上：黑白黑白……
				bcnt+=(ch+1)/2;
				wcnt+=ch/2;
			}
			st.add(1,l[i].yd,1);st.add(1,l[i].yu,1);
		}else{
			//删边
			st.add(1,l[i].yd,-1);st.add(1,l[i].yu,-1);
			int d=st.sum(1,l[i].yd),u=st.sum(1,l[i].yu);
			int ch=u-d-1;//改变了几块的颜色
			bool col=d%2;//最下面的颜色（1 黑 0 白）
			if(u==d){//特殊情况
				//if(rec.find(l[i].rect)==rec.find(/*外侧那个矩形的编号*/))
				//不管，直接减
				if(col)bcnt--;
				else wcnt--;
			}else{
				if(col){
					wcnt+=(ch+1)/2;
					bcnt+=ch/2;
				}else{
					bcnt+=(ch+1)/2;
					wcnt+=ch/2;
				}
			}
		}
	}
	if(t==1)cout<<wcnt+bcnt;
	else cout<<wcnt<<" "<<bcnt;
	return 0;
}
```

---

## 作者：_l_l_ (赞：9)

提供一个简单易懂的题解。

显然啊先上一个扫描线，线段树维护当前扫描线区间左端点颜色，右端点颜色，中间两种颜色的块数，线段树的修改操作即为区间异或。

然后的话是维护连通块，你会发现在两段颜色与中间的颜色合并或者一段颜色被异或分割了，这种时候连通块数会变。

因此我们尝试维护这个改变，当一个颜色段被分割时，给这两个连通块一个相同的并查集编号，代表这两段原来是一个并查集连通块中的，合并的时候检查一下这两个编号是否是同一个并查集连通块的就行，同时并查集合并。

各种细节都可以见代码：

`node` 维护的左端点颜色，右端点颜色，中间两种颜色的块数。

`id` 是并查集编号，空则为 -1，没有下传操作为 -2。

`modify` 是区间异或。

`query` 是询问 `node`。

`querycol` 查询单点颜色。

`modifyid` 修改区间编号。

`queryid` 查询单点编号。

`queryl` 询问从 x 开始向左颜色持续为 w 的左端点。

`queryr` 同上。

`evt` 是扫描线离线。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
struct node {
    int val[2], lcol, rcol;
    node operator + (const node &sec) const {
        node ans; ans.val[0] = val[0] + sec.val[0] - (rcol == 0 && sec.lcol == 0);
        ans.val[1] = val[1] + sec.val[1] - (rcol && sec.lcol);
        ans.lcol = lcol; ans.rcol = sec.rcol; return ans;
    }
};
namespace sgt {
    int tag[MAXN << 3]; node val[MAXN << 3]; int id[MAXN << 3];
    void pushup(int rt) {val[rt] = val[rt << 1] + val[rt << 1 | 1];}
    void addtag(int rt) {swap(val[rt].val[0], val[rt].val[1]); val[rt].lcol ^= 1; val[rt].rcol ^= 1; tag[rt] ^= 1;}
    void pushdown(int rt) {
        if (tag[rt]) addtag(rt << 1), addtag(rt << 1 | 1), tag[rt] = 0;
        if (id[rt] != -2) id[rt << 1] = id[rt], id[rt << 1 | 1] = id[rt], id[rt] = -2;
    }
    void build(int rt, int l, int r) {
        val[rt].val[0] = 1; id[rt] = -2; if (l == r) return id[rt] = -1, void(); int mid = (l + r) >> 1;
        build(rt << 1, l, mid); build(rt << 1 | 1, mid + 1, r);
    }
    void modify(int rt, int l, int r, int x, int y) {
        if (x <= l && r <= y) return addtag(rt); int mid = (l + r) >> 1; pushdown(rt);
        if (x <= mid) modify(rt << 1, l, mid, x, y); if (y > mid) modify(rt << 1 | 1, mid + 1, r, x, y);
        pushup(rt);
    }
    node query(int rt, int l, int r, int x, int y) {
        if (x <= l && r <= y) return val[rt]; int mid = (l + r) >> 1; pushdown(rt);
        if (y <= mid) return query(rt << 1, l, mid, x, y); if (x > mid) return query(rt << 1 | 1, mid + 1, r, x, y);
        return query(rt << 1, l, mid, x, y) + query(rt << 1 | 1, mid + 1, r, x, y);
    }
    int querycol(int rt, int l, int r, int x) {
        if (l == r) return val[rt].lcol; int mid = (l + r) >> 1; pushdown(rt);
        if (x <= mid) return querycol(rt << 1, l, mid, x); else return querycol(rt << 1 | 1, mid + 1, r, x);
    }
    void modifyid(int rt, int l, int r, int x, int y, int w) {
        if (x <= l && r <= y) return id[rt] = w, void(); int mid = (l + r) >> 1; pushdown(rt);
        if (x <= mid) modifyid(rt << 1, l, mid, x, y, w); if (y > mid) modifyid(rt << 1 | 1, mid + 1, r, x, y, w);
    }
    int queryid(int rt, int l, int r, int x) {
        if (l == r) return id[rt]; int mid = (l + r) >> 1; pushdown(rt);
        if (x <= mid) return queryid(rt << 1, l, mid, x); else return queryid(rt << 1 | 1, mid + 1, r, x);
    }
    int queryl(int rt, int l, int r, int x, int w) {
        if (r <= x && val[rt].val[w] == 1 && val[rt].val[w ^ 1] == 0) return l;
        if (l == r) return l + 1; int mid = (l + r) >> 1; pushdown(rt);
        if (x <= mid) return queryl(rt << 1, l, mid, x, w); int p;
        if ((p = queryl(rt << 1 | 1, mid + 1, r, x, w)) == mid + 1) return queryl(rt << 1, l, mid, x, w);
        else return p;
    }
    int queryr(int rt, int l, int r, int x, int w) {
        if (x <= l && val[rt].val[w] == 1 && val[rt].val[w ^ 1] == 0) return r;
        if (l == r) return l - 1; int mid = (l + r) >> 1; pushdown(rt);
        if (x > mid) return queryr(rt << 1 | 1, mid + 1, r, x, w); int p;
        if ((p = queryr(rt << 1, l, mid, x, w)) == mid) return queryr(rt << 1 | 1, mid + 1, r, x, w);
        else return p;
    }
}
struct evt {
    int t, l, r, tp; bool operator < (const evt &sec) const {
        return t < sec.t;
    }
} evts[MAXN << 1];
namespace dsu {
    int fa[MAXN], tot;
    void init(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i; tot = 0;
    }
    int findfa(int a) {return fa[a] == a ? a : fa[a] = findfa(fa[a]);}
    void merge(int u, int v) {fa[findfa(u)] = findfa(v);}
}
int main() {
    int n, m = 0, tp; scanf("%d %d", &n, &tp); dsu::init(n);
    long long ans[2]; ans[0] = 1, ans[1] = 0;
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        evts[++m] = evt{x1, y1 + 1, y2, 1}; evts[++m] = evt{x2, y1 + 1, y2, 2};
    } sgt::build(1, 1, n * 2 + 1);
    sort(evts + 1, evts + 1 + m); for (int i = 1; i <= m; i++) {
        node midd = sgt::query(1, 1, n * 2 + 1, evts[i].l, evts[i].r);
        int ll = sgt::querycol(1, 1, n * 2 + 1, evts[i].l - 1);
        int rr = sgt::querycol(1, 1, n * 2 + 1, evts[i].r + 1); bool tag = 0;
        if (ll == rr && midd.lcol == ll && midd.rcol == ll && midd.val[ll] == 1 && midd.val[ll ^ 1] == 0) {
            // 分割了一个块 
            if (sgt::queryid(1, 1, n * 2 + 1, evts[i].l) == -1) sgt::modifyid(1, 1, n * 2 + 1, sgt::queryl(1, 1, n * 2 + 1, evts[i].l - 1, ll), sgt::queryr(1, 1, n * 2 + 1, evts[i].r + 1, ll), ++dsu::tot);
            sgt::modifyid(1, 1, n * 2 + 1, evts[i].l, evts[i].r, -1); tag = 1;
        }
        if (ll == rr && midd.lcol != ll && midd.rcol != rr && midd.val[ll] == 0 && midd.val[ll ^ 1] == 1) {
            // 合并了两个块
            int il = sgt::queryid(1, 1, n * 2 + 1, evts[i].l - 1), ir = sgt::queryid(1, 1, n * 2 + 1, evts[i].r + 1);
            if (il != -1) il = dsu::findfa(il); if (ir != -1) ir = dsu::findfa(ir);
            if (il != -1 && ir != -1 && il != ir) dsu::merge(il, ir);
			else if (il != -1 && ir != -1) ans[ll]++;
            sgt::modifyid(1, 1, n * 2 + 1, sgt::queryl(1, 1, n * 2 + 1, evts[i].l - 1, ll), sgt::queryr(1, 1, n * 2 + 1, evts[i].r + 1, ll), max(il, ir)); tag = 1;
        }
        ans[0] += midd.val[1]; ans[1] += midd.val[0];
        ans[0] -= (ll == 0 && midd.lcol); ans[1] -= (ll == 1 && midd.lcol == 0);
        ans[0] -= (rr == 0 && midd.rcol); ans[1] -= (rr == 1 && midd.rcol == 0);
        if (tag == 0) {
            sgt::modifyid(1, 1, n * 2 + 1, evts[i].l, evts[i].r, -1);
            if (ll == midd.lcol) sgt::modifyid(1, 1, n * 2 + 1, evts[i].l, sgt::queryr(1, 1, n * 2 + 1, evts[i].l, midd.lcol), -1); // 左边界缩小
            else sgt::modifyid(1, 1, n * 2 + 1, evts[i].l, sgt::queryr(1, 1, n * 2 + 1, evts[i].l, midd.lcol), sgt::queryid(1, 1, n * 2 + 1, evts[i].l - 1)); // 左边界放大 
            if (rr == midd.rcol) sgt::modifyid(1, 1, n * 2 + 1, sgt::queryl(1, 1, n * 2 + 1, evts[i].r, midd.rcol), evts[i].r, -1); // 右边界缩小
            else sgt::modifyid(1, 1, n * 2 + 1, sgt::queryl(1, 1, n * 2 + 1, evts[i].r, midd.rcol), evts[i].r, sgt::queryid(1, 1, n * 2 + 1, evts[i].r + 1)); // 右边界放大 
        }
        sgt::modify(1, 1, n * 2 + 1, evts[i].l, evts[i].r);
    }
    if (tp == 2) printf("%lld %lld\n", ans[0], ans[1]);
    else printf("%lld\n", ans[0] + ans[1]);
}
```

---

## 作者：XuYueming (赞：2)

## 前言

没用线段树的小常数、小短码。

题目链接：[洛谷](https://www.luogu.com.cn/problem/P8192)。

[更好的阅读体验](https://www.cnblogs.com/XuYueming/p/18209403)。

## 题意简述

给出 $n$ 个平行于坐标轴的矩形，各边所在直线互不重合，钦定最外面为白色，对这个平面图黑白染色，分别求黑色块数和白色块数。

## 题目分析

这道题扫描线一眼题吧？所以考虑从左到右扫描线。初始白色有 $1$ 块。

我们发现，在扫描线的任意时刻，这个序列一定是类似斑马线黑白交错出现的。我们如果确定了这个序列某一端的颜色，以及有多少个颜色段，我们就能唯一确定这个序列，方便我们统计答案。

### 加边

先考虑加边。加入一条竖边 $[l, r]$，就把这段区间异或一下，统计新增的白色块数和黑色块数。根据一开始的分析，我们需要知道这条边对应的区间有多少个颜色段，以及这个区间下面第一块的颜色是什么就行了。

记有 $cnt$ 个块，黑色为 $1$，白色为 $0$，记最下面一块颜色是 $c \in \lbrace 0, 1 \rbrace$。

那么就让 $c$ 的块数加上 $\left \lceil \cfrac{cnt}{2} \right \rceil$；让 $c \operatorname{xor} 1$ 的块数加上 $\left \lfloor \cfrac{cnt}{2} \right \rfloor$。

那么如何知道块数和最下面的颜色呢？使用树状数组维护即可。

我们维护横边。加边的时候用树状数组将 $l, r$ 分别单点加一。那么块数就是 $[l + 1, r - 1]$ 中横边个数加一；最下方的颜色就查询 $l$ 以下有多少条横边，若是奇数个，则是白色，反之是黑色。

可以跟着作者模拟样例加深理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/ls8njjx2.png)

加入这条绿色的竖边。块数 $cnt = 3$，由于 $l$ 下方横边数量 $0$ 是偶数，所以最下方颜色是黑色。就上黑色块数加上 $\left \lceil \cfrac{3}{2} \right \rceil = 2$，白色块数加上 $\left \lfloor \cfrac{3}{2} \right \rfloor = 1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/921dbqu4.png)

再来看看这条绿边。块数 $cnt = 2$，由于 $l$ 下方横边数量 $3$ 是奇数，所以最下方颜色是白色。就上黑色块数加上 $\left \lceil \cfrac{2}{2} \right \rceil = 1$，白色块数加上 $\left \lfloor \cfrac{2}{2} \right \rfloor = 1$。

### 删边

删边也同理，但是略有不同。记删边后，这里有 $cnt$ 个块，最下面一块颜色是 $c \in \lbrace 0, 1 \rbrace$。

注意，如果此时 $cnt = 1$，则表示这是一条「结束的边」。之前我们将 $c$ 统计成多个块，但这时候它们到一起去了，所以要将 $c$ 的块数减一。

其他情况注意最下面的颜色是和加边相反的，以及最上面的块和最下面的块是和外面的连成一个块，不做统计。

结合样例更好理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/pcml1g9c.png)

删去这条绿色的边。$l$ 下面横边数量 $1$ 是奇数，所以最下方颜色是黑色（而不是白色）。块数 $cnt = 3$，但是最上面的黑色块属于橙色矩形，最下面的黑色块属于黄色矩形，这些块之前已经统计过了。所以让黑色块数加上 $\left \lfloor \cfrac{cnt - 2}{2} \right \rfloor = 0$，白色块数加上 $\left \lceil \cfrac{cnt - 2}{2} \right \rceil = 1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/errgc8l9.png)

删去这条绿色的边，即为前文提到的「结束的边」。$l$ 下面横边数量 $0$ 是偶数，所以最下方颜色是白色。这种情况特殊在，两个紫色圆圈处，我们将它统计成两个白色部分，而实际上它是一个块，可以理解为在这里将它们合并了，所以将白色块数减一。

### 处理

这样就结束了吗？不不不，你可以看看下面的最简单的反例。

![](https://cdn.luogu.com.cn/upload/image_hosting/6a0lxjh8.png)

没错，只有一个矩形。我们会发现在删去右边的竖边时，不应该将白色块数减一。

这是为什么呢？我们发现这是因为白色是「背景」，本来就连在一起了。

那我们将白色块数加上矩形互相相交形成的连通块个数就行了，吗？但是还是不对，不光光只是外面的白色平面，我们考虑矩形完全包含的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/0gu1lci0.png)

我们发现，处理里面红色矩形的时候，也会将黑色块数多减了一。此时，由于红色矩形和紫色矩形没有任何交点，也即不和紫色矩形相交，相当于红色矩形处在一个背景色是黑色的平面内，这是一个更小的子问题。

所以，我们在开始处理一个矩形互相相交的连通块时，首先看看它是处在一个黑色还是白色的平面内，将这个颜色数量加一，然后再处理这个子问题，这样就不会出现问题。

那么我们在预处理的时候，需要用并查集把相交的矩形合并起来。还是考虑扫描线的过程，对于一条竖边（无论是矩形左边还是右边），我们需要把此时依然存在的横边中，和竖边有交的那一部分对应的矩形，和这个竖边对应的矩形合并。发现由于我们做区间合并，序列被我们划分成了若干个连通块，每个连通块都被并查集合并到一起了。显然为了减少重复操作，我们对这样的连通块只用做一次就行了。于是可以用类珂朵莉树状物实现就行了。

时间复杂度 $\mathcal{O}(n (\log n + \alpha(n)))$。

## 代码

参考代码内注释可以帮助更好理解。

不压行，去掉注释仅 $110$ 行左右，其中还包含了很多空行，和 $21$ 行的树状数组板子。

带注释的代码见[我的博客](https://www.cnblogs.com/XuYueming/p/18209403#%E4%BB%A3%E7%A0%81)。

## 后记

比用欧拉公式，线段树加并查集的做法是不是好多了？

**Updated at 2024.12.15**：修复了预处理的错误，润色文章，优化可读性。

---

## 作者：约瑟夫用脑玩 (赞：2)

没人写题解我就来口胡了，orz fzjn 教我完全看不懂的 USACO 官解。（英语太撇，理解能力太差，是我的问题/kk

## Subtask 1

$n\le 10^3$：没啥用的暴力分，可能提示了你并查集，不过应该没有想不到的吧。

我们把离散化后的每个单位格子看成一个点，然后把没有矩形边界隔开的格子并查集连起来，然后跑二分图黑白染色即可，$n^2\alpha$。

至于为什么是二分图，**考虑每次往图内加入一个矩形并翻转矩形内部颜色**，发现符合题目要求，都有黑白染色方案了肯定是二分图。

## Subtask 2

矩形不交：有提示性的一个部分分，决定了我们由 Sub3,4 到 Sub5,6 飞跃的基础。

首先区域数就是 $n+1$，每多个矩形多个区域，考虑黑色数。（以下皆不考虑白色数，因为有区域数减一下就能算）

考虑上文“每次往图内加入一个矩形并翻转矩形内部颜色”的办法，于是每个矩形的颜色由有多少个包含它的矩形决定。

上扫描线二维偏序数一下矩形个数，即可。

## Subtask 3

矩形连通且 $T=1$：

由于连通了，考虑欧拉公式 $F=E-V+C+1$，此时连通块数 $C=1$。

发现相交了就有交点，同时会把原来矩形的一条边割出两条来，设交点个数为 $t$，有：

- $V=4n+t$
- $E=4n+2t$
- $F=t+2$

算交点数应该没有不会的吧，扫描线即可。

## Subtask 4

矩形连通且 $T=2$：算黑色数。

看题解就是被这个 der 东西卡住了，不会证明正确性，但给出算法：

- 从左往右考虑一根竖直的线，初始是白的，扫过的每个时刻显示其当前竖直位置每个区域的颜色。

先把官解的图贺过来：![](https://cdn.luogu.com.cn/upload/image_hosting/12jzi4sw.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

[图源](http://www.usaco.org/current/data/sol_prob1_platinum_feb22.html)，希望不侵。

- 每次遇到一个矩形的竖线，根据“每次往图内加入一个矩形并翻转矩形内部颜色”，我们进行黑白颜色翻转，考虑这次**翻转的贡献**。

  以下是正确性主要缺失部分，别问证明，问就是不会。
  
  **注意：以下区间指原来/现在的颜色段和当前翻转区间位置的两重限制下的极长区间。**
  
- 如果原来这个区间是白色的变成了黑色：
  - **且不与现有的其他黑色相连**，我们称出现了新的黑色线段，贡献为 $+1$。
  - **且与现有的其他黑色相连**，由于每个位置只有一个矩形的竖线，也即我们只会翻转一个连续区间，这里**现有的其他黑色**必定是原来就有的黑色而我们没有动它。
    - 若**只与现有的一个黑色段相连**，我们称是原来黑色的延伸，贡献为 $0$。
    - 若**与现有的两个黑色段相连，即左右都接了一个黑色段**，我们称是原来黑色的合并，贡献为 $-1$。
- 如果原来这个区间是黑色的变成了白色：
  - 且出现了原本的黑色区间的分裂，贡献为 $0$。
  - 且出现了一整个黑色区间的消失，贡献为 $0$。（说白了这里的贡献都不用考虑）
  
将这个莫名其妙的算法写出来发现在连通的情况下是对的，至于感性理解就因读者而异了。

上述过程就是个扫描线，直接写即可。

## Subtask 5

$T=1$：考虑将 Sub3 的欧拉公式扩展到可能出现 $C\neq1$。

于是我们要计数的只有 $C$，其他的 $E,V$ 还是一样的。

还是考虑扫描线，只不过我们扫描线不是算交点个数，而是把每个位置的线段合并到一个并查集上。

上线段树，可以打懒标记。

## Subtask 6

$T=2$：上述算法大融合。

考虑直接上 Sub4 挂哪里了，根据“每次往图内加入一个矩形并翻转矩形内部颜色”，发现就是有包含的情况使得内部黑白翻转。

于是每个连通块的颜色贡献是：包含它们的矩形个数来决定其自身使用 Sub4 的算法算出的两个数哪边是白哪边是黑。

首先用 Sub5 的算法算出区域数，然后用 Sub5 搞出来的并查集丢到 Sub2 的二维偏序里面算出包含当前连通块的矩形数。

然后按 Sub4 算出每个连通块的黑白个数，根据之前算的累入对应的答案。

实际上官解给你说了个什么（没有证明）包含一个连通块的矩形个数决定其要翻转而导致的**贡献差值只与连通块大小相关**，原文是 $x-connected$ 则算少了 $x$ 的黑色贡献。

然后给的是先假装是一个连通块算 Sub4，再按 Sub5+Sub2 对答案进行更新，应该差不多吧。（反正是口胡

口胡没有代码，要的自己翻官解。

---

