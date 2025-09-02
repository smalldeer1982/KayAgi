# Ciel and Robot

## 题目描述

Fox Ciel has a robot on a 2D plane. Initially it is located in (0, 0). Fox Ciel code a command to it. The command was represented by string $ s $ . Each character of $ s $ is one move operation. There are four move operations at all:

- 'U': go up, (x, y) $ → $ (x, y+1);
- 'D': go down, (x, y) $ → $ (x, y-1);
- 'L': go left, (x, y) $ → $ (x-1, y);
- 'R': go right, (x, y) $ → $ (x+1, y).

The robot will do the operations in $ s $ from left to right, and repeat it infinite times. Help Fox Ciel to determine if after some steps the robot will located in $ (a,b) $ .

## 说明/提示

In the first and second test case, command string is "RU", so the robot will go right, then go up, then right, and then up and so on.

The locations of its moves are (0, 0) $ → $ (1, 0) $ → $ (1, 1) $ → $ (2, 1) $ → $ (2, 2) $ → $ $ ... $

So it can reach (2, 2) but not (1, 2).

## 样例 #1

### 输入

```
2 2
RU
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
1 2
RU
```

### 输出

```
No
```

## 样例 #3

### 输入

```
-1 1000000000
LRRLU
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
0 0
D
```

### 输出

```
Yes
```

# 题解

## 作者：辛丑九月 (赞：1)

## Analysis

建议评橙。

设要求到的点是 $(tx,ty)$，字符串长度为 $n$。

首先发现每走 $n$ 步在 $x$、$y$ 上的变化量都是相同的，所以我们可以先处理出走 $n$ 步后坐标变化量 $(dx, dy)$。

然后再枚举零头走了几步，算出当前的坐标变化量 $(nx, ny)$，那么只要 $dx \mid (tx - nx)$ 且 $dy \mid (ty - ny)$ 且 $\frac {tx - nx} {dx} = \frac {ty - ny}{dy}$，其中 $\mid$ 符号表示整除，例如 $2 \mid 4$。

真正麻烦的是一些细节，比如要走的步数是正的，所以 $\frac {tx - nx} {dx}$ 需要是正的（或是 $0$）。

然后有可能出现 $dx = 0$ 或是 $dy = 0$ 的情况，如果两个都是 $0$，那么就直接枚举走了几步，这个步数是一定小于 $n$ 的，因为走 $n$ 步就回到原点了。

单独只有一个 $dx = 0$ 的话，还是枚举走了几步，不同的是需要满足 $tx - nx = dx$，另外一维照常，只是不用 $\frac {tx - nx} {dx} = \frac {ty - ny}{dy}$ 这个条件。如果 $dy = 0$ 同理，只不过将 $x$ 和 $y$ 互换罢了。

## Code

```cpp
# include <bits/stdc++.h>
# define int long long
# define P(x) return puts (x), 0;
using namespace std;

const int W[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int tx, ty, n;
int nx, ny, dx, dy;
string s;
map < char, int > S;

signed main () {
	cin >> tx >> ty >> s;
	S['U'] = 0, S['R'] = 1, S['D'] = 2, S['L'] = 3;
	for (char i : s) dx += W[S[i]][0], dy += W[S[i]][1];
	if (tx == 0 && ty == 0) P("Yes"); // 刚开始就满足直接输出 Y 就行了
	if (dx == 0 && dy == 0) {
		for (char i : s) {
			nx += W[S[i]][0]; ny += W[S[i]][1];
			if (nx == tx && ny == ty) P("Yes");
		}	P("No");
	}
	if (!dx) {
		for (char i : s) {
			nx += W[S[i]][0]; ny += W[S[i]][1]; ty -= ny;
			if (tx == nx && ty % dy == 0 && ty / dy > 0) P("Yes");
			ty += ny;
		}	P("No");
	}
	if (!dy) {
		for (char i : s) {
			nx += W[S[i]][0]; ny += W[S[i]][1]; tx -= nx;
			if (ty == ny && tx % dx == 0 && tx / dx > 0) P("Yes");
			tx += nx;
		}	P("No");
	}
	for (char i : s) {	
		nx += W[S[i]][0]; ny += W[S[i]][1]; tx -= nx; ty -= ny;
		if (tx % dx == 0 && ty % dy == 0 && tx / dx == ty / dy && tx / dx >= 0) P("Yes");
		tx += nx; ty += ny;
	}
	P("No");
}
```

---

## 作者：_rbq (赞：0)

翻译已经很清楚了，就不再重复了。

首先，需要求出操作 $s$ 的任意前缀之后位置会如何变化。模拟即可。记 $a_{i,1}$ 为操作 $s$ 的长度为 $i$ 的前缀之后的 $x$ 值，$a_{i,2}$ 为 $y$ 值。

例如第一组样例，$s=\{\text{R,U}\}$。

$a_{1,1}=1,a_{1,2}=0$

$a_{2,1}=a_{2,2}=1$

然后，如果要经过 $n$ 次操作变成 $(a,b)$。那么肯定是先操作若干次 $s$，再操作长度为 $i$ 的 $s$ 的前缀。

我们并不知道 $i$ 的值，但是知道 $i\le|S|$。根据 $|s|\le100$，可以枚举每个 $i$。

那么，当操作 $n-i$ 次时，在 $(a-a_{i,1},b-a_{i,2})$，必然操作了若干次完整的 $s$，则 $a_{|s|,1}|a-a_{i,1},a_{|s|,2}|b-a_{i,2}$。于是，只要满足这个条件，就可以到达。如果遍历了所有 $i\in[1,|s|]$ 都不满足，则不能到达。

---

