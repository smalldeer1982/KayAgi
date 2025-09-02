# Maximal Area Quadrilateral

## 题目描述

Iahub has drawn a set of $ n $ points in the cartesian plane which he calls "special points". A quadrilateral is a simple polygon without self-intersections with four sides (also called edges) and four vertices (also called corners). Please note that a quadrilateral doesn't have to be convex. A special quadrilateral is one which has all four vertices in the set of special points. Given the set of special points, please calculate the maximal area of a special quadrilateral.

## 说明/提示

In the test example we can choose first $ 4 $ points to be the vertices of the quadrilateral. They form a square by side $ 4 $ , so the area is $ 4·4=16 $ .

## 样例 #1

### 输入

```
5
0 0
0 4
4 0
4 4
2 3
```

### 输出

```
16.000000```

# 题解

## 作者：流绪 (赞：2)

求最大面积的四边形,考虑枚举对角线,然后再枚举一个点,算出左边,右边两个三角形的最大面积,最后取最大值即可,n 只有 300 ,n3 的暴力枚举可过

一些细节注释在代码里了

下面是AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	double x,y; 
}a[310];
double f(node a,node b,node c)
{
	double a1=b.x-a.x;
	double a2=c.x-b.x;
	double a3=b.y-a.y;
	double a4=c.y-b.y;
	return (a1*a4-a2*a3)/2; 
}		//算面积,可根据正负来判断是左边还是右边 
int main()
{
	int n;
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> a[i].x >> a[i].y;
	double ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)//枚举两个点表示对角线 
		{
			double ls=0,rs=0;
			for(int k=1;k<=n;k++)//枚举其他点构成三角形 
			{
				double s=f(a[i],a[j],a[k]);
				if(s>0&&s>ls)
					ls=s;
				else if(s<0&&-s>rs)
					rs=-s;		//记录最大三角形面积 
			}
			if(ls+rs>ans&&ls>0&&rs>0)
				ans = ls+rs;		//若能构成四边形,更新答案 
		}
	printf("%.6lf",ans);
}
```


---

## 作者：Jerry_heng (赞：1)

（一）

枚举对角线。

然后分别找正在对角线上方的点与对角线端点构成三角形面积的最大值。

和在对角线下方的点与对角线端点构成三角形面积的最大值。

如果所有点都在同侧，那么不算。

通过过两点直线的解析式求出另一点在直线的哪一侧。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define hyh double
using namespace std;
int n;
hyh ans;
struct node{
	hyh x,y;
}a[310];
bool pd(hyh x1,hyh y1,hyh x2,hyh y2,hyh x3,hyh y3){
	hyh k=(y2-y1)/(x2-x1),b=y1-k*x1;
	return x3*k+b<y3;
}
hyh s(hyh x1,hyh y1,hyh x2,hyh y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
hyh js(hyh x1,hyh y1,hyh x2,hyh y2,hyh x3,hyh y3){
	hyh a=s(x1,y1,x2,y2),b=s(x1,y1,x3,y3),c=s(x2,y2,x3,y3);
	hyh p=(a+b+c)/2;
	return sqrt(p*(p-a)*(p-b)*(p-c));
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++){
			hyh s1=0,s2=0;
			for(int k=1;k<=n;k++){
				if(k==i||k==j)continue;
				bool pos=pd(a[i].x,a[i].y,a[j].x,a[j].y,a[k].x,a[k].y);
				if(pos==0)s1=max(s1,js(a[i].x,a[i].y,a[j].x,a[j].y,a[k].x,a[k].y));
				else s2=max(s2,js(a[i].x,a[i].y,a[j].x,a[j].y,a[k].x,a[k].y));
			}
			if(s1==0||s2==0)continue;
			ans=max(ans,s1+s2);
		}
	printf("%.9lf",ans);
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
一道比较不错的计算几何题，可以拿这道题练通过复杂度推算法的题。
## 分析。
看到最大面积题，我们先考虑暴力枚举：选定一个点，去判断与任意三个点的组合围成的四边形的面积，然后打擂台，记录当前最大值，换下一个点，时间复杂度 $O\left(n^4\right)$ 此时 $400^4=\left(4\times100\right)^4=4^4\times10^8$ 显然没有办法在一秒的时间内解决。

考虑 $O\left(n^3\right)$ 的算法，此时 $400^3=4^3\times10^6$ 可以在一秒的时间内解决。我们不妨把它拆分，这样我们便于分析算法。首先我们肯定必须用 $O\left(n\right)$ 的复杂度来枚举每一个点，则我们发现剩下的 $O\left(n^2\right)$ 的复杂度可以枚举每一条相连的线段。这样就有算法了，我们不妨枚举线段，然后得到三角形，再用秦九昭公式算出这个三角形的面积。我们知道任意一个四边形都可以分成两个三角形，所以我们就可以用两个三角形的面积去凑出这个四边形的面积。此时我们不妨设一个一次函数，然后看这个三角形在这个直线的左侧还是右侧，然后粉笔统计出来，左侧和右侧最大值的加和就是当前四边形在固定当前线段后能取到的最大面积，最后在打擂台，就是答案。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
int n;
struct node{
	double x,y;
}a[305];
double ans,k2,b,s_now,s_left,s_right;
double dis(node x,node y){
	return sqrt(abs(x.x-y.x)*abs(x.x-y.x)+abs(x.y-y.y)*abs(x.y-y.y));
}
double S_qjz(node x,node y,node z){
    double a=dis(x,y),b=dis(y,z),c=dis(x,z);
    double p=(a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
    //秦九昭公式不多解释。 
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i].x>>a[i].y;
	}
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            s_left=s_right=0;//左右两个三角形的面积。
            //k2=10000;
            for(int k=1;k<=n;k++){
            	//k2=10000;
                if(k==i||k==j){
				    continue;
				}
				k2=10000;
                s_now=S_qjz(a[i],a[j],a[k]);//计算当前固定的线段能够组成三角形的面积。 
                if(a[i].y!=a[j].y){
				    k2=(a[i].y-a[j].y)/(a[i].x-a[j].x);
				}
				//cout<<k2<<"\n";
                b=a[i].y-a[i].x*k2;
                //cout<<b<<"  yep!\n";
                //这里就是一次函数y=k2x+b。 
                if(k2==10000){
                    if(a[k].y>a[i].y){
					    s_left=max(s_left,s_now);
					}
                    else s_right=max(s_right,s_now);
                } 
                else if(k2==0){
                    if(a[k].x<a[i].x){
					    s_left=max(s_left,s_now);
					}
                    else s_right=max(s_right,s_now);
                }//函数左右两边分别取最大值。 
                else{
                	if(k2<0){
                        if(a[k].y<k2*a[k].x+b){
						    s_left=max(s_left,s_now);
						}
                        else s_right=max(s_right,s_now);
                    }
                    else{
                        if(a[k].y>k2*a[k].x+b){
						    s_left=max(s_left,s_now);
						}
                        else s_right=max(s_right,s_now);
                    }
                }
            }
            if(s_left&&s_right){
			    ans=max(ans,s_left+s_right);
			}//相加的四边形面积打擂台。 
        }
    }
    printf("%.6lf\n",ans);
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

