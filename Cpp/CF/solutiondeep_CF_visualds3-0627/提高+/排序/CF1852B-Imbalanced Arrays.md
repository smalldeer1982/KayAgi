# 题目信息

# Imbalanced Arrays

## 题目描述

Ntarsis has come up with an array $ a $ of $ n $ non-negative integers.

Call an array $ b $ of $ n $ integers imbalanced if it satisfies the following:

- $ -n\le b_i\le n $ , $ b_i \ne 0 $ ,
- there are no two indices $ (i, j) $ ( $ 1 \le i, j \le n $ ) such that $ b_i + b_j = 0 $ ,
- for each $ 1 \leq i \leq n $ , there are exactly $ a_i $ indices $ j $ ( $ 1 \le j \le n $ ) such that $ b_i+b_j>0 $ , where $ i $ and $ j $ are not necessarily distinct.

Given the array $ a $ , Ntarsis wants you to construct some imbalanced array. Help him solve this task, or determine it is impossible.

## 说明/提示

For the first test case, $ b = [1] $ is an imbalanced array. This is because for $ i = 1 $ , there is exactly one $ j $ ( $ j = 1 $ ) where $ b_1 + b_j > 0 $ .

For the second test case, it can be shown that there exists no imbalanced array.

For the third test case, $ a = [0, 1, 0] $ . The array $ b = [-3, 1, -2] $ is an imbalanced array.

- For $ i = 1 $ and $ i = 3 $ , there exists no index $ j $ such that $ b_i + b_j > 0 $ .
- For $ i = 2 $ , there is only one index $ j = 2 $ such that $ b_i + b_j > 0 $ ( $ b_2 + b_2 = 1 + 1 = 2 $ ).

 Another possible output for the third test case could be $ b = [-2, 1, -3] $ .

## 样例 #1

### 输入

```
5
1
1
4
1 4 3 4
3
0 1 0
4
4 3 2 1
3
1 3 1```

### 输出

```
YES
1 
NO
YES
-3 1 -2 
YES
4 2 -1 -3 
YES
-1 3 -1```

# AI分析结果



---

## 算法分类
**贪心 + 双指针**

---

## 题解思路与核心难点

### 核心思路
1. **极端值优先处理**：每次处理当前最大可能的正数或最小可能的负数，对应数组中的 `0` 或 `n`。
2. **递归分解问题**：通过调整剩余数组的规模和相关参数，将问题逐步缩小为子问题。
3. **双指针实现**：排序数组后，用左右指针分别指向最小和最大值，动态维护当前剩余规模与调整量。

### 算法实现要点
1. **排序**：将数组 `a` 排序以便快速定位极端值。
2. **双指针与调整变量**：
   - **左指针**处理可能的最小值（赋值为负数）。
   - **右指针**处理可能的最大值（赋值为正数）。
   - **调整变量 `add`** 记录正数对剩余元素的影响（相当于批量减1）。
3. **合法性检查**：
   - 若同时存在 `0` 和 `n`，无解。
   - 若无法找到极端值，无解。

### 解决难点
1. **动态维护剩余规模**：通过 `n` 的递减和 `add` 的调整，避免实际修改每个元素的 `a` 值。
2. **正确性证明**：通过数学归纳法证明每一步选择的极端值唯一且必要。

---

## 最优题解评分与亮点

### 题解1：dark_moon（⭐⭐⭐⭐⭐）
- **亮点**：
  - 使用双指针清晰处理极端值。
  - 调整变量 `add` 避免数组遍历修改。
  - 代码简洁，逻辑分层明确。
- **代码片段**：
  ```cpp
  int l = 1, r = n, now = n, add = 0;
  for (int i = n; i >= 1; --i) {
      if (s[l].a + add == 0) {
          s[l].b = -i;
          now--; l++;
      } else if (now - (s[r].a + add) == 0) {
          s[r].b = i;
          now--; add--; r--;
      } else return 0;
  }
  ```

### 题解2：Zooping（⭐⭐⭐⭐）
- **亮点**：
  - 使用结构体保留原始索引。
  - 显式处理 `0` 和 `n` 的冲突。
- **代码片段**：
  ```cpp
  if (a[l].num + jian == 0) {
      b[a[l].wei] = -cnt;
      cnt--; l++;
  } else if (a[r].num + jian == cnt) {
      b[a[r].wei] = cnt;
      cnt--; r--; jian--;
  }
  ```

### 题解3：phil071128（⭐⭐⭐⭐）
- **亮点**：
  - 倒序维护正负数量。
  - 利用哈希表快速查找可能的 `a` 值。
- **代码片段**：
  ```cpp
  if (t[x + i]) {
      t[x + i]--; ans[p[l++].id] = i; x++;
  } else if (t[n - i - y]) {
      t[n - i - y]--; ans[p[r--].id] = -i; y++;
  }
  ```

---

## 关键思路与技巧

### 核心算法流程
1. **排序数组**：按 `a` 升序排列，保留原始索引。
2. **双指针遍历**：
   - **左指针**：若 `a[l] + add == 0`，赋值为 `-current_n`。
   - **右指针**：若 `a[r] + add == current_n`，赋值为 `current_n`。
3. **动态调整参数**：
   - 每处理一个正数，剩余元素的 `a` 值需减1（通过 `add--` 实现）。
   - `current_n` 递减表示剩余规模缩小。

### 数学证明
- **极端值唯一性**：若存在解，必存在一个 `0` 或 `n`，否则矛盾。
- **子问题合法性**：每次处理后的剩余数组仍满足原问题的约束。

---

## 同类型题与拓展

### 相似题目
1. **LeetCode 870. Advantage Shuffle**：贪心匹配最大最小值。
2. **Codeforces 1795D. Balanced Array**：构造满足特定条件的数组。
3. **洛谷 P1094 [NOIP2007 普及组] 纪念品分组**：双指针处理极值。

### 扩展思路
- **拓扑排序思想**：将元素间的依赖关系建模为图。
- **差分数组**：批量调整区间值，提高效率。

---

## 可视化与算法演示

### 动画设计
1. **像素风格界面**：
   - **数组块**：用不同颜色表示已处理（绿色）、正数（蓝色）、负数（红色）。
   - **指针**：高亮左右指针位置，动态移动。
2. **关键步骤演示**：
   - **处理正数**：右指针元素变蓝，播放“升级”音效。
   - **处理负数**：左指针元素变红，播放“点击”音效。
3. **控制面板**：
   - **速度调节**：滑动条控制动画速度。
   - **单步执行**：按钮逐步观察处理过程。

### 代码片段（Canvas 绘制）
```javascript
function drawArray(ctx, arr, l, r, currentN) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let i = 0; i < arr.length; i++) {
        if (i < l || i > r) ctx.fillStyle = '#4CAF50'; // 已处理
        else if (i === l) ctx.fillStyle = '#FF0000';   // 左指针
        else if (i === r) ctx.fillStyle = '#0000FF';   // 右指针
        else ctx.fillStyle = '#CCCCCC';                // 未处理
        ctx.fillRect(i * 50 + 10, 100, 40, 40);
    }
}
```

---

## 个人心得摘录
- **调试经验**：初始未处理索引导致输出顺序错误，需显式保留原始位置。
- **思维突破**：通过调整变量替代实际修改数组，极大优化时间复杂度。
- **教训**：必须严格检查 `0` 和 `n` 的共存情况，否则会漏判无解。

---
处理用时：88.91秒