# 题目信息

# Not Afraid

## 题目描述

Since the giant heads have appeared in the sky all humanity is in danger, so all Ricks and Mortys from all parallel universes are gathering in groups to find a solution to get rid of them.

There are $ n $ parallel universes participating in this event ( $ n $ Ricks and $ n $ Mortys). I. e. each of $ n $ universes has one Rick and one Morty. They're gathering in $ m $ groups. Each person can be in many groups and a group can contain an arbitrary number of members.

Ricks and Mortys have registered online in these groups. So, a person can have joined a group more than once (developer of this website hadn't considered this possibility).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787B/dcab08f4f41338897a1e46a0544bffe9ab994433.png)Summer from universe #1 knows that in each parallel universe (including hers) exactly one of Rick and Morty from that universe is a traitor and is loyal, but no one knows which one. She knows that we are doomed if there's a group such that every member in that group is a traitor (they will plan and destroy the world).

Summer knows that if there's a possibility that world ends (there's a group where all members are traitors) she should immediately cancel this event. So she wants to know if she should cancel the event. You have to tell her yes if and only if there's at least one scenario (among all $ 2^{n} $ possible scenarios, $ 2 $ possible scenarios for who a traitor in each universe) such that in that scenario the world will end.

## 说明/提示

In the first sample testcase, $ 1 $ st group only contains the Rick from universe number $ 3 $ , so in case he's a traitor, then all members of this group are traitors and so Summer should cancel the event.

## 样例 #1

### 输入

```
4 2
1 -3
4 -2 3 2 -3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 2
5 3 -2 1 -1 5
3 -5 2 5
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
7 2
3 -1 6 7
7 -5 4 2 4 7 -3 4
```

### 输出

```
YES
```

# AI分析结果

### 题目翻译
# 无所畏惧

## 题目描述
自从巨大的头颅出现在天空中，全人类都陷入了危险之中。因此，来自所有平行宇宙的瑞克（Rick）和莫蒂（Morty）都在组队，试图找到摆脱它们的方法。

有 $n$ 个平行宇宙参与了这次行动（$n$ 个瑞克和 $n$ 个莫蒂）。也就是说，$n$ 个宇宙中的每个宇宙都有一个瑞克和一个莫蒂。他们正在组成 $m$ 个小组。每个人可以加入多个小组，一个小组也可以包含任意数量的成员。

瑞克和莫蒂已经在网上注册加入了这些小组。所以，一个人可能多次加入同一个小组（这个网站的开发者没有考虑到这种可能性）。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787B/dcab08f4f41338897a1e46a0544bffe9ab994433.png)来自 1 号宇宙的萨默（Summer）知道，在每个平行宇宙（包括她自己的宇宙）中，该宇宙的瑞克和莫蒂中恰好有一个是叛徒，另一个是忠诚的，但没有人知道具体是谁。她知道，如果有一个小组中的每个成员都是叛徒，我们就完蛋了（他们会策划并毁灭世界）。

萨默知道，如果有可能世界末日降临（存在一个小组，其中所有成员都是叛徒），她应该立即取消这次行动。所以她想知道是否应该取消这次行动。当且仅当存在至少一种情况（在所有 $2^{n}$ 种可能的情况中，每个宇宙有 2 种可能的叛徒情况），在这种情况下世界将会毁灭，你才应该告诉她 “yes”。

## 说明/提示
在第一个样例测试用例中，第一组只包含 3 号宇宙的瑞克。所以，如果他是叛徒，那么这个小组的所有成员都是叛徒，因此萨默应该取消这次行动。

## 样例 #1
### 输入
```
4 2
1 -3
4 -2 3 2 -3
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
5 2
5 3 -2 1 -1 5
3 -5 2 5
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
7 2
3 -1 6 7
7 -5 4 2 4 7 -3 4
```
### 输出
```
YES
```

### 算法分类
无算法分类

### 综合分析与结论
这些题解的核心思路都是判断每个团队中是否存在互为相反数的编号，若存在则该团队不可能全是叛徒，若所有团队都不存在这样的情况，则存在团队全是叛徒的可能。

不同题解的实现方式有所不同，部分使用 `map` 容器来记录出现过的数，部分使用两个数组分别记录正数和负数的出现情况。

### 所选题解
- **rui_er（4星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `map` 容器记录出现过的数，通过判断相反数是否出现来确定团队是否可能全是叛徒。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
map<int, int> mp;

int main() {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=m;i++) {
        int _;
        scanf("%d", &_);
        mp.clear();
        bool ok = false;
        while(_--) {
            int x;
            scanf("%d", &x);
            if(mp[-x]) ok = true;
            mp[x] = 1;
        }
        if(!ok) return puts("YES"), 0;
    }
    puts("NO");
    return 0;
}
```
核心实现思想：对于每个团队，先清空 `map`，然后遍历团队中的每个成员编号，若其相反数已经在 `map` 中出现过，则该团队不可能全是叛徒，标记 `ok` 为 `true`；若遍历完都没有出现相反数，则该团队可能全是叛徒，输出 `YES` 并结束程序。若所有团队都不可能全是叛徒，则输出 `NO`。

- **封禁用户（4星）**
    - **关键亮点**：详细解释了 `map` 容器的使用方法，代码逻辑清晰，通过 `map` 记录出现过的数，判断是否存在相反数。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,x;
map<int,bool>mp;
int main(){
    cin>>n>>m;
    while(m--){
        bool f=0;
        cin>>t,mp.clear();
        while(t--){
            cin>>x,mp[x]=1;
            if(mp[-x])f=1;
        }
        if(!f)return cout<<"YES",0;
    }
    return cout<<"NO",0;
}
```
核心实现思想：与 rui_er 的题解类似，对于每个团队，清空 `map`，遍历团队成员编号，若其相反数已在 `map` 中，则标记 `f` 为 `true`，表示该团队不可能全是叛徒；若遍历完 `f` 仍为 `false`，则该团队可能全是叛徒，输出 `YES` 并结束程序，否则输出 `NO`。

### 最优关键思路或技巧
使用 `map` 容器记录出现过的数，能方便地判断某个数的相反数是否已经出现，时间复杂度较低。

### 拓展思路
同类型题目可能会有不同的背景设定，但核心逻辑都是判断是否存在某种特殊关系的元素组合。可以使用类似的记录和判断方法来解决，如使用数组、集合等数据结构记录元素的出现情况。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
3. [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)

### 个人心得摘录与总结
- **豌豆射手皮0608**：最初使用桶排思路，对正数和负数出现次数进行累加判断，遇到特殊数据会出错，因为正数和负数出现次数不一定相等。后来改为记录正数和负数是否出现过，成功 AC。总结是在处理类似问题时，要考虑数据的特性，避免简单累加带来的错误。 

---
处理用时：42.22秒