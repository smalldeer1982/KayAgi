# Triangles

## 题目描述

Little Petya likes to draw. He drew $ N $ red and $ M $ blue points on the plane in such a way that no three points lie on the same line. Now he wonders what is the number of distinct triangles with vertices in red points which do not contain any blue point inside.

## 样例 #1

### 输入

```
4 1
0 0
10 0
10 10
5 4
2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5
5 10
6 1
8 6
-6 -7
7 -1
5 -1
10 -4
-10 -8
-10 5
-2 -8
```

### 输出

```
7
```

# 题解

## 作者：XL4453 (赞：1)


给个有图的题解。

[广告](https://www.luogu.com.cn/blog/JSYZCHTHOLLY/)

---
### 解题思路：

$n$ 是 $500$ 的，考虑用一种 $O(n^3)$ 或者以下的算法计算结果。

发现其实想要不枚举三角形的三边直接计算满足条件的三角形并不简单，此时仅仅是枚举三个点就已经是 $O(n^3)$ 的了，所以尝试在判断上优化，要求优化到 $O(1)$。

这里我们不从点而从边入手，因为一个点在和其他的点进行搭配时找到不变量是比较困难的，而边则相对固定。

![](https://cdn.luogu.com.cn/upload/image_hosting/qhr04ds3.png)

入图，已知三角形和两个点，考虑如何判断一个点是否在三角形内。对于每一条边，可以预处理出所有的在两端点之间（这里指过该点作 $x$ 轴的平行线，在两平行线之间，上开下闭或者上闭下开都行）且在这条边的左边或者右边的点的数量。

如果没有点在三角形内部，可以发现，在 $y$ 方向上跨度最大一条边恰好统计了其他的两条边所有点，反之则一定有一些点多统计或者少统计（这个取决于三角形的形状和统计方向，与点无关）。

那么就珂以根据这个来进行判断了，如果将两条跨度较小的边的左边（或右边）的点相加恰好等于跨度较大的一条边的左边（或右边）的点，那么这个三角形一定是没有任何点在三角形内的，也就是符合条件。反之一定不符合。

---

然后考虑如何判断一个点是否在一条边的左边或者右边，首先将纵坐标超出两端点范围的点排除（也就是那个平行线之外的点）。然后就只有两种情况了（题目保证不存在共线）。

接下来的判断一共有两种方法，一种是用叉积，这一种相对简单，但是如果没有接触过叉积呢？

其实一次函数（解析几何相关）的知识就足以解决这个问题了。

过要求的那个点作 $x$ 轴的平行线，求出这个点与刚才那条边的交点（根据上面的判断，显然可以证明，这里一定有交点），然后比较这两个点的横坐标就行了。

---

具体实现上，珂以先将所有的点按照 $y$ 从小到大排序，然后直接通过数组位置关系判断那一个是 $y$ 上跨度在最大的。

---
### 代码：

#### 叉积判断法：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct str{
	long long x,y;
	bool operator <(str a){
		return y<a.y;
	}
}r[505],b[505];
long long n,m;
int ans,f[505][505];
bool CHECK(long long x1,long long y1,long long x2,long long y2){
	return x1*y2-x2*y1>0;
}
bool check(str a,str b,str c){//叉积判断法 
	if(c.y<a.y||c.y>=b.y)return 0;
	return CHECK(c.x-a.x,c.y-a.y,b.x-a.x,b.y-a.y);
}
int main(){
	scanf("%I64d%I64d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%I64d%I64d",&r[i].x,&r[i].y);
	for(int i=1;i<=m;i++)scanf("%I64d%I64d",&b[i].x,&b[i].y);
	sort(r+1,r+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	for(int k=1;k<=m;k++)
	f[i][j]+=check(r[i],r[j],b[k]);
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	for(int k=j+1;k<=n;k++)
	ans+=(f[i][j]+f[j][k]==f[i][k]);
	printf("%d\n",ans);
	return 0;
}
```

#### 函数判断法：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct str{
	long long x,y;
	bool operator <(str a){
		return y<a.y;
	}
}r[505],b[505];
long long n,m;
int ans,f[505][505];
bool CHECK(long long x1,long long y1,long long x2,long long y2,long long x,long long y){
	return (double)x<((double)x1+((((double)y-(double)y1)*((double)x1-(double)x2))/((double)y1-(double)y2)));
}
bool check(str a,str b,str c){//一次函数判断法 
	if(c.y<a.y||c.y>=b.y)return 0;
	return CHECK(a.x,a.y,b.x,b.y,c.x,c.y);
}
int main(){
	scanf("%I64d%I64d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%I64d%I64d",&r[i].x,&r[i].y);
	for(int i=1;i<=m;i++)scanf("%I64d%I64d",&b[i].x,&b[i].y);
	sort(r+1,r+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	for(int k=1;k<=m;k++)
	f[i][j]+=check(r[i],r[j],b[k]);
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	for(int k=j+1;k<=n;k++)
	ans+=(f[i][j]+f[j][k]==f[i][k]);
	printf("%d\n",ans);
	return 0;
}
```




---

## 作者：demon_yao (赞：1)

### 题意
- 给定$n$个红点和$m$个蓝点，求满足条件的三角形个数，使得他的顶点是$3$个红点，且没有任何一个蓝点在其内部。

### 思路
- 我们考虑怎样的三角形满足条件:画图可以发现 如果一个点位于三角形的内部，那么对于逆时针遍历有向直线，该点总是落在左边。反之，如果顺时针遍历，一定都落在右边。

- 于是我们就想到了方法：$f[i][j]$为以$i$,$j$为顶点的边的计数数组，若一个点在此边左边则$++1$,在右边不变，以此方法遍历所有点，当且仅当遍历到$f[i][j]+f[j][k]==f[i][k]$我们就$ans++$。

- 问题来了，如何判断一个点在此边左边？这里推荐一个方法 $To-left$方法，这里大家可以自行百度（记板子），我就不赘述了。

$Ps:$$code$十分简洁，因该看得懂叭$qwq$

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=1e3+5;int f[N][N];
struct node{long long x,y;}a[N],b[N];
bool cmp(node x,node y){return x.y<y.y;}
long long area(node a,node b,node c){
  return a.x*b.y-a.y*b.x+b.x*c.y-b.y*c.x+c.x*a.y-c.y*a.x;
}
bool toleft(node a,node b,node c){
  if(c.y<=a.y || c.y>b.y) return 0;
  return area(a,b,c)>0;
}
int n,m;
int main(){
	cin>>n>>m;
    for(int i=1;i<=n;++i)  scanf("%lld%lld",&a[i].x,&a[i].y);
    for(int i=1;i<=m;++i)  scanf("%lld%lld",&b[i].x,&b[i].y);
    sort(a+1,a+n+1,cmp);int ans=0;
    for(int i=1;i<n;++i)
      for(int j=i+1;j<=n;++j)
        for(int k=1;k<=m;++k)
          if(toleft(a[i],a[j],b[k])) f[i][j]++;
    for(int i=1;i<n;++i)
      for(int j=i+1;j<n;++j)
        for(int k=j+1;k<=n;++k)
          if(f[i][j]+f[j][k]==f[i][k]) ans++;
    printf("%d\n",ans); 
    return 0;
}

```


---

## 作者：PiCaHor (赞：1)

更好食用 
[mimimi](https://www.cnblogs.com/PiCaHor/p/9750204.html)
#Describtion 

Little Petya likes to draw. He drew N red and M blue points on the plane in such a way that no three points lie on the same line. Now he wonders what is the number of distinct triangles with vertices in red points which do not contain any blue point inside.

#Input

The first line contains two non-negative integer numbers N and M (0 ≤ N ≤ 500, 0 ≤ M ≤ 500) — the number of red and blue points respectively. The following N lines contain two integer numbers each — coordinates of red points. The following M lines contain two integer numbers each — coordinates of blue points. All coordinates do not exceed 109 by absolute value.

#Output

Output one integer — the number of distinct triangles with vertices in red points which do not contain any blue point inside.

#Examples
input
4 1
0 0
10 0
10 10
5 4
2 1
output
2
input
5 5
5 10
6 1
8 6
-6 -7
7 -1
5 -1
10 -4
-10 -8
-10 5
-2 -8
output
7 

#Translation 

给定平面n个红点，m个蓝点，求三个顶点由红色构成的且内部没有蓝点的三角形个数。 

##分析 
按y坐标升序排序 
这道明显是解析几何的题 
看如图
![](https://img2018.cnblogs.com/blog/1502976/201810/1502976-20181007151010754-1908206250.png)
对于一个合法的三角形，那么这三条边的toleft测试的点数一定是一样的（出去上下部） 
所以我们只用枚举边统计该边的有多少的蓝点在左侧 
然后枚举三角形的三边，看三边左边电视是否一样，如果一样，那么一定可以形成三角形
时间复杂度O（n^3）;  

其中ToLeft Text （叉积）详见 
[解析几何学习笔记](https://www.cnblogs.com/PiCaHor/p/9745919.html) 

#代码 
```cpp  
#include <bits/stdc++.h>
using namespace std;

const int N = 550;
int n,m,f[N][N],ans;

struct point
{
  long long x,y;
  bool operator < (const point &a) const
  {
    return y<a.y;
  }
} red[N],bl[N];

inline long long area(point a,point b,point c)
{
  return a.x*b.y-a.y*b.x+b.x*c.y-b.y*c.x+c.x*a.y-c.y*a.x;
}

inline bool toleft(point a,point b,point c)
{
  if(c.y<=a.y || c.y>b.y) return 0;
  return area(a,b,c)>0;
}

int main()
{
  scanf("%d%d",&n,&m);
  for(int i=1; i<=n; ++i)  scanf("%lld%lld",&red[i].x,&red[i].y);
  for(int i=1; i<=m; ++i)  scanf("%lld%lld",&bl[i].x,&bl[i].y);
  sort(red+1,red+1+n);
  for(int i=1; i<n; ++i)
    for(int j=i+1; j<=n; ++j)
      for(int k=1; k<=m; ++k)
        if(toleft(red[i],red[j],bl[k]))
          f[i][j]++;
  for(int i=1; i<n; ++i)
    for(int j=i+1; j<n; ++j)
      for(int k=j+1; k<=n; ++k)
        if(f[i][j]+f[j][k]==f[i][k])
          ans++;
  printf("%d\n",ans);
  return 0;
}

```

---

