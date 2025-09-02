# 题目信息

# Two Screens

## 题目描述

这里有两个可以显示大写字母序列的显示屏。初始时，两个屏幕都没有显示任何东西。

每秒钟你可以执行下列两种操作中的一种：

* 选择一个屏幕和一个大写字母，并将该字母添加到该屏幕上显示的序列的末尾；  
* 选择一个屏幕并将该屏幕上的序列复制到另一个屏幕，覆盖另一个屏幕上显示的序列。

你需要计算让第一个屏幕显示序列 $s$，第二个屏幕显示序列 $t$ 所需要花费的最少秒数。

## 说明/提示

【样例解释】

对于第一组数据，以下是一种可能的操作方案：

* 花费 6 秒向第一个屏幕写入序列 GARAGE；
* 花费 1 秒将序列从第一个屏幕复制到第二个屏幕；
* 花费 7 秒向第二个屏幕写入序列 FORSALE。

对于第二组数据，以下是一种可能的操作方案：

* 花费 1 秒向第二个屏幕写入序列 A；
* 花费 1 秒将序列从第二个屏幕复制到第一个屏幕；
* 花费 4 秒向第一个屏幕写入序列 BCDE；
* 花费 4 秒向第二个屏幕写入序列 ABCD。

对于第三组数据，最快的方法是将字母一个一个地写入屏幕，而不进行复制，这需要花费 16 秒。


对于所有测试数据，保证 $1 \le q \le 500$，$1 \le |s|,|t| \le 100$。

翻译来自 [Jason_Ming](https://www.luogu.com.cn/user/1014421)。

## 样例 #1

### 输入

```
3
GARAGE
GARAGEFORSALE
ABCDE
AABCD
TRAINING
DRAINING```

### 输出

```
14
10
16```

# AI分析结果



## 【唯一算法分类】
动态规划

## 【综合分析与结论】

### 核心思路
本题通过动态规划结合广度优先搜索（BFS）的状态转移，预处理字符串前缀关系，求解最小操作时间。关键点在于：
1. **状态定义**：状态 `(a, b)` 表示屏幕A已构造 `s` 的前 `a` 个字符，屏幕B已构造 `t` 的前 `b` 个字符。
2. **预处理前缀匹配**：预处理数组 `max_s_to_t` 和 `max_t_to_s` 分别记录复制操作后能匹配目标字符串的最大前缀长度。
3. **状态转移**：每次操作分为添加字符或复制屏幕，利用预处理数组快速判断复制后能否推进构造目标字符串。

### 难点与解决
- **状态压缩**：通过仅记录前缀长度而非具体字符串，避免状态爆炸。
- **有效复制判断**：预处理前缀数组确保复制操作后能继续构造目标字符串，避免无效转移。
- **BFS优化**：采用队列按时间递增顺序处理状态，保证首次到达终点即为最优解。

### 可视化设计
- **动画效果**：用两个横向条形图表示屏幕A和B的构造进度，每一步操作（添加/复制）以箭头和颜色高亮显示。
- **复古像素风格**：每个字符用8x8像素块表示，复制操作时添加屏幕间箭头动画，并伴随“哔”音效。
- **交互控制**：支持暂停/继续、单步执行，速度调节可观察不同策略的转移路径。

---

## 【最优思路提炼】

1. **前缀预处理**：对每个可能的 `a` 和 `b`，计算复制操作后能匹配目标字符串的最大前缀长度。
2. **BFS状态转移**：每次转移尝试四种操作，仅保留有效且更优的状态。
3. **剪枝优化**：仅在复制后的前缀长度严格增加时才进行转移，避免无效操作。

---

## 【核心代码实现】

```python
from collections import deque

def compute_max_prefix(s, target):
    len_s = len(s)
    len_t = len(target)
    max_prefix = [0] * (len_s + 1)
    for a in range(len_s + 1):
        max_c = min(a, len_t)
        for c in range(max_c, -1, -1):
            if s[:c] == target[:c]:
                max_prefix[a] = c
                break
    return max_prefix

def min_time(s, t):
    len_s, len_t = len(s), len(t)
    max_s_to_t = compute_max_prefix(s, t)
    max_t_to_s = compute_max_prefix(t, s)
    
    INF = float('inf')
    dp = [[INF] * (len_t + 1) for _ in range(len_s + 1)]
    dp[0][0] = 0
    queue = deque([(0, 0)])
    
    while queue:
        a, b = queue.popleft()
        if a == len_s and b == len_t:
            return dp[a][b]
        
        current_time = dp[a][b]
        # Add to A
        if a < len_s and dp[a+1][b] > current_time + 1:
            dp[a+1][b] = current_time + 1
            queue.append((a+1, b))
        # Add to B
        if b < len_t and dp[a][b+1] > current_time + 1:
            dp[a][b+1] = current_time + 1
            queue.append((a, b+1))
        # Copy A to B
        c = max_s_to_t[a]
        if c > b and dp[a][c] > current_time + 1:
            dp[a][c] = current_time + 1
            queue.append((a, c))
        # Copy B to A
        d = max_t_to_s[b]
        if d > a and dp[d][b] > current_time + 1:
            dp[d][b] = current_time + 1
            queue.append((d, b))
    return -1  # unreachable if inputs are valid
```

---

## 【相似题目推荐】

1. [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)  
   **关键点**：字符串构造与分段操作。
   
2. [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)  
   **关键点**：动态规划处理字符增删改的最优操作。

3. [P4052 [JSOI2007]文本生成器](https://www.luogu.com.cn/problem/P4052)  
   **关键点**：动态规划与自动机结合处理字符串生成。

---
处理用时：954.27秒