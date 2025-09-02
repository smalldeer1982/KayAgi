# 题目信息

# Shohag Loves XOR (Hard Version)

## 题目描述

This is the hard version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ x \oplus y $ is divisible $ ^{\text{∗}} $ by either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ a $ is divisible by the number $ b $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 说明/提示

In the first test case, for $ x = 7 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 10 $ , and they are $ 1 $ , $ 7 $ , and $ 9 $ .

- $ y = 1 $ is valid because $ x \oplus y = 7 \oplus 1 = 6 $ and $ 6 $ is divisible by $ y = 1 $ .
- $ y = 7 $ is valid because $ x \oplus y = 7 \oplus 7 = 0 $ and $ 0 $ is divisible by both $ x = 7 $ and $ y = 7 $ .
- $ y = 9 $ is valid because $ x \oplus y = 7 \oplus 9 = 14 $ and $ 14 $ is divisible by $ x = 7 $ .

## 样例 #1

### 输入

```
5
7 10
2 3
6 4
1 6
4 1```

### 输出

```
3
2
2
6
1```

# AI分析结果



### 题目重写

# Shohag 爱异或（困难版）

## 题目描述

这是该问题的困难版本，两个版本的不同之处已用粗体标出。只有解决了两个版本的问题才能进行 hack。

Shohag 有两个整数 $x$ 和 $m$。请帮他统计满足条件 $1 \le y \le m$ 的整数 $y$ 的数量，使得 $x \oplus y$ 能被 $x$、$y$ 中的至少一个整除。其中 $\oplus$ 表示[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)运算。

## 说明/提示

在第一个测试样例中，当 $x = 7$ 时，在 $1$ 到 $m = 10$ 的整数中有 $3$ 个有效的 $y$ 值：$1$、$7$、$9$。

- $y = 1$ 有效，因为 $x \oplus y = 7 \oplus 1 = 6$ 能被 $y = 1$ 整除
- $y = 7$ 有效，因为 $x \oplus y = 0$ 可被 $x$ 和 $y$ 同时整除
- $y = 9$ 有效，因为 $x \oplus y = 14$ 能被 $x = 7$ 整除

---

### 题解分析与结论

#### 关键思路总结
1. **分治策略**：将 $y$ 分为小范围暴力枚举（$y < 2^k$）和大范围数学推导（$y \ge 2^k$），其中 $k$ 是 $x$ 的二进制最高位
2. **异或性质**：利用 $x \oplus y \le x + y$ 的特性，当 $y \ge 2^k$ 时，$x \oplus y$ 的最高位与 $y$ 相同，此时无法被 $y$ 整除
3. **数学优化**：对满足 $x \mid (x \oplus y)$ 的情况，推导 $y = kx \oplus x$ 的形式，通过整除关系快速统计

#### 评分较高题解

1. **littlebug（4星）**
   - **亮点**：利用二进制位确定分界点，小范围暴力+大范围二分，边界修正确保正确性
   - **代码核心**：
     ```cpp
     int t = (1ll << (bit + 1)) - 1; // 最高位分界点
     for (int i=1; i<t; i++) {...} // 暴力枚举小范围
     int l=1, r=m/x+100;          // 二分统计大范围
     while (l<r) {
         mid = l+r+1>>1;
         (x*mid <= m) ? l=mid : r=mid-1;
     }
     ```

2. **LiJoQiao（4星）**
   - **亮点**：分情况讨论 $x \mid (x \oplus y)$ 的情况，推导 $y = kx \oplus x$ 的形式，边界特判清晰
   - **代码核心**：
     ```cpp
     ll j = m/x;                 // 最大系数
     ans += j - (j-1>=1);        // 排除 y=0 的情况
     for (int y=1; y<=min(x,m); y++) 
         if ((x^y) % y == 0) ans++;
     ```

3. **Dangerise（4星）**
   - **亮点**：二进制分段处理，类似数位DP思想，按最高位分组统计
   - **代码核心**：
     ```cpp
     int f = highbit(x) * 2;     // 分界点 2^k
     for (int y=1; y<=f; y++) {  // 暴力小范围
         if ((x^y) % y == 0) cnt++;
     }
     ```

#### 调试心得
- **littlebug**：发现二分单调性不完美后，通过检查前10和后10个值修正结果
- **LiJoQiao**：注意 $y=x$ 的重复计数问题，通过条件判断去重

---

### 推荐相似题目
1. [P4317 花神的数论题](https://www.luogu.com.cn/problem/P4317) - 二进制位统计技巧
2. [P2114 NOI2014 起床困难综合症](https://www.luogu.com.cn/problem/P2114) - 位运算性质应用
3. [P1594 护卫队](https://www.luogu.com.cn/problem/P1594) - 数学推导与分治策略

---
处理用时：83.16秒