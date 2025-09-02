# 题目信息

# Cutting Game

## 题目描述

Alice and Bob were playing a game again. They have a grid of size $ a \times b $ ( $ 1 \le a, b \le 10^9 $ ), on which there are $ n $ chips, with at most one chip in each cell. The cell at the intersection of the $ x $ -th row and the $ y $ -th column has coordinates $ (x, y) $ .

Alice made the first move, and the players took turns. On each move, a player could cut several (but not all) rows or columns from the beginning or end of the remaining grid and earn a point for each chip that was on the cut part of the grid. Each move can be described by the character 'U', 'D', 'L', or 'R' and an integer $ k $ :

- If the character is 'U', then the first $ k $ remaining rows will be cut;
- If the character is 'D', then the last $ k $ remaining rows will be cut;
- If the character is 'L', then the first $ k $ remaining columns will be cut;
- If the character is 'R', then the last $ k $ remaining columns will be cut.

Based on the initial state of the grid and the players' moves, determine the number of points earned by Alice and Bob, respectively.

## 说明/提示

Below is the game from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974F/9f1554443f39a3c1eca0a96dffd50920759ede0a.png)On her turn, Alice cut $ 2 $ rows from the bottom and scored $ 2 $ points, then Bob cut $ 1 $ column from the right and scored one point. Note that if Bob had cut $ 1 $ row from the bottom, he would have also scored $ 1 $ point.

## 样例 #1

### 输入

```
6
4 4 3 2
4 1
3 3
2 4
D 2
R 1
4 4 3 3
4 1
3 2
2 3
D 1
L 1
U 2
3 5 3 2
1 3
2 2
3 3
R 2
R 2
6 4 4 2
1 4
2 3
5 3
1 1
R 1
U 1
9 3 2 1
6 1
3 3
D 8
10 10 2 5
7 5
9 1
R 1
L 2
D 1
U 4
D 1```

### 输出

```
2 1
2 0
0 3
1 1
2 0
0 1```

# AI分析结果



### 题目内容中文翻译

#### 切割游戏

## 题目描述

Alice和Bob再次玩游戏。他们有一个大小为 $a \times b$（$1 \le a, b \le 10^9$）的网格，上面有 $n$ 个棋子，每个格子最多一个棋子。坐标为 $(x, y)$ 的格子位于第 $x$ 行第 $y$ 列。

Alice先手，两人轮流操作。每次操作可以切割剩余网格开头或结尾的若干行/列（不能全切），获得被切割区域内的棋子数对应的分数。操作类型由字符（U/D/L/R）和整数 $k$ 描述：

- 'U'：切割前 $k$ 行
- 'D'：切割后 $k$ 行
- 'L'：切割前 $k$ 列
- 'R'：切割后 $k$ 列

根据初始状态和操作序列，计算两人的得分。

---

### 题解对比与结论

#### 核心思路总结
1. **边界维护**：维护当前棋盘的四边界（上下左右），通过调整边界模拟切割操作
2. **双指针+排序**：将棋子按行列排序，使用双指针快速定位被切割区域
3. **去重机制**：用哈希表或标记数组避免重复统计已删除棋子
4. **二分优化**：在有序数据中快速查找符合当前边界的棋子

#### 高星题解推荐

##### 1. DrAlfred（4.5星）
**亮点**：
- 双指针维护行列指针区间
- 二分统计有效区间内的棋子数
- 时间复杂度最优（O(n log n)）

**关键代码**：
```cpp
auto count = [&](vector<int> &v, int l, int r) -> int {
    auto L = lower_bound(v.begin(), v.end(), l);
    auto R = upper_bound(v.begin(), v.end(), r);
    return R - L;
};
// 操作时遍历排序后的行列，用count统计有效点
```

##### 2. Genshin_ZFYX（4星）
**亮点**：
- 结构体数组排序+四指针滑动窗口
- 简洁直观，适合快速实现

**关键代码**：
```cpp
// 维护四个指针ku,kd,kl,kr
for(;_Ls[ku].x<u+k&&ku<=kd;ku++) 
    if(在当前棋盘内) 统计得分
```

##### 3. Austin0116（4星）
**亮点**：
- 双set维护行列视图
- 迭代器直接操作删除区域
- 利用set自动排序特性

**关键代码**：
```cpp
while(!s1.empty() && s1.begin()->first < new_bound) {
    auto p = *s1.begin();
    s1.erase(p); s2.erase({p.second, p.first});
    sum += 1;
}
```

---

### 关键技巧与拓展

#### 调试心得
- **边界条件**：注意切割后的棋盘尺寸不能为0（题目保证）
- **坐标映射**：行列操作后要同步更新另一方向的坐标范围
- **去重陷阱**：同一棋子可能在多个操作中被多次扫描，必须用哈希表标记

#### 相似题目推荐
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908) - 双指针/分治思想
2. [P3384 树链剖分](https://www.luogu.com.cn/problem/P3384) - 区间维护与映射
3. [P1972 数颜色](https://www.luogu.com.cn/problem/P1972) - 滑动窗口与去重统计

---

### 最优题解代码（DrAlfred）

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b, n, m;
    cin >> a >> b >> n >> m;
    vector<pair<int, int>> points(n);
    map<int, vector<int>> rows, cols;
    
    // 读取并预处理行列数据
    for (auto& [x, y] : points) {
        cin >> x >> y;
        rows[x].push_back(y);
        cols[y].push_back(x);
    }
    
    // 行列排序
    deque<int> row_order, col_order;
    for (auto& [x, ys] : rows) {
        row_order.push_back(x);
        sort(ys.begin(), ys.end());
    }
    for (auto& [y, xs] : cols) {
        col_order.push_back(y);
        sort(xs.begin(), xs.end());
    }
    
    // 边界初始化
    int u = 1, d = a, l = 1, r = b;
    int score[2] = {0, 0};
    
    // 处理每个操作
    for (int i = 0; i < m; ++i) {
        char op; int k;
        cin >> op >> k;
        int cnt = 0;
        
        if (op == 'U') { 
            int new_u = u + k;
            while (!row_order.empty() && row_order.front() < new_u) {
                int x = row_order.front();
                row_order.pop_front();
                auto& ys = rows[x];
                auto it = lower_bound(ys.begin(), ys.end(), l);
                auto jt = upper_bound(ys.begin(), ys.end(), r);
                cnt += jt - it;
            }
            u = new_u;
        }
        // 类似处理D/L/R操作...
        
        score[i % 2] += cnt;
    }
    cout << score[0] << " " << score[1] << "\n";
}
```

---
处理用时：53.99秒