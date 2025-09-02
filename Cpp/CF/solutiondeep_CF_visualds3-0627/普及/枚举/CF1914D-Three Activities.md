# 题目信息

# Three Activities

## 题目描述

Winter holidays are coming up. They are going to last for $ n $ days.

During the holidays, Monocarp wants to try all of these activities exactly once with his friends:

- go skiing;
- watch a movie in a cinema;
- play board games.

Monocarp knows that, on the $ i $ -th day, exactly $ a_i $ friends will join him for skiing, $ b_i $ friends will join him for a movie and $ c_i $ friends will join him for board games.

Monocarp also knows that he can't try more than one activity in a single day.

Thus, he asks you to help him choose three distinct days $ x, y, z $ in such a way that the total number of friends to join him for the activities ( $ a_x + b_y + c_z $ ) is maximized.

## 说明/提示

In the first testcase, Monocarp can choose day $ 2 $ for skiing, day $ 1 $ for a movie and day $ 3 $ for board games. This way, $ a_2 = 10 $ friends will join him for skiing, $ b_1 = 10 $ friends will join him for a movie and $ c_3 = 10 $ friends will join him for board games. The total number of friends is $ 30 $ .

In the second testcase, Monocarp can choose day $ 1 $ for skiing, day $ 4 $ for a movie and day $ 2 $ for board games. $ 30 + 20 + 25 = 75 $ friends in total. Note that Monocarp can't choose day $ 1 $ for all activities, because he can't try more than one activity in a single day.

In the third testcase, Monocarp can choose day $ 2 $ for skiing, day $ 3 $ for a movie and day $ 7 $ for board games. $ 19 + 19 + 17 = 55 $ friends in total.

In the fourth testcase, Monocarp can choose day $ 1 $ for skiing, day $ 4 $ for a movie and day $ 9 $ for board games. $ 17 + 19 + 20 = 56 $ friends in total.

## 样例 #1

### 输入

```
4
3
1 10 1
10 1 1
1 1 10
4
30 20 10 1
30 5 15 20
30 25 10 10
10
5 19 12 3 18 18 6 17 10 13
15 17 19 11 16 3 11 17 17 17
1 17 18 10 15 8 17 3 13 12
10
17 5 4 18 12 4 11 2 16 16
8 4 14 19 3 12 6 7 5 16
3 4 8 11 10 8 10 2 20 3```

### 输出

```
30
75
55
56```

# AI分析结果



## 算法分类
贪心算法

## 题解思路、算法要点与解决难点

### 核心思路
题目要求从三个数组中各选一个不同天数的元素，使得总和最大。关键难点在于快速排除大量不可能的组合，避免 O(n³) 暴力枚举。通过观察发现，最优解必然由各数组的前几个最大值构成，但需满足天数不重复。

### 算法要点
1. **排序取前三大**：将每个数组按值降序排序，取前三大元素（包含其对应的天数）。
2. **暴力组合检查**：枚举三个数组前三大元素的所有组合（3³=27种可能），筛选天数互不重复的组合，计算最大值。

### 解决难点
- **减少枚举量**：通过排序将问题规模从 O(n³) 降至 O(1)。
- **避免日期冲突**：仅检查前三大的组合即可覆盖最优解的可能情况（反证法可证不存在比前三大的更优组合）。

---

## 题解评分（≥4星）

1. **hjqhs（5星）**
   - 思路清晰：直接排序后取前三大，三层循环枚举。
   - 代码简洁：使用 `pair` 存储值和天数，排序后反向遍历。
   - 高效优化：时间复杂度 O(n log n) + O(1)，完美处理大数范围。

2. **infinite2021（4星）**
   - 明确取前三：代码直接取前三元素，枚举组合。
   - 代码可读性高：结构清晰，但未处理边界（如数组长度不足3时）。
   - 时间复杂度低：与最优解一致。

---

## 最优思路提炼
**贪心+暴力枚举**：  
1. 对每个数组降序排序，保留前三大元素及其天数。
2. 枚举所有组合，筛选天数不重复的组合，记录最大值。

**关键技巧**：  
- 使用 `pair<int, int>` 存储值和天数，便于排序后保留原始天数。
- 仅需遍历前三大的元素组合，确保高效性。

---

## 同类型题与算法套路
**多数组组合问题**：  
- 常见于需要从多个数组中选择元素，且元素需满足特定位置约束（如不同索引）。
- 通用解法：对各数组降维（排序取前 k 大/小），再暴力枚举可行组合。

---

## 推荐题目
1. **洛谷 P1003**：铺地毯（选择覆盖点的最优解）。
2. **洛谷 P1090**：合并果子（贪心选择最小堆）。
3. **洛谷 P1223**：排队接水（贪心排序优化平均值）。

---

## 可视化与算法演示

### 动画设计
1. **排序展示**：三个数组分别降序排列，高亮前三大元素。
2. **组合枚举**：用不同颜色标记当前选中的元素（红、绿、蓝）。
3. **冲突检测**：当天数重复时显示红色警告，有效组合显示绿色。
4. **最大值更新**：动态显示当前最大值及对应组合。

### 复古像素风格
- **颜色方案**：8-bit 色调（红、绿、蓝分别对应三个数组）。
- **音效提示**：选中元素时播放“哔”声，找到最大值时播放胜利音效。
- **Canvas 网格**：将数组元素绘制为方块，数值显示在方块内。

---

## 代码片段（核心逻辑）
```cpp
// 取每个数组前三大元素（已排序）
sort(a + 1, a + n + 1, greater<>());
sort(b + 1, b + n + 1, greater<>());
sort(c + 1, c + n + 1, greater<>());

int max_sum = 0;
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            if (a[i].day != b[j].day && b[j].day != c[k].day && a[i].day != c[k].day) {
                max_sum = max(max_sum, a[i].val + b[j].val + c[k].val);
            }
        }
    }
}
cout << max_sum << endl;
```

---

## 结论
通过贪心策略快速缩小搜索范围，再暴力枚举可行组合，是处理此类多约束优化问题的典型方法。其核心在于利用排序降维，将不可行解快速排除。

---
处理用时：142.05秒