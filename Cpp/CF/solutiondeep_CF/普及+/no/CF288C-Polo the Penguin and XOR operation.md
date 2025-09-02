# 题目信息

# Polo the Penguin and XOR operation

## 题目描述

Little penguin Polo likes permutations. But most of all he likes permutations of integers from $ 0 $ to $ n $ , inclusive.

For permutation $ p=p_{0},p_{1},...,p_{n} $ , Polo has defined its beauty — number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF288C/6024047c9c91de0156ffb9e5c8b6ac649d55fe1e.png).

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF288C/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying the operation of bitwise excluding "OR" to numbers $ x $ and $ y $ . This operation exists in all modern programming languages, for example, in language C++ and Java it is represented as "^" and in Pascal — as "xor".

Help him find among all permutations of integers from $ 0 $ to $ n $ the permutation with the maximum beauty.

## 样例 #1

### 输入

```
4
```

### 输出

```
20
0 2 1 4 3
```

# AI分析结果

### 题目内容
# 企鹅波罗与异或运算

## 题目描述
小企鹅波罗喜欢排列。但他最喜欢的是从0到n（包含0和n）的整数的排列。

对于排列 $p = p_{0}, p_{1},..., p_{n}$，波罗定义了它的“美观度”——数字 $\sum_{i = 0}^{n}(i \otimes p_{i})$。

表达式 $x \otimes y$ 表示对数字 $x$ 和 $y$ 进行按位异或运算。这个运算在所有现代编程语言中都存在，例如，在C++ 和Java 语言中用“^”表示，在Pascal 中用“xor”表示。

帮助他在从0到n的整数的所有排列中找到美观度最大的排列。

## 样例 #1
### 输入
```
4
```
### 输出
```
20
0 2 1 4 3
```

### 算法分类
数学

### 综合分析与结论
两题解思路本质相似，均基于异或运算性质及数字二进制表示来解决问题。都发现让进行异或的两个数二进制位上的0和1错开能使结果最大，且都得出答案为 $n(n + 1)$ 这一结论。题解“ztxtjz”通过代码具体实现了如何构造满足条件的排列，而“AC_love”未给出具体代码，只是描述了思路及通过爆搜找规律的过程。

### 所选的题解
- **作者：ztxtjz (5星)**
  - **关键亮点**：思路清晰，不仅给出数学结论，还通过代码实现了如何构造出美观度最大的排列，时间复杂度优化到 $O(n)$。
  - **重点代码核心实现思想**：通过循环遍历从 $n$ 到 $0$ 的数 $i$，计算 $i$ 的二进制位数 $t$，得到对应全为1的二进制数 $k$，然后让 $i$ 与 $k$ 异或得到 $ans[i]$ 以及 $ans[k \otimes i]$，最终输出美观度最大值 $n(n + 1)$ 以及构造的排列。
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,ans[1000005];
int main()
{
    scanf("%lld",&n);
    memset(ans,-1,sizeof(ans));
    for(int i=n;i>=0;i--)
    {
        if(ans[i]!=-1) continue;
        ll k=(1<<(ll)(log2(i)+1))-1;
        ans[k^i]=i,ans[i]=k^i;
    }
    printf("%lld\n",n*(n+1));
    for(int i=0;i<=n;i++) printf("%lld ",ans[i]);
    return 0;
}
```
- **作者：AC_love (4星)**
  - **关键亮点**：通过对较小的 $n$ 进行爆搜找规律，快速得出答案公式为 $n(n + 1)$，并阐述了构造答案的核心思路。
  - **重点代码核心实现思想**：无具体代码，但思路上是让进行异或的两个数二进制位上的0和1错开，例如让一个数异或上一串1。

### 最优关键思路或技巧
利用异或运算性质，通过对数字二进制表示的分析，找到让异或结果每位都为1从而使总和最大的构造方法，即让两个数二进制位上的0和1错开，通过计算每个数二进制位数构造出全1二进制数与之异或。

### 可拓展之处
同类型题或类似算法套路：此类题目通常围绕位运算性质展开，可拓展到其他位运算操作（如按位与、按位或等）与排列组合结合的问题，或对特定二进制位操作的题目。

### 洛谷相似题目推荐
- P1514 引水入城，考察位运算及逻辑推理。
- P1876 开灯，涉及位运算及简单的逻辑分析。
- P2141 珠心算测验，同样需要利用位运算来解决计数问题。 

---
处理用时：38.47秒