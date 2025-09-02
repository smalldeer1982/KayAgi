# [ARC004A] 2点間距離の最大値 ( The longest distance )

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc004/tasks/arc004_1

平面上に $ N $ 個の点があり、それぞれ $ 0 $ から $ N-1 $ までの番号が付けられており、それぞれの点について $ x $ 座標と $ y $ 座標が与えられています。  
 その $ N $ 点のうち $ 2 $ 点を選び結んで得られる線分のうち、最も長くなる線分の長さを求めてください。 入力は以下の形式で標準入力から与えられる。

> $ N $ $ x_{0} $ $ y_{0} $ $ x_{1} $ $ y_{1} $ : : $ x_{N-1} $ $ y_{N-1} $

- 入力は $ N+1 $ 行ある。
- $ 1 $ 行目には、点の個数を表す整数 $ N\ (2≦N≦100) $が与えられる。
- $ 2 $ 行目から $ N+1 $ 行目までの $ i+2\ (0\ ≦\ i\ 行目には、i $ 番の点の $ x $ 座標を表す整数 $ x_{i}(0≦x_{i}≦100) $ と $ y $ 座標を表す整数 $ y_{i}(0≦y_{i}≦100) $ が空白を区切りとして与えられる。
- 与えられる点のうち $ x $ 座標と $ y $ 座標がともに一致する点の組は存在しないが、$ 2 $ つの点を繋ぐ線分上に他の点が存在することはありうる。
 
 $ N $ 点のうち $ 2 $ 点を選び結んで得られる線分のうち、最も長い線分の長さを標準出力に $ 1 $ 行で出力せよ。  
 誤差は絶対誤差あるいは相対誤差の少なくとも片方が $ 10^{-3} $ 以下であれば許容する。  
 なお、最後には改行を出力せよ。 ```
<pre class="prettyprint linenums">
3
1 1
2 4
4 3
```

 ```
<pre class="prettyprint linenums">
3.605551
```

- $ 3 $ 点の位置関係を示すと下図のようになります。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc004_1/f9435303ba02d69cbe4d613ed7da44c306fbdbce.png)

- $ (1,1) $ と $ (2,4) $ を繋いだ線分の長さは $ \sqrt{(2-1)^2+(4-1)^2}\ =\ \sqrt{10}\ =\ 3.162278 $ です。
- $ (2,4) $ と $ (4,3) $ を繋いだ線分の長さは $ \sqrt{(4-2)^2+(3-4)^2}\ =\ \sqrt{5}\ =\ 2.236068 $ です。
- $ (4,3) $ と $ (1,1) $ を繋いだ線分の長さは $ \sqrt{(1-4)^2+(1-3)^2}\ =\ \sqrt{13}\ =\ 3.605551 $ です。
- 以上により最も長い線分の長さは太線が示す $ 3.605551 $ になります。
 
```
<pre class="prettyprint linenums">
10
1 8
4 0
3 7
2 4
5 9
9 1
6 2
0 2
8 6
7 8
```

 ```
<pre class="prettyprint linenums">
10.630146
```

- $ 10 $ 点の位置関係を示すと下図のようになります。
- 最も長い線分は点 $ 0 $ と点 $ 5 $ を繋ぐ線分で、$ 10.630146 $ になります。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc004_1/0518354a5208ab203dcd93e56a38b1787a87f90c.png)

 ```
<pre class="prettyprint linenums">
4
0 0
0 100
100 0
100 100
```

 ```
<pre class="prettyprint linenums">
141.421356
```

- 最も長い線分は点 $ 0 $ と点 $ 3 $ を繋ぐ線分、または点 $ 1 $ と点 $ 2 $ を繋ぐ線分で、$ 141.421356 $ になります。

```
<pre class="prettyprint linenums">
5
3 0
1 0
0 0
4 0
2 0
```

 ```
<pre class="prettyprint linenums">
4.000000
```

- 最も長い線分は点 $ 2 $ と点 $ 3 $ を繋ぐ線分で、その長さは $ 4.000000 $ です。
 
```
<pre class="prettyprint linenums">
4
2 2
0 0
1 1
3 3
```

 ```
<pre class="prettyprint linenums">
4.242641
```

- 最も長い線分は点 $ 1 $ と点 $ 3 $ を繋ぐ線分で、その長さは $ 4.242641 $ です。

# 题解

## 作者：sxtm12138 (赞：10)

这道题好像没有上面的dalao想得那么复杂，n<=100，就是枚举都只要几千次，只要暴力模拟，求出每两个点间的距离，找到最大值即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],b[105],n;
double t=0;//t记录最大距离
int main()
{cin>>n;//读入点个数
 for(int i=1;i<=n;i++) cin>>a[i]>>b[i];//读入点坐标
 for(int i=1;i<=n-1;i++)
   for(int j=i+1;j<=n;j++)//枚举任意两个点 
     t=max(t,sqrt((a[i]-a[j])*(a[i]-a[j])+(b[i]-b[j])*(b[i]-b[j])));//使用距离公式
 printf("%.3lf",t);//输出
return 0;
}
```

---

## 作者：Siyuan (赞：4)

### 一道简单的数论题。

平面上两点距离公式：$dis=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$

因为$\ N$的范围很小，因此枚举所有点即可，若发现距离小于当前已知答案，则更新答案。

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
 
int n,x[101],y[101];
double ans;
 
inline double dis(const int i,const int j)
{
    int xx=x[i]-x[j],yy=y[i]-y[j];
    return sqrt(xx*xx+yy*yy);
}
inline double max(const double a,const double b)
{
    return a>b?a:b;
}
int main()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;i++)
        scanf("%d%d",&x[i],&y[i]);
    for(register int i=1;i<n;i++)
        for(register int j=i+1;j<=n;j++)
            ans=max(ans,dis(i,j));
    printf("%.6f",ans);
    return 0;
}
```

---

## 作者：hwk0518 (赞：4)

旋转卡壳的裸题。

显然最远点对一定在覆盖n个点的凸包上。Graham求出凸包后一遍旋转卡壳即可。

~~n<=100不是随便过吗？~~

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const double eps=1e-6;
int N,top;
struct node
{
	double x,y;
};
node n[100005],dot[100005];

double dis(node a,node b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double S(node a,node b,node c)
{
	node X,Y;
	X.x=b.x-a.x;
	X.y=b.y-a.y;
	Y.x=c.x-a.x;
	Y.y=c.y-a.y;
	return fabs(X.x*Y.y-X.y*Y.x);
}

bool my_comp(node a,node b)
{
	double X=(a.x-n[1].x)*(b.y-n[1].y);
	double Y=(a.y-n[1].y)*(b.x-n[1].x);
	double Z=X-Y;
	if(fabs(Z)<=eps)
		if(dis(n[1],a)<dis(n[1],b)) return true;
		else return false;
	else
		return Z>0?true:false;
}

void init()
{
	int i;
	scanf("%d",&N);
	for(i=1;i<=N;++i) scanf("%lf%lf",&n[i].x,&n[i].y);
}

bool ok(int i)
{
	double X=(dot[top].x-dot[top-1].x)*(n[i].y-dot[top-1].y);
	double Y=(dot[top].y-dot[top-1].y)*(n[i].x-dot[top-1].x);
	if(X-Y<eps) return true;
	else return false;
}

void graham()
{
	int i,j;
	
	for(i=2;i<=N;++i)
		if(n[i].y-n[1].y<eps||fabs(n[i].y-n[1].y)<eps&&n[i].x-n[1].x<eps)
		{
			swap(n[i].x,n[1].x);
			swap(n[i].y,n[1].y);
		}
	sort(n+2,n+N+1,my_comp);

	dot[0]=n[1],dot[1]=n[2];
	top=1;
	for(i=3;i<=N;++i)
	{
		while(top>0&&ok(i)) --top;
		dot[++top]=n[i];
	}
}

double rotate()
{
	double ret=0.0;
	int i,j;
	
	j=2;++top;
	for(i=0;i<top;++i)
	{
		while(S(dot[i],dot[(i+1)%top],dot[j])<S(dot[i],dot[(i+1)%top],dot[(j+1)%top]))
			j=(j+1)%top;
		ret=max(ret,dis(dot[j],dot[i]));
		ret=max(ret,dis(dot[j],dot[(i+1)%top]));
	}
	
	return ret;
}
int main()
{
//	freopen("dotfar.in","r",stdin);
//	freopen("dotfar.out","w",stdout);
	
	init();
	graham();
	printf("%.6lf\n",rotate());
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}

```

---

## 作者：小小小朋友 (赞：3)

#### 废话

备战初赛，考完一登洛谷就看到我掉蓝了……难受，赶快写题解补回去……

#### 题目描述

翻译找都找不到……

没有样例吗？

给出一堆点，求它们之间的欧几里得距离中的最小值

#### 思路简介

这里主要是给大家介绍一下cmath库的几个有意思的函数:`pow(a,b)`用来求$a^b$与`sqrt(a)`用来求$\sqrt{a}$

然后就很简单了，枚举两点之间距离，取最大值输出即可

解释看代码。

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
double x[1000],y[1000],ans=0;
ll n;
inline double dis(int a,int b){//求距离函数
	return sqrt(pow(x[a]-x[b],2)+pow(y[a]-y[b],2));//使用了sqrt与pow函数
}
int main(){
	scanf("%lld",&n);//输入
	for(int i=0;i<n;i++) scanf("%lf%lf",&x[i],&y[i]);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			ans=fmax(ans,dis(i,j));//求最大距离
		}
	}
	printf("%.03lf",ans);//输出答案，注意取3位小数
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：2)

**求平面上的两点的距离公式：dis = sqrt(（x1 - x2）^2 + (y1 - y2) ^ 2)//sqrt平方根**

**然后只要任意两点求距离然后保存最大值，最后输出即可，上代码！注意：数据类型double**

```
#include <iostream>
#include <cmath>
using namespace std;
int main() 
{
	int n,a[105],b[105];
	double ans = 0;
	cin>>n;
	for(int i = 1;i <= n;i++) cin>>a[i]>>b[i];
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= i;j++) 
			ans = max(ans,sqrt(pow(a[i] - a[j],2) + pow(b[i] - b[j],2)));
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：ShineEternal (赞：1)

## description：
给定n个点，求出两点之间最短距离

## solution：
观察数据范围，发现$n\leq100$，所以之间$O(n^2)$暴力即可。

这里要注意不要丢失精度，于是就全开double，最后输出6位就行了

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
double sqr(double x)
{
	return x*x; 
}
double x[1005],y[1005];
int main()
{
	double n;
	double ans=0;
	scanf("%lf",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&x[i],&y[i]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			ans=max(ans,sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])));
		}
	} 
	printf("%.6lf\n",ans);
	return 0;
} 
```

---

## 作者：不到前10不改名 (赞：1)

暴力枚举纯粹c风格，已经加上防伪标识
```
#include<stdio.h>
int n,srx[101],sry[101],i,j;
double lhy;
double lgx(int i,int j)
{
    int mzy=srx[i]-srx[j],zjq=sry[i]-sry[j];//mzy，zjq分别为三角形两边长
    return sqrt(mzy*mzy+zjq*zjq);//因为在坐标系中，所以是直角三角形，利用勾股定理，易得第三边，也就是两点之间的距离
}
double max(double a,double b)
{
    return a>b?a:b;//三目一元运算符
}
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    scanf("%d%d",&srx[i],&sry[i]);
    for(i=1;i<n;i++)
    for(j=i+1;j<=n;j++)
    lhy=max(lhy,lgx(i,j));//连个max都要手打的纯c党
    printf("%.1f",lhy);//注意位数
    return 0;
}
```

---

## 作者：Soyilieber (赞：1)

和楼下思想一样，都是用的平面上两点间距离公式sqrt((x1−x2)2+(y1−y2)2)

*pas代码：*
```pascal
var
    i,j,n:longint;
    x,y:array[1..100]of longint;
    ans:real;
begin
    readln(n);
    for i:=1 to n do
        readln(x[i],y[i]);
    for i:=1 to n-1 do
        for j:=i+1 to n do
            if sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))>ans then ans:=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
    writeln(ans:0:6);//只能有0.001的误差，注意开场宽
end.
```

---

