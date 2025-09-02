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

### 题目内容（已为中文，无需翻译）
在 Berland 流行着纸牌游戏 `Berlogging`，这个游戏的赢家是根据以下规则确定的：

1. 在每一轮中，玩家获得或失去一定数量的分数，在游戏过程中，分数被记录在 `名称和得分` 行中，其中名字是玩家的名字，得分是在这一轮中获得的分数。得分是负值意味着玩家失去了相应的分数。
2. 如果在比赛结束时只有一名玩家分数最多，他就是获胜者。
3. 如果两名或两名以上的玩家在比赛结束时都有最大的分数 $m$ ，那么其中首先获得至少 $m$ 分的玩家胜利。开始时，每个玩家都是 $0$ 分。

保证在比赛结束时至少有一个玩家的分数为正。

### 综合分析与结论
这些题解主要围绕如何确定纸牌游戏 `Berlogging` 的获胜者展开。思路大致相同，先记录每个玩家的最终得分，找出最大得分，再重新遍历比赛过程，确定最先达到最大得分的玩家。

- **思路对比**：大部分题解使用 `map` 来记录玩家得分，少数使用结构体或数组模拟 `map` 的功能。
- **算法要点**：
    - 记录每个玩家的最终得分。
    - 找出最大得分。
    - 重新遍历比赛过程，确定最先达到最大得分的玩家。
- **解决难点**：
    - 处理玩家名字和得分的映射关系。
    - 处理多个玩家最终得分相同的情况。

### 评分情况
| 作者 | 评分 | 理由 |
| ---- | ---- | ---- |
| Honor誉 | 4星 | 思路清晰，代码简洁，对 `map` 的使用进行了详细介绍。 |
| _Blue_ | 4星 | 运用迭代器和双元结构体，提供了高端写法，对题意理解准确。 |
| Loner_Knowledge | 4星 | 提供了 STL 和非 STL 两种代码，对题意理解深刻，代码注释详细。 |

### 所选题解
- **作者：Honor誉（4星）**
    - **关键亮点**：思路清晰，代码简洁，对 `map` 的使用进行了详细介绍。
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
    - **核心实现思想**：使用两个 `map` 分别记录玩家的最终得分和过程得分，先找出最大得分，再遍历比赛过程，找出最先达到最大得分的玩家。

- **作者：_Blue_（4星）**
    - **关键亮点**：运用迭代器和双元结构体，提供了高端写法，对题意理解准确。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<string,int>Pair;
typedef pair<int,int>PPair;
map<int,Pair> q;
map<string,PPair> p;
int n;
int m;
int main(){
   scanf("%d",&n);
   for(int i=1;i<=n;i++){
       string x;int v;
       cin>>x>>v;
       q[i].first=x;
       q[i].second=v;
       p[x].first+=v;
   } 
   for(map<string,PPair>::iterator it=p.begin();it!=p.end();it++){
       m=max(p[it->first].first,m);
   }
   for(int i=1;i<=n;i++){
       p[q[i].first].second+=q[i].second;
       if(p[q[i].first].second>=m&&p[q[i].first].first==m){
           cout<<q[i].first<<endl;
           return 0;
       }
   }
   
}
```
    - **核心实现思想**：使用 `map` 和 `pair` 记录玩家的信息，通过迭代器找出最大得分，再遍历比赛过程，找出最先达到最大得分的玩家。

- **作者：Loner_Knowledge（4星）**
    - **关键亮点**：提供了 STL 和非 STL 两种代码，对题意理解深刻，代码注释详细。
    - **核心代码（STL）**：
```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<map>
using namespace std;        //皆同上所述
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
    - **核心实现思想**：使用 `map` 记录玩家的最终得分和过程得分，先找出最大得分，再遍历比赛过程，找出最先达到最大得分的玩家。

### 最优关键思路或技巧
- 使用 `map` 来处理玩家名字和得分的映射关系，简化代码实现。
- 分两步遍历比赛过程，第一步记录最终得分，第二步确定最先达到最大得分的玩家。

### 可拓展之处
同类型题可能会有更多的规则和条件，如增加玩家属性、比赛轮数等。类似算法套路可以应用于其他需要记录和比较数据的场景，如比赛排名、游戏得分统计等。

### 推荐洛谷题目
1. [P1093 [NOIP2007 普及组] 奖学金](https://www.luogu.com.cn/problem/P1093)
2. [P1177 [模板] 快速排序](https://www.luogu.com.cn/problem/P1177)
3. [P1540 [NOIP2010 提高组] 机器翻译](https://www.luogu.com.cn/problem/P1540)

### 个人心得摘录与总结
- **sandwich**：提到讨论区的大佬帮忙解决了很多难题，并给出了一些有用的数据，提醒要注意题目的细节，如“至少”等关键字。
- **purple7**：第一次做时没有考虑到负数，WA了最后一个点，提醒要注意数据的范围和特殊情况。
- **_Blue_**：表示自己没有理解题意，找了半天错误，提醒要正确理解题意。

---
处理用时：39.77秒