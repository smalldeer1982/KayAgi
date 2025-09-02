# Say Hello

## 题目描述

两个朋友正在芭比星系旅行。如果他们的距离小于或等于 $d _ 1$，并且这是他们第一次交谈或者在他们上次互相打招呼后的某个时间点，他们的距离大于 $d_2$，那么他们会互相打一次招呼。

我们需要计算这两位朋友打招呼的次数。有 $n$ 个时刻，对于每个人，我们知道他在每个时刻的位置。位置都是在二维平面上的整点。

一个人可以在两个时刻之间保持相同的位置，但是如果一个人在两个时刻之间的位置不同，我们假设他会以恒定的速度在恒定的方向上从上个时刻移动到下个时刻。

## 样例 #1

### 输入

```
4
2 5
0 0 0 10
5 5 5 6
5 0 10 5
14 7 10 5
```

### 输出

```
2
```

# 题解

## 作者：daifucong (赞：2)

这是一道计算几何题。

题意如下：

有两个人，他们第$i(1\leqslant i\leqslant n)$秒开始时分别会在点$a_i,b_i$上，在第$i(1 \leqslant i <n)$秒中内，他们分别会从点$x_i,y_i$出发进行匀速直线运动到达点$x_{i+1},y_{i+1}$。当这两个人的距离小于等于$d_1$，且这两个人之前未曾say hello或这两个人在之前的某个时刻的距离大于$d_2$，这两个人会say hello。
求这两个人say hello的次数。

我们发现，在第$i$秒内，这两个人的距离可能：

1. 一直变大
2. 一直变小
3. 先变小再变大

我们可以计算$t$时刻和$t+10^{-4}$时刻两人的距离来判断$t$时刻两人距离的变化情况。

接下来大力分类讨论所有情况即可。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-5;
struct Point
{
	double x,y;
	Point(){}Point(double __x,double __y){x=__x;y=__y;}
	inline Point operator +(const Point &p)const{return Point(x+p.x,y+p.y);}
	inline Point operator -(const Point &p)const{return Point(x-p.x,y-p.y);}
	inline Point operator *(const double &p)const{return Point(x*p,y*p);}
	inline double sqr(){return x*x+y*y;}
	inline void read(){scanf("%lf%lf",&x,&y);}
	inline void print(){printf("(%0.5f %0.5f)",x,y);}
};
inline double dis(Point a,Point b){return sqrt((a-b).sqr());}
inline double calcdis(Point a1,Point a2,Point b1,Point b2,double k)
{
	Point A=(a2-a1)*k+a1,B=(b2-b1)*k+b1;
	return dis(A,B);
}//计算某一秒开始过了k秒时(0<=k<=1)，两人之间的距离
int n;double d1,d2;
Point la,lb,a,b;int ans=0;
bool flag=1;//flag表示如果这时两人距离小于d1,两人能否say hello
int main()
{
	scanf("%d",&n);scanf("%lf%lf",&d1,&d2);
	la.read();lb.read();if(dis(la,lb)-eps<=d1) ans++,flag=0;
	for(int i=2;i<=n;i++)
	{
		a.read();b.read();
		bool flag1=calcdis(la,a,lb,b,0)>calcdis(la,a,lb,b,eps),flag2=calcdis(la,a,lb,b,1-eps)>calcdis(la,a,lb,b,1);
		if(flag1&&flag2)
		{
			double mindis=dis(a,b),maxdis=dis(la,lb);
			if(maxdis-eps>d2) flag=1;
			if(flag&&mindis-eps<=d1) ans++,flag=0;
		}//距离变小
		else if(flag1)
		{
			double l=0,r=1;
			while(l+eps<r)
			{
				double mid=(l+r)*0.5;
				bool check=calcdis(la,a,lb,b,mid)>calcdis(la,a,lb,b,mid+eps);
				if(check) l=mid;else r=mid;
			}//通过二分找出距离最小的时刻
			double mindis=calcdis(la,a,lb,b,l);
			if(flag&&mindis-eps<=d1) ans++,flag=0;
			if(dis(a,b)-eps>d2) flag=1;
		}//距离先变小再变大
		else if(flag2) assert(0);//这种情况不存在
		else
		{
			double maxdis=dis(a,b);
			if(maxdis-eps>d2) flag=1;
		}//距离变大
		la=a;lb=b;
	}
	cout<<ans;
}
```

---

