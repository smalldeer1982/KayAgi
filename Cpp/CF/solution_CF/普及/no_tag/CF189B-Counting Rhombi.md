# Counting Rhombi

## 题目描述

You have two positive integers $ w $ and $ h $ . Your task is to count the number of rhombi which have the following properties:

- Have positive area.
- With vertices at integer points.
- All vertices of the rhombi are located inside or on the border of the rectangle with vertices at points $ (0,0) $ , $ (w,0) $ , $ (w,h) $ , $ (0,h) $ . In other words, for all vertices $ (x_{i},y_{i}) $ of the rhombus the following conditions should fulfill: $ 0<=x_{i}<=w $ and $ 0<=y_{i}<=h $ .
- Its diagonals are parallel to the axis.

Count the number of such rhombi.

Let us remind you that a rhombus is a quadrilateral whose four sides all have the same length.

## 说明/提示

In the first example there exists only one such rhombus. Its vertices are located at points $ (1,0) $ , $ (2,1) $ , $ (1,2) $ , $ (0,1) $ .

## 样例 #1

### 输入

```
2 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 2
```

### 输出

```
0
```

# 题解

## 作者：Sammy_prime (赞：2)

[CF189B](https://www.luogu.com.cn/problem/CF189B)

# 思路

本题是一道水题，根据题意可确定思路为将菱形的两条对角线平移到边上，确定为一个矩形，然后枚举矩形个数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std
int w,h;
int main(){ 
	scanf("%d%d",&w,&h);
	printf("%lld\n",(w*w-w%2)*(h*h-h%2)/16);
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

一道简单的几何题 ，推导的方法很多 ，这里提供其中一种思路 。

对于菱形 ，它需要满足如下条件：
- 面积为整数 。
- 顶点为整点 。
- 顶点在矩形 (0,0) ,(w,0) ,(w,h) ,(0,h) 的边上或内部 。
- 对角线平行于轴线 。

归纳一下 ，在大矩形内部且对角线平行于轴线而交于整点 ，长度为偶数的菱形即满足条件 ，那么事实上我们并不用在意菱形的四个顶点 ，可以用顶点在整点上 ，长宽都为偶数的矩形代替菱形 ，结果是等价的 。

那么我们就把题目转化成一道类似于小学奥数的题目 ，暴力推式子即可 。
$$Ans=\dfrac{(w^2-w\mod2)(h^2-h\mod2)}{16}$$

---

## 作者：PvbeLLN (赞：0)

### 分析：

题目中指出菱形的顶点在矩形内部或边上，而且对角线平行于坐标轴，于是我们可以把每一个菱形对应到一个矩形，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/j76m09fd.png)

（红色的为符合题意的菱形，绿色的为对应的矩形）

又因为 $h$ 与 $w$ 均为整数，于是可以根据排列组合的方法得到不同的小矩形的个数。

具体见代码。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int w,h;
int main(){ 
	cin>>w>>h;
	cout<<(long long)(w*w-w%2)*(h*h-h%2)/16; //注意要用long long，否则会爆范围
	return 0;
}
```


---

## 作者：fp0cy1tz6mn4rd_ (赞：0)

# CF189B 题解

~~又是一道大水题。~~

### 题意简介

求满足以下条件的菱形个数：

- 面积为整数。

- 顶点为整点。

- 顶点在矩形 $(0,0) ,(w,0) ,(w,h) ,(0,h)$ 的边上或内部 。

- 对角线平行于轴线 。

换句话说，就是求在大矩形内部，对角线平行于轴线，交于整点，长度乘积为偶数的菱形个数。

### 思路

将这个菱形的两条线平移到边上，变成一个矩形。我们只需要枚举矩形的个数即可。

### 代码

```cpp
#include<iostream>
using namespace std;
int main(){
	int w,h; 
	cin>>w>>h;
	printf("%lld",(w*w-w%2)*(h*h-h%2)/16);
	return 0;
}
```


---

## 作者：ZM____ML (赞：0)

## 题意

求满足以下条件的菱形个数：
- 面积为整数。

- 顶点为整点（即 $x,y$ 坐标都是整数）。

- 顶点在矩形 $(0,0),(w,0),(w,h),(0,h)$ 的边上或内部（即 $0\leq x\leq w$，$0\leq y\leq h$）。

- 对角线平行于轴线。

化成一句话就是在大矩形内部，对角线平行于轴线，对角线交于整点，对角线长度乘积为偶数的菱形即满足条件。

## 思路

我们将这个菱形的两条对角线平移到边上，可以确定一个矩形，我们只要枚举一下矩形的个数即可。

## 代码
```c
#include<cstdio>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int w,h; 
signed main(){
	w=read(),h=read();
	printf("%lld",(w*w-w%2)*(h*h-h%2)/16);
	return 0;
}
```


---

## 作者：Lavande (赞：0)

# 题目

[LINK！](https://www.luogu.com.cn/problem/CF189B)

# 思路

这是一道**几何**题，就是求在大矩形内部，**对角线平行于轴线**，**交于整点**，**长度乘积为偶数**的菱形个数。

所以整体的思路是将这个菱形的两条线平移到边上，变成一个矩形，然后枚举矩形的个数就可以了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long w,h;
int main(){
//  freopen();
//  freopen(); 
	scanf("%lld%lld",&w,&h);
	printf("%lld",(w*w-w%2)*(h*h-h%2)/16);
	return 0;
}
```


---

