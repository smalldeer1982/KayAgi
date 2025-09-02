# 题目信息

# Chess Tourney

## 题目描述

Berland annual chess tournament is coming!

Organizers have gathered $ 2·n $ chess players who should be divided into two teams with $ n $ people each. The first team is sponsored by BerOil and the second team is sponsored by BerMobile. Obviously, organizers should guarantee the win for the team of BerOil.

Thus, organizers should divide all $ 2·n $ players into two teams with $ n $ people each in such a way that the first team always wins.

Every chess player has its rating $ r_{i} $ . It is known that chess player with the greater rating always wins the player with the lower rating. If their ratings are equal then any of the players can win.

After teams assignment there will come a drawing to form $ n $ pairs of opponents: in each pair there is a player from the first team and a player from the second team. Every chess player should be in exactly one pair. Every pair plays once. The drawing is totally random.

Is it possible to divide all $ 2·n $ players into two teams with $ n $ people each so that the player from the first team in every pair wins regardless of the results of the drawing?

## 样例 #1

### 输入

```
2
1 3 2 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1
3 3
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
# 国际象棋锦标赛

## 题目描述
伯兰一年一度的国际象棋锦标赛即将来临！

组织者已经召集了 $2·n$ 名棋手，他们应该被分成两队，每队 $n$ 人。第一队由伯油公司（BerOil）赞助，第二队由伯移动公司（BerMobile）赞助。显然，组织者应该确保伯油公司赞助的队伍获胜。

因此，组织者应该将所有 $2·n$ 名棋手分成两队，每队 $n$ 人，使得第一队总是获胜。

每个棋手都有其等级分 $r_{i}$。已知等级分较高的棋手总是能战胜等级分较低的棋手。如果他们的等级分相等，那么任何一名棋手都可能获胜。

在队伍分配完成后，将进行抽签以组成 $n$ 对对手：每一对中都有一名来自第一队的棋手和一名来自第二队的棋手。每名棋手都应恰好参与一对比赛。每一对进行一场比赛。抽签是完全随机的。

是否有可能将所有 $2·n$ 名棋手分成两队，每队 $n$ 人，使得无论抽签结果如何，每一对中来自第一队的棋手都能获胜？

## 样例 #1
### 输入
```
2
1 3 2 4
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
1
3 3
```
### 输出
```
NO
```

### 综合分析与结论
- **思路**：各题解思路基本一致，都是先对输入的 $2n$ 个棋手等级分进行排序，然后比较排序后第 $n$ 个数和第 $n + 1$ 个数的大小。若第 $n$ 个数小于第 $n + 1$ 个数，则可以将棋手分成满足条件的两队，输出 `YES`；否则输出 `NO`。
- **算法要点**：主要使用了排序算法（如 `sort` 函数）对数组进行排序，然后通过简单的比较操作得出结果。
- **解决难点**：关键在于理解将数组排序后，通过比较中间两个数的大小就能判断是否能满足分组条件。需要考虑到等级分相等时的情况，当第 $n$ 个数和第 $n + 1$ 个数相等时，无法保证第一队总是获胜。

### 题解评分
- **ShineEternal**：5星。思路清晰，代码简洁，注释明确，准确实现了核心思路。
- **Nivi**：4星。思路讲解详细，代码规范，有一定的可读性。
- **Fat_Fish**：4星。对不成立情况有深入思考，代码实现完整。

### 所选题解
- **ShineEternal（5星）**
    - **关键亮点**：代码简洁，注释清晰，准确体现了贪心思想。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[210];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+2*n+1);
    if(a[n]<a[n+1])
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;
}
```
- **Nivi（4星）**
    - **关键亮点**：思路讲解详细，代码规范，适合初学者。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m[201];
    cin>>n;
    for(int i=1;i<=n*2;i++){
        cin>>m[i];
    }
    sort(m+1,m+2*n+1);
    if(m[n]<m[n+1]){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
    return 0;
}
```
- **Fat_Fish（4星）**
    - **关键亮点**：对不成立情况有深入思考，代码实现完整。
    - **核心代码**：
```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int a[n*2+1];
    for(int i=1;i<=n*2;++i){
        cin>>a[i];
    }
    sort(a+1,a+1+n*2);
    if(a[n]<a[n+1]){
        cout<<"YES\n";
        return 0;
    }
    cout<<"NO\n";
    return 0;
}
```

### 最优关键思路或技巧
- **思维方式**：采用贪心思想，将所有棋手等级分排序后，尝试将最小的 $n$ 个作为一队，其余 $n$ 个作为另一队，通过比较两队临界值判断是否满足条件。
- **代码实现技巧**：使用 `sort` 函数对数组进行排序，简化了排序操作。

### 拓展思路
同类型题可能会有不同的分组规则或获胜条件，但核心思路通常都是先排序再进行比较判断。例如，可能会要求将数组分成多组，每组满足特定的大小关系；或者在排序后根据不同的规则进行元素分配。

### 推荐洛谷题目
- P1093 [NOIP2007 普及组] 奖学金
- P1104 生日
- P1271 [深基9.例1] 选举学生会

### 个人心得摘录与总结
- **Nivi**：第一次提交忘记排序，提醒我们在实现代码时要仔细检查关键步骤是否遗漏。
- **Fat_Fish**：一开始认为排序后分组就一定成立，后来考虑到两数相等的情况，说明在解题时要全面思考可能出现的特殊情况。 

---
处理用时：29.38秒