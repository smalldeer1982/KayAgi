# Tape Programming

## 题目描述

There is a programming language in which every program is a non-empty sequence of "<" and ">" signs and digits. Let's explain how the interpreter of this programming language works. A program is interpreted using movement of instruction pointer (IP) which consists of two parts.

- Current character pointer (CP);
- Direction pointer (DP) which can point left or right;

Initially CP points to the leftmost character of the sequence and DP points to the right.

We repeat the following steps until the first moment that CP points to somewhere outside the sequence.

- If CP is pointing to a digit the interpreter prints that digit then CP moves one step according to the direction of DP. After that the value of the printed digit in the sequence decreases by one. If the printed digit was $ 0 $ then it cannot be decreased therefore it's erased from the sequence and the length of the sequence decreases by one.
- If CP is pointing to "<" or ">" then the direction of DP changes to "left" or "right" correspondingly. Then CP moves one step according to DP. If the new character that CP is pointing to is "<" or ">" then the previous character will be erased from the sequence.

If at any moment the CP goes outside of the sequence the execution is terminated.

It's obvious the every program in this language terminates after some steps.

We have a sequence $ s_{1},s_{2},...,s_{n} $ of "<", ">" and digits. You should answer $ q $ queries. Each query gives you $ l $ and $ r $ and asks how many of each digit will be printed if we run the sequence $ s_{l},s_{l+1},...,s_{r} $ as an independent program in this language.

## 样例 #1

### 输入

```
7 4
1>3>22<
1 3
4 7
7 7
1 7```

### 输出

```
0 1 0 1 0 0 0 0 0 0
2 2 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
2 3 2 1 0 0 0 0 0 0
```

# 题解

## 作者：__gcd (赞：5)

首先，我们可以在 $O(nd)$（$d$ 为数字个数，此处为 $10$）的时间复杂度里求出一段代码的答案，但在多组询问中这样做是不现实的，原因是多组询问做了很多重复的操作。于是我们可以尝试一遍处理出所有信息，然后查询。

注意到此题中 CP 的移动是连续的，这保证了在一段连续的时间之内，CP 的移动在一个固定的连续区间里。所以我们从 $1$ 出发运行，以时间为轴做一个数字输出个数的前缀和，注意为了使程序不中途中止，我们需要在开头补上足够的 $<$。为了适应区间查询，我们需要记录两个数组：$f_{1,i,j}$ 表示第一次准备到达 $i$ 时数字 $j$ 的输出个数，$f_{0,i,j}$ 表示从 $i$ 出发第一次准备往左移动时数字 $j$ 的输出个数。注意两者的叙述是有细微差别的。

于是对于区间 $[l,r]$，我们比较第一次到达 $r+1$ 时的时间和第一次准备从 $l$ 往左走的时间，然后用前缀和相减得到结果。比较时间可以记录时间戳，也可以直接比较元素的大小，因为前缀和的元素是递增的。

注意有一个细节，第一次从 $l$ 往左移出并不一定是以 $l$ 为起点，$l$ 在此之前可能已经被删除。所以我们需要做一个区间赋值，只需要用并查集记录未被赋值的点即可。

细节真的超多。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
using namespace std;
inline int read() {
	int x = 0; bool op = 0;
	char c = getchar();
	while(!isdigit(c))op |= (c == '-'), c = getchar();
	while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return op ? -x : x;
}
const int N = 100010;
const int INF = 1e9;
int n, q, len, pre;
int l[N], r[N], b[N], vis[2][N], f[2][N][10], fa[N]; 
char s[N];
void del(int p) {
	r[l[p]] = r[p]; l[r[p]] = l[p];
	len--;
	return ;
}
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
void unionn(int x, int y) {
	int fx = find(x), fy = find(y);
	if(fx == fy)return ; fa[fy] = fx;
	return ;
} 
void move(int &p, int &dir) {
	int nxt;
	if(isdigit(s[p])) {
		b[s[p] - '0']++; 
		if(s[p] == '0')del(p);
		else s[p]--;
		nxt = (dir == 0) ? l[p] : r[p];
	}
	else {
		if(s[p] == '<')dir = 0;
		else dir = 1;
		nxt = (dir == 0) ? l[p] : r[p];
		if(p && !isdigit(s[nxt]))del(p);
	}
	if(dir == 1 && vis[1][nxt] == 0) {
		for(int i = 0; i < 10; i++)f[1][nxt][i] = b[i];
		vis[1][nxt] = 1;
	}
	if(dir == 0) {
		int j = find(nxt) + 1;
		while(j <= p) {
			vis[0][j] = 1;
			for(int i = 0; i < 10; i++)f[0][j][i] = b[i];
			unionn(j, j - 1); j = find(j) + 1;
		}
	}
	p = nxt;
	return ;
}  
int main() {
	n = read(); q = read();
	s[0] = '>'; scanf("%s", s + 1);
	for(int i = 1; i <= n; i++)fa[i] = i;
	for(int i = 0; i <= n; i++) {
		if(i > 0)l[i] = i - 1;
		r[i] = i + 1;
	} 
	memset(f, 0x3f, sizeof(f));
	int p = 0, dir = 1; len = n;
	while(p <= n && len)move(p, dir);
	while(q--) {
		int l = read(), r = read();
		for(int j = 0; j < 10; j++) {
			printf("%d ", (vis[0][l] ? min(f[0][l][j], f[1][r + 1][j]) : f[1][r + 1][j]) - f[1][l][j]);
		}
		puts("");
	}
	return 0;
}


```


---

## 作者：LinkyChristian (赞：4)

~~杂题清除计划~~

考虑我们将 $1 \sim n$ 的序列整个操作一遍（中途断掉了就跳到下一段，操作前要在最左边加个 $>$ 防止指针从左边掉出去），然后将指针移动的序列记下来。由于每个数字最多被经过 $10$ 次，因此序列长度 $\le 10 \times n$ 。

考虑一个询问 $(l,r)$ , $l,r$ 的操作序列一定是我们之前预处理出的序列的一部分（移动是连续的）。因此考虑直接在序列上使用前缀和求解。

分类讨论：走出 $l,r$ 的方式有两种，一种是直接往右走出去，第二种是往右走然后掉头从左边走出去。

处理这两种情况，记下 $right_{i,j}$ 表示第一次从 $i$ 往右边走出去时第 $j$ 个数输出的次数。记下 $left_{i,j}$ 表示第一次从 $i$ **右边走到左边** 时第 $j$ 个数输出的次数。注意这里是从 $i$ 右边走到左边而不是从 $i$ 走到左边。因为 $i$ 这个位置可能在一开始往右走的时候就被删掉了，对于删除我们使用链表。

对于如何给被删除的数赋值，我们 $nxt_i$ 表示第 $i$ 个数右边第一个 $left$ 没被赋值的数。往左移的时候，对于当前点在链表上的前驱，我们从前驱开始，**在下标上移动**，给 $left$ 没被赋值的数赋值后维护 $nxt_i$ 即可。

最后输出时判断有没有从 $l$ 的左边出来过，分类输出即可。


---

