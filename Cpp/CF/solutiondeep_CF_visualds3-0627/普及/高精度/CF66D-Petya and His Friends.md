# 题目信息

# Petya and His Friends

## 题目描述

Little Petya has a birthday soon. Due this wonderful event, Petya's friends decided to give him sweets. The total number of Petya's friends equals to $ n $ .

Let us remind you the definition of the greatest common divisor: $ GCD(a_{1},...,a_{k})=d $ , where $ d $ represents such a maximal positive number that each $ a_{i} $ ( $ 1<=i<=k $ ) is evenly divisible by $ d $ . At that, we assume that all $ a_{i} $ 's are greater than zero.

Knowing that Petya is keen on programming, his friends has agreed beforehand that the $ 1 $ -st friend gives $ a_{1} $ sweets, the $ 2 $ -nd one gives $ a_{2} $ sweets, ..., the $ n $ -th one gives $ a_{n} $ sweets. At the same time, for any $ i $ and $ j $ ( $ 1<=i,j<=n $ ) they want the $ GCD(a_{i},a_{j}) $ not to be equal to $ 1 $ . However, they also want the following condition to be satisfied: $ GCD(a_{1},a_{2},...,a_{n})=1 $ . One more: all the $ a_{i} $ should be distinct.

Help the friends to choose the suitable numbers $ a_{1},...,a_{n} $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
99
55
11115
```

## 样例 #2

### 输入

```
4
```

### 输出

```
385
360
792
8360
```

# AI分析结果



### 算法分类
构造性数学、数论

---

### 题解思路与核心难点

#### 题目核心要求
构造 n 个**不同**的正整数，满足：
1. 任意两数的最大公约数（GCD）≠ 1
2. 所有数的 GCD = 1

#### 解决思路对比
1. **质数乘积法**（封禁用户、Binary_Search_Tree）
   - **核心思路**：取前 n 个质数，构造每个数 \( a_i = \prod_{j=1}^n p_j / p_i \)。此时所有数的 GCD 为 1，且两两有公共质因子。
   - **优点**：数学严谨，适用于任意 n ≥ 3。
   - **缺点**：需要高精度计算大数乘积，代码复杂度高。

2. **三数构造法**（Fan_Tuan、Back_Stuff、youdu666）
   - **核心思路**：构造三个基准数（如 6, 10, 15），后续数为它们的公倍数（如 30 的倍数）。
   - **优点**：无需高精度，代码简洁，时间复杂度 O(n)。
   - **验证**：前三个数的 GCD=1，后续数通过公倍数保证两两 GCD≠1，整体 GCD 仍为 1。

#### 关键难点
- **整体 GCD=1 的构造**：需确保存在某些数不包含公共质因子。
- **两两 GCD≠1**：所有数需共享至少一个质因子。
- **数值范围控制**：避免高精度计算（如三数构造法）。

---

### 题解评分（≥4星）

1. **Fan_Tuan（5星）**
   - **亮点**：代码极简，思路清晰，直接构造 6、10、15 后生成公倍数，避免复杂数学和高精度。
   - **代码片段**：
     ```cpp
     printf("%d\n", 6);
     printf("%d\n", 15);
     for (int i = 1; i <= n-2; i++)  
         printf("%d\n", 10*i);
     ```

2. **Back_Stuff（4星）**
   - **亮点**：明确选择 6 和 10 作为前两数，后续用 30 的倍数，逻辑直观。
   - **代码片段**：
     ```cpp
     cout << "6\n10";
     for (int i=3; i<=n; i++)
         cout << "\n" << (i-2)*30;
     ```

3. **youdu666（4星）**
   - **亮点**：统一使用 6、10、15 后接 30 倍数，直接处理 n≥3 的所有情况。
   - **代码片段**：
     ```cpp
     printf("6\n10\n15\n");
     for (int i=4; i<=n; i++)
         printf("%d\n", 30*(i-3));
     ```

---

### 最优思路提炼
**三数构造法**：
1. **基准数选择**：6（2×3）、10（2×5）、15（3×5）。
2. **后续数生成**：后续数为 30（2×3×5）的倍数。
3. **正确性验证**：
   - 前三个数的 GCD=1。
   - 所有数两两共享至少一个质因子（2/3/5）。
   - 后续数的加入不影响整体 GCD=1。

---

### 类似题目推荐
1. **CF359B**：构造数列满足特定 GCD 条件。
2. **AT_abc139_e**：数论构造与条件分析。
3. **洛谷 P2568**：GCD 性质与质数应用。

---

### 可视化算法演示
**动画设计**（基于三数构造法）：
1. **初始化**：展示三个基准数 6、10、15，高亮其质因子（红-2，绿-3，蓝-5）。
2. **生成后续数**：步进添加 30 的倍数，动态显示其质因子分解。
3. **GCD 验证**：
   - **两两 GCD**：用连线标记共享质因子。
   - **整体 GCD**：显示最终结果为 1。

**复古像素风格**：
- **颜色方案**：红（2）、绿（3）、蓝（5）、黄（其他质因子）。
- **音效**：添加数时播放 8-bit 音效，成功构造后播放胜利音效。

---

### 代码实现（三数构造法）
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n <= 2) {
        cout << -1;
        return 0;
    }
    cout << "6\n10\n15\n";
    for (int i = 4; i <= n; ++i)
        cout << 30 * (i - 3) << '\n';
    return 0;
}
```

---

### 总结
**三数构造法**以简洁的数学逻辑和代码实现，高效解决了题目要求，避免了高精度计算的复杂性，是本题的最优解法。其核心在于巧妙选择基准数并利用公倍数性质，既保证了条件满足，又控制了数值范围。

---
处理用时：132.53秒