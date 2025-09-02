# 题目信息

# Restoring the Duration of Tasks

## 题目描述

Recently, Polycarp completed $ n $ successive tasks.

For each completed task, the time $ s_i $ is known when it was given, no two tasks were given at the same time. Also given is the time $ f_i $ when the task was completed. For each task, there is an unknown value $ d_i $ ( $ d_i>0 $ ) — duration of task execution.

It is known that the tasks were completed in the order in which they came. Polycarp performed the tasks as follows:

- As soon as the very first task came, Polycarp immediately began to carry it out.
- If a new task arrived before Polycarp finished the previous one, he put the new task at the end of the queue.
- When Polycarp finished executing the next task and the queue was not empty, he immediately took a new task from the head of the queue (if the queue is empty — he just waited for the next task).

Find $ d_i $ (duration) of each task.

### 题目翻译

Polycarp（以下称为Pc）得到了 $n\ (1\le n\le2\times 10^5)$ 个任务。

每个任务有两个属性 $s_i$ 和 $f_i$，分别表示这个任务开始和结束的时间。

Pc在任务开始时间没到的时候什么都不会做，时间一到就会立马开始。

在任务期间，下一个任务来了Pc会把这个任务加到任务列表的末尾。

当处理完一个任务后，如果任务列表还有任务时，会立马处理第一个任务。

当处理完一个任务后，如果任务列表没有任务了，Pc什么都不会做直到下一个任务来临。

处理每个任务的时间就是原文中的 $d_i$。

测试数据个数 $t\ (1\le t\le 10^4)$。

**输入：**

第一行，$t$。

对于每一个测试数据：

第一行一个任务数 $n$，

第二行 $n$ 个正整数，表示 $s_1<s_2<s_2<...<s_n\ (0\le s_i\le 10^9)$，

第三行 $n$ 个正整数，表示 $f_1<f_2<f_3<...<f_n\ (s_i<f_i\le 10^9)$。

**输出：**

对于每一个测试数据，一行 $n$ 个正整数，表示 $d_i$。

## 说明/提示

First test case:

The queue is empty at the beginning: $ [ ] $ . And that's where the first task comes in. At time $ 2 $ , Polycarp finishes doing the first task, so the duration of the first task is $ 2 $ . The queue is empty so Polycarp is just waiting.

At time $ 3 $ , the second task arrives. And at time $ 7 $ , the third task arrives, and now the queue looks like this: $ [7] $ .

At the time $ 10 $ , Polycarp finishes doing the second task, as a result, the duration of the second task is $ 7 $ .

And at time $ 10 $ , Polycarp immediately starts doing the third task and finishes at time $ 11 $ . As a result, the duration of the third task is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1690C/d2350660c42c220190947ba223600b0328cd0bf5.png)An example of the first test case.

## 样例 #1

### 输入

```
4
3
0 3 7
2 10 11
2
10 15
11 16
9
12 16 90 195 1456 1569 3001 5237 19275
13 199 200 260 9100 10000 10914 91066 5735533
1
0
1000000000```

### 输出

```
2 7 1 
1 1 
1 183 1 60 7644 900 914 80152 5644467 
1000000000```

# AI分析结果

### 题目内容
# 恢复任务时长

## 题目描述
最近，Polycarp 完成了 $n$ 个连续的任务。

对于每个已完成的任务，已知其被给出的时间 $s_i$，且没有两个任务在同一时间被给出。同时也已知任务完成的时间 $f_i$。对于每个任务，存在一个未知值 $d_i$（$d_i > 0$），即任务执行的时长。

已知任务是按照它们到来的顺序完成的。Polycarp 按如下方式执行任务：
- 一旦第一个任务到来，Polycarp 立即开始执行它。
- 如果在 Polycarp 完成前一个任务之前有新任务到达，他会将新任务放在队列的末尾。
- 当 Polycarp 完成执行下一个任务且队列不为空时，他会立即从队列头部取出一个新任务（如果队列为空，他就只是等待下一个任务）。

请找出每个任务的 $d_i$（时长）。

### 题目翻译
Polycarp（以下称为 Pc）得到了 $n\ (1\le n\le2\times 10^5)$ 个任务。

每个任务有两个属性 $s_i$ 和 $f_i$，分别表示这个任务开始和结束的时间。

Pc 在任务开始时间没到的时候什么都不会做，时间一到就会立马开始。

在任务期间，下一个任务来了 Pc 会把这个任务加到任务列表的末尾。

当处理完一个任务后，如果任务列表还有任务时，会立马处理第一个任务。

当处理完一个任务后，如果任务列表没有任务了，Pc 什么都不会做直到下一个任务来临。

处理每个任务的时间就是原文中的 $d_i$。

测试数据个数 $t\ (1\le t\le 10^4)$。

**输入：**
第一行，$t$。

对于每一个测试数据：
第一行一个任务数 $n$，
第二行 $n$ 个正整数，表示 $s_1<s_2<s_2<...<s_n\ (0\le s_i\le 10^9)$，
第三行 $n$ 个正整数，表示 $f_1<f_2<f_3<...<f_n\ (s_i<f_i\le 10^9)$。

**输出：**
对于每一个测试数据，一行 $n$ 个正整数，表示 $d_i$。

## 说明/提示
第一个测试用例：
一开始队列是空的：$ [ ] $ 。然后第一个任务到来。在时间 $2$ 时，Polycarp 完成第一个任务，所以第一个任务的时长是 $2$ 。队列是空的，所以 Polycarp 只是等待。

在时间 $3$ 时，第二个任务到达。在时间 $7$ 时，第三个任务到达，现在队列看起来是这样：$ [7] $ 。

在时间 $10$ 时，Polycarp 完成第二个任务，结果，第二个任务的时长是 $7$ 。

在时间 $10$ 时，Polycarp 立即开始做第三个任务，并在时间 $11$ 时完成。结果，第三个任务的时长是 $1$ 。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1690C/d2350660c42c220190947ba223600b0328cd0bf5.png)第一个测试用例的示例。

## 样例 #1
### 输入
```
4
3
0 3 7
2 10 11
2
10 15
11 16
9
12 16 90 195 1456 1569 3001 5237 19275
13 199 200 260 9100 10000 10914 91066 5735533
1
0
1000000000
```

### 输出
```
2 7 1 
1 1 
1 183 1 60 7644 900 914 80152 5644467 
1000000000
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是围绕任务执行的规则来模拟计算每个任务的执行时长。主要要点在于判断当前任务与上一个任务的时间关系，进而确定当前任务的实际开始时间。难点在于准确理解任务执行的先后顺序以及队列处理任务的逻辑。不同题解在实现细节上略有不同，例如记录时间的方式、边界条件的处理等，但整体思路一致。

### 通用建议与扩展思路
通用建议：在处理这类模拟题时，要清晰梳理题目中的规则和逻辑，通过记录关键信息（如当前时间、上一个任务的结束时间等）来模拟整个过程。代码实现时注意边界条件的处理，确保逻辑的完整性。
扩展思路：类似题目可能会增加任务的限制条件，如任务优先级、资源限制等，解题时需根据新规则调整模拟逻辑。也可能会改变任务到达和处理的模式，如并行处理部分任务等，这就需要更复杂的逻辑判断和数据结构来实现。

### 洛谷相似题目推荐
- [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：简单的模拟题目，通过给定条件模拟陶陶摘苹果的过程。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同包装铅笔的价格和数量，模拟计算购买一定数量铅笔的最优方案，涉及简单的逻辑判断和计算。
- [P5718 三角形分类](https://www.luogu.com.cn/problem/P5718)：根据输入的三角形三边长度，模拟判断三角形类型，考验对几何条件的模拟实现。 

---
处理用时：43.96秒