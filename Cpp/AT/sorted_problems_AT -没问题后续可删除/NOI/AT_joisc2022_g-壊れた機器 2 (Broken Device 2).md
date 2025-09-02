---
title: "壊れた機器 2 (Broken Device 2)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_joisc2022_g
tag: []
---

# 壊れた機器 2 (Broken Device 2)

## 题目描述

这是一道通信题。

### 题意

D-taro 会给 Anna 一个整数，目标就是让 Anna 将这个整数发送给 Bruno。

游戏开始时，Anna 声明了一个在 $1$ 到 $2000$ 之间的整数 $m$，接下来他们玩 $Q$ 轮游戏。第 $i$ 轮游戏的过程如下：

1. D-taro 向 Anna 给出一个整数 $A_i$。

2. Anna 向通信设备输入两个数组 $s_i,t_i$，数组的每个元素 $s_i,t_i$ 应当是 $0$ 或 $1$，并且两者的长度相同且均为某个 $1$ 到 $m$ 之间的整数。

3. 令 $u_i$ 为 $s_i$ 和 $t_i$ 经过**乱序归并**得到的结果，通信设备会向 Bruno 发送 $u_i$。

4. Bruno 告诉 D-taro 一个整数，如果这个整数和 $A_i$ 相同，Anna 和 Bruno 在这轮获胜。

以下是**乱序归并**的定义：

我们称数组 $Z$ 是数组 $X$ 和数组 $Y$ 经过乱序归并得到的结果当且仅当：存在一种划分方式，将 $Z$ 中的元素划成两个集合，满足：

- 第一个集合中的元素按在 $Z$ 中的位置顺次连接得到的数组是 $X$。
- 第二个集合中的元素按在 $Z$ 中的位置顺次连接得到的数组是 $Y$。

例如：数组 $[\underline{1},\underline{1},1,0,0,\underline{0}]$ 可以由数组 $[1,1,0]$ 和数组 $[1,0,0]$ 乱序归并得到。

请你实现 Anna 和 Bruno 的策略。

### 任务

你需要提交一份源文件，包括以下两个部分。

#### Anna

你必须引用 `Anna.h`。

这份代码需要实现 Anna 的策略，因此你需要实现如下过程：

```cpp
int Declare();
```

这个函数会在每个测试点评测开始时被调用一次。

函数的返回值是 Anna 声明的 $m$。$m$ 必须是 $1$ 到 $2000$ 之间的整数，否则程序将被判为 `Wrong Answer [1]`。

```cpp
std::pair < std::vector <int>, std::vector <int> > Anna(long long A);
```

在 `Declare` 被调用后，这个函数会被调用 $Q$ 次。第 $i$ 次调用对应第 $i$ 轮游戏的前两轮之间。

参数 $\texttt{A}$ 表示 D-taro 向 Anna 给出的整数。
这个函数的返回值应当是两个数组 $s_i,t_i$，即 Anna 向通信设备输入的字符串。$s_i,t_i$ 应当只包含字符 0 或 1，否则程序将被判为 `Wrong Answer [2]`。

数组 $s_i,t_i$ 的长度应当在 $1$ 和 $m$ 之间，否则程序将被判为 `Wrong Answer [3]`。数组 $s_i,t_i$ 应当具有相同的长度，否则程序将被判为 `Wrong Answer [4]`。

#### Bruno

你必须引用 `Bruno.h`。

这份代码需要实现 Bruno 的策略，因此你需要实现如下过程：
```cpp
long long Bruno(std::vector <int> u);
```

每当 Anna 将数组对输入设备，调用该函数一次，因此这个函数的第 $i$ 次调用对应游戏第 $i$ 轮的第 $3$ 步和第 $4$ 步之间的过程。

参数 $\texttt{u}$ 是第 $i$ 轮中，Bruno 接收到的字符串 $u_i$。返回值是 Bruno 向 D-taro 给出的数。返回值应当与 D-taro 向 Anna 给出的相同，否则你的程序将被判为 `Wrong Answer [5]`。

### 样例评测库

见附件下载中的 grader.cpp。

你可以通过如下命令编译样例交互库：
```cpp
g++ -std=gnu++17 -O2 -o grader grader.cpp Anna.cpp Bruno.cpp
```

## 输入格式

第一行一个整数 $Q$。

接下来 $Q$ 行每行一个整数 $A_i$。

## 输出格式

如果你的程序正确运行，样例交互库将会输出形如 `Accepted: m` 的信息，其中 
$m$ 为 Declare 的返回值。

否则会输出形如 `Wrong Answer [x]` 的信息返回错误编号。

## 说明/提示

样例评测库的乱序归并是使用伪随机数完成的，这意味着重复允许程序，乱序归并的方式是相同的。你可以通过添加运行参数来改变伪随机数种子，例如：
```cpp
./grader 2022
 ```
### 样例

#### input

```cpp
2
42
2000
```

#### explanation
|  |  |
| -----------: | -----------: |
|  |  |
|  |  |

|函数调用	|返回值 |
| :-----------: | :-----------: |
|Declare()	|4|
|Anna(42)	|([0, 0, 1, 0], [1, 1, 0, 1])|
|Bruno([1, 0, 0, 1, 0, 1, 0, 1])|	42|
|Anna(2000)|	([0, 1], [0, 0])|
|Bruno([0, 0, 1, 0])|	2000|

在这组样例中，进行了 $Q(=2)$ 轮游戏。


### 数据范围与评分方式

- $1\leq Q\leq 1000$
- $1\leq A_i\leq 10^{18}$

#### Subtasks

- $\text{(5 points) } A_i\leq 2000$
- $\text{(5 points) } A_i\leq 4\times 10^6$
- $\text{(3 points) } A_i\leq 10^7$
- $\text{(12 points) } A_i\leq 10^8$
- $\text{(15 points) } A_i\leq 10^{11}$
- $\text{(60 points)}$ 无特殊限制，评分方式如下：

这个子任务的得分是所有测试点得分的最小值。

对于某个测试点，他的得分由 $m$ 决定，如下表：

|$m$	|得分 |
| :-----------: | :-----------: |
|$201\leq m\leq 2000$	|$40-25\times \log_{10}\left(\frac{m}{200}\right)$|
|$161\leq m\leq 200$	|$40$|
|$156\leq m\leq 160$	|$44$|
|$151\leq m\leq 155$	|$48$|
|$146\leq m\leq 150$	|$52$|
|$141\leq m\leq 145$	|$56$|
|$m\leq 140$	|$60$|
保证得分的交互过程中，交互库分别不会使用超过 $\texttt{0.5s}$ 时间和 $\texttt{32MB}$ 空间。

时间限制：两份程序分别 $\texttt{2s}$。

空间限制：两份程序分别 $\texttt{512MB}$。



[附件](https://uoj.ac/download/problem/728/attachment.zip)

