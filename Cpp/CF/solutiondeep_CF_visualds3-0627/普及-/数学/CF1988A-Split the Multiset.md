# 题目信息

# Split the Multiset

## 题目描述

A multiset is a set of numbers in which there can be equal elements, and the order of the numbers does not matter. For example, $ \{2,2,4\} $ is a multiset.

You have a multiset $ S $ . Initially, the multiset contains only one positive integer $ n $ . That is, $ S=\{n\} $ . Additionally, there is a given positive integer $ k $ .

In one operation, you can select any positive integer $ u $ in $ S $ and remove one copy of $ u $ from $ S $ . Then, insert no more than $ k $ positive integers into $ S $ so that the sum of all inserted integers is equal to $ u $ .

Find the minimum number of operations to make $ S $ contain $ n $ ones.

## 说明/提示

For the first test case, initially $ S=\{1\} $ , already satisfying the requirement. Therefore, we need zero operations.

For the second test case, initially $ S=\{5\} $ . We can apply the following operations:

- Select $ u=5 $ , remove $ u $ from $ S $ , and insert $ 2,3 $ into $ S $ . Now, $ S=\{2,3\} $ .
- Select $ u=2 $ , remove $ u $ from $ S $ , and insert $ 1,1 $ into $ S $ . Now, $ S=\{1,1,3\} $ .
- Select $ u=3 $ , remove $ u $ from $ S $ , and insert $ 1,2 $ into $ S $ . Now, $ S=\{1,1,1,2\} $ .
- Select $ u=2 $ , remove $ u $ from $ S $ , and insert $ 1,1 $ into $ S $ . Now, $ S=\{1,1,1,1,1\} $ .

Using $ 4 $ operations in total, we achieve the goal.

For the third test case, initially $ S=\{6\} $ . We can apply the following operations:

- Select $ u=6 $ , remove $ u $ from $ S $ , and insert $ 1,2,3 $ into $ S $ . Now, $ S=\{1,2,3\} $ .
- Select $ u=2 $ , remove $ u $ from $ S $ , and insert $ 1,1 $ into $ S $ . Now, $ S=\{1,1,1,3\} $ .
- Select $ u=3 $ , remove $ u $ from $ S $ , and insert $ 1,1,1 $ into $ S $ . Now, $ S=\{1,1,1,1,1,1\} $ .

Using $ 3 $ operations in total, we achieve the goal.

For the fourth test case, initially $ S=\{16\} $ . We can apply the following operations:

- Select $ u=16 $ , remove $ u $ from $ S $ , and insert $ 4,4,4,4 $ into $ S $ . Now, $ S=\{4,4,4,4\} $ .
- Repeat for $ 4 $ times: select $ u=4 $ , remove $ u $ from $ S $ , and insert $ 1,1,1,1 $ into $ S $ .

Using $ 5 $ operations in total, we achieve the goal.

## 样例 #1

### 输入

```
4
1 5
5 2
6 3
16 4```

### 输出

```
0
4
3
5```

# AI分析结果



## 唯一算法分类  
**数论**

---

## 综合分析与结论  
本题核心在于发现关键数学规律：每次操作最多产生 k-1 个新元素，总操作次数等于将初始 1 个元素扩展为 n 个 1 所需的最小操作次数。通过数论中的整数除法取整技巧，推导出公式：`ceil((n-1)/(k-1))`。

### 关键公式推导  
1. **目标转换**：初始 1 个元素，最终需要变为 n 个 1，需生成 n-1 个新元素。  
2. **操作效率**：每次操作最多生成 k-1 个新元素（分解一个元素为最多 k 个元素，净增 k-1 个）。  
3. **最小次数**：总操作次数为 `ceil((n-1)/(k-1))`，利用整数除法实现向上取整。

### 可视化设计思路  
1. **动画演示**：以像素风格展示元素分解过程，每次操作高亮当前分解元素，生成新元素时触发音效。  
2. **颜色标记**：当前操作元素用红色高亮，生成的新元素渐变为绿色。  
3. **步进控制**：允许单步执行观察每次分解后的集合变化，自动模式按公式步数推进。

---

## 题解清单 (≥4星)  
无具体题解，但最优思路已提炼为数学公式，直接实现即可。

---

## 代码实现  
```cpp
#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long n, k;
        cin >> n >> k;
        if (n == 1) {
            cout << 0 << endl;
            continue;
        }
        if (k == 1) {
            cout << (n == 1 ? 0 : -1) << endl; // k=1时无法分解
            continue;
        }
        long long ans = (n - 1 + k - 2) / (k - 1);
        cout << ans << endl;
    }
    return 0;
}
```

### 核心逻辑  
- **公式计算**：`(n-1 + k-2) // (k-1)` 实现向上取整除法。  
- **边界处理**：当 n=1 时直接返回 0，k=1 时无解（除非 n=1）。

---

## 同类型题与算法套路  
**常见数论优化**：  
- 分解问题转化为整数除法与取模运算。  
- 利用向上取整公式快速计算最小操作次数。

---

## 推荐类似题目  
1. **洛谷 P1226** 【快速幂】：利用分治思想进行快速幂计算。  
2. **洛谷 P1469** 【找筷子】：利用异或性质解决配对问题。  
3. **洛谷 P1102** 【A-B数对】：通过哈希表优化统计效率。

---

## 可视化与游戏化设计  
1. **像素风格**：使用 8-bit 像素元素表示数值，分解时以爆炸动画过渡。  
2. **音效触发**：分解操作播放“哔”声，完成时播放胜利音效。  
3. **自动演示**：按公式计算结果自动播放分解步骤，展示数学推导的正确性。  
4. **关卡模式**：将不同测试用例设为关卡，完成解锁更复杂案例。

---

**总结**：本题通过数论公式直接求解，关键在发现操作次数与元素增长的数学关系，避免复杂递归或贪心策略。

---
处理用时：394.88秒