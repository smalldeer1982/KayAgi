# 题目信息

# Obtain a Permutation

## 题目描述

You are given a rectangular matrix of size $ n \times m $ consisting of integers from $ 1 $ to $ 2 \cdot 10^5 $ .

In one move, you can:

- choose any element of the matrix and change its value to any integer between $ 1 $ and $ n \cdot m $ , inclusive;
- take any column and shift it one cell up cyclically (see the example of such cyclic shift below).

A cyclic shift is an operation such that you choose some $ j $ ( $ 1 \le j \le m $ ) and set $ a_{1, j} := a_{2, j}, a_{2, j} := a_{3, j}, \dots, a_{n, j} := a_{1, j} $ simultaneously.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1294E/8565157bd76bb2dbe391e7f12ac2946eff0ed96a.png) Example of cyclic shift of the first column You want to perform the minimum number of moves to make this matrix look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1294E/f0a34fa55590e79e2f0e0af3c39b0d9ee30b43c2.png)In other words, the goal is to obtain the matrix, where $ a_{1, 1} = 1, a_{1, 2} = 2, \dots, a_{1, m} = m, a_{2, 1} = m + 1, a_{2, 2} = m + 2, \dots, a_{n, m} = n \cdot m $ (i.e. $ a_{i, j} = (i - 1) \cdot m + j $ ) with the minimum number of moves performed.

## 说明/提示

In the first example, you can set $ a_{1, 1} := 7, a_{1, 2} := 8 $ and $ a_{1, 3} := 9 $ then shift the first, the second and the third columns cyclically, so the answer is $ 6 $ . It can be shown that you cannot achieve a better answer.

In the second example, the matrix is already good so the answer is $ 0 $ .

In the third example, it is enough to shift the second column cyclically twice to obtain a good matrix, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
3 3
3 2 1
1 2 3
4 5 6```

### 输出

```
6```

## 样例 #2

### 输入

```
4 3
1 2 3
4 5 6
7 8 9
10 11 12```

### 输出

```
0```

## 样例 #3

### 输入

```
3 4
1 6 3 4
5 10 7 8
9 2 11 12```

### 输出

```
2```

# AI分析结果

### 题目翻译
## 获取一个排列

### 题目描述
给定一个大小为 $n \times m$ 的矩形矩阵，矩阵中的整数范围是从 $1$ 到 $2 \cdot 10^5$。

在一次移动中，你可以：
- 选择矩阵中的任意一个元素，并将其值更改为 $1$ 到 $n \cdot m$（包含）之间的任意整数；
- 选择任意一列，并将其向上循环移动一个单元格（见下面这种循环移动的示例）。

循环移动是这样一种操作：你选择某个 $j$（$1 \le j \le m$），并同时设置 $a_{1, j} := a_{2, j}, a_{2, j} := a_{3, j}, \dots, a_{n, j} := a_{1, j}$。

![循环移动第一列的示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1294E/8565157bd76bb2dbe391e7f12ac2946eff0ed96a.png) 

你希望通过最少的移动次数，使这个矩阵变成如下形式：

![目标矩阵](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1294E/f0a34fa55590e79e2f0e0af3c39b0d9ee30b43c2.png)

换句话说，目标是通过最少的移动次数得到一个矩阵，其中 $a_{1, 1} = 1, a_{1, 2} = 2, \dots, a_{1, m} = m, a_{2, 1} = m + 1, a_{2, 2} = m + 2, \dots, a_{n, m} = n \cdot m$（即 $a_{i, j} = (i - 1) \cdot m + j$）。

### 说明/提示
在第一个示例中，你可以将 $a_{1, 1}$ 设为 $7$，$a_{1, 2}$ 设为 $8$，$a_{1, 3}$ 设为 $9$，然后循环移动第一列、第二列和第三列，所以答案是 $6$。可以证明，你无法得到更好的答案。

在第二个示例中，矩阵已经符合要求，所以答案是 $0$。

在第三个示例中，只需将第二列循环移动两次，就可以得到符合要求的矩阵，所以答案是 $2$。

### 样例 #1
#### 输入
```
3 3
3 2 1
1 2 3
4 5 6
```
#### 输出
```
6
```

### 样例 #2
#### 输入
```
4 3
1 2 3
4 5 6
7 8 9
10 11 12
```
#### 输出
```
0
```

### 样例 #3
#### 输入
```
3 4
1 6 3 4
5 10 7 8
9 2 11 12
```
#### 输出
```
2
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是发现不同列之间的操作互不影响，所以对每列单独处理。对于每一列，枚举所有可能的上移次数，计算每种上移次数下不需要修改的元素个数，进而得到该列达到目标状态所需的最小操作次数，最后将每列的最小操作次数累加得到最终答案。

各题解的算法要点和难点解决方式类似，主要差异在于代码实现细节，如输入输出方式、数组的使用等。

### 所选题解
- **syksykCCC（5星）**
    - **关键亮点**：思路清晰，详细阐述了 $same$ 数组的含义和计算方法，代码注释清晰，可读性高。
- **清尘（4星）**
    - **关键亮点**：思路简洁明了，代码实现较为精炼，同时提醒了判断 $x <= n * m$ 的重要性。
- **星落云川（4星）**
    - **关键亮点**：详细分析了模拟方法的复杂度并给出优化思路，提醒了注意数组越界的问题。

### 重点代码
#### syksykCCC 的核心代码
```cpp
for(int j = 1; j <= m; j++)
{
    int tans = INT_MAX;
    for(int i = 0; i < n; i++) same[i] = 0;
    for(int i = 1; i <= n; i++)
    {
        if(a[i][j] < j || a[i][j] > n * m || (a[i][j] - j) % m != 0) continue;
        int k = (a[i][j] - j) / m + 1;
        same[(i - k + n) % n]++;
    }
    for(int i = 0; i < n; i++) tans = min(tans, i + n - same[i]);
    ans += tans;
}
```
**核心实现思想**：对于每一列，先初始化 $same$ 数组为 $0$，然后遍历该列的每个元素，判断其是否应该在该列，如果是，则计算其移动到目标位置所需的移动次数，并将对应 $same$ 数组的值加 $1$。最后枚举所有移动次数，计算最小操作次数并累加到最终答案中。

#### 清尘的核心代码
```cpp
for (int j = 1; j <= m; ++j) {
    for (int i = 0; i < n; ++i) c[i] = 0;
    int ans = 1e9, tmp = 0;
    for (int i = 1; i <= n; ++i) {
        int t = v[i][j - 1];
        if ((t - j) % m == 0 && t <= n * m) 
            ++c[(i - (t - j) / m - 1 + n) % n];
    }
    for (int i = 0; i < n; ++i) ans = min (ans, i + n - c[i]);
    res += ans;
}
```
**核心实现思想**：与 syksykCCC 的思路类似，对于每一列，初始化计数数组 $c$，遍历该列元素，判断是否应该在该列，若是则更新计数数组，最后枚举移动次数求最小操作次数并累加。

#### 星落云川的核心代码
```c
int cmp( int n, int m, int j )
{
    int move, realN, min=2<<29;
    for( int i=1; i<=n; i++ ){
        if( row[i] % m != j%m ) continue;
        if( row[i]<1 || row[i]>n*m ) continue;
        realN = (row[i]-j) / m + 1;
        move = i - realN;
        if( move<0 ) move += n;
        cnt[ move ]++;
    }
    for( int i=0; i<n; i++ )
        min = min < n-cnt[i]+i ? min : n-cnt[i]+i;
    return min;
}
```
**核心实现思想**：对于某一列，遍历该列元素，判断是否应该在该列，若是则计算移动次数并更新计数数组 $cnt$，最后枚举移动次数求最小操作次数。

### 关键思路或技巧
- 发现不同列之间操作互不影响，将问题转化为对每列单独处理，降低问题复杂度。
- 使用数组记录每种上移次数下不需要修改的元素个数，避免了模拟上移操作，将时间复杂度从 $O(mn^2)$ 优化到 $O(nm)$。
- 注意判断元素是否在有效范围内，避免数组越界。

### 拓展思路
同类型题目可能会有不同的矩阵操作规则或目标矩阵形式，但解题的关键思路可能类似，即分析操作的特点，找到独立的处理单元，然后枚举所有可能的操作情况，计算每种情况下的代价，最终得到最优解。

### 推荐题目
- [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)

### 个人心得
- **清尘**：比赛时没判断 $x <= n * m$，查了半天也没发现问题，提醒我们在处理这类问题时要注意元素范围的判断，谨防数组越界。
- **星落云川**：有惨痛的教训，没判断元素小于 $nm$ 导致数组越界，再次强调了注意元素范围判断的重要性。 

---
处理用时：56.19秒