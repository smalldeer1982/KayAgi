# 题目信息

# Yet Another Array Partitioning Task

## 题目描述

An array $ b $ is called to be a subarray of $ a $ if it forms a continuous subsequence of $ a $ , that is, if it is equal to $ a_l $ , $ a_{l + 1} $ , $ \ldots $ , $ a_r $ for some $ l, r $ .

Suppose $ m $ is some known constant. For any array, having $ m $ or more elements, let's define it's beauty as the sum of $ m $ largest elements of that array. For example:

- For array $ x = [4, 3, 1, 5, 2] $ and $ m = 3 $ , the $ 3 $ largest elements of $ x $ are $ 5 $ , $ 4 $ and $ 3 $ , so the beauty of $ x $ is $ 5 + 4 + 3 = 12 $ .
- For array $ x = [10, 10, 10] $ and $ m = 2 $ , the beauty of $ x $ is $ 10 + 10 = 20 $ .

You are given an array $ a_1, a_2, \ldots, a_n $ , the value of the said constant $ m $ and an integer $ k $ . Your need to split the array $ a $ into exactly $ k $ subarrays such that:

- Each element from $ a $ belongs to exactly one subarray.
- Each subarray has at least $ m $ elements.
- The sum of all beauties of $ k $ subarrays is maximum possible.

## 说明/提示

In the first example, one of the optimal partitions is $ [5, 2, 5] $ , $ [2, 4] $ , $ [1, 1, 3, 2] $ .

- The beauty of the subarray $ [5, 2, 5] $ is $ 5 + 5 = 10 $ .
- The beauty of the subarray $ [2, 4] $ is $ 2 + 4 = 6 $ .
- The beauty of the subarray $ [1, 1, 3, 2] $ is $ 3 + 2 = 5 $ .

The sum of their beauties is $ 10 + 6 + 5 = 21 $ .

In the second example, one optimal partition is $ [4] $ , $ [1, 3] $ , $ [2, 2] $ , $ [3] $ .

## 样例 #1

### 输入

```
9 2 3
5 2 5 2 4 1 1 3 2
```

### 输出

```
21
3 5 ```

## 样例 #2

### 输入

```
6 1 4
4 1 3 2 2 3
```

### 输出

```
12
1 3 5 ```

## 样例 #3

### 输入

```
2 1 2
-1000000000 1000000000
```

### 输出

```
0
1 ```

# AI分析结果



# 题目中文重写

## 题目描述

若数组 $b$ 是数组 $a$ 的连续子序列，则称 $b$ 是 $a$ 的子数组。例如，$b = a_l, a_{l+1}, \ldots, a_r$ 时，$b$ 是 $a$ 的子数组。

对于一个长度至少为 $m$ 的数组，定义其美丽度为该数组中最大的 $m$ 个元素之和。例如：
- 数组 $x = [4, 3, 1, 5, 2]$，$m=3$ 时，最大的 $3$ 个元素是 $5,4,3$，美丽度为 $12$。
- 数组 $x = [10,10,10]$，$m=2$ 时，美丽度为 $20$。

给定数组 $a_1, a_2, \ldots, a_n$，以及整数 $m$ 和 $k$。要求将数组分割为恰好 $k$ 个子数组，满足：
1. 每个元素属于且仅属于一个子数组。
2. 每个子数组长度至少为 $m$。
3. 所有子数组的美丽度之和最大化。

---

**算法分类**  
贪心

---

## 题解分析与结论

### 核心思路
所有题解均基于以下贪心策略：
1. **最大元素选取**：美丽度之和最大等价于所有子数组包含尽可能多的大元素。因此，直接选取数组中前 $k \times m$ 大的元素之和作为答案。
2. **动态分割**：遍历原数组，每当当前子数组已包含 $m$ 个前 $k \times m$ 大的元素时进行分割，确保每个子数组贡献 $m$ 个最大元素。

### 解决难点
- **重复元素处理**：使用哈希表（如 `map`）记录每个元素的出现次数，避免重复计数。
- **分割点判定**：维护计数器，当收集到 $m$ 个目标元素时立即分割，保证每个子数组满足条件。

---

## 高星题解推荐

### 题解1：cannotdp（4星）
**关键亮点**  
- 使用优先队列筛选前 $k \times m$ 大的元素，逻辑清晰。
- 严格维护分割条件，确保每个子数组恰好包含 $m$ 个目标元素。
- 代码变量命名合理，可读性强。

**核心代码**  
```cpp
priority_queue<int> q;
map<int, int> f; // 记录前k*m大元素的出现次数

// 筛选前k*m大的元素
int temp = m * k;
for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
    q.push(a[i]);
}
int p = 1;
while (!q.empty() && p <= temp) {
    ans += q.top();
    f[q.top()]++;
    q.pop();
    p++;
}

// 动态分割
int num = 1, i = 1, L = 0;
while (num < k && i <= n) {
    if (f[a[i]] > 0) {
        L++;
        f[a[i]]--;
    }
    if (L == m) { // 每收集m个目标元素分割一次
        printf("%lld ", i);
        L = 0;
        num++;
    }
    i++;
}
```

---

### 题解2：Chillturtle（4星）
**关键亮点**  
- 与 cannotdp 的思路完全一致，代码简洁。
- 使用 `long long` 避免整数溢出，鲁棒性强。

**核心代码**  
（与 cannotdp 的代码结构相同，仅变量名略有差异）

---

## 最优思路总结
- **贪心选择**：直接取前 $k \times m$ 大元素之和，无需复杂动态规划。
- **哈希表计数**：解决重复元素的分配问题。
- **动态分割**：遍历时实时统计目标元素数量，触发分割条件。

---

## 同类题目推荐
1. **P1090 合并果子**：贪心+优先队列，最小化合并成本。
2. **P1223 排队接水**：贪心排序，最小化平均等待时间。
3. **P1106 删数问题**：贪心选择保留最大/最小数字序列。

---
处理用时：104.45秒