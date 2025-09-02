# 题目信息

# Game

## 题目描述

Vasya and Petya have invented a new game. Vasya takes a stripe consisting of $ 1×n $ square and paints the squares black and white. After that Petya can start moves — during a move he may choose any two neighboring squares of one color and repaint these two squares any way he wants, perhaps in different colors. Petya can only repaint the squares in white and black colors. Petya’s aim is to repaint the stripe so that no two neighboring squares were of one color. Help Petya, using the given initial coloring, find the minimum number of moves Petya needs to win.

## 说明/提示

In the first sample Petya can take squares 1 and 2. He repaints square 1 to black and square 2 to white.

In the second sample Petya can take squares 2 and 3. He repaints square 2 to white and square 3 to black.

## 样例 #1

### 输入

```
6
111010
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
10001
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7
1100010
```

### 输出

```
2
```

## 样例 #4

### 输入

```
5
00100
```

### 输出

```
2
```

# AI分析结果



### 算法分类
**贪心**

### 题解思路与难点
题目要求将给定的01字符串转换为相邻字符不同的形式，且每次操作只能修改相邻两个相同字符。核心思路是：最终字符串只能是两种形式（如0101...或1010...），统计原字符串与这两种目标的差异数，取较小值作为答案。

**关键点**：
1. **目标形式唯一性**：最终只能是交替形式，故仅需比较两种可能的目标。
2. **差异数计算**：原字符串与两种目标的不同位置数即为需要修改的次数。
3. **操作等价性**：每次操作可以修复两个相邻差异，因此总操作次数等于差异数的最小值。

### 题解评分（≥4星）
1. **Mr_WA的大号（5星）**：思路清晰，直接统计差异数，代码简洁高效。
2. **chengni（4星）**：逻辑明确，逐字符比较，但生成目标方式稍显冗余。
3. **Great_Influence（4星）**：使用bitset优化异或操作，代码较复杂但思路新颖。

### 最优思路提炼
**核心技巧**：比较原字符串与两种交替模式（0开头和1开头）的差异数，取较小值。差异数即为所需操作次数，因每次操作可处理两个相邻差异。

### 同类型题与套路
- **套路**：目标状态有限的题目，可枚举所有可能目标，计算差异取最优。
- **类似题目**：  
  1. CF266B（队列变换）  
  2. CF1294C（构造交替序列）  
  3. Luogu P1055（字符串交替检测）

### 个人心得摘录
“发现最终只有两种可能目标，直接统计差异即可。无需模拟操作，贪心取最优。” —— Mr_WA的大号

### 算法可视化
**动画方案**：
1. **初始状态**：显示原字符串，用红/绿标注差异位置。
2. **目标生成**：左右分屏展示两种交替目标（0101...和1010...）。
3. **差异统计**：动态高亮每个字符与目标的匹配情况，统计差异数。
4. **操作模拟**：用箭头连接相邻差异，每次操作消除两个差异，计数减少。
5. **结果展示**：取较小差异数，显示最终操作次数。

**复古像素风格**：
- **颜色方案**：红（差异）、绿（匹配）、黄（操作高亮）。
- **音效**：操作成功时播放8-bit音效，差异消除时触发连击奖励音。

### 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, ans1 = 0, ans2 = 0;
    string s;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        char target = (i % 2) + '0'; // 目标A：0开头交替
        if (s[i] == target) ans1++;
        else ans2++; // ans2统计与目标B的匹配数
    }
    cout << min(ans1, ans2);
    return 0;
}
```

### 结论
题目本质是贪心枚举有限目标，差异数直接决定操作次数。所有题解均通过差异数比较实现，正确性由问题性质保证。

---
处理用时：476.39秒