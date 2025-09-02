# 题目信息

# Perfect Groups

## 题目描述

SaMer has written the greatest test case of all time for one of his problems. For a given array of integers, the problem asks to find the minimum number of groups the array can be divided into, such that the product of any pair of integers in the same group is a perfect square.

Each integer must be in exactly one group. However, integers in a group do not necessarily have to be contiguous in the array.

SaMer wishes to create more cases from the test case he already has. His test case has an array $ A $ of $ n $ integers, and he needs to find the number of contiguous subarrays of $ A $ that have an answer to the problem equal to $ k $ for each integer $ k $ between $ 1 $ and $ n $ (inclusive).

## 样例 #1

### 输入

```
2
5 5
```

### 输出

```
3 0
```

## 样例 #2

### 输入

```
5
5 -4 2 1 8
```

### 输出

```
5 5 3 2 0
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
1
```

# AI分析结果



---

### 算法分类  
**数学（平方因子处理） + 哈希统计**

---

### 题解思路与算法要点  
1. **核心数学推导**  
   - 两个数乘积为平方数 ⟺ 除去平方因子后的剩余部分相等  
   - 预处理每个数：消去所有平方因子（如 8 → 2，12 → 3）  
   - 0 可与其他任意数同组，需特殊处理  

2. **关键实现步骤**  
   - **预处理**：将每个数除以所有平方因子（如循环试除 1e4 内的平方数）  
   - **分组统计**：枚举每个子数组起点，动态维护当前出现的不同数值，统计组数  
   - **优化技巧**：记录每个数前一个相同值的位置，避免重复遍历  

3. **解决难点**  
   - **平方因子分解**：需处理大数（1e8）的质因数，采用试除法或预处理质数  
   - **时间复杂度**：通过预处理前序位置将复杂度优化至 O(n²)  
   - **0 的特殊处理**：单独维护 0 的存在性，动态调整组数  

---

### 题解评分（≥4星）  
1. **作者：fanypcd（4.5星）**  
   - **亮点**：预处理前序位置实现 O(n²) 统计，代码简洁  
   - **代码片段**：  
     ```cpp  
     for(int i=1; i<=n; ++i) {  
         for(int j=i-1; j>=1; --j) {  
             if (a[i]==a[j]) { pre[i]=j; break; }  
         }  
     }  
     ```  
   - **心得分**：通过预处理前序位置避免重复遍历，显著优化性能  

2. **作者：_Life_（4星）**  
   - **亮点**：并查集合并可同组数，逻辑清晰  
   - **代码片段**：  
     ```cpp  
     for(int i=1; i<=n; ++i) {  
         for(int j=1; j<i; ++j) {  
             if (a[i]*a[j] >0 && sqrt(a[i]*a[j])是整数)  
                 merge(i,j);  
         }  
     }  
     ```  

3. **作者：WZKQWQ（4星）**  
   - **亮点**：直接哈希统计不同值，处理 0 的逻辑简洁  
   - **代码片段**：  
     ```cpp  
     bitset<2*INF+1> s;  
     for(int j=l; j<=r; ++j) {  
         if (a[j]==0) ans[max(tot,1)]++;  
         else if (!s[a[j]]) tot++, s[a[j]]=1;  
     }  
     ```  

---

### 最优技巧提炼  
1. **平方因子预处理**  
   - 对每个数循环除以最大平方因子（如 10000, 9801,...2,1）  
   - 结果存储为无平方因子形式，便于直接比较  

2. **前序位置优化**  
   - 对每个数记录其前一个相同值的位置，避免重复统计  
   - 在枚举子数组时，只需判断前序位置是否在当前起点之后  

3. **动态维护哈希表**  
   - 枚举子数组起点后，增量维护出现的数值  
   - 使用 `bitset` 或 `vis[]` 数组快速判断是否新增组  

---

### 类似题目推荐  
1. [CF1225D - Power Products](https://codeforces.com/problemset/problem/1225/D)  
   - **关键词**：平方因子分解、哈希统计  

2. [LeetCode 1525. Number of Good Ways to Split a String](https://leetcode.com/problems/number-of-good-ways-to-split-a-string/)  
   - **关键词**：子数组特征统计、动态哈希  

3. [Luogu P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147)  
   - **关键词**：枚举子矩阵、动态维护极值  

---

### 可视化设计  
1. **核心动画流程**  
   - **初始网格**：将数组元素显示为像素块，颜色表示其处理后的值（如 0 为黑色，其他值不同颜色）  
   - **枚举子数组**：高亮当前起点和终点，步进式扩展右边界  
   - **组数变化**：当新元素加入时，若值未出现过则播放“新增组”音效，并闪烁该元素  

2. **复古像素风格**  
   - **调色板**：8 位风格（红、绿、蓝、黑、白）  
   - **音效**：  
     - 新增组：短促“哔”声（Web Audio API）  
     - 扫描完成：经典 FC 过关音效  

3. **交互控制**  
   - **自动模式**：按预设速度演示所有子数组的扫描过程  
   - **手动模式**：方向键控制右边界移动，空格暂停  

---

### 代码片段（关键逻辑）  
```cpp  
// 预处理平方因子（作者：WZKQWQ）  
for(int i=1; i<=n; ++i) {  
    for(int j=10000; j>=2; --j)  
        while(abs(a[i]) % (j*j) ==0) a[i] /= j*j;  
}  

// 动态统计组数（作者：fanypcd）  
for(int l=1; l<=n; ++l) {  
    int sum=0, flag=0;  
    for(int r=l; r<=n; ++r) {  
        if(a[r]==0) flag=1;  
        else if(pre[r]<l) sum++;  
        ans[sum - (flag && sum)]++;  
    }  
}  
```

---
处理用时：82.34秒