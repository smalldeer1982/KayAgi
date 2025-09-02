# 题目信息

# Cinema Cashier

## 题目描述

All cinema halls in Berland are rectangles with $ K $ rows of $ K $ seats each, and $ K $ is an odd number. Rows and seats are numbered from $ 1 $ to $ K $ . For safety reasons people, who come to the box office to buy tickets, are not allowed to choose seats themselves. Formerly the choice was made by a cashier, but now this is the responsibility of a special seating program. It was found out that the large majority of Berland's inhabitants go to the cinema in order to watch a movie, that's why they want to sit as close to the hall center as possible. Moreover, a company of $ M $ people, who come to watch a movie, want necessarily to occupy $ M $ successive seats in one row. Let's formulate the algorithm, according to which the program chooses seats and sells tickets. As the request for $ M $ seats comes, the program should determine the row number $ x $ and the segment $ [y_{l},y_{r}] $ of the seats numbers in this row, where $ y_{r}-y_{l}+1=M $ . From all such possible variants as a final result the program should choose the one with the minimum function value of total seats remoteness from the center. Say, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/c9748a84837b67ee9aa2cbea2b55fdd9ec523940.png) — the row and the seat numbers of the most "central" seat. Then the function value of seats remoteness from the hall center is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/9bc644baca5d1a575e01b85fce16d96f8e180ca4.png). If the amount of minimum function values is more than one, the program should choose the one that is closer to the screen (i.e. the row number $ x $ is lower). If the variants are still multiple, it should choose the one with the minimum $ y_{l} $ . If you did not get yet, your task is to simulate the work of this program.


## 样例 #1

### 输入

```
2 1
1 1
```

### 输出

```
1 1 1
-1
```

## 样例 #2

### 输入

```
4 3
1 2 3 1
```

### 输出

```
2 2 2
1 1 2
3 1 3
2 1 1
```

# AI分析结果



**唯一算法分类**：模拟与贪心

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
1. **问题分析**：电影院座位为K×K的矩阵，每波人需选同一排连续的座位，优先级为总曼哈顿距离最小→行号小→左端点小。
2. **关键难点**：快速判断座位是否可用、高效计算总距离。
3. **算法对比**：
   - **树状数组+数学优化**（题解1）：用树状数组维护每行的座位占用状态，实现O(log K)的区间查询；通过数学公式分情况计算总距离，避免逐个求和。
   - **暴力枚举**（题解2、3、4）：直接检查每个可能的起始位置是否可用，逐个计算距离。虽时间复杂度较高（O(nK³)），但数据范围小（K≤99）仍可接受。

#### **解决难点**
- **快速判断座位可用性**：树状数组将区间查询复杂度从O(M)降为O(log K)。
- **高效距离计算**：通过数学公式将距离求和从O(M)优化为O(1)，分三种情况处理区间位置（全左、全右、跨越中心）。

---

### **题解评分（≥4星）**
1. **题解1（404Not_Found）**：⭐⭐⭐⭐⭐  
   - **亮点**：树状数组优化查询，数学公式优化计算，思路清晰，代码高效。
2. **题解3（一铭君一）**：⭐⭐⭐⭐  
   - **亮点**：暴力枚举但加入跳跃优化，减少无效检查，代码简洁。
3. **题解2（ncwzdlsd）**：⭐⭐⭐⭐  
   - **亮点**：直接暴力实现，代码简单易懂，适合快速编写。

---

### **最优思路与技巧**
- **数据结构优化**：用树状数组维护区间占用状态，快速判断座位是否可用。
- **数学推导**：将曼哈顿距离之和转换为等差数列公式，避免逐项计算。
- **贪心策略**：按优先级（总距离→行号→左端点）遍历所有可能位置。

---

### **同类型题推荐**
1. **P1880 石子合并**（区间DP，贪心选择合并顺序）
2. **P1090 合并果子**（优先队列优化）
3. **P1004 方格取数**（多维DP，路径选择）

---

### **代码核心逻辑**
```cpp
// 树状数组查询区间是否可用
int query(int line, int l, int r) {
    return sum(line, r) - sum(line, l-1);
}

// 计算总曼哈顿距离（分三种情况）
int calculate_cost(int x, int l, int m) {
    int mid = (k+1)/2;
    int cost_x = abs(x - mid) * m;
    if (l >= mid) {
        return cost_x + (l + l+m-1)*m/2 - mid*m;
    } else if (l + m-1 <= mid) {
        return cost_x + mid*m - (l + l+m-1)*m/2;
    } else {
        // 分两段计算
        int left_len = mid - l;
        int right_len = (l + m-1) - mid;
        return cost_x + (mid*(mid+1)/2 - l*(l-1)/2) 
                     + ((mid + mid + right_len)*(right_len+1)/2 - mid*(right_len+1));
    }
}
```

---

### **可视化与算法演示**
1. **动画设计**：
   - **座位网格**：用Canvas绘制K×K网格，标记已占用（红色）和候选区间（绿色）。
   - **当前操作**：高亮正在检查的行和区间，显示总距离计算结果。
   - **最优路径标记**：最终选择的座位显示为蓝色，播放成功音效。
2. **复古风格**：
   - **像素画风**：8-bit风格座位，中心点用黄色标记。
   - **音效**：检查座位时播放“点击”声，成功安排时播放胜利音效。
3. **交互控制**：可调节速度或单步执行，观察枚举和计算过程。

---

### **总结**
树状数组+数学优化是本题最优解，兼顾效率与代码可维护性。暴力方法虽简单，但在数据范围小时仍适用。核心在于快速判断区间可用性和高效计算总距离，结合贪心策略选择最优位置。

---
处理用时：106.54秒