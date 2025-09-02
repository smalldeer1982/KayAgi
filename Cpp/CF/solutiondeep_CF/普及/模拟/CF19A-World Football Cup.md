# 题目信息

# World Football Cup

## 题目描述

## 题意
众所周知，2010 年 FIFA 世界杯在南非举行。BFA 决定下一届世界杯将在伯兰德举行。BFA 决定改变世界杯的一些规定：  

- 最后的比赛涉及 $n$ 支球队（$n$ 总是偶数）；
- 前 $\frac{n}{2}$ 队（根据排名）进入淘汰赛阶段。

积分榜是按照以下原则制作的：胜利一个队得 $3$ 分，平分 $1$ 分，失败 $0$ 分。首先，球队按积分顺序排在积分榜上，分数相等比较净胜球，净胜球相等比较进球数。

你被要求写一个程序，通过给定的比赛名单和所有比赛的结果，找到设法进入淘汰赛阶段的球队名单。

## 样例 #1

### 输入

```
4
A
B
C
D
A-B 1:1
A-C 2:2
A-D 1:0
B-C 1:0
B-D 0:3
C-D 0:3
```

### 输出

```
A
D
```

## 样例 #2

### 输入

```
2
a
A
a-A 2:1
```

### 输出

```
a
```

# AI分析结果

### 题目翻译
本题已为中文，无需翻译。

### 综合分析与结论
这些题解的核心思路都是模拟比赛过程，统计各球队的积分、净胜球和进球数，然后按照规则排序选出前 $\frac{n}{2}$ 名球队，最后按字典序输出。

#### 算法要点
- **数据结构**：大多使用结构体或类存储球队信息，部分使用 `map` 或 `unordered_map` 建立球队名和下标的映射。
- **排序规则**：以积分、净胜球、进球数为关键字排序，最后对出线球队按字典序排序。
- **模拟过程**：读取比赛结果，根据胜负平情况更新球队信息。

#### 难点对比
- **输入处理**：部分题解逐字符读取输入，代码复杂；部分使用 `substr` 或自定义函数解析输入，更简洁。
- **排序实现**：有的重载 `<` 运算符，有的自定义 `cmp` 函数。
- **映射关系**：使用 `map` 或 `unordered_map` 可简化查找球队信息的过程，但 `unordered_map` 时间复杂度更优。

### 评分较高的题解
1. **作者：codeLJH114514（5星）**
    - **关键亮点**：使用 `unordered_map` 建立映射，时间复杂度期望为 $O(1)$；重载 `<` 运算符，代码简洁易读。
    - **核心代码**：
```cpp
class Team{
    public:
        int score, win, get; // score为得分，win为净胜球，get为进球数
        string name;
        Team(int s, int w, int g): score(s), win(w), get(g){};
        Team(): score(0), win(0), get(0){};
        bool operator<(const Team& a) const&;
} t[maxn];
bool Team::operator<(const Team& a) const& {
    if (score!= a.score)
        return score > a.score;
    else if (win!= a.win)
        return win > a.win;
    else
        return get > a.get;
}
```
2. **作者：灵光一闪（4星）**
    - **关键亮点**：思路清晰，代码注释详细，适合初学者。
    - **核心代码**：
```cpp
struct TEAM{
    string name;
    int pts;
    int jsq;
    int jqs;
};
TEAM t[233];
map <string,int> mp;
for(int i=0;i<n*(n-1)/2;i++){
    string s1,s2;
    cin>>s1;
    s2=s1.substr(s1.find('-')+1);
    s1=s1.substr(0,s1.find('-'));
    int a,b;
    scanf("%d:%d",&a,&b);
    int team1=mp[s1],team2=mp[s2];
    if(a>b){
        t[team1].pts+=3;
    }
    else if(a<b){
        t[team2].pts+=3;
    }
    else{
        t[team1].pts++;
        t[team2].pts++;
    }
    t[team1].jsq+=(a-b);
    t[team2].jsq+=(b-a);
    t[team1].jqs+=a;
    t[team2].jqs+=b;
}
```
3. **作者：PC_DOS（4星）**
    - **关键亮点**：详细说明了注意事项，使用 `vector` 和 `map` 结合处理排序问题。
    - **核心代码**：
```cpp
struct TeamData{
    string sName;
    long long iScore = 0;
    long long iNetGoal = 0;
    long long iGoal=0;
};
bool cmp(TeamData tdTeam1, TeamData tdTeam2){
    if (tdTeam1.iScore!= tdTeam2.iScore)
        return tdTeam1.iScore > tdTeam2.iScore;
    else if (tdTeam1.iNetGoal!= tdTeam2.iNetGoal)
        return tdTeam1.iNetGoal > tdTeam2.iNetGoal;
    else
        return tdTeam1.iGoal > tdTeam2.iGoal;
}
```

### 最优关键思路或技巧
- 使用 `unordered_map` 建立球队名和下标的映射，可将查找时间复杂度优化到 $O(1)$。
- 重载 `<` 运算符或自定义 `cmp` 函数，方便排序。

### 拓展思路
同类型题可拓展到其他比赛排名问题，如篮球、排球等，只需修改比赛规则和得分方式。类似算法套路为模拟比赛过程，统计数据，按规则排序。

### 洛谷推荐题目
1. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)：根据学生的多科成绩进行排序。
2. [P1781 宇宙总统](https://www.luogu.com.cn/problem/P1781)：根据候选人的票数进行排序。
3. [P2676 [USACO07DEC]Bookshelf B](https://www.luogu.com.cn/problem/P2676)：根据奶牛的身高进行排序。

### 个人心得摘录与总结
- **灵光一闪**：调了一个多小时，提醒注意细节，耐心调试。
- **Ousmane_Dembele**：卡了一个下午，遇到输入问题、判断错误等，强调细心和检查代码。
- **Adam_Ng**：交了若干次没 AC，没注意题目细节，要认真读题。
- **晨·曦**：被净胜球可以为负数卡了好久，做题要考虑全面。 

---
处理用时：31.83秒