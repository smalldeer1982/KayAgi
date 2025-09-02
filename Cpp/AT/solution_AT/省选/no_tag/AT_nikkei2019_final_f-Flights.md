# Flights

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_f

$ 2 $ 次元平面上に、$ 1 $ から $ N $ までの番号のついた $ N $ 個の国があります。 国 $ i $ は座標 $ (X_i,Y_i) $ にあります。

それぞれの国には航空会社があります。 国 $ i $ の航空会社は、$ X_j\ \leq\ X_i $ かつ $ Y_j\ \leq\ Y_i $ を満たすすべての $ j $ ($ j\ \neq\ i $) について、 国 $ j $ との間に直通便を運航しています。 この直通便は双方向です。 つまり、国 $ i $ の航空会社の飛行機を利用して、国 $ i $ から国 $ j $ へ移動することも、 国 $ j $ から国 $ i $ へ移動することも可能です。 国 $ i $ の航空会社の飛行機は、$ 1 $ 度利用するたびに $ C_i $ 円の料金がかかります。

ケンさんは現在国 $ S $ にいて、国 $ T $ まで移動したいです。 飛行機を利用して移動するとき、飛行機の料金の合計の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ X_i\ \leq\ 10^9 $
- $ 0\ \leq\ Y_i\ \leq\ 10^9 $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- $ (X_i,Y_i)\ \neq\ (X_j,Y_j) $ ($ i\ \neq\ j $)
- $ 1\ \leq\ S\ \leq\ N $
- $ 1\ \leq\ T\ \leq\ N $
- $ S\ \neq\ T $
- 飛行機のみを利用して国 $ S $ から国 $ T $ まで移動することができる。
- 入力される値はすべて整数である。

### Sample Explanation 1

この例では、直通便は以下の $ 5 $ 種類が存在します。 - 国 $ 1 $ と国 $ 3 $ を結ぶ直通便。国 $ 1 $ の航空会社が運航しており、一度利用するのに $ 3 $ 円かかる。 - 国 $ 1 $ と国 $ 2 $ を結ぶ直通便。国 $ 2 $ の航空会社が運航しており、一度利用するのに $ 6 $ 円かかる。 - 国 $ 2 $ と国 $ 3 $ を結ぶ直通便。国 $ 2 $ の航空会社が運航しており、一度利用するのに $ 6 $ 円かかる。 - 国 $ 2 $ と国 $ 4 $ を結ぶ直通便。国 $ 2 $ の航空会社が運航しており、一度利用するのに $ 6 $ 円かかる。 - 国 $ 3 $ と国 $ 4 $ を結ぶ直通便。国 $ 4 $ の航空会社が運航しており、一度利用するのに $ 8 $ 円かかる。 国 $ 1 $ から国 $ 4 $ へ移動する場合は、国 $ 1→3→4 $ と移動すると料金の合計が $ 11 $ 円になり、これが最小です。

## 样例 #1

### 输入

```
4 1 4
0 1 3
1 1 6
0 0 4
1 0 8```

### 输出

```
11```

## 样例 #2

### 输入

```
9 3 6
2 3 9
1 4 2
0 4 16
1 3 77
3 3 12
4 0 96
4 2 41
2 1 17
3 4 45```

### 输出

```
104```

# 题解

## 作者：Starrykiller (赞：2)

考虑持久化线段树优化建图。假设你已经掌握了线段树优化建图的方法。

首先将点按照 $x$ 为第一关键字，$y$ 为第二关键字排序。

考虑持久化线段树。插入一个节点的时候，至多会有一个节点被顶替掉。注意到，如果 $X_k\le X_j$，那么能走到点 $j$ 的点一定能走到点 $k$，反之不然。所以在图上体现为新版本的叶子与旧版本的叶子之间的连边。

那么我们略微修改一下图的构造。我们还是一样地建出一棵出树一棵入树，不一样的是，本题中，我们将点 $i$ 连向出树中对应的叶子节点，将入树中对应的叶子节点连向点 $i$。更新版本时，新版本的叶子向旧版本的叶子连边，具体地就是入树中新版本连旧版本，出树中旧版本连新版本。

然后就将点 $i$ 与 $\log V$ 个区间连边即可。需要轻微卡常，[代码](https://atcoder.jp/contests/nikkei2019-final/submissions/54715760)。

时间复杂度就是 $\Theta(n\log ^2 n)$ 的。

/bx skz。

---

## 作者：OldDriverTree (赞：0)

主席树优化建图板子题。

# Solution

这个边显然是一个二维偏序的形式，考虑先把所有点按 $X$ 从小到大排序，对于一个点，就把前面所有 $Y$ 小于等于当前点的 $Y$ 的点，和当前点连一条边权为 $C$ 的边。

注意到这个东西很像线段树优化建图，但是线段树优化建图不支持插入点的操作，改成主席树优化建图即可，最后再跑一遍 $\text{dijkstra}$，答案就为 $S$ 到 $T$ 的最短路，时间复杂度 $O(n\log^2 n)$。

# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
const int N=1e5+1;
vector<P> g[N<<7];
int n,s,t,cnt,p[N],dis[N<<7];
struct Node { int x,y,c; }a[N];
vector<int> num; bool st[N<<7];
int tot,root;

int read() {
	int x=0; bool f=true; char c=0;
	while (!isdigit(c) ) f&=(c!='-'),c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?x:-x;
}
struct node { int ls,rs,in,out; }T[N<<7];
void update(int &rt,int p,int l,int r,int x,int y)
{
	rt=++tot,T[rt]=T[p],T[rt].in=++cnt,T[rt].out=++cnt;
	if (l==r) {
		if (p) g[T[rt].in].push_back({T[p].in,0}),g[T[p].out].push_back({T[rt].out,0});
		return g[T[rt].in].push_back({y,0}),g[y].push_back({T[rt].out,0});
	}
	if (x<=mid) update(T[rt].ls,T[p].ls,l,mid,x,y); else update(T[rt].rs,T[p].rs,mid+1,r,x,y);
	if (T[rt].ls) g[T[rt].in].push_back({T[T[rt].ls].in,0}),g[T[T[rt].ls].out].push_back({T[rt].out,0});
	if (T[rt].rs) g[T[rt].in].push_back({T[T[rt].rs].in,0}),g[T[T[rt].rs].out].push_back({T[rt].out,0});
}
void change(int rt,int l,int r,int s,int t,int x,int y) {
	if (!rt) return; if (s<=l&&r<=t) return g[x].push_back({T[rt].in,y}),g[T[rt].out].push_back({x,y});
	if (s<=mid) change(T[rt].ls,l,mid,s,t,x,y); if (mid<t) change(T[rt].rs,mid+1,r,s,t,x,y);
}
void dijkstra()
{
	priority_queue<P,vector<P>,greater<P> > q;
	memset(dis,0x3f,sizeof dis),q.push({dis[s]=0,s});
	while (!q.empty() ) {
		int u=q.top().second; q.pop();
		if (st[u]) continue; st[u]=true;
		for (auto [v,w]:g[u]) if (dis[u]+w<dis[v])
		q.push({dis[v]=dis[u]+w,v});
	}
}
main()
{
	n=cnt=read(),s=read(),t=read();
	for (int i=1;i<=n;i++) a[i]={read(),read(),read()},p[i]=i,num.push_back(a[i].y);
	sort(num.begin(),num.end() ),num.erase(unique(num.begin(),num.end() ),num.end() );
	for (int i=1;i<=n;i++) a[i].y=lower_bound(num.begin(),num.end(),a[i].y)-num.begin()+1;
	sort(p+1,p+n+1,[&](int x,int y){ return a[x].x^a[y].x?a[x].x<a[y].x:a[x].y<a[y].y; });
	for (int i=1;i<=n;i++) {
		change(root,1,num.size(),1,a[p[i] ].y,p[i],a[p[i] ].c);
		int rt=0; update(rt,root,1,num.size(),a[p[i] ].y,p[i]),root=rt;
	}
	dijkstra();
	printf("%lld",dis[t]);
	return 0;
}
```

---

