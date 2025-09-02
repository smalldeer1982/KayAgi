# 题目信息

# The Phone Number

## 题目描述

Mrs. Smith is trying to contact her husband, John Smith, but she forgot the secret phone number!

The only thing Mrs. Smith remembered was that any permutation of $ n $ can be a secret phone number. Only those permutations that minimize secret value might be the phone of her husband.

The sequence of $ n $ integers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once.

The secret value of a phone number is defined as the sum of the length of the longest increasing subsequence (LIS) and length of the longest decreasing subsequence (LDS).

A subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ where $ 1\leq i_1 < i_2 < \ldots < i_k\leq n $ is called increasing if $ a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k} $ . If $ a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k} $ , a subsequence is called decreasing. An increasing/decreasing subsequence is called longest if it has maximum length among all increasing/decreasing subsequences.

For example, if there is a permutation $ [6, 4, 1, 7, 2, 3, 5] $ , LIS of this permutation will be $ [1, 2, 3, 5] $ , so the length of LIS is equal to $ 4 $ . LDS can be $ [6, 4, 1] $ , $ [6, 4, 2] $ , or $ [6, 4, 3] $ , so the length of LDS is $ 3 $ .

Note, the lengths of LIS and LDS can be different.

So please help Mrs. Smith to find a permutation that gives a minimum sum of lengths of LIS and LDS.

## 说明/提示

In the first sample, you can build a permutation $ [3, 4, 1, 2] $ . LIS is $ [3, 4] $ (or $ [1, 2] $ ), so the length of LIS is equal to $ 2 $ . LDS can be ony of $ [3, 1] $ , $ [4, 2] $ , $ [3, 2] $ , or $ [4, 1] $ . The length of LDS is also equal to $ 2 $ . The sum is equal to $ 4 $ . Note that $ [3, 4, 1, 2] $ is not the only permutation that is valid.

In the second sample, you can build a permutation $ [2, 1] $ . LIS is $ [1] $ (or $ [2] $ ), so the length of LIS is equal to $ 1 $ . LDS is $ [2, 1] $ , so the length of LDS is equal to $ 2 $ . The sum is equal to $ 3 $ . Note that permutation $ [1, 2] $ is also valid.

## 样例 #1

### 输入

```
4
```

### 输出

```
3 4 1 2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
2 1
```

# AI分析结果



**唯一算法分类**  
组合数学  

---

**题解思路、算法要点与解决难点**  
- **核心思路**：分块构造排列，块内递增，块间递减。利用均值不等式确定最优块大小k=√n，使LIS（块长k）与LDS（块数⌈n/k⌉）之和最小。  
- **数学推导**：设块长为k，总块数为⌈n/k⌉，目标为最小化k+⌈n/k⌉。由均值不等式，k+n/k≥2√n，当k≈√n时取得极小值。  
- **构造方法**：从后往前生成每个块，块内元素递增，块间整体递减。例如n=9，k=3，构造为[7,8,9][4,5,6][1,2,3]，LIS=3，LDS=3，总和6。  

---

**题解评分 (≥4星)**  
1. **FxorG（★★★★☆）**  
   - 思路清晰，直接应用分块策略。  
   - 代码简洁，但未处理n非平方数时的边界条件。  

2. **皎月半洒花（★★★★☆）**  
   - 结合Dilworth定理深入分析，代码实现严谨。  
   - 使用`std::reverse`确保块内递增，增强可读性。  

3. **agicy（★★★★☆）**  
   - 通过大量数据验证分块规律，提供直观构造示例。  
   - 代码逻辑清晰，但变量命名可优化。  

---

**最优思路或技巧提炼**  
- **分块构造法**：将排列划分为大小≈√n的块，块内升序保证LIS=块长，块间降序保证LDS=块数。  
- **数学优化**：利用k+⌈n/k⌉的最小化条件，快速确定块长。  
- **代码实现**：逆序生成块，确保块间降序排列。  

---

**同类型题或类似算法套路**  
- **分块优化**：常见于平衡时间复杂度的问题，如区间查询、莫队算法。  
- **均值不等式应用**：在需要平衡两个变量的场景（如CF1088D - Minimum Diameter Tree）。  

---

**推荐相似题目**  
1. P1020 [NOIP1999 提高组] 导弹拦截（Dilworth定理应用）  
2. CF1294E（分块构造与贪心）  
3. CF1165E（排列构造与最优化）  

---

**可视化与算法演示**  
1. **动画方案**：  
   - 初始状态：网格显示1~n的原始序列。  
   - **分块过程**：高亮当前块（红色），从右向左生成块元素（绿色箭头表示填充方向）。  
   - **步进控制**：单步展示每个块的生成，实时显示当前LIS/LDS值。  
   - **颜色标记**：块内元素用渐变色（绿→黄），块间用对比色分隔。  

2. **复古像素风格**：  
   - **8位像素UI**：块用16x16像素方块表示，背景音乐为8-bit风格。  
   - **音效触发**：生成块时播放“哔”声，完成构造时播放胜利音效。  
   - **Canvas绘制**：动态绘制块划分与元素填充过程。  

---

**代码实现（核心分块逻辑）**  
```cpp
#include <cmath>
#include <vector>
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int k = sqrt(n);
    std::vector<int> ans;
    while (n > 0) {
        for (int i = std::max(1, n - k + 1); i <= n; ++i)
            ans.push_back(i);
        n -= k;
    }
    for (auto it = ans.rbegin(); it != ans.rend(); ++it)
        std::cout << *it << ' ';
}
```  
- **核心思想**：逆序生成每个块并反向输出，确保块间降序。  

---

**个人心得摘录**  
- **调试教训**：需注意n非平方数时最后一块的长度，避免负数索引。  
- **顿悟时刻**：发现块间降序时LDS即为块数，极大简化问题。

---
处理用时：89.05秒