# [COTS 2018] 逃遁 Bijeg

## 题目背景


译自 [Izborne Pripreme 2018 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2018/) D2T2。$\texttt{10s,1G}$。


## 题目描述


考虑一个二维笛卡尔坐标系。

劫匪初始时在原点，此外有 $n$ 个警察分布在平面上。

他们的**速率**均为 $v$（一个正实数），且只会沿着一个特定的方向做**匀速直线**运动（每个人运动的方向可能不同）。

劫匪可以任意选定自己逃跑的方向，而警察会选择最优的方式追捕劫匪。当警察和劫匪的位置重合时，劫匪即被逮捕。

试判断：

- 劫匪是否可以成功逃跑，也就是，是否存在一个方向，使得劫匪不被逮捕。

如果无法逃跑，还需要求出劫匪被逮捕时，离原点的欧几里得距离的最大值。

数据保证这 $(n+1)$ 个人的位置两两不同。


## 说明/提示


#### 样例解释

样例 $1$ 解释如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/fdrlttoq.png)

#### 子任务

对于 $100\%$ 的数据，保证 $1\le n\le 10^5$，$|x|,|y|\le 10^3$，所有人的位置均不同。


| 子任务编号 | $n\le $ |  $\vert x\vert ,\vert y\vert \le $ |  得分 |  
| :--: | :--: | :--: | :--: |  
| $ 1 $    | $ 100 $    |  $10$ | $ 20 $   |  
| $ 2 $    | $ 3\, 000 $   |  $100$ | $ 30 $   |  
| $ 3 $    | $ 10^5$ | $1\, 000$ |  $ 50 $   |  


## 样例 #1

### 输入

```
4
4 4
-4 4
-4 -4
4 -4```

### 输出

```
4```

## 样例 #2

### 输入

```
3
3 0
-3 1
-3 -1```

### 输出

```
9.617692030835672```

## 样例 #3

### 输入

```
2
1 1
0 1```

### 输出

```
-1```

# 题解

## 作者：Twlight！ (赞：3)

~~andychen打球时直接想出半平面交做法这我哪会写啊。~~

## 初步思路（半平面交）
观察到警察与劫匪都只能走一条射线，且相同时间内他们行驶的路程都一样，那么不难发现劫匪被某个警察抓住时，抓住的位置在劫匪与那个警察连线的中垂线上，如图。

[![image.png](https://i.postimg.cc/9f3y1ZbL/image.png)](https://postimg.cc/18Hg3gLF)

显然劫匪无法穿过这条中垂线，否则必会被警察抓到。换句话说，每个警察与劫匪的连线的中垂线都限制了劫匪的活动范围，这些半平面或交成了个凸多边形。不难发现我们要求出劫匪最远能跑的距离，就相当于求这个凸多边形的顶点与原点的距离的最大值。

判断劫匪永远都不会被抓到也很简单，看半平面交围成的是否是一个有范围的凸多边形即可。

时间复杂度 $O(n \log n)$。


## 简化难度（二分答案）
我不会半平面交，只能换一种思路进行解决了。

发现答案是具有单调性的，考虑二分答案。此时问题就变为了，判断劫匪是否能跑 $\text{mid}$ 距离，即劫匪是否能到达以原点为圆心，$\text{mid}$ 为半径的圆的圆弧上。

我们把每个警察也看成大小为 $\text{mid}$ 的圆，显然警察的圆与劫匪的圆的交点，在警察与劫匪的连线的中垂线上，如图。

[![image.png](https://i.postimg.cc/J0wbYJRr/image.png)](https://postimg.cc/wyVy71tZ)

显然劫匪不能越过中垂线，而劫匪又只能在圆弧上移动，可以发现每个警察或覆盖了圆弧的一部分，或没有覆盖。如果存在一个点，那个点没有被任何警察覆盖，那么劫匪就一定可以跑到那里（弦围成的多边形是凸的），用朴素方法判断线段覆盖就可以了。

做法也比较简单，把交点转为方位角之类的角度，变为一段区间，最后排个序判断是否全覆盖即可。至于求交点一事，可查阅相关代码或推式子。

这里再提一嘴二分上界，我认为这可能是考场上最难发现的问题。两条中垂线的交点，可能到达 $10^9$ 的级别，因为两条直线可能斜率都很极端，导致最终的交点非常远，如果不注意就可能爆零。

时间复杂度 $O(n \log^2 n)$，虽然慢了但是应该比较好写。

### 参考代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int ll
#define double long double

const int N = 100000 + 10;
const double inf = 1e10;
const double PI = acos(-1);
const double eps1 = 1e-18;
const double eps2 = 1e-6;

using namespace std;

int read () {
	int x = 0, k = 1;
	char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') k = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return (1ll * x * k);
}

using Pdd = pair<double, double>;
using Pdi = pair<double, int>;

int n;
Pdd P[N], P0(0, 0);

double sqr (double x) { return x * x; }
double sgn (double x, double eps = eps1) { return x < -eps ? -1 : x > eps; }

vector<double> findPoint (Pdd A, Pdd B, double r) {
	vector<double> ret; double d = sqrt(sqr(A.first - B.first) + sqr(A.second - B.second));
	if (!sgn(d) || d - 2 * r >= eps1) return ret;
	double q = atan2(B.second - A.second, B.first - A.first), h = acos(d / r / 2);
	double a1 = q - h, a2 = q + h;
	if (a1 < eps1) a1 += 2 * PI; if (a2 < eps1) a2 += 2 * PI;
	ret.push_back(a1), ret.push_back(a2); return ret;
}

bool check (double r) {
	vector<Pdi> Arg; int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		auto q = findPoint(P0, P[i], r);
		if (!q.size()) continue;
		Arg.emplace_back(q[0], 1);
		Arg.emplace_back(q[1], -1);
		cnt += (q[0] - q[1] > eps1);
	}

	if (!cnt) return 1;

	sort(Arg.begin(), Arg.end(), [](Pdi A, Pdi B){ return A.first - B.first < eps1; }); 

	for (int i = 0, l = Arg.size(); i < l; ++i) {
		cnt += Arg[i].second;
		if (!cnt) return 1;
	}
	return 0;
}

signed main() {
	n = read();
	for (int i = 1, X, Y; i <= n; ++i) X = read(), Y = read(), P[i] = Pdd(X, Y);

	if (check(inf)) puts("-1"), exit(0);

	double l = 0, r = inf, mid;
	while (r - l > eps2) {
		mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%.10Lf\n", r); 

	return 0;
}
```

---

## 作者：andychen_2012 (赞：2)

Hint 1：警察抓到小偷时跑了相同的距离。

Hint 2：如果小偷无法逃脱，他的活动范围必然被局限在了一个多边形中。



---



根据 Hint 1，我们由初中数学知识可以得到小偷与警察相遇的位置必然在他们连线的中垂线上。

我们将这些中垂线画出来，可以发现，小偷的活动范围即为这些中垂线的包含原点的半平面交。

因此我们只需要求出这个半平面交即可。如果半平面交无法构成一个多边形，那么小偷就能逃跑；否则，小偷跑的最远处即为这个半平面交离原点最远的顶点。

时间复杂度 $O(n\log n)$。

半平面交的板子见这道题：[P4196 [CQOI2006] 凸多边形 /【模板】半平面交](https://www.luogu.com.cn/problem/P4196)。


```cpp
#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0;
	int f=0,ch=0;
	while(ch<48||ch>57) f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return f?-x:x;
}
inline void write(ll x,char end='\n'){
	if(x==0){
		putchar('0');
		putchar(end);
		return;
	}
	if(x<0) putchar('-'),x=-x;
	int ch[40]={0},cnt=0;
	while(x){
		ch[cnt++]=(int)(x%10);
		x/=10;
	}
	while(cnt--) putchar(ch[cnt]+48);
	putchar(end);
}
#define mp make_pair
const int N=1e5+5;
const double eps=1e-9;
const double inf=1e18;
int n;
struct vec{
	double x,y;
	friend vec operator +(vec a,vec b){return {a.x+b.x,a.y+b.y};}
	friend vec operator -(vec a,vec b){return {a.x-b.x,a.y-b.y};}
	friend double operator *(vec a,vec b){return a.x*b.x+(a.y*b.y);}
	friend vec operator *(double a,vec b){return {a*b.x,a*b.y};}
};
inline double cross(vec a,vec b){return a.x*b.y-a.y*b.x;}
inline double len(vec a){return sqrt(a.x*a.x+a.y*a.y);}
struct line{
	vec p,way;
	double ang;
}a[N];
inline line makeLine(vec a,vec b){line x={a,b,atan2(b.y,b.x)};return x;}
inline bool onRight(line a,vec b){return cross(a.way,b-a.p)<=-eps;}
inline bool cmp(line a,line b){return a.ang<b.ang;}
inline vec inter(line a,line b){double x=cross(b.way,a.p-b.p)/cross(a.way,b.way);return a.p+x*a.way;}
vec p[N];
line q[N];
int hd,tl;
inline bool halfPlane(){
	a[++n]=makeLine({inf,0},{0,1});
	a[++n]=makeLine({-inf,0},{0,-1});
	a[++n]=makeLine({0,inf},{-1,0});
	a[++n]=makeLine({0,-inf},{1,0});
	sort(a+1,a+n+1,cmp);
	hd=tl=0;
	q[0]=a[1];
	for(int i=2;i<=n;++i){
		while(hd<tl&&onRight(a[i],p[tl])) --tl;
		while(hd<tl&&onRight(a[i],p[hd+1])) ++hd;
		q[++tl]=a[i];
		if(abs(cross(q[tl].way,q[tl-1].way))<=eps){
			if(onRight(q[tl],q[tl-1].p)&&q[tl].way*q[tl-1].way<=eps) return 0;
			--tl;
			if(!onRight(q[tl],a[i].p)) q[tl]=a[i];
		}
		if(hd<tl) p[tl]=inter(q[tl],q[tl-1]);
	}
	while(hd<tl&&onRight(q[hd],p[tl])) --tl;
	if(tl-hd<=1) return 0;
	p[hd]=inter(q[hd],q[tl]);
	for(int i=hd;i<=tl;++i) if(p[i].x>=inf-eps||p[i].x<=-inf+eps||p[i].y>=inf-eps||p[i].y<=-inf+eps) return 0;
	return 1;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		int nx=read(),ny=read();
		double x=nx,y=ny;
		double tx=y,ty=-x;
		x/=2,y/=2;
		if(onRight(makeLine({x,y},{tx,ty}),{0,0})) tx=-tx,ty=-ty;
		a[i]=makeLine({x,y},{tx,ty});
	}
	if(!halfPlane()) puts("-1");
	else{
		double mx=0;
		for(int i=hd;i<=tl;++i) mx=max(mx,len(p[i]));
		printf("%.9lf\n",mx);
	}
	return 0;
}
```

---

