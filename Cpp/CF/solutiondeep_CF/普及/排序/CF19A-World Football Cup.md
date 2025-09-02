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

### 综合分析与结论
这些题解的核心思路都是模拟世界杯比赛的积分计算和排名过程。主要步骤包括输入球队信息、比赛结果，根据规则计算各球队的积分、净胜球和进球数，然后按照指定规则排序，最后输出前 $\frac{n}{2}$ 名的球队。

- **思路对比**：大部分题解都采用结构体或类来存储球队信息，使用排序算法进行排名。部分题解使用 `map` 或 `unordered_map` 来建立球队名和下标或信息的映射，方便查找和更新球队信息。
- **算法要点**：关键在于正确实现积分、净胜球和进球数的计算，以及按照指定规则进行排序。排序规则为：先按积分降序，积分相同按净胜球降序，净胜球相同按进球数降序，最后对出线球队按字典序排序。
- **解决难点**：
    - **输入处理**：需要正确解析比赛信息，包括球队名和比分。部分题解采用字符逐个读取，部分使用 `substr` 函数截取。
    - **排序规则实现**：通过重载比较运算符或自定义比较函数来实现多关键字排序。
    - **净胜球处理**：注意净胜球可以为负数。

### 所选题解
- **作者：codeLJH114514 (赞：2)  4星**
    - **关键亮点**：使用类和 `unordered_map` 实现，思路清晰，代码结构良好。`unordered_map` 的使用提高了查找效率，时间复杂度期望为 $O(1)$。
    - **个人心得**：无

### 重点代码
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
    if (score != a.score)
        return score > a.score;
    else if (win != a.win)
        return win > a.win;
    else
        return get > a.get;
}
int n;
unordered_map<string, int> teams;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t[i].name;
    for (int i = 1; i <= n; i++)    
        teams[t[i].name] = i;
    int m = n * (n - 1) / 2;
    for (int i = 1; i <= m; i++) {
        int in1, in2;
        string name1, name2;
        string s;
        char ch;
        cin >> s >> in1 >> ch >> in2;
        name1 = s.substr(0, s.find('-'));
        name2 = s.substr(s.find('-') + 1);
        if (in1 == in2) {
            t[teams[name1]].score += 1;
            t[teams[name2]].score += 1;
        } else if (in1 < in2)
            t[teams[name2]].score += 3;
        else
            t[teams[name1]].score += 3;
        t[teams[name1]].win += in1 - in2;
        t[teams[name2]].win += in2 - in1;
        t[teams[name1]].get += in1;
        t[teams[name2]].get += in2;
    }
    sort(t + 1, t + n + 1);
    vector<string> v;
    for (int i = 1; i <= n / 2; i++)
        v.push_back(t[i].name);
    sort(v.begin(), v.end());
    for (auto i : v)
        cout << i << "\n";
    return 0;
}
```
**核心实现思想**：
1. 定义 `Team` 类存储球队信息，并重载 `<` 运算符实现排序规则。
2. 使用 `unordered_map` 建立球队名和下标的映射，方便查找球队信息。
3. 输入比赛信息，根据比分更新球队的积分、净胜球和进球数。
4. 对所有球队按规则排序，取出前 $\frac{n}{2}$ 名球队的名字，再按字典序排序后输出。

### 可拓展之处
同类型题目可能会有不同的比赛规则和排名规则，如增加更多的排名关键字，或改变比赛得分规则等。解题思路仍然是模拟比赛过程，正确计算各项指标，然后按照规则排序。类似的算法套路包括使用结构体或类存储信息，使用 `map` 或 `unordered_map` 进行映射，以及自定义比较函数或重载运算符实现排序。

### 推荐题目
1. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)：涉及多关键字排序，与本题的排序思路类似。
2. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)：需要根据成绩进行排序和筛选，与本题的筛选前 $\frac{n}{2}$ 名球队类似。
3. [P1541 乌龟棋](https://www.luogu.com.cn/problem/P1541)：虽然是动态规划题，但也涉及到对状态的排序和选择，锻炼排序和模拟的思维。

### 个人心得摘录与总结
- **灵光一闪**：认为这题是很坑的大模拟，自己调了一个多小时。强调了结构体的使用，并分享了曾经卡掉自己的数据。总结：大模拟题需要仔细调试，注意数据的边界情况。
- **Ousmane_Dembele**：一开始做法很累，后来改进。遇到了输入、判断和特判等问题，卡了一个下午。总结：在实现算法时可以尝试不同的方法，注意输入处理和边界条件的判断。
- **Adam_Ng**：交了若干次没 AC，原因是题目复杂没注意到一些事项。总结：做复杂题目时要仔细阅读题目要求，避免遗漏重要信息。
- **晨·曦**：被净胜球可以为负数这个点卡了好久。总结：要注意题目中的特殊条件，避免因疏忽导致错误。

---
处理用时：42.31秒