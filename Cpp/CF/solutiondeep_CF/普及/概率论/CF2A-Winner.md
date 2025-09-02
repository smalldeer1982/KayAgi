# 题目信息

# Winner

## 题目描述

在 Berland 流行着纸牌游戏 `Berlogging`，这个游戏的赢家是根据以下规则确定的：

1. 在每一轮中，玩家获得或失去一定数量的分数，在游戏过程中，分数被记录在 `名称和得分` 行中，其中名字是玩家的名字，得分是在这一轮中获得的分数。得分是负值意味着玩家失去了相应的分数。
2. 如果在比赛结束时只有一名玩家分数最多，他就是获胜者。
3. 如果两名或两名以上的玩家在比赛结束时都有最大的分数 $m$ ，那么其中首先获得至少 $m$ 分的玩家胜利。开始时，每个玩家都是 $0$ 分。


保证在比赛结束时至少有一个玩家的分数为正。

## 样例 #1

### 输入

```
3
mike 3
andrew 5
mike 2
```

### 输出

```
andrew
```

## 样例 #2

### 输入

```
3
andrew 3
andrew 2
mike 5
```

### 输出

```
andrew
```

# AI分析结果

### 题目翻译
#### 赢家

### 题目描述
在 Berland 地区，纸牌游戏 “Berlogging” 十分流行，该游戏的赢家按照以下规则确定：
1. 在每一轮中，玩家会获得或失去一定数量的分数。游戏过程中，分数以 “名称和得分” 的形式记录，其中名字代表玩家姓名，得分表示该轮获得的分数。若得分是负数，则意味着玩家失去了相应分数。
2. 若比赛结束时只有一名玩家分数最高，那么该玩家就是赢家。
3. 若两名或更多玩家在比赛结束时都取得了最高分数 $m$，则最先获得至少 $m$ 分的玩家获胜。游戏开始时，每个玩家的初始分数均为 0。

确保比赛结束时至少有一名玩家的分数为正数。

### 样例 #1
#### 输入
```
3
mike 3
andrew 5
mike 2
```
#### 输出
```
andrew
```

### 样例 #2
#### 输入
```
3
andrew 3
andrew 2
mike 5
```
#### 输出
```
andrew
```

### 题解综合分析与结论
这些题解的核心思路都是先记录每个玩家的最终得分，找出最大得分，然后再次遍历游戏过程，找出最先达到最大得分且最终得分等于最大得分的玩家。

#### 算法要点对比
- **使用 `map` 的题解**：利用 `map<string, int>` 方便地记录玩家名字和得分，简化了查找和更新操作。
- **使用结构体的题解**：通过自定义结构体存储玩家信息，手动实现查找和更新，代码相对复杂，但不依赖 STL。

#### 解决难点对比
- **确定最大得分**：所有题解都通过遍历记录的得分来找出最大得分。
- **找出最先达到最大得分的玩家**：需要重新遍历游戏过程，记录每个玩家的实时得分，判断是否最先达到最大得分。

### 评分较高的题解
1. **作者：Honor誉 (赞：26)，5星**
    - **关键亮点**：思路清晰，代码简洁，详细介绍了 `map` 的使用方法，适合初学者。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int> mp,mpp;
int n,a[100001],maxn=-99999999;
string s[100001],s1;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>s[i]>>a[i];
        mp[s[i]]+=a[i];//记录数值
    }
    for(int i=1;i<=n;i++)
    {
        maxn=max(maxn,mp[s[i]]);//取最大
    }
    for(int i=1;i<=n;i++)//谁先到达maxn的就取谁
    {
        mpp[s[i]]+=a[i];
        if(mp[s[i]]==maxn&&mpp[s[i]]>=maxn)
        {
            s1=s[i];
            break;
        }
    }
    cout<<s1<<endl;
    return 0;
} 
```
    - **核心实现思想**：先使用 `mp` 记录每个玩家的最终得分，找出最大得分 `maxn`，再使用 `mpp` 重新记录每个玩家的得分，当某个玩家的最终得分等于 `maxn` 且实时得分大于等于 `maxn` 时，该玩家即为赢家。

2. **作者：Loner_Knowledge (赞：4)，4星**
    - **关键亮点**：提供了 STL 和非 STL 两种实现方式，适合不同水平的学习者。
    - **STL 核心代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<map>
using namespace std;
const int Inf=0x7FFFFFFF;
struct Data {
    string str;
    int score;
}D[1002];
map<string,int> m,t;
int main() {
    int n,Max=-Inf,p=0;
    scanf("%d",&n);
    for(int i=1,num;i<=n;++i) {
        cin>>D[i].str;
        scanf("%d",&D[i].score);
        m[D[i].str]+=D[i].score;
    }
    for(int i=1;i<=n;++i)
        if(m[D[i].str]>Max)
            Max=m[D[i].str];
    for(int i=1;i<=n&&!p;++i) {
        t[D[i].str]+=D[i].score;
        if(m[D[i].str]==Max&&t[D[i].str]>=Max)
            p=i;
    }
    cout<<D[p].str;
    return 0;
}
```
    - **核心实现思想**：使用 `m` 记录每个玩家的最终得分，找出最大得分 `Max`，再使用 `t` 重新记录每个玩家的得分，当某个玩家的最终得分等于 `Max` 且实时得分大于等于 `Max` 时，记录该玩家的编号 `p`，最后输出该玩家的名字。

3. **作者：xiaohuang (赞：1)，4星**
    - **关键亮点**：代码结构清晰，注释详细，对思路的解释明确。
    - **核心代码**：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>

using namespace std;

const int INF = 0x3f3f3f3f, MAXN =  1005;
int n, a[MAXN];
string name[MAXN];
map<string, int> Map1, Map2;
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> name[i] >> a[i];
        Map1[name[i]] += a[i];
    }//映射到map里
    int Max = -INF;
    for (int i = 0; i < n; i++)
        if (Map1[name[i]] > Max) Max = Map1[name[i]];//求出最大得分
    for (int i = 0; i < n; i++) {
        Map2[name[i]] += a[i];
        if (Map2[name[i]] >= Max && Map1[name[i]] >= Max) {
            cout << name[i] << endl;//输出最先到最大得分的人
            return 0;
        }
    }
    return 0;
}
```
    - **核心实现思想**：使用 `Map1` 记录每个玩家的最终得分，找出最大得分 `Max`，再使用 `Map2` 重新记录每个玩家的得分，当某个玩家的最终得分大于等于 `Max` 且实时得分大于等于 `Max` 时，输出该玩家的名字。

### 最优关键思路或技巧
- 使用 `map` 数据结构可以方便地记录玩家名字和得分，避免手动实现查找和更新操作。
- 分两步处理：先记录最终得分，找出最大得分；再重新遍历游戏过程，找出最先达到最大得分的玩家。

### 可拓展之处
同类型题可能会有更复杂的规则，如多轮比赛、不同的得分计算方式等。类似算法套路可用于处理其他需要记录和比较数据的问题，如统计不同元素的出现次数、找出满足特定条件的元素等。

### 推荐洛谷题目
1. [P1160 队列安排](https://www.luogu.com.cn/problem/P1160)：考察链表的使用，与本题中记录和处理数据的思路有一定相似性。
2. [P1540 机器翻译](https://www.luogu.com.cn/problem/P1540)：考察队列和集合的使用，可锻炼数据处理和查找的能力。
3. [P2676 [USACO07DEC]Bookshelf B](https://www.luogu.com.cn/problem/P2676)：考察贪心算法和数据记录，有助于提高问题分析和解决能力。

### 个人心得摘录与总结
- **作者：sandwich**：提到题目有很多坑，通过讨论区的数据解决了难题，强调了测试数据的重要性。
- **作者：purple7**：第一次做时没考虑负数导致 WA 了最后一个点，提醒我们在解题时要考虑边界情况。
- **作者：_Blue_**：表示自己一开始没理解题意，找了半天错误，强调正确理解题意的重要性。

---
处理用时：44.30秒