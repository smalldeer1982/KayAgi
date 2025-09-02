# 题目信息

# Jumping Through Segments

## 题目描述

Polycarp is designing a level for a game. The level consists of $ n $ segments on the number line, where the $ i $ -th segment starts at the point with coordinate $ l_i $ and ends at the point with coordinate $ r_i $ .

The player starts the level at the point with coordinate $ 0 $ . In one move, they can move to any point that is within a distance of no more than $ k $ . After their $ i $ -th move, the player must land within the $ i $ -th segment, that is, at a coordinate $ x $ such that $ l_i \le x \le r_i $ . This means:

- After the first move, they must be inside the first segment (from $ l_1 $ to $ r_1 $ );
- After the second move, they must be inside the second segment (from $ l_2 $ to $ r_2 $ );
- ...
- After the $ n $ -th move, they must be inside the $ n $ -th segment (from $ l_n $ to $ r_n $ ).

The level is considered completed if the player reaches the $ n $ -th segment, following the rules described above. After some thought, Polycarp realized that it is impossible to complete the level with some values of $ k $ .

Polycarp does not want the level to be too easy, so he asks you to determine the minimum integer $ k $ with which it is possible to complete the level.

## 说明/提示

In the third example, the player can make the following moves:

- Move from point $ 0 $ to point $ 5 $ ( $ 3 \le 5 \le 8 $ );
- Move from point $ 5 $ to point $ 10 $ ( $ 10 \le 10 \le 18 $ );
- Move from point $ 10 $ to point $ 7 $ ( $ 6 \le 7 \le 11 $ ).

Note that for the last move, the player could have chosen not to move and still complete the level.

## 样例 #1

### 输入

```
4
5
1 5
3 4
5 6
8 10
0 1
3
0 2
0 1
0 3
3
3 8
10 18
6 11
4
10 20
0 5
15 17
2 2```

### 输出

```
7
0
5
13```

# AI分析结果

### 题目内容重写

**题目描述**

Polycarp正在为一个游戏设计关卡。该关卡由数轴上的$n$个线段组成，第$i$个线段的起点坐标为$l_i$，终点坐标为$r_i$。

玩家从坐标$0$开始，每次移动可以跳到距离不超过$k$的任意点。在第$i$次移动后，玩家必须落在第$i$个线段内，即坐标$x$满足$l_i \le x \le r_i$。这意味着：

- 第一次移动后，玩家必须位于第一个线段内（从$l_1$到$r_1$）；
- 第二次移动后，玩家必须位于第二个线段内（从$l_2$到$r_2$）；
- ...
- 第$n$次移动后，玩家必须位于第$n$个线段内（从$l_n$到$r_n$）。

如果玩家按照上述规则成功到达第$n$个线段，则关卡完成。经过思考，Polycarp发现某些$k$值无法完成关卡。

Polycarp不希望关卡过于简单，因此他请你确定能够完成关卡的最小整数$k$。

**说明/提示**

在第三个样例中，玩家可以进行如下移动：

- 从点$0$跳到点$5$（$3 \le 5 \le 8$）；
- 从点$5$跳到点$10$（$10 \le 10 \le 18$）；
- 从点$10$跳到点$7$（$6 \le 7 \le 11$）。

注意，最后一次移动玩家可以选择不移动，仍然完成关卡。

### 题解分析与结论

#### 综合分析与结论

本题的核心是找到最小的$k$，使得玩家能够在每次移动后落在对应的线段内。所有题解都采用了二分搜索的思路，通过二分枚举$k$的值，并检查该$k$是否满足条件。检查的方法是通过维护一个区间$[lef, rig]$，表示玩家当前可能的位置范围，每次移动后更新该区间，并判断是否与目标线段有交集。

#### 所选高星题解

1. **作者：abensyl (5星)**
   - **关键亮点**：思路清晰，代码简洁，维护区间的方法非常直观，且通过二分搜索高效地找到最小$k$。
   - **核心代码**：
     ```cpp
     bool check(int k,int n) {
         int posl=0,posr=0;
         for(int i=1;i<=n;++i) {
             posl=posl-k,posr=posr+k;
             if(posl>r[i]||posr<l[i]) return false;
             posl=max(posl,l[i]),posr=min(posr,r[i]);
         } return true;
     }
     ```
   - **个人心得**：通过维护区间$[posl, posr]$，每次移动后更新该区间，并判断是否与目标线段有交集，这种方法非常高效且易于理解。

2. **作者：kimidonatsu (4星)**
   - **关键亮点**：代码简洁，思路清晰，通过二分搜索和区间维护的方法快速找到最小$k$。
   - **核心代码**：
     ```cpp
     bool check(int k) {
         int l = 0, r = 0;
         for (int i = 1; i <= n; i++) {
             l = max(l - k, a[i].first);
             r = min(r + k, a[i].second);
             if (l > r) return 0;
         }
         return 1;
     }
     ```
   - **个人心得**：通过维护区间$[l, r]$，每次移动后更新该区间，并判断是否与目标线段有交集，这种方法非常直观且易于实现。

3. **作者：WAis_WonderfulAnswer (4星)**
   - **关键亮点**：代码简洁，思路清晰，通过二分搜索和区间维护的方法快速找到最小$k$。
   - **核心代码**：
     ```cpp
     bool check(int k)
     {
         int ll=0,rr=0;
         for (int i=1;i<=n;i++)
         {
             ll=max(ll-k,l[i]);
             rr=min(rr+k,r[i]);
             if (ll>rr) return false;
         }
         return true;
     }
     ```
   - **个人心得**：通过维护区间$[ll, rr]$，每次移动后更新该区间，并判断是否与目标线段有交集，这种方法非常高效且易于理解。

### 最优关键思路或技巧

- **二分搜索**：通过二分枚举$k$的值，快速找到满足条件的最小$k$。
- **区间维护**：维护一个区间$[lef, rig]$，表示玩家当前可能的位置范围，每次移动后更新该区间，并判断是否与目标线段有交集。

### 可拓展之处

- **类似问题**：类似的问题可以扩展到多维空间，或者增加移动的限制条件（如只能向某个方向移动）。
- **算法套路**：二分搜索结合区间维护的方法可以应用于其他需要找到最小或最大值的优化问题。

### 推荐题目

1. **洛谷P1020 导弹拦截**：考察二分搜索和动态规划的结合。
2. **洛谷P1886 滑动窗口**：考察区间维护和单调队列的应用。
3. **洛谷P3382 【模板】三分法**：考察三分搜索在凸函数中的应用。

---
处理用时：42.68秒