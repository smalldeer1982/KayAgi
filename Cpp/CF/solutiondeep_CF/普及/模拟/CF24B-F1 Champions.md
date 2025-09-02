# 题目信息

# F1 Champions

## 题目描述

Formula One championship consists of series of races called Grand Prix. After every race drivers receive points according to their final position. Only the top 10 drivers receive points in the following order 25, 18, 15, 12, 10, 8, 6, 4, 2, 1. At the conclusion of the championship the driver with most points is the champion. If there is a tie, champion is the one with most wins (i.e. first places). If a tie still exists, it is chosen the one with most second places, and so on, until there are no more place to use for compare.

 Last year another scoring system was proposed but rejected. In it the champion is the one with most wins. If there is tie, champion is the one with most points. If a tie still exists it is proceeded the same way as in the original scoring system, that is comparing number of second, third, forth, and so on, places.

You are given the result of all races during the season and you are to determine the champion according to both scoring systems. It is guaranteed, that both systems will produce unique champion.

## 说明/提示

It is not guaranteed that the same drivers participate in all races. For the championship consider every driver that has participated in at least one race. The total number of drivers during the whole season is not more then $ 50 $ .

## 样例 #1

### 输入

```
3
3
Hamilton
Vettel
Webber
2
Webber
Vettel
2
Hamilton
Vettel
```

### 输出

```
Vettel
Hamilton
```

## 样例 #2

### 输入

```
2
7
Prost
Surtees
Nakajima
Schumacher
Button
DeLaRosa
Buemi
8
Alonso
Prost
NinoFarina
JimClark
DeLaRosa
Nakajima
Patrese
Surtees
```

### 输出

```
Prost
Prost
```

# AI分析结果

### 题目翻译
# F1 冠军

## 题目描述
一级方程式锦标赛由一系列被称为大奖赛的比赛组成。每场比赛结束后，车手会根据他们的最终名次获得积分。只有排名前十的车手能获得积分，积分顺序如下：25、18、15、12、10、8、6、4、2、1。赛季结束时，积分最多的车手成为冠军。若出现积分相同的情况，则冠军为获胜次数（即获得第一名的次数）最多的车手。若仍然平局，则比较获得第二名的次数，依此类推，直到能分出胜负为止。

去年曾提出另一种计分系统，但被否决了。在该系统中，冠军是获胜次数最多的车手。若出现平局，则冠军是积分最多的车手。若仍然平局，则按照原计分系统的方式继续比较，即比较获得第二名、第三名、第四名等的次数。

给定一个赛季中所有比赛的结果，你需要根据这两种计分系统确定冠军。可以保证两种系统都会产生唯一的冠军。

## 说明/提示
不保证相同的车手会参加所有比赛。在计算锦标赛成绩时，应考虑至少参加过一场比赛的所有车手。整个赛季的车手总数不超过 50 人。

## 样例 #1
### 输入
```
3
3
Hamilton
Vettel
Webber
2
Webber
Vettel
2
Hamilton
Vettel
```
### 输出
```
Vettel
Hamilton
```

## 样例 #2
### 输入
```
2
7
Prost
Surtees
Nakajima
Schumacher
Button
DeLaRosa
Buemi
8
Alonso
Prost
NinoFarina
JimClark
DeLaRosa
Nakajima
Patrese
Surtees
```
### 输出
```
Prost
Prost
```

### 综合分析与结论
这些题解的核心思路都是通过结构体存储车手信息（名字、得分、各排名次数），再根据两种计分规则编写比较函数进行排序，最后输出冠军。

#### 思路对比
- 多数题解直接用结构体数组存储车手信息，部分使用 `map` 或哈希表映射车手名字到数组下标，方便查找和更新信息。
- 排序时，都依据两种计分规则编写 `cmp` 函数，但比较顺序和实现细节略有不同。

#### 算法要点
- 结构体定义：存储车手名字、得分和各排名次数。
- 信息记录：遍历每场比赛，更新车手得分和排名次数。
- 排序：根据两种计分规则编写 `cmp` 函数进行排序。

#### 解决难点
- 车手信息存储：因车手数量和名字未知，需用合适数据结构（如 `map`、哈希表）映射名字到数组下标。
- 排名比较：当得分或第一名次数相同时，需依次比较后续排名次数。

### 高评分题解
1. **作者：_Give_up_（5星）**
    - **关键亮点**：思路清晰，详细解释每个步骤，代码规范，使用 `set` 去重，`map` 映射车手名字到编号，方便处理未知数量的车手。
    - **重点代码**：
```cpp
struct rec
{
    string name;
    int sum;
    map <int,int> mp;
};

bool cmp(rec a, rec b)
{
    if (a.sum == b.sum)
    {
        for (int i = 1; i <= 55; i++)
            if (a.mp[i]!= b.mp[i]) return a.mp[i] > b.mp[i];
    }
    else return a.sum > b.sum;
}

bool cmp2(rec a, rec b)
{
    if (a.mp[1] == b.mp[1])
    {
        if (a.sum == b.sum)
        {
            for (int i = 2; i <= 55; i++)
                if (a.mp[i]!= b.mp[i]) return a.mp[i] > b.mp[i];
        }
        return a.sum > b.sum;
    }
    return a.mp[1] > b.mp[1];
}
```
核心思想：用结构体 `rec` 存储车手信息，`mp` 记录各排名次数。`cmp` 函数按原计分规则排序，`cmp2` 函数按新计分规则排序。

2. **作者：wmrqwq（4星）**
    - **关键亮点**：代码简洁，直接用结构体数组存储车手信息，通过遍历判断车手是否已记录，易于理解。
    - **重点代码**：
```cpp
struct node 
{
    string id;
    int sum, cs[110];
};

bool cmp1(node x, node y) 
{
    if (x.sum == y.sum)
        for (int i = 1; i <= 50; i++)
            if (x.cs[i]!= y.cs[i])
                return x.cs[i] > y.cs[i];
    else 
        return x.sum > y.sum;
}

bool cmp2(node x, node y) 
{
    if (x.cs[1] == y.cs[1])
    {
        if (x.sum == y.sum)
        {
            for (int i = 2; i <= 50; i++)
                if (x.cs[i]!= y.cs[i])
                    return x.cs[i] > y.cs[i];
        }
        else 
            return x.sum > y.sum;
    }
    else 
        return x.cs[1] > y.cs[1];
}
```
核心思想：用结构体 `node` 存储车手信息，`cs` 数组记录各排名次数。`cmp1` 和 `cmp2` 分别实现两种计分规则的排序。

3. **作者：Minecraft万岁（4星）**
    - **关键亮点**：指出题目坑点，使用 `set` 记录人名，`map` 映射名字到数组下标，代码逻辑清晰。
    - **重点代码**：
```cpp
struct node
{
    string name;
    int t[55];
    int tot;
};

inline bool cmp1(node p, node q)
{
    if (p.tot!= q.tot) return p.tot > q.tot;
    for (int i = 1; i <= 50; i++)
        if (p.t[i]!= q.t[i]) return p.t[i] > q.t[i];
}

inline bool cmp2(node p, node q)
{
    if (p.t[1]!= q.t[1]) return p.t[1] > q.t[1];
    if (p.tot!= q.tot) return p.tot > q.tot;
    for (int i = 2; i <= 50; i++)
        if (p.t[i]!= q.t[i]) return p.t[i] > q.t[i];
}
```
核心思想：用结构体 `node` 存储车手信息，`t` 数组记录各排名次数。`cmp1` 和 `cmp2` 分别实现两种计分规则的排序。

### 最优关键思路或技巧
- 使用 `map` 或哈希表映射车手名字到数组下标，可快速查找和更新车手信息。
- 编写 `cmp` 函数实现自定义排序，清晰表达两种计分规则。

### 拓展思路
同类型题目可能涉及不同计分规则或更多信息比较，可使用类似结构体存储信息和自定义排序函数解决。

### 推荐题目
1. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)：根据多科成绩和总分排序。
2. [P1781 宇宙总统](https://www.luogu.com.cn/problem/P1781)：根据票数和编号排序。
3. [P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)：涉及并查集和排序。

### 个人心得摘录与总结
- **封禁用户**：WA 了 3 次，指出排名大于 10 时分数不加但排名要算，且两种计分方法不能看错。
总结：做题时要注意题目细节，避免因粗心导致错误。
- **Minecraft万岁**：指出题目坑点，如排名统计数组至少开到 51，输入的人名可能互不重复。
总结：读题时要仔细分析数据范围和特殊情况，避免遗漏关键信息。 

---
处理用时：43.95秒