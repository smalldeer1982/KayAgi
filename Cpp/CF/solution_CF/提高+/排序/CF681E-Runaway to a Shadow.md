# Runaway to a Shadow

## 题目描述

Dima is living in a dormitory, as well as some cockroaches.

At the moment $ 0 $ Dima saw a cockroach running on a table and decided to kill it. Dima needs exactly $ T $ seconds for aiming, and after that he will precisely strike the cockroach and finish it.

To survive the cockroach has to run into a shadow, cast by round plates standing on the table, in $ T $ seconds. Shadow casted by any of the plates has the shape of a circle. Shadow circles may intersect, nest or overlap arbitrarily.

The cockroach uses the following strategy: first he equiprobably picks a direction to run towards and then runs towards it with the constant speed $ v $ . If at some moment $ t<=T $ it reaches any shadow circle, it immediately stops in the shadow and thus will stay alive. Otherwise the cockroach is killed by the Dima's precise strike. Consider that the Dima's precise strike is instant.

Determine the probability of that the cockroach will stay alive.

## 说明/提示

The picture for the first sample is given below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF681E/3b35a58e93815d2d230d24cb7d27ab6d96995987.png)Red color stands for points which being chosen as the cockroach's running direction will cause him being killed, green color for those standing for survival directions. Please note that despite containing a circle centered in $ (-2,2) $ a part of zone is colored red because the cockroach is not able to reach it in one second.

## 样例 #1

### 输入

```
0 0 1 1
3
1 1 1
-1 -1 1
-2 2 1
```

### 输出

```
0.50000000000```

## 样例 #2

### 输入

```
0 0 1 0
1
1 0 1
```

### 输出

```
1.00000000000```

# 题解

## 作者：xzggzh1 (赞：1)

一道比较容易的计算几何题。

题意:

一个蟑螂等概率随机向任意方向跑最多 $t$ 秒。

问最后停在 $n$ 个圆中的概率。

---

转化一下题意，等价于

求一个圆和其他所有圆的交集所对的角度的并集。（表述可能略有偏差）

对于每一个圆都分类讨论和一开始圆的交集所对的角度。

然后把这些角度放到一个容器里合并然后算出概率。

需要注意精度的优化。


```cpp

#define  sqr(x)  ((x)*(x))
const double  eps = 1E-9;
const double  PI = acos(-1.0);
inline double  dist2(double  x1,double  y1,double  x2,double  y2) {
	return sqr(x1-x2)+sqr(y1-y2);
}
vector<pair <double,double >  > a;
vector<pair <double,double >  >::iterator it;
int main() {
	int x0, y0, v, T, n, x, y, r;
	double  R, d, ang, angM, angL, angR, last, ans;
	scanf("%d%d%d%d%d", &x0, &y0, &v, &T, &n);
	R = (double )v * T;
	while (n --> 0) {
		scanf("%d%d%d", &x, &y, &r);
		d = dist2(x,y,x0,y0);
		if (d < 1.0 * r * r + eps) {//若圆心被包含 
			printf("%.11f", 1.0);
			return 0;
		}
		d = sqrt(d);
		if (R+r < d-eps) continue;//无交集 
		angM = atan2(y-y0,x-x0);
		if (angM < 0) angM += 2*PI;
		if (sqrt(d*d-1.0*r*r) < R+eps) ang = asin(r / d); else ang = acos((d*d+R*R-1.0*r*r) / (2*d*R));
		angL = angM-ang, angR = angM+ang;
		if (angL < 0) {
			a.push_back(make_pair(angL+2*PI,1));
			a.push_back(make_pair(2*PI,-1));
			a.push_back(make_pair(0,1));
			a.push_back(make_pair(angR,-1));
		} else if (angR > 2*PI) {
			a.push_back(make_pair(angL,1));
			a.push_back(make_pair(2*PI,-1));
			a.push_back(make_pair(0,1));
			a.push_back(make_pair(angR-2*PI,-1));
		} else {
			a.push_back(make_pair(angL,1));
			a.push_back(make_pair(angR,-1));
		}
	}
	sort(a.begin(),a.end());
	for (last = ans = x = 0, it = a.begin(); it != a.end(); it ++ ) {
		if (x > 0) ans += it->first-last;
		x += it->second;
		last = it->first;
	}
	printf("%.11f\n", ans/(2*PI));
}

```

---

## 作者：skyskyCCC (赞：0)

## 前言。
基础读懂计算几何，就是细节比较繁琐罢了。

顺便提一嘴，虽然这个题目翻译很简短，但是该有的要点都有。
## 分析。
给定坐标，这就不得不考虑建系了。建立一个平面直角坐标系，以蟑螂的坐标作为原点，那么既然让我们去求停在 $n$ 个圆的概率，那么我们只要求出以原点为圆心，半径为 $T\times v$ 的圆 $O$ 和其它每个圆相交的部分的弧度即可。然后在求出并集来。如果我们设并集的大小为 $k$ 则概率就是 $\frac{k}{2\times\pi}$。这个公式应该不用多解释了。

求弧度的并集可以采用余弦定理。简单来说，由初中知识可得，当原点与交点的连线 $l_i$ 与圆相切的时候，弧度到达最大，那么在计算的时候只要将 $l_i$ 跟切线长取最小值即可。再利用小圆的圆心与 $x$ 轴正方向的弧度，就可以求出两个边界的弧度了。最后的总并集就是每个上面求出的边界的弧度的并集。

最后注意一下精度就行了。

代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
#define eps 1e-9
#define mp(a,b) make_pair(a,b)
const double pi=acos(-1);
double a,b,v,t,x,y,r;
double dy,dx,d,tot,eg,ans;
double leftt;
int n,sum;
pair<double,double> ve[100005*2];
int main(){
	scanf("%lf %lf %lf %lf %d",&a,&b,&v,&t,&n);
	for(int i=0;i<n;i++){
		scanf("%lf %lf %lf",&x,&y,&r);
		dy=y-b;
		dx=x-a;
		d=sqrt(dy*dy+dx*dx);
		if(d*d<r*r+eps){
			printf("1.0000000000\n");
			return 0;
		}
		if(v*t+r<d-eps){
	        continue;
	    }
		tot=atan2(dy,dx);
		if(tot<0){
		    tot+=2.0*pi;
		}
		if(v*t+eps>sqrt(d*d-r*r)){
		    eg=asin(r/d);
		}
		else eg=acos(v*t/d/2.0+(d*d-r*r)/v/t/d/2.0);
		if(tot+eg>2.0*pi){
			ve[sum++]=mp(0,tot+eg-2.0*pi);
			ve[sum++]=mp(tot-eg,2.0*pi);
		}
		else if(tot-eg<0.0){
			ve[sum++]=mp(tot-eg+2.0*pi,2.0*pi);
			ve[sum++]=mp(0,tot+eg);
		}
		else ve[sum++]=mp(tot-eg,tot+eg);	
	}
	sort(ve,ve+sum);
	for(int i=0;i<sum;i++){
		if(i==0||ve[i].first>leftt){
			ans+=ve[i].second-ve[i].first;
			leftt=ve[i].second;
		}
		else if(ve[i].second>leftt){
			ans+=ve[i].second-leftt;
			leftt=ve[i].second;
		}
	}
	printf("%.10lf\n",ans/pi/2.0);
	return 0;
}
```
## 后记。
这个题用余弦定理有一个坑点，就是弧度的取值范围是 $\left[0,2\times\pi\right]$ 所以根据任意角的余弦值的定义，对于 $a-b<0$ 和 $a+b>2\times\pi$ 的情况特别处理一些即可。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

