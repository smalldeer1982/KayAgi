# 题目信息

# Electrification

## 题目描述

At first, there was a legend related to the name of the problem, but now it's just a formal statement.

You are given $ n $ points $ a_1, a_2, \dots, a_n $ on the $ OX $ axis. Now you are asked to find such an integer point $ x $ on $ OX $ axis that $ f_k(x) $ is minimal possible.

The function $ f_k(x) $ can be described in the following way:

- form a list of distances $ d_1, d_2, \dots, d_n $ where $ d_i = |a_i - x| $ (distance between $ a_i $ and $ x $ );
- sort list $ d $ in non-descending order;
- take $ d_{k + 1} $ as a result.

If there are multiple optimal answers you can print any of them.

## 样例 #1

### 输入

```
3
3 2
1 2 5
2 1
1 1000000000
1 0
4
```

### 输出

```
3
500000000
4
```

# AI分析结果



## 算法分类：二分

---

### **题解思路与核心难点**
- **核心问题**：寻找点x，使第k+1小的距离最小。关键性质是该距离对应一段连续区间内的最大距离。
- **最优思路**：线性扫描所有长度为k+1的区间，取其中点。时间复杂度O(n)。
- **二分思路**：二分答案`mid`，检查是否存在区间满足最大距离≤`mid`。通过滑动窗口判断，时间复杂度O(n log V)。

---

### **题解评分（≥4星）**
1. **wanghaoyu120104（5星）**  
   - 思路清晰，直接枚举连续区间，代码简洁高效。  
   - 亮点：线性复杂度，直观易懂。
2. **SamuelXuch（5星）**  
   - 与最优解法一致，代码简洁，无冗余操作。  
   - 亮点：最短区间中点策略，性能优异。
3. **cosf（4星）**  
   - 明确解释连续区间性质，代码与思路匹配。  
   - 亮点：数学推导清晰，避免复杂条件。

---

### **最优思路与技巧提炼**
- **关键技巧**：  
  1. **连续区间性质**：第k+1小的距离对应一个长度为k+1的连续区间。  
  2. **中点策略**：最优x为区间中点，此时最大距离为区间长度的一半。  
  3. **线性扫描优化**：遍历所有可能的左端点，维护最短区间。

---

### **同类型题与算法套路**
- **二分答案通用思路**：  
  1. 确定答案范围，定义`check(mid)`函数。  
  2. 滑动窗口判断是否存在合法区间。  
- **类似题目**：  
  - P1314 聪明的质监员（二分答案+前缀和）  
  - P4343 自动刷题机（二分答案+模拟）  
  - P2218 覆盖问题（二分+贪心）

---

### **代码实现（核心二分逻辑）**
```cpp
// 二分答案实现（Leaper_lyc）
bool check(int mid) {
    int r = 1, len = 0;
    for (int l = 1; l <= n; l++) {
        while (r <= n && a[r] - a[l] <= (mid << 1)) r++;
        len = max(len, r - l);
        if (r - l > k) ans = (a[r - 1] + a[l]) / 2;
    }
    return len > k;
}
```

---

### **可视化与算法演示**
- **动画设计**：  
  1. **Canvas绘制**：数值轴展示当前二分区间`[L, R]`，高亮`mid`。  
  2. **滑动窗口模拟**：动态显示窗口移动，标记合法区间。  
  3. **复古像素风格**：使用8位色块表示数值，收缩区间时播放音效。  
- **交互功能**：  
  - **步进控制**：单步执行二分过程，观察`mid`变化。  
  - **自动模式**：AI自动运行，每步0.5秒，音效提示收缩方向。  

---

### **个人心得摘录**
- **wanghaoyu120104**：  
  > “枚举左端点，x放在区间中点”——直接抓住问题本质，避免复杂推导。  
- **米奇**：  
  > “比赛时想用二分，但谢神点拨后才明白连续区间性质”——强调思维突破的重要性。

---

### **推荐题目**
1. **P1314 聪明的质监员**（二分答案+前缀和）  
2. **P4343 自动刷题机**（二分答案+模拟验证）  
3. **P2218 覆盖问题**（二分答案+几何贪心）

---
处理用时：100.93秒