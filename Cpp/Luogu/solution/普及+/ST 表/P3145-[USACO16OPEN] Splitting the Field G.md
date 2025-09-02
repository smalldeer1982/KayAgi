# [USACO16OPEN] Splitting the Field G

## 题目描述

Farmer John 的 $N$ 头奶牛（$3 \leq N \leq 50,000$）位于他二维牧场的不同位置。FJ 想要用一个与 x 轴和 y 轴平行的矩形围栏将所有奶牛围住，并且他希望这个围栏尽可能小，以便它包含每一头奶牛（允许奶牛位于边界上）。

由于上季度牛奶产量低，FJ 的预算紧张。因此，他希望围住更小的区域以减少维护成本，而他唯一能想到的方法就是建造两个围栏而不是一个。请帮助他计算使用两个围栏而不是一个围栏总共可以减少多少面积。与原始围栏一样，这两个围栏必须共同包含所有奶牛（允许奶牛位于边界上），并且它们的边必须与 $x$ 轴和 $y$ 轴平行。这两个围栏不允许重叠——即使在它们的边界上也不行。注意，零面积的围栏是合法的，例如如果一个围栏的宽度和/或高度为零。

## 样例 #1

### 输入

```
6
4 2
8 10
1 1
9 12
14 7
2 3```

### 输出

```
107```

# 题解

## 作者：caddy (赞：7)

**排序+统计**

既然只允许建造两个栅栏。那么对于一个点，必然是以他为边界，沿x轴分成两个矩形，

或者沿y轴分出两个矩形

如图 ，沿A点划分

 ![](https://cdn.luogu.com.cn/upload/pic/10305.png) 

所以如果沿x轴分，要左边的面积，只需要预处理出左边y值的最大和最小值

右边同理。有个细节，再算右边的时候，不能包括该点本身

那么沿y轴分，算上方的面积也只需要预处理出该点上方x值的最大值和最小值。

下方同理

上代码

``` cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define max2(x,y) ((x>y)? x:y)
#define min2(x,y) ((x<y)? x:y)
using namespace std;
typedef struct aa{
    long long  x,y;
}node;
node a[50005],b[50005];
long long amaxyzuo[50005],aminyzuo[50005],aminyyou[50005],amaxyyou[50005];
long long bminxshang[50005],bmaxxshang[50005],bmaxxxia[50005],bminxxia[50005];
int n;
bool cmp1(node a,node b)
{
    return a.x<b.x;
}
bool cmp2(node a,node b)
{
    return a.y<b.y;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld %lld",&a[i].x,&a[i].y);
        b[i].x=a[i].x,b[i].y=a[i].y;
    }
    sort(a+1,a+1+n,cmp1);
    sort(b+1,b+1+n,cmp2);
    aminyzuo[0]=bminxxia[0]=0x7fffffff;
    for(int i=1;i<=n;i++)
    aminyzuo[i]=min2(aminyzuo[i-1],a[i].y),amaxyzuo[i]=max2(amaxyzuo[i-1],a[i].y),
    bminxxia[i]=min2(bminxxia[i-1],b[i].x),bmaxxxia[i]=max2(bmaxxxia[i-1],b[i].x);
    aminyyou[n+1]=bminxshang[n+1]=0x7fffffffffff;
    for(int i=n;i>=1;i--)
    aminyyou[i]=min2(a[i].y,aminyyou[i+1]),amaxyyou[i]=max2(a[i].y,amaxyyou[i+1]),
    bminxshang[i]=min2(b[i].x,bminxshang[i+1]),bmaxxshang[i]=max2(b[i].x,bmaxxshang[i+1]);//递推预处理最大与最小值
    long long  el=a[n].x,wl=a[1].x,nl=b[n].y,sl=b[1].y;
    long long ans=(nl-sl)*(el-wl);
    long long tans=0x7fffffffffffffff;
    for(int i=1;i<n;i++)
    {
        long long  ta=(a[i].x-wl)*(amaxyzuo[i]-aminyzuo[i]);//横着分的面积
        ta+=(el-a[i+1].x)*(amaxyyou[i+1]-aminyyou[i+1]);
        long long  tb=(nl-b[i].y)*(bmaxxshang[i]-bminxshang[i]);//竖着分的面积
        tb+=(b[i-1].y-sl)*(bmaxxxia[i-1]-bminxxia[i-1]);
        tans=min2(ta,tans);
        tans=min2(tans,tb);
    }
    printf("%lld",ans-tans);
}
```

---

## 作者：Outer_Horizon (赞：7)

**前言:**

本蒟蒻第一篇题解，存在问题的的地方还请各位多多包涵、指出。

# 核心思路
本题可以简化成在网格图中有 $n$ 个点，让你圈出 $2$ 个矩形，使得这 $2$ 个矩形面积最小。

### 1.建立矩阵

题目中指出所有坐标都是正数，于是我们可以 $(0,0)$ 为锚点，从远到近将所有的点排序。再从第一个点开始枚举，将点的序列分为前后两部分。

$$ ans_{i} = S_{1, i} + S_{i + 1, n} $$

这样分可以将所有的点分成离锚点较近的和距离锚点较远的点，易证没有更优的分法。

### 2.求矩形面积

通过观察，我们可以发现矩形的长就是这些点中**最大的 $x$ 的值**减去**最小的 $x$ 的值**，宽是这些点中**最大的 $y$ 的值**减去**最小的 $y$ 的值**。

那我们的问题可以转化成**区间内求最值**。

数据范围是 $ 1 \le n \le 50000 $。

我们要枚举每一个点，找到每一个点的最大和最小的 $x$ 和 $y$ 的值，所以需要对查找操作进行优化。这里推荐使用 RMQ 。不懂戳这儿 [RMQ 简单介绍](https://www.cnblogs.com/KonjakLAF/p/13488957.html)。

**注意事项:**
1. 我们应该将 $x$,$y$ 分别排序，取最小值(只对 $x$ 排序 $80$ 分)。
2. 不开 long long 见祖宗。
3. RMQ 要设置初始值。
4. 求出 ans 后要用整个矩形的面积减去 ans。

## 代码如下:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
/*
fx[i][j][0] 代表 i - j 区间内 x 的最小值
fx[i][j][1] 代表 i - j 区间内 x 的最大值
fy[i][j][0] 代表 i - j 区间内 y 的最小值
fy[i][j][1] 代表 i - j 区间内 y 的最大值
*/
int n, fx[50001][31][2], fy[50001][30][2], ans = 1e20, t, lx, ly, rx, ry;
struct cow{  //牛的位置
	int x, y;
}a[50001];
bool cmp1(cow a, cow b){  // 以 x 的远近排序
	return a.x < b.x;
}
bool cmp2(cow a, cow b){  // 以 y 的远近排序
	return a.y < b.y;
}
inline int read(){  // 读入优化
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){ if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*f;
}
void rmq(){
    // 初始化
	for (int i = 0; i <= n; i++){
		for (int j = 0; j <= 30; j++){
			fx[i][j][0] = fy[i][j][0] = 1e20;
		}
	}
	for (int i = 1; i <= n; i++) fx[i][0][0] = fx[i][0][1] = a[i].x, fy[i][0][0] = fy[i][0][1] = a[i].y;

	for (int j = 1; j <= 30; j++){
		for (int i = 1; i + (1 << j) - 1 <= n; i++){
			fx[i][j][0] = min(fx[i][j - 1][0], fx[i + (1 << j - 1)][j - 1][0]);
			fx[i][j][1] = max(fx[i][j - 1][1], fx[i + (1 << j - 1)][j - 1][1]);
			fy[i][j][0] = min(fy[i][j - 1][0], fy[i + (1 << j - 1)][j - 1][0]);
			fy[i][j][1] = max(fy[i][j - 1][1], fy[i + (1 << j - 1)][j - 1][1]);
		}
	}
}
int find(int l, int r){  // l - r 区间内的面积
	t = log2(r - l + 1);
	lx = max(fx[l][t][1], fx[r - (1 << t) + 1][t][1]);
	rx = min(fx[l][t][0], fx[r - (1 << t) + 1][t][0]);
	ly = max(fy[l][t][1], fy[r - (1 << t) + 1][t][1]);
	ry = min(fy[l][t][0], fy[r - (1 << t) + 1][t][0]);
	return (lx - rx) * (ly - ry);
}
signed main() {
	n = read();
	for (int i = 1; i <= n; i++) a[i].x = read(), a[i].y = read();
    // x 
	sort(a + 1, a + 1 + n, cmp1);
	rmq();
	for (int i = 1; i < n; i++){
		int k = find(1, i), q = find(i + 1, n);
		ans = min(ans, k + q);
	}
    // y
	sort(a + 1, a + 1 + n, cmp2);
	rmq();
	for (int i = 1; i < n; i++){
		int k = find(1, i), q = find(i + 1, n);
		ans = min(ans, k + q);
	}

	cout << find(1, n) - ans;  // 输出答案，大面积减去小面积
	return 0;
}
```

---

## 作者：Hoks (赞：4)

**前言** 蒟蒻的第一篇题解，有些地方没讲好积极接受改进建议。（个人博客内食用味道更佳！）（~~废话一堆请见谅~~）

[传送门](https://www.luogu.com.cn/blog/Hok/solution-p3145)

------------

# **核心思想** **ST 表大法好**

------------

**何为 RMQ**（学过的大佬可以自行跳过，蒟蒻的算法普及。）

可能有的同学并不知道什么是 RMQ，所以我来略微科普一下。

~~可以参考这个[百度百科链接](https://baike.baidu.com/item/rmq/1797559?fr=aladdin)~~

RMQ 是区间最值查询的算法，类似于线段树（~~我居然没学过~~），时间效率最大可以跑过 $n=4000000$ 左右的情况。

RMQ 的思想就是将两个**等长**的区间合并（长度都为 $2$ 的幂次方），合并为一个长度为原来的 $2$ 倍的区间，从而比起暴力枚举提高效率，将本为 $n$ 的时间复杂度缩减到 $\log_2(n)$ 。

可能大家没听懂，所以我举个栗子：求 $1$ 到 $n$ 中任意区间的最大值。
```cpp
//f[i][j]表示从i开始向下数1<<j位的最大值
for(int i=1;i<=n;i++) a[i]=read(),f[i][0]=a[i];//初始化f数组
for(int j=1;j<=16;j++)//注意，j在前面
	for(int i=1;i<=n-(1<<j)+1;i++)
		f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
```
这个时候可能有同学就要问了：我的区间长度都是 $2$ 的幂次方的，如何去查找长度不为 $2$ 的幂次方的区间呢？

这个很好解决，**只需要找两个区间将这个区间全部覆盖就可以了**。（可以相交。）

```cpp
while(m--)//m表示询问个数
{
    int x=read(),y=read(),z=log2(y-x+1);//x，y表示区间两端，z是其中最大j的值
    cout<<max(f[x][z],f[y-(1<<z)+1][z])<<endl;
    //用x到x+（1<<z）-1以及y-(1<<z)+1到y这两个区间覆盖它即可求出最大值
}
```

如[P1440](https://www.luogu.com.cn/problem/P1440)就是 RMQ 中的典型，可以先练习一下再做本题。

对于本题而言，矩形框架的长和宽就是横坐标以及纵坐标最大值与最小值的差。那我们就可以用上非常方便的 RMQ 的模板去快速寻找任意区间的极值，从而快速求出矩形面积，方便枚举。
```cpp
for(int i=1;i<=n;i++) f[i][0][0][0]=f[i][0][0][1]=e[i].x,f[i][0][1][0]=f[i][0][1][1]=e[i].y;
for(int i=0;i<=n;i++)
	for(int j=1;j<=16;j++)
		f[i][j][1][1]=f[i][j][0][1]=0x3f3f3f3f3f3f3f3f;
for(int j=1;j<=16;j++)
	for(int i=0;i<=n-(1<<j)+1;i++)
		f[i][j][0][0]=max(f[i][j-1][0][0],f[i+(1<<j-1)][j-1][0][0]),f[i][j][0][1]=min(f[i][j-1][0][1],f[i+(1<<j-1)][j-1][0][1]),
		f[i][j][1][0]=max(f[i][j-1][1][0],f[i+(1<<j-1)][j-1][1][0]),f[i][j][1][1]=min(f[i][j-1][1][1],f[i+(1<<j-1)][j-1][1][1]);
//f[i][j]后面的第一个维度表示 横坐标 或 纵坐标 ，第二个维度表示 最大值 或 最小值
```


------------

**回归正题**

有了 RMQ 的加持，本题就简单多了，我们只需要先给点按照横坐标排序一次，暴力枚举求最小面积，接着是纵坐标也来一次就 OK 了。

（求最小值的时候不要忘了初始化！）

AC 代码奉上：

```cpp
#include<bits/stdc++.h>
#define int long long//让你打代码更丝滑并且不会见祖宗的神器
using namespace std;
struct node
{int x,y;}e[50010];
int n;
int f[65537][17][2][2];
int ans=0x3f3f3f3f3f3f3f3f;
int x,y,x2=0x3f3f3f3f3f3f3f3f,y2=0x3f3f3f3f3f3f3f3f;
int read()//个人习惯快读
{
   char c=getchar();int x=0;
   while(!isdigit(c)) getchar();
   while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
   return x;
}
void cz()
{
   for(int i=1;i<=n;i++) 
      f[i][0][0][0]=f[i][0][0][1]=e[i].x,
      f[i][0][1][0]=f[i][0][1][1]=e[i].y;
   for(int i=0;i<=n;i++)
      for(int j=1;j<=16;j++)
         f[i][j][1][1]=f[i][j][0][1]=0x3f3f3f3f3f3f3f3f;
   for(int j=1;j<=16;j++)
      for(int i=0;i<=n-(1<<j)+1;i++)
         f[i][j][0][0]=max(f[i][j-1][0][0],f[i+(1<<j-1)][j-1][0][0]),
         f[i][j][0][1]=min(f[i][j-1][0][1],f[i+(1<<j-1)][j-1][0][1]),
         f[i][j][1][0]=max(f[i][j-1][1][0],f[i+(1<<j-1)][j-1][1][0]),
         f[i][j][1][1]=min(f[i][j-1][1][1],f[i+(1<<j-1)][j-1][1][1]);
   for(int i=1;i<n;i++) 
   {
      int k=log2(i),maxx1,minn1,maxx2,minn2,num;//计算第一个四边形
      maxx1=max(f[1][k][0][0],f[i-(1<<k)+1][k][0][0]);
      maxx2=max(f[1][k][1][0],f[i-(1<<k)+1][k][1][0]);
      minn1=min(f[1][k][0][1],f[i-(1<<k)+1][k][0][1]);
      minn2=min(f[1][k][1][1],f[i-(1<<k)+1][k][1][1]);
      num=(maxx1-minn1)*(maxx2-minn2);	
      k=log2(n-i);//第二个
      maxx1=max(f[i+1][k][0][0],f[n-(1<<k)+1][k][0][0]);
      maxx2=max(f[i+1][k][1][0],f[n-(1<<k)+1][k][1][0]);
      minn1=min(f[i+1][k][0][1],f[n-(1<<k)+1][k][0][1]);
      minn2=min(f[i+1][k][1][1],f[n-(1<<k)+1][k][1][1]);
      ans=min(ans,num+(maxx1-minn1)*(maxx2-minn2));
   }
}
bool cmpx(node x,node y){return x.x<y.x;}
bool cmpy(node x,node y){return x.y<y.y;}
signed main()
{
   n=read();
   for(int i=1;i<=n;i++) 
      e[i].x=read(),e[i].y=read(),
      x=max(x,e[i].x),y=max(y,e[i].y),
      x2=min(x2,e[i].x),y2=min(y2,e[i].y);
   sort(e+1,e+1+n,cmpx);
   cz();
   sort(e+1,e+1+n,cmpy);
   cz();
   cout<<(x-x2)*(y-y2)-ans;
   return 0;
}
```
~~完结撒花！！！~~

---

## 作者：曹老师 (赞：3)

**知识点：模拟 暴力**

~~我第一次没读懂题意！~~

一个围栏好处理：求出所有点的横纵坐标的最大最小值即可求

**两个围栏：上下分 或 左右分**

对于每一个点用数组存改点上下左右的区域中点的最大最小值

于是我们就得到两个矩形 求出面积相加即为两个围栏面积

(注：long long ~~和 -INF有负号~~

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=50005;
LL int n,x[L],y[L],xmin=INF,xmax=-INF,ymin=INF,ymax=-INF;
LL int max1[L],max2[L],max3[L],max4[L],min1[L],min2[L],min3[L],min4[L];
LL int area1,area2=INF,rank[L];
bool cmp1(int a,int b)
{
	return (x[a]==x[b])?y[a]<y[b]:x[a]<x[b];
}
bool cmp2(int a,int b)
{
	return (y[a]==y[b])?x[a]<x[b]:y[a]<y[b];
}
int main()
{
	scanf("%lld",&n);
	
	/*以下为输入和处理一个围栏的部分*/ 
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&x[i],&y[i]);
		xmin=min(xmin,x[i]);
		xmax=max(xmax,x[i]);
		ymin=min(ymin,y[i]);
		ymax=max(ymax,y[i]);
		rank[i]=i;
	}
	area1=(ymax-ymin)*(xmax-xmin);
	/*输入和一个围栏部分处理完毕*/
	
	/*以下是处理左右分的部分*/
	area2=area1;
	sort(rank+1,rank+n+1,cmp2);
	memset(min2,0x3f,sizeof(min2));
	memset(max2,-0x3f,sizeof(max2));
	memset(min4,0x3f,sizeof(min4));
	memset(max4,-0x3f,sizeof(max4));
	for(int i=1;i<=n;i++)
	{
		min2[i]=min(min2[i],min(min2[i-1],x[rank[i]]));
		max2[i]=max(max2[i],max(max2[i-1],x[rank[i]]));
	}
	for(int i=n;i>=1;i--)
	{
		min4[i]=min(min4[i],min(min4[i+1],x[rank[i]]));
		max4[i]=max(max4[i],max(max4[i+1],x[rank[i]]));		
	}
	for(int i=2;i<=n;i++)
		area2=min(area2,(LL)(y[rank[i-1]]-y[rank[1]])*(LL)(max2[i-1]-min2[i-1])+(LL)(y[rank[n]]-y[rank[i]])*(LL)(max4[i]-min4[i]));
	/*左右分处理完毕*/ 
	
	/*以下是处理上下分的部分*/ 
    sort(rank+1,rank+n+1,cmp1);
	memset(min1,0x3f,sizeof(min1));
	memset(max1,-0x3f,sizeof(max1));
	memset(min3,0x3f,sizeof(min3));
	memset(max3,-0x3f,sizeof(max3));
	for(int i=1;i<=n;i++)
	{
		min1[i]=min(min1[i],min(min1[i-1],y[rank[i]]));
		max1[i]=max(max1[i],max(max1[i-1],y[rank[i]]));
	}
	for(int i=n;i>=1;i--)
	{
		min3[i]=min(min3[i],min(min3[i+1],y[rank[i]]));
		max3[i]=max(max3[i],max(max3[i+1],y[rank[i]]));	
	}
	for(int i=2;i<=n;i++)
		area2=min(area2,(LL)(x[rank[i-1]]-x[rank[1]])*(LL)(max1[i-1]-min1[i-1])+(LL)(x[rank[n]]-x[rank[i]])*(LL)(max3[i]-min3[i]));
	/*上下分处理完毕*/ 
	
	printf("%lld",area1-area2);
	return 0;
}
```

---

## 作者：Starria的脑残粉 (赞：3)

这个是用栈的代码

优点：代码比较短

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,l[1000000],r[1000000],dd,kk,z[1000000],d,ans;
struct lsg{int l,r;}a[1000000];
bool pd(lsg x,lsg y){return x.l<y.l;}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;for (int i=1;i<=n;i++){
        cin>>x;if (x==0){dd=i;continue;}
        if (l[x]){
            r[x]=i;dd=r[x];//找到含有一个元素最左边的和最右边的地方
        }else l[x]=r[x]=i;
    }for (int i=1;i<=n;i++)
        if (l[i])a[++kk].l=l[i],a[kk].r=r[i];
    sort(a+1,a+1+kk,pd);for (int i=1;i<=kk;i++){
        while (a[i].l>a[z[d]].r&&d!=0)d--;
        if (a[i].r>a[z[d]].r&&d!=0){cout<<-1<<endl;return 0;}//处理区间相交情况
        z[++d]=i;ans=max(ans,d);
    }cout<<ans<<endl;
}
```

---

## 作者：kardsOI (赞：2)

~~闲话，感觉这题作为蓝题真的有点水。~~

### 题目大意

![](https://s3.bmp.ovh/imgs/2024/10/25/65bfccc205d4ebd4.png)

给定一个二维平面中 $n$ 个点的坐标（如上图），先用一个最小的矩形将它们全部围起来（点可以在矩形边界），记此矩形面积为 $S_1$，再用两个边界不能重合的矩形一起将所有点全部围起来，记其面积为 $S_2$ 与 $S_3$，要求 $S_1-(S_2+S_3)$ 的最小值。

### 求将某些点全围起来的最小矩形面积的方法

![](https://s3.bmp.ovh/imgs/2024/10/25/db22b727dabb12ae.png)

如上图所示，我们只需要通过暴力枚举所有应该被包含的点得出它们中间最小与最大的 $x$ 和 $y$ 坐标，即可得出最小矩形的长和宽，最后就可以求出面积，然后一个最小矩形的面积 $S_1$ 就求完了。

求出了 $S_1$，还有两个最小矩形的面积 $S_2+S_3$ 待求。因为求的是 $S_1$ 与 $S_2+S_3$ 的差的最大值，则显然要求这两个小矩形的最小面积和。

### 两个不相交的矩形最小面积和的求法

要先知道的是，如何划分出两个矩形？

我们可以先想象一条平行于 $y$ 轴的线在图上扫过，$x$ 轴左侧和轴上的点全部划分在一个矩形里，右侧的划分在另一个矩形里，如下图所示。

![](https://s3.bmp.ovh/imgs/2024/10/25/358b0a238f871ad0.png)

求出每次扫描得出的两个矩形面积和，更新最小值。

然后再进行一次相似的“扫描”操作，不过用的是一条平行于 $x$ 轴的线，线中间和上面的点划分在一个矩形里，下面的划分在另一个矩形里，如下图所示。

![](https://s3.bmp.ovh/imgs/2024/10/25/d874befabfc2ff53.png)

再拿每次的面积和更新最小值。

不难证明，在满足题目的要求情况下没有别的划分两个矩形的方法，则最后的最小值即为我们所需的 $S_2+S_3$。然后再输出 $S_1-(S_2+S_3)$，大功告成！

### 优化+注意事项

因为给出的坐标 $x_i$，$y_i \le 10^9$，所以按照 $x$ 或 $y$ 坐标来从 $0$ 枚举到 $10^9$ 的话稳稳的超时。

在简化时，我们不妨先以 $x$ 坐标为第一关键词，$y$ 坐标为第二关键词从小到大排序。再枚举将 $x$ 坐标相同的各自归组，并求出每组的最大与最小 $y$ 坐标和枚举到这组为止经历过的最大与最小 $y$ 坐标。然后扫描时从右到左按组扫描，不断更新扫描过的最大与最小 $y$ 坐标，而左侧的图形最大与最小 $y$ 坐标是提前处理好的，所以这就很容易求出两个矩形面积之和了，顺便还能得出一个最小矩形的面积 $S_1$。

竖向扫描时也进行相似的排序操作，不过 $x$ 与 $y$ 的操作倒过来。这样代码的时间复杂度为 $n$，时间剩余绰绰有余。

注意：

1. 数据较大，不开长整见祖宗。
2. 计算中可能涉及的变量较多，别被绕晕了。

### 满分代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int xyn,xymax[50100],xymin[50100],xyx[50100];
int yxn,yxmax[50100],yxmin[50100],yxy[50100];
int xya[50100],xyi[50100],yxa[50100],yxi[50100];
long long result1,result2,t1,t2,t3,t4,t5,t6,t7,t8;
struct zuobiao
{
    int xx,yy;
}ax[50100];
bool cmp2(zuobiao ta,zuobiao tb)
{
    return (ta.yy<tb.yy)||(ta.yy==tb.yy&&ta.xx<tb.xx);
}
bool cmp1(zuobiao ta,zuobiao tb)
{
    return (ta.xx<tb.xx)||(ta.xx==tb.xx&&ta.yy<tb.yy);
}
int main()
{
	//freopen("1.txt","r",stdin);
    scanf("%d",&n);
    memset(xyi,0x3f,sizeof(xyi));
    memset(yxi,0x3f,sizeof(yxi));
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&ax[i].xx,&ax[i].yy);
    }
    sort(ax+1,ax+n+1,cmp1);
    for(int i=1;i<=n;i++)
    {
        if(ax[i].xx!=ax[i-1].xx)
        {
            if(i!=1)
            {
                xymax[xyn]=ax[i-1].yy;
                xya[xyn]=max(xymax[xyn],xya[xyn-1]);
                xyi[xyn]=min(xymin[xyn],xyi[xyn-1]);
            }
            xyn++;
            xyx[xyn]=ax[i].xx;
            xymin[xyn]=ax[i].yy;
        }
    }
    xymax[xyn]=ax[n].yy;
    xya[xyn]=max(xymax[xyn],xya[xyn-1]);
    xyi[xyn]=min(xymin[xyn],xyi[xyn-1]);
    t1=xyx[1],t2=xyx[xyn],t3=xya[xyn],t4=xyi[xyn];
    result1=(t2-t1)*(t3-t4);
    result2=result1;
    t1=xyx[xyn];
    t8=xyx[1];
    t4=xymin[xyn];
    for(int i=xyn;i>=1;i--)
    {
        t2=xyx[i];
        if(xymax[i]>t3) t3=xymax[i];
        if(xymin[i]<t4) t4=xymin[i];
        t5=xyx[i-1];
        t6=xya[i-1];
        t7=xyi[i-1];
        result2=min(result2,(t5-t8)*(t6-t7)+(t3-t4)*(t1-t2));
    }
    sort(ax+1,ax+n+1,cmp2);
    for(int i=1;i<=n;i++)
    {
        if(ax[i].yy!=ax[i-1].yy)
        {
            if(i!=1)
            {
                yxmax[yxn]=ax[i-1].xx;
                yxa[yxn]=max(yxmax[yxn],yxa[yxn-1]);
                yxi[yxn]=min(yxmin[yxn],yxi[yxn-1]);
            }
            yxn++;
            yxy[yxn]=ax[i].yy;
            yxmin[yxn]=ax[i].xx;
        }
    }
    yxmax[yxn]=ax[n].xx;
    t1=t2=t3=t4=t5=t6=t7=t8=0;
    yxa[yxn]=max(yxmax[yxn],yxa[yxn-1]);
    yxi[yxn]=min(yxmin[yxn],yxi[yxn-1]);
    t1=yxy[yxn];
    t8=yxy[1];
    t4=yxmin[yxn];
    for(int i=yxn;i>=1;i--)
    {
        t2=yxy[i];
        if(yxmax[i]>t3) t3=yxmax[i];
        if(yxmin[i]<t4) t4=yxmin[i];
        t5=yxy[i-1];
        t6=yxa[i-1];
        t7=yxi[i-1];
        result2=min(result2,(t5-t8)*(t6-t7)+(t3-t4)*(t1-t2));
    }
    printf("%lld",result1-result2);
    return 0;
}
```

---

## 作者：Orion_Rigel (赞：2)

仔细想一想题目还是很简单的。

首先只用一个栅栏是很容易解决的。

用两个栅栏的时候可以横着分开，也可以竖着分开。

只需要对xy进行两次排序就可以愉快的统计了，区间最大最小值可以递推解决。

代码比较丑，另外：不知道为什么，这道题的最小值一定初始化成-inf才能过，WA了五次！

···
```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
int x[50010],y[50010],rank[50010];
int upmax[50010],upmin[50010],domax[50010],domin[50010];
int xmin=inf,xmax=-inf,ymin=inf,ymax=-inf;
ll ans1,ans2;
inline bool cmp1(int a,int b)
{return (x[a]==x[b])?y[a]<y[b]:x[a]<x[b];}
inline bool cmp2(int a,int b)
{return (y[a]==y[b])?x[a]<x[b]:y[a]<y[b];}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        scanf("%d%d",&x[i],&y[i]);
        xmin=min(xmin,x[i]);
        xmax=max(xmax,x[i]);
        ymin=min(ymin,y[i]);
        ymax=max(ymax,y[i]);
        rank[i]=i;
    }
    ans1=((ll)xmax-(ll)xmin)*((ll)ymax-(ll)ymin);
    sort(rank+1,rank+n+1,cmp1);
    ans2=ans1;
    memset(upmin,0x3f,sizeof upmin);
    memset(domin,0x3f,sizeof domin);
    for (int i=1;i<=n+1;++i) upmax[i]=-inf;
    for (int i=1;i<=n+1;++i) domax[i]=-inf;
    for (int i=1;i<=n;++i)
    {
        upmin[i]=upmin[i-1];
        upmax[i]=upmax[i-1];
        upmin[i]=min(upmin[i],y[rank[i]]);
        upmax[i]=max(upmax[i],y[rank[i]]);
    }
    for (int i=n;i>=1;--i)
    {
        domin[i]=domin[i+1];
        domax[i]=domax[i+1];
        domin[i]=min(domin[i],y[rank[i]]);
        domax[i]=max(domax[i],y[rank[i]]);
    }
    for (int i=2;i<=n;++i)
    {
        ll tmp=((ll)x[rank[i-1]]-x[rank[1]])*((ll)upmax[i-1]-upmin[i-1])+((ll)x[rank[n]]-x[rank[i]])*((ll)domax[i]-domin[i]);
        ans2=min(ans2,tmp);
    }
    for (int i=1;i<=n;++i) rank[i]=i;
    sort(rank+1,rank+n+1,cmp2);
    memset(upmin,0x3f,sizeof upmin);
    memset(domin,0x3f,sizeof domin);
    for (int i=1;i<=n+1;++i) upmax[i]=-inf;
    for (int i=1;i<=n+1;++i) domax[i]=-inf;
    for (int i=1;i<=n;++i)
    {
        upmin[i]=upmin[i-1];
        upmax[i]=upmax[i-1];
        upmin[i]=min(upmin[i],x[rank[i]]);
        upmax[i]=max(upmax[i],x[rank[i]]);
    }
    for (int i=n;i>=1;--i)
    {
        domin[i]=domin[i+1];
        domax[i]=domax[i+1];
        domin[i]=min(domin[i],x[rank[i]]);
        domax[i]=max(domax[i],x[rank[i]]);
    }
    for (int i=2;i<=n;++i)
    {
        ll tmp=((ll)y[rank[i-1]]-y[rank[1]])*((ll)upmax[i-1]-upmin[i-1])+((ll)y[rank[n]]-y[rank[i]])*((ll)domax[i]-domin[i]);
        ans2=min(ans2,tmp);
    }
    printf("%lld\n",ans1-ans2);
}
···
```

---

## 作者：lzt415 (赞：0)

## 题目大意
已知平面上有 $n$ 个点，现有一个面积最小且长和宽与的矩形能将这 $n$ 个点框起来，此处将这个面积记为 $s_{1}$，然后希望你能找到两个长与宽也与 $x$ 轴 $y$ 轴平行的矩形，也能把 $n$ 个点框起来，此处将这两个矩形的总面积记为 $s_{2}$。

请你找到 $s_{1}$ 与 $s_{2}$ 的最大差值。
## 解题思路
显然易见，我们先把这 $n$ 个点按 $x$，$y$ 大小排序，然后我们会发现无论怎么分，这 $n$ 个点被分成两个矩形无非是两种情况，即一上以下，或一左一右。

通过观察，我们可以发现这矩形的长就是这些点中最大的 $x$ 的值减去最小的 $x$ 的值，宽是这些点中最大的 $y$ 的值减去最小的 $y$ 的值。

等等，最大值与最小值？这不是区间内求最值吗？既然要求区间最值，那我们就很好维护了。至于这个区间范围，也就是这个矩形的范围，我们可以枚举。
## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+10;
int n,fx[N][20][2],fy[N][20][2],ans=1e18;
struct node
{
	int x,y;
}a[N];
bool cmp1(node a,node b)
{
	return a.x<b.x;
}
bool cmp2(node a,node b)
{
	return a.y<b.y;
}
inline void build()
{
	for(int i=1;i<=n;i++)
	{
		fx[i][0][0]=fx[i][0][1]=a[i].x;
		fy[i][0][0]=fy[i][0][1]=a[i].y;	
	}	
	for(int e=1;e<=20;e++)
	{
		for(int i=1;i+(1<<e)-1<=n;i++)
		{
			fx[i][e][0]=min(fx[i][e-1][0],fx[i+(1<<(e-1))][e-1][0]);
			fx[i][e][1]=max(fx[i][e-1][1],fx[i+(1<<(e-1))][e-1][1]);
			fy[i][e][0]=min(fy[i][e-1][0],fy[i+(1<<(e-1))][e-1][0]);
			fy[i][e][1]=max(fy[i][e-1][1],fy[i+(1<<(e-1))][e-1][1]);			
		}
	}
}
inline int find(int l,int r)
{
	int t=log2(r-l+1);
	int lx = max(fx[l][t][1],fx[r-(1 << t)+1][t][1]);
	int rx = min(fx[l][t][0],fx[r-(1 << t)+1][t][0]);
	int ly = max(fy[l][t][1],fy[r-(1 << t)+1][t][1]);
	int ry = min(fy[l][t][0],fy[r-(1 << t)+1][t][0]);
	return (lx - rx) * (ly - ry);
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp1);
	build();
	for(int i=1;i<=n;i++)
	{
		int k1=find(1,i),k2=find(i+1,n);
		ans=min(ans,k1+k2);
	}
	sort(a+1,a+n+1,cmp2);
	build();
	for(int i=1;i<=n;i++)
	{
		int k1=find(1,i),k2=find(i+1,n);
		ans=min(ans,k1+k2);
	}
	cout<<find(1,n)-ans;	
	return 0;
}

```

---

## 作者：miserExist (赞：0)

题意大概就是，二维平面上有一堆点，本来是一个固定的大矩形包住所有的点。
现在要求你用两个可能较小的矩形包住所有的点，最大化大矩形与两个小矩形面积之差。

那么我们首先的直觉就是把点分别按照 $x$ 和 $y$ 排序，然后枚举分界点，
分别算出左右两块小矩形的面积并进行比较。

在枚举分界点时，左右小矩形的一条边易得，而另外一条边我们需要求出它坐标的最大值和最小值，是一个 RMQ 问题，可以用ST 表做。

但是由于忘记了 ST 表，所以我用线段树（麻烦亿点）维护区间最大最小值。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define debug cout<<"!error!";

const int N = 2e5 + 1000,M = 210,inf = 0x3f3f3f3f;

template <class T> void read(T &w){
	w=0;unsigned long long f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){(w*=10)+=ch-'0';ch=getchar();}
	w*=f;
}

template <class T> void write(T w){
	if(w<0){putchar('-');w*=-1;}
	if(w/10) write(w/10);
	putchar(w%10+'0');
}
template<class T> void writeln(T x){write(x);puts("");}
int n;
struct node
{
	int x,y;
}point[N];
int cmp1(node x, node y)
{
	return x.x < y.x;
}
int cmp2(node x, node y)
{
	return x.y < y.y;
}
struct yy
{
	int l, r;
	int maxx, minn;
}trxx[N << 2];

struct xx
{
	int l, r;
	int maxx, minn;
}tryy[N << 2];
void pushup1(int u)
{
	tryy[u].maxx = max(tryy[u << 1].maxx, tryy[u << 1 | 1].maxx);
	tryy[u].minn = min(tryy[u << 1].minn, tryy[u << 1 | 1].minn);
}
void pushup2(int u)
{
	trxx[u].maxx = max(trxx[u << 1].maxx, trxx[u << 1 | 1].maxx);
	trxx[u].minn = min(trxx[u << 1].minn, trxx[u << 1 | 1].minn);
}
void build_1(int u, int l, int r)
{
	tryy[u].l = l, tryy[u].r = r;
	if(l == r)
	{
		tryy[u].maxx = tryy[u].minn = point[l].y;
		return;
	}
	int mid = l + r >> 1;
	build_1(u << 1, l, mid), build_1(u << 1 | 1, mid + 1, r);
	pushup1(u);
}
void build_2(int u, int l, int r)
{
	trxx[u].l = l, trxx[u].r = r;
	if(l == r)
	{
		trxx[u].maxx = trxx[u].minn = point[l].x;
		return;
	}
	int mid = l + r >> 1;
	build_2(u << 1, l, mid), build_2(u << 1 | 1, mid + 1, r);
	pushup2(u);
}
int query_1_min(int u, int l, int r)
{
	if(tryy[u].l >= l && tryy[u].r <= r)
	{
		return tryy[u].minn;
	}
	int mid = tryy[u].l + tryy[u].r >> 1;
	int minn = inf;
	if(l <= mid) minn = min(minn, query_1_min(u << 1, l, r));
	if(r > mid) minn = min(minn, query_1_min(u << 1 | 1, l, r));
	return minn;
}
int query_1_max(int u, int l, int r)
{
	if(tryy[u].l >= l && tryy[u].r <= r)
	{
		return tryy[u].maxx;
	}
	int mid = tryy[u].l + tryy[u].r >> 1;
	int minn = 0;
	if(l <= mid) minn = max(minn, query_1_max(u << 1, l, r));
	if(r > mid) minn = max(minn, query_1_max(u << 1 | 1, l, r));
	return minn;
}
int query_2_max(int u, int l, int r)
{
	if(trxx[u].l >= l && trxx[u].r <= r)
	{
		return trxx[u].maxx;
	}
	int mid = trxx[u].l + trxx[u].r >> 1;
	int minn = 0;
	if(l <= mid) minn = max(minn, query_2_max(u << 1, l, r));
	if(r > mid) minn = max(minn, query_2_max(u << 1 | 1, l, r));
	return minn;
}
int query_2_min(int u, int l, int r)
{
	if(trxx[u].l >= l && trxx[u].r <= r)
	{
		return trxx[u].minn;
	}
	int mid = trxx[u].l + trxx[u].r >> 1;
	int minn = inf;
	if(l <= mid) minn = min(minn, query_2_min(u << 1, l, r));
	if(r > mid) minn = min(minn, query_2_min(u << 1 | 1, l, r));
	return minn;
}
signed main()
{
	read(n);
	int ANS = 0;
	int MAX_X = 0, MAX_Y = 0, MIN_X = inf, MIN_Y = inf;
	for(int i = 1; i <= n; i ++)
	{
		read(point[i].x), read(point[i].y);
		MAX_X = max(MAX_X, point[i].x);
		MIN_X = min(MIN_X, point[i].x);
		MAX_Y = max(MAX_Y, point[i].y);
		MIN_Y = min(MIN_Y, point[i].y);
	}
	ANS = (MAX_X - MIN_X) * (MAX_Y - MIN_Y);
	//----------------------------------------------------
	sort(point + 1, point + 1 + n, cmp1);
	build_1(1,1,n);
	int ans = 0;
	for(int duan = 1; duan < n; duan ++)
	{
		int lc = (point[duan].x - point[1].x);
		int rc = (point[n].x - point[duan + 1].x);
		int lminy = query_1_min(1, 1, duan);
		int lmaxy = query_1_max(1, 1, duan);
		int rminy = query_1_min(1, duan + 1, n);
		int rmaxy = query_1_max(1, duan + 1, n);
		int lh = (lmaxy - lminy), rh = (rmaxy - rminy);
		
		ans = max(ans, ANS - (lh * lc) - (rh * rc));
	}
	sort(point + 1, point + 1 + n, cmp2);
	
	build_2(1,1,n);
	for(int d = 1; d < n; d ++)
	{
		int lc = (point[d].y - point[1].y);
		int rc = (point[n].y - point[d + 1].y);
		int lminy = query_2_min(1,1,d);
		int lmaxy = query_2_max(1,1,d);
		int rminy = query_2_min(1,d + 1, n);
		int rmaxy = query_2_max(1,d+1,n);
		int lh = (lmaxy - lminy), rh = (rmaxy - rminy);
		
		ans = max(ans, ANS - (lh * lc) - (rh * rc));
	}
	writeln(ans);
	
	
	
	
	return 0;
}

```

---

