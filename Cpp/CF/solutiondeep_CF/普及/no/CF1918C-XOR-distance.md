# 题目信息

# XOR-distance

## 题目描述

You are given integers $ a $ , $ b $ , $ r $ . Find the smallest value of $ |({a \oplus x}) - ({b \oplus x})| $ among all $ 0 \leq x \leq r $ .

 $ \oplus $ is the operation of [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR), and $ |y| $ is [absolute value](https://en.wikipedia.org/wiki/Absolute_value) of $ y $ .

## 说明/提示

In the first test, when $ r = 0 $ , then $ x $ is definitely equal to $ 0 $ , so the answer is $ |{4 \oplus 0} - {6 \oplus 0}| = |4 - 6| = 2 $ .

In the second test:

- When $ x = 0 $ , $ |{0 \oplus 0} - {3 \oplus 0}| = |0 - 3| = 3 $ .
- When $ x = 1 $ , $ |{0 \oplus 1} - {3 \oplus 1}| = |1 - 2| = 1 $ .
- When $ x = 2 $ , $ |{0 \oplus 2} - {3 \oplus 2}| = |2 - 1| = 1 $ .

Therefore, the answer is $ 1 $ .

In the third test, the minimum is achieved when $ x = 1 $ .

## 样例 #1

### 输入

```
10
4 6 0
0 3 2
9 6 10
92 256 23
165 839 201
1 14 5
2 7 2
96549 34359 13851
853686404475946 283666553522252166 127929199446003072
735268590557942972 916721749674600979 895150420120690183```

### 输出

```
2
1
1
164
542
5
3
37102
27934920819538516
104449824168870225```

# AI分析结果



# XOR-distance

## 题目描述

给定整数 $a$、$b$、$r$。请找出在 $0 \leq x \leq r$ 范围内，使得 $|({a \oplus x}) - ({b \oplus x})|$ 最小的值。其中 $\oplus$ 表示按位异或运算，$|y|$ 表示绝对值。

## 说明/提示

样例说明详见原题。

---

**算法分类**：贪心、位运算

---

### 题解对比与结论

#### 共同思路
1. **大小预处理**：确保 $a \geq b$，简化后续处理逻辑。
2. **最高不同位定位**：找到二进制最高位中 $a$ 与 $b$ 不同的位置，此位决定两数原始大小关系。
3. **贪心策略**：从最高不同位的下一位开始，对后续每一位进行判断，若翻转该位能缩小差值且不超过 $r$，则进行翻转。

#### 解决难点
- **避免大小关系反转**：保留最高不同位的原始值，防止翻转导致大小关系反转。
- **动态更新限制**：在贪心过程中实时维护 $x$ 的累加值，确保不超过 $r$。

---

### 精选题解

#### 1. BIG_CUTE_BUG（5星）
**关键亮点**：
- 使用 `__builtin_clzll` 快速定位最高不同位。
- 直接在原数上进行位翻转，避免构造额外数组。
- 代码简洁高效，时间复杂度 $O(\log \max(a,b))$。

**核心代码**：
```cpp
for(int i= min(lg(a^ b)- 1, lg(u)); i>= 0; i--) {
    if((a& (1ll<< i)) == (b& (1ll<< i))) continue;
    if((a& (1ll<< i)) && ((us| (1ll<< i))<= u)) {
        a ^= (1ll<< i), b ^= (1ll<< i), us |= (1ll<< i);
    }
}
cout << a - b << '\n';
```

#### 2. GXZJQ（4星）
**关键亮点**：
- 显式标注处理不同位的逻辑，代码可读性强。
- 通过 `swap` 预处理保证 $a \geq b$，统一处理逻辑。

**核心代码**：
```cpp
for (long long i = 60; i >= 0; i--) {
    if (flag) flag = 0; // 跳过最高不同位
    else if (!a2 && x + (1ll << i) <= r) {
        x += (1ll << i);
        a ^= (1ll << i); b ^= (1ll << i);
    }
}
```

#### 3. Special_Tony（4星）
**关键亮点**：
- 极简实现，直接遍历每一位判断是否翻转。
- 通过位运算直接操作数值，无额外空间开销。

**核心代码**：
```cpp
for (int i = 62; ~i; --i) {
    if ((1ll << i) <= r && (a & (1ll << i)) && !(b & (1ll << i)) 
        && (a ^ (1ll << i)) >= (b ^ (1ll << i))) {
        a ^= 1ll << i; b ^= 1ll << i; r -= 1ll << i;
    }
}
```

---

### 关键技巧总结
1. **位运算贪心**：从高位到低位逐位处理，优先缩小高位差异。
2. **动态约束维护**：在翻转时实时检查 $x$ 的累加值是否超出 $r$。
3. **大小关系锁定**：保留最高不同位的原始值，避免大小反转。

---

### 相似题目推荐
1. [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)  
   **考察点**：位运算贪心选择最优操作序列。
2. [P1594 护卫队](https://www.luogu.com.cn/problem/P1594)  
   **考察点**：动态规划与贪心结合处理区间问题。
3. [P1582 倒水](https://www.luogu.com.cn/problem/P1582)  
   **考察点**：二进制表示与最少操作次数。

---
处理用时：71.52秒