# 题目信息

# Pie Rules

## 题目描述

You may have heard of the pie rule before. It states that if two people wish to fairly share a slice of pie, one person should cut the slice in half, and the other person should choose who gets which slice. Alice and Bob have many slices of pie, and rather than cutting the slices in half, each individual slice will be eaten by just one person.

The way Alice and Bob decide who eats each slice is as follows. First, the order in which the pies are to be handed out is decided. There is a special token called the "decider" token, initially held by Bob. Until all the pie is handed out, whoever has the decider token will give the next slice of pie to one of the participants, and the decider token to the other participant. They continue until no slices of pie are left.

All of the slices are of excellent quality, so each participant obviously wants to maximize the total amount of pie they get to eat. Assuming both players make their decisions optimally, how much pie will each participant receive?

## 说明/提示

In the first example, Bob takes the size $ 141 $ slice for himself and gives the decider token to Alice. Then Alice gives the size $ 592 $ slice to Bob and keeps the decider token for herself, so that she can then give the size $ 653 $ slice to herself.

## 样例 #1

### 输入

```
3
141 592 653
```

### 输出

```
653 733
```

## 样例 #2

### 输入

```
5
10 21 10 21 10
```

### 输出

```
31 41
```

# AI分析结果

### 题目内容
#### Pie Rules
#### 题目描述
你可能之前听说过切派规则。它指出如果两个人想要公平地分享一块派，一个人应该把派切成两半，另一个人应该选择谁得到哪一块。爱丽丝（Alice）和鲍勃（Bob）有很多块派，并且不是把每块派切成两半，而是每一块派只会被一个人吃掉。

爱丽丝和鲍勃决定谁吃每一块派的方式如下。首先，决定派分发的顺序。有一个特殊的令牌叫做“决定者”令牌，最初由鲍勃持有。直到所有的派都分发完，持有“决定者”令牌的人将下一块派给其中一个参与者，然后将“决定者”令牌交给另一个参与者。他们继续这个过程，直到没有派剩下。

所有的派块质量都非常好，所以每个参与者显然都想最大化他们吃到的派的总量。假设两个玩家都做出最优决策，每个参与者会得到多少派？
#### 说明/提示
在第一个例子中，鲍勃为自己拿了大小为141的派块，并将“决定者”令牌给爱丽丝。然后爱丽丝将大小为592的派块给鲍勃，并为自己保留“决定者”令牌，这样她就可以将大小为653的派块给自己。
#### 样例 #1
##### 输入
```
3
141 592 653
```
##### 输出
```
653 733
```
#### 样例 #2
##### 输入
```
5
10 21 10 21 10
```
##### 输出
```
31 41
```

• **算法分类**：动态规划
• **综合分析与结论**：这些题解都围绕动态规划解决该博弈问题。难点在于正向DP存在后效性，需倒推DP。各题解思路核心是定义状态和状态转移方程，通过后缀和辅助计算。不同点在于状态定义和具体实现细节。
• **所选的题解**
  - **作者：Lilyana (5星)**
    - **关键亮点**：详细分析正向DP存在后效性原因，清晰阐述倒推DP的思路及状态转移方程的推导，代码简洁明了。
    - **个人心得**：吐槽题目评级与数据范围误导，自己做题时因对复杂度判断错误不敢提交。
    - **重点代码**：
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
const int MAXN(1e5+5);
inline int read()
{
    char ch(getchar());
    int x(0);
    int flag(1); 
    while(!isdigit(ch))
    {
        if(ch=='-')
        {
            flag=-1;
        }
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+(ch^48); 
        ch=getchar();
    }
    return flag*x;
}
int sum[MAXN];
int a[MAXN];
int dp[MAXN];
int main()
{
    int n(read()); 
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
    }
    for(int i=n;i>=1;i--)
    {
        sum[i]=sum[i+1]+a[i]; 
        dp[i]=std::max(dp[i+1],sum[i+1]-dp[i+1]+a[i]);
    }
    std::printf("%d %d\n",sum[1]-dp[1],dp[1]);
    return 0;
}
```
核心实现思想：通过read函数读入数据，计算后缀和sum数组，利用状态转移方程dp[i]=max(dp[i+1],sum[i+1]-dp[i+1]+a[i])倒推DP数组，最后输出两人所得派的数量。
  - **作者：yyz1005 (4星)**
    - **关键亮点**：先定义二维DP状态，分析状态转移方程，后简化为一维DP，逻辑清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,a[55],sum = 0;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    int dp[55];
    dp[n] = a[n];
    sum = a[n];
    for(int i = n-1; i >= 1; i--){
        dp[i] = max(dp[i+1],sum-dp[i+1]+a[i]);
        sum+=a[i];
    }
    cout << sum-dp[1] << " " << dp[1];
    return 0;
}
```
核心实现思想：读入数据后初始化dp[n]和sum，通过循环利用状态转移方程dp[i]=max(dp[i+1],sum-dp[i+1]+a[i])计算DP数组，最后输出结果。
  - **作者：songge888 (4星)**
    - **关键亮点**：简洁明了地阐述题意和思路，给出状态转移方程的详细分析，代码规范。
    - **重点代码**：
```c++
#include<bits/stdc++.h>
#define bug cout<<"songge888"<<'\n';
#define int long long
using namespace std;
int n;
int a[114],sum[114],dp[114]; 
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=n;i>=1;i--){
        sum[i]=sum[i+1]+a[i];
    }
    for(int i=n;i>=1;i--){
        dp[i]=max(dp[i+1],sum[i]-dp[i+1]);
    }
    cout<<sum[1]-dp[1]<<' '<<dp[1];
    return 0;
}
```
核心实现思想：读入数据后计算后缀和sum数组，利用状态转移方程dp[i]=max(dp[i+1],sum[i]-dp[i+1])倒推DP数组，输出两人所得结果。
• **最优关键思路或技巧**：采用倒推的动态规划，避免正向DP的后效性。定义合适的DP状态，利用后缀和简化状态转移方程的计算。
• **可拓展之处**：此类博弈类型动态规划题，常需分析决策对后续状态的影响，通过倒推或合理定义状态消除后效性。类似套路可用于其他轮流决策且需最优策略的问题。
• **推荐洛谷题目**
  - [P1118 数字三角形](https://www.luogu.com.cn/problem/P1118)
  - [P1216 数字三角形 2](https://www.luogu.com.cn/problem/P1216)
  - [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)

---
处理用时：52.06秒