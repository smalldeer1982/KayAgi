# 题目信息

# Taxes

## 题目描述

Mr. Funt now lives in a country with a very specific tax laws. The total income of mr. Funt during this year is equal to $ n $ ( $ n>=2 $ ) burles and the amount of tax he has to pay is calculated as the maximum divisor of $ n $ (not equal to $ n $ , of course). For example, if $ n=6 $ then Funt has to pay $ 3 $ burles, while for $ n=25 $ he needs to pay $ 5 $ and if $ n=2 $ he pays only $ 1 $ burle.

As mr. Funt is a very opportunistic person he wants to cheat a bit. In particular, he wants to split the initial $ n $ in several parts $ n_{1}+n_{2}+...+n_{k}=n $ (here $ k $ is arbitrary, even $ k=1 $ is allowed) and pay the taxes for each part separately. He can't make some part equal to $ 1 $ because it will reveal him. So, the condition $ n_{i}>=2 $ should hold for all $ i $ from $ 1 $ to $ k $ .

Ostap Bender wonders, how many money Funt has to pay (i.e. minimal) if he chooses and optimal way to split $ n $ in parts.

## 样例 #1

### 输入

```
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
27
```

### 输出

```
3
```

# AI分析结果

### 题目中文重写
# 税收

## 题目描述
Funt 先生现在生活在一个税收法律非常特殊的国家。Funt 先生今年的总收入为 $n$（$n \geq 2$）伯尔（货币单位），他需要缴纳的税款计算方式为 $n$ 的最大因数（当然，不能等于 $n$ 本身）。例如，如果 $n = 6$，那么 Funt 先生需要缴纳 3 伯尔的税款；而当 $n = 25$ 时，他需要缴纳 5 伯尔；如果 $n = 2$，他只需缴纳 1 伯尔。

由于 Funt 先生是一个非常投机取巧的人，他想稍微作弊一下。具体来说，他想把初始的 $n$ 拆分成几个部分 $n_1 + n_2 + \cdots + n_k = n$（这里 $k$ 是任意的，甚至 $k = 1$ 也是允许的），然后分别为每个部分纳税。他不能让任何一部分等于 1，因为这会暴露他。所以，对于从 1 到 $k$ 的所有 $i$，都应满足条件 $n_i \geq 2$。

Ostap Bender 想知道，如果 Funt 先生选择一种最优的拆分 $n$ 的方式，他最少需要缴纳多少税款。

## 样例 #1
### 输入
```
4
```
### 输出
```
2
```

## 样例 #2
### 输入
```
27
```
### 输出
```
3
```

### 综合分析与结论
这些题解的核心思路均围绕哥德巴赫猜想展开，根据数的性质（质数、偶数、奇数）对 $n$ 进行分类讨论，以确定最少的纳税金额。主要分为以下几种情况：
1. 若 $n$ 是质数，答案为 1。
2. 若 $n$ 是大于 2 的偶数，根据哥德巴赫猜想，可拆成两个质数，答案为 2。
3. 若 $n$ 是奇数且 $n - 2$ 是质数，可拆成 2 和另一个质数，答案为 2。
4. 若以上情况都不满足，可拆成 3 和一个偶数，答案为 3。

算法要点在于质数的判断，多数题解采用遍历 2 到 $\sqrt{n}$ 的方式判断质数，部分题解对该算法进行了优化，如根据数与 6 的余数关系优化，还有题解使用 Miller - Rabin 算法判断大质数。

解决的难点在于如何根据哥德巴赫猜想合理分类讨论，以及选择合适的质数判断算法，以提高效率。

### 所选题解
- **yyyer（4星）**
    - **关键亮点**：思路清晰，对不同情况的分类讨论明确，代码结构清晰，注释详细，采用常规的质数判断方法，易于理解。
    - **个人心得**：无
- **lgnotus（4星）**
    - **关键亮点**：题目简述清晰，对思路的解释详细，代码简洁明了，使用万能头文件和 `long long` 类型，具有一定的通用性。
    - **个人心得**：无
- **SqrtSecond（4星）**
    - **关键亮点**：先给出错误代码并分析原因，再给出正确代码，有助于读者理解易错点，采用快读提高输入效率。
    - **个人心得**：最初代码 WA 后，分析发现即使 $n$ 为奇数且 $n$ 不是质数，也可能分解成 2 与另一个质数的和，从而修正代码。

### 重点代码
```cpp
// yyyer 的代码
bool isprime(int n) {
    if(n < 2) return false;
    for(int i = 2; i * i <= n; i++) if(n % i == 0) return false;
    return true;
}
int main() {
    int n;
    cin >> n;
    if(isprime(n)) cout << "1" << endl; 
    else if(n % 2 == 0) cout << "2" << endl; 
    else if(isprime(n - 2)) cout << "2" << endl; 
    else cout << "3" << endl; 
    return 0;
}

// lgnotus 的代码
bool prime(long long num) {
    for(long long i = 2; i * i <= num; i++) {
        if(num % i == 0) return 0;
    }
    return 1;
}
int main() {
    cin >> n;
    if(prime(n)) cout << 1 << endl;
    else if(n % 2 == 0) cout << 2 << endl;
    else if(prime(n - 2)) cout << 2 << endl;
    else cout << 3 << endl;
    return 0;
}

// SqrtSecond 的 AC 代码
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}
bool prime(int n) {
    int k = sqrt(n);
    for(int i = 2; i <= k; ++i)
        if(n % i == 0) return false;
    return true;
}
int n;
int main() {
    n = read();
    if(prime(n)) {
        printf("1");
        return 0;
    }
    if(n % 2 == 0 || prime(n - 2)) {
        printf("2");
        return 0;
    }
    printf("3");
    return 0;
}
```
### 核心实现思想
这些代码的核心实现思想是先定义一个判断质数的函数，然后在主函数中根据 $n$ 的不同情况进行分类讨论，输出最少的纳税金额。判断质数的函数通过遍历 2 到 $\sqrt{n}$ 的数，检查是否能整除 $n$ 来判断 $n$ 是否为质数。

### 最优关键思路或技巧
- **分类讨论**：根据数的性质（质数、偶数、奇数）进行分类讨论，结合哥德巴赫猜想，确定最少纳税金额。
- **质数判断优化**：判断质数时，只需遍历 2 到 $\sqrt{n}$ 的数，可减少时间复杂度。部分题解根据数与 6 的余数关系进一步优化质数判断算法。

### 可拓展之处
同类型题目可能会涉及更复杂的数论问题，如大质数判断、更复杂的数的拆分问题等。类似算法套路包括利用数学定理（如费马小定理、欧拉定理等）进行数论相关的计算和判断，以及对算法进行优化以提高效率。

### 推荐洛谷题目
1. P1218 [USACO1.5]特殊的质数肋骨 Superprime Rib
2. P1075 质因数分解
3. P1579 哥德巴赫猜想（升级版）

### 个人心得摘录与总结
- **SqrtSecond**：最初代码 WA 后，分析发现即使 $n$ 为奇数且 $n$ 不是质数，也可能分解成 2 与另一个质数的和，从而修正代码。这提醒我们在解题时要考虑全面，对特殊情况进行仔细分析。

---
处理用时：51.43秒