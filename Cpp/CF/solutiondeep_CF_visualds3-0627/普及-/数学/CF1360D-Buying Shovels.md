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



# 数学分类选择
**数论**

---

# 题解思路、算法要点与解决难点

## 核心思路
题目要求找到最大的因数 `d ≤ k`，使得 `n/d` 最小。通过遍历 `1 ≤ i ≤ √n`，同时检查 `i` 和 `n/i` 是否 ≤k，记录最小的 `n/d`。

## 关键数学推导
- 因数成对特性：若 `i` 是 `n` 的因数，则 `n/i` 也是因数。
- 只需遍历到 `√n`，时间复杂度优化为 `O(√n)`。

## 解决难点
- 边界条件处理：当 `k ≥ n` 时直接返回 1。
- 同步检查因数对 `i` 和 `n/i`，避免重复计算。

---

# 题解评分（≥4星）

1. **丧黑福造（5星）**  
   - 思路清晰，直接遍历因数对并维护最小值。  
   - 代码简洁，无冗余操作。  
   - 时间复杂度最优，适用于大范围数据。  

2. **jasonshen_（4星）**  
   - 明确分析时间复杂度与数据规模的关系。  
   - 代码结构清晰，包含详细注释。  

3. **Pink_Cut_Tree（4星）**  
   - 代码简洁，包含输入优化（关闭同步）。  
   - 直观展示因数遍历与条件判断。  

---

# 最优思路或技巧提炼

1. **因数对遍历**  
   遍历 `i` 到 `√n`，每次检查 `i` 和 `n/i` 是否合法，避免重复计算。

2. **实时更新最小值**  
   在遍历过程中直接维护最小包裹数，减少后续比较操作。

3. **边界处理优化**  
   当 `k ≥ n` 时直接返回 1，无需进入循环。

---

# 同类型题或算法套路

- **常见数论问题**  
  最大/最小因数、质因数分解、因数性质分析。
  
- **通用解法套路**  
  1. 遍历到 `√n` 枚举因数对。  
  2. 利用排序或二分法快速查找合法因数。  

---

# 推荐洛谷题目

1. **P1075 质因数分解**  
   （分解质因数，找最大质因数）

2. **P1029 最大公约数和最小公倍数问题**  
   （因数与公倍数性质分析）

3. **P1463 反素数**  
   （寻找因数数目最多的数）

---

# 可视化与算法演示

## 动画设计
- **网格展示**：将 `n` 的因数对 `(i, n/i)` 显示在网格中，当前检查的因数用高亮色标记。
- **步进流程**：  
  1. 初始显示 `n=8, k=7`。  
  2. 遍历 `i=1`：显示 `i=1 ≤7`，包裹数 `8/1=8`；`n/i=8 >7` 不更新。  
  3. 遍历 `i=2`：显示 `i=2 ≤7`，包裹数 `8/2=4`；`n/i=4 ≤7`，更新最小包裹数为 `2`。  
  4. 最终结果 `2` 以闪烁效果展示。  

## 复古像素风格
- **8位色彩**：使用红、蓝、绿像素块表示因数对。
- **音效**：  
  - 发现合法因数时播放“滴”声。  
  - 更新最小值时播放“叮”声。  

---

# 核心代码实现

```cpp
#include <stdio.h>
int main() {
    int t, n, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        int ans = n; // 初始化为最大可能值
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                if (i <= k) ans = (n/i < ans) ? n/i : ans;
                if (n/i <= k) ans = (i < ans) ? i : ans;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

# 个人心得摘录

- **调试经验**：注意 `i` 和 `n/i` 都要检查，避免漏掉较大因数。
- **优化顿悟**：遍历到 `√n` 是关键，无需完整遍历所有数。

---
处理用时：79.31秒