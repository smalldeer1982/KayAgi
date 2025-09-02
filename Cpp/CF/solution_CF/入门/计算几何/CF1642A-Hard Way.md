# Hard Way

## 题目描述

# 题面简述

Sam 住在 Awesomeburg，其市中心为三角形。 此外，三角形满足：

- 它的顶点具有整数坐标。
- 它的顶点具有非负坐标。
- 它的顶点不会共线。

如果他可以从 X 轴的至少一个点沿着某条直线行走而不穿过三角形的内部，他就称市中心边界上的一个点（即三角形的边界）是安全的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1642A/e2013fd23336b6f6190b1c93f2f1758325693e6d.png)

在图片中，市中心用灰色标记。

第一条路径无效，因为它不沿着直线走。

第二条路径无效，因为它与市中心的内部相交。

第三条和第四条路径是正确的。

求市区边界不安全部分的总长度。 可以证明，这些部分是段，它们的数量是有限的。

## 样例 #1

### 输入

```
5
8 10
10 4
6 2
4 6
0 1
4 2
14 1
11 2
13 2
0 0
4 0
2 4
0 1
1 1
0 0```

### 输出

```
0.0000000
0
2.0000
0.00
1```

# 题解

## 作者：FFTotoro (赞：1)

一道几何好题。

我们观察题目可以发现，只有在三角形的一条边平行于 x 轴且三角形的另外两条边都比它更靠近 x 轴时，才有可能存在所谓不安全的点。

所以只要判断平行，然后再验证是否在其他两条边上面即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int x1,y1,x2,y2,x3,y3; cin>>x1>>y1>>x2>>y2>>x3>>y3;
    if(y1==y2 /* 平行 */ &&y3<y1 /* 判断边是否在上面 */ )cout<<abs(x2-x1)<<endl;
    else if(y1==y3&&y2<y1)cout<<abs(x3-x1)<<endl;
    else if(y2==y3&&y1<y2)cout<<abs(x3-x2)<<endl;
    else cout<<"0\n";
  }
  return 0;
}
```

---

## 作者：Suzt_ilymtics (赞：1)

### Description

> $T$ 组数据，每组数据给你一个三角形，计算有多长的三角形边“不安全”。
>
> 我们这样定义“安全”，一个三角形边上的点“安全”，当且仅当存在一条线段满足经过该点和 $x$ 轴上一点且没有经过三角形内部。反之则“不安全”

### Solution

不难发现，如果一个线段斜率不为 $0$，那么整个线段上的点都是“安全”的。

当一个线段斜率为 $0$ 时，如果这条线段在三角形底部，则它是“安全”的，否则它是“不安全”的，输出它的长度即可。

具体做法：根据横纵坐标随便判断一下即可。

### Code

仅放部分代码：

```cpp
int T;
bool cmp(node x, node y) { return x.y < y.y; }

void Main() {
    for(int i = 1; i <= 3; ++i) a[i].x = read(), a[i].y = read();
    sort(a + 1, a + 4, cmp);
    if(a[2].y == a[3].y) {
        printf("%d\n", abs(a[2].x - a[3].x));
    } else {
        puts("0");
    }
}

int main()
{
    T = read();
    while(T--) Main();
    return 0;
}

```

---

## 作者：落花月朦胧 (赞：1)

# 题目大意：


给出一个三角形，求不完全的线的长度。

不安全的定义是指从 $x$ 轴上没有一个点满足：这个点和被检验的点所连接的直线不穿过这个三角形的内部。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1642A/e2013fd23336b6f6190b1c93f2f1758325693e6d.png)

比如这个样例。

第一条线是不满足题意的，因为它不是直线。

第二条线也是不满足题意的，但是它穿过了这个三角形的内部， 

第三条线和第四条线都是满足题意的，这两个连接的点也都是安全的。

# 解题

可以把这个三角形分为三条线段，对每一条线段思考。

用解析式表示一条线段，可以发现如果这个一次函数不是一个常函数，在数轴上一定可以找到一个点连接到这条线段而不经过三角形的内部。

若延长这条线段，与数轴的交点以右的所有点都可以满足题意。

反之，如果这条线段是一个常函数，与数轴就没有交点，就是不满足题意的点。

本题就转换为了一个求和 $x$ 轴平行的线的长度。

模拟一下就可以了。

```cpp
/*
Writer:ZhengXiangYu
*/
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define fre(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

using i64 = long long;
constexpr i64 eps = 1e-9;
constexpr i64 N = 5;
 
struct node {
  i64 x, y;
} a[N + 1];
int main() {
  IOS;
  
  i64 T;
  std::cin >> T;
  while (T--) {
  	for (i64 i = 1; i <= 3; i++) {
	  std::cin >> a[i].x >> a[i].y;
	}
	i64 p = -1, q = -1, s = -1;
	for (i64 i = 1; i <= 3; i++) {
	  for (i64 j = i + 1; j <= 3; j++) {
		if (a[i].y == a[j].y && a[i].y && a[j].y) {
		  q = i, p = j, s = 6 - i - j;
		  break;
		}  
	  }
	}
//	std::cout << p << " " << q << " " << s << "\n";
	if (p == -1 || q == -1) {
	  std::cout << 0 << "\n";
	} else {
	  if (a[s].y <= a[p].y) {
	  	std::cout << abs(a[p].x - a[q].x) << "\n";
	  } else {
	  	std::cout << 0 << "\n";
	  }
	}
  }
  return 0;
}
```

---

## 作者：windflower (赞：0)

很简单的一道题目：  
显然只有一条边与 x 轴平行且三角形在它下方才是不安全的。因为其他情况都可以取 x 趋向正负无穷的情况来找到安全点。  
利用排序函数就可以很方便的解决，以纵坐标为关键词排序，若最大的两点纵坐标相同，则这条边是不安全的。  
（如果只要求判断是否安全的话，只需要纵坐标就够了，这题横坐标只用于求不安全线段的长度）  
附 AC 代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
struct T{
	int x,y;
	bool operator<(T t){return y<t.y;}
}a[3];
int main(){
	cin>>t;
	while(t--){
		for(int i=0;i<3;i++)cin>>a[i].x>>a[i].y;
		sort(a,a+3);
		cout<<(a[1].y==a[2].y?abs(a[1].x-a[2].x):0)<<endl;
	}
	return (0-0);
}
```


---

## 作者：lichenghan (赞：0)

~~为什么这么少题解呢~~

# Codeforces 1642A 题解

[传送门](https://www.luogu.com.cn/problem/CF1642A)
## Problem
给定一个三角形，说一个三角形边上的点是安全的，当且仅当存在一条一个端点在这个点上，另一个端点在 $x$ 轴上且不穿过三角形内部。

问这个三角形三边有多长是不安全的。
## Solution
很显然，如果一条边的斜率不为 $0$ ，那么这整条边都是安全的。

如果一条边斜率为 $0$ 且这条边在三角形的下方，那么这整条边也是安全的。

如果一条边斜率为 $0$ 且这条边在三角形的上方，那么这整条边（除端点外）都是不安全的。

而且，题目保证三点不共线，所以只会有 $0$ 或者 $1$ 条边是不安全的。

按照上面的方式判断每一条边是否安全即可。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
struct pt{
	double x,y;
	void read(){
		scanf("%lf%lf",&x,&y);
	}
};
struct seg{
	pt s,e;
	double slope(){
		return (s.y-e.y)/(s.x-e.x);
	}
	double len(){
		return sqrt((s.x-e.x)*(s.x-e.x)+(s.y-e.y)*(s.y-e.y));
	}
};
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		pt A,B,C;
		seg a,b,c;
		A.read();B.read();C.read();
		a={B,C};b={A,C};c={B,A};
		if(a.slope()==0.0&&(A.y<B.y)){
			printf("%.12lf\n",a.len());
		}
		else if(b.slope()==0.0&&(B.y<A.y)){
			printf("%.12lf\n",b.len());
		}
		else if(c.slope()==0.0&&(C.y<A.y)){
			printf("%.12lf\n",c.len());
		}
		else puts("0");
	}
}
```

---

## 作者：_Fatalis_ (赞：0)

### Solution

关于某一条线段是否是安全的（以下不考虑端点），有两个结论。

1. 不是平行于 $y=0$ 的线段必定是安全的；
2. 若这条线段中较低的点（即 $y$ 坐标较小的点）下方没有其他边，那么这条线段必定是安全的。

第二条结论显而易见，可以直接从三角形正下方的点通过直线到达。

第一条结论，斜着的线段无论多斜，我都可以从线段两侧中任意选择一侧的点到达。

![](https://cdn.luogu.com.cn/upload/image_hosting/yl6o3g0n.png)

如图，$AB$ 为原线段，延长 $AB$ 至 $D$ 交 $x$ 轴于 $D$。在 $D$ 左侧任意找一点 $E$ 都可以通过直线到达 $AB$ 上的点 $(C)$。

结合下两个结论，只有一种可能有不安全的线段。即：

一个三角形中，有一条线段平行于 $y=0$，并且还是三角形较高的边。

比如样例第三组数据，

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1642A/bd252d53633e695cb006d77cf34133cf6ce27f27.png)

就是符合这些要求的三角形。

解法已经有了，如何~~更好的~~写~~更简单的~~代码呢？

用 `struct` 存端点，用 `sort` 简化代码。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x,y;
    void read(){
        cin>>x>>y;
    }
    bool operator < (Point b) const
    {
        if(y==b.y) return x>b.x;
        return y>b.y;
    }
}a[3];

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        a[0].read();a[1].read();a[2].read();
        sort(a,a+3);
        if(a[0].y==a[1].y) cout<<abs(a[0].x-a[1].x);
        else               cout<<0;
        puts("");
    }
}
```

~~我有一个小疑问，题目中对浮点误差的处理有何意义？反正都是整数~~

---

## 作者：hank0402 (赞：0)

### 题目大意：

给定一个三角形的坐标，求出一条边的长度，该边满足：平行于 $x$ 轴，而且至少存在一个点离 $x$ 轴的距离比此边离 $x$ 轴的距离近。

### 思路：

根据题意，将三个点按 $y$ 坐标从小到大排序，枚举边，有三种情况：

- 平行于 $x$ 轴，$y$ 坐标是正整数。

如果该边两个端点不是前两点，答案为此边长度

- 平行于 $x$ 轴，$y$ 坐标是非负数。

如果该边两个端点不是后两点，答案为此边长度。

- 不平行于 $x$ 轴。

答案不可能是此边。

复杂度 $O(T)$. 因为边数很少，所以当做常数项。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T; 
struct point {
	int x, y;
}a[4];
bool cmp(point x, point y) {
	return x.y < y.y; //按y排序
}
void solve(point a[]) {
	int ans = 0;
	for(int i = 1; i <= 3; ++i) {
		for(int j = i + 1; j <= 3; ++j) {
			if(a[i].y == a[j].y && ((a[i].y >= 0 && i != 1) || (a[i].y < 0 && i != 3))) ans += abs(a[i].x - a[j].x); //累加答案
		}
	}
	printf("%d.000000000\n", ans); //题目要求
}
int main() {
	cin >> T;
	while(T --) { //多组数据
		int x[4], y[4];
		for(int i = 1; i <= 3; ++i) cin >> a[i].x >> a[i].y;
		sort(a + 1, a + 3 + 1, cmp);
		solve(a);
	}
	return 0;
}
```

---

## 作者：西湖水妖 (赞：0)

### 题意简述

+ 在平面直角坐标系中，给定一个三角形，三个顶点的坐标分别为 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$。
+ 如果连结这个三角形的三条边上的一个点，和 y 轴上的至少一个点的线段，不经过这个三角形的内部，那么称这个点是安全的。
+ 你需要求出这个三角形三条边上不安全部分的总长度。
+ 有 $t$ 组数据，$1\le{t}\le1000,0\le{x_i}\le10^9,0\le{y_i}\le10^9$ 并且 $x_i,y_i$ 都是整数。你的答案和标准答案相差不超过 $10^{-9}$ 视为正确。

### 题目分析

小心不要被误导了。输出可以是实数，甚至连答案正确的公式都给出了，但是其实输出一定是整数。

首先观察样例，发现大多数情况下答案都是 $0$，于是我们重点观察答案不是 $0$ 的情况，发现都有一条边是平行于 y 轴的，并且这条边都在三角形的顶部，因为如果在底部，那么这条边上的点肯定都安全。

对于样例来讲，答案就是上述边的长度，那么是不是都这样呢？考虑反证法。假设上述边是安全的，那么这条边上的点都是安全的。我们考虑其中任意一个点，它向下的路径全部都被三角形堵死了，只能向上连结或者平行于 y 轴连结，显然不能连结到 y 轴上的点，所以假设错误，原结论成立。于是答案就出来了。

如果你难以理解，也可以这样想，如果把含有上述边的三角形稍微旋转一点，你就一定可以从 y 轴很远处找到一个点，和上述边上的点连结不经过三角形，不旋转就找不到这个点。

具体代码实现可以看代码。

### 代码

```cpp
if(Y1 == y3)
{
    swap(x2, x3);
    swap(y2, y3);
}
if(y2 == y3)
{
    swap(x1, x3);
    swap(Y1, y3);
}
/*以上两个 if 语句保证如果有两个点 y 坐标相等，
那么保证它们的位置在前面两个，这样方便之后操作。*/
if(Y1 == y2) //判断是否有两个点 y 坐标相等。
    if(Y1 > y3) //如果相等的点的 y 坐标比另一个点的 y 坐标大，这条边就是答案。
        cout << abs(x1 - x2) << endl;
    else //没有题目分析里的边，答案为 0。
        cout << 0 << endl;
else
    cout << 0 << endl;
```

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1642A)

题意：给一个三角形的三个顶点，问所有不能从 $x$ 轴上连一条直线到达的点组成的线段的长度。

显然这样的线段必定平行于 $x$ 轴，且另外一个顶点必然在这条平行线下方。

所以直接判断一下是否有两个点的纵坐标相等，并且第三个点的纵坐标比这两个点小即可。

时间复杂度 $O(t)$。

---

## 作者：miao5 (赞：0)

这道题给你一个三角形三个顶点的坐标，问从 $y$ 轴任意一点画一条直线，不经过三角形内部不能到达的线段有多长。

这道题显然三角形靠下的两条边都是肯定能到达的，所以最终的答案就取决于最靠上的那条线段。

我们发现如果最靠上的线段平行于 $y$ 轴，那么它是无法到达的。否则是可以到达的。这样我们就可以判断两个横坐标较大的点横坐标是否相同，如果相同的话就是平行于 $y$ 轴的。这样我们就输出这两个点的纵坐标差的绝对值就可以了，否则答案为 $0$。

```
#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int a,b,c,d,x,y;
		cin>>a>>b>>c>>d>>x>>y;
		if(b<d&&y==d) cout<<abs(x-c)<<endl;
		else if(d<b&&b==y) cout<<abs(a-x)<<endl;
		else if(y<b&&b==d) cout<<abs(a-c)<<endl;
		else cout<<0<<endl;
	}
}
```

---

## 作者：ttq012 (赞：0)

数学题。

三角形的三个坐标 $(x_i, y_i)$ 满足 $x_i, y_i\ge 0$。

那么我们分类讨论即可。

先从样例下手。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1642A/97925eac9d0b542d0fbf94894a34867df09a7fd0.png)

我们发现，蓝色的三角形可以通过这三条黑色的边来到达它的三个边。

[![A1.png](https://i.postimg.cc/3rnQ1jHV/A1.png)](https://postimg.cc/yWgGYZxy)

黄色的三角形可以通过这三条黑色的边来到达它的三个边。

[![A1.png](https://i.postimg.cc/5ytGTGMG/A1.png)](https://postimg.cc/r0vQtfsC)

而红色的三角形只能到达它的两条边。

[![A1.png](https://i.postimg.cc/G2gz8mZ7/A1.png)](https://postimg.cc/BLD2R4ZH)

通过上面的分析，我们可以发现，只有红色的三角形会有一条不安全的边，这一条最上面的边是顶上的那一条边。

这一条边的长度就是 $|x_i - x_j|$。

那么我们直接模拟即可。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

struct node {
    int x, y;
    bool operator < (const node & _2) {
        return y < _2.y || y == _2.y && x < _2.x;
    }
} a[5];

signed main() {
    int t;
    cin >> t;
    while (t --) {
        for (int i = 1; i <= 3; i ++)
            scanf ("%d%d", &a[i].x, &a[i].y);
        sort (a + 1, a + 4);
        double ans = 0;
        if (a[2].y == a[3].y && a[1].y < a[3].y && a[1].y < a[2].y) // 红色三角形的那一种情况
            printf ("%d\n", a[3].x - a[2].x);
        else
            puts("0");
    }
    return 0;
}

```


---

## 作者：jiangtaizhe001 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/15932359.html)  
[题目传送门](https://codeforces.com/problemset/problem/1642/A)
## 题目大意
在平面直角坐标系上，有一个三角形，给出三角形的三个顶点的坐标 $(x_i,y_i)$，其中 $x_i,y_i$ 均为整数且 $0\le x_i,y_i\le 10^9$。  
如果存在一条线段，这条线段的端点在 $x$ 轴上，另一个端点在三角形上，并且这条线段不穿过三角形内部，那么就称三角形上的这个点是安全的。  
现在要求 **不是** 安全的点组成的线段（或者是折线）的长度。  
## 题目解析
首先，不难证明，如果一条边的斜率不等于 $0$，那么这条线段上的点肯定是安全的。  
证明如下：  
如果第三个点在这条线段上方，那么直接做一条到 $x$ 轴的垂线即可。否则就过这一点做一条斜率的绝对值比原来的线段更小并且同号的线段即可。

也就是说我们只需要考虑斜率等于 $0$ 的线段。  
这时需要分类讨论。  
如果三角形的另一个点在这条线段上方，我们只需要作一条到 $x$ 轴的垂线就可以的。  
如果三角形的另一个点在这条线段下方，那么这条线段上的点（除了线段端点）不是安全的点。

因此枚举三条边判断即可。

代码（主要部分）：
```cpp
struct JTZ{
	ll x,y;
}a[39];
db dis(JTZ x,JTZ y){ return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y)); }
void work(){
	int i; db ans=0;
	for(i=1;i<=3;i++) a[i].x=read(),a[i].y=read();
	if(a[1].y==a[2].y&&a[3].y<a[1].y) ans+=dis(a[1],a[2]);
	if(a[1].y==a[3].y&&a[2].y<a[1].y) ans+=dis(a[1],a[3]);
	if(a[2].y==a[3].y&&a[1].y<a[2].y) ans+=dis(a[2],a[3]);
	printf("%lf\n",ans);
}
```

---

## 作者：heaksicn (赞：0)

## 1 题意
在第一象限内有一个三角形，你可以从 $x$ 轴的任意一个点出发，沿一条直线走到三角形三边的某一个点上，但不能穿过三角形内部。

问三角形三边上有多长的距离是不能走到的。

多组数据
## 2 思路
考虑题目描述中给到的三角形。

我们可以发现，无论在 $x$ 轴上取哪一个点，都无法走到三边中**与 $x$ 轴平行的那条边**。

推广一下，得到：在一个三角形内，如果有两点组成的一条边平行于 $x$ 轴，并且第三点的 $y$ 坐标小于前两个点的 $y$ 坐标，那么答案就是平行于 $x$ 轴的边的长度。

否则输出 $0$。

时间复杂度 $O(T)$。
## 3 code
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int T; 
int x[4],y[4];
int main(){
	T=read();
	while(T--){
		for(int i=1;i<=3;i++) x[i]=read(),y[i]=read();
		int ans=0;
		for(int i=1;i<=3;i++){
			for(int j=i+1;j<=3;j++){//枚举前两个点
				int k=6-i-j;//第三个点
				if(y[i]==y[j]&&y[k]<y[i]){//平行于x轴且纵坐标大
					ans+=abs(x[i]-x[j]);
				}
			}
		}
		write(ans);
		puts("");
	}
	return 0;
}

```


---

