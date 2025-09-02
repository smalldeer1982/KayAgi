# 题目信息

# [ABC187D] Choose Me

## 题目描述

### 题目简述
农场一年一度的选农场主开始啦！

选举的人有 Farmer John 和 Farmer Jack，全农场有 $N$ 个片区，第 $i$ 个片区有 $a_i$ 只 Jack 的奶牛，$b_i$ 只 John 的奶牛，没有其他人的奶牛。

John 要在各个片区发放牧草。

如果 John 在一个区发放牧草，那么所有 John 和 Jack 的奶牛都会投票支持 John，另一方面，如果 John 不在该区发放牧草，所有 Jack 的奶牛投票支持 Jack ，而 John 的奶牛不参与投票。

求John 想赢得比 Jack 多的选票，至少要去发放牧草的片区数量 $X$ 。

## 样例 #1

### 输入

```
4

2 1

2 2

5 1

1 3```

### 输出

```
1```

## 样例 #2

### 输入

```
5

2 1

2 1

2 1

2 1

2 1```

### 输出

```
3```

## 样例 #3

### 输入

```
1

273 691```

### 输出

```
1```

# AI分析结果

### 题目内容重写

【题目描述】

农场一年一度的选农场主开始啦！

选举的人有 Farmer John 和 Farmer Jack，全农场有 $N$ 个片区，第 $i$ 个片区有 $a_i$ 只 Jack 的奶牛，$b_i$ 只 John 的奶牛，没有其他人的奶牛。

John 要在各个片区发放牧草。

如果 John 在一个区发放牧草，那么所有 John 和 Jack 的奶牛都会投票支持 John，另一方面，如果 John 不在该区发放牧草，所有 Jack 的奶牛投票支持 Jack ，而 John 的奶牛不参与投票。

求John 想赢得比 Jack 多的选票，至少要去发放牧草的片区数量 $X$ 。

### 样例 #1

#### 输入

```
4

2 1

2 2

5 1

1 3
```

#### 输出

```
1
```

### 样例 #2

#### 输入

```
5

2 1

2 1

2 1

2 1

2 1
```

#### 输出

```
3
```

### 样例 #3

#### 输入

```
1

273 691
```

#### 输出

```
1
```

### 算法分类

贪心

### 综合分析与结论

本题的核心问题是如何选择最少的片区发放牧草，使得 John 的选票超过 Jack。通过分析可以发现，选择发放牧草的片区对选票的影响是确定的，因此可以通过贪心策略来选择最优的片区。

### 题解分析

由于暂无题解，以下为通用建议与扩展思路：

1. **贪心策略**：对于每个片区，计算发放牧草和不发放牧草对选票的差值，选择差值最大的片区优先发放牧草。这样可以最大化每次选择对选票的贡献，从而减少需要发放牧草的片区数量。

2. **实现步骤**：
   - 计算每个片区的差值：`diff[i] = (a[i] + b[i]) - (a[i]) = b[i]`。
   - 按照差值从大到小排序。
   - 依次选择差值最大的片区，直到 John 的选票超过 Jack。

3. **代码实现**：
   ```cpp
   #include <iostream>
   #include <vector>
   #include <algorithm>

   using namespace std;

   int main() {
       int N;
       cin >> N;
       vector<pair<int, int>> regions(N);
       for (int i = 0; i < N; ++i) {
           cin >> regions[i].first >> regions[i].second;
       }

       // 计算差值并排序
       vector<int> diff(N);
       for (int i = 0; i < N; ++i) {
           diff[i] = regions[i].second;
       }
       sort(diff.begin(), diff.end(), greater<int>());

       int total = 0, count = 0;
       for (int i = 0; i < N; ++i) {
           total += diff[i];
           count++;
           if (total > 0) {
               break;
           }
       }

       cout << count << endl;
       return 0;
   }
   ```

### 推荐题目

1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007) - 贪心策略的应用。
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心与优先队列的结合。
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 贪心策略在时间安排中的应用。

### 总结

本题通过贪心策略，选择对选票贡献最大的片区优先发放牧草，从而在最少的选择次数内达到目标。这种策略在类似的优化问题中具有广泛的应用，值得深入理解和掌握。

---
处理用时：21.40秒