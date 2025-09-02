# 题目信息

# Insert a Progression

## 题目描述

给你一个 $n$ 个数的序列 $a_1,a_2,...,a_n$，同时给你 $x$ 个正整数 $1,2,...,x$。

你要将这 $x$ 个数插入到序列 $a$ 中，每个数可以插在序列首位，末位以及任意两个元素中间。

设最后得到的序列为 $a'$，定义它的分数为相邻两个元素之间的绝对值之和，也就是 $\sum\limits_{i=1}^{n+x-1}|a_i'-a_{i+1}'|$。

求最小分数。

## 说明/提示

样例 $4$ 组询问（构造不一定唯一）：

- $ \underline{1}, \underline{2}, \underline{3}, \underline{4}, \underline{5}, 10 $
- $ \underline{7}, 7, \underline{6}, \underline{4}, 2, \underline{2}, \underline{1}, \underline{3}, \underline{5}, \underline{8}, 10 $
- $ 6, \underline{1}, 1, \underline{2}, 5, 7, 3, 3, 9, 10, 10, 1 $
- $ 1, 3, \underline{1}, 1, 2, \underline{2}, \underline{3}, \underline{4}, \underline{5}, \underline{6}, \underline{7}, \underline{8}, \underline{9}, \underline{10} $

## 样例 #1

### 输入

```
4
1 5
10
3 8
7 2 10
10 2
6 1 5 7 3 3 9 10 10 1
4 10
1 3 1 2```

### 输出

```
9
15
31
13```

# AI分析结果

### 题目内容重写
#### 题目描述
给定一个包含 $n$ 个数的序列 $a_1,a_2,...,a_n$，同时给定 $x$ 个正整数 $1,2,...,x$。

你需要将这 $x$ 个数插入到序列 $a$ 中，每个数可以插入到序列的首位、末位或任意两个元素之间。

设最后得到的序列为 $a'$，定义它的分数为相邻两个元素之间的绝对值之和，即 $\sum\limits_{i=1}^{n+x-1}|a_i'-a_{i+1}'|$。

求最小分数。

#### 说明/提示
样例 $4$ 组询问（构造不一定唯一）：
- $ \underline{1}, \underline{2}, \underline{3}, \underline{4}, \underline{5}, 10 $
- $ \underline{7}, 7, \underline{6}, \underline{4}, 2, \underline{2}, \underline{1}, \underline{3}, \underline{5}, \underline{8}, 10 $
- $ 6, \underline{1}, 1, \underline{2}, 5, 7, 3, 3, 9, 10, 10, 1 $
- $ 1, 3, \underline{1}, 1, 2, \underline{2}, \underline{3}, \underline{4}, \underline{5}, \underline{6}, \underline{7}, \underline{8}, \underline{9}, \underline{10} $

#### 样例 #1
##### 输入
```
4
1 5
10
3 8
7 2 10
10 2
6 1 5 7 3 3 9 10 10 1
4 10
1 3 1 2
```

##### 输出
```
9
15
31
13
```

### 算法分类
贪心

### 题解分析与结论
所有题解的核心思路都是通过贪心策略，尽量减少插入数字对序列分数的影响。具体来说，插入的数字如果在原序列的最小值和最大值之间，则对分数没有影响。因此，只需要考虑插入 $1$ 和 $x$ 的位置，其他数字可以无影响地插入。

### 所选高分题解
#### 题解1：作者 tuzhewen (5星)
**关键亮点**：
1. 通过分析发现，插入的数字如果在 $[min, max]$ 范围内，对分数没有影响。
2. 只需要考虑插入 $1$ 和 $x$ 的位置，其他数字可以无影响地插入。
3. 通过循环寻找插入 $1$ 和 $x$ 的最佳位置，最小化对分数的影响。

**核心代码**：
```cpp
if(minn>1) {
    int res1=min(a[1]-1,a[n]-1);
    F(i,2,n) res1=min(res1,a[i]+a[i-1]-2-abs(a[i]-a[i-1]));
    ans+=res1;
}
if(x>maxn) {
    int res2=min(x-a[1],x-a[n]);
    F(i,2,n) res2=min(res2,2*x-a[i]-a[i-1]-abs(a[i]-a[i-1]));
    ans+=res2;
}
```
**实现思想**：通过循环遍历序列，计算插入 $1$ 和 $x$ 的最小影响，并将其加到原序列的分数上。

#### 题解2：作者 Tx_Lcy (4星)
**关键亮点**：
1. 通过例子说明，插入 $2$ 到 $x-1$ 的数字可以无影响地插入。
2. 只需要考虑插入 $1$ 和 $x$ 的位置，其他数字可以无影响地插入。
3. 通过循环寻找插入 $1$ 和 $x$ 的最佳位置，最小化对分数的影响。

**核心代码**：
```cpp
for (int i=2;i<=n;i++)
    cx=min(cx,abs(x-a[i-1])+abs(x-a[i])-abs(a[i]-a[i-1])),
    cy=min(cy,abs(1-a[i-1])+abs(1-a[i])-abs(a[i]-a[i-1]));
if (x>maxx) ans+=cx;
if (mina>1) ans+=cy;
```
**实现思想**：通过循环遍历序列，计算插入 $1$ 和 $x$ 的最小影响，并将其加到原序列的分数上。

### 最优关键思路
1. **贪心策略**：通过分析发现，插入的数字如果在 $[min, max]$ 范围内，对分数没有影响，因此只需要考虑插入 $1$ 和 $x$ 的位置。
2. **循环优化**：通过循环遍历序列，计算插入 $1$ 和 $x$ 的最小影响，并将其加到原序列的分数上。

### 可拓展之处
类似的问题可以通过贪心策略，尽量减少插入数字对序列的影响。例如，插入数字使得序列的某种性质（如和、积等）最小或最大。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：31.53秒