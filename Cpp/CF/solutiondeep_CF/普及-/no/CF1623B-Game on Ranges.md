# 题目信息

# Game on Ranges

## 题目描述

Alice and Bob play the following game. Alice has a set $ S $ of disjoint ranges of integers, initially containing only one range $ [1, n] $ . In one turn, Alice picks a range $ [l, r] $ from the set $ S $ and asks Bob to pick a number in the range. Bob chooses a number $ d $ ( $ l \le d \le r $ ). Then Alice removes $ [l, r] $ from $ S $ and puts into the set $ S $ the range $ [l, d - 1] $ (if $ l \le d - 1 $ ) and the range $ [d + 1, r] $ (if $ d + 1 \le r $ ). The game ends when the set $ S $ is empty. We can show that the number of turns in each game is exactly $ n $ .

After playing the game, Alice remembers all the ranges $ [l, r] $ she picked from the set $ S $ , but Bob does not remember any of the numbers that he picked. But Bob is smart, and he knows he can find out his numbers $ d $ from Alice's ranges, and so he asks you for help with your programming skill.

Given the list of ranges that Alice has picked ( $ [l, r] $ ), for each range, help Bob find the number $ d $ that Bob has picked.

We can show that there is always a unique way for Bob to choose his number for a list of valid ranges picked by Alice.

## 说明/提示

In the first test case, there is only 1 range $ [1, 1] $ . There was only one range $ [1, 1] $ for Alice to pick, and there was only one number $ 1 $ for Bob to pick.

In the second test case, $ n = 3 $ . Initially, the set contains only one range $ [1, 3] $ .

- Alice picked the range $ [1, 3] $ . Bob picked the number $ 1 $ . Then Alice put the range $ [2, 3] $ back to the set, which after this turn is the only range in the set.
- Alice picked the range $ [2, 3] $ . Bob picked the number $ 3 $ . Then Alice put the range $ [2, 2] $ back to the set.
- Alice picked the range $ [2, 2] $ . Bob picked the number $ 2 $ . The game ended.

In the fourth test case, the game was played with $ n = 5 $ . Initially, the set contains only one range $ [1, 5] $ . The game's turn is described in the following table.

 Game turnAlice's picked rangeBob's picked numberThe range set afterBefore the game start $  \{ [1, 5] \}  $ 1 $ [1, 5] $  $ 3 $  $  \{ [1, 2], [4, 5] \} $ 2 $ [1, 2] $  $ 1 $  $  \{ [2, 2], [4, 5] \}  $ 3 $ [4, 5] $  $ 5 $  $  \{ [2, 2], [4, 4] \}  $ 4 $ [2, 2] $  $ 2 $  $  \{ [4, 4] \}  $ 5 $ [4, 4] $  $ 4 $  $  \{ \}  $ (empty set)

## 样例 #1

### 输入

```
4
1
1 1
3
1 3
2 3
2 2
6
1 1
3 5
4 4
3 6
4 5
1 6
5
1 5
1 2
4 5
2 2
4 4```

### 输出

```
1 1 1

1 3 1
2 2 2
2 3 3

1 1 1
3 5 3
4 4 4
3 6 6
4 5 5
1 6 2

1 5 3
1 2 1
4 5 5
2 2 2
4 4 4```

# AI分析结果

### 题目内容
# 区间上的游戏

## 题目描述
爱丽丝和鲍勃玩以下游戏。爱丽丝有一个不相交的整数区间集合 \( S \)，初始时仅包含一个区间 \( [1, n] \) 。在一轮中，爱丽丝从集合 \( S \) 中选取一个区间 \( [l, r] \)，并让鲍勃在该区间中选一个数。鲍勃选择一个数 \( d \)（\( l \leq d \leq r \)）。然后爱丽丝从集合 \( S \) 中移除 \( [l, r] \)，并将区间 \( [l, d - 1] \)（如果 \( l \leq d - 1 \)）和区间 \( [d + 1, r] \)（如果 \( d + 1 \leq r \)）放入集合 \( S \) 。当集合 \( S \) 为空时游戏结束。可以证明每个游戏的轮数恰好为 \( n \) 。

游戏结束后，爱丽丝记得她从集合 \( S \) 中选取的所有区间 \( [l, r] \)，但鲍勃不记得他选取的任何数字。不过鲍勃很聪明，他知道可以从爱丽丝的区间中找出他选的数字 \( d \)，所以他向你求助，希望借助你的编程能力帮忙。

给定爱丽丝选取的区间列表（\( [l, r] \)），对于每个区间，帮助鲍勃找出他选取的数字 \( d \) 。

可以证明，对于爱丽丝选取的有效区间列表，鲍勃总是有一种唯一的方式来选择他的数字。

## 说明/提示
在第一个测试用例中，只有 1 个区间 \( [1, 1] \) 。爱丽丝只能选取这一个区间 \( [1, 1] \)，鲍勃也只能选取数字 \( 1 \) 。

在第二个测试用例中，\( n = 3 \) 。初始时，集合仅包含一个区间 \( [1, 3] \) 。
 - 爱丽丝选取区间 \( [1, 3] \) 。鲍勃选取数字 \( 1 \) 。然后爱丽丝将区间 \( [2, 3] \) 放回集合，此轮过后该区间是集合中唯一的区间。
 - 爱丽丝选取区间 \( [2, 3] \) 。鲍勃选取数字 \( 3 \) 。然后爱丽丝将区间 \( [2, 2] \) 放回集合。
 - 爱丽丝选取区间 \( [2, 2] \) 。鲍勃选取数字 \( 2 \) 。游戏结束。

在第四个测试用例中，游戏以 \( n = 5 \) 进行。初始时，集合仅包含一个区间 \( [1, 5] \) 。游戏的轮次描述如下表：
|游戏轮次|爱丽丝选取的区间|鲍勃选取的数字|之后的区间集合|
| ---- | ---- | ---- | ---- |
|游戏开始前|\( \{ [1, 5] \} \)| - | - |
|1|\( [1, 5] \)|\( 3 \)|\( \{ [1, 2], [4, 5] \} \)|
|2|\( [1, 2] \)|\( 1 \)|\( \{ [2, 2], [4, 5] \} \)|
|3|\( [4, 5] \)|\( 5 \)|\( \{ [2, 2], [4, 4] \} \)|
|4|\( [2, 2] \)|\( 2 \)|\( \{ [4, 4] \} \)|
|5|\( [4, 4] \)|\( 4 \)|\( \{ \} \)（空集）|

## 样例 #1
### 输入
```
4
1
1 1
3
1 3
2 3
2 2
6
1 1
3 5
4 4
3 6
4 5
1 6
5
1 5
1 2
4 5
2 2
4 4
```
### 输出
```
1 1 1

1 3 1
2 2 2
2 3 3

1 1 1
3 5 3
4 4 4
3 6 6
4 5 5
1 6 2

1 5 3
1 2 1
4 5 5
2 2 2
4 4 4
```

### 算法分类
排序

### 综合分析与结论
这些题解主要围绕如何根据给定的区间列表确定鲍勃选取的数字。多数题解采用排序结合贪心的策略。不同题解的排序依据和贪心方式略有不同，有的按区间长度排序，有的按区间端点排序。解决的难点在于如何通过对区间的合理排序和分析，找到每个区间对应的唯一数字。

### 所选的题解
 - **作者：deviance (4星)**
    - **关键亮点**：思路清晰，先解释题意并举例说明，再提出将区间按长度从小到大排序，利用每个区间对应的 \( d \) 值不同且左右端点相等区间 \( d \) 值易确定的特点，逐步确定所有区间的 \( d \) 值。
    - **重点代码及核心思想**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define LM LLONG_MAX
#define IM INT_MAX
#define N 1001
struct pair1
{
    int l;
    int r;
    int len;
    int d=0;
};
bool cmp(pair1 a,pair1 b)
{
    return a.len<b.len;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        bool vis1[N]={0};
        int n,ans[N];
        cin>>n;
        pair1 a[N];
        for(int i=1;i<=n;i++)
        {
            cin>>a[i].l>>a[i].r;
            a[i].len=a[i].r-a[i].l;
        }
        sort(a+1,a+1+n,cmp);
        for(int i=1;i<=n;i++)
        {
            if(a[i].l==a[i].r)
            {
                a[i].d=a[i].l;
                vis1[a[i].d]=true;
            }
            else 
            {
                for(int j=a[i].l;j<=a[i].r;j++)
                {
                    if(!vis1[j])
                    {
                        a[i].d=j;
                        vis1[j]=true;
                    }
                }
            }
        }
        for(int i=1;i<=n;i++) cout<<a[i].l<<" "<<a[i].r<<" "<<a[i].d<<endl;
    }
}
```
核心思想是先按区间长度排序，对于长度为1的区间（左右端点相等）直接确定 \( d \) 值并标记，对于其他区间，在未标记的数中找 \( d \) 值并标记。

 - **作者：Legitimity (4星)**
    - **关键亮点**：提出按区间长度从大到小排序（类似拓扑排序），并基于排序后的区间关系，通过三种情况判断确定每个区间对应的 \( d \) 值，还提到可使用bfs实现及复杂度优化。
    - **重点代码及核心思想**：代码略（链接：https://www.luogu.com.cn/paste/83thr75h）。核心思想是排序后，对每个区间，根据比它短的区间中左端点等于它左端点和右端点等于它右端点的情况，确定 \( d \) 值。例如不存在左端点相等的短区间，则取左端点为 \( d \) 值；不存在右端点相等的短区间，则取右端点为 \( d \) 值；若都存在，则取右端点加1为 \( d \) 值。

 - **作者：liuyuanpei (4星)**
    - **关键亮点**：给出两种方法，一种是先结构体排序，利用删过的数不会再出现的特点，通过遍历找未选的数确定 \( d \) 值；另一种更优方法是按特定规则排序区间（左端点不同时按左端点从小到大，左端点相同时按右端点从大到小），根据排序后区间关系确定 \( d \) 值。
    - **重点代码及核心思想**：
```cpp
# include <iostream>
# include <cmath>
# include <cstring>
# include <string>
# include <algorithm>
# include <stack>
# include <queue>
# include <set>
# include <map>
using namespace std;
struct node{//结构体
    int l,r;
    int id,ans;
}a[100005],b[100005];
bool tt[100005];
bool cmp(node a,node b){//排序
    if((a.r-a.l)!=(b.r-b.l)) return (a.r-a.l)<(b.r-b.l);
    return a.l<b.l;
}
int main(){
    int t;
    cin >>t;
    while(t--){
        memset(tt,0,sizeof(tt));//清空桶 
        int n;
        cin >>n;
        for(int i=1;i<=n;i++) {
            cin >>a[i].l>>a[i].r;
            a[i].id=i;
        }
        sort(a+1,a+n+1,cmp);//排序 
        for(int i=1;i<=n;i++) {
            for(int j=a[i].l,k=a[i].r;j<=k;j++,k--) {
                if(!tt[j]) {
                    tt[j]=1;
                    a[i].ans=j;
                    continue;
                }
                if(!tt[k]) {
                    tt[k]=1;
                    a[i].ans=k;
                    continue;
                }
            }
            b[a[i].id].l=a[i].l;
            b[a[i].id].r=a[i].r;
            b[a[i].id].ans=a[i].ans;
        }
        for(int i=1;i<=n;i++) 
            cout <<b[i].l<<" "<<b[i].r<<" "<<b[i].ans<<endl;
        cout <<endl;
    }
    return 0;
}
```
核心思想是按特定规则排序后，对于左端点相同的区间，下一个区间由当前区间分割而来，分割点为下一个区间右端点加1；若下一个区间左端点不同，则当前区间是该左端点分割出的最后一个区间，分割点为当前区间左端点。

### 最优关键思路或技巧
通过合理的区间排序（如按长度或端点排序），利用区间之间的包含与分割关系，结合每个区间对应的 \( d \) 值唯一且不重复的特点，确定每个区间的 \( d \) 值。

### 可拓展思路
此类题目可拓展到更复杂的区间操作和关系判断，例如区间有重叠情况，或者操作规则更复杂。类似算法套路是先对区间进行合理排序，再分析区间间的逻辑关系来解决问题。

### 推荐洛谷题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据排序并贪心求解。
 - [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：利用贪心和字符串处理。
 - [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)：对区间进行排序后贪心处理。

### 个人心得摘录与总结
 - **作者：deviance**：第一次发题解，强调了格式处理，建议先自己理解原题再看其题解对题意的理解。总结为发题解要注重格式，且帮助读者理解题意很重要。 

---
处理用时：75.79秒