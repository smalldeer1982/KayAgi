# 题目信息

# Yet Another Coin Problem

## 题目描述

You have $ 5 $ different types of coins, each with a value equal to one of the first $ 5 $ triangular numbers: $ 1 $ , $ 3 $ , $ 6 $ , $ 10 $ , and $ 15 $ . These coin types are available in abundance. Your goal is to find the minimum number of these coins required such that their total value sums up to exactly $ n $ .

We can show that the answer always exists.

## 说明/提示

In the first test case, for $ n = 1 $ , the answer is $ 1 $ since only one $ 1 $ value coin is sufficient. $ 1 = 1 \cdot 1 $ .

In the fourth test case, for $ n = 5 $ , the answer is $ 3 $ , which can be achieved using two $ 1 $ value coins and one $ 3 $ value coin. $ 5 = 2 \cdot 1 + 1 \cdot 3 $ .

In the seventh test case, for $ n = 12 $ , the answer is $ 2 $ , which can be achieved using two $ 6 $ value coins.

In the ninth test case, for $ n = 16 $ , the answer is $ 2 $ , which can be achieved using one $ 1 $ value coin and one $ 15 $ value coin or using one $ 10 $ value coin and one $ 6 $ value coin. $ 16 = 1 \cdot 1 + 1 \cdot 15 = 1 \cdot 6 + 1 \cdot 10 $ .

## 样例 #1

### 输入

```
14
1
2
3
5
7
11
12
14
16
17
18
20
98
402931328```

### 输出

```
1
2
1
3
2
2
2
3
2
3
2
2
8
26862090```

# AI分析结果

### 题目内容重写

你有5种不同面值的硬币，分别为1元、3元、6元、10元和15元。这些硬币种类有无穷多。你的目标是用最少的硬币凑出正好n元钱。

### 说明/提示

在第一个测试用例中，对于n=1，答案是1，因为只需要1个1元硬币即可。1 = 1 × 1。

在第四个测试用例中，对于n=5，答案是3，可以通过使用2个1元硬币和1个3元硬币来实现。5 = 2 × 1 + 1 × 3。

在第七个测试用例中，对于n=12，答案是2，可以通过使用2个6元硬币来实现。

在第九个测试用例中，对于n=16，答案是2，可以通过使用1个1元硬币和1个15元硬币，或者使用1个10元硬币和1个6元硬币来实现。16 = 1 × 1 + 1 × 15 = 1 × 6 + 1 × 10。

### 样例 #1

#### 输入

```
14
1
2
3
5
7
11
12
14
16
17
18
20
98
402931328
```

#### 输出

```
1
2
1
3
2
2
2
3
2
3
2
2
8
26862090
```

### 题解分析与结论

1. **暴力枚举+贪心**：多个题解采用了暴力枚举的思路，通过限制每种硬币的最大使用数量来减少枚举范围，然后结合贪心策略优先使用大面值硬币。这种方法在小范围内有效，但在大范围内可能效率较低。
2. **动态规划+贪心**：部分题解结合了动态规划和贪心策略，先通过动态规划预处理小范围内的最优解，然后对于大范围的n，优先使用15元硬币，再结合预处理的结果进行求解。这种方法在处理大范围n时效率较高。
3. **数学方法**：个别题解尝试通过数学方法减少枚举范围，但实现较为复杂，且效果不如动态规划+贪心结合的方法。

### 评分较高的题解

#### 1. 作者：RyanLeander (5星)

**关键亮点**：
- 结合动态规划和贪心策略，预处理小范围内的最优解，处理大范围n时效率高。
- 代码简洁，思路清晰，时间复杂度低。

**核心代码**：
```cpp
const int N=110;
ll f[N],n;
int main(){
    for(int i=0;i<40;i++) f[i]=0x3f3f3f3f3f3f3f;
    f[1]=1,f[0]=0;
    for(int i=0;i<40;i++){
        f[i+1]=min(f[i+1],f[i]+1);
        f[i+3]=min(f[i+3],f[i]+1);
        f[i+6]=min(f[i+6],f[i]+1);
        f[i+10]=min(f[i+10],f[i]+1);
        f[i+15]=min(f[i+15],f[i]+1);
    }
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%lld",&n);
        if(n<40) printf("%lld\n",f[n]);
        else printf("%lld\n",min(
        f[n%15]+(int)(n/15),
        f[n%15+15]+(int)(n/15-1)
        ));
    }
    return 0;
}
```

#### 2. 作者：hgckythgcfhk (4星)

**关键亮点**：
- 使用完全背包预处理小范围内的最优解，结合贪心策略处理大范围n。
- 预处理范围较大，确保在大范围内的高效性。

**核心代码**：
```cpp
unsigned dp[N];
signed main(){open;memset(dp,0x3f,sizeof dp);dp[1]=dp[3]=dp[6]=dp[10]=dp[15]=1;dp[0]=0;
    for(int i=2 ;i<N;++i)dp[i]=min(dp[i-1 ]+1,dp[i]);
    for(int i=4 ;i<N;++i)dp[i]=min(dp[i-3 ]+1,dp[i]);
    for(int i=7 ;i<N;++i)dp[i]=min(dp[i-6 ]+1,dp[i]);
    for(int i=11;i<N;++i)dp[i]=min(dp[i-10]+1,dp[i]);
    for(int i=16;i<N;++i)dp[i]=min(dp[i-15]+1,dp[i]);
    int t;cin>>t;while(t--){int n;cin>>n;if(n<N){cout<<dp[n]<<'\n';continue;}
        int ans=(n-N+1)/15+1;n-=ans*15;cout<<ans+dp[n]<<'\n';}
}
```

### 最优关键思路

结合动态规划和贪心策略，先预处理小范围内的最优解，然后对于大范围的n，优先使用大面值硬币（如15元），再结合预处理的结果进行求解。这种方法在处理大范围n时效率较高，且代码实现简洁。

### 可拓展之处

类似的问题可以扩展到其他面值的硬币组合，或者扩展到其他类型的完全背包问题。通过预处理小范围内的最优解，再结合贪心策略处理大范围问题，是一种通用的优化思路。

### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 完全背包问题
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060) - 动态规划与贪心结合
3. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616) - 完全背包问题的高效处理

---
处理用时：43.28秒