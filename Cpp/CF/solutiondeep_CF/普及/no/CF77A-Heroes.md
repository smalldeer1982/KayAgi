# 题目信息

# Heroes

## 题目描述

The year of 2012 is coming...

According to an ancient choradrican legend in this very year, in 2012, Diablo and his brothers Mephisto and Baal will escape from hell, and innumerable hordes of demons will enslave the human world. But seven brave heroes have already gathered on the top of a mountain Arreat to protect us mere mortals from the effect of this terrible evil.

The seven great heroes are: amazon Anka, barbarian Chapay, sorceress Cleo, druid Troll, necromancer Dracul, paladin Snowy and a professional hit girl Hexadecimal. Heroes already know how much experience will be given for each of the three megabosses: $ a $ for Mephisto, $ b $ for Diablo and $ c $ for Baal.

Here's the problem: heroes are as much as seven and megabosses are only three! Then our heroes decided to split into three teams, where each team will go to destroy their own megaboss. Each team member will receive a ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77A/4ac5ad94fb5392cd96ac09e5b84eb06e8c8a0edb.png) of experience, rounded down, where $ x $ will be the amount of experience for the killed megaboss and $ y $ — the number of people in the team.

Heroes do not want to hurt each other's feelings, so they want to split into teams so that the difference between the hero who received the maximum number of experience and the hero who received the minimum number of experience were minimal. Since there can be several divisions into teams, then you need to find the one in which the total amount of liking in teams were maximum.

It is known that some heroes like others. But if hero $ p $ likes hero $ q $ , this does not mean that the hero $ q $ likes hero $ p $ . No hero likes himself.

The total amount of liking in teams is the amount of ordered pairs $ (p,q) $ , such that heroes $ p $ and $ q $ are in the same group, and hero $ p $ likes hero $ q $ (but it is not important if hero $ q $ likes hero $ p $ ). In case of heroes $ p $ and $ q $ likes each other and they are in the same group, this pair should be counted twice, as $ (p,q) $ and $ (q,p) $ .

A team can consist even of a single hero, but it is important that every megaboss was destroyed. All heroes must be involved in the campaign against evil. None of the heroes can be in more than one team.

It is guaranteed that every hero is able to destroy any megaboss alone.

## 说明/提示

A note to first example: it the first team should be Dracul, Troll and Anka, in the second one Hexadecimal and Snowy, and in the third Cleo и Chapay.

## 样例 #1

### 输入

```
3
Troll likes Dracul
Dracul likes Anka
Snowy likes Hexadecimal
210 200 180
```

### 输出

```
30 3
```

## 样例 #2

### 输入

```
2
Anka likes Chapay
Chapay likes Anka
10000 50 50
```

### 输出

```
1950 2
```

# AI分析结果



### 中文重写题目
#### 题目名称：Heroes

**题目描述**  
2012年即将到来……  

根据古老的Choradrica传说，在这一年，迪亚波罗和他的兄弟墨菲斯托、巴尔将从地狱逃脱，无数恶魔将奴役人类世界。但七位勇敢的英雄已聚集在亚瑞特山顶，保护我们凡人免受这可怕邪恶的侵袭。  

七位英雄分别是：亚马逊女战士安卡、野蛮人查佩、女巫克莱奥、德鲁伊特罗尔、死灵法师德古拉、圣骑士斯诺薇和职业杀手海克斯。英雄们已知三个超级boss各自提供的经验值：墨菲斯托为$a$，迪亚波罗为$b$，巴尔为$c$。  

问题在于：英雄有七位，而超级boss只有三个！英雄们决定分成三队，每队消灭一个boss。每个队员获得的经验值为$\lfloor \frac{x}{y} \rfloor$，其中$x$为boss经验，$y$为队伍人数。  

英雄们希望分组的经验差（最大经验与最小经验的差值）尽可能小。若存在多种方案经验差相同，则选择团队好感度总和最大的方案。好感度定义为：若英雄$p$喜欢$q$且两人同队，则计为一次有效配对。注意好感度是单向的，若$p$喜欢$q$且$q$喜欢$p$且同队，则计为两次。  

每个队伍至少有一人，所有英雄必须参与。保证每个英雄都能单独击败任意boss。  

**输入输出样例**  
见原题描述。

---

### 算法分类  
**搜索（深度优先搜索 DFS）**

---

### 题解综合分析  
**核心逻辑**：枚举所有可能的分组方式，计算每组的经验差与好感度，选择最优解。  
**难点对比**：  
1. **分组枚举**：需确保所有七人被分为三组，每组至少一人，暴力搜索需处理大量情况。  
2. **好感度计算**：需高效统计同组成员间的单向喜欢关系，避免重复计算。  

**最优策略**：DFS递归枚举每个英雄加入三个组的所有可能，逐步计算好感度，记录最小经验差及对应的最大好感度。  

---

### 精选题解  
#### 题解作者：小杨小小杨（★★★★☆）  
**关键亮点**：  
1. **递归分治**：通过DFS递归将每个英雄依次分配到三个组，自然生成所有可能分组。  
2. **实时好感度计算**：在递归过程中动态累加新增好感度，避免全局重复计算。  
3. **剪枝优化**：当某组人数为零时提前终止无效分支。  

**核心代码片段**：  
```cpp  
void sc(int t, int aa, int bb, int cc, int s) {
    if (t == 8) { // 所有英雄分配完毕
        if (aa == 0 || bb == 0 || cc == 0) return;
        int h1 = a/aa, h2 = b/bb, h3 = c/cc;
        int diff = max(abs(h1-h2), max(abs(h2-h3), abs(h1-h3)));
        if (diff < mi) { // 更新最小经验差
            mi = diff;
            ma = s;
        } else if (diff == mi) { // 相同差时更新最大好感度
            ma = max(ma, s);
        }
        return;
    }
    // 尝试将当前英雄t加入三个组中的一个，并计算新增好感度
    for (三种分组情况) {
        int new_s = s + 新增的好感度;
        递归调用sc(...);
    }
}
```  

---

### 关键思路总结  
1. **状态表示**：用三个数组（b1, b2, b3）分别存储三个组的成员编号。  
2. **好感度递推**：每次将新成员加入组时，遍历已有成员，累加其与当前成员的单向关系。  
3. **经验差计算**：在递归终点统一计算三个组的经验值，避免中间状态冗余计算。  

---

### 拓展思路  
- **剪枝优化**：若当前递归路径的临时经验差已超过已记录的最小值，可提前终止搜索。  
- **预处理好感度矩阵**：可预先构建好感度的邻接矩阵，加速查询。  

---

### 相似题目推荐  
1. [P1039 划分团队](https://www.luogu.com.cn/problem/P1039)  
2. [P1154 奶牛分厩](https://www.luogu.com.cn/problem/P1154)  
3. [P1103 学生分组](https://www.luogu.com.cn/problem/P1103)

---
处理用时：83.38秒