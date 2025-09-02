# 题目信息

# Zero-Sum Prefixes

## 题目描述

The score of an array $ v_1,v_2,\ldots,v_n $ is defined as the number of indices $ i $ ( $ 1 \le i \le n $ ) such that $ v_1+v_2+\ldots+v_i = 0 $ .

You are given an array $ a_1,a_2,\ldots,a_n $ of length $ n $ . You can perform the following operation multiple times:

- select an index $ i $ ( $ 1 \le i \le n $ ) such that $ a_i=0 $ ;
- then replace $ a_i $ by an arbitrary integer.

What is the maximum possible score of $ a $ that can be obtained by performing a sequence of such operations?

## 说明/提示

In the first test case, it is optimal to change the value of $ a_2 $ to $ -2 $ in one operation.

The resulting array $ a $ will be $ [2,-2,1,-1,0] $ , with a score of $ 3 $ :

- $ a_1+a_2=2-2=0 $ ;
- $ a_1+a_2+a_3+a_4=2-2+1-1=0 $ ;
- $ a_1+a_2+a_3+a_4+a_5=2-2+1-1+0=0 $ .

In the second test case, it is optimal to change the value of $ a_3 $ to $ -2\,000\,000\,000 $ , giving us an array with a score of $ 1 $ .

In the third test case, it is not necessary to perform any operations.

## 样例 #1

### 输入

```
5
5
2 0 1 -1 0
3
1000000000 1000000000 0
4
0 0 0 0
8
3 0 2 -10 10 -30 30 0
9
1 0 0 1 -1 0 1 0 -1```

### 输出

```
3
1
4
4
5```

# AI分析结果



**唯一算法分类**  
贪心、前缀和与哈希表

---

### **题解思路、算法要点与解决难点**  
**核心思路**：将数组按零的位置分段，每段内统计前缀和众数，通过修改当前段的零值使众数变为零，从而最大化该段贡献。  
**关键步骤**：  
1. **分段处理**：将数组按零的位置划分为多个区间。  
2. **前缀和统计**：对每个区间内的前缀和，用哈希表统计出现次数。  
3. **众数选择**：选择出现次数最多的前缀和作为修改目标，贡献次数。  
4. **边界处理**：单独处理第一个零之前的前缀和为零的项。  

**解决难点**：  
- 如何高效处理多个零的分段，避免重复统计。  
- 正确统计每个区间的前缀和众数，需使用哈希表（`map`或`unordered_map`）。  
- 处理第一个零前的原始前缀和为零的情况。  

---

### **题解评分 (≥4星)**  
1. **Hovery的题解 (4星)**  
   - **亮点**：分段思路清晰，代码结构明确，预处理零位置。  
   - **代码**：预处理零的位置，逐个区间处理。  

2. **Nuclear_Fish_cyq的题解 (4星)**  
   - **亮点**：反向遍历动态统计，代码简洁高效。  
   - **代码**：从后往前遍历，遇到零时统计当前众数。  

3. **XL4453的题解 (4星)**  
   - **亮点**：极简代码实现，反向遍历与动态分段结合。  
   - **代码**：利用`map`统计，时间复杂度最优。  

---

### **最优思路或技巧提炼**  
1. **分段贪心**：每个零影响其到下一个零的区间，独立处理每段。  
2. **前缀和众数**：哈希表统计区间内的前缀和出现次数，选众数最大化贡献。  
3. **反向遍历优化**：从后往前遍历可动态处理区间，避免预处理零位置。  

---

### **同类型题或类似算法套路**  
- **类似题目**：前缀和+哈希表统计频率的题目，如求子数组和为k的个数（LeetCode 560）。  
- **通用套路**：将数组分段处理，利用哈希表快速统计区间特征。  

---

### **推荐相似题目**  
1. **洛谷 P1114** - 频繁子数组和统计。  
2. **LeetCode 560** - 和为k的子数组数目。  
3. **Codeforces 1398C** - 前缀和转换与计数。  

---

### **个人心得摘录**  
- **调试经验**：需注意前缀和可能溢出，需用`long long`存储。  
- **踩坑教训**：第一个零前的原始前缀和需单独统计，易遗漏。  

---

### **可视化与算法演示**  
**动画方案**：  
1. **分步展示**：  
   - **颜色标记**：用不同颜色标记每个零的区间。  
   - **前缀和高亮**：在区间内显示前缀和数值，统计时动态更新哈希表。  
   - **众数突出**：在统计完成后，高亮众数并显示贡献次数。  

2. **复古像素风格**：  
   - **Canvas 绘制**：用8位像素风格显示数组元素，零位置用闪烁方块标记。  
   - **音效提示**：统计众数时播放“收集金币”音效，贡献增加时播放上扬音调。  

3. **交互设计**：  
   - **步进控制**：允许单步执行观察每个区间的处理。  
   - **自动模式**：AI自动运行，模拟贪心选择过程。  

**代码片段 (JavaScript)**：  
```javascript
// 示例：Canvas绘制分段区间
function drawSegment(start, end, color) {
    ctx.fillStyle = color;
    for (let i = start; i <= end; i++) {
        ctx.fillRect(i * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE);
    }
}
```

---

### **代码实现 (Hovery版关键逻辑)**  
```cpp
vector<int> zeros; // 存储所有零的位置
for (int i = 1; i <= n; i++) {
    if (a[i] == 0) zeros.push_back(i);
}
zeros.push_back(n + 1); // 哨兵处理末尾

// 处理第一个零前的贡献
int ans = 0;
for (int i = 1; i < zeros[0]; i++) {
    if (prefix_sum[i] == 0) ans++;
}

// 处理每个零区间
for (int i = 0; i < zeros.size() - 1; i++) {
    int start = zeros[i], end = zeros[i + 1];
    map<int, int> freq;
    int max_count = 0;
    for (int j = start; j < end; j++) {
        freq[prefix_sum[j]]++;
        max_count = max(max_count, freq[prefix_sum[j]]);
    }
    ans += max_count;
}
```

---
处理用时：89.88秒