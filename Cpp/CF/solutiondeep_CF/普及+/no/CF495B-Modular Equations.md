# 题目信息

# Modular Equations

## 题目描述

Last week, Hamed learned about a new type of equations in his math class called Modular Equations. Lets define $ i $ modulo $ j $ as the remainder of division of $ i $ by $ j $ and denote it by ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495B/57aaef9d4f53d75c7150d35a36ceb219c08ecb8d.png). A Modular Equation, as Hamed's teacher described, is an equation of the form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495B/bedc8c54f3a5a224f7fdfd3a3301336e4b862b12.png) in which $ a $ and $ b $ are two non-negative integers and $ x $ is a variable. We call a positive integer $ x $ for which ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495B/bedc8c54f3a5a224f7fdfd3a3301336e4b862b12.png) a solution of our equation.

Hamed didn't pay much attention to the class since he was watching a movie. He only managed to understand the definitions of these equations.

Now he wants to write his math exercises but since he has no idea how to do that, he asked you for help. He has told you all he knows about Modular Equations and asked you to write a program which given two numbers $ a $ and $ b $ determines how many answers the Modular Equation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495B/bedc8c54f3a5a224f7fdfd3a3301336e4b862b12.png) has.

## 说明/提示

In the first sample the answers of the Modular Equation are 8 and 16 since ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495B/c013274f5a802f50affb5d5736cfe493bd6c937a.png)

## 样例 #1

### 输入

```
21 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
9435152 272
```

### 输出

```
282
```

## 样例 #3

### 输入

```
10 10
```

### 输出

```
infinity
```

# AI分析结果

### 题目内容
# 模方程

## 题目描述
上周，哈米德在数学课上学到了一种新型方程，叫做模方程。我们将 $i$ 除以 $j$ 的余数定义为 $i$ 模 $j$，并用 $\text{i}\bmod\text{j}$ 表示。正如哈米德的老师所描述的，模方程是形如 $a\bmod x = b$ 的方程，其中 $a$ 和 $b$ 是两个非负整数，$x$ 是变量。我们把使 $a\bmod x = b$ 成立的正整数 $x$ 称为该方程的解。

哈米德在课堂上因为看电影没怎么注意听讲，他只弄懂了这些方程的定义。

现在他想完成数学作业，但因为不知道怎么做，所以向你求助。他把自己所知道的关于模方程的所有信息都告诉了你，并请你编写一个程序，对于给定的两个数 $a$ 和 $b$，确定模方程 $a\bmod x = b$ 有多少个解。

## 说明/提示
在第一个样例中，模方程的解是 8 和 16，因为 $21\bmod 8 = 5$ 且 $21\bmod 16 = 5$。

## 样例 #1
### 输入
```
21 5
```
### 输出
```
2
```

## 样例 #2
### 输入
```
9435152 272
```
### 输出
```
282
```

## 样例 #3
### 输入
```
10 10
```
### 输出
```
infinity
```

### 算法分类
数学

### 题解综合分析与结论
所有题解均围绕对 $a$ 和 $b$ 大小关系的分类讨论展开求解。思路上，当 $a = b$ 时，大于 $a$（或 $b$）的任意 $x$ 都满足方程，解有无限个；当 $a < b$ 时，由于余数不能大于被除数，所以无解；当 $a > b$ 时，将方程 $a\bmod x = b$ 转化为 $a - b = kx$（$k$ 为整数），即求 $a - b$ 中大于 $b$ 的因数个数。算法要点在于利用数学性质化简方程，并通过遍历 $\sqrt{a - b}$ 来提高求因数的效率。解决难点在于对不同情况的准确分类和对因数求解过程中边界条件（如 $x$ 不能重复计算）的处理。各题解整体思路相近，质量差异主要体现在代码的简洁性、清晰度以及对特殊情况处理的完整性上。

### 所选的题解
- **作者：BLX32M_10（5星）**
    - **关键亮点**：思路清晰，简洁明了。直接根据题目未提及“无答案”情况得出 $a \ge b$，省略了 $a < b$ 的讨论，简化代码。对 $a = b$ 情况进行特判，之后通过遍历 $1$ 到 $\sqrt{a - b}$ 判断整除，且对 $i = \sqrt{a - b}$ 的情况处理得当。
    - **重点代码核心实现思想**：先特判 $a = b$ 输出“infinity”，然后 $a -= b$，通过循环从 $1$ 到 $\sqrt{a}$ 判断 $a$ 的因数，若 $i$ 是因数且 $i > b$ 则答案加一，若 $a / i$ 是因数且 $a / i > b$ 且 $i \neq a / i$ 则答案再加一。
    ```cpp
    int main()
    {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == b)
        {
            printf("infinity");
            return 0;
        }
        a -= b;
        int res = 0;
        for (int i = 1; i * i <= a; i++)
            if (a % i == 0)
                if (i * i == a)
                    res += (i > b);
                else
                    res += (i > b) + (a / i > b);
        printf("%d", res);
        return 0;
    }
    ```
- **作者：zsyyyy（4星）**
    - **关键亮点**：对三种情况（$a = b$、$a < b$、$a > b$）的分析详细且有条理，代码注释清晰，使用 `#define int long long` 方便处理较大数据。
    - **重点代码核心实现思想**：先对 $a = b$ 和 $a < b$ 分别特判输出“infinity”和“0”，$a > b$ 时，$a -= b$，通过循环从 $1$ 到 $\sqrt{a}$ 判断因数，处理与上一代码类似。
    ```cpp
    #include<bits/stdc++.h>
    #define int long long
    using namespace std;
    int a,b,sa,ans;
    signed main()
    {
        scanf("%lld%lld",&a,&b);
        if(a==b)
        {
            puts("infinity");
            return 0;
        }
        if(a<b)
        {
            puts("0");
            return 0;
        }
        a-=b;
        sa=sqrt(a);
        for(int i=1;i<=sa;i++)
        {
            if(!(a%i))
            {
                if(i>b)  ans++;
                if((a/i)>b&&i!=(a/i))  ans++;
            }
        }
        printf("%lld",ans);
        return 0;
    }
    ```
- **作者：TRZ_2007（4星）**
    - **关键亮点**：对每种情况的数学推导清晰，代码逻辑紧凑，变量命名直观，如 `moder` 表示 $a - b$。
    - **重点代码核心实现思想**：与其他代码类似，先处理 $a < b$ 和 $a = b$ 的情况，$a > b$ 时，求出 $a - b$，通过循环从 $1$ 到 $\sqrt{a - b}$ 判断因数并统计符合条件的 $x$ 个数。
    ```cpp
    int main() {
        scanf("%d %d",&n,&m);
        if(n < m) printf("0\n");
        else if(n == m) {
            printf("infinity\n");
        } else {
            moder = n - m;
            for(int i = 1;i * i <= moder;i++) {
                if(moder % i == 0) {
                    ans += (i > m);
                    if(moder / i > m && moder / i!= i) ++ans;
                }
            }
            printf("%d\n",ans);
        }
        return 0;
    }
    ```

### 最优关键思路或技巧
利用数学性质将模方程 $a\bmod x = b$ 转化为 $a - b = kx$，从而将问题转化为求 $a - b$ 的因数个数问题，并通过只遍历到 $\sqrt{a - b}$ 来优化时间复杂度。同时，准确处理 $a$ 和 $b$ 不同大小关系下的特殊情况。

### 可拓展之处
同类型题通常围绕数论中的余数、因数等概念，如给定更复杂的模方程形式，或结合其他数论知识如最大公约数、最小公倍数等出题。类似算法套路是遇到模运算相关问题，尝试通过数学推导转化为更易求解的形式，利用数论性质和优化的枚举方式解决问题。

### 洛谷相似题目推荐
- [P1072  Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)：涉及数论中最大公约数和最小公倍数的计算与推理，与本题类似，需根据数论性质进行分类讨论和求解。
- [P2613  【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)：考查数论中的取模运算以及逆元的概念，与本题在模运算的数学处理上有相似之处。
- [P1572  计算分数](https://www.luogu.com.cn/problem/P1572)：通过分数运算和取模操作，锻炼对数学运算和数论知识的综合运用，与本题思路有一定关联。

### 个人心得摘录与总结
无。 

---
处理用时：76.44秒