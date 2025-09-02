# Valuable Resources

## 题目描述

Many computer strategy games require building cities, recruiting army, conquering tribes, collecting resources. Sometimes it leads to interesting problems.

Let's suppose that your task is to build a square city. The world map uses the Cartesian coordinates. The sides of the city should be parallel to coordinate axes. The map contains mines with valuable resources, located at some points with integer coordinates. The sizes of mines are relatively small, i.e. they can be treated as points. The city should be built in such a way that all the mines are inside or on the border of the city square.

Building a city takes large amount of money depending on the size of the city, so you have to build the city with the minimum area. Given the positions of the mines find the minimum possible area of the city.

## 样例 #1

### 输入

```
2
0 0
2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2
0 0
0 3
```

### 输出

```
9
```

# 题解

## 作者：MuLinnnnn (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF485B)

**题目要求**

输入 $n$ 个 $x,y$ 坐标，输入能最小把这些点覆盖住的正方形面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/trk9eoxe.png)

**思路**

先求出 $x$ 的最大点和最小点 $p1,p3$ ， $y$ 同理 $p2,p4$ 。

知道这些坐标就知道一个长方形。

![](https://cdn.luogu.com.cn/upload/image_hosting/lmtqezwe.png)

用长方形的最长那条边作为正方形的边长，也就是 $\max(p3-p1,p4-p2)$ 。

有已知正方形面积 $S=a^2$ 。

所以最终面积为 $\max(p3-p1,p4-p2) \times \max(p3-p1,p4-p2)$ 。

p.s. 使用 ```cmath``` 里的 ```pow``` 会爆，还是乖乖用乘法吧。

p.s. 因为范围很大，所以用 ```long long``` 。

**AC Code**:
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
	long long n;
	long long p1 = 1e18,p2 = 1e18; // 小的点 （打擂赋大值）
	long long p3 = -1e18,p4 = -1e18; // 大的点 （打擂赋小值）
	scanf("%lld",&n);
	for(int i = 0; i < n; ++i) {
		long long x,y;
		scanf("%lld%lld",&x,&y);
		//公式
		p1 = min(x,p1);
		p2 = min(y,p2);
		p3 = max(x,p3);
		p4 = max(y,p4);
	}
	printf("%lld",max(p3 - p1,p4 - p2) * max(p3 - p1,p4 - p2));
	return 0;
}


```


---

## 作者：N_z_ (赞：2)

## 题意
有$n$个点，给定坐标，用最小的平行于坐标轴的正方形将它们全部框起来，求该正方形的面积。
## 思路
只要求出横坐标差最大的两点，求差，对纵坐标一样处理，就得到了最小的长方形。

那么要求的正方形就是这个长方形最长边的平方。

一边输入一边处理即可。

注意答案可能很大，要开`long long`。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int n;
    cin>>n;
    int q,w,e,r;
    cin>>q>>e;
    w=q,r=e;
    for(int x=2;x<=n;x++)
    {
        int y,z;
        cin>>y>>z;
        q=min(q,y);
        w=max(w,y);
        e=min(e,z);
        r=max(r,z);
    }
    cout<<max(w-q,r-e)*max(w-q,r-e);
}
```

---

## 作者：Moon_Wind (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF485B)

本题为了保证一个正方形能够包括所有的点，所以要找出最小的横坐标、最大的横坐标、最小的纵坐标、最大的纵坐标。而正方形的边长就是最大的横坐标减去最小的横坐标的差与最大的纵坐标减去最小的纵坐标的差的最大值。再边长乘以边长算出正方形的面积即可。

代码部分：

------------
```cpp
#include<bits/stdc++.h>
#define ll long long
ll ans=0,maxxx=-1e14,minnx=1e14,maxxy=-1e14,minny=1e14;
ll n,maxx,minn;
using namespace std;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
        ll x,y;
		cin>>x>>y;
		maxxx=max(maxxx,x);//最大的横坐标
		maxxy=max(maxxy,y);//最大的纵坐标
		minny=min(minny,y);//最小的纵坐标。
		minnx=min(minnx,x);//最小的横坐标
	} 
	maxx=maxxx-minnx;
	minn=maxxy-minny;
	ans=max(maxx,minn);//正方形边长
	cout<<ans*ans;
	return 0;
} 
```
------------
本人只是一名蒟蒻，若有错误请多多包涵，谢谢大家。


---

## 作者：zjhzs666 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF485B)

# 题意
给你 $n$ 个位于平面直角坐标系的点，求一个恰好能把所有的点都覆盖的最小正方形的面积。
# 思路
定义 $4$ 个变量，用来记录正方形的最大和最小的 $x$ 坐标与 $y$ 坐标，我们每次输入点的坐标就把它们与设置的变量进行打擂台比较，然后我们把得出的矩形的最大边长赋值到 $x$ 内，最后输出边长为 $x$ 的正方形的面积。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
long long x,y,n,xd=-999999999999,xx=999999999999,yd=-999999999999,yx=999999999999;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		xd=max(xd,x);//最大的x
		xx=min(xx,x);//最小的x
		yd=max(yd,y);//最大的y
		yx=min(yx,y);//最小的y
	}
	x=max(xd-xx,yd-yx);//正方形边长
	cout<<x*x<<endl;//正方形面积
	return 0;
} 
```


---

## 作者：Yang_OIer (赞：0)

## 题意
给定 $n$ 个坐标，有一正方形可以覆盖所有点，求它的面积。

## 思路
求出
1.	横坐标最大值
2.	横坐标最小值 
3.	纵坐标最大值
4.	纵坐标最小值 

即可求出最小长方形的长，宽。

比较出大的为正方形边长，最后套用公式即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a[21],b[21];
	int hangmax=-1000000,hangmin=10000000;
	int liemax=-100000,liemin=10000000;
	cin>>n;
	for(int i=1;i<=n;i++){ 
		cin>>a[i]>>b[i];
		if(a[i]>=hangmax) 
			hangmax=a[i];
		if(a[i]<=hangmin) 
			hangmin=a[i];
		if(b[i]>=liemax)
			liemax=b[i];	
		if(b[i]>=liemin) 
			liemin=b[i];
	}
	 	int c=hangmax-hangmin; 
		int k=liemax-liemin; 
		int ans=max(c,k); 
		cout<<ans*ans;
	return 0;
} 
```


---

## 作者：VitrelosTia (赞：0)

题链：[CF](https://codeforces.com/contest/485/problem/B)/[Luogu](https://www.luogu.com.cn/problem/CF485B)

### 题意
给定 $n$ 个坐标，用一个正方形将它们全部包含，求这个正方形的最小面积。

### 思路
要包含所有的坐标，不妨先考虑横向，显然需要使横向的边长大于等于两个横向间距最长点的距离，纵向同理；取横纵两条边的最大值为正方形的边长，此时这个边长的正方形必然可以包含所有点。

简单总结一下就是记录位于最外面四个角的个点，最后让这四个点构成长方形，取长和宽的最大值做正方形的边长即可。

实现也很简单，只需要每次读入时更新四个角的坐标。需要注意的是要开`long long`。

### code
```
#include<bits/stdc++.h>

#define ll long long
using namespace std;
const int INF=1e18;

int main(){
    ll n;
    scanf("%lld",&n);
    ll lu=INF,ld=-INF,ru=INF,rd=-INF;//left up,left down,right up,right down
    while(n--){
        ll x,y;scanf("%lld%lld",&x,&y);
        lu=min(lu,x),ld=max(ld,x);
        ru=min(ru,y),rd=max(rd,y);
    }
    cout<<max(ld-lu,rd-ru)*max(ld-lu,rd-ru);
}
```


---

## 作者：Szr__QAQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF485B)


------------
**本题坑点**：**数据范围**

题目中并没有特别说明数据范围，但我试了之后发现开 ```int``` 会爆，开 ```long long``` 即可解决,但我用的是打擂台的方法求出答案的正方形的 $4$ 个顶点，所以要将打擂台的初始最大值与最小值的绝对值所赋的值超过 $10$ 的 $9$ 次方，对于这个问题我是这样解决的：
```
const int MAXN=-2e9,MINN=2e9;
int n,x,y,ans;
int Xmax=MAXN,Ymin=MINN,Ymax=MAXN,Xmin=MINN;
// Xmax记录横坐标最大值,Xmin记录横坐标最小值,Ymax与Ymin同理 
```


------------
**本题思路**：

因为题目需求可以覆盖题目中所有点的最小的正方形，所以只要求出横坐标差最大的两点的差与纵坐标差最大的两点的差，再取两者的较大值，最后套公式求出面积即可。


------------
完整代码：
```cpp
#include<bits/stdc++.h>//这个数据范围题目中没有说明，所以 
#define int long long//要开long long 
using namespace std;

const int MAXN=-2e9,MINN=2e9;
int n,x,y,ans;
int Xmax=MAXN,Ymin=MINN,Ymax=MAXN,Xmin=MINN;
// Xmax记录横坐标最大值,Xmin记录横坐标最小值,Ymax与Ymin同理 
signed main(){
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{
		cin>>x>>y;
		Xmax=max(Xmax,x);//开始记录 
		Xmin=min(Xmin,x);
		Ymax=max(Ymax,y);
		Ymin=min(Ymin,y);
	}
	
	ans=pow(max(Xmax-Xmin,Ymax-Ymin),2);//求出正方形面积，即答案 
	cout<<ans;
	return 0;
} 
```


------------
------------
我只是一名小蒟蒻，若有错误请指正，谢谢大家。





---

