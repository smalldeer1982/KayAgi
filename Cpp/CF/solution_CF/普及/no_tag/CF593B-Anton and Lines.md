# Anton and Lines

## 题目描述

给定 $n$ 条形如 $y=k_ix+b_i$ 的直线，你需要判断是否存在两条直线 $a,b$，使 $a,b$ 的交点 $(x_0,y_0)$ 满足 $x_1<x_0<x_2$。

## 样例 #1

### 输入

```
4
1 2
1 2
1 0
0 1
0 2
```

### 输出

```
NO```

## 样例 #2

### 输入

```
2
1 3
1 0
-1 3
```

### 输出

```
YES```

## 样例 #3

### 输入

```
2
1 3
1 0
0 2
```

### 输出

```
YES```

## 样例 #4

### 输入

```
2
1 3
1 0
0 3
```

### 输出

```
NO```

# 题解

## 作者：StudyingFather (赞：5)

考虑两条直线相交的性质。画图容易发现，两条直线相交，则交点两端 $y$ 坐标相对大小一定改变（直观表现为，原来在下面的，相交后跑到上面去了）。如果不相交，则 $y$ 坐标的相对大小不会发生变化。

于是我们只需判断 $x=x_1$ 处各条直线的 $y$ 坐标相对大小和 $x=x_2$ 处相比，是否发生改变即可。

注意题目要求交点严格位于 $(x_1,x_2)$ 这一开区间内，所以需要排除在 $x_1,x_2$ 这两个区间端点相交的情况，详细见代码实现。

```cpp
// Problem: B. Anton and Lines
// Contest: Codeforces - Codeforces Round #329 (Div. 2)
// URL: https://codeforces.com/contest/593/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
typedef tuple<long long, long long, int> tlli;
// 通过 x1 处 y 坐标，x2 处 y 坐标和线段编号三个关键字
// 确保端点处相交的线段排序时不改变相对位置
vector<tlli> v1;
vector<tlli> v2;
int main() {
  int n;
  long long x1, x2;
  cin >> n;
  cin >> x1 >> x2;
  for (int i = 0; i < n; i++) {
    long long k, b;
    cin >> k >> b;
    v1.push_back(make_tuple(k * x1 + b, k * x2 + b, i));
  }
  sort(v1.begin(), v1.end());
  for (int i = 0; i < n; i++)
    v2.push_back(make_tuple(get<1>(v1[i]), get<0>(v1[i]), get<2>(v1[i])));
  sort(v2.begin(), v2.end());
  bool ans = false;
  for (int i = 0; i < n; i++)
    if (get<2>(v1[i]) != get<2>(v2[i])) ans = true;
  cout << (ans ? "YES" : "NO") << endl;
  return 0;
}
```

---

## 作者：三点水一个各 (赞：1)

## 题意

在平面直角坐标系中有 n 条直线（没有与y轴平行的直线），问有没有一个交点在 ($X_{1}$,$X_{2}$) 内。

每条线的解析式是y‘=$k_{i}$*x'+$b_{i}$。

***

## 思路

易证若线 A 的 k 大于线 B 的 k（$k_{A}$>$k_{B}$）且 线 A 的 b 小于线 B 的 b（$b_{A}$>$b_{B}$）,此时两直线的交点必位于($X_{1}$,$X_{2}$) 内。

图本蒟蒻懒得画了，还恳请各位大佬自行画一下。



```
#include<cstdio>
#include<algorithm>
#include<utility>
#define ll long long
using namespace std;
typedef pair<ll,ll> P; //麻麻再也不用担心make_pair了~
P a[100005];
ll n,x1,x2;
int main()
{
    scanf("%lld%lld%lld",&n,&x1,&x2);
    for(ll i=1;i<=n;i++)
    {
        ll k,b;
        scanf("%lld%lld",&k,&b);
        a[i]=P(k*x1+b,k*x2+b);//储存解析式
    }
    sort(a+1,a+n+1);//从小到大
    bool boolen=0;
    for(ll i=2;i<=n;i++)
    {
        if(a[i].second<a[i-1].second)//比较
        {
            boolen=1;break;
        }
    }
    if(boolen) printf("YES");
          else printf("NO");
    return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

### 思路
这道题我们直接求两条直线有没有交点是行不通的，我们不妨把目光聚焦在 $x1$ 和 $x2$ 上。

![](https://cdn.luogu.com.cn/upload/image_hosting/qxu4i5d7.png)

令直线 1 与 $y=x1$ 和 $y=x2$ 的交点的横坐标为 $x2$ 和 $x3$，直线 2 与 $y=x1$ 和 $y=x2$ 的交点的横坐标为 $x4$ 和 $x5$。

若 $x2>x4$ 且 $x3>x4$ 两直线平行，
若 $x2<x4$ 且 $x3<x4$ 两直线也平行。

换句话说只要 $x2$ 和 $x3$ 的大小关系和 $x4$ 和 $x5$ 的大小关系不同，则两直线必有横坐标在 $(x1,x2)$ 的交点。

所以我们把每一条直线与 $y=x1$ 和 $y=x2$ 的交点的横坐标算出来，随便按照一个排序，判断另一个是不是逆序的就好了。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct st{
	double x1,x2;
}a[100005];
int x1,x2;
bool cmp(st a,st b)
{
	if(a.x1==b.x1) return a.x2<b.x2;
	return a.x1<b.x1;
}
signed main()
{
//	freopen("1.in","r",stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	cin>>x1>>x2;
	for(int i=1;i<=n;i++)
	{
		double k,b;
		cin>>k>>b;
		a[i].x1=k*x1+b;
		a[i].x2=k*x2+b;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<n;i++)
	{
		if(a[i].x2>a[i+1].x2)
		{
			cout<<"YES\n";
			return 0;
		}
	}
	cout<<"NO\n";
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
题意概述：给定 $n$ 条直线，函数解析式为一次函数关系，求在 $x_1$ 和 $x_2$ 之间是否存在交点。

感觉更像是一个思维分析题。
## 分析。
当 $n=1$ 时，显然无解。

当 $n=2$ 时，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3144tohc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

其中的 $a_1$ 到 $a_4$ 均为交点，两个黑色的平行线代表的是 $x1$ 和 $x2$ 这两个数。如果要相交其中，那么必定有 $a_1>a_2$ 存在。

当 $n=3$ 时，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ygwc7ra5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

可以发现如果 $L_1$ 和 $L_3$ 之间有交点，那么 $L_1$ 和 $L_2$ 也必定有一个交点在 $x_1$ 和 $x_2$ 之间，所以我们此时只需要判断这三条直线是否两两相交即可。

其余情况同理。我们发现，如果我们将 $k_i$ 从小到大排序，然后如果 $l_i$ 和 $l_{i-1}$ 之间有交点，那么就说明存在，如果任意两条直线之间没有交点，那么可以说明所以的直线在 $x_1$ 和 $x_2$ 之间不存在交点。但是我们有一种特殊情况，就是其中的某两条线段的交点交在 $x_1$ 或 $x_2$ 上，但是其中的一条和其它的一条交于区间内，那么我们不妨调换一下判断的顺序，把后面的提到前面来，用结构体进行关键字排序，从小到大，然后我们就可以判断是否相交了。具体可以见代码。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
using namespace std;
long long n,x1,x2,k,b;
bool flag;
struct node{
	long long k2,b2;
}a[100005];
bool cmp(node a,node b){
	if(a.k2==b.k2){
		return a.b2<b.b2;
	}
	return a.k2<b.k2;
}
int main(){
	cin>>n>>x1>>x2;
	for (int i=0;i<n;i++){
		cin>>k>>b;
		long long l=x1*k+b;
		long long r=x2*k+b;
		a[i].k2=l;
		a[i].b2=r;
	}
	sort(a,a+n,cmp);
	for (int i=1;i<n;i++){
		if(a[i].b2<a[i-1].b2){
			flag=1;
			break;
		}
	}
	if(flag){
		cout<<"YES\n";
	}
	else cout<<"NO\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：CSP_Sept (赞：0)

### Description

>给定 $n$ 条形如 $y=k_ix+b_i$ 的直线，你需要判断是否存在两条直线的交点 $(x_0,y_0)$ 满足 $x_1<x_0<x_2$。
>
>即在 $y=x_1$ 和 $y=x_2$ 之间有无交点。

### Solution

我们先找一下交点的性质。

![](https://cdn.luogu.com.cn/upload/image_hosting/6ip5kcdb.png)

我们分别存储每一条直线与 $y=x_1$ 和 $y=x_2$ 交点的纵坐标，即 $l_i,r_i$。

我们发现 $A$  点在 $y=x_1$ 和 $y=x_2$ 之间，**当且仅当**以下关系式成立：

$$
l_1>l_2\And r_1<r_2
$$

注意到不能取等号，原因显然。

于是我们可以把问题转化为以下子问题：

>给定 $n$ 个二元组 $(x,y)$，判断是否存在两个二元组使得 $x_i>x_j$ 且 $y_i<y_j$。
>
>$1\le n\le 10^5$，你需要给出复杂度不超过 $O(n\log n)$ 的算法。

这样就是一个经典问题了。

我们按 $x$ 递减的顺序对 $(x,y)$ 排序，对于相等的 $x$，我们按 $y$ 降序排列。

从前往后扫一遍，同时维护 $m=\min y$，每次判断是否有 $y>m$。

注意到这里用了一个 $y$ 降序排列的 trick，目的是防止误判 $x$ 相等的情况。

### Code

[$\textit{134811359}$](https://codeforces.com/contest/593/submission/134811359)

---

