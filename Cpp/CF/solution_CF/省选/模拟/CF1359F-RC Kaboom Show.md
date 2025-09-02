# RC Kaboom Show

## 题目描述

You know, it's hard to conduct a show with lots of participants and spectators at the same place nowadays. Still, you are not giving up on your dream to make a car crash showcase! You decided to replace the real cars with remote controlled ones, call the event "Remote Control Kaboom Show" and stream everything online.

For the preparation you arranged an arena — an infinite 2D-field. You also bought $ n $ remote controlled cars and set them up on the arena. Unfortunately, the cars you bought can only go forward without turning left, right or around. So you additionally put the cars in the direction you want them to go.

To be formal, for each car $ i $ ( $ 1 \le i \le n $ ) you chose its initial position ( $ x_i, y_i $ ) and a direction vector ( $ dx_i, dy_i $ ). Moreover, each car has a constant speed $ s_i $ units per second. So after car $ i $ is launched, it stars moving from ( $ x_i, y_i $ ) in the direction ( $ dx_i, dy_i $ ) with constant speed $ s_i $ .

The goal of the show is to create a car collision as fast as possible! You noted that launching every car at the beginning of the show often fails to produce any collisions at all. Thus, you plan to launch the $ i $ -th car at some moment $ t_i $ . You haven't chosen $ t_i $ , that's yet to be decided. Note that it's not necessary for $ t_i $ to be integer and $ t_i $ is allowed to be equal to $ t_j $ for any $ i, j $ .

The show starts at time $ 0 $ . The show ends when two cars $ i $ and $ j $ ( $ i \ne j $ ) collide (i. e. come to the same coordinate at the same time). The duration of the show is the time between the start and the end.

What's the fastest crash you can arrange by choosing all $ t_i $ ? If it's possible to arrange a crash then print the shortest possible duration of the show. Otherwise, report that it's impossible.

## 说明/提示

Here is the picture for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1359F/d2ecf70507b59a587066a94bf192c2aaf876732b.png)The fastest cars to crash are cars $ 2 $ and $ 4 $ . Let's launch car $ 2 $ at $ 0 $ , car $ 4 $ at about $ 0.096762 $ and cars $ 1 $ and $ 3 $ at arbitrary time. That way cars $ 2 $ and $ 4 $ will crash into each other at about $ 0.585902 $ . So here's what it looks like at the moment of the collision:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1359F/7eb93988ebce321ea184467bf5782ea0b56ef6ba.png)Here's the picture for the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1359F/8ba1cf46328b0ac8eb2a7e79c52a4646f39b1d74.png)

## 样例 #1

### 输入

```
4
3 -1 -1 1 2
2 3 -3 -2 10
-4 2 1 -2 1
-2 -2 -1 2 4```

### 输出

```
0.585902082262898```

## 样例 #2

### 输入

```
2
-1 1 -1 1 200
1 1 1 5 200```

### 输出

```
No show :(```

# 题解

## 作者：猪脑子 (赞：4)

首先，如果我们考虑二分一个答案$t$，那么问题就会变成判断是否存在一种方案使得能让两个车在时间$t$之前相撞。

如果想到这里，稍微动动脑筋就会发现，假如我们把每辆车在$t$时间内能够到达的位置画出来，那么图像会是$n$条线段，此时如果存在两个线段有公共点，那么就一定存在一个方案。

现在问题就变成如何判断线段之间是否有交点了。

我们考虑一个类似扫描线的东西：按照$x$从小到大扫描，将每个线段拆成插入和删除两个事件（题目中没有线段与坐标轴平行，这样就减少了很多麻烦），此时考虑如何判断是否存在两条线段有交。

我们用一个set去维护线段，set内部按照线段与直线$x=x_0$（$x_0$是当前扫描到的$x$）交点的纵坐标排序，这个东西用一个自定义的比较运算符就可以搞定。

每次加入一条线段的时候，我们找到它上面和下面与它相邻的两条线段，判断一下加入的线段与这两条线段有没有交；删除一条线段的时候，我们还是找到它上面和下面的两条线段，判断这两条线段之间是否相交。一旦我们发现有两条线段相交，就立刻返回。不难发现，如果有两条线段相交，那么一定能够判断出来（可以对这两种情况都画画图理解一下）。

然后由于令人头大的精度误差，进行实数判断的时候要仔细一些。最主要的是两个地方：第一个是进行大小比较的时候最好设个精度误差，第二个是删除线段的时候不一定要现从set中find，可以在插入的时候将对应的iterator存下来，删除的时候直接erase掉iterator就可以了

具体细节可以看代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
using namespace std;
const double eps=1e-8;
struct Line{
	double k,b;
	double l,r;
	int id;
};
double X;//for comparing
bool operator <(const Line& a,const Line& b)
{
	double vala=a.k*X+a.b;
	double valb=b.k*X+b.b;
	if(fabs(vala-valb)>eps)
		return vala<valb;
	return a.id<b.id;
}
bool check_inter(Line a,Line b)
{
	double dk=a.k-b.k;
	double db=b.b-a.b;
	if(fabs(dk)<eps)
		return fabs(a.b-b.b)<eps&&a.r+eps>b.l-eps&&a.l-eps<b.r+eps;
	double x=db/dk;
	return a.l-eps<x&&x<a.r+eps&&b.l-eps<x&&x<b.r+eps;
}
struct Vec{
	double x,y;
	Vec(double xx=0,double yy=0)
	{
		x=xx;
		y=yy;
	}
	double len()
	{
		return sqrt(x*x+y*y);
	}
}p[25010],dir[25010];
Vec operator +(const Vec& a,const Vec& b){return Vec(a.x+b.x,a.y+b.y);}
Vec operator -(const Vec& a,const Vec& b){return Vec(a.x-b.x,a.y-b.y);}
Vec operator *(const Vec& a,const double& b){return Vec(a.x*b,a.y*b);}
Vec operator /(const Vec& a,const double& b){return Vec(a.x/b,a.y/b);}
Line GetLine(Vec a,Vec b)
{
	if(a.x>b.x)swap(a,b);
	Line res;
	res.l=a.x;res.r=b.x;
	res.k=(b.y-a.y)/(b.x-a.x);
	res.b=a.y-res.k*a.x;
	return res;
}
Line l[25010];
struct Event{
	double x;
	int id,op;
	Event(){}
	Event(double a,int b,int c)
	{
		x=a;
		id=b;
		op=c;
	}
}e[50010];
bool cmp(Event a,Event b)
{
	return a.x<b.x;
}
int n;
typedef multiset<Line>::iterator iter;
iter It[25010];
bool check(double t)
{
	multiset<Line>S;
	for(int i=1;i<=n;i++)
	{
		l[i]=GetLine(p[i],p[i]+dir[i]*t);
		l[i].id=i;
		Vec to=p[i]+dir[i]*t;
//		printf("%d:(%.3lf,%.3lf),(%.3lf,%.3lf)\n",i,p[i].x,p[i].y,to.x,to.y);
		e[i*2-1]=Event(l[i].l,i,0);
		e[i*2]=Event(l[i].r-eps,i,1);
	}
	sort(e+1,e+n*2+1,cmp);
	for(int i=1;i<=n*2;i++)
	{
		int id=e[i].id;
		X=e[i].x;
//		printf("x:%lf,id=%d\n",X,id);
		if(e[i].op==0)
		{
			iter it=S.insert(l[id]);
			iter it1;It[id]=it;
			if(it!=S.begin())
			{
				it1=it;it1--;
//				printf(")
				if(check_inter(*it1,*it))
					return true;
			}
			it1=it;it1++;
			if(it1!=S.end())
			{
				if(check_inter(*it1,*it))
					return true;
			}
		}
		else{
			iter it=It[id],it1,it2;
			it1=it;it1++;it2=it;
			if(it1!=S.end()&&it2!=S.begin())
			{
				it2--;
				if(check_inter(*it1,*it2))
					return true;
			}
			S.erase(it);
		}
	}
	return false;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		double s;
		scanf("%lf %lf %lf %lf %lf",&p[i].x,&p[i].y,&dir[i].x,&dir[i].y,&s);
		dir[i]=dir[i]/dir[i].len()*s;
	}
//	check(5);
//	return 0;
	double l=0,r=1e12;
	int tim=100;
	while(tim--)
	{
		double mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid;
	}
	if(r>1e11)printf("No show :(\n");
	else printf("%.10lf\n",r);
	return 0;
}
```


---

