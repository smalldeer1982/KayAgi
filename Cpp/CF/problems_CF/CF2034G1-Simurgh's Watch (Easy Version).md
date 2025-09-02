---
title: "Simurgh's Watch (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2034G1
tag: ['动态规划 DP', '贪心', '构造']
---

# Simurgh's Watch (Easy Version)

## 题目描述

传说中，神鸟 [Simurgh](https://www.eavartravel.com/blog/2023/11/3/140727/simurgh/) 需要监管大片土地，她召集了 $ n $ 名警惕的战士帮忙。每个战士在特定的时间段内保持警戒，这个时间段用 $ [l_i, r_i] $ 表示，其中 $ l_i $ 和 $ r_i $ 分别为开始和结束时间，都是包含在内的正整数。

![](https://espresso.codeforces.com/e448e919c3f03a9c212cd45c8dcd8e2bb0be579c.webp)然而，Simurgh 的顾问 [Zal](https://asia-archive.si.edu/learn/shahnama/zal-and-the-simurgh/) 担心，如果多个战士在同一时间值守且都穿着相同颜色的衣服，会造成混淆。因此，为了防止这种情况发生，在任何时刻（可以是非整数时间）的战士中，至少要有一种颜色是由恰好一个战士穿着的。

我们的任务是：确定需要的最少颜色数，并为每个战士的时间段 $ [l_i, r_i] $ 分配一种颜色 $ c_i $，使得无论在哪一个时间 $ t $（被某个时间段包含在内），至少有一种颜色只出现在一个战士上。

## 输入格式

第一行包含一个整数 $ t $ （$ 1 \leq t \leq 10^4 $）——表示测试用例的数目。

每个测试用例包含以下内容：

- 第一行是一个整数 $ n $ （$ 1 \leq n \leq 2 \cdot 10^5 $）——表示 Simurgh 派出的战士数量。
- 接下来的 $ n $ 行中，每行包含两个整数 $ l_i $ 和 $ r_i $ （$ 1 \leq l_i \leq r_i \leq 10^9 $）——分别表示第 $ i $ 个战士的值班开始和结束时间。

所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例：

- 首先输出要使用的最少的颜色数量 $ k $。
- 接下来输出一行 $ n $ 个整数 $ c_i $（$ 1 \leq c_i \leq k $），代表为第 $ i $ 位战士分配的颜色。

## 说明/提示

可以将每个战士的值班时间段视作 X 轴上的一个区间：

- 在测试用例 1 中，有两个彼此不重叠的区间，因此可用相同颜色。
- 在测试用例 2 中，时间点 2 是公共的，因此不能使用相同颜色。
- 在测试用例 3 中，区间可以按下图所示进行着色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/dd56c79752790418adde70ef7aa40c52b2f8834f.png)

- 在测试用例 4 中，区间的着色方式如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/7c7aad3a3ba91ddaff1d673e62791383c4f77dec.png)

- 在测试用例 5 中，区间着色如下图所示。右侧图是错误的着色示例；在时间点 $ 5.5 $ 时，没有唯一颜色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/b8f2a4852b6af3f78d2729a80e0ad7497e55682a.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
1 2
3 4
2
1 2
2 3
3
1 4
2 5
3 6
5
1 4
2 8
3 7
5 10
6 9
5
1 5
2 6
3 7
4 7
6 7
```

### 输出

```
1
1 1
2
1 2
2
1 2 1
3
2 3 1 2 1
3
2 1 3 1 1
```

