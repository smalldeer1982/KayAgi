# 题目信息

# ACM ICPC

## 题目描述

In a small but very proud high school it was decided to win ACM ICPC. This goal requires to compose as many teams of three as possible, but since there were only $ 6 $ students who wished to participate, the decision was to build exactly two teams.

After practice competition, participant number $ i $ got a score of $ a_{i} $ . Team score is defined as sum of scores of its participants. High school management is interested if it's possible to build two teams with equal scores. Your task is to answer that question.

## 说明/提示

In the first sample, first team can be composed of $ 1 $ st, $ 2 $ nd and $ 6 $ th participant, second — of $ 3 $ rd, $ 4 $ th and $ 5 $ th: team scores are $ 1+3+1=2+1+2=5 $ .

In the second sample, score of participant number $ 6 $ is too high: his team score will be definitely greater.

## 样例 #1

### 输入

```
1 3 2 1 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1 1 1 1 1 99
```

### 输出

```
NO
```

# AI分析结果



---

### **算法分类**
暴力枚举

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
所有题解的核心逻辑均基于以下步骤：
1. **总和奇偶性判断**：若总和为奇数，直接输出`NO`。
2. **暴力枚举三元组**：若总和为偶数，遍历所有可能的三人组合，检查是否存在和为总和一半的情况。

#### **解决难点**
- **组合去重**：需避免重复计算相同的三元组（如`(a,b,c)`和`(b,a,c)`视为同一组合）。
- **时间复杂度优化**：直接枚举组合而非排列，将复杂度从 `O(n^3)` 优化为 `O(C(6,3))=20`。

#### **题解对比**
| 题解 | 实现方式 | 时间复杂度 | 优化点 | 缺点 |
|------|----------|------------|--------|------|
| hello2020 | 三层循环枚举 `i<j<k` | O(20) | 组合枚举，无重复 | 无 |
| AmaZingFantasy | DFS遍历所有选数可能 | O(2^6)=64 | 递归剪枝 | 递归栈开销 |
| Dog_Two | 全排列后取前三个数 | O(6!)=720 | 代码简洁 | 大量重复计算 |
| chufuzhe | 三重循环检查所有排列 | O(6^3)=216 | 直接暴力 | 重复检查同一组合 |

---

### **题解评分 (≥4星)**

1. **hello2020 (4星)**
   - **亮点**：直接枚举组合，代码简洁高效。
   - **代码片段**：
     ```cpp
     for (int i=1;i<=4;i++)
       for (int j=i+1;j<=5;j++)
         for (int k=j+1;k<=6;k++)
           if (a[i]+a[j]+a[k]==sum/2) return YES;
     ```

2. **AmaZingFantasy (4星)**
   - **亮点**：DFS剪枝，适合通用组合问题。
   - **代码片段**：
     ```cpp
     void dfs(l step, l sum) {
         if (cnt==3 && sum==he/2) { cout<<"YES"; exit(0); }
         // 剪枝：sum超过目标或已选满3人
         cnt++; dfs(step+1, sum+arr[step]); cnt--;
         dfs(step+1, sum);
     }
     ```

3. **jijidawang (4星)**
   - **亮点**：理论分析清晰，指出组合枚举的本质。

---

### **最优思路或技巧提炼**

- **总和奇偶性剪枝**：总和为奇数时直接返回，避免无效计算。
- **组合枚举法**：通过 `i<j<k` 三层循环直接生成所有唯一三元组。
- **DFS剪枝**：通过递归提前终止无效分支，适用于更通用的组合问题。

---

### **同类型题或类似算法套路**
- **子集和问题**：如分割数组为两部分（LeetCode 416）。
- **组合枚举**：如洛谷 P1036（选数问题）。
- **暴力优化**：小数据量下直接暴力，大数据量需动态规划或回溯剪枝。

---

### **推荐相似题目**
1. **洛谷 P1036**：选数，枚举组合求和。
2. **LeetCode 416**：分割等和子集，动态规划或暴力剪枝。
3. **洛谷 P1466**：集合，子集和计数问题。

---

### **可视化与算法演示**

#### **核心算法流程**
1. **输入数据**：展示输入的6个数字及总和计算。
2. **奇偶判断**：高亮总和并判断是否为偶数。
3. **组合遍历**：动态显示当前枚举的 `i,j,k` 索引及对应数值。
4. **结果反馈**：找到匹配时触发动画效果，显示 `YES`。

#### **复古游戏化设计**
- **像素风格**：用16色网格展示数字，当前选中元素用闪烁边框标记。
- **音效设计**：
  - **成功**：8-bit 胜利音效。
  - **失败**：低沉错误音效。
- **自动演示**：按步长自动遍历组合，支持暂停/继续。

#### **交互示例（伪代码）**
```javascript
// Canvas 绘制组合枚举过程
function drawCombination(i, j, k, a) {
    ctx.fillStyle = "#FF0000"; // 高亮当前组合
    ctx.fillRect(i*50, 0, 50, 50); // 绘制i,j,k对应的方块
    // ...类似绘制j和k
}
```

---

### **总结**
通过暴力枚举组合或DFS剪枝，结合总和奇偶性优化，本题可在极低时间复杂度内解决。核心在于组合去重与剪枝策略的合理应用。

---
处理用时：111.66秒