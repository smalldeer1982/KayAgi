# 题目信息

# Alter the GCD

## 题目描述

You are given two arrays $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ .

You must perform the following operation exactly once:

- choose any indices $ l $ and $ r $ such that $ 1 \le l \le r \le n $ ;
- swap $ a_i $ and $ b_i $ for all $ i $ such that $ l \leq i \leq r $ .

Find the maximum possible value of $ \text{gcd}(a_1, a_2, \ldots, a_n) + \text{gcd}(b_1, b_2, \ldots, b_n) $ after performing the operation exactly once. Also find the number of distinct pairs $ (l, r) $ which achieve the maximum value.

## 说明/提示

In the first, third, and fourth test cases, there's no way to achieve a higher GCD than $ 1 $ in any of the arrays, so the answer is $ 1 + 1 = 2 $ . Any pair $ (l, r) $ achieves the same result; for example, in the first test case there are $ 36 $ such pairs.

In the last test case, you must choose $ l = 1 $ , $ r = 2 $ to maximize the answer. In this case, the GCD of the first array is $ 5 $ , and the GCD of the second array is $ 1 $ , so the answer is $ 5 + 1 = 6 $ , and the number of ways is $ 1 $ .

## 样例 #1

### 输入

```
5
8
11 4 16 17 3 24 25 8
8 10 4 21 17 18 25 21
4
6 4 24 13
15 3 1 14
2
13 14
5 8
8
20 17 15 11 21 10 3 7
9 9 4 20 14 9 13 1
2
18 13
15 20```

### 输出

```
2 36
3 2
2 3
2 36
6 1```

# AI分析结果



## 算法分类
- **最大公约数（GCD）性质与分段处理**

---

## 题解思路与核心分析

### **题目核心**
给定两个数组，选择一段区间交换两数组对应元素，使得交换后的两个数组的GCD之和最大。需统计所有能达到最大值的区间数量。

### **关键难点**
1. **高效枚举区间**：直接枚举所有区间的时间复杂度为O(n²)，不可行。
2. **GCD变化的稀疏性**：区间扩展时，GCD的变化次数为O(log V)级别（V为元素最大值）。
3. **状态合并与统计**：如何高效维护不同交换区间对全局GCD的影响。

### **解决思路**
1. **预处理前后缀GCD**：快速计算交换区间外的GCD部分。
2. **倒序扫描左端点**：维护交换区间内的GCD变化，利用Map记录不同四元组（交换区间的a/b GCD及其后缀GCD）的出现次数。
3. **分段处理**：每个左端点对应的右端点仅有O(log V)个GCD变化点，大幅减少计算量。

---

## 题解评分与推荐（≥4星）

### **喵仔牛奶的题解（5星）**
- **亮点**：代码简洁，利用倒序枚举和Map维护四元组，时间复杂度O(n log² V)。
- **核心代码**：
  ```cpp
  struct node { ... }; // 四元组定义
  map<node, int> s;    // 维护四元组及其出现次数
  void solve() {
      // 倒序枚举左端点，更新四元组并统计贡献
  }
  ```

### **xyvsvg的题解（4.5星）**
- **亮点**：类似思路，但通过预处理和Map直接维护贡献值。
- **核心代码**：
  ```cpp
  map<P, ll> mp;      // 维护交换区间内的GCD对
  for (int l = n; l; --l) {
      // 动态更新四元组并计算贡献
  }
  ```

### **huangleyi0129的题解（4星）**
- **亮点**：链表维护相同GCD段，合并重复状态。
- **核心代码**：
  ```cpp
  while (合并相同段) { ... } // 动态合并链表节点
  ```

---

## 最优思路提炼
1. **预处理前后缀GCD**：快速获取区间外的GCD值。
2. **倒序枚举左端点**：从右到左处理，动态维护交换区间内的GCD。
3. **四元组状态压缩**：将交换区间的GCD及后缀GCD压缩为状态，用Map统计出现次数。
4. **分段合并优化**：利用GCD变化次数稀疏性，减少无效枚举。

---

## 相似题目推荐
1. **P1890 GCD区间**：求区间GCD的极值，可用类似分段处理。
2. **P3455 POI2007 ZAP-Queries**：数论与GCD性质结合。
3. **P4513 小白逛公园**：区间操作与极值统计的变种。

---

## 可视化设计
### **动画演示**
1. **前缀/后缀GCD计算**：用颜色标记前后缀数组的构建过程。
2. **倒序枚举左端点**：高亮当前处理的左端点l，展示对应的四元组变化。
3. **Map维护状态**：动态显示Map中不同四元组的数量变化。
4. **贡献值更新**：当发现更大贡献值时，触发上扬音效；重复贡献时累加计数。

### **复古像素风格**
- **颜色方案**：8位色调（如红、绿、蓝）区分不同的GCD段。
- **音效设计**：
  - **关键操作**：像素“哔”声提示四元组更新。
  - **找到最优解**：播放经典FC过关音效。
- **交互控制**：支持暂停/步进，观察每个左端点处理细节。

---

## 核心代码片段（喵仔牛奶）
```cpp
struct node {
    int A1, A2, B1, B2; // 交换区间的a/b GCD及后缀GCD
    node mdf(int x, int y) const { // 合并新元素到当前状态
        return {__gcd(A1, x), A2, __gcd(B1, y), B2};
    }
    int calc(int x, int y) const { // 计算贡献值
        return __gcd(x, __gcd(B1, A2)) + __gcd(y, __gcd(A1, B2));
    }
};

void solve() {
    map<node, int> s; // 维护四元组及其出现次数
    for (int l = n; l >= 1; --l) {
        map<node, int> t;
        for (auto [x, cnt] : s) {
            node new_x = x.mdf(a[l], b[l]); // 合并新元素
            t[new_x] += cnt;
        }
        t[{a[l], suf_a, b[l], suf_b}]++; // 新增独立区间
        s.swap(t); // 更新状态
        for (auto [x, cnt] : s) {
            int cur = x.calc(pre_a[l-1], pre_b[l-1]);
            if (cur > ans) ans = cur, total = 0;
            if (cur == ans) total += cnt;
        }
        // 更新后缀GCD
        suf_a = __gcd(suf_a, a[l]);
        suf_b = __gcd(suf_b, b[l]);
    }
}
```

---

## 总结
通过预处理和动态维护GCD变化段，结合Map高效统计状态，将时间复杂度优化至O(n log² V)。核心在于利用GCD的稀疏性和状态压缩，避免无效枚举。

---
处理用时：104.72秒