# 题目信息

# Credit Card

## 题目描述

Recenlty Luba got a credit card and started to use it. Let's consider $ n $ consecutive days Luba uses the card.

She starts with $ 0 $ money on her account.

In the evening of $ i $ -th day a transaction $ a_{i} $ occurs. If $ a_{i}&gt;0 $ , then $ a_{i} $ bourles are deposited to Luba's account. If $ a_{i}&lt;0 $ , then $ a_{i} $ bourles are withdrawn. And if $ a_{i}=0 $ , then the amount of money on Luba's account is checked.

In the morning of any of $ n $ days Luba can go to the bank and deposit any positive integer amount of burles to her account. But there is a limitation: the amount of money on the account can never exceed $ d $ .

It can happen that the amount of money goes greater than $ d $ by some transaction in the evening. In this case answer will be «-1».

Luba must not exceed this limit, and also she wants that every day her account is checked (the days when $ a_{i}=0 $ ) the amount of money on her account is non-negative. It takes a lot of time to go to the bank, so Luba wants to know the minimum number of days she needs to deposit some money to her account (if it is possible to meet all the requirements). Help her!

## 样例 #1

### 输入

```
5 10
-1 5 0 -5 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 4
-10 0 20
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 10
-5 0 10 -11 0
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# 信用卡

## 题目描述
最近，卢巴（Luba）拿到了一张信用卡并开始使用。我们考虑卢巴使用信用卡的 \(n\) 个连续日子。

她账户初始金额为 \(0\) 。

在第 \(i\) 天晚上会发生一笔交易 \(a_{i}\) 。如果 \(a_{i}>0\) ，那么 \(a_{i}\) 卢布会存入卢巴的账户。如果 \(a_{i}<0\) ，那么 \(a_{i}\) 卢布会被取出。如果 \(a_{i}=0\) ，那么会检查卢巴账户上的金额。

在 \(n\) 天中的任何一天早上，卢巴都可以去银行，并向她的账户存入任意正整数金额的卢布。但有一个限制：账户上的金额永远不能超过 \(d\) 。

有可能在晚上的某笔交易后，金额超过 \(d\) 。在这种情况下，答案将是“\(-1\)”。

卢巴不能超过这个限制，并且她希望在每天检查账户（即 \(a_{i}=0\) 的日子）时，账户上的金额是非负的。去银行需要花费很多时间，所以卢巴想知道她最少需要去银行存钱的天数（如果有可能满足所有要求的话）。帮帮她！

## 样例 #1
### 输入
```
5 10
-1 5 0 -5 3
```
### 输出
```
0
```

## 样例 #2
### 输入
```
3 4
-10 0 20
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
5 10
-5 0 10 -11 0
```
### 输出
```
2
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路大多是通过维护账户金额的上下界来解决问题。难点在于如何在满足账户金额不超过上限 \(d\) 且在检查日金额非负的条件下，找到最少的存钱次数。

多数题解采用贪心策略，在每次操作时同步更新上下界：对于非零操作，上下界同时加上操作金额，若下界超过 \(d\) 则无解，上界超过 \(d\) 则设为 \(d\)；对于零操作，若下界小于 \(0\) 设为 \(0\)，上界小于 \(0\) 则设为 \(d\) 并增加存钱次数。

部分题解思路和代码较为清晰简洁，部分相对复杂或存在代码不完整、未充分优化等问题。

### 所选的题解
- **作者：流绪 (5星)**
    - **关键亮点**：思路清晰，详细阐述了平衡充钱少与次数少的矛盾，通过贪心模拟，用两个变量分别表示尽量少充钱和尽量多充钱时的余额，逻辑严谨，代码可读性高。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010];
int main()
{
    ios::sync_with_stdio(false);
    int n,d;
    cin >> n >> d;
    for(int i=1;i<=n;i++)
        cin >> a[i];
    int sum1,sum2,cnt;
    sum1=sum2=cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(!a[i])
        {
            if(sum1 <0)
                sum1 = 0;
            if(sum2 <0)
                sum2 = d,cnt++;
        }
        else
        {
            sum1 += a[i];
            sum2 += a[i];
            if(sum1 >d)
            {
                cout << -1;
                return 0; 
            }
            if(sum2 > d)
                sum2 = d;
        }
    }
    cout << cnt;
} 
```
    - **核心实现思想**：用 `sum1` 记录尽量少充钱时的余额，`sum2` 记录尽量多充钱时的余额。遍历操作数组，零操作时，若 `sum1` 小于 \(0\) 则设为 \(0\)，若 `sum2` 小于 \(0\) 则设为 \(d\) 并增加存钱次数；非零操作时，同时更新 `sum1` 和 `sum2`，若 `sum1` 大于 \(d\) 则无解，若 `sum2` 大于 \(d\) 则设为 \(d\)。

- **作者：蒟酱 (5星)**
    - **关键亮点**：题意提炼准确，代码简洁明了，通过记录信用卡里钱的下界 `s1` 和上界 `s2`，按照操作类型更新上下界，逻辑清晰。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
constexpr int N=1e5+1;
int n,m,a[N],ans,s1,s2;
signed main(){
    std::ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1,x;i<=n;i++)
        if(cin>>x,x){
            if((s1+=x)>m)return cout<<"-1",0;
            if((s2+=x)>m)s2=m;
        }else{
            if(s1<0)s1=0;
            if(s2<0)s2=m,ans++;
        }
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：遍历操作数组，非零操作时，同时更新 `s1` 和 `s2`，若 `s1` 大于 \(m\) 则无解，若 `s2` 大于 \(m\) 则设为 \(m\)；零操作时，若 `s1` 小于 \(0\) 则设为 \(0\)，若 `s2` 小于 \(0\) 则设为 \(m\) 并增加存钱次数。

- **作者：Crazyouth (4星)**
    - **关键亮点**：分析部分清晰阐述了维护上下界判断有解与答案个数的思路，代码实现简洁，逻辑明确。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,d,up=0,low=0,ans=0;
    cin>>n>>d;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        if(x)
        {
            up+=x;
            low+=x;
            if(low>d)
            {
                cout<<-1;
                return 0;
            }
            if(up>d) up=d;
        }
        else
        {
            if(up<0) up=d,ans++;
            if(low<0) low=0;
        }
    }
    cout<<ans;
    return 0; 
}
```
    - **核心实现思想**：用 `low` 表示下界，`up` 表示上界。遍历操作数组，非零操作时，同时更新 `low` 和 `up`，若 `low` 大于 \(d\) 则无解，若 `up` 大于 \(d\) 则设为 \(d\)；零操作时，若 `low` 小于 \(0\) 则设为 \(0\)，若 `up` 小于 \(0\) 则设为 \(d\) 并增加存钱次数。

### 最优关键思路或技巧
维护账户金额的上下界，在每次操作时根据操作类型和上下界的变化情况进行判断和调整，利用贪心思想，在保证满足条件的前提下，尽量减少充钱次数。

### 可拓展之处
同类型题可涉及其他具有上下界限制的资源管理问题，类似算法套路为通过维护关键变量的上下界，结合贪心策略解决问题。

### 推荐题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录
无

---
处理用时：59.83秒