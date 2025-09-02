# 题目信息

# Robin Hood in Town

## 题目描述

In Sherwood, we judge a man not by his wealth, but by his merit.



Look around, the rich are getting richer, and the poor are getting poorer. We need to take from the rich and give to the poor. We need Robin Hood!

There are $ n $ people living in the town. Just now, the wealth of the $ i $ -th person was $ a_i $ gold. But guess what? The richest person has found an extra pot of gold!

More formally, find an $ a_j=max(a_1, a_2, \dots, a_n) $ , change $ a_j $ to $ a_j+x $ , where $ x $ is a non-negative integer number of gold found in the pot. If there are multiple maxima, it can be any one of them.

A person is unhappy if their wealth is strictly less than half of the average wealth $ ^{\text{∗}} $ .

If strictly more than half of the total population $ n $ are unhappy, Robin Hood will appear by popular demand.

Determine the minimum value of $ x $ for Robin Hood to appear, or output $ -1 $ if it is impossible.

 $ ^{\text{∗}} $ The average wealth is defined as the total wealth divided by the total population $ n $ , that is, $ \frac{\sum a_i}{n} $ , the result is a real number.

## 说明/提示

In the first test case, it is impossible for a single person to be unhappy.

In the second test case, there is always $ 1 $ happy person (the richest).

In the third test case, no additional gold are required, so the answer is $ 0 $ .

In the fourth test case, after adding $ 15 $ gold, the average wealth becomes $ \frac{25}{4} $ , and half of this average is $ \frac{25}{8} $ , resulting in $ 3 $ people being unhappy.

In the fifth test case, after adding $ 16 $ gold, the average wealth becomes $ \frac{31}{5} $ , resulting in $ 3 $ people being unhappy.

## 样例 #1

### 输入

```
6
1
2
2
2 19
3
1 3 20
4
1 2 3 4
5
1 2 3 4 5
6
1 2 1 1 1 25```

### 输出

```
-1
-1
0
15
16
0```

# AI分析结果



## 唯一算法分类  
**无算法分类**（核心为数学推导与不等式处理）

---

## 综合分析与结论  
### 核心逻辑  
1. **特判**：当 $n \le 2$ 时无解（无法满足超过半数条件）。  
2. **排序**：将数组从小到大排序，取第 $k = \lfloor n/2 \rfloor + 1$ 小的元素 $a_k$。  
3. **数学推导**：  
   - 要使得超过半数的人财富严格小于 $\frac{\text{总财富} + x}{2n}$，只需保证 $a_k < \frac{\text{总财富} + x}{2n}$。  
   - 解得 $x > 2n \cdot a_k - \text{总财富}$，取最小非负整数 $x = \max(0, 2n \cdot a_k - \text{总财富} + 1)$。  

### 解决难点  
- **关键公式**：通过中位数性质推导阈值，避免二分法的多次验证。  
- **可视化设计**：  
  - **动画流程**：排序数组 → 高亮第 $k$ 个元素 → 显示总财富和计算过程 → 最终输出 $x$。  
  - **颜色标记**：用不同颜色区分排序后的数组、中位数元素、总财富计算。  
  - **复古风格**：用像素风格展示数组排序和关键步骤，音效提示计算完成。  

---

## 题解清单 (≥4星)  
### 1. Karieciation（5星）  
- **亮点**：公式推导清晰，代码简洁高效。  
- **核心代码**：  
  ```cpp  
  sort(a+1, a+1+n);  
  ll v = (ll)a[n/2+1] * n * 2;  
  x = max(0, v - sum + 1);  
  ```  
- **评分**：思路清晰（5）、代码可读性（5）、实践性（5）。  

### 2. naroto2022（4星）  
- **亮点**：详细解释中位数与阈值关系，代码简洁。  
- **个人心得**：“直接取中间元素，倒推总财富，省去多次遍历”。  
- **评分**：思路清晰（4）、代码可读性（5）、实践性（4）。  

### 3. alan1118（4星）  
- **亮点**：快速判断 $n \le 2$ 的情况，公式推导明确。  
- **代码片段**：  
  ```cpp  
  LL p = a[n/2 + 1];  
  LL m = p * 2 * n + 1;  
  cout << max(0LL, m - sum) << endl;  
  ```  
- **评分**：思路清晰（4）、代码可读性（4）、优化程度（4）。  

---

## 最优思路提炼  
### 关键公式与推导  
1. **排序后取中位数**：排序后第 $k = \lfloor n/2 \rfloor + 1$ 个元素 $a_k$ 是阈值。  
2. **不等式转换**：  
   $$ a_k < \frac{\text{sum} + x}{2n} \implies x > 2n \cdot a_k - \text{sum} $$  
   $$ x_{\text{min}} = \max(0, 2n \cdot a_k - \text{sum} + 1) $$  

### 实现技巧  
- **排序优化**：直接取排序后的中间元素，无需遍历统计。  
- **避免浮点运算**：用整数运算推导 $x$，避免精度问题。  

---

## 类似题目推荐  
1. **P1168 中位数**（中位数性质应用）  
2. **P2879 [USACO07JAN] Balanced Lineup**（极差与区间查询）  
3. **P2218 [HAOI2007] 覆盖问题**（几何最优化与二分）  

---

## 可视化与算法演示  
### 像素化动画设计  
- **步骤演示**：  
  1. **排序动画**：数组元素以像素方块动态排序，高亮交换过程。  
  2. **中位数标记**：第 $k$ 个元素闪烁显示，标注 $a_k$ 值。  
  3. **公式计算**：显示总财富 `sum` 和 $2n \cdot a_k$，逐步计算差值。  
  4. **结果输出**：最终 $x$ 以像素字体弹出，播放胜利音效。  

### 复古交互功能  
- **音效**：排序完成（8-bit音效）、计算成功（上扬音调）。  
- **自动模式**：模拟“AI推导”，自动展示排序和公式计算流程。  

---

## 代码实现（关键部分）  
```cpp  
#include <bits/stdc++.h>  
using namespace std;  
typedef long long ll;  

int main() {  
    int T; cin >> T;  
    while (T--) {  
        int n; cin >> n;  
        vector<ll> a(n);  
        ll sum = 0;  
        for (auto &x : a) cin >> x, sum += x;  
        if (n <= 2) { cout << "-1\n"; continue; }  
        sort(a.begin(), a.end());  
        int k = (n / 2);  
        ll required = 2 * n * a[k] + 1;  
        ll x = max(0LL, required - sum);  
        cout << x << '\n';  
    }  
    return 0;  
}  
```  

**核心思想**：排序后利用中位数性质直接推导最小 $x$，避免复杂计算。

---
处理用时：66.19秒