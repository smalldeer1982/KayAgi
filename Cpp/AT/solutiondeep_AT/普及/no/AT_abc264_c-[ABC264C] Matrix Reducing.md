# 题目信息

# [ABC264C] Matrix Reducing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc264/tasks/abc264_c

$ H_1 $ 行 $ W_1 $ 列の行列 $ A $ と、$ H_2 $ 行 $ W_2 $ 列の行列 $ B $ が与えられます。

- $ 1\ \leq\ i\ \leq\ H_1 $ かつ $ 1\ \leq\ j\ \leq\ W_1 $ を満たす整数の組 $ (i,\ j) $ について、行列 $ A $ の $ i $ 行目 $ j $ 列目の要素は $ A_{i,\ j} $ です。
- $ 1\ \leq\ i\ \leq\ H_2 $ かつ $ 1\ \leq\ j\ \leq\ W_2 $ を満たす整数の組 $ (i,\ j) $ について、行列 $ B $ の $ i $ 行目 $ j $ 列目の要素は $ B_{i,\ j} $ です。

行列 $ A $ に対して、下記の $ 2 $ つの操作のうちどちらかを行うことを、好きなだけ（ $ 0 $ 回でも良い）繰り返すことができます。

- $ A $ の行を任意に $ 1 $ つ選んで削除する。
- $ A $ の列を任意に $ 1 $ つ選んで削除する。

行列 $ A $ を行列 $ B $ に一致させることができるかどうかを判定して下さい。

## 说明/提示

### 制約

- $ 1\ \leq\ H_2\ \leq\ H_1\ \leq\ 10 $
- $ 1\ \leq\ W_2\ \leq\ W_1\ \leq\ 10 $
- $ 1\ \leq\ A_{i,\ j}\ \leq\ 10^9 $
- $ 1\ \leq\ B_{i,\ j}\ \leq\ 10^9 $
- 入力中の値はすべて整数

### Sample Explanation 1

初期状態の行列 $ A $ から $ 2 $ 列目を削除すると、行列 $ A $ は ``` 1 3 4 5 6 8 9 10 11 13 14 15 16 18 19 20 ``` となります。そこからさらに $ 3 $ 行目を削除すると、行列 $ A $ は ``` 1 3 4 5 6 8 9 10 16 18 19 20 ``` となります。そこからさらに $ 1 $ 行目を削除すると、行列 $ A $ は ``` 6 8 9 10 16 18 19 20 ``` となります。そこからさらに $ 4 $ 列目を削除すると、行列 $ A $ は ``` 6 8 9 16 18 19 ``` となります。これは行列 $ B $ と一致します。 操作の繰り返しによって行列 $ A $ を行列 $ B $ に一致させることができるので `Yes` を出力します。

### Sample Explanation 2

どのように操作を行っても、 行列 $ A $ を行列 $ B $ に一致させることはできません。 よって、`No` を出力します。

## 样例 #1

### 输入

```
4 5

1 2 3 4 5

6 7 8 9 10

11 12 13 14 15

16 17 18 19 20

2 3

6 8 9

16 18 19```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 3

1 1 1

1 1 1

1 1 1

1 1

2```

### 输出

```
No```

# AI分析结果



# [ABC264C] Matrix Reducing

## 题目描述

给定两个矩阵 $A$（$H_1$ 行 $W_1$ 列）和 $B$（$H_2$ 行 $W_2$ 列），判断能否通过删除 $A$ 的任意多行和列，使得剩下的矩阵与 $B$ 完全一致。

### 输入格式
- 输入矩阵 $A$ 和 $B$ 的具体数值
- 矩阵元素取值范围：$1 \leq A_{i,j}, B_{i,j} \leq 10^9$

### 输出格式
- 如果可以通过删除操作使 $A$ 变为 $B$，输出 `Yes`，否则输出 `No`

## 算法分类
**枚举**

## 题解分析与结论

题目要求判断能否通过删除行和列使 $A$ 变为 $B$。由于矩阵尺寸最大为 $10 \times 10$，可采用暴力枚举所有可能的行和列组合，检查是否存在与 $B$ 完全匹配的情况。

### 关键思路与技巧
1. **组合枚举**：通过二进制掩码枚举所有可能的行和列选择组合。对于行选择，枚举 $H_1$ 中选 $H_2$ 行的所有可能；对于列选择，枚举 $W_1$ 中选 $W_2$ 列的所有可能。
2. **快速验证**：对每个组合进行逐元素比对，一旦发现匹配立即返回成功。

### 题解代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int H1, W1;
    cin >> H1 >> W1;
    vector<vector<int>> A(H1, vector<int>(W1));
    for (int i = 0; i < H1; ++i)
        for (int j = 0; j < W1; ++j)
            cin >> A[i][j];
    
    int H2, W2;
    cin >> H2 >> W2;
    vector<vector<int>> B(H2, vector<int>(W2));
    for (int i = 0; i < H2; ++i)
        for (int j = 0; j < W2; ++j)
            cin >> B[i][j];
    
    // 生成所有可能的行选择
    vector<vector<int>> row_choices;
    for (int mask = 0; mask < (1 << H1); ++mask) {
        if (__builtin_popcount(mask) != H2) continue;
        vector<int> rows;
        for (int i = 0; i < H1; ++i)
            if (mask & (1 << i)) rows.push_back(i);
        row_choices.push_back(rows);
    }
    
    // 生成所有可能的列选择
    vector<vector<int>> col_choices;
    for (int mask = 0; mask < (1 << W1); ++mask) {
        if (__builtin_popcount(mask) != W2) continue;
        vector<int> cols;
        for (int j = 0; j < W1; ++j)
            if (mask & (1 << j)) cols.push_back(j);
        col_choices.push_back(cols);
    }
    
    // 检查所有组合
    for (auto& rows : row_choices) {
        for (auto& cols : col_choices) {
            bool ok = true;
            for (int i = 0; i < H2; ++i) {
                for (int j = 0; j < W2; ++j) {
                    if (A[rows[i]][cols[j]] != B[i][j]) {
                        ok = false;
                        break;
                    }
                }
                if (!ok) break;
            }
            if (ok) {
                cout << "Yes\n";
                return 0;
            }
        }
    }
    cout << "No\n";
    return 0;
}
```

### 推荐相似题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036) - 组合枚举与条件判断
2. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706) - 枚举所有排列组合
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219) - 基于约束的组合搜索

---
处理用时：186.80秒