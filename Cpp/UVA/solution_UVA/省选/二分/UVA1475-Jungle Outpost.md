# Jungle Outpost

## 题目描述

在丛林里有n个瞭望塔，瞭望塔的保护范围就是一个凸n多边形，敌人进攻会炸毁一些瞭望塔，使总部暴露在剩下的瞭望塔围成的凸多边形之外，请你选择一个点作为总部，使得敌人要炸毁的瞭望塔尽量多。

## 样例 #1

### 输入

```
3
0 0
50 50
60 10
5
0 0
0 10
10 20
20 10
25 0```

### 输出

```
1
2```

# 题解

## 作者：TimeTraveller (赞：2)

这个题就是一个半平面交加二分，因为敌人每次如果炸k个瞭望塔，那么连续的k个肯定比分散的k个要更优，所以每次二分答案k，将点每隔k个连一条新的线，判断这些新的线有无半平面交即可。

下面上代码

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define db double
using namespace std;
const int M=1e5+10;
const db eps=1e-7;
struct point{
	db x,y;
	point(db a=0,db b=0):x(a),y(b){}
	void in(){scanf("%lf%lf",&x,&y);}
}pp[M];

point operator +(point a,point b){return point(a.x+b.x,a.y+b.y);}
point operator -(point a,point b){return point(a.x-b.x,a.y-b.y);}
point operator *(point a,db    b){return point(a.x*b  ,a.y*b  );}
point operator /(point a,db    b){return point(a.x/b  ,a.y/b  );}

db cross(point a,point b){return a.x*b.y-a.y*b.x;}
db dot  (point a,point b){return a.x*b.x+a.y*b.y;}

struct line{
	point p,v;
	db ang;
	line(){}
	line(point a,point b):p(a),v(b){ang=atan2(v.y,v.x);}
	bool operator <(line a)const{return ang<a.ang;}
	point getp(db t){return p+v*t;}
}l[M];

bool onleft(line le,point p){
	return cross(le.v,p-le.p)>0;
}

point getlinecut(line a,line b){
	point u=a.p-b.p;
	db t=cross(b.v,u)/cross(a.v,b.v);
	return a.getp(t);
}

int fi,la;
point p[M];
line  q[M];
int n;
void init(int mid){for(int i=0;i<n;i++){l[i]=line(pp[i],pp[i]-pp[(i+mid+1)%n]);}}
//二分的mid，每隔mid个连一条线
bool halfcut(int mid){
	init(mid);
	sort(l,l+n);
	q[fi=la=0]=l[0];
	for(int i=1;i<n;i++){
		while(fi<la&&!onleft(l[i],p[la-1])) --la;
		while(fi<la&&!onleft(l[i],p[fi  ])) ++fi;
		q[++la]=l[i];
		if(fabs(cross(q[la].v,q[la-1].v))<eps){
			--la;if(onleft(q[la],l[i].p)) q[la]=l[i];
		}
		if(fi<la) p[la-1]=getlinecut(q[la],q[la-1]);
	}
	while(fi<la&&!onleft(q[fi],p[la-1])) --la;
	if(la-fi<=1) return 0;return 1;
}

int le,ri;
int main()
{
	while(scanf("%d",&n)==1&&n){
		for(int i=0;i<n;i++) pp[i].in();
		le=1,ri=n;
		while(le<=ri){
			int mid=(le+ri)>>1;
			if(halfcut(mid)) le=mid+1;
			else ri=mid-1;
		}
		printf("%d\n",le);
	}
	return 0;
}
```

---

