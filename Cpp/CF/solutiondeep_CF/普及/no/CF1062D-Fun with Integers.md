# 题目信息

# Fun with Integers

## 题目描述

You are given a positive integer $ n $ greater or equal to $ 2 $ . For every pair of integers $ a $ and $ b $ ( $ 2 \le |a|, |b| \le n $ ), you can transform $ a $ into $ b $ if and only if there exists an integer $ x $ such that $ 1 < |x| $ and ( $ a \cdot x = b $ or $ b \cdot x = a $ ), where $ |x| $ denotes the absolute value of $ x $ .

After such a transformation, your score increases by $ |x| $ points and you are not allowed to transform $ a $ into $ b $ nor $ b $ into $ a $ anymore.

Initially, you have a score of $ 0 $ . You can start at any integer and transform it as many times as you like. What is the maximum score you can achieve?

## 说明/提示

In the first example, the transformations are $ 2 \rightarrow 4 \rightarrow (-2) \rightarrow (-4) \rightarrow 2 $ .

In the third example, it is impossible to perform even a single transformation.

## 样例 #1

### 输入

```
4
```

### 输出

```
8```

## 样例 #2

### 输入

```
6
```

### 输出

```
28```

## 样例 #3

### 输入

```
2
```

### 输出

```
0```

# AI分析结果

### 题目重写
# 与整数的乐趣

## 题目描述

给定一个大于或等于2的正整数$n$。对于每一对整数$a$和$b$（$2 \le |a|, |b| \le n$），你可以将$a$转换为$b$，当且仅当存在一个整数$x$，使得$1 < |x|$且（$a \cdot x = b$或$b \cdot x = a$），其中$|x|$表示$x$的绝对值。

在进行这样的转换后，你的分数增加$|x|$分，并且你不能再将$a$转换为$b$或将$b$转换为$a$。

初始时，你的分数为0。你可以从任意整数开始，并尽可能多地进行转换。你能获得的最大分数是多少？

## 说明/提示

在第一个例子中，转换过程为$2 \rightarrow 4 \rightarrow (-2) \rightarrow (-4) \rightarrow 2$。

在第三个例子中，甚至无法进行任何一次转换。

## 样例 #1

### 输入

```
4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
6
```

### 输出

```
28
```

## 样例 #3

### 输入

```
2
```

### 输出

```
0
```

### 算法分类
数学

### 题解分析与结论
所有题解的核心思路都是通过枚举每个数的倍数来计算得分，并最终将结果乘以4以涵盖正负数的所有情况。不同题解在代码实现和优化程度上有所差异。

### 所选高星题解
1. **作者：张心博harry (5星)**
   - **关键亮点**：代码简洁，思路清晰，通过枚举倍数并巧妙地将结果乘以4来涵盖所有情况。
   - **代码核心**：
     ```cpp
     for(int i=2;i<=n;i++) for(int j=2*i;j<=n;j=j+i) ans=ans+j/i;
     cout<<ans*4<<endl;
     ```
   - **个人心得**：作者提到一开始想用二维数组记录转换情况，但发现不可行，最终通过直接计算倍数得到答案。

2. **作者：AubRain (4星)**
   - **关键亮点**：代码简洁，直接枚举倍数并累加得分，最后乘以4。
   - **代码核心**：
     ```cpp
     for(int i=2;i<=n;i++) for(int j=i+i;j<=n;j+=i) ans+=j/i;
     cout<<ans*4;
     ```
   - **个人心得**：作者提到可以进一步优化到$O(n)$或$O(n^{1/2})$，但认为没有必要。

3. **作者：ryf_loser (4星)**
   - **关键亮点**：使用高斯求和公式进行优化，代码简洁且高效。
   - **代码核心**：
     ```cpp
     for (int i=2;i<=n;i++)ans+=((n/i+2)*(n/i-1));
     printf ("%lld",ans<<1);
     ```
   - **个人心得**：作者提到喜欢优化，并使用了高斯求和公式来简化计算。

### 最优关键思路
通过枚举每个数的倍数来计算得分，并最终将结果乘以4以涵盖正负数的所有情况。这种方法既简洁又高效，避免了复杂的记录和计算。

### 可拓展之处
类似的问题可以通过枚举倍数或使用数学公式来简化计算，特别是在涉及整数变换和得分累加的场景中。

### 推荐题目
1. [P1062 数列](https://www.luogu.com.cn/problem/P1062)
2. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)
3. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

---
处理用时：28.39秒