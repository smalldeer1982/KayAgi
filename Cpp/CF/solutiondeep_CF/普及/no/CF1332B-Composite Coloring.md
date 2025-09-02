# 题目信息

# Composite Coloring

## 题目描述

A positive integer is called composite if it can be represented as a product of two positive integers, both greater than $ 1 $ . For example, the following numbers are composite: $ 6 $ , $ 4 $ , $ 120 $ , $ 27 $ . The following numbers aren't: $ 1 $ , $ 2 $ , $ 3 $ , $ 17 $ , $ 97 $ .

Alice is given a sequence of $ n $ composite numbers $ a_1,a_2,\ldots,a_n $ .

She wants to choose an integer $ m \le 11 $ and color each element one of $ m $ colors from $ 1 $ to $ m $ so that:

- for each color from $ 1 $ to $ m $ there is at least one element of this color;
- each element is colored and colored exactly one color;
- the greatest common divisor of any two elements that are colored the same color is greater than $ 1 $ , i.e. $ \gcd(a_i, a_j)>1 $ for each pair $ i, j $ if these elements are colored the same color.

Note that equal elements can be colored different colors — you just have to choose one of $ m $ colors for each of the indices from $ 1 $ to $ n $ .

Alice showed already that if all $ a_i \le 1000 $ then she can always solve the task by choosing some $ m \le 11 $ .

Help Alice to find the required coloring. Note that you don't have to minimize or maximize the number of colors, you just have to find the solution with some $ m $ from $ 1 $ to $ 11 $ .

## 说明/提示

In the first test case, $ \gcd(6,10)=2 $ , $ \gcd(6,15)=3 $ and $ \gcd(10,15)=5 $ . Therefore, it's valid to color all elements the same color. Note that there are other colorings which satisfy Alice's requirement in this test case.

In the second test case there is only one element of each color, so the coloring definitely satisfies Alice's requirement.

## 样例 #1

### 输入

```
3
3
6 10 15
2
4 9
23
437 519 865 808 909 391 194 291 237 395 323 365 511 497 781 737 871 559 731 697 779 841 961```

### 输出

```
1
1 1 1
2
2 1
11
4 7 8 10 7 3 10 7 7 8 3 1 1 5 5 9 2 2 3 3 4 11 6```

# AI分析结果

### 题目翻译
# 合数染色

## 题目描述

一个正整数被称为合数，如果它可以表示为两个大于 $1$ 的正整数的乘积。例如，以下数字是合数：$6$、$4$、$120$、$27$。以下数字不是合数：$1$、$2$、$3$、$17$、$97$。

Alice 被给定一个包含 $n$ 个合数的序列 $a_1,a_2,\ldots,a_n$。

她希望选择一个整数 $m \le 11$，并将每个元素染成 $1$ 到 $m$ 中的一种颜色，使得：

- 对于每种颜色 $1$ 到 $m$，至少有一个元素被染成该颜色；
- 每个元素被染色且仅被染成一种颜色；
- 任何两个被染成相同颜色的元素的最大公约数大于 $1$，即对于每对 $i, j$，如果这些元素被染成相同颜色，则 $\gcd(a_i, a_j)>1$。

注意，相等的元素可以被染成不同的颜色——你只需为每个索引从 $1$ 到 $n$ 选择一种颜色。

Alice 已经证明，如果所有 $a_i \le 1000$，那么她总是可以通过选择某个 $m \le 11$ 来解决这个问题。

帮助 Alice 找到所需的染色方案。注意，你不需要最小化或最大化颜色数，只需找到一个 $m$ 在 $1$ 到 $11$ 之间的解。

## 说明/提示

在第一个测试用例中，$\gcd(6,10)=2$，$\gcd(6,15)=3$，$\gcd(10,15)=5$。因此，将所有元素染成同一种颜色是有效的。注意，在这个测试用例中还有其他满足 Alice 要求的染色方案。

在第二个测试用例中，每种颜色只有一个元素，因此染色方案肯定满足 Alice 的要求。

## 样例 #1

### 输入

```
3
3
6 10 15
2
4 9
23
437 519 865 808 909 391 194 291 237 395 323 365 511 497 781 737 871 559 731 697 779 841 961
```

### 输出

```
1
1 1 1
2
2 1
11
4 7 8 10 7 3 10 7 7 8 3 1 1 5 5 9 2 2 3 3 4 11 6
```

### 算法分类
构造、数学

### 题解分析与结论
本题的核心思路是利用合数的质因数特性进行分组染色。由于所有合数的最小质因数不超过 $\sqrt{1000}$（即 31），而 31 以内的质数恰好有 11 个，因此可以将每个合数按其最小质因数分配到对应的颜色组中。这样，每组内的数都有相同的质因数，保证了它们的最大公约数大于 1。

### 高星题解推荐
1. **作者：Rainy7 (赞：8)**  
   - **星级：4.5**  
   - **关键亮点**：通过打表找到前 11 个质数，并将每个合数按其最小质因数分配到对应的颜色组中。代码清晰，逻辑简单，易于理解。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++)
         for(int j=1;j<=cnt;j++) //分组
             if(a[i]%p[j]==0){ans[i]=j;break;}
     ```

2. **作者：cute_overmind (赞：3)**  
   - **星级：4**  
   - **关键亮点**：直接使用前 11 个质数进行分组，代码简洁，逻辑清晰。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++){
         for(int j=1;j<=11;j++){
             if(a[i]%p[j]==0){
                 if(cur[j]==0) cur[j]=++cnt;
                 b[i]=cur[j];
                 break;
             }
         }
     }
     ```

3. **作者：lijianACE (赞：2)**  
   - **星级：4**  
   - **关键亮点**：详细解释了为什么可以使用前 11 个质数进行分组，并提供了完整的代码实现。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++){
         for(int j=1;j<=11;j++){
             if(a[i]%prime[j]==0){
                 if(usep[j]==0){//如果还没用过
                     gs++;
                     usep[j]=gs;
                 }
                 a[i]=usep[j];//千万记得不是赋值它桶代表的质数
                 break;
             }
         }
     }
     ```

### 最优关键思路
利用合数的最小质因数进行分组染色，确保每组内的数有相同的质因数，从而保证它们的最大公约数大于 1。这种方法简单高效，且代码实现清晰。

### 拓展思路
类似的问题可以扩展到更大的数范围，或者要求最小化颜色数。此外，可以结合其他数学性质（如最大公约数、最小公倍数等）进行更复杂的分组染色。

### 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)
3. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)

---
处理用时：38.39秒