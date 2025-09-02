# 题目信息

# Ticket Hoarding

## 题目描述

[Maître Gims - Est-ce que tu m'aimes ?](https://youtu.be/6TpyRE_juyA)

ඞ



As the CEO of a startup company, you want to reward each of your $ k $ employees with a ticket to the upcoming concert. The tickets will be on sale for $ n $ days, and by some time travelling, you have predicted that the price per ticket at day $ i $ will be $ a_i $ . However, to prevent ticket hoarding, the concert organizers have implemented the following measures:

- A person may purchase no more than $ m $ tickets per day.
- If a person purchases $ x $ tickets on day $ i $ , all subsequent days (i.e. from day $ i+1 $ onwards) will have their prices per ticket increased by $ x $ .

For example, if $ a = [1, 3, 8, 4, 5] $ and you purchase $ 2 $ tickets on day $ 1 $ , they will cost $ 2 $ in total, and the prices from day $ 2 $ onwards will become $ [5, 10, 6, 7] $ . If you then purchase $ 3 $ more tickets on day $ 2 $ , they will cost in total an additional $ 15 $ , and the prices from day $ 3 $ onwards will become $ [13, 9, 10] $ .

Find the minimum spending to purchase $ k $ tickets.

## 说明/提示

In the first test case, one optimal way to buy $ 3 $ tickets is as follows:

- Buy $ 0 $ tickets on the first day. The prices per ticket for the remaining days are $ [6, 4, 2] $ .
- Buy $ 0 $ tickets on the second day. The prices per ticket for the remaining days are $ [4, 2] $ .
- Buy $ 1 $ ticket on the third day with cost $ 4 $ . The price per ticket for the remaining day is $ [3] $ .
- Buy $ 2 $ tickets on the fourth day with cost $ 6 $ .

In the second test case, there is only one way to buy $ 8 $ tickets:

- Buy $ 2 $ tickets on the first day with cost $ 16 $ . The prices per ticket for the remaining days are $ [8, 6, 4] $ .
- Buy $ 2 $ tickets on the second day with cost $ 16 $ . The prices per ticket for the remaining days are $ [8, 6] $ .
- Buy $ 2 $ tickets on the third day with cost $ 16 $ . The price per ticket for the remaining day is $ [8] $ .
- Buy $ 2 $ tickets on the fourth day with cost $ 16 $ .

## 样例 #1

### 输入

```
4
4 2 3
8 6 4 2
4 2 8
8 6 4 2
5 100 1
10000 1 100 10 1000
6 3 9
5 5 5 5 5 5```

### 输出

```
10
64
1
72```

# AI分析结果

### 题目内容重写
#### 题目描述
作为一家初创公司的CEO，你想奖励你的 $k$ 名员工每人一张即将到来的音乐会的门票。门票将会销售 $n$ 天，通过一些时间旅行，你已经预测到第 $i$ 天的每张票的价格将会是 $a_i$。不过，为防止囤积门票，音乐会主办方采取了以下措施：

- 每人每天可购买不超过 $m$ 张票。
- 如果一个人在第 $i$ 天购买了 $x$ 张票，那么随后的所有日子（即从第 $i+1$ 天起）的每张票的价格将增加 $x$。

例如，如果 $a = [1, 3, 8, 4, 5]$，你在第一天购买了2张票，它们将花费 $2$，从第二天开始的价格将变成 $[5, 10, 6, 7]$。如果你在第 $2$ 天再购买 $3$ 张票，他们将花费额外的 $15$ 美元，从第 $3$ 天开始的价格将变成 $[13, 9, 10]$。

求购买 $k$ 张票的最小花费。

### 题解分析与结论
各题解均采用了贪心算法，核心思路是从价格最低的天数开始购买门票，以减少总成本。主要难点在于如何有效地计算由于购买行为导致的后序天数价格增加，并确保在每天购买的门票数不超过 $m$。

#### 关键思路与技巧
1. **贪心策略**：从价格最低的天数开始购买门票，以最小化总成本。
2. **排序优化**：先对价格数组进行排序，确保优先购买价格最低的门票。
3. **动态更新价格**：每次购买后，更新后续天数的价格增加量，确保后续购买时价格计算正确。

### 所选高星题解
#### 题解1：作者：littlebug (5星)
**关键亮点**：
- 通过数学推导，证明了排序后贪心策略的正确性。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
sort(a+1,a+n+1);
ll ans=0,add=0;
for(int i=1;i<=n;++i)
{
    if(k>=m)
    {
        k-=m;
        ans+=m*(a[i]+add);
        add+=m;
    }
    else
    {
        ans+=k*(a[i]+add);
        cout<<ans<<'\n';
        return;
    }
}
cout<<ans<<'\n';
```

#### 题解2：作者：Karl_Aldrich (4星)
**关键亮点**：
- 详细解释了贪心策略的合理性，并提供了清晰的代码实现。
- 代码结构良好，注释详细，便于阅读。

**核心代码**：
```cpp
sort(a+1,a+n+1);
ans=0,more=0;
rep(i,1,n){
    int cnt=min(m,k);
    ans+=1ll*cnt*(a[i]+more);
    more+=cnt;
    k-=cnt;
}
cout<<ans<<'\n';
```

#### 题解3：作者：_Lightning_ (4星)
**关键亮点**：
- 代码简洁，逻辑清晰，直接实现了贪心策略。
- 通过循环逐步减少需要购买的门票数，确保每天购买的门票数不超过 $m$。

**核心代码**：
```cpp
sort(a+1,a+1+n);
ll i=1,s=0,ans=0;
while(k!=0){
    if(k>=m){
        k-=m;
        ans+=m*(a[i]+s);
        s+=m;
    }
    else{
        ans+=k*(a[i]+s);
        k=0;
    }
    i++;
}
cout<<ans<<endl;
```

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

这些题目都涉及到贪心算法和排序的应用，适合进一步巩固相关知识点。

---
处理用时：35.05秒