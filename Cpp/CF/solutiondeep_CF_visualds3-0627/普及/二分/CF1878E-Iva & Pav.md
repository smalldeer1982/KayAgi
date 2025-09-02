# 题目信息

# Iva & Pav

## 题目描述

Iva and Pav are a famous Serbian competitive programming couple. In Serbia, they call Pav "papuca" and that's why he will make all of Iva's wishes come true.

Iva gave Pav an array $ a $ of $ n $ elements.

Let's define $ f(l, r) = a_l \ \& \ a_{l+1} \ \& \dots \& \ a_r $ (here $ \& $ denotes the [bitwise AND operation](http://tiny.cc/bitwise_and)).

Note that $ f(l, r) $ is not defined when $ l>r $ .

Iva also gave Pav $ q $ queries.

Each query consists of 2 numbers, $ k $ and $ l $ , and she wants Pav to find the largest index $ r $ ( $ l \le r \le n $ ), such that $ f(l, r) \ge k $ .

Pav wants to solve this problem fast because he doesn't want to upset Iva. He needs your help.

## 说明/提示

In the first test case $ n=5 $ , and the array $ a = [15, 14, 17, 42, 34] $

The first query asks for the biggest index $ r $ such that the $ f(1, r) \ge 7 $ .

 $ f(1,1) = 15, \ f(1, 2) = 14, \ f(1,3)=0 \ f(1, 4)=0 \ f(1, 5)=0 $ , so $ r=2 $ is the answer.

The second query asks for $ f(2, r) \ge 15 $ . Since such $ r $ doesn't exist, the answer is $ -1 $ .

The third query asks for $ f(4, r) \ge 5 $ . $ f(4, 4) = 42, \ f(4, 5) = 34 $ , so $ r=5 $ is the answer.

In the second test case $ n=5 $ , and the array $ a= [7, 5, 3, 1, 7] $ .

For the first query, $ f(1, r) \ge 7 $ .

 $ f(1, 1)=7, \ f(1, 2)=5, \ f(1, 3) = 1, \ f(1,4) = 1, \ f(1, 5)=1 $ , so the answer to this query is $ 1 $ .

For the second query, $ f(5, r) \ge 7 $ .

 $ f(5, 5) = 7 $ , so the answer is $ 5 $ .

For the third query, $ f(2, r) \ge 3 $ .

 $ f(2, 2) = 5, \ f(2, 3) = 1, \ f(2, 4) = 1, \ f(2, 5) = 1 $ , so the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
5
15 14 17 42 34
3
1 7
2 15
4 5
5
7 5 3 1 7
4
1 7
5 7
2 3
2 2
7
19 20 15 12 21 7 11
4
1 15
4 4
7 12
5 7```

### 输出

```
2 -1 5 
1 5 2 2 
2 6 -1 5```

# AI分析结果



---

**算法分类**: 二分

---

### **题解思路与核心分析**
题目要求对每个查询找最大右端点，使得区间按位与结果 ≥ k。核心解法均基于以下观察：
1. **单调性**：固定左端点时，随着右端点增大，按位与结果单调不增。
2. **二分可行性**：利用单调性对右端点二分，快速定位临界点。
3. **区间计算优化**：通过 ST 表、线段树或拆位前缀和加速区间按位与的查询。

**二分关键点**：
- **搜索区间**：初始化为 `[l, n]`。
- **条件判断**：若 `f(l, mid) ≥ k`，则尝试扩大右端点；否则缩小。
- **边界处理**：初始检查 `a[l] < k` 时直接返回 `-1`。

---

### **题解评分 (≥4星)**
1. **Register_int (5星)**  
   - **亮点**：ST 表预处理，倍增优化查询，代码高效简洁。  
   - **优化**：利用 ST 表特性减少区间查询次数，时间复杂度最优。
2. **WaterSun (4星)**  
   - **亮点**：拆位前缀和实现直观，适合理解按位与的二进制特性。  
   - **不足**：时间复杂度略高（需遍历所有二进制位），但思路清晰。
3. **luqyou (4星)**  
   - **亮点**：ST 表结合二分，逻辑明确，代码易于移植。  
   - **优化**：直接调用 `log2` 函数简化 ST 表查询，可读性强。

---

### **最优思路提炼**
1. **ST 表 + 倍增二分**  
   - 预处理所有区间的按位与结果，通过倍增快速扩展右端点。
   - **关键代码**：
     ```cpp
     for (int i = lg[n]; ~i; i--) {
         if (r + (1 << i) - 1 <= n && (x & st[i][r]) >= k) {
             x &= st[i][r], r += 1 << i;
         }
     }
     ```
2. **拆位前缀和**  
   - 预处理每个二进制位的前缀和，快速判断区间内各位是否全为 1。
   - **关键代码**：
     ```cpp
     for (int bit = 0; bit <= 30; bit++) {
         if (num[bit][r] - num[bit][l-1] == r - l + 1) {
             sum += (1ll << bit);
         }
     }
     ```

---

### **同类型题与算法套路**
- **二分答案**：适用于单调性问题，如求最大/最小的可行值。
- **区间查询优化**：使用 ST 表、线段树或前缀和加速。
- **类似题目**：
  1. **P1419 寻找段落**（二分答案 + 前缀和）
  2. **P1083 借教室**（二分答案 + 差分）
  3. **P2218 涂色**（二分 + 贪心验证）

---

### **可视化与算法演示**
**动画方案**：
1. **区间收缩**：以网格表示数组，高亮当前二分区间 `[left, right]`。
2. **mid 检查**：标记 `mid` 位置，计算 `f(l, mid)` 并显示是否满足条件。
3. **颜色标记**：绿色表示 `f(l, mid) ≥ k`，红色表示不满足，灰色为未检查区域。
4. **步进控制**：用户可调整速度或单步执行，观察 `left` 和 `right` 的更新。

**复古像素风格**：
- **Canvas 绘制**：数组元素用 16x16 像素块表示，二分区间以不同颜色边框区分。
- **音效**：移动 `mid` 时播放 8-bit 音效，成功/失败时用不同音调提示。
- **AI 模式**：自动执行二分步骤，模拟“AI 解题”过程。

---

### **推荐题目**
1. **P1419**：二分答案与单调性的经典结合。
2. **P1083**：二分答案 + 差分验证的典型应用。
3. **P2218**：二分答案在几何问题中的灵活使用。

---

**代码片段（ST 表实现）**：
```cpp
// ST 表预处理
void init(int n, int *a) {
    for (int i = 1; i <= n; i++) st[0][i] = a[i];
    for (int i = 1; i <= lg[n]; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            st[i][j] = st[i-1][j] & st[i-1][j + (1 << (i-1))];
        }
    }
}

// 二分查询
int query(int l, int k) {
    if (a[l] < k) return -1;
    int r = l, x = INT_MAX;
    for (int i = lg[n]; ~i; i--) {
        if (r + (1 << i) - 1 <= n && (x & st[i][r]) >= k) {
            x &= st[i][r], r += 1 << i;
        }
    }
    return r - 1;
}
```

---
处理用时：79.06秒