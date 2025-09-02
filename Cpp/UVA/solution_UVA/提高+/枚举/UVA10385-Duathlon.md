# Duathlon

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1326

[PDF](https://uva.onlinejudge.org/external/103/p10385.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10385/945f9e56a0937fda8776dab247e1ddf0a30143a8.png)

## 样例 #1

### 输入

```
100
3
10.0 40.0
20.0 30.0
15.0 35.0
100
3
10.0 40.0
20.0 30.0
15.0 25.0```

### 输出

```
The cheater can win by 612 seconds with r = 14.29km and k = 85.71km.
The cheater cannot win.```

# 题解

## 作者：Diogenes (赞：3)

## 　　　　solution:铁人两项
### 数学表示方式
　　首先考虑先跑 $r$ 公里，然后骑行 $t-r$ 公里，怎样计算每个选手的耗时。假设第i个选手的跑步速度为 $run_i$ 公里/小时，骑行速度为 $cycle_i$ 公里/小时。那么，此选手跑完全程耗费的时间为：
				　　$$	time_i = \dfrac{r}{run_i} + \dfrac{(t - r)}{cycle_i}    $$
　　对r进行整理发现，$time_i()$ 是对r的线性函数。要最大化的是 $n-1$ 号选手的成绩与其他选手最好成绩的差距。把第 $n-1$ 号选手的成绩表示为 $cheater(r)$ ,其他选手的最好成绩表示为 $other(r)$ 时，这两个函数可以定义成如下形式。
$$ cheater(r) =  time_{n-1}(r) $$
$$ others(r) = \min\limits_{i=0}^{n-2}{time_i(r)} $$
　　期望求出的结果是 $others(r) - cheater(r)$ 的最大值。$cheater(r)$ 是线性函数，$others()$ 函数是几个线性函数的最小值，多画几幅图就能发现，$others()$ 是凹函数，凹函数 - 线性函数 得到凹函数。
 
　　**对凹函数进行三分即可。**
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define N 30
using namespace std;

double runSpeed[N],cycleSpeed[N];
int t,n;

//跑步距离为run时，第i个选手耗费的时间。 
double time(int i,double run) {
	double cycle=t-run;
	return run/runSpeed[i]+cycle/cycleSpeed[i];
}
//跑步距离为r时，返回others(r)-cheaters(r)的结果。
double diff(double r) {
	double cheater=time(n-1,r);
	double others=time(0,r);
	for(int i=1;i<n-1;i++) {
		others=min(others,time(i,r));
	}
	return others-cheater;
}
//三分法计算diff函数最大值 
double maxDifference() {
	double lo=0,hi=t;
	for(int i=0;i<200;i++) {
		double aab=(2*lo+hi)/3;
		double abb=(lo+2*hi)/3;
		if(diff(aab)>diff(abb)) hi=abb;
		else lo=aab;
	}
	return (lo+hi)/2;
}
int main()
{
//	freopen("duathlon.in","r",stdin);
//	freopen("duathlon.out","w",stdout);
	while(scanf("%d",&t)==1) {
		scanf("%d",&n);
		for(int i=0;i<n;i++) {
			scanf("%lf%lf",&runSpeed[i],&cycleSpeed[i]);
		}
		double ans=maxDifference();
		double judge=diff(ans);
		if(judge<0 && abs(judge)>1e-10) {
			printf("The cheater cannot win.\n");
		} else {
			printf("The cheater can win by %d seconds with r = %.2lfkm and k = %.2lfkm.\n",int(judge*3600+0.5),ans,t-ans);
		}
	}
	return 0;
}
```








---

## 作者：ZLightS (赞：1)

　　暴力，不多说，看程序吧。
  
　　还是bb几句，就是暴力枚举跑步的路程，因为精度，就只要x100就行。然后...死算...
  
  ~~最后，皮这一下我很开心!@[病名為愛](https://www.luogu.org/space/show?uid=12191)~~
  ```cpp
#include <bits/stdc++.h>
using namespace std;

double XCY,ZZW;
double ans,dis;
struct node{double x,y;}a[1000];
int t,n;

int main(){
    while (scanf("%d",&t)!=EOF){
        scanf("%d",&n);
        for (int i=1;i<=n;i++){
            scanf("%lf%lf",&a[i].x,&a[i].y);
            a[i].x/=3.6;a[i].y/=3.6; //换算
        }
        ans=-6324;
        for (int i=0;i<=t*100;i++){
            ZZW=666666666;
            for (int j=1;j<n;j++){
                double r=(double)(i*10)/a[j].x;
                double k=(double)(t*1000-i*10)/a[j].y;
                if (r+k<ZZW) ZZW=r+k;
            }  //暴力枚举
            double r=(double)(i*10)/a[n].x;
            double k=(double)(t*1000-i*10)/a[n].y;
            XCY=r+k;
            if (ZZW-XCY>ans) ans=ZZW-XCY,dis=i;
        }
        ans=trunc(ans+0.5);
        if (ans<0) printf("The cheater cannot win.\n");
        if (ans>=0) 
            printf("The cheater can win by %d seconds with r = %.2lfkm and k = %.2lfkm.\n",(int)ans,dis/100,(t*100-dis)/100);
    }
    return 0;
}
```

---

## 作者：Meickol (赞：0)

因为 $r+k=t$ 且 $t$ 已知。显然当 $r$ 确定时就能表示出 $k$，因为 $k=t-r$。

有了 $r,k$ 我们便能计算每个人完成的总用时。

用 $t_1$ 表示最后一位选手的总用时，然后依次枚举其他选手，用 $t_2$ 表示其他选手总用时。

每次枚举计算 $t_2-t_1$，用 $\text{ans}$ 记录 $t_2-t_1$ 的最小值。

显然当 $t_2-t_1<0$ 时无解。

本题思路就讲完了，因为要求其与第二名耗时之差的最大值，我们对 $r$ 三分求峰值即可。

```c++
#define rep(x,y,z) for(int x=y;x<=z;x++)
const int N=22;
const double eps=1e-15;
int n;
double t,v1[N],v2[N];
double calc(double r){
	double k=t-r;
	double ans=1e100;
	double t1=r/v1[n]+k/v2[n];
	rep(i,1,n-1){
		double t2=r/v1[i]+k/v2[i];
		ans=min(ans,t2-t1);
	}
	return ans;
}
void solve(){
	while(cin>>t){
		cin>>n;
		rep(i,1,n) cin>>v1[i]>>v2[i];
		double l=0,r=t;
		rep(i,1,100){
			double m1=l+(r-l)/3,m2=r-(r-l)/3;
			if(calc(m1)<calc(m2)) l=m1;
			else r=m2;
		}
		if(calc(l)<eps) printf("The cheater cannot win.\n");
		else printf("The cheater can win by %.0lf seconds with r = %.2lfkm and k = %.2lfkm.\n",calc(l)*3600,l,t-l);
	}
}
```

---

## 作者：Celtic (赞：0)

一道三分裸题。

题目链接[UVA10385 Duathlon](https://www.luogu.com.cn/problem/UVA10385)

首先设关于$r$的函数

$calc(r)=min\{r/run[i]+k/cycle[i],i∈[1,n-1]\}-r/run[n]+k/cycle[n]$

多画几幅图就能知道$calc(r)$为凸函数。

直接三分。

卡精度，我用的是三分次数的，$r-l>eps$这种没调出来。

最后附上我丑陋的代码。

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define eps 1e-20
#define re register
#define N 2001001
#define MAX 2001
#define PI acos(-1)
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
    ret=0;re ll pd=0;re char c=getchar();
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
    ret=pd?-ret:ret;
}
db run[N],cycle[N],t,ans2,ans3,tr;
ll n,ans1,ju;
inline db calc(re db r,re db k)
{
	re db cheater=r/run[n]+k/cycle[n],others=100000000000000.0;
	for(re int i=1;i<n;i++)
		if(r/run[i]+k/cycle[i]<others)others=r/run[i]+k/cycle[i];
	return others-cheater; 
}
inline void solve()
{
	re db l=0.0,r=t;
	re ll ts=300;
	while(ts--)
	{
		re db mid1=(r-l)/3+l,mid2=(r-l)/3*2+l;
		if(calc(mid1,t-mid1)-calc(mid2,t-mid2)>eps)
			r=mid2;
		else
			l=mid1;
	}
	ans2=l;
	ans3=t-ans2;
	tr=calc(ans2,t-ans2)*3600;
	ans1=ll(tr+0.5);
	ju=ll(tr);
}
int main()
{
	while(~scanf("%lf %lld",&t,&n))
	{
		for(re int i=1;i<=n;i++)
			scanf("%lf %lf",&run[i],&cycle[i]);
		solve();
		if(tr>eps)
			printf("The cheater can win by %lld seconds with r = %.2lfkm and k = %.2lfkm.\n",ans1,ans2,ans3);	
		else
			printf("The cheater cannot win.\n");
	}
    exit(0);
}
```




---

