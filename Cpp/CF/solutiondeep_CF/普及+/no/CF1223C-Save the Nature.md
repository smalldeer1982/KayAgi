# 题目信息

# Save the Nature

## 题目描述

You are an environmental activist at heart but the reality is harsh and you are just a cashier in a cinema. But you can still do something!

You have $ n $ tickets to sell. The price of the $ i $ -th ticket is $ p_i $ . As a teller, you have a possibility to select the order in which the tickets will be sold (i.e. a permutation of the tickets). You know that the cinema participates in two ecological restoration programs applying them to the order you chose:

- The $ x\% $ of the price of each the $ a $ -th sold ticket ( $ a $ -th, $ 2a $ -th, $ 3a $ -th and so on) in the order you chose is aimed for research and spreading of renewable energy sources.
- The $ y\% $ of the price of each the $ b $ -th sold ticket ( $ b $ -th, $ 2b $ -th, $ 3b $ -th and so on) in the order you chose is aimed for pollution abatement.

If the ticket is in both programs then the $ (x + y) \% $ are used for environmental activities. Also, it's known that all prices are multiples of $ 100 $ , so there is no need in any rounding.

For example, if you'd like to sell tickets with prices $ [400, 100, 300, 200] $ and the cinema pays $ 10\% $ of each $ 2 $ -nd sold ticket and $ 20\% $ of each $ 3 $ -rd sold ticket, then arranging them in order $ [100, 200, 300, 400] $ will lead to contribution equal to $ 100 \cdot 0 + 200 \cdot 0.1 + 300 \cdot 0.2 + 400 \cdot 0.1 = 120 $ . But arranging them in order $ [100, 300, 400, 200] $ will lead to $ 100 \cdot 0 + 300 \cdot 0.1 + 400 \cdot 0.2 + 200 \cdot 0.1 = 130 $ .

Nature can't wait, so you decided to change the order of tickets in such a way, so that the total contribution to programs will reach at least $ k $ in minimum number of sold tickets. Or say that it's impossible to do so. In other words, find the minimum number of tickets which are needed to be sold in order to earn at least $ k $ .

## 说明/提示

In the first query the total contribution is equal to $ 50 + 49 = 99 < 100 $ , so it's impossible to gather enough money.

In the second query you can rearrange tickets in a following way: $ [100, 100, 200, 200, 100, 200, 100, 100] $ and the total contribution from the first $ 6 $ tickets is equal to $ 100 \cdot 0 + 100 \cdot 0.1 + 200 \cdot 0.15 + 200 \cdot 0.1 + 100 \cdot 0 + 200 \cdot 0.25 = 10 + 30 + 20 + 50 = 110 $ .

In the third query the full price of each ticket goes to the environmental activities.

In the fourth query you can rearrange tickets as $ [100, 200, 100, 100, 100] $ and the total contribution from the first $ 4 $ tickets is $ 100 \cdot 0 + 200 \cdot 0.31 + 100 \cdot 0 + 100 \cdot 0.31 = 62 + 31 = 93 $ .

## 样例 #1

### 输入

```
4
1
100
50 1
49 1
100
8
100 200 100 200 100 200 100 100
10 2
15 3
107
3
1000000000 1000000000 1000000000
50 1
50 1
3000000000
5
200 100 100 100 100
69 5
31 2
90
```

### 输出

```
-1
6
3
4
```

# AI分析结果

### 题目中文重写
# 拯救自然

## 题目描述
你内心是一名环保活动家，但现实很残酷，你只是一家电影院的收银员。但你仍然可以做些什么！

你有 $n$ 张票要出售。第 $i$ 张票的价格是 $p_i$。作为收银员，你可以选择售票的顺序（即票的一个排列）。你知道电影院参与了两个生态修复项目，并会按照你选择的顺序来应用这些项目：
- 你所选择顺序中，每张第 $a$ 张售出的票（第 $a$ 张、第 $2a$ 张、第 $3a$ 张 等等）价格的 $x\%$ 用于可再生能源的研究和推广。
- 你所选择顺序中，每张第 $b$ 张售出的票（第 $b$ 张、第 $2b$ 张、第 $3b$ 张 等等）价格的 $y\%$ 用于污染治理。

如果一张票同时参与了两个项目，那么将使用其价格的 $(x + y)\%$ 用于环保活动。此外，已知所有票价都是 $100$ 的倍数，因此无需进行任何四舍五入。

例如，如果你想出售价格为 $[400, 100, 300, 200]$ 的票，并且电影院会对每张第 $2$ 张售出的票支付 $10\%$，对每张第 $3$ 张售出的票支付 $20\%$，那么按 $[100, 200, 300, 400]$ 的顺序售票，环保贡献将为 $100 \cdot 0 + 200 \cdot 0.1 + 300 \cdot 0.2 + 400 \cdot 0.1 = 120$。但按 $[100, 300, 400, 200]$ 的顺序售票，环保贡献将为 $100 \cdot 0 + 300 \cdot 0.1 + 400 \cdot 0.2 + 200 \cdot 0.1 = 130$。

大自然刻不容缓，所以你决定改变售票顺序，使得对项目的总贡献至少达到 $k$，并且售出的票数最少。或者说明无法做到这一点。换句话说，找到为了赚取至少 $k$ 所需售出的最少票数。

## 说明/提示
在第一个查询中，总贡献为 $50 + 49 = 99 < 100$，所以无法筹集到足够的资金。

在第二个查询中，你可以按以下顺序重新排列票：$[100, 100, 200, 200, 100, 200, 100, 100]$，前 $6$ 张票的总贡献为 $100 \cdot 0 + 100 \cdot 0.1 + 200 \cdot 0.15 + 200 \cdot 0.1 + 100 \cdot 0 + 200 \cdot 0.25 = 10 + 30 + 20 + 50 = 110$。

在第三个查询中，每张票的全价都用于环保活动。

在第四个查询中，你可以将票重新排列为 $[100, 200, 100, 100, 100]$，前 $4$ 张票的总贡献为 $100 \cdot 0 + 200 \cdot 0.31 + 100 \cdot 0 + 100 \cdot 0.31 = 62 + 31 = 93$。

## 样例 #1
### 输入
```
4
1
100
50 1
49 1
100
8
100 200 100 200 100 200 100 100
10 2
15 3
107
3
1000000000 1000000000 1000000000
50 1
50 1
3000000000
5
200 100 100 100 100
69 5
31 2
90
```
### 输出
```
-1
6
3
4
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路都是利用二分查找来确定满足总贡献至少为 $k$ 的最少售票数。因为售票数越多，总贡献只会增大，具有单调性，所以可以使用二分。

思路上，大家都先对票价从大到小排序，以保证优先使用价格高的票来获得更多贡献。在检查函数（`check`）中，不同题解有不同的实现方式：
- 部分题解通过遍历当前二分的售票数，计算每张票的贡献百分比，再对百分比数组排序，与票价数组配对计算总贡献。
- 部分题解利用容斥原理，先计算出能同时被 $a$ 和 $b$ 整除、只能被 $a$ 整除、只能被 $b$ 整除的票的数量，然后按贡献百分比从大到小分配票价。

### 所选题解
- **作者：yuzhechuan (赞：2)  5星**
    - **关键亮点**：提供了 $O(nlog^2n)$ 和 $O(nlogn)$ 两种复杂度的算法，思路清晰，代码实现详细，且对两种算法的复杂度和特点进行了说明。
    - **核心代码**：
```cpp
// O(nlog^2n) 算法的 check 函数
bool check(int n){
    int sum=0;
    for(int i=1;i<=n;i++){
        b[i]=0;
        if(i%al==0) b[i]+=x; //有第一种贡献
        if(i%be==0) b[i]+=y; //有第二种贡献
    }
    sort(b+1,b+1+n,greater<int>()); //greater<int>()是自带的一个比较函数，用来从大到小排
    for(int i=1;i<=n;i++) sum+=a[i]*b[i]; //a[]在main()中均已除以100，直接暴力配对
    return sum>=k;
}

// O(nlogn) 算法的 check 函数
bool check(int n){
    int sum=0,xn=n/al,yn=n/be,xyn=n/lcm; //除法计算
    xn-=xyn; //容斥
    yn-=xyn;
    for(int i=1;i<=xyn;i++) sum+=(x+y)*a[i]; //lcm段
    for(int i=xyn+1;i<=xyn+xn;i++) sum+=x*a[i]; //a段
    for(int i=xyn+xn+1;i<=xyn+xn+yn;i++) sum+=y*a[i]; //b段
    return sum>=k;
}
```
**实现思想**：第一个 `check` 函数通过遍历计算每张票的贡献百分比，排序后与票价配对求和；第二个 `check` 函数利用容斥原理计算不同贡献类型的票的数量，按顺序分配票价求和。

### 最优关键思路或技巧
- **二分查找**：利用售票数和总贡献的单调性，通过二分查找快速确定满足条件的最少售票数。
- **贪心策略**：对票价从大到小排序，优先使用价格高的票，将其分配给贡献百分比大的位置，以获得最大总贡献。
- **容斥原理**：在计算不同贡献类型的票的数量时，使用容斥原理避免重复计算。

### 可拓展之处
同类型题可能会改变项目规则、增加项目数量或改变票价的计算方式，但核心思路仍然可以是利用二分查找和贪心策略。类似算法套路还可以应用在资源分配、任务调度等问题中，通过二分查找确定最优解，贪心策略优化资源分配。

### 推荐题目
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：二分答案经典题目，通过二分查找确定满足条件的最小跳跃距离。
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：同样是二分答案的题目，二分查找满足条件的最大分段和。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：利用二分查找确定满足条件的最小路标间距。

### 个人心得
本题解中暂无个人心得相关内容。

---
处理用时：60.86秒