# Track

## 题目描述

You already know that Valery's favorite sport is biathlon. Due to your help, he learned to shoot without missing, and his skills are unmatched at the shooting range. But now a smaller task is to be performed, he should learn to complete the path fastest.

The track's map is represented by a rectangle $ n×m $ in size divided into squares. Each square is marked with a lowercase Latin letter (which means the type of the plot), with the exception of the starting square (it is marked with a capital Latin letters $ S $ ) and the terminating square (it is marked with a capital Latin letter $ T $ ). The time of movement from one square to another is equal to $ 1 $ minute. The time of movement within the cell can be neglected. We can move from the cell only to side-adjacent ones, but it is forbidden to go beyond the map edges. Also the following restriction is imposed on the path: it is not allowed to visit more than $ k $ different types of squares (squares of one type can be visited an infinite number of times). Squares marked with $ S $ and $ T $ have no type, so they are not counted. But $ S $ must be visited exactly once — at the very beginning, and $ T $ must be visited exactly once — at the very end.

Your task is to find the path from the square $ S $ to the square $ T $ that takes minimum time. Among all shortest paths you should choose the lexicographically minimal one. When comparing paths you should lexicographically represent them as a sequence of characters, that is, of plot types.

## 样例 #1

### 输入

```
5 3 2
Sba
ccc
aac
ccc
abT
```

### 输出

```
bcccc
```

## 样例 #2

### 输入

```
3 4 1
Sxyy
yxxx
yyyT
```

### 输出

```
xxxx
```

## 样例 #3

### 输入

```
1 3 3
TyS
```

### 输出

```
y
```

## 样例 #4

### 输入

```
1 4 1
SxyT
```

### 输出

```
-1
```

# 题解

## 作者：wizardMarshall (赞：1)

## 题意

有一个 $n$ 行 $m$ 列的矩阵，每个格子要么是起点，要么是终点，要么是某个小写字母。求出从起点到终点的最短路径，在此基础上输出字典序最小的路径。

## 思路

最短路板子。

有一个走过的字符数不超过 $k$ 的限制。由于小写字母只有二十六个，可以用状压表示，每次判断二进制中 $1$ 的位数。但每个格子都维护状压是不太现实的。只能是在状态里用一个整数表示。

然后凭直觉，我们肯定要在状态里维护一个字符串用来表示走过的路径。

于是一个状态里有以下数据：坐标、状压表示的字符集以及走过的字符串。

如果直接在网格图上跑 BFS，显然不能保证最优。于是将其换成优先队列存储，每次先判断字符串长度（即路径长度）然后再判断字符串的字典序。这样便能保证在第一次搜到终点的时候答案最小。

然后我们还要避免状态的重复，即到了同一个格子，字符集也相同的这些状态。这些状态中有一个最优的可以继续搜下去，其他就不应继续。由于前面的条件，保证了这个最优的最先到达，因此在每个格子维护一个 `set`，用来存储已有的状态，防止多次搜到。每次判重即可。

最后，我们发现如果按此状态搜索的话状态量过大（如网格都是同一个字符时），因此考虑剪枝。在同一个格子里，若后到状态的字符集被前面的状态包含，说明这个状态无论哪方面都不比之前优，没有必要继续。维护一个数组，记录这个格子上一个的（状压）字符集状态即可。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;
struct node{
	int x, y, c;
	string s;
	bool operator < (const node & y) const{//优先队列比较条件，先比较字符串长度，再比较字典序
		if (s.size() != y.s.size()) {
			return s.size() > y.s.size();
		}return s > y.s;
	}
};
char s[55][55];
set <int> dp[55][55];
int lst[55][55];
int xx[5] = {0, 0, 1, -1};
int yy[5] = {1, -1, 0, 0};
signed main() {
	int n, m, k;
	cin >> n >> m >> k;
	int sx, sy;
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == 'S') {
				sx = i, sy = j;
			}
		}
	}
	priority_queue <node> q;
	
	q.push((node){sx, sy, 0, ""});
	while (!q.empty()) {
		node f = q.top();q.pop();
		for (int l = 0; l < 4; l++) {
			int nowx = f.x + xx[l];
			int nowy = f.y + yy[l];
			if (nowx < 1 || nowx > n || nowy < 1 || nowy > m) {
				continue;
			}if (s[nowx][nowy] == 'T') {//搜到了终点，此时状态最优
				cout << f.s;
				return 0;
			}
			if (s[nowx][nowy] == 'S')continue;//不走回头路
			int nowc = f.c | (1 << (s[nowx][nowy] - 'a'));//当前状态
			if (__builtin_popcount(nowc) > k || dp[nowx][nowy].count(nowc)) {//如果字符个数>k，或者之前就搜到过（比之前的劣）
				continue;
			}
			if (lst[nowx][nowy] && (lst[nowx][nowy] & nowc) == lst[nowx][nowy]) {//如上述，剪枝
				continue;
			}lst[nowx][nowy] = nowc;
			dp[nowx][nowy].insert(nowc);
			q.push((node){nowx, nowy, nowc, f.s + s[nowx][nowy]});
		}
	}cout << -1;//中途被k限制等
	return 0;
}
```

---

