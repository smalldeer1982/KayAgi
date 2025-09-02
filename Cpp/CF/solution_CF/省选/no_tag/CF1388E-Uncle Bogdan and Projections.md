# Uncle Bogdan and Projections

## 题目描述

After returning to shore, uncle Bogdan usually visits the computer club "The Rock", to solve tasks in a pleasant company. One day, uncle Bogdan met his good old friend who told him one unusual task...

There are $ n $ non-intersecting horizontal segments with ends in integers points on the plane with the standard cartesian coordinate system. All segments are strictly above the $ OX $ axis. You can choose an arbitrary vector ( $ a $ , $ b $ ), where $ b < 0 $ and coordinates are real numbers, and project all segments to $ OX $ axis along this vector. The projections shouldn't intersect but may touch each other.

Find the minimum possible difference between $ x $ coordinate of the right end of the rightmost projection and $ x $ coordinate of the left end of the leftmost projection.

## 说明/提示

In the first example if we project segments along the vector $ (1, -1) $ then we get an answer $ 12-3=9 $ and (it can be proven) it is impossible to get less.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388E/7a162b2d634a087b55fa87bc9c25d1618a19da15.png)It is optimal to project along the vector $ (1, -3) $ in the second example. The answer is $ 8\frac{2}{3}-2\frac{1}{3}=6\frac{1}{3} $

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388E/71a67c43df81257b1d2cff0fce891d8bbda0570c.png)

## 样例 #1

### 输入

```
3
1 6 2
4 6 4
4 6 6```

### 输出

```
9.000000000```

## 样例 #2

### 输入

```
3
2 5 1
4 6 4
7 8 2```

### 输出

```
6.333333333```

## 样例 #3

### 输入

```
2
1 3 1
4 7 1```

### 输出

```
6.000000000```

# 题解

## 作者：Flan (赞：2)

为了方便处理，先翻转一下坐标系，使得原来的 $x$ 正半轴变为 $y$ 正半轴，原来的 $y$ 正半轴变为 $x$ 负半轴，如图所示。  
![vector1](https://cdn.luogu.com.cn/upload/image_hosting/lbhf62qz.png)  
这样规避了斜率不存在的情况。  
由于题目要求线段的投影不相交，于是对于任两个不同线段 $i, j$，都有 $k \notin (\min\{\frac{xr_i-xl_j}{y_j-y_i},\frac{xl_i-xr_j}{y_j-y_i}\}, \max\{\frac{xr_i-xl_j}{y_j-y_i},\frac{xl_i-xr_j}{y_j-y_i}\})$，这使我们得到了 $k$ 的可行域 $S$。  
Tutorial 中提到
>It is easy to understand that there is an optimal vector at which the value we need is minimal and at least one pair of projections is touching.

这里给出一种简要的证明：若任两个线段的投影都不相交，那么我们就一定能够增加、减小 $k$ 的值。由于投影最靠前的线段和投影最靠后的线段的 $y$ 的不同，$k$ 的改变势必能够使之投影的相对位置接近，从而减小答案。  
根据以上结论，我们可以 $O(n ^ 2 \log n)$ 求出 $n(n-1)$ 个相交点并排除可行域外的点，得到 $k$ 所有可能的取值。  
这时不能暴力地逐个求答案，使复杂度高达 $O(n^3)$。设 $f(x)$ 表示投影斜率为 $x$ 时的答案，显然 $f(x)$ 具有凸性，于是可以以 $O(n^2\log n)$ 的复杂度三分求极值。  
关于 $f(x)$ 凸性的证明：设 $x$ 为使得 $f(x)$ 取最小值的值，显然当 $x'<x$ 时 $f(x')$ 单调不增，当 $x'>x$ 时 $f(x')$ 单调不降。
```cpp
#include <bits/stdc++.h>
const double EPS = 1e-9;
const int MAXN = 2e3 + 19;
struct Line{
	int l, r, y;
}line[MAXN];
int n;
std::vector<double> v;
std::vector<std::pair<double, int> > e;
double get(double b){
	double mx = -1e18, mn = 1e18;
	for(int i = 1; i <= n; ++i) mx = std::max(mx, line[i].r + line[i].y * b), mn = std::min(mn, line[i].l + line[i].y * b);
	return mx - mn;
}
int main(){
	std::scanf("%d", &n);
	for(int i = 1; i <= n; ++i) std::scanf("%d%d%d", &line[i].l, &line[i].r, &line[i].y);
	for(int i = 1; i < n; ++i)
		for(int j = i + 1; j <= n; ++j)
			if(line[i].y != line[j].y){
				double low = double(line[i].l - line[j].r) / double(line[j].y - line[i].y);
				double upp = double(line[i].r - line[j].l) / double(line[j].y - line[i].y);
				if(low > upp) std::swap(low, upp);
				e.push_back({low + EPS, -1}), e.push_back({upp - EPS, 1});
			}
	std::sort(e.begin(), e.end());
	int g = 0;
	for(auto i : e){
		if(g == 0) v.push_back(i.first);
		else if(g == -1 && i.second == 1) v.push_back(i.first);
		g += i.second;
	}
	if(v.empty()) v.push_back(0);
	int l = 0, r = v.size() - 1;
	while(r - l > 2){
		int m1 = l + (r - l) / 3,
			m2 = r - (r - l) / 3;
		if(get(v[m2]) < get(v[m1])) l = m1;
		else r = m2;
	}
	double ans = 1e18;
	for(int i = l; i <= r; ++i) ans = std::min(ans, get(v[i]));
	std::printf("%.8f\n", ans);
}
```

---

## 作者：Leap_Frog (赞：0)

### P.S.
没题解？来补一篇。  

### Link.
[Codeforces](https://codeforces.com/problemset/problem/1388/E)  
[Luogu](https://codeforces.com/problemset/problem/1388/E)  

### Description.
给定一些和 $x$ 轴平行的线段，保证两两不交。  
现在你需要找到一个向量，使得他们按照这个向量的方向都平移到 $x$ 轴上，还是两两不交。  
最小化平移后最左端点到最右端点的距离，输出这个最小值

### Solution.
首先，我们考虑枚举向量的角度，这个东西是无限的。  
我们考虑无限转有限，因为必定是两个线段他们“擦过”时才可能取最小值。  
所以我们直接暴力找出 $O(n^2)$ 个有机会取到最小值得地方。  
然后，我们发现，两个不在同一条直线上的线段，他们平移后，取得两个端点之间肯定是无解的。  
所以我们考虑“扫描线”（CF 官方题解用词，但我觉得这根本算不上吧），把不可能的直接删掉。  
就是排序后，如果当前这个点不管不插入或插入都被一个区间覆盖着，就显然不可行。  

然后，我们得到了 $O(n^2)$ 个可行的点，每判断一个最小值是 $O(n)$ 的，总复杂度 $O(n^3)$ 无法通过。  
所以我们可以考虑有无什么特殊性质。  
我们发现了，它具有凸性质！！ ~~赶快上 wqs 二分~~  
直接三分，我们发现复杂度很优良，达到了 $O(n\log (n^2))=O(n\log n)$，可以通过此题。  
~~所以这是碾标了？~~  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),bz=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) bz=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	bz?x=-x:x;
}/*}}}*/
int n,L[2005],R[2005],Y[2005],at,bt;double b[4000005];const double eps=1e-9;
struct node{double ps;int vl;char operator<(node b) const {return ps<b.ps;}}a[4000005];
inline double chk(double vl)
{
	double mn=1e13,mx=-1e13;
	for(int i=1;i<=n;i++) mn=min(mn,L[i]-vl*Y[i]),mx=max(mx,R[i]-vl*Y[i]);
	return mx-mn;
}
int main()
{
	read(n);for(int i=1;i<=n;i++) read(L[i]),read(R[i]),read(Y[i]);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(Y[i]<Y[j])
		a[++at]=(node){1.0*(L[j]-R[i])/(Y[j]-Y[i])+eps,1},a[++at]=(node){1.0*(R[j]-L[i])/(Y[j]-Y[i])-eps,-1};
	sort(a+1,a+at+1);if(!at) a[++at]=(node){0,0};
	//for(int i=1;i<=at;i++) printf("%.10lf %d\n",a[i].ps,a[i].vl);
	for(int i=1,v=0;i<=at;v+=a[i++].vl) if(!v||!(v+a[i].vl)) b[++bt]=a[i].ps;
	//for(int i=1;i<=bt;i++) printf("%lf%c",b[i],i==bt?'\n':' ');
	int l=1,r=bt;while(l+2<r) {int md1=(l+r)>>1,md2=md1+1;if(chk(b[md1])<chk(b[md2])) r=md2;else l=md1;}
	double rs=1e13;for(int i=max(1,l-1);i<=min(r+2,bt);i++) rs=min(rs,chk(b[i]));
	return printf("%.10lf\n",rs),0;
}
```

---

