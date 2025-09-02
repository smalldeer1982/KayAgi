# 题目信息

# Rising Sand

## 题目描述

There are $ n $ piles of sand where the $ i $ -th pile has $ a_i $ blocks of sand. The $ i $ -th pile is called too tall if $ 1 < i < n $ and $ a_i > a_{i-1} + a_{i+1} $ . That is, a pile is too tall if it has more sand than its two neighbours combined. (Note that piles on the ends of the array cannot be too tall.)

You are given an integer $ k $ . An operation consists of picking $ k $ consecutive piles of sand and adding one unit of sand to them all. Formally, pick $ 1 \leq l,r \leq n $ such that $ r-l+1=k $ . Then for all $ l \leq i \leq r $ , update $ a_i \gets a_i+1 $ .

What is the maximum number of piles that can simultaneously be too tall after some (possibly zero) operations?

## 说明/提示

In the first test case, we can perform the following three operations:

- Add one unit of sand to piles $ 1 $ and $ 2 $ : $ [\color{red}{3}, \color{red}{10}, 2, 4, 1] $ .
- Add one unit of sand to piles $ 4 $ and $ 5 $ : $ [3, 10, 2, \color{red}{5}, \color{red}{2}] $ .
- Add one unit of sand to piles $ 3 $ and $ 4 $ : $ [3, 10, \color{red}{3}, \color{red}{6}, 2] $ .

 Now piles $ 2 $ and $ 4 $ are too tall, so in this case the answer is $ 2 $ . It can be shown that it is impossible to make more than $ 2 $ piles too tall.In the second test case, any operation will increase all piles by $ 1 $ unit, so the number of too tall piles will always be $ 0 $ .

In the third test case, we can increase any pile by $ 1 $ unit of sand. It can be shown that the maximum number of too tall piles is $ 1 $ .

## 样例 #1

### 输入

```
3
5 2
2 9 2 4 1
4 4
1 3 2 1
3 1
1 3 1```

### 输出

```
2
0
1```

# AI分析结果

### 题目内容
# 上升的沙子

## 题目描述
有 $n$ 堆沙子，其中第 $i$ 堆有 $a_i$ 块沙子。如果 $1 < i < n$ 且 $a_i > a_{i - 1} + a_{i + 1}$，则第 $i$ 堆被称为过高。也就是说，如果一堆沙子比它的两个相邻堆的沙子总和还多，那么这堆沙子就是过高的。（注意，数组两端的堆不可能过高。）

给定一个整数 $k$。一次操作包括选择 $k$ 个连续的沙堆，并给它们都添加一个单位的沙子。形式上，选择 $1 \leq l, r \leq n$ 使得 $r - l + 1 = k$。然后对于所有 $l \leq i \leq r$，更新 $a_i \gets a_i + 1$。

经过一些（可能为零）操作后，同时过高的沙堆的最大数量是多少？

## 说明/提示
在第一个测试用例中，我们可以执行以下三个操作：
- 给第 $1$ 和第 $2$ 堆沙子各添加一个单位：$[\color{red}{3}, \color{red}{10}, 2, 4, 1]$。
- 给第 $4$ 和第 $5$ 堆沙子各添加一个单位：$[3, 10, 2, \color{red}{5}, \color{red}{2}]$。
- 给第 $3$ 和第 $4$ 堆沙子各添加一个单位：$[3, 10, \color{red}{3}, \color{red}{6}, 2]$。

现在第 $2$ 和第 $4$ 堆沙子过高，所以在这种情况下答案是 $2$。可以证明不可能使超过 $2$ 堆沙子过高。
在第二个测试用例中，任何操作都会使所有堆增加一个单位，所以过高的沙堆数量将始终为 $0$。
在第三个测试用例中，我们可以给任何一堆沙子增加一个单位的沙子。可以证明过高沙堆的最大数量是 $1$。

## 样例 #1
### 输入
```
3
5 2
2 9 2 4 1
4 4
1 3 2 1
3 1
1 3 1
```
### 输出
```
2
0
1
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路一致，均通过分类讨论解决问题。当 $k = 1$ 时，因可对单个元素操作，能构造出最多 $\lfloor\frac{n - 1}{2}\rfloor$ 个过高的堆；当 $k \gt 1$ 时，对长度为 $k$ 的区间操作，无法增加过高堆的数量，直接统计原数组中过高堆的数量即可。各题解在思路清晰度、代码可读性、优化程度上有差异。

### 所选的题解
- **作者：MH_SLC (5星)**
    - **关键亮点**：思路清晰，先分析题目，再分情况讨论，代码简洁明了，对 $k$ 不同取值的处理逻辑清晰。
    - **重点代码核心实现思想**：根据 $k$ 的值分情况计算过高堆数量。$k \neq 1$ 时遍历数组统计原数组中满足 $a[i] > a[i - 1] + a[i + 1]$ 的数量；$k = 1$ 时按 $n$ 的奇偶性计算最大过高堆数量。
    - **核心代码片段**：
```cpp
if (k!= 1) {    //k！=1的情况
    for (int i = 2 ; i < n ; i ++ )
        if (a[i] > a[i - 1] + a[i + 1]) cnt++;    //需要满足条件a[i]>a[i-1]+a[i+1]
} else {    //k等于1的情况，按奇偶性分类
    if (n & 1) cnt = (n - 2) / 2 + 1;    //不会计算端点
    else cnt = (n - 2) / 2;
}
```
- **作者：luogu_gza (4星)**
    - **关键亮点**：对操作影响的分析详细，通过举例说明 $k \geq 2$ 时操作对答案的影响，代码规范，注释详细。
    - **重点代码核心实现思想**：与 MH_SLC 类似，根据 $k$ 值分情况处理。$k = 1$ 时按 $n$ 的奇偶性输出最大过高堆数量；$k \neq 1$ 时遍历统计原数组中满足条件的数量。
    - **核心代码片段**：
```cpp
if(k==1)
{
    if(n%2==0) write(n/2-1);//最后一个不算
    else write(n/2);
    puts("");
}
else
{
    int ans=0;
    fo(i,2,n-1)
        if(a[i]>a[i-1]+a[i+1])
            ans++;
    write(ans),puts("");//原序列满足条件的数量就是答案
}
```
- **作者：Dry_ice (4星)**
    - **关键亮点**：分析部分对两种情况的证明简洁清晰，代码简洁高效，使用位运算优化除法操作。
    - **重点代码核心实现思想**：同样依据 $k$ 值分情况计算过高堆数量。$k = 1$ 时用位运算计算 $\lfloor\frac{n - 1}{2}\rfloor$；$k \gt 1$ 时遍历数组统计满足条件的数量。
    - **核心代码片段**：
```cpp
if (k == 1) printf("%d\n", n - 1 >> 1); //k = 1的情况
else { //k > 1的情况
    int Res = 0;
    for (int i = 2; i < n; ++i)
        Res += (a[i] > a[i - 1] + a[i + 1]);
    printf("%d\n", Res);
}
```

### 最优关键思路或技巧
通过分类讨论，针对 $k$ 的不同取值分析操作对过高堆数量的影响。$k = 1$ 时利用可单独操作单个元素的特性构造过高堆；$k \gt 1$ 时分析出操作无法增加过高堆数量，从而简化问题求解。

### 拓展
此类题目属于通过分析操作对特定条件影响来求解最值的问题。类似套路是先分析不同操作情况对目标条件的作用，再根据分析结果分类讨论得出结论。

### 相似知识点洛谷题目
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)
- [P2669 金币](https://www.luogu.com.cn/problem/P2669)
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085) 

---
处理用时：48.75秒