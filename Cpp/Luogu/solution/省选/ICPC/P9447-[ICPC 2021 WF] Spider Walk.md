# [ICPC 2021 WF] Spider Walk

## 题目描述

夏洛特蜘蛛坐在她的蜘蛛网中心，蜘蛛网由一系列从中心延伸到外边界的丝线组成。夏洛特的网还有桥，每座桥连接两条相邻的丝线。桥的两个端点到蜘蛛网中心的距离总是相同。

当夏洛特在中心享用完深夜的盛宴后想要撤退到某个角落时，她会自动驾驶地走到边缘。为此，她选择一条起始丝线，并沿着它走，直到遇到这条丝线上的第一座桥。她会穿过桥到另一条丝线上，然后继续向外走，直到遇到另一座桥。然后她会穿过那座桥，并重复这个过程，直到当前丝线上没有更多的桥，然后她会走到当前丝线的末端。注意，夏洛特必须穿过她遇到的所有桥。图 I.1 展示了夏洛特可能走的一条路径。

夏洛特白天最喜欢睡觉的角落在丝线 $s$ 的末端。对于每个可能的起始丝线，她想知道为了最终到达 $s$，需要在原始网中添加的最少桥数。夏洛特可以在丝线的任何一点添加桥，只要添加的桥不接触任何其他桥。任何添加的桥的两个端点必须到蜘蛛网中心的距离相同，并且桥必须连接两条相邻的丝线。

![](https://cdn.luogu.com.cn/upload/image_hosting/7nb4cy7c.png)

图 I.1：在示例输入 1 中从丝线 4 开始的路径。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7 5 6
2 1
4 3
6 3
8 7
10 5
```

### 输出

```
2
1
1
1
0
1
2
```

## 样例 #2

### 输入

```
4 4 2
1 1
2 2
3 3
4 4
```

### 输出

```
1
1
0
1
```

# 题解

## 作者：qiuzx (赞：1)

## 题意

从一个点向外射出 $n$ 条足够长的线段形成一个环，逆时针顺序依次编号为 $1\sim n$，其中有 $m$ 条边连接两个相邻线段上的两个点，满足这两个点到原点距离相等，且任意两条边到原点的距离不等。现在从原点出发，初始选择一条线段，然后一直向外走，若遇到一条边则立即沿着边走到另一侧并继续往外走，直到走到某条线段的端点。现在希望最后走到第 $s$ 条线段的端点。你可以加入任意多条边，这些边也要满足两点到原点距离相等和任意两边距离不等的要求。对于每个 $i$，求出至少要加入多少条边。$n\le 2\times 10^5,m\le 5\times 10^5$。

## 思路

容易发现这个过程是可逆的，即从一个位置出发的下一步是唯一的，而从一个位置向后倒推也能唯一推出从原点到这个位置的路径是什么样子的。因此一个简单的想法是从 $s$ 出发倒着做，则我们需要处理一个最短路状的问题。

考虑一种类似扫描线的想法，倒着扫描每条边，实时对每个 $i$ 维护当前已经考虑过的部分中，从 $s$ 到 $i$ 所需增加的最少的边的数量，记为 $f_i$。则考察加入一条边对 $f$ 产生的影响是什么。假设加入了 $(x,y)$ 这条边，则在这条边上面的路径向下走的时候，$x$ 会走到 $y$，$y$ 会走到 $x$，因此影响是 $f_x,f_y$ 互换。此后，我们开始加入一些边。容易发现我们加入的边一定按照先后顺序形如 $(l,l+1),(l+1,l+2),\cdots,(r-1,r)$ 或反过来。目的是为了从 $f_l$ 更新到 $f_r$。这样我们就得到了一个暴力的做法，每次暴力枚举 $l,r$ 并更新。这样做的复杂度是 $O(mn^2)$。

第一个优化是显然的，由于我们上一步只修改了 $f_x,f_y$ 的值，而在这之前我们得到的结果已经是最新的结果了，所以对于一个 $i\ne x,i\ne y$ 的位置 $i$，它对其它元素的更新是无效的。因此我们只需要枚举 $l=x,y$ 和 $r$ 更新即可。复杂度变为 $O(mn)$。需要注意的是，由于我们交换 $f_x,f_y$ 这一步操作的时候可能会使得 $f_x,f_y$ 的值变大，所以我们还需要先用别的值更新 $f_x,f_y$。但此时必然是用 $f_{x-1}\to f_x$，$f_{y+1}\to f_y$，原因是若 $f_{a}\to f_x$ 更优，则说明 $f_a\to f_{x-1}$ 也可以被更新，但我们在上一步已经处理过这样的更新了。

下面剩余的部分就是数据结构维护这个事情。我们需要维护一个数据结构，支持区间对公差为 $\pm1$ 的等差数列取 $\min$，单点修改与单点查询。使用两棵线段树分别维护公差为 $1,-1$ 的操作。此时一次操作可以看作区间对 $v+i$ 或 $v-i$ 取 $\min$，在线段树节点上记录区间内 $v$ 的最小值，单点查询时查询其 $v$ 的最小值再加上或减去 $i$ 即可得到真实的值。线段树维护的部分应当是简单的，这样就做完了，复杂度 $O(m\log n)$。

[代码](https://www.luogu.com.cn/paste/v1u0krcq)

---

## 作者：StayAlone (赞：0)

设 $dis_{i, j}$ 表示两点环上的距离。

将整个过程倒过来考虑。设 $f_i$ 表示从 $s$ 的无穷远处最终走到 $i$ 号射线的答案。显然有 $|f_i-f_j|\leq dis_{i, j}$。

由外向内依次加入桥。初始没有桥，$f_i=dis_{i, s}$。当加入一座桥时，设其两端为 $a,b$，则交换 $f_a,f_b$。

此时可能不满足上面给出的不等式，因此需要更新一下。发现对于 $f_a,f_b$，只需要使用相邻的位置更新即可，否则一定存在更多不合法位置。

此后，再用 $f_a,f_b$ 向外更新。问题转化为区间对公差 $\pm 1$ 的等差数列取 $\min$，线段树维护即可。时间复杂度 $\mathcal O(m\log nm+n)$。

```cpp
int n, m, s; pii a[MAXM];

struct setr {
	#define STZ MAXN << 2
	int tag1[STZ], tag2[STZ];
	
	il void pushdown(int x, int l, int r) {
		int mid = l + r >> 1;
		if (tag1[x] != inf) {
			gmin(tag1[ls(x)], tag1[x]);
			gmin(tag1[rs(x)], tag1[x] + mid - l + 1);
			tag1[x] = inf;
		}
		if (tag2[x] != inf) {
			gmin(tag2[ls(x)], tag2[x]);
			gmin(tag2[rs(x)], tag2[x] - (mid - l + 1));
			tag2[x] = inf;
		}
	}
	
	il void build(int x, int l, int r) {
		tag1[x] = tag2[x] = inf;
		if (l == r) return tag1[x] = tag2[x] = l == s ? 0 : inf, void();
		int mid = l + r >> 1;
		build(ls(x), l, mid); build(rs(x), mid + 1, r);
	}
	
	il int query(int x, int l, int r, int k) {
		if (l == r) return min(tag1[x], tag2[x]);
		int mid = l + r >> 1; pushdown(x, l, r);
		return k <= mid ? query(ls(x), l, mid, k) : query(rs(x), mid + 1, r, k);
	}
	
	il void upd1(int x, int l, int r, int ql, int qr, int &k) {
		if (l > qr || r < ql) return;
		if (l >= ql && r <= qr) return gmin(tag1[x], k), k += r - l + 1, void();
		int mid = l + r >> 1; pushdown(x, l, r);
		upd1(ls(x), l, mid, ql, qr, k); upd1(rs(x), mid + 1, r, ql, qr, k);
	}
	
	il void upd2(int x, int l, int r, int ql, int qr, int &k) {
		if (l > qr || r < ql) return;
		if (l >= ql && r <= qr) return gmin(tag2[x], k), k -= r - l + 1, void();
		int mid = l + r >> 1; pushdown(x, l, r);
		upd2(ls(x), l, mid, ql, qr, k); upd2(rs(x), mid + 1, r, ql, qr, k);
	}
	
	il void print(int x, int l, int r) {
		if (l == r) return printf("%d\n", min(tag1[x], tag2[x])), void();
		int mid = l + r >> 1; pushdown(x, l, r);
		print(ls(x), l, mid); print(rs(x), mid + 1, r);
	}
	
	il void update(int x, int l, int r, int k, int p) {
		if (l == r) return gmin(tag1[x], p), gmin(tag2[x], p);
		int mid = l + r >> 1; pushdown(x, l, r);
		k <= mid ? update(ls(x), l, mid, k, p) : update(rs(x), mid + 1, r, k, p);
	}
	
	il void update2(int x, int l, int r, int k, int p) {
		if (l == r) return tag1[x] = tag2[x] = p, void();
		int mid = l + r >> 1; pushdown(x, l, r);
		k <= mid ? update2(ls(x), l, mid, k, p) : update2(rs(x), mid + 1, r, k, p);
	}
} T;

il void change(int x) {
	T.update(1, 1, n, x, min(T.query(1, 1, n, x % n + 1), T.query(1, 1, n, x > 1 ? x - 1 : n)) + 1);
}

il void spread(int x) {
	int g, f = T.query(1, 1, n, x);
	T.upd1(1, 1, n, 1, x - 1, g = f + n - x + 1); T.upd1(1, 1, n, x + 1, n, g = f + 1);
	T.upd2(1, 1, n, 1, x - 1, g = f + x - 1); T.upd2(1, 1, n, x + 1, n, g = f + n - 1);
}

int main() {
	read(n, m, s); rer(i, 1, m, a);
	sort(a + 1, a + 1 + m, greater<>());
	T.build(1, 1, n); spread(s);
	rep1(i, 1, m) {
		int x = a[i].snd, y = x % n + 1, fx = T.query(1, 1, n, x), fy = T.query(1, 1, n, y);
		T.update2(1, 1, n, y, fx); T.update2(1, 1, n, x, fy);
		change(x); change(y); spread(x); spread(y);
	} T.print(1, 1, n);
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：0)

## [更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17860148.html)

很有意思的一道题。

设 $f_i$ 表示第 $i$ 根线的答案，首先有一个关键结论：任意两根相邻的线答案只差一定小于 $1$。原因显然，可以在无限远的地方加一根线来构造。该结论可以扩展一下，对于距离为 $d$ 的两根线，答案之差不会超过 $d$。

考虑进行倒着加线，考虑加了一根线会有什么影响：首先会把这两根线的答案交换，然后用上面的结论去更新答案。

对于交换的两根线，交换了之后不一定是最优解，可能可以用其他线的答案更新，这个东西似乎不太好高效维护。

但是事实上，只用左右相邻的两根线来更新代价就是对的。如果存在使用距离它大于等于 $2$ 的线来更新它的答案比和它相邻的线优秀，假设用来更新的线在此线的右边，则一定有：

$$ f_x+x-i>f_{i+1}+1 $$

移一下项，

$$ f_{i+1}-f_x>x-(i+1)$$

与结论相悖，所以原命题正确。接下来考虑用这两根线去更新其他线的答案。发现操作本质是对 $i\in [l,r]$ 的 $i$ 执行 $f_i=\min(f_i,k+i)$（或者 $i$ 的符号相反），可以直接 segment beats 维护。用 $tagl,tagr$ 分别表示左边和右边取 $\min$ 的最小值，下传标记的细节见代码。

```cpp
	int n,m,s;
	namespace Segment
	{
		struct{int l,r,tagl,tagr;}t[800010];
		inline void downl(int p,int tagl){t[p].tagl=min(t[p].tagl,tagl);}
		inline void downr(int p,int tagr){t[p].tagr=min(t[p].tagr,tagr);}
		inline void spread(int p)
		{
			downl(p*2,t[p].tagl),downl(p*2+1,t[p].tagl+t[p*2+1].l-t[p*2].l);
			downr(p*2+1,t[p].tagr),downr(p*2,t[p].tagr+t[p*2+1].r-t[p*2].r);
			t[p].tagl=t[p].tagr=INF;
		}
		void build(int p,int l,int r)
		{
			t[p].l=l,t[p].r=r,t[p].tagl=t[p].tagr=INF;
			if(l==r)return;
			int mid=l+((r-l)>>1);
			build(p*2,l,mid),build(p*2+1,mid+1,r);
		}
		int ask(int p,int x)
		{
			if(t[p].l==t[p].r)return min(t[p].tagl,t[p].tagr);
			return spread(p),x<=t[p*2].r?ask(p*2,x):ask(p*2+1,x);
		}
		void modifys(int p,int x,int y)
		{
			if(t[p].l==t[p].r)return t[p].tagl=t[p].tagr=y,void();
			spread(p);
			if(x<=t[p*2].r)modifys(p*2,x,y);else modifys(p*2+1,x,y);
		}
		void modifyl(int p,int x,int y)
		{
			if(x<=t[p].l)return downl(p,y+t[p].l-x);
			spread(p),modifyl(p*2+1,x,y);
			if(x<=t[p*2].r)modifyl(p*2,x,y);
		}
		void modifyr(int p,int x,int y)
		{
			if(x>=t[p].r)return downr(p,y+x-t[p].r);
			spread(p),modifyr(p*2,x,y);
			if(x>t[p*2].r)modifyr(p*2+1,x,y);
		}
		inline void change(int x,int y){modifyl(1,x,y),modifyr(1,x,y),modifyl(1,1,n-x+1+y),modifyr(1,n,x+y);}
	}
	using namespace Segment;
	pii a[500010];
	inline bool cmp(pii p1,pii p2){return p1.fi>p2.fi;}
	inline void mian()
	{
		read(n,m,s),build(1,1,n),change(s,0);
		for(int i=1;i<=m;++i)read(a[i]);
		sort(a+1,a+1+m,cmp);
		for(int i=1;i<=m;++i)
		{
			a[i].fi=a[i].se,a[i].se=a[i].fi%n+1;
			int lef=ask(1,a[i].fi),rig=ask(1,a[i].se);
			swap(lef,rig);
			modifys(1,a[i].fi,lef),modifys(1,a[i].se,rig);
			int Minl=ask(1,a[i].fi-1==0?n:a[i].fi-1);
			if(Minl+1<lef)modifys(1,a[i].fi,Minl+1);
			Minl=ask(1,a[i].se==n?1:a[i].se+1);
			if(Minl+1<rig)modifys(1,a[i].se,Minl+1);
			change(a[i].fi,lef),change(a[i].se,rig);
		}
		for(int i=1;i<=n;++i)write(ask(1,i),'\n');
	}
```

---

