# 题目信息

# Nice Matrix

## 题目描述

A matrix of size $ n \times m $ is called nice, if all rows and columns of the matrix are palindromes. A sequence of integers $ (a_1, a_2, \dots , a_k) $ is a palindrome, if for any integer $ i $ ( $ 1 \le i \le k $ ) the equality $ a_i = a_{k - i + 1} $ holds.

Sasha owns a matrix $ a $ of size $ n \times m $ . In one operation he can increase or decrease any number in the matrix by one. Sasha wants to make the matrix nice. He is interested what is the minimum number of operations he needs.

Help him!

## 说明/提示

In the first test case we can, for example, obtain the following nice matrix in $ 8 $ operations:

```
<pre class="verbatim"><br></br>2 2<br></br>4 4<br></br>4 4<br></br>2 2<br></br>
```

In the second test case we can, for example, obtain the following nice matrix in $ 42 $ operations:

```
<pre class="verbatim"><br></br>5 6 6 5<br></br>6 6 6 6<br></br>5 6 6 5<br></br>
```

## 样例 #1

### 输入

```
2
4 2
4 2
2 4
4 2
2 4
3 4
1 2 3 4
5 6 7 8
9 10 11 18```

### 输出

```
8
42```

# AI分析结果

### 题目内容重写

#### 题目描述

一个大小为 $n \times m$ 的矩阵被称为“nice”，如果矩阵的所有行和列都是回文序列。一个整数序列 $(a_1, a_2, \dots , a_k)$ 是回文序列，如果对于任何整数 $i$（$1 \le i \le k$），等式 $a_i = a_{k - i + 1}$ 成立。

Sasha 拥有一个大小为 $n \times m$ 的矩阵 $a$。在一次操作中，他可以将矩阵中的任何一个数增加或减少 1。Sasha 想要使这个矩阵变成“nice”矩阵。他想知道最少需要多少次操作。

帮助他！

#### 说明/提示

在第一个测试用例中，我们可以通过 8 次操作得到以下“nice”矩阵：

```
2 2
4 4
4 4
2 2
```

在第二个测试用例中，我们可以通过 42 次操作得到以下“nice”矩阵：

```
5 6 6 5
6 6 6 6
5 6 6 5
```

#### 样例 #1

##### 输入

```
2
4 2
4 2
2 4
4 2
2 4
3 4
1 2 3 4
5 6 7 8
9 10 11 18
```

##### 输出

```
8
42
```

### 算法分类
贪心

### 题解分析与结论

题目要求将矩阵变为“nice”矩阵，即所有行和列都是回文序列。通过分析可以发现，矩阵中的每个元素最多与三个其他元素相关（对称位置的元素）。为了使这些元素相等，且操作次数最少，通常选择将这些元素变为它们的中位数。

#### 关键思路
1. **对称性分析**：矩阵中的每个元素与其对称位置的元素必须相等，因此可以将这些元素分为一组进行处理。
2. **中位数选择**：为了使操作次数最少，选择将这些元素变为它们的中位数。
3. **特殊情况处理**：当矩阵的行或列为奇数时，需要单独处理中轴线上的元素。

### 高星题解

#### 题解1：作者：Lynkcat (5星)
**关键亮点**：
- 通过对称性分析，将矩阵中的元素分组处理。
- 使用中位数来最小化操作次数，思路清晰且代码简洁。

**核心代码**：
```cpp
for (int i=1;i<=(n/2)+(n&1);i++)
  for (int j=1;j<=(m/2)+(m&1);j++)
  {
    tot=0;
    tot++,p[tot]=a[i][j];
    if (n-i+1!=i) tot++,p[tot]=a[n-i+1][j];
    if (m-j+1!=j) tot++,p[tot]=a[i][m-j+1];
    if (n-i+1!=i&&m-j+1!=j) tot++,p[tot]=a[n-i+1][m-j+1];
    sort(p+1,p+tot+1);
    for (int j=1;j<=tot/2;j++) ans+=p[j+tot/2]-p[j];
  }
```

#### 题解2：作者：Werner_Yin (4星)
**关键亮点**：
- 详细解释了中位数选择的数学依据，并通过图示直观展示了最优解。
- 代码中考虑了矩阵中轴线的特殊情况，处理较为全面。

**核心代码**：
```cpp
for(int i = 1;i <= n/2;i++){
    for(int j = 1;j <= m/2;j++){
        ll tt = INF,sum;
        sum = a[i][j];
        tt = min(tt,abs(a[i][j]-sum) + abs(a[n-i+1][j]-sum)+abs(a[i][m-j+1]-sum) + abs(a[n-i+1][m-j+1]-sum));
        sum = a[n-i+1][j];
        tt = min(tt,abs(a[i][j]-sum) + abs(a[n-i+1][j]-sum)+abs(a[i][m-j+1]-sum) + abs(a[n-i+1][m-j+1]-sum));
        sum = a[i][m-j+1];
        tt = min(tt,abs(a[i][j]-sum) + abs(a[n-i+1][j]-sum)+abs(a[i][m-j+1]-sum) + abs(a[n-i+1][m-j+1]-sum));
        sum = a[n-i+1][m-j+1];
        tt = min(tt,abs(a[i][j]-sum) + abs(a[n-i+1][j]-sum)+abs(a[i][m-j+1]-sum) + abs(a[n-i+1][m-j+1]-sum));
        ans += tt;
    }
}
```

#### 题解3：作者：cqbzpyl (4星)
**关键亮点**：
- 通过贪心思想，直接选择中位数作为目标值，简化了计算过程。
- 代码实现简洁，且考虑了矩阵中轴线的特殊情况。

**核心代码**：
```cpp
for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
        b[0]=a[i][j],b[1]=a[i][m-j+1];
        b[2]=a[n-i+1][j],b[3]=a[n-i+1][m-j+1];
        sort(b,b+3);
        int cnt=min(b[1],b[2]);
        ans+=abs(cnt-b[0])+abs(cnt-b[1])+abs(cnt-b[2])+abs(cnt-b[3]);
    }
}
```

### 最优关键思路
1. **对称性分组**：将矩阵中的元素按照对称性分组，每组最多包含四个元素。
2. **中位数选择**：将每组元素变为它们的中位数，以最小化操作次数。
3. **特殊情况处理**：当矩阵的行或列为奇数时，单独处理中轴线上的元素。

### 拓展思路
类似的问题可以扩展到更高维度的矩阵或更复杂的对称性要求。例如，处理三维矩阵中的对称性问题，或者要求矩阵的某些特定区域满足回文条件。

### 推荐题目
1. [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433) - 考察贪心与对称性处理。
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219) - 考察对称性与回溯算法。
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 考察贪心与最小化操作次数。

---
处理用时：45.38秒