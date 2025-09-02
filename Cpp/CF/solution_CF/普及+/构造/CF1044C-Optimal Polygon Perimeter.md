# Optimal Polygon Perimeter

## 题目描述

You are given $ n $ points on the plane. The polygon formed from all the $ n $ points is strictly convex, that is, the polygon is convex, and there are no three collinear points (i.e. lying in the same straight line). The points are numbered from $ 1 $ to $ n $ , in clockwise order.

We define the distance between two points $ p_1 = (x_1, y_1) $ and $ p_2 = (x_2, y_2) $ as their Manhattan distance: $ $$$d(p_1, p_2) = |x_1 - x_2| + |y_1 - y_2|. $ $ </p><p>Furthermore, we define the perimeter of a polygon, as the sum of Manhattan distances between all adjacent pairs of points on it; if the points on the polygon are ordered as  $ p\_1, p\_2, \\ldots, p\_k $   $ (k \\geq 3) $ , then the perimeter of the polygon is  $ d(p\_1, p\_2) + d(p\_2, p\_3) + \\ldots + d(p\_k, p\_1) $ .</p><p>For some parameter  $ k $ , let's consider all the polygons that can be formed from the given set of points, having <span class="tex-font-style-bf">any</span>  $ k $  vertices, such that the polygon is <span class="tex-font-style-bf">not</span> self-intersecting. For each such polygon, let's consider its perimeter. Over all such perimeters, we define  $ f(k) $  to be the maximal perimeter.</p><p>Please note, when checking whether a polygon is self-intersecting, that the edges of a polygon are still drawn as straight lines. For instance, in the following pictures:</p><center> <img class="tex-graphics" src="/predownloaded/4e/c2/4ec25e6ecb8feac3ac0b9b7fa51a118c2b777e87.png" style="max-width: 100.0%;max-height: 100.0%;" /> </center><p>In the middle polygon, the order of points ( $ p\_1, p\_3, p\_2, p\_4 $ ) is not valid, since it is a self-intersecting polygon. The right polygon (whose edges resemble the Manhattan distance) has the same order and is not self-intersecting, but we consider edges as straight lines. The correct way to draw this polygon is ( $ p\_1, p\_2, p\_3, p\_4 $ ), which is the left polygon.</p><p>Your task is to compute  $ f(3), f(4), \\ldots, f(n) $ . In other words, find the maximum possible perimeter for each possible number of points (i.e.  $ 3 $  to  $ n$$$).

## 说明/提示

In the first example, for $ f(3) $ , we consider four possible polygons:

- ( $ p_1, p_2, p_3 $ ), with perimeter $ 12 $ .
- ( $ p_1, p_2, p_4 $ ), with perimeter $ 8 $ .
- ( $ p_1, p_3, p_4 $ ), with perimeter $ 12 $ .
- ( $ p_2, p_3, p_4 $ ), with perimeter $ 12 $ .

For $ f(4) $ , there is only one option, taking all the given points. Its perimeter $ 14 $ .

In the second example, there is only one possible polygon. Its perimeter is $ 8 $ .

## 样例 #1

### 输入

```
4
2 4
4 3
3 0
1 3
```

### 输出

```
12 14 ```

## 样例 #2

### 输入

```
3
0 0
0 2
2 0
```

### 输出

```
8 ```

# 题解

## 作者：Chocola4ever (赞：1)

首先我们描一组数据：

```
7
-1 1
5 2
3 0
-1 4
5 6
1 5
2 3
```

![](https://ae03.alicdn.com/kf/U1c12e4a8190647a1905ce993def9f1412.jpg)

当我们选 4 个点的时候，很明显，可以选出处于最外围的 4 个点作为新四边形

这四个点分别是处于最左边，最右边，最上面，最下面 4 个位置。

例如图中的四边形 $EBFA$ 就满足要求（当然，四边形 $EBFD$ 同理）

这 4 个点组成的“曼哈顿周长”就是这样一个矩形：

![](https://image.kysic.com.cn/60cfac49366e89c704b67bdbac35cded/77c8553025156.png)

所以，我们只要先扫一遍，找出 $x_{max},y_{max},x_{min},y_{min}$ 所对应的点，求出矩形的周长就可以了

至于 $n>4$ 的情况，显然，答案是不变的。

接下来看 $n=3$ 的情况：

这时我们不能继续从原来的 $x_{max},y_{max},x_{min},y_{min}$ 中选 3 个作为新点。只能选定 $x_{max},y_{max},x_{min},y_{min}$ 四个点中的一个，然后重新枚举一遍。

请看这么一组hack数据：

```
8
0 3
2 2
3 0
2 -2
0 -3
-2 -2
-3 0
-2 2
```

![](https://ae03.alicdn.com/kf/U9291867cc2b94d9982aba84d9f21c844k.jpg)

如果我们按上面的方法选点，选出的是 $A,E,G,C$ （如下图所示）

![image.png](https://ae03.alicdn.com/kf/U34061938c72a4d1cbb9c75c983325a7e2.jpg)

但是当我们只选3个点时，可以选出 $A,E,H$ 三点作为“曼哈顿周长”最大的三角形（如下图所示）

![](https://ae03.alicdn.com/kf/Ud865f42e7f8e4e10bec548ef1a0fb2f47.jpg)

所以需要重新枚举

具体请看代码实现：

```cpp
/*
	Author: Chocola4ever
	Date: 2021-03-29 19:44:37
	LastEditTime: 2021-03-30 21:38:25
	FilePath: \Programs\test.cpp
	Description: RP++
*/
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
const int N=3e5+5;
inline ll read(){
	ll x=0,w=1;
	char ch=getchar();
	for (;!isdigit(ch);ch=getchar())
		if (ch=='-')
			w=-1;
	for (;isdigit(ch);ch=getchar())
		x=x*10+(ch-'0');
	return x*w;
}
int n,x[N],y[N];
struct Chocola{
	int x,y;
}maxx,maxy,minx,miny;
ll getC(Chocola x,Chocola y,Chocola z){
	int maxX=max(max(x.x,y.x),z.x),maxY=max(max(x.y,y.y),z.y),minX=min(min(x.x,y.x),z.x),minY=min(min(x.y,y.y),z.y);
	return ((maxX-minX)<<1)+((maxY-minY)<<1);
}
int main(){
	n=read();
	if (n==3){ //n=3时直接计算输出
		printf("%lld",getC((Chocola){read(),read()},(Chocola){read(),read()},(Chocola){read(),read()}));
		return 0;
	}
	x[1]=read(),y[1]=read();
	maxx=minx=maxy=miny=(Chocola){x[1],y[1]};
	for (int i=2;i<=n;++i){
		x[i]=read(),y[i]=read();
		if (x[i]>maxx.x)
			maxx=(Chocola){x[i],y[i]};
		if (x[i]<minx.x)
			minx=(Chocola){x[i],y[i]};
		if (y[i]>maxy.y)
			maxy=(Chocola){x[i],y[i]};
		if (y[i]<miny.y)
			miny=(Chocola){x[i],y[i]};
	}
	ll ans=((maxx.x-minx.x)<<1)+((maxy.y-miny.y)<<1);
	int ans3=0;
	for(int i=1;i<=n;i++){
		ans3=max(max(max(ans3,abs(x[i]-maxx.x)+abs(y[i]-maxy.y)),max(ans3,abs(x[i]-maxx.x)+abs(y[i]-miny.y))),max(max(ans3,abs(x[i]-minx.x)+abs(y[i]-maxy.y)),max(ans3,abs(x[i]-minx.x)+abs(y[i]-miny.y))));
	}//枚举求出ans3
	printf("%d ",ans3<<1);
	for (int i=4;i<=n;++i)
		printf("%lld ",ans);
/*	printf("maxx:%d %d\n",maxx.x,maxx.y);调试信息
	printf("maxy:%d %d\n",maxy.x,maxy.y);
	printf("minx:%d %d\n",minx.x,minx.y);
	printf("miny:%d %d\n",miny.x,miny.y);*/
	return 0;
}

```

---

## 作者：liuyifan (赞：1)

1.因为本题中的距离为曼哈顿距离，所以题目中6边形的周长等于它的外接矩形的周长

2.而现在我只需要四个端点,也可以求出这个矩形，因此最优k边形周长=最优四边形周长的

3.又因为最优四边形的四个顶点就是这四个端点。所以我们接下来枚举找出最大值即可

code:
```cpp
#include<bits/stdc++.h>//万能头文件 
#define reg register
#define ll long long
using namespace std;
ll n,x,y,a[4][2],xi[3000005],yi[3000005],ans,anss;
inline ll dis(reg int i,reg int j)
{
	j%=4;
	return abs(a[i][0]-a[j][0])+abs(a[i][1]-a[j][1]); 
}//曼哈顿距离 
inline ll dis2(reg int i,reg int j)
{
	return abs(a[i][0]-xi[j])+abs(a[i][1]-yi[j]); 
}//同上 
int main()
{
	scanf("%lld",&n);
	for(reg int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&x,&y);
		xi[i]=x,yi[i]=y;
		if(i==1)
		for(reg int j=0;j<=3;j++)a[j][0]=x,a[j][1]=y;//初始化 
		else
		{
			if(x>a[0][0])a[0][0]=x,a[0][1]=y;
			if(y<a[1][1])a[1][0]=x,a[1][1]=y;
			if(x<a[2][0])a[2][0]=x,a[2][1]=y;
			if(y>a[3][1])a[3][0]=x,a[3][1]=y;
		}//枚举端点(上述和外接矩形的关系) 
	}
	for(reg int i=0;i<=3;i++)
	for(reg int j=0;j<=3;j++)
	{
		reg ll t=dis(i,j);
		if(i==j)continue;
		for(reg int k=1;k<=n;k++)anss=max(anss,t+dis2(i,k)+dis2(j,k));
	}//查询最大值 
	printf("%d ",anss);
	for(reg int i=0;i<=3;i++)ans+=dis(i,i+1);//求和 
	for(reg int i=4;i<=n;i++)printf("%d ",ans);
	return 0;
}
```


---

## 作者：Code_AC (赞：0)

## 题目大意：
给你 $n$ 个在平面直角坐标系内的点，然后求出 $3,4,5...,n$ 边形的最大周长，任意两点间距离为曼哈顿距离。

## 题目分析：

显而易见，因为距离为曼哈顿距离，所以题目要求的东西就变成了由多个点组成的矩形的周长。

举个例子，如下图，假设我们选择这样四个点：

![](https://pic.imgdb.cn/item/62d03b30f54cd3f93737bbba.png)

那么我们要求的矩形长这样：

![](https://pic.imgdb.cn/item/62d03b4af54cd3f93737e42a.png)

得到了这个以后，我们还需要分三种情况考虑：

**1.** 当 $k \geqslant 4$ 时即我们要求的是一个非三角形的最大周长时，这时就直接取横纵坐标的最大差值求和作为答案就行了。

这个的正确性显然，因为当我们求个非三角形时，就一定能取至少四个点，那么这时，我们一定能保证取到最大的差值。

**2.** 当 $k=3$ 时即我们要求的是一个三角形的最大周长时，这时我们就无法像上面那样考虑，样例一就是一个例子。

所以，这个时候我们可以直接枚举求解。

**注：**

看到数据范围 $-10^8 \leqslant x_i,y_i \leqslant 10^8$ 一定要记得开 long long。

这里给出核心部分代码：

```cpp
int main()
{
    n=read();
    long long maxx=-1,minx=0x7f7f7f;
    long long maxy=-1,miny=0x7f7f7f;
    for(register int i=1;i<=n;i++)
    {
        x[i]=read(),y[i]=read();
        maxx=max(maxx,x[i]);
        minx=min(minx,x[i]);
        maxy=max(maxy,y[i]);
        miny=min(miny,y[i]);
    }
    long long sum=(maxx-minx+maxy-miny)*2;
    if(n==3)
    {
        cout<<sum;
        return 0;
    }
    for(register int i=1;i<=n;i++)
    {
        if(x[i]==maxx)
            a[1]=x[i],b[1]=y[i];
        if(x[i]==minx)
            a[2]=x[i],b[2]=y[i];
        if(y[i]==maxy)
            a[3]=x[i],b[3]=y[i];
        if(y[i]==miny)
            a[4]=x[i],b[4]=y[i];
    }
    long long maxn=0;
    for(register int i=1;i<=n;i++)
    {
        maxn=max(maxn,abs(x[i]-minx)+abs(y[i]-miny));
        maxn=max(maxn,abs(x[i]-minx)+abs(y[i]-maxy));
        maxn=max(maxn,abs(x[i]-maxx)+abs(y[i]-maxy));
        maxn=max(maxn,abs(x[i]-maxx)+abs(y[i]-miny));
	}
    cout<<maxn*2<<' ';
    for(register int i=4;i<=n;i++)
    {
        cout<<sum<<' ';
    }
	return 0;
}

```



---

## 作者：KadiaNEFU (赞：0)

**~~来一发~~**

1. 思路：因为是一个凸边形，那么此种定义下的周长就是能将这个多边形完全装下的最小矩形。
![](http://a1.qpic.cn/psc?/V13gqYSE4WvhY3/A5hOE6*rc9U8eSRlr1H24vfaHCp49JKB9AnWBE*SioF4Urb6Zer0Bj4uRd0Qpx8ykDeXlUf2c8VP.kaqbAf2OQ!!/b&ek=1&kp=1&pt=0&bo=RgWBAgAAAAADF*I!&tl=1&vuin=2132886896&tm=1588086000&sce=60-1-1&rf=viewer_4)
我们假定有以上7个点。
**K>=4时我们选择最边缘的四个点（与矩形接触的四个点）就可以使周长最大**。我们把这个矩形叫做A矩形
K=3时，我们只能选择三个点，我们知道三个点得到的最大矩形至少有一个顶点与这三个点的一个点重合，且三个点构成的三角形至少有两个边与矩形A的某一对邻边重合（反证法），所以我们就**遍历一下每一个点与矩形A构成的四个矩形中的最大值，作为我们K=3时的结果。**
![](http://m.qpic.cn/psc?/V13gqYSE4WvhY3/VvKoQz*3MdOV*27lszynSb1FJhPBvUErCRfWfwiUYvTbqeo*x*nN.kJB2eTM1A2vrFJVuGsxYTSXfKR2DidIV7D6hR2uTlW8.*nqG91CgQM!/b&bo=RgWBAgAAAAADF*I!&rf=viewer_4)
```cpp
#include <bits/stdc++.h>
using namespace std;
int x[300005];
int y[300005];
int main()
{
    int n;
    cin >> n;
    int max_x=-0x3f3f3f3f;
    int max_y=-0x3f3f3f3f;
    int min_x=0x3f3f3f3f;
    int min_y=0x3f3f3f3f;
    for(int i=1;i<=n;i++)
    {
        cin >> x[i] >> y[i];
        max_x=max(max_x,x[i]);
        max_y=max(max_y,y[i]);
        min_x=min(min_x,x[i]);
        min_y=min(min_y,y[i]);
    }
    int c=0;
    for(int i=1;i<=n;i++)
    {
        c=max(c,abs(x[i]-max_x)+abs(y[i]-max_y));
        c=max(c,abs(x[i]-max_x)+abs(y[i]-min_y));
        c=max(c,abs(x[i]-min_x)+abs(y[i]-max_y));
        c=max(c,abs(x[i]-min_x)+abs(y[i]-min_y));
    }
    cout << 2*c ;
    c=2*(max_x-min_x)+2*(max_y-min_y);
    for(int i=4;i<=n;i++)
    {
        cout << " " << c;
    }
    cout << endl ;
    return 0;
}

```


---

## 作者：KadiaNEFU (赞：0)

题目思路有了就不难
我们发现其实就是求k个点构成的图形用一个周长多少的矩形才能装下
k>3时，始终取最大的x、y和最小的x、y。
k=3时，我们拿每一个点判断到最大边界的距离，取最大的一个
```cpp
#include <bits/stdc++.h>
using namespace std;
int x[300005];
int y[300005];
int main()
{
    int n;
    cin >> n;
    int max_x=-0x3f3f3f3f;
    int max_y=-0x3f3f3f3f;
    int min_x=0x3f3f3f3f;
    int min_y=0x3f3f3f3f;
    for(int i=1;i<=n;i++)
    {
        cin >> x[i] >> y[i];
        max_x=max(max_x,x[i]);
        max_y=max(max_y,y[i]);
        min_x=min(min_x,x[i]);
        min_y=min(min_y,y[i]);
    }
    int c=0;
    for(int i=1;i<=n;i++)
    {
        c=max(c,abs(x[i]-max_x)+abs(y[i]-max_y));
        c=max(c,abs(x[i]-max_x)+abs(y[i]-min_y));
        c=max(c,abs(x[i]-min_x)+abs(y[i]-max_y));
        c=max(c,abs(x[i]-min_x)+abs(y[i]-min_y));
    }
    cout << 2*c << " ";
    c=2*(max_x-min_x)+2*(max_y-min_y);
    for(int i=4;i<=n;i++)
    {
        cout << c << " ";
    }
    cout << endl ;
    return 0;
}

```


---

