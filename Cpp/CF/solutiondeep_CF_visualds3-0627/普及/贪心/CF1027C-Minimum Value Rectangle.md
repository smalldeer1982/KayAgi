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



### 综合分析与结论

**题目核心**：选择四根木棍组成矩形，使得周长平方与面积的比值最小。  
**关键推导**：最优解对应的矩形边长比（a/b）尽可能接近1，即优先选正方形或相邻长度。  
**贪心策略**：  
1. 统计所有出现次数≥2的长度，排序后遍历相邻元素对。  
2. 优先处理出现次数≥4的情况（正方形最优）。  
3. 比较相邻元素对时，用乘法代替除法避免精度问题。  

**实现难点**：  
- 高效统计次数（桶排序/map）。  
- 正确遍历相邻元素并维护最优解。  

**可视化设计**：  
- **像素动画**：用不同颜色方块表示长度，高度对应出现次数。  
- **动态比较**：高亮当前比较的相邻元素对，计算比值并更新最优解。  
- **音效提示**：正方形发现时播放成功音效，错误选择时提示警示音。  
- **自动模式**：逐步展示贪心选择过程，支持调速与单步执行。  

---

### 题解清单（≥4星）

1. **Siyuan的题解（★★★★★）**  
   - **亮点**：使用map高效统计，代码简洁，处理相邻元素逻辑清晰。  
   - **核心代码**：遍历排序后的候选数组，维护最优解的x和y。  

2. **YellowBean_Elsa的题解（★★★★☆）**  
   - **亮点**：桶排序实现O(n)统计，特判正方形优化时间。  
   - **心得**：避免浮点比较，用乘法代替除法。  

3. **PanH的题解（★★★★☆）**  
   - **亮点**：数学推导独特，将目标转化为最小化(a-b)^2/(ab)。  
   - **实现**：动态维护前一个可用长度，减少遍历次数。  

---

### 最优思路与技巧提炼

**核心步骤**：  
1. **统计与筛选**：仅保留出现次数≥2的长度。  
2. **排序与遍历**：排序后相邻元素比值为最接近的可能解。  
3. **特判优化**：优先处理正方形情况（出现次数≥4）。  

**关键代码片段**（Siyuan题解）：  
```cpp
// 统计次数并筛选候选数组
std::map<int, int> cnt;
for (int i = 1; i <= n; i++) {
    read(t);
    cnt[t]++;
}
// 处理正方形特判
for (auto it : cnt) {
    if (it.second >= 4) {
        printf("%d %d %d %d\n", it.first, it.first, it.first, it.first);
        flg = 1;
        break;
    }
}
// 遍历相邻候选元素
int x = a[1], y = a[2];
for (int i = 3; i <= m; i++) {
    if (x * a[i] < y * a[i - 1]) {
        x = a[i - 1];
        y = a[i];
    }
}
```

---

### 同类型题与算法套路

**常见贪心场景**：  
- **相邻元素最优**：如任务调度、最小差值对。  
- **比值最优化**：通过排序转化为线性遍历问题。  

**推荐题目**：  
1. **P1090 [NOIP2004 提高组] 合并果子**（贪心+优先队列）  
2. **P1223 [JSOI2007] 书架**（排序后相邻配对）  
3. **P1106 删数问题**（贪心选择最小序列）  

---

### 可视化与算法演示

**复古像素动画设计**：  
- **Canvas绘制**：木棍长度用彩色方块表示，高度=出现次数。  
- **交互逻辑**：  
  1. **高亮候选**：出现≥2次的长度闪烁显示。  
  2. **遍历过程**：箭头指示当前比较的相邻元素对，动态计算比值。  
  3. **音效反馈**：选择正方形时播放8-bit胜利音效。  

**自动演示模式**：  
```javascript
// 伪代码示例
function autoPlay() {
    let pairs = sortedCandidates;
    let bestPair = findSquare() || pairs[0];
    for (let i = 1; i < pairs.length; i++) {
        highlight(pairs[i-1], pairs[i]);
        if (compare(pairs[i-1], pairs[i]) < bestPair.ratio) {
            bestPair = {a: pairs[i-1], b: pairs[i]};
            playSound('select');
        }
        await sleep(speed);
    }
    showResult(bestPair);
}
```

---

### 个人心得摘录

- **浮点陷阱**：比较比值时用交叉乘法避免精度损失。  
- **桶排序优势**：数据范围小时（a_i ≤1e4），桶排序比map更高效。  
- **贪心验证**：通过数学证明相邻元素最优，减少无效计算。  

---

**总结**：本题的核心在于将问题转化为比值最优化，并通过排序与相邻遍历实现高效贪心。可视化设计通过动态交互强化理解，适合教学与自学。

---
处理用时：74.51秒