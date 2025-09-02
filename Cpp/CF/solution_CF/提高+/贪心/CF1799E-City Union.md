# City Union

## 题目描述

You are given $ n \times m $ grid. Some cells are filled and some are empty.

A city is a maximal (by inclusion) set of filled cells such that it is possible to get from any cell in the set to any other cell in the set by moving to adjacent (by side) cells, without moving into any cells not in the set. In other words, a city is a connected component of filled cells with edges between adjacent (by side) cells.

Initially, there are two cities on the grid. You want to change some empty cells into filled cells so that both of the following are satisfied:

- There is one city on the resulting grid.
- The shortest path between any two filled cells, achievable only by moving onto filled cells, is equal to the Manhattan distance between them.

The Manhattan distance between two cells $ (a, b) $ and $ (c, d) $ is equal to $ |a - c| + |b - d| $ .

Find a way to add filled cells that satisfies these conditions and minimizes the total number of filled cells.

## 说明/提示

In the first test case, we can add a single filled cell between the two cities to connect them. We can verify that the second condition is satisfied.

In the second test case, we can also connect the cities with a single filled cell, while satisfying the second condition.

In the third test case, note that if we filled the 3 cells in the top left, the cities would be connected, but the second condition would not be satisfied for cells $ (4, 2) $ and $ (2, 4) $ .

## 样例 #1

### 输入

```
11
1 3
#.#
2 2
.#
#.
4 4
..##
...#
#...
##..
6 6
.##...
##....
......
....##
.....#
...###
6 5
.#..#
.#..#
.#..#
.#.##
.#...
##...
5 5
#####
#...#
#.#.#
#...#
#####
4 4
.##.
##.#
#.##
.##.
5 5
..###
....#
.....
#....
#....
5 6
.##...
##....
#....#
....##
...##.
6 5
..##.
...##
....#
#....
##...
.##..
5 4
..##
..#.
..#.
#...
#...```

### 输出

```
###

.#
##

..##
..##
###.
##..

.##...
###...
..#...
..####
...###
...###

.####
.####
.####
.####
.#...
##...

#####
#####
#####
#####
#####

.##.
####
####
.##.

..###
..###
..#..
###..
#....

.##...
###...
######
...###
...##.

..##.
..###
..###
###..
###..
.##..

..##
..#.
..#.
###.
#...```

# 题解

## 作者：yimuhua (赞：7)

## 题意

给你一个 $n\times m$ 的网格图，每个点为 '#' 或 '.'。定义一个城市为一个 '#' 的连通块。一开始原图中有两个城市，要求你用最少次将某个格子变为 '#' 的操作使得图中只有一个城市，满足其中任意两个 '#' 的只经过 '#' 的最短路长度为它们的曼哈顿距离。

## 思路

首先考虑满足第二个条件，发现如果有两个 '#' 之间的最短路会绕成 $C$ 形则不满足。于是发现每一行每一列都必须为一段连续的 '#'，否则断开的两段中任意两点的最短路不满足要求。

于是需要将每一行每一列填满成一个连续段。

然后还有可能是两个城市，我们需要将它们连在一起，应该各取一个坐标为已填了的点中最大（小）横坐标和最大（小）纵坐标的点，随便连一条最短路，然后再填满。

可以发现这样做需要填的格子数量是最小的。

时间复杂度 $O(nm\log(n+m))$，实现劣的话甚至可能要 $O(n^2m^2)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
char c[55][55];
multiset<int> s;
int t, n, m, l[55], r[55];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--) {
		cin >> n >> m, s.clear();
		for(int i = 1; i <= n; i++) {
			l[i] = 51, r[i] = 0;
			for(int j = 1; j <= m; j++) {
				cin >> c[i][j];
				if(c[i][j] == '#') {
					r[i] = j, s.insert(j);
					if(l[i] > 50)
						l[i] = j;
				}
			}
		}
		for(int i = n; i; i--)
			if(l[i] < 51) {
				for(int j = l[i]; j <= r[i]; j++)
					if(c[i][j] == '.')
						c[i][j] = '#';
					else
						s.erase(s.find(j));
				if(!s.empty()) {
					if(*s.begin() < l[i])
						l[i - 1] = min(l[i - 1], l[i]);
					else
						l[i - 1] = min(r[i], *s.begin());
					if(*s.rbegin() > r[i])
						r[i - 1] = max(r[i - 1], r[i]);
					else
						r[i - 1] = max(l[i], *s.rbegin());
				}
			}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++)
				cout << c[i][j];
			cout << '\n';
		}
	}
	return 0;
}
```


---

## 作者：unputdownable (赞：7)

提供一种 $
\Theta(\sum nm)$ 的做法。

--------

对于一个联通块，称其合法当且仅当它满足题目所属条件（即任何两个格点之间最短路都等于曼哈顿距离）。

这一段只讨论只有一个联通块的情况。

观察一个合法联通块的边界，从最高点顺时针走，一定是：

1. 先只向右向下走；
2. 再只向左向下走；
3. 再只向左向上走；
4. 再只向右向上走。

如果设 $L_i$ 表示第 $i$ 行左侧 ``.`` 的数量，则联通块合法当且仅当：

1. 对于所有 $i$ 都有 $L_i \leq L_{i-1}$ 或者 $L_i \leq L_{i+1}$；
2. 对于右侧也满足上述条件；
3. 每行 ``#`` 连续。

![](https://cdn.luogu.com.cn/upload/image_hosting/8yja47db.png)

--------

考虑一个将不合法的联通块扩充成最小合法联通块的算法：

先算出每行左侧有多少 ``.``；

将 $L_i$ 对 $L_{i-1}$ 取 $\min$ 得到 $L_i'$；

将 $L_i$ 对 $L_{i+1}$ 取 $\min$ 得到 $L_i''$；

令 $L_i$ 为 $\max(L_i',L_i'')$，并标记第 $i$ 行最左侧的 $L_i$ 个格子（标记表示这个格子不用放 ``#``）。

不难发现这会得到每个 $L_i$ 的可能最大值。

接着对右侧做同样的事情。

最后将所有未标记格子全部变成 ``#``。（这同时处理了中间的空洞）

![](https://cdn.luogu.com.cn/upload/image_hosting/dvw1300l.png)

--------

然后上面那个算法完全可以处理不连通的情况，但是有时候处理出来的 "最小合法联通块" 可能会不联通。

可以发现这种时候是若干个合法的联通块斜着分布，像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/pzc8urhz.png)

易证直接用最短路把他们联通起来就是合法的。

![](https://cdn.luogu.com.cn/upload/image_hosting/7v40dglr.png)

--------

贴上两段核心代码：

```c++
    // 处理 L[i] 和 R[i]
    L[0]=1; R[0]=m; 
    L[n+1]=1; R[n+1]=m;
    for(int i=1; i<=n; ++i) {
        R[i]=0;   
        while(R[i]<R[i-1]&&s[i][R[i]+1]=='.') vis[i][++R[i]]=1;
        L[i]=m+1; 
        while(L[i]>L[i-1]&&s[i][L[i]-1]=='.') vis[i][--L[i]]=1;
    }
    for(int i=n; i>=1; --i) {
        R[i]=0;   
        while(R[i]<R[i+1]&&s[i][R[i]+1]=='.') vis[i][++R[i]]=1;
        L[i]=m+1; 
        while(L[i]>L[i+1]&&s[i][L[i]-1]=='.') vis[i][--L[i]]=1;
    }
    for(int i=1; i<=n; ++i) 
        for(int u=1; u<=m; ++u)
            if(!vis[i][u]) s[i][u]='#';
```
```c++
    // 连接两个点
    int dx=P2.first >=P1.first  ? 1 : -1;
    int dy=P2.second>=P1.second ? 1 : -1;
    while(P1!=P2) {
              if(s[P1.first+dx][P1.second   ]=='#'&&P1.first !=P2.first ) P1.first +=dx;
         else if(s[P1.first   ][P1.second+dy]=='#'&&P1.second!=P2.second) P1.second+=dy;
         else if(P1.first!=P2.first) P1.first +=dx,s[P1.first][P1.second]='#';
         else                        P1.second+=dy,s[P1.first][P1.second]='#';
    }
    
```



---

## 作者：wxzzzz (赞：6)

### 思路

先考虑一件事情，对于一个连通块，如何使它合法。

可以发现，对于一组合法解，不可能有任何行、列上存在一段区间 $[l,r]$ 满足 $l,r$ 都是 `#` 且 $l+1\sim r-1$ 都是 `.`，这一段 `.` 必须被 `#` 填上。因此，可以对行列交替操作，直到没有如上 $[l+1,r-1]$ 可以被填上为止。显然，行列最多各操作两次，故复杂度正确。

为了方便后续操作，要先用如上操作把每一个连通块都变成合法的。

然后，要把连通块合并。

题面说了最多两个连通块，而且前面操作可以保证两个连通块没有任何点在同一行、列上，因此可以直接连接连个连通块的最短路径。

具体来说，记录每个连通块的最小横坐标 $minx_{1/2}$、最小纵坐标 $miny_{1/2}$、最大横坐标 $maxx_{1/2}$ 以及最大纵坐标 $maxy_{1/2}$。

然后分四种情况讨论：

1. 连通块 $1$ 在连通块 $2$ 左上方。

	连接 $(maxx_1,maxy_1)$ 和 $(minx_2,miny_2)$。

1. 连通块 $1$ 在连通块 $2$ 右上方。

	连接 $(minx_1,maxy_1)$ 和 $(maxx_2,maxy_2)$。

1. 连通块 $1$ 在连通块 $2$ 左下方。

	连接 $(maxx_1,miny_1)$ 和 $(minx_2,maxy_2)$。

1. 连通块 $1$ 在连通块 $2$ 右下方。

	连接 $(minx_1,miny_1)$ 和 $(maxx_2,maxy_2)$。

到这里，整个图大概会变成类似这个框架：

![](https://cdn.luogu.com.cn/upload/image_hosting/x24kmaq9.png)

然后，按前面处理一个连通块的办法，对整张图做一遍就好了，总时间复杂度为 $O(\sum nm)$。

思考过程并不难，需要注意的是一些细节，例如 $x,y$ 表示行还是列，$y$ 坐标是从上到下增大。这些平时用不着思考的细节在这道题却非常重要。

- 下面代码为了减小常数，用了 bitset 代替 bool，具体可以去 [我的博客园](https://www.cnblogs.com/wangxuzhou-blog/p/data-structure-preliminary.html#bitset) 查看用法，和 bool 差不多。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
int t, n, m, nx, ny, idx, root, minn, minl, maxr, f[2505], id[2505], maxx[2505], maxy[2505], minx[2505],
    miny[2505];
char s[55][55];
bool check;
bitset<2505> vis, flag;
int p(int x, int y) {
    return (x - 1) * m + y;
}
int find(int x) {
    if (x == f[x])
        return x;

    return f[x] = find(f[x]);
}
bool ok() {
    int last = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '#') {
                if (last && find(p(i, j)) != last)
                    return 0;

                last = find(p(i, j));
            }
        }
    }

    return 1;
}
void line() {
    for (int i = 1; i <= n; i++) {
        minl = 0, maxr = 0;

        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '#' && !minl)
                minl = j;

            if (s[i][j] == '#')
                maxr = j;
        }

        if (!minl)
            continue;

        for (int j = minl, last = 0; j <= maxr; j++) {
            if (s[i][j] == '.') {
                check = 1, s[i][j] = '#';

                if (last)
                    f[find(p(i, j))] = last;

                last = find(p(i, j));
            }
        }
    }
}
inline void row() {
    for (int j = 1; j <= m; j++) {
        minl = 0, maxr = 0;

        for (int i = 1; i <= n; i++) {
            if (s[i][j] == '#' && !minl)
                minl = i;

            if (s[i][j] == '#')
                maxr = i;
        }

        if (!minl)
            continue;

        for (int i = minl, last = 0; i <= maxr; i++)
            if (s[i][j] == '.')
                check = 1, s[i][j] = '#';
    }
}
void dfs(int x, int y) {
    vis[p(x, y)] = 1, f[p(x, y)] = root;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];

        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[p(nx, ny)] && s[nx][ny] == '#')
            dfs(nx, ny);
    }
}
int main() {
    cin >> t;

    while (t--) {
        cin >> n >> m;
        idx = 0, minn = 1e18, check = 1;
        vis.reset(), flag.reset();
        memset(maxx, 0, sizeof maxx);
        memset(maxy, 0, sizeof maxy);
        memset(minx, 0x3f, sizeof minx);
        memset(miny, 0x3f, sizeof miny);

        for (int i = 1; i <= n; i++)
            scanf("%s", s[i] + 1);

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                f[p(i, j)] = p(i, j);

        while (check)
            check = 0, line(), row();

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (s[i][j] == '#' && !vis[p(i, j)])
                    root = p(i, j), dfs(i, j);

        if (ok()) {
            for (int i = 1; i <= n; i++)
                cout << s[i] + 1 << '\n';

            cout << '\n';
            continue;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1, now; j <= m; j++) {
                if (s[i][j] == '.')
                    continue;

                now = find(p(i, j));

                if (!flag[now])
                    id[++idx] = now, flag[now] = 1;

                minx[now] = min(minx[now], i);
                miny[now] = min(miny[now], j);
                maxx[now] = max(maxx[now], i);
                maxy[now] = max(maxy[now], j);
            }
        }

        if (maxy[id[1]] < maxy[id[2]]) {
            if (maxx[id[1]] < maxx[id[2]]) {
                nx = maxx[id[1]], ny = maxy[id[1]], s[nx][ny] = '#';

                while (nx < minx[id[2]] || ny < miny[id[2]]) {
                    if (nx < minx[id[2]])
                        nx++, s[nx][ny] = '#';

                    if (ny < miny[id[2]])
                        ny++, s[nx][ny] = '#';
                }
            } else {
                nx = minx[id[1]], ny = maxy[id[1]], s[nx][ny] = '#';

                while (nx > maxx[id[2]] || ny < maxy[id[2]]) {
                    if (nx > maxx[id[2]])
                        nx--, s[nx][ny] = '#';

                    if (ny < maxy[id[2]])
                        ny++, s[nx][ny] = '#';
                }
            }
        } else {
            if (maxx[id[1]] < maxx[id[2]]) {
                nx = maxx[id[1]], ny = miny[id[1]], s[nx][ny] = '#';

                while (nx < minx[id[2]] || ny < maxy[id[2]]) {
                    if (nx < minx[id[2]])
                        nx++, s[nx][ny] = '#';

                    if (ny < maxy[id[2]])
                        ny++, s[nx][ny] = '#';
                }
            } else {
                nx = minx[id[1]], ny = miny[id[1]], s[nx][ny] = '#';

                while (nx > maxx[id[2]] || ny > maxy[id[2]]) {
                    if (nx > maxx[id[2]])
                        nx--, s[nx][ny] = '#';

                    if (ny > maxy[id[2]])
                        ny--, s[nx][ny] = '#';
                }
            }
        }

        check = 1;

        while (check)
            check = 0, line(), row();

        for (int i = 1; i <= n; i++)
            cout << s[i] + 1 << '\n';

        cout << '\n';
    }

    return 0;
}
```

---

## 作者：有趣的问题 (赞：3)

题外话：本来没打这场，但同寝室的巨佬 @[赵悦岑](https://www.luogu.com.cn/user/291248) 在打，所以我说帮他口胡一下 E，结果我口胡出来的时候他还没过 B，而且一直到最后都没过！咳咳……

### 题意

给你一个 $n\times m$ 的矩阵，矩阵中有 `.` 和 `#`，且 `#` 构成两个四连通块。请用尽量少的操作，将一些 `.` 改成 `#` 使得所有 `#` 构成一个四连通块，且任意两个 `#` 的最短路（只经过 `#` ）为他们的曼哈顿距离。

### 分析

由题目要求，我们可以发现一些简单的性质：如果一个格子上下或左右都有 `#`，则他必定会被染成 `#`，否则无法满足条件。补充完这些后，如果此时只剩一个连通块，那么就做完了。否则继续考虑这个性质：对于上下左右四个边界，一定只会出现单峰的情况，而且剩下的两个连通块一定是左上-右下或右上-左下的，而且不会有某一行或某一列出现两个 `#` 属于不同连通块。现在我们只考虑左上-右下型的。一个显然的想法是先分别把左上的右下角补齐，把右下的左上角补齐，再用一条简单的路径把两个连通块连起来。举个例子，如果图是这样的：

```
###....
##.....
##.....
#......
......#
.....##
....###
```

那么我们补充完后可以是这样的：

```
###....
###....
###....
#####..
....###
....###
....###
```

不难证明，这样补充填充的 `#` 一定是最少的。

### 代码

有点长，放在[这里](https://codeforces.com/contest/1799/submission/195512267)。

---

## 作者：Leasier (赞：0)

先考虑下面那个奇怪的条件，不难发现当某行或某列的 `#` 格子不连续时相邻不连续位置不满足条件，而都连续时显然可以构造出一条路径。

于是我们先把初始的网格拿来涂 `#` 使得其满足上面这个条件，现在分为两种情况：

1. 此时只有一个连通块

已经满足条件了，不需要继续涂色。

2. 此时有两个连通块

考虑找出这两个连通块的位置，先考虑横坐标较小的连通块（设为 A）的最大纵坐标 $<$ 横坐标较大的连通块（设为 B）的最小纵坐标的情况，另一种可以把网格旋转一下后类似地操作。

此时两个连通块一定均呈现以下形态（可能经过旋转）：

- 至多两个方向相反的凸其起的块拼在一起。

经过大量手模我们发现染下面这条路径总是不劣：

- 起点为横坐标为 A 中最大横坐标，纵坐标为 A 中最大纵坐标。
- 终点为横坐标为 B 中最小横坐标，纵坐标为 B 中最小纵坐标。

染的时候贪心地尽量走已经是 `#` 的位置，并在每次染完后重新进行一开始使其满足第二个条件的操作即可。

综上，时间复杂度为 $O(\sum nm(n + m))$。

代码：
```cpp
#include <stdio.h>

int id[57][57], root[2507];
char s[57][57];

inline void init(int n){
	for (int i = 1; i <= n; i++){
		root[i] = i;
	}
}

inline void fill(int n, int m){
	for (int i = 1; i <= n; i++){
		int l = 0x7fffffff, r = 0;
		for (int j = 1; j <= m; j++){
			if (s[i][j] == '#'){
				l = j;
				break;
			}
		}
		for (int j = m; j >= 1; j--){
			if (s[i][j] == '#'){
				r = j;
				break;
			}
		}
		for (int j = l; j <= r; j++){
			s[i][j] = '#';
		}
	}
	for (int i = 1; i <= m; i++){
		int l = 0x7fffffff, r = 0;
		for (int j = 1; j <= n; j++){
			if (s[j][i] == '#'){
				l = j;
				break;
			}
		}
		for (int j = n; j >= 1; j--){
			if (s[j][i] == '#'){
				r = j;
				break;
			}
		}
		for (int j = l; j <= r; j++){
			s[j][i] = '#';
		}
	}
	for (int i = 1; i <= n; i++){
		int l = 0x7fffffff, r = 0;
		for (int j = 1; j <= m; j++){
			if (s[i][j] == '#'){
				l = j;
				break;
			}
		}
		for (int j = m; j >= 1; j--){
			if (s[i][j] == '#'){
				r = j;
				break;
			}
		}
		for (int j = l; j <= r; j++){
			s[i][j] = '#';
		}
	}
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline void merge(int x, int y){
	int x_root = get_root(x), y_root = get_root(y);
	if (x_root != y_root) root[x_root] = y_root;
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, m, cnt = 0, anyx = -1, anyy = -1;
		bool flag = false;
		scanf("%d %d", &n, &m);
		for (int j = 1; j <= n; j++){
			for (int k = 1; k <= m; k++){
				id[j][k] = ++cnt;
			}
		}
		init(cnt);
		for (int j = 1; j <= n; j++){
			scanf("%s", &s[j][1]);
		}
		fill(n, m);
		for (int j = 1; j <= n && anyx == -1 && anyy == -1; j++){
			for (int k = 1; k <= m; k++){
				if (s[j][k] == '#'){
					anyx = j;
					anyy = k;
					break;
				}
			}
		}
		for (int j = 1; j <= n; j++){
			for (int k = 1; k <= m; k++){
				if (s[j][k] == '#'){
					if (j < n && s[j + 1][k] == '#') merge(id[j][k], id[j + 1][k]);
					if (k < m && s[j][k + 1] == '#') merge(id[j][k], id[j][k + 1]);
				}
			}
		}
		for (int j = 1; j <= n && !flag; j++){
			for (int k = 1; k <= m; k++){
				if (s[j][k] == '#' && get_root(id[j][k]) != get_root(id[anyx][anyy])){
					flag = true;
					break;
				}
			}
		}
		if (flag){
			int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
			for (int j = n; j >= 1 && x1 == -1; j--){
				for (int k = 1; k <= m; k++){
					if (s[j][k] == '#' && get_root(id[j][k]) == get_root(id[anyx][anyy])){
						x1 = j;
						break;
					}
				}
			}
			for (int j = m; j >= 1 && y1 == -1; j--){
				for (int k = 1; k <= n; k++){
					if (s[k][j] == '#' && get_root(id[k][j]) == get_root(id[anyx][anyy])){
						y1 = j;
						break;
					}
				}
			}
			for (int j = 1; j <= n && x2 == -1; j++){
				for (int k = 1; k <= m; k++){
					if (s[j][k] == '#' && get_root(id[j][k]) != get_root(id[anyx][anyy])){
						x2 = j;
						break;
					}
				}
			}
			for (int j = 1; j <= m && y2 == -1; j++){
				for (int k = 1; k <= n; k++){
					if (s[k][j] == '#' && get_root(id[k][j]) != get_root(id[anyx][anyy])){
						y2 = j;
						break;
					}
				}
			}
			if (y1 > y2){
				x1 = y1 = x2 = y2 = -1;
				for (int j = n; j >= 1 && x1 == -1; j--){
					for (int k = 1; k <= m; k++){
						if (s[j][k] == '#' && get_root(id[j][k]) == get_root(id[anyx][anyy])){
							x1 = j;
							break;
						}
					}
				}
				for (int j = 1; j <= m && y1 == -1; j++){
					for (int k = 1; k <= n; k++){
						if (s[k][j] == '#' && get_root(id[k][j]) == get_root(id[anyx][anyy])){
							y1 = j;
							break;
						}
					}
				}
				for (int j = 1; j <= n && x2 == -1; j++){
					for (int k = 1; k <= m; k++){
						if (s[j][k] == '#' && get_root(id[j][k]) != get_root(id[anyx][anyy])){
							x2 = j;
							break;
						}
					}
				}
				for (int j = m; j >= 1 && y2 == -1; j--){
					for (int k = 1; k <= n; k++){
						if (s[k][j] == '#' && get_root(id[k][j]) != get_root(id[anyx][anyy])){
							y2 = j;
							break;
						}
					}
				}
			}
			while (x1 != x2 && y1 != y2){
				int dx = x1 < x2 ? 1 : -1;
				s[x1][y1] = '#';
				fill(n, m);
				if (s[x1 + dx][y1] == '#'){
					x1 += dx;
				} else {
					y1 += y1 < y2 ? 1 : -1;
				}
			}
			while (x1 != x2){
				s[x1][y2] = '#';
				x1 += x1 < x2 ? 1 : -1;
			}
			while (y1 != y2){
				s[x2][y1] = '#';
				y1 += y1 < y2 ? 1 : -1;
			}
			fill(n, m);
		}
		for (int j = 1; j <= n; j++){
			printf("%s\n", &s[j][1]);
		}
		printf("\n");
	}
	return 0;
}
```

---

