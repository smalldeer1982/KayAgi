# Deadly Laser

## 题目描述

# Deadly Laser


The robot is placed in the top left corner of a grid, consisting of $ n $ rows and $ m $ columns, in a cell $ (1, 1) $ .

In one step, it can move into a cell, adjacent by a side to the current one:

- $ (x, y) \rightarrow (x, y + 1) $ ;
- $ (x, y) \rightarrow (x + 1, y) $ ;
- $ (x, y) \rightarrow (x, y - 1) $ ;
- $ (x, y) \rightarrow (x - 1, y) $ .

The robot can't move outside the grid.

The cell $ (s_x, s_y) $ contains a deadly laser. If the robot comes into some cell that has distance less than or equal to $ d $ to the laser, it gets evaporated. The distance between two cells $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ .

Print the smallest number of steps that the robot can take to reach the cell $ (n, m) $ without getting evaporated or moving outside the grid. If it's not possible to reach the cell $ (n, m) $ , print -1.

The laser is neither in the starting cell, nor in the ending cell. The starting cell always has distance greater than $ d $ to the laser.

有一个长$n$宽$m$的网格，一个机器人被放在此网格的左上角$(1,1)$。
每一步，机器人可以移动到与其所在格子相邻的四个格子：
- $(x,y) \rightarrow (x,y+1)$;
- $(x,y) \rightarrow (x+1,y)$;
- $(x,y) \rightarrow (x,y-1)$;
- $(x,y) \rightarrow (x-1,y)$。

机器人不能移出网格。\
在$(s_x,s_y)$处，放置着致命的激光。所有与激光所在格子的距离小于等于$d$的格子都不可通行。（$(x_1,y_1)$到$(x_2,y_2)$的距离为: $|x_1-x_2|+|y_1-y_2|$）\
输出机器人从$(1,1)$移至$(n,m)$的最小步数。如果机器人不能到达$(n,m)$，输出`-1`。

## 样例 #1

### 输入

```
3
2 3 1 3 0
2 3 1 3 1
5 5 3 4 1```

### 输出

```
3
-1
8```

# 题解

## 作者：wimg6_ (赞：2)

## CF1721B 题解

### 题意简述

$t$ 组数据。

你需要从 $(1,1)$ 走到 $(n,m)$，途中与 $(sx,sy)$ 相离 $d$ 个单位长度的格子不能走。如果能走到 $(n,m)$，输出最少步数；如果不能走到 $(n,m)$，输出 $-1$。

注：矩阵上相离单位的计算公式为： $|x_1-x_2|+|y_1-y_2|$，其中两个点分别为 $(x_1,y_1)$ 和 $(x_2,y_2)$。

### 解题过程

乍一看是一个宽度优先搜索问题，跑一边整个图即可。然而分析一下时间复杂度：$O(t\times n\times m)$，会炸。

考虑挖掘题目特殊性质，发现只有五种情况会输出 $-1$，否则输出图上最短路，即 $n+m-2$。

五种情况分别为：

1. 不能走的区域覆盖 $(n,m)$。

2. 不能走的区域覆盖 $(1,1)$。

3. 不能走的区域覆盖完整的，且在第 $n$ 行前的某一行。

4. 不能走的区域覆盖完整的，且在第 $m$ 列前的某一列。

5. 不能走的区域覆盖完整地图。

按照以上步骤判断即可。

### 完整代码

```
#include<bits/stdc++.h>
using namespace std;
int t;
int cal(int x1,int y1,int x2,int y2)
{
	return abs(x1-x2)+abs(y1-y2);
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int n,m,sx,sy,d;
		scanf("%d%d%d%d%d",&n,&m,&sx,&sy,&d);
		if
		(
			cal(sx,sy,n,m)<=d ||
			(sx-d<=1 && sx+d>=n) ||
			(sy-d<=1 && sy+d>=m) ||
			(sx-d<=1 && sy-d<=1) ||
			(sx+d>=n && sy+d>=m)
		)
			printf("-1\n");
		else printf("%d\n",n+m-2);
	}
	return 0;
}
```


---

## 作者：xiaomuyun (赞：2)

- [洛谷传送门](https://www.luogu.com.cn/problem/CF1721B)
- [CodeForces 传送门](https://codeforces.com/contest/1721/problem/B)

## 思路分析

我们可以发现，如果题目有解，那么要么是从左上角走到右上角，再从右上角走到右下角，要么是从左上角走到左下角，再从左下角走到右下角。或者两种走法都成立。所以，只要 _Deadly Laser_ 不会使两条路都走不通，那么就有解，否则无解。如果有解，那么答案就是 $n+m-2$。

## 代码实现

$s_x-1$ 表示的是 _Deadly Laser_ 到第一行的距离，$s_y-1$ 表示的是 _Deadly Laser_ 到第一列的距离，$n-s_x$ 表示的是 _Deadly Laser_ 到最后一行的距离，$m-s_y$ 表示的是 _Deadly Laser_ 到最后一列的距离。

```cpp
#include<cstdio>
using namespace std;
int t,n,m,sx,sy,d;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d%d",&n,&m,&sx,&sy,&d);
		if((sx-1<=d||m-sy<=d)&&(sy-1<=d||n-sx<=d)) printf("-1\n");//判断无解
		else printf("%d\n",n+m-2);
	}
	return 0;
}
```

---

## 作者：Dry_ice (赞：2)

题链：[cf](https://codeforces.ml/contest/1721/problem/B) [luogu](https://www.luogu.com.cn/problem/CF1721B)

[cnblogs浏览](https://www.cnblogs.com/dry-ice/p/cf1712b.html)

> 分类讨论？

## Description
给一张 $n\times m$ 的地图，有一个点 $\left(sx,sy\right)$ 有辐射，辐射半径为 $d$，问能否从 $\left(1,1\right)$ 走到 $\left(n,m\right)$，如果能走最少几步。

## Analysis
我们把辐射点记作点 $A$。

倘若 $A$ 点能够阻断从左上角到右下角的路径，共有 $4$ 种可能情况：

1. 左上角阻断，即从 $A$ 点可以辐射到上边界和左边界；
2. 右下角阻断，即从 $A$ 点可以辐射到下边界和右边界；
3. 横断，即从 $A$ 点可以辐射到左边界和右边界；
4. 纵断，即从 $A$ 点可以辐射到上边界和左边界。

这四种情况都无合法路径，即输出 ```-1```。

如果有合法路径，因为只有 $1$ 个辐射点，向左或向上走都是浪费的。因此最小步骤一定是向右向下走，易得最小步数为 $n + m - 2$。

## Code
```cpp
#include <stdio.h>
int n, m, sx, sy, d;
int main(void) {
    int t; for (scanf("%d", &t); t--; ) {
        scanf("%d %d %d %d %d", &n, &m, &sx, &sy, &d);
        if (sx - d <= 1 && sy - d <= 1 ||
			sx + d >= n && sy + d >= m ||
			sx - d <= 1 && sx + d >= n ||
			sy - d <= 1 && sy + d >= m) puts("-1"); //四种不合法情况
        else printf("%d\n", n + m - 2); //直接向右向下走
    }
    return 0;
}
```

## The end. Thanks.

~~（小手点点~~

---

## 作者：flying_man (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1721B)

题意：有一个 $N \times M$ 的矩阵，一个机器人一开始在点 $(1,1)$，可以上下左右移动，它要前往终点 $(N,M)$。但是有一个死亡激光器在点 $(s_x,s_y)$ ，只要机器人所在点利死亡激光器的距离 $ \le d$ ，那么机器人将停止运作。请你求它到终点的最短移动次数。如果无法到达，输出 $-1$。

距离的定义：对于两点 $(x_1,y_1)$ 和 $(x_2,y_2)$，距离 $d$ 为 $ | x_1 - x_2 | + | y_1 - y_2 | $。

------------
**题解部分：**

**首先，我们可以想到，如果路径存在，最短移动次数一定为 $N+M-2$ ！**

为什么？~~只要是地球人都能想到~~，机器人不可能向左或向上走，否则这步就算浪费了。

所以最短移动次数为起点和终点的距离，也就是 $N+M-2$。

接下来我们要判无解的情况：

**1. 死亡激光器把起点堵死了，即 $s_x - d \leq 1$ 且 $s_y - d \leq 1$。**

**2. 死亡激光器把终点堵死了，即 $s_x + d \geq n$ 且 $s_y + d \geq m$。**

**3. 死亡激光器把纵向路堵死了，即 $s_x - d \leq 1$ 且 $s_x + d \geq n$。**

**4. 死亡激光器把横向路堵死了，即 $s_y - d \leq 1$ 且 $s_y + d \geq m$。**

判完无解后，代码就出来啦！

------------

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,sx,sy,d;
void in(int &s){
	char c;s = 0;
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9')
		s=s*10+c-'0',c = getchar();
}
int main(){
	in(t);
	while(t--){
		in(n);in(m);in(sx);in(sy);in(d);
		if(sx-d <= 1 && sy-d <= 1) printf("-1\n");
		else if(sx+d >= n && sy+d >= m) printf("-1\n");
		else if(sx-d <= 1 && sx+d >= n) printf("-1\n");
		else if(sy-d <= 1 && sy+d >= m) printf("-1\n");
		else printf("%d\n",n+m-2);
	}
	return 0;
}
```



---

## 作者：WilliamFranklin (赞：1)

### 主要思路

首先，看一下数据范围：$1 \le t \le 10^4$，$2 \le n, m \le 1000$。

很容易得出时间复杂度是 $O\left(tnm\right)$ 时会 TLE 的。

所以只能思考 $O\left(t\right)$ 算法，也就是每一组数据都是 $O\left(1\right)$ 求出。

这道题非常良心，因为它只有一个地方有致命激光，并且起点为 $\left(1, 1\right)$，终点为 $\left(n, m\right)$。

我们的第一反应就是如果这个激光，横着切或竖着切，把整一个网格图分成了两半，那么一定输出 $-1$。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7v26ejxl.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/ox8j65yq.png)
（注：黄色部分为激光）

然后又发现，只要再看一看这激光把起点或终点围住了吗，如果围住了，则输出 $-1$，否则输出 $n - 1 + m - 1$。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ixb2bszw.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/dtro2sbn.png)
（注：黄色部分为激光）

好啦，讲解完毕，贴代码！

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, m, x, y, d;
		cin >> n >> m >> x >> y >> d;
		if (abs(n - x) + abs(m - y) <= d) {
			cout << -1 << endl;
		} else {
			if (x - d <= 1 && x + d >= n) {
				cout << -1 << endl;
			} else if (y - d <= 1 && y + d >= m) {
				cout << -1 << endl;
			} else {
				if (x - d <= 1 && y - d <= 1) {
					cout << -1 << endl;
				} else if (x + d >= n && y + d >= m) {
					cout << -1 << endl;
				} else {
					cout << n - 1 + m - 1 << endl;
				}
			}
		}
	}
}
```


---

## 作者：_Give_up_ (赞：0)

## 题目大意
有一个机器人在一个方阵的左上角 $(1,1)$，要走到右下角 $(n,m)$。每个方阵都会有一个障碍，这个障碍会往外射出激光，激光的长度为 $d$，求不碰到激光的情况要走到右下角，最少走多少步。

## 题目思路
机器人只有四种情况走不到右下角：

1、激光射到了初始位置 $(1,1)$。

2、激光射到了右下角 $(n,m)$。

3、激光从最左边射到了最右边。

4、激光从最上边射到了最下边。

所以只要判断这四种情况就行了，如果这四种情况都不属于，就说明能走到右下角 $(n,m)$，输出 $n + m - 2$。

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int read()
{
    int x = 0,f = 1;
    char c = getchar();
    while(c<'0' || c>'9')
    {
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0' && c<='9')
    {
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
    return x*f;
}

int main()
{
    int t=read();
    while(t--)
    {
        int n=read(),m=read(),x=read(),y=read(),d=read();
        if ((x+d>=n && x-d<=1) || (y+d>=m && y-d<=1) || (x-d<=1&&y-d<=1) || (y+d>=m&&x+d>=n)) cout<<-1<<endl;
        else cout << n+m-2 << endl;
    }
    return 0;
}
```


---

## 作者：xzy090626 (赞：0)

# CF1721B 题解
## 题意
有一个 $n\times m$ 的网格，机器人一开始在 $(1,1)$ 的地方，要到 $(n,m)$ 去。但是在 $(s_x,s_y)$ 的地方有一个激光，激光攻击的范围是与激光距离 $\le d$ 的地方。**这里的距离不是欧几里得距离**：对于 $(x_1,y_1)$ 与 $(x_2,y_2)$，它们的距离是 $|x_1-x_2|+|y_1-y_2|$。

请问是否机器人是否可以成功。如果可以，输出最小的行走步数；否则，输出 $-1$。
## 分析
我们分析激光的影响范围，打个表可以发现是这样的：
```
0 0 0 0 0
0 0 1 0 0
0 1 1 1 0
1 1 1 1 1
0 1 1 1 0
0 0 1 0 0
0 0 0 0 0
```
其中，$1$ 代表激光可以影响这里，$0$ 代表这里安全。

容易发现，激光能不能使得机器人无法通过就在于激光最大的影响距离。

比如，如果激光形成了横向或者纵向的拦截，那么不可行；如果激光将出发点或者目标点围住了，那也不可行。否则就可行。

那么为什么这是正确的呢？反证法，如果最长的距离可行，那就一定非法；反之，如果最长的距离都无法阻止，那么短一些的肯定也不行。

那么当机器人可以成功时最短距离是什么呢？通过上面的观察发现，由于影响范围一定是辐射状而不会绕弯，所以就是 $(n+m-2)$。

---
## 实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int n,m,sx,sy,d;
	cin>>n>>m>>sx>>sy>>d;
	bool a = sx-d<=1,b = sx+d>=n,c = sy-d<=1,e= sy+d>=m;
	if(a&c || b&e || a&b || c&e) cout<<"-1\n";
	else cout<<n+m-2<<'\n';
}
signed main(){
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---
## 结语
- 赛时可以通过打表等方式观察规律和特殊性质以获得灵感；
- 本题样例十分迷惑人，非常弱；而且这题手玩数据也很困难，所以建议大家一定要多加思考，保证代码逻辑性正确才行。
- 考虑要全面，比如我这种傻逼，赛时只判了横向纵向拦截而没有判断别的。

完结撒花，另祝大家 CSP 2022 rp++！


---

## 作者：XiaoQuQu (赞：0)

更好的阅读体验与 CF1721 A-D 题解：[My Blog](blog.zshfoj.com)。

开始写了个 BFS，发现 TLE on #3，回去看数据范围发现不对劲，然后考虑分类讨论。因为是横竖走，要是终点可以走的话答案就是 $n+m-2$，如果终点被挡住了那么就是 $-1$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m, sx, sy, d;

void work()
{
    cin >> n >> m >> sx >> sy >> d;
    if ((sx + d >= n && sx - d <= 1) || (sy - d <= 1 && sy + d >= m))
        cout << "-1" << endl;
    else if ((sx + d >= n && sy + d >= m) || (sy - d <= 1 && sx - d <= 1))
        cout << "-1" << endl;
    else if ((abs(n - sx) * abs(n - sx) + abs(m - sy) * abs(m - sy)) <= d)
        cout << "-1" << endl;
    else if ((abs(1 - sx) * abs(1 - sx) + abs(1 - sy) * abs(1 - sy)) <= d)
        cout << "-1" << endl;
    else
        cout << n + m - 2 << endl;
}

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        work();
    }
    return 0;
}
```


---

## 作者：Error_Eric (赞：0)

### 题意

给定一个 $n\times m$ 的矩形，其中离点 $(s_x,s_y)$ 的[曼哈顿距离](https://oi-wiki.org//geometry/distance/#%E6%9B%BC%E5%93%88%E9%A1%BF%E8%B7%9D%E7%A6%BB)小于等于 $d$ 的点是危险的。

一个机器人每次可以向上下左右之一的方向移动 $1$ 格。从 $(1,1)$ 到 $(n,m)$ 的，不经过危险点的，全程在矩形内的合法路径最短长度。

有 $t$ 组数据。

### 解法

不考虑危险点限制，存在这么两条路径。

$(1,1)\rightarrow(n,1)\rightarrow(n,m)$

$(1,1)\rightarrow(1,m)\rightarrow(n,m)$

这两条路径如果有一条是通的，那么显然答案是 $n+m-2$ 。

如果这两条都不通，那么我们任取路径 $1$ 上的一个危险点 $p_1$ ,路径 $2$ 上的一个危险点 $p_2$，显然存在一条从 $p_1$ 至 $p_2$ 的路径上都是危险点。

这条危险路径已经将矩形分成两块，那么绝对不存在合法路径了。

### Code

代码太简单，放个链接罢。

[Link](https://codeforces.ml/contest/1721/submission/169923208)

---

## 作者：Simclover (赞：0)

这道题很简单，我们需要判断 $(n,m)$ 与 $(s_x,s_y)$ 的距离是否小于或者等于 $d$，如果是，就是无解，输出 `-1`。

如果不是，判断 $(s_x,s_y)$ 的扫描范围是否横跨上下或者是否横跨左右，如果是，就无法从 $(1,1)$ 走到 $(n,m)$，无解，输出 `-1`。

如果还不是的话，就说明有解。我们只需要从 $(1,1)$ 走到 $(1,m)$，再从 $(1,m)$ 走到 $(n,m)$。或者从 $(1,1)$ 走到 $(n,1)$，再从 $(n,1)$ 走到 $(n,m)$ 即可。可以证明这是最短路线中的一条。

定义答案为 $ans$，那么有以下式子：

$$ans=(n-1)+(m-1)=n+m-2$$

最后输出 $ans$ 即可，代码很好写就不放了。

---

## 作者：Lib_Zhang (赞：0)

#### 题意简述:
给定一个 $n \times m$ 的棋盘，其中存在一个可以发射激光的点 $(sx,sy)$ 机器人从起点 $(1,1)$ 出发，每次可以移动到相邻四个位置，重点是 $(n,m)$ ，机器人不能经过距离激光发射点曼哈顿距离小于等于 $d$ 的点，求机器人到 $(n,m)$ 最少移动次数。

#### 分析:

要想求最短距离，必然只能向下或向右走，所以答案只有 $n + m - 2$ 或 $-1$ 。

所以只需要判断 $-1$ 的情况即可.

可以发现 $-1$ 的情况有四种:

- 起点被激光点封住，即 $ (sx-d \le 1) $ 并且 $(sy-d \le 1) $.
- 终点被激光点封住，即 $ (sx+d \ge n) $ 并且 $ (sy+d \ge m) $.
- 起点和终点被一条竖线分开，即 $ sx-d \le 1 $ 并且 $ sx+d \ge n $.
- 起点和终点被一条横线分开， 即 $ sy-d \le 1  $ 并且 $ sy+d \ge m  $.

### 代码:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<set>
#include<stack>
#include<map>
#include<queue>
#include<cstdlib>
#include<iomanip>
#include<utility>
#define mid (l+r>>1)
#define endl '\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pai;
const double eps = 1e-10;
const int base = 13331;
const long long mod = 998242353;
long long maxn = -2147483647-1,minn = 0x7f7f7f7f;
ll t,n,m,sx,sy,d;
int main(){
	//freopen("filename.in","r",stdin);
	//freopen("filename.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>sx>>sy>>d;
		if(((sx-d<=1)&&(sy-d<=1))||((sx-d<=1)&&(sx+d>=n))||((sy-d<=1)&&(sy+d>=m))||((sx+d>=n)&&(sy+d>=m))){
			cout<<-1<<endl;
			continue;
		}
		cout<<n+m-2<<endl;
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}


```

#### 总结:
思维题。


---

