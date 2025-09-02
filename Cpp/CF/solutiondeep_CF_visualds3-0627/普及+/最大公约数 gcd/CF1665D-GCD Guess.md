# 题目信息

# GCD Guess

## 题目描述

This is an interactive problem.

There is a positive integer $ 1 \le x \le 10^9 $ that you have to guess.

In one query you can choose two positive integers $ a \neq b $ . As an answer to this query you will get $ \gcd(x + a, x + b) $ , where $ \gcd(n, m) $ is the [greatest common divisor](<https://en.wikipedia.org/wiki/Greatest common divisor>) of the numbers $ n $ and $ m $ .

To guess one hidden number $ x $ you are allowed to make no more than $ 30 $ queries.

## 说明/提示

The first hidden number is $ 4 $ , that's why the answers for the queries are:

"? 1 2" — $ \gcd(4 + 1, 4 + 2) = \gcd(5, 6) = 1 $ .

"? 12 4" — $ \gcd(4 + 12, 4 + 4) = \gcd(16, 8) = 8 $ .

The second hidden number is $ 10^9 $ , that's why the answer for the query is:

"? 2000000000 1999999999" — $ \gcd(3 \cdot 10^9, 3 \cdot 10^9 - 1) = 1 $ .

These queries are made only for understanding the interaction and are not enough for finding the true $ x $ .

## 样例 #1

### 输入

```
2

1

8


1```

### 输出

```
? 1 2

? 12 4

! 4
? 2000000000 1999999999

! 1000000000```

# AI分析结果



### 算法分类
**数学、二进制逐位确定**

---

### 综合分析与结论
本题要求通过不超过30次查询确定一个正整数x的值。核心思路是逐位确定x的二进制位，利用gcd的性质构造特定的查询条件。通过每次询问确定一位，总计30次恰好覆盖所有可能位。

**核心算法流程**：
1. 从低位到高位依次处理每一位。
2. 对于第i位，构造a和b使得它们的差为2^i。
3. 若返回的gcd是2^i的倍数，则该位为1，否则为0。
4. 更新ans的值，记录当前确定的二进制位。

**难点与解决方案**：
- **构造差值为2^i**：确保每次查询的差值为当前处理的二进制位的权重，从而分离出该位的信息。
- **避免溢出**：通过调整a和b的值，确保查询参数不超过题目限制的2e9。

---

### 题解评分（≥4星）
1. **听取MLE声一片（5星）**  
   - 思路清晰，逐位确定二进制位，代码简洁高效。
   - 关键点：构造a=2^(i-1)-ans和b=3*2^(i-1)-ans，利用gcd结果判断位值。
   - 代码可读性强，正确性明显。

2. **王熙文（5星）**  
   - 类似逐位思路，构造a=2^i-now和b=3*2^i-now。
   - 通过判断gcd是否为2^(i+1)的倍数确定该位。
   - 代码简洁，逻辑明确。

3. **y0y68（5星）**  
   - 直接构造a和b的差为2^(i+1)，通过gcd结果判断位值。
   - 代码最简，仅需一个循环，适合快速实现。

---

### 最优思路与技巧提炼
**关键技巧**：
1. **二进制逐位分解**：利用gcd(x+a, x+b) = gcd(x+a, b-a)的性质，将问题转化为逐位确定。
2. **参数构造**：每次处理第i位时，构造a和b使得差值为2^i，确保每次查询仅影响当前位。
3. **位值判断**：若返回的gcd是2^i的倍数，则当前位为1，否则为0。

**代码实现**：
```cpp
#include<iostream>
using namespace std;

int ask(int a, int b) {
    cout << "? " << a << " " << b << endl;
    int res; cin >> res;
    return res;
}

void solve() {
    int ans = 0;
    for (int i = 0; i < 30; ++i) {
        int a = (1 << i) - ans;
        int b = (3 << i) - ans;
        int g = ask(a, b);
        if (g % (2 << i) == 0)
            ans |= (1 << i);
    }
    cout << "! " << ans << endl;
}

int main() {
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
```

---

### 同类型题与算法套路
**类似题目特征**：
- 需要通过有限次查询确定数值。
- 利用数学性质（如gcd、位运算）分解问题。

**推荐题目**：
1. **CF 1527D** - MEX Tree（位运算与路径查询）
2. **CF 1493C** - DP + 二进制贪心
3. **洛谷 P1582** - 倒水（二进制应用）

---

### 可视化与算法演示
**动画设计**：
1. **像素风格界面**：用8位像素风格显示当前处理的二进制位、ans值和查询参数。
2. **关键步骤高亮**：
   - 当前处理的位（闪烁显示）。
   - ans的更新过程（颜色变化）。
   - gcd计算结果与位判断的对应关系（箭头/标记）。
3. **步进控制**：允许暂停/继续，调整动画速度观察每位处理细节。
4. **音效反馈**：成功设置位时播放上升音调，错误时短促提示。

**交互示例**：
- **初始状态**：显示x的二进制位均为灰色（未知）。
- **每一步骤**：高亮当前位，显示构造的a和b，计算gcd后更新ans。
- **最终结果**：所有位点亮，显示十进制结果。

---

**总结**：逐位二进制法是最优解，结合数学性质与高效查询设计，适用于类似数值猜谜问题。

---
处理用时：277.41秒