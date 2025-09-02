# 题目信息

# Ciel and Duel

## 题目描述

Fox Ciel is playing a card game with her friend Jiro.

Jiro has $ n $ cards, each one has two attributes: $ position $ (Attack or Defense) and $ strength $ . Fox Ciel has $ m $ cards, each one has these two attributes too. It's known that position of all Ciel's cards is Attack.

Now is Ciel's battle phase, Ciel can do the following operation many times:

1. Choose one of her cards $ X $ . This card mustn't be chosen before.
2. If Jiro has no alive cards at that moment, he gets the damage equal to ( $ X $ 's strength). Otherwise, Ciel needs to choose one Jiro's alive card $ Y $ , then: 
  - If $ Y $ 's position is Attack, then ( $ X $ 's strength) $ >= $ ( $ Y $ 's strength) must hold. After this attack, card $ Y $ dies, and Jiro gets the damage equal to ( $ X $ 's strength) - ( $ Y $ 's strength).
  - If $ Y $ 's position is Defense, then ( $ X $ 's strength) $ &gt; $ ( $ Y $ 's strength) must hold. After this attack, card $ Y $ dies, but Jiro gets no damage.

Ciel can end her battle phase at any moment (so, she can use not all her cards). Help the Fox to calculate the maximal sum of damage Jiro can get.

## 说明/提示

In the first test case, Ciel has 3 cards with same $ strength $ . The best strategy is as follows. First she uses one of these 3 cards to attack "ATK 2000" card first, this attack destroys that card and Jiro gets $ 2500-2000=500 $ damage. Then she uses the second card to destroy the "DEF 1700" card. Jiro doesn't get damage that time. Now Jiro has no cards so she can use the third card to attack and Jiro gets $ 2500 $ damage. So the answer is $ 500+2500=3000 $ .

In the second test case, she should use the "1001" card to attack the "ATK 100" card, then use the "101" card to attack the "ATK 10" card. Now Ciel still has cards but she can choose to end her battle phase. The total damage equals $ (1001-100)+(101-10)=992 $ .

In the third test case note that she can destroy the "ATK 0" card by a card with strength equal to 0, but she can't destroy a "DEF 0" card with that card.

## 样例 #1

### 输入

```
2 3
ATK 2000
DEF 1700
2500
2500
2500
```

### 输出

```
3000
```

## 样例 #2

### 输入

```
3 4
ATK 10
ATK 100
ATK 1000
1
11
101
1001
```

### 输出

```
992
```

## 样例 #3

### 输入

```
2 4
DEF 0
ATK 0
0
0
1
1
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# Ciel和决斗
## 题目描述
狐狸Ciel正在和她的朋友Jiro玩一个卡牌游戏。

Jiro有$n$张卡牌，每张卡牌有两个属性：位置（攻击或防御）和力量值 。狐狸Ciel有$m$张卡牌，每张卡牌也有这两个属性。已知Ciel的所有卡牌位置都是攻击。

现在是Ciel的战斗阶段，Ciel可以多次进行以下操作：
1. 选择她的一张卡牌$X$ 。这张卡牌之前不能被选择过。
2. 如果此时Jiro没有存活的卡牌，那么他受到的伤害等于（$X$的力量值）。否则，Ciel需要选择Jiro的一张存活卡牌$Y$ ，然后：
    - 如果$Y$的位置是攻击，那么必须满足（$X$的力量值）$ \geq $（$Y$的力量值） 。这次攻击后，卡牌$Y$死亡，Jiro受到的伤害等于（$X$的力量值） - （$Y$的力量值）。
    - 如果$Y$的位置是防御，那么必须满足（$X$的力量值）$ > $（$Y$的力量值） 。这次攻击后，卡牌$Y$死亡，但Jiro不会受到伤害。

Ciel可以在任何时候结束她的战斗阶段（所以，她可以不使用所有的卡牌）。帮助狐狸计算Jiro可能受到的最大伤害总和。
## 说明/提示
在第一个测试用例中，Ciel有3张力量值相同的卡牌。最佳策略如下。首先，她用这3张卡牌中的一张先攻击“攻击力2000”的卡牌，这次攻击摧毁了那张卡牌，Jiro受到$2500 - 2000 = 500$的伤害。然后她用第二张卡牌摧毁“防御力1700”的卡牌。这次Jiro没有受到伤害。现在Jiro没有卡牌了，所以她可以用第三张卡牌进行攻击，Jiro受到$2500$的伤害。所以答案是$500 + 2500 = 3000$。

在第二个测试用例中，她应该用“1001”的卡牌攻击“攻击力100”的卡牌，然后用“101”的卡牌攻击“攻击力10”的卡牌。现在Ciel仍然有卡牌，但她可以选择结束她的战斗阶段。总伤害等于$(1001 - 100)+(101 - 10)=992$。

在第三个测试用例中，注意她可以用力量值为0的卡牌摧毁“攻击力0”的卡牌，但她不能用那张卡牌摧毁“防御力0”的卡牌。
## 样例 #1
### 输入
```
2 3
ATK 2000
DEF 1700
2500
2500
2500
```
### 输出
```
3000
```
## 样例 #2
### 输入
```
3 4
ATK 10
ATK 100
ATK 1000
1
11
101
1001
```
### 输出
```
992
```
## 样例 #3
### 输入
```
2 4
DEF 0
ATK 0
0
0
1
1
```
### 输出
```
1
```
### 算法分类
贪心
### 题解综合分析与结论
这几道题解主要围绕两种贪心策略展开。第一种策略是不打对方的防御牌，用自己较大力量值的牌去攻击对方较小力量值的攻击牌，以获取当前攻击的最大伤害；第二种策略是先用较小力量值的牌消耗完对方的防御牌，再用合适的牌打完对方的攻击牌，最后用剩余牌对对方造成直接伤害。由于单独使用一种策略可能无法得到最优解，所以综合两种策略取最大值。各题解在实现细节上有所不同，比如排序方式、数组使用、循环条件等，但核心思路一致。
### 所选的题解
- **作者：Rbu_nas（5星）**
    - **关键亮点**：思路清晰，对两种贪心策略分别进行详细阐述，并通过代码实现两种策略，且使用数组备份避免策略间相互影响。对边界情况处理得当，如力量值非负，初值设为`-1`。
    - **个人心得**：提到两种贪心策略单独使用易被`hack`，强调要综合考虑两种策略。
    - **核心代码**：
```cpp
//rush便是打完所有牌的策略
inline LL rush(int *xAtk, int *yAtk, int *yDef)
{
    LL ret = 0;
    sort(xAtk + 1, xAtk + m + 1);
    sort(yDef + 1, yDef + totDef + 1);
    sort(yAtk + 1, yAtk + totAtk + 1);
    for(register int i = 1; i <= totDef; ++i)
    {
        int P = upper_bound(xAtk + 1, xAtk + m + 1, yDef[i]) - xAtk;
        if(xAtk[P] < yDef[i]) return 0;
        xAtk[P] = -1; yDef[i] = -1;
    }
    sort(xAtk + 1, xAtk + m + 1);
    for(register int i = 1; i <= totAtk; ++i)
    {
        int P = lower_bound(xAtk + 1, xAtk + m + 1, yAtk[i]) - xAtk;
        if(xAtk[P] < yAtk[i] || xAtk[P] == -1 || yAtk[i] == -1) return ret;
        ret += xAtk[P] - yAtk[i];
        xAtk[P] = -1; yAtk[i] = -1;
    }
    for(register int i = 1; i <= m; ++i) if(xAtk[i]!= -1) ret += xAtk[i];
    return ret;
}
//策略二，把大牌直接炸出去
inline LL blow(int *xAtk, int *yAtk, int *yDef)
{
    LL ret = 0;
    sort(xAtk + 1, xAtk + m + 1);
    sort(yAtk + 1, yAtk + totAtk + 1);
    for(register int i = m, j = 1; i >= 1; --i, ++j)
        if(xAtk[i] >= yAtk[j])
        {
            if(yAtk[j]!= -1)
            {
                ret += xAtk[i] - yAtk[j];
                xAtk[i] = -1; yAtk[j] = -1;
            }
        }
    return ret;
}
```
核心思想：`rush`函数先排序，用`upper_bound`找能打防御牌的最小牌，打完防御牌后重新排序，再用`lower_bound`找能打攻击牌的最小牌，最后计算剩余牌伤害。`blow`函数排序后，用大力量值牌打小力量值攻击牌。
- **作者：XXh0919（4星）**
    - **关键亮点**：代码简洁明了，通过两个函数`f1`和`f2`分别实现两种贪心策略，逻辑清晰。使用`bool`数组记录牌的使用情况，便于后续计算。
    - **核心代码**：
```cpp
int f1(){
    int ans = 0;
    int tot1 = m, tot2 = 1;
    while(ciel[tot1] >= atk[tot2] && tot1 > 0 && tot2 <= a){
        ans += ciel[tot1] - atk[tot2];
        --tot1; ++tot2;
    }
    return ans;
}
int f2(){
    int ans = 0, tot1 = 1;
    bool ff = 1;
    rep(tot2, 1, d){
        while((ciel[tot1] <= def[tot2] || f[tot1]) && tot1 <= m)++tot1;
        if(tot1 == m + 1){
            memset(f, 0, sizeof f);
            ff = 0;
            break;
        }
        f[tot1] = 1;
    }
    tot1 = 1;
    rep(tot2, 1, a){
        while((ciel[tot1] < atk[tot2] || f[tot1]) && tot1 <= m)++tot1;
        if(tot1 == m + 1){
            return ans;
        }
        ans += ciel[tot1] - atk[tot2];
        f[tot1] = 1;
    }
    if(ff){
        rep(i, 1, m){
            if(!f[i]){
                ans += ciel[i];
            }
        }
    }
    return ans;
}
```
核心思想：`f1`函数从大到小用`ciel`牌打`atk`牌计算伤害。`f2`函数先用小`ciel`牌打`def`牌，再打`atk`牌，若能打完对方牌，计算剩余`ciel`牌伤害。
- **作者：_Qer（4星）**
    - **关键亮点**：代码结构清晰，通过`bool`数组记录手牌使用情况，在两种贪心策略的实现函数中，逻辑判断明确，边界条件处理较好。
    - **核心代码**：
```cpp
LL solve1() {
    LL sum = 0;
    int p1 = m, p2 = 1;
    while (a[p1] >= atk[p2] && p1 > 0 && p2 <= ca) {
        sum += a[p1] - atk[p2];
        --p1, ++p2;
    }
    return sum;
}
LL solve2() {
    LL sum = 0;
    int p1 = 1;
    bool b = true;
    for (int p2 = 1; p2 <= cd; ++p2) {
        while ((a[p1] <= def[p2] || used[p1]) && p1 <= m) {
            ++p1;
        }
        if (p1 == m + 1) {
            b = false;
            memset(used, false, sizeof(used));
            break;
        }
        used[p1] = true;
    }
    p1 = 1;
    for (int p2 = 1; p2 <= ca; ++p2) {
        while ((a[p1] < atk[p2] || used[p1]) && p1 <= m) {
            ++p1;
        }
        if (p1 == m + 1) {
            return sum;
        }
        sum += a[p1] - atk[p2];
        used[p1] = true;
    }
    if (b)
    for (int i = 1; i <= m; ++i) {
        if (!used[i]) {
            sum += a[i];
        }
    }
    return sum;
}
```
核心思想：`solve1`函数从大到小用`a`牌打`atk`牌计算伤害。`solve2`函数先用小`a`牌打`def`牌，再打`atk`牌，若能打完对方牌，计算剩余`a`牌伤害。
### 最优关键思路或技巧
采用两种贪心策略综合的方法，先分别考虑用大牌打小攻击牌和用小牌消耗防御牌再贴脸攻击这两种情况，通过排序和合理的循环判断来实现，利用数组记录牌的使用情况辅助计算。
### 可拓展之处
同类型题可考虑其他带有不同条件限制的卡牌对战游戏，类似算法套路是在面对多种可能的贪心策略且单一策略无法保证最优解时，综合多种策略取最优。
### 洛谷推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：涉及贪心策略，通过对数据的排序和分析来确定最优方案。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：同样是博弈类问题，需要运用贪心思想来制定策略。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对数据进行排序，利用贪心算法解决问题。 

---
处理用时：113.34秒