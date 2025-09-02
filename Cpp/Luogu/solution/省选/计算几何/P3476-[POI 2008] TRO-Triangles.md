# [POI 2008] TRO-Triangles

## 题目描述

平面上给定了 $n$ 个两两不相交的点（$n \ge 3$）。

这些点中有 $\dfrac{n(n-1)(n-2)}{6}$ 个三角形，其顶点是其中一些两两不同的点（包括退化三角形，即顶点共线的三角形）。

我们想要计算所有以给定点为顶点的三角形的面积之和。

属于多个三角形的平面部分需要多次计算。我们假设退化三角形（即顶点共线的三角形）的面积为零。

<Task>

编写一个程序：

从标准输入读取平面上点的坐标，确定所有以给定点为顶点的三角形的面积之和，输出结果到标准输出。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
0 0
1 2
0 2
1 0
1 1
```

### 输出

```
7.0
```

# 题解

## 作者：FZzzz (赞：3)

似乎其他两篇题解都说得不太清楚的样子，那我写一篇好懂一点的吧。

~~首先使用`assert`，测出$n\le3000$。~~

我们考虑三个点$A$，$B$，$C$组成的三角形面积，根据叉积的几何意义可知$S_{\triangle ABC}=\frac{|(x_B-x_A)(y_C-y_A)-(x_C-x_A)(y_B-y_A)|}{2}$，整理得$S_{\triangle ABC}=\frac{|x_A(y_B-y_C)+y_A(x_C-x_B)+x_By_C-x_Cy_B|}{2}$。

那我们为了不暴力统计，考虑依次固定一个点，比如$A$点。

但这就产生一个问题：如果其他点相对$A$的极角跨度超过$180^\circ$的话，绝对值无法消去，不好处理。所以我们将所有点按照纵坐标从小到大排序，然后依次考虑。每次考虑时，把后面所有点复制一下，按照极角再排一次序。这样只要$C$排在$B$后面，绝对值就可以去掉。

然后我们依次考虑所有点作为点$B$。可以发现只要知道后面所有点的坐标之和，就能一次算出所有三角形面积和。所以我们从后往前扫描$B$点，维护后缀和即可。

总时间复杂度为$n^2\log n$。代码如下：
```cpp
#include<iostream>
#include<algorithm>
#include<cctype>
#include<cstdio>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
struct Point{
	ll x,y;
	Point(int x=0,int y=0):x(x),y(y){}
};
typedef Point Vector;
inline Point readpoint(){
	Point p;
	p.x=readint();
	p.y=readint();
	return p;
}
Vector operator -(Vector a,Vector b){
	return Vector(a.x-b.x,a.y-b.y);
}
inline ll cross(Vector a,Vector b){
	return a.x*b.y-b.x*a.y;
}
int n;
const int maxn=3000+5;
Point p[maxn];
bool cmp1(Point a,Point b){
	return a.y<b.y||(a.y==b.y&&a.x<b.x);
}
Point p2[maxn];
Point aa;
bool cmp2(Point a,Point b){
	return cross(a-aa,b-aa)>0;
}
ll ans=0;
int main(){
	#ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    for(int i=0;i<n;i++) p[i]=readpoint();
    sort(p,p+n,cmp1);
    for(int i=0;i<n;i++){
    	aa=p[i];
    	for(int j=i+1;j<n;j++) p2[j]=p[j];
    	sort(p2+i+1,p2+n,cmp2);
    	ll sx=0,sy=0;
    	for(int j=n-1;j>i;j--){
    		ans+=aa.x*(p2[j].y*(n-j-1)-sy)+aa.y*(sx-p2[j].x*(n-j-1))+p2[j].x*sy-sx*p2[j].y;
    		sx+=p2[j].x;
    		sy+=p2[j].y;
		}
	}
	if(ans%2==1) cout<<ans/2<<".5"<<endl;
	else cout<<ans/2<<".0"<<endl;
    return 0;
}
```


---

## 作者：shiroi (赞：2)

#### 题意简述

平面上有 $N$ 个点. 求出所有以这 $N$ 个点为顶点的三角形的面积和。

#### 题目分析

先排序，每次把最左边的点当成原点，然后剩下的极角排序，接着枚举剩下的点，求叉积之和。

通常使用叉积求面积是 $abs(x_i*y_j-y_i*x_j)$ 通过极角排序去掉绝对值，把 $x_i$ 和 $x_j$ 提出来就可以求和了。

坐标都是整数，因此可以使用long long存下，double之类的可能有爆精度的风险。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0; int f=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}

typedef long long ll;
struct Point {int x,y;} p[3005],t[3005];
int n,sumx,sumy;
ll ans;

ll operator * (Point a,Point b)
{return a.x*b.y-a.y*b.x;}

bool operator < (Point a,Point b)
{return a.y<b.y||(a.y==b.y&&a.x<b.x);}

bool cmp(Point a,Point b) {return a*b>0;}

inline void solve()
{
	sort(p+1,p+n+1);
	for(int i=1; i<=n-2; i++)
	{
		int top=0; sumx=sumy=0;
		for(int j=i+1; j<=n; j++)
		{
			t[++top].x=p[j].x-p[i].x;
			t[top].y=p[j].y-p[i].y;
		}
		sort(t+1,t+top+1,cmp);
		for(int j=1; j<=top; j++)
			sumx+=t[j].x,sumy+=t[j].y;
		for(int j=1; j<=top; j++)
		{
			sumx-=t[j].x; sumy-=t[j].y;
			ans+=(ll)t[j].x*sumy-(ll)t[j].y*sumx;
		}
	}
}

int main(int argc, char const *argv[])
{
	n=read();
	for(int i=1; i<=n; i++)
		p[i].x=read(),p[i].y=read();
	solve();
	if(ans&1) printf("%lld.5",ans/2);
	else printf("%lld.0",ans/2);
	return 0;
}
```

---

## 作者：skylee (赞：2)

题目大意：

平面直角坐标系上有$n$个点，问以这$n$个点为顶点的不同的三角形的面积和是多少？

思路：

很容易想到一个$O(n^3)$的暴力，枚举三个点，用海龙公式求一下面积和即可，这样做是40分。

标算的复杂度是$O(n^2 \log n)$，

首先对所有的点按照位置的左右排序，

按顺序枚举每一个点$i$，并将其作为三角形的一个顶点。

对于顺序在$i$后面的点关于点i极角排序，并按照极角序枚举每一个点$j$。

三角形面积的两倍我们可以用叉积来求。

为了不枚举第三个顶点，我们可以算一下后缀和。

这题会爆double，由于小数部分要么是$.0$要么是$.5$，我们可以用long long来存一下，最后特判一下奇数偶数即可。

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
typedef long long int64;
inline int getint() {
    register char ch;
    while(!isdigit(ch=getchar()));
    register int x=ch^'0';
    while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
    return x;
}
const int N=3000;
struct Point {
    int x,y;
    Point operator - (const Point &another) const {
        return (Point){x-another.x,y-another.y};
    }
    int64 operator * (const Point &another) const {
        return (int64)x*another.y-(int64)y*another.x;
    }
};
Point p[N],t[N];
inline bool cmp1(const Point &a,const Point &b) {
    if(a.y==b.y) return a.x<b.x;
    return a.y<b.y;
}
inline bool cmp2(const Point &a,const Point &b) {
    return a*b>0;
}
int main() {
    int n=getint();
    for(register int i=0;i<n;i++) {
        p[i]=(Point){getint(),getint()};
    }
    std::sort(&p[0],&p[n],cmp1);
    int64 ans=0;
    for(register int i=0;i<n;i++) {
        int cnt=0;
        for(register int j=i+1;j<n;j++) {
            t[++cnt]=p[j]-p[i];
        }
        std::sort(&t[1],&t[cnt+1],cmp2);
        Point sum=(Point){0,0};
        for(register int j=cnt;j;j--) {
            ans+=sum*t[j];
            sum=sum-t[j];
        }
    }
    printf("%lld.%c\n",ans>>1,(ans&1)?'5':'0');
    return 0;
}
```

---

## 作者：LiuIR (赞：1)

### 题目大意

[题目传送门](https://www.luogu.com.cn/problem/P3476)

给定平面上的 $n$ 个点，求这些点能组成的所有三角形的面积之和。答案保留一位小数。

### 题目分析

首先，可以根据向量的叉积求出任意三角形的面积。

若直接暴力枚举三个点计算，时间复杂度为 $O(n^3)$，无法通过此题，于是考虑优化。

若只枚举两个点 $A,B$，那么在按极角排序之后可以使用前缀和优化，如下
$$
\begin{aligned}
\sum S&=\sum(B.x-A.x)\times(C.y-A.y)-(B.y-A.y)\times(C.x-A.x)\\
&=\sum(B.x-A.x)\times(C.y-A.y)-\sum(B.y-A.y)\times(C.x-A.x)\\
&=(B.x-A.x)\times\sum(C.y-A.y)-(B.y-A.y)\times\sum(C.x-A.x)\\
\end{aligned}
$$
但叉积是有符号的，而正负符号的临界点在与直线 $AB$ 夹角小于 $\pi$ 的夹角最大的点。所以可以用双指针找到这个点，并分成两部分统计答案。

时间复杂度 $O(n^2\log_2n)$，可以通过本题。

### 细节处理

注意 `atan2` 的符号问题。

### 代码

```c++
#include <cmath>
#include <cstdio>
#include <algorithm>
#define ld long double

const int N = 3005;
const ld PI = acos(-1.0);
const ld EXP = 1e-8;

struct Point{
	ld x, y, theta;//x，y为点的坐标，theta为极角
}a[N], b[N];

int n, tot;
ld ans, sumx[N], sumy[N];

bool operator < (Point, Point);
ld Atan(int, int);
int Cmp(ld, ld);

signed main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%Lf%Lf", &a[i].x, &a[i].y);
	for (int i = 1; i <= n; i++)
	{
		tot = 0;
		for (int j = i + 1; j <= n; j++)if (i != j)
		{
			b[++tot] = Point{a[j].x - a[i].x, a[j].y - a[i].y};
			b[tot].theta = Atan(b[tot].x, b[tot].y);
		}
		std::sort(b + 1, b + tot + 1);//极角排序
		sumx[1] = b[1].x;
		sumy[1] = b[1].y;
		for (int j = 2, k = 1; j <= tot; j++)
		{
			sumx[j] = sumx[j - 1] + b[j].x;
			sumy[j] = sumy[j - 1] + b[j].y;//处理前缀和
			while(b[j].theta - b[k].theta > PI)
				k++;//双指针
			ld val = b[j].x * sumy[k - 1] - b[j].y * sumx[k - 1];
			val += (sumx[j - 1] - sumx[k - 1]) * b[j].y - (sumy[j - 1] - sumy[k - 1]) * b[j].x;
			ans += val / 2;//计算答案
		}
	}
	printf("%.1Lf", ans);
	return 0;
}

bool operator < (Point x, Point y){return Cmp(x.theta, y.theta) < 0;}
ld Atan(int x, int y)//计算极角
{
	ld tmp = atan2(y, x);
	return tmp < 0 ? tmp + 2 * PI : tmp;
}
int Cmp(ld x, ld y){return fabs(x - y) < EXP ? 0 : x < y ? -1 : 1;}
```



---

## 作者：大菜鸡fks (赞：1)

这题主要是从左往右统计，推柿子，推出来以后可以化成前缀和的形式进行计算，通过改变枚举顺序（极角排序）的方式来化去绝对值。

o（n²logn）的复杂度可以做出来。

具体柿子见https://www.cnblogs.com/GXZlegend/p/7509699.html

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int N=3005;
struct node{
	int x,y;
	inline node(int a=0,int b=0){x=a; y=b;}
	inline node operator-(const node &a)const {return node(x-a.x,y-a.y);}
    inline bool operator<(const node &a)const {return y*a.x<x*a.y;}
}s[N],a[N];
int n;
inline void init(){
	scanf("%lld",&n);
	for (int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].x,&a[i].y);
	}
}
inline bool cmp(node A,node B){
	return A.x==B.x?A.y<B.y:A.x<B.x;
}
int sx[N],sy[N],ans;
inline void solve(){
	sort(a+1,a+1+n,cmp);
	for (int i=1;i<=n;i++){
		for (int j=i+1;j<=n;j++){
			s[j]=a[j]-a[i];	
		}
		sort(s+i+1,s+n+1);
		for (int j=n;j>i;j--){
			sx[j]=sx[j+1]+s[j].x;
			sy[j]=sy[j+1]+s[j].y;
			ans+=s[j].x*sy[j+1]-s[j].y*sx[j+1];
		}
	}
	printf("%lld.%lld\n",ans/2,ans%2*5);
}
signed main(){
	init();
	solve();
	return 0;
} 
```

---

