---
title: "Hongcow's Game"
layout: "post"
diff: 普及+/提高
pid: CF744B
tag: ['交互题']
---

# Hongcow's Game

## 题目描述

This is an interactive problem. In the interaction section below you will see the information about flushing the output.

In this problem, you will be playing a game with Hongcow. How lucky of you!

Hongcow has a hidden $ n $ by $ n $ matrix $ M $ . Let $ M_{i,j} $ denote the entry $ i $ -th row and $ j $ -th column of the matrix. The rows and columns are labeled from $ 1 $ to $ n $ .

The matrix entries are between $ 0 $ and $ 10^{9} $ . In addition, $ M_{i,i}=0 $ for all valid $ i $ . Your task is to find the minimum value along each row, excluding diagonal elements. Formally, for each $ i $ , you must find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF744B/60abf7e287a9efbab7664bfef9cac9ebdb2e6b1f.png).

To do this, you can ask Hongcow some questions.

A question consists of giving Hongcow a subset of distinct indices $ {w_{1},w_{2},...,w_{k}} $ , with $ 1<=k<=n $ . Hongcow will respond with $ n $ integers. The $ i $ -th integer will contain the minimum value of $ min_{1<=j<=k}M_{i,wj} $ .

You may only ask Hongcow at most $ 20 $ questions — he thinks you only need that many questions answered.

When you are ready to answer, print out a single integer $ -1 $ on its own line, then $ n $ integers on the next line. The $ i $ -th integer should be the minimum value in the $ i $ -th row of the matrix, excluding the $ i $ -th element. Do not forget to flush the final answer as well. Printing the answer does not count as asking a question.

You will get Wrong Answer verdict if

- Your question or answers are not in the format described in this statement.
- You ask strictly more than $ 20 $ questions.
- Your question contains duplicate indices.
- The value of $ k $ in your question does not lie in the range from $ 1 $ to $ n $ , inclusive.
- Your final answer is not correct.

 You will get Idleness Limit Exceeded if you don't print anything or if you forget to flush the output, including for the final answer (more info about flushing output below).

## 输入格式

The first line of input will contain a single integer $ n $ ( $ 2<=n<=1,000 $ ).

## 输出格式

To print the final answer, print out the string -1 on its own line. Then, the next line should contain $ n $ integers. The $ i $ -th integer should be the minimum value of the $ i $ -th row of the matrix, excluding elements on the diagonal. Do not forget to flush your answer!

Interaction

To ask a question, print out a single integer $ k $ on its own line, denoting the size of your subset. Then, the next line should contain $ k $ integers $ w_{1},w_{2},...\ w_{k} $ . Note, you must flush your output to get a response.

Hongcow will respond by printing out a line with $ n $ integers. The $ i $ -th integer in this line represents the minimum value of $ M_{i,wj} $ where $ j $ is between $ 1 $ and $ k $ .

You may only ask a question at most $ 20 $ times, otherwise, you will get Wrong Answer.

To flush you can use (just after printing an integer and end-of-line):

- fflush(stdout) in C++;
- System.out.flush() in Java;
- stdout.flush() in Python;
- flush(output) in Pascal;
- See the documentation for other languages.

Hacking To hack someone, use the following format

`<br></br>n<br></br>M_{1,1} M_{1,2} ... M_{1,n}<br></br>M_{2,1} M_{2,2} ... M_{2,n}<br></br>...<br></br>M_{n,1} M_{n,2} ... M_{n,n}<br></br>`Of course, contestant programs will not be able to see this input.

## 说明/提示

In the first sample, Hongcow has the hidden matrix

`<br></br>[<br></br> [0, 3, 2],<br></br> [5, 0, 7],<br></br> [4, 8 ,0],<br></br>]<br></br>`Here is a more readable version demonstrating the interaction. The column on the left represents Hongcow, while the column on the right represents the contestant.

`<br></br>3<br></br>              3<br></br>              1 2 3<br></br>0 0 0<br></br>              1<br></br>              3<br></br>2 7 0<br></br>              2<br></br>              1 2<br></br>0 0 4<br></br>              1<br></br>              2<br></br>3 0 8<br></br>              1<br></br>              1<br></br>0 5 4<br></br>              -1<br></br>              2 5 4<br></br>`For the second sample, it is possible for off-diagonal elements of the matrix to be zero.

## 样例 #1

### 输入

```
3
0 0 0
2 7 0
0 0 4
3 0 8
0 5 4
```

### 输出

```
3
1 2 3
1
3
2
1 2
1
2
1
1
-1
2 5 4

```

## 样例 #2

### 输入

```
2
0 0
0 0
```

### 输出

```
1
2
1
1
-1
0 0
```

