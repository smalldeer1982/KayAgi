# Surrounded

## 题目描述

So, the Berland is at war with its eternal enemy Flatland again, and Vasya, an accountant, was assigned to fulfil his duty to the nation.

Right now the situation in Berland is dismal — their both cities are surrounded! The armies of flatlanders stand on the borders of circles, the circles' centers are in the surrounded cities. At any moment all points of the flatland ring can begin to move quickly in the direction of the city — that's the strategy the flatlanders usually follow when they besiege cities.

The berlanders are sure that they can repel the enemy's attack if they learn the exact time the attack starts. For that they need to construct a radar that would register any movement at the distance of at most $ r $ from it. Thus, we can install a radar at such point, that at least one point of the enemy ring will be in its detecting range (that is, at a distance of at most $ r $ ). Then the radar can immediately inform about the enemy's attack.

Due to the newest technologies, we can place a radar at any point without any problems. But the problem is that the berlanders have the time to make only one radar. Besides, the larger the detection radius $ (r) $ is, the more the radar costs.

That's why Vasya's task (that is, your task) is to find the minimum possible detection radius for the radar. In other words, your task is to find the minimum radius $ r $ $ (r>=0) $ such, that a radar with radius $ r $ can be installed at some point and it can register the start of the movements of both flatland rings from that point.

In this problem you can consider the cities as material points, the attacking enemy rings - as circles with centers in the cities, the radar's detection range — as a disk (including the border) with the center at the point where the radar is placed.

## 说明/提示

The figure below shows the answer to the first sample. In this sample the best decision is to put the radar at point with coordinates $ (2,0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF190B/d8b028b093bb3a5b506b76e0b869d1e14653f9f5.png)The figure below shows the answer for the second sample. In this sample the best decision is to put the radar at point with coordinates $ (0,0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF190B/621697dde00296bbf818d1a40e69e6ac2914a652.png)

## 样例 #1

### 输入

```
0 0 1
6 0 3
```

### 输出

```
1.000000000000000```

## 样例 #2

### 输入

```
-10 10 3
10 -10 3
```

### 输出

```
11.142135623730951```

# 题解

## 作者：王梓涵 (赞：1)

# CF190B Surrounded 题解

## 01. 题目大意
给出两个圆的位置和半径，输出第三个圆连接其它两个圆的最小半径，误差不超过 $10^{-6}$。

## 02.题目分析
因为输出的数是第三个圆连接其它两个圆的半径，也就是说这个输出的数
就是两圆最短距离的距离的一半，于是就可以把情况分为三种：

1. 两圆相离（就是两圆没有交点且不为包含）

1. 两圆包含（就是大圆包小圆）

1. 两圆相切或相交

首先两圆的最短距离公式为：
$$di=\sqrt{(x1-x2)^2+(y1-y2)^2}$$

用代码表达就是：
```cpp
double di1 = pow(x1 - x2, 2);
double di2 = pow(y1 - y2, 2);
double di = sqrt(di1 + di2);
```

如果是第 $1$ 种情况，即 $di>r1+r2$，则第三个圆的半径就是 $(di-r1-r2)\div2$，其中 $di$ 为两圆的最短距离。

如果是第 $2$ 种情况，即 $di<\left|r1+r2\right|$，则第三个圆的半径就是 $\left|r1-r2\right|-di\div2$，其中 $di$ 为两圆的最短距离。

如果是第 $3$ 种情况，即两个圆相切或相交，最小半径就是 $0$。

## 03. 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x1, y1, r1, x2, y2, r2;
	cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
	double di1 = pow(x1 - x2, 2);
	double di2 = pow(y1 - y2, 2);
	double di = sqrt(di1 + di2); //求两圆最短距离
	if (di > r1 + r2)
	{
		cout << fixed << setprecision(10) << (di - r1 - r2) / 2 << endl; //具题意，这个精度肯定把误差控制在1e-6内
	}
	else if (di < abs(r1 - r2))
	{
		cout << fixed << setprecision(10) << (abs(r1 - r2) - di) / 2 << endl;
	}
	else
	{
		cout << "0" << endl;
	}
	return 0; //完结撒花~
}
```

---

## 作者：wang_freedom (赞：0)

### 思路：
设大圆圆心坐标为 $(a_x,a_y)$，半径为 $a_r$，小圆圆心坐标为 $(b_x,b_y)$，半径为 $b_r$，大圆和小圆圆心之间的距离为 $dis$。

两个圆的距离有三种情况。

第一种是小圆嵌套在大圆里面，答案为 $b_r-a_r-dis$。

第二种是两个圆相交，答案为 $0$。

第三种是两个圆不相交也不嵌套，答案为 $dis-a_r-b_r$。
### AC Code:
```cpp
#include<bits/stdc++.h>
typedef double lf;
using namespace std;
lf dis;
struct circle{
	int x,y,r;
}a,b;
lf get_dis(circle a,circle b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>a.x>>a.y>>a.r>>b.x>>b.y>>b.r;
	dis=get_dis(a,b);
	if(a.r>b.r)
		swap(a,b);
	if(dis<=a.r+b.r&&b.r-a.r>dis)//嵌套 
		cout<<fixed<<setprecision(12)<<lf((b.r-a.r-dis)/2);
	else if(dis<=a.r+b.r)//两圆相交 
		cout<<fixed<<setprecision(12)<<0;
	else//正常 
		cout<<fixed<<setprecision(12)<<lf((dis-a.r-b.r)/2);
	return 0;
}
```

---

## 作者：Moon_Wind (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF190B)



------------
首先，两点之间的**距离公式**是：

$$dis=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$$



两个圆在同一个平面上有**两种**位置关系：


**情况一**：两圆不相交，有**两种**可能：

**可能一**：有一个圆在另一个圆里面。

![](https://cdn.luogu.com.cn/upload/image_hosting/nf6xjody.png?x-oss-process=image/resize,m_lfit,h_350,w_715)

这时，第三个圆的**直径**就是**大圆的半径**减去**小圆的半径**再减去**大圆圆心与小圆圆心的距离**。

**可能二**：一个圆在另一个圆的外面。

![](https://cdn.luogu.com.cn/upload/image_hosting/zsnp9x2w.png?x-oss-process=image/resize,m_lfit,h_350,w_715)

如图所示，此时第三个圆的**直径**就是**大小圆心的距离**与**两个圆半径之和**的差。

**情况二**：两圆相交。

![](https://cdn.luogu.com.cn/upload/image_hosting/p5xx7nnk.png?x-oss-process=image/resize,m_lfit,h_350,w_725)

很明显，此时两个圆之间的最近距离是 $0$，所以第三个圆的半径也就是 $0$。


**代码部分**：

------------
   ```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	   ios::sync_with_stdio(0);
	   cin.tie(0);cout.tie(0);
	   int x,y,r,xx,yy,rr;
	   cin>>x>>y>>r>>xx>>yy>>rr;
	   double cx=x-xx,cy=y-yy,dis=sqrt(cx*cx+cy*cy);
	   if(dis<abs(r-rr)
		printf("%.10lf",(fabs(r-rr)-dis)/2);//可能一。
       else if(dis>r+rr) 
		printf("%.10lf",(dis-r-rr)/2);//可能二。
	   else //情况二。
		cout<<0;//注意一下，这里要输出整数，不然第9个点过不去。
	   return 0;
}
```



------------

本人只是一名蒟蒻，若有错误请多多包涵，谢谢大家。

---

## 作者：ccrui (赞：0)

## 题意理解
题目已经说的很清楚了，输出第三个圆连接两个圆的最小半径。

## 两圆圆心之间的距离
根据两点间的面积公式，可以求出两圆圆心之间的距离长度为：

$$\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$$

设 $l=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$。

## 两个圆在平面上有三种状态
### 1.不相交

#### 情况一
当 $l>r_1+r_2$ 时出现。

![](https://cdn.luogu.com.cn/upload/image_hosting/io96lt0e.png)

很容易发现把第三个圆放在蓝色线段是最优的，那它的直径就是两圆圆心的距离长度减去两圆半径的长度（即蓝色线段减去两段红色线段），所以第三个圆的半径就是：

$$\frac{l-r_1-r_2}{2}$$

#### 情况二
当 $l<\left | r_1-r_2 \right | $ 时出现。

![](https://cdn.luogu.com.cn/upload/image_hosting/n2scyott.png)

很容易发现把第三个圆放在红色线段是最优的，那它的直径就是大圆半径的长度减去两圆圆心的距离长度和小圆半径的长度之和，所以第三个圆的半径就是：

$$\frac{max_{r_1,r_2}-l-min_{r_1,r_2}}{2}$$

### 2.相交且不是相切
当 $l>\left | r_1-r_2 \right | $ 且 $l<r_1+r_2$ 时出现。

![](https://cdn.luogu.com.cn/upload/image_hosting/um2z0h1x.png)

这时只要把第三个圆放在两个交点的位置，这时它的半径就可以为 $0$ 了。

### 3.相切
当$l=\left | r_1-r_2 \right | $ 或 $l=r_1+r_2$ 时出现。

![](https://cdn.luogu.com.cn/upload/image_hosting/3ido776o.png)

- 当出现前一种情况时，可以发现蓝色线段等于两圆半径的长度之和，
所以满足：

$$\sqrt{(x1-x2)^2+(y1-y2)^2}=r1+r2$$

- 当出现后一种情况时，可以发现蓝色线段等于两圆半径的长度之和，
所以满足：

$$\sqrt{(x1-x2)^2+(y1-y2)^2}=r1-r2$$

当出现这两种情况时直接输出 $0$ 即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double x1,y,r1;
double x2,y2,r2;
int main(){
	cin>>x1>>y>>r1;
	cin>>x2>>y2>>r2;//输入 
	double xc=(x1-x2)*(x1-x2);
	double yc=(y-y2)*(y-y2);
	double l=sqrt(xc+yc),ans;//两圆圆心之间的距离长度
	if(fabs(l-abs(r1+r2))<0.0000001)cout<<"0.000000000000000";//相切情况一
	else if(fabs(l-abs(r1-r2))<0.0000001)cout<<"0.000000000000000";//相切情况二
	else if(l<r1+r2&&l>fabs(r1-r2))cout<<"0.000000000000000";//相交且不是相切 
	else if(l>r1+r2)printf("%.15lf",(l-r1-r2)/2);//不相交情况一
	else printf("%.15lf",(max(r1,r2)-l-min(r1,r2))/2);//不相交情况二
	return 0;
}

```
[AC记录](https://www.luogu.com.cn/record/120069932)

---

## 作者：neil021110 (赞：0)

给出两个圆的位置和半径，输出第三个圆连接其他两个圆的最小半径

两圆间的距离公式d=sqrt(pow(x1-x2,2)+pow(y1-y2,2))

若d>r1+r2则两个圆外离，则最小半径为(d-r1-r2)/2

若d<abs(r1-r2)则两个圆内含，则最小半径为(abs(r1-r2)-d)/2

其余情况下，两个圆相切或相交，则最小半径为0
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int main(){
	int x1,y1,r1,x2,y2,r2;
	cin>>x1>>y1>>r1>>x2>>y2>>r2;
	double d=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	if(d>r1+r2){
		printf("%.15lf",(d-r1-r2)/2);
	}else if(d<abs(r1-r2)){
		printf("%.15lf",(abs(r1-r2)-d)/2);
	}else{
		printf("%.15lf",0);
	}
	
} 
```


---

