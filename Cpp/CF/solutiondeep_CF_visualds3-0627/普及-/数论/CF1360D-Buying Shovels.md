# 题目信息

# Buying Shovels

## 题目描述

Polycarp wants to buy exactly $ n $ shovels. The shop sells packages with shovels. The store has $ k $ types of packages: the package of the $ i $ -th type consists of exactly $ i $ shovels ( $ 1 \le i \le k $ ). The store has an infinite number of packages of each type.

Polycarp wants to choose one type of packages and then buy several (one or more) packages of this type. What is the smallest number of packages Polycarp will have to buy to get exactly $ n $ shovels?

For example, if $ n=8 $ and $ k=7 $ , then Polycarp will buy $ 2 $ packages of $ 4 $ shovels.

Help Polycarp find the minimum number of packages that he needs to buy, given that he:

- will buy exactly $ n $ shovels in total;
- the sizes of all packages he will buy are all the same and the number of shovels in each package is an integer from $ 1 $ to $ k $ , inclusive.

## 说明/提示

The answer to the first test case was explained in the statement.

In the second test case, there is only one way to buy $ 8 $ shovels — $ 8 $ packages of one shovel.

In the third test case, you need to buy a $ 1 $ package of $ 6 $ shovels.

## 样例 #1

### 输入

```
5
8 7
8 1
6 10
999999733 999999732
999999733 999999733```

### 输出

```
2
8
1
999999733
1```

# AI分析结果



**唯一算法分类**：数论（因数分解）

---

### **题解思路与难点对比**

1. **核心思路**  
   所有题解均基于以下观察：购买次数的最小值等于 `n` 除以 `n` 在 `[1, k]` 范围内的最大因数。问题转化为高效寻找该最大因数。

2. **实现方法对比**  
   - **直接因数遍历**：遍历 `1` 到 `sqrt(n)`，检查每个 `i` 是否为 `n` 的因数。若 `i` 或 `n/i` ≤ `k`，则更新最小次数。时间复杂度为 `O(√n)`，空间复杂度 `O(1)`。（如丧黑福造、jasonshen_ 的题解）
   - **存储因数后排序**：先收集所有因数，排序后二分查找最大合法值。时间复杂度仍为 `O(√n)`，但需额外 `O(d)` 空间（`d` 为因数数）和排序开销。（如 Warriors_Cat 的题解）

3. **难点与优化**  
   - **循环条件**：使用 `i*i <= n` 而非 `i <= sqrt(n)` 避免浮点误差。
   - **边界处理**：提前处理 `k >= n` 的情况，直接返回 `1`。
   - **成对因数处理**：在遍历时同时检查 `i` 和 `n/i`，无需存储所有因数。

---

### **题解评分（≥4星）**

1. **丧黑福造（5星）**  
   - **亮点**：代码简洁高效，直接遍历因数并更新结果，无冗余操作。
   - **代码片段**：
     ```cpp
     for (int i = 1; i * i <= n; i++) {
         if (n % i == 0) {
             if (i <= k) ans = min(ans, n/i);
             if (n/i <= k) ans = min(ans, i);
         }
     }
     ```

2. **jasonshen_（4星）**  
   - **亮点**：通过三目运算符简化条件判断，逻辑清晰。
   - **关键优化**：遍历时限制 `i <= k`，减少无效检查。

3. **rui_er（4星）**  
   - **亮点**：倒序遍历因数，优先处理大因数，可能提前终止循环。
   - **代码片段**：
     ```cpp
     for (int i = sqrt(n); i >= 1; i--) {
         if (n % i != 0) continue;
         if (i <= k) ma = max(ma, i);
         if (n/i <= k) ma = max(ma, n/i);
     }
     ```

---

### **最优思路提炼**

- **关键步骤**：
  1. 遍历 `1` 到 `√n`，检查每个 `i` 是否为因数。
  2. 若 `i <= k`，则候选次数为 `n/i`。
  3. 若 `n/i <= k`，则候选次数为 `i`。
  4. 取所有候选次数的最小值。

- **技巧**：利用因数成对特性，同时处理 `i` 和 `n/i`，避免存储所有因数。

---

### **同类题目推荐**

1. **P1075 [NOIP2012 普及组] 质因数分解**  
   - **相似点**：寻找 `n` 的最大质因数。

2. **P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题**  
   - **相似点**：基于因数分解的条件判断。

3. **P1414 又是毕业季II**  
   - **相似点**：处理多数的因数交集与极值问题。

---

### **可视化算法演示**

1. **动画设计**：
   - **像素网格**：显示 `n` 的因数对 `(i, n/i)`，高亮当前检查的 `i`。
   - **状态面板**：展示当前最大合法因数和最小次数。
   - **步进控制**：允许单步执行观察每个 `i` 的判断过程。

2. **复古特效**：
   - **音效**：发现因数时播放 `8-bit` 音效，找到更优解时触发胜利音效。
   - **像素风格**：用 `16色` 调色板渲染因数网格，绿色表示合法因数。

---

### **核心代码实现**

```cpp
#include <stdio.h>
#include <math.h>
inline int min(int x, int y) { return x < y ? x : y; }

int main() {
    int t, n, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        int ans = n;
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                if (i <= k) ans = min(ans, n / i);
                if (n / i <= k) ans = min(ans, i);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

### **个人心得摘录**

- **浮点陷阱**：使用 `i*i <= n` 而非 `i <= sqrt(n)` 避免精度问题。
- **优化思维**：遍历时同时处理成对因数，无需存储全部结果。

---
处理用时：185.58秒