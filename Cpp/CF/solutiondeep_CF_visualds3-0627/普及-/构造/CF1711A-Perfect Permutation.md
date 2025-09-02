# 题目信息

# Perfect Permutation

## 题目描述

You are given a positive integer $ n $ .

The weight of a permutation $ p_1, p_2, \ldots, p_n $ is the number of indices $ 1\le i\le n $ such that $ i $ divides $ p_i $ . Find a permutation $ p_1,p_2,\dots, p_n $ with the minimum possible weight (among all permutations of length $ n $ ).

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the only valid permutation is $ p=[1] $ . Its weight is $ 1 $ .

In the second test case, one possible answer is the permutation $ p=[2,1,4,3] $ . One can check that $ 1 $ divides $ p_1 $ and $ i $ does not divide $ p_i $ for $ i=2,3,4 $ , so the weight of this permutation is $ 1 $ . It is impossible to find a permutation of length $ 4 $ with a strictly smaller weight.

## 样例 #1

### 输入

```
2
1
4```

### 输出

```
1
2 1 4 3```

# AI分析结果



---

**唯一算法分类**：构造

---

### **题解思路与算法分析**

**核心目标**：构造一个排列，使得除位置1外，其余位置i的p_i均不被i整除，从而最小化权重（固定为1）。

**关键思路**：
1. **错位构造**：利用相邻数互质的性质，将排列构造为每个元素的值为前一个位置的值（如p_i = i+1，末尾置1），或整体右移（p_1 =n，其余依次为1,2,…,n-1）。
2. **互质性质**：i与i±1互质，确保i无法整除i±1，从而避免贡献权重。

**解决难点**：确保构造的排列满足所有i≥2时i∤p_i。通过错位排列或整体位移，保证每个元素与下标互质。

---

### **题解评分（≥4星）**

1. **封禁用户（5星）**  
   - **亮点**：代码极简，直接输出n后接1~n-1，时间复杂度O(n)，逻辑清晰。
   - **代码**：输出n后依次输出1~n-1，保证除i=1外均不贡献权重。

2. **shenyiran（4星）**  
   - **亮点**：将i≥2的p_i设为i+1，最后置1，利用相邻互质性质。
   - **代码**：依次输出i+1，最后补1，逻辑简洁。

3. **sw2022（4星）**  
   - **亮点**：错位法输出n后接1~n-1，直接利用右移构造互质序列。

---

### **最优思路提炼**

1. **错位构造法**：将排列整体右移一位，p_1 =n，p_i =i-1（i≥2）。  
   - **关键点**：i与i-1互质，确保i∤(i-1)。
2. **循环位移法**：将每个p_i设为i+1（i<n），p_n=1。  
   - **关键点**：i与i+1互质，末尾处理避免循环冲突。

---

### **同类型题推荐**

1. **P5436 【XR-2】缘分**：最大化相邻数乘积，利用互质性质。
2. **P1146 硬币翻转**：构造特定排列满足条件。
3. **P7914 [CSP-S 2021] 括号序列**：构造合法括号序列。

---

### **代码实现（核心逻辑）**

**封禁用户的代码片段**：
```cpp
cout << n << " ";
for (int i=1; i<=n-1; i++) {
    cout << i << " ";
}
```
**核心思想**：将排列构造为[n,1,2,…,n-1]，确保每个i≥2的p_i=i-1，与i互质。

---

### **可视化算法设计**

**动画方案**：
1. **网格展示**：在Canvas中绘制n个格子，初始填充1~n。
2. **错位操作**：高亮首元素并置为n，其余元素依次左移一位。
3. **颜色标记**：
   - 红色：当前操作的格子（如首元素）。
   - 绿色：已处理且满足i∤p_i的格子。
4. **步进控制**：单步执行构造过程，展示每个位置的赋值逻辑。

**复古像素风格**：
- **8位调色板**：使用16色像素风格，格子用不同颜色区分操作步骤。
- **音效设计**：移动时播放“滴”声，完成时播放胜利音效。

---

### **个人心得摘录**

- **封禁用户**提到换行符易错，需注意输出格式细节。
- **Scorilon**的判重数组虽正确但冗余，直接构造即可避免复杂逻辑。

---

**总结**：通过巧妙利用相邻数互质性质，构造错位排列可高效解决此问题，代码简洁且时间复杂度最优。

---
处理用时：118.65秒