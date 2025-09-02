# 题目信息

# Naughty Stone Piles

## 题目描述

There are $ n $ piles of stones of sizes $ a_{1},a_{2},...,a_{n} $ lying on the table in front of you.

During one move you can take one pile and add it to the other. As you add pile $ i $ to pile $ j $ , the size of pile $ j $ increases by the current size of pile $ i $ , and pile $ i $ stops existing. The cost of the adding operation equals the size of the added pile.

Your task is to determine the minimum cost at which you can gather all stones in one pile.

To add some challenge, the stone piles built up conspiracy and decided that each pile will let you add to it not more than $ k $ times (after that it can only be added to another pile).

Moreover, the piles decided to puzzle you completely and told you $ q $ variants (not necessarily distinct) of what $ k $ might equal.

Your task is to find the minimum cost for each of $ q $ variants.

## 说明/提示

In the first sample one way to get the optimal answer goes like this: we add in turns the $ 4 $ -th and the $ 5 $ -th piles to the $ 2 $ -nd one; then we add the $ 1 $ -st pile to the $ 3 $ -rd one; we add the $ 2 $ -nd pile to the $ 3 $ -rd one. The first two operations cost $ 1 $ each; the third one costs $ 2 $ , the fourth one costs $ 5 $ (the size of the $ 2 $ -nd pile after the first two operations is not $ 3 $ , it already is $ 5 $ ).

In the second sample you can add the $ 2 $ -nd pile to the $ 3 $ -rd one (the operations costs $ 3 $ ); then the $ 1 $ -st one to the $ 3 $ -th one (the cost is $ 2 $ ); then the $ 5 $ -th one to the $ 4 $ -th one (the costs is $ 1 $ ); and at last, the $ 4 $ -th one to the $ 3 $ -rd one (the cost is $ 2 $ ).

## 样例 #1

### 输入

```
5
2 3 4 1 1
2
2 3
```

### 输出

```
9 8 ```

# AI分析结果

### 题目内容
# 调皮的石堆

## 题目描述
有 $n$ 堆石子，大小分别为 $a_{1},a_{2},\cdots,a_{n}$，摆在你面前的桌子上。

在一次移动中，你可以拿起一堆石子并将其加到另一堆上。当你将第 $i$ 堆石子加到第 $j$ 堆上时，第 $j$ 堆石子的大小会增加第 $i$ 堆石子当前的大小，而第 $i$ 堆石子将不复存在。添加操作的代价等于被添加的那堆石子的大小。

你的任务是确定将所有石子收集到一堆中的最小代价。

为了增加一些挑战性，石堆们密谋决定，每堆石子最多允许你添加 $k$ 次（在此之后，它只能被添加到另一堆中）。

此外，石堆们决定彻底难住你，并告诉你 $q$ 种（不一定不同）$k$ 可能的值。

你的任务是为这 $q$ 种 $k$ 的取值分别找到最小代价。

## 说明/提示
在第一个样例中，一种获得最优答案的方法如下：我们依次将第 $4$ 堆和第 $5$ 堆石子加到第 $2$ 堆上；然后将第 $1$ 堆石子加到第 $3$ 堆上；最后将第 $2$ 堆石子加到第 $3$ 堆上。前两个操作的代价各为 $1$；第三个操作的代价为 $2$，第四个操作的代价为 $5$（在前两个操作之后，第 $2$ 堆石子的大小不是 $3$，而是已经变为 $5$ 了）。

在第二个样例中，你可以将第 $2$ 堆石子加到第 $3$ 堆上（操作代价为 $3$）；然后将第 $1$ 堆石子加到第 $3$ 堆上（代价为 $2$）；接着将第 $5$ 堆石子加到第 $4$ 堆上（代价为 $1$）；最后，将第 $4$ 堆石子加到第 $3$ 堆上（代价为 $2$）。

## 样例 #1
### 输入
```
5
2 3 4 1 1
2
2 3
```
### 输出
```
9 8 
```

• **算法分类**：贪心
• **综合分析与结论**：这几道题解的核心思路都是基于贪心策略。大家都认识到若不限制合并次数，将所有石子合并到最大堆是最优解。在有合并次数 $k$ 限制的情况下，都采用对石子堆按大小排序，让权值大的石子移动次数尽量少，权值小的石子移动次数尽量多的贪心策略。不同点在于具体实现方式，有的通过模拟合并过程结合前缀和计算，有的从树形结构角度分析每层节点数量及贡献来计算。整体思路相近，实现细节略有差异。
• **所选的题解**
  - **作者：Feyn (5星)**
    - **关键亮点**：将问题转化为构建一棵树，以点权乘深度之和最小为目标，提出树为完全（类似完全二叉树概念）时最优，通过排序数组考虑点在同一层的情况实现，思路清晰且独特，代码简洁高效。
    - **核心代码片段**：
```cpp
void solve(int len){
    int l=2,now=len,op=1;
    for(;l<=m;l=l+now,op++,now*=len)ans[len]+=(a[min(l+now-1,m)]-a[l-1])*op;
}
```
核心实现思想：通过循环计算每层石子对答案的贡献，`l` 表示当前层起始位置，`now` 表示当前层石子数量，`op` 表示当前层数，每次循环更新位置、层数及当前层石子数，计算当前层石子贡献累加到 `ans[len]` 中。
  - **作者：ncwzdlsd (4星)**
    - **关键亮点**：从简单情况 $k = 1$ 入手，逐步分析 $k$ 次移动的情况，通过模拟移动过程得出贪心策略，并用前缀和维护计算每次合并代价，思路通俗易懂。
    - **核心代码片段**：
```cpp
while(q--)
{
    int k;cin>>k;
    if(k==1) {cout<<ans1<<' ';continue;}
    int ans=0,kk=k,nn=n-1,cnt=1;
    while(nn>=kk)
    {
        ans+=(sum[nn]-sum[nn-kk])*cnt;
        nn-=kk,kk*=k,cnt++;
    }
    ans+=sum[nn]*cnt;
    cout<<ans<<' ';
}
```
核心实现思想：对于每个询问的 $k$，若 $k = 1$ 直接输出预处理的答案 `ans1`。否则，通过循环模拟合并过程，`nn` 表示剩余未合并的石子堆索引，`kk` 表示当前层可合并的石子堆数量，`cnt` 表示当前合并次数，每次循环计算当前层合并代价累加到 `ans` 中，最后输出 `ans`。
  - **作者：TH911 (4星)**
    - **关键亮点**：详细分析了加入 $k$ 次限制后总代价的形式，以建一棵树辅助理解但实际通过排序后贪心统计答案，同时预处理所有可能 $k$ 值的答案，提高查询效率。
    - **核心代码片段**：
```cpp
for(int k=1;k<=n;k++){
    //p=n-1:a[n]不统计 
    int p=n-1,pl=1;
    ll kk=k;//kk=k^pl
    while(p>=kk){
        ans[k]+=(sum[p]-sum[p-kk])*pl;//这一层的kk个元素统计答案
        p-=kk;kk*=k;
        pl++;
    }
    ans[k]+=sum[p]*pl;
} 
```
核心实现思想：通过双重循环，外层循环遍历 $k$ 的所有可能值，内层循环计算每种 $k$ 值下的答案。`p` 表示当前未合并的石子堆索引，`pl` 表示当前层数，`kk` 表示当前层可合并的石子堆数量，每次循环计算当前层石子贡献累加到 `ans[k]` 中。
• **最优关键思路或技巧**：将问题类比为树形结构，利用贪心策略，对石子堆按大小排序，让大石子移动次数少，小石子移动次数多，通过前缀和优化计算合并代价。同时，预处理所有可能 $k$ 值的答案，可提高查询效率。
• **可拓展之处**：类似的贪心策略在其他合并类问题中也可能适用，如合并果子等问题，关键在于分析每次操作对结果的影响，找到最优的合并顺序。
• **推荐题目**：
  - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
  - [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
  - [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)
• **个人心得**：无。 

---
处理用时：69.76秒