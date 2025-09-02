# 题目信息

# Physical Education Lesson

## 题目描述

In a well-known school, a physical education lesson took place. As usual, everyone was lined up and asked to settle in "the first– $ k $ -th" position.

As is known, settling in "the first– $ k $ -th" position occurs as follows: the first $ k $ people have numbers $ 1, 2, 3, \ldots, k $ , the next $ k - 2 $ people have numbers $ k - 1, k - 2, \ldots, 2 $ , the next $ k $ people have numbers $ 1, 2, 3, \ldots, k $ , and so on. Thus, the settling repeats every $ 2k - 2 $ positions. Examples of settling are given in the "Note" section.

The boy Vasya constantly forgets everything. For example, he forgot the number $ k $ described above. But he remembers the position he occupied in the line, as well as the number he received during the settling. Help Vasya understand how many natural numbers $ k $ fit under the given constraints.

Note that the settling exists if and only if $ k > 1 $ . In particular, this means that the settling does not exist for $ k = 1 $ .

## 说明/提示

In the first test case, $ k $ equals $ 2, 3, 5, 6 $ are suitable.

An example of settling for these $ k $ :

  $ k $ / № $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 6 $  $ 7 $  $ 8 $  $ 9 $  $ 10 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 3 $  $ 1 $  $ 2 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 5 $  $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 4 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 6 $  $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 6 $  $ 5 $  $ 4 $  $ 3 $  $ 2 $  In the second test case, $ k = 2 $ is suitable.

## 样例 #1

### 输入

```
5
10 2
3 1
76 4
100 99
1000000000 500000000```

### 输出

```
4
1
9
0
1```

# AI分析结果

### 题目内容重写（中文）

在一所知名学校中，进行了一节体育课。和往常一样，所有人排成一列，并被要求按照“第1到第k个”位置就座。

众所周知，按照“第1到第k个”位置就座的规则如下：前k个人的编号为1, 2, 3, ..., k，接下来的k-2个人的编号为k-1, k-2, ..., 2，再接下来的k个人的编号为1, 2, 3, ..., k，以此类推。因此，这种就座方式每2k-2个位置重复一次。具体的例子可以在“说明/提示”部分找到。

男孩Vasya总是忘记一切。例如，他忘记了上述的k值。但他记得自己在队列中的位置，以及在就座时获得的编号。请帮助Vasya找出有多少个自然数k符合给定的约束条件。

注意，这种就座方式仅当k > 1时存在。特别地，这意味着当k = 1时，这种就座方式不存在。

### 说明/提示

在第一个测试用例中，k = 2, 3, 5, 6是合适的。

这些k的就座方式示例如下：

- k = 2：1, 2, 1, 2, 1, 2, 1, 2, 1, 2
- k = 3：1, 2, 3, 2, 1, 2, 3, 2, 1, 2
- k = 5：1, 2, 3, 4, 5, 4, 3, 2, 1, 2
- k = 6：1, 2, 3, 4, 5, 6, 5, 4, 3, 2

在第二个测试用例中，k = 2是合适的。

### 样例 #1

#### 输入

```
5
10 2
3 1
76 4
100 99
1000000000 500000000
```

#### 输出

```
4
1
9
0
1
```

### 题解分析与结论

该题的核心是找出所有满足条件的k值，使得在特定的位置n上，编号为x。题解的主要思路是通过数学推导，将问题转化为求解同余方程或枚举因数的问题。大多数题解都采用了分类讨论的方法，分别考虑x在上升段和下降段的情况，并通过枚举因数来找到符合条件的k值。

### 精选题解

#### 题解1：作者：int_R (赞：7)
- **星级**：★★★★★
- **关键亮点**：通过枚举n-x和n+x-2的因数，直接判断k是否合法，并使用set去重，代码简洁高效。
- **核心代码**：
  ```cpp
  inline void A(int y) { if(!(y&1)&&y/2+1>=x) s.insert(y); }
  inline void work() {
      cin >> n >> x;
      int a = n - x, b = n + (x - 2);
      for(int i = 1; i <= sqrt(a); ++i)
          if(!(a % i)) A(i), A(a / i);
      for(int i = 1; i <= sqrt(b); ++i)
          if(!(b % i)) A(i), A(b / i);
      cout << s.size() << '\n'; s.clear();
  }
  ```

#### 题解2：作者：信息向阳花木 (赞：7)
- **星级**：★★★★★
- **关键亮点**：详细推导了x在上升段和下降段的情况，并通过枚举因数来求解k值，代码逻辑清晰。
- **核心代码**：
  ```cpp
  for(int i = 1; i <= p / i; i++) {
      if(p % i == 0) {
          if(i % 2 == 0) {
              int k = (i + 2) / 2;
              if(x >= 1 && x <= k) res++;
          }
          int j = p / i;
          if(j != i && j % 2 == 0) {
              int k = (j + 2) / 2;
              if(x >= 1 && x <= k) res++;
          }
      }
  }
  ```

#### 题解3：作者：HappyJaPhy (赞：4)
- **星级**：★★★★
- **关键亮点**：通过同余方程将问题转化为求解因数的问题，并注意去重，代码实现较为简洁。
- **核心代码**：
  ```cpp
  inline int work(int a, int b, int x) {
      int m = a - b, res = 0;
      for(int i = 1; i * i <= m; i++) {
          if(m % i == 0) {
              if(check(i, b, x)) res++;
              if(check(m / i, b, x)) res++;
          }
      }
      return res;
  }
  ```

### 最优关键思路与技巧

1. **分类讨论**：将问题分为x在上升段和下降段两种情况，分别求解。
2. **枚举因数**：通过枚举n-x和n+x-2的因数，快速找到符合条件的k值。
3. **去重处理**：使用set或map来避免重复计算相同的k值。

### 拓展思路

该题的解题思路可以推广到类似的周期性排列问题，尤其是涉及到位置与编号关系的题目。通过数学推导和枚举因数的方法，可以高效解决这类问题。

### 推荐题目

1. [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)
2. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
3. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)

### 个人心得总结

在解决这类问题时，数学推导和分类讨论是非常重要的。通过将问题转化为同余方程或因数枚举，可以大大简化问题的复杂度。同时，使用数据结构如set或map来去重，可以避免重复计算，提高代码的效率。

---
处理用时：48.38秒