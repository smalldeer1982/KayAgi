# 题目信息

# Magic Formulas

## 题目描述

People in the Tomskaya region like magic formulas very much. You can see some of them below.

Imagine you are given a sequence of positive integer numbers $ p_{1} $ , $ p_{2} $ , ..., $ p_{n} $ . Lets write down some magic formulas:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/bc5cfed2fc930604306d4050665204f7083b9e3e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/7e1ac84d84d4d0097a495218327d72c2379cae8d.png)Here, "mod" means the operation of taking the residue after dividing.

The expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying the bitwise $ xor $ (excluding "OR") operation to integers $ x $ and $ y $ . The given operation exists in all modern programming languages. For example, in languages C++ and Java it is represented by "^", in Pascal — by "xor".

People in the Tomskaya region like magic formulas very much, but they don't like to calculate them! Therefore you are given the sequence $ p $ , calculate the value of $ Q $ .

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# Magic Formulas

## 题目描述
托木斯克地区的人们非常喜欢神奇公式。你可以在下面看到其中一些。

假设给你一个正整数序列$p_{1}$，$p_{2}$，...，$p_{n}$。让我们写下一些神奇公式：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/bc5cfed2fc930604306d4050665204f7083b9e3e.png)
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/7e1ac84d84d4d0097a495218327d72c2379cae8d.png)
这里，“mod”表示取余运算。

表达式![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png)表示对整数$x$和$y$应用按位异或（不包括“或”）运算。这个运算在所有现代编程语言中都存在。例如，在C++和Java语言中用“^”表示，在Pascal中用“xor”表示。

托木斯克地区的人们非常喜欢神奇公式，但他们不喜欢计算它们！因此，给定序列$p$，请计算$Q$的值。

## 样例 #1
### 输入
```
3
1 2 3
```
### 输出
```
3
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用异或运算的交换律和结合律，将$Q$拆分为两部分，即$\sum_{i = 1}^{n}p_i$和$\sum_{i = 1}^{n}\sum_{j = 1}^{n}i\%j$分别计算，难点在于对$\sum_{i = 1}^{n}\sum_{j = 1}^{n}i\%j$的优化计算。各题解主要通过分析取模运算的周期性，利用异或运算$x \oplus x = 0$的性质，结合前缀异或和来降低时间复杂度。

### 所选的题解
- **作者：ZolaWatle（5星）**
  - **关键亮点**：思路清晰，详细阐述了从暴力到优化的过程，对优化部分的式子变形、分组讨论讲解细致，代码注释完整。
  - **个人心得**：校内模拟赛做过该题，写题解梳理解题思路。
  ```cpp
  // 核心代码
  for(int i=1;i<=n;i++)
  {
      a[i]=read();
      b[i]=b[i-1]^i;
      ans=ans^a[i];
  }
  
  for(int i=2;i<=n;i++)
  {
      int num=n/i;
      if(num&1) ans^=b[i-1];
      if(num*i<n)
      {
          int k=n-num*i;
          ans^=b[k];
      }
  }
  ```
  - **核心实现思想**：先在输入时计算$\sum_{i = 1}^{n}p_i$并记录前缀异或和$b$，然后遍历$i$，根据$n/i$的奇偶性决定是否异或$b[i - 1]$，若$n$不能被$i$整除，再异或$b[n - i \cdot \lfloor \frac{n}{i} \rfloor - 1]$。

- **作者：osfly（4星）**
  - **关键亮点**：公式推导过程清晰，直接从数学公式角度出发，利用异或性质得出计算$b$的优化式子，代码简洁明了。
  ```cpp
  // 核心代码
  for(int i=1;i<=n;i++) scanf("%lld",&p),ans^=p,pre[i]=pre[i-1]^i;
  for(int i=1;i<=n;i++)
  {
      if((n/i)&1) ans^=pre[i-1];
      ans^=pre[n%i];
  }
  ```
  - **核心实现思想**：输入时计算$\sum_{i = 1}^{n}p_i$并记录前缀异或和$pre$，遍历$i$，根据$n/i$的奇偶性决定是否异或$pre[i - 1]$，再异或$pre[n\%i]$。

- **作者：Perfonster（4星）**
  - **关键亮点**：对每一行的异或值分析独特，从取模运算的周期性出发，清晰得出每行的异或值计算方式，代码逻辑清晰。
  ```cpp
  // 核心代码
  for(int i=1;i<=n;i++){
      a[i]=read();
      q^=a[i];
      sum[i]=sum[i-1]^i;
  }
  for(int i=1;i<=n;i++){
      int t=n%i,p=n/i;
      if(p%2){
          q^=sum[i-1];
      }
      q^=sum[t];
  }
  ```
  - **核心实现思想**：先输入并计算$\sum_{i = 1}^{n}p_i$和前缀异或和$sum$，遍历$i$，根据$n/i$的奇偶性决定是否异或$sum[i - 1]$，再异或$sum[n\%i]$。

### 最优关键思路或技巧
利用异或运算的交换律、结合律以及$x \oplus x = 0$的性质，通过分析取模运算的周期性，将$\sum_{i = 1}^{n}\sum_{j = 1}^{n}i\%j$按$j$分组，结合前缀异或和优化计算，从而将时间复杂度从暴力的$O(n^2)$降低到$O(n)$。

### 可拓展思路
此类题目通常涉及数论与位运算结合，类似套路是分析运算的数学性质（如交换律、结合律、周期性等），利用这些性质对复杂式子进行变形和优化。同类型题可能会改变运算类型或者增加序列的限制条件等。

### 洛谷相似题目推荐
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：涉及归并排序和前缀和思想，与本题利用特定运算性质优化计算有相似之处。
- [P2141 珠心算测验](https://www.luogu.com.cn/problem/P2141)：通过位运算和枚举解决问题，和本题对异或运算的运用类似。
- [P3390 【模板】矩阵快速幂](https://www.luogu.com.cn/problem/P3390)：虽然是矩阵快速幂问题，但在利用数学性质优化计算方面与本题有相通之处。 

---
处理用时：57.30秒