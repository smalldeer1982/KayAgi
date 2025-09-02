# 题目信息

# World Cup

## 题目描述

Allen wants to enter a fan zone that occupies a round square and has $ n $ entrances.

There already is a queue of $ a_i $ people in front of the $ i $ -th entrance. Each entrance allows one person from its queue to enter the fan zone in one minute.

Allen uses the following strategy to enter the fan zone:

- Initially he stands in the end of the queue in front of the first entrance.
- Each minute, if he is not allowed into the fan zone during the minute (meaning he is not the first in the queue), he leaves the current queue and stands in the end of the queue of the next entrance (or the first entrance if he leaves the last entrance).

Determine the entrance through which Allen will finally enter the fan zone.

## 说明/提示

In the first example the number of people (not including Allen) changes as follows: $ [\textbf{2}, 3, 2, 0] \to [1, \textbf{2}, 1, 0] \to [0, 1, \textbf{0}, 0] $ . The number in bold is the queue Alles stands in. We see that he will enter the fan zone through the third entrance.

In the second example the number of people (not including Allen) changes as follows: $ [\textbf{10}, 10] \to [9, \textbf{9}] \to [\textbf{8}, 8] \to [7, \textbf{7}] \to [\textbf{6}, 6] \to \\ [5, \textbf{5}] \to [\textbf{4}, 4] \to [3, \textbf{3}] \to [\textbf{2}, 2] \to [1, \textbf{1}] \to [\textbf{0}, 0] $ .

In the third example the number of people (not including Allen) changes as follows: $ [\textbf{5}, 2, 6, 5, 7, 4] \to [4, \textbf{1}, 5, 4, 6, 3] \to [3, 0, \textbf{4}, 3, 5, 2] \to \\ [2, 0, 3, \textbf{2}, 4, 1] \to [1, 0, 2, 1, \textbf{3}, 0] \to [0, 0, 1, 0, 2, \textbf{0}] $ .

## 样例 #1

### 输入

```
4
2 3 2 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
10 10
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6
5 2 6 5 7 4
```

### 输出

```
6
```

# AI分析结果

【题目内容中文重写】
# 世界杯

## 题目描述

Allen 想进入一个占据圆形广场的球迷区，该球迷区有 $ n $ 个入口。

每个入口前已经有 $ a_i $ 个人在排队。每个入口每分钟允许其队列中的一个人进入球迷区。

Allen 使用以下策略进入球迷区：

- 最初，他站在第一个入口的队列末尾。
- 每分钟，如果他没有被允许进入球迷区（意味着他不是队列中的第一个），他就会离开当前队列，并站在下一个入口的队列末尾（如果他从最后一个入口离开，则回到第一个入口）。

确定 Allen 最终将通过哪个入口进入球迷区。

## 说明/提示

在第一个示例中，人数（不包括 Allen）变化如下：$ [\textbf{2}, 3, 2, 0] \to [1, \textbf{2}, 1, 0] \to [0, 1, \textbf{0}, 0] $。加粗的数字是 Allen 所在的队列。我们看到他将通过第三个入口进入球迷区。

在第二个示例中，人数（不包括 Allen）变化如下：$ [\textbf{10}, 10] \to [9, \textbf{9}] \to [\textbf{8}, 8] \to [7, \textbf{7}] \to [\textbf{6}, 6] \to \\ [5, \textbf{5}] \to [\textbf{4}, 4] \to [3, \textbf{3}] \to [\textbf{2}, 2] \to [1, \textbf{1}] \to [\textbf{0}, 0] $。

在第三个示例中，人数（不包括 Allen）变化如下：$ [\textbf{5}, 2, 6, 5, 7, 4] \to [4, \textbf{1}, 5, 4, 6, 3] \to [3, 0, \textbf{4}, 3, 5, 2] \to \\ [2, 0, 3, \textbf{2}, 4, 1] \to [1, 0, 2, 1, \textbf{3}, 0] \to [0, 0, 1, 0, 2, \textbf{0}] $。

## 样例 #1

### 输入

```
4
2 3 2 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
10 10
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6
5 2 6 5 7 4
```

### 输出

```
6
```

【算法分类】
模拟

【题解分析与结论】
该题的核心逻辑是模拟 Allen 在多个入口之间的移动过程，直到他能够进入球迷区。题解主要分为两种思路：一种是直接模拟整个过程，另一种是通过数学计算来优化模拟过程。

1. **直接模拟**：通过记录时间 $t$ 和 Allen 的位置 $p$，每分钟更新队列中的人数，直到 Allen 能够进入球迷区。这种方法直观但效率较低，适用于小规模数据。
2. **数学优化**：通过计算每个入口的队列在多少分钟后会变为 0，找到 Allen 最早能够进入的入口。这种方法避免了重复模拟，效率更高。

【所选高星题解】
1. **题解作者：Siteyava_145 (4星)**
   - **关键亮点**：通过数学公式计算每个入口的队列在多少分钟后会变为 0，避免了重复模拟，效率高。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++){
         ans[i]=(a[i]-i+n)/n; // 计算第几轮会变为0
     }
     int minn=0x7fffffff,pos;
     for(int i=1;i<=n;i++){
         if(ans[i]<minn){
             minn=ans[i];
             pos=i;
         }
     }
     cout<<pos;
     ```

2. **题解作者：wanghanjun (4星)**
   - **关键亮点**：同样通过数学计算优化模拟过程，代码简洁明了。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++){
         a[i]=(x-i+n)/n; // 计算Allen最多走到这个点上几次
     }
     for(int i=1;i<=n;i++){
         if(mina>a[i]){
             id=i;
             mina=a[i];
         }
     }
     cout<<id<<endl;
     ```

【最优关键思路】
通过数学公式 `(a[i] - i + n) / n` 计算每个入口的队列在多少分钟后会变为 0，从而找到 Allen 最早能够进入的入口。这种方法避免了重复模拟，大大提高了效率。

【拓展思路】
类似的问题可以通过数学优化来减少模拟的次数，特别是在涉及到周期性或重复性操作时。例如，计算某个事件在多长时间后会再次发生，或者某个状态在多长时间后会发生变化。

【推荐题目】
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：38.42秒