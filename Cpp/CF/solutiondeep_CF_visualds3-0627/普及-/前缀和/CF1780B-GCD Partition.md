# 题目信息

# GCD Partition

## 题目描述

While at Kira's house, Josuke saw a piece of paper on the table with a task written on it.

The task sounded as follows. There is an array $ a $ of length $ n $ . On this array, do the following:

- select an integer $ k > 1 $ ;
- split the array into $ k $ subsegments $ ^\dagger $ ;
- calculate the sum in each of $ k $ subsegments and write these sums to another array $ b $ (where the sum of the subsegment $ (l, r) $ is $ {\sum_{j = l}^{r}a_j} $ );
- the final score of such a split will be $ \gcd(b_1, b_2, \ldots, b_k)^\ddagger $ .

The task is to find such a partition that the score is maximum possible. Josuke is interested in this task but is not strong in computer science. Help him to find the maximum possible score.

 $ ^\dagger $ A division of an array into $ k $ subsegments is $ k $ pairs of numbers $ (l_1, r_1), (l_2, r_2), \ldots, (l_k, r_k) $ such that $ l_i \le r_i $ and for every $ 1 \le j \le k - 1 $ $ l_{j + 1} = r_j + 1 $ , also $ l_1 = 1 $ and $ r_k = n $ . These pairs represent the subsegments.

 $ ^\ddagger $ $ \gcd(b_1, b_2, \ldots, b_k) $ stands for the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the array $ b $ .

## 说明/提示

In the first test case, you can choose $ k = 2 $ and split the array into subsegments $ (1, 2) $ and $ (3, 4) $ .

Then the score of such a partition will be equal to $ \gcd(a_1 + a_2, a_3 + a_4) = \gcd(2 + 2, 1 + 3) = \gcd(4, 4) = 4 $ .

In the fourth test case, you can choose $ k = 3 $ and split the array into subsegments $ (1, 2), (3, 5), (6, 6) $ .

The split score is $ \gcd(1 + 2, 1 + 1 + 1, 3) = 3 $ .

## 样例 #1

### 输入

```
6
4
2 2 1 3
2
1 2
3
1 4 5
6
1 2 1 1 1 3
10
12 30 37 88 12 78 89 17 2 12
6
7 7 7 7 7 7```

### 输出

```
4
1
5
3
1
21```

# AI分析结果



---

**唯一算法分类**：数学（GCD性质与贪心策略）

---

### 题解思路、算法要点与解决难点

1. **核心结论**  
   任意分割成 k>1 段的方案，其最大 GCD 必定可通过分割成 2 段得到。  
   **证明思路**：  
   - 合并任意两段后，GCD 不会更小（见公式推导）  
   - 数学归纳可得最优解必在 k=2 时出现  

2. **实现方法**  
   - **前缀和**：预处理数组前缀和，快速计算任意子段和  
   - **枚举分割点**：遍历所有可能的分割点 i，计算前 i 项和与剩余项和的 GCD  
   - **取最大值**：维护全局最大值  

3. **复杂度分析**  
   - 时间：O(n) 预处理 + O(n) 遍历 → O(n)  
   - 空间：O(n) 存储前缀和数组  

---

### 题解评分 (≥4星)

1. **wzc_IOI_czl（⭐⭐⭐⭐⭐）**  
   - 亮点：简洁直击核心结论，代码实现短小精悍  
   - 代码可读性高，边界处理明确  

2. **RNTBW（⭐⭐⭐⭐）**  
   - 亮点：详细数学证明，强调关键推论  
   - 代码注释清晰，注意 long long 处理  

3. **Enjoy2024（⭐⭐⭐⭐）**  
   - 亮点：从基础数论性质推导结论  
   - 提出线段树优化思路（虽非必需但展示拓展性）  

---

### 最优思路提炼

- **关键技巧**：利用 GCD 的合并性质将问题简化为两段分割  
- **实现要点**：  
  1. 预处理前缀和数组  
  2. 遍历所有可能的分割点 i  
  3. 计算 `gcd( sum[1..i], sum[i+1..n] )`  
  4. 维护最大值  

---

### 类似题目推荐

1. **P1414 又是毕业季II**（GCD 性质应用）  
2. **P1894 [USACO4.2] 完美的牛栏**（分割序列求极值）  
3. **P1495 曹冲养猪**（中国剩余定理与模数运算）  

---

### 代码实现（核心逻辑）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        vector<ll> a(n+1), s(n+1);
        for(int i=1; i<=n; ++i) {
            cin >> a[i];
            s[i] = s[i-1] + a[i];
        }
        ll ans = 0;
        for(int i=1; i<n; ++i) { // 注意i<n的边界
            ans = max(ans, gcd(s[i], s[n]-s[i]));
        }
        cout << ans << '\n';
    }
}
```

---

### 可视化与算法演示设计

**动画方案**：  
1. **像素风格界面**：  
   - 数组元素显示为 16x16 像素块，数值以 8-bit 字体显示  
   - 当前分割线用红色像素条标识，左右区域用不同底色  

2. **动态过程**：  
   - 分割线从左向右扫描，每帧显示：  
     - 左和 `sum[1..i]`（绿色）  
     - 右和 `sum[i+1..n]`（蓝色）  
     - 当前 GCD 值（黄色闪烁显示）  

3. **音效交互**：  
   - 分割线移动：短促 "beep" 声  
   - 发现新最大值：上升音阶  
   - 最终结果：经典 FC 过关音效  

**Canvas 伪代码**：  
```javascript
function drawFrame(i) {
    ctx.clearRect(0,0,W,H);
    // 绘制数组
    drawArray(a, x=50, y=50); 
    // 绘制分割线
    drawLine(x=50+i*16, y=50, color='red');
    // 显示当前GCD
    ctx.fillText(`GCD: ${currentGCD}`, 100, 200);
}
```

---

### 个人心得摘录

> "C题出锅了，D题是恶心交互，E题不会，下班力（喜" —— wzc_IOI_czl  
> **启示**：比赛时需快速识别可解题目，避免在复杂题中过度耗时

---

### 综合结论

本题通过深入分析 GCD 的数学性质，将看似复杂的分割问题简化为线性扫描。前缀和的巧妙应用使得算法效率达到最优，展现了数论与贪心策略的完美结合。可视化方案采用复古像素风格，通过动态扫描与音效反馈，帮助理解核心逻辑。

---
处理用时：66.60秒