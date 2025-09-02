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
# Shohag Loves XOR (Hard Version)

## 题目描述
这是该问题的困难版本。两个版本之间的差异以**粗体**突出显示。只有当两个版本的问题都被解决时，你才能进行攻击（hacks）。

Shohag 有两个整数 \(x\) 和 \(m\)。帮助他计算满足 \(1 \leq y \leq m\) 且 \(x \oplus y\) 能被 \(x\)、\(y\) 或两者整除的整数 \(y\) 的数量。这里 \(\oplus\) 是[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)运算符。

\(^{\text{∗}}\) 数 \(a\) 能被数 \(b\) 整除，当且仅当存在整数 \(c\) 使得 \(a = b \cdot c\)。

## 说明/提示
在第一个测试用例中，对于 \(x = 7\)，在 \(1\) 到 \(m = 10\) 的整数中，有 \(3\) 个有效的 \(y\) 值，它们是 \(1\)、\(7\) 和 \(9\)。
 - \(y = 1\) 是有效的，因为 \(x \oplus y = 7 \oplus 1 = 6\)，且 \(6\) 能被 \(y = 1\) 整除。
 - \(y = 7\) 是有效的，因为 \(x \oplus y = 7 \oplus 7 = 0\)，且 \(0\) 能被 \(x = 7\) 和 \(y = 7\) 整除。
 - \(y = 9\) 是有效的，因为 \(x \oplus y = 7 \oplus 9 = 14\)，且 \(14\) 能被 \(x = 7\) 整除。

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
1. **思路方面**：
    - 多数题解采用分类讨论的方式，主要围绕 \(x\) 与 \(y\) 的大小关系，以及 \(x \oplus y\) 分别对 \(x\) 和 \(y\) 的整除情况进行分析。如当 \(y < x\) 时，常采用暴力枚举判断 \(x \oplus y\) 能否被 \(y\) 整除；当 \(y \geq x\) 时，分析 \(x \oplus y\) 被 \(x\) 整除的情况。
    - 部分题解利用异或的性质，如 \(|x - y| \leq x \oplus y \leq x + y\)，来确定 \(y\) 的取值范围或合法性。
    - 还有题解通过打表找规律，发现 \(y\) 的某些取值规律，如循环节等，从而优化计算。
2. **算法要点**：
    - 暴力枚举：对于较小范围的 \(y\)（如 \(y \leq x\) 或 \(y \leq 2x\) 等），直接枚举判断 \(x \oplus y\) 对 \(x\) 和 \(y\) 的整除性。
    - 数学推导：根据异或性质和整除关系，推导出 \(y\) 或相关倍数 \(k\) 的取值范围，进而计算满足条件的数量。例如，由 \(x \oplus y = kx\) 推出 \(k\) 的范围。
    - 二分查找：利用 \(y\) 取值的某种单调性（虽不完美），通过二分查找确定满足条件的 \(y\) 的数量。
3. **解决难点**：
    - **确定 \(y\) 的有效范围**：通过异或性质和数学推导，确定在不同条件下 \(y\) 的可能取值范围，减少不必要的枚举。
    - **处理边界情况和重复计数**：在分类讨论过程中，准确处理边界值（如 \(y = x\) 等情况），并避免重复统计满足条件的 \(y\)。例如，同时满足 \(x \mid x \oplus y\) 和 \(y \mid x \oplus y\) 的情况可能会被重复计算。

### 通用建议与扩展思路
1. **通用建议**：
    - 对于涉及位运算和整除关系的题目，深入理解位运算（如异或）的性质是关键。可以通过打表、简单示例分析等方式，挖掘隐藏的规律。
    - 分类讨论时要全面且细致，明确每种情况的边界条件，避免遗漏或重复计算。
    - 在优化算法时，注意利用数据范围来选择合适的优化方法，如数据范围小时暴力枚举可能可行，范围大时则需寻找更高效的方法，如利用单调性进行二分查找等。
2. **扩展思路**：
    - **同类型题**：此类题目通常围绕位运算与数论关系展开，例如给定一些数的操作和条件，求满足特定条件的数的个数或具体值。可以拓展到更多复杂的位运算组合，如与、或、非等运算与整除、余数等数论概念结合。
    - **类似算法套路**：在处理这类问题时，分类讨论结合数学推导是常见套路。先根据条件对变量进行合理分类，然后利用相关运算性质进行推导，确定取值范围。若存在单调性，二分查找可优化枚举过程。同时，对于复杂问题，打表找规律也是探索解题方向的有效手段。

### 洛谷相似知识点题目推荐
1. **P1552 [APIO2012]派遣**：涉及到树结构与贪心算法，同时对数论知识有一定要求，与本题类似之处在于需要根据给定条件进行分析和计算，优化求解过程。
2. **P2155 [SDOI2008]沙拉公主的困惑**：主要考查数论中的欧拉函数等知识，与本题类似在于都需要深入理解数论概念，并通过数学推导来解决问题。
3. **P3951 [NOIP2017 提高组] 小凯的疑惑**：属于数论中的不定方程问题，通过对问题的分析和数学性质的运用来求解，与本题一样需要挖掘题目背后的数学规律。 

---
处理用时：26.11秒