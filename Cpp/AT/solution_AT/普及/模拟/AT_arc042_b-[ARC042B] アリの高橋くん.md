# [ARC042B] アリの高橋くん

## 题目描述

阿里的高桥在凸多边形的木板上。高桥一直朝着对面的方向走，但是不知道朝着哪个方向。高桥君一走到木板周围就掉下来了。因为高桥君的位置和构成板子的凸多边形的顶点的位置被给予，所以请求高桥君从板子上掉下来之前走的最短距离。位置全部以二维坐标给出。

## 说明/提示

如果你垂直走到哪一边，你只需走100步就从木板上掉下来。


------------

翻译者：[Eric1030](https://www.luogu.com.cn/user/995571)

## 样例 #1

### 输入

```
0 0
4
100 100
-100 100
-100 -100
100 -100```

### 输出

```
100```

## 样例 #2

### 输入

```
10 10
3
0 100
-100 -100
100 -100```

### 输出

```
31.3049516850```

## 样例 #3

### 输入

```
34 6
7
-43 -65
-23 -99
54 -68
65 92
16 83
-18 43
-39 2```

### 输出

```
25.0284205314```

# 题解

## 作者：kkksc03___is_sb (赞：1)

## 题意
给出一个凸多边形，求其中一个点与其中每一条边距离的最小值。

------------

## 思路

1. 在初一数学中，我们知道一个点到一条边的距离为过这一点所作的垂线的线段长度，如图中的 $ L $ 。

![图1](https://cdn.luogu.com.cn/upload/image_hosting/juo5ixhu.png)

2. 那么我们就可以把每条线段上的端点与目标点相连。

![图2](https://cdn.luogu.com.cn/upload/image_hosting/eq3vvwy3.png)

3. 则构成的三角形以凸多边形的每条边为底所作的对于三角形的高的最小值即为本题的答案。

![图3](https://cdn.luogu.com.cn/upload/image_hosting/965vybgd.png)

4. 对第三步进行证明。唯一一种不符合离开凸多边形的距离为三角形（见上文）的高的情况为该三角形如下图

![图4](https://cdn.luogu.com.cn/upload/image_hosting/lp5rjj4v.png)

但在这种情况下保证有其他线段大于该真实距离

![图5](https://cdn.luogu.com.cn/upload/image_hosting/apyeivvs.png)

![图6](https://cdn.luogu.com.cn/upload/image_hosting/8dxblsgl.png)

5. 求高就是最后的一步，我们可以通过距离公式求出三角形边的长度，然后通过海伦公式计算面积，在反推出答案。


------------


## 代码

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;

struct poi
{
	double x, y;
}A[15];

double len(double x1, double y1, double x2, double y2)//两点间距离公式
{
	return sqrt(abs(x1 - x2) * abs(x1 - x2) + abs(y1 - y2) * abs(y1 - y2));
}

double hl(double x, double y, double z)//海伦公式
{
	double p = (x + y + z) / 2;
	return sqrt(p * (p - x) * (p - y) * (p - z));
}

int main()
{
	double x, y;
	int n;
	cin >> x >> y >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> A[i].x >> A[i].y;
	}
	double a, b, c, sq, x1, x2, y1, y2;
	a = len(x, y, A[1].x, A[1].y), b = len(x, y, A[n].x, A[n].y), c = len(A[n].x, A[n].y, A[1].x, A[1].y),
	sq = hl(a, b, c);
	double ans = sq * 2 / c;//先以以A[1],A[n]为底的高为答案数据
	for(int i = 1; i < n; i++)
	{
		a = len(x, y, A[i].x, A[i].y), b = len(x, y, A[i + 1].x, A[i + 1].y), c = len(A[i + 1].x, A[i + 1].y, A[i].x, A[i].y),
		sq = hl(a, b, c);//枚举以A[i],A[i+1]为底的距离
		ans = min(ans, sq * 2 / c);
	}
	if(ans != (int)(ans))
	{
		printf("%.10lf\n", ans);
	}
	else
	{
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：qianyuzhe (赞：0)

## 题意简述

给定高橋和一个凸 $n$ 边形每个顶点的坐标，求高橋走出该图形的最小距离。

## 题目分析

由于高桥最终一定从该图形的边上出来，而我们知道，直线外一点与直线上各点连接的所有线段中，垂线段最短，于是我们可以分别计算出该图形每条边与高桥的距离并取最小值输出。

如果采用函数的做法很难推出公式，因此我们可以采用面积法求解。设高橋的坐标为 $A(x_1,y_1)$，该图形某条边两个端点的坐标分别为 $B(x_2,y_2)$ 和 $C(x_3,y_3)$，由勾股定理可得 $\begin{cases}AB=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}\\AC=\sqrt{(x_1-x_3)^2+(y_1-y_3)^2}\\BC=\sqrt{(x_2-x_3)^2+(y_2-y_3)^2}\end{cases}$，令 $p=\dfrac{AB+AC+BC}{2}$，由海伦公式可得 $S_{\vartriangle ABC}=\sqrt{p\times(p-AB)\times(p-AC)\times(p-BC)}$，由三角形面积公式可得 $A$ 到 $BC$ 的距离为 $\dfrac{2S_{\vartriangle ABC}}{BC}$。

对于 $\vartriangle ABC$ 中 $\angle ABC$ 或 $\angle ACB$ 是钝角的情况，易得此时 $A$ 到 $BC$ 的距离一定不是全局最优解，因此无需特判。

时间复杂度 $O(n)$，空间复杂度 $O(n)$，可以通过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i;
double x,y,a,b,c,d,m=500;
pair<double,double>p[15];
int main(){
	ios::sync_with_stdio(false);
	cin>>x>>y>>n;
	for(i=0;i<n;i++)cin>>p[i].first>>p[i].second;//输入顶点坐标 
	p[n]=p[0];
	for(i=0;i<n;i++){
		a=hypot(x-p[i].first,y-p[i].second);
		b=hypot(x-p[i+1].first,y-p[i+1].second);
		c=hypot(p[i].first-p[i+1].first,p[i].second-p[i+1].second);
		d=(a+b+c)/2;
		m=min(m,2*sqrt(d*(d-a)*(d-b)*(d-c))/c);//海伦公式+面积法求A到BC的距离 
	}
	cout<<fixed<<setprecision(10)<<m;//保留10位小数输出 
}
```

---

