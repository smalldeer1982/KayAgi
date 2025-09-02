# 题目信息

# Jumps

## 题目描述

You are standing on the $ \mathit{OX} $ -axis at point $ 0 $ and you want to move to an integer point $ x > 0 $ .

You can make several jumps. Suppose you're currently at point $ y $ ( $ y $ may be negative) and jump for the $ k $ -th time. You can:

- either jump to the point $ y + k $
- or jump to the point $ y - 1 $ .

What is the minimum number of jumps you need to reach the point $ x $ ?

## 说明/提示

In the first test case $ x = 1 $ , so you need only one jump: the $ 1 $ -st jump from $ 0 $ to $ 0 + 1 = 1 $ .

In the second test case $ x = 2 $ . You need at least three jumps:

- the $ 1 $ -st jump from $ 0 $ to $ 0 + 1 = 1 $ ;
- the $ 2 $ -nd jump from $ 1 $ to $ 1 + 2 = 3 $ ;
- the $ 3 $ -rd jump from $ 3 $ to $ 3 - 1 = 2 $ ;

Two jumps are not enough because these are the only possible variants:

- the $ 1 $ -st jump as $ -1 $ and the $ 2 $ -nd one as $ -1 $ — you'll reach $ 0 -1 -1 =-2 $ ;
- the $ 1 $ -st jump as $ -1 $ and the $ 2 $ -nd one as $ +2 $ — you'll reach $ 0 -1 +2 = 1 $ ;
- the $ 1 $ -st jump as $ +1 $ and the $ 2 $ -nd one as $ -1 $ — you'll reach $ 0 +1 -1 = 0 $ ;
- the $ 1 $ -st jump as $ +1 $ and the $ 2 $ -nd one as $ +2 $ — you'll reach $ 0 +1 +2 = 3 $ ;

In the third test case, you need two jumps: the $ 1 $ -st one as $ +1 $ and the $ 2 $ -nd one as $ +2 $ , so $ 0 + 1 + 2 = 3 $ .

In the fourth test case, you need three jumps: the $ 1 $ -st one as $ -1 $ , the $ 2 $ -nd one as $ +2 $ and the $ 3 $ -rd one as $ +3 $ , so $ 0 - 1 + 2 + 3 = 4 $ .

## 样例 #1

### 输入

```
5
1
2
3
4
5```

### 输出

```
1
3
2
3
4```

# AI分析结果

### 题目内容重写

#### 跳跃

**题目描述**

你站在 $ \mathit{OX} $ 轴上的点 $ 0 $ 处，想要移动到一个整数点 $ x > 0 $。

你可以进行多次跳跃。假设你当前位于点 $ y $（$ y $ 可能为负数），并且正在进行第 $ k $ 次跳跃。你可以选择：

- 跳到点 $ y + k $
- 或者跳到点 $ y - 1 $。

问：你最少需要多少次跳跃才能到达点 $ x $？

**说明/提示**

在第一个测试用例中，$ x = 1 $，所以你只需要一次跳跃：第 $ 1 $ 次跳跃从 $ 0 $ 到 $ 0 + 1 = 1 $。

在第二个测试用例中，$ x = 2 $。你至少需要三次跳跃：

- 第 $ 1 $ 次跳跃从 $ 0 $ 到 $ 0 + 1 = 1 $；
- 第 $ 2 $ 次跳跃从 $ 1 $ 到 $ 1 + 2 = 3 $；
- 第 $ 3 $ 次跳跃从 $ 3 $ 到 $ 3 - 1 = 2 $；

两次跳跃是不够的，因为只有以下几种可能：

- 第 $ 1 $ 次跳跃为 $ -1 $，第 $ 2 $ 次跳跃为 $ -1 $ —— 你将到达 $ 0 -1 -1 =-2 $；
- 第 $ 1 $ 次跳跃为 $ -1 $，第 $ 2 $ 次跳跃为 $ +2 $ —— 你将到达 $ 0 -1 +2 = 1 $；
- 第 $ 1 $ 次跳跃为 $ +1 $，第 $ 2 $ 次跳跃为 $ -1 $ —— 你将到达 $ 0 +1 -1 = 0 $；
- 第 $ 1 $ 次跳跃为 $ +1 $，第 $ 2 $ 次跳跃为 $ +2 $ —— 你将到达 $ 0 +1 +2 = 3 $；

在第三个测试用例中，你需要两次跳跃：第 $ 1 $ 次跳跃为 $ +1 $，第 $ 2 $ 次跳跃为 $ +2 $，所以 $ 0 + 1 + 2 = 3 $。

在第四个测试用例中，你需要三次跳跃：第 $ 1 $ 次跳跃为 $ -1 $，第 $ 2 $ 次跳跃为 $ +2 $，第 $ 3 $ 次跳跃为 $ +3 $，所以 $ 0 - 1 + 2 + 3 = 4 $。

**样例 #1**

**输入**

```
5
1
2
3
4
5
```

**输出**

```
1
3
2
3
4
```

### 算法分类
**数学**

### 题解分析与结论

本题的核心是通过数学分析找到最小跳跃次数。各题解的主要思路是通过枚举或数学公式找到满足条件的最小跳跃次数，并通过调整跳跃策略来达到目标点。

#### 题解对比与评分

1. **Allanljx (5星)**
   - **关键亮点**：通过枚举找到最小的跳跃次数，利用数学公式判断是否需要额外跳跃。代码简洁，思路清晰。
   - **核心代码**：
     ```cpp
     for(i=0;s<n||s==n+1;s+=++i){}
     cout<<i<<endl;
     ```
   - **总结**：通过枚举找到最小的 $i$ 使得 $s \geq n$，然后判断是否需要额外跳跃。

2. **TEoS (4星)**
   - **关键亮点**：通过数学公式找到最小的 $p$ 使得 $\frac{p(p+1)}{2} \geq x$，然后判断是否需要额外跳跃。思路清晰，代码简洁。
   - **核心代码**：
     ```cpp
     for(p=1;p*(p+1)<n*2;p++);
     printf("%d\n",p+(p*(p+1)/2-n==1));
     ```
   - **总结**：通过数学公式找到最小的 $p$，然后判断是否需要额外跳跃。

3. **_HwH_ (4星)**
   - **关键亮点**：通过预处理步数序列，利用二分查找找到最小跳跃次数。思路清晰，代码简洁。
   - **核心代码**：
     ```cpp
     ll pos=std::lower_bound(s+1,s+cnt+1,n)-s;
     if(s[pos]==n) ans=pos;
     else if(s[pos]-n-1==0) ans=pos+1;
     else ans=pos;
     ```
   - **总结**：通过预处理步数序列，利用二分查找找到最小跳跃次数，然后判断是否需要额外跳跃。

### 最优关键思路
通过数学公式或枚举找到最小的跳跃次数，然后判断是否需要额外跳跃。这种方法避免了复杂的模拟过程，直接通过数学计算得到结果，效率高且代码简洁。

### 拓展思路
类似的问题可以通过数学分析找到规律，避免复杂的模拟过程。例如，通过枚举或数学公式找到满足条件的最小步数，然后通过调整策略达到目标。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)
3. [P1011 车站](https://www.luogu.com.cn/problem/P1011)

---
处理用时：37.30秒