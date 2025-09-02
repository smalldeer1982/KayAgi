# Beru-taxi

## 题目描述

**题意翻译**
Vasiliy在点（a，b），他周围有n辆出租车，坐标在点（x，y），速度是v，假设Vasiliy已经知道了他最早能坐上哪辆出租车，请你求出他最早能坐上出租车的时间（出租车将直线朝Vasiliy行驶）。

## 样例 #1

### 输入

```
0 0
2
2 0 1
0 2 2
```

### 输出

```
1.00000000000000000000```

## 样例 #2

### 输入

```
1 3
3
3 3 2
-2 3 6
-2 7 10
```

### 输出

```
0.50000000000000000000```

# 题解

## 作者：DreamsChaser (赞：3)

此题可以依靠纯模拟解决。

我们发现：对于一辆在 $(x_k,y_k)$ 的出租车，他想要赶到 $\texttt{Vasiliy}$ 所处的坐标 $(a,b)$，他所耗费的时间如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/i0eoc3ud.png)

我们设 $A(a,b),B(x_k,y_k)$，则 $C(x_k,b)$

由勾股定理知

$$\therefore S=\sqrt{(x_k-a)^2+(y_k-b)^2}$$

$$t=S/v$$

即可求出每辆出租车到达 $(a,b)$ 的时间了，再求最小值即可。

代码不展示了，留给大家自行思考，有不懂的欢迎随时私信。

---

## 作者：happybob (赞：0)

水题，众所周知，两点之间直线距离：

$\Large \sqrt{(x2 - x1)^2+(y2-y1)^2}$。

然后就能过了：

```cpp
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
	double a, b, n, ans = 1e14;
	cin >> a >> b >> n;
	for (int i = 1; i <= n; i++)
	{
		double x, y, v;
		cin >> x >> y >> v;
		ans = min(ans, sqrt(pow(x - a, 2) + pow(y - b, 2)) / v);
	}
	cout << fixed << setprecision(20) << ans << endl;
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有一个人在点 $(a,b)$ 等出租车。已知他周围共有 $n$ 辆出租车，其中第 $i$ 辆车在点 $(x_i,y_i)$ 上，速度为 $v_i$。这个人想打能让他最早上车的出租车，请问这辆出租车需要多久才能到达这个人的位置？

**数据范围：$-100\leqslant a,b,x_i,y_i\leqslant 100,1\leqslant n\leqslant 1000,1\leqslant v_i\leqslant 100$。**
## Solution
直接暴力计算每辆车到达这个人位置的时间。因为距离为 $\sqrt{(x_i-a)^2+(y_i-b)^2}$，速度为 $v_i$，所以第 $i$ 辆车到达的时间为 $\dfrac{\sqrt{(x_i-a)^2+(y_i-b)^2}}{v_i}$。然后按照时间为关键字从小到大排序，输出第一个即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int n;
double ax, ay;
struct node {
	double x, y, v, dist;
	bool operator < (const node& ss) const {return dist < ss.dist;}
}a[100007];

int main() {
	scanf("%lf%lf%d", &ax, &ay, &n);
	for(int i = 1; i <= n; ++i)	{
		scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].v);
		a[i].dist = sqrt((ax - a[i].x) * (ax - a[i].x) + (ay - a[i].y) * (ay - a[i].y)) / a[i].v;
	}
	sort(a + 1, a + n + 1);
	printf("%.20lf", a[1].dist);
}
```

---

## 作者：sysu_yzc (赞：0)

## 思路
利用[勾股定理](https://baike.baidu.com/item/%E5%8B%BE%E8%82%A1%E5%AE%9A%E7%90%86/91499?fr=aladdin)求出每个点与Vasiliy的家的距离，再除以$t$，求出每辆出租车，用$ans$记录最小值即为答案。
## 上代码
```
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
double A,ans=100000000;
int main(){
	int a,b,x,y,t,n;
	cin>>a>>b>>n;
	for(int i=0;i<n;i++){
		cin>>x>>y>>t;
		A=sqrt(fabs(x-a)*fabs(x-a)+fabs(y-b)*fabs(y-b))/t;
		if(ans>A) ans=A;
	}
	printf("%.6f",ans);
	return 0;
}
```

---

