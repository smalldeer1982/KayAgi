# [NEERC 2017] Archery Tournament

## 题目描述

你被邀请参加一年一度的射箭比赛。你将与来自整个北欧亚的最佳射手竞争。今年引入了一种新的比赛类型，射击场是动态的，新的目标可能会在任何时候出现。

由于射击场离你足够远，可以表示为一个二维平面，其中 $y = 0$ 是地面。有一些目标是圆形的，所有的目标都站在地面上。这意味着，如果一个目标的中心是 $(x, y) (y > 0)$，那么它的半径等于 $y$，以便它接触到 $y = 0$ 的线。在任何给定时刻，射击场上没有两个目标同时存在相交（但它们可能接触）。

最初，射击场是空的。你在这次比赛中的参与可以描述为 $n$ 个事件：要么一个新目标出现在射击场上，要么你在射击场的某个点射出一箭。要击中目标，你必须严格射入圆内（击中边界不算）。如果你射中并击中某个目标，那么该目标将从射击场上移除，你将获得一分。

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
8
1 0 12
2 -11 22
1 24 10
1 12 3
2 12 12
2 16 14
1 28 15
2 3 6
```

### 输出

```
-1
-1
3
1
```

# 题解

## 作者：a___ (赞：2)

由于这些圆都与 $x$ 轴相切且没有两圆相交，所以显然我们将这些圆全部投影到 $x$ 轴上后任意一个点最多会被 $\mathbf O (\log n)$ 个区间覆盖。所以我们每次只需要找到这 $\mathbf O (\log n)$ 个圆就好。   

考虑用线段树维护。每个节点开一个 `unordered_set`，每次修改向 $[x_i-y_i,x_i+y_i]$ 全部加入编号 $i$。查询的时候直接遍历途径的每个节点的 `unordered_set` 就好。修改的复杂度是 $\mathbf O(\log n)$ 的，查询的复杂度是 $\mathbf O(\log n+\log n)$ 的，所以总复杂度为 $\mathbf O(n\log n)$。   

代码：  
```cpp
#include<cstdio>
#include<unordered_set>
#include<algorithm>
const int N=2e5+10;
int n,t[N],x[N],y[N],a[N];
std::unordered_set<int>st[N<<2];
void update(int rt,int l,int r,int ql,int qr,int x)
{
	if(ql<=l&&r<=qr){x<0?(st[rt].erase(-x),0):(st[rt].insert(x),0);return;}
	int m=(l+r)>>1;
	if(ql<=m)update(rt<<1,l,m,ql,qr,x);
	if(qr>m)update(rt<<1|1,m+1,r,ql,qr,x);
}
void query(int rt,int l,int r,int p,int &ans)
{
	for(int i:st[rt])if(1ll*(x[p]-x[i])*(x[p]-x[i])+1ll*(y[p]-y[i])*(y[p]-y[i])<1ll*y[i]*y[i])ans=i;
	if(l==r)return; int m=(l+r)>>1;
	x[p]<=a[m]?query(rt<<1,l,m,p,ans):query(rt<<1|1,m+1,r,p,ans);
}
int main()
{
	int i,p;scanf("%d",&n);
	for(i=1;i<=n;i++)
	scanf("%d%d%d",&t[i],&x[i],&y[i]),a[i]=x[i];
	std::sort(a+1,a+1+n);
	for(i=1;i<=n;i++)
	t[i]==1?(update(1,1,n,std::lower_bound(a+1,a+1+n,x[i]-y[i])-a,std::upper_bound(a+1,a+1+n,x[i]+y[i])-a-1,i),0):
	(p=-1,query(1,1,n,i,p),printf("%d\n",p),(~p)&&(update(1,1,n,std::lower_bound(a+1,a+1+n,x[p]-y[p])-a,std::upper_bound(a+1,a+1+n,x[p]+y[p])-a-1,-p),0));
	return 0;
}
```

---

## 作者：MosTi25Falg (赞：1)

# P6952 [NEERC2017] Archery Tournament

[Luogo P6952](https://www.luogu.com.cn/problem/P6952)

## Solution

感性的想一下，感觉如果子弹能打中一个圆，那么这个圆的横坐标应该不会离这个子弹的横坐标太远。虽然这个想法对解题没什么用，但是可以启发我们按照 $x$ 坐标把所有圆拍扁到数轴上。

考虑一个子弹 $(x,y)$ 能击中圆 $(a,b)$ 的一个必要条件，显然需要有 $x\in[a-b,a+b]$。因此维护一个线段树，线段树上的每一个节点开一个 `set`，`set` 中存储能够完全覆盖当前区间的圆的编号。添加和删除圆相当于线段树的区间加减。查询操作就找到对应的节点遍历 `set` 中的圆，挨个判断是否能够覆盖当前询问点。

添加和删除的复杂度显然正确，考虑查询操作的复杂度。题目中提到任意时刻不存在两圆相交，感觉上一个点不会被太多的圆覆盖，考虑来证明这件事情。

![](https://cdn.luogu.com.cn/upload/image_hosting/crhwkou4.png)

不妨设小圆 $c$ 半径为 $1$，需要覆盖的位置是 $x=0$，圆都放在 $x=0$ 的左侧，那么圆 $d$ 的半径利用勾股定理可以解出 $r_d=2\sqrt 2 + 3$，也就是说如果要在一个小圆左侧再放一个大圆覆盖到 $x=0$，这个大圆的半径至少应当是小圆半径的 $2\sqrt 2 + 3$ 倍。也就是说，一个点被覆盖的次数是 $\mathcal O(\log n)$ 这一级别的。

因此可以证明出来查询的复杂度也是 $\mathcal O(\log n)$ 的，总时间复杂度 $\mathcal O(n\log n)$。

然后是关于代码的一些细节。如果直接使用动态开点线段树会获得 MLE 的成绩，因此需要离散化。并且线段树的区间添加可以使用标记永久化减小常数。

```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); ++i)
#define Rof(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
using i64 = long long;
using Ldouble = long double;
constexpr int _N = 2e5 + 5;
Ldouble Sq(int x) { return (Ldouble)x * x; }
struct Point {
	int x, y;
	Point(int x = 0, int y = 0) : x(x), y(y) {}
	Point operator - (const Point &A) const { return Point(x - A.x, y - A.y); }
	Ldouble Mod() { return sqrtl(Sq(x) + Sq(y)); }
};
int n;
struct Query { int opt, x, y; } qu[_N];
int lsh[_N], ltot;
set<int> s[_N << 2];
#define LC (k << 1)
#define RC (k << 1 | 1)
#define mid ((l + r) >> 1)
void Update(int k, int l, int r, int a, int b, int p, bool opt) {
	if (l >= a && r <= b)
		return opt ? void(s[k].insert(p)) : void(s[k].erase(p));
	if (a <= mid) Update(LC, l, mid, a, b, p, opt);
	if (b > mid) Update(RC, mid + 1, r, a, b, p, opt);
}
bool In(Point Cir, Point p) {
	return (p - Cir).Mod() < Cir.y;
}
int Find(int k, int l, int r, Point p) {
	for (int i : s[k])
		if (In(Point(lsh[qu[i].x], qu[i].y), Point(lsh[p.x], p.y)))
			return i;
	if (l == r) return -1;
	if (p.x <= mid) return Find(LC, l, mid, p);
	else return Find(RC, mid + 1, r, p);
}
void Modify(int i, bool opt) {
	int l = lower_bound(lsh + 1, lsh + ltot + 1, lsh[qu[i].x] - qu[i].y + 1) - lsh;
	int r = upper_bound(lsh + 1, lsh + ltot + 1, lsh[qu[i].x] + qu[i].y - 1) - lsh - 1;
	Update(1, 1, ltot, l, r, i, opt);
}
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	For(i, 1, n) {
		cin >> qu[i].opt >> qu[i].x >> qu[i].y;
		lsh[++ltot] = qu[i].x;
	}
	sort(lsh + 1, lsh + ltot + 1);
	ltot = unique(lsh + 1, lsh + ltot + 1) - lsh - 1;
	For(i, 1, n)
		qu[i].x = lower_bound(lsh + 1, lsh + ltot + 1, qu[i].x) - lsh;
	For(i, 1, n) {
		if (qu[i].opt == 1) Modify(i, 1);
		else {
			int id = Find(1, 1, ltot, { qu[i].x, qu[i].y });
			cout << id << '\n';
			if (~id) Modify(id, 0);
		}
	}
}
```



---

