# 题目信息

# Set To Max (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions of this problem are the constraints on $ n $ and the time limit. You can make hacks only if all versions of the problem are solved.

You are given two arrays $ a $ and $ b $ of length $ n $ .

You can perform the following operation some (possibly zero) times:

1. choose $ l $ and $ r $ such that $ 1 \leq l \leq r \leq n $ .
2. let $ x=\max(a_l,a_{l+1},\ldots,a_r) $ .
3. for all $ l \leq i \leq r $ , set $ a_i := x $ .

Determine if you can make array $ a $ equal to array $ b $ .

## 说明/提示

In the first test case, we can achieve array $ b $ by applying a single operation: $ (l,r)=(2,3) $ .

In the second test case, it can be shown we cannot achieve array $ b $ in any amount of operations.

In the third test case, we can achieve array $ b $ by applying two operations: $ (l,r)=(2,5) $ . followed by $ (l,r)=(1,3) $ .

In the fourth and fifth test cases, it can be shown we cannot achieve array $ b $ in any amount of operations.

## 样例 #1

### 输入

```
5
5
1 2 3 2 4
1 3 3 2 4
5
3 4 2 2 4
3 4 3 4 4
5
3 2 1 1 1
3 3 3 2 2
2
1 1
1 2
3
1 1 2
2 1 2```

### 输出

```
YES
NO
YES
NO
NO```

# AI分析结果



---

### 题解思路、算法要点与解决难点

#### 核心贪心策略
1. **无解条件**：若存在任意位置 `a[i] > b[i]`，直接返回 `NO`（操作只能增大元素）。
2. **左右扩展验证**：对每个 `a[i] < b[i]`，需在左右两侧找到 `a[j] = b[i]`，且路径上所有元素满足：
   - 无 `a[k] > b[i]`（否则操作后会导致该位置的值超过 `b[i]`）。
   - 所有 `b[k] >= b[i]`（否则操作后该位置的 `a[k]` 会超过 `b[k]`）。

#### 解决难点
- **验证条件的完整性**：需同时检查路径上的 `a` 和 `b` 数组，确保操作后的合法性。
- **贪心选择的最优性**：优先选择离 `i` 最近的 `j`，减少后续操作的干扰。

#### 算法对比
| 题解作者       | 核心方法                           | 数据结构/优化       | 时间复杂度 | 亮点                         |
|----------------|-----------------------------------|---------------------|------------|------------------------------|
| CuteChat       | 左右线性扫描验证条件              | 无                  | O(n²)      | 思路清晰，代码简洁           |
| Genius_Star    | ST表预处理区间极值                | ST表、单调队列      | O(n log n) | 高效处理区间查询              |
| yshpdyt        | 单调队列维护候选解                | 单调队列、区间最小值 | O(n log n) | 优化候选解的查找与验证        |

---

### 题解评分（≥4星）

1. **CuteChat (★★★★☆)**  
   - **思路清晰度**：详细推导每一步条件，易于理解。  
   - **代码可读性**：简洁直观，无复杂结构。  
   - **优化程度**：暴力但正确，适合简单版本。  
   - **实践性**：直接实现，适合快速验证。

2. **Genius_Star (★★★★☆)**  
   - **思路清晰度**：利用预处理优化查询，逻辑严谨。  
   - **代码可读性**：稍复杂但注释详细。  
   - **优化程度**：ST表加速，适合大规模数据。  
   - **实践性**：适合进阶学习区间查询优化。

---

### 最优思路或技巧提炼

1. **贪心选择依据**  
   - **最近优先**：对每个 `i`，优先查找最近的 `j` 使得 `a[j] = b[i]`，减少覆盖区间。
   - **双条件验证**：路径需满足 `a[k] ≤ b[i]` 且 `b[k] ≥ b[i]`。

2. **预处理优化**  
   - **ST表加速**：预处理区间最大值（`a`）和最小值（`b`），快速验证路径合法性。

---

### 同类型题与算法套路

- **常见贪心场景**：区间覆盖、元素递增操作、最小操作次数。
- **类似题目**：  
  1. [CF1582D. Vupsen, Pupsen and 0](https://codeforces.com/problemset/problem/1582/D)（贪心构造）  
  2. [LeetCode 670. Maximum Swap](https://leetcode.com/problems/maximum-swap/)（选择最优交换）  
  3. [洛谷 P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（贪心选择删除策略）

---

### 代码核心片段

#### 关键逻辑（CuteChat 题解）
```cpp
for (int i = 1; i <= n; ++i) {
    if (a[i] < b[i]) {
        bool ok = false;
        // 向右寻找
        for (int r = i; r <= n; ++r) {
            if (a[r] == b[i]) {
                if (check_range(i, r, b[i])) { ok = true; break; }
            }
            if (a[r] > b[i] || b[r] < b[i]) break;
        }
        // 向左寻找同理...
        if (!ok) return NO;
    }
}
```

#### ST表优化（Genius_Star 题解）
```cpp
void build_st() {
    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            st_max[j][i] = max(st_max[j-1][i], st_max[j-1][i + (1 << (j-1))]);
            st_min[j][i] = min(st_min[j-1][i], st_min[j-1][i + (1 << (j-1))]);
        }
}

bool valid(int l, int r, int target) {
    int k = log2(r - l + 1);
    int max_a = max(st_max[k][l], st_max[k][r - (1 << k) + 1]);
    int min_b = min(st_min[k][l], st_min[k][r - (1 << k) + 1]);
    return max_a <= target && min_b >= target;
}
```

---

### 可视化与算法演示

#### 动画设计
- **像素风格界面**：用 Canvas 绘制数组元素，`a` 和 `b` 上下排列，元素用色块表示。
- **贪心过程**：  
  1. **高亮当前检查的 `i`**：红色边框标记当前处理的元素。  
  2. **左右扫描**：绿色箭头动态扩展，遇到非法元素（红色闪烁）则停止。  
  3. **成功匹配**：找到 `j` 后，区间变为金色，播放“成功音效”。

#### 交互功能
- **步进控制**：按钮控制执行下一步，观察扫描过程。  
- **音效提示**：  
  - 成功找到 `j`：轻快的“叮”声。  
  - 遇到非法元素：低沉的“哔”声。  

---

### 复古游戏化示例（伪代码）

```javascript
// 初始化像素画布
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
const colors = ['#FF6B6B', '#4ECDC4', '#45B7D1']; // 复古配色

function drawArray(arr, y, highlightIdx) {
    arr.forEach((val, idx) => {
        ctx.fillStyle = highlightIdx === idx ? colors[0] : colors[1];
        ctx.fillRect(idx * 30, y, 25, 25);
        ctx.fillStyle = '#FFF';
        ctx.fillText(val, idx * 30 + 10, y + 15);
    });
}

// 示例动画帧
function animateStep(i, direction) {
    drawArray(a, 50, i); // 绘制a数组
    drawArray(b, 100, -1); // 绘制b数组
    // 绘制扫描箭头...
}
```

---

### 总结

**核心结论**：通过贪心策略验证每个元素的合法性，优先选择最近的有效区间，结合预处理优化查询效率。  
**可视化亮点**：动态扫描过程与复古像素风格结合，强化对贪心选择的理解。

---
处理用时：99.98秒