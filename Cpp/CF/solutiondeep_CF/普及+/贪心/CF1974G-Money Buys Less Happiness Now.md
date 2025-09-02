# 题目信息

# Money Buys Less Happiness Now

## 题目描述

You can never buy enough happiness, so here we go again! In this version, you can only buy $ h_i = 1 $ unit of happiness each month, but the number of months is hugely increased. We are in the realm of quantum happiness and time dilation.

Being a physicist, Charlie likes to plan his life in simple and precise terms.

For the next $ m $ months, starting with no money, Charlie will work hard and earn $ x $ pounds per month. For the $ i $ -th month $ (1 \le i \le m) $ , there'll be a single opportunity of paying cost $ c_i $ pounds to obtain one unit of happiness. You cannot buy more than one unit each month.

Borrowing is not allowed. Money earned in the $ i $ -th month can only be spent in a later $ j $ -th month ( $ j>i $ ).

Since physicists don't code, help Charlie find the maximum reachable units of happiness.

## 样例 #1

### 输入

```
6
3 3
2 2 2
6 5
2 2 8 2 6 8
6 4
4 10 3 8 6 10
2 1
1 1
4 1
4 1 3 1
4 2
1 3 4 3```

### 输出

```
2
4
3
1
2
1```

# AI分析结果



### 题目翻译

# 金钱此时买不到更多的幸福

## 题目描述

你永远买不到足够的幸福，所以这次又来了！在这个版本中，你每个月只能购买 $ h_i = 1 $ 单位的幸福，但月份数量大幅增加。我们处于量子幸福和时间膨胀的领域。

作为物理学家，Charlie 喜欢用简单而精确的术语规划他的生活。

在接下来的 $ m $ 个月里，Charlie 一开始没有钱，每个月通过努力工作赚取 $ x $ 英镑。在第 $ i $ 个月（$ 1 \le i \le m $），有一次支付 $ c_i $ 英镑获得 1 单位幸福的机会。每个月最多只能购买一次幸福。

不允许借贷。第 $ i $ 个月赚的钱只能用于之后的月份（$ j > i $）。

由于物理学家不擅长编程，请帮助 Charlie 找到可获得的幸福单位数的最大值。

### 样例输入与输出（略）

---

### 题解综合分析

本题核心在于反悔贪心策略。所有题解均围绕维护一个大根堆来记录已购买的幸福值，当资金不足时替换掉历史最高开销的购买操作。关键点在于动态调整购买选择以最大化总幸福数。

#### 最优题解亮点

1. **DrAlfred 的题解（⭐⭐⭐⭐⭐）**
   - **核心思路**：始终尝试购买当前月份的幸福值，若资金不足则弹出堆顶（历史最大开销），保证当前资金非负。通过优先队列实现高效维护。
   - **代码亮点**：直接处理所有情况，代码简洁高效，时间复杂度 $O(m \log m)$。
   - **代码片段**：
     ```cpp
     priority_queue<i64> heap;
     for (int i = 1; i <= m; i++) {
         cin >> c;
         heap.push(c);
         sum -= c;
         if (sum < 0) { // 资金不足时弹出最大值
             sum += heap.top();
             heap.pop();
         }
         sum += x; // 月末获得资金
     }
     ```

2. **Malkin_Moonlight 的题解（⭐⭐⭐⭐）**
   - **核心思路**：与 DrAlfred 思路一致，代码结构清晰，变量命名易读。
   - **代码亮点**：逻辑与 DrAlfred 完全一致，但变量命名更直观。

3. **hanss6 的题解（⭐⭐⭐⭐）**
   - **核心思路**：同样采用反悔贪心，强调堆的作用，代码极简。
   - **亮点**：代码量最少，适合快速理解算法核心。

---

### 关键思路总结

- **反悔贪心策略**：始终优先选择当前最优解（购买当前月份），若后续发现更优解（更低开销）则撤销历史高价操作。
- **大根堆维护**：记录已购买的幸福值开销，动态替换最高开销以释放更多资金。
- **时间复杂度**：每次堆操作为 $O(\log m)$，总复杂度 $O(m \log m)$。

---

### 类似题目推荐

1. **[P4053 建筑抢修](https://www.luogu.com.cn/problem/P4053)**  
   **相似点**：反悔贪心，通过堆维护任务选择，动态替换无法及时完成的任务。

2. **[CF1526C2 Potions (Hard Version)](https://www.luogu.com.cn/problem/CF1526C2)**  
   **相似点**：反悔贪心处理生命值问题，优先队列维护已选择的药水。

3. **[P9749 [CSP-J 2023] 公路](https://www.luogu.com.cn/problem/P9749)**  
   **相似点**：贪心策略结合动态调整，维护最优加油选择。

---

### 调试心得摘录

- **DrAlfred**：无需复杂条件判断，直接弹出堆顶即可保证资金有效。
- **hanss6**：强调堆在反悔贪心中的核心作用，类比其他经典问题加深理解。

---
处理用时：331.45秒