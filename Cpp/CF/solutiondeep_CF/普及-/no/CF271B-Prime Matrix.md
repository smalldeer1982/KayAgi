# 题目信息

# Prime Matrix

## 题目描述

You've got an $ n×m $ matrix. The matrix consists of integers. In one move, you can apply a single transformation to the matrix: choose an arbitrary element of the matrix and increase it by $ 1 $ . Each element can be increased an arbitrary number of times.

You are really curious about prime numbers. Let us remind you that a prime number is a positive integer that has exactly two distinct positive integer divisors: itself and number one. For example, numbers 2, 3, 5 are prime and numbers 1, 4, 6 are not.

A matrix is prime if at least one of the two following conditions fulfills:

- the matrix has a row with prime numbers only;
- the matrix has a column with prime numbers only;

Your task is to count the minimum number of moves needed to get a prime matrix from the one you've got.

## 说明/提示

In the first sample you need to increase number 1 in cell (1, 1). Thus, the first row will consist of prime numbers: 2, 2, 3.

In the second sample you need to increase number 8 in cell (1, 2) three times. Thus, the second column will consist of prime numbers: 11, 2.

In the third sample you don't have to do anything as the second column already consists of prime numbers: 3, 2.

## 样例 #1

### 输入

```
3 3
1 2 3
5 6 1
4 4 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3
4 8 8
9 2 9
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2 2
1 3
4 2
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 质数矩阵

## 题目描述
你有一个 $n×m$ 的矩阵。矩阵由整数组成。在一次移动中，你可以对矩阵应用单个变换：选择矩阵中的任意一个元素并将其增加 $1$ 。每个元素可以增加任意次数。

你对质数非常感兴趣。让我们提醒你，质数是一个正整数，它恰好有两个不同的正整数因数：它本身和数字 $1$ 。例如，数字 $2$、$3$、$5$ 是质数，而数字 $1$、$4$、$6$ 不是。

如果满足以下两个条件中的至少一个，则矩阵是质数矩阵：
- 矩阵有一行仅由质数组成；
- 矩阵有一列仅由质数组成。

你的任务是计算从你所拥有的矩阵得到质数矩阵所需的最小移动次数。

## 说明/提示
在第一个样例中，你需要将单元格 $(1, 1)$ 中的数字 $1$ 增加。这样，第一行将由质数组成：$2$、$2$、$3$ 。

在第二个样例中，你需要将单元格 $(1, 2)$ 中的数字 $8$ 增加三次。这样，第二列将由质数组成：$11$、$2$ 。

在第三个样例中，你无需做任何操作，因为第二列已经由质数组成：$3$、$2$ 。

## 样例 #1
### 输入
```
3 3
1 2 3
5 6 1
4 4 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
2 3
4 8 8
9 2 9
```
### 输出
```
3
```

## 样例 #3
### 输入
```
2 2
1 3
4 2
```
### 输出
```
0
```

### 算法分类
质数

### 综合分析与结论
这几道题解的核心思路都是先筛选出一定范围内的质数，然后针对矩阵中的每个元素，计算将其变为质数所需的操作次数，最后统计行和列的操作次数总和，取最小值作为结果。不同之处主要在于质数筛选方法（埃氏筛、欧拉筛、线性筛等）以及代码实现细节。
1. **思路**：均围绕找出矩阵元素到最近质数的操作次数，进而统计行和列的最小操作次数和。
2. **算法要点**：需掌握质数筛选算法（埃氏筛、欧拉筛、线性筛等），并能遍历矩阵计算操作次数，最后统计结果。
3. **解决难点**：确定合适的质数筛选范围，优化计算每个元素到最近质数的操作次数的过程，减少时间复杂度。

### 所选的题解
- **作者：agicy（5星）**
    - **关键亮点**：思路清晰，代码简洁明了。使用埃氏筛法筛选质数，通过巧妙地记录行和列的操作总数，简化了最终统计答案的过程。
    - **重点代码**：
```cpp
// 埃氏筛
isNotPrime[1] = true;
for (i = 2; i <= 100003; ++i) {
    if (!isNotPrime[i])
        for (j = (i << 1); j <= 100003; j += i)
            isNotPrime[j] = true;
}
for (i = 1; i <= n; ++i)
    for (j = 1; j <= m; ++j) {
        scanf("%d", &a[i][j]);
        now = temp = a[i][j];
        while (isNotPrime[now])
            ++now;
        a[i][j] = now - temp;
        a[i][0] += a[i][j];
        a[0][j] += a[i][j];
    }
for (i = 1; i <= n; ++i)
    ans = min(ans, a[i][0]);
for (j = 1; j <= m; ++j)
    ans = min(ans, a[0][j]);
```
    - **核心实现思想**：先通过埃氏筛标记非质数，读入矩阵元素时，找到每个元素变为质数的操作次数，同时累加行和列的操作次数，最后取行和列操作次数总和的最小值。

- **作者：LYqwq（4星）**
    - **关键亮点**：使用欧拉筛筛选质数，代码注释详细，对读入优化使用模板函数，整体逻辑清晰。
    - **重点代码**：
```cpp
// 欧拉筛
template<typename T=int>
int getprime(T n){
    int cnt=0;
    for(int i=1; i<=n; i++) isprime[i]=1;
    isprime[1]=0;
    for(int i=2; i<=n; i++){
        if(isprime[i]) prime[++cnt]=i;
        for(int j=1; j<=cnt && prime[j]*i<=n; j++){
            isprime[i*prime[j]]=0;
            if(i%prime[j]==0) break;
        }
    }
    return cnt;
}
for(int i=1; i<=n; i++)
    for(int j=1; j<=m; j++)
        for(a[i][j]=read();!isprime[a[i][j]+f[i][j]]; f[i][j]++);
// 每列
for(int i=1; i<=n; i++,ans=min(ans,sum),sum=0) 
    for(int j=1; j<=m; j++)
        sum+=f[i][j];
// 每行
for(int i=1; i<=m; i++,ans=min(ans,sum),sum=0)
    for(int j=1; j<=n; j++)
        sum+=f[j][i]; 
```
    - **核心实现思想**：通过欧拉筛标记质数，读入矩阵元素时，计算每个元素变为质数的操作次数，分别统计行和列的操作次数总和并取最小值。

### 最优关键思路或技巧
1. **质数筛选**：选择合适的质数筛选算法，如埃氏筛或欧拉筛，能高效标记质数，为后续计算操作次数提供基础。
2. **操作次数统计优化**：在遍历矩阵元素计算操作次数时，同时累加行和列的操作次数，避免重复遍历矩阵统计，减少时间复杂度。

### 可拓展之处
此类题目可拓展到更多条件限制下的矩阵元素变换问题，类似算法套路是先预处理出相关数据（如本题的质数表），再针对每个元素进行计算，最后按要求统计结果。

### 洛谷相似题目推荐
1. **P1075 质因数分解**：通过分解质因数，加深对质数相关操作的理解。
2. **P3383 【模板】线性筛素数**：练习线性筛法筛选质数，巩固基础算法。
3. **P2615 神奇的幻方**：结合矩阵操作与质数判断，提升综合解题能力。

### 个人心得摘录与总结
1. **作者：q_sum**：在实现素数筛时，要注意数组范围，避免因范围过小导致统计素数不完整；循环方向要正确，否则会找错最接近的素数。总结为实现质数相关算法时，边界条件和逻辑方向需谨慎处理。 

---
处理用时：61.33秒