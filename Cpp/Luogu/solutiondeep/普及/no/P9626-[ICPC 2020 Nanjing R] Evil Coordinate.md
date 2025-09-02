# 题目信息

# [ICPC 2020 Nanjing R] Evil Coordinate

## 题目描述

A robot is standing on an infinite 2-dimensional plane. Programmed with a string $s_1s_2\cdots s_n$ of length $n$, where $s_i \in \{\text{`U'}, \text{`D'}, \text{`L'}, \text{`R'}\}$, the robot will start moving from $(0, 0)$ and will follow the instructions represented by the characters in the string.

More formally, let $(x, y)$ be the current coordinate of the robot. Starting from $(0, 0)$, the robot repeats the following procedure $n$ times. During the $i$-th time:

- If $s_i = \text{`U'}$ the robot moves from $(x, y)$ to $(x, y+1)$;
- If $s_i = \text{`D'}$ the robot moves from $(x, y)$ to $(x, y-1)$;
- If $s_i = \text{`L'}$ the robot moves from $(x, y)$ to $(x-1, y)$;
- If $s_i = \text{`R'}$ the robot moves from $(x, y)$ to $(x+1, y)$.-

However, there is a mine buried under the coordinate $(m_x, m_y)$. If the robot steps onto $(m_x, m_y)$ during its movement, it will be blown up into pieces. Poor robot!

Your task is to rearrange the characters in the string in any order, so that the robot will not step onto $(m_x, m_y)$.

## 样例 #1

### 输入

```
5
1 1
RURULLD
0 5
UUU
0 3
UUU
0 2
UUU
0 0
UUU
```

### 输出

```
LDLRUUR
UUU
Impossible
Impossible
Impossible
```

# AI分析结果



### 算法分类
**构造**

### 综合分析与结论
题目要求通过重排移动指令，使机器人路径避开地雷点。核心思路是枚举所有可能的移动顺序，并验证其合法性。正确解法需满足以下条件：
1. 排除终点为地雷点的情况。
2. 枚举方向的全排列，保证每个方向的所有移动连续处理。
3. 模拟每一步移动，实时检查是否经过地雷点。

### 精选题解

#### 题解：lraM41（5星）
**关键亮点**  
- 正确枚举所有方向的全排列顺序，逐次模拟每一步移动。
- 通过实时坐标更新和条件判断，确保路径不经过地雷点。
- 代码简洁，逻辑清晰，正确处理坐标变化。

**核心代码**  
```cpp
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, 1, -1}; // 对应 L, R, U, D 的方向
int a[4] = {L_count, R_count, U_count, D_count}; // 统计各方向数量
int nx[4] = {0, 1, 2, 3}; // 初始顺序 L, R, U, D

do {
    int x = 0, y = 0; // 起点
    bool valid = true;
    for (int dir : nx) { // 按当前排列顺序处理方向
        for (int step = 0; step < a[dir]; step++) {
            x += dx[dir];
            y += dy[dir];
            if (x == mx && y == my) { // 中途踩雷
                valid = false;
                break;
            }
        }
        if (!valid) break;
    }
    if (valid) { // 找到合法排列，输出结果
        for (int d : nx) {
            for (int i = 0; i < a[d]; i++) cout << "LRUD"[d];
        }
        return;
    }
} while (next_permutation(nx, nx + 4));
```

### 关键思路总结
1. **全排列枚举方向顺序**：通过枚举 U/D/L/R 的 24 种排列顺序，覆盖所有可能的移动组合。
2. **逐步骤模拟路径**：在每一步移动中实时更新坐标，严格检查是否经过地雷点。
3. **剪枝优化**：一旦某方向处理时路径非法，立即终止后续模拟，减少冗余计算。

### 拓展练习
1. **P1706 全排列问题**（基础全排列枚举）
2. **P1036 选数**（DFS 枚举组合）
3. **P1223 排队接水**（贪心排序构造最优序列）

### 个人心得摘录
- **模拟细节决定正确性**：必须严格处理每一步坐标更新，不能忽略中间状态。
- **方向处理顺序的陷阱**：全排列枚举方向顺序的合理性需结合路径几何特征分析。
- **代码可读性优先**：清晰的变量命名和逻辑分段能显著降低调试难度。

---
处理用时：224.56秒