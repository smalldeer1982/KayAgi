# [USACO12FEB] Symmetry G

## 题目描述

在上了一门现代艺术课后，Farmer John 对在农场周围寻找几何图案产生了兴趣。他仔细地绘制了他的 N 头奶牛的位置（2 <= N <= 1000），每头奶牛占据二维平面中的一个不同的点，他想知道这些点集有多少条不同的对称轴。当然，对称轴是指在这条线上，两侧的点是彼此的镜像。

请帮助 FJ 解答这个最紧迫的几何问题。




## 说明/提示

这 4 头奶牛形成一个正方形的四个角。

有 4 条对称轴——一条垂直的，一条水平的，以及两条对角线。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4 
0 0 
0 1 
1 0 
1 1 
```

### 输出

```
4 
```

# 题解

## 作者：jzzcjb (赞：7)

这大概是一道数学题？？反正觉得回到了初三。

首先 $n^3$ 很容易想，无非 $n^2$ 枚举两个点，$O(n)$ 判断。

不如来做个脑筋急转弯。一个数集里有几种数？两种，等于1的和不等于1的。

由此，所有对称轴有几种？两种,经过点1的和不经过点1的。

所以我们可以固定一个点 $1$ ，枚举一个点 $i$ 与 $1$ 配对。假设这两个点之间有一条对称轴，这两个点是关于这条对称轴的一对对称点。就可以求出这条对称轴的方程。再 $O(n)$ 判断，是不是对称轴。 

这样就可以找出所有不经过点 $1$ 的对称轴。因为假设有一条对称轴不经过点 $1$ ，既然它合法， $1$ 就一定有一个对称点。但是我们已经枚举了所有的点与 $1$ 配对，所以这样的对称轴是不存在的，即得证。

那经过点 $1$ 的对称轴又怎么办？可以再固定一个点 $2$ ，再求一遍。这次要求所有的对称轴合法的条件还要加上经过点 $1$ ，不然会算重。

这样就不重不漏的计算了所有不经过点 $1$ 的、经过点 $1$ 但不经过点 $2$ 的，所有可能的对称轴。还漏了经过点 $1$ 并且经过点 $2$ 的怎么办？两点确定一条直线，单独判断一下就可以了。

某神犇结论：思路很明了，实现很虐心

首先要手推一发数学结论，就不在这里证了。
```
两点(x1,y1)(x2,y2)求过两点直线Ax+By+C=0
  A=y2-y1 B=x1-x2 C=x2*y1-x1*y2 
  
两点(x1,y1)(x2,y2)求两点间的对称轴Ax+By+C=0
  A=x1-x2 B=y1-y2 C=-((x1+x2)(x1-x2)+(y1+y2)(y1-y2))/2
  
求(x',y')关于直线 Ax+By+C=0 的对称点(x0,y0) 
  设 k=-2*(A*x'+B*y'+C)/(A*A+B*B);
  x0=x'+k*A; 
  y0=y'+k*B;

```
$O(n)$ 判断的方法是枚举一个点，求出它的对称点，如果对称点的位置上有点，就继续；否则这条直线不合法；或者它的对称点根本没有落到整点上或超出了范围，也会不合法
。

因为坐标有负数，所以要把所有坐标整体加上1w。

要记每个位置是否有点，要开一个2w*2w的布尔数组，不知道为什么没有爆空间(大概靠信仰)。

另外，精度要开到1e-10所有。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#define eps 1e-10
using namespace std;
int n,cnt,x[100100],y[100100];
bool map[20001][20001];
bool dy(double x,double y){return ((x-y<=eps)||(y-x<=eps));}
bool is(double A,double B,double C){//判断某条直线是否是对称轴 
	for(int i=1;i<=n;i++){
		/*
    		求(x',y')关于直线 Ax+By+C=0 的对称点(x0,y0) 
    		设 k=-2*(A*x'+B*y'+C)/(A*A+B*B);
    		x0=x'+k*A;
    		y0=y'+k*B;
		*/
        double k=-2*(double)(A*x[i]+B*y[i]+C)/(A*A+B*B);
        double xo=x[i]+k*A;int x0=round(xo);
        double yo=y[i]+k*B;int y0=round(yo);
        if(!dy(x0,xo)||!dy(y0,yo)) return 0;//不是整点 
        if(x0>20000||y0>20000) return 0;//越界 
        if(!map[x0][y0]) return 0;
    }
    return 1;
}
bool check(int a,int b){//以两点为一对对称点 
    //A=x1-x2 B=y1-y2 C=-((x1+x2)(x1-x2)+(y1+y2)(y1-y2))/2
    double A=x[a]-x[b];
    double B=y[a]-y[b];
    double C=(double)-((x[a]*x[a]-x[b]*x[b])+(y[a]*y[a]-y[b]*y[b]))/2;
    if(a!=1&&A*x[1]+B*y[1]+C!=0) return 0;
    return is(A,B,C);
}
bool ok(int a,int b){//以两点所在直线为对称轴 
    //A=y2-y1 B=x1-x2 C=x2*y1-x1*y2
    int A=y[b]-y[a];
    int B=x[a]-x[b];
    int C=x[b]*y[a]-x[a]*y[b];
    return is(A,B,C);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>x[i]>>y[i],x[i]+=10000,y[i]+=10000,
    map[x[i]][y[i]]=1;
    for(int i=2;i<=n;i++) cnt+=check(1,i);
    for(int i=2;i<n;i++) cnt+=check(i,n);
    cout<<cnt+ok(1,n);
}
```

---

## 作者：wangjyqh (赞：3)

### 思路楼上已经说得是否详细了,我这里提供一下离散化
```
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXX=2010;
const double eps=1e-8;
int n,x[MAXX],y[MAXX],a[MAXX<<1];
int xx[MAXX*10],yy[MAXX*10];
int tot,ans;
bool MAP[MAXX][MAXX];
inline bool check(double a,double b){
    if(fabs(a-b)<=eps)return 1;
    else return 0;
}
inline void judge(int a,int b,double A,double B,double C){
    bool flag=0;
    for(int j=1;j<=n;++j){
          if(j==a||j==b)continue;
          double T=(A*(double)x[j]+B*(double)y[j]+C)/(A*A+B*B);
          double x0=x[j]-2.0*A*T;
          double xxx1=round(x0);
          int xxx2=round(x0);
          double y0=y[j]-2.0*B*T;
          double yyy1=round(y0);
          int yyy2=round(y0);
          if(!check(x0,xxx1)||!check(y0,yyy1)){
          	flag=1;
          	break;
          }
          if(xxx2>10000||xxx2<-10000||yyy2>10000||yyy2<-10000){
          	flag=1;
          	break;
          }
          if(!MAP[xx[xxx2+10000]][yy[yyy2+10000]]){
          	flag=1;
          	break;
          }
      }
      if(!flag)ans++;
}//检查对称轴是否合法
int main(){
   scanf("%d",&n);
   for(int i=1;i<=n;++i){
   	  scanf("%d%d",&x[i],&y[i]);
   	  a[++tot]=x[i];
   	  a[++tot]=y[i];
   }
   sort(a+1,a+tot+1);
   int m=unique(a+1,a+tot+1)-a-1;
   for(int i=1;i<=n;++i){
   	 xx[x[i]+10000]=lower_bound(a+1,a+m+1,x[i])-a;
   	 yy[y[i]+10000]=lower_bound(a+1,a+m+1,y[i])-a;
   	 MAP[xx[x[i]+10000]][yy[y[i]+10000]]=1;
   }
   for(int i=2;i<=n;++i){
   	  double x1=(double)x[1];
   	  double y1=(double)y[1];
   	  double x2=(double)x[i];
   	  double y2=(double)y[i];
      double A=x2-x1;
      double B=y2-y1;
      double C=0.5*((x1-x2)*(x1+x2)+(y1-y2)*(y1+y2));
      judge(1,i,A,B,C);
   }//ok
   for(int i=3;i<=n;++i){
      double x1=(double)x[2];
   	  double y1=(double)y[2];
   	  double x2=(double)x[i];
   	  double y2=(double)y[i];
      double A=x2-x1;
      double B=y2-y1;
      double C=0.5*((x1-x2)*(x1+x2)+(y1-y2)*(y1+y2));
      if(!check(A*x[1]+B*y[1]+C,0))continue;
      judge(2,i,A,B,C);
   }//ok
   double B=x[2]-x[1];
   double A=y[1]-y[2];
   double C=x[1]*y[2]-y[1]*x[2];
   judge(1,2,A,B,C);
   cout<<ans<<endl;
   return 0;
}
```

---

