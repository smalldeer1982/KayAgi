---
title: "CERC07S - Robotic Sort"
layout: "post"
diff: 省选/NOI-
pid: SP2059
tag: []
---

# CERC07S - Robotic Sort

## 题目描述

Somewhere deep in the Czech Technical University buildings, there are laboratories for examin- ing mechanical and electrical properties of various materials. In one of yesterday's presentations, you have seen how was one of the laboratories changed into a new multimedia lab. But there are still others, serving to their original purposes.

In this task, you are to write software for a robot that handles samples in such a laboratory. Imagine there are material samples lined up on a running belt. The samples have different heights, which may cause troubles to the next processing unit. To eliminate such troubles, we need to sort the samples by their height into the ascending order.

Reordering is done by a mechanical robot arm, which is able to pick up any number of consecutive samples and turn them round, such that their mutual order is reversed. In other words, one robot operation can reverse the order of samples on positions between A and B.

A possible way to sort the samples is to find the position of the smallest one (P\_1) and reverse the order between positions 1 and P\_1, which causes the smallest sample to become first. Then we find the second one on position P\_2 and reverse the order between 2 and P\_2. Then the third sample is located etc.

![example](https://cdn.luogu.com.cn/upload/vjudge_pic/SP2059/2f7348f6bf17c3916201e5a2e7ac372850f12509.png)The picture shows a simple example of 6 samples. The smallest one is on the 4th position, therefore, the robot arm reverses the first 4 samples. The second smallest sample is the last one, so the next robot operation will reverse the order of five samples on positions 2-6. The third step will be to reverse the samples 3-4, etc.

Your task is to find the correct sequence of reversal operations that will sort the samples using the above algorithm. If there are more samples with the same height, their mutual order must be preserved: the one that was given first in the initial order must be placed before the others in the final order too.

## 输入格式

The input consists of several scenarios. Each scenario is described by two lines. The first line contains one integer number N, the number of samples, 1 <= N <= 100 000. The second line lists exactly N space-separated positive integers, they specify the heights of individual samples and their initial order.

The last scenario is followed by a line containing zero.

## 输出格式

For each scenario, output one line with exactly N integers P\_1,P\_2,...P\_N, separated by a space. Each P\_i must be an integer (1 <= P\_i <= N) giving the position of the i-th sample just before the i-th reversal operation.

Note that if a sample is already on its correct position P\_i, you should output the number P\_i anyway, indicating that the "interval between P\_i and P\_i" (a single sample) should be reversed.

## 样例 #1

### 输入

```
6
3 4 5 1 6 2
4
3 3 2 1
0
```

### 输出

```
4 6 4 5 6 6
4 2 4 4
```

