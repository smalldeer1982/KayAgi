# [USACO08DEC] Largest Fence G

## 题目描述

Farmer John has purchased N (5 <= N <= 250) fence posts in order to build a very nice-looking fence. Everyone knows the best fences are convex polygons where fence posts form vertices of a polygon. The pasture is represented as a rectilinear grid; fencepost i is at integer coordinates (x\_i, y\_i) (1 <= x\_i <= 1,000; 1 <= y\_i <= 1000).

Given the locations of N fence posts (which, intriguingly, feature no set of three points which are collinear), what is the largest number of fence posts FJ can use to create a fence that is convex?

For test cases worth 45% of the points for this problem, N <= 65.

Time limit: 1.2 seconds

POINTS: 400

Farmer John的农场里有N（5<=N<=250）个篱笆桩，每个都有独一无二的坐标(xi,yi)（1<=xi,yi<=1000）。他想选择尽量多的篱笆桩来构建他的围栏。这个围栏要美观，所以必须是凸多边形的。那他最多能选多少个呢？

所有的篱笆桩中不存在三点共线。


## 说明/提示

A square with two points inside.


The largest convex polygon is the pentagon (2,3), (3,2), (5,1), (5,5), (1,5).


## 样例 #1

### 输入

```
6 
5 5 
2 3 
3 2 
1 5 
5 1 
1 1 
```

### 输出

```
5 
```

# 题解

## 作者：Iscream2001 (赞：10)

首先O（n^4）的dp显然。。
但是n<=250跑不过。。。

考虑换一种方式dp。。。

观察凸包发现从一个点开始，向某一方向沿着边走一圈，边的斜率都是单调的。。。

于是考虑把所有边都连出来，然后按照极角序排序，然后枚举凸包起点dp。。因为保证了边的极角序单调，也就保证了dp顺序的正确性。。

效率是O（n^3），就可以通过此题了

最后是代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
#include<algorithm>
#define N 270
#define mod 100000000
#define ept 1e-12
#define LL long long
#define pa pair<int,int>
using namespace std;
int n,cnt,ans;
int f[N];
struct P{
	int l,r;
	double x,y;
}p[N],e[N*N];
bool cmp(P a,P b){
	return atan2(a.x,a.y)<atan2(b.x,b.y);
}
int main(){
	cnt=ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			e[++cnt].l=i;e[cnt].r=j;
			e[cnt].x=p[j].x-p[i].x;
			e[cnt].y=p[j].y-p[i].y;
		}
	sort(e+1,e+1+cnt,cmp);
	for(int i=1;i<=n;i++){
		memset(f,-62,sizeof(f));
		f[i]=0;
		for(int j=1;j<=cnt;j++)
			f[e[j].r]=max(f[e[j].r],f[e[j].l]+1);
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：water_tomato (赞：7)

本文同步发表于个人博客：[Link](https://www.watertomato.com/p2924-usaco08declargest-fence-g-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/P2924)

给定 $n$ 个点，求一个由若干个点连接成的凸多边形，所包含的点数最多，输出点数。



## 解析

先说解法：将所有边按照 `atan2(y,x)` 的值排序， 然后枚举凸多边形起点，再遍历排序后的边进行 dp 转移，复杂度为 $O(n^3)$。

大致思路与已有题解相同，但是我在这里想要阐述一个困惑我许久的点：为什么是 `atan2` ？

搜索[百度百科](https://baike.baidu.com/item/atan2/10931300?fr=aladdin)可以发现，`atan2` 这个函数的返回值是方位角（而 `atan` 返回的仅是数字的反正切值），具体地：

![](https://cdn.luogu.com.cn/upload/image_hosting/61yc721x.png)

然后我们来看一个凸多边形。

![](https://cdn.luogu.com.cn/upload/image_hosting/lpxuvfeg.png)

我们可以将这个凸多边形分为四部分，在图中分别用四种颜色表示。

对于蓝色部分：满足 $x,y>0$，返回值是一个在第一象限的值，记为 $k1$。

对于橙色部分：满足 $x<0,y>0$，返回值是一个在第二象限的值，记为 $k2$。

对于黄色部分：满足 $x,y<0$ 返回值是一个在第三象限的值，记为 $k3$。

对于灰色部分：满足 $x>0,y<0$ 返回值是一个在第四象限的值，记为 $k4$。

我们可以发现，$k3<k4<k1<k2$，同时对于每一个部分，容易发现其内部也是单调的（可以自行画图得出）。也就是说，如果我们找到了一个黄橙两个区域的交点作为起始点，那么接下来只要它所走的边的 `atan2(y,x)` 的值是单调递增的，最后回到这个点，形成的图形就一定是一个凸多边形。

因此，我们只需要枚举这个起始点，然后遍历排序好的边进行 dp，最后用这个起始点上的结果来更新答案就可以了，详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=255;
int n,cnt,ans;
int f[N];
struct P{
	int u,v,x,y;
}a[N],e[N*N];
inline bool cmp(P i,P j){//按照 atan2 的值排序
	return atan2(i.y,i.x)<atan2(j.y,j.x);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	for(int i=1;i<=n;i++)//连边
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			e[++cnt].u=i,e[cnt].v=j;
			e[cnt].x=a[j].x-a[i].x,e[cnt].y=a[j].y-a[i].y;
		}
	sort(e+1,e+1+cnt,cmp);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) f[j]=-1e9+7;
		f[i]=0;//枚举起始点
		for(int j=1;j<=cnt;j++)
			f[e[j].v]=max(f[e[j].v],f[e[j].u]+1);//动规
		ans=max(ans,f[i]);//更新答案
	}
	printf("%d\n",ans);
	return 0;
}
```





---

## 作者：ANJHZ (赞：3)

楼上dalao的说法或许不一定准确

在我的理解中，准确的讲法是：对于某个凸包，这个凸包上一定存在一点，使得凸包上的边从这一点连出的边开始，按照顺时针/逆时针方向极角有序。

我们枚举的这一点不仅仅是凸包的起点，同时也是满足上述条件的那一点。

接下来的dp就比较显然了，这里给出逆时针的写法，如果要改成顺时针只需要把atan2函数的x和y换下顺序，亲测两种写法都能A掉。




```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;
int n,ans,st,m,dp[251];
struct point
{
	int sx,sy;
	point operator -(point q){return (point){sx-q.sx,sy-q.sy};}
	int operator ^(point q){return sx*q.sy-q.sx*sy;}
}a[251];
struct edge
{
	point vec;
	int from,to;
}e[90001];
int cmp(edge p,edge q){return atan2(p.vec.sy,p.vec.sx)<atan2(q.vec.sy,q.vec.sx);}
void addedge(int from,int to)
{
	e[++m].from=from;e[m].to=to;
	e[m].vec=(a[to]-a[from]);
}
int main()
{
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d%d",&a[i].sx,&a[i].sy);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i==j) continue;
			addedge(i,j);
		}
	}
	sort(e+1,e+m+1,cmp);
	for(i=1;i<=n;i++)
	{
		memset(dp,-62,sizeof dp);
		dp[i]=0;
		for(j=1;j<=m;j++) dp[e[j].to]=max(dp[e[j].to],dp[e[j].from]+1);
		ans=max(ans,dp[i]); 
	}
	printf("%d\n",ans);
	return 0;
} 
```


---

## 作者：封禁用户 (赞：2)

## 解题思路：

题目意思找长度大于等于的 F 的连续的平均值最大。    

我是从 $-10^6$ 到 $10^6$ 开始二分的。二分一直是每个数减去平均值求前缀和，从长度为 L 的地方开始判断减去 $i-L$ 之前的最小值看是不是大于 0 即可。

代码如下，加注释：

```c
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define eps 1e-6
using namespace std;
const double INF=0x3f3f3f3f*1.0;
int n,m;
double arr[100005];
double sum[100005];

bool check(double num){
    double minn=INF;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+arr[i]-num;
    }
    double ans;
    for(int i=m;i<=n;i++){  ///看长度大于等于m的有没有大于等于0的
        minn=min(minn,sum[i-m]);  //i-m 之前的最小值
        ans=sum[i]-m;   //
        if(ans>=0) return true;   //这个平均值是可以达到的
    }
    return false;
}

void Calculation(){
    double left=1e-6;
    double right=1e6;
    while(left+eps<right){
        double mid=(left+right)/2;
        if(check(mid)) left=mid;
        else right=mid;
    }
    printf("%d\n",(int)(right*1000));
}


int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lf",&arr[i]);
    Calculation();
    return 0;
}
```


---

## 作者：Stevehim (赞：1)

# Luogu-P2924 [USACO08DEC] Largest Fence G

[原题链接](https://www.luogu.com.cn/problem/P2924)

## 题意简述

在平面直角坐标系中有 $N~(5 \le n \le 250)$ 个点，请你从这些点中找出一个**凸多边形**，使这个凸多边形包含的点最多。

## 题目分析

先讲一波我的奇(cuo)思(wu)妙(xiang)想(fa)。

一开始我以为这道题是素数筛法 + 凸包，但是一看也没发现和素数有关的东西，遂放弃。

后来我天真的以为这道题就是求凸包的顶点个数，看都没看难度标签就粘了个 Andrew 的板子上去，还过了样例！于是果断提交并：

![眼神一下子就清澈起来了呢](https://cdn.luogu.com.cn/upload/image_hosting/q6rqzyo3.png)

求凸包定点个数的错误在于：你怎么就知道凸包内部的点不够呢？这道题并没有限制说图形必须是凸包，那么就会出现如下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/n27br5sy.png)

最后的最后，我发现这道题是个 dp，这道题的数据范围以及洛谷的评测姬给了我们 $n^3$ 也能过这道题的机会。

我们考虑先给每对点建双向边，然后运用凸包的排序思想，可以发现我们如果按照极角排序，可以保证枚举到的图形的每条边相对上一条都是“向左拐”的，便满足了凸多边形的要求。

## 代码实现

首先说一个实现的细节，**警钟撅烂，警示后人**：

一般我们建双向边开数组的时候都会下意识敲一个 ```maxn << 1```，但这道题你不能这么敲，因为建的边总数会达到 $n^2$，所以开数组的时候要注意，不然会 RE。

另外，感觉楼上几篇题解所说“枚举凸包起点” 的说法有些不妥，事实上凸包顶点并不能包括所有点，而我们枚举的是所有点。

update in 2023.9.14:

感谢@[**JayintPan**](https://www.luogu.com.cn/user/613051)提出的问题：为什么 f 数组非得设成负无穷，这里给出解释：

这个 f 数组实际上是包括了两个功能：标记是否访问和计数，对于一条边 $e$ 如果起点 $from$ 没有被访问过，说明它并不是从起点延伸至此，而我们需要的凸多边形是必须要从起点开始的（不然枚举起点干什么是不是），这样我们就不去统计答案。那我们如何用 f 数组标记呢？答案是设成负无穷（实测 ```memset(f, -2, sizeof f)``` 即可），$0$ 不行是因为你这么搞相当于让所有点都能进行转移了（当然如果你额外设个 vis 数组的话当我没说），$-1$ 不行是因为转移方程，你本来是 $-1$，加一成了 $0$，这不相当于访问了吗对吧，因此要设成 $-2$ 以下，另外提示 ```memset(f, -2, sizeof f)``` 事实上会让整个数组变为 $-16843010$，可以通过本题。

下面是实现代码：

```cpp
#include <bits/stdc++.h>
#define maxn 270
using namespace std;
//dp就是一维的dp，设f[i] 表示当前为第 i 个点时最多能选择多少个
int n;
struct node{
	int from,to;
	double x,y;
}a[maxn],e[maxn * maxn]; //警钟敲烂，左移是乘二不是平方啊喂！
int cnt;
bool cmp(node a,node b){ //对于为什么使用atan在题解区有大佬解释
	return atan2(a.x, a.y) < atan2(b.x , b.y);
}
int f[maxn * maxn];
int ans = 0;
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n; i++)
		scanf("%lf %lf",&a[i].x,&a[i].y);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){ //n ^ 2 建边
			if(i == j) continue;
			e[++cnt].from = i,e[cnt].to = j;
			e[cnt].x = a[j].x - a[i].x; //计算，目的是排列极角，对于dp没有用处
			e[cnt].y = a[j].y - a[i].y;
		}
	}
	sort(e + 1,e + 1 + cnt, cmp);
	for(int i = 1;i <= n; i++){
		memset(f, -0x3f, sizeof f); //每次先清空，因为起点变了
		f[i] = 0; //设置最初点
		for(int j = 1; j <= cnt;j ++) //一个个枚举，保证单调顺序
			f[e[j].to] = max(f[e[j].to], f[e[j].from] + 1); //可以选可以不选
		ans = max(ans,f[i]);
	}
	printf("%d",ans);
	return 0;
}
```

然后是加 vis 数组的实现代码：

```cpp
#include <bits/stdc++.h>
#define maxn 270
using namespace std;
//dp就是一维的dp，设f[i] 表示当前为第 i 个点时最多能选择多少个
int n;
struct node {
	int from, to;
	double x, y;
} a[maxn], e[maxn * maxn]; //警钟敲烂，左移是乘二不是平方啊喂！
int cnt;
bool cmp(node a, node b) { //对于为什么使用atan在题解区有大佬解释
	return atan2(a.x, a.y) < atan2(b.x, b.y);
}
int f[maxn * maxn];
bool vis[maxn * maxn];
int ans = 0;
int main() {
	freopen("1.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf %lf", &a[i].x, &a[i].y);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) { //n ^ 2 建边
			if (i == j) continue;
			e[++cnt].from = i, e[cnt].to = j;
			e[cnt].x = a[j].x - a[i].x;
			e[cnt].y = a[j].y - a[i].y;
		}
	}
	sort(e + 1, e + 1 + cnt, cmp);
	for (int i = 1; i <= n; i++) {
		memset(f, -2, sizeof f);
		memset(vis, false, sizeof vis);
		vis[i] = true; //别忘了先设置为访问
		f[i] = 0;
		for (int j = 1; j <= cnt; j ++) //一个个枚举，保证单调顺序
			if (vis[e[j].from]) {
				f[e[j].to] = max(f[e[j].to], f[e[j].from] + 1); //可以选可以不选
				vis[e[j].to] = true;
			}
		ans = max(ans, f[i]);
	}
	printf("%d", ans);
	return 0;
}
```



---

## 作者：_Ch1F4N_ (赞：0)

注意到对于一个凸多边形而言，如果将其所有边看作向量后按照顺序写下来，再将起点平移到原点，那么写下这些向量的顺序实际上是顺时针（或者是逆时针）顺序。

所以考虑先把每条边拆成两个有向边，然后把这些有向边按照顺时针排序，那么任意一个凸包都可以表达为有向边序列的一个子序列。

但是并非任意一个子序列都合法，但是如果子序列上相邻的有向边首尾相接，并且子序列最后一个有向边形如 $x \to y$，第一个有向边形如 $y \to w$，那么这个子序列一定是一个凸包。

枚举第一条有向边的起点后暴力 dp 即可，时间复杂度 $O(n^3)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 300;
const double eps = 1e-9;
pair<int,int> P[maxn];
bool cmp(pair<int,int> X,pair<int,int> Y){
    //对边 X.first->X.second,Y.first->Y.second 排序
    //先分类
    int dx1=P[X.second].first-P[X.first].first,dy1=P[X.second].second-P[X.first].second;
    int dx2=P[Y.second].first-P[Y.first].first,dy2=P[Y.second].second-P[Y.first].second;
    int id1,id2;
    if(dx1==0&&dy1>0) id1=1;
    else if(dx1>0&&dy1>0) id1=2;
    else if(dx1>0&&dy1==0) id1=3;
    else if(dx1>0&&dy1<0) id1=4;
    else if(dx1==0&&dy1<0) id1=5;
    else if(dx1<0&&dy1<0) id1=6;
    else if(dx1<0&&dy1==0) id1=7;
    else id1=8;

    if(dx2==0&&dy2>0) id2=1;
    else if(dx2>0&&dy2>0) id2=2;
    else if(dx2>0&&dy2==0) id2=3;
    else if(dx2>0&&dy2<0) id2=4;
    else if(dx2==0&&dy2<0) id2=5;
    else if(dx2<0&&dy2<0) id2=6;
    else if(dx2<0&&dy2==0) id2=7;
    else id2=8;
    if(id1!=id2) return id1<id2;
    return (P[X.second].second-P[X.first].second)*(P[Y.second].first-P[Y.first].first)>(P[Y.second].second-P[Y.first].second)*(P[X.second].first-P[X.first].first);
}
int n;
vector< pair<int,int> > E;
int mx[maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>P[i].first>>P[i].second;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j) E.push_back(make_pair(i,j));
        }
    }
    int ans=0;
    sort(E.begin(),E.end(),cmp);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) mx[j]=-1e9;
        mx[i]=0;
        for(pair<int,int> e:E){
            int res=mx[e.first]+1;
            mx[e.second]=max(mx[e.second],res);
        }
        ans=max(ans,mx[i]);
    }
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

我们不难想到，如果你按照某一个方向去遍历最终的凸包，那么这些边的斜率是单调的。

这启示我们手动限制转移：我们见强制限定必须选 $i$ 点，然后按照所有的边的斜率顺序的将 $dp_r$ 和 $dp_l+1$ 更新最大值。最后只取 $dp_i$ 的值。

分析完毕，时间复杂度 $O(n\times n^2)=O(n^3)$，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct vecor {
	double x, y; vecor(double xi = 0, double yi = 0) :x(xi), y(yi) {}
	friend istream& operator>>(istream& l, vecor& r) { return l >> r.x >> r.y; }
	inline vecor operator-(const vecor& r) const { return vecor(x - r.x, y - r.y); }
	inline double arc() const { return atan2(y, x); }
}p[255];
struct edge { 
	double a; int l, r; 
	inline bool operator<(const edge& r) {
		return a != r.a ? a < r.a : l < r.l;
	}
}v[255 * 255];
int n, dp[255], vc, ans;
inline void tmax(int& l, const int r) { (l < r) && (l = r); }
signed main() {
	ios::sync_with_stdio(0); cin >> n;
	for (int i = 1; i <= n; ++i) cin >> p[i];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (i != j) v[++vc] = { (p[j] - p[i]).arc(),i,j };
	sort(v + 1, v + vc + 1);
	for (int i = 1; i <= n; ++i) {
		memset(dp, 0xcf, sizeof dp); dp[i] = 0;
		for (int j = 1; j <= vc; ++j)
			tmax(dp[v[j].r], dp[v[j].l] + 1);
		tmax(ans, dp[i]);
	}
	cout << ans << endl;
}
//私は猫です
```

---

## 作者：MoonCake2011 (赞：0)

首先，这一定是道 dp。

这题的 $n$ 很小，而 $O(n\log n)$ 算法所用的单调栈不适合记录成状态，所以考虑用 $O(n^2)$ 的算法来记录 dp 状态。

我们利用[这篇文章](https://www.luogu.com.cn/article/td3ah746)中的 Jarvis 算法记录状态进行 dp。

首先，我们将 $O(n^2)$ 条两点之间连的向量极角求出，然后按照极角进行排序。

接着我们需要去枚举凸包的起点，然后和 Jarvis 算法一样，按照极角大小遍历每条边。

这样，只要按顺序加边，我们都可以形成一个凸包。

设这条边是由 $i$ 到 $j$ 的，设 $dp_x$ 为以 $x$ 为末尾的凸包最多的点数。

那我们就可以用 $dp_i$ 去更新 $dp_j$。

最终答案为所有起点的 $dp$ 值（绕一圈绕回去了嘛）取个 `max`。

代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tot;
struct node{
	int x,y;
}a[260];
struct MoonCake2011{
	int u,v;
	double tt;
}e[260*260];
inline bool cmp(MoonCake2011 x,MoonCake2011 y){
	return x.tt<y.tt;
}
int dp[260];
main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i].x>>a[i].y;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			if(i==j) continue;
			e[++tot].u=i,e[tot].v=j;
			e[tot].tt=atan2(a[i].y-a[j].y,a[i].x-a[j].x);
		}
	sort(e+1,e+tot+1,cmp);
	int ans=0;
	for(int i=1;i<=n;++i){
		memset(dp,-0x3f,sizeof dp);
		dp[i]=0;
		for(int j=1;j<=tot;++j) dp[e[j].v]=max(dp[e[j].v],dp[e[j].u]+1);
		ans=max(ans,dp[i]);//绕回起点 
	}
	cout<<ans;
	return 0;
}
```

---

