# 题目信息

# Asesino (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, you can ask at most $ n+69 $ questions. You can make hacks only if both versions of the problem are solved.

This is an interactive problem.

It is a tradition in Mexico's national IOI trainings to play the game "Asesino", which is similar to "Among Us" or "Mafia".

Today, $ n $ players, numbered from $ 1 $ to $ n $ , will play "Asesino" with the following three roles:

- Knight: a Knight is someone who always tells the truth.
- Knave: a Knave is someone who always lies.
- Impostor: an Impostor is someone everybody thinks is a Knight, but is secretly a Knave.

Each player will be assigned a role in the game. There will be exactly one Impostor but there can be any (possible zero) number of Knights and Knaves.

As the game moderator, you have accidentally forgotten the roles of everyone, but you need to determine the player who is the Impostor.

To determine the Impostor, you will ask some questions. In each question, you will pick two players $ i $ and $ j $ ( $ 1 \leq i, j \leq n $ ; $ i \neq j $ ) and ask if player $ i $ thinks that player $ j $ is a Knight. The results of the question is shown in the table below.

 KnightKnaveImpostorKnightYesNoYesKnaveNoYesNoImpostorNoYes— The response of the cell in row $ a $ and column $ b $ is the result of asking a question when $ i $ has role $ a $ and $ j $ has row $ b $ . For example, the "Yes" in the top right cell belongs to row "Knight" and column "Impostor", so it is the response when $ i $ is a Knight and $ j $ is an Impostor.Find the Impostor in at most $ n + 69 $ questions.

Note: the grader is adaptive: the roles of the players are not fixed in the beginning and may change depending on your questions. However, it is guaranteed that there exists an assignment of roles that is consistent with all previously asked questions under the constraints of this problem.

## 说明/提示

Note that the example test cases do not represent an optimal strategy for asking questions and are only shown for the sake of demonstrating the interaction format. Specifically, we cannot determine which player is the Impostor from the questions asked in the examples.

In the first test case of the example, players at indices $ 2 $ and $ 6 $ are Knights, players at indices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are Knaves, and the Impostor is at index $ 4 $ . The following is an explanation of the questions asked:

- In the first query, player $ i $ is a Knave and player $ j $ is a Knave. The answer is "yes" since Knaves always lie.
- In the second query, player $ i $ is a Knave and player $ j $ is a Knight. The answer is "no" since Knaves always lie.
- In the third query, player $ i $ is a Knight and player $ j $ is a Knave. The answer is "no" since Knights always tell the truth.
- In the fourth query, player $ i $ is a Knight and player $ j $ is a Knight. The answer is "yes" since Knights always tell the truth.
- In the fifth query, player $ i $ is a Impostor and player $ j $ is a Knave. The answer is "yes" since the Impostor always lies.
- In the sixth query, player $ i $ is a Impostor and player $ j $ is a Knight. The answer is "no" since the Impostor always lies.
- In the seventh query, player $ i $ is a Knave and player $ j $ is a Impostor. The answer is "no" since Knaves always lie and Knaves thinks that the Impostor is a Knight.
- In the eighth query, player $ i $ is a Knight and player $ j $ is a Impostor. The answer is "yes" since Knights always tell the truth and Knights think that the Impostor is a Knight.

## 样例 #1

### 输入

```
2
7

1

0

0

1

1

0

0

1

4

0

1

1

1```

### 输出

```
? 1 3

? 7 6

? 2 5

? 6 2

? 4 5

? 4 6

? 1 4

? 2 4

! 4

? 1 2

? 2 3

? 3 4

? 4 1

! 3```

# AI分析结果

### 题目中文重写
# 冒名顶替者（简单版本）

## 题目描述
这是该问题的简单版本。在此版本中，你最多可以询问 $n + 69$ 个问题。只有当两个版本的问题都解决后，你才能进行 Hack 操作。

这是一个交互式问题。

在墨西哥的国家信息学奥林匹克竞赛（IOI）培训中，有一个传统游戏叫 “冒名顶替者”，它类似于 “Among Us” 或 “黑手党” 游戏。

今天，有 $n$ 名玩家，编号从 $1$ 到 $n$，将玩 “冒名顶替者” 游戏，玩家有以下三种角色：
- 骑士：骑士总是说真话。
- 骗子：骗子总是说谎。
- 冒名顶替者：冒名顶替者是每个人都认为是骑士，但实际上是骗子的人。

每个玩家在游戏中都会被分配一个角色。游戏中恰好有一个冒名顶替者，但骑士和骗子的数量可以是任意的（可能为零）。

作为游戏主持人，你不小心忘记了每个人的角色，但你需要确定谁是冒名顶替者。

为了确定冒名顶替者，你可以问一些问题。在每个问题中，你将选择两名玩家 $i$ 和 $j$（$1 \leq i, j \leq n$；$i \neq j$），并询问玩家 $i$ 是否认为玩家 $j$ 是骑士。问题的结果如下表所示：

|          | 骑士 | 骗子 | 冒名顶替者 |
|----------|------|------|------------|
| 骑士     | 是   | 否   | 是         |
| 骗子     | 否   | 是   | 否         |
| 冒名顶替者 | 否   | 是   | —          |

表格中第 $a$ 行和第 $b$ 列的单元格中的响应是当 $i$ 具有角色 $a$ 且 $j$ 具有角色 $b$ 时询问问题的结果。例如，右上角单元格中的 “是” 属于 “骑士” 行和 “冒名顶替者” 列，所以当 $i$ 是骑士且 $j$ 是冒名顶替者时，响应为 “是”。

请在最多 $n + 69$ 个问题内找出冒名顶替者。

注意：评测机是自适应的，玩家的角色在开始时并不固定，可能会根据你的问题而改变。但是，保证在这个问题的约束下，存在一个与所有先前询问的问题一致的角色分配。

## 说明/提示
请注意，示例测试用例并不代表询问问题的最优策略，仅用于演示交互格式。具体来说，我们无法从示例中询问的问题确定哪个玩家是冒名顶替者。

在示例的第一个测试用例中，索引为 $2$ 和 $6$ 的玩家是骑士，索引为 $1$、$3$、$5$ 和 $7$ 的玩家是骗子，冒名顶替者的索引为 $4$。以下是对询问问题的解释：
- 在第一次查询中，玩家 $i$ 是骗子，玩家 $j$ 是骗子。答案是 “是”，因为骗子总是说谎。
- 在第二次查询中，玩家 $i$ 是骗子，玩家 $j$ 是骑士。答案是 “否”，因为骗子总是说谎。
- 在第三次查询中，玩家 $i$ 是骑士，玩家 $j$ 是骗子。答案是 “否”，因为骑士总是说真话。
- 在第四次查询中，玩家 $i$ 是骑士，玩家 $j$ 是骑士。答案是 “是”，因为骑士总是说真话。
- 在第五次查询中，玩家 $i$ 是冒名顶替者，玩家 $j$ 是骗子。答案是 “是”，因为冒名顶替者总是说谎。
- 在第六次查询中，玩家 $i$ 是冒名顶替者，玩家 $j$ 是骑士。答案是 “否”，因为冒名顶替者总是说谎。
- 在第七次查询中，玩家 $i$ 是骗子，玩家 $j$ 是冒名顶替者。答案是 “否”，因为骗子总是说谎，并且骗子认为冒名顶替者是骑士。
- 在第八次查询中，玩家 $i$ 是骑士，玩家 $j$ 是冒名顶替者。答案是 “是”，因为骑士总是说真话，并且骑士认为冒名顶替者是骑士。

## 样例 #1
### 输入
```
2
7

1

0

0

1

1

0

0

1

4

0

1

1

1
```
### 输出
```
? 1 3

? 7 6

? 2 5

? 6 2

? 4 5

? 4 6

? 1 4

? 2 4

! 4

? 1 2

? 2 3

? 3 4

? 4 1

! 3
```

### 综合分析与结论
- **思路对比**：四位作者思路基本一致，均是利用若 $(i,j) \neq (j,i)$ 时，$i$ 和 $j$ 中必有一个是冒名顶替者这一特性，先将玩家两两配对询问，找出有嫌疑的一组，再找一个额外的玩家 $k$ 与这组中的一个人相互询问来确定冒名顶替者。
- **算法要点**：将 $n$ 个玩家两两配对进行询问，若结果不同则该组有冒名顶替者，再通过两次额外询问确定具体是谁。
- **解决难点**：主要难点在于发现 $(i,j) \neq (j,i)$ 与冒名顶替者的关系，以及合理选择额外询问的玩家 $k$ 。

### 所选题解
- **作者：WuMin4（5星）**
    - **关键亮点**：思路清晰，代码可读性高，详细注释了思路和代码逻辑。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
signed main(){
    cin>>T;
    while(T--){
        cin>>n;
        string res1,res2;
        int id=0;
        for(int i=1;i<=n-(n%2);i+=2){
            cout<<"? "<<i<<" "<<i+1<<endl;
            cin>>res1;
            cout<<"? "<<i+1<<" "<<i<<endl;
            cin>>res2;
            if(res1!=res2){
                id=i;
                break;
            }
        }
        if(!id){
            cout<<"! "<<n<<endl;
            continue;
        }
        else{
            if(id==1){
                cout<<"? "<<id+1<<" "<<id+2<<endl;
                cin>>res1;
                cout<<"? "<<id+2<<" "<<id+1<<endl;
                cin>>res2;
                if(res1==res2)
                    cout<<"! "<<id<<endl;
                else
                    cout<<"! "<<id+1<<endl;
            }
            else{
                cout<<"? "<<id-1<<" "<<id<<endl;
                cin>>res1;
                cout<<"? "<<id<<" "<<id-1<<endl;
                cin>>res2;
                if(res1==res2)
                    cout<<"! "<<id+1<<endl;
                else
                    cout<<"! "<<id<<endl;
            }
        }
    }
    return 0;
}
```
核心实现思想：先将玩家两两配对询问，若结果不同则记录起始编号，若没找到则认为最后一个是冒名顶替者。找到有嫌疑的一组后，根据情况选择额外玩家进行询问，根据结果确定冒名顶替者。

- **作者：WYX1210（4星）**
    - **关键亮点**：思路简洁明了，代码实现较为规范。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define maxn 200005
#define multicase() int t;cin>>t;while(t--)
using namespace std;
int n,a[maxn],b[maxn],x,y;
void solve()
{
    cin >> n ;
    bool flg = 0;
    for(int i=1;i<=n/2;i++)
    {
        cout << "? " << i*2-1 << " " << i*2 << endl;
        cin >> x;
        cout << "? " << i*2 << " " << i*2-1 << endl;
        cin >> y ;
        if(x!=y)
        {
            if(i>1)
            {
                cout << "? " << i*2-1 << " " << i*2-2 << endl;
                cin >> x;
                cout << "? " << i*2-2 << " " << i*2-1 << endl;
                cin >> y ;
            }
            else
            {
                cout << "? " << i*2-1 << " " << n << endl;
                cin >> x ;
                cout << "? " << n << " " << i*2-1 << endl;
                cin >> y;
            }
            if(x!= y) cout << "! " << i*2-1 << endl;
            else cout << "! " << i*2 << endl;
            flg = 1;
            break;
        }
    }
    if(!flg) cout << "! " << n << endl;
}
int main()
{
    int t;
    cin >> t ;
    while(t--) solve(); 
    return 0;
}
```
核心实现思想：同样是两两配对询问，若结果不同则根据情况选择额外玩家询问，确定冒名顶替者，若没找到则认为最后一个是。

- **作者：yifu_chen（4星）**
    - **关键亮点**：将询问和回答封装成函数，代码结构清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
bool opt;
bool ask(int a,int b)
{
    cout<<"? "<<a<<" "<<b<<endl;
    cin>>opt;
    return opt;
}
void ans(int a)
{
    cout<<"! "<<a<<endl;
    return;
}
void check(int a,int b)
{
    int c;
    if(a!=1&&b!=1)c=1;
    else if(a!=2&&b!=2)c=2;
    else if(a!=3&&b!=3)c=3;
    if(ask(a,c)!=ask(c,a))ans(a);
    else                  ans(b);
    return;
}
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        bool flag=false;
        for(int i=1;i<n-i+1;i++)
        {
            if(ask(i,n-i+1)!=ask(n-i+1,i))
            {
                check(i,n-i+1);
                flag=true;
                break;
            }
        }
        if(flag)continue;
        ans((n+1)/2);
    }
    return 0;
}
```
核心实现思想：通过 `ask` 函数进行询问，`ans` 函数输出结果，`check` 函数确定冒名顶替者。将玩家两两配对询问，若结果不同则调用 `check` 函数，若没找到则认为中间位置的是冒名顶替者。

### 最优关键思路或技巧
- 观察问题表格，发现 $(i,j) \neq (j,i)$ 与冒名顶替者的关系，利用这一特性缩小查找范围。
- 将玩家两两配对询问，减少询问次数，同时合理选择额外询问的玩家来确定冒名顶替者。

### 可拓展之处
同类型题可能会增加角色种类、改变询问规则或增加更多限制条件。类似算法套路是通过观察问题的特性，将对象进行分组处理，逐步缩小目标范围，最终确定答案。

### 推荐洛谷题目
- P1168 中位数：通过合适的数据结构动态维护中位数，与本题通过合理询问缩小范围确定目标有相似的思维方式。
- P1955 [NOI2015] 程序自动分析：利用并查集处理变量之间的相等和不等关系，本题可类比为通过询问处理玩家之间的关系。
- P2024 [NOI2001] 食物链：通过并查集维护动物之间的食物链关系，与本题通过询问确定玩家角色有一定相似性。

### 个人心得
题解中未包含个人心得。 

---
处理用时：63.38秒