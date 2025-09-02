# 题目信息

# Mahmoud and Ehab and another array construction task

## 题目描述

Mahmoud has an array $ a $ consisting of $ n $ integers. He asked Ehab to find another array $ b $ of the same length such that:

- $ b $ is lexicographically greater than or equal to $ a $ .
- $ b_{i}>=2 $ .
- $ b $ is pairwise coprime: for every $ 1<=i<j<=n $ , $ b_{i} $ and $ b_{j} $ are coprime, i. e. $ GCD(b_{i},b_{j})=1 $ , where $ GCD(w,z) $ is the greatest common divisor of $ w $ and $ z $ .

Ehab wants to choose a special array so he wants the lexicographically minimal array between all the variants. Can you find it?

An array $ x $ is lexicographically greater than an array $ y $ if there exists an index $ i $ such than $ x_{i}>y_{i} $ and $ x_{j}=y_{j} $ for all $ 1<=j<i $ . An array $ x $ is equal to an array $ y $ if $ x_{i}=y_{i} $ for all $ 1<=i<=n $ .

## 说明/提示

Note that in the second sample, the array is already pairwise coprime so we printed it.

## 样例 #1

### 输入

```
5
2 3 5 4 13
```

### 输出

```
2 3 5 7 11 ```

## 样例 #2

### 输入

```
3
10 3 7
```

### 输出

```
10 3 7 ```

# AI分析结果



**唯一算法分类**: 贪心 + 数学（质因数分解）

---

### **综合分析与结论**

**核心思路**：  
题目要求构造字典序最小且两两互质的数组b。关键策略是尽可能保留原数组a的前缀，直到遇到无法满足互质条件的位置。此时，找到第一个满足条件的最小值，后续位置填充未使用过的最小质数，确保字典序最小。

**难点与解决**：  
1. **贪心保留前缀**：需快速检测当前数是否与之前所有数的质因子冲突。  
2. **快速质因数分解**：预处理质数表，分解质因数并标记已用质数。  
3. **动态维护可用数**：通过筛法或集合动态删除不可用数，保证后续选数高效。  

**可视化设计**：  
- **动画演示**：  
  1. 展示数组a的每个元素逐步被处理，高亮当前处理位置。  
  2. 分解质因数时，标记已用质数（红色），并删除其倍数（灰色）。  
  3. 后续位置显示可用质数池（绿色），动态选取最小值。  
- **复古像素风格**：用8位网格展示数组，当前操作元素闪烁，删除的倍数渐隐，音效提示成功/冲突。  

---

### **题解清单 (≥4星)**

1. **mulberror (4.5星)**  
   - **亮点**：使用`set`动态维护可用数，通过删除质因数倍数保证互质，代码简洁高效。  
   - **核心代码**：  
     ```cpp
     set<int> s; // 维护可用数
     void del(int x) {
         for (int i = 2; i * i <= x; i++) {
             if (x % i == 0) {
                 for (int j = i; j < N; j += i) s.erase(j);
                 while (x % i == 0) x /= i;
             }
         }
         if (x > 1) for (int j = x; j < N; j += x) s.erase(j);
     }
     ```

2. **wangbinfeng (4星)**  
   - **亮点**：分阶段处理，先保留前缀，后填充质数，思路清晰。  
   - **核心代码**：  
     ```cpp
     for (int i = 1; i <= n; i++) {
         if (flag) { // 后续填充最小质数
             while (use[pri[j]]) j++;
             b[i] = pri[j];
         } else {
             int k = a[i];
             while (!check(k)) k++; // 暴力找满足条件的数
         }
     }
     ```

3. **zhaotiensn (4星)**  
   - **亮点**：分情况讨论，暴力检查冲突，代码可读性强。  
   - **核心代码**：  
     ```cpp
     bool check(int x) { // 检查是否与已用质数冲突
         vector<int> factors = decompose(x);
         for (int p : factors) if (used[p]) return false;
         return true;
     }
     ```

---

### **最优思路或技巧提炼**

1. **动态维护可用数池**：通过集合或筛法实时删除不可用数，保证后续选数时间复杂度。  
2. **质因数分解优化**：预处理最小质因子，快速分解并标记冲突。  
3. **贪心填充质数**：一旦确定某位置需修改，后续直接填充最小质数，保证字典序最小。  

---

### **同类型题或类似算法套路**

- **构造型贪心题**：如CF862B（构造二分图）、CF1154E（交替选最大数）。  
- **质因数分解应用**：如CF1047C（统计最大公约数）、ABC177E（判断数组互质）。  

---

### **推荐相似题目**

1. **CF862B**：构造二分图边最大化。  
2. **CF1047C**：通过质因数分解求最大可能GCD。  
3. **ABC177E**：判断数组是否两两互质。  

---

### **个人心得摘录**

- **mulberror**：利用`set`的`lower_bound`和动态删除，简化了可用数的维护。  
- **zhaotiensn**：暴力检查时需注意质因数分解的完整性，避免漏判。  

---

### **可视化与算法演示**

**动画方案**：  
1. **初始化**：展示原数组a，高亮当前位置i=1。  
2. **检查冲突**：分解a[i]质因数，若存在已用质数（红色），将a[i]标记为冲突，逐步增加k直到找到合法值。  
3. **更新可用数池**：分解k的质因数，删除其所有倍数（灰色渐隐）。  
4. **填充后续位置**：从可用质数池（绿色）中选取最小值，动态更新。  

**复古像素效果**：  
- **颜色方案**：红色（冲突质数）、绿色（可用质数）、黄色（当前处理位置）。  
- **音效**：成功选中（8-bit上升音调），冲突（短促低音）。  

---

### **核心代码实现**

```cpp
// mulberror的题解核心代码（简化）
#include <set>
#include <cstdio>
using namespace std;

const int N = 2e6 + 5;
set<int> s;

void del(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            for (int j = i; j < N; j += i) s.erase(j);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) for (int j = x; j < N; j += x) s.erase(j);
}

int main() {
    int n, a[N], b[N]; bool flag = false;
    for (int i = 2; i < N; i++) s.insert(i);
    for (int i = 0; i < n; i++) {
        auto it = flag ? s.begin() : s.lower_bound(a[i]);
        if (*it > a[i]) flag = true;
        b[i] = *it; del(*it);
    }
}
```

---
处理用时：115.87秒