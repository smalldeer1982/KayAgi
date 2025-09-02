# 题目信息

# Easy Scheduling

## 题目描述

Eonathan Eostar decided to learn the magic of multiprocessor systems. He has a full binary tree of tasks with height $ h $ . In the beginning, there is only one ready task in the tree — the task in the root. At each moment of time, $ p $ processes choose at most $ p $ ready tasks and perform them. After that, tasks whose parents were performed become ready for the next moment of time. Once the task becomes ready, it stays ready until it is performed.

You shall calculate the smallest number of time moments the system needs to perform all the tasks.

## 说明/提示

Let us consider the second test from the sample input. There is a full binary tree of height $ 3 $ and there are two processes. At the first moment of time, there is only one ready task, $ 1 $ , and $ p_1 $ performs it. At the second moment of time, there are two ready tasks, $ 2 $ and $ 3 $ , and the processes perform them. At the third moment of time, there are four ready tasks, $ 4 $ , $ 5 $ , $ 6 $ , and $ 7 $ , and $ p_1 $ performs $ 6 $ and $ p_2 $ performs $ 5 $ . At the fourth moment of time, there are two ready tasks, $ 4 $ and $ 7 $ , and the processes perform them. Thus, the system spends $ 4 $ moments of time to perform all the tasks.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1578E/98a14360f938976e2072b80e9c0ef58237d08d77.png)

## 样例 #1

### 输入

```
3
3 1
3 2
10 6```

### 输出

```
7
4
173```

# AI分析结果

### 题目内容重写
#### 题目描述
Eonathan Eostar 决定学习多处理器系统的魔法。他有一个高度为 $h$ 的满二叉树任务。开始时，树中只有一个就绪任务——根节点任务。在每一时刻，$p$ 个处理器最多选择 $p$ 个就绪任务并执行它们。执行后，那些父任务已被执行的任务将在下一时刻变为就绪状态。一旦任务变为就绪状态，它将保持就绪状态直到被执行。

你需要计算系统执行所有任务所需的最少时间时刻数。

#### 说明/提示
考虑样例输入中的第二个测试。有一个高度为 $3$ 的满二叉树和两个处理器。在第一个时刻，只有一个就绪任务 $1$，$p_1$ 执行它。在第二个时刻，有两个就绪任务 $2$ 和 $3$，处理器执行它们。在第三个时刻，有四个就绪任务 $4$、$5$、$6$ 和 $7$，$p_1$ 执行 $6$，$p_2$ 执行 $5$。在第四个时刻，有两个就绪任务 $4$ 和 $7$，处理器执行它们。因此，系统花费了 $4$ 个时刻来执行所有任务。

### 算法分类
模拟

### 题解分析与结论
所有题解的核心思路都是通过模拟任务执行的过程来计算最小时间时刻数。主要分为两种情况：
1. 当前层的节点数小于等于处理器数 $p$，则一次性执行完该层所有节点。
2. 当前层的节点数大于处理器数 $p$，则分多次执行，每次执行 $p$ 个节点。

### 所选高星题解
#### 题解1：DarkShadow（4星）
**关键亮点**：
- 通过预处理2的幂次来快速计算每层的节点数。
- 使用 `cnt1` 和 `cnt2` 分别记录剩余节点数和当前暴露的节点数，逻辑清晰。

**核心代码**：
```cpp
while(cnt1){
    if(cnt2<=q){
        cnt1-=cnt2,cnt2*=2ll,ans++;
        continue;
    }
    t=cnt2/(ll)(q),ans+=t,cnt1-=t*(ll)(q),cnt2-=t*(ll)(q),cnt2+=t*(ll)(q)*2ll,cnt2=min(cnt2,cnt1);
}
```

#### 题解2：Goodrage（4星）
**关键亮点**：
- 通过 `rdcnt` 数组存储每层的节点数，便于后续计算。
- 对特殊情况（$p=1$）进行了特判，提高了代码的鲁棒性。

**核心代码**：
```cpp
while(i<=n){
    if(rdcnt[i]<=m){
        steps++;
        i++;
    } else {
        int gone=pow(2.0,i-1)-1;
        int newnum=nodenum-gone;
        steps+=newnum/m;
        if(newnum%m!=0) steps++;
        break;
    }
}
```

#### 题解3：__int127（4星）
**关键亮点**：
- 使用 `ceil` 函数来处理剩余节点的执行次数，简化了代码逻辑。
- 通过 `gs` 变量记录已执行的节点数，便于计算剩余节点。

**核心代码**：
```cpp
for (long long i = 0; i < n; i++){
    if (pow(2, i) <= q){
        ans++;
        gs += pow(2, i);
    } else {
        break;
    }
}
ans += ceil(((double)num - gs) / q);
```

### 最优关键思路或技巧
- **预处理幂次**：通过预处理2的幂次来快速计算每层的节点数，减少了重复计算。
- **分层处理**：将问题分层处理，分别处理每层的节点数小于等于和大于处理器数的情况。
- **特判处理**：对特殊情况（如 $p=1$）进行特判，提高了代码的鲁棒性。

### 可拓展之处
- **多处理器调度**：可以扩展到更复杂的任务调度问题，如非满二叉树、任务优先级等。
- **并行计算**：可以进一步研究并行计算中的任务调度问题，优化处理器利用率。

### 推荐相似题目
1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
3. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)

### 个人心得摘录
- **调试经历**：在处理多层节点时，容易出现边界条件错误，需仔细检查每层的节点数和剩余节点数的计算。
- **顿悟感想**：通过分层处理和预处理幂次，可以大大简化问题的复杂度，提高代码的可读性和执行效率。

---
处理用时：31.39秒