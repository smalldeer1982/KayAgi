# 题目信息

# Equalize

## 题目描述

Vasya has two hobbies — adding permutations $ ^{\dagger} $ to arrays and finding the most frequently occurring element. Recently, he found an array $ a $ and decided to find out the maximum number of elements equal to the same number in the array $ a $ that he can obtain after adding some permutation to the array $ a $ .

More formally, Vasya must choose exactly one permutation $ p_1, p_2, p_3, \ldots, p_n $ of length $ n $ , and then change the elements of the array $ a $ according to the rule $ a_i := a_i + p_i $ . After that, Vasya counts how many times each number occurs in the array $ a $ and takes the maximum of these values. You need to determine the maximum value he can obtain.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, it is optimal to choose $ p = [2, 1] $ . Then after applying the operation, the array $ a $ will be $ [3, 3] $ , in which the number $ 3 $ occurs twice, so the answer is $ 2 $ .

In the second test case, one of the optimal options is $ p = [2, 3, 1, 4] $ . After applying the operation, the array $ a $ will be $ [9, 4, 5, 5] $ . Since the number $ 5 $ occurs twice, the answer is $ 2 $ .

## 样例 #1

### 输入

```
7
2
1 2
4
7 1 4 1
3
103 102 104
5
1 101 1 100 1
5
1 10 100 1000 1
2
3 1
3
1000000000 999999997 999999999```

### 输出

```
2
2
3
2
1
1
2```

# AI分析结果



## 【唯一算法分类】
滑动窗口（双指针）

---

## **综合分析与结论**
### **核心思路**
题目要求通过添加排列使相同元素最多，关键结论是：原数组重复元素无法贡献多个结果，必须去重。排序后，问题转化为在单调递增数组中找最长子数组，满足最大值与最小值之差 ≤ n-1。采用滑动窗口（双指针）或二分法解决。

### **解决难点**
1. **去重与排序**：确保相同的元素只保留一个，避免无效计算。
2. **区间条件推导**：推导出区间极差 ≤ n-1 的条件，保证所有元素能通过排列调整为同一值。
3. **高效求解**：滑动窗口在 O(n) 时间找到最长区间，二分法在 O(n log n) 时间实现。

### **可视化设计**
- **动画方案**：以排序后的数组为横轴，左右指针 `l` 和 `r` 高亮当前区间。每次 `r` 右移时，若区间极差 ≤ n-1，扩展区间；否则移动 `l`。动态更新最大区间长度。
- **颜色标记**：当前区间用绿色背景，指针用红色，最大长度区间用黄色边框。
- **步进控制**：允许单步执行观察指针移动逻辑。
- **复古像素风**：采用 8-bit 风格渲染数组元素，指针移动时播放“哔”音效，找到新最大值时播放“胜利”音效。

---

## **题解清单 (≥4星)**
1. **Kdlyh（5星）**
   - 亮点：同时提供双指针和二分两种实现，代码简洁高效，逻辑清晰。
   - 核心代码片段：
     ```cpp
     for (int i = 0, j = 0; i < a.size(); i++) {
         while (j < a.size() && a[i] + n - 1 >= a[j]) j++;
         ans = max(ans, j - i);
     }
     ```

2. **2huk（4星）**
   - 亮点：详细推导区间条件，双指针实现正确且代码易读。
   - 核心代码片段：
     ```cpp
     for (int r = 0, l = 0; r < m; ++r) {
         while (l <= r && a[r] + 1 - a[l] > n) l++;
         res = max(res, r - l + 1);
     }
     ```

3. **UniGravity（4星）**
   - 亮点：代码简洁，直接维护极差条件，去重逻辑清晰。
   - 核心代码片段：
     ```cpp
     for (int s = 1, t = 1; s <= m; s++) {
         while (t < m && b[t + 1] - b[s] < n) t++;
         ans = max(ans, t - s + 1);
     }
     ```

---

## **最优思路提炼**
**滑动窗口法**：排序去重后，维护窗口 `[l, r]`，确保 `a[r] - a[l] ≤ n-1`。右指针 `r` 尽可能扩展，不满足条件时左移 `l`，时间复杂度 O(n)。

**关键技巧**：
1. **去重优化**：减少无效计算，确保每个元素唯一。
2. **极差条件**：利用单调性快速判断区间可行性。
3. **双指针同步移动**：无需回退指针，保证线性时间复杂度。

---

## **相似题目推荐**
1. **洛谷 P1638 逛画展**：滑动窗口求最小覆盖区间。
2. **LeetCode 209. 长度最小的子数组**：双指针寻找满足条件的子数组。
3. **Codeforces 279B - Books**：滑动窗口求最大连续子序列和。

---

## **个人心得摘录**
- **去重陷阱**：部分题解因未正确去重或排序导致错误（如无名之雾提到排序范围错误）。
- **极差推导**：多篇题解强调极差 ≤ n-1 的数学证明是解题关键。
- **双指针优化**：初始暴力枚举 O(n²) 不可行，滑动窗口显著提升效率。

---

## **可视化核心代码（伪代码）**
```javascript
// 初始化数组和指针
let a = sortedUniqueArray;
let l = 0, r = 0, maxLen = 0;

function animateStep() {
    if (r < a.length && a[r] - a[l] <= n-1) {
        maxLen = Math.max(maxLen, r - l + 1);
        r++;
    } else {
        l++;
    }
    // 更新画布，高亮当前区间 [l, r]
    drawCanvas(a, l, r, maxLen);
    // 触发音效
    playSound('beep');
}
```

**复古风格设计**：
- **Canvas 绘制**：数组元素以 16x16 像素方块呈现，当前区间绿色，指针红色。
- **音效**：步进时播放 8-bit 音效，最大长度更新时播放胜利音效。
- **自动演示**：设置定时器逐步执行 `animateStep`，速度可调。

---
处理用时：131.57秒