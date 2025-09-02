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



# Two Screens

## 题目描述

这里有两个可以显示大写字母序列的显示屏。初始时，两个屏幕都没有显示任何东西。

每秒钟你可以执行下列两种操作中的一种：

* 选择一个屏幕和一个大写字母，并将该字母添加到该屏幕上显示的序列的末尾；  
* 选择一个屏幕并将该屏幕上的序列复制到另一个屏幕，覆盖另一个屏幕上显示的序列。

你需要计算让第一个屏幕显示序列 $s$，第二个屏幕显示序列 $t$ 所需要花费的最少秒数。

## 样例解释（略）

---

### 关键思路总结

本题的难点在于动态规划状态的设计与转移条件的处理。核心思路如下：

1. **状态定义**：用 `dp[i][j][k]` 表示第一个屏幕已构造 `s` 的前 `i` 个字符，第二个屏幕构造了 `t` 的前 `j` 个字符，最后一次操作类型为 `k`（0-无复制，1-从A复制到B，2-从B复制到A）时的最小时间。

2. **转移条件**：
   - **添加操作**：直接按顺序添加字符到对应屏幕。
   - **复制操作**：需确保复制后的屏幕内容与目标字符串的前缀匹配。例如，复制A到B时，要求 `s` 的前 `i` 字符等于 `t` 的前 `i` 字符。

3. **预处理公共前缀**：提前计算所有可能的公共前缀长度，以快速判断复制操作的合法性。

### 核心代码实现

```python
def main():
    import sys
    import heapq
    q = int(sys.stdin.readline())
    for _ in range(q):
        s = sys.stdin.readline().strip()
        t = sys.stdin.readline().strip()
        len_s, len_t = len(s), len(t)
        max_len = max(len_s, len_t)
        prefix_eq = [False] * (max_len + 1)
        for i in range(max_len + 1):
            if i > len_s or i > len_t:
                prefix_eq[i] = False
            else:
                prefix_eq[i] = (s[:i] == t[:i])
        
        INF = float('inf')
        dp = [[[INF] * 3 for _ in range(len_t + 1)] for __ in range(len_s + 1)]
        dp[0][0][0] = 0
        heap = []
        heapq.heappush(heap, (0, 0, 0, 0))
        visited = set()
        ans = INF
        while heap:
            time, i, j, k = heapq.heappop(heap)
            if (i, j, k) in visited:
                continue
            visited.add((i, j, k))
            if i == len_s and j == len_t:
                ans = min(ans, time)
                break  # 优先队列保证首次到达即最优
            # 添加操作
            if i < len_s:
                new_time = time + 1
                if new_time < dp[i+1][j][k]:
                    dp[i+1][j][k] = new_time
                    heapq.heappush(heap, (new_time, i+1, j, k))
            if j < len_t:
                new_time = time + 1
                if new_time < dp[i][j+1][k]:
                    dp[i][j+1][k] = new_time
                    heapq.heappush(heap, (new_time, i, j+1, k))
            # 复制A到B
            if i <= len_s and i <= len_t and prefix_eq[i]:
                new_i, new_j = i, i
                new_k = 1
                new_time = time + 1
                if new_time < dp[new_i][new_j][new_k]:
                    dp[new_i][new_j][new_k] = new_time
                    heapq.heappush(heap, (new_time, new_i, new_j, new_k))
            # 复制B到A
            if j <= len_s and j <= len_t and prefix_eq[j]:
                new_i, new_j = j, j
                new_k = 2
                new_time = time + 1
                if new_time < dp[new_i][new_j][new_k]:
                    dp[new_i][new_j][new_k] = new_time
                    heapq.heappush(heap, (new_time, new_i, new_j, new_k))
        print(ans if ans != INF else len_s + len_t)
```

### 推荐相似题目

1. **P1279 字串距离** - 涉及字符串操作与动态规划优化。
2. **P1140 相似基因** - 利用动态规划处理字符串匹配问题。
3. **P2758 编辑距离** - 经典动态规划处理字符操作问题。

---
处理用时：293.73秒