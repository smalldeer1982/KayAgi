# Okabe and Banana Trees

## 题目描述

Okabe needs bananas for one of his experiments for some strange reason. So he decides to go to the forest and cut banana trees.

Consider the point $ (x,y) $ in the 2D plane such that $ x $ and $ y $ are integers and $ 0<=x,y $ . There is a tree in such a point, and it has $ x+y $ bananas. There are no trees nor bananas in other points. Now, Okabe draws a line with equation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821B/943332af45ee9b24d3dd582c61cd6fb6bc9281c7.png). Okabe can select a single rectangle with axis aligned sides with all points on or under the line and cut all the trees in all points that are inside or on the border of this rectangle and take their bananas. Okabe's rectangle can be degenerate; that is, it can be a line segment or even a point.

Help Okabe and find the maximum number of bananas he can get if he chooses the rectangle wisely.

Okabe is sure that the answer does not exceed $ 10^{18} $ . You can trust him.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821B/9062959c907537ca725899b162ca1dad63845c7e.png)The graph above corresponds to sample test 1. The optimal rectangle is shown in red and has $ 30 $ bananas.

## 样例 #1

### 输入

```
1 5
```

### 输出

```
30
```

## 样例 #2

### 输入

```
2 3
```

### 输出

```
25
```

# 题解

## 作者：IGA_Indigo (赞：5)

## 题目大意
每个点 $(a,b)$（$a$、$b$ 都取正整数）都有一个点权 $a+b$，给定一条直线 $y=-\frac{x}{m}+b$，在这条直线与 $y$ 轴和 $x$ 轴所围成的三角形中截取一个最大的正方形，使得所围成的点权最大。
## 大体思路
每个点都是正的，所以加一个点不会让围成的点权变小，我们最好的方案只能是 $(x,y)$ 在每一个 $x$ 取正整数、$y$ 取正整数最靠近直线的点作为矩形的一个顶点。矩形的四个顶点就是 $(0,0)$、$(0,y)$、$(x,0)$、$(x,y)$，我们可以枚举每一个 $y$，$x$ 可以由 $y$ 推得，因为 $b\le10^4$，所以 $O(b)$ 是可取的复杂度。

枚举每一个 $y$，$x=m\times (b-y)$，由 $\sum^n_{i=1}i=(1+n)\times n\div2$ 可以拓展成二维得右上角为 $(x,y)$ 的矩形有 $(x+1)\times(y+1)\times(x+y)\div2$ 个玉米，在枚举 $y$ 的过程中比较，求出最大值即可。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(long long x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return ;
}
int main(){ 
	long long m,b;
	long long ans=0;
	m=read();
	b=read();
	long long sum=0;
	for(int y=0;y<=b;y++){
		long long x=m*(b-y);
		sum=(x+1)*(y+1)*(x+y)/2;
		if(sum>ans){
			ans=sum;
		}
	}
	write(ans);
	putchar('\n');
}
```

---

## 作者：littleone (赞：2)

### 题目大意

给你一条直线 $y = -\frac{x}{m}+b$，在平面直角坐标系中的**给定的直线下**画一个**四条边平行于坐标轴**的矩形。当且仅当 $x,y$ 均为**非负整数**时，在 $(x,y)$ 这个点上有 $x+y$ 个香蕉。问所画矩形的内部和边界上加起来最多能有几个香蕉。

### 思路

注意到给定的直线、$x$ 轴和 $y$ 轴围成了一个底边长度为 $b \times m$，高为 $b$ 的直角三角形。因此考虑直接暴力枚举所画矩形右上角的 $x$ 坐标。（这里枚举 $y$ 坐标可能会漏掉一些情况）

枚举出右上角的 $x$ 坐标后，$y$ 坐标和矩形内的香蕉数量也就确定了。其中矩形内的香蕉数量为：

$$\sum_{i=0}^{x}\sum_{j=0}^{y}(i+j)$$

但是如果对于枚举出的每个矩形都这样计算答案，会超时。所以进入推式子环节：

$$\sum_{i=0}^{x}\sum_{j=0}^{y}(i+j)$$

$$=\sum_{i=0}^{x}\sum_{j=0}^{y}i+\sum_{i=0}^{x}\sum_{j=0}^{y}j$$

$$=\sum_{i=0}^{x}(y+1)i+\sum_{i=0}^{x}\frac{y(y+1)}{2}$$

$$=\frac{(x+1)(y+1)x}{2}+\frac{(x+1)(y+1)y}{2}$$

$$=\frac{(x+1)(y+1)(x+y)}{2}$$

这样，计算答案的部分的时间复杂度就是 $O(1)$ 了，总体的时间复杂度为 $O(b \times m)$。

### 代码

最后附上短小精悍的代码。其中有一个坑点，c++ 中的整型除以整型是**向0取整**而不是向下取整，因此需要用 cmath 中的向下取整函数。

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
int m,b;
long long y,ans;
int main(){
    scanf("%d%d",&m,&b);
    for(long long x = 0;x <= m * b;x++){
        y = floor(b - x / (double)m);
        ans = max(ans,(x + 1) * (y + 1) * (x + y) / 2);
    }
    printf("%lld",ans);
    return 0;
}
```

---

