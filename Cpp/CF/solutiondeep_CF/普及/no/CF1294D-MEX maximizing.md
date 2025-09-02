# 题目信息

# MEX maximizing

## 题目描述

Recall that MEX of an array is a minimum non-negative integer that does not belong to the array. Examples:

- for the array $ [0, 0, 1, 0, 2] $ MEX equals to $ 3 $ because numbers $ 0, 1 $ and $ 2 $ are presented in the array and $ 3 $ is the minimum non-negative integer not presented in the array;
- for the array $ [1, 2, 3, 4] $ MEX equals to $ 0 $ because $ 0 $ is the minimum non-negative integer not presented in the array;
- for the array $ [0, 1, 4, 3] $ MEX equals to $ 2 $ because $ 2 $ is the minimum non-negative integer not presented in the array.

You are given an empty array $ a=[] $ (in other words, a zero-length array). You are also given a positive integer $ x $ .

You are also given $ q $ queries. The $ j $ -th query consists of one integer $ y_j $ and means that you have to append one element $ y_j $ to the array. The array length increases by $ 1 $ after a query.

In one move, you can choose any index $ i $ and set $ a_i := a_i + x $ or $ a_i := a_i - x $ (i.e. increase or decrease any element of the array by $ x $ ). The only restriction is that  $ a_i $ cannot become negative. Since initially the array is empty, you can perform moves only after the first query.

You have to maximize the MEX (minimum excluded) of the array if you can perform any number of such operations (you can even perform the operation multiple times with one element).

You have to find the answer after each of $ q $ queries (i.e. the $ j $ -th answer corresponds to the array of length $ j $ ).

Operations are discarded before each query. I.e. the array $ a $ after the $ j $ -th query equals to $ [y_1, y_2, \dots, y_j] $ .

## 说明/提示

In the first example:

- After the first query, the array is $ a=[0] $ : you don't need to perform any operations, maximum possible MEX is $ 1 $ .
- After the second query, the array is $ a=[0, 1] $ : you don't need to perform any operations, maximum possible MEX is $ 2 $ .
- After the third query, the array is $ a=[0, 1, 2] $ : you don't need to perform any operations, maximum possible MEX is $ 3 $ .
- After the fourth query, the array is $ a=[0, 1, 2, 2] $ : you don't need to perform any operations, maximum possible MEX is $ 3 $ (you can't make it greater with operations).
- After the fifth query, the array is $ a=[0, 1, 2, 2, 0] $ : you can perform $ a[4] := a[4] + 3 = 3 $ . The array changes to be $ a=[0, 1, 2, 2, 3] $ . Now MEX is maximum possible and equals to $ 4 $ .
- After the sixth query, the array is $ a=[0, 1, 2, 2, 0, 0] $ : you can perform $ a[4] := a[4] + 3 = 0 + 3 = 3 $ . The array changes to be $ a=[0, 1, 2, 2, 3, 0] $ . Now MEX is maximum possible and equals to $ 4 $ .
- After the seventh query, the array is $ a=[0, 1, 2, 2, 0, 0, 10] $ . You can perform the following operations: 
  - $ a[3] := a[3] + 3 = 2 + 3 = 5 $ ,
  - $ a[4] := a[4] + 3 = 0 + 3 = 3 $ ,
  - $ a[5] := a[5] + 3 = 0 + 3 = 3 $ ,
  - $ a[5] := a[5] + 3 = 3 + 3 = 6 $ ,
  - $ a[6] := a[6] - 3 = 10 - 3 = 7 $ ,
  - $ a[6] := a[6] - 3 = 7 - 3 = 4 $ .
  
   The resulting array will be $ a=[0, 1, 2, 5, 3, 6, 4] $ . Now MEX is maximum possible and equals to $ 7 $ .

## 样例 #1

### 输入

```
7 3
0
1
2
2
0
0
10```

### 输出

```
1
2
3
3
4
4
7```

## 样例 #2

### 输入

```
4 3
1
2
1
2```

### 输出

```
0
0
0
0```

# AI分析结果

### 题目重写
**MEX 最大化**

**题目描述**

回忆一下，数组的 MEX 是指数组中未出现的最小非负整数。例如：

- 对于数组 $[0, 0, 1, 0, 2]$，MEX 等于 $3$，因为数字 $0, 1$ 和 $2$ 都在数组中，而 $3$ 是未出现的最小非负整数；
- 对于数组 $[1, 2, 3, 4]$，MEX 等于 $0$，因为 $0$ 是未出现的最小非负整数；
- 对于数组 $[0, 1, 4, 3]$，MEX 等于 $2$，因为 $2$ 是未出现的最小非负整数。

你有一个空数组 $a=[]$（即长度为 0 的数组）。你还有一个正整数 $x$。

你还会收到 $q$ 次查询。第 $j$ 次查询包含一个整数 $y_j$，表示你需要将 $y_j$ 添加到数组中。每次查询后，数组长度增加 1。

在一次操作中，你可以选择任意索引 $i$ 并设置 $a_i := a_i + x$ 或 $a_i := a_i - x$（即对数组中的任意元素增加或减少 $x$）。唯一的限制是 $a_i$ 不能变为负数。由于初始数组为空，你只能在第一次查询后进行操作。

你的目标是通过任意次数的操作（甚至可以对一个元素进行多次操作）来最大化数组的 MEX（最小未出现非负整数）。

你需要在每次查询后找到答案（即第 $j$ 次查询对应的数组长度为 $j$ 时的答案）。

每次查询前的操作都会被重置。即第 $j$ 次查询后的数组 $a$ 等于 $[y_1, y_2, \dots, y_j]$。

### 算法分类
贪心

### 题解分析与结论
本题的核心在于通过贪心策略最大化 MEX。由于可以对数组中的元素进行加减 $x$ 的操作，因此每个元素的有效信息是其模 $x$ 的余数。通过维护每个余数的出现次数，可以逐步计算当前的 MEX。

### 高星题解
#### 1. 作者：YooLc407 (赞：10)
**星级：5**
**关键亮点：**
- 简洁明了地解释了 MEX 的计算方法。
- 通过模 $x$ 的余数来简化问题，使用数组记录每个余数的出现次数。
- 代码简洁高效，时间复杂度为 $O(q)$。

**核心代码：**
```cpp
int main() {
    int q, x, ans = 0;
    q = rd(); x = rd();
    for(int i = 1; i <= q; ++i) {
        int opt = rd();
        vis[opt % x] ++; // 记录添加的数字
        while(vis[ans % x])
            vis[ans++ % x]--; // 更新 MEX
        printf("%d\n", ans);
    }
    return 0;
}
```

#### 2. 作者：lzy120406 (赞：1)
**星级：4**
**关键亮点：**
- 通过模 $x$ 的余数来简化问题，使用数组记录每个余数的出现次数。
- 逐步更新 MEX，代码简洁高效。

**核心代码：**
```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q, x;
    cin >> q >> x;
    int mex = 0;
    while (q--) {
        int y;
        cin >> y;
        int mod = y % x;
        cnt[mod]++;
        // 更新 mex
        while (cnt[mex % x] > mex / x) {
            mex++;
        }
        cout << mex << '\n';
    }
    return 0;
}
```

#### 3. 作者：zhangyuxing (赞：3)
**星级：4**
**关键亮点：**
- 使用线段树维护每个余数的出现次数，时间复杂度为 $O(n \log x)$。
- 通过线段树的合并操作来更新 MEX，思路清晰。

**核心代码：**
```cpp
int main() {
    int in, i;
    read(n); read(x);
    build(0, x - 1, 1);
    for(i = 1; i <= n; ++i) {
        read(in);
        add(0, x - 1, in % x, 1);
        printf("%d\n", a[1].minn.v * x + a[1].minn.id);
    }
    return 0;
}
```

### 最优关键思路
通过模 $x$ 的余数来简化问题，维护每个余数的出现次数，逐步计算当前的 MEX。这种方法既高效又简洁，适用于类似的问题。

### 拓展思路
类似的问题可以通过模运算来简化，例如在需要最大化或最小化某个指标时，可以通过模运算将问题转化为更易处理的形式。

### 推荐题目
1. [P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

---
处理用时：37.56秒