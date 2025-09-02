# 题目信息

# Football Championship

## 题目描述

这个题目是说，Berland的国家队成功加入一场足球联赛的半决赛。下面是球赛的规则：



**·** 两队比赛，比赛结束后哪支队伍进的球比对方队伍多，哪方获胜。



**·** 胜利得3分，平局两队各得1分，失败不得分（得0分）。



**·** 这四队中得到第一或第二的队伍进入下一轮。



每个队伍的名次是由总得分来算的：分越多，名次越高。如果两个队伍有同样的分，以下列方式来决定高低（越靠前的规则越优先考虑，如果还是不能分出高低，再往下判断。下列第一个权重最高）：



**·** 每个队的进球数减去失球数，得到的结果越高排名就越高。



**·** 总进球数越高，排名就越高。



**·** 如果以上都不行的话，则以字典序排列。



现在还有一场比赛未打。一共6场比赛，已知前五场的队伍与得分。某个队伍和Berland还没交战。教练想让你找到如此X:Y（X是Berland的得分，Y是另一只球队的得分），可以满足下列条件：



**·** X>Y，Berland得赢；



**·** Berland赢后，得进前二名；



**·** 如果不止一种答案，尽可能让X-Y小；



**·** 如果还是有很多答案（不止一个），你应该让Y尽可能小。

## 样例 #1

### 输入

```
AERLAND DERLAND 2:1
DERLAND CERLAND 0:3
CERLAND AERLAND 0:1
AERLAND BERLAND 2:0
DERLAND BERLAND 4:0
```

### 输出

```
6:0
```

## 样例 #2

### 输入

```
AERLAND DERLAND 2:2
DERLAND CERLAND 2:3
CERLAND AERLAND 1:3
AERLAND BERLAND 2:1
DERLAND BERLAND 4:1
```

### 输出

```
IMPOSSIBLE
```

# AI分析结果

### 题目内容
# 足球锦标赛

## 题目描述
这个题目是说，Berland的国家队成功进入一场足球联赛的半决赛。下面是球赛的规则：
- 两队比赛，比赛结束后哪支队伍进的球比对方队伍多，哪方获胜。
- 胜利得3分，平局两队各得1分，失败不得分（得0分）。
- 这四队中得到第一或第二的队伍进入下一轮。

每个队伍的名次是由总得分来算的：分越多，名次越高。如果两个队伍有同样的分，以下列方式来决定高低（越靠前的规则越优先考虑，如果还是不能分出高低，再往下判断。下列第一个权重最高）：
- 每个队的进球数减去失球数，得到的结果越高排名就越高。
- 总进球数越高，排名就越高。
- 如果以上都不行的话，则以字典序排列。

现在还有一场比赛未打。一共6场比赛，已知前五场的队伍与得分。某个队伍和Berland还没交战。教练想让你找到如此X:Y（X是Berland的得分，Y是另一只球队的得分），可以满足下列条件：
- X>Y，Berland得赢；
- Berland赢后，得进前二名；
- 如果不止一种答案，尽可能让X - Y小；
- 如果还是有很多答案（不止一个），你应该让Y尽可能小。

## 样例 #1
### 输入
```
AERLAND DERLAND 2:1
DERLAND CERLAND 0:3
CERLAND AERLAND 0:1
AERLAND BERLAND 2:0
DERLAND BERLAND 4:0
```
### 输出
```
6:0
```

## 样例 #2
### 输入
```
AERLAND DERLAND 2:2
DERLAND CERLAND 2:3
CERLAND AERLAND 1:3
AERLAND BERLAND 2:1
DERLAND BERLAND 4:1
```
### 输出
```
IMPOSSIBLE
```

### 算法分类
模拟

### 综合分析与结论
这几道题解思路基本一致，均是先统计前五场比赛各队的得分、进球数、净胜球等信息，然后通过枚举Berland与未比赛队伍的比分，模拟比赛后的排名情况，判断Berland是否能进入前两名，并根据题目要求找到最优比分。不同之处主要体现在数据结构的使用和代码实现细节上。

### 所选的题解
- **作者：Jerrywang09 (5星)**
    - **关键亮点**：思路清晰，详细解释了结构体、比较函数的设计，代码结构完整，使用`map`嵌套`struct`存储队伍信息，通过拷贝`map`来模拟比赛结果，便于理解和实现。
    - **个人心得**：提到题目类似踢假球，带着这种理解更容易明白题意。
    - **重点代码**：
```cpp
struct node
{
    string name;  // 名称
    int score;    // 得分
    int jsq;      // 净胜球
    int zsq;      // 总进球数
    node()        // 初始化
    {
        score = jsq = zsq = 0;
    }
};

bool cmp(node a, node b)
{
    if (a.score!= b.score)        // 1.得分
        return a.score > b.score;
    if (a.jsq!= b.jsq)            // 2.净胜球
        return a.jsq > b.jsq;
    if (a.zsq!= b.zsq)            // 3.总进球数
        return a.zsq > b.zsq;
    return a.name < b.name;        // 4.队名字典序
}

int main()
{
    map<string, node> m;
    map<string, int> cnt;
    for (int i = 0; i < 5; i++)
    {
        string s1, s2; cin >> s1 >> s2;
        cnt[s1]++; cnt[s2]++;
        m[s1].name = s1;
        m[s2].name = s2;
        int x, y;
        scanf("%d:%d", &x, &y);
        m[s1].zsq += x;
        m[s2].zsq += y;
        m[s1].jsq += x - y;
        m[s2].jsq += y - x;
        if (x > y)
            m[s1].score += 3;
        if (y > x)
            m[s2].score += 3;
        if (x == y)
        {
            m[s1].score++;
            m[s2].score++;
        }
    }
    string another;
    for (auto x : cnt)
        if (x.first!= "BERLAND" && x.second == 2)
        {
            another = x.first;
            break;
        }
    for (int d = 1; d <= 100; d++)
        for (int y = 0; y <= 100; y++)
        {
            int x = y + d;
            auto nm = m;
            nm["BERLAND"].score += 3;
            nm["BERLAND"].jsq += d;
            nm[another].jsq += -d;
            nm["BERLAND"].zsq += x;
            nm[another].zsq += y;
            vector<node> v;
            for (auto t : nm)
                v.push_back(t.second);
            sort(v.begin(), v.end(), cmp);
            if (v[0].name == "BERLAND" || v[1].name == "BERLAND")
            {
                cout << x << ':' << y;
                return 0;
            }
        }
    puts("IMPOSSIBLE");

    return 0;
}
```
核心实现思想：定义`node`结构体存储队伍信息，`cmp`函数实现队伍排名规则。主函数中通过`map`记录前五场比赛信息，找到未与Berland比赛的队伍，枚举比分`x:y`，模拟比赛后更新队伍信息并排序，判断Berland是否进入前两名。

- **作者：TheSky233 (4星)**
    - **关键亮点**：代码注释详细，对每个函数的功能都有清晰说明，逻辑连贯，使用`unordered_map`存储队伍信息，提高查找效率，通过多个函数分别实现不同功能，使代码结构更清晰。
    - **重点代码**：
```cpp
struct Node{
    int win,lose,rating;
    string name;
};

unordered_map<string,Node> Team;
set<string> record,fight;
vector<Node> rate;

void Judge(string name1,string name2,int rate1,int rate2){
    Team[name1].name=name1,Team[name2].name=name2;
    Team[name1].win+=rate1,Team[name2].win+=rate2;
    Team[name2].lose+=rate1,Team[name1].lose+=rate2;
    if(rate1>rate2) Team[name1].rating+=3;
    if(rate1==rate2) Team[name1].rating+=1,Team[name2].rating+=1;
    if(rate1<rate2) Team[name2].rating+=3;
    record.insert(name1); record.insert(name2); 
}

void ReadMatch(){
    for(int i=1;i<=5;i++){
        string fst,sec;
        int pts1,pts2;
        cin>>fst>>sec;
        scanf("%d:%d",&pts1,&pts2);
        Judge(fst,sec,pts1,pts2);
        if(fst=="BERLAND") fight.insert(sec);
        if(sec=="BERLAND") fight.insert(fst); 
    }
    for(auto it=record.begin();it!=record.end();it++) rate.push_back(Team[*it]);
}

void Sort(vector<Node> &v){//进行一轮排序
    sort(v.begin(),v.end(),[](Node A,Node B){
        if(A.rating!=B.rating) return A.rating>B.rating;
        if(A.win-A.lose!=B.win-B.lose) return A.win-A.lose>B.win-B.lose;
        if(A.win!=B.win) return A.win>B.win;
        return A.name<B.name;
    });
}

bool Check(int Ber,int Rival,int Fst,int Sec,vector<Node> v){//判断进行这场比赛后Berland对能否进前二
    v[Ber].win+=Fst,v[Rival].win+=Sec;
    v[Ber].lose+=Sec,v[Rival].lose+=Fst;
    v[Ber].rating+=3;
    Sort(v);
    if(VecFind(v,"BERLAND")<=1) return true;
    return false;
}

void LastFight(){
    int Berland=VecFind(rate,"BERLAND");
    if(Berland<=1){
        printf("1:0");
        exit(0);
    }
    if(rate[Berland].rating+3<rate[1].rating){
        printf("IMPOSSIBLE");
        exit(0);
    }

    int Rival=FindRival(rate);//rival 敌人

    for(int Less=1;Less<=100;Less++){
        for(int X=1;X<=100;X++){
            if(X-Less<0) continue;
            if(Check(Berland,Rival,X,X-Less,rate)){
                printf("%d:%d",X,X-Less);
                exit(0);
            }
        }
    }
}
```
核心实现思想：定义`Node`结构体存储队伍信息，`Judge`函数处理每场比赛结果，`ReadMatch`函数读入前五场比赛信息，`Sort`函数实现队伍排序规则，`Check`函数判断比赛后Berland是否能进前二，`LastFight`函数枚举比分并判断。

### 最优关键思路或技巧
- **数据结构选择**：使用合适的数据结构存储队伍信息，如`map`或`unordered_map`嵌套`struct`，方便根据队伍名称快速查找和更新信息。
- **模拟过程**：通过拷贝现有数据结构来模拟比赛结果，避免直接修改原始数据导致混乱，同时便于重复模拟不同比分情况。
- **枚举策略**：合理确定枚举范围，由于题目中进球数有限，从1到100枚举比分能够满足要求，且保证了答案的全面性。

### 同类型题或类似算法套路
此类题目属于模拟类问题，通常需要根据给定的规则和条件，详细模拟整个过程。类似套路包括：
- 明确规则：仔细分析题目给定的各种规则，如比赛得分规则、排名规则等，确保在模拟过程中准确应用。
- 数据记录与更新：选择合适的数据结构记录每个阶段的状态信息，并在模拟过程中按照规则准确更新。
- 结果判断：根据模拟结果，依据题目要求进行判断，如本题中判断Berland是否进入前两名。

### 洛谷题目推荐
- [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)：通过模拟纸牌移动过程，考察对规则的理解和模拟实现能力。
- [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)：根据后缀表达式的计算规则，模拟计算过程，锻炼对规则的模拟和代码实现。
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：通过模拟数组元素的比较过程，统计逆序对数量，涉及到对数组操作的模拟。

### 个人心得摘录与总结
- Jerrywang09提到将题目理解为踢假球，这种形象的理解方式有助于更快把握题意，在面对复杂模拟题时，找到一种易于理解的角度能更好地梳理思路。 

---
处理用时：103.34秒