# [ICPC 2014 WF] Maze Reduction

## 题目描述

Jay 经营着一个小型嘉年华，里面有各种游乐设施。不幸的是，最近发生的过山车事故、厕所的水灾以及小丑事件使得 Jay 的嘉年华在公众中声誉不佳。由于付费顾客减少和收入下降，他需要削减一些成本以维持经营。

嘉年华中最大的吸引点之一是一个大型且复杂的迷宫。它由各种圆形房间组成，这些房间通过狭窄、曲折的走廊连接。游客们喜欢在其中迷路并尝试绘制地图。Jay 注意到，有些房间可能实际上是相同的。如果是这样，他可以在不被人注意的情况下缩小迷宫的规模。

如果你被放置在房间 $A$ 或 $B$ 中（并且你知道迷宫的地图），仅通过探索迷宫无法判断你是从 $A$ 还是 $B$ 开始的，那么两个房间 $A$ 和 $B$ 就是实际上相同的。每个房间的走廊出口均匀分布，你不能在房间中做标记或留下任何东西（特别是，你无法判断你是否曾经访问过它）。房间的唯一识别特征是它们的出口数量。走廊也足够曲折，以至于彼此无法区分，但当你进入一个房间时，你知道你是从哪个走廊来的，因此可以通过它们在房间周围出现的顺序进行一些导航。

Jay 向嘉年华迷宫协会求助。那就是你！编写一个程序来确定迷宫中所有实际上相同的房间集合。

## 说明/提示

时间限制：2000 毫秒，内存限制：1048576 kB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2014。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
13
2 2 4
3 1 3 5
2 2 4
3 1 3 6
2 2 6
2 4 5
2 8 9
2 7 9
2 7 8
2 11 13
2 10 12
2 11 13
2 10 12
```

### 输出

```
2 4
5 6
7 8 9 10 11 12 13
```

## 样例 #2

### 输入

```
6
3 3 4 5
0
1 1
1 1
2 1 6
1 5
```

### 输出

```
none
```

# 题解

## 作者：FangZeLi (赞：2)

## Link

[P6896 [ICPC2014 WF]Maze Reduction](https://www.luogu.com.cn/problem/P6896)

## Solution

首先你可能要花一定的时间理解一下题意。

然后你发现就是要你判断房间的等价类的个数。

要做这个问题，我们不妨先考虑我们判断房间是否等价的手段。直接从点的角度出发，我们不妨设我们从某个边 $u$ 进入点 $x$，从边 $v$ 进入点 $y$ ，那么两个点等价，当且仅当**点 $x$ 从 $u$ 起与点 $y$ 从 $v$ 起的边序列相等**，而两个边相等，又要求**两个边的终点等价**。

那么我们再考虑需要判断的点。这时，我们有选择第一条走的边的权力，也就是说，只要两个点的边序列**循环移位**后相等，两个点就相等。

这是一个复杂结构的判等问题，我们考虑hash。

这个hash值显然是递推出来的。我们考虑一下要记哪些东西：

- 点 $x$（显然）
- 先走哪一条边 $v$（见上面的推导）

然后你发现记这么一点不能递推，于是你想了想，再记一维：

- 走了 $k$ 步

然后万事大吉。最后我们递推hash值时，只要从进入边顺时针遍历，就可以保证边序列的信息记录到了hash值中。

唔……具体hash的递推过程比较难表达，大家可以看看代码。

然后就是那个循环移位的解决：其实也很简单，只需要把 $f_{n,x,-}$ 看成一个字符串，求出一个最小表示，然后判相等的时候直接一个字符串比较就OK了。

注意如果你是用Lyndon分解求最小表示的要注意 $|s| = 1$ 的情况。

## Code

```cpp
#include <cstdio>

#define _N 110
#define _P 998244353

struct Mod {
	int val;
	Mod() {
		val = 0;
	}
	Mod(long long x) {
		val = x >= 0 ? x % _P : x % _P + _P;
	}
};

bool inline operator ==(const Mod& left, const Mod& right) {
	return left.val == right.val;
}
bool inline operator !=(const Mod& left, const Mod& right) {
	return left.val != right.val;
}
bool inline operator <=(const Mod& left, const Mod& right) {
	return left.val <= right.val;
}

Mod inline operator +(const Mod& left, const Mod& right) {
	return left.val + right.val;
}
Mod inline operator *(const Mod& left, const Mod& right) {
	return 1ll * left.val * right.val;
}

int n;

int cnt[_N];
int to[_N][_N], id[_N][_N];

Mod f[_N][_N][_N];

Mod tmp[_N << 1];
Mod mnsw[_N][_N];

bool vis[_N];

int qcnt;
int q[_N];

Mod inline hash(Mod left, Mod right) {
	return left * 19260817 + right;
}

void calc_mnsw(Mod* s, Mod* res, int slen) {
	for (int i = 1; i <= slen; i++) {
		tmp[i] = tmp[i + slen] = s[i];
	}
	int resp = 1;
	for (int i = 1, j, k; i <= slen;) {
		for (j = i, k = i + 1; k <= (slen << 1) && tmp[j] <= tmp[k]; k++) {
			j = (tmp[j] == tmp[k] ? j + 1 : i);
		}
		while (i <= j) {
			i += k - j;
			resp = (i <= slen ? i : resp);
		}
	}
	for (int i = 1; i <= slen; i++) {
		res[i] = tmp[resp + i - 1];
	}
}

bool equals(int left, int right) {
	if (cnt[left] != cnt[right]) {
		return false;
	}
	for (int i = 1; i <= n; i++) {
		if (mnsw[left][i] != mnsw[right][i]) {
			return false;
		}
	}
	return true;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &cnt[i]);
		for (int j = 1; j <= cnt[i]; j++) {
			scanf("%d", &to[i][j]);
			id[i][to[i][j]] = j;
		}
	}
	for (int x = 1; x <= n; x++) {
		for (int i = 1; i <= cnt[x]; i++) {
			f[0][x][i] = cnt[x];
		}
	}
	for (int k = 1; k <= n; k++) {
		for (int x = 1; x <= n; x++) {
			for (int i = 1; i <= cnt[x]; i++) {
				int y = to[x][i];
				for (int j = id[y][x]; j <= cnt[y]; j++) {
					f[k][x][i] = hash(f[k][x][i], f[k - 1][y][j]);
				}
				for (int j = 1; j < id[y][x]; j++) {
					f[k][x][i] = hash(f[k][x][i], f[k - 1][y][j]);
				}
			}
		}
	}
	for (int x = 1; x <= n; x++) {
		calc_mnsw(f[n][x], mnsw[x], cnt[x]);
	}
	bool flag = false;
	for (int x = 1; x <= n; x++) {
		if (!vis[x]) {
			vis[x] = true;
			qcnt = 0;
			q[++qcnt] = x;
			for (int y = x + 1; y <= n; y++) {
				if (!vis[y] && equals(x, y)) {
					vis[y] = true;
					q[++qcnt] = y;
				}
			}
			if (qcnt > 1) {
				for (int i = 1; i <= qcnt; i++) {
					printf("%d ", q[i]);
				}
				puts("");
				flag = true;
			}
		}
	}
	if (!flag) {
		puts("none");
	}
	return 0;
}
```

## Inspiration

我认为这道题的思路总体比较自然。~~首先要读懂复杂的题意~~，然后注意到这是一个复杂结构的相等判断，于是想到使用hash。

核心结论：

- 点的等价可以表示为边序列的相等，然后hash
- 边序列的任意开始可以用最小表示法来做



---

