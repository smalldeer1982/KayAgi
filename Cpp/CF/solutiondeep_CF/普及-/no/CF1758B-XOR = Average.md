# 题目信息

# XOR = Average

## 题目描述

You are given an integer $ n $ . Find a sequence of $ n $ integers $ a_1, a_2, \dots, a_n $ such that $ 1 \leq a_i \leq 10^9 $ for all $ i $ and $ $$$a_1 \oplus a_2 \oplus \dots \oplus a_n = \frac{a_1 + a_2 + \dots + a_n}{n}, $ $  where  $ \\oplus$$$ represents the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

It can be proven that there exists a sequence of integers that satisfies all the conditions above.

## 说明/提示

In the first test case, $ 69 = \frac{69}{1} = 69 $ .

In the second test case, $ 13 \oplus 2 \oplus 8 \oplus 1 = \frac{13 + 2 + 8 + 1}{4} = 6 $ .

## 样例 #1

### 输入

```
3
1
4
3```

### 输出

```
69
13 2 8 1
7 7 7```

# AI分析结果

### 题目内容
# XOR = Average
## 题目描述
给定一个整数 $n$ 。找到一个由 $n$ 个整数 $a_1, a_2, \dots, a_n$ 组成的序列，使得对于所有的 $i$ 都有 $1 \leq a_i \leq 10^9$ ，并且 $a_1 \oplus a_2 \oplus \dots \oplus a_n = \frac{a_1 + a_2 + \dots + a_n}{n}$ ，其中 $\oplus$ 表示[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) 。
可以证明存在满足上述所有条件的整数序列。
## 说明/提示
在第一个测试用例中，$69 = \frac{69}{1} = 69$ 。
在第二个测试用例中，$13 \oplus 2 \oplus 8 \oplus 1 = \frac{13 + 2 + 8 + 1}{4} = 6$ 。
## 样例 #1
### 输入
```
3
1
4
3
```
### 输出
```
69
13 2 8 1
7 7 7
```
### 算法分类
构造
### 综合分析与结论
这些题解的核心思路都是基于对 $n$ 的奇偶性进行分类讨论来构造满足条件的序列。
 - **思路**：利用异或运算的性质 $a \oplus a = 0$ 和 $a \oplus 0 = a$ 。当 $n$ 为奇数时，构造一个所有元素都相同的序列，这样异或和等于平均值；当 $n$ 为偶数时，先找到一组特殊解（如 $1,3$ ），再通过补充若干个特定值（如 $2$ ）来保证异或和与平均值相等。
 - **算法要点**：根据 $n$ 的奇偶性分别处理，奇数情况较为直接，偶数情况需找到合适的特殊值组合。
 - **解决难点**：主要难点在于找到偶数情况下满足异或和等于平均值的数的组合，通过从小数据入手尝试，发现合适的组合方式。
### 所选的题解
 - **作者：aCssen (5星)**
    - **关键亮点**：思路清晰，详细阐述了根据 $n$ 奇偶性分类讨论的依据和过程，从异或性质出发逐步推导构造方法，代码实现规范，还包含了自定义的读入优化函数。
    - **重点代码**：
```cpp
if(n&1){//n为奇数
    for(int i=1;i<=n;i++) printf("1 ");
    printf("\n");
    continue;
}
//偶数
for(int i=1;i<=n-2;i++) printf("2 ");
printf("1 3\n");
```
核心实现思想：根据 $n$ 的奇偶性，奇数时输出 $n$ 个 $1$ ，偶数时先输出 $n - 2$ 个 $2$ ，再输出 $1,3$ 。
 - **作者：Clyfort (4星)**
    - **关键亮点**：简洁明了地阐述思路，从 $n$ 为奇数的简单情况入手，自然过渡到 $n$ 为偶数时在奇数解基础上的修改，代码简洁易懂。
    - **重点代码**：
```cpp
if (n % 2)
{
    for (int i = 1; i <= n; i ++)
        cout << 1 << " ";
    cout << endl;
}
else
{
    cout << 1 << " ";
    for (int i = 2; i <= n - 1; i ++)
        cout << 2 << " ";
    cout << 3;
    cout << endl;
}
```
核心实现思想：同样依据 $n$ 奇偶性，奇数输出 $n$ 个 $1$ ，偶数先输出 $1$ ，再输出 $n - 2$ 个 $2$ ，最后输出 $3$ 。
 - **作者：what_can_I_do (4星)**
    - **关键亮点**：采用凑 $0$ 法的表述，从原理上解释了构造思路，对偶数情况的构造解释详细，代码实现简洁。
    - **重点代码**：
```cpp
if(n%2==1) for(register int i=1;i<=n;i++) printf("%d ",1);
else 
{
    printf("%d ",1);
    for(register int i=2;i<n;i++) printf("%d ",2);
    printf("%d",3);
}
```
核心实现思想：根据 $n$ 奇偶性，奇数全输出 $1$ ，偶数先输出 $1$ ，接着输出 $n - 2$ 个 $2$ ，最后输出 $3$ 。
### 最优关键思路或技巧
利用异或运算的基本性质，通过对 $n$ 奇偶性分类讨论来构造序列。奇数情况利用相同数异或的特点，偶数情况通过寻找特殊值组合并结合若干相同值来满足条件。
### 拓展
同类型题通常围绕特定运算性质构造满足等式或不等式的序列。类似算法套路是先分析运算性质，再根据关键参数（如本题的 $n$ ）的不同情况进行构造尝试，从小数据入手找规律。
### 洛谷题目推荐
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149) ：通过枚举和构造来解决火柴棒拼等式的问题，涉及数字与火柴棒数量的对应关系构造。
 - [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678) ：利用二分查找和构造来确定满足条件的最小距离，需要构造检查函数。
 - [P1464 Function](https://www.luogu.com.cn/problem/P1464) ：通过分析函数性质，构造递归或递推关系来求解函数值。 

---
处理用时：43.47秒