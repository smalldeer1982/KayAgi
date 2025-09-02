# 题目信息

# Expression Evaluation Error

## 题目描述

On the board, Bob wrote $ n $ positive integers in [base](https://en.wikipedia.org/wiki/Positional_notation#Base_of_the_numeral_system) $ 10 $ with sum $ s $ (i. e. in decimal numeral system). Alice sees the board, but accidentally interprets the numbers on the board as base- $ 11 $ integers and adds them up (in base $ 11 $ ).

What numbers should Bob write on the board, so Alice's sum is as large as possible?

## 说明/提示

In the first test case, $ 70_{10} + 27_{10} = 97_{10} $ , and Alice's sum is $ $$$70_{11} + 27_{11} = 97_{11} = 9 \cdot 11 + 7 = 106_{10}. $ $  (Here  $ x\_b $  represents the number  $ x $  in base  $ b $ .) It can be shown that it is impossible for Alice to get a larger sum than  $ 106\_{10} $ .</p><p>In the second test case, Bob can only write a single number on the board, so he must write  $ 17 $ .</p><p>In the third test case,  $ 3\_{10} + 4\_{10} + 100\_{10} + 4\_{10} = 111\_{10} $ , and Alice's sum is  $ $ 3_{11} + 4_{11} + 100_{11} + 4_{11} = 110_{11} = 1 \cdot 11^2 + 1 \cdot 11 = 132_{10}. $ $  It can be shown that it is impossible for Alice to get a larger sum than  $ 132\_{10}$$$.

## 样例 #1

### 输入

```
6
97 2
17 1
111 4
100 2
10 9
999999 3```

### 输出

```
70 27 
17 
3 4 100 4
10 90
1 1 2 1 1 1 1 1 1 
999900 90 9```

# AI分析结果

### 题目内容中文重写
# 表达式求值错误

## 题目描述
在黑板上，鲍勃写下了 $n$ 个十进制的正整数，它们的和为 $s$。爱丽丝看到了黑板，但不小心将黑板上的数字当作十一进制的整数，并将它们相加（在十一进制下）。

鲍勃应该在黑板上写下哪些数字，才能使爱丽丝得到的和尽可能大？

## 说明/提示
在第一个测试用例中，$70_{10} + 27_{10} = 97_{10}$，而爱丽丝计算的和是 $70_{11} + 27_{11} = 97_{11} = 9 \cdot 11 + 7 = 106_{10}$。（这里 $x_b$ 表示 $x$ 在 $b$ 进制下的表示。）可以证明，爱丽丝不可能得到比 $106_{10}$ 更大的和。

在第二个测试用例中，鲍勃只能在黑板上写一个数字，所以他必须写 $17$。

在第三个测试用例中，$3_{10} + 4_{10} + 100_{10} + 4_{10} = 111_{10}$，爱丽丝计算的和是 $3_{11} + 4_{11} + 100_{11} + 4_{11} = 110_{11} = 1 \cdot 11^2 + 1 \cdot 11 = 132_{10}$。可以证明，爱丽丝不可能得到比 $132_{10}$ 更大的和。

## 样例 #1

### 输入
```
6
97 2
17 1
111 4
100 2
10 9
999999 3
```

### 输出
```
70 27 
17 
3 4 100 4
10 90
1 1 2 1 1 1 1 1 1 
999900 90 9
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，要使爱丽丝在十一进制下的求和结果最大，就需要尽量避免在十一进制加法中产生进位。因为在十进制下产生进位，在十一进制下会导致结果变小。

各题解的思路和实现方式略有不同：
- 清烛的题解直接从最高位往最低位依次划分，每次取最大的 $10$ 的幂，直到划分出 $n$ 个数。
- dottle 的题解先分析出最大结果不超过 $s$ 看成十一进制的结果，然后分情况讨论，若各位数字和大于等于 $n$ 则直接划分，否则从低位往高位拆分。
- XL4453 的题解与 dottle 类似，先判断各位数字和与 $n$ 的大小关系，再进行相应的划分。
- wmrqwq 的题解强调每次将尽可能多的数分到最高的数位上，前 $n - 1$ 个数取最大的能分的 $10$ 的非负整数次幂，最后一个数取剩余的。
- DaiRuiChen007 的题解先将 $S$ 的每个位拆成若干个 $10^k$，若覆盖的数不足 $n$ 个，就从低位开始拆分，时间复杂度为 $\Theta(n^2\log n)$。

### 题解评分
- 清烛：4星。思路清晰，代码简洁，直接实现了贪心策略。
- dottle：3星。思路正确，但没有给出代码实现。
- XL4453：3星。代码实现了思路，但代码结构稍显复杂。
- wmrqwq：3星。思路和代码都比较清晰，但使用了较多的宏定义，可能会影响代码的可读性。
- DaiRuiChen007：3星。思路和代码都有，但时间复杂度较高。

### 所选题解
- 清烛：4星。关键亮点在于代码简洁，直接从最高位往最低位依次划分，实现了贪心策略。

### 重点代码
```cpp
int main() {
    int T; read(T);
    while (T--) {
        int s, n, p; read(s), read(n);
        while (n--) {
            if (!n) print(s), putchar('\n');
            else print(p = pow(10, (int)log10(s - n))), putchar(' ');
            s -= p;
        }
    }
    return output(), 0;
}
```
**核心实现思想**：通过 `pow(10, (int)log10(s - n))` 来获取当前能取到的最大的 $10$ 的幂，将其作为一个划分的数，然后更新 $s$ 的值，直到划分出 $n$ 个数。

### 关键思路或技巧
- 贪心策略：尽量避免在十一进制加法中产生进位，优先划分高位的数。
- 从最高位往最低位依次划分，保证高位的数尽可能大。

### 拓展思路
同类型题或类似算法套路：在其他进制相关的构造问题中，也可以考虑贪心策略，通过分析进位对结果的影响来确定最优的构造方案。例如，在不同进制下的数字拆分、组合问题中，都可以尝试这种思路。

### 推荐题目
- [P1015 回文数](https://www.luogu.com.cn/problem/P1015)
- [P1143 进制转换](https://www.luogu.com.cn/problem/P1143)
- [P1604 B进制星球](https://www.luogu.com.cn/problem/P1604)

### 个人心得
这些题解中没有包含个人心得内容。

---
处理用时：82.25秒