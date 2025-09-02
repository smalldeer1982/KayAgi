# Problem Set

## 题目描述

给定两个序列 $a,b$ ， 请判断是否有一种方案，满足可以用 $a$ 序列中的元素经过一定排序组成序列 $b$ 。

## 样例 #1

### 输入

```
5
3 1 4 1 5
3
5 4 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
7
100 200 500 700 1200 1600 2000
6
100 200 500 700 1600 1600```

### 输出

```
NO```

## 样例 #3

### 输入

```
1
800
5
100 100 100 100 100```

### 输出

```
NO```

## 样例 #4

### 输入

```
15
1 2 2 3 3 3 4 4 4 4 5 5 5 5 5
9
5 4 3 2 1 2 3 4 5```

### 输出

```
YES```

# 题解

## 作者：Ray662 (赞：1)

[洛谷 传送门](https://www.luogu.com.cn/problem/AT_code_festival_2017_qualb_b) | [AtCoder 传送门](https://atcoder.jp/contests/code-festival-2017-qualb/tasks/code_festival_2017_qualb_b)

[更好的阅读体验](https://www.luogu.com.cn/blog/sunrize/codefestival2017qualbb-li-ti-xie)

题目大意：能否从含有 $n$ 个数的序列 $a$ 中选出 $m$ 个数，使得这 $m$ 个数的某一种排列能和 $b$ 序列等价。

$n, m \le 2 \times 10^5$

$a_i, b_i \le 10^9$

---

这里设一个数 $x$ 在 $a$ 序列中的出现次数为 $A_x$，在 $b$ 序列中的出现次数为 $B_x$。

考虑一个很好理解的性质：**若回答为 `YES`，则对于任意一个 $x$，都有 $A_x \ge B_x$**。

这很好证明。

由于 $a_i$ 的上限为 $10^9$，开数组存出现次数显然不现实，这里使用 map。

---

### map

map 的原理是[**映射**](https://baike.baidu.com/item/%E6%98%A0%E5%B0%84/20402621?fromModule=lemma_sense-layer#viewPageContent)，和数组的原理差不多，$T[x]$ 便可查询映射后的值。

至此，这道题便得以解决。

---

复杂度 $O(\max(n, m))$。

代码很短，不到 $20$ 行。

```cpp
#include <bits/stdc++.h>
#define _for(i, a, b)  for (int i = (a); i <= (b); i ++ )
using namespace std;
const int N = 2e5 + 5;
int n, m, a[N], b[N];
map<int, int> T;
int main() {
	cin >> n;
	_for (i, 1, n)  cin >> a[i], T[a[i]] ++ ;  // a[i] 的出现次数，用 map 记录 
	cin >> m;
	_for (i, 1, m) {
		cin >> b[i];
		if (! T[b[i]]) { puts("NO"); return 0; }  // 如果 a 中的 b[i] 值已经花光了，那么 NO 
		T[b[i]] -- ;  // 更新次数 
	}
	puts("YES");  // 剩下的情况都是 YES 
	return 0;
}
```

---

