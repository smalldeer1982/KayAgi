# 题目信息

# Queue

## 题目描述

Little girl Susie went shopping with her mom and she wondered how to improve service quality.

There are $ n $ people in the queue. For each person we know time $ t_{i} $ needed to serve him. A person will be disappointed if the time he waits is more than the time needed to serve him. The time a person waits is the total time when all the people who stand in the queue in front of him are served. Susie thought that if we swap some people in the queue, then we can decrease the number of people who are disappointed.

Help Susie find out what is the maximum number of not disappointed people can be achieved by swapping people in the queue.

## 说明/提示

Value $ 4 $ is achieved at such an arrangement, for example: $ 1,2,3,5,15 $ . Thus, you can make everything feel not disappointed except for the person with time 5.

## 样例 #1

### 输入

```
5
15 2 1 5 3
```

### 输出

```
4
```

# AI分析结果



**唯一算法分类**  
贪心算法

---

### **题解思路与核心难点**  
所有题解均采用**贪心策略**，核心思想是将服务时间从小到大排序，依次累加时间总和，确保当前人的等待时间不超过其服务时间。  
- **关键点**：排序后按顺序选择，若当前总时间 ≤ 当前人服务时间，则选中并累加其时间；否则跳过。  
- **解决难点**：贪心的正确性通过交换相邻逆序元素可更优的交换论证证明，确保选择顺序最优。

---

### **题解评分 (≥4星)**  
1. **Michael123456 (5星)**  
   - **亮点**：代码简洁，直接排序后遍历，逻辑清晰。  
   - **代码**：时间复杂度为 O(n log n)，代码可读性高。  

2. **封禁用户 (AC代码) (4星)**  
   - **亮点**：通过错误示例强调核心逻辑，最终代码简洁正确。  
   - **代码**：排序后仅累加满足条件的时间，避免错误累加。  

3. **宁_缺 (4星)**  
   - **亮点**：使用优先队列实现排序逻辑，提供另一种实现视角。  
   - **代码**：虽复杂度相同，但展示 STL 容器的灵活应用。

---

### **最优思路提炼**  
1. **贪心策略**：按服务时间升序排列，确保每次选择后总等待时间最小。  
2. **关键变量**：维护累加变量 `sum`，仅当 `sum ≤ t_i` 时选中并更新 `sum`。  
3. **跳过处理**：不满足条件时直接跳过，避免影响后续判断。

---

### **同类型题与算法套路**  
- **通用解法**：贪心选择最小代价元素，确保局部最优推导全局最优。  
- **类似题目**：  
  1. **洛谷 P1230**（智力大冲浪）：贪心选择截止时间早的任务。  
  2. **活动安排问题**：选择不冲突且结束时间最早的活动。  

---

### **推荐相似题目**  
1. [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)  
2. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)  
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)  

---

### **代码核心实现**  
```cpp
// 核心代码片段（Michael123456 的题解）
sort(a + 1, a + n + 1); // 排序
int sum = 0, ans = 0;
for (int i = 1; i <= n; i++) {
    if (sum <= a[i]) {  // 判断是否满足条件
        ans++;
        sum += a[i];    // 累加时间
    }
}
```

---

### **可视化与算法演示**  
**动画方案**：  
1. **排序阶段**：展示数组从小到大排序过程。  
2. **遍历选择**：  
   - 高亮当前元素，若 `sum ≤ t_i`，标记为绿色并累加 `sum`。  
   - 否则标记为红色，跳过不累加。  
3. **状态面板**：实时显示 `sum` 和 `ans` 的值。  

**复古像素风格**：  
- **颜色**：绿色方块表示选中，红色表示跳过。  
- **音效**：选中时播放“成功”音效，跳过时播放“失败”音效。  
- **自动演示**：按步长自动执行，支持暂停/继续。  

---

### **总结**  
本题通过贪心排序确保总等待时间最小化，代码简洁且高效。关键在理解贪心策略的证明和正确实现累加逻辑。通过可视化可直观观察选择过程，加深对贪心算法的理解。

---
处理用时：108.45秒