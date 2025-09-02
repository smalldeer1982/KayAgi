# 题目信息

# Sequence and Swaps

## 题目描述

You are given a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ , and an integer $ x $ . Your task is to make the sequence $ a $ sorted (it is considered sorted if the condition $ a_1 \le a_2 \le a_3 \le \dots \le a_n $ holds).

To make the sequence sorted, you may perform the following operation any number of times you want (possibly zero): choose an integer $ i $ such that $ 1 \le i \le n $ and $ a_i > x $ , and swap the values of $ a_i $ and $ x $ .

For example, if $ a = [0, 2, 3, 5, 4] $ , $ x = 1 $ , the following sequence of operations is possible:

1. choose $ i = 2 $ (it is possible since $ a_2 > x $ ), then $ a = [0, 1, 3, 5, 4] $ , $ x = 2 $ ;
2. choose $ i = 3 $ (it is possible since $ a_3 > x $ ), then $ a = [0, 1, 2, 5, 4] $ , $ x = 3 $ ;
3. choose $ i = 4 $ (it is possible since $ a_4 > x $ ), then $ a = [0, 1, 2, 3, 4] $ , $ x = 5 $ .

Calculate the minimum number of operations you have to perform so that $ a $ becomes sorted, or report that it is impossible.

## 样例 #1

### 输入

```
6
4 1
2 3 5 4
5 6
1 1 3 4 4
1 10
2
2 10
11 9
2 10
12 11
5 18
81 324 218 413 324```

### 输出

```
3
0
0
-1
1
3```

# AI分析结果

### 题目中文重写
# 序列与交换

## 题目描述
给定一个由 $n$ 个整数 $a_1, a_2, \dots, a_n$ 组成的序列 $a$，以及一个整数 $x$。你的任务是使序列 $a$ 有序（若满足 $a_1 \le a_2 \le a_3 \le \dots \le a_n$，则认为该序列有序）。

为了使序列有序，你可以根据需要多次执行以下操作（也可以不执行）：选择一个整数 $i$，满足 $1 \le i \le n$ 且 $a_i > x$，然后交换 $a_i$ 和 $x$ 的值。

例如，若 $a = [0, 2, 3, 5, 4]$，$x = 1$，则可以进行以下操作序列：
1. 选择 $i = 2$（因为 $a_2 > x$），此时 $a = [0, 1, 3, 5, 4]$，$x = 2$；
2. 选择 $i = 3$（因为 $a_3 > x$），此时 $a = [0, 1, 2, 5, 4]$，$x = 3$；
3. 选择 $i = 4$（因为 $a_4 > x$），此时 $a = [0, 1, 2, 3, 4]$，$x = 5$。

计算使 $a$ 有序所需执行的最少操作次数，若无法使 $a$ 有序，则报告 -1。

## 样例 #1
### 输入
```
6
4 1
2 3 5 4
5 6
1 1 3 4 4
1 10
2
2 10
11 9
2 10
12 11
5 18
81 324 218 413 324
```

### 输出
```
3
0
0
-1
1
3
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕如何通过最少的交换操作使序列有序展开。大部分题解采用贪心策略，依据“若 $a_i>x$ 但不交换，后面的数无法通过交换使序列有序”这一关键性质，从前往后扫描序列，遇到可交换的元素就进行交换。部分题解还通过先找出最后一个乱序位置，减少不必要的操作。而 `_•́へ•́╬_` 的题解使用动态规划，定义状态并进行状态转移，但代码复杂度较高。

### 所选题解
- **作者：TEoS (4星)**
    - **关键亮点**：思路清晰，先找出最后一个乱序位置，然后在该位置之前进行交换操作，最后检查序列是否有序，代码简洁易懂。
- **作者：Composite_Function (4星)**
    - **关键亮点**：同样采用贪心策略，先找出无序部分，再进行交换操作，逻辑清晰，代码规范。
- **作者：zztqwq (4星)**
    - **关键亮点**：给出了“若 $a_i>x$ 但不交换，后面的数无法通过交换使序列有序”的证明，理论依据充分，代码实现简单直接。

### 重点代码
#### 作者：TEoS
```c++
while(T--)
{
    scanf("%d%d",&n,&x);b=ans=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]<a[i-1])
            b=i;//最后一个乱序的位置
    }
    if(b)
    {
        for(int i=1;i<=b;i++)
            if(x<a[i])
                swap(x,a[i]),ans++;//遍历 [1,b] 并处理
        for(int i=1;i<=n;i++)
            if(a[i]<a[i-1])
                b=0;//仍然乱序
        printf(!b?"-1\n":"%d\n",ans);
    }
    else//有序
        puts("0");
}
```
**核心实现思想**：先找出最后一个乱序位置 $b$，若存在乱序则在 $[1,b]$ 区间内进行交换操作，最后检查序列是否有序，若有序则输出操作次数，否则输出 -1；若序列本身有序则输出 0。

#### 作者：Composite_Function
```c++
while (T--) {
    int tmp = 0;
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
        if (val[i] < val[i - 1])
            tmp = i; // 找出无序的部分
    }
    if (tmp == 0) cout << 0 << endl; // 如果有序就不用了
    else {
        int ans = 0;
        bool flag = true;
        for (int i = 1; i <= tmp; ++i)
            if (x < val[i]) {
                swap(x, val[i]);
                ++ans;
            }
        for (int i = 1; i <= n; ++i)
            if (val[i] < val[i - 1])
                flag = false; // 如果还是无序，那么就没办法再继续了
        if (flag == true) cout << ans << endl;
        else cout << -1 << endl;
    }
}
```
**核心实现思想**：先找出无序部分的最后位置 $tmp$，若序列有序则输出 0；否则在 $[1,tmp]$ 区间内进行交换操作，最后检查序列是否有序，若有序则输出操作次数，否则输出 -1。

#### 作者：zztqwq
```cpp
while(T--)
{
    int x;
    scanf("%d %d",&n,&x);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    if(check())
    {
        printf("0\n");
        continue;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]>x)
        {
            swap(a[i],x);
            ans++;
        }
        if(check()) 
        {
            printf("%d\n",ans);
            break;
        }
    }
    if(!check()) printf("-1\n");
}
```
**核心实现思想**：先检查序列是否有序，若有序则输出 0；否则从前往后扫描序列，遇到可交换的元素就进行交换，每交换一次操作次数加 1，若交换后序列有序则输出操作次数，若扫描完序列仍无序则输出 -1。

### 最优关键思路或技巧
- **贪心策略**：根据“若 $a_i>x$ 但不交换，后面的数无法通过交换使序列有序”的性质，从前往后扫描序列，遇到可交换的元素就进行交换，能有效减少操作次数。
- **找出最后一个乱序位置**：通过先找出最后一个乱序位置，只对该位置之前的元素进行操作，避免对有序部分进行不必要的操作，提高效率。

### 拓展思路
同类型题目通常会涉及对序列的操作和状态变化，要求通过某种操作使序列满足特定条件。类似的算法套路包括贪心策略、动态规划等。在处理这类问题时，关键是找出操作的规律和限制条件，从而确定最优的操作策略。

### 推荐洛谷题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略解决合并果子的最小代价问题。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：运用贪心思想安排排队顺序，使平均等待时间最短。
3. [P2240 食草的奶牛](https://www.luogu.com.cn/problem/P2240)：利用贪心算法解决奶牛吃草的最优选择问题。

### 个人心得摘录与总结
- **作者：yingkeqian9217**：提到本题对代码能力要求不高，关键在于能否想到规律，即要换编号最小的满足 $a_i>x$ 的元素，否则会出现逆序对，与最终目的不符。总结就是在解决此类问题时，要善于发现规律和限制条件，从而确定正确的解题思路。

---
处理用时：54.59秒