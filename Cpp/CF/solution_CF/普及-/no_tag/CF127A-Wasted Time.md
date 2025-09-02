# Wasted Time

## 题目描述

Mr. Scrooge, a very busy man, decided to count the time he wastes on all sorts of useless stuff to evaluate the lost profit. He has already counted the time he wastes sleeping and eating. And now Mr. Scrooge wants to count the time he has wasted signing papers.

Mr. Scrooge's signature can be represented as a polyline $ A_{1}A_{2}...\ A_{n} $ . Scrooge signs like that: first it places a pen at the point $ A_{1} $ , then draws a segment from point $ A_{1} $ to point $ A_{2} $ , then he draws a segment from point $ A_{2} $ to point $ A_{3} $ and so on to point $ A_{n} $ , where he stops signing and takes the pen off the paper. At that the resulting line can intersect with itself and partially repeat itself but Scrooge pays no attention to it and never changes his signing style. As Scrooge makes the signature, he never takes the pen off the paper and his writing speed is constant — $ 50 $ millimeters per second.

Scrooge signed exactly $ k $ papers throughout his life and all those signatures look the same.

Find the total time Scrooge wasted signing the papers.

## 样例 #1

### 输入

```
2 1
0 0
10 0
```

### 输出

```
0.200000000```

## 样例 #2

### 输入

```
5 10
3 1
-5 6
-2 -1
3 2
10 0
```

### 输出

```
6.032163204```

## 样例 #3

### 输入

```
6 10
5 0
4 0
6 0
3 0
7 0
2 0
```

### 输出

```
3.000000000```

# 题解

## 作者：sqh_let_it_be (赞：3)

刚开始看到这个题的时候有一点懵，没搞懂这个 $k$ 是什么意思，然后在草纸上一通验算，发现这个 $k$ 只参与到了最后的乘法运算里......

言归正传，回到题目上。

由[勾股定理](https://baike.baidu.com/item/%E5%8B%BE%E8%82%A1%E5%AE%9A%E7%90%86/91499?fr=aladdin)可得，$ab$ 两点之间的距离公式为

$$ab= \sqrt{{(a_x-b_x)}^2+{(a_y-b_y)}^2} $$

注：$a_x$，$b_x$ 表示 $a,b$ 的横坐标。$a_y$，$b_y$ 表示 $a,b$ 的纵坐标。

那我们的思路就非常清晰了，就是用两个数组将输入的坐标存起来，然后再按顺序算将这些点连起来的总长度，再用这个总长度与 $k$ 相乘再除以时间就行了。

# Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorihtm>
#include<cmath>
using namespace std;
int n,k,y[10001],x[10001];
double ans;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	  cin>>x[i]>>y[i];//蒟蒻不会输一个算一个
	for(int i=2;i<=n;i++)
		ans=ans+sqrt(pow(x[i-1]-x[i],2)+pow(y[i-1]-y[i],2));
	ans=ans*k/50;
	printf("%.9lf",ans);
	return 0;
}
```

小心 CE。

---

## 作者：simonG (赞：1)

### 前言
题目为Wasted time，意味节约时间，所以我们需要简洁的代码。  
### 详解
>1，a,b两点距离之间的公式为
$S(a,b)=sqrt((ax-bx)^2+(ay-by)^2)$  
其中ax，bx表示x轴坐标，ay，by同理。即运用初中二年级学过的勾股定理，在一个直角三角形内，斜边平方等于其两边的平方之和。

>2，既然节约时间，就要用最简单易懂的方法。知道每两个点之间的距离后，把它们开始点与结束点连接，再用结束点连接下一个点。用一个循环变量指向开始点。

>3,最后，用路程总和除以速度

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,X,Y;
double ans;
int main()
{
	scanf("%d %d",&n,&m);
	scanf("%d %d",&x,&y);
	for(int i=1;i<n;i++)
	{
		scanf("%d %d",&X,&Y);
		ans+=sqrt((x-X)*(x-X)+(y-Y)*(y-Y));
		x=X;y=Y;
	}
	printf("%.9lf",ans*m/50.0);
	return 0;
}
```
### 后记
简单题简单做

---

## 作者：Allanljx (赞：0)

## 题意
有 $n$ 个点，第 $i$ 个点要连接第 $i+1$ 个点，连接的速度是 $50$ 每秒，每两个点要连接 $k$ 次。问要多少秒才能连完所有的线。
## 思路
用勾股算出两个点的距离，加起来，最后再除以 $50$，乘 $k$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int n,k;
	int a1,a2,b1,b2;//a1和b1表示前一个点的坐标，a2和b2表示当前点的坐标
	double ans;
	cin>>n>>k;
	cin>>a1>>b1;
	for(int i=2;i<=n;i++)
	{
		cin>>a2>>b2;
		ans+=1.0*sqrt((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2));//勾股算距离
		a1=a2,b1=b2;//更新
	}
	printf("%.9f",ans*k/50.0);
    return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
平面上有 $A_1(x_1,y_1),A_2(x_2,y_2),...,A_n(x_n,y_n)$ 共计 $n$ 个点。你需要依次将 $A_1$ 连接至 $A_2$，$A_2$ 连接至 $A_3$，以此类推，直到将 $A_{n-1}$ 连接至 $A_n$ 为止。每次连接的长度即为连接的两个点之间的距离。你需要在 $k$ 个相同的平面上完成这样的操作，已知你连接的速度为 $50$ 个单位每秒，求完成所有的连接操作需要的时间。

**数据范围：$2\leqslant n\leqslant 100,1\leqslant k\leqslant 1000$。**
## Solution
每次将线段的长度除以 $50$ 累加进去，这样就不需要再在最后还要除以一个 $50$。最后记得答案再乘上 $k$。总之不是很难。

贴个两点之间的距离公式吧：$dis(A,B)=\sqrt{(x_A-x_B)^2+(y_A-y_B)^2}$
## Code
```cpp
#include <cstdio>
#include <cmath>
using namespace std;

int n;
double ans, x[107], y[107], k;

double dist(int i, int j) {
	return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) / 50.0;
}

int main() {
	scanf("%d%lf", &n, &k);
	for(int i = 1; i <= n; ++i)	scanf("%lf%lf", &x[i], &y[i]);
	for(int i = 1; i < n; ++i)	ans += dist(i, i % n + 1);
	printf("%.9lf", ans * k);
}
```

---

## 作者：codemap (赞：0)

第一眼看到这道题还以为很难，其实就是一个简单题

k其实就是直接用来乘的，没有任何其他作用

只要注意一下要用double就可以了

没有什么可解释的，直接上代码吧，代码里会有解释
```c
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
double dis(double x1,double y1,double x2,double y2)//两点之间距离，注意这里所有都要用double
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));//直接用两点之间距离公式
}
int main()
{
    int n,i;
    double k,x[101],y[101],s=0;//这些都要用double
    cin>>n>>k;
    for(i=1;i<=n;i++)
        cin>>x[i]>>y[i];
    for(i=2;i<=n;i++)
        s+=dis(x[i],y[i],x[i-1],y[i-1])/50*k;//每一个和前一个算一下距离，注意要除50并且乘k
    printf("%.9f",s);//输出，保留9位小数
    return 0;//完美结束
}
```
# 拒绝抄袭，共创和谐洛谷

---

