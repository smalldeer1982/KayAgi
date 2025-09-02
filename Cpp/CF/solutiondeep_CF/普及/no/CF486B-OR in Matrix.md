# 题目信息

# OR in Matrix

## 题目描述

Let's define logical $ OR $ as an operation on two logical values (i. e. values that belong to the set $ {0,1} $ ) that is equal to $ 1 $ if either or both of the logical values is set to $ 1 $ , otherwise it is $ 0 $ . We can define logical $ OR $ of three or more logical values in the same manner:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/406211f13f2a7c95dc14e24b4ae950d102f218cc.png) where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/83308fae1dcded561005b623c7c1ed2fdfdfe04f.png) is equal to $ 1 $ if some $ a_{i}=1 $ , otherwise it is equal to $ 0 $ .

Nam has a matrix $ A $ consisting of $ m $ rows and $ n $ columns. The rows are numbered from $ 1 $ to $ m $ , columns are numbered from $ 1 $ to $ n $ . Element at row $ i $ ( $ 1<=i<=m $ ) and column $ j $ ( $ 1<=j<=n $ ) is denoted as $ A_{ij} $ . All elements of $ A $ are either 0 or 1. From matrix $ A $ , Nam creates another matrix $ B $ of the same size using formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/157692e348a7a47f249e1d0e7ed60b12dc8cb619.png).

( $ B_{ij} $ is $ OR $ of all elements in row $ i $ and column $ j $ of matrix $ A $ )

Nam gives you matrix $ B $ and challenges you to guess matrix $ A $ . Although Nam is smart, he could probably make a mistake while calculating matrix $ B $ , since size of $ A $ can be large.

## 样例 #1

### 输入

```
2 2
1 0
0 0
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
2 3
1 1 1
1 1 1
```

### 输出

```
YES
1 1 1
1 1 1
```

## 样例 #3

### 输入

```
2 3
0 1 0
1 1 1
```

### 输出

```
YES
0 0 0
0 1 0
```

# AI分析结果



【题目重述】
# 矩阵或运算（OR in Matrix）

## 题目描述

定义逻辑或运算 $OR$：当两个逻辑值（属于集合 ${0,1}$）中至少有一个为 1 时结果为 1，否则为 0。对三个及以上逻辑值的或运算定义为：若存在至少一个值为 1，则结果为 1，否则为 0。

Nam 有一个 $m$ 行 $n$ 列的矩阵 $A$，其中所有元素均为 0 或 1。通过以下公式生成新矩阵 $B$：
$$ B_{ij} = \left( \bigvee_{k=1}^n A_{ik} \right) \vee \left( \bigvee_{k=1}^m A_{kj} \right) $$
（即 $B_{ij}$ 是 $A$ 的第 $i$ 行所有元素与第 $j$ 列所有元素的或运算结果）

现给定矩阵 $B$，请判断是否存在合法的矩阵 $A$，若存在则构造一个解。

## 输入样例与输出
（样例内容与原文一致，此处略）

---

**算法分类**：构造

---

### 题解综合分析
各题解核心思路统一：
1. **强制约束**：当 $B_{ij}=0$ 时，$A$ 的第 $i$ 行和第 $j$ 列必须全为 0
2. **贪心构造**：将 $A$ 初始化为全 1，根据 $B$ 中 0 的位置清除对应行列
3. **合法性验证**：检查每个 $B_{ij}=1$ 的位置是否在 $A$ 中存在至少一个 1

---

### 精选题解（评分≥4★）

#### 1. 珅肐（5★）
**亮点**：
- 使用位标记数组（`vh[]`/`vl[]`）记录清零的行列
- 通过预计算行列或值（`ah[]`/`al[]`）快速验证
- 代码简洁高效（时间复杂度 $O(nm)$）

**核心代码**：
```cpp
bool b[107][107], vh[107], vl[107], ah[107], al[107];
for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)
    if(!b[i][j]) vh[i]=vl[j]=1; // 标记清零行列

for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)
    ah[i]|=(!vl[j]&!vh[i]), al[j]|=(!vh[i]&!vl[j]); // 计算行列或值

// 验证并输出结果
```

#### 2. asasas（4★）
**亮点**：
- 直观的矩阵清零操作
- 显式的双重验证逻辑
- 适合初学者的实现方式

**验证逻辑**：
```cpp
for (int i=1;i<=n;++i) {
    for (int j=1;j<=m;++j) {
        if (p[i][j]==1) {
            bool qo=0;
            for (int k=1;k<=m;k++) if (ans[i][k]) qo=1;
            for (int k=1;k<=n;k++) if (ans[k][j]) qo=1;
            if (!qo) return 0; // 验证失败
        }
    }
}
```

#### 3. yuzhechuan（4★）
**亮点**：
- 独立的行列标记优化
- 使用位运算快速计算最终或值
- 代码结构清晰

---

### 关键思路总结
1. **逆向构造法**：从结果反推初始状态，利用约束条件缩小解空间
2. **位标记优化**：用布尔数组记录清零行列，避免重复操作
3. **预计算验证**：提前计算行列或值，将验证复杂度降至 $O(1)$

---

### 拓展训练
1. [P2894 酒店](https://www.luogu.com.cn/problem/P2894) - 区间覆盖与反向构造
2. [P3397 地毯](https://www.luogu.com.cn/problem/P3397) - 二维差分约束
3. [CF1311C Perform the Combo](https://www.luogu.com.cn/problem/CF1311C) - 逆向操作统计

---

### 调试心得摘录
- **珅肐**：强调"优先处理0的约束，再验证1的合法性"的解题顺序
- **Suzt_ilymtics**：提醒注意变量命名（`end` 是保留字）
- **KEBrantily**：指出"初始全1矩阵的贪心选择对简化问题至关重要"

---
处理用时：59.48秒