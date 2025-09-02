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



**算法分类**  
二分

---

### **题解思路与算法要点**  
题目要求在最多k次操作后，最大化得分。核心思路是结合二分答案与贪心策略，处理两种情况：  
1. **直接提升某个元素**：将k次操作全用于可操作的最大元素，使其成为最大值后计算得分。  
2. **提升中位数**：通过二分法确定剩余数组的最大可能中位数mid，计算原最大值与mid之和。

**解决难点**  
- **二分条件确定**：如何验证是否能在k次操作内使足够多的元素≥mid。  
- **贪心策略**：优先处理需要最少操作次数的元素，以最小化总成本。  
- **两种情况的结合**：分别计算两种策略的得分，取最大值。

---

### **题解评分 (≥4星)**  
1. **BrotherCall（4星）**  
   - 思路清晰，结合二分与贪心，代码结构明确。  
   - 关键点：二分验证中位数可行性，处理两种情况的最大值。  
   - 代码可读性较好，但部分逻辑需深入理解。

2. **liugh_（4星）**  
   - 简洁的二分实现，分情况讨论得分。  
   - 代码核心逻辑直接，突出贪心与二分的结合。  
   - 验证逻辑高效，时间复杂度合理。

3. **yshpdyt（4星）**  
   - 明确分拆两种策略，二分部分逻辑清晰。  
   - 代码中包含详细注释，便于理解中位数计算与操作分配。  
   - 优化判断条件，减少不必要的计算。

---

### **最优思路与技巧**  
1. **二分答案的应用**  
   - **搜索区间**：初始`left`为原数组最小值，`right`为原最大值+k。  
   - **条件判断**：验证是否能让至少半数元素≥mid，贪心选择最少的操作次数。  
   - **边界处理**：`mid=(l+r+1)>>1`避免死循环，保证收敛。

2. **贪心策略**  
   - 将需要提升的元素按操作代价排序，优先处理代价小的。  
   - 统计满足条件的元素数量，确保总操作次数≤k。

3. **得分分情况计算**  
   - 若最大元素可操作，直接提升至`a_max +k`。  
   - 否则，二分找到最大中位数mid，计算`a_max +mid`。

---

### **同类型题与算法套路**  
- **二分答案常见题**：如“最大化最小值”“最小化最大值”。  
- **贪心优化操作分配**：如[CF1796C] Maximum Set、[LeetCode 410] Split Array Largest Sum。  
- **中位数性质利用**：中位数为中间位置的元素，排序后直接取索引。

---

### **推荐题目**  
1. **P1020 导弹拦截**（贪心与二分结合）  
2. **P2678 跳石头**（经典二分答案）  
3. **CF1117C Magic Ship**（二分与条件验证）  

---

### **可视化与算法演示**  
**动画设计**  
1. **Canvas绘制**：显示排序后的数组，高亮当前二分区间`[left, right]`。  
2. **步进操作**：每次计算`mid`时，标记需提升的元素及操作次数。  
3. **颜色区分**：  
   - 绿色：已满足≥mid的元素。  
   - 黄色：需操作且可行的元素。  
   - 红色：无法操作或操作后仍不满足。  
4. **音效反馈**：  
   - 点击步进时播放“哔”声，成功验证mid时播放上扬音效。  

**复古像素风格**  
- **8位调色板**：使用深蓝（背景）、绿（区间）、红（mid）。  
- **网格布局**：数组元素以方块表示，操作次数显示在方块下方。  
- **AI自动演示**：按最优路径自动调整区间，展示二分过程。

---

### **核心代码实现**  
```cpp
bool check(int mid) {
    vector<int> costs;
    int cnt = 0, required = (n - 1 + 1) / 2;
    for (int i = 0; i < n - 1; i++) { // 假设删除最大元素
        if (a[i] >= mid) cnt++;
        else if (b[i]) 
            costs.push_back(mid - a[i]);
    }
    sort(costs.begin(), costs.end());
    int used = 0;
    for (int c : costs) {
        if (used + c > k) break;
        used += c;
        cnt++;
    }
    return cnt >= required;
}

// 二分逻辑
int l = min_val, r = max_val + k, ans_mid = 0;
while (l <= r) {
    int mid = (l + r + 1) >> 1;
    if (check(mid)) {
        ans_mid = mid;
        l = mid + 1;
    } else {
        r = mid - 1;
    }
}
```

---

### **总结**  
通过二分验证中位数可行性，结合贪心策略分配操作次数，分情况计算最大值。复古动画可直观展示二分与贪心的协同过程，增强理解。

---
处理用时：239.55秒