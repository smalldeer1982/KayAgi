# 题目信息

# Petya and His Friends

## 题目描述

Little Petya has a birthday soon. Due this wonderful event, Petya's friends decided to give him sweets. The total number of Petya's friends equals to $ n $ .

Let us remind you the definition of the greatest common divisor: $ GCD(a_{1},...,a_{k})=d $ , where $ d $ represents such a maximal positive number that each $ a_{i} $ ( $ 1<=i<=k $ ) is evenly divisible by $ d $ . At that, we assume that all $ a_{i} $ 's are greater than zero.

Knowing that Petya is keen on programming, his friends has agreed beforehand that the $ 1 $ -st friend gives $ a_{1} $ sweets, the $ 2 $ -nd one gives $ a_{2} $ sweets, ..., the $ n $ -th one gives $ a_{n} $ sweets. At the same time, for any $ i $ and $ j $ ( $ 1<=i,j<=n $ ) they want the $ GCD(a_{i},a_{j}) $ not to be equal to $ 1 $ . However, they also want the following condition to be satisfied: $ GCD(a_{1},a_{2},...,a_{n})=1 $ . One more: all the $ a_{i} $ should be distinct.

Help the friends to choose the suitable numbers $ a_{1},...,a_{n} $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
99
55
11115
```

## 样例 #2

### 输入

```
4
```

### 输出

```
385
360
792
8360
```

# AI分析结果

### 题目中文重写
# 彼佳和他的朋友们

## 题目描述
小彼佳很快就要过生日了。由于这个美好的事件，彼佳的朋友们决定送给他糖果。彼佳的朋友总数为 $n$。

让我们回顾一下最大公约数的定义：$GCD(a_{1},...,a_{k}) = d$，其中 $d$ 表示一个最大的正整数，使得每个 $a_{i}$（$1 \leq i \leq k$）都能被 $d$ 整除。同时，我们假设所有的 $a_{i}$ 都大于零。

已知彼佳热衷于编程，他的朋友们事先约定，第 $1$ 个朋友送 $a_{1}$ 颗糖果，第 $2$ 个朋友送 $a_{2}$ 颗糖果，……，第 $n$ 个朋友送 $a_{n}$ 颗糖果。同时，对于任意的 $i$ 和 $j$（$1 \leq i, j \leq n$），他们希望 $GCD(a_{i}, a_{j})$ 不等于 $1$。然而，他们还希望满足以下条件：$GCD(a_{1}, a_{2},..., a_{n}) = 1$。此外，所有的 $a_{i}$ 都应该不同。

帮助朋友们选择合适的数字 $a_{1},..., a_{n}$。

## 样例 #1
### 输入
```
3
```
### 输出
```
99
55
11115
```

## 样例 #2
### 输入
```
4
```
### 输出
```
385
360
792
8360
```

### 综合分析与结论
这些题解主要围绕构造满足特定条件的数列展开，即构造 $n$ 个数，使任意两数的最大公约数不为 $1$，但所有数的最大公约数为 $1$。不同题解采用了不同的思路和方法，各有优劣。
- **思路对比**
    - 部分题解通过素数构造，如用前 $n$ 个素数的乘积除以其中一个素数得到结果；部分题解则从简单的数对出发，如 $(6, 10)$、$(6, 15)$ 等，再根据这些数的因数关系构造后续的数。
    - 还有题解利用特殊的构造方式，如 $6$ 的幂次结合其他数。
- **算法要点**
    - 素数构造法需要先求出素数，可能涉及高精度计算；简单数对构造法只需进行基本的乘法和循环操作。
    - 特殊构造法可能需要处理高精度，同时要注意数的组合满足条件。
- **解决难点**
    - 最大的难点在于满足所有数两两不互质且整体最大公约数为 $1$ 的条件。
    - 部分题解需要处理高精度计算，以避免数据溢出。

### 所选题解
- **作者：封禁用户（5星）**
    - **关键亮点**：思路清晰，通过欧拉筛求出素数，利用素数乘积构造满足条件的数，虽然使用了高精度，但逻辑严谨。
    - **核心代码**：
```cpp
inline void oula()
{
    for(int i = 2;cnt < 50;++i)
    {
        if(!ip[i]) p[++cnt] = i;
        for(int j = 1;j <= cnt&&i * p[j] <= 300;++j)
        {
            ip[i * p[j]] = 1;
            if(i % p[j] == 0) break;	
        }	
    }
}
//...
for(int i = 1;i <= n;++i)
{
    Num.init();
    for(int j = 1;j <= n;++j)
        if(j!= i)
            Num = Num * p[j];
    Num.print();
}
```
    - **核心实现思想**：先通过欧拉筛求出前 $50$ 个素数，然后对于每个位置 $i$，计算除了第 $i$ 个素数之外的其他素数的乘积，使用高精度存储和输出。

- **作者：Fan_Tuan（4星）**
    - **关键亮点**：思路简洁，从简单的素数组合出发构造满足条件的数，代码实现简单，不涉及高精度。
    - **核心代码**：
```cpp
if (n <= 2)  
    printf("%d\n", -1);  
else  
{  
    printf("%d\n", 6);  
    printf("%d\n", 15);
    for (int i = 1; i <= n-2; i++)  
        printf("%d\n", 10*i);
}
```
    - **核心实现思想**：当 $n \leq 2$ 时无解，当 $n > 2$ 时，先输出 $6$ 和 $15$，然后后续的数为 $10$ 的倍数，这样能保证两两不互质且整体最大公约数为 $1$。

- **作者：youdu666（4星）**
    - **关键亮点**：思路直接，先输出三个最大公约数为 $1$ 的数，再输出它们最小公倍数的倍数，避免了高精度计算。
    - **核心代码**：
```cpp
if(n==2)
{
    printf("-1\n");
    return 0;
}
printf("6\n10\n15\n");
int ans=0;
for(int i=4;i<=n;i++)
{
    ans+=30;
    printf("%d\n",ans);
}
```
    - **核心实现思想**：当 $n = 2$ 时无解，当 $n > 2$ 时，先输出 $6$、$10$、$15$，然后后续的数为 $30$ 的倍数，因为 $6$、$10$、$15$ 的最小公倍数是 $30$，这样能满足条件。

### 最优关键思路或技巧
- 从简单的数对或数的组合出发，如 $(6, 10)$、$(6, 15)$ 等，利用它们的因数关系构造后续的数，避免复杂的计算和高精度处理。
- 先确定满足条件的少数几个数，再通过这些数的最小公倍数或其他倍数关系构造整个数列。

### 可拓展之处
同类型题可能会有不同的约束条件，如要求构造的数在某个范围内，或者对数列的单调性等有要求。类似算法套路可以是先找出满足部分条件的基础数，再根据其他条件进行扩展和调整。

### 推荐洛谷题目
- P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题
- P1147 连续自然数和
- P1414 又是毕业季II

### 个人心得摘录与总结
- **作者：_Weslie_**：作者提到高精度是万恶之源，自己忘了板子所以尽量避免使用，通过找特殊条件和简单数对来构造数列，还尝试打表优化时间复杂度，但实际运行速度却比 $O(n)$ 的代码慢，反映出在实际编程中要综合考虑理论复杂度和实际运行效率。 

---
处理用时：36.53秒