# Satanic Panic

## 题目描述

You are given a set of $ n $ points in a 2D plane. No three points are collinear.

A pentagram is a set of $ 5 $ points $ A,B,C,D,E $ that can be arranged as follows. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/f942ae06c7e29cb9bc6462315be09bb7d5b4c362.png) Note the length of the line segments don't matter, only that those particular intersections exist.

Count the number of ways to choose $ 5 $ points from the given set that form a pentagram.

## 说明/提示

A picture of the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/ecb5db206846ce3b41c177fcaeaebe0ee2b1bb2a.png) A picture of the second sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/4f7f38f01a0904403461b302f8dc7d443ccc0e93.png) A picture of the third sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/d922b8e812b7b67b3a0bbbb474a47be87ee53781.png)

## 样例 #1

### 输入

```
5
0 0
0 2
2 0
2 2
1 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
0 0
4 0
0 4
4 4
2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10
841746 527518
595261 331297
-946901 129987
670374 -140388
-684770 309555
-302589 415564
-387435 613331
-624940 -95922
945847 -199224
24636 -565799
```

### 输出

```
85
```

# 题解

## 作者：zerc (赞：9)

首先五角星可以转化成 $5$ 个点的凸包，然后就可以用计算几何来求解。

怎么判断是否合法呢？可以用叉积，当然也可以通过极角排序保证合法，我用的是后者。

然后就是统计答案，这里用 `DP`，$f[i][j][k]$ 表示 $i$ 到 $j$ 有 $k$ 条路径。

对于每条边而言都有 $f[x_i][y_i][1]=1$，即初始化；

再考虑转移，对于点 $j$，$f[j][x_i][k]=f[j][x_i][k]+f[j][y_i][k-1]$；

最后的答案是 $\sum_{i=1}^{n}f[i][i][5]$，即所有从自身出发，经过$5$条边又能回到自身的方案数。

最后是代码，注意 `Line` 中 `x`，`y` 为点的编号。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[333][333][6];
int n, cnt;
struct Point {
    double x, y;
} point[100010];
struct Line {
    int x, y; double sigma;
    void MakeLine (int a, int b) {
        x = a, y = b; sigma = atan2(point[b].y-point[a].y, point[b].x-point[a].x); }
    friend bool operator < (Line a, Line b) {
        return a.sigma < b.sigma; }
} line[100010];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &point[i].x, &point[i].y);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i!=j) line[++cnt].MakeLine(i, j);
    sort(line+1, line+cnt+1);
    for (int i = 1; i <= cnt; i++) {
        f[line[i].x][line[i].y][1] = 1;    
        for (int j = 1; j <= n; j++)
            for (int k = 2; k <= 5; k++)
                f[j][line[i].y][k] += f[j][line[i].x][k-1]; }
    for (int i = 1; i <= n; i++)
        f[0][0][0] += f[i][i][5];
    printf("%lld\n", f[0][0][0]);
    return 0;
}
```

---

## 作者：wucstdio (赞：5)

VP差5分钟调出来，好自闭啊。

首先考虑五个点在什么情况下会形成五角星。答案是这五个点形成了一个五个点的凸包。

所以就可以用DP的方法来求凸包了。

首先枚举一个点$st$，表示凸包最左下角的点，然后设$f[num][i]$表示已经选了$num$个点，最后一个点是$i$的方案数。

由于要满足凸包的性质，所以我们还需要记录一维$j$，表示它上一个点是哪一个。

考虑转移，如果我们能够从$f[x][i][j]$转移到$f[x+1][k][i]$（也就是新加入一个点$k$），那么应该满足$j,i,k$这三个点形成了一个凸壳，也就是下面这种情况：

![](https://cdn.luogu.com.cn/upload/pic/61356.png)

可以用叉积来判断是否合法，如果$\vec{ji}\times\vec{jk}<0$，就说明可以形成凸壳。

最后枚举$f[4][i][j]$，检查能否和$st$这个点形成凸包即可。

为了能够DP出所有的凸壳，我们还需要枚举完$st$后将所有的点按照到$st$的极角排序，然后从大到小转移。

时间复杂度$O(n^4)$，更准确的说是$O\left(\dfrac{n^4}{8}\right)$，CF的机子那么快就过了。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
struct Point
{
	ll x,y;
	Point(ll xx=0,ll yy=0){x=xx,y=yy;}
	Point operator+(Point p){return Point(x+p.x,y+p.y);}
	Point operator-(Point p){return Point(x-p.x,y-p.y);}
	Point operator*(ll d){return Point(x*d,y*d);}
	Point operator/(ll d){return Point(x/d,y/d);}
	ll dot(Point p){return x*p.x+y*p.y;}
	ll det(Point p){return x*p.y-y*p.x;}
	double alpha(){return atan2(y,x);}
}p[305],a[305];
int n,m;
ll f[6][305][305];
bool cmp(Point a,Point b)
{
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
bool cmp2(Point a,Point b)
{
	return a.alpha()>b.alpha();
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%I64d%I64d",&p[i].x,&p[i].y);
	sort(p+1,p+n+1,cmp);
	ll ans=0;
	for(int st=1;st<=n;st++)
	{
		memset(f,0,sizeof(f));
		m=0;
		for(int i=st;i<=n;i++)
			a[++m]=p[i]-p[st];
		sort(a+2,a+m+1,cmp2);
		for(int i=2;i<=m;i++)
		  f[1][i][1]=1;
		for(int num=1;num<=3;num++)
		{
			for(int i=num+1;i<=m;i++)
			for(int j=1;j<i;j++)
			{
				if(!f[num][i][j])continue;
				for(int k=i+1;k<=m;k++)
				{
					if((a[i]-a[j]).det(a[k]-a[j])<0)
					  f[num+1][k][i]+=f[num][i][j];
				}
			}
		}
		for(int i=1;i<=m;i++)
		  for(int j=1;j<i;j++)
		    if((a[i]-a[j]).det(a[1]-a[j])<0)
		      ans+=f[4][i][j];
	}
	printf("%I64d\n",ans);
	return 0;
}
```

---

## 作者：NightTide (赞：4)

## 前排警告 & 闲话
重要的事情说三遍：这个题目不用极角排序，不用极角排序，不用极角排序！

我们最近模考考了这一题，我钛蒻了不知道极角排序是什么，所以考试的时候想了这种写法，结果没想到卡一卡常数就过了，个人觉得代码和极角一点关系都没有，感觉这个思路比较一眼吧（~~反正我是一眼）~~。

纪念我在考场上 A 出的第一道黑题。
## 题目大意
给定平面上 $n$ 个点，选取五个点，使得这五个点能够构成一个五角星，求方案数。
## 解题思路
首先转化题意，五个点能够构成一个五角星，其充要条件是这五个点能够构成一个凸五边形。

这里有一个显然的结论（为什么显然？因为我也不会证）：**对于一个凸多边形，我们有且仅有一种方法，以它的一条对角线为分界线，将它分为一个上凸包和一个下凸包。**

为了方便，下文中我们将这一条对角线称为**划分线**。

如图，这里就把图中的五边形分割成了一个上凸包和一个下凸包。而且这也是唯一的分割方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/2u6pvmwr.png)

那么我们可以分成两半来计算方案，分别计算构成上凸包的方案数和构成下凸包的方案数，最后相乘就可以了。

至于方案数，可以用动态规划来计算。

考虑一个凸包的性质，它的边的斜率是有单调性的。具体来说，上凸包的边的斜率单调递减，下凸包的边的斜率单调递增。我们可以用这个性质来进行动态规划。

为了方便，我们只讲解上凸包的动态规划过程，下凸包是一样的，只需要把上凸包中斜率单调递增的条件改成单调递减就好了。

我们设 $dp_{s,i,j,k}$ 表示选取的第一个点是 $s$，最后一个点和倒数第二个点分别是 $i$ 和 $j$，总共选取了 $k$ 条边，也就是 $k + 1$ 个点，形成了一个上凸包的方案数。

讲一下每一维的意义。第一维,第三维和最后一维在统计答案的时候会用到。我们在最后统计答案的时候会枚举切分点 $i$ 和 $j$，那么以 $i,j$ 之间对角线为划分线的凸五边形的方案数就是第一个点为 $i$，最后一个点为 $j$，共 $k$ 条边的上凸包方案数乘以第一个点为 $i$，最后一个点为 $j$，共 $5 - k$ 条边的下凸包方案数，$k$ 从 $1$ 到 $4$ 枚举。第二维和第三维加起来可以表示选取的最后一条边，这样方便我们保证斜率的单调性。

然后就有式子：
$$dp_{s,i,j,k} = \sum_{gra(t,i) > gra(i,j)} dp_{s,t,i,k - 1}$$

其中 $gra(i,j)$ 表示 $i,j$ 两点之间的线段的斜率。

然而就这样写你甚至过不了样例。原因很显然，凸包的边的斜率的单调性不是随便什么顺序都有的。更严格一点的说法是：上凸包的边的斜率随 $x$ 坐标增加单调递减，下凸包的边的斜率随 $x$ 坐标增加单调递增。当然，边没有什么 $x$ 坐标一说，但是你可以感性理解一下，也就是上凸包中，越右边的边斜率越大，下凸包相反。同时，你个凸包都算了两次，以 $i$ 为起点，$j$ 为终点一次；以 $j$ 为起点 $i$ 为终点又一次。再有你每一条边也算了两次。还有一些奇奇怪怪的问题，这样的答案就会非常离谱了。

所以我们把点按照 $x$ 坐标排序，规定一条边的起点一定是 $x$ 坐标较小的，终点一定是 $x$ 坐标较大的。凸包的规定类似，即选取的点一定是 $x$ 坐标单调不降的。这样的答案就是对的。（为什么是对的？我还是不会证。）

~~感觉最后一部分为什么按照 $x$ 坐标排序没有讲清楚啊。留到以后更强了再来填坑把，包括证明也是。如果有大佬能够帮我证明一下就再好不过了。~~

不过，这样写答案确实对了，但是一看空间，$O(n^3)$，炸完了。观察到第一维是不需要的，递推过程中可以省略掉。

然而，这样省略掉之后，统计答案就不好办了，因为我们统计答案的时候需要的信息有凸包的起点，凸包的终点，以及构成凸包的边的数量。

于是我们再开一个数组，$f_{i,j,k}$ 表示以 $i$ 为起点，$j$ 为终点，共 $k$ 条边的凸包数量。这样做的原因是，虽然倒数第二个点的信息在递推过程中有用，但是统计答案的时候却没有用处，可以省去；而第一个点的信息在递推过程中可以省略，但是在统计答案的时候却必不可少，所以加上。

虽然是 $O(n^4)$，但是 $O($能过$)$。

## 完整代码
不管了，上代码，应该也不难看懂的说。（不会被 Hack 掉把，害怕）
```cpp
#include<bits/stdc++.h>
#define MAXN 301
using namespace std;
typedef long long ll;
struct coor{ int x, y; };
bool operator < (coor a, coor b){ return a.x < b.x; };
coor node[MAXN];
int n, m;
ll dp[MAXN][MAXN][5][2], f[MAXN][MAXN][5][2];
int main(){
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) scanf("%d%d",&node[i].x,&node[i].y);
    sort(node + 1, node + n + 1);
    for(int i = 1; i <= n; i++){
        memset(dp, 0, sizeof(dp));
        for(int j = i + 1; j <= n; j++) dp[i][j][1][0] = dp[i][j][1][1] = 1;
        for(int k = 2; k < 5; k++){
            for(int j = i; j <= n; j++){
                if(k == 2 && j != i) break;
                for(int s = j + 1; s <= n; s++){
                    if(dp[j][s][k - 1][0] == 0 && dp[j][s][k - 1][1] == 0) continue;
                    for(int t = s + 1; t <= n; t++){
                        ll k1 = (ll)(node[t].x - node[s].x) * (node[s].y - node[j].y), k2 = (ll)(node[s].x - node[j].x) * (node[t].y - node[s].y);// 计算斜率，为保证精度移项
                        if(k1 < k2) dp[s][t][k][0] += dp[j][s][k - 1][0];
                        else dp[s][t][k][1] += dp[j][s][k - 1][1];
                    }
                }
            }
        }
        for(int s = 1; s <= n; s++){
            for(int j = s + 1; j <= n; j++){
                for(int k = 1; k < 5; k++){
                    f[i][j][k][0] += dp[s][j][k][0];
                    f[i][j][k][1] += dp[s][j][k][1];
                }
            }
        }
    }
    ll ans = 0;
    for(int s = 1; s <= n; s++){
        for(int t = s + 1; t <= n; t++){
            for(int k = 1; k < 5; k++){
                ans += f[s][t][k][0] * f[s][t][5 - k][1];
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：λᴉʍ (赞：2)

五角星可以转化成5个点的凸包，就是5条极角序线段上升的线段。

设$f[i][j][k]$表示从$i$开始到$j$的一个线段路径共有$k+1$条边，那么每次按照极角序新加进来一个线段$x\rightarrow y$，转移是$f[x][y][0]=1,f[S][y][k]+=f[S][x][k-1]$

https://codeforces.com/contest/1146/submission/53116991

---

## 作者：Purslane (赞：0)

# Solution

首先，五角星这个条件实在是太鬼晦了，尝试优化一下条件。

> 结论：五角星对应一个凸包。
>
> 证明：任意一个凸四边形，对角线必然相交。而一个凸包选取任意大小 $\ge 3$ 的子点集，仍然构成一个凸包，因此任何一个凸五边形都能对应一个五角星。
>
> 给定一个五角星，如果其顶点构成的凸包并不包含所有点，则必然会出现两条应该有交点的对角线没有交点的情形，矛盾。

因此考虑对平面上凸五边形进行计数，或者更一般的，对平面上的凸 $n$ 变形进行计数。

一个必要条件是，考虑向量 $A_i \to A_{i+1}$（模意义下），我们可以通过选择适当的起点使得向量们的极角序递增。我们尝试证明其充分性。

我们可以将构造的凸包拆解成四个象限向量形成的凸壳，$A \to B \to C \to D \to A$，分别对应一二三四象限。我们想要说明 $A \to B$ 的凸壳和 $C \to D$ 的凸壳没有交。鉴于 $C$ 在 $A$ 和 $B$ 上方，这时候两个凸壳相交的一个必要条件是：线段 $AB$ 与线段 $CD$ 相交。

我们只需要说明：$AB$ 和 $CD$ 无交。但这几乎是显然的，因为有交点，$D \to A$ 就是第二象限凸壳了，矛盾！

因此设 $dp_{i,j,k}$ 表示，用了 $k$ 步从 $i$ 到 $j$。

新增线段 $u \to v$ 时，$\forall i$，$dp_{i,v,k} \leftarrow dp_{i,v,k} + dp_{i,u,k-1}$。不需要考虑各种奇奇怪怪的情况，因为我们已经证明了选择 $5$ 条收尾相接且封闭的、极角序递增的向量一定是合法的。

复杂度：$O(kn^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=300+10;
int n,x[MAXN],y[MAXN],dp[MAXN][MAXN][10];
struct VEC {int dx,dy,u,v;};
int gid(VEC vc) {
	if(vc.dx>=0&&vc.dy>=0) return 1;
	if(vc.dy>=0) return 2;
	if(vc.dx<=0) return 3;
	return 4;	
}
bool operator <(VEC A,VEC B) {
	if(gid(A)!=gid(B)) return gid(A)<gid(B);
	return A.dx*B.dy>=A.dy*B.dx;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>x[i]>>y[i],dp[i][i][0]=1;
	vector<VEC> vc;
	ffor(i,1,n) ffor(j,1,n) if(i!=j) vc.push_back({x[j]-x[i],y[j]-y[i],i,j});
	sort(vc.begin(),vc.end());
	for(auto pr:vc) {
		int u=pr.u,v=pr.v;
		ffor(i,1,n) ffor(j,1,5) dp[i][v][j]+=dp[i][u][j-1];	
	}
	int ans=0;
	ffor(i,1,n) ans+=dp[i][i][5];
	cout<<ans;
	return 0;
}
```

---

## 作者：Aiopr_2378 (赞：0)

solution of CF1146H Satanic Panic

## 解题思路

考虑如果要围成一个五角星，则五条边的斜率单调递增，考虑使用动态规划维护凸包。

令 $f_{i,j,k}$ 表示从节点 $i$ 开始（作为五角星第一条边的起点），经过 $k$ 条边到达节点 $j$ 的方案数。因为要围成五角星，故 $k\in [1,5]$。

因为规划的边要满足斜率递增规则，故需要先对 $n^2$ 条边按斜率进行排序，再按斜率顺序对每一条边 $(u,v)$ 进行如下转移：

$$
f_{i,v,j}\longleftarrow f_{i,u,j-1}
$$

关于斜率排序，可以直接用 `atan2(y,x)` 计算出斜率，但有精度误差，故推荐使用叉积运算，重定义排序函数。对两条边进行叉积运算，根据正负判断两条边斜率的相对大小即可。但要注意，要先对斜率正负分类处理，才能保证叉积排序的正确性。

时间复杂度 $O(kn^3)$，本题中 $k=5$ 可忽略为常数。

## 参考代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 305
typedef long long ll;
struct point{
    int x,y,id;
    point operator-(point k){return {x-k.x,y-k.y};}
}p[MAXN];
struct line{
    point a,b;
    int op;
}a[MAXN*MAXN];
int n,m;
ll f[MAXN][MAXN][7];
bool cmp(line x,line y){
    if(x.op!=y.op) return x.op<y.op;
    point tx=x.b-x.a;
    point ty=y.b-y.a;
    return 1ll*tx.x*ty.y-1ll*tx.y*ty.x>0;
}
bool getop(point x){
    return x.y>0||x.y==0&&x.x>=0;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        p[i].id=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            a[++m]={p[i],p[j]};
            a[m].op=getop(p[j]-p[i]);
        }
    }
    sort(a+1,a+1+m,cmp);
    for(int i=1;i<=m;i++){
        int v=a[i].a.id;
        int u=a[i].b.id;
        f[v][u][1]=1;
        for(int j=1;j<=n;j++){
            for(int k=2;k<=5;k++) f[j][u][k]+=f[j][v][k-1];
        }
    }
    ll ans=0;
    for(int i=1;i<=n;i++) ans+=f[i][i][5];
    cout<<ans<<endl;
    return 0;
}
```

---

