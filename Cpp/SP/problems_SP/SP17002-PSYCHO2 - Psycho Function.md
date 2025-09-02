---
title: "PSYCHO2 - Psycho Function"
layout: "post"
diff: 难度0
pid: SP17002
tag: []
---

# PSYCHO2 - Psycho Function

## 题目描述

如果一个数 $N$ 被称为 “Psycho 数”，我们需要对 $N$ 进行质因数分解，得到一系列质数及其幂次。假设这些幂次共有 $M$ 个，我们需要统计这些幂次中偶数和奇数的个数。当偶数幂次的数量严格大于奇数幂次的数量时，$N$ 被称为 “Psycho 数”；否则，称为 “Ordinary 数”。

例如，若 $N = 67500$，它的质因数分解为 $67500 = 2^2 \times 3^3 \times 5^4$。这里有 2 个偶数幂（2 和 4），以及 1 个奇数幂（3）。由于偶数幂的数量（2）大于奇数幂（1），因此 67500 是一个 Psycho 数。

你需要计算以下函数的结果，判断其是 Psycho 数还是 Ordinary 数：

```cpp
bool isPsycho(long long K, long long b, long long p)
{   
    N = numberoftrailingzeros(K!) * lastdigit(b^p); 
    if (N == psychonumber) return true;  
    else return false;
}
```

例如，给定 $k = 10$，$b = 12$，$p = 1$，我们得到 $N = 4$，它是一个 Psycho 数。
- $10! = 3628800$，末尾零的数量为 2。
- $12^1 = 12$，最后一位数字为 2。
- 因此，$N = 4$，且 $4 = 2^2$，偶数幂比奇数幂多，所以 4 是 Psycho 数。

## 输入格式

输入的第一行是一个整数 $T$（表示测试用例数量，$1 \le T \le 10^5$），接下来每行包含三个整数：$K$（$1 \le K \le 4 \times 10^6$），$b$（$0 \le b \le 10^4$），和 $p$（$0 \le p \le 10^{17}$）。

## 输出格式

对于每个测试用例，输出结果为 “Psycho Number” 或 “Ordinary Number”。

## 说明/提示

- $1 \le T \le 10^5$
- $1 \le K \le 4 \times 10^6$
- $0 \le b \le 10^4$
- $0 \le p \le 10^{17}$

**样例输入**
```
2
5 2 5
10 12 1
```

**样例输出**
```
Ordinary Number
Psycho Number
```

**注意：**
- 数字 0 和 1 不是 Psycho 数。

 **本翻译由 AI 自动生成**

