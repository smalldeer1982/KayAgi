# 题目信息

# Our Tanya is Crying Out Loud

## 题目描述

Right now she actually isn't. But she will be, if you don't solve this problem.

You are given integers $ n $ , $ k $ , $ A $ and $ B $ . There is a number $ x $ , which is initially equal to $ n $ . You are allowed to perform two types of operations:

1. Subtract 1 from $ x $ . This operation costs you $ A $ coins.
2. Divide $ x $ by $ k $ . Can be performed only if $ x $ is divisible by $ k $ . This operation costs you $ B $ coins.

 What is the minimum amount of coins you have to pay to make $ x $ equal to $ 1 $ ?

## 说明/提示

In the first testcase, the optimal strategy is as follows:

- Subtract 1 from $ x $ ( $ 9→8 $ ) paying 3 coins.
- Divide $ x $ by 2 ( $ 8→4 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 4→2 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 2→1 $ ) paying 1 coin.

The total cost is $ 6 $ coins.

In the second test case the optimal strategy is to subtract 1 from $ x $ $ 4 $ times paying $ 8 $ coins in total.

## 样例 #1

### 输入

```
9
2
3
1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
5
2
20
```

### 输出

```
8
```

## 样例 #3

### 输入

```
19
3
4
2
```

### 输出

```
12
```

# AI分析结果



---

**唯一算法分类**：贪心

---

### **题解思路与算法要点**

1. **核心思路**  
   - 贪心策略：在每一步选择当前最优操作（减或除），确保总费用最小。
   - **关键变量**：当前值 `n`，减法的代价 `A`，除法的代价 `B`，总费用 `ans`。

2. **解决难点**  
   - **余数处理**：当 `n` 不能被 `k` 整除时，先减到最近的 `k` 的倍数。
   - **费用比较**：在每次除法前，比较 `B` 与 `(n - n/k) * A`，决定是否除法更优。
   - **特判 `k=1`**：避免死循环，直接减到 1。

3. **算法流程**  
   ```plaintext
   while n > 1:
       if k == 1:
           ans += (n-1)*A
           break
       if n < k:
           ans += (n-1)*A
           break
       ans += (n % k) * A     # 处理余数
       n -= n % k             # 减到 k 的倍数
       if B < (n - n/k) * A:  # 除法更优
           ans += B
           n = n/k
       else:                  # 减法更优，直接减到底
           ans += (n-1)*A
           break
   ```

---

### **题解评分 (≥4星)**

1. **作者：miraculously (4星)**  
   - **亮点**：代码简洁，逻辑清晰，处理余数和费用比较高效。  
   - **代码片段**：  
     ```cpp
     ans += n%k * a;
     n -= n%k;
     if (b < (n - n/k) * a) ans += b, n /= k;
     else { ans += (n-1)*a; break; }
     ```

2. **作者：thomas_zjl (4星)**  
   - **亮点**：明确解题思路和优化逻辑，代码注释详细。  
   - **代码片段**：  
     ```cpp
     ans += (n % k) * a;
     n = n - n % k;
     if (b > (n - n/k) * a) { ans += (n-1)*a; break; }
     ```

3. **作者：Aisaka_Taiga (4星)**  
   - **亮点**：引入 `kkk` 阈值优化计算，特判 `k=1` 全面。  
   - **代码片段**：  
     ```cpp
     kkk = (b-1)/a + 1;  // 除法的最小收益阈值
     if (k == 1) { ans = (n-1)*a; break; }
     ```

---

### **最优思路与技巧**

1. **关键优化点**  
   - **余数处理公式**：`n -= n % k` 快速得到最近的 `k` 的倍数。
   - **费用比较阈值**：计算 `(n - n/k) * A` 作为减法的总代价，与 `B` 直接对比。
   - **提前终止条件**：一旦发现减法更优，直接减到底，避免后续无效循环。

2. **思维角度**  
   - 将大问题分解为每一步的最优子问题，逐步逼近最终解。
   - 通过数学推导证明贪心选择的正确性（如除法操作的费用优势单调递减）。

---

### **同类型题与算法套路**

1. **通用解法**  
   - 贪心策略的典型应用场景：操作代价不同，需动态选择最优步骤。
   - 类似题目：最少硬币问题、任务调度优化等。

2. **推荐题目**  
   - **洛谷 P1031**：均分纸牌（贪心分配）  
   - **CF 1328A**：Divisibility Problem（余数处理）  
   - **洛谷 P4995**：跳跳！（贪心选择最大/小值）

---

### **个人心得摘录**

- **作者：cym_233**：  
  > “一定要特判 `k=1` 的情况，否则会卡死在一个测试点！”  
  （调试教训：边界条件需全面覆盖）

- **作者：tribool4_in**：  
  > “暴力不可能，直接贪心，每一步都要 O(1) 处理余数。”  
  （思维转换：从暴力到贪心的优化思路）

---

### **可视化与算法演示**

1. **动画设计**  
   - **动态步骤**：展示 `n` 的变化过程，高亮当前操作（红色减法，蓝色除法）。  
   - **费用统计**：实时显示总费用 `ans` 的累计过程。  
   - **复古像素风格**：  
     - **颜色方案**：16 色调色板，绿色背景，黄色数字。  
     - **音效**：减法时播放“滴”声，除法时播放“咚”声，背景 8-bit 音乐循环。  

2. **交互功能**  
   - **步进控制**：允许暂停/继续，调整动画速度（1x/2x/0.5x）。  
   - **AI 自动演示**：自动执行最优策略，展示关键决策点。  

3. **Canvas 实现**  
   ```javascript
   // 伪代码：绘制当前 n 值和操作
   function drawStep(n, operation) {
       ctx.fillStyle = "#8B0000"; // 暗红色背景
       ctx.fillRect(0, 0, canvas.width, canvas.height);
       ctx.fillStyle = "#FFFF00"; // 黄色数字
       ctx.fillText(`n = ${n}`, 50, 50);
       ctx.fillStyle = operation === "subtract" ? "#FF0000" : "#0000FF";
       ctx.fillText(`操作：${operation}`, 50, 80);
   }
   ```

---

### **代码实现（核心逻辑）**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int n, k, a, b, ans = 0;
    cin >> n >> k >> a >> b;
    if (k == 1) { // 特判 k=1
        cout << (n-1)*a;
        return 0;
    }
    while (n > 1) {
        if (n < k) { // 直接减到底
            ans += (n-1)*a;
            break;
        }
        ans += (n % k) * a; // 处理余数
        n -= n % k;
        if (b < (n - n/k) * a) { // 除法更优
            ans += b;
            n /= k;
        } else { // 减法更优，直接结束
            ans += (n-1)*a;
            break;
        }
    }
    cout << ans;
    return 0;
}
```

---
处理用时：84.19秒