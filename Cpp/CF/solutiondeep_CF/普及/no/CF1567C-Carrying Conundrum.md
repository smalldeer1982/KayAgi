# 题目信息

# Carrying Conundrum

## 题目描述

Alice has just learned addition. However, she hasn't learned the concept of "carrying" fully — instead of carrying to the next column, she carries to the column two columns to the left.

For example, the regular way to evaluate the sum $ 2039 + 2976 $ would be as shown:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/7f811803128f9de09a9d354d6ba38f6c979516bb.png)However, Alice evaluates it as shown:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/83982f3a368c4bf27357d999f4274a4bb752e11c.png)In particular, this is what she does:

- add $ 9 $ and $ 6 $ to make $ 15 $ , and carry the $ 1 $ to the column two columns to the left, i. e. to the column " $ 0 $ $ 9 $ ";
- add $ 3 $ and $ 7 $ to make $ 10 $ and carry the $ 1 $ to the column two columns to the left, i. e. to the column " $ 2 $ $ 2 $ ";
- add $ 1 $ , $ 0 $ , and $ 9 $ to make $ 10 $ and carry the $ 1 $ to the column two columns to the left, i. e. to the column above the plus sign;
- add $ 1 $ , $ 2 $ and $ 2 $ to make $ 5 $ ;
- add $ 1 $ to make $ 1 $ .

 Thus, she ends up with the incorrect result of $ 15005 $ .Alice comes up to Bob and says that she has added two numbers to get a result of $ n $ . However, Bob knows that Alice adds in her own way. Help Bob find the number of ordered pairs of positive integers such that when Alice adds them, she will get a result of $ n $ . Note that pairs $ (a, b) $ and $ (b, a) $ are considered different if $ a \ne b $ .

## 说明/提示

In the first test case, when Alice evaluates any of the sums $ 1 + 9 $ , $ 2 + 8 $ , $ 3 + 7 $ , $ 4 + 6 $ , $ 5 + 5 $ , $ 6 + 4 $ , $ 7 + 3 $ , $ 8 + 2 $ , or $ 9 + 1 $ , she will get a result of $ 100 $ . The picture below shows how Alice evaluates $ 6 + 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/b16910e4b25eab78326b49caad3574b10b90fef3.png)

## 样例 #1

### 输入

```
5
100
12
8
2021
10000```

### 输出

```
9
4
7
44
99```

# AI分析结果

### 题目内容重写

Alice 刚刚学习了加法。然而，她还没有完全理解“进位”的概念——她不是将进位传递到下一列，而是将进位传递到左边两列的列。

例如，常规的计算 $2039 + 2976$ 的方式如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/7f811803128f9de09a9d354d6ba38f6c979516bb.png)

然而，Alice 的计算方式如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/83982f3a368c4bf27357d999f4274a4bb752e11c.png)

具体来说，她做了以下操作：

- 将 $9$ 和 $6$ 相加得到 $15$，并将 $1$ 进位到左边两列的列，即“$0$ $9$”列；
- 将 $3$ 和 $7$ 相加得到 $10$，并将 $1$ 进位到左边两列的列，即“$2$ $2$”列；
- 将 $1$、$0$ 和 $9$ 相加得到 $10$，并将 $1$ 进位到左边两列的列，即加号上方的列；
- 将 $1$、$2$ 和 $2$ 相加得到 $5$；
- 将 $1$ 相加得到 $1$。

因此，她得到了错误的结果 $15005$。Alice 找到 Bob 并说她将两个数相加得到了 $n$。然而，Bob 知道 Alice 的加法方式。帮助 Bob 找到所有有序正整数对，使得当 Alice 将它们相加时，她会得到 $n$。注意，如果 $a \ne b$，则 $(a, b)$ 和 $(b, a)$ 被认为是不同的。

### 说明/提示

在第一个测试用例中，当 Alice 计算 $1 + 9$、$2 + 8$、$3 + 7$、$4 + 6$、$5 + 5$、$6 + 4$、$7 + 3$、$8 + 2$ 或 $9 + 1$ 时，她会得到 $100$。下图展示了 Alice 如何计算 $6 + 4$：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/b16910e4b25eab78326b49caad3574b10b90fef3.png)

### 样例 #1

#### 输入

```
5
100
12
8
2021
10000
```

#### 输出

```
9
4
7
44
99
```

### 算法分类
数学

### 题解分析与结论

该题的核心在于理解 Alice 的加法规则，即进位是向左两列进行的。通过观察可以发现，奇数位和偶数位的加法是相互独立的，因此可以将问题分解为奇数位和偶数位的两个独立问题。每个问题都可以转化为正常的加法问题，即求两个数的和为给定数的有序正整数对的数量。

### 所选高星题解

#### 题解1：作者：dd_d (赞：13)
**星级：5星**
**关键亮点：**
- 明确指出了奇数位和偶数位的独立性，将问题分解为两个独立的加法问题。
- 通过简单的数学公式 $(x+1) \times (y+1) - 2$ 计算答案，思路清晰且代码简洁。
- 代码实现高效，直接通过字符串处理输入，避免了复杂的数学运算。

**核心代码：**
```cpp
signed main()
{
    T=read();
    while (T--)
    {
        scanf("%s",st+1); n=strlen(st+1);
        num1=num2=0;
        for (int i=1;i<=n;i+=2)
            num1=num1*10+(st[i]^48);
        for (int i=2;i<=n;i+=2)
            num2=num2*10+(st[i]^48);
        writeln((num1+1)*(num2+1)-2);
    }
}
```

#### 题解2：作者：zimujun (赞：7)
**星级：4星**
**关键亮点：**
- 详细解释了奇数位和偶数位的独立性，并通过举例说明了如何将问题分解。
- 提供了对 $o > 0, e > 0$ 和 $\min\{o, e\} = 0$ 两种情况的处理，逻辑严谨。
- 代码实现简洁，直接通过字符串处理输入，避免了复杂的数学运算。

**核心代码：**
```cpp
void solve(){
    string N;
    cin >> N;
    LL odd = 0, even = 0;
    
    for (LL i = 0; i < (LL)N.size(); i += 2){
        odd = odd * 10 + (N[i] ^ 48);
    }
    for (LL i = 1; i < (LL)N.size(); i += 2){
        even = even * 10 + (N[i] ^ 48);
    }
    
    cout << (odd + 1) * (even + 1) - 2 << "\n";
    return ;
}
```

#### 题解3：作者：LaDeX (赞：6)
**星级：4星**
**关键亮点：**
- 通过观察样例，明确指出了奇数位和偶数位的独立性，并将问题分解为两个独立的加法问题。
- 通过简单的数学公式 $(x+1) \times (y+1) - 2$ 计算答案，思路清晰且代码简洁。
- 代码实现高效，直接通过字符串处理输入，避免了复杂的数学运算。

**核心代码：**
```cpp
void solve(){
    string N;
    cin >> N;
    LL odd = 0, even = 0;
    
    for (LL i = 0; i < (LL)N.size(); i += 2){
        odd = odd * 10 + (N[i] ^ 48);
    }
    for (LL i = 1; i < (LL)N.size(); i += 2){
        even = even * 10 + (N[i] ^ 48);
    }
    
    cout << (odd + 1) * (even + 1) - 2 << "\n";
    return ;
}
```

### 最优关键思路或技巧
1. **问题分解**：将奇数位和偶数位的加法问题独立处理，简化了问题的复杂度。
2. **数学公式**：通过 $(x+1) \times (y+1) - 2$ 计算答案，避免了复杂的枚举和计算。
3. **字符串处理**：直接通过字符串处理输入，避免了复杂的数学运算，提高了代码的可读性和效率。

### 可拓展之处
该题的思路可以拓展到其他类似的数学问题，尤其是涉及到进位规则的变种问题。例如，可以设计类似的题目，要求在不同的进位规则下计算两个数的和，或者设计更复杂的进位规则。

### 推荐题目
1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
2. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)

### 个人心得摘录
- **调试经历**：在处理奇数位和偶数位的独立性时，需要特别注意边界情况，例如当奇数位或偶数位为0时的处理。
- **踩坑教训**：在计算答案时，容易忽略 $(x+1) \times (y+1) - 2$ 中的减2操作，导致答案错误。
- **顿悟感想**：通过将问题分解为两个独立的加法问题，大大简化了问题的复杂度，使得解题思路更加清晰。

---
处理用时：55.12秒