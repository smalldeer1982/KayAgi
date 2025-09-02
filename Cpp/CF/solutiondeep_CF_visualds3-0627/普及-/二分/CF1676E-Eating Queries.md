# 题目信息

# Eating Queries

## 题目描述

Timur has $ n $ candies. The $ i $ -th candy has a quantity of sugar equal to $ a_i $ . So, by eating the $ i $ -th candy, Timur consumes a quantity of sugar equal to $ a_i $ .

Timur will ask you $ q $ queries regarding his candies. For the $ j $ -th query you have to answer what is the minimum number of candies he needs to eat in order to reach a quantity of sugar greater than or equal to $ x_j $ or print -1 if it's not possible to obtain such a quantity. In other words, you should print the minimum possible $ k $ such that after eating $ k $ candies, Timur consumes a quantity of sugar of at least $ x_j $ or say that no possible $ k $ exists.

Note that he can't eat the same candy twice and queries are independent of each other (Timur can use the same candy in different queries).

## 说明/提示

For the first test case:

For the first query, Timur can eat any candy, and he will reach the desired quantity.

For the second query, Timur can reach a quantity of at least $ 10 $ by eating the $ 7 $ -th and the $ 8 $ -th candies, thus consuming a quantity of sugar equal to $ 14 $ .

For the third query, there is no possible answer.

For the fourth query, Timur can reach a quantity of at least $ 14 $ by eating the $ 7 $ -th and the $ 8 $ -th candies, thus consuming a quantity of sugar equal to $ 14 $ .

For the second test case:

For the only query of the second test case, we can choose the third candy from which Timur receives exactly $ 3 $ sugar. It's also possible to obtain the same answer by choosing the fourth candy.

## 样例 #1

### 输入

```
3
8 7
4 3 3 1 1 4 5 9
1
10
50
14
15
22
30
4 1
1 2 3 4
3
1 2
5
4
6```

### 输出

```
1
2
-1
2
3
4
8
1
1
-1```

# AI分析结果



# 算法分类：二分

---

## 题解思路与难点

### 核心思路
- **贪心排序**：按糖果糖分降序排列，优先吃高糖分糖果。
- **前缀和预处理**：构建单调递增的前缀和数组，便于快速计算总糖分。
- **二分查找**：在排序后的前缀和数组中，找到第一个 ≥ 查询值的最小下标。

### 解决难点
- **二分条件与区间收缩**：
  - **初始区间**：`left=1`，`right=n`（前缀和数组有效范围）。
  - **终止条件**：`left <= right`，保证所有可能值被覆盖。
  - **收缩逻辑**：若 `sum[mid] >= x`，则尝试更小的右区间（`right=mid-1`），否则扩大左区间（`left=mid+1`）。
- **边界处理**：总和不足时返回 `-1`，利用 `lower_bound` 或手动实现避免死循环。

---

## 题解评分（≥4星）

1. **Otue（5星）**
   - **亮点**：代码简洁，直接使用 `lower_bound` 简化二分逻辑，预处理高效。
   - **代码示例**：
     ```cpp
     sort(a + 1, a + n + 1, cmp);  // 降序排序
     lower_bound(sum + 1, sum + n + 1, x) - sum; // STL二分
     ```

2. **Coros_Trusds（4.5星）**
   - **亮点**：手动二分实现清晰，兼容性强，适合教学。
   - **代码片段**：
     ```cpp
     int l = 1, r = n, ans = -1;
     while (l <= r) {
         int mid = l + r >> 1;
         if (sum[mid] >= x) r = mid - 1, ans = mid;
         else l = mid + 1;
     }
     ```

3. **LYqwq（4星）**
   - **亮点**：Lambda表达式简化排序，前缀和与二分结合紧密。
   - **核心代码**：
     ```cpp
     sort(a+1, a+n+1, [](int x, int y){return x>y;});
     lower_bound(a+1, a+n+1, x) - a; // 直接操作数组
     ```

---

## 最优思路提炼
1. **降序排序**：确保每次选择糖分最大的糖果。
2. **前缀和单调性**：通过排序保证前缀和数组单调递增，支持二分。
3. **二分边界处理**：
   - 总和不足时直接返回 `-1`。
   - 使用 `lower_bound` 或手动二分确保快速定位最小下标。

---

## 同类型题与算法套路
- **通用解法**：在排序后的数组上，通过前缀和构建单调序列，二分查找满足条件的最小值。
- **类似题目**：
  1. **P2249** 【深基13.例1】查找（基础二分）
  2. **P1678** 烦恼的高考志愿（二分最小差值）
  3. **CF474B** Worms（前缀和+二分定位区间）

---

## 个人心得摘录
- **调试教训**：排序方向错误导致前缀和非单调，需严格验证排序逻辑。
- **顿悟点**：前缀和数组的单调性允许直接使用 `lower_bound`，避免手动二分复杂性。

---

## 可视化与算法演示
### 二分过程动画设计
1. **区间表示**：Canvas绘制数轴，区间 `[left, right]` 用高亮色块标记。
2. **Mid计算**：红色标记当前 `mid`，显示 `sum[mid]` 值。
3. **条件判断**：
   - **满足条件**（`sum[mid] >= x`）：收缩右边界，绿色箭头指向新 `right=mid-1`。
   - **不满足**：收缩左边界，红色箭头指向 `left=mid+1`。
4. **复古像素风格**：
   - **颜色方案**：8-bit调色板，区间块用蓝/黄色，mid用红色像素点。
   - **音效**：移动时播放“哔”声，找到答案时播放胜利音效。
   - **自动演示**：AI逐步执行二分步骤，用户可暂停/调速观察。

### 核心代码（JS伪代码）
```javascript
function binarySearchVisual(sum, x) {
    let left = 1, right = sum.length - 1;
    while (left <= right) {
        let mid = Math.floor((left + right) / 2);
        drawInterval(left, right); // 绘制当前区间
        highlightMid(mid); // 高亮mid
        if (sum[mid] >= x) {
            playSound('success');
            right = mid - 1;
        } else {
            playSound('move');
            left = mid + 1;
        }
    }
    return left <= sum.length ? left : -1;
}
```

---

**推荐题目**：在洛谷练习中巩固二分与前缀和结合的思路，如上述P2249、P1678。

---
处理用时：66.40秒