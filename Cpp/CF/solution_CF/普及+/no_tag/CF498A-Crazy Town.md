# Crazy Town

## 题目描述

求与线段AB（你家与学校连线）相交的直线数量

## 说明/提示

1≤n≤300;
106≤ai​,bi​,ci​≤106;∣ai​∣+∣bi​∣>0;

## 样例 #1

### 输入

```
1 1
-1 -1
2
0 1 0
1 0 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 1
-1 -1
3
1 0 0
0 1 0
1 1 -3
```

### 输出

```
2
```

# 题解

## 作者：ModestCoder_ (赞：4)

跟实数运算有关的题目做起来总是很方。。。

就是求多少条直线跟线段有交点

针对每条直线求出解析式

$ax+by+c=0-->y=-\frac{a}{b}x-\frac{c}{b}$

$x1,x2$代进去，只要两个对应值和$y1,y2$大小关系不一样即说明有交点

特判$b=0$的情况，此时直线方程是$x=-\frac{c}{a}$

此时判断$x$是否∈$[x1,x2](x1<x2)$即可

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int x1, x2, Y1, y2, n;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main(){
	x1 = read(), Y1 = read(), x2 = read(), y2 = read(), n = read();
	if (x1 > x2) swap(x1, x2), swap(Y1, y2);
	int ans = 0;
	while (n--){
		int a = read(), b = read(), c = read();
		if (!b){
			double x = 1.0 * (-c) / a;
			ans += (x1 <= x) && (x2 >= x) ;
		} else{
			double k = 1.0 * (-a) / b, B = 1.0 * (-c) / b;
			double fx1 = k * x1 + B, fx2 = k * x2 + B;
			ans += (fx1 > Y1) != (fx2 > y2);
		}
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：osfly (赞：1)

简单解析几何。

做这道题之前，你需要知道：

1. 根据两点求直线一般式。

2. 根据两条直线求交点坐标。

这里直接丢公式了，百度上也有证明过程，自己推导难度也不大。

1. 若两点坐标为 $(x_1,y_1),(x_2,y_2)$，则直线方程为：$Ax+By+C=0$，其中 $A=y_2-y_1,B=x_1-x_2,C=x_2y_1-x_1y_2$。

2. 若两条直线方程为 $A_1\ x+B_1\ y+C=0,A_2\ x+B_2\ y+C=0$，若 $A_1B_2=A_2B_1$ 则两直线平行，否则这两条直线有交点为 $\Large (\frac{C_2B_1-C_1B_2}{A_1B_2-A_2B_1},\frac{C_1A_2-C_2A_1}{A_1B_2-A_2B_1})$。

那直接暴力把每条直线的交点求出来，判断是否在 $(x_1,y_1),(x_2,y_2)$ 所围成的矩形区域的范围内就可以了，要特判两条直线平行的情况，这里 $(x_1,y_1),(x_2,y_2)$ 指的是学校和家两点的坐标。记得先判断 $x_1$ 和 $x_2$，$y_1$ 和 $y_2$ 之间的大小关系。

为了避免实数比大小，可以把交点的分母移到不等式另外一边，但是要注意分母正负对不等号方向的影响。

观察到坐标范围能到 $10^6$，如果两个坐标相乘可能能到达 $10^{12}$，所以记得开 `ll`。

```cpp
#include<cstdio>
#define ll long long
ll x1,y1,x2,y2;
ll A,B,C;
int n,cnt;
ll a,b,c;
ll fm,x,y;
int main()
{
	scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
	A=y2-y1,B=x1-x2,C=x2*y1-x1*y2;
	if(x2<x1)
	{
		int t=x2;
		x2=x1;
		x1=t;
	}
	if(y2<y1)
	{
		int t=y2;
		y2=y1;
		y1=t;
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&a,&b,&c);
		fm=A*b-a*B,x=c*B-C*b,y=C*a-c*A;
		if(fm==0) continue;
		if(fm>0&&x1*fm<=x&&x<=x2*fm&&y1*fm<=y&&y<=y2*fm) cnt++;
		if(fm<0&&x1*fm>=x&&x>=x2*fm&&y1*fm>=y&&y>=y2*fm) cnt++;
	}
	printf("%d",cnt);
	return 0;
}
```

---

## 作者：enyyyyyyy (赞：1)

- 思路：
  数学几何题！求每条直线跟每条线段有几个交点，是否大于 $0$，再将条直线跟每条线段有的交点大于 $0$ 的结果异或一下，如果方程成立，就把答案加一，所以针对每条直线求出方程。

- 方程：
  $$ [a\times X_1+b\times Y_1+c>0]⊕[a\times X_2+b\times Y_2+c>0] $$ 

- 所以 ACcode：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {//快读 
    ll s = 0,w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
    return s * w;
}
inline void print(ll x)//快输 
{
    if(x < 0)
    {
        putchar('-');
        x = -x;
    }
    if(x>=10) print(x/10);
    putchar(x%10+'0');
    return;
}
ll X1,X2,Y1,Y2,a,b,c,n,ans;
int main(){
	X1=read(),Y1=read(),X2=read(),Y2=read(),n=read();//输入 
    while(n--){
        a=read(),b=read(),c=read();
        //方程： a*X1+b*Y1+c>0^a*X2+b*Y2+c>0
        if(a*X1+b*Y1+c>0^a*X2+b*Y2+c>0)++ans;//如果满足方程 统计答案 
    }
    print(ans);//输出 
    return 0;
}
```


---

## 作者：GFyyx (赞：1)

## 解题思路
解析几何！

题意说得很明显了。
当 $b \neq 0$ 时，有 $x_i = -\frac{c}{a}$，直线平行于纵轴，$x_1 \leq x_i \leq x_2$ 即成立。

否则由 $ax_i + by_i + c = 0$ 得 $y_i = -(\frac{a}{b}x + \frac{c}{b})$。

## AC Code
```cpp
#include <iostream>
#include <math.h>
#define y1 YYXgf2009
//撞变量名 
#define int double
//实数 
using namespace std;
int x1,x2,y1,y2,n,ans;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	cin >> x1 >> y1 >> x2 >> y2 >> n;
	if (x1>x2) swap(x1,x2),swap(y1,y2);
	while(n--){
		int a,b,c;
		cin >> a >> b >> c;
		if(!b){
			int k=-c/a;
			if((x1<=k)&&(x2>=k)) ans++;
		}//特殊处理b=0,直线平行于x轴。 
		else{
			int k1=-a/b,k2=-c/b;
			int f1=k1*x1+k2,f2=k1*x2+k2;
			if((f1>y1)!=(f2>y2)) ans++;
		}//y=-(a/b.x+c/b) 
	}
	cout << ans << endl;
	return 0;
}

```


---

## 作者：dutianchen1 (赞：0)

# CF498A Crazy Town

## 题意翻译

给定一条线段的两点，再给出 $n$ 条直线的解析式，求这条线段共与多少条直线相交。

## 思路简析

这里提供两种做法，一种是简单的模拟，一种是需要利用一定几何知识的做法。

- 做法一：
  分别计算出线段和所有直线的斜率和截距。将每一条直线与线段进行**相交判定**。其中，对于线段和直线的斜率竖直或水平的条件进行特判即可。

  思路较为简单，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const double inf = 1e9+7;
struct node{
	double k,bb;
}mp[N],AB;
double x,y,X,Y;
double a,b,c;
ll n,ans;
int main()
{
	cin.tie(0);cout.tie(0);
	cin>>x>>y;
	cin>>X>>Y;
	cin>>n;
	AB.k=(x-X==0)?inf:(y-Y)/(x-X);
	AB.bb=(x-X==0)?x:Y-AB.k*X;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b>>c;
		if(b==0)
		{
			mp[i].k=inf;mp[i].bb=-(c/a);
			continue;
		}
		mp[i].k=-(a/b);
		mp[i].bb=-(c/b);
	}	
	for(int i=1;i<=n;i++)
	{
		double xx,yy;
		if(mp[i].k==AB.k)
		{
			continue;
		}
		if(mp[i].k==inf*1.0)
		{
			if(max(x,X)>=mp[i].bb&&min(x,X)<=mp[i].bb&&max(y,Y)>=AB.k*mp[i].bb+AB.bb&&min(y,Y)<=AB.k*mp[i].bb+AB.bb) ans++;
			continue;
		}
		if(AB.k==inf*1.0)
		{
			if(max(x,X)>=AB.bb&&min(x,X)<=AB.bb&&max(y,Y)>=mp[i].k*AB.bb+mp[i].bb&&min(y,Y)<=mp[i].k*AB.bb+mp[i].bb) ans++;
			continue;
		}
		xx=(mp[i].bb-AB.bb)/(AB.k-mp[i].k);
		yy=(AB.k*xx+AB.bb);
		if(max(x,X)>=xx&&min(x,X)<=xx&&max(y,Y)>=yy&&min(y,Y)<=yy)ans++;
	}
	cout<<ans<<'\n';
	return 0;
}
```


- 做法二：
  考虑分析两线相交的**几何意义**。我们考虑对坐标系进行平移与旋转，使得给出的直线 $ a \times x + b \times y + c $ 成为 $y=0$ 的直线，将线段两端点带入直线，可以算出相对的 $y$ 坐标，只需要判断计算出来的 $y$ 坐标是否在直线 $y=0$ 两侧即可。思路较为复杂，不过代码好写。代码如下：

  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+5;

inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
double xa,ya,xb,yb;
int main()
{
	cin.tie(0);cout.tie(0);
	cin>>xa>>ya>>xb>>yb;
	ll ans=0;
	ll n=read();
	for(int i=1;i<=n;i++)
	{
		double a,b,c;
		cin>>a>>b>>c;
		double t1=a*xa+b*ya+c,t2=a*xb+b*yb+c;
		if(t1*t2<0) ans++;
	}
	cout<<ans<<'\n';
	return 0;
}


```

---

