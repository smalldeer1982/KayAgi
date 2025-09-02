# 【模板】旋转卡壳 | [USACO03FALL] Beauty Contest G

## 题目描述

给定平面上 $n$ 个点，求凸包直径。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$2\le n \le 50000$，$|x|,|y| \le 10^4$。

---

$\text{upd 2022.7.22}$：新增加四组 Hack 数据。

## 样例 #1

### 输入

```
4
0 0
0 1
1 1
1 0
```

### 输出

```
2```

# 题解

## 作者：_farawaystar_ (赞：104)

我们充分发扬人类智慧：

将所有点全部绕原点旋转同一个角度，然后按 $x\times x +y\times y$
排序。

根据数学直觉，在随机旋转后，答案中的两个点在数组中肯定不会离得太近。

所以我们只取最远点以及向前的 $4$ 个点来计算答案。

这样速度快得飞起，在 $n=50000$ 时都可以在 90ms 内卡过，hack 数据都起不到效果。

---

## 作者：lfxxx (赞：62)

> 管理备注：虽然此题解为乱搞，但是本乱搞是非常有意义的经典乱搞，故保留在题解区中供学习与参考。

我们充分发扬人类智慧：

将所有点全部绕原点旋转同一个角度，然后按 $x$ 坐标排序。

根据数学直觉，在随机旋转后，答案中的两个点在数组中肯定不会离得太近。

所以排序后把前 $20000$ 个点和后 $20000$ 个点暴力枚举更新答案。


这样开 `o2` 就可以过了。

可以想一想这样乱搞为什么能过？

假设不旋转，出题人会使用一组 $x$ 轴坐标特别远，$y$ 轴坐标特别近的数据来卡你。

但是旋转后 $x$ 轴坐标和 $y$ 轴坐标的差会变小。

所以就可以通过数据。

此外还有其他的排序方法。

比如将 $x$ 轴坐标与 $y$ 轴坐标的乘积作为排序关键字。

原理都是让坐标分布更均匀。


```cpp
#include<bits/stdc++.h>
#define double long double
using namespace std;
const int maxn=4e5+5;
struct node{
    int x,y,lx,ly;
}p[maxn];
bool cmp(node A,node B){
    if(A.x<B.x||(A.x==B.x&&A.y<B.y))
        return 1;
    else
        return 0;
}
int dis(node A,node B){
    return (A.lx-B.lx)*(A.lx-B.lx)+(A.ly-B.ly)*(A.ly-B.ly);
}
int n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int X,Y;
        cin>>X>>Y;
        p[i].lx=X;
        p[i].ly=Y;
        p[i].x=X*cos(1.14)-Y*sin(1.14);
        p[i].y=X*sin(1.14)+Y*cos(1.14);
    }
    sort(p+1,p+n+1,cmp);
    int ans=0;
    for(int i=1;i<=min(20000,n);i++){
        for(int j=n-min(20000,n)+1;j<=n;j++){
            ans=max(ans,dis(p[i],p[j]));
        }
    }
    cout<<ans<<'\n';
}
```


---

## 作者：xiezheyuan (赞：28)

upd 2024.9.26 修正一处精度误差带来的问题，欢迎大家提供 hack 数据。

## 前言

旋转卡壳（Rotating Calipers）可以在凸包上维护许多有用的信息，最常见的就是凸包直径（平面最远点对）。

注意：本文不介绍所谓的“人类智慧”乱搞做法。

## 算法流程

首先我们需要求出点集的凸包（我个人喜欢 Andrew 算法）。

![](https://cdn.luogu.com.cn/upload/image_hosting/q9yfxo8g.png)

然后我们考虑选定凸包的一条边所在的直线，比如 $AB$。然后找到凸包的所有顶点中离它最远的点，在这个例子中是 $D$。然后凸包直径就 **可能** 是 $AD$ 或 $BD$。

![](https://cdn.luogu.com.cn/upload/image_hosting/d47rcts0.png)

然后我们继续。逆时针选择下一条边 $AE$，这时我们发现最远点变成了 $C$，然后尝试用 $AC,EC$ 更新答案。以此类推。这样我们就找到了凸包直径。

但是这样子时间复杂度是 $O(n^2)$ 的，应该无法通过。

但是根据以前的经验，似乎最远点也是逆时针旋转的。换句话说，逆时针遍历的点到直线的距离单调。

这也可以用凸包的凸性来解释。我无法给出详细证明，但是大家不妨手动画几个图，就可以感性的理解了。

于是我们就可以用一个漂亮的双指针解决了。

## P145 【模板】旋转卡壳 代码

注意本题需要输出凸包直径的平方。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;

int n;

const double eps=1e-9;
int dcmp(double x){
    return (fabs(x)<=eps)?0:(x<0?-1:1);
}
struct Point{
    double x,y;
    Point(double X=0,double Y=0){x=X,y=Y;}
};
struct Vector{
    double x,y;
    Vector(double X=0,double Y=0){x=X,y=Y;}
};
inline Vector operator-(Point x,Point y){// 点-点=向量
    return Vector(x.x-y.x,x.y-y.y);
}
inline double cross(Vector x,Vector y){ // 向量叉积
    return x.x*y.y-x.y*y.x;
}
inline double operator*(Vector x,Vector y){ // 向量叉积
    return cross(x,y);
}
inline double len(Vector x){ // 向量模长
    return sqrt(x.x*x.x+x.y*x.y);
}

int stk[50005];
bool used[50005];
vector<Point> ConvexHull(Point* poly, int n){ // Andrew算法求凸包
    int top=0;
    sort(poly+1,poly+n+1,[&](Point x,Point y){
        return (x.x==y.x)?(x.y<y.y):(x.x<y.x);
    });
    stk[++top]=1;
    for(int i=2;i<=n;i++){
        while(top>1&&dcmp((poly[stk[top]]-poly[stk[top-1]])*(poly[i]-poly[stk[top]]))<=0){
            used[stk[top--]]=0;
        }
        used[i]=1;
        stk[++top]=i;
    }
    int tmp=top;
    for(int i=n-1;i;i--){
        if(used[i]) continue;
        while(top>tmp&&dcmp((poly[stk[top]]-poly[stk[top-1]])*(poly[i]-poly[stk[top]]))<=0){
            used[stk[top--]]=0;
        }
        used[i]=1;
        stk[++top]=i;
    }
    vector<Point> a;
    for(int i=1;i<=top;i++){
        a.push_back(poly[stk[i]]);
    }
    return a;
}

struct Line{
    Point x;Vector y;
    Line(Point X,Vector Y){x=X,y=Y;}
    Line(Point X,Point Y){x=X,y=Y-X;}
};

inline double DistanceToLine(Point P,Line x){// 点到直线的距离
    Vector v1=x.y, v2=P-x.x;
    return fabs(cross(v1,v2))/len(v1);
}

double RoatingCalipers(vector<Point> poly){// 旋转卡壳
    if(poly.size()==3) return len(poly[1]-poly[0]);
    int cur=0;
    double ans=0;
    for(int i=0;i<poly.size()-1;i++){
        Line line(poly[i],poly[i+1]);
        while(DistanceToLine(poly[cur], line) <= DistanceToLine(poly[(cur+1)%poly.size()], line)){
            cur=(cur+1)%poly.size();
        }
        ans=max(ans, max(len(poly[i]-poly[cur]), len(poly[i+1]-poly[cur])));
    }
    return ans;
}

Point poly[50005];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>poly[i].x>>poly[i].y;
    double v=RoatingCalipers(ConvexHull(poly, n));
    // cerr << v << '\n';
    cout<<(int)round(v * v);
    return 0;
}
```

---

## 作者：cjZYZtcl (赞：22)

### 前言

由于凸包求直径的时候对点执行双指针会出错，而本人不知什么原因不想写对边执行双指针的做法，于是充分发挥人类智慧，有感而发，写下这篇题解。

### 前置知识

二维凸包（Jarvis 算法）

### 思路

首先求出凸包。

如果还不会求凸包的可以先做[这题](https://www.luogu.com.cn/problem/P2742)。

由于要求直径，即凸包上各点的平面最远点对，所以可以想到枚举一个点，然后找到离该点最远的点，求距离。

所以问题就转化为了如何找距离一个点最远的点。

首先暴力找复杂度为 $O(n^2)$，显然行不通（但好像同机房大佬用暴力搞过去了？）

所以考虑一些性质。

在经过~~不仔细地~~分析了几组数据之后，发现好像可以用指针按顺时针或逆时针在凸包上移动维护最远的点，于是时间复杂度降为 $O(n)$。

交了一发，发现被测试点 #7 hack 了。

于是继续手玩，发现了一个较小的 Hack 数据：

![](https://cdn.luogu.com.cn/upload/image_hosting/b8yuko0i.png)

当 $BD < AD < CD$ 时，在枚举到 D 点时指针会出错。

于是有一个奇怪的想法：让指针按顺时针和逆时针都枚举一遍。

但不难发现，把上面的图稍微改一改然后对称一下拼起来就是 Hack 数据。

这时候本来只要把按点指针改称按边指针就好了，但本人突然不想写边的，于是开始思考奇怪的东西。

发现一个凸包内如果要出现上面的 Hack 情况，则至少包含 $2$ 个锐角，而多边形至多有 $3$ 个锐角，所以上述情况出现次数极少。

于是考虑一点人类智慧：当遇到这种情况的时候类似模拟退火的做法，设置初温，有概率取更短的距离，继续指针。

不难发现这样并不会增加很多的移动次数，所以时间复杂度很优秀。

有些小细节可以看代码。

### AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

mt19937_64 rnd(time(NULL));

struct node{
	int x, y;
} a[100005], st[100005];

inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}

inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}

signed main() {
    auto calc = [&](node a, node b, node c) -> int {
        return (a.x - b.x) * (c.y - b.y) - (c.x - b.x) * (a.y - b.y);
    };

    auto dis = [&](node a, node b) -> int {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    };

	int n = read();

	for (int i = 1; i <= n; i++) {
        a[i].x = read(), a[i].y = read();

		if (i > 1 && (a[i].y > a[1].y || (a[i].y == a[1].y && a[i].x > a[1].x))) swap(a[i], a[1]);
	}

	sort(a + 2, a + n + 1, [&](node x, node y) {
        int z = calc(x, a[1], y);
        return (z > 0 || (z == 0 && dis(a[1], y) > dis(a[1], x)));
    });

	st[1] = a[1];
    st[2] = a[2];
	int cnt = 2;

    if (n > 2) st[++cnt] = a[3];

	for (int i = 4; i <= n; i++) {
		while (cnt > 2 && calc(st[cnt - 1], st[cnt], a[i]) >= 0) cnt--;

		st[++cnt] = a[i];
	}

    int t = 1;

    auto nxt = [&](int x) {
        return x % cnt + 1;
    };

    int ans = 0;

    for (int i = 1; i <= cnt; i++) {
        double T = 1, down = 0.4;

        ans = max(ans, dis(st[t], st[i]));

        while (dis(st[t], st[i]) < dis(st[nxt(t)], st[i]) || (dis(st[t], st[i]) >= dis(st[nxt(t)], st[i]) && exp((dis(st[nxt(t)], st[i]) - dis(st[t], st[i])) / T) < (rnd() % 100) / 100.0)) {
            t = nxt(t);

            T *= down;

            ans = max(ans, dis(st[t], st[i]));
        }
    }

    auto Nxt = [&](int x) {
        x--;

        if (!x) x = cnt;

        return x;
    };
    
    t = cnt;

    for (int i = cnt; i >= 1; i--) {
        double T = 1, down = 0.5;

        ans = max(ans, dis(st[t], st[i]));

        while (dis(st[t], st[i]) < dis(st[Nxt(t)], st[i]) || (dis(st[t], st[i]) >= dis(st[Nxt(t)], st[i]) && exp((dis(st[Nxt(t)], st[i]) - dis(st[t], st[i])) / T) < (rnd() % 100) / 100.0)) {
            t = Nxt(t);

            T *= down;

            ans = max(ans, dis(st[t], st[i]));
        }
    }

    write(ans);
}
```

---

## 作者：王熙文 (赞：15)

## 前言

洛谷题解区和 oi-wiki 都没有这个算法的证明，可能是证明太恶心了。因此我来写一个不严谨的证明。有一些结论可以直接从图形看出来，就不写证明了，因为这些的证明可能需要深入到凸包的定义等等，太麻烦了。

## 问题

[P1452](https://www.luogu.com.cn/problem/P1452)。

## 思路

* 结论 1：

> 凸包的直径为凸包上的点两两距离的最大值。

证明：首先凸包的直径一定在凸包的边上，否则将这条线段延长一定能交于边上。现在只需要考虑两点分别在两条边上的距离的最大值。根据勾股定理可知，一个点与一条边上的点的距离的最大值一定为这个点与边的端点的距离的最大值。考虑调整，对于两个点，可以先将一个点变成边的端点，再将另一个点变成边的端点，这样一定更优。所以两点分别在两条边上的距离的最大值为两条边的端点两两距离的最大值。

* 结论 2：

> 在凸包上所有点距离任意一条边的距离（垂线的长度）是单峰函数。

证明：可以想象将凸包旋转使得这条边与 x 轴重合，此时点的距离即为 y 坐标。如果存在三个点使得中间的点与边的距离最小，则第三个点一定是向外连出去的（如果向内就不可能再连到这条边了），而第三个点必须需要连回来，这样反复横跳的图形一定不是凸包。

下文称与一条边距离最大的点为这条边对应的点。

* 结论 3：

> 从一条边顺时针移动到相邻的那条边，则边对应的点要么不动要么顺时针移动。

证明：假设对于两条边，考虑第二条边对应的点在第一条边的对应的点的哪里。如下图，下面是两条边，上面两条直线的交点是第一条边对应的点，那么第二条边对应的点必须在阴影部分（在线段 1 下面且在线段 2 上面），所以移动方向不能为逆时针。

![](https://cdn.luogu.com.cn/upload/image_hosting/9h9fbpe1.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

* 结论 4：

> 从一条边 $l_1$ 顺时针移动到这条边的端点 $A$，若 $A$ 和与这个点距离最大的点 $B$ 是凸包的直径，则从 $l_1$ 对应的点 $C$ 到与 $B$ 的移动方向也是顺时针。

证明：因为 $A$ 是凸包的直径的一端，所以 $B$ 一定在 $l_1$ 的垂直平分线的逆时针移动方向侧（如果将这条边放到图的最下面，则逆时针移动方向侧即为右侧）。所以如果移动方向为逆时针，$C$ 与 $A$ 的距离就比 $B$ 与 $A$ 的距离大（首先 $C$ 到 $l_1$ 的垂线比 $B$ 大，其次因为是逆时针移动且 $B$ 在垂直平分线逆时针移动方向侧，$C$ 的垂足到 $A$ 的距离比 $B$ 大），与定义矛盾。详见下图，下面横着的线为边，竖着的线为垂直平分线，点 1 为 $C$，点 2 为 $B$。如果移动方向为逆时针，则点 2 的距离一定不如点 1 大。

![](https://cdn.luogu.com.cn/upload/image_hosting/j5se2jnq.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

* 结论 5：

> 在点随机移动 eps 个距离后，凸包的直径为每条边的两个端点与这条边对应的点的距离的最大值。

因为下面的证明需要满足过一个点的两条边对应的点作对应边的平行线后两条平行线的交点不为凸包上的点（比如正六边形就不满足），所以需要将点随机移动 eps 个距离。原因详见下文。但是如果不随机移动点也有可能是正确的，只是我不会证明。

证明：对于一个直径的端点 $A$，考虑过包含它的两条边 $l_1,l_2$ 的对应点 $B,C$ 分别作 $l_1,l_2$ 的平行线，设为 $l_3,l_4$。则根据对应点的定义凸包内的所有点都在 $l_3,l_4$ 的下面。设与 $A$ 距离最大的点为 $D$，根据结论 4，$D$ 在凸包中的位置一定在 $B,C$ 之间。如果 $D$ 是 $B$ 或 $C$，则已经找到了这条有可能是直径的线段 $AD$。否则，当 $D$ 不为 $l_3,l_4$ 的交点时，包含 $D$ 的两条边中至少有一条边 $l_5$ 的斜率在 $l_3,l_4$ 之间且不与它们相等。那么 $l_5$ 对应的点一定为 $A$。所以一定会得到 $AD$ 这条线段。

![](https://cdn.luogu.com.cn/upload/image_hosting/osylch87.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

已知了这 5 个结论，就可以证明旋转卡壳的正确性了。算法的流程是：遍历每条边，使用双指针找到每条边对应的点。并求出边的两个端点与这个点的距离。这个距离的最大值即为答案。

过程中需要求一个点与一条直线的距离。可以求出这个点与直线上任意两个点组成的三角形的面积，再乘 $2$ 除以两个点的距离。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define double long double
#define pdd pair<double,double>
double get_dis(pdd x,pdd y)
{
	return sqrt((x.first-y.first)*(x.first-y.first)+(x.second-y.second)*(x.second-y.second));
}
double check(pdd l1,pdd r1,pdd l2,pdd r2)
{
	return (r1.first-l1.first)*(r2.second-l2.second)-(r1.second-l1.second)*(r2.first-l2.first);
}
int n;
pdd a[100010];
bool cmp(pdd x,pdd y) { return check(a[1],x,a[1],y)>0; }
int tot; pdd st[100010];
double get_dis(pdd x,pdd y,pdd z)
{
	double a=get_dis(x,y),b=get_dis(x,z),c=get_dis(y,z);
	double p=(a+b+c)/2;
	return sqrt(p*(p-a)*(p-b)*(p-c))*2/a;
}
int main()
{
	cin>>n;
	double in=1e9; int wz;
	mt19937 rnd(time(0));
	for(int i=1; i<=n; ++i)
	{
		cin>>a[i].first>>a[i].second;
		a[i].first+=rnd()*1.0/1e15,a[i].second+=rnd()*1.0/1e15;
		if(in>a[i].second) in=a[i].second,wz=i;
	}
	swap(a[1],a[wz]);
	sort(a+2,a+n+1,cmp);
	st[tot=1]=a[1];
	for(int i=2; i<=n; ++i)
	{
		while(tot>=2 && check(st[tot-1],st[tot],st[tot],a[i])<0) --tot;
		st[++tot]=a[i];
	}
	for(int i=1; i<=tot; ++i) st[i+tot]=st[i];
	int now=2;
	double ans=0;
	for(int i=1; i<=tot; ++i)
	{
		while(get_dis(st[i],st[i+1],st[now])<get_dis(st[i],st[i+1],st[now+1])) ++now;
		ans=max(ans,max(get_dis(st[i],st[now]),get_dis(st[i+1],st[now])));
	}
	printf("%.0Lf",ans*ans);
	return 0;
}
```

---

## 作者：ByGones (赞：13)

## 前言
因为发现没人用 K-D Tree，就写了这篇题解。
## 转化
K-D Tree 最典型的应用应该是[平面 k 远点对](https://www.luogu.com.cn/problem/P4357)，但这题要求的是凸包直径，如何把问题转化为 K-D Tree 能解决的呢？

其实，凸包的直径就是平面最远点对的距离，可以参考[网上的证明](https://www.cnblogs.com/Ishtar/p/10010792.html)。所以，只要把[平面 k 远点对](https://www.luogu.com.cn/problem/P4357)中的 $k$ 改成 $1$，就是本题的代码。
## 代码
轮换维度分割建树的复杂度是 $O(n\log n)$ 的，查询操作单次 $O(\sqrt n)$，对于比较随机的数据，因为有估价函数，所以肯定跑不满，这题的范围又比较小，所以 K-D Tree [跑得飞快](https://www.luogu.com.cn/record/111433860)。

复杂度的证明可以参考[这篇](https://blog.csdn.net/qq_50332374/article/details/123242226)。
```cpp
/*
写了一些简要的注释，P4357的题解已经挺详细的了，
我觉得 EnofTaiPeople 的那篇要比第一篇要好一些，
巧的是，我刚看完那篇题解，他就上日报了。
https://www.luogu.com.cn/blog/502410/k-d-tree-sharp-weapon-of-high-dimension
*/
#include<bits/stdc++.h>
#define F(i,x,y) for(int i=(x);i<=(y);i++)
#define mid ((l+r)>>1)
using namespace std;
const int N=100010;
typedef long long ll;
template<typename T>inline void chkmax(T &x,T y){x=max(x,y);}
template<typename T>inline void chkmin(T &x,T y){x=min(x,y);}
int n,k;
priority_queue<ll,vector<ll>,greater<ll> >qu;
int lx[N],rx[N],ly[N],ry[N],lc[N],rc[N];
struct T{
	int x,y;
}a[N];
bool cmpx(T x,T y)
{
	return x.x<y.x;
}
bool cmpy(T x,T y)
{
	return x.y<y.y;
}
ll sq(int x)
{
	return ll(x)*x;
}
ll dis(int x,int y)
{
	return sq(a[x].x-a[y].x)+sq(a[x].y-a[y].y);
}
void maintain(int x)//维护x节点的信息，lx,rx,ly,ry表示这个节点对应平面四个角的坐标。
{
	lx[x]=rx[x]=a[x].x;
	ly[x]=ry[x]=a[x].y;
	if(lc[x])
	{
		chkmin(lx[x],lx[lc[x]]);
		chkmax(rx[x],rx[lc[x]]);
		chkmin(ly[x],ly[lc[x]]);
		chkmax(ry[x],ry[lc[x]]);
	}
	if(rc[x])
	{
		chkmin(lx[x],lx[rc[x]]);
		chkmax(rx[x],rx[rc[x]]);
		chkmin(ly[x],ly[rc[x]]);
		chkmax(ry[x],ry[rc[x]]);
	}
}
int build(int l=1,int r=n,int t=0)
{
	if(r<l)return 0;
	if(t)nth_element(a+l,a+mid,a+r+1,cmpx);
	else nth_element(a+l,a+mid,a+r+1,cmpy);//轮换维度分割，K-D Tree的核心。
	lc[mid]=build(l,mid-1,t^1);
	rc[mid]=build(mid+1,r,t^1);
	maintain(mid);
	return mid;
}
ll f(int x,int y)
{
	return sq(max(a[x].x-lx[y],rx[y]-a[x].x))+sq(max(a[x].y-ly[y],ry[y]-a[x].y));//点x到y平面中最远的点（应该是四个顶点中的一个）的距离。
}
void query(int x,int l=1,int r=n)
{
	if(r<l||f(x,mid)<=qu.top())return;//如果最远距离都没以前的最大值大，就没必要继续搜下去了。
	if(dis(mid,x)>qu.top())
	{
		qu.pop();
		qu.push(dis(mid,x));//更新最大值。
	}
	if(l==r)return;
	if(f(x,lc[mid])>f(x,rc[mid]))//f在这里作为估价函数，能进一步优化K-D Tree。
	{
		query(x,l,mid-1);
		query(x,mid+1,r);
	}
	else
	{
		query(x,mid+1,r);
		query(x,l,mid-1);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	k=2;//k本来应该改成1的，但由于一个点对会正反算两次，所以k=2。
	F(i,1,k)qu.push(0);
	F(i,1,n)cin>>a[i].x>>a[i].y;
	build();
	F(i,1,n)query(i);//对于每个点都询问一遍最长距离。
	cout<<qu.top();
	return 0;
}
```
码风不好看但自我感觉写的还算清楚，如有问题可以在评论中指出。

---

## 作者：2c_s (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P1452)

我们继续发扬人类智慧：

**不用旋转即可 AC。**

把所有点按照横坐标 $x$ 从小到大排序。根据数学直觉，最远的两个点肯定不会离得太近。所以我们只取最远点向前 $1000$ 个点来计算答案，这样速度快得飞起，不仅不会超时，连 Hack 也没有效果。

---

## 作者：1saunoya (赞：7)

好像题解没有用这个做法的。。

不会求凸包直径，我们先把凸包求出来，然后用 BZOJ 最远点的办法。

也就是决策单调性分治。

[BZOJ 最远点](https://www.cnblogs.com/Isaunoya/p/12820028.html)

```cpp
// powered by c++11
// by Isaunoya
#include <bits/stdc++.h>

#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)

using namespace std;
using db = double;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

#define pii pair<int, int>
#define fir first
#define sec second

template <class T>

void cmax(T& x, const T& y) {
  if (x < y) x = y;
}

template <class T>

void cmin(T& x, const T& y) {
  if (x > y) x = y;
}

#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back

template <class T>

void sort(vector<T>& v) {
  sort(all(v));
}

template <class T>

void reverse(vector<T>& v) {
  reverse(all(v));
}

template <class T>

void unique(vector<T>& v) {
  sort(all(v)), v.erase(unique(all(v)), v.end());
}

void reverse(string& s) { reverse(s.begin(), s.end()); }

const int io_size = 1 << 23 | 233;
const int io_limit = 1 << 22;
struct io_in {
  char ch;
#ifndef __WIN64
  char getchar() {
    static char buf[io_size], *p1 = buf, *p2 = buf;

    return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, io_size, stdin), p1 == p2) ? EOF : *p1++;
  }
#endif
  io_in& operator>>(char& c) {
    for (c = getchar(); isspace(c); c = getchar())
      ;

    return *this;
  }
  io_in& operator>>(string& s) {
    for (s.clear(); isspace(ch = getchar());)
      ;

    if (!~ch) return *this;

    for (s = ch; !isspace(ch = getchar()) && ~ch; s += ch)
      ;

    return *this;
  }

  io_in& operator>>(char* str) {
    char* cur = str;
    while (*cur) *cur++ = 0;

    for (cur = str; isspace(ch = getchar());)
      ;
    if (!~ch) return *this;

    for (*cur = ch; !isspace(ch = getchar()) && ~ch; *++cur = ch)
      ;

    return *++cur = 0, *this;
  }

  template <class T>

  void read(T& x) {
    bool f = 0;
    while ((ch = getchar()) < 48 && ~ch) f ^= (ch == 45);

    x = ~ch ? (ch ^ 48) : 0;
    while ((ch = getchar()) > 47) x = x * 10 + (ch ^ 48);
    x = f ? -x : x;
  }

  io_in& operator>>(int& x) { return read(x), *this; }

  io_in& operator>>(ll& x) { return read(x), *this; }

  io_in& operator>>(uint& x) { return read(x), *this; }

  io_in& operator>>(ull& x) { return read(x), *this; }

  io_in& operator>>(db& x) {
    read(x);
    bool f = x < 0;
    x = f ? -x : x;
    if (ch ^ '.') return *this;

    double d = 0.1;
    while ((ch = getchar()) > 47) x += d * (ch ^ 48), d *= .1;
    return x = f ? -x : x, *this;
  }
} in;

struct io_out {
  char buf[io_size], *s = buf;
  int pw[233], st[233];

  io_out() {
    set(7);
    rep(i, pw[0] = 1, 9) pw[i] = pw[i - 1] * 10;
  }

  ~io_out() { flush(); }

  void io_chk() {
    if (s - buf > io_limit) flush();
  }

  void flush() { fwrite(buf, 1, s - buf, stdout), fflush(stdout), s = buf; }

  io_out& operator<<(char c) { return *s++ = c, *this; }

  io_out& operator<<(string str) {
    for (char c : str) *s++ = c;
    return io_chk(), *this;
  }

  io_out& operator<<(char* str) {
    char* cur = str;
    while (*cur) *s++ = *cur++;
    return io_chk(), *this;
  }

  template <class T>

  void write(T x) {
    if (x < 0) *s++ = '-', x = -x;

    do {
      st[++st[0]] = x % 10, x /= 10;
    } while (x);

    while (st[0]) *s++ = st[st[0]--] ^ 48;
  }

  io_out& operator<<(int x) { return write(x), io_chk(), *this; }

  io_out& operator<<(ll x) { return write(x), io_chk(), *this; }

  io_out& operator<<(uint x) { return write(x), io_chk(), *this; }

  io_out& operator<<(ull x) { return write(x), io_chk(), *this; }

  int len, lft, rig;

  void set(int _length) { len = _length; }

  io_out& operator<<(db x) {
    bool f = x < 0;
    x = f ? -x : x, lft = x, rig = 1. * (x - lft) * pw[len];
    return write(f ? -lft : lft), *s++ = '.', write(rig), io_chk(), *this;
  }
} out;
#define int long long

template <int sz, int mod>

struct math_t {
  math_t() {
    fac.resize(sz + 1), ifac.resize(sz + 1);
    rep(i, fac[0] = 1, sz) fac[i] = fac[i - 1] * i % mod;

    ifac[sz] = inv(fac[sz]);
    Rep(i, sz - 1, 0) ifac[i] = ifac[i + 1] * (i + 1) % mod;
  }

  vector<int> fac, ifac;

  int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = x * x % mod)
      if (y & 1) ans = ans * x % mod;
    return ans;
  }

  int inv(int x) { return qpow(x, mod - 2); }

  int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
  }
};

int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
int lcm(int x, int y) { return x * y / gcd(x, y); }

int n;

struct point { int x, y; };

int dis(point x, point y) { return (x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y); }
const int maxn = 5e5 + 55;
point a[maxn];
int ans[maxn];

int getid(int x) { return (x > n) ? (x - n) : x; }
bool chk(int t, int x, int y) {
  int distx = dis(a[t], a[x]);
  int disty = dis(a[t], a[y]);
  if (x > t + n || x < t) distx *= -1;
  if (y > t + n || y < t) disty *= -1;
  if (distx == disty) return getid(x) > getid(y);
  return distx < disty;
}

void solve(int l, int r, int ql, int qr) {
  if (l > r) return;
  int mid = l + r >> 1, nxt = ql;
  for (int i = ql; i <= qr; i++)
    if (chk(mid, nxt, i)) nxt = i;
  ans[mid] = getid(nxt);
  solve(l, mid - 1, ql, nxt);
  solve(mid + 1, r, nxt, qr);
}

const double pi = acos(-1);

struct Vector {
	int x, y;
  Vector(int _x = 0, int _y = 0) { x = _x, y = _y; }
//  Vector operator+(const Vector& rhs) const { return Vector(x + rhs.x, y + rhs.y); }
  Vector operator-(const Vector& rhs) const { return Vector(x - rhs.x, y - rhs.y); }
  double operator^(const Vector& rhs) const { return x * rhs.y - y * rhs.x; }
//  double dis() { return sqrt(x * x + y * y); }
  bool operator<(const Vector& rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
};

Vector rtt(Vector x, double tht) {
  return Vector(x.x * cos(tht) - x.y * sin(tht), x.x * sin(tht) + x.y * cos(tht));
}
vector<Vector> p;

signed main() {
  // code begin.
  in >> n;
  for (int i = 1; i <= n; i++) in >> a[i].x >> a[i].y, p.push_back({a[i].x, a[i].y});
  int sz = p.size() - 1;
  sort(p.begin(), p.end());
  static int st[233333], top = 0;
  st[++top] = 0, st[++top] = 1;
  auto ins = [&](int x) {
    while (top >= 2 && ((p[st[top - 1]] - p[st[top]]) ^ (p[st[top]] - p[x])) <= 0) --top;
    st[++top] = x;
  };
  for (int i = 2; i <= sz; i++) {
    ins(i);
  }
  int cnt = 0;
  for(int i = 1 ; i <= top ; i ++) a[++ cnt] = { p[st[i]].x, p[st[i]].y };
  st[top = 1] = sz, st[++top] = sz - 1;
  for (int i = sz - 2; ~i; --i) {
    ins(i);
  }
	for(int i = 2 ; i <= top ; i ++) a[++ cnt] = { p[st[i]].x, p[st[i]].y };
  for (int i = 1; i <= cnt; i++) a[i + cnt] = a[i];
  solve(1, cnt, 1, cnt * 2);
  int res = 0;
  for (int i = 1; i <= cnt; i++) cmax(res, dis(a[i], a[ans[i]]));
  out << res << '\n';
  return 0;
  // code end.
}
```

---

## 作者：andychen_2012 (赞：5)

## 一、解题思路

特别注明，本题解介绍非常乱搞但很有用的做法（~~甚至于冲到最优解榜一，这是我没有想到的~~）。

首先我们根据凸包直径可以想到我们找的必定是最远点对。

很明显，一个凸包的直径必定是包含其的点集的最远点对（这应该是感性理解的，证明的话我也不太会，不过应该可以通过凸包定义直接得出）。

那么问题就转化为求这个点集的最远点对。

观察到 $|x|,|y| \le 10^4$，我们可以开两个桶 $mx_i,mn_i$，表示 $x=i$ 这条直线上最高的点和最低的点。

那么很明显，最后的答案就是这些点间的最大距离。

我们从左往右数这些点，并且开一个 $up,down$ 分别表示当前已经遍历的最高 $y$ 值和最低 $y$ 值。初始 $up=-10^4,down=10^4$。

假如当前的 $mn_i \ge down,mx_i \le up$，我们就可以不用遍历 $x=i$ 这条线了，因为很明显左边的点会有比它答案更高的。

我们注意到假设 $i \le j$，则 $dis((i,mx_i),(j,mn_j))\ge dis((i,mx_i),(j,mx_j))$，同理我们有 $dis((i,mn_i),(j,mx_j))\ge dis((i,mn_i),(j,mn_j))$。其中 $dis((x_1,y_1),(x_2,y_2))$ 表示 $(x_1,y_1),(x_2,y_2)$ 两点间的距离的平方。这里不给出证明，因为比较容易得出。

因此我们只需要判断 $ans,dis((i,mx_i),(j,mn_j)),dis((i,mn_i),(j,mx_j))$ 三者间的大小。其中 $ans$ 表示当前答案，初始值为 $0$。

然后我们用一个看起来像是 $O(n^2)$ 的东西进行两层循环遍历。不过实际上经过以上这些优化，时间非常玄学，并且非常快。

当然，注意到，直径的 $x$ 有可能相等，于是第二层循环是从 $i$ 开始，而不是 $i+1$。

## 二、解题代码

```cpp
#include<cstdio>
inline int read(){
	int x=0;
	int f=0,ch=0;
	while(ch<48||ch>57) f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return f?-x:x;
}
inline void write(int x,char end=' '){
	if(x==0){
		putchar('0');
		putchar(end);
		return;
	}
	if(x<0) putchar('-'),x=-x;
	int ch[70]={0},cnt=0;
	while(x){
		ch[cnt++]=(int)(x%10);
		x/=10;
	}
	while(cnt--) putchar(ch[cnt]+48);
	putchar(end);
}
const int N=5e4+5;
const int ad=1e4;
struct node{
	int x,y;
}e[N];
int n;
int mx[N],mn[N];
int vis[N];
int nxt[N];
inline int dis(int x1,int y1,int x2,int y2){
	int x=(x1-x2),y=(y1-y2);
	return x*x+y*y;
}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
int ans;
int main(){
	n=read();
	for(int i=0;i<N;++i)
		mx[i]=-ad,mn[i]=ad;
	for(int i=1;i<=n;++i){
		e[i].x=read()+ad;
		e[i].y=read();
		vis[e[i].x]=1;
		mx[e[i].x]=max(mx[e[i].x],e[i].y);
		mn[e[i].x]=min(mn[e[i].x],e[i].y);
	}
	int st=e[1].x,end=e[1].x;
	for(int i=2;i<=n;++i){
		st=min(st,e[i].x);
		end=max(end,e[i].x);
	}
	int lst=st;
	for(int i=st+1;i<=end;++i){
		if(vis[i]){
			nxt[lst]=i;
			lst=i;
		}
	}
	nxt[end]=2*ad+1;
	int ly=ad,uy=-ad;
	for(int i=st;i<=end;i=nxt[i]){
		if(mn[i]>=ly&&mx[i]<=uy) continue;
		ly=min(ly,mn[i]);
		uy=max(uy,mx[i]);
		for(int j=i;j<=end;j=nxt[j]){
			ans=max(ans,dis(i,mx[i],j,mn[j]));
			ans=max(ans,dis(i,mn[i],j,mx[j]));
		}
	}
	write(ans);
	return 0;
}
```

---

