# 题目信息

# Ohana Cleans Up

## 题目描述

Ohana Matsumae is trying to clean a room, which is divided up into an $ n $ by $ n $ grid of squares. Each square is initially either clean or dirty. Ohana can sweep her broom over columns of the grid. Her broom is very strange: if she sweeps over a clean square, it will become dirty, and if she sweeps over a dirty square, it will become clean. She wants to sweep some columns of the room to maximize the number of rows that are completely clean. It is not allowed to sweep over the part of the column, Ohana can only sweep the whole column.

Return the maximum number of rows that she can make completely clean.

## 说明/提示

In the first sample, Ohana can sweep the 1st and 3rd columns. This will make the 1st and 4th row be completely clean.

In the second sample, everything is already clean, so Ohana doesn't need to do anything.

## 样例 #1

### 输入

```
4
0101
1000
1111
0101
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
111
111
111
```

### 输出

```
3
```

# AI分析结果



# Ohana Cleans Up

## 题目描述

Ohana Matsumae 正在打扫一个被划分为 $n \times n$ 网格的房间。每个格子初始是干净或脏的。Ohana 可以用扫帚清扫整列格子，每次清扫会翻转该列所有格子的状态（干净变脏，脏变干净）。要求通过若干次列清扫操作后，使得完全干净的行数最大化。输出这个最大行数。

## 输入格式

第一行输入整数 $n$，接着输入 $n$ 行字符串表示初始网格状态（0 表示干净，1 表示脏）。

## 输出格式

输出一个整数表示最大全干净行数。

## 样例 #1

### 输入
```
4
0101
1000
1111
0101
```

### 输出
```
2
```

## 样例 #2

### 输入
```
3
111
111
111
```

### 输出
```
3
```

---

**算法分类**：字符串（基于哈希统计频率）

---

### 题解综合分析

所有题解的核心思路均基于**行相同性原理**：若两行初始状态相同，则通过相同列翻转操作后，这两行状态仍然相同。因此，要使某行变为全0，所有与其初始状态相同的行都会变为全0。问题转化为统计初始行中出现次数最多的行模式。

#### 关键思路与技巧
1. **哈希表统计**：将每行视为字符串，用哈希表统计出现频率。
2. **时间复杂度优化**：使用 `unordered_map` 替代 `map` 可将复杂度从 $O(n \log n)$ 优化至 $O(n)$。
3. **关键性质**：只有相同初始行才能同步变为全0行。

---

### 高星题解推荐

#### 题解1（作者：きりと，4星）
**亮点**：代码简洁，思路明确，直接使用 `map` 统计字符串频率。
```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int> mp;
int main() {
    int n, maxn=0; cin >> n;
    for(int i=1; i<=n; i++) {
        string s; cin >> s;
        maxn = max(maxn, ++mp[s]);
    }
    cout << maxn;
}
```

#### 题解4（作者：wbs200，4星）
**亮点**：使用 `unordered_map` 提升效率，代码简洁高效。
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    int n; cin >> n;
    unordered_map<string, int> cnt;
    while(n--) {
        string s; cin >> s;
        cnt[s]++;
    }
    int ans = 0;
    for (auto [k, v] : cnt) ans = max(ans, v);
    cout << ans;
}
```

---

### 类似题目推荐
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102) - 哈希统计频率
2. [P3405 [USACO09DEC]Cities and States S](https://www.luogu.com.cn/problem/P3405) - 字符串哈希处理
3. [P2957 [USACO09OCT]Barn Echoes G](https://www.luogu.com.cn/problem/P2957) - 字符串模式匹配

---
处理用时：103.49秒