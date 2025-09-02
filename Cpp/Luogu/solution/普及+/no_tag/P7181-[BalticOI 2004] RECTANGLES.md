# [BalticOI 2004] RECTANGLES

## 题目描述

平面上有 $n$ 个矩形。矩形边平行于坐标轴。这些长方形可以重叠、重合或相互分离。它们的顶点坐标 $(x,y)$ 中，$x,y$ 都是非负整数，横坐标不超过 $x_{\max}$，纵坐标不超过 $y_{\max}$。

$A$ 点位于 $(0,0)$，若 $C(x_{\max},0),D(0,y_{\max}),E(x_{\max},y_{\max})$，则 $B$ 点位于线段 $CE$ 或 $DE$ 上。

线段 $AB$ 可能与矩形相交（即使只与一个矩形**顶点**相交，也视为相交）。

你需要找到一个 $B$，使与线段 $AB$ 相交的矩形尽可能**多**。

## 说明/提示

#### 样例 1 说明

![](https://cdn.luogu.com.cn/upload/image_hosting/n987wmyr.png)

输出也可以为 `5 22 11`。

#### 数据规模与约定

对于 $100\%$ 的数据，有 $1\le n\le 10^4$，$0\le x_{\max},y_{\max}\le 10^9$。

#### 说明

译自 [BalticOI 2004 Day2 B RECTANGLES](https://boi.cses.fi/files/boi2004_day2.pdf)

#### 特别感谢

感谢 @[tiger2005](https://www.luogu.com.cn/user/60864) 提供的 SPJ！

## 样例 #1

### 输入

```
22 14 8
1 8 7 11
18 10 20 12
17 1 19 7
12 2 16 3
16 7 19 9
8 4 12 11
7 4 9 6
10 5 11 6```

### 输出

```
5 22 12```

# 题解

## 作者：KohaD_SEGA (赞：3)

这个题是波罗的海 $2004$ 年信息竞赛的题目，放到现在应该是一道普及 + 的题目。

我们来看看 $n=1$ 时的情形。例如， $x_{\mathrm{max}}=y_{\mathrm{max}}=11,$ 矩形左下角和右上角分别为 $(4,2),\ (5,7)$ 时，我们来直观地看一下哪些边界点是满足它和原点的连线与矩形相交的。

![](https://cdn.luogu.com.cn/upload/image_hosting/396evycc.png)

这意味着我们只需考虑矩形的左上顶点和右下顶点，将原点与此二顶点相连的射线与边界交于两点，这两点之间的边界点中的整点即为我们所求的 $n=1$ 时的点。

则题目变成：给定 $n$ 个区间，求一个整点，使得任何其他的点所被包括的区间数量均不大于该整点。这即是一道较低难度的模板题了。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct el // 区间
{
	int h;//区间的整点边界
	int tp;//是区间左界还是右界
}m[20001];//区间有两个界，所以是10000*2
struct ju//矩形
{
	int x_1;
	int y_1;
	int x_2;
	int y_2;
}mas[10001];
int len,pried;
int maxx,maxy,n;
inline bool cmp(el A,el B)//排序
{
	if(A.h==B.h)	return A.tp>B.tp;
	else return A.h<B.h;
}
#define QKSORT(l,r)	sort(m+(l),m+(r),cmp)
inline void add(int x,int y,int tp)
{
	double a;
	m[++len].tp=tp;
	if(x*1LL*maxy<=y*1LL*maxx)	m[len].h=maxy;//只考虑外边界矩形的某一边
	else
	{
		a=(long long)maxx*1LL*y;
		a=a*1.0/x;
		if(tp>0)	m[len].h=ceil(a-0.0001);//防止奇怪的浮点数出错
		else	m[len].h=floor(a+0.0001);
	}
}
int sum(int* x,int* y)
{
	int k,mx,mxh;
	len=0;
	for(int i=1;i<=n;i++)
	{
		if((long long)1LL*mas[i].x_1*maxy<1LL*mas[i].y_1*maxx)	continue;//它属于另外一边
		add(mas[i].x_1,mas[i].y_1,1);
		add(mas[i].x_2,mas[i].y_2,-1);
	}
	if(len>0)	QKSORT(1,len);
	k=0,mx=0,mxh=0;
	for(int i=1;i<=len;i++)
	{
		k+=m[i].tp;
		if(k>mx)	mx=k,mxh=m[i].h;
	}
	*x=maxx,*y=mxh;
	return mx;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>maxx>>maxy>>n;
	int tmp=0,i=1;
	for(int j=1;j<=n;j++)
	{
		cin>>mas[i].x_1>>mas[i].y_1>>mas[i].x_2>>mas[i].y_2;
		if(mas[i].x_1==0 && mas[i].y_1==0)
			pried++;
		else
		{
			swap(mas[i].x_1,mas[i].x_2);
			i++,tmp++;			
		}
	}
	n=tmp;
	int ats,ax=0,ay=0,bx=0,by=0;
	ats=sum(&ax,&ay);
	swap(maxx,maxy);//全部取反，考虑另一边
	for(int i=1;i<=n;i++)
	{
		swap(mas[i].x_1,mas[i].y_1);
		swap(mas[i].x_2,mas[i].y_2);
		swap(mas[i].x_1,mas[i].x_2);
		swap(mas[i].y_1,mas[i].y_2);
	}
	tmp=sum(&by,&bx);
	if(ats<tmp)	ats=tmp,ax=bx,ay=by;//合并两边，得到答案
	cout<<ats+pried<<' '<<ax<<' '<<ay<<endl;
	return 0;
}
```

---

## 作者：qiliu (赞：1)

## 思路

考虑一条从原点出发的直线什么时候与一个矩形相交，很显然只和一个矩形的左上角和右下角有关系。因为只考虑第一象限不用判断正负，所以其充要条件是这条直线的斜率需要比左上角点的斜率小，比右下角斜率大。所以我们以原点到一个矩形的左上角和右下角画直线重构这一张图，比如这一组样例。


```
20 20 3
2 12 10 20
8 10 10 16
10 3 15 15
```

画出来的图就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/qo5whtf3.png)

于是问题就变成了在 $y=y_{max}$ 和 $x=x_{max}$ 上找一个整点，使得其被最多对直线夹在中间。

## Code


```cpp
#include<bits/stdc++.h>
#define int long long
//#define DEBUG(x) cerr<<#x<<'='<<x<<endl
#define endl '\n'
using namespace std;
int rd(){
    char t=getchar();int f=1,x=0;
    while(t<'0'||t>'9'){ if(t=='-')f*=-1; t=getchar(); }
    while(t>='0'&&t<='9') x=x*10+t-'0',t=getchar();
    return x*f;
}void wt(int t){
    if(t<0)putchar('-'),t=-t;
    if(t>9)wt(t/10);
    putchar(t%10+'0');
    return;
}
const int N=2e4+100;
struct xyxy{
    double x,y;
    bool operator>(const xyxy &xx)const{return y*xx.x>x*xx.y;}//实际上就是   y/x > xx.y/xx.x   防止掉精度
    bool operator!=(const xyxy &xx)const{return y*xx.x!=x*xx.y;}
};
pair<xyxy,int>a[N];
int n;
bool cmp(pair<xyxy,int>xx,pair<xyxy,int>yy)
    {return xx.first!=yy.first?xx.first>yy.first:xx.second<yy.second;}
signed main(){
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    //cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    double xmax=rd(),ymax=rd();
    n=rd();int cnt=0;
    for(int i=1;i<=n;i++){
        xyxy tmpLU,tmpRD;//一个记录左上角坐标(left up)，一个记录右下角(right down)
        tmpLU.x=rd(),tmpRD.y=rd();
        tmpRD.x=rd(),tmpLU.y=rd();
        if(tmpLU.y==0)tmpLU.y=0.00001;
        if(tmpRD.x==0)tmpRD.x=0.00001;//防止除0爆RE
        a[++cnt].first=tmpLU,a[cnt].second=0;//0表示左上角
        a[++cnt].first=tmpRD,a[cnt].second=1;//1表示右下角
    }for(int i=1;i<=cnt;i++){//下面将y=y_{max}称之为矩形的上边，x=x_{max}为右边
        if(!a[i].second){//指左上角的点，表示一个矩形开始
            if(a[i].first.y*xmax>ymax*a[i].first.x) //斜率大于(x_{max},y_{max})为上边，下面第50行同理
                a[i].first=(xyxy){(int)ceil(ymax*a[i].first.x/a[i].first.y),ymax};//因为是整点，所以ceil一下取靠右的一个点
            else //斜率小于(x_{max},y_{max})为右边
                a[i].first=(xyxy){xmax,(int)floor(xmax*a[i].first.y/a[i].first.x)};//同上，取靠上的一个点
        }else{//右下角的点，和上面一个if相似，不做解释
            if(a[i].first.y*xmax>ymax*a[i].first.x) 
                a[i].first=(xyxy){(int)floor(ymax*a[i].first.x/a[i].first.y),ymax};
            else 
                a[i].first=(xyxy){xmax,(int)ceil(xmax*a[i].first.y/a[i].first.x)};
        }
    }sort(a+1,a+1+cnt,cmp);//记得排序
    int nowmax=0,ans_max=0;
    //nowmax：当前的点经过多少矩形
    //ans_max：最终经过多少矩形
    xyxy ans;
    for(int i=1;i<=cnt;i++){
        if(!(a[i].second&1)){
            nowmax++;
        }else nowmax--;
        if(nowmax>ans_max)ans=a[i].first,ans_max=nowmax;//显然答案点出现在一个区间里，我们只取头尾方便处理
    }wt(ans_max),putchar(' '),//别忘了加上cnt_zero
    wt(ans.x),putchar(' '),wt(ans.y);
    return 0;
}
```
---------

希望有帮到你

---

