---
title: "Data Recovery"
layout: "post"
diff: 普及/提高-
pid: CF413A
tag: []
---

# Data Recovery

## 题目描述

Not so long ago company R2 bought company R1 and consequently, all its developments in the field of multicore processors. Now the R2 laboratory is testing one of the R1 processors.

The testing goes in $ n $ steps, at each step the processor gets some instructions, and then its temperature is measured. The head engineer in R2 is keeping a report record on the work of the processor: he writes down the minimum and the maximum measured temperature in his notebook. His assistant had to write down all temperatures into his notebook, but (for unknown reasons) he recorded only $ m $ .

The next day, the engineer's assistant filed in a report with all the $ m $ temperatures. However, the chief engineer doubts that the assistant wrote down everything correctly (naturally, the chief engineer doesn't doubt his notes). So he asked you to help him. Given numbers $ n $ , $ m $ , $ min $ , $ max $ and the list of $ m $ temperatures determine whether you can upgrade the set of $ m $ temperatures to the set of $ n $ temperatures (that is add $ n-m $ temperatures), so that the minimum temperature was $ min $ and the maximum one was $ max $ .

## 输入格式

The first line contains four integers $ n,m,min,max $ $ (1<=m&lt;n<=100; 1<=min&lt;max<=100) $ . The second line contains $ m $ space-separated integers $ t_{i} $ $ (1<=t_{i}<=100) $ — the temperatures reported by the assistant.

Note, that the reported temperatures, and the temperatures you want to add can contain equal temperatures.

## 输出格式

If the data is consistent, print 'Correct' (without the quotes). Otherwise, print 'Incorrect' (without the quotes).

## 说明/提示

In the first test sample one of the possible initial configurations of temperatures is \[1, 2\].

In the second test sample one of the possible initial configurations of temperatures is \[2, 1, 3\].

In the third test sample it is impossible to add one temperature to obtain the minimum equal to 1 and the maximum equal to 3.

## 样例 #1

### 输入

```
2 1 1 2
1

```

### 输出

```
Correct

```

## 样例 #2

### 输入

```
3 1 1 3
2

```

### 输出

```
Correct

```

## 样例 #3

### 输入

```
2 1 1 3
2

```

### 输出

```
Incorrect

```

