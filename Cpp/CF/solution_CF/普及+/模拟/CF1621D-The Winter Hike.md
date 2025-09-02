# The Winter Hike

## 题目描述

Circular land is an $ 2n \times 2n $ grid. Rows of this grid are numbered by integers from $ 1 $ to $ 2n $ from top to bottom and columns of this grid are numbered by integers from $ 1 $ to $ 2n $ from left to right. The cell $ (x, y) $ is the cell on the intersection of row $ x $ and column $ y $ for $ 1 \leq x \leq 2n $ and $ 1 \leq y \leq 2n $ .

There are $ n^2 $ of your friends in the top left corner of the grid. That is, in each cell $ (x, y) $ with $ 1 \leq x, y \leq n $ there is exactly one friend. Some of the other cells are covered with snow.

Your friends want to get to the bottom right corner of the grid. For this in each cell $ (x, y) $ with $ n+1 \leq x, y \leq 2n $ there should be exactly one friend. It doesn't matter in what cell each of friends will be.

You have decided to help your friends to get to the bottom right corner of the grid.

For this, you can give instructions of the following types:

- You select a row $ x $ . All friends in this row should move to the next cell in this row. That is, friend from the cell $ (x, y) $ with $ 1 \leq y < 2n $ will move to the cell $ (x, y + 1) $ and friend from the cell $ (x, 2n) $ will move to the cell $ (x, 1) $ .
- You select a row $ x $ . All friends in this row should move to the previous cell in this row. That is, friend from the cell $ (x, y) $ with $ 1 < y \leq 2n $ will move to the cell $ (x, y - 1) $ and friend from the cell $ (x, 1) $ will move to the cell $ (x, 2n) $ .
- You select a column $ y $ . All friends in this column should move to the next cell in this column. That is, friend from the cell $ (x, y) $ with $ 1 \leq x < 2n $ will move to the cell $ (x + 1, y) $ and friend from the cell $ (2n, y) $ will move to the cell $ (1, y) $ .
- You select a column $ y $ . All friends in this column should move to the previous cell in this column. That is, friend from the cell $ (x, y) $ with $ 1 < x \leq 2n $ will move to the cell $ (x - 1, y) $ and friend from the cell $ (1, y) $ will move to the cell $ (2n, y) $ .

Note how friends on the grid border behave in these instructions.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1621D/7dcaab901980e50347f58a947000827b29e91e59.png)Example of applying the third operation to the second column. Here, colorful circles denote your friends and blue cells are covered with snow.You can give such instructions any number of times. You can give instructions of different types. If after any instruction one of your friends is in the cell covered with snow he becomes ill.

In order to save your friends you can remove snow from some cells before giving the first instruction:

- You can select the cell $ (x, y) $ that is covered with snow now and remove snow from this cell for $ c_{x, y} $ coins.

You can do this operation any number of times.

You want to spend the minimal number of coins and give some instructions to your friends. After this, all your friends should be in the bottom right corner of the grid and none of them should be ill.

Please, find how many coins you will spend.

## 说明/提示

In the first test case you can remove snow from the cells $ (2, 1) $ and $ (2, 2) $ for $ 100 $ coins. Then you can give instructions

- All friends in the first collum should move to the previous cell. After this, your friend will be in the cell $ (2, 1) $ .
- All friends in the second row should move to the next cell. After this, your friend will be in the cell $ (2, 2) $ .

In the second test case you can remove all snow from the columns $ 3 $ and $ 4 $ for $ 22 $ coins. Then you can give instructions

- All friends in the first row should move to the next cell.
- All friends in the first row should move to the next cell.
- All friends in the second row should move to the next cell.
- All friends in the second row should move to the next cell.
- All friends in the third column should move to the next cell.
- All friends in the third column should move to the next cell.
- All friends in the fourth column should move to the next cell.
- All friends in the fourth column should move to the next cell.

It can be shown that none of the friends will become ill and that it is impossible to spend less coins.

## 样例 #1

### 输入

```
4
1
0 8
1 99
2
0 0 0 0
0 0 0 0
9 9 2 2
9 9 9 9
2
0 0 4 2
0 0 2 4
4 2 4 2
2 4 2 4
4
0 0 0 0 0 0 0 2
0 0 0 0 0 0 2 0
0 0 0 0 0 2 0 0
0 0 0 0 2 0 0 0
0 0 0 2 2 0 2 2
0 0 2 0 1 6 2 1
0 2 0 0 2 4 7 4
2 0 0 0 2 0 1 6```

### 输出

```
100
22
14
42```

# 题解

## 作者：一念之间、、 (赞：6)

# 简述题意
说：给 $2n*2n $ $ n<=250$ 的矩形，最开始 $n*n$ 个人在左上角 $n*n$ ，要移动到右下角 $n*n$ ，可以对一行或者一列选择整体向上/下或者整体向左/右平移，然后超出边界就在另一端出现。（可以看样例结束图片）有一些格子有积雪，一片积雪有个代价，要求人走的所有地方没有积雪，问最小清除积雪代价。

# 题解
很遗憾考试没有做出来。

显然不好去找路径，显然右下角 $n*n$ 要扫完。

尝试手推几个样例，找到些许规律

![](https://cdn.luogu.com.cn/upload/image_hosting/9r77p5ym.png)

可以发现对于红色四个点，无论怎么动，都至少经过蓝色八个点之一，然后又可以发现，只要经过一个蓝色点就可以把所有人都通过这个方式送到右下角去。所以 $ans=$ 八个点取min+右下角的和。

# 代码


```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
//#define getchar gc
int read()
{
	char c;
	int w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	int ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&s==t))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x);pc(op,0);
}
int a[505][505];
int main(){
	int T=read();
	while(T--)
	{
		int n=read();
		for(int i=1;i<=n+n;i++)
			for(int j=1;j<=n+n;j++)a[i][j]=read();
		ll ans=0;
		for(int i=n+1;i<=n+n;i++)
			for(int j=n+1;j<=n+n;j++)ans+=a[i][j];
		int mn=2e9;
		mn=min(mn,a[1][n+1]);
		mn=min(mn,a[1][n+n]);
		mn=min(mn,a[n][n+1]);
		mn=min(mn,a[n][n+n]);
		mn=min(mn,a[n+1][n]);
		mn=min(mn,a[n+1][1]);
		mn=min(mn,a[n+n][1]);
		mn=min(mn,a[n+n][n]);
		cout<<ans+mn<<"\n";
	}
	pc('1',1);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：3)

> [CF1621D The Winter Hike](https://www.luogu.com.cn/problem/CF1621D)。

有趣的思维题。

考虑 $(1, 1), (1, n), (n, 1)$ 和 $(n, n)$ 这四个格子，若要移动其中任意一个，必然需要清理 $(n + 1, 1) / (n + 1, n) / (2n, 1) / (2n, n)$ 或者 $(1, n + 1)/(n, n + 1) / (1, 2n) / (n, 2n)$ 这八个格子上任意一个格子的雪，即左下角正方形和右上角正方形的四个角。

又因为如果清理了任意一个，我们必然可以构造一组方案，使得只经过该格子以及右下角的所有格子。考虑每次只移动一个人，若清理 $(1, 2n)$，则 $(1, 1)$ 的路线可以为 $(1, 1)\to (1, 2n)\to (2n, 2n)$，即第一行左移，第 $n$ 列上移，然后任意移动至右下角正方形的某一个位置。此时原来的 $(1, 2)$ 现在被移动至 $(1, 1)$，类似地进行上述操作即可。

因此答案即 $\min(c_{n + 1, 1}, c_{n + 1, n}, \cdots, ) + \sum_{i, j > n} c_{i, j}$。时间复杂度 $\mathcal{O}(n ^ 2)$。

```cpp
const int N = 500 + 5;
ll n, c[N][N];
void solve() {
	ll ans = 0, res = 1e9 + 7; cin >> n;
	for(int i = 1; i <= n * 2; i++) for(int j = 1; j <= n * 2; j++)
		cin >> c[i][j], ans += i > n && j > n ? c[i][j] : 0;
	cmin(res, c[n + 1][1]), cmin(res, c[n + 1][n]), cmin(res, c[n << 1][1]), cmin(res, c[n << 1][n]);
	cmin(res, c[1][n + 1]), cmin(res, c[n][n + 1]), cmin(res, c[1][n << 1]), cmin(res, c[n][n << 1]);
	cout << ans + res << endl;
}
int main() {
	int T; cin >> T;
	while(T--) solve();
	return  0;
}
```

---

## 作者：xuyifei0302 (赞：2)

首先，我们要把朋友们安全地移动到右下角 $n ^ 2$ 个格子，那么铲去这 $n ^ 2$ 个格子的积雪所花费的代价是无法避免的。然后我们考虑把朋友们移动到这些格子的路程当中所花费的代价该如何最小。我们可以发现，只要有一个朋友到达右下角 $n ^ 2$ 个格子之一，剩下的朋友可以沿着第一个到达的小朋友所走的路径到达。那么问题就转化为一个朋友从左上角 $n ^ 2$ 个格子中任意一个格子出发，到达右下角 $n ^ 2$ 个格子中的任意一个格子的最小花费。可以发现这个朋友只能从右上角初始格子的四个顶点出发，不然答案会变劣。我们就可以分别讨论他要前往哪一个格子。

让我们来讨论一下：

+ 从坐标为 $(1, 1)$ 的格子出发
  - 向左走一步到达格子 $(1, 2n)$，再向上走一步到达格子 $(2n, 2n)$。
  - 向上走一步到达格子 $(2n, 1)$，再向左走一步到达格子 $(2n, 2n)$。
+ 从坐标为 $(1, n)$ 的格子出发
  - 向右走一步到达格子 $(1 , n + 1)$，再向上走一步到达格子 $(2n, n + 1)$。
  - 向上走一步到达格子 $(2n, n)$，再向右走一步到达格子 $(2n, n + 1)$。
+ 从坐标为 $(n, 1)$ 的格子出发
  - 向左走一步到达格子 $(n, 2n)$，再向下走一步到达格子 $(n + 1, 2n)$。
  - 向下走一步到达格子 $(n + 1, 1)$，再向右走一步到达格子 $(n + 1, 2n)$。
+ 从坐标为 $(n, n)$ 的格子出发
  - 向右走一步到达格子 $(n, n + 1)$，再向下走一步到达格子 $(n + 1, n + 1)$。
  - 向下走一步到达格子 $(n + 1, n)$，再向右走一步到达格子 $(n + 1, n + 1)$。

所以，我们只需计算以上 $8$ 种情况的花费，然后取最小值即可。相当于对格子 $(1, 2n)$、格子 $(2n, 1)$、格子 $(1 , n + 1)$、格子 $(2n, n)$、格子 $(n, 2n)$、格子 $(n + 1, 1)$、格子 $(n, n + 1)$ 和格子 $(n + 1, n)$ 取最小值。然后再加上清理右下角 $n ^ 2$ 个格子的积雪的花费即可。

接下来是代码环节：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, c[505][505], sum;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		sum = 0;
		cin >> n;
		for (int i = 1; i <= n * 2; i ++) {
			for (int j = 1; j <= n * 2; j ++) {
				cin >> c[i][j];
			}
		}
		for (int i = n + 1; i <= n * 2; i ++) {
			for (int j = n + 1; j <= n * 2; j ++) {
				sum += c[i][j];
			}
		}
		sum += min(c[1][n + 1], min(c[1][n * 2], min(c[n + 1][1], min(c[n * 2][1], min(c[n][n + 1], min(c[n][n * 2], min(c[n * 2][n], c[n + 1][n])))))));
		cout << sum << "\n";
	}
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

### Preface

考场上卡到结束的思维题 awa。

不过还是建议难度评 `普及-`。

### Analysis

猜结论：**答案为八个角中值最小的一个。**

其中角为 $(1,n+1),(n,n+1),(1,2n),(n,2n)$ 和她们的对称点（$i.e.\ (x,y)\to(y,x)$）。

首先，只经过八个角中的一个必然满足题意（证明略，类似 Minecraft 中的活塞）。

如果八个角都不经过，则 $(1,1),(1,n),(n,1),(n,n)$ 四个点上的同学被卡住了，都动不了 qwq（类似滑木块游戏）。

综上，结论得证。

### Code

（因为太简短就被略了，若要私信）

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2100}$
---
### 解题思路：

很有种诈骗的味道在。

首先环状的结构不好处理，考虑将其展开，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/j7ixlh79.png)

灰色表示原来的，直接平移而不是翻折过去。

那么题目就转换为各种平移（同原题，没有越界处理）最后让白色区块中的全都到红色中。

可以发现，最后红色区域中的所有雪都是要求清除的，否则连站位置都没有。对于其他的雪，其实只需要清除一块与白色区域的顶点相邻的一块蓝色或者黄色的就行了。

由于不限移动次数，可以直接考虑一点一点慢慢挪过去，具体为先将一行或者一列向空下来的位置平移一个单位，然后将进去的那一个点向红色区域平移直到底，并以此类推。

将几个区块平移回去，结果其实就是黄色和蓝色八个角的权的最小值加上右下角的整个红色块。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int T,n,num[505][505],ans;
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d",&n);
		for(int i=1;i<=2*n;i++)
		for(int j=1;j<=2*n;j++)
		scanf("%I64d",&num[i][j]);
		ans=0;
		for(int i=n+1;i<=2*n;i++)
		for(int j=n+1;j<=n*2;j++)
		ans+=num[i][j];
		ans+=min(num[n+1][1],min(num[n+1][n],min(num[2*n][n],min(num[2*n][1],min(
		num[1][n+1],min(num[1][2*n],min(num[n][2*n],num[n][n+1])))))));
		printf("%I64d\n",ans);
	}
	return 0;
}
```


---

## 作者：清烛 (赞：1)

## Description
~~（想吐槽一下这个题面，真的好长。。）~~

给定 $2n\times 2n$ 的棋盘，初始有 $n^2$ 个人在左上角的 $n\times n$ 正方形内（每个格子里面 $1$ 人）。现要将这 $n^2$ 个人通过如下方式移动到右下角的 $n\times n$ 正方形内（每个格子 $1$ 人）：

- 选定一行，将其里面所有的人循环往左/右移一格。即对于有人的 $(x_0, y)$，我们施变换 $(x_0, y)\to (x_0, y + 1)$ 或 $(x_0, y)\to(x_0, y - 1)$。在 $(x_0, 2n)$ 和 $(x_0, 1)$ 的特判。
- 选定一列，将其里面所有的人循环往上/下移一格。即对于有人的 $(x, y_0)$，我们施变换 $(x, y_0)\to (x + 1, y_0)$ 或 $(x, y_0)\to(x - 1, y_0)$。在 $(2n, y_0)$ 和 $(1, y_0)$ 的特判。

操作可以进行任意次。同时有些格子里面有障碍，人不能经过，除掉 $(x, y)$ 的障碍需要花费 $c_{x, y}$，可除掉的障碍数不限。问最小花费。

## Solution

是一道非常巧妙的构造。

首先我们观察一下，发现右下角的 $n\times n$ 区域是必须除掉的。然后观察一下样例 $3$，发现右下角的权值和为 $12$，说明我们只扣掉了一个多余的 $2$。然后注意到挖掉 $(2, 3)$，$(3, 2)$ 或者 $(1, 4)$ 和 $(4, 1)$ 都是可以的。方案可以自行尝试构造。

然后我们就发现，我们除了右下角的 $n\times n$ 要抠掉，只需要在两块 $n\times n$ 区域四角的**交界格点处抠掉一个点作为入口**就可以了。至于方案构造，就考虑一行行/一列列的移入右下角的区域，可以自行想象一下。这些点一共有 $8$ 个，分别是：

$(1, 2n)$，$(2n, 1)$，$(1, n + 1)$，$(n + 1, 1)$，$(n, n + 1)$，$(n + 1, n)$，$(n, 2n)$，$(2n, n)$。于是这题就做完了。非常妙。

记得开 `ll` 以及数组不要开小了。

```cpp
const int maxn = 512;
using ll = long long;
ll c[maxn][maxn];
int n;

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n << 1) FOR(j, 1, n << 1) read(c[i][j]);
        ll ans = 0;
        FOR(i, n + 1, n << 1)
            FOR(j, n + 1, n << 1)
                ans += c[i][j];
        ans += min(c[n << 1][1], c[1][n << 1], c[n << 1][n], c[n][n << 1], c[1][n + 1], c[n + 1][1], c[n][n + 1], c[n + 1][n]);
        print(ans);
    }
    return output(), 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路

首先一定会过图中的紫色部分。
![](https://cdn.luogu.com.cn/upload/image_hosting/47nz9ltj.png)

如图的紫色线与蓝色线，都是上下左右平移过来的，如果再次上下左右移动一定会经过紫色方块。

![](https://cdn.luogu.com.cn/upload/image_hosting/f2eqzpxg.png)

其次是我们可以只经过一个紫色点。例如左下绿色大块的右下角紫块，先让红色部分竖着的最靠右的向上移动一格，有一个跳到了目标紫色块，再向右移动一格，以此类推，此时红色部分竖着的最靠右的部分移动到了蓝色横向最下面的部分。而左下绿色大块的右上角紫块就是向下一格向左一格，左下绿色大块的左上角紫块就是红色部分竖着的最靠左的向下一格向左一格，左下绿色大块的左下角紫块就是红色部分竖着的最靠左的向上一格向左一格

右上角绿色块同理。

所以最小值就是蓝色部分的总数加上紫色块的最小值。
### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define maxn 300
using namespace std;
int n,ans=0,a[maxn*2][maxn*2];
void todo()
{
	memset(a,0,sizeof a);ans=0,n=0;
	cin>>n;
	for(int i=1;i<=n*2;i++)
		for(int j=1;j<=n*2;j++)
			cin>>a[i][j];
	for(int i=n+1;i<=n*2;i++)
		for(int j=n+1;j<=n*2;j++)
			ans+=a[i][j];
	
	cout<<ans+min(a[1][n+1],min(a[1][n+n],min(a[n][n+1],min(a[n][n+n],min(a[n+1][1],min(a[n+1][n],min(a[n+n][1],a[n+n][n])))))))<<endl;
}

signed main(){int __;cin>>__;while(__--){todo();}return 0;}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1621D 题解



## 思路分析

显然右下部分所有积雪必定清空，而我们注意到如下的观察：

> 对于任何一种操作方案，至少会经过右上部分的四个顶点或左下部分的四个顶点之一。
>
> 假如我们操作左上部分，的第 $1$ 行、第 $n$ 行、第 $1$ 列、第 $n$ 列中的任何一个，左上部分的 $4$ 个端点中必有一个接触到这 $8$ 个顶点之一。

而且我们发现这 $8$ 个顶点都是可以直接到达右下部分的，如下图所示：

[![pSP2x0S.png](https://s1.ax1x.com/2023/01/02/pSP2x0S.png)](https://imgse.com/i/pSP2x0S)

其中红色的边为每个学生走到积雪上的可能路径，而蓝色的边表示从这 $8$ 个特殊格子最终走到右下部分的路径。

因此我们只需要这 $8$ 个格子中 $c$ 值的 $\min$ 加上右下部分 $c$ 值的和即可。

时间复杂度 $\Theta(n^2)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=501,INF=1e18;
int c[MAXN][MAXN],dp[MAXN][MAXN][4];
inline void solve() {
	int n,cost=0;
	scanf("%lld",&n);
	for(int i=1;i<=2*n;++i) {
		for(int j=1;j<=2*n;++j) {
			scanf("%lld",&c[i][j]);
			if(i>n&&j>n) cost+=c[i][j];
		}
	}
	printf("%lld\n",min(min(min(c[1][n+1],c[1][n*2]),min(c[n][n+1],c[n][n*2])),
						min(min(c[n+1][1],c[n+1][n]),min(c[n*2][1],c[n*2][n])))+cost);
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

