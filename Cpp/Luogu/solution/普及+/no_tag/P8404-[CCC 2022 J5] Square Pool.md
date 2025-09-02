# [CCC 2022 J5] Square Pool

## 题目描述

罗恩想在他的 $n\times n$ 的正方形院子里建一个正方形游泳池，但他的院子里有 $T$ 棵树。

你的任务是确定他可以建造的最大的方形游泳池的边长。

## 说明/提示

样例 $1$ 解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/c2b58ek8.png)

样例 $2$ 解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/r7uoub7n.png)

对于 $20\%$ 的数据：$1\le n\le 50,T=1$

对于 $35\%$ 的数据：$1\le n\le 50,1\le T\le 10$

对于 $25\%$ 的数据：$1\le n\le 5\times 10^5,1\le T\le 10$

对于 $100\%$ 的数据：$1\le n\le 5\times 10^5,1\le T\le 100$

## 样例 #1

### 输入

```
5
1
2 4```

### 输出

```
3```

## 样例 #2

### 输入

```
15
8
4 7
4 1
14 11
10 6
13 4
4 10
10 3
9 14```

### 输出

```
7```

# 题解

## 作者：David_Mercury (赞：10)

## 题意简述

[~~自己看~~](https://www.luogu.com.cn/problem/P8404)


------------

## 题目分析

这道题的核心思想就是**枚举**。

55pts 解法：

使用前缀和储存地图树的棵数，去二分枚举水池的边长，然后去枚举所有可能的左上角位置，检验是否合法即可。

100pts 解法：

可以发现，树是非常稀疏的，最多仅为 $100$ 棵。因此就想：是否可以通过枚举树来枚举正方形。

很明显的，正方形的上、下、左、右界限，会被树或者墙所限制。而此时它的边长，就为上下界距离、左右界距离中更小的那一个。而代表上下界的树一定在两棵左右界树之间。因此，基本的枚举思路，就是将树从左到右进行排序，接着枚举所有可能的左右界。在每一次从左界开始往右枚举右界时，就可以顺便求出中间的上下界。

![map](https://cdn.luogu.com.cn/upload/image_hosting/me25xwob.png)

而上下界树的具体确定方式，相当于以左界树为中轴，取一路上找过去，离这个“中轴”最近的树，就像向中间压缩过去一样。

![map2](https://cdn.luogu.com.cn/upload/image_hosting/o2gqrpqx.png)

这一段的代码大概如下：

```cpp
sort(tree+1, tree+1+t, cmp1);
int ans = 0;
for(int i=1; i<=t; i++){
    int minn = 1, maxn = n;										//上下界在初始时为墙 
    for(int j=i+1; j<=t; j++){
        if(maxn-minn-1 < tree[j].x-tree[i].x-1) break;          //如果上下界距离小于左右界距离，无继续枚举必要 
        ans = max(ans, tree[j].x-tree[i].x-1);                  //检测边长 
        if(tree[j].y<=tree[i].y) minn = max(minn, tree[j].y);   //打擂台，求上下界 
        if(tree[j].y>=tree[i].y) maxn = min(maxn, tree[j].y);
    }
}
```

现在你可以开心地发现我们已经过了第二个样例，也就是**没有墙 / 上界或下界为墙 / 上界与下界为墙**的情况。但是，还有一些有靠墙的特殊情况我们还没有处理。


------------

#### 1. 四界为墙

显然在有树的情况下就不存在。

------------

#### 2. 有相邻两界 / 三界为墙

这便是样例一的情形。

![sample1](https://cdn.luogu.com.cn/upload/image_hosting/c2b58ek8.png)

可以证明，此时的最优正方形必有一个角是靠在墙上的。所以我们只需要在地图的四个角上种树，即可将这种情况转化为全是树的情况。


------------

#### 3. 有左界或右界 / 左界与右界为墙

![:)](https://cdn.luogu.com.cn/upload/image_hosting/m5175mdn.png)

这种情况，我们只需要以上下顺序排序，并以枚举上下界的方式走一遍我们之前的枚举左右界的程序即可。


------------

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXT = 105;
int n, t;
struct node{
	int x, y;
} tree[MAXT];

bool cmp1(node a, node b){
	return a.x < b.x;
}

bool cmp2(node a, node b){
	return a.y < b.y;
}

int main(){
	scanf("%d%d", &n, &t);
	n++;
	for(int i=1; i<=t; i++) scanf("%d%d", &tree[i].x, &tree[i].y);
	//四角种树 
	tree[++t] = {0,0}, tree[++t] = {0,n};
	tree[++t] = {n,n}, tree[++t] = {n,0};
	//枚举左右界 
	sort(tree+1, tree+1+t, cmp1);
	int ans = 0;
	for(int i=1; i<=t; i++){
		int minn = 1, maxn = n;
		for(int j=i+1; j<=t; j++){
			if(maxn-minn-1 < tree[j].x-tree[i].x-1) break;
			ans = max(ans, tree[j].x-tree[i].x-1);
			if(tree[j].y<=tree[i].y) minn = max(minn, tree[j].y);
			if(tree[j].y>=tree[i].y) maxn = min(maxn, tree[j].y);
		}
	}
	//枚举上下界 
	sort(tree+1, tree+1+t, cmp2);
	for(int i=1; i<=t; i++){
		int minn = 1, maxn = n;
		for(int j=i+1; j<=t; j++){
			if(maxn-minn-1 < tree[j].y-tree[i].y-1) break;
			ans = max(ans, tree[j].y-tree[i].y-1);
			if(tree[j].x<=tree[i].x) minn = max(minn, tree[j].x);
			if(tree[j].x>=tree[i].x) maxn = min(maxn, tree[j].x);
		}
	}
	cout<<ans;
	
	return 0;
}
```


------------

## ~~废话~~后记

第一次写题解，可能有疏漏，欢迎指出。

最后的最后，感谢您的观看！

---

## 作者：gudzpoz (赞：7)

[![License: CC BY-SA 4.0](https://img.shields.io/badge/License-CC_BY--SA_4.0-green.svg)](https://creativecommons.org/licenses/by-sa/4.0/)

本文以 [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) 发布。

搜了一圈没搜到典型例题，所以这里自己写一个题解。

这道题的障碍点非常稀疏，所以大概不能用常见的悬线法或者单调栈。忽略边界的话，一个局部的极大正方形肯定由某一对障碍物限制住了大小，那么直接枚举每一对障碍物即可：

- 对于每一对障碍物，在以它们两个连线为对角线的矩形中，如果存在另外的障碍物，那么这一对肯定限制不住正方形的大小。

  ![](https://images-64b.pages.dev/P8404/A.svg)

- 矩形里没有障碍物的话，看长轴的垂直方向上找上下界，判断上下界之间是否能容下一个正方形。

  ![](https://images-64b.pages.dev/P8404/B.svg)

当然，边界以及边界顶点需要特殊处理一下，直接把顶点也放到障碍物里再限制一下上下界的初始值。

## 代码

储存结构及预处理，预先排个序：

```cpp
struct Point {
  int x, y;
  int xOrder, yOrder;
};
constexpr int LIMIT = 100 + 4;

Point trees[LIMIT];
Point* treesXSorted[LIMIT];
Point* treesYSorted[LIMIT];

void sortAndPrune(int T) {
  sort(treesXSorted, treesXSorted + T, [](const Point* a, const Point* b) {
    return a->x < b->x;
  });
  sort(treesYSorted, treesYSorted + T, [](const Point* a, const Point* b) {
    return a->y < b->y;
  });
  for (int i = 0; i != T; ++i) {
    treesXSorted[i]->xOrder = i;
    treesYSorted[i]->yOrder = i;
  }
}
```

对于某一对障碍物查找其限制住的最大正方形：（直接上了 `template` 希望编译器能够自动 `inline`）

```cpp
using Getter = int(const Point&);

template<Point** axis>
inline int axisWiseMax(const Point& a, const Point& b, int n,
                       int dx, Getter getY,
                       Getter order) {
  int minY = 0, maxY = n;
  int lessY = min(getY(a), getY(b)), greaterY = max(getY(a), getY(b));
  const Point& larger = order(a) > order(b) ? a : b;
  const Point& smaller = order(a) > order(b) ? b : a;
  for (int o = order(smaller) + 1; o != order(larger); ++o) {
    const Point& p = *axis[o];
    if (getY(p) <= lessY) {
      if (getY(p) > minY) {
        minY = getY(p);
      }
    } else if (greaterY <= getY(p)) {
      if (getY(p) - 1 < maxY) {
        maxY = getY(p) - 1;
      }
    } else {
      return 0;
    }
  }
  return min(maxY - minY, dx);
}

inline int maxBetween(const Point& a, const Point& b, int n) {
  int dx = abs(a.x - b.x) - 1;
  int dy = abs(a.y - b.y) - 1;
  if (dx >= dy) {
    return axisWiseMax<treesXSorted>(a, b, n, dx,
                       [](const Point& p) { return p.y; },
                       [](const Point& p) { return p.xOrder; });
  } else {
    return axisWiseMax<treesYSorted>(a, b, n, dy,
                       [](const Point& p) { return p.x; },
                       [](const Point& p) { return p.yOrder; });
  }
}
```

遍历每一对障碍物的代码略。边界的四个顶点也要加到障碍物里。

### 扩展：如果泳池可以是长方形？

这时候一个长方形一定受到两对障碍点的限制，一对上下方向，一对左右方向。那么按上面的思路可以两个方向都遍历一次。更有效率的话是只按一个方向遍历一遍，但是这个时候需要处理一些边与边界重合的特殊情况。

## 最大子矩阵相关问题

本题因为障碍点比较稀疏，而 $n$ 比较大，所以只能从障碍物着手。下面是一些不是很稀疏的例题，有其他常见的做法。~~找不到其它比较稀疏的例题。~~

### 障碍严格不可跨越

一般是悬线法或者是单调栈。

- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：
  与本题相同，但障碍点密集。
- [P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147)：
  求的是长方形。障碍点比较密集。

### 障碍赋负权

没有严格意义上的障碍点，各点有可负权重。这种题基本只能把所有组合情况枚举一遍。
我们最多能够优化一下这种过程，例如用最大子段和、单调栈等优化一个维度方向的枚举。

- [P1115 最大子段和](https://www.luogu.com.cn/problem/solution/P1115)：
  可看作一维矩阵。
- [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)：
  权值最大的子矩阵。
- [P1565 牛宫](https://www.luogu.com.cn/problem/P1565)：
  最大面积的子矩阵，但要求权值求和为正。
- [P2331 [SCOI2005]最大子矩阵](https://www.luogu.com.cn/problem/P2331)：
  求 $k$ 个不重叠的子矩阵使权值最大。~~还好数据规模很小。~~

---

## 作者：jr_zch (赞：3)

# [Square Pool](https://www.luogu.com.cn/problem/P8404)
## Part 1：题目大意
给定一个 $n \times n$ 的矩形，以及 $t$ 个障碍物的坐标，试求边长最大的正方形。

## Part 2：解题思路
$O(n^4)：$ 二维前缀和暴力找点即可。

$O(n^2)：$ 用扫描线朝任意方向对每一行进行扫描，并 $O(n)$ 递推 $h$ 数组，记录能够拓展的最远位置，对 $ans$ 取 $\max$ 即可。

$O(t^2)：$ 正解如下

观察到 $n$ 的范围非常大，达到了 $5 \times 10^5$，但是 $t$ 却只有 $100$，所以考虑从 $t$ 突破。

很容易想到任何一个正方形一定是被树给框住的，所以可以把树作为**横向或者纵向的中心**进行扩展，并且固定一个方向为较小的一边，如果另一边较大，则停止此次扩展。

以纵向扫描为例，先选一棵树，然后不断向下找，遇到新的树就以最初的树的 $x$ 坐标为 $mid$ 进行缩小，然后继续向下扩展，直到超出边界或者纵向高度大于横向长度就终止，再以下一棵树为中心来扩展。

请**仔细观察**下图。

第一步：

![](https://cdn.luogu.com.cn/upload/image_hosting/5ztltamm.png)

第二步：

![](https://cdn.luogu.com.cn/upload/image_hosting/i14geezo.png)

第三步：

![](https://cdn.luogu.com.cn/upload/image_hosting/7336hktp.png)

第四步：

![](https://cdn.luogu.com.cn/upload/image_hosting/11sl7n4s.png)

最后得出答案 $ans = 4$。

#### tips：
* 输入是无序的，要先排序。
* 扫描一次会有部分漏掉所以要横纵扫描两次。
* 在该过程中要始终保证纵向高度小于等于横向长度 横向扫描时反之。
* 部分矩形会以 $1$ ~ $3$ 条边界为边 所以要在**四个角之外**都手动种一棵树。

## Part 3：Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e2+7,inf=0x3f3f3f3f;
int n,m,l,r,u,d,ans=-inf;
struct node{
	int x,y;
}p[maxn];

bool dcmp(node x,node y){
	return x.x==y.x?x.y<y.y:x.x<y.x;
}

bool lcmp(node x,node y){
	return x.y==y.y?x.x<y.x:x.y<y.y;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&p[i].x,&p[i].y);
	p[++m]=(node){0,0},p[++m]=(node){0,n+1},p[++m]=(node){n+1,0},p[++m]=(node){n+1,n+1};
	sort(p+1,p+1+m,dcmp);
	for(int i=1;i<=m;i++){
		l=1,r=n;
		for(int j=i+1;j<=m;j++){
			if(r-l+1<p[j].x-p[i].x-1) break;
			ans=max(ans,p[j].x-p[i].x-1);
			if(l<=p[j].y&&p[j].y<=p[i].y) l=p[j].y+1;
			else if(r>=p[j].y&&p[j].y>p[i].y) r=p[j].y-1;
		}
	}
	sort(p+1,p+1+m,lcmp);
	for(int i=1;i<=m;i++){
		u=1,d=n;
		for(int j=i+1;j<=m;j++){
			if(d-u+1<p[j].y-p[i].y-1) break;
			ans=max(ans,p[j].y-p[i].y-1);
			if(u<=p[j].x&&p[j].x<=p[i].x) u=p[j].x+1;
			else if(d>=p[j].x&&p[j].x>p[i].x) d=p[j].x-1;
		}
	}
	printf("%d",ans);
	return 0;
}
```
$$\text {Thanks~for~your~reading}$$

---

## 作者：ccrui (赞：2)

### 题意解释：

一个 $n\times n$ 个点的网格图上有 $T$ 个不能覆盖的点，求这网格图上最大的正方形的边长。

### 55 pts

前缀和记录，枚举边长和左上角，$O(n^3)$ 实现。

进一步优化，加一个二分，可以达到 $O(n^2\log n)$，但 $n\le 5\times 10^5$，还是过不了！

### 100 pts

容易发现 $T$ 很小，所以可以使用 $O(T^2)$ 的方法实现

**扫描左右界：**

先把每一棵树按 $y$ 坐标排序。

接下来就可以保证存数的数组 $t$ 中树的 $y$ 坐标具有单调性。

可以发现正方形的边长为最上面挨到的树或墙与强于最下面挨到的树或墙的距离与最左面挨到的树最上面挨到的树或墙与强于最右面挨到的树或墙的距离中的最小值。

所以说排序后我们可以枚举所有可能的上下界。每一次从一个点对应的横线作为下界开始往上枚举上界，还可以求出左右界，左右界就为过程中经过的点的 $x$ 坐标的极差。

![](https://cdn.luogu.com.cn/upload/image_hosting/f74du7iq.png)

还可以加一个小优化：因为极差不会增大，所以当极差小于上下界的距离时，正方形边长就不会有增加了。

从一个点求上下界的代码如下：

```cpp
int getx(int x){//上下界，x代表起始点 
	int maxx=1,minx=n+1,ans=0;
	for(int i=x+1;i<=T;i++){
		if(minx-maxx<a[i].y-a[x].y)return ans;//优化 
		ans=a[i].y-a[x].y-1;//上下界距离 
		if(a[i].x<=a[x].x){
			if(maxx<a[i].x)maxx=a[i].x;//更新极值 
		}
		if(a[i].x>=a[x].x){
			if(minx>a[i].x)minx=a[i].x;//更新极值 
		}
	}
	return ans;
}
```


同理我们也可以对每一棵树按 $x$ 坐标排序，再求出左右界和上下界。

代码：

```cpp
int gety(int x){//左右界，x代表起始点 
	int maxx=1,minx=n+1,ans=0;
	for(int i=x+1;i<=T;i++){
		if(minx-maxx<b[i].x-b[x].x)return ans;//优化 
		ans=b[i].x-b[x].x-1;//左右界距离 
		if(b[i].y<=b[x].y){
			if(maxx<b[i].y)maxx=b[i].y;//更新极值 
		}
		if(b[i].y>=b[x].y){
			if(minx>b[i].y)minx=b[i].y;//更新极值 
		}
	}
	return ans;
}
```

**四个角加树：**

这时我们发现样例一过不了，因为正方形的左界和下界都是靠墙的，这时我们可以在地图的左下角的左下角、右下角的右下角、左上角的左上角、右上角的右上角分别加一棵树，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/lev40klc.png)

这样方形的边界也可以是院子的四面墙了。

四棵树的位置分别为 $(0,0),(n+1,0),(0,n+1),(n+1,n+1)$。

### 代码：



------------


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,T;
struct dot{
	int x,y;
}a[114],b[114];
bool cmpx(dot x,dot y){
	if(x.x==y.x)return x.y<y.y;
	else return x.x<y.x;
}
bool cmpy(dot x,dot y){
	if(x.y==y.y)return x.x<y.x;
	else return x.y<y.y;
}
int getx(int x){//上下界 
	int maxx=1,minx=n+1,ans=0;
	for(int i=x+1;i<=T;i++){
		if(minx-maxx<a[i].y-a[x].y)return ans;//优化 
		ans=a[i].y-a[x].y-1;//上下界距离 
		if(a[i].x<=a[x].x){
			if(maxx<a[i].x)maxx=a[i].x;//更新极值 
		}
		if(a[i].x>=a[x].x){
			if(minx>a[i].x)minx=a[i].x;//更新极值 
		}
	}
	return ans;
}
int gety(int x){//左右界 
	int maxx=1,minx=n+1,ans=0;
	for(int i=x+1;i<=T;i++){
		if(minx-maxx<b[i].x-b[x].x)return ans;//优化 
		ans=b[i].x-b[x].x-1;//左右界距离 
		if(b[i].y<=b[x].y){
			if(maxx<b[i].y)maxx=b[i].y;//更新极值 
		}
		if(b[i].y>=b[x].y){
			if(minx>b[i].y)minx=b[i].y;//更新极值 
		}
	}
	return ans;
}
signed main(){
    cin>>n;
	cin>>T;
    for(int i=1;i<=T;i++){
    	cin>>a[i].x>>a[i].y;
    	b[i]=a[i];
	}
	a[T+1]=dot{0,n+1};b[T+1]=a[T+1];
	a[T+2]=dot{n+1,0};b[T+2]=a[T+2];
	a[T+3]=dot{n+1,n+1};b[T+3]=a[T+3];
	a[T+4]=dot{0,0};b[T+4]=a[T+4];//四角加树 
	T+=4;
	sort(a+1,a+T+1,cmpy);//求上下界的排序 
	sort(b+1,b+T+1,cmpx);//求左右界的排序 
	int ans=0;
	for(int i=1;i<=T;i++){
		int u=max(getx(i),gety(i));
		ans=max(ans,u);
	}
	cout<<ans<<endl;
    return 0;
}

```


---

## 作者：ZHONGZIJIE0608 (赞：1)

[**博客食用更佳**](https://www.luogu.com.cn/blog/Administator/p8404-ti-xie)

一道不错的**枚举**题。

55 分的解法比较容易想，枚举长度与左上角，遍历整个正方形即可。时间复杂度  $O(n^{4})$。

还有一种解法。感性理解一下，正方形的长度是满足单调性的，比合法的最大值大的长度都是不合法的。因此我们可以二分长度，枚举左上角，使用二维前缀和优化。具体实现是统计每个左上角为 $(1,1)$ 的矩阵的树的个数。时间复杂度 $O(n^{2}\log n)$。

然而，上述解法均只能获得 55 分。

**正解：**

我们发现 $1 \le T \le 100$，所以可以枚举树。

显然对于答案正方形，它的上下边界**或**左右边界是被树或边界限制的。因此我们分别枚举作为上下边界和左右边界的树（排序后枚举即可），求出边长。

固定第一个点，则可以存下这一点所限制的正方形的另两个边界 $minn$ 和 $maxx$。

最大合法边长即为答案。

时间复杂度是以排序占主要的 $O(T^2\log T)$。

以下是代码。

[AC 记录](https://www.luogu.com.cn/record/129303481)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t,ans=0;
struct ZHONGZIJIE0608{int x,y;}g[105];
inline bool cmpx(ZHONGZIJIE0608 x,ZHONGZIJIE0608 y){return x.x<y.x;}
inline bool cmpy(ZHONGZIJIE0608 x,ZHONGZIJIE0608 y){return x.y<y.y;}
signed main(){
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	cin>>n>>t;++n;
	for(int i=1;i<=t;++i)cin>>g[i].x>>g[i].y;
	g[++t]={0,0},g[++t]={0,n},g[++t]={n,0},g[++t]={n,n};//四角种树，用于边界的判定 
	sort(g+1,g+1+t,cmpx);//以横坐标排序 
	for(int i=1;i<=t;++i){
		int minn=1,maxx=n;
		for(int j=i+1;j<=t;++j){
			if(maxx-minn-1<g[j].x-g[i].x-1)break;//若上下距短于左右距则不合法 
			ans=max(ans,g[j].x-g[i].x-1);//更新边长 
			if(g[j].y<=g[i].y)minn=max(minn,g[j].y);//查找上界 
			if(g[j].y>=g[i].y)maxx=min(maxx,g[j].y);//查找下界 
		}
	}
	sort(g+1,g+1+t,cmpy);//以纵坐标排序 
	for(int i=1;i<=t;++i){
		int minn=1,maxx=n;
		for(int j=i+1;j<=t;++j){
			if(maxx-minn-1<g[j].y-g[i].y-1)break;//若左右距短于上下距则不合法 
			ans=max(ans,g[j].y-g[i].y-1);//更新边长 
			if(g[j].x<=g[i].x)minn=max(minn,g[j].x);//查找左界 
			if(g[j].x>=g[i].x)maxx=min(maxx,g[j].x);//查找右界 
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：gan1234 (赞：1)

发个不太一样的题解，可供开拓思路。

## 分析

最暴力的方法就是枚举一个点 $(i,j)$ 作为正方形一个顶点，枚举正方形的长度 $k$，接着暴力检查该正方形内是否有障碍点，复杂度 $O(n^5)$。

其中暴力检查障碍点可以通过前缀和，将每个障碍点设为 $1$，$O(1)$ 复杂度计算正方形内和是否为 $0$ 判断是否有障碍点。

观察数据范围，发现 $T$ 的值很小，障碍点十分稀疏，不用枚举所有点，只需要枚举一些有用的点就行，因此我们可以对数据出现的坐标进行类似离散化的操作。

## 正解

将每个障碍点的坐标都离散化(叫离散化或许不太精确，总之就是那样的操作)，例如两个相邻的障碍点 $(1,1)$ 和 $(1,5000)$，我们不需要从 $1$ 枚举到 $5000$，因此只需要保留 $1$，$2$，$4999$，$5000$就够了，$2$ 到 $4999$ 之间就不用管了。

离散化相关代码

```cpp
int ls(int x){
    int l=1,r=cnt;
    while(r>l){
        int mid=(l+r)/2;
        if(t[mid]>=x)r=mid;
        else l=mid+1;
    }
    return l;
}


for(int i=1;m>=i;i++){
        t[++cnt]=x[i];t[++cnt]=max(x[i]-1,1ll);t[++cnt]=min(x[i]+1,n);
        t[++cnt]=y[i];t[++cnt]=max(y[i]-1,1ll);t[++cnt]=min(y[i]+1,n);
    }
    t[++cnt]=n;t[++cnt]=1;
    sort(t+1,t+cnt+1);
    cnt=unique(t+1,t+cnt+1)-t-1;   
    
```
复杂度从 $O(n^3)$ 变为 $O(T^3\log T)$，常数较大，吸氧能过。

还有一个优化，枚举正方形的长度 $k$ 时，$k$ 不用从 $1$ 开始，而是直接从目前所求最大边长开始。优化后不吸氧每个测试点可在 $25$ ms 内通过。

具体的实现可以看代码，有注释。

## 完整代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans=1;
int x[105],y[105],t[605];
int cnt;
int a[605][605],s[605][605];
int f(int x1,int y1,int x2,int y2){//前缀和
    return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
}
int ls(int x){
    int l=1,r=cnt;
    while(r>l){
        int mid=(l+r)/2;
        if(t[mid]>=x)r=mid;
        else l=mid+1;
    }
    return l;
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;m>=i;i++)cin>>x[i]>>y[i];
    //离散化
    for(int i=1;m>=i;i++){
        t[++cnt]=x[i];t[++cnt]=max(x[i]-1,1ll);t[++cnt]=min(x[i]+1,n);
        t[++cnt]=y[i];t[++cnt]=max(y[i]-1,1ll);t[++cnt]=min(y[i]+1,n);
    }
    t[++cnt]=n;t[++cnt]=1;
    sort(t+1,t+cnt+1);
    cnt=unique(t+1,t+cnt+1)-t-1;   
    
    for(int i=1;m>=i;i++)a[ls(x[i])][ls(y[i])]=1;
    //前缀和
    for(int i=1;cnt>=i;i++)
        for(int j=1;cnt>=j;j++)
            s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
    //两次不同方向的枚举正方形。
    for(int i=1;cnt>=i;i++)
        for(int j=1;cnt>=j;j++)
            for(int k=ls(t[j]+ans-1)-1;cnt>=k;k++){//k从ans开始
                //判断正方形内是否有障碍点
           
                if(t[i]+t[k]-t[j]>n||a[i][j]||a[i][k])break;
                int r=ls(t[i]+t[k]-t[j]);
                //注意！t[r]代表的并不是正方形的顶边纵坐标
                //因为正方形的顶边纵坐标不一定被记录过
                //所以t[r]代表的是记录中第一个大于等于顶边纵坐标的值
                if((t[r]>t[i]+t[k]-t[j]&&f(i,j,r,k)==f(r,j,r,k))||
                    f(i,j,r,k)==0){
                    ans=max(ans,(t[k]-t[j]+1));
                }else break;
            }
    for(int i=1;cnt>=i;i++)
        for(int j=1;cnt>=j;j++)
            for(int k=ls(t[j]+ans-1)-1;cnt>=k;k++){
                if(t[i]+t[k]-t[j]>n||a[j][i]||a[k][i])break;
                int r=ls(t[i]+t[k]-t[j]);
                if((t[r]>t[i]+t[k]-t[j]&&f(j,i,k,r)==f(j,r,k,r))||
                    f(j,i,k,r)==0){
                    ans=max(ans,(t[k]-t[j]+1));
                }else break;
            } 
    cout<<ans<<endl;
    return 0;
}
```
## 进一步优化

虽然已经能过掉这题了，但是复杂度还可以继续优化。

在每个点枚举正方形长度时，我们发现，如果边长 $l$ 无法满足要求，那么比 $l$ 更大的边长一定无法满足要求。同理，如果边长 $l$ 可以满足要求，那么比 $l$ 更小的边长一定可以满足要求。

满足二分的条件，可以二分出 $k$ 的值。
复杂度降为 $O(T^2 \log^2 T)$。

~~因为懒，没有写二分的代码。~~

可能有错误或疏漏，欢迎指出和补充。感谢阅读。


---

## 作者：yx666 (赞：0)

# P8404 Square Pool 悬线法题解
$$\text{Discription}$$

- 题目：[传送门](https://www.luogu.com.cn/problem/P8404)。

- AC 记录：[~~谁说悬线法过不去的~~](https://www.luogu.com.cn/record/180253843)。

- 跑得比较慢，时间复杂度 $O(nT)$。

---

$$\text{Solution}$$

55 pts 做法：

1. $O(n^4)$ 的枚举；

2. 不经优化的 $O(n^3)$ 的[朴素悬线法](https://www.luogu.com.cn/record/180251663)（吐槽出题人数据梯度弱）（[代码](https://www.luogu.com/paste/03xo7u0r)）。

有关于悬线法，可以戳这里→[link](https://www.luogu.com/article/475qql1h)。

100 pts 做法：

1. 其他巨佬的扫描线、枚举障碍树等解法。

2. 对悬线法的优化。

这里是第二种解法。

---

观察朴素的悬线法，我们发现：

- 树较稀疏，很可能有一大片都没有树；

- 我们一行一行地跑单调栈时，每行都是空。

所以，我们可以选择只跑这些行：

1. 有树在的行；

2. 下一行有树的行。

不难发现，其他行，对答案的贡献是包含在上面的行中的。

---

$$\text{Code}$$

实现见注释（~~快读被我吃了~~）。

```cpp
#define pii pair<int,int>

#define N 500005
#define T 105

// n,t：如题
// h：可以伸展到的高度
// l_i：可以向左伸展到的列（左边第一个比 h_i 小的位置）
int n,t,h[N],l[N];

// st,tp：单调栈
int st[N],tp=0;

// 存点
vector<pii>pts;
signed main(){
	n=read(),t=read();
	
	// 读点，排序
	for(int i=1;i<=t;++i)
		pts.emplace_back(read(),read());
	sort(pts.begin(),pts.end());
	pts.emplace_back(n+1,11060208);		// 加上一个在 n+1 行的，避免枚举不到底边
	
	auto flush=[&](int &x)->void{
		static auto p=pts.begin();					// 当前还没有遍历到的树
		if(x<p->first){								// 将当前行设置为“下一行有树的行”
			const int d=p->first-x;
			for(int i=1;i<=n;++i) h[i]+=d;
			x=p->first-1;
		}else{											// 当前行是有树的行
			int lst=-1;
			while(p!=pts.end()&&p->first==x){			// 只更新这一行
				for(int i=lst+1;i<p->second;++i) ++h[i];
				lst=p->second;
				h[lst]=0;
				++p;
			}
			for(int i=lst+1;i<=n;++i) ++h[i];
		}
	};
	
	int ans=0;
	for(int i=1;i<=n;++i){
		flush(i);			// 修改当前行 & 更新
		
		/* 以下是悬线法基本运用 */
		st[tp=0]=0;
		for(int j=1;j<=n;++j){
			while(tp&&h[st[tp]]>=h[j]) --tp;
			l[j]=st[tp];
			st[++tp]=j;
		}
		
		st[tp=0]=n+1;
		for(int j=n;j;--j){
			while(tp&&h[st[tp]]>h[j]) --tp;
			ans=max(ans,min(h[j],st[tp]-l[j]-1));
			st[++tp]=j;
		}
	}writeln(ans);
	return 0;
}
```

---

## 作者：leiaxiwo (赞：0)

# 洛谷 P8404
## 搜索 扫描线 枚举
### 题目分析 
#### 情况 1
抛开题目所说的正方形，这就是一道扫描线的题，只不过我们之前接触的多是封闭区间面积，如csp往年的矩形染色等。

但是这道题添加了树和正方形，乍一看正方形很唬人，但是反而是给你打暴力的，毕竟确定一个正方形只需要一个顶点和边长，我们考虑对每个所有可能的顶点和边长做二分搜索，可以拿  $\texttt{Subtask 1}$ 和 $\texttt{Subtask 2}$ 的分。
#### 情况 2
我们看到 $1 \le T \le 100$，思考能否通过树确定正方形位置，显然对于最优情况的正方形它一定会撑满所有可以使用的空间，换言之，它边旁边必定有树。

我们考虑把树建立的结构体从左到右进行排序，枚举出所有可能的区间，对于上下再来一次，就可以解决本题了，答案取所有可能结果的最大值。

#### 样例代码

```cpp
//-std=c++14
#include<bits/stdc++.h>
#define int long long
//n^2就是1e10了 
using namespace std;
int n,t,ans=0;
struct node{
	int x,y;
}tree[5005];
bool cmp1(node a, node b){//sort的加权排序，这次先排左右 
	return a.x < b.x;
}
bool cmp2(node a, node b){//那么接下来就是上下了 
	return a.y < b.y;
}
signed main(){
	scanf("%lld",&n);
	n++;//因为我们要对图边上建立树来方式扫描出界，所以现在先增大一个单位避免不扫描边对结果的影响
	scanf("%lld",&t);
	for(int i=1;i<=t;i++){
		scanf("%lld%lld",&tree[i].x,&tree[i].y);
	}
	tree[++t]={0,0};//边上建立树 
	tree[++t]={0,n};
	tree[++t]={n,n};
	tree[++t]={n,0};
	sort(tree+1,tree+1+t,cmp1);//排序 
	for(int i=1;i<=t;i++){
		int minn=1;
		int maxn=n;
		for(int j=i+1;j<=t;j++){
			if(maxn-minn-1<tree[j].x-tree[i].x-1){//搜索边界 
				break;
			}
			ans=max(ans,tree[j].x-tree[i].x-1);
			if(tree[j].y<=tree[i].y){
				minn=max(minn,tree[j].y);
			}
			if(tree[j].y>=tree[i].y){
				maxn=min(maxn,tree[j].y);
			}
		}
	}
	sort(tree+1,tree+1+t,cmp2);
	for(int i=1;i<=t;i++){
		int minn=1;
		int maxn=n;
		for(int j=i+1;j<=t;j++){
			if(maxn-minn-1<tree[j].y-tree[i].y-1){//搜索边界 
				break;
			}
			ans=max(ans,tree[j].y-tree[i].y-1);
			if(tree[j].x<=tree[i].x){
				minn=max(minn,tree[j].x);
			}
			if(tree[j].x>=tree[i].x){
				maxn=min(maxn,tree[j].x);
			}
		}	
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

