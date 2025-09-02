# [CEOI 2013] 新宝岛 / Treasure

## 题目背景

翻译自 [CEOI 2013 Day 1](https://ceoi2013.hsin.hr/tasks/tasks_day1.pdf)。

**这是一道 IO 交互题。**

一次地震过后，亚得里亚海出现了一座新岛。在岛上发现了一个特殊装置，名叫“神谕”。尽管没有说明手册，但考古学家和计算机专家的队伍成功地理解了它的行为。

神谕提供了一些有关该岛宝藏位置的信息。该岛被分为一个 $N$ 行 $N$ 列的网格，其中行和列都从 $1$ 到 $N$ 编号。网格中的一些单元格包含宝藏。神谕只会回答以下形式的问题：“给定网格中的一个矩形，在这个矩形中，有多少个单元格包含宝藏？”

**尽管神谕可以回答所有大小的矩形问题，但发现请求的信息越具体（矩形越小），神谕在回答时消耗的能量越多**。更精确地说，如果一个矩形包含 $S$ 个单元格，则神谕将使用 $1 + N \times N - S$ 个单位的能量来回答。

## 题目描述

编写一个程序，通过与神谕交互的方式，确定该岛上所有含有宝藏的单元格的位置。我们不希望在此过程中使用过多的能量，能量使用越少越好。但是也不要求使用的能量数量是最小的，具体得分规则见最后的“说明/提示”。

这是一个交互式任务。您的程序使用标准输出向神谕提问，并通过读取标准输入来获得答案。

- 在程序开始时，它应该读取一个整数 $N$（$2 \leq N \leq 100$），表示网格的大小。
- 要向神谕提问，您的程序应输出一行包含 $4$ 个整数 $R_1$、$C_1$、$R_2$ 和 $C_2$，它们之间由空格分隔，使得 $1 \leq R_1 \leq R_2 \leq N$ 和 $1 \leq C_1 \leq C_2 \leq N$ 成立。如果条件不成立或行格式不正确，则您的程序在该测试运行中将得零分。
- 神谕将响应一个包含单个整数的行 - 包含宝藏的矩形中提供的单元格数。更确切地说，是 $R_1 \leq R \leq R_2$ 且 $C_1 \leq C \leq C_2$ 且位于行 $R$、列 $C$ 的单元格包含宝藏的单元格数（$R$，$C$）。
- 当程序完成提问（已经确定所有宝藏的位置）后，它应在新的一行上输出 `END`。然后，再输出 $N$ 行，每行包含 $N$ 个 `0` 或 `1` 字符的字符串。第 $R$ 行中的第 $C$ 个字符是 `1`，如果该行中列 $C$ 的单元格中有宝藏，则为 `0`，如果没有，则为 `1`。行从顶部到底部编号为 $1$ 到 $N$，列从左到右编号。一旦您的程序输出解决方案，程序的执行将会自动终止。

为了与评分器正确交互，需要在每个问题和写出解决方案后**刷新标准输出**，这是交互题的惯例。

在每个测试运行中，可以假定神谕必然正确回答问题，并且在交互之前宝藏的位置是确定的。换句话说，答案不会取决于程序先前问的问题（不会根据你问的问题来改变答案），它在每个测试点都是固定的。

## 说明/提示

[样例解释](https://www.luogu.com.cn/paste/tpzc0qdt)

每个测试用例得分为 $10$ 分。如果程序的输出不正确，则该测试用例得零分。否则，根据神谕使用的总能量单位 $K$ 来确定分数。

具体而言:
- 如果 $K ≤ \frac{7}{16} N^4 + N^2$，则得 $10$ 分。
- 否则，如果 $K ≤ \frac{7}{16} N^4 + 2N^3$，则得 $8$ 分。
- 否则，如果 $K ≤ \frac{3}{4} N^4$，则得 $4$ 分。
- 否则，如果 $K ≤ N^4$，则得 $1$ 分。
- 否则，得 $0$ 分。

此外，在至少占总分 $40\%$ 的测试数据中，$N$ 将最多为 $20$。

总而言之，**花费的能量越少，你的得分就越高**。

交互库/SPJ 提供者：@[Sprague_Garundy](https://www.luogu.com.cn/user/764746) 。

## 样例 #1

### 输入

```
2
0
1
2```

### 输出

```
1 1 1 1
1 2 1 2
2 1 2 2
END
01
11```

# 题解

## 作者：cff_0102 (赞：5)

学过二维的前缀和吗？

![](https://cdn.luogu.com.cn/upload/image_hosting/cj49001g.png)

正确的，官方正解就是容斥+贪心。

因为要让查询的范围尽量大，所以索性直接贴一个角然后查询 $4$ 次求容斥。重复查询的不需要再查了。

对于每一格，判断它大概所处的位置，然后在上面四种中选择一个最合适（矩形最大）的查询方案，输出。注意如果这一格在中间，可以选一个较好的，虽然判分似乎严了点，但应该还是能过的。

官方代码：

```cpp
// CEOI 2013 - Task: Treasure - Solution
// Author: Luka Kalinovcic

#include <cstdio>
#include <map>

using namespace std;

struct Rect {
  int r1, c1, r2, c2;
  Rect(int r1, int c1, int r2, int c2) : r1(r1), c1(c1), r2(r2), c2(c2) {}
};
bool operator < (Rect const& A, Rect const& B) {
  if (A.r1 != B.r1) return A.r1 < B.r1;
  if (A.c1 != B.c1) return A.c1 < B.c1;
  if (A.r2 != B.r2) return A.r2 < B.r2;
  if (A.c2 != B.c2) return A.c2 < B.c2;
  return 0;
}

int n, cff_0102;
map<Rect, int> memo;

int Sum(int r1, int c1, int r2, int c2) {
  if (r1 == r2) return 0;
  if (c1 == c2) return 0;
  if (r1 != 0 && r2 != n) {
    return Sum(r1, c1, n, c2) + Sum(0, c1, r2, c2) - Sum(0, c1, n, c2);
  }
  if (c1 != 0 && c2 != n) {
    return Sum(r1, c1, r2, n) + Sum(r1, 0, r2, c2) - Sum(r1, 0, r2, n);
  }
  if (r1 != 0 && r1 >= n - r1) {  // r2 == n
    return Sum(0, c1, n, c2) - Sum(0, c1, r1, c2);
  }
  if (r2 != n - 1 && n - r2 > r2) {  // r1 == 0
    return Sum(0, c1, n, c2) - Sum(r2, c1, n, c2);
  }
  if (c1 != 0 && c1 >= n - c1) {  // c2 == n
    return Sum(r1, 0, r2, n) - Sum(r1, 0, r2, c1);
  }
  if (c2 != n - 1 && n - c2 > c2) {  // c1 == 0
    return Sum(r1, 0, r2, n) - Sum(r1, c2, r2, n);
  }
  Rect rect(r1, c1, r2, c2);
  if (memo.count(rect)) return memo[rect];
  printf("%d %d %d %d\n", r1 + 1, c1 + 1, r2, c2);
  fflush(stdout);
  scanf("%d", &memo[rect]);
  return memo[rect];
}

int main() {
  scanf("%d", &n);
  for (int r = 0; r < n; ++r)
    for (int c = 0; c < n; ++c)
      Sum(r, c, r + 1, c + 1);

  printf("END\n");
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      printf("%d", Sum(r, c, r + 1, c + 1));
    }
    printf("\n");
  }

  return 0;
}
```

官方代码给了一个叫 `memo` 的 `map`，来存储输入信息。在 `Sum` 函数的倒数第五行可以看出这个程序确实用了记忆化。记得要用 `fflush(stdout);` 刷新标准输出。还是比较好理解的。

最后感谢@[cff_0102](https://www.luogu.com.cn/user/542457) 供题，以及@[Sprague_Garundy](https://www.luogu.com.cn/user/764746) 提供的交互库和 SPJ。

---

