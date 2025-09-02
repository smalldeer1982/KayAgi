# 题目信息

# Fortune Telling

## 题目描述

Haha, try to solve this, SelectorUnlimited!

— antontrygubO_o



Your friends Alice and Bob practice fortune telling.

Fortune telling is performed as follows. There is a well-known array $ a $ of $ n $ non-negative integers indexed from $ 1 $ to $ n $ . The tellee starts with some non-negative number $ d $ and performs one of the two operations for each $ i = 1, 2, \ldots, n $ , in the increasing order of $ i $ . The possible operations are:

- replace their current number $ d $ with $ d + a_i $
- replace their current number $ d $ with $ d \oplus a_i $ (hereinafter $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Exclusive_or))

Notice that the chosen operation may be different for different $ i $ and for different tellees.

One time, Alice decided to start with $ d = x $ and Bob started with $ d = x + 3 $ . Each of them performed fortune telling and got a particular number in the end. Notice that the friends chose operations independently of each other, that is, they could apply different operations for the same $ i $ .

You learnt that either Alice or Bob ended up with number $ y $ in the end, but you don't know whose of the two it was. Given the numbers Alice and Bob started with and $ y $ , find out who (Alice or Bob) could get the number $ y $ after performing the operations. It is guaranteed that on the jury tests, exactly one of your friends could have actually gotten that number.

Hacks

You cannot make hacks in this problem.

## 说明/提示

In the first test case, Alice could get $ 9 $ using the following operations: $ 7 + 2 = 9 $ .

In the second test case, Alice could get $ 2 $ using this operations: $ (0 + 1) \oplus 3 = 2 $ .

In the third test case, Bob started with $ x+3 = 0+3=3 $ and could get $ 1 $ this way: $ (((3 + 1) + 2) \oplus 3) \oplus 4 = 1 $ .

## 样例 #1

### 输入

```
4
1 7 9
2
2 0 2
1 3
4 0 1
1 2 3 4
2 1000000000 3000000000
1000000000 1000000000```

### 输出

```
Alice
Alice
Bob
Alice```

# AI分析结果

【题目内容】
# 算命

## 题目描述

Haha, try to solve this, SelectorUnlimited!

— antontrygubO_o

你的朋友 Alice 和 Bob 在练习算命。

算命的规则如下：有一个著名的数组 $a$，包含 $n$ 个非负整数，索引从 $1$ 到 $n$。算命者从一个非负数 $d$ 开始，对每个 $i = 1, 2, \ldots, n$，按 $i$ 的递增顺序执行以下两种操作之一：

- 将当前数 $d$ 替换为 $d + a_i$
- 将当前数 $d$ 替换为 $d \oplus a_i$（其中 $ \oplus $ 表示[按位异或操作](https://en.wikipedia.org/wiki/Exclusive_or)）

注意，对于不同的 $i$ 和不同的算命者，所选择的操作可能不同。

有一次，Alice 决定从 $d = x$ 开始，而 Bob 从 $d = x + 3$ 开始。他们各自进行了算命，并最终得到了一个特定的数字。注意，朋友们选择的操作是相互独立的，即他们可能对相同的 $i$ 应用不同的操作。

你得知 Alice 或 Bob 最终得到了数字 $y$，但不知道是谁。给定 Alice 和 Bob 的起始数字以及 $y$，找出谁（Alice 或 Bob）可能在执行操作后得到数字 $y$。保证在测试数据中，只有一位朋友可能得到该数字。

Hacks

你无法在此问题中进行 hack。

## 说明/提示

在第一个测试用例中，Alice 可以通过以下操作得到 $9$：$7 + 2 = 9$。

在第二个测试用例中，Alice 可以通过以下操作得到 $2$：$(0 + 1) \oplus 3 = 2$。

在第三个测试用例中，Bob 从 $x+3 = 0+3=3$ 开始，可以通过以下操作得到 $1$：$(((3 + 1) + 2) \oplus 3) \oplus 4 = 1$。

## 样例 #1

### 输入

```
4
1 7 9
2
2 0 2
1 3
4 0 1
1 2 3 4
2 1000000000 3000000000
1000000000 1000000000```

### 输出

```
Alice
Alice
Bob
Alice```

【题解分析与结论】
这道题的核心在于利用奇偶性来判断 Alice 和 Bob 谁能通过一系列操作得到目标数 $y$。由于 $x$ 和 $x+3$ 的奇偶性不同，且加法和异或操作对奇偶性的影响相同，因此可以通过对 $x$ 进行一系列操作后，判断其结果的奇偶性是否与 $y$ 的奇偶性相同，来确定谁能得到 $y$。

【评分较高的题解】
1. **作者：Rnfmabj (赞：15)**
   - **星级：5星**
   - **关键亮点：**
     - 利用异或和加法对奇偶性的影响相同的性质，简化了问题。
     - 代码简洁高效，直接通过读入时对 $x$ 进行异或操作，最后判断奇偶性。
   - **代码核心思想：**
     ```cpp
     for(ll i=1;i<=n;i++){
         x^=R&1; // 对 x 进行异或操作
     }
     if(!x^y)cout<<"Alice"<<endl; // 判断奇偶性
     else cout<<"Bob"<<endl;
     ```

2. **作者：8atemak1r (赞：7)**
   - **星级：4星**
   - **关键亮点：**
     - 同样利用加法和异或对奇偶性影响相同的性质，思路清晰。
     - 代码简洁，直接对 $x$ 进行异或操作后判断奇偶性。
   - **代码核心思想：**
     ```cpp
     for(int i = 1; i <= n; ++ i) {
         x ^= tmp; // 对 x 进行异或操作
     }
     if(((x & 1) ^ (y & 1)) == 1) cout << "Bob\n";
     else cout << "Alice\n";
     ```

3. **作者：ttq012 (赞：0)**
   - **星级：4星**
   - **关键亮点：**
     - 通过表格详细解释了异或和加法对奇偶性的影响，帮助理解。
     - 代码简洁，直接对 $x$ 进行加法操作后判断奇偶性。
   - **代码核心思想：**
     ```cpp
     for(int i = 1; i <= n; ++ i) {
         x = (x + tmp) % 2; // 对 x 进行加法操作
     }
     if(x % 2 == y % 2) printf("Alice\n");
     else printf("Bob\n");
     ```

【最优关键思路或技巧】
- **奇偶性判断**：利用加法和异或操作对奇偶性影响相同的性质，简化问题。
- **直接操作**：在读入数据时直接对 $x$ 进行操作，避免额外存储数组，提高效率。

【可拓展之处】
- 类似的问题可以通过分析操作对某些性质（如奇偶性、模数等）的影响来简化问题。
- 可以扩展到其他位运算或模运算相关的问题。

【推荐题目】
1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001) - 基础加法问题。
2. [P1464 Function](https://www.luogu.com.cn/problem/P1464) - 递归与位运算结合的问题。
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886) - 利用滑动窗口和位运算优化问题。

---
处理用时：45.63秒