# Volatile Kite

## 题目描述

You are given a convex polygon $ P $ with $ n $ distinct vertices $ p_{1},p_{2},...,p_{n} $ . Vertex $ p_{i} $ has coordinates $ (x_{i},y_{i}) $ in the 2D plane. These vertices are listed in clockwise order.

You can choose a real number $ D $ and move each vertex of the polygon a distance of at most $ D $ from their original positions.

Find the maximum value of $ D $ such that no matter how you move the vertices, the polygon does not intersect itself and stays convex.

## 说明/提示

Here is a picture of the first sample

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772B/dde3b583b8130c23fcfe1a3be5859cfee6d3318c.png)

Here is an example of making the polygon non-convex.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772B/6cf9c89dbdf099a68520895969908ade3679a607.png)

This is not an optimal solution, since the maximum distance we moved one point is $ ≈0.4242640687 $ , whereas we can make it non-convex by only moving each point a distance of at most $ ≈0.3535533906 $ .

## 样例 #1

### 输入

```
4
0 0
0 1
1 1
1 0
```

### 输出

```
0.3535533906
```

## 样例 #2

### 输入

```
6
5 0
10 0
12 -4
10 -8
5 -8
3 -4
```

### 输出

```
1.0000000000
```

# 题解

## 作者：11400F (赞：0)

## CF772B Volatile Kite 题解

考虑怎么才能让他不变为凸多边形。只要其中一个点，他在这个多边形内是内凹进去的，那么这个多边形就不是凸多边形。

于是我们可以枚举内凹的那一个点 $X$，看看让他内凹进去的最小值 $d_X$ 是多少。

现在这里有一个凸多边形。我们想要把 $A$ 点往内移动使其成为非凸多边形。

![](https://s21.ax1x.com/2024/12/11/pAH4T0K.png)

容易发现，让他内凹还要让他移动距离最小，就要让它沿着 $FB$ 的垂线向内移动，移到 $G$ 点之后再往下移动无限小的距离。这时点 $A$ 移动的距离就可以近似看作 $AG$。

而因为其他的点也是可以移动的，所以就让 $A$ 点沿着 $AG$ 往下移动距离 $d_A$，$F$、$B$ 点同时平行于 $AG$ 网上移动距离 $d_A$，$2d_A = AG$，所以 $d_A = \frac{AG}{2}$。

然后枚举所有的点，求出他们的 $d$，再对 $d$ 取最小值即可。

现在问题转化为了 $AG$ 如何算。因为我们知道 $FB$ 的长度，所以就可以算三角形 $AFB$ 的面积，然后乘上 $2$ 再除以 $FB$ 即可。

我们知道，给定三点求三角形面积，可以用向量法。因为向量叉积的几何意义就是两个向量作成的平行四边形的“有向面积”。于是我们可以先找到向量 $\vec{FB}$ 和 $\vec{FA}$，然后求 $\frac{\vec{FB}\times\vec{FA}}{2}$，就可以得到这个三角形的面积（注意顺序不要错！）。然后就可以计算出 $AG$，最后计算出对于 $A$ 点的 $D$ 值了。

因为题目上说的点是以顺时针方向给的，所以顺序判断也是非常简单的。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1007;
int n;
struct Point{
    double x, y;
    Point operator + (const Point &b){
        return {x+b.x, y+b.y};
    }
    Point operator - (const Point &b){
        return {x-b.x, y-b.y};
    }
};
double Cross(Point u, Point v){
    return u.x*v.y-u.y*v.x;
}
double Dist(Point u, Point v){
    return sqrt((u.x-v.x)*(u.x-v.x) + (u.y-v.y)*(u.y-v.y));
}
Point p[N];

int main(){
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }
    p[n+1] = p[1], p[0] = p[n];
    double minid = 0x3f3f3f3f3f3f3f3f;
    for(int i=1;i<=n;i++){
        double triarea = Cross(p[i+1] - p[i-1], p[i] - p[i-1]) / 2;
        double height = triarea * 2 / Dist(p[i+1], p[i-1]);
        minid = min(minid, height);
    }
    minid /= 2;
    printf("%.10lf", minid);
    return 0;
}
```

---

## 作者：ivyjiao (赞：0)

计算几何的基础题，也是我做的第一个计算几何题。

首先我们可以想到：拉出相邻的三个点（题目中已经按顺时针顺序给出，其实这一点是我最后想到的，最开始写的 $O(n^3)$），然后求出它们的任意两点间距离，拉成一个三角形。

公式：$dis_{a,b}=\sqrt{(a_x-b_x)^2+(a_y-b_y)^2}$。

然后通过海伦公式求出该三角形的面积，公式：$S_{\Delta ABC}=\sqrt{p\times(p-a)\times(p-b)\times(p-c)}$，其中 $p=\dfrac{a+b+c}{2}$。

这样设 $A,B,C$ 的编号分别为 $i-1,i,i+1$，那么 $\dfrac{2\times S_{\Delta ABC}}{AC}$ 就是只挪动 $B$ 点让这个多边形不凸的最小 $d$ 值，但是 $A,C$ 也可以挪，所以对于 $i$ 真正的答案是 $\dfrac{2\times S_{\Delta ABC}}{2\times AC}=\dfrac{S_{\Delta ABC}}{AC}$，即原答案的一半。

放个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/g3c3nlxg.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

设 $2$ 为 $A$，$1$ 为 $B$，$4$ 为 $C$，$BG=\dfrac{2\times S_{\Delta ABC}}{AC}$，求的就是 $\dfrac {BG} 2$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double x[1001],y[1001],ans=2e9;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    for(int i=1;i<=n;i++){
        int j=i+1,k=i-1;
        if(j>n) j=1;
        if(k<1) k=n;
        double a=sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2));
        double b=sqrt(pow(x[i]-x[k],2)+pow(y[i]-y[k],2));
        double c=sqrt(pow(x[j]-x[k],2)+pow(y[j]-y[k],2));
        double p=(a+b+c)/2;
        double s=sqrt(p*(p-a)*(p-b)*(p-c));
        double cnt=s/c;
        ans=min(ans,cnt);
    }
    cout<<ans;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF772B)    
是个[双倍经验](https://www.luogu.com.cn/problem/P3744)。    
## 解法
我们贪心地想，要想要这个移动距离最小，那么我们必然需要移动在原凸多边形上相邻的三个点，移动距离即其所围成的三角形的高的 $\dfrac{1}{2}$。      
解释一下这个结论：因为我们选取的相邻三点中，位于中间的可以向内走，两边的可以向外走，这样一共就走了一个高的距离，使得这两条边被拉直，从而破坏其凸多边形的特性。    
那么接下来就是求三角形的高了。我们这里需要用到一个公式：   
令三角形的三边长分别为 $a,b,c$，其半周长为 $p$，则其面积为 $\sqrt{p(p-a)(p-b)(p-c)}$。    
求高我们直接计算 $\dfrac{2S}{b}$ 即可。（$b$ 为底边。）    
但是这里我们需要再除以二，所以这里就不必再多乘上一个 $2$ 了，所以最后的式子为 $\dfrac{1}{2}\sqrt{p(p-a)(p-b)(p-c)}$，我们对其取 $\min$ 即可。     
注意本题需要 `long double`。   
CODE：   
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
cst int N=1e3;
int n;
Point p[N+10];
db ans=1e18;
il db dis(cst Point& a,cst Point& b){
	ret sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
il db geth(cst Point& a,cst Point& b,cst Point& c){
	db p=(dis(a,b)+dis(a,c)+dis(b,c))/2;
	db S=sqrt(p*(p-dis(a,b))*(p-dis(a,c))*(p-dis(b,c)));
	db h=S/dis(a,c);
	ret h;
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i].x>>p[i].y;
	}
	p[0]=p[n];
	p[n+1]=p[1];
	for(int i=1;i<=n;i++){
		db h=geth(p[i-1],p[i],p[i+1]);
		if(dcmp(ans-h)>0){
			ans=h;
		}
	}
	cout<<fixed<<setprecision(10)<<ans;
	ret 0;
}
```


---

## 作者：Toothless03 (赞：0)

既然没有那我就来来~~水~~一篇题解

先来双倍经验：[P3744 李彬的几何](https://www.luogu.com.cn/problem/P3744)，真的是一毛一样的

显然对于三个点 $A, B, C$，如果 $B$ 移动到 $AC$ 上时为最大值，如果 $AC$ 和 $B$ 相距 $d$，辣么 $B$ 可以向 $AC$ 移动 $\displaystyle\frac{d}{2}$，$AC$ 可以整体向 $B$ 移动 $\displaystyle\frac{d}{2}$，所以最终答案即为 $\displaystyle\frac{d}{2}$。我们显然可以看出来，$B$ 到其他对角线的距离小于 $B$ 到 $B$ 两侧点的连线。所以我们就可以暴力枚举连续的 $3$ 个点即可，复杂度 $O(n)$。

那如何计算点到直线的距离呢？

对于 $B(n,m)$ 到 $AC$ 的距离当然可以先将 $AC$ 的直线方程计算成形如 $ax+by=c$ 的形式，距离就是 $\displaystyle\frac{|an+bm+c|}{\sqrt{a^2+b^2}}$ 但是实在是有亿点麻烦。。。。。。

所以我们可以使用向量叉积 $|\vec{BA}\times\vec{BC}|$ 除以 $|AC|$ 即可。

附上 AC 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <cstring>
#include <map>
#include <bitset>
using namespace std;
#define int long long
#define double long double
#define pr pair<int, int>
const int INF = LONG_LONG_MAX;
const int mod = 1000000007;
int gcd(int x, int y) {
	if (y == 0)
		return x;
	return gcd(y, x % y);
}
struct point {
	double x, y;
	friend void operator>>(istream& in, point& p) {
		in >> p.x >> p.y;
	}
	friend double operator*(point a, point b) {
		return abs(a.x * b.y - a.y * b.x);
	}
	friend double len(point p) {
		return sqrt(p.x * p.x + p.y * p.y);
	}
	friend point operator-(point a, point b) {
		return {a.x - b.x, a.y - b.y};
	}
};
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<point> pts(n + 2);
	for (int i = 0; i < n; i++)
		cin >> pts[i];
	pts[n] = pts[0], pts[n + 1] = pts[1];
	double ans = INF;
	for (int i = 1; i <= n; i++)
		ans = min((pts[i - 1] - pts[i]) * (pts[i + 1] - pts[i]) / len(pts[i + 1] - pts[i - 1]), ans);
	ans /= 2.0;
	printf("%.8Lf\n", ans);
}
```

---

