---
title: "IITD1 - Another Sorting Algorithm"
layout: "post"
diff: 难度0
pid: SP7565
tag: []
---

# IITD1 - Another Sorting Algorithm

## 题目描述

Dexter 一直对数字进行一些奇怪的操作。  
昨天，他发现了一种新的排序算法，并写出了如下伪代码来将长度为 $N$ 的序列（从 0 开始编号）按升序排序：

```
Seq = 给定的 N 个数字组成的序列

swap(i, j)
{
    temp = Seq[i]
    Seq[i] = Seq[j]
    Seq[j] = temp
}

reverse(i, j)
{
    对 k 从 i 到 (i + j - 1) / 2 执行
        swap(k, i + j - k)
}

sort()
{
    对 i 从 0 到 N-1 执行
        对 j 从 i+1 到 N-1 执行
            如果 Seq[i] > Seq[j] ，则执行 reverse(i, j)
}
```

然而，Dexter 并不知道，他的妹妹 Dee Dee 在外层循环中又加入了一个循环，使得改动后的 `sort` 函数变成了这样：

```
sort()
{
    对 i 从 0 到 N-1 执行
        对 j 从 i+1 到 N-1 执行
            如果 Seq[i] > Seq[j] ，则执行 reverse(i, j)

        对 j 从 N-2 到 i+2 执行
            reverse(i+1, j)
}
```

今天，Dexter 测试程序时发现，虽然程序能够正确排序，但运行时间比预期要长（Dee Dee 总是有办法！）。  
你需要帮助估算程序运行所需的时间。给定 Dexter 想要排序的序列，任务是计算 `swap` 函数被调用的次数。

### 输入格式

第一行是一个整数 $N$，表示序列的长度。接下来的 $N$ 行中，每行包含一个整数，第 $i$ 行对应 $Seq[i]$ 的值。

### 输出格式

输出一个整数，表示 `swap` 函数被调用的总次数。

### 数据范围与提示

- $1 \leq N \leq 4000$
- $0 \leq Seq[i] \leq 1,000,000,000$

### 样例输入

```
5
1
2
3
4
5
```

### 样例输出

```
4
```

 **本翻译由 AI 自动生成**

