# 题目信息

# Madoka and Math Dad

## 题目描述

Madoka finally found the administrator password for her computer. Her father is a well-known popularizer of mathematics, so the password is the answer to the following problem.

Find the maximum decimal number without zeroes and with no equal digits in a row, such that the sum of its digits is $ n $ .

Madoka is too tired of math to solve it herself, so help her to solve this problem!

## 说明/提示

The only numbers with the sum of digits equal to $ 2 $ without zeros are $ 2 $ and $ 11 $ . But the last one has two ones in a row, so it's not valid. That's why the answer is $ 2 $ .

The only numbers with the sum of digits equal to $ 3 $ without zeros are $ 111 $ , $ 12 $ , $ 21 $ , and $ 3 $ . The first one has $ 2 $ ones in a row, so it's not valid. So the maximum valid number is $ 21 $ .

The only numbers with the sum of digits equals to $ 4 $ without zeros are $ 1111 $ , $ 211 $ , $ 121 $ , $ 112 $ , $ 13 $ , $ 31 $ , $ 22 $ , and $ 4 $ . Numbers $ 1111 $ , $ 211 $ , $ 112 $ , $ 22 $ aren't valid, because they have some identical digits in a row. So the maximum valid number is $ 121 $ .

## 样例 #1

### 输入

```
5
1
2
3
4
5```

### 输出

```
1
2
21
121
212```

# AI分析结果

### 题目内容
# Madoka和数学爸爸

## 题目描述
Madoka最终找到了她电脑的管理员密码。她的父亲是一位知名的数学科普者，所以密码是以下问题的答案。

找到最大的十进制数，该数不含零且没有连续相等的数字，使得其各位数字之和为 $n$ 。

Madoka对数学感到十分厌倦，无法自己解决这个问题，所以请帮助她解决这个问题！

## 说明/提示
各位数字之和等于2且不含零的数只有2和11。但11有两个连续的1，所以它不符合要求。这就是为什么答案是2。

各位数字之和等于3且不含零的数有111、12、21和3。111有两个连续的1，所以它不符合要求。所以最大的有效数字是21。

各位数字之和等于4且不含零的数有1111、211、121、112、13、31、22和4。1111、211、112、22不符合要求，因为它们有连续相同的数字。所以最大的有效数字是121。

## 样例 #1
### 输入
```
5
1
2
3
4
5
```
### 输出
```
1
2
21
121
212
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，要使所求数字最大，需让位数尽可能多，所以优先考虑用最小的非零数字1和2来组成该数，且1和2交替出现。通过对样例分析或数学推导得出，数字的形态与 $n$ 除以3的余数有关，进而根据余数分类讨论得出结果。各题解的主要差异在于代码实现方式及对规律的推导过程详细程度不同。

### 所选的题解
- **作者：happy_dengziyue（5星）**
    - **关键亮点**：思路清晰简洁，直接点明数字由1和2组成，并根据 $n \bmod 3$ 的不同情况，直接给出输出数字的形态，代码实现简洁明了。
    - **重点代码**：
```cpp
if(n%3==0){
    for(int i=1;i<=n/3;++i)printf("21");
}
if(n%3==1){
    for(int i=1;i<=n/3;++i)printf("12");
    printf("1");
}
if(n%3==2){
    for(int i=1;i<=n/3;++i)printf("21");
    printf("2");
}
```
    - **核心实现思想**：根据 $n$ 除以3的余数，分别按不同规则循环输出由1和2组成的数字。
- **作者：郑朝曦zzx（4星）**
    - **关键亮点**：解题思路阐述清晰，明确指出使用贪心策略，通过分析样例得出数字形态和输入整数除以3余数的关系，代码结构清晰。
    - **重点代码**：
```cpp
if (x % 3 == 0)
{
    for (int i = 1; i <= x / 3; ++i)
        printf("21");
}
else if (x % 3 == 1)
{
    for (int i = 1; i <= x / 3; ++i)
        printf("12");
    printf("1");
}
else
{
    for (int i = 1; i <= x / 3; ++i)
        printf("21");
    printf("2");
}
```
    - **核心实现思想**：与上一题解类似，依据 $x$（即 $n$）除以3的余数，按不同方式循环输出1和2组成的数字。
- **作者：风羽跃（4星）**
    - **关键亮点**：从另一个角度分析，指出若某一位大于等于3，会将其拆成若干个3再拆成21的情况，进而分类讨论，思路独特，代码实现简洁。
    - **重点代码**：
```cpp
if(n%3==0) For(i,1,n/3) printf("21");
else if(n%3==1){
    putchar('1');
    For(i,1,n/3) printf("21");
}
else{
    For(i,1,n/3) printf("21");
    putchar('2');
}
```
    - **核心实现思想**：根据 $n$ 除以3的余数情况，按不同逻辑输出由1和2组成的数字。

### 最优关键思路或技巧
1. **贪心策略**：优先使用最小的非零数字1和2来构造数字，以保证位数最多从而使数字最大。
2. **余数分类讨论**：通过对样例观察或数学推导，发现数字形态与 $n$ 除以3的余数紧密相关，基于此分类讨论得出结果。

### 同类型题或类似算法套路拓展
此类题目通常围绕数字构造，给定一些限制条件，需通过贪心策略选择合适数字进行组合。常见套路是先分析如何使目标结果最优（如本题使数字最大就需位数最多），再根据限制条件（如本题无零且无连续相同数字），结合数字特性（如本题利用数字和与3的余数关系）进行分类讨论。

### 洛谷相似题目推荐
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：同样运用贪心策略，根据给定条件对数据进行分组。
2. [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：通过分析游戏规则，利用贪心思想找到最优策略。
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间等条件，运用贪心算法求出最优排队方案。 

---
处理用时：36.88秒