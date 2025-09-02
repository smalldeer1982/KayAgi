# Space Rescuers

## 题目描述

The Galaxy contains $ n $ planets, there are many different living creatures inhabiting each planet. And each creature can get into troubles! Space rescuers know it perfectly well and they are always ready to help anyone who really needs help. All you need to do is call for them.

Now the space rescuers plan to build the largest in the history of the Galaxy rescue station; however, the rescue station's location is yet to be determined. As some cases are real emergencies, the rescuers want to find such a point in the Galaxy from which it would be possible to get to the remotest planet in the minimum possible time. In other words, the rescuers need such point in the space that the distance between it and the planet remotest from it was minimal (if we compare this point with all other possible points in the space). Unfortunately, the rescuers can't sole this problem.

As the planets are quite remote from each other, they can be considered as points in Euclidean three-dimensional space. The distance between points $ (x_{i},y_{i},z_{i}) $ and $ (x_{j},y_{j},z_{j}) $ can be calculated by the formula ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF106E/abb554e6cf2d19bd7b5533e0d45803da81f67e64.png). The rescue station can be positioned in any point in the space. It can also coincide with some planet.

Galaxy is in danger! Save the space rescuers and find the required point for them.

## 样例 #1

### 输入

```
5
5 0 0
-5 0 0
0 3 4
4 -3 0
2 2 -2
```

### 输出

```
0.000 0.000 0.000
```

# 题解

## 作者：C3H5ClO (赞：2)

对每一维坐标进行三分即可。

为什么这样正确呢？因为对每一维，答案都满足：某个点以前单增，以后单减（即三分的前提条件，单峰函数）。那么有一个结论：多个开口向上的单峰函数取max仍是开口向上的单峰函数。

假设依次确定x,y,z坐标。如果确定了x,y坐标，到点$P_i$的距离将是$f_i(z)=\sqrt{(x-p_i.x)^2+(y-p_i.y)^2+(z-p_i.z)^2}=\sqrt{(z-p_i.z)^2+C}$，是以$x=p_i.z$为对称轴的开口向上的单峰函数。求n个点中最大距离，即每个点距离取max，根据前文结论也是关于z的开口向上的单峰函数。这个结论可以扩展到对于三维空间内任意一条直线，产生的函数都是开口向上的单峰函数。

对每一维是开口向上的单峰函数，等价于定义域是三维空间点的开口向上的单峰函数，设其为$f$。显然，$f$有最小值没有最大值，不可能是开口向下的单峰函数。假设$f$存在多峰，取任意两个开口向上的顶点，将这两个顶点对应的三维空间内的点连线，连线上产生的是开口向上的单峰函数，与连线两端是顶点矛盾。因此，假设不成立，$f$是开口向上的单峰函数。

上代码！
```
#include<bits/stdc++.h>
using namespace std;
const int N=105,M=10000;
const double eps=1e-10,gold=(sqrt(5)-1)/2;
int n;
double ansx,ansy,ansz;
struct point{double x,y,z;}p[N];
inline double sqr(double x){return x*x;}
inline double getdis(point a,point b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)+sqr(a.z-b.z));}
inline double chkmax(double &x,double y){if(y>x)x=y;}
double fz(double x,double y,double z)
{
	double res=0; point a={x,y,z};
	for(int i=1;i<=n;i++)chkmax(res,getdis(a,p[i]));
	return res;
}
double fy(double x,double y)
{
	double l=-M,r=M,midl,midr;
	while(r-l>eps)
	{
		midr=l+(r-l)*gold; midl=l+r-midr;
		if(fz(x,y,midl)<fz(x,y,midr))r=midr;
		else l=midl;
	}
	return fz(x,y,l);
}
double fx(double x)
{
	double l=-M,r=M,midl,midr;
	while(r-l>eps)
	{
		midr=l+(r-l)*gold; midl=l+r-midr;
		if(fy(x,midl)<fy(x,midr))r=midr;
		else l=midl;
	}
	return fy(x,l);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].z);
	double l=-M,r=M,midl,midr;
	while(r-l>eps)
	{
		midr=l+(r-l)*gold; midl=l+r-midr;
		if(fx(midl)<fx(midr))r=midr;
		else l=midl;
	}
	ansx=l; l=-M; r=M;
	while(r-l>eps)
	{
		midr=l+(r-l)*gold; midl=l+r-midr;
		if(fy(ansx,midl)<fy(ansx,midr))r=midr;
		else l=midl;
	}
	ansy=l; l=-M; r=M;
	while(r-l>eps)
	{
		midr=l+(r-l)*gold; midl=l+r-midr;
		if(fz(ansx,ansy,midl)<fz(ansx,ansy,midr))r=midr;
		else l=midl;
	}
	ansz=l;
	printf("%.8lf %.8lf %.8lf",ansx,ansy,ansz);
}
```

---

## 作者：Shunpower (赞：1)

来一发 SA。

------------

看到这种题空间上取点距离题，考虑模拟退火。

退火怎么做就不赘述了，我们主要考虑怎么从旧解调整出比较优秀的新解，从而能够在降温过程结束之后得到最优解。

显然，为了让距离最远的点距离最小，我们应当每次把旧解往最远的点的方向拉一下。具体来说，记旧解向最远点的空间向量为 $\vec{v}$，我们对旧解直接加一个 $\lambda\vec{v}$。当然拉的幅度要随着降温减小，并且我们这个操作并不太需要让 $\lambda\geq 1$（挪到最远点甚至比最远点还远明显不太好）。所以可以直接设置一个较小的初始温度例如 $T=1$，退火过程直接让 $\lambda\gets T$。

啊如果不会向量的话，用人话就是每一维上都按照偏移量的 $\lambda$ 倍移动一下。

这样做每次意图取的新解就足够优秀了。设置一个非常小的阈值（注意要非常小，因为初温就很小）就能跑出答案。

至于为什么强调优秀的新解，因为这题你用随机偏移的烂退火是过不了的。

---------

似乎可以不写退火，爬个山就行了。如果非要退火注意 `Rand()` 的写法，随机区间取 $[-1,1]$ 比较合适。

这里取初温 $T=1$，降温系数 $d=0.9992$，终止温度 $T_k=10^{-10}$。实际上跑起来很快。

代码：

```cpp
int n;
ld x[N],y[N],z[N];
ld ansx,ansy,ansz;
ld Rand(){
    return ((ld)rand()/RAND_MAX)*2-1;
}
ld dis(pair<ld,ld> dx,pair<ld,ld> dy,pair<ld,ld> dz){
    return sqrt((dx.fi-dx.se)*(dx.fi-dx.se)+(dy.fi-dy.se)*(dy.fi-dy.se)+(dz.fi-dz.se)*(dz.fi-dz.se));
}
ld calc(ld nx,ld ny,ld nz){
    ld maxn=0;
    fr1(i,1,n) maxn=max(maxn,dis(mp(nx,x[i]),mp(ny,y[i]),mp(nz,z[i])));
    return maxn;
}
void SA(){
    ld T=1;
    ld nowx=ansx,nowy=ansy,nowz=ansz;
    while(T>=1e-10){
        ld maxn=0;
        int idx=0;
        fr1(i,1,n){
            ld d=dis(mp(nowx,x[i]),mp(nowy,y[i]),mp(nowz,z[i]));
            if(maxn<d) maxn=d,idx=i;
        }
        ld nxtx=nowx+T*(x[idx]-nowx),nxty=nowy+T*(y[idx]-nowy),nxtz=nowz+T*(z[idx]-nowz);
        ld delta=calc(nxtx,nxty,nxtz)-calc(nowx,nowy,nowz);
        if(delta<0) nowx=nxtx,nowy=nxty,nowz=nxtz;
        else if(exp(-delta/T)>Rand()) nowx=nxtx,nowy=nxty,nowz=nxtz;
        T*=0.9992;
    }
    cout.setf(ios::fixed);
    cout<<setprecision(6)<<nowx<<" "<<nowy<<" "<<nowz<<'\n';
    // cout<<setprecision(6)<<calc(nowx,nowy,nowz)<<'\n';
}
```

[AC Submission](https://codeforces.com/contest/106/submission/268997606)

---

