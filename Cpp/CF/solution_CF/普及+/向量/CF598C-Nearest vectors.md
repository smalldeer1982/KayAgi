# Nearest vectors

## 题目描述

You are given the set of vectors on the plane, each of them starting at the origin. Your task is to find a pair of vectors with the minimal non-oriented angle between them.

Non-oriented angle is non-negative value, minimal between clockwise and counterclockwise direction angles. Non-oriented angle is always between $ 0 $ and $ π $ . For example, opposite directions vectors have angle equals to $ π $ .

## 样例 #1

### 输入

```
4
-1 0
0 -1
1 0
1 1
```

### 输出

```
3 4
```

## 样例 #2

### 输入

```
6
-1 0
0 -1
1 0
1 1
-4 -5
-4 -6
```

### 输出

```
6 5```

# 题解

## 作者：XL4453 (赞：9)

### 题目分析：

基本的反三角函数（数学上写作 $\arctan(x)$ 等）在 cmath 库中是直接在三角函数前面加一个 a，例如反正切函数就是 atan。作用是给出一个三角函数值，返回其对应的角度值（弧度制）。

但是发现，在任意角的定义下，一般的反三角函数并不能满足象限上的要求，于是就有了 atan2 这个函数。这个函数需要你给出两个参数，分别是 $x,y$ 表示求 $\dfrac{y}{x}$ 的反正切值，这个函数要比普通的 atan 稳定，一般不会随便 RE。

------
回到这道题目，首先求出每一个角与 $x$ 轴的夹角，并将其转换为正角（atan2 的返回值是 $(-\pi,\pi]$，转化一下更方便），然后按照角的大小排序，每一次选择相邻的两项比较。

注意第一个角和最后一个角也是邻近的角，所以也需要判断。

实现上，可以用一个结构体记录下每一个角的大小和编号并用 algorithm 库里的快排实现排序。

----
### 代码：

```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
long  double Pi=acos(-1);
struct node{
	int x,y,id;
	long double a;
}p[100005];
bool cmp1(node a,node b){
	return a.a<b.a;
}
int n,ans1,ans2;
long double ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&p[i].x,&p[i].y);
		p[i].a=atan2(p[i].x,p[i].y);
		if(p[i].a<0)p[i].a+=2*Pi;
		p[i].id=i;
	}
	sort(p+1,p+n+1,cmp1);
	ans=p[1].a-p[n].a+2*Pi;
	ans1=p[n].id;ans2=p[1].id;
	for(int i=2;i<=n;i++){
		if(p[i].a-p[i-1].a<ans){
			ans=p[i].a-p[i-1].a;
			ans1=p[i-1].id;
			ans2=p[i].id;
		}
	}
	printf("%d %d",ans1,ans2);
	return 0;
}
```


---

## 作者：jianhe (赞：4)

### 前言：
卡精度的毒瘤题。不开 `long double` 见祖宗。

### 思路：
极角排序模板题。

[（极角排序是什么？）](https://blog.csdn.net/qq_44691917/article/details/105264091#:~:text=%E7%BB%99%E5%AE%9A%E6%9E%81%E8%BD%B4%EF%BC%8C%E5%9C%A8%E5%B9%B3%E9%9D%A2,%E5%B0%B1%E5%8F%AB%E5%81%9A%E6%9E%81%E8%A7%92%E6%8E%92%E5%BA%8F%E3%80%82)

首先我们要了解 $atan2$ 函数。返回值是弧度制（$- \pi$ 到 $\pi$），传入参数 $y,x$ 表示 $(x,y)$ 连到 $(0,0)$ 直线的夹角。（注意 $x,y$ 的顺序！）

由于返回值有负数，可以把所有负数加上 $2\times\pi$，方便排序。

于是极角排序完统计答案就好了。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double
const ll N=1e5+10;
const double pi=acos(-1);
ll n,ans1,ans2;
double ans;
struct P{
	double x,y,a;ll i;
	bool operator<(const P& b){return a<b.a;}
}p[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y,p[i].i=i,p[i].a=atan2(p[i].y,p[i].x),p[i].a+=(p[i].a<0?pi*2.:0.);
	sort(p+1,p+n+1);ans=p[1].a-p[n].a+pi*2.;ans1=p[1].i;ans2=p[n].i;
	for(int i=2;i<=n;i++) if(p[i].a-p[i-1].a<ans) ans=p[i].a-p[i-1].a,ans2=p[i].i,ans1=p[i-1].i;
	cout<<ans1<<" "<<ans2;
	return 0;
}
```

---

## 作者：hxhhxh (赞：4)

## 大意

给定 $ n $ 个点，表示 $ n $ 个向量（从原点到该点），求两个不同的向量，使夹角最小。

## 思路

有一个函数叫`atan`。用它可以直接算出一个向量和`x`轴正半轴的夹角（**弧度制**）。

分四个象限讨论再作减法就可以算出两个向量之间的夹角。

排序，对于每一个向量和它后面的向量相减，统计最小值即可。

$ \pi $ 是`acos(-1)`。

## 代码
```cpp
#include<bits/stdc++.h>
#define double long double
using namespace std;
int n,pos,s,l;
double ans,nw;
const double pi=acos(-1);
struct st{
    int x,y,id;
    double ang;
}a[100005];
bool cmp(st x,st y){
	return x.ang<y.ang;
}
double calc(st x){
    double xi=abs(x.x),yi=abs(x.y);
    if(x.x>=0&&x.y>=0) return atan(xi/yi)*180/pi;
    if(x.x>=0&&x.y<0) return atan(yi/xi)*180/pi+90;
    if(x.x<0&&x.y<0) return atan(xi/yi)*180/pi+180;
    if(x.x<0&&x.y>=0) return atan(yi/xi)*180/pi+270;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%d %d",&a[i].x,&a[i].y),a[i].id=i;
    for(int i=1;i<=n;i++) a[i].ang=calc(a[i]);
    sort(a+1,a+n+1,cmp);
    pos=n;
    ans=min(a[n].ang-a[1].ang,360-a[n].ang+a[1].ang);
    for(int i=1;i<=n-1;i++){
        nw=min(a[i+1].ang-a[i].ang,360-a[i+1].ang+a[i].ang);
        if(nw<ans){
            ans=nw;
            pos=i;
        }
    }
    printf("%d %d",a[pos].id,a[pos%n+1].id);
    return 0;
}
```

---

## 作者：Clever_Jimmy (赞：2)

CF598C 【Nearest vectors】

### 题意简述：

给定 $n$ 个向量的坐标表示 $(x, y)$，求任意两对向量的夹角的最小值所对应的那两个向量。

$1 \le n \le 10^5$，$\left|x \right|, \left|y\right| \le 10^4$，$x^2 + y^2 > 0$。

[题目链接](http://codeforces.com/problemset/problem/598/C)

### 解题思路：

首先考虑把所有的向量按照极角排序，但这也是有技巧的。

考虑把整个坐标系分为 $8$ 个部分：$4$ 个象限和 $4$ 个半坐标轴。

如果在同一个象限内，就很容易判断出极角的大小关系，否则就直接按照象限与象限之间的位置关系直接比较了。

注意 `std::atan2(a, b)` 的用法，它返回坐标表示为 $(b, a)$ 的向量的极角。

开 `long double` 枚举两个相邻的向量的极角差的大小即可。

### 参考代码：

```cpp
#include <bits/stdc++.h>
#define LL long long

const long double PI = 3.1415926535897932384626;
const int N = 1e5 + 5;

int n, ansx, ansy;
long double ans = 1e9;

int quad(int x, int y) {
	if(x > 0 && y > 0) return 1;
	else if(x == 0 && y > 0) return 2;
	else if(x < 0 && y > 0) return 3;
	else if(x < 0 && y == 0) return 4;
	else if(x < 0 && y < 0) return 5;
	else if(x == 0 && y < 0) return 6;
	else if(x > 0 && y < 0) return 7;
	else if(x > 0 && y == 0) return 8;
} // 得到这个向量在哪里

struct POINT {
	int id, x, y;
	long double deg;
	bool operator<(const POINT &rhs) const {
		int quad1 = quad(x, y), quad2 = quad(rhs.x, rhs.y);
		if(quad1 != quad2)
			return quad1 < quad2;
		else
			return y * rhs.x < x * rhs.y; // 通过分五类讨论得到的通式
	}
} p[N];

int32_t main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d %d", &p[i].x, &p[i].y);
		p[i].id = i;
		p[i].deg = std::atan2(1.0 * p[i].y, 1.0 * p[i].x);
		if(p[i].deg < 0)
			p[i].deg += 2 * PI;
	}
	std::sort(p + 1, p + n + 1);
	p[0] = p[n];
	for(int i = 1; i <= n; ++i) {
		long double cur_ans = p[i].deg - p[i - 1].deg;
		if(cur_ans < 0)
			cur_ans += 2 * PI;
		if(cur_ans < ans) {
			ans = cur_ans;
			ansx = p[i].id, ansy = p[i - 1].id;
		}
	}
	printf("%d %d", ansx, ansy);
    return 0;
}
```


---

## 作者：truly_handsome (赞：1)

毒瘤题，卡了我 1h。

题意：有 $n$ 个点，每个点表示原点到该点的向量，让你求出两个向量最小的夹角，输出向量的序号。

### 思路

很明显，按极角排个序之后选连续的两个向量即可。但是你会发现难度是 $2300$，很明显这题会卡精度。

为了切掉这题，我们可以用以下几个优化。

- 用 long double
- 手写 $\pi$
- 将 $\operatorname{atan2}$ 换成 $\operatorname{atan2l}$

这样就可以过了。

### Code

```cpp
# include <bits/stdc++.h>
# define pb push_back
# define int long long
# define db long double
# define pi 3.141592653589793238462643383279
using namespace std;

int n;

struct node{
	int x, y, idx;
} arr[100005], rans;

bool cmp(node a, node b){
	return atan2l(a.y, a.x) < atan2l(b.y, b.x);
}

db mn(db x, db y){
	return x < y ? x : y;
}

signed main(){
	scanf("%lld", &n); rans = (node){1, 2};
	for (int i = 1;i <= n;i++) scanf("%lld%lld", &arr[i].x, &arr[i].y), arr[i].idx = i;
	sort (arr+1, arr+n+1, cmp);
	db ans = 360.00000000; arr[n+1] = arr[1];
	for (int i = 1;i <= n;i++){
		db ang = atan2l(arr[i].y, arr[i].x) - atan2l(arr[i+1].y, arr[i+1].x);
		ang = mn(fabs(ang), mn(fabs(ang + 2.0*pi), fabs(ang - 2.0*pi)));
		if (ans > ang){
			ans = ang;
			rans = (node){arr[i].idx, arr[i+1].idx};
		}
	}
	printf("%lld %lld\n", rans.x, rans.y);
	return 0;
}

```


---

## 作者：Eltaos_xingyu (赞：1)

### 题目描述

有 $ n $ 个点，每个点表示原点到该点的向量，让你求出两个向量最小的夹角，输出向量的序号。

### 分析

很容易想到先给所有的向量排个序，然后每次枚举相邻的两个向量的夹角就行了。

所以，这就是一道极角排序板子题。

那么如何极角排序呢？

有一个函数 `atan2(x,y)`，它能返回 $ \frac{x}{y} $ 的反三角函数值。

所以这个函数这个函数返回的是点 $ (y,x) $ 的极角......好像有点问题，所以在计算极角时要逆序传参。

这里推荐把负极角转换成正极角，即对于负极角的值加上 $ 2 \pi $，这样在枚举时更好算。$ \pi $ 的值就是 `acos(-1)`。

排完序枚举相邻向量的极角差就行了，注意第一个和最后一个向量也是相邻的，也要枚举。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const long double Pi=acos(-1);
struct p{
	int x,y,id;
	long double dis;
	void init(){
		dis=atan2(y,x);
		if(dis<0)dis+=2*Pi;
	}
};
p d[100001];
int ans1,ans2;
long double cp=2*Pi;
bool cmp(p a,p b){
	return a.dis<b.dis;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>d[i].x>>d[i].y;
		d[i].id=i;
		d[i].init();
	}
	sort(d+1,d+n+1,cmp);
	ans1=d[1].id,ans2=d[n].id;
	cp=d[1].dis-d[n].dis+2*Pi;
	for(int i=1,j=i+1;i<n;i++,j++){
		if(d[j].dis-d[i].dis<cp)cp=d[j].dis-d[i].dis,ans1=d[i].id,ans2=d[j].id;
	}
	cout<<ans1<<" "<<ans2;
}
```


---

## 作者：Code_星云 (赞：1)

这题很自然地想到把向量按照一定顺序排序。在 ```cmath``` 库里面，有个 $\operatorname{atan2}$ 函数，其相对 $\operatorname{atan}$ 函数来说，优点在于可以处理与 $y$ 轴重合的角度情况。但需要注意的是，它的第一个参数是 $y$ 坐标，第二个是 $x$ 坐标。

需要注意的是，在普通情况处理完后，还需要处理一下排序后第一个向量和最后一个向量之间的特殊差角。此时如果仅仅是取两个 $\operatorname{atan2}$ 值的差的绝对值，其实是求的 $1$ 和 $n$ 号向量从 $- \pi$ 到 $\pi$ 方向的夹角，因此其特殊角的度数是用 $2 \times \pi$ 减去 $\operatorname{fabs}(d_1 - d_n)$。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<utility>
using namespace std;
typedef long double db;
#define x first
#define y second
const int N = 100005;
int n, pl1, pl2;
pair<db, int> p[N];
db minn = 2e9;
const db pi = acos(-1);
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		db x, y; cin >> x >> y;
		p[i] = make_pair(atan2(y, x), i);
		if(y == 0 && x > 0) p[i].x = 0;
		if(y == 0 && x < 0) p[i].x = pi;
	}
	sort(p + 1, p + n + 1);
	for(int i = 2; i <= n; i ++){
		if(fabs(p[i].x - p[i - 1].x) < minn){
			minn = fabs(p[i].x - p[i - 1].x);
			pl1 = p[i - 1].y;
			pl2 = p[i].y;
		}
	}
	if(2 * pi - fabs(p[1].x - p[n].x) <minn){
		minn = 2 * pi - fabs(p[1].x - p[n].x);
		pl1 = p[n].y;
		pl2 = p[1].y;
	}
	printf("%d %d\n", pl1, pl2);
	return 0;
}
```
话说这题评分真的有 2300 吗？码量加思维量都不大吧。

---

## 作者：MoonCake2011 (赞：0)

其实就是给你 $n$ 条从原点发出的射线，求哪两个射线间夹角最小。

首先我们使用 `atan2l(y,x)` 函数计算出原点到 $(x,y)$ 的射线与 $x$ 轴正方向的这条射线的夹角（可能大于一百八十度）。

这里返回的是弧度，可以直接加减法算角度。

然后对这 $n$ 条射线与 $x$ 轴正方向的夹角排序。

然后相邻两个差最小的角就是答案。

注意还要特判一下排序后第 $n$ 条与第 $1$ 条射线之间的夹角，因为它们也相邻。

[AC 记录](https://mirror.codeforces.com/problemset/submission/598/328867811)。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double//注意用 long double
const double PI=3.141592653589793238462643383279502884197169399375105;//2*PI 就相当于 360 度
//这里上网抄的 PI，但也可以使用 acosl(-1) 直接计算，这里主要是怕精度 
int n;
int x[100010],y[100010],id[100010];
double p[100010];
inline bool cmp(int x,int y){
	return p[x]<p[y];
} 
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i],p[i]=atan2l(y[i],x[i]),id[i]=i;
	sort(id+1,id+n+1,cmp);
	int minn=1;
	for(int i=2;i<n;i++) if(p[id[minn+1]]-p[id[minn]]>p[id[i+1]]-p[id[i]]) minn=i;
	if(p[id[1]]-p[id[n]]+2*PI<p[id[minn+1]]-p[id[minn]]) cout<<id[1]<<" "<<id[n];//特判 
	else cout<<id[minn]<<" "<<id[minn+1];
	return 0;
}
```

---

## 作者：Vitamin_B (赞：0)

祝大家春节快乐！
# 思路
其实我们可以把这个平面看成一个圆，此时显然我们只能取任意**相邻的**两条边之间的夹角。注意因为是平面，所以头尾间的夹角也要考虑。

这题的难点在于如何计算夹角。但是好在 c++ 提供了一个很好用的函数：`atan2`。`atan2(y,x)` 可以自动求出坐标位于 $(x,y)$ 的点与原点的夹角。这个函数它会返回弧度，不过不妨碍做题。记得在**传参前**强制转化参数为 `long double`，否则返回值将只有 `double`！

至于 $\pi$ 怎么求，那你可以自己背出精度极高的 $\pi$（前提条件别被错），也可以使用 c++ 自带的 `acos(-1)`。

[Code](https://codeforces.com/contest/598/submission/303413208)。

---

## 作者：UKBwyx (赞：0)

这篇题解提供一个**不需要 stl 三角函数**的做法（也不是手写三角函数，但还是要用到三角函数的知识）。

~~当然如果你不会三角函数只会线性代数也可以~~。

前置知识：  
向量的模长。  
内积。  
甚至还有牛顿迭代法。

首先考虑我们只要关注向量的夹角，也就是**向量的方向**，而**不需要关注它的长度**，于是我们可以把它全部弄成长度为 $1$ 的单位向量。

这样我们把它按角度排序时只需要关注它的象限，如果两个向量在同一个象限里就**只关注它的 $y$ 坐标**就行了。

具体来说是这样的：

当向量都在第一象限的时候按 $y$ 坐标从小到大排序。
![](https://cdn.luogu.com.cn/upload/image_hosting/fxskut8f.png)
当向量都在第二象限的时候按 $y$ 坐标从小到大排序。
![](https://cdn.luogu.com.cn/upload/image_hosting/8fgqw42o.png)
当向量都在第三象限的时候按 $y$ 坐标从小到大排序。
![](https://cdn.luogu.com.cn/upload/image_hosting/too1i5ut.png)
当向量都在第四象限的时候按 $y$ 坐标从小到大排序。
![](https://cdn.luogu.com.cn/upload/image_hosting/c3ef0a4i.png)
然后就是比较夹角，这个事实上也是不难的。

因为我们的向量都是单位向量，所以所以向量的长度都是一样的。

用我们高中学过的内积知识易知，设有两个二维向量 $a=[a_1,a_2]$ 和 $b=[b_1,b_2]$，那当 $a$ 与 $b$ 的夹角越小时 $\frac{a_1b_1+a_2b_2}{|a||b|}$ 就越大。

由于向量的长度都是一样的，所以我们直接选取内积最大的两个向量就是答案。

但是还是有问题，通常来说，如果用 sqrtl 的话会在第 $100$ 个 WA 掉，原因是被卡精度了，所以我们再手写一个牛顿迭代法就行了。

这里贴上代码。
```cpp
#include<bits/stdc++.h>
#define pii pair<long long,long long>
#define mp make_pair
#define pb push_back
using namespace std;
__float128 lim=1,cs;
__float128 f(__float128 d) {//牛顿迭代法
	__float128 wz=sqrtl(d);
	d=-d;
	while(1) {
		__float128 v=wz*wz+d;
		if(-lim<=v&&v<=lim) {
			return wz;
		}
		__float128 del=2*wz;
		wz-=v/del;
	}
	return wz;
}
struct ab {
	__float128 x,y;
	long long bh;
};
ab a[100005];
long long n;
int f(ab x) {//返回的是象限
	if(x.x>=0&&x.y>=0)return 1;
	if(x.x<=0&&x.y>=0)return 2;
	if(x.x<=0&&x.y<=0)return 3;
	if(x.x>=0&&x.y<=0)return 4;
}
bool cmp(ab x,ab y) {//按角度排序
	if(f(x)!=f(y)) {
		return f(x)<f(y);
	} else {
		long long t=f(x);
		switch(t) {
		case 1: {
			return x.y<y.y;
		}
		case 2: {
			return x.y>y.y;
		}
		case 3: {
			return x.y>y.y;
		}
		case 4: {
			return x.y<y.y;
		}
		}
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(int i=1; i<=20; i++) {//牛顿迭代的精度到 10^-20
		lim/=10;
	}
	cin>>n;
	for(int i=1; i<=n; i++) {
		long long t1,t2;
		cin>>t1>>t2;
		a[i].x=t1;
		a[i].y=t2;
		__float128 bl=f(a[i].x*a[i].x+a[i].y*a[i].y);//向量的长度
		a[i].x/=bl,a[i].y/=bl;//除成单位向量
		a[i].bh=i;
	}
	sort(a+1,a+n+1,cmp);
	pair<__float128,pii> ans=mp(-1,mp(0,0));
	a[n+1]=a[1];//最后一个和第一个比较
	for(int i=1; i<=n; i++) {
		ans=max(ans,mp(a[i].x*a[i+1].x+a[i].y*a[i+1].y,mp(a[i].bh,a[i+1].bh)));//内积
	}
	cout<<ans.second.first<<" "<<ans.second.second;
	return 0;
}
```

---

## 作者：cold_cold (赞：0)

[安利一波博客](https://www.cnblogs.com/cold-cold/p/10041583.html)

**题目描述**
：有n个点,每个点表示原点到该点的向量,让你求出两个向量最小的夹角,输出向量的序号

 

此题其实不难，只需把每个向量与x轴的非负半轴的逆时针角度求出来，排序后，相邻的角度相减，取最小值即可。

但是难在atan我并没有接触过，atan2是一个函数，返回的是指方位角（弧度制），计算时atan2 比 atan 稳定。

返回的值取值范围为  ，所以我们在得到的值小于0时要加上2π

另外要注意的是，函数atan2(y,x)中参数的顺序是倒置的，atan2(y,x)计算的值相当于点(x,y)的角度值。

实现如下：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
inline int read()
{
    register int p(1),a(0);register char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
const int N=100100;
const long double pai=atan2(0.0,-1.0);
int n,jl;
struct node
{
	int xu;
	long double x,y,du;
	bool operator < (const node &xx)const{return du<xx.du;}
}a[N];
long double maxn=9999999.0;
int main()
{
//	freopen("input","r",stdin);
//	freopen("output","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i].xu=i;
		a[i].x=read(),a[i].y=read();
		a[i].du=atan2(a[i].y,a[i].x);
		if(a[i].du<0.0) a[i].du=a[i].du+pai+pai;
	}
	sort(a+1,a+1+n);
	for(int i=2;i<=n;i++)
		if(maxn>min(a[i].du-a[i-1].du,pai+pai-a[i].du+a[i-1].du))
		{
			maxn=min(a[i].du-a[i-1].du,pai+pai-a[i].du+a[i-1].du);
			jl=i;
		}
	if(maxn>min(a[n].du-a[1].du,pai+pai-a[n].du+a[1].du)) jl=1;
	printf("%d %d\n",a[jl].xu,jl-1==0?a[n].xu:a[jl-1].xu);
    return 0;
}


```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF598C](https://www.luogu.com.cn/problem/CF598C)

* **【解题思路】**

其实，这题非常水（蓝是水的颜色）。

思路：

* 把所有向量按照幅角排序。

* 枚举所有相邻向量的幅角差，如果小于当前答案的幅角差就更新答案。

计算幅角，很多人用```atan2```。（```atan```无法区分大于 $180^\circ$ 与小于 $180^\circ$ 的角。）但是，因为```atan2```传参是按先 $\sin$ 后 $\cos$ （先 $y$ 后 $x$）的顺序，就容易把两个参数搞反。

这时，我们可以用```complex```。有一个全局函数叫```arg```，接受一个```complex```并返回它的幅角。（不用担心把参数弄反啦！）

然后我们开心地写出了代码（以下为主要部分）：

```cpp
......

array<pair<complex<long double>,int>,100000> vectors;
	......
	sort(vectors.begin(),vectors.begin()+cntvec,[](pair<complex<long double>,int> vec_a,decltype(vec_a) vec_b){return arg(vec_a.first)<arg(vec_b.first);});
	long double min_poldif=4*acos(-1);
	int index_1,index_2;
	for(int i=0;i<cntvec-1;i++)
		if(arg(vectors[i+1].first)-arg(vectors[i].first)<min_poldif)
			index_1=vectors[i+1].second,index_2=vectors[i].second,min_poldif=arg(vectors[i+1].first)-arg(vectors[i].first);
	......
``````

然后交上去。$\text{\color{red}WA}$？

考虑下面的样例：

```
Input:
3
-1000000 1
-1000000 -1
1 1
Output:
1 2
```

但是我们输出了```1 3```。原因是因为，由于隔了一个正负分界线（$\theta=\pi$）,导致程序计算出的幅角差接近 $2\pi$，但是实际上它们的幅角差应该接近 $0$。所以，我们要把第一个元素与最后一个元素算一遍幅角差。这一次我们应该把第一个元素的幅角加上 $2\pi$，才能计算出正确的幅角差。

所以要加上：

```cpp
if(arg(vectors[0].first)+2*acos(-1)-arg(vectors[cntvec-1].first)<min_poldif)
	index_1=vectors[cntvec-1].second,index_2=vectors[0].second;
```

* **【实现细节】**

实际上，如果你真交上去上面的程序：$\color{goldenrod}\text{CTLE}$！？

原来，用```pair```开大数组会导致类似于编译文件过大导致编译时间过长。

于是我们只好手写一个结构体：

```cpp
struct pair_cust
{
	complex<long double> first;
	int second;
};
```

* **【代码实现】**

```cpp
#include <algorithm>
#include <iostream>
#include <complex>
#include <array>
#include <cmath>

using namespace std;

struct pair_cust
{
	complex<long double> first;
	int second;
	pair_cust()=default;
};

array<pair_cust,100000> vectors;

int main(int argc,char *argv[],char *envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cntvec;
	long double real_t,imag_t;
	cin>>cntvec;
	for(int i=0;i<cntvec;i++)
		cin>>real_t>>imag_t,vectors[i].first.real(real_t),vectors[i].first.imag(imag_t),vectors[i].second=i;
	sort(vectors.begin(),vectors.begin()+cntvec,[](pair_cust vec_a,decltype(vec_a) vec_b){return arg(vec_a.first)<arg(vec_b.first);});
	long double min_poldif=4*acos(-1);
	int index_1,index_2;
	for(int i=0;i<cntvec-1;i++)
		if(arg(vectors[i+1].first)-arg(vectors[i].first)<min_poldif)
			index_1=vectors[i+1].second,index_2=vectors[i].second,min_poldif=arg(vectors[i+1].first)-arg(vectors[i].first);
	if(arg(vectors[0].first)+2*acos(-1)-arg(vectors[cntvec-1].first)<min_poldif)
		index_1=vectors[cntvec-1].second,index_2=vectors[0].second;
	cout<<index_1+1<<' '<<index_2+1;
 	return 0;
}
```

---

