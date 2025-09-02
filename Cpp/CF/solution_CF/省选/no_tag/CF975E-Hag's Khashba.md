# Hag's Khashba

## 题目描述

按逆时针顺序给出一个凸多边形的 n 个顶点，初始第 1,2 个顶点被钉在了墙上

一共有 q 个操作，操作分为两种：

1 f t：解除第 f 个点的钉子，待图形在重力的作用下平衡之后，在第 t 个点处钉上一颗钉子  
2 v：询问当第 v 个点的坐标。

## 样例 #1

### 输入

```
3 4
0 0
2 0
2 2
1 1 2
2 1
2 2
2 3
```

### 输出

```
3.4142135624 -1.4142135624
2.0000000000 0.0000000000
0.5857864376 -1.4142135624
```

## 样例 #2

### 输入

```
3 2
-1 1
0 0
1 1
1 1 2
2 1
```

### 输出

```
1.0000000000 -1.0000000000
```

# 题解

## 作者：奇卡 (赞：1)

## CF975E

根据你的初中物理学知识可以发现，旋转中心和重心的连线在重力所在的直线上时，旋转才会停止。

然后重心这个东西又很好维护，只用知道旋转中心的坐标和它到旋转中心的距离就好了。

于是考虑维护重心位置和重心和多边形上各点组成的**向量**，再记录下旋转了多少角度，每次修改直接用旋转角度算当前向量，得到当前点的位置。

**一个比较重要的点**

初始重心坐标**不是**$(\frac{\sum_{i\le n}x_i}{n},\frac{\sum_{i\le n}y_i}{n})$

一个反例：在$\frac{1}{4}$圆的圆弧上取很多个点，按照逆时针顺序连边，然后把最左边和最右边的点和圆心连边。这样的图形按照上式求出的重心和圆弧会非常接近，但显然不是这样的。

正确的求重心方法是**三角剖分+带权平均**，对凸多边形有$G=\frac{\sum_{i} s_i\times G_i}{\sum_i s_i}$，其中$s_i,G_i$表示剖出来第$i$个三角形的面积和重心。

如果把三角形看成质点上面的式子大概会比较好理解些？

代码
```cpp
//maremaremaremaremaremaremaremaremaware
#include<bits/stdc++.h>
#define For(i,x,y) for(int i=(x);i<=(y);++i)
#define Rof(i,x,y) for(int i=(x);i>=(y);--i)
typedef double db;
typedef long double ldb;
typedef long long ll;
const int N=1e4+5;
using namespace std;

int pin[2],x[N],y[N];
db gx=0,gy=0,dd=0,S=0;
struct vec{
	vec(db a=0,db b=0){ x=a,y=b; }
	db x,y;
}a[N];

db dist(db x,db y,db _x,db _y){ return sqrt((x-_x)*(x-_x)+(y-_y)*(y-_y)); }
db dot(vec a,vec b){ return a.x*b.x+a.y*b.y; }
db cross(vec a,vec b){ return a.x*b.y-a.y*b.x; } 
db deg(vec a,vec b){ return atan2(cross(a,b),dot(a,b)); }
vec rotate(vec l,ldb d){ return vec(l.x*cos(d)-l.y*sin(d),l.y*cos(d)+l.x*sin(d)); }

int main(){
	int n,q,op,f,t;
	scanf("%d%d",&n,&q);
	For(i,1,n){
		scanf("%d%d",&x[i],&y[i]);
//		gx+=(ldb)1.0*x[i]/n,gy+=(ldb)1.0*y[i]/n;
	}
	pin[0]=1,pin[1]=2;
	For(i,2,n-1){
		db xx=(x[i]+x[i+1]+x[1])/3.00,yy=(y[i]+y[i+1]+y[1])/3.00;
		db s=cross(vec((db)x[i]-x[1],(db)y[i]-y[1]),vec((db)x[i+1]-x[1],(db)y[i+1]-y[1]))/2.00;
		S+=s,gx+=s*xx,gy+=s*yy;
	}
	gx/=S,gy/=S;
//	gx/=1.0*n,gy/=1.0*n;
//	printf("%.10Lf %.10Lf\n",gx,gy);
	For(i,1,n) a[i]=vec(x[i]-gx,y[i]-gy);
	while(q--){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&f,&t);
			if(f==pin[0]) f=pin[1]; else f=pin[0];
			vec nowaf=rotate(a[f],dd);
			db fx=gx+nowaf.x,fy=gy+nowaf.y;
			db d=deg(vec(-nowaf.x,-nowaf.y),vec(0.00,-1.00));
			dd+=d,gy=fy-dist(fx,fy,gx,gy),gx=fx;
			if(f==pin[1]) pin[0]=t; else pin[1]=t;
		} else{
			scanf("%d",&f);
			vec nowaf=rotate(a[f],dd);
			printf("%.10f %.10f\n",gx+nowaf.x,gy+nowaf.y);
		}
	}
}
```


---

