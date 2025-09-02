# 题目信息

# Petya and Catacombs

## 题目描述

A very brave explorer Petya once decided to explore Paris catacombs. Since Petya is not really experienced, his exploration is just walking through the catacombs.

Catacombs consist of several rooms and bidirectional passages between some pairs of them. Some passages can connect a room to itself and since the passages are built on different depths they do not intersect each other. Every minute Petya arbitrary chooses a passage from the room he is currently in and then reaches the room on the other end of the passage in exactly one minute. When he enters a room at minute $ i $ , he makes a note in his logbook with number $ t_{i} $ :

- If Petya has visited this room before, he writes down the minute he was in this room last time;
- Otherwise, Petya writes down an arbitrary non-negative integer strictly less than current minute $ i $ .

Initially, Petya was in one of the rooms at minute $ 0 $ , he didn't write down number $ t_{0} $ .

At some point during his wandering Petya got tired, threw out his logbook and went home. Vasya found his logbook and now he is curious: what is the minimum possible number of rooms in Paris catacombs according to Petya's logbook?

## 说明/提示

In the first sample, sequence of rooms Petya visited could be, for example $ 1→1→2 $ , $ 1→2→1 $ or $ 1→2→3 $ . The minimum possible number of rooms is $ 2 $ .

In the second sample, the sequence could be $ 1→2→3→1→2→1 $ .

## 样例 #1

### 输入

```
2
0 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
0 1 0 1 3
```

### 输出

```
3
```

# AI分析结果

### 题目内容翻译
# 佩佳与地下墓穴

## 题目描述
一位非常勇敢的探险家佩佳（Petya）曾经决定去探索巴黎的地下墓穴。由于佩佳经验不足，他的探索方式仅仅是在地下墓穴中漫步。

地下墓穴由若干房间以及一些房间对之间的双向通道组成。有些通道可以将一个房间与自身相连，并且由于通道建在不同的深度，它们不会相互交叉。每分钟，佩佳会随机选择一条从他当前所在房间出发的通道，然后在恰好一分钟内到达通道另一端的房间。当他在第 $i$ 分钟进入一个房间时，他会在日志中记录一个数字 $t_{i}$：
- 如果佩佳之前来过这个房间，他会写下他上次在这个房间的分钟数；
- 否则，佩佳会写下一个严格小于当前分钟数 $i$ 的任意非负整数。

最初，佩佳在第 0 分钟时位于其中一个房间，他没有记录数字 $t_{0}$。

在漫步的某个时刻，佩佳感到疲惫，扔掉了他的日志然后回家了。瓦夏（Vasya）发现了他的日志，现在他很好奇：根据佩佳的日志，巴黎地下墓穴中最少可能有多少个房间？

## 说明/提示
在第一个样例中，佩佳访问的房间序列可能是，例如 $1→1→2$、$1→2→1$ 或 $1→2→3$。最少可能的房间数是 $2$。

在第二个样例中，序列可能是 $1→2→3→1→2→1$。

## 样例 #1
### 输入
```
2
0 0
```
### 输出
```
2
```

## 样例 #2
### 输入
```
5
0 1 0 1 3
```
### 输出
```
3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心策略，即让随机数出现的次数最少，从而使图中的点数最少。大部分题解使用数组来记录数字是否可能是上一次来到该位置的时间，通过判断输入数字对应的标记来确定是否新增房间。部分题解将问题转化为树的链分割问题，统计叶子节点个数。

### 所选题解
- **作者：Noby_Glds (赞：3)  4星**
    - **关键亮点**：思路清晰，详细阐述了数字的两种类型以及如何通过 $vis$ 数组判断是否新增房间，代码简洁易懂。
- **作者：Soojin2012 (赞：3)  4星**
    - **关键亮点**：对思路的解释清晰，强调了使随机数最少的贪心策略，代码有输入输出优化。
- **作者：yhx0322 (赞：0)  4星**
    - **关键亮点**：明确分析出要使图中点的数量最少，必须使随机数字尽可能少的性质，代码有输入输出流优化。

### 重点代码
```cpp
// Noby_Glds的代码
#include<bits/stdc++.h>
using namespace std;
int n,ans=1,vis[200010],p;
int main(){
    scanf("%d",&n);
    vis[0]=1;
    for(int i=1;i<=n;i++){
        scanf("%d",&p);
        if(vis[p]==0) ans++;
        else vis[p]=0;
        vis[i]=1;
    }
    cout<<ans;
    return 0;
}

// Soojin2012的代码
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main(){
   int n,ans=1,m;
   ios::sync_with_stdio(false);
    cin>>n;
    a[0]=1;
    for(int i=1;i<=n;i++){
        cin>>m;
        if(a[m]==0) ans++;
        else a[m]=0;
        a[i]=1;
    }
    cout<<ans;
    return 0;
}

// yhx0322的代码
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int f[N], n, num = 1, x;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (!f[x]) num++;
        else f[x] = 0;
        f[i] = 1;
    }
    cout << num;
    return 0;
}
```
**核心实现思想**：用数组记录每个数字是否可能是上一次来到该位置的时间，初始时 $vis[0]$ 或 $a[0]$ 或 $f[0]$ 设为 $1$，表示佩佳一开始就在一个房间。遍历输入的数字，如果该数字对应的标记为 $0$，则房间数加一，否则将该标记设为 $0$，并将当前时间对应的标记设为 $1$。

### 扩展思路
同类型题可能会改变规则或条件，例如通道变为单向、记录数字的规则更复杂等，但核心的贪心思想不变，即尽量让某些情况出现的次数最少。类似算法套路可以应用在其他需要优化资源使用或减少某种操作次数的问题中。

### 推荐题目
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得
部分作者提到题目第一眼感觉很难，但想到思路后就觉得是水题，这说明解题时要仔细分析题目条件，找到关键的解题思路。还有作者在思考树链剖分的解法时，经同学提醒发现可以统计叶子节点，这体现了交流和思维碰撞的重要性。 

---
处理用时：38.98秒