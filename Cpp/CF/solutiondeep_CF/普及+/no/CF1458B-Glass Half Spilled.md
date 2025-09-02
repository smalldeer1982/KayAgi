# 题目信息

# Glass Half Spilled

## 题目描述

There are $ n $ glasses on the table numbered $ 1, \ldots, n $ . The glass $ i $ can hold up to $ a_i $ units of water, and currently contains $ b_i $ units of water.

You would like to choose $ k $ glasses and collect as much water in them as possible. To that effect you can pour water from one glass to another as many times as you like. However, because of the glasses' awkward shape (and totally unrelated to your natural clumsiness), each time you try to transfer any amount of water, half of the amount is spilled on the floor.

Formally, suppose a glass $ i $ currently contains $ c_i $ units of water, and a glass $ j $ contains $ c_j $ units of water. Suppose you try to transfer $ x $ units from glass $ i $ to glass $ j $ (naturally, $ x $ can not exceed $ c_i $ ). Then, $ x / 2 $ units is spilled on the floor. After the transfer is done, the glass $ i $ will contain $ c_i - x $ units, and the glass $ j $ will contain $ \min(a_j, c_j + x / 2) $ units (excess water that doesn't fit in the glass is also spilled).

Each time you transfer water, you can arbitrarlly choose from which glass $ i $ to which glass $ j $ to pour, and also the amount $ x $ transferred can be any positive real number.

For each $ k = 1, \ldots, n $ , determine the largest possible total amount of water that can be collected in arbitrarily chosen $ k $ glasses after transferring water between glasses zero or more times.

## 说明/提示

In the sample case, you can act as follows:


2. for $ k = 1 $ , transfer water from the first two glasses to the third one, spilling $ (5 + 5) / 2 = 5 $ units and securing $ 2 + (5 + 5) / 2 = 7 $ units;
3. for $ k = 2 $ , transfer water from the third glass to any of the first two, spilling $ 2 / 2 = 1 $ unit and securing $ 5 + 5 + 2 / 2 = 11 $ units;
4. for $ k = 3 $ , do nothing. All $ 5 + 5 + 2 = 12 $ units are secured.

## 样例 #1

### 输入

```
3
6 5
6 5
10 2```

### 输出

```
7.0000000000 11.0000000000 12.0000000000```

# AI分析结果

### 题目中文重写
# 半洒的杯子

## 题目描述
桌子上有 $n$ 个杯子，编号为 $1, \ldots, n$。杯子 $i$ 最多能容纳 $a_i$ 单位的水，目前装有 $b_i$ 单位的水。

你想选择 $k$ 个杯子，并尽可能多地收集其中的水。为此，你可以随意多次将水从一个杯子倒入另一个杯子。然而，由于杯子形状奇特（与你天生的笨拙完全无关），每次尝试转移任何数量的水时，一半的水量会洒在地板上。

形式上，假设杯子 $i$ 目前装有 $c_i$ 单位的水，杯子 $j$ 装有 $c_j$ 单位的水。假设你尝试从杯子 $i$ 向杯子 $j$ 转移 $x$ 单位的水（自然地，$x$ 不能超过 $c_i$）。那么，$x / 2$ 单位的水会洒在地板上。转移完成后，杯子 $i$ 将装有 $c_i - x$ 单位的水，杯子 $j$ 将装有 $\min(a_j, c_j + x / 2)$ 单位的水（装不进杯子的多余水也会洒出）。

每次转移水时，你可以任意选择从哪个杯子 $i$ 向哪个杯子 $j$ 倒水，并且转移的水量 $x$ 可以是任何正实数。

对于每个 $k = 1, \ldots, n$，确定在零次或多次转移水之后，任意选择的 $k$ 个杯子中所能收集到的最大总水量。

## 说明/提示
在样例中，你可以按如下方式操作：
2. 当 $k = 1$ 时，将前两个杯子中的水转移到第三个杯子中，洒出 $(5 + 5) / 2 = 5$ 单位的水，最终获得 $2 + (5 + 5) / 2 = 7$ 单位的水；
3. 当 $k = 2$ 时，将第三个杯子中的水转移到前两个杯子中的任意一个，洒出 $2 / 2 = 1$ 单位的水，最终获得 $5 + 5 + 2 / 2 = 11$ 单位的水；
4. 当 $k = 3$ 时，不进行任何操作。所有 $5 + 5 + 2 = 12$ 单位的水都得以保留。

## 样例 #1
### 输入
```
3
6 5
6 5
10 2
```
### 输出
```
7.0000000000 11.0000000000 12.0000000000
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是将问题转化为选择 $k$ 个杯子，把其他杯子的水倒入这 $k$ 个杯子中，通过动态规划来求解最大水量。不同题解在状态定义和转移方程上有相似之处，但也存在细节差异。部分题解利用了倒水过程不会回倒这一重要性质简化问题。难点在于如何准确地定义状态和写出转移方程，以处理杯子的容量和已有水量的限制。

### 所选题解
- **dead_X（5星）**
    - **关键亮点**：思路清晰，对问题的分析和状态转移方程的推导详细，代码实现规范，复杂度分析明确。
    - **核心代码**：
```cpp
int a[103],b[103],tot,dp[103][10003];//空间，空余量 
double ans[103];
signed main()
{
    int n=read();
    for(int i=1; i<=n; i++) b[i]=read(),a[i]=read(),tot+=a[i];
    memset(dp,0xc0,sizeof(dp));
    for(int i=0; i<=n; i++) dp[i][0]=0;
    for(int i=1; i<=n; i++) for(int j=i; j>=1; j--) for(int k=100*j; k>=b[i]-a[i]; k--)
        dp[j][k]=max(dp[j][k],dp[j-1][k-b[i]+a[i]]+a[i]);
    for(int i=1; i<=n; i++) for(int j=0; j<=100*i; j++) ans[i]=max(ans[i],min((tot-dp[i][j])/2.0,(double)j)+dp[i][j]);
    for(int i=1; i<=n; i++) printf("%.10lf ",ans[i]);
    return 0;
}
```
    - **核心实现思想**：定义 $dp_{i,j}$ 表示选了 $i$ 个盆子，这些盆子的 $a$ 之和为 $j$ 时 $b$ 之和的最大值。通过三重循环进行状态转移，最后根据状态计算每个 $k$ 对应的最大水量。
- **Warriors_Cat（4星）**
    - **关键亮点**：准确抓住问题的关键性质，状态定义和转移清晰，代码结构合理。
    - **核心代码**：
```cpp
const int N = 100;
int n, a[N + 5], b[N + 5], sum, f[N + 5][N + 5][N * N + 5]; double ans[N];
inline void work(){
    n = read(); rep(i, 1, n) b[i] = read(), sum += (a[i] = read());
    memset(f, -0x3f, sizeof(f)); rep(i, 0, n) f[i][0][0] = 0;
    rep(i, 1, n) rep(j, 1, i) rep(k, 0, N * N){
        f[i][j][k] = f[i - 1][j][k];
        if(k >= b[i]) f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - b[i]] + a[i]);
    }
    rep(i, 1, n) rep(j, 0, N * N) ans[i] = max(ans[i], min(1.0 * j, 1.0 * (sum + f[n][i][j]) / 2));
    rep(i, 1, n) printf("%0.11lf ", ans[i]);
}
```
    - **核心实现思想**：定义 $f_{i, j, k}$ 表示前 $i$ 个杯子中选 $j$ 个，此时 $b_i$ 和为 $k$ 时 $a_i$ 和的最大值。通过三重循环进行状态转移，最后计算每个 $k$ 对应的最大水量。
- **Fairicle（4星）**
    - **关键亮点**：思路推导过程详细，对问题的理解深入，代码简洁。
    - **核心代码**：
```cpp
#define ri register int
#define N 102
int n,b[N],a[N],f[N][N][N*N];
int main(){
    cin>>n;
    for(ri i=1;i<=n;++i) cin>>a[i]>>b[i];
    int all=0;
    for(ri i=1;i<=n;++i) all+=b[i];
    memset(f,-0x3f,sizeof(f));
    f[0][0][0]=0;
    for(ri i=1;i<=n;++i)
        for(ri j=0;j<=i;++j)
            for(ri k=0;k<=10000;++k){
                f[i][j][k]=f[i-1][j][k];
                if(j>0&&k>=a[i]) f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k-a[i]]+b[i]);
            }
    for(ri k=1;k<=n;++k){
        int ans=0;
        for(ri p=0;p<=10000;++p) ans=max(ans,min(p*2,f[n][k][p]+all));
        printf("%d.%d ",ans/2,(ans%2)*5);
    }   
    return 0;
}
```
    - **核心实现思想**：定义 $f_{i,j,k}$ 表示遍历前 $i$ 个杯子，选择了 $j$ 个杯子，$a$ 值之和为 $k$ 时的最大 $b$ 值之和。通过三重循环进行状态转移，最后计算每个 $k$ 对应的最大水量。

### 最优关键思路或技巧
- 利用倒水过程不会回倒的性质，将问题简化为选择 $k$ 个杯子并将其他杯子的水倒入其中。
- 通过合理定义动态规划的状态，如选择的杯子数量、杯子容量之和、已有水量之和等，来处理杯子的容量和水量限制。

### 拓展思路
同类型题目可能会改变倒水的规则（如洒出的水量比例不同）或增加其他限制条件（如倒水次数限制），但核心思路仍然是通过动态规划来处理选择和转移的过程。类似的算法套路包括在有多种选择和限制条件的情况下，通过状态定义和转移方程来求解最优解。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，与本题的动态规划思想类似。
- [P1853 投资的最大效益](https://www.luogu.com.cn/problem/P1853)：涉及到资金的选择和收益计算，需要运用动态规划来求解最优投资方案。
- [P2722 总分 Score Inflation](https://www.luogu.com.cn/problem/P2722)：同样是通过动态规划来处理选择问题，与本题的思路有一定的相似性。

### 个人心得摘录与总结
- **Timmylyx**：这是作者写的第一篇题解，希望有错误时能得到谅解。总结：新手写题解时可能会存在不足，需要不断学习和改进。

---
处理用时：69.49秒