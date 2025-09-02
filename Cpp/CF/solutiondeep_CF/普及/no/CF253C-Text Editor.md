# 题目信息

# Text Editor

## 题目描述

Vasya is pressing the keys on the keyboard reluctantly, squeezing out his ideas on the classical epos depicted in Homer's Odysseus... How can he explain to his literature teacher that he isn't going to become a writer? In fact, he is going to become a programmer. So, he would take great pleasure in writing a program, but none — in writing a composition.

As Vasya was fishing for a sentence in the dark pond of his imagination, he suddenly wondered: what is the least number of times he should push a key to shift the cursor from one position to another one?

Let's describe his question more formally: to type a text, Vasya is using the text editor. He has already written $ n $ lines, the $ i $ -th line contains $ a_{i} $ characters (including spaces). If some line contains $ k $ characters, then this line overall contains $ (k+1) $ positions where the cursor can stand: before some character or after all characters (at the end of the line). Thus, the cursor's position is determined by a pair of integers $ (r,c) $ , where $ r $ is the number of the line and $ c $ is the cursor's position in the line (the positions are indexed starting from one from the beginning of the line).

Vasya doesn't use the mouse to move the cursor. He uses keys "Up", "Down", "Right" and "Left". When he pushes each of these keys, the cursor shifts in the needed direction. Let's assume that before the corresponding key is pressed, the cursor was located in the position $ (r,c) $ , then Vasya pushed key:

- "Up": if the cursor was located in the first line ( $ r=1 $ ), then it does not move. Otherwise, it moves to the previous line (with number $ r-1 $ ), to the same position. At that, if the previous line was short, that is, the cursor couldn't occupy position $ c $ there, the cursor moves to the last position of the line with number $ r-1 $ ;
- "Down": if the cursor was located in the last line ( $ r=n $ ), then it does not move. Otherwise, it moves to the next line (with number $ r+1 $ ), to the same position. At that, if the next line was short, that is, the cursor couldn't occupy position $ c $ there, the cursor moves to the last position of the line with number $ r+1 $ ;
- "Right": if the cursor can move to the right in this line ( $ c&lt;a_{r}+1 $ ), then it moves to the right (to position $ c+1 $ ). Otherwise, it is located at the end of the line and doesn't move anywhere when Vasya presses the "Right" key;
- "Left": if the cursor can move to the left in this line ( $ c&gt;1 $ ), then it moves to the left (to position $ c-1 $ ). Otherwise, it is located at the beginning of the line and doesn't move anywhere when Vasya presses the "Left" key.

You've got the number of lines in the text file and the number of characters, written in each line of this file. Find the least number of times Vasya should push the keys, described above, to shift the cursor from position $ (r_{1},c_{1}) $ to position $ (r_{2},c_{2}) $ .

## 说明/提示

In the first sample the editor contains four lines. Let's represent the cursor's possible positions in the line as numbers. Letter $ s $ represents the cursor's initial position, letter $ t $ represents the last one. Then all possible positions of the cursor in the text editor are described by the following table.

123

12

123s567

1t345

One of the possible answers in the given sample is: "Left", "Down", "Left".

## 样例 #1

### 输入

```
4
2 1 6 4
3 4 4 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
10 5 6 4
1 11 4 2
```

### 输出

```
6
```

## 样例 #3

### 输入

```
3
10 1 10
1 10 1 1
```

### 输出

```
3
```

# AI分析结果



### 题目重述
# 文本编辑器

## 题目描述

Vasya 正在用文本编辑器写文章，已输入 $n$ 行文本，第 $i$ 行包含 $a_i$ 个字符（含空格）。光标位置由 $(r,c)$ 表示，其中 $r$ 是行号，$c$ 是行内位置（从 1 开始计数）。光标移动规则如下：

- **上移**：若当前不在首行，则移动到上一行的同一列位置，若上一行较短则移动到行末。
- **下移**：若当前不在末行，则移动到下一行的同一列位置，若下一行较短则移动到行末。
- **左/右移**：常规左右移动，无法越界。

求从 $(r_1,c_1)$ 移动到 $(r_2,c_2)$ 的最少按键次数。

---

### 算法分类
**广度优先搜索 BFS**

---

### 题解分析与结论

#### 核心思路对比
各题解主要分为两类：
1. **BFS 标准解法**：处理光标移动时的行末修正逻辑，通过状态转移遍历所有可能路径。
2. **枚举中间行贪心法**：通过枚举中间行计算垂直移动总步数，结合水平位置限制求最小值。

#### 解决难点
- **BFS 实现难点**：正确处理上下移动时的行末修正，避免状态重复访问。
- **贪心法正确性**：证明通过中间行枚举能覆盖最优路径，需数学验证路径最优性。

#### 最优思路
**枚举中间行法**（tongziyu 的解法）：
1. **垂直移动优化**：枚举中间行 $i$，总垂直步数为 $|i-r_1| + |i-r_2|$。
2. **水平位置修正**：在移动路径经过的所有行中，光标列数被限制为这些行的最小可能值。
3. **时间复杂度**：$O(n)$，显著优于 BFS 的 $O(n \cdot \max(a_i))$。

---

### 精选题解

#### 题解1：tongziyu（⭐⭐⭐⭐⭐）
**关键亮点**：  
- 独创性提出枚举中间行的贪心思路，时间复杂度优化到 $O(n)$。  
- 正确性验证覆盖所有测试样例，数学证明路径最优性。  

**核心代码**：
```cpp
int main() {
    // 输入处理略
    int ans = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        int vertical = abs(i - r1) + abs(i - r2);
        int c = c1;
        for (int j = min({r1, i, r2}); j <= max({r1, i, r2}); ++j)
            c = min(c, a[j] + 1); // 水平位置修正
        ans = min(ans, vertical + abs(c - c2));
    }
    cout << ans;
}
```

#### 题解2：_Gabriel_（⭐⭐⭐⭐）
**关键亮点**：  
- 标准 BFS 实现，正确处理行末修正逻辑。  
- 状态标记清晰，代码可读性强。  

**核心代码**：
```cpp
queue<node> q;
q.push({sx, sy, 0});
vis[sx][sy] = 1;
while (!q.empty()) {
    node u = q.front();
    if (到达目标) 输出步数;
    for (移动方向) {
        int ny = 移动后的列;
        ny = min(ny, a[目标行]); // 行末修正
        if (合法且未访问) {
            标记并入队;
        }
    }
}
```

#### 题解3：封禁用户（⭐⭐⭐⭐）
**关键亮点**：  
- 使用预处理优化，直接计算移动后的合法位置。  
- 代码简洁高效，内存管理合理。  

**核心代码**：
```cpp
if (kx != n) {
    int target_col = min(ky, a[kx+1] + 1); // 预处理修正列
    if (未访问) 更新距离并入队;
}
```

---

### 关键技巧总结
1. **贪心枚举**：通过中间行枚举将二维路径问题转化为一维优化，适用于行列独立影响的场景。
2. **行末修正公式**：`min(c, a[j]+1)` 确保光标位置始终合法。
3. **状态压缩**：BFS 中通过预处理目标行最大列数，减少运行时判断。

---

### 类似题目推荐
1. [P1144 迷宫问题](https://www.luogu.com.cn/problem/P1144) - 基础 BFS 路径搜索。
2. [P1219 八数码](https://www.luogu.com.cn/problem/P1379) - 状态空间搜索与哈希处理。
3. [P3958 奶酪](https://www.luogu.com.cn/problem/P3958) - 三维空间中的贪心路径枚举。

---
处理用时：194.11秒