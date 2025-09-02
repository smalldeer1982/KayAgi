# 题目信息

# Kill the Monster

## 题目描述

Monocarp is playing a computer game. In this game, his character fights different monsters.

A fight between a character and a monster goes as follows. Suppose the character initially has health $ h_C $ and attack $ d_C $ ; the monster initially has health $ h_M $ and attack $ d_M $ . The fight consists of several steps:

1. the character attacks the monster, decreasing the monster's health by $ d_C $ ;
2. the monster attacks the character, decreasing the character's health by $ d_M $ ;
3. the character attacks the monster, decreasing the monster's health by $ d_C $ ;
4. the monster attacks the character, decreasing the character's health by $ d_M $ ;
5. and so on, until the end of the fight.

The fight ends when someone's health becomes non-positive (i. e. $ 0 $ or less). If the monster's health becomes non-positive, the character wins, otherwise the monster wins.

Monocarp's character currently has health equal to $ h_C $ and attack equal to $ d_C $ . He wants to slay a monster with health equal to $ h_M $ and attack equal to $ d_M $ . Before the fight, Monocarp can spend up to $ k $ coins to upgrade his character's weapon and/or armor; each upgrade costs exactly one coin, each weapon upgrade increases the character's attack by $ w $ , and each armor upgrade increases the character's health by $ a $ .

Can Monocarp's character slay the monster if Monocarp spends coins on upgrades optimally?

## 说明/提示

In the first example, Monocarp can spend one coin to upgrade weapon (damage will be equal to $ 5 $ ), then health during battle will change as follows: $ (h_C, h_M) = (25, 9) \rightarrow (25, 4) \rightarrow (5, 4) \rightarrow (5, -1) $ . The battle ended with Monocarp's victory.

In the second example, Monocarp has no way to defeat the monster.

In the third example, Monocarp has no coins, so he can't buy upgrades. However, the initial characteristics are enough for Monocarp to win.

In the fourth example, Monocarp has $ 4 $ coins. To defeat the monster, he has to spend $ 2 $ coins to upgrade weapon and $ 2 $ coins to upgrade armor.

## 样例 #1

### 输入

```
4
25 4
9 20
1 1 10
25 4
12 20
1 1 10
100 1
45 2
0 4 10
9 2
69 2
4 2 7```

### 输出

```
YES
NO
YES
YES```

# AI分析结果

### 题目内容重写

Monocarp 正在玩一款电脑游戏。在游戏中，他的角色与不同的怪物战斗。

角色与怪物之间的战斗过程如下：假设角色初始有血量 $h_C$ 和攻击力 $d_C$，怪物初始有血量 $h_M$ 和攻击力 $d_M$。战斗由多个步骤组成：

1. 角色攻击怪物，怪物的血量减少 $d_C$；
2. 怪物攻击角色，角色的血量减少 $d_M$；
3. 角色攻击怪物，怪物的血量减少 $d_C$；
4. 怪物攻击角色，角色的血量减少 $d_M$；
5. 如此循环，直到战斗结束。

战斗结束的条件是某一方的血量变为非正数（即 $0$ 或更少）。如果怪物的血量变为非正数，角色获胜；否则，怪物获胜。

Monocarp 的角色当前有血量 $h_C$ 和攻击力 $d_C$。他想要击败一个血量为 $h_M$、攻击力为 $d_M$ 的怪物。在战斗开始前，Monocarp 可以花费最多 $k$ 枚硬币来升级他的武器或护甲；每次升级花费恰好一枚硬币，每次武器升级使角色的攻击力增加 $w$，每次护甲升级使角色的血量增加 $a$。

Monocarp 能否通过最优地花费硬币来击败怪物？

### 算法分类
枚举

### 题解分析与结论

1. **核心思路**：所有题解的核心思路都是枚举硬币的分配方式，即枚举用于升级攻击力和血量的硬币数量，然后计算升级后的角色和怪物的战斗结果，判断角色是否能击败怪物。

2. **难点对比**：
   - **数据范围**：部分题解提到了数据范围较大，容易导致 `long long` 溢出，因此需要使用 `__int128` 或其他高精度处理方式。
   - **优化**：部分题解通过优化计算方式（如使用整数除法上取整公式）来避免浮点数误差。

3. **最优思路**：枚举硬币分配方式，计算升级后的角色和怪物的战斗结果，使用整数除法上取整公式避免浮点数误差，同时注意数据范围，防止溢出。

### 评分较高的题解

#### 题解作者：include_BM (赞：9)
- **星级**：5星
- **关键亮点**：代码简洁，使用整数除法上取整公式，避免了浮点数误差，且逻辑清晰。
- **核心代码**：
  ```cpp
  for(int i=0;i<=k;++i)
      if((hc+i*a+dm-1)/dm>=(hm+dc+(k-i)*w-1)/(dc+(k-i)*w)){
          puts("YES");f=1;break;}
  ```

#### 题解作者：FFTotoro (赞：5)
- **星级**：4星
- **关键亮点**：代码结构清晰，使用 `ceil` 函数计算上取整，虽然存在浮点数误差的风险，但在本题中通过了测试。
- **核心代码**：
  ```cpp
  if(!(a1%d))x=a1/d;
  else x=ceil((double)a1/d);
  if(!(c%b1))y=c/b1;
  else y=ceil((double)c/b1);
  ```

#### 题解作者：__vector__ (赞：0)
- **星级**：4星
- **关键亮点**：使用 `__int128` 处理大数，避免了溢出问题，代码逻辑清晰。
- **核心代码**：
  ```cpp
  if((__int128)hc+(__int128)i*(__int128)a>(__int128)sd*(__int128)dm)
  ```

### 关键思路与技巧
1. **枚举法**：通过枚举硬币的分配方式，计算每种情况下的战斗结果，判断角色是否能击败怪物。
2. **整数除法上取整**：使用 `(x + y - 1) / y` 代替 `ceil(x / y)`，避免浮点数误差。
3. **数据范围处理**：对于大数计算，使用 `__int128` 或其他高精度处理方式，防止溢出。

### 可拓展之处
类似的问题可以通过枚举法解决，尤其是当问题的解空间较小且可以通过枚举所有可能情况来判断时。例如，资源分配问题、背包问题等。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)

---
处理用时：31.04秒