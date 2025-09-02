# Polygon

## 题目描述

Polycarpus loves convex polygons, especially if all their angles are the same and all their sides are different. Draw for him any such polygon with the given number of vertexes.

## 样例 #1

### 输入

```
8
```

### 输出

```
1.000 0.000
7.000 0.000
9.000 2.000
9.000 3.000
5.000 7.000
3.000 7.000
0.000 4.000
0.000 1.000
```

# 题解

## 作者：tzc_wk (赞：2)

[Codeforces 题目传送门](https://codeforces.com/contest/306/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF306D)

中考终于结束了……简单写道题恢复下状态罢。

首先这一类题目肯定没法用一般的方法解决，因此考虑用一些奇淫的乱搞做法解决这道题，不难发现，如果我们固定住了前 $n-1$ 条边，那么第 $n$ 条边的长度与前 $n-1$ 条边的长度冲突的概率是小之又小了——这个用爪子想想即可明白。

因此考虑一个乱搞做法，我们每次随机前 $n-1$ 条边的长度 $l_1,l_2,\cdots,l_{n-1}$，然后从原点开始绕一圈每次旋转 $\dfrac{2\pi}{n}$ 补全这个 $n$ 边形，如果最后一条边的长度与前 $n-1$ 条边长度均不同且在 $(0,1000]$ 之内则直接输出。

这样一来倒是避免边长度相同的问题了，但同时还会带来另一个问题，就是如果有可能我们随机出来的图形不是凸图形，比如说下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lrlbe2ps.png)

解决方法倒也容易，把每条边随机的范围变小一点即可，我是将第 $i$ 条边的长度设为 $600+0.1i$ 然后 `random_shuffle`，这样就不太可能出现这样的情况了。

思路出来了，剩下就是实现的问题了，旋转 $\dfrac{2\pi}{n}$ 我拿复数乘法实现的，最后第 $n$ 个点的位置需解个直线方程。

随机次数最多大概是 $2$（别问我怎么知道的 qwq），时间复杂度 $\mathcal O(\text{能过)}$

```cpp
const int MAXN=100;
const double Pi=acos(-1);
const double EPS=1e-6;
int n;
double len[MAXN+5];
struct point{
	double x,y;
	point(double _x=0,double _y=0):x(_x),y(_y){}
	point operator +(const point &rhs) const{return point(x+rhs.x,y+rhs.y);}
	point operator -(const point &rhs) const{return point(x-rhs.x,y-rhs.y);}
	point operator *(const double &rhs) const{return point(x*rhs,y*rhs);}
	point operator /(const double &rhs) const{return point(x/rhs,y/rhs);}
	double operator ~() const{return sqrt(x*x+y*y);}
} p[MAXN+5];
int main(){
	srand(time(0));scanf("%d",&n);
	if(n<=4) return puts("No solution")&0;
	double ang=2*Pi/n;
	while(1){
		for(int i=1;i<n;i++) len[i]=600+i*0.1;
		random_shuffle(len+1,len+n);
		p[1]=point(0,0);p[2]=point(len[1],0);
		for(int i=3;i<=n;i++){
			point dif=p[i-1]-p[i-2];
			point coe=point(cos(ang),sin(ang));
			point nw=point(dif.x*coe.x-dif.y*coe.y,dif.x*coe.y+dif.y*coe.x);
			nw=nw*(len[i-1]/len[i-2]);
			if(i^n) p[i]=p[i-1]+nw;
			else{
				double k1=nw.y/nw.x;
				double b=p[i-1].y-k1*p[i-1].x;
				double k2=tan(Pi/n*(n-2));
				p[i].x=b/(k2-k1);p[i].y=k2*p[i].x;
			}
		} bool flg=(~(p[1]-p[n])<1000+EPS);
		for(int i=1;i<n;i++) flg&=(fabs((~(p[1]-p[n]))-len[i])>EPS);
		if(flg) break;
	}
	for(int i=1;i<=n;i++) printf("%.10lf %.10lf\n",p[i].x,p[i].y);
	return 0;
}
```



---

## 作者：Lightwhite (赞：1)

[不好的阅读体验。](https://www.cnblogs.com/Lightwhite/p/18034771)

题意：给定一个 $n$，构造一个边长两两不等，内角两两相同的 $n$ 边形。

发现可以构造一个正 $n$ 边形，然后对每条边加以不同且很小的边长偏扰，比如逆时针考虑，对第 $i$ 条边加上 $i\epsilon$。但是这样多边形无法闭合，否则角度不同。所以可以特殊考虑最后一个点位置。令第一个点在原点上，多边形始终在 $x$ 轴之上，最后一条边在 $x$ 轴上，那么最后一个点就直接按照角度求与 $x$ 轴交点。

那为什么这个构造方案他不会出现边长相同呢？首先前 $n-2$ 条边是递增的。把这些边分为左右两边，因为边长递增，所以右边除去第一条边的向上长度短于左边，所以第 $n-1$ 条边短于第 $1$ 条边，也短于其他所有边。同理，把这些边分成上下两部分，本来应该是边长相近的，但是第 $n-1$ 条边遥遥落后于其他边，所以第 $n$ 条边就要遥遥长于其他边。

代码非常好写。

```cpp
// STOOOOOOOOOOOOOOOOOOOOOOOOO hzt CCCCCCCCCCCCCCCCCCCCCCCORZ
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using LL = long long;
using PII = pair<int, int>;

int n;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  if (n < 5) {
    cout << "No solution\n";
    return 0;
  }
  double agl = 0, c = acos(-1) * 2 / n, len = 500;
  double x = 0, y = 0;
  cout << fixed << setprecision(3);
  for (int i = 1; i < n; i++) {
    cout << x << ' ' << y << '\n';
    agl += c, len += 1e-2;
    i < n - 1 && (x += len * cos(agl), y += len * sin(agl));
  }
  cout << x - y / tan(agl) << ' ' << 0 << '\n';
  return 0;
}
```

---

## 作者：Mr_RoastFish (赞：0)

~~本题解偏想象类，恕鄙人实力菜没法给出严谨的证明~~

首先明确一个点，$n\le4$ 时没有解。

先考虑要满足的条件：内角相等。很显然，正凸多边形的内角相等。但题目要求边长都不相同，所以考虑在保证角度不变的前提下对各边长进行微调。这个微调很灵性，调的好万事大吉，调不好就圆不上凸多边形的要求。

也就是说，我们要让这个凸多边形的边长差距尽可能小，从感官上讲就是看不出来各边实际长度不同（有点像手画几何题草图，虽然肯定没法和尺规作图比，但是不影响做题）。我们把长度差设成 $0.01$，这样在乘上正弦和余弦算坐标时精度就达到了要求的最小值 $0.001$。

然后考虑边的初始长度，这个值不能太小，不然边数一大就可能跑到画的第一条边以下，这肯定是不符合要求的。可以自己测试一下结果进行调整，开到 $500$ 就可以了。最后注意下最后一个点要能和原点接成凸多边形，直接强制把最后一个点按在横轴上就好（计算一下第一条边的斜率摆个直线方程接过去也可以）。

具体看看代码吧（讲的可能不太具体）。


```cpp
#include<bits/stdc++.h>
using namespace std;
void read(int &x){
	x=0;int f=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')     f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	x*=f;
}
int main(){
	double n;
        cin>>n;
	if(n<=4)	printf("No solution"),exit(0);
	double c=acos(-1)*2.0/n,len=500,ang=0,x=0,y=0;
	for(int i=1;i<n-1;i++){
		printf("%.3lf %.3lf\n",x,y); 
		len+=0.01,ang+=c;
		x+=len*cos(ang),y+=len*sin(ang);
	}
	printf("%.3lf %.3lf\n",x,y);
	printf("%.3lf 0",x-y/tan(ang+c));
	return 0;
}

```

---

