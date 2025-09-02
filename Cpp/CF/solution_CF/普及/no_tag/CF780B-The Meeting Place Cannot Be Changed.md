# The Meeting Place Cannot Be Changed

## 题目描述

The main road in Bytecity is a straight line from south to north. Conveniently, there are coordinates measured in meters from the southernmost building in north direction.

At some points on the road there are $ n $ friends, and $ i $ -th of them is standing at the point $ x_{i} $ meters and can move with any speed no greater than $ v_{i} $ meters per second in any of the two directions along the road: south or north.

You are to compute the minimum time needed to gather all the $ n $ friends at some point on the road. Note that the point they meet at doesn't need to have integer coordinate.

## 说明/提示

In the first sample, all friends can gather at the point $ 5 $ within $ 2 $ seconds. In order to achieve this, the first friend should go south all the time at his maximum speed, while the second and the third friends should go north at their maximum speeds.

## 样例 #1

### 输入

```
3
7 1 3
1 2 1
```

### 输出

```
2.000000000000
```

## 样例 #2

### 输入

```
4
5 10 3 2
2 3 2 4
```

### 输出

```
1.400000000000
```

# 题解

## 作者：Rty123 (赞：3)

2023 csp 考前写题解 rp++


这道题一眼丁真为**二分**，二分就是把一个最优解问题转化成判定性问题，并且要满足单调性。

对于这道题，我们可以二分时间，时间是满足单调性的，假如你在一个特定时间点可以聚集所有人，比这个时间点用时长的便肯定可以聚集所有人，反之则肯定不行。

然而判断对于一个时间能否让所有人到达同一点，只要记录一下往左跑跑到的最小的点和往右跑跑到的最大的点，看是否有交集即可。

接下来看代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double x[60005],v[60005];
double l,r;
bool rty(double u){
	double maxx=0,minn=1e9;
	for(int i=1;i<=n;i++){
		maxx=max(maxx,x[i]-v[i]*1.0*u);//往右跑，跑到的最大的点
		minn=min(minn,x[i]+v[i]*1.0*u);//往左跑，跑到的最小的点
	}
	return maxx<=minn;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i];
		r=max(r,x[i]);
	}
	for(int i=1;i<=n;i++){
		cin>>v[i];
	}
	while((r-l)>0.000001){//小数二分模板（注意精度）
		double mid=(l+r)/2.0;
		if(rty(mid)){
			r=mid;
		}
		else l=mid;
	}
	printf("%.12lf",l);
	return 0;
}
```


---

## 作者：Numenor (赞：2)

蒟蒻的第一篇题解，，，
~~为了蹭积分嘛~~

二分枚举时间
	
```#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
  
const int inf=0x3f3f3f3f3f;

double fri[60005];

double v[600005];

int n;

double l,r;

bool f(double time)

{

	double lmin=inf,rmax=-inf;
    
	for(int i=1;i<=n;i++)
    
	{
		lmin=min(lmin,fri[i]+v[i]*time);//往左跑，找到能跑到的最小的点 
		rmax=max(rmax,fri[i]-v[i]*time);//往右跑，找到能跑到的最的的点
		                                //（也即能跑的长度最短的点） 
	}
	if(lmin>=rmax)return 1;//如果向能跑到的最小的点，能与向右能跑的距离最短的点相遇
	                       //那么就有交集，满足要求 
	else return 0;
    }
int main()
{

	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf",&fri[i]);
		r=max(r,fri[i]);//蒟蒻写法吧，，，因为是int数据嘛。最长时间不会超过最右边的点*1吧 
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lf",&v[i]);
	}
	double mid;
	while((r-l)>0.000001)//二分模板 
	{
		mid=(l+r)/2;
		if(!f(mid))
		{
			l=mid;
		}
		else
		{
			r=mid;
		}
	}
	printf("%.12lf",l);		
}
	

---

## 作者：Stars_Traveller (赞：1)

## CF780B The Meeting Place Cannot Be Changed 题解
### 分析
二分板子。

首先确定二分对象。在本题中要求汇合的最小时间，发现如果 $x$ 这个汇合时间可行，那么比 $x$ 大的汇合时间肯定也可以。

设最小汇合时间为 $m$，那么 向左移动的人抵达的位置为 $x_i-v_i \times m$，向右移动的人抵达的位置为 $x_i+v_i \times m$。

若向左移动到达的最大的点和向右移动到达的最小的点有交集，也就是向左移动到达的最大的点的位置小于或等于向右移动到达的最小的点，则当前枚举到的汇合时间为答案。

### 代码
```cpp
#include<iostream>
#include<cmath>
#include<bits/stdc++.h>
using namespace std;
const int no_final_exam=6e4+5;
int n;long double x[no_final_exam], v[no_final_exam];
bool qimokaoshinibuyaoguolai(long double wo_bu_yao_kao_qi_mo_kao_shi_aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa){long double wanla=0, rev=34579843758934.0;for(int i=1;i<=n;i++)wanla=max(wanla,x[i]-v[i]*wo_bu_yao_kao_qi_mo_kao_shi_aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa),rev=min(rev,x[i]+v[i]*wo_bu_yao_kao_qi_mo_kao_shi_aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa);return wanla<=rev;}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x[i];for(int i=1;i<=n;i++)cin>>v[i];
	long double lt=0, rt=34579843758934.0;
	while(rt-lt>1e-8){long double mid=(lt+rt)/2.0;if(qimokaoshinibuyaoguolai(mid))rt=mid;else lt=mid;}
	cout<<fixed<<setprecision(14)<<rt;
	return 0;
}

---

## 作者：Stars_visitor_tyw (赞：1)

## 题解：CF780B The Meeting Place Cannot Be Changed
### 分析
好像就是二分板子。

二分汇合时间，然后考虑极限情况，也就是他们向左走走到的最大的点是否在向右走能走到的最小的点的左边。如果上述情况属实，则这个汇合时间即为答案。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int n;
double X[114514], v[114514];
const double eps=1e-7;
bool check(double x)
{
	double lft=0, rft=1145140000.0;
	for(int i=1;i<=n;i++)
	{
		lft=max(lft,X[i]-v[i]*x);
		rft=min(rft,X[i]+v[i]*x);
	}
	return rft>=lft;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=2*n;i++)
	{
		if(i<=n)
		{
			cin>>X[i];
		}
		else
		{ 
			cin>>v[i-n];
		}
	}
	double lt=0, rt=1145140000.0;
	while(rt-lt>eps)
	{
		double mid=(lt+rt)/2;
		if(check(mid))rt=mid;
		else lt=mid;
	}
	cout<<fixed<<setprecision(12)<<rt;
}

---

## 作者：Loser_Syx (赞：1)

随着时间的推移，每个人最多走的距离肯定是逐渐变长的，此时数轴上每个人可以到达的距离的交集一定是慢慢变大的，所以当时间越大交点越多，满足单调性可以二分。

考虑二分时的 $mid$，我们需要所有人当中到达的往左走 $mid$ 步的最大值 $l$ 和往右走 $mid$ 步的最小值 $r$，这两个是最坏情况，一个是最右边一个是最左边，如果他们不能相遇的话，别人肯定就不能相遇；如果他们能够相遇的话，那么别人一定是可以在 $[l,r]$ 中找到一个点相遇。

复杂度 $O(n \log n)$。

```cpp
#include <iostream>
using namespace std;
int a[1001011], n, b[1001011];
inline bool check(long double qwq){
	long double l = -1e18, r = 1e18;
	for(int i = 1; i <= n; ++i){
		l = max(l, a[i] - 1LL * b[i] * qwq);
		r = min(r, a[i] + 1LL * b[i] * qwq);
	}
	return l <= r;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n; ++i){
		scanf("%d", &b[i]);
	}
	double l = 0, r = 1e9, eps = 1e-7;
	while(l+eps <= r){
		double mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid+eps;
	}
	printf("%.15lf", r);
	return 0;
}
```

---

## 作者：ATION001 (赞：0)

## 题目描述
一条无限长的直线上有 $n$ 个点，第 $i$ 个点初始时在位置 $x_i$，每个节点每秒可以向左或向右移动 $y_i$ 单位的距离。请求出使所有点都在同一位置最少需要多少秒。
## 思路
一道二分好题。

**给大家提个醒：一定要注意计算精度问题！！！否则会听取 WA 声一片。**

可以计算出在 $x$ 秒内（$x$ 为二分结果）每一个节点能走到的范围。如果能够到达同一个位置，那么区间直接肯定有重合的范围。

所以判定函数只需要判断区间左端点的最大值是否大于等于区间右端点的最小值，如果满足该条件，说明当前秒数下能够到达同一个位置。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=60010;
int n;
double a[N],b[N];
bool code(double x){
	double maxn=0,minn=1e9+7;
	for(int i=1;i<=n;i++){
		maxn=max(maxn,a[i]-b[i]*1.0*x);
		minn=min(minn,a[i]+b[i]*1.0*x);
	}
	return maxn<=minn;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	double l,r,mid;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		r=max(a[i],r);
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	while((r-l)>=1e-7){
		mid=(l+r)/2.0;
		if(code(mid)){
			r=mid;
		}
		else{
			l=mid+1e-7;
		}
	}
	cout<<fixed<<setprecision(6)<<l<<endl;
	return 0;
}
```

---

## 作者：Frank2010 (赞：0)

# [CodeForces CF780B](https://www.luogu.com.cn/problem/CF780B)

**update 2024.7.23**：修改了炸掉的代码块，并删减了一些无关的文字。

## 题意简述

在一条直线上有 $n$ 个小朋友，每个小朋友都有一个坐标 $X_{i}$ 和一个最大速度 $V_{i}$，求**最少**需要多少时间在一个位置上回合。**注意最后的汇合点不一定是整数点。**

## 解题思路

### 二分

看到那个“最少”了吗？简直一眼**二分**。

二分代码：

```cpp
double l=1e-7,r=1e9;
while(r-l>1e-7){ //误差不超过1e-7就行了
    double mid=(l+r)/2; //记得开 double
    if(check(mid))r=mid-1e-7;
    else l=mid+1e-7;
}
```

注意：一定不能跟平常一样，直接 $l=1$ ，否则直接听取 WA 声一片：

![WA 声一片](https://cdn.luogu.com.cn/upload/image_hosting/8c7pzdrg.png)

（这也是本蒟蒻为什么加粗“注意最后的汇合点不一定是整数点”的原因。）

### 模拟和差分

模拟和差分，即在 `check()` 函数里面。

这时有人会说为什么要用模拟？当然是看到题解里没有一篇是模拟的，所以前来贡献一篇。

模拟每个小朋友能跑向的最左端和最右端。

再往右就跑不到了，所以设为 $-1$。

还有就是不能直接 $x_{i}+v_{i}m+1$，

因为 $1$ 跨度太大了。

差分和模拟代码：

```cpp
struct node{
    double x;
    int w;
};
vector<node>nodes;
bool cmp(node a,node b){
    return a.x<b.x;
}
bool check(double m){
    nodes.clear();//初始化
    for(int i=1;i<=n;i++){
        nodes.push_back({x[i]-v[i]*m,1});
        nodes.push_back({x[i]+v[i]*m+1e-20,-1});
    }
    //模拟
    sort(nodes.begin(),nodes.end(),cmp);//对每个端点进行排序
    int t=0;
    for(node i:nodes){
        t+=i.w;
        if(t==n)return true;//如果这个区间满足条件就直接返回 true
    }
    return false;//如果没有一个区间满足条件就返回 false
    //差分
}
```

### 输出

建议用如下代码输出：

```cpp
cout<<fixed<<setprecision(12)<<l<<endl;
```

## AC 代码

```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<vector>
using namespace std;
const int N=60005;
int n;
double x[N],v[N];
struct node{
    double x;
    int w;
};
vector<node>nodes;
bool cmp(node a,node b){
    return a.x<b.x;
}
bool check(double m){
    nodes.clear();//初始化
    for(int i=1;i<=n;i++){
        nodes.push_back({x[i]-v[i]*m,1});
        nodes.push_back({x[i]+v[i]*m+1e-20,-1});
    }
    //模拟
    sort(nodes.begin(),nodes.end(),cmp);//对每个端点进行排序
    int t=0;
    for(node i:nodes){
        t+=i.w;
        if(t==n)return true;//如果这个区间满足条件就直接返回 true
    }
    return false;//如果没有一个区间满足条件就返回 false
    //差分
};
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lf",&x[i]);
    for(int i=1;i<=n;i++)scanf("%lf",&v[i]);
    double l=1e-7,r=1e9;
    while(r-l>1e-7){
        double mid=(l+r)/2;
        if(check(mid))r=mid-1e-7;
        else l=mid+1e-7;
    }
    //二分
    cout<<fixed<<setprecision(12)<<l<<endl;//注意输出
    return 0;
}
```

---

## 作者：hanciyang (赞：0)

这道题一看就是 **二分** 板子题。

当然由于精度原因，最好由原来的二分模板转换成这个。

```cpp
while ((w - t) > 0.000001) {
		mid = (t + w) / 2.0 ;
		if (check (mid))  w = mid ;
		else  t = mid ;
	}
```

至于 `check` 函数，十分简单。二分出的时间 $t$，先计算每个人能够到达的区间 $[x_i-tv_i \ ,\ x+tv_i]$，再判断是否有公共交集。

判断公共交集更简单，算出最小区间 $mi$ 和最大区间 $ma$，如果最大交集 $ma$ **小于等于**最小交集 $mi$，则成立。

放出代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std ;
int n ;
double a [60010] , b [60010] , mid , t , w , bao ;
bool check (double x) {
	double ma = 0 , mi = 2e9 ;
	for (int i = 1 ; i <= n ; i ++) {
		mi = min (mi , a [i] + b [i] * x) ;
		ma = max (ma , a [i] - b [i] * x) ;
	}
	return ma <= mi ;
	return 0 ;
}
main () {
	ios::sync_with_stdio (false) ;
	cin.tie (NULL) ; cout.tie (NULL) ;
	cin >> n ;
	for (int i = 1 ; i <= n ; i ++)  
		cin >> a [i] , w = max (w , a [i]) ;
	for (int i = 1 ; i <= n ; i ++)  cin >> b [i] ;
	t = 0 ; 
	while ((w - t) > 0.000001) {
		mid = (t + w) / 2.0 ;
		if (check (mid))  w = mid ;
		else  t = mid ;
	}
	printf ("%.12lf" , t) ;
	return 0 ;
}
```

**注意：由于精度原因，样例数据会差大概 $\pm 0.1$ 左右，这样子也算对的。**

---

## 作者：wwxxbb (赞：0)

## 分析

这题其实就是在求带权中位数。我们二分时间，因为时间肯定是满足单调性的，假设一个时间满足题意，那比这个时间长肯定也满足，反之则可能不满足。

对于 `check` 函数，我们要判断在这个时间里所有人是否可以在同一个位置汇合，只需要看一下他们向左跑到的最大的点和向右跑到最小的点是否有交集即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using db = double;
const int N = 60010;

int n;
db a[N], b[N];

bool check(db x) {
    db mx = 0, mn = 2e9;
    for (int i = 1; i <= n; i ++) { // 题解好多都左右搞反
        mx = max(mx, a[i] - b[i] * x); // 向左是减
        mn = min(mn, a[i] + b[i] * x); // 向右是加
    }
    return mx <= mn;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    db mx = 0;
    for (int i = 1; i <= n; i ++) cin >> a[i], mx = max(mx, a[i]);
    for (int i = 1; i <= n; i ++) cin >> b[i];
    db l = 0, r = mx;
    while (r - l > 1e-6) {
        db mid = (l + r) / 2.0;
        if (check(mid)) r = mid;
        else l = mid;
    }
    return cout << fixed << setprecision(12) << l, 0;
}
```

### 题外话

这题也有数学方法，发现这是一个分段函数，所以求导一下应该也能做。~~但我懒~~

---

## 作者：MWL_wma (赞：0)

本题要求每个人在一定时间内到达同一个点，显然这个时间越长月容易满足要求。

因此，**答案具有单调性**。

考虑二分答案。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double l,r=1e9+1;
const double one=1;
struct dot{
	double x,v;
}a[60002];
bool pd(double t){
	double mn=0,mx=1e9+1;
	for(int i=1;i<=n;i++){
		mn=max(mn,a[i].x-1.0*a[i].v*t);
		mx=min(mx,a[i].x+1.0*a[i].v*t);
	}
	return mn<=mx;
}
void data(){
	while(r-l>0.000001){
		double mid=(l+r)/2;
		if(pd(mid)){
			r=mid;
		}else{
			l=mid;
		}
	}
	return ;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf",&a[i].x);
	}
	for(int i=1;i<=n;i++){
		scanf("%lf",&a[i].v);
	}
	data();
	printf("%.12lf",r);
	return 0;
}

```

---

## 作者：TangyixiaoQAQ (赞：0)

# 思路
注意到每个人的速度不同，无法直接枚举地点，所以本题考虑 **二分答案** 枚举时间。

假设某个人所花费的时间为 $t$，那么那个人在 $t$ 秒内可以移动的范围为 $(x_i-v_i*t\hspace {0.1cm},\hspace {0.1cm}x_i+v_i*t)$ ，这样就转化成了一个求区间交的问题。

求所有区间交的方式为：取左端点的最大值、右端点的最小值，求该区间是否为空。

若取交时二者为同一个点，那么也是可行的。

## 关键代码

```cpp
while (r - l > eps) {
    mid = (l + r) / 2;
    L = x[1] - v[1] * mid;
    R = x[1] + v[1] * mid;
    for (int i = 2; i <= n; ++i) {
        L = max(L, x[i] - v[i] * mid);
        R = min(R, x[i] + v[i] * mid);
    }
    if (L <= R)
        r = mid;
    else
        l = mid;
}
```

---

## 作者：天亮codekiller (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF780B)

## 思路：

使用二分答案，二分所需的时间，每次计算出每个人所能到达的最远范围，在这些范围中取交集，如果范围存在就可以，二分直到误差满足要求即可。

## 上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[60005],v[60005];
const double eps=1e-10;//精度要求 
double t,l,r;
double klft,krgt;
bool flag;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&x[i]);
	for(int i=1;i<=n;++i)scanf("%d",&v[i]);
	l=0,r=1e9+5;//二分的左右端点 
	while(r-l>=eps){
		t=(l+r)/2;
		klft=-1e26,krgt=1e26;
		flag=true;
		for(int i=1;i<=n&&flag;++i){
			klft=max(klft,x[i]-v[i]*t);//用取左端点的最右值来实现区间取交集 
			krgt=min(krgt,x[i]+v[i]*t);//用取右端点的最左值来实现区间取交集 
			if(krgt-klft<=eps)flag=false;//如果左端点的最右值大于右端点的最左值，就不可行 
		}
		if(flag)r=t;
		else l=t;
	}
	printf("%.10f",t);//按精度要求输出答案即可 
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### 题目分析：

如果在一个特定时间能到，那么在这个时间往后也一定能到，这样的话就可以用二分来做了。

具体的，每一次二分秒数，然后判断这些人能否到达同一个位置，换言之，就是说这些人能到达的区间是否有交集。

应对这一类区间交集有一个好用的方法，在所有的左端点中去一个最靠右的的值，同时在所有的右端点中取一个最靠左的值比较两者大小就行了。

如果最靠右的左端点在最靠左的右端点的左边，那么就说明这样的一堆段区间在最靠右的左端点和最靠左的右端点之间有交集。反之则说明没有交集。

这道题不可以用解方程的方法做，原因是每一个点的移动方向不确定。

-------
注意别把二分的极限值定的太小，题目只要六位的精度就行了。

--------
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int x[60005],v[60005],n;
double l,r,mid;
bool check(double mid){
	double ll=-2147483647,rr=2147483647;
	for(int i=1;i<=n;i++){
		ll=max(ll,x[i]-v[i]*mid);
		rr=min(rr,x[i]+v[i]*mid);
	}
	if(ll<=rr)return 1;
	return 0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&x[i]),r=max(r,(double)x[i]);
	for(int i=1;i<=n;i++)scanf("%d",&v[i]);
	while(l+0.0000001<r){
		mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid;
	}
	printf("%.7f",l);
	return 0;
}
```


---

## 作者：chala_tea (赞：0)

因为答案具有单调性，因此可以用**二分答案**解决此题。

$check()$ 函数只需要观察最小的右端点 是否小于等于 最大的左端点即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 114514
#define int long long

int n;
double x[MAXN],v[MAXN];

bool check(double t){
	double minr=1e9,maxl=0;
	for(int i=1;i<=n;i++){
		minr=min(minr,x[i]+t*v[i]*1.0);
		maxl=max(maxl,x[i]-t*v[i]*1.0);
	}
	if(minr>=maxl)return true;
	else return false;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x[i];
	for(int i=1;i<=n;i++)cin>>v[i];
	
	double l=0,r=1e9,ans=0;
	while(abs(l-r)>0.000001){
		double mid=(l+r)/2.0;
		if(check(mid)){
			ans=mid,r=mid-0.000001;
		}else{
			l=mid+0.000001;
		}
	}
	printf("%.12lf",ans);
	return 0;
}

```

---

## 作者：CrazyWisdom (赞：0)

## 附言
题目名称：[The Meeting Place Cannot Be Changed](https://www.luogu.com.cn/problem/CF780B)

在另外一个课集训时候做的，老师还讲了，那就交一发题解吧。
## 二分
这是一道二分题（判断算法这件事看感觉，~~但有个技巧就是看数据范围~~）。

二分的特点是：处理单调序列；能够把求最优解的问题转换为判断性问题。

知道是二分了，怎么二分？
## 思路

一条数轴上有很多人，第一感觉是枚举点。

但是点好像没有什么可以二分的，硬来枚举复杂度只能变成一个标准的二次函数，当然，还是因为点不具备单调之类的特殊性质，尤其在出发点不可控的情况下。

那么就可以从另外一个要素：时间，来考虑。

众所周知，人们可以行走到的区域是随着时间的增加和变广的。

事实上，如果有一个有一个点使得所有人都可以走到，即说明这个点是合法的开会地点。因此大体的思路是：二分遍历行走的时间，然后在这种时间下寻找一个所有人都可以到达的点，没有就增加时间，有就减少然后继续找。

但是如何快速的寻找这个点是一个问题，如果用普通循环先遍历，再记录，再搜索，时空复杂度明显大了些。

因此考虑一种优化算法。容易理解，所有人都可以向左行走一定的距离，也可以向右行走相同的距离。在两个方向中，总有人到达的地方较近（注意，是位置不是距离，也就是说有可能一个行走速度快但是位置遥远的人他到达的距离并没有一个很慢的人远）。注意，向左走的时候落点越小越远，向右走的时候越大越远。显而易见，落点越远，覆盖的距离越大，同时比它近的落点它都能覆盖到。（好好理解）

那么如果左右落点最近的两个人他们的可以达到的范围都有交点，那落点远的必然也有焦点，这样问题就解决了。而且这种方法时间复杂度也相对比较小。思路完，代码实现。

看看其他三位大佬的思路和我差不多，我也想不出更好的方法，也就在细枝末节上优化优化吧。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int N, x[60005], y[60005];
bool check(double t) {
	double lmin, rmin;
	rmin=2147483645; 
	lmin=-2147483645;
	for(int i=1;i<=N;i++) {
		lmin=max(lmin,x[i]-y[i]*t);//关键思路; 
		rmin=min(rmin,x[i]+y[i]*t); 
	}
	return (lmin<=rmin);
}
int main () {
	double l=0, r=0;
	scanf("%d", &N);
	for(int i=1;i<=N;i++) {
		scanf("%d", &x[i]);
		r=max(r,(double)x[i]);//max貌似只能处理同一个类型的变量 
	}
	for(int i=1;i<=N;i++) {
		scanf("%d", &y[i]);
	}
	double mid, t, cnt=0;
	while(++cnt<=70) {//此处是处优化，由于小数极有可能产生精度问题，所以采用这种提前限制范围的方法比较好。此处是经过计算了的。 
		mid=(l+r)/2.0;//板子 
		if(check(mid)) {
			r=mid;
		} else {
			l=mid;
		}
	}
	printf("%.12lf", l);//看清楚位数！细节决定成败 
	return 0;
} 
```


---

