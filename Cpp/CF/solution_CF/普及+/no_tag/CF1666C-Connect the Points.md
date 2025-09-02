# Connect the Points

## 题目描述

You are given three points on a plane. You should choose some segments on the plane that are parallel to coordinate axes, so that all three points become connected. The total length of the chosen segments should be the minimal possible.

Two points $ a $ and $ b $ are considered connected if there is a sequence of points $ p_0 = a, p_1, \ldots, p_k = b $ such that points $ p_i $ and $ p_{i+1} $ lie on the same segment.

## 说明/提示

The points and the segments from the example are shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666C/076acbc26156c4b983e140e9e71fa403c1c87ecb.png)

## 样例 #1

### 输入

```
1 1
3 5
8 6```

### 输出

```
3
1 1 1 5
1 5 8 5
8 5 8 6```

# 题解

## 作者：BorisDimitri (赞：5)

# Connect the Points

### 题意
平面上给定 $3$ 个点（其横坐标与纵坐标的绝对值均不超过 $10^9$），现在要在这个平面上连若干条平行于坐标轴的线段，每连一条线段，花费为该线段长。求一种连线段的方法使得这 $3$ 个点均连通且花费尽可能小。

我们定义两个点 $A,B$ 连通如下：

存在一组点 $P_0 , P_1, \ldots, P_k $，使得 $P_0$ 与 $A$ 重合，$P_k$ 与 $B$ 重合，且对于任意 $0 < i \le k$，都有 $p_i$ 与 $p_{i-1}$ 在同一条已连的线段中。

另外，保证满足题意的所有线段端点的横坐标与纵坐标的绝对值均不超过 $10^9$。


![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666C/076acbc26156c4b983e140e9e71fa403c1c87ecb.png)
 
### 思路
我们可以很容易发现一个性质：无论如何连线，最后的最短线段长度都是等于 $x_{max} - x_{min} + y_{max} - y_{min}$。

> Proof: 
>
> 记答案为 $ans = x_{max} - x_{min} + y_{max} - y_{min}$，如果存在一种摆放方式可以做到比 $ans$ 更小，则不可能做到使这三个点联通，所以不存在长度比 $ans$ 更小的情况。

构造出 $ans$ 的方法非常多，大家可以去翻别人 CF 里的代码看看，这里主要介绍我赛时的做法。

首先我将所有点按横坐标排序。

之后我找到第二大的纵坐标 $y_{mid}$，从 $(x_{min},y_{mid})$ 向 $(x_{max},y_{mid})$ 连一条边。

之后将所有点竖直向 $y_{mid}$ 连一条边即可（结合代码理解）。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

pair<int,int> p[10];
vector<int> px,py;

int main()
{
	int n = 3;
	for(int i=1;i<=n;i++)
	{
		cin>>p[i].x>>p[i].y;
		px.push_back(p[i].x), py.push_back(p[i].y);
	}
	
	sort(p+1,p+1+n);
	sort(px.begin(),px.end());
	sort(py.begin(),py.end());
	
	vector<vector<int>> ans;
	ans.push_back({px[0],py[1],px[2],py[1]});
	for(int i=1;i<=3;i++)
	{
		if(p[i].y != py[1]) ans.push_back({p[i].x,p[i].y,p[i].x,py[1]});
	}
	
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++)
	{
		for(int j=0;j<ans[i].size();j++)
			printf("%d ",ans[i][j]);
		cout<<endl;
	}
	
	return 0;
}
```

---

## 作者：Cuiyi_SAI (赞：2)

## 题目大意

给定三个整点的坐标，使用任意条平行于坐标轴的线段将他们连通。问，在线段长度和最小的情况下，这些线段的位置。

---
## 解题思路

我的第一眼想法是对两两点之间求曼哈顿距离，但是这个思路比较麻烦。因为两个点间的等价的曼哈顿路径有两种走法，三个点就有四种，但是这种曼哈顿路径作用到三个点上并不一定都是最优的。

于是我选择抛弃曼哈顿距离，重新思考。

可以看出，在题目条件下，**必定存在一种由 $3$ 条线段组成的可行方案**。所以可以尝试构造出这样的三条线段。

先将点坐标按照横坐标从小到大排序，然后我们可以发现线段 $(x_1,y_1,x_2,y_1)$ 和 $(x_3,y_3,x_2,y_3)$ 必定等价存在于最优解。

就是如下图的两条线段：

![](https://cdn.luogu.com.cn/upload/image_hosting/eh1anw3j.png)

显然这时候我们很自然的会在 $B$ 和 $G$ 间连一条线，这样子就是最优方案了。

可以手动尝试一下，这样子的连线方案对于任意三个点都是可以得到最优解。

总结一下，第一条线 $(x_1,y_1,x_2,y_1)$，第二条线 $(x_3,y_3,x_2,y_3)$，第三条线 $\left(x_2,\max(y_1,y_2,y_3),x_2,\min(y_1,y_2,y_3)\right)$。

## CODE:

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
struct node
{
	int x,y;
} a[4];
bool cmp(node s,node t)
{
	return s.x<t.x;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(int i=1;i<=3;i++) cin>>a[i].x>>a[i].y;
	sort(a+1,a+1+3,cmp);
	if(a[1].y>a[3].y) swap(a[1],a[3]);
	cout<<3<<'\n';
	cout<<a[1].x<<' '<<a[1].y<<' '<<a[2].x<<' '<<a[1].y<<'\n';
	cout<<a[2].x<<' '<<a[3].y<<' '<<a[3].x<<' '<<a[3].y<<'\n';
	cout<<a[2].x<<' '<<max({a[1].y,a[2].y,a[3].y})<<' '<<a[2].x<<' '<<min({a[1].y,a[2].y,a[3].y});
	return 0;
} 
```


---

## 作者：eb0ycn (赞：1)

## 形象题意

给定三个地点，需要修建与坐标轴水平的道路，使它们两两连通。构造方案使道路总长最小。**最多修 $100$ 条路**。

## 思路

比较简单，直接给出方案。

首先，我们钦定一个“主干道”。

把点按 $x$ 坐标升序排序，再找到 $y$ 坐标的中位数，则平行于 $x$ 轴、$y$ 坐标为中位数、两端 $x$ 坐标分别为 $x_1,x_3$ 的线段为“主干道”。

接着把每个点连到“主干道”即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/ejbyiylv.png)

这样最多连四条边，且至少一条长度为零。

## 代码

因为只有三个点，所以我手写了冒泡排序。


```cpp
#include<cstdio>
using namespace std;
int x1,x2,x3,y1,y2,y3,ret,r1,r2,r3;
int main(){
	scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3),r1=y1,r2=y2,r3=y3;
	if(x1>x2)ret=x1,x1=x2,x2=ret,ret=y1,y1=y2,y2=ret;
	if(x2>x3)ret=x2,x2=x3,x3=ret,ret=y2,y2=y3,y3=ret;
	if(x1>x2)ret=x1,x1=x2,x2=ret,ret=y1,y1=y2,y2=ret;
	if(r1>r2)ret=r1,r1=r2,r2=ret;
	if(r2>r3)ret=r2,r2=r3,r3=ret;
	if(r1>r2)ret=r1,r1=r2,r2=ret;
	printf("4\n");
	printf("%d %d %d %d\n",x1,r2,x3,r2);
	printf("%d %d %d %d\n",x1,y1,x1,r2);
	printf("%d %d %d %d\n",x2,y2,x2,r2);
	printf("%d %d %d %d",x3,y3,x3,r2);
	return 0;
}
```

---

