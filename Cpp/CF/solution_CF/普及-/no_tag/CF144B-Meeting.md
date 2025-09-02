# Meeting

## 题目描述

The Super Duper Secret Meeting of the Super Duper Secret Military Squad takes place in a Super Duper Secret Place. The place is an infinite plane with introduced Cartesian coordinate system. The meeting table is represented as a rectangle whose sides are parallel to the coordinate axes and whose vertexes are located at the integer points of the plane. At each integer point which belongs to the table perimeter there is a chair in which a general sits.

Some points on the plane contain radiators for the generals not to freeze in winter. Each radiator is characterized by the number $ r_{i} $ — the radius of the area this radiator can heat. That is, if the distance between some general and the given radiator is less than or equal to $ r_{i} $ , than the general feels comfortable and warm. Here distance is defined as Euclidean distance, so the distance between points $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF144B/db1ba0d5909a3b47109b2e5f65fe13400ae1bd9a.png)

Each general who is located outside the radiators' heating area can get sick. Thus, you should bring him a warm blanket. Your task is to count the number of warm blankets you should bring to the Super Duper Secret Place.

The generals who are already comfortable do not need a blanket. Also the generals never overheat, ever if they are located in the heating area of several radiators. The radiators can be located at any integer points on the plane, even inside the rectangle (under the table) or on the perimeter (directly under some general). Even in this case their radius does not change.

## 说明/提示

In the first sample the generals are sitting at points: $ (2,2) $ , $ (2,3) $ , $ (2,4) $ , $ (2,5) $ , $ (3,2) $ , $ (3,5) $ , $ (4,2) $ , $ (4,3) $ , $ (4,4) $ , $ (4,5) $ . Among them, 4 generals are located outside the heating range. They are the generals at points: $ (2,5) $ , $ (3,5) $ , $ (4,4) $ , $ (4,5) $ .

In the second sample the generals are sitting at points: $ (5,2) $ , $ (5,3) $ , $ (6,2) $ , $ (6,3) $ . All of them are located inside the heating range.

## 样例 #1

### 输入

```
2 5 4 2
3
3 1 2
5 3 1
1 3 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 2 6 3
2
6 2 2
6 5 3
```

### 输出

```
0
```

# 题解

## 作者：_xbn (赞：3)

由于 n 很小，我们考虑暴力做法，即枚举矩形上的每一个点，再枚举每一个信号塔

看看这个点是否被其中一个信号塔覆盖，这样这题就可以过了，此外，由于矩形

是轴对称图形，我们可以加一个小优化，在枚举时，可以直接判断对称的两个点。

细节内容详见代码注释。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int x[1010],y[1010],r[1010],n;
int zone(int xx, int yy)//求两个点的欧几里得距离
{
    for(int i=0;i<n;i++)
    {
       if((x[i]-xx)*(x[i]-xx)+(y[i]-yy)*(y[i]-yy)<=r[i]*r[i])return 0;//勾股定理
        
    } 
	return 1;
}
int main()
{
    int xa,ya,xb,yb,ans=0;
    cin>>xa>>ya>>xb>>yb>>n;
    for(int i=0;i<n;i++) 
    {
        cin>>x[i]>>y[i]>>r[i];
    }
    for(int i=min(xa,xb);i<=max(xa,xb);i++)//横坐标从小到大枚举
     ans+=zone(i,ya)+zone(i,yb);
    for(int i=min(ya,yb)+1;i<max(ya,yb);i++)//纵坐标从小到大枚举
     ans+=zone(xa,i)+zone(xb,i);
    cout<<ans;
   return 0;
} 
```




---

## 作者：arrow_king (赞：2)

这道题就是一个模拟题，但是其中有许多细节需要注意。

## 思路

观察数据范围，发现 $n\leq10^3$，所以这道题可以放心大胆地去暴力模拟。

思路也很简单：首先枚举矩形上的所有点，然后枚举每一个散热器，用公式
$$s=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$$
来取得散热器与矩形上的点的欧几里得距离，以此来判断是否超出范围。

附一张图：（第一个样例）

![](https://cdn.luogu.com.cn/upload/image_hosting/d6x3630p.png)

其中，点 $O$ 为坐标系原点，点 $A,B$ 为题目中给出的矩形两个点，$x_1,x_2,x_3$ 分别表示三个散热器，绿色的圈表示散热器范围，矩形上的红色点表示将军们坐的位置。

这张图中显然看出，未被辐射到的点有 $4$ 个。

## 细节

这些细节使得我调了很久。

- 注意初始给出的点不一定第 $2$ 个点就在第 $1$ 个点的右上方，从哪里开始枚举要注意，不然会成死循环。
- 注意四个角上的点不要重复计算，不然会 WA。
- 坐标系横坐标和纵坐标的关系要分清，不要反过来。（我就反过来了，最后变成了全反。）
- 注意点在辐射范围边缘上的情况，比如上面样例中 $x_2$ 的那个点就是。

**最后就是大家期待已久的代码：**

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
struct node {
	int x,y;
	int r;
};
int n,l1,r1,l2,r2,ans;
node a,b,p[100005];
bool f1,f2;
double getlen(int x1,int y1,int x2,int y2) {
	double num=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	return num;
}
int main() {
	scanf("%d%d%d%d",&a.x,&a.y,&b.x,&b.y);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].r);
	l1=min(a.x,b.x),r1=max(a.x,b.x);
	l2=min(a.y,b.y),r2=max(a.y,b.y);    //确定l1,r1,l2,r2的大小关系
	for(int i=l1;i<=r1;i++) {
		f1=f2=0;
		for(int j=1;j<=n;j++) if(p[j].r>=getlen(l2,i,p[j].y,p[j].x)) {    //我不小心把所有坐标都反过来了，这是数组的习惯，大家不要模仿，还是要以坐标系的习惯好。
			f1=1;
			break;
		}
		for(int j=1;j<=n;j++) if(p[j].r>=getlen(r2,i,p[j].y,p[j].x)) {
			f2=1;
			break;
		}
		if(!f1) ans++;
		if(!f2) ans++;
	}
	for(int i=l2+1;i<r2;i++) {    //不要重复计算
		f1=f2=0;
		for(int j=1;j<=n;j++) if(p[j].r>=getlen(i,l1,p[j].y,p[j].x)) {
			f1=1;
			break;
		}
		for(int j=1;j<=n;j++) if(p[j].r>=getlen(i,r1,p[j].y,p[j].x)) {    //必须要用大于等于，不然边界计算不上
			f2=1;
			break;
		}
		if(!f1) ans++;
		if(!f2) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```

~~完结撒花，给个赞吧~~

---

## 作者：飞啾6373 (赞：2)

### 题意

给出一个长方形对角的坐标和 $n$ 个圆的坐标及半径，要求给出长方形的边上的点中没有被任何圆覆盖的点数量。

（小提示：由于题目描述里并没有表示输入的对角具体是哪两个，所以需要在代码里判断一下）

### 思路

以这题 $n$ 的范围来看，暴力方法并不会超时。

因此，只需要在输入每一个圆的坐标及半径后枚举长方形边上的每一个点，判断该点是否被覆盖并使用数组记录，最后枚举用于记录的数组，得出未被覆盖的点数量后输出即可。

### 代码

（代码内含注释）

```
#include<bits/stdc++.h>
using namespace std;
int a[4444][4444];
int main()
{
	int xa,ya,xd,yd,n,i,ans=0;//ans存储最终答案，即未被覆盖的人数 ，提前赋值为0 
	cin>>xa>>ya>>xd>>yd;//输入对角 
	cin>>n;//圆个数 
	for(i=0;i<n;i++)
	{
		int x,y,r,j,k;
		cin>>x>>y>>r;//圆的坐标及半径 
		for(j=0;j<=abs(xa-xd);j+=abs(xa-xd))
		{
			for(k=0;k<=abs(ya-yd);k++)
			{
				double sq=0.0;
				int x1,y1;
				x1=max(xa,xd)-j;
				y1=max(ya,yd)-k;
				sq=sqrt(((x1-x-0.0)*(x1-x-0.0)*1.0)+((y1-y-0.0)*(y1-y-0.0)*1.0));
				if(sq<=r)a[j][k]=1;
			}
		}
		for(j=0;j<=abs(xa-xd);j++)
		{
			for(k=0;k<=abs(ya-yd);k+=abs(ya-yd))
			{
				double sq=0.0;
				int x1,y1;
				x1=max(xa,xd)-j;
				y1=max(ya,yd)-k;
				sq=sqrt(((x1-x-0.0)*(x1-x-0.0)*1.0)+((y1-y-0.0)*(y1-y-0.0)*1.0));
				if(sq<=r)a[j][k]=1;//注意一点，在圆覆盖边界上的点也算被圆覆盖 
			}
		}
	}
	//↓枚举每一条边上未被覆盖的的人数 ，以ans记录
	for(i=0;i<=abs(xa-xd);i++)
	{
		if(a[i][0]==0)ans++;
		if(a[i][abs(ya-yd)]==0)ans++; 
	}
	for(i=0;i<=abs(ya-yd);i++)
	{
		if(a[0][i]==0)ans++;
		if(a[abs(xa-xd)][i]==0)ans++;
	}
	//↓注意特判四个角上的人，如果有重复记录需要相应减少
	if(a[0][0]==0)ans--;
	if(a[0][abs(ya-yd)]==0)ans--;
	if(a[abs(xa-xd)][0]==0)ans--;
	if(a[abs(xa-xd)][abs(ya-yd)]==0)ans--;
	cout<<ans;//输出答案 
	return 0;
}
```


---

## 作者：Ninelife_Cat (赞：2)

### 题目大意：

给出一个矩形的左上角坐标和右下角坐标以及 $n$ 个信号站 ~~（?~~ 的坐标，每个信号站的覆盖半径为 $r_i$ 。

若一个点到信号站的欧几里得距离小于等于该信号站的覆盖半径，则称这个点被覆盖。

求矩形周长上的点有几个没有被覆盖。

### 思路：

$n$ 的范围比较小，所以我们可以直接暴力过。

对于矩形周长上的每个点扫一遍所有的信号站，判断它是否被覆盖即可。

注意不要重复计算矩形周长上的点。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,x2,y2,n,tx[1001],ty[1001],r[1001],ans;
int dis(int x,int y,int x2,int y2) {return (x2-x)*(x2-x)+(y2-y)*(y2-y);}
//计算欧几里得距离,为了防止掉精度将两边同时平方
signed main()
{
	cin>>x>>y>>x2>>y2;//矩形坐标
	if(x2<x) swap(x2,x);
	if(y2<y) swap(y2,y);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>tx[i]>>ty[i]>>r[i];//信号站坐标
	bool flag=0;//flag记录当前的点是否被覆盖
	for(int i=1;i<=n;i++)
		if(dis(x,y,tx[i],ty[i])<=r[i]*r[i]) {flag=1;break;}
	if(!flag) ans++;
	flag=0;
	for(int i=1;i<=n;i++)
		if(dis(x2,y,tx[i],ty[i])<=r[i]*r[i]) {flag=1;break;}
	if(!flag) ans++;
	flag=0;
	for(int i=1;i<=n;i++)
		if(dis(x,y2,tx[i],ty[i])<=r[i]*r[i]) {flag=1;break;}
	if(!flag) ans++;
	flag=0;
	for(int i=1;i<=n;i++)
		if(dis(x2,y2,tx[i],ty[i])<=r[i]*r[i]) {flag=1;break;}
	if(!flag) ans++;
    	//特判矩形四个角上的点,防止重复计算
	for(int i=x+1;i<x2;i++)
	{
		flag=0;
		for(int j=1;j<=n;j++)
			if(dis(i,y,tx[j],ty[j])<=r[j]*r[j]) {flag=1;break;}
		if(!flag) ans++;
	}
	for(int i=x+1;i<x2;i++)
	{
		flag=0;
		for(int j=1;j<=n;j++)
			if(dis(i,y2,tx[j],ty[j])<=r[j]*r[j]) {flag=1;break;}
		if(!flag) ans++;
	}
	for(int i=y+1;i<y2;i++)
	{
		flag=0;
		for(int j=1;j<=n;j++)
			if(dis(x,i,tx[j],ty[j])<=r[j]*r[j]) {flag=1;break;}
		if(!flag) ans++;
	}
	for(int i=y+1;i<y2;i++)
	{
		flag=0;
		for(int j=1;j<=n;j++)
			if(dis(x2,i,tx[j],ty[j])<=r[j]*r[j]) {flag=1;break;}
		if(!flag) ans++;
	}
	cout<<ans;
	return 0;
}

---

## 作者：Nephren_Sakura (赞：1)

题意简述：[link](https://www.luogu.com.cn/problem/)

打开题面，首先看到数据范围：$n\le10^3$，十分的小。

于是考虑暴力过题。

具体下来，枚举会议桌边的每个点，再枚举每个加热器。

如果每个加热器都无法加热到这个点，则 $ans$ 加一。

具体代码实现中，对于每个点，可以先将 $ans$ 加一，然后枚举加热器时，如果加热器能够加热，则将 $ans$ 减一并 break。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9'){
		if (ch=='-')
			f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-48;
		ch=getchar();
	}
	return x*f;
}
inline void put(int x)
{
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}
int xa=read(),ya=read(),xb=read(),yb=read(),n=read(),ans;
struct node{
	int x,y,r;
}a[1000005];
signed main(){
	for(int i=1; i<=n; i++)
		a[i].x=read(),a[i].y=read(),a[i].r=read();
	for(int i=min(xa,xb); i<=max(xa,xb); i++){
		ans+=2;
		for(int j=1; j<=n; j++){
			if((a[j].x-i)*(a[j].x-i)+(a[j].y-ya)*(a[j].y-ya)<=a[j].r*a[j].r){
				ans--;
				break;
			}
		}
		for(int j=1; j<=n; j++){
			if((a[j].x-i)*(a[j].x-i)+(a[j].y-yb)*(a[j].y-yb)<=a[j].r*a[j].r){
				ans--;
				break;
			}
		}
	}//我将同一行放在一个循环做了
	for(int i=min(ya,yb)+1; i<max(ya,yb); i++){
		ans+=2;
		for(int j=1; j<=n; j++){
			if((a[j].x-xa)*(a[j].x-xa)+(a[j].y-i)*(a[j].y-i)<=a[j].r*a[j].r){
				ans--;
				break;
			}
		}
		for(int j=1; j<=n; j++){
			if((a[j].x-xb)*(a[j].x-xb)+(a[j].y-i)*(a[j].y-i)<=a[j].r*a[j].r){
				ans--;
				break;
			}
		}
	}//同上
	cout<<ans;
	return 0;
}

```

---

## 作者：xiaomimxl (赞：1)

## 题意：

一张长方形桌子的四个顶点全部在整数点位置，桌子的四条边上每个整数点  $(x,y)$ 位置有一把椅子，代表有一个人，当使用加热器在桌子周围加热时，问有几个人不在加热范围之内。

## 解题思路：

刚开始还以为是在整个矩形内部都有点，但是看了样例发现是在矩阵的边上

一个加热器可以确定一个圆，判断每个人是否在圆内或圆上；输出不在圆内或圆上的人的个数即可。

时间复杂度: $O(4 \times n^2)$

## Code:

```cpp
#include<stdio.h>
#include<string.h>
int n,i,j,t,cnt,sum,x1,x2,y1,y2;
struct radiator
{
    int x;
    int y;
    int r;
}a[1005];
void dis(int X,int Y) /*判断是否在圆内或圆上*/
{
     sum++; /*记录桌子周围的总人数*/
     for(t=0;t<n;t++)
     if((X-a[t].x)*(X-a[t].x)+(Y-a[t].y)*(Y-a[t].y)<=a[t].r*a[t].r)
     {
        cnt++;  /*记录在圆内或圆上的人的个数*/
        break;
     }
}
void cal1(int m,int p,int q)  /**/
{
    for(i=m,j=p;i<=q;i++)
        dis(i,j);
}
void cal2(int m,int p,int q) /**/
{
    for(j=m,i=p;j<=q;j++)
       dis(i,j);
}
int main()
{
    int temp1,temp2;
    while(~scanf("%d%d%d%d",&x1,&y1,&x2,&y2))
    {
        if(x1>x2) 
        {
            temp1=x1;x1=x2;x2=temp1;
            temp2=y1;y1=y2;y2=temp2;
        }  /*保证x1<x2*/
        sum=0;
        cnt=0;
        scanf("%d",&n);
        for(i=0;i<n;i++)
          scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].r);
        cal1(x1,y1,x2); /*和x轴平行的边上的点*/
        cal1(x1,y2,x2); /*和x轴平行的边上的点*/
        if(y1>y2)
        {
            cal2(y2+1,x1,y1-1); /*和y轴平行的边上的点*/
            cal2(y2+1,x2,y1-1); /*和y轴平行的边上的点*/
        }
        else
        {
            cal2(y1+1,x1,y2-1); /*和y轴平行的边上的点*/
            cal2(y1+1,x2,y2-1); /*和y轴平行的边上的点*/
        }
        printf("%d\n",sum-cnt);
    }
    return 0;
}
```


---

## 作者：yimuhua (赞：1)

## 题意：
给出一个矩形左上角和右下角的坐标以及 $n$ 个圆的半径，求有多少个在矩形周长上的点没有被任何圆覆盖。
## 思路：
看到数据范围，我们发现 $n$ 很小，于是考虑暴力做法。

枚举矩形周长上的每一个点，看看其是否被任何圆覆盖。

**小优化：** 由于矩形是轴对称图形，于是只需要枚举对称两边其中一个。
## AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ans, x[1005], y[1005], r[1005];
int f(int cx, int cy) {
    for(int i = 0; i < n; i++)
        if((x[i] - cx) * (x[i] - cx) + (y[i] - cy) * (y[i] - cy) <= r[i] * r[i])
            return 0;
    return 1;
}
int main() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2 >> n;
    for(int i = 0; i < n; i++)
        cin >> x[i] >> y[i] >> r[i];
    for(int i = min(x1, x2); i <= max(x1, x2); i++)
        ans += f(i, y1) + f(i, y2);
    for(int i = min(y1, y2) + 1; i < max(y1, y2); i++)
        ans += f(x1, i) + f(x2, i);
    cout << ans;
    return 0;
}
```


---

## 作者：flangeborg (赞：0)

~~关于我在 CF 上过了这道题，在洛谷上提交就 UKE 这档事~~

## 题意简述

在笛卡尔坐标系里给定一个与坐标轴平行的矩形的左上角和右下角（从数据看起来是这样的，但是在 CF 直接当成这样去写就会 WA），给定 $n$ 个半径为 $r$、圆心分别在 $(x_i,y_i)$ 的圆，求未被**这些圆所覆盖的并且在这个矩形的边上的整数点**个数。

## 解题方法

本题 $n$ 的范围较小，$n\le1000$。完全可以使用暴力枚举来求解，只要分别枚举矩形长上的和宽上的整点，并用两点距离公式来判断是否被包含在圆内，计数得到解并输出就行了。**（矩形上 4 个长与宽的交点一定不要重复计算！）**

## 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
int x1,y1,x2,y2,n,res;
struct node{int x,y,r;}tower[10005];

int main()
{
	scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&n);
	for(int i = 1; i <= n; i++) scanf("%d%d%d",&tower[i].x,&tower[i].y,&tower[i].r);//读入 
	for(int i = min(x1,x2); i <= max(x1,x2); i++)//max，min确定遍历范围 
	{
		bool check1 = false,check2 = false;//同时计算矩形的两条长上的整点是否被包含 
		for(int j = 1; j <= n; j++)
		{
			double dis1 = (tower[j].x - i) * (tower[j].x - i) + (tower[j].y - y1) * (tower[j].y - y1);
			double dis2 = (tower[j].x - i) * (tower[j].x - i) + (tower[j].y - y2) * (tower[j].y - y2);
			//两点距离公式 
			if(dis1 <= tower[j].r * tower[j].r) check1 = true;
			if(dis2 <= tower[j].r * tower[j].r) check2 = true;
			//判断是否被包含 
		}
		if(!check1) res++;
		if(!check2) res++;
		//如果没有被任何一个圆所包含，答案++ 
	}
	//方法同上，只是枚举宽上的整点 
	for(int i = min(y1,y2) + 1; i < max(y1,y2); i++)//循环的起始和重点一定要注意，不能重复计算 
	{
		bool check1 = false,check2 = false;
		for(int j = 1; j <= n; j++)
		{
			double dis1 = (tower[j].y - i) * (tower[j].y - i) + (tower[j].x - x1) * (tower[j].x - x1);
			double dis2 = (tower[j].y - i) * (tower[j].y - i) + (tower[j].x - x2) * (tower[j].x - x2);
			if(dis1 <= tower[j].r * tower[j].r) check1 = true;
			if(dis2 <= tower[j].r * tower[j].r) check2 = true;
		}
		if(!check1) res++;
		if(!check2) res++;
	}
	printf("%d",res);
	return 0;
}
```


---

## 作者：ningago (赞：0)

### 简要题意
- 给出一个矩形的**相对**顶点。
- 给出 $n$ 个半径为 $r_i$ 的圆及其坐标。
- 求矩形的边上多少个点不被圆覆盖。

### 思路

根据题面 The absolute value of all coordinates does not exceed 1000(输入所有数绝对值不大于1000)。

可以使用暴力 $O(n^{2})$ 做法。

对于每个圆,可以枚举每个处于矩形的边上的点与它的欧几里得距离，将符合要求的点进行计数。

将总点数减去符合要求的点，就是是不符合要求的点。

### 代码

```cpp
#include <iostream>
#include <cstdio>

#define M 2005
using namespace std;

bool mp[2 * M][2 * M];//防止负数数组越界
int xa,ya,xb,yb,n,ans;

bool cd(int x3,int y3,int x4,int y4,int _r)
{
	return (x4 - x3) * (x4 - x3) + (y4 - y3) * (y4 - y3) <= _r * _r;
}

void radiator(int xx,int yy,int r)
{
	for(int i = xa;i <= xb;i++)
	{//i + M 防止负数数组越界
		if(!mp[i + M][ya + M] && cd(xx,yy,i,ya,r))
		{
			ans++;
			mp[i + M][ya + M] = 1;
		}
		if(!mp[i + M][yb + M] && cd(xx,yy,i,yb,r))
		{
			ans++;
			mp[i + M][yb + M] = 1;
		}
	}
	for(int i = ya;i <= yb;i++)
	{
		if(!mp[xa + M][i + M] && cd(xx,yy,xa,i,r))
		{
			ans++;
			mp[xa + M][i + M] = 1;
		}
		if(!mp[xb + M][i + M] && cd(xx,yy,xb,i,r))
		{
			ans++;
			mp[xb + M][i + M] = 1;
		}
	}
	return;
}

int main()
{
	scanf("%d%d%d%d%d",&xa,&ya,&xb,&yb,&n);
	if(xa > xb)	swap(xa,xb);
	if(ya > yb)	swap(ya,yb);
  	//使xa,ya,xb,yb统一成左上角与右下角,便于计算
	for(int k = 1,x_,y_,r;k <= n;k++)
	{
		scanf("%d%d%d",&x_,&y_,&r);
		radiator(x_,y_,r);
	}
  	//周长 - 符合要求的点数
	printf("%d",2 * (xb - xa + yb - ya) - ans);
	return 0;
}
```

---

