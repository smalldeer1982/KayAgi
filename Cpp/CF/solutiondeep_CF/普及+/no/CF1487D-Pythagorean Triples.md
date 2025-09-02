# 题目信息

# Pythagorean Triples

## 题目描述

A Pythagorean triple is a triple of integer numbers $ (a, b, c) $ such that it is possible to form a right triangle with the lengths of the first cathetus, the second cathetus and the hypotenuse equal to $ a $ , $ b $ and $ c $ , respectively. An example of the Pythagorean triple is $ (3, 4, 5) $ .

Vasya studies the properties of right triangles, and he uses a formula that determines if some triple of integers is Pythagorean. Unfortunately, he has forgotten the exact formula; he remembers only that the formula was some equation with squares. So, he came up with the following formula: $ c = a^2 - b $ .

Obviously, this is not the right formula to check if a triple of numbers is Pythagorean. But, to Vasya's surprise, it actually worked on the triple $ (3, 4, 5) $ : $ 5 = 3^2 - 4 $ , so, according to Vasya's formula, it is a Pythagorean triple.

When Vasya found the right formula (and understood that his formula is wrong), he wondered: how many are there triples of integers $ (a, b, c) $ with $ 1 \le a \le b \le c \le n $ such that they are Pythagorean both according to his formula and the real definition? He asked you to count these triples.

## 说明/提示

The only Pythagorean triple satisfying $ c = a^2 - b $ with $ 1 \le a \le b \le c \le 9 $ is $ (3, 4, 5) $ ; that's why the answer for $ n = 3 $ is $ 0 $ , and the answer for $ n = 6 $ (and for $ n = 9 $ ) is $ 1 $ .

## 样例 #1

### 输入

```
3
3
6
9```

### 输出

```
0
1
1```

# AI分析结果

### 题目中文重写
# 勾股数

## 题目描述
勾股数是一组整数 $(a, b, c)$，使得以长度分别为 $a$、$b$ 和 $c$ 的边可以构成一个直角三角形，其中 $a$、$b$ 为直角边，$c$ 为斜边。例如，$(3, 4, 5)$ 就是一组勾股数。

瓦西亚正在研究直角三角形的性质，他使用一个公式来判断一组整数是否为勾股数。不幸的是，他忘记了确切的公式，只记得这个公式涉及平方运算。于是，他想出了以下公式：$c = a^2 - b$。

显然，这不是判断一组数是否为勾股数的正确公式。但令瓦西亚惊讶的是，这个公式在 $(3, 4, 5)$ 这组数据上居然成立：$5 = 3^2 - 4$，所以根据瓦西亚的公式，这是一组勾股数。

当瓦西亚找到正确的公式（并意识到自己的公式是错误的）后，他想知道：有多少组整数 $(a, b, c)$ 满足 $1 \le a \le b \le c \le n$，且根据他的公式和真正的定义，它们都是勾股数？他请你计算这些三元组的数量。

## 说明/提示
满足 $c = a^2 - b$ 且 $1 \le a \le b \le c \le 9$ 的唯一勾股数是 $(3, 4, 5)$；这就是为什么当 $n = 3$ 时答案是 $0$，而当 $n = 6$（和 $n = 9$）时答案是 $1$。

## 样例 #1

### 输入
```
3
3
6
9
```

### 输出
```
0
1
1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过联立题目所给的两个方程 $a^2 + b^2 = c^2$ 和 $c = a^2 - b$，经过一系列数学推导得出 $a$、$b$、$c$ 之间的关系，进而根据 $1 \le a \le b \le c \le n$ 的条件确定满足条件的 $a$ 的取值范围，最终计算出满足条件的三元组 $(a, b, c)$ 的数量。

不同题解的推导过程略有不同，但最终都得到了相同或相似的结果。部分题解在推导过程中更加详细，解释了每一步的依据，而有些题解则相对简洁。在代码实现上，大部分题解的时间复杂度都是 $O(T)$，其中 $T$ 是输入的测试数据组数。

### 所选题解
- **Kobe303（5星）**
    - **关键亮点**：思路清晰，详细解释了每一步的推导过程，包括使用平方差公式、判断 $a$ 的奇偶性等，代码可读性高，有快读优化。
- **John_Smith（4星）**
    - **关键亮点**：推导过程简洁明了，对每一步的变形都有说明，关键代码简洁。
- **绝顶我为峰（4星）**
    - **关键亮点**：纯数学做法，对不等式的求解和奇数的判断有详细说明，代码实现简洁。

### 重点代码
#### Kobe303
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define reg register 
#define il inline
int T, n;
il int qrint()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        s = (s << 1) + (s << 3) + (ch ^ 48);
        ch = getchar();
    }
    return s * f;
}
int main()
{
    T = qrint();
    while(T--)
    {
        n = qrint();
        int ans = (sqrt(2 * n - 1) - 1) / 2;
        printf("%d\n", ans);
    }
    return 0;
}
```
**核心实现思想**：通过快读读取输入的测试数据组数 $T$ 和 $n$，根据推导得出的公式 `(sqrt(2 * n - 1) - 1) / 2` 计算满足条件的三元组数量并输出。

#### John_Smith
```cpp
long long n;cin>>n;
cout<<((int)sqrt(2*n-1)-1)/2<<endl;
```
**核心实现思想**：读取输入的 $n$，直接使用公式 `((int)sqrt(2*n-1)-1)/2` 计算并输出结果。

#### 绝顶我为峰
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
long long t,n;
int main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);
        printf("%lld\n",((long long)(sqrt((n<<1)-1))-1)>>1);
    }
    return 0;
}
```
**核心实现思想**：使用 `scanf` 读取输入的测试数据组数 $t$ 和 $n$，根据公式 `((long long)(sqrt((n<<1)-1))-1)>>1` 计算结果并使用 `printf` 输出。

### 最优关键思路或技巧
- **数学推导**：通过联立方程，利用平方差公式等数学知识，将三元二次方程转化为简单的关系，如 $c = b + 1$ 和 $a^2 = 2b + 1$，从而简化问题。
- **范围判断**：根据 $1 \le a \le b \le c \le n$ 的条件，确定 $a$ 的取值范围，进而计算满足条件的 $a$ 的数量。

### 拓展思路
同类型题可能会给出不同的方程或条件，要求找出满足特定条件的整数解的数量。解题的关键仍然是通过数学推导找出变量之间的关系，再根据条件确定取值范围。类似的算法套路包括联立方程、化简方程、利用不等式求解等。

### 推荐洛谷题目
- P1045 [NOIP2003 普及组] 麦森数
- P1069 [NOIP2009 普及组] 细胞分裂
- P1072 [NOIP2009 提高组] Hankson 的趣味题

### 个人心得摘录与总结
部分题解作者提到打表找规律，这是一种在遇到复杂问题时可以尝试的方法，通过观察数据的规律来推测可能的解法。同时，一些作者感谢同机房大佬教自己 markdown 语法，说明在学习过程中交流和互相帮助的重要性。

---
处理用时：47.28秒