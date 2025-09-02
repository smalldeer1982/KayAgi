# Yet another 2D Walking

## 题目描述

Maksim walks on a Cartesian plane. Initially, he stands at the point $ (0, 0) $ and in one move he can go to any of four adjacent points (left, right, up, down). For example, if Maksim is currently at the point $ (0, 0) $ , he can go to any of the following points in one move:

- $ (1, 0) $ ;
- $ (0, 1) $ ;
- $ (-1, 0) $ ;
- $ (0, -1) $ .

There are also $ n $ distinct key points at this plane. The $ i $ -th point is $ p_i = (x_i, y_i) $ . It is guaranteed that $ 0 \le x_i $ and $ 0 \le y_i $ and there is no key point $ (0, 0) $ .

Let the first level points be such points that $ max(x_i, y_i) = 1 $ , the second level points be such points that $ max(x_i, y_i) = 2 $ and so on. Maksim wants to visit all the key points. But he shouldn't visit points of level $ i + 1 $ if he does not visit all the points of level $ i $ . He starts visiting the points from the minimum level of point from the given set.

The distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ where $ |v| $ is the absolute value of $ v $ .

Maksim wants to visit all the key points in such a way that the total distance he walks will be minimum possible. Your task is to find this distance.

If you are Python programmer, consider using PyPy instead of Python when you submit your code.

## 说明/提示

The picture corresponding to the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1066F/896df4e9ea79d5fd52a150516ea0bd817a9ff17d.png)

There is one of the possible answers of length $ 15 $ .

The picture corresponding to the second example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1066F/df4d50be023876f6bcdf0e6166cef5c64a3a8a11.png)

There is one of the possible answers of length $ 9 $ .

## 样例 #1

### 输入

```
8
2 2
1 4
2 3
3 1
3 4
1 1
4 3
1 2
```

### 输出

```
15
```

## 样例 #2

### 输入

```
5
2 1
1 0
2 0
3 2
0 3
```

### 输出

```
9
```

# 题解

## 作者：p_b_p_b (赞：5)

抢到第一篇题解好激动~~~

~~这题我们可以先看看标签：DP。嗯……~~

依照题意，每一层都必须走完后才能到下一层，而且距离是很良心的曼哈顿距离。

于是，有一个很明显的贪心策略：每层都由左上方走到右下方（反过来同理），期间经过该层所有点，然后走到下一层的左上方/右下方。

那么，可以：

1、用$dp[N][2]$记录走完第i层时，在左上/右下时最小距离

2、用$p[N][2]$记录每一层的左上角点、右下角点的坐标

然后，用上一层的数据更新这一层。转移方程：~~太简单懒得写~~

~~其实还可以滚动数组，但这题不卡空间，我也很懒，就没写~~

代码：（很多奇怪的单个变量名）

```cpp
#include<bits/stdc++.h>
#define sz 200020
#define mod 998244353ll
using namespace std;
typedef long long ll;
struct FastIO
{
    inline FastIO& operator>>(int& x)
    {
        x=0;char f=0,ch=getchar();
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') x=x*10+ch-48,ch=getchar();
        return x=(f?-x:x),*this;
    }
    inline FastIO& operator>>(ll& x)
    {
        x=0;char f=0,ch=getchar();
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') x=x*10+ch-48,ch=getchar();
        return x=(f?-x:x),*this;
    }
    inline FastIO& operator>>(double& x)
    {
        x=0;char f=0,ch=getchar();
        double d=0.1;
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') x=x*10+ch-48,ch=getchar();
        if(ch=='.')
        {
            ch=getchar();
            while(ch<='9'&&ch>='0') x+=d*(ch^48),d*=0.1,ch=getchar();
        }
        return x=(f?-x:x),*this;
    }
}read;
void file()
{
    #ifndef ONLINE_JUDGE
    freopen("a.txt","r",stdin);
    #endif
}
unsigned int log2(int x){unsigned int ret;__asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));return ret;}
inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int n;
struct hh{int x,y;}a[sz];
inline int id(hh x){return max(x.x,x.y);}
inline bool cmp(const hh &x,const hh &y){return id(x)<id(y);}
ll dp[sz][2];
hh p[sz][2];
inline bool cmpx(const hh &x,const hh &y){return x.x==y.x?x.y>y.y:x.x<y.x;}//left
inline bool cmpy(const hh &x,const hh &y){return x.y==y.y?x.x>y.x:x.y<y.y;}//right
inline ll dis(const hh &x,const hh &y){return abs(x.x-y.x)+abs(x.y-y.y);}
int main()
{
	file();
	int i,j,k,x,y,z;
	read>>n;
	for (i=1;i<=n;i++) read>>a[i].x>>a[i].y;
	sort(a+1,a+n+1,cmp);
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=dp[0][1]=0;
	for (i=j=z=1;i<=n;i=j+1,++z,++j)
	{
		while (id(a[j+1])==id(a[j])) ++j;
		p[z][0]=p[z][1]=a[i];
		for (k=i+1;k<=j;k++)
		{
			if (cmpx(a[k],p[z][0])) p[z][0]=a[k];
			if (cmpy(a[k],p[z][1])) p[z][1]=a[k];
		}
		for (x=0;x<2;x++)
			for (y=0;y<2;y++)
				dp[z][x]=min(dp[z][x],dp[z-1][y]+dis(p[z-1][y],p[z][!x])+dis(p[z][!x],p[z][x]));
	}
	cout<<min(dp[z-1][0],dp[z-1][1]);
}
```

---

## 作者：ncwzdlsd (赞：3)

考虑在每一级别如何走最优，形成的路线一定是从最左上点到最右下点或从最右下点到最左上点，否则路径会有重合部分，一定不优。

设计状态 $f(i,0/1)$ 表示在第 $i$ 个级别，当前在最左上 / 最右下点。

用 $d(i,j)$ 表示两点间的曼哈顿距离，$l_i/r_i$ 表示当前级别的最左 / 右点，状态转移：

$$
\begin{aligned}
f(i,0)&=\min(f(i-1,0)+d(l_{i-1},r_i),f(i-1,1)+d(r_{i-1},r_i))+d(l_i,r_i)\\
f(i,1)&=\min(f(i-1,0)+d(l_{i-1},l_i),f(i-1,1)+d(r_{i-1},l_i))+d(l_i,r_i)
\end{aligned}
$$

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=2e5+5;
int l[maxn],r[maxn],f[maxn][2];
struct node{int x,y,m;}p[maxn];

bool cmp(node a,node b)
{
    if(a.m!=b.m) return a.m<b.m;
    if(a.x!=b.x) return a.x<b.x;
    return a.y>b.y;
}

int dis(int i,int j){return abs(p[i].x-p[j].x)+abs(p[i].y-p[j].y);}

signed main()
{
    int n;cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y,p[i].m=max(p[i].x,p[i].y);
    sort(p+1,p+n+1,cmp);
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(p[i].m!=p[i-1].m) r[++cnt]=i;
        if(p[i].m!=p[i+1].m) l[cnt]=i;
    }
    for(int i=1;i<=cnt;i++)
        f[i][0]=min(f[i-1][0]+dis(l[i-1],r[i]),f[i-1][1]+dis(r[i-1],r[i]))+dis(l[i],r[i]),
        f[i][1]=min(f[i-1][0]+dis(l[i-1],l[i]),f[i-1][1]+dis(r[i-1],l[i]))+dis(l[i],r[i]);
    cout<<min(f[cnt][0],f[cnt][1]);
    return 0;
}
```

---

## 作者：littlewyy (赞：3)

#### [Codeforces 1066F](<http://codeforces.com/problemset/problem/1066/F>)

#### 题意

平面上有 n 个点，且坐标均为非负整数。规定点 (i, j) 的等级为 max(i, j) 且保证不存在等级为 0 的点。现在从点 (0, 0) 出发，每次可以水平或竖直移动 1 个单位长度。在遍历完等级低于 i 的点之前，不能到达等级为 i 或更高的点。问遍历所有点的最短路长度。$1 \leq n \leq 2 \times 10^5 , 0 \leq x,y \leq 10^9$

#### 题解

画图可知，等级为$i$的点一定组成1个倒L字。

对于**同1等级**，最短路为沿着L字从1个端点走向另1个端点。（端点为L字上最左上点和最右下点）

对于从等级$i$到等级$i+1$的**跨越**，猜测最优解应从$i$的端点到$i + 1$的端点。

证明：若在$i+1$的起始点$x$并非L字的端点，定会导致完成$i + 1$途中路径重复，重复的路径恰好就是从$i$的端点到$x$节省下的跨级距离。后者相对前者的收益等于花费，故两者等价，只需考虑到达端点的情况即可。

因此，策略应为：对于第$i$等级L字的两端点$lef,rig$，存在$lef \rightarrow rig$和$rig \rightarrow lef$两种方案；第$i$等级到第$i + 1$等级，存在$lef \rightarrow lef'$ 、 $rig \rightarrow lef'$、$lef \rightarrow rig'$和$rig \rightarrow rig'$四种方案。求解逐一处理各等级的最小花费。

经典的**动态规划**问题。

设$f[i][0/1]$表示处理完第$i$等级，且停留在$lef/rig$的最短路。枚举第$i-1$等级的结束点$0/1$即可转移。

时间复杂度：（离散化）$O(NlogN)$。

代码见此：
```
#include<iostream>
#include<cstdio>
#include<deque>
#include<algorithm>
#include<cstring>
#include<cstdlib>
using namespace std;
long long typedef LL;
const int MAXN = 2E5 + 5;
int cur = -1,n,Ori[MAXN],Head[MAXN];
int Lef[MAXN],Rig[MAXN];
LL f[MAXN][2];
struct wyy
{
	int x,y,c;
}A[MAXN];
struct gr
{
	int to,next;
}Group[MAXN];
void Add(int g,int to)
{
	Group[++ cur].to = to;
	Group[cur].next = Head[g];
	Head[g] = cur;
}
int read()
{
	char ch = getchar();int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		w = w * 10 + (int)(ch - '0');
		ch = getchar();
	}
	return w;
}
void Read()
{
	n = read();
	for(int i = 1 ; i <= n ; i ++)
	{
		A[i].x = read() , A[i].y = read();
		A[i].c = max(A[i].x,A[i].y);
		Ori[i] = A[i].c;
	}
	sort(Ori + 1 , Ori + 1 + n);
	
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= n ; i ++)
	{
		int c = A[i].c;
		Add(lower_bound(Ori + 1 , Ori + 1 + n , c) - Ori , i);
	}
	
	for(int i = 1 ; i <= n ; i ++)	Lef[i] = Rig[i] = -1;
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int h = Head[i] ; h != -1 ; h = Group[h].next)
		{
			int to = Group[h].to;
			if(Lef[i] == -1)	Lef[i] = to;
			else	if(A[to].x < A[Lef[i]].x || (A[to].x == A[Lef[i]].x && A[to].y > A[Lef[i]].y))	Lef[i] = to;
			if(Rig[i] == -1)	Rig[i] = to;
			else	if(A[to].x > A[Rig[i]].x || (A[to].x == A[Rig[i]].x && A[to].y < A[Rig[i]].y))	Rig[i] = to;
		}
	}
}
int getDis(int a,int b)
{
	int x = A[a].x , y = A[a].y;
	int xx = A[b].x , yy = A[b].y;
	return abs(x - xx) + abs(y - yy);
}
void Calc()
{
	int last = 0;
	for(int i = 1 ; i <= n ; i ++)	
	{
		if(Head[i] == -1)	continue;
		LL dis = getDis(Lef[i],Rig[i]);
		if(last == 0)	
		{
			f[i][0] = dis + A[Rig[i]].x + A[Rig[i]].y;
			f[i][1] = dis + A[Lef[i]].x + A[Lef[i]].y;
		}
		else	
		{
			f[i][0] = dis + min(f[last][0] + getDis(Lef[last],Rig[i]),f[last][1] + getDis(Rig[last],Rig[i]));
			f[i][1] = dis + min(f[last][0] + getDis(Lef[last],Lef[i]),f[last][1] + getDis(Rig[last],Lef[i]));
		}		
		last = i;
	}
	printf("%I64d\n",min(f[last][0],f[last][1]));
}
int main()
{
	Read();
	Calc();
	return 0;
}

```
#### 回顾与思考

通过拆分，复杂问题简单化。

---

## 作者：__LZH__ (赞：0)

# Yet another 2D Walking

## 题意

小M在平面直角坐标系上的 $(0, 0)$ 处，他每次可以向上，下，左，右走一格。有 $n$ 个第 $i$ 个关键点的坐标为 $(x_i, y_i)$，第 $i$ 个关键点须走多远。的级别为 $\max(x_i,y_i)$，小M想经过所有的关键点，只有为 $p$ 级别的点全部走完才能且只能去走 $p+1$ 级别的点。求出走遍全部关键点须走多远。

## 思路

来看看这张图：

![](https://vj.csgrandeur.cn/144d59fcd595776fe3fb6653bb3fd5d6?v=1711626697)

可以发现每一级别对应的层上的关键点都是从上一层的右下或左上的关键点走过来的，比如级别为 $3$ 的那一层就是级别为  $2$ 的右下角转移过来的。因此我们又能发现，每一层转移到下一层都是这一层的右下或左上去下一层的右下或左上。

因此：

我们可以先这么排序：

```cpp
bool cmp(node a, node b){
  if(max(a.x, a.y) != max(b.x, b.y)){
    return max(a.x, a.y) < max(b.x, b.y);
  }
  return a.y < b.y || (a.y == b.y && a.x > b.x);
}
sort(a + 1, a + 1 + n);
```
就能保证所有的点都是按级别且按左上到右下排的。

DP 状态：考虑 $dp_{i,0/1}$ 表示到第 $i$ 个级别并且下一次分别从左上、右下转移。

转移：见代码。

code：

```cpp
#include<bits/stdc++.h>

using namespace std;

struct node{
  int x, y;
}a[200010];

long long n, dp[2][200010];//记得开 long long
vector<int> id;
vector<node> lr;

bool cmp(node a, node b){
  if(max(a.x, a.y) != max(b.x, b.y)){
    return max(a.x, a.y) < max(b.x, b.y);
  }
  return a.y < b.y || (a.y == b.y && a.x > b.x);
}

int d(int i, int j){//i 点到 j 点的曼哈顿距离
  return abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y);
}

int main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n;
  set<int> s;
  for(int i = 1; i <= n; i++){
    cin >> a[i].x >> a[i].y;
    s.insert(max(a[i].x, a[i].y));
  }
  for(auto i = s.begin(); i != s.end(); i++){
    id.push_back(*i);
  }
  sort(a + 1, a + 1 + n, cmp);
  int k = 0, l = 0, r = 0;
  lr.push_back({0, 0});
  for(int i = 1; i <= n; i++){
    if(id[k] != max(a[i].x, a[i].y)){
      lr.push_back({l, r}), k++, l = 0, r = 0;
    }
    if(!l){
      l = i;
    }
    r = i;
  }
  lr.push_back({l, r});
  //lr 存第 i 个级别排序后的左右端点
  for(int i = 1; i <= lr.size(); i++){
    dp[0][i] = dp[1][i] = 1e18;
  }
  long long ans = 0;
  for(int i = 1; i < lr.size(); i++){
    int i1 = lr[i - 1].x, j1 = lr[i - 1].y, i2 = lr[i].x, j2 = lr[i].y;
    //得出上一个与这一个的级别的左右端点，i 是左端点，j 是右端点
    ans += abs(a[i2].x - a[j2].x) + abs(a[i2].y - a[j2].y); //遍历一个级别的花费
    dp[0][i] = min(dp[0][i - 1] + d(i1, j2), dp[1][i - 1] + d(j1, j2));
    dp[1][i] = min(dp[0][i - 1] + d(i1, i2), dp[1][i - 1] + d(j1, i2));
    //从上一级别转移到这一级别所需的最小花费
  }
  cout << min(dp[0][lr.size() - 1], dp[1][lr.size() - 1]) + ans;
  return 0;
}
```

---

## 作者：Lee666666 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1066F)

建议多研究一下**样例解释**中的平面直角坐标系，很有帮助。

题意中要求在经过级别为 $k$ 的关键点之前必须要通过所有级别小于 $k$ 的关键点，所以一条合法的经过所有关键点的路径必然是**一级一级**来的。

我们首先研究在同一级中**第一个**经过的点和最后一个经过的点。要想让路径长度最小，这两个点必须在所有点的**两侧**，因为同一级的所有点在连接起来会形成一条**折线**，想要让这一级的路径长度最短，只能让这两个点分居于两侧。

我们定义同级中横纵坐标之差最小的点为**左侧点**，横纵坐标之差最大的点为**右侧点**，那么在一层到另一层的过程中，有可能是从左侧点到右侧点，也有可能是从右侧点到左侧点；有可能是从左侧点到左侧点，还有可能是从右侧点到右侧点，所以我们采用**动态规划**解决这个问题。

状态：

设 $dp_{i,0/1}$ 表示第 1 级到第 $i$ 级，当前位于第 $i$ 级的左侧点（0）或右侧点（1）的路径最小值。

决策：

左侧点 $\Rightarrow$ 左侧点

左侧点 $\Rightarrow$ 右侧点

右侧点 $\Rightarrow$ 左侧点

右侧点 $\Rightarrow$ 右侧点

状态转移方程：

设 $lv_{i,0/1}$ 表示第 $i$ 级中的左侧点（0）和右侧点（1），$\operatorname{DIS}(A,B)$ 表示点 $A,B$ 之间的**曼哈顿距离**。

$$
dp_{i,0}=\min(dp_{i-1,0}+\operatorname{DIS}(lv_{i-1,0}, lv_{i,1}),\ dp_{i-1,1}+\operatorname{DIS}(lv_{i-1,1},lv_{i-1,1}))
$$

$$
dp_{i,1}=\min(dp_{i-1,0}+\operatorname{DIS}(lv_{i-1,0}, lv_{i,0}),\ dp_{i-1,1}+\operatorname{DIS}(lv_{i-1,1},lv_{i-1,0}))
$$

上代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int maxn = 200015;

inline int sim_read() {
    int s = 0;
    char ch = getchar();
    while (ch < 48 || ch > 57) {
        ch = getchar();
    }
    while (ch > 47 && ch < 58) {
        s = (s << 3) + (s << 1) + ch - 48;
        ch = getchar();
    }
    return s;
}

struct Point {
    int x, y;
    void operator = (const Point &rhs) {
        x = rhs.x;
        y = rhs.y;
        return;
    }
    bool operator < (const Point &rhs) const { // 将等级作为第一关键字，x - y 作为第二关键字排序
        if (max(x, y) != max(rhs.x, rhs.y)) {
            return max(x, y) < max(rhs.x, rhs.y);
        }
        return x - y < rhs.x - rhs.y;
    }
} point[maxn], lv[maxn][2];

inline int ABS(int n) {
    return n < 0 ? -n : n;
}

int dis(Point p1, Point p2) {
    return ABS(p1.x - p2.x) + ABS(p1.y - p2.y);
}

int n;
LL dp[maxn][2];

int main() {
    n = sim_read();
    for (register int i = 1; i <= n; i++) {
        point[i].x = sim_read();
        point[i].y = sim_read();
    }
    sort(point + 1, point + n + 1);
    lv[0][0].x = lv[0][0].y = lv[0][1].x = lv[0][1].y = 0;
    int len = 1;
    lv[len][0] = point[1];
    for (register int i = 2; i <= n; i++) { // 计算出 lv 数组的值
        if (max(point[i].x, point[i].y) != max(point[i - 1].x, point[i - 1].y)) {
            lv[len][1] = point[i - 1];
            lv[++len][0] = point[i];
        }
    }
    lv[len][1] = point[n];
    dp[0][0] = dp[0][1] = 0;
    for (register int i = 1; i <= len; i++) { // DP
        dp[i][0] = min(dp[i - 1][0] + dis(lv[i - 1][0], lv[i][1]), dp[i - 1][1] + dis(lv[i - 1][1], lv[i][1])) + dis(lv[i][0], lv[i][1]);
        dp[i][1] = min(dp[i - 1][0] + dis(lv[i - 1][0], lv[i][0]), dp[i - 1][1] + dis(lv[i - 1][1], lv[i][0])) + dis(lv[i][0], lv[i][1]);
    }
    printf("%lld", min(dp[len][0], dp[len][1]));
    return 0;
}

```


时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$。



---

