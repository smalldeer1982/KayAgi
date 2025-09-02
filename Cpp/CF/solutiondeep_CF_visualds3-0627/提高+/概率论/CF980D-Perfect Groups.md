# 题目信息

# Perfect Groups

## 题目描述

SaMer has written the greatest test case of all time for one of his problems. For a given array of integers, the problem asks to find the minimum number of groups the array can be divided into, such that the product of any pair of integers in the same group is a perfect square.

Each integer must be in exactly one group. However, integers in a group do not necessarily have to be contiguous in the array.

SaMer wishes to create more cases from the test case he already has. His test case has an array $ A $ of $ n $ integers, and he needs to find the number of contiguous subarrays of $ A $ that have an answer to the problem equal to $ k $ for each integer $ k $ between $ 1 $ and $ n $ (inclusive).

## 样例 #1

### 输入

```
2
5 5
```

### 输出

```
3 0
```

## 样例 #2

### 输入

```
5
5 -4 2 1 8
```

### 输出

```
5 5 3 2 0
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
1
```

# AI分析结果



**算法分类**: 数学（质因数分解） + 并查集/区间统计

---

### **题解思路与核心难点**

#### **核心思路**
1. **平方因子去除**：将每个数去除所有平方因子，使得两数乘积为平方数当且仅当它们的简化形式相等。
2. **并查集预处理**：通过并查集合并所有能互相形成平方数的数，或在预处理阶段记录每个数最近的可合并位置。
3. **区间统计**：枚举每个子数组的起点，动态维护区间内的不同组数，利用预处理信息快速判断是否需要新增组。

#### **解决难点**
- **平方因子高效分解**：通过试除法或质数筛法快速去除平方因子。
- **0的特殊处理**：0可与任意数同组，需单独统计其存在性。
- **时间复杂度优化**：通过预处理每个数的前驱位置，避免重复计算，将复杂度从 \(O(n^3)\) 优化到 \(O(n^2)\)。

---

### **题解评分 (≥4星)**

| 题解作者 | 评分 | 关键亮点 |
|----------|------|----------|
| honglan0301 | ⭐⭐⭐⭐ | 预处理每个数的前驱位置，避免并查集操作，代码简洁高效 |
| _Life_      | ⭐⭐⭐⭐ | 并查集思路清晰，证明完整，但时间效率稍低 |
| fanypcd     | ⭐⭐⭐⭐ | 提出特征值哈希离散化，解决值域过大问题 |

---

### **最优思路/技巧**
1. **平方因子预处理**：将每个数分解为无平方因子的形式，简化比较逻辑。
   ```cpp
   // 去除平方因子
   int simplify(int x) {
       for (int j=2; j*j <= abs(x); ++j)
           while (x % (j*j) == 0) x /= j*j;
       return x;
   }
   ```
2. **前驱位置记录**：对每个数记录其左侧最近的相同简化值的位置，避免重复统计。
   ```cpp
   for (int i=1; i<=n; ++i)
       for (int j=i-1; j>=1; --j)
           if (simplify(a[i]) == simplify(a[j])) {
               pre[i] = j; break;
           }
   ```
3. **动态区间统计**：固定左端点，右端点扩展时利用前驱位置判断是否需要新增组。
   ```cpp
   for (int l=1; l<=n; ++l) {
       int cnt = 0;
       for (int r=l; r<=n; ++r) {
           if (pre[r] < l) cnt++; // 新增组
           ans[cnt]++;
       }
   }
   ```

---

### **同类型题/算法套路**
- **区间不同元素统计**：如[CF1000F](https://www.luogu.com.cn/problem/CF1000F)（区间唯一出现次数的数）。
- **并查集分组优化**：如[P1955](https://www.luogu.com.cn/problem/P1955)（程序自动分析）。
- **预处理优化查询**：如[P1972](https://www.luogu.com.cn/problem/P1972)（HH的项链）。

---

### **可视化设计**
#### **核心算法演示**
- **动画流程**：
  1. **分解阶段**：用像素方块展示每个数的质因数分解，红色高亮奇数次幂的质因数。
  2. **预处理阶段**：显示每个数的简化形式，用箭头指向其左侧最近相同值的位置。
  3. **区间扩展**：固定左端点，右端点逐格右移，当新数的前驱不在当前区间时，颜色变为绿色表示新增组。

#### **复古像素风格**
- **颜色方案**：
  - 质因数分解：奇数次幂红色，偶数次幂蓝色。
  - 区间统计：当前区间黄色边框，新增组绿色高亮。
- **音效**：
  - 分解完成：8-bit "叮"声。
  - 新增组：短促上升音调。
- **Canvas绘制**：网格布局，每个数占据一个像素块，动态更新颜色和连接线。

---

### **代码片段 (关键逻辑)**
```cpp
// 预处理每个数的前驱位置
vector<int> pre(n+1, -1);
for (int i=1; i<=n; ++i) {
    int x = simplify(a[i]);
    for (int j=i-1; j>=1; --j) {
        if (x == simplify(a[j])) {
            pre[i] = j; break;
        }
    }
}

// 统计答案
vector<int> ans(n+1, 0);
for (int l=1; l<=n; ++l) {
    int cnt = 0;
    for (int r=l; r<=n; ++r) {
        if (a[r] == 0) ans[max(1, cnt)]++;
        else if (pre[r] < l) cnt++;
        ans[cnt]++;
    }
}
```

---

### **个人心得摘录**
> "卡在 sqrt 负数超时，没想到是这里的问题，改为 1ll*a[i]*a[j] 后解决。长记性了！" —— lenlen  
> **教训**：数值范围溢出常导致隐蔽错误，需显式类型转换。

---
处理用时：58.89秒