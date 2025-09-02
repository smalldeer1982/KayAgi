# 题目信息

# Exact Change

## 题目描述

One day, early in the morning, you decided to buy yourself a bag of chips in the nearby store. The store has chips of $ n $ different flavors. A bag of the $ i $ -th flavor costs $ a_i $ burles.

The store may run out of some flavors, so you'll decide which one to buy after arriving there. But there are two major flaws in this plan:

1. you have only coins of $ 1 $ , $ 2 $ and $ 3 $ burles;
2. since it's morning, the store will ask you to pay in exact change, i. e. if you choose the $ i $ -th flavor, you'll have to pay exactly $ a_i $ burles.

Coins are heavy, so you'd like to take the least possible number of coins in total. That's why you are wondering: what is the minimum total number of coins you should take with you, so you can buy a bag of chips of any flavor in exact change?

## 说明/提示

In the first test case, you should, for example, take with you $ 445 $ coins of value $ 3 $ and $ 1 $ coin of value $ 2 $ . So, $ 1337 = 445 \cdot 3 + 1 \cdot 2 $ .

In the second test case, you should, for example, take $ 2 $ coins of value $ 3 $ and $ 2 $ coins of value $ 2 $ . So you can pay either exactly $ 8 = 2 \cdot 3 + 1 \cdot 2 $ or $ 10 = 2 \cdot 3 + 2 \cdot 2 $ .

In the third test case, it's enough to take $ 1 $ coin of value $ 3 $ and $ 2 $ coins of value $ 1 $ .

## 样例 #1

### 输入

```
4
1
1337
3
10 8 10
5
1 2 3 4 5
3
7 77 777```

### 输出

```
446
4
3
260```

# AI分析结果

### 题目翻译
## 精确找零

### 题目描述
一天清晨，你决定去附近的商店买一袋薯片。商店里有 $n$ 种不同口味的薯片，第 $i$ 种口味的薯片售价为 $a_i$ 伯尔（货币单位）。

商店里某些口味的薯片可能会售罄，所以你打算到了商店之后再决定买哪种。但这个计划有两个主要问题：
1. 你只有面值为 $1$、$2$ 和 $3$ 伯尔的硬币；
2. 因为是早上，商店要求你必须用恰好的钱数付款，也就是说，如果你选择了第 $i$ 种口味的薯片，你必须正好支付 $a_i$ 伯尔。

硬币很重，所以你希望携带的硬币总数尽可能少。因此你想知道：你最少需要携带多少枚硬币，才能用恰好的钱数购买任意一种口味的薯片？

### 说明/提示
在第一个测试用例中，你可以携带 $445$ 枚面值为 $3$ 的硬币和 $1$ 枚面值为 $2$ 的硬币。这样，$1337 = 445 \cdot 3 + 1 \cdot 2$。

在第二个测试用例中，你可以携带 $2$ 枚面值为 $3$ 的硬币和 $2$ 枚面值为 $2$ 的硬币。这样你就可以正好支付 $8 = 2 \cdot 3 + 1 \cdot 2$ 或 $10 = 2 \cdot 3 + 2 \cdot 2$。

在第三个测试用例中，携带 $1$ 枚面值为 $3$ 的硬币和 $2$ 枚面值为 $1$ 的硬币就足够了。

### 样例 #1
#### 输入
```
4
1
1337
3
10 8 10
5
1 2 3 4 5
3
7 77 777
```
#### 输出
```
446
4
3
260
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是基于硬币面值的特殊性质，即面值为 $1$ 和 $2$ 的硬币数量有一定限制，从而通过枚举这两种硬币的数量，再计算出所需面值为 $3$ 的硬币数量，最终找出满足条件的最小硬币总数。

不同题解的差异在于枚举的方式和细节处理上。部分题解通过分类讨论最大价格的余数情况来简化枚举过程，而有些题解则直接暴力枚举所有可能的情况。

### 所选题解
- **Presentation_Emitter（4星）**
    - **关键亮点**：思路简洁，直接指出面值为 $1$ 和 $2$ 的硬币各不超过两个的结论，通过枚举这两种硬币个数来计算结果，代码实现较为精炼。
- **Tyyyyyy（4星）**
    - **关键亮点**：详细证明了最多带 $1$ 张 $1$ 元和 $2$ 张 $2$ 元的结论，并给出了不同情况下计算 $3$ 元硬币数量的公式，逻辑清晰，代码可读性高。
- **jianhe（4星）**
    - **关键亮点**：同样基于硬币数量的限制进行枚举，代码结构清晰，函数封装合理，易于理解。

### 重点代码
#### Presentation_Emitter
```cpp
ll slv(ll t1,ll t2)
{
    ll res=-1;
    for(int i=1;i<=n;++i)
    {
        ll u=inf;
        for(int j=0;j<=t1;++j)
        {
            for(int k=0;k<=t2;++k)
            {
                ll r=a[i]-j-k-k;
                if(r<0)continue;
                if(!(r%3))tomin(u,r/3);
            }
        }
        tomax(res,u);
    }
    ret res+t1+t2;
}
```
**核心实现思想**：枚举面值为 $1$ 和 $2$ 的硬币个数 $t1$ 和 $t2$，对于每种口味的薯片价格 $a[i]$，计算在使用 $j$ 个 $1$ 元硬币和 $k$ 个 $2$ 元硬币后，所需 $3$ 元硬币的最小数量，最后取所有口味中 $3$ 元硬币数量的最大值，再加上 $1$ 元和 $2$ 元硬币的总数。

#### Tyyyyyy
```cpp
for(int num1=0;num1<=1;num1++)
{
    for(int num2=0;num2<=2;num2++)
    {
        int res=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]%3==0)
            {
                if(num1&&num2)res=max(res,a[i]/3-1);
                else res=max(res,a[i]/3);
            }
            else if(a[i]%3==1)
            {
                if(num2==2&&a[i]>=4)res=max(res,(a[i]-4)/3);
                else if(num1)res=max(res,(a[i]-1)/3);
                else res=1e9;
            }
            else
            {
                if(num2==2&&num1&&a[i]>=5)res=max(res,(a[i]-5)/3);
                else if(num2)res=max(res,(a[i]-2)/3);
                else res=1e9;
            }
        }
        ans=min(ans,res+num1+num2);
    }
}
```
**核心实现思想**：枚举 $1$ 元硬币数量 $num1$ 和 $2$ 元硬币数量 $num2$，对于每种口味的薯片价格 $a[i]$，根据其除以 $3$ 的余数情况，计算所需 $3$ 元硬币的数量，取所有口味中 $3$ 元硬币数量的最大值，再加上 $1$ 元和 $2$ 元硬币的总数，最后取最小值作为答案。

#### jianhe
```cpp
ll solve(ll t,ll t1,ll t2){
    ll ct=inf; 
    for(int i=0;i<=t1;i++)//面值为 1 的纸币数量
        for(int j=0;j<=t2;j++){//面值为 2 的纸币数量
            ll tmp=t-i-j*2;//剩余钱数
            if(tmp<0) continue;
            if(!(tmp%3)) ct=min(ct,tmp/3);//面值为 3 的纸币数量
        }
    return ct;
}
ll work(ll t1,ll t2){
    ll ans=-1;//面值为 3 的纸币数量最大值
    for(int i=1;i<=n;i++) ans=max(ans,solve(a[i],t1,t2));
    return ans+t1+t2;
}
```
**核心实现思想**：`solve` 函数用于计算对于给定价格 $t$，在使用 $t1$ 个 $1$ 元硬币和 $t2$ 个 $2$ 元硬币的情况下，所需 $3$ 元硬币的最小数量。`work` 函数则对所有口味的薯片价格调用 `solve` 函数，取 $3$ 元硬币数量的最大值，再加上 $1$ 元和 $2$ 元硬币的总数。

### 关键思路或技巧
- 发现面值为 $1$ 和 $2$ 的硬币数量的限制，减少枚举的范围。
- 通过枚举 $1$ 元和 $2$ 元硬币的数量，计算出满足所有价格的最小 $3$ 元硬币数量。

### 拓展思路
同类型题目可能会改变硬币的面值或增加硬币的种类，解题思路仍然可以基于枚举和贪心的思想，先找出某些面值硬币数量的限制，再进行枚举计算。

### 推荐洛谷题目
- P1036 选数（组合数学 + 枚举）
- P1149 火柴棒等式（枚举）
- P1217 [USACO1.5] 回文质数 Prime Palindromes（质数 + 枚举）

### 个人心得
- **Presentation_Emitter**：作者觉得此题比 `C` 题水多了，说明对该题难度的一种感受。 

---
处理用时：51.70秒