# Gleb And Pizza

## 题目描述

### 题目大意

Gleb 点了披萨，他发现有几片香肠在外皮上，但他讨厌披萨的外皮。

披萨一个半径为  $r$ 的圆，圆心位于原点，披萨中间部分是半径为  $r-d$ 的圆，圆心也在原点。外皮部分就是外面一圈宽为  $d$ 的环。

香肠片也是圆的，对于第  $i$ 片香肠，他的半径为  $r_i$ ，圆心位于  $(x_i,y_i)$

现在求有多少个香肠片整个都在外皮上。

## 样例 #1

### 输入

```
8 4
7
7 8 1
-7 3 2
0 2 1
0 -2 2
-3 -3 1
0 6 2
5 3 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 8
4
0 0 9
0 0 10
1 0 1
1 0 2
```

### 输出

```
0
```

# 题解

## 作者：D2T1 (赞：2)

首先，题目翻译有问题。

第一行两个数字 $r$,$d$ 代表的是大圆的半径和大圆半径和小圆半径的差。

------------

**解法**

把问题抽象化。

以原图的圆2为例，画一条直线连接圆2的圆心和 $(0,0)$ 点：

![https://cdn.luogu.com.cn/upload/image_hosting/qf0wuvlb.png](https://cdn.luogu.com.cn/upload/image_hosting/qf0wuvlb.png)

因此，如果这一条直线和圆2的两个交点位于大圆和小圆之间，那么圆2就位于两个圆之间。

显然，直线和圆2的交点有一个在大圆以外，所以圆2不在两个圆之间。

------------

**代码**

核心的一句：

```
if(sqrt(x*x+y*y)-z>=(r-d)-eps&&sqrt(x*x+y*y)+z<=r+eps) ++sum;
```

其他就是一些输入输出什么的。

---

## 作者：Double_Light (赞：1)

首先简化题意，本题可以看作给定 $n$ 个圆和一个圆环，求有多少个圆完全在圆环内。

然后我们发现一个显然的事实：从圆环的圆心出发向一个圆的圆心连一条线，如果这条直线与圆边的交点均在圆环之内，那么整个圆也在圆环里面。

接着由于已知圆环的圆心位置、圆的半径和圆心位置，我们容易用勾股定理得出上述的两交点与圆心的距离。

最后，我们根据这个距离，判断一下焦点是否在圆环内，如果是，则圆完全在圆环内。

代码如下：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int r,d,n,ans,x,y,z;
int main(){
	cin>>r>>d>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y>>z;
		if(sqrt(x*x+y*y)-z>=r-d&&sqrt(x*x+y*y)+z<=r)ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_byta (赞：1)

我们可以用勾股定理求出每一个香肠的圆心到披萨的圆心的距离，我们设它为 $k$，如果 $k-r(i)>r-d$ 而且 $k + r(i) <= r$，说明香肠在披萨的环上。

```cpp
#include <bits/stdc++.h>
using namespace std;	
int r,d,n,x,y,r1,a=0;
int main()
{
	cin >> r >> d >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> x >> y >> r1;
		double k = sqrt(x * x + y * y);
		if(k - r1 >= r - d && k + r1 <= r)a++;
	}
	cout<<a;
	return 0;
}
```



---

## 作者：GFyyx (赞：1)

## 题目大意
各位奆老太强了，本人落后地发一篇 C 语言的题解。

给定一个大圆环，圆心处于原点，再给定 $n$ 个圆，问有多少个圆在大圆环上。

## 解题思路
简单的几何题。

连接第 $i$ 个香肠 $S_i$ 圆心与原点（披萨圆心），设其所在的直线为 $l_i$。

截取圆 $S_i$ 与 $l_i$ 的两个交点，若它们都在大圆环上，则满足题目条件。

## AC 代码（附有注释）
```c
#include <stdio.h>
#include <math.h>
int r,d,n,ans;
int main(){
	scanf("%d%d%d",&r,&d,&n);
	double x,y,k,dis;//香肠的坐标及半径,距离原点的距离 
	for(register int i=1; i<=n; i++){
	scanf("%lf%lf%lf",&x,&y,&k);
		dis=sqrt(x*x+y*y);
		if(dis-k>=r-d&&dis+k<=r) ans++;
		//判断香肠的弧与原点连线交点是否在外皮中 
	}
	printf("%d\n",ans);
    return 0;//远古C码风，见笑了 
}
```


---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

这道题我们要用到一个在平面直角坐标系求两点 $(x_1,y_1)$ 和 $(x_2,y_2)$ 距离的公式：

$ dis=\sqrt{|x_1-x_2|^2+|y_1-y_2|^2}$

不妨设香肠 $i$ 的半径为 $R$，其圆心和原点距离为 $dis$，则只要满足 $dis+R \le r$ 且 $dis-R \ge r-d$，这片香肠就满足题意。

代码很简单，因此不放代码。

---

## 作者：ny_Dacong (赞：0)

# 题目思路

我们会发现，当一个香肠在外皮上的时候，这个香肠的圆心与披萨圆心的连线所在的直线与香肠边缘的两个交点一定在外皮上。

![](https://cdn.luogu.com.cn/upload/image_hosting/sw5x2iy3.png?x-oss-process=image/resize,m_lfit,h_380,w_600)

首先讨论靠近披萨圆心的交点。怎么判断交点在外皮上呢？最简单的办法就是判断交点与披萨圆心的连线长度，和披萨中间部分的半径。如果前者比后者长，那么交点一定在外皮上。

![](https://cdn.luogu.com.cn/upload/image_hosting/qi8b1fzq.png?x-oss-process=image/resize,m_lfit,h_300,w_350)

怎么计算交点与披萨圆心的连线长度？很简单，用勾股定理即可。我们用勾股定理算出香肠的圆心与披萨圆心的连线的长度，再减去香肠的半径即可。

同样，另一个交点也可以用相同的思路判断。

# code

语言：C++。

```cpp
#include<bits/stdc++.h>
using namespace std;
int R,D,n,Len;
int x,y,r;
double len;
int ans = 0;
int main(){
    scanf("%d%d%d",&R,&D,&n);
    Len = R-D;
    for(int i = 1; i <= n; i++){
        scanf("%d%d%d",&x,&y,&r);
        len = sqrt(x*x+y*y);
        if(len-r >= Len && len+r <= R){
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：jhdrgfj (赞：0)

## 解法

一道纯数学题。

香肠片在披萨中间部分外的条件是离圆心的距离大于等于 $r-d$，而香肠片在外皮内的条件则是离圆心的距离小于等于 $r$。综合两式，可得出香肠片在外皮内部的条件为 $r-d \le dis \le r$，其中 $dis$ 为香肠片离圆心的距离。

再根据两点之间的距离公式，可得出 $dis=\sqrt {x_i^2+y_i^2}$，其中 $x_i,y_i$ 分别是第 $i$ 个香肠片圆心的横，纵坐标。 

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,d,n,ans; //ans 来存答案数
int main()
{
	cin>>r>>d>>n;
	for (int i=1;i<=n;i++){
		double rr,x,y,dis;
		cin>>x>>y>>rr;
		dis=sqrt(x*x+y*y);    //计算距离
		if (dis-rr>=r-d && dis+rr<=r){  //判断香肠片是否在外皮内部
			ans++;
		}
	}
	cout<<ans;
}
```


---

## 作者：BigJoker (赞：0)

# Solution

一道很简单的几何题，不卡精度。

先计算一下香肠的圆心到顶点的直线距离为  $p$，直接勾股定理即可。

$p=\sqrt{x_i^2+y_i^2}$

那么当 $p+d\le R$，表明没有超出。

当 $p-d\ge R-D$，表明没有出环最小边界。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
double R,d;
int n,ans;
int main(){
	scanf("%lf %lf %d",&R,&d,&n);
	while(n--){
		int x,y;
		double r;
		scanf("%d %d %lf",&x,&y,&r);
		double path=sqrt(x*x+y*y);
		if(path-r>=R-d && path+r<=R) ans++;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：泠小毒 (赞：0)

# Gleb And Pizza

给定2个以(0,0)为圆心的圆的半径，给定n个以(x,y)为圆心，z为半径的圆

让你求有多少个圆刚好在两圆之间

## 广告插入

在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190430/)

## 解法

用数学化简它，发现就是(x,y)离(0,0)的距离±z和两个半径比较一下，因为要开根号，用一个eps避免卡精

## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
int r,d,n,x,y,z,ans;
double dis;
int main()
{
	scanf("%d%d%d",&r,&d,&n),d=r-d;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&x,&y,&z),dis=sqrt(1.0*(x*x+y*y));
		if(dis-1.0*z>=1.0*d-eps&&dis+1.0*z<=1.0*r+eps)ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

