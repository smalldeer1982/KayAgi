# 题目信息

# Shohag Loves XOR (Easy Version)

## 题目描述

This is the easy version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ \mathbf{x \neq y} $ and $ x \oplus y $ is a divisor $ ^{\text{∗}} $ of either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ b $ is a divisor of the number $ a $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 说明/提示

In the first test case, for $ x = 6 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 9 $ , and they are $ 4 $ , $ 5 $ , and $ 7 $ .

- $ y = 4 $ is valid because $ x \oplus y = 6 \oplus 4 = 2 $ and $ 2 $ is a divisor of both $ x = 6 $ and $ y = 4 $ .
- $ y = 5 $ is valid because $ x \oplus y = 6 \oplus 5 = 3 $ and $ 3 $ is a divisor of $ x = 6 $ .
- $ y = 7 $ is valid because $ x \oplus y = 6 \oplus 7 = 1 $ and $ 1 $ is a divisor of both $ x = 6 $ and $ y = 7 $ .

In the second test case, for $ x = 5 $ , there are $ 2 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 7 $ , and they are $ 4 $ and $ 6 $ .

- $ y = 4 $ is valid because $ x \oplus y = 5 \oplus 4 = 1 $ and $ 1 $ is a divisor of both $ x = 5 $ and $ y = 4 $ .
- $ y = 6 $ is valid because $ x \oplus y = 5 \oplus 6 = 3 $ and $ 3 $ is a divisor of $ y = 6 $ .

## 样例 #1

### 输入

```
5
6 9
5 7
2 3
6 4
4 1```

### 输出

```
3
2
1
1
0```

# AI分析结果



**唯一算法分类**: 枚举优化

---

### **题解思路与解决难点**
#### **核心思路**
题目要求找出满足条件的y，使得x异或y的结果是x或y的因数。关键在于通过数学分析缩小y的枚举范围，避免暴力枚举大范围的m。

#### **解决难点**
1. **范围限制**：通过分析异或结果的性质，发现当y超过2x时，x异或y的值必然无法成为x或y的因数。因此，y的取值范围可缩小到 `[1, min(2x, m)]`。
2. **因数判断**：枚举范围内的每个y，计算x异或y的结果，检查其是否为x或y的因数。

#### **算法流程**
1. **枚举范围**：遍历y从1到 `min(2x, m)`。
2. **条件过滤**：跳过y等于x的情况。
3. **异或计算**：计算 `d = x ^ y`。
4. **因数检查**：判断d是否能整除x或y。

---

### **题解评分 ≥4星**
1. **作者：Chenyanxi0829（5星）**
   - **亮点**：代码简洁，直接枚举到 `2x`，逻辑清晰，可读性高。
   - **代码片段**：
     ```cpp
     for (int i = 1; i <= min(m, 2ll * x); i++) {
         ans += (x != i && (x % (x ^ i) == 0 || i % (x ^ i) == 0));
     }
     ```

2. **作者：Fiendish（4星）**
   - **亮点**：通过二进制位数分析，限制y的最高位不超过x的位数，优化枚举范围。
   - **代码片段**：
     ```cpp
     for (int i=1; i<min((1ll<<((int)__lg(x)+1)), m+1); i++) {
         if (i!=x && (x%(i^x)==0 || i%(i^x)==0)) ans++;
     }
     ```

3. **作者：postpone（4星）**
   - **亮点**：结合因数性质和异或结果的范围，明确枚举到 `2x`，代码简短高效。
   - **代码片段**：
     ```cpp
     m = min<ll>(2 * x, m);
     for (int i = 1; i <= m; i++) {
         int t = i ^ x;
         if (x % t == 0 || i % t == 0) ans++;
     }
     ```

---

### **最优思路与技巧**
- **范围优化**：利用数学推导将y的枚举范围从O(m)降至O(x)。
- **二进制分析**：通过最高位判断，确保异或结果不会超过有效因数范围。
- **代码简化**：直接枚举 `2x` 避免复杂位运算，保持代码可读性。

---

### **类似题型与套路**
- **相似题目**：涉及因数判断和位运算的题目，如：
  1. [洛谷 P1463 [POI2001] 反素数](https://www.luogu.com.cn/problem/P1463)
  2. [洛谷 P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)
  3. [洛谷 P4317 花神的数论题](https://www.luogu.com.cn/problem/P4317)

---

### **可视化与算法演示**
#### **动画设计**
- **可视化逻辑**：
  1. **枚举步骤**：展示y从1逐步增加到 `2x`，高亮当前y。
  2. **异或计算**：以二进制形式显示x和y的异或过程，结果高亮。
  3. **因数检查**：用不同颜色标记满足条件的y（如绿色通过，红色不通过）。

#### **复古像素风格**
- **颜色方案**：8位色（红、绿、蓝）区分不同状态。
- **音效提示**：成功匹配时播放上升音调，失败时短促低音。
- **Canvas动画**：用网格表示二进制位，异或结果实时更新。

#### **交互功能**
- **步进控制**：允许手动点击或自动播放。
- **参数调节**：动态调整x和m，观察不同输入的结果变化。

---

### **代码实现（核心逻辑）**
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int x;
        long long m;
        cin >> x >> m;
        m = min(m, 2LL * x); // 关键：限制范围到2x
        int ans = 0;
        for (int y = 1; y <= m; y++) {
            if (y == x) continue;
            int d = x ^ y;
            if (x % d == 0 || y % d == 0) ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

### **总结**
通过数学推导优化枚举范围是本题的核心，将时间复杂度从O(m)降至O(x)，极大提升效率。代码实现简洁，适合快速解决类似位运算与因数结合的问题。

---
处理用时：229.97秒