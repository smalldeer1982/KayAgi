# 题目信息

# Ntarsis' Set

## 题目描述

Ntarsis has been given a set $ S $ , initially containing integers $ 1, 2, 3, \ldots, 10^{1000} $ in sorted order. Every day, he will remove the $ a_1 $ -th, $ a_2 $ -th, $ \ldots $ , $ a_n $ -th smallest numbers in $ S $ simultaneously.

What is the smallest element in $ S $ after $ k $ days?

## 说明/提示

For the first test case, each day the $ 1 $ -st, $ 2 $ -nd, $ 4 $ -th, $ 5 $ -th, and $ 6 $ -th smallest elements need to be removed from $ S $ . So after the first day, $ S $ will become $ \require{cancel} $ $ \{\cancel 1, \cancel 2, 3, \cancel 4, \cancel 5, \cancel 6, 7, 8, 9, \ldots\} = \{3, 7, 8, 9, \ldots\} $ . The smallest element is $ 3 $ .

For the second case, each day the $ 1 $ -st, $ 3 $ -rd, $ 5 $ -th, $ 6 $ -th and $ 7 $ -th smallest elements need to be removed from $ S $ . $ S $ will be changed as follows:

 Day $ S $ before $ S $ after1 $ \{\cancel 1, 2, \cancel 3, 4, \cancel 5, \cancel 6, \cancel 7, 8, 9, 10, \ldots \} $  $ \to $  $ \{2, 4, 8, 9, 10, \ldots\} $ 2 $ \{\cancel 2, 4, \cancel 8, 9, \cancel{10}, \cancel{11}, \cancel{12}, 13, 14, 15, \ldots\} $  $ \to $  $ \{4, 9, 13, 14, 15, \ldots\} $ 3 $ \{\cancel 4, 9, \cancel{13}, 14, \cancel{15}, \cancel{16}, \cancel{17}, 18, 19, 20, \ldots\} $  $ \to $  $ \{9, 14, 18, 19, 20, \ldots\} $ The smallest element left after $ k = 3 $ days is $ 9 $ .

## 样例 #1

### 输入

```
7
5 1
1 2 4 5 6
5 3
1 3 5 6 7
4 1000
2 3 4 5
9 1434
1 4 7 9 12 15 17 18 20
10 4
1 3 5 7 9 11 13 15 17 19
10 6
1 4 7 10 13 16 19 22 25 28
10 150000
1 3 4 5 10 11 12 13 14 15```

### 输出

```
3
9
1
12874
16
18
1499986```

# AI分析结果

### 题目内容
# Ntarsis' Set

## 题目描述

Ntarsis 有一个集合 $S$，初始时包含按升序排列的整数 $1, 2, 3, \ldots, 10^{1000}$。每天，他会同时删除集合 $S$ 中第 $a_1$ 小、第 $a_2$ 小、……、第 $a_n$ 小的数。

请问经过 $k$ 天后，集合 $S$ 中最小的元素是多少？

## 说明/提示

对于第一个测试用例，每天删除集合中第 $1$、$2$、$4$、$5$、$6$ 小的数。经过第一天后，集合变为 $\{3, 7, 8, 9, \ldots\}$，最小的元素是 $3$。

对于第二个测试用例，每天删除集合中第 $1$、$3$、$5$、$6$、$7$ 小的数。经过 $k=3$ 天后，集合中最小的元素是 $9$。

### 样例 #1

#### 输入

```
7
5 1
1 2 4 5 6
5 3
1 3 5 6 7
4 1000
2 3 4 5
9 1434
1 4 7 9 12 15 17 18 20
10 4
1 3 5 7 9 11 13 15 17 19
10 6
1 4 7 10 13 16 19 22 25 28
10 150000
1 3 4 5 10 11 12 13 14 15
```

#### 输出

```
3
9
1
12874
16
18
1499986
```

### 算法分类
二分

### 题解分析与结论

题目要求经过 $k$ 次删除操作后，集合 $S$ 中最小的元素。由于集合初始包含 $1$ 到 $10^{1000}$ 的数，直接模拟删除操作不可行。因此，大多数题解采用了二分查找或逆向模拟的思路。

#### 关键思路：
1. **二分查找**：通过二分查找确定最小的元素，检查某个数是否在 $k$ 次删除操作后仍然存在。
2. **逆向模拟**：从最后一步倒推，计算某个数在每次操作后的位置变化，最终确定其初始位置。

#### 难点：
1. **时间复杂度**：直接模拟删除操作的时间复杂度极高，无法通过。
2. **位置计算**：如何高效计算某个数在每次删除操作后的位置变化。

### 高星题解推荐

#### 1. 作者：Kedit2007 (赞：30)
- **星级**：5
- **关键亮点**：通过逆向模拟，从最后一步倒推，计算某个数在每次操作后的位置变化，时间复杂度为 $O(n + k)$。
- **核心代码**：
```cpp
void work()
{
    long long n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    long long cur = 1, index = 0;
    while (k--)
    {
        cur += index;
        while (index < n && arr[index] <= cur)
        {
            index++;
            cur++;
        }
    }
    cout << cur << '\n';
}
```
- **实现思想**：通过记录当前数的位置和操作数组的索引，逐步计算每次操作后的位置变化。

#### 2. 作者：Che_001 (赞：7)
- **星级**：4
- **关键亮点**：采用二分查找，检查某个数是否在 $k$ 次删除操作后仍然存在，时间复杂度为 $O(k \log nk)$。
- **核心代码**：
```cpp
bool check(long long mid)
{
    int point = n;
    for (int i = 1; i <= k; i++)
    {
        while (val[point] > mid)
            point--;
        mid -= point;
    }
    return mid > 0;
}
```
- **实现思想**：通过二分查找确定最小的数，检查其在 $k$ 次删除操作后是否仍然存在。

#### 3. 作者：_adil_ (赞：5)
- **星级**：4
- **关键亮点**：通过逆向模拟，计算某个数在每次操作后的位置变化，时间复杂度为 $O(n)$。
- **核心代码**：
```cpp
ll onepos = 1, cur = 1;
for (int i = 1; i <= k; i++)
{
    while (onepos > a[cur + 1] && cur + 1 <= n) { cur++; }
    onepos += cur;
}
cout << onepos << endl;
```
- **实现思想**：通过记录当前数的位置和操作数组的索引，逐步计算每次操作后的位置变化。

### 最优关键思路
通过逆向模拟，从最后一步倒推，计算某个数在每次操作后的位置变化，时间复杂度为 $O(n + k)$，是最优的解决方案。

### 可拓展之处
类似的问题可以通过逆向模拟或二分查找来解决，尤其是当直接模拟操作不可行时，逆向模拟是一种高效的解决方案。

### 推荐题目
1. [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
3. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)

### 个人心得
在解决类似问题时，逆向模拟和二分查找是非常有效的工具，尤其是在处理大规模数据时，直接模拟操作往往不可行。通过逆向模拟，可以大大降低时间复杂度，提高算法的效率。

---
处理用时：51.38秒