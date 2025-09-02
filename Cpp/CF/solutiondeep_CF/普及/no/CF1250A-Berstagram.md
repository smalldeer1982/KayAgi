# 题目信息

# Berstagram

## 题目描述

**题意简述**



给定两个序列 $a=[a_1,a_2,\dots,a_m]$ 和 $b=[b_1,b_2,\dots,b_n]$，其中 $b_i$ 的初始值为 $i$，$a_i$ 的初始值将由键盘读入。对于每个 $a_i$，若 $b_j=a_i$，则将 $b_j$ 与 $b_{j-1}$ 的值调换（若 $j=1$，则序列不变）。

## 样例 #1

### 输入

```
3 5
3 2 1 3 3
```

### 输出

```
1 2
2 3
1 3
```

## 样例 #2

### 输入

```
10 6
7 3 5 7 3 6
```

### 输出

```
1 2
2 3
1 3
4 7
4 5
6 7
5 7
8 8
9 9
10 10
```

# AI分析结果

### 题目重写
**题目名称**: Berstagram

**题目描述**:

给定两个序列 $a=[a_1,a_2,\dots,a_m]$ 和 $b=[b_1,b_2,\dots,b_n]$，其中 $b_i$ 的初始值为 $i$，$a_i$ 的初始值将由键盘读入。对于每个 $a_i$，若 $b_j=a_i$，则将 $b_j$ 与 $b_{j-1}$ 的值调换（若 $j=1$，则序列不变）。

### 算法分类
模拟

### 题解分析与结论
本题的核心在于模拟序列 $b$ 的交换过程，并在每次交换后更新每个数字的最大和最小位置。三个题解都采用了类似的方法，即通过维护每个数字的位置信息来实现高效的交换和更新。

#### 题解对比
1. **Withershine** (5星)
   - **关键亮点**: 使用结构体存储数字的最小值和最大值，并通过 `tag` 数组记录每个数字的位置，实现了高效的交换和更新。
   - **代码实现**: 通过 `swap` 函数交换位置，并更新 `tag` 数组和结构体中的 `minn` 和 `maxn`。
   - **个人心得**: 作者提到最初的暴力解法无法通过大数据，通过优化思路将复杂度降低了一个数量级。

2. **Goodrage** (4星)
   - **关键亮点**: 使用 `ori` 数组记录序列，`pos` 数组记录每个数字的位置，`mx` 和 `mn` 数组记录最大和最小位置。
   - **代码实现**: 通过 `swap` 函数交换位置，并更新 `pos`、`mx` 和 `mn` 数组。
   - **个人心得**: 作者提到题目 Remotejudge 可能有问题，但在 CF 上通过了测试。

3. **ChenZQ** (4星)
   - **关键亮点**: 使用 `id` 数组记录每个数字的位置，`mi` 和 `mx` 数组记录最小和最大位置。
   - **代码实现**: 通过 `swap` 函数交换位置，并更新 `id`、`mi` 和 `mx` 数组。
   - **个人心得**: 作者提到每个数最多最少都是出现一次，因此可以通过数组直接记录位置。

### 最优关键思路
最优的思路是通过维护每个数字的位置信息（如 `tag` 或 `id` 数组），并在每次交换后更新该数字的位置及其最大和最小位置。这种方法避免了暴力解法的高复杂度，实现了高效的模拟过程。

### 可拓展之处
类似的问题可以通过维护位置信息来优化模拟过程，例如在处理序列交换、排序等问题时，可以通过记录每个元素的位置来减少时间复杂度。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

### 重点代码片段
```cpp
// Withershine 的代码片段
a = read();
ll now = tag[a]; // 数字a现在的位置
ll last = now - 1; // now的上一个位置
if(last == 0) {
    continue;
}
swap(b[now], b[last]);
tag[a] = last;
tag[b[now].num] = now;
b[last].minn = min(b[last].minn, last);
b[now].maxn = max(b[now].maxn, now);
```

```cpp
// Goodrage 的代码片段
int tmppos = pos[tmp]; // 这个数字的对应位置
if(tmppos != 1) {
    int other = ori[tmppos - 1]; // 它前面的数
    swap(ori[tmppos - 1], ori[tmppos]); // 改变原本的数列里的位置
    pos[tmp] = tmppos - 1;
    pos[other] = tmppos; // 改变记录位置的数列
    mx[tmp] = max(mx[tmp], pos[tmp]);
    mn[tmp] = min(mn[tmp], pos[tmp]);
    mx[other] = max(mx[other], pos[other]);
    mn[other] = min(mn[other], pos[other]); // 更新最大位置与最小位置
}
```

```cpp
// ChenZQ 的代码片段
int k = id[a[i]]; // 现获取下标
if(k == 1) continue; // 如果下标为一就不操作
swap(b[k], b[k - 1]); // 交换原数组中的数
mi[a[i]] = min(mi[a[i]], k - 1); // 往前移了一格，更新最小值
mx[b[k]] = max(mx[b[k]], k); // 前面的往后挪了一格，更新最大值
swap(id[a[i]], id[b[k]]); // 交换下标
```

---
处理用时：35.44秒