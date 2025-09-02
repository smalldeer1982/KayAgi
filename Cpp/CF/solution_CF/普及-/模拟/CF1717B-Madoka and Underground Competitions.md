# Madoka and Underground Competitions

## 题目描述

Madoka decided to participate in an underground sports programming competition. And there was exactly one task in it:

A square table of size $ n \times n $ , where  $ n $ is a multiple of $ k $ , is called good if only the characters '.' and 'X' are written in it, as well as in any subtable of size $ 1 \times k $ or $ k \times 1 $ , there is at least one character 'X'. In other words, among any $ k $ consecutive vertical or horizontal cells, there must be at least one containing the character 'X'.

Output any good table that has the minimum possible number of characters 'X', and also the symbol 'X' is written in the cell $ (r, c) $ . Rows are numbered from $ 1 $ to $ n $ from top to bottom, columns are numbered from $ 1 $ to $ n $ from left to right.

## 说明/提示

Let's analyze the first test case.

The following tables can be printed as the correct answer:

 X....X.X. or ..XX...X. It can be proved that there cannot be less than $ 3 $ characters 'X' in the answer.Note that the following table is invalid because cell $ (3, 2) $ does not contain the character 'X':

 X...X...XIn the second test case, the only correct table is:

 XXXX Each subtable of size $ 1 \times 1 $ must contain a 'X' character, so all characters in the table must be equal to 'X'.

## 样例 #1

### 输入

```
3
3 3 3 2
2 1 1 2
6 3 4 2```

### 输出

```
X..
..X
.X.
XX
XX
.X..X.
X..X..
..X..X
.X..X.
X..X..
..X..X```

# 题解

## 作者：weizhiyonghu (赞：5)

# CF1717B solution
## 思路
题目中有一个关键条件： $k \mid n$ .这告诉我们在所有的数据中，每行每列都能出现完整的**循环节**。因此，可以考虑对给出的 $(r,c)$ 坐标进行偏移。

首先，找出 $(r,c)$ 在行内循环节中的相对位置 $c \equiv c' \pmod k$ ，然后在行内的每一个满足 $x \equiv c' \pmod k$ 的 $x$ 位置输出 `X` 。

再来分析列上的偏移：这个也很好做。只要把当前行与目标行 $r$ 的距离当作偏移量(记得模上 $k$ )，再输出就行了。

```cpp
#include <iostream>
#include <string.h>
#include <cstring>

using namespace std;
int n,k,r,c,T;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k);
		scanf("%d%d",&r,&c);
		int x = c % k;x = (x+1+n-r)%k;
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++)
				if(j % k == x) printf("X");
				else printf(".");
			printf("\n");x = (x + 1) % k;
		}
	}
	return 0;
}
```

---

## 作者：Jasper08 (赞：4)

很简单的一道题，依题意模拟即可。

首先在 $(r,c)$ 的位置放上一个 X，然后分别向上、向下遍历。若第 $i$ 行在第 $r$ 行上方，显然在 $(i,c+r-i)$ 的位置应该有一个 `X`；若第 $i$ 行在第 $r$ 行下方，显然在 $(i,c-i+r)$ 的位置应该有一个 `X`（数组开大，不用担心越界的问题）。对于每一行，从 `X` 的位置分别向左、向右填，每隔 $k-1$ 个数放上一个 `X` 即可。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1010;

int t, n, k, r, c;
char ans[N][N];

int main() {
	scanf("%d", &t);
	while (t -- ) {
		scanf("%d%d%d%d", &n, &k, &r, &c);
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) ans[i][j] = '.';
		
		ans[r][c] = 'X';
		for (int i = c; i >= 1; i -= k) ans[r][i] = 'X'; //填充第r行左侧
		for (int i = c; i <= n; i += k) ans[r][i] = 'X'; //填充第r行右侧
		for (int i = r-1; i >= 1; --i) {
			ans[i][c+r-i] = 'X'; //填充第r行上方的行
			for (int j = c+r-i; j >= 1; j -= k) ans[i][j] = 'X';
			for (int j = c+r-i; j <= n; j += k) ans[i][j] = 'X';
		}
		for (int i = r+1; i <= n; ++i) { //填充第r行下方的行
			ans[i][c-i+r] = 'X';
			for (int j = c-i+r; j >= 1; j -= k) ans[i][j] = 'X';
			for (int j = c-i+r; j <= n; j += k) ans[i][j] = 'X';
		}
		
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) cout << ans[i][j];
			cout << endl;
		}
	}
	return 0;
}
```

---

## 作者：ioker (赞：2)

题解区没看到我的做法

如果知道一列中的任意一个位置有 $\text{x}$ 那么可以确定这一行、列所有 $\text{x}$，即从 $(x,y)$ 扩展到 $(x\pm k,y\pm k)$，那么如何从一列扩展到下一列？

观察样例想到可以从 $(x,y)$ 扩展到 $(x+1,y+1)$，不与 $(x,y)$ 在同一行。

参考代码

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool v[505][505];
int r,k,sx,sy;
void bfs(){
	queue<pair<int,int> > q;
	q.push(make_pair(sx,sy));
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;q.pop();
		if(x<1||y<1||x>r||y>r)continue;
		if(v[x][y])continue;
		v[x][y]=1;
		q.push(make_pair(x%r+1,y%r+1));
		q.push(make_pair(x,y+k));
		q.push(make_pair(x,y-k));
		q.push(make_pair(x+k,y));
		q.push(make_pair(x-k,y));
	}
}
int zero(){
	cin>>t;
	while(t--){
		memset(v,0,sizeof(v));
        cin>>r>>k>>sx>sy;
		bfs();
		for(int i=1;i<=r;i++,cout<<'\n')for(int j=1;j<=r;j++)cout<<(v[i][j]?'X':'.');
	}
	return 0;
}
signed main() {return zero();}
```

---

## 作者：Acerkaio (赞：2)

哈哈哈哈，水题！

### 题目简述：

一个只由 $\verb!X!$ 和 $\verb!.!$ 组成的 $n \times n$ 矩阵，在 $r$ 行 $c$ 列有一个 $\verb!X!$，且这个矩阵每一个 $1 \times k$ 或 $k \times 1$ 的子矩阵至少有一个 $\verb!X!$，求 $\verb!X!$ 最少时的矩阵。

### 大致思路：

从 $r$ 行 $c$ 列的那个 $\verb!X!$ 分别向上和向下标记 $\verb!X!$，因为这个矩阵每一个 $1 \times k$ 或 $k \times 1$ 的子矩阵至少有一个 $\verb!X!$，所以我们只需要每次标记上一个标记的 $\verb!X!$ 的横坐标 $+k$ 或者 $-k$，不足加减换行处理一下就好了。

### CODE：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
	int n = 0, m = 1;
	char a = getchar();
	while (!isdigit(a)) {
		if (a == '-') {
			m = -1;
		}
		a = getchar();
	}
	while (isdigit(a)) {
		n = (n << 3) + (n << 1) + (a - '0');
		a = getchar();
	}
	return n * m;
}
char a[5005][5005];
signed main() {
	int t = read();
	while (t--) {
		int n = read(), k = read(), r = read(), c = read();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				a[i][j] = '.';
		queue < pair<int, int> > q;
		q.push(make_pair(r, c));
		while (!q.empty()) {
			int x = q.front().first, y = q.front().second;
			q.pop();
			if (x > n)
				break;
			a[x][y] = 'X';
			int x2 = x, y2 = y;
			if (y2 + k > n) {
				y2 = (y2 + k) % n - 1;
				x2++;
			} else {
				y2 += k;
			}
			q.push(make_pair(x2, y2));
		}
		q.pop();
		queue < pair<int, int> > qu;
		qu.push(make_pair(r, c));
		while (!q.empty()) {
			int x = qu.front().first, y = qu.front().second;
			//cout << x << " " << y << '\n';
			qu.pop();
			a[x][y] = 'X';
			if (x < 1)
				break;
			int x2 = x, y2 = y;
			if (y2 - k < 1) {
				y2 = n + (y2 - k) + 1;
				x2--;
			} else {
				y2 -= k;
			}
			qu.push(make_pair(x2, y2));
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				cout << a[i][j];
			cout << '\n';
		}
	}
	return 0;
}
```


---

## 作者：kaceqwq (赞：1)

# 题目大意：
有 $t$ 组数据，每组有 $n$ ，$k$ ，$r$ ，$c$ ，表示让你构造一个 $n \times n$ 的仅由`X`和`.`组成的矩阵，其中保证第 $r$ 行，第 $c$ 列是 `X`，并且要求每个 $1 \times k$ 或 $k \times 1$ 的子序列包含至少一个`X`，现要求`X`的数量最少，求构造好的矩阵。

# 分析：
本题其实比较简单，使用深搜跑一遍即可。具体思路是这样，首先题目给出了一个确定的`X`的位置，我们就以它作为搜索的起点，向上，下，左，右四个方向搜索 $k$ 格，使其由`.`变为`X`，因为要求 $1 \times k$ 或 $k \times 1$ 的子序列包含至少一个`X`，并且要使`X`的数量最少，也就是说每两个`X`之间隔 $k - 1$ 格即可。一直到无法再搜索时，这时我们从当前位置的右下方（右上方也行）一格重新开始搜索，因为这样的话就可以避免再次搜索的点在原先 $1 \times k$ 或 $k \times 1$ 的区域内，如图：

![](https://s1.ax1x.com/2022/09/09/vL1vM8.png)

接着如果新点超出了 $n$ 的范围，让它 x 坐标或 y 坐标变为 $1$ ，然后搜索。搜索过程中可以用记忆化优化，最后输出搜索后的矩阵即可。

# Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k, r, c;
char a[5005][5005];
bool v[5005][5005];
void dfs (int x, int y) {	
	if (x <= 0 || x > n || y <= 0 || y > n) return ; // 边界
	if (v[x][y]) return ; //记忆化
	v[x][y] = 1;
	a[x][y] = 'X';   //更新为 X
	dfs (x % n + 1,y % n + 1);  //如果超过边界，坐标变为1，否则直接加1即可
	dfs (x + k, y);   //四个方向进行搜索
	dfs (x - k, y);
	dfs (x, y + k);
	dfs (x, y - k);
}
int main() {
	cin >> t;
	while (t--) {
		memset (v ,0 , sizeof (v));  //注意要清空记忆化数组
		cin >> n >> k >> r >> c; 
        for (int i = 1; i <= n; i++)  //初始化
			for (int j = 1; j <= n; j++) 
				 a[i][j] = '.';
		dfs (r, c);  //搜索
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				cout << a[i][j];
		cout << '\n';
		}
	} 
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

## 题意简述

有 $t$（$1 \leq t \leq 100$）组测试数据。

对于每一组测试数据，给你 $4$ 个整数 $n$, $k$, $r$, $c$（$1 \leq n, k \leq 100$, $1 \leq r, c \leq n$，$\sum_{}n \leq 500$）。

图的大小为 $n \times n$，初始值为一个英文句点。你可以在任意位置放置任意个 X，使得在每一个的 $1 \times k$ 和 $k \times 1$ 的矩形中，至少有一个 X，并且要求位置 $(r,c)$ 上的符号必须为 X。

输出满足要求的任意一种方案。

## 题目分析

我们 ~~观察样例~~ 可以发现，答案似乎像是一个图表，你只需要不停的滚动，检查 $(r,c)$ 的位置是不是 X 就行了。

例如 $n=10$，$k=3$，$r=3$，$c=3$，那么我们的初始图就是这样：

```
X..X..X..X
..X..X..X.
.X..X..X..
X..X..X..X
..X..X..X.
.X..X..X..
X..X..X..X
..X..X..X.
.X..X..X..
X..X..X..X
```

我们可以发现，横排每两个 X 之间相隔的距离就是 $k$。

但是当前 $(3, 3)$ 不为 X，那么我们就需要往右下角滚动：

```
.X..X..X..
X..X..X..X
..X..X..X.
.X..X..X..
X..X..X..X
..X..X..X.
.X..X..X..
X..X..X..X
..X..X..X.
.X..X..X..
```

这下答案就合法了。

关于「滚动」的实现，你可以枚举第一行的第一个 X 的纵坐标，从 $1$ 枚举到 $k$，接着依次判断合法即可。

明显滚动一次的时间复杂度为 $O(n^2)$，枚举起点的复杂度为 $O(k)$，所以对于每一组的测试用例的时间复杂度为 $O(k \times n^2)$，可以通过。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[1200][1200];

void fill(int k, int s) {
	memset(a, 0, sizeof(a));
	for (int j = s; j <= 1100; j += k) {
		for (int i = 1; i <= 1100; i++) {
			if (j >= i) a[i][j - i + 1] = 1;
			else break;
		}
	}
}

void print(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) cout << (a[i][j] ? 'X' : '.');
		cout << endl;
	}
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, k, r, c;
		cin >> n >> k >> r >> c;
		for (int s = 1; s <= k + 1; s++) {
			fill(k, s);
			if (a[r][c]) {
				print(n);
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1717B 题解



## 思路分析

设 $m=n\div k$。

首先解决 $1\times n$ 的情况，不难发现如果将一个 $1\times n$ 的网格拆成 $m$ 个 $1\times k$ 的网格，显然，每个网格至少需要一个 `X`，此时如果这 $m$ 个网格中 `X` 的相对位置都相同，则拼起来的 $1\times n$ 的网格满足要求，可以证明，此时需要 $m$ 个 `X` 的方案是最优的。

因此类似 $1\times n$ 的情况，我们把 $n\times n$ 的网格拆成 $m\times m$ 个 $k\times k$ 的网格，每个 $k\times k$ 网格中要满足每行每列至少一个 `X` ，显然选择其中一条对角线满足条件，同样，可以证明这个花费为 $m^2k$ 的方案是最优的。

接下来考虑把 $(r,c)$ 这个位置赋成 `X`，首先求出这个位置在其所属的 $k\times k$ 网格中的位置 $(r',c')$，不难发现，我们只需要把 $(r',r'),(c',c')$ 两个位置填成 `.`，把 $(r',c'),(c',r')$ 填成 `X` 即可，由于没有额外添加 `X`，因此这个解一定是最优的。

时间复杂度 $\Theta(n^2)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=501;
char unit[MAXN][MAXN];
inline void solve() {
	int n,k,r,c;
	scanf("%d%d%d%d",&n,&k,&r,&c);
	r=(r-1)%k,c=(c-1)%k;
	for(int i=0;i<k;++i) for(int j=0;j<k;++j) unit[i][j]='.';
	unit[r][c]=unit[c][r]='X';
	for(int i=0;i<k;++i) if(i!=r&&i!=c) unit[i][i]='X';
	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			putchar(unit[i%k][j%k]);
		}
		putchar('\n');
	}
	return ;
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：stntn (赞：0)

## 简要题意

[描述够简单了](https://www.luogu.com.cn/problem/CF1717B)。

## 构造

首先，由题可知 $n$ 是 $k$ 的倍数，所以我们可以把整个图划分成 $(\frac{n}{k})\times(\frac{n}{k})$ 块，每块为一个 $k \times k$ 的正方形，对于每一块，显然只需要最多填 $k$ 位置即可使其满足条件。

而如果每一块都刚好满足条件，将其复制粘贴以填满整张图，整张图也会满足条件（建议自己画一下）。

具体地，若不考虑 $r$ 和 $c$，我们总可以找到一种方法，使得每一行每一列均有且只有一个格子被填上，比如一条对角线解决这个小块：

```
X...
.X..
..X.
...X
```

由于有 $r$ 和 $c$ 的限制，我们先把该限制做如下转变：

```cpp
nowr=(r-1)%k+1;
nowc=(c-1)%k+1;
```

此时 $nowr,nowc\le k$。同上文所说，只有填上当前的 $(nowr,nowc)$，才会在复制粘贴后满足 $(r,c)$ 被填上。 

此时情况是这样：

```
....
....
.X..
....
```

同上，在每行每列最多只填入一个 X，随便填就行了。最后再复制粘贴 $(\frac{n}{k})\times(\frac{n}{k})$ 次。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 1010
#define int long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define tep(i,u) for(int i=head[u];~i;i=e[i].nxt)
#define INF 0x3f3f3f3f
#define pir pair<int,int>
#define mp(i,j) make_pair(i,j)
#define fi first
#define se second
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline void read(T &x,Args &...args){read(x);read(args...);}
int T,n,k,r,c;
bool ans[N][N];
signed main()
{
	read(T);
	while(T--)
	{
		read(n,k,r,c);
		r=(r-1)%k+1;
		c=(c-1)%k+1;
		rep(i,1,k) rep(j,1,k) ans[i][j]=0;
		ans[r][c]=1;
		for(int i=1;r+i<=k;i++) ans[r+i][(c+i-1)%k+1]=1;
		for(int i=1;r-i>=1;i++) ans[r-i][(c-i+k-1)%k+1]=1;
		rep(i,1,n)
		{
			rep(j,1,n) printf("%c",ans[(i-1)%k+1][(j-1)%k+1] ? 'X' : '.');
			printf("\n");
		}
	}
}
```

其实还可以直接画斜线（写题解的时候才发现之前把简单题想复杂了），先在 $(r,c)$，处画一条斜线，然后每隔 $k$ 列再画一条。

如（$k=3$）：

```
...X.	...X.	X..X.
.....	....X	.X..X
.....	.....	..X..
.....	.....	X..X.
.....	.....	.X..X
```

代码就不写了。

---

## 作者：lrqlrq250 (赞：0)

## 解题思路
一眼看上去可能比较难想，因此我们可以先分析样例。

通过样例可以很明显看出两个特点：

1. 要求输出的 $n \times n$ 的矩阵一定是由若干个**完全相同**的 $k \times k$ 的子矩阵组成的。

1. 在每个 $k \times k$ 的子矩阵中，每一行和上一行都类似滚动的关系。

所以想要直接构造这样一个矩阵就很简单了。

我们现在再考虑如何加入“位于 $(r, c)$ 位置上的一定是字母 X”这一条件。

很容易想到对于该位置所在的子矩阵，我们要让字母 X 位于这一个矩阵这一行中的特定位置，剩下的位置都为空。

因此这个 $k \times k$ 矩阵的一行就确定了。通过我们上面发现的第二个特点，整个子矩阵就这样确定了。

总体在运算上的时间复杂度为 $O(TK^2)$，而题解区现有的大部分都是 $O(TN^2)$（虽然我这个好像反而跑的比较慢？）。

不过总的时间复杂度依然是 $O(TN^2)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
char mp[501][501];

int main(){
	int t, n, k, r, c;
	scanf("%d", &t);
	while (t--){
		scanf("%d%d%d%d", &n, &k, &r, &c);
		memset(mp, '.', sizeof(mp));
		int x = (r - 1) % k + 1, y = (c - 1) % k + 1;
		for (int i=1; i<=k; i++){
			mp[x++][y--] = 'X';
			if (x > k) x = 1;
			if (!y) y = k;
		}
		for (int i=1; i<=n; i++, printf("\n")) for (int j=1; j<=n; j++) printf("%c", mp[(i - 1) % k + 1][(j - 1) % k + 1]);
	}
	return 0;
}

```


---

## 作者：Texas_the_Omertosa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1717B)

### 0x01 思路

这题数据范围够小，足够我们暴力构造（转了一圈就我一个暴力成这样子的，而且这个代码还能优化，可是我水平低啊 QAQ）。

这题唯一需要说明的是没有被初始化行的处理。没有被初始化说明有一些列在两个隔了 $k-1$ 行的 `X` 之间，所以必须处理。在两个隔了 $k-1$ 行的 `X` 之间的列的特征为所在列数减去 $c$ 刚好是 $k$ 的倍数，循环判断就可以了。

### 0x02 AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 505
#define M 100005
#define mod 1000000007
#define ios ios::sync_with_stdio(0);cin.tie(0);
#define inf LLONG_MAX
#define pint pair<int,int>
#define mp make_pair
using namespace std;
int n, k, r, c;
char a[N][N];
inline bool check(int tot)
{
	for (int i = 0; i * k + c <= tot; ++ i)
	{
		if (i * k + c == tot)
		{
			return 1;
		}
	}
	for (int i = -1; i * k + c >= tot; -- i)
	{
		if (i * k + c == tot)
		{
			return 1;
		}
	}
	return 0;
}
signed main()
{
  ios;
	int t;
	cin >> t;
	for (int asdf = 1; asdf <= t; ++ asdf)
    {
      memset(a, 0, sizeof(a));
      int tot = 0;
      cin >> n >> k >> r >> c;
      for (int i = 1; i <= n; ++ i)
	  	  {
		  	  for (int j = 1; j <= n; ++ j)
			      {
				      a[i][j] = '.';
      			}
		    }//初始化
  		a[r][c] = 'X';
	  	for (int i = c; i >= 1; i -= k)
		    {
	    		a[r][i] = 'X';
		    }
		    for (int i = c; i <= n; i += k)
	    	{
		    	a[r][i] = 'X';
	    	}
		  for (int i = r; i >= 1; i -= k)
        {
          a[i][c] = 'X';
        }
      for (int i = r; i <= n; i += k)
        {
          a[i][c] = 'X';
        }//把第 r 行与第 c 列标记
      for (int i = 1; i <= n; ++ i)
        {
          if (i == r)
            {
              continue;
            }//第 r 行已经处理完毕
          bool flag = 0;
          for (int j = 1; j <= n; ++ j)
            {
              if (a[i][j] == 'X')
                {
                  flag = 1;
                  break;
                }
            }//判断这一行是否被标记过
          if (!flag)//没有
            {
              if (check(tot + 1))
                {
                  ++ tot;
                }//检查是否在一个已经被标记的矩阵内
              a[i][++ tot] = 'X';//从最前面开始标记
              for (int j = tot; j >= 1; j -= k)
                {
                  a[i][j] = 'X';
                }
              for (int j = tot; j <= n; j += k)
                {
                  a[i][j] = 'X';
                }//把此行标记
            }
          else//有
            {
              for (int j = c; j >= 1; j -= k)
                {
                  a[i][j] = 'X';
                }
              for (int j = c; j <= n; j += k)
                {
                  a[i][j] = 'X';
                }//标记
            }
        }
      for (int i = 1; i <= n; ++ i)
        {
          for (int j = 1; j <= n; ++ j)
            {
              cout << a[i][j];
            }
          cout << '\n';
        }//输出
    }
	return 0;
}

```

还有看不懂的评论或私信（这不可能还看不懂吧）。


---

