# [ICPC 2017 WF] Airport Construction

## 题目描述

热带岛国 Piconesia 以其美丽的海滩、郁郁葱葱的植被、可可和咖啡种植园以及全年宜人的天气而闻名。这个天堂般的地方正被考虑作为 ACM 国际大学生程序设计竞赛（ICPC）世界总决赛的未来举办地（或者至少是执行委员会的度假胜地）。只有一个小问题：这个岛屿真的很难到达。

目前，最快到达该岛的方法需要从最近的机场出发，历时三天，并结合使用渔船、油轮、皮划艇和潜艇。为了使参加 ICPC 世界总决赛稍微容易一些，并启动该岛的旅游业务，Piconesia 计划建造其第一个机场。

由于较长的跑道可以容纳更大的飞机，Piconesia 决定在他们的岛上建造尽可能长的跑道。不幸的是，他们无法确定这条跑道应该建在哪里。也许你可以帮忙？

对于这个问题，我们将 Piconesia 的边界建模为一个多边形。给定这个多边形，你需要计算可以在岛上建造的最长跑道（即直线段）的长度。跑道不得与海相交，但可以接触或沿着岛的边界。图 A.1 显示了与第一个样例输入对应的示例。

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14633/1.png)

图 A.1：将岛屿建模为多边形。最长的可能跑道显示为粗线。

## 说明/提示

时间限制：2 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7
0 20
40 0
40 20
70 50
50 70
30 50
0 50
```

### 输出

```
76.157731059
```

## 样例 #2

### 输入

```
3
0 2017
-2017 -2017
2017 0
```

### 输出

```
4510.149110617
```

# 题解

## 作者：constexpr (赞：5)

首先观察多边形内最长线段的性质：

![](https://s1.328888.xyz/2022/07/06/2BsE.png)
![](https://s1.328888.xyz/2022/07/06/25Gn.png)
![](https://s1.328888.xyz/2022/07/06/2GOw.png)

可以发现最长的线段至少经过多边形上的两点。考虑枚举两点。

但是线段的端点未必是枚举的两个点，并且不能保证线段完全在多边形内部。

先考虑线段端点的问题。可以以这两点间的线段为基础，向线段的两端扩展。

由于线段需要在多边形的内部，考虑求出这条线段所在直线与这个多边形的所有交点，并找出所有两端中至少一端为多边形外部的点，找到不在线段上离线段最近的两点即可。注意线段两端点也需要判断。

接下来需要验证线段是否完全在多边形内部。首先在扩展线段时向外延伸的部分是一定在多边形内部的。而判断线段原本的部分只需要判断这一部分存不存在两端中至少一端为多边形外部的点即可。

但是注意有一种特殊情况，如下图所示：

![](https://s1.328888.xyz/2022/07/06/2thB.png)

这种情况下，线段原本的部分没有多边形任何部分相交。

对于这一种情况，使用多边形的面积可以较为方便地判断。

具体来说，预处理出整个多边形的面积 $S$，设两点分别为 $i,j$，则计算出由点 $i$ 到点 $j$ 构成多边形的面积 $S_1$ 以及剩下的点和 $i,j$ 构成多边形的面积 $S_2$，判断 $S_1+S_2$ 是否等于 $S$ 即可。若相等，则线段在多边形内部。

接下来是一些代码细节上的处理问题：

求解直线与多边形交点时，需要特判直线与多边形的边平行的情况。

除此以外，交点可能恰好在多边形的点上，这种情况下需要分以下两种情况讨论。
  - 该点所在内角 $< 180\degree$，这种情况下直线一定会有一端在多边形外。
  - 该点所在内角 $\geq 180\degree$，这种情况下需要判断直线与角的位置关系。

对于上述第二种情况，观察下面两张图：

![](https://s1.328888.xyz/2022/07/06/2nh7.png)
![](https://s1.328888.xyz/2022/07/06/2AMk.png)

令端点为 $A$，与端点相邻的两个点为 $B,C$，直线的方向向量为 $\textbf{v}$，则直线穿过多边形边界的充要条件为 $\operatorname{sgn}(\overrightarrow{AB} \times \textbf{v}) \cdot \operatorname{sgn}(\textbf{v} \times \overrightarrow{AC}) \geq 0$。

枚举两端点需要 $O(n^2)$，对于每一条线段，需要 $O(n \log n)$ 的时间去处理，复杂度瓶颈在于对与多边形相交所有点的排序。总时间复杂度 $O(n^3 \log n)$。

代码：

```cpp
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <vector>
#define double long double
const int N=210;
const double inf=1e9,pi=acos(-1),eps=1e-7;
int n;
double ans,farea,l[N],r[N];
bool vis[N];
namespace basic{
	int res;char cdc;bool ng;
	template<typename T>T sq(T x){return x*x;}
	template<typename T>T rv(T x){return x>T()?x:(-x);}
	template<typename T>void cmin(T &x,T y){if(x>y)x=y;}
	template<typename T>void cmax(T &x,T y){if(x<y)x=y;}
	template<typename T>void swp(T &x,T &y){T z=x;x=y;y=z;}
	inline int read(){
		res=0,ng=false;
		for(;cdc<'0'||cdc>'9';cdc=getchar())ng|=cdc=='-';
		for(;!(cdc<'0'||cdc>'9');cdc=getchar())res=(res<<1)+(res<<3)+(cdc^48);
		return ng?~res+1:res;
	}
}using basic::sq;using basic::rv;using basic::cmin;using basic::cmax;using basic::swp;using basic::read;
struct cpx{
	double x,y;
	cpx():x(0),y(0){};
	cpx(double x,double y):x(x),y(y){};
	inline cpx operator-()const{return cpx(-x,-y);}
	inline cpx operator+(const cpx &nxt)const{return cpx(x+nxt.x,y+nxt.y);}
	inline cpx operator-(const cpx &nxt)const{return cpx(x-nxt.x,y-nxt.y);}
	inline cpx operator*(double w)const{return cpx(x*w,y*w);}
	inline cpx operator/(double w)const{return cpx(x/w,y/w);}
	inline double operator|(const cpx &nxt)const{return x*nxt.x+y*nxt.y;}
	inline double operator&(const cpx &nxt)const{return x*nxt.y-y*nxt.x;}
	inline bool operator<(const cpx &nxt)const{return x<nxt.x||(x==nxt.x&&y<nxt.y);}
	inline bool operator>(const cpx &nxt)const{return x>nxt.x||(x==nxt.x&&y>nxt.y);}
	inline double len()const{return sqrt(sq(x)+sq(y));}
	inline cpx bk()const{return *this/len();}
}crr[N];std::vector<cpx> vec;
struct line{
	cpx u,v;
	line(){};
	line(const cpx &u,const cpx &v):u(u),v(v){};
}lrr[N];
inline double area(const cpx &a,const cpx &b,const cpx &c){return ((b-a)&(c-a))/2;}
inline bool ponline(const cpx &a,const line &b){return rv((b.u-a)&(b.v-a))<eps;}
inline bool online(const cpx &a,const line &b){return ponline(a,b)&&((b.u-a)|(b.v-a))<-eps;}
inline double dist(const cpx &a,const line &b){return rv(area(a,b.u,b.v))*2/(b.u-b.v).len();}
inline cpx depart(const cpx &a,const cpx &b,double da,double db){return (a*db+b*da)/(da+db);}
inline cpx inter(const line &a,const line &b){return depart(a.u,a.v,area(a.u,b.u,b.v),area(a.v,b.v,b.u));}
double f(int i,int j){
	std::vector<cpx> vec;
	while(i!=j)vec.push_back(crr[i]),i=i==n?1:i+1;
	vec.push_back(crr[j]);int len=vec.size();double res=0;
	for(int p=0;p<len;++p)res+=(vec[p]&vec[(p+1)%len])/2;
	return rv(res);
}
void check(line c){
	vec.clear();cpx p,mn=cpx(-inf,-inf),mx=cpx(inf,inf);
	if(c.u>c.v)swp(c.u,c.v);
	for(int i=1;i<=n;++i){
		p=inter(c,lrr[i]);
		if(!online(p,lrr[i])||rv((lrr[i].v-lrr[i].u)&(c.v-c.u))<eps)continue;
		vec.push_back(p);
	}
	for(int i=1;i<=n;++i){
		if(!ponline(crr[i],c))continue;
		cpx a=crr[i==1?n:i-1],b=crr[i==n?1:i+1],t=crr[i];
		if(vis[i]||((a-t)&(c.u-c.v))*((c.u-c.v)&(b-t))>eps)vec.push_back(crr[i]);
	}
	for(cpx i:vec){
		if(!(i>c.u))cmax(mn,i);
		if(!(i<c.v))cmin(mx,i);
		if(i>c.u&&i<c.v)return;
	}
	cmax(ans,(mx-mn).len());
}
int main(){
	srand(time(NULL)),n=read();
	for(int x,y,i=1;i<=n;++i){
		x=read(),y=read();
		crr[i]=cpx(x,y);
	}
	farea=f(1,n);
	for(int i=1;i<=n;++i)lrr[i]=line(crr[i],crr[i==n?1:i+1]),vis[i]=((crr[i]-crr[i==1?n:i-1])&(crr[i==n?1:i+1]-crr[i]))>eps;
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			if(j!=i+1&&rv(f(i,j)+f(j,i)-farea)>eps)continue;
			check(line(crr[i],crr[j]));
		}
	}
	printf("%.9Lf",ans);
	return 0;
}
```


---

