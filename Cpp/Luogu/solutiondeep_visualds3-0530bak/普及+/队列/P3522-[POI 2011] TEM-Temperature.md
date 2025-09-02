# 题目信息

# [POI 2011] TEM-Temperature

## 题目描述

The Byteotian Institute of Meteorology (BIM) measures the air temperature  daily.

The measurement is done automatically, and its result immediately printed.

Unfortunately, the ink in the printer has long dried out...

The employees of BIM however realised the fact only recently, when the    Byteotian Organisation for Meteorology (BOM) requested access to that data.

An eager intern by the name of Byteasar saved the day, as he systematically    noted down the temperatures reported by two domestic alcohol thermometers    placed on the north and south outside wall of the BIM building.

It was established decades ago by various BIM employees that the temperature    reported by the thermometer on the south wall of the building is never lower    than the actual temperature, while that reported by the thermometer on the    north wall of the building is never higher than the actual temperature.

Thus even though the exact temperatures for each day remain somewhat of    a mystery, the range they were in is known at least.

Fortunately for everyone involved (except Byteasar and you, perhaps),    BOM does not require exact temperatures. They only want to know the longest    period in which the temperature was not dropping (i.e. on each successive    day it was no smaller than on the day before).

In fact, the veteran head of BIM knows very well that BOM would like this    period as long as possible.

To whitewash the negligence he insists that Byteasar determines, based on    his valuable notes, the longest period in which the temperature    could have been not dropping.

Now this is a task that Byteasar did not quite expect on his BIM internship,    and he honestly has no idea how to tackle it.

He asks you for help in writing a program that determines the longest such    period.

某国进行了连续 $ n $ ( $ 1 \le n \le 1,000,000 $）天的温度测量，测量存在误差，测量结果是第 $i$ 天温度在 $[l_i,r_i]$ 范围内。

求最长的连续的一段，满足该段内可能温度不降。


## 样例 #1

### 输入

```
6
6 10
1 5
4 8
2 5
6 8
3 5```

### 输出

```
4```

# AI分析结果



**唯一算法分类**：单调队列

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
寻找最长连续天数，使得存在温度序列非降。关键点在于维护当前区间的最低温度最大值，确保后续天数的最高温度不低于该值。单调队列用于高效维护可能的最长区间。

#### **算法要点**
1. **单调队列维护**：队列保存可能作为区间左端点的元素，按最低温度降序排列，确保队头为当前最大最低温度。
2. **区间扩展条件**：新一天的 `r[i]` 必须 ≥ 队列中所有天的 `l` 的最大值（即队头 `l`）。
3. **队列调整**：
   - **队头弹出**：若队头 `l > r[i]`，则无法与新天构成区间，需弹出。
   - **队尾维护单调性**：弹出队尾 `l ≤ 当前天 l` 的元素，保持队列递减。

#### **解决难点**
- **连续区间起始维护**：在弹出队尾元素时，记录最后一个被弹出的起始天数，确保新天的区间起始正确。
- **时间复杂度优化**：通过单调队列将复杂度降至 O(n)，避免暴力枚举所有可能区间。

---

### **题解评分 (≥4星)**

1. **Lonely_NewYear (5星)**  
   - **亮点**：通过记录 `tmp` 维护连续区间起始，代码简洁高效，正确处理了队列合并逻辑。
   - **代码可读性**：结构清晰，注释明确。
   
2. **zhendelan (5星)**  
   - **亮点**：队列存储区间起始和最低温度，代码极简且效率高，直接维护单调性。
   - **实现关键**：`q[++t]=i; st[t]=tmp;` 动态更新起始位置。

3. **chenxinyang2006 (4星)**  
   - **亮点**：RMQ预处理+双指针，思路直观，适合理解单调队列前的过渡。
   - **优化点**：双指针调整左端点，无需复杂数据结构。

---

### **最优思路或技巧提炼**
- **队列维护起始天数**：在弹出队尾时记录最后一个元素的起始天数，确保新区间连续。
- **动态维护最大最小值**：单调队列天然维护当前窗口的最值，避免重复计算。
- **代码简化技巧**：将区间起始与队列元素绑定，减少额外变量。

---

### **同类型题与算法套路**
- **滑动窗口最值**：如 [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)。
- **区间合法性判断**：需保证区间内某条件始终满足（如最大值 ≤ 阈值）。

---

### **推荐题目**
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)  
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)  
3. [P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)  

---

### **个人心得摘录**
- **Lonely_NewYear**：调试时发现单纯弹出队尾无法维护起始天数，引入 `tmp` 解决。
- **Holy_Push**：线段树实现复杂，但动态规划思路为其他问题提供启发。

---

### **可视化与算法演示**
**动画方案**：
1. **队列变化**：用像素方块表示队列元素，颜色区分操作：
   - **红色**：弹出队头（`l > r[i]`）。
   - **蓝色**：弹出队尾（`l ≤ 当前天 l`）。
   - **绿色**：新元素入队。
2. **区间高亮**：当前最长区间用闪烁边框标记。
3. **音效设计**：
   - 弹出操作：短促“哔”声。
   - 更新最长区间：上扬音调。
4. **Canvas 交互**：支持拖拽调整输入数据，实时展示队列变化。

**复古风格**：
- **8位像素UI**：队列显示为横向方块，颜色使用FC经典16色调。
- **自动演示**：模拟AI逐步处理输入，展示队列调整过程。

---

### **核心代码实现**
```cpp
// Lonely_NewYear 题解核心代码
deque<node> q;
for (int i=1; i<=n; i++) {
    while (!q.empty() && q.front().l > r[i]) q.pop_front();
    int tmp = i;
    while (!q.empty() && q.back().l < l[i]) {
        tmp = q.back().id; // 记录最后弹出的起始天数
        q.pop_back();
    }
    q.push_back({l[i], r[i], tmp});
    ans = max(ans, i - q.front().id + 1);
}
```

**代码说明**：维护队列单调性，动态更新起始天数 `tmp`，确保新区间连续。

---
处理用时：71.50秒