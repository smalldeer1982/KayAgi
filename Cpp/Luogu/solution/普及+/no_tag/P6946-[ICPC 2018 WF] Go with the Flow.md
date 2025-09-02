# [ICPC 2018 WF] Go with the Flow

## 题目描述

在字体排印学中，“川流”是由单词之间的间隙组成的连续几列的空格。如图所示为几个用红色高亮标出的“川流”（文本被有意模糊处理来凸显川流）：

![img](https://cdn.luogu.com.cn/upload/image_hosting/vd2s7f3r.png)

知名川流机构 Flo Ng 希望他在新的关于世界河流的书上出现尽可能长的川流。他会使用一种单一字宽的字体（每个字母和空格都具有相同的宽度）且左对齐，单词之间恰用一个空格分隔。对 Flo 来说，一条“川流”指的是连续几行里的空格，且相邻空格在行里出现的位置的距离不超过 $1$。川流不能包含末尾的空格。每行的单词都必须尽可能地紧凑，但不能有单词被拆到两行里。行宽至少不能短于文本中最长的一个单词。下图是同一个文本使用不同行宽的一个例子。

![img](https://cdn.luogu.com.cn/upload/image_hosting/jgci4wvf.png)

给定文本，你需要求出一个行宽使得该文本最长的川流尽可能长。

## 样例 #1

### 输入

```
21
The Yangtze is the third longest
river in Asia and the longest in
the world to flow
entirely in one country
```

### 输出

```
15 5
```

## 样例 #2

### 输入

```
25
When two or more rivers meet at
a confluence other than the sea
the resulting merged river takes
the name of one of those rivers
```

### 输出

```
21 6
```

# 题解

## 作者：LJY_ljy (赞：2)

updated on 2025.4.12: 感谢 @yellow_mt 提醒，已经将 49 行代码修改。

本代码需要开 -O2 优化通过。

---


考虑枚举行宽后模拟。

由于符合条件的行宽的范围为 $\displaystyle [\max_{1 \leq i \leq n}{len[i]}, \sum_{i = 1}^n len[i] + n - 1]$ （注意空格也占据一个字符宽度）, 其中 $len[i]$ 表示第 $i$ 个字符串的长度，故可以得到行宽范围区间最大长度近似为 $2500 \times 80 = 2 \times 10^5$, 故可以判断出，对于每一个行宽，判断最长川流长度的算法的时间复杂度是 $\mathrm{O}(n)$ 且需要常数较小。

首先，很容易在 $\mathrm{O}(n)$ 的时间复杂度下计算出每个空格在行中的位置（根据题目要求，**一行的最后是没有空格的**）。通过不断往某一行中加字符串，如果不能加就换行。如果加了**某个字符串**后还能再加一个字符串，则紧跟着**该字符串**的空格可以被记录。

得到每一行的空格的位置后，我们设 $cnt[i][j]$ 表示 第 $1 \sim i$ 行中，以第 $i$ 行，位置为 $j$ 的空格结尾的最长川流长度，$G[i][j]$ 表示第 $i$ 行的第 $j$ 个位置是否为符合条件的空格（是，则值为 $1$；否则为 $0$）。

则可以得到如下转移表达式：

$$
cnt[i][j] = \max \begin{cases}
  cnt[i - 1][j - 1] + 1 & if \ G[i - 1][j - 1]   \\
  cnt[i - 1][j] + 1 & if\ G[i - 1][j] \\
  cnt[i - 1][j + 1] + 1 & if \ G[i - 1][j + 1] \\
  1 & else
  \end{cases}
$$

答案即为 $\max\{cnt[i][j]\}$.

但是这样开 $cnt$ 数组是开不下的，故我们考虑直接删去第一维（由于两个符合条件的空格之间的距离至少为 $2$, 故 $cnt[j]$ 从 $cnt[j - 1]$ 转移时不会受到同行空格的影响）。

同样，$G$ 数组也是开不下的，但是如果使用滚动数组，每次将 **所有** $j$ 的状态都赋值过去的话，常数会达到 $80$, 从而导致无法通过。

故我们只用赋值两行中存有空格的 $j$。用 $a, b$ 两个数组分别记录第 $i - 1$ 和 $i$ 行所有空格的位置。当 $cnt$ 数组处理完第 $i$ 行后，将 $a$ 数组内所有元素的标记去除，并将 $b$ 数组内的所有元素打上标记。

考虑到行宽在变化时 $cnt$ 数组需要清零但也不能每次将数组内的元素均清零，故用一个数组记录每个行宽下所有空格在对应行中的位置，然后只将这些位置的 $cnt$ 清零即可。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100;
const int MAXM = 3000;
char str[MAXN];
int n, len[MAXM], sum, maxx, cnt[MAXN * MAXM], ans, ansx, aa[MAXM], bb[MAXM];
int G[MAXM]; 
bool used[MAXN * MAXM];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> str + 1;
		len[i] = strlen(str + 1);
		maxx = max(maxx, len[i]); 
		sum += len[i];
	}	
	for (int gap = maxx; gap < sum + n; gap++) {
		int maxx = 0;
		int j = 1, Len = 0, eid1 = 0, eid = 0;
		int len1 = 0, len2 = 0;
		while (j <= n) {
			++eid1;
			while (Len + len[j] <= gap && j <= n) {
				Len = Len + len[j] + 1;
				if (Len + len[j + 1] <= gap && j < n) {
					G[++eid] = Len;
					bb[++len2] = Len;
					int A = 0;
					if (used[Len - 1]) A = max(A, cnt[Len - 1]);
					if (used[Len]) A = max(A, cnt[Len]); 
					if (used[Len + 1]) A = max(A, cnt[Len + 1]);
					cnt[Len] = A + 1;
					maxx = max(maxx, cnt[Len]);
				}
				j++;
			}
			Len = 0;
			for (int i = 1; i <= len1; i++) used[aa[i]] = false;
			for (int i = 1; i <= len2; i++) used[bb[i]] = true;
			len1 = len2;
			for (int i = 1; i <= len2; i++) aa[i] = bb[i];
			len2 = 0;
		}
		for (int i = 1; i <= len1; i++) used[aa[i]] = false;
		for (int i = 1; i <= eid; i++) cnt[G[i]] = 0;
		if (maxx > ans) {
			ans = maxx;
			ansx = gap;
		}
	}
	cout << ansx << " " << ans << endl;
	return 0;
} 
```

---

