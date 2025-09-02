# Theseus and labyrinth

## 题目描述

给定 $n (1≤n≤100)$ 个数,从中找出尽可能多的数使得他们能够组成一个最长的等差数列。输出该最长等差数列的长度。

注意：当 $n=1$ 时，构成长度为 $1$ 的等差数列。

## 样例 #1

### 输入

```
2 2
+*
*U
1 1
2 2
```

### 输出

```
-1```

## 样例 #2

### 输入

```
2 3
&lt;&gt;&lt;
&gt;&lt;&gt;
1 1
2 1
```

### 输出

```
4```

# 题解

## 作者：Juanzhang (赞：1)

**思路：**

- $bfs$

这题的特点在于，可以**旋转**

我们可以记录当前位置，已旋转的次数

而我们又可以发现，旋转$4$次与不旋转的效果一样

于是我们的状态便可以$mod$ $4$

可以预处理出每个字符代表的门的情况（打表），

以及给出的$map$旋转$0,1,2,3$次的情况

**注意：**

- 手打队列空间要开$1e7$

**代码**

``` cpp
#include <bits/stdc++.h>
using namespace std;

#define fir first
#define sec second

typedef pair <int, int> pii;
typedef pair <pii, int> ppi;
const int maxn = 1010;
const int maxlen = 1e7 + 10;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
ppi q[maxlen];
bool to[4][1 << 8];
char a[4][maxn][maxn];
int n, m, l, r, sx, sy, tx, ty, to_next[4], nxt[1 << 8], dp[4][maxn][maxn];

void make(char ch, bool b1, bool b2, bool b3, bool b4) {
	to[0][ch] = b1, to[1][ch] = b2, to[2][ch] = b3, to[3][ch] = b4;
}

void init() {
	to_next[0] = 1;
	to_next[1] = 0;
	to_next[2] = 3;
	to_next[3] = 2; // 因为题目要求相邻点都有门才能走，所以就要判断出发点的当前方向，结束点的相反方向是否有门。
	nxt['+'] = '+';
	nxt['-'] = '|';
	nxt['|'] = '-';
	nxt['^'] = '>';
	nxt['>'] = 'v';
	nxt['<'] = '^';
	nxt['v'] = '<';
	nxt['L'] = 'U';
	nxt['R'] = 'D';
	nxt['U'] = 'R';
	nxt['D'] = 'L';
	nxt['*'] = '*'; // 每个字符旋转一次的状态
	make('+', 1, 1, 1, 1);
	make('-', 0, 0, 1, 1);
	make('|', 1, 1, 0, 0);
	make('^', 1, 0, 0, 0);
	make('>', 0, 0, 0, 1);
	make('<', 0, 0, 1, 0);
	make('v', 0, 1, 0, 0);
	make('L', 1, 1, 0, 1);
	make('R', 1, 1, 1, 0);
	make('U', 0, 1, 1, 1);
	make('D', 1, 0, 1, 1);
	make('*', 0, 0, 0, 0); // 处理出每个字符能往什么地方走
}

bool pd(int x, int y) {
	return x > 0 && y > 0 && x <= n && y <= m;
}

int main() {
	init();
	char buf[maxn];
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		gets(buf);
		for (int j = 1; j <= m; j++) {
			a[0][i][j] = getchar();
			for (int k = 1; k < 4; k++) {
				a[k][i][j] = nxt[a[k - 1][i][j]];
			}
		}
	}
	scanf("%d %d %d %d", &sx, &sy, &tx, &ty);
	if (sx == tx && sy == ty) {
		return puts("0"), 0;
	}
	dp[0][sx][sy] = 1; // 因为只用了dp一个数组，为了方便判重，初始值+1
	q[++r] = make_pair(make_pair(sx, sy), 0);
	for (; l <= r; ) {
		ppi u = q[l++];
		int px = u.fir.fir, py = u.fir.sec;
		if (!dp[(u.sec + 1) % 4][px][py]) {
			dp[(u.sec + 1) % 4][px][py] = dp[u.sec][px][py] + 1;
			q[++r] = make_pair(u.fir, (u.sec + 1) % 4);
		}
		for (int i = 0; i < 4; i++) {
			int nx = px + dx[i], ny = py + dy[i];
			if (pd(nx, ny) && to[i][a[u.sec][px][py]] && to[to_next[i]][a[u.sec][nx][ny]]) {
				if (nx == tx && ny == ty) {
					printf("%d", dp[u.sec][px][py]);
					return 0;
				}
				if (!dp[u.sec][nx][ny]) {
					dp[u.sec][nx][ny] = dp[u.sec][px][py] + 1;
					q[++r] = make_pair(make_pair(nx, ny), u.sec);
				}
			}
		}
	}
	puts("-1");
	return 0;
}
```

然而这题也可以通过**位运算**处理能否通过的问题

大体思路就是，用一个整数表示当前位置的通过状态

**代码**

``` cpp
#include <bits/stdc++.h>
using namespace std;

#define fir first
#define sec second

typedef pair <int, int> pii;
typedef pair <pii, int> ppi;
const int maxn = 2010;
const int maxlen = 1e7 + 10;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
ppi q[maxlen];
char a[4][maxn][maxn];
int n, m, l = 1, r, to[1 << 8], nxt[1 << 8], dp[4][maxn][maxn];

void make(char ch, bool b1, bool b2, bool b3, bool b4) {
	to[ch] = (b1 << 0) + (b2 << 1) + (b3 << 2) + (b4 << 3);
}

void init() {
	nxt['+'] = '+';
	nxt['-'] = '|';
	nxt['|'] = '-';
	nxt['^'] = '>';
	nxt['>'] = 'v';
	nxt['<'] = '^';
	nxt['v'] = '<';
	nxt['L'] = 'U';
	nxt['R'] = 'D';
	nxt['U'] = 'R';
	nxt['D'] = 'L';
	nxt['*'] = '*';
    make('+', 1, 1, 1, 1);
    make('-', 0, 1, 0, 1);
    make('|', 1, 0, 1, 0);
    make('^', 1, 0, 0, 0);
    make('>', 0, 0, 0, 1);
    make('<', 0, 1, 0, 0);
    make('v', 0, 0, 1, 0);
	make('L', 1, 0, 1, 1);
	make('R', 1, 1, 1, 0);
	make('U', 0, 1, 1, 1);
	make('D', 1, 1, 0, 1);
	make('*', 0, 0, 0, 0);
}

bool pd(int x, int y) {
	return x > 0 && y > 0 && x <= n && y <= m;
}

bool pass(int hx, int hy, int which, int chk) {
	return to[a[which][hx][hy]] & 1 << chk;
}

int main() {
	init();
	char buf[maxn];
	int sx, sy, tx, ty;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		gets(buf);
		for (int j = 1; j <= m; j++) {
			a[0][i][j] = getchar();
			for (int k = 1; k < 4; k++) {
				a[k][i][j] = nxt[a[k - 1][i][j]];
			}
		}
	}
	scanf("%d %d %d %d", &sx, &sy, &tx, &ty);
	if (sx == tx && sy == ty) {
		return puts("0"), 0;
	}
	dp[0][sx][sy] = 1;
	q[++r] = make_pair(make_pair(sx, sy), 0);
	for (; l <= r; ) {
		ppi u = q[l++];
		int px = u.fir.fir, py = u.fir.sec, t = dp[u.sec][px][py];
		if (!dp[(u.sec + 1) % 4][px][py]) {
			dp[(u.sec + 1) % 4][px][py] = t + 1;
			q[++r] = make_pair(u.fir, (u.sec + 1) % 4);
		}
		for (int i = 0; i < 4; i++) {
			int nx = px + dx[i], ny = py + dy[i];
			if (pd(nx, ny) && pass(px, py, u.sec, i) && pass(nx, ny, u.sec, (i + 2) % 4)) {
				if (nx == tx && ny == ty) {
					printf("%d", t);
					return 0;
				}
				if (!dp[u.sec][nx][ny]) {
					dp[u.sec][nx][ny] = t + 1;
					q[++r] = make_pair(make_pair(nx, ny), u.sec);
				}
			}
		}
	}
	puts("-1");
	return 0;
}
```

---

