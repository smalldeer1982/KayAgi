# 题目信息

# [USACO10NOV] Candy S

## 题目描述

Farmer John knows that Bessie loves to eat candy. FJ has N (1 <= N <= 40,000) candies that he wants to give Bessie over some number of days. Each day, Farmer John gives Bessie a choice of how many candies she chooses to eat that day by choosing the number from a master list FJ supplies that has Nopt (1 <= Nopt <= 50) different options, C\_i (1 <= C\_i <= N). She must take exactly C\_i candies, no more, no less.

Farmer John has also disclosed F (1 <= F <= 50) of his favorite numbers, FN\_i (1 <= FN\_i <= N). Whenever the number of candies remaining at the end of the day precisely matches one of these favorite numbers, Bessie has the option to have him add exactly M (1 <= M <= 100) more candies to the candy supply. Bessie might get another option to add M candies several times if adding candies creates another favorite number. In the best circumstances, Bessie can obtain an infinite amount of candy!

When Bessie cannot choose some amount of candy to take (because there is not enough), and the number of candies remaining is not any of FJ's favorite numbers, she cannot have any more candy.

Unfortunately, Bessie cannot think ahead as far as she'd like to, so she needs your help in order to eat as many candies as possible.

By way of example, consider this scenario:

\* Farmer John's basket initially contains 10 candies

\* Bessie can chose to eat either 3 or 5 candies each day

\* Farmer John will add 1 candy any time the remaining number of candies is 2 or 4

Bessie could use this set of choices to maximize the amount of candy she can eat:

```cpp

                  Initial      # Candies   Remaining     Bonus     Final
        Day      # Candies       Eaten      Candies     Candies   Candies

         1          10             3          7            0        7
         2           7             3          4            1        5
         3           5             3          2            1        3
         4           3             3          0            0        0

```

Total candies eaten = 3 + 3 + 3 + 3 = 12. 

农民约翰知道Bessie喜欢吃糖果。约翰有N（1≤N≤40000）的糖果，他想给Bessie几天。每一天，贝茜从一个列表（有nopt（1 <= nopt <= 50）种不同的选择），选择那一天吃掉刚好C\_i（1 <= c\_i <= N）个糖果。


农民约翰也透露F（1≤f≤50）他最喜欢的数字，FN\_i（1 <= FN\_i <= N）。当当天最后剩下的糖果数量精确匹配其中一个喜欢的号码，Bessie可以让他添加恰好M（1 <= M = 100）个糖果。如果加后得到的个数，还是FJ喜欢的数字，就可以继续添加糖果M个（加几次由贝西决定）。在最好的情况下，Bessie可以吃掉无限量的糖果！


当Bessie不能选择一定量的糖（因为没有足够的），或者糖果的剩余数量不是任何约翰最喜欢的号码，她不能有任何更多的糖果。


不幸的是，Bessie想不出她想做的事，所以她需要你的帮助才能吃尽可能多的糖果。


## 说明/提示

感谢@ 王彦梓 提供翻译，kkksc03进行了修正。


## 样例 #1

### 输入

```
10 2 2 1 
3 
5 
4 
2 
```

### 输出

```
12 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何解决Bessie吃糖果问题展开，核心在于处理吃糖果和加糖果的状态转移，并判断是否能无限吃糖。主要思路可分为动态规划和图论建模两种。

动态规划思路通过定义状态数组 `dp` 来记录剩余不同数量糖果时最多可吃的糖果数，依据吃糖果和加糖果的规则进行状态转移；图论建模思路则将每个糖果剩余数量抽象为图中的节点，吃糖果和加糖果的操作抽象为边，问题转化为求图中从起点到终点的最长路，同时需判断图中是否存在环。

### 所选题解
- **作者：L______ (赞：8)，4星**
    - **关键亮点**：思路清晰，先考虑无加糖情况的状态转移方程，再处理加糖情况，通过 `cnt` 数组判断是否能无限吃糖，代码实现简洁易懂。
    - **个人心得**：最开始尝试用堆维护可反悔的贪心但未成功，转而思考dp思路。

### 重点代码
```cpp
// 作者：L______
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
#define inf 0x7f7f7f7f
#define N 60
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int n,nopt,F,m,c[N],f[N],book[40110],dp[40110],cnt[40110],ans;

int main(){
    n=read(),nopt=read(),F=read(),m=read();
    for(int i=1;i<=nopt;i++) c[i]=read();
    for(int i=1;i<=F;i++) book[read()]=1;
    memset(dp,-1,sizeof(dp));
    dp[n]=0;book[n]=false;
    for(int i=n;i;i--){
        if(dp[i]==-1) continue;
        if(cnt[i]>F+1) return printf("-1\n"),0;
        if(book[i]){
            cnt[i]++;
            if(dp[i]>dp[i+m]){
                dp[i+m]=dp[i];
                i+=m+1;
            }
            continue;
        }
        for(int j=1;j<=nopt;j++){
            if(i-c[j]<0) continue;
            dp[i-c[j]]=max(dp[i-c[j]],dp[i]+c[j]);
        }
    }
    for(int i=n;i>=0;i--) ans=max(ans,dp[i]);
    printf("%d\n",ans);
    return 0;
}
```
**核心实现思想**：
1. 初始化 `dp` 数组为 -1，`dp[n]` 初始化为 0，表示初始有 `n` 个糖果时已吃 0 个。
2. 从 `n` 到 1 枚举剩余糖果数 `i`，若 `dp[i]` 为 -1 则跳过。
3. 若 `cnt[i] > F + 1`，说明可能进入无限循环，输出 -1。
4. 若 `i` 是喜欢的数，更新 `dp[i + m]` 并将 `i` 加上 `m + 1`。
5. 枚举每次可吃的糖果数 `c[j]`，更新 `dp[i - c[j]]`。
6. 最后遍历 `dp` 数组，找出最大值作为答案。

### 最优关键思路或技巧
- **动态规划**：通过定义合适的状态数组 `dp`，将问题拆分为子问题，依据规则进行状态转移，逐步求解。
- **图论建模**：将问题抽象为图，利用图的性质（如最长路、环的判断）来解决问题。
- **记忆化搜索**：避免重复计算，提高效率。

### 可拓展之处
同类型题或类似算法套路：
- 资源分配问题：在一定资源限制下，依据不同操作规则，求最大收益或最优方案。
- 路径规划问题：在图中依据边的权值和特殊条件，求最短或最长路径。

### 推荐题目
- P1048 [NOIP2005 普及组] 采药：0 - 1 背包问题，可使用动态规划求解。
- P1177 [模板] 快速排序：涉及排序算法，与图论和动态规划的状态转移有一定关联。
- P1216 [USACO1.5] 数字三角形 Number Triangles：经典的动态规划问题，可锻炼状态定义和转移的能力。

### 个人心得总结
作者 L______ 尝试用堆维护可反悔的贪心未成功后，转向dp思路，说明在解题时若一种方法行不通，可尝试换一种思路。

---
处理用时：38.02秒