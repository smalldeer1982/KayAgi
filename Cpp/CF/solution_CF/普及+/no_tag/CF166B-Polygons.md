# Polygons

## 题目描述

You've got another geometrical task. You are given two non-degenerate polygons $ A $ and $ B $ as vertex coordinates. Polygon $ A $ is strictly convex. Polygon $ B $ is an arbitrary polygon without any self-intersections and self-touches. The vertices of both polygons are given in the clockwise order. For each polygon no three consecutively following vertices are located on the same straight line.

Your task is to check whether polygon $ B $ is positioned strictly inside polygon $ A $ . It means that any point of polygon $ B $ should be strictly inside polygon $ A $ . "Strictly" means that the vertex of polygon $ B $ cannot lie on the side of the polygon $ A $ .

## 样例 #1

### 输入

```
6
-2 1
0 3
3 3
4 1
3 -2
2 -2
4
0 1
2 2
3 1
1 0
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5
1 2
4 2
3 -3
-2 -2
-2 1
4
0 1
1 2
4 1
2 -1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
-1 2
2 3
4 1
3 -2
0 -3
5
1 0
1 1
3 1
5 -1
2 -1
```

### 输出

```
NO
```

# 题解

## 作者：minecraft_herobrine (赞：2)

这个题其实等价于

给你一个凸多边形 $A$ 和一个点集 $B$ ，问 $B$ 中的所有点是否都在 $A$ 中，不允许在边界上。

如果一个一个枚举的话显然复杂度会爆炸

所以我们对这个 $A$ 求一次凸包，然后把 $AB$ 点集合并成一个大点集，对这个大点集求一个凸包，比较一下这两个凸包是否相同就行了。

因为当 $B$ 点集中有一个点在 $A$ 外部时候， $AB$ 的共同凸包必然会包含这个在 $A$ 外边的点，而这个点属于 $B$ 集合，所以这种情况下两个凸包必然不同，反之两个凸包相同。

这里用Andrew算法求凸包，保留凸包上的点，这样可以判断边界的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
const int MAXN=1.2e5+10;
struct Vector
{
	double x,y;
	Vector operator - (const Vector &f) const//向量减法
	{
		Vector res;
		res.x=x-f.x;res.y=y-f.y;
		return res;
	}
	bool operator < (const Vector &f) const
	{
		return x<f.x||x==f.x&&y<f.y;
	}
}A[MAXN],B[MAXN],res[MAXN],res2[MAXN];
//A数组存的是A集合，B数组存的是AB两个集合
//res1和res2表示对应凸包上的点

double cross(Vector a,Vector b)//求向量叉积
{
	return a.x*b.y-b.x*a.y;
}

int andrew1(Vector p[],int n)//对A求凸包
{
	sort(p+1,p+n+1);
	int m=1,i;
	for(i=1;i<=n;i++)//求下凸壳
	{
		while(m>2 && cross(res[m-1]-res[m-2],p[i]-res[m-2])<0) m--;
		res[m++]=p[i];
	}
	int k=m;
	for(i=n-1;i>=1;i--)//上凸壳
	{
		while(m>k && cross(res[m-1]-res[m-2],p[i]-res[m-2])<0) m--;
		res[m++]=p[i];
	}
	if(m>2) m--;
	return m;
}

int andrew2(Vector p[],int n)//对AB求凸包
{
	sort(p+1,p+n+1);
	int m=1,i;
	for(i=1;i<=n;i++)
	{
		while(m>2 && cross(res2[m-1]-res2[m-2],p[i]-res2[m-2])<0) m--;
		res2[m++]=p[i];
	}
	int k=m;
	for(i=n-1;i>=1;i--)
	{
		while(m>k && cross(res2[m-1]-res2[m-2],p[i]-res2[m-2])<0) m--;
		res2[m++]=p[i];
	}
	if(m>2) m--;
	return m;
}

int main()
{
	int n,m,i,a,b;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%lf %lf",&A[i].x,&A[i].y);
		B[i].x=A[i].x;
		B[i].y=A[i].y;
	}
	scanf("%d",&m);
	for(i=1;i<=m;i++) scanf("%lf %lf",&B[i+n].x,&B[i+n].y);
	int m1=andrew1(A,n),m2=andrew2(B,n+m);//m1,m2表示两个凸包中点的数量
//	printf("%d %d\n",m1,m2);
	if(m1!=m2)//点数都不一样显然都不是一个凸包了
	{
		printf("NO");
		return 0;
	}
	sort(res+1,res+m1+1);
	sort(res2+1,res2+m2+1);
	for(i=0;i<m1;i++)//点数相同看是否都是相同的点
	{
		double x1=res[i].x,x2=res2[i].x,y1=res[i].y,y2=res2[i].y;
		if(fabs(x1-x2)>=eps || fabs(y1-y2)>=eps) break;
	}
	printf(i==m1 ? "YES" : "NO");
	return 0;
}
```


---

