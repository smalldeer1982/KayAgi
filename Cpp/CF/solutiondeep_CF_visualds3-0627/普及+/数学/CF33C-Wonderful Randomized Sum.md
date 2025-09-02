# 题目信息

# Wonderful Randomized Sum

## 题目描述

Learn, learn and learn again — Valera has to do this every day. He is studying at mathematical school, where math is the main discipline. The mathematics teacher loves her discipline very much and tries to cultivate this love in children. That's why she always gives her students large and difficult homework. Despite that Valera is one of the best students, he failed to manage with the new homework. That's why he asks for your help. He has the following task. A sequence of $ n $ numbers is given. A prefix of a sequence is the part of the sequence (possibly empty), taken from the start of the sequence. A suffix of a sequence is the part of the sequence (possibly empty), taken from the end of the sequence. It is allowed to sequentially make two operations with the sequence. The first operation is to take some prefix of the sequence and multiply all numbers in this prefix by $ -1 $ . The second operation is to take some suffix and multiply all numbers in it by $ -1 $ . The chosen prefix and suffix may intersect. What is the maximum total sum of the sequence that can be obtained by applying the described operations?

## 样例 #1

### 输入

```
3
-1 -2 -3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
-4 2 0 5 0
```

### 输出

```
11
```

## 样例 #3

### 输入

```
5
-1 10 -5 10 -2
```

### 输出

```
18
```

# AI分析结果



### 唯一算法分类
**数论**

---

### 题解思路与核心分析
**核心逻辑**：  
通过数学推导发现，操作后的总和可表示为 `2C - S`，其中 `C` 是中间未被取反的最大子段和，`S` 为原数组总和。问题转化为求最大子段和。

**关键公式推导**：  
- 原总和 `S = A + B + C`（A为前缀，B为后缀，C为中间未变化部分）
- 操作后总和为 `-A - B + C = 2C - S`
- 最大化 `2C - S` 等价于最大化 `C`

**解决难点**：  
- 将复杂操作转化为最大子段和问题
- 允许空子段（即 `C` 可为空，此时 `C=0`）

---

### 题解评分（≥4星）
1. **LuckyCloud（5星）**  
   - 思路清晰，数学推导简洁直接  
   - 代码高效，使用 Kadane 算法求最大子段和  
   - 可读性高，适合快速理解核心逻辑  
   ```cpp
   // 核心代码片段
   long long sum = 0, Max = 0, S = 0;
   for (int i = 1; i <= n; i++) {
       sum += a[i];
       S = max(S + a[i], 0LL);
       Max = max(Max, S);
   }
   ans = Max * 2 - sum;
   ```

2. **Level_Down（4星）**  
   - 代码极简，直接嵌入公式  
   - 动态规划实现 Kadane 算法  
   ```cpp
   // 核心代码片段
   int sum = 0, ans = 0, current = 0;
   for (int i = 1; i <= n; i++) {
       sum += a[i];
       current = max(current + a[i], 0);
       ans = max(ans, current);
   }
   cout << 2 * ans - sum;
   ```

3. **Z_M__（4星）**  
   - 详细数学证明，强化逻辑理解  
   - 代码简洁，与核心思路一致  
   ```cpp
   int sum = 0, max_sub = 0, current = 0;
   for (int i = 1; i <= n; i++) {
       sum += a[i];
       current = max(current + a[i], 0);
       max_sub = max(max_sub, current);
   }
   cout << 2 * max_sub - sum;
   ```

---

### 最优思路提炼
1. **数学转换**：将前缀/后缀操作转化为中间子段的最大化问题。
2. **Kadane 算法**：动态规划求最大子段和，时间复杂度 `O(n)`。
3. **空子段处理**：允许中间部分为空（和为0），确保所有元素被取反的情况可覆盖。

---

### 同类型题目与套路
**常见套路**：  
- **最大子段和**：如股票买卖、连续数组最大和等。
- **数学转换**：将操作转化为已知模型（如本题的 `2C - S`）。
- **前后缀分解**：通过预处理前后缀极值优化枚举。

**推荐题目**：  
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
2. [P2642 双子序列最大和](https://www.luogu.com.cn/problem/P2642)  
3. [CF455A Boredom](https://codeforces.com/problemset/problem/455/A)  

---

### 可视化与动画设计
**核心动画流程**：  
1. **初始数组**：显示原数组，用灰色表示所有元素。
2. **遍历过程**：  
   - 高亮当前遍历的元素，计算当前子段和（绿色表示正贡献，红色表示负）。
   - 动态更新最大子段和的值，显示公式 `2C - S` 的实时计算。
3. **最终结果**：  
   - 高亮最大子段 `C` 对应的区间，显示前缀和后缀取反的区域。
   - 展示最终总和的计算过程（`2C - S`）。

**复古像素风格**：  
- **颜色方案**：使用 8-bit 风格调色板（绿、红、蓝、黄）。
- **音效**：  
  - 步进时播放“哔”声，找到最大子段时播放胜利音效。
  - 背景音乐循环播放 8-bit 风格旋律。
- **Canvas 绘制**：用像素块表示数组元素，动态更新颜色和数值。

---

### 核心代码实现
**Kadane 算法实现**：  
```cpp
#include <iostream>
using namespace std;

int main() {
    int n, sum = 0, max_sub = 0, current = 0;
    cin >> n;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        sum += x;
        current = max(current + x, 0);
        max_sub = max(max_sub, current);
    }
    cout << 2 * max_sub - sum << endl;
    return 0;
}
```

**代码说明**：  
- `sum` 记录原数组总和，`current` 为当前子段和，`max_sub` 为最大子段和。
- 遍历时动态更新 `current`，若为负则重置为0（允许空子段）。
- 最终结果由公式 `2 * max_sub - sum` 直接计算。

---
处理用时：113.32秒