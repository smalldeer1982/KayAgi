# Wilbur and Swimming Pool

## 题目描述

After making bad dives into swimming pools, Wilbur wants to build a swimming pool in the shape of a rectangle in his backyard. He has set up coordinate axes, and he wants the sides of the rectangle to be parallel to them. Of course, the area of the rectangle must be positive. Wilbur had all four vertices of the planned pool written on a paper, until his friend came along and erased some of the vertices.

Now Wilbur is wondering, if the remaining $ n $ vertices of the initial rectangle give enough information to restore the area of the planned swimming pool.

## 说明/提示

In the first sample, two opposite corners of the initial rectangle are given, and that gives enough information to say that the rectangle is actually a unit square.

In the second sample there is only one vertex left and this is definitely not enough to uniquely define the area.

## 样例 #1

### 输入

```
2
0 0
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1
1 1
```

### 输出

```
-1
```

# 题解

## 作者：miraculously (赞：3)

题目大意：

给出 $n$ 个 $x$ 和 $y$ 坐标，分别选择 2 个 $x$，$y$ 作为一个唯一确定的最大矩形的两个顶点，输出这个矩形的面积。

分析：

这题只要将 $x$，$y$ 排序，$x$ 的最大值减去 $x$ 最小值乘 $y$ 的最大值减去 $y$ 的最小值就是最大矩形的面积了。

代码如下（有注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[5],y[5];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d%d",&x[i],&y[i]);
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	if(x[1]==x[n]||y[1]==y[n]||n==1)//如果n=1或者x的最大值等于x的最小值或者y的最大值等于y的最小值，则不能组成矩形，输出-1。
	printf("-1");
	else
	printf("%d",(x[n]-x[1])*(y[n]-y[1]));
}
```


---

## 作者：TheCliffSwallow (赞：1)

### 题意简述

给定 $n$ 个点的坐标 $(x,y)$，分别选择 $2$ 个 $x,y$ 作为**矩形对角线上的顶点的坐标**，使得矩形面积最大，如果无法构成矩形，那么输出 $-1$。

### 思路

这道题你有两个理解方式，而且都能 A 了这道题。（由于数据的缘故，我并不能确定哪个是正解，但是我最开始想到的是第一个情况，对了，也就写上在这里了）

1. 如果你将题意理解为是选两个点作为矩形的对角线上的点的坐标使得矩形面积最大的话，因为 $1\le n\le4$，那么直接枚举两个点并记录面积即可。[AC记录](https://www.luogu.com.cn/record/80436742)。

1. 第二种情况，你认为是任意选择 $x,y$，让他们组成两个顶点，让这两个顶点组成的矩形面积最大，这也是其他题解的思路，这里就不再赘述了。[AC记录](https://www.luogu.com.cn/record/80436056)。

而已知矩形对角线上的点，求矩形面积是再简单不过了，$S=\lvert(x_1-x_2)(y_1-y_2)\rvert$。
### CODE 1
```cpp
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
using namespace std;
int n,x[5],y[5],ans,maxx=-114514,minx=1919810,maxy=-114514,miny=1919810; 
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		maxx=max(x[i],maxx);
		minx=min(x[i],minx);
		maxy=max(x[i],maxy);
		miny=min(x[i],miny);//记录x，y的最大最小值来判断是否能组成矩形
	}
	if(n==1||maxx-minx==0||maxy-miny==0){//无法构成矩形
		cout<<-1;
		return 0;
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){//枚举两个点
			if(ans<abs((x[i]-x[j])*(y[i]-y[j])))//判断这两个点组成的矩形面积是否大于ans
				ans=abs((x[i]-x[j])*(y[i]-y[j]));
		}
	}
	cout<<ans;
  	return 0;
}
```

### CODE 2

```cpp
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
#include<string>
#include<cctype>
#define ll long long
#define ull unsigned long long
using namespace std;
int n,x[5],y[5];
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	sort(x+1,x+n+1),sort(y+1,y+n+1);
	if(x[1]==x[n] || y[1]==y[n] || n==1){
		cout<<-1;
	}else{
		cout<<(x[n]-x[1])*(y[n]-y[1]);
	}
  	return 0;
}
```


---

## 作者：WilliamFranklin (赞：1)

~~又找到了一个能写题解的。~~

首先，你要了解一个公式，在 2D 网格图上，知两点坐标，这两个点是一个矩形的对角线的两个端点，求这个矩形面积，就用 $\left|(x_1-x_2)\right| \left|(y_1-y_2)\right|$ 即可，$\left|(x_1-x_2)\right|$ 和 $\left|(y_1-y_2)\right|$ 求的就是这个矩形的宽和高。这个知道了，做这道题就简单了。
## 主要思路
其实这道题我们只要求出 $x$ 中的最大值和最小值以及 $y$ 中的最大值和最小值，再套公式就可以了。

废话不多说，上代码。

### AC Code

```cpp
#include<bits/stdc++.h> 
using namespace std;
int main() {
	int x, y, ansx = 1e9, ansy = 1e9, ansx1 = -1e9, ansy1 = -1e9, n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x >> y;
		ansx = min(ansx, x);
		ansy = min(ansy, x);
		ansx1 = max(ansx1, x);
		ansy1 = max(ansy1, y);
	}
	if(ansx == ansx1 || ansy == ansy1 || n <= 1) {
		cout << -1;
		return 0;
	}
	cout << (ansx1 - ansx) * (ansy1 - ansy);
	return 0;
} 
```


---

## 作者：Together_ (赞：1)

# 题目大意：

你有 $\mathtt n$ 个点，坐标分别是 $\mathtt{(X_1,Y_1)\ \ (X_2,Y_2)\ \ ...\ \ (X_n,Y_n)}$，你的任务是从中找出 $\mathtt 2$ 个点，使得其构成的矩阵面积最大。（注意：这两个点为左上顶点和右下顶点）

# 思路：

变输入时边找出 $\mathtt {maxx , minx , maxy, miny}$，在用公式计算即可。

# 计算矩阵的公式：

$\mathtt{(maxx - minx) × (maxy - miny)}$

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;  
int main(){
	cin>>n;
	//初始化 
	int maxx=-0x3f3f3f3f,maxy=-0x3f3f3f3f;
	int minx=0x3f3f3f3f,miny=0x3f3f3f3f;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		//找到最大最小的x和y 
		maxx=max(maxx,x);
		minx=min(minx,x);
		maxy=max(maxy,y);
		miny=min(miny,y);
	}
	//特殊判断输出-1的情况 
	if(n<=1||maxx==minx||maxy==miny){
		cout<<-1;
		return 0;
	}
	//用求矩阵的公式进行计算 
	cout<<(maxx-minx)*(maxy-miny);
    return 0;
}
```

 

---

## 作者：wangyi_c (赞：1)

## 0.前言

[题目传送门](https://www.luogu.com.cn/problem/CF596A)

## 1.题目大意

给出一个 $n$ 和 $n$ 组坐标 ${x,y}$，求两个点所组成的矩形的最大值。如果没有输出 $-1$，否则输出矩形最大值

## 2.思路讲解

我们可以先来分析无解的情况：

- 当最小的 $x$ 坐标和最大的 $x$ 坐标一样时，必定无解，因为这种情况下矩形的长为 $0$。

- 当最小的 $y$ 坐标和最大的 $y$ 坐标一样时，也必定无解，因为这种情况下矩形的宽为 $0$。

- 当 $n$ 为 $1$ 时，只有 $1$ 个点，也必定无解。

我们可以先对数组进行一个排序，找出最大值和最小值的 $x$ 和 $y$，判断一下，如果满足其中一个无解条件就输出 $-1$ 并结束程序。如果一直没有就输出 $(max_x-min_x)\times (max_y-min_y)$。

## 3.AC 代码(1)
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int x[5],y[5];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	sort(x+1,x+n+1);//排序
	sort(y+1,y+n+1);
	if(x[1]==x[n] || y[1]==y[n] || n==1){//判断是否满足条件
		cout<<-1;
	}
	else{
		cout<<(x[n]-x[1])*(y[n]-y[1]);
	}
	return 0;
}
```
## 3.AC 代码(2)
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int x,y,max_x,min_x=1e18,max_y,min_y=1e18;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		max_x=max(max_x,x);//取x的最大值
		max_y=max(max_y,y);//取y的最大值
		min_x=min(min_x,x);//取x的最小值
		min_y=min(min_y,y);//取y的最小值		
	}
	if(max_x==min_x || max_y==min_y || n==1){//判断是否无解
		cout<<-1;
	}
	else{
		cout<<(max_x-min_x)*(max_y-min_y);
	}
	return 0;
}
```
_THE END_

谢谢观看

By wangyi

---

## 作者：_ouhsnaijgnat_ (赞：1)

这道题 $n\le4$ 我是真的没有想到。

## 题目大意

给你 $n$ 个 $x$ 和 $y$。让你组成一个矩形，求出它最大的面积。

## 思路

这道题我们只要知道矩形面积怎么求就可以了，面积公式：

$(maxx-minx) \times (maxy-miny)$

$maxx$ 表示最大的 $x$，$minx$ 表示最小的 $x$，以此类推。

我们找出来最大的 $x$ 和 $y$ 以及最小的 $x$ 和 $y$。

在判断如果围出来的如果是一个点就输出 $-1$，否则就套用公式。

时间复杂度 $O(n)$，顶多也就 $4$。

来个无注释版的代码！

## 代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int n,x[5],y[5],xx,nx,xy,ny;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		xx=max(xx,x[i]);
		nx=min(nx,x[i]);
		xy=max(xy,y[i]);
		ny=min(ny,y[i]);
	}
	if(nx==xx||ny==xy||n==1){
		cout<<-1;
	}else cout<<abs((xx-nx)*(xy-ny));
    return 0;
}
```


---

## 作者：Marshall001 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF596A)

## 题目大意
给你 $n$ 个坐标 $(x,y)$，让你选择两对 $x,y$，组成一个矩形，让你求矩形面积最大可以是多大。
## 思路
$n\le4$，$n$ 很小，所以我们可以用暴力枚举来做，枚举每两对 $(x,y)$，找出最优解即可 $S=(x_1-x_2)\times(y_1-y_2)$。



## 代码

```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
const int MAXN=10;//n最大为4，数组开10肯定不会错
int x[MAXN],y[MAXN];
int main(){
	int n,ans=-1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		for(int j=1;j<i;j++){
			int X=abs(x[i]-x[j]),Y=abs(y[i]-y[j]);
			if(X*Y!=0){//如果可以组成一个矩阵
				ans=max(ans,X*Y);//那么让这个答案与目前最优解对比
			}
		}
	}
	printf("%d",ans);//输出最优解
	return 0;
}
```

---

## 作者：_lmz_ (赞：0)

首先，我们要先明确 $1$ 点，当一个矩形由 $x,y,l,r$ 这 $4$ 个变量组成的时候，矩形的面积为 $(l-x) \times (r-y)$。

我们还需要知道一点，如果 $4$ 个点相同的话，就无法组成矩形，这就是题目输出 $-1$ 的条件。

然后这道题目还有贪心的思想，我们可以发现，$4$ 个点的选择是越极端越好，所以我们需要排序，取最大、最小值。

最后贴上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ud unsigned double
#define db double
#define ll long long
const int maxn = 1e6,INF=0x7fffffff;
const int X[]={0,1,0,-1},Y[]={-1,0,1,0};
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,x[maxn],y[maxn];
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	sort(x+1,x+1+n);
	sort(y+1,y+1+n);
	if(x[1]==x[n]||y[1]==y[n]||n==1) cout<<"-1";
	else cout<<(x[n]-x[1])*(y[n]-y[1]);
	return 0;
}
```

---

