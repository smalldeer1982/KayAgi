# 题目信息

# The Child and Toy

## 题目描述

On Children's Day, the child got a toy from Delayyy as a present. However, the child is so naughty that he can't wait to destroy the toy.

The toy consists of $ n $ parts and $ m $ ropes. Each rope links two parts, but every pair of parts is linked by at most one rope. To split the toy, the child must remove all its parts. The child can remove a single part at a time, and each remove consume an energy. Let's define an energy value of part $ i $ as $ v_{i} $ . The child spend $ v_{f1}+v_{f2}+...+v_{fk} $ energy for removing part $ i $ where $ f_{1},f_{2},...,f_{k} $ are the parts that are directly connected to the $ i $ -th and haven't been removed.

Help the child to find out, what is the minimum total energy he should spend to remove all $ n $ parts.

## 说明/提示

One of the optimal sequence of actions in the first sample is:

- First, remove part $ 3 $ , cost of the action is $ 20 $ .
- Then, remove part $ 2 $ , cost of the action is $ 10 $ .
- Next, remove part $ 4 $ , cost of the action is $ 10 $ .
- At last, remove part $ 1 $ , cost of the action is $ 0 $ .

So the total energy the child paid is $ 20+10+10+0=40 $ , which is the minimum.

In the second sample, the child will spend $ 400 $ no matter in what order he will remove the parts.

## 样例 #1

### 输入

```
4 3
10 20 30 40
1 4
1 2
2 3
```

### 输出

```
40
```

## 样例 #2

### 输入

```
4 4
100 100 100 100
1 2
2 3
2 4
3 4
```

### 输出

```
400
```

## 样例 #3

### 输入

```
7 10
40 10 20 10 20 80 40
1 5
4 7
4 5
5 2
5 7
6 4
1 6
1 3
4 3
1 4
```

### 输出

```
160
```

# AI分析结果

### 题目中文重写
# 孩子与玩具

## 题目描述
在儿童节，孩子从Delayyy那里得到了一个玩具作为礼物。然而，这个孩子非常调皮，他迫不及待地想要毁掉这个玩具。

这个玩具由 $n$ 个部件和 $m$ 条绳子组成。每条绳子连接两个部件，但每对部件最多由一条绳子连接。为了拆开这个玩具，孩子必须移除所有的部件。孩子每次可以移除一个部件，并且每次移除都需要消耗一定的能量。我们定义部件 $i$ 的能量值为 $v_{i}$。当孩子移除部件 $i$ 时，他需要消耗 $v_{f1}+v_{f2}+...+v_{fk}$ 的能量，其中 $f_{1},f_{2},...,f_{k}$ 是与第 $i$ 个部件直接相连且尚未被移除的部件。

帮助孩子找出移除所有 $n$ 个部件所需的最小总能量。

## 说明/提示
第一个样例的一个最优操作序列如下：
- 首先，移除部件 $3$，此操作的代价为 $20$。
- 然后，移除部件 $2$，此操作的代价为 $10$。
- 接着，移除部件 $4$，此操作的代价为 $10$。
- 最后，移除部件 $1$，此操作的代价为 $0$。

因此，孩子支付的总能量为 $20 + 10 + 10 + 0 = 40$，这是最小值。

在第二个样例中，无论孩子以何种顺序移除部件，他都将花费 $400$ 的能量。

## 样例 #1
### 输入
```
4 3
10 20 30 40
1 4
1 2
2 3
```
### 输出
```
40
```

## 样例 #2
### 输入
```
4 4
100 100 100 100
1 2
2 3
2 4
3 4
```
### 输出
```
400
```

## 样例 #3
### 输入
```
7 10
40 10 20 10 20 80 40
1 5
4 7
4 5
5 2
5 7
6 4
1 6
1 3
4 3
1 4
```
### 输出
```
160
```

### 题解综合分析与结论
这些题解主要围绕贪心算法展开，多数思路是将删点问题转化为删边问题，通过计算每条边两端点权值的最小值之和来得到删除所有点的最小代价。部分题解还考虑了拓扑排序和缩点，但最终核心计算方式相同。
|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|无心揽青丝|将删点转化为删边，每次删边时取两端点权值最小值累加|遍历每条边，取两端点权值最小值相加|无|5星|
|KEBrantily|按点权从大到小排序依次删点|排序后依次删点并累加贡献|无|3星|
|little_sun|从边权大的点向边权小的点连边，用tarjan缩点后跑拓扑排序|tarjan缩点和拓扑排序|处理点权相等形成的环|2星|
|Prean|考虑边的贡献，取边两端点权值较小值累加|遍历边累加最小值|无|5星|
|Evfidiw|贪心找出最大点，保证每条边选较小点权消耗|遍历边取两端点权值最小值累加|无|4星|
|雄鹰展翅|从边的视角切入，按点权从大到小删点|遍历边取两端点权值最小值累加|无|4星|
|nalemy|节点按点权从小到大排序，从后往前删点|遍历边取两端点权值最小值累加|无|4星|
|傅思维666|每次删除当前未删点中权值最大的点|优先队列维护最大点权|无|3星|
|寒鸽儿|考虑边的贡献，取边两端点权值较小值累加|遍历边累加最小值|无|4星|
|nekko|从点权大到小删点，边的贡献为较小点权|遍历边取两端点权值最小值累加|无|4星|
|Aw顿顿|从边入手，累加边两端点权值较小值|遍历边累加最小值|将删点问题转化为删边问题|4星|
|Phoenix_chaser|一边建边一边删边，取代价小的点去掉|遍历边取两端点权值最小值累加|无|4星|
|YanYou|权值大的点先删，边的代价为两端点较小权值|遍历边累加最小值|无|4星|
|EdenHazard|每次删去x,y中最小的，累加代价|遍历边取两端点权值最小值累加|无|4星|
|DennyQi|将无向边改为有向边，用tarjan缩点后拓扑排序|tarjan缩点和拓扑排序|处理点权相等形成的环|2星|
|Mickey_snow|从边的角度考虑，贪心取边两端点最小价值累加|遍历边累加最小值|无|4星|
|人间凡人|逐边考虑，每次删权值较大点，累加较小权值|遍历边累加最小值|无|4星|

### 所选题解
- **无心揽青丝（5星）**：关键亮点是思路清晰，直接将删点问题转化为删边问题，代码简洁高效。
```cpp
#include<bits/stdc++.h>
#define itn int
#define ll long long
using namespace std;
int n,m,a[1005],x,y;
ll ans;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",a+i);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        ans+=min(a[x],a[y]);
    }
    printf("%lld",ans);
    return 0;
}
```
核心实现思想：先读取点的数量、边的数量和每个点的权值，然后遍历每条边，将边两端点权值的最小值累加到答案中，最后输出答案。

- **Prean（5星）**：关键亮点是思路简洁明了，直接点明考虑边的贡献，代码实现简单。
```cpp
#include<cstdio>
const int M=1e5+5;
int n,m,a[M];
long long ans;
inline int min(const int&a,const int&b){
    return a>b?b:a;
}
signed main(){
    register int i,u,v;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;++i)scanf("%d",a+i);
    for(i=1;i<=m;++i){
        scanf("%d%d",&u,&v);
        ans+=min(a[u],a[v]);
    }
    printf("%lld",ans);
}
```
核心实现思想：读取输入，遍历每条边，将边两端点权值的最小值累加到答案中并输出。

- **Evfidiw（4星）**：关键亮点是利用贪心思想，通过遍历边取最小值来求解，代码规范。
```cpp
#pragma G++ optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;
#define REG register
#define REP(i,x,y) for(REG int i=x;i<=y;i++)
#define UP(i,x,y) for(REG int i=x;i>=y;i--)
#define IN inline
#define LL long long
#define inf 0x3f3f3f3f

const int maxn=2005;
LL ans=0;
int w[maxn];

int main(){
    int n,m;
    scanf("%d %d",&n,&m) ;
    REP(i,1,n) scanf("%d",&w[i]);
    REP(i,1,m){
        int x,y;
        scanf("%d %d",&x,&y);
        ans+=min(w[x],w[y]);
    }
    printf("%lld",ans);
    return 0;
}
```
核心实现思想：读取输入，通过循环遍历每条边，取边两端点权值的最小值累加到答案中，最后输出结果。

### 最优关键思路或技巧
将删点问题转化为删边问题，从边的角度考虑，每条边的贡献取两端点权值的最小值，这样可以简化问题，避免复杂的删点顺序分析。

### 可拓展之处
同类型题可能会改变图的类型（如有向图、带权图）或增加其他限制条件，但核心思路依然可以从边或点的贡献角度出发，运用贪心算法求解。类似算法套路还有在图的操作中，通过转化问题视角（如点和边的转化）来简化问题。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法，通过合并果子的操作求最小代价。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：运用贪心思想，合理安排排队顺序使总等待时间最小。
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：贪心选择单位价值最高的物品放入背包，求最大价值。

### 个人心得摘录与总结
- **傅思维666**：考场上看到最优化先想DP但无法划分状态，后尝试贪心，手推样例找到规律，未证明贪心就过了大样例。总结是遇到最优化问题可先尝试常见算法，若不行再考虑贪心，可通过手推样例找规律。
- **little_sun**：一开始用拓扑排序写题WA，分析后发现点权相等会形成环，拓扑排序只对DAG有效，于是用tarjan缩点后AC。总结是在使用拓扑排序时要考虑图中是否存在环，若有环可尝试缩点处理。 

---
处理用时：52.61秒