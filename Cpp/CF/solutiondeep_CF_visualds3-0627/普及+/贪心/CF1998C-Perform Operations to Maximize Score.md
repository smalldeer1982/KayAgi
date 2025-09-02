# 题目信息

# Perform Operations to Maximize Score

## 题目描述

I see satyam343. I'm shaking. Please more median problems this time. I love those. Please satyam343 we believe in you.

— satyam343's biggest fan



You are given an array $ a $ of length $ n $ and an integer $ k $ . You are also given a binary array $ b $ of length $ n $ .

You can perform the following operation at most $ k $ times:

- Select an index $ i $ ( $ 1 \leq i \leq n $ ) such that $ b_i = 1 $ . Set $ a_i = a_i + 1 $ (i.e., increase $ a_i $ by $ 1 $ ).

Your score is defined to be $ \max\limits_{i = 1}^{n} \left( a_i + \operatorname{median}(c_i) \right) $ , where $ c_i $ denotes the array of length $ n-1 $ that you get by deleting $ a_i $ from $ a $ . In other words, your score is the maximum value of $ a_i + \operatorname{median}(c_i) $ over all $ i $ from $ 1 $ to $ n $ .

Find the maximum score that you can achieve if you perform the operations optimally.

For an arbitrary array $ p $ , $ \operatorname{median}(p) $ is defined as the $ \left\lfloor \frac{|p|+1}{2} \right\rfloor $ -th smallest element of $ p $ . For example, $ \operatorname{median} \left( [3,2,1,3] \right) = 2 $ and $ \operatorname{median} \left( [6,2,4,5,1] \right) = 4 $ .

## 说明/提示

For the first test case, it is optimal to perform $ 5 $ operations on both elements so $ a = [8,8] $ . So, the maximum score we can achieve is $ \max(8 + \operatorname{median}[8], 8 + \operatorname{median}[8]) = 16 $ , as $ c_1 = [a_2] = [8] $ . It can be proven that you cannot get a better score.

For the second test case, you are not able to perform operations on any elements, so $ a $ remains $ [3,3,3] $ . So, the maximum score we can achieve is $ 3 + \operatorname{median}[3, 3] = 6 $ , as $ c_1 = [a_2, a_3] = [3, 3] $ . It can be proven that you cannot get a better score.

## 样例 #1

### 输入

```
8
2 10
3 3
1 1
3 10
3 3 3
0 0 0
4 4
2 1 5 1
0 1 0 1
5 4
7 5 2 5 4
0 0 1 0 1
5 1
5 15 15 2 11
1 0 0 1 1
5 2
10 11 4 10 15
1 1 0 1 0
4 4
1 1 2 5
1 1 0 0
2 1000000000
1000000000 1000000000
1 1```

### 输出

```
16
6
8
13
21
26
8
3000000000```

# AI分析结果



### 题解思路、算法要点与解决难点

**核心贪心思路**：
1. **排序数组**：将数组按升序排列，便于快速确定中位数的位置。
2. **分两种情况处理**：
   - **情况一**：选择一个可增加的元素（`b[i] = 1`），将全部 `k` 次操作用于该元素，最大化其值。
   - **情况二**：若最大元素不可增加，则通过二分法确定剩余元素的中位数是否可通过 `k` 次操作达到某个目标值。
3. **二分验证**：通过贪心策略验证在 `k` 次操作内，能否使至少 `⌊(n-1)/2⌋ + 1` 个元素 ≥ 目标中位数。

**解决难点**：
- **中位数动态变化**：删除不同元素后，中位数位置可能变化，需快速确定如何分配操作次数。
- **操作分配冲突**：需权衡是否将 `k` 次操作用于直接增加元素，还是用于提升其他元素的中位数。

---

### 题解评分（≥4星）

1. **BrotherCall（⭐⭐⭐⭐）**  
   - **亮点**：明确分情况讨论，给出数学证明，并引入二分法的思路。
   - **代码缺陷**：未提供完整实现，但思路清晰。

2. **liugh_（⭐⭐⭐⭐⭐）**  
   - **亮点**：代码结构简洁，正确处理两种情况的比较，逻辑清晰。
   - **代码优势**：利用排序和二分法高效计算答案。

3. **yshpdyt（⭐⭐⭐⭐）**  
   - **亮点**：详细分Part讨论中位数变化，结合贪心与二分法。
   - **优化点**：代码中的二分验证部分可读性稍弱。

---

### 最优思路提炼

1. **贪心选择策略**：
   - **直接增益**：若最大元素可增加（`b[i] = 1`），则全部分配 `k` 次操作，得分公式为 `a_i + k + median`。
   - **间接增益**：若最大元素不可增加，通过二分法确定中位数目标值，并验证能否在 `k` 次操作内使足够多元素 ≥ 目标值。

2. **二分法实现**：
   - **目标值范围**：中位数可能的取值范围为 `[当前最小值, 当前最大值 + k]`。
   - **验证函数**：优先选择较大的元素进行增加，确保所需操作次数最少。

---

### 同类型题与算法套路

**常见套路**：
- **中位数最大化**：通过操作调整数组元素，使得中位数尽可能大（如 LeetCode 5691. 通过最少操作次数使数组和相等）。
- **资源分配贪心**：在有限操作次数下，优先分配资源到收益最大的位置。

**推荐题目**：
1. **洛谷 P1168**：动态维护中位数。
2. **LeetCode 2382. Maximum Segment Sum After Removals**：删除元素后的最大值问题。
3. **CodeForces 1526C2**：贪心选择与资源分配。

---

### 代码片段（核心逻辑）

```cpp
// liugh_ 题解核心代码（简化版）
sort(a.begin(), a.end());
ll ans = 0;

// 情况一：选择可增加的最大元素
for (int i = n; i >= 1; --i) {
    if (a[i].second == 1) {
        ll median_pos = (n % 2) ? (n / 2) : (n / 2 + 1);
        ans = max(ans, a[i].first + k + a[median_pos].first);
        break;
    }
}

// 情况二：二分中位数目标值
ll l = 0, r = 2e18, res = 0;
while (l <= r) {
    ll mid = (l + r) / 2;
    if (check(mid, a, k, n)) {
        res = mid;
        l = mid + 1;
    } else {
        r = mid - 1;
    }
}
ans = max(ans, res + a[n].first);
```

---

### 可视化设计（复古像素风格）

**动画设计**：
1. **初始画面**：排序后的数组以像素块显示，绿色表示 `b[i] = 1`，红色表示不可操作。
2. **贪心选择**：高亮当前候选元素，显示其增益后的得分（如 `+k` 的动画效果）。
3. **二分过程**：
   - **目标值调整**：以滑动条动态显示当前二分的中位数目标。
   - **验证步骤**：展示哪些元素被增加至目标值，消耗的操作次数以进度条表示。
4. **音效与反馈**：
   - **成功验证**：播放8-bit上升音效。
   - **失败验证**：播放短促低音。

**交互功能**：
- **步进控制**：允许单步执行二分或贪心选择。
- **AI自动模式**：自动展示最优路径，如红色箭头指示操作分配。

---

### 总结

本题通过排序与分治思想，结合贪心与二分法，解决了动态中位数最大化问题。核心在于灵活选择直接增益或间接增益，并通过高效验证策略确保最优解。可视化设计可通过复古像素动画强化理解，帮助掌握贪心策略与二分法的协同应用。

---
处理用时：90.97秒