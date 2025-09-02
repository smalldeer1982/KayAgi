# Vacuum Сleaner

## 题目描述

One winter evening the Hedgehog was relaxing at home in his cozy armchair and clicking through the TV channels. Stumbled on an issue of «TopShop», the Hedgehog was about to change the channel when all of a sudden he was stopped by an advertisement of a new wondrous invention.

Actually, a vacuum cleaner was advertised there. It was called Marvellous Vacuum and it doesn't even need a human to operate it while it cleans! The vacuum cleaner can move around the flat on its own: it moves in some direction and if it hits an obstacle there, it automatically chooses a new direction. Sooner or later this vacuum cleaner will travel through all the room and clean it all. Having remembered how much time the Hedgehog spends every time on cleaning (surely, no less than a half of the day), he got eager to buy this wonder.

However, the Hedgehog quickly understood that the cleaner has at least one weak point: it won't clean well in the room's corners because it often won't able to reach the corner due to its shape. To estimate how serious is this drawback in practice, the Hedgehog asked you to write for him the corresponding program.

You will be given the cleaner's shape in the top view. We will consider only the cases when the vacuum cleaner is represented as a convex polygon. The room is some infinitely large rectangle. We consider one corner of this room and want to find such a rotation of the vacuum cleaner so that it, being pushed into this corner, will leave the minimum possible area in the corner uncovered.

## 样例 #1

### 输入

```
4
0 0
1 0
1 1
0 1
```

### 输出

```
0.00000000000000000000```

## 样例 #2

### 输入

```
8
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
-2 1
-1 2
```

### 输出

```
0.50000000000000000000```

# 题解

## 作者：rEdWhitE_uMbrElla (赞：3)

简洁的题意翻译：对于一个凸包形状的吸尘器，问你这个吸尘器在清理矩形的角落时，遗留下的最小面积，可以旋转

~~都翻译成这样了，明显~~**这题需要计算几何**

![tmp.png](https://i.loli.net/2018/11/25/5bfa412598c34.png)

如图，死角的面积是$S_{\Delta ABC}-S_1$ (注：1可为任何边形)，明显，对于每个固定的A和B，$S_1$的面积是固定的且$\Delta ABC$的高AB也是固定的。于是，**为了让死角面积最小，就是让$\Delta ABC$ AB边上的高最小**。因为直角三角形的斜边的中线等于斜边的一半，所以点O在以AB为直径的圆上，所以**当三角形的边与多边形的边重合时高最小**。

于是我们只需要枚举该多边形的n条边，讨论其靠左墙或靠下墙，然后通过作垂直于该边的线求出贴在另一墙上离点O最近的点，然后计算出此时面积，取最小值。维护内部多边形的面积时可将其分割成若干三角形，然后用叉积维护。

最后，注意精度控制 

代码如下

```
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

long long sqr(long long x) __attribute__((always_inline));

long long sqr(long long x) {
	return x * x;
}

struct Point {
	Point(int x = 0, int y = 0) : x(x), y(y) {}
	inline Point &operator -=(const Point &o) {
		x -= o.x;
		y -= o.y;
		return *this;
	}
	double dis() const __attribute__((always_inline));
	int x, y;
};

double Point::dis() const {
	return sqrt(sqr(x) + sqr(y));
}

inline Point operator - (Point a, const Point &b) {
	return a -= b;
}

long long det(const Point &a, const Point &b) __attribute__((always_inline));
long long dot(const Point &a, const Point &b) __attribute__((always_inline));
long long get_sum(int i,int j) __attribute__((always_inline));
int nxt(int i) __attribute__((always_inline));
double solve() __attribute__((always_inline));

long long det(const Point &a, const Point &b) {
	return (long long)a.x * b.y - (long long)a.y * b.x;
}

long long dot(const Point &a, const Point &b) {
	return (long long)a.x * b.x + (long long)a.y * b.y;
}

const int N = 40000;

int n;
Point p[N];
long long sum[N + 1];

long long get_sum(int i, int j) {
	long long s = sum[j] - sum[i];
	return i <= j ? s : sum[n] + s;
}

int nxt(int i) {
	return (i + 1) % n;
}

double solve() {
	sum[0] = 0;
	for (int i = 0; i < n; ++ i) sum[i + 1] = sum[i] + det(p[i], p[(i + 1) % n]);
	double result = INFINITY;
	for (int i = 0, j = 0; i < n; ++ i) {
		while (dot(p[nxt(i)] - p[i], p[nxt(j)] - p[j]) > 0) j = nxt(j);
		Point a = p[nxt(i)] - p[i];
		Point b = p[j] - p[i];
		double n = a.dis();
		result = min(result, det(a, b) / n * dot(a, b) / n - (get_sum(i, j) + det(p[j], p[i])));
		if (i == j) return 0.;
	}
	return .5 * result;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d%d", &p[i].x, &p[i].y);
	solve();
	if (sum[n] < 0) reverse(p, p + n);
	double result = solve();
	for (int i = 0; i < n; ++ i) p[i].x *= -1;
	reverse(p, p + n);
	result = min(result, solve());
	printf("%.10f\n", result);
	return 0;
}
```

---

## 作者：luosw (赞：1)

## 题目描述

- 对于一个凸包形状的吸尘器，问你这个吸尘器在清理矩形的角落时，遗留下的最小面积。
- 可以旋转。
---

## 题目分析 
- 计算从第i个点到第j个点所围成的面积，（从i到j 向量旋转不能超过90度）。
- 算出凸包的i与j连线在矩形中对应的长与宽，用长，宽，以及i，j连线构成的三角形减去前面的面积，就是够不到的角落，最后取最小值即可。
- 注意顺时针逆时针都要来一次。

## $Code$
```cpp

#include<stdio.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
struct P
{
    double x,y;
    P(double a=0,double b=0):x(a),y(b){}
    P operator +(const P &a)const{
        return P(x+a.x,y+a.y);
    }
    P operator -(const P &a)const{
        return P(x-a.x,y-a.y);
    }
    P operator *(const double a)const{
        return P(x*a,y*a);
    }
    P operator /(const double a)const{
        return P(x/a,y/a);
    }
    double operator *(const P &a)const{
        return x*a.x+y*a.y;
    }
    double operator ^(const P &a)const{
        return x*a.y-y*a.x;
    }
};
double dis(P a,P b)
{
    return sqrt((b-a)*(b-a));	//平方差
}
P p[100100];
int n;
double sum[100100];
double solve()
{
    for(int i=n;i<n+n;i++) p[i]=p[i-n];
    sum[0]=0;
    for(int i=1;i<2*n;i++) {sum[i]=sum[i-1]+(p[i]^p[i-1])/2.0;}
    int j=0;
    double ans=1e18;
    for(int i=0;i<n;i++)
    {
        if(j<=i) j=i+1;
        while(j+1<2*n&&(((p[j+1]-p[i])*(p[i+1]-p[i]))>=((p[j]-p[i])*(p[i+1]-p[i])))) j++;
        //cout<<"j="<<j<<endl;
        if(j==i+1) ans=0;
        if(j>=2*n) break;
        double s=sum[j]-sum[i];
 
        s+=(p[i]^p[j])/2.0;
 
        double x=((p[j]-p[i])*(p[i+1]-p[i]))/dis(p[i],p[i+1]);
        double y=sqrt(((p[i]-p[j])*(p[i]-p[j]))-x*x);
        //cout<<"s="<<s<<" x="<<x;
        //printf(" y=%.10lf\n",y);
        ans=min(ans,x*y/2.0-fabs(s));
    }
    return ans;
}
int main()
{
    while(scanf("%d",&n)!=EOF)	//直到输入结束
    {
        for(int i=0;i<n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        double ans=solve();
        for(int i=0;i<n/2;i++)
            swap(p[i],p[n-i-1]);
        ans=min(ans,solve());
        printf("%.10lf\n",ans);	//保留10位小数
    }
    return 0;	、//完结撒花！
}

```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
对于一个 $n$ 个结点的凸包形状的吸尘器，问你这个吸尘器在清理矩形的角落时，遗留下的最小面积，可以旋转.  
$n\le 4\times10^4$.
## $\text{Solution}$
可能是入门难度的计算几何了.  
不难发现最优的时候墙一定和一条边重合（可以通过画圆证明）.  
那么我们就暴力枚举这条边，双指针维护墙另一条边过的顶点即可.  
最后把所有点翻转过来再做一次.  
实现上的技巧：  
1. 寻找另一条墙边过的点可以通过判断向量在当前边上投影的大小来实现.
2. 计算面积时用墙的三角形面积减去多边形两个顶点截出的多边形面积，这个多边形面积可以处理一个面积关于顶点叉积的前缀和再减去这两个顶点叉积求出（建议画图理解）.（算出的面积 **可能为负**，所以要取绝对值）
3. 墙角三角形的边长一条可以通过投影来求，另一条勾股定理即可.

具体实现建议参考代码理解.  

## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
//#define double long double
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e5+100;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m,k;
struct P{
  double x,y;
}p[N];
inline P operator + (P a,P b){return (P){a.x+b.x,a.y+b.y};}
inline P operator - (P a,P b){return (P){a.x-b.x,a.y-b.y};}
inline double operator * (P a,P b){return a.x*b.x+a.y*b.y;}
inline double operator ^ (P a,P b){return a.x*b.y-a.y*b.x;}
inline double dis(P a,P b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
inline double calc(double x,double y){return sqrt(x*x-y*y);}
double sum[N];
double solve(){
  double res=2e18;
  for(int i=n+1;i<=n+n;i++) p[i]=p[i-n];
  for(int i=2;i<=n+n;i++) sum[i]=sum[i-1]+(p[i]^p[i-1])/2;
  int j=1;
  for(int i=1;i<=n;i++){
    j=max(j,i+1);
    while(j+1<=n*2&&(p[i+1]-p[i])*(p[j+1]-p[i])>=(p[i+1]-p[i])*(p[j]-p[i])) ++j;
    if(j==i+1) res=0;
    if(j>2*n) break;
    double s=sum[j]-sum[i]+(p[i]^p[j])/2;
    double x=(p[j]-p[i])*(p[i+1]-p[i])/dis(p[i+1],p[i]);
    double y=calc(dis(p[i],p[j]),x);
    res=min(res,x*y/2-abs(s));
    //printf("i=%d j=%d s=%lf x=%lf y=%lf res=%lf\n",i,j,s,x,y,x*y/2-s);
  }
  return res;
}
signed main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  #endif
  n=read();
  for(int i=1;i<=n;i++) p[i].x=read(),p[i].y=read();
  double ans=solve();
  reverse(p+1,p+1+n);
  ans=min(ans,solve());
  printf("%.10lf\n",ans);
  return 0;
}
/*

*/

```


---

