# Power Transmission (Hard Edition)

## 题目描述

This problem is same as the previous one, but has larger constraints.

It was a Sunday morning when the three friends Selena, Shiro and Katie decided to have a trip to the nearby power station (do not try this at home). After arriving at the power station, the cats got impressed with a large power transmission system consisting of many chimneys, electric poles, and wires. Since they are cats, they found those things gigantic.

At the entrance of the station, there is a map describing the complicated wiring system. Selena is the best at math among three friends. He decided to draw the map on the Cartesian plane. Each pole is now a point at some coordinates $ (x_i, y_i) $ . Since every pole is different, all of the points representing these poles are distinct. Also, every two poles are connected with each other by wires. A wire is a straight line on the plane infinite in both directions. If there are more than two poles lying on the same line, they are connected by a single common wire.

Selena thinks, that whenever two different electric wires intersect, they may interfere with each other and cause damage. So he wonders, how many pairs are intersecting? Could you help him with this problem?

## 说明/提示

In the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C2/2317b27306c4c65175012212cdceb02039be0972.png)In the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C2/0792ee139dbdc603551bd0c872a1bea92551eac5.png)Note that the three poles $ (0, 0) $ , $ (0, 2) $ and $ (0, 4) $ are connected by a single wire.

In the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C2/9e20f52f47cf7b9d491a8675d81506c0f862a971.png)

## 样例 #1

### 输入

```
4
0 0
1 1
0 3
1 2
```

### 输出

```
14
```

## 样例 #2

### 输入

```
4
0 0
0 2
0 4
2 0
```

### 输出

```
6
```

## 样例 #3

### 输入

```
3
-1 -1
1 0
3 1
```

### 输出

```
0
```

# 题解

## 作者：V1mnkE (赞：1)

直接求相交可能有些困难？换一种思路，两条直线不是平行就是相交，那对于每一条线段，与其相交的直线条数就是总数减去与其平行的直线条数。

什么时候两条直线平行呢？两个斜率相同的时候，那开个 map 记录斜率看上去就可以了。

$k=\frac{dy}{dx}$，但是直接用浮点数会有问题，把解析式换 $a_1x+b_1y=c_1$ 的形式，这样就可以通过记录 $a_1,b_1$ 判断直线是否平行。

注意重合的线段只能算一次，可以对于每组 $a,b$ 开一个集合，如果 $a_1,b_1$ 对应的集合里面没有出现 $c_1$ 就塞 $c_1$ 进去。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;
int T;
int n;
struct point{
	double x,y;
}a[maxn];
map<pair<int,int>,set<int> >mp;
int gcd(int a,int b){
//	cout<<114514;
	if(b==0)return a;
	return gcd(b,a%b);
}
int main(){
	T=1;
	while(T--){
		cin>>n;
		long long ans=0,tot=0;
		for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
		for(int i=1;i<=n;i++){
			for(int j=1;j<i;j++){
				int d1=(a[i].y-a[j].y);
				int d2=(a[i].x-a[j].x);
				int d3=a[j].x*a[i].y-a[i].x*a[j].y;
				int dls=gcd(d1,d2);
				d1/=dls,d2/=dls;
				if(d1<0||(d1==0&&d2<0)){
					d1=-d1,d2=-d2;
				}
				d3=d2*a[j].y-d1*a[j].x;
				pair<int,int>k=make_pair(d1,d2);
				if(mp[k].find(d3)==mp[k].end()){
					ans+=tot-(int)mp[k].size();
					tot++;
					mp[k].insert(d3);
				}
			}
		}
		cout<<ans;
	}
}
```


---

## 作者：幻影星坚强 (赞：1)

两条直线相交仅当他们斜率不同，所以求出所有直线之后去个重，于是问题成了求在n个数中选择两个不同数的方案数（我对于斜率不存在需是单独考虑的，即an数组）。

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct bian
{
	double b, k;
}eg[1000100], an[1000100];
int n, num, anoth;
long long zong, ans;
double x[1010], y[1010];
bool pd(bian i, bian j)
{
	return (i.k < j.k || (i.k == j.k && i.b < j.b));
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i)
	{
		scanf("%lf%lf", &x[i], &y[i]);
		for (int j = 1; j < i; ++ j)
		{
			if(x[i] == x[j])
			{
				an[++ anoth].k = x[i];
				continue;
			}
			eg[++ num].k = (y[j] - y[i]) / (x[j] - x[i]);
			eg[num].b = y[i] - x[i] * eg[num].k;
		}
	}
	sort(eg + 1, eg + num + 1, pd);
	
	sort(an + 1, an + anoth + 1, pd);
	long long now = 0;
	for (int i = 1; i <= num; ++ i)
	{
		if(eg[i].k == eg[i - 1].k)
		{
			if(eg[i].b == eg[i - 1].b)
			{
				continue;
			}
			ans += now - zong;
			++ zong;
		}
		else
		{
			zong = 0;
			ans += now - zong;
			++ zong;
		}
		++ now;
	}
	long long dif = now;
	now = 0;
	for (int i = 1; i <= anoth; ++ i)
	{
		if(an[i].k == an[i - 1].k && i > 1)
		{
			continue;
		}
		else
		{
			ans += dif;
		}
	}
	printf("%lld\n", ans);
}
```


---

## 作者：az__eg (赞：0)

简单计算几何题。

为了方便，接下来直线表达式默认使用 $y=kx+b$。

我们发现两条直线不相交当且仅当平行，即两条直线 $k_1 = k_2$。

然后发现一共有 $n^2$ 条直线。我们可以直接把每一条的直线解析式求出来，然后直接算就行。与一条直线相交的数量，就是与这条直线的 $k$ 值不同的直线数量。

然后去个重即可，一些处理的小细节在代码的注释里：

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
const long double eps=1e-10;
using namespace std;
bool equal(long double a,long double b)
{
	if(fabs(a-b)<eps)
	{
		return true;
	}
	else
	{
		return false;
	}
}
struct node
{
	long double x,y;
}point[1001];
int n;
struct node2
{
	long double k,b;
	bool operator < (const node2 &asd)const
	{
		if(equal(k,asd.k))
		{
			return b<asd.b;
		}
		return k<asd.k;
	}
}line[1000001],line2[1000001];
int	zl[1000001];
int cnt2;
int cnt;
int sum[1000001];
signed main()
{
	cin>>n;
	int i,j;
	for(i=1;i<=n;i++)
	{
		cin>>point[i].x>>point[i].y;
	}
	for(i=1;i<=n;i++)
	{
		for(j=i+1;j<=n;j++)
		{
			long double kk,bb;
			kk=(point[j].y-point[i].y)/(point[j].x-point[i].x);
			bb=point[i].y-point[i].x*kk;
			if(equal(point[j].x,point[i].x))
			{
				kk=1145151919810;//防止无穷大情况。
				bb=point[i].x;//防止两条直线相同。
			}
			line[++cnt].k=kk;
			line[cnt].b=bb;
		}
	}
	sort(line+1,line+1+cnt);
	int svcnt=cnt;
	cnt=0;
	line2[++cnt]=line[1];
	for(i=2;i<=svcnt;i++)
	{
		if(equal(line[i].k,line[i-1].k)&&equal(line[i].b,line[i-1].b))//去重直线
		{
			continue;
		}
		else
		{
			line2[++cnt]=line[i];
		}
	}
	zl[++cnt2]+=1;
	for(i=2;i<=cnt;i++)
	{
		if(equal(line2[i].k,line2[i-1].k))
		{
			zl[cnt2]+=1;
		}
		else
		{
			zl[++cnt2]+=1;
		}
	}
	int ans=0;
	for(i=cnt2;i>=1;i--)
	{
		sum[i]=sum[i+1]+zl[i];
	}
	for(i=1;i<=cnt2;i++)
	{
		ans+=zl[i]*sum[i+1];
	}
	cout<<ans;
}
```


---

