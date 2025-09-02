# Happy Farm 5

## 题目描述

The Happy Farm 5 creators decided to invent the mechanism of cow grazing. The cows in the game are very slow and they move very slowly, it can even be considered that they stand still. However, carnivores should always be chased off them.

For that a young player Vasya decided to make the shepherd run round the cows along one and the same closed path. It is very important that the cows stayed strictly inside the area limited by the path, as otherwise some cows will sooner or later be eaten. To be absolutely sure in the cows' safety, Vasya wants the path completion time to be minimum.

The new game is launched for different devices, including mobile phones. That's why the developers decided to quit using the arithmetics with the floating decimal point and use only the arithmetics of integers. The cows and the shepherd in the game are represented as points on the plane with integer coordinates. The playing time is modeled by the turns. During every turn the shepherd can either stay where he stands or step in one of eight directions: horizontally, vertically, or diagonally. As the coordinates should always remain integer, then the length of a horizontal and vertical step is equal to $ 1 $ , and the length of a diagonal step is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50C/2826342a15affce70e459206e8466cd2b66552a3.png). The cows do not move. You have to minimize the number of moves the shepherd needs to run round the whole herd.

## 说明/提示

Picture for the example test: The coordinate grid is painted grey, the coordinates axes are painted black, the cows are painted red and the sought route is painted green.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50C/8b34e942d3e45fab9f6a1a087e0ce5cc6f58c465.png)

## 样例 #1

### 输入

```
4
1 1
5 1
5 3
1 3
```

### 输出

```
16
```

# 题解

## 作者：hjsxhst2022 (赞：1)

[原题](https://www.luogu.com.cn/problem/CF50C)
### 题意
给你 $n (1 \le n \le 10^5)$ 个在整数位置上的点，求包围所有点的最短路径需要的步数。每一步可以走到原位置的上、下、左、右、左上、左下、右上、右下。要求点不能在包围的路径上。

### 思路
做这道题之前建议先做[这道凸包模版题](https://www.luogu.com.cn/problem/P2742)。

既然提到凸包，那肯定要用凸包。

那什么是凸包？

凸包（Convex Hull）是一个计算几何中的概念。

在一个实数向量空间 $V$ 中，对于给定集合 $X$ ，所有包含 $X$ 的凸集的交集 $S$ 被称为 $X$ 的凸包。 $X$ 的凸包可以用 $X$ 内所有点 $(x_1,x_2, x_3.....x_n)$ 的凸组合来构造.

在二维欧几里得空间中，凸包可想象为一条刚好包含所有点的橡皮圈。

用不严谨的话来讲，给定二维平面上的点集，凸包就是将最外层的点连接起来构成的凸多边形，它能包含点集中所有的点。

用严谨的话来讲，凸包就是对于一个集合 $D$ ， $D$ 中任意有限个点的凸组合的全体称为 $D$ 的凸包。

那这题和凸包有什么关系？

题目说要划出一条最短路径包含所有点，这就和凸包的定义非常像。考虑我们已经选出了点集 $D$ ，用线将这些点一连，所有的点就全部包含在内了。

那么如何算凸包呢？

Graham 扫描法。

#### 过程
1. 在所有点中选取 $y$ 坐标最小的一点 $H$ ，当作基点。如果存在多个点的 $y$ 坐标都为最小值，则选取 $x$ 坐标最小的一点。坐标相同的点应排除。然后按照其它各点 $p$ 和基点构成的向量 $<H,p>$ ；与 $x$ 轴的夹角进行排序，夹角由大至小进行顺时针扫描，反之则进行逆时针扫描。实现中无需求得夹角，只需根据余弦定理求出向量夹角的余弦值即可。下面进行逆时针扫描。

2. 线段$<H,K>$；一定在凸包上，接着加入 $C$ 。假设线段$<K,C>$；也在凸包上，因为就 $H$ ，$K$， $C$ 三点而言，它们的凸包就是由此三点所组成。但是接下来加入 $D$ 时会发现，线段$<K,D>$；才会在凸包上，所以将线段$<K,C>$；排除， $C$ 点不可能是凸包。

3. 当加入一点时，必须考虑到前面的线段是否在凸包上。从基点开始，凸包上每条相临的线段的旋转方向应该一致，并与扫描的方向相反。如果发现新加的点使得新线段与上线段的旋转方向发生变化，则可判定上一点必然不在凸包上。实现时可用向量叉积进行判断，设新加入的点为，上一点为，再上一点为。顺时针扫描时，如果向量与的叉积为正（逆时针扫描判断是否为负），则将上一点删除。删除过程需要回溯，将之前所有叉积符号相反的点都删除，然后将新点加入凸包。


#### 复杂度

这个算法可以直接在原数据上进行运算，因此空间复杂度为 $O(1)$ 。但如果将凸包的结果存储到另一数组中，则可能在代码级别进行优化。由于在扫描凸包前要进行排序，因此时间复杂度至少为快速排序的 $O(n\log(n))$ 。后面的扫描过程复杂度为 $O(n)$ ，因此整个算法的复杂度为 $O(n \log(n))$。不会超时。

---

## 作者：Cure_Wing (赞：0)

[题目](https://www.luogu.com.cn/problem/CF50C)

### 解析
看到这题就想到了[二维凸包](https://www.luogu.com.cn/problem/P2742)。

什么是凸包？

用不严谨的话来讲，给定二维平面上的点集，凸包就是将最外层的点连接起来构成的凸多边形，它能包含点集中所有的点。

比如，

![](https://img0.baidu.com/it/u=1940414835,2004815361&fm=253&fmt=auto&app=138&f=JPEG?w=600&h=300)

点 $(p_0,p_1,p_3,p_{10},p_{12})$ 就是凸包的点集。

那这题和凸包有什么关系呢？

题意大概是这样的：用一条线围出一个区间，使其包含平面内的给定点，但点不能在线上。线可以出现在正方形网格的边和对角线上。

这似乎和凸包的定义非常像。考虑我们已经选出了这个凸包的点集，用满足条件的线将这些点一连，所有的点就全部包含在内了。

如果把这个点集往里收，就会导致有点被忽略的情况，就不满足要求了。

这个时候就需要考虑怎么算凸包上相邻两点的距离了。

考虑线是可以沿对角线走的，这样一定是最快的，然后走直线补齐差价就可以了。假设两点为 $(x_1,y_1)$ 和 $(x_2,y_2)$，那么两点间的路程为 $max\{|x_1-x_2|,|y_1-y_2|\}$。

那么如何算凸包呢？

Graham 扫描法：
1. 找出 坐标最小的点，若有多个，找出 坐标最小的点。
2. 将其作为原点进行极角排序。
3. 将这个点和排序所得的第一个点放入栈，然后用单调栈维护斜率单调点，扫描一遍，最后在单调栈里的点即为所求。

回到这道题目，由于不能过这个点，我们就考虑过离他们最近的点，即上下左右四个点。如果要过右上的点，那么把右边的点和上面的点相连，所用的长度比先前的一定短且符合题意。

这样我们就可以建出原来的点周围的四个点，以这些点为点求凸包，这个凸包一定是满足要求的。

用 Graham 求凸包需要注意一点，要去重点，不然会超时。

接下来我知道你们想要看什么。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
using std::cin;using std::cout;
constexpr int N=100005,K=1e7;
int n,x,y,cnt,now;
double Ans;
struct Point{
	double x,y;
	Point(double X=0,double Y=0){
		x=X,y=Y;
	}
}p[N<<2],ans[N<<2];
std::map<int,std::map<int,bool> >q;
typedef Point Vector;
inline Vector operator -(Point a,Point b){
	return Vector(a.x-b.x,a.y-b.y);
}
inline double Cross(Vector a,Vector b){//叉积
	return a.x*b.y-a.y*b.x;
}
inline double dis(Point a,Point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline bool cmp(Point a,Point b){
	double check=Cross(a-p[1],b-p[1]);
	return (check>0||check==0&&dis(p[0],a)<=dis(p[0],b));
}
inline double Dis(Point a,Point b){
	return std::max(std::fabs(a.x-b.x),std::fabs(a.y-b.y));
}
signed main(){
// 	freopen("T1.in","r",stdin);
// 	freopen("T1.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>x>>y;//x+=K;y+=K;
		if(!q[x][y]){
			p[++cnt]=(Point){x+1,y};
			p[++cnt]=(Point){x-1,y};
			p[++cnt]=(Point){x,y+1};
			p[++cnt]=(Point){x,y-1};
		}
		q[x][y]=1;//去重点。
	}
	for(int i=2;i<=cnt;++i)
		if(p[i].y<p[1].y||p[i].y==p[1].y&&p[i].x<p[1].x) std::swap(p[1],p[i]);
	std::sort(p+2,p+cnt+1,cmp);//按极角排序
	// cout<<'\n';
	// for(int i=1;i<=cnt;++i) cout<<p[i].x<<' '<<p[i].y<<'\n';
	ans[++now]=p[1];//求凸包
	for(int i=2;i<=cnt;++i){
		while(now>=2&&Cross(ans[now]-ans[now-1],p[i]-ans[now])<=0) --now;
		ans[++now]=p[i];
	}
	ans[now+1]=p[1];//cout<<'\n';
	for(int i=1;i<=now;++i) Ans+=Dis(ans[i],ans[i+1]);//,cout<<ans[i].x<<' '<<ans[i].y<<'\n';
    //计算长度
	cout<<(int)Ans;
	return 0;
}
```

---

## 作者：tonyre (赞：0)

# CF50C Happy Farm 5

## 1 题意

给你 $n(1\le n\le 10^5)$ 个**整数点**，求严格包围所有点的路径最少要移动多少步。每一步可以走到原位置的上、下、左、右、左上、右上、左下、右下。**严格包围要求点不能在路径上。**

## 2 题解

很容易想到这题可以使用凸包。

### 2.1 前置知识

首先了解一下相关概念。

> 在平面上能包含所有给定点的最小凸多边形叫做凸包。
>
> 其定义为：**对于给定集合 $X$，所有包含 $X$ 的凸集的交集 $S$ 被称为 $X$ 的凸包**。
>
> 凸包用最小的周长围住了给定的所有点。如果一个凹多边形围住了所有的点，它的周长一定不是最小，如下图。根据三角不等式，凸多边形在周长上一定是最优的。
>
> ——来自 [OI Wiki](https://oi-wiki.org/geometry/convex-hull/)。

很显然，此题需要求严格凸包（凸包上不存在点集中的点）。而一般的凸包题（[比如这个](https://www.luogu.com.cn/problem/P2742)）求的是非严格凸包。所以我们需要考虑将非严格凸包转化为严格凸包。

### 2.2 转化

**将每个点的上下左右都加入一个点，求加入后的凸包。**

由于都是整数点，这个方法使所有点都离凸多边形的顶点至少一个单位长度。

以样例为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/95qsk201.png)

### 2.3 实现

建议 A 了模板题再来。

和模板比起来，只有两点差别：

* 插入输入的点之外还要插入上下左右的点进入点集。很好实现，不过用 Graham 算法需要注意新加入的点也需要判断是否是坐标最靠下的起点。
* 两点间步数的计算。若有两点 $A(x_1,y_1),B(x_2,y_2)$，则两点间步数为 $\max( |x_1-x_2|,|y_1-y_2|)$。短的差距可以依靠斜着走来弥补，如图：![](https://cdn.luogu.com.cn/upload/image_hosting/xvaklus3.png)

该算法时间复杂度 $O(n \log n)$，由于时间限制为 $2s$，所以 $1\le n\le 10^5$ 情况下可以 AC 此题。

## 3 参考代码

使用 Graham 算法实现。

```C++
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXN=500005;
struct Point
{
    int x;
    int y;
}a[MAXN],s[MAXN];
int dis[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
bool cmp(Point x,Point y)
{
    if(x.y==a[1].y&&y.y==a[1].y) return x.x<y.x;
    if(x.y==a[1].y) return true;
    if(y.y==a[1].y) return false;
    if(x.x==a[1].x&&x.x==y.x) return x.y<y.y;
    if(1.0*(x.x-a[1].x)/(x.y-a[1].y)>1.0*(y.x-a[1].x)/(y.y-a[1].y)) return true;//注意需要浮点运算，我在这里挂了好久
    return false;
}
bool check(double x1,double y1,double x2,double y2,double x3,double y3)//判断是否左拐
{
    if((x2-x1)*(y3-y2)-(x3-x2)*(y2-y1)<=0) return true;
    return false;
}
int dist(int i,int j)
{
    return max(abs(s[i].x-s[j].x),abs(s[i].y-s[j].y));//两点距离
}
int main()
{
    int n;
    cin>>n;
    int cnt=n;
    double miny=1e9,minx=1e9;
    int first;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x>>a[i].y;
        if(a[i].y<miny||(a[i].y==miny&&a[i].x<minx))
        {
            miny=a[i].y;
            minx=a[i].x;
            first=i;
        }
        for(int j=0;j<4;j++)
        {
            cnt++;
            a[cnt].x=a[i].x+dis[j][0];
            a[cnt].y=a[i].y+dis[j][1];
            if(a[cnt].y<miny||(a[cnt].y==miny&&a[cnt].x<minx))
            {
                miny=a[cnt].y;
                minx=a[cnt].x;
                first=cnt;
            }
        }
    }
    n=cnt;
    swap(a[1],a[first]);
    sort(a+2,a+n+1,cmp);
    int top=1;
    s[top]=Point{a[1].x,a[1].y};
    for(int i=2;i<=n;i++)
    {
        while(top>1&&check(s[top-1].x,s[top-1].y,s[top].x,s[top].y,a[i].x,a[i].y)) top--;//模拟单调栈
        s[++top]=Point{a[i].x,a[i].y};
    }
    int sum=dist(1,top);
    for(int i=1;i<top;i++) sum+=dist(i,i+1);
    cout<<sum<<endl;
    return 0;
}
```

这道题似乎有更简单的解法，但我觉得凸包的解法也很有必要。~~主要是因为我不会证明那种解法。~~

---

## 作者：Ag2WO4 (赞：0)

打着凸包旗号的思维水题。本题解复杂度 $O(n)$ 是优于其他题解的，跑得也更快。

注意到：由于只有八个方向，最终的凸包一定是一个变形甚至退化的正八边形（边长可能为零）。如果没有领会请仔细观察下图，注意到红色、绿色、蓝色的线分别代表完整、变形、退化的正八边形。
![示意图](https://cdn.luogu.com.cn/upload/image_hosting/3zs88ybq.png)
我们关心构成这个八边形的重要的点，即八个方向最外侧线段的端点（可能重合）。记录下这些点的坐标，相邻点间距离为横坐标之差与纵坐标之差的最大值，绕圈求和即可。
#### C/C++
```c
#include<stdio.h>
int i,x,y,xa,ya,pa,ma,xaa,yaa,paa,maa,xia,yia,pia,mia,xi,yi,pi,mi,xai,yai,pai,mai,xii,yii,pii,mii;
int main()
{
    xa=ya=pa=ma=xaa=yaa=paa=maa=xia=yia=pia=mia=-(1<<30);xi=yi=pi=mi=xai=yai=pai=mai=xii=yii=pii=mii=1<<30;
    scanf("%d",&i);
    while(i--)
    {
        scanf("%d%d",&x,&y);
        ++x;
        if(x==xa){xaa=xaa>y?xaa:y;xai=xai<y?xai:y;}
    	if(x>xa){xa=x;xaa=xai=y;}
    	if(x==xi){xia=xia>y?xia:y;xii=xii<y?xii:y;}
    	if(x<xi){xi=x;xia=xii=y;}
    	if(y==ya){yaa=yaa>x?yaa:x;yai=yai<x?yai:x;}
    	if(y>ya){ya=y;yaa=yai=x;}
    	if(y==yi){yia=yia>x?yia:x;yii=yii<x?yii:x;}
    	if(y<yi){yi=y;yia=yii=x;}
    	if(x+y==pa){paa=paa>x?paa:x;pai=pai<x?pai:x;}
    	if(x+y>pa){pa=x+y;paa=pai=x;}
    	if(x+y==pi){pia=pia>x?pia:x;pii=pii<x?pii:x;}
    	if(x+y<pi){pi=x+y;pia=pii=x;}
    	if(x-y==ma){maa=maa>x?maa:x;mai=mai<x?mai:x;}
    	if(x-y>ma){ma=x-y;maa=mai=x;}
    	if(x-y==mi){mia=mia>x?mia:x;mii=mii<x?mii:x;}
    	if(x-y<mi){mi=x-y;mia=mii=x;}
    	x-=2;
    	if(x==xa){xaa=xaa>y?xaa:y;xai=xai<y?xai:y;}
    	if(x>xa){xa=x;xaa=xai=y;}
    	if(x==xi){xia=xia>y?xia:y;xii=xii<y?xii:y;}
    	if(x<xi){xi=x;xia=xii=y;}
    	if(y==ya){yaa=yaa>x?yaa:x;yai=yai<x?yai:x;}
    	if(y>ya){ya=y;yaa=yai=x;}
    	if(y==yi){yia=yia>x?yia:x;yii=yii<x?yii:x;}
    	if(y<yi){yi=y;yia=yii=x;}
    	if(x+y==pa){paa=paa>x?paa:x;pai=pai<x?pai:x;}
    	if(x+y>pa){pa=x+y;paa=pai=x;}
    	if(x+y==pi){pia=pia>x?pia:x;pii=pii<x?pii:x;}
    	if(x+y<pi){pi=x+y;pia=pii=x;}
    	if(x-y==ma){maa=maa>x?maa:x;mai=mai<x?mai:x;}
    	if(x-y>ma){ma=x-y;maa=mai=x;}
    	if(x-y==mi){mia=mia>x?mia:x;mii=mii<x?mii:x;}
    	if(x-y<mi){mi=x-y;mia=mii=x;}
    	++x;++y;
    	if(x==xa){xaa=xaa>y?xaa:y;xai=xai<y?xai:y;}
    	if(x>xa){xa=x;xaa=xai=y;}
    	if(x==xi){xia=xia>y?xia:y;xii=xii<y?xii:y;}
    	if(x<xi){xi=x;xia=xii=y;}
    	if(y==ya){yaa=yaa>x?yaa:x;yai=yai<x?yai:x;}
    	if(y>ya){ya=y;yaa=yai=x;}
    	if(y==yi){yia=yia>x?yia:x;yii=yii<x?yii:x;}
    	if(y<yi){yi=y;yia=yii=x;}
    	if(x+y==pa){paa=paa>x?paa:x;pai=pai<x?pai:x;}
    	if(x+y>pa){pa=x+y;paa=pai=x;}
    	if(x+y==pi){pia=pia>x?pia:x;pii=pii<x?pii:x;}
    	if(x+y<pi){pi=x+y;pia=pii=x;}
    	if(x-y==ma){maa=maa>x?maa:x;mai=mai<x?mai:x;}
    	if(x-y>ma){ma=x-y;maa=mai=x;}
    	if(x-y==mi){mia=mia>x?mia:x;mii=mii<x?mii:x;}
    	if(x-y<mi){mi=x-y;mia=mii=x;}
    	y-=2;
    	if(x==xa){xaa=xaa>y?xaa:y;xai=xai<y?xai:y;}
    	if(x>xa){xa=x;xaa=xai=y;}
    	if(x==xi){xia=xia>y?xia:y;xii=xii<y?xii:y;}
    	if(x<xi){xi=x;xia=xii=y;}
    	if(y==ya){yaa=yaa>x?yaa:x;yai=yai<x?yai:x;}
    	if(y>ya){ya=y;yaa=yai=x;}
    	if(y==yi){yia=yia>x?yia:x;yii=yii<x?yii:x;}
    	if(y<yi){yi=y;yia=yii=x;}
    	if(x+y==pa){paa=paa>x?paa:x;pai=pai<x?pai:x;}
    	if(x+y>pa){pa=x+y;paa=pai=x;}
    	if(x+y==pi){pia=pia>x?pia:x;pii=pii<x?pii:x;}
    	if(x+y<pi){pi=x+y;pia=pii=x;}
    	if(x-y==ma){maa=maa>x?maa:x;mai=mai<x?mai:x;}
    	if(x-y>ma){ma=x-y;maa=mai=x;}
    	if(x-y==mi){mia=mia>x?mia:x;mii=mii<x?mii:x;}
    	if(x-y<mi){mi=x-y;mia=mii=x;}
    }
    printf("%d",yaa-yai+yia-yii+xaa-xai+xia-xii+(ya+mi>yai?ya+mi:yai)-(pa-ya<yaa?pa-ya:yaa)+(pi-yi>yii?pi-yi:yii)-(ma+yi<yia?ma+yi:yia)+(xa>pa-xaa?xa:pa-xaa)+(xa>xai+ma?xa:xai+ma)-(xi<mi+xia?xi:mi+xia)-(xi<pi-xii?xi:pi-xii));
}
```
#### Python
```python
xa=ya=pa=ma=xaa=yaa=paa=maa=xia=yia=pia=mia=-1<<30;xi=yi=pi=mi=xai=yai=pai=mai=xii=yii=pii=mii=1<<30
for i in range(int(input())):
    x,y=map(int,input().split());x+=1
    if x==xa:xaa=max(xaa,y);xai=min(xai,y)
    if x>xa:xa=x;xaa=xai=y
    if x==xi:xia=max(xia,y);xii=min(xii,y)
    if x<xi:xi=x;xia=xii=y
    if y==ya:yaa=max(yaa,x);yai=min(yai,x)
    if y>ya:ya=y;yaa=yai=x
    if y==yi:yia=max(yia,x);yii=min(yii,x)
    if y<yi:yi=y;yia=yii=x
    if x+y==pa:paa=max(paa,x);pai=min(pai,x)
    if x+y>pa:pa=x+y;paa=pai=x
    if x+y==pi:pia=max(pia,x);pii=min(pii,x)
    if x+y<pi:pi=x+y;pia=pii=x
    if x-y==ma:maa=max(maa,x);mai=min(mai,x)
    if x-y>ma:ma=x-y;maa=mai=x
    if x-y==mi:mia=max(mia,x);mii=min(mii,x)
    if x-y<mi:mi=x-y;mia=mii=x
    x-=2
    if x==xa:xaa=max(xaa,y);xai=min(xai,y)
    if x>xa:xa=x;xaa=xai=y
    if x==xi:xia=max(xia,y);xii=min(xii,y)
    if x<xi:xi=x;xia=xii=y
    if y==ya:yaa=max(yaa,x);yai=min(yai,x)
    if y>ya:ya=y;yaa=yai=x
    if y==yi:yia=max(yia,x);yii=min(yii,x)
    if y<yi:yi=y;yia=yii=x
    if x+y==pa:paa=max(paa,x);pai=min(pai,x)
    if x+y>pa:pa=x+y;paa=pai=x
    if x+y==pi:pia=max(pia,x);pii=min(pii,x)
    if x+y<pi:pi=x+y;pia=pii=x
    if x-y==ma:maa=max(maa,x);mai=min(mai,x)
    if x-y>ma:ma=x-y;maa=mai=x
    if x-y==mi:mia=max(mia,x);mii=min(mii,x)
    if x-y<mi:mi=x-y;mia=mii=x
    x+=1;y+=1
    if x==xa:xaa=max(xaa,y);xai=min(xai,y)
    if x>xa:xa=x;xaa=xai=y
    if x==xi:xia=max(xia,y);xii=min(xii,y)
    if x<xi:xi=x;xia=xii=y
    if y==ya:yaa=max(yaa,x);yai=min(yai,x)
    if y>ya:ya=y;yaa=yai=x
    if y==yi:yia=max(yia,x);yii=min(yii,x)
    if y<yi:yi=y;yia=yii=x
    if x+y==pa:paa=max(paa,x);pai=min(pai,x)
    if x+y>pa:pa=x+y;paa=pai=x
    if x+y==pi:pia=max(pia,x);pii=min(pii,x)
    if x+y<pi:pi=x+y;pia=pii=x
    if x-y==ma:maa=max(maa,x);mai=min(mai,x)
    if x-y>ma:ma=x-y;maa=mai=x
    if x-y==mi:mia=max(mia,x);mii=min(mii,x)
    if x-y<mi:mi=x-y;mia=mii=x
    y-=2
    if x==xa:xaa=max(xaa,y);xai=min(xai,y)
    if x>xa:xa=x;xaa=xai=y
    if x==xi:xia=max(xia,y);xii=min(xii,y)
    if x<xi:xi=x;xia=xii=y
    if y==ya:yaa=max(yaa,x);yai=min(yai,x)
    if y>ya:ya=y;yaa=yai=x
    if y==yi:yia=max(yia,x);yii=min(yii,x)
    if y<yi:yi=y;yia=yii=x
    if x+y==pa:paa=max(paa,x);pai=min(pai,x)
    if x+y>pa:pa=x+y;paa=pai=x
    if x+y==pi:pia=max(pia,x);pii=min(pii,x)
    if x+y<pi:pi=x+y;pia=pii=x
    if x-y==ma:maa=max(maa,x);mai=min(mai,x)
    if x-y>ma:ma=x-y;maa=mai=x
    if x-y==mi:mia=max(mia,x);mii=min(mii,x)
    if x-y<mi:mi=x-y;mia=mii=x
print(yaa-yai+yia-yii+xaa-xai+xia-xii+max(ya+mi,yai)-min(pa-ya,yaa)+max(pi-yi,yii)-min(ma+yi,yia)+max(xa,pa-xaa)+max(xa,xai+ma)-min(xi,mi+xia)-min(xi,pi-xii))
```
#### 补两句话
![具有代表性的正八边形](https://www.yzthome.com/upload/attach/20211207/212_FVGYY8VBXWA97F6.jpeg)
虽然这是一道 CF 2000 分的绿题，但其实它有更加简单、模型化、熟悉的图景（如上图）。我们遇到难题不要害怕，找到规律就可以完美解决。

---

