# Garden of the Sun

## 题目描述

There are many sunflowers in the Garden of the Sun.

Garden of the Sun is a rectangular table with $ n $ rows and $ m $ columns, where the cells of the table are farmlands. All of the cells grow a sunflower on it. Unfortunately, one night, the lightning stroke some (possibly zero) cells, and sunflowers on those cells were burned into ashes. In other words, those cells struck by the lightning became empty. Magically, any two empty cells have no common points (neither edges nor corners).

Now the owner wants to remove some (possibly zero) sunflowers to reach the following two goals:

- When you are on an empty cell, you can walk to any other empty cell. In other words, those empty cells are connected.
- There is exactly one simple path between any two empty cells. In other words, there is no cycle among the empty cells.

You can walk from an empty cell to another if they share a common edge.

Could you please give the owner a solution that meets all her requirements?

Note that you are not allowed to plant sunflowers. You don't need to minimize the number of sunflowers you remove. It can be shown that the answer always exists.

## 说明/提示

Let's use $ (x,y) $ to describe the cell on $ x $ -th row and $ y $ -th column.

In the following pictures white, yellow, and blue cells stand for the cells that grow a sunflower, the cells lightning stroke, and the cells sunflower on which are removed, respectively.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1495C/6c1f0eba6baaa11b758e7cc9933abfde3f83e428.png)

In the first test case, one possible solution is to remove sunflowers on $ (1,2) $ , $ (2,3) $ and $ (3 ,2) $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1495C/a0b70183d96ea9c228c083ab93b05f1533fd6a98.png)

Another acceptable solution is to remove sunflowers on $ (1,2) $ , $ (2,2) $ and $ (3,2) $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1495C/280c704460a9e38f47a86fc4285daa49bfbd1f1d.png)

This output is considered wrong because there are 2 simple paths between any pair of cells (there is a cycle). For example, there are 2 simple paths between $ (1,1) $ and $ (3,3) $ .

1. $ (1,1)\to (1,2)\to (1,3)\to (2,3)\to (3,3) $
2. $ (1,1)\to (2,1)\to (3,1)\to (3,2)\to (3,3) $

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1495C/b70e5f707d67e6ea976951ebead8241851d9d621.png)

This output is considered wrong because you can't walk from $ (1,1) $ to $ (3,3) $ .

## 样例 #1

### 输入

```
5
3 3
X.X
...
X.X
4 4
....
.X.X
....
.X.X
5 5
.X...
....X
.X...
.....
X.X.X
1 10
....X.X.X.
2 2
..
..```

### 输出

```
XXX
..X
XXX
XXXX
.X.X
.X..
.XXX
.X...
.XXXX
.X...
.X...
XXXXX
XXXXXXXXXX
..
..```

# 题解

## 作者：CSP_Sept (赞：10)

这里是来自 sb 验题人 CSP_Sept 的题解。

___

### Description

不妨将 `X` 当作蓝色，`.` 当作白色，给定一个 $n\times m$ 的格子，网格上本来有一些蓝色的格子，原本蓝色的格子满足：任意两个蓝色的格子，没有相邻的边和顶点，其他的格子都是白色的。

你现在要把一些白色的格子涂成蓝色，使得所有的蓝色格子都连起来，且每个蓝色格子八连通方向和四联通方向都不存在其他蓝色格子。

### Solution

首先注意到，初始情况下可以涂任意一列。

我们先涂满 $1,4,7,\ldots$ 列，可以发现，这样是符合题意的。

然后我们分析第 $i(i\in\{2,5,8,\ldots\})$ 列，按照如下方式染色：

- 若 $(2,i),(2,i+1)$ 中有一个是蓝色的，则两个格子都涂上蓝色。
- 否则把 $(1,i),(1,i+1)$ 涂上蓝色。

注意特判：

- 如果 $i+1=m$ 直接跳过即可。
- 如果 $i+2=m$，则循环一遍 $l(1\le l\le n)$，若 $(l,i+1)$ 是蓝色，则把 $(l,i)$ 也涂成蓝色。

顺便特判一下 $n=1$ 与 $m=1$ 即可。

### Code

[109672479](https://codeforces.com/contest/1496/submission/109672479)

### Digression

这题怎么才 200 多人 A，这不是 strong pretests 吗（

头次当 tester 留念。

---

## 作者：gyh20 (赞：4)

简单构造题。

观察题目中的重要性质，所有空地不存在点相连的情况，也就是说，不会出现如下情况：

```
X.
.X
```

这提示我们以 $3$ 对行分类，填出如下形状：

```
XXXXXXXX
...X..X.
X.......
XXXXXXXX
```

此时，上下两部分一定是分别连通的，只需要找一个位置将上下连起来即可。

```cpp
#include<bits/stdc++.h>
#define re register
//#define int long long
const int M=1e9+7;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[1000002],b[1000002],head[1000002],cnt,A,B,C,D;
struct edge{int to,next;}e[2000002];
inline void addd(re int x,re int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
char s[502][502],ans[502][502];
#define Y puts("YES");
#define N puts("NO");
signed main(){
	t=read();
	while(t--){
		n=read(),m=read();
		for(re int i=1;i<=n;++i)scanf("%s",s[i]+1);
		for(re int i=1;i<=n+1;i++)for(re int j=1;j<=m+1;++j)ans[i][j]=0;
		for(re int i=1;i<=n;++i)for(re int j=1;j<=m;++j)ans[i][j]=s[i][j];
		for(re int i=1;i<=n;i+=3)for(re int j=1;j<=m;++j)ans[i][j]='X';
		for(re int i=1;i<=n;i+=3){
			re int fst=0,tmp=0;
			if(i+2==n){
				for(re int j=1;j<=m;++j)if(ans[i+2][j]=='X')ans[i+1][j]='X';
				break;
			}
			if(i+1==n||i==n)break;
			for(re int j=1;j<=m;++j)
				if(s[i+2][j]=='X'){
					fst=1;
					ans[i+1][j]='X';
					break;
				}
			if(!fst){
			for(re int j=1;j<=m;++j)
				if(s[i+1][j]=='X'){
					fst=1;
					ans[i+2][j]='X';
					break;
				}
			}
			if(!fst){
				ans[i+1][1]=ans[i+2][1]='X';
			}
		}
		for(re int i=1;i<=n;++i)printf("%s\n",ans[i]+1);
	}
}
```


---

## 作者：ChickyHas (赞：2)

很灵机一动的构造题，符合我对简单但又不简单的构造题的理解。

这道题的重点在于弱化这个条件，通过考虑简单的构造方式，也就是别想太复杂。

直接给出想法：隔两行填满一行。

```
XXXXXXXX
....X.X.
.X......
XXXXXXXX
```

我们发现这样没有成环的风险，那么我们只需要连接任意接口处，但记得判断旁边是不是有已经填好的地方。

最后还需要特判最后 2 行，直接往上连即可。

难度不好评价，初三的巨佬 2 分钟秒了，我却 4 分钟都没刻画出来。

---

## 作者：AuCloud (赞：2)

好玩的构造

# 题意

给你一个矩阵，要求在其中加入任意数量的`X`使所有`X`联通且不形成环。

题目保证给出的矩阵中没有相邻的`X`，“相邻”包括公共顶点和公共边

# 题解

挺好玩的一道构造题

~~要不是我回家只剩下 15 分钟做 1C 怎么可能才 2 切![ruo](https://cdn.luogu.com.cn/upload/pic/62238.png)~~

题目没有限制`X`的个数，所以考虑强制让他们连通。

显然最暴力的思想肯定是全变成`X`，但是显然环太多了

考虑隔一行染一次，但是还是会出现环:

```
XXXXXX
..X.X.
XXXXXX

```

再拉开一行，隔两行染一次，这次一定不会出现环，但是不一定联通（~~自行感性理解一下~~）

```
XXXXXX
..X...
X.....
XXXXXX
......
..X.X.
XXXXXX
```

于是下面的事就是让它联通。

显然的，在空着的两行任意连一条线，就会变得联通。

假设我们将所有行数$\mod3=2$的行全部染成`X`，那么所有空行的**上行连接着上一行，下行连接着下一行**，如果将所有这种连通块都连在一起，则整张图就会连通。

问题是如何合法的连上。

第一种方法是把第一列也全部染成`X`，但是在第二列出现`X`时就会出现环，不合法：

```
XXXXXX
X...X.
XX....
XXXXXX
```

题目中保证没有初始的`X`相邻，也就是说如果某行第二个位置出现`X`，则代表这一行和上下两行的第一个位置到第三个位置都不可能有`X`，这个时候直接将第二列连上即可

否则我们连第一列不会不合法，连第一列就行。

于是这题就做完了……

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[505][505];
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int n, m;
		cin >> n >> m;
		for(int i = 1; i <= n; i++)
		{
			cin >> (a[i] + 1);
		}
		if(n == 1)
		{
			for(int i = 1; i <= m; i++) cout << 'X';
			cout << endl;
			continue;
		}
		for(int i = 2; i <= n; i++)
		{
			if(i % 3 == 2)
			{
				for(int j = 1; j <= m; j++) a[i][j] = 'X';
			}
			else if(i % 3 == 1 && a[i][2] != 'X' && a[i - 1][2] != 'X') a[i][1] = a[i - 1][1] = 'X';
			else if(i % 3 == 1)a[i][2] = a[i - 1][2] = 'X';
		}
		if(n % 3 == 1) for(int i = 1; i <= m; i++) if(a[n][i] == 'X' && a[n][i - 1] != 'X')a[n - 1][i] = 'X';
		for(int i = 1; i <= n; i++) printf("%s\n", a[i] + 1);
	}
}

```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1495C 题解



## 思路分析

首先考虑的思路应该是对于奇数行都全部变成 `X`，偶数行就自动和上下的奇数行连接，但是这样可能会形成多个环。

一个比较自然的思路是按行号 $\bmod 3$ 来讨论，对于第 $3i+1$ 行全部变成 `X`，这样第 $3i+2$ 行和 $3i+3$ 行就会分别与第 $3i+1$ 行和第 $3(i+1)+1$ 行相连，那么我们只需要找到一种合适的方式连接 $3i+1$ 行和 $3(i+1)+1$ 行。

注意到任意一个 `X` 周围 $8$ 个位置都是 `.`，因此对于某个在 $(3i+2,j)$ 上的 `X`，$(3i+3,j-1)$ 和 $(3i+3,j+1)$ 都是 `.`，因此我们直接把 $(3i+3,j)$ 变成 `X`，能连通第 $3i+1$ 行和 $3(i+1)+1$ 行而不产生环，对于某个坐标为 $(3i+3,j)$ 的 `X` 也一样，把 $(3i+2,j)$ 变成 `X` 即可。

假如不存在这样的 $j$，那么第 $3i+2$ 和 $3i+3$ 行应该全都是 `.`，那么任取同一列的两个位置变成 `X` 即可。

注意一个需要特判的边界情况：若 $n\bmod 3=0$，那么第 $n$ 行的每个 `X` 都是独立的，其间两两都不联通，因此对于每个为 `X` 的 $(n,j)$，把 $(n-1,j)$ 变成 `X` 即可。

时间复杂度 $\Theta(nm)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=501;
char a[MAXN][MAXN];
inline void solve() {
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i+=3) {
		for(int j=1;j<=m;++j) a[i][j]='X';
		if(i==n||i+1==n) break;
		if(i+2==n) {
			for(int j=1;j<=m;++j) if(a[i+2][j]=='X') a[i+1][j]='X';
			break;
		}
		for(int j=1;j<=m;++j) {
			if(a[i+1][j]=='X'||a[i+2][j]=='X') {
				a[i+1][j]=a[i+2][j]='X';
				goto Connected;
			}
		}
		a[i+1][1]=a[i+2][1]='X';
		Connected:;
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			cout<<a[i][j];
		}
		cout<<"\n";
	}
}
signed main() {
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```



---

## 作者：FiraCode (赞：0)

## 题解思路：
我们就第一行全填上 `X`，
第二行让 `X` 联通，
第三行全填 `X`。

这样我们会发现每 $3$ 个一个周期。

但题目给出了在一个 `X` 的八个方向上是没有 `X` 的。

有了这个条件后，那么我们填好后，那么每三个就是一个连通块。

但上下之间没有贯穿。

若原来有 `X` 就选最少的就可以了，若原来没有 `X`，那么就随便开出一条就可以了。

**注意：最后一行直接打穿上去就行了。**

## AC CODE:
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 510;
int T;
char a[N][N]; 
int main() {
    scanf ("%d" , &T);
    while (T --) {
        int n , m;
        scanf ("%d%d" , &n , &m);
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < m; ++ j)
				cin >> a[i][j];
		for (int i = 0; i < n; ++ i) {
			bool ok = true;
			for (int j = 0; j < m; ++ j) {
				if (i % 3 == 0) {//是三的倍数的行，就把他填成X 
					a[i][j] = 'X';
					if (ok && a[i - 1][j] == 'X'){//把他从上面连上，变联通 
						a[i - 1][j] = a[i - 2][j] = 'X';
						ok = false;
					}
					if (ok && i > 1 && a[i - 2][j] == 'X') {//同上 
						a[i - 1][j] = a[i - 2][j] = 'X';
						ok = false;
					} 
				}else if (i == n - 1) {
					if (a[i][j] == 'X')//最后一行的情况 
						if (i > 0)
							a[i - 1][j] = 'X';
				}
			}
			if (ok && i % 3 == 0 && i > 0) {//其他地方没有X随便建一条。
				a[i - 1][0] = a[i - 2][0] = 'X'; 
			}
		}
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < m; ++ j)
				cout << a[i][j];
			puts("");
		}
	}
    return 0;
}
```

---

## 作者：清烛 (赞：0)

[My blog](https://imyangty.com/oi/1324)

### 题意
给定一个 $n\times m$ 矩阵，里面含有字符 `.` 和 `X`。保证所有 `X` 之间无公共点（即不联通），请将一部分 `.` 替换成 `X` 使得这些 `X` 形成一棵树（要求四联通，即两个 `X` 之间有一公共边，不能有环）

### 题解
一道构造题。

首先**所有 `X` 之间无公共点**是一个特别好的性质，这保证了下面填充列的方法的正确性。

具体地，考虑 $3\mid m$ 的情况，不妨直接将 $2,5,8,\cdots$ 列全部填成 `X`，不难发现这样**隔两列填一列的方式是不会出现环的**，然后再将 $3, 6, 9, \cdots$ 和 $4,7,10,\cdots$ 等列构造成联通的就可以了，最简单的方法就是只考虑第一行和第二行，如果合法就直接连。

如果 $3\not| m$，那么只需要变一下，把 $1, 4, 7,\cdots$ 填成 `X`，剩余操作类似。至于为什么填的列改变了则可以考虑画一下图自己模拟一下，会发现如果选 $2, 5, 8,\cdots$ 的话在 $m = 3k + 1$ 的时候会多出一个需要单独考虑的列，所以不如简化问题。

代码如下：

```cpp
#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 505;
char s[maxn][maxn];
int n, m;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &m);
        FOR(i, 1, n)
            scanf("%s", s[i] + 1);
        for (int j = 1 + (m % 3 == 0); j <= m;)
        {
            FOR(i, 1, n)
                s[i][j] = 'X';//直接全部赋值
            j += 3;
            if (j > m) break;
            int p = 2;//进行操作的行号
            if (n == 1 || (s[2][j - 1] != 'X' && s[2][j - 2] != 'X'))//如果第二不可以操作
                p = 1;//那就操作第一行
            s[p][j - 1] = s[p][j - 2] = 'X';//联通
        }
        FOR(i, 1, n)
            puts(s[i] + 1);
    }
    return 0;
}
```

---

## 作者：xuyifei0302 (赞：0)

首先我们注意到我们不需要保证操作数的最小化，所以我们可以将能移走的向日葵全部移走。我们可以先把奇数排全部移走。但是偶数排有可能会有两个及以上的空地，所以我们考虑用并查集来维护，对于奇数排我们要移走的格子，它的上面一个格子和左右的格子必须不在同一个连通块内。然后考虑把没有相连的连通块通过偶数排的格子连起来。

我们奇数排要讨论两次，第一次只将四周至少有一个格子是空格的格子移走。第二次再把奇数排全部连通，不然会出现不连通的错解。

然后模拟即可。

接下来是代码环节：


```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node {
	int x, y;
} f[705][705];
int t, n, m;
bool mp[705][705];
string s;
Node get_father(int x, int y) {
	if (f[x][y].x == x && f[x][y].y == y) {
		return f[x][y];
	} else {
		f[x][y] = get_father(f[x][y].x, f[x][y].y);
		return f[x][y];
	}
}
bool check(Node x, Node y) {
	return (x.x == y.x && x.y == y.y);
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		cin >> n >> m;
		for (int i = 1; i <= n; i ++) {
			cin >> s;
			s = " " + s;
			for (int j = 1; j <= m; j ++) {
				if (s[j] == 'X') {
					mp[i][j] = true;
				}
			}
		}
		for (int i = 0; i <= n + 5; i ++) {
			for (int j = 0; j <= m + 5; j ++) {
				f[i][j].x = i, f[i][j].y = j;
			}
		}
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= m; j ++) {
				if (mp[i][j]) {
					if (mp[i - 1][j]) {
						Node fx = get_father(i - 1, j), fy = get_father(i, j);
						if (!check(fx, fy)) {
							f[fx.x][fx.y] = fy;
						}
					}
					if (mp[i][j - 1]) {
						Node fx = get_father(i, j - 1), fy = get_father(i, j);
						if (!check(fx, fy)) {
							f[fx.x][fx.y] = fy;
						}
					}
					if (mp[i + 1][j]) {
						Node fx = get_father(i + 1, j), fy = get_father(i, j);
						if (!check(fx, fy)) {
							f[fx.x][fx.y] = fy;
						}
					}
					if (mp[i][j + 1]) {
						Node fx = get_father(i, j + 1), fy = get_father(i, j);
						if (!check(fx, fy)) {
							f[fx.x][fx.y] = fy;
						}
					}
				}
			}
		}
		for (int i = 1; i <= n; i += 2) {
			for (int j = 1; j <= m; j ++) {
				if (!mp[i][j]) {
					Node fnow = get_father(i, j);
					Node fu = get_father(i + 1, j), fd = get_father(i - 1, j), fl = get_father(i, j - 1), fr = get_father(i, j + 1);
					if (mp[i + 1][j] && mp[i - 1][j] && mp[i][j + 1] && mp[i][j - 1]) {
						if (!check(fu, fd) && !check(fu, fl) && !check(fu, fr) && !check(fd, fl) && !check(fd, fr) && !check(fl, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j + 1] && mp[i - 1][j]) {
						if (!check(fu, fd) && !check(fu, fr) && !check(fd, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j + 1] && mp[i][j - 1]) {
						if (!check(fu, fl) && !check(fu, fr) && !check(fl, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fr.x][fr.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i - 1][j] && mp[i][j - 1]) {
						if (!check(fu, fd) && !check(fu, fl) && !check(fd, fl)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i][j + 1] && mp[i - 1][j] && mp[i][j - 1]) {
						if (!check(fd, fl) && !check(fd, fr) && !check(fl, fr)) {
							mp[i][j] = true;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j + 1]) {
						if (!check(fu, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j - 1]) {
						if (!check(fu, fl)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i - 1][j] && mp[i][j - 1]) {
						if (!check(fd, fl)) {
							mp[i][j] = true;
							f[fd.x][fd.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i - 1][j] && mp[i][j + 1]) {
						if (!check(fd, fr)) {
							mp[i][j] = true;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i - 1][j]) {
						if (!check(fu, fd)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
						}
					} else if (mp[i][j + 1] && mp[i][j - 1]) {
						if (!check(fl, fr)) {
							mp[i][j] = true;
							f[fl.x][fl.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i + 1][j]) {
						mp[i][j] = true;
						f[fu.x][fu.y] = fnow;
					} else if (mp[i - 1][j]) {
						mp[i][j] = true;
						f[fd.x][fd.y] = fnow;
					}
					else if (mp[i][j + 1]) {
						mp[i][j] = true;
						f[fr.x][fr.y] = fnow;
					}
				}
			}
		}
		for (int i = 1; i <= n; i += 2) {
			for (int j = 1; j <= m; j ++) {
				if (!mp[i][j]) {
					Node fnow = get_father(i, j);
					Node fu = get_father(i + 1, j), fd = get_father(i - 1, j), fl = get_father(i, j - 1), fr = get_father(i, j + 1);
					if (mp[i + 1][j] && mp[i - 1][j] && mp[i][j + 1] && mp[i][j - 1]) {
						if (!check(fu, fd) && !check(fu, fl) && !check(fu, fr) && !check(fd, fl) && !check(fd, fr) && !check(fl, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j + 1] && mp[i - 1][j]) {
						if (!check(fu, fd) && !check(fu, fr) && !check(fd, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j + 1] && mp[i][j - 1]) {
						if (!check(fu, fl) && !check(fu, fr) && !check(fl, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fr.x][fr.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i - 1][j] && mp[i][j - 1]) {
						if (!check(fu, fd) && !check(fu, fl) && !check(fd, fl)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i][j + 1] && mp[i - 1][j] && mp[i][j - 1]) {
						if (!check(fd, fl) && !check(fd, fr) && !check(fl, fr)) {
							mp[i][j] = true;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j + 1]) {
						if (!check(fu, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j - 1]) {
						if (!check(fu, fl)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i - 1][j] && mp[i][j - 1]) {
						if (!check(fd, fl)) {
							mp[i][j] = true;
							f[fd.x][fd.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i - 1][j] && mp[i][j + 1]) {
						if (!check(fd, fr)) {
							mp[i][j] = true;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i - 1][j]) {
						if (!check(fu, fd)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
						}
					} else if (mp[i][j + 1] && mp[i][j - 1]) {
						if (!check(fl, fr)) {
							mp[i][j] = true;
							f[fl.x][fl.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i][j - 1]) {
						mp[i][j] = true;
						f[fl.x][fl.y] = fnow;
					} else if (mp[i + 1][j]) {
						mp[i][j] = true;
						f[fu.x][fu.y] = fnow;
					} else if (mp[i - 1][j]) {
						mp[i][j] = true;
						f[fd.x][fd.y] = fnow;
					} else if (mp[i][j + 1]) {
						mp[i][j] = true;
						f[fr.x][fr.y] = fnow;
					} else {
						mp[i][j] = true;
					}
				}
			}
		}
		for (int i = 2; i <= n; i += 2) {
			for (int j = 1; j <= m; j ++) {
				if (!mp[i][j]) {
					Node fnow = get_father(i, j);
					Node fu = get_father(i + 1, j), fd = get_father(i - 1, j), fl = get_father(i, j - 1), fr = get_father(i, j + 1);
					if (mp[i + 1][j] && mp[i - 1][j] && mp[i][j + 1] && mp[i][j - 1]) {
						if (!check(fu, fd) && !check(fu, fl) && !check(fu, fr) && !check(fd, fl) && !check(fd, fr) && !check(fl, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j + 1] && mp[i - 1][j]) {
						if (!check(fu, fd) && !check(fu, fr) && !check(fd, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j + 1] && mp[i][j - 1]) {
						if (!check(fu, fl) && !check(fu, fr) && !check(fl, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fr.x][fr.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i - 1][j] && mp[i][j - 1]) {
						if (!check(fu, fd) && !check(fu, fl) && !check(fd, fl)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i][j + 1] && mp[i - 1][j] && mp[i][j - 1]) {
						if (!check(fd, fl) && !check(fd, fr) && !check(fl, fr)) {
							mp[i][j] = true;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j + 1]) {
						if (!check(fu, fr)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i][j - 1]) {
						if (!check(fu, fl)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i - 1][j] && mp[i][j - 1]) {
						if (!check(fd, fl)) {
							mp[i][j] = true;
							f[fd.x][fd.y] = fnow;
							f[fl.x][fl.y] = fnow;
						}
					} else if (mp[i - 1][j] && mp[i][j + 1]) {
						if (!check(fd, fr)) {
							mp[i][j] = true;
							f[fd.x][fd.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i + 1][j] && mp[i - 1][j]) {
						if (!check(fu, fd)) {
							mp[i][j] = true;
							f[fu.x][fu.y] = fnow;
							f[fd.x][fd.y] = fnow;
						}
					} else if (mp[i][j + 1] && mp[i][j - 1]) {
						if (!check(fl, fr)) {
							mp[i][j] = true;
							f[fl.x][fl.y] = fnow;
							f[fr.x][fr.y] = fnow;
						}
					} else if (mp[i][j - 1]) {
						mp[i][j] = true;
						f[fl.x][fl.y] = fnow;
					} else if (mp[i + 1][j]) {
						mp[i][j] = true;
						f[fu.x][fu.y] = fnow;
					} else if (mp[i - 1][j]) {
						mp[i][j] = true;
						f[fd.x][fd.y] = fnow;
					} else if (mp[i][j + 1]) {
						mp[i][j] = true;
						f[fr.x][fr.y] = fnow;
					}
				}
			}
		}
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= m; j ++) {
				if (mp[i][j]) {
					cout << "X";
				} else {
					cout << ".";
				}
			}
			cout << "\n";
		}
		cout << "\n";
		for (int i = 0; i <= n + 5; i ++) {
			for (int j = 0; j <= m + 5; j ++) {
				mp[i][j] = false;
			}
		}
	}
	return 0;
}
```

---

