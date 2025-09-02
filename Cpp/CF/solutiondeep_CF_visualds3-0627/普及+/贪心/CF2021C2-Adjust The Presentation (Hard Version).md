# 题目信息

# Adjust The Presentation (Hard Version)

## 题目描述

This is the hard version of the problem. In the two versions, the constraints on $ q $ and the time limit are different. In this version, $ 0 \leq q \leq 2 \cdot 10^5 $ . You can make hacks only if all the versions of the problem are solved.

A team consisting of $ n $ members, numbered from $ 1 $ to $ n $ , is set to present a slide show at a large meeting. The slide show contains $ m $ slides.

There is an array $ a $ of length $ n $ . Initially, the members are standing in a line in the order of $ a_1, a_2, \ldots, a_n $ from front to back. The slide show will be presented in order from slide $ 1 $ to slide $ m $ . Each section will be presented by the member at the front of the line. After each slide is presented, you can move the member at the front of the line to any position in the lineup (without changing the order of the rest of the members). For example, suppose the line of members is $ [\color{red}{3},1,2,4] $ . After member $ 3 $ presents the current slide, you can change the line of members into either $ [\color{red}{3},1,2,4] $ , $ [1,\color{red}{3},2,4] $ , $ [1,2,\color{red}{3},4] $ or $ [1,2,4,\color{red}{3}] $ .

There is also an array $ b $ of length $ m $ . The slide show is considered good if it is possible to make member $ b_i $ present slide $ i $ for all $ i $ from $ 1 $ to $ m $ under these constraints.

However, your annoying boss wants to make $ q $ updates to the array $ b $ . In the $ i $ -th update, he will choose a slide $ s_i $ and a member $ t_i $ and set $ b_{s_i} := t_i $ . Note that these updates are persistent, that is changes made to the array $ b $ will apply when processing future updates.

For each of the $ q+1 $ states of array $ b $ , the initial state and after each of the $ q $ updates, determine if the slideshow is good.

## 说明/提示

For the first test case, you do not need to move the members as both slides are presented by member $ 1 $ , who is already at the front of the line. After that, set $ b_1 := 2 $ , now slide $ 1 $ must be presented by member $ 2 $ which is impossible as member $ 1 $ will present slide $ 1 $ first. Then, set $ b_1 = 1 $ , the $ b $ is the same as the initial $ b $ , making a good presentation possible.

## 样例 #1

### 输入

```
3
4 2 2
1 2 3 4
1 1
1 2
1 1
3 6 2
1 2 3
1 1 2 3 3 2
3 3
2 2
4 6 2
3 1 4 2
3 1 1 2 3 4
3 4
4 2```

### 输出

```
YA
TIDAK
YA
YA
TIDAK
YA
TIDAK
YA
YA```

# AI分析结果



---

## **综合分析与结论**

### **核心思路与贪心策略**
1. **关键条件**：每个数在 `b` 中的首次出现位置需严格递增，即对于任意 `i`，`i` 的首次出现位置必须早于 `i+1` 的首次出现位置。若此条件满足，则可通过调整队首位置生成合法序列。
2. **数据结构选择**：
   - 使用 `set` 维护每个数在 `b` 中的所有出现位置，快速获取首次出现的最小值。
   - 维护一个计数器 `cnt`，统计所有违反递增条件的相邻对 `(i, i+1)` 的数量。当 `cnt=0` 时合法。
3. **动态更新**：每次修改 `b` 的某位置时，更新相关 `set` 并检查受影响相邻对的合法性，更新 `cnt`。

### **算法难点与解决**
- **高效维护首次出现顺序**：通过 `set` 的自动排序特性，快速获取最小值。
- **动态条件判断**：每次修改仅影响局部相邻对，避免全局遍历。
- **边界处理**：处理 `i=1` 和 `i=n` 的特殊情况，避免越界。

---

## **题解清单 (≥4星)**

### **1. 作者：chenxi2009（★★★★☆）**
- **核心思路**：
  - 将 `b` 映射为原排列中的位置，维护每个数的首次出现位置。
  - 用 `set` 存储每个数的所有出现位置，`cnt` 统计非法相邻对。
- **亮点**：
  - 代码简洁，通过 `set` 和 `cnt` 高效处理动态修改。
  - 边界条件处理清晰，利用 `map` 快速映射原排列位置。

### **2. 作者：Day_Tao（★★★★☆）**
- **核心思路**：
  - 维护 `S[i]` 为每个数的出现位置集合，`cnt` 统计 `S[i-1].begin() > S[i].begin()` 的对数。
- **亮点**：
  - 引入 `S[0]` 和 `S[n+1]` 简化边界判断。
  - 修改时通过前后影响局部更新 `cnt`，复杂度稳定。

### **3. 作者：GY程袁浩（★★★★☆）**
- **核心思路**：
  - 用线段树维护每个数的首次出现位置，判断全局是否递增。
- **亮点**：
  - 线段树实现全局单调性检查，支持快速单点修改。
  - 代码结构清晰，利用线段树合并区间信息。

---

## **最优思路与技巧提炼**

### **贪心选择策略**
- **首次出现顺序**：合法序列的充要条件是每个数的首次出现位置严格递增。
- **动态维护**：每次修改仅需更新相关数的 `set`，并检查相邻对的合法性。

### **实现技巧**
1. **set 的高效操作**：
   ```cpp
   set<int> q[N];  // q[i] 存储数 i 的所有出现位置
   auto first_pos = *q[i].begin();  // 获取首次出现位置
   ```
2. **计数器更新逻辑**：
   ```cpp
   // 修改前删除旧值的影响
   if (旧值影响相邻对) cnt--;
   // 插入新值后检查新影响
   if (新值导致相邻对不合法) cnt++;
   ```
3. **边界处理**：
   ```cpp
   if (i == 1) continue;  // i=1 无前驱，无需检查
   ```

---

## **同类型题目与算法套路**

### **通用解法**
- **依赖顺序问题**：若问题中元素的合法性依赖于其前驱的顺序（如任务调度、区间覆盖），可维护首次出现或最早完成时间。
- **动态维护有序性**：通过平衡树、线段树等结构维护关键属性的动态变化。

### **类似题目**
1. **洛谷 P1090**（合并果子）：贪心选择最小两堆，优先队列实现。
2. **洛谷 P2870**（任务调度）：按截止时间排序，维护当前时间。
3. **洛谷 P4053**（建筑抢修）：贪心+堆维护已选任务。

---

## **代码实现（核心逻辑）**

### **关键代码片段（chenxi2009 版本）**
```cpp
set<int> q[200001]; // 每个数在 b 中的出现位置集合
int cnt = 0;        // 非法相邻对数量

// 初始化每个数的出现位置
for (int i = 1; i <= m; i++) {
    q[b[i]].insert(i);
}

// 初始检查相邻对合法性
for (int i = 2; i <= n; i++) {
    if (!q[i].empty() && (q[i-1].empty() || *q[i-1].begin() > *q[i].begin())) {
        cnt++;
    }
}

// 处理每次修改
void update(int s, int old_val, int new_val) {
    // 删除旧值的影响
    q[old_val].erase(s);
    if (old_val > 1 && !q[old_val-1].empty() && *q[old_val-1].begin() > *q[old_val].begin()) {
        cnt--;
    }
    // 类似处理其他相邻对...

    // 插入新值的影响
    q[new_val].insert(s);
    if (new_val > 1 && (q[new_val-1].empty() || *q[new_val-1].begin() > *q[new_val].begin())) {
        cnt++;
    }
    // 类似处理其他相邻对...
}
```

---

## **可视化与算法演示**

### **动画设计**
- **像素风格界面**：
  - 每个数用不同颜色方块表示，首次出现位置标为高亮。
  - 非法相邻对用红色连线标记，合法后变绿。
- **交互操作**：
  - **步进控制**：单步执行修改，显示 `set` 和 `cnt` 变化。
  - **音效**：正确时播放清脆音效，错误时低沉提示。

### **AI 自动演示**
- **自动生成修改序列**，模拟不同策略下的 `cnt` 变化。
- **动态高亮当前处理的相邻对**，显示 `set` 的最小值比较过程。

---

## **复古游戏化设计**
- **8-bit 像素风格**：
  - 使用 Canvas 绘制队列和 `set` 结构，方块代表位置。
  - 背景音乐循环播放 FC 风格旋律。
- **积分与连击**：
  - 每次合法修改得 10 分，连续合法触发连击倍率。
  - 错误时连击重置，播放“失败”音效。
- **关卡模式**：
  - 初级：固定修改序列，学习维护逻辑。
  - 高级：随机生成高频率修改，考验反应。

---
处理用时：91.59秒