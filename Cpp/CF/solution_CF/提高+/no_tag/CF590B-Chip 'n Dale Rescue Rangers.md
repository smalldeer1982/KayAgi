# Chip 'n Dale Rescue Rangers

## 题目描述

一群毛茸茸的救援小队在他们的树洞里休息时，突然接到了求救信号。他们立刻整装出发，驾驶着他们的飞艇开始了救援之旅。

假设救援行动在一个平面直角坐标系中进行。救援队的总部位于点 $(x_1, y_1)$，求救信号来自点 $(x_2, y_2)$。

借助 Gadget 的高超工程技术，救援飞艇可以在任何时刻随意改变速度和飞行方向。唯一的限制是：相对于空气，飞艇的速度不能超过 $v$ 米/秒。

当然，Gadget 希望尽快到达求救地点。然而，空中风速对飞艇的运动有影响。根据天气预报，未来的 $t$ 秒内风速为向量 $(v_x, v_y)$，之后将变为向量 $(w_x, w_y)$。这些向量表示风的方向和速度。具体来说，如果飞艇此时位于点 $(x, y)$，相对于空气的速度为零，同时风速为 $(u_x, u_y)$，那么经过 $\Delta t$ 秒，飞艇将到达新位置 $(x + u_x \cdot \Delta t, y + u_y \cdot \Delta t)$。

由于 Gadget 忙于驾驶，她希望 Chip 计算出他们最快能何时到达目的地。Chip 很快找出了答案，但 Dale 对结果表示怀疑，认为 Chip 只是随便给了个数。于是，Dale 请求你帮忙找出正确答案。

可以确保在任何时间点上，风的速度都严格小于飞艇相对于空气的最大速度。

## 样例 #1

### 输入

```
0 0 5 5
3 2
-1 -1
-1 0
```

### 输出

```
3.729935587093555327
```

## 样例 #2

### 输入

```
0 0 0 1000
100 1000
-50 0
50 0
```

### 输出

```
11.547005383792516398
```

# 题解

## 作者：skyskyCCC (赞：0)

## 前言。
上一个提交这个题的人的提交时间都过去一年了。本题是非常裸的二分。

题意简述：一个救援队，计划从 $\left(x_1,y_1\right)$ 出发前往 $\left(x_2,y_2\right)$。救援人员的飞船可以根据需要随时改变当前的速度和运动方向，但是该飞船的最大静风速度为 $V_{\max}$。已知在 $\left[0,t\right]$ 时间内风的向量表示为 $\left(V_x,V_y\right)$，此后的风的向量表示为 $\left(W_x,W_y\right)$。其中保证风的速度在任何时刻都严格小于飞船相对于空气的最大可能速度（即静风速度）。请求出最短需要的时间。
## 分析。
这个就比较物理了。我们要求求出最小的时间，那么在 $t$ 个单位时间之后，因为风时刻影响飞船的速度，且必定存在满足要求和不满足要求的唯一分界点，显然时间是单调的，所以求最小时间这个问题上我们可以采用二分时间的方式。在时间的确定的情况下，可以得到飞船的位移，从而判断是不是能到达目的地。

我们可以把这个运动拆成两个方面。一个方面是受风力影响而移动的距离，另一个是本身的移动距离。风吹的影响无非就是将飞船看做静止不动的，然后算风推的距离即可。飞船在静止时，其移动方向就是风向，设飞行时间为 $k$。若小于 $t$ 秒，则移动的距离为 $\left(x_1+V_x\times k,x_2+V_y\times k\right)$。若大于 $t$ 秒，则移动的距离就是 $\left(x_1+V_x\times t+W_x\times\left(k-t\right),x_2+V_y\times t+W_y\times\left(k-t\right)\right)$。然后把这两方面分别判断，看看是否合法即可。

代码如下，仅供参考：
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int x1,y_1,x2,y2,vmax,t,vx,vy,wx,wy;
double ans,leftt,rightt=100000000.0;
double dis(double x1,double y_1,double x2,double y2){
	return (x1-x2)*(x1-x2)+(y_1-y2)*(y_1-y2);
}
bool check(double ti){
	double min_x,min_y;
	if(ti-t*1.0>=1e-7){
		min_x=x1*1.0+vx*t*1.0+wx*1.0*(ti-1.0*t);
		min_y=y_1*1.0+vy*t*1.0+wy*1.0*(ti-1.0*t);
	}
	else{
		min_x=x1*1.0+vx*1.0*ti;
		min_y=y_1*1.0+vy*1.0*ti;
	}
	if(dis(min_x,min_y,x2*1.0,y2*1.0)<(vmax*1.0*ti)*(vmax*1.0*ti)){
	    return true;
	}
	else return false;
}
int main(){
	cin>>x1>>y_1>>x2>>y2>>vmax>>t>>vx>>vy>>wx>>wy;
	while(fabs(rightt-leftt)>1e-7){
		  double mid=(leftt+rightt)/2.0;
		  if(check(mid)){
		        rightt=mid;
		        ans=mid;
		  }
		  else  leftt=mid;
	}
	printf("%.18lf\n",ans);
	return 0;
}
```
## 后记。
大家如有疑问。可以在评论区提出，我会尽力解答的。

---

