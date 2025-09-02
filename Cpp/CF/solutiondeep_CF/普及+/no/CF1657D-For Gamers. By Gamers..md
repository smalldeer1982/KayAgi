# 题目信息

# For Gamers. By Gamers.

## 题目描述

Monocarp is playing a strategy game. In the game, he recruits a squad to fight monsters. Before each battle, Monocarp has $ C $ coins to spend on his squad.

Before each battle starts, his squad is empty. Monocarp chooses one type of units and recruits no more units of that type than he can recruit with $ C $ coins.

There are $ n $ types of units. Every unit type has three parameters:

- $ c_i $ — the cost of recruiting one unit of the $ i $ -th type;
- $ d_i $ — the damage that one unit of the $ i $ -th type deals in a second;
- $ h_i $ — the amount of health of one unit of the $ i $ -th type.

Monocarp has to face $ m $ monsters. Every monster has two parameters:

- $ D_j $ — the damage that the $ j $ -th monster deals in a second;
- $ H_j $ — the amount of health the $ j $ -th monster has.

Monocarp has to fight only the $ j $ -th monster during the $ j $ -th battle. He wants all his recruited units to stay alive. Both Monocarp's squad and the monster attack continuously (not once per second) and at the same time. Thus, Monocarp wins the battle if and only if his squad kills the monster strictly faster than the monster kills one of his units. The time is compared with no rounding.

For each monster, Monocarp wants to know the minimum amount of coins he has to spend to kill that monster. If this amount is greater than $ C $ , then report that it's impossible to kill that monster.

## 说明/提示

Consider the first monster of the first example.

Monocarp can't recruit one unit of the first type, because it will take both him and the monster $ 0.75 $ seconds to kill each other. He can recruit two units for the cost of $ 6 $ coins and kill the monster in $ 0.375 $ second.

Monocarp can recruit one unit of the second type, because he kills the monster in $ 0.6 $ seconds, and the monster kills him in $ 0.625 $ seconds. The unit is faster. Thus, $ 5 $ coins is enough.

Monocarp will need at least three units of the third type to kill the first monster, that will cost $ 30 $ coins.

Monocarp will spend the least coins if he chooses the second type of units and recruits one unit of that type.

## 样例 #1

### 输入

```
3 10
3 4 6
5 5 5
10 3 4
3
8 3
5 4
10 15```

### 输出

```
5 3 -1```

## 样例 #2

### 输入

```
5 15
14 10 3
9 2 2
10 4 3
7 3 5
4 3 1
6
11 2
1 1
4 7
2 1
1 14
3 3```

### 输出

```
14 4 14 4 7 7```

## 样例 #3

### 输入

```
5 13
13 1 9
6 4 5
12 18 4
9 13 2
5 4 5
2
16 3
6 2```

### 输出

```
12 5```

# AI分析结果

### 题目内容翻译
# 为玩家打造，由玩家创作。

## 题目描述
Monocarp正在玩一款策略游戏。在游戏中，他招募一支小队来对抗怪物。在每场战斗前，Monocarp有 $C$ 枚硬币可用于招募小队成员。

每场战斗开始前，他的小队是空的。Monocarp选择一种类型的单位，并且招募的该类型单位数量不超过他用 $C$ 枚硬币所能招募的数量。

有 $n$ 种类型的单位。每种单位类型有三个参数：
- $c_i$ —— 招募一个第 $i$ 种类型单位的成本；
- $d_i$ —— 一个第 $i$ 种类型单位每秒造成的伤害；
- $h_i$ —— 一个第 $i$ 种类型单位的生命值。

Monocarp必须面对 $m$ 个怪物。每个怪物有两个参数：
- $D_j$ —— 第 $j$ 个怪物每秒造成的伤害；
- $H_j$ —— 第 $j$ 个怪物的生命值。

在第 $j$ 场战斗中，Monocarp只需要对抗第 $j$ 个怪物。他希望他招募的所有单位都能存活下来。Monocarp的小队和怪物都持续攻击（不是每秒攻击一次）且同时进行。因此，当且仅当他的小队比怪物更快地杀死怪物（时间比较不进行四舍五入）时，Monocarp才能赢得战斗。

对于每个怪物，Monocarp想知道他杀死该怪物所需的最少硬币数量。如果这个数量大于 $C$，则报告无法杀死该怪物。

## 说明/提示
考虑第一个样例中的第一个怪物。

Monocarp不能招募一个第一种类型的单位，因为他和怪物都需要 $0.75$ 秒才能杀死对方。他可以花费 $6$ 枚硬币招募两个单位，并在 $0.375$ 秒内杀死怪物。

Monocarp可以招募一个第二种类型的单位，因为他在 $0.6$ 秒内杀死怪物，而怪物在 $0.625$ 秒内杀死他。该单位更快。因此，$5$ 枚硬币就足够了。

Monocarp至少需要三个第三种类型的单位才能杀死第一个怪物，这将花费 $30$ 枚硬币。

如果Monocarp选择第二种类型的单位并招募一个该类型的单位，他将花费最少的硬币。

## 样例 #1
### 输入
```
3 10
3 4 6
5 5 5
10 3 4
3
8 3
5 4
10 15
```
### 输出
```
5 3 -1
```

## 样例 #2
### 输入
```
5 15
14 10 3
9 2 2
10 4 3
7 3 5
4 3 1
6
11 2
1 1
4 7
2 1
1 14
3 3
```
### 输出
```
14 4 14 4 7 7
```

## 样例 #3
### 输入
```
5 13
13 1 9
6 4 5
12 18 4
9 13 2
5 4 5
2
16 3
6 2
```
### 输出
```
12 5
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是先对士兵的属性进行预处理，将战斗胜负条件转化为比较士兵和怪物的“属性值”（攻击力与生命值的乘积），然后通过动态规划的方式预处理出每种花费能达到的最大属性值，最后对于每个询问，使用二分查找来找到满足条件的最小花费。

不同题解的主要区别在于预处理和剪枝的方式：
- pocafup 的题解通过对士兵按 $d \times h$ 从大到小排序，并使用单调队列的思想进行剪枝，避免了使用一些不优的士兵。
- Genius_Star 的题解直接通过动态规划的状态转移方程 $dp_{i \times j}=\max(dp_{i \times j},dp_i \times j)$ 来更新每种花费的最大属性值。
- XL4453 的题解在枚举士兵时，只考虑每种钱数中属性最高的战士进行枚举，避免了重复计算。
- youdu666 的题解对士兵按价格和战斗力排序，对于价格相同的士兵只考虑战斗力高的，进行剪枝。
- GaryH 的题解通过数学推导，利用因数个数的性质，暴力更新每种花费的最大属性值。

### 所选题解
- pocafup 的题解（4星）
  - 关键亮点：思路清晰，使用单调队列思想进行剪枝，复杂度分析详细。
  - 个人心得：场上读了二十分钟仍然读不懂 C 的样例，只能写 D 了。
- Genius_Star 的题解（4星）
  - 关键亮点：思路清晰，动态规划的状态转移方程明确，代码实现简洁。
- youdu666 的题解（4星）
  - 关键亮点：思路清晰，对士兵进行排序和剪枝，保证了单调性。

### 重点代码
#### pocafup 的题解核心代码
```cpp
struct Node{
  int c,d,h;
  bool operator < (const Node &o) const{
    return d*h>o.d*o.h;
  }//排序: d*h 大在前面
}node[MAXN];
inline int bs(int val){
  int l = 1, r = C;
  while(l!=r){
    int mid = (l+r)>>1;
    if (dp[mid]>val) r = mid;
    else l = mid+1;
  }//直接二分
  return dp[l]>val ? l : -1;
}
// ...
sort(node+1,node+1+n);
int pre = 1e9;
For(i,1,n){
  if (node[i].c>=pre) continue;
  pre = node[i].c;
  for (int j=1;j*node[i].c<=C;j++){
    dp[j*node[i].c] = chkmax(dp[j*node[i].c],j*node[i].d*node[i].h);
  }
}
For(i,1,C) dp[i] = chkmax(dp[i],dp[i-1]);//求个前缀最大
```
核心实现思想：先对士兵按 $d \times h$ 从大到小排序，使用单调队列思想剪枝，然后枚举每个士兵及其倍数，更新每种花费的最大属性值，最后求前缀最大值。

#### Genius_Star 的题解核心代码
```cpp
for(int i=1;i<=n;i++){
  x=read(),y=read(),z=read();
  dp[x]=max(dp[x],y*z);
}
for(int i=1;i<=k;i++)
  for(int j=2;i*j<=k;j++)
    dp[i*j]=max(dp[i*j],dp[i]*j);
for(int i=1;i<=k;i++) 
  dp[i]=max(dp[i],dp[i-1]);
```
核心实现思想：先初始化每种花费的最大属性值，然后通过动态规划的状态转移方程更新每种花费的最大属性值，最后求前缀最大值。

#### youdu666 的题解核心代码
```cpp
bool cmp(army a,army b)
{
    return a.m==b.m?a.vs>b.vs:a.m<b.m;
}
// ...
sort(a+1,a+n+1,cmp);
for(int i=1;i<=n;i++)
{
    if(i>1&&a[i].m==a[i-1].m) continue;
    for(int j=a[i].m;j<=m;j+=a[i].m)
        ok[j]=max(ok[j],j/a[i].m*a[i].vs);
}
int mx=ok[1];
for(int i=2;i<=m;i++)
{
    if(ok[i]>mx) mx=ok[i];
    else ok[i]=mx;
}
```
核心实现思想：先对士兵按价格和战斗力排序，对于价格相同的士兵只考虑战斗力高的，进行剪枝，然后枚举每个士兵及其倍数，更新每种花费的最大属性值，最后保证单调性。

### 最优关键思路或技巧
- **数学转化**：将战斗胜负条件转化为比较士兵和怪物的“属性值”（攻击力与生命值的乘积），简化了问题的处理。
- **动态规划预处理**：通过动态规划的方式预处理出每种花费能达到的最大属性值，避免了重复计算。
- **剪枝优化**：使用单调队列、排序等方法进行剪枝，避免了使用一些不优的士兵，降低了时间复杂度。

### 拓展思路
同类型题或类似算法套路：
- 这类问题通常涉及到资源分配和比较，在其他游戏策略问题、资源优化问题中也可能会遇到。
- 可以将问题拓展到多种资源限制、多种单位组合等情况，需要考虑更复杂的动态规划状态和转移方程。

### 推荐洛谷题目
- P1048 [NOIP2005 普及组] 采药
- P1060 [NOIP2006 普及组] 开心的金明
- P1616 疯狂的采药

---
处理用时：64.56秒