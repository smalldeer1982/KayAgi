# 题目信息

# Lexicographically Largest

## 题目描述

Stack has an array $ a $ of length $ n $ . He also has an empty set $ S $ . Note that $ S $ is not a multiset.

He will do the following three-step operation exactly $ n $ times:

1. Select an index $ i $ such that $ 1 \leq i \leq |a| $ .
2. Insert $ ^\dagger $ $ a_i + i $ into $ S $ .
3. Delete $ a_i $ from $ a $ . Note that the indices of all elements to the right of $ a_i $ will decrease by $ 1 $ .

Note that after $ n $ operations, $ a $ will be empty.

Stack will now construct a new array $ b $ which is $ S $ sorted in decreasing order. Formally, $ b $ is an array of size $ |S| $ where $ b_i $ is the $ i $ -th largest element of $ S $ for all $ 1 \leq i \leq |S| $ .

Find the lexicographically largest $ ^\ddagger $ $ b $ that Stack can make.

 $ ^\dagger $ A set can only contain unique elements. Inserting an element that is already present in a set will not change the elements of the set.

 $ ^\ddagger $ An array $ p $ is lexicographically larger than a sequence $ q $ if and only if one of the following holds:

- $ q $ is a prefix of $ p $ , but $ p \ne q $ ; or
- in the first position where $ p $ and $ q $ differ, the array $ p $ has a larger element than the corresponding element in $ q $ .

Note that $ [3,1,4,1,5] $ is lexicographically larger than $ [3,1,3] $ , $ [\,] $ , and $ [3,1,4,1] $ but not $ [3,1,4,1,5,9] $ , $ [3,1,4,1,5] $ , and $ [4] $ .

## 说明/提示

In the first test case, select $ i=1 $ in the first operation, insert $ a_1 + 1 = 3 $ in $ S $ , and delete $ a_1 $ from $ a $ . After the first operation, $ a $ becomes $ a=[1] $ . In the second operation, we select $ i=1 $ again and insert $ a_1 + 1 = 2 $ in $ S $ . Thus $ S=\{2, 3\} $ , and $ b = [3, 2] $ .

Note that if you select $ i=2 $ in the first operation, and $ i=1 $ in the second operation, $ S=\{3\} $ as $ 3 $ will be inserted twice, resulting in $ b=[3] $ .

As $ [3,2] $ is lexicographically larger than $ [3] $ , we should select $ i=1 $ in the first operation.

In the second test case, in each operation, select the last element.

## 样例 #1

### 输入

```
3
2
2 1
5
1 100 1000 1000000 1000000000
3
6 4 8```

### 输出

```
3 2 
1000000005 1000004 1003 102 2 
11 7 6```

# AI分析结果



### 综合分析与结论

**核心思路**：每个元素贡献的值为 `a_i + 当前索引`，但索引会因删除操作动态变化。需构造字典序最大的降序数组，避免重复。  
**贪心策略**：  
1. 计算所有初始候选值 `c_i = a_i + i`，降序排序。  
2. 对排序后的数组，逐个调整元素，确保每个元素不超过前一个元素减一，从而避免重复并保持字典序最大。  

**正确性证明**：调整后的序列满足以下性质：  
- 每个元素尽可能大。  
- 重复值被转换为递减序列（如 `[3,3] → [3,2]`）。  

**可视化设计**：  
- **动画方案**：初始降序排列的方块，逐步调整重复项为前项减一。  
- **高亮标记**：当前处理的元素用红色标记，调整后的值用绿色闪烁。  
- **复古风格**：8-bit 像素块表示数值，调整时播放经典音效（如《超级玛丽》金币声）。  
- **交互控制**：支持步进/自动播放，展示调整前后的对比。

---

### 题解评分与推荐（≥4星）

1. **JiuZhE66666（5星）**  
   - **亮点**：  
     - 思路简洁，直接降序排序并线性调整。  
     - 时间复杂度 O(n log n)，高效易实现。  
     - 代码仅需两次排序和一次遍历调整。  
   - **代码可读性**：变量命名清晰，逻辑紧凑。

---

### 最优思路提炼

**关键步骤**：  
1. **初始计算**：`c_i = a_i + i`，直接反映每个元素的理论最大值。  
2. **排序策略**：降序排列，确保优先处理大值。  
3. **冲突处理**：若当前值与前值重复或过大，调整为其前值减一。  

**实现核心**：  
```cpp
sort(a + 1, a + 1 + n, greater<int>()); // 降序排序
for (int i = 2; i <= n; i++)
    a[i] = min(a[i], a[i - 1] - 1);    // 调整冲突值
```

---

### 相似题目推荐

1. **CF455A Boredom**（贪心+动态规划）  
2. **LeetCode 321. 拼接最大数**（贪心+单调栈）  
3. **Luogu P1090 合并果子**（贪心+优先队列）

---

### 代码实现

**核心逻辑片段**：  
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[300005];

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] += i; // 计算初始候选值
        }
        sort(a + 1, a + n + 1, greater<int>());
        // 调整重复项
        for (int i = 2; i <= n; i++) 
            a[i] = min(a[i], a[i - 1] - 1);
        // 输出结果
        for (int i = 1; i <= n; i++) 
            cout << a[i] << " \n"[i == n];
    }
    return 0;
}
```

---

### 可视化与游戏化设计

**复古像素动画**：  
1. **初始化**：将排序后的 `c_i` 显示为彩色像素块，高度对应数值。  
2. **调整过程**：  
   - 当前处理块闪烁，与前一块比较。  
   - 若需要调整，播放“下降”动画并更新数值。  
3. **音效设计**：  
   - 调整时触发 8-bit 音效，成功生成数组后播放胜利音乐。  

**交互功能**：  
- **自动模式**：AI 逐步执行，间隔 1 秒/步。  
- **手动控制**：用户点击触发下一步，观察调整逻辑。  

**示例动画帧**：  
```
初始排序：[5,4,4,3]
调整后 → [5,4,3,2]
颜色变化：第二个4→绿色闪烁后变为3，第三个4→红色调整到2。
```

---

**总结**：通过降序排序与线性调整，确保字典序最大且无重复值。复古动画与交互设计可直观展示贪心策略的决策过程。

---
处理用时：70.33秒