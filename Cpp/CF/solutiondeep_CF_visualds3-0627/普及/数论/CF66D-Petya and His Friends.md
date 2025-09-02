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
**数学构造**

---

### 题解思路与解决难点

#### 核心思路
构造前三个数使其两两有共同质因数，但整体 GCD 为 1，后续数为其乘积的倍数。例如：
- 前三个数选为 **6（2×3）、10（2×5）、15（3×5）**，后续数为 **30（2×3×5）** 的倍数。
- 两两之间必有公因数（2/3/5），但所有数的整体 GCD 为 1。

#### 解决难点
1. **两两不互质**：每个数至少包含两个不同质因数。
2. **整体 GCD 为 1**：前三个数通过质因数组合确保整体无公共质因数。
3. **避免大数问题**：通过合理选择质因数组合，避免高精度运算。

---

### 题解评分（≥4星）

1. **Fan_Tuan（5星）**  
   - 思路清晰，直接构造前三个数为 6、15、10，后续数为 10 的倍数。
   - 代码简洁，无需高精度，可读性强。

2. **youdu666（5星）**  
   - 构造前三个数为 6、10、15，后续数为 30 的倍数。
   - 代码简洁高效，时间复杂度为 O(n)。

3. **Binary_Search_Tree（4星）**  
   - 数学严谨，通过质数分配构造每个数。
   - 需高精度实现，代码较长但逻辑明确。

---

### 最优思路提炼
1. **质因数组合构造法**  
   选择三个质数（如 2、3、5），构造前三个数为两两乘积，后续数为三者乘积的倍数。  
   - 前三个数：6（2×3）、10（2×5）、15（3×5）  
   - 后续数：30×k（k≥1）

2. **无需高精度**  
   通过合理选择质因数组合，确保所有数在 64 位整数范围内。

---

### 类似算法套路
- **质因数分解构造**：通过控制质因数的分布，满足特定 GCD/LCM 条件。
- **多条件组合设计**：在约束条件下构造数列，如互质但整体有公因数。

---

### 推荐题目
1. [P5535 【XR-3】小道消息](https://www.luogu.com.cn/problem/P5535)  
2. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)  
3. [P2445 动物园的笼子问题](https://www.luogu.com.cn/problem/P2445)

---

### 个人心得摘录
- **构造思维**：跳出常规，利用质因数组合的互补性。
- **特判 n=2**：必须单独处理，否则矛盾。

---

### 算法可视化设计
#### 核心逻辑演示
1. **质因数分解展示**  
   - 用不同颜色标记 2（红）、3（绿）、5（蓝）。
   - 前三个数显示为组合块：6（红+绿）、10（红+蓝）、15（绿+蓝）。
   - 后续数显示为 30（红+绿+蓝）的倍数。

2. **交互式步进**  
   - 用户点击“下一步”生成一个数，显示其质因数分解。
   - 高亮当前数的质因数，并标注与其他数的公共因数。

#### 复古像素风格
- **8 位调色板**：红（#FF0000）、绿（#00FF00）、蓝（#0000FF）。
- **Canvas 动画**：用像素方块表示质因数组合，如 6 显示为红色和绿色方块拼接。
- **音效**：生成数时播放 8 位音效，成功构造时播放胜利音效。

#### 关键代码片段（JS）
```javascript
// 构造数列并绘制
function generateNumbers(n) {
    let numbers = [];
    if (n <= 2) return [];
    numbers.push(6, 10, 15);
    for (let i = 4; i <= n; i++) {
        numbers.push(30 * (i - 2));
    }
    return numbers;
}

// 绘制质因数分解
function drawFactors(number, ctx, x, y) {
    const factors = {2: 'red', 3: 'green', 5: 'blue'};
    Object.keys(factors).forEach(p => {
        if (number % p === 0) {
            ctx.fillStyle = factors[p];
            ctx.fillRect(x, y, 16, 16);
            x += 16;
        }
    });
}
```

---

### 最终结论
通过质因数组合构造法，可高效解决该问题，无需复杂算法或高精度运算。核心在于利用前三个数的互补质因数分布，确保两两有公因数且整体 GCD 为 1。

---
处理用时：155.09秒