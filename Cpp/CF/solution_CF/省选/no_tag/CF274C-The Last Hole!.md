# The Last Hole!

## 题目描述

Luyi has $ n $ circles on the plane. The $ i $ -th circle is centered at $ (x_{i},y_{i}) $ . At the time zero circles start to grow simultaneously. In other words, the radius of each circle at time $ t\ (t&gt;0) $ is equal to $ t $ . The circles are drawn as black discs on an infinite white plane. So at each moment the plane consists of several black and white regions. Note that the circles may overlap while growing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF274C/9b4e1ebb881bb05cb98067ff4ad19ee2f6db6140.png)We define a hole as a closed, connected white region. For instance, the figure contains two holes shown by red border. During growing some holes may be created and it is easy to see that each created hole will disappear eventually. Luyi asks you to find moment of time such that the last hole disappears. In other words, you should find the first moment such that no hole can be seen after that.

## 样例 #1

### 输入

```
3
0 0
1 1
2 2
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
4
0 0
0 2
2 2
2 0
```

### 输出

```
1.414214
```

## 样例 #3

### 输入

```
4
0 1
0 -1
-2 0
4 0
```

### 输出

```
2.125000
```

# 题解

## 作者：辰星凌 (赞：3)

# **【题解】The Last Hole! [CF274C]**

[$\mathcal{My}\ \mathcal{Blog}$](https://www.cnblogs.com/Xing-Ling/p/12455736.html)

传送门：[$\text{The Last Hole!}$](https://www.luogu.com.cn/problem/CF274C) [$\text{[CF274C]}$](http://codeforces.com/problemset/problem/274/C)

## **【题目描述】**

给出平面上 $n$ 个圆的圆心坐标，最开始它们的半径都是 $0$，然后所有圆同时开始扩大，在时刻 $t$ 时所有圆的半径均为 $t$ 。

假设这些黑色的圆被放在一个无穷大的白色平面上，每个时刻都存在一些黑色、白色连通块。随着圆的逐渐增大，越来越多的圆会相交。

定义一个白色的封闭区域为一个“洞”，求最后一个“洞”消失的时刻。如果没有“洞”则输出 $-1$。

答案精度差不能超过 $10^{-4}$ 。

## **【分析】**

[【计算几何全家桶】](https://www.luogu.com.cn/blog/ChenXingLing/post-xue-xi-bi-ji-ji-suan-ji-he-quan-jia-tong)

画个图感受一下，发现所有的♂洞♂都可以简化为两种情况：由 呈**锐角三角形**的三个圆 或者 呈**矩形**的四个圆 所生成（指圆心呈 XX 形状）。

可以直接 $O(n^3)$ 枚举包围圈，可知“洞”消失的部位一定是 外心/对角线交点。对于三角形取外接圆半径，对于矩形则取对角线长度一半，最后找最大值即为答案。

给出三角形顶点坐标不会求外接圆的，这里有个板子（输出有点鬼畜）：[$\text{Circle Through Three Points [UVA190]}$](https://www.luogu.com.cn/problem/UVA190)

但这样做的话在 $\text{test 6}$ 就会 $\text{WA}$ ：

```cpp
4
0 0
4 8
8 0
4 3
```

按照上述做法求出来答案为 $5$，而实际上三角形外心与另一个圆心 $(4,3)$ 重合了，也就是说根本就不会出现“洞”。

所以正确做法应该是把所以可能的“洞”的消失点储存下来，并计算它在选出来的包围圈中消失所需时间 $ti$ 。最后扫一遍所有圆，如果所有圆都没有在 $ti$ 之前覆盖掉这个点，那么 $ti$ 就是合法的。

时间复杂度为：$O(n^3+kn)$，其中 $k$ 为储存下来的可能消失点个数，由于不合法的较多，远达不到上界 $n^3$，可以轻松水过。

## **【Code】**

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
#define LD double
#define LL long long
#define Re register int
#define Vector Point
#define mp make_pair
#define S(a) ((a)*(a))
using namespace std;
const int N=103;
const LD eps=1e-10;
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}//处理精度
inline LD Abs(LD a){return a*dcmp(a);}//取绝对值
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Point{LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}};
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}//【点积】
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}//【叉积】
inline LD Len(Vector a){return sqrt(Dot(a,a));}//【模长】
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator*(Vector a,LD b){return Vector(a.x*b,a.y*b);}
inline bool operator==(Point a,Point b){return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y);}
struct Circle{Point O;LD r;Circle(Point P,LD R=0){O=P,r=R;}};
inline Circle getcircle(Point A,Point B,Point C){//三点确定一圆
    LD x1=A.x,y1=A.y,x2=B.x,y2=B.y,x3=C.x,y3=C.y;
    LD D=((S(x2)+S(y2)-S(x3)-S(y3))*(y1-y2)-(S(x1)+S(y1)-S(x2)-S(y2))*(y2-y3))/((x1-x2)*(y2-y3)-(x2-x3)*(y1-y2));
    LD E=(dcmp(y2-y1)!=0)?(S(x1)+S(y1)-S(x2)-S(y2)+D*(x1-x2))/(y2-y1):(S(x2)+S(y2)-S(x3)-S(y3)+D*(x2-x3))/(y3-y2);
    LD F=-(S(x1)+S(y1)+D*x1+E*y1);
    return Circle(Point(-D/2.0,-E/2.0),sqrt((S(D)+S(E)-4.0*F)/4.0));
}
inline int pan_PL_(Point p,Point a,Point b){//【判断点P是否在直线AB上】
    return !dcmp(Cro(p-a,b-a));//PA,AB共线
}
int n,cnt,X[N],Y[N];Point P[N],Q[N*N*N];LD ti[N*N*N];LD ans=-1;map<pair<int,int>,int>vis;
inline void sakura1(Point A,Point B,Point C){//处理三角形
    if(dcmp(Dot(A-B,C-B))<=0||dcmp(Dot(A-C,B-C))<=0||dcmp(Dot(B-A,C-A))<=0)return;//钝角三角形、直角三角形都不要
//    printf("(%.lf,%.lf) (%.lf,%.lf) (%.lf,%.lf)\n",A.x,A.y,B.x,B.y,C.x,C.y);
    Circle Cir=getcircle(A,B,C);Q[++cnt]=Cir.O,ti[cnt]=Cir.r;
}
inline void sakura2_(Re i,Re j,Re k){//假设i为左下角，j为左上角，k为右下角
    if(X[i]==X[j]&&Y[i]<Y[j]&&Y[i]==Y[k]&&X[i]<X[k]){
//        printf("(%d,%d) (%d,%d) (%d,%d)\n",X[i],Y[i],X[j],Y[j],X[k],Y[k]);
        if(vis[mp(X[k],Y[j])])Q[++cnt]=Point((X[i]+X[k])/2.0,(Y[i]+Y[j])/2.0),ti[cnt]=Len(P[j]-P[k])/2.0;
    }
}
inline void sakura2(Re i,Re j,Re k){//处理矩形
    sakura2_(i,j,k),sakura2_(j,i,k),sakura2_(k,i,j);//枚举6种i,j,k可能的组合,
    sakura2_(i,k,j),sakura2_(j,k,i),sakura2_(k,j,i);//最后需要的只有1种
}
int main(){
//    freopen("123.txt","r",stdin);
    in(n);
    for(Re i=1;i<=n;++i)in(X[i]),in(Y[i]),vis[mp(X[i],Y[i])]=1,P[i]=Point(X[i],Y[i]);
    for(Re i=1;i<=n;++i)//不重复的枚举i,j,k
        for(Re j=i+1;j<=n;++j)
            for(Re k=j+1;k<=n;++k)
                if(!pan_PL_(P[i],P[j],P[k]))//如果三点不共线
                    sakura1(P[i],P[j],P[k]),sakura2(i,j,k);
    for(Re i=1;i<=cnt;++i){
        Re flag=1;
        for(Re j=1;j<=n&&flag;++j)flag&=(dcmp(Len(Q[i]-P[j])-ti[i])>=0);//如果在ti[i]之前就被某个点覆盖了
        if(flag)ans=max(ans,ti[i]);
    }
    printf("%lf\n",ans);
}
```


---

