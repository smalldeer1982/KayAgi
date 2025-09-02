# 题目信息

# LCM Challenge

## 题目描述

Some days ago, I learned the concept of LCM (least common multiple). I've played with it for several times and I want to make a big number with it.

But I also don't want to use many numbers, so I'll choose three positive integers (they don't have to be distinct) which are not greater than $ n $ . Can you help me to find the maximum possible least common multiple of these three integers?

## 说明/提示

The least common multiple of some positive integers is the least positive integer which is multiple for each of them.

The result may become very large, 32-bit integer won't be enough. So using 64-bit integers is recommended.

For the last example, we can chose numbers $ 7 $ , $ 6 $ , $ 5 $ and the LCM of them is $ 7·6·5=210 $ . It is the maximum value we can get.

## 样例 #1

### 输入

```
9
```

### 输出

```
504
```

## 样例 #2

### 输入

```
7
```

### 输出

```
210
```

# AI分析结果



# LCM Challenge

## 题目描述

给定一个正整数 $n$，请找到三个不超过 $n$ 的正整数（可以相同），使得它们的最小公倍数（LCM）最大。输出这个最大LCM值。

## 说明/提示

- 最小公倍数是能同时被这三个数整除的最小正整数
- 结果可能超过32位整数范围，建议使用64位整数类型
- 样例：当 $n=7$ 时，最优解为 7、6、5，其LCM为210

## 样例 #1

### 输入
9

### 输出
504

---

## 综合分析与结论

题目核心是通过数论分析确定三个数的选取策略。最优解主要基于奇偶性判断：

1. **奇数情况**：直接选取最大的三个连续数 $n×(n-1)×(n-2)$，因连续奇数和偶数互质。
2. **偶数情况**：
   - 若 $n$ 是6的倍数，选择 $(n-1)×(n-2)×(n-3)$ 避免公因子3的影响
   - 否则选择 $n×(n-1)×(n-3)$ 保证最大乘积且互质
3. **特判**：$n<3$ 时直接输出 $n$

---

## 精选题解

### 题解1：chinaxjh（5星）
**关键亮点**：
- 完整数学推导证明奇偶情况的选取策略
- 通过最大公约数定理分析互质关系
- 代码处理了n为偶数时两种情况的比较

**核心代码**：
```pascal
if n mod 2=1 then
  writeln(n*(n-1)*(n-2))
else
  max := max((n-1)*(n-2)*(n-3), n*(n-1)*(n-3))
```

### 题解2：alan1118（5星）
**关键亮点**：
- 极简代码直接判断6的倍数情况
- 利用奇偶分治策略实现O(1)复杂度
- 特殊处理n为6的倍数时的边界条件

**核心代码**：
```cpp
if(n%2){
    cout << n*(n-1)*(n-2);
} else {
    if(n%6) cout << n*(n-1)*(n-3);
    else cout << (n-1)*(n-2)*(n-3);
}
```

---

## 关键思路总结

1. **奇偶分治**：奇数取连续三数，偶数需特殊处理
2. **6的倍数判断**：避免公因子3对结果的影响
3. **互质优先**：确保选取的数两两之间尽量互质
4. **边界处理**：n<3时直接返回，避免计算错误

---

## 相似题目推荐

1. P1887 - 乘积最大（数论优化）
2. P2651 - 添加括号III（公约数应用）
3. P1072 - Hankson的趣味题（LCM与GCD综合应用）

---
处理用时：115.58秒