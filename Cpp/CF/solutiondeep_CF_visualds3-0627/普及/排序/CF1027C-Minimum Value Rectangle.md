# 题目信息

# Minimum Value Rectangle

## 题目描述

You have $ n $ sticks of the given lengths.

Your task is to choose exactly four of them in such a way that they can form a rectangle. No sticks can be cut to pieces, each side of the rectangle must be formed by a single stick. No stick can be chosen multiple times. It is guaranteed that it is always possible to choose such sticks.

Let $ S $ be the area of the rectangle and $ P $ be the perimeter of the rectangle.

The chosen rectangle should have the value $ \frac{P^2}{S} $ minimal possible. The value is taken without any rounding.

If there are multiple answers, print any of them.

Each testcase contains several lists of sticks, for each of them you are required to solve the problem separately.

## 说明/提示

There is only one way to choose four sticks in the first list, they form a rectangle with sides $ 2 $ and $ 7 $ , its area is $ 2 \cdot 7 = 14 $ , perimeter is $ 2(2 + 7) = 18 $ . $ \frac{18^2}{14} \approx 23.143 $ .

The second list contains subsets of four sticks that can form rectangles with sides $ (1, 2) $ , $ (2, 8) $ and $ (1, 8) $ . Their values are $ \frac{6^2}{2} = 18 $ , $ \frac{20^2}{16} = 25 $ and $ \frac{18^2}{8} = 40.5 $ , respectively. The minimal one of them is the rectangle $ (1, 2) $ .

You can choose any four of the $ 5 $ given sticks from the third list, they will form a square with side $ 5 $ , which is still a rectangle with sides $ (5, 5) $ .

## 样例 #1

### 输入

```
3
4
7 2 2 7
8
2 8 1 4 8 2 1 5
5
5 5 5 5 5
```

### 输出

```
2 7 7 2
2 2 1 1
5 5 5 5
```

# AI分析结果



# 算法分类
**贪心算法**

---

## 综合分析与结论

### 核心算法流程
1. **统计出现次数**：用桶排序或哈希表统计每个长度的出现次数。
2. **筛选候选边长**：收集出现次数≥2的边长，并按升序排列。
3. **特判正方形**：若某长度出现≥4次，直接输出该长度的正方形。
4. **贪心比较相邻对**：遍历排序后的候选边长，比较相邻两数的比值，选择最接近1的相邻对。

### 解决难点
- **数学推导**：将目标函数转化为求a/b + b/a的最小值，等价于找相邻的最接近数值。
- **避免浮点运算**：通过交叉相乘比较（如比较a_i*b_j与a_j*b_i）防止精度误差。
- **高效处理大数据**：桶排序或哈希表统计确保时间复杂度为O(n)。

### 可视化设计要点
- **像素动画**：用网格展示候选边长分布，高亮当前比较的a和b。
- **动态比值显示**：在动画中实时显示当前比值及最优解。
- **音效提示**：关键操作（选择候选对、发现正方形）触发8位音效。
- **自动演示模式**：AI自动遍历候选对，展示贪心比较过程。

---

## 题解评分（≥4星）

1. **Siyuan的题解（5星）**
   - **亮点**：数学推导清晰，避免浮点运算，高效处理大数据。
   - **代码**：使用map统计次数，提前特判正方形，代码简洁高效。

2. **YellowBean_Elsa的题解（4星）**
   - **亮点**：桶排序优化统计，特判正方形提升效率。
   - **代码**：数组实现桶排，逻辑清晰，适合大数据量。

3. **Mickey_snow的题解（4星）**
   - **亮点**：数学证明严谨，提出引理优化遍历。
   - **代码**：动态规划式遍历，记录当前最优解。

---

## 最优思路提炼

### 关键技巧
- **数学转换**：将目标函数转化为求a/b + b/a的最小值，简化比较逻辑。
- **相邻贪心**：排序后只需比较相邻元素，时间复杂度降至O(n)。
- **特判优化**：若存在四次相同长度，直接输出正方形，无需后续计算。

### 代码片段（Siyuan核心逻辑）
```cpp
std::map<int, int> cnt;
// 统计次数并筛选候选边长
for (auto it : cnt) {
    if (it.second >= 2) a[++m] = it.first;
    if (it.second >= 4) { // 特判正方形
        printf("%d %d %d %d\n", ans, ans, ans, ans);
        flg = 1; break;
    }
}
// 贪心比较相邻对
int x = a[1], y = a[2];
for (int i = 3; i <= m; i++) {
    if (x * a[i] < a[i-1] * y) {
        x = a[i-1], y = a[i];
    }
}
printf("%d %d %d %d\n", x, x, y, y);
```

---

## 同类型题目与拓展

### 相似算法套路
- **相邻贪心**：如[LeetCode 561. Array Partition I](https://leetcode.com/problems/array-partition-i/)。
- **比值最优化**：如选择两数使a² + b²最小（需排序后取相邻对）。

### 推荐题目
1. **CF977D Divide by three, multiply by two**（贪心排序）
2. **洛谷P1094 纪念品分组**（相邻贪心配对）
3. **LeetCode 1679. Max Number of K-Sum Pairs**（哈希表统计+贪心）

---

## 个人心得摘录

- **浮点陷阱**：多位题解强调避免浮点比较，转化为整数运算。
- **特判优化**：正方形特判可大幅减少计算量，是竞赛常见技巧。

---

## 可视化算法演示（像素风格）

### 动画设计
- **初始化**：木棍长度以像素方块显示，颜色深浅表示出现次数。
- **高亮操作**：当前比较的a和b用闪烁边框标记，比值公式实时更新。
- **音效反馈**：发现正方形时播放胜利音效，错误选择触发警示音。

### 代码片段（Canvas高亮）
```javascript
function drawSticks(sticks) {
    sticks.forEach((stick, idx) => {
        ctx.fillStyle = idx === currentA || idx === currentB ? '#FF0000' : '#00FF00';
        ctx.fillRect(idx * 10, 0, 8, stick * 5); // 高度代表长度
    });
}
```

---

**注**：以上内容整合了多篇题解的核心思想，突出贪心策略与数学优化，适合快速掌握算法本质。

---
处理用时：73.81秒