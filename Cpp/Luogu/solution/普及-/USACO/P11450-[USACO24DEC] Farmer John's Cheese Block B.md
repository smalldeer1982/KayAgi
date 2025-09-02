# [USACO24DEC] Farmer John's Cheese Block B

## 题目描述

Farmer John 有一块立方体形状的奶酪，它位于三维坐标空间中，从 $(0,0,0)$ 延伸至 $(N,N,N)$（$2≤N≤1000$）。Farmer John 将对他的奶酪块执行一系列 $Q$（$1≤Q≤2⋅10^5$）次更新操作。

对于每次更新操作，FJ 将从整数坐标 $(x,y,z)$ 到 $(x+1,y+1,z+1)$ 处切割出一个 $1×1×1$ 的奶酪块，其中 $0≤x,y,z<N$。输入保证在 FJ 切割的位置上存在一个 $1×1×1$ 的奶酪块。由于 FJ 正在玩牛的世界，当下方的奶酪被切割后，重力不会导致上方的奶酪掉落。

在每次更新后，输出 FJ 可以将一个 $1×1×N$ 的砖块插入奶酪块中的方案数，使得砖块的任何部分都不与剩余的奶酪重叠。砖块的每个顶点在全部三个坐标轴上均必须具有整数坐标，范围为 $[0,N]$。FJ 可以随意旋转砖块。

## 说明/提示

### 样例解释

在前三次更新操作后，$[0,1]×[0,2]×[0,1]$ 范围的 $1×2×1$ 砖块与剩余的奶酪不重叠，因此它贡献了答案。

![](https://usaco.org/current/data/fig_1_cheese_bronze_dec24.png)

### 测试点性质

- 测试点 1：样例。
- 测试点 2-4：$N≤10$ 且 $Q≤1000$。
- 测试点 5-7：$N≤100$ 且 $Q≤1000$。
- 测试点 8-16：没有额外限制。

## 样例 #1

### 输入

```
2 5
0 0 0
1 1 1
0 1 0
1 0 0
1 1 0```

### 输出

```
0
0
1
2
5```

# 题解

## 作者：Su777 (赞：7)

# USACO 24Dec Bronze B 题解

## 题意

给定一个三维的正方体奶酪，坐标从 $(0,0,0)$ 延伸到 $(N, N, N)$。有 $Q$ 次询问，每次询问给定三个数 $(x, y, z)$，表示切去由坐标点 $(x,y,z)$ 到坐标点 $(x+1,y+1,z+1)$ 的一个 $1\times 1\times 1$ 立方体奶酪。然后询问，在这个残缺的奶酪中，可以有多少种方式，可以插入一个 $1\times 1\times N$ 的木棒。保证对于 $1\leq i\leq Q$，$(x_i, y_i, z_i)$ 互不相同。

## 分析

可以对题意进行转化。空间中共有 $N\times N\times N$ 个正方体，为了方便，把他们表示为 $\{0,0,0\}$ 到 $\{N-1,N-1,N-1\}$。一个木棒相当与占据了 $n$ 个小正方体，且这 $n$ 个正方体在某一方向是连续的。在坐标上，这种规律呈现为 $x,y,z$ 三种坐标中有两种相同，另外一种构成一个 $1\sim n$ 的排列。比如当 $N=3$ 时，$\{1, 1, 0\},\{1, 1, 1\},\{1, 1, 2\}$ 这三个位置。

## 暴力

很显然当 $N\leq 100$ 时，可以开数组标记是否已经被挖掉。判断那些位置可以插入木棒时，$O(N^2)$ 枚举 $(x,y)$，$(x,z)$ 和 $(y,z)$，然后 $O(N)$ 判断是否可以插入。复杂度 $O(N^3Q)$。

## 对暴力进行优化

因为是在不停的扣奶酪，所以不难发现答案是单调不减的。

发现对于每一组相同的 $(x,y)$ 或 $(x,z)$ 或 $(y,z)$ 坐标，当且仅当这一条被覆盖了 $N$ 次后，才会对答案产生 $+1$ 的贡献。开三个 `map` 记录一下，每次更新的时候判断一下是否满足条件即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
const int Q = 2e5 + 5;
int n, q, x, y, z;
map<PII, int> mapab;
map<PII, int> mapac;
map<PII, int> mapbc;

int main() {
    scanf("%d %d", &n, &q);
    int ans = 0;
    for (int i = 1; i <= q; i ++) {
        scanf("%d %d %d", &x, &y, &z);
        mapab[{x, y}] ++;
        mapac[{x, z}] ++;
        mapbc[{y, z}] ++;
        if (mapab[{x, y}] == n) ans ++;
        if (mapac[{x, z}] == n) ans ++;
        if (mapbc[{y, z}] == n) ans ++;
        printf("%d\n", ans);
    }
    return 0;
}
// 是的，AC 代码比暴力要短
```

那这个题就做完了，撒花。

---

## 作者：DrDuck (赞：4)

# 基本思路 #
~~比赛的时候一直以为砖块是 $1 \times 1 \times 2$ 的坑了我好久~~

首先开三位数组是不行的，会炸。

但是题目问你有几种方式放下 $1 \times 1 \times n$ 的砖块，不就是问你有几条直线被挖空了吗？

开三个二维数组，记录每条直线被挖空了几个方块，然后如果直线被完全挖空了，就将 $ans$ 自增 $1$ 就好了。
# CODE #

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1003;
int n, q, ans;
int x[maxn][maxn], y[maxn][maxn], z[maxn][maxn];
int main()
{
	cin >> n >> q;
	for (int i = 1; i <= q; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		x[a][b]++;
		y[a][c]++;
		z[b][c]++;
		if (x[a][b] == n)
		{
			ans++;
		}
		if (y[a][c] == n)
		{
			ans++;
		}
		if (z[b][c] == n)
		{
			ans++;
		}
		cout << ans << endl;
	}
	return 0;
}
```
拒绝抄袭！

---

## 作者：GSQ0829 (赞：3)

#### [[USACO24DEC] Farmer John's Cheese Block B](https://www.luogu.com.cn/problem/P11450)

---
### 解题思路：
我们其实可以发现每次割出来的小方块只会影响到那一行、列。所以只需要判断割出来的数量是否等于 $N$，如果相等，方案数就加一。

---
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;
int x[MAXN][MAXN], y[MAXN][MAXN], z[MAXN][MAXN], n, q, a, b, c, ans = 0;

int main() {
	cin >> n >> q;
	for (int i = 1; i <= q; i++) {
		cin >> a >> b >> c;
        // 判断的代码
		if (++x[a][b] == n) ans++;
		if (++y[a][c] == n) ans++;
		if (++z[b][c] == n) ans++;
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：orpg (赞：3)

### 题目大意
给一个边长为 $N$ 的立方体，共有 $Q$ 个操作，每一个操作会挖走一个边长为 $1$ 的小立方体，问每一次操作后会有多少行，列和竖列被挖空。
### 思路
对于一个立方体表示一行，一列或一竖列其实就相当与在一个平面上取一个点。又因为题目是求哪一行，列和竖列被挖空，所以只需要记录对于一行，列和竖列一共被挖了多少次，如果等于 $N$ 就表示被挖空了，记录答案。

刚刚好，因为 $2≤N≤1000$ 所以我们开三个二维数组分别用于表示行，列和竖列。

### code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e3+5;
ll n,q,sum;
ll dimen1[N][N];
ll dimen2[N][N];
ll dimen3[N][N];
short check(int x,int y,int z){
	short ans=0;
	if(dimen1[x][y]==n) ans++;
	if(dimen2[y][z]==n) ans++;
	if(dimen3[x][z]==n) ans++;
	return ans;
}
main(){
	scanf("%d%d",&n,&q);
	while(q--){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		dimen1[x][y]++,dimen2[y][z]++,dimen3[x][z]++;
		sum+=check(x,y,z);
		printf("%d\n",sum);
	}
	return 0;
}
```

---

## 作者：yehongxin (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/P11450)
## 题目大意
Farmer John 有一个正方体，它位于三维坐标空间中，从 $(0,0,0)$ 延伸到 $(N,N,N)$，现在执行 $Q$ 次操作。

对于每次更新操作，将从整数坐标 $(x,y,z)$ 到 $(x+1,y+1,z+1)$ 处割出一个 $1×1×1$ 的方块。当下面方块被切割后，重力不会导致上面的方块掉落。
## 解题思路
我们不难发现每次割出的小方块只会影响到那一行、列。所以只需要监测有多少个小方块割出，如果割出的数量等于 $N$ 的话，方案数加一。
## 参考代码

```cpp
#include<bits/stdc++.h>
#define N 1005
using namespace std;
int x[N][N],y[N][N],z[N][N],n,q,a,b,c,ans;
int main(){
	cin>>n>>q;
	for(int i=1;i<=q;i++)
	{
		cin>>a>>b>>c;//输入三维坐标
		if(++x[b][c]==n) ans++;//如果被割出的小方块等于N了，方案数加一
		if(++y[a][c]==n) ans++;
		if(++z[a][b]==n) ans++;
		cout<<ans<<endl;//输出方案数
	}
	return 0;
} 
```

---

## 作者：WFHFAQFXY (赞：3)

# Farmer John's Cheese Block

题目不必多说，就是求操作后一共可能有多少为 $1 \times 1 \times n$ 的列。 
# 主要思路  
直接模拟很明显是不行的，首先 $n$ 的范围就不支持用三维数组存。  

不妨从另一个角度分析这个问题，从一个面上能够插入一个 $1 \times 1 \times n$ 的砖块，那么这个位置一定被操作了 $n$ 次，也就是每一个都被挖空了，而且他不会去挖已经被挖掉的位置。

而且面对面的两个面，因为是通的，因此看上去其实是一样的。

那么好，我们就可以放三个二维数组，分别是从上、前、右看的面，那么就可以实现我们所说的这个算法。

# 赛时代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005][1005],b[1005][1005],c[1005][1005],n,m,ma,mb,mc,las;//abc分别对应三个面
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>ma>>mb>>mc;
		a[ma][mb]++,b[ma][mc]++,c[mb][mc]++;
		//每一次操作时，如果要增加，那么一定会在被删的这个格子所在的列里面才有可能再通一条，所以在输入时操作即可。 
		if(a[ma][mb]==n) las++;
		if(b[ma][mc]==n) las++;
		if(c[mb][mc]==n) las++;
		cout<<las<<'\n';
	}
	return 0;
}
```

---

## 作者：liuzhuoran141516 (赞：1)

# USACO 24Dec Bronze B 题解

## 思路

### 初始状态： 
 - 初始时，奶酪块是一个完整的立方体，从 $(0,0,0)$ 到 $(N,N,N)$。
 - 我们可以将奶酪块看作一个三维数组 `c[x][y][z]`，其中 `c[x][y][z]` 表示该位置是否有奶酪。

### 切割操作： 
 - 每次切割操作会移除一个 $1 \times 1 \times 1$ 的奶酪块，即设置 `c[x][y][z] = 0`。

## 暴力： 
 - 我们需要计算可以插入的 $1 \times 1 \times N$ 砖块的方案数。砖块可以沿任意轴 $(x,y,z)$ 插入，并且可以旋转。
 - 具体来说，砖块可以沿 $x$ 轴、$y$ 轴或 $z$ 轴插入。对于每种情况，我们需要检查从 $(0,0,0)$ 到 $(0,0,N)$、$(0,0,0)$ 到 $(0,N,0)$、$(0,0,0)$ 到 $(N,0,0)$ 的路径上是否有任何奶酪块被移除。
 - 如果路径上没有任何奶酪块被移除，则该路径是一个有效的插入方案，复杂度 $O(N^3Q)$。

## 暴力优化： 
 - 显然暴力会超时，所以我们要优化。
 - 对于每一组相同的 $(x,y)$ 或 $(x,z)$ 或 $(y,z)$ 坐标，当且仅当这一条被覆盖了 $N$ 次以后，才会对答案产生 $+1$ 的贡献。

**代码**： 

```cpp
#include <bits/stdc++.h>
#define int long long
#define x a[i].a1
#define y a[i].a2
#define z a[i].a3
using namespace std;
const int N = 1005;
int n, q, ans;
int xy[N][N], xz[N][N], yz[N][N];
struct node {
	int a1, a2, a3;
}a[200005];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= q; i++) {
		cin >> x >> y >> z;
		xy[x][y]++;
		xz[x][z]++;
		yz[y][z]++;
		if (xy[x][y] == n) {
			ans++;
		}
		if (yz[y][z] == n) {
			ans++;
		}
		if (xz[x][z] == n) {
			ans++;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Pratty (赞：1)

题意：每一次在三维坐标系中切除一个块，每次切除后询问有多少行或列别完整的切除了。

我们发现，如果一行或列被切除了，那么它就永远的被切除了，不会再次从答案中撤回，也不会再次计算到答案中。

所以由此得出结论：答案是一个单调不减序列。

通过样例可以看出，每一行或列如果**已经**被切除，在输入的时候会有一个共同特点：这一行或列的每个点的 $x,y,z$ 中一定有两个值是相同的，另一个值是 $0\sim N-1$ 这 $N$ 个数。所以我们可以开三个 $sum$ 数组，分别记录当 $x,y$ 值相同、$y,z$ 值相同、$x,z$ 值相同且分别等于 $i,j$ 时，这一行或列已经有 $sum_{i,j}$ 块被切除了。

换句话说，可以用一个 $sum$ 数组记录一个平面的答案，故三个平面由三个 $sum$ 记录，我们可以边输入边累加，亦同时输出，就可以实现时间复杂度为 $O(Q)$ 的代价来通过这道题。

注意开较大的数据类型。

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1100;
int n, q, ans;
int sumxy[N][N], sumxz[N][N], sumyz[N][N];
struct node {
	int x, y, z;
}a[210000];
signed main() {
	scanf("%lld%lld", &n, &q);
	for (int i = 1; i <= q; i++) {
		scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].z);
		sumxy[a[i].x][a[i].y]++;
		sumxz[a[i].x][a[i].z]++;
		sumyz[a[i].y][a[i].z]++;
		if (sumxy[a[i].x][a[i].y] == n) ans++;
		if (sumyz[a[i].y][a[i].z] == n) ans++;
		if (sumxz[a[i].x][a[i].z] == n) ans++;
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：vanueber (赞：1)

# 题目大意

在类似 mc 的反重力世界中，有一个 $n \times n \times n$ 大方块，每次敲掉其中的一个方块，同时询问有多少种方案能放下一个 $1 \times 1 \times n$ 的块。

# 题目分析

若是直接模拟，数组都开不下。

但是如果放在一个二维平面上考虑，问题会简单很多：

我们用 $(i,j,k)$ 表示一个从 $(i,j,k)$ 到 $(i+1,j+1,k+1)$ 的方块

压缩 $y$ 轴，用 $h_{i,j}$ 表示$(i,j,1)$ 及其上方有多少奶酪块。

那么 $(i,j,1)$ 到 $(i,j,n)$ 能够贡献答案，当且仅当 $h_{i,j}=0$。

同理地，压缩其他坐标轴，也有类似的结论。

于是只用开三个二维数组分别记录下就行。时间复杂度 $\Theta(q)$，空间复杂度 $\Theta(n^2)$。

# 代码实现


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <ctime>
#include <random>

using namespace std;

const int INF = 0x3f3f3f3f;

inline int read()
{
	int w = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		w = (w << 1) + (w << 3) + (ch ^ 48);
		ch = getchar();
	}
	return w * f;
}

inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

const int maxn=1005;
int n,q;
int res1[maxn][maxn],res2[maxn][maxn],res3[maxn][maxn];
//res1 固定x,y当前剩的z
//res2 固定x,z当前剩的y
//res3 固定y,z当前剩的x

int main()
{
	n=read(),q=read();
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			res1[i][j]=res2[i][j]=res3[i][j]=n;
		}
	}
	int ans=0;
	for(int i=1,x,y,z;i<=q;++i)
	{
		x=read(),y=read(),z=read();
		++x,++y,++z;
		res1[x][y]--,res2[x][z]--,res3[y][z]--;
		if(res1[x][y]==0) ++ans;
		if(res2[x][z]==0) ++ans;
		if(res3[y][z]==0) ++ans;
		cout<<ans<<endl;
	}
	return 0;
}


```

---

## 作者：CommandSR (赞：1)

## 题意简化

结合样例解释给出的参考图理解。

挖空一个 $n \times n \times n$ 立方体内的部分格子，欲将一个 $n \times 1 \times 1$ 的柱子嵌入，问有多少种方案。

## 基本思路

显然 $2 \le N \le 1000$ 无法直接用三维数组存下，尝试换一个角度看问题。

尝试从正上方俯视这个立方体，能够看到一个 $n \times n$ 的平面，我们用 $up_{i, j}$ 存储俯视这一个点向下的 $n$ 格被挖空的个数，当挖空个数恰好等于 $n$ 时将 $ans$ 加一。

从正面，侧面看同理。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n, q;
int up[N][N], lf[N][N], rt[N][N];
int ans = 0;
int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	int ans = 0;
	for (int i = 1; i <= q; i++)
	{
		int x, y, z;
		cin >> x >> y >> z;
		up[y][z] ++;
		lf[x][z] ++;
		rt[x][y] ++;
		if (up[y][z] == n) ans++;
		if (lf[x][z] == n) ans++;
		if (rt[x][y] == n) ans++;
		cout << ans << '\n';
	}	
	return 0;
}
```

拒绝抄袭！

---

## 作者：xu_jh (赞：0)

[USACO2024铜组T2](https://usaco.org/index.php?page=viewproblem&cpid=1432&lang=zh)

[我的博客园的文章](https://www.cnblogs.com/xjh-OI-Forever/articles/18611229)

注意到：
>FJ 可以随意旋转砖块。

于是，我们可以从不同的角度，即 $x$ 方向、$y$ 方向、$z$ 方向三个方向来统计答案，以此做到不重不漏。

然后，我们注意到，如果有位置能够放下砖块：
对于砖块 $(1,1,n)$，只要有 $n$ 个被消除的位置它们的 $x,y$ 都相等，那么在 $(x,y,1)$ $\sim$ $(x,y,n)$ 的位置，就可以放下一个 $(1,1,n)$ 的砖块。

对于砖块 $(1,n,1)$，只要有 $n$ 个被消除的位置它们的 $x,z$ 都相等，那么在 $(x,1,z)$ $\sim$ $(x,n,z)$ 的位置，就可以放下一个 $(1,1,n)$ 的砖块。

对于砖块 $(n,1,1)$，只要有 $n$ 个被消除的位置它们的 $y,z$ 都相等，那么在 $(1,y,z)$ $\sim$ $(n,y,z)$ 的位置，就可以放下一个 $(n,1,1)$ 的砖块。

而且观察到：
>由于 FJ 正在玩牛的世界，当下方的奶酪被切割后，重力不会导致上方的奶酪掉落。 

所以每一次更新，消除一个单位体积的奶酪，都只会影响其在 $x$ 方向, $y$ 方向, $z$ 方向的方案数，对其它的位置并没有影响，而且每一次更新，方案数相较以前的方案数最多会 $+3$ （并且每一次能够插入砖块的方案数所组成的序列，是单调不降的）。

于是，我们搞一个 $cnt$ ，每次统计完答案直接加到 $cnt$ 中就行，然后输出 $cnt$ 。

然后，我们可以开三个二维数组，表示当前 $(x,y,1)$ $\sim$ $(x,y,n)$ 或者 $(x,1,z)$ $\sim$ $(x, n, z)$ 或者 $(1,y,z)$ $\sim$ $(n,y,z)$ 的位置能否插入一个砖块，并且每次消除奶酪的时候，三个数组中表示当前二维位置的元素都 $+1$ ；对于每个数组，如果当前二维位置统计到了 $n$ 个，那么 $cnt$ 加一。

```cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;
const int maxn = 1e3 + 10;
int x[maxn][maxn];
int y[maxn][maxn];
int z[maxn][maxn];

int main()
{
  int n, q;
  cin >> n >> q;
  long long cnt = 0;
  while (q--)
  {
    int a, b, c;
    cin >> a >> b >> c;
    x[b][c]++;
    y[a][c]++;
    z[a][b]++;
    if (x[b][c] == n)
      ++cnt;
    if (y[a][c] == n)
      ++cnt;
    if (z[a][b] == n)
      ++cnt;
    cout << cnt << '\n';
  }
  return 0;
}
```

---

## 作者：K_yuxiang_rose (赞：0)

我们发现，当删去一个小块时，只会对其所在行、所在列和所在高，考虑开三个数组，分别统计三个面的剩余小块，当小块数为零时方案数加一。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1005][1005],b[1005][1005],c[1005][1005];
signed main()
{
	int n,q,ans=0;
	cin>>n>>q;
	for(int i=0;i<=1000;i++)
	{
		for(int j=0;j<=1000;j++)
		{
			a[i][j]=n;
			b[i][j]=n;
			c[i][j]=n;
		}
	}//初始化，三个方向一开始都有n个小块
	while(q--)
	{
		int x,y,z;
		cin>>x>>y>>z;
		a[x][y]--;
		if(!a[x][y]) ans++;
		b[y][z]--;
		if(!b[y][z]) ans++;
		c[x][z]--;
		if(!c[x][z]) ans++;
		cout<<ans<<endl;
	}
	return 0;
} 

```

---

## 作者：ChenZQ (赞：0)

我们发现，插入的方案可以归类为三种，长，宽，高。

所以我们就可以开三个二维数组，每次切掉一个奶酪块就按坐标在三个维度代表的二维数组上减掉，变成 $0$ 了就增加答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[1010][1010],b[1010][1010],c[1010][1010];
int n,q;

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) a[i][j]=b[i][j]=c[i][j]=n;
	}
	int cnt=0;
	while(q--)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		x++,y++,z++;
		a[x][y]--;b[x][z]--;c[y][z]--;
		if(a[x][y]==0) cnt++;
		if(b[x][z]==0) cnt++;
		if(c[y][z]==0) cnt++;
		printf("%d\n",cnt);
	}
}
/*
5
5
1 2 3 4 5
1 5 2
1 4 3
*/

```

---

## 作者：greater_than (赞：0)

### 思路
我们开三个二维数组 $ ch $。$ ch1 $ 表示从前面看位置 $ x , y $ 有没有被凿空。$ ch2 $ 与 $ ch3 $ 同理。   
对与每一次操作，读入 $ x , y , z $。则标记 $ ch1_{x,y} , ch2_{y,z} , ch3_{x,z} $ 加一。如过加完之后值为 $ n $，则证明被凿空了，$ ans $ 加一。
### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int ch1[1001][1001],ch2[1001][1001],ch3[1001][1001];
long long ans=0;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    register int N, Q;
    cin >> N >> Q;
    while (Q--) {
        register int x, y, z;
        cin >> x >> y >> z;
        ch1[x][y]++,ch2[y][z]++,ch3[x][z]++;
        if(ch1[x][y]==N)ans++;
        if(ch2[y][z]==N)ans++;
        if(ch3[x][z]==N)ans++;
        cout << ans << endl;
    }
}
```

---

## 作者：Statax (赞：0)

## 前言

~~来个唐氏题解，其他的题解都虐爆此篇。~~

## 分析

注意到 $N \leq 1000, Q \leq 2 \cdot 10^5$，说明 $O(QN)$ 是能过的。

又注意到每次更新最多影响三个方向，那每次更新循环三遍就行。

那选哪个存三维呢？数组？空间爆炸；`map`？时间爆炸；还是 `bitset` 大佬。

## 代码

比其它代码长亿点点…

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) x & (-x)

using namespace std;
constexpr int MAXN = 1e3 + 5;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;

int getIndex(int x, int y, int z, int n)
{
    return x * n * n + y * n + z;
}

int n, q;
bitset<MAXN * MAXN * MAXN> umap;

int calc(int x, int y, int z)
{
    int cnt = 3;
    int rd1 = rand() % n, rd2 = rand() % n, rd3 = rand() % n;
    int index1 = getIndex(rd1, y, z, n);
    if (!umap[index1])
        --cnt;
    else {
        for (int i = 0; i < n; ++i) {
            int check_index = getIndex(i, y, z, n);
            if (!umap[check_index]) {
                --cnt;
                break;
            }
        }
    }

    int index2 = getIndex(x, rd2, z, n);
    if (!umap[index2])
        --cnt;
    else {
        for (int i = 0; i < n; ++i) {
            int check_index = getIndex(x, i, z, n);
            if (!umap[check_index]) {
                --cnt;
                break;
            }
        }
    }

    int index3 = getIndex(x, y, rd3, n);
    if (!umap[index3])
        --cnt;
    else {
        for (int i = 0; i < n; ++i) {
            int check_index = getIndex(x, y, i, n);
            if (!umap[check_index]) {
                --cnt;
                break;
            }
        }
    }

    return cnt;
}

signed main()
{
    srand(time(0));
    scanf("%lld%lld", &n, &q);
    int ans = 0;
    for (int i = 1; i <= q; ++i) {
        short x, y, z;
        scanf("%hd%hd%hd", &x, &y, &z);
        int index = getIndex(x, y, z, n);
        umap[index] = true;
        if (i >= n)
            ans += calc(x, y, z);
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：GFyyx (赞：0)

## 忠告
USACO 比赛没看懂题最好看看英语原版，一定有收获。

边界条件好好检查，不然 Debug 半天调不出来。

## 题目大意
在三维坐标空间中，从 $(0,0,0)$ 延伸至 $(N,N,N)(2\leq N \leq1000)$。现在将执行 $Q(1\leq Q \leq 2\times10^5)$ 次更新操作。

对于每次更新操作，将从整数坐标 $(x,y,z)$ 到 $(x+1,y+1,z+1)$ 处切割出一个 $1\times1\times1$ 的方块。

当下方的方块被切割后，重力不会导致上方的方块掉落。

在每次更新后，输出 $1×1×N$ 可以随意旋转的长条，使得其的任何部分都不与剩余的方块重叠。长条的每个顶点在全部三个坐标轴上均必须具有整数坐标，范围为 $[0,N]$。

## 正确做法
显然大模拟的时间和空间复杂度是我们无法接受的，我们注意到每次取出方块只会影响那一行、列，对于每个 $1×1×N$ 的条，我们记录下有多少个小方块被取出，如果经过操作后被取出的个数等于 $N$，答案加一。

## 场切代码
```cpp
#include<iostream>
using namespace std;
int blkx[1001][1001],blky[1001][1001],blkz[1001][1001];
int main(){
	int n,q; cin >> n >> q;
	int x,y,z,ans=0;
	while(q--){
		cin >> x >> y >> z;
		if(++blkx[y][z]==n) ans++;
		if(++blky[x][z]==n) ans++;
		if(++blkz[x][y]==n) ans++;
		cout << ans << endl;
	}
}
```

---

## 作者：wht_1218 (赞：0)

我不知道我的做法是不是正解。

每一个操作我们将对应的奶酪块 $a_{x,y,z}$ 设置为“空”。

对于查询，我们可以枚举一个数 $i$，由于 $1\times 1 \times n$ 的奶酪块的限制，我们每一次只要判断 $a_{i,y,z},~a_{x,i,z},~a_{x,y,i}$ 是否均为空即可求出三个方向（长、宽、高）是否可以放入 $1\times 1 \times n$ 的奶酪块。

每一次的答案要叠加。

由于 $a_{i,j,k}$ 只可能是 $0,1$，所以可使用 `bitset` 优化，我就是这样的。


```cpp
cin>>n>>q;
while(q--){
  int x,y,z;cin>>x>>y>>z;
  x++,y++,z++;
  a[x][y][z]=1;
  int f1=1,f2=1,f3=1;
  for(int i=1;i<=n;++i){
    if(!a[i][y][z])f1=0;
    if(!a[x][i][z])f2=0;
    if(!a[x][y][i])f3=0;
  }ans+=f1+f2+f3;
  cout<<ans<<"\n";
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

一个位置 $(x,y,[1,n])$ 能放下长棒子，当且仅当这部分没有奶酪。$(x,[1,n],z),([1,n],y,z)$ 同理。

于是，我们直接去维护这三个东西就完了。修改 $(x,y,z)$ 的时候，$(x,y,[1,n]),(x,[1,n],z),([1,n],y,z)$ 各会减少一个。最后加上这三者中新增的 $0$ 值个数就完了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, vx[1005][1005], vy[1005][1005], vz[1005][1005], ans;
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			vx[i][j] = vy[i][j] = vz[i][j] = n;
	for (int i = 1, a, b, c; i <= m; ++i) {
		cin >> a >> b >> c;
		a++, b++, c++;
		ans += (!--vx[a][b]);
		ans += (!--vy[a][c]);
		ans += (!--vz[b][c]);
		cout << ans << endl;
	}
}
```

---

## 作者：Your_Name (赞：0)

## 题解
显然每次取走都会使三条 $1\times 1 \times N$ 的长条少一个块，于是直接维护每一面还剩几个如果减到 $0$ 就累加答案就行。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int n, q, d[N][N], l[N][N], r[N][N], ans, x, y, z;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < n; j ++){
			d[i][j] = l[i][j] = r[i][j] = n;
		}
	}
	while(q --){
		cin >> x >> y >> z;
		d[x][y] --;
		if(d[x][y] == 0)ans ++;
		l[x][z] --;
		if(l[x][z] == 0)ans ++;
		r[z][y] --;
		if(r[z][y] == 0)ans ++;
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：masonxiong (赞：0)

# 题目分析

从立方体中选取一面，再从这个面上选取一个位置，这个位置上能引出奶酪块，当且仅当这个位置所对应的一条被挖空了。

那么我们维护三个面（为什么不是六个面自己思考一下）中每个点所对应的一条被挖掉的数量，当某一次更新后某一条被挖掉的数量到达了 $n$，说明这一条被挖空了，那么我们更新答案即可。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1e3 + 5;
int n, q, x, y, z, c;
int cntxy[Maxn][Maxn], cntyz[Maxn][Maxn], cntzx[Maxn][Maxn];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	for (cin >> n >> q; q--; ) {
		cin >> x >> y >> z;
		cout << (c += (++cntxy[x][y] == n) + (++cntyz[y][z] == n) + (++cntzx[z][x] == n)) << '\n';
	}
    return 0;
}
```

---

