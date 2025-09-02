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

### 题目内容
# Shohag Loves XOR（困难版本）

## 题目描述
这是该问题的困难版本。两个版本之间的差异以**粗体**突出显示。只有当两个版本的问题都被解决时，你才能进行攻击（hacks）。

Shohag 有两个整数 $x$ 和 $m$ 。帮助他计算满足 $1 \le y \le m$ 且 $x \oplus y$ 能被 $x$ 、$y$ 或者两者整除的整数 $y$ 的数量。这里 $\oplus$ 是[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)运算符。

$^{\text{∗}}$ 若存在整数 $c$ 使得 $a = b \cdot c$，则称数 $a$ 能被数 $b$ 整除。

## 说明/提示
在第一个测试用例中，对于 $x = 7$ ，在从 $1$ 到 $m = 10$ 的整数中，有 $3$ 个 $y$ 的有效值，它们是 $1$ 、$7$ 和 $9$ 。
- $y = 1$ 是有效的，因为 $x \oplus y = 7 \oplus 1 = 6$ 且 $6$ 能被 $y = 1$ 整除。
- $y = 7$ 是有效的，因为 $x \oplus y = 7 \oplus 7 = 0$ 且 $0$ 能被 $x = 7$ 和 $y = 7$ 整除。
- $y = 9$ 是有效的，因为 $x \oplus y = 7 \oplus 9 = 14$ 且 $14$ 能被 $x = 7$ 整除。

## 样例 #1
### 输入
```
5
7 10
2 3
6 4
1 6
4 1
```
### 输出
```
3
2
2
6
1
```

### 综合分析与结论
这些题解的核心思路大多围绕分类讨论与优化枚举。主要难点在于如何优化暴力枚举以满足时间复杂度要求。
1. **littlebug**：先找到 $x$ 最高二进制位上一位为 $1$ 其余位为 $0$ 组成的数 $t$，认为 $y \geq t$ 时，$y ~|~ x \oplus y$ 不可能成立，从而缩小枚举范围。对于 $\geq t$ 的部分，利用二分查找满足 $x \oplus y$ 为 $x$ 倍数的 $y$，但因单调性不优，通过检查前后部分数据来确保正确性。
2. **Limerency**：记 $p = x\oplus y$，通过分类讨论 $y$ 与 $x$ 的大小关系来统计 $p$ 的个数。$y < x$ 时暴力枚举；$x = y$ 时答案加 $1$；$x > y$ 时，统计 $x$ 的倍数作为合法 $p$ 的个数，并特判边界情况。
3. **LiJoQiao**：分类讨论 $x\oplus y \mid x$ 和 $x\oplus y \mid y$ 两种情况。对于 $x\oplus y \mid x$，通过等式变形确定 $y$ 的取值范围并统计符合条件的 $i$ 的数量，同时特判边界；对于 $x\oplus y \mid y$，$y<x$ 时枚举统计，$y\geq x$ 时通过分析等式排除一些情况。最后去重处理两种情况的重复部分。
4. **Enoch006**：将答案拆成 $x|x\oplus y + y|x\oplus y - [x,y]|x\oplus y$ 三部分。处理 $x|x\oplus y$ 时，根据异或性质确定 $k$ 的范围，部分暴力判断；处理 $y|x\oplus y$ 时，因 $y\oplus ky\geq y$，当 $y>x$ 时不合法，直接暴力枚举 $y$ 判断；处理 $[x,y]|x\oplus y$ 时，在处理 $y|x\oplus y$ 时顺便判断。
5. **I_will_AKIOI**：通过暴力枚举发现从 $y=x$ 开始，相邻两个 $y$ 之间的差会出现循环，循环节长度为 $2^{\lfloor\log_2 x\rfloor}$。先暴力枚举 $y<x$ 的部分，再对循环部分利用循环节计算，最后处理可能不完整的循环节。
6. **OIer_Hhy**：把条件拆成 $x \mid x \oplus y$ 和 $y \mid x \oplus y$ 。对于 $x \mid x \oplus y$，打表得出 $x \le y \le x \times (2^k + 1)(k=\lceil\log_2 x\rceil)$，枚举 $ix$ 统计；对于 $y \mid x \oplus y$，打表得出 $1 \le y < x$，直接枚举。
7. **wfc284**：令 $x \leq y$，分 $y|x \oplus y$ 和 $x|x\oplus y$ 两类。$y|x \oplus y$ 时推出 $x = 0$ 舍去；$x|x\oplus y$ 时设 $x \oplus y = kx$ 确定 $k$ 的必要条件。将可能的 $y$ 按与 $x$ 的大小关系分成两部分，小于等于 $x$ 的直接枚举判定，大于 $x$ 的枚举最后 $10^4$ 个 $k$ 判定，其他默认成立。
8. **Dangerise**：从二进制角度分析，发现当 $y\geq 2^k$（$k$ 为 $x$ 的二进制位数），$x \oplus y$ 不可能是 $y$ 的倍数。利用异或性质对 $y$ 分段处理，类似数位 DP，固定 $y$ 某些位，让其他位任取统计贡献，最后容斥处理 $x$ 与 $y$ 答案交集。
9. **SUNCHAOYI**：设 $p = x \oplus y$，分 $x | p$、$y | p$、$x | p$ 且 $y | p$ 三种情况讨论。$x | p$ 时，根据 $y = x \oplus p \le p + x \le m$ 确定 $k$ 的范围，循环判断特定区间；$y | p$ 时，当 $0 < x < y$ 不存在 $p = ky(k \geq 2)$ 的解，只考虑 $y \le x$ 的情况；$x | p$ 且 $y | p$ 时，只有 $x = y$ 成立。
10. **sbno333**：考虑 $y>2x$ 时，$x\oplus y$ 二进制最高位和 $y$ 的一样，不为 $y$ 的倍数。先枚举 $y\le 2x$，再枚举 $x\oplus y$ 的合法结果，将 $kx$ 拆分处理，根据取值范围判断是否需要枚举。

整体来看，各题解都有一定的优化思路，但在代码可读性、思路清晰度和优化程度上有所差异，没有题解达到4星及以上。

### 通用建议与扩展思路
1. **通用建议**：对于此类涉及异或运算和整除关系的题目，深入理解异或运算的性质（如不进位加法、不借位减法，$|x - y| \leq x\oplus y \leq x + y$ 等）是关键。在优化枚举时，可以从数据范围出发，结合数学推导来缩小枚举范围，同时利用单调性、周期性等特性进一步优化。在代码实现上，注意边界条件的处理和代码的可读性。
2. **扩展思路**：同类型题可能会改变限制条件，如改变整除关系或者异或运算的对象，或者增加更多的条件限制。类似的算法套路包括利用位运算的性质进行分析，通过分类讨论简化问题，以及利用数学推导优化暴力枚举。例如，对于一些与二进制相关的计数问题，常常可以从二进制位的角度出发，分析每一位的变化对结果的影响；对于涉及倍数关系的问题，通过设倍数关系的等式，推导取值范围来优化算法。

### 洛谷相似题目推荐
1. **P1552 跳跳棋**：涉及位运算和数学推导，通过分析棋子位置的变化规律，利用位运算优化计算过程，与本题利用异或运算性质优化算法有相似之处。
2. **P1469 找筷子**：主要考查位运算中的异或运算特性，通过异或运算找出数组中出现奇数次的数，与本题对异或运算的运用都基于其特性展开。
3. **P2141 珠心算测验**：同样涉及位运算和计数问题，通过对数字进行按位分析，统计满足特定条件的数字对数，与本题在利用位运算解决计数问题上思路类似。 

---
处理用时：47.35秒