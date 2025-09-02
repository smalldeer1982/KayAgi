# [ABC296G] Polygon and Points

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc296/tasks/abc296_g

$ x $ 軸の正の向きを右、$ y $ 軸の正の向きを上とする $ 2 $ 次元座標平面上に、凸 $ N $ 角形 $ S $ があります。$ S $ の頂点の座標は、反時計回りに $ (X_1,Y_1),\ldots,(X_N,Y_N) $ です。

$ Q $ 個の点 $ (A_i,B_i) $ について、それぞれ $ S $ の内部・外部・境界上のいずれにあるか求めてください。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\times\ 10^5 $
- $ -10^9\ \leq\ X_i,Y_i,A_i,B_i\ \leq\ 10^9 $
- $ S $ は狭義凸 $ N $ 角形である。すなわち、全ての内角は $ 180 $ 度未満である。
- $ (X_1,Y_1),\ldots,(X_N,Y_N) $ は $ S $ の頂点を反時計回りに列挙したものである。
- 入力は全て整数である。

### Sample Explanation 1

$ S $ 及び 与えられた $ 3 $ 個の点は下図の通りです。$ 1 $ 番目の点は $ S $ の境界上、$ 2 $ 番目の点は内部、$ 3 $ 番目の点は外部にあります。 !\[図\](https://img.atcoder.jp/abc296/828da6ca52e6b48a908ad06fa59eb9cb.png)

## 样例 #1

### 输入

```
4
0 4
-2 2
-1 0
3 1
3
-1 3
0 2
2 0```

### 输出

```
ON
IN
OUT```

## 样例 #2

### 输入

```
3
0 0
1 0
0 1
3
0 0
1 0
0 1```

### 输出

```
ON
ON
ON```

# 题解

## 作者：Register_int (赞：4)

过查询点作 $x$ 轴的平行线。只要求出直线与凸包的交点，即可判断点与凸包的关系。

以凸包的最高点与最低点为分割点，将其分为左右两个凸壳。由于凸壳上的点的 $y$ 坐标一定单调递减或递增，于是可以通过二分求出直线的交点位于哪两个点之间。单次复杂度 $O(\log n)$。

# AC 代码

赛时没打完，先咕咕咕。

---

## 作者：syxmz (赞：3)

# AtCoder Beginner Contest 296G - Polygon and Points 解题报告
### 1 题目链接
[传送门](https://atcoder.jp/contests/abc296/tasks/abc296_g)
### 2 题目大意
##### 题目：多边形和点
##### 题目大意：
在一个平面直角坐标系中有一个凸 $N$ 变形，按逆时针给出这 $N$ 个点：$(X_i, Y_i)$。
现在有 $Q$ 个点，请输出 `ON`， `IN` 或 `OUT` 分别表示这些点在 $N$ 变形内，在边上或是在 $N$ 变形外。
### 3 解法分析
显然这一题有重题嫌疑，只是蒟蒻忘了是哪一场 `abc` 了

需要注意一下数据范围。发挥空间极小。

不难看出二分是个好方法。

首先，这是一个离线的多测。

于是你可以考虑借鉴一下[官解做法](https://atcoder.jp/contests/abc296/editorial/6128)，本人感觉不是很好写。

本人对其的理解是对 $x$ 坐标排序，然后用双指针去找它是在哪一条边上，然后数学搞定。显然数学的力量远远不止如此。

有几个前置知识：极坐标与向量叉乘。

首先，你可以将点从自然坐标系中换到极坐标系中，注意将极点换为凸多边形内任意一点，代码中为凸多边形的重心。

然后你可以考虑二分极角，找到与询问点极角相邻两个点。

显然，对于极角相邻两个点的，只要询问的点都在这一条边左侧（题目保证逆时针给出），那么此询问点定在凸多边形内部。

实现上述过程即可。

完结撒花~
### 4 AC Code
```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); ++(i))
#define fep(i, a, b) for (int (i) = (a); (i) < (b); ++(i))
#define N 200007
using namespace std;

int n, p, q;
double fx, fy;
double theta[N << 1];
int x[N << 1], y[N << 1];

int main() {
    scanf("%d", &n);
    rep(i, 1, n) {
    	scanf("%d%d", &x[i], &y[i]);
    	fx += (x[i + n] = x[i]);
    	fy += (y[i + n] = y[i]);
    }
    fx /= n;
	fy /= n;
    for (int i = 1; i <= n; ++i) {
        theta[i] = theta[i + n] = atan2(y[i] - fy, x[i] - fx);
        if (theta[i] < theta[p])
			p = i;
    }
    scanf("%d", &q);
    rep(i, 1, q) {
    	int dx, dy;
    	scanf("%d%d", &dx, &dy);
        int dz = lower_bound(theta + p, theta + p + n, atan2(dy - fy, dx - fx)) - theta;
        long long cc = 1LL * (x[dz] - x[dz - 1]) * (dy - y[dz - 1]) - 1LL * (y[dz] - y[dz - 1]) * (dx - x[dz - 1]);
        if (cc == 0)
        	puts("ON");
        if (cc > 0)
        	puts("IN");
        if (cc < 0)
        	puts("OUT");
    }
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

计算几何板子，建议复健计算几何使用。

因为其为**凸**多边形，所以说对于任意一条不和多边形中任意一条边重合的边，最多和多边形的边缘有 $2$ 个交点。因此过询问点随便做一条直线，然后在多边形中找出所有和这个直线相交的点的坐标即可。考虑做过这个点和 $x$ 轴平行或重合的直线，然后将整个多边形分割为左右两个凸壳，然后分别二分出交点即可。

代码预计会十分的让人 er，所以暂时咕咕咕了。

---

## 作者：SkyRainWind (赞：0)

考虑维护一下下凸壳和上凸壳，每次给点的时候考虑二分一下对应 $x$ 坐标的上凸壳和下凸壳的位置，然后再判一下 $y$ 坐标的关系。

注意特判凸壳中 $x$ 坐标相等的部分，实际证明这道题如果随机旋转坐标系的话会寄，因为边太多了。

代码：

```cpp
// by SkyRainWind
#include <bits/stdc++.h>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define pii pair<int,int>
#define pb push_back

using namespace std;

typedef long long ll;
typedef long long LL;

const int inf = 1e9, INF = 0x3f3f3f3f, maxn = 2e5+5;
const double eps = 1e-10;

typedef long double db;
int n;
struct point{
	db x,y;
}p[maxn];

point operator - (point a,point b){return point{a.x - b.x, a.y - b.y};}
point operator + (point a,point b){return point{a.x + b.x, a.y + b.y};}

db cross(point a,point b){return a.x * b.y - a.y * b.x;}
// 右手定则拇指向上，叉积为正，否则为负 

vector<point>up,dn;
int stk[maxn];

point rot(point now,db th){	// 逆时针旋转 th 
	db x1 = now.x*cos(th) - now.y*sin(th);
	db y1 = now.x*sin(th) + now.y*cos(th);
	return point{x1,y1};
}

mt19937 mrand(random_device{}()); 
double rnd(int x) { return (mrand() % x+1) * 1.0 / x;}
map<db,db>mpx,mpn;

int sgn(double x){
	if(fabs(x) < eps)return 0;
	if(x < -eps)return -1;
	return 1;
}

signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%Lf%Lf",&p[i].x,&p[i].y);
		if(!mpx.count(p[i].x))mpx[p[i].x] = p[i].y;
		else mpx[p[i].x] = max(mpx[p[i].x], p[i].y);
		if(!mpn.count(p[i].x))mpn[p[i].x] = p[i].y;
		else mpn[p[i].x] = min(mpn[p[i].x], p[i].y);
	}
	sort(p+1,p+n+1,[&](point a,point b){return a.x==b.x?a.y<b.y:a.x<b.x;});
	
	int tp=0;
	stk[++ tp] = 1;
	for(int i=2;i<=n;i++){
		while(tp > 1 && cross(p[stk[tp-1]] - p[stk[tp]], p[stk[tp]] - p[i]) > 0)
			-- tp;
		stk[++ tp] = i;
	}
	for(int i=1;i<=tp;i++)up.pb(p[stk[i]]);
	
	tp = 0;
	stk[++ tp] = 1;
	for(int i=2;i<=n;i++){
		while(tp > 1 && cross(p[stk[tp-1]] - p[stk[tp]], p[stk[tp]] - p[i]) < 0)
			-- tp;
		stk[++ tp] = i;
	}
	for(int i=1;i<=tp;i++)dn.pb(p[stk[i]]);
	
	int qu;scanf("%d",&qu);
	while(qu --){
		db x,y;scanf("%Lf%Lf",&x,&y);
		
		int l=0, r=up.size()-1, r1 =-1;
		if(sgn(up[0].x-x)==1 || sgn(up[up.size()-1].x-x)==-1){
			puts("OUT");
			continue;
		}
		if(mpx.count(x) && sgn(mpx[x]-mpn[x])){
			if(sgn(y-mpn[x]) >=0 && sgn(mpx[x]-y) >= 0)puts("ON");
			else puts("OUT");
			continue; 
		}
		while(l <= r){
			int mid = l+r>>1;
			if(sgn(up[mid].x-x)<=0)r1 = mid, l=mid+1;
			else r=mid-1;
		}
		l=0, r=dn.size()-1;
		int r2 =-1;
		while(l <= r){
			int mid = l+r>>1;
			if(sgn(dn[mid].x-x)<=0)r2 = mid, l=mid+1;
			else r=mid-1;
		}
		
		// 找到对应的两个点 up[r1],up[r1+1], dn[r2],dn[r2+1] 
		db y1, y2;
		if(r1 == up.size()-1)y1 = up[up.size()-1].y;
		else y1 = (x - up[r1].x) * 1.0 / (up[r1+1].x - up[r1].x) * (up[r1+1].y - up[r1].y) + up[r1].y;
		
		if(r2 == dn.size()-1)y2 = dn[dn.size()-1].y;
		else y2 = (x - dn[r2].x) * 1.0 / (dn[r2+1].x - dn[r2].x) * (dn[r2+1].y - dn[r2].y) + dn[r2].y;
		if(fabs(y1-y) < eps || fabs(y2-y) < eps)puts("ON");
		else if(sgn(y1-y) == 1 && sgn(y-y2) == 1)puts("IN");
		else puts("OUT");
	}

	return 0;
}
```

---

