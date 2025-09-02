# [GXOI/GZOI2019] 特技飞行

## 题目描述

公元 $9012$ 年，Z 市的航空基地计划举行一场特技飞行表演。表演的场地可以看作一个二维平面直角坐标系，其中横坐标代表着水平位置，纵坐标代表着飞行高度。

在最初的计划中，这 $n$ 架飞机首先会飞行到起点 $x = x_{st}$ 处，其中第 $i$ 架飞机在起点处的高度为 $y_{i,0}$。它们的目标是终点 $x = x_{ed}$ 处，其中第 $i$ 架飞机在终点处的高度应为 $y_{i,1}$。因此，每架飞机可以看作坐标系中的一个点，它的航线是从 $(x_{st},y_{i,0})$ 出发、到 $(x_{ed},y_{i,1})$ 结束的一条线段，如下图所示。

![aerobatics1.png](https://cdn.luogu.com.cn/upload/pic/56679.png)

这 $n$ 架飞机同时出发且始终保持一定的对地速度。因此，对于任意两条交叉的航线（线段），对应的两架飞机必然会同时到达交点处——这就是它们进行特技表演的时刻。它们将会偏转机翼，展现以极近的距离「擦身而过」特技，然后**继续保持各自的航线**。

航空基地最近还研究了一种新的特技「对向交换」。当两架飞机到达交点处时，之前正在下降的那架立即转为执行抬升动作，之前正在上升的那架则执行一次空翻，两架飞机一上一下、机腹对机腹，同样以极近的距离经过交点，然后**互相交换接下来的航线**。

我们不必关心特技动作在物理上究竟是如何实现的，飞机仍然看作一个点，在两种特技动作下，航线的变化如下图所示（$y_{i,1}'$ 表示交换航线后第 $i$ 架飞机在终点的新高度）。容易发现，「对向交换」会使它们的航线变为折线，并**保持它们在纵坐标上的相对顺序**；而「擦身而过」会**改变它们在纵坐标上的相对顺序**。

![aerobatics2.png](https://cdn.luogu.com.cn/upload/pic/56680.png)

现在，观看表演的嘉宾团提出了一个苛刻的要求——在终点 $x = x_{ed}$ 处，按照高度排序，$n$ 架飞机的相对顺序必须与 $x = x_{st}$ 处的相对顺序一致。嘉宾团还给「对向交换」特技和「擦身而过」特技分别评定了难度系数 $a$ 和 $b$，每次「对向交换」特技可以获得 $a$ 的分数，每次「擦身而过」特技可以获得 $b$ 的分数。

除此以外，嘉宾团共有 $k$ 名成员，第 $i$ 名成员会乘热气球停留在位置 $(p_i,q_i)$ 处，具有 $r_i$ 的观测距离，可以观测到区域 $|x - p_i| + |y - q_i| \le r_i$ 里的所有特技。  
若某个交点处的特技被**一名或多名**嘉宾观测到，则可以获得 $c$ 的额外加分。  
注意：**特技无论是否被观测到，均可以获得 $a$ 或者 $b$ 的得分**。

下图是对本题第一幅图 $4$ 条航线 $4$ 个交点的一种满足要求的安排，包括 $2$ 次「对向交换」、$2$ 次「擦身而过」，$3$ 项特技被观测到，得分 $2a + 2b + 3c$。为了方便观察，图中展现「对向交换」特技的交点稍稍有些分离。

![aerobatics3.png](https://cdn.luogu.com.cn/upload/pic/56681.png)

在这次的剧情里，你成为了 Z 市航空基地的规划员，你可以决定在每个交点处是执行「对向交换」还是「擦身而过」。你被要求在保证嘉宾团要求的前提下，计算整个特技表演的可能得到的最低和最高分数。

## 说明/提示

### 样例1解释

该样例的航线就是题目描述的图中所画的情况，只是嘉宾所在的位置稍有不同。  
最低得分的表演方案是在所有交点处均采用「对向交换」特技，得分 $4a + 3c = 13$。  
最高得分的表演方案与题目描述的图中所画的情况一致，得分 $2a + 2b + 3c = 15$。

### 数据范围

不存在三条或三条以上的线段交于同一点。  
所有坐标和 $r_i$ 均为 $5 \times 10^7$ 以内的非负整数。  
$y_{i,0} < y_{i + 1,0}$，$y_{i,1}$ 各不相同。  
$x_{st} < p_i < x_{ed},1 ≤ a,b,c ≤ 10^3$。

|测试点编号|$n,k$ 的规模|交点数的规模|约定|
|:-:|:-:|:-:|:-:|
|$1$|$n,k \le 15$|$\le 40$|无|
|$2$|$n,k \le 15$|$\le 40$|无|
|$3$|$n,k \le 15$|$\le 40$|无|
|$4$|$n,k \le 15$|$\le 40$|无|
|$5$|$n \le 30,000,k \le 100$|$\le 200,000$|无|
|$6$|$n \le 30,000,k \le 100$|$\le 200,000$|无|
|$7$|$n \le 30,000,k \le 100$|$\le 200,000$|无|
|$8$|$n \le 30,000,k \le 100$|$\le 200,000$|无|
|$9$|$n,k \le 100,000$|$\le 500,000$|$a = b$|
|$10$|$n,k \le 100,000$|$\le 500,000$|$a = b$|
|$11$|$n,k \le 100,000$|$\le 500,000$|$a = b$|
|$12$|$n,k \le 100,000$|$\le 500,000$|$a = b$|
|$13$|$n,k \le 50,000$|$\le 250,000$|无|
|$14$|$n,k \le 50,000$|$\le 250,000$|无|
|$15$|$n,k \le 50,000$|$\le 250,000$|无|
|$16$|$n,k \le 50,000$|$\le 250,000$|无|
|$17$|$n,k \le 100,000$|$\le 500,000$|无|
|$18$|$n,k \le 100,000$|$\le 500,000$|无|
|$19$|$n,k \le 100,000$|$\le 500,000$|无|
|$20$|$n,k \le 100,000$|$\le 500,000$|无|

## 样例 #1

### 输入

```
4 1 2 3 1 6
1 2 3 4
4 1 3 2
2
3 3 1
5 2 2```

### 输出

```
13 15```

## 样例 #2

### 输入

```
10 73 28 13 0 100
2 9 16 25 29 34 43 46 52 58
8 25 35 52 41 5 16 3 19 48
5
46 40 1
37 27 5
67 34 1
65 28 4
29 38 1```

### 输出

```
989 1619```

# 题解

## 作者：xht (赞：6)

题目地址：[P5302 [GXOI/GZOI2019]特技飞行](https://www.luogu.org/problemnew/show/P5302)

这里是官方题解（by lydrainbowcat）

### 题意

给 $10^5$ 条直线，给 $x = st$ 和 $x = ed$ 两个位置

在两条直线 $l1,l2$ 交点，可以交换 $l1,l2$ 接下来的部分（变成两条折线）

交换或不交换分别可以获得固定的分数 $a$ 和 $b$

另外有 $10^5$ 个观测点可以观测到一定范围内情况（曼哈顿距离），在观测范围内的点额外计分 $c$

要求最后在 $x = st$ 处和 $x = ed$ 处，直线保持相同的顺序

问如何交换可以获得最高的得分。保证交点小于等于 $5*10^5$ 个

### 解法

这其实是两个题的拼接

首先，若 $a>b$ ，说明交换越多越好。实际上所有交点都可以交换，因为交点个数恰好是逆序对数，所有逆序对都交换一下最后正好变成正序

若 $a<b$ ，交换次数为 $n - $ 置换数，因为每个置换之间的互相独立的，可以不参与交换。每个置换内部其实都等价于一个环（5-1-2-3-4这样的），交换次数为 $len-1$ ，故总次数为 $\sum\ (len - 1) = n - $ 置换数。

所有交点可以用类似于排序的方法 $O(n)$ 预处理，坐标转 $45$ 度

接下来就是若干个点（事件），还有若干个正方形（拆成两个事件）的扫描线问题

扫描线 + 树状数组即可

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#define MAX_NR 100010
const long double eps = 1e-9;
int N, A, B, C, ST_X, ED_X, M;

struct Point {
	long double x, y;
	Point() = default;
	Point(int x_, int y_) :
		x(x_), y(y_) {}
	Point(long double x_, long double y_) :
		x(x_), y(y_) {}
} point[MAX_NR * 2];

struct Event {
	long double x;
	int y0, y1, op;
	Event() = default;
	Event(int x_, int y0_, int y1_, int op_) :
		x(x_), y0(y0_), y1(y1_), op(op_) {}
	Event(long double x_, int y_) :
		x(x_), y0(y_), y1(y_), op(0) {}
	inline bool operator < (const Event &a) const {
		if (fabs(x - a.x) > eps) {
			return x < a.x;
		} else if (op != a.op) {
			return op > a.op;
		} else {
			return false;
		}
	}
};

std::vector<Point> inter;

inline Point get_intersection(Point a, Point b, Point c, Point d) {
	long double a1 = b.y - a.y;
	long double b1 = a.x - b.x;
	long double c1 = a1 * a.x + b1 * a.y;

	long double a2 = d.y - c.y;
	long double b2 = c.x - d.x;
	long double c2 = a2 * c.x + b2 * c.y;

	long double determinant = a1 * b2 - a2 * b1;

	if (determinant == 0) {
		return { -1, -1 };
	} else {
		long double x = (b2*c1 - b1 * c2) / determinant;
		long double y = (a1*c2 - a2 * c1) / determinant;
		return { x, y };
	}
}

namespace BIT {

	int N;
	int b[MAX_NR * 20];

	void init(int n) {
		N = n;
		memset(b, 0, sizeof(b));
	}

	int query(int x) {
		int res = 0;
		for (int i = x; i > 0; i -= i & (-i)) {
			res += b[i];
		}
		return res;
	}

	void update(int x, int v) {
		for (int i = x; i <= N; i += i & (-i)) {
			b[i] += v;
		}
	}
}

bool cmp(int i,int j) {
	return point[N + i].y < point[N + j].y;
}

int main() {
	scanf("%d%d%d%d%d%d", &N, &A, &B, &C, &ST_X, &ED_X);
	for (int i = 0, x, y; i < N * 2; ++i) {
		scanf("%d", &y);
		x = (i < N ? ST_X : ED_X);
		point[i] = { x, y };
	}

	std::vector<int> p(N), rank(N), a(N), v(N);
	for (int i = 0; i < N; ++i) {
		a[i] = rank[i] = i;
		v[i] = 0;
	}

	std::sort(rank.begin(), rank.end(), cmp);

	for (int i = 0; i < N; ++i) {
		p[rank[i]] = i;
	}

	int nr_cross = N;
	for (int i = 0; i < N; ++i) {
		if (v[i]) continue;
		nr_cross--;
		int x = p[i];
		while (x != i) {
			v[x] = 1;
			x = p[x];
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = i; ; ++j) {
			if (i == p[j]) {
				int aj = a[j];
				for (int k = j - 1; k >= i; --k) {
					Point cur = get_intersection(
					                point[a[k]], point[a[k] + N],
					                point[aj], point[aj + N]);
					inter.push_back(Point(cur.x + cur.y, cur.x - cur.y));
					std::swap(p[k], p[k + 1]);
					a[k + 1] = a[k];
				}
				break;
			}
		}
	}

	scanf("%d", &M);
	std::vector<long double> Y(M * 2 + inter.size());
	std::vector<Event> events(M * 2 + inter.size());
	for (int i = 0, x, y, r; i < M; ++i) {
		scanf("%d%d%d", &x, &y, &r);
		int x_ = x, y_ = y;
		x = x + y, y = x_ - y_;
		events[i] = { x - r, y - r, y + r, 1 };
		events[i + M] = { x + r, y - r, y + r, -1 };
		Y[i] = y - r;
		Y[i + M] = y + r;
	}
	for (int i = 0; i < inter.size(); ++i) {
		Y[2 * M + i] = inter[i].y;
	}
	std::sort(Y.begin(), Y.end());
	// Y.resize(std::unique(Y.begin(), Y.end()) - Y.begin());
	int pos = 0;
	for (int i = 0; i < Y.size(); i++)
		if (i == 0 || fabs(Y[i] - Y[i - 1]) > eps) Y[pos++] = Y[i];
	Y.resize(pos);
	for (int i = 0; i < 2 * M; ++i) {
		events[i].y0 = std::lower_bound(Y.begin(), Y.end(), events[i].y0) - Y.begin() + 1;
		events[i].y1 = std::lower_bound(Y.begin(), Y.end(), events[i].y1) - Y.begin() + 1;
	}
	for (int i = 0; i < inter.size(); ++i) {
		int y = std::lower_bound(Y.begin(), Y.end(), inter[i].y) - Y.begin() + 1;
		events[2 * M + i] = { inter[i].x, y };
	}
	std::sort(events.begin(), events.end());

	int nr_observed = 0;
	BIT::init(2 * Y.size());
	for (int i = 0; i < events.size(); i++) {
		Event e = events[i];
		if (e.op) {
			BIT::update(e.y0, e.op);
			BIT::update(e.y1 + 1, -e.op);
		} else {
			nr_observed += BIT::query(e.y0) > 0;
		}
	}

	int nr_inv = inter.size();
	int score_observed = nr_observed * C;
	int max_score = A * nr_inv;
	int min_score = A * nr_cross + B * (nr_inv - nr_cross);
	if (A < B) {
		std::swap(min_score, max_score);
	}
	std::cout << min_score + score_observed << ' ' << max_score + score_observed << std::endl;
	return 0;
}
```

---

## 作者：cosmicAC (赞：4)

这道题显然是由三个部分组成的：
1. 找到所有的直线交点
2. 统计每一个点是否被矩形覆盖
3. 决定【擦身而过】特技的最多次数

首先是部分一，容易观察到$y_{x,1}$数组的每一个逆序对对应一个交点。所以只要CDQ或者set求出所有的逆序对，然后写一个直线求交点即可。直接上计算几何板子即可。由于此题中的斜率不会是$\infty$，所以也可以解析暴力。

然后是部分二，这里不需要kd-tree或者树套树。可以先把坐标系转$45\degree$，即$(x,y)\rightarrow(x+y,y-x)$，然后就变成了矩形加单点求和。可以差分，就变成了单点加矩形求和。于是可以离线+扫描线，用一个线段树或BIT维护即可。此处要注意实数坐标的精度误差。

最后是部分三，首先可以注意到，每次两条航线相交就相当于交换一个排列中的相邻两个数。所以可以把所有交点按照从左往右顺序写成一个序列，比如$[(1,2),(2,3),(3,4),(2,3),(1,2)]$。我首先想到的是一个假算法，把每个数对的第一次出现当成左括号，第二次当成右括号，比如刚才的序列就写成`([{])`。然后消去尽量多构成合法括号序列的括号对。可惜这样做是有反例的，比如下面的图。

![](https://i.loli.net/2019/04/16/5cb59c77e5272.png
)

交点序列是$[(1,2),(2,3),(3,4),(1,2),(4,5),(2,3),(1,2),(3,4),(2,3)]$，然而最优解是消去$[(1,2),(2,3),(1,2),(2,3),(1,2),(2,3)]$。

就在手工模拟这个反例的时候，我发现了一些规律：貌似**左侧最上方的点和右侧最上方的点之间的折线最多只会有两段**。于是我可以把这两段消去，把剩下的半段折线强行掰直。比如上面的图第一次消去之后是这样的
![](https://i.loli.net/2019/04/16/5cb59ec1d392e.png)

每次掰直一段折线时，【对向交换】的次数加1。然后似乎贪心的递归下去做就是对的了。**本人无法证明其正确性。**

代码如下：
```cpp
#include<bits/stdc++.h>
#define eps 1e-12
using namespace std;
using ll=long long;
const int maxn=1<<20;
struct point{double x,y;};
point operator-(point a,point b){return{a.x-b.x,a.y-b.y};}
point operator+(point a,point b){return{a.x+b.x,a.y+b.y};}
point operator*(double a,point b){return {b.x*a,b.y*a};}
double operator*(point a,point b){return a.x*b.y-a.y*b.x;}
point jd(point a,point b,point c,point d){
	return a+((c-a)*(d-c))/((b-a)*(d-c))*(b-a);
}
struct segTree{
	int a[1<<24],L[1<<24],R[1<<24],tot,rt;
	void ins(int x,int v,int&p,int tl=-2e8,int tr=2e8){
		if(!p)p=++tot;
		if(tl==tr){a[p]+=v;return;}
		int mid=tl+tr>>1;
		if(x<=mid)ins(x,v,L[p],tl,mid);else ins(x,v,R[p],mid+1,tr);
		a[p]=a[L[p]]+a[R[p]];
	}
	int qry(int l,int r,int p=1,int tl=-2e8,int tr=2e8){
		if(l<=tl&&tr<=r)return a[p];
		int mid=tl+tr>>1,re=0;
		if(l<=mid)re=qry(l,r,L[p],tl,mid);
		if(r>mid)re+=qry(l,r,R[p],mid+1,tr);
		return re;
	}
}tr;
int n,A,B,C,x0,x1,k,Y0[maxn],m,rnk[maxn],sa[maxn];
ll ans;
struct st{int v,id;}a[maxn],b[maxn];
struct ev{double x,y;int tp,vl;};vector<ev> e;
void cdq(int l,int r){
	if(l==r)return;
	int mid=l+r>>1; cdq(l,mid),cdq(mid+1,r);
	int i=l,j=mid+1,k=0;
	while(i<=mid||j<=r)
		if(j>r||i<=mid&&a[i].v<a[j].v){
			for(int t=mid+1;t<j;t++,m++){
				point p=jd({x0,Y0[a[i].id]},{x1,a[i].v},
				{x0,Y0[a[t].id]},{x1,a[t].v});
				e.push_back({p.x+p.y,p.y-p.x,1,0});
			}
			b[++k]=a[i++];
		}else b[++k]=a[j++];
	copy(b+1,b+1+k,a+l);
}
int main(){
	scanf("%d%d%d%d%d%d",&n,&A,&B,&C,&x0,&x1);
	for(int i=1;i<=n;i++)scanf("%d",Y0+i),sa[i]=i;
	for(int i=1,x;i<=n;i++)scanf("%d",&x),a[i]={x,i};
	sort(sa+1,sa+1+n,[](int x,int y){return a[x].v<a[y].v;});
	for(int i=1;i<=n;i++)rnk[sa[i]]=i;
	scanf("%d",&k);
	while(k--){
		int p,q,r;scanf("%d%d%d",&p,&q,&r);
		e.insert(e.end(),{
			{p+q-r-eps,q-r-p,0,1},{p+q-r-eps,q+r-p,0,-1},
			{p+q+r+eps,q-r-p,0,-1},{p+q+r+eps,q+r-p,0,1}});
	}
	cdq(1,n);
	sort(e.begin(),e.end(),[](ev a,ev b){return a.x<b.x;});
	for(ev&x:e)if(!x.tp)tr.ins(x.y,x.vl,tr.rt);else
		if(tr.qry(-2e8,floor(x.y-eps)))ans+=C;
	//此处必须要floor，因为把double转成int默认是向零取整
	ll x=1ll*m*A+ans;int cnt=0;
	for(int i=1;i<=n;i++){
		int p=rnk[i],q=sa[i];
		if(p!=i){
			sa[p]=q,rnk[q]=p;
			cnt++;
		}
	}
	ll y=1ll*cnt*A+1ll*(m-cnt)*B+ans;
	printf("%lld %lld\n",min(x,y),max(x,y));
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

## Preface

缝合题刺激。

好欸，[黄题 逆序对](https://www.luogu.com.cn/problem/P1908) $+$ [蓝题【模板】扫描线](https://www.luogu.com.cn/problem/P5490) $=$ 本黑题。

## Analysis

发现 特技飞行的得分 和 嘉宾观测的得分 可以分开算。

### 特技飞行得分

这部分的得分不是固定的。

我们先算出交叉点个数（逆序对思想）。

#### 「对向交换」最多

即所有交叉点都是「对向交换」。

#### 「对向交换」最少

将飞行员按起点高度排序，他们终点高度 rank 的排列设为 $p_1,p_2,\dots,p_n$。

设 $cy$ 为 $\{p\}$ 置换环的个数。

「对向交换」最少 $n-cy$ 个。因为手玩一下发现每一个置换环（设个数为 $len$）至少要 $len-1$ 次「对向交换」。证明不难。

### 嘉宾观测得分

这部分的得分是固定的。

发现嘉宾观测范围就是一个斜 $45^{\circ}$ 的正方形，我们用矩阵乘法将坐标系旋转 $45^{\circ}$，就是模板扫描线了。

扫描线甚至可以用树状数组。

## Code

（丑死，但是还是贴了）

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define int long long
#define N 100003
#define M 500010
#define db double
#define Pos pair<db,db>
#define low (x&(-x))
//P5302 [GXOI/GZOI2019]????
const db inf=1e16;
const db eps=1e-6;
const db sq2=(db)1.4142135623730950488016887242097;
const db cs=sq2/2;
const db sn=-cs;
int n,m,q,A,B,C,a1,a2,ans;
db S,T;
pair<int,int> a[N],b[N];
int c[N],d[N];
namespace scl{
	Pos ext=mkp(inf,-inf);
	vector<Pos> inter;
	vector<pair<Pos,db> > obs;
	vector<pair<pair<db,bool>,Pos> > line;
	db v[M];
	int tot=0;
	int c[M];
	void add(int x,int y){
		while(x<=tot){
			c[x]+=y;
			x+=low;
		}
	}
	int que(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=low;
		}
		return res;
	}
	void init(){
		ext=mkp(inf,-inf);
		for(auto &i:inter){
			Pos j=i;
			i.fir=j.fir*cs-j.sec*sn;
			i.sec=j.fir*sn+j.sec*cs;
			ckmn(ext.fir,i.fir);
			ckmx(ext.sec,i.fir);
		}
		for(auto &i:obs){
			Pos j=i.fir;
			i.fir.fir=j.fir*cs-j.sec*sn;
			i.fir.sec=j.fir*sn+j.sec*cs;
			i.sec*=sq2/2;
			i.sec+=eps;
		}
		db l,r; 
		for(auto i:obs){
			l=i.fir.fir-i.sec;r=i.fir.fir+i.sec;
			if(r<ext.fir-eps || l>ext.sec+eps) continue;
			line.pb(mkp(mkp(i.fir.sec-i.sec,1),mkp(l,r)));
			line.pb(mkp(mkp(i.fir.sec+i.sec,0),mkp(l,r)));
		}
//		cerr<<"s_inter:"<<endl; for(auto i:inter) cerr<<i.fir<<" "<<i.sec<<endl;
//		cerr<<"s_obs:"<<endl; for(auto i:obs) cerr<<i.fir.fir<<" "<<i.fir.sec<<" "<<i.sec<<endl;
//		cerr<<"Line:"<<endl; for(auto i:line) cerr<<i.fir.fir<<" "<<i.fir.sec<<" "<<i.sec.fir<<" "<<i.sec.sec<<endl;
	}
	void lisan(){
		for(auto i:inter) v[++tot]=i.fir;
		sort(v+1,v+1+tot);
		tot=unique(v+1,v+1+tot)-v-1;
//		cerr<<"%%% ";For(i,1,tot) cerr<<v[i]<<" "; cerr<<endl;
		for(auto &i:inter) i.fir=lower_bound(v+1,v+1+tot,i.fir)-v;
		for(auto &i:line){
			i.sec.fir=lower_bound(v+1,v+1+tot,i.sec.fir)-v;
			i.sec.sec=upper_bound(v+1,v+1+tot,i.sec.sec)-v-1;
		}
	}
	bool cmp(Pos x,Pos y){return x.sec<y.sec;}
	int work(){
		int res=0;
		init();
		lisan();
		sort(inter.begin(),inter.end(),cmp);
		sort(line.begin(),line.end());
//		cerr<<"s_l_inter:"<<endl; for(auto i:inter) cerr<<i.fir<<" "<<i.sec<<endl;
//		cerr<<"l_Line:"<<endl; for(auto i:line) cerr<<i.fir.fir<<" "<<i.fir.sec<<" "<<i.sec.fir<<" "<<i.sec.sec<<endl;
		auto pos=line.begin();
		tot++;
//		cerr<<"work"<<endl;
		for(auto i:inter){
			while(pos!=line.end() && pos->fir.fir<i.sec){
				add(pos->sec.fir,(pos->fir.sec?1:-1));
				add(pos->sec.sec+1,(pos->fir.sec?-1:1));
				pos=next(pos);
			}
			assert(que(i.fir)>=0);
//			cerr<<i.fir<<" "<<i.sec<<" "<<que(i.fir)<<endl;
			if(que(i.fir)>0) res++;
		}
		return res;
	}
}
int e[N];
bool v[N]; 
inline Pos ckpos(int x,int y){
	Pos xx=a[x],yy=a[y];
	double res=(yy.fir-xx.fir)*(T-S)/((xx.sec-xx.fir)-(yy.sec-yy.fir))+S;
	return mkp(res,xx.fir+(xx.sec-xx.fir)/(T-S)*(res-S));
}
inline int ms(int l,int r){
	if(l>=r) return 0;
	int mid=(l+r)>>1,res=ms(l,mid)+ms(mid+1,r),tl=l,tr=mid+1,tot=l;
	while(tl<=mid || tr<=r){
		if(tr>r || (tl<=mid && c[tl]<c[tr])){
			res+=tr-mid-1;
			For(i,mid+1,tr-1) scl::inter.pb(ckpos(c[tl],c[i]));
			d[tot++]=c[tl++]; 
		}else{
			d[tot++]=c[tr++];
		}
	}
	For(i,l,r) c[i]=d[i];
//	cerr<<l<<" "<<r<<":"<<res<<endl;
	return res;
}
inline int out(int x){return x*A+(m-x)*B;}
inline void see(int x){
	v[x]=1;
	if(!v[e[x]]) see(e[x]);
}
signed main(){IOS;
	cin>>n>>A>>B>>C>>S>>T;
	For(i,1,n) cin>>a[i].fir;
	For(i,1,n) cin>>a[i].sec;
	//a1
	sort(a+1,a+1+n);
	For(i,1,n) b[i]=mkp(a[i].sec,i);
	sort(b+1,b+1+n);
	For(i,1,n) e[i]=c[i]=b[i].sec;
//	cerr<<fixed<<setprecision(3);
//	cerr<<"c: "; For(i,1,n) cerr<<c[i]<<" "; cerr<<endl;
	a1=ms(1,n);
	m=scl::inter.size();
//	cerr<<"a1:"<<a1<<endl;
//	cerr<<"inter "<<m<<":"<<endl;for(auto i:(scl::inter)) cerr<<i.fir<<" "<<i.sec<<endl;
	//a2
	a2=n;
	For(i,1,n) if(!v[i]){see(i);a2--;}
//	cerr<<"a2:"<<a2<<endl;
	//ans
	cin>>q;
	scl::obs.resize(q);
	for(auto &i:(scl::obs)) cin>>i.fir.fir>>i.fir.sec>>i.sec;
	ans=scl::work();
	a1=out(a1);a2=out(a2);
	cout<<min(a1,a2)+ans*C<<" "<<max(a1,a2)+ans*C<<endl;
return 0;}
```

---

## 作者：crashed (赞：2)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/P5302)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于交叉点的位置，交叉点选择特技和嘉宾的$bonus$是互相独立的，所以说这道题其实是三个问题强行凑成的。一部分是计算交叉点数量和位置，一部分是给每一个交叉点选择特技，还一部分是二维数点、计算$bonus$的问题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;第一步，我们需要求出来交叉点的数量和坐标。不难发现，由于$x_{st}$的位置上的$y_0$坐标都已经排好序了，一个交点实际上就对应着$y_1$坐标的一个逆序对。所以统计数量就变成了常规的问题。计算位置也很简单。用一个$set$维护当前位置之前的$y_1$，每次$lower\_bound$一下，找到$set$里面$y_1$比自己的$y_1$大的那些飞行路线，也就是会与自己出现交点的那些路线，于是便可以计算交点。你可以选择用斜率法或者向量法。推荐使用斜率，操作简单，并且这里$x_{st}<x_{ed}$，所以斜率法不会出问题。这一部分的时间为$O(n\log_2n)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;第二步，给每一个交叉点选择特技。设特技的总贡献为$W$，选择了$x$个交点进行【对向交换】的特技，总共有$t$个交点，那么可以列出$W$与$x$的函数关系式为：  
$$W=ax+b(t-x)=(a-b)x+bt$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;暂时不考虑定义域的问题。可以发现，$W$和$x$是一次函数的关系，所以我们考虑$x$可取到的最值，也就对应了$W$可取到的最值。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;第一，显然$x\le t$。并且$x=t$的取值是合法的。有两种理解方式，一种可以理解为，逆序对都被交换完了，自然就是有序的；另一种，由于一次【对向交换】的特技不会改变两架飞机的上下关系，最开始是有序的，最后自然还是有序的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（这一部分的理解借鉴自[洛水·锦衣卫的博客](https://www.luogu.com.cn/blog/Vsinger/solution-p5302)，感谢）  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;第二，考虑$x$的最小取值。不难发现，其实每一架飞机的最终位置都是确定的。设第$i$架飞机的最终位置上原本的航线对应着$tar_{i}$号飞机（比如，题目中的例子，$tar_1=2$）。我们设计一个图，每个节点代表一架飞机。节点$i$连出去一条指向节点$tar_i$的边，表示最终要和它换位置。不难发现，最后这个图会变成多个环。在一个长度为$k$的环中，要想将它变成合法的顺序，至少需要进行$k-1$次交换。也就是说，最开始最少交换次数为$n$，出现一个环，最少交换的次数就可以少$1$。所以$x$的最小取值为$n-\text{环数}$。这一部分的时间为$O(n)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;第三步，计算每一个嘉宾的$bonus$。这是一个经典的二维数点的问题，我们用扫描线解决。首先把坐标轴旋转$45^\circ$，再放大$\sqrt 2$倍。这样操作之后答案显然不会改变。这是原来坐标轴上点$(x,y)$，在新的坐标轴中位置就变成了$(x+y,y-x)$。然后对于横坐标离散化之后用$BIT$维护，纵坐标用来排序。对于一个正方形，将它拆分成两个操作，下边界看作向$BIT$中插入一条边，上边界看作删除一条边。一个点就是一个查询，即查询$BIT$里面有没有线段覆盖到它。时间是$O((n+4k)\log_2(n+4k))$（主要是离散化最花时间）。 
# 代码
```cpp
#include <set>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> ele;
typedef pair<double, double> coord;

const int MAXN = 1e5 + 5, MAXK = 1e5 + 5, MAXJ = 5e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
   	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

struct oper
{
	double y;
	int type, a, b;
	bool operator < ( const oper & other ) const 
	{ return y == other.y ? ( type == other.type ? a < other.a : type < other.type ) : y < other.y; }
}os[MAXJ + MAXK * 2];

struct node
{
	double a; int indx, side;
	node(){} node( const double A, const int I, const int S ) { a = A, indx = I, side = S; }
	bool operator < ( const node & other ) const { return a < other.a; }
};

set<ele> s;

node disc[MAXJ + MAXK * 4];
coord junc[MAXJ];

int BIT[MAXJ + MAXK * 2];
int p[MAXK], q[MAXK], r[MAXK];
int sty[MAXN], edy[MAXN], tar[MAXN];
int N, K, A, B, C, siz, stX, edX, cnt;
bool visited[MAXN];

int lowbit( const int x ) { return x & ( -x ); }
void upt( const int x, const int v ) { for( int i = x ; i <= siz ; i += lowbit( i ) ) BIT[i] += v; }
int getSum( const int x ) { int ret = 0; for( int i = x ; i ; i -= lowbit( i ) ) ret += BIT[i]; return ret; }
void update( const int l, const int rr, const int v ) { upt( l, v ), upt( rr + 1, -v ); }
int query( const int l, const int rr ) { return getSum( rr ) - getSum( l - 1 ); } 

coord junct( const int a, const int b )
{
	double k1 = 1.0 * ( edy[a] - sty[a] ) / ( edX - stX ), b1 = sty[a] - k1 * stX;
	double k2 = 1.0 * ( edy[b] - sty[b] ) / ( edX - stX ), b2 = sty[b] - k2 * stX;
	double xx = ( b2 - b1 ) / ( k1 - k2 );
	return coord( xx, k1 * xx + b1 );
}

void DFS( const int u )
{
	if( visited[u] ) return ;
	visited[u] = true, DFS( tar[u] );
}

int main()
{
	int rmn, rmx, ra, rb;
	read( N ), read( A ), read( B ), read( C ), read( stX ), read( edX );
	for( int i = 1 ; i <= N ; i ++ ) read( sty[i] );
	for( int i = 1 ; i <= N ; i ++ ) read( edy[i] );
	read( K );
	for( int i = 1 ; i <= K ; i ++ ) read( p[i] ), read( q[i] ), read( r[i] );
	for( int i = 1 ; i <= N ; i ++ )
	{
		set<ele> :: iterator it = s.lower_bound( ele( edy[i], i ) );
		for( ; it != s.end() ; it ++ ) 
			junc[++ cnt] = junct( it->second, i );
		s.insert( ele( edy[i], i ) );
	}
	ra = cnt * A;
	int indx = 0, tot = 0;
	for( set<ele> :: iterator it = s.begin() ; it != s.end() ; it ++ ) tar[++ indx] = it->second;
	for( int i = 1 ; i <= N ; i ++ ) if( ! visited[i] ) DFS( i ), tot ++;
	rb = ( N - tot ) * A + ( cnt - N + tot ) * B, tot = 0;
	rmn = MIN( ra, rb ), rmx = MAX( ra, rb );
	for( int i = 1 ; i <= cnt ; i ++ ) 
	{
		disc[++ tot] = node( junc[i].first + junc[i].second, i, 0 );
		os[i].type = 1, os[i].y = junc[i].second - junc[i].first;
	}
	for( int i = 1, cur ; i <= K ; i ++ )
	{
		cur = ( i << 1 ) + cnt - 1;
		disc[++ tot] = node( p[i] + q[i] - r[i], cur, 0 ); // (p[i], q[i] - r[i])
		disc[++ tot] = node( p[i] + r[i] + q[i], cur, 1 ); // ( p[i] + r[i], q[i] )
		os[cur].type = 0, os[cur].y = q[i] - r[i] - p[i];
		cur = ( i << 1 ) + cnt;
		disc[++ tot] = node( p[i] - r[i] + q[i], cur, 0 ); // ( p[i] - r[i], q[i] )
		disc[++ tot] = node( p[i] + q[i] + r[i], cur, 1 ); // ( p[i], q[i] + r[i] )
		os[cur].type = 2, os[cur].y = q[i] + r[i] - p[i];
	}
	int all = ( K << 1 ) + cnt, rest = 0;
	std :: sort( disc + 1, disc + 1 + tot );
	disc[0].a = -0x3f3f3f3f;
	for( int i = 1 ; i <= tot ; i ++ )
	{
		if( disc[i].a != disc[i - 1].a ) siz ++;
		( disc[i].side ? os[disc[i].indx].b : os[disc[i].indx].a ) = siz;
	}
	std :: sort( os + 1, os + 1 + all );
	for( int i = 1 ; i <= all ; i ++ )
	{
		if( os[i].type == 0 ) update( os[i].a, os[i].b, 1 );
		else if( os[i].type == 1 ) 
		{
			int val = getSum( os[i].a );
			rest += bool( val ) * C;
		}
		else if( os[i].type == 2 ) update( os[i].a, os[i].b, -1 );
	}
	write( rmn + rest ), putchar( ' ' ), write( rmx + rest ), putchar( '\n' );
	return 0;
}
```

---

## 作者：洛水·锦依卫 (赞：1)

# Mentality

考场上打的全是麻烦的算法 .jpg 。

$step1:$

首先发现，由于交点数不多，显然先求交点。对于两条线段，它们相交当且仅当左端点纵坐标的大小关系和右端点相反。

由于题目按照左端点纵坐标单调递增给出，直接用一个 $set$ 维护已给出的右端点纵坐标集合，对于新线段暴力扫一遍 $set$ 中的线段，看是否相交。

求交点其实很简单，利用斜率就好了。

奈何我选择了叉积 $(???)$，我也觉得自己挺迷的。

$step2:$

对于每个嘉宾，直接将嘉宾和交点坐标转换成切比雪夫意义下的坐标，二维数点即可。

这里使用扫描线二维数点。

$step3:$

接下来剩下的是翻折操作。

不难发现，由于 $a,b$ 有明确的大小关系，所以两个极端答案肯定是尽量多选 $a$ 和尽量少选 $a$ 。

对于尽量多选 $a$ ，也就是翻折操作，我们发现其实可以所有操作全部翻折，最后到右边之后，一定会是有序的。

这个有两种理解方式：

一、交点数等价于逆序对数，一次翻折就相当于扭回去了一对逆序对，当我们将所有逆序对都扭回去之后，序列不存在逆序对，即结果有序。

二、题面中有提到：一次翻折操作会使两架飞机仍保持相对位置不变。那么我们每次都进行翻折，始终不会有任意两架飞机交换位置，所以最后结果有序。

对于尽量少选 $a$ ，我们将每个飞机 $i$ 和它的目的地 $p_i$ 相连，就会得到一张只存在简单环的图。

不难发现，对于一个环，设其中元素分别为 $a_1\sim a_n$ 它的形式如下：

$\forall_{i=1}^{n-1}p_{a_i}=a_{i+1}$

$p_{a_n}=a_1$

由于交换元素仅针对逆序对，所以要将环整体位移一位最少也就需要环长减一的次数。

所以 $a$ 的最少选择次数为所有环的环长减一之和。

没了。

# Code

考场的时候脑子比较乱，代码也就打得长了。我也不知道我为什么码出了 $5k$

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 1e5 + 5;
int n, a, b, c, K, ans;
int cnt, cc;
LL Ans1, Ans2;
double xs, xe, ys[Max_n], ye[Max_n];
struct dots {
  double x, y;
} k[Max_n * 5];
struct xl {
  double x, y;
  double operator*(const xl &b) { return x * b.y - b.x * y; }
};
set<pair<double, double> > s;
set<pair<double, double> >::iterator it;
inline bool cmp(dots a, dots b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
inline void part1() {
  n = read(), a = read(), b = read(), c = read(), xs = read(), xe = read();
  for (int i = 1; i <= n; i++) ys[i] = read();
  double D = xe - xs;
  for (int i = 1; i <= n; i++) {
    ye[i] = read();
    it = s.end();
    if (s.size()) it--;
    while ((*it).first > ye[i] && it != s.begin()) {
      cnt++;
      xl d1 = (xl){-D, ys[i] - (*it).first}, d2 = (xl){0, ye[i] - (*it).first};
      double S1 = abs(d1 * d2);
      d1 = (xl){D, ye[i] - (*it).second}, d2 = (xl){0, ys[i] - (*it).second};
      double S2 = abs(d1 * d2);
      double K = S2 / (S1 + S2), D1 = (*it).first - (*it).second;
      k[cnt].x = xs + D * K, k[cnt].y = (*it).second + K * D1;
      it--;
    }
    if (it == s.begin())
      if ((*it).first > ye[i]) {
        cnt++;
        xl d1 = (xl){-D, ys[i] - (*it).first},
           d2 = (xl){0, ye[i] - (*it).first};
        double S1 = abs(d1 * d2);
        d1 = (xl){D, ye[i] - (*it).second}, d2 = (xl){0, ys[i] - (*it).second};
        double S2 = abs(d1 * d2);
        double K = S2 / (S1 + S2), D1 = (*it).first - (*it).second;
        k[cnt].x = xs + D * K, k[cnt].y = (*it).second + K * D1;
      }
    s.insert(make_pair(ye[i], ys[i]));
  }
  for (int i = 1; i <= cnt; i++) {
    double X = k[i].x, Y = k[i].y;
    k[i].x = X + Y, k[i].y = X - Y;
  }
  sort(k + 1, k + cnt + 1, cmp);
}
double z[Max_n << 4];
int C[Max_n << 3];
int cntr, hd[Max_n], nx[Max_n << 1], to[Max_n << 1];
struct que {
  double pos;
  double l, r, L, R;
  int id, t;
} q[Max_n << 3];
struct person {
  double x, y, r;
} p[Max_n];
inline bool cmp2(que a, que b) {
  return a.pos == b.pos ? a.t < b.t : a.pos < b.pos;
}
inline void add(int k, int x) {
  for (int i = k; i <= cc; i += i & -i) C[i] += x;
}
inline int query(int k) {
  int ans = 0;
  for (int i = k; i; i -= i & -i) ans += C[i];
  return ans;
}
inline void part2() {
  K = read();
  for (int i = 1; i <= K; i++) {
    p[i].x = read(), p[i].y = read(), p[i].r = read();
    double X = p[i].x, Y = p[i].y;
    p[i].x = X + Y, p[i].y = X - Y;
  }
  int Cnt = 0;
  for (int i = 1; i <= K; i++) {
    Cnt++;
    q[Cnt].l = p[i].x - p[i].r, q[Cnt].r = p[i].x + p[i].r;
    q[Cnt].L = p[i].y - p[i].r, q[Cnt].R = p[i].y + p[i].r;
    q[Cnt].t = 1, q[Cnt + 1] = q[Cnt], q[Cnt + 1].t = 3;
    q[Cnt].pos = q[Cnt].l, q[++Cnt].pos = q[Cnt].r;
    z[++cc] = q[Cnt].L, z[++cc] = q[Cnt].R;
    q[Cnt].id = q[Cnt - 1].id = i;
  }
  for (int i = 1; i <= cnt; i++) {
    Cnt++, q[Cnt].pos = k[i].x, q[Cnt].l = k[i].y, q[Cnt].t = 2;
    z[++cc] = q[Cnt].l;
  }
  sort(q + 1, q + Cnt + 1, cmp2);
  sort(z + 1, z + cc + 1);
  for (int i = 1; i <= Cnt; i++) {
    if (q[i].t == 1) {
      int x = lower_bound(z + 1, z + cc + 1, q[i].R) - z;
      int y = lower_bound(z + 1, z + cc + 1, q[i].L) - z;
      add(y, 1), add(x + 1, -1);
    }
    if (q[i].t == 3) {
      int x = lower_bound(z + 1, z + cc + 1, q[i].R) - z;
      int y = lower_bound(z + 1, z + cc + 1, q[i].L) - z;
      add(y, -1), add(x + 1, 1);
    }
    if (q[i].t == 2) {
      int x = lower_bound(z + 1, z + cc + 1, q[i].l) - z;
      if (query(x)) ans++;
    }
  }
  Ans1 += 1ll * ans * c, Ans2 += 1ll * ans * c;
  Ans1 += 1ll * a * cnt;
}
int num[Max_n], P[Max_n];
int top, tim, dfn[Max_n], low[Max_n], vis[Max_n], stk[Max_n];
int size[Max_n], bel[Max_n], cir;
bool cmp3(int a, int b) { return ye[a] < ye[b]; }
void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
void dfs(int x) {
  stk[++top] = x, dfn[x] = low[x] = ++tim, vis[x] = 1;
  go(x, i, v) if (!vis[v]) dfs(v), low[x] = min(low[x], low[v]);
  else if (vis[v] == 1) low[x] = min(low[x], dfn[v]);
  if (dfn[x] == low[x]) {
    cir++;
    while (stk[top] != x)
      bel[stk[top]] = cir, size[cir]++, vis[stk[top--]] = -1;
    top--, bel[x] = cir, size[cir]++;
  }
}
void part3() {
  for (int i = 1; i <= n; i++) num[i] = i;
  sort(num + 1, num + n + 1, cmp3);
  for (int i = 1; i <= n; i++) addr(num[i], i), addr(i, num[i]);
  for (int i = 1; i <= n; i++)
    if (!dfn[i]) dfs(i);
  int tot = 0;
  for (int i = 1; i <= cir; i++) tot += size[i] - 1;
  Ans2 += 1ll * tot * a + 1ll * (cnt - tot) * b;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("trick.in", "r", stdin);
  freopen("trick.out", "w", stdout);
#endif
  part1();
  part2();
  part3();
  if (Ans1 > Ans2) swap(Ans1, Ans2);
  cout << Ans1 << " " << Ans2;
}
```


---

