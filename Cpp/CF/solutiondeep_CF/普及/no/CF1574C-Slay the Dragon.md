# 题目信息

# Slay the Dragon

## 题目描述

Recently, Petya learned about a new game "Slay the Dragon". As the name suggests, the player will have to fight with dragons. To defeat a dragon, you have to kill it and defend your castle. To do this, the player has a squad of $ n $ heroes, the strength of the $ i $ -th hero is equal to $ a_i $ .

According to the rules of the game, exactly one hero should go kill the dragon, all the others will defend the castle. If the dragon's defense is equal to $ x $ , then you have to send a hero with a strength of at least $ x $ to kill it. If the dragon's attack power is $ y $ , then the total strength of the heroes defending the castle should be at least $ y $ .

The player can increase the strength of any hero by $ 1 $ for one gold coin. This operation can be done any number of times.

There are $ m $ dragons in the game, the $ i $ -th of them has defense equal to $ x_i $ and attack power equal to $ y_i $ . Petya was wondering what is the minimum number of coins he needs to spend to defeat the $ i $ -th dragon.

Note that the task is solved independently for each dragon (improvements are not saved).

## 说明/提示

To defeat the first dragon, you can increase the strength of the third hero by $ 1 $ , then the strength of the heroes will be equal to $ [3, 6, 3, 3] $ . To kill the dragon, you can choose the first hero.

To defeat the second dragon, you can increase the forces of the second and third heroes by $ 1 $ , then the strength of the heroes will be equal to $ [3, 7, 3, 3] $ . To kill the dragon, you can choose a second hero.

To defeat the third dragon, you can increase the strength of all the heroes by $ 1 $ , then the strength of the heroes will be equal to $ [4, 7, 3, 4] $ . To kill the dragon, you can choose a fourth hero.

To defeat the fourth dragon, you don't need to improve the heroes and choose a third hero to kill the dragon.

To defeat the fifth dragon, you can increase the strength of the second hero by $ 2 $ , then the strength of the heroes will be equal to $ [3, 8, 2, 3] $ . To kill the dragon, you can choose a second hero.

## 样例 #1

### 输入

```
4
3 6 2 3
5
3 12
7 9
4 14
1 10
8 7```

### 输出

```
1
2
4
0
2```

# AI分析结果

### 题目内容重写

#### 题目描述

最近，Petya 了解到了一款新游戏“Slay the Dragon”。顾名思义，玩家需要与龙战斗。为了击败一条龙，玩家需要杀死它并保卫自己的城堡。为此，玩家拥有一支由 $n$ 个英雄组成的队伍，第 $i$ 个英雄的力量为 $a_i$。

根据游戏规则，玩家需要派出一名英雄去杀死龙，其他英雄则负责保卫城堡。如果龙的防御值为 $x$，那么派出的英雄的力量必须至少为 $x$。如果龙的攻击力为 $y$，那么所有保卫城堡的英雄的力量之和必须至少为 $y$。

玩家可以通过花费一枚金币将任意英雄的力量提升 $1$。这个操作可以进行任意次数。

游戏中有 $m$ 条龙，第 $i$ 条龙的防御值为 $x_i$，攻击力为 $y_i$。Petya 想知道，击败第 $i$ 条龙所需的最少金币数是多少。

注意，每个龙的挑战是独立解决的（提升的力量不会保留）。

#### 样例输入

```
4
3 6 2 3
5
3 12
7 9
4 14
1 10
8 7
```

#### 样例输出

```
1
2
4
0
2
```

### 算法分类

贪心、二分、排序

### 题解分析与结论

该题的核心思路是通过贪心策略和二分查找来优化金币的使用。具体来说，对于每条龙，我们需要找到一个英雄去击败它，并且剩下的英雄能够保卫城堡。通过排序和二分查找，我们可以快速找到满足条件的最优英雄，并计算所需的最小金币数。

### 精选题解

#### 题解1：作者：Wuyanru (赞：3)

**星级：4星**

**关键亮点：**
- 通过二分查找快速定位满足条件的英雄。
- 分别考虑派出力量大于等于龙防御值的英雄和派出力量小于龙防御值的英雄两种情况，取最小值。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
int num=lower_bound(a+1,a+n+1,x)-a;
if(num!=n+1)
    ans=max(y-(sum-a[num]),0ll);
num--;
if(num)
    ans=min(ans,x-a[num]+max(y-(sum-a[num]),0ll));
```

**个人心得：**
- 通过二分查找优化了查找过程，避免了暴力搜索的低效。

#### 题解2：作者：引领天下 (赞：0)

**星级：4星**

**关键亮点：**
- 详细证明了贪心策略的正确性，确保派出英雄的最优性。
- 通过二分查找快速定位满足条件的英雄，并处理边界情况。
- 代码结构清晰，注释详细。

**核心代码：**
```cpp
int k=lower_bound(a+1,a+n+1,x)-a;
if(a[k]<x)cout<<(x-a[n]+max(y-(sum-a[n]),0ll))<<endl;
else cout<<min((k>1?x-a[k-1]+max(y-(sum-a[k-1]),0ll):1ll<<60),max(y-(sum-a[k]),0ll))<<endl;
```

**个人心得：**
- 通过二分查找和贪心策略的结合，确保了算法的效率和正确性。

#### 题解3：作者：Jerrywang09 (赞：0)

**星级：4星**

**关键亮点：**
- 详细分析了不同情况下的最优策略，并提供了优化建议。
- 通过预处理和输入输出优化，提高了代码的执行效率。
- 代码结构清晰，注释详细。

**核心代码：**
```cpp
var k=lower_bound(a, a+n, x)-a;
if(k==0) {
    var s=getsumWithout(a, n, k);
    if(s<y) cout<<y-s<<endl;
    else cout<<0<<endl;
    continue;
}
if(k!=n) {
    var res1 = (s=getsumWithout(a, n, k)) < y ? y-s : 0;
    var res2 = x-a[k-1] + ((s=getsumWithout(a, n, k-1)) < y ? y-s : 0);
    cout<<min(res1, res2)<<endl;
}
else {
    var s=getsumWithout(a, n, maxi);
    if(s<y) cout<<y-s+x-a[maxi]<<endl;
    else cout<<x-a[maxi]<<endl;
}
```

**个人心得：**
- 通过预处理和优化，确保了代码的高效执行，避免了不必要的计算。

### 最优关键思路或技巧

1. **排序与二分查找**：通过排序英雄的力量值，并使用二分查找快速定位满足条件的英雄，极大地提高了查找效率。
2. **贪心策略**：通过贪心策略选择最优的英雄去击败龙，并确保剩下的英雄能够保卫城堡，从而最小化金币的使用。
3. **边界处理**：在处理边界情况时，如没有英雄满足条件时，选择力量最大的英雄进行升级，确保算法的鲁棒性。

### 可拓展之处

该题的思路可以拓展到其他需要优化资源分配的问题，如任务调度、资源分配等。通过贪心策略和二分查找的结合，可以高效地解决类似的问题。

### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心、优先队列
2. [P1168 中位数](https://www.luogu.com.cn/problem/P1168) - 排序、二分查找
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 动态规划、贪心

---
处理用时：40.91秒