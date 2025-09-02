# 题目信息

# Smart Boy

## 题目描述

Petya和Vasya发明了一种新的游戏，并把它叫做 "聪明小子"。他们为这个游戏规定了一组单词——字典。字典中可以包含类似的单词。

游戏规则如下：首先，第一个玩家从字典中的任意一个单词中选择任意一个字母,得到一个长度为 $1$ 的单词，并将其写在一张纸上。第二位玩家在这个字母的开头或结尾位置加上其他字母，这样就形成了一个长度为 $2$ 的单词，然后又轮到第一位玩家，他在目前单词的开头或结尾加上一个字母，这样就形成了一个长度为 $3$ 的单词，以此类推。但玩家的操作必须满足一个条件：新造的单词必须是字典中的一个单词的子串。如果玩家不能在不违反条件的情况下给当前的单词添加一个字母，那么他就输了。

另外，如果在一个回合结束时，某个字符串 $s$ 被写在纸上，那么刚刚完成操作的玩家，就会根据公式得到一定的分数:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/0581ff8dd9c5f97bc34f4839b9be626798958173.png)

其中:


- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/e4be189456c3857fdc2ca591471080a7e0553024.png)是拉丁字母（即英文字母）中符号 $c$ 的序列号，从 $1$ 开始编号。例如![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/a709cc8eab21d8d610387ef6b07c36d3277a654a.png)，和![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/72027ed786a5fe069852a41dd736894e110bbaab.png) 。
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/a15427ebfe6c6b2fd1a1aca564e59cc85cdf2fd3.png)是字典中含有 $s$ 的单词数量。（若字符串 $s$ 作为子串在单词 $x$ 中出现至少一次，我们称 $x$ 是一个含有 $s$ 的单词）

你的任务是计算出谁将赢得游戏以及最后的分数是多少。每个玩家都会以最佳的方式进行游戏，并且试图赢得比赛，即使自己的分数最大化，使对手的分数最小化。

## 样例 #1

### 输入

```
2
aba
abac
```

### 输出

```
Second
29 35
```

## 样例 #2

### 输入

```
3
artem
nik
max
```

### 输出

```
First
2403 1882
```

# AI分析结果

### 题目内容
# 聪明小子

## 题目描述
Petya和Vasya发明了一种新的游戏，并把它叫做 “聪明小子”。他们为这个游戏规定了一组单词——字典。字典中可以包含类似的单词。

游戏规则如下：首先，第一个玩家从字典中的任意一个单词中选择任意一个字母，得到一个长度为1的单词，并将其写在一张纸上。第二位玩家在这个字母的开头或结尾位置加上其他字母，这样就形成了一个长度为2的单词，然后又轮到第一位玩家，他在目前单词的开头或结尾加上一个字母，这样就形成了一个长度为3的单词，以此类推。但玩家的操作必须满足一个条件：新造的单词必须是字典中的一个单词的子串。如果玩家不能在不违反条件的情况下给当前的单词添加一个字母，那么他就输了。

另外，如果在一个回合结束时，某个字符串 $s$ 被写在纸上，那么刚刚完成操作的玩家，就会根据公式得到一定的分数:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/0581ff8dd9c5f97bc34f4839b9be626798958173.png)

其中:

-  $\text{value}(c)$ 是拉丁字母（即英文字母）中符号 $c$ 的序列号，从1开始编号。例如 $\text{value}(\text{'a'}) = 1$，和 $\text{value}(\text{'z'}) = 26$ 。
-  $num(s)$ 是字典中含有 $s$ 的单词数量。（若字符串 $s$ 作为子串在单词 $x$ 中出现至少一次，我们称 $x$ 是一个含有 $s$ 的单词）

你的任务是计算出谁将赢得游戏以及最后的分数是多少。每个玩家都会以最佳的方式进行游戏，并且试图赢得比赛，即使自己的分数最大化，使对手的分数最小化。

## 样例 #1
### 输入
```
2
aba
abac
```
### 输出
```
Second
29 35
```

## 样例 #2
### 输入
```
3
artem
nik
max
```
### 输出
```
First
2403 1882
```

### 算法分类
动态规划

### 综合分析与结论
两题解均基于博弈论采用动态规划思想解题。liangbowen题解提出直接暴力DP，通过预处理 $num(s)$ 后进行记忆化搜索，暴力枚举每次操作字符；EgLund题解同样用动态规划，利用 `std::unordered_map` 解决字符串存储问题，通过倒推状态转移更新答案，并使用 `std::set` 预处理状态转移。两题解思路相近，EgLund题解代码实现更完整清晰。

### 所选的题解
 - **EgLund题解**：★★★★
    - **关键亮点**：代码实现完整，巧妙利用 `std::unordered_map` 解决字符串存储问题，通过倒推状态转移更新答案，并用 `std::set` 预处理状态转移。
 - **liangbowen题解**：★★★
    - **关键亮点**：提出暴力DP结合记忆化搜索的思路，直接模拟过程解题。

### 重点代码及核心实现思想
**EgLund题解核心代码**：
```cpp
#include<bits/stdc++.h>

using namespace std;

using Status=pair<bool,pair<int,int> >;
int n,a[14000],b[14000],vis[14000];
string s[31];
map<string,int> mp;
#define get_id(str) ((mp.count(str))?(mp[str]):(mp[str]=mp.size()-1))
set<int> g[14000];
Status dp[14000];

Status dfs(int u)
{
    if(!vis[u])
    {
        vis[u]=1;
        if(g[u].empty())return make_pair(0,make_pair(0,0));
        else
        {
            Status res=make_pair(0,make_pair(0,0));
            for(int v:g[u])
            {
                Status p=dfs(v);
                res=max(res,make_pair(!p.first,make_pair(a[v]-p.second.second,-p.second.first)));
            }
            dp[u]=res;
        }
    }
    return dp[u];
}

int main()
{
    cin>>n;
    mp[""]=0;
    for(int i=1;i<=n;i++)
    {
        memset(b,0,sizeof b);
        cin>>s[i];
        for(int j=0;j<(int)s[i].size();j++)
        {
            for(int k=1;k+j<=(int)s[i].size();k++)
            {
                b[get_id(s[i].substr(j,k))]=1;
            }
        }
        for(int j=0;j<14000;j++)a[j]+=b[j];
    }
    for(pair<string,int> i:mp)
    {
        int mx=0,sm=0;
        for(int j=0;j<(int)i.first.size();j++)
        {
            mx=max(mx,i.first[j]-'a'+1);
            sm+=i.first[j]-'a'+1;
        }
        a[i.second]+=mx*sm;
        if(i.first!="")
        {
            if(mp.count(i.first.substr(1,i.first.size()-1)))g[mp[i.first.substr(1,i.first.size()-1)]].insert(i.second);
            if(mp.count(i.first.substr(0,i.first.size()-1)))g[mp[i.first.substr(0,i.first.size()-1)]].insert(i.second);
        }
    }
    Status p=dfs(0);
    cout<<((p.first)?"First":"Second")<<endl<<p.second.first<<' '<<-p.second.second;
}
```
**核心实现思想**：通过 `dfs` 函数进行记忆化搜索，利用 `dp` 数组存储每个状态下的胜负情况和双方分数。在 `main` 函数中，先预处理每个子串在字典中的出现次数，再计算每个子串对应的分数，并构建状态转移关系，最后通过 `dfs` 从初始状态开始倒推，得出最终结果。

### 最优关键思路或技巧
利用 `std::unordered_map` 将字符串映射为序数，解决字符串难以直接作为数组下标的问题；通过倒推状态转移，从必败态推出必胜态，有效解决了正向转移困难的问题。

### 同类型题或类似算法套路拓展
此类题目属于博弈论与动态规划结合的问题，通常可以通过定义状态、确定状态转移方程来解决。类似套路包括根据游戏规则确定每个状态下玩家的最优决策，通过记忆化搜索或递推方式求解。

### 洛谷相似题目推荐
 - [P1288 取数游戏II](https://www.luogu.com.cn/problem/P1288)
 - [P2197 模板 - Nim游戏](https://www.luogu.com.cn/problem/P2197)
 - [P2252 取石子游戏II](https://www.luogu.com.cn/problem/P2252)

### 个人心得摘录及总结
无。 

---
处理用时：68.31秒