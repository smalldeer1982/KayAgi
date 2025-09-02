# 『PG1』[JDWOI-2] 猪猪大厦

## 题目描述

$ \texttt{piggy} $ 建了一个巨大无比的 $\texttt {PIG}$ 大厦，可以看做一个平面，在这个平面上有 $n$ 个无限长的不垂直或平行于地面的扶手电梯，可以看做一些一次函数，并且这些电梯方向均朝右即 $x$ 轴正方向。

两个电梯的交汇点可以花 $1 \ \texttt{ZMB}$ 换乘。

一个人想要给  $ \texttt{piggy} $ 发短信让 $ \texttt{piggy} $ 过去找他 。

但是：

![](https://cdn.luogu.com.cn/upload/image_hosting/m2hw7oer.png)

于是只能走过去找 $ \texttt{piggy} $。

此时他站在第 $x_1$ 个电梯的横坐标为 $y_1$ 位置。

$ \texttt{piggy} $ 在第 $x_2$ 个电梯的横坐标为 $y_2$ 位置。

请问他最少花多少 $\texttt{ZMB}$ 才能过去？



## 说明/提示

**本题采用 Subtask。**

$\sf Subtask1(20pts)$：$1 \le n \le 10$；

$\sf Subtask2(30pts)$：$1 \le n\le 1000$；

$\sf Subtask3(50pts)$：$1 \le x_1,x_2 \le n\le 10^5$，$-10^3 \le y_1,y_2,k_i,b_i \le 10^3$。

**电梯的编号从 1 开始。**

## 样例 #1

### 输入

```
1
1 1 1 2
50 -30```

### 输出

```
0```

## 样例 #2

### 输入

```
2
1 2 2 2
1 0
2 0```

### 输出

```
-1```

## 样例 #3

### 输入

```
2
1 -1 2 1
1 0
2 0```

### 输出

```
1```

# 题解

## 作者：kyBWE (赞：13)

## P7731题解
### 题意简述
起点为第 $x_1$ 部电梯且横坐标为 $y_1$(横坐标是 $y$ 就及其别扭)，终点为第 $x_2$ 部电梯且横坐标为 $y_2$，换乘一次电梯花费 $1$ **ZMB**（注意所有电梯都是向右走的）。
### 题目分析
通过~~简单的~~分析可以得知，如果能到达终点，那么至多需要换乘两次电梯。
#### 证明
+ **情况一**  
![](https://cdn.luogu.com.cn/upload/image_hosting/6h8qzcj0.png)  
 如果起点和终点在同一部电梯上（即在同一条直线上），并且起点在终点左侧，显然不需要换乘即可到达。  
此时需要满足 $x_1=x_2$ 且 $y_1≤y_2$ （注意 $y_1$ 可以等于 $y_2$，即起点和终点相同）。 


------------

+ **情况二**
![](https://cdn.luogu.com.cn/upload/image_hosting/loz1q66f.png)  
 如果起点所在直线 $x_1$ 和和终点所在直线 $x_2$ 有交点且交点位于 $y_1,y_2$ 之间，那么只需在交点处换乘一次即可到达。  
此时需要满足 $y_1 ≤$ 交点横坐标 $≤ y_2$。（如果 $y_1=y_2=$ 交点横坐标，那显然 $y_1,y_2$ 在一条直线上，若为这种情况则已经在情况一中判断并输出结果了，所以不用担心误判）  
 顺便来推一下交点坐标：设交点坐标为 $(x_0,y_0)$，那么我们可以得到方程组
> $y_0=k[x_1]*x_0+b[x_1]$   
> $y_0=k[x_2]*x_0+b[x_2]$  

 上减下可以得到 
>$(k[x_1]-k[x_2])*x_0=b[x_2]-b[x_1]$  

 由此我们很容易就能得出交点横坐标 $x_0$ 的关系式。


------------

+ **情况三**

![](https://cdn.luogu.com.cn/upload/image_hosting/qeccsx7z.png)  
 如果直线 $x_1$ 和直线 $x_2$ 的交点位于 $y_1,y_2$  两侧，有一条直线分别与 $x_1,x_2$ 交于点 $xj_1,xj_2$，若两交点位于 $y_1,y_2$ 之间且 $xj_1≤xj_2$，那么只需在 $xj_1$ 和 $xj_2$ 两点各换乘一次即可到达  
此时需要满足 $y_1≤xj_1≤xj_2≤y_2$，所以我们可以枚举每一条直线的 $k$ 和 $b$，并算出相应的 $xj_1$ 和 $xj_2$，判断是否满足条件。


------------

+ **除上述三种情况外，其他情况都不能达到。**   
 我们顺便来看一下不能到达的情况：  
1. $y_1>y_2$ 时显然不可能到达（因为电梯只能往右走）。
2. $x_1$ 与 $x_2$ 的交点位于 $y_1,y_2$ 两侧，但没有一条直线与 $x_1,x_2$ 的交点位于 $y_1,y_2$ 之间。
![](https://cdn.luogu.com.cn/upload/image_hosting/ys72ccon.png)
3. $x_1$ 与 $x_2$ 的交点位于 $y_1,y_2$ 两侧，并且有一条直线与 $x_1,x_2$ 的交点位于 $y_1,y_2$ 之间，但是 $xj_1>xj_2$。
![](https://cdn.luogu.com.cn/upload/image_hosting/usmzsrct.png)  
（因为电梯只能向右走，所以无法从 $xj_1$ 到达 $xj_2$）


------------

### 最后附上AC代码
```cpp
	#include <iostream>
	using namespace std;
	int k[100005],b[100005];
	int main()
	{
		int n,x1,x2,y1,y2;
		cin>>n;
		cin>>x1>>y1>>x2>>y2;
		for(int i=1;i<=n;i++)
			cin>>k[i]>>b[i];
		if(x1==x2&&y1<=y2)//情况一 
		{//y1,y2在一条直线上 
			cout<<"0";
			return 0;//直接结束程序防止后面误判 
		}
		//情况二 
		double x0=(b[x2]-b[x1])*1.0/(k[x1]-k[x2]);
		//先求出交点横坐标（注意要 *1.0把 k和 b转成 double型） 
		if(y1<=x0&&y2>=x0)
		{
			cout<<"1";
			return 0;
		}
		//情况三 
		for(int i=1;i<=n;i++)//枚举每一条直线 
		{
			double xj1=(b[i]-b[x1])*1.0/(k[x1]-k[i]);
			double xj2=(b[x2]-b[i])*1.0/(k[i]-k[x2]);
			//先求出两交点 xj1，xj2的横坐标 
			if(y1<=xj1&&xj1<=xj2&&xj2<=y2)
			{
				cout<<"2";
				return 0;
			}
		}
		//若上述三种都不满足，则无法到达 
		cout<<"-1";//输出-1走人 
		return 0;
	}
```
蒟蒻的第一篇题解qvq

---

## 作者：CZJ_999 (赞：5)

# 猪猪大厦
本人一只初二的小蒟蒻，发现一种新的做法，还没大佬解析，特来一氵。

------------

## 题意复述
一个人要从起点（ $x_1$ 电梯 $y_1$ 位置）走到终点（$x_2$ 电梯 $y_2$ 位置），且只能沿着直线（电梯正方向）走，换乘要花费 1 ZMB，问最少花费，不能到达输出“-1”。

（注意：电梯只能向右走）。

------------

## 题目分析
### <1> 电梯运行
已知电梯向右，如果我们在 $x_1$ 电梯的 $A$ 点，那我们能到达 $B$ 点（右侧的点）而不能到达 $C$（左侧的点），如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/eotl3s1a.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

------------

### <2> 电梯换乘
电梯换乘有两种情况，假设小明在 $x_1$ 电梯的 $A$ 位置。

一，可以换乘，如图，$x_1$ 电梯和 $x_3$ 电梯在点 $B$ 交汇，而且点 $B$ 在小明右侧，可以到达，所以，小明可以从 $x_1$ 电梯的 $A$ 位置换乘到 $x_3$ 电梯的 $B$ 位置。

二，不可换乘，如图，$x_1$ 电梯和 $x_2$ 电梯在点 $C$ 交汇，但是点 $C$ 在小明左侧，不可到达，所以，小明不能从 $x_1$ 电梯的 $A$ 位置换乘到 $x_2$ 电梯。

![](https://cdn.luogu.com.cn/upload/image_hosting/eotl3s1a.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

补充：由<1>得，电梯只能向右走，如果我们算出两部电梯的交点在终点 $x_2$ 电梯的 $y_2$ 位置的右方，那这条电梯是绝对不可能到达终点 $B$ 的，我们可以判断为“不能换乘”，节省时间。


------------

### <3> 电梯交点
电梯交点（横坐标）的推导。

题目很清晰，每部电梯可以表示成 **一次函数表达式** ，（初二蒟蒻表示很熟悉 $y = k \cdot x + b$）。

题目就是用了 $k_i$ 和 $b_i$ 表示“$k$”和“$b$”，那我们就用二年级学的解方程，（设 $x_1$ 电梯表达式为 $y_1 = k_1 \cdot x + b_1$，则 $x_2$ 电梯为 $y_2 = k_2 \cdot x + b_2$）。

那么，当两电梯交汇时，$x$ 相等，$y_1 = y_2$（坐标相等）。

$\rightarrow k_1 \cdot x + b_1 = k_2 \cdot x + b_2$

$\rightarrow ( k_1 - k_2 ) \cdot x = b_2 - b_1$

$\rightarrow x =( b_2 - b_1 ) / ( k_1 - k_2 )$

------------

## 大开脑洞
我们不妨想像一下：

<1> 在同一电梯上，我们可以无限制的 **向右** 走且不花费 ZMB，难道不可以看成 **0步** 吗？

<2> 如果换乘，要花费 1 ZMB，难道不可以看成 **1步** 吗？

<3> 换乘一次花费 1 ZMB（1 步），问最少花费多少 ZMB，难道不可以看成 **最短路径** 吗？

把三者结合起来，不就是广搜（ _~~亿点点~~ 细节_  ）？

------------


## 综上所述
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,xx,yy,k[100005],b[100005],f[100005],usd[100005];
//f[i]存从起点到第i号电梯的最少花费，usd[i]记忆化已到达的电梯
queue<int> w,ZMB;
queue<double> c;
void wc()
//bfs
{
	w.push(x),c.push(y),usd[x]=1,ZMB.push(0),f[x]=0;
    while(w.size()>0)
	{
	    for(int i=1;i<=n;i++)
	    {
			int it=w.front();
		    if(i!=it)
			//自己不找自己，不然会有0除以0
		    {
			    double banana;
				//banana香蕉——相交，电梯交汇点的横坐标
			    banana=(b[i]-b[it])*1.0/(k[it]-k[i]);
				//一定要double并 *1.0 不然会四舍五入取整，有误差
			    if(banana>=c.front() && banana<=yy && usd[i]==0)
				//判断能不能换乘
				{
					w.push(i),c.push(banana),ZMB.push(ZMB.front()+1),usd[i]=1,f[i]=ZMB.front()+1;
				    if(i==xx) return ;
					//找到就退，后面的花费 ZMB 一定是大于或等于前面的，所以不会再有更优解
				}
		    }
	    }
		w.pop(),c.pop(),ZMB.pop();
	}
}
int main()
{
	scanf("%d%d%d%d%d",&n,&x,&y,&xx,&yy);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&k[i],&b[i]);
		f[i]=-1;
		//初始化
	}
	wc();
	printf("%d",f[xx]);
    return 0;
}
``` 


------------ 
最后，祝你在生活这条荆棘遍布的小路上一路生花。

---

## 作者：信息向阳花木 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P7731)
### 简化题意
$n$ 条直线，只能在线上走。问有没有方案从 $x_1,y_1$（称为 $A$ 点） 走到 $x_2,y_2$（称为 $B$ 点），若走的到，输出最少拐几个弯，否则输出 $-1$。**注意：只能往右走。**
 
### 题目解析
分情况考虑：
* 情况一：两点在一条直线上，判断时所需时间复杂度为 $O(1)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/m2slg9ak.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

很简单，答案为 $0$。一路走到头，不需要拐弯啊。


------------

* 情况二：两点所在的先相交，且 $A$ 到 $B$ 有可行方案，判断时所需时间复杂度为 $O(1)$。
	![](https://cdn.luogu.com.cn/upload/image_hosting/bhp8jb24.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
    
通过图可以看到，需要拐 $1$ 个弯，所以，答案为 $1$。


------------

* 情况三：两点所在的线都与另一条相交，判断时需要循环枚举所需时间复杂度为 $O(n)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ftje7l5j.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样，我们可以枚举每一条直线的 $k$ 和 $b$，算出 $a_1$，$a_2$ 看是否符合条件。（$a_1$，$a_2$ 是啥？有啥条件？往下看）



------------
如果三种情况都不满足，肯定到不了。
那么，哪些情况到不了呢?

* 如果 $A$ 在 $B$ 的右边（$y_1>y_2$），输出 $-1$。（$A$ 在 $B$ 的右边，想到达 $B$ **肯定**要往左走，而只能**往右走**）。
* $x_1$ 与 $x_2$ 的交点位于 $y_1$ 和 $y_2$ 的两侧，且没有一条直线与 $x_1$，$x_2$ 的交点位于 $y_1$ 和 $y_2$ 中间（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/ke6uo3tt.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

* $a_1<a_2$，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/zutyt5rv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果是这样的话，走到 $a_1$ 以后，只能往上走了。


---

## 作者：NightTide (赞：4)

## PART 1：题意解释
即在一个平面上，有 $n$ 条直线，问 $A$ 点能否沿着直线走到达 $B$ 点，若能，则需要经转换至少多少条直线。

这题看似不容易，但其实很简单（~~毕竟是普及-~~）。只需~~简单~~思考即可
## PART 2：思路分析
这道题并没有什么高大上的算法，我们可以考虑点与直线在平面内的分布情况，从而确定不同情况下需要转换的次数。

- ### 情况1：两点在一条直线上
如图

![](https://cdn.luogu.com.cn/upload/image_hosting/di2rvx0e.png)

这是最为简单的情况，即 $x1=x2$ 那么换乘的次数就是 $0$ 了，但是题目中还有一个容易忽略的条件：

**这些电梯方向均朝右即 $x$ 轴正方向**

注意这里的直线是单向的而非双向的，因此，即使 $piggy$ 和那个要找他的人在同一架电梯上，他也不可能能找到 $piggy$。这一点很重要，在后面的判断中也需要注意不能漏掉。（下文记为条件 $Z$）

- ### 情况2：两点在两条相交的直线上且 $A$ 可以到达 $B$（没有其他直线与这两条线段相交）
如图

![](https://cdn.luogu.com.cn/upload/image_hosting/6bsk9tdr.png)

这个情况可以转换为 $A$ 点先到交点 $C$,在从 $C$ 到终点 $B$。因此 $A$ 与 $C$，$C$ 与 $B$ 都需要满足条件 $Z$。设三点坐标分别为 $(x_A,y_A),(x_B,y_B),(x_C,y_C)$，则满足 $y_A \le y_C \le y_B$。这种情况需要转换 $1$ 次。

- ### 情况3：两点在两条相交的线段上且 $a$ 与 $b$ 在交点同侧
这个情况其实是 $y_A,y_B \le y_C$ 或 $y_A,y_B \ge y_C$ 的情况。按照我们上一种情况中的讨论，这两个点其实是不能仅仅转换 $1$ 次就到达的，因此我们需要其他的线段才能让 $A$ 到达 $B$。如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/i65hsr6u.png)

同情况2，如果要到达的话也需要满足条件 $Z$，这里不多赘述。

在这种情况下，需要转换 $3$ 次。
- ### 情况4：两点所在线段平行
这种情况其实可以归到情况 3 中，只需要把交点 $C$ 的坐标设为无限小即可。即 $y_C=-\infty$。这里不再讲述。

以上的情况就是全部的可以到达的情况了，剩下的就是不能到达的情况。

正常做题想到这里就可以结束了，但是你可能会想：真的最多只需要转 $2$ 次吗？

这确实是一个问题，可以画图解决，但是不太好证明，我来试着证明一下。（个人观点，有错误请指出）

首先，我们有两个点，所在的直线分别为 $l_1,l_2$。假设这两个点相互到达至少需要转 $3$ 次，也就是说总共走了 $4$ 条直线，设另外两条直线分别为 $l_3,l_4$。设 $l_1$ 与 $l_3$ 交于点 $D$，$l_2$ 与 $l_4$ 交于点 $E$，$l_3$ 与 $l_4$ 交于点 $F$，很显然，不论怎么摆放，$l_1$ 与 $l_4$，$l_2$ 与 $l_3$ 都会有交点，设这两个交点分别为 $G,H$。由于点 $D$ 与点 $F$ 满足条件 $Z$ 且点 $D,F,H$ 三点共线，那么点 $F$ 与点 $H$ 同样满足条件 $Z$，自然的，点 $D$ 与点 $H$ 也满足条件 $Z$。同理，点 $G$ 与点 $E$ 满足条件 $Z$。下面分两种情况：

- 当 $y_H<y_E$ 时,$y_D>y_G$

$\because y_E<y_B \And y_H<y_E$

$\therefore y_H<y_B$

$\therefore$ 可通过 $A,D,H,B$ 的路径到达，只需要转 $2$ 次，与假设矛盾。

- 当 $y_H>y_E$ 时,$y_D<y_G$

$\because y_D>y_A \And y_D<y_G$

$\therefore y_A<y_G$

$\therefore$ 可通过 $A,G,E,B$ 的路径到达，只需要转 $2$ 次，与假设矛盾。

综上所述，不可能存在至少需要走三次的情况。
## PART 3：AC 代码
这片题解到这里就结束了，下面附上 AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

struct coor{
    int x,y;
};
struct ana{
    int k,b;
};

coor piggy,now;
ana lift[100010];
int n;
double inter;

double cal(ana u,ana v);

int main(){
    cin>>n;
    cin>>now.x>>now.y>>piggy.x>>piggy.y;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&lift[i].k,&lift[i].b);
    }
    if(now.x==piggy.x&&now.y<=piggy.y){
        printf("0\n");
        exit(0);
    }
    inter=cal(lift[piggy.x],lift[now.x]);
    if(now.y<=inter&&piggy.y>=inter){
        printf("1\n");
        exit(0);
    }
    for(int i=1;i<=n;i++){
        double inter1=cal(lift[i],lift[now.x]);
        double inter2=cal(lift[piggy.x],lift[i]);
        if(now.y<=inter1&&inter1<=inter2&&inter2<=piggy.y){
            printf("2\n");
            exit(0);
        }
    }
    printf("-1\n");
    return 0;
}
double cal(ana u,ana v){
    return (double)((double)(u.b-v.b)/(double)(v.k-u.k));
}
```

---

## 作者：zhangzehao1 (赞：1)

**思路**

标签里写的贪心，但我们可以分类讨论，就可以通过。首先判断在同一直线的情况下，直接输出 `0`。然后是两点所在的线相交，只在交点处换乘一次的情况，输出 `1`，此时要求出交点坐标，由~~初一~~数学知识可以求出交点坐标，易得交点横坐标为：

$x=\frac{(b_{x_2}-b_{x_1})}{(k_{x_1}-k_{x_2})}$ 。 

注意其中要乘 `1.0` 转为 `double` 型。

最后一种情况是两点所在的线都与另一条线相交，在两个交点处换乘两次，输出 $2$，此时枚举所有直线，同理可得两个交点的横坐标 $jd_1=\frac{(b_i-b_{x_1})}{(k_{x_1}-k_i)}$，$jd_2=\frac{(b_{x_2]}-b_i)}{(k_i-k_{x_2})}$。

由于电梯只能向右走，易证除此之外其他情况均不成立，直接输出 `-1`。

还有一点注意事项，对于 `C++` 万能头和标准名字空间选手来说，`y1` 等词是关键字，容易出错，最好不要用。

**AC代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int m;
int n[100005],k[100005];
int a,b,c,d; 
int main()
{
	scanf("%d",&m);
	scanf("%d %d %d %d",&a,&b,&c,&d);
	for(int i=1;i<=m;i++)
	    scanf("%d %d",&k[i],&n[i]);
	//以下分别对应三种情况
	if(a==c&&b<=d)
	{
		puts("0");
		return 0;
	}
	double jd=(n[c]-n[a])*1.0/(k[a]-k[c]);
	if(b<=jd&&d>=jd)
	{
		puts("1");
		return 0;
	}
	for(int i=1;i<=m;i++)
	{
		double jd1=(n[i]-n[a])*1.0/(k[a]-k[i]);
		double jd2=(n[c]-n[i])*1.0/(k[i]-k[c]);
		if(b<=jd1&&jd1<=jd2&&jd2<=d)
		{
			puts("2");
			return 0;
		}
	}
	puts("-1");
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P7731)

------------
# 思路：
结论：如果能到目标点，那么最多转换 $2$ 次即可到达。

特殊情况：

令起终点为 $(x_1,y_1)$，$(x_2,y_2)$，

1. 起点终点在同一直线，代价为 $0$。
2. 起点所在直线 $l_1$ 与终点所在直线 $l_2$ 交点位于 $x_1$，$x_2$ 之间，可以直接换乘 $1$ 次。
3. 起终点直线交点不满足条件，通过第三方直线换乘 $2$ 次。枚举换乘直线，判断交点顺序是否从左到右。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
struct node{
    int x,y;
}a[N];
int n,sx,sy,ex,ey,l1,l2;
double x1,x2;
signed main(){
    cin>>n>>l1>>x1>>l2>>x2;
    l1--;
	l2--;
    for(int i=0;i<n;i++){
        cin>>a[i].x>>a[i].y;
    }
    sx=x1;
    ex=x2;
    if(l1==l2&&x1<=x2){
        cout<<0;
        return 0;
    }
    if(a[l1].x!=a[l2].x){
        double cx=(a[l2].y-a[l1].y)*1.0/(a[l1].x-a[l2].x);
        if(sx<=cx&&ex>=cx){
            cout<<1;
            return 0;
        }
    }else if(a[l1].y==a[l2].y){
        if(sx<=ex){
            cout<<1;
        }else{
            cout<<-1;
        }
        return 0;
    }
    for(int i=0;i<n;i++){
        if(i!=l1&&i!=l2){
            if(a[l1].x!=a[i].x&&a[i].x!=a[l2].x){
                double cx1=(a[i].y-a[l1].y)*1.0/(a[l1].x-a[i].x),cx2=(a[l2].y-a[i].y)*1.0/(a[i].x-a[l2].x);
                if(cx1<=cx2&&x1<=cx1&&x2>=cx2){
                    cout<<2;
                    return 0;
                }
            }
        }
	}
    cout<<-1;
    return 0;
}
```
完结撒花~

---

