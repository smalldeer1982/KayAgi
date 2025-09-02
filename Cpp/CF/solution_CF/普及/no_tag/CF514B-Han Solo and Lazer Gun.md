# Han Solo and Lazer Gun

## 题目描述

There are $ n $ Imperial stormtroopers on the field. The battle field is a plane with Cartesian coordinate system. Each stormtrooper is associated with his coordinates $ (x,y) $ on this plane.

Han Solo has the newest duplex lazer gun to fight these stormtroopers. It is situated at the point $ (x_{0},y_{0}) $ . In one shot it can can destroy all the stormtroopers, situated on some line that crosses point $ (x_{0},y_{0}) $ .

Your task is to determine what minimum number of shots Han Solo needs to defeat all the stormtroopers.

The gun is the newest invention, it shoots very quickly and even after a very large number of shots the stormtroopers don't have enough time to realize what's happening and change their location.

## 说明/提示

Explanation to the first and second samples from the statement, respectively:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514B/e0665254dc28c85d59225f8c53a8542938957367.png)

## 样例 #1

### 输入

```
4 0 0
1 1
2 2
2 0
-1 -1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 1 2
1 1
1 0
```

### 输出

```
1
```

# 题解

## 作者：亦枫 (赞：5)

**Solution**
------------

看到这道题，再看到这个图

![](https://cdn.luogu.org/upload/vjudge_pic/CF514B/e0665254dc28c85d59225f8c53a8542938957367.png)

 **可以发现一条直线上的恐怖分子斜率相同，只要求出斜率的个数，就得出了答案**

 但要注意：在横坐标为 $ 0 $ 的情况时要特判


下面附上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
long double x, y;
double a,b;//好像开long double会炸，注意一下
int n;
set< long double> s;//set表示集合，集合有这内部元素不重复的性质
int main() {
	cin>>n>>x>>y;
	for (register int i=1; i<=n; ++i) {
		scanf("%lf %lf",&a,&b);
		a-=x,b-=y;
		if(a!=0)s.insert(b/a);//特判
		if(a==0)s.insert(1e9);
	}
	cout<<s.size();//因为内部元素不重复，所以求出集合内元素个数即可。
}
```


---

## 作者：to_be_continued (赞：5)

##### ~~这题其实有点水~~

刚开始我被卡进去了，用了个数组存下所有的坐标，然后一看数据范围，em

其实可以发现的一点是，如果把枪的位置当做原点的话，这个恐怖分子只有两种情况

#### 一，被先前的枪打中了
#### 二，就算没有被之前的枪打中，那就给他来上一~~超炮~~

那么这个问题就转换成为了这两个点是否是在同一条直线上。

我介绍一种比较麻烦的方法

#### 如果这两个点是在一条线上的话，那么他们除去他们的最大公倍数也一定是一样的。例如样例1
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514B/e0665254dc28c85d59225f8c53a8542938957367.png)
#### 那三个人是在同一条直线的，他们的除去他们的最大公倍数都是1 1。说的准确一点就是，因为他们都是从原点扩展出来的，连起来是一个经过原点的一次函数。所以说如果他们除去他们的最大公倍数后一样，那么他们就在同一条直线上。

#### 以上是斜线 ， 直线就比较好判断了，如果行是0，那么去前面几条线中，找到一条行也是0的。列也是一样。

```cpp
#include <cstdio>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

struct aa{
	int x,y;
} a[1000];//x表示行，y表示列

int gcd(int x,int y){//加特判的gcd应该看得懂吧
	if (x==0||y==0) return 1;//因为可能会出现0的特殊情况所以要进行特判。
	return x%y==0?y:gcd(y,x%y);
}


void sj(int x,int y,int &z){
	if (x==0){//如果行是0，那么只需要去找一个行也是0 的直线就好了
		for (int i=1;i<=z;i++){
			if (a[i].x==0){
				return;
			}
		}
	} else if (y==0){//如果列是0，那么也只需要去找一个列也是0的直线就好了
		for (int i=1;i<=z;i++){
			if (a[i].y==0){
				return;
			}
		}
	} else
	for (int i=1;i<=z;i++){//不然的话就必须找到行列都相等的线
		if (a[i].x==x&&a[i].y==y){
			return;
		}
	}
	a[++z].x=x;
	a[z].y=y;//如果实在是找不到的话，就说明之前没有给他来一炮，那就补上。
}
int main(){
	int n,x,y;
	scanf("%d%d%d",&n,&x,&y);
	int ans=0;
	for (int i=1;i<=n;i++){
		int h,l;
		scanf("%d%d",&h,&l);
		h-=x;
		l-=y;//先把这个点放进这张图里，就必须以原点为中心
		int k=gcd(h,l);
		h/=k;
		l/=k;//约一约
		sj(h,l,ans);//进行直线判断
	}
	printf("%d",ans);
}
```

本人是见习C++，在此向各位C++巨爷致敬。

---

## 作者：伟大的王夫子 (赞：4)

我看到这道题，首先想着如何去处理共线。如果两个点与激光枪所在位置连成的直线斜率相同，那么激光枪以及这两个点共线，激光枪可以一炮直接轰死他们两个。如果有多个点共线，那么处理方法类似。

那么，经过我一番分析之后，我们可以将每个点与激光枪所在点的斜率算出，存入一个数组中，对这个数组排序，去重，数组剩下元素的个数就是所有点与激光枪所在点的不同斜率的数，这些斜率所对应的点不在一条直线上，那么当然一炮是直接轰不死的。

当然，去重我们可以不用数组去重，可以用 C++ 中的 STL
不可重集合，最后输出集合的大小。

最后，将代码给大家参考一下。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
long double x0, yc;
int n;
struct P {
	double x, y;
} a[1010];
set<long double> s;
int ans;
main() {
	cin >> n >> x0 >> yc;
	for (register int i = 1; i <= n; ++i) {
		scanf("%lf %lf", &a[i].x, &a[i].y); 
        a[i].x -= x0, a[i].y -= yc;
		if (a[i].x != 0)  s.insert(a[i].y / a[i].x);
		if (a[i].x == 0) s.insert(1e9);
	}
		
	cout << s.size();
}
```

ps:
数学知识

在平面直角坐标系中点 $(x1, y1)$ $(x2, y2)$ 的直线的斜率
为 $\dfrac{y2 - y1}{x2 -x1}$。

当 $x1=x2$ 时，为了方便，可认为斜率无限大。

在这里我们设这个值为 $10^9$，因为这已经够大了。

这题还有一个坑点，我将结构体 P 的 long double 换成 double 之后，反而可以 AC，而用 long double 貌似不能 AC。

---

## 作者：codemap (赞：4)

这道题刚开始不知道该怎么做,但是后来想了想发现这道题有个简单的做法:

# 以激光枪为坐标系原点,记录每个恐怖分子的斜率,最后排个序就做完了

注意当恐怖分子坐标横坐标=0时,因为不能除以0,要将斜率设为一个大数

没有什么可以说的,直接上代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n,i,s=0,t=1;//s是数组下标,t是答案计数器
    double x0,y0,x,y,a[1001];
    cin>>n>>x0>>y0;
    for(i=1;i<=n;i++)
    {
        cin>>x>>y;
        if(x0-x==0)//如果恐怖分子横坐标=0
            a[++s]=100000;//将斜率设为100000
        else//如果不等于0
            a[++s]=(y0-y)/(x0-x);//斜率=以激光枪为原点时的斜率
    }
    sort(a+1,a+s+1);//排序
    for(i=1;i<s;i++)//要小于s
        if(a[i]!=a[i+1])//如果这个斜率与下个斜率不等
            t++;//再发一炮
    cout<<t;//输出
    return 0;//结束
}
```
# 不要抄袭


---

## 作者：_weishiqi66_ (赞：3)

# 思路
看到这个题目，便可以很自然而然地想到，可以武器的坐标为顶点，建立一个平面直角坐标系。我们的每次攻击都是一条经过原点的直线，这不是就是正比例函数吗？这样问题就转化成给定 $n$ 个点，求这些点能形成多少个不同的正比例函数了。因此我们可以在线计算每个点所处的正比例函数，并记录，最后有记录了多少个不同的正比例函数就是我们的解。

# 实现
- 注意正比例函数 $y=kx$ 可能为小数。

# 代码
```
#include<bits/stdc++.h>
#define y0 ihatewhyy0asdifferentkindofsymbol
using namespace std;
const int N=1e6;
int n,x0,y0;
set<double> pd;
int main(){
	cin>>n>>x0>>y0;
	int ans=0;
	bool fx,fy;fx=fy=0;
	for(int i=1;i<=n;i++){
		int x,y,rx,ry;
		cin>>x>>y;
		x-=x0,y-=y0;
		if(x==0){
			if(fx==0) ans++;
			fx=1;
			continue;
		}	
		if(y==0){
			if(fy==0) ans++;
			fy=1;
			continue;
		}
		double tmp=(y*1.00)/(x*1.00);
		pd.insert(tmp);
	}
	cout<<ans+pd.size();
	return 0;
} 
```


---

## 作者：naroto2022 (赞：2)

# CF514B 题解

### 题意

有 $n$ 个恐怖分子，他们的位置都会给出，现在有一个激光枪在 $(x_0,y_0)$，激光枪每一发子弹都可以打~~死~~这一条直线上的恐怖分子，问至少要开几枪。

### 思路

其实总体思路很简单，先求每一个恐怖分子关于激光枪的斜率（斜率 $=(y_0-y)\div(x_0-x)$），但有两种情况：

1. $x_0-x=0$，因为分母不可以为 $0$，所以斜率就随便设一个大数。
2. $x_0-x\neq0$，那就用正常的公式：斜率 $=(y_0-y)\div(x_0-x)$。

等我们求完所有的斜率并记录在一个数组 $a$ 之中之后，就需要看看恐怖分子最少会组成几条直线，我们都知道，斜率相等的两个点在一条直线上，所以只要将 $a$ 从小到大（或从大到小）排序，则这样在同一条直线上的恐怖分子就排在一起了，所以只要一个个遍历过去，要是后面一个不等于前面那个，那么就要多打一枪。

注：一开始打的枪数要等于 $1$。

### 总结

1. 一次函数：斜率。
2. 特殊情况判断。
3. 排序去重。
4. 初始赋值。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>//快排要用。 
using namespace std;
int n,x0,y0,x,y,ans=1;
double a[1005];
//变量名如题。 
//a数组是记录每个恐怖分子关于激光枪的斜率。
//ans表示要开几枪。 
int main(){
	scanf("%d %d %d",&n,&x0,&y0);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&x,&y);
		if(x0-x==0) a[i]=2147483647;//因为分母不能为0，所以就随便设一个大数。
		else a[i]=(double)(y0-y)/(x0-x);//求以激光枪为原点恐怖分子的斜率。 
	}
	sort(a+1,a+1+n);//排一下序，这样在同一条直线上的恐怖分子就排在一起了。 
	for(int i=2; i<=n; i++)
		if(a[i]!=a[i-1])//后面的恐怖分子不和前面的在一条直线上，也就是在新一条直线上。
			ans++;//也就是要再开一枪打这条直线上的恐怖分子。
	printf("%d",ans); 
	return 0;
}
```


---

## 作者：极寒神冰 (赞：1)

按照题意模拟。

对于每一个恐怖分子算出斜率。（注意要特判横坐标为0的情况）

之后排序去重，剩下的元素个数即为答案

---

## 作者：shenbairui (赞：0)

### 题目大意
有 $n$ 个恐怖分子，题目会给出他们的位置，现在有一把激光枪在 $(x_0,y_0)$，激光枪每一发子弹都可以打死这一条直线上的恐怖分子，问至少要开几枪。
### 题目分析
我们可以先看这两张图：

![](https://cdn.luogu.org/upload/vjudge_pic/CF514B/e0665254dc28c85d59225f8c53a8542938957367.png)

不难发现同一条直线上的所有恐怖分子的斜率是相同，只要求出斜率的个数，就等于得出了答案。这里我懒得排序去重所以直接用集合。

不知道斜率的可以看这里[这里](https://baike.baidu.com/item/%E6%96%9C%E7%8E%87/4914111?fr=ge_ala)已经讲得很清楚了。

你以为就结束了吗？不，还要去特判 $x$ 坐标为 $0$ 的情况和精度的问题！
### 代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
long double x, y, a, b;
int n;
set<long double> s;
signed main() {
	cin >> n >> x >> y;
	for ( int i = 1; i <= n; ++i) {
		cin >> a >> b;
		a -= x, b -= y;
		if (a != 0) s.insert(b / a);
		if (a == 0) s.insert(1e9);
	}
	cout << s.size();
}
```

[AC记录](https://codeforces.com/contest/514/submission/282459701)

下期见！拜拜！

---

