# 题目信息

# Two Teams Composing

## 题目描述

You have $ n $ students under your control and you have to compose exactly two teams consisting of some subset of your students. Each student had his own skill, the $ i $ -th student skill is denoted by an integer $ a_i $ (different students can have the same skills).

So, about the teams. Firstly, these two teams should have the same size. Two more constraints:

- The first team should consist of students with distinct skills (i.e. all skills in the first team are unique).
- The second team should consist of students with the same skills (i.e. all skills in the second team are equal).

Note that it is permissible that some student of the first team has the same skill as a student of the second team.

Consider some examples (skills are given):

- $ [1, 2, 3] $ , $ [4, 4] $ is not a good pair of teams because sizes should be the same;
- $ [1, 1, 2] $ , $ [3, 3, 3] $ is not a good pair of teams because the first team should not contain students with the same skills;
- $ [1, 2, 3] $ , $ [3, 4, 4] $ is not a good pair of teams because the second team should contain students with the same skills;
- $ [1, 2, 3] $ , $ [3, 3, 3] $ is a good pair of teams;
- $ [5] $ , $ [6] $ is a good pair of teams.

Your task is to find the maximum possible size $ x $ for which it is possible to compose a valid pair of teams, where each team size is $ x $ (skills in the first team needed to be unique, skills in the second team should be the same between them). A student cannot be part of more than one team.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, it is possible to construct two teams of size $ 3 $ : the first team is $ [1, 2, 4] $ and the second team is $ [4, 4, 4] $ . Note, that there are some other ways to construct two valid teams of size $ 3 $ .

## 样例 #1

### 输入

```
4
7
4 2 4 1 4 3 4
5
2 1 5 4 3
1
1
4
1 1 1 3```

### 输出

```
3
1
0
2```

# AI分析结果

### 题目内容
# 组建两支队伍

## 题目描述
你管理着$n$名学生，你必须从这些学生的子集中恰好组建两支队伍。每个学生都有自己的技能，第$i$个学生的技能用整数$a_i$表示（不同的学生可以有相同的技能）。

关于队伍，有以下要求。首先，这两支队伍的人数必须相同。另外还有两个限制条件：
- 第一支队伍应由技能不同的学生组成（即第一支队伍中的所有技能都是唯一的）。
- 第二支队伍应由技能相同的学生组成（即第二支队伍中的所有技能都相等）。

注意，第一支队伍中的某个学生的技能与第二支队伍中的某个学生的技能相同是允许的。

考虑一些例子（给出技能）：
- $[1, 2, 3]$ ，$[4, 4]$ 不是一对好的队伍，因为人数应该相同；
- $[1, 1, 2]$ ，$[3, 3, 3]$ 不是一对好的队伍，因为第一支队伍不应包含技能相同的学生；
- $[1, 2, 3]$ ，$[3, 4, 4]$ 不是一对好的队伍，因为第二支队伍应包含技能相同的学生；
- $[1, 2, 3]$ ，$[3, 3, 3]$ 是一对好的队伍；
- $[5]$ ，$[6]$ 是一对好的队伍。

你的任务是找到最大可能的人数$x$，使得可以组建一对有效的队伍，其中每支队伍的人数都是$x$（第一支队伍中的技能需要是唯一的，第二支队伍中的技能应该彼此相同）。一个学生不能同时属于多个队伍。

你必须回答$t$个独立的测试用例。

## 说明/提示
在示例的第一个测试用例中，可以组建两支人数为$3$的队伍：第一支队伍是$[1, 2, 4]$，第二支队伍是$[4, 4, 4]$。注意，还有其他一些方法可以组建两支人数为$3$的有效队伍。

## 样例 #1
### 输入
```
4
7
4 2 4 1 4 3 4
5
2 1 5 4 3
1
1
4
1 1 1 3```
### 输出
```
3
1
0
2```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕统计不同技能数量与相同技能最大数量，并据此进行分类讨论来求解。不同题解在实现细节和分析角度上存在差异。有的通过桶排统计，有的使用map；在结果分析上，有的直接根据不同数量关系得出结果，有的采用二分或循环查找合适的队伍人数。

### 所选的题解
- **作者：lingfunny (5星)**
    - **关键亮点**：思路清晰，先明确需统计不同技能值数量$x$和相同技能值数量最大值$y$，再分$x<y$、$x=y$、$x>y$三种情况讨论，利用桶排实现，代码简洁易懂。
    - **重点代码**：
```cpp
#include <iostream>
using namespace std;
int t,n,x,kind,maxtong;
const int maxn = 200005;
int tong[maxn];
int main(){
    cin>>t;
    while(t--){
        kind=maxtong=0;
        cin>>n;
        for(register int i=1;i<=n;++i){
            cin>>x;
            if(!tong[x]++)++kind;
        }
        for(register int i=1;i<=n;++i)
            maxtong=max(maxtong,tong[i]);
        if(maxtong == kind)
            cout<<(kind-1);
        else if(maxtong > kind)
            cout<<kind;
        else
            cout<<maxtong;
        for(int i=1;i<=n;++i)
            tong[i]=0;
        cout<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：先通过桶排统计每个技能出现次数，确定$x$和$y$，再根据不同情况输出结果，最后清空桶数组以处理下一组数据。
- **作者：andyli (5星)**
    - **关键亮点**：分析简洁，统计每个能力出现次数，找出出现次数最多的数$a$及除去该数后不同数的个数$b$，直接得出每组人数为$\min\{a,b\}$，并考虑$a\geq2$时的特殊情况，时间复杂度$\mathcal O(n)$。
    - **重点代码**：
```cpp
const int maxn = 200005, INF = -1u / 2;
int c[maxn], A[maxn];
int main() {
    int q;
    io.read(q);
    while (q--) {
        int n;
        io.read(n);
        for (int i = 1; i <= n; i++)
            c[i] = 0;
        for (int i = 1; i <= n; i++)
            io.read(A[i]), c[A[i]]++;
        int p = 0;
        for (int i = 1; i <= n; i++)
            if (c[i] > c[p])
                p = i;
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            if (c[i] && i!= p)
                cnt++;
        writeln(max(min(cnt, c[p]), c[p] <= 1? -INF : min(c[p] - 1, cnt + 1)));
    }
    return 0;
}
```
    - **核心实现思想**：先清零数组$c$，读入数据并统计各能力出现次数，找到出现次数最多的数及其位置$p$，统计除去该数后不同数的个数$cnt$，根据不同情况计算并输出结果。
- **作者：laboba (4星)**
    - **关键亮点**：使用map统计不同数的出现次数，进而得到不同数的数量$k$和出现最多的数的出现次数$l$，通过分类讨论得出结果，代码逻辑较清晰。
    - **重点代码**：
```cpp
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
const int N=210000;
int a[N],bt[N];
map<int,int>mp;
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),mp[a[i]]++;
        int mx1=mp.size(),mx2=-1;
        for(int i=1;i<=mp.size();i++){
            mx2=max(mx2,mp[i]);
        }
        mx1--;
        if(mx2-mx1>1)printf("%d\n",mx1+1);
        else printf("%d\n",min(mx1,mx2));
        mp.clear();
    }
}
```
    - **核心实现思想**：读入数据并利用map统计每个数出现次数，获取不同数的数量$mx1$和出现最多的数的出现次数$mx2$，对$mx1$减1后分类讨论输出结果，最后清空map处理下一组数据。

### 最优关键思路或技巧
通过统计不同技能的数量和相同技能的最大数量，依据两者关系进行分类讨论得出结果。可利用桶排或map等数据结构实现统计过程，优化时间复杂度。

### 同类型题或类似算法套路拓展
此类题目通常围绕对数据的统计分析，通过挖掘数据间数量关系求解。类似套路如统计不同元素个数、特定元素出现次数等，再依据条件进行分类讨论或贪心选择。

### 洛谷相似题目推荐
- [P1903 数颜色](https://www.luogu.com.cn/problem/P1903)
- [P1131 海战](https://www.luogu.com.cn/problem/P1131)
- [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 个人心得摘录与总结
laboba提到在使用map时要记得清空，否则会影响下一组数据处理，调试时花费了一些时间在这个问题上，强调了处理多组数据时对数据结构状态重置的重要性。 

---
处理用时：72.85秒