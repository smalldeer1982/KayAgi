# Radar Installation

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3634

[PDF](https://uva.onlinejudge.org/external/11/p1193.pdf)

## 样例 #1

### 输入

```
3 2
1 2
-3 1
2 1

1 2
0 2

0 0```

### 输出

```
Case 1: 2
Case 2: 1```

# 题解

## 作者：盖矣斌峥 (赞：9)


[本人博客](https://prime.design.blog/)

   对于x轴上的每个小岛，可以计算出x轴上一段能够管辖它的区间l[i]~r[i]。问题转化为：给定N个区间，在x轴上放置最少的点，使每个区间至少包含一个点。


------------
  然后就是贪心操作了，将每个区间按照左端点l[i]从小到大排序，用一个变量来维护已经安放的最后一个监控设备的坐标pos，开始时pos为负无穷。
  
  首先对于每个区间l[i]~r[i]，有两种选择：
  
  1.使用已有的监控设备管辖它
  
  2.建造一台新的设备管辖它
  
  我们的贪心策略是，可以选择1的时候不会选择2
  
  依次考虑每个区间。如果当前区间i的左端点l[i]大于最后一台监控设备的坐标pos，则新增一台监控设备，并令pos=r[i]
 （监控尽量向右放），否则就让最后一台已经安放的监控设备来管辖当前区间，并令pos=min(r[i],pos)。

------------
```
for(int i=1;i<=n;i++)
{
	if(a[i].l>pos)
	{
		ans++;
		pos=a[i].r;
	}
	else pos=min(pos,a[i].r);
}
```
------------

见代码：

```
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct point{
	double l,r;
}a[1005];
int d,bj=0;
bool cmp(const point &x,const point &y){return x.l<y.l;}
void jisuan(int i,double x,double y)
{
	double t=d*d-y*y;
	if(t<0){bj=1;return;}
	a[i].l=x-sqrt(t);
	a[i].r=x+sqrt(t);
}
int main()
{
	int n,t=0;
	while(scanf("%d%d",&n,&d))
	{
		if(n==0&&d==0)break;
		t++;bj=0;
		for(int i=1;i<=n;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			jisuan(i,x,y);
		}
		if(bj==1||d<0)
		{
			printf("Case %d: -1\n",t);
			continue;
		}
		sort(a+1,a+n+1,cmp);
		double pos=-0x7fffffff/2;
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i].l>pos)
			{
				ans++;
				pos=a[i].r;
			}
			else pos=min(pos,a[i].r);
		}
		printf("Case %d: %d\n",t,ans);
	}
	return 0;
}
```


---

## 作者：Nitrogens (赞：5)

### 解题思路

本题为一道**贪心问题**，贪心问题中的**区间取点问题**。

首先，我们可以换个角度来分析问题：**以`x轴`上方的每一个点为圆心，`d`为半径作圆**。则这个圆会与`x轴`有交点（两个不同的或两个相同的）。每一对交点可以连成**一条交线**。在交线上的点距离`x轴`上方对应的点的距离一定小于等于`d`。因此，这个问题就转化为**区间选点问题**，即在若干的区间中，取尽可能少的点，使得每个区间中都至少有一个点。

该类问题的解题思路是：对于每个区间，先按照**右端点从小到大**排序，右端点**相同**时，按照**左端点从大到小**排序。之后，取第一个区间的右端点，不断往下取区间，若取到的点仍在区间中，则跳过，否则取新的区间中的右端点，以此类推，最终算出点的个数。

为方便起见，本题使用结构体和优先队列实现。

### 注意事项

1. 要对结构体重载`<`运算符。

2. 优先队列虽然使用了`<`运算符，但是默认是按照从大到小排列的。因此重载运算符的时候，要**反向定义**。

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;
struct range
{
    //s为区间的左端点，t为区间的右端点
    double s, t;
    //对于每个区间，先按照t从小到大排序，t相同时，按照s从大到小排序（这里需要反向设置，因为优先队列默认是按照大于号排列的）
    bool operator < (const range b) const
    {
        if(t > b.t)
            return true;
        else if(t == b.t)
        {
            if(s < b.s)
                return true;
            else
                return false;
        }
        else
            return false;
    }
};
priority_queue <range> que, empty;
int main(void)
{
	int n, flag = 1;
	double d, x, y;

	while(scanf("%d%lf", &n, &d) != EOF)
    {
        if(n == 0 && d == 0.0)
            break;

        bool isFail = false;
        que = empty;
        while(n--)
        {
            scanf("%lf%lf", &x, &y);
            /*
                y > d 表明在d距离内，在雷达信号无法从海岸线传到该岛上
                也就是以海岛坐标为圆心，d为半径的圆与x轴（海岸线）没有交点
                问题无解
            */
            if(y > d)
            {
                isFail = true;
            }
            //计算以海岛坐标为圆心，d为半径的圆与x轴（海岸线）的交点
            double delta = sqrt(d * d - y * y);
            que.push((range){x - delta, x + delta});
        }

        //取第一个区间的右端点
        range s = que.top();
        que.pop();
        double current = s.t;
        //cnt为取到的点数
        int cnt = 1;

        while(!que.empty() && !isFail)
        {
            s = que.top();
            que.pop();

            //当原来取到的点仍在新的区间中，则跳过，否则重新取新区间的右端点，并将cnt加1
            if(s.s > current)
            {
                current = s.t;
                cnt++;
            }
        }

        printf("Case %d: ", flag);
        flag++;

        if(!isFail)
            printf("%d\n", cnt);
        else
            printf("-1\n");
    }

	return 0;
}
```

---

## 作者：_xbn (赞：4)

一道经典的贪心问题，我们先预处理出每个岛屿能被雷达控制的最左端点和最

右端点，接下来我们考虑贪心，对于一个岛屿，它能被多个雷达控制，我们

选择离他最远的能控制它的雷达，这样就能让最多的雷达空闲，即最少的雷达

工作。其他细节详见代码注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1010;
struct Point
{
	double l,r;
}a[MAXN];
bool cmp(Point aa,Point bb)
{
	return aa.r<bb.r;//将每个岛屿按照右端点排序 
}
int main()
{
	int n,d,ans=1,t=0;
	while(cin>>n&&n!=0)//多组数据 
	{
		t++;
		ans=1;
		cin>>d;
	    memset(a,0,sizeof(a)); 
		int flag=0;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(y>d)//如果一个岛屿距离雷达的距离大于雷达的控制范围，则为无解 
		{
			cout<<"Case "<<t<<": "<<"-1"<<endl;
			flag=1;
			break;
		}
		int dis=sqrt(d*d-y*y);
		a[i].l=x-dis;a[i].r=x+dis;//预处理 
	}
	if(flag==1)continue; 
	sort(a+1,a+n+1,cmp);//排序 
	double now=a[1].r;
	for(int i=2;i<=n;i++)
	{
		if(now<a[i].l)//如果一个岛屿超过了雷达控制范围，就添加一个雷达 
		{
			now=a[i].r;
			ans++;
		}
	}
	cout<<"Case "<<t<<": "<<ans<<endl;
    }
	return 0;
}
```



---

## 作者：feecle6418 (赞：3)

这道题由两部分组成。

## Part 1 转化为区间选点问题 (数学)

先来看一张图。（用Windows画图画的，比较丑）

![](https://cdn.luogu.com.cn/upload/pic/42210.png)

现在大家应该都知道怎么做了。为了锻炼大家的代码阅读能力~~其实是我懒得写注释~~，这里直接给出转换部分的代码：

```
bool flg=0;
for(int i=1;i<=n;i++){
    double ff,gg;
    scanf("%lf%lf",&ff,&gg);
    if(d*d-gg*gg<0)printf("Case %d: -1\n",casee),flg=1;
    if(!flg){
            a[i].x=ff-sqrt(d*d-gg*gg);
            a[i].y=ff+sqrt(d*d-gg*gg);
    }
}
if(flg)continue;
```

## Part 2 解决区间选点问题 (贪心)

再来看一张图：

![](https://t1.picb.cc/uploads/2018/11/05/Jp85q6.png)

明显，灰色线段移动到绿色位置会更优。

因此~~其实是我懒得写证明，需要者可自行百度~~，我们得到了这道题的贪心策略：先将所有线段按照右端点从小到大排序，然后一个一个遍历，如果```当前选择的右端点```已经在```当前区间```内了则继续，否则将```当前选择的右端点```更新为```当前区间的右端点```（注意不同），并且```ans++```。

只是阅读可能有些难以理解，配合代码食用效果更佳：

```
sort(a+1,a+n+1);
int ans=1,now=a[1].y;//now为当前选择的右端点
for(int i=2;i<=n;i++){
	if(a[i].x>now)ans++,now=a[i].y;//a[i].y为当前区间的右端点
}
```

---

## 作者：SmallTownKid (赞：2)

比较有思维难度的一道贪心题。我们可以把一个雷达能监测到的小岛转化为小岛能被检测到需要在海岸线的那一段区间上放雷达。

比如下面这个图。如果雷达监测范围是 $d$ ，那么在 $a,b$ 之间放雷达，这个小岛就能被监测到。
![](https://cdn.luogu.com.cn/upload/image_hosting/hmrf7247.png)

根据勾股定理，可以求出 $a$ 点坐标和 $b$ 点坐标。

所以我们可以处理出每个小岛要被监测到需要在哪段区间上放雷达。这样按照区间的右端点从小到大排序。放雷达的时候放在右端点一定是最优的。因为如果下一个区间和这个区间有重叠，一定包含了这个区间的右端点。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
struct node{
	double l,r;
}a[100010];
int ans,n;
double x,y,last=-1000000;
double d;
double cal1(double x,double y)//计算左端点 
{
	return x-(sqrt(d*d-y*y));
}
double cal2(double x,double y)//计算右端点
{
	return x+(sqrt(d*d-y*y));
}
bool cmp(node a,node b)
{
	return a.r<b.r;
}
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>x>>y;
		if(y>d)
        {
            printf("Case i:-1\n");
            return 0;
        }
		a[i].l=cal1(x,y);
		a[i].r=cal2(x,y);
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		if(a[i].l<=last)
		continue;
		ans++;
		last=a[i].r;
	}
	printf("Case i:%d\n",ans);
	return 0;
} 

---

## 作者：陷语 (赞：1)

## Radar Installation

### 思路：
这其实是一道典型的区间求点问题，由题可知雷达只能建在x轴上，那么我么可以通过勾股定理来求区间在x轴上的覆盖长度，需要注意的是，如果纵坐标y大于d显然是无解的，我们只要将纵坐标＜=d的区间在x轴上的起始位置和结束位置保存，然后将所有区间的起始位置按从小到大的顺序排序一遍，然后使用一个变量pos维护已经安放雷达的最大扫描位置，在考虑每一个区间的时候判断下一个区间的起始位置是否>pos，如果大于pos则增加一台雷达，并且更新pos，否则直接在pos和结束区间位置中取最小值。

### 证明：

由题可知对于每个区间我们有两种选择情况：

1.使用原雷达来检测岛屿。

2.新增一台雷达来检测岛屿。

很显然，在可以选择1的情况下优先选择1比选择2的结果对答案的贡献更大，既选择1未来可到达状态包含选择2未来可到达的状态。

代码：

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1005;
const int INF = 0x3f3f3f3f;

int n, d, ans, t;
bool flag;

struct node{
    double l, r;
    bool operator < (const node & a) const{return l < a.l;}
} a[N];

int main() {
//	freopen("in.txt", "r", stdin);
    
    while(~scanf("%d %d", &n, &d)) {
        if(!n && !d) break;
        double pos = -INF;
        double x, y;
        ans = 0;
        flag = 0;
        
        for(int i = 1; i <= n; ++i) {
            scanf("%lf %lf", &x, &y);
            if(fabs(y) > d) {
                printf("Case %d: -1\n", ++t);
                flag = 1;
                break; 
            }
            double m = sqrt(d * d - y * y);//勾股定理求x轴上的长度 (圆的半径)
            a[i].l = x - m;//起始位置 
            a[i].r = x + m;//结束位置 
        }
        if(flag) continue;
        
        sort(a + 1, a + 1 + n);
        
        for(int i = 1; i <= n; ++i) {
            if(a[i].l > pos) {
                pos = a[i].r;//新增了一台设备，更新pos 
                ans++;
            }
            else pos = min(a[i].r, pos);
        }
        
        printf("Case %d: %d\n", ++t, ans);
    }
    return 0;
}
```


---

## 作者：Thomastine (赞：1)

#正如楼上的大犇们所说，本题可以转化为区间求点问题。根据每个点坐标求出可以控制该点的雷达在x轴上的区间，再排序，每次在最右端设雷达便能使数量最少，注意特判区间包含情况。
~~~
#include<bits/stdc++.h>
using namespace std;
inline void read(int &x)
{
    x=0;int f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
    while(c<='9'&&c>='0'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    x*=f;
}
inline void print(int x)
{
    if(x<0){x=-x;putchar('-');}
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
int n,radii;
struct radar{
    double l,r;
}r[1008];
inline bool rmp(radar a,radar b)
{
    if(a.l==b.l) return a.r<b.r;
    return a.l<b.l;
}
int main()
{
    int gg=0;
    while(~scanf("%d%d",&n,&radii)&&n&&radii)
    {
        int maxy=-0x3f3f3f3f;
        int tot=0,a,b;
        for(int i=1;i<=n;i++) 
        {
            read(a);read(b);
            maxy=max(maxy,b);
            r[i].l=a*1.0-sqrt(radii*radii-b*b);
            r[i].r=a*1.0+sqrt(radii*radii-b*b);
        }
        if(maxy<=radii) 
        {
            stable_sort(r+1,r+n+1,rmp);
//			for(int i=1;i<=n;i++)
//			{
//				cout<<r[i].l<<" "<<r[i].r<<endl;
//			}
            double ll=r[1].l,rr=r[1].r;tot=1;
            for(int i=2;i<=n;i++)
            {
                if(rr>=r[i].l&&rr<=r[i].r) 
                {
                    ll=r[i].l;
                }
                else if(rr>r[i].r&&ll<=r[i].r)
                {
                    ll=r[i].l;
                    rr=r[i].r;
                }
                else
                {
                    tot++;rr=r[i].r;
                }
            }
        }
        else tot=-1;
        gg++;printf("Case %d: %d\n",gg,tot);	
    }
}
~~~


---

## 作者：luckydrawbox (赞：0)

[传送门](https://www.luogu.com.cn/problem/UVA1193)

## 题意

对于第 $i$ 组测试数据，在一条数轴上选一些点，用以这些点为圆心作的半径为 $d$ 的圆覆盖所给点，若无法全部覆盖，则输出 ``Case i: -1``；否则输出 ``Case i:  ``$+$ **最少**需要的点数 $ans$。

## 分析

为了方便，我们把 $x$ 和 $y$ 都存在**结构体** $asdf$ 中。

```cpp
struct asdf
{
	int x,y;
	double l,r;//这个后面会讲
}a[N];
```

我们首先判断是否能全部覆盖，一个点能够被数轴上的某个点覆盖，当且仅当它与数轴的距离 $a_i.y$ **不超过**半径 $d$，所以我们输入的时候判断一下就好了。

```cpp
t++;//第t组测试数据 
b=0;//b代表是否有点没被覆盖 
for(int i=1;i<=n;i++)
{
	cin>>a[i].x>>a[i].y;
	if(a[i].y>d)//y就是第i个点到数轴的距离
	{
		b=1;//标记 
		break;//已经有不能覆盖的点就不做无用的输入了 
	}
}
if(b)//有没被覆盖的点 
{
	cout<<"Case "<<t<<": -1"<<endl;
	continue;
}
```

接下来，我们**预处理**出距离第 $i$ 个点不超过 $d$ 的最左点 $a_i.l$ 和最右点 $a_i.r$，这样当我们想判断某个点上装的雷达时候能覆盖到第 $i$ 个点的时候，只要判断是否在 $a_i.l$ 到 $a_i.r$ 的线段上就行了。

那么 $a_i.l$ 怎么求呢？请看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/23fy3sp5.png)

如图所示，$d、a_i.y$ 和 $(a_i.x-a_i.l)$ 正好构成了一个**直角三角形**，根据小学时学过的**勾股定理**：

$$a_i.y^2+(a_i.x-a_i.l)^2=d^2$$

反过来就是：

$$a_i.l=a_i.x-\sqrt{d^2+a_i.y^2}$$

$a_i.r$ 也同理：

$$a_i.r=a_i.x+\sqrt{d^2+a_i.y^2}$$

```cpp
for(int i=1;i<=n;i++)
{
	a[i].l=a[i].x-sqrt(d*d-a[i].y*a[i].y);
	a[i].r=a[i].x+sqrt(d*d-a[i].y*a[i].y);
}
```

然后就是**贪心**了，设上一个雷达的位置为 $w$，我们按 $x$ 轴**从小到大**排序，当前我们在第 $i$ 个点，则我们有以下 $2$ 种选择：

$1.$ 让当前的点被之前的雷达覆盖。

$2.$ **新建**一个雷达供它使用。

我们为了使雷达最少，在条件允许的情况下应该**尽量选择**第一种，条件就是当前雷达位置 $w$ 比**不少于**能覆盖第 $i$ 个点的最左点 $a_i.l$，即 $w>=a_i.l$，不过有可能当前雷达位置 $w$ **超过**了能覆盖第 $i$ 个点的最右点 $a_i.r$，我们只能把雷达向左移一些满足要求，即 $w=\min(w,a_i.r)$。

如果不能选择第一种，那么我们只能选择第二种了，为了给后面**留出更多的位置**，我们把雷达**尽量往右放**，又要覆盖这个点，所以只能放在能覆盖第 $i$ 个点的最右点 $a_i.r$，即 $w=a_i.r$，且 $ans$ 要加 $1$，因为我们又放了一个雷达。**注意**，第一个点时还没有雷达，所以我们在第一个点直接放雷达，然后循环 $2-n$。

```cpp
sort(a+1,a+n+1,cmp);//排序
w=a[1].r;ans=1;//第一个点直接放雷达 
for(int i=2;i<=n;i++)//循环剩下的n-1次 
{
	if(w>=a[i].l)//能覆盖到 
		w=min(w,a[i].r);//第一种选择 
	else 
		ans++,w=a[i].r;//否则只能第二种选择 
}
```

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int t,n,d,ans;
bool b;
double w;
struct asdf
{
	int x,y;
	double l,r;
}a[N];
bool cmp(asdf p,asdf q)//按x轴从小到大排序 
{
	return p.x<q.x;
}
int main()
{
    while(cin>>n>>d&&n&&d)//有多组数据 
    {
    	t++;//第t组测试数据 
    	b=0;//b代表是否有点没被覆盖 
    	for(int i=1;i<=n;i++)
    	{
    		cin>>a[i].x>>a[i].y;
    		if(a[i].y>d)//y就是第i个点到数轴的距离
    		{
    			b=1;//标记 
    			break;//已经有不能覆盖的点就不做无用的输入了 
			}
		}
		if(b)//有没被覆盖的点 
		{
			cout<<"Case "<<t<<": -1"<<endl;
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			a[i].l=a[i].x-sqrt(d*d-a[i].y*a[i].y);
			a[i].r=a[i].x+sqrt(d*d-a[i].y*a[i].y);
		} 
		sort(a+1,a+n+1,cmp);//排序
		w=a[1].r;ans=1;//第一个点直接放雷达 
		for(int i=2;i<=n;i++)//循环剩下的n-1次 
		{
			if(w>=a[i].l)//能覆盖到 
				w=min(w,a[i].r);//第一种选择 
			else 
				ans++,w=a[i].r;//否则只能第二种选择 
		}
		cout<<"Case "<<t<<": "<<ans<<endl;
	}
	return 0;
}
```

懂了来领[双倍经验](https://www.luogu.com.cn/problem/P1325)。

---

## 作者：_Luminous (赞：0)

这题的解题思路正如大佬们已经说得很详细了，我就不赘述了，在此提供一个跟dalao们处理选点的不同方法，供大家参考借鉴。
```cpp
memset(used,false,sizeof(used));//used数组表示当前下标为i的这个点有没有被覆盖
for(int i=0;i<n;i++){
	if(used[i])//如果已经被覆盖，便不用再执行这次循环了
		continue;
	ant++;//如果当前点没被覆盖，则雷达数ant++
	for(int j=i+1;j<n;j++){//将这个区间里的点都标记为已经被覆盖
		if(used[j])
			continue;
		if(radar[j].start<=radar[i].end)
			used[j]=true;
	}
}
```

思路是一样的，要看你从什么角度考虑。~~（不过我的貌似还麻烦一点qwq）~~

下面是完整代码 ~~（前面的处理都是一样的，其实看不看都无所谓）~~

#### · Code


------------

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int n,d,Case=1,ant;
bool ans,used[1010];
struct node{
	double start,end;
}radar[1010];
bool cmp(node a,node b){
	return a.end<b.end;
}
int main(){
	while(scanf("%d %d",&n,&d) && n!=0 && d!=0){
		ans=true;
		for(int i=0;i<n;i++){
		    double x,y;
		    scanf("%lf %lf",&x,&y);
		    if(y>d){
		    	ans=false;
		    	continue;
			}
			double t=sqrt(d*d-y*y);
			radar[i].start=x-t;
			radar[i].end=x+t;
		}
		printf("Case %d: ",Case++);
		if(!ans){
			printf("-1\n");
			continue;
		}
		ant=0;
		sort(radar,radar+n,cmp);
		memset(used,false,sizeof(used));
		for(int i=0;i<n;i++){
			if(used[i])
			    continue;
			ant++;
			for(int j=i+1;j<n;j++){
				if(used[j])
				    continue;
				if(radar[j].start<=radar[i].end)
				    used[j]=true;
			}
		}
		printf("%d\n",ant);
	}
	return 0;
}
```


---

## 作者：windrizzle (赞：0)

是一道比较简单的贪心，主要是对公式的运用。

### 题意

多组测试数据。

给你$n$个坐标上的点, $n <= 1000$。

你可以在$x$轴上放置雷达,每个雷达的辐射半径都是$d$。

现在问你辐射到所有的点至少需要几个雷达,如果辐射不到所有的点输出$-1$。

### 题解

因为二维的贪心比较困难，所以我们使用圆形的公式即可。用公式转化后，就变成了一道覆盖区间的普通贪心。

### 代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#define eps 0.0000005
using namespace std;
struct note 
{
	double x;
	double y;
}a[30001];
int n;
double s;
double l,r;
int sum;
bool cmp(note a,note b)
{
	return a.x<b.x;
}
int main()
{
	cin>>n>>s;
	while(n&&s)
	{
		int flag=0;
		for(int i=0;i<n;i++) 
		{
			cin>>l>>r;
			if(abs(r)>s) flag=1;
			a[i].x=l-sqrt(s*s-r*r);
			a[i].y=l+sqrt(s*s-r*r);//公式的运用
		}
		if(flag) //特判
		{
			cout<<"Case "<<++sum<<": -1"<<endl;
			for(int i=0;i<n;i++) a[i].x=a[i].y=0.0;
			scanf("\n%d %lf",&n,&s);
			continue;
		}
		sort(a,a+n,cmp);//开始寻找
		double right=a[0].y;
		int ans=1;
		for(int i=1;i<n;i++)
			if(a[i].x<=right) right=min(right,a[i].y);
			else right=a[i].y,ans++;
		cout<<"Case "<<++sum<<": "<<ans<<endl;
		for(int i=0;i<n;i++) a[i].x=a[i].y=0.0;
		scanf("\n%d %lf",&n,&s);
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

# ad
欢迎去博客观看：http://blog.cinema000.xyz
# 分析

对于$x$轴上方建筑，可以计算其$x$轴上被管辖的范围，大概就是以其自身为圆心，$d$为半径做圆，与$x$轴的左右交点便是$L[i],R[i]$。

然后问题就转化为：

> 给出$n$个区间，在$x$轴上放置最少的点，使得每个区间至少含有一个点。

然后就是一个经典的贪心，先按区间左端点从小到大排序，用$pos$记录已经安放的最后设备的坐标，初始$pos$为负无穷。

然后遍历每个区间，如果当前区间$i$的左端点大于$pos$，累加答案，令`pos = R[i]`，否则令`pos = min(R[i],pos)`

# 代码

注意这题和POJ 1328是重题，但是数据不太一样，UVa的数据的$d>0$，而POJ的数据的$d\in R$。~~（要是Luogu也能交POJ就好了，反正不要验证码的）~~

## POJ 1328

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
const int MAXN = 1000 + 6;
const double eps = 1e-9;
const int INF = 0x7fffffff;
struct Point{
    double x,y;
};Point P[MAXN];
struct Interval{
    double l,r;
    bool operator < (const Interval &rhs) const{return rhs.l - l > eps;}
};Interval I[MAXN];
bool calc(int n,double d){
    for(int i = 0;i < n;i++){
        if(P[i].y * P[i].y - d * d > eps) return false;
        double delta = sqrt((double)(d * d - P[i].y * P[i].y));
        I[i].l = P[i].x - delta;
        I[i].r = P[i].x + delta;
    }
    return true;
}
int main(){
    int n,ans,id = 0;double d,pos;bool running;
    while(scanf("%d %lf",&n,&d) == 2 && n){
        for(int i = 0;i < n;i++) scanf("%lf %lf",&P[i].x,&P[i].y);
        if(d <= 0){printf("Case %d: -1\n",++id);continue;}
        running = calc(n,d);
        std::sort(I,I + n);
        pos = -INF,ans = 0;
        for(int i = 0;i < n;i++){
            if(I[i].l - pos > 0){ans++;pos = I[i].r;}
            else pos = std::min(I[i].r,pos);
        }
        printf("Case %d: %d\n",++id,running ? ans : -1);
    }

    return 0;
}
```

## UVa 1193

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
const int MAXN = 1000 + 6;
const double eps = 1e-6;
const int INF = 0x7fffffff;
struct Point{
    double x,y;
};Point P[MAXN];
struct Interval{
    double l,r;
    bool operator < (const Interval &rhs) const{return rhs.l - l > eps;}
};Interval I[MAXN];
void calc(int n,double d){
    for(int i = 0;i < n;i++){
        double delta = sqrt((double)(d * d - P[i].y * P[i].y));
        I[i].l = P[i].x - delta;
        I[i].r = P[i].x + delta;
    }
}
int main(){
    int n,ans,id = 0;double d,pos;
    while(scanf("%d %lf",&n,&d) == 2 && n){
        for(int i = 0;i < n;i++) scanf("%lf %lf",&P[i].x,&P[i].y);
        calc(n,d);
        std::sort(I,I + n);
        pos = -INF,ans = 0;
        for(int i = 0;i < n;i++){
            if(I[i].l > pos) ans++,pos = I[i].r;
            else{
                pos = std::min(I[i].r,pos);
            }
        }
        printf("Case %d: %d\n",++id,ans);
    }

    return 0;
}
```



---

