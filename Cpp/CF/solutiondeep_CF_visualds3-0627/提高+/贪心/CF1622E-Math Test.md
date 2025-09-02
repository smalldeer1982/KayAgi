# 题目信息

# Math Test

## 题目描述

Petya is a math teacher. $ n $ of his students has written a test consisting of $ m $ questions. For each student, it is known which questions he has answered correctly and which he has not.

If the student answers the $ j $ -th question correctly, he gets $ p_j $ points (otherwise, he gets $ 0 $ points). Moreover, the points for the questions are distributed in such a way that the array $ p $ is a permutation of numbers from $ 1 $ to $ m $ .

For the $ i $ -th student, Petya knows that he expects to get $ x_i $ points for the test. Petya wonders how unexpected the results could be. Petya believes that the surprise value of the results for students is equal to $ \sum\limits_{i=1}^{n} |x_i - r_i| $ , where $ r_i $ is the number of points that the $ i $ -th student has got for the test.

Your task is to help Petya find such a permutation $ p $ for which the surprise value of the results is maximum possible. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
4 3
5 1 2 2
110
100
101
100
4 4
6 2 0 10
1001
0010
0110
0101
3 6
20 3 15
010110
000101
111111```

### 输出

```
3 1 2 
2 3 4 1 
3 1 4 5 2 6```

# AI分析结果



---

### **综合分析与结论**

**题目核心**：构造排列 $p$（题目分值），使得所有学生的惊喜值 $\sum |x_i - r_i|$ 最大。  
**关键难点**：绝对值的处理与最大化策略。  
**解法核心**：枚举所有可能的贡献方向（$x_i - r_i$ 或 $r_i - x_i$），利用排序不等式分配分数。

---

### **题解要点与对比**

#### **贪心策略分析**  
1. **贡献方向枚举**：  
   - 每个学生的贡献方向由二进制掩码（mask）确定，共 $2^n$ 种可能。  
   - 对于每个 mask，计算每题的系数 $d_j = \sum c_i \cdot p_{i,j}$，其中 $c_i \in \{-1,1\}$。  
2. **分数分配贪心**：  
   - 按 $d_j$ 从小到大排序，将最小的 $d_j$ 分配最大的分数（$m, m-1, \dots, 1$）。  
   - 正确性依赖排序不等式：逆序乘积和最大。

#### **题解对比**  
| 题解作者     | 亮点                                                                 | 难点处理                               |  
|--------------|----------------------------------------------------------------------|----------------------------------------|  
| I_am_Accepted | 数学推导严谨，证明贡献方向矛盾不影响最优解                          | 处理 $d_j$ 的符号与分数分配的关联性    |  
| Tyyyyyy      | 代码简洁，直接通过排序实现贪心                                      | 高效计算每题的系数，优化循环逻辑       |  
| XL4453       | 结构清晰，独立处理每个状态并保留最优解                              | 验证不同状态下的实际贡献方向是否合法   |  

---

### **题解评分（≥4星）**

1. **Tyyyyyy（★★★★☆）**  
   - **思路清晰度**：代码直击贪心核心，逻辑清晰。  
   - **代码可读性**：简洁的循环与排序实现，易于移植。  
   - **优化程度**：利用预处理和排序不等式，时间复杂度合理。  
   ```cpp
   // 核心代码片段：计算系数并排序
   for(int i=1;i<=m;i++) {
       a[i].id = i;
       a[i].v = 0;
       for(int j=1;j<=n;j++)
           if(s[j][i] == '1') a[i].v += (msk & (1<<(j-1))) ? -1 : 1;
   }
   sort(a+1, a+m+1); // 按系数升序排列
   ```

2. **I_am_Accepted（★★★★☆）**  
   - **思路清晰度**：数学公式推导详尽，证明正确性。  
   - **实践可操作性**：通过状压枚举所有可能性，确保不漏解。  

3. **XL4453（★★★☆☆）**  
   - **代码可读性**：结构明确但变量命名稍显复杂。  
   - **优化程度**：与高分题解思路一致，但实现稍冗长。  

---

### **最优思路提炼**

1. **状态枚举**：  
   - 枚举每个学生的贡献方向（$2^n$ 种），将绝对值转化为线性组合。  
2. **系数计算**：  
   - 对每个题目计算其全局系数 $d_j$，反映该题对总惊喜值的权重。  
3. **贪心排序**：  
   - 将 $d_j$ 最小的题目分配最大的分数，最大化 $\sum d_j \cdot p_j$。  

---

### **同类型题目与算法套路**

- **常见贪心场景**：  
  - 最大加权和（如 [Huffman 编码](https://www.luogu.com.cn/problem/P1090)）。  
  - 任务调度（如 [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)）。  
- **类似题推荐**：  
  1. P1090（合并果子）  
  2. P1572（关路灯）  
  3. P1842 [USACO05NOV] 奶牛玩杂技  

---

### **可视化与算法演示**

#### **复古像素风格动画设计**  
1. **界面设计**：  
   - 8-bit 像素网格，每格代表一题，颜色表示 $d_j$ 大小（红色=小，绿色=大）。  
   - 右侧面板显示当前 mask 的二进制表示和总分。  
2. **动画流程**：  
   - **步骤1**：枚举 mask，高亮当前状态。  
   - **步骤2**：计算每题的 $d_j$，动态更新颜色。  
   - **步骤3**：按 $d_j$ 排序，分配分数（显示分数从 $m$ 到 $1$ 下落动画）。  
   - **步骤4**：计算总分，若破纪录则播放胜利音效。  
3. **音效与交互**：  
   - **点击**：单步执行 mask。  
   - **自动播放**：AI 自动遍历 mask，实时更新最优解。  
   - **音效**：分配分数时触发“得分”音效，破纪录时播放 8-bit 欢呼声。  

#### **核心 JavaScript 片段**  
```javascript
// 模拟排序与分数分配
function simulateGreedy(mask) {
    let d = Array(m).fill(0);
    for (let i = 0; i < n; i++) {
        let sign = (mask & (1 << i)) ? -1 : 1;
        for (let j = 0; j < m; j++) {
            if (s[i][j] === '1') d[j] += sign;
        }
    }
    // 排序并分配分数
    let sorted = d.map((val, idx) => ({val, idx}))
                  .sort((a, b) => a.val - b.val)
                  .map((obj, i) => ({...obj, score: m - i}));
    return sorted;
}
```

---

### **个人心得摘录**

- **I_am_Accepted**：  
  > “枚举所有可能的贡献方向时，即使某些方向与实际结果矛盾，但正确的情况必然存在于某个 mask 中，最终会被保留。”  
- **Tyyyyyy**：  
  > “通过预处理每题的系数，直接利用排序函数简化代码，避免手动实现复杂逻辑。”  

---

### **总结**  
本题通过状态枚举与贪心排序，巧妙地将绝对值最大化问题转化为线性组合优化。核心在于利用排序不等式和二进制掩码的暴力枚举，结合小数据范围特性，实现高效求解。

---
处理用时：82.41秒