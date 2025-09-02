# 题目信息

# Fill in the Matrix

## 题目描述

There is an empty matrix $ M $ of size $ n\times m $ .

Zhongkao examination is over, and Daniel would like to do some puzzle games. He is going to fill in the matrix $ M $ using permutations of length $ m $ . That is, each row of $ M $ must be a permutation of length $ m^\dagger $ .

Define the value of the $ i $ -th column in $ M $ as $ v_i=\operatorname{MEX}(M_{1,i},M_{2,i},\ldots,M_{n,i})^\ddagger $ . Since Daniel likes diversity, the beauty of $ M $ is $ s=\operatorname{MEX}(v_1,v_2,\cdots,v_m) $ .

You have to help Daniel fill in the matrix $ M $ and maximize its beauty.

 $ ^\dagger $ A permutation of length $ m $ is an array consisting of $ m $ distinct integers from $ 0 $ to $ m-1 $ in arbitrary order. For example, $ [1,2,0,4,3] $ is a permutation, but $ [0,1,1] $ is not a permutation ( $ 1 $ appears twice in the array), and $ [0,1,3] $ is also not a permutation ( $ m-1=2 $ but there is $ 3 $ in the array).

 $ ^\ddagger $ The $ \operatorname{MEX} $ of an array is the smallest non-negative integer that does not belong to the array. For example, $ \operatorname{MEX}(2,2,1)=0 $ because $ 0 $ does not belong to the array, and $ \operatorname{MEX}(0,3,1,2)=4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ appear in the array, but $ 4 $ does not.

## 说明/提示

In the first test case:

- $ v_1=\operatorname{MEX}(1,0,1,0)=2 $ ;
- $ v_2=\operatorname{MEX}(0,2,0,2)=1 $ ;
- $ v_3=\operatorname{MEX}(2,1,2,1)=0 $ .

Therefore, $ s=\operatorname{MEX}(2,1,0)=3 $ .

It can be shown that $ 3 $ is the maximum possible beauty of $ M $ .

In the second test case, any permutation will make $ s=2 $ .

In the third test case:

- $ v_1=\operatorname{MEX}(3,5,1,4,4,2)=0 $ ;
- $ v_2=\operatorname{MEX}(0,2,3,1,2,4)=5 $ ;
- $ v_3=\operatorname{MEX}(1,1,2,3,5,0)=4 $ ;
- $ v_4=\operatorname{MEX}(4,0,4,2,3,5)=1 $ ;
- $ v_5=\operatorname{MEX}(2,4,5,5,0,1)=3 $ ;
- $ v_6=\operatorname{MEX}(5,3,0,0,1,3)=2 $ .

Therefore, $ s=\operatorname{MEX}(0,5,4,1,3,2)=6 $ .

## 样例 #1

### 输入

```
4
4 3
1 16
6 6
2 1```

### 输出

```
3
1 0 2
0 2 1
1 0 2
0 2 1
2
14 7 15 4 10 0 8 6 1 2 3 5 9 11 12 13 
6
3 0 1 4 2 5 
5 2 1 0 4 3 
1 3 2 4 5 0 
4 1 3 2 5 0 
4 2 5 3 0 1 
2 4 0 5 1 3
0
0
0```

# AI分析结果

### 题目内容重写

#### 填充矩阵

##### 题目描述

有一个大小为 $n \times m$ 的空矩阵 $M$。

中考结束了，丹尼尔想做一些益智游戏。他打算用长度为 $m$ 的排列来填充矩阵 $M$。也就是说，$M$ 的每一行都必须是长度为 $m$ 的排列。

定义矩阵 $M$ 中第 $i$ 列的值为 $v_i = \operatorname{MEX}(M_{1,i}, M_{2,i}, \ldots, M_{n,i})$。由于丹尼尔喜欢多样性，矩阵 $M$ 的美丽程度为 $s = \operatorname{MEX}(v_1, v_2, \cdots, v_m)$。

你需要帮助丹尼尔填充矩阵 $M$，并**最大化**它的美丽程度。

##### 说明/提示

在第一个测试用例中：

- $v_1 = \operatorname{MEX}(1, 0, 1, 0) = 2$；
- $v_2 = \operatorname{MEX}(0, 2, 0, 2) = 1$；
- $v_3 = \operatorname{MEX}(2, 1, 2, 1) = 0$。

因此，$s = \operatorname{MEX}(2, 1, 0) = 3$。

可以证明，$3$ 是矩阵 $M$ 的最大可能美丽程度。

在第二个测试用例中，任何排列都会使 $s = 2$。

在第三个测试用例中：

- $v_1 = \operatorname{MEX}(3, 5, 1, 4, 4, 2) = 0$；
- $v_2 = \operatorname{MEX}(0, 2, 3, 1, 2, 4) = 5$；
- $v_3 = \operatorname{MEX}(1, 1, 2, 3, 5, 0) = 4$；
- $v_4 = \operatorname{MEX}(4, 0, 4, 2, 3, 5) = 1$；
- $v_5 = \operatorname{MEX}(2, 4, 5, 5, 0, 1) = 3$；
- $v_6 = \operatorname{MEX}(5, 3, 0, 0, 1, 3) = 2$。

因此，$s = \operatorname{MEX}(0, 5, 4, 1, 3, 2) = 6$。

##### 样例 #1

###### 输入

```
4
4 3
1 16
6 6
2 1
```

###### 输出

```
3
1 0 2
0 2 1
1 0 2
0 2 1
2
14 7 15 4 10 0 8 6 1 2 3 5 9 11 12 13 
6
3 0 1 4 2 5 
5 2 1 0 4 3 
1 3 2 4 5 0 
4 1 3 2 5 0 
4 2 5 3 0 1 
2 4 0 5 1 3
0
0
0
```

### 算法分类

**构造**

### 题解分析与结论

#### 综合分析

本题的核心是通过构造矩阵的每一行和每一列，使得最终计算出的 $s$ 最大化。题解的关键在于如何巧妙地排列每一行的元素，使得每一列的 $\operatorname{MEX}$ 值尽可能分散，从而使得最终的 $\operatorname{MEX}(v_1, v_2, \cdots, v_m)$ 最大化。

#### 题解对比

1. **SunnyYuan 的题解**：
   - **思路**：根据 $n$ 和 $m$ 的大小关系，分两种情况构造矩阵。当 $m \le n$ 时，构造一个循环排列的矩阵，使得每一列的 $\operatorname{MEX}$ 值从 $0$ 到 $m-1$ 不重复。当 $m > n$ 时，构造一个循环排列的矩阵，使得每一列的 $\operatorname{MEX}$ 值从 $0$ 到 $n$ 不重复。
   - **亮点**：思路清晰，代码实现简洁，能够处理不同情况。
   - **评分**：4.5星

2. **_299817_ 的题解**：
   - **思路**：通过构造一个大小为 $(n, n+1)$ 或 $(m-1, m)$ 的矩阵，然后根据 $n$ 和 $m$ 的关系进行扩展。当 $n \le m-1$ 时，先构造一个大小为 $(n, n+1)$ 的矩阵，然后对剩余的列进行填充。当 $n > m-1$ 时，先构造一个大小为 $(m-1, m)$ 的矩阵，然后对剩余的行进行填充。
   - **亮点**：思路较为复杂，但能够处理不同情况，代码实现较为详细。
   - **评分**：4星

#### 最优关键思路

通过循环排列的方式构造矩阵，使得每一列的 $\operatorname{MEX}$ 值尽可能分散，从而最大化最终的 $\operatorname{MEX}(v_1, v_2, \cdots, v_m)$。这种方法的核心在于利用排列的性质，确保每一列的 $\operatorname{MEX}$ 值不重复。

#### 可拓展之处

类似的问题可以通过构造特定的排列或矩阵来达到某种优化目标。例如，在矩阵填充问题中，可以通过排列组合来优化某些特定的目标函数。

#### 推荐题目

1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)

#### 个人心得

在构造矩阵时，循环排列是一种非常有效的方法，能够确保每一列的 $\operatorname{MEX}$ 值不重复，从而最大化最终的 $\operatorname{MEX}$。此外，在处理不同情况时，分情况讨论是解决问题的关键。

### 核心代码片段

```cpp
void solve() {
    cin >> n >> m;
    if (m == 1) {
        cout << "0\n";
        for (int i = 1; i <= n; i++) cout << "0\n";
        return;
    }
    if (n == 1) {
        cout << "2\n";
        for (int i = 0; i < m; i++) cout << i << ' ';
        cout << '\n';
        return;
    }
    vector<vector<int> > a(n + 1);
    for (int i = 0; i <= n; i++) {
        for (int j = -1; j < m; j++) {
            a[i].push_back(j);
        }
    }
    if (n < m) {
        for (int j = 1; j <= n + 1; j++) {
            for (int i = 0, st = j; i <= n; i++, st++) {
                a[i][j] = st % (n + 1);
            }
        }
        cout << n + 1 << '\n';
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cout << a[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    else {
        for (int j = 1; j <= m; j++) {
            for (int i = 0, st = j; i < m; i++, st++) {
                a[i][j] = st % m;
            }
        }
        cout << m << '\n';
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cout << a[min(i, m - 1)][j] << ' ';
            }
            cout << '\n';
        }
    }
}
```

这段代码的核心思想是通过循环排列的方式构造矩阵，确保每一列的 $\operatorname{MEX}$ 值不重复，从而最大化最终的 $\operatorname{MEX}$。

---
处理用时：48.49秒